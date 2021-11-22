#include <ui/Button.hpp>

void Button::Render(const RenderSystem& r){
    ui::pfloat top = GetTop();
    ui::pfloat left = GetLeft();
    ui::pfloat s = GetFontSize();
    ui::pfloat y = (toVHFloat(top) + (toVHFloat(h_) - toVHFloat(s)) / 2) VH;
    ColoredElement::Render(r);
    //requires updating
    if(cropped_) r.RenderText(text_, left, y, w_, s, textColor_, font_, align_);
    else r.RenderText(text_, left, y, w_, s, textColor_, font_, align_);
}