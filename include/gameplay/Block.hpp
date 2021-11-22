#ifndef GAME_BLOCK_HPP
#define GAME_BLOCK_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

/// A Block is a single body physics object with a shape and a material, that can give points when broken
class Block : public PhysObject {
public:

    /// Construct a Block identified by this GameObjectType. It is assumed the type is a valid block
    Block(Game& game, gm::GameObjectType type, float x, float y, float rot) : 
    PhysObject(game, type, x, y, rot), blockData_(gm::blockTypes.at(type)), shapeData_(gm::shapeProperties.at(blockData_.shape)),
    materialData_(gm::materialProperties.at(blockData_.material)) { }

    virtual void Render(const RenderSystem& r) {

    }

private:
    gm::BlockData blockData_;
    gm::BlockShapeData shapeData_;
    gm::BlockMaterialData materialData_;

};



#endif