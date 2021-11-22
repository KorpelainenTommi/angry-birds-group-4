#ifndef UI_TEXTELEMENT_HPP
#define UI_TEXTELEMENT_HPP

#include <ui/ColoredElement.hpp>

class TextElement: public ColoredElement{
public:
    TextElement(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width
    ): ColoredElement(top, left, height, width){}
    
    void SetText(const std::string& s){text_ = s;}

    void SetTextColor(const sf::Color& c){textColor_ = c;}
    void SetTextColor(){textColor_ = ui::textColor;}

    void SetFont(FontID f){font_ = f;}

    void SetTextAlign(const ui::TextAlign& a){align_ = a;}

    void SetRelativeFontSize(const ui::pfloat& s);

    void SetAbsoluteFontSize(float s);

    virtual void Render(const RenderSystem&);

    ui::pfloat GetFontSize();

protected:
    std::string text_ = "";
    sf::Color textColor_ = ui::textColor;
    FontID font_ = ui::defaultFont;
    ui::TextAlign align_ = ui::TextAlign::left;

private:
    ui::pfloat relativeFontSize_ = ui::defaultFontSize;
    bool useRelativeFontSize_ = false;
    float absoluteFontSize_ = ui::defaultAbsoluteFontSize;
};

#endif