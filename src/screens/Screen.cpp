#include <screens/Screen.hpp>
#include <ui/MessageBox.hpp>
#include <ui/Button.hpp>
#include <ui/TextElement.hpp>

#include <iostream>

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
    std::vector<std::shared_ptr<Element>> v;
    auto base = std::make_shared<MessageBox>(15 VH, 30 VW);
    v.push_back(base);
    auto b1 = std::make_shared<Button>(52.5 VH, 36 VW, 4 VH, 13.5 VW, [this, callBack](){
        this->DequeueMessage();
        callBack(false);
    });
    b1->SetText("cancel");
    b1->SetRelativeFontSize(ui::defaultFontSize);
    //b1->SetMouseEnterHandler([b1](){b1->SetBackgroundColor(ui::highlightColor);});
    //b1->SetMouseLeaveHandler([b1](){b1->SetBackgroundColor();});
    v.push_back(b1);
    auto b2 = std::make_shared<Button>(52.5 VH, 50.5 VW, 4 VH, 13.5 VW, [this, callBack](){
        this->DequeueMessage();
        callBack(true);
    });
    b2->SetText("ok");
    b2->SetRelativeFontSize(ui::defaultFontSize);
    //b2->SetMouseEnterHandler([b2](){b2->SetBackgroundColor(ui::highlightColor);});
    //b2->SetMouseLeaveHandler([b2](){b2->SetBackgroundColor();});
    v.push_back(b2);
    auto t = std::make_shared<TextElement>(42.5 VH, 35 VW, 10 VH, 30 VW);
    t->SetText(text);
    t->SetTextAlign(ui::TextAlign::center);
    t->SetRelativeFontSize(ui::defaultFontSize);
    v.push_back(t);
    messages_.push(v);
}

void Screen::DequeueMessage(){
    messages_.pop();
}