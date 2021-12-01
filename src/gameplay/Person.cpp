#include <gameplay/Person.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_revolute_joint.h>

#include <iostream>


Person::Person(Game& game, gm::GameObjectType type, float x, float y, float rot) : 
    PhysObject(game, type, x, y, rot) {

    float density = ph::personMass / totalVolume;

    headX_ = x;
    headY_ = y;
    headRot_ = ph::rotToAng(rot);
    
    armRX_ = x;
    armRY_ = y;
    armRRot_ = ph::rotToAng(rot);

    armLX_ = x;
    armLY_ = y;
    armLRot_ = ph::rotToAng(rot);

    legRX_ = x;
    legRY_ = y;
    legRRot_ = ph::rotToAng(rot);

    legLX_ = x;
    legLY_ = y;
    legLRot_ = ph::rotToAng(rot);


    //Create torso

    b2BodyDef torsoDefinition;
    torsoDefinition.type = b2BodyType::b2_dynamicBody;
    torsoDefinition.fixedRotation = false;
    torsoDefinition.position = {x, y};
    torsoDefinition.angle = ph::rotToAng(rot);

    mainBody_ = game.GetB2World().CreateBody(&torsoDefinition);

    b2PolygonShape torsoShape;
    torsoShape.SetAsBox(torsoWidth / 2, torsoHeight / 2);

    b2FixtureDef torsoFixture;
    b2FixtureUserData userData;
    torsoFixture.density = density;
    torsoFixture.restitution = restitution;
    torsoFixture.shape = &torsoShape;
    userData.data = this;
    torsoFixture.userData = userData;
    torsoFixture.filter.groupIndex = -5;
    
    mainBody_->CreateFixture(&torsoFixture);

    //Create arms

    b2BodyDef armDefinition;
    armDefinition.type = b2BodyType::b2_dynamicBody;
    armDefinition.fixedRotation = false;
    armDefinition.position = {x, y};
    armDefinition.angle = ph::rotToAng(rot);

    armRBody_ = game_.GetB2World().CreateBody(&armDefinition);
    armLBody_ = game_.GetB2World().CreateBody(&armDefinition);

    b2PolygonShape armShape;
    armShape.SetAsBox(armWidth / 2, armHeight / 2);

    b2FixtureDef armFixture;
    armFixture.density = density;
    armFixture.restitution = restitution;
    armFixture.shape = &armShape;
    armFixture.userData = userData;
    armFixture.filter.groupIndex = -5;
    
    armRBody_->CreateFixture(&armFixture);
    armLBody_->CreateFixture(&armFixture);

    //Create legs

    b2BodyDef legDefinition;
    legDefinition.type = b2BodyType::b2_dynamicBody;
    legDefinition.fixedRotation = false;
    legDefinition.position = {x, y};
    legDefinition.angle = ph::rotToAng(rot);

    legRBody_ = game_.GetB2World().CreateBody(&legDefinition);
    legLBody_ = game_.GetB2World().CreateBody(&legDefinition);

    b2PolygonShape legShape;
    legShape.SetAsBox(legWidth / 2, legHeight / 2);

    b2FixtureDef legFixture;
    legFixture.density = density;
    legFixture.restitution = restitution;
    legFixture.shape = &legShape;
    legFixture.userData = userData;
    legFixture.filter.groupIndex = -5;
    
    legRBody_->CreateFixture(&legFixture);
    legLBody_->CreateFixture(&legFixture);

    //Create head

    b2BodyDef headDefinition;
    headDefinition.type = b2BodyType::b2_dynamicBody;
    headDefinition.fixedRotation = false;
    headDefinition.position = {x, y};
    headDefinition.angle = ph::rotToAng(rot);

    headBody_ = game_.GetB2World().CreateBody(&headDefinition);

    b2CircleShape headShape;
    headShape.m_radius = headHeight / 2;

    b2FixtureDef headFixture;
    headFixture.density = density;
    headFixture.restitution = restitution;
    headFixture.shape = &headShape;
    headFixture.userData = userData;
    headFixture.filter.groupIndex = -5;

    headBody_->CreateFixture(&headFixture);

    //Connect head to torso

    b2RevoluteJointDef headJoint;
    headJoint.bodyA = mainBody_;
    headJoint.bodyB = headBody_;
    headJoint.localAnchorA = {0, 0.44179F * Person::torsoHeight};
    headJoint.localAnchorB = {0.158878F * Person::headWidth, -0.383333F * Person::headHeight};
    headJoint.enableLimit = true;
    headJoint.referenceAngle = 0;
    headJoint.lowerAngle = ph::rotToAng(30);
    headJoint.upperAngle = ph::rotToAng(-10);
    headJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&headJoint);


    //Connect arms to torso
    b2RevoluteJointDef armLJoint;
    armLJoint.bodyA = mainBody_;
    armLJoint.bodyB = armLBody_;
    armLJoint.localAnchorA = {0.32307F * Person::torsoWidth, 0.18179F * Person::torsoHeight};
    armLJoint.localAnchorB = {0.1764705F * Person::armWidth, 0.275F * Person::armHeight};
    armLJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&armLJoint);

    b2RevoluteJointDef armRJoint;
    armRJoint.bodyA = mainBody_;
    armRJoint.bodyB = armRBody_;
    armRJoint.localAnchorA = {-0.32307F * Person::torsoWidth, 0.18179F * Person::torsoHeight};
    armRJoint.localAnchorB = {0.1764705F * Person::armWidth, 0.275F * Person::armHeight};
    armRJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&armRJoint);


    //Connect legs to torso
    b2RevoluteJointDef legLJoint;
    legLJoint.bodyA = mainBody_;
    legLJoint.bodyB = legLBody_;
    legLJoint.localAnchorA = {0.26307F * Person::torsoWidth, -0.28179F * Person::torsoHeight};
    legLJoint.localAnchorB = {-0.1864705F * Person::legWidth, 0.335F * Person::legHeight};
    legLJoint.enableLimit = true;
    legLJoint.referenceAngle = 0;
    legLJoint.lowerAngle = ph::rotToAng(45);
    legLJoint.upperAngle = ph::rotToAng(-60);
    legLJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&legLJoint);

    b2RevoluteJointDef legRJoint;
    legRJoint.bodyA = mainBody_;
    legRJoint.bodyB = legRBody_;
    legRJoint.localAnchorA = {-0.26307F * Person::torsoWidth, -0.28179F * Person::torsoHeight};
    legRJoint.localAnchorB = {-0.1864705F * Person::legWidth, 0.335F * Person::legHeight};
    legRJoint.enableLimit = true;
    legRJoint.referenceAngle = 0;
    legRJoint.lowerAngle = ph::rotToAng(45);
    legRJoint.upperAngle = ph::rotToAng(-60);    
    legRJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&legRJoint);

    hp_ = ph::teekkariHP;
    Record();

}

