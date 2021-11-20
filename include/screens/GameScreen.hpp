#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/Level.hpp>
#include <screens/Screen.hpp>

class GameScreen : public Screen {
public:

    //Create a 
    GameScreen() {}

    GameScreen(const Level&) {


    }

private:
    Game game;

};


#endif