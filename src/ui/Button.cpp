#include <ui/Button.hpp>

void Button::Render(const RenderSystem& r){
    ui::pfloat top = GetTop();
    ui::pfloat left = GetLeft();
    ui::pfloat s = GetFontSize();
    ui::pfloat y = (toVHFloat(top) + (toVHFloat(h_) - toVHFloat(s)) / 2) VH;
    if(cropped_){
        r.RenderRect(
            active_ ? backgroundColor_ : deactivatedBackgroundColor_, left, top, w_, h_, cropArea_
        );
        r.RenderText(text_, left, y, w_, s, cropArea_, textColor_, font_ , align_);
    }else{
        r.RenderRect(active_ ? backgroundColor_ : deactivatedBackgroundColor_, left, top, w_, h_);
        r.RenderText(text_, left, y, w_, s, textColor_, font_ , align_);
    }
}

bool Button::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
    if(mouseDownHandler_ != NULL && isInside(xw, yh)){
        if(active_) mouseDownHandler_();
        return true;
    }
    return false;
}

bool Button::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh){
    if(mouseUpHandler_ != NULL && isInside(xw, yh)){
        if(active_) mouseUpHandler_();
        return true;
    }
    return false;
}