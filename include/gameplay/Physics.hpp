#ifndef PHYSICS_HPP
#define PHYSICS_HPP

// A file for some physics constants and other stuff


////////////////////////////////////////////////////
/////     Definition of world coordinates     //////
////////////////////////////////////////////////////
/*
 * The UI is defined in percentage coordinates relative to screen size.
 * This means that a sprite of size 0.2F, 0.2F will be 20% of the screen width,
 * and 20% of the screen height. This means, that despite what the size would suggest,
 * it's shape isn't necessarily square. It is dependent on the screen aspect ratio
 *
 * For most gameplay purposes however, it is important that a circle is a circle and not an
 * oval despite what aspect ratio we are using. For this purpose, RenderSystem allows drawing
 * sprites using meters as units. To distinguish these two, parameters should be named either
 * xw => x relative to screen width
 * xh => x relative to screen height
 * xm => x given in meters
 * wm => width in meters
 * hh => height relative to screen height
 * etc.
 * 
 * 
 * However, since the game will also use a camera for panning, zooming etc. meters only have meaning
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
 * 
 *
 */


namespace ph {


    constexpr float Gravity = 9.81F;
    constexpr float FullscreenPlayArea = 50.0F;


    //Other stuff here

}


#endif