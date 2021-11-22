#include <gameplay/Game.hpp>
#include <gameplay/Physics.hpp>
#include <screens/GameScreen.hpp>

void Game::Update() {

    world_.Step(ph::Timestep, ph::velocityIters, ph::positionIters);

    for(auto& obj : objects_) {
        obj.second->Update();
    }

}

void Game::Render(const RenderSystem& r) {

    for(auto& obj : objects_) {
        obj.second->Render(r);
    }

}


Camera Game::GetCamera() const { return camera_; }
AudioSystem& Game::GetAudioSystem() const { return screen_.GetApplication().GetAudioSystem(); }
b2World& Game::GetB2World() { return world_; }