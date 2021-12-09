#ifndef TEEKKARI_HPP
#define TEEKKARI_HPP

#include <screens/GameScreen.hpp>
#include <ui/UIConstants.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/PhysObject.hpp>
#include <framework/RandomGen.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/Person.hpp>
#include <box2d/b2_body.h>
#include <memory>

class Teekkari : public Person {
public:
    Teekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, data.objType, x, y, rot)
    { data_ = data; }
    Teekkari(Game& game, gm::GameObjectType type, float x, float y, float rot) : Person(game, type, x, y, rot, false, -5)
    { data_ = gm::RandomTeekkari(type); hp_ = ph::teekkariHP; creationTime_ = game_.GetTime(); }

    virtual void Update() {
        if(mainBody_->GetLinearVelocity().Length() < 0.1F) sleepCounter_++;
        else sleepCounter_ = 0;
        if(game_.GetTime() - creationTime_ > 8.0F || sleepCounter_ > 10) hp_ = 0;
        Person::Update();
    }

    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh) {
        if(!game_.IsPaused() && button == sf::Mouse::Button::Right && !abilityUsed_) {
            this->Ability(xw, yh);
            abilityUsed_ = true;
            return true;
        }   else return false;
    }

protected:
    virtual void OnDeath() { game_.CheckLevelEnd(); }
    virtual void Ability(float x, float y) = 0;

    float creationTime_;
    bool abilityUsed_ = false;
    int sleepCounter_ = 0;

};


//Abilities


class AbilityCow : public PhysObject {
public:
    AbilityCow(Game& game, float x, float y, float rot) : PhysObject(game, gm::GameObjectType::ability_cow, x, y, rot) {
        hp_ = 100000;
        creationTime_ = game.GetTime();

        //Create the main body
        b2BodyDef definition;
        definition.type = b2BodyType::b2_dynamicBody;
        definition.fixedRotation = false;
        definition.position = {x, y};
        definition.angle = ph::rotToAng(rot);
        
        mainBody_ = game.GetB2World().CreateBody(&definition);
        
        b2PolygonShape shape;
        shape.SetAsBox(1.333333F, 1.0F);
        b2FixtureDef fixture;
        b2FixtureUserData userData;
        userData.data = this;
        fixture.density = 1000.0F;
        fixture.friction = 0.0F;
        fixture.restitution = 0.4F;
        fixture.filter.groupIndex = -5;
        fixture.shape = &shape;
        fixture.userData = userData;
        mainBody_->CreateFixture(&fixture);

        Angular(rng::RandomInt(0, 1) ? (10000 + rng::RandomF() * 10000) : (-10000 - rng::RandomF() * 10000));
        Impulse({0, 14000.0F});

        Record();
    }

    virtual void Render(const RenderSystem& r) {
        r.RenderSprite(SpriteID::cow, x_, y_, 2.0F, rot_, game_.GetCamera());
    }

    virtual void Update() {
        if(game_.GetTime() - creationTime_ > 5.0F) hp_ = 0;
        PhysObject::Update();
    }

protected:
    float creationTime_;
    virtual void OnDeath() {

        //Moo
        //Spawn smoke

    }
};


class AbilityWrench : public PhysObject {
public:
    AbilityWrench(Game& game, float x, float y, float rot) : PhysObject(game, gm::GameObjectType::ability_wrench, x, y, rot) {
        creationTime_ = game.GetTime();

        //Create the main body
        b2BodyDef definition;
        definition.type = b2BodyType::b2_dynamicBody;
        definition.fixedRotation = false;
        definition.position = {x, y};
        definition.angle = ph::rotToAng(rot);
        
        mainBody_ = game.GetB2World().CreateBody(&definition);
        
        gm::BlockMaterialData metalData = gm::materialProperties.at(gm::metal);

        b2PolygonShape shape;
        shape.SetAsBox(0.5F, 0.16F);
        b2FixtureDef fixture;
        b2FixtureUserData userData;
        userData.data = this;
        fixture.density = metalData.density;
        fixture.friction = metalData.friction;
        fixture.restitution = metalData.restitution;
        fixture.filter.groupIndex = -5;
        fixture.shape = &shape;
        fixture.userData = userData;
        mainBody_->CreateFixture(&fixture);

        hp_ = 10;

        Angular(900.0F);

        Record();
    }

    virtual void Render(const RenderSystem& r) {
        r.RenderSprite(SpriteID::wrench, x_, y_, 0.32F, rot_, game_.GetCamera());
    }

    virtual void Update() {
        if(game_.GetTime() - creationTime_ > 5.0F) hp_ = 0;
        PhysObject::Update();
    }

protected:
    float creationTime_;
    virtual void OnDeath() {

        //Moo
        //Spawn smoke
    }

    virtual void OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact) {

        PhysObject::OnCollision(velocity, other, contact);

        //Collision sound

        //Deal extra damage to wood
        if(gm::GetObjectGroup(other.GetObjectType()) == gm::GameObjectGroup::block) {
            if(gm::blockTypes.at(other.GetObjectType()).material == gm::BlockMaterial::wood) {
                other.DealDamage(200);
            }
        }
    }

};



//Teekkaris

class IKTeekkari : public Teekkari {
public:
    IKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    IKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

    }
};

class SIKTeekkari : public Teekkari {
public:
    SIKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    SIKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

    }
};

class TEFYTeekkari : public Teekkari {
public:
    TEFYTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    TEFYTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

    }
};

class TUTATeekkari : public Teekkari {
public:
    TUTATeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    TUTATeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

    }
};

class TIKTeekkari : public Teekkari {
public:
    TIKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    TIKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

    }
};

class INKUBIOTeekkari : public Teekkari {
public:
    INKUBIOTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    INKUBIOTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {
        auto cow = std::make_unique<AbilityCow>(game_, x_, y_, 0.0F);
        game_.AddObject(std::move(cow));
    }
};

class KIKTeekkari : public Teekkari {
public:
    KIKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    KIKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {
        auto relativeCoords = game_.GetScreen().GetApplication().GetRenderSystem().GetRelativeCoords({x_, y_}, game_.GetCamera());
        targetDir = {x - relativeCoords.x, relativeCoords.y - y};
        targetDir.Normalize();
        mainBody_->SetLinearVelocity({0, 0});
        headBody_->SetLinearVelocity({0, 0});
        mainBody_->ApplyAngularImpulse(1800.0F, true);
        armRBody_->ApplyLinearImpulseToCenter({targetDir.x * -1000.0F, targetDir.y * -1000.0F}, true);
    }

    virtual void Update() {
        if(abilityUsed_ && wrenchesShot_ < 3 && game_.GetTime() - lastShotTime_ > shootingInterval_) {
            int id = game_.AddObject(std::make_unique<AbilityWrench>(game_, x_ + targetDir.x * 0.5F, y_ + targetDir.y * 0.5F, 0.0F));
            AbilityWrench& wrench = (AbilityWrench&)game_.GetObject(id);
            wrench.Impulse({5000.0F * targetDir.x, 5000.0F * targetDir.y});
            lastShotTime_ = game_.GetTime();
            wrenchesShot_++;
        }
        Teekkari::Update();
    }

private:
    float shootingInterval_ = 0.2F;
    float lastShotTime_ = 0;
    int wrenchesShot_ = 0;
    b2Vec2 targetDir = {0, -1};
};

class Professor : public Teekkari {
public:
    Professor(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    Professor(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

    }
};


#endif