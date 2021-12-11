#ifndef GAME_BLOCK_HPP
#define GAME_BLOCK_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

/// @brief A Block is a single body physics object with a shape and a material, that can give points when broken
class Block : public PhysObject {
public:

    /// @brief Construct a Block identified by this GameObjectType. It is assumed the type is a valid block
    Block(Game& game, gm::GameObjectType type, float x, float y, float rot);

    ///@brief  Render this block
    virtual void Render(const RenderSystem& r);

    /// @brief Do additional things when colliding
    virtual void OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact);
    
    /// @brief Get all sprites of a block
    virtual std::vector<sf::Sprite> GetSprites(const RenderSystem& r);
    
    /// @brief Check intersection with another sprite
    virtual bool CheckIntersection(sf::Sprite s, const RenderSystem& r);

    /// @brief Get b2bodies
    virtual std::vector<b2Body*> GetPhysBodies();
    
    /// @brief Check intersection with other b2body
    virtual bool CheckIntersection(b2Body* other);
    
    /// @brief Get block material
    const gm::BlockMaterial GetBlockMaterial() const;
    
    /// @brief Check if electricity can flow from another block to this block
    bool ElectricityCheck(Block& block);
    

protected:
    gm::BlockData blockData_;
    gm::BlockShapeData shapeData_;
    gm::BlockMaterialData materialData_;
    float lastHitSound_ = 0.0F;

    virtual void OnDeath();
};



#endif
