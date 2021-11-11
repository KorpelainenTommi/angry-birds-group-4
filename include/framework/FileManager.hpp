#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <gameplay/Level.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class FileManager {
public:

    //TODO: implement these with exception handling
    //NOTE! Do it in a .cpp file please and not here

    bool LoadTexture(sf::Texture& texture, const std::string& path) const { return false; }
    bool LoadAudio(sf::SoundBuffer& soundBuffer, const std::string& path) const { return false; }
    bool LoadFont(sf::Font& font, const std::string& path) const { return font.loadFromFile(path); }

    bool LoadLevel(Level& level, const std::string& path) const { return false; }

    
};


#endif