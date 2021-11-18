#include <screens/MainMenu.hpp>
#include <ui/ListElement.hpp>

MainMenu::MainMenu(Application& app): Screen(app){
    auto list = std::make_unique<ListElement>(0 VH, 0 VW, 100 VH, 74 VW);
    list->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(std::move(list));
}

void MainMenu::Render(const RenderSystem& r){
    //background
    r.RenderRect(ui::backgroundColor, 0 VW, 0 VH, 100 VW, 100 VH);

    for(const auto& e : menu_) e->Render(r);
}