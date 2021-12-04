#include <screens/GameScreen.hpp>
#include <ui/MessageBox.hpp>

#include <ui/InputElement.hpp>

GameScreen::GameScreen(
    Application& app, const Level& initialLevel
): Screen(app), scoreLabel_(addScoreLabel()), game_(Game(*this, initialLevel)){
    level_ = initialLevel;
    addTopLeftButtons();
    timeLabel_ = addTopRightLabel(2, "time: ");
    /*auto input = std::make_shared<InputElement>(30 VH, 30 VW, ui::defaultFontSize * 8, 40 VW);
    input->SetFontSize(ui::defaultFontSize * 4);
    menu_.push_back(input);*/
    //OnGameCompleted(8000, 10000);
}

void GameScreen::Update(){
    game_.Update();
    timeLabel_->SetText("time: " + getString((int)(game_.GetTimeForUI())));
}

void GameScreen::Render(const RenderSystem& r){
    game_.Render(r);
    Screen::Render(r);
}

void GameScreen::Exit(){
    app_.TransitionTo(std::make_unique<MainMenu>(this->GetApplication()));
}

void GameScreen::Restart(){
    game_.Restart();
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
            this->GetGame().Resume();
        }else{
            pb->SetIcon(SpriteID::ui_button_resume);
            this->GetGame().Pause();
        }
    });
    addTopLeftButton(2, [this](){
        this->GetGame().Pause();
        this->Confirm("Do you want to restart the level?", [this](bool b){
            if(b) this->Restart();
            else this->GetGame().Resume();
        });
    }, SpriteID::ui_button_restart);
    addTopLeftButton(3, [this](){
        this->GetGame().Pause();
        this->Confirm("Do you want to quit to main menu?", [this](bool b){
            if(b) this->Exit();
            else this->GetGame().Resume();
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
    }, SpriteID::ui_button_restart, messageBoxHeight_, messageBoxWidth_));
    v.push_back(generateMessageBoxButton(2, [this](){
        this->DequeueMessage();
        this->Exit();
    }, SpriteID::ui_button_exit, messageBoxHeight_, messageBoxWidth_));
    v.push_back(generateConfirmText("Level failed!"));
    messages_.push(v);
}

void GameScreen::OnGameCompleted(int score, int requiredMaxScore){
    std::vector<std::shared_ptr<Element>> v;
    v.push_back(std::make_shared<MessageBox>(victoryMessageHeight_, victoryMessageWidth_));
    addVictoryMessageStars(score, requiredMaxScore, v);
    addVictoryMessageScore(score, v);
    addVictoryMessageNicknamePrompt(v);
    auto i = generateVictoryMessageInput();
    v.push_back(i);
    v.push_back(generateMessageBoxButton(1, [this, i, score](){
        this->DequeueMessage();
        std::string name = i->GetText();
        if(name.size() > 0) this->saveScore(name, score);
        this->Exit();
    }, SpriteID::ui_button_ok, victoryMessageHeight_, victoryMessageWidth_));
    v.push_back(generateMessageBoxButton(2, [this, i, score](){
        this->DequeueMessage();
        std::string name = i->GetText();
        if(name.size() > 0) this->saveScore(name, score);
        this->Restart();
    }, SpriteID::ui_button_restart, victoryMessageHeight_, victoryMessageWidth_));
    messages_.push(v);
}

void GameScreen::addVictoryMessageStars(int score, int maxScore, std::vector<std::shared_ptr<Element>>& v){
    v.push_back(generateVictoryMessageStar(1, true));
    v.push_back(generateVictoryMessageStar(2, score >= maxScore / 2));
    v.push_back(generateVictoryMessageStar(3, score >= maxScore));
}

std::shared_ptr<RoundIcon> GameScreen::generateVictoryMessageStar(char starNumber, bool achieved){
    auto s = std::make_shared<RoundIcon>(
        calcVictoryMessageStarTop(), 
        calcVictoryMessageStarLeft(starNumber), 
        victoryMessageStarSize_ / 2,
        achieved ? SpriteID::ui_star : SpriteID::ui_missing_star
    );
    auto ws = std::weak_ptr<RoundIcon>(s);
    s->SetWindowResizeHandler([this, ws, starNumber](){
        ws.lock()->SetPosition(
            this->calcVictoryMessageStarLeft(starNumber), 
            this->calcVictoryMessageStarTop()
        );
    });
    return s;
}

ui::pfloat GameScreen::calcVictoryMessageStarTop() const {
    return (50 - ui::toVHFloat(victoryMessageHeight_) / 2 + ui::toVHFloat(messageBoxSpacing_)) VH;
}

ui::pfloat GameScreen::calcVictoryMessageStarLeft(char starNumber) const {
    return (50 + ui::toVWFloat(victoryMessageStarSize_) * (starNumber - 2.5)) VW;
}

