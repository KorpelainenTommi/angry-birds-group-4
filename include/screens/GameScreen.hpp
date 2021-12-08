#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <memory>
#include <gameplay/Editor.hpp>
#include <gameplay/Level.hpp>
#include <gameplay/Physics.hpp>
#include <screens/Screen.hpp>
#include <screens/MainMenu.hpp>
#include <ui/TextLine.hpp>
#include <gameplay/Person.hpp>
#include <ui/InputElement.hpp>

class GameScreen : public Screen {
public:

    /// Create a screen and start the Game with the selected level
    GameScreen(Application& app, const Level& initialLevel, bool editorMode = false);
    
    virtual void Update();

    virtual void Render(const RenderSystem& r);

    virtual bool OnMouseDown(const sf::Mouse::Button& e, float x, float y);

    virtual bool OnMouseUp(const sf::Mouse::Button& e, float x, float y);
    
    virtual bool OnMouseScroll(float delta, float xw, float yh);

    virtual bool OnMouseMove(float x, float y);

    virtual bool OnKeyDown(const sf::Event::KeyEvent&);

    virtual bool OnKeyUp(const sf::Event::KeyEvent&);
    
    virtual ~GameScreen() = default;

    void Exit();

    void Restart();

    /**
     * requiredMaxScore is not the absolute max score but the one that is required for max points.
     */
    void OnGameCompleted(int score, int requiredMaxScore);

    void OnGameLost();

    void OnScoreChange(int score);

    /**
     * Game should call this whenever the the list of projectiles should be updated.
     */
    void UpdateProjectileList(std::vector<SpriteID /*this can be changed*/>);

    Game& GetGame();

    Editor& GetEditor();

    bool IsInEditorMode() const {return editorMode_;}

    /**
     * button number is the number of the button from left starting from 1.
     */
    ui::pfloat calcTopLeftButtonLeft(unsigned char buttonNumber) const;

    /**
     * labelNumber is the number of the label from top starting from 1.
     */
    ui::pfloat calcTopRightLabelTop(unsigned char labelNumber) const;

    ui::pfloat calcTopRightLabelLeft() const;

    ui::pfloat calcVictoryMessageStarTop() const;

    ui::pfloat calcVictoryMessageStarLeft(char starNumber) const;

    ui::pfloat calcVictoryMessageScoreTop() const;

    ui::pfloat calcVictoryMessageContentLeft() const;

    ui::pfloat calcVictoryMessageContentWidth() const;

    ui::pfloat calcVictoryMessageNicknamePromptTop() const;

    ui::pfloat calcVictoryMessageInputTop() const;

    void saveScore(const std::string& name, int score);

    ui::pfloat calcProjectileBarWidth() const;

    ui::pfloat calcProjectileBarTop() const;

    ui::pfloat calcProjectileBarBottomTop() const;

    ui::pfloat calcProjectileBarBodyTop() const;

    ui::pfloat calcProjectileBarBodyHeight() const;

    void selectProjectileIcon(std::shared_ptr<RoundIcon> i);

    ui::pfloat calcEditorPanelLeft() const;

    ui::pfloat calcEditorContentWidth() const;

    ui::pfloat calcEditorContentLeft() const;

    ui::pfloat calcEditorDropDownTop() const;

    void addDropDownContents(std::shared_ptr<TextElement> e);

    void setSelectedGameMode(LevelMode m);

private:
    const ui::pfloat topLeftButtonSpacing_ = 1 VH;
    const ui::pfloat topLeftButtonSize_ = 4 VH;
    const ui::pfloat topRightLabelLength_ = ui::defaultFontSize * 9;
    const ui::pfloat topRightLabelHeigth_ = ui::defaultFontSize;
    const ui::pfloat topRightLabelSpacing_ = 1 VH;
    const ui::pfloat victoryMessageHeight_ = 20 VH;
    const ui::pfloat victoryMessageWidth_ = 30 VW;
    const ui::pfloat victoryMessageStarSize_ = 5 VH;
    const ui::pfloat victoryMessageFontSize_ = ui::defaultFontSize;
    const ui::pfloat projectileBarHeight_ = 50 VH;
    const ui::pfloat projectileBarIconSize_ = 8 VH;
    const ui::pfloat projectileBarSpacing_ = 1 VH;
    const ui::pfloat editorPanelWidth_ = 20 VW;
    const ui::pfloat editorPanelPadding_ = 1 VH;
    const ui::pfloat editorPanelSpacing_ = 1 VH;
    const ui::pfloat editorFontSize_ = ui::defaultFontSize;

    std::unique_ptr<Game> game_;
    Level level_;
    std::shared_ptr<TextLine> scoreLabel_;
    std::shared_ptr<TextLine> timeLabel_;
    std::shared_ptr<ListElement> projectileList_;
    std::vector<std::size_t> iconIndexes_;
    std::shared_ptr<RoundIcon> selectedIcon_;
    bool hasSelectedIcon_ = false;
    bool editorMode_;
    std::shared_ptr<InputElement> editorNameInput_;
    LevelMode selectedGameMode_ = LevelMode::normal;

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

    void addEditorTopLeftButtons();

    void addTopRightLabels();

    std::shared_ptr<TextLine> addTopRightLabel(unsigned char labelNumber, const std::string& text);

    void addVictoryMessageStars(int score, int maxScore, std::vector<std::shared_ptr<Element>>& v);

    std::shared_ptr<RoundIcon> generateVictoryMessageStar(char starNumber, bool achieved);

    void addVictoryMessageScore(int score, std::vector<std::shared_ptr<Element>>& v);

    void addVictoryMessageNicknamePrompt(std::vector<std::shared_ptr<Element>>& v);

    std::shared_ptr<InputElement> generateVictoryMessageInput();

    void addProjectileBar();

    std::shared_ptr<ColoredElement> addListTop();

    std::shared_ptr<ColoredElement> addListBottom();

    void addList();

    void addProjectileIcon(SpriteID icon);

    void clearIcons();

    void addEditorPanel();

    void addEditorPanelBackground();

    void addEditorNameInput();

    void addEditorGameModeDropDown();
};


#endif
