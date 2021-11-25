#include <ui/RoundElement.hpp>
#include <math.h>

bool RoundElement::isInside(float xw, float yh) const {
    float xvh = xw * 100 * ui::aspectRatio;
    float yvh = yh * 100;
    float rvh = ui::toVHFloat(r_);
    float cxvh = getCenterVHFloatX(rvh);
    float cyvh = getCenterVHFloatY(rvh);
    if(distance(cxvh, cyvh, xvh, yvh) <= rvh) return true;
    return false;
}

float RoundElement::getCenterVHFloatX() const {
    return ui::toVHFloat(x_) + ui::toVHFloat(r_);
}

float RoundElement::getCenterVHFloatX(float rvh) const {
    return ui::toVHFloat(x_) + rvh;
}

float RoundElement::getCenterVHFloatY() const {
    return ui::toVHFloat(y_) + ui::toVHFloat(r_);
}

float RoundElement::getCenterVHFloatY(float rvh) const {
    return ui::toVHFloat(y_) + rvh;
}

float RoundElement::distance(float x1, float y1, float x2, float y2) const {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}