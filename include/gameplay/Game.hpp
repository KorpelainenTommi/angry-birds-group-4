#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <UpdateListener.hpp>

#include <gameplay/Camera.hpp>
#include <gameplay/Level.hpp>
#include <gameplay/GameObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/AudioSystem.hpp>

//#include "b2_world.h"

/** 
 * Game owns and manages all GameObjects. It also manages the box2d world, 
 * and counts ticks (Update calls) for keeping track of time.
 *
 * GameObjects are kept in a map as std::unique_ptr, and ordered based on their rendering order.
 * 
 * When creating new objects, their id should be assigned from one of the following groups:
 * 
 * IDs:
 *  Backgrounds          0      - 100 000 000
 *  Blocks          100 000 000 - 200 000 000
 *  Teekkari        200 000 000 - 300 000 000
 *  Effects         300 000 000 - 400 000 000
 *  ..              
 * 
 *  the namespace gm defines a constant called objectGroupSize, and a method 
 *  int GetObjectGroup(GameObjectID) that returns an integer 0, 1, 2, 3 etc.
 *
 */

//Forward declaration
class GameScreen;

class Game : public UpdateListener {
public:
    /// Construct an empty game
    Game(GameScreen&);

    /// Construct a game, and load the provided level into it
    Game(GameScreen &s, Level level);

    virtual ~Game() = default;

    virtual void Render(const RenderSystem& r);
    virtual void Update();


    /// Create all objects from this level.
    void LoadLevel(Level level);


    /* Note about object creation:
     *
     * A class can construct a GameObject themselves, and add the pointer
     * with AddObject. This method then needs to simply assign the object a valid gameID
     * 
     * 
     */


    /// Add an existing object and take ownership. Also assign the object a gameID
    int AddObject(std::unique_ptr<GameObject>);
    
    /// Create a new GameObject from the specified data
    int CreateObject(gm::GameObjectData data);

    /// Create a new GameObject with specified type, at this location and rotation
    int CreateObject(gm::GameObjectID id, float x = 0, float y = 0, float rot = 0);

    /// Destroy object with specified id
    void DestroyObject(int id);

    /// Clear all objects
    void ClearObjects();

    /// Get a reference to the GameObject with this gameID. Returns true if it exists, false otherwise
    bool GetObject(int id, GameObject&);


    /// Get time in ticks
    unsigned int GetTicks() const;

    /// Get time in seconds
    float GetTime() const;

    AudioSystem& GetAudioSystem() const; //Through screen => app => audiosystem
    //b2World& GetB2World() const;


    Camera GetCamera() const;
    void ResetCamera();
    void SetCameraPos(float x, float y);
    void SetCameraZoom(float zoom);
    void SetCameraRot(float rot);


    
protected:
    GameScreen& screen_;
    
    std::map<int,std::unique_ptr<GameObject>> objects_;
    Level level_;
    Camera camera_;

    int points_;
    unsigned int time_; //Game ticks since starting => number of update calls

    //b2World world_;
    
};


#endif
