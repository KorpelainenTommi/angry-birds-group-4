#ifndef UI_TEXTLINE_HPP
#define UI_TEXTLINE_HPP

#include <ui/TextElement.hpp>
 /// @brief an element for a single text line
class TextLine: public TextElement{
public:
    TextLine(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width,
        const std::string& text
    ): TextElement(top, left, height, width){
        text_ = text;
        backgroundColor_ = {0, 0, 0, 0};
    }

    virtual void Render(const RenderSystem&);
};

#endif