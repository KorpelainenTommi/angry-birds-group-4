#include <ui/TextElement.hpp>

void TextElement::SetRelativeFontSize(const ui::pfloat& s){
    useRelativeFontSize_ = true;
    relativeFontSize_ = s;
}

void TextElement::SetAbsoluteFontSize(float s){
    useRelativeFontSize_ = false;
    absoluteFontSize_ = s;
}

ui::pfloat TextElement::GetFontSize(){
    if(useRelativeFontSize_) return relativeFontSize_;
    return (100.0F * absoluteFontSize_ / ui::windowHeight) VH;
}

//Simply copied from Button render, replace with better implementation
void TextElement::Render(const RenderSystem& r){
    r.RenderRect(backgroundColor_, x_, y_, w_, h_);
    ui::pfloat s = GetFontSize();
    auto y = (toVHFloat(y_) + (toVHFloat(h_) - toVHFloat(s)) / 2) VH;
    r.RenderText(text_, x_, y, w_, s, textColor_, font_, ui::TextAlign::center);
}