#include <gameplay/Person.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_revolute_joint.h>
#include <SFML/System/Vector2.hpp>
#include <framework/RandomGen.hpp>
#include <iostream>


Person::Person(Game& game, gm::GameObjectType type, float x, float y, float rot, bool mirrored, int collisionGroup) : 
    PhysObject(game, type, x, y, rot) {

    float density = ph::personMass / totalVolume;

    //Mirroring
    float m = (mirrored) ? -1.0F : 1.0F;

    float hx = -m * 0.158878F * Person::headWidth;
    float hy = 0.44179F * Person::torsoHeight + 0.383333F * Person::headHeight;
    sf::Vector2f hv = ph::rotateVector(hx, hy, rot);

    headX_ = x + hv.x;
    headY_ = y + hv.y;
    headRot_ = rot;

    float arx = m * -0.32307F * Person::torsoWidth - m * 0.1764705F * Person::armWidth;
    float ary = 0.18179F * Person::torsoHeight - 0.275F * Person::armHeight;
    sf::Vector2f arv = ph::rotateVector(arx, ary, rot);
    
    armRX_ = x + arv.x;
    armRY_ = y + arv.y;
    armRRot_ = headRot_;

    float alx = m * 0.32307F * Person::torsoWidth - m * 0.1764705F * Person::armWidth;
    float aly = 0.18179F * Person::torsoHeight - 0.275F * Person::armHeight;
    sf::Vector2f alv = ph::rotateVector(alx, aly, rot);

    armLX_ = x + alv.x;
    armLY_ = y + alv.y;
    armLRot_ = headRot_;


    float lrx = m * -0.26307F * Person::torsoWidth - m * -0.1864705F * Person::legWidth;
    float lry = -0.28179F * Person::torsoHeight - 0.335F * Person::legHeight;
    sf::Vector2f lrv = ph::rotateVector(lrx, lry, rot);
    
    legRX_ = x + lrv.x;
    legRY_ = y + lrv.y;
    legRRot_ = headRot_;

    float llx = m * 0.26307F * Person::torsoWidth - m * 0.1864705F * Person::legWidth;
    float lly = -0.28179F * Person::torsoHeight - 0.335F * Person::legHeight;
    sf::Vector2f llv = ph::rotateVector(llx, lly, rot);
    
    legLX_ = x + llv.x;
    legLY_ = y + llv.y;
    legLRot_ = headRot_;


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
    torsoFixture.filter.groupIndex = collisionGroup;
    
    mainBody_->CreateFixture(&torsoFixture);

    //Create arms

    b2BodyDef armDefinition;
    armDefinition.type = b2BodyType::b2_dynamicBody;
    armDefinition.fixedRotation = false;
    armDefinition.angle = ph::rotToAng(rot);

    armDefinition.position = {armRX_, armRY_};
    armRBody_ = game_.GetB2World().CreateBody(&armDefinition);
    armDefinition.position = {armLX_, armLY_};
    armLBody_ = game_.GetB2World().CreateBody(&armDefinition);

    b2PolygonShape armShape;
    armShape.SetAsBox(armWidth / 2, armHeight / 2);

    b2FixtureDef armFixture;
    armFixture.density = density;
    armFixture.restitution = restitution;
    armFixture.shape = &armShape;
    armFixture.userData = userData;
    armFixture.filter.groupIndex = collisionGroup;
    
    armRBody_->CreateFixture(&armFixture);
    armLBody_->CreateFixture(&armFixture);

    //Create legs

    b2BodyDef legDefinition;
    legDefinition.type = b2BodyType::b2_dynamicBody;
    legDefinition.fixedRotation = false;
    legDefinition.angle = ph::rotToAng(rot);

    legDefinition.position = {legRX_, legRY_};
    legRBody_ = game_.GetB2World().CreateBody(&legDefinition);
    legDefinition.position = {legLX_, legLY_};
    legLBody_ = game_.GetB2World().CreateBody(&legDefinition);

    b2PolygonShape legShape;
    legShape.SetAsBox(legWidth / 2, legHeight / 2);

    b2FixtureDef legFixture;
    legFixture.density = density;
    legFixture.restitution = restitution;
    legFixture.shape = &legShape;
    legFixture.userData = userData;
    legFixture.filter.groupIndex = collisionGroup;
    
    legRBody_->CreateFixture(&legFixture);
    legLBody_->CreateFixture(&legFixture);

    //Create head

    b2BodyDef headDefinition;
    headDefinition.type = b2BodyType::b2_dynamicBody;
    headDefinition.fixedRotation = false;
    headDefinition.position = {headX_, headY_};
    headDefinition.angle = ph::rotToAng(rot);

    headBody_ = game_.GetB2World().CreateBody(&headDefinition);

    b2CircleShape headShape;
    headShape.m_radius = headHeight / 2;

    b2FixtureDef headFixture;
    headFixture.density = density;
    headFixture.restitution = restitution;
    headFixture.shape = &headShape;
    headFixture.userData = userData;
    headFixture.filter.groupIndex = collisionGroup;

    headBody_->CreateFixture(&headFixture);

    //Connect head to torso

    b2RevoluteJointDef headJoint;
    headJoint.bodyA = mainBody_;
    headJoint.bodyB = headBody_;
    headJoint.localAnchorA = {0, 0.44179F * Person::torsoHeight};
    headJoint.localAnchorB = {m * 0.158878F * Person::headWidth, -0.383333F * Person::headHeight};
    headJoint.enableLimit = true;
    headJoint.referenceAngle = 0;
    headJoint.lowerAngle = ph::rotToAng(mirrored ? 10.0F : 30.0F);
    headJoint.upperAngle = ph::rotToAng(mirrored ? -30.0F : -10.0F);
    headJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&headJoint);


    //Connect arms to torso
    b2RevoluteJointDef armLJoint;
    armLJoint.bodyA = mainBody_;
    armLJoint.bodyB = armLBody_;
    armLJoint.localAnchorA = {m * 0.32307F * Person::torsoWidth, 0.18179F * Person::torsoHeight};
    armLJoint.localAnchorB = {m * 0.1764705F * Person::armWidth, 0.275F * Person::armHeight};
    armLJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&armLJoint);

    b2RevoluteJointDef armRJoint;
    armRJoint.bodyA = mainBody_;
    armRJoint.bodyB = armRBody_;
    armRJoint.localAnchorA = {m * -0.32307F * Person::torsoWidth, 0.18179F * Person::torsoHeight};
    armRJoint.localAnchorB = {m * 0.1764705F * Person::armWidth, 0.275F * Person::armHeight};
    armRJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&armRJoint);


    //Connect legs to torso
    b2RevoluteJointDef legLJoint;
    legLJoint.bodyA = mainBody_;
    legLJoint.bodyB = legLBody_;
    legLJoint.localAnchorA = {m * 0.26307F * Person::torsoWidth, -0.28179F * Person::torsoHeight};
    legLJoint.localAnchorB = {m * -0.1864705F * Person::legWidth, 0.335F * Person::legHeight};
    legLJoint.enableLimit = true;
    legLJoint.referenceAngle = 0;
    legLJoint.lowerAngle = ph::rotToAng(mirrored ? 60.0F : 45.0F);
    legLJoint.upperAngle = ph::rotToAng(mirrored ? -45.0F : -60.0F);
    legLJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&legLJoint);

    b2RevoluteJointDef legRJoint;
    legRJoint.bodyA = mainBody_;
    legRJoint.bodyB = legRBody_;
    legRJoint.localAnchorA = {m * -0.26307F * Person::torsoWidth, -0.28179F * Person::torsoHeight};
    legRJoint.localAnchorB = {m * -0.1864705F * Person::legWidth, 0.335F * Person::legHeight};
    legRJoint.enableLimit = true;
    legRJoint.referenceAngle = 0;
    legRJoint.lowerAngle = ph::rotToAng(mirrored ? 60.0F : 45.0F);
    legRJoint.upperAngle = ph::rotToAng(mirrored ? -45.0F : -60.0F);
    legRJoint.collideConnected = false;

    game_.GetB2World().CreateJoint(&legRJoint);

    //This gets initialized by child classes, but never want this initialized to zero so...
    hp_ = 1;
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

    if(offscreen || zerohp) { 
        this->OnDeath();
        game_.DestroyObject(gameID_); return;
    }
}

