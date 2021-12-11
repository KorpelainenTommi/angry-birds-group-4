#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <utility>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/Resources.hpp>

/// @brief The mode this level is played at
enum LevelMode { normal, time_trial, endless };
inline const std::vector<std::string> levelModeNames = {"normal", "time trial", "endless"};

/// @brief A struct defining the initial state of all objects at the start of a game
struct Level {
    /// @brief Levelname
    std::string levelName = "new level";
    /// @brief Path to the level
    std::string levelPath = "";
    /// @brief Timelimit
    int timeLimit = 0;
    /// @brief Score for the prefect score
    int perfectScore = 0;
    /// @brief Level mode of the level
    LevelMode levelMode = LevelMode::normal;
    /// @brief Object data of the level
    std::vector<gm::GameObjectData> objectData;
    /// @brief Highscores
    std::vector<std::pair<std::string, int>> highscores;
    /// @brief Background image
    SpriteID backgroundImage = SpriteID::background_field;

    /// @brief Projectiles of the level
    std::vector<gm::GameObjectType> startingTeekkaris;
    
    /// @brief Get theoretical max score of the level
    int CalculateMaxScore() {

        int sum = 0;
        for(const auto& obj : objectData)
            sum += gm::GetObjectScore(obj.type);
        if(startingTeekkaris.empty()) return sum;
        else return sum + (startingTeekkaris.size()-1) * gm::GetObjectScore(gm::GameObjectType::teekkari_ik);

    }


};

#endif
