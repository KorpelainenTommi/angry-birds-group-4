#ifndef UI_CONSTANTS_HPP
#define UI_CONSTANTS_HPP

#include <SFML/Graphics/Color.hpp>

// A file defining the color scheme and style of the program

namespace ui {

    constexpr char* AppName = "AngryTeekkari";
    constexpr char* AppVersion = "alpha 1.0";
    constexpr unsigned int AppMinWidth = 266; //Currently unused
    constexpr unsigned int AppMinHeight = 200;

    const sf::Color DefaultTextColor = {0, 0, 0};

}

#endif