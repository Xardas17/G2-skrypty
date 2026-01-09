///   													XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///   													XX  G E N E R A T E D    B Y   X A R D A S 1 7   E D I T O R   XX
///   													XX    P F X         V E R S I O N   1.70                       XX
///   													XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
instance spellfx_Gold_armor (CFX_BASE_PROTO)
{
	 visname_s = "ARMOR_GOLD_INIT";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_RightHand";
	 emfxcreate_s = "spellfx_Gold_armor_active";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_armor_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "ZULTY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_armor_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "ARMOR_GOLD";
	 lightrange = 400;
	 sfxid = "MFX_ICECUBE_CAST";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_armor_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_armor_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_armor_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Gold_Plate (CFX_BASE_PROTO)
{
	 visname_s = "ARMOR_Plate_INIT";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_RightHand";
	 emfxcreate_s = "spellfx_Gold_Plate_active";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_Plate_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "NIEBIESKI";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_Plate_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "ARMOR_Plate";
	 lightrange = 400;
	 sfxid = "MFX_ICECUBE_CAST";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_Plate_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_Plate_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Gold_Plate_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_RED_armor (CFX_BASE_PROTO)
{
	 visname_s = "ARMOR_RED_INIT";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_RightHand";
	 emfxcreate_s = "spellfx_RED_armor_active";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_armor_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "CZERWONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_armor_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "ARMOR_RED";
	 lightrange = 400;
	 sfxid = "MFX_ICECUBE_CAST";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_armor_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_armor_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_armor_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance barriere_pc_shoot(cfx_base_proto)
{
	visname_s = "blast";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	sfxid = "mfx_lightning_origin";
};

instance barriere_pc_warning(cfx_base_proto)
{
	emtrjoriginnode = "bip01toe";
	visname_s = "mfx_lightning_target";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0.;
	lightpresetname = "aura";
};

instance beliar_weapon_atak(cfx_base_proto)
{
	visname_s = "beliar_weapon_cast";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
};

instance beliar_weapon_elektyryka(cfx_base_proto)
{
	emtrjoriginnode = "bip01toe";
	visname_s = "beliar_weapon_init";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0.;
	lightpresetname = "aura";
};

instance  black_screen2 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 130";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "blackscreentr";
    	userstring[4]  =  "8";
    	visalphablendfunc_s  =  "BLEND";
};

instance  black_screen3 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 200";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "blackscreentr";
    	userstring[4]  =  "8";
    	visalphablendfunc_s  =  "BLEND";
};

instance  black_screen_10 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  10.0;
};

instance  black_screen_11 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  11.0;
};

instance  black_screen_12 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  12.0;
};

instance  black_screen_13 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  13.0;
};

instance  black_screen_14 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  14.0;
};

instance  black_screen_15 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  15.0;
};

instance  black_screen_3 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  3.0;
};

instance  black_screen_4 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  4.0;
};

instance  black_screen_5 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  5.0;
};

instance  black_screen_6 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  6.0;
};

instance  black_screen_7 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  7.0;
};

instance  black_screen_8 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  8.0;
};

instance  black_screen_9 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  9.0;
};

instance  black_screen_long (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  200000.0;
};

instance blitz_fade_in_slow_out(cfx_base_proto)
{
	visname_s = "screenblend.scx";
	userstring[0] = "5";
	userstring[1] = "0 0 0 255";
	userstring[2] = "0.1";
	visalphablendfunc_s = "BLEND";
	emfxlifespan = 5;
};

instance blueaura(cfx_base_proto)
{
	lightpresetname = "aura";
	visname_s = "mfx_blue_aura";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emfxlifespan = 3;
};

instance  burning_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	emfxcreate_s  =  "fov_morph1";
    	userstring  =  "100000000000";
    	userstring[1]  =  "50 0 0 150";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "screenfx_burning_a0";
    	userstring[4]  =  "8";
    	visalphablendfunc_s  =  "BLEND";
};

instance  confession_dialog (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "1000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "3";
    	userstring[3]  =  "confession_dialog.tga";
    	visalphablendfunc_s  =  "BLEND";
};

instance  confession_startgame (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "1000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "3";
    	userstring[3]  =  "confession_startgame.tga";
    	visalphablendfunc_s  =  "ADD";
    	emfxlifespan  =  10.0;
};

instance  credits_screen (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "5";
    	userstring[1]  =  "credits 1.tga";
    	userstring[2]  =  "5";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  2.0;
};

instance  crystalinvisibility_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	emfxcreate_s  =  "fov_morph1";
    	userstring  =  "100000000000";
    	userstring[1]  =  "200 200 255 180";
    	userstring[2]  =  "1";
    	userstring[3]  =  "screenfx_white_a0";
    	userstring[4]  =  "10";
    	visalphablendfunc_s  =  "BLEND";
    	sfxid  =  "dementhor_talk";
    	sfxisambient  =  1;
};

instance  drunk (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.8";
    	userstring[1]  =  "0.5";
    	emfxtriggerdelay  =  4.0;
    	emfxcreate_s  =  "drunk_child";
    	emtrjoriginnode  =  "bip01";
    	emfxlifespan  =  80.0;
};

instance  drunk_child (cfx_base_proto)
{    	visname_s  =  "morph.fov";
    	userstring  =  "1.5";
    	userstring[1]  =  "0.6";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
    	emfxtriggerdelay  =  2.0;
    	emfxlifespan  =  80.0;
};

instance  fast_time (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "1.3";
    	userstring[1]  =  "1.3";
    	emfxlifespan  =  30.0;
    	emfxtriggerdelay  =  6.0;
    	emfxcreate_s  =  "slow_time_child";
    	emtrjoriginnode  =  "bip01";
};

instance fear_silverwolf(cfx_base_proto)
{
	visname_s = "time.slw";
	userstring[0] = "1";
	userstring[1] = "0.33";
	emfxlifespan = 30;
	emfxtriggerdelay = 6;
	emfxcreate_s = "slow_time_child";
	emtrjoriginnode = "bip01";
};

instance  fov_morph3 (cfx_base_proto)
{    	visname_s  =  "morph.fov";
    	userstring  =  "1.0";
    	userstring[1]  =  "0.5";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
};

instance  fx_bigearthquake (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "5";
    	userstring[2]  =  "10 10 10";
    	sfxid  =  "mfx_earthquake";
};

instance fx_coll_small(cfx_base_proto)
{
	visname_s = "coldummy.3ds";
	emactioncollstat_s = "noresp";
	emactioncolldyn_s = "norespCREATEONCE";
	visalpha = 0;
};

instance fx_coll_small_key_cast(c_particlefxemitkey)
{
	emcheckcollision = 1;
};

instance  fx_earthquake_big (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1500";
    	userstring[1]  =  "7";
    	userstring[2]  =  "7 7 7";
    	sfxid  =  "mfx_earthquake";
    	sfxisambient  =  1;
};

instance  fx_earthquake_small (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "500";
    	userstring[1]  =  "3";
    	userstring[2]  =  "3 3 3";
};

instance fx_electric(cfx_base_proto)
{
	visname_s = "mfx_thunderball_target";
	emtrjoriginnode = "Bip01 Head";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_lightning_target";
	emfxcreate_s = "spellfx_thunderspell_target_child1";
	emfxcreatedowntrj = 1;
};

instance  fx_fassklein_01 (cfx_base_proto)
{    	visname_s  =  "pfx_fassklein";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
};

instance  fx_fireskull_earthquake (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "5";
    	userstring[2]  =  "5 5 5";
    	sfxid  =  "mfx_earthquake";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "spellfx_firestorm_spread";
};

instance  fx_headquake (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "0.3";
    	userstring[2]  =  "10 10 10";
    	emfxlifespan  =  1.0;
};

instance fx_mortus_dead(cfx_base_proto)
{
	emtrjoriginnode = "bip01toe";
	visname_s = "mfx_mortus_dead";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
	sfxisambient = 1;
	emfxlifespan = 10;
};

instance  fx_schild_01 (cfx_base_proto)
{    	visname_s  =  "pfx_schild_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_shield";
};

instance  fx_strongearthquake (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "10";
    	userstring[2]  =  "10 10 10";
    	sfxid  =  "mfx_earthquake";
    	sfxisambient  =  1;
};

instance gfa_destroy_vfx(cfx_base_proto)
{
	visname_s = "gfa_impact";
	emtrjoriginnode = "bip01";
	sfxid = "picklock_broken";
	sfxisambient = 1;
};

instance gfa_trail_inst_vfx(cfx_base_proto)
{
	visname_s = "gfa_trail";
	emtrjoriginnode = "bip01";
	emfxlifespan = 2.0;
};

instance gfa_trail_vfx(cfx_base_proto)
{
	emfxlifespan = 2.0;
};

instance gfa_trail_vfx_key_invest_1(c_particlefxemitkey)
{};

instance gfa_trail_vfx_key_invest_2(c_particlefxemitkey)
{
	visname_s = "gfa_trail";
};

instance gfa_trail_vfx_key_invest_3(c_particlefxemitkey)
{
	visname_s = "";
	pfx_ppsisloopingchg = 1;
};

instance  ghost_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	emfxcreate_s  =  "fov_morph1";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 0";
    	userstring[2]  =  "0";
    	userstring[3]  =  "screenfx_dem_a0";
    	userstring[4]  =  "8";
    	visalphablendfunc_s  =  "BLEND";
    	sfxid  =  "dementhor_talk";
    	sfxisambient  =  1;
};

instance greenlight(cfx_base_proto)
{
	lightpresetname = "aura";
	visname_s = "mfx_segen_1";
	emtrjoriginnode = "bip01";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_fear_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

instance greenlight_amb(cfx_base_proto)
{
	lightpresetname = "aura";
	visname_s = "mfx_segen_1";
	emtrjoriginnode = "bip01";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_fear_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	emfxlifespan = 0.6;
};

instance handfire(cfx_base_proto)
{
	lightpresetname = "redambience";
	visname_s = "mfx_fireball_init";
	emtrjoriginnode = "zs_righthand";
	emactioncolldyn_s = "CREATEONCE";
	emtrjmode_s = "FIXED";
	emfxlifespan = 1;
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 1;
};

instance  hero_gift (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "0.1";
    	userstring[1]  =  "0 128 0 64";
    	userstring[2]  =  "0.1";
    	userstring[3]  =  "";
    	visalphablendfunc_s  =  "ADD";
    	emfxlifespan  =  0.1;
};

instance high_fx(cfx_base_proto)
{
	visname_s = "screenblend.scx";
	emfxtriggerdelay = 6;
	emfxcreate_s = "slow_time_child_kick";
	userstring[0] = "100000000000";
	userstring[1] = "0 0 0 75";
	userstring[2] = "0.5";
	userstring[3] = "screenfx_high_a0";
	userstring[4] = "8";
	visalphablendfunc_s = "BLEND";
	sfxid = "mfx_telekinesis_startinvest";
	sfxisambient = 1;
};

instance  inextremo_lute (cfx_base_proto)
{    	visname_s  =  "inextremo_lutefx";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxid  =  "inextremo_lute";
    	sfxisambient  =  1;
};

instance  infernalfire (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_infernalfire";
    	emfxcreate_s  =  "infernalfire_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
    	emfxlifespan  =  1.0;
};

instance  infernalfire_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_infernalfire";
    	emfxcreate_s  =  "infernalfire_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emfxlifespan  =  1.0;
};

instance  infernalfire_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_infernalfire";
    	emfxcreate_s  =  "infernalfire_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emfxlifespan  =  1.0;
};

instance  infernalfire_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_infernalfire";
    	emfxcreate_s  =  "infernalfire_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emfxlifespan  =  1.0;
};

instance  infernalfire_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_infernalfire";
    	emfxcreate_s  =  "infernalfire_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emfxlifespan  =  1.0;
};

instance  infernalfire_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_infernalfire";
    	emfxcreate_s  =  "infernalfire_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emfxlifespan  =  1.0;
};

instance  infernalfire_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_infernalfire";
    	emfxcreate_s  =  "spellfx_magicfire_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
    	emfxlifespan  =  1.0;
};

instance  kill_special_bullet_effect (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.5";
    	userstring[1]  =  "1.0";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  20.0;
    	emfxtriggerdelay  =  3.0;
};

instance  mark_weapon (cfx_base_proto)
{    	visname_s  =  "irrlicht";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance mod_fx_blitz(cfx_base_proto)
{
	emtrjoriginnode = "Bip01 Head";
	emtrjmode_s = "FIXED";
	emfxcreate_s = "spellfx_thunderspell_target_child1";
	emfxcreatedowntrj = 1;
	visname_s = "blast";
	emtrjdynupdatedelay = 0;
	sfxid = "mfx_lightning_origin";
};

instance mortussummoner(cfx_base_proto)
{
	lightpresetname = "redambience";
	visname_s = "mfx_mortus_summoner";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emfxlifespan = 10;
};

instance  nightsparcles_burst (cfx_base_proto)
{    	visname_s  =  "health_potion";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  nightsparcles_burst_child (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicfire_humansmoke";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  playlute_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	emfxcreate_s  =  "fov_morph1";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 100";
    	userstring[2]  =  "0.5";
    	userstring[4]  =  "8";
    	visalphablendfunc_s  =  "BLEND";
    	sfxid  =  "lute_musicdefault";
    	sfxisambient  =  1;
};

instance pocisk_helmet(cfx_base_proto)
{
	visname_s = "arrrows_belt";
	emtrjoriginnode = "zs_helmet";
};

instance pocisk_leftarm(cfx_base_proto)
{
	visname_s = "arrrows_belt";
	emtrjoriginnode = "zs_leftarm";
};

instance pocisk_lefthand(cfx_base_proto)
{
	visname_s = "arrrows_belt";
	emtrjoriginnode = "zs_lefthand";
};

instance pocisk_longsword(cfx_base_proto)
{
	visname_s = "arrrows_belt";
	emtrjoriginnode = "zs_longsword";
};

instance pocisk_shield(cfx_base_proto)
{
	visname_s = "arrrows_belt";
	emtrjoriginnode = "zs_shield";
};

instance  poisoned_01_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 80";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "screenfx_psn_a0";
    	userstring[4]  =  "5";
    	visalphablendfunc_s  =  "BLEND";
    	sfxisambient  =  1;
};

instance  poisoned_02_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 90";
    	userstring[2]  =  "0.7";
    	userstring[3]  =  "screenfx_psn_a0";
    	userstring[4]  =  "6";
    	visalphablendfunc_s  =  "BLEND";
    	sfxisambient  =  1;
};

instance  poisoned_03_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 100";
    	userstring[2]  =  "0.8";
    	userstring[3]  =  "screenfx_psn_a0";
    	userstring[4]  =  "7";
    	visalphablendfunc_s  =  "BLEND";
    	sfxisambient  =  1;
};

instance  poison_drgtears (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "0 0 0 200";
    	userstring[2]  =  "0.75";
    	userstring[3]  =  "screenfx_dem_a0";
    	userstring[4]  =  "5";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  3.0;
};

instance  poison_fog_noise (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 90";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "screenfx_noise_a0";
    	userstring[4]  =  "5";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  4.0;
    	sfxisambient  =  1;
};

instance  poison_fog_slow (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.8";
    	userstring[1]  =  "0.5";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  5.0;
    	emfxtriggerdelay  =  3.0;
};

instance  poison_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	emfxcreate_s  =  "fov_morph1";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 50 0 150";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "screenfx_poison_a0";
    	userstring[4]  =  "8";
    	visalphablendfunc_s  =  "BLEND";
    	sfxid  =  "mfx_suckenergy_target";
    	sfxisambient  =  1;
};

instance  resident_fx (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	emfxcreate_s  =  "fov_morph1";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 100";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "screenfx_dem_a0";
    	userstring[4]  =  "8";
    	visalphablendfunc_s  =  "BLEND";
};

instance  screenblend_02 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "2";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0.5";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  3.0;
};

instance  screenblend_03 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "3";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "1";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  3.0;
};

instance  screenblend_10 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "4";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  10.0;
};

instance  screenblend_magus_reset (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "1";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  2.0;
};

instance  screenblend_schwarz (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "2";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  7.0;
};

instance  screenblend_sleep_1_1 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "1";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0.5";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  1.0;
};

instance  screenblend_sleep_1_2 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0.5";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  100000.0;
};

instance  screenblend_sleep_2_1 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "0.5";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  1.0;
};

instance  screenblend_sleep_2_2 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "1";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0.5";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  1.0;
};

instance  screenblend_steinzeit (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "1";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  6.0;
};

instance  screenblend_steinzeit_18 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "1";
    	userstring[3]  =  "stargate_blend.tga";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  18.0;
};

instance  screen_sweat (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 100";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "screen_sweat_a0";
    	userstring[4]  =  "4";
    	visalphablendfunc_s  =  "BLEND";
};

instance  screen_sweat1 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 100";
    	userstring[2]  =  "0.5";
    	userstring[3]  =  "screen_sweat_a10";
    	userstring[4]  =  "4";
    	visalphablendfunc_s  =  "BLEND";
};

instance  scr_dark (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "3";
    	visalphablendfunc_s  =  "BLEND";
};

instance  scr_dark_and_light (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "3";
    	emfxlifespan  =  7.0;
    	visalphablendfunc_s  =  "BLEND";
};

instance  scr_hurt (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "1000";
    	userstring[1]  =  "188 41 41 255";
    	userstring[2]  =  "3";
    	visalphablendfunc_s  =  "BLEND";
};

instance short_blitz_fade_in_slow_out(cfx_base_proto)
{
	visname_s = "screenblend.scx";
	userstring[0] = "3";
	userstring[1] = "0 0 0 255";
	userstring[2] = "0.1";
	visalphablendfunc_s = "BLEND";
	emfxlifespan = 3;
};

instance slow_fade_out_in(cfx_base_proto)
{
	visname_s = "screenblend.scx";
	userstring[0] = "7";
	userstring[1] = "0 0 0 255";
	userstring[2] = "3";
	visalphablendfunc_s = "BLEND";
	emfxlifespan = 7;
};

instance  slow_motion_00 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.94";
    	userstring[1]  =  "1.06";
    	emfxlifespan  =  16.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_01 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.94";
    	userstring[1]  =  "1.06";
    	emfxlifespan  =  16.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_02 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.88";
    	userstring[1]  =  "1.12";
    	emfxlifespan  =  17.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_03 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.85";
    	userstring[1]  =  "1.15";
    	emfxlifespan  =  17.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_04 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.82";
    	userstring[1]  =  "1.18";
    	emfxlifespan  =  18.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_05 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.79";
    	userstring[1]  =  "1.21";
    	emfxlifespan  =  18.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_06 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.76";
    	userstring[1]  =  "1.24";
    	emfxlifespan  =  19.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_07 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.73";
    	userstring[1]  =  "1.27";
    	emfxlifespan  =  19.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_08 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.7";
    	userstring[1]  =  "1.3";
    	emfxlifespan  =  20.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_09 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.67";
    	userstring[1]  =  "1.33";
    	emfxlifespan  =  20.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_1 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.7";
    	userstring[1]  =  "0.9";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  15.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_2 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.6";
    	userstring[1]  =  "0.9";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  25.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_3 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.5";
    	userstring[1]  =  "0.9";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  35.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_4 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.4";
    	userstring[1]  =  "0.9";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  48.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_5 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.3";
    	userstring[1]  =  "0.9";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  60.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_6 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.1";
    	userstring[1]  =  "1.0";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  120.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_argezvision (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.2";
    	userstring[1]  =  "1.0";
    	emfxcreate_s  =  "fov_morph3";
    	emfxlifespan  =  150.0;
    	emfxtriggerdelay  =  1.0;
};

instance  slow_motion_augedessturms_01 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.16";
    	userstring[1]  =  "1.0";
    	emfxlifespan  =  0.72;
    	emfxtriggerdelay  =  0.0;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
};

instance  slow_motion_augedessturms_02 (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.16";
    	userstring[1]  =  "1.0";
    	emfxlifespan  =  1.1;
    	emfxtriggerdelay  =  0.0;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
};

instance  slow_motion_black (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.1";
    	userstring[1]  =  "1.0";
    	emfxcreate_s  =  "fov_morph1";
    	emfxlifespan  =  10.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_fun (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.3";
    	userstring[1]  =  "3.5";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  150.0;
    	emfxtriggerdelay  =  1.0;
};

instance  slow_motion_invisibility (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "1.0";
    	userstring[1]  =  "1.15";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  6.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_menu (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.1";
    	userstring[1]  =  "0.1";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  60.0;
    	emfxtriggerdelay  =  0.0;
};

instance  slow_motion_oedland (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.5";
    	userstring[1]  =  "1.0";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  15.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_overlord (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "1.0";
    	userstring[1]  =  "0.1";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  150.0;
    	emfxtriggerdelay  =  3.0;
};

instance  slow_motion_sword (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.5";
    	userstring[1]  =  "1.0";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  15.0;
    	emfxtriggerdelay  =  150.0;
};

instance  slow_motion_zoric (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.7";
    	userstring[1]  =  "1.1";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  15.0;
    	emfxtriggerdelay  =  2.0;
};

instance slow_time_child_kick(cfx_base_proto)
{
	emfxtriggerdelay = 6;
	emfxlifespan = 100000000000;
	visname_s = "morph.fov";
	userstring[0] = "0.8";
	userstring[1] = "1.0";
	userstring[2] = "120";
	userstring[3] = "90";
};

instance  slow_uriziel_motion (cfx_base_proto)
{    	visname_s  =  "time.slw";
    	userstring  =  "0.2";
    	userstring[1]  =  "1.1";
    	emfxcreate_s  =  "fov_morph2";
    	emfxlifespan  =  4.0;
    	emfxtriggerdelay  =  1.0;
};

instance  soj_black_screen (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  5.0;
};

instance  soj_whiteblend (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "255 255 255 130";
    	userstring[2]  =  "0.5";
    	visalphablendfunc_s  =  "BLEND";
};

instance spellfxdragondragonfear_old_wings2(cfx_base_proto)
{
	visname_s = "mfx_dragon_fear_wings2";
	emtrjmode_s = "FIXED";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "bip01";
	emtrjdynupdatedelay = 10000;
	emfxcreate_s = "spellfx_dragon_fear_ground";
};

instance spellfx_acid(cfx_base_proto)
{
	visname_s = "mfx_acid_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcolldyn_s = "spellfx_acid_collidedynfx";
	emfxcolldynperc_s = "vob_acid";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100100";
	userstring[2] = "mul";
};

instance spellfx_ACID_AURA (CFX_BASE_PROTO)
{
	 visname_s = "ACID_AURA_Init";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_ACID_AURA_active";
	 lightpresetname = "DECAL_TELESTORM";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_ACID_AURA_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "Bip01 Footsteps";//bip01
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "DECAL_TELESTORM";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_ACID_AURA_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "ACID_AURA";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_ACID_AURA_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_ACID_AURA_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_ACID_AURA_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_acid_cast1(cfx_base_proto)
{
	visname_s = "mfx_acid_cast1";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 800;
	emselfrotvel_s = "00400";
	emcheckcollision = 2;
	emactioncollstat_s = "collide";
	emactioncolldyn_s = "collide";
	emfxcreate_s = "spellfx_acid_cast2";
};

instance spellfx_acid_cast1_collide(c_particlefxemitkey)
{
	emtrjeasevel = 0.0001;
};

instance spellfx_acid_cast2(cfx_base_proto)
{
	visname_s = "mfx_acid_cast2";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 800;
	emselfrotvel_s = "00400";
	emcheckcollision = 2;
	emactioncollstat_s = "collide";
	emactioncolldyn_s = "collide";
};

instance spellfx_acid_cast2_collide(c_particlefxemitkey)
{
	emtrjeasevel = 0.0001;
};

instance spellfx_acid_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_windfist_collide";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	sfxid = "mfx_acid";
};

instance spellfx_acid_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_acid_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 800;
	emselfrotvel_s = "00400";
	sfxisambient = 1;
	sfxid = "mfx_destroyundead_cast";
	emcreatefxid = "spellfx_acid_cast1";
	emcheckcollision = 1;
};

instance spellfx_acid_key_collide(c_particlefxemitkey)
{
	emtrjeasevel = 1e-006;
};

instance  spellfx_adanosamulett_blue (cfx_base_proto)
{    	visname_s  =  "mfx_adanosamulett_vob_blue";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	emfxlifespan  =  4.0;
};

instance  spellfx_adanosamulett_red (cfx_base_proto)
{    	visname_s  =  "mfx_adanosamulett_vob_red";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	emfxlifespan  =  4.0;
};

instance  spellfx_adanosamulett_violet (cfx_base_proto)
{    	visname_s  =  "mfx_adanosamulett_vob_violet";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	emfxlifespan  =  4.0;
};

instance  spellfx_adanosamulett_yellow (cfx_base_proto)
{    	visname_s  =  "mfx_adanosamulett_vob_white";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	emfxlifespan  =  4.0;
};

instance spellfx_adanosball(cfx_base_proto)
{
	visname_s = "mfx_adanosball_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collide";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcolldyn_s = "spellfx_adanosball_target";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	lightpresetname = "aura";
};

instance spellfx_adanosball_key_back(c_particlefxemitkey)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
};

instance spellfx_adanosball_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_adanosball_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 900;
	sfxid = "mfx_thunderball_collide3";
	lightrange = 100;
	emcheckcollision = 1;
};

instance spellfx_adanosball_key_collide(c_particlefxemitkey)
{
	emtrjeasevel = 1e-006;
};

instance spellfx_adanosball_key_init(c_particlefxemitkey)
{
	lightrange = 0.001;
};

instance spellfx_adanosball_key_invest(c_particlefxemitkey)
{
	lightrange = 100;
};

instance spellfx_adanosball_target(cfx_base_proto)
{
	visname_s = "mfx_adanosball_target";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	sendassessmagic = 1;
	sfxid = "mfx_lightning_origin";
	sfxisambient = 1;
};

instance  spellfx_adanosbaptise (cfx_base_proto)
{    	visname_s  =  "mfx_adanosbaptise";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_adanosprojectile (cfx_base_proto)
{    	visname_s  =  "mfx_adanosprojectile_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_adanosprojectile_collide";
    	emfxcolldyn_s  =  "spellfx_adanosprojectile_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_adanosprojectile_collide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_adanosprojectile_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_destroyundead_collide";
    	sfxisambient  =  1;
};

instance  spellfx_adanosprojectile_collidedynfx (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_adanosprojectile_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_destroyundead_collide";
    	sfxisambient  =  1;
};

instance  spellfx_adanosprojectile_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	sfxid  =  "mfx_destroyundead_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_adanosprojectile_key_init (c_particlefxemitkey)
{};

instance  spellfx_adanosprojectile_trail (cfx_base_proto)
{    	emtrjeasevel  =  800.0;
    	visname_s  =  "mfx_adanosprojectile_trail";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emcheckcollision  =  1;
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide";
};

instance  spellfx_adanosprojectile_trail_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_adanosrage (cfx_base_proto)
{    	visname_s  =  "mfx_adanosrage_flash";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_adanosrage_target_cloud";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_barriere_shoot";
    	sfxisambient  =  1;
};

instance  spellfx_adanosrage_target_cloud (cfx_base_proto)
{    	visname_s  =  "mfx_adanosrage_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_adanoswave (cfx_base_proto)
{    	visname_s  =  "mfx_adanoswave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_adanoswave_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_adanoswave_target";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_massdeath_target";
};

instance  spellfx_adanoswave_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_adanoswave_explosion";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_adanoswave_ground";
};

instance  spellfx_adanoswave_ground (cfx_base_proto)
{    	visname_s  =  "mfx_adanoswave_cast";
    	emtrjoriginnode  =  "bip01 r foot";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_adanoswave_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_adanoswave_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_massdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_adanoswave_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_adanoswave_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_adanoswave_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_adanoswave_init";
};

instance  spellfx_adanoswave_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_adanoswave_righthand";
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_adanoswave_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_adanoswave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  5.0;
    	visalpha  =  1.0;
};

instance  spellfx_adanoswave_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_adanoswave_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_adanoszorn (cfx_base_proto)
{    	visname_s  =  "mfx_adanoszorn_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_adanoszorn_collidedynfx";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "aura";
};

instance  spellfx_adanoszorn_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_waterball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_adanoszorn_collide";
    	emfxcreate_s  =  "spellfx_adanoszorn_target";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_adanoszorn_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	visname_s  =  "mfx_adanoszorn_pfxtrail";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_suckenergy_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_adanoszorn_trail";
    	emcheckcollision  =  1;
};

instance  spellfx_adanoszorn_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "fsb_attack";
};

instance  spellfx_adanoszorn_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_adanoszorn_init";
    	lightrange  =  0.01;
};

instance  spellfx_adanoszorn_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_adanoszorn_target (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_adanoszorn_spread";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_adanoszorn_sphere";
    	sfxisambient  =  1;
};

instance  spellfx_adanoszorn_trail (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_adanoszorn_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emselfrotvel_s  =  "0 0 200";
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_adanoszorn_trail_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_adanos_amulet_perm (cfx_base_proto)
{    	visname_s  =  "mfx_adanos_amulet_perm_pfx";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 neck";
    	emfxlifespan  =  -1.0;
};

instance  spellfx_altern (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "pingpong_once";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_suckenergy_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_suckenergy_invest";
};

instance  spellfx_altern_bloodfly (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_flytoplayer";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_altern_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_altern_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_altern_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_altern_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_altern_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_altern_slowtime (cfx_base_proto)
{    	emfxtriggerdelay  =  6.0;
    	emfxlifespan  =  30.0;
    	visname_s  =  "morph.fov";
    	userstring  =  "0.8";
    	userstring[1]  =  "1.0";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
};

instance  spellfx_arcaneball (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_00 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_00_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_00_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_00_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_00_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_00_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_00";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_00_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_00_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_00_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_01 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_01_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_01_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_01_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_01_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_01_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_01";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_01_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_01_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_01_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_02 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_02_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_02_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_02_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_02_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_02_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_02";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_02_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_02_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_02_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_03 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_03_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_03_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_03_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_03_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_03_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_03";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_03_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_03_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_03_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_04 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_04_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_04_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_04_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_04_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_04_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_04";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_04_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_04_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_04_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_05 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_05_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_05_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_05_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_05_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_05_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_05";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_05_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_05_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_05_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_06 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_06_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_06_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_06_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_06_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_06_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_06";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_06_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_06_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_06_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_07 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_07_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_07_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_07_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_07_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_07_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_07";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_07_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_07_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_07_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_08 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_08_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_08_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_08_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_08_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_08_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_08";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_08_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_08_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_08_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_09 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_09_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_09_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_09_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_09_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_09_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_09";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_09_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_09_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_09_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcaneball_realproj";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneball_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcaneball_init";
    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_arcaneball_realproj (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_cast_00";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  4.0;
    	emtrjangleheadvar  =  8.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  1000.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneball_target";
    	emfxcollstat_s  =  "spellfx_arcaneball_target";
    	emfxcolldynperc_s  =  "spellfx_arcaneball_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_arcaneball_realproj_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_massdeath_cast";
};

instance  spellfx_arcaneball_realproj_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arcaneball_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_arcaneball_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_arcaneball_target (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanecharge (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_projectile";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanecharge_collide";
    	emfxcolldyn_s  =  "spellfx_arcanecharge_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcanecharge_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanechargeprojectile01 (cfx_base_proto)
{    	visname_s  =  "mfx_palholybolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_palholybolt_collide";
    	emfxcolldyn_s  =  "spellfx_palholybolt_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanechargeprojectile01_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcanecharge_01";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  600.0;
    	sfxid  =  "mfx_thunderbolt_cast";
    	emcheckcollision  =  1;
};

instance  spellfx_arcanechargeprojectile01_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanechargeprojectile01_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_palholybolt_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanechargewithtrail (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_projectile_withtrail";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanechargewithtrail_collide";
    	emfxcolldyn_s  =  "spellfx_arcanechargewithtrail_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcanechargewithtrail_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanechargewithtrail_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanechargewithtrail_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanechargewithtrail_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanechargewithtrail_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcanecharge_projectile_withtrail";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanechargewithtrail_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_projectile_withtrail";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  3;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  2.0;
    	emtrjangleheadvar  =  4.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emfxcolldynperc_s  =  "spellfx_arcanechargewithtrail_sendperception";
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanechargewithtrail_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanechargewithtrail_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_arcanecharge_01 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanecharge_02 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanecharge_03 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanecharge_04 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanecharge_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanecharge_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanecharge_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanecharge_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcanecharge_projectile";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanecharge_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_projectile";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  3;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  2.0;
    	emtrjangleheadvar  =  4.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emfxcolldynperc_s  =  "spellfx_arcanecharge_sendperception";
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanecharge_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanecharge_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_arcanecharge_vob (cfx_base_proto)
{    	visname_s  =  "mfx_arcanecharge_vob";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcaneexplosion (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_00 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_00_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_00";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_00_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_00_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_00_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_00_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_00";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_00_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_00_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_00";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_01 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_01_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_01";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_01_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_01_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_01_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_01_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_01";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_01_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_01_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_02 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_02_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_02";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_02_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_02_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_02_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_02_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_02";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_02_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_02_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_02";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_03 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_03_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_03";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_03_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_03_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_03_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_03_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_03";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_03_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_03_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_03";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_04 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_04_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_04";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_04_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_04_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_04_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_04_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_04";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_04_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_04_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_04";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_05 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_05_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_05";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_05_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_05_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_05_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_05_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_05";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_05_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_05_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_05";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_06 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_06_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_06";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_06_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_06_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_06_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_06_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_06";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_06_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_06_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_06";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_07 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_07_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_07";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_07_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_07_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_07_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_07_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_07";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_07_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_07_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_07";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_08 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_08_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_08";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_08_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_08_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_08_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_08_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_08";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_08_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_08_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_08";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_09 (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_arcaneexplosion_09_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle_09";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_09_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_09_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_09_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_09_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere_09";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_09_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_09_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2_09";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_cast (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_sphere";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_arcaneexplosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arcaneexplosion_sendperception";
    	emcheckcollision  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_circle (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_circle";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_target";
    	sfxid  =  "arcane_missiles_1";
};

instance  spellfx_arcaneexplosion_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_init";
    	emcreatefxid  =  "spellfx_arcaneexplosion_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcaneexplosion_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.2;
    	visalpha  =  1.0;
};

instance  spellfx_arcaneexplosion_righthand_short (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  0.7;
    	visalpha  =  1.0;
};

instance  spellfx_arcaneexplosion_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_arcaneexplosion_sphere (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere";
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_arcaneexplosion_sphere2";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcaneexplosion_sphere2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcaneexplosion_sphere2";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  1.5;
};

instance  spellfx_arcanehit (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanehit_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_arcanehit_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_arcanehit_righthand_symbol (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_symbol_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  0.6;
    	visalpha  =  1.0;
};

instance  spellfx_arcanehit_symbol (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_symbol";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  0.3;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_arcanehit_target (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_00 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_00";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_01 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_02 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_02";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_03 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_03";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_04 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_04";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_05 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_05";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_06 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_06";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_07 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_07";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_08 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_08";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanehit_target_09 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanehit_explosion_09";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 head";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
};

instance  spellfx_arcanemissiles (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissiles2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissiles2head (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissiles2head_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissiles2head_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissiles2head_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissiles2head_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissiles2head_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast2";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissiles2head_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissiles2lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissiles2lefthand_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissiles2lefthand_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissiles2lefthand_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissiles2lefthand_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissiles2lefthand_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast2";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  7.0;
    	emtrjangleheadvar  =  12.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissiles2lefthand_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissiles2_collide (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_arcanemissiles2_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_arcanemissiles2_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissiles2_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissiles2_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissiles2_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissiles2_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast2";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissiles2_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_00 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_00_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_00_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_00_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_00_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_00_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_00";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_00_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_01 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_01_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_01_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_01_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_01_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_01_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_01";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_01_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_02 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_02_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_02_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_02_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_02_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_02_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_02";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_02_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_03 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_03_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_03_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_03_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_03_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_03_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_03";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_03_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_04 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_04_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_04_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_04_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_04_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_04_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_04";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_04_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_05 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_05_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_05_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_05_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_05_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_05_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_05";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_05_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_06 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_06_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_06_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_06_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_06_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_06_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_06";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_06_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_07 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_07_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_07_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_07_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_07_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_07_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_07";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_07_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_08 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_08_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_08_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_08_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_08_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_08_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_08";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_08_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_09 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileshead_09_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_09_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_09_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_09_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_09_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast_09";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_09_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileshead_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileshead_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileshead_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileshead_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileshead_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  12.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileshead_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissileslefthand (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arcanemissiles_collide";
    	emfxcolldyn_s  =  "spellfx_arcanemissiles_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arcanemissileslefthand_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissileslefthand_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissileslefthand_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissileslefthand_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissileslefthand_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  12.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissileslefthand_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissiles_collide (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_arcanemissiles_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_arcanemissiles_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_arcanemissiles_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_arcanemissiles_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_arcanemissiles_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_arcanemissiles_missile (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  12.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_arcanemissiles_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_arcanemissilevob_01 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanemissilevob_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanemissilevob_02 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanemissilevob_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanemissilevob_03 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanemissilevob_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_arcanemissilevob_04 (cfx_base_proto)
{    	visname_s  =  "mfx_arcanemissilevob_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
};

instance spellfx_arena(cfx_base_proto)
{
	visname_s = "mfx_thunderball_init";
	vissize_s = "11";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 0.;
	emtrjtargetrange = 440;
	emtrjtargetelev = 0;
	emfxinvesttarget_s = "spellfx_arena_target";
	emfxinvestorigin_s = "spellfx_arena_bridge";
};

instance spellfx_arena_bridge(cfx_base_proto)
{
	visname_s = "mfx_arena_bridge";
	emtrjmode_s = "targetline";
	emtrjoriginnode = "Bip01 Head";
	emtrjtargetnode = "Bip01 Head";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
	emfxcreate_s = "spellfx_arena_origin";
	sfxid = "watherrain";
	sfxisambient = 1;
};

instance spellfx_arena_bridge_key_init(c_particlefxemitkey)
{
	emtrjeasevel = 0.01;
};

instance spellfx_arena_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
	sfxid = "watherrain";
	sfxisambient = 1;
};

instance spellfx_arena_key_invest_1(c_particlefxemitkey)
{
	visname_s = "simpleglow.tga";
	sfxid = "watherrain";
	sfxisambient = 1;
};

instance spellfx_arena_target(cfx_base_proto)
{
	visname_s = "mfx_arena";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
	sendassessmagic = 1;
};

instance  spellfx_argezvision (cfx_base_proto)
{    	visname_s  =  "mfx_argezvision_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_argezvision_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_argezvision_cast (cfx_base_proto)
{    	visname_s  =  "mfx_argezvision_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_argezvision_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  1.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_argezvision_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_argezvision_invest (cfx_base_proto)
{    	visname_s  =  "mfx_argezvision_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_argezvision_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_argezvision_cast";
};

instance  spellfx_argezvision_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_argezvision_target (cfx_base_proto)
{    	visname_s  =  "mfx_argezvision_collide";
    	sfxid  =  "mfx_breathofdeath_target";
    	sfxisambient  =  1;
};

instance  spellfx_arkanemissiles (cfx_base_proto)
{    	visname_s  =  "mfx_arkanemissiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arkanemissiles_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  0;
    	visname_s  =  "";
};

instance  spellfx_arkanemissiles_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_arkanemissiles_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_arkanemissiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  3.0;
    	visalpha  =  1.0;
};

instance  spellfx_arkanemissiles_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_arkanemissiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  3.0;
    	visalpha  =  1.0;
};

instance  spellfx_arkmisinvisprojectile (cfx_base_proto)
{    	visname_s  =  "mfx_arkmisinvis_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_arkmisinvisprojectile_collidefx";
    	emfxcolldyn_s  =  "spellfx_arkmisinvisprojectile_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_arkmisinvisprojectile_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_arkmisinvisprojectile_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_arkmisinvis_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_arkmisinvisprojectile_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_arkmisinvis_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_arkmisinvisprojectile_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_arkmisinvis_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1300.0;
    	emcheckcollision  =  1;
};

instance  spellfx_arkmisinvisprojectile_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_arkmisinvisprojectile_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arkmisinvis_init";
};

instance  spellfx_arkmisinvisprojectile_key_open (c_particlefxemitkey)
{};

instance  spellfx_armor (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_armor_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "sfx_innoseye";
    	sfxisambient  =  1;
};

instance  spellfx_armor_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_armor_lefthand";
};

instance  spellfx_armor_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_armor_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_armor_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_armor_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_armourpiercingarrow (cfx_base_proto)
{    	visname_s  =  "armourpiercing_arrow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_armourpiercingarrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_armourpiercingarrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_armourpiercingarrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance spellfx_armre(cfx_base_proto)
{
	visname_s = "armore";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "aura";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "campfire1";
};

instance  spellfx_armyofbeliar (cfx_base_proto)
{    	visname_s  =  "mfx_massdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_armyofbeliar_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_massdeath_target";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_massdeath_target";
};

instance  spellfx_armyofbeliar_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_massdeath_explosion";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_armyofbeliar_ground";
};

instance  spellfx_armyofbeliar_ground (cfx_base_proto)
{    	visname_s  =  "mfx_massdeath_cast";
    	emtrjoriginnode  =  "bip01 r foot";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_armyofbeliar_collidedynfx";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_massdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_armyofbeliar_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_armyofbeliar_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_armyofbeliar_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_massdeath_init";
};

instance  spellfx_armyofbeliar_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_massdeath_righthand";
    	emcreatefxid  =  "spellfx_armyofbeliar_lefthand";
};

instance  spellfx_armyofbeliar_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_massdeath_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_armyofbeliar_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance spellfx_armyofdarkness_key_invest_2(c_particlefxemitkey)
{};

instance spellfx_armyofdarkness_key_invest_3(c_particlefxemitkey)
{	emcreatefxid = "fx_earthquake";};

instance  spellfx_armyofdarkness_origin (cfx_base_proto)
{    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_army_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_arrow2 (cfx_base_proto)
{    	visname_s  =  "magic_arrow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "aura";
};

instance  spellfx_arrow2_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_arrow2_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  300.0;
};

instance  spellfx_arrow2_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  400.0;
};

instance  spellfx_arrow_green (cfx_base_proto)
{    	visname_s  =  "magic_arrow_green";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "aura";
};

instance  spellfx_arrow_green_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_arrow_green_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  300.0;
};

instance  spellfx_arrow_green_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  400.0;
};

instance spellfx_atak(cfx_base_proto)
{
	visname_s = "mfx_atak_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_atak_initglow";
	emfxcreatedowntrj = 0;
	sfxid = "mfx_beliarweap";
};

instance spellfx_atak_ground(cfx_base_proto)
{
	visname_s = "mfx_atak_cast";
	emtrjoriginnode = "bip01rfoot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "redambience";
	sfxid = "mfx_atak_cast";
	sfxisambient = 1;
};

instance spellfx_atak_initglow(cfx_base_proto)
{
	visname_s = "mfx_atak_init_glow";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	lightpresetname = "redambience";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_atak_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_atak_ground";
	pfx_ppsisloopingchg = 1;
	sfxid = "mfx_firerain_rain";
};

instance spellfx_atak_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_atak_init";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_atak_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
	sfxid = "mfx_firerain_rain";
};

instance  spellfx_athunderstorm_screenblend (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "0.1";
    	userstring[1]  =  "255 255 255 255";
    	userstring[2]  =  "0.25";
    	emfxlifespan  =  0.1;
};

instance  spellfx_augedessturms_start (cfx_base_proto)
{    	visname_s  =  "mfx_augedessturms_start";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_auraberserker (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_auraberserker_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_auraberserker_origin";
};

instance  spellfx_auraberserker_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_auraberserker_lefthand";
};

instance  spellfx_auraberserker_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_auraberserker_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_auraberserker_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_auraberserker_origin (cfx_base_proto)
{    	visname_s  =  "mfx_heal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_auradesstehlens (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_auradesstehlens_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_auradesstehlens_origin";
};

instance  spellfx_auradesstehlens_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_auradesstehlens_lefthand";
};

instance  spellfx_auradesstehlens_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_auradesstehlens_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_auradesstehlens_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_auradesstehlens_origin (cfx_base_proto)
{    	visname_s  =  "mfx_heal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_aurafeuer (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_aurafeuer_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_aurafeuer_origin";
};

instance  spellfx_aurafeuer_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_aurafeuer_lefthand";
};

instance  spellfx_aurafeuer_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_aurafeuer_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_aurafeuer_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_aurafeuer_origin (cfx_base_proto)
{    	visname_s  =  "mfx_heal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_auraflammen (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_auraflammen_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_auraflammen_origin";
};

instance  spellfx_auraflammen_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_auraflammen_lefthand";
};

instance  spellfx_auraflammen_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_auraflammen_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_auraflammen_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_auraflammen_origin (cfx_base_proto)
{    	visname_s  =  "mfx_heal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_aurafrost (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_aurafrost_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_aurafrost_origin";
};

instance  spellfx_aurafrost_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_aurafrost_lefthand";
};

instance  spellfx_aurafrost_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_aurafrost_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_aurafrost_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_aurafrost_origin (cfx_base_proto)
{    	visname_s  =  "mfx_heal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_auraheilung (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_auraheilung_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_auraheilung_origin";
};

instance  spellfx_auraheilung_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_auraheilung_lefthand";
};

instance  spellfx_auraheilung_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_auraheilung_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_auraheilung_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_auraheilung_origin (cfx_base_proto)
{    	visname_s  =  "mfx_heal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_baneling_die (cfx_base_proto)
{    	visname_s  =  "swampdrone_explode_baneling";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "BLEND";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_barrierewarning (cfx_base_proto)
{    	visname_s  =  "barrierewarning_box_new";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  0;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
};

instance  spellfx_beeinflussung (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_beeinflussung_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_beeinflussung_origin";
};

instance  spellfx_beeinflussung_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_beeinflussung_lefthand";
};

instance  spellfx_beeinflussung_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_beeinflussung_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_beeinflussung_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_beeinflussung_origin (cfx_base_proto)
{    	visname_s  =  "mfx_heal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_beliarcity (cfx_base_proto)
{    	visname_s  =  "mfx_pallight_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_beliarcity_active";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_beliarcity_active (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
    	lightpresetname  =  "aura";
};

instance  spellfx_beliarcity_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_pallight_origin";
    	lightrange  =  1000.0;
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_beliarcity_active_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_beliarcity_active_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_beliarcity_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_beliardebuff (cfx_base_proto)
{    	visname_s  =  "beliardebuff";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_beliarheadbase (cfx_base_proto)
{    	visname_s  =  "mfx_skull_beliarbase";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_helmet";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_beliarheadeyes (cfx_base_proto)
{    	visname_s  =  "mfx_skull_beliareyes";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_helmet";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_beliarheadjaw1 (cfx_base_proto)
{    	visname_s  =  "mfx_skull_beliarjaw1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_helmet";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_beliarheadjaw2 (cfx_base_proto)
{    	visname_s  =  "mfx_skull_beliarjaw2";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_helmet";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_beliarheadjaw3 (cfx_base_proto)
{    	visname_s  =  "mfx_skull_beliarjaw3";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_helmet";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_beliarheadjaw4 (cfx_base_proto)
{    	visname_s  =  "mfx_skull_beliarjaw4";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_helmet";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_beliarheadjaw5 (cfx_base_proto)
{    	visname_s  =  "mfx_skull_beliarjaw5";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_helmet";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_beliarheal (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "pingpong_once";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_suckenergy_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_suckenergy_invest";
};

instance  spellfx_beliarheal_bloodfly (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_flytoplayer";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_beliarheal_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_beliarheal_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_beliarheal_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_beliarheal_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_beliarheal_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_target";
    	sendassessmagic  =  1;
};

instance  spellfx_beliarheal_slowtime (cfx_base_proto)
{    	emfxtriggerdelay  =  6.0;
    	emfxlifespan  =  30.0;
    	visname_s  =  "morph.fov";
    	userstring  =  "0.8";
    	userstring[1]  =  "1.0";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
};

instance spellfx_beliars(cfx_base_proto)
{
	visname_s = "mfx_lightning_origin";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collideCREATEONCEcreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_beliars_spread";
	emfxcolldyn_s = "spellfx_beliars_spread";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellfx_beliars_investsound";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100100";
	userstring[2] = "mul";
	lightpresetname = "firesmall";
};

instance  spellfx_beliarsrage_collide_01 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_collide4";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_lightning_dummy";
    	sfxisambient  =  1;
};

instance  spellfx_beliarsrage_collide_02 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_collide5";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_lightning_dummy";
    	sfxisambient  =  1;
};

instance  spellfx_beliarsrage_collide_curse (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_beliarweap_quiet";
    	sfxisambient  =  1;
};

instance  spellfx_beliarsrage_curse (cfx_base_proto)
{    	visname_s  =  "mfx_beliarsrage_flash";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_beliarsrage_target_cloud";
    	lightpresetname  =  "justwhite";
    	sfxid  =  "mfx_barriere_shoot_quiet";
    	sfxisambient  =  1;
};

instance  spellfx_beliarsrage_perm (cfx_base_proto)
{    	visname_s  =  "mfx_beliarsrage_flash_perm";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_beliarsrage_target_cloud";
    	lightpresetname  =  "justwhite";
    	sfxid  =  "mfx_barriere_shoot";
    	sfxisambient  =  1;
};

instance  spellfx_beliarsrage_yellow (cfx_base_proto)
{    	visname_s  =  "mfx_beliarsrage_flash_yellow";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "justwhite";
    	sfxid  =  "mfx_barriere_shoot";
    	sfxisambient  =  1;
};

instance spellfx_beliars_collide(cfx_base_proto)
{
	visname_s = "mfx_fireball_collide3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sfxid = "mfx_fireball_collide3";
};

instance spellfx_beliars_investblast1(cfx_base_proto)
{
	visname_s = "mfx_lightning_origin";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest1";
	sfxisambient = 1;
};

instance spellfx_beliars_investblast2(cfx_base_proto)
{
	visname_s = "mfx_lightning_origin";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest2";
	sfxisambient = 1;
};

instance spellfx_beliars_investblast3(cfx_base_proto)
{
	visname_s = "mfx_lightning_origin";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest3";
	sfxisambient = 1;
};

instance spellfx_beliars_investblast4(cfx_base_proto)
{
	visname_s = "mfx_lightning_origin";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest4";
	sfxisambient = 1;
};

instance spellfx_beliars_investsound(cfx_base_proto)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "mfx_beliars_invest";
	sfxisambient = 1;
};

instance spellfx_beliars_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_heavensrage_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400.;
	sfxid = "mfx_beliars_cast";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 200;
};

instance spellfx_beliars_key_collide(c_particlefxemitkey)
{
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 0.000001;
};

instance spellfx_beliars_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_beliars_init";
	lightrange = 0.01;
};

instance spellfx_beliars_key_invest_1(c_particlefxemitkey)
{	lightrange = 100;	emcreatefxid = "spellfx_beliars_investblast1";};

instance spellfx_beliars_key_invest_2(c_particlefxemitkey)
{	lightrange = 200;	emcreatefxid = "spellfx_beliars_investblast2";};

instance spellfx_beliars_key_invest_3(c_particlefxemitkey)
{	lightrange = 300;	emcreatefxid = "spellfx_beliars_investblast3";};

instance spellfx_beliars_key_invest_4(c_particlefxemitkey)
{	lightrange = 400;	emcreatefxid = "spellfx_beliars_investblast4";};

instance spellfx_beliars_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_beliars_spread(cfx_base_proto)
{
	visname_s = "mfx_beliars_spread";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "createcreatequad";
	emactioncolldyn_s = "CREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	lightpresetname = "firesmall";
	visname_s = "mfx_xardas_cast";
	emfxcreate_s = "spellfx_xardas";
	sfxisambient = 1;
};

instance spellfx_beliars_storm(cfx_base_proto)
{
	visname_s = "mfx_beliars_storm_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collideCREATEONCEcreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_beliars_storm_spread";
	emfxcolldyn_s = "spellfx_beliars_storm_spread";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellfx_beliars_storm_investsound";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100100";
	userstring[2] = "mul";
	lightpresetname = "firesmall";
};

instance spellfx_beliars_storm_collide(cfx_base_proto)
{
	visname_s = "mfx_fireball_collide3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sfxid = "mfx_fireball_collide3";
};

instance spellfx_beliars_storm_investblast1(cfx_base_proto)
{
	visname_s = "mfx_beliars_storm_investblast1";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest1";
	sfxisambient = 1;
};

instance spellfx_beliars_storm_investblast2(cfx_base_proto)
{
	visname_s = "mfx_beliars_storm_investblast2";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest2";
	sfxisambient = 1;
};

instance spellfx_beliars_storm_investblast3(cfx_base_proto)
{
	visname_s = "mfx_beliars_storm_investblast3";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest3";
	sfxisambient = 1;
};

instance spellfx_beliars_storm_investblast4(cfx_base_proto)
{
	visname_s = "mfx_beliars_storm_investblast4";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest4";
	sfxisambient = 1;
};

instance spellfx_beliars_storm_investsound(cfx_base_proto)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "mfx_beliars_storm_invest";
	sfxisambient = 1;
};

instance spellfx_beliars_storm_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_beliars_storm_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400.;
	sfxid = "mfx_beliars_storm_cast";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 200;
};

instance spellfx_beliars_storm_key_collide(c_particlefxemitkey)
{
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 0.000001;
};

instance spellfx_beliars_storm_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_beliars_storm_init";
	lightrange = 0.01;
};

instance spellfx_beliars_storm_key_invest_1(c_particlefxemitkey)
{	lightrange = 100;	emcreatefxid = "spellfx_beliars_storm_investblast1";};

instance spellfx_beliars_storm_key_invest_2(c_particlefxemitkey)
{	lightrange = 200;	emcreatefxid = "spellfx_beliars_storm_investblast2";};

instance spellfx_beliars_storm_key_invest_3(c_particlefxemitkey)
{	lightrange = 300;	emcreatefxid = "spellfx_beliars_storm_investblast3";};

instance spellfx_beliars_storm_key_invest_4(c_particlefxemitkey)
{	lightrange = 400;	emcreatefxid = "spellfx_beliars_storm_investblast4";};

instance spellfx_beliars_storm_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_beliars_storm_spread(cfx_base_proto)
{
	visname_s = "mfx_beliars_storm_spread";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "createcreatequad";
	emactioncolldyn_s = "CREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	lightpresetname = "firesmall";
	emfxcreate_s = "spellfx_beliars_storm_collide";
	sfxid = "mfx_beliars_storm_collide";
	sfxisambient = 1;
};

instance  spellfx_berserk (cfx_base_proto)
{    	visname_s  =  "mfx_berserk_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjnumkeys  =  5;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjloopmode_s  =  "none";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "aura";
};

instance  spellfx_berserk_active (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_00 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_00";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_01 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_01";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_02 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_02";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_03 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_03";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_04 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_04";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_05 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_05";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_06 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_06";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_07 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_07";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_08 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_08";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_active_09 (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_glow_orange_09";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_berserk_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "target line";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_cast";
};

instance  spellfx_berserk_key_init (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_berserk_key_open (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_berserk_lefthandperm (cfx_base_proto)
{    	visname_s  =  "mfx_berserk_init_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	visalpha  =  1.0;
};

instance  spellfx_berserk_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_berserk_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_berserk_righthandperm (cfx_base_proto)
{    	visname_s  =  "mfx_berserk_init_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	visalpha  =  1.0;
};

instance spellfx_berzerk_origin(cfx_base_proto)
{
	visname_s = "mfx_charm_origin";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjdynupdatedelay = 0;
};

instance  spellfx_blackorearrow (cfx_base_proto)
{    	visname_s  =  "blackore_arrow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_blackorearrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_blackorearrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_blackorearrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_blackorebolt (cfx_base_proto)
{    	visname_s  =  "blackore_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_blackorebolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_blackorebolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_blackorebolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_bleeding_invest (cfx_base_proto)
{    	visname_s  =  "mfx_bleeding_spatter_0";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	sfxisambient  =  1;
    	emfxcreate_s  =  "spellfx_bleeding_spatter_90";
    	emfxlifespan  =  0.4;
};

instance  spellfx_bleeding_spatter_180 (cfx_base_proto)
{    	visname_s  =  "mfx_bleeding_spatter_180";
    	emtrjoriginnode  =  "bip01 pelvis";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_bleeding_spatter_90 (cfx_base_proto)
{    	visname_s  =  "mfx_bleeding_spatter_90";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_bleeding_spatter_180";
};

instance  spellfx_blizzard (cfx_base_proto)
{    	visname_s  =  "mfx_blizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_blizzard_investglow";
};

instance  spellfx_blizzardbullet (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_blizzardbullet_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_blizzardbullet_cast";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_blizzardbullet_collidefx";
    	emfxcolldyn_s  =  "spellfx_blizzardbullet_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_blizzardbullet_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_blizzardbullet_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_blizzardbullet_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_blizzardbullet_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_blizzardbullet_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_blizzardbullet_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_smallblizzard_init";
    	lightrange  =  0.001;
};

instance  spellfx_blizzardbullet_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_blizzard_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_blizzard_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_blizzard_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_blizzard_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_blizzard_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_blizzard_rain (cfx_base_proto)
{    	visname_s  =  "mfx_blizzard_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
    	sfxid  =  "mfx_blizzard_rain";
    	sfxisambient  =  1;
};

instance  spellfx_blizzard_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_blooddrone_die (cfx_base_proto)
{    	visname_s  =  "swampdrone_explode_blood";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "BLEND";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance spellfx_BLOODEXCRICATE (CFX_BASE_PROTO)
{
	 visname_s = "mfx_energyball_wulw_21_init";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emtrjloopmode_s = "none";
	 emtrjeasefunc_s = "LINEAR";
	 emfxinvestorigin_s = "spellfx_BLOODEXCRICATE_buildup";
};

/* Made by Risepolak (Xardas17) */

instance spellfx_BLOODEXCRICATE_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_energyball_wulw_21_init";
	emcreatefxid = "spellfx_BLOODEXCRICATE_cast";
	pfx_ppsisloopingchg = 1;
};


/* Made by Risepolak (Xardas17) */

instance spellfx_BLOODEXCRICATE_cast(cfx_base_proto)
{
	visname_s = "MFX_EXPLOSION_BLOOD_WULW_02";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "none";
	emfxcreate_s = "spellfx_BLOODEXCRICATE_caster";
	emfxcreatedowntrj = 1;
	emactioncolldyn_s = "createcollide";
	emfxcolldyn_s = "spellfx_BLOODEXCRICATE_collidedynfx";
	emfxcolldynperc_s = "spellfx_BLOODEXCRICATE_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

/* Made by Risepolak (Xardas17) */

instance spellfx_BLOODEXCRICATE_sendperception(cfx_base_proto)
{
	visname_s = "";
	sendassessmagic = 1;
};

instance spellfx_BLOODEXCRICATE_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_windfist_target";
	sfxid = "mfx_extricate_collide";
};

instance spellfx_BLOODEXCRICATE_caster(cfx_base_proto)
{
	visname_s = "";
	sfxid = "mfx_fireball_collide4";
	emfxcreate_s = "spellfx_BLOODEXCRICATE_rumble";
	emfxcreatedowntrj = 1;
};


instance spellfx_BLOODEXCRICATE_rumble(cfx_base_proto)
{
};

instance  spellfx_bloodmouthprojectile (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_mouth";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_bloodmouthprojectile_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_bloodmouthprojectile_invest";
};

instance  spellfx_bloodmouthprojectile_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_bloodmouthprojectile_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_bloodmouthprojectile_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_bloodmouthprojectile_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_bloodmouthprojectile_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_blueglow (cfx_base_proto)
{    	visname_s  =  "lightstar_blue";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_bluelight (cfx_base_proto)
{    	visname_s  =  "mfx_charm_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_bluerain (cfx_base_proto)
{    	visname_s  =  "mfx_bluerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_bluerain_investglow";
};

instance  spellfx_bluerain_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_bluerain_investglow";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetrange  =  30.0;
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_bluerain_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_bluerain_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_bluerain_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_bluerain_rain (cfx_base_proto)
{    	visname_s  =  "mfx_bluerain_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
    	sfxid  =  "mfx_bluerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_bluerain_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance spellfx_BLUE_AURA (CFX_BASE_PROTO)
{
	 visname_s = "ACID_AURA_Init_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_BLUE_AURA_active";
	 lightpresetname = "AURASMALL";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_BLUE_AURA_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "Bip01 Footsteps";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "AURAMEDIUM";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_BLUE_AURA_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "ACID_AURA_1";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_BLUE_AURA_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_BLUE_AURA_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_BLUE_AURA_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_blue_shield (CFX_BASE_PROTO)
{
	 visname_s = "mfx_blue_shield_init";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_blue_shield_active";
	 lightpresetname = "AURASMALL";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_blue_shield_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */





instance spellfx_blue_shield_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "AURAMEDIUM";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_blue_shield_active_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_blue_shield";
	lightrange = 400;
	sfxid = "mfx_arcanemissile_cast01";
	sfxisambient = 1;
	emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_blue_shield_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance  spellfx_blutfall (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_blutfall_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_blutfall_origin";
};

instance  spellfx_blutfall_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_blutrausch";
    	emcreatefxid  =  "spellfx_heal_lefthand";
};

instance  spellfx_blutfall_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_blutfall_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_blutfall_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_blutfall_origin (cfx_base_proto)
{    	visname_s  =  "mfx_blutrausch";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_blutopfer (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_energyball_target";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
};

instance  spellfx_blutopfer_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_energyball_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  900.0;
    	sfxid  =  "mfx_thunderball_collide3";
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_blutopfer_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_blutopfer_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_blutopfer_key_invest (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_blutopfer_target (cfx_base_proto)
{    	visname_s  =  "mfx_energyball_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_blutrausch (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "pingpong_once";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_suckenergy_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_blutrausch_invest";
};

instance  spellfx_blutrausch_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_blutrausch_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_blutrausch_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1200.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_blutrausch_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_blutrausch_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_blutrausch_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_blutrausch_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_blutrausch_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_blutrausch_origin (cfx_base_proto)
{    	visname_s  =  "mfx_blutrausch";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_blutrausch_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance spellfx_blyskawice(cfx_base_proto)
{
	visname_s = "blyskawice";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjnumkeys = 1;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 15.;
	emtrjangleheadvar = 0.;
	emtrjdynupdatedelay = 0.;
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
};

instance spellfx_blyskawice_key_cast(c_particlefxemitkey)
{
	sfxid = "mfx_lightning_target";
	pfx_ppsisloopingchg = 1;
};

instance  spellfx_bosskiller (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_invisibleprojectile";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_bosskiller_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_breathofdeath2 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_breathofdeath2_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_breathofdeath_cast";
};

instance  spellfx_breathofdeath2_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_breathofdeathforlich (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_breathofdeathforlich_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_breathofdeath_cast";
};

instance  spellfx_breathofdeathforlich_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_breathofdeathfororc (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_breathofdeathfororc_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_breathofdeath_cast";
};

instance  spellfx_breathofdeathfororc_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_breathofdeathsumskel (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_breathofdeathsumskel_cast (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_breathofdeathsumskel_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_breathofdeathsumskel_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_breathofdeathsumskel_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_breathofdeathsumskel_cast";
};

instance  spellfx_breathofdeathsumskel_key_invest_1 (c_particlefxemitkey)
{};

instance spellfx_breathofdeath_key_init(c_particlefxemitkey)
{
	emcheckcollision = 0;
};

instance  spellfx_breathofdemon (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdemon_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_breathofdemon_cast (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_breathofdemon_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_breathofdemon_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_breathofdemon_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_breathofdeath_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_breathofdemon_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_breathofdemon_target (cfx_base_proto)
{    	visname_s  =  "mfx_skull_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_skull_collide";
};

instance  spellfx_breathofferis (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_breathofferis_cast (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_breathofferis_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_breathofferis_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_breathofferis_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_breathofferis_cast";
};

instance  spellfx_breathofferis_key_invest_1 (c_particlefxemitkey)
{};

instance spellfx_bron(cfx_base_proto)
{
	visname_s = "mfx_bron_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_lefthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_bron_initglow";
	emfxcreatedowntrj = 0;
};

instance spellfx_bron_ground(cfx_base_proto)
{
	visname_s = "mfx_bron_cast";
	emtrjoriginnode = "bip01rfoot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_bron_target";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	sfxisambient = 1;
};

instance spellfx_bron_initglow(cfx_base_proto)
{
	visname_s = "mfx_bron_init_glow";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
};

instance spellfx_bron_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_bron_ground";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_bron_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_bron_init";
};

instance spellfx_bron_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
};

instance spellfx_bron_target(cfx_base_proto)
{
	visname_s = "mfx_bron_target";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_bron_target";
	sendassessmagic = 1;
};

instance  spellfx_cast (cfx_base_proto)
{    	visname_s  =  "mfx_spawn_cast";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_castfail_betweenhands (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.1;
    	visalpha  =  1.0;
};

instance  spellfx_castfail_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.1;
    	visalpha  =  1.0;
};

instance  spellfx_castfail_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.1;
    	visalpha  =  1.0;
};

instance spellfx_chainlightning(cfx_base_proto)
{
	visname_s = "lightning_big_a0.tga";
	vissize_s = "33";
	visalphablendfunc_s = "ADD";
	vistexanifps = 17;
	vistexaniislooping = 1;
	emfxcreate_s = "spellfx_chainlightning_origin";
	emtrjmode_s = "FIXED";
	emtrjnumkeys = 12;
	emtrjnumkeysvar = 3;
	emtrjangleelevvar = 20.;
	emtrjangleheadvar = 20.;
	emtrjloopmode_s = "none";
	emtrjoriginnode = "zs_righthand";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 200000.0;
	emselfrotvel_s = "0050";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
};

instance  spellfx_chainlightning_heavensrage (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_chainlightning_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_chainlightning_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_heavensrage_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2000.0;
    	sfxid  =  "mfx_thunderball_collide3";
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_chainlightning_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_chainlightning_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_chainlightning_key_invest (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance spellfx_chainlightning_origin(cfx_base_proto)
{
	visname_s = "mfx_lightning_origin";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	lightpresetname = "aura";
};

instance spellfx_chainlightning_origin_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_chainlightning_origin_key_invest_1(c_particlefxemitkey)
{
	sfxid = "mfx_lightning_origin";
	lightrange = 200;
};

instance spellfx_chainlightning_origin_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance  spellfx_chainlightning_target_cloud (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_chargefireball_00 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_firestorm_spread_00";
    	emfxcolldyn_s  =  "spellfx_firestorm_spread_00";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_00_collide (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_collide_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_00_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1_00";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_00_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1_00";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_00_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide2_00";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_00_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide3_00";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_00_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide4_00";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_00_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_00";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_00_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_00";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_00_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_00";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_00_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_00";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_00_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_chargefireball_00_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_chargefireball_00_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_chargefireball_00_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_chargefireball_00_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_chargefireball_00_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_chargefireball_00_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_00_key_invest_1 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_00_invest_blast1";
    	visname_s  =  "mfx_chargefb_cast_00_l2";
    	lightrange  =  150.0;
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_00_key_invest_2 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_00_invest_blast2";
    	visname_s  =  "mfx_chargefb_cast_00_l3";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_00_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_00_invest_blast3";
    	visname_s  =  "mfx_chargefb_cast_00_l4";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_00_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_00_invest_blast4";
    	visname_s  =  "mfx_chargefb_cast_00_l5";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_00_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_01 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_firestorm_spread_01";
    	emfxcolldyn_s  =  "spellfx_firestorm_spread_01";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_01_collide (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_collide_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_01_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1_01";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_01_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1_01";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_01_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide2_01";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_01_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide3_01";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_01_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide4_01";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_01_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_01";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_01_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_01";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_01_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_01";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_01_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_01";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_01_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_chargefireball_01_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_chargefireball_01_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_chargefireball_01_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_chargefireball_01_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_chargefireball_01_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_chargefireball_01_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_01_key_invest_1 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_01_invest_blast1";
    	visname_s  =  "mfx_chargefb_cast_01_l2";
    	lightrange  =  150.0;
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_01_key_invest_2 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_01_invest_blast2";
    	visname_s  =  "mfx_chargefb_cast_01_l3";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_01_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_01_invest_blast3";
    	visname_s  =  "mfx_chargefb_cast_01_l4";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_01_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_01_invest_blast4";
    	visname_s  =  "mfx_chargefb_cast_01_l5";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_01_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_02 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_firestorm_spread_02";
    	emfxcolldyn_s  =  "spellfx_firestorm_spread_02";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_02_collide (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_collide_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_02_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1_02";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_02_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1_02";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_02_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide2_02";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_02_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide3_02";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_02_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide4_02";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_02_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_02";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_02_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_02";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_02_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_02";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_02_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_02";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_02_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_chargefireball_02_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_chargefireball_02_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_chargefireball_02_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_chargefireball_02_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_chargefireball_02_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_chargefireball_02_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_02_key_invest_1 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_02_invest_blast1";
    	visname_s  =  "mfx_chargefb_cast_02_l2";
    	lightrange  =  150.0;
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_02_key_invest_2 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_02_invest_blast2";
    	visname_s  =  "mfx_chargefb_cast_02_l3";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_02_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_02_invest_blast3";
    	visname_s  =  "mfx_chargefb_cast_02_l4";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_02_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_02_invest_blast4";
    	visname_s  =  "mfx_chargefb_cast_02_l5";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_02_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_03 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_firestorm_spread_03";
    	emfxcolldyn_s  =  "spellfx_firestorm_spread_03";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_03_collide (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_collide_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_03_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1_03";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_03_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1_03";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_03_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide2_03";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_03_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide3_03";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_03_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide4_03";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_03_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_03";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_03_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_03";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_03_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_03";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_03_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_03";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_03_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_chargefireball_03_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_chargefireball_03_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_chargefireball_03_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_chargefireball_03_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_chargefireball_03_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_chargefireball_03_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_03_key_invest_1 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_03_invest_blast1";
    	visname_s  =  "mfx_chargefb_cast_03_l2";
    	lightrange  =  150.0;
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_03_key_invest_2 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_03_invest_blast2";
    	visname_s  =  "mfx_chargefb_cast_03_l3";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_03_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_03_invest_blast3";
    	visname_s  =  "mfx_chargefb_cast_03_l4";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_03_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_03_invest_blast4";
    	visname_s  =  "mfx_chargefb_cast_03_l5";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_03_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_04 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_firestorm_spread_04";
    	emfxcolldyn_s  =  "spellfx_firestorm_spread_04";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_04_collide (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_collide_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_04_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1_04";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_04_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1_04";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_04_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide2_04";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_04_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide3_04";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_04_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide4_04";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_04_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_04";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_04_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_04";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_04_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_04";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_04_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_04";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_04_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_chargefireball_04_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_chargefireball_04_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_chargefireball_04_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_chargefireball_04_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_chargefireball_04_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_chargefireball_04_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_04_key_invest_1 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_04_invest_blast1";
    	visname_s  =  "mfx_chargefb_cast_04_l2";
    	lightrange  =  150.0;
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_04_key_invest_2 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_04_invest_blast2";
    	visname_s  =  "mfx_chargefb_cast_04_l3";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_04_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_04_invest_blast3";
    	visname_s  =  "mfx_chargefb_cast_04_l4";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_04_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_04_invest_blast4";
    	visname_s  =  "mfx_chargefb_cast_04_l5";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_04_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_05 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_firestorm_spread_05";
    	emfxcolldyn_s  =  "spellfx_firestorm_spread_05";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_05_collide (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_collide_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_05_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1_05";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_chargefireball_05_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1_05";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_05_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide2_05";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_05_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide3_05";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_05_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide4_05";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_05_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_05";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_chargefireball_05_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_05";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_chargefireball_05_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_05";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_chargefireball_05_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide_05";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_chargefireball_05_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_chargefireball_05_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_chargefireball_05_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_chargefireball_05_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_chargefireball_05_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_chargefireball_05_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_chargefireball_05_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_05_key_invest_1 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_05_invest_blast1";
    	visname_s  =  "mfx_chargefb_cast_05_l2";
    	lightrange  =  150.0;
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_05_key_invest_2 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_05_invest_blast2";
    	visname_s  =  "mfx_chargefb_cast_05_l3";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_05_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_05_invest_blast3";
    	visname_s  =  "mfx_chargefb_cast_05_l4";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_05_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_chargefireball_05_invest_blast4";
    	visname_s  =  "mfx_chargefb_cast_05_l5";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_chargefireball_05_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_chargefireball_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  1.0;
};

instance  spellfx_chargepoison_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_poison_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "poison2";
};

instance  spellfx_charm_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_charm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.0;
    	visalpha  =  1.0;
};

instance  spellfx_concussionbolthead (cfx_base_proto)
{    	visname_s  =  "mfx_palholybolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_concussionbolt_collide";
    	emfxcolldyn_s  =  "spellfx_concussionbolt_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_concussionbolthead_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_palholybolt_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1600.0;
    	sfxid  =  "mfx_palholybolt_cast";
    	emcheckcollision  =  1;
};

instance  spellfx_concussionbolthead_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_concussionbolthead_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_palholybolt_init";
    	scaleduration  =  0.5;
};

instance  spellfx_concussionboltlefthand (cfx_base_proto)
{    	visname_s  =  "mfx_palholybolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_concussionbolt_collide";
    	emfxcolldyn_s  =  "spellfx_concussionbolt_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_concussionboltlefthand_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_palholybolt_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1600.0;
    	sfxid  =  "mfx_palholybolt_cast";
    	emcheckcollision  =  1;
};

instance  spellfx_concussionboltlefthand_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_concussionboltlefthand_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_palholybolt_init";
    	scaleduration  =  0.5;
};

instance  spellfx_crystalbody_glimmer (cfx_base_proto)
{    	visname_s  =  "crystalbody_glimmer_white";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_CRY_V0 (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V0";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V0_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_CRY_V0_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_CRY_V0_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V0";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
//	 sfxid = "BCR_EATING";
//	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V0_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V0_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V0_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V1 (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V1_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_CRY_V1_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_CRY_V1_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V1";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
//	 sfxid = "BCR_EATING";
//	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V1_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V1_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V1_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V2 (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V2";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V2_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_CRY_V2_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_CRY_V2_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V2";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
//	 sfxid = "BCR_EATING";
//	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V2_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V2_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V2_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V3 (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V3";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V3_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_CRY_V3_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_CRY_V3_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V3";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
//	 sfxid = "BCR_EATING";
//	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V3_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V3_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V3_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V4 (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V4";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V4_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_CRY_V4_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_CRY_V4_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "CRY_V4";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
//	 sfxid = "BCR_EATING";
//	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V4_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V4_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_CRY_V4_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance  spellfx_darkarmor_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_darkarmor_smoke (cfx_base_proto)
{    	visname_s  =  "smoke_model_kairo";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "whiteblend";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_darkarmor_smoke_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_darkmagestaff_collidefx (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_ifb_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
    	sfxid  =  "mfx_darkmagestaff_collide";
};

instance spellfx_DEATHEXCRICATE (CFX_BASE_PROTO)
{
	 visname_s = "mfx_energyball_wulw_40_init";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emtrjloopmode_s = "none";
	 emtrjeasefunc_s = "LINEAR";
	 emfxinvestorigin_s = "spellfx_DEATHEXCRICATE_buildup";
};

/* Made by Risepolak (Xardas17) */

instance spellfx_DEATHEXCRICATE_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_energyball_wulw_40_init";
	emcreatefxid = "spellfx_DEATHEXCRICATE_cast";
	pfx_ppsisloopingchg = 1;
};


/* Made by Risepolak (Xardas17) */

instance spellfx_DEATHEXCRICATE_cast(cfx_base_proto)
{
	visname_s = "MFX_EXPLOSION_DEATH_WULW_02";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "none";
	emfxcreate_s = "spellfx_DEATHEXCRICATE_caster";
	emfxcreatedowntrj = 1;
	emactioncolldyn_s = "createcollide";
	emfxcolldyn_s = "spellfx_DEATHEXCRICATE_collidedynfx";
	emfxcolldynperc_s = "spellfx_DEATHEXCRICATE_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

/* Made by Risepolak (Xardas17) */

instance spellfx_DEATHEXCRICATE_sendperception(cfx_base_proto)
{
	visname_s = "";
	sendassessmagic = 1;
};

instance spellfx_DEATHEXCRICATE_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_windfist_target";
	sfxid = "mfx_extricate_collide";
};

instance spellfx_DEATHEXCRICATE_caster(cfx_base_proto)
{
	visname_s = "";
	sfxid = "mfx_fireball_collide4";
	emfxcreate_s = "spellfx_DEATHEXCRICATE_rumble";
	emfxcreatedowntrj = 1;
};


instance spellfx_DEATHEXCRICATE_rumble(cfx_base_proto)
{
};

instance  spellfx_deathrangedweaponenchantment (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_deathrangedweaponenchantment_investglow (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_deathrangedweaponenchantment_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_deathrangedweaponenchantment_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_deathshoot2_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_deathshoot_mesheffect";
};

instance  spellfx_deathshoot_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_deathshoot2_arrow";
};

instance  spellfx_deathshoot_mesheffect (cfx_base_proto)
{    	visname_s  =  "death_arrow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_deathspark (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_deathspark_invest";
};

instance  spellfx_deathspark_00 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_00_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_00_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_00_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_00_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_00_cast";
};

instance  spellfx_deathspark_00_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_01 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_01_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_01_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_01_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_01_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_01_cast";
};

instance  spellfx_deathspark_01_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_02 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_02_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_02_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_02_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_02_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_02_cast";
};

instance  spellfx_deathspark_02_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_03 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_03_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_03_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_03_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_03_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_03_cast";
};

instance  spellfx_deathspark_03_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_04 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_04_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_04_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_04_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_04_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_04_cast";
};

instance  spellfx_deathspark_04_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_05 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_05_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_05_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_05_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_05_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_05_cast";
};

instance  spellfx_deathspark_05_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_06 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_06_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_06_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_06_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_06_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_06_cast";
};

instance  spellfx_deathspark_06_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_07 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_07_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_07_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_07_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_07_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_07_cast";
};

instance  spellfx_deathspark_07_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_08 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_08_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_08_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_08_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_08_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_08_cast";
};

instance  spellfx_deathspark_08_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_09 (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_deathspark_09_cast (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_cast_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_breathofdeath_target";
    	emfxcolldynperc_s  =  "spellfx_deathspark_sendperception";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_09_cast_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	emcheckcollision  =  1;
};

instance  spellfx_deathspark_09_invest (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_invest";
    	sfxid  =  "mfx_breathofdeath_invest";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_09_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_deathspark_09_cast";
};

instance  spellfx_deathspark_09_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_deathspark_blood (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_blood";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emfxlifespan  =  1.0;
};

instance  spellfx_deathspark_blood_dark (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_blood_dark";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emfxlifespan  =  1.0;
};

instance  spellfx_deathspark_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_deathspark_explosion";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  " = ";
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathspark_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_deathspark_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_deathspark_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_deathspark_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_deathspark_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_deathspark_sendperception (cfx_base_proto)
{    	sendassessmagic  =  1;
};

instance  spellfx_deathwave (cfx_base_proto)
{    	visname_s  =  "mfx_deathwave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_deathwave_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_deathwave_target";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_deathwave_target";
};

instance  spellfx_deathwave_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_deathwave_explosion";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_deathwave_ground";
};

instance  spellfx_deathwave_ground (cfx_base_proto)
{    	visname_s  =  "mfx_deathwave_cast";
    	emtrjoriginnode  =  "bip01 r foot";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_deathwave_collidedynfx";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_deathwave_cast";
    	sfxisambient  =  1;
};

instance  spellfx_deathwave_invest (cfx_base_proto)
{    	visname_s  =  "mfx_deathwave_righthand";
    	emtrjmode_s  =  "FIXED";
    	emfxcolldyn_s  =  "spellfx_deathwave_lefthand";
};

instance  spellfx_deathwave_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_deathwave_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_deathwave_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_deathwave_init";
};

instance  spellfx_deathwave_key_invest (c_particlefxemitkey)
{    	visname_s  =  "mfx_deathwave_righthand";
    	emcreatefxid  =  "spellfx_deathwave_lefthand";
};

instance  spellfx_deathwave_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_deathwave_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_deathwave_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_deathweaponenchantment_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_deathweaponenchantment_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_death_arrow (cfx_base_proto)
{    	visname_s  =  "death_arrow";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_death_weapon_ranged_enchantment (cfx_base_proto)
{    	visname_s  =  "fire_swordblack";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance spellfx_demon(cfx_base_proto)
{
	visname_s = "mfx_summondemon_init";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	lightpresetname = "redambience";
	emfxinvestorigin_s = "spellfx_demon_invest";
};

instance  spellfx_demonspawn (cfx_base_proto)
{    	visname_s  =  "spawn_demon";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance spellfx_demon_invest(cfx_base_proto)
{
	visname_s = "mfx_summondemon_invest";
	emtrjoriginnode = "bip01";
};

instance spellfx_demon_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_demon_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_demon_key_invest_1(c_particlefxemitkey)
{	lightrange = 400;};

instance spellfx_demon_key_invest_2(c_particlefxemitkey)
{};

instance spellfx_demon_key_invest_3(c_particlefxemitkey)
{	emcreatefxid = "fx_earthquake";};

instance spellfx_demon_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance  spellfx_deshrink (cfx_base_proto)
{    	visname_s  =  "mfx_deshrink";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
};

instance  spellfx_destory_corpse_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_destroycorpse_explosion";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emfxlifespan  =  5.0;
};

instance  spellfx_destroyevilgorzah (cfx_base_proto)
{    	visname_s  =  "mfx_destroyundead_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_destroyevilgorzah_collide";
    	emfxcolldyn_s  =  "spellfx_destroyevilgorzah_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_destroyevilgorzah_collide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_destroyundead_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_destroyundead_collide";
    	sfxisambient  =  1;
};

instance  spellfx_destroyevilgorzah_collidedynfx (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_destroyundead_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_destroyundead_collide";
    	sfxisambient  =  1;
};

instance  spellfx_destroyevilgorzah_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_destroyundead_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_destroyundead_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_destroyevilgorzah_key_init (c_particlefxemitkey)
{};

instance  spellfx_destroyorcsiegecorpse (cfx_base_proto)
{    	visname_s  =  "mfx_destroyorcsiegecorpse";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_destroyundead_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_destroyundead_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  1.0;
};

instance  spellfx_destroyundead_schmetterschuss (cfx_base_proto)
{    	visname_s  =  "mfx_destroyundead_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_destroyundead_collide";
    	emfxcolldyn_s  =  "spellfx_destroyundead_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_destroyundead_schmetterschuss_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_destroyundead_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1800.0;
    	sfxid  =  "mfx_destroyundead_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_destroyundead_schmetterschuss_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_destroyundead_init";
};

instance spellfx_destroyundead_sendperception(cfx_base_proto)
{
	emtrjoriginnode = "bip01";
	visname_s = "mfx_destroyundead_collide";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0.;
	lightpresetname = "aura";
	sendassessmagic = 1;
	sfxid = "mfx_destroyundead_collide";
	sfxisambient = 1;
};

instance  spellfx_divfirebolt (cfx_base_proto)
{    	visname_s  =  "fire_bolt_div";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "div_arrow_fire";
    	sfxisambient  =  1;
};

instance  spellfx_divfirebolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_divfirebolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  300.0;
};

instance  spellfx_divfirebolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  400.0;
};

instance spellfx_dragon(cfx_base_proto)
{
	visname_s = "mfx_fireball_init";
	vissize_s = "11";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 0.;
	lightpresetname = "firesmall";
	emtrjtargetrange = 440;
	emtrjtargetelev = 0;
	emfxinvesttarget_s = "spellfx_dragon_target";
	emfxinvestorigin_s = "spellfx_dragon_bridge";
};

instance spellfx_dragonfear(cfx_base_proto)
{
	visname_s = "mfx_dragon_fear_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_dragonfear_collidefx";
	emfxcolldyn_s = "spellfx_dragonfear_sendperception";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "firesmall";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
};

instance spellfx_dragonfear_collidefx(cfx_base_proto)
{
	visname_s = "mfx_dragon_fear_origin";
	emtrjmode_s = "FIXED";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "bip01";
	emtrjdynupdatedelay = 10000;
	sfxid = "mfx_dragon_fear_cast";
	sfxisambient = 1;
};

instance spellfx_dragonfear_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_firebolt_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400.;
	sfxid = "torch_enlight";
	lightrange = 200;
	emcheckcollision = 1;
};

instance spellfx_dragonfear_key_collide(c_particlefxemitkey)
{
	visname_s = "";
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 0.000001;
	sfxid = "torch_enlight";
};

instance spellfx_dragonfear_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_firebolt_init";
	lightrange = 0.001;
};

instance spellfx_dragonfear_key_open(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_dragonfear_old_wings";
	emcreatefxid = "spellfx_dragonfear_old_wings2";
	lightrange = 0.001;
};

instance spellfx_dragonfear_old(cfx_base_proto)
{
	visname_s = "mfx_dragon_fear_init";
	emtrjmode_s = "FIXED";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emactioncollstat_s = "collideCREATEONCE";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxinvesttarget_s = "spellfx_dragonfear_old_wings2";
	emfxinvestorigin_s = "spellfx_dragonfear_old_wings";
};

instance spellfx_dragonfear_old_ground(cfx_base_proto)
{
	visname_s = "mfx_dragon_fear_origin";
	emtrjmode_s = "FIXED";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "bip01";
	emtrjdynupdatedelay = 10000;
	sfxid = "mfx_dragon_fear_cast";
	sfxisambient = 1;
};

instance spellfx_dragonfear_old_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_dragon_fear_ground";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_dragonfear_old_key_invest_1(c_particlefxemitkey)
{
};

instance spellfx_dragonfear_old_key_open(c_particlefxemitkey)
{
	emtrjeasevel = 0.;
	emcreatefxid = "spellfx_dragonfear_old_wings";
	emcreatefxid = "spellfx_dragonfear_old_wings2";
};

instance spellfx_dragonfear_old_sendperception(cfx_base_proto)
{
	visname_s = "";
	sfxid = "hammer";
	sendassessmagic = 1;
};

instance spellfx_dragonfear_old_wings(cfx_base_proto)
{
	visname_s = "mfx_dragon_fear_wings";
	emtrjmode_s = "FIXED";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "bip01";
	emtrjdynupdatedelay = 10000;
	emfxcreate_s = "fx_earthquake";
};

instance spellfx_dragonfear_sendperception(cfx_base_proto)
{
	visname_s = "mfx_dragon_fear_origin";
	emtrjmode_s = "FIXED";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "bip01";
	emtrjdynupdatedelay = 10000;
	sfxid = "mfx_dragon_fear_cast";
	sfxisambient = 1;
};

instance  spellfx_dragonfire (cfx_base_proto)
{    	visname_s  =  "mfx_dragonfire_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_dragonfire_collidefx";
    	emfxcolldyn_s  =  "spellfx_dragonfire_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "firesmall";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_dragonfire_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_dragonfire_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_dragonfire_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_dragonfire_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_dragonfire_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_dragonfire_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "torch_enlight";
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_dragonfire_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "torch_enlight";
};

instance  spellfx_dragonfire_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_dragonfire_init";
    	lightrange  =  0.001;
};

instance  spellfx_dragonfire_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_dragonstone (cfx_base_proto)
{    	visname_s  =  "dragon_stones3";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_dragon_bridge(cfx_base_proto)
{
	visname_s = "mfx_dragon_bridge";
	emtrjmode_s = "targetline";
	emtrjoriginnode = "Bip01 Head";
	emtrjtargetnode = "Bip01 Head";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
	emfxcreate_s = "spellfx_dragon_origin";
	sfxid = "mfx_fireball_invest1";
	sfxisambient = 1;
	lightpresetname = "firesmall";
};

instance spellfx_dragon_bridge_key_init(c_particlefxemitkey)
{
	emtrjeasevel = 0.01;
};

instance spellfx_dragon_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
	sfxid = "mfx_fireball_invest1";
	sfxisambient = 1;
};

instance spellfx_dragon_key_invest_1(c_particlefxemitkey)
{
	visname_s = "simpleglow.tga";
	sfxid = "watherrain";
	sfxisambient = 1;
};

instance spellfx_dragon_target(cfx_base_proto)
{
	visname_s = "mfx_dragon";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
	sendassessmagic = 1;
	lightpresetname = "firesmall";
};

instance  spellfx_drones (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_drones_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_drones_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_drones_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_drones_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_druckwelle (cfx_base_proto)
{    	visname_s  =  "mfx_druckwelle_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_druckwelle_investstorm";
};

instance  spellfx_druckwelle_collidedynfx (cfx_base_proto)
{    	visname_s  =  "lightstar_white";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
    	sendassessmagic  =  1;
};

instance  spellfx_druckwelle_investstorm (cfx_base_proto)
{    	visname_s  =  "mfx_druckwelle_investstorm";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "justwhite";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_druckwelle_key_cast (c_particlefxemitkey)
{    	visname_s  =  "empty";
    	emcreatefxid  =  "spellfx_druckwelle_wave";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_druckwelle_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_druckwelle_init";
};

instance  spellfx_druckwelle_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "empty";
};

instance  spellfx_druckwelle_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "empty";
};

instance  spellfx_druckwelle_wave (cfx_base_proto)
{    	visname_s  =  "mfx_druckwelle_wave";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	lightpresetname  =  "justwhite";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_druznash_berserk (cfx_base_proto)
{    	visname_s  =  "druznash_berserk";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_druznash_holyshield (cfx_base_proto)
{    	visname_s  =  "druznash_holyshield";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_ds_damedge (cfx_base_proto)
{    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_ds_damedge_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windbolt_invis_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	emcheckcollision  =  1;
};

instance spellfx_earthquake(cfx_base_proto)
{
	visname_s = "mfx_earthquake_init";
	vissize_s = "11";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjnumkeys = 7;
	emtrjnumkeysvar = 3;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 20;
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 200000;
	emactioncolldyn_s = "CREATEONCE";
	emfxinvestorigin_s = "spellfx_earthquake_invest";
};

instance  spellfx_earthquakenew (cfx_base_proto)
{    	visname_s  =  "mfx_earthquakenew_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_earthquakenew_investglow";
};

instance  spellfx_earthquakenew_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_earthquakenew_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_earthquakenew_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_earthquakenew_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_earthquakenew_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_earthquakenew_rain (cfx_base_proto)
{    	visname_s  =  "mfx_earthquakenew_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
};

instance  spellfx_earthquakenew_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance spellfx_earthquake_cast(cfx_base_proto)
{
	visname_s = "mfx_earthquake_cast";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	sfxid = "mfx_earthquake_cast";
	sfxisambient = 1;
};

instance spellfx_earthquake_invest(cfx_base_proto)
{
	visname_s = "mfx_earthquake_invest";
	sfxid = "mfx_earthquake_invest";
	sfxisambient = 1;
};

instance spellfx_earthquake_investblast(cfx_base_proto)
{
	visname_s = "mfx_earthquake_invest_blast";
	sfxid = "mfx_earthquake_investblast";
	sfxisambient = 1;
};

instance spellfx_earthquake_key_cast(c_particlefxemitkey)
{
	visname_s = "simpleglow.tga";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	emcheckcollision = 1;
	emcreatefxid = "spellfx_earthquake_cast";
};

instance spellfx_earthquake_key_init(c_particlefxemitkey)
{
	emcheckcollision = 0;
};

instance spellfx_earthquake_key_invest_1(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_earthquake_investblast";
};

instance spellfx_earthquake_key_invest_2(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_earthquake_investblast";
};

instance spellfx_earthquake_key_invest_3(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_earthquake_investblast";
};

instance spellfx_earthquake_key_invest_4(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_earthquake_investblast";
};

instance spellfx_earthquake_target(cfx_base_proto)
{
	visname_s = "mfx_earthquake_collide";
	sendassessmagic = 1;
};

instance  spellfx_earth_ring_elementalorc (cfx_base_proto)
{    	visname_s  =  "mfx_earthring_fadeout_long";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance spellfx_EFFECT_Wulwryk_BSM_1128(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1128";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1128a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1128a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1128b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1128b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1182(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1182";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1182a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1182a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1182b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1182b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1248(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1248";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1248a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1248a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1248b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1248b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1250(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1250";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_1383(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_1383";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_146(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_146";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_146a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_146a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_146b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_146b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_150(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_150";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_153(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_153";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_17(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_17";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_17a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_17a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_17b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_17b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_180(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_180";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_267(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_267";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_267a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_267a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_267b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_267b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_305(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_305";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_39(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_39";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_394(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_394";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_40(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_40";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_408(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_408";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_408a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_408a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_408b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_408b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_40a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_40a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_40b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_40b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_5(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_5";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_693(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_693";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_694(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_694";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_72(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_72";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_BSM_974(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_BSM_974";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_1091(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_1091";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_1091a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_1091a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_1091b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_1091b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_1248(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_1248";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_1262(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_1262";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_1262a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_1262a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_1262b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_1262b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_150(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_150";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_154(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_154";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_DSS_3(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_DSS_3";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_1074(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_1074";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_1248(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_1248";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_1249(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_1249";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_144(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_144";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_619(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_619";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_619a(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_619a";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_619b(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_619b";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_693 (EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_693";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_MK_736(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_MK_736";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_UDD_1026(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_UDD_1026";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_UDD_1248(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_UDD_1248";
	//lightpresetname = "";
};

instance spellfx_EFFECT_Wulwryk_UDD_663(EFFECT_SE)
{
	visname_s = "EFFECT_Wulwryk_UDD_663";
	//lightpresetname = "";
};

instance  spellfx_eisklinge (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_eisklinge_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_eisklinge_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_init";
};

instance  spellfx_eisklinge_origin (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_eisklinge_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "mfx_sleep_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_electrowave_explosion_05 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_05";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_10 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_10";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_15 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_15";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_20 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_20";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_25 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_25";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_30 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_30";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_35 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_35";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_40 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_40";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_45 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_45";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_50 (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_50";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_rundumschlag (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_rundumschlag";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_electrowave_explosion_rundumschlag_beliar (cfx_base_proto)
{    	visname_s  =  "mfx_electrowave_rundumschlag_beliar";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance spellfx_ELECTRRICEXCRICATE (CFX_BASE_PROTO)
{
	 visname_s = "mfx_energyball_wulw_10_init";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emtrjloopmode_s = "none";
	 emtrjeasefunc_s = "LINEAR";
	 emfxinvestorigin_s = "spellfx_ELECTRRICEXCRICATE_buildup";
};

/* Made by Risepolak (Xardas17) */

instance spellfx_ELECTRRICEXCRICATE_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_energyball_wulw_10_init";
	emcreatefxid = "spellfx_ELECTRRICEXCRICATE_cast";
	pfx_ppsisloopingchg = 1;
};


/* Made by Risepolak (Xardas17) */

instance spellfx_ELECTRRICEXCRICATE_cast(cfx_base_proto)
{
	visname_s = "MFX_EXPLOSION_ELECTRIC_WULW_03";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "none";
	emfxcreate_s = "spellfx_ELECTRRICEXCRICATE_caster";
	emfxcreatedowntrj = 1;
	emactioncolldyn_s = "createcollide";
	emfxcolldyn_s = "spellfx_ELECTRRICEXCRICATE_collidedynfx";
	emfxcolldynperc_s = "spellfx_ELECTRRICEXCRICATE_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

/* Made by Risepolak (Xardas17) */

instance spellfx_ELECTRRICEXCRICATE_sendperception(cfx_base_proto)
{
	visname_s = "";
	sendassessmagic = 1;
};

instance spellfx_ELECTRRICEXCRICATE_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_windfist_target";
	sfxid = "mfx_extricate_collide";
};

instance spellfx_ELECTRRICEXCRICATE_caster(cfx_base_proto)
{
	visname_s = "";
	sfxid = "mfx_fireball_collide4";
	emfxcreate_s = "spellfx_ELECTRRICEXCRICATE_rumble";
	emfxcreatedowntrj = 1;
};


instance spellfx_ELECTRRICEXCRICATE_rumble(cfx_base_proto)
{
};

instance  spellfx_elementalorcimmortal (cfx_base_proto)
{    	visname_s  =  "mfx_healshrine_green";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_elementalorc_ice_mode (cfx_base_proto)
{    	visname_s  =  "ice_weapon_enchantment";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_elementalorc_mode_fire (cfx_base_proto)
{    	visname_s  =  "elementalorc_mode_fire";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_elementalorc_spiral_1 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_fire";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_2";
};

instance  spellfx_elementalorc_spiral_2 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_storm";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_3";
};

instance  spellfx_elementalorc_spiral_3 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_earth";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_4";
};

instance  spellfx_elementalorc_spiral_4 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_ice";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_elementalorc_spiral_earth_1 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_earth_01";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	sfxid  =  "mfx_earthquake";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_earth_2";
};

instance  spellfx_elementalorc_spiral_earth_2 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_earth_02";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_earth_3";
};

instance  spellfx_elementalorc_spiral_earth_3 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_earth_03";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_earth_4";
};

instance  spellfx_elementalorc_spiral_earth_4 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_earth_04";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_elementalorc_spiral_fire_1 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_fire_01";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	sfxid  =  "mfx_firespell_humanburn";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_fire_2";
};

instance  spellfx_elementalorc_spiral_fire_2 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_fire_02";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_fire_3";
};

instance  spellfx_elementalorc_spiral_fire_3 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_fire_03";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_fire_4";
};

instance  spellfx_elementalorc_spiral_fire_4 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_fire_04";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_elementalorc_spiral_ice_1 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_ice_01";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	sfxid  =  "mfx_icecube_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_ice_2";
};

instance  spellfx_elementalorc_spiral_ice_2 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_ice_02";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_ice_3";
};

instance  spellfx_elementalorc_spiral_ice_3 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_ice_03";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_ice_4";
};

instance  spellfx_elementalorc_spiral_ice_4 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_ice_04";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_elementalorc_spiral_storm_1 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_storm_01";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_storm_2";
};

instance  spellfx_elementalorc_spiral_storm_2 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_storm_02";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_storm_3";
};

instance  spellfx_elementalorc_spiral_storm_3 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_storm_03";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
    	emfxcreate_s  =  "spellfx_elementalorc_spiral_storm_4";
};

instance  spellfx_elementalorc_spiral_storm_4 (cfx_base_proto)
{    	visname_s  =  "mfx_elementalorc_spiral_storm_04";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_elevate_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_elevate_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_elevate_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_elevate_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_endboss_lightstar_berserkerphase (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_berserkerphase";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_endboss_lightstar_elementalphase_earth (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_elementalphase_earth";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_endboss_lightstar_elementalphase_fire (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_elementalphase_fire";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_endboss_lightstar_elementalphase_ice (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_elementalphase_ice";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_endboss_lightstar_elementalphase_storm (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_elementalphase_storm";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_endboss_lightstar_ritualphase (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_ritualphase";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_endboss_lightstar_ritualphase2 (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_ritualphase2";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_endboss_lightstar_shadowphase (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_shadowphase";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_endboss_lightstar_summonerphase (cfx_base_proto)
{    	visname_s  =  "endboss_lightstar_summonerphase";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance spellfx_enervate(cfx_base_proto)
{
	visname_s = "mfx_enervate_init";
	emtrjmode_s = "TARGET";
	emtrjoriginnode = "zs_righthand";
	emtrjnumkeys = 2;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 2;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjloopmode_s = "HALT";
	emtrjdynupdatedelay = 0;
	emfxinvestorigin_s = "spellfx_enervate_origin";
	emfxinvesttarget_s = "spellfx_enervate_target";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
};

instance spellfx_enervate_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_enervate_targetend";
};

instance spellfx_enervate_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_enervate_init";
	emtrjeasevel = 0.01;
};

instance spellfx_enervate_key_invest_1(c_particlefxemitkey)
{
	visname_s = "mfx_enervate_target";
	emtrjeasevel = 2000;
	sfxid = "mfx_lightning_origin";
	sfxisambient = 1;
};

instance spellfx_enervate_origin(cfx_base_proto)
{
	visname_s = "mfx_enervate_bridge";
	emtrjmode_s = "targetline";
	emtrjeasevel = 0.001;
	emtrjoriginnode = "bip01rhand";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
	sfxid = "mfx_lightning_target";
	sfxisambient = 1;
};

instance spellfx_enervate_target(cfx_base_proto)
{
	visname_s = "mfx_enervate_target";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
	lightpresetname = "firesmall";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
	sendassessmagic = 1;
	emtrjdynupdatedelay = 0.01;
	sfxid = "mfx_lightning_target";
	sfxisambient = 1;
};

instance  spellfx_engel (cfx_base_proto)
{    	visname_s  =  "mfx_engel_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_engel_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_feuerschwert_origin";
};

instance  spellfx_engel_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_feuerschwert_cast";
    	emcreatefxid  =  "spellfx_feuerschwert_lefthand";
};

instance  spellfx_engel_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_feuerschwert_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "fire";
};

instance  spellfx_engel_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_engel_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_engel_origin (cfx_base_proto)
{    	visname_s  =  "mfx_feuerschwert_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_erdbeben (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_invisibleprojectile";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_erdbeben_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_erster_fokus (cfx_base_proto)
{    	visname_s  =  "erster_fokus_effect";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_explosion(cfx_base_proto)
{
	visname_s = "mfx_explosion_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collideCREATEONCEcreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_instantfireball_collide";
	emfxcolldyn_s = "spellfx_explosion_collidedynfx";
	emfxcolldynperc_s = "vob_magicburn";
	emfxcollstatalign_s = "COLLISIONNORMAL";
	emfxcreatedowntrj = 0;
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100100";
	userstring[2] = "mul";
	lightpresetname = "firesmall";
};

instance  spellfx_explosionarrowexplosionnosound (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_explosionarrowexplosionnosound_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firestorm_spreadnosound";
    	pfx_ppsisloopingchg  =  1;
};


instance spellfx_explosionFrost (CFX_BASE_PROTO)
{
	 visname_s = "MFX_ICEEXPLOISION_INIT";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emtrjloopmode_s = "none";
	 emtrjeasefunc_s = "LINEAR";
	 emfxinvestorigin_s = "spellfx_explosionFrost_buildup";
};

instance spellfx_explosionFrost_buildup (CFX_BASE_PROTO)
{
	 visname_s = "mfx_heal_invest_1";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "bip01";
	 emfxcreate_s = "spellfx_explosionFrost_prerumble";
	 sfxid = "mfx_extricate_inhale";
};

instance spellfx_explosionFrost_cast (CFX_BASE_PROTO)
{
	 visname_s = "MFX_ICEEXPLOISION_SPREAD_SMALL";
	 emtrjmode_s = "none";
	 emtrjoriginnode = "bip01";
	 emfxcreate_s = "spellfx_explosionFrost_caster";
	 emfxcreatedowntrj = 1;
	 emactioncolldyn_s = "createcollide";
	 emfxcolldyn_s = "spellfx_explosionFrost_collidedynfx";
	 emfxcolldynperc_s = "spellfx_explosionFrost_sendperception";
	 emfxcolldynalign_s = "COLLISIONNORMAL";
	 emcheckcollision = 1;
};

instance spellfx_explosionFrost_caster(cfx_base_proto)
{
	visname_s = "";
	sfxid = "mfx_fireball_collide4";
	emfxcreate_s = "spellfx_explosionFrost_rumble";
	emfxcreatedowntrj = 1;
};

instance spellfx_explosionFrost_collidedynfx (CFX_BASE_PROTO)
{
	 visname_s = "MFX_ICEEXPLOISION_SPREAD_SMALL";
	 sfxid = "mfx_extricate_collide";
};

instance spellfx_explosionFrost_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "MFX_ICEEXPLOISION_INIT";
	 pfx_ppsisloopingchg = 1;
	 emcreatefxid = "spellfx_explosionFrost_cast";
};

instance spellfx_explosionFrost_prerumble (CFX_BASE_PROTO)
{
};

instance spellfx_explosionFrost_rumble (CFX_BASE_PROTO)
{
};

instance spellfx_explosionFrost_sendperception(cfx_base_proto)
{
	visname_s = "";
	sendassessmagic = 1;
};
instance spellfx_explosion_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_fireball_collide1";
	visalpha = 1;
	emtrjoriginnode = "bip01";
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sfxid = "mfx_explosion_collide";
	emfxcreate_s = "spellfx_explosion_target";
	emfxcreatedowntrj = 1;
};

instance spellfx_explosion_key_cast(c_particlefxemitkey)
{
	lightrange = 100;
	visname_s = "mfx_explosion_pfxtrail";
	emtrjmode_s = "TARGET";
	emselfrotvel_s = "100100100";
	emtrjeasevel = 1400;
	sfxid = "mfx_suckenergy_cast";
	sfxisambient = 1;
	emcreatefxid = "spellfx_explosion_trail";
	emcheckcollision = 1;
};

instance spellfx_explosion_key_collide(c_particlefxemitkey)
{
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 1e-006;
	sfxid = "fsb_attack";
};

instance spellfx_explosion_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_explosion_init";
	lightrange = 0.01;
};

instance spellfx_explosion_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_explosion_target(cfx_base_proto)
{
	emtrjoriginnode = "bip01";
	visname_s = "mfx_explosion_spread";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sfxid = "mfx_explosion_sphere";
	sfxisambient = 1;
};

instance spellfx_explosion_trail(cfx_base_proto)
{
	emtrjeasevel = 1400;
	visname_s = "mfx_explosion_cast";
	visalpha = 1;
	emtrjmode_s = "TARGET";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 20000;
	emselfrotvel_s = "00200";
	emcheckcollision = 2;
	emactioncolldyn_s = "collide";
	emactioncollstat_s = "collide";
};

instance spellfx_explosion_trail_key_collide(c_particlefxemitkey)
{
	emtrjeasevel = 1e-006;
};

instance spellfx_explosivearrow(cfx_base_proto)
{
	visname_s = "mfx_firefist_collide";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "ognisko";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "mfx_massdeath_target";
};

instance  spellfx_explosivearrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_explosivearrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_explosivearrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_explosivebolt (cfx_base_proto)
{    	visname_s  =  "explosive_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_explosivebolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_explosivebolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_explosivebolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance spellfx_extricate(cfx_base_proto)
{
	visname_s = "mfx_extricate_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emfxinvestorigin_s = "spellfx_extricate_buildup";
};

instance  spellfx_extricate2 (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emfxinvestorigin_s  =  "spellfx_extricate2_buildup";
};

instance  spellfx_extricate2_buildup (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_buildup";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_extricate2_prerumble";
};

instance  spellfx_extricate2_cast (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_circle";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "none";
    	emfxcreate_s  =  "spellfx_extricate2_caster";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "create collide";
    	emfxcolldyn_s  =  "spellfx_extricate2_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_extricate_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
};

instance  spellfx_extricate2_caster (cfx_base_proto)
{    	visname_s  =  "";
    	sfxid  =  "mfx_fireball_collide4";
    	emfxcreate_s  =  "spellfx_extricate2_rumble";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_extricate2_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_target";
};

instance  spellfx_extricate2_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_extricate_init";
    	emcreatefxid  =  "spellfx_extricate2_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_extricate2_prerumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "500";
    	userstring[1]  =  "0";
    	userstring[2]  =  "4 4 4";
};

instance  spellfx_extricate2_rumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "1";
    	userstring[2]  =  "7 7 7";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_extricateinvisible (cfx_base_proto)
{    	visname_s  =  "mfx_extricateinvisible_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emfxinvestorigin_s  =  "spellfx_extricateinvisible_buildup";
};

instance  spellfx_extricateinvisible_buildup (cfx_base_proto)
{    	visname_s  =  "mfx_extricateinvisible_buildup";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_extricateinvisible_prerumble";
    	sfxid  =  "mfx_extricate_inhale";
};

instance  spellfx_extricateinvisible_cast (cfx_base_proto)
{    	visname_s  =  "mfx_extricateinvisible_cast";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "none";
    	emfxcreate_s  =  "spellfx_extricateinvisible_caster";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "create collide";
    	emfxcolldyn_s  =  "spellfx_extricateinvisible_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_extricateinvisible_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
};

instance  spellfx_extricateinvisible_caster (cfx_base_proto)
{    	visname_s  =  "";
    	sfxid  =  "mfx_fireball_collide4";
    	emfxcreate_s  =  "spellfx_extricateinvisible_rumble";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_extricateinvisible_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_target";
    	sfxid  =  "mfx_extricate_collide";
};

instance  spellfx_extricateinvisible_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_extricateinvisible_init";
    	emcreatefxid  =  "spellfx_extricateinvisible_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_extricateinvisible_prerumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "500";
    	userstring[1]  =  "0";
    	userstring[2]  =  "4 4 4";
};

instance  spellfx_extricateinvisible_rumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "1";
    	userstring[2]  =  "7 7 7";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_extricateinvisible_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance spellfx_extricate_buildup(cfx_base_proto)
{
	visname_s = "mfx_extricate_buildup";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emfxcreate_s = "spellfx_extricate_prerumble";
	sfxid = "mfx_extricate_inhale";
};

instance spellfx_extricate_cast(cfx_base_proto)
{
	visname_s = "mfx_extricate_cast";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "none";
	emfxcreate_s = "spellfx_extricate_caster";
	emfxcreatedowntrj = 1;
	emactioncolldyn_s = "createcollide";
	emfxcolldyn_s = "spellfx_extricate_collidedynfx";
	emfxcolldynperc_s = "spellfx_extricate_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

instance spellfx_extricate_caster(cfx_base_proto)
{
	visname_s = "";
	sfxid = "mfx_fireball_collide4";
	emfxcreate_s = "spellfx_extricate_rumble";
	emfxcreatedowntrj = 1;
};

instance spellfx_extricate_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_windfist_target";
	sfxid = "mfx_extricate_collide";
};

instance spellfx_extricate_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_extricate_init";
	emcreatefxid = "spellfx_extricate_cast";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_extricate_prerumble(cfx_base_proto)
{
	visname_s = "earthquake.eqk";
	userstring[0] = "500";
	userstring[1] = "0";
	userstring[2] = "444";
};

instance  spellfx_extricate_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance spellfx_extricate_rumble(cfx_base_proto)
{
	visname_s = "earthquake.eqk";
	userstring[0] = "1000";
	userstring[1] = "1";
	userstring[2] = "777";
	emfxcreatedowntrj = 1;
};

instance spellfx_extricate_sendperception(cfx_base_proto)
{
	visname_s = "";
	sendassessmagic = 1;
};

instance  spellfx_extricate_tarses (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emfxinvestorigin_s  =  "spellfx_extricate_tarses_buildup";
};

instance  spellfx_extricate_tarses_buildup (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_buildup";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_extricate_tarses_prerumble";
    	sfxid  =  "mfx_extricate_inhale";
};

instance  spellfx_extricate_tarses_cast (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_tarses_cast";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "none";
    	emfxcreate_s  =  "spellfx_extricate_tarses_caster";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "create collide";
    	emfxcolldyn_s  =  "spellfx_extricate_tarses_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_extricate_tarses_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
};

instance  spellfx_extricate_tarses_caster (cfx_base_proto)
{    	visname_s  =  "";
    	sfxid  =  "mfx_fireball_collide4";
    	emfxcreate_s  =  "spellfx_extricate_tarses_rumble";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_extricate_tarses_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_target";
    	sfxid  =  "mfx_extricate_collide";
};

instance  spellfx_extricate_tarses_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_extricate_init";
    	emcreatefxid  =  "spellfx_extricate_tarses_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_extricate_tarses_prerumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "500";
    	userstring[1]  =  "0";
    	userstring[2]  =  "4 4 4";
};

instance  spellfx_extricate_tarses_rumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "1";
    	userstring[2]  =  "7 7 7";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_extricate_tarses_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance spellfx_f1(cfx_base_proto)
{
	visname_s = "fire_torch_fire";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_rpfx01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "firesmall";
};

instance spellfx_f2(cfx_base_proto)
{
	visname_s = "fire_torch_fire";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_lpfx01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "firesmall";
};

instance  spellfx_fackel (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_fackel_collidefx";
    	emfxcolldyn_s  =  "spellfx_fackel_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "firesmall";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_fackel_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_fackel_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_fackel_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_firebolt_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "torch_enlight";
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_fackel_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "torch_enlight";
};

instance  spellfx_fackel_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firebolt_init";
    	lightrange  =  0.001;
};

instance  spellfx_fackel_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_fakearrow (cfx_base_proto)
{    	visname_s  =  "mfx_fakearrow_cast_neu";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_fakearrow_collide";
    	emfxcolldyn_s  =  "spellfx_fakearrow_collide";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emcheckcollision  =  1;
    	emtrjeasevel  =  1800.0;
};

instance  spellfx_fakearrow_collide (cfx_base_proto)
{    	visname_s  =  "mfx_fakearrow_stuck";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxlifespan  =  5.0;
};

instance  spellfx_fakearrow_impact (cfx_base_proto)
{    	visname_s  =  "mfx_fakearrow_cast_neu";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_fakearrow_impact_collide";
    	emfxcolldyn_s  =  "spellfx_fakearrow_impact_collide";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emcheckcollision  =  1;
    	emtrjeasevel  =  1800.0;
};

instance  spellfx_fakearrow_impact_collide (cfx_base_proto)
{    	visname_s  =  "gfa_impact";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxlifespan  =  5.0;
};

instance  spellfx_fakearrow_impact_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "bowshoot";
};

instance  spellfx_fakearrow_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "bowshoot";
};

instance  spellfx_fakefocus_l (cfx_base_proto)
{    	visname_s  =  "mfx_fakefocus_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "zs_lefthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  600.0;
};

instance  spellfx_fakefocus_m (cfx_base_proto)
{    	visname_s  =  "mfx_fakefocus_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  600.0;
};

instance  spellfx_fakefocus_r (cfx_base_proto)
{    	visname_s  =  "mfx_fakefocus_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  600.0;
};

instance spellfx_fear_face(cfx_base_proto)
{
	emtrjmode_s = "FIXED";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "Bip01 Head";
	emtrjdynupdatedelay = 10000;
	lightpresetname = "redambience";
	sfxid = "mfx_fear_cast";
	sfxisambient = 1;
	visname_s = "mfx_fear_face";
	emfxcreate_s = "spellfx_fear_wave";
};

instance spellfx_fear_wave(cfx_base_proto)
{
	visname_s = "mfx_fear_wave";
	emtrjoriginnode = "bip01";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_fear_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

instance spellfx_fireball(cfx_base_proto)
{
	visname_s = "mfx_fireball_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collideCREATEONCEcreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_fireball_collide";
	emfxcolldyn_s = "spellfx_fireball_sendperception";
	emfxcollstatalign_s = "COLLISIONNORMAL";
	emfxcreatedowntrj = 0;
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100100";
	userstring[2] = "mul";
	lightpresetname = "firesmall";
};

instance spellfx_fireball_collide(cfx_base_proto)
{
	visname_s = "mfx_fireball_collide1";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	lightpresetname = "firesmall";
};

instance spellfx_fireball_collide_key_invest_1(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide1";	sfxid = "mfx_fireball_collide1";};

instance spellfx_fireball_collide_key_invest_2(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide2";	sfxid = "mfx_fireball_collide2";};

instance spellfx_fireball_collide_key_invest_3(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide3";	sfxid = "mfx_fireball_collide3";};

instance spellfx_fireball_collide_key_invest_4(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide4";	sfxid = "mfx_fireball_collide4";};

instance spellfx_fireball_invest_blast1(cfx_base_proto)
{
	visname_s = "mfx_fireball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest1";
	sfxisambient = 1;
	visalpha = 0.3;
};

instance spellfx_fireball_invest_blast2(cfx_base_proto)
{
	visname_s = "mfx_fireball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest2";
	sfxisambient = 1;
	visalpha = 0.5;
};

instance spellfx_fireball_invest_blast3(cfx_base_proto)
{
	visname_s = "mfx_fireball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest3";
	sfxisambient = 1;
	visalpha = 0.8;
};

instance spellfx_fireball_invest_blast4(cfx_base_proto)
{
	visname_s = "mfx_fireball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_fireball_invest4";
	sfxisambient = 1;
	visalpha = 1;
};

instance spellfx_fireball_key_cast(c_particlefxemitkey)
{
	lightrange = 200;
	visname_s = "mfx_fireball_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400.;
	sfxid = "mfx_fireball_cast";
	sfxisambient = 1;
	emcheckcollision = 1;
};

instance spellfx_fireball_key_collide(c_particlefxemitkey)
{
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 1e-006;
};

instance spellfx_fireball_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_fireball_init";
	lightrange = 0.01;
};

instance spellfx_fireball_key_invest_1(c_particlefxemitkey)
{
	visname_s = "mfx_fireball_invest";
	emcreatefxid = "spellfx_fireball_invest_blast1";
	lightrange = 150;
	sfxid = "mfx_fireball_invest1";
	sfxisambient = 1;
};

instance spellfx_fireball_key_invest_2(c_particlefxemitkey)
{
	visname_s = "mfx_fireball_invest_l2";
	emcreatefxid = "spellfx_fireball_invest_blast2";
	sfxid = "mfx_fireball_invest2";
	sfxisambient = 1;
};

instance spellfx_fireball_key_invest_3(c_particlefxemitkey)
{
	visname_s = "mfx_fireball_invest_l3";
	emcreatefxid = "spellfx_fireball_invest_blast3";
	sfxid = "mfx_fireball_invest3";
	sfxisambient = 1;
};

instance spellfx_fireball_key_invest_4(c_particlefxemitkey)
{
	visname_s = "mfx_fireball_invest_l4";
	emcreatefxid = "spellfx_fireball_invest_blast4";
	sfxid = "mfx_fireball_invest4";
	sfxisambient = 1;
};

instance spellfx_fireball_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_fireball_sendperception(cfx_base_proto)
{
	visname_s = "mfx_fireball_collide1";
	visalpha = 1;
	emtrjoriginnode = "bip01";
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sendassessmagic = 1;
};

instance spellfx_fireball_sendperception_key_invest_1(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide1";	sfxid = "mfx_fireball_collide1";};

instance spellfx_fireball_sendperception_key_invest_2(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide2";	sfxid = "mfx_fireball_collide2";};

instance spellfx_fireball_sendperception_key_invest_3(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide3";	sfxid = "mfx_fireball_collide3";};

instance spellfx_fireball_sendperception_key_invest_4(c_particlefxemitkey)
{	visname_s = "mfx_fireball_collide4";	sfxid = "mfx_fireball_collide4";};

instance spellfx_firebodyy(cfx_base_proto)
{
	visname_s = "fire_body_fire";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "ognisko";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "campfire1";
};

instance  spellfx_firebolt1 (cfx_base_proto)
{    	visname_s  =  "fire_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_firebolt1_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_firebolt1_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firebolt1_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_fireboltwithinstantfireballeffect (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_fireboltwithinstantfireballeffect_collide";
    	emfxcolldyn_s  =  "spellfx_fireboltwithinstantfireballeffect_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_fireboltwithinstantfireballeffect_collide (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_fireboltwithinstantfireballeffect_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_fireboltwithinstantfireballeffect_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_fireboltwithinstantfireballeffect_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_fireboltwithinstantfireballeffect_firecloud (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_ifb_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_fireboltwithinstantfireballeffect_firecloud_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_fireboltwithinstantfireballeffect_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	visname_s  =  "mfx_ifb_pfxtrail";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_fireboltwithinstantfireballeffect_firecloud";
    	emcheckcollision  =  1;
};

instance  spellfx_fireboltwithinstantfireballeffect_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_fireboltwithinstantfireballeffect_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_init";
    	lightrange  =  0.01;
};

instance  spellfx_fireboltwithinstantfireballeffect_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_firebolt_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  1.0;
};

instance spellfx_firebolt_sendperception(cfx_base_proto)
{
	visname_s = "mfx_firebolt_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sendassessmagic = 1;
};

instance spellfx_FIREEXCRICATE (CFX_BASE_PROTO)
{
	 visname_s = "mfx_energyball_wulw_05_init";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emtrjloopmode_s = "none";
	 emtrjeasefunc_s = "LINEAR";
	 emfxinvestorigin_s = "spellfx_FIREEXCRICATE_buildup";
};

/* Made by Risepolak (Xardas17) */

instance spellfx_FIREEXCRICATE_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_energyball_wulw_05_init";
	emcreatefxid = "spellfx_FIREEXCRICATE_cast";
	pfx_ppsisloopingchg = 1;
};


/* Made by Risepolak (Xardas17) */

instance spellfx_FIREEXCRICATE_cast(cfx_base_proto)
{
	visname_s = "MFX_EXPLOSION_FIRE_WULW_01";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "none";
	emfxcreate_s = "spellfx_FIREEXCRICATE_caster";
	emfxcreatedowntrj = 1;
	emactioncolldyn_s = "createcollide";
	emfxcolldyn_s = "spellfx_FIREEXCRICATE_collidedynfx";
	emfxcolldynperc_s = "spellfx_FIREEXCRICATE_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

/* Made by Risepolak (Xardas17) */

instance spellfx_FIREEXCRICATE_sendperception(cfx_base_proto)
{
	visname_s = "";
	sendassessmagic = 1;
};

instance spellfx_FIREEXCRICATE_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_windfist_target";
	sfxid = "mfx_extricate_collide";
};

instance spellfx_FIREEXCRICATE_caster(cfx_base_proto)
{
	visname_s = "";
	sfxid = "mfx_fireball_collide4";
	emfxcreate_s = "spellfx_FIREEXCRICATE_rumble";
	emfxcreatedowntrj = 1;
};


instance spellfx_FIREEXCRICATE_rumble(cfx_base_proto)
{
};

instance spellfx_firefist(cfx_base_proto)
{
	vissize_s = "11";
	emtrjmode_s = "FIXED";
	visalphablendfunc_s = "ADD";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "pellfx_firefist_abyss";
	emfxcreatedowntrj = 0;
	emtrjnumkeys = 7;
	emtrjnumkeysvar = 3;
	emtrjangleelevvar = 5.;
	emtrjangleheadvar = 20.;
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 200000;
	emtrjtargetrange = 100;
	emtrjtargetelev = 1;
	emactioncolldyn_s = "CREATEONCE";
	sfxid = "mfx_massdeath_target";
};

instance spellfx_firefist_abyss(cfx_base_proto)
{
	visname_s = "mfx_firefist_cast";
	emactioncolldyn_s = "collideCREATEONCE";
	emactioncollstat_s = "collidecreate";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxcollstat_s = "spellfx_firefist_collidefx";
	emfxcolldyn_s = "spellfx_firefist_collidedynfx";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjmode_s = "targetsplinerandom";
	visalphablendfunc_s = "ADD";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_massdeath_target";
};

instance spellfx_firefist_abyss_key_cast(c_particlefxemitkey)
{
	emcheckcollision = 1;
	sfxid = "fireoutlet1";
	sfxid = "mfx_massdeath_target";
};

instance spellfx_firefist_abyss_key_collide(c_particlefxemitkey)
{
	visname_s = "";
	emtrjeasevel = 0.000001;
	sfxid = "mfx_massdeath_target";
};

instance spellfx_firefist_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_firefist_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	visalphablendfunc_s = "ADD";
	sfxid = "mfx_massdeath_target";
	sfxisambient = 1;
};

instance spellfx_firefist_collidefx(cfx_base_proto)
{
	visname_s = "mfx_firefist_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	visalphablendfunc_s = "ADD";
	sfxid = "mfx_massdeath_target";
	sfxisambient = 1;
};

instance spellfx_firefist_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_firefist_abyss";
	sfxid = "mfx_massdeath_target";
	sfxid = "mfx_massdeath_target";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	lightrange = 200;
	emcheckcollision = 1;
	sfxid = "mfx_massdeath_target";
};

instance spellfx_firefist_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_firefist_init";
	lightrange = 0.001;
	sfxid = "mfx_massdeath_target";
};

instance spellfx_firefist_key_open(c_particlefxemitkey)
{
	lightrange = 0.001;
	sfxid = "mfx_massdeath_target";
};

instance  spellfx_firemagestaff_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_firemeatbug (cfx_base_proto)
{    	visname_s  =  "mfx_dragonlocation_fire";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_firemouthprojectile (cfx_base_proto)
{    	visname_s  =  "mfx_firespit_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_mouth";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_firemouthprojectile_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_firemouthprojectile_invest";
};

instance  spellfx_firemouthprojectile_invest (cfx_base_proto)
{    	visname_s  =  "mfx_firespit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_firemouthprojectile_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_firespit_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_firemouthprojectile_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firemouthprojectile_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firemouthprojectile_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_firespit_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_firerain_00 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_00_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_00_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_00_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_00_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_01 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_01_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_01_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_01_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_01_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_02 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_02_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_02_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_02_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_02_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_03 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_03_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_03_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_03_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_03_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_04 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_04_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_04_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_04_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_04_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_05 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_05_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_05_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_05_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_05_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_06 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_06_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_06_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_06_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_06_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_07 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_07_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_07_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_07_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_07_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_08 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_08_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_08_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_08_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_08_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_09 (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_firerain_investglow";
};

instance  spellfx_firerain_09_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firerain_09_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firerain_09_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_rain_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_firerain_09_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_firerain_screenblend (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "255 88 14 100";
    	userstring[2]  =  "3";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  10.0;
};

instance  spellfx_fireshield (cfx_base_proto)
{    	visname_s  =  "fire_sword";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_fireskull (cfx_base_proto)
{    	visname_s  =  "mfx_skull_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_fireskull_fountain (cfx_base_proto)
{    	visname_s  =  "mfx_lacerate_fountain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_geyser_fountain";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_fireskull_earthquake";
};

instance  spellfx_fireskull_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_fireskull_skull";
    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_skull_cast";
    	sfxisambient  =  1;
};

instance  spellfx_fireskull_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_fireskull_skull (cfx_base_proto)
{    	visname_s  =  "mfx_fireskull_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_fireskull_fountain";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_fireskull_skull_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_skull_fly";
};

instance spellfx_firespell_humanburn(cfx_base_proto)
{
	emtrjoriginnode = "bip01fire";
	visname_s = "mfx_firespell_humanburn";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0.;
	emadjustshptoorigin = 1;
};

instance  spellfx_firestormnosound_collide (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide3";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_firestorm_spreadnosound (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestormnosound_collide";
};

instance  spellfx_firestorm_spreadnosound_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firestorm_spreadnosound_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firestorm_spread_00 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_firestorm_spread_00_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firestorm_spread_00_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firestorm_spread_01 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_firestorm_spread_01_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firestorm_spread_01_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firestorm_spread_02 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_firestorm_spread_02_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firestorm_spread_02_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firestorm_spread_03 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_firestorm_spread_03_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firestorm_spread_03_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firestorm_spread_04 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_firestorm_spread_04_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firestorm_spread_04_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firestorm_spread_05 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_firestorm_spread_05_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firestorm_spread_05_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_fireswordgreen (cfx_base_proto)
{    	visname_s  =  "fire_swordgreen";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_firesword_kasdeja (cfx_base_proto)
{    	visname_s  =  "fire_sword_kasdeja";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_firesword_kasdeja2 (cfx_base_proto)
{    	visname_s  =  "fire_sword_kasdeja";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance spellfx_firetorch(cfx_base_proto)
{
	visname_s = "fire_torch_fire";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_helmet";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "ognisko";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "campfire1";
};

instance spellfx_firetorch1(cfx_base_proto)
{
	visname_s = "fire_torch_fire";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "ognisko";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "campfire1";
};

instance  spellfx_firewall (cfx_base_proto)
{    	visname_s  =  "mfx_thunderstorm_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_thunderstorm_flash";
    	sfxid  =  "mfx_thunderstorm_icerain";
    	sfxisambient  =  1;
};

instance  spellfx_firewavespell_invest (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_firewave_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_firewave_00 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_00_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_00";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_00_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_00_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_00_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_00_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_01 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_01_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_01_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_01_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_01_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_01_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_02 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_02_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_02";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_02_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_02_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_02_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_02_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_03 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_03_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_03";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_03_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_03_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_03_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_03_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_04 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_04_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_04";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_04_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_04_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_04_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_04_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_05 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_05_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_05";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_05_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_05_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_05_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_05_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_06 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_06_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_06";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_06_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_06_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_06_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_06_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_07 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_07_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_07";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_07_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_07_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_07_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_07_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_08 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_08_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_08";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_08_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_08_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_08_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_08_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_09 (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_firewave_09_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_09";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxcreate_s  =  "spellfx_firewave_ground";
    	emfxlifespan  =  1.2;
};

instance  spellfx_firewave_09_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firewave_09_explosion";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_firewave_09_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_init";
};

instance  spellfx_firewave_09_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_firewave_righthand";
};

instance  spellfx_firewave_initglow (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init_glow";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreatedowntrj  =  0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
};

instance  spellfx_firewave_lefthandlong (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emfxlifespan  =  4.0;
};

instance  spellfx_firewave_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  2.5;
};

instance  spellfx_firewave_righthandlong (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  4.0;
};

instance  spellfx_firewave_spread (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_meteorbullet_collide";
};

instance  spellfx_firewave_spread_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_firewave_spread_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_firewave_target (cfx_base_proto)
{    	visname_s  =  "mfx_firewave_target";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_firewave_target";
    	sendassessmagic  =  1;
};

instance spellfx_firewave_wave(cfx_base_proto)
{
	visname_s = "mfx_firewave_wave";
	emtrjoriginnode = "zs_righthand";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_firespell_target";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

instance spellfx_firewave_wave_key_cast(c_particlefxemitkey)
{
	lightrange = 200;
};

instance spellfx_firewave_wave_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_firewave_wave_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance  spellfx_fireweapon (cfx_base_proto)
{    	visname_s  =  "fire_ds_weapon";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_fire_50UP (CFX_BASE_PROTO)
{
	 visname_s = "fire_50UP";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "none";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIRELARGE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "000";
	 secsperdamage = -1;
};

/* Made by Risepolak (Xardas17) */















instance  spellfx_fire_bolt (cfx_base_proto)
{    	visname_s  =  "fire_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_fire_bolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_fire_bolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  300.0;
};

instance  spellfx_fire_bolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  400.0;
};

instance  spellfx_fire_ring (cfx_base_proto)
{    	visname_s  =  "mfx_firering_fadeout";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_fire_ring_elementalorc (cfx_base_proto)
{    	visname_s  =  "mfx_firering_fadeout_long";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance spellfx_fire_shield (CFX_BASE_PROTO)
{
	 visname_s = "mfx_fire_shield_init";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_fire_shield_active";
	 lightpresetname = "FIRE";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_fire_shield_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */





instance spellfx_fire_shield_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "FIRELARGE";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_fire_shield_active_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_fire_shield";
	lightrange = 400;
	sfxid = "mfx_arcanemissile_cast01";
	sfxisambient = 1;
	emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_fire_shield_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance  spellfx_flameguardian (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_flameguardianbolt (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardianbolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_flameguardianbolt_collidefx";
    	emfxcolldyn_s  =  "spellfx_flameguardianbolt_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "firesmall";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_flameguardianbolt_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_flameguardianbolt_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "torch_enlight";
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_flameguardianbolt_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "torch_enlight";
};

instance  spellfx_flameguardianbolt_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_flameguardianbolt_init";
    	lightrange  =  0.001;
};

instance  spellfx_flameguardianbolt_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_flameguardian_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_flameguardian_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_flameguardian_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_flameguardian_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_flameguardian_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_flameguardian_particles_00 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_01 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_02 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_03 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_04 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_05 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_06 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_06";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_07 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_07";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_08 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_08";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_particles_09 (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_particles_09";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_flameguardian_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_flameguardian_target (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_dest";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjeasevel  =  6000.0;
};

instance  spellfx_flamesword (cfx_base_proto)
{    	visname_s  =  "fire_sword_flame";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_forgewheelsvisibility (cfx_base_proto)
{    	visname_s  =  "mfx_charm_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_forgewheelsvisibility_target";
};

instance  spellfx_forgewheelsvisibility_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_charm_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_forgewheelsvisibility_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_charm_init";
};

instance  spellfx_forgewheelsvisibility_origin (cfx_base_proto)
{    	visname_s  =  "mfx_charm_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_forgewheelsvisibility_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "mfx_charm_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_freeze (cfx_base_proto)
{    	visname_s  =  "mfx_icespell_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_freeze_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_freeze_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_icecube_target";
};

instance  spellfx_fury_mageset (cfx_base_proto)
{    	visname_s  =  "mfx_mage_set";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
    	sfxisambient  =  1;
};

instance  spellfx_fury_magic1 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_small";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_fury_magic2 (cfx_base_proto)
{    	visname_s  =  "mfx_fury_magic";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_fury_mercset (cfx_base_proto)
{    	visname_s  =  "mfx_merc_set";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
    	sfxisambient  =  1;
};

instance  spellfx_fury_palset (cfx_base_proto)
{    	visname_s  =  "mfx_pal_set";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
    	sfxisambient  =  1;
};

instance  spellfx_geister (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_invisibleprojectile";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_geisterspell (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "pingpong_once";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_suckenergy_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_suckenergy_invest";
};

instance  spellfx_geisterspell_bloodfly (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_flytoplayer";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_geisterspell_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_geisterspell_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_geisterspell_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_geisterspell_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_geisterspell_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_geisterspell_slowtime (cfx_base_proto)
{    	emfxtriggerdelay  =  6.0;
    	emfxlifespan  =  30.0;
    	visname_s  =  "morph.fov";
    	userstring  =  "0.8";
    	userstring[1]  =  "1.0";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
};

instance  spellfx_geister_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_getteleported (cfx_base_proto)
{    	visname_s  =  "waterfx";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_ghostarmor (cfx_base_proto)
{    	visname_s  =  "mfx_ghostarmor_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjnumkeys  =  5;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjloopmode_s  =  "none";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "aura";
    	emfxinvestorigin_s  =  "spellfx_ghostarmor_origin";
};

instance  spellfx_ghostarmor_curse (cfx_base_proto)
{    	visname_s  =  "mfx_ghostarmor_curse";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  20.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emfxcollstat_s  =  "spellfx_zap_collide";
    	emfxcolldyn_s  =  "spellfx_zap_collidedynfx";
    	emtrjeasevel  =  900.0;
};

instance  spellfx_ghostarmor_humanoid (cfx_base_proto)
{    	visname_s  =  "green_ghost_particles";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "poison";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_ghostarmor_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "target line";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
};

instance  spellfx_ghostarmor_key_init (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_ghostarmor_key_open (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_ghostarmor_origin (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_ghostarmor_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_ghostarmor_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_ghostarmor_wolf (cfx_base_proto)
{    	visname_s  =  "green_ghost_particles";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "poison";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_ghostarmor_wolf_pink (cfx_base_proto)
{    	visname_s  =  "pink_ghost_particles";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "poison";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_ghost_dream (cfx_base_proto)
{    	visname_s  =  "ghost_model_dream";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_giftanschlag (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_chargezap_collide";
    	emfxcolldyn_s  =  "spellfx_chargezap_collide";
    	emfxcolldynperc_s  =  "spellfx_thunderspell_sendperception";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "aura";
};

instance  spellfx_giftanschlag_collide (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_giftanschlag_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide1";
    	sfxid  =  "mfx_thunderball_collide1";
};

instance  spellfx_giftanschlag_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide2";
    	sfxid  =  "mfx_thunderball_collide2";
};

instance  spellfx_giftanschlag_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide3";
    	sfxid  =  "mfx_thunderball_collide3";
};

instance  spellfx_giftanschlag_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide4";
    	sfxid  =  "mfx_thunderball_collide4";
};

instance  spellfx_giftanschlag_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_giftanschlag_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_giftanschlag_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_giftanschlag_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_giftanschlag_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	visname_s  =  "mfx_thunderball_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_thunderball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_giftanschlag_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_giftanschlag_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_init";
    	lightrange  =  0.01;
};

instance  spellfx_giftanschlag_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest";
    	emcreatefxid  =  "spellfx_chargezap_invest_blast1";
    	lightrange  =  50.0;
    	sfxid  =  "mfx_thunderball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_giftanschlag_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest_l2";
    	emcreatefxid  =  "spellfx_chargezap_invest_blast2";
    	sfxid  =  "mfx_thunderball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_giftanschlag_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest_l3";
    	emcreatefxid  =  "spellfx_chargezap_invest_blast3";
    	sfxid  =  "mfx_thunderball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_giftanschlag_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest_l4";
    	emcreatefxid  =  "spellfx_chargezap_invest_blast4";
    	sfxid  =  "mfx_thunderball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_giftanschlag_key_open (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_init";
    	lightrange  =  0.01;
};

instance  spellfx_giftteppich (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "moos";
};

instance  spellfx_giftteppich_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_giftteppich_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_giftteppich_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_giftteppich_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_glb_innoslight_spread (cfx_base_proto)
{    	visname_s  =  "mfx_glb_innoslight_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetnode  =  "bip01";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_glb_soul (cfx_base_proto)
{    	visname_s  =  "mfx_glb_soul_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_glb_soul_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_glb_soul_cast";
    	emtrjmode_s  =  "follow target";
    	lightpresetname  =  "firesmall";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetnode  =  "bip01";
    	emtrjtargetrange  =  10.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  1.0;
    	emselfrotvel_s  =  "100 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  150.0;
};

instance  spellfx_glb_soul_arrow_spread (cfx_base_proto)
{    	visname_s  =  "fire_glb_soul_fire";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetnode  =  "bip01";
    	emtrjtargetrange  =  10.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "100 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  150.0;
    	emflygravity  =  0.1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_glb_soul_arrow_spread_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_skull_fly";
};

instance  spellfx_glb_soul_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_glb_soul_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_skull_collide";
    	lightpresetname  =  "redambience";
};

instance  spellfx_glb_soul_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_skull_skull";
    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_skull_cast";
    	sfxisambient  =  1;
};

instance  spellfx_glb_soul_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_glb_soul_soul (cfx_base_proto)
{    	visname_s  =  "mfx_glb_soul_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetnode  =  "bip01 spine2";
    	emtrjtargetrange  =  10.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  0.5;
    	emselfrotvel_s  =  "100 100 100";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  150.0;
};

instance  spellfx_glb_soul_soul_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_skull_fly";
};

instance  spellfx_glb_soul_spread (cfx_base_proto)
{    	visname_s  =  "mfx_glb_soul_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_glb_soul_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_glowworms_crystalinvisibiility (cfx_base_proto)
{    	visname_s  =  "glowworms_crystalinvisibility";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_glowworms_ghostarmor (cfx_base_proto)
{    	visname_s  =  "glowworms_ghostarmor";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_glowworms_verjuengung (cfx_base_proto)
{    	visname_s  =  "glowworms_small_verjuengung";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_golem(cfx_base_proto)
{
	visname_s = "mfx_summondemon_init";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	lightpresetname = "redambience";
	emfxinvestorigin_s = "spellfx_demon_invest";
};

instance  spellfx_golemchargefireball (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_golemchargefireball_collide";
    	emfxcolldyn_s  =  "spellfx_golemchargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_golemchargefireball_collide (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_golemchargefireball_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_golemchargefireball_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_golemchargefireball_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide2";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_golemchargefireball_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide3";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_golemchargefireball_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide4";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_golemchargefireball_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_golemchargefireball_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_golemchargefireball_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_golemchargefireball_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_golemchargefireball_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_golemchargefireball_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_golemchargefireball_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_golemchargefireball_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_chargefb_investblast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_golemchargefireball_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_golemchargefireball_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_golemchargefireball_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_golemchargefireball_key_invest_1 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_golemchargefireball_invest_blast1";
    	visname_s  =  "mfx_chargefb_cast_l2";
    	lightrange  =  150.0;
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_golemchargefireball_key_invest_2 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_golemchargefireball_invest_blast2";
    	visname_s  =  "mfx_chargefb_cast_l3";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_golemchargefireball_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_golemchargefireball_invest_blast3";
    	visname_s  =  "mfx_chargefb_cast_l4";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_golemchargefireball_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_golemchargefireball_invest_blast4";
    	visname_s  =  "mfx_chargefb_cast_l5";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_golemchargefireball_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_golemgeyser (cfx_base_proto)
{    	visname_s  =  "mfx_geyser_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_golemgeyser_fountain";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "aura";
};

instance  spellfx_golemgeyser_fountain (cfx_base_proto)
{    	visname_s  =  "mfx_geyser_fountain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_geyser_fountain";
    	sfxisambient  =  1;
};

instance  spellfx_golemgeyser_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_geyser_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_geyser_rumble";
    	sfxisambient  =  1;
};

instance  spellfx_golemgeyser_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_golemgeyser_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_golemgeyser_key_invest (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_golemgeyser_rumble";
};

instance  spellfx_golemgeyser_rumble (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_geyser_rumble";
    	sfxisambient  =  1;
};

instance  spellfx_golemicecube (cfx_base_proto)
{    	visname_s  =  "mfx_golemicecube_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_golemicecube_collide";
    	emfxcolldynperc_s  =  "spellfx_icespell_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_icespell_invest";
    	lightpresetname  =  "aura";
};

instance  spellfx_golemicecube_collide (cfx_base_proto)
{    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_golemicecube_collide";
};

instance  spellfx_golemicecube_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_golemicecube_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_golemicecube_cast";
    	sfxisambient  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_golemicecube_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_golemicecube_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_golemicecube_init";
    	lightrange  =  0.01;
    	scaleduration  =  0.5;
};

instance  spellfx_golemicecube_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_golemwindfist (cfx_base_proto)
{    	visname_s  =  "mfx_golemwindfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_golemwindfist_collidedynfx";
    	emfxinvestorigin_s  =  "spellfx_golemwindfist_invest";
};

instance  spellfx_golemwindfist_cast (cfx_base_proto)
{    	visname_s  =  "mfx_golemwindfist_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_golemwindfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_golemwindfist_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_golemwindfist_collide";
    	sendassessmagic  =  1;
};

instance  spellfx_golemwindfist_invest (cfx_base_proto)
{    	visname_s  =  "mfx_golemwindfist_invest";
    	sfxid  =  "mfx_golemwindfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_golemwindfist_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_golemwindfist_invest_blast";
    	sfxid  =  "mfx_golemwindfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_golemwindfist_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_golemwindfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_golemwindfist_cast";
};

instance  spellfx_golemwindfist_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance spellfx_golem_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
	lightrange = 200;
};

instance spellfx_golem_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_golem_key_invest_1(c_particlefxemitkey)
{	lightrange = 400;};

instance spellfx_golem_key_invest_2(c_particlefxemitkey)
{};

instance spellfx_golem_key_invest_3(c_particlefxemitkey)
{	emcreatefxid = "fx_earthquake";};

instance spellfx_golem_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance  spellfx_greenboom (cfx_base_proto)
{    	visname_s  =  "swampdrone_explode2";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "BLEND";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_greenboom_big (cfx_base_proto)
{    	visname_s  =  "swampdrone_explode";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "BLEND";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_greenheal_origin(cfx_base_proto)
{
	visname_s = "mfx_heal_greenheavenlight";
	emtrjoriginnode = "bip01";
	visalpha = 1;
	emfxcreate_s = "spellfx_greenheal_start";
	emtrjmode_s = "FIXED";
	lightpresetname = "aura";
};

instance spellfx_greenheal_start(cfx_base_proto)
{
	visname_s = "mfx_heal_start";
	sfxid = "mfx_greenheal_cast";
	sfxisambient = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01rfoot";
};

instance  spellfx_greenpotion (cfx_base_proto)
{    	visname_s  =  "green_potion";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_greenroots (cfx_base_proto)
{    	visname_s  =  "mfx_realgreententacle_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_greenroots_explode";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
};

instance  spellfx_greenroots_explode (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_realgreententacle_burst";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_greententacle_grow";
};

instance  spellfx_greenroots_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_realgreententacle_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_greenroots_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_greenroots_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_greenroots_key_invest (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_greenroots_noise";
};

instance  spellfx_greenroots_noise (cfx_base_proto)
{};

instance  spellfx_greententacle_grow (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_greententacle_sphere";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_greententacle_grow";
};

instance  spellfx_greententacle_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_greententacle_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emfxlifespan  =  2.5;
};

instance  spellfx_greententacle_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_greententacle_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  2.5;
};

instance  spellfx_greententacle_targetfast (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_greententacle_targetfast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_greententacle_grow";
    	sendassessmagic  =  1;
};

instance spellfx_green_shield (CFX_BASE_PROTO)
{
	 visname_s = "mfx_green_shield_init";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_green_shield_active";
	 sfxid = "ALG_WARN";
	 lightpresetname = "DECAL_TELESTORM";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_green_shield_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */





instance spellfx_green_shield_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "DECAL_TELESTORM";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_green_shield_active_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_green_shield";
	lightrange = 400;
	sfxid = "mfx_arcanemissile_cast01";
	sfxisambient = 1;
	emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_green_shield_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_grom(cfx_base_proto)
{
	visname_s = "mfx_grom_init_glow";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_grom_initglow";
	emfxcreatedowntrj = 0;
	sfxid = "mfx_firerain_rain";
};

instance spellfx_grom_ground(cfx_base_proto)
{
	visname_s = "mfx_grom_cast";
	emtrjoriginnode = "bip01rfoot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "redambience";
	sfxid = "mfx_grom_cast";
	sfxid = "mfx_firerain_rain";
	sfxisambient = 1;
};

instance spellfx_grom_initglow(cfx_base_proto)
{
	visname_s = "mfx_grom_init";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	lightpresetname = "redambience";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_grom_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_grom_ground";
	pfx_ppsisloopingchg = 1;
	sfxid = "mfx_firerain_rain";
};

instance spellfx_grom_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_grom_init";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_grom_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
	sfxid = "mfx_firerain_rain";
};

instance  spellfx_hagel (cfx_base_proto)
{    	visname_s  =  "mfx_thunderstorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "fx_earthquake";
};

instance  spellfx_hagel_flash (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	visname_s  =  "mfx_thunderstorm_flashes";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_hagel_screenblend";
    	sfxid  =  "mfx_thunderstorm_thunder";
    	sfxisambient  =  1;
};

instance  spellfx_hagel_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_thunderstorm_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_hagel_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_hagel_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_hagel_rain (cfx_base_proto)
{    	visname_s  =  "mfx_thunderstorm_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_hagel_flash";
    	sfxid  =  "mfx_thunderstorm_icerain";
    	sfxisambient  =  1;
};

instance  spellfx_hagel_screenblend (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "0 0 0 120";
    	userstring[2]  =  "3";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  10.0;
};

instance  spellfx_hand_2_hand_bridge (cfx_base_proto)
{    	visname_s  =  "mfx_ritual_bridge";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "zs_lefthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance spellfx_healother(cfx_base_proto)
{
	visname_s = "mfx_healother_init";
	emtrjoriginnode = "zs_righthand";
	emtrjmode_s = "FIXED";
};

instance spellfx_healotherhigh(cfx_base_proto)
{
	visname_s = "mfx_healother_init";
	emtrjoriginnode = "zs_righthand";
	emtrjmode_s = "FIXED";
};

instance spellfx_healotherhigh_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_healotherhigh_target(cfx_base_proto)
{
	visname_s = "mfx_healother_target";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	sfxid = "mfx_heal_cast";
	sfxisambient = 1;
};

instance spellfx_healothermedium(cfx_base_proto)
{
	visname_s = "mfx_healother_init";
	emtrjoriginnode = "zs_righthand";
	emtrjmode_s = "FIXED";
};

instance spellfx_healothermedium_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_healothermedium_target(cfx_base_proto)
{
	visname_s = "mfx_healother_target";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	sfxid = "mfx_heal_cast";
	sfxisambient = 1;
};

instance spellfx_healother_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_healother_target(cfx_base_proto)
{
	visname_s = "mfx_healother_target";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	sfxid = "mfx_heal_cast";
	sfxisambient = 1;
};

instance  spellfx_healshrine2 (cfx_base_proto)
{    	visname_s  =  "mfx_healshrine";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
};

instance spellfx_HEAL_ORB (CFX_BASE_PROTO)
{
	 visname_s = "MFX_XAR_HEAL_ORB_INIT";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_HEAL_ORB_active";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_HEAL_ORB_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "1HEAVENLIGHT_TRANS";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_HEAL_ORB_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "MFX_XAR_HEAL_ORB";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emcreatefxid = "spellfx_HEAL_ORB_activeS";
	 emtrjeasevel = 1400;
};

instance spellfx_HEAL_ORB_activeS (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 100;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 1.2;
	 lightpresetname = "1HEAVENLIGHT_FIRE";
};

instance spellfx_HEAL_ORB_activeSA (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 100;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.9;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
};


instance spellfx_HEAL_ORB_activeSA_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "MFX_XAR_HEAL_ORB2";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};


instance spellfx_HEAL_ORB_activeS_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "MFX_XAR_HEAL_ORB1";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emcreatefxid = "spellfx_HEAL_ORB_activeSA";
	 emtrjeasevel = 1400;
};


/* Made by Risepolak (Xardas17) */

instance spellfx_HEAL_ORB_activeS_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_HEAL_ORB_activeS_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_HEAL_ORB_activeSA_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_HEAL_ORB_activeSA_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};


instance spellfx_HEAL_ORB_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_HEAL_ORB_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_HEAL_ORB_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_heal_start(cfx_base_proto)
{
	visname_s = "mfx_heal_start";
	sfxid = "mfx_heal_cast";
	sfxisambient = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01rfoot";
};

instance  spellfx_hitbyiceweapon (cfx_base_proto)
{    	visname_s  =  "mfx_icespell_collide_withoutmrk";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_icecube_collide";
};

instance  spellfx_holyrain (cfx_base_proto)
{    	visname_s  =  "mfx_holyrain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_holyrain_investglow";
};

instance  spellfx_holyrainchargefireball_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_holyrainfireball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_holyrainchargefireball_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_holyrainfireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_holyrainchargefireball_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_holyrainfireball_collide2";
    	sfxid  =  "mfx_fireball_collide2";
};

instance  spellfx_holyrainchargefireball_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_holyrainfireball_collide3";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_holyrainchargefireball_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_holyrainfireball_collide4";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_holyrain_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_holyrain_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_holyrain_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_holyrain_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_holyrain_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_holyrain_rain (cfx_base_proto)
{    	visname_s  =  "mfx_holyrain_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_holyrainchargefireball_collidedynfx";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_holyrain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_holyrain_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_holywave (cfx_base_proto)
{    	visname_s  =  "mfx_holywave_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_holywave_initglow";
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_holywave_ground (cfx_base_proto)
{    	visname_s  =  "mfx_holywave_cast";
    	emtrjoriginnode  =  "bip01 r foot";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_holywave_target";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_holywave_cast";
    	sfxisambient  =  1;
};

instance  spellfx_holywave_initglow (cfx_base_proto)
{    	visname_s  =  "mfx_holywave_init_glow";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreatedowntrj  =  0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
};

instance  spellfx_holywave_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_holywave_ground";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_holywave_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_holywave_init";
};

instance  spellfx_holywave_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_holywave_target (cfx_base_proto)
{    	visname_s  =  "mfx_holywave_target";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_holywave_target";
    	sendassessmagic  =  1;
};

instance  spellfx_human_holyshield (cfx_base_proto)
{    	visname_s  =  "druznash_holyshield";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_icearmor (cfx_base_proto)
{    	visname_s  =  "ice_model_kairo";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "aura";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	emfxcreate_s  =  "spellfx_icearmor_smoke";
};

instance  spellfx_icearmor_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_icearmor_smoke (cfx_base_proto)
{    	visname_s  =  "icesmoke_model_kairo";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "aura";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_icearmor_smoke_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance spellfx_icearrow(cfx_base_proto)
{
	visname_s = "ice_arrow";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 2000000;
	emfxlifespan = -1;
	emselfrotvel_s = "000";
	secsperdamage = -1;
	emadjustshptoorigin = 1;
	lightpresetname = "aura";
};

instance spellfx_icearrow_key_invest_1(c_particlefxemitkey)
{
	lightrange = 100;
};

instance spellfx_icearrow_key_invest_2(c_particlefxemitkey)
{
	lightrange = 300;
};

instance spellfx_icearrow_key_invest_3(c_particlefxemitkey)
{
	lightrange = 400;
};

instance  spellfx_iceball (cfx_base_proto)
{    	visname_s  =  "mfx_iceball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_iceball_collide";
    	emfxcolldyn_s  =  "spellfx_iceball_collidedynfx";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_iceball_collide (cfx_base_proto)
{    	visname_s  =  "mfx_iceball_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_iceball_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_iceball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_iceball_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_iceball_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_iceball_firecloud_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_iceball_icecloud (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_ib_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_iceball_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	visname_s  =  "mfx_ib_pfxtrail";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_iceball_icecloud";
    	emcheckcollision  =  1;
};

instance  spellfx_iceball_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "mfx_iceball_collide";
};

instance  spellfx_iceball_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceball_init";
    	lightrange  =  0.01;
};

instance  spellfx_iceball_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_icecubenpconly (cfx_base_proto)
{    	visname_s  =  "mfx_icecube_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_icecubenpconly_collide";
    	emfxcolldynperc_s  =  "spellfx_icespell_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_icespell_invest";
    	lightpresetname  =  "aura";
};

instance  spellfx_icecubenpconly_collide (cfx_base_proto)
{    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_icecube_collide";
};

instance  spellfx_icecubenpconly_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_icecube_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_icecube_cast";
    	sfxisambient  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_icecubenpconly_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_icecubenpconly_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_icecube_init";
    	lightrange  =  0.01;
    	scaleduration  =  0.5;
};

instance  spellfx_icecubenpconly_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance spellfx_ICEEXCRICATE (CFX_BASE_PROTO)
{
	 visname_s = "mfx_energyball_wulw_18_init";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emtrjloopmode_s = "none";
	 emtrjeasefunc_s = "LINEAR";
	 emfxinvestorigin_s = "spellfx_ICEEXCRICATE_buildup";
};

/* Made by Risepolak (Xardas17) */

instance spellfx_ICEEXCRICATE_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_energyball_wulw_18_init";
	emcreatefxid = "spellfx_ICEEXCRICATE_cast";
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */

instance spellfx_ICEEXCRICATE_sendperception(cfx_base_proto)
{
	visname_s = "";
	sendassessmagic = 1;
};

/* Made by Risepolak (Xardas17) */

instance spellfx_ICEEXCRICATE_cast(cfx_base_proto)
{
	visname_s = "MFX_EXPLOSION_ICE_WULW_03";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "none";
	emfxcreate_s = "spellfx_ICEEXCRICATE_caster";
	emfxcreatedowntrj = 1;
	emactioncolldyn_s = "createcollide";
	emfxcolldyn_s = "spellfx_ICEEXCRICATE_collidedynfx";
	emfxcolldynperc_s = "spellfx_ICEEXCRICATE_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_ICEEXCRICATE_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_windfist_target";
	sfxid = "mfx_extricate_collide";
};

instance spellfx_ICEEXCRICATE_caster(cfx_base_proto)
{
	visname_s = "";
	sfxid = "mfx_fireball_collide4";
	emfxcreate_s = "spellfx_ICEEXCRICATE_rumble";
	emfxcreatedowntrj = 1;
};


instance spellfx_ICEEXCRICATE_rumble(cfx_base_proto)
{
};


instance  spellfx_iceexplosionfog (cfx_base_proto)
{    	visname_s  =  "mfx_iceexplosionfog";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  0;
};

instance  spellfx_icelancebig (cfx_base_proto)
{    	visname_s  =  "mfx_adanosprojectile_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_icelancebig_collide";
    	emfxcolldyn_s  =  "spellfx_icelancebig_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_icelancebig_collide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_adanosprojectile_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_destroyundead_collide";
    	sfxisambient  =  1;
};

instance  spellfx_icelancebig_collidedynfx (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_adanosprojectile_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_destroyundead_collide";
    	sfxisambient  =  1;
};

instance  spellfx_icelancebig_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	sfxid  =  "mfx_destroyundead_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_icelancebig_key_init (c_particlefxemitkey)
{};

instance  spellfx_icelancebig_trail (cfx_base_proto)
{    	emtrjeasevel  =  800.0;
    	visname_s  =  "mfx_adanosprojectile_trail";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emcheckcollision  =  1;
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide";
};

instance  spellfx_icelancebig_trail_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_icelance_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_icelance_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  1.0;
};

instance  spellfx_icerainchargefireball_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_icerainfireball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_icerainchargefireball_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_icerainfireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_icerainchargefireball_collidedynfx_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_icerainfireball_collide2";
    	sfxid  =  "mfx_ireball_collide2";
};

instance  spellfx_icerainchargefireball_collidedynfx_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_icerainfireball_collide3";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_icerainchargefireball_collidedynfx_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_icerainfireball_collide4";
    	sfxid  =  "mfx_fireball_collide4";
};

instance  spellfx_icerangedweaponenchantment (cfx_base_proto)
{    	visname_s  =  "mfx_iceweaponenchantment_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_icerangedweaponenchantment_investglow (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_icerangedweaponenchantment_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_icerangedweaponenchantment_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_iceshard (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjeasefunc_s  =  "LINEAR";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcollstat_s  =  "spellfx_iceshard_collidefx";
    	emfxcolldyn_s  =  "spellfx_iceshard_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_iceshards_shard_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "aura";
    	userstring  =  "iceflare.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_iceshardhead (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_iceshard_collidefx";
    	emfxcolldyn_s  =  "spellfx_iceshard_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_iceshards_shard_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "aura";
    	userstring  =  "iceflare.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_iceshardhead_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceshard_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_iceshardhead_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "mfx_icelance_collide";
};

instance  spellfx_iceshardhead_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firebolt_init";
    	lightrange  =  0.001;
};

instance  spellfx_iceshardhead_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_iceshardlefthand (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_iceshard_collidefx";
    	emfxcolldyn_s  =  "spellfx_iceshard_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_iceshards_shard_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "aura";
    	userstring  =  "iceflare.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_iceshardlefthand_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceshard_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_iceshardlefthand_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "mfx_icelance_collide";
};

instance  spellfx_iceshardlefthand_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firebolt_init";
    	lightrange  =  0.001;
};

instance  spellfx_iceshardlefthand_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_iceshards (cfx_base_proto)
{    	visname_s  =  "mfx_icelance_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxcreatedowntrj  =  0;
    	lightpresetname  =  "aura";
};

instance  spellfx_iceshards_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_icelance_cast";
    	sfxisambient  =  1;
};

instance  spellfx_iceshards_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_iceshards_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_iceshards_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_icelance_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emfxlifespan  =  3.0;
};

instance  spellfx_iceshards_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_icelance_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  3.0;
};

instance  spellfx_iceshards_shard_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_iceshard_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceshard_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_iceshard_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "mfx_icelance_collide";
};

instance  spellfx_iceshard_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firebolt_init";
    	lightrange  =  0.001;
};

instance  spellfx_iceshard_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_iceshoot2_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_iceshoot_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_iceshoot_mesheffect";
};

instance  spellfx_iceshoot_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_iceshoot2_arrow";
};

instance  spellfx_iceshoot_mesheffect (cfx_base_proto)
{    	visname_s  =  "ice_weapon_enchantment";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_icespellshort_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_icespellshort_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sendassessmagic  =  1;
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_icecube_target";
};

instance  spellfx_icespellveryshort_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_icespellveryshort_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sendassessmagic  =  1;
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_icecube_target";
};

instance  spellfx_icespell_send (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance spellfx_icespell_target(cfx_base_proto)
{
	visname_s = "mfx_icespell_target";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sendassessmagic = 1;
	emadjustshptoorigin = 1;
	sfxid = "mfx_icecube_target";
};

instance  spellfx_icestorm (cfx_base_proto)
{    	visname_s  =  "mfx_icestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "fx_earthquake";
};

instance  spellfx_icestorm_cloud (cfx_base_proto)
{    	visname_s  =  "mfx_icestorm_cloud";
    	emtrjmode_s  =  "none";
    	emtrjoriginnode  =  "bip01";
    	emfxlifespan  =  12.0;
    	sfxid  =  "mfx_iceball_collide";
    	sfxisambient  =  1;
};

instance  spellfx_icestorm_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_iceball_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_icestorm_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_icestorm_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_icestorm_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_icestorm_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_icestorm_rain (cfx_base_proto)
{    	visname_s  =  "mfx_icestorm_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_icestorm_collidedynfx";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_icestorm_storm";
    	sfxid  =  "mfx_icestorm_storm";
    	sfxisambient  =  1;
    	emfxlifespan  =  12.0;
};

instance  spellfx_icestorm_storm (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	visname_s  =  "mfx_icestorm_strongstorm";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_icestorm_cloud";
    	sfxid  =  "mfx_icestorm_icerain";
    	sfxisambient  =  1;
};

instance  spellfx_icesword (cfx_base_proto)
{    	visname_s  =  "fire_sword_ice";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "ice";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_icesword_attack (cfx_base_proto)
{    	visname_s  =  "ice_sword_attack";
    	emtrjoriginnode  =  "zs_righthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_icesword_hit (cfx_base_proto)
{    	visname_s  =  "ice_sword_hit";
    	emtrjoriginnode  =  "zs_righthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_icesword_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_icesword_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "ice_sword";
    	lightrange  =  100.0;
    	pfx_ppsvalue  =  100.0;
};

instance  spellfx_icesword_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "ice_sword";
    	lightrange  =  300.0;
    	pfx_ppsvalue  =  150.0;
};

instance  spellfx_icesword_key_invest_3 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_icesword_attack";
    	lightrange  =  400.0;
};

instance  spellfx_icesword_key_invest_4 (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_icesword_hit";
    	lightrange  =  600.0;
    	pfx_ppsvalue  =  300.0;
};

instance  spellfx_icesword_key_invest_5 (c_particlefxemitkey)
{    	visname_s  =  "ice_sword";
    	lightrange  =  100.0;
    	pfx_ppsvalue  =  150.0;
};

instance  spellfx_icewave_fake (cfx_base_proto)
{    	visname_s  =  "mfx_icewave_wave";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_icewave_fast_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_icespell4seconds_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sendassessmagic  =  1;
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_icecube_target";
};

instance  spellfx_icewave_rundumschlag (cfx_base_proto)
{    	visname_s  =  "mfx_icewave_rundumschlag";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  " = ";
};

instance  spellfx_icewave_send (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_icewave_wave_fast (cfx_base_proto)
{    	visname_s  =  "mfx_icewave_wave_fast";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_icewave_fast_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_iceweaponenchantment (cfx_base_proto)
{    	visname_s  =  "mfx_iceweaponenchantment_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_iceweaponenchantment_investglow (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_iceweaponenchantment_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_iceweaponenchantment_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_iceweaponenchantment_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_iceweaponenchantment_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_iceweaponenchantment_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_iceweaponenchantment_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_ice_ring_elementalorc (cfx_base_proto)
{    	visname_s  =  "mfx_icering_fadeout_long";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_ice_weapon_enchantment (cfx_base_proto)
{    	visname_s  =  "ice_weapon_enchantment";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_icecube_invest_quiet";
    	sfxisambient  =  1;
};

instance  spellfx_ice_weapon_enchantment_arrow (cfx_base_proto)
{    	visname_s  =  "ice_weapon_enchantment_arrow";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_ice_weapon_ranged_enchantment (cfx_base_proto)
{    	visname_s  =  "ice_weapon_enchantment";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_icecube_invest_quiet";
    	sfxisambient  =  1;
};

instance  spellfx_implosion (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emfxinvestorigin_s  =  "spellfx_implosion_buildup";
};

instance  spellfx_implosion_buildup (cfx_base_proto)
{    	visname_s  =  "mfx_extricate_buildup";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_implosion_prerumble";
    	sfxid  =  "mfx_extricate_inhale";
};

instance  spellfx_implosion_cast (cfx_base_proto)
{    	visname_s  =  "mfx_implosion_cast";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "none";
    	emfxcreate_s  =  "spellfx_implosion_caster";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "create collide";
    	emfxcolldyn_s  =  "spellfx_implosion_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_implosion_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
};

instance  spellfx_implosion_caster (cfx_base_proto)
{    	visname_s  =  "";
    	sfxid  =  "mfx_fireball_collide4";
    	emfxcreate_s  =  "spellfx_implosion_rumble";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_implosion_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_target";
    	sfxid  =  "mfx_extricate_collide";
};

instance  spellfx_implosion_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_extricate_init";
    	emcreatefxid  =  "spellfx_implosion_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_implosion_prerumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "500";
    	userstring[1]  =  "0";
    	userstring[2]  =  "4 4 4";
};

instance  spellfx_implosion_rumble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "1";
    	userstring[2]  =  "7 7 7";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_implosion_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_incovation_black (cfx_base_proto)
{    	visname_s  =  "invocation_black";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "whiteblend";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_incovation_grey (cfx_base_proto)
{    	visname_s  =  "invocation_grey";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "whiteblend";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_incovation_intro (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_intro";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "justwhite";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_incovation_orange (cfx_base_proto)
{    	visname_s  =  "invocation_orange";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "cataclysm";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_incovation_swamp (cfx_base_proto)
{    	visname_s  =  "invocation_swamp";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "redambience";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_incovation_yellow (cfx_base_proto)
{    	visname_s  =  "invocation_yellow";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_innosfire (cfx_base_proto)
{    	visname_s  =  "duch ognia";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_innosfire_collide";
    	emfxcolldyn_s  =  "spellfx_innosfire_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_innosfire_collide (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_innosfire_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_innosfire_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_innosfire_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_innosfire_firecloud (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_ifb_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_innosfire_firecloud_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_innosfire_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	visname_s  =  "mfx_ifb_pfxtrail";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_instantfireball_firecloud";
    	emcheckcollision  =  1;
};

instance  spellfx_innosfire_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_innosfire_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_init";
    	lightrange  =  0.01;
};

instance  spellfx_innosfire_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance spellfx_innospain(cfx_base_proto)
{
	visname_s = "mfx_innospain_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_innospain_collidefx";
	emfxcolldyn_s = "spellfx_innospain_sendperception";
	emtrjtargetrange = 100;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
};

instance spellfx_innospain_collidefx(cfx_base_proto)
{
	visname_s = "mfx_innospain_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "aura";
	sfxid = "mfx_massdeath_target";
};

instance spellfx_innospain_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_innospain_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	lightrange = 200;
	emcheckcollision = 1;
	sfxid = "mfx_massdeath_target";
};

instance spellfx_innospain_key_collide(c_particlefxemitkey)
{
	visname_s = "";
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 1e-006;
	sfxid = "mfx_massdeath_target";
};

instance spellfx_innospain_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_innospain_init";
	sfxid = "mfx_massdeath_target";
	lightrange = 0.001;
};

instance spellfx_innospain_key_open(c_particlefxemitkey)
{
	lightrange = 0.001;
};

instance  spellfx_innosrage (cfx_base_proto)
{    	visname_s  =  "mfx_innosrage_flash";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_innosrage_target_cloud";
    	lightpresetname  =  "justwhite";
    	sfxid  =  "mfx_barriere_shoot";
    	sfxisambient  =  1;
};

instance  spellfx_innosrage_target_cloud (cfx_base_proto)
{    	visname_s  =  "mfx_innosrage_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_innosretribution (cfx_base_proto)
{    	visname_s  =  "innosretribution";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_lightning_dummy";
    	sfxisambient  =  1;
};

instance  spellfx_innosretributionarrow (cfx_base_proto)
{    	visname_s  =  "innosretribution_arrow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_innosretributionarrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_innosretributionarrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_innosretributionarrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_innosretributionbolt (cfx_base_proto)
{    	visname_s  =  "innosretribution_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_innosretributionbolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_innosretributionbolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_innosretributionbolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_instantfireballfororc (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_instantfireballfororc_collide";
    	emfxcolldyn_s  =  "spellfx_instantfireballfororc_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_instantfireballfororc_collide (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_instantfireballfororc_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_instantfireballfororc_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_instantfireballfororc_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_instantfireballfororc_firecloud (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_ifb_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_instantfireballfororc_firecloud_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_instantfireballfororc_key_cast (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	visname_s  =  "mfx_ifb_pfxtrail";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_instantfireballfororc_firecloud";
    	emcheckcollision  =  1;
};

instance  spellfx_instantfireballfororc_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_instantfireballfororc_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_init";
    	lightrange  =  0.01;
};

instance  spellfx_instantfireballfororc_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_instanticeball (cfx_base_proto)
{    	visname_s  =  "mfx_iceball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_instanticeball_collide";
    	emfxcolldyn_s  =  "spellfx_instanticeball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicice";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "iceballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "aura";
};

instance  spellfx_instanticeball_collide (cfx_base_proto)
{    	visname_s  =  "mfx_iceball_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "aura";
};

instance  spellfx_instanticeball_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_iceball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_instanticeball_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_instanticeball_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_instanticeball_firecloud (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_ice_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_instanticeball_firecloud_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_instanticeball_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	visname_s  =  "mfx_ice_pfxtrail";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_instanticeball_firecloud";
    	emcheckcollision  =  1;
};

instance  spellfx_instanticeball_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_instanticeball_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_iceball_init";
    	lightrange  =  0.01;
};

instance  spellfx_instanticeball_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_intro_ritual (cfx_base_proto)
{    	visname_s  =  "mfx_intro_ritual";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_invisibility (cfx_base_proto)
{    	visname_s  =  "mfx_invisibility_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  10000.0;
    	emfxcolldynperc_s  =  "spellfx_invisibility_sendperception";
};

instance  spellfx_invisibility_footsteps_left (cfx_base_proto)
{    	visname_s  =  "mfx_speed_footsteps";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  "bip01 l foot";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_invisibility_footsteps_right (cfx_base_proto)
{    	visname_s  =  "mfx_speed_footsteps";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  "bip01 r foot";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_invisibility_glimmer (cfx_base_proto)
{    	visname_s  =  "weak_glimmer_white";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_invisibility_ground (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  10000.0;
    	sfxid  =  "mfx_fear_cast";
    	sfxisambient  =  1;
};

instance  spellfx_invisibility_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_invisibility_origin";
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_invisibility_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_invisibility_key_open (c_particlefxemitkey)
{    	emtrjeasevel  =  0.0;
};

instance  spellfx_invisibility_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_invisibility_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_invisibility_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sfxid  =  "hammer";
    	sendassessmagic  =  1;
};

instance  spellfx_invisibleprojectilefast (cfx_base_proto)
{    	visname_s  =  "mfx_firebolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "";
    	emfxcolldyn_s  =  "";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "firesmall";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
};

instance  spellfx_invisibleprojectilefast_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_invisibleprojectilefast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "torch_enlight";
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_invisibleprojectilefast_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "torch_enlight";
};

instance  spellfx_invisibleprojectilefast_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_firebolt_init";
    	lightrange  =  0.001;
};

instance  spellfx_invisibleprojectilefast_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_itemglimmer_green (cfx_base_proto)
{    	visname_s  =  "item_glimmer_green";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_itemglimmer_violet (cfx_base_proto)
{    	visname_s  =  "item_glimmer_violet";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_itemstars_green (cfx_base_proto)
{    	visname_s  =  "item_stars_green";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance SPELLFX_item_absorb(CFX_BASE_PROTO)
{
	 visname_s = "item_absorb";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FACKEL";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_ADANOSBALL (CFX_BASE_PROTO)
{
	 visname_s = "item_ADANOSBALL";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "ADANOSBALL";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_ADANOSBALL1 (CFX_BASE_PROTO)
{
	 visname_s = "item_ADANOSBALL";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "ADANOSBALL";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_ADANOSBALL2 (CFX_BASE_PROTO)
{
	 visname_s = "item_ADANOSBALL2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "ADANOSBALL";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_adanosballred (CFX_BASE_PROTO)
{
	 visname_s = "item_adanosballred";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "CZERWONY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_adanosballred1 (CFX_BASE_PROTO)
{
	 visname_s = "item_adanosballred1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "CZERWONY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_adanosballred2 (CFX_BASE_PROTO)
{
	 visname_s = "item_adanosballred2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "CZERWONY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_ARCANEORB (CFX_BASE_PROTO)
{
	 visname_s = "item_ARCANEORB";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "MAGICDUMMY_1";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_ARCANE_BALL(CFX_BASE_PROTO)
{
	 visname_s = "item_ARCANE_BALL";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "MAGICDUMMY_1";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_ARCANE_BOLT(CFX_BASE_PROTO)
{
	 visname_s = "item_ARCANE_BOLT";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "MAGICDUMMY_1";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_ARCANE_STORM(CFX_BASE_PROTO)
{
	 visname_s = "item_ARCANE_STORM";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "MAGICDUMMY_1";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_BELIARSZORN (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_BELIARSZORN";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "CZARNY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_BELIARSZORN1 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_BELIARSZORN1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "CZARNY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_BELIARSZORN2 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_BELIARSZORN2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "CZARNY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_BLOOD_BALL (CFX_BASE_PROTO)
{
	 visname_s = "item_BLOOD_BALL";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIRE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_BLOOD_BALL1 (CFX_BASE_PROTO)
{
	 visname_s = "item_BLOOD_BALL1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIRE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_BLOOD_BALL2 (CFX_BASE_PROTO)
{
	 visname_s = "item_BLOOD_BALL2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIRE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_BLUESUMM (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_BLUESUMM";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_BLUESUMM1 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_BLUESUMM1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIRE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_BLUESUMM2 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_BLUESUMM2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIRE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_castfail (CFX_BASE_PROTO)
{
	 visname_s = "item_castfail";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIOLETOWY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_darkstatsup (CFX_BASE_PROTO)
{
	 visname_s = "item_darkstatsup";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "darkstatsup";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_darkstatsup1 (CFX_BASE_PROTO)
{
	 visname_s = "item_darkstatsup1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "darkstatsup";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_darkstatsup2 (CFX_BASE_PROTO)
{
	 visname_s = "item_darkstatsup2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "darkstatsup";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_edefense (CFX_BASE_PROTO)
{
	 visname_s = "item_edefense";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "NIEBIESKI";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_edefense1 (CFX_BASE_PROTO)
{
	 visname_s = "item_edefense1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "NIEBIESKI";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_edefense2 (CFX_BASE_PROTO)
{
	 visname_s = "item_edefense2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "NIEBIESKI";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_electrowave (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_electrowave";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_electrowave1 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_electrowave1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_electrowave2 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_electrowave2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_GREENTENTACLE (CFX_BASE_PROTO)
{
	 visname_s = "item_GREENTENTACLE";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "darkstatsup";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_GrenSumm (CFX_BASE_PROTO)
{
	 visname_s = "item_GrenSumm";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BQM_MEATBUG";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_GrenSumm1 (CFX_BASE_PROTO)
{
	 visname_s = "item_GrenSumm1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BQM_MEATBUG";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_GrenSumm2 (CFX_BASE_PROTO)
{
	 visname_s = "item_GrenSumm2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BQM_MEATBUG";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_LEAF (CFX_BASE_PROTO)
{
	 visname_s = "item_LEAF";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "darkstatsup";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_LIGHTBOLT (CFX_BASE_PROTO)
{
	 visname_s = "item_LIGHTBOLT";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "DECAL_DEAMON";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_Mage_Armor (CFX_BASE_PROTO)
{
	 visname_s = "item_Mage_Armor";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "DECAL_DEAMON";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_massdot (CFX_BASE_PROTO)
{
	 visname_s = "item_massdot";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIOLETOWY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_massdot1 (CFX_BASE_PROTO)
{
	 visname_s = "item_massdot1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIOLETOWY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_massdot2 (CFX_BASE_PROTO)
{
	 visname_s = "item_massdot2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FIOLETOWY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_MDGREY (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_MDGREY";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BIALAWE_SIATLO";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_MDGREY1 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_MDGREY1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BIALAWE_SIATLO";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_MDGREY2 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_MDGREY2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BIALAWE_SIATLO";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_PYROKINESIS(CFX_BASE_PROTO)
{
	 visname_s = "item_PYROKINESIS";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FACKEL";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_PYROKINESIS1(CFX_BASE_PROTO)
{
	 visname_s = "item_PYROKINESIS1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FACKEL";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_PYROKINESIS2 (CFX_BASE_PROTO)
{
	 visname_s = "item_PYROKINESIS2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "FACKEL";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_REALGREENTENTACLE (CFX_BASE_PROTO)
{
	 visname_s = "item_REALGREENTENTACLE";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "GREENCAVE_500";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_REALGREENTENTACLE1 (CFX_BASE_PROTO)
{
	 visname_s = "item_REALGREENTENTACLE1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "GREENCAVE_500";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_REALGREENTENTACLE2 (CFX_BASE_PROTO)
{
	 visname_s = "item_REALGREENTENTACLE2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "GREENCAVE_500";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_SLEEP (CFX_BASE_PROTO)
{
	 visname_s = "item_SLEEP";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BIALAWE_SIATLO";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_SPELLWATERSTORM (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_SPELLWATERSTORM";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "SPELLWATERSTORM";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_SPELLWATERSTORM1 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_SPELLWATERSTORM1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "SPELLWATERSTORM";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_SPELLWATERSTORM2 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_SPELLWATERSTORM2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "SPELLWATERSTORM";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_Item_stealhealth (CFX_BASE_PROTO)
{
	 visname_s = "Item_stealhealth";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "MFX_FEAR_DEMONFACE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_Item_stealhealth1 (CFX_BASE_PROTO)
{
	 visname_s = "Item_stealhealth1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "MFX_FEAR_DEMONFACE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_Item_stealhealth2 (CFX_BASE_PROTO)
{
	 visname_s = "Item_stealhealth2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "MFX_FEAR_DEMONFACE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_SUCKENERGY(CFX_BASE_PROTO)
{
	 visname_s = "ITEM_SUCKENERGY";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "SUCKENERGY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_SUCKENERGY1 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_SUCKENERGY1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "SUCKENERGY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_ITEM_SUCKENERGY2 (CFX_BASE_PROTO)
{
	 visname_s = "ITEM_SUCKENERGY2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "SUCKENERGY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_Sun (CFX_BASE_PROTO)
{
	 visname_s = "item_Sun";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "GALAXYYELLOW0000";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_TRANSFORM (CFX_BASE_PROTO)
{
	 visname_s = "item_TRANSFORM";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_TRANSFORM1 (CFX_BASE_PROTO)
{
	 visname_s = "item_TRANSFORM1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_TRANSFORM2 (CFX_BASE_PROTO)
{
	 visname_s = "item_TRANSFORM2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "1IFX_MAGIC_SMOKE";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_WINDFIST (CFX_BASE_PROTO)
{
	 visname_s = "item_WINDFIST";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BIALAWE_SIATLO";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_WINDFIST1 (CFX_BASE_PROTO)
{
	 visname_s = "item_WINDFIST1";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BIALAWE_SIATLO";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_item_WINDFIST2 (CFX_BASE_PROTO)
{
	 visname_s = "item_WINDFIST2";
	 visalpha = 1;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2e+006;
	 lightpresetname = "BIALAWE_SIATLO";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance  spellfx_jiranteleport_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_jiranteleport_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_jiranteleport_origin (cfx_base_proto)
{    	visname_s  =  "mfx_jiranteleport_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_jiranteleport_origin_timed (cfx_base_proto)
{    	visname_s  =  "mfx_jiranteleport_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_jiranteleport_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_jiranteleport_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_killerwanze (cfx_base_proto)
{    	visname_s  =  "mfx_killerwanze_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_killerwanze_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_killerwanze_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_killerwanze_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_killerwanze_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance spellfx_Kubsonic (CFX_BASE_PROTO)
{
	 visname_s = "MFX_KUBSONIC_INIT";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	emfxcreate_s = "spellfx_Kubsonic_active";
	 emfxcreatedowntrj = 1;	
};


/* Made by Risepolak (Xardas17) */


instance spellfx_Kubsonic_active (CFX_BASE_PROTO)
{
	 visname_s = "";
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET TARGET SPLINE RANDOM";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "DECAL_TELEKINESIS";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Kubsonic_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "MFX_KUBSONIC";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Kubsonic_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Kubsonic_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Kubsonic_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_lacerate(cfx_base_proto)
{
	visname_s = "mfx_lacerate_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collide";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcolldyn_s = "spellfx_lacerate_fountain";
	emfxcollstatalign_s = "COLLISIONNORMAL";
	emfxcreatedowntrj = 0;
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "redambience";
};

instance spellfx_lacerate_fountain(cfx_base_proto)
{
	visname_s = "mfx_lacerate_fountain";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	sfxid = "mfx_geyser_fountain";
	sfxisambient = 1;
};

instance  spellfx_lacerate_fountain_poison (cfx_base_proto)
{    	visname_s  =  "mfx_lacerate_fountain_poison";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_lacerate_fountain_small (cfx_base_proto)
{    	visname_s  =  "mfx_lacerate_fountain_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxisambient  =  1;
};

instance spellfx_lacerate_key_cast(c_particlefxemitkey)
{
	lightrange = 100;
	visname_s = "mfx_lacerate_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxisambient = 1;
	sfxid = "mfx_geyser_rumble";
	emcheckcollision = 1;
};

instance spellfx_lacerate_key_collide(c_particlefxemitkey)
{
	emtrjeasevel = 1e-006;
	sfxid = "cs_iam";
};

instance spellfx_lacerate_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_lacerate_init";
	lightrange = 0.001;
};

instance  spellfx_laehmen (cfx_base_proto)
{    	visname_s  =  "mfx_laehmen_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_laehmen_bridge (cfx_base_proto)
{    	visname_s  =  "mfx_laehmen_cast";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide";
    	emfxcolldynperc_s  =  "spellfx_laehmen_target";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_laehmen_bridge_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_laehmen_bridge_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_laehmen_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_laehmen_bridge";
    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
    	emtrjmode_s  =  "target spline random";
    	emtrjeasevel  =  500.0;
    	emcheckcollision  =  1;
};

instance  spellfx_laehmen_key_collide (c_particlefxemitkey)
{};

instance  spellfx_laehmen_target (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_laehmen_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_laehmen_grow";
    	sendassessmagic  =  1;
};

instance  spellfx_leech (cfx_base_proto)
{    	visname_s  =  "mfx_leech";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_icecube_cast";
    	sfxisambient  =  1;
};

instance spellfx_Lentern_0 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TempleFX02";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_1 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_2 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH2";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_3 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH3";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_4 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH4";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_5 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH5";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_6 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH6";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_7 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH7";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_8 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH8";
};

/* Made by Risepolak (Xardas17) */








instance spellfx_Lentern_9 (CFX_BASE_PROTO)
{
	 visname_s = "A_NIE_WIDAC";
	 lightpresetname = "FIRE_TORCH9";
};

/* Made by Risepolak (Xardas17) */








instance  spellfx_levitate (cfx_base_proto)
{    	visname_s  =  "mfx_light_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_levitate_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_light_origin";
    	lightrange  =  1000.0;
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_levitate_active_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_levitate_active_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_levitate_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_levitate_whirlwind (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_levitation_whirlwind";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_levitation_loop";
    	sfxisambient  =  1;
};

instance  spellfx_lichtschwert (cfx_base_proto)
{    	visname_s  =  "mfx_lichtschwert";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_lifeleech (cfx_base_proto)
{    	visname_s  =  "mfx_lifeleech";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_lightcone (cfx_base_proto)
{    	visname_s  =  "lightcone";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjoriginnode  =  "bip01 fokus";
    	emtrjtargetnode  =  "bip01 fokus";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "firesmall";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_lightingsragetdm(cfx_base_proto)
{
	visname_s = "mfx_lightingsragetdm_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_lightingsragetdm_investglow";
};

instance spellfx_lightingsragetdm_investglow(cfx_base_proto)
{
	visname_s = "mfx_lightingsragetdm_investglow";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "redambience";
	sfxid = "mfx_lightingsragetdm_invest";
	sfxisambient = 1;
	emfxcreate_s = "fx_earthquake";
};

instance spellfx_lightingsragetdm_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_lightingsragetdm_rain";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_lightingsragetdm_rain(cfx_base_proto)
{
	visname_s = "mfx_lightingsragetdm_rain";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "cataclysm";
	sfxid = "mfx_lightingsragetdm_rain";
	sfxisambient = 1;
};

instance spellfx_lightingsragetdm_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
};

instance spellfx_lightningbeliar(cfx_base_proto)
{
	visname_s = "mfx_lightningbeliar_origin";
	vissize_s = "4040";
	visalphablendfunc_s = "ADD";
	vistexanifps = 17;
	vistexaniislooping = 1;
	emtrjmode_s = "FIXED";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 20.;
	emtrjangleheadvar = 20.;
	emtrjloopmode_s = "pingpong";
	emtrjoriginnode = "zs_righthand";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 0.05;
	emselfrotvel_s = "0050";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjkeydistvar = 2;
	emtrjeasevel = 150;
};

instance spellfx_lightningbeliar_key_cast(c_particlefxemitkey)
{
};

instance spellfx_lightningbeliar_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_lightningbeliar_origin";
};

instance spellfx_lightningbeliar_key_invest_1(c_particlefxemitkey)
{
	visname_s = "lightningbeliar_single.ltn";
	emtrjmode_s = "targetlinerandom";
	emtrjeasevel = 3000.;
};

instance  spellfx_lightningflash_heavensrage_00 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_01 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_02 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_03 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_04 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_05 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_06 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_07 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_08 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningflash_heavensrage_09 (cfx_base_proto)
{    	visname_s  =  "mfx_heavensrage_flash_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	emfxcreate_s  =  "spellfx_lightningflash_target_cloud";
    	sfxid  =  "mfx_lightning_origin";
    	sfxisambient  =  1;
};

instance  spellfx_lightningstrike (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_lightningstrike_investglow (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_lightningstrike_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_lightningstrike_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_lightningstrike_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_origin";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emfxlifespan  =  5.0;
};

instance  spellfx_lightningstrike_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_lightning_origin";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  5.0;
};

instance  spellfx_lightningweaponenchantment (cfx_base_proto)
{    	visname_s  =  "mfx_lightningweaponenchantment_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_lightningweaponenchantment_investglow (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_lightningweaponenchantment_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_lightningweaponenchantment_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_lightningweaponenchantment_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_lightningweaponenchantment_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_lightningweaponenchantment_lefthand_beliar (cfx_base_proto)
{    	visname_s  =  "mfx_lightningweaponenchantment_origin_beliar";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_lightningweaponenchantment_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_lightningweaponenchantment_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_lightningweaponenchantment_righthand_beliar (cfx_base_proto)
{    	visname_s  =  "mfx_lightningweaponenchantment_origin_beliar";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_lightning_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "lightning_single.ltn";
    	emtrjmode_s  =  "target line random";
    	emtrjeasevel  =  6000.0;
    	sfxid  =  "mfx_lightning_target";
    	sfxisambient  =  1;
};

instance  spellfx_lightning_weapon_enchantment (cfx_base_proto)
{    	visname_s  =  "lightning_weapon_enchantment";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_lightningweaponenchantment_loop";
    	sfxisambient  =  1;
};

instance  spellfx_lightning_weapon_enchantment_beliar (cfx_base_proto)
{    	visname_s  =  "lightning_weapon_enchantment_beliar";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_lightningweaponenchantment_loop";
    	sfxisambient  =  1;
};

instance  spellfx_lightning_weapon_enchantment_victim (cfx_base_proto)
{    	visname_s  =  "lightning_weapon_enchantment_victim";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	emfxlifespan  =  1.0;
    	sfxid  =  "mfx_lightningweaponenchantment_loop";
    	sfxisambient  =  1;
};

instance  spellfx_lightning_weapon_enchantment_victim_beliar (cfx_base_proto)
{    	visname_s  =  "lightning_weapon_enchantment_victim_beliar";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
    	emfxlifespan  =  1.0;
    	sfxid  =  "mfx_lightningweaponenchantment_loop";
    	sfxisambient  =  1;
};

instance  spellfx_lightscript_active (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
    	lightpresetname  =  "justwhite";
};

instance  spellfx_lightscript_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_lightscript_origin";
    	lightrange  =  2000.0;
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_lightscript_active_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_lightscript_active_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_lightstar_amulett_blue (cfx_base_proto)
{    	visname_s  =  "lightstar_amulett_blue";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_lightstar_amulett_red (cfx_base_proto)
{    	visname_s  =  "lightstar_amulett_red";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_lightstar_amulett_violet (cfx_base_proto)
{    	visname_s  =  "lightstar_amulett_violet";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_lightstar_amulett_white (cfx_base_proto)
{    	visname_s  =  "lightstar_amulett_white";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_lightstar_green2 (cfx_base_proto)
{    	visname_s  =  "lightstar_green2";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_lightstar_green_small (cfx_base_proto)
{    	visname_s  =  "lightstar_green_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_lightstar_kasdeja (cfx_base_proto)
{    	visname_s  =  "lightstar_kasdeja";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_lightstar_soulrobber (cfx_base_proto)
{    	visname_s  =  "lightstar_soulrobber";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_light_jiran (cfx_base_proto)
{    	visname_s  =  "mfx_light_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_light_jiran_active";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_light_jiran_active (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
    	lightpresetname  =  "justwhite";
};

instance  spellfx_light_jiran_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_light_origin_jiran";
    	lightrange  =  1000.0;
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_light_jiran_active_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_light_jiran_active_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_light_jiran_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_loa_3minheal (cfx_base_proto)
{    	visname_s  =  "mfx_loa_3minheal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_loa_3minheal_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_loa_3minheal_origin";
};

instance  spellfx_loa_3minheal_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_loa_3minheal_cast";
    	emcreatefxid  =  "spellfx_loa_3minheal_lefthand";
};

instance  spellfx_loa_3minheal_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_loa_3minheal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_loa_3minheal_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_loa_3minheal_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_loa_3minheal_origin (cfx_base_proto)
{    	visname_s  =  "mfx_loa_3minheal_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_loa_3minheal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_loa_3minmana (cfx_base_proto)
{    	visname_s  =  "mfx_loa_3minmana_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_loa_3minmana_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_loa_3minmana_origin";
};

instance  spellfx_loa_3minmana_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_loa_3minmana_cast";
    	emcreatefxid  =  "spellfx_loa_3minmana_lefthand";
};

instance  spellfx_loa_3minmana_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_loa_3minmana_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_loa_3minmana_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_loa_3minmana_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_loa_3minmana_origin (cfx_base_proto)
{    	visname_s  =  "mfx_loa_3minmana_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_loa_3minmana_cast";
    	sfxisambient  =  1;
};

instance spellfx_MAGES (CFX_BASE_PROTO)
{
	 visname_s = "MFX_XAR_MAGES_INIT";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_MAGES_active";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MAGES_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "TARGET SPLINE RANDOM";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "1HEAVENLIGHT";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MAGES_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "MFX_XAR_MAGES";
	 lightrange = 400;
	 sfxid = "ZOMBIE_01";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MAGES_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MAGES_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MAGES_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Mage_Armor (CFX_BASE_PROTO)
{
	 visname_s = "Mage_Armor_init";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_Mage_Armor_active";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Mage_Armor_active(cfx_base_proto)
{
	visname_s = "";
	visalpha = 1;
	emtrjmode_s = "FOLLOW TARGET";
	emtrjeasevel = 0;
	emtrjoriginnode = "bip01";
	emtrjloopmode_s = "HALT";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 0.2;
	emtrjtargetrange = 0.1;
	emtrjtargetelev = 1;
	lightpresetname = "auramedium";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Mage_Armor_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "Arcane_Armor";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Mage_Armor_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Mage_Armor_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Mage_Armor_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance  spellfx_magicarrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_magicarrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  300.0;
};

instance  spellfx_magicarrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  400.0;
};

instance  spellfx_magicbolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_magicbolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_magicbolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  300.0;
};

instance spellfx_magiccage(cfx_base_proto)
{
	visname_s = "mfx_magiccage_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	lightpresetname = "whiteblend";
};

instance  spellfx_magiccagelong_target (cfx_base_proto)
{    	visname_s  =  "mfx_magiccagelong_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	lightpresetname  =  "whiteblend";
    	emfxlifespan  =  10.0;
};

instance spellfx_magiccage_bridge(cfx_base_proto)
{
	visname_s = "mfx_magiccage_cast";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET";
	emtrjoriginnode = "zs_righthand";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 900;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "collideCREATEONCE";
	emactioncollstat_s = "collide";
	emfxcolldynperc_s = "spellfx_magiccage_target";
	emfxlifespan = -1;
	emselfrotvel_s = "000";
	secsperdamage = -1;
	sfxid = "mfx_windfist_cast";
	sfxisambient = 1;
};

instance spellfx_magiccage_bridge_key_cast(c_particlefxemitkey)
{
	emcheckcollision = 1;
};

instance spellfx_magiccage_bridge_key_collide(c_particlefxemitkey)
{
	emtrjeasevel = 1e-006;
	pfx_ppsisloopingchg = 1;
	sfxid = "spear_start";
};

instance spellfx_magiccage_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_magiccage_bridge";
	emtrjeasevel = 1e-006;
	pfx_ppsisloopingchg = 1;
	sfxid = "mfx_sleep_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 500;
	emcheckcollision = 1;
};

instance spellfx_magiccage_key_collide(c_particlefxemitkey)
{
};

instance spellfx_magiccage_key_init(c_particlefxemitkey)
{
	lightrange = 0.001;
};

instance spellfx_magiccage_key_invest_1(c_particlefxemitkey)
{
	lightrange = 100;
};

instance  spellfx_magiccage_minion (cfx_base_proto)
{    	visname_s  =  "mfx_magiccage_minion";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sendassessmagic  =  1;
    	lightpresetname  =  "whiteblend";
    	emfxlifespan  =  3.0;
};

instance spellfx_magiccage_target(cfx_base_proto)
{
	visname_s = "mfx_magiccage_origin";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	sendassessmagic = 1;
	lightpresetname = "whiteblend";
	emfxlifespan = 18;
};

instance  spellfx_magicice_humansmoke (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicice_humansmoke";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_magicmissile (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_00 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_00_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_00_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_00_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_00_lightningcollide";
};

instance  spellfx_magicmissile_00_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_00_lightningcollide";
};

instance  spellfx_magicmissile_00_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_00";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_00_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_00_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_00_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_00_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_01 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_01_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_01_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_01_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_01_lightningcollide";
};

instance  spellfx_magicmissile_01_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_01_lightningcollide";
};

instance  spellfx_magicmissile_01_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_01";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_01_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_01_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_01_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_01_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_02 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_02_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_02_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_02_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_02_lightningcollide";
};

instance  spellfx_magicmissile_02_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_02_lightningcollide";
};

instance  spellfx_magicmissile_02_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_02";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_02_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_02_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_02_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_02_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_03 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_03_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_03_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_03_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_03_lightningcollide";
};

instance  spellfx_magicmissile_03_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_03_lightningcollide";
};

instance  spellfx_magicmissile_03_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_03";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_03_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_03_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_03_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_03_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_04 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_04_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_04_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_04_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_04_lightningcollide";
};

instance  spellfx_magicmissile_04_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_04_lightningcollide";
};

instance  spellfx_magicmissile_04_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_04";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_04_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_04_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_04_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_04_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_05 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_05_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_05_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_05_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_05_lightningcollide";
};

instance  spellfx_magicmissile_05_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_05_lightningcollide";
};

instance  spellfx_magicmissile_05_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_05";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_05_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_05_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_05_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_05_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_06 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_06_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_06_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_06_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_06";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_06_lightningcollide";
};

instance  spellfx_magicmissile_06_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_06";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_06_lightningcollide";
};

instance  spellfx_magicmissile_06_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_06";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_06_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_06_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_06_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_06_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_07 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_07_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_07_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_07_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_07";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_07_lightningcollide";
};

instance  spellfx_magicmissile_07_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_07";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_07_lightningcollide";
};

instance  spellfx_magicmissile_07_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_07";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_07_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_07_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_07_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_07_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_08 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_08_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_08_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_08_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_08";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_08_lightningcollide";
};

instance  spellfx_magicmissile_08_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_08";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_08_lightningcollide";
};

instance  spellfx_magicmissile_08_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_08";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_08_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_08_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_08_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_08_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_09 (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_magicmissile_09_collidefx";
    	emfxcolldyn_s  =  "spellfx_magicmissile_09_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_magicmissile_09_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_09";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_09_lightningcollide";
};

instance  spellfx_magicmissile_09_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide_09";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_09_lightningcollide";
};

instance  spellfx_magicmissile_09_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast_09";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_09_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_09_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_castfail_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_09_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_09_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicmissile_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_lightningcollide";
};

instance  spellfx_magicmissile_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_magicmissile_lightningcollide";
};

instance  spellfx_magicmissile_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
};

instance  spellfx_magicmissile_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_magicmissile_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_magicmissile_init";
    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_magicmissile_lightningcollide (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magicmissile_collide_light";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_magic_missile_impact_4";
};

instance  spellfx_magicorearrow (cfx_base_proto)
{    	visname_s  =  "magicore_arrow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_magicorearrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_magicorearrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_magicorearrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_magicorebolt (cfx_base_proto)
{    	visname_s  =  "magicore_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_magicorebolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_magicorebolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_magicorebolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_magicrune (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_magicrune_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_arcaneexplosion_cast";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_00 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_01 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_02 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_03 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_04 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_05 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_06 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_07 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_08 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_explosion_09 (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_explosion_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_massdeath_target";
    	sfxisambient  =  1;
    	emfxlifespan  =  1.2;
};

instance  spellfx_magicrune_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_magicrune_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_magicrune_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_magicrune_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_magicrune_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  3.0;
    	visalpha  =  1.0;
};

instance  spellfx_magicrune_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  3.0;
    	visalpha  =  1.0;
};

instance  spellfx_magicrune_target (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_dest";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjeasevel  =  6000.0;
};

instance  spellfx_magicrune_while_explode (cfx_base_proto)
{    	visname_s  =  "magicrune_effect_while_explode";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance spellfx_magicsword(cfx_base_proto)
{
	visname_s = "fire_sword_proto";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "justwhite";
	emadjustshptoorigin = 1;
};

instance  spellfx_magic_staff (cfx_base_proto)
{    	visname_s  =  "magic_staff";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_magic_staff_red (cfx_base_proto)
{    	visname_s  =  "magic_staff_red";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_magus_round2_smoke (cfx_base_proto)
{    	visname_s  =  "mfx_magus_round2_smoke";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_magus_round3_area_blue (cfx_base_proto)
{    	visname_s  =  "mfx_magus_round3_area_blue";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_magus_round3_area_red (cfx_base_proto)
{    	visname_s  =  "mfx_magus_round3_area_red";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_magus_round3_smoke_blue (cfx_base_proto)
{    	visname_s  =  "mfx_magus_round3_smoke_blue";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_magus_round3_smoke_red (cfx_base_proto)
{    	visname_s  =  "mfx_magus_round3_smoke_red";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_magus_round4_firestorm (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magus_round4_firestorm";
    	emfxcreate_s  =  "vob_burn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  spellfx_magus_round5_darkness (cfx_base_proto)
{    	visname_s  =  "mfx_magus_round5_darkness";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  30.0;
};

instance  spellfx_magus_round5_tentacles (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_magus_round5_tentacles";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_greententacle_grow";
};

instance SPELLFX_MAIDARMOR (CFX_BASE_PROTO)
{
	 visname_s = "MAIDFX";
	 visalpha = 1.0;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "=";
	 emtrjtargetrange = 10;
	 emtrjnumkeys = 10;
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2000000;
	 emfxcreate_s = "MAIDFX";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_MAIDARMORGreen (CFX_BASE_PROTO)
{
	 visname_s = "MAIDFX_Green";
	 visalpha = 1.0;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Rock3";
	 emtrjtargetrange = 10;
	 emtrjnumkeys = 10;
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2000000;
	 emfxcreate_s = "MAIDFX_Green";
	 lightpresetname = "ZIELONY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
/* Made by Risepolak (Xardas17) */








instance SPELLFX_MAIDARMORICE (CFX_BASE_PROTO)
{
	 visname_s = "MAIDFX_ice";
	 visalpha = 1.0;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Rock3";
	 emtrjtargetrange = 10;
	 emtrjnumkeys = 10;
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2000000;
	 emfxcreate_s = "MAIDFX_ice";
	 lightpresetname = "SELEDYNOWY";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance SPELLFX_MAIDARMORMAGIC (CFX_BASE_PROTO)
{
	 visname_s = "MAIDFX_Magic";
	 visalpha = 1.0;
	 visalphablendfunc_s = "ADD";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Rock3";
	 emtrjtargetrange = 10;
	 emtrjnumkeys = 10;
	 emtrjloopmode_s = "NONE";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjdynupdatedelay = 2000000;
	 emfxcreate_s = "MAIDFX_Magic";
	 lightpresetname = "SNOW_BALL1";
	 emfxlifespan = -1;
	 emadjustshptoorigin = 1;
	 emselfrotvel_s = "0 0 0";
	 secsperdamage = -1;
};
instance  spellfx_manaentzug (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "pingpong_once";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_suckenergy_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_suckenergy_invest";
};

instance  spellfx_manaentzug_bloodfly (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_flytoplayer";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_manaentzug_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_manaentzug_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_manaentzug_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_manaentzug_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_manaentzug_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_manaentzug_slowtime (cfx_base_proto)
{    	emfxtriggerdelay  =  6.0;
    	emfxlifespan  =  30.0;
    	visname_s  =  "morph.fov";
    	userstring  =  "0.8";
    	userstring[1]  =  "1.0";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
};

instance spellfx_manaforlife(cfx_base_proto)
{
	visname_s = "mfx_manaforlife_init";
	emtrjoriginnode = "zs_righthand";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emselfrotvel_s = "0500-250";
	emtrjdynupdatedelay = 0;
	emfxcreate_s = "spellfx_manaforlife_2obj";
	emfxinvestorigin_s = "spellfx_manaforlife_invest";
};

instance spellfx_manaforlife_2obj(cfx_base_proto)
{
	visname_s = "mfx_manaforlife_init2";
	emtrjoriginnode = "zs_righthand";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emselfrotvel_s = "5000250";
	emtrjdynupdatedelay = 0;
};

instance spellfx_manaforlife_2obj_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_manaforlife_2obj_key_init(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_manaforlife_invest(cfx_base_proto)
{
	visname_s = "mfx_manaforlife_spatter_0";
	emtrjoriginnode = "bip01spine2";
	emfxcreatedowntrj = 1;
	sfxid = "mfx_manaforlife_heartbeat";
	sfxisambient = 1;
	lightpresetname = "aura";
	emfxcreate_s = "spellfx_manaforlife_spatter_90";
	emfxlifespan = 30;
};

instance spellfx_manaforlife_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_manaforlife_origin";
	sfxid = "sfx_healobsession";
	sfxisambient = 1;
};

instance  spellfx_manaforlife_key_init (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_manaforlife_righthand_01 (cfx_base_proto)
{    	visname_s  =  "mfx_manaforlife_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emselfrotvel_s  =  "0 500 -250";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_manaforlife_righthand_02 (cfx_base_proto)
{    	visname_s  =  "mfx_manaforlife_init2";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emselfrotvel_s  =  "500 0 250";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance spellfx_manaforlife_spatter_180(cfx_base_proto)
{
	visname_s = "mfx_manaforlife_spatter_180";
	emtrjoriginnode = "bip01pelvis";
	emfxcreatedowntrj = 1;
	emfxcreate_s = "spellfx_manaforlife_spiral";
};

instance spellfx_manaforlife_spatter_90(cfx_base_proto)
{
	visname_s = "mfx_manaforlife_spatter_90";
	emtrjoriginnode = "bip01spine2";
	emfxcreatedowntrj = 1;
	emfxcreate_s = "spellfx_manaforlife_spatter_180";
};

instance spellfx_manaforlife_spiral(cfx_base_proto)
{
	visname_s = "mfx_manaforlife_ring_large1";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "FIXED";
	emselfrotvel_s = "04000";
	emtrjdynupdatedelay = 0;
	emfxcreatedowntrj = 1;
	emfxcreate_s = "spellfx_manaforlife_spiral2";
};

instance spellfx_manaforlife_spiral2(cfx_base_proto)
{
	visname_s = "mfx_manaforlife_ring_large2";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "FIXED";
	emselfrotvel_s = "04000";
	emtrjdynupdatedelay = 0;
	emfxcreatedowntrj = 0;
	emfxcreate_s = "dementor_fx";
};

instance  spellfx_manaforlife_spiral2_dark (cfx_base_proto)
{    	visname_s  =  "mfx_manaforlife_ring_large2_dark";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_manaforlife_spiral_dark (cfx_base_proto)
{    	visname_s  =  "mfx_manaforlife_ring_large1_dark";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_manaforlife_spiral2_dark";
};

instance  spellfx_manaleech (cfx_base_proto)
{    	visname_s  =  "mfx_manaleech";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_manarauben (cfx_base_proto)
{    	visname_s  =  "mfx_manarauben_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "pingpong_once";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_suckenergy_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_manarauben_invest";
};

instance  spellfx_manarauben_bloodfly (cfx_base_proto)
{    	visname_s  =  "mfx_manarauben_flytoplayer";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_manarauben_invest (cfx_base_proto)
{    	visname_s  =  "mfx_manarauben_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_manarauben_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_manarauben_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_manarauben_cast";
};

instance  spellfx_manarauben_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_manarauben_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_manarauben_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_manarauben_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_manarauben_target";
};

instance  spellfx_manareload_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  5.0;
    	visalpha  =  1.0;
};

instance  spellfx_manareload_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_castfail_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  5.0;
    	visalpha  =  1.0;
};

instance  spellfx_manareload_whirlwind (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_manareloadwhirlwind_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxisambient  =  1;
    	sfxid  =  "mfx_berserk_loop";
};

instance  spellfx_manashield (cfx_base_proto)
{    	visname_s  =  "mfx_manashield";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  0;
};

instance  spellfx_manashoot (cfx_base_proto)
{    	visname_s  =  "mfx_manashoot_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjnumkeys  =  5;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjloopmode_s  =  "none";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "aura";
};

instance  spellfx_manashoot2_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_manashoot_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_manashoot_mesheffect";
};

instance  spellfx_manashootferis2_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_manashootferis_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_manashootferis_mesheffect";
};

instance  spellfx_manashootferis_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_manashootferis_trail";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_manashootferis2_arrow";
};

instance  spellfx_manashootferis_mesheffect (cfx_base_proto)
{    	visname_s  =  "magic_bow_feris";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_manashoot_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_manashoot_trail";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_manashoot2_arrow";
};

instance  spellfx_manashoot_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "target line";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_light_cast";
};

instance  spellfx_manashoot_key_init (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_manashoot_key_open (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_manashoot_mesheffect (cfx_base_proto)
{    	visname_s  =  "magic_bow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_manashoot_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_manashoot_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	visalpha  =  1.0;
};

instance  spellfx_manashoot_righthand_init (cfx_base_proto)
{    	visname_s  =  "mfx_manashoot_righthand_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	visalpha  =  1.0;
};

instance spellfx_mask(cfx_base_proto)
{
	visname_s = "gww_mask";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
};

instance  spellfx_mask2 (cfx_base_proto)
{    	visname_s  =  "mfx_mask2_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_mask2_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_mask2_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_mask_collide";
    	lightpresetname  =  "redambience";
};

instance  spellfx_mask2_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mask2_mask";
    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_mask_cast";
    	sfxisambient  =  1;
};

instance  spellfx_mask2_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_mask2_mask (cfx_base_proto)
{    	visname_s  =  "mfx_mask2_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mask2_collidefx";
    	emfxcolldyn_s  =  "spellfx_mask2_spread";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_mask2_mask_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_mask_fly";
};

instance  spellfx_mask2_spread (cfx_base_proto)
{    	visname_s  =  "mfx_mask2_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_mask2_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_mask3 (cfx_base_proto)
{    	visname_s  =  "mfx_mask3_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_mask3_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_mask3_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_mask_collide";
    	lightpresetname  =  "redambience";
};

instance  spellfx_mask3_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mask3_mask";
    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_mask_cast";
    	sfxisambient  =  1;
};

instance  spellfx_mask3_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_mask3_mask (cfx_base_proto)
{    	visname_s  =  "mfx_mask3_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mask3_collidefx";
    	emfxcolldyn_s  =  "spellfx_mask3_spread";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_mask3_mask_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_mask_fly";
};

instance  spellfx_mask3_spread (cfx_base_proto)
{    	visname_s  =  "mfx_mask3_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_mask3_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_mask4 (cfx_base_proto)
{    	visname_s  =  "mfx_mask4_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_mask4_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_mask4_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_mask_collide";
    	lightpresetname  =  "redambience";
};

instance  spellfx_mask4_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mask4_mask";
    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_mask_cast";
    	sfxisambient  =  1;
};

instance  spellfx_mask4_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_mask4_mask (cfx_base_proto)
{    	visname_s  =  "mfx_mask4_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mask4_collidefx";
    	emfxcolldyn_s  =  "spellfx_mask4_spread";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_mask4_mask_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_mask_fly";
};

instance  spellfx_mask4_spread (cfx_base_proto)
{    	visname_s  =  "mfx_mask4_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_mask4_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_mask5 (cfx_base_proto)
{    	visname_s  =  "mfx_mask5_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_mask5_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_mask5_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_mask_collide";
    	lightpresetname  =  "redambience";
};

instance  spellfx_mask5_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mask5_mask";
    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_mask_cast";
    	sfxisambient  =  1;
};

instance  spellfx_mask5_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_mask5_mask (cfx_base_proto)
{    	visname_s  =  "mfx_mask5_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mask5_collidefx";
    	emfxcolldyn_s  =  "spellfx_mask5_spread";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_mask5_mask_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_mask_fly";
};

instance  spellfx_mask5_spread (cfx_base_proto)
{    	visname_s  =  "mfx_mask5_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_mask5_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_mask_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_mask_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_mask_collide";
    	lightpresetname  =  "redambience";
};

instance  spellfx_mask_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mask_mask";
    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_mask_cast";
    	sfxisambient  =  1;
};

instance  spellfx_mask_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_mask_mask (cfx_base_proto)
{    	visname_s  =  "mfx_mask_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mask_collidefx";
    	emfxcolldyn_s  =  "spellfx_mask_spread";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_mask_mask_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_mask_fly";
};

instance  spellfx_mask_spread (cfx_base_proto)
{    	visname_s  =  "mfx_mask_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_mask_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_massdeath_collidedynfx_silent (cfx_base_proto)
{    	visname_s  =  "mfx_massdeath_target";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance spellfx_massdeath_initglow(cfx_base_proto)
{
	visname_s = "mfx_massdeath_init_glow";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	lightpresetname = "redambience";
};

instance spellfx_massdeath_target(cfx_base_proto)
{
	visname_s = "mfx_massdeath_target";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_massdeath_target";
	sendassessmagic = 1;
};

instance  spellfx_masssleep (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_masssleep_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_masssleep_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_init";
};

instance  spellfx_masterofdisaster_heal (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_masterofdisaster_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  spellfx_masterofdisaster_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

/*
 *  MCQUEENFOG
 *
 *  Made by Damianut
 */
instance SPELLFX_MCQUEENFOG_SENDPERCEPTION(CFX_BASE_PROTO)
{
	visname_s = "MFX_MCQUEENFOGCATCH_CAST";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sendassessmagic = 1;
	emadjustshptoorigin = 1;
	// sfxid = "MFX_Icecube_Target";
};

instance spellfx_MCQUEENFOG_Invest(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	// sfxid = "MFX_ICECUBE_INVEST";
	// sfxisambient = 1;
};
instance spellfx_MCQUEENFOG (CFX_BASE_PROTO)
{
    visname_s = "FIRE_Green_1";
    visalpha = 0.1;
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    lightpresetname = "ZIELONY";
    emfxinvestorigin_s = "spellfx_MCQUEENFOG_Invest";
};

instance spellfx_MCQUEENFOG_key_cast_origin (CFX_BASE_PROTO)
{
    visname_s = "SPIDER_QUEEN_FOOG_V1";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0;
    sfxid = "BCR_EATING";
    lightpresetname = "ZIELONY";
    sfxisambient = 1;
    
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynperc_s = "SPELLFX_MCQUEENFOG_SENDPERCEPTION";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};
instance spellfx_MCQUEENFOG_key_invest_1 (C_PARTICLEFXEMITKEY)
{
    lightrange = 200;
};

instance spellfx_MCQUEENFOG_key_open(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};
instance spellfx_MCQUEENFOG_key_init(C_PARTICLEFXEMITKEY)
{
    lightrange = 0.01;
};
instance spellfx_MCQUEENFOG_key_cast(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_MCQUEENFOG_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

// (FURY) Efekt furii - jak przy uleczeniu, ale na czerwono.
instance FURY_START(CFX_BASE_PROTO)
{
	visname_s = "MFX_FURY_Start";
	sfxid = "MFX_FURY_CAST";
	sfxisambient = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R FOOT";
};

instance FURY_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_FURY_LIGHT";
	emtrjoriginnode = "BIP01";
	visalpha = 1;
	emfxcreate_s = "FURY_START";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURA";
};
//END "FURY"

instance  spellfx_meteor (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
};

instance  spellfx_meteorbullet (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_00 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_00_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_00";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_00_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_00_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_00_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_00_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_00_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_00_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_00_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_01 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_01_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_01";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_01_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_01_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_01_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_01_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_01_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_01_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_01_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_02 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_02_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_02";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_02_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_02_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_02_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_02_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_02_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_02_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_02_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_03 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_03_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_03";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_03_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_03_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_03_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_03_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_03_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_03_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_03_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_04 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_04_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_04";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_04_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_04_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_04_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_04_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_04_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_04_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_04_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_05 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_05_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_05";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_05_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_05_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_05_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_05_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_05_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_05_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_05_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_06 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_06_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_06";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_06_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_06_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_06_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_06_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_06_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_06_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_06_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_07 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_07_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_07";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_07_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_07_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_07_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_07_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_07_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_07_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_07_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_08 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_08_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_08";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_08_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_08_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_08_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_08_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_08_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_08_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_08_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_09 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldyn_s  =  "spellfx_meteorbullet_spread";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_meteorbullet_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_meteorbullet_09_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast_09";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_09_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_09_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_09_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_09_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_09_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_09_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_09_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_collide (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide3";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_collide3";
    	emfxcreate_s  =  "vob_magicburn_withearthquake";
};

instance  spellfx_meteorbullet_investblast1 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast1";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_meteorbullet_investblast2 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast2";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_meteorbullet_investblast3 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast3";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_meteorbullet_investblast4 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast4";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_meteorbullet_investsound (cfx_base_proto)
{    	visname_s  =  "simpleglow.tga";
    	visalpha  =  0.01;
    	sfxid  =  "mfx_firestorm_invest";
    	sfxisambient  =  1;
};

instance  spellfx_meteorbullet_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_meteorbullet_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  100.0;
};

instance  spellfx_meteorbullet_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_meteorbullet_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast1";
};

instance  spellfx_meteorbullet_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast2";
};

instance  spellfx_meteorbullet_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast3";
};

instance  spellfx_meteorbullet_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_meteorbullet_investblast4";
};

instance  spellfx_meteorbullet_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_meteorbullet_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_meteorbullet_spread (cfx_base_proto)
{    	visname_s  =  "mfx_meteorbullet_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "vob_magicburn";
    	emfxcolldynperc_s  =  "spellfx_meteorbullet_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_meteorbullet_collide";
    	sfxid  =  "mfx_meteor_collide";
    	sfxisambient  =  1;
};

instance  spellfx_meteorbullet_spread_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_meteorbullet_spread_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance spellfx_meteorstorm(cfx_base_proto)
{
	visname_s = "mfx_firestorm_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_meteorstorm_investsound";
	sfxisambient = 1;
};

instance spellfx_meteorstorm_investsound(cfx_base_proto)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "mfx_firestorm_invest";
	sfxisambient = 1;
};

instance spellfx_meteorstorm_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_meteorstorm_spread";
	pfx_ppsisloopingchg = 1;
	sfxid = "watherrain";
};

instance spellfx_meteorstorm_spread(cfx_base_proto)
{
	visname_s = "mfx_meteor_spread";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "firesmall";
	sfxid = "mfx_firestorm_collide";
	sfxisambient = 1;
};

instance  spellfx_meteor_cast (cfx_base_proto)
{    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_meteor_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_meteor_cast";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_meteor_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_meteor_key_invest_2 (c_particlefxemitkey)
{    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_meteor_target (cfx_base_proto)
{    	visname_s  =  "mfx_meteor_dest";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjeasevel  =  6000.0;
};

instance spellfx_miecz(cfx_base_proto)
{
	visname_s = "mfx_miecz_ciosy";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_icespell_invest";
};

instance spellfx_miecz_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_miecz_wave";
	pfx_ppsisloopingchg = 1;
	sfxisambient = 1;
};

instance spellfx_miecz_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_miecz_ciosy";
};

instance spellfx_miecz_lewy(cfx_base_proto)
{
	visname_s = "sword_atack";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_lefthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjnumkeys = 1;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 15.;
	emtrjangleheadvar = 0.;
	emtrjdynupdatedelay = 0.;
	emfxinvesttarget_s = "spellfx_pyrokinesis_target";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
};

instance spellfx_miecz_lewy_key_cast(c_particlefxemitkey)
{
};

instance spellfx_miecz_miecz(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	sfxisambient = 1;
};

instance spellfx_miecz_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
};

instance spellfx_miecz_wave(cfx_base_proto)
{
	emtrjoriginnode = "zs_righthand";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
};

instance spellfx_miecz_wave_key_cast(c_particlefxemitkey)
{
	lightrange = 200;
};

instance spellfx_miecz_wave_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_miecz_wave_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance  spellfx_modifiedzap (cfx_base_proto)
{    	visname_s  =  "mfx_thunderstorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "fx_earthquake";
};

instance  spellfx_modifiedzap_flash (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	visname_s  =  "mfx_thunderstorm_flashes";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_modifiedzap_screenblend";
    	sfxid  =  "mfx_thunderstorm_thunder";
    	sfxisambient  =  1;
};

instance  spellfx_modifiedzap_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_thunderstorm_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_modifiedzap_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_modifiedzap_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_modifiedzap_rain (cfx_base_proto)
{    	visname_s  =  "mfx_thunderstorm_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_modifiedzap_flash";
    	sfxid  =  "mfx_thunderstorm_icerain";
    	sfxisambient  =  1;
};

instance  spellfx_modifiedzap_screenblend (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "0 0 0 120";
    	userstring[2]  =  "3";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  10.0;
};

instance spellfx_MOONBLESS (CFX_BASE_PROTO)
{
	 visname_s = "MFX_XAR_MOONBLESS_INIT";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_MOONBLESS_active";
	 lightpresetname = "SELEDYNOWY";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MOONBLESS_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "1LIGHTNING_ORIGINRED_A0";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MOONBLESS_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "MFX_XAR_MOONBLESS";
	 lightrange = 400;
	 sfxid = "WARP";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MOONBLESS_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MOONBLESS_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_MOONBLESS_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */



instance  spellfx_mortmissiles (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mortmissiles_collide";
    	emfxcolldyn_s  =  "spellfx_mortmissiles_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_mortmissiles2 (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mortmissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_mortmissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_mortmissiles2head (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mortmissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_mortmissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_mortmissiles2head_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mortmissiles2head_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_mortmissiles2head_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_mortmissiles2head_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_mortmissiles2head_missile (cfx_base_proto)
{    	visname_s  =  "mfx_mort_missiles_cast2";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  2.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_mortmissiles2head_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_mortmissiles2lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mortmissiles2_collide";
    	emfxcolldyn_s  =  "spellfx_mortmissiles2_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_mortmissiles2lefthand_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mortmissiles2lefthand_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_mortmissiles2lefthand_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_mortmissiles2lefthand_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_mortmissiles2lefthand_missile (cfx_base_proto)
{    	visname_s  =  "mfx_mort_missiles_cast2";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  7.0;
    	emtrjangleheadvar  =  12.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_mortmissiles2lefthand_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_mortmissiles2_collide (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_mortmissiles2_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_mortmissiles2_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mortmissiles2_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_mortmissiles2_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_mortmissiles2_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_mortmissiles2_missile (cfx_base_proto)
{    	visname_s  =  "mfx_mort_missiles_cast2";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_mortmissiles2_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_mortmissileshead (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mortmissiles_collide";
    	emfxcolldyn_s  =  "spellfx_mortmissiles_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_mortmissileshead_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mortmissileshead_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_mortmissileshead_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_mortmissileshead_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_mortmissileshead_missile (cfx_base_proto)
{    	visname_s  =  "mfx_mort_missiles_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  12.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_mortmissileshead_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_mortmissileslefthand (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_mortmissiles_collide";
    	emfxcolldyn_s  =  "spellfx_mortmissiles_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_mortmissileslefthand_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mortmissileslefthand_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_mortmissileslefthand_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_mortmissileslefthand_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_mortmissileslefthand_missile (cfx_base_proto)
{    	visname_s  =  "mfx_mort_missiles_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  12.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_mortmissileslefthand_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_mortmissiles_collide (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_mortmissiles_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_arcane_missiles_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_mortmissiles_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_mortmissiles_missile";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_mortmissiles_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_mortmissiles_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arcane_missiles_init";
    	scaleduration  =  0.5;
};

instance  spellfx_mortmissiles_missile (cfx_base_proto)
{    	visname_s  =  "mfx_mort_missiles_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  12.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  1300.0;
};

instance  spellfx_mortmissiles_missile_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_mort_charge_missiles (cfx_base_proto)
{    	visname_s  =  "mort_charge_missiles";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "cataclysm";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_mort_spiral2_dark (cfx_base_proto)
{    	visname_s  =  "mfx_mort_ring_large2_dark";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  0;
};

instance  spellfx_mort_spiral_dark (cfx_base_proto)
{    	visname_s  =  "mfx_mort_ring_large1_dark";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 400 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_mort_spiral2_dark";
};

instance  spellfx_nebel (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_nebel_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_nebel_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_nebel_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_nebel_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_obsidian (cfx_base_proto)
{    	visname_s  =  "mfx_obsidian_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_obsidian_target";
};

instance  spellfx_obsidian_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_obsidian_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_obsidian_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_obsidian_init";
};

instance  spellfx_obsidian_killstart (cfx_base_proto)
{    	visname_s  =  "mfx_obsidian_dead_pfx";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "whiteblend";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_obsidian_origin (cfx_base_proto)
{    	visname_s  =  "mfx_obsidian_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_obsidian_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "mfx_obsidian_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance spellfx_ogien(cfx_base_proto)
{
	visname_s = "cast10";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjnumkeys = 1;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 15.;
	emtrjangleheadvar = 0.;
	emtrjdynupdatedelay = 0.;
	emfxinvesttarget_s = "spellfx_pyrokinesis_target";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
};

instance spellfx_ogien_key_cast(c_particlefxemitkey)
{
	sfxid = "mfx_firespell_humanburn";
	pfx_ppsisloopingchg = 1;
};

instance  spellfx_openchest (cfx_base_proto)
{    	visname_s  =  "mfx_openchest_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
};

instance  spellfx_openlock (cfx_base_proto)
{    	visname_s  =  "mfx_charm_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_openlock_target";
};

instance  spellfx_openlock_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_charm_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_openlock_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_charm_init";
};

instance  spellfx_openlock_origin (cfx_base_proto)
{    	visname_s  =  "mfx_charm_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_openlock_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "mfx_charm_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_orangepotion (cfx_base_proto)
{    	visname_s  =  "orange_potion";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_orcbosssummon_origin (cfx_base_proto)
{    	visname_s  =  "mfx_orcbosssummon_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_pallightscript_active (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
    	lightpresetname  =  "auralight";
};

instance  spellfx_pallightscript_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_pallightscript_origin";
    	lightrange  =  2000.0;
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_pallightscript_active_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pallightscript_active_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_picklock (cfx_base_proto)
{    	visname_s  =  "mfx_picklock_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "pingpong";
    	emtrjeasefunc_s  =  "LINEAR";
    	emfxinvesttarget_s  =  "spellfx_picklock_investtarget";
};

instance  spellfx_picklock_investsound (cfx_base_proto)
{    	sfxid  =  "mfx_picklock_invest";
    	sfxisambient  =  0;
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_picklock_investtarget (cfx_base_proto)
{    	visname_s  =  "mfx_picklock_target";
    	lightpresetname  =  "cataclysm";
    	emfxcreate_s  =  "spellfx_picklock_investsound";
};

instance  spellfx_picklock_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_picklock_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_picklock_key_invest_2 (c_particlefxemitkey)
{    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  500.0;
};

instance  spellfx_plantglimmer_withsound (cfx_base_proto)
{    	visname_s  =  "herb_glimmer";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	sfxid  =  "perm_plant_sound";
    	sfxisambient  =  1;
};

instance  spellfx_poisonarrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_poisonarrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_poisonarrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_poisonball (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emfxcollstat_s  =  "spellfx_poisonball_spread";
    	emfxcolldyn_s  =  "spellfx_poisonball_spread";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_00 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_00_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_00_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_00";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_00_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_00_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_01 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_01_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_01_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_01";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_01_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_01_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_02 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_02_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_02_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_02";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_02_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_02_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_03 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_03_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_03_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_03";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_03_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_03_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_04 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_04_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_04_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_04";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_04_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_04_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_05 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_05_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_05_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_05";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_05_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_05_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_06 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_06_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_06_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_06";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_06_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_06_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_07 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_07_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_07_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_07";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_07_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_07_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_08 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_08_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_08_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_08";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_08_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_08_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_09 (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonball_invest";
};

instance  spellfx_poisonball_09_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_09_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast_09";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  700.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_09_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_09_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonball_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonball_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonball_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_poisonball_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_poisonball_spread (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_spread_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonball_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
};

instance  spellfx_poisonball_spread_fake (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_spread_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  0;
};

instance  spellfx_poisonball_spread_fake_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_poisonball_spread_fake_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonball_spread_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_poisonball_spread_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonbolt (cfx_base_proto)
{    	visname_s  =  "poison_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_poisonbolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_poisonbolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_poisonbolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_poisoned (cfx_base_proto)
{    	visname_s  =  "poisoned_particles";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_poisoned_gorzah (cfx_base_proto)
{    	visname_s  =  "poisoned_particles";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_poisonmouthprojectile (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_mouth";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_poisonmouthprojectile_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_poisonmouthprojectile_invest";
};

instance  spellfx_poisonmouthprojectile_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonmouthprojectile_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_poisonspit_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonmouthprojectile_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poisonmouthprojectile_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonmouthprojectile_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_poisonstorm_collide (cfx_base_proto)
{    	visname_s  =  "mfx_poison_collide3";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_collide3";
};

instance  spellfx_poisonstorm_spread (cfx_base_proto)
{    	visname_s  =  "mfx_poisonstorm_spread_small";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargepoison_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "poison2";
    	emfxcreate_s  =  "spellfx_poisonstorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_poisonstorm_spread_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_poisonstorm_spread_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_poisonsword (cfx_base_proto)
{    	visname_s  =  "poison_sword";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "poison2";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_poisonwave_explosion (cfx_base_proto)
{    	visname_s  =  "mfx_poisonwave";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonwave_explosion_rundumschlag (cfx_base_proto)
{    	visname_s  =  "mfx_poisonwave_rundumschlag";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonwave_explosion_small (cfx_base_proto)
{    	visname_s  =  "mfx_poisonwave_small";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonwave_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emfxlifespan  =  3.0;
};

instance  spellfx_poisonwave_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  3.0;
};

instance  spellfx_poisonwave_swampdrone (cfx_base_proto)
{    	visname_s  =  "mfx_poisonwave_swampdrone";
    	emtrjmode_s  =  "FIXED";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  0;
    	emtrjoriginnode  =  "bip01 l hand";
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_poisonweaponenchantment (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_poisonweaponenchantment_investglow (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_poisonweaponenchantment_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_poisonweaponenchantment_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_poisonweaponenchantment_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_poisonweaponenchantment_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_poisonball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_poison_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_firerain_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_poison_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_firestorm_spread";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_poison_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_init";
};

instance  spellfx_poison_origin (cfx_base_proto)
{    	visname_s  =  "practicemagic_01a";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_poison_rain (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_poison_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_poison_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "practicemagic_01a";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_poison_weapon_enchantment (cfx_base_proto)
{    	visname_s  =  "poison_weapon_enchantment";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance spellfx_prawa_reka_trucizna_1(cfx_base_proto)
{
	visname_s = "trucizna";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjnumkeys = 1;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 15.;
	emtrjangleheadvar = 0.;
	emtrjdynupdatedelay = 0.;
	emfxinvesttarget_s = "spellfx_pyrokinesis_target";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
};

instance spellfx_prawa_reka_trucizna_2(cfx_base_proto)
{
	visname_s = "trucizna";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjnumkeys = 1;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 15.;
	emtrjangleheadvar = 0.;
	emtrjdynupdatedelay = 0.;
	emfxinvesttarget_s = "spellfx_pyrokinesis_target";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
};

instance  spellfx_prisma (cfx_base_proto)
{    	visname_s  =  "lightstar_prisma";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_protectice (cfx_base_proto)
{    	visname_s  =  "mfx_protectice_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_protectice_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_protectice_origin";
};

instance  spellfx_protectice_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_protectice_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_protectice_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_protectice_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_protectice_origin (cfx_base_proto)
{    	visname_s  =  "mfx_protectice_ring";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_light_invest";
    	sfxisambient  =  1;
};

instance spellfx_purple_shield (CFX_BASE_PROTO)
{
	 visname_s = "mfx_purple_shield_init";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_purple_shield_active";
	 sfxid = "ALG_WARN";
	 lightpresetname = "DECAL_TRANSFORM";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_purple_shield_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */





instance spellfx_purple_shield_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "bip01";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "DECAL_WINDFIST";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_purple_shield_active_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_purple_shield";
	lightrange = 400;
	sfxid = "mfx_arcanemissile_cast01";
	sfxisambient = 1;
	emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_purple_shield_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance  spellfx_pyrokinesis_05 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_pyrokinesis_spread_05";
    	emfxcolldyn_s  =  "spellfx_pyrokinesis_spread_05";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_pyrokinesis_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_pyrokinesis_05_investblast1 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast1_05";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_05_investblast2 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast2_05";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_05_investblast3 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast3_05";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_05_investblast4 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast4_05";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_05_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_firestorm_cast_05";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_05_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_pyrokinesis_05_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_05_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_05_investblast1";
};

instance  spellfx_pyrokinesis_05_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_05_investblast2";
};

instance  spellfx_pyrokinesis_05_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_05_investblast3";
};

instance  spellfx_pyrokinesis_05_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_05_investblast4";
};

instance  spellfx_pyrokinesis_05_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_06 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_pyrokinesis_spread_06";
    	emfxcolldyn_s  =  "spellfx_pyrokinesis_spread_06";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_pyrokinesis_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_pyrokinesis_06_investblast1 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast1_06";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_06_investblast2 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast2_06";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_06_investblast3 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast3_06";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_06_investblast4 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast4_06";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_06_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_firestorm_cast_06";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_06_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_pyrokinesis_06_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_06_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_06_investblast1";
};

instance  spellfx_pyrokinesis_06_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_06_investblast2";
};

instance  spellfx_pyrokinesis_06_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_06_investblast3";
};

instance  spellfx_pyrokinesis_06_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_06_investblast4";
};

instance  spellfx_pyrokinesis_06_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_07 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_pyrokinesis_spread_07";
    	emfxcolldyn_s  =  "spellfx_pyrokinesis_spread_07";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_pyrokinesis_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_pyrokinesis_07_investblast1 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast1_07";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_07_investblast2 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast2_07";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_07_investblast3 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast3_07";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_07_investblast4 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast4_07";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_07_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_firestorm_cast_07";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_07_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_pyrokinesis_07_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_07_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_07_investblast1";
};

instance  spellfx_pyrokinesis_07_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_07_investblast2";
};

instance  spellfx_pyrokinesis_07_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_07_investblast3";
};

instance  spellfx_pyrokinesis_07_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_07_investblast4";
};

instance  spellfx_pyrokinesis_07_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_08 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_pyrokinesis_spread_08";
    	emfxcolldyn_s  =  "spellfx_pyrokinesis_spread_08";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_pyrokinesis_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_pyrokinesis_08_investblast1 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast1_08";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_08_investblast2 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast2_08";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_08_investblast3 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast3_08";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_08_investblast4 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast4_08";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_08_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_firestorm_cast_08";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_08_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_pyrokinesis_08_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_08_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_08_investblast1";
};

instance  spellfx_pyrokinesis_08_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_08_investblast2";
};

instance  spellfx_pyrokinesis_08_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_08_investblast3";
};

instance  spellfx_pyrokinesis_08_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_08_investblast4";
};

instance  spellfx_pyrokinesis_08_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_09 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_pyrokinesis_spread_09";
    	emfxcolldyn_s  =  "spellfx_pyrokinesis_spread_09";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxinvestorigin_s  =  "spellfx_pyrokinesis_investsound";
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_pyrokinesis_09_investblast1 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast1_09";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_09_investblast2 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast2_09";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_09_investblast3 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast3_09";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_09_investblast4 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_investblast4_09";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_fireball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_09_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_firestorm_cast_09";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_firestorm_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_09_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_pyrokinesis_09_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_09_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_09_investblast1";
};

instance  spellfx_pyrokinesis_09_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_09_investblast2";
};

instance  spellfx_pyrokinesis_09_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_09_investblast3";
};

instance  spellfx_pyrokinesis_09_key_invest_4 (c_particlefxemitkey)
{    	lightrange  =  250.0;
    	emcreatefxid  =  "spellfx_pyrokinesis_09_investblast4";
};

instance  spellfx_pyrokinesis_09_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_pyrokinesis_g1 (cfx_base_proto)
{    	visname_s  =  "mfx_pyrokinesis_g1_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 head";
    	emtrjnumkeys  =  1;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjdynupdatedelay  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_pyrokinesis_g1_target";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
};

instance  spellfx_pyrokinesis_g1_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_pyrokinesis_g1_target (cfx_base_proto)
{    	visname_s  =  "mfx_pyrokinesis_g1_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	lightpresetname  =  "firesmall";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	sendassessmagic  =  1;
    	emtrjdynupdatedelay  =  0.01;
    	sfxid  =  "mfx_pyrokinesis_g1_target";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_spread_05 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_spread_05_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_spread_05_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_pyrokinesis_spread_06 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_spread_06_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_spread_06_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_pyrokinesis_spread_07 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_spread_07_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_spread_07_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_pyrokinesis_spread_08 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_spread_08_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_spread_08_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_pyrokinesis_spread_09 (cfx_base_proto)
{    	visname_s  =  "mfx_firestorm_spread_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_chargefireball_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "40 40";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
    	emfxcreate_s  =  "spellfx_firestorm_collide";
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_pyrokinesis_spread_09_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_pyrokinesis_spread_09_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance spellfx_pyrokinesis_target(cfx_base_proto)
{
	visname_s = "mfx_pyrokinesis_target";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
	lightpresetname = "firesmall";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
	sendassessmagic = 1;
	emtrjdynupdatedelay = 0.01;
	sfxid = "mfx_pyrokinesis_target";
	sfxisambient = 1;
};

instance spellfx_quake(cfx_base_proto)
{
	visname_s = "mfx_quake_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_quake_buildup";
};

instance spellfx_quake_buildup(cfx_base_proto)
{
	visname_s = "spellfx_invisibleprojectile";
	sfxid = "mfx_quake_cast";
};

instance spellfx_quake_cast(cfx_base_proto)
{
	visname_s = "earthquake.eqk";
	userstring[0] = "1000";
	userstring[1] = "8";
	userstring[2] = "777";
	sfxid = "mfx_quake_earthquake";
	sfxisambient = 1;
};

instance spellfx_quake_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_quake_targets";
	pfx_ppsisloopingchg = 1;
	sfxid = "mfx_quake_stomp";
	sfxisambient = 1;
};

instance spellfx_quake_sendperception(cfx_base_proto)
{
	sendassessmagic = 1;
};

instance spellfx_quake_targets(cfx_base_proto)
{
	visname_s = "mfx_quake_cast";
	emtrjoriginnode = "bip01";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynperc_s = "spellfx_quake_sendperception";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	emfxcreate_s = "spellfx_quake_cast";
	emfxcreatedowntrj = 1;
};

instance spellfx_Queen_Vomit_V0 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_Vomit_V0_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_Vomit_V0_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_Vomit_V0_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V0";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_Vomit_V0_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_Vomit_V0_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_Vomit_V0_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Queen_VOMIT_V2 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V2_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V2_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V2_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V2";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V2_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V2_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V2_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Queen_VOMIT_V3 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V3_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V3_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V3_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V3";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V3_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V3_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V3_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Queen_VOMIT_V4 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V4_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V4_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V4_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V4";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V4_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V4_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V4_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Queen_VOMIT_V5 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V5_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V5_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V5_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V5";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V5_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V5_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V5_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Queen_VOMIT_V6 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V6_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V6_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V6_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V6";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V6_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V6_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V6_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */



instance spellfx_Queen_VOMIT_V7 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V7_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V7_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V7_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V7";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V7_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V7_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V7_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V8 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V8_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V8_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V8_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V8";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V8_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V8_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V8_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V9 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V9_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_Queen_VOMIT_V2_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_Queen_VOMIT_V9_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "QUEEN_VOMIT_V9";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01 Head";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V9_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V9_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_Queen_VOMIT_V9_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_rage(cfx_base_proto)
{
	visname_s = "mfx_fear_init";
	emtrjmode_s = "FIXED";
	emtrjeasefunc_s = "LINEAR";
	emtrjoriginnode = "zs_righthand";
	emtrjdynupdatedelay = 10000;
};

instance spellfx_rage_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_fear_ground";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_rage_key_open(c_particlefxemitkey)
{
	emtrjeasevel = 0;
};

instance spellfx_rage_target(cfx_base_proto)
{
	visname_s = "mfx_fear_ghostend";
	emtrjoriginnode = "bip01";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "none";
	sfxid = "mfx_fear_ghostend";
	sfxisambient = 1;
};

instance spellfx_rapidzap(cfx_base_proto)
{
	visname_s = "mfx_icebolt_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreate";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_rapidicebolt_collide";
	emfxcolldyn_s = "spellfx_rapidicebolt_collidedynfx";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
};

instance spellfx_rapidzap_collide(cfx_base_proto)
{
	visname_s = "mfx_icebolt_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "torch_enlight";
};

instance spellfx_rapidzap_collidedynfx(cfx_base_proto)
{
	visname_s = "mfx_thunderbolt_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "torch_enlight";
	sendassessmagic = 1;
};

instance spellfx_rapidzap_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_heavensrage_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "mfx_thunderball_collide3";
	emcheckcollision = 1;
};

instance spellfx_rapidzap_key_collide(c_particlefxemitkey)
{
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 1e-006;
	emcheckcollision = 0;
};

instance spellfx_rapizap_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_icebolt_init";
	scaleduration = 0.5;
};

instance  spellfx_raven_heal (cfx_base_proto)
{    	visname_s  =  "mfx_summondemon_invest";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "sfx_circle";
    	sfxisambient  =  1;
};

instance  spellfx_realgreententacle (cfx_base_proto)
{    	visname_s  =  "mfx_realgreententacle_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
};

instance  spellfx_realgreententacle_bridge (cfx_base_proto)
{    	visname_s  =  "mfx_realgreententacle_cast";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide";
    	emfxcolldynperc_s  =  "spellfx_realgreententacle_target";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_realgreententacle_bridge_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
};

instance  spellfx_realgreententacle_bridge_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_realgreententacle_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_realgreententacle_bridge";
    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
    	emtrjmode_s  =  "target spline random";
    	emtrjeasevel  =  500.0;
    	emcheckcollision  =  1;
};

instance  spellfx_realgreententacle_key_collide (c_particlefxemitkey)
{};

instance  spellfx_realgreententacle_target (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_realgreententacle_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_greententacle_grow";
    	sendassessmagic  =  1;
};

instance  spellfx_realpyrokinesis (cfx_base_proto)
{    	visname_s  =  "mfx_pyrokinesis_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 head";
    	emtrjnumkeys  =  1;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjdynupdatedelay  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_realpyrokinesis_target";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
};

instance  spellfx_realpyrokinesis_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_realpyrokinesis_target (cfx_base_proto)
{    	visname_s  =  "mfx_realpyrokinesis_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	lightpresetname  =  "firesmall";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	sendassessmagic  =  1;
    	emtrjdynupdatedelay  =  0.01;
    	sfxid  =  "mfx_realpyrokinesis_target";
    	sfxisambient  =  1;
};

instance  spellfx_redglow (cfx_base_proto)
{    	visname_s  =  "lightstar_red";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_firerain_invest";
    	sfxisambient  =  1;
};

instance  spellfx_redlight (cfx_base_proto)
{    	visname_s  =  "mfx_berzerk_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_redteleport (cfx_base_proto)
{    	visname_s  =  "mfx_redteleport_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxinvestorigin_s  =  "spellfx_redteleport_origin";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_redteleport_cast (cfx_base_proto)
{    	visname_s  =  "mfx_redteleport_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_redteleport_cast";
    	sfxisambient  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_redteleport_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_redteleport_cast";
    	pfx_ppsisloopingchg  =  1;
    	lightrange  =  200.0;
};

instance  spellfx_redteleport_key_init (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_redteleport_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_redteleport_key_open (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_redteleport_origin (cfx_base_proto)
{    	visname_s  =  "mfx_redteleport_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_redteleport_ring";
    	sfxid  =  "mfx_redteleport_invest";
    	sfxisambient  =  1;
};

instance  spellfx_redteleport_ring (cfx_base_proto)
{    	visname_s  =  "mfx_redteleport_ring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance spellfx_RED_AURA (CFX_BASE_PROTO)
{
	 visname_s = "ACID_AURA_Init_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "zs_righthand";
	 emfxcreate_s = "spellfx_RED_AURA_active";
	 lightpresetname = "AURASMALL";
	 emfxcreatedowntrj = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_AURA_active (CFX_BASE_PROTO)
{
	 visalpha = 1;
	 emtrjmode_s = "FOLLOW TARGET";
	 emtrjoriginnode = "Bip01 Footsteps";
	 emtrjtargetrange = 0.1;
	 emtrjtargetelev = 1;
	 emtrjloopmode_s = "HALT";
	 emtrjeasefunc_s = "LINEAR";
	 emtrjeasevel = 0;
	 emtrjdynupdatedelay = 0.2;
	 lightpresetname = "AURAMEDIUM";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_AURA_active_key_cast (C_PARTICLEFXEMITKEY)
{
	 visname_s = "ACID_AURA_1";
	 lightrange = 400;
	 sfxid = "mfx_arcanemissile_cast01";
	 sfxisambient = 1;
	 emtrjeasevel = 1400;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_AURA_active_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_AURA_active_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_RED_AURA_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

/* Made by Risepolak (Xardas17) */


instance  spellfx_ringritual_kasdeja (cfx_base_proto)
{    	visname_s  =  "mfx_ringritual_kasdeja";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_ritualorc_blood (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_ani";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_ritualorc_blood_start (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_ani";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_ritualstaff (cfx_base_proto)
{    	visname_s  =  "mfx_ritualstaff";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_thunderbolt_cast";
};

instance  spellfx_ritual_bridge (cfx_base_proto)
{    	visname_s  =  "mfx_ritual_bridge";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_ritual_cast (cfx_base_proto)
{    	visname_s  =  "mfx_ritual_cast";
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
};

instance  spellfx_ritual_firebridge (cfx_base_proto)
{    	visname_s  =  "mfx_ritual_firebridge";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_ritual_init (cfx_base_proto)
{    	visname_s  =  "mfx_ritual_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
};

instance  spellfx_runesword (cfx_base_proto)
{    	visname_s  =  "mfx_runesword";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_runesword_attack (cfx_base_proto)
{    	visname_s  =  "mfx_runesword";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_runesword_collide";
};

instance  spellfx_rune_vob (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_idle2";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance spellfx_schmetterarrow(cfx_base_proto)
{
	visname_s = "schmetter_arrow";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 2000000;
	emfxlifespan = -1;
	emselfrotvel_s = "000";
	secsperdamage = -1;
	emadjustshptoorigin = 1;
	lightpresetname = "redambience";
};

instance spellfx_schmetterarrow_key_invest_1(c_particlefxemitkey)
{
	lightrange = 100;
};

instance spellfx_schmetterarrow_key_invest_2(c_particlefxemitkey)
{
	lightrange = 300;
};

instance spellfx_schmetterarrow_key_invest_3(c_particlefxemitkey)
{
	lightrange = 400;
};

instance  spellfx_schmetterschuss (cfx_base_proto)
{    	visname_s  =  "mfx_fakearrow_cast_neu";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_schmetterschuss_collide";
    	emfxcolldyn_s  =  "spellfx_schmetterschuss_collide";
    	emfxcolldynperc_s  =  "spellfx_schmetterschuss_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emcheckcollision  =  1;
    	emtrjeasevel  =  1800.0;
};

instance  spellfx_schmetterschussdeath (cfx_base_proto)
{    	visname_s  =  "mfx_fakearrow_cast_death";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_schmetterschussdeath_collide";
    	emfxcolldyn_s  =  "spellfx_skull_spread_black";
    	emfxcolldynperc_s  =  "spellfx_schmetterschussdeath_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emcheckcollision  =  1;
    	emtrjeasevel  =  1800.0;
};

instance  spellfx_schmetterschussdeath_collide (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_collide";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "bip01 spine2";
    	sfxid  =  "mfx_breathofdeath_target";
    	sfxisambient  =  1;
};

instance  spellfx_schmetterschussdeath_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_breathofdeath_cast";
    	sfxisambient  =  1;
};

instance  spellfx_schmetterschussdeath_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_collide";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "bip01 spine2";
    	sfxid  =  "mfx_breathofdeath_target";
    	sfxisambient  =  1;
    	sendassessmagic  =  1;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_schmetterschussfake (cfx_base_proto)
{    	visname_s  =  "mfx_arkmisinvis_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_schmetterschuss_collide";
    	emfxcolldyn_s  =  "spellfx_schmetterschuss_collide";
    	emfxcolldynperc_s  =  "spellfx_schmetterschuss_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_schmetterschussfake_flydamage (cfx_base_proto)
{    	visname_s  =  "mfx_arkmisinvis_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_schmetterschussfake_flydamage_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_schmetterschussfake_flydamage_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_arkmisinvis_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1300.0;
    	emcheckcollision  =  1;
};

instance  spellfx_schmetterschussfake_flydamage_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_schmetterschussfake_flydamage_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arkmisinvis_init";
};

instance  spellfx_schmetterschussfake_flydamage_key_open (c_particlefxemitkey)
{};

instance  spellfx_schmetterschussfake_flydamage_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_schmetterschussfake_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_arkmisinvis_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1300.0;
    	emcheckcollision  =  1;
};

instance  spellfx_schmetterschussfake_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_schmetterschussfake_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_arkmisinvis_init";
};

instance  spellfx_schmetterschussfake_key_open (c_particlefxemitkey)
{};

instance  spellfx_schmetterschussice (cfx_base_proto)
{    	visname_s  =  "mfx_fakearrow_cast_ice";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_schmetterschussice_collide";
    	emfxcolldyn_s  =  "spellfx_schmetterschussice_collide";
    	emfxcolldynperc_s  =  "spellfx_schmetterschussice_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emcheckcollision  =  1;
    	emtrjeasevel  =  1800.0;
};

instance  spellfx_schmetterschussice_collide (cfx_base_proto)
{    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_icecube_collide";
};

instance  spellfx_schmetterschussice_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_icecube_cast";
    	sfxisambient  =  1;
};

instance  spellfx_schmetterschussice_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_icespell4seconds_target";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sendassessmagic  =  1;
    	emadjustshptoorigin  =  1;
    	sfxid  =  "mfx_icecube_target";
};

instance  spellfx_schmetterschussmanashoot (cfx_base_proto)
{    	visname_s  =  "mfx_fakearrow_cast_manashoot";
    	emtrjmode_s  =  "TARGET";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_destroyundead_collide";
    	emfxcolldyn_s  =  "spellfx_destroyundead_collidedynfx";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emcheckcollision  =  1;
    	emtrjeasevel  =  1800.0;
};

instance  spellfx_schmetterschussmanashoot_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_destroyundead_cast";
    	sfxisambient  =  1;
};

instance  spellfx_schmetterschuss_collide (cfx_base_proto)
{    	visname_s  =  "gfa_impact";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "spellfx_extricate_collidedynfx";
    	emtrjmode_s  =  "FIXED";
    	emfxlifespan  =  5.0;
};

instance  spellfx_schmetterschuss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_destroyundead_cast";
    	sfxisambient  =  1;
};

instance  spellfx_schmetterschuss_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_schutz (cfx_base_proto)
{    	visname_s  =  "mfx_light_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxinvestorigin_s  =  "spellfx_light_origin";
    	lightpresetname  =  "aura";
};

instance  spellfx_schutzkugel (cfx_base_proto)
{    	visname_s  =  "pfx_schutzkugel";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_schutz_cast (cfx_base_proto)
{    	visname_s  =  "mfx_light_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_schutz_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_light_cast";
    	pfx_ppsisloopingchg  =  1;
    	lightrange  =  400.0;
};

instance  spellfx_schutz_key_init (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_schutz_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_schutz_key_open (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_schutz_origin (cfx_base_proto)
{    	visname_s  =  "mfx_light_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_light_ring";
    	sfxid  =  "mfx_light_invest";
    	sfxisambient  =  1;
};

instance  spellfx_schutz_ring (cfx_base_proto)
{    	visname_s  =  "mfx_light_ring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_schwaechen (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "pingpong_once";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_schwaechen_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_schwaechen_invest";
};

instance  spellfx_schwaechen_bloodfly (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_flytoplayer";
    	emtrjeasevel  =  0.01;
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 spine2";
    	emtrjtargetnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.01;
};

instance  spellfx_schwaechen_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_schwaechen_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_schwaechen_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_schwaechen_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_schwaechen_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_schwaechen_slowtime (cfx_base_proto)
{    	emfxtriggerdelay  =  6.0;
    	emfxlifespan  =  30.0;
    	visname_s  =  "morph.fov";
    	userstring  =  "0.8";
    	userstring[1]  =  "1.0";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
};

instance  spellfx_seelenraub (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_seelenraub_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_seelenraub_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_init";
};

instance  spellfx_seelenraub_origin (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_seelenraub_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "mfx_sleep_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_seraphiaspell (cfx_base_proto)
{    	visname_s  =  "mfx_seraphiaspell_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_seraphiaspell_collide";
    	emfxcolldyn_s  =  "spellfx_seraphiaspell_collidedynfx";
    	emfxcolldynperc_s  =  "vob_magicburn";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_seraphiaspell_collide (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_seraphiaspell_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_fireball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_seraphiaspell_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_seraphiaspell_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_fireball_collide1";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_seraphiaspell_firecloud (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "mfx_seraphiaspell_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_seraphiaspell_firecloud_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_seraphiaspell_key_cast (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	visname_s  =  "mfx_seraphiaspell_pfxtrail";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_seraphiaspell_firecloud";
    	emcheckcollision  =  1;
};

instance  spellfx_seraphiaspell_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_seraphiaspell_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_seraphiaspell_init";
    	lightrange  =  0.01;
};

instance  spellfx_seraphiaspell_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_seta (cfx_base_proto)
{    	visname_s  =  "mfx_seta_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_seta_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_seta_origin";
};

instance  spellfx_seta_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_seta_init";
    	emcreatefxid  =  "spellfx_seta_lefthand";
};

instance  spellfx_seta_origin (cfx_base_proto)
{    	visname_s  =  "mfx_seta_glow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  1000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "aura";
    	secsperdamage  =  -1.0;
    	emfxcreate_s  =  "seta_mode";
};

instance  spellfx_shrink_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_shrink_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance spellfx_skeleton(cfx_base_proto)
{
	visname_s = "mfx_summondemon_init";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	lightpresetname = "redambience";
	emfxinvestorigin_s = "spellfx_demon_invest";
};

instance spellfx_skeleton_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
	lightrange = 200;
};

instance spellfx_skeleton_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_skeleton_key_invest_1(c_particlefxemitkey)
{	lightrange = 400;};

instance spellfx_skeleton_key_invest_2(c_particlefxemitkey)
{};

instance spellfx_skeleton_key_invest_3(c_particlefxemitkey)
{	emcreatefxid = "fx_earthquake";};

instance spellfx_skeleton_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance  spellfx_skull_dark_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_skull_collide_dark";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_skull_collide";
    	lightpresetname  =  "redambience";
};

instance  spellfx_skull_dark_spread (cfx_base_proto)
{    	visname_s  =  "mfx_skull_spread_dark";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_skull_dark_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_skull_skull1 (cfx_base_proto)
{    	visname_s  =  "mfx_skull_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_skull_skull1_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_skull_fly";
};

instance  spellfx_skull_skull_dark (cfx_base_proto)
{    	visname_s  =  "mfx_skull_cast_dark";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  20.0;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  25.0;
    	emtrjnumkeys  =  2;
    	emtrjnumkeysvar  =  1;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_skull_dark_collidefx";
    	emfxcolldyn_s  =  "spellfx_skull_dark_spread";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emtrjeasevel  =  700.0;
};

instance  spellfx_skull_skull_dark_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_skull_fly";
};

instance  spellfx_skull_spread_black (cfx_base_proto)
{    	visname_s  =  "mfx_skull_spread_dark";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "create createquad";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_skull_collidefx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	sfxid  =  "mfx_firestorm_collide";
    	sfxisambient  =  1;
};

instance  spellfx_slomo (cfx_base_proto)
{    	visname_s  =  "mfx_slomo_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_slomo_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	sfxid  =  "sfx_innoseye";
    	sfxisambient  =  1;
    	emcreatefxid  =  "spellfx_slomo_origin";
};

instance  spellfx_slomo_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_slomo_init";
};

instance  spellfx_slomo_origin (cfx_base_proto)
{    	visname_s  =  "mfx_slomo_glow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  1000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "aura";
    	secsperdamage  =  -1.0;
    	emfxcreate_s  =  "slomo_mode";
};

instance  spellfx_smallblizzard (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_00 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_00_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_00_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_00_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_01 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_01_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_01_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_01_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_02 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_02_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_02_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_02_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_03 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_03_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_03_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_03_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_04 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_04_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_04_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_04_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_05 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_05_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_05_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_05_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_06 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_06_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_06_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_06_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_07 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_07_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_07_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_07_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_08 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_08_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_08_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_08_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_09 (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_smallblizzard_09_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_09_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_09_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance  spellfx_smallblizzard_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_smallblizzard_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_smallblizzard_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emfxlifespan  =  3.0;
};

instance  spellfx_smallblizzard_rain (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_rain_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_firerain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_smallblizzard_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_smallblizzard_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  3.0;
};

instance  spellfx_smallblizzard_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance spellfx_smierc(cfx_base_proto)
{
	visname_s = "cast7";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "Bip01 Head";
	emtrjnumkeys = 1;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 15.;
	emtrjangleheadvar = 0.;
	emtrjdynupdatedelay = 0.;
	emfxinvesttarget_s = "spellfx_pyrokinesis_target";
	emtrjtargetrange = 0;
	emtrjtargetelev = 0;
};

instance spellfx_smierc_2(cfx_base_proto)
{
	visname_s = "itmw_1h_sword_bastard_04.3ds";
	emtrjoriginnode = "zs_lefthand";
};

instance spellfx_SNOWBALL_0 (CFX_BASE_PROTO)
{
	 visname_s = "Wulwryk_BSM_274";
	 lightpresetname = "SNOW_BALL";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SNOWBALL_1 (CFX_BASE_PROTO)
{
	 visname_s = "SNOWBALL";
	 lightpresetname = "SNOW_BALL1";
};

/* Made by Risepolak (Xardas17) */


/* Made by Risepolak (Xardas17) */


instance  spellfx_soulrobber (cfx_base_proto)
{    	visname_s  =  "mfx_soulrobber_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_soulrobber_active";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_soulrobberheal (cfx_base_proto)
{    	visname_s  =  "mfx_soulrobber_soul";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_soulrobberheal_sendperception";
    	emfxlifespan  =  12.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_soulrobberhealbeliardebuff (cfx_base_proto)
{    	visname_s  =  "mfx_soulrobber_soul";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_soulrobberhealbeliardebuff_sendperception";
    	emfxlifespan  =  12.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_soulrobberhealbeliardebuff_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_soulrobber_soul";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  650.0;
    	emtrjdynupdatedelay  =  0.1;
    	emfxlifespan  =  12.0;
    	emtrjdynupdatetargetonly  =  1;
    	emfxcolldynperc_s  =  "spellfx_soulrobberhealbeliardebuff_sendperception";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_soulrobberhealbeliardebuff_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_breathofdeath_target";
};

instance  spellfx_soulrobberhealbeliardebuff_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_soulrobberhealbeliardebuff_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_soulrobberhealbeliardebuff_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_soulrobberhealbeliardebuff_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_soulrobber_soul";
    	lightrange  =  0.001;
};

instance  spellfx_soulrobberhealbeliardebuff_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_soulrobberhealbeliardebuff_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_soulrobberheal_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_soulrobber_soul";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  650.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emfxcolldynperc_s  =  "spellfx_soulrobberheal_sendperception";
    	emfxcreatedowntrj  =  1;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxlifespan  =  12.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_soulrobberheal_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_breathofdeath_target";
};

instance  spellfx_soulrobberheal_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_soulrobberheal_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_soulrobberheal_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_soulrobberheal_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_soulrobber_soul";
    	lightrange  =  0.001;
};

instance  spellfx_soulrobberheal_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_soulrobberheal_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_soulrobberspellhotkey (cfx_base_proto)
{    	visname_s  =  "mfx_light_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_soulrobberspellhotkey_active";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_soulrobberspellhotkey_active (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_soulrobberspellhotkey_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_soulrobber_origin_spellhotkey";
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_soulrobberspellhotkey_active_key_init (c_particlefxemitkey)
{};

instance  spellfx_soulrobberspellhotkey_active_key_open (c_particlefxemitkey)
{};

instance  spellfx_soulrobberspellhotkey_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_soulrobber_active (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  70.0;
};

instance  spellfx_soulrobber_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_soulrobber_origin";
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
    	emtrjeasevel  =  1000.0;
};

instance  spellfx_soulrobber_active_key_init (c_particlefxemitkey)
{};

instance  spellfx_soulrobber_active_key_open (c_particlefxemitkey)
{};

instance  spellfx_soulrobber_hero (cfx_base_proto)
{    	visname_s  =  "druznash_holyshield";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_soulrobber_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_soulrobber_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_soulrobber_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_soulsplit (cfx_base_proto)
{    	visname_s  =  "mfx_heal_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_soulsplit_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_soulsplit_origin";
};

instance  spellfx_soulsplit_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_heal_cast";
    	emcreatefxid  =  "spellfx_soulsplit_lefthand";
};

instance  spellfx_soulsplit_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_heal_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_soulsplit_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_soulsplit_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_soulsplit_origin (cfx_base_proto)
{    	visname_s  =  "mfx_soul_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_heal_cast";
    	sfxisambient  =  1;
};

instance  spellfx_spawn_cast (cfx_base_proto)
{    	visname_s  =  "mfx_spawn_cast";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "whiteblend";
};

instance  spellfx_specialweapon (cfx_base_proto)
{    	visname_s  =  "special_weapon";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_speed(cfx_base_proto)
{
	visname_s = "mfx_heal_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emfxinvestorigin_s = "spellfx_speed_origin";
};

instance  spellfx_speed_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_light_origin";
    	lightrange  =  1000.0;
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_speed_active_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_speed_active_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance spellfx_speed_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_speed_key_invest_1(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_speed_start";
};

instance spellfx_speed_origin(cfx_base_proto)
{
	visname_s = "mfx_heal_invest";
	visalpha = 1;
	lightpresetname = "aura";
	emtrjmode_s = "FIXED";
};

instance spellfx_speed_start(cfx_base_proto)
{
	visname_s = "mfx_heal_start";
	sfxid = "mfx_heal_cast";
	sfxisambient = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01rfoot";
};

instance spellfx_spidercube(cfx_base_proto)
{
	visname_s = "mfx_spidercube_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collideCREATEONCE";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_spidercube_collide";
	emfxcolldyn_s = "spellfx_icespell_target";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellfx_spiderspell_invest";
	lightpresetname = "aura";
};

instance spellfx_spidercube_collide(cfx_base_proto)
{
	visname_s = "mfx_spiderspell_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_spidercube_collide";
};

instance spellfx_spidercube_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_spidercube_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400.;
	emcheckcollision = 1;
	sfxid = "crw_attack";
	sfxisambient = 1;
	lightrange = 200;
};

instance spellfx_spidercube_key_collide(c_particlefxemitkey)
{
	emtrjeasevel = 0.000001;
};

instance spellfx_spidercube_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_spidercube_init";
	lightrange = 0.01;
	scaleduration = 0.5;
};

instance spellfx_spidercube_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_spiderspell_invest(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	sfxid = "mfx_spidercube_invest";
	sfxisambient = 1;
};

instance spellfx_SPIDER_QUEEN_FOOG_V0 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V0_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_SPIDER_QUEEN_FOOG_V0_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_SPIDER_QUEEN_FOOG_V0_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "SPIDER_QUEEN_FOOG_V0";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V0_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V0_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V0_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V1 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V1_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_SPIDER_QUEEN_FOOG_V1_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_SPIDER_QUEEN_FOOG_V1_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "SPIDER_QUEEN_FOOG_V1";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V1_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V1_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V1_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V2 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V2_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_SPIDER_QUEEN_FOOG_V2_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_SPIDER_QUEEN_FOOG_V2_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "SPIDER_QUEEN_FOOG_V2";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V2_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V2_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V2_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V3 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V3_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_SPIDER_QUEEN_FOOG_V3_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_SPIDER_QUEEN_FOOG_V3_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "SPIDER_QUEEN_FOOG_V3";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V3_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V3_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V3_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */

instance spellfx_SPIDER_QUEEN_FOOG_V4 (CFX_BASE_PROTO)
{
	 visname_s = "FIRE_Green_1";
	 visalpha = 1;
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 lightpresetname = "ZIELONY";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V4_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_SPIDER_QUEEN_FOOG_V4_key_cast_origin";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_SPIDER_QUEEN_FOOG_V4_key_cast_origin (CFX_BASE_PROTO)
{
	 visname_s = "SPIDER_QUEEN_FOOG_V4";
	 emtrjmode_s = "FIXED";
	 emtrjoriginnode = "Bip01";
	 emtrjdynupdatedelay = 0;
	 sfxid = "BCR_EATING";
	 lightpresetname = "ZIELONY";
	 sfxisambient = 1;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V4_key_init (C_PARTICLEFXEMITKEY)
{
	 lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V4_key_invest_1 (C_PARTICLEFXEMITKEY)
{
	 lightrange = 200;
};

/* Made by Risepolak (Xardas17) */


instance spellfx_SPIDER_QUEEN_FOOG_V4_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

/* Made by Risepolak (Xardas17) */

instance  spellfx_spiral2_green (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large3";
    	emtrjoriginnode  =  "bip01";
    	emselfrotvel_s  =  "50 -130 0";
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_spiral3_green";
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_spiral2_green_verjuengung (cfx_base_proto)
{    	visname_s  =  "mfx_ring_verjuengung_large3";
    	emtrjoriginnode  =  "bip01";
    	emselfrotvel_s  =  "50 -130 0";
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_spiral3_green_verjuengung";
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  400.0;
};

instance  spellfx_spiral3_green (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large1";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 -150 -40";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_spiral3_green_verjuengung (cfx_base_proto)
{    	visname_s  =  "mfx_ring_verjuengung_large1";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 -150 -40";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emtrjtargetelev  =  400.0;
};

instance  spellfx_spiral4_green (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large3";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "20 130 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_spiral_ghostarmor_1 (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large1";
    	emtrjoriginnode  =  "bip01";
    	emselfrotvel_s  =  "0 80 0";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_spiral_ghostarmor_2 (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large3";
    	emtrjoriginnode  =  "bip01";
    	emselfrotvel_s  =  "50 -130 0";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_spiral_ghostarmor_3 (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large1";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "0 -150 -40";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_spiral_ghostarmor_4 (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large3";
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	emselfrotvel_s  =  "20 130 0";
    	emtrjdynupdatedelay  =  0.0;
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_spiral_green (cfx_base_proto)
{    	visname_s  =  "mfx_ring_green_large1";
    	emtrjoriginnode  =  "bip01";
    	emselfrotvel_s  =  "0 80 0";
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_spiral2_green";
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_spiral_green_verjuengung (cfx_base_proto)
{    	visname_s  =  "mfx_ring_verjuengung_large1";
    	emtrjoriginnode  =  "bip01";
    	emselfrotvel_s  =  "0 80 0";
    	emfxcreatedowntrj  =  1;
    	emfxcreate_s  =  "spellfx_spiral2_green_verjuengung";
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  400.0;
};

instance spellfx_sprengstoffarrow(cfx_base_proto)
{
	visname_s = "sprengstoff_arrow";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 2000000;
	emfxlifespan = -1;
	emselfrotvel_s = "000";
	secsperdamage = -1;
	emadjustshptoorigin = 1;
	lightpresetname = "justwhite";
};

instance spellfx_sprengstoffarrow_key_invest_1(c_particlefxemitkey)
{
	lightrange = 100;
};

instance spellfx_sprengstoffarrow_key_invest_2(c_particlefxemitkey)
{
	lightrange = 300;
};

instance spellfx_sprengstoffarrow_key_invest_3(c_particlefxemitkey)
{
	lightrange = 400;
};

instance  spellfx_sprint (cfx_base_proto)
{    	visname_s  =  "mfx_sprint_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
};

instance  spellfx_sprint_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "spellfx_sprint_origin";
};

instance  spellfx_sprint_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_sprint_cast";
    	emcreatefxid  =  "spellfx_sprint_lefthand";
};

instance  spellfx_sprint_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_sprint_cast";
    	emtrjoriginnode  =  "zs_lefthand";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "aura";
};

instance  spellfx_sprint_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_sprint_lefthand_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_sprint_origin (cfx_base_proto)
{    	visname_s  =  "mfx_sprint_heavenlight";
    	emtrjoriginnode  =  "bip01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_sprint_cast";
    	sfxisambient  =  1;
};

instance  spellfx_spucke (cfx_base_proto)
{    	visname_s  =  "mfx_spucke_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_spucke_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_spucke_cast";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_spucke_collidefx";
    	emfxcolldyn_s  =  "spellfx_spucke_collidedynfx";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_spucke_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_spucke_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_spucke_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_spucke_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_spucke_collidefx (cfx_base_proto)
{    	visname_s  =  "mfx_spucke_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_spucke_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_spucke_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_spucke_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_spucke_init";
    	lightrange  =  0.001;
};

instance  spellfx_spucke_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance spellfx_staf_dead(cfx_base_proto)
{
	visname_s = "staf_dead";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "redambience";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "zom_die";
};

instance spellfx_staf_elektric(cfx_base_proto)
{
	visname_s = "staf_elektric";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "aura";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "mfx_beliarweap";
};

instance spellfx_staf_ice(cfx_base_proto)
{
	visname_s = "staf_ice";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreatecreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "aura";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "4040";
	userstring[2] = "mul";
	sfxid = "mfx_icewave_cast";
};

instance  spellfx_stargate_effect (cfx_base_proto)
{    	visname_s  =  "mfx_magicrune_idle";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjeasevel  =  0.0;
    	emtrjmode_s  =  "follow target";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  0.4;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_stealthball_ice (cfx_base_proto)
{    	visname_s  =  "mfx_invisibleprojectile";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_stealthball_ice_collide";
    	emfxcolldyn_s  =  "spellfx_stealthball_ice_collidedynfx";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	lightpresetname  =  "justwhite";
};

instance  spellfx_stealthball_ice_collide (cfx_base_proto)
{    	visname_s  =  "mfx_icebreath_collide1";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	lightpresetname  =  "whiteblend";
    	sfxid  =  "mfx_iceball_collide";
};

instance  spellfx_stealthball_ice_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_icebreath_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_iceball_collide";
};

instance  spellfx_stealthball_ice_collidedynfx_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_stealthball_ice_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "";
    	sfxid  =  "mfx_fireball_collide1";
};

instance  spellfx_stealthball_ice_firecloud (cfx_base_proto)
{    	emtrjeasevel  =  1400.0;
    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "TARGET";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  20000.0;
    	emcheckcollision  =  2;
    	emactioncolldyn_s  =  "collide";
    	emactioncollstat_s  =  "collide";
};

instance  spellfx_stealthball_ice_firecloud_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_stealthball_ice_key_cast (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	visname_s  =  "";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_fireball_cast";
    	sfxisambient  =  1;
    	emcreatefxid  =  "";
    	emcheckcollision  =  1;
};

instance  spellfx_stealthball_ice_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	sfxid  =  "mfx_iceball_collide";
};

instance  spellfx_stealthball_ice_key_init (c_particlefxemitkey)
{    	visname_s  =  "";
    	lightrange  =  0.01;
};

instance  spellfx_stealthball_ice_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_stealthwave (cfx_base_proto)
{    	visname_s  =  "mfx_invisibleprojectile";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_stealthwave_collide";
    	emfxcolldyn_s  =  "spellfx_stealthwave_collidedynfx";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emfxcreatedowntrj  =  0;
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_stealthwave_collide (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_stealthwave_collidedynfx (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_stealthwave_key_cast (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	visname_s  =  "";
    	emtrjmode_s  =  "TARGET";
    	emselfrotvel_s  =  "100 100 100";
    	emtrjeasevel  =  1400.0;
    	emcreatefxid  =  "";
    	emcheckcollision  =  1;
};

instance  spellfx_stealthwave_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_stealthwave_key_init (c_particlefxemitkey)
{    	visname_s  =  "";
    	lightrange  =  0.01;
};

instance  spellfx_stealthwave_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_stomperdust (cfx_base_proto)
{    	visname_s  =  "stomperdust";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "BLEND";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  2.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance spellfx_stormfist(cfx_base_proto)
{
	visname_s = "mfx_windfist_init";
	vissize_s = "11";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjnumkeys = 7;
	emtrjnumkeysvar = 3;
	emtrjangleelevvar = 5.;
	emtrjangleheadvar = 20.;
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 200000;
	emtrjtargetrange = 100;
	emtrjtargetelev = 1;
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_windfist_target";
	emfxinvestorigin_s = "spellfx_windfist_invest";
};

instance  spellfx_stormfistnpconly (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxinvestorigin_s  =  "spellfx_windfist_invest";
};

instance  spellfx_stormfistnpconlylategame (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxinvestorigin_s  =  "spellfx_windfist_invest";
};

instance  spellfx_stormfistnpconlylategame_cast (cfx_base_proto)
{    	visname_s  =  "mfx_stormfist_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_stormfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_stormfistnpconlylategame_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_collide";
    	sendassessmagic  =  1;
};

instance  spellfx_stormfistnpconlylategame_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_stormfistnpconlylategame_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_stormfistnpconlylategame_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_stormfist_cast";
};

instance  spellfx_stormfistnpconlylategame_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_stormfistnpconly_cast (cfx_base_proto)
{    	visname_s  =  "mfx_stormfist_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_stormfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_stormfistnpconly_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_collide";
    	sendassessmagic  =  1;
};

instance  spellfx_stormfistnpconly_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_stormfistnpconly_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_stormfistnpconly_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_stormfist_cast";
};

instance  spellfx_stormfistnpconly_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_stormfist_cast (cfx_base_proto)
{    	visname_s  =  "mfx_stormfist_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_stormfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_stormfist_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_collide";
    	sendassessmagic  =  1;
};

instance spellfx_stormfist_invest(cfx_base_proto)
{
	visname_s = "mfx_windfist_invest";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
};

instance  spellfx_stormfist_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance spellfx_stormfist_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_stormfist_cast";
	emcheckcollision = 1;
	sfxid = "mfx_stormfist_cast";
	sfxisambient = 1;
};

instance spellfx_stormfist_key_init(c_particlefxemitkey)
{
	emcheckcollision = 0;
};

instance  spellfx_storm_ring_elementalorc (cfx_base_proto)
{    	visname_s  =  "mfx_stormring_fadeout_long";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_stun (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  10000.0;
};

instance  spellfx_stunvictim (cfx_base_proto)
{    	visname_s  =  "stunvictim";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_stunvictim_key_cast (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_stun_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_stun_key_invest_1 (c_particlefxemitkey)
{};

instance  spellfx_stun_key_open (c_particlefxemitkey)
{    	emtrjeasevel  =  0.0;
};

instance  spellfx_stun_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_suckenergy2 (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_suckenergy2_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
    	emfxinvestorigin_s  =  "spellfx_suckenergy2_invest";
};

instance  spellfx_suckenergy2_invest (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_suckenergy2_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_suckenergy_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_suckenergy2_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_suckenergy2_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_suckenergy2_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_suckenergy_target";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_suckenergy_target";
};

instance  spellfx_suckenergy2_slowtime (cfx_base_proto)
{    	emfxtriggerdelay  =  6.0;
    	emfxlifespan  =  30.0;
    	visname_s  =  "morph.fov";
    	userstring  =  "0.8";
    	userstring[1]  =  "1.0";
    	userstring[2]  =  "120";
    	userstring[3]  =  "90";
};

instance  spellfx_summon1hbeliarweapon (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
};

instance  spellfx_summon1hbeliarweapon_investglow (cfx_base_proto)
{    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_summon1hbeliarweapon_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summon1hbeliarweapon_investglow";
    	pfx_ppsisloopingchg  =  0;
    	emfxlifespan  =  1.0;
};

instance  spellfx_summon1hbeliarweapon_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_summon1hbeliarweapon_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_breathofdeath_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.0;
    	visalpha  =  1.0;
};

instance  spellfx_summoncrawler (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summoncrawler_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summoncrawler_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summoncrawler_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summoncrawler_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summoncreaturefire_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_summfiregolem_init2";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
};

instance  spellfx_summoncreaturefire_origin (cfx_base_proto)
{    	visname_s  =  "mfx_summfiregolem_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summoncreatureice_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_summicegolem_init2";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
};

instance  spellfx_summoncreatureice_origin (cfx_base_proto)
{    	visname_s  =  "mfx_summicegolem_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summoncreaturestone_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_summstonegolem_init2";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
};

instance  spellfx_summoncreaturestone_origin (cfx_base_proto)
{    	visname_s  =  "mfx_summstonegolem_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summoncreatureswamp_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_summswampgolem_init2";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
};

instance  spellfx_summoncreatureswamp_origin (cfx_base_proto)
{    	visname_s  =  "mfx_summswampgolem_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summoncreaturewood_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_summwoodgolem_init2";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
};

instance  spellfx_summoncreaturewood_origin (cfx_base_proto)
{    	visname_s  =  "mfx_summwoodgolem_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summondragon (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summondragonsnapper (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summondragonsnapper_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summondragonsnapper_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summondragonsnapper_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summondragonsnapper_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summondragon_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summondragon_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summondragon_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summondragon_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summoneisgoblin (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summoneisgoblin_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summoneisgoblin_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summoneisgoblin_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summoneisgoblin_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonerorcspell (cfx_base_proto)
{    	visname_s  =  "mfx_summonerorc_small_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_abyss (cfx_base_proto)
{    	visname_s  =  "summoner_orc_spell";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_fireball_cast";
};

instance  spellfx_summonerorcspell_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_summonerorcspell_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summonerorcspell_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonerorcspell_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_summonerorc_init";
    	lightrange  =  0.001;
};

instance  spellfx_summonerorcspell_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_summonerorcspell_soultransfer (cfx_base_proto)
{    	visname_s  =  "mfx_summonerorc_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_soultransferfast (cfx_base_proto)
{    	visname_s  =  "mfx_summonerorc_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  600.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_soultransferfast_abyss (cfx_base_proto)
{    	visname_s  =  "summoner_orc_soul_transfer";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  600.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_soultransferfast_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_fireball_cast";
};

instance  spellfx_summonerorcspell_soultransferfast_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_summonerorcspell_soultransferfast_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summonerorcspell_soultransferfast_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonerorcspell_soultransferfast_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_summonerorc_init";
    	lightrange  =  0.001;
};

instance  spellfx_summonerorcspell_soultransferfast_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_summonerorcspell_soultransfer_abyss (cfx_base_proto)
{    	visname_s  =  "summoner_orc_soul_transfer";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  200.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_soultransfer_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_fireball_cast";
};

instance  spellfx_summonerorcspell_soultransfer_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_summonerorcspell_soultransfer_atspawn (cfx_base_proto)
{    	visname_s  =  "mfx_summonerorc_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  12.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_soultransfer_atspawn_abyss (cfx_base_proto)
{    	visname_s  =  "summoner_orc_soul_transfer_atspawn";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  20.0;
    	emtrjangleheadvar  =  30.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  200.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_summonerorcspell_soultransfer_atspawn_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_fireball_cast";
};

instance  spellfx_summonerorcspell_soultransfer_atspawn_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_summonerorcspell_soultransfer_atspawn_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summonerorcspell_soultransfer_atspawn_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonerorcspell_soultransfer_atspawn_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_summonerorc_init";
    	lightrange  =  0.001;
};

instance  spellfx_summonerorcspell_soultransfer_atspawn_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_summonerorcspell_soultransfer_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summonerorcspell_soultransfer_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonerorcspell_soultransfer_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_summonerorc_init";
    	lightrange  =  0.001;
};

instance  spellfx_summonerorcspell_soultransfer_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_summoner_orc_weapon (cfx_base_proto)
{    	visname_s  =  "mfx_summoner_orc_weapon";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_summonfeuerbeast (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonfeuerbeast_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonfeuerbeast_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonfeuerbeast_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonfeuerbeast_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonfirebeast (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonfirebeast_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonfirebeast_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonfirebeast_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonfirebeast_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonflameguardian_origin (cfx_base_proto)
{    	visname_s  =  "mfx_flameguardian_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_light_cast";
    	sfxisambient  =  1;
};

instance  spellfx_summongeist (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summongeist_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summongeist_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summongeist_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summongeist_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonghostwolf (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolf_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "poison";
};

instance  spellfx_summonghostwolfrosa (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolfpink_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "poison";
};

instance  spellfx_summonghostwolfrosa_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summonghostwolf_origin_pink";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonghostwolfrosa_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonghostwolfrosa_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonghostwolfrosa_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonghostwolf_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summonghostwolf_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonghostwolf_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonghostwolf_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonghostwolf_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonghostwolf_lefthand_short (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolf_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  0.8;
    	visalpha  =  1.0;
};

instance  spellfx_summonghostwolf_origin (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolf_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summonghostwolf_origin_pink (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolf_origin_pink";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summonghostwolf_origin_pink_withoutsound (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolf_origin_pink";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summonghostwolf_origin_withoutsound (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolf_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summonghostwolf_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolf_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_summonghostwolf_righthand_pink (cfx_base_proto)
{    	visname_s  =  "mfx_summonghostwolfpink_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_summongoblinblack (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summongoblinblack_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summongoblinblack_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summongoblinblack_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summongoblinblack_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summongoblinkrieger (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summongoblinkrieger_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summongoblinkrieger_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summongoblinkrieger_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summongoblinkrieger_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summongolem_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_summonhagen (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonhagen_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonhagen_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonhagen_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonhagen_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance spellfx_summonharpie(cfx_base_proto)
{
	visname_s = "mfx_summongreen_init";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	lightpresetname = "aura";
	emfxinvestorigin_s = "spellfx_summonharpie_invest";
};

instance spellfx_summonharpie_invest(cfx_base_proto)
{
	visname_s = "mfx_summongreen_invest";
	emtrjoriginnode = "bip01";
};

instance spellfx_summonharpie_key_cast(c_particlefxemitkey)
{
	pfx_ppsisloopingchg = 1;
};

instance spellfx_summonharpie_key_init(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance spellfx_summonharpie_key_invest_1(c_particlefxemitkey)
{
	lightrange = 400;
};

instance spellfx_summonharpie_key_invest_2(c_particlefxemitkey)
{
};

instance spellfx_summonharpie_key_invest_3(c_particlefxemitkey)
{
	emcreatefxid = "fx_earthquake";
};

instance spellfx_summonharpie_key_open(c_particlefxemitkey)
{
	lightrange = 0.01;
};

instance  spellfx_summonicewolf (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonicewolf_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summonicewolf_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonicewolf_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonicewolf_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonicewolf_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonicewolf_origin (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_summonrabbit (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonrabbit_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonrabbit_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonrabbit_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonrabbit_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonrats (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonrats_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonrats_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonrats_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonrats_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonshadowskel (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonshadowskel_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonshadowskel_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonshadowskel_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonshadowskel_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonsnapper (cfx_base_proto)
{    	visname_s  =  "mfx_summstonegolem_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonsnapper_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreaturestone_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonsnapper_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonsnapper_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonsnapper_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonudswampshark (cfx_base_proto)
{    	visname_s  =  "mfx_armyofdarkness_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonudswampshark_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonudswampshark_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonudswampshark_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonudswampshark_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonwoodgolem (cfx_base_proto)
{    	visname_s  =  "mfx_summwoodgolem_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "aura";
};

instance  spellfx_summonwoodgolem_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreaturewood_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonwoodgolem_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonwoodgolem_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_summonwoodgolem_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonzombiearmy (cfx_base_proto)
{    	visname_s  =  "mfx_summonzombiearmy_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_summonzombiearmy_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_summoncreature_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_summonzombiearmy_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_summonzombiearmy_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "spellfx_summoncreature_lefthand";
};

instance  spellfx_summonzombiearmy_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_sumskelwarrior (cfx_base_proto)
{    	visname_s  =  "mfx_sumskelwarrior_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	lightpresetname  =  "redambience";
};

instance  spellfx_sumskelwarrior_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_tarsessummon_origin";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_sumskelwarrior_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_sumskelwarrior_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
    	emcreatefxid  =  "fx_earthquake";
};

instance  spellfx_sumskelwarrior_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_sumskelwarrior_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_sumskelwarrior_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_sumskelwarrior_lefthand_short (cfx_base_proto)
{    	visname_s  =  "mfx_sumskelwarrior_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  0.8;
    	visalpha  =  1.0;
};

instance  spellfx_sumskelwarrior_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_sumskelwarrior_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  2.5;
    	visalpha  =  1.0;
};

instance  spellfx_swampdrone_spawnsphere (cfx_base_proto)
{    	visname_s  =  "mfx_swampdrone_spawnsphere";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_swampfist (cfx_base_proto)
{    	visname_s  =  "mfx_swampfist_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_swampfist_explode";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "aura";
};

instance  spellfx_swampfistsmall (cfx_base_proto)
{    	visname_s  =  "mfx_swampfistsmall_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_swampfistsmall_explode";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "aura";
};

instance  spellfx_swampfistsmall_explode (cfx_base_proto)
{    	visname_s  =  "swampdrone_explode";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "herb_stomp_a1";
    	sfxisambient  =  1;
};

instance  spellfx_swampfistsmall_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_swampfistsmall_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_swampfistsmall_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_swampfistsmall_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_swampfistsmall_key_invest (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_swampfistsmall_noise";
};

instance  spellfx_swampfistsmall_noise (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_waterfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_swampfist_explode (cfx_base_proto)
{    	visname_s  =  "swampdrone_explode";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "herb_stomp_a1";
    	sfxisambient  =  1;
};

instance  spellfx_swampfist_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_swampfist_cast";
    	emtrjmode_s  =  "target spline random";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_swampfist_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_swampfist_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_swampfist_key_invest (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_swampfist_noise";
};

instance  spellfx_swampfist_noise (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_waterfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_swarmarmor (cfx_base_proto)
{    	visname_s  =  "swarm_model";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_swarmarmor_key_cast (c_particlefxemitkey)
{};

instance  spellfx_swarm_zs1 (cfx_base_proto)
{    	visname_s  =  "mfx_swarm_target1";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	sfxid  =  "mfx_swarm_target";
};

instance  spellfx_swarm_zs2 (cfx_base_proto)
{    	visname_s  =  "mfx_swarm_target2";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	sfxid  =  "mfx_swarm_target";
};

instance  spellfx_swarm_zs3 (cfx_base_proto)
{    	visname_s  =  "mfx_swarm_target3";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	sfxid  =  "mfx_swarm_target";
};

instance  spellfx_tanzmover_blue (cfx_base_proto)
{    	visname_s  =  "mfx_tanzmover_blue";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_tanzmover_red (cfx_base_proto)
{    	visname_s  =  "mfx_tanzmover_red";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_tanzmover_violet (cfx_base_proto)
{    	visname_s  =  "mfx_tanzmover_violet";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_tanzmover_yellow (cfx_base_proto)
{    	visname_s  =  "mfx_tanzmover_yellow";
    	visalphablendfunc_s  =  "ADD";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  spellfx_targetheal (cfx_base_proto)
{    	visname_s  =  "mfx_targetheal_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_targetheal_target";
};

instance  spellfx_targetheal_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_targetheal_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_targetheal_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_targetheal_init";
};

instance  spellfx_targetheal_origin (cfx_base_proto)
{    	visname_s  =  "mfx_targetheal_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_targetheal_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "mfx_targetheal_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_tarsessummon_origin (cfx_base_proto)
{    	visname_s  =  "mfx_tarsessummon_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_transform_cast";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_tarsessummon_origin_withoutsound (cfx_base_proto)
{    	visname_s  =  "mfx_tarsessummon_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_telekinese (cfx_base_proto)
{    	visname_s  =  "mfx_telekinese_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 head";
    	emtrjnumkeys  =  1;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjdynupdatedelay  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_telekinese_target";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
};

instance  spellfx_telekinese_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_telekinese_target (cfx_base_proto)
{    	visname_s  =  "mfx_telekinese_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	lightpresetname  =  "firesmall";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	sendassessmagic  =  1;
    	emtrjdynupdatedelay  =  0.01;
    	sfxid  =  "mfx_telekinese_target";
    	sfxisambient  =  1;
};

instance  spellfx_telekinesis_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance spellfx_telekinesis_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_telekinesis_init";
	emtrjeasevel = 0.01;
};

instance  spellfx_teleport4 (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxinvestorigin_s  =  "spellfx_teleport_origin";
    	lightpresetname  =  "aura";
};

instance  spellfx_teleport4_cast (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_teleport_cast";
    	sfxisambient  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_teleport4_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_teleport_cast";
    	pfx_ppsisloopingchg  =  1;
    	lightrange  =  200.0;
};

instance  spellfx_teleport4_key_init (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_teleport4_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_teleport4_key_open (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_teleport4_origin (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_teleport_ring";
    	sfxid  =  "mfx_teleport_invest";
    	sfxisambient  =  1;
};

instance  spellfx_teleport4_ring (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleport5 (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxinvestorigin_s  =  "spellfx_teleport_origin";
    	lightpresetname  =  "aura";
};

instance  spellfx_teleport5_cast (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_teleport_cast";
    	sfxisambient  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_teleport5_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_teleport_cast";
    	pfx_ppsisloopingchg  =  1;
    	lightrange  =  200.0;
};

instance  spellfx_teleport5_key_init (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_teleport5_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_teleport5_key_open (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_teleport5_origin (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_teleport_ring";
    	sfxid  =  "mfx_teleport_invest";
    	sfxisambient  =  1;
};

instance  spellfx_teleport5_ring (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleporttonpc (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxinvestorigin_s  =  "spellfx_teleporttonpc_origin";
    	lightpresetname  =  "aura";
};

instance  spellfx_teleporttonpc_cast (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_teleport_cast";
    	sfxisambient  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_teleporttonpc_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_teleporttonpc_cast";
    	pfx_ppsisloopingchg  =  1;
    	lightrange  =  200.0;
};

instance  spellfx_teleporttonpc_key_init (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_teleporttonpc_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_teleporttonpc_key_open (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_teleporttonpc_origin (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_teleporttonpc_ring";
    	sfxid  =  "mfx_teleport_invest";
    	sfxisambient  =  1;
};

instance  spellfx_teleporttonpc_ring (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleport_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emfxlifespan  =  2.5;
};

instance  spellfx_teleport_origin_timed (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_teleport_ring";
    	sfxid  =  "mfx_teleport_invest";
    	sfxisambient  =  1;
    	emfxlifespan  =  2.5;
};

instance  spellfx_teleport_redring (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_redring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleport_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  2.5;
};

instance  spellfx_teleport_ring_black (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring_black";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleport_ring_red (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring_red";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleport_ring_ritualorc (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring_ritualorc";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleport_ring_ryanus (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring_ryanus";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_teleport_ring_white (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring_white";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance spellfx_test(cfx_base_proto)
{
	visname_s = "mfx_test_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_test_initglow";
	emfxcreatedowntrj = 0;
};

instance spellfx_testf(cfx_base_proto)
{
	visname_s = "mfx_test1_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_testf_initglow";
	emfxcreatedowntrj = 0;
};

instance spellfx_testf_ground(cfx_base_proto)
{
	visname_s = "mfx_test1_cast";
	emtrjoriginnode = "bip01rfoot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_testf_target";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "firesmall";
	sfxisambient = 1;
};

instance spellfx_testf_initglow(cfx_base_proto)
{
	visname_s = "mfx_test1_init_glow";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
};

instance spellfx_testf_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_testf_ground";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_testf_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_test1_init";
};

instance spellfx_testf_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
};

instance spellfx_testf_target(cfx_base_proto)
{
	visname_s = "mfx_test1_target";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sendassessmagic = 1;
};

instance spellfx_test_ground(cfx_base_proto)
{
	visname_s = "mfx_test_cast";
	emtrjoriginnode = "bip01rfoot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_test_target";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	sfxisambient = 1;
};

instance spellfx_test_initglow(cfx_base_proto)
{
	visname_s = "mfx_test_init_glow";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
};

instance spellfx_test_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_test_ground";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_test_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_test_init";
};

instance spellfx_test_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
};

instance spellfx_test_target(cfx_base_proto)
{
	visname_s = "mfx_test_target";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_test_target";
	sendassessmagic = 1;
};

instance spellfx_thunderball(cfx_base_proto)
{
	visname_s = "mfx_thunderball_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collideCREATEONCEcreatequad";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_thunderball_collide";
	emfxcolldyn_s = "spellfx_thunderspell_target";
	emfxcollstatalign_s = "COLLISIONNORMAL";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100100";
	userstring[2] = "mul";
	lightpresetname = "aura";
};

instance spellfx_thunderball_collide(cfx_base_proto)
{
	visname_s = "mfx_thunderball_collide1";
	visalpha = 1;
	emtrjoriginnode = "bip01";
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
};

instance spellfx_thunderball_collide_key_invest_1(c_particlefxemitkey)
{	visname_s = "mfx_thunderball_collide1";	sfxid = "mfx_thunderball_collide1";};

instance spellfx_thunderball_collide_key_invest_2(c_particlefxemitkey)
{	visname_s = "mfx_thunderball_collide2";	sfxid = "mfx_thunderball_collide2";};

instance spellfx_thunderball_collide_key_invest_3(c_particlefxemitkey)
{	visname_s = "mfx_thunderball_collide3";	sfxid = "mfx_thunderball_collide3";};

instance spellfx_thunderball_collide_key_invest_4(c_particlefxemitkey)
{	visname_s = "mfx_thunderball_collide4";	sfxid = "mfx_thunderball_collide4";};

instance spellfx_thunderball_invest_blast1(cfx_base_proto)
{
	visname_s = "mfx_thunderball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_thunderball_invest1";
	sfxisambient = 1;
	visalpha = 0.3;
};

instance spellfx_thunderball_invest_blast2(cfx_base_proto)
{
	visname_s = "mfx_thunderball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_thunderball_invest2";
	sfxisambient = 1;
	visalpha = 0.5;
};

instance spellfx_thunderball_invest_blast3(cfx_base_proto)
{
	visname_s = "mfx_thunderball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_thunderball_invest3";
	sfxisambient = 1;
	visalpha = 0.8;
};

instance spellfx_thunderball_invest_blast4(cfx_base_proto)
{
	visname_s = "mfx_thunderball_invest_blast";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_thunderball_invest4";
	sfxisambient = 1;
	visalpha = 1;
};

instance spellfx_thunderball_key_cast(c_particlefxemitkey)
{
	lightrange = 200;
	visname_s = "mfx_thunderball_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400.;
	sfxid = "mfx_thunderball_cast";
	sfxisambient = 1;
	emcheckcollision = 1;
};

instance spellfx_thunderball_key_collide(c_particlefxemitkey)
{
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 0.000001;
};

instance spellfx_thunderball_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_init";
	lightrange = 0.01;
};

instance spellfx_thunderball_key_invest_1(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_invest";
	emcreatefxid = "spellfx_thunderball_invest_blast1";
	lightrange = 50;
	sfxid = "mfx_thunderball_invest1";
	sfxisambient = 1;
};

instance spellfx_thunderball_key_invest_2(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_invest_l2";
	emcreatefxid = "spellfx_thunderball_invest_blast2";
	sfxid = "mfx_thunderball_invest2";
	sfxisambient = 1;
};

instance spellfx_thunderball_key_invest_3(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_invest_l3";
	emcreatefxid = "spellfx_thunderball_invest_blast3";
	sfxid = "mfx_thunderball_invest3";
	sfxisambient = 1;
};

instance spellfx_thunderball_key_invest_4(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_invest_l4";
	emcreatefxid = "spellfx_thunderball_invest_blast4";
	sfxid = "mfx_thunderball_invest4";
	sfxisambient = 1;
};

instance spellfx_thunderball_key_open(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_init";
	lightrange = 0.01;
};

instance spellfx_thunderbolt(cfx_base_proto)
{
	visname_s = "mfx_thunderebolt_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjtargetnode = "bip01fire";
	emtrjloopmode_s = "none";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "collidecreate";
	emactioncolldyn_s = "collideCREATEONCE";
	emfxcollstat_s = "spellfx_thunderbolt_collide";
	emfxcolldyn_s = "spellfx_thunderbolt_sendperception";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
};

instance spellfx_thunderbolt_collide(cfx_base_proto)
{
	visname_s = "mfx_thunderbolt_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "torch_enlight";
};

instance spellfx_thunderbolt_key_cast(c_particlefxemitkey)
{
	visname_s = "mfx_thunderbolt_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400.;
	sfxid = "mfx_thunderbolt_cast";
	emcheckcollision = 1;
};

instance spellfx_thunderbolt_key_collide(c_particlefxemitkey)
{
	pfx_flygravity_s = "00.00020";
	emtrjeasevel = 0.000001;
	emcheckcollision = 0;
};

instance spellfx_thunderbolt_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_thunderbolt_init";
	scaleduration = 0.5;
};

instance spellfx_thunderbolt_sendperception(cfx_base_proto)
{
	visname_s = "mfx_thunderbolt_collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "torch_enlight";
	sendassessmagic = 1;
};

instance spellfx_thunderspell_target(cfx_base_proto)
{
	visname_s = "mfx_thunderball_target";
	emtrjoriginnode = "Bip01 Head";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sendassessmagic = 1;
	sfxid = "mfx_lightning_target";
	emfxcreate_s = "spellfx_thunderspell_target_child1";
	emfxcreatedowntrj = 1;
};

instance spellfx_thunderspell_target_child1(cfx_base_proto)
{
	visname_s = "mfx_thunderball_target";
	emtrjoriginnode = "bip01rupperarm";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emfxcreate_s = "spellfx_thunderspell_target_child2";
	emfxcreatedowntrj = 1;
};

instance spellfx_torch_0 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_1 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH1";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_2 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH2";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_3 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH3";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_4 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH4";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_5 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH5";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_6 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH6";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_7 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH7";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_8 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH8";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_torch_9 (CFX_BASE_PROTO)
{
	 visname_s = "effect_invisible";
	 lightpresetname = "FIRE_TORCH9";
};

/* Made by Risepolak (Xardas17) */


instance spellfx_transform_glow(cfx_base_proto)
{
	visname_s = "mfx_transform_glow";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjdynupdatedelay = 0;
};

instance spellfx_transform_glow_sfx(cfx_base_proto)
{
	visname_s = "mfx_transform_glow";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjdynupdatedelay = 0;
	sfxid = "mfx_transform_invest";
	sfxisambient = 1;
};

instance spellfx_transform_key_open(c_particlefxemitkey)
{
	visname_s = "mfx_transform_init";
};

instance  spellfx_undead_skeletonlord (cfx_base_proto)
{    	visname_s  =  "undead_skeleton";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "aura";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_unsichtbarkeit (cfx_base_proto)
{    	visname_s  =  "mfx_unsichtbarkeit_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxcreate_s  =  "spellfx_unsichtbarkeit_active";
    	emfxcreatedowntrj  =  1;
};

instance  spellfx_unsichtbarkeit_active (cfx_base_proto)
{    	visname_s  =  "";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "follow target";
    	emtrjeasevel  =  0.0;
    	emtrjoriginnode  =  "bip01 head";
    	emtrjloopmode_s  =  "HALT";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.4;
    	emtrjtargetrange  =  1.2;
    	emtrjtargetelev  =  89.0;
};

instance  spellfx_unsichtbarkeit_active_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_unsichtbarkeit_origin";
    	lightrange  =  1000.0;
    	sfxid  =  "mfx_unsichtbarkeit_cast";
    	sfxisambient  =  1;
    	emtrjeasevel  =  1400.0;
};

instance  spellfx_unsichtbarkeit_active_key_init (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_unsichtbarkeit_active_key_open (c_particlefxemitkey)
{    	lightrange  =  0.01;
};

instance  spellfx_unsichtbarkeit_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_uriziel (cfx_base_proto)
{    	visname_s  =  "mfx_uriziel_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxinvestorigin_s  =  "spellfx_uriziel_origin";
    	lightpresetname  =  "aura";
};

instance  spellfx_uriziel_cast (cfx_base_proto)
{    	visname_s  =  "mfx_uriziel_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_teleport_cast";
    	sfxisambient  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_uriziel_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_uriziel_cast";
    	pfx_ppsisloopingchg  =  1;
    	lightrange  =  800.0;
};

instance  spellfx_uriziel_key_init (c_particlefxemitkey)
{    	lightrange  =  0.3;
};

instance  spellfx_uriziel_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_uriziel_key_open (c_particlefxemitkey)
{    	lightrange  =  0.3;
};

instance  spellfx_uriziel_origin (cfx_base_proto)
{    	visname_s  =  "mfx_uriziel_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_teleport_invest";
    	sfxisambient  =  1;
};

instance  spellfx_uriziel_ring (cfx_base_proto)
{    	visname_s  =  "mfx_teleport_ring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_vampirarrow (cfx_base_proto)
{    	visname_s  =  "vampir_arrow";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_vampirarrow_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_vampirarrow_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_vampirarrow_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_vampirbolt (cfx_base_proto)
{    	visname_s  =  "vampir_bolt";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
    	lightpresetname  =  "firesmall";
};

instance  spellfx_vampirbolt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_vampirbolt_key_invest_2 (c_particlefxemitkey)
{    	lightrange  =  150.0;
};

instance  spellfx_vampirbolt_key_invest_3 (c_particlefxemitkey)
{    	lightrange  =  200.0;
};

instance  spellfx_verjuengung (cfx_base_proto)
{    	visname_s  =  "mfx_verjuengung_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01";
    	emtrjnumkeys  =  5;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  15.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjloopmode_s  =  "none";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "aura";
};

instance  spellfx_verjuengung_key_cast (c_particlefxemitkey)
{    	emtrjmode_s  =  "target line";
    	emtrjeasevel  =  6000.0;
    	lightrange  =  100.0;
    	sfxisambient  =  1;
    	sfxid  =  "mfx_control_cast";
};

instance  spellfx_verjuengung_key_init (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_verjuengung_key_open (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
    	lightrange  =  0.01;
};

instance  spellfx_verjuengung_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_verjuengung_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_verjuengung_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_verjuengung_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_violetfirearmor (cfx_base_proto)
{    	visname_s  =  "violet_light_human";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  " = ";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "firesmall";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_violetfirearmor_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_violetfirebip_lefthand (cfx_base_proto)
{    	visname_s  =  "violet_light_humanbip";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "firesmall";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_violetfirebip_lefthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_violetfirebip_neck (cfx_base_proto)
{    	visname_s  =  "violet_light_humanbip";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 neck";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "firesmall";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_violetfirebip_neck_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_violetfirebip_righthand (cfx_base_proto)
{    	visname_s  =  "violet_light_humanbip";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  10.0;
    	emtrjnumkeys  =  10;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	lightpresetname  =  "firesmall";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_violetfirebip_righthand_key_cast (c_particlefxemitkey)
{    	lightrange  =  500.0;
};

instance  spellfx_wahnsinn (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_init";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_wahnsinn_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_sleep_cast";
};

instance  spellfx_wahnsinn_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_sleep_init";
};

instance  spellfx_wahnsinn_origin (cfx_base_proto)
{    	visname_s  =  "mfx_sleep_origin";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjdynupdatedelay  =  0.0;
};

instance  spellfx_wahnsinn_target (cfx_base_proto)
{    	lightpresetname  =  "aura";
    	visname_s  =  "mfx_sleep_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emtrjdynupdatedelay  =  0.0;
};

instance spellfx_wampiresrage(cfx_base_proto)
{
	visname_s = "mfx_wampiresrage_flash";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01";
	emfxcreate_s = "spellfx_wampiresrage_target_cloud";
	sfxid = "wampire";
	sfxisambient = 1;
};

instance spellfx_wampiresrage_collide(cfx_base_proto)
{
	visname_s = "wampire_weapon_init";
	visalpha = 1;
	emtrjoriginnode = "zs_righthand";
	emtrjmode_s = "FIXED";
	lightpresetname = "firesmall";
	sfxid = "wampire";
	sfxisambient = 1;
};

instance spellfx_wampiresrage_target_cloud(cfx_base_proto)
{
	visname_s = "mfx_wampiresrage_target";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjdynupdatedelay = 0.01;
};

instance  spellfx_waterfist_00 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_00_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_00";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_00";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_00";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_00_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_00_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_00_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_00_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_00_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_00_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_01 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_01_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_01";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_01";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_01";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_01_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_01_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_01_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_01_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_01_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_01_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_02 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_02_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_02";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_02";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_02";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_02_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_02_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_02_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_02_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_02_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_02_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_03 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_03_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_03";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_03";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_03";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_03_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_03_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_03_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_03_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_03_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_03_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_04 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_04_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_04";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_04";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_04";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_04_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_04_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_04_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_04_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_04_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_04_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_05 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_05_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_05";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_05";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_05";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_05_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_05_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_05_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_05_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_05_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_05_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_06 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_06_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_06";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_06";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_06";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_06_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_06_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_06_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_06_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_06_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_06_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_07 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_07_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_07";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_07";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_07";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_07_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_07_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_07_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_07_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_07_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_07_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_08 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_08_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_08";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_08";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_08";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_08_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_08_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_08_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_08_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_08_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_08_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_09 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetrange  =  50.0;
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  1;
    	emtrjangleelevvar  =  0.0;
    	emtrjangleheadvar  =  0.0;
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  100.0;
    	emtrjdynupdatedelay  =  20000.0;
    	emfxcreatedowntrj  =  1;
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_09_abyss (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_cast_09";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "target spline random";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  4;
    	emtrjnumkeysvar  =  2;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  10.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjeasevel  =  900.0;
    	emtrjdynupdatedelay  =  0.1;
    	emtrjdynupdatetargetonly  =  1;
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emactioncollstat_s  =  "collide create";
    	emfxcollstat_s  =  "spellfx_waterfist_collidefx_09";
    	emfxcolldyn_s  =  "spellfx_waterfist_collidedynfx_09";
    	emfxcolldynperc_s  =  "spellfx_waterfist_sendperception";
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
};

instance  spellfx_waterfist_09_abyss_key_cast (c_particlefxemitkey)
{    	emcheckcollision  =  1;
    	sfxid  =  "mfx_waterfist_cast";
};

instance  spellfx_waterfist_09_abyss_key_collide (c_particlefxemitkey)
{    	visname_s  =  "";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_waterfist_09_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterfist_09_abyss";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterfist_09_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_waterfist_init";
    	lightrange  =  0.001;
};

instance  spellfx_waterfist_09_key_open (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_waterfist_collidedynfx_00 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_01 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_02 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_03 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_04 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_05 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_06 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_06";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_07 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_07";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_08 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_08";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidedynfx_09 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_09";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_00 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_00";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_01 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_01";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_02 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_02";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_03 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_03";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_04 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_04";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_05 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_05";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_06 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_06";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_07 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_07";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_08 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_08";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_collidefx_09 (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_collide_09";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_waterfist_collide";
    	sfxisambient  =  1;
};

instance  spellfx_waterfist_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_waterfist_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_waterfist_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  1.5;
    	visalpha  =  1.0;
};

instance  spellfx_waterfist_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance  spellfx_waterrain (cfx_base_proto)
{    	visname_s  =  "mfx_waterrain_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxinvestorigin_s  =  "spellfx_waterrain_investglow";
};

instance  spellfx_waterrain_investglow (cfx_base_proto)
{    	visname_s  =  "mfx_waterrain_investglow";
    	emtrjoriginnode  =  "bip01";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "redambience";
    	sfxid  =  "mfx_waterrain_invest";
    	sfxisambient  =  1;
    	emfxcreate_s  =  "fx_earthquake";
};

instance  spellfx_waterrain_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_waterrain_rain";
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_waterrain_rain (cfx_base_proto)
{    	visname_s  =  "mfx_waterrain_rain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_icespell_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_icespell_sendperception";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emcheckcollision  =  1;
    	lightpresetname  =  "cataclysm";
    	sfxid  =  "mfx_waterrain_rain";
    	sfxisambient  =  1;
};

instance  spellfx_waterrain_sub (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
};

instance spellfx_watherrain(cfx_base_proto)
{
	visname_s = "mfx_thunderball_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_watherrain_investglow";
	sfxisambient = 1;
};

instance spellfx_watherrain_investglow(cfx_base_proto)
{
	visname_s = "mfx_watherrain_investglow";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "aura";
	sfxid = "ow_windheavy2";
	sfxisambient = 1;
	emfxcreate_s = "fx_earthquake";
};

instance spellfx_watherrain_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_watherrain_rain";
	pfx_ppsisloopingchg = 1;
	sfxid = "watherrain";
};

instance spellfx_watherrain_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_init";
};

instance spellfx_watherrain_key_invest_1(c_particlefxemitkey)
{
	visname_s = "mfx_thunderball_init";
	emcreatefxid = "spellfx_watherrain_lefthand";
};

instance spellfx_watherrain_lefthand(cfx_base_proto)
{
	visname_s = "mfx_watherrain_rain_hard";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "bip01lhand";
};

instance spellfx_watherrain_rain(cfx_base_proto)
{
	visname_s = "mfx_watherrain_rain";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "cataclysm";
	sfxid = "watherrain";
	sfxisambient = 1;
};

instance spellfx_watherrain_rain_hard(cfx_base_proto)
{
	visname_s = "mfx_watherrain_rain_hard";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "cataclysm";
	sfxid = "watherrain";
	sfxisambient = 1;
};

instance spellfx_watherrain_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
};

instance  spellfx_weakglimmer_green (cfx_base_proto)
{    	visname_s  =  "weak_glimmer_green";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_weakglimmer_orange (cfx_base_proto)
{    	visname_s  =  "weak_glimmer_orange";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_weakglimmer_violet (cfx_base_proto)
{    	visname_s  =  "weak_glimmer_violet";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_whirlwind_target_15seconds (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01";
    	visname_s  =  "mfx_whirlwind_target_15seconds";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_whirlwind_target";
    	sfxisambient  =  1;
};

instance  spellfx_windbolt (cfx_base_proto)
{    	visname_s  =  "mfx_windbolt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide create";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_windbolt_collide";
    	emfxcolldyn_s  =  "spellfx_windbolt_collidedynfx";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
};

instance  spellfx_windbolt_collide (cfx_base_proto)
{    	visname_s  =  "mfx_windbolt_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
};

instance  spellfx_windbolt_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_thunderbolt_collide";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "torch_enlight";
    	sendassessmagic  =  1;
};

instance  spellfx_windbolt_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windbolt_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_thunderbolt_cast";
    	emcheckcollision  =  1;
};

instance  spellfx_windbolt_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
    	emcheckcollision  =  0;
};

instance  spellfx_windbolt_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_windbolt_init";
    	scaleduration  =  0.5;
};

instance  spellfx_windferis2_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_manashootferis_wind_cast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_windferis_mesheffect";
};

instance  spellfx_windferis_arrow (cfx_base_proto)
{    	visname_s  =  "mfx_manashootferis_wind_trail";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emfxcreate_s  =  "spellfx_windferis2_arrow";
};

instance  spellfx_windferis_mesheffect (cfx_base_proto)
{    	visname_s  =  "magic_bow_feris_wind";
    	visalpha  =  1.0;
    	visalphablendfunc_s  =  "ADD";
    	emtrjmode_s  =  "FIXED";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  2000000.0;
    	emfxlifespan  =  -1.0;
    	emselfrotvel_s  =  "0 0 0";
    	secsperdamage  =  -1.0;
    	emadjustshptoorigin  =  1;
};

instance  spellfx_windfist_00 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_00_invest";
};

instance  spellfx_windfist_00_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_00";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_00_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_00";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_00_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_00";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_00_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_00_cast";
};

instance  spellfx_windfist_00_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_01 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_01_invest";
};

instance  spellfx_windfist_01_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_01_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_01";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_01_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_01";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_01_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_01_cast";
};

instance  spellfx_windfist_01_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_02 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_02_invest";
};

instance  spellfx_windfist_02_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_02_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_02";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_02_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_02";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_02_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_02_cast";
};

instance  spellfx_windfist_02_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_03 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_03_invest";
};

instance  spellfx_windfist_03_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_03_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_03";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_03_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_03";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_03_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_03_cast";
};

instance  spellfx_windfist_03_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_04 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_04_invest";
};

instance  spellfx_windfist_04_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_04";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_04_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_04";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_04_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_04";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_04_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_04_cast";
};

instance  spellfx_windfist_04_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_05 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_05_invest";
};

instance  spellfx_windfist_05_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_05";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_05_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_05";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_05_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_05";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_05_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_05_cast";
};

instance  spellfx_windfist_05_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_06 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_06_invest";
};

instance  spellfx_windfist_06_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_06";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_06_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_06";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_06_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_06";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_06_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_06_cast";
};

instance  spellfx_windfist_06_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_07 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_07_invest";
};

instance  spellfx_windfist_07_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_07";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_07_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_07";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_07_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_07";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_07_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_07_cast";
};

instance  spellfx_windfist_07_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_08 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_08_invest";
};

instance  spellfx_windfist_08_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_08";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_08_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_08";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_08_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_08";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_08_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_08_cast";
};

instance  spellfx_windfist_08_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_09 (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjnumkeys  =  7;
    	emtrjnumkeysvar  =  3;
    	emtrjangleelevvar  =  5.0;
    	emtrjangleheadvar  =  20.0;
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  200000.0;
    	emtrjtargetrange  =  100.0;
    	emtrjtargetelev  =  1.0;
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynalign_s  =  "COLLISIONNORMAL";
    	emfxcolldyn_s  =  "spellfx_windfist_collidedynfx";
    	emfxcolldynperc_s  =  "spellfx_windfist_sendperception";
    	emfxinvestorigin_s  =  "spellfx_windfist_09_invest";
};

instance  spellfx_windfist_09_cast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_cast_09";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_cast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_09_invest (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_09";
    	sfxid  =  "mfx_windfist_invest";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_09_investblast (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_09";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance  spellfx_windfist_09_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_windfist_collisiondummy";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  2500.0;
    	emcheckcollision  =  1;
    	emcreatefxid  =  "spellfx_windfist_09_cast";
};

instance  spellfx_windfist_09_key_init (c_particlefxemitkey)
{    	emcheckcollision  =  0;
};

instance  spellfx_windfist_investblast_small (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_invest_blast_small";
    	emtrjoriginnode  =  "zs_righthand";
    	sfxid  =  "mfx_windfist_invesblast";
    	sfxisambient  =  1;
};

instance spellfx_windfist_key_invest_1(c_particlefxemitkey)
{	emcreatefxid = "spellfx_windfist_investblast";};

instance spellfx_windfist_key_invest_2(c_particlefxemitkey)
{	emcreatefxid = "spellfx_windfist_investblast";};

instance spellfx_windfist_key_invest_3(c_particlefxemitkey)
{	emcreatefxid = "spellfx_windfist_investblast";};

instance spellfx_windfist_key_invest_4(c_particlefxemitkey)
{	emcreatefxid = "spellfx_windfist_investblast";};

instance  spellfx_windfist_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_lefthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  5.0;
    	visalpha  =  1.0;
};

instance  spellfx_windfist_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emfxlifespan  =  5.0;
    	visalpha  =  1.0;
};

instance  spellfx_windfist_sendperception (cfx_base_proto)
{    	visname_s  =  "";
    	sendassessmagic  =  1;
};

instance spellfx_windfist_target(cfx_base_proto)
{
	visname_s = "mfx_windfist_collide";
	sendassessmagic = 1;
};

instance  spellfx_woodgolemprojectile (cfx_base_proto)
{    	visname_s  =  "mfx_shrink_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "CREATEONCE";
    	emfxcolldynperc_s  =  "spellfx_woodgolemprojectile_sendperception";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvestorigin_s  =  "spellfx_woodgolemprojectile_invest";
};

instance  spellfx_woodgolemprojectile_invest (cfx_base_proto)
{    	visname_s  =  "mfx_poisonspit_invest";
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_woodgolemprojectile_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_shrink_init";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  800.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_suckenergy_cast";
};

instance  spellfx_woodgolemprojectile_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
    	pfx_ppsisloopingchg  =  1;
};

instance  spellfx_woodgolemprojectile_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_woodgolemprojectile_sendperception (cfx_base_proto)
{    	visname_s  =  "mfx_magicmissile_collide";
    	sendassessmagic  =  1;
    	sfxid  =  "mfx_thunderball_collide2";
};

instance  spellfx_wurzelstaff_collidedynfx (cfx_base_proto)
{    	visname_s  =  "mfx_windfist_target";
    	sfxid  =  "mfx_thunderball_collide2";
};

instance spellfx_xardas(cfx_base_proto)
{
	visname_s = "mfx_xardas_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_righthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_xardas_initglowc";
	emfxcreatedowntrj = 0;
	sfxid = "mfx_firerain_rain";
};

instance spellfx_xardas_ground(cfx_base_proto)
{
	visname_s = "mfx_xardas_cast";
	emtrjoriginnode = "bip01rfoot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_xardas_target";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "aura";
	sfxid = "mfx_xardas_cast";
	sfxisambient = 1;
};

instance spellfx_xardas_initglow(cfx_base_proto)
{
	visname_s = "mfx_xardas_init_glow";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	lightpresetname = "redambience";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_xardas_initglowb(cfx_base_proto)
{
	visname_s = "mfx_xardas_init_glowb";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	lightpresetname = "redambience";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_xardas_initglowc(cfx_base_proto)
{
	visname_s = "mfx_xardas_init_glowc";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
	lightpresetname = "redambience";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_xardas_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_xardas_ground";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_xardas_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_xardas_init";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_xardas_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
	sfxid = "mfx_firerain_rain";
};

instance spellfx_xardas_target(cfx_base_proto)
{
	visname_s = "mfx_xardas_init_glow";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_xardas_target";
	sendassessmagic = 1;
	sfxid = "mfx_firerain_rain";
};

instance  spellfx_zaehmen (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 fire";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide CREATEONCE createquad";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcollstat_s  =  "spellfx_zaehmen_collide";
    	emfxcolldyn_s  =  "spellfx_zaehmen_collide";
    	emfxcolldynperc_s  =  "spellfx_thunderspell_sendperception";
    	emfxcollstatalign_s  =  "COLLISIONNORMAL";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	emtrjdynupdatedelay  =  20000.0;
    	userstring  =  "fireballquadmark.tga";
    	userstring[1]  =  "100 100";
    	userstring[2]  =  "mul";
    	lightpresetname  =  "aura";
};

instance  spellfx_zaehmen_collide (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emtrjoriginnode  =  "bip01";
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
};

instance  spellfx_zaehmen_collide_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide1";
    	sfxid  =  "mfx_thunderball_collide1";
};

instance  spellfx_zaehmen_collide_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide2";
    	sfxid  =  "mfx_thunderball_collide2";
};

instance  spellfx_zaehmen_collide_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide3";
    	sfxid  =  "mfx_thunderball_collide3";
};

instance  spellfx_zaehmen_collide_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_collide4";
    	sfxid  =  "mfx_thunderball_collide4";
};

instance  spellfx_zaehmen_invest_blast1 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest1";
    	sfxisambient  =  1;
    	visalpha  =  0.3;
};

instance  spellfx_zaehmen_invest_blast2 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest2";
    	sfxisambient  =  1;
    	visalpha  =  0.5;
};

instance  spellfx_zaehmen_invest_blast3 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest3";
    	sfxisambient  =  1;
    	visalpha  =  0.8;
};

instance  spellfx_zaehmen_invest_blast4 (cfx_base_proto)
{    	visname_s  =  "mfx_thunderball_invest_blast";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	sfxid  =  "mfx_thunderball_invest4";
    	sfxisambient  =  1;
    	visalpha  =  1.0;
};

instance  spellfx_zaehmen_key_cast (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	visname_s  =  "mfx_thunderball_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1400.0;
    	sfxid  =  "mfx_thunderball_cast";
    	sfxisambient  =  1;
    	emcheckcollision  =  1;
};

instance  spellfx_zaehmen_key_collide (c_particlefxemitkey)
{    	pfx_flygravity_s  =  "0 0.0002 0";
    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_zaehmen_key_init (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_init";
    	lightrange  =  0.01;
};

instance  spellfx_zaehmen_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest";
    	emcreatefxid  =  "spellfx_zaehmen_invest_blast1";
    	lightrange  =  50.0;
    	sfxid  =  "mfx_thunderball_invest1";
    	sfxisambient  =  1;
};

instance  spellfx_zaehmen_key_invest_2 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest_l2";
    	emcreatefxid  =  "spellfx_zaehmen_invest_blast2";
    	sfxid  =  "mfx_thunderball_invest2";
    	sfxisambient  =  1;
};

instance  spellfx_zaehmen_key_invest_3 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest_l3";
    	emcreatefxid  =  "spellfx_zaehmen_invest_blast3";
    	sfxid  =  "mfx_thunderball_invest3";
    	sfxisambient  =  1;
};

instance  spellfx_zaehmen_key_invest_4 (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_invest_l4";
    	emcreatefxid  =  "spellfx_zaehmen_invest_blast4";
    	sfxid  =  "mfx_thunderball_invest4";
    	sfxisambient  =  1;
};

instance  spellfx_zaehmen_key_open (c_particlefxemitkey)
{    	visname_s  =  "mfx_thunderball_init";
    	lightrange  =  0.01;
};

instance  spellfx_zeitspalt (cfx_base_proto)
{    	visname_s  =  "mfx_zeitspalt_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxinvestorigin_s  =  "spellfx_zeitspalt_origin";
    	lightpresetname  =  "aura";
};

instance  spellfx_zeitspalt_cast (cfx_base_proto)
{    	visname_s  =  "mfx_zeitspalt_cast";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_teleport_cast";
    	sfxisambient  =  1;
    	emtrjmode_s  =  "FIXED";
};

instance  spellfx_zeitspalt_key_cast (c_particlefxemitkey)
{    	emcreatefxid  =  "spellfx_zeitspalt_cast";
    	pfx_ppsisloopingchg  =  1;
    	lightrange  =  200.0;
};

instance  spellfx_zeitspalt_key_init (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_zeitspalt_key_invest_1 (c_particlefxemitkey)
{    	lightrange  =  100.0;
};

instance  spellfx_zeitspalt_key_open (c_particlefxemitkey)
{    	lightrange  =  0.1;
};

instance  spellfx_zeitspalt_lefthand (cfx_base_proto)
{    	visname_s  =  "mfx_zeitspalt_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 l hand";
    	emfxlifespan  =  4.0;
};

instance  spellfx_zeitspalt_origin (cfx_base_proto)
{    	visname_s  =  "mfx_zeitspalt_invest";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	emfxcreate_s  =  "spellfx_zeitspalt_ring";
    	sfxid  =  "mfx_teleport_invest";
    	sfxisambient  =  1;
};

instance  spellfx_zeitspalt_righthand (cfx_base_proto)
{    	visname_s  =  "mfx_zeitspalt_init";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emfxlifespan  =  4.0;
};

instance  spellfx_zeitspalt_ring (cfx_base_proto)
{    	visname_s  =  "mfx_zeitspalt_ring";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
};

instance  spellfx_zerfleischen (cfx_base_proto)
{    	visname_s  =  "mfx_zerfleischen_init";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emactioncollstat_s  =  "collide";
    	emactioncolldyn_s  =  "collide CREATEONCE";
    	emfxcolldyn_s  =  "spellfx_zerfleischen_fountain";
    	emtrjtargetrange  =  20.0;
    	emtrjtargetelev  =  0.0;
    	lightpresetname  =  "redambience";
};

instance  spellfx_zerfleischen_fountain (cfx_base_proto)
{    	visname_s  =  "mfx_zerfleischen_fountain";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_zerfleischen_fountain";
    	sfxisambient  =  1;
};

instance  spellfx_zerfleischen_key_cast (c_particlefxemitkey)
{    	visname_s  =  "mfx_zerfleischen_cast";
    	emtrjmode_s  =  "TARGET";
    	emtrjeasevel  =  1000.0;
    	lightrange  =  100.0;
    	emcheckcollision  =  1;
    	sfxid  =  "mfx_zerfleischen_rumble";
    	sfxisambient  =  1;
};

instance  spellfx_zerfleischen_key_collide (c_particlefxemitkey)
{    	emtrjeasevel  =  1.0e-6;
};

instance  spellfx_zerfleischen_key_init (c_particlefxemitkey)
{    	lightrange  =  0.001;
};

instance  spellfx_zerfleischen_key_invest (c_particlefxemitkey)
{    	lightrange  =  100.0;
    	emcreatefxid  =  "spellfx_zerfleischen_rumble";
};

instance  spellfx_zerfleischen_rumble (cfx_base_proto)
{    	visname_s  =  "";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01";
    	sfxid  =  "mfx_zerfleischen_rumble";
    	sfxisambient  =  1;
};

instance  spellfx_ziegezaehmen (cfx_base_proto)
{    	visname_s  =  "mfx_control_init";
    	vissize_s  =  "1 1";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "zs_righthand";
    	emtrjtargetnode  =  "bip01 head";
    	emtrjloopmode_s  =  "none";
    	emtrjeasefunc_s  =  "LINEAR";
    	emtrjdynupdatedelay  =  0.0;
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	emfxinvesttarget_s  =  "spellfx_ziegezaehmen_target";
    	emfxinvestorigin_s  =  "spellfx_ziegezaehmen_bridge";
};

instance  spellfx_ziegezaehmen_bridge (cfx_base_proto)
{    	visname_s  =  "mfx_control_bridge";
    	emtrjmode_s  =  "target line";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetnode  =  "bip01 head";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	emfxcreate_s  =  "spellfx_ziegezaehmen_origin";
    	sfxid  =  "mfx_control_invest";
    	sfxisambient  =  1;
};

instance  spellfx_ziegezaehmen_bridge_key_init (c_particlefxemitkey)
{    	emtrjeasevel  =  0.01;
};

instance  spellfx_ziegezaehmen_key_cast (c_particlefxemitkey)
{    	pfx_ppsisloopingchg  =  1;
    	emcreatefxid  =  "control_castblend";
    	sfxid  =  "mfx_control_cast";
    	sfxisambient  =  1;
};

instance  spellfx_ziegezaehmen_key_invest_1 (c_particlefxemitkey)
{    	visname_s  =  "simpleglow.tga";
    	sfxid  =  "mfx_control_startinvest";
    	sfxisambient  =  1;
};

instance  spellfx_ziegezaehmen_target (cfx_base_proto)
{    	visname_s  =  "mfx_control_target";
    	emtrjmode_s  =  "FIXED";
    	emtrjoriginnode  =  "bip01 head";
    	emtrjtargetrange  =  0.0;
    	emtrjtargetelev  =  0.0;
    	sendassessmagic  =  1;
};

instance spellfx_ziemia(cfx_base_proto)
{
	visname_s = "mfx_ziemia_init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "zs_lefthand";
	emtrjloopmode_s = "none";
	emfxinvestorigin_s = "spellfx_ziemia_initglow";
	emfxcreatedowntrj = 0;
};

instance spellfx_ziemia_ground(cfx_base_proto)
{
	visname_s = "mfx_ziemia_cast";
	emtrjoriginnode = "bip01rfoot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellfx_ziemia_target";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	sfxisambient = 1;
};

instance spellfx_ziemia_initglow(cfx_base_proto)
{
	visname_s = "mfx_ziemia_init_glow";
	emtrjoriginnode = "zs_righthand";
	emfxcreatedowntrj = 0;
	emtrjmode_s = "FIXED";
};

instance spellfx_ziemia_key_cast(c_particlefxemitkey)
{
	emcreatefxid = "spellfx_ziemia_ground";
	pfx_ppsisloopingchg = 1;
};

instance spellfx_ziemia_key_init(c_particlefxemitkey)
{
	visname_s = "mfx_ziemia_init";
};

instance spellfx_ziemia_sub(cfx_base_proto)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 Head";
};

instance spellfx_ziemia_target(cfx_base_proto)
{
	visname_s = "mfx_ziemia_target";
	emtrjoriginnode = "bip01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	sfxid = "mfx_ziemia_target";
	sendassessmagic = 1;
};

instance s_heashoot(cfx_base_proto)
{
	emtrjoriginnode = "bip01toe";
	visname_s = "mfx_lightning_target";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
};

instance s_heashoot_amb(cfx_base_proto)
{
	emtrjoriginnode = "bip01toe";
	visname_s = "mfx_donnerwort_fx";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
	sfxisambient = 1;
	emfxlifespan = 2;
};

instance  timelapse_blend (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "100000000000";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "0.5";
    	visalphablendfunc_s  =  "BLEND";
};

instance  tremble (cfx_base_proto)
{    	visname_s  =  "earthquake.eqk";
    	userstring  =  "1000";
    	userstring[1]  =  "5";
    	userstring[2]  =  "2 7 2";
};

instance  velen_screenblend (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  10.0;
};

instance  velen_screenblend_02 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "10";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "3";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  10.0;
};

instance  velen_screenblend_03 (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	userstring  =  "15";
    	userstring[1]  =  "0 0 0 255";
    	userstring[2]  =  "3";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  15.0;
};

instance  vfx_blackcloud_permanent_humanoid (cfx_base_proto)
{    	visname_s  =  "fire_swordblack";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  vfx_blackcloud_permanent_skeletonmage (cfx_base_proto)
{    	visname_s  =  "fire_swordblack";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  vfx_cs_fokus2 (cfx_base_proto)
{    	visname_s  =  "cs_fokus2";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  vfx_summoner_orc_selected_soul_humanoid (cfx_base_proto)
{    	visname_s  =  "mfx_summoner_orc_weapon";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance  vfx_summoner_orc_selected_soul_skeletonmage (cfx_base_proto)
{    	visname_s  =  "mfx_summoner_orc_weapon";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	emadjustshptoorigin  =  1;
};

instance vfx_weihe_1(cfx_base_proto)
{
	visname_s = "mfx_weihe_erde";
	emfxlifespan = 2;
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjeasevel = 0.001;
	emtrjoriginnode = "bip01";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
	emfxcreatedowntrj = 1;
};

instance vfx_weihe_beliar(cfx_base_proto)
{
	visname_s = "mfx_weihe_beliar";
	emtrjmode_s = "targetline";
	emtrjeasevel = 0.001;
	emtrjoriginnode = "bip01rhand";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
	emfxlifespan = 2;
};

instance vfx_weihe_erde(cfx_base_proto)
{
	visname_s = "mfx_weihe_erde";
	emfxlifespan = 2;
	emtrjmode_s = "targetline";
	emtrjeasevel = 0.001;
	emtrjoriginnode = "bip01rhand";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
};

instance vfx_weihe_feuer(cfx_base_proto)
{
	visname_s = "mfx_weihe_feuer";
	emfxlifespan = 2;
	emtrjmode_s = "targetline";
	emtrjeasevel = 0.001;
	emtrjoriginnode = "bip01rhand";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
};

instance vfx_weihe_water(cfx_base_proto)
{
	visname_s = "mfx_weihe_water";
	emfxlifespan = 2;
	emtrjmode_s = "targetline";
	emtrjeasevel = 0.001;
	emtrjoriginnode = "bip01rhand";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
};

instance vfx_weihe_wind(cfx_base_proto)
{
	visname_s = "mfx_weihe_wind";
	emfxlifespan = 2;
	emtrjmode_s = "targetline";
	emtrjeasevel = 0.001;
	emtrjoriginnode = "bip01rhand";
	emtrjdynupdatedelay = 0;
	lightpresetname = "aura";
};

instance  vob_1h_innosfiresword_01 (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "mfx_1h_innosfiresword_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "fsb_fire_a1";
};

instance  vob_1h_innosfiresword_02 (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "mfx_1h_innosfiresword_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_1h_innosfiresword_03 (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "mfx_1h_innosfiresword_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
};

instance  vob_1h_oresword (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "ore_sword";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_2h_innosfiresword_01 (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "mfx_2h_innosfiresword_01";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "fsb_fire_a1";
};

instance  vob_2h_innosfiresword_02 (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "mfx_2h_innosfiresword_02";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_2h_innosfiresword_03 (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "mfx_2h_innosfiresword_03";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
};

instance  vob_2h_oresword (cfx_base_proto)
{    	emtrjoriginnode  =  "zs_righthand";
    	visname_s  =  "ore_2hsword";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance vob_acid(cfx_base_proto)
{
	emtrjoriginnode = "bip01fire";
	visname_s = "mfx_acid_target";
	emfxcreate_s = "vob_acid_child1";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emadjustshptoorigin = 1;
	secsperdamage = 0.5;
	emfxlifespan = 8;
};

instance vob_acid_child1(cfx_base_proto)
{
	emtrjoriginnode = "bip01rupperarm";
	visname_s = "mfx_acid_target";
	emfxcreate_s = "vob_acid_child2";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emadjustshptoorigin = 1;
	sfxid = "mfx_acid_dot";
};

instance vob_acid_child2(cfx_base_proto)
{
	emtrjoriginnode = "bip01lupperarm";
	visname_s = "mfx_acid_target";
	emfxcreate_s = "vob_acid_child3";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emadjustshptoorigin = 1;
};

instance vob_acid_child3(cfx_base_proto)
{
	emtrjoriginnode = "bip01lhand";
	visname_s = "mfx_acid_target";
	emfxcreate_s = "vob_acid_child4";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emadjustshptoorigin = 1;
};

instance vob_acid_child4(cfx_base_proto)
{
	emtrjoriginnode = "bip01rhand";
	visname_s = "mfx_acid_target";
	emfxcreate_s = "vob_acid_child5";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emadjustshptoorigin = 1;
	emfxtriggerdelay = 0.5;
};

instance vob_acid_child5(cfx_base_proto)
{
	emtrjoriginnode = "bip01lfoot";
	visname_s = "mfx_acid_target";
	emfxcreate_s = "vob_acid_child6";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emadjustshptoorigin = 1;
	emfxtriggerdelay = 0.5;
};

instance vob_acid_child6(cfx_base_proto)
{
	emtrjoriginnode = "bip01rfoot";
	visname_s = "mfx_acid_target";
	emfxcreate_s = "spellfx_firespell_humansmoke";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emadjustshptoorigin = 1;
	emfxtriggerdelay = 0.8;
};

instance  vob_bluemagicburn (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humanburnblue";
    	emfxcreate_s  =  "vob_bluemagicburn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_firespell_humanburn";
    	lightpresetname  =  "aura";
};

instance  vob_bluemagicburn_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicfire_humanburnblue";
    	emfxcreate_s  =  "vob_bluemagicburn_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_bluemagicburn_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicfire_humanburnblue";
    	emfxcreate_s  =  "vob_bluemagicburn_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_bluemagicburn_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicfire_humanburnblue";
    	emfxcreate_s  =  "vob_bluemagicburn_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_bluemagicburn_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicfire_humanburnblue";
    	emfxcreate_s  =  "vob_bluemagicburn_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_bluemagicburn_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicfire_humanburnblue";
    	emfxcreate_s  =  "vob_bluemagicburn_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_bluemagicburn_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicfire_humanburnblue";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_burn_permanent_humanoid (cfx_base_proto)
{    	visname_s  =  "fire_sword";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  vob_burn_permanent_imp (cfx_base_proto)
{    	visname_s  =  "fire_sword";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  vob_burn_permanent_waran (cfx_base_proto)
{    	visname_s  =  "fire_sword";
    	visalpha  =  1.0;
    	emtrjmode_s  =  "FIXED";
    	lightpresetname  =  "firesmall";
    	emadjustshptoorigin  =  1;
};

instance  vob_electricburn (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricburn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_beliarweap";
    	sfxisambient  =  1;
};

instance  vob_electricburn_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricburn_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricburn_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricburn_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricburn_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricburn_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricburn_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricburn_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricburn_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricburn_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricburn_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_thunderball_collide1";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricburn_child7";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	sendassessmagic  =  1;
};

instance  vob_electricburn_child7 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humansmoke";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_electricshock (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_electricshock_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricshock_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_beliarweap";
    	sfxisambient  =  1;
};

instance  vob_electricshock_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_electricshock_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricshock_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricshock_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_electricshock_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricshock_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricshock_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_electricshock_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricshock_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricshock_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_electricshock_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricshock_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricshock_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_electricshock_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricshock_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_electricshock_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_electricshock_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_electricshock_child7";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	sendassessmagic  =  1;
};

instance  vob_electricshock_child7 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_fireburn (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_fire_humanburn_short";
    	emfxcreate_s  =  "vob_fireburn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_fireburn_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_fire_humanburn_short";
    	emfxcreate_s  =  "vob_fireburn_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_fireburn_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_fire_humanburn_short";
    	emfxcreate_s  =  "vob_fireburn_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_fireburn_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_fire_humanburn_short";
    	emfxcreate_s  =  "vob_fireburn_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_fireburn_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_fire_humanburn_short";
    	emfxcreate_s  =  "vob_fireburn_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_fireburn_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_fire_humanburn_short";
    	emfxcreate_s  =  "vob_fireburn_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_fireburn_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_fire_humanburn_short";
    	emfxcreate_s  =  "spellfx_magicfire_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_freezeshock (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock_child1";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_icecube_collide";
    	sfxisambient  =  1;
};

instance  vob_freezeshock2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock2_child1";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_icecube_collide";
    	sfxisambient  =  1;
};

instance  vob_freezeshock2_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock2_child2";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock2_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock2_child3";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock2_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock2_child4";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock2_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock2_child5";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock2_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock2_child6";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock2_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock2_child7";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	sendassessmagic  =  1;
};

instance  vob_freezeshock2_child7 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_icespell_collide";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_freezeshock_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock_child2";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock_child3";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock_child4";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock_child5";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock_child6";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_freezeshock_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_icespell_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_freezeshock_child7";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	sendassessmagic  =  1;
};

instance  vob_freezeshock_child7 (cfx_base_proto)
{};

instance  vob_greenmagicburn (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humanburngreen";
    	emfxcreate_s  =  "vob_greenmagicburn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "blueambient";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_greenmagicburn_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicfire_humanburngreen";
    	emfxcreate_s  =  "vob_greenmagicburn_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_greenmagicburn_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicfire_humanburngreen";
    	emfxcreate_s  =  "vob_greenmagicburn_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_greenmagicburn_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicfire_humanburngreen";
    	emfxcreate_s  =  "vob_greenmagicburn_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_greenmagicburn_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicfire_humanburngreen";
    	emfxcreate_s  =  "vob_greenmagicburn_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_greenmagicburn_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicfire_humanburngreen";
    	emfxcreate_s  =  "vob_greenmagicburn_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_greenmagicburn_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicfire_humanburngreen";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_iceshock (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_icebolt_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_iceshock_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "torch_enlight";
    	sfxisambient  =  1;
};

instance  vob_iceshock_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_icebolt_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_iceshock_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_iceshock_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_icebolt_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_iceshock_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_iceshock_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_icebolt_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_iceshock_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_iceshock_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_icebolt_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_iceshock_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_iceshock_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_icebolt_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_iceshock_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
};

instance  vob_iceshock_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_icebolt_collide";
    	visalpha  =  1.0;
    	emfxcreate_s  =  "vob_iceshock_child7";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxisambient  =  1;
    	sendassessmagic  =  1;
};

instance  vob_iceshock_child7 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_magicburn_flame (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humanburn_flame";
    	emfxcreate_s  =  "vob_magicburn_flame_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "ice";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_magicburn_flame_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicfire_humanburn_flame";
    	emfxcreate_s  =  "vob_magicburn_flame_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_flame_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicfire_humanburn_flame";
    	emfxcreate_s  =  "vob_magicburn_flame_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_flame_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicfire_humanburn_flame";
    	emfxcreate_s  =  "vob_magicburn_flame_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_flame_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicfire_humanburn_flame";
    	emfxcreate_s  =  "vob_magicburn_flame_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_flame_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicfire_humanburn_flame";
    	emfxcreate_s  =  "vob_magicburn_flame_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_flame_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicfire_humanburn_flame";
    	emfxcreate_s  =  "spellfx_magicfire_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_magicburn_ice (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humanburn_ice";
    	emfxcreate_s  =  "vob_magicburn_ice_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "ice";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_magicburn_ice_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicfire_humanburn_ice";
    	emfxcreate_s  =  "vob_magicburn_ice_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_ice_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicfire_humanburn_ice";
    	emfxcreate_s  =  "vob_magicburn_ice_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_ice_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicfire_humanburn_ice";
    	emfxcreate_s  =  "vob_magicburn_ice_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_ice_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicfire_humanburn_ice";
    	emfxcreate_s  =  "vob_magicburn_ice_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_ice_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicfire_humanburn_ice";
    	emfxcreate_s  =  "vob_magicburn_ice_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_ice_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicfire_humanburn_ice";
    	emfxcreate_s  =  "spellfx_magicfire_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_magicburn_nosmoke (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreate_s  =  "vob_magicburn_nosmoke_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_magicburn_nosmoke_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreate_s  =  "vob_magicburn_nosmoke_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_nosmoke_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreate_s  =  "vob_magicburn_nosmoke_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_nosmoke_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreate_s  =  "vob_magicburn_nosmoke_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_nosmoke_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreate_s  =  "vob_magicburn_nosmoke_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_nosmoke_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreate_s  =  "vob_magicburn_nosmoke_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_nosmoke_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_magicburn_shadoworc (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_feuerpfanne";
    	emfxcreate_s  =  "vob_magicburn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_magicburn_small_nosound_nolight (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicburn_withearthquake (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicfire_humanburn";
    	emfxcreate_s  =  "vob_magicburn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
    	emfxcreate_s  =  "fx_earthquake";
};

instance  vob_magicflame (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicflame_humanburn";
    	emfxcreate_s  =  "vob_magicflame_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_magicflame_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicflame_humanburn";
    	emfxcreate_s  =  "vob_magicflame_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicflame_humanburn";
    	emfxcreate_s  =  "vob_magicflame_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicflame_humanburn";
    	emfxcreate_s  =  "vob_magicflame_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicflame_humanburn";
    	emfxcreate_s  =  "vob_magicflame_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicflame_humanburn";
    	emfxcreate_s  =  "vob_magicflame_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicflame_humanburn";
    	emfxcreate_s  =  "spellfx_magicfire_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_magicflame_short (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicflame_humanburn_short";
    	emfxcreate_s  =  "vob_magicflame_short_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "firesmall";
    	sfxid  =  "mfx_firespell_humanburn";
};

instance  vob_magicflame_short_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicflame_humanburn_short";
    	emfxcreate_s  =  "vob_magicflame_short_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_short_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicflame_humanburn_short";
    	emfxcreate_s  =  "vob_magicflame_short_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_short_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicflame_humanburn_short";
    	emfxcreate_s  =  "vob_magicflame_short_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_short_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicflame_humanburn_short";
    	emfxcreate_s  =  "vob_magicflame_short_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_short_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicflame_humanburn_short";
    	emfxcreate_s  =  "vob_magicflame_short_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicflame_short_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicflame_humanburn_short";
    	emfxcreate_s  =  "spellfx_magicfire_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_magicice (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_magicice_humanburn";
    	emfxcreate_s  =  "vob_magicice_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	lightpresetname  =  "aura";
    	sfxid  =  "mfx_icespell_humanburn";
};

instance  vob_magicice_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_magicice_humanburn";
    	emfxcreate_s  =  "vob_magicice_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicice_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_magicice_humanburn";
    	emfxcreate_s  =  "vob_magicice_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicice_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_magicice_humanburn";
    	emfxcreate_s  =  "vob_magicice_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicice_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_magicice_humanburn";
    	emfxcreate_s  =  "vob_magicice_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicice_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_magicice_humanburn";
    	emfxcreate_s  =  "vob_magicice_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
};

instance  vob_magicice_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_magicice_humanburn";
    	emfxcreate_s  =  "spellfx_magicice_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sendassessmagic  =  1;
};

instance  vob_shadoworcburn (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 fire";
    	visname_s  =  "mfx_firespell_shadoworcburn";
    	emfxcreate_s  =  "vob_shadoworcburn_child1";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	sfxid  =  "mfx_firespell_shadoworcburn";
    	emadjustshptoorigin  =  1;
};

instance  vob_shadoworcburn_child1 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r upperarm";
    	visname_s  =  "mfx_firespell_shadoworcburn";
    	emfxcreate_s  =  "vob_shadoworcburn_child2";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_shadoworcburn_child2 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l upperarm";
    	visname_s  =  "mfx_firespell_shadoworcburn";
    	emfxcreate_s  =  "vob_shadoworcburn_child3";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_shadoworcburn_child3 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l hand";
    	visname_s  =  "mfx_firespell_shadoworcburn";
    	emfxcreate_s  =  "vob_shadoworcburn_child4";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_shadoworcburn_child4 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r hand";
    	visname_s  =  "mfx_firespell_shadoworcburn";
    	emfxcreate_s  =  "vob_shadoworcburn_child5";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_shadoworcburn_child5 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 l foot";
    	visname_s  =  "mfx_firespell_shadoworcburn";
    	emfxcreate_s  =  "vob_shadoworcburn_child6";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  vob_shadoworcburn_child6 (cfx_base_proto)
{    	emtrjoriginnode  =  "bip01 r foot";
    	visname_s  =  "mfx_firespell_shadoworcburn";
    	emfxcreate_s  =  "spellfx_firespell_humansmoke";
    	emfxcreatedowntrj  =  1;
    	emtrjmode_s  =  "FIXED";
    	emtrjdynupdatedelay  =  0.0;
    	emadjustshptoorigin  =  1;
};

instance  white_screen (cfx_base_proto)
{    	visname_s  =  "screenblend.scx";
    	visalpha  =  1.0;
    	userstring  =  "100000000000";
    	userstring[1]  =  "128 128 128 255";
    	userstring[2]  =  "0.08";
    	visalphablendfunc_s  =  "BLEND";
    	emfxlifespan  =  0.25;
    	sfxid  =  "mfx_barriere_shoot";
    	sfxisambient  =  1;
};

