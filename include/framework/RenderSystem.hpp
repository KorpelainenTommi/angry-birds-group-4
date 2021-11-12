#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <string>
#include <gameplay/Camera.hpp>
#include <ui/UIConstants.hpp>
#include <gameplay/Physics.hpp>
#include <SFML/Graphics.hpp>
#include <framework/ResourceManager.hpp>

class RenderSystem {
public:
        
    RenderSystem(sf::RenderTarget& canvas, const ResourceManager& resourceManager) : resourceManager_(resourceManager), canvas_(canvas) {}

    //For the definition of screen independent coordinates, see gameplay/Physics.hpp

    /* Render a sprite in screen independent coordinates (meters). This is useful for game objects.
     * The shape is defined by the sprite itself.
     */
    void RenderSprite(SpriteID id, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, const Camera& camera) const;

    /// Render a sprite in relative coordinates. This is useful for UI
    void RenderSprite(SpriteID id, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, sf::Color color = sf::Color(255, 255, 255)) const;

    /// Render a single color rectangle in screen independent coordinates
    void RenderRect(sf::Color color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const;

    /// Render a single color rectangle in relative coordinates
    void RenderRect(sf::Color color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const;

    /// Render text in screen independent coordinates. Font size is defined by height and width is dependent on string length
    void RenderText(const std::string& text, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot,
    const Camera& camera, sf::Color color = ui::DefaultTextColor, FontID id = ui::DefaultFont) const;

    /// Render text in relative coordinates. Fontsize is defined by height h
    void RenderText(const std::string& text, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h,
    sf::Color color = ui::DefaultTextColor, FontID id = ui::DefaultFont, ui::TextAlign textAlign = ui::TextAlign::center) const;

    /// Measures the width of string of text at a given height. Returns the units in vw or vh depending on the argument p
    ui::pfloat MeasureText(const std::string& text, ui::pfloat h, ui::pfloat::P p = ui::pfloat::P::vw, FontID id = ui::DefaultFont) const;

    /// Render a single color oval in relative coordinates
    void RenderOval(sf::Color color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const;

    /// Render a single color oval in screen independent coordinates
    void RenderOval(sf::Color color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const;



    // NOTE! functions for more advanced rendering (eg. rendering to a subtarget of the screen or an external view) will get added later
    // These will almost certainly be necessary for implementing more sophisticated UI elements



private:

    //Allow Application to set these values
    friend class Application;
    float ALPHA;
    float WW;
    float HH;

    sf::RenderTarget& canvas_;
    const ResourceManager& resourceManager_;
};

#endif