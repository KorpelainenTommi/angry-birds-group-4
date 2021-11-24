#include <ui/MultilineText.hpp>

void MultilineText::SetText(const std::string& s){
    lines_.clear();
    std::size_t len = s.size();
    std::string buffer = "";
    for(std::size_t i = 0; i < len; i++){
        if(s[i] == '\n'){
            lines_.push_back(buffer);
            buffer = "";
        }else{
            buffer += "";
        }
    }
    lines_.push_back(buffer);
}

void MultilineText::Render(const RenderSystem& r){
    ui::pfloat top = GetTop();
    ui::pfloat left = GetLeft();
    ui::pfloat s = GetFontSize();
    if(cropped_) r.RenderRect(backgroundColor_, left, top, w_, h_, cropArea_);
    else r.RenderRect(backgroundColor_, left, top, w_, h_);
    float dy = ui::toVHFloat(GetLineSpacing()) + ui::toVHFloat(s);
    float y = ui::toVHFloat(top);
    for(auto line: lines_){
        if(useRelativeLineSpacing_) r.RenderText(line, left, y VH, w_, s, cropArea_, textColor_, font_, align_);
        else r.RenderText(line, left, y VH, w_, s, textColor_, font_, align_);
        y += dy;
    }
}

void MultilineText::SetRelativeLineSpacing(const ui::pfloat& s){
    useRelativeLineSpacing_ = true;
    relativeLineSpacing_ = s;
}

void MultilineText::SetAbsoluteLineSpacing(float s){
    useRelativeLineSpacing_ = false;
    absoluteLineSpacing_ = s;
}

ui::pfloat MultilineText::GetLineSpacing(){
    if(useRelativeLineSpacing_) return relativeLineSpacing_;
    return (100.0F * absoluteLineSpacing_ / ui::windowHeight) VH;
}