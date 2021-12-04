#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include <gameplay/Game.hpp>
#include <gameplay/Level.hpp>
#include <gameplay/Physics.hpp>
#include <screens/Screen.hpp>
#include <screens/MainMenu.hpp>
#include <ui/TextLine.hpp>
#include <gameplay/Person.hpp>

class GameScreen : public Screen {
public:

    /// Create a screen and start the Game with the selected level
    GameScreen(Application& app, const Level& initialLevel);
    
    virtual void Update();

    virtual void Render(const RenderSystem& r);

    virtual bool OnMouseDown(const sf::Mouse::Button& e, float x, float y);

    virtual bool OnMouseUp(const sf::Mouse::Button& e, float x, float y);
    
    virtual bool OnMouseScroll(float delta, float xw, float yh);

    virtual bool OnMouseMove(float x, float y);
    
    virtual ~GameScreen() = default;

    void Exit();

    void Restart();

    void OnGameCompleted(int score);

    void OnGameLost();

    void OnScoreChange(int score);

    /**
     * Game should call this whenever the the list of projectiles should be updated.
     */
    void UpdateProjectileList(std::vector<SpriteID /*this can be changed*/>){}

    Game& GetGame(){return game_;}

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


    Game game_;
    Level level_;
    std::shared_ptr<TextLine> scoreLabel_;
    std::shared_ptr<TextLine> timeLabel_;

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
