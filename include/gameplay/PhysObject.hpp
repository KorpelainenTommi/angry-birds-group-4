#ifndef PHYS_OBJECT_HPP
#define PHYS_OBJECT_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/GameObject.hpp>

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_contact.h>

/// An object that has one or more rigidbodies. Can be affected with forces and other PhysObjects
class PhysObject : public GameObject {
public:

    PhysObject(Game& game, gm::GameObjectType objectID, float x, float y, float rot) : 
    GameObject(game, objectID, x, y, rot) { }

    /// Destroy underlying rigidbodies with b2dWorld.DestroyBody()
    virtual ~PhysObject();

    /// Update this GameObjects position to reflect the state in the box2d world
    virtual void Update();

    /// OnCollision is called when this PhysObject collides with another PhysObject
    virtual void OnCollision(const b2Vec2& relativeVelocity, PhysObject& other, const b2Contact& contact);

    /// Set this rigidbody's x
    virtual void SetX(float x);

    /// Set this rigidbody's y
    virtual void SetY(float y);

    /// Set this rigidbody's rotation
    virtual void SetRotation(float rot);

    /// Set this rigidbody's position
    virtual void SetPosition(float x, float y);

    /// Instant change in velocity
    virtual void Impulse(const b2Vec2& f);

    /// Instant change in velocity at point p
    virtual void Impulse(const b2Vec2& f, const b2Vec2& p);

    /// Force over time
    virtual void Force(const b2Vec2& f);

    /// Force over time at point p
    virtual void Force(const b2Vec2& f, const b2Vec2& p);

    /// Torque over time
    virtual void Torque(float t);

    /// Instant change in angular velocity
    virtual void Angular(float a);

    /// Add explosive force away from center
    virtual void Explosion(const b2Vec2& center, float magnitude);

    /// Explicitly deal damage to this objects hp
    virtual void DealDamage(float damage);

    virtual float GetHP() const;
    virtual float GetMass() const;



protected:

    /// This is the main (root) box2d body. Objects can have subparts such as bodies connected by joints
    b2Body* mainBody_;
    float hp_ = 0;


    /// This is called just before this object is destroyed from hp
    virtual void OnDeath() { }
};


#endif