Person::~Person() {
    game_.GetB2World().DestroyBody(headBody_);
    game_.GetB2World().DestroyBody(armRBody_);
    game_.GetB2World().DestroyBody(armLBody_);
    game_.GetB2World().DestroyBody(legRBody_);
    game_.GetB2World().DestroyBody(legLBody_);
}

void Person::Record() {
    x_.Record();
    y_.Record();
    rot_.Record();

    headX_.Record();
    headY_.Record();
    headRot_.Record();
    
    armRX_.Record();
    armRY_.Record();
    armRRot_.Record();

    armLX_.Record();
    armLY_.Record();
    armLRot_.Record();

    legRX_.Record();
    legRY_.Record();
    legRRot_.Record();

    legLX_.Record();
    legLY_.Record();
    legLRot_.Record();

}

void Person::Update() {
    //Record previous state
    this->Record();

    //Update current state based on box2d
    const b2Vec2& torsoPos = mainBody_->GetPosition();
    x_ = torsoPos.x;
    y_ = torsoPos.y;
    rot_ = ph::angToRot(mainBody_->GetAngle());

    const b2Vec2& headPos = headBody_->GetPosition();
    headX_ = headPos.x;
    headY_ = headPos.y;
    headRot_ = ph::angToRot(headBody_->GetAngle());

    const b2Vec2& armRPos = armRBody_->GetPosition();
    armRX_ = armRPos.x;
    armRY_ = armRPos.y;
    armRRot_ = ph::angToRot(armRBody_->GetAngle());

    const b2Vec2& armLPos = armLBody_->GetPosition();
    armLX_ = armLPos.x;
    armLY_ = armLPos.y;
    armLRot_ = ph::angToRot(armLBody_->GetAngle());

    const b2Vec2& legRPos = legRBody_->GetPosition();
    legRX_ = legRPos.x;
    legRY_ = legRPos.y;
    legRRot_ = ph::angToRot(legRBody_->GetAngle());

    const b2Vec2& legLPos = legLBody_->GetPosition();
    legLX_ = legLPos.x;
    legLY_ = legLPos.y;
    legLRot_ = ph::angToRot(legLBody_->GetAngle());


    //Important! Immediately return after destroying the object. DestroyObject causes the destructor to be called (I think???) which is why
    //any code that accesses member variables will crash if put after it

    //Destroy off screen objects
    bool offscreen = x_ > 0.5F * ph::fullscreenPlayArea || x_ < -0.5F * ph::fullscreenPlayArea;
    offscreen = offscreen || (y_ < -ph::groundThickness);

    //Destroy zero hp objects
    bool zerohp = hp_ <= 0;
    
    if(offscreen || zerohp) { game_.DestroyObject(gameID_); return; }
}

void Person::Render(const RenderSystem& r) {

    //r.RenderRect({0, 255, 0, 100}, armLX_, armLY_, armWidth, armHeight, armLRot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, legLX_, legLY_, legWidth, legHeight, legLRot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, x_, y_, torsoWidth, torsoHeight, rot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, legRX_, legRY_, legWidth, legHeight, legRRot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, armRX_, armRY_, armWidth, armHeight, armRRot_, game_.GetCamera());
    //r.RenderOval({0, 255, 0, 100}, headX_, headY_, headHeight, headHeight, headRot_, game_.GetCamera());

    r.RenderSprite(SpriteID::arm_lgray, armLX_, armLY_, armHeight, armLRot_, game_.GetCamera());
    r.RenderSprite(SpriteID::leg_lgray, legLX_, legLY_, legHeight, legLRot_, game_.GetCamera());
    r.RenderSprite(SpriteID::torso_lgray, x_, y_, torsoHeight, rot_, game_.GetCamera());
    r.RenderSprite(SpriteID::leg_lgray, legRX_, legRY_, legHeight, legRRot_, game_.GetCamera());
    r.RenderSprite(SpriteID::arm_lgray, armRX_, armRY_, armHeight, armRRot_, game_.GetCamera());
    r.RenderSprite(SpriteID::teekkari_head1, headX_, headY_, headHeight, headRot_, game_.GetCamera());

}

float Person::GetMass() const { return ph::personMass; }