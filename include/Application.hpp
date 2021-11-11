#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include <framework.hpp>
#include <screens/Screen.hpp>
#include <SFML/Graphics.hpp>


class Application {
public:

    /// Construct a fullscreen application and activate the first screen
    Application();

    /// Game, event and renderloop
    bool Loop();

    /// Transition to screen, and make it active. The old screen is destroyed.
    void TransitionTo(std::unique_ptr<Screen>);

    /// Resize the window
    void Resize(unsigned int width, unsigned int height);

    /// Go fullscreen
    void Fullscreen();

    /// Close the application
    void Exit();


    /// These are here in case someone absolutely needs them
    float GetAspectRatio() const;
    float GetWindowWidth() const;
    float GetWindowHeight() const;

    /// Get explicit access to systems
    const FileManager& GetFileManager() const;
    const AudioSystem& GetAudioSystem() const;
    const RenderSystem& GetRenderSystem() const;
    const ResourceManager& GetResourceManager() const;



private:

    //Time stuff
    sf::Clock clock;
    float accumulatedTime;


    sf::RenderWindow window_;
    std::unique_ptr<Screen> activeScreen_;

    FileManager fileManager_;
    AudioSystem audioSystem_;
    RenderSystem renderSystem_;
    ResourceManager resourceManager_;

};



#endif