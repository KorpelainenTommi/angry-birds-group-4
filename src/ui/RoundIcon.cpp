#include <ui/RoundIcon.hpp>

void RoundIcon::Render(const RenderSystem& r){
    ui::pfloat d = r_ * 2;
    r.RenderSprite(icon_, x_, y_, d, d);
}