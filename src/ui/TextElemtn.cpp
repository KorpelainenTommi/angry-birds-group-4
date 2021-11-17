#include <ui/TextElement.hpp>

void TextElement::SetRelativeFontSize(ui::pfloat& s){
    useRelativeFontSize_ = true;
    relativeFontSize_ = s;
}

void TextElement::SetAbsoluteFontSize(float s){
    useRelativeFontSize_ = false;
    absoluteFontSize_ = s;
}

ui::pfloat TextElement::GetFontSize(){
    if(useRelativeFontSize_) return relativeFontSize_;
    return (100 * absoluteFontSize_ / ui::windowHeight) VH;
}