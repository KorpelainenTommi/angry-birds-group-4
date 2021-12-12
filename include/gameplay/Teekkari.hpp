#ifndef TEEKKARI_HPP
#define TEEKKARI_HPP

#include <framework/RenderSystem.hpp>
#include <screens/GameScreen.hpp>
#include <ui/UIConstants.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/ParticleEffect.hpp>
#include <gameplay/PhysObject.hpp>
#include <framework/RandomGen.hpp>
#include <SFML/System/Vector2.hpp>
#include <gameplay/Effect.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/Person.hpp>
#include <box2d/b2_body.h>
#include <memory>

#include <gameplay/Block.hpp>
#include <cmath>
#include <set>
#include <limits>


/// @brief Class for the projectiles of the game
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

/// @brief Class for cow ability of an inkubioteekkari. Spawns a cow.
class AbilityCow : public PhysObject {
public:
    AbilityCow(Game& game, float x, float y, float rot) : PhysObject(game, gm::GameObjectType::ability_cow, x, y, rot) {
        hp_ = 300000;
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

        game_.GetAudioSystem().PlaySound(SoundID::cow_moo);

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

        game_.GetAudioSystem().PlaySound(SoundID::cow_death);
        game_.GetAudioSystem().PlaySound(SoundID::poof);
        game_.AddObject(std::make_unique<Effect>(game_, AnimationID::particles_poof,
        x_, y_, 0.0F, 2.0F, 60.0F, 0.2666666F));
        
        game_.CheckLevelEnd();
    }
};

/// @brief Class for wrench ability of an ikteekkari. Spawns wrenches
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
        fixture.density = metalData.density * 0.04F;
        fixture.friction = metalData.friction;
        fixture.restitution = metalData.restitution;
        fixture.filter.groupIndex = -5;
        fixture.shape = &shape;
        fixture.userData = userData;
        mainBody_->CreateFixture(&fixture);

        hp_ = 1;

        Angular(40.0F);

        Record();

        game_.GetAudioSystem().PlaySound(SoundID::wrench_swish);

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

        game_.GetAudioSystem().PlaySound(SoundID::metal_hit);
        game_.CheckLevelEnd();

    }

    virtual void OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact) {

        PhysObject::OnCollision(velocity, other, contact);
        hp_ = 0;

        //Collision sound

        //Deal extra damage to wood
        if(gm::GetObjectGroup(other.GetObjectType()) == gm::GameObjectGroup::block) {
            if(gm::blockTypes.at(other.GetObjectType()).material == gm::BlockMaterial::wood) {
                other.DealDamage(1000);
            }
        }
    }

};

/// @brief Class for integral ability of a professor
class AbilityIntegral : public PhysObject {
public:
    AbilityIntegral(Game& game, float x, float y, float rot, const b2Vec2 velocity) : PhysObject(game, gm::GameObjectType::ability_integral, x, y, rot) {
        // Normalized velocity
        b2Vec2 nVelocity = velocity;
        nVelocity *= 1/std::sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
        x_ += 3.0F*nVelocity.x;
        y_ += 3.0F*nVelocity.y;
        
        rot_ = std::atanf(nVelocity.x/nVelocity.y)*180/ph::pi;
        if(nVelocity.y < 0) rot_ = rot_ + 180;

        creationTime_ = game.GetTime();
        //Create the main body
        b2BodyDef definition;
        definition.type = b2BodyType::b2_kinematicBody;
        definition.fixedRotation = false;
        definition.position = {x_, y_};
        definition.angle = ph::rotToAng(rot_);
        
        mainBody_ = game.GetB2World().CreateBody(&definition);


        b2PolygonShape shape;
        shape.SetAsBox(3.0F, 1.0F);
        b2FixtureDef fixture;
        b2FixtureUserData userData;
        userData.data = this;

        fixture.filter.groupIndex = -5;
        fixture.shape = &shape;
        fixture.userData = userData;
        mainBody_->CreateFixture(&fixture);
        mainBody_->SetLinearVelocity(velocity);
        hp_ = ph::inf;
        Record();

    }

