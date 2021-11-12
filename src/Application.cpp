#include <math.h>
#include <Application.hpp>
#include <ui/UIConstants.hpp>
#include <screens/DemoScreen.hpp>


void Application::Exit() {
    window_.close();
}

void Application::TransitionTo(std::unique_ptr<Screen> screen) {
    activeScreen_ = std::move(screen);
}

void Application::Fullscreen() {
    
    const auto& available = sf::VideoMode::getFullscreenModes();
    if(available.size() > 0) window_.create(available[0], ui::AppName, sf::Style::Fullscreen);
    else window_.create(sf::VideoMode::getDesktopMode(), ui::AppName, sf::Style::Fullscreen);

    renderSystem_.WW = window_.getView().getSize().x;
    renderSystem_.HH = window_.getView().getSize().y;
    aspectRatio = renderSystem_.WW / renderSystem_.HH;
    ui::aspectRatio = aspectRatio;
    windowWidth = (float)window_.getViewport(window_.getView()).width;
    windowHeight = (float)window_.getViewport(window_.getView()).height;


}

void Application::Resize(unsigned int width, unsigned int height) {
    
    float w = (float)width;
    float h = (float)height;

    if(abs(w/h - aspectRatio) > 0.01F) {
        if(w != windowWidth) h = w / aspectRatio;
        else w = h * aspectRatio;
    }

    windowWidth = w;
    windowHeight = h;
    window_.setSize({(unsigned int)w, (unsigned int)h});

}

Application::Application() : resourceManager_(fileManager_), renderSystem_(window_, resourceManager_) {

    //Create fullscreen window
    Fullscreen();
    window_.setVerticalSyncEnabled(false);
    window_.setFramerateLimit(150); //This will probably get turned to a constant

    //switch to resizable for debugging different window sizes
    window_.create(sf::VideoMode::getDesktopMode(), ui::AppName);
    renderSystem_.WW = window_.getView().getSize().x;
    renderSystem_.HH = window_.getView().getSize().y;
    renderSystem_.WW = window_.getView().getSize().x;
    renderSystem_.HH = window_.getView().getSize().y;
    aspectRatio = renderSystem_.WW / renderSystem_.HH;
    ui::aspectRatio = aspectRatio;
    windowWidth = (float)window_.getViewport(window_.getView()).width;
    windowHeight = (float)window_.getViewport(window_.getView()).height;

    //Make 800 px wide
    Resize(800, 800);
    
    TransitionTo(std::make_unique<DemoScreen>(*this));
}

float Application::GetAspectRatio() const { return aspectRatio; }
float Application::GetWindowWidth() const { return windowWidth; }
float Application::GetWindowHeight() const { return windowHeight; }

const FileManager& Application::GetFileManager() const { return fileManager_;}
const AudioSystem& Application::GetAudioSystem() const { return audioSystem_; }
const RenderSystem& Application::GetRenderSystem() const { return renderSystem_; }
const ResourceManager& Application::GetResourceManager() const { return resourceManager_; }


bool Application::Loop() {

    sf::Event event;
    while(window_.pollEvent(event)) {
        if(event.type == sf::Event::Closed) window_.close();
        if(event.type == sf::Event::Resized) Resize(event.size.width, event.size.height);

        if(event.type == sf::Event::KeyPressed) activeScreen_->OnKeyDown(event.key);
        if(event.type == sf::Event::KeyReleased) activeScreen_->OnKeyUp(event.key);

        if(event.type == sf::Event::MouseButtonPressed) {
            float x = event.mouseButton.x / GetWindowWidth();
            float y = event.mouseButton.y / GetWindowHeight();
            activeScreen_->OnMouseDown(event.mouseButton.button, x, y);
        }
        if(event.type == sf::Event::MouseButtonReleased) {
            float x = event.mouseButton.x / GetWindowWidth();
            float y = event.mouseButton.y / GetWindowHeight();
            activeScreen_->OnMouseUp(event.mouseButton.button, x, y);
        }
        if(event.type == sf::Event::MouseMoved) {
            float x = event.mouseMove.x / GetWindowWidth();
            float y = event.mouseMove.y / GetWindowHeight();
            activeScreen_->OnMouseMove(x, y);
        }

        if(event.type == sf::Event::MouseWheelScrolled) activeScreen_->OnMouseScroll(event.mouseWheelScroll);
        if(event.type == sf::Event::TextEntered) activeScreen_->OnTextEntered(event.text);

    }

    float frametime = clock.restart().asSeconds();
    if(frametime > 0.2F) frametime = 0.2F;
    accumulatedTime += frametime;

    while(accumulatedTime >= ph::Timestep) {
        activeScreen_->Update();
        accumulatedTime -= ph::Timestep;
    }
    
    
    //Gray color
    window_.clear({128, 128, 128, 255});
    renderSystem_.ALPHA = accumulatedTime / ph::Timestep;
    activeScreen_->Render(renderSystem_);
    window_.display();


    return window_.isOpen();

}