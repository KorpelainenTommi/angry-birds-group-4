#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <functional>
#include <ui/UIConstants.hpp>
#include <UpdateListener.hpp>


/// @brief Base class for elements
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

    virtual void SetPosition(ui::pfloat x, ui::pfloat y) { x_ = x; y_ = y; }

    virtual void SetTop(ui::pfloat top){y_ = top;}

    /// @brief returns the raw y coordinate of the element without considering the offset
    ui::pfloat GetTopY() const {return y_;}

    virtual void SetLeft(ui::pfloat left){x_ = left;}

    /// @brief returns the raw x coordinate of the element without considering the offset
    ui::pfloat GetLeftX() const {return x_;}

    virtual void SetSize(ui::pfloat w, ui::pfloat h) { w_ = w; h_ = h; }

    virtual void SetHeight(ui::pfloat height){h_ = height;}

    ui::pfloat GetHeight() const {return h_;}

    virtual void SetWidth(ui::pfloat width){w_ = width;}

    ui::pfloat GetWidth() const {return w_;}

    /// @brief checks if the given coordinates are inside the elements and its crop area and the element is visible
    virtual bool isInside(float xw, float yh) const;

    /// @brief return true if the element captures the event, but doesn't execute any event handlers yet
    /// @details ideally this should be a pure function
    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);

    /// @brief return true if screen should play click sound after this element is clicked
    /// @details this method is called only if OnMouseDown returned true
    bool ClickSoundShouldBePlayed() const;

    /// @brief execute event handlers and do all other things that must be done on the event occurs
    /// @details this method is called only if OnMouseDown returned true
    virtual void ExecuteOnMouseDown();

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseMove(float xw, float yh);

    virtual bool OnMouseScroll(float delta, float xw, float yh);

    virtual bool OnKeyDown(const sf::Event::KeyEvent&){return false;}

    virtual bool OnKeyUp(const sf::Event::KeyEvent&){return false;}

    virtual bool OnTextEntered(const sf::Event::TextEvent&){return false;}

    /// @brief this method is called whenever the window is resized
    virtual void OnWindowResize();

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

    /// @brief remove frocus from the element
    virtual void Blur();

    /// @brief give focus for the element
    virtual void Focus();

    virtual void SetOffsetX(const ui::pfloat& ox){offsetX_ = ox;}
    virtual void SetOffsetX(){offsetX_ = 0 VW;}

    virtual void SetOffsetY(const ui::pfloat& oy){offsetY_ = oy;}
    virtual void SetOffsetY(){offsetY_ = 0 VH;}

    /// @brief set the area in which the element must be rendered
    virtual void SetCropArea(const ui::CropArea& a){
        cropArea_ = a;
        cropped_ = true;
    }
    virtual void SetCropArea(){cropped_ = false;}

    bool IsCropped() const {return cropped_;}

    ui::CropArea GetCropArea() const {return cropArea_;}

    /// @brief convert any pfloat into a pfloat that is relative to window height
    ui::pfloat toVH(const ui::pfloat&) const;
    /// @brief convert any pfloat into a pfloat that is relative to window width
    ui::pfloat toVW(const ui::pfloat&) const;

    /// @brief get the y coordinate in which the offset has been taken into account
    ui::pfloat GetTop() const;
    /// @brief get the x coordinate in which the offset has been taken into account
    ui::pfloat GetLeft() const;

    /// @brief tell the element to either capture or pass events that can give it a focus
    void SetFocusCapture(bool b){captureFocus_ = b;}

    /// @brief set a HTML-like title for the elemnt
    /// @brief currently RoundIcon is the only element that implements this functionality
    void SetTitle(const std::string& s);

    bool IsVisible() const;
    virtual void Hide();
    virtual void Show();

protected:

    ui::pfloat x_;
    ui::pfloat y_;
    ui::pfloat w_;
    ui::pfloat h_;
    ui::pfloat offsetX_ = 0 VW;
    ui::pfloat offsetY_ = 0 VH;
    bool captureFocus_ = false;
    bool visible_ = true;

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

    std::string title_ = "";
    ui::pfloat titleFontSize_ = ui::defaultFontSize;
    ui::pfloat titleX_;
    ui::pfloat titleY_;
    ui::pfloat titleW_ = 1 VW;
    bool renderTitle = false;

    bool isInsideCropArea(float xvw, float yvh) const;

    void RenderTitle(const RenderSystem& r);
};



#endif
