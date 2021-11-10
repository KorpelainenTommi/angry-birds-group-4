#include <ui/Label.hpp>
#include <framework/RenderSystem.hpp>

void Label::Render(const RenderSystem& r) {
    r.RenderRect({255, 255, 255, 255}, xw_, yh_, ww_, hh_);
    r.RenderText(text_, xw_, yh_, ww_, hh_, color_, font_);
}