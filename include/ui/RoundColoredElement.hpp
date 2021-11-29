#ifndef UI_ROUNDCOLOREDELEMENT_HPP
#define UI_ROUNDCOLOREDELEMENT_HPP

#include <ui/RoundElement.hpp>

class RoundColoredElement: public RoundElement{
public:
    RoundColoredElement(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& radius
    ): RoundElement(top, left, radius){}

    void SetBackgroundColor(const sf::Color& c){backgroundColor_ = c;}
    void SetBackgroundColor(){backgroundColor_ = defaultBackgroundColor_;}

    virtual void Render(const RenderSystem& r);

protected:
    sf::Color backgroundColor_ = ui::backgroundColor;
    sf::Color defaultBackgroundColor_ = ui::backgroundColor;
};

#endif