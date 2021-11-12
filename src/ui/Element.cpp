#include <ui/Element.hpp>

bool Element::OnMouseDown(const sf::Event::MouseButtonEvent& e){
    if(isInside(e)){
        if(mouseDownHandler_ != NULL) mouseDownHandler_();
        return true;
    }
    return false;
}

bool Element::OnMouseUp(const sf::Event::MouseButtonEvent& e){
    if(isInside(e)){
        if(mouseUpHandler_ != NULL) mouseUpHandler_();
        return true;
    }
    return false;
}

bool Element::OnMouseMove(const sf::Event::MouseMoveEvent& e){
    if(isInside(e) != mouseIn_){
        mouseIn_ = !mouseIn_;
        if(mouseEnterHandler_ != NULL && mouseIn_) mouseEnterHandler_();
        else if(mouseLeaveHandler_ != NULL && !mouseIn_) mouseLeaveHandler_();
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