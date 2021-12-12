#ifndef GAME_TERRAIN_HPP
#define GAME_TERRAIN_HPP

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
#include <limits>

///@brief An inmovable, indestructible block
class Terrain : public Block {
public:
/// @brief Constructor
    Terrain(Game& game, float x, float y, float rot) : Block(game, gm::GameObjectType::terrain1x1, x, y, rot) {
        mainBody_->SetGravityScale(0);
        mainBody_->SetType(b2BodyType::b2_staticBody);
        hp_ = std::numeric_limits<float>::infinity();
    }

    virtual float GetMass() const { return ph::groundMass; }

    /// @brief Empty method removes ability to take damage
    virtual void DealDamage(float damage) { }





};



#endif