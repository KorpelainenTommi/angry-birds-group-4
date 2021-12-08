#include <ui/DivElement.hpp>

void DivElement::updateValues(){
    ui::pfloat offx = GetLeft();
    ui::pfloat offy = GetTop();
    for(auto e: elements_){
        e.second->SetOffsetX(offx);
        e.second->SetOffsetY(offy);
        if(cropped_) e.second->SetCropArea(cropArea_);
    }
}

int DivElement::InsertElement(std::shared_ptr<Element> element){
    element->SetOffsetX(GetLeft());
    element->SetOffsetY(GetTop());
    if(cropped_) element->SetCropArea(cropArea_);
    elements_[nextId_] = element;
    return nextId_++;
}

void DivElement::RemoveElement(int id){
    elements_.erase(id);
}

std::shared_ptr<Element> DivElement::GetElement(int id){
    return elements_[id];
}

const std::map<int, std::shared_ptr<Element>>& DivElement::GetElements() const {
    return elements_;
}

void DivElement::ClearElements(){
    elements_.clear();
}

void DivElement::SetPosition(ui::pfloat x, ui::pfloat y){
    Element::SetPosition(x, y);
    updateValues();
}

void DivElement::SetTop(ui::pfloat top){
    Element::SetTop(top);
    updateValues();
}

void DivElement::SetLeft(ui::pfloat left){
    Element::SetLeft(left);
    updateValues();
}

void DivElement::SetSize(ui::pfloat w, ui::pfloat h){
    Element::SetSize(w, h);
    updateValues();
}

void DivElement::SetHeight(ui::pfloat height){
    Element::SetHeight(height);
    updateValues();
}

void DivElement::SetWidth(ui::pfloat width){
    Element::SetWidth(width);
    updateValues();
}

void DivElement::OnWindowResize(){
    Element::OnWindowResize();
    updateValues();
}

void DivElement::SetOffsetX(const ui::pfloat& ox){
    Element::SetOffsetX(ox);
    updateValues();
}
void DivElement::SetOffsetX(){
    Element::SetOffsetX();
    updateValues();
}

void DivElement::SetOffsetY(const ui::pfloat& oy){
    Element::SetOffsetY(oy);
    updateValues();
}
void DivElement::SetOffsetY(){
    Element::SetOffsetY();
    updateValues();
}

void DivElement::SetCropArea(const ui::CropArea& a){
    Element::SetCropArea(a);
    updateValues();
}
void DivElement::SetCropArea(){
    Element::SetCropArea();
    updateValues();
}