#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <gameplay/Game.hpp>

class Editor: public Game{
public:
    Editor(GameScreen &s, Level level): Game(s, level){}

    void SetSelectedElement(gm::GameObjectType t){
        std::cout << "selected " << t << std::endl;
    }
};

#endif