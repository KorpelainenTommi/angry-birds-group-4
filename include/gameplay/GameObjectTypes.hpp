#ifndef GAME_OBJECT_TYPES
#define GAME_OBJECT_TYPES

#include <memory>
#include <utility>
#include <unordered_map>
#include <box2d/b2_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <framework/Resources.hpp>


class Game;
class GameObject;


namespace gm {

//List of all game object types
//Defined in the cpp file

/// A unique identifier defining the type of GameObject. All GameObjects should be spawnable without extra info
enum GameObjectType {


    //Background objects
    terrain1x1, //Unmovable block of terrain
    background_tree1,
    background_tree2,
    background_lamp_pole,
    background_bench,
    background_person1,
    background_person2,
    background_person3,


    //Blocks
    block_wood1x1,
    block_metal1x1,
    block_glass1x1,
    block_plastic1x1,
    block_rubber1x1,        
    block_concrete1x1,
    
    block_wood2x1,
    block_metal2x1,
    block_glass2x1,
    block_plastic2x1,
    block_rubber2x1,
    block_concrete2x1,

    block_wood2x2,
    block_metal2x2,
    block_glass2x2,
    block_plastic2x2,
    block_rubber2x2,
    block_concrete2x2,

    ball_wood,
    ball_metal,
    ball_glass,
    ball_plastic,
    ball_rubber,
    ball_concrete,

    block_woodTri,
    block_metalTri,
    block_glassTri,
    block_plasticTri,
    block_rubberTri,
    block_concreteTri,

    plank_wood,
    plank_metal,
    plank_glass,
    plank_plastic,
    plank_rubber,
    plank_concrete,

    thickplank_wood,
    thickplank_metal,
    thickplank_glass,
    thickplank_plastic,   
    thickplank_rubber,
    thickplank_concrete,


    //Props
    prop_beer1,
    prop_beer2,
    prop_beer_can1,
    prop_beer_can2,

    prop_sofa2x1,
    prop_tnt,


    //Catapult
    catapult,


    //Teekkaris
    teekkari_teemu,
    teekkari_tefy,
    teekkari_tik,
    teekkari_inkubio,
    teekkari_tuta,
    teekkari_sik,
    teekkari_kik,
    teekkari_professor,


    //Fuksi (all fuksis are functionally identical, only different in appearance)
    fuksi,
    
    //Teekkari abilities (those that have spawnable components)
    ability_cow,
    ability_wrench,
    ability_integral,




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
int GetObjectScore(GameObjectType type);

/// Construct a child class based on GameObjectType
std::unique_ptr<GameObject> IDToObject(Game& game, GameObjectType type, float x, float y, float rot);





// Block properties

enum BlockMaterial { wood, metal, glass, plastic, rubber, concrete };
enum BlockShape { block_1x1, block_2x1, block_2x2, block_ball, block_tri, block_plank, block_thickplanck };


// Allocate and create shared base shapes for BlockShapeData to use

std::shared_ptr<b2Shape> CreateShape1x1();
std::shared_ptr<b2Shape> CreateShape2x1();
std::shared_ptr<b2Shape> CreateShape2x2();
std::shared_ptr<b2Shape> CreateShapeBall();
std::shared_ptr<b2Shape> CreateShapeTri();
std::shared_ptr<b2Shape> CreateShapePlank();
std::shared_ptr<b2Shape> CreateShapeThickPlank();


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
    float height;
    std::shared_ptr<b2Shape> b2shape;
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