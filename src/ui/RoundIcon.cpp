#include <ui/RoundIcon.hpp>

void RoundIcon::Render(const RenderSystem& r){
    ui::pfloat d = r_ * 2;
    ui::pfloat x = GetLeft();
    ui::pfloat y = GetTop();
    float bt = ui::toVHFloat(borderThickness_);
    ui::pfloat sd = (ui::toVHFloat(d) + bt * 2) VH;
    ui::pfloat sx = (ui::toVHFloat(x) - bt) VH;
    ui::pfloat sy = (ui::toVHFloat(y) - bt) VH;
    if(cropped_){
        if(selected_) r.RenderOval(ui::highlightColor, sx, sy, sd, sd, cropArea_);
        r.RenderSprite(icon_, x, y, d, d, cropArea_);
    }else{
        if(selected_) r.RenderOval(ui::highlightColor, sx, sy, sd, sd, cropArea_);
        r.RenderSprite(icon_, x, y, d, d);
    }
    if(renderTitle) RenderTitle(r);
}

void RoundIcon::Select(){
    selected_ = true;
}

void RoundIcon::Unselect(){
    selected_ = false;
}

void RoundIcon::SetBorderThickness(const ui::pfloat& t){
    borderThickness_ = t;
}