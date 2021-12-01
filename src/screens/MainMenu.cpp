#include <screens/MainMenu.hpp>
#include <Application.hpp>
#include <screens/GameScreen.hpp>

//development
#include <gameplay/TestLevel.hpp>

MainMenu::MainMenu(Application& app): Screen(app){
    addList();

    generateLevels();

    addRightSideButton("Exit", [&app](){app.Exit();});
    addRightSideButton("test level", [&app](){
        app.TransitionTo(std::make_unique<GameScreen>(app,TestLevel()));
    });
    addRightSideButton("Play", [&app, this](){
        app.TransitionTo(std::make_unique<GameScreen>(app, this->GetSelectedLevel()));
    }, true);

    addScoreboard();
    scoreboard_->SetText("  Some\n  text\n  here\n  to\n  try\n  this\n  out");
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

/*void MainMenu::checkListWidth(){
    ui::pfloat w = calcListWidth();
    if(w.f == curListW_.f) return;
    curListW_ = w;
    list_->SetWidth(w);
    listTop_->SetWidth(w);
    listBottom_->SetWidth(w);
    curElementW_ = calcListElementWidth();
    for(auto e: list_->GetElements()) e.second->SetWidth(curElementW_);
}*/

void MainMenu::generateLevels(){
    auto list = std::vector<Level>();//app_.GetFileManager().ListLevels();
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

/*void MainMenu::checkRightSideElementWidth(){
    ui::pfloat w = calcRightSideElementWidth();
    if(w.f == rightSideElementW_.f) return;
    rightSideElementW_ = w;
    for(auto e: rightSideElements_) e->SetWidth(w);
}*/

void MainMenu::addRightSideButton(
    const std::string& text,
    const std::function<void()> mouseDownHandler,
    bool deactivating
){
    auto e = std::make_shared<Button>(
        (getRightSideButtonsVHFloatHeight() - ui::toVHFloat(buttonHeight_)) VH, 
        getRightSideLeft(), 
        buttonHeight_, 
        calcRightSideElementWidth(), 
        mouseDownHandler
    );
    e->SetText(text);
    e->SetRelativeFontSize(ui::defaultFontSize * 1.5);
    

    rightSideElements_.push_back(e);
    if(deactivating){
        deactivatingButtons_.push_back(e);
        e->Deactivate();
    }
    menu_.push_back(e);
}

ui::pfloat MainMenu::getRightSideLeft() const {
    return (75.0F + ui::toVWFloat(spacingX_) / 2) VW;
}

float MainMenu::getRightSideButtonsVHFloatHeight() const {
    return (100 - rightSideElements_.size() * (ui::toVHFloat(buttonHeight_) 
        + ui::toVHFloat(spacingY_)) - ui::toVHFloat(padding_));
}

void MainMenu::addScoreboard(){
    ui::pfloat left = getRightSideLeft();
    float pf = ui::toVHFloat(padding_);
    float hl = getRightSideButtonsVHFloatHeight() - pf;
    float hh = addScoreboardHeader(left);
    hl -= hh;
    addScoreboardMultiline((pf + hh) VH, left, hl VH);
}

float MainMenu::addScoreboardHeader(const ui::pfloat& left){
    auto header = std::make_shared<TextElement>(
        padding_, 
        left,  
        1 VH,
        calcRightSideElementWidth()
    );
    rightSideElements_.push_back(header);
    menu_.push_back(header);
    header->SetBackgroundColor(ui::backgroundColor2);
    header->SetText("Scoreboard");
    header->SetTextAlign(ui::TextAlign::center);
    header->SetRelativeFontSize(ui::defaultFontSize * 2);
    float hh = ui::toVHFloat(header->GetFontSize()) * 2;
    header->SetHeight(hh VH);
    return hh;
}

void MainMenu::addScoreboardMultiline(
    const ui::pfloat& top, const ui::pfloat& left, const ui::pfloat& height
){
    scoreboard_ = std::make_shared<MultilineText>(
        top,
        left,
        height,
        calcRightSideElementWidth()
    );
    rightSideElements_.push_back(scoreboard_);
    menu_.push_back(scoreboard_);
    scoreboard_->SetBackgroundColor(ui::backgroundColor2);
    scoreboard_->SetRelativeFontSize(ui::defaultFontSize * 1.3);
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
        (padding_.f + list_->toVHFloat(listPadding_) + list_->GetHeight().f) VH, 
        padding_, 
        listPadding_, 
        calcListWidth()
    );
    listBottom_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(listBottom_);
    return listBottom_;
}