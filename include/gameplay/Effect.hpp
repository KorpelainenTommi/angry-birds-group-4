#include <include/gameplay/GameObjectTypes.hpp>
#include <include/gameplay/GameObject.hpp>
#include <include/gameplay/Physics.hpp>

class Effect : public GameObject {
public:
    Effect(Game& game, gm::GameObjectType objectType, float x, float y, float rot, float fps, float duration) : GameObject(game, objectType, x, y, rot), fps_(fps), duration_(duration) {starting_time = game_.GetTime();};

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

    ~Effect();

private:

    float fps_;
    float starting_time;
    float duration_;
};