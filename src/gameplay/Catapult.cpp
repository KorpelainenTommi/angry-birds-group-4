#include <gameplay/Catapult.hpp>
#include <math.h>
// Test purposes
#include <SFML/Graphics/Color.hpp>

Catapult::Catapult(Game& game, gm::GameObjectType type, float x, float y, float rot) :
    GameObject(game, type, x, y, rot) {
        
        isActive_ = true;
        x_base_ = x;
        y_base_ = y+sizeh_*0.5;
        h_base_ = sizeh_; 
        
        x_pipe_ = x;
        y_pipe_ = y+sizeh_*(0.5+0.2);
        rot_pipe_ = 45;
        h_pipe_ = sizeh_*1.1;
        
        
}

Catapult::~Catapult() {
}
bool Catapult::OnMouseMove(float xw, float yh) {
    if(!isActive_) return false;
    
    return true;
}

void Catapult::Update() {

}

void Catapult::Render(const RenderSystem& r) {
 
    r.RenderSprite(SpriteID::catapult_base, ph::tfloat(x_pipe_), ph::tfloat(y_pipe_), ph::tfloat(h_pipe_), ph::tfloat(rot_pipe_), game_.GetCamera());
    r.RenderSprite(SpriteID::catapult_base, ph::tfloat(x_base_), ph::tfloat(y_base_), ph::tfloat(h_base_), ph::tfloat(rot_base_), game_.GetCamera());

    
}

