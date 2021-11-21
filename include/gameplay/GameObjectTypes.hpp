#ifndef GAME_OBJECT_TYPES
#define GAME_OBJECT_TYPES

#include <memory>
#include <utility>
#include <unordered_map>
#include <box2d/b2_shape.h>
#include <framework/Resources.hpp>


class Game;
class GameObject;

namespace gm {

//List of all game object ids
//Defined in the cpp file
enum GameObjectID;

/// Used to save objects to file
struct GameObjectData {
    
    float x;
    float y;
    float rot;
    GameObjectID id;

};

const int objectGroupSize = 100000000;

/// Get the desired object group based on a GameObjectID
int GetObjectGroup(GameObjectID);

/// Get the object score if broken, or 0 if not applicable
int GetObjectScore(GameObjectID id);

/// Construct a child class based on GameObjectID
std::unique_ptr<GameObject> IDToObject(Game& game, GameObjectID id, float x, float y, float rot);

/// Is this object affected by physics (b2World.step)
bool IsPhysicsObject(GameObjectID id);





// Block properties

enum BlockMaterial;
enum BlockShape;

struct BlockMaterialData {
    BlockMaterial material;
    float density;
    float friction;
    float restitution;
    float hpMassRatio;
    float pointsPerMass;
};

struct BlockShapeData {
    BlockShape shape;
    float volume;
    b2Shape& b2shape;
    b2Vec2 spriteOffset;
};

struct BlockData {
    SpriteID sprite;
    BlockMaterial material;
    BlockShape shape;
};

extern const std::unordered_map<GameObjectID, BlockData> blockTypes;
extern const std::unordered_map<BlockMaterial, BlockMaterialData> materialProperties;
extern const std::unordered_map<BlockShape, BlockShapeData> shapeProperties;




}

#endif