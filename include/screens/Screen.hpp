#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include <vector>
#include <ui/Element.hpp>
#include <UpdateListener.hpp>
#include <Application.hpp>


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

    virtual bool OnMouseDown(const sf::Event::MouseButtonEvent& e){
        std::size_t len = menu_.size();
        for(std::size_t i = 0; i < len; i++){
            if(menu_[i].get()->OnMouseDown(e)) return true;
        }
        return false;
    }

    virtual bool OnMouseUp(const sf::Event::MouseButtonEvent& e){
        std::size_t len = menu_.size();
        for(std::size_t i = 0; i < len; i++){
            if(menu_[i].get()->OnMouseUp(e)) return true;
        }
        return false;
    }

    virtual bool OnMouseMove(const sf::Event::MouseMoveEvent& e){
        std::size_t len = menu_.size();
        for(std::size_t i = 0; i < len; i++){
            if(menu_[i].get()->OnMouseMove(e)) return true;
        }
        return false;
    }

protected:
    Application& app_;
    std::vector<std::unique_ptr<Element>> menu_;
};


#endif