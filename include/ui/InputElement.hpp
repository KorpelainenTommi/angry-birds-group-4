#ifndef UI_INPUTELEMENT_HPP
#define UI_INPUTELEMENT_HPP

#include <ui/ColoredElement.hpp>

class InputElement: public ColoredElement{
public:
    InputElement(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& height, 
        const ui::pfloat& width
    ): ColoredElement(top, left, height, width){
        captureFocus_ = true;
        defaultBackgroundColor_ = ui::inputBackgroundColor;
        backgroundColor_ = ui::inputBackgroundColor;
        updateInputArea();
    };

    virtual void Render(const RenderSystem&);

    void SetText(const std::string&);

    std::string GetText() const;

    virtual bool OnKeyDown(const sf::Event::KeyEvent&);

    virtual bool OnTextEntered(const sf::Event::TextEvent&);

    void SetTextColor(const sf::Color& c){textColor_ = c;}
    void SetTextColor(){textColor_ = ui::textColor;}

    void SetFont(FontID f);

    void SetFontSize(const ui::pfloat& s);

    ui::pfloat GetFontSize(){return fontSize_;}

    virtual void SetPosition(ui::pfloat x, ui::pfloat y);

    virtual void SetTop(ui::pfloat top);

    virtual void SetLeft(ui::pfloat left);

    virtual void SetSize(ui::pfloat w, ui::pfloat h);

    virtual void SetHeight(ui::pfloat height);

    virtual void SetWidth(ui::pfloat width);

    virtual void OnWindowResize();

    virtual void SetOffsetX(const ui::pfloat& ox);
    virtual void SetOffsetX();

    virtual void SetOffsetY(const ui::pfloat& oy);
    virtual void SetOffsetY();

    virtual void SetCropArea(const ui::CropArea& a);
    virtual void SetCropArea();

    //virtual void Blur();

    //virtual void Focus();

private:
    std::string value_ = "";
    size_t caretPos_ = 0;
    ui::pfloat textOffset_ = 0 VH;
    ui::pfloat caretOffset_ = 0 VH;
    bool modified_ = false;
    ui::pfloat fontSize_ = ui::defaultFontSize;
    FontID font_ = ui::defaultMonospaceFont;
    sf::Color textColor_ = ui::textColor;
    ui::CropArea inputArea_;
    sf::Color caretColor_ = ui::inputCaretColor;
    ui::pfloat caretWidth_ = ui::defaultFontSize / 8;

    void write(char);

    void backspace();

    void moveCaretRight();

    void moveCaretLeft();

    /**
     * returns 0 if the char is invalid and should not be added to value.
     */
    char getChar(sf::Uint32) const;

    void updateInputRenderingValues(const RenderSystem& r);

    void updateInputArea();
};

#endif