#include <gameplay/Editor.hpp>
#include <box2d/b2_body.h>
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
    if(!teekkarisLeft_.empty()) {
        levelMaxScore_ += ph::teekkariScore;
        screen_.UpdateTheoreticalMaxScore(levelMaxScore_);
    }
    teekkarisLeft_.push_back(gm::RandomTeekkari(t));
    UpdateProjectileList();
}

/// remove the element at the given idex in projectile list and call GameScreen::UpdateProjectileList()
void Editor::RemoveProjectile(std::size_t index){
    if(teekkarisLeft_.size() > index) { 

        if(teekkarisLeft_.size() > 1) {
            levelMaxScore_ -= ph::teekkariScore;
            screen_.UpdateTheoreticalMaxScore(levelMaxScore_);
        }
        teekkarisLeft_.erase(teekkarisLeft_.begin()+index);
    }
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
    if(button == sf::Mouse::Button::Left && isPaused_) {
        if((dragObjectID_ = id) == -1) {
            dragObjectID_ = CreateObject(selectedElement_, xPos, yPos, 0);
            levelMaxScore_ += gm::GetObjectScore(GetObject(dragObjectID_).GetObjectType());
            screen_.UpdateTheoreticalMaxScore(levelMaxScore_);
        }

    }
    else if(button == sf::Mouse::Button::Right && isPaused_) {
        if(id != -1) {
            levelMaxScore_ -= gm::GetObjectScore(GetObject(id).GetObjectType());
            screen_.UpdateTheoreticalMaxScore(levelMaxScore_);
            DestroyObject(id);
        }
    }
    else {
        return Game::OnMouseDown(button, xw, yh);
    }
    return true;
}


bool Editor::OnMouseUp(const sf::Mouse::Button& button, float xw, float yh) {
    if(button == sf::Mouse::Button::Left && isPaused_) {
        const RenderSystem r = screen_.GetApplication().GetRenderSystem();
        if(dragObjectID_ == -1) return true;
        std::vector<sf::Sprite> sprites =  GetObject(dragObjectID_).GetSprites(r);
        std::vector<b2Body*> bodies = GetObject(dragObjectID_).GetPhysBodies();
        for(auto& s : sprites) {
            if(r.CheckGround(s)) {
                levelMaxScore_ -= gm::GetObjectScore(GetObject(dragObjectID_).GetObjectType());
                screen_.UpdateTheoreticalMaxScore(levelMaxScore_);
                DestroyObject(dragObjectID_);
                dragObjectID_ = -1;
                return true;
            }
        }
        for(auto& obj : objects_) {
            if(dragObjectID_ != obj.first) {
                for(auto b : bodies) {
                    if(obj.second->CheckIntersection(b)) {
                        levelMaxScore_ -= gm::GetObjectScore(GetObject(dragObjectID_).GetObjectType());
                        screen_.UpdateTheoreticalMaxScore(levelMaxScore_);
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


Level& Editor::GetLevel() {
    return level_;
}

void Editor::SaveLevel() {
    level_.objectData.clear();
    for(auto& obj : objects_) {
        if(obj.second->GetObjectType() != gm::GameObjectType::ground_obj && obj.second->GetObjectType() != gm::GameObjectType::cannon) {
            gm::GameObjectData data = {obj.second->GetX().f0,obj.second->GetY().f0,obj.second->GetRot().f0,obj.second->GetObjectType()};
            level_.objectData.push_back(data);            
        }
    }
    level_.startingTeekkaris.clear();
    for(auto& teekkari : teekkarisLeft_) {
        level_.startingTeekkaris.push_back(teekkari.objType);
    }
}

bool Editor::OnKeyDown(const sf::Event::KeyEvent& key){
    if(key.code == sf::Keyboard::Up && dragObjectID_ != -1) {
        float rot = GetObject(dragObjectID_).GetRot().f0;
        GetObject(dragObjectID_).SetRotation(rot + 10.0F);
        GetObject(dragObjectID_).Record();
    }
    else if(key.code == sf::Keyboard::Down && dragObjectID_ != -1){
        float rot = GetObject(dragObjectID_).GetRot().f0;
        GetObject(dragObjectID_).SetRotation(rot - 10.0F);
        GetObject(dragObjectID_).Record();
    }
    else return false;
    return true;
}

bool Editor::InPlayMode() const {
    return playMode_;
}

void Editor::Restart() {
    playMode_ = false;
    Game::Restart();
}

void Editor::Play() {
    SaveLevel();
    playMode_ = true;
    isPaused_ = false;
}

void Editor::Resume() {
    if(playMode_) isPaused_ = false;
    else isPaused_ = true;
}