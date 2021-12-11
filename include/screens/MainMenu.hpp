#ifndef SCREENS_MAINMENU_HPP
#define SCREENS_MAINMENU_HPP

#include <screens/Screen.hpp>
#include <ui/ListElement.hpp>
#include <ui/Button.hpp>
#include <ui/MultilineText.hpp>
#include <gameplay/Level.hpp>

class MainMenu : public Screen {
public:
    MainMenu(Application& app);

    virtual void Render(const RenderSystem&);

    /**
     * This should be used only by buttons created in Mainmenu::addLevel()
     */
    void SelectLevel(const Level& level, std::weak_ptr<Button> button, int id);

    Level GetSelectedLevel() const {return selectedLevel_.first;};

    ui::pfloat calcListWidth() const;

    ui::pfloat calcListElementWidth() const;

    ui::pfloat calcRightSideElementWidth() const;

    ui::pfloat calcListTop() const;

    ui::pfloat calcListHeight() const;

    ui::pfloat calcListBottomTop() const;

    ui::pfloat calcRightSideButtonTop(unsigned char buttonNumber) const;

    ui::pfloat calcRightSideLeft() const;

    ui::pfloat calcScoreboardMultilineTop() const;

    ui::pfloat calcScoreboardMultilineHeight() const;

    void deleteSelectedLevel();

private:
    const ui::pfloat padding_ = 2 VH;
    const ui::pfloat listPadding_ = 1 VH;
    const ui::pfloat listSpacing_ = 1 VH;
    const ui::pfloat spacingY_ = 1 VH;
    const ui::pfloat spacingX_ = 1 VW;
    const ui::pfloat buttonHeight_ = 5 VH;
    const ui::pfloat scoreboardLeftPadding_ = 0.5 VW;
    const sf::Color selectedLevelBackground_ = ui::highlightColor;
    const ui::pfloat scoreboardHeaderSize_ = ui::defaultFontSize * 4;

    std::shared_ptr<ListElement> list_;
    std::shared_ptr<ColoredElement> listTop_;
    std::shared_ptr<ColoredElement> listBottom_;
    std::pair<Level, std::weak_ptr<Button>> selectedLevel_;
    bool hasSelectedLevel_ = false;
    int selectedLevelButtonListID_;
    std::shared_ptr<MultilineText> scoreboard_;
    std::vector<std::shared_ptr<Button>> deactivatingButtons_;
    unsigned char nofButtons_ = 0;

    void generateLevels();

    void addLevel(Level level);

    void addRightSideButton(
        unsigned char buttonNumber, 
        const std::string& text, 
        const std::function<void()> mouseDownHandler,
        bool deactivating = false
    );

    void addScoreboard();

    std::shared_ptr<TextElement> addScoreboardHeader();

    std::shared_ptr<MultilineText> addScoreboardMultiline();

    std::string generateScoreboardText(const Level& level) const;

    std::shared_ptr<ListElement> addList();

    std::shared_ptr<ListElement> addListBody();

    std::shared_ptr<ColoredElement> addListTop();

    std::shared_ptr<ColoredElement> addListBottom();
};

#endif