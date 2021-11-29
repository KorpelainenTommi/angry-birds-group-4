#include <ui/MessageBox.hpp>

void MessageBox::Render(const RenderSystem& r){
    r.RenderRect(ui::messageBoxBackgroundColor, 0 VW, 0 VH, 100 VW, 100 VH);
    r.RenderRect(backgroundColor_, x_, y_, w_, h_);
}