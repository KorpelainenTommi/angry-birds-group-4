#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <string>
#include <gameplay/Camera.hpp>
#include <ui/UIConstants.hpp>
#include <gameplay/Physics.hpp>
#include <SFML/Graphics.hpp>
#include <framework/ResourceManager.hpp>

/// Framework class for drawing sprites and basic shapes with relative or absolute units
class RenderSystem {
public:
        
    /// Construct a RenderSystem that draws to this Window, and queries sprites from this ResourceManager
    RenderSystem(sf::RenderWindow& window, ResourceManager& resourceManager) : resourceManager_(resourceManager), window_(window) {}

    //For the definition of screen independent coordinates, see gameplay/Physics.hpp

    /* Render a sprite in screen independent coordinates (meters). This is useful for game objects.
     * The shape is defined by the sprite itself.
     */
    void RenderSprite(SpriteID id, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, const Camera& camera, const sf::Color& color = sf::Color(255, 255, 255)) const;

    /// Render a sprite in relative coordinates. This is useful for UI
    void RenderSprite(SpriteID id, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const sf::Color& color = sf::Color(255, 255, 255)) const;

    /// Render a sprite in relative coordinates, but restrict drawing to a cropped portion
    void RenderSprite(SpriteID id, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea, const sf::Color& color = sf::Color(255, 255, 255)) const;

    /// Render a single color rectangle in screen independent coordinates
    void RenderRect(const sf::Color& color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const;

    /// Render a single color rectangle in relative coordinates
    void RenderRect(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const;

    /// Render a single color rectangle in relative coordinates, but restrict drawing to a cropped portion
    void RenderRect(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea) const;

    /// Render text in screen independent coordinates. Font size is defined by height and width is dependent on string length
    void RenderText(const std::string& text, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot,
    const Camera& camera, const sf::Color& color = ui::textColor, FontID id = ui::defaultFont) const;

    /// Render text in relative coordinates. Fontsize is defined by height h
    void RenderText(const std::string& text, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h,
    const sf::Color& color = ui::textColor, FontID id = ui::defaultFont, ui::TextAlign textAlign = ui::TextAlign::center) const;

    /// Render text in relative coordinates, but restrict drawing to a cropped portion
    void RenderText(const std::string& text, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h,
    const ui::CropArea& cropArea, const sf::Color& color = ui::textColor, FontID id = ui::defaultFont, ui::TextAlign textAlign = ui::TextAlign::center) const;

    /// Measures the width of string of text at a given height. Returns the units in vw or vh depending on the argument p
    ui::pfloat MeasureText(const std::string& text, ui::pfloat h, ui::pfloat::P p = ui::pfloat::P::vw, FontID id = ui::defaultFont) const;

    /// Render a single color oval in screen independent coordinates
    void RenderOval(const sf::Color& color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const;

    /// Render a single color oval in relative coordinates
    void RenderOval(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const;

    /// Render a single color oval in relative coordinates, but restrict drawing to a cropped portion
    void RenderOval(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea) const;

    /// Not yet implemented, but can be done later
    void RenderAnimation(AnimationID id, int frame, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {}

    /// Get the screen space coordinates of this world position when translated with a Camera
    sf::Vector2f GetRelativeCoords(sf::Vector2f coords, const Camera& camera) const;
    
    bool ContainsCoordinates(SpriteID id, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, sf::Vector2f mouseCoords) const;
    
    sf::Sprite MakeSprite(SpriteID id, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot) const;
    
    
    bool IntersectWithSprite(SpriteID id, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, sf::Sprite sprite) const;
    
    bool CheckGround(sf::Sprite s) const;
    
private:

    //Allow Application to set these values
    friend class Application;

    /// Interpolation value for drawing between physics updates
    float ALPHA;

    /// Window width
    float WW;

    /// Window height
    float HH;



    
    sf::RenderWindow& window_;
    ResourceManager& resourceManager_;



    /// Translate this Drawable with a camera, then draw it
    void CameraDraw(const sf::Drawable& shape, const Camera& camera) const;

    /// Resolve the pixel coordinates of this Shape, then draw it
    void RenderRelative(sf::Shape& shape, const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const;

    /// Resolve the pixel coordinates of this Shape drawn with this CropArea
    void RenderRelativeCrop(sf::Shape& shape, const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea) const;
    
    /// Resolve the camera position of this Shape, then translate it with a camera and draw it
    void RenderAbs(sf::Shape& shape, const sf::Color& color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const;
    
};

#endif
