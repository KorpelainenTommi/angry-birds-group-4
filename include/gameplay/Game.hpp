#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <UpdateListener.hpp>
#include <screens/GameScreen.hpp>

#include <gameplay/Camera.hpp>
#include <gameplay/Level.hpp>
#include <gameplay/GameObject.hpp>
#include <gameplay/GameObjectTypes.hpp>

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
 * IDs:
 *  Backgrounds 0-1000
 *  Blocks 1000-2000
 *  Birds 2000-3000
 *
 */

//Forward declaration
class GameScreen;

class Game : public UpdateListener {

    /// Construct an empty game
    Game(const GameScreen&);

    /// Construct a game, and load the provided level into it
    Game(const GameScreen &s, Level level);

    virtual ~Game() = default;

    virtual void Render(const RenderSystem& r);
    virtual void Update();
    int AddObject(std::unique_ptr<GameObject>);
    int CreateObject()
    void DestroyObject(int id);
    
private:
    std::map<int,std::unique_ptr<GameObject>> objects_;
    Level level_;
    const GameScreen& screen_;
    Camera c;
    int Points;
    
};


#endif
