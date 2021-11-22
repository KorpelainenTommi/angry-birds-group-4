#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include <vector>
#include <ui/Element.hpp>
#include <UpdateListener.hpp>
#include <Application.hpp>

#include <iostream>

class Application;

/// Base class for screens
class Screen : public UpdateListener {
public:
    Screen(Application& app) : app_(app) {}

    virtual ~Screen() = default;

    virtual void Update() {
        //Update all elements
        for(const auto& e : menu_) e->Update();
    }

    virtual void Render(const RenderSystem& r) {
        //Render all elements
        for(const auto& e : menu_) e->Render(r);
    }

    Application& GetApplication() const { return app_; }

    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh){
        std::size_t len = menu_.size();
        for(std::size_t i = 0; i < len; i++){
            if(menu_[i].get()->OnMouseDown(button, xw, yh)) return true;
        }
        return false;
    }

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh){
        std::size_t len = menu_.size();
        for(std::size_t i = 0; i < len; i++){
            if(menu_[i].get()->OnMouseUp(button, xw, yh)) return true;
        }
        return false;
    }

    virtual bool OnMouseMove(float xw, float yh){
        std::size_t len = menu_.size();
        for(std::size_t i = 0; i < len; i++){
            if(menu_[i].get()->OnMouseMove(xw, yh)) return true;
        }
        return false;
    }

    virtual bool OnMouseScroll(float delta, float xw, float yh){
        std::size_t len = menu_.size();
        for(std::size_t i = 0; i < len; i++){
            if(menu_[i].get()->OnMouseScroll(delta, xw, yh)) return true;
        }
        return false;
    }

protected:
    Application& app_;
    std::vector<std::shared_ptr<Element>> menu_;
};


#endif