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
    virtual void OnDeath() { game_.CheckLevelEnd(); }

};


class IKTeekkari : public Teekkari {

};

class SIKTeekkari : public Teekkari {

};

class TEFYTeekkari : public Teekkari {

};

class TUTATeekkari : public Teekkari {

};

class TIKTeekkari : public Teekkari {

};

class INKUBIOTeekkari : public Teekkari {

};

class KIKTeekkari : public Teekkari {

};

class Professor : public Teekkari {

};


#endif