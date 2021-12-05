#include <framework/ResourceManager.hpp>
#include <iostream>

const std::pair<FontID, std::string> ResourceManager::fontPaths_[] = {
    {FontID::source_serif, "data/fonts/source_serif.ttf"}
};

const std::pair<SoundID, std::string> ResourceManager::audioPaths_[] = {
    {SoundID::ui_click, "data/audio/ui_click.wav"},
    {SoundID::nice, "data/audio/nice.wav"}
};

const std::pair<int, std::string> ResourceManager::texturePaths_[] = {
    {0, "data/textures/blocks.png"},
    {1, "data/textures/teekkari.png"},
    {2, "data/textures/nice.png"},
    {3, "data/textures/background0.jpg"},
    {4, "data/textures/buttons.png"}
};

const ResourceManager::SpriteMapping ResourceManager::spriteMaps_[] = {
    {SpriteID::wood_block1x1, 0, {0, 0, 128, 128}},
    {SpriteID::metal_block1x1, 0, {128, 0, 128, 128}},
    {SpriteID::glass_block1x1, 0, {256, 0, 128, 128}},


    {SpriteID::arm_lgray, 1, {0, 396, 68, 120}},
    {SpriteID::leg_lgray, 1, {68, 396, 68, 106}},
    {SpriteID::torso_lgray, 1, {0, 240, 130, 156}},


    {SpriteID::teekkari_head1, 1, {0, 0, 214, 240}},
    {SpriteID::nice_face, 2, {0, 0, 500, 500}},
    

    {SpriteID::ui_button_pause, 4, {0, 0, 127, 127}},
    {SpriteID::ui_button_restart, 4, {128, 0, 127, 127}},
    {SpriteID::ui_button_exit, 4, {256, 0, 127, 127}},
    {SpriteID::ui_button_resume, 4, {384, 0, 127, 127}},
    {SpriteID::ui_button_cancel, 4, {512, 0, 127, 127}},
    {SpriteID::ui_button_ok, 4, {640, 0, 127, 127}},
    
    {SpriteID::cannon_base, 0, {0, 654, 214, 114}},
    {SpriteID::cannon_head, 0, {214, 501, 137, 267}}

};


ResourceManager::ResourceManager(const FileManager& fileManager) : fileManager_(fileManager) {

    //Create missing texture
    std::cout << "\n-----Loading resources-----" << std::endl;
    missingTexture_.create(32, 32);
    constexpr int N = 32 * 32 * 4;
    sf::Uint8 pixels[N];

    for(int i = 0; i < N; i += 4) {
        bool B = i % (32 * 4) < (16 * 4);
        if(i < N / 2) {
            pixels[  i  ] = B ? 0x0 : 0xFF;
            pixels[i + 1] = 0x0;
            pixels[i + 2] = B ? 0x0 : 0xFF;
            pixels[i + 3] = 0xFF;
        }
        else {
            pixels[  i  ] = B ? 0xFF : 0x0;
            pixels[i + 1] = 0x0;
            pixels[i + 2] = B ? 0xFF : 0x0;
            pixels[i + 3] = 0xFF;
        }
    }

    missingTexture_.update(pixels);
    missingTexture_.setRepeated(true);
    missingTexture_.setSmooth(true);
    std::cout << "  Created missingTexture\n" << std::endl;

    //Load physical textures
    for(const auto& texPath : texturePaths_)
        if(!fileManager_.LoadTexture(textures_[texPath.first], texPath.second)) textures_.erase(texPath.first);
    
    std::cout << "  Textures loaded\n" << std::endl;
    //Load sounds
    for(const auto& aPath : audioPaths_)
        if(!fileManager_.LoadAudio(audio_[aPath.first], aPath.second)) audio_[aPath.first] = sf::SoundBuffer();

    std::cout << "  Audio loaded\n" << std::endl;
    //Load fonts
    for(const auto& fPath : fontPaths_)
        if(!fileManager_.LoadFont(fonts_[fPath.first], fPath.second)) fonts_[fPath.first] = sf::Font();
    
    std::cout << "  Fonts loaded\n" << std::endl;
    //Map textures to sprites
    for(const auto& spMap : spriteMaps_) {
        if(textures_.find(spMap.textureID) != textures_.end())
            sprites_[spMap.spriteID] = sf::Sprite(textures_[spMap.textureID], spMap.rect);
        else sprites_[spMap.spriteID] = sf::Sprite(missingTexture_, {0, 0, 128, 128});
    }

    std::cout << "-----Resource loading done-----\n\n" << std::endl;
}


const sf::Font& ResourceManager::GetFont(FontID id) { return fonts_[id]; }
const sf::SoundBuffer& ResourceManager::GetSound(SoundID id) { return audio_[id]; }
const sf::Sprite& ResourceManager::GetSprite(SpriteID id) { return sprites_[id]; }
