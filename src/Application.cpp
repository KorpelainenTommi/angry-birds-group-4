#include <math.h>
#include <Application.hpp>
#include <ui/UIConstants.hpp>
#include <screens/DemoScreen.hpp>
#include <screens/MainMenu.hpp>


float ui::windowWidth = 0;
float ui::windowHeight = 0;
float ui::aspectRatio = 1;

void Application::Exit() {
    window_.close();
}

void Application::TransitionTo(std::unique_ptr<Screen> screen) {
    activeScreen_ = std::move(screen);
}

void Application::UpdateView() {

    renderSystem_.WW = window_.getView().getSize().x;
    renderSystem_.HH = window_.getView().getSize().y;
    ui::windowWidth = renderSystem_.WW;
    ui::windowHeight = renderSystem_.HH;
    ui::aspectRatio = renderSystem_.WW / renderSystem_.HH;

}

void Application::Fullscreen() {
    
    const auto& available = sf::VideoMode::getFullscreenModes();
    if(available.size() > 0) window_.create(available[0], ui::appName, sf::Style::Fullscreen);
    else window_.create(sf::VideoMode::getDesktopMode(), ui::appName, sf::Style::Fullscreen);
    window_.setView(window_.getDefaultView());
    UpdateView();
    isFullScreen_ = true;

}

void Application::Resize(unsigned int width, unsigned int height) {

    if(isFullScreen_) window_.create(sf::VideoMode(width, height), ui::appName, sf::Style::Default);
    window_.setView(sf::View({0.0F, 0.0F, (float)width, (float)height}));
    UpdateView();
    isFullScreen_ = false;

}

Application::Application() : resourceManager_(fileManager_), renderSystem_(window_, resourceManager_), audioSystem_(resourceManager_) {

    //Create fullscreen window
    //Fullscreen();

    //Switch to resizable for now
    Resize(800, 800);
    
    //This is needed to capture some startup events that happen on certain desktops
    sf::Event ev;
    while(window_.pollEvent(ev));

    //TransitionTo(std::make_unique<MainMenu>(*this));
    TransitionTo(std::make_unique<DemoScreen>(*this));
}

float Application::GetAspectRatio() const { return ui::aspectRatio; }
float Application::GetWindowWidth() const { return ui::windowWidth; }
float Application::GetWindowHeight() const { return ui::windowHeight; }
bool Application::IsFullScreen() const { return isFullScreen_; }

AudioSystem& Application::GetAudioSystem() { return audioSystem_; }
const FileManager& Application::GetFileManager() const { return fileManager_;}
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

        if(event.type == sf::Event::MouseWheelScrolled) {
            float x = event.mouseWheelScroll.x / GetWindowWidth();
            float y = event.mouseWheelScroll.y / GetWindowHeight();
            activeScreen_->OnMouseScroll(event.mouseWheelScroll.delta, x, y);
        }

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

    //This replaces window.setFrameratelimit as it was causing a freeze with certain desktops
    //No idea why it failed, negative sleep? This hopefully works
    float t;
    while((t = clock.getElapsedTime().asSeconds()) < ui::targetFrametime) {
        t = ui::targetFrametime - t; if(t < 0) t = 0;
        sf::sleep(sf::seconds(t * 0.5F));
    }

    return window_.isOpen();

}