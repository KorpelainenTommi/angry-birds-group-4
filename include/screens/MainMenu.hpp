#ifndef SCREENS_MAINMENU_HPP
#define SCREENS_MAINMENU_HPP

#include <screens/Screen.hpp>

class MainMenu : public Screen {
public:
    MainMenu(Application& app);

    virtual void Render(const RenderSystem&);
};

#endif