#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <UpdateListener.hpp>

#include <gameplay/Camera.hpp>
#include <gameplay/Level.hpp>
#include <gameplay/GameObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/AudioSystem.hpp>

#include <box2d/b2_world.h>
#include <box2d/b2_world_callbacks.h>
#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>

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
 *  int GetObjectGroup(GameObjectType) that returns an integer 0, 1, 2, 3 etc.
 *
 */
struct IDCounter {
    int backgrounds = 0;
    int blocks = 1 * gm::objectGroupSize;
    int teekkaris = 2 * gm::objectGroupSize;
    int effects = 3 * gm::objectGroupSize;
};

//Forward declaration
class GameScreen;


/// A Game encapsulates a single game session that starts when entering a GameScreen, and ends when exiting it
class Game : public UpdateListener, public b2ContactListener {
public:

    /// Construct a game but don't add any objects
    Game(GameScreen&);

    /// Construct a game, and load the provided level into it
    Game(GameScreen &s, Level level);           

    virtual ~Game();

    /// Render all objects in this game
    virtual void Render(const RenderSystem& r);

    /// Update all objects in this game
    virtual void Update();

    //===========================================================================
    //TODO:
    //In addition to implementin these methods call GameScreen::OnGameCompleted()
    //or GameScreen::OnGameLost when the game ends.
    //Call also GameScreen::OnScoreChange whenever the score changes.

    /// UI uses this to pause the physics simulation
    void Pause(){}; //TODO: implement this properly

    /// UI uses this to continue physics simulation after pausing it
    void Resume(){}; //TODO: implement this properly

    //===========================================================================

    void ChooseTeekkari(){}; // TODO: implement


    /// Create all objects from this level.
    void LoadLevel(Level level);


    /* Note about object creation:
     *
     * A class can construct a GameObject themselves, and add the pointer
     * with AddObject. AddObject then needs to simply assign the object a valid gameID
     * 
     * CreateObject should use gm::IDToObject to create the correct subclass of GameObject based on
     * GameObjectType. It should then add it just like with AddObject
     */


    /// Add an existing object and take ownership. Also assign the object a gameID
    int AddObject(std::unique_ptr<GameObject>);
    
    /// Create a new GameObject from the specified data
    int CreateObject(gm::GameObjectData data);

    /// Create a new GameObject with specified type, at this location and rotation
    int CreateObject(gm::GameObjectType type, float x = 0, float y = 0, float rot = 0);

    /// Destroy the object with specified id
    void DestroyObject(int id);

    /// Clear all objects
    void ClearObjects();

    /// Get a reference to the GameObject with this id
    GameObject& GetObject(int id);


    /// Get the time in ticks
    unsigned int GetTicks() const;

    /// Get the time in seconds
    float GetTime() const;

    /// Get a reference to an AudioSystem to play sounds
    AudioSystem& GetAudioSystem() const;

    /// Get a reference to a b2World to add rigidbodies
    b2World& GetB2World();

    /// Callback for Box2D contacts
    virtual void BeginContact(b2Contact* contact);


    /// Get a copy of current Camera
    const Camera& GetCamera() const;

    /// Reset the camera to a natural fullscreen view
    void ResetCamera();

    /// Set the camera position
    void SetCameraPos(float x, float y);

    /// Set the camera zoom
    void SetCameraZoom(float zoom);

    /// Set the camera rotation
    void SetCameraRot(float rot);

    virtual bool OnMouseMove(float xw, float yh);
    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);
    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);
    
protected:
    GameScreen& screen_;
    
    std::map<int,std::unique_ptr<GameObject>> objects_;
    Level level_;
    Camera camera_;

    /// List of teekkaris that can be spawned to the cannon
    std::vector<gm::TeekkariData> teekkarisLeft_;
    int chosenTeekkari_ = 0;


    int points_;
    unsigned int time_; //Game ticks since starting => number of update calls

    b2World world_;
    
    IDCounter IDCounter_;

};


#endif
