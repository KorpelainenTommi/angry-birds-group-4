#include <gameplay/ParticleEffect.hpp>
#include <framework/RandomGen.hpp>
#include <gameplay/Block.hpp>
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_api.h>
#include <ui/UIConstants.hpp>
#include <sstream>
#include <cmath>
#include <iostream>

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
    if(game_.GetTime() - lastHitSound_ > ph::soundCooldown) {
        lastHitSound_ = game_.GetTime();
        game_.GetAudioSystem().PlaySound(materialData_.hitSound, velocity.LengthSquared() / ph::damageTreshold);
    }

}

void Block::OnDeath() {
    game_.GetAudioSystem().PlaySound(materialData_.breakSound);
    game_.AddPoints(gm::GetObjectScore(objectType_));


    //Spawn some particles

    for(int i = 0; i < 10; i++) {
        
        //Random point inside circle
        float a = 2.0F * ph::pi * rng::RandomF();
        float u = rng::RandomF() + rng::RandomF();
        float r = (u > 1) ? 2 - u : u;
        float x = shapeData_.height * r * std::cosf(a);
        float y = shapeData_.height * r * std::sinf(a);
        int id = game_.AddObject(std::make_unique<PhysParticle>(game_, x_ + x, y_ + y, ph::angToRot(a)));
        PhysParticle& p = (PhysParticle&)game_.GetObject(id);

        p.SetSize(0.25F);
        p.SetSprite(materialData_.particle);
        p.Angular(rng::RandomInt(0, 1) ? rng::RandomF() * 0.4F : -rng::RandomF() * 0.4F);
        p.Explosion({x_, y_}, 30.0F);

    }

    //Spawn points effect
    int points = gm::GetObjectScore(objectType_);
    int id = game_.AddObject(std::make_unique<TextParticle>(game_, x_, y_, 0.0F));
    TextParticle& textP = (TextParticle&)game_.GetObject(id);
    textP.SetSize(1.0F);
    int r = (int)std::roundf(255 * points / 1400.0F);
    if(r > 255) r = 255;
    int g = (2000 - points);
    g = (int)std::roundf(255 * g / 2000.0F);
    if(g > 255) g = 255;
    textP.SetColor(sf::Color(r, g, 0, 255));
    std::stringstream ss;
    ss << points;
    textP.SetText(ss.str());


}

bool Block::ContainsCoordinates(sf::Vector2f mouseCoords, const RenderSystem& r) {

    auto absCoords = mouseCoords;
    return mainBody_->GetFixtureList()[0].TestPoint({absCoords.x, absCoords.y});

}

std::vector<sf::Sprite> Block::GetSprites(const RenderSystem& r) {
    std::vector<sf::Sprite> s;
    s.push_back(r.MakeSprite(blockData_.sprite, x_, y_, shapeData_.height, rot_));
    return s;
    
}

bool Block::CheckIntersection(sf::Sprite s, const RenderSystem& r) {
    return r.IntersectWithSprite(blockData_.sprite, x_, y_, shapeData_.height, rot_, s);
    
}


std::vector<b2Body*> Block::GetPhysBodies() {
    std::vector<b2Body*> vec;
    vec.push_back(mainBody_);
    return vec;
}

bool Block::CheckIntersection(b2Body* other) {
    return b2TestOverlap(mainBody_->GetFixtureList()[0].GetShape(), 0, other->GetFixtureList()[0].GetShape(), 0, mainBody_->GetTransform(), other->GetTransform());
}

const gm::BlockMaterial Block::GetBlockMaterial() const {
    return blockData_.material;
}

bool Block::ElectricityCheck(Block& block) {
    return true;
}
