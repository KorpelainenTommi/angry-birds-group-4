#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP

#include <math.h>
#include <memory>
#include <ui.hpp>
#include <screens/Screen.hpp>

class DemoScreen : public Screen {
public:
    DemoScreen() {

        //Example of adding some elements

        auto title = std::make_unique<Label>(ui::AppName);
        auto version = std::make_unique<Label>(ui::AppVersion);
        title->SetPosition(0.0F, 0.2F);
        title->SetSize(1.0F, 0.05F);
        version->SetPosition(0.0F, 0.95F);
        version->SetSize(0.2F, 0.05F);
        menu_.push_back(std::move(title));
        menu_.push_back(std::move(version));
    }

    virtual void Render(const RenderSystem& r) {

        //Some sample stuff for game rendering

        
        float x = sin(clock.getElapsedTime().asSeconds()) * 20.0F;
        //c.zoom = 0.5F; //Camera zoom
        //c.xm = x; //Center camera on moving object, comment this out for static camera
        //r.RenderSprite(SpriteID::glass_block1x1, 0, 0, 80, 0, c); //Background
        r.RenderSprite(SpriteID::metal_block1x1, x, 0, 5, clock.getElapsedTime().asSeconds() * 20, c);

        Screen::Render(r);
    }
private:



    Camera c;
    sf::Clock clock;

};


#endif