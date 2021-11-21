#ifndef PHYS_OBJECT_HPP
#define PHYS_OBJECT_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/GameObject.hpp>
#include <box2d/b2_body.h>


class PhysObject : public GameObject {
public:
    PhysObject(Game& game, gm::GameObjectID objectID, float x, float y, float rot) : 
    GameObject(game, objectID, x, y, rot) {}

protected:
    std::unique_ptr<b2Body> body;
};


#endif