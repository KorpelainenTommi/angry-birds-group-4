#ifndef RESOURCES_HPP
#define RESOURCES_HPP

/// All sprites usable with RenderSystem
enum SpriteID { 

    background_testroom,
    background_otakaari,
    background_dipoli,
    background_field,

    terrain,
    bg_tree1,
    bg_tree2,
    bg_lamp_pole,
    bg_bench,
    bg_person1,
    bg_person2,
    bg_person3,

    wood_block1x1,
    metal_block1x1,
    glass_block1x1,
    plastic_block1x1,
    rubber_block1x1,

    wood_block2x1,
    metal_block2x1,
    glass_block2x1,
    plastic_block2x1,
    rubber_block2x1,

    wood_block2x2,
    metal_block2x2,
    glass_block2x2,
    plastic_block2x2,
    rubber_block2x2,    

    wood_ball,
    metal_ball,
    glass_ball,
    plastic_ball,
    rubber_ball,

    wood_blockTri,
    metal_blockTri,
    glass_blockTri,
    plastic_blockTri,
    rubber_blockTri,

    wood_plank,
    metal_plank,
    glass_plank,
    plastic_plank,
    rubber_plank,

    wood_thickplank,
    metal_thickplank,
    glass_thickplank,
    plastic_thickplank,
    rubber_thickplank,

    beer1,
    beer2,

    sofa2x1,
    tnt,


    arm_lgray,
    torso_lgray,
    leg_lgray,

    teekkari_head1,


    nice_face

};

/// All sounds usable with AudioSystem
enum SoundID { ui_click, nice };

/// All fonts usable with RenderSystem
enum FontID { source_serif };

#endif