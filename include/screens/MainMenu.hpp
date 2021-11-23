#ifndef SCREENS_MAINMENU_HPP
#define SCREENS_MAINMENU_HPP

#include <screens/Screen.hpp>
#include <ui/ListElement.hpp>

class MainMenu : public Screen {
public:
    MainMenu(Application& app);

    virtual void Render(const RenderSystem&);

private:
    std::shared_ptr<ListElement> list_;
    ui::pfloat curListW_ = 0 VW;
    ui::pfloat curElementW_ = 0 VW;
    ui::pfloat listSpacing_ = 1 VH;

    ui::pfloat calcListWidth() const;

    ui::pfloat calcListElementWidth() const;

    void checkListWidth();

    //this will change later on
    void addLevel(std::string level);
};

#endif