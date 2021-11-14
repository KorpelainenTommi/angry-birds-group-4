#include <framework/AudioSystem.hpp>

void AudioSystem::SetGlobalVolume(float volume) {
    globalVolume_ = 
        (volume > 1) ? 1.0F :
        (volume < 0) ? 0.0F :
        volume;
}

void AudioSystem::PlaySound(SoundID id, float volume) {

    //Cleanup finished sources
    //Queuesize is not a hard limit, it can be exceeded if multiple sounds are playing at once
    if(soundQueue_.size() >= queueSize) {
        while(soundQueue_.size() > 0 && soundQueue_.front().getStatus() != sf::Sound::Playing)
            soundQueue_.pop();
    }

    float v = 
        (volume > 1) ? 1.0F :
        (volume < 0) ? 0.0F :
        volume;

    soundQueue_.emplace();
    sf::Sound& sound = soundQueue_.back();
    sound.setBuffer(resourceManager_.GetSound(id));
    sound.setVolume(100 * v * globalVolume_);
    sound.play();

}