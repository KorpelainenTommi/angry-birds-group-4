#include <ui/TextLine.hpp>

void TextLine::Render(const RenderSystem& r){
    ui::pfloat top = GetTop();
    ui::pfloat left = GetLeft();
    ui::pfloat s = GetFontSize();
    ColoredElement::Render(r);
    //requires updating
    if(cropped_) r.RenderText(text_, left, top, w_, s, textColor_, font_, align_);
    else r.RenderText(text_, left, top, w_, s, textColor_, font_, align_);
}