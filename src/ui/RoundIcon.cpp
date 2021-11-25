#include <ui/RoundIcon.hpp>

void RoundIcon::Render(const RenderSystem& r){
    ui::pfloat d = r_ * 2;
    r.RenderSprite(icon_, x_, y_, d, d);
}

/*
Undefined symbols for architecture x86_64:
"vtable for RoundIcon", referenced from:
GameScreen::GameScreen(Application&) in MainMenu.cpp.o
NOTE: a missing vtable usually means the first non-inline virtual member function has no definition.
ld: symbol(s) not found for architecture x86_64 
*/