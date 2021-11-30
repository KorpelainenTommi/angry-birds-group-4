#include <screens/GameScreen.hpp>

GameScreen::GameScreen(
    Application& app, const Level& initialLevel
): Screen(app), game_(std::make_shared<Game>(*this, initialLevel)), level_(initialLevel){
    addTopLeftButton(2, [this](){
        this->Confirm("Do you want to restart the level?", [this](bool b){
            if(b) this->Restart();
        });
    }, SpriteID::ui_button_restart);
    addTopLeftButton(3, [this](){
        this->Exit();
    }, SpriteID::ui_button_exit);
}

void GameScreen::Exit(){
    Confirm("Do you want to quit to main menu?", [this](bool b){
        if(b) this->GetApplication().TransitionTo(std::make_unique<MainMenu>(this->GetApplication()));
    });
}

void GameScreen::Restart(){
    game_ = std::make_shared<Game>(*this, level_);
}

void GameScreen::addTopLeftButton(
    unsigned char buttonNumber, std::function<void()> callBack, const SpriteID& sprite
){
    auto b = std::make_shared<RoundIcon>(
        topLeftButtonSpacing_, 
        calcTopLeftButtonLeft(buttonNumber), 
        topLeftButtonSize_ / 2,
        sprite
    );
    b->SetMouseDownHandler(callBack);
    b->SetWindowResizeHandler([this, b, buttonNumber](){
        b->SetLeft(this->calcTopLeftButtonLeft(buttonNumber));
    });
    menu_.push_back(b);
}

ui::pfloat GameScreen::calcTopLeftButtonLeft(unsigned char buttonNumber){
    float s = ui::toVHFloat(topLeftButtonSpacing_);
    return (s + (s + ui::toVHFloat(topLeftButtonSize_)) * (buttonNumber - 1)) VH;
}