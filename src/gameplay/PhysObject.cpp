#include <gameplay/PhysObject.hpp>

#include <iostream>
#include <cmath>

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
    b2Vec2 pos(x_, y_);
    b2Vec2 direction = pos - center;
    float distance = direction.Normalize();

    float decay = std::exp(-ph::explosionDecay * distance);
    direction.x = direction.x * magnitude * decay;
    direction.y = direction.y * magnitude * decay;

    Impulse(direction);
}

void PhysObject::DealDamage(float damage) {
    hp_ -= damage;
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

    if(offscreen || zerohp) { 
        this->OnDeath();
        game_.DestroyObject(gameID_); return;
    }
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

void PhysObject::OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact) {

    b2Vec2 v = {(other.GetObjectType() == gm::GameObjectType::ground_obj) ? 0 : other.GetX() - x_, other.GetY() - y_};
    b2Vec2 v2 = velocity;
    v.Normalize();
    v2.Normalize();
    float dotV = std::abs(v.x * v2.x + v.y * v2.y);
    if(dotV > 0.5F && velocity.LengthSquared() > ph::damageTreshold) hp_ -= ph::damageScaling * velocity.Length() * 0.5F * (GetMass() + other.GetMass());

}
