#ifndef RESOURCES_HPP
#define RESOURCES_HPP

/// All sprites usable with RenderSystem
enum SpriteID { 

    nice_face,

    //UI sprites
    ui_button,
    ui_button_pause,
    ui_button_restart,
    ui_button_exit,
    ui_button_resume,
    ui_button_cancel,
    ui_button_ok,
    ui_button_save,
    ui_button_right,
    ui_button_left,
    ui_star,
    ui_missing_star,


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
    
    /*
    wood_blockTri,
    metal_blockTri,
    glass_blockTri,
    plastic_blockTri,
    rubber_blockTri,
    concrete_blockTri,*/

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

    //Block crack overlays
    crack1x1,
    crack2x1,
    crack2x2,
    crack_ball,
    crack_plank,
    crack_thickplank,

    crack1x1_b,
    crack2x1_b,
    crack2x2_b,
    crack_ball_b,
    crack_plank_b,
    crack_thickplank_b,

    //Props
    beer1,
    beer2,
    beer_can1,
    beer_can2,

    sofa3x1,
    tnt,


    //Cannon
    cannon_base,
    cannon_head,


    //Teekkari parts

    //IK
    arm_blue,
    armb_blue,
    torso_blue,
    leg_blue,

    //TEFY
    arm_lwhite,
    armb_lwhite,
    torso_lwhite,
    leg_lwhite,

    //TIK
    arm_black,
    armb_black,
    torso_black,
    leg_black,

    //INKUBIO
    arm_brown,
    armb_brown,
    torso_brown,
    leg_brown,

    //TUTA
    arm_rainbow,
    armb_rainbow,
    torso_rainbow,
    leg_rainbow,

    //SIK
    arm_white,
    armb_white,
    torso_white,
    leg_white,

    //KIK
    arm_pink,
    armb_pink,
    torso_pink,
    leg_pink,

    //Professor
    professor_head,
    professor_torso,
    professor_arm,
    professor_leg,


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

    teekkari_head1s,
    teekkari_head2s,
    teekkari_head3s,
    teekkari_head4s,
    teekkari_head5s,
    teekkari_head6s,
    teekkari_head7s,
    teekkari_head8s,
    teekkari_head9s,
    teekkari_head10s,

    //Fuksi parts

    //IK
    fuksi_arm_blue,
    fuksi_armb_blue,
    fuksi_torso_blue,
    fuksi_leg_blue,

    //TEFY
    fuksi_arm_lwhite,
    fuksi_armb_lwhite,
    fuksi_torso_lwhite,
    fuksi_leg_lwhite,

    //TIK
    fuksi_arm_black,
    fuksi_armb_black,
    fuksi_torso_black,
    fuksi_leg_black,

    //INKUBIO
    fuksi_arm_brown,
    fuksi_armb_brown,
    fuksi_torso_brown,
    fuksi_leg_brown,

    //TUTA
    fuksi_arm_rainbow,
    fuksi_armb_rainbow,
    fuksi_torso_rainbow,
    fuksi_leg_rainbow,

    //SIK
    fuksi_arm_white,
    fuksi_armb_white,
    fuksi_torso_white,
    fuksi_leg_white,

    //KIK
    fuksi_arm_pink,
    fuksi_armb_pink,
    fuksi_torso_pink,
    fuksi_leg_pink,


    //Fuksi heads
    fuksi_head1,
    fuksi_head2,
    fuksi_head3,
    fuksi_head4,
    fuksi_head5,
    fuksi_head6,
    fuksi_head7,
    fuksi_head8,


    //Teekkari abilities
    gravity_symbols,
    cow,
    lightning_strike,
    wrench,
    math_cloud,
    integral_sign,
    
    
    //Block break particles
    particles_dust, //Generic ground hit
    particles_wood,
    particles_metal,
    particles_glass,
    particles_plastic,
    particles_rubber,
    particles_concrete,

    //Prop particles
    bottle_particle,
    can_particle,

    //Object collisions
    hit_sparks1,
    hit_sparks2,

    //Person collisions
    hit_stars,

    //Screen filters (sprite applied after all)
    filter_thunder,
    filter_timefreeze


};

/// All animations usable with RenderSystem
enum AnimationID { 

    //Explosions
    explosion,
    cannon_explosion,

    //Person despawning
    particles_poof,


    //Teekkari abilities
    gravity_flash,
    matrix_bug,
    hand_whirl,
    thunder_sparks


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
    bottle_hit,
    can_hit,
    bottle_break,
    can_break,

    sofa_spring,
    tnt_explode,


    //Cannon sounds
    cannon_load,
    cannon_shot,


    //Teekkari sounds
    poof,
    thud1,
    thud2,
    thud3,

    smack1,
    smack2,
    smack3,

    grunt1,
    grunt2,
    grunt3,
    grunt4,

    teekkari_death1,
    teekkari_death2,
    teekkari_death3,
    teekkari_death4,

    teekkari_recruit,

    
    //Fuksi sounds
    fuksi_cry1,
    fuksi_cry2,
    fuksi_cry3,
    fuksi_cry4,

    fuksi_death1,
    fuksi_death2,
    fuksi_death3,
    fuksi_death4,


    //Teekkari abilities
    gravity_shiftup,
    gravity_shiftdown,
    glitch_sound,
    hand_whoosh,
    wrench_swish,
    cow_moo,
    cow_death,
    thunder_static,
    thunder_strike,
    professor_oneliner,
    integral_destruction



};

/// All fonts usable with RenderSystem
enum FontID { source_serif, consolas, magneto };

#endif