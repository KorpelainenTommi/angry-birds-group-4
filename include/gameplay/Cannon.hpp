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


/// @brief Projectile (teekkari) launcher
/// @details A Cannon always aims at the mouse cursor. The launch force is based on cursor distance to the cannon
class Cannon : public GameObject {
public:

    /// @brief Construct a catapult at this position facing right
    Cannon(Game& game, gm::GameObjectType type, float x, float y, float rot);

    ///@brief  Destroy underlying rigidbodies with b2dWorld.DestroyBody()
    virtual ~Cannon();

    /// @brief Update this GameObjects position to reflect the state in the box2d world
    virtual void Update();

    /// @brief Render the cannon
    virtual void Render(const RenderSystem& r);
    
    /// @brief Receive mouse events from the user
    virtual bool OnMouseMove(float xw, float yh);
    
    /// @brief Receive mouse events from the user
    virtual bool OnMouseDown(const sf::Mouse::Button& e, float x, float y);
    
    /// @brief Receive mouse events from the user
    virtual bool OnMouseUp(const sf::Mouse::Button& e, float x, float y);
    
    
private:
    bool isActive_;
    const float sizeh_ = 1;
    
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
    float relativeDistance_ = 0.5F;
};



#endif
