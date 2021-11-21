#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/Level.hpp>
#include <screens/Screen.hpp>

class GameScreen : public Screen {
public:

    /// Create a screen with an empty Game
    GameScreen(Application& app) : Screen(app), game_(*this) { }

    /// Create a screen and start the Game with the selected level
    GameScreen(Application& app, const Level& initialLevel) : Screen(app), game_(*this, initialLevel) {}

    virtual ~GameScreen() = default;

protected:
    Game game_;

};


#endif