    virtual void Render(const RenderSystem& r) {
        r.RenderSprite(SpriteID::integral_sign, x_, y_, 2.0F, rot_, game_.GetCamera());
    }

    virtual void Update() {
        if(game_.GetTime() - creationTime_ > ph::integralLength) hp_ = 0;
        PhysObject::Update();
    }
    virtual void OnCollision(const b2Vec2& relativeVelocity, PhysObject& other, const b2Contact& contact) {
        other.DealDamage(other.GetHP());
        SpriteID hitSp = SpriteID::hit_stars;
        b2WorldManifold manifold;
        contact.GetWorldManifold(&manifold);
        auto point = manifold.points[0];
        hitSp_ = hitSp;
        hitPoint_ = point;
        spawnHit_ = true;
        
    }

protected:
    float creationTime_;
    virtual void OnDeath() {

        game_.CheckLevelEnd();

    }

};



/// @brief Class for the integral ability of a professor
class AbilityIntegral : public GameObject {
public:
    AbilityIntegral(Game& game, float x, float y, float rot) : GameObject(game, gm::GameObjectType::ability_integral, x, y, rot) {
        creationTime_ = game.GetTime();
        hitShape_.SetAsBox(width_ / 2, height_ / 2);
        Record();
    }

    virtual void Render(const RenderSystem& r) {
        r.RenderSprite(SpriteID::integral_sign, x_, y_, height_, rot_, game_.GetCamera());
    }

    virtual void Update() {

        updCount_++;

        if(GetRealTime() - creationTime_ > 3.2F) {
            game_.DestroyObject(gameID_);
        }
        else {

            b2Transform hitTransform;
            hitTransform.Set({x_, y_}, 0);

            auto objs = game_.GetObjects();
            for(auto o : game_.GetObjects()) {
                if(o->GetObjectType() != gm::GameObjectType::ability_integral 
                && o->GetObjectType() != gm::GameObjectType::teekkari_professor
                && o->GetObjectType() != gm::GameObjectType::professor_particle) {
                    if(gm::GetObjectGroup(o->GetObjectType()) == gm::GameObjectGroup::block 
                    || gm::GetObjectGroup(o->GetObjectType()) == gm::GameObjectGroup::teekkari) {
                        auto physBodies = o->GetPhysBodies();
                        bool hit = false;
                        for(auto p : physBodies) {
                            if(b2TestOverlap(&hitShape_, 0, p->GetFixtureList()[0].GetShape(), 0, hitTransform, p->GetTransform())) {
                                hit = true;
                                break;
                            }
                        }
                        if(hit) {
                            PhysObject* phys = (PhysObject*)o;
                            phys->DealDamage(std::numeric_limits<float>::infinity());
                        }
                    }
                }
            }

            x_.Record();
            x_ += ph::timestep * ph::fullscreenPlayArea / 3.2F;
        }
    }

protected:

    float GetRealTime() {
        return creationTime_ + updCount_ * ph::timestep;
    }

    int updCount_ = 0;
    float creationTime_;
    b2PolygonShape hitShape_;
    float height_ = 2.0F;
    float width_ = 5.15625F;

};



//Teekkaris
/// @brief  Class for IKteekkari
class IKTeekkari : public Teekkari {
public:
    IKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    IKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

    }
};
/// @brief Class for SIKteekkari
class SIKTeekkari : public Teekkari {
public:
    SIKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    SIKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
    
