#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <UpdateListener.hpp>
#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <box2d/b2_body.h>
#include <vector>
/// @brief Base class for GameObjects
class GameObject : public UpdateListener {
public:
    
    /// @brief Initialize an empty gameobject
    GameObject();

    /// @brief Initialize base gameobject information
    GameObject(Game& game, gm::GameObjectType objectType, float x, float y, float rot) : 
    game_(game), objectType_(objectType), x_(x), y_(y), rot_(rot) {}
    
    /// @brief Desttructor
    virtual ~GameObject() = default;

    /// @brief Call record on all tfloats
    virtual void Record() {
        x_.Record();
        y_.Record();
        rot_.Record();
    }

    //Important that these are virtual.
    //For example, PhysObject derives these to set its underlying rigidbody position

    /// @brief Set this gameobject's x
    virtual void SetX(float x) { x_ = x; }

    /// @brief Set this gameobject's y
    virtual void SetY(float y) { y_ = y; }

    /// @brief Set this gameobject's rotation
    virtual void SetRotation(float rot) { rot_ = rot; }

    /// @brief Set this gameobject's position
    virtual void SetPosition(float x, float y) { this->SetX(x); this->SetY(y); }

    /// @brief Get x coordinate
    virtual ph::tfloat GetX() const { return x_; }
    
    /// @brief Get y coordinate
    virtual ph::tfloat GetY() const { return y_; }
    
    /// @brief Get rotation
    virtual ph::tfloat GetRot() const { return rot_; }
    
    /// @brief Get object type
    gm::GameObjectType GetObjectType() const { return objectType_; }
    
    /// @brief Get gameID
    int GetGameID() const { return gameID_; }
    
    /// @brief Renders the object. Pure virtual function.
    virtual void Render(const RenderSystem&) = 0;
    
    /// @brief Get Sprites of the object for collision test. Default an empty vector.
    virtual std::vector<sf::Sprite> GetSprites(const RenderSystem& r) { return std::vector<sf::Sprite>(); }
    
    /// @brief Check intersection of this object and a sprite. Default false
    virtual bool CheckIntersection(sf::Sprite s, const RenderSystem& r) { return false; }
    
    /// @brief Check if the object contains given relative coordinates. Default false.
    virtual bool ContainsCoordinates(sf::Vector2f mouseCoords, const RenderSystem& r) { return false; }
    /// @brief Get b2bodies of the object
    virtual std::vector<b2Body*> GetPhysBodies() { return std::vector<b2Body*>(); }
    /// @brief Check intersection with another b2body
    virtual bool CheckIntersection(b2Body* other) { return false; }

protected:

    //Allow Game to modify gameID_ when taking ownership of an object
    friend class Game;

    Game& game_;
    ph::tfloat x_;
    ph::tfloat y_;
    ph::tfloat rot_;
    gm::GameObjectType objectType_; //Object type
    int gameID_ = -1;               //Object id
};


#endif
