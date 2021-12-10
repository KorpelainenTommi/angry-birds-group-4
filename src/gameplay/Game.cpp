#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <screens/GameScreen.hpp>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RandomGen.hpp>
#include <gameplay/Teekkari.hpp>
#include <math.h>
#include <iostream>

Game::Game(GameScreen& gameScreen) : screen_(gameScreen), world_({0, -ph::gravity}) {
    //Listen to contacts
    world_.SetContactListener(this);

    Restart();

}

Game::Game(GameScreen& gameScreen, Level level) : Game(gameScreen) {
    level_ = level;
    Restart();
}

//Notice that LoadLevel shouldn't reset the following things:
//-points
//-time
//-projectiles the player can use
//This way endless mode works as intended

void Game::LoadLevel(Level level) {
    level_  = level;
    ClearObjects();
    IDCounter_ = {};
    
    levelMaxScore_ = level_.CalculateMaxScore();
    //Create ground and cannon
    CreateObject(gm::GameObjectType::ground_obj);
    CreateObject(gm::GameObjectType::cannon, ph::cannonX);

    //Create all other objects
    for(const auto& objectdata : level.objectData)
        CreateObject(objectdata.type,objectdata.x,objectdata.y,objectdata.rot);


    //Add starting teekkaris to list
    for(const auto& t : level.startingTeekkaris)
        teekkarisLeft_.push_back(gm::RandomTeekkari(t));
    
    //RandomTeekkari doesn't pick random starting teekkaris, it just picks random faces for the starting teekkaris
    
    UpdateProjectileList();

}

//NOTE! This will crash for invalid ID values, so be careful
GameObject& Game::GetObject(int id) {
    return *objects_[id];
}

int Game::AddObject(std::unique_ptr<GameObject> obj) {
    int id;
    switch (gm::GetObjectGroup(obj->objectType_)) {
        case gm::GameObjectGroup::background : id = IDCounter_.backgrounds++; break;
        case gm::GameObjectGroup::block : id = IDCounter_.blocks++; break;
        case gm::GameObjectGroup::teekkari : id = IDCounter_.teekkaris++; break;
        case gm::GameObjectGroup::effect : id = IDCounter_.effects++; break;
        case gm::GameObjectGroup::ground : id = 4 * gm::objectGroupSize; break;
    }
    obj->gameID_ = id;
    objects_[id] = std::move(obj);

    return id;
}

int Game::CreateObject(gm::GameObjectType type, float x, float y, float rot) {
    std::unique_ptr<GameObject> obj = gm::IDToObject(*this, type, x, y, rot);
    return AddObject(std::move(obj));
}

int Game::CreateTeekkari(gm::PersonData data, float x, float y, float rot) {
    std::unique_ptr<Teekkari> obj;
    switch(data.objType) {
        case gm::GameObjectType::teekkari_ik: obj = std::make_unique<IKTeekkari>(*this, x, y, rot, data); break;
        case gm::GameObjectType::teekkari_sik: obj = std::make_unique<SIKTeekkari>(*this, x, y, rot, data); break;
        case gm::GameObjectType::teekkari_tefy: obj = std::make_unique<TEFYTeekkari>(*this, x, y, rot, data); break;
        case gm::GameObjectType::teekkari_tuta: obj = std::make_unique<TUTATeekkari>(*this, x, y, rot, data); break;
        case gm::GameObjectType::teekkari_tik: obj = std::make_unique<TIKTeekkari>(*this, x, y, rot, data); break;
        case gm::GameObjectType::teekkari_inkubio: obj = std::make_unique<INKUBIOTeekkari>(*this, x, y, rot, data); break;
        case gm::GameObjectType::teekkari_kik: obj = std::make_unique<KIKTeekkari>(*this, x, y, rot, data); break;
        case gm::GameObjectType::teekkari_professor: obj = std::make_unique<Professor>(*this, x, y, rot, data); break;
        default: obj = std::make_unique<IKTeekkari>(*this, x, y, rot, data); break;
    }
    return AddObject(std::move(obj));
}


void Game::DestroyObject(int id) {
    objects_.erase(id);
}

void Game::ClearObjects() {
    objects_.clear();
}

void Game::SelectProjectile(int index) {
    chosenTeekkari_ = index;
}