    virtual void Render(const RenderSystem& r) {
        Teekkari::Render(r);

        if(abilityUsed_ && !used_) {
            float t = game_.GetTime() - abilityStartTime_;
            int frame = (int)(t * 20.0F);
            r.RenderAnimation(AnimationID::thunder_sparks, frame, x_, y_, 2.0F, 0.0F, game_.GetCamera());
        }

        if(lightning_) {
            r.RenderSprite(SpriteID::lightning_strike, lightningPos_.x, lightningPos_.y, lightningH_, lightningRot_, game_.GetCamera());
            if(game_.GetTime() > lightningStart_ + 0.05F) lightning_ = false;
        }
    }

    virtual void Update() {

        if(abilityUsed_ && !used_ && game_.GetTime() > abilityStartTime_ + 1.0F) {
            ActiveAbility();
            used_ = true;
        }

        int c = sleepCounter_;
        Teekkari::Update();

        //Prevent the Teekkari from despawning when he is charging his ability
        if(abilityUsed_ && !used_) sleepCounter_ = c;
    }

protected:
    virtual void Ability(float x, float y) {
        abilityStartTime_ = game_.GetTime();
        game_.GetAudioSystem().PlaySound(SoundID::thunder_static);
    }



    float abilityStartTime_ = 0;
    bool used_ = false;

    b2Vec2 lightningPos_ = {0, 0};
    float lightningH_ = 0;
    float lightningRot_ = 0;
    bool lightning_ = false;
    float lightningStart_ = 0;

    void ActiveAbility() {
        std::set<int> metalBlocks;
        int nearestBlock = -1;
        float minDistance = ph::inf;
        for(auto o : game_.GetObjects()) {
            if(o->GetGameID() >= gm::objectGroupSize && o->GetGameID() < 2*gm::objectGroupSize) {
                Block& block = static_cast<Block&>(*o);
                if(block.GetBlockMaterial() == gm::BlockMaterial::metal) {
                    metalBlocks.insert(o->GetGameID());
                    float distance = std::sqrt((x_-block.GetX())*(x_-block.GetX())+(y_-block.GetY())*(y_-block.GetY()));
                    if(distance < minDistance) {
                        minDistance = distance;
                        nearestBlock = o->GetGameID();
                    }
                }
            }
        }
        std::function<void(int,float)> destroyRecursively = [&](int startBlock, float remainingEnergy) {
            Block& currentBlock = static_cast<Block&>(game_.GetObject(startBlock));
            metalBlocks.erase(startBlock);
            std::set<int>::iterator it = metalBlocks.begin();
            while(it != metalBlocks.end()) {
                Block& nextBlock = static_cast<Block&>(game_.GetObject(*it));
                if(currentBlock.ElectricityCheck(nextBlock) && remainingEnergy > 200) {
                    float exponentialDecay = 2.5F;
                    destroyRecursively(*it,remainingEnergy/exponentialDecay);
                    it = metalBlocks.begin();
                }
                else {
                    ++it;
                }
            }
            currentBlock.DealDamage(remainingEnergy);
            game_.AddObject(std::make_unique<Effect>(game_, AnimationID::lightning, currentBlock.GetX(), currentBlock.GetY(), 0.0F, 4.0F, 40.0F, 0.1F));
        };
        if(nearestBlock != -1 && minDistance < 15.0F) {
            auto& block = game_.GetObject(nearestBlock);
            b2Vec2 v = {block.GetX() - x_, block.GetY() - y_};
            float d = v.Length();

            lightning_ = true;
            lightningStart_ = game_.GetTime();
            lightningPos_ = {x_ + v.x * 0.5F, y_ + v.y * 0.5F};
            lightningH_ = 0.364583333F * (v.Length());
            lightningRot_ = (v.y > 0) ? acosf(v.x / d) : 2 * ph::pi - acosf(v.x / d);
            lightningRot_ = ph::angToRot(lightningRot_);

            destroyRecursively(nearestBlock,ph::lightningEnergy);
            game_.GetAudioSystem().PlaySound(SoundID::thunder_strike);
        }
    }

};
/// @brief Class for TEFYTeekkari
class TEFYTeekkari : public Teekkari {
public:
    TEFYTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    TEFYTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
    
    
    virtual void Update() {
        float t = 3.0F + abilityStartTime_ - game_.GetTime();
        if(abilityUsed_ && t > 0) {
            Torque(-8000.0F / (t*t));
            if(gCounter == 0) {
                auto objs = game_.GetObjects();
                
                b2CircleShape circle;
                circle.m_radius = 15.0F;
                
                for(auto o : objs) {
                    if(o->GetGameID() != gameID_) {
                        auto physBodies = o->GetPhysBodies();
                        bool hit = false;
                        for(auto p : physBodies) {
                            if(b2TestOverlap(&circle, 0, p->GetFixtureList()[0].GetShape(), 0, mainBody_->GetTransform(), p->GetTransform())) {
                                hit = true;
                                break;
                            }
                        }
                        if(hit) {
                            PhysObject* phys = (PhysObject*)o;
                            phys->Explosion({x_, y_}, phys->GetMass() * -15.0F);
                        }
                    }
                }
            }
            gCounter++;
            gCounter %= 5;
        }
        
        else if(abilityUsed_) {
            game_.GetAudioSystem().PlaySound(SoundID::gravity_shiftdown);
            hp_ = 0;
        }
        Teekkari::Update();
    }

