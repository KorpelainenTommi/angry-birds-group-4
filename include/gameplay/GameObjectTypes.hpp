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

/// @brief All types and properties of GameObjects are stored in this namespace
namespace gm {

//List of all game object types
//Defined in the cpp file

/// @brief Groups for gameobjects
enum GameObjectGroup {
    background,
    block,
    teekkari,
    effect,
    ground
};

/// @brief A unique identifier defining the type of GameObject. All GameObjects should be spawnable without extra info
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
    prop_beer,
    prop_beer_can,
    prop_chair,
    prop_table,

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
    
    //Physics particle
    phys_particle,
    professor_particle,

    //Animation
    anim_effect,

    //Teekkari abilities (those that have spawnable components)
    ability_cow,
    ability_wrench,
    ability_integral,



    ground_obj

};

/// @brief Struct to save objects to file
struct GameObjectData {
    
    float x;
    float y;
    float rot;
    GameObjectType type;

};

const int objectGroupSize = 100000000;

/// @brief Get the desired object group based on a GameObjectType
int GetObjectGroup(GameObjectType);

/// @brief Get the object score if broken, or 0 if not applicable
int GetObjectScore(GameObjectType type);

/// @brief Construct a child class based on GameObjectType
std::unique_ptr<GameObject> IDToObject(Game& game, GameObjectType type, float x, float y, float rot);




/// @brief Struct for face and sound of a Teekkari or Fuksi
struct PersonFace {
    SpriteID face = SpriteID::teekkari_head1;
    SoundID grunt = SoundID::grunt1;
    SoundID die = SoundID::teekkari_death1;
    bool bType = false; //use tanned hands because the face is also tanned

    //just looks wrong if the face doesn't match the hands
};

/// @brief Struct for body of a person
struct PersonBody {
    SpriteID torso = SpriteID::torso_blue;
    SpriteID arm = SpriteID::arm_blue;
    SpriteID leg = SpriteID::leg_blue;
    SpriteID armb = SpriteID::armb_blue;
    std::string guildName = "Teemu Teekkari";
};
/// @brief Struct for all data needed for a person
/** @details All properties needed to spawn a unique Teekkari or Fuksi.
*  A Teekkari can be spawned with GameObjectType as well, it will have a randomly generated PersonData
*/
struct PersonData {
    PersonFace face;
    PersonBody body;
    GameObjectType objType = GameObjectType::teekkari_ik;
};


/// @brief List of teekkari heads to choose from
extern const std::vector<PersonFace> teekkariHeads;

/// @brief List of teekkari heads with a different cap, because... well this is a really dumb way to accomplish this
extern const std::vector<PersonFace> teekkariHeads_s;

/// @brief List of fuksi heads to choose from
extern const std::vector<PersonFace> fuksiHeads;

/// @brief Lookup for teekkari bodies
extern const std::unordered_map<GameObjectType, PersonBody> teekkariBodies;

/// @brief List of fuksi bodies
extern const std::vector<gm::PersonBody> fuksiBodies;

/// @brief List of all teekkaris
extern const std::vector<gm::GameObjectType> teekkaris;

/// @brief Lookup from pickups to teekkaris
extern const std::unordered_map<gm::GameObjectType, gm::GameObjectType> pickupLookup;

/// @brief Return a random teekkari from a guild based on GameObjectType
PersonData RandomTeekkari(GameObjectType type);

/// @brief Return a random fuksi
PersonData RandomFuksi();



/// @brief Block material properties
enum BlockMaterial { wood, metal, glass, plastic, rubber, concrete };
/// @brief Block shape properties
enum BlockShape { block_1x1, block_2x1, block_2x2, block_ball, /*block_tri,*/ block_plank, block_thickplank, block_bottle, block_can };


// Allocate and create shared base shapes for BlockShapeData to use

std::shared_ptr<b2Shape> CreateShape1x1();
std::shared_ptr<b2Shape> CreateShape2x1();
std::shared_ptr<b2Shape> CreateShape2x2();
std::shared_ptr<b2Shape> CreateShapeBall();
//std::shared_ptr<b2Shape> CreateShapeTri();
std::shared_ptr<b2Shape> CreateShapePlank();
std::shared_ptr<b2Shape> CreateShapeThickPlank();
std::shared_ptr<b2Shape> CreateShapeBottle();
std::shared_ptr<b2Shape> CreateShapeCan();

/// @brief Struct for Block material data
struct BlockMaterialData {
    BlockMaterial material;
    float density;
    float friction;
    float restitution;
    float hpMassRatio;
    float pointsPerMass;
    SoundID hitSound;
    SoundID breakSound;
    SpriteID particle;
};

/// @brief Struct for block shape data
struct BlockShapeData {
    BlockShape shape;
    float volume;
    float height;
    std::shared_ptr<b2Shape> b2shape;
    SpriteID halfHPSprite;
    SpriteID lowHPSprite;
};

/// @brief Struct for block's data
struct BlockData {
    std::string blockName;
    SpriteID sprite;
    BlockMaterial material;
    BlockShape shape;
};

/// @brief Ordered lookup for all types of blocks
extern const std::map<GameObjectType, BlockData> blockTypes;

/// @brief Lookup for all block materials
extern const std::unordered_map<BlockMaterial, BlockMaterialData> materialProperties;

/// @brief Lookup for all block shapes
extern const std::unordered_map<BlockShape, BlockShapeData> shapeProperties;


}

#endif
