#include <screens/MainMenu.hpp>
#include <Application.hpp>
#include <screens/GameScreen.hpp>

//development
#include <gameplay/TestLevel.hpp>

MainMenu::MainMenu(Application& app): Screen(app){
    addList();

    generateLevels();

    addRightSideButton(1, "Exit", [&app](){app.Exit();});
    addRightSideButton(2, "test level", [&app](){
        app.TransitionTo(std::make_unique<GameScreen>(app,TestLevel()));
    });
    addRightSideButton(3, "Edit", [&app, this](){
        app.TransitionTo(std::make_unique<GameScreen>(app, this->GetSelectedLevel(), true));
    }, true);
    addRightSideButton(4, "Play", [&app, this](){
        app.TransitionTo(std::make_unique<GameScreen>(app, this->GetSelectedLevel()));
    }, true);

    addScoreboard();
}

void MainMenu::Render(const RenderSystem& r){
    //background
    r.RenderRect(ui::backgroundColor, 0 VW, 0 VH, 100 VW, 100 VH);

    Screen::Render(r);
}

ui::pfloat MainMenu::calcListWidth() const {
    return (75.0F - ui::toVWFloat(spacingX_) / 2 - ui::toVWFloat(padding_)) VW;
}

ui::pfloat MainMenu::calcListElementWidth() const {
    return (ui::toVWFloat(calcListWidth()) - 2 * ui::toVWFloat(listPadding_)) VW;
}

void MainMenu::generateLevels(){
    auto list = app_.GetFileManager().ListLevels();
    list.push_back(TestLevel());
    for(auto e: list) addLevel(e);
}

void MainMenu::addLevel(Level level){
    auto e = std::make_shared<Button>(0 VH, listPadding_, 20 VH, calcListElementWidth());
    auto w = std::weak_ptr<Button>(e);
    e->SetMouseDownHandler([level, w, this](){
        this->SelectLevel(level, w);
    });
    e->SetText(level.levelName);
    e->SetRelativeFontSize(ui::defaultFontSize * 2.5);
    list_->InsertElement(e);
    menu_.push_back(e);
}

void MainMenu::SelectLevel(const Level& level, std::weak_ptr<Button> button){
    if(hasSelectedLevel_) selectedLevel_.second.lock()->SetBackgroundColor();
    else{
        hasSelectedLevel_ = true;
        for(auto e: deactivatingButtons_) e->Activate();
    }
    selectedLevel_ = {level, button};
    button.lock()->SetBackgroundColor(selectedLevelBackground_);
    scoreboard_->SetText(generateScoreboardText(level));
}

std::string MainMenu::generateScoreboardText(const Level& level) const {
    std::string s = "";
    for(auto e: level.highscores) s += "  " + e.first + ' ' + getString(e.second) + '\n';
    return s;
}

ui::pfloat MainMenu::calcRightSideElementWidth() const {
    return (25.0F - ui::toVWFloat(spacingX_) / 2 - ui::toVWFloat(padding_)) VW;
}

ui::pfloat MainMenu::calcRightSideButtonTop(unsigned char buttonNumber) const {
    float s = ui::toVHFloat(spacingY_);
    return (100 - ui::toVHFloat(padding_) - (ui::toVHFloat(buttonHeight_) + s) * buttonNumber + s) VH;
}

void MainMenu::addRightSideButton(
    unsigned char buttonNumber, 
    const std::string& text,
    const std::function<void()> mouseDownHandler,
    bool deactivating
){
    if(buttonNumber > nofButtons_) nofButtons_ = buttonNumber;
    auto e = std::make_shared<Button>(
        calcRightSideButtonTop(buttonNumber), 
        calcRightSideLeft(), 
        buttonHeight_, 
        calcRightSideElementWidth(), 
        mouseDownHandler
    );
    e->SetText(text);
    e->SetRelativeFontSize(ui::defaultFontSize * 1.5);
    auto we = std::weak_ptr<Button>(e);
    e->SetWindowResizeHandler([this, we, buttonNumber](){
        auto e = we.lock();
        e->SetPosition(
            this->calcRightSideLeft(),
            this->calcRightSideButtonTop(buttonNumber)
        );
        e->SetWidth(this->calcRightSideElementWidth());
    });
    if(deactivating){
        deactivatingButtons_.push_back(e);
        e->Deactivate();
    }
    menu_.push_back(e);
}

ui::pfloat MainMenu::calcRightSideLeft() const {
    return (75.0F + ui::toVWFloat(spacingX_) / 2) VW;
}

