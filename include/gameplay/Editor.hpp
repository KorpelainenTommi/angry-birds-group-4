#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <gameplay/Game.hpp>

class Editor: public Game{
public:
    Editor(GameScreen &s, Level level): Game(s, level) {
        Pause();
    }

    /// ui uses this to report the block/element the player wants to spawn next to the level
    void SetSelectedElement(gm::GameObjectType t){
        std::cout << "selected " << t << std::endl;
    }

    /// add the projectile to starting projectile list and call GameScreen::UpdateProjectileList()
    void AddProjectile(gm::GameObjectType t){
        std::cout << "added " << t << std::endl;
    }

    /// remove the element at the given idex in projectile list and call GameScreen::UpdateProjectileList()
    void RemoveProjectile(std::size_t index){
        std::cout << "removed " << index << std::endl;
    }

    Level GetLevel() const {return level_;}
};

#endif