void GameScreen::addVictoryMessageScore(int score, std::vector<std::shared_ptr<Element>>& v){
    auto s = std::make_shared<TextLine>(
        calcVictoryMessageScoreTop(), 
        calcVictoryMessageContentLeft(), 
        victoryMessageFontSize_, 
        calcVictoryMessageContentWidth(), 
        "score: " + getString(score)
    );
    s->SetRelativeFontSize(victoryMessageFontSize_);
    s->SetTextAlign(ui::TextAlign::center);
    auto ws = std::weak_ptr<TextLine>(s);
    s->SetWindowResizeHandler([this, ws](){
        auto s = ws.lock();
        s->SetPosition(
            this->calcVictoryMessageContentLeft(), 
            this->calcVictoryMessageScoreTop()
        );
        s->SetWidth(this->calcVictoryMessageContentWidth());
    });
    v.push_back(s);
}

ui::pfloat GameScreen::calcVictoryMessageScoreTop() const {
    return (ui::toVHFloat(calcVictoryMessageStarTop()) 
        + ui::toVHFloat(victoryMessageStarSize_) + ui::toVHFloat(messageBoxSpacing_)) VH;
}

ui::pfloat GameScreen::calcVictoryMessageContentLeft() const {
    return (50 - ui::toVWFloat(victoryMessageWidth_) / 2 + ui::toVWFloat(messageBoxSpacing_)) VW;
}

ui::pfloat GameScreen::calcVictoryMessageContentWidth() const {
    return (ui::toVWFloat(victoryMessageWidth_) - ui::toVWFloat(messageBoxSpacing_) * 2) VW;
}

void GameScreen::addVictoryMessageNicknamePrompt(std::vector<std::shared_ptr<Element>>& v){
    auto t = std::make_shared<TextLine>(
        calcVictoryMessageNicknamePromptTop(), 
        calcVictoryMessageContentLeft(), 
        victoryMessageFontSize_, 
        calcVictoryMessageContentLeft(), 
        "Please give a nickname to save your score:"
    );
    t->SetRelativeFontSize(victoryMessageFontSize_);
    t->SetTextAlign(ui::TextAlign::center);
    auto wt = std::weak_ptr<TextLine>(t);
    t->SetWindowResizeHandler([this, wt](){
        auto t = wt.lock();
        t->SetPosition(
            this->calcVictoryMessageContentLeft(), 
            this->calcVictoryMessageNicknamePromptTop()
        );
        t->SetWidth(this->calcVictoryMessageContentWidth());
    });
    v.push_back(t);
}

ui::pfloat GameScreen::calcVictoryMessageNicknamePromptTop() const {
    return (ui::toVHFloat(calcVictoryMessageScoreTop()) 
        + ui::toVHFloat(victoryMessageFontSize_) + ui::toVHFloat(messageBoxSpacing_)) VH;
}

std::shared_ptr<InputElement> GameScreen::generateVictoryMessageInput(){
    auto i = std::make_shared<InputElement>(
        calcVictoryMessageInputTop(), 
        calcVictoryMessageContentLeft(), 
        victoryMessageFontSize_ * 2, 
        calcVictoryMessageContentWidth()
    );
    auto wi = std::weak_ptr<InputElement>(i);
    i->SetWindowResizeHandler([this, wi](){
        auto i = wi.lock();
        i->SetPosition(
            calcVictoryMessageContentLeft(), 
            calcVictoryMessageInputTop()
        );
        i->SetWidth(this->calcVictoryMessageContentWidth());
    });
    return i;
}

ui::pfloat GameScreen::calcVictoryMessageInputTop() const {
    return (ui::toVHFloat(calcVictoryMessageNicknamePromptTop()) 
        + ui::toVHFloat(victoryMessageFontSize_)) VH;
}

void GameScreen::saveScore(const std::string& name, int score){
    std::size_t len = level_.highscores.size();
    if(len == 0){
        level_.highscores.push_back({name, score});
    }else{
        //This naive algorithm could be replaced with binary search if I have time and will power.
        for(std::size_t i = 0; i < len; i++){
            if(level_.highscores[i].second < score){
                level_.highscores.insert(level_.highscores.begin() + i, {name, score});
                break;
            }
        }
    }
    app_.GetFileManager().SaveLevel(level_);
}

bool GameScreen::OnMouseScroll(float delta, float xw, float yh) {
    if(Screen::OnMouseScroll(delta, xw, yh)) return true;
    if(game_.OnMouseScroll(delta, xw, yh)) return true;
    return false;
}
bool GameScreen::OnMouseDown(const sf::Mouse::Button& e, float x, float y) {
    if(Screen::OnMouseDown(e, x, y)) return true;
    if(game_.OnMouseDown(e, x, y)) return true;
    return false;
}

bool GameScreen::OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
    if(Screen::OnMouseUp(e, x, y)) return true;
    if(game_.OnMouseUp(e, x, y)) return true;
    return false;
}

bool GameScreen::OnMouseMove(float x, float y) {
    bool b = Screen::OnMouseMove(x, y);
    return game_.OnMouseMove(x, y) || b;
}
