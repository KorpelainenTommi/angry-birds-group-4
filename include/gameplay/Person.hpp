#ifndef PERSON_HPP
#define PERSON_HPP

#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/PhysObject.hpp>
#include <gameplay/Physics.hpp>
#include <box2d/b2_body.h>

/// @brief Physics ragdoll that can be used for humanlike objects
class Person : public PhysObject {
public:

    /// @brief Constructor. The person will point right. If mirrored = true, it will point to the left
    Person(Game& game, gm::GameObjectType type, float x, float y, float rot, bool mirrored = false, int collisionGroup = -5);
    
    /// @brief Destructor for person
    virtual ~Person();

    /// @brief Renders the person
    virtual void Render(const RenderSystem& r);
    
    /// @brief Returns mass of the person
    virtual float GetMass() const;
    /// @brief Records all tfloats
    virtual void Record();
    
    /// @brief Updates rigidbody
    virtual void Update();
    
    /// @brief Set x coordinate
    virtual void SetX(float x);
    
    /// @brief Set y coordinate
    virtual void SetY(float y);

    /// @brief Set pos
    virtual void SetPosition(float x, float y);

    /// @brief Set rotation
    virtual void SetRotation(float rot);

    
    //SetPosition is same as GameObject::SetPosition

    /// @brief Handles the collision between itself and another physobject
    virtual void OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact);
    /// @brief Creates an impulse
    virtual void Impulse(const b2Vec2& f);

    virtual bool ContainsCoordinates(sf::Vector2f mouseCoords, const RenderSystem& r);
    virtual std::vector<sf::Sprite> GetSprites(const RenderSystem& r);
    virtual bool CheckIntersection(sf::Sprite s, const RenderSystem& r);

    virtual std::vector<b2Body*> GetPhysBodies();
    virtual bool CheckIntersection(b2Body* other);

protected:

    // Data defining the look and sound of this person
    gm::PersonData data_;

    float lastHitSound_ = 0.0F;

    inline static const float restitution = 0.3F;

    inline static const float totalHeight = ph::personHeight;
    inline static const float legHeight = 0.23913F * Person::totalHeight;
    inline static const float armHeight = 1.13207F * Person::legHeight;
    inline static const float torsoHeight = 1.47169F * Person::legHeight;
    inline static const float headHeight = 2.064150F * Person::legHeight;

    inline static const float torsoWidth = 0.8333F * Person::torsoHeight;
    inline static const float legWidth = 0.6415F * Person::legHeight;
    inline static const float armWidth = 0.56666F * Person::armHeight;
    inline static const float headWidth = 0.89166F * Person::headHeight;

    inline static const float torsoVolume = Person::torsoWidth * Person::torsoHeight;
    inline static const float legVolume = Person::legWidth * Person::legHeight;
    inline static const float armVolume = Person::armWidth * Person::armHeight;
    inline static const float headVolume = 0.25F * Person::headHeight * Person::headHeight * ph::pi;

    inline static const float totalVolume = Person::torsoVolume + 2 * Person::legVolume + 2 * Person::armVolume + Person::headVolume;

    b2Body* headBody_;
    b2Body* armRBody_;
    b2Body* armLBody_;
    b2Body* legRBody_;
    b2Body* legLBody_;

    ph::tfloat headX_;
    ph::tfloat headY_;
    ph::tfloat headRot_;

    ph::tfloat armRX_;
    ph::tfloat armRY_;
    ph::tfloat armRRot_;

    ph::tfloat armLX_;
    ph::tfloat armLY_;
    ph::tfloat armLRot_;            

    ph::tfloat legRX_;
    ph::tfloat legRY_;
    ph::tfloat legRRot_;

    ph::tfloat legLX_;
    ph::tfloat legLY_;
    ph::tfloat legLRot_;


};

#endif
