#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <gameplay/Physics.hpp>

/* A Camera has a position in world space, and a zoom.
 * zoom < 1 means zooming in, zoom > 1 means zooming out.
 * zoom = 1 is fullscreen.
 * 
 * As per the definition in gameplay/Physics.hpp, a camera at fullscreen zoom
 * will see an area that is 50 meters wide.
 */

struct Camera {
    ph::tfloat x = 0;
    ph::tfloat y = 0;
    ph::tfloat rot = 0;
    ph::tfloat zoom = 1;
    void Record() {
        x.Record();
        y.Record();
        rot.Record();
        zoom.Record();
    }
    void SetFullscreen() {
        x = 0;
        y = 0;
        rot = 0;
        zoom = 1;
        Record();
    }
};



#endif