#include <screens/Screen.hpp>
#include <ui/MessageBox.hpp>
#include <ui/Button.hpp>

#include <iostream>

void Screen::Render(const RenderSystem& r){
    if(ui::windowHeight != windowHeight_ || ui::windowWidth != windowWidth_){
        windowWidth_ = ui::windowWidth;
        windowHeight_ = ui::windowHeight;
        for(const auto& e : menu_){
            e->OnWindowResize();
            e->Render(r);
        }
        if(messages_.size() > 0) for(const auto& e: messages_.front()){
            e->OnWindowResize();
            e->Render(r);
        }
    }else{
        for(const auto& e : menu_) e->Render(r);
        if(messages_.size() > 0) for(const auto& e: messages_.front()) e->Render(r);
    }
}

void Screen::setFocusedElement(const std::shared_ptr<Element>& p){
    if(hasFocusedElement_ && !focusedElement_.expired()) focusedElement_.lock()->Blur();
    else hasFocusedElement_ = true;
    p->Focus();
    focusedElement_ = std::weak_ptr<Element>(p);
}

bool Screen::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
    if(hasFocusedElement_ && !focusedElement_.expired()){
        auto e = focusedElement_.lock();
        if(e->OnMouseDown(button, xw, yh)) return true;
        e->Blur();
        hasFocusedElement_ = false;
    }
    if(messages_.size() > 0){
        auto m = messages_.front();
        for(std::size_t i = m.size(); i > 0;){
            auto e = std::weak_ptr<Element>(m[--i]);
            if(m[i]->OnMouseDown(button, xw, yh)){
                if(!e.expired()) setFocusedElement(e.lock());
                return true;
            }
        }
    }
    for(std::size_t i = menu_.size(); i > 0;){
        auto e = std::weak_ptr<Element>(menu_[--i]);
        if(menu_[i]->OnMouseDown(button, xw, yh)){
            if(!e.expired()) setFocusedElement(e.lock());
            return true;
        }
    }
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

bool Screen::OnTextEntered(const sf::Event::TextEvent& e){
    if(!hasFocusedElement_ || focusedElement_.expired()) return false;
    return focusedElement_.lock()->OnTextEntered(e);
}

bool Screen::OnKeyDown(const sf::Event::KeyEvent& e){
    if(!hasFocusedElement_ || focusedElement_.expired()) return false;
    return focusedElement_.lock()->OnKeyDown(e);
}

bool Screen::OnKeyUp(const sf::Event::KeyEvent& e){
    if(!hasFocusedElement_ || focusedElement_.expired()) return false;
    return focusedElement_.lock()->OnKeyUp(e);
}

void Screen::Confirm(std::string text, const std::function<void(bool)> callBack){
    std::vector<std::shared_ptr<Element>> v;
    v.push_back(std::make_shared<MessageBox>(messageBoxHeight_, messageBoxWidth_));
    v.push_back(generateMessageBoxButton(1, [this, callBack](){
        this->DequeueMessage();
        callBack(true);
    }, SpriteID::ui_button_ok));
    v.push_back(generateMessageBoxButton(2, [this, callBack](){
        this->DequeueMessage();
        callBack(false);
    }, SpriteID::ui_button_cancel));
    v.push_back(generateConfirmText(text));
    messages_.push(v);
}

void Screen::DequeueMessage(){
    messages_.pop();
}

ui::pfloat Screen::calcMessageBoxButtonTop() const {
    return (50 + ui::toVHFloat(messageBoxHeight_) / 2 - ui::toVHFloat(messageBoxButtonSize_) 
        - ui::toVHFloat(messageBoxSpacing_)) VH;
}

ui::pfloat Screen::calcMessageBoxButtonLeft(unsigned char buttonNumber) const {
    return (50 + ui::toVWFloat(messageBoxWidth_) / 2 
        - (ui::toVWFloat(messageBoxButtonSize_) + ui::toVWFloat(messageBoxSpacing_)) * buttonNumber) VW;
}

std::shared_ptr<RoundIcon> Screen::generateMessageBoxButton(
    unsigned char buttonNumber, 
    const std::function<void()> callBack, 
    const SpriteID& sprite
){
    auto b = std::make_shared<RoundIcon>(
        calcMessageBoxButtonTop(), 
        calcMessageBoxButtonLeft(buttonNumber), 
        messageBoxButtonSize_ / 2, 
        sprite
    );
    b->SetMouseDownHandler(callBack);
    auto wb = std::weak_ptr<RoundIcon>(b);
    b->SetWindowResizeHandler([wb, this, buttonNumber](){
        wb.lock()->SetPosition(
            this->calcMessageBoxButtonLeft(buttonNumber),
            this->calcMessageBoxButtonTop()
        );
    });
    return b;
}

ui::pfloat Screen::calcConfirmTextTop() const {
    return (50 - ui::toVHFloat(messageBoxHeight_) / 2) VH;
}

ui::pfloat Screen::calcConfirmTextLeft() const {
    return (50 - ui::toVWFloat(messageBoxWidth_) / 2) VW;
}

ui::pfloat Screen::calcConfirmTextHeight() const {
    return (ui::toVHFloat(messageBoxHeight_) - ui::toVHFloat(messageBoxButtonSize_) 
        - ui::toVHFloat(messageBoxSpacing_)) VH;
}

ui::pfloat Screen::calcConfirmTextWidth() const {
    return messageBoxWidth_;
}

std::shared_ptr<TextElement> Screen::generateConfirmText(const std::string& text){
    auto t = std::make_shared<TextElement>(
        calcConfirmTextTop(), 
        calcConfirmTextLeft(), 
        calcConfirmTextHeight(), 
        calcConfirmTextWidth()
    );
    t->SetText(text);
    t->SetTextAlign(ui::TextAlign::center);
    t->SetRelativeFontSize(ui::defaultFontSize);
    auto wt = std::weak_ptr<TextElement>(t);
    t->SetWindowResizeHandler([wt, this](){
        auto t = wt.lock();
        t->SetPosition(
            this->calcConfirmTextLeft(),
            this->calcConfirmTextTop()
        );
        t->SetSize(
            this->calcConfirmTextWidth(),
            this->calcConfirmTextHeight()
        );
    });
    return t;
}