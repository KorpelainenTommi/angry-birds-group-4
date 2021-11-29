#ifndef UI_MESSAGEBOX_HPP
#define UI_MESSAGEBOX_HPP

#include <ui/ColoredElement.hpp>

class MessageBox: public ColoredElement{
public:
    MessageBox(const ui::pfloat& height, const ui::pfloat& width): ColoredElement(
        (50 - ui::toVHFloat(height) / 2) VH, (50 - ui::toVWFloat(width) / 2) VW, height, width
    ){}

    virtual void Render(const RenderSystem&);
};

#endif