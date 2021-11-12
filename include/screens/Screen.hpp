#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include <vector>
#include <ui/Element.hpp>
#include <UpdateListener.hpp>

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


protected:
    Application& app_;
    std::vector<std::unique_ptr<Element>> menu_;
};


#endif