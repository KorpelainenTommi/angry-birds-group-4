#ifndef AUDIO_SYSTEM_HPP
#define AUDIO_SYSTEM_HPP

#include <queue>
#include <SFML/Audio.hpp>
#include <framework/ResourceManager.hpp>

/// Framework class for playing sound effects using SoundIDs
class AudioSystem {
public:

    /// Construct an AudioSystem that queries sounds from this ResourceManager
    AudioSystem(ResourceManager& resourceManager) : resourceManager_(resourceManager) {}
    
    /// Play the sound specified by SoundID at volume [0-1]
    void PlaySound(SoundID id, float volume = 1.0F);
    
    /// Set the global volume multiplier for sound effects [0-1]
    void SetGlobalVolume(float volume);

private:
    
    ResourceManager& resourceManager_;
    static const int queueSize = 18;
    float globalVolume_ = 0.3F;

    std::queue<sf::Sound> soundQueue_;

    /// Clean up all finished sound players
    void Cleanup();

};

#endif