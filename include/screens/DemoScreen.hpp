#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP

#include <math.h>
#include <memory>
#include <ui.hpp>
#include <screens/Screen.hpp>


//An example screen demonstrating some ui and rendering stuff


class DemoScreen : public Screen {
public:
    DemoScreen(Application& app) : Screen(app) {

        //Example of adding some elements

        auto title = std::make_unique<Label>(ui::AppName);
        auto version = std::make_unique<Label>(ui::AppVersion);
        title->SetPosition(0 VW, 20 VH);
        title->SetSize(100 VW, 5 VH);
        version->SetPosition(0 VW, 95 VH);
        version->SetSize(20 VW, 5 VH);

        menu_.push_back(std::move(title));
        menu_.push_back(std::move(version));
    }

    virtual bool OnMouseDown(const sf::Mouse::Button& e, float x, float y) {
        if(e == sf::Mouse::Button::Right) {
            mDown = true;
            mouseX = x;
            mouseY = y;
            mouseX.Record();
            mouseY.Record();
        }
        return false;
    }

    virtual bool OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
        if(e == sf::Mouse::Button::Right) {
            mDown = false;
        }
        return false;
    }

    virtual bool OnMouseScroll(const sf::Event::MouseWheelScrollEvent& e) {
        c.zoom -= e.delta * 0.1F;
        if(c.zoom <= 0.1F) c.zoom = 0.1F;
        return false;
    }



    virtual bool OnMouseMove(float x, float y) {
        if(mDown) {
            mouseX = x;
            mouseY = y;
            c.x -= ph::FullscreenPlayArea * c.zoom * (mouseX.f1 - mouseX.f0);
            c.y += ph::FullscreenPlayArea * c.zoom * (mouseY.f1 - mouseY.f0);
            mouseX.Record();
            mouseY.Record();
        }
        return false;
    }

    virtual void Update() {
        //Record tfloat values at the start of physics update
        x.Record();
        c.Record();
        rot.Record();

        //x position at time t will be something between -20 meters and 20 meters
        x = sin(clock.getElapsedTime().asSeconds()) * 20.0F;

        //c.zoom = 0.5F; //Camera zoom
        //c.x = x; //Center camera on moving object, comment this out for static camera

        //rotation at time t
        rot = clock.getElapsedTime().asSeconds() * 20;
    }

    virtual void Render(const RenderSystem& r) {

        //Additional rendering for some gamelike stuff.
        //In an actual implementation, this should instead be done through a collection of gameobjects
        //that all have their own render method etc.

        r.RenderSprite(SpriteID::glass_block1x1, 0, 0, 80, 0, c); //Background

        r.RenderSprite(SpriteID::metal_block1x1, x, 0, 5, rot, c);

        r.RenderRect({0, 255, 0}, x, 5, 2.0F, 3.0F, rot, c);

        r.RenderOval({0, 0, 255}, x, -5, 2.0F, 3.0F, rot, c);

        r.RenderText("EXAMPLE", x, 15, 5, rot, c, {255, 0, 0}, FontID::source_serif);

        Screen::Render(r);
    }

private:
    bool mDown = false;

    //these tfloats are simply used here for storing previous values
    //they have nothing to do with the interpolation system
    ph::tfloat mouseX;
    ph::tfloat mouseY;

    //These are updated in Update, and get Record called at the start of it.
    ph::tfloat x;
    ph::tfloat rot;
    Camera c;
    sf::Clock clock;

};


#endif