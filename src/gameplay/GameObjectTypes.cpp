#include <gameplay/GameObjectTypes.hpp>
#include <framework/RandomGen.hpp>
#include <gameplay/Block.hpp>
#include <gameplay/Cannon.hpp>
#include <gameplay/Ground.hpp>
#include <gameplay/Teekkari.hpp>
#include <gameplay/Fuksi.hpp>
#include <math.h>



const std::vector<gm::PersonFace> gm::teekkariHeads = { 
    {SpriteID::teekkari_head1,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head2,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head3,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head4,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head5,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head6,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head7,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head8,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head9,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head10, SoundID::grunt1, SoundID::teekkari_death1, false}
};

const std::vector<gm::PersonFace> gm::teekkariHeads_s = {
    {SpriteID::teekkari_head1s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head2s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head3s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head4s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head5s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head6s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head7s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head8s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head9s,  SoundID::grunt1, SoundID::teekkari_death1, false},
    {SpriteID::teekkari_head10s, SoundID::grunt1, SoundID::teekkari_death1, false}
};

const std::vector<gm::PersonFace> gm::fuksiHeads = {
    {SpriteID::fuksi_head1, SoundID::fuksi_cry1, SoundID::fuksi_death1, false},
    {SpriteID::fuksi_head2, SoundID::fuksi_cry1, SoundID::fuksi_death1, false},
    {SpriteID::fuksi_head3, SoundID::fuksi_cry1, SoundID::fuksi_death1, false},
    {SpriteID::fuksi_head4, SoundID::fuksi_cry1, SoundID::fuksi_death1, false},
    {SpriteID::fuksi_head5, SoundID::fuksi_cry1, SoundID::fuksi_death1, false},
    {SpriteID::fuksi_head6, SoundID::fuksi_cry1, SoundID::fuksi_death1, false},
    {SpriteID::fuksi_head7, SoundID::fuksi_cry1, SoundID::fuksi_death1, false},
    {SpriteID::fuksi_head8, SoundID::fuksi_cry1, SoundID::fuksi_death1, false}
};

const std::unordered_map<gm::GameObjectType, gm::PersonBody> gm::teekkariBodies = {
    { gm::GameObjectType::teekkari_ik, { SpriteID::torso_blue, SpriteID::arm_blue, SpriteID::leg_blue, SpriteID::armb_blue, "IK Teekkari" }},
    { gm::GameObjectType::teekkari_sik, { SpriteID::torso_white, SpriteID::arm_white, SpriteID::leg_white, SpriteID::armb_white, "SIK Teekkari" }},
    { gm::GameObjectType::teekkari_tik, { SpriteID::torso_black, SpriteID::arm_black, SpriteID::leg_black, SpriteID::armb_black, "TIK Teekkari" }},
    { gm::GameObjectType::teekkari_kik, { SpriteID::torso_pink, SpriteID::arm_pink, SpriteID::leg_pink, SpriteID::armb_pink, "KIK Teekkari" }},
    { gm::GameObjectType::teekkari_tefy, { SpriteID::torso_lwhite, SpriteID::arm_lwhite, SpriteID::leg_lwhite, SpriteID::armb_lwhite, "TEFY Teekkari" }},
    { gm::GameObjectType::teekkari_tuta, { SpriteID::torso_rainbow, SpriteID::arm_rainbow, SpriteID::leg_rainbow, SpriteID::armb_rainbow, "Prodeko Teekkari" }},
    { gm::GameObjectType::teekkari_inkubio, { SpriteID::torso_brown, SpriteID::arm_brown, SpriteID::leg_brown, SpriteID::armb_brown, "Inkubio Teekkari" }},
    { gm::GameObjectType::teekkari_professor, { SpriteID::professor_torso, SpriteID::professor_arm, SpriteID::professor_leg, SpriteID::professor_arm, "The Professor" }}
};

