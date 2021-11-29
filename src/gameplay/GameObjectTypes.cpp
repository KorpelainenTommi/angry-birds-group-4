#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/Block.hpp>


const std::unordered_map<gm::GameObjectType, gm::BlockData> gm::blockTypes = {

    //1x1
    { gm::GameObjectType::block_wood1x1, { SpriteID::wood_block1x1, gm::BlockMaterial::wood, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_metal1x1, { SpriteID::metal_block1x1, gm::BlockMaterial::metal, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_glass1x1, { SpriteID::glass_block1x1, gm::BlockMaterial::glass, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_plastic1x1, { SpriteID::plastic_block1x1, gm::BlockMaterial::plastic, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_rubber1x1, { SpriteID::rubber_block1x1, gm::BlockMaterial::rubber, gm::BlockShape::block_1x1 } },
    { gm::GameObjectType::block_concrete1x1, { SpriteID::concrete_block1x1, gm::BlockMaterial::concrete, gm::BlockShape::block_1x1 } },

    //2x1
    { gm::GameObjectType::block_wood2x1, { SpriteID::wood_block2x1, gm::BlockMaterial::wood, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_metal2x1, { SpriteID::metal_block2x1, gm::BlockMaterial::metal, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_glass2x1, { SpriteID::glass_block2x1, gm::BlockMaterial::glass, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_plastic2x1, { SpriteID::plastic_block2x1, gm::BlockMaterial::plastic, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_rubber2x1, { SpriteID::rubber_block2x1, gm::BlockMaterial::rubber, gm::BlockShape::block_2x1 } },
    { gm::GameObjectType::block_concrete2x1, { SpriteID::concrete_block2x1, gm::BlockMaterial::concrete, gm::BlockShape::block_2x1 } }

    //More to come

};


// Materials

const std::unordered_map<gm::BlockMaterial, gm::BlockMaterialData> gm::materialProperties = {
    { gm::BlockMaterial::wood, { gm::BlockMaterial::wood, 200, 0.3F, 0, 1, 1 }},
    { gm::BlockMaterial::metal, { gm::BlockMaterial::metal, 900, 0.2F, 0, 5.0F, 0.1F }},
    { gm::BlockMaterial::glass, { gm::BlockMaterial::glass, 400, 0.15F, 0.12F, 0.25F, 2.5F }},
    { gm::BlockMaterial::plastic, { gm::BlockMaterial::plastic, 150, 0.23F, 0.18F, 2, 2 }},
    { gm::BlockMaterial::rubber, { gm::BlockMaterial::rubber, 180, 0.18F, 0.6F, 2, 4 }},
    { gm::BlockMaterial::concrete, { gm::BlockMaterial::concrete, 1000, 0.88F, 0, 0.4F, 0.4F }}
};


//Shapes

std::shared_ptr<b2Shape> gm::CreateShape1x1() { b2PolygonShape shape; shape.SetAsBox(0.5F, 0.5F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShape2x1() { b2PolygonShape shape; shape.SetAsBox(1.0F, 0.5F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShape2x2() { b2PolygonShape shape; shape.SetAsBox(1.0F, 1.0F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShapeBall() { b2CircleShape shape; shape.m_radius = 0.5F; return std::make_shared<b2CircleShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShapePlank() { b2PolygonShape shape; shape.SetAsBox(1.5F, 0.1F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShapeThickPlank() { b2PolygonShape shape; shape.SetAsBox(1.5F, 0.2F); return std::make_shared<b2PolygonShape>(shape); }
std::shared_ptr<b2Shape> gm::CreateShapeTri() {
    b2PolygonShape shape;
    b2Vec2 v[3] = {{0.5F, -0.3F},{0, 0.58F},{-0.5F, -0.3F}};
    shape.Set(v, 3); return std::make_shared<b2PolygonShape>(shape);
}

const std::unordered_map<gm::BlockShape, gm::BlockShapeData> gm::shapeProperties = {
    { gm::BlockShape::block_1x1, { gm::BlockShape::block_1x1, 1, 1, gm::CreateShape1x1(), {0, 0}}},
    { gm::BlockShape::block_2x1, { gm::BlockShape::block_2x1, 2, 1, gm::CreateShape2x1(), {0, 0}}},
    { gm::BlockShape::block_2x2, { gm::BlockShape::block_2x2, 4, 2, gm::CreateShape2x2(), {0, 0}}},        
    { gm::BlockShape::block_ball, { gm::BlockShape::block_ball, 3.1415926F, 1, gm::CreateShapeBall(), {0, 0}}},
    { gm::BlockShape::block_tri, { gm::BlockShape::block_tri, 0.435F, 0.87F, gm::CreateShapeTri(), {0, 0}}},
    { gm::BlockShape::block_plank, { gm::BlockShape::block_plank, 0.6F, 0.2F, gm::CreateShapePlank(), {0, 0}}},
    { gm::BlockShape::block_thickplanck, { gm::BlockShape::block_thickplanck, 1.2F, 0.4F, gm::CreateShapeThickPlank(), {0, 0}}}
};



int gm::GetObjectGroup(gm::GameObjectType type) {
    if(type <= gm::GameObjectType::background_person3) return gm::GameObjectGroup::background;
    else if(type < gm::GameObjectType::catapult) return gm::GameObjectGroup::block;
    else if(type <= gm::GameObjectType::fuksi) return gm::GameObjectGroup::teekkari;
    else if(type <= gm::GameObjectType::ability_integral) return gm::GameObjectGroup::effect;
    else return -1;
}

int GetObjectScore(gm::GameObjectType type) {
    return 0;
}

std::unique_ptr<GameObject> gm::IDToObject(Game& game, gm::GameObjectType type, float x, float y, float rot) {

    // Block
    if(type >= gm::GameObjectType::block_wood1x1 && type <= gm::GameObjectType::thickplank_concrete) return std::make_unique<Block>(game, type, x, y, rot);
    else return std::unique_ptr<GameObject>(nullptr);


}
