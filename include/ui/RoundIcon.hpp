#ifndef UI_ROUNDICON_HPP
#define UI_ROUNDICON_HPP

#include <ui/RoundElement.hpp>

/// @brief an element for showing icons with a round hit box
class RoundIcon: public RoundElement{
public:
    RoundIcon(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& radius,
        const SpriteID& icon
    ): RoundElement(top, left, radius), icon_(icon){}

    virtual void Render(const RenderSystem& r);

    void SetIcon(const SpriteID& icon){icon_ = icon;}

    SpriteID GetIcon(){return icon_;}

    /// @brief modify the apperance of the element to indicate that it is selected
    void Select();

    /// @brief undo Select()
    void Unselect();

    /// @brief set the thickness of the highlight border that is shown when the element is selected
    void SetBorderThickness(const ui::pfloat&);

private:
    SpriteID icon_;
    bool selected_ = false;
    ui::pfloat borderThickness_ = 0.5 VH;
};

#endif