#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <UpdateListener.hpp>
#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/GameObjectTypes.hpp>

//TODO:
//-add const getters for protected variables
//-add SetPosition and SetRotation


class GameObject : public UpdateListener {
public:
    
    /// Empty gameobject
    GameObject();

    GameObject(Game& game, gm::GameObjectID objectID, float x, float y, float rot) : 
    game_(game), objectID_(objectID), x_(x), y_(y), rot_(rot) {}

    virtual ~GameObject() = default;

    //Call record on all tfloats
    virtual void Record() {
        x_.Record();
        y_.Record();
        rot_.Record();
    }

    virtual void Render(const RenderSystem&) = 0;

protected:

    //Allow Game to e.g modify gameID_ when taking ownership of an object
    friend class Game;

    Game& game_;
    ph::tfloat x_;
    ph::tfloat y_;
    ph::tfloat rot_;
    gm::GameObjectID objectID_; //Object type
    int gameID_ = -1;           //Object instance
};


#endif