#ifndef FUKSI_HPP
#define FUKSI_HPP

#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/PhysObject.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/Person.hpp>
#include <box2d/b2_body.h>

class Fuksi : public Person {
public:
    Fuksi(Game& game, float x, float y, float rot) : Person(game, gm::GameObjectType::fuksi, x, y, rot, true, -6) {}

protected:
    


private:

};


#endif