#include <ui/InputElement.hpp>

void InputElement::write(char c){
    value_.insert(caretPos_++, 1, c);
    modified_ = true;
}

void InputElement::backspace(){
    if(caretPos_ == 0) return;
    value_.erase(--caretPos_, 1);
    modified_ = true;
}

void InputElement::moveCaretRight(){
    if(caretPos_ >= value_.size()) return;
    caretPos_++;
    modified_ = true;
}

void InputElement::moveCaretLeft(){
    if(caretPos_ <= 0) return;
    caretPos_--;
    modified_ = true;
}

bool InputElement::OnKeyDown(const sf::Event::KeyEvent& e){
    if(!focused_ || e.alt || e.control || e.shift || e.system) return false;
    switch(e.code){
        case 59:
            backspace();
            return true;
        case 72:
            moveCaretRight();
            return true;
        case 71:
            moveCaretLeft();
            return true;
        default:
            return false;
    }
}

bool InputElement::OnTextEntered(const sf::Event::TextEvent& e){
    if(!focused_) return false;
    char c = getChar(e.unicode);
    if(c){
        write(c);
        return true;
    }
    return false;
}

char InputElement::getChar(sf::Uint32 u) const {
    if(u >= 32 && u <= 126) return u;
    return 0;
}

void InputElement::SetText(const std::string& s){
    value_ = s;
    caretPos_ = s.size();
    modified_ = true;
}

std::string InputElement::GetText() const {
    return value_;
}

void InputElement::updateInputRenderingValues(const RenderSystem& r){
    modified_ = false;
    float cl = ui::toVHFloat(r.MeasureText(value_.substr(0, caretPos_), fontSize_, fontSize_.p, font_));
    float b = ui::toVHFloat(fontSize_) / 2;
    float w = ui::toVHFloat(w_) - b;
    float off = ui::toVHFloat(textOffset_);
    float clpoff = cl + off;
    float v;
    if(clpoff < b) v = off - clpoff + b;
    else if(clpoff > w) v = off - clpoff + w;
    else{
        caretOffset_ = clpoff VH;
        return;
    }
    textOffset_ = v VH;
    caretOffset_ = (cl + v) VH;
}

void InputElement::Render(const RenderSystem& r){
    if(modified_) updateInputRenderingValues(r);
    ColoredElement::Render(r);
    float l = GetLeft();
    ui::pfloat t = (ui::toVHFloat(GetTop()) + (ui::toVHFloat(h_) - ui::toVHFloat(fontSize_)) / 2) VH;
    r.RenderText(
        value_, 
        (l + ui::toVHFloat(textOffset_)) VH, 
        t, 
        w_, 
        fontSize_, 
        inputArea_, 
        textColor_, 
        font_, 
        ui::TextAlign::left
    );
    if(focused_) r.RenderRect(
        caretColor_, 
        (l + ui::toVHFloat(caretOffset_)) VH, 
        t, 
        caretWidth_, 
        fontSize_, 
        inputArea_
    );
}

void InputElement::updateInputArea(){
    inputArea_ = {GetTop(), GetLeft(), h_, w_};
    if(cropped_) inputArea_ = ui::combineCropAreas(inputArea_, cropArea_);
}

void InputElement::SetPosition(ui::pfloat x, ui::pfloat y){
    Element::SetPosition(x, y);
    updateInputArea();
}

void InputElement::SetTop(ui::pfloat top){
    Element::SetTop(top);
    updateInputArea();
}

void InputElement::SetLeft(ui::pfloat left){
    Element::SetLeft(left);
    updateInputArea();
}

void InputElement::SetSize(ui::pfloat w, ui::pfloat h){
    Element::SetSize(w, h);
    updateInputArea();
    modified_ = true;
}

void InputElement::SetHeight(ui::pfloat height){
    Element::SetHeight(height);
    updateInputArea();
}

void InputElement::SetWidth(ui::pfloat width){
    Element::SetWidth(width);
    updateInputArea();
    modified_ = true;
}

void InputElement::OnWindowResize(){
    Element::OnWindowResize();
    updateInputArea();
    modified_ = true;
}

void InputElement::SetOffsetX(const ui::pfloat& ox){
    Element::SetOffsetX(ox);
    updateInputArea();
}
void InputElement::SetOffsetX(){
    Element::SetOffsetX();
    updateInputArea();
}

void InputElement::SetOffsetY(const ui::pfloat& oy){
    Element::SetOffsetY(oy);
    updateInputArea();
}
void InputElement::SetOffsetY(){
    Element::SetOffsetY();
    updateInputArea();
}

void InputElement::SetCropArea(const ui::CropArea& a){
    Element::SetCropArea(a);
    updateInputArea();
}
void InputElement::SetCropArea(){
    Element::SetCropArea();
    updateInputArea();
}

void InputElement::SetFont(FontID f){
    font_ = f;
    modified_ = true;
}

void InputElement::SetFontSize(const ui::pfloat& s){
    fontSize_ = s;
    modified_ = true;
}