#ifndef GROUND_HPP
#define GROUND_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/Physics.hpp>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <limits>

/// @brief Ground class
class Ground : public PhysObject {
public:
    /// @brief Constructs the ground according to the dimensions in physics-hpp
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
    /// @brief Get the mass of the ground
    virtual float GetMass() const { return ph::groundMass;}
   /// @brief Renders the ground
    virtual void Render(const RenderSystem& r) {
        r.RenderRect(ph::groundColor, 0, -0.5F * ph::groundThickness, ph::fullscreenPlayArea, ph::groundThickness, 0, game_.GetCamera());
    }
    /// @brief Update ground. Empty implementation overrides default behaviour for PhysObjects and therefore ground is not updated.
    virtual void Update() {
    }
    virtual bool ContainsCoordinates(sf::Vector2f mouseCoords, const RenderSystem& r) { false; }

    
};


#endif
