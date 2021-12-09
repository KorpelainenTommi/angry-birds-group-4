#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include <vector>
#include <ui/Element.hpp>
#include <UpdateListener.hpp>
#include <Application.hpp>
#include <queue>
#include <ui/RoundIcon.hpp>
#include <ui/TextElement.hpp>
#include <sstream>

#include <iostream>

class Application;

/// Base class for screens
class Screen : public UpdateListener {
public:
    Screen(Application& app) : app_(app) {}

    virtual ~Screen() = default;

    virtual void Update() {
        //Update all elements
        //for(const auto& e : menu_) e->Update();
        //GameScreen overrides this
    }

    virtual void Render(const RenderSystem& r);

    Application& GetApplication() const { return app_; }

    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseMove(float xw, float yh);

    virtual bool OnMouseScroll(float delta, float xw, float yh);

    virtual bool OnTextEntered(const sf::Event::TextEvent&);

    virtual bool OnKeyDown(const sf::Event::KeyEvent&);

    virtual bool OnKeyUp(const sf::Event::KeyEvent&);

    void Confirm(std::string text, const std::function<void(bool)> callBack);

    void Alert(std::string text, const std::function<void()> callBack);
    void Alert(std::string text);

    void ClickSound() const;

    void DequeueMessage();

    ui::pfloat calcMessageBoxButtonTop(const ui::pfloat& messageHeight) const;

    /**
     * button number is the number of the button from right starting from 1.
     */
    ui::pfloat calcMessageBoxButtonLeft(
        unsigned char buttonNumber, 
        const ui::pfloat& messageWidth
    ) const;

    ui::pfloat calcConfirmTextTop() const;

    ui::pfloat calcConfirmTextLeft() const;

    ui::pfloat calcConfirmTextHeight() const;

    ui::pfloat calcConfirmTextWidth() const;

protected:
    const ui::pfloat messageBoxHeight_ = 15 VH;
    const ui::pfloat messageBoxWidth_ = 30 VW;
    const ui::pfloat messageBoxButtonSize_ = 4 VH;
    const ui::pfloat messageBoxSpacing_ = 1 VH;

    Application& app_;
    std::vector<std::shared_ptr<Element>> menu_;
    std::queue<std::vector<std::shared_ptr<Element>>> messages_;
    float windowWidth_ = 0.0F;
    float windowHeight_ = 0.0F;
    std::shared_ptr<Element> focusedElement_;
    bool hasFocusedElement_ = false;

    template <typename T>
    std::string getString(T v) const {
        std::stringstream ss;
        ss << v;
        return ss.str();
    }

    /**
     * button number is the number of the button from right starting from 1.
     */
    std::shared_ptr<RoundIcon> generateMessageBoxButton(
        unsigned char buttonNumber, 
        const std::function<void()> callBack, 
        const SpriteID& sprite, 
        const ui::pfloat& messageHeight, 
        const ui::pfloat& messageWidth
    );

    std::shared_ptr<TextElement> generateConfirmText(const std::string& text);

    void setFocusedElement(const std::shared_ptr<Element>&);
};


#endif