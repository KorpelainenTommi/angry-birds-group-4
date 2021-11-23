#include <screens/MainMenu.hpp>
#include <ui/Button.hpp>
#include <Application.hpp>
#include <screens/GameScreen.hpp>

//development
#include <iostream>

MainMenu::MainMenu(Application& app): Screen(app){
    list_ = std::make_shared<ListElement>(3 VH, 2 VH, 94 VH, curListW_);
    curListW_ = calcListWidth();
    curElementW_ = calcListElementWidth();
    list_->SetWidth(curListW_);
    list_->SetBackgroundColor(ui::backgroundColor2);
    list_->SetSpacing(listSpacing_);
    menu_.push_back(list_);

    listTop_ = std::make_shared<ColoredElement>(2 VH, 2 VH, 1 VH, curListW_);
    listTop_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(listTop_);

    listBottom_ = std::make_shared<ColoredElement>(97 VH, 2 VH, 1 VH, curListW_);
    listBottom_->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(listBottom_);

    addLevel("level1");
    menu_[menu_.size() - 1]->SetMouseDownHandler([&app](){
        std::cout << "level1" << std::endl;
        app.TransitionTo(std::make_unique<GameScreen>(app));
    });

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
    return (74.0F - list_->toVWFloat(list_->GetLeft())) VW;
}

ui::pfloat MainMenu::calcListElementWidth() const {
    return (list_->toVWFloat(curListW_) - 2 * list_->toVWFloat(listSpacing_)) VW;
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
    auto e = std::make_shared<Button>(0 VH, listSpacing_, 20 VH, curElementW_, [level](){
        std::cout << level << std::endl;
    });
    e->SetText(level);
    list_->InsertElement(e);
    menu_.push_back(e);
}