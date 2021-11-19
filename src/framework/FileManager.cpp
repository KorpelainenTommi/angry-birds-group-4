#include <framework/FileManager.hpp>
#include <iostream>

bool FileManager::LoadTexture(sf::Texture& texture, const std::string& path) const {
    std::cout << "  Loading texture: " << path << std::endl;
    return texture.loadFromFile(path);
}

bool FileManager::LoadAudio(sf::SoundBuffer& soundBuffer, const std::string& path) const {
    std::cout << "  Loading audio: " << path << std::endl;
    return soundBuffer.loadFromFile(path);
}

bool FileManager::LoadFont(sf::Font& font, const std::string& path) const {
    std::cout << "  Loading font: " << path << std::endl;    
    return font.loadFromFile(path);
}