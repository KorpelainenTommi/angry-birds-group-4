#ifndef GAME_BLOCK_HPP
#define GAME_BLOCK_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

/// A Block is a single body physics object with a shape and a material, that can give points when broken
class Block : public PhysObject {
public:

    /// Construct a Block identified by this GameObjectType. It is assumed the type is a valid block
    Block(Game& game, gm::GameObjectType type, float x, float y, float rot);

    /// Render this block
    virtual void Render(const RenderSystem& r);

    /// Do additional things when colliding
    virtual void OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact);
    
    virtual std::vector<sf::Sprite> GetSprites(const RenderSystem& r);
    virtual bool CheckIntersection(sf::Sprite s, const RenderSystem& r);

protected:
    gm::BlockData blockData_;
    gm::BlockShapeData shapeData_;
    gm::BlockMaterialData materialData_;
    float lastHitSound_ = 0.0F;

    virtual void OnDeath();
};



#endif
