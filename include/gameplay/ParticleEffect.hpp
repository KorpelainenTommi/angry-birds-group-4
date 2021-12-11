#ifndef PARTICLE_EFFECT_HPP
#define PARTICLE_EFFECT_HPP

#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/PhysObject.hpp>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_body.h>
#include <string>
#include <cmath>

class PhysParticle : public PhysObject {
public:
    PhysParticle(Game& game, float x, float y, float rot) : PhysObject(game, gm::GameObjectType::phys_particle, x, y, rot) {
        hp_ = 100;
        creationTime_ = game.GetTime();

        //Create the main body
        b2BodyDef definition;
        definition.type = b2BodyType::b2_dynamicBody;
        definition.fixedRotation = false;
        definition.position = {x, y};
        definition.angle = ph::rotToAng(rot);
        
        mainBody_ = game.GetB2World().CreateBody(&definition);
        
        b2CircleShape shape;
        shape.m_radius = 0.1F;
        b2FixtureDef fixture;
        b2FixtureUserData userData;
        fixture.density = 100.0F;
        fixture.isSensor = true;
        userData.data = this;
        fixture.shape = &shape;
        fixture.userData = userData;
        mainBody_->CreateFixture(&fixture);

        Record();
    }

    virtual void Render(const RenderSystem& r) {
        float opacity = 1.0F;
        float t = creationTime_ + lifeTime_ - game_.GetTime();
        if(t < ph::particleFadeTime) {
            opacity = t / ph::particleFadeTime;
            opacity *= opacity;
        }
        r.RenderSprite(sprite_, x_, y_, size_, rot_, game_.GetCamera(), sf::Color(255, 255, 255, (int)std::roundf(opacity * 255)));
    }

    virtual void Update() {
        if(game_.GetTime() - creationTime_ > lifeTime_) hp_ = 0;
        PhysObject::Update();
    }

    void SetSize(float sz) { size_ = sz; }
    void SetLifeTime(float l) { lifeTime_ = l; }
    void SetSprite(SpriteID sp) { sprite_ = sp; }
    b2Body* GetBody() { return mainBody_; }

protected:
    float creationTime_;
    float size_ = 0.1F;
    float lifeTime_ = 1.0F;
    SpriteID sprite_ = SpriteID::particles_dust;
};

class TextParticle : public PhysObject {
public:
    TextParticle(Game& game, float x, float y, float rot) : PhysObject(game, gm::GameObjectType::phys_particle, x, y, rot) {
        hp_ = 100;
        creationTime_ = game.GetTime();

        //Create the main body
        b2BodyDef definition;
        definition.type = b2BodyType::b2_dynamicBody;
        definition.fixedRotation = false;
        definition.position = {x, y};
        definition.angle = ph::rotToAng(rot);
        
        mainBody_ = game.GetB2World().CreateBody(&definition);
        
        b2CircleShape shape;
        shape.m_radius = 0.1F;
        b2FixtureDef fixture;
        b2FixtureUserData userData;
        fixture.density = 100.0F;
        fixture.isSensor = true;
        userData.data = this;
        fixture.shape = &shape;
        fixture.userData = userData;
        mainBody_->CreateFixture(&fixture);
        mainBody_->SetGravityScale(-0.5F);

        Record();
    }

    virtual void Render(const RenderSystem& r) {
        float opacity = 1.0F;
        float t = creationTime_ + lifeTime_ - game_.GetTime();
        if(t < ph::particleFadeTime) {
            opacity = t / ph::particleFadeTime;
            opacity *= opacity;
        }
        r.RenderText(text_, x_, y_, size_, rot_, game_.GetCamera(), sf::Color(color_.r, color_.g, color_.b, (int)std::roundf(opacity * 255)), FontID::magneto);
    }

    virtual void Update() {
        if(game_.GetTime() - creationTime_ > lifeTime_) hp_ = 0;
        PhysObject::Update();
    }

    void SetSize(float sz) { size_ = sz; }
    void SetLifeTime(float l) { lifeTime_ = l; }
    void SetText(std::string text) { text_ = text; }
    void SetColor(sf::Color color) { color_ = color; }

protected:
    float creationTime_;
    float size_ = 0.1F;
    float lifeTime_ = 1.0F;
    std::string text_ = "";
    sf::Color color_ = {255, 106, 0, 255};
};

#endif