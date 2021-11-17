#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <gameplay/Level.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class FileManager {
public:

    bool LoadTexture(sf::Texture& texture, const std::string& path) const;
    bool LoadAudio(sf::SoundBuffer& soundBuffer, const std::string& path) const;
    bool LoadFont(sf::Font& font, const std::string& path) const;

    bool LoadLevel(Level& level, const std::string& path) const { return false; }

    
};


#endif