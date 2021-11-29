#include <screens/Screen.hpp>
#include <ui/MessageBox.hpp>

void Screen::Render(const RenderSystem& r){
    for(const auto& e : menu_) e->Render(r);
    if(messages_.size() > 0) for(const auto& e: messages_.front()) e->Render(r);
}

bool Screen::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
    if(messages_.size() > 0){
        auto m = messages_.front();
        for(std::size_t i = m.size(); i > 0;) if(m[--i]->OnMouseDown(button, xw, yh)) return true;
    }
    for(std::size_t i = menu_.size(); i > 0;) if(menu_[--i]->OnMouseDown(button, xw, yh)) return true;
    return false;
}

bool Screen::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh){
    if(messages_.size() > 0){
        auto m = messages_.front();
        for(std::size_t i = m.size(); i > 0;) if(m[--i]->OnMouseUp(button, xw, yh)) return true;
    }
    for(std::size_t i = menu_.size(); i > 0;) if(menu_[--i]->OnMouseUp(button, xw, yh)) return true;
    return false;
}

bool Screen::OnMouseMove(float xw, float yh){
    if(messages_.size() > 0){
        auto m = messages_.front();
        for(std::size_t i = m.size(); i > 0;) if(m[--i]->OnMouseMove(xw, yh)) return true;
    }
    for(std::size_t i = menu_.size(); i > 0;) if(menu_[--i]->OnMouseMove(xw, yh)) return true;
    return false;
}

bool Screen::OnMouseScroll(float delta, float xw, float yh){
    if(messages_.size() > 0){
        auto m = messages_.front();
        for(std::size_t i = m.size(); i > 0;) if(m[--i]->OnMouseScroll(delta, xw, yh)) return true;
    }
    for(std::size_t i = menu_.size(); i > 0;) if(menu_[--i]->OnMouseScroll(delta, xw, yh)) return true;
    return false;
}

void Screen::Confirm(std::string text, const std::function<void(bool)> callBack){

}