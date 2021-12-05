#include <ui/ListElement.hpp>

#include <iostream>

int ListElement::InsertElement(std::shared_ptr<Element> element){
    element->SetOffsetX(x_);
    element->SetCropArea({GetTop(), GetLeft(), h_, w_});
    elements_[nextId_] = element;
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
    float h = toVHFloat(GetTop());
    float s = toVHFloat(spacing_);
    for(const auto t: elements_){
        auto e = t.second;
        e->SetTop(h VH);
        h += toVHFloat(e->GetHeight()) + s;
    }
}

void ListElement::SetCropArea(){
    cropped_ = false;
    ui::CropArea ca = {GetTop(), GetLeft(), h_, w_};
    for(auto t: elements_) t.second->SetCropArea(ca);
}

bool ListElement::OnMouseScroll(float delta, float xw, float yh){
    if(isInside(xw, yh)){
        float h = toVHFloat(h_);
        float s = toVHFloat(spacing_);
        for(auto t: elements_){
            //if(t.second->OnMouseScroll(delta, xw, yh)) return true;
            h -= toVHFloat(t.second->GetHeight()) + s;
        }
        h += s;
        if(scrollOffset_.f >= 0 && delta * scrollMultiplier_ >= 0) return true;
        scrollOffset_ += (delta * scrollMultiplier_ / ui::windowHeight) VH;

        //set scroll limits
        if(scrollOffset_.f > 0) scrollOffset_ = 0 VH;
        else if(scrollOffset_.f < h && h < 0) scrollOffset_ = h VH;
        else if(scrollOffset_.f < h) scrollOffset_ = 0 VH;

        for(auto t: elements_){
            t.second->SetOffsetY(scrollOffset_);
            t.second->OnMouseMove(xw, yh);
        }
        return true;
    }
    return false;
}

void ListElement::SetSpacing(const ui::pfloat& s){
    spacing_ = s;
}

const std::map<int, std::shared_ptr<Element>>& ListElement::GetElements() const {
    return elements_;
}

void ListElement::ClearElements(){
    elements_.clear();
}