bool Game::TakeProjectile(gm::PersonData& teekkari) {
    if(teekkarisLeft_.size() < 1) return false;
    teekkari = teekkarisLeft_.at(chosenTeekkari_);
    teekkarisLeft_.erase(teekkarisLeft_.begin() + chosenTeekkari_);
    chosenTeekkari_ = 0;

    UpdateProjectileList();

    return true;
}

Game::~Game() {
    ClearObjects();
}


void Game::BeginContact(b2Contact* contact) {
    if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor()) return;
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    //Calculate relative velocity
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    b2Vec2 velocity = bodyA->GetLinearVelocityFromWorldPoint(worldManifold.points[0]) - bodyB->GetLinearVelocityFromWorldPoint(worldManifold.points[0]);
    if(velocity.LengthSquared() < ph::collisionTreshold) return;
    
    //Call OnCollision
    PhysObject* objA = ((PhysObject*)contact->GetFixtureA()->GetUserData().data);
    PhysObject* objB = ((PhysObject*)contact->GetFixtureB()->GetUserData().data);
    if(objA) objA->OnCollision(-velocity, *objB, *contact);
    if(objB) objB->OnCollision(velocity, *objA, *contact);
}

void Game::Update() {

    if(isPaused_) return;
    //Increment tick count
    time_++;

    world_.Step(ph::timestep, ph::velocityIters, ph::positionIters);

    //Call update on objects. They will handle their own business
    
    auto it = objects_.begin();
    int i = 0;
    while(it != objects_.end()) {
        (it++)->second->Update();
    }

    bool timeLimitReached = (level_.levelMode == LevelMode::time_trial && level_.timeLimit > 0 && GetTime() > level_.timeLimit);

    //Don't add anything after this. Fuksi and Teekkari checks might end the level
    if(checkForFinish_ || timeLimitReached) {
        checkForFinish_ = false;
        bool b = CheckFuksiCount();
        if(!b) b = CheckTeekkariCount();
        if(!b && timeLimitReached) screen_.OnGameLost("Out of time");
    }
}

void Game::CheckCameraBounds() {
    if(camera_.x-ph::fullscreenPlayArea/2.0F*camera_.zoom < -ph::fullscreenPlayArea/2.0F){
        camera_.x = -ph::fullscreenPlayArea/2.0F*(1-camera_.zoom);
    }
    else if(camera_.x+ph::fullscreenPlayArea/2.0F*camera_.zoom > ph::fullscreenPlayArea/2.0F){
        camera_.x = ph::fullscreenPlayArea/2.0F*(1-camera_.zoom);
    }
    if(camera_.y-ph::fullscreenPlayArea/2.0F*camera_.zoom < -ph::groundThickness){
        camera_.y = -ph::groundThickness + camera_.zoom*ph::fullscreenPlayArea/2.0F;
    }
    else if(camera_.y+ph::fullscreenPlayArea/2.0F*camera_.zoom > ph::cameraUpperBound){
        camera_.y = ph::cameraUpperBound-ph::fullscreenPlayArea/2.0F*camera_.zoom;
    }
}

void Game::UpdateProjectileList() {
    std::vector<std::pair<SpriteID, std::string>> uiIcons;
    for(const auto& t : teekkarisLeft_)
        uiIcons.push_back({t.face.face, t.body.guildName});
    screen_.UpdateProjectileList(uiIcons);
}

//Mark for level end check

void Game::CheckLevelEnd() {
    checkForFinish_ = true;
}

bool Game::CheckTeekkariCount() {
    if(teekkarisLeft_.empty()) {
        bool noActiveTeekkaris = true;
        for(const auto& o : objects_) {
            if(std::find(gm::teekkaris.begin(), gm::teekkaris.end(), o.second->objectType_) != gm::teekkaris.end()) {
                noActiveTeekkaris = false;
                break;
            }
        }

        if(noActiveTeekkaris) {
            screen_.OnGameLost();
            return true;
        }
    }
    return false;
}

bool Game::CheckFuksiCount() {
    bool noFuksis = true;
    for(const auto& o : objects_) {
        if(o.second->objectType_ == gm::GameObjectType::fuksi) {
            noFuksis = false;
            break;
        }
    }

    if(noFuksis) {
        if(level_.levelMode == LevelMode::endless) {
            auto levels = screen_.GetApplication().GetFileManager().ListEndless();
            LoadLevel(levels[rng::RandomInt(0, levels.size()-1)]);
        }
        else if(level_.levelMode == LevelMode::time_trial && level_.timeLimit > 0) {
            float timeLeft = (float)(level_.timeLimit - GetTime()) / level_.timeLimit;
            int p = (int)roundf(timeLeft * points_);
            screen_.OnGameCompleted(p, level_.perfectScore);
        }
        else screen_.OnGameCompleted(points_, level_.perfectScore);
    }
    return noFuksis;
}

