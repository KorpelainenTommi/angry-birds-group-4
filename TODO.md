# This is a list of some TODO things in various files.

Pick something from this list and implement it:

1. Derive from GameObject to create child class Effect. These don't have any Physics, and are for playing animations and sound effects. An Effect playing some animation should store the fps of the animation (e.g 24 fps) and the start time with `Game::GetTime()`. In the `Render()` method, it is possible to calculate the current frame of the animation by comparing `Game::GetTime()` to the stored starting time. 

RenderSystem will have a method similar to `RenderSprite()` called `RenderAnimation()` that accepts an `AnimationID`, an int frame (and position, rotation etc. probably)

2. PhysObject method `Explosion` has not been implemented. It should calculate an Impulse that is away from the given center of explosion, and a magnitude that decays with distance. This method will be used for implementing tnt and metal blocks exploding when hit with lightning.

3. Implement Editor::SetSelectedElement(), Editor::AddProjectile(), and Editor::RemoveProjectile().