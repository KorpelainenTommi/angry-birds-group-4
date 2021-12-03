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
    level.objectData.push_back({-20,0,0,gm::cannon});
    level.objectData.push_back({15,0.5,0,gm::block_wood1x1});
    level.objectData.push_back({15,1.5,0,gm::block_wood1x1});
    level.objectData.push_back({15,2.5,0,gm::block_wood1x1});
    level.objectData.push_back({15,3.5,0,gm::block_wood1x1});
    level.objectData.push_back({15,4.5,0,gm::block_wood1x1});
    level.highscores.push_back({"player1", 123456});
    level.highscores.push_back({"player2", 56});
    return level;
}



#endif