void Game::Render(const RenderSystem& r) {
    //Render all objects in render order
    float parallax = 0.5F;
    r.RenderSprite(level_.backgroundImage, parallax * camera_.x, 0.3F * ph::fullscreenPlayArea + parallax * camera_.y, 0.66458333F * ph::fullscreenPlayArea * 1.5F, 0, camera_);

    for(auto& obj : objects_) {
        obj.second->Render(r);
    }

}

bool Game::OnMouseMove(float xw, float yh) {
    
    if(movingCamera_) {
        cameraGrabX_ = xw;
        cameraGrabY_ = yh;
        Camera c = GetCamera();
        c.x -= ph::fullscreenPlayArea * c.zoom * (cameraGrabX_.f1 - cameraGrabX_.f0);
        c.y += ph::fullscreenPlayArea * c.zoom * (cameraGrabY_.f1 - cameraGrabY_.f0) / ui::aspectRatio;
        SetCameraPos(c.x, c.y);
        cameraGrabX_.Record();
        cameraGrabY_.Record();
        CheckCameraBounds();
        return true;
    }
    for(auto& obj : objects_) {
        if(obj.second->OnMouseMove(xw, yh)) return true;
    }
    return false;
}


bool Game::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh) {

    bool b = false;
    for(auto& obj : objects_) {
        if(obj.second->OnMouseDown(button, xw, yh)) b = true;
    }
    if(b) return true;
    
    if(button == sf::Mouse::Button::Middle) {
        movingCamera_ = true;
        cameraGrabX_ = xw;
        cameraGrabY_ = yh;
        cameraGrabX_.Record();
        cameraGrabY_.Record();
        return true;
    }
    
    return false;
}


bool Game::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh) {
    if(button == sf::Mouse::Button::Middle && movingCamera_) {
        movingCamera_ = false;
        return true;
    }
    for(auto& obj : objects_) {
        if(obj.second->OnMouseUp(button, xw, yh)) return true;
    }
    return false;
}

bool Game::OnMouseScroll(float delta, float xw, float yh) {

    float zoom = GetCamera().zoom;
    zoom -= delta * 0.1F;
    if(zoom <= 0.1F) SetCameraZoom(0.1F);
    else if(zoom > 1.0F) SetCameraZoom(1.0F);
    else SetCameraZoom(zoom);
    CheckCameraBounds();

    return true;
}

unsigned int Game::GetTicks() const { return time_; };
float Game::GetTime() const { return time_ * ph::timestep; }
float Game::GetTimeForUI() const {
    if(level_.levelMode == LevelMode::time_trial && level_.timeLimit > 0) return level_.timeLimit - GetTime();
    else return GetTime();
}


const Camera& Game::GetCamera() const { return camera_; }

void Game::ResetCamera() {
    camera_.SetFullscreen();
    camera_.y = 10;
    CheckCameraBounds();
}

void Game::SetCameraPos(float x, float y) { camera_.x = x; camera_.y = y; }
void Game::SetCameraZoom(float zoom) { camera_.zoom = zoom; }
void Game::SetCameraRot(float rot) { camera_.rot = rot; }
void Game::AddPoints(int p) { points_ += p; screen_.OnScoreChange(points_); }

AudioSystem& Game::GetAudioSystem() const { return screen_.GetApplication().GetAudioSystem(); }
b2World& Game::GetB2World() { return world_; }
GameScreen& Game::GetScreen() { return screen_; }

bool Game::CannonDisabled() const { return isPaused_ || teekkarisLeft_.empty(); }
bool Game::IsPaused() const { return isPaused_; }

void Game::Pause() {

    for(const auto& obj : objects_) obj.second->Record();
    isPaused_ = true;
}

void Game::Resume() {
    isPaused_ = false;
}

void Game::Restart() {
    ResetCamera();
    teekkarisLeft_.clear();
    isPaused_ = false;
    time_ = 0;
    points_ = 0;
    chosenTeekkari_ = 0;
    screen_.OnScoreChange(0);
    LoadLevel(level_);
}

int Game::GetMaxScore() {
    return levelMaxScore_;
}


