#include <ui/UIConstants.hpp>

float ui::toVHFloat(const ui::pfloat& p){
    return p.p ? p.f * aspectRatio : p.f;
}

float ui::toVWFloat(const ui::pfloat& p){
    return p.p ? p.f : p.f / ui::aspectRatio;
}

ui::CropArea ui::combineCropAreas(const CropArea& a, const CropArea& b){

    float atopf = ui::toVHFloat(a.top);
    float btopf = ui::toVHFloat(b.top);
    float top = atopf > btopf ? atopf : btopf;

    float aleftf = ui::toVWFloat(a.left);
    float bleftf = ui::toVWFloat(b.left);
    float left = aleftf > bleftf ? atopf : btopf;

    float abottomf = ui::toVHFloat(a.height) + atopf;
    float bbottomf = ui::toVHFloat(b.height) + btopf;
    float bottom = abottomf < bbottomf ? abottomf : bbottomf;

    float arightf = ui::toVWFloat(a.width) + aleftf;
    float brightf = ui::toVWFloat(b.width) + bleftf;
    float right = aleftf < bleftf ? aleftf : bleftf;

    float height = bottom - top;
    float width = right - left;

    if(height <= 0.0F || width <= 0.0F) return CropArea(0 VH, 0 VW, 0 VH, 0 VW);

    return CropArea(top VH, left VW, height VH, width VW);
}