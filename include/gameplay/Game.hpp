#ifndef GAME_HPP
#define GAME_HPP

#include <UpdateListener.hpp>


/** 
 * -Game owns and manages all GameObjects. It also needs to manage the box2d world, 
 * and probably count ticks (Update calls) for keeping track of time
 * 
 * -It needs to store Objects somewhere
 * 
 * -Objects might need to be accessed randomly, based on an identifier (for example, subtracting hp after resolving a collision)
 * 
 * -Objects might need to get added or removed randomly. This means that object index CANNOT be an identifier (so vector doesn't really work)
 * 
 * -Override Render to draw all objects in the correct order
 * 
 * -Override Update to update all objects. Also call Record on all Objects
 * 
 * -Game should have a Camera it can move
 * 
 * -Game probably needs a const reference of Screen (probably GameScreen) so it can do stuff like save files and exit out etc.
 * 
 */

class Game : public UpdateListener {

};


#endif