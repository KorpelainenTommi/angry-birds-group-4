#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <ui/UIConstants.hpp>
#include <UpdateListener.hpp>


/// Base class for elements
class Element : public UpdateListener {
public:
    virtual ~Element() = default;
    virtual void Render(const RenderSystem&) = 0;
    void SetPosition(ui::pfloat x, ui::pfloat y) { x_ = x; y_ = y; }
    void SetSize(ui::pfloat w, ui::pfloat h) { w_ = w; h_ = h; }
protected:
    ui::pfloat x_;
    ui::pfloat y_;
    ui::pfloat w_;
    ui::pfloat h_;
};



#endif