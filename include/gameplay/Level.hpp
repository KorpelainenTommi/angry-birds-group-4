#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <utility>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/Resources.hpp>

/// The mode this level is played at
enum LevelMode { normal, time_trial, endless };

/// A struct defining the initial state of all objects at the start of a game
struct Level {

    std::string levelName;
    LevelMode levelMode = LevelMode::normal;
    std::vector<gm::GameObjectData> objectData;
    std::vector<std::pair<std::string, int>> highscores;
    SpriteID backgroundImage = SpriteID::background_testroom;

    /// Calculate a max score by adding the point values for all objects
    int CalculateMaxScore() {
        //TODO: implement


    }


};

#endif
