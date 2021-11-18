/*#ifndef LABEL_HPP
#define LABEL_HPP

#include <string>
#include <ui/Element.hpp>
#include <ui/UIConstants.hpp>
#include <framework/Resources.hpp>


/// An element that displays text
class Label : public Element {
public:
    
    Label(const std::string& text, sf::Color color = ui::DefaultTextColor, FontID id = FontID::source_serif) : 
    text_(text), font_(id), color_(color) {}

    virtual void Render(const RenderSystem&);

private:
    std::string text_;
    FontID font_;
    sf::Color color_;
};

#endif*/