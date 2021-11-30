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
    
    sf::Vector2f relativeCoords_;
    
};



#endif
