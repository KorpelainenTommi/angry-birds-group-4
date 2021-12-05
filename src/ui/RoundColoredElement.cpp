#include <ui/RoundColoredElement.hpp>

void RoundColoredElement::Render(const RenderSystem& r){
    ui::pfloat d = r_ * 2;
    if(cropped_) r.RenderOval(backgroundColor_, GetLeft(), GetTop(), d, d, cropArea_);
    else r.RenderOval(backgroundColor_, GetLeft(), GetTop(), d, d);
}