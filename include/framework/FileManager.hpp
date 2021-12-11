#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <gameplay/Level.hpp>
#include <SFML/Audio/SoundBuffer.hpp>




/// @brief Framework class for loading and saving data
class FileManager {
public:

    /// @brief Load a texture from this path, true if successful, false if not
    bool LoadTexture(sf::Texture& texture, const std::string& path) const;

    /// @brief Load an audio clip from this path, true if successful, false if not
    bool LoadAudio(sf::SoundBuffer& soundBuffer, const std::string& path) const;

    /// @brief Load a font from this path, true if successful, false if not
    bool LoadFont(sf::Font& font, const std::string& path) const;


    /// @brief Return a list of all playable levels
    std::vector<Level> ListLevels() const;

    /// @brief Return a list of levels that can extend an endless game
    std::vector<Level> ListEndless() const;

    /// @brief Save a level. If the level already existed, this will overwrite it
    bool SaveLevel(Level& level) const;

    /// @brief Delete a level
    void DeleteLevel(const Level& level) const;

private:

    const std::string levelPath = "data/levels/";
    const std::string endlessPath = "data/levels/endless/";

    /// Generate a unique filepath for a level file
    std::string GenerateFilepath(const std::string folder) const;

    /// Load a level from this path, true if successful, false if not
    bool LoadLevel(Level& level, const std::string& path) const;
    
    /// Save a level to this path, true if successful, false if not
    bool SaveLevel(const Level& level, const std::string& path) const;

    /// Write a gameobject to output stream
    void PrintGameObjectData(std::ofstream& file, const gm::GameObjectData& data) const;
    
    /// Write a highscore to output stream
    void PrintHighScores(std::ofstream& file, const std::pair<std::string, int>& score) const;

    /// Write a starting teekkari to output stream
    void PrintStartingTeekkaris(std::ofstream& file, const gm::GameObjectType& object) const;

    /// List all level paths from this folder
    std::vector<std::string> ListLevelPaths(std::string folder) const;

    /// Load all levels from folder path
    std::vector<Level> LoadLevels(std::string path) const;
    

};


#endif
