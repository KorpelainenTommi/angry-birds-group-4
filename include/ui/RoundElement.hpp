#ifndef UI_ROUNDELEMENT_HPP
#define UI_ROUNDELEMENT_HPP

#include <ui/Element.hpp>

class RoundElement: public Element{
public:
    RoundElement(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& radius
    ): Element(top, left, radius * 2, radius * 2), r_(radius){};

    virtual bool isInside(float xw, float yh) const;

protected:
    ui::pfloat r_;

    float getCenterVHFloatX() const;
    float getCenterVHFloatX(float rvh) const;

    float getCenterVHFloatY() const;
    float getCenterVHFloatY(float rvh) const;

    float distance(float x1, float y1, float x2, float y2) const;
};

#endif