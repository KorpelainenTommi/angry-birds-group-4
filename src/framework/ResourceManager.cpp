#include <framework/ResourceManager.hpp>
#include <iostream>

const std::pair<FontID, std::string> ResourceManager::fontPaths_[] = {
    {FontID::source_serif, "data/fonts/source_serif.ttf"},
    {FontID::consolas, "data/fonts/consolas.ttf"}
};

const std::pair<SoundID, std::string> ResourceManager::audioPaths_[] = {
    {SoundID::ui_click, "data/audio/ui_click.wav"},
    {SoundID::nice, "data/audio/nice.wav"}
};

const std::pair<int, std::string> ResourceManager::texturePaths_[] = {
    {0, "data/textures/blocks.png"},
    {1, "data/textures/teekkari_bodies.png"},
    {2, "data/textures/teekkari_heads.png"},
    {3, "data/textures/fx.png"},
    {4, "data/textures/buttons.png"},
    {5, "data/textures/stars.png"},
    {6, "data/textures/fuksi_bodies.png"},
    {7, "data/textures/fuksi_heads.png"},
    {8, "data/textures/background0.jpg"},
    {9, "data/textures/ground0.jpg"}
};

const ResourceManager::SpriteMapping ResourceManager::spriteMaps_[] = {

    //Blocks
    {SpriteID::wood_block2x2, 0, {0, 0, 128, 128}},
    {SpriteID::metal_block2x2, 0, {128, 0, 128, 128}},
    {SpriteID::glass_block2x2, 0, {256, 0, 128, 128}},
    {SpriteID::plastic_block2x2, 0, {384, 0, 128, 128}},
    {SpriteID::rubber_block2x2, 0, {512, 0, 128, 128}},
    {SpriteID::concrete_block2x2, 0, {640, 0, 128, 128}},

    {SpriteID::wood_block1x1, 0, {0, 128, 64, 64}},
    {SpriteID::metal_block1x1, 0, {64, 128, 64, 64}},
    {SpriteID::glass_block1x1, 0, {128, 128, 64, 64}},
    {SpriteID::plastic_block1x1, 0, {192, 128, 64, 64}},
    {SpriteID::rubber_block1x1, 0, {256, 128, 64, 64}},
    {SpriteID::concrete_block1x1, 0, {320, 128, 64, 64}},

    {SpriteID::wood_block2x1, 0, {384, 128, 128, 64}},
    {SpriteID::metal_block2x1, 0, {512, 128, 128, 64}},
    {SpriteID::glass_block2x1, 0, {640, 128, 128, 64}},
    {SpriteID::plastic_block2x1, 0, {0, 192, 128, 64}},
    {SpriteID::rubber_block2x1, 0, {128, 192, 128, 64}},
    {SpriteID::concrete_block2x1, 0, {256, 192, 128, 64}},

    {SpriteID::wood_ball, 0, {0, 256, 64, 64}},
    {SpriteID::metal_ball, 0, {64, 256, 64, 64}},
    {SpriteID::glass_ball, 0, {128, 256, 64, 64}},
    {SpriteID::plastic_ball, 0, {192, 256, 64, 64}},
    {SpriteID::rubber_ball, 0, {256, 256, 64, 64}},
    {SpriteID::concrete_ball, 0, {320, 256, 64, 64}},

    {SpriteID::wood_plank, 0, {0, 320, 192, 12}},
    {SpriteID::metal_plank, 0, {192, 320, 192, 12}},
    {SpriteID::glass_plank, 0, {0, 332, 192, 12}},
    {SpriteID::plastic_plank, 0, {192, 332, 192, 12}},
    {SpriteID::rubber_plank, 0, {0, 344, 192, 12}},
    {SpriteID::concrete_plank, 0, {192, 344, 192, 12}},

    {SpriteID::wood_thickplank, 0, {384, 192, 384, 24}},
    {SpriteID::metal_thickplank, 0, {384, 216, 384, 24}},
    {SpriteID::glass_thickplank, 0, {384, 240, 384, 24}},
    {SpriteID::plastic_thickplank, 0, {384, 264, 384, 24}},
    {SpriteID::rubber_thickplank, 0, {384, 288, 384, 24}},
    {SpriteID::concrete_thickplank, 0, {384, 312, 384, 24}},

    {SpriteID::tnt, 0, {0, 356, 64, 64}},
    {SpriteID::sofa3x1, 0, {64, 356, 192, 64}},

    {SpriteID::particles_dust, 0, {0, 420, 32, 32}},
    {SpriteID::particles_wood, 0, {32, 420, 32, 32}},
    {SpriteID::particles_metal, 0, {64, 420, 32, 32}},
    {SpriteID::particles_glass, 0, {96, 420, 32, 32}},
    {SpriteID::particles_plastic, 0, {128, 420, 32, 32}},
    {SpriteID::particles_rubber, 0, {160, 420, 32, 32}},
    {SpriteID::particles_concrete, 0, {192, 420, 32, 32}},

    //Teekkari bodies
    {SpriteID::torso_blue, 1, {0, 0, 130, 156}},
    {SpriteID::torso_white, 1, {130, 0, 130, 156}},
    {SpriteID::torso_lwhite, 1, {260, 0, 130, 156}},
    {SpriteID::torso_rainbow, 1, {390, 0, 130, 156}},
    {SpriteID::torso_black, 1, {520, 0, 130, 156}},
    {SpriteID::torso_brown, 1, {650, 0, 130, 156}},
    {SpriteID::torso_pink, 1, {780, 0, 130, 156}},
    {SpriteID::professor_torso, 1, {910, 0, 130, 156}},

    {SpriteID::arm_blue, 1, {0, 156, 68, 120}},
    {SpriteID::arm_white, 1, {0, 276, 68, 120}},
    {SpriteID::arm_rainbow, 1, {204, 156, 68, 120}},
    {SpriteID::arm_lwhite, 1, {204, 276, 68, 120}},
    {SpriteID::arm_black, 1, {408, 156, 68, 120}},
    {SpriteID::arm_brown, 1, {408, 276, 68, 120}},
    {SpriteID::arm_pink, 1, {612, 156, 68, 120}},
    {SpriteID::professor_arm, 1, {612, 276, 68, 120}},

    {SpriteID::leg_blue, 1, {68, 156, 68, 106}},
    {SpriteID::leg_white, 1, {68, 276, 68, 106}},
    {SpriteID::leg_rainbow, 1, {272, 156, 68, 106}},
    {SpriteID::leg_lwhite, 1, {272, 276, 68, 106}},
    {SpriteID::leg_black, 1, {476, 156, 68, 106}},
    {SpriteID::leg_brown, 1, {476, 276, 68, 106}},
    {SpriteID::leg_pink, 1, {680, 156, 68, 106}},
    {SpriteID::professor_leg, 1, {680, 276, 68, 106}},

    {SpriteID::armb_blue, 1, {136, 156, 68, 120}},
    {SpriteID::armb_white, 1, {136, 276, 68, 120}},
    {SpriteID::armb_rainbow, 1, {340, 156, 68, 120}},
    {SpriteID::armb_lwhite, 1, {340, 276, 68, 120}},
    {SpriteID::armb_black, 1, {544, 156, 68, 120}},
    {SpriteID::armb_brown, 1, {544, 276, 68, 120}},
    {SpriteID::armb_pink, 1, {748, 156, 68, 120}},
    {SpriteID::professor_head, 1, {816, 156, 214, 240}},


    //Teekkari heads
    {SpriteID::teekkari_head1, 2, {0, 0, 214, 240}},
    {SpriteID::teekkari_head2, 2, {214, 0, 214, 240}},
    {SpriteID::teekkari_head3, 2, {428, 0, 214, 240}},
    {SpriteID::teekkari_head4, 2, {642, 0, 214, 240}},
    {SpriteID::teekkari_head5, 2, {856, 0, 214, 240}},
    {SpriteID::teekkari_head6, 2, {0, 240, 214, 240}},
    {SpriteID::teekkari_head7, 2, {214, 240, 214, 240}},
    {SpriteID::teekkari_head8, 2, {428, 240, 214, 240}},
    {SpriteID::teekkari_head9, 2, {642, 240, 214, 240}},
    {SpriteID::teekkari_head10, 2, {856, 240, 214, 240}},

    {SpriteID::teekkari_head1s, 2, {0, 480, 214, 240}},
    {SpriteID::teekkari_head2s, 2, {214, 480, 214, 240}},
    {SpriteID::teekkari_head3s, 2, {428, 480, 214, 240}},
    {SpriteID::teekkari_head4s, 2, {642, 480, 214, 240}},
    {SpriteID::teekkari_head5s, 2, {856, 480, 214, 240}},
    {SpriteID::teekkari_head6s, 2, {0, 720, 214, 240}},
    {SpriteID::teekkari_head7s, 2, {214, 720, 214, 240}},
    {SpriteID::teekkari_head8s, 2, {428, 720, 214, 240}},
    {SpriteID::teekkari_head9s, 2, {642, 720, 214, 240}},
    {SpriteID::teekkari_head10s, 2, {856, 720, 214, 240}},


    //Fuksi bodies
    {SpriteID::fuksi_torso_pink, 6, {0, 0, 130, 156}},
    {SpriteID::fuksi_torso_brown, 6, {130, 0, 130, 156}},
    {SpriteID::fuksi_torso_black, 6, {260, 0, 130, 156}},
    {SpriteID::fuksi_torso_rainbow, 6, {390, 0, 130, 156}},
    {SpriteID::fuksi_torso_lwhite, 6, {520, 0, 130, 156}},
    {SpriteID::fuksi_torso_white, 6, {650, 0, 130, 156}},
    {SpriteID::fuksi_torso_blue, 6, {780, 0, 130, 156}},

    {SpriteID::fuksi_armb_pink, 6, {0, 156, 68, 120}},
    {SpriteID::fuksi_armb_brown, 6, {0, 276, 68, 120}},
    {SpriteID::fuksi_armb_black, 6, {204, 156, 68, 120}},
    {SpriteID::fuksi_armb_lwhite, 6, {204, 276, 68, 120}},
    {SpriteID::fuksi_armb_rainbow, 6, {408, 156, 68, 120}},
    {SpriteID::fuksi_armb_white, 6, {408, 276, 68, 120}},
    {SpriteID::fuksi_armb_blue, 6, {612, 156, 68, 120}},

    {SpriteID::fuksi_leg_pink, 6, {68, 156, 68, 106}},
    {SpriteID::fuksi_leg_brown, 6, {68, 276, 68, 106}},
    {SpriteID::fuksi_leg_black, 6, {272, 156, 68, 106}},
    {SpriteID::fuksi_leg_lwhite, 6, {272, 276, 68, 106}},
    {SpriteID::fuksi_leg_rainbow, 6, {476, 156, 68, 106}},
    {SpriteID::fuksi_leg_white, 6, {476, 276, 68, 106}},
    {SpriteID::fuksi_leg_blue, 6, {680, 156, 68, 106}},

    {SpriteID::fuksi_arm_pink, 6, {136, 156, 68, 120}},
    {SpriteID::fuksi_arm_brown, 6, {136, 276, 68, 120}},
    {SpriteID::fuksi_arm_black, 6, {340, 156, 68, 120}},
    {SpriteID::fuksi_arm_lwhite, 6, {340, 276, 68, 120}},
    {SpriteID::fuksi_arm_rainbow, 6, {544, 156, 68, 120}},
    {SpriteID::fuksi_arm_white, 6, {544, 276, 68, 120}},
    {SpriteID::fuksi_arm_blue, 6, {748, 156, 68, 120}},

    //Fuksi heads
    {SpriteID::fuksi_head1, 7, {0, 0, 214, 240}},
    {SpriteID::fuksi_head2, 7, {214, 0, 214, 240}},
    {SpriteID::fuksi_head3, 7, {428, 0, 214, 240}},
    {SpriteID::fuksi_head4, 7, {642, 0, 214, 240}},
    {SpriteID::fuksi_head5, 7, {0, 240, 214, 240}},
    {SpriteID::fuksi_head6, 7, {214, 240, 214, 240}},
    {SpriteID::fuksi_head7, 7, {428, 240, 214, 240}},
    {SpriteID::fuksi_head8, 7, {642, 240, 214, 240}},

    {SpriteID::ui_button_pause, 4, {0, 0, 127, 127}},
    {SpriteID::ui_button_restart, 4, {128, 0, 127, 127}},
    {SpriteID::ui_button_exit, 4, {256, 0, 127, 127}},
    {SpriteID::ui_button_resume, 4, {384, 0, 127, 127}},
    {SpriteID::ui_button_cancel, 4, {512, 0, 127, 127}},
    {SpriteID::ui_button_ok, 4, {640, 0, 127, 127}},
    {SpriteID::ui_button_save, 4, {768, 0, 127, 127}},

    {SpriteID::ui_star, 5, {0, 0, 256, 256}},
    {SpriteID::ui_missing_star, 5, {257, 0, 256, 256}},
    
    {SpriteID::cannon_base, 0, {0, 654, 214, 114}},
    {SpriteID::cannon_head, 0, {214, 501, 137, 267}},

    {SpriteID::background_field, 8, {0, 0, 1440, 957}},


    {SpriteID::cow, 3, {0, 0, 200, 150}},
    {SpriteID::wrench, 3, {200, 0, 100, 32}}


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
