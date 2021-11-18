#include <ui/Button.hpp>

void Button::Render(const RenderSystem& r){
    r.RenderRect(backgroundColor_, x_, y_, w_, h_);
    ui::pfloat s = GetFontSize();
    auto y = (toVHFloat(y_) + (toVHFloat(h_) - toVHFloat(s)) / 2) VH;
    r.RenderText(text_, x_, y, w_, s, textColor_, font_, ui::TextAlign::center);
}