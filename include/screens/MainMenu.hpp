#ifndef SCREENS_MAINMENU_HPP
#define SCREENS_MAINMENU_HPP

#include <screens/Screen.hpp>
#include <ui/ListElement.hpp>
#include <ui/Button.hpp>

class MainMenu : public Screen {
public:
    MainMenu(Application& app);

    virtual void Render(const RenderSystem&);

    void SelectLevel(const std::string level, std::weak_ptr<Button> button);

private:
    const sf::Color selectedLevelBackground_ = {200, 200, 255};

    std::shared_ptr<ListElement> list_;
    ui::pfloat curListW_ = 0 VW;
    ui::pfloat curElementW_ = 0 VW;
    ui::pfloat listSpacing_ = 1 VH;
    std::shared_ptr<ColoredElement> listTop_;
    std::shared_ptr<ColoredElement> listBottom_;
    std::pair<std::string, std::weak_ptr<Button>> selectedLevel_;
    bool hasSelectedLevel_ = false;

    ui::pfloat calcListWidth() const;

    ui::pfloat calcListElementWidth() const;

    void checkListWidth();

    //this will change later on
    void addLevel(std::string level);
};

#endif