    virtual void Render(const RenderSystem& r) {

        float t = 3.0F + abilityStartTime_ - game_.GetTime();
        if(abilityUsed_ && t > 0) {

        float timeLeft = game_.GetTime() - abilityStartTime_;
        int frame = (int)(timeLeft * 30.0F);


        float fade = 200 * (t / 2.5F);
        if(fade < 0) fade = 0;
        sf::Color c = sf::Color(255, 255, 255, (int)roundf(fade));
        r.RenderAnimation(AnimationID::gravity_spiral, frame, x_, y_, 2.5F, 0, game_.GetCamera(), c);
        SpriteID arm = data_.face.bType ? data_.body.armb : data_.body.arm;
        r.RenderSprite(arm, armLX_, armLY_, armHeight, armLRot_, game_.GetCamera(), c);
        r.RenderSprite(data_.body.leg, legLX_, legLY_, legHeight, legLRot_, game_.GetCamera(), c);
        r.RenderSprite(data_.body.torso, x_, y_, torsoHeight, rot_, game_.GetCamera(), c);
        r.RenderSprite(data_.body.leg, legRX_, legRY_, legHeight, legRRot_, game_.GetCamera(), c);
        r.RenderSprite(arm, armRX_, armRY_, armHeight, armRRot_, game_.GetCamera(), c);
        r.RenderSprite(data_.face.face, headX_, headY_, headHeight, headRot_, game_.GetCamera(), c);
        }
        else Teekkari::Render(r);
    }

protected:
    virtual void Ability(float x, float y) {
        game_.GetAudioSystem().PlaySound(SoundID::gravity_shiftup);

        int id = game_.AddObject(std::make_unique<PhysParticle>(game_, x_, y_, 0.0F));
        PhysParticle& p = (PhysParticle&)game_.GetObject(id);

        p.SetSprite(SpriteID::gravity_symbols);
        p.SetSize(1.5F);
        p.GetBody()->SetGravityScale(0);
        p.GetBody()->ApplyLinearImpulseToCenter({0, 10.0F}, true);

        abilityStartTime_ = game_.GetTime();

        mainBody_->SetGravityScale(0);
        headBody_->SetGravityScale(0);
        armRBody_->SetGravityScale(0);
        armLBody_->SetGravityScale(0);
        legRBody_->SetGravityScale(0);
        legLBody_->SetGravityScale(0);

        mainBody_->SetLinearDamping(3);
        headBody_->SetLinearDamping(3);
        armRBody_->SetLinearDamping(3);
        armLBody_->SetLinearDamping(3);
        legRBody_->SetLinearDamping(3);
        legLBody_->SetLinearDamping(3);

        mainBody_->GetFixtureList()[0].SetSensor(true);
        headBody_->GetFixtureList()[0].SetSensor(true);
        armRBody_->GetFixtureList()[0].SetSensor(true);
        armLBody_->GetFixtureList()[0].SetSensor(true);
        legRBody_->GetFixtureList()[0].SetSensor(true);
        legLBody_->GetFixtureList()[0].SetSensor(true);



        hp_ = std::numeric_limits<float>::infinity();
    }



