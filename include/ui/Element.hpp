#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <functional>
#include <ui/UIConstants.hpp>
#include <UpdateListener.hpp>


/// Base class for elements
class Element : public UpdateListener {
public:
    Element(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& height, 
        const ui::pfloat& width
    ): x_(left), y_(top), w_(width), h_(height){};

    virtual ~Element() = default;

    virtual void Render(const RenderSystem&) = 0;

    void SetPosition(ui::pfloat x, ui::pfloat y) { x_ = x; y_ = y; }

    void SetSize(ui::pfloat w, ui::pfloat h) { w_ = w; h_ = h; }

    bool isInside(float xw, float yh) const;

    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseMove(float xw, float yh);

    virtual bool OnMouseScroll(float delta, float xw, float yh);

    void SetMouseDownHandler(const std::function<void()> f){mouseDownHandler_ = f;}
    void SetMouseDownHandler(){mouseDownHandler_ = NULL;}

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

    void SetOffsetX(const ui::pfloat& ox){offsetX_ = ox;}
    void SetOffsetX(){offsetX_ = 0 VW;}

    void SetOffsetY(const ui::pfloat& oy){offsetY_ = oy;}
    void SetOffsetY(){offsetY_ = 0 VH;}

protected:
    float toVHFloat(const ui::pfloat&) const;
    float toVWFloat(const ui::pfloat&) const;
    ui::pfloat toVH(const ui::pfloat&) const;
    ui::pfloat toVW(const ui::pfloat&) const;

    ui::pfloat GetTop() const;
    ui::pfloat GetLeft() const;

    ui::pfloat x_;
    ui::pfloat y_;
    ui::pfloat w_;
    ui::pfloat h_;
    ui::pfloat offsetX_;
    ui::pfloat offsetY_;

    std::function<void()> mouseDownHandler_ = NULL;
    std::function<void()> mouseUpHandler_ = NULL;
    std::function<void()> mouseEnterHandler_ = NULL;
    std::function<void()> mouseLeaveHandler_ = NULL;
    std::function<void(float delta)> mouseScrollHandler_ = NULL;
    std::function<void(bool focused)> focusChangeHandler_ = NULL;

    bool mouseIn_ = false;
    bool focused_ = false;
};



#endif