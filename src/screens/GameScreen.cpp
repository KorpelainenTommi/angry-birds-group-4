#include <screens/GameScreen.hpp>

GameScreen::GameScreen(
    Application& app, const Level& initialLevel
): Screen(app), scoreLabel_(addScoreLabel()), game_(std::make_shared<Game>(*this, initialLevel)){
    level_ = initialLevel;
    addTopLeftButtons();
    timeLabel_ = addTopRightLabel(2, "time: ");
    OnScoreChange(123456);
}

void GameScreen::Update(){
    game_->Update();
    timeLabel_->SetText("time: " + getString((int)(game_->GetTime())));
}

void GameScreen::Render(const RenderSystem& r){
    game_->Render(r);
    Screen::Render(r);
}

void GameScreen::Exit(){
    Confirm("Do you want to quit to main menu?", [this](bool b){
        if(b) this->GetApplication().TransitionTo(std::make_unique<MainMenu>(this->GetApplication()));
    });
}

void GameScreen::Restart(){
    game_ = std::make_shared<Game>(*this, level_);
}

std::shared_ptr<RoundIcon> GameScreen::addTopLeftButton(
    unsigned char buttonNumber, std::function<void()> callBack, const SpriteID& sprite
){
    auto b = addTopLeftButton(buttonNumber, sprite);
    b->SetMouseDownHandler(callBack);
    return b;
}

std::shared_ptr<RoundIcon> GameScreen::addTopLeftButton(
    unsigned char buttonNumber, const SpriteID& sprite
){
    auto b = std::make_shared<RoundIcon>(
        topLeftButtonSpacing_, 
        calcTopLeftButtonLeft(buttonNumber), 
        topLeftButtonSize_ / 2,
        sprite
    );
    b->SetWindowResizeHandler([this, b, buttonNumber](){
        b->SetLeft(this->calcTopLeftButtonLeft(buttonNumber));
    });
    menu_.push_back(b);
    return b;
}

ui::pfloat GameScreen::calcTopLeftButtonLeft(unsigned char buttonNumber) const {
    float s = ui::toVHFloat(topLeftButtonSpacing_);
    return (s + (s + ui::toVHFloat(topLeftButtonSize_)) * (buttonNumber - 1)) VH;
}

void GameScreen::addTopLeftButtons(){
    auto pauseButton = addTopLeftButton(1, SpriteID::ui_button_pause);
    pauseButton->SetMouseDownHandler([this, pauseButton](){
        if(pauseButton->GetIcon() == SpriteID::ui_button_resume){
            pauseButton->SetIcon(SpriteID::ui_button_pause);
            this->GetGame()->Resume();
        }else{
            pauseButton->SetIcon(SpriteID::ui_button_resume);
            this->GetGame()->Pause();
        }
    });
    addTopLeftButton(2, [this](){
        this->Confirm("Do you want to restart the level?", [this](bool b){
            if(b) this->Restart();
        });
    }, SpriteID::ui_button_restart);
    addTopLeftButton(3, [this](){
        this->Exit();
    }, SpriteID::ui_button_exit);
}

void GameScreen::OnScoreChange(int score){
    scoreLabel_->SetText("score: " + getString(score));
}

ui::pfloat GameScreen::calcTopRightLabelTop(unsigned char labelNumber) const {
    float s = ui::toVHFloat(topRightLabelSpacing_);
    return (s + (s + ui::toVHFloat(topRightLabelHeigth_)) * (labelNumber - 1)) VH;
}

ui::pfloat GameScreen::calcTopRightLabelLeft() const {
    return (100 - ui::toVWFloat(topRightLabelLength_)) VW;
}

std::shared_ptr<TextLine> GameScreen::addTopRightLabel(
    unsigned char labelNumber, const std::string& text
){
    auto e = std::make_shared<TextLine>(
        calcTopRightLabelTop(labelNumber), 
        calcTopRightLabelLeft(), 
        topRightLabelHeigth_, 
        topRightLabelLength_, 
        text
    );
    e->SetWindowResizeHandler([this, e, labelNumber](){
        e->SetPosition(
            this->calcTopRightLabelLeft(), 
            this->calcTopRightLabelTop(labelNumber)
        );
    });
    e->SetRelativeFontSize(topRightLabelHeigth_);
    menu_.push_back(e);
    return e;
}

std::shared_ptr<TextLine> GameScreen::addScoreLabel(){
    return addTopRightLabel(1, "score: ");
}