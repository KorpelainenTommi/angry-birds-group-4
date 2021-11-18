#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <ui/TextElement.hpp>

class Button: public TextElement{
public:
    Button(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width,
        const std::function<void()> mouseDownHandler
    ): TextElement(top, left, height, width){
        mouseDownHandler_ = mouseDownHandler;
        backgroundColor_ = ui::buttonBackgroundColor;
        textColor_ = ui::buttonTextColor;
    };

    virtual void Render(const RenderSystem&);
};

#endif