#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <ui/UIConstants.hpp>
#include <gameplay/Physics.hpp>

/* A Camera has a position in world space, and a zoom.
 * zoom < 1 means zooming in, zoom > 1 means zooming out.
 * zoom = 1 is fullscreen.
 * 
 * As per the definition in gameplay/Physics.hpp, a camera at fullscreen zoom
 * will see an area that is 50 meters wide.
 */

/// @brief A camera can be moved and zoomed, and can be used to translate object positions
struct Camera {
    
    /// @brief Camera x coordinate
    float x = 0;
    /// @brief Camera y coordinate
    float y = 0;
    /// @brief Camera rotation
    float rot = 0;
    /// @brief Camera zoom
    float zoom = 1;

    /// @brief Set camera at fullscreen zoom, and at the center of the world
    void SetFullscreen() {
        x = 0;
        y = 0.5F * ph::fullscreenPlayArea / ui::aspectRatio - ph::groundThickness;
        rot = 0;
        zoom = 1;
    }
};



#endif
