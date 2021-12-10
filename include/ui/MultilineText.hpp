#ifndef UI_MULTILINETEXT_HPP
#define UI_MULTILINETEXT_HPP

#include <ui/TextElement.hpp>

class MultilineText: public TextElement{
public:
    MultilineText(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width
    ): TextElement(top, left, height, width){}

    virtual void SetText(const std::string& s);

    virtual void Render(const RenderSystem& r);

    void SetRelativeLineSpacing(const ui::pfloat& s);

    void SetAbsoluteLineSpacing(float s);

    ui::pfloat GetLineSpacing();

private:
    ui::pfloat relativeLineSpacing_ = 0 VH;
    float absoluteLineSpacing_ = ui::defaultAbsoluteFontSize / 4;
    bool useRelativeLineSpacing_ = false;
    std::vector<std::string> lines_;
};

#endif
