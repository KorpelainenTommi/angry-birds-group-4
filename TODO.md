# This is a list of some TODO things in various files.

Pick something from this list and implement it:

1. LoadLevel and SaveLevel from FileManager are not implemented. Check the Level struct for reference

2. GameIDs are assigned to newly created objects in order (1, 2, 3, 4...) Instead they should be allocated from groups (ids 0-10000, 10000-20000 etc.) Check `Game.hpp` and GameObjectTypes.hpp, there will be a method called `gm::GetObjectGroup()` to return a group based on `GameObjectType`.

3. Camera position/panning should probably be restricted so that the user cannot move the camera too far away to the left or right. The playable area is currently limited to 50 meters based on  `ph::fullcreenPlayArea`. It would make sense for it to be limited in a way that the playarea is always visible

4. Derive from GameObject to create child class Effect. These don't have any Physics, and are for playing animations and sound effects. An Effect playing some animation should store the fps of the animation (e.g 24 fps) and the start time with `Game::GetTime()`. In the `Render()` method, it is possible to calculate the current frame of the animation by comparing `Game::GetTime()` to the stored starting time. 

RenderSystem will have a method similar to `RenderSprite()` called `RenderAnimation()` that accepts an `AnimationID`, an int frame (and position, rotation etc. probably)

5. The catapult for the game has not been started. However, it would make most sense for it to be a PhysObject that simply has a B2Body attached to
its `mainBody_` via a joint. After this, Physics functions like Impulse, Force etc. can be overriden to add forces and torque to the catapult
lever.

6. PhysObject method `Explosion` has not been implemented. It should calculate an Impulse that is away from the given center of explosion, and a magnitude that decays with distance. This method will be used for implementing tnt and metal blocks exploding when hit with lightning.


7. Level's score calculation hasn't been implemented. The simplest implementation would be to sum up the scores for all gameobjects. A score can
be retrieved based on GameObjectType with `gm::GetObjectScore(GameObjectType type)`

8. Teekkaris and Fuksis haven't been implemented. It would make sense to store usable Teekkaris just in a vector with GameObjectTypes. A Teekkari can then be spawned on the catapult with `Game::CreateObject()`
