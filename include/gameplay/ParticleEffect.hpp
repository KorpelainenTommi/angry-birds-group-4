#ifndef FUKSI_HPP
#define FUKSI_HPP

#include <include/gameplay/GameObjectTypes.hpp>
#include <include/gameplay/PhysObject.hpp>
#include <include/gameplay/Physics.hpp>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_body.h>

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
        fixture.isSensor = true;
        userData.data = this;
        fixture.shape = &shape;
        fixture.userData = userData;
        mainBody_->CreateFixture(&fixture);

        Record();
    }

    virtual void Render(const RenderSystem& r) {
        r.RenderSprite(sprite_, x_, y_, size_, rot_, game_.GetCamera());
    }

    virtual void Update() {
        if(game_.GetTime() - creationTime_ > lifeTime_) hp_ = 0;
        PhysObject::Update();
    }

    void SetSize(float sz) { size_ = sz; }
    void SetLifeTime(float l) { lifeTime_ = l; }
    void SetSprite(SpriteID sp) { sprite_ = sp; }

protected:
    float creationTime_;
    float size_ = 0.1F;
    float lifeTime_ = 1.0F;
    SpriteID sprite_ = SpriteID::particles_dust;
};

#endif