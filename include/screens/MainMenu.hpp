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
    void SelectLevel(const Level& level, std::weak_ptr<Button> button);

    Level GetSelectedLevel() const {return selectedLevel_.first;};

    ui::pfloat calcListWidth() const;

    ui::pfloat calcListElementWidth() const;

    ui::pfloat calcRightSideElementWidth() const;

    ui::pfloat calcListTop() const;

    ui::pfloat calcListHeight() const;

    ui::pfloat calcListBottomTop() const;

private:
    const ui::pfloat padding_ = 2 VH;
    const ui::pfloat listPadding_ = 1 VH;
    const ui::pfloat listSpacing_ = 1 VH;
    const ui::pfloat spacingY_ = 1 VH;
    const ui::pfloat spacingX_ = 1 VW;
    const ui::pfloat buttonHeight_ = 5 VH;
    const ui::pfloat scoreboardLeftPadding_ = 0.5 VW;
    const sf::Color selectedLevelBackground_ = ui::highlightColor;

    std::shared_ptr<ListElement> list_;
    std::shared_ptr<ColoredElement> listTop_;
    std::shared_ptr<ColoredElement> listBottom_;
    std::pair<Level, std::weak_ptr<Button>> selectedLevel_;
    bool hasSelectedLevel_ = false;
    std::vector<std::shared_ptr<Element>> rightSideElements_;
    ui::pfloat rightSideElementW_ = 0 VW;
    std::shared_ptr<MultilineText> scoreboard_;
    std::vector<std::shared_ptr<Button>> deactivatingButtons_;

    void generateLevels();

    void addLevel(Level level);

    void checkRightSideElementWidth();

    void addRightSideButton(
        const std::string& text, 
        const std::function<void()> mouseDownHandler,
        bool deactivating = false
    );

    ui::pfloat getRightSideLeft() const;

    float getRightSideButtonsVHFloatHeight() const;

    void addScoreboard();

    float addScoreboardHeader(const ui::pfloat&);

    void addScoreboardMultiline(const ui::pfloat& top, const ui::pfloat& left, const ui::pfloat& height);

    std::string generateScoreboardText(const Level& level) const;

    std::shared_ptr<ListElement> addList();

    std::shared_ptr<ListElement> addListBody();

    std::shared_ptr<ColoredElement> addListTop();

    std::shared_ptr<ColoredElement> addListBottom();
};

#endif