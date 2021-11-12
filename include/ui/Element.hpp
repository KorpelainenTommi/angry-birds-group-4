#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <functional>
#include <ui/UIConstants.hpp>
#include <UpdateListener.hpp>
#include <screens/Screen.hpp>


/// Base class for elements
class Element : public UpdateListener {
public:
    Element(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& height, 
        const ui::pfloat& width,
        Screen& screen
    ): x_(left), y_(top), w_(width), h_(height), screen_(screen){};

    virtual ~Element() = default;

    virtual void Render(const RenderSystem&) = 0;

    void SetPosition(ui::pfloat x, ui::pfloat y) { x_ = x; y_ = y; }

    void SetSize(ui::pfloat w, ui::pfloat h) { w_ = w; h_ = h; }

    Screen& GetScreen() const {return screen_;}

    template <typename T>
    bool isInside(const T& mouseEvent){
        float windowHeight = screen_.GetApplication().GetWindowHeight();
        float windowWidth = screen_.GetApplication().GetWindowWidth();
        float left = x_.f * 0.01F * (x_.p ? windowWidth : windowHeight);
        float top = y_.f * 0.01F * (y_.p ? windowWidth : windowHeight);
        float right = w_.f * 0.01F * (w_.p ? windowWidth : windowHeight) + left;
        float bottom = h_.f * 0.01F * (h_.p ? windowWidth : windowHeight) + top;
        return mouseEvent.x > left && mouseEvent.x < right && mouseEvent.y > top && mouseEvent.y < bottom;
    };

    virtual bool OnMouseDown(const sf::Event::MouseButtonEvent&);

    virtual bool OnMouseUp(const sf::Event::MouseButtonEvent&);

    virtual bool OnMouseMove(const sf::Event::MouseMoveEvent&);

    void SetMouseDownHandler(const std::function<void()> f){mouseDownHandler_ = f;}
    void SetMOuseDownHandler(){mouseDownHandler_ = NULL;}

    void SetMouseUpHandler(const std::function<void()> f){mouseUpHandler_ = f;}
    void SetMouseUpHandler(){mouseUpHandler_ = NULL;}

    void SetMouseEnterHandler(const std::function<void()> f){mouseEnterHandler_ = f;}
    void SetMOuseEnterHandler(){mouseEnterHandler_ = NULL;}

    void SetMouseLeaveHandler(const std::function<void()> f){mouseLeaveHandler_ = f;}
    void SetMouseLeaveHandler(){mouseLeaveHandler_ = NULL;}

    /**
     * delta is the wheel offset (positive is up/left, negative is down/right).
     */
    void SetMouseScrollHandler(const std::function<void(float delta)> f){mouseScrollHandler_ = f;}
    void SetMouseScrollHandler(){mouseScrollHandler_ = NULL;}

    void SetFocusChangeHandler(const std::function<void(bool focused)> f){focusChangeHandler_ = f;}
    void SetFocusChangeHandler(){focusChangeHandler_ = NULL;}

    void Blur();

    void Focus();

protected:
    ui::pfloat x_;
    ui::pfloat y_;
    ui::pfloat w_;
    ui::pfloat h_;

    std::function<void()> mouseDownHandler_ = NULL;
    std::function<void()> mouseUpHandler_ = NULL;
    std::function<void()> mouseEnterHandler_ = NULL;
    std::function<void()> mouseLeaveHandler_ = NULL;
    std::function<void(float delta)> mouseScrollHandler_ = NULL;
    std::function<void(bool focused)> focusChangeHandler_ = NULL;

    bool mouseIn_ = false;
    bool focused_ = false;

    Screen& screen_;
};



#endif