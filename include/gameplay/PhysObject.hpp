#ifndef PHYS_OBJECT_HPP
#define PHYS_OBJECT_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/GameObject.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

/// An object that has one or more rigidbodies. Can be affected with forces and other PhysObjects
class PhysObject : public GameObject {
public:

    PhysObject(Game& game, gm::GameObjectType objectID, float x, float y, float rot) : 
    GameObject(game, objectID, x, y, rot) { }

    virtual ~PhysObject() = default;

    /// Update this objects position to reflect the state in the box2d world
    virtual void Update();

    /// Set this rigidbody's x
    virtual void SetX(float x);

    /// Set this rigidbody's y
    virtual void SetY(float y);

    /// Set this rigidbody's rotation
    virtual void SetRotation(float rot);

    /// Set this rigidbody's position
    virtual void SetPosition(float x, float y);

    /// Instant change in velocity
    virtual void Impulse(b2Vec2 f) { mainBody_->ApplyLinearImpulseToCenter(f, true);}

    /// Instant change in velocity at point p
    virtual void Impulse(b2Vec2 f, b2Vec2 p) { mainBody_->ApplyLinearImpulse(f, p, true);}

    /// Force over time
    virtual void Force(b2Vec2 f) { mainBody_->ApplyForceToCenter(f, true); }

    /// Force over time at point p
    virtual void Force(b2Vec2 f, b2Vec2 p) { mainBody_->ApplyForce(f, p, true); }



protected:

    // This is the main (root) box2d body. Objects can have subparts such as bodies connected by joints
    std::unique_ptr<b2Body> mainBody_;
};


#endif