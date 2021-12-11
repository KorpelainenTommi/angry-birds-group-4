#include <gameplay/PhysObject.hpp>

#include <framework/RandomGen.hpp>
#include <gameplay/ParticleEffect.hpp>
#include <iostream>
#include <memory>
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

void PhysObject::ExplosionDamage(const b2Vec2& center, float damage) {
    b2Vec2 pos(x_, y_);
    b2Vec2 direction = pos - center;
    float distance = direction.Normalize();

    float decay = std::exp(-ph::explosionDecay * distance);
    DealDamage(decay * damage);
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

    if(spawnHit_) {
        spawnHit_ = false;
        float a = 2.0F * ph::pi * rng::RandomF();
        float u = rng::RandomF() + rng::RandomF();
        float r = (u > 1) ? 2 - u : u;
        float x = 0.5F * r * cosf(a);
        float y = 0.5F * r * sinf(a);
        int id = game_.AddObject(std::make_unique<PhysParticle>(game_, hitPoint_.x + x, hitPoint_.y + y, ph::angToRot(a)));
        PhysParticle& p = (PhysParticle&)game_.GetObject(id);

        p.SetSize(0.25F);
        p.SetSprite(hitSp_);
        p.Angular(rng::RandomInt(0, 1) ? rng::RandomF() * 0.4F : -rng::RandomF() * 0.4F);
        p.Impulse({0, 10.0F});
    }

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
    if(dotV > 0.5F && velocity.LengthSquared() > ph::damageTreshold) {
        hp_ -= ph::damageScaling * velocity.Length() * 0.5F * (GetMass() + other.GetMass());
        
        SpriteID hitSp = SpriteID::hit_stars;

        if(dotV * velocity.LengthSquared() < ph::damageTreshold * 2) hitSp = SpriteID::particles_dust;
        else hitSp = SpriteID::hit_stars;
            
        b2WorldManifold manifold;
        contact.GetWorldManifold(&manifold);
        auto point = manifold.points[0];
        hitSp_ = hitSp;
        hitPoint_ = point;
        spawnHit_ = true;
    }

}


bool PhysObject::ContainsCoordinates(sf::Vector2f mouseCoords, const RenderSystem& r) {

    auto absCoords = mouseCoords;
    return mainBody_->GetFixtureList()[0].TestPoint({absCoords.x, absCoords.y});

}

std::vector<b2Body*> PhysObject::GetPhysBodies() {
    std::vector<b2Body*> vec;
    vec.push_back(mainBody_);
    return vec;
}

bool PhysObject::CheckIntersection(b2Body* other) {
    return b2TestOverlap(mainBody_->GetFixtureList()[0].GetShape(), 0, other->GetFixtureList()[0].GetShape(), 0, mainBody_->GetTransform(), other->GetTransform());
}