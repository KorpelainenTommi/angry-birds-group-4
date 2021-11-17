#include <framework/FileManager.hpp>

bool FileManager::LoadTexture(sf::Texture& texture, const std::string& path) const { return texture.loadFromFile(path); }
bool FileManager::LoadAudio(sf::SoundBuffer& soundBuffer, const std::string& path) const { return soundBuffer.loadFromFile(path); }
bool FileManager::LoadFont(sf::Font& font, const std::string& path) const { return font.loadFromFile(path); }