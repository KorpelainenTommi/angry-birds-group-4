#ifndef TEEKKARI_HPP
#define TEEKKARI_HPP

#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/PhysObject.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/Person.hpp>
#include <box2d/b2_body.h>

class Teekkari : public Person {
public:
    Teekkari(Game& game, float x, float y, float rot, gm::PersonData data) : Teekkari(game, data.objType, x, y, rot) { data_ = data; }
    Teekkari(Game& game, gm::GameObjectType type, float x, float y, float rot) : Person(game, type, x, y, rot, false, -5)
    { data_ = gm::RandomTeekkari(type); hp_ = ph::teekkariHP; }
protected:

};

#endif