#ifndef FUKSI_HPP
#define FUKSI_HPP

#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/ParticleEffect.hpp>
#include <gameplay/PhysObject.hpp>
#include <gameplay/Physics.hpp>
#include <gameplay/Person.hpp>
#include <box2d/b2_body.h>
#include <memory>

/// @brief Enemyclass
class Fuksi : public Person {
public:
    /// @brief Constructor
    Fuksi(Game& game, float x, float y, float rot, gm::PersonData data) : Fuksi(game, x, y, rot) { data_ = data; }
    Fuksi(Game& game, float x, float y, float rot) : Person(game, gm::GameObjectType::fuksi, x, y, rot, true, -6)
    { data_ = gm::RandomFuksi(); hp_ = ph::fuksiHP; }

protected:
    /// @brief Increments points and other things  on death. 
    virtual void OnDeath() {
        //Spawn points effect
        int points = gm::GetObjectScore(objectType_);
        int id = game_.AddObject(std::make_unique<TextParticle>(game_, x_, y_, 0.0F));
        TextParticle& textP = (TextParticle&)game_.GetObject(id);
        textP.SetSize(1.0F);
        textP.SetColor(sf::Color(0, 0, 255, 255));
        std::stringstream ss;
        ss << points;
        textP.SetText(ss.str());

        game_.AddPoints(gm::GetObjectScore(gm::GameObjectType::fuksi));
    }

private:

};


#endif
