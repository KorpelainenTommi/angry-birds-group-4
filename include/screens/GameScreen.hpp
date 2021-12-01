#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/Level.hpp>
#include <gameplay/Physics.hpp>
#include <screens/Screen.hpp>
#include <screens/MainMenu.hpp>
#include <ui/TextLine.hpp>
#include <sstream>

class GameScreen : public Screen {
public:

    /// Create a screen with an empty Game
    /*GameScreen(Application& app) : Screen(app), game_(*this) {
        auto rce = std::make_shared<RoundIcon>(1 VH, 1 VH, 3 VH, SpriteID::ui_button_exit);
        rce->SetMouseDownHandler([this, &app](){
            this->Confirm("Do you want to quit to main menu?", [&app](bool b){
                if(b) app.TransitionTo(std::make_unique<MainMenu>(app));
            });
        });
        menu_.push_back(rce);
    }*/

    /// Create a screen and start the Game with the selected level
    GameScreen(Application& app, const Level& initialLevel);
    /*GameScreen(Application& app, const Level& initialLevel) : Screen(app), game_(*this, initialLevel) {
        auto rce = std::make_shared<RoundIcon>(1 VH, 1 VH, 3 VH, SpriteID::ui_button_exit);
        rce->SetMouseDownHandler([this, &app](){
            this->Exit();
        });
        menu_.push_back(rce);
    }*/
    
    virtual void Update();

    virtual void Render(const RenderSystem& r);

    virtual bool OnMouseDown(const sf::Mouse::Button& e, float x, float y) {
        if(Screen::OnMouseDown(e, x, y)) return true;
        if(game_->OnMouseDown(e, x, y)) return true;

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
            const Camera& cam = game_->GetCamera();
            float cw = ph::fullscreenPlayArea;
            float ch = cw / ui::aspectRatio;
            float xPos = cam.x  + (x * cw - 0.5F * cw ) * cam.zoom;
            float yPos = cam.y + ((1.0F - y) * ch - 0.5F * ch) * cam.zoom;
            game_->CreateObject(gm::GameObjectType::block_wood1x1, xPos, yPos);
        }
        if(e == sf::Mouse::Button::Middle) {
            const Camera& cam = game_->GetCamera();
            float cw = ph::fullscreenPlayArea;
            float ch = cw / ui::aspectRatio;
            float xPos = cam.x  + (x * cw - 0.5F * cw ) * cam.zoom;
            float yPos = cam.y + ((1.0F - y) * ch - 0.5F * ch) * cam.zoom;
            game_->CreateObject(gm::GameObjectType::block_metal1x1, xPos, yPos);
        }
        //=====================================================================

        return false;
    }

    virtual bool OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
        if(Screen::OnMouseUp(e, x, y)) return true;
        if(game_->OnMouseUp(e, x, y)) return true;

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
        if(game_->OnMouseScroll(delta, xw, yh)) return true;

        //move this code to game
        //=====================================================================
        float zoom = game_->GetCamera().zoom;
        zoom -= delta * 0.1F;
        if(zoom <= 0.1F) game_->SetCameraZoom(0.1F);
        else if(zoom > 1.0F) game_->SetCameraZoom(1.0F);
        else game_->SetCameraZoom(zoom);
        //=====================================================================

        return true;
    }



    virtual bool OnMouseMove(float x, float y) {
        bool b = Screen::OnMouseMove(x, y);
        b = game_->OnMouseMove(x, y) || b;

        //move this code to game
        //=====================================================================
        if(mDown) {
            mouseX = x;
            mouseY = y;
            Camera c = game_->GetCamera();
            c.x -= ph::fullscreenPlayArea * c.zoom * (mouseX.f1 - mouseX.f0);
            c.y += ph::fullscreenPlayArea * c.zoom * (mouseY.f1 - mouseY.f0);
            game_->SetCameraPos(c.x, c.y);
            mouseX.Record();
            mouseY.Record();
        }
        //=====================================================================

        return b;
    }    

    virtual ~GameScreen() = default;

    void Exit();

    void Restart();

    void OnGameCompleted(int score){};

    void OnGameLost();

    void OnScoreChange(int score);

    std::shared_ptr<Game> GetGame(){return game_;}

    /**
     * button number is the number of the button from left starting from 1.
     */
    ui::pfloat calcTopLeftButtonLeft(unsigned char buttonNumber) const;

    /**
     * labelNumber is the number of the label from top starting from 1.
     */
    ui::pfloat calcTopRightLabelTop(unsigned char labelNumber) const;

    ui::pfloat calcTopRightLabelLeft() const;

private:
    const ui::pfloat topLeftButtonSpacing_ = 1 VH;
    const ui::pfloat topLeftButtonSize_ = 4 VH;
    const ui::pfloat topRightLabelLength_ = ui::defaultFontSize * 9;
    const ui::pfloat topRightLabelHeigth_ = ui::defaultFontSize;
    const ui::pfloat topRightLabelSpacing_ = 1 VH;

    //move these to game
    //=====================================================================
    bool mDown = false;
    ph::tfloat mouseX;
    ph::tfloat mouseY;
    //=====================================================================

    std::shared_ptr<Game> game_;
    Level level_;
    std::shared_ptr<TextLine> scoreLabel_;
    std::shared_ptr<TextLine> timeLabel_;

    template <typename T>
    std::string getString(T v) const {
        std::stringstream ss;
        ss << v;
        return ss.str();
    }

    /**
     * button number is the number of the button from left starting from 1.
     */
    std::shared_ptr<RoundIcon> addTopLeftButton(
        unsigned char buttonNumber, std::function<void()> callBack, const SpriteID& sprite
    );

    /**
     * button number is the number of the button from left starting from 1.
     */
    std::shared_ptr<RoundIcon> addTopLeftButton(
        unsigned char buttonNumber, const SpriteID& sprite
    );

    void addTopLeftButtons();

    std::shared_ptr<TextLine> addTopRightLabel(unsigned char labelNumber, const std::string& text);

    std::shared_ptr<TextLine> addScoreLabel();
};


#endif
