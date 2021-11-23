#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <screens/GameScreen.hpp>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <gameplay/PhysObject.hpp>

#include <iostream>

Game::Game(GameScreen& gameScreen) : screen_(gameScreen), world_({0, -ph::gravity}) {

    //Create the ground
    b2BodyDef groundDef;
    b2PolygonShape groundShape;
    groundDef.position = {0, -0.5F * ph::groundThickness};
    groundShape.SetAsBox(ph::fullscreenPlayArea * 0.5F, 0.5F * ph::groundThickness);

    //Box2D clones the data so it doesn't matter that groundDef and groundShape go out of scope
    ground_ = world_.CreateBody(&groundDef);
    ground_->CreateFixture(&groundShape, 0.0F);


    //Listen to contacts
    world_.SetContactListener(this);

    //Reset camera to fullscreen
    camera_.SetFullscreen();
    camera_.zoom = 0.6F;
    camera_.Record();

}

//TODO: should use gm::GetObjectGroup(GameObjectType) give object ids from groups
int Game::CreateObject(gm::GameObjectType type, float x, float y, float rot) {

    std::unique_ptr<GameObject> obj = gm::IDToObject(*this, type, x, y, rot);
    int id = simpleIDCounter++;
    obj->gameID_ = id;
    objects_[obj->gameID_] = std::move(obj);

    return id;
}


void Game::DestroyObject(int id) {
    objects_.erase(id);
}

void Game::ClearObjects() {
    objects_.clear();
}


Game::~Game() {
    world_.DestroyBody(ground_);
    ClearObjects();
}

void Game::BeginContact(b2Contact* contact) {
    
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    b2Vec2 velocity = bodyA->GetLinearVelocityFromWorldPoint(worldManifold.points[0]) - bodyB->GetLinearVelocityFromWorldPoint(worldManifold.points[0]);
    if(velocity.LengthSquared() < ph::collisionTreshold) return;
    PhysObject* objA = nullptr;
    PhysObject* objB = nullptr;

    if(bodyA != ground_) objA = ((PhysObject*)contact->GetFixtureA()->GetUserData().data);
    if(bodyB != ground_) objB = ((PhysObject*)contact->GetFixtureB()->GetUserData().data);

    if(objA) objA->OnCollision(-velocity, *objB, bodyB == ground_);
    if(objB) objB->OnCollision(velocity, *objA, bodyA == ground_);
}

void Game::Update() {

    //Increment tick count
    time_++;

    //Record previous camera pos
    camera_.Record();
    world_.Step(ph::timestep, ph::velocityIters, ph::positionIters);

    //Call update on objects. They will handle their own business
    for(auto& obj : objects_) {
        obj.second->Update();
    }

}

void Game::Render(const RenderSystem& r) {

    //Render all objects in render order
    for(auto& obj : objects_) {
        obj.second->Render(r);
    }


    //Render the ground last
    r.RenderRect(ph::groundColor, 0, -0.5F * ph::groundThickness, ph::fullscreenPlayArea, ph::groundThickness, 0, camera_);

}



const Camera& Game::GetCamera() const { return camera_; }

void Game::ResetCamera() { camera_.SetFullscreen(); }
void Game::SetCameraPos(float x, float y) { camera_.x = x; camera_.y = y; }
void Game::SetCameraZoom(float zoom) { camera_.zoom = zoom; }
void Game::SetCameraRot(float rot) { camera_.rot = rot; }


AudioSystem& Game::GetAudioSystem() const { return screen_.GetApplication().GetAudioSystem(); }
b2World& Game::GetB2World() { return world_; }


