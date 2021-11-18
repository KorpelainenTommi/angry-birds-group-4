#ifndef UI_CONSTANTS_HPP
#define UI_CONSTANTS_HPP

#include <string>
#include <framework/Resources.hpp>
#include <SFML/Graphics/Color.hpp>

// A file defining the color scheme and style of the program

#define VW % ui::pfloat(1, ui::pfloat::P::vw)
#define VH % ui::pfloat(1, ui::pfloat::P::vh)

namespace ui {


    struct pfloat {
    public:
        enum P { vh, vw };
        pfloat() : f(0), p(P::vw) {}
        pfloat(const float& ff, P pp) { f = ff; p = pp; }
        operator float() const { return f; }
        pfloat operator-() const { return { -f, p }; }
        pfloat& operator=(const pfloat& pf) { f = pf.f; p = pf.p; return *this; }
        pfloat& operator*=(const float& ff) { f *= ff; return *this; }
        pfloat& operator/=(const float& ff) { f /= ff; return *this; }
        pfloat& operator+=(const float& ff) { f += ff; return *this; }
        pfloat& operator-=(const float& ff) { f -= ff; return *this; }

        float f;
        P p;
    };
    inline ui::pfloat operator%(const float& ff, const ui::pfloat& pp) { return { ff, pp.p }; }
/* VW and VH should be used like this:
 *
 * auto x = 50 VW;
 * x = 13 VH;
 * 
 * auto y = 19.5F VW;
 * 
 * y = x;                              y will be 13 VH
 * 
 * ui::pfloat z = 3 VW;
 * z = -z                              this is fine
 * 
 * 
 * y = (5 * x) VW;                     y will be 5*13 VW
 * 
 * x = (x + y * 13 - 40 / x * x ) VH;  value of the expression VH
 * 
 * Dont' do this:
 * 
 * x = 4                               unknown units, put VW or VH after it
 * 
 * x = VW 4                            no
 * 
 * x = VW                              technically fine
 * 
 * x = VW VH VW VH                     same as 1 VH but ugly
 * 
 * y = x * y * x * y VW                needs brackets: y = (expression) VW works
 * 
 * 
 * 
 * //Notes:
 * x == y, x != y, x > y etc. compare by float value, and don't care about VW VH because I was lazy
 * 
 * something, something, if all else fails there's access to x.f and x.p directly
 * 
 * 
 * 
 */

    const std::string AppName = "AngryTeekkari";
    const std::string AppVersion = "alpha 1.1";
    constexpr unsigned int AppMinWidth = 266; //Currently unused
    constexpr unsigned int AppMinHeight = 200;
    constexpr unsigned int TargetFramerate = 180;
    constexpr float TargetFrametime = 1.0F / TargetFramerate;

    enum TextAlign { left, center, right };
    const FontID DefaultFont = FontID::source_serif;
    const sf::Color DefaultTextColor = {0, 0, 0};
    const sf::Color backgroundColor = {255, 255, 255};
    const sf::Color backgroundColor2 = {221, 221, 221};
    const sf::Color textColor = {0, 0, 0};
    const sf::Color buttonBackgroundColor = {204, 204, 204};
    const sf::Color buttonTextColor = {0, 0, 0};

    const FontID defaultFont = FontID::source_serif;

    const float defaultAbsoluteFontSize = 16.0F;
    const ui::pfloat defaultFontSize = (100 * defaultAbsoluteFontSize / 1080) VH;


    //Don't touch this unless u are Application
    //plz
    extern float windowWidth;
    extern float windowHeight;
    extern float aspectRatio;

}

#endif