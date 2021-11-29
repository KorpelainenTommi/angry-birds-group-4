#ifndef TESTLEVEL_HPP
#define TESTLEVEL_HPP

#include <vector>
#include <string>
#include <utility>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/Resources.hpp>
#include <gameplay/Level.hpp>



Level TestLevel() {
    Level level = {};
    level.levelName = "TESTLEVEL";
    level.objectData.push_back({0,0,0,gm::block_wood1x1});
    return level;
}



#endif
