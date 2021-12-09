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
    definition.angle = ph::rotToAng(rot);

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

    hp_ = mainBody_->GetMass() * materialData_.hpMassRatio;
    Record();

}

void Block::Render(const RenderSystem& r) {
    r.RenderSprite(blockData_.sprite, x_, y_, shapeData_.height, rot_, game_.GetCamera());
}

void Block::OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact) {
    
    PhysObject::OnCollision(velocity, other, contact);
    game_.GetAudioSystem().PlaySound(materialData_.hitSound);

}

void Block::OnDeath() {
    game_.GetAudioSystem().PlaySound(materialData_.breakSound);
    game_.AddPoints(gm::GetObjectScore(objectType_));

    //Spawn points effect

    //Spawn some particles
}

bool Block::ContainsCoordinates(sf::Vector2f mouseCoords, const RenderSystem& r) {
    return r.ContainsCoordinates(blockData_.sprite, x_, y_, shapeData_.height, rot_, mouseCoords);
}
std::vector<sf::Sprite> Block::GetSprites(const RenderSystem& r) {
    std::vector<sf::Sprite> s;
    s.push_back(r.MakeSprite(blockData_.sprite, x_, y_, shapeData_.height, rot_));
    return s;
    
}
bool Block::checkIntersection(sf::Sprite s, const RenderSystem& r) {
    return r.IntersectWithSprite(blockData_.sprite, x_, y_, shapeData_.height, rot_, s);
    
}