    int gCounter = 0;
    float abilityStartTime_ = 0;
};
/// @brief Class for TUTAteekkari
class TUTATeekkari : public Teekkari {
public:
    TUTATeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    TUTATeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
    
    virtual void Update() {
        if(abilityUsed_ && game_.GetTime() < abilityStartTime_ + 2.0F) {
            Force({0, 2000.0F});
            if(whooshCounter == 0) {
                game_.GetAudioSystem().PlaySound(SoundID::hand_whoosh);
                
                auto objs = game_.GetObjects();
                
                b2CircleShape circle;
                circle.m_radius = 4.0F;
                
                for(auto o : objs) {
                    if(o->GetGameID() != gameID_) {
                        auto physBodies = o->GetPhysBodies();
                        bool hit = false;
                        for(auto p : physBodies) {
                            if(b2TestOverlap(&circle, 0, p->GetFixtureList()[0].GetShape(), 0, mainBody_->GetTransform(), p->GetTransform())) {
                                hit = true;
                                break;
                            }
                        }
                        if(hit) {
                            PhysObject* phys = (PhysObject*)o;
                            phys->ExplosionDamage({x_, y_}, 3000);
                            phys->Explosion({x_, y_}, phys->GetMass() * 15.0F);
                        }
                    }
                }
            }
            whooshCounter++;
            whooshCounter %= 5;

            armRBody_->SetAngularVelocity(100);
            armLBody_->SetAngularVelocity(100);
        }
        Teekkari::Update();
    }

    virtual void Render(const RenderSystem& r) {
        Teekkari::Render(r);
        if(abilityUsed_ && game_.GetTime() < abilityStartTime_ + 2.0F) {
            float t = game_.GetTime() - abilityStartTime_;
            int frame = (int)(t * 60.0F);
            r.RenderAnimation(AnimationID::hand_whirl, frame, x_, y_, 3.0F, rot_, game_.GetCamera());
        }
    }

protected:
    virtual void Ability(float x, float y) {
        abilityStartTime_ = game_.GetTime();
    }

    int whooshCounter = 0;
    float abilityStartTime_ = 0;
};


/// @brief Class for TIKteekkari
class TIKTeekkari : public Teekkari {
public:
    TIKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    TIKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}
protected:
    virtual void Ability(float x, float y) {

        game_.GetAudioSystem().PlaySound(SoundID::glitch_sound);
        game_.AddObject(std::make_unique<Effect>(game_, AnimationID::matrix_bug,
        x_, y_, 0.0F, 1.0F, 60.0F, 0.1F));
        SetX(x_ + 8.0F);
        Record();
        game_.AddObject(std::make_unique<Effect>(game_, AnimationID::matrix_bug,
        x_, y_, 0.0F, 1.0F, 60.0F, 0.1F));


    }
};
/// @brief Class for INKUBIOteekkari
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


/// @brief Class for KIKteekkari
class KIKTeekkari : public Teekkari {
public:
    KIKTeekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    KIKTeekkari(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}

    virtual void Update() {
        if(abilityUsed_ && wrenchesShot_ < 3 && game_.GetTime() - lastShotTime_ > shootingInterval_) {
            int id = game_.AddObject(std::make_unique<AbilityWrench>(game_, x_ + targetDir.x * 0.5F, y_ + targetDir.y * 0.5F, 0.0F));
            AbilityWrench& wrench = (AbilityWrench&)game_.GetObject(id);
            wrench.Impulse({250.0F * targetDir.x, 250.0F * targetDir.y});
            lastShotTime_ = game_.GetTime();
            wrenchesShot_++;
        }
        Teekkari::Update();
    }

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

