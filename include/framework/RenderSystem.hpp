#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <gameplay/Camera.hpp>
#include <framework/ResourceManager.hpp>

class RenderSystem {
public:
        
    RenderSystem(sf::RenderWindow& window, ResourceManager& resourceManager) : 
    window_(window), resourceManager_(resourceManager) {}

    //For the definition of screen independent coordinates, see gameplay/Physics.hpp

    /* Render a sprite in screen independent coordinates (meters). This is useful for game objects.
     * The shape is defined by the sprite itself.
     */
    void RenderSprite(SpriteID id, float xm, float ym, float hm, float rot, const Camera& camera) const;

    /// Render a sprite in relative coordinates. This is useful for UI
    void RenderSprite(SpriteID id, float xw, float yh, float ww, float hh, sf::Color color = sf::Color(255, 255, 255)) const;

    /// Render a single color rectangle in relative coordinates
    void RenderSystem::RenderRect(sf::Color color, float xw, float yh, float ww, float hh) const;

    /// Render text in relative coordinates
    void RenderText(const std::string& text, float xw, float yh, float ww, float hh, sf::Color color, FontID id) const;

private:

    //Allow application to set these values
    friend class Application;
    float WW;
    float HH;

    sf::RenderWindow& window_;
    ResourceManager& resourceManager_;
};

#endif