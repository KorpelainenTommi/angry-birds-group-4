#ifndef UI_TEXTELEMENT_HPP
#define UI_TEXTELEMENT_HPP

#include <ui/Element.hpp>

class TextElement: public Element{
public:
    TextElement(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width
    ): Element(top, left, height, width){}
    
    void SetText(const std::string& s){text_ = s;}

    void SetBackgroundColor(const sf::Color& c){backgroundColor_ = c;}

    void SetTextColor(const sf::Color& c){textColor_ = c;}

    void SetFont(FontID f){font_ = f;}

    void SetRelativeFontSize(const ui::pfloat& s);

    void SetAbsoluteFontSize(float s);

    //virtual void Render(const RenderSystem&);

    ui::pfloat GetFontSize();

protected:
    std::string text_ = "";
    sf::Color backgroundColor_ = ui::backgroundColor;
    sf::Color textColor_ = ui::textColor;
    FontID font_ = ui::defaultFont;

private:
    ui::pfloat relativeFontSize_ = ui::defaultFontSize;
    bool useRelativeFontSize_ = false;
    float absoluteFontSize_ = ui::defaultAbsoluteFontSize;
};

#endif