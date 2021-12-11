#include <ui/ListElement.hpp>

#include <iostream>

int ListElement::InsertElement(std::shared_ptr<Element> element){
    elements_[nextId_] = element;
    updateValues();
    return nextId_++;
}

void ListElement::RemoveElement(int id){
    elements_.erase(id);
    OnWindowResize();
}

std::shared_ptr<Element> ListElement::GetElement(int id){
    return elements_[id];
}

bool ListElement::OnMouseMove(float xw, float yh){
    bool b = Element::OnMouseMove(xw, yh);
    lastMouseX_ = xw;
    lastMouseY_ = yh;
    return b;
}

bool ListElement::OnMouseScroll(float delta, float xw, float yh){
    if(isInside(xw, yh)){
        updateScrollOffset(delta, xw, yh);
        return true;
    }
    return false;
}

void ListElement::updateScrollOffset(float delta, float xw, float yh){
    float h = toVHFloat(h_);
    float s = toVHFloat(spacing_);
    for(auto t: elements_) h -= toVHFloat(t.second->GetHeight()) + s;
    h += s;
    float dtsm = delta * scrollMultiplier_;
    if(scrollOffset_.f == 0 && dtsm >= 0) return;
    else if(scrollOffset_.f == h && h < 0 && dtsm < 0) return;
    scrollOffset_ = (scrollOffset_.f + dtsm / ui::windowHeight) VH;

    //set scroll limits
    if(scrollOffset_.f > 0) scrollOffset_ = 0 VH;
    else if(scrollOffset_.f < h && h < 0) scrollOffset_ = h VH;
    else if(scrollOffset_.f < h) scrollOffset_ = 0 VH;

    for(auto t: elements_){
        t.second->SetOffsetY(scrollOffset_);
        t.second->OnMouseMove(xw, yh);
    }
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

void ListElement::updateValues(){
    ui::CropArea ca = calcCropArea();
    ui::pfloat offx = GetLeft();
    float h = toVHFloat(GetTop());
    float s = toVHFloat(spacing_);
    for(const auto t: elements_){
        auto e = t.second;
        e->SetTop(h VH);
        e->SetOffsetX(offx);
        e->SetCropArea(ca);
        h += toVHFloat(e->GetHeight()) + s;
    }
    updateScrollOffset(0, lastMouseX_, lastMouseY_);
}

ui::CropArea ListElement::calcCropArea() const {
    if(cropped_) return ui::combineCropAreas(cropArea_, {GetTop(), GetLeft(), h_, w_});
    return {GetTop(), GetLeft(), h_, w_};
}   

void ListElement::SetPosition(ui::pfloat x, ui::pfloat y){
    Element::SetPosition(x, y);
    updateValues();
}

void ListElement::SetTop(ui::pfloat top){
    Element::SetTop(top);
    updateValues();
}

void ListElement::SetLeft(ui::pfloat left){
    Element::SetLeft(left);
    updateValues();
}

void ListElement::SetSize(ui::pfloat w, ui::pfloat h){
    Element::SetSize(w, h);
    updateValues();
}

void ListElement::SetHeight(ui::pfloat height){
    Element::SetHeight(height);
    updateValues();
}

void ListElement::SetWidth(ui::pfloat width){
    Element::SetWidth(width);
    updateValues();
}

void ListElement::OnWindowResize(){
    Element::OnWindowResize();
    updateValues();
}

void ListElement::SetOffsetX(const ui::pfloat& ox){
    Element::SetOffsetX(ox);
    updateValues();
}
void ListElement::SetOffsetX(){
    Element::SetOffsetX();
    updateValues();
}

void ListElement::SetOffsetY(const ui::pfloat& oy){
    Element::SetOffsetY(oy);
    updateValues();
}
void ListElement::SetOffsetY(){
    Element::SetOffsetY();
    updateValues();
}

void ListElement::SetCropArea(const ui::CropArea& a){
    Element::SetCropArea(a);
    updateValues();
}
void ListElement::SetCropArea(){
    Element::SetCropArea();
    updateValues();
}

void ListElement::Hide(){
    visible_ = false;
    for(auto t: elements_) t.second->Hide();
}
void ListElement::Show(){
    visible_ = true;
    for(auto t: elements_) t.second->Show();
}