#include <ui/TextLine.hpp>

void TextLine::Render(const RenderSystem& r){
    ui::pfloat top = GetTop();
    ui::pfloat left = GetLeft();
    r.RenderRect(backgroundColor_, left, top, w_, h_);
    ui::pfloat s = GetFontSize();
    r.RenderText(text_, left, top, w_, s, textColor_, font_, ui::TextAlign::left);
}