const std::vector<gm::PersonBody> gm::fuksiBodies = {
    { SpriteID::fuksi_torso_blue, SpriteID::fuksi_arm_blue, SpriteID::fuksi_leg_blue, SpriteID::fuksi_armb_blue },
    { SpriteID::fuksi_torso_white, SpriteID::fuksi_arm_white, SpriteID::fuksi_leg_white, SpriteID::fuksi_armb_white },
    { SpriteID::fuksi_torso_black, SpriteID::fuksi_arm_black, SpriteID::fuksi_leg_black, SpriteID::fuksi_armb_black },
    { SpriteID::fuksi_torso_pink, SpriteID::fuksi_arm_pink, SpriteID::fuksi_leg_pink, SpriteID::fuksi_armb_pink },
    { SpriteID::fuksi_torso_lwhite, SpriteID::fuksi_arm_lwhite, SpriteID::fuksi_leg_lwhite, SpriteID::fuksi_armb_lwhite },
    { SpriteID::fuksi_torso_rainbow, SpriteID::fuksi_arm_rainbow, SpriteID::fuksi_leg_rainbow, SpriteID::fuksi_armb_rainbow },
    { SpriteID::fuksi_torso_brown, SpriteID::fuksi_arm_brown, SpriteID::fuksi_leg_brown, SpriteID::fuksi_armb_brown }
};

const std::vector<gm::GameObjectType> teekkaris = {
    gm::GameObjectType::teekkari_ik,
    gm::GameObjectType::teekkari_sik,
    gm::GameObjectType::teekkari_tefy,
    gm::GameObjectType::teekkari_tuta,
    gm::GameObjectType::teekkari_tik,
    gm::GameObjectType::teekkari_inkubio,
    gm::GameObjectType::teekkari_kik,
    gm::GameObjectType::teekkari_professor
};

gm::PersonData gm::RandomTeekkari(gm::GameObjectType type) {

    gm::PersonFace face;
    gm::PersonBody body = teekkariBodies.at(type);
    if(type == gm::GameObjectType::teekkari_professor)
        face = {SpriteID::professor_head, SoundID::grunt1, SoundID::teekkari_death1, false};
    else if(type == gm::GameObjectType::teekkari_sik)
        face = gm::teekkariHeads_s.at(rng::RandomInt(0, gm::teekkariHeads_s.size()-1));
    else face = gm::teekkariHeads.at(rng::RandomInt(0, gm::teekkariHeads.size()-1));
    return {face, body, type};

}


gm::PersonData gm::RandomFuksi() {
    gm::PersonFace face = fuksiHeads.at(rng::RandomInt(0, gm::fuksiHeads.size()-1));
    gm::PersonBody body = fuksiBodies.at(rng::RandomInt(0, gm::fuksiBodies.size()-1));
    return {face, body, gm::GameObjectType::fuksi};
}




