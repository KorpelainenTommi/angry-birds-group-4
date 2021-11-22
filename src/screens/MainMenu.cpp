#include <screens/MainMenu.hpp>
#include <ui.hpp>

//development
#include <iostream>

MainMenu::MainMenu(Application& app): Screen(app){
    auto list = std::make_shared<ListElement>(0 VH, 0 VW, 100 VH, 74 VW);
    list->SetBackgroundColor(ui::backgroundColor2);
    menu_.push_back(list);

    auto level1 = std::make_shared<Button>(0 VH, 1 VW, 40 VH, 72 VW, [](){std::cout << "level1" << std::endl;});
    level1->SetText("level1");
    list->InsertElement(level1);
    menu_.push_back(level1);

    auto level2 = std::make_shared<Button>(0 VH, 1 VW, 40 VH, 72 VW, [](){std::cout << "level2" << std::endl;});
    level2->SetText("level2");
    list->InsertElement(level2);
    menu_.push_back(level2);

    auto level3 = std::make_shared<Button>(0 VH, 1 VW, 40 VH, 72 VW, [](){std::cout << "level3" << std::endl;});
    level3->SetText("level3");
    list->InsertElement(level3);
    menu_.push_back(level3);
}

void MainMenu::Render(const RenderSystem& r){
    //background
    r.RenderRect(ui::backgroundColor, 0 VW, 0 VH, 100 VW, 100 VH);

    for(const auto& e : menu_) e->Render(r);
}