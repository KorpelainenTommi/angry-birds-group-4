#ifndef SCREENS_MAINMENU_HPP
#define SCREENS_MAINMENU_HPP

#include <screens/Screen.hpp>
#include <ui/ListElement.hpp>
#include <ui/Button.hpp>
#include <ui/MultilineText.hpp>

class MainMenu : public Screen {
public:
    MainMenu(Application& app);

    virtual void Render(const RenderSystem&);

    /**
     * This should be used only by buttons created in Mainmenu::addLevel()
     */
    void SelectLevel(const std::string level, std::weak_ptr<Button> button);

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
    ui::pfloat curListW_ = 0 VW;
    ui::pfloat curElementW_ = 0 VW;
    std::shared_ptr<ColoredElement> listTop_;
    std::shared_ptr<ColoredElement> listBottom_;
    std::pair<std::string, std::weak_ptr<Button>> selectedLevel_;
    bool hasSelectedLevel_ = false;
    std::vector<std::shared_ptr<Element>> rightSideElements_;
    ui::pfloat rightSideElementW_ = 0 VW;
    std::shared_ptr<MultilineText> scoreboard_;

    ui::pfloat calcListWidth() const;

    ui::pfloat calcListElementWidth() const;

    void checkListWidth();

    //this will change later on
    void addLevel(std::string level);

    ui::pfloat calcRightSideElementWidth() const;

    void checkRightSideElementWidth();

    void addRightSideButton(
        const std::string& text, 
        const std::function<void()> mouseDownHandler
    );

    ui::pfloat getRightSideLeft() const;

    float getRightSideButtonsVHFloatHeight() const;

    void addScoreboard();

    float addScoreboardHeader(const ui::pfloat&);

    void addScoreboardMultiline(const ui::pfloat& top, const ui::pfloat& left, const ui::pfloat& height);
};

#endif