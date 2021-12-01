#include <gameplay/Cannon.hpp>
#include <gameplay/Block.hpp>
#include <gameplay/Person.hpp>
#include <iostream>
Cannon::Cannon(Game& game, gm::GameObjectType type, float x, float y, float rot) :
    GameObject(game, type, x, y, rot) {
        
        isActive_ = false;
        x_base_ = x;
        y_base_ = y+sizeh_*0.5F;
        h_base_ = sizeh_; 
        
        x_pipe_ = x;
        y_pipe_ = y+sizeh_*(0.5F+0.2F);
        rot_pipe_ = 45;
        h_pipe_ = sizeh_*2.5F;
        
        w_loadBar_ = h_pipe_*0.5F;
        h_loadBar_ = sizeh_*0.1F;
        
}

Cannon::~Cannon() {
}
bool Cannon::OnMouseMove(float xw, float yh) {
    if(!isActive_ || relativeCoords_.x >= xw) return false;
    float angle = std::atan((xw-relativeCoords_.x)/(-yh+relativeCoords_.y))*180/ph::pi;
    if(relativeCoords_.y < yh) angle += 180;
    if(angle < 15 || angle > 110) return true;
    rot_pipe_ = angle;
    relativeDistance_ = std::sqrt((xw-relativeCoords_.x)*(xw-relativeCoords_.x) + (yh-relativeCoords_.y)*(yh-relativeCoords_.y));
    if(relativeDistance_ > 0.5F) relativeDistance_ = 0.5F;
    w_loadBar_ = h_pipe_*relativeDistance_*2;
    float angleRad = rot_pipe_*ph::pi/180;
    x_loadBar_ = x_pipe_ - std::cos(angleRad)*sizeh_*0.4F - std::sin(angleRad)*(0.5F-relativeDistance_)*h_pipe_;
    y_loadBar_ = y_pipe_ + std::sin(angleRad)*sizeh_*0.4F - std::cos(angleRad)*(0.5F-relativeDistance_)*h_pipe_;
    return true;
}

bool Cannon::OnMouseDown(const sf::Mouse::Button& e, float x, float y){
    if(e != sf::Mouse::Button::Left) return false;
    isActive_ = true;
    OnMouseMove(x,y);
    return true;
}

// This function will summon a teekkari when called
bool Cannon::OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
    if(!isActive_ || e != sf::Mouse::Button::Left) return false;
    isActive_ = false;

    //Shoot teekkari (This is a demo version with a Person)
    
    float angleRad = ph::rotToAng(rot_pipe_);
    b2Vec2 dir = { -std::sin(angleRad), std::cos(angleRad) };
    int id = game_.AddObject(std::make_unique<Person>(game_, gm::GameObjectType::teekkari_teemu, x_pipe_+dir.x*sizeh_, y_pipe_+dir.y*sizeh_, 0));
    GameObject& obj = game_.GetObject(id);
    Person& p = (Person&)obj;
    p.Impulse({dir.x * relativeDistance_ * ph::cannonMaxForce, dir.y * relativeDistance_ * ph::cannonMaxForce});

    return true;
}


void Cannon::Update() {

}

void Cannon::Render(const RenderSystem& r) {
    relativeCoords_ = r.GetRelativeCoords(sf::Vector2f(x_pipe_,y_pipe_), game_.GetCamera());
    r.RenderSprite(SpriteID::cannon_head, ph::tfloat(x_pipe_), ph::tfloat(y_pipe_), ph::tfloat(h_pipe_), ph::tfloat(rot_pipe_), game_.GetCamera());
    r.RenderSprite(SpriteID::cannon_base, ph::tfloat(x_base_), ph::tfloat(y_base_), ph::tfloat(h_base_), ph::tfloat(rot_base_), game_.GetCamera());
    
    if(isActive_) {
        r.RenderRect(barColor_, ph::tfloat(x_loadBar_), ph::tfloat(y_loadBar_), ph::tfloat(h_loadBar_), ph::tfloat(w_loadBar_), ph::tfloat(rot_pipe_), game_.GetCamera());
    }
}

