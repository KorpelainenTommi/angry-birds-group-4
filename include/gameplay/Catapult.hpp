#ifndef CATAPULT_HPP
#define CATAPULT_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>


/// A Catapult consists of base that is a static rigidbody, and a lever that is a dynamic rigidbody
class Catapult : public PhysObject {
public:

    /// Construct a catapult at this position facing right
    Catapult(Game& game, float x, float y) : 
    PhysObject(game, gm::GameObjectType::catapult, x, y, 0) { }


    /// 
    virtual void Render(const RenderSystem& r) {

    }

};



#endif