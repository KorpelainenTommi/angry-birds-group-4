#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <gameplay.hpp>
#include <UpdateListener.hpp
#include <framework/Resources.hpp>

/** 
 * -This will probably need at least a position and a rotation and scale etc.
 * 
 * -A subclass of this could be PhysObject or something that adds velocity, mass, hp etc.
 * 
 * -Blocks could be a subclass of PhysObject with material or something
 * 
 *  etc. etc.
 * 
 * 
 * -Overriding Render should be pretty straightforward
 * 
 * -Use ph::tfloats for stuff so they can get interpolated by the renderer ;)
 * 
 * 
 * -Also note: in order to get saved to a level file, GameObjects probably need some kind of type or id enumeration
 * 
 * -Alternatively, they could get saved by just saving all related fields or something
 */

//TODO: this is an abstract base class for objects
class GameObject : public UpdateListener {
public:

    //TODO: These aren't implemented
    virtual ~GameObject() = default;

    //Call record on all tfloats
    virtual void Record();

    //Do game logics. Call Record at the start
    virtual void Update();

    //Draw this thing
    virtual void Render(const RenderSystem&);

private:

};


#endif