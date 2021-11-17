#include <ui/Element.hpp>

bool Element::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
    if(isInside(xw, yh)){
        if(mouseDownHandler_ != NULL) mouseDownHandler_();
        return true;
    }
    return false;
}

bool Element::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh){
    if(isInside(xw, yh)){
        if(mouseUpHandler_ != NULL) mouseUpHandler_();
        return true;
    }
    return false;
}

bool Element::OnMouseMove(float xw, float yh){
    if(isInside(xw, yh) != mouseIn_){
        mouseIn_ = !mouseIn_;
        if(mouseEnterHandler_ != NULL && mouseIn_) mouseEnterHandler_();
        else if(mouseLeaveHandler_ != NULL && !mouseIn_) mouseLeaveHandler_();
    }
    return false;
}

bool Element::OnMouseScroll(float delta, float xw, float yh){
    if(isInside(xw, yh)){
        if(mouseScrollHandler_ != NULL) mouseScrollHandler_(delta);
        return true;
    }
    return false;
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