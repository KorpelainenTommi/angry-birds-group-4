#include <gameplay/Catapult.hpp>
#include <gameplay/Block.hpp>
#include <iostream>
Catapult::Catapult(Game& game, gm::GameObjectType type, float x, float y, float rot) :
    GameObject(game, type, x, y, rot) {
        
        isActive_ = false;
        x_base_ = x;
        y_base_ = y+sizeh_*0.5;
        h_base_ = sizeh_; 
        
        x_pipe_ = x;
        y_pipe_ = y+sizeh_*(0.5+0.2);
        rot_pipe_ = 45;
        h_pipe_ = sizeh_*1.1;
        
        w_loadBar_ = h_pipe_*0.5;
        h_loadBar_ = sizeh_*0.1;
        
}

Catapult::~Catapult() {
}
bool Catapult::OnMouseMove(float xw, float yh) {
    if(!isActive_ || relativeCoords_.x >= xw) return false;
    float angle = std::atan((xw-relativeCoords_.x)/(-yh+relativeCoords_.y))*180/M_PI;
    rot_pipe_ = angle;
    if(relativeCoords_.y < yh) rot_pipe_ += 180;
    
    relativeDistance_ = std::sqrt((xw-relativeCoords_.x)*(xw-relativeCoords_.x) + (yh-relativeCoords_.y)*(yh-relativeCoords_.y));
    if(relativeDistance_ > 0.5) relativeDistance_ = 0.5;
    w_loadBar_ = h_pipe_*relativeDistance_*2;
    float angleRad = rot_pipe_*M_PI/180;
    x_loadBar_ = x_pipe_ - std::cos(angleRad)*sizeh_*0.4 - std::sin(angleRad)*(0.5-relativeDistance_)*h_pipe_;
    y_loadBar_ = y_pipe_ + std::sin(angleRad)*sizeh_*0.4 - std::cos(angleRad)*(0.5-relativeDistance_)*h_pipe_;
    return true;
}

bool Catapult::OnMouseDown(const sf::Mouse::Button& e, float x, float y){
    isActive_ = true;
    OnMouseMove(x,y);
    return true;
}

// This function will summon a teekkari when called
bool Catapult::OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
    if(!isActive_) return false;
    isActive_ = false;
    return true;
}


void Catapult::Update() {

}

void Catapult::Render(const RenderSystem& r) {
    relativeCoords_ = r.GetRelativeCoords(sf::Vector2f(x_pipe_,y_pipe_), game_.GetCamera());
    r.RenderSprite(SpriteID::catapult_base, ph::tfloat(x_pipe_), ph::tfloat(y_pipe_), ph::tfloat(h_pipe_), ph::tfloat(rot_pipe_), game_.GetCamera());
    r.RenderSprite(SpriteID::catapult_base, ph::tfloat(x_base_), ph::tfloat(y_base_), ph::tfloat(h_base_), ph::tfloat(rot_base_), game_.GetCamera());
    
    if(isActive_) {
        r.RenderRect(barColor_, ph::tfloat(x_loadBar_), ph::tfloat(y_loadBar_), ph::tfloat(h_loadBar_), ph::tfloat(w_loadBar_), ph::tfloat(rot_pipe_), game_.GetCamera());
    }
}

