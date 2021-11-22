#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <utility>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <framework/Resources.hpp>
#include <framework/FileManager.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

/// Framework class for managing and indexing all resources
class ResourceManager {
public:

    /// Construct a ResourceManager, that loads resources with this FileManager
    ResourceManager(const FileManager&);
    
    /// Reference to the Font specified by this FontID
    const sf::Font& GetFont(FontID);
    
    /// Reference to the Sprite specified by this SpriteID    
    const sf::Sprite& GetSprite(SpriteID id);
    
    /// Reference to the Sound specified by this SoundID
    const sf::SoundBuffer& GetSound(SoundID id);

private:

    /// All loaded fonts
    std::unordered_map<FontID, sf::Font> fonts_;

    /// All loaded sounds
    std::unordered_map<SoundID, sf::SoundBuffer> audio_;

    /// All loaded sprites
    std::unordered_map<SpriteID, sf::Sprite> sprites_;

    /// All loaded textures
    std::unordered_map<int, sf::Texture> textures_;


    const FileManager& fileManager_;

    /// If a texture is not found, this will replace it
    sf::Texture missingTexture_;

    /// A mapping from SpriteID => physical area in some texture
    struct SpriteMapping {
        SpriteID spriteID;
        int textureID;
        sf::IntRect rect;
    };

    /// All fonts to load
    static const std::pair<FontID, std::string> fontPaths_[];

    /// All sounds to load
    static const std::pair<SoundID, std::string> audioPaths_[];

    /// All textures to load
    static const std::pair<int, std::string> texturePaths_[];

    /// Mappings for all sprites
    static const SpriteMapping spriteMaps_[];

};

#endif