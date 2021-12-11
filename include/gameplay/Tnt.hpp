#ifndef GAME_TNT_HPP
#define GAME_TNT_HPP

#include <gameplay/Block.hpp>
#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <framework/RandomGen.hpp>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_api.h>

/// A block that explodes
class Tnt : public Block {
public:

    Tnt(Game& game, float x, float y, float rot) : Block(game, gm::GameObjectType::prop_tnt, x, y, rot) {}

protected:
    virtual void OnDeath() {
        
        Block::OnDeath();
        auto objs = game_.GetObjects();

        b2CircleShape circle;
        circle.m_radius = 5.0F;

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
                    phys->ExplosionDamage({x_, y_}, 100 + phys->GetMass() * 5);
                    phys->Explosion({x_, y_}, phys->GetMass() * 100.0F);
                }
            }
        }

        game_.GetAudioSystem().PlaySound(rng::RandomInt(0, 1) ? SoundID::tnt_explode1 : SoundID::tnt_explode2);
        game_.AddObject(std::make_unique<Effect>(game_, AnimationID::explosion,
        x_, y_, 0.0F, 4.0F, 60.0F, 0.35F));


    }
};



#endif
