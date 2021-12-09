#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <UpdateListener.hpp>
#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/GameObjectTypes.hpp>

/// Base class for gameobjects
class GameObject : public UpdateListener {
public:
    
    /// Initialize an empty gameobject
    GameObject();

    /// Initialize base gameobject information
    GameObject(Game& game, gm::GameObjectType objectType, float x, float y, float rot) : 
    game_(game), objectType_(objectType), x_(x), y_(y), rot_(rot) {}

    virtual ~GameObject() = default;

    /// Call record on all tfloats
    virtual void Record() {
        x_.Record();
        y_.Record();
        rot_.Record();
    }

    //Important that these are virtual.
    //For example, PhysObject derives these to set its underlying rigidbody position

    /// Set this gameobject's x
    virtual void SetX(float x) { x_ = x; }

    /// Set this gameobject's y
    virtual void SetY(float y) { y_ = y; }

    /// Set this gameobject's rotation
    virtual void SetRotation(float rot) { rot_ = rot; }

    /// Set this gameobject's position
    virtual void SetPosition(float x, float y) { this->SetX(x); this->SetY(y); }


    virtual ph::tfloat GetX() const { return x_; }
    virtual ph::tfloat GetY() const { return y_; }
    virtual ph::tfloat GetRot() const { return rot_; }
    gm::GameObjectType GetObjectType() const { return objectType_; }


    virtual void Render(const RenderSystem&) = 0;

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