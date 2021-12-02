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


    //TODO: Implement in the cpp
    //Explosion should add an impulse away from center, with a magnitude that decays exponentially with distance
    //The decay factor lambda is defined in ph::explosionDecay
    //The magnitude should be <magnitude> at 0 distance from the center

    /// Add explosive force away from this
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
    rot_ = ph::angToRot(mainBody_->GetAngle());

    //Important! Immediately return after destroying the object. DestroyObject causes the destructor to be called (I think???) which is why
    //any code that accesses member variables will crash if put after it

    //Destroy off screen objects
    bool offscreen = x_ > 0.5F * ph::fullscreenPlayArea || x_ < -0.5F * ph::fullscreenPlayArea;
    offscreen = offscreen || (y_ < -ph::groundThickness);

    //Destroy zero hp objects
    bool zerohp = hp_ <= 0;

    if(offscreen || zerohp) { game_.DestroyObject(gameID_); return; }
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
    mainBody_->SetTransform(mainBody_->GetPosition(), ph::rotToAng(rot));
}

void PhysObject::SetPosition(float x, float y) {
    x_ = x; y_ = y;
    float a = mainBody_->GetAngle();
    mainBody_->SetTransform({x, y}, a);
}

void PhysObject::OnCollision(b2Vec2 relativeVelocity, PhysObject& other) {
    hp_ -= ph::damageScaling * relativeVelocity.Length() * 0.5F * (GetMass() + other.GetMass());

}
