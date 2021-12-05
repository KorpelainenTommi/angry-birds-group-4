#ifndef GROUND_HPP
#define GROUND_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/Physics.hpp>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <limits>

class Ground : public PhysObject {
public:
    Ground(Game& game) : PhysObject(game, gm::GameObjectType::ground_obj, 0, -0.5F * ph::groundThickness, 0) {
        b2BodyDef groundDef;
        b2PolygonShape groundShape;
        
        groundDef.type = b2BodyType::b2_staticBody;
        groundDef.position = {0, -0.5F * ph::groundThickness};
        groundShape.SetAsBox(ph::fullscreenPlayArea * 0.5F, 0.5F * ph::groundThickness);
        
        //Box2D clones the data so it doesn't matter that groundDef and groundShape go out of scope
        mainBody_ = game.GetB2World().CreateBody(&groundDef);

        b2FixtureDef fixture;
        b2FixtureUserData userData;
        userData.data = this;
        fixture.density = 0;
        fixture.shape = &groundShape;
        fixture.userData = userData;
        
        mainBody_->CreateFixture(&fixture);
        hp_ = std::numeric_limits<float>::infinity();
    }

    virtual float GetMass() const { return ph::groundMass;}

    virtual void Render(const RenderSystem& r) {
        r.RenderRect(ph::groundColor, 0, -0.5F * ph::groundThickness, ph::fullscreenPlayArea, ph::groundThickness, 0, game_.GetCamera());
    }

    virtual void Update() {
        //Empty implementation overrides default behaviour for PhysObjects
    }

    
};


#endif