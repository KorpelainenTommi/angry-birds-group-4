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
    level.objectData.push_back({0,0,0,gm::cannon});
    level.highscores.push_back({"player1", 123456});
    level.highscores.push_back({"player2", 56});
    return level;
}



#endif
