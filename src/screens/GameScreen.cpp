#include <screens/GameScreen.hpp>
#include <ui/MessageBox.hpp>

GameScreen::GameScreen(
    Application& app, const Level& initialLevel
): Screen(app), scoreLabel_(addScoreLabel()), game_(std::make_shared<Game>(*this, initialLevel)){
    level_ = initialLevel;
    addTopLeftButtons();
    timeLabel_ = addTopRightLabel(2, "time: ");
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
    app_.TransitionTo(std::make_unique<MainMenu>(this->GetApplication()));
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
    auto bt = std::make_shared<RoundIcon>(
        topLeftButtonSpacing_, 
        calcTopLeftButtonLeft(buttonNumber), 
        topLeftButtonSize_ / 2,
        sprite
    );
    auto b = std::weak_ptr<RoundIcon>(bt);
    bt->SetWindowResizeHandler([this, b, buttonNumber](){
        b.lock()->SetLeft(this->calcTopLeftButtonLeft(buttonNumber));
    });
    menu_.push_back(bt);
    return bt;
}

ui::pfloat GameScreen::calcTopLeftButtonLeft(unsigned char buttonNumber) const {
    float s = ui::toVHFloat(topLeftButtonSpacing_);
    return (s + (s + ui::toVHFloat(topLeftButtonSize_)) * (buttonNumber - 1)) VH;
}

void GameScreen::addTopLeftButtons(){
    auto pauseButton = std::weak_ptr<RoundIcon>(addTopLeftButton(1, SpriteID::ui_button_pause));
    pauseButton.lock()->SetMouseDownHandler([this, pauseButton](){
        auto pb = pauseButton.lock();
        if(pb->GetIcon() == SpriteID::ui_button_resume){
            pb->SetIcon(SpriteID::ui_button_pause);
            this->GetGame()->Resume();
        }else{
            pb->SetIcon(SpriteID::ui_button_resume);
            this->GetGame()->Pause();
        }
    });
    addTopLeftButton(2, [this](){
        this->GetGame()->Pause();
        this->Confirm("Do you want to restart the level?", [this](bool b){
            if(b) this->Restart();
            else this->GetGame()->Resume();
        });
    }, SpriteID::ui_button_restart);
    addTopLeftButton(3, [this](){
        this->GetGame()->Pause();
        this->Confirm("Do you want to quit to main menu?", [this](bool b){
            if(b) this->Exit();
            else this->GetGame()->Resume();
        });
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
    auto we = std::weak_ptr<TextLine>(e);
    e->SetWindowResizeHandler([this, we, labelNumber](){
        we.lock()->SetPosition(
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

void GameScreen::OnGameLost(){
    std::vector<std::shared_ptr<Element>> v;
    v.push_back(std::make_shared<MessageBox>(messageBoxHeight_, messageBoxWidth_));
    v.push_back(generateMessageBoxButton(1, [this](){
        this->DequeueMessage();
        this->Restart();
    }, SpriteID::ui_button_restart));
    v.push_back(generateMessageBoxButton(2, [this](){
        this->DequeueMessage();
        this->Exit();
    }, SpriteID::ui_button_exit));
    v.push_back(generateConfirmText("Level failed!"));
    messages_.push(v);
}