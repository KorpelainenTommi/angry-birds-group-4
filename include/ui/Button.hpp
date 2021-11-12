#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <ui/TextElement.hpp>

class Button: public Element{
public:
    Button(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width,
        const std::function<void()> mouseDownHandler,
        Screen& screen
    ): Element(top, left, height, width, screen){
        mouseDownHandler_ = mouseDownHandler_;
    };

};

#endif