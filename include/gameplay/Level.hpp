#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <utility>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/Resources.hpp>


enum LevelMode { normal, time_trial, endless };

struct Level {

    std::string levelName;
    LevelMode levelMode;
    std::vector<gm::GameObjectData> objectData;
    std::vector<std::pair<std::string, int>> highscores;
    SpriteID backgroundImage;

    int CalculateMaxScore() {

        

    }


};

#endif
