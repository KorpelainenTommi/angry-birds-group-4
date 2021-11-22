#ifndef CATAPULT_HPP
#define CATAPULT_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

/// A Block is a single body physics object with a shape and a material, that can give points when broken
class Catapult : public PhysObject {
public:

    /// Construct a catapult at this position facing right. If mirrored, it will face left
    Catapult(Game& game, float x, float y, bool mirror) : 
    PhysObject(game, type, x, y, rot), blockData_(gm::blockTypes.at(type)), shapeData_(gm::shapeProperties.at(blockData_.shape)),
    materialData_(gm::materialProperties.at(blockData_.material)) { }

    virtual void Render(const RenderSystem& r) {

    }

};



#endif