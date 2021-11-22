#include <ui/ListElement.hpp>

//development
#include <iostream>

int ListElement::InsertElement(std::shared_ptr<Element> element){
    element->SetOffsetX(x_);
    element->SetCropArea({y_, x_, h_, w_});
    elements_[nextId_] = element;
    //std::cout << elements_.size() << std::endl;
    return nextId_++;
}

void ListElement::RemoveElement(int id){
    elements_.erase(id);
}

std::shared_ptr<Element> ListElement::GetElement(int id){
    return elements_[id];
}

void ListElement::Render(const RenderSystem& r){
    ColoredElement::Render(r);
    float h = GetTop();
    float s = toVHFloat(spacing_);
    //std::cout << "render" << std::endl;
    for(const auto t: elements_){
        auto e = t.second;
        e->SetTop(h VH);
        //std::cout << "top set " << h << std::endl;
        h += toVHFloat(e->GetHeight()) + s;
    }
}

bool ListElement::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
    if(isInside(xw, yh)){
        for(auto t: elements_){
            if(t.second->OnMouseDown(button, xw, yh)) return true;
        }
        if(mouseDownHandler_ != NULL){
            mouseDownHandler_();
            return true;
        }
    }
    return false;
}

bool ListElement::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh){
    if(isInside(xw, yh)){
        for(auto t: elements_){
            if(t.second->OnMouseUp(button, xw, yh)) return true;
        }
        if(mouseUpHandler_ != NULL){
            mouseUpHandler_();
            return true;
        }
    }
    return false;
}

bool ListElement::OnMouseMove(float xw, float yh){
    bool b = false;
    for(auto t: elements_){
        if(t.second->OnMouseMove(xw, yh)) b = true;
    }
    if(isInside(xw, yh) != mouseIn_){
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
    return b;
}

bool ListElement::OnMouseScroll(float delta, float xw, float yh){
    if(isInside(xw, yh)){
        float h = toVHFloat(h_);
        float s = toVHFloat(spacing_);
        for(auto t: elements_){
            if(t.second->OnMouseScroll(delta, xw, yh)) return true;
            h -= toVHFloat(t.second->GetHeight()) + s;
        }
        if(scrollOffset_.f >= 0 && delta * scrollMultiplier_ >= 0) return false;
        scrollOffset_ += (delta * scrollMultiplier_ / ui::windowHeight) VH;

        //set scroll limits
        if(scrollOffset_.f > 0) scrollOffset_ = 0 VH;
        if(scrollOffset_.f < h && h < 0) scrollOffset_ = h VH;

        for(auto t: elements_) t.second->SetOffsetY(scrollOffset_);
        return true;
    }
    return false;
}