void Person::OnCollision(const b2Vec2& velocity, PhysObject& other, const b2Contact& contact) {
    
    PhysObject::OnCollision(velocity, other, contact);
    if(game_.GetTime() - lastHitSound_ > ph::soundCooldown) {
        lastHitSound_ = game_.GetTime();
        SoundID sounds[] = { SoundID::thud1, SoundID::thud2, SoundID::thud3 };
        game_.GetAudioSystem().PlaySound(sounds[rng::RandomInt(0, 2)], velocity.LengthSquared() / ph::damageTreshold);
    }

}

void Person::Render(const RenderSystem& r) {

    //Hitboxes
    //r.RenderRect({0, 255, 0, 100}, armLX_, armLY_, armWidth, armHeight, armLRot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, legLX_, legLY_, legWidth, legHeight, legLRot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, x_, y_, torsoWidth, torsoHeight, rot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, legRX_, legRY_, legWidth, legHeight, legRRot_, game_.GetCamera());
    //r.RenderRect({0, 255, 0, 100}, armRX_, armRY_, armWidth, armHeight, armRRot_, game_.GetCamera());
    //r.RenderOval({0, 255, 0, 100}, headX_, headY_, headHeight, headHeight, headRot_, game_.GetCamera());

    SpriteID arm = data_.face.bType ? data_.body.armb : data_.body.arm;
    r.RenderSprite(arm, armLX_, armLY_, armHeight, armLRot_, game_.GetCamera());
    r.RenderSprite(data_.body.leg, legLX_, legLY_, legHeight, legLRot_, game_.GetCamera());
    r.RenderSprite(data_.body.torso, x_, y_, torsoHeight, rot_, game_.GetCamera());
    r.RenderSprite(data_.body.leg, legRX_, legRY_, legHeight, legRRot_, game_.GetCamera());
    r.RenderSprite(arm, armRX_, armRY_, armHeight, armRRot_, game_.GetCamera());
    r.RenderSprite(data_.face.face, headX_, headY_, headHeight, headRot_, game_.GetCamera());

}

float Person::GetMass() const { return ph::personMass; }
void Person::Impulse(const b2Vec2& f)
{ headBody_->ApplyLinearImpulseToCenter(f, true); mainBody_->ApplyLinearImpulseToCenter(f, true); }
