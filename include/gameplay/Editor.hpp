#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <gameplay/Game.hpp>
#include <screens/GameScreen.hpp>

/// @brief Class for the game editor
class Editor: public Game{
public:
    /// @brief Constructor
    Editor(GameScreen &s, Level level);

    /// @brief Ui uses this to report the block/element the player wants to spawn next to the level
    void SetSelectedElement(gm::GameObjectType t);
    
    /// @brief Add the projectile to starting projectile list and call GameScreen::UpdateProjectileList()
    void AddProjectile(gm::GameObjectType t);
    
    /// @brief Remove the element at the given idex in projectile list and call GameScreen::UpdateProjectileList()
    void RemoveProjectile(std::size_t index);
    
    /// @brief Resume to the game and activate physics
    virtual void Resume();
    
    /// @brief Restart the game and deactive physics
    virtual void Restart();
    
    /// @brief Returns if playmode is active
    bool InPlayMode() const;

    /// @brief Receive mouse events from the user
    virtual bool OnMouseMove(float xw, float yh);
    /// @brief Receive mouse events from the user
    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);
    /// @brief Receive mouse events from the user
    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);
    /// @brief Receive keyboard events from the user
    virtual bool OnKeyDown(const sf::Event::KeyEvent&);

    /// @brief Activate game
    void Play();
    
    /// @brief Get level
    Level& GetLevel();
    
    /// @brief Save changes to the level stored in the game object
    void SaveLevel();

    /// @brief Determines if it is editor. Returns always true
    virtual bool IsEditor() const { return true; }    
    
private:
    gm::GameObjectType selectedElement_;
    int dragObjectID_ = -1;
    ph::tfloat dragX_;
    ph::tfloat dragY_;

    bool playMode_ = false;

};

#endif
