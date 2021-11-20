#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <UpdateListener.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/GameObjectTypes.hpp>

//TODO:
//-add const getters for protected variables
//-add SetPosition and SetRotation

//Forward declaration for RenderSystem

class GameObject : public UpdateListener {
public:
    
    GameObject(const ph::tfloat& x, const ph::tfloat& y, const ph::tfloat& rot) : 
    x_(x), y_(y), rot_(rot) {}

    virtual ~GameObject() = default;

    //Call record on all tfloats
    virtual void Record() {
        x_.Record();
        y_.Record();
        rot_.Record();
    }

    virtual void Render(const RenderSystem&) = 0;

protected:
    ph::tfloat x_;
    ph::tfloat y_;
    ph::tfloat rot_;
    GameObjectID objectID_; //Object type
    int gameID_;            //Object instance
};


#endif