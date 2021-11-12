#ifndef UI_TEXTELEMENT_HPP
#define UI_TEXTELEMENT_HPP

#include <ui/Element.hpp>

class TextElement: public Element{
public:
    void SetText(const std::string& s){text_ = s;}

    void SetBackgroundColor(sf::Color& c){backgroundColor_ = c;}

    void SetTextColor(sf::Color& c){textColor_ = c;}

private:
    std::string text_ = "";
    sf::Color backgroundColor_ = ui::backgroundColor;
    sf::Color textColor_ = ui::textColor;
};

#endif