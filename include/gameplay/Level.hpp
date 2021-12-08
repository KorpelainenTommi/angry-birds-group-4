#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <utility>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/Resources.hpp>

/// The mode this level is played at
enum LevelMode { normal, time_trial, endless };
inline const std::vector<std::string> levelModeNames = {"normal", "time trial", "endless"};

/// A struct defining the initial state of all objects at the start of a game
struct Level {

    std::string levelName = "new level";
    std::string levelPath = "";
    LevelMode levelMode = LevelMode::normal;
    std::vector<gm::GameObjectData> objectData;
    std::vector<std::pair<std::string, int>> highscores;
    SpriteID backgroundImage = SpriteID::background_testroom;

    std::vector<gm::GameObjectType> startingTeekkaris;
    
    int CalculateMaxScore() {

        int sum = 0;
        for(const auto& obj : objectData)
            sum += gm::GetObjectScore(obj.type);
        return sum;

    }


};

#endif