const std::map<gm::GameObjectType, gm::BlockData> gm::blockTypes = {

    //1x1
    { gm::GameObjectType::block_wood1x1,  { "wood 1x1", SpriteID::wood_block1x1, gm::BlockMaterial::wood, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_metal1x1, { "metal 1x1", SpriteID::metal_block1x1, gm::BlockMaterial::metal, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_glass1x1, { "glass 1x1", SpriteID::glass_block1x1, gm::BlockMaterial::glass, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_plastic1x1, { "plastic 1x1", SpriteID::plastic_block1x1, gm::BlockMaterial::plastic, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_rubber1x1, { "rubber 1x1", SpriteID::rubber_block1x1, gm::BlockMaterial::rubber, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_concrete1x1, { "concrete 1x1", SpriteID::concrete_block1x1, gm::BlockMaterial::concrete, gm::BlockShape::block_1x1 } },

    //2x1
    { gm::GameObjectType::block_wood2x1, { "wood 2x1", SpriteID::wood_block2x1, gm::BlockMaterial::wood, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_metal2x1, { "metal 2x1", SpriteID::metal_block2x1, gm::BlockMaterial::metal, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_glass2x1, { "glass 2x1", SpriteID::glass_block2x1, gm::BlockMaterial::glass, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_plastic2x1, { "plastic 2x1",  SpriteID::plastic_block2x1, gm::BlockMaterial::plastic, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_rubber2x1, { "rubber 2x1", SpriteID::rubber_block2x1, gm::BlockMaterial::rubber, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_concrete2x1, { "concrete 2x1", SpriteID::concrete_block2x1, gm::BlockMaterial::concrete, gm::BlockShape::block_2x1 } },

    //2x2
    { gm::GameObjectType::block_wood2x2, { "wood 2x2", SpriteID::wood_block2x2, gm::BlockMaterial::wood, gm::BlockShape::block_2x2 } },
    { gm::GameObjectType::block_metal2x2, { "metal 2x2", SpriteID::metal_block2x2, gm::BlockMaterial::metal, gm::BlockShape::block_2x2 } },
    { gm::GameObjectType::block_glass2x2, { "glass 2x2", SpriteID::glass_block2x2, gm::BlockMaterial::glass, gm::BlockShape::block_2x2 } },
    { gm::GameObjectType::block_plastic2x2, { "plastic 2x2", SpriteID::plastic_block2x2, gm::BlockMaterial::plastic, gm::BlockShape::block_2x2 } },
    { gm::GameObjectType::block_rubber2x2, { "rubber 2x2", SpriteID::rubber_block2x2, gm::BlockMaterial::rubber, gm::BlockShape::block_2x2 } },
    { gm::GameObjectType::block_concrete2x2, { "concrete 2x2", SpriteID::concrete_block2x2, gm::BlockMaterial::concrete, gm::BlockShape::block_2x2 } },

    //Ball
    { gm::GameObjectType::ball_wood, { "wooden ball", SpriteID::wood_ball, gm::BlockMaterial::wood, gm::BlockShape::block_ball } },
    { gm::GameObjectType::ball_metal, { "metal ball", SpriteID::metal_ball, gm::BlockMaterial::metal, gm::BlockShape::block_ball } },
    { gm::GameObjectType::ball_glass, { "glass ball", SpriteID::glass_ball, gm::BlockMaterial::glass, gm::BlockShape::block_ball } },
    { gm::GameObjectType::ball_plastic, { "plastic ball", SpriteID::plastic_ball, gm::BlockMaterial::plastic, gm::BlockShape::block_ball } },
    { gm::GameObjectType::ball_rubber, { "rubber ball", SpriteID::rubber_ball, gm::BlockMaterial::rubber, gm::BlockShape::block_ball } },
    { gm::GameObjectType::ball_concrete, { "concrete ball", SpriteID::concrete_ball, gm::BlockMaterial::concrete, gm::BlockShape::block_ball } },

    //Tri
    /*
    { gm::GameObjectType::block_woodTri, { SpriteID::wood_blockTri, gm::BlockMaterial::wood, gm::BlockShape::block_tri } },
    { gm::GameObjectType::block_metalTri, { SpriteID::metal_blockTri, gm::BlockMaterial::metal, gm::BlockShape::block_tri } },
    { gm::GameObjectType::block_glassTri, { SpriteID::glass_blockTri, gm::BlockMaterial::glass, gm::BlockShape::block_tri } },
    { gm::GameObjectType::block_plasticTri, { SpriteID::plastic_blockTri, gm::BlockMaterial::plastic, gm::BlockShape::block_tri } },
    { gm::GameObjectType::block_rubberTri, { SpriteID::rubber_blockTri, gm::BlockMaterial::rubber, gm::BlockShape::block_tri } },
    { gm::GameObjectType::block_concreteTri, { SpriteID::concrete_blockTri, gm::BlockMaterial::concrete, gm::BlockShape::block_tri } },*/

    //Plank
    { gm::GameObjectType::plank_wood, { "wooden plank", SpriteID::wood_plank, gm::BlockMaterial::wood, gm::BlockShape::block_plank } },
    { gm::GameObjectType::plank_metal, { "metal plank", SpriteID::metal_plank, gm::BlockMaterial::metal, gm::BlockShape::block_plank } },
    { gm::GameObjectType::plank_glass, { "glass plank", SpriteID::glass_plank, gm::BlockMaterial::glass, gm::BlockShape::block_plank } },
    { gm::GameObjectType::plank_plastic, { "plastic plank", SpriteID::plastic_plank, gm::BlockMaterial::plastic, gm::BlockShape::block_plank } },
    { gm::GameObjectType::plank_rubber, { "rubber plank", SpriteID::rubber_plank, gm::BlockMaterial::rubber, gm::BlockShape::block_plank } },
    { gm::GameObjectType::plank_concrete, { "concrete plank", SpriteID::concrete_plank, gm::BlockMaterial::concrete, gm::BlockShape::block_plank } },

    //ThickPlank
    { gm::GameObjectType::thickplank_wood, { "large wooden plank", SpriteID::wood_thickplank, gm::BlockMaterial::wood, gm::BlockShape::block_thickplank } },
    { gm::GameObjectType::thickplank_metal, { "large metal plank", SpriteID::metal_thickplank, gm::BlockMaterial::metal, gm::BlockShape::block_thickplank } },
    { gm::GameObjectType::thickplank_glass, { "large glass plank", SpriteID::glass_thickplank, gm::BlockMaterial::glass, gm::BlockShape::block_thickplank } },
    { gm::GameObjectType::thickplank_plastic, { "large plastic plank", SpriteID::plastic_thickplank, gm::BlockMaterial::plastic, gm::BlockShape::block_thickplank } },
    { gm::GameObjectType::thickplank_rubber, { "large rubber plank", SpriteID::rubber_thickplank, gm::BlockMaterial::rubber, gm::BlockShape::block_thickplank } },
    { gm::GameObjectType::thickplank_concrete, { "large concrete plank", SpriteID::concrete_thickplank, gm::BlockMaterial::concrete, gm::BlockShape::block_thickplank } }

};


// Materials

const std::unordered_map<gm::BlockMaterial, gm::BlockMaterialData> gm::materialProperties = {
    { gm::BlockMaterial::wood, { gm::BlockMaterial::wood, 200, 0.3F, 0, 1, 1, SoundID::wood_hit, SoundID::wood_crack }},
    { gm::BlockMaterial::metal, { gm::BlockMaterial::metal, 900, 0.2F, 0, 5.0F, 0.1F, SoundID::metal_hit, SoundID::metal_crack }},
    { gm::BlockMaterial::glass, { gm::BlockMaterial::glass, 400, 0.15F, 0.12F, 0.25F, 2.5F, SoundID::glass_hit, SoundID::glass_crack }},
    { gm::BlockMaterial::plastic, { gm::BlockMaterial::plastic, 150, 0.23F, 0.18F, 2, 2, SoundID::plastic_hit, SoundID::plastic_crack }},
    { gm::BlockMaterial::rubber, { gm::BlockMaterial::rubber, 180, 0.18F, 0.6F, 2, 4, SoundID::rubber_hit, SoundID::rubber_crack }},
    { gm::BlockMaterial::concrete, { gm::BlockMaterial::concrete, 1000, 0.88F, 0, 0.4F, 0.4F, SoundID::concrete_hit, SoundID::concrete_crack }}
};


//Shapes

std::shared_ptr<b2Shape> gm::CreateShape1x1() { b2PolygonShape shape; shape.SetAsBox(0.5F, 0.5F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShape2x1() { b2PolygonShape shape; shape.SetAsBox(1.0F, 0.5F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShape2x2() { b2PolygonShape shape; shape.SetAsBox(1.0F, 1.0F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShapeBall() { b2CircleShape shape; shape.m_radius = 0.5F; return std::make_shared<b2CircleShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShapePlank() { b2PolygonShape shape; shape.SetAsBox(1.5F, 0.09375F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShapeThickPlank() { b2PolygonShape shape; shape.SetAsBox(3.0F, 0.1875F); return std::make_shared<b2PolygonShape>(shape); }

/*std::shared_ptr<b2Shape> gm::CreateShapeTri() {
    b2PolygonShape shape;
    b2Vec2 v[3] = {{0.5F, -0.3F},{0, 0.58F},{-0.5F, -0.3F}};
    shape.Set(v, 3); return std::make_shared<b2PolygonShape>(shape);
}*/

const std::unordered_map<gm::BlockShape, gm::BlockShapeData> gm::shapeProperties = {
    { gm::BlockShape::block_1x1, { gm::BlockShape::block_1x1, 1, 1, gm::CreateShape1x1(), SpriteID::crack1x1, SpriteID::crack1x1_b}},
    { gm::BlockShape::block_2x1, { gm::BlockShape::block_2x1, 2, 1, gm::CreateShape2x1(), SpriteID::crack2x1, SpriteID::crack2x1_b}},
    { gm::BlockShape::block_2x2, { gm::BlockShape::block_2x2, 4, 2, gm::CreateShape2x2(), SpriteID::crack2x2, SpriteID::crack2x2_b}},
    { gm::BlockShape::block_ball, { gm::BlockShape::block_ball, 3.1415926F, 1, gm::CreateShapeBall(), SpriteID::crack_ball, SpriteID::crack_ball_b}},
    /*{ gm::BlockShape::block_tri, { gm::BlockShape::block_tri, 0.435F, 0.87F, gm::CreateShapeTri()}},*/
    { gm::BlockShape::block_plank, { gm::BlockShape::block_plank, 0.5625F, 0.1875F, gm::CreateShapePlank(), SpriteID::crack_plank, SpriteID::crack_plank_b}},
    { gm::BlockShape::block_thickplank, { gm::BlockShape::block_thickplank, 2.25F, 0.375F, gm::CreateShapeThickPlank(), SpriteID::crack_thickplank, SpriteID::crack_thickplank_b}}
};



int gm::GetObjectGroup(gm::GameObjectType type) {
    if(type <= gm::GameObjectType::background_person3) return gm::GameObjectGroup::background;
    else if(type < gm::GameObjectType::cannon) return gm::GameObjectGroup::block;
    else if(type <= gm::GameObjectType::fuksi) return gm::GameObjectGroup::teekkari;
    else if(type <= gm::GameObjectType::ability_integral) return gm::GameObjectGroup::effect;
    else return gm::GameObjectGroup::ground;
}

int gm::GetObjectScore(gm::GameObjectType type) {
    if(type >= gm::GameObjectType::block_wood1x1 && type <= gm::GameObjectType::thickplank_concrete) {
        gm::BlockData bd = blockTypes.at(type);
        gm::BlockShapeData shapeData = shapeProperties.at(bd.shape);
        gm::BlockMaterialData materialData = materialProperties.at(bd.material);
        return (int)roundf(shapeData.volume * materialData.density * materialData.pointsPerMass);
    }
    else if(type == gm::GameObjectType::fuksi) return ph::fuksiScore;
    else return 0;
}

std::unique_ptr<GameObject> gm::IDToObject(Game& game, gm::GameObjectType type, float x, float y, float rot) {

    // TODO: make this cleaner, easier to do once all basic types are added

    // Block
    if(type >= gm::GameObjectType::block_wood1x1 && type <= gm::GameObjectType::thickplank_concrete) return std::make_unique<Block>(game, type, x, y, rot);

    // Teekkaris (add all these separately when they get their own classes and super powers)
    if(type >= gm::GameObjectType::teekkari_ik && type <= gm::GameObjectType::teekkari_professor) return std::make_unique<Teekkari>(game, type, x, y, rot);
    if(type == gm::GameObjectType::fuksi) return std::make_unique<Fuksi>(game, x, y, rot);


    if(type == gm::GameObjectType::cannon) return std::make_unique<Cannon>(game, type, x, y, rot);
    if(type == gm::GameObjectType::ground_obj) return std::make_unique<Ground>(game);
    else return std::unique_ptr<GameObject>(nullptr);

}
