#include <ui/MessageBox.hpp>

void MessageBox::Render(const RenderSystem& r){
    r.RenderRect(ui::messageBoxBackgroundColor, 0 VW, 0 VH, 100 VW, 100 VH);
    r.RenderRect(backgroundColor_, x_, y_, w_, h_);
}

bool MessageBox::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
    Element::OnMouseDown(button, xw, yh);
    return true;
}

bool MessageBox::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh){
    Element::OnMouseUp(button, xw, yh);
    return true;
}

bool MessageBox::OnMouseScroll(float delta, float xw, float yh){
    Element::OnMouseScroll(delta, xw, yh);
    return true;
}