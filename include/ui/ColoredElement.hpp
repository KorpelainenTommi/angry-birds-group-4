#ifndef UI_COLOREDELEMENT_HPP
#define UI_COLOREDELEMENT_HPP

#include <ui/Element.hpp>

class ColoredElement: public Element{
public:
    ColoredElement(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width
    ): Element(top, left, height, width){}

    void SetBackgroundColor(const sf::Color& c){backgroundColor_ = c;}
    void SetBackgroundColor(){backgroundColor_ = ui::backgroundColor;}

    virtual void Render(const RenderSystem& r){
        r.RenderRect(backgroundColor_, GetLeft(), GetTop(), w_, h_);
    }

protected:
    sf::Color backgroundColor_ = ui::backgroundColor;
};

#endif