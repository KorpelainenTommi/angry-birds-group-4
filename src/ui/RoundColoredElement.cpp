#include <ui/RoundColoredElement.hpp>

void RoundColoredElement::Render(const RenderSystem& r){
    ui::pfloat d = r_ * 2;
    r.RenderOval(backgroundColor_, x_, y_, d, d);
}