#ifndef AUDIO_SYSTEM_HPP
#define AUDIO_SYSTEM_HPP

#include <queue>
#include <SFML/Audio.hpp>
#include <framework/ResourceManager.hpp>

class AudioSystem {
public:
    AudioSystem(ResourceManager& resourceManager) : resourceManager_(resourceManager) {}
    void PlaySound(SoundID id, float volume = 1.0F);
    void SetGlobalVolume(float volume);

private:
    
    static const int queueSize = 18;
    float globalVolume_ = 0.3F;
    ResourceManager& resourceManager_;

    std::queue<sf::Sound> soundQueue_;
    void Cleanup();

};

#endif