#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <screens/GameScreen.hpp>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
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


void Game::LoadLevel(Level level) {
    level_  = level;
    ClearObjects();
    IDCounter_ = {};
    CreateObject(gm::GameObjectType::ground_obj);
    for(const auto& objectdata : level.objectData) {
        CreateObject(objectdata.type,objectdata.x,objectdata.y,objectdata.rot);
    }
}

//TODO: this isn't an actual implementation, this will crash for invalid ID values
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


void Game::DestroyObject(int id) {
    objects_.erase(id);
}

void Game::ClearObjects() {
    objects_.clear();
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
    if(objA) objA->OnCollision(-velocity, *objB);
    if(objB) objB->OnCollision(velocity, *objA);
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
}

void Game::Render(const RenderSystem& r) {

    //Render all objects in render order
    for(auto& obj : objects_) {
        obj.second->Render(r);
    }

}

bool Game::OnMouseMove(float xw, float yh) {
    if(mDown) {
        mouseX = xw;
        mouseY = yh;
        Camera c = GetCamera();
        c.x -= ph::fullscreenPlayArea * c.zoom * (mouseX.f1 - mouseX.f0);
        c.y += ph::fullscreenPlayArea * c.zoom * (mouseY.f1 - mouseY.f0);
        SetCameraPos(c.x, c.y);
        mouseX.Record();
        mouseY.Record();
        return true;
    }
    for(auto& obj : objects_) {
        if(obj.second->OnMouseMove(xw, yh)) return true;
    }
    return false;
}


bool Game::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh) {
    for(auto& obj : objects_) {
        if(obj.second->OnMouseDown(button, xw, yh)) return true;
    }
    
    if(button == sf::Mouse::Button::Right) {
        mDown = true;
        mouseX = xw;
        mouseY = yh;
        mouseX.Record();
        mouseY.Record();
        return true;
    }
    
    return false;
}


bool Game::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh) {
    if(button == sf::Mouse::Button::Right && mDown) {
        mDown = false;
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


    return true;
}

unsigned int Game::GetTicks() const { return time_; };
float Game::GetTime() const { return time_ * ph::timestep; }


const Camera& Game::GetCamera() const { return camera_; }

void Game::ResetCamera() { 
    camera_.SetFullscreen();
    camera_.zoom = 0.6F;
    camera_.y = 5;
}

void Game::SetCameraPos(float x, float y) { camera_.x = x; camera_.y = y; }
void Game::SetCameraZoom(float zoom) { camera_.zoom = zoom; }
void Game::SetCameraRot(float rot) { camera_.rot = rot; }


AudioSystem& Game::GetAudioSystem() const { return screen_.GetApplication().GetAudioSystem(); }
b2World& Game::GetB2World() { return world_; }

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
    LoadLevel(level_);
}
