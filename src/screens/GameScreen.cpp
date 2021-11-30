#include <screens/GameScreen.hpp>

void GameScreen::Exit(){
    Confirm("Do you want to quit to main menu?", [this](bool b){
        if(b) this->GetApplication().TransitionTo(std::make_unique<MainMenu>(this->GetApplication()));
    });
}