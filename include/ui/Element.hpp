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

    void SetTop(ui::pfloat top){y_ = top;}

    ui::pfloat GetTopY() const {return y_;}

    void SetLeft(ui::pfloat left){x_ = left;}

    ui::pfloat GetLeftX() const {return x_;}

    void SetSize(ui::pfloat w, ui::pfloat h) { w_ = w; h_ = h; }

    void SetHeight(ui::pfloat height){h_ = height;}

    ui::pfloat GetHeight() const {return h_;}

    void SetWidth(ui::pfloat width){w_ = width;}

    ui::pfloat GetWidth() const {return w_;}

    virtual bool isInside(float xw, float yh) const;

    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseMove(float xw, float yh);

    virtual bool OnMouseScroll(float delta, float xw, float yh);

    void OnWindowResize();

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

    void SetWindowResizeHandler(const std::function<void()> f){windowResizeHandler_ = f;}
    void SetWindowResizeHandler(){windowResizeHandler_ = NULL;}

    void Blur();

    void Focus();

    void SetOffsetX(const ui::pfloat& ox){offsetX_ = ox;}
    void SetOffsetX(){offsetX_ = 0 VW;}

    void SetOffsetY(const ui::pfloat& oy){offsetY_ = oy;}
    void SetOffsetY(){offsetY_ = 0 VH;}

    virtual void SetCropArea(const ui::CropArea& a){
        cropArea_ = a;
        cropped_ = true;
    }
    virtual void SetCropArea(){cropped_ = false;}

    bool IsCropped() const {return cropped_;}

    ui::CropArea GetCropArea() const {return cropArea_;}

    float toVHFloat(const ui::pfloat&) const;
    float toVWFloat(const ui::pfloat&) const;
    ui::pfloat toVH(const ui::pfloat&) const;
    ui::pfloat toVW(const ui::pfloat&) const;

    ui::pfloat GetTop() const;
    ui::pfloat GetLeft() const;

protected:

    ui::pfloat x_;
    ui::pfloat y_;
    ui::pfloat w_;
    ui::pfloat h_;
    ui::pfloat offsetX_ = 0 VW;
    ui::pfloat offsetY_ = 0 VH;

    std::function<void()> mouseDownHandler_ = NULL;
    std::function<void()> mouseUpHandler_ = NULL;
    std::function<void()> mouseEnterHandler_ = NULL;
    std::function<void()> mouseLeaveHandler_ = NULL;
    std::function<void(float delta)> mouseScrollHandler_ = NULL;
    std::function<void(bool focused)> focusChangeHandler_ = NULL;
    std::function<void()> windowResizeHandler_ = NULL;

    bool mouseIn_ = false;
    bool focused_ = false;

    bool cropped_ = false;
    ui::CropArea cropArea_;
};



#endif