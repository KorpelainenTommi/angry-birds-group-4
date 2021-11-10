#ifndef CAMERA_HPP
#define CAMERA_HPP

/* A Camera has a position in world space, and a zoom.
 * zoom < 1 means zooming in, zoom > 1 means zooming out.
 * zoom = 1 is fullscreen.
 * 
 * As per the definition in gameplay/Physics.hpp, a camera at fullscreen zoom
 * will see an area that is 50 meters wide.
 */

struct Camera {
    float xm = 0;
    float ym = 0;
    float rot = 0;
    float zoom = 1;
    void SetFullscreen() {
        xm = 0;
        ym = 0;
        rot = 0;
        zoom = 1;
    }
};



#endif