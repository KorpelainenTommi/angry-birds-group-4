#include <ui/Element.hpp>

bool Element::isInside(float xw, float yh) const {
    float xvw = xw * 100;
    float yvh = yh * 100;
    float left = ui::toVWFloat(GetLeft());
    float top = ui::toVHFloat(GetTop());
    float right = ui::toVWFloat(w_) + left;
    float bottom = ui::toVHFloat(h_) + top;
    return visible_ && xvw > left && xvw < right && yvh > top && yvh < bottom 
        && isInsideCropArea(xvw, yvh);
};

bool Element::isInsideCropArea(float xvw, float yvh) const {
    if(!cropped_) return true;
    float left = ui::toVWFloat(cropArea_.left);
    float top = ui::toVHFloat(cropArea_.top);
    float right = ui::toVWFloat(cropArea_.width) + left;
    float bottom = ui::toVHFloat(cropArea_.height) + top;
    return xvw > left && xvw < right && yvh > top && yvh < bottom;
}

bool Element::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
    if((mouseDownHandler_ != NULL || captureFocus_) && isInside(xw, yh)) return true;
    return false;
}

bool Element::ClickSoundShouldBePlayed() const {
    return mouseDownHandler_ != NULL;
}

void Element::ExecuteOnMouseDown(){
    if(mouseDownHandler_ != NULL) mouseDownHandler_();
}

bool Element::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh){
    if(mouseUpHandler_ != NULL && isInside(xw, yh)){
        mouseUpHandler_();
        return true;
    }
    return false;
}

bool Element::OnMouseMove(float xw, float yh){
    bool isIn = isInside(xw, yh);
    if(isIn != mouseIn_){
        mouseIn_ = !mouseIn_;
        if(mouseEnterHandler_ != NULL && mouseIn_){
            mouseEnterHandler_();
            return true;
        }
        else if(mouseLeaveHandler_ != NULL && !mouseIn_){
            mouseLeaveHandler_();
            return true;
        }
    }
    if(isIn && title_.size() > 0){
        titleX_ = (xw * 100) VW;
        titleY_ = (yh * 100 - ui::toVHFloat(titleFontSize_)) VH;
        renderTitle = true;
    }else if(renderTitle && !isIn){
        renderTitle = false;
    }
    return false;
}

bool Element::OnMouseScroll(float delta, float xw, float yh){
    if(mouseScrollHandler_ != NULL && isInside(xw, yh)){
        mouseScrollHandler_(delta);
        return true;
    }
    return false;
}

void Element::OnWindowResize(){
    if(windowResizeHandler_ != NULL) windowResizeHandler_();
    if(title_.size() > 0) titleW_ = 0 VW;
}

void Element::Blur(){
    if(focused_){
        focused_ = false;
        if(focusChangeHandler_ != NULL) focusChangeHandler_(false);
    }
}

void Element::Focus(){
    if(!focused_){
        focused_ = true;
        if(focusChangeHandler_ != NULL) focusChangeHandler_(true);
    }
}

ui::pfloat Element::toVH(const ui::pfloat& p) const {
    return (toVHFloat(p)) VH;
}

ui::pfloat Element::toVW(const ui::pfloat& p) const {
    return (toVWFloat(p)) VW;
}

ui::pfloat Element::GetTop() const {
    return (toVHFloat(y_) + toVHFloat(offsetY_)) VH;
}

ui::pfloat Element::GetLeft() const {
    return (toVWFloat(x_) + toVWFloat(offsetX_)) VW;
}

void Element::SetTitle(const std::string& s){
    title_ = s;
    titleW_ = 0 VW;
}

bool Element::IsVisible() const {
    return visible_;
}
void Element::Hide(){
    visible_ = false;
}
void Element::Show(){
    visible_ = true;
}