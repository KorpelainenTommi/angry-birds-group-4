#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <utility>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <framework/Resources.hpp>
#include <framework/FileManager.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class ResourceManager {
public:
    ResourceManager(const FileManager&);
    const sf::Font& GetFont(FontID);
    const sf::Sprite& GetSprite(SpriteID id);
    const sf::SoundBuffer& GetSound(SoundID id);

private:

    std::unordered_map<FontID, sf::Font> fonts_;
    std::unordered_map<SoundID, sf::SoundBuffer> audio_;
    std::unordered_map<SpriteID, sf::Sprite> sprites_;
    std::unordered_map<int, sf::Texture> textures_;

    const FileManager& fileManager_;
    sf::Texture missingTexture_;

    struct SpriteMapping {
        SpriteID spriteID;
        int textureID;
        sf::IntRect rect;
    };

    static const std::pair<FontID, std::string> fontPaths_[];
    static const std::pair<SoundID, std::string> audioPaths_[];
    static const std::pair<int, std::string> texturePaths_[];
    static const SpriteMapping spriteMaps_[];


};

#endif