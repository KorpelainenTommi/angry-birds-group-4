#include <framework/ResourceManager.hpp>

ResourceManager::ResourceManager(const FileManager& fileManager) : fileManager_(fileManager) {

    //Create missing texture
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

    //Load physical textures
    if(!fileManager_.LoadTexture(textures_[0], "data/textures/blocks.png")) textures_.erase(0);
    if(!fileManager_.LoadTexture(textures_[1], "data/textures/objects.png")) textures_.erase(1);
    if(!fileManager_.LoadTexture(textures_[2], "data/textures/people.png")) textures_.erase(2);
    if(!fileManager_.LoadTexture(textures_[3], "data/textures/art.png")) textures_.erase(3);
    if(!fileManager_.LoadTexture(textures_[4], "data/textures/ui.png")) textures_.erase(4);

    //Map sprites to textures
    //TODO: eventually replace these with actual mappings, so far everything is automatically assumed missing

    sprites_.push_back(sf::Sprite(missingTexture_, {0, 0, 128, 128}));
    sprites_.push_back(sf::Sprite(missingTexture_, {0, 0, 128, 128}));
    sprites_.push_back(sf::Sprite(missingTexture_, {0, 0, 128, 128}));


    //TODO: rework with filemanager
    sf::Font serif;
    if(fileManager_.LoadFont(serif, "data/fonts/source_serif.ttf")) fonts_.push_back(serif);
    else std::exit(-1);


}


const sf::Font& ResourceManager::GetFont(FontID id) const { return fonts_[id]; }
const sf::SoundBuffer& ResourceManager::GetSound(SoundID id) const { return audio_[id]; }
const sf::Sprite& ResourceManager::GetSprite(SpriteID id) const { return sprites_[id]; }