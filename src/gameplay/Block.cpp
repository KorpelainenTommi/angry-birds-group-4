#include <gameplay/Block.hpp>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <math.h>

Block::Block(Game& game, gm::GameObjectType type, float x, float y, float rot) : 
    PhysObject(game, type, x, y, rot), blockData_(gm::blockTypes.at(type)), shapeData_(gm::shapeProperties.at(blockData_.shape)),
    materialData_(gm::materialProperties.at(blockData_.material)) {


    //Create the main body
    b2BodyDef definition;
    definition.type = b2BodyType::b2_dynamicBody;
    definition.fixedRotation = false;
    definition.position = {x, y};
    definition.angle = rot;

    mainBody_ = game.GetB2World().CreateBody(&definition);


    b2FixtureDef fixture;
    b2FixtureUserData userData;
    userData.data = this;
    fixture.density = materialData_.density;
    fixture.friction = materialData_.friction;
    fixture.restitution = materialData_.restitution;
    fixture.shape = shapeData_.b2shape.get();
    fixture.userData = userData;
    
    mainBody_->CreateFixture(&fixture);

}

void Block::Render(const RenderSystem& r) {

    float xOfs = shapeData_.spriteOffset.x;
    float yOfs = shapeData_.spriteOffset.y;
    b2Vec2 offset0 = { cosf(rot_.f0) * xOfs - sinf(rot_.f0) * yOfs, sinf(rot_.f0) * xOfs + cosf(rot_.f0) * yOfs };
    b2Vec2 offset1 = { cosf(rot_) * xOfs - sinf(rot_) * yOfs, sinf(rot_) * xOfs + cosf(rot_) * yOfs };
    ph::tfloat x; x.f0 = x_.f0 + offset0.x; x.f1 = x_.f1 + offset1.x;
    ph::tfloat y; y.f0 = y_.f0 + offset0.y; y.f1 = y_.f1 + offset1.y;
    r.RenderSprite(blockData_.sprite, x, y, shapeData_.height, -180 * rot_ / 3.14159265F, game_.GetCamera());

}