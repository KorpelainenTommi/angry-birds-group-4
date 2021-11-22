#include <gameplay/PhysObject.hpp>

void PhysObject::Update() { 
    
    //Record previous state
    this->Record();

    //Update current state based on box2d
    const b2Vec2& pos = mainBody_->GetPosition();
    x_ = pos.x;
    y_ = pos.y;
    rot_ = mainBody_->GetAngle();

}

void PhysObject::SetX(float x) {
    GameObject::SetX(x);
    float y = mainBody_->GetPosition().y;
    float a = mainBody_->GetAngle();
    mainBody_->SetTransform({x, y}, a);
}

void PhysObject::SetY(float y) {
    GameObject::SetY(y);
    float x = mainBody_->GetPosition().x;
    float a = mainBody_->GetAngle();
    mainBody_->SetTransform({x, y}, a);
}

void PhysObject::SetRotation(float rot) {
    GameObject::SetRotation(rot);
    mainBody_->SetTransform(mainBody_->GetPosition(), rot);
}

void PhysObject::SetPosition(float x, float y) {
    x_ = x; y_ = y;
    float a = mainBody_->GetAngle();
    mainBody_->SetTransform({x, y}, a);
}