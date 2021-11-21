#ifndef PHYSICS_HPP
#define PHYSICS_HPP

// A file for some physics constants and other stuff


////////////////////////////////////////////////////
/////     Definition of world coordinates     //////
////////////////////////////////////////////////////
/*
 * The UI is defined in percentage coordinates relative to screen size using custom floats called pfloats.
 * They were implemented by request from Ilari, based on the similar vw vh units in cascading style sheets
 * 
 * This means that a sprite of size 20 VW, 20 VH will be 20% of the screen width,
 * and 20% of the screen height. This means, that despite what the size might suggest,
 * it's shape isn't necessarily square. It is dependent on the screen aspect ratio
 *
 * For most gameplay purposes however, it is important that a circle is a circle and not an
 * oval despite what aspect ratio we are using. For this purpose, RenderSystem allows drawing
 * sprites using either relative coordinates, or absolute coordinates (meters)
 * These are represented by the aforementioned pfloat, and also a physics counterpart tfloat
 * 
 * A pfloat (percent float) has a value, and associated flag for either window width or window height
 * 
 * A tfloat (time float) has a previous and a current value (f0 and f1).
 * All active modifications to it (including tfloat = tfloat assignment) always modify the current value. 
 * It also has a method Record that stores the current value to its previous (f1 => f0)
 * This is used by RenderSystem for interpolating positions in between physics updates.
 * 
 * Both pfloats and tfloats can basically be used just like floats. In fact, absolutely nothing will break
 * whether they're used or not. Object movement might simply have some stuttering.
 * 
 * 
 * 
 * Back to screen independent units.
 * Since the game will also use a camera for panning, zooming etc. meters only have meaning
 * relative to the definition of the camera. As such let us define the world, and the camera like this:
 * 
 * A Camera at fullscreen zoom (zoom = 1F), will see an area that is 50 meters wide around the origin.
 * 
 * This is defined in the constant FullscreenPlayArea. 50 meters was chosen based on Box2D's documentation of units.
 * Based on this definition, we can define objects in meters, such as a Teekkari as 1.8 meters tall,
 * and a box as 2 meters tall. Their distance can be 5.89 meters, and Teekkari's position can be (-9.3, 15.05)
 * These definitions can be directly used in Box2D, and they can be directly rendered with RenderSystem.
 * 
 * So for example, a camera that is zoomed in by a factor of two (zoom = 0.5F) will see an area that is
 * 25 meters wide around it.
 * 
 * Since camera will always draw to the full area of our target window, the shape of the camera must always be the same
 * shape as our window or sprite shapes get distorted. This means that the height in meters that our camera sees depends on
 * the window aspect ratio. For example, with a 1:1 aspect ratio, a fullscreen camera will see an area that is 50m x 50m.
 * With aspect ratio 16:9, the same camera will see an area that is 50m x 28m.
 * 
 * 
 * The "size" of the world can be changed simply by changing the FullscreenPlayArea constant, without modifying the RenderSystem or
 * definitions of object sizes, gravity or anything else.
 * 
 * Alternatively, the constant could be removed altogether, and instead the camera zoom parameter given in meters.
 * 
 * 
 *
 */






namespace ph {


    const float FullscreenPlayArea = 50.0F;
    const float Gravity = 9.81F;
    const int velocityIters = 8;
    const int positionIters = 3;
    const float Timestep = 0.02F;


    /* A tfloat is simply a float that keeps track of its last value
     * Treat these like any normal float. In fact, you can freely assign floats to tfloats,
     * and tfloats to floats
     * 
     * This is used by the RenderSystem to be able to interpolate positions, sizes, anything.
     * Using tfloats simply gives a clean way to incorporate interpolation to the whole physics system,
     * without actually doing it IN the physics system. Call Record at the start of an Update
     */
    struct tfloat {
    public:
        tfloat() : f0(0), f1(0) {}
        tfloat(const float& f) : f0(f), f1(f) {}
        operator float() const { return f1; }
        tfloat& operator=(const float& f) { f1 = f; return *this; }
        tfloat& operator*=(const float& f) { f1 *= f; return *this; }
        tfloat& operator/=(const float& f) { f1 /= f; return *this; }
        tfloat& operator+=(const float& f) { f1 += f; return *this; }
        tfloat& operator-=(const float& f) { f1 -= f; return *this; }
        
        float Lerp(float t) const { return f0 + (f1 - f0) * t; }
        void Record() { f0 = f1; }
        float f0;
        float f1;
    };



}


#endif