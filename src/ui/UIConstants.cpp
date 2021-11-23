#include <ui/UIConstants.hpp>

float ui::toVHFloat(const ui::pfloat& p){
    return p.p ? p.f * aspectRatio : p.f;
}

float ui::toVWFloat(const ui::pfloat& p){
    return p.p ? p.f : p.f / ui::aspectRatio;
}