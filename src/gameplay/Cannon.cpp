#include <gameplay/Cannon.hpp>
#include <gameplay/Block.hpp>
#include <gameplay/Teekkari.hpp>
#include <gameplay/Effect.hpp>
#include <cmath>
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
        
        float angleRad = rot_pipe_*ph::pi/180;
        x_loadBar_ = x_pipe_ - std::cos(angleRad)*sizeh_*0.6F - std::sin(angleRad)*(0.1F-relativeDistance_*0.5F)*h_pipe_;
        y_loadBar_ = y_pipe_ + std::sin(angleRad)*sizeh_*0.6F - std::cos(angleRad)*(0.1F-relativeDistance_*0.5F)*h_pipe_;
        w_loadBar_ = h_pipe_*0.5F;
        h_loadBar_ = sizeh_*0.1F;
        
}

Cannon::~Cannon() {
}
bool Cannon::OnMouseMove(float xW, float yH) {
    if(!isActive_ || game_.CannonDisabled()) return false;

    float rx = relativeCoords_.x;
    float ry = relativeCoords_.y;
    float xw = xW;
    float yh = yH;
    if(rx >= xw) xw = rx;
    
    relativeDistance_ = sqrtf((xw-rx)*(xw-rx) + (yh-ry)*(yh-ry));
    if(relativeDistance_ > 0.5F) relativeDistance_ = 0.5F;
    w_loadBar_ = h_pipe_*relativeDistance_;
    
    float angle = atanf((xw-rx)/(-yh+ry))*180/ph::pi;
    if(ry < yh) angle += 180;
    if(angle > 0 && angle < 110) rot_pipe_ = angle;
    else {
        if(ry < yh) rot_pipe_ = 110;
        else rot_pipe_ = atanf(0.01F/(-yh+ry))*180/ph::pi;
    }
    float angleRad = rot_pipe_*ph::pi/180;
    x_loadBar_ = x_pipe_ - cosf(angleRad)*sizeh_*0.6F - std::sin(angleRad)*(0.1F-relativeDistance_*0.5F)*h_pipe_;
    y_loadBar_ = y_pipe_ + sinf(angleRad)*sizeh_*0.6F - std::cos(angleRad)*(0.1F-relativeDistance_*0.5F)*h_pipe_;
    return true;
}

bool Cannon::OnMouseDown(const sf::Mouse::Button& e, float x, float y){
    if(e != sf::Mouse::Button::Left || game_.CannonDisabled()) return false;
    isActive_ = true;
    game_.GetAudioSystem().PlaySound(SoundID::cannon_load);
    OnMouseMove(x,y);
    return true;
}

// This function will summon a teekkari when called
bool Cannon::OnMouseUp(const sf::Mouse::Button& e, float x, float y) {
    if(!isActive_ || e != sf::Mouse::Button::Left || game_.CannonDisabled()) return false;
    isActive_ = false;

    //Shoot selected teekkari


    float angleRad = ph::rotToAng(rot_pipe_);
    b2Vec2 dir = { -sinf(angleRad), cosf(angleRad) };

    gm::PersonData teekkari;
    if(game_.TakeProjectile(teekkari)) {
        
        int id = game_.CreateTeekkari(teekkari, x_pipe_+dir.x*sizeh_*1.8F, y_pipe_+dir.y*sizeh_*1.8F, rot_pipe_);
        Teekkari& t = (Teekkari&)game_.GetObject(id);
        t.Impulse({dir.x * relativeDistance_ * ph::cannonMaxForce, dir.y * relativeDistance_ * ph::cannonMaxForce});
        
        //Effects
        game_.GetAudioSystem().PlaySound(SoundID::cannon_shot);

        game_.AddObject(std::make_unique<Effect>(game_, AnimationID::cannon_explosion,
        x_pipe_+dir.x*sizeh_*2.0F, y_pipe_+dir.y*sizeh_*2.0F, rot_pipe_-90, 2.0F, 60.0F, 0.0666666F));

        return true;
    } else return false;
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

