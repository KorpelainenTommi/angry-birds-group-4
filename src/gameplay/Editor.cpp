#include <gameplay/Editor.hpp>
#include <iostream>

Editor::Editor(GameScreen &s, Level level): Game(s, level) {
        Pause();
    selectedElement_ = gm::GameObjectType::block_wood1x1;
    }

/// ui uses this to report the block/element the player wants to spawn next to the level
void Editor::SetSelectedElement(gm::GameObjectType t){
    selectedElement_ = t;
}

// add the projectile to starting projectile list and call GameScreen::UpdateProjectileList()
void Editor::AddProjectile(gm::GameObjectType t){
    teekkarisLeft_.push_back(gm::RandomTeekkari(t));
    UpdateProjectileList();
}

/// remove the element at the given idex in projectile list and call GameScreen::UpdateProjectileList()
void Editor::RemoveProjectile(std::size_t index){
    if(teekkarisLeft_.size() > index) teekkarisLeft_.erase(teekkarisLeft_.begin()+index);
    UpdateProjectileList();
}

bool Editor::OnMouseMove(float xw, float yh) {
    //screen_.GetApplication().GetRenderSystem()
    if(dragObjectID_ != -1) {
        dragX_ = xw;
        dragY_ = yh;
        float x = GetObject(dragObjectID_).GetX();
        float y = GetObject(dragObjectID_).GetY();
        x += ph::fullscreenPlayArea * camera_.zoom * (dragX_.f1 - dragX_.f0);
        y -= ph::fullscreenPlayArea * camera_.zoom * (dragY_.f1 - dragY_.f0) / ui::aspectRatio;
        GetObject(dragObjectID_).SetX(x);
        GetObject(dragObjectID_).SetY(y);
        dragX_.Record();
        dragY_.Record();
        GetObject(dragObjectID_).Record();
    }
    
    return Game::OnMouseMove(xw, yh);
}


bool Editor::OnMouseDown(const sf::Mouse::Button& button, float xw, float yh) {
    dragX_ = xw;
    dragY_ = yh;
    dragX_.Record();
    dragY_.Record();
    const RenderSystem r = screen_.GetApplication().GetRenderSystem();
    float cw = ph::fullscreenPlayArea;
    float ch = cw / ui::aspectRatio;
    float xPos = camera_.x  + (xw * cw - 0.5F * cw ) * camera_.zoom;
    float yPos = camera_.y + ((1.0F - yh) * ch - 0.5F * ch) * camera_.zoom;
    int id = -1;
    for(auto& obj : objects_) {
        if(obj.second->ContainsCoordinates(sf::Vector2f(xPos,yPos), r)) id = obj.first;
    }
    if(button == sf::Mouse::Button::Left) {
        if((dragObjectID_ = id) == -1) {
            dragObjectID_ = CreateObject(selectedElement_, xPos, yPos, 0);
        }

    }
    else if(button == sf::Mouse::Button::Right) {
        DestroyObject(id);

    }
    else {
        return Game::OnMouseDown(button, xw, yh);
    }
    return true;
}


bool Editor::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh) {
    if(button == sf::Mouse::Button::Left) {
        const RenderSystem r = screen_.GetApplication().GetRenderSystem();
        if(dragObjectID_ == -1) return true;
        std::vector<sf::Sprite> sprites =  GetObject(dragObjectID_).GetSprites(r);
        for(auto& obj : objects_) {
            if(dragObjectID_ != obj.first) {
                for(auto& s : sprites) {
                    if(obj.second->checkIntersection(s,r)) {
                        DestroyObject(dragObjectID_);
                        dragObjectID_ = -1;
                        return true;
                    }
                }
            }
        }
        
        dragObjectID_ = -1;
        
    }
    return Game::OnMouseUp(button, xw, yh);
    
}

