#ifndef GAME_BEER_HPP
#define GAME_BEER_HPP

#include <gameplay/Block.hpp>
#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <framework/RandomGen.hpp>
#include <gameplay/ParticleEffect.hpp>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_api.h>
#include <unordered_map>

// A block that gives a teekkari to the player when broken
class Beer : public Block {
public:

    Beer(Game& game, gm::GameObjectType type, float x, float y, float rot) : Block(game, type, x, y, rot) {}

protected:

    virtual void OnDeath() {

        game_.GetAudioSystem().PlaySound(materialData_.breakSound);
        game_.AddPoints(objectType_ == gm::GameObjectType::prop_beer ? -2000 : -1000);
        
        //Spawn some particles
        
        if(objectType_ == gm::GameObjectType::prop_beer) {
            for(int i = 0; i < 10; i++) {
                //Random point inside circle
                float a = 2.0F * ph::pi * rng::RandomF();
                float u = rng::RandomF() + rng::RandomF();
                float r = (u > 1) ? 2 - u : u;
                float x = shapeData_.height * r * cosf(a);
                float y = shapeData_.height * r * sinf(a);
                int id = game_.AddObject(std::make_unique<PhysParticle>(game_, x_ + x, y_ + y, ph::angToRot(a)));
                PhysParticle& p = (PhysParticle&)game_.GetObject(id);
                
                p.SetSize(0.25F);
                p.SetSprite(SpriteID::bottle_particle);
                p.Angular(rng::RandomInt(0, 1) ? rng::RandomF() * 0.4F : -rng::RandomF() * 0.4F);
                p.Explosion({x_, y_}, 30.0F);
            }
        }

        else {
            float a = 2.0F * ph::pi * rng::RandomF();
            int id = game_.AddObject(std::make_unique<PhysParticle>(game_, x_, y_, rot_));
            PhysParticle& p = (PhysParticle&)game_.GetObject(id);

            p.SetSize(0.25F);
            p.SetSprite(SpriteID::can_particle);
            p.Angular(rng::RandomInt(0, 1) ? rng::RandomF() * 0.4F : -rng::RandomF() * 0.4F);
            p.Impulse({0, 10.0F});
        }

        int id = game_.AddObject(std::make_unique<TextParticle>(game_, x_+0.5F, y_, 0.0F));
        TextParticle& textP = (TextParticle&)game_.GetObject(id);
        textP.SetSize(1.0F);
        textP.SetColor(sf::Color(0, 0, 0, 255));
        textP.SetText(objectType_ == gm::GameObjectType::prop_beer ? "-2000" : "-1000");


    }
};



#endif
