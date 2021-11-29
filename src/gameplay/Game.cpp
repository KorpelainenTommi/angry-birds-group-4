#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <screens/GameScreen.hpp>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <iostream>

Game::Game(GameScreen& gameScreen) : screen_(gameScreen), world_({0, -ph::gravity}) {

    //Create the ground
    CreateObject(gm::GameObjectType::ground_obj);

    //Listen to contacts
    world_.SetContactListener(this);

    //Reset camera to fullscreen
    camera_.SetFullscreen();
    camera_.zoom = 0.6F;
    camera_.Record();

}

Game::Game(GameScreen& gameScreen, Level level) : Game(gameScreen) {
    LoadLevel(level);
}


void Game::LoadLevel(Level level) {
    level_  = level;
    ClearObjects();
    if(level.levelMode != LevelMode::endless) teekkarisLeft_.clear();
    ResetCamera();
    IDCounter_ = {};
    CreateObject(gm::GameObjectType::ground_obj);
    for(const auto& objectdata : level.objectData) {
        CreateObject(objectdata.type,objectdata.x,objectdata.y,objectdata.rot);
    }
}


int Game::CreateObject(gm::GameObjectType type, float x, float y, float rot) {

    std::unique_ptr<GameObject> obj = gm::IDToObject(*this, type, x, y, rot);
    int id;
    switch (gm::GetObjectGroup(type)) {
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

    //Increment tick count
    time_++;

    //Record previous camera pos
    camera_.Record();
    world_.Step(ph::timestep, ph::velocityIters, ph::positionIters);

    //Call update on objects. They will handle their own business
    
    //It is important to increment iterator first, since Update might destroy the object causing the iterator to become invalid
    auto it = objects_.begin();
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


unsigned int Game::GetTicks() const { return time_; };
float Game::GetTime() const { return time_ * ph::timestep; }


const Camera& Game::GetCamera() const { return camera_; }

void Game::ResetCamera() { camera_.SetFullscreen(); }
void Game::SetCameraPos(float x, float y) { camera_.x = x; camera_.y = y; }
void Game::SetCameraZoom(float zoom) { camera_.zoom = zoom; }
void Game::SetCameraRot(float rot) { camera_.rot = rot; }


AudioSystem& Game::GetAudioSystem() const { return screen_.GetApplication().GetAudioSystem(); }
b2World& Game::GetB2World() { return world_; }



