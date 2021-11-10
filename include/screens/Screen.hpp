#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include <vector>
#include <ui/Element.hpp>
#include <UpdateListener.hpp>


//Base class for screens
class Screen : public UpdateListener {
public:

    virtual void Update() {
        //Update all elements
        for(const auto& e : menu_) e->Update();
    }

    virtual void Render(const RenderSystem& r) {
        //Render all elements
        for(const auto& e : menu_) e->Render(r);
    }


protected:
    std::vector<std::unique_ptr<Element>> menu_;
};


#endif