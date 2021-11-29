#include <gameplay/PhysObject.hpp>

#include <iostream>

PhysObject::~PhysObject() { 
    game_.GetB2World().DestroyBody(mainBody_);
}

void PhysObject::Impulse(const b2Vec2& f) { mainBody_->ApplyLinearImpulseToCenter(f, true);}
void PhysObject::Impulse(const b2Vec2& f, const b2Vec2& p) { mainBody_->ApplyLinearImpulse(f, p, true);}
void PhysObject::Force(const b2Vec2& f) { mainBody_->ApplyForceToCenter(f, true); }
void PhysObject::Force(const b2Vec2& f, const b2Vec2& p) { mainBody_->ApplyForce(f, p, true); }
void PhysObject::Torque(float t) { mainBody_->ApplyTorque(t, true); }
void PhysObject::Angular(float a) { mainBody_->ApplyAngularImpulse(a, true); }

void PhysObject::Explosion(const b2Vec2& center, float magnitude) { 

}


float PhysObject::GetHP() const { return hp_; }
float PhysObject::GetMass() const { return mainBody_->GetMass(); }


void PhysObject::Update() { 
    
    //Record previous state
    this->Record();

    //Update current state based on box2d
    const b2Vec2& pos = mainBody_->GetPosition();
    x_ = pos.x;
    y_ = pos.y;
    rot_ = mainBody_->GetAngle();

    //Destroy off screen objects
    if(x_ > 0.5F * ph::fullscreenPlayArea || x_ < -0.5F * ph::fullscreenPlayArea) game_.DestroyObject(gameID_);
    else if(y_ < 0.0F) game_.DestroyObject(gameID_);

    //Destroy zero hp objects
    if(hp_ <= 0) game_.DestroyObject(gameID_);

}

void PhysObject::SetX(float x) {
    GameObject::SetX(x);
    float y = mainBody_->GetPosition().y;
    float a = mainBody_->GetAngle();
    mainBody_->SetTransform({x, y}, a);
}

void PhysObject::SetY(float y) {
    GameObject::SetY(y);
    float x = mainBody_->GetPosition().x;
    float a = mainBody_->GetAngle();
    mainBody_->SetTransform({x, y}, a);
}

void PhysObject::SetRotation(float rot) {
    GameObject::SetRotation(rot);
    mainBody_->SetTransform(mainBody_->GetPosition(), rot);
}

void PhysObject::SetPosition(float x, float y) {
    x_ = x; y_ = y;
    float a = mainBody_->GetAngle();
    mainBody_->SetTransform({x, y}, a);
}

void PhysObject::OnCollision(b2Vec2 relativeVelocity, PhysObject& other) {
    
    hp_ -= ph::damageScaling * relativeVelocity.Length() * 0.5F * (GetMass() + other.GetMass());
    if(hp_ <= 0) mainBody_->GetFixtureList()->SetSensor(true);

}
