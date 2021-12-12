#ifndef PARTICLE_EFFECT_HPP
#define PARTICLE_EFFECT_HPP

#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/PhysObject.hpp>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_body.h>
#include <limits>
#include <string>
#include <cmath>

/// @brief Particle class with physics
class PhysParticle : public PhysObject {
public:
    /// @brief Constructor
    PhysParticle(Game& game, float x, float y, float rot) : PhysObject(game, gm::GameObjectType::phys_particle, x, y, rot) {
        hp_ = std::numeric_limits<float>::infinity();
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
    /// @brief Renders the particle
    virtual void Render(const RenderSystem& r) {
        float opacity = 1.0F;
        float t = creationTime_ + lifeTime_ - game_.GetTime();
        if(t < ph::particleFadeTime) {
            opacity = t / ph::particleFadeTime;
            opacity *= opacity;
        }
        r.RenderSprite(sprite_, x_, y_, size_, rot_, game_.GetCamera(), sf::Color(255, 255, 255, (int)std::roundf(opacity * 255)));
    }
    /// @brief Updates particle: location and lifetime
    virtual void Update() {
        if(game_.GetTime() - creationTime_ > lifeTime_) hp_ = 0;
        PhysObject::Update();
    }
    /// @brief Sets size of the particle
    void SetSize(float sz) { size_ = sz; }
    /// @brief Sets lifetime of the particle
    void SetLifeTime(float l) { lifeTime_ = l; }
    /// @brief Sets sprite of the particle
    void SetSprite(SpriteID sp) { sprite_ = sp; }
    /// @brief Implements parentclass method and returns empty vector.
    virtual std::vector<b2Body*> GetPhysBodies() { return std::vector<b2Body*>(); }
    
    /// @brief Get mainbody
    b2Body* GetBody() { return mainBody_; }

protected:

    // Allows professor to create special particles that move in stopped time
    float creationTime_;
    float size_ = 0.1F;
    float lifeTime_ = 1.0F;
    SpriteID sprite_ = SpriteID::particles_dust;
};

/// @brief Particle class for texts
class TextParticle : public PhysObject {
public:
    /// @brief Constructor
    TextParticle(Game& game, float x, float y, float rot) : PhysObject(game, gm::GameObjectType::phys_particle, x, y, rot) {
        hp_ = std::numeric_limits<float>::infinity();
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
    /// @brief Renders the particle
    virtual void Render(const RenderSystem& r) {
        float opacity = 1.0F;
        float t = creationTime_ + lifeTime_ - game_.GetTime();
        if(t < ph::particleFadeTime) {
            opacity = t / ph::particleFadeTime;
            opacity *= opacity;
        }
        r.RenderText(text_, x_, y_, size_, rot_, game_.GetCamera(), sf::Color(color_.r, color_.g, color_.b, (int)std::roundf(opacity * 255)), FontID::consolas);
    }
    /// @brief Updates particle: location and lifetime
    virtual void Update() {
        if(game_.GetTime() - creationTime_ > lifeTime_) hp_ = 0;
        PhysObject::Update();
    }
    /// @brief Sets size of the particle
    void SetSize(float sz) { size_ = sz; }
    /// @brief Sets lifetime of the particle
    void SetLifeTime(float l) { lifeTime_ = l; }
    /// @brief Sets text of the particle
    void SetText(std::string text) { text_ = text; }
    /// @brief Sets color of the particle
    void SetColor(sf::Color color) { color_ = color; }
    /// @brief Implements parentclass method and return empty vector.
    virtual std::vector<b2Body*> GetPhysBodies() { return std::vector<b2Body*>(); }

protected:
    float creationTime_;
    float size_ = 0.1F;
    float lifeTime_ = 1.0F;
    std::string text_ = "";
    sf::Color color_ = {255, 106, 0, 255};
};


/// @brief Special particle that moves in stopped time
class ProfessorParticle : public GameObject {
public:
    /// @brief Constructor
    ProfessorParticle(Game& game, float x, float y, float rot) : GameObject(game, gm::GameObjectType::professor_particle, x, y, rot) {
        creationTime_ = game.GetTime();
        Record();
    }
    /// @brief Renders the particle
    virtual void Render(const RenderSystem& r) {
        float opacity = 1.0F;
        float t = creationTime_ + lifeTime_ - GetRealTime();
        if(t < ph::particleFadeTime) {
            opacity = t / ph::particleFadeTime;
            opacity *= opacity;
        }
        r.RenderSprite(sprite_, x_, y_, size_, rot_, game_.GetCamera(), sf::Color(255, 255, 255, (int)std::roundf(opacity * 255)));
    }
    /// @brief Updates particle: location and lifetime
    virtual void Update() {
        upd_++;
        if(GetRealTime() - creationTime_ > lifeTime_) game_.DestroyObject(gameID_);
        else {
            Record();
            x_ = x_ + ph::timestep * vx;
            y_ = y_ + ph::timestep * vy;
        }
    }
    /// @brief Sets size of the particle
    void SetSize(float sz) { size_ = sz; }
    /// @brief Sets lifetime of the particle
    void SetLifeTime(float l) { lifeTime_ = l; }
    /// @brief Sets sprite of the particle
    void SetSprite(SpriteID sp) { sprite_ = sp; }
    /// @brief Implements parentclass method and return empty vector.
    virtual std::vector<b2Body*> GetPhysBodies() { return std::vector<b2Body*>(); }
    /// @brief Set velocity of the particle
    void SetVelocity(float x, float y) { vx = x; vy = y; }


protected:

    float GetRealTime() {
        return creationTime_ + upd_ * ph::timestep;
    }

    int upd_ = 0;
    float creationTime_;
    float size_ = 0.1F;
    float lifeTime_ = 1.0F;
    SpriteID sprite_ = SpriteID::particles_dust;
    float vx = 0;
    float vy = 0;
};


#endif
