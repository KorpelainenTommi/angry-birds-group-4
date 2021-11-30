#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/Level.hpp>
#include <gameplay/Physics.hpp>
#include <screens/Screen.hpp>
#include <ui/RoundIcon.hpp>
#include <screens/MainMenu.hpp>

class GameScreen : public Screen {
public:

    /// Create a screen with an empty Game
    GameScreen(Application& app) : Screen(app), game_(*this) {
        auto rce = std::make_shared<RoundIcon>(1 VH, 1 VH, 3 VH, SpriteID::ui_button_exit);
        rce->SetMouseDownHandler([this, &app](){
            this->Confirm("Do you want to quit to main menu?", [&app](bool b){
                if(b) app.TransitionTo(std::make_unique<MainMenu>(app));
            });
        });
        menu_.push_back(rce);
    }

    /// Create a screen and start the Game with the selected level
    GameScreen(Application& app, const Level& initialLevel) : Screen(app), game_(*this, initialLevel) {
        auto rce = std::make_shared<RoundIcon>(1 VH, 1 VH, 3 VH, SpriteID::ui_button_exit);
        rce->SetMouseDownHandler([this, &app](){
            this->Confirm("Do you want to quit to main menu?", [&app](bool b){
                if(b) app.TransitionTo(std::make_unique<MainMenu>(app));
            });
        });
        menu_.push_back(rce);
    }
    
    virtual void Update() { game_.Update(); }
    virtual void Render(const RenderSystem& r){
        game_.Render(r);
        Screen::Render(r);
    }

    virtual bool OnMouseDown(const sf::Mouse::Button& e, float x, float y) {
        if(Screen::OnMouseDown(e, x, y)) return true;
        if(game_.OnMouseDown(e, x, y)) return true;

        //move this code to game
        //=====================================================================
        if(e == sf::Mouse::Button::Right) {
            mDown = true;
            mouseX = x;
            mouseY = y;
            mouseX.Record();
            mouseY.Record();
            return true;
        }
        if(e == sf::Mouse::Button::Left) {
            const Camera& cam = game_.GetCamera();
            float cw = ph::fullscreenPlayArea;
            float ch = cw / ui::aspectRatio;
            float xPos = cam.x  + (x * cw - 0.5F * cw ) * cam.zoom;
            float yPos = cam.y + ((1.0F - y) * ch - 0.5F * ch) * cam.zoom;
            game_.CreateObject(gm::GameObjectType::block_wood1x1, xPos, yPos);
        }
        if(e == sf::Mouse::Button::Middle) {
            const Camera& cam = game_.GetCamera();
            float cw = ph::fullscreenPlayArea;
            float ch = cw / ui::aspectRatio;
            float xPos = cam.x  + (x * cw - 0.5F * cw ) * cam.zoom;
            float yPos = cam.y + ((1.0F - y) * ch - 0.5F * ch) * cam.zoom;
            game_.CreateObject(gm::GameObjectType::block_metal1x1, xPos, yPos);
        }
        //=====================================================================

        return false;
    }

    virtual bool OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
        if(Screen::OnMouseUp(e, x, y)) return true;
        if(game_.OnMouseUp(e, x, y)) return true;

        //move this code to game
        //=====================================================================
        if(e == sf::Mouse::Button::Right) {
            mDown = false;
        }
        //=====================================================================

        return false;
    }

    virtual bool OnMouseScroll(float delta, float xw, float yh) {
        if(Screen::OnMouseScroll(delta, xw, yh)) return true;
        if(game_.OnMouseScroll(delta, xw, yh)) return true;

        //move this code to game
        //=====================================================================
        float zoom = game_.GetCamera().zoom;
        zoom -= delta * 0.1F;
        if(zoom <= 0.1F) game_.SetCameraZoom(0.1F);
        else if(zoom > 1.0F) game_.SetCameraZoom(1.0F);
        else game_.SetCameraZoom(zoom);
        //=====================================================================

        return true;
    }



    virtual bool OnMouseMove(float x, float y) {
        bool b = Screen::OnMouseMove(x, y);
        b = game_.OnMouseMove(x, y) || b;

        //move this code to game
        //=====================================================================
        if(mDown) {
            mouseX = x;
            mouseY = y;
            Camera c = game_.GetCamera();
            c.x -= ph::fullscreenPlayArea * c.zoom * (mouseX.f1 - mouseX.f0);
            c.y += ph::fullscreenPlayArea * c.zoom * (mouseY.f1 - mouseY.f0);
            game_.SetCameraPos(c.x, c.y);
            mouseX.Record();
            mouseY.Record();
        }
        //=====================================================================

        return b;
    }    

    virtual ~GameScreen() = default;

    void OnGameCompleted(int score){};

    void OnGameLost(){};

    void OnScoreChange(int score){};

protected:

    //move these to game
    //=====================================================================
    bool mDown = false;
    ph::tfloat mouseX;
    ph::tfloat mouseY;
    //=====================================================================

    Game game_;

};


#endif
