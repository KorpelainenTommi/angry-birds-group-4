#include <GameObject.hpp>

///         GameObject          ///

GameObject::GameObject(BOX2D_H::b2World* world, float x, float y, char type){
    world_ = world;
    bodyDef_.position.Set(x, y);
    if(type == 'd'){                     //automatically static object, so changed only if type is 'd' (dynamic)
        bodyDef_.type == b2_dynamicBody;
    }
    body_ = world_->CreateBody(&bodyDef_);
};

BOX2D_H::b2Vec2 GameObject::GetCoordinates(){
    return body_->GetPosition();
};

float GameObject::GetRotation(){
    return body_->GetAngle();
};

BOX2D_H::b2Body* GameObject::GetBody(){
    return body_;
};

void GameObject::SetCollisionsOff(){
    body_->GetFixtureList()->SetSensor(true); ///Doesn't seem to return list as it says in function name?
    /*for(int i = 0; i < (body_->GetFixtureList()).size; i++){
        body_->GetFixtureList().get(i).setSensor(true);
    }*/
}

void GameObject::SetCollisionsOn(){
    body_->GetFixtureList()->SetSensor(false);
    /*for(int i = 0; i < body_->GetFixtureList().size; i++){
        body_->GetFixtureList().get(i).setSensor(false);
    }*/
}

///         Block           ///

Block::Block(BOX2D_H::b2World* world, float x, float y, char material = 'w', float height = 1.0f, float width = 1.0f) : PhysObject(world, x, y){
    shapeDef_.SetAsBox(height/2, width/2);
    fixtureDef_.shape = &shapeDef_;
    material_ = material;
    if(material == 'w'){              ///wood
        fixtureDef_.density = 600.0f; ///density of wood in kg/m^3 (propably should be changed later?)
        fixtureDef_.friction = 0.2f;
    }
    else if(material == 's'){         ///steel
        fixtureDef_.density = 8000.0f;
        fixtureDef_.friction = 0.2f;
    }
    else if(material == 'g'){         ///glass
        fixtureDef_.density = 2500.0f;
        fixtureDef_.friction = 0.2f;
    }
    else{
        material_ = 'u';               ///undef
        fixtureDef_.density = 1.0f;
        fixtureDef_.friction = 0.2f;
    }
    GameObject::SetFixture(fixtureDef_);
};


Circle::Circle(BOX2D_H::b2World* world, float x, float y, char material = 'w', float radius) : PhysObject(world, x, y){
    shapeDef_.m_radius = radius;
    fixtureDef_.shape = &shapeDef_;
    material_ = material;
    if(material == 'w'){              ///wood
        fixtureDef_.density = 600.0f; ///density of wood in kg/m^3 (propably should be changed later?)
        fixtureDef_.friction = 0.2f;
    }
    else if(material == 's'){         ///steel
        fixtureDef_.density = 8000.0f;
        fixtureDef_.friction = 0.2f;
    }
    else if(material == 'g'){         ///glass
        fixtureDef_.density = 2500.0f;
        fixtureDef_.friction = 0.2f;
    }
    else{
        material_ = 'u';               ///undef
        fixtureDef_.density = 1.0f;
        fixtureDef_.friction = 0.2f;
    }
    GameObject::SetFixture(fixtureDef_);
};


///     Collision      ///

GroundBlock::GroundBlock(BOX2D_H::b2World* world, float x, float y, float height, float width) : StatObject(world, x, y){
    shapeDef_.SetAsBox(height/2, width/2);
    fixtureDef_.shape = &shapeDef_;
    fixtureDef_.friction = 0.3f;
    GameObject::SetFixture(fixtureDef_);
};