void MainMenu::addScoreboard(){
    auto h = std::weak_ptr<TextElement>(addScoreboardHeader());
    auto m = addScoreboardMultiline();
    h.lock()->SetWindowResizeHandler([this, h, m](){
        ui::pfloat w = this->calcRightSideElementWidth();
        ui::pfloat l = this->calcRightSideLeft();
        auto he = h.lock();
        he->SetLeft(l);
        he->SetWidth(w);
        m->SetPosition(l, this->calcScoreboardMultilineTop());
        m->SetSize(w, this->calcScoreboardMultilineHeight());
    });
}

std::shared_ptr<TextElement> MainMenu::addScoreboardHeader(){
    auto header = std::make_shared<TextElement>(
        padding_, 
        calcRightSideLeft(),  
        scoreboardHeaderSize_,
        calcRightSideElementWidth()
    );
    menu_.push_back(header);
    header->SetBackgroundColor(ui::backgroundColor2);
    header->SetText("Scoreboard");
    header->SetTextAlign(ui::TextAlign::center);
    header->SetRelativeFontSize(scoreboardHeaderSize_ / 2);
    return header;
}

ui::pfloat MainMenu::calcScoreboardMultilineTop() const {
    return (ui::toVHFloat(padding_) + ui::toVHFloat(scoreboardHeaderSize_)) VH;
}

ui::pfloat MainMenu::calcScoreboardMultilineHeight() const {
    return (100 - ui::toVHFloat(padding_) * 2 - ui::toVHFloat(scoreboardHeaderSize_) 
        - (ui::toVHFloat(buttonHeight_) + ui::toVHFloat(spacingY_)) * nofButtons_) VH;
}

std::shared_ptr<MultilineText> MainMenu::addScoreboardMultiline(){
    scoreboard_ = std::make_shared<MultilineText>(
        calcScoreboardMultilineTop(),
        calcRightSideLeft(),
        calcScoreboardMultilineHeight(),
        calcRightSideElementWidth()
    );
    menu_.push_back(scoreboard_);
    scoreboard_->SetBackgroundColor(ui::backgroundColor2);
    scoreboard_->SetRelativeFontSize(ui::defaultFontSize * 1.3);
    return scoreboard_;
}

ui::pfloat MainMenu::calcListTop() const {
    return (ui::toVHFloat(padding_) + ui::toVHFloat(listPadding_)) VH;
}

ui::pfloat MainMenu::calcListHeight() const {
    return (100 - 2 * ui::toVHFloat(listPadding_) - 2 * ui::toVHFloat(padding_)) VH;
}

ui::pfloat MainMenu::calcListBottomTop() const {
    return (100 - ui::toVHFloat(padding_) - ui::toVHFloat(listPadding_)) VH;
}

std::shared_ptr<ListElement> MainMenu::addList(){
    auto li = std::weak_ptr<ListElement>(addListBody());
    auto liTop = addListTop();
    auto liBottom = addListBottom();

    list_->SetWindowResizeHandler([this, li, liTop, liBottom](){
        auto list = li.lock();
        ui::pfloat w = this->calcListWidth();
        list->SetTop(this->calcListTop());
        list->SetSize(
            w,
            this->calcListHeight()
        );
        liTop->SetWidth(w);
        liBottom->SetWidth(w);
        liBottom->SetTop(this->calcListBottomTop());
        ui::pfloat ew = this->calcListElementWidth();
        ui::CropArea ca = {list->GetTop(), list->GetLeft(), list->GetHeight(), list->GetWidth()};
        if(list->IsCropped()) ca = ui::combineCropAreas(ca, list->GetCropArea());
        for(auto e: list->GetElements()){
            e.second->SetWidth(ew);
            e.second->SetCropArea(ca);
        }
    });
    return list_;
}

std::shared_ptr<ListElement> MainMenu::addListBody(){
    list_ = std::make_shared<ListElement>(
        calcListTop(), 
        padding_, 
        calcListHeight(), 
        calcListWidth()
    );
    list_->SetWidth(calcListWidth());
    list_->SetBackgroundColor(ui::backgroundColor2);
    list_->SetSpacing(listSpacing_);
    menu_.push_back(list_);
    return list_;
}

std::shared_ptr<ColoredElement> MainMenu::addListTop(){
    listTop_ = std::make_shared<ColoredElement>(padding_, padding_, listPadding_, calcListWidth());
    listTop_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(listTop_);
    return listTop_;
}

std::shared_ptr<ColoredElement> MainMenu::addListBottom(){
    listBottom_ = std::make_shared<ColoredElement>(
        (padding_.f + ui::toVHFloat(listPadding_) + list_->GetHeight().f) VH, 
        padding_, 
        listPadding_, 
        calcListWidth()
    );
    listBottom_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(listBottom_);
    return listBottom_;
}