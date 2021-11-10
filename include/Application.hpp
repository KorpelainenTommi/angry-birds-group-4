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

    /// Transition to a screen and make it active. The old screen is destroyed
    void TransitionTo(std::unique_ptr<Screen>);

    /// Resize the window
    void Resize(unsigned int width, unsigned int height);

    /// Go fullscreen
    void Fullscreen();


private:

    sf::RenderWindow window_;
    std::unique_ptr<Screen> activeScreen_;

    FileManager fileManager_;
    AudioSystem audioSystem_;
    RenderSystem renderSystem_;
    ResourceManager resourceManager_;

};



#endif