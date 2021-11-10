#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <UpdateListener.hpp>

/// Base class for elements
class Element : public UpdateListener {
public:
    virtual void Render(const RenderSystem&) = 0;
    void SetPosition(float xw, float yh) { xw_ = xw; yh_ = yh; }
    void SetSize(float ww, float hh) { ww_ = ww; hh_ = hh; }
protected:
    float xw_;
    float yh_;
    float ww_;
    float hh_;
};



#endif