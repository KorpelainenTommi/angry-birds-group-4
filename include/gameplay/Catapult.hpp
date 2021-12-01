#ifndef CATAPULT_HPP
#define CATAPULT_HPP
#define _USE_MATH_DEFINES
#include <gameplay/Physics.hpp>
#include <gameplay/GameObject.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <framework/RenderSystem.hpp>
#include <framework/Resources.hpp>
#include <cmath>
#include <SFML/System/Vector2.hpp>


/// A Catapult consists of base that is a static rigidbody, and a lever that is a dynamic rigidbody
class Catapult : public GameObject {
public:

    /// Construct a catapult at this position facing right
    Catapult(Game& game, gm::GameObjectType type, float x, float y, float rot);

    /// Destroy underlying rigidbodies with b2dWorld.DestroyBody()
    virtual ~Catapult();

    /// Update this GameObjects position to reflect the state in the box2d world
    virtual void Update();

    
    virtual void Render(const RenderSystem& r);
    
    virtual bool OnMouseMove(float xw, float yh);
    virtual bool OnMouseDown(const sf::Mouse::Button& e, float x, float y);
    virtual bool OnMouseUp(const sf::Mouse::Button& e, float x, float y);
    
    
private:
    bool isActive_;
    const float sizeh_ = 4;
    
    float x_base_;
    float y_base_;
    float h_base_;
    const float rot_base_ = 0;

    float x_pipe_;
    float y_pipe_;
    float h_pipe_;
    float rot_pipe_;
    
    float x_loadBar_;
    float y_loadBar_;
    float h_loadBar_;
    float w_loadBar_;
    const sf::Color barColor_ = {255, 0, 0};
    
    sf::Vector2f relativeCoords_;
    float relativeDistance_;
};



#endif
