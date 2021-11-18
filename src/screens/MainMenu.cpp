#include <screens/MainMenu.hpp>

MainMenu::MainMenu(Application& app): Screen(app){

}

void MainMenu::Render(const RenderSystem& r){
    //background
    r.RenderRect(ui::backgroundColor, 0 VW, 0 VH, 100 VW, 100 VH);

    for(const auto& e : menu_) e->Render(r);
}