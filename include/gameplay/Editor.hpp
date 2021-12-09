#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <gameplay/Game.hpp>
#include <screens/GameScreen.hpp>

class Editor: public Game{
public:
    Editor(GameScreen &s, Level level);

    /// ui uses this to report the block/element the player wants to spawn next to the level
    void SetSelectedElement(gm::GameObjectType t);
    
    /// add the projectile to starting projectile list and call GameScreen::UpdateProjectileList()
    void AddProjectile(gm::GameObjectType t);
    
    /// remove the element at the given idex in projectile list and call GameScreen::UpdateProjectileList()

    void RemoveProjectile(std::size_t index);
    
    
    virtual bool OnMouseMove(float xw, float yh);
    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);
    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);
    
    Level GetLevel() const;
    
    void SaveLevel();
    
private:
    gm::GameObjectType selectedElement_;
    int dragObjectID_ = -1;
    ph::tfloat dragX_;
    ph::tfloat dragY_;

};

#endif
