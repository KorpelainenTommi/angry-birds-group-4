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

void TextElement::Render(const RenderSystem& r){
    ui::pfloat top = GetTop();
    ui::pfloat left = GetLeft();
    ui::pfloat s = GetFontSize();
    ui::pfloat y = (toVHFloat(top) + (toVHFloat(h_) - toVHFloat(s)) / 2) VH;
    if(cropped_){
        r.RenderRect(backgroundColor_, left, top, w_, h_, cropArea_);
        r.RenderText(text_, left, y, w_, s, cropArea_, textColor_, font_ , align_);
    }else{
        r.RenderRect(backgroundColor_, left, top, w_, h_);
        r.RenderText(text_, left, y, w_, s, textColor_, font_ , align_);
    }
}