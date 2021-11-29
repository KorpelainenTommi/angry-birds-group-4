#ifndef UI_MESSAGEBOX_HPP
#define UI_MESSAGEBOX_HPP

#include <ui/TextElement.hpp>

class MessageBox: public TextElement{
public:
    MessageBox(const ui::pfloat& height, const ui::pfloat& width): TextElement(
        (50 - ui::toVHFloat(height) / 2) VH, (50 - ui::toVWFloat(width) / 2) VW, height, width
    ){}

    virtual void Render(const RenderSystem&);
};

#endif