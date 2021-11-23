#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <gameplay/Level.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


/// Framework class for loading and saving data
class FileManager {
public:

    /// Load a texture from this path, true if successful, false if not
    bool LoadTexture(sf::Texture& texture, const std::string& path) const;

    /// Load an audio clip from this path, true if successful, false if not    
    bool LoadAudio(sf::SoundBuffer& soundBuffer, const std::string& path) const;

    /// Load a font from this path, true if successful, false if not    
    bool LoadFont(sf::Font& font, const std::string& path) const;


    //TODO: Load and Save level are not implemented. Check the Level struct for reference
    /// Load a level from this path, true if successful, false if not
    bool LoadLevel(Level& level, const std::string& path) const { return false; }

    /// Save a level to this path, true if successful, false if not
    bool SaveLevel(const Level& level, const std::string& path) const { return false; }
    
};


#endif