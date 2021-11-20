#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include <utility>
#include <framework/Resources.hpp>

//Max score calculation shouldn't be saved in level files
//That would mean old levels would have incorrect max scores
//if the max score formula is ever changed

struct Level {

    std::string levelName;
    std::vector<int> objectData;
    std::vector<std::pair<std::string, int>> highscores;
    SpriteID backgroundImage;

};

#endif
