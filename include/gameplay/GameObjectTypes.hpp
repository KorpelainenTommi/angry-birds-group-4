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

//List of all game object types
//Defined in the cpp file

/// A unique identifier defining the type of GameObject. All GameObjects should be spawnable without extra info
enum GameObjectType {

    terrain1x1, //Unmovable block of terrain
    background_tree,
    background_lamp_pole,
    background_bench,
    background_person,

    Catapult,

    block_wood1x1,
    block_metal1x1,
    block_glass1x1,



};

/// Used to save objects to file
struct GameObjectData {
    
    float x;
    float y;
    float rot;
    GameObjectType type;

};

const int objectGroupSize = 100000000;

/// Get the desired object group based on a GameObjectType
int GetObjectGroup(GameObjectType);

/// Get the object score if broken, or 0 if not applicable
int GetObjectScore(GameObjectType id);

/// Construct a child class based on GameObjectType
std::unique_ptr<GameObject> IDToObject(Game& game, GameObjectType type, float x, float y, float rot);





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
    const b2Shape& b2shape;
    b2Vec2 spriteOffset;
};

struct BlockData {
    SpriteID sprite;
    BlockMaterial material;
    BlockShape shape;
};

/// Lookup for all types of blocks
extern const std::unordered_map<GameObjectType, BlockData> blockTypes;

/// Lookup for all block materials
extern const std::unordered_map<BlockMaterial, BlockMaterialData> materialProperties;

/// Lookup for all block shapes
extern const std::unordered_map<BlockShape, BlockShapeData> shapeProperties;




}

#endif