#ifndef CATAPULT_HPP
#define CATAPULT_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>


/// A Cannon always aims at the mouse cursor. The launch force is based on cursor distance to the cannon
class Cannon : public PhysObject {
public:

    /// Construct a cannon at this position facing right
    Cannon(Game& game, float x, float y) : 
    PhysObject(game, gm::GameObjectType::cannon, x, y, 0) { }


    /// 
    virtual void Render(const RenderSystem& r) {

    }

};



#endif