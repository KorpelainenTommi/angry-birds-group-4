#include <screens/MainMenu.hpp>
#include <Application.hpp>
#include <screens/GameScreen.hpp>

//development
#include <iostream>

MainMenu::MainMenu(Application& app): Screen(app){
    list_ = std::make_shared<ListElement>(
        (padding_.f + listPadding_.f) VH, padding_, (100 - 2 * listPadding_.f - 2 * padding_.f) VH, curListW_
    );
    curListW_ = calcListWidth();
    curElementW_ = calcListElementWidth();
    list_->SetWidth(curListW_);
    list_->SetBackgroundColor(ui::backgroundColor2);
    list_->SetSpacing(listSpacing_);
    menu_.push_back(list_);

    listTop_ = std::make_shared<ColoredElement>(padding_, padding_, listPadding_, curListW_);
    listTop_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(listTop_);

    listBottom_ = std::make_shared<ColoredElement>(
        (padding_.f + list_->toVHFloat(listPadding_) + list_->GetHeight().f) VH, 
        padding_, 
        listPadding_, 
        curListW_
    );
    listBottom_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(listBottom_);

    addLevel("level1");
    /*menu_[menu_.size() - 1]->SetMouseDownHandler([&app](){
        std::cout << "level1" << std::endl;
        app.TransitionTo(std::make_unique<GameScreen>(app));
    });*/

    addLevel("level2");
    addLevel("level3");
    addLevel("level4");
    addLevel("level5");
    addLevel("level6");
    addLevel("level7");
    addLevel("level8");
    addLevel("level9");

    
}

void MainMenu::Render(const RenderSystem& r){
    //background
    r.RenderRect(ui::backgroundColor, 0 VW, 0 VH, 100 VW, 100 VH);

    checkListWidth();

    for(const auto& e : menu_) e->Render(r);
}

ui::pfloat MainMenu::calcListWidth() const {
    return (74.5F - list_->toVWFloat(padding_)) VW;
}

ui::pfloat MainMenu::calcListElementWidth() const {
    return (list_->toVWFloat(curListW_) - 2 * list_->toVWFloat(listPadding_)) VW;
}

void MainMenu::checkListWidth(){
    ui::pfloat w = calcListWidth();
    if(w.f == curListW_.f) return;
    curListW_ = w;
    list_->SetWidth(w);
    listTop_->SetWidth(w);
    listBottom_->SetWidth(w);
    curElementW_ = calcListElementWidth();
    for(auto e: list_->GetElements()) e.second->SetWidth(curElementW_);
}

void MainMenu::addLevel(std::string level){
    auto e = std::make_shared<Button>(0 VH, listPadding_, 20 VH, curElementW_);
    auto w = std::weak_ptr<Button>(e);
    e->SetMouseDownHandler([level, w, this](){
        std::cout << level << std::endl;
        this->SelectLevel(level, w);
    });
    e->SetText(level);
    //e->SetMouseEnterHandler([e](){e->SetBackgroundColor({0, 100, 200});});
    //e->SetMouseLeaveHandler([e](){e->SetBackgroundColor();});
    list_->InsertElement(e);
    menu_.push_back(e);
}

void MainMenu::SelectLevel(const std::string level, std::weak_ptr<Button> button){
    if(hasSelectedLevel_) selectedLevel_.second.lock()->SetBackgroundColor();
    else hasSelectedLevel_ = true;
    selectedLevel_ = {level, button};
    button.lock()->SetBackgroundColor(selectedLevelBackground_);
}

ui::pfloat MainMenu::calcRightSideElementWidth() const {
    return (24.5 - list_->toVWFloat(padding_)) VW;
}

void MainMenu::addRightSideButton(
    const ui::pfloat& top, 
    const ui::pfloat& left, 
    const ui::pfloat& height, 
    const ui::pfloat& width, 
    const std::function<void()> mouseDownHandler
){
    auto e = std::make_shared<Button>(top, left, height, width, mouseDownHandler);
    e->SetWidth(rightSideElementW_);
    rightSideElements_.push_back(e);
    menu_.push_back(e);
}