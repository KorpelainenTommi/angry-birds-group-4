#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <framework/Resources.hpp>
#include <framework/FileManager.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class ResourceManager {
public:
    ResourceManager(const FileManager&);
    const sf::Font& GetFont(FontID) const;
    const sf::Sprite& GetSprite(SpriteID id) const;
    const sf::SoundBuffer& GetSound(SoundID id) const;

private:
    //Consider switching from vector to unordered_map?

    std::vector<sf::Font> fonts_;
    std::vector<sf::SoundBuffer> audio_;
    std::vector<sf::Sprite> sprites_;
    std::map<int, sf::Texture> textures_;

    const FileManager& fileManager_;
    sf::Texture missingTexture_;
};

#endif