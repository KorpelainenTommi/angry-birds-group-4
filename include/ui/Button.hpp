#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <ui/TextElement.hpp>

/// @brief Class for different buttons
class Button: public TextElement{
public:
    Button(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width
    ): TextElement(top, left, height, width){
        defaultBackgroundColor_ = ui::buttonBackgroundColor;
        backgroundColor_ = ui::buttonBackgroundColor;
        textColor_ = ui::buttonTextColor;
        align_ = ui::TextAlign::center;
    };

    Button(
        const ui::pfloat& top,
        const ui::pfloat& left,
        const ui::pfloat& height,
        const ui::pfloat& width,
        const std::function<void()> mouseDownHandler
    ): Button(top, left, height, width){
        mouseDownHandler_ = mouseDownHandler;
    };

    /// @brief deactivate the button so it can't be pressed
    void Deactivate(){active_ = false;};

    /// @brief activate the button so it can be pressed again
    void Activate(){active_ = true;};

    void SetDeactivatedBackgroundColor(const sf::Color& c){deactivatedBackgroundColor_ = c;}
    void SetDeactivatedBackgroundColor(){deactivatedBackgroundColor_ = defaultDeactivatedBackgroundColor_;}

    virtual void Render(const RenderSystem&);

    /// @brief execute mouse down handler and do other things that should be done when mouse down occurs
    /// @details screen calls this after setting focus for the element if OnMouseDown returned true
    virtual void ExecuteOnMouseDown();

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);

private:
    bool active_ = true;
    sf::Color defaultDeactivatedBackgroundColor_ = ui::deactivatedButtonBackgroundColor;
    sf::Color deactivatedBackgroundColor_ = ui::deactivatedButtonBackgroundColor;
};

#endif
