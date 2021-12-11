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

/// @brief Class for objects that have one or more rigidbodies. Can be affected with forces and other PhysObjects
class PhysObject : public GameObject {
public:
    /// @brief Constructor
    PhysObject(Game& game, gm::GameObjectType objectID, float x, float y, float rot) : 
    GameObject(game, objectID, x, y, rot) { }

    /// @brief Destroy underlying rigidbodies with b2dWorld.DestroyBody()
    virtual ~PhysObject();

    /// @brief Update this GameObjects position to reflect the state in the box2d world
    virtual void Update();

    /// @brief OnCollision is called when this PhysObject collides with another PhysObject
    virtual void OnCollision(const b2Vec2& relativeVelocity, PhysObject& other, const b2Contact& contact);

    /// @brief Set this rigidbody's x
    virtual void SetX(float x);

    /// @brief Set this rigidbody's y
    virtual void SetY(float y);

    /// @brief Set this rigidbody's rotation
    virtual void SetRotation(float rot);

    /// @brief Set this rigidbody's position
    virtual void SetPosition(float x, float y);

    /// @brief Instant change in velocity
    virtual void Impulse(const b2Vec2& f);

    /// @brief Instant change in velocity at point p
    virtual void Impulse(const b2Vec2& f, const b2Vec2& p);

    /// @brief Force over time
    virtual void Force(const b2Vec2& f);

    /// @brief Force over time at point p
    virtual void Force(const b2Vec2& f, const b2Vec2& p);

    /// @brief Torque over time
    virtual void Torque(float t);

    /// @brief Instant change in angular velocity
    virtual void Angular(float a);

    /// @brief Add explosive force away from center
    virtual void Explosion(const b2Vec2& center, float magnitude);
    
    /// @brief Deal explosive damage, that decays with distance
    void ExplosionDamage(const b2Vec2& center, float damage);

    /// @brief Explicitly deal damage to this objects hp
    virtual void DealDamage(float damage);

    /// @brief Get HP
    virtual float GetHP() const;
    /// @brief Get mass
    virtual float GetMass() const;

    virtual bool ContainsCoordinates(sf::Vector2f mouseCoords, const RenderSystem& r);
    virtual std::vector<b2Body*> GetPhysBodies();
    virtual bool CheckIntersection(b2Body* other);



protected:

    /// This is the main (root) box2d body. Objects can have subparts such as bodies connected by joints
    b2Body* mainBody_;
    float hp_ = 0;


    /// This is called just before this object is destroyed from hp
    virtual void OnDeath() { }

    SpriteID hitSp_ = SpriteID::hit_stars;
    b2Vec2 hitPoint_ = {0, 0};
    bool spawnHit_ = false;

};


#endif
