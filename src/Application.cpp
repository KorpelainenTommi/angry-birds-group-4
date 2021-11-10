#include <Application.hpp>
#include <ui/UIConstants.hpp>
#include <screens/DemoScreen.hpp>



void Application::TransitionTo(std::unique_ptr<Screen> screen) {
    activeScreen_ = std::move(screen);
}

void Application::Fullscreen() {
    
    const auto& available = sf::VideoMode::getFullscreenModes();
    if(available.size() > 0) window_.create(available[0], ui::AppName, sf::Style::Fullscreen);
    else window_.create(sf::VideoMode::getDesktopMode(), ui::AppName, sf::Style::Fullscreen);

    renderSystem_.WW = window_.getView().getSize().x;
    renderSystem_.HH = window_.getView().getSize().y;

}

void Application::Resize(unsigned int width, unsigned int height) {
    
    //Recreating the window with an appropriate videomode instead of setSize prevents stretched text etc.
    //w.setSize({sz.width, sz.height});

    //Update rendersystem values for screen size, since rendersystem cannot know when these values change
    //Otherwise, getView copies a view every frame for every draw call

    window_.create(sf::VideoMode(width, height), ui::AppName);
    renderSystem_.WW = window_.getView().getSize().x;
    renderSystem_.HH = window_.getView().getSize().y;

}

Application::Application() : resourceManager_(fileManager_), renderSystem_(window_, resourceManager_) {

    //Create fullscreen window
    Fullscreen();
    window_.setVerticalSyncEnabled(false);
    window_.setFramerateLimit(150); //This will probably get turned to a constant

    //switch to resizable for debugging different window sizes
    Resize(800, 800);
    
    TransitionTo(std::make_unique<DemoScreen>());
}




bool Application::Loop() {

    sf::Event event;
    while(window_.pollEvent(event)) {
        if(event.type == sf::Event::Closed) window_.close();
        if(event.type == sf::Event::Resized) Resize(event.size.width, event.size.height);

        if(event.type == sf::Event::KeyPressed) activeScreen_->OnKeyDown(event.key);
        if(event.type == sf::Event::KeyReleased) activeScreen_->OnKeyUp(event.key);
        if(event.type == sf::Event::MouseMoved) activeScreen_->OnMouseMove(event.mouseMove);
        if(event.type == sf::Event::TextEntered) activeScreen_->OnTextEntered(event.text);

    }


    //TODO: Update should be a fixed timestep event that is called eg. 60 times a second.
    //Update should be independent of framerate, which it currently isn't


    activeScreen_->Update();
    
    
    //Gray color
    window_.clear({128, 128, 128, 255});
    activeScreen_->Render(renderSystem_);
    window_.display();


    return window_.isOpen();

}