    float shootingInterval_ = 0.2F;
    float lastShotTime_ = 0;
    int wrenchesShot_ = 0;
    b2Vec2 targetDir = {0, -1};
};



/// @brief Class for the professor
class Professor : public Teekkari {
public:
    Professor(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, x, y, rot, data) {}
    Professor(Game& game, float x, float y, float rot) : Teekkari(game, gm::GameObjectType::teekkari_ik, x, y, rot) {}

    virtual void Update() {
        updCount_++;
        if(abilityUsed_ && GetRealTime() > abilityStartTime_ + 3.2F) {
            if(!resumed_) { 
                resumed_ = true;
                game_.ProfessorResume();
            }
        }

        else if(abilityUsed_) {

            float t = GetRealTime() - abilityStartTime_;
            t /= 3.2F;

            auto v = tVelocity_;
            v = {v.x * 0.9F, v.y * 0.9F};
            SetX(x_ + ph::timestep * v.x);
            //tY_ = tY_ + ph::timestep * v.y;
            tVelocity_ = v;
            SetY(tY_ + sinf(t * 2 * ph::pi));

            int rDeg = abs((int)rot_) % 360;
            int rDeg2 = rDeg % 180;

            if(rDeg> 5) SetRotation(rot_ + ((rDeg > 180) ? ph::timestep * rDeg2 : -ph::timestep * rDeg2));

            for(int i = 0; i < 8; i++) {
                sf::Vector2f v = ph::rotateVector(1.0F + sinf(ph::pi * t) * 3.0F, 0.0F, t * 360 + i * 45.0F);
                particles_.at(i)->SetPosition(x_ + v.x, y_ + v.y);
            }

        }

        Teekkari::Update();
    }

protected:
    virtual void Ability(float x, float y) {
        abilityStartTime_ = game_.GetTime();
        updCount_ = 0;
        tVelocity_ = mainBody_->GetLinearVelocity();
        tY_ = y_;
        game_.ProfessorPause();

        SoundID sounds[] = { 
            SoundID::professor_oneliner1,
            SoundID::professor_oneliner2,
            SoundID::professor_oneliner3,                                        
            SoundID::professor_oneliner4,
            SoundID::professor_oneliner5,
            SoundID::professor_oneliner6,
            SoundID::professor_oneliner7,
            SoundID::professor_oneliner8
        };

        game_.GetAudioSystem().PlaySound(sounds[rng::RandomInt(0, 7)]);
        game_.GetAudioSystem().PlaySound(SoundID::integral_destruction, 0.6F);
        game_.AddObject(std::make_unique<AbilityIntegral>(game_, x_, y_, 0.0F));

        for(int i = 0; i < 8; i++) {

            sf::Vector2f v = ph::rotateVector(1.0F, 0.0F, i * 45.0F);

            int id = game_.AddObject(std::make_unique<ProfessorParticle>(game_, x_ + v.x, y_ + v.y, 0.0F));
            ProfessorParticle& pp = (ProfessorParticle&)game_.GetObject(id);

            pp.SetSize(1.0F);
            pp.SetSprite((i % 2) ? SpriteID::gravity_symbols : SpriteID::math_cloud);
            pp.SetLifeTime(3.3F);

            particles_.push_back(&pp);
        }

    }

    float GetRealTime() {
        return abilityStartTime_ + updCount_ * ph::timestep;
    }

    bool resumed_ = false;
    int updCount_ = 0;
    float abilityStartTime_ = 0;

    b2Vec2 tVelocity_ = {0, 0};
    float tY_ = 0;

    std::vector<ProfessorParticle*> particles_;


};


#endif
