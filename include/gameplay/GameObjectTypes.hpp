#ifndef GAME_OBJECT_TYPES
#define GAME_OBJECT_TYPES

#include <map>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>
#include <box2d/b2_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <framework/Resources.hpp>
#include <string>


class Game;
class GameObject;


namespace gm {

//List of all game object types
//Defined in the cpp file


enum GameObjectGroup {
    background,
    block,
    teekkari,
    effect,
    ground
};

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
    
    /*
    block_woodTri,
    block_metalTri,
    block_glassTri,
    block_plasticTri,
    block_rubberTri,
    block_concreteTri,*/

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

    pickup_ik,
    pickup_sik,
    pickup_tefy,
    pickup_tuta,
    pickup_tik,
    pickup_inkubio,
    pickup_kik,
    pickup_professor,


    //Cannon
    cannon,


    //Teekkaris
    teekkari_ik,
    teekkari_sik,
    teekkari_tefy,
    teekkari_tuta,
    teekkari_tik,
    teekkari_inkubio,
    teekkari_kik,
    teekkari_professor,


    //Fuksi (all fuksis are functionally identical, only different in appearance)
    fuksi,
    
    //Teekkari abilities (those that have spawnable components)
    ability_cow,
    ability_wrench,
    ability_integral,


    ground_obj

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




//Face and sound of a Teekkari or Fuksi
struct PersonFace {
    SpriteID face = SpriteID::teekkari_head1;
    SoundID grunt = SoundID::grunt1;
    SoundID die = SoundID::teekkari_death1;
    bool bType = false; //use tanned hands because the face is also tanned

    //just looks wrong if the face doesn't match the hands
};

//Body of a person
struct PersonBody {
    SpriteID torso = SpriteID::torso_blue;
    SpriteID arm = SpriteID::arm_blue;
    SpriteID leg = SpriteID::leg_blue;
    SpriteID armb = SpriteID::armb_blue;
    std::string guildName = "Teemu Teekkari";
};

// All properties needed to spawn a unique Teekkari or Fuksi.
// A Teekkari can be spawned with GameObjectType as well, it will have a randomly generated PersonData
struct PersonData {
    PersonFace face;
    PersonBody body;
    GameObjectType objType = GameObjectType::teekkari_ik;
};


/// List of teekkari heads to choose from
extern const std::vector<PersonFace> teekkariHeads;

/// List of teekkari heads with a different cap, because... well this is a really dumb way to accomplish this
extern const std::vector<PersonFace> teekkariHeads_s;

/// List of fuksi heads to choose from
extern const std::vector<PersonFace> fuksiHeads;

/// Lookup for teekkari bodies
extern const std::unordered_map<GameObjectType, PersonBody> teekkariBodies;

/// List of fuksi bodies
extern const std::vector<gm::PersonBody> fuksiBodies;

/// List of all teekkaris
extern const std::vector<gm::GameObjectType> teekkaris;

/// Return a random teekkari from a guild based on GameObjectType
PersonData RandomTeekkari(GameObjectType type);

/// Return a random fuksi
PersonData RandomFuksi();


// Block properties

enum BlockMaterial { wood, metal, glass, plastic, rubber, concrete };
enum BlockShape { block_1x1, block_2x1, block_2x2, block_ball, /*block_tri,*/ block_plank, block_thickplank };


// Allocate and create shared base shapes for BlockShapeData to use

std::shared_ptr<b2Shape> CreateShape1x1();
std::shared_ptr<b2Shape> CreateShape2x1();
std::shared_ptr<b2Shape> CreateShape2x2();
std::shared_ptr<b2Shape> CreateShapeBall();
//std::shared_ptr<b2Shape> CreateShapeTri();
std::shared_ptr<b2Shape> CreateShapePlank();
std::shared_ptr<b2Shape> CreateShapeThickPlank();


struct BlockMaterialData {
    BlockMaterial material;
    float density;
    float friction;
    float restitution;
    float hpMassRatio;
    float pointsPerMass;
    SoundID hitSound;
    SoundID breakSound;
};

struct BlockShapeData {
    BlockShape shape;
    float volume;
    float height;
    std::shared_ptr<b2Shape> b2shape;
    SpriteID halfHPSprite;
    SpriteID lowHPSprite;
};

struct BlockData {
    std::string blockName;
    SpriteID sprite;
    BlockMaterial material;
    BlockShape shape;
};

/// Ordered lookup for all types of blocks
extern const std::map<GameObjectType, BlockData> blockTypes;

/// Lookup for all block materials
extern const std::unordered_map<BlockMaterial, BlockMaterialData> materialProperties;

/// Lookup for all block shapes
extern const std::unordered_map<BlockShape, BlockShapeData> shapeProperties;


}

#endif
