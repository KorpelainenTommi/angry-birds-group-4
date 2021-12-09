#include <screens/GameScreen.hpp>
#include <ui/MessageBox.hpp>

#include <ui/InputElement.hpp>
#include <exception>

GameScreen::GameScreen(
    Application& app, const Level& initialLevel, bool editorMode
): Screen(app){
    level_ = initialLevel;
    editorMode_ = editorMode;
    if(editorMode_){
        addEditorTopLeftButtons();
        addEditorPanel();
    }else{
        addTopLeftButtons();
        addTopRightLabels();
    }
    addProjectileBar();
    game_ = editorMode ? 
        std::make_unique<Editor>(*this, initialLevel) : 
        std::make_unique<Game>(*this, initialLevel);
    UpdateTheoreticalMaxScore(1234567);
}

void GameScreen::Update(){
    game_->Update();
    if(!editorMode_) timeLabel_->SetText("time: " + getString((int)(game_->GetTimeForUI())));
}

void GameScreen::Render(const RenderSystem& r){
    game_->Render(r);
    Screen::Render(r);
}

void GameScreen::Exit(){
    app_.TransitionTo(std::make_unique<MainMenu>(this->GetApplication()));
}

void GameScreen::Restart(){
    game_->Restart();
}

Game& GameScreen::GetGame(){
    return *game_;
}

Editor& GameScreen::GetEditor(){
    if(!editorMode_) throw std::runtime_error("The GameScreen isn't in editor mode so GetEditor shouldn't be called.");
    return *((Editor*)game_.get());
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
    addTopLeftButton(2, [this, pauseButton](){
        this->GetGame().Pause();
        this->Confirm("Do you want to restart the level?", [this, pauseButton](bool b){
            if(b){
                pauseButton.lock()->SetIcon(SpriteID::ui_button_pause);
                this->Restart();
            }
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

void GameScreen::addEditorTopLeftButtons(){
    addTopLeftButton(1, [this](){
        if(this->SaveEditor()) this->Alert("Level saved.");
    }, SpriteID::ui_button_save);
    auto startButton = std::weak_ptr<RoundIcon>(addTopLeftButton(2, SpriteID::ui_button_resume));
    startButton.lock()->SetMouseDownHandler([this, startButton](){
        auto sb = startButton.lock();
        if(sb->GetIcon() == SpriteID::ui_button_resume){
            sb->SetIcon(SpriteID::ui_button_restart);
            //resume editor here
        }else{
            sb->SetIcon(SpriteID::ui_button_resume);
            //restart and pause Editor here
        }
    });
    addTopLeftButton(3, [this](){
        this->GetGame().Pause();
        this->Confirm("Do you want to quit to main menu?", [this](bool b){
            if(b) this->Exit();
            else this->GetGame().Resume();
        });
    }, SpriteID::ui_button_exit);
}

bool GameScreen::SaveEditor(){
    std::string name = editorNameInput_->GetText();
    if(isEmpty(name)){
        Alert("Level name can't be empty.");
        return false;
    }

    int score;
    try{
        score = parseInt(editorRequiredScoreInput_->GetText());
    }catch(std::exception e){
        Alert("Score must be an integer.");
        return false;
    }

    int time;
    if(selectedGameMode_ == LevelMode::time_trial){
        try{
            time = parseInt(editorTimeInput_->GetText());
        }catch(std::exception e){
            time = 0;
        }
        if(time <= 0){
            Alert("Time limit must be a positive integer.");
            return false;
        }
    }

    Level lev = GetEditor().GetLevel();
    lev.levelName = name;
    lev.levelMode = selectedGameMode_;
    lev.perfectScore = score;
    if(selectedGameMode_ == LevelMode::time_trial) lev.timeLimit = time;
    app_.GetFileManager().SaveLevel(lev);
    return true;
}

void GameScreen::OnScoreChange(int score){
    if(!editorMode_) scoreLabel_->SetText("score: " + getString(score));
}

ui::pfloat GameScreen::calcTopRightLabelTop(unsigned char labelNumber) const {
    float s = ui::toVHFloat(topRightLabelSpacing_);
    return (s + (s + ui::toVHFloat(topRightLabelHeigth_)) * (labelNumber - 1)) VH;
}

ui::pfloat GameScreen::calcTopRightLabelLeft() const {
    return (100 - ui::toVWFloat(topRightLabelLength_)) VW;
}

void GameScreen::addTopRightLabels(){
    timeLabel_ = addTopRightLabel(2, "time: ");
    scoreLabel_ = addTopRightLabel(1, "score: 0");
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
    e->SetTextColor({0, 0, 0});
    menu_.push_back(e);
    return e;
}

void GameScreen::OnGameLost(const std::string& reason){
    if(editorMode_) return;
    game_->Pause();
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
    v.push_back(generateConfirmText(reason));
    messages_.push(v);
}

void GameScreen::OnGameCompleted(int score, int requiredMaxScore){
    if(editorMode_) return;
    game_->Pause();
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
    return (50 + ui::toVWFloat(victoryMessageStarSize_) * (starNumber - 2.5) 
        + ui::toVWFloat(victoryMessageStarSpacing_) * (starNumber - 2)) VW;
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
        calcVictoryMessageContentWidth(), 
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

void GameScreen::addProjectileBar(){
    addList();
    projectileList_->SetFocusCapture(true);
    auto listTop = addListTop();
    listTop->SetFocusCapture(true);
    auto listBottom = addListBottom();
    listBottom->SetFocusCapture(true);
    auto wp = std::weak_ptr<ListElement>(projectileList_);
    projectileList_->SetWindowResizeHandler([this, wp, listTop, listBottom](){
        ui::pfloat w = this->calcProjectileBarWidth();
        listTop->SetTop(this->calcProjectileBarTop());
        listTop->SetWidth(w);
        listBottom->SetTop(this->calcProjectileBarBottomTop());
        listBottom->SetWidth(w);
        auto p = wp.lock();
        p->SetTop(this->calcProjectileBarBodyTop());
        p->SetSize(
            w, 
            this->calcProjectileBarBodyHeight()
        );
    });
}

std::shared_ptr<ColoredElement> GameScreen::addListTop(){
    auto e = std::make_shared<ColoredElement>(
        calcProjectileBarTop(), 
        0 VW, 
        projectileBarSpacing_, 
        calcProjectileBarWidth()
    );
    e->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(e);
    return e;
}

ui::pfloat GameScreen::calcProjectileBarWidth() const {
    return (ui::toVHFloat(projectileBarIconSize_) + ui::toVHFloat(projectileBarSpacing_) * 2) VH;
}

ui::pfloat GameScreen::calcProjectileBarTop() const {
    return (50 - ui::toVHFloat(projectileBarHeight_) / 2) VH;
}

std::shared_ptr<ColoredElement> GameScreen::addListBottom(){
    auto e = std::make_shared<ColoredElement>(
        calcProjectileBarBottomTop(), 
        0 VW, 
        projectileBarSpacing_, 
        calcProjectileBarWidth()
    );
    e->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(e);
    return e;
}

ui::pfloat GameScreen::calcProjectileBarBottomTop() const {
    return (50 + ui::toVHFloat(projectileBarHeight_) / 2 - ui::toVHFloat(projectileBarSpacing_)) VH;
}

void GameScreen::addList(){
    projectileList_ = std::make_shared<ListElement>(
        calcProjectileBarBodyTop(), 
        0 VW, 
        calcProjectileBarBodyHeight(), 
        calcProjectileBarWidth()
    );
    projectileList_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(projectileList_);
}

ui::pfloat GameScreen::calcProjectileBarBodyTop() const {
    return (50 - ui::toVHFloat(projectileBarHeight_) / 2 + ui::toVHFloat(projectileBarSpacing_)) VH;
}

ui::pfloat GameScreen::calcProjectileBarBodyHeight() const {
    return (ui::toVHFloat(projectileBarHeight_) - ui::toVHFloat(projectileBarSpacing_) * 2) VH;
}

void GameScreen::UpdateProjectileList(std::vector<std::pair<SpriteID, std::string>> projectiles){
    clearIcons();
    for(auto e: projectiles) addProjectileIcon(e.first, e.second);
    if(!editorMode_ && projectiles.size() > 0) {
        auto last = std::static_pointer_cast<RoundIcon>(projectileList_->GetElements().cbegin()->second);
        selectProjectileIcon(last);
    }
}

void GameScreen::clearIcons(){
    projectileList_->ClearElements();
    for(std::size_t i = iconIndexes_.size(); i > 0;){
        menu_.erase(menu_.begin() + iconIndexes_[--i]);
    }
    iconIndexes_.clear();
}

void GameScreen::addProjectileIcon(SpriteID icon, const std::string& name){
    auto i = std::make_shared<RoundIcon>(
        0 VH, 
        projectileBarSpacing_, 
        projectileBarIconSize_ / 2, 
        icon
    );
    i->SetTitle(name);
    auto wi = std::weak_ptr<RoundIcon>(i);
    auto index = projectileList_->GetElements().size();
    i->SetMouseDownHandler([this, index, wi](){
        if(this->IsInEditorMode()){
            this->GetEditor().RemoveProjectile(index);
        }else{
            this->GetGame().SelectProjectile(index);
            this->selectProjectileIcon(wi.lock());
        }
    });
    projectileList_->InsertElement(i);
    iconIndexes_.push_back(menu_.size());
    menu_.push_back(i);
}

void GameScreen::selectProjectileIcon(std::shared_ptr<RoundIcon> i){
    if(hasSelectedIcon_) selectedIcon_->Unselect();
    else hasSelectedIcon_ = true;
    i->Select();
    selectedIcon_ = i;
}

void GameScreen::addEditorPanel(){
    addEditorPanelBackground();
    addEditorNameInput();
    addEditorGameModeDropDown();
    addEditorMaxScoreLabel();
    addEditorRequiredScoreLabel();
    addEditorRequiredScoreInput();
    addEditorTimeLimitLabel();
    addEditorTimeLimitInput();
    addEditorElementList();

    addBlocksToEditorElementList();
    addFuksiToEditorElementList();
    addProjectilesToEditorElementList();

    addEditorPanelVisibilityButton();

    setSelectedGameMode(level_.levelMode);
}

void GameScreen::addEditorPanelBackground(){
    editorPanelDiv_ = std::make_shared<DivElement>(
        0 VH, 
        calcEditorPanelLeft(), 
        100 VH, 
        editorPanelWidth_
    );
    editorPanelDiv_->SetFocusCapture(true);
    auto wb = std::weak_ptr<ColoredElement>(editorPanelDiv_);
    editorPanelDiv_->SetWindowResizeHandler([this, wb](){
        wb.lock()->SetLeft(this->calcEditorPanelLeft());
    });
    menu_.push_back(editorPanelDiv_);
}

ui::pfloat GameScreen::calcEditorPanelLeft() const {
    return (100 - ui::toVWFloat(editorPanelWidth_)) VW;
}

void GameScreen::addEditorNameInput(){
    editorNameInput_ = std::make_shared<InputElement>(
        editorPanelPadding_, 
        editorPanelPadding_, 
        editorFontSize_ * 2, 
        calcEditorContentWidth()
    );
    editorNameInput_->SetText(level_.levelName);
    editorNameInput_->SetFontSize(editorFontSize_);
    auto wi = std::weak_ptr<InputElement>(editorNameInput_);
    editorNameInput_->SetWindowResizeHandler([this, wi](){
        auto i = wi.lock();
        i->SetWidth(this->calcEditorContentWidth());
    });
    editorPanelDiv_->InsertElement(editorNameInput_);
    menu_.push_back(editorNameInput_);
}

ui::pfloat GameScreen::calcEditorContentWidth() const {
    return (ui::toVWFloat(editorPanelWidth_) - ui::toVWFloat(editorPanelPadding_) * 2) VW;
}

ui::pfloat GameScreen::calcEditorContentLeft() const {
    return (100 - ui::toVWFloat(editorPanelWidth_) + ui::toVWFloat(editorPanelPadding_)) VW;
}

void GameScreen::addEditorGameModeDropDown(){
    editorGameModeDropDown_ = std::make_shared<TextElement>(
        calcEditorDropDownTop(), 
        editorPanelPadding_, 
        editorFontSize_ * 2, 
        calcEditorContentWidth()
    );
    editorGameModeDropDown_->SetRelativeFontSize(editorFontSize_);
    editorGameModeDropDown_->SetBackgroundColor(ui::backgroundColor2);
    editorGameModeDropDown_->SetFocusCapture(true);
    auto we = std::weak_ptr<TextElement>(editorGameModeDropDown_);
    editorGameModeDropDown_->SetFocusChangeHandler([this, we](bool b){
        if(b) this->addDropDownContents(we.lock());
        else this->DequeueMessage();
    });
    editorGameModeDropDown_->SetWindowResizeHandler([this, we](){
        auto e = we.lock();
        e->Blur(); //I just don't want to even think about resizing the contents.
        e->SetTop(this->calcEditorDropDownTop());
        e->SetWidth(this->calcEditorContentWidth());
    });
    editorPanelDiv_->InsertElement(editorGameModeDropDown_);
    menu_.push_back(editorGameModeDropDown_);
}

void GameScreen::addDropDownContents(std::shared_ptr<TextElement> e){
    float y = ui::toVHFloat(e->GetTop()) + ui::toVHFloat(e->GetHeight());
    const ui::pfloat x = calcEditorContentLeft();
    float h = ui::toVHFloat(editorFontSize_ * 2);
    const ui::pfloat w = calcEditorContentWidth();
    std::vector<std::shared_ptr<Element>> v;
    std::size_t len = levelModeNames.size();
    for(std::size_t i = 0; i < len; i++){
        auto o = std::make_shared<TextElement>(y VH, x, h VH, w);
        o->SetText(' ' + levelModeNames[i]);
        o->SetRelativeFontSize(editorFontSize_);
        o->SetBackgroundColor(ui::backgroundColor2);
        o->SetMouseDownHandler([this, i, e](){
            this->setSelectedGameMode((LevelMode)i);
        });
        auto wo = std::weak_ptr<TextElement>(o);
        o->SetMouseEnterHandler([wo](){wo.lock()->SetBackgroundColor(ui::highlightColor);});
        o->SetMouseLeaveHandler([wo](){wo.lock()->SetBackgroundColor(ui::backgroundColor2);});
        v.push_back(o);
        y += h;
    }
    messages_.push(v);
}

void GameScreen::setSelectedGameMode(LevelMode m){
    selectedGameMode_ = m;
    editorGameModeDropDown_->SetText(" game mode: " + levelModeNames[m]);
    if(m == LevelMode::time_trial) showTimeTrialOptions();
    else hideTimeTrialOptions();
}

ui::pfloat GameScreen::calcEditorDropDownTop() const {
    return (ui::toVHFloat(editorPanelPadding_) + ui::toVHFloat(editorFontSize_) * 2 
        + ui::toVHFloat(editorPanelSpacing_)) VH;
}

void GameScreen::addEditorMaxScoreLabel(){
    editorMaxScoreLabel_ = std::make_shared<TextLine>(
        calcEditorMaxScoreLabelTop(), 
        editorPanelPadding_, 
        editorFontSize_, 
        calcEditorContentWidth(), 
        " max score:"
    );
    editorMaxScoreLabel_->SetRelativeFontSize(editorFontSize_);
    auto w = std::weak_ptr<TextLine>(editorMaxScoreLabel_);
    editorMaxScoreLabel_->SetWindowResizeHandler([this, w](){
        auto e = w.lock();
        e->SetTop(this->calcEditorMaxScoreLabelTop());
        e->SetWidth(this->calcEditorContentWidth());
    });
    editorPanelDiv_->InsertElement(editorMaxScoreLabel_);
    menu_.push_back(editorMaxScoreLabel_);
}

ui::pfloat GameScreen::calcEditorMaxScoreLabelTop() const {
    return (ui::toVHFloat(calcEditorDropDownTop()) + ui::toVHFloat(editorFontSize_) * 2 
        + ui::toVHFloat(editorPanelSpacing_)) VH;
}

void GameScreen::UpdateTheoreticalMaxScore(int maxScore){
    if(!editorMode_) return;
    editorMaxScoreLabel_->SetText(" max score: " + getString(maxScore));
}

void GameScreen::addEditorRequiredScoreLabel(){
    auto e = std::make_shared<TextLine>(
        calcEditorRequiredScoreLabelTop(), 
        editorPanelPadding_, 
        editorFontSize_, 
        calcEditorContentWidth(), 
        " require for max points:"
    );
    e->SetRelativeFontSize(editorFontSize_);
    auto we = std::weak_ptr<TextLine>(e);
    e->SetWindowResizeHandler([this, we](){
        auto e = we.lock();
        e->SetTop(this->calcEditorRequiredScoreLabelTop());
        e->SetWidth(this->calcEditorContentWidth());
    });
    editorPanelDiv_->InsertElement(e);
    menu_.push_back(e);
}

ui::pfloat GameScreen::calcEditorRequiredScoreLabelTop() const {
    return (ui::toVHFloat(calcEditorMaxScoreLabelTop()) + ui::toVHFloat(editorFontSize_) 
        + ui::toVHFloat(editorPanelSpacing_)) VH;
}

void GameScreen::addEditorRequiredScoreInput(){
    editorRequiredScoreInput_ = std::make_shared<InputElement>(
        calcEditorRequiredScoreInputTop(), 
        editorPanelPadding_, 
        editorFontSize_ * 2, 
        calcEditorContentWidth()
    );
    editorRequiredScoreInput_->SetFontSize(editorFontSize_);
    editorRequiredScoreInput_->SetText(getString(level_.perfectScore));
    auto w = std::weak_ptr<InputElement>(editorRequiredScoreInput_);
    editorRequiredScoreInput_->SetWindowResizeHandler([this, w](){
        auto i = w.lock();
        i->SetTop(this->calcEditorRequiredScoreInputTop());
        i->SetWidth(this->calcEditorContentWidth());
    });
    editorPanelDiv_->InsertElement(editorRequiredScoreInput_);
    menu_.push_back(editorRequiredScoreInput_);
}

ui::pfloat GameScreen::calcEditorRequiredScoreInputTop() const {
    return (ui::toVHFloat(calcEditorRequiredScoreLabelTop()) + ui::toVHFloat(editorFontSize_)) VH;
}

void GameScreen::addEditorTimeLimitLabel(){
    auto e = std::make_shared<TextLine>(
        calcEditorTimeLimitLabelTop(), 
        editorPanelPadding_, 
        editorFontSize_, 
        calcEditorContentWidth(), 
        " time limit in seconds:"
    );
    e->SetRelativeFontSize(editorFontSize_);
    e->Hide();
    auto we = std::weak_ptr<TextLine>(e);
    e->SetWindowResizeHandler([this, we](){
        auto e = we.lock();
        e->SetTop(this->calcEditorTimeLimitLabelTop());
        e->SetWidth(this->calcEditorContentWidth());
    });
    timeTrialElements_.push_back(e);
    editorPanelDiv_->InsertElement(e);
    menu_.push_back(e);
}

ui::pfloat GameScreen::calcEditorTimeLimitLabelTop() const {
    return (ui::toVHFloat(calcEditorRequiredScoreInputTop()) 
        + ui::toVHFloat(editorFontSize_) * 2 + ui::toVHFloat(editorPanelSpacing_)) VH;
}

void GameScreen::addEditorTimeLimitInput(){
    editorTimeInput_ = std::make_shared<InputElement>(
        calcEditorTimeLimitInputTop(), 
        editorPanelPadding_, 
        editorFontSize_ * 2, 
        calcEditorContentWidth()
    );
    editorTimeInput_->SetFontSize(editorFontSize_);
    editorTimeInput_->SetText(getString(level_.timeLimit));
    editorTimeInput_->Hide();
    auto w = std::weak_ptr<InputElement>(editorTimeInput_);
    editorTimeInput_->SetWindowResizeHandler([this, w](){
        auto i = w.lock();
        i->SetTop(this->calcEditorTimeLimitInputTop());
        i->SetWidth(this->calcEditorContentWidth());
    });
    timeTrialElements_.push_back(editorTimeInput_);
    editorPanelDiv_->InsertElement(editorTimeInput_);
    menu_.push_back(editorTimeInput_);
}

ui::pfloat GameScreen::calcEditorTimeLimitInputTop() const {
    return (ui::toVHFloat(calcEditorTimeLimitLabelTop()) + ui::toVHFloat(editorFontSize_)) VH;
}

void GameScreen::addEditorElementList(){
    editorElementList_ = std::make_shared<ListElement>(
        calcEditorElementListTop(), 
        editorPanelPadding_, 
        calcEditorElementListHeight(), 
        calcEditorContentWidth()
    );
    editorElementList_->SetBackgroundColor(ui::backgroundColor2);
    editorElementList_->SetSpacing(editorElementListSpacing_);
    auto w = std::weak_ptr<ListElement>(editorElementList_);
    editorElementList_->SetWindowResizeHandler([this, w](){
        auto e = w.lock();
        e->SetTop(this->calcEditorElementListTop());
        e->SetSize(
            this->calcEditorContentWidth(), 
            this->calcEditorElementListHeight()
        );
    });
    editorPanelDiv_->InsertElement(editorElementList_);
    menu_.push_back(editorElementList_);
}

ui::pfloat GameScreen::calcEditorElementListTop() const {
    return (ui::toVHFloat(timeTrial_ ? calcEditorTimeLimitInputTop() : calcEditorRequiredScoreInputTop()) 
        + ui::toVHFloat(editorFontSize_) * 2 + ui::toVHFloat(editorPanelSpacing_)) VH;
}

ui::pfloat GameScreen::calcEditorElementListHeight() const {
    return (100 - ui::toVHFloat(calcEditorElementListTop()) - ui::toVHFloat(editorPanelPadding_)) VH;
}

std::shared_ptr<DivElement> GameScreen::addEditorElementListLine(
    SpriteID icon, const std::string& text, const std::function<void()> mouseDownHandler
){
    auto div = std::make_shared<DivElement>(
        0 VH, 
        0 VW, 
        editorElementListLineHeight_, 
        calcEditorContentWidth()
    );
    div->SetMouseDownHandler(mouseDownHandler);
    div->SetBackgroundColor({0, 0, 0, 0});
    auto wd = std::weak_ptr<DivElement>(div);
    div->SetMouseEnterHandler([wd](){wd.lock()->SetBackgroundColor(ui::highlightColor);});
    div->SetMouseLeaveHandler([wd](){wd.lock()->SetBackgroundColor({0, 0, 0, 0});});
    editorElementList_->InsertElement(div);
    menu_.push_back(div);
    auto ico = std::make_shared<RoundIcon>(0 VH, 0 VW, editorElementListLineHeight_ / 2, icon);
    div->InsertElement(ico);
    menu_.push_back(ico);
    auto t = std::make_shared<TextElement>(
        0 VH, editorElementListLineHeight_, editorElementListLineHeight_, 1 VW /*this doesn't matter*/
    );
    t->SetBackgroundColor({0, 0, 0, 0});
    t->SetText(' ' + text);
    t->SetRelativeFontSize(editorFontSize_);
    div->InsertElement(t);
    menu_.push_back(t);
    div->SetWindowResizeHandler([this, wd](){
        wd.lock()->SetWidth(this->calcEditorContentWidth());
    });
    return div;
}

void GameScreen::addBlocksToEditorElementList(){
    for(auto t: gm::blockTypes){
        gm::GameObjectType type = t.first;
        std::string text = t.second.blockName;
        SpriteID icon = t.second.sprite;
        addEditorElementListLine(icon, text, [type, this](){
            this->GetEditor().SetSelectedElement(type);
        });
    }
}

void GameScreen::addProjectilesToEditorElementList(){
    for(auto p: gm::teekkaris){
        gm::GameObjectType type = p;
        std::string text = gm::teekkariBodies.at(p).guildName;
        SpriteID icon = SpriteID::teekkari_head1;
        addEditorElementListLine(icon, text, [type, this](){
            this->GetEditor().AddProjectile(type);
        });
    }
}

void GameScreen::addFuksiToEditorElementList(){
    gm::GameObjectType type = gm::GameObjectType::fuksi;
    std::string text = "Fuksi";
    SpriteID icon = SpriteID::fuksi_head1;
    addEditorElementListLine(icon, text, [type, this](){
        this->GetEditor().SetSelectedElement(type);
    });
}

void GameScreen::showTimeTrialOptions(){
    timeTrial_ = true;
    for(auto e: timeTrialElements_) e->Show();
    editorElementList_->OnWindowResize();
}

void GameScreen::hideTimeTrialOptions(){
    timeTrial_ = false;
    for(auto e: timeTrialElements_) e->Hide();
    editorElementList_->OnWindowResize();
}

void GameScreen::addEditorPanelVisibilityButton(){
    auto b = std::make_shared<RoundIcon>(
        topLeftButtonSpacing_, 
        calcEditorPanelVisibilityButtonLeft(), 
        topLeftButtonSize_ / 2, 
        SpriteID::ui_button_right
    );
    auto wb = std::weak_ptr<RoundIcon>(b);
    b->SetMouseDownHandler([this, wb](){
        auto b = wb.lock();
        if(b->GetIcon() == SpriteID::ui_button_right){
            b->SetIcon(SpriteID::ui_button_left);
            this->hideEditorPanel();
        }else{
            b->SetIcon(SpriteID::ui_button_right);
            this->showEditorPanel();
        }
        b->SetLeft(this->calcEditorPanelVisibilityButtonLeft());
    });
    b->SetWindowResizeHandler([this, wb](){
        wb.lock()->SetLeft(this->calcEditorPanelVisibilityButtonLeft());
    });
    menu_.push_back(b);
}

ui::pfloat GameScreen::calcEditorPanelVisibilityButtonLeft() const {
    return (100 - (editorPanelDiv_->IsVisible() ? ui::toVWFloat(editorPanelWidth_) : 0) 
        - ui::toVWFloat(topLeftButtonSpacing_) - ui::toVWFloat(topLeftButtonSize_)) VW;
}

void GameScreen::hideEditorPanel(){
    editorPanelDiv_->Hide();
}

void GameScreen::showEditorPanel(){
    editorPanelDiv_->Show();
    if(!timeTrial_) for(auto e: timeTrialElements_) e->Hide();
}

bool GameScreen::OnMouseScroll(float delta, float xw, float yh) {
    if(Screen::OnMouseScroll(delta, xw, yh)) return true;
    if(game_->OnMouseScroll(delta, xw, yh)) return true;
    return false;
}

bool GameScreen::OnMouseDown(const sf::Mouse::Button& e, float x, float y) {
    if(Screen::OnMouseDown(e, x, y)) return true;
    if(game_->OnMouseDown(e, x, y)) return true;
    return false;
}

bool GameScreen::OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
    if(Screen::OnMouseUp(e, x, y)) return true;
    if(game_->OnMouseUp(e, x, y)) return true;
    return false;
}

bool GameScreen::OnMouseMove(float x, float y) {
    bool b = Screen::OnMouseMove(x, y);
    return game_->OnMouseMove(x, y) || b;
}

bool GameScreen::OnKeyDown(const sf::Event::KeyEvent& e){
    if(Screen::OnKeyDown(e)) return true;
    return game_->OnKeyDown(e);
}

bool GameScreen::OnKeyUp(const sf::Event::KeyEvent& e){
    if(Screen::OnKeyUp(e)) return true;
    return game_->OnKeyUp(e);
}