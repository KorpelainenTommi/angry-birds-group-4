#ifndef EFFECT_HPP
#define EFFECT_HPP
#include <framework/Resources.hpp>
#include <gameplay/GameObjectTypes.hpp>
#include <gameplay/GameObject.hpp>
#include <gameplay/Physics.hpp>
#include <iostream>

class Effect : public GameObject {
public:
    Effect(Game& game, AnimationID anim, float x, float y, float rot, float size = 1.0F, float fps = 24.0F, float duration = 1.0F, bool loop = false) :
    GameObject(game, gm::GameObjectType::anim_effect, x, y, rot), fps_(fps), size_(size), duration_(duration), loop_(loop), animationID_(anim)
    {starting_time = game_.GetTime();}

    int GetFrame(){
        float time = game_.GetTime() - starting_time;
        return (int)(time * fps_);
    }

    bool CheckDuration(){  ///For checking if effect has ended
        if(game_.GetTime() - starting_time > duration_){
            return true;
        }
        return false;
    }

    virtual void Render(const RenderSystem& r) {

        int frame = CheckDuration() ? (int)(duration_ * fps_) : GetFrame();
        if(loop_) frame = GetFrame();
        r.RenderAnimation(animationID_, frame, x_, y_, size_, rot_, game_.GetCamera());

    }

    virtual void Update() {
        if(CheckDuration()) game_.DestroyObject(gameID_);
    }

private:

    float fps_;
    float size_;
    float starting_time;
    float duration_;
    bool loop_;
    AnimationID animationID_;
};

#endif