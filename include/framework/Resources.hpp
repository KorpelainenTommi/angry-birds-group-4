#ifndef RESOURCES_HPP
#define RESOURCES_HPP

/// All sprites usable with RenderSystem
enum SpriteID { 

    nice_face,

    //UI sprites
    ui_button,
    ui_star_empty,
    ui_star,


    //Level backgrounds
    background_testroom,
    background_otakaari,
    background_dipoli,
    background_field,


    //Background objects
    terrain,
    bg_tree1,
    bg_tree2,
    bg_lamp_pole,
    bg_bench,
    bg_person1,
    bg_person2,
    bg_person3,


    //Blocks
    wood_block1x1,
    metal_block1x1,
    glass_block1x1,
    plastic_block1x1,
    rubber_block1x1,
    concrete_block1x1,

    wood_block2x1,
    metal_block2x1,
    glass_block2x1,
    plastic_block2x1,
    rubber_block2x1,
    concrete_block2x1,

    wood_block2x2,
    metal_block2x2,
    glass_block2x2,
    plastic_block2x2,
    rubber_block2x2,
    concrete_block2x2,

    wood_ball,
    metal_ball,
    glass_ball,
    plastic_ball,
    rubber_ball,
    concrete_ball,

    wood_blockTri,
    metal_blockTri,
    glass_blockTri,
    plastic_blockTri,
    rubber_blockTri,
    concrete_blockTri,

    wood_plank,
    metal_plank,
    glass_plank,
    plastic_plank,
    rubber_plank,
    concrete_plank,

    wood_thickplank,
    metal_thickplank,
    glass_thickplank,
    plastic_thickplank,
    rubber_thickplank,
    concrete_thickplank,


    //Props
    beer1,
    beer2,
    beer_can1,
    beer_can2,

    sofa2x1,
    tnt,


    //Catapult
    catapult_base,
    catapult_lever,
    catapult_head,


    //Teekkari parts

    //Teemu teekkari
    arm_lgray,
    torso_lgray,
    leg_lgray,

    //TEFY
    arm_lwhite,
    torso_lwhite,
    leg_lwhite,

    //TIK
    arm_black,
    torso_black,
    leg_black,

    //INKUBIO
    arm_brown,
    torso_brown,
    leg_brown,

    //TUTA
    arm_rainbow,
    torso_rainbow,
    leg_rainbow,

    //SIK
    arm_white,
    torso_white,
    leg_white,

    //KIK
    arm_pink,
    torso_pink,
    leg_pink,

    //Professor
    professor_head,
    professor_torso,
    professor_arm,
    professor_leg,

    teekkari_cap,
    teekkari_cap_sik,


    //Teekkari heads
    teekkari_head1,
    teekkari_head2,
    teekkari_head3,
    teekkari_head4,
    teekkari_head5,
    teekkari_head6,
    teekkari_head7,
    teekkari_head8,
    teekkari_head9,
    teekkari_head10,
    teekkari_head11,


    //Fuksi heads
    fuksi_head1,
    fuksi_head2,
    fuksi_head3,
    fuksi_head4,
    fuksi_head5,
    fuksi_head6,
    fuksi_head7,


    //Teekkari abilities
    cow,
    lightning_strike,
    wrench,
    integral_sign,


    //Screen filters (sprite applied after all)
    filter_thunder,
    filter_timefreeze


};

/// All animations usable with
enum AnimationID { 

    //Block break particles
    particles_dust, //Generic ground hit
    partices_wood,
    particles_metal,
    particles_glass,
    particles_plastic,
    particles_rubber,
    particles_concrete,


    //Props
    bottle_crack,
    can_crack,

    explosion,


    //Object collisions
    hit_sparks1,
    hit_sparks2,


    //Fuksi collisions
    hit_stars,
    particles_poof,


    //Teekkari abilities
    gravity_symbols,
    matrix_bug,
    hand_whirl,
    thunder_sparks,
    math_cloud


};

/// All sounds usable with AudioSystem
enum SoundID { 
    

    //UI sounds
    ui_click,
    nice,


    //Block sounds
    wood_hit,
    metal_hit,
    glass_hit,
    plastic_hit,
    rubber_hit,
    concrete_hit,

    wood_crack,
    metal_crack,
    glass_crack,
    plastic_crack,
    rubber_crack,
    concrete_crack,

    
    //Prop sounds
    bottle_break,
    can_break,

    sofa_spring,
    tnt_explode,


    //Catapult sounds
    catapult_click,
    catapult_sling,


    //Teekkari sounds
    thud1,
    thud2,
    thud3,

    grunt1,
    grunt2,

    teekkari_death1,
    teekkari_death2,
    teekkari_death3,
    teekkari_death4,

    teekkari_recruit,

    
    //Fuksi sounds
    fuksi_cry1,
    fuksi_cry2,

    fuksi_death1,
    fuksi_death2,
    fuksi_death3,
    fuksi_death4,


    //Teekkari abilities
    gravity_shift,
    glitch_sound,
    hand_whoosh,
    thunder_static,
    thunder_strike,
    professor_oneliner



};

/// All fonts usable with RenderSystem
enum FontID { source_serif };

#endif