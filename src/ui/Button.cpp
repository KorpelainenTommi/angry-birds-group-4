#include <ui/Button.hpp>

void Button::Render(const RenderSystem& r){
    ui::pfloat top = GetTop();
    ui::pfloat left = GetLeft();
    r.RenderRect(backgroundColor_, left, top, w_, h_);
    ui::pfloat s = GetFontSize();
    ui::pfloat y = (toVHFloat(top) + (toVHFloat(h_) - toVHFloat(s)) / 2) VH;
    r.RenderText(text_, left, y, w_, s, textColor_, font_, align_);
}