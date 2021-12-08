#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <gameplay/Game.hpp>

class Editor: public Game{
public:
    Editor(GameScreen &s, Level level): Game(s, level){}

    void SetSelectedElement(gm::GameObjectType t){
        std::cout << "selected " << t << std::endl;
    }

    void AddProjectile(SpriteID icon){
        std::cout << "added " << icon << std::endl;
    }

    void RemoveProjectile(std::size_t index){
        std::cout << "removed " << index << std::endl;
    }
};

#endif