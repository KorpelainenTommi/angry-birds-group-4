#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include <screens/Screen.hpp>
#include <SFML/Graphics.hpp>
#include <framework/FileManager.hpp>
#include <framework/ResourceManager.hpp>
#include <framework/RenderSystem.hpp>
#include <framework/AudioSystem.hpp>


class Screen;

/// @brief The top level object of an instance

class Application {
public:

    /// @brief Construct a fullscreen application and activate the first screen
    Application();

    /// @brief Game, event and renderloop
    bool Loop();

    /// @brief Transition to screen, and make it active. The old screen is destroyed.
    void TransitionTo(std::unique_ptr<Screen>);

    /// @brief Resize the window
    void Resize(unsigned int width, unsigned int height);

    /// @brief Go fullscreen
    void Fullscreen();

    /// @brief Close the application
    void Exit();


    // These are here in case someone absolutely needs them
    
    /// @brief Get aspectratio
    float GetAspectRatio() const;
    
    /// @brief Get window width
    float GetWindowWidth() const;
    
    /// @brief Get window height
    float GetWindowHeight() const;
    
    /// @brief  Get if it is Fullscreen
    bool IsFullScreen() const;

    /// @brief Get explicit access to Audiosystem
    AudioSystem& GetAudioSystem();
    
    /// @brief Get explicit access to Filemanager
    const FileManager& GetFileManager() const;
    
    /// @brief Get explicit access to RenderSystem
    const RenderSystem& GetRenderSystem() const;
    
    /// @brief Get explicit access to RescourceManager
    const ResourceManager& GetResourceManager() const;



private:

    //Time stuff
    sf::Clock clock;
    float accumulatedTime = 0;
    bool isFullScreen_ = true;

    sf::RenderWindow window_;
    std::unique_ptr<Screen> activeScreen_;

    FileManager fileManager_;
    AudioSystem audioSystem_;
    RenderSystem renderSystem_;
    ResourceManager resourceManager_;

    void UpdateView();

};



#endif
