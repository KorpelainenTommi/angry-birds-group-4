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
#include <SFML/System/Vector2.hpp>

#include <iostream>
/// @brief Game class that manages all gameobjects and implements majority of the gamelogic
/**
 * @details
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
/// @brief ID-counter for gameobjects
/// @details Each object will get a own unique id based on this counter
struct IDCounter {
    int backgrounds = 0;
    int blocks = 1 * gm::objectGroupSize;
    int teekkaris = 2 * gm::objectGroupSize;
    int effects = 3 * gm::objectGroupSize;
};

//Forward declaration
class GameScreen;


/// @brief A Game encapsulates a single game session that starts when entering a GameScreen, and ends when exiting it
class Game : public UpdateListener, public b2ContactListener {
public:

    /// @brief Construct a game but don't add any objects
    Game(GameScreen&);

    /// @brief Construct a game, and load the provided level into it
    Game(GameScreen &s, Level level);

    virtual ~Game();

    /// @brief Render all objects in this game
    virtual void Render(const RenderSystem& r);

    /// @brief Update all objects in this game
    virtual void Update();

    /// @brief UI uses this to pause the physics simulation
    void Pause();

    /// @brief UI uses this to continue physics simulation after pausing it
    virtual void Resume();
    /// @brief Restart the game
    void Restart();

    /// @brief Create all objects from this level.
    void LoadLevel(Level level);
    /// @brief Get maxscore
    int GetMaxScore();


    /// @brief Add an existing object and take ownership. Also assign the object a gameID
    /** @note
     *
     * A class can construct a GameObject themselves, and add the pointer
     * with AddObject. AddObject then needs to simply assign the object a valid gameID
     *
     * CreateObject should use gm::IDToObject to create the correct subclass of GameObject based on
     * GameObjectType. It should then add it just like with AddObject
     */
    int AddObject(std::unique_ptr<GameObject>);
    
    /// @brief Create a new GameObject from the specified data
    int CreateObject(gm::GameObjectData data);

    /// @brief Create a new GameObject with specified type, at this location and rotation
    int CreateObject(gm::GameObjectType type, float x = 0, float y = 0, float rot = 0);
    
    /// @brief Create a Teekkari from data
    int CreateTeekkari(gm::PersonData data, float x = 0, float y = 0, float rot = 0);

    /// @brief Destroy the object with specified id
    void DestroyObject(int id);

    /// @brief Clear all objects
    void ClearObjects();

    /// @brief Get a reference to the GameObject with this id
    GameObject& GetObject(int id);

    /// @brief Get a list of all objects
    std::vector<GameObject*> GetObjects();


    /// @brief Get the time in ticks
    unsigned int GetTicks() const;

    /// @brief Get the time in seconds
    float GetTime() const;

    /// @brief Get the time in secods for UI purposes
    float GetTimeForUI() const;

    /// @brief Is the game paused?
    bool IsPaused() const;

    /// @brief Returns true if cannon is disabled
    bool CannonDisabled() const;

    /// @brief Get a reference to an AudioSystem to play sounds
    AudioSystem& GetAudioSystem() const;

    /// @brief Get a reference to a b2World to add rigidbodies
    b2World& GetB2World();

    /// @brief Get gamescreen
    GameScreen& GetScreen();

    /// @brief Callback for Box2D contacts
    virtual void BeginContact(b2Contact* contact);


    /// @brief Get a copy of current Camera
    const Camera& GetCamera() const;

    /// @brief Reset the camera to a natural fullscreen view
    void ResetCamera();

    /// @brief Set the camera position
    void SetCameraPos(float x, float y);

    /// @brief Set the camera zoom
    void SetCameraZoom(float zoom);

    /// @brief Set the camera rotation
    void SetCameraRot(float rot);
    
    /// @brief End the level if level is at end
    void CheckLevelEnd();

    ///@brief  Increment current points
    void AddPoints(int p);

    /// @brief  Add a teekkari
    void AddTeekkari(gm::GameObjectType teekkari);

    /// @brief Pause time for everyone, except the professor !
    void ProfessorPause();

    /// @brief Time moves again
    void ProfessorResume();

    /// @brief UI calls this to report Game that the user has selected a projectile.
    void SelectProjectile(int index);

    /// @brief Pop out the selected teekkari. This will also update UI
    bool TakeProjectile(gm::PersonData& teekkari);

    /// @brief Receive mouse events from the user
    virtual bool OnMouseMove(float xw, float yh);
    /// @brief Receive mouse events from the user
    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);
    /// @brief Receive mouse events from the user
    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);
    /// @brief Receive mouse events from the user
    virtual bool OnMouseScroll(float delta, float xw, float yh);


    /// @brief Check the amount of fuksis in the level. Return true if there are none
    bool NoFuksis();

    /// @brief Check the amount of teekkaris left. Return true if there are none
    bool NoTeekkaris();

    /// @brief Checks if there are active teekkaris, or active abilities in the level
    bool NoActivity();

    /// @brief Check if the object is an editor. Return always false
    virtual bool IsEditor() const { return false; }
    
    //std::map<int,std::unique_ptr<GameObject>>& GetObjects();
    
protected:
    GameScreen& screen_;
    
    IDCounter IDCounter_;
    std::map<int,std::unique_ptr<GameObject>> objects_;
    Level level_;
    Camera camera_;

    /// List of teekkaris that can be spawned to the cannon
    std::vector<gm::PersonData> teekkarisLeft_;
    int chosenTeekkari_ = 0;

    //Mark this level for ending check. It is important that the level isn't ended in the middle of an Update, since
    //that could cause us to reference destructed objects
    bool checkForFinish_ = false;

    /// The professors ability can stop all other objects except himself
    bool professorPause_ = false;

    bool isPaused_ = false;
    int points_;
    unsigned int time_ = 0; //Game ticks since starting => number of update calls

    int levelMaxScore_ = 0;

    b2World world_;
    
    /// Notify UI of the changes to projectiles
    void UpdateProjectileList();


    //Variables for panning the camera
    bool movingCamera_ = false;
    ph::tfloat cameraGrabX_;
    ph::tfloat cameraGrabY_;
    
    /// Set the camera inside world's bounds
    void CheckCameraBounds();

};


#endif
