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
    void SetBackgroundColor(){backgroundColor_ = defaultBackgroundColor_;}

    virtual void Render(const RenderSystem& r){
        if(cropped_) r.RenderRect(backgroundColor_, GetLeft(), GetTop(), w_, h_, cropArea_);
        else r.RenderRect(backgroundColor_, GetLeft(), GetTop(), w_, h_);
    }

protected:
    sf::Color backgroundColor_ = ui::backgroundColor;
    sf::Color defaultBackgroundColor_ = ui::backgroundColor;
};

#endif