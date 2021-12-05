#ifndef UI_ROUNDICON_HPP
#define UI_ROUNDICON_HPP

#include <ui/RoundElement.hpp>

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

private:
    SpriteID icon_;
};

#endif