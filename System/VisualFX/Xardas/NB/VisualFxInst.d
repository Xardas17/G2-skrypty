//emtrjoriginnode = "Bip01 L Hand";
instance spellfx_incovation_fire(cfx_base_proto) {

    visname_s = "INVOCATION_FIRE";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    lightpresetname = "FIRESMALL";

    sfxid = "FSB_FIRE";

    sfxisambient = 1;

};
instance spellfx_lightstar_white_wisp(cfx_base_proto) {

    visname_s = "LIGHTSTAR_WHITE_WISP";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

};
instance spellfx_palelite(cfx_base_proto) {

    visname_s = "MFX_Innoseye";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emfxcreate_s = "spellFX_PALELITE_Light";

    emfxcreatedowntrj = 1;

};
instance spellfx_palelite_light(cfx_base_proto) {

    visname_s = "";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    emtrjeasevel = 0.0;

    emtrjoriginnode = "BIP01 Head";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.4;

    emtrjtargetrange = 5.0;

    emtrjtargetelev = 89.0;

    lightpresetname = "FIRESMALL";

    sfxid = "MFX_FIrestorm_Collide";

    sfxisambient = 1;

};

instance spellfx_beliarshrine(cfx_base_proto) {

    visname_s = "MFX_BELIARSHRINE";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "WHITEBLEND";

};

instance spellfx_dragonflameball(cfx_base_proto) {

    visname_s = "MFX_CHARGEFB_CAST_L5";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_DRAGONFLAMEBALL_COLLIDE";

    emfxcolldyn_s = "spellFX_DRAGONFLAMEBALL_COLLIDEDYNFX";

    emfxcolldynperc_s = "vob_magicburn";

    emfxcollstatalign_s = "COLLISIONNORMAL";

    emfxcreatedowntrj = 0;

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 30.0;

    lightpresetname = "FIRESMALL";

};



instance spellfx_dragonflameball_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_dragonflameball_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_dragonflameball_key_invest_1(c_particlefxemitkey) {

    emcreatefxid = "spellFX_DRAGONFLAMEBALL_InVEST_BLAST1";

    visname_s = "MFX_ChargeFB_CAST_L2";

    lightrange = 150.0;

    sfxid = "MFX_Fireball_invest1";

    sfxisambient = 1;

};



instance spellfx_dragonflameball_key_invest_2(c_particlefxemitkey) {

    emcreatefxid = "spellFX_DRAGONFLAMEBALL_InVEST_BLAST2";

    visname_s = "MFX_ChargeFB_CAST_L3";

    sfxid = "MFX_Fireball_invest2";

    sfxisambient = 1;

};



instance spellfx_dragonflameball_key_invest_3(c_particlefxemitkey) {

    emcreatefxid = "spellFX_DRAGONFLAMEBALL_InVEST_BLAST3";

    visname_s = "MFX_ChargeFB_CAST_L4";

    sfxid = "MFX_Fireball_invest3";

    sfxisambient = 1;

};



instance spellfx_dragonflameball_key_invest_4(c_particlefxemitkey) {

    emcreatefxid = "spellFX_DRAGONFLAMEBALL_InVEST_BLAST4";

    visname_s = "MFX_ChargeFB_CAST_L5";

    sfxid = "MFX_Fireball_invest4";

    sfxisambient = 1;

};



instance spellfx_dragonflameball_key_cast(c_particlefxemitkey) {

    lightrange = 100.0;

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "MFX_Fireball_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_dragonflameball_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_dragonflameball_invest_blast1(cfx_base_proto) {

    visname_s = "MFX_ChargeFB_INVESTBLAST";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Fireball_invest1";

    sfxisambient = 1;

    visalpha = 0.3;

};



instance spellfx_dragonflameball_invest_blast2(cfx_base_proto) {

    visname_s = "MFX_ChargeFB_INVESTBLAST";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Fireball_invest2";

    sfxisambient = 1;

    visalpha = 0.5;

};



instance spellfx_dragonflameball_invest_blast3(cfx_base_proto) {

    visname_s = "MFX_ChargeFB_INVESTBLAST";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Fireball_invest3";

    sfxisambient = 1;

    visalpha = 0.8;

};



instance spellfx_dragonflameball_invest_blast4(cfx_base_proto) {

    visname_s = "MFX_ChargeFB_INVESTBLAST";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Fireball_invest4";

    sfxisambient = 1;

    visalpha = 1.0;

};



instance spellfx_dragonflameball_collide(cfx_base_proto) {

    visname_s = "MFX_ChargeFB_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    lightpresetname = "FIRESMALL";

};



instance spellfx_dragonflameball_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_Fireball_Collide1";

    visalpha = 1.0;

    emtrjoriginnode = "BIP01";

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_dragonflameball_collidedynfx_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide1";

    sfxid = "MFX_Fireball_Collide1";

};



instance spellfx_dragonflameball_collidedynfx_key_invest_2(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide2";

    sfxid = "MFX_Fireball_Collide2";

};



instance spellfx_dragonflameball_collidedynfx_key_invest_3(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide3";

    sfxid = "MFX_Fireball_Collide3";

};



instance spellfx_dragonflameball_collidedynfx_key_invest_4(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide4";

    sfxid = "MFX_Fireball_Collide4";

};
instance spellfx_undead_screenblend(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "10";

    userstring[1] = "2 48 16 100";

    userstring[2] = "3";

    visalphablendfunc_s = "BLEND";

    emfxlifespan = 10.0;

};



instance spellfx_darkred_screenblend(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "10";

    userstring[1] = "37 16 2 100";

    userstring[2] = "3";

    visalphablendfunc_s = "BLEND";

    emfxlifespan = 10.0;

};
instance spellfx_teleport_castnosound(cfx_base_proto) {

    visname_s = "MFX_TELEPORT_CAST";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    emtrjmode_s = "FIXED";

};
instance spellfx_summonskeleton_archer(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_summonskeleton_archer_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonskeleton_archer_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonskeleton_archer_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summonskeleton_archer_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_summonskeleton_spear(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_summonskeleton_spear_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonskeleton_spear_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonskeleton_spear_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summonskeleton_spear_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_sumdsnapper(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_sumdsnapper_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_sumdsnapper_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_sumdsnapper_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

};



instance spellfx_sumdsnapper_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_summoncrait(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_summoncrait_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summoncrait_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summoncrait_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

};



instance spellfx_summoncrait_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_sumkhub(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_sumkhub_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_sumkhub_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_sumkhub_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

};



instance spellfx_sumkhub_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_summonshoal(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_summonshoal_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonshoal_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonshoal_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summonshoal_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_severefetidity(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_severefetidity_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_severefetidity_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_severefetidity_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_severefetidity_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};

instance spellfx_dragonbreathofdeath(cfx_base_proto) {

    visname_s = "MFX_DRAGONBREATHOFDEATH";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_ChargeFireball_COLLIDE";

    emfxcolldyn_s = "spellFX_ChargeFireball_COLLIDEDYNFX";

    emfxcolldynperc_s = "vob_magicburn";

    emfxcollstatalign_s = "COLLISIONNORMAL";

    emfxcreatedowntrj = 0;

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 30.0;

    lightpresetname = "FIRESMALL";

};



instance spellfx_dragonbreathofdeath_magic(cfx_base_proto) {

    visname_s = "MFX_DRAGONBREATHOFDEATH_MAGIC";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_ChargeFireball_COLLIDE";

    emfxcolldyn_s = "spellFX_ChargeFireball_COLLIDEDYNFX";

    emfxcolldynperc_s = "vob_magicburn";

    emfxcollstatalign_s = "COLLISIONNORMAL";

    emfxcreatedowntrj = 0;

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 30.0;

    lightpresetname = "FIRESMALL";

};
instance poisoned_fx(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 100";

    userstring[2] = "0.5";

    userstring[3] = "ScreenFX_Pos_a0";

    userstring[4] = "8";

    visalphablendfunc_s = "BLEND";

};



instance insane_fx(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 100";

    userstring[2] = "0.5";

    userstring[3] = "DREAMFX_A0";

    userstring[4] = "46";

    visalphablendfunc_s = "BLEND";

};



instance lowhealth_fx(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 100";

    userstring[2] = "0.5";

    userstring[3] = "ScreenFX_Dem_a0";

    userstring[4] = "8";

    visalphablendfunc_s = "BLEND";

    sfxid = "Heart_Beat";

    sfxisambient = 1;

};



instance startgame_fx(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "RET_LOGO";

    userstring[4] = "1";

    visalphablendfunc_s = "BLEND";

};



instance endgame_fx_01(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_01";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_02(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_02";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_03(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_03";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_04(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_04";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_05(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_05";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_06(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_06";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_07(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_07";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_08(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_08";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_09(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_09";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_10(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_10";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_11(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_11";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_12(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_12";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_13(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_13";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_14(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_14";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_15(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_15";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_16(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_16";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_17(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_17";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_18(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_18";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_19(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_19";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_20(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_20";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_21(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_21";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_22(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_22";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_23(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_23";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_24(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_24";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_25(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_25";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_26(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_26";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_27(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_27";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_28(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_28";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_29(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_29";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_30(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_30";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_31(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_31";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_32(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_32";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_33(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_33";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_34(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_34";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_35(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_35";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_36(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_36";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_37(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_37";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_38(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_38";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_39(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_39";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_40(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_40";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_41(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_41";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_42(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_42";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};



instance endgame_fx_43(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0.4";

    userstring[3] = "LOADING_ENDGAME_43";

    userstring[4] = "1";

    visalphablendfunc_s = "NONE";

};
instance dragonlook_fx(cfx_base_proto) {

    visname_s = "screenblend.scx";

    emfxcreate_s = "FOV_MORPH1";

    userstring = "100000000000";

    userstring[1] = "0 0 0 150";

    userstring[2] = "0.4";

    userstring[3] = "ScreenFX_Drg_a0";

    userstring[4] = "8";

    visalphablendfunc_s = "BLEND";

};
instance spellfx_waterarmor(cfx_base_proto) {

    visname_s = "INVOCATION_BLUE";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "REDAMBIENCE";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_FIREARMOR_SMOKE";

};



instance spellfx_stonearmor(cfx_base_proto) {

    visname_s = "INVOCATION_WHITE";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "WHITEBLEND";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_FIREARMOR_SMOKE";

};



instance spellfx_darkarmor(cfx_base_proto) {

    visname_s = "INVOCATION_VIOLET";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "CATACLYSM";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_FIREARMOR_SMOKE";

};
instance spellfx_icedragon(cfx_base_proto) {

    visname_s = "ICE_DRAGONAURA";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_ICE_SMOKE";

};
instance spellfx_ice_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_ICE";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_ice_smoke_full(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_ICE_FULL";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_moon_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_MOON";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_sand_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_SAND";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_snow_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_SNOW";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_light_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_LIGHT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_fires_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_FIRES";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_fog_smoke(cfx_base_proto) {

    visname_s = "SMOKE_FOG";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};
instance spellfx_firedragon(cfx_base_proto) {

    visname_s = "FIRE_DRAGONAURA";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_FIRE_SMOKE";

};

instance spellfx_fire_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_FIRE";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_fire_smoke_full(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_FIRE_FULL";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_swampdragon(cfx_base_proto) {

    visname_s = "SWAMP_DRAGONAURA";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_SWAMP_SMOKE";

};
instance spellfx_swamp_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_SWAMP";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_swamp_smoke_full(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_SWAMP_FULL";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_redflamedragon(cfx_base_proto) {

    visname_s = "REDFLAME_DRAGONAURA";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_REDFLAME_SMOKE";

};



instance spellfx_redflame_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_REDFLAME";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_redflame_smoke_full(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_REDFLAME_FULL";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_magicdragon(cfx_base_proto) {

    visname_s = "MAGIC_DRAGONAURA";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_MAGIC_SMOKE";

};



instance spellfx_magic_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_MAGIC";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_magic_smoke_full(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_MAGIC_FULL";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_icedragonaura(cfx_base_proto) {

    visname_s = "ICE_DRAGONAURA";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_swampdragonaura(cfx_base_proto) {

    visname_s = "SWAMP_DRAGONAURA";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_firedragonaura(cfx_base_proto) {

    visname_s = "FIRE_DRAGONAURA";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_magicdragonaura(cfx_base_proto) {

    visname_s = "MAGIC_DRAGONAURA";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_redflamedragonaura(cfx_base_proto) {

    visname_s = "REDFLAME_DRAGONAURA";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};

instance spellfx_fire_sword_nb(cfx_base_proto) {

    visname_s = "FIRE_SWORD_NB";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

};
instance spellfx_watersphere(cfx_base_proto) {

    visname_s = "MFX_WATERFIST_INIT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_stonesphere(cfx_base_proto) {

    visname_s = "MFX_MasterOfDisaster_INIT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_darksphere(cfx_base_proto) {

    visname_s = "MFX_BreathOfDeath_INIT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};

instance spellfx_firespell(cfx_base_proto) {

    visname_s = "FIRE_SPELL";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    lightpresetname = "FIRESMALL";

};
instance spellfx_holyarrow(cfx_base_proto) {

    visname_s = "HOLY_ARROW";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_holybolt(cfx_base_proto) {

    visname_s = "HOLY_BOLT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_magicarrow(cfx_base_proto) {

    visname_s = "MAGIC_ARROW";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_magicbolt(cfx_base_proto) {

    visname_s = "MAGIC_BOLT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_poisonarrow(cfx_base_proto) {

    visname_s = "POISON_ARROW";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

};
instance spellfx_enchant_ice(cfx_base_proto) {

    visname_s = "MAGIC_CROSSBOW_ICE";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};
instance spellfx_moonblade(cfx_base_proto) {

    visname_s = "MAGIC_MOONAURA";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    lightpresetname = "AURA";

};
instance spellfx_manapotion_new(cfx_base_proto) {

    visname_s = "MANA_POTION_NEW";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};
instance spellfx_healthpotion_new(cfx_base_proto) {

    visname_s = "HEALTH_POTION_NEW";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};
instance spellfx_dragonundead_smoke_full(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_MAGIC_FULL";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};

instance spellfx_control(cfx_base_proto) {

    visname_s = "MFX_CONTROL_INIT";

    vissize_s = "1 1";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 HEAD";

    emtrjloopmode_s = "none";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emtrjtargetrange = 0.0;

    emtrjtargetelev = 0.0;

    emfxinvesttarget_s = "spellFX_Control_TARGET";

    emfxinvestorigin_s = "spellFX_Control_BRIDGE";

};



instance spellfx_control_key_invest_1(c_particlefxemitkey) {

    visname_s = "simpleglow.tga";

    sfxid = "MFX_CONTROL_STARTINVEST";

    sfxisambient = 1;

};



instance spellfx_control_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    emcreatefxid = "CONTROL_CASTBLEND";

    sfxid = "MFX_CONTROL_CAST";

    sfxisambient = 1;

};



instance spellfx_control_target(cfx_base_proto) {

    visname_s = "MFX_CONTROL_TARGET";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjtargetelev = 0.0;

    sendassessmagic = 1;

    sfxid = "MFX_Pyrokinesis_target";

    sfxisambient = 1;

};



instance spellfx_control_bridge(cfx_base_proto) {

    visname_s = "MFX_CONTROL_BRIDGE";

    emtrjmode_s = "TARGET LINE";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjtargetelev = 0.0;

    emfxcreate_s = "spellFX_Control_ORIGIN";

    sfxid = "MFX_CONTROL_INVEST";

    sfxisambient = 1;

};



instance spellfx_control_bridge_key_init(c_particlefxemitkey) {

    emtrjeasevel = 0.01;

};
instance spellfx_telekinesis(cfx_base_proto) {

    visname_s = "MFX_Telekinesis_INIT";

    vissize_s = "1 1";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 HEAD";

    emtrjloopmode_s = "none";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emtrjtargetrange = 0.0;

    emtrjtargetelev = 0.0;

    emfxinvesttarget_s = "spellFX_Telekinesis_TARGET";

    emfxinvestorigin_s = "spellFX_Telekinesis_ORIGIN";

};



instance spellfx_telekinesis_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_TELEKINESIS_TARGET";

    emtrjeasevel = 2000.0;

    sfxid = "MFX_TELEKINESIS_STARTINVEST";

    sfxisambient = 1;

};



instance spellfx_telekinesis_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_Telekinesis_TargetEnd";

};



instance spellfx_telekinesis_target(cfx_base_proto) {

    visname_s = "MFX_Telekinesis_BRIDGE";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjtargetelev = 0.0;

    sendassessmagic = 1;

    sfxid = "MFX_TELEKINESIS_INVEST";

    sfxisambient = 1;

};



instance spellfx_telekinesis_origin(cfx_base_proto) {

    visname_s = "MFX_Telekinesis_BRIDGE";

    emtrjmode_s = "TARGET LINE";

    emtrjoriginnode = "BIP01 R Hand";

    emtrjtargetnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 0.0;

    sfxid = "MFX_TELEKINESIS_INVEST";

    sfxisambient = 1;

};
instance spellfx_berzerk(cfx_base_proto) {

    visname_s = "MFX_Telekinesis_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_Concussionbolt_COLLIDE";

    emfxcolldyn_s = "spellFX_Concussionbolt_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_berzerk_key_init(c_particlefxemitkey) {

    visname_s = "MFX_Telekinesis_INIT";

    scaleduration = 0.5;

};



instance spellfx_berzerk_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_PalHolyBolt_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1600.0;

    sfxid = "MFX_PalHolyBolt_Cast";

    emcheckcollision = 1;

};



instance spellfx_berzerk_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 0.0;

    emcheckcollision = 0;

};



instance spellfx_berzerk_collide(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

};



instance spellfx_berzerk_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

};
instance spellfx_demoneligor(cfx_base_proto) {

    visname_s = "FIRE_SWORDBLACK";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_DEMONELIGOR_SMOKE";

};



instance spellfx_demoneligor_key_cast(c_particlefxemitkey) {

    lightrange = 500.0;

};



instance spellfx_demoneligor_smoke(cfx_base_proto) {

    visname_s = "SMOKE_MODEL_KAIRO";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "=";

    emtrjtargetrange = 10.0;

    emtrjnumkeys = 10;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    lightpresetname = "FIRESMALL";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_demoneligor_smoke_key_cast(c_particlefxemitkey) {

    lightrange = 500.0;

};



instance spellfx_summoneligor(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_summoneligor_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summoneligor_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summoneligor_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summoneligor_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};
instance spellfx_tplheal(cfx_base_proto) {

    visname_s = "MFX_Heal_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_tplheal_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    emcreatefxid = "spellFX_Heal_ORIGIN";

};



instance spellfx_tplheal_start(cfx_base_proto) {

    visname_s = "MFX_Heal_Start";

    sfxid = "MFX_Light_CAST";

    sfxisambient = 1;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 R FOOT";

};



instance spellfx_tplheal_origin(cfx_base_proto) {

    visname_s = "MFX_Heal_HEAVENLIGHT";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emfxcreate_s = "spellFX_TPLHeal_START";

    emtrjmode_s = "FIXED";

    lightpresetname = "AURA";

};



instance spellfx_tplheal_origin_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_tplheal_origin_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};
instance spellfx_inflate(cfx_base_proto) {

    visname_s = "MFX_MasterOfDisaster_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_INFLATE_COLLIDE";

    emfxcolldyn_s = "spellFX_INFLATE_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_inflate_key_init(c_particlefxemitkey) {

};



instance spellfx_inflate_key_cast(c_particlefxemitkey) {

    emtrjmode_s = "TARGET";

    emtrjeasevel = 2500.0;

    sfxid = "MFX_DestroyUndead_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_inflate_trail(cfx_base_proto) {

    emtrjeasevel = 800.0;

    visname_s = "MFX_MasterOfDisaster_TRAIL";

    visalpha = 1.0;

    emtrjmode_s = "TARGET";

    emcheckcollision = 1;

    emactioncollstat_s = "COLLIDE";

    emactioncolldyn_s = "COLLIDE";

};



instance spellfx_inflate_trail_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_inflate_collide(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_MasterOfDisaster_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_inflate_collidedynfx(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_MasterOfDisaster_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};

instance spellfx_evillight(cfx_base_proto) {

    visname_s = "MFX_FEAR_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjeasefunc_s = "linear";

    emtrjdynupdatedelay = 10000.0;

};
instance spellfx_tplllight(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjeasefunc_s = "linear";

    emtrjdynupdatedelay = 10000.0;

};



instance spellfx_darkllight(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjeasefunc_s = "linear";

    emtrjdynupdatedelay = 10000.0;

};



instance spellfx_darkstaff(cfx_base_proto) {

    visname_s = "FIRE_SWORDBLACK";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_waterstaff(cfx_base_proto) {

    visname_s = "MFX_Icecube_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_firestaff(cfx_base_proto) {

    visname_s = "FIRE_SWORD";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_gurustaff(cfx_base_proto) {

    visname_s = "MFX_WINDFIST_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_gurustaffdamage(cfx_base_proto) {

    visname_s = "MFX_SLEEP_TARGET";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};
instance spellfx_summonicegolem(cfx_base_proto) {

    visname_s = "MFX_Icecube_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "AURA";

};



instance spellfx_summonicegolem_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonicegolem_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonicegolem_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summonicegolem_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_summonfiregolem(cfx_base_proto) {

    visname_s = "MFX_FireStorm_Init";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "FIRESMALL";

};



instance spellfx_summonfiregolem_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonfiregolem_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonfiregolem_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summonfiregolem_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_summonswampgolem(cfx_base_proto) {

    visname_s = "MFX_GREENTENTACLE_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "AURA";

};



instance spellfx_summonswampgolem_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonswampgolem_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summonswampgolem_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summonswampgolem_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_summontreant(cfx_base_proto) {

    visname_s = "MFX_GREENTENTACLE_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "AURA";

};



instance spellfx_summontreant_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summontreant_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_summontreant_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_summontreant_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};
instance spellfx_sleeper_fireball(cfx_base_proto) {

    visname_s = "MFX_Fireball_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 JAWS";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_Fireball_COLLIDE";

    emfxcolldyn_s = "spellFX_Fireball_SENDPERCEPTION";

    emfxcollstatalign_s = "COLLISIONNORMAL";

    emfxcreatedowntrj = 0;

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    userstring = "fireballquadmark.tga";

    userstring[1] = "100 100";

    userstring[2] = "MUL";

    lightpresetname = "FIRESMALL";

};



instance spellfx_sleeper_fireball_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_sleeper_fireball_key_init(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_INIT";

    lightrange = 0.01;

};



instance spellfx_sleeper_fireball_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_INVEST";

    emcreatefxid = "spellFX_Fireball_InVEST_BLAST1";

    lightrange = 150.0;

    sfxid = "MFX_Fireball_invest1";

    sfxisambient = 1;

};



instance spellfx_sleeper_fireball_key_invest_2(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_INVEST_L2";

    emcreatefxid = "spellFX_Fireball_InVEST_BLAST2";

    sfxid = "MFX_Fireball_invest2";

    sfxisambient = 1;

};



instance spellfx_sleeper_fireball_key_invest_3(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_INVEST_L3";

    emcreatefxid = "spellFX_Fireball_InVEST_BLAST3";

    sfxid = "MFX_Fireball_invest3";

    sfxisambient = 1;

};



instance spellfx_sleeper_fireball_key_invest_4(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_INVEST_L4";

    emcreatefxid = "spellFX_Fireball_InVEST_BLAST4";

    sfxid = "MFX_Fireball_invest4";

    sfxisambient = 1;

};



instance spellfx_sleeper_fireball_key_cast(c_particlefxemitkey) {

    lightrange = 200.0;

    visname_s = "MFX_Fireball_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "MFX_Fireball_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_sleeper_fireball_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_stealthball(cfx_base_proto) {

    visname_s = "MFX_INVISIBLEPROJECTILE";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_Deathbolt_COLLIDE";

    emfxcolldyn_s = "spellFX_Deathbolt_COLLIDEDYNFX";

    emfxcolldynperc_s = "VOB_MAGICBURN";

    emfxcollstatalign_s = "COLLISIONNORMAL";

    emfxcreatedowntrj = 0;

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    lightpresetname = "FIRESMALL";

};



instance spellfx_stealthball_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_stealthball_key_init(c_particlefxemitkey) {

    visname_s = "";

    lightrange = 0.01;

};



instance spellfx_stealthball_key_cast(c_particlefxemitkey) {

    lightrange = 200.0;

    visname_s = "";

    emtrjmode_s = "TARGET";

    emselfrotvel_s = "100 100 100";

    emtrjeasevel = 1400.0;

    sfxid = "MFX_Fireball_Cast";

    sfxisambient = 1;

    emcreatefxid = "";

    emcheckcollision = 1;

};



instance spellfx_stealthball_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_stealthball_firecloud(cfx_base_proto) {

    emtrjeasevel = 1400.0;

    visname_s = "";

    visalpha = 1.0;

    emtrjmode_s = "TARGET";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 2;

    emactioncolldyn_s = "COLLIDE";

    emactioncollstat_s = "COLLIDE";

};



instance spellfx_stealthball_firecloud_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_stealthball_collide(cfx_base_proto) {

    visname_s = "";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    lightpresetname = "FIRESMALL";

};



instance spellfx_stealthball_collide_key_invest_1(c_particlefxemitkey) {

    visname_s = "";

    sfxid = "MFX_Fireball_Collide1";

};



instance spellfx_stealthball_collidedynfx(cfx_base_proto) {

    visname_s = "";

    visalpha = 1.0;

    emtrjoriginnode = "BIP01";

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_stealthball_collidedynfx_key_invest_1(c_particlefxemitkey) {

    visname_s = "";

    sfxid = "MFX_Fireball_Collide1";

};
instance spellfx_destroyguardians(cfx_base_proto) {

    visname_s = "MFX_DestroyUndead_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_Destroyundead_COLLIDE";

    emfxcolldyn_s = "spellFX_Destroyundead_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_destroyguardians_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DestroyUndead_INIT";

};



instance spellfx_destroyguardians_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DestroyUndead_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 800.0;

    sfxid = "MFX_DestroyUndead_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_destroyguardians_collide(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_DESTROYUNDEAD_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    lightpresetname = "AURA";

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_destroyguardians_collidedynfx(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_DESTROYUNDEAD_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    lightpresetname = "AURA";

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};
instance spellfx_blooddead1(cfx_base_proto) {

    visname_s = "BFX_PRESET1_DEAD";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_blooddead2(cfx_base_proto) {

    visname_s = "BFX_PRESET2_DEAD";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_blooddead3(cfx_base_proto) {

    visname_s = "BFX_PRESET3_DEAD";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emadjustshptoorigin = 1;

};



instance spellfx_poison(cfx_base_proto) {

    visname_s = "MAGIC_POISON";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 2000000.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    lightpresetname = "AURA";

};
instance spellfx_monsterspawn(cfx_base_proto) {

    visname_s = "MFX_MONSTERSPAWN_FLASH";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    emfxcreate_s = "spellFX_MonsterSpawn_target_Cloud";

    lightpresetname = "JUSTWHITE";

    sfxisambient = 1;

};



instance spellfx_monsterspawn_target_cloud(cfx_base_proto) {

    visname_s = "MFX_MONSTERSPAWN_TARGET";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjdynupdatedelay = 0.01;

};



instance spellfx_orcfireball(cfx_base_proto) {

    visname_s = "MFX_Fireball_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_ORCFIREBALL_COLLIDEFX";

    emfxcolldyn_s = "spellFX_ORCFIREBALL_COLLIDEDYNFX";

    emfxcolldynperc_s = "VOB_MAGICBURN";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    userstring = "fireballquadmark.tga";

    userstring[1] = "40 40";

    userstring[2] = "MUL";

};



instance spellfx_orcfireball_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_orcfireball_key_init(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_INIT";

    lightrange = 0.001;

};



instance spellfx_orcfireball_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_IFB_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "Torch_Enlight";

    lightrange = 100.0;

    emcheckcollision = 1;

};



instance spellfx_orcfireball_key_collide(c_particlefxemitkey) {

    visname_s = "";

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    sfxid = "TORCH_ENLIGHT";

};



instance spellfx_orcfireball_collidefx(cfx_base_proto) {

    visname_s = "MFX_Firebolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

};



instance spellfx_orcfireball_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_Firebolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

};

instance spellfx_whiteeyes(cfx_base_proto) {

    visname_s = "WHITEEYES_LEFT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_WHITEEYES_RIGHT";

    emfxcreatedowntrj = 1;

};



instance spellfx_whiteeyes_right(cfx_base_proto) {

    visname_s = "WHITEEYES_RIGHT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_greeneyes(cfx_base_proto) {

    visname_s = "GREENEYES_LEFT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_GREENEYES_RIGHT";

    emfxcreatedowntrj = 1;

};



instance spellfx_greeneyes_right(cfx_base_proto) {

    visname_s = "GREENEYES_RIGHT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_redeyes(cfx_base_proto) {

    visname_s = "REDEYES_LEFT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_REDEYES_RIGHT";

    emfxcreatedowntrj = 1;

};



instance spellfx_redeyes_right(cfx_base_proto) {

    visname_s = "REDEYES_RIGHT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_DRAGONUNDEAD_SMOKE_FULL";

    emfxcreatedowntrj = 1;

};



instance spellfx_ghost_candle(cfx_base_proto) {

    visname_s = "MFX_GHOST_CANDLE";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_ghost_torch(cfx_base_proto) {

    visname_s = "MFX_GHOST_TORCH";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    lightpresetname = "FIRESMALL";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_fire_torch(cfx_base_proto) {

    visname_s = "MFX_FIRE_TORCH";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    lightpresetname = "FIRE";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance spellfx_warcandle(cfx_base_proto) {

    visname_s = "MFX_WARCANDLE";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    lightpresetname = "FIRE";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

};



instance dialogscope_fx(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "0";

    userstring[1] = "0 0 0 0";

    userstring[2] = "0.1";

    userstring[3] = "DIALOG_SCOPE_A0";

    userstring[4] = "0";

    visalphablendfunc_s = "NONE";

};



instance spellfx_spiderweb(cfx_base_proto) {

    visname_s = "MFX_SPIDERWEB_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};



instance spellfx_spiderweb_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SPIDERWEB_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjeasevel = 1400.0;
    emcheckcollision = 1;
	sfxid = "CRW_DIE_LAST";
};



instance spellfx_spiderweb_key_collide(c_particlefxemitkey) {

};



instance spellfx_spiderweb_bridge(cfx_base_proto) {

    visname_s = "MFX_SPIDERWEB_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;
    emtrjnumkeysvar = 2;
    emtrjangleelevvar = 5.0;
    emtrjangleheadvar = 10.0;
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 900.0;
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_SPIDERWEB_Target";
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    secsperdamage = -1.0;
};



instance spellfx_spiderweb_bridge_key_cast(c_particlefxemitkey) {

    emcheckcollision = 1;
};



instance spellfx_spiderweb_bridge_key_collide(c_particlefxemitkey) {

    visname_s = "";
    emtrjeasevel = 1.0E-6;

};



instance spellfx_spiderweb_target(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_SPIDERWEB_Target";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "CRW_AMBIENT_SHORT_A2";

    sendassessmagic = 1;

};
instance stop_time(cfx_base_proto) {

    visname_s = "time.slw";

    userstring = "0.5";

    userstring[1] = "0.5";

    emfxlifespan = 30.0;

    emfxtriggerdelay = 6.0;

    emfxcreate_s = "STOP_TIME_CHILD2";

    emtrjoriginnode = "BIP01";

};



instance stop_time_child2(cfx_base_proto) {

    emfxtriggerdelay = 6.0;

    emfxlifespan = 30.0;

    visname_s = "morph.fov";

    userstring = "0.8";

    userstring[1] = "1.0";

    userstring[2] = "120";

    userstring[3] = "90";

};



instance spellfx_cast_guru(cfx_base_proto) {

    visname_s = "CAST_GURU";

    emtrjmode_s = "FIXED";

    emfxtriggerdelay = 6.0;

    emfxlifespan = 30.0;

    emtrjoriginnode = "BIP01 HEAD";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldynperc_s = "PRACTICEMAGIC_03";

    emfxcolldynalign_s = "COLLISIONNORMAL";

    emcheckcollision = 1;

    lightpresetname = "AURA";

    sfxid = "MFX_CONTROL_STARTINVEST";

    sfxisambient = 1;

};
instance spellfx_dragonicecube(cfx_base_proto) {

    visname_s = "MFX_DRAGONIcecube_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_DRAGONIceCube_COLLIDE";

    emfxcolldynperc_s = "spellFX_DRAGONIcespell_SENDPERCEPTION";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 30.0;

    emfxtriggerdelay = 1.0;

    emfxinvestorigin_s = "spellFX_DRAGONIcespell_Invest";

    lightpresetname = "AURA";

};



instance spellfx_dragonicecube_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_dragonicecube_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DRAGONIcecube_INIT";

    lightrange = 0.01;

    scaleduration = 0.5;

};



instance spellfx_dragonicecube_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DRAGONICECUBE_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1000.0;

    emcheckcollision = 1;

    sfxid = "MFX_Icecube_cast";

    sfxisambient = 1;

    lightrange = 100.0;

};



instance spellfx_dragonicecube_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_dragonicecube_collide(cfx_base_proto) {

    visname_s = "MFX_ICESPELL_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_ICECUBE_COLLIDE";

};



instance spellfx_dragonicespell_invest(cfx_base_proto) {

    visname_s = "";

    emtrjmode_s = "FIXED";

    sfxid = "MFX_ICECUBE_INVEST";

    sfxisambient = 1;

};



instance spellfx_dragonicespell_sendperception(cfx_base_proto) {

    visname_s = "MFX_IceSpell_Target";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sendassessmagic = 1;

    emadjustshptoorigin = 1;

    sfxid = "MFX_Icecube_Target";

};



instance pockertable(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "100000000000";

    userstring[1] = "0 0 0 255";

    userstring[2] = "0";

    userstring[3] = "PlayTable.tga";

    visalphablendfunc_s = "BLEND";

};
instance spellfx_firelight(cfx_base_proto) {

    visname_s = "MFX_FIRELIGHT_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_firelight_key_init(c_particlefxemitkey) {

    visname_s = "MFX_FIRELIGHT_INIT";

};



instance spellfx_firelight_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_FIRELIGHT_RIGHTHAND";

};



instance spellfx_firelight_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_FIRELIGHT_GROUND";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_firelight_ground(cfx_base_proto) {

    visname_s = "MFX_FIRELIGHT_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Firestorm_Cast";

    sfxisambient = 1;

};



instance hero_hurt(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "0.1";

    userstring[1] = "128 0 0 64";

    userstring[2] = "0.1";

    userstring[3] = "";

    visalphablendfunc_s = "ADD";

    emfxlifespan = 0.1;

};



instance spellfx_rapidfirebolt(cfx_base_proto) {

    visname_s = "MFX_ChargeFB_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_RapidFirebolt_COLLIDEFX";

    emfxcolldyn_s = "spellFX_RapidFirebolt_COLLIDEDYNFX";

    emfxcolldynperc_s = "VOB_MAGICBURN";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    lightpresetname = "FIRESMALL";

    userstring = "fireballquadmark.tga";

    userstring[1] = "40 40";

    userstring[2] = "MUL";

};



instance spellfx_rapidfirebolt_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_rapidfirebolt_key_init(c_particlefxemitkey) {

    visname_s = "MFX_ChargeFB_INIT";

    lightrange = 0.001;

};



instance spellfx_rapidfirebolt_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide4";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "Torch_Enlight";

    lightrange = 100.0;

    emcheckcollision = 1;

};



instance spellfx_rapidfirebolt_key_collide(c_particlefxemitkey) {

    visname_s = "";

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    sfxid = "TORCH_ENLIGHT";

};



instance spellfx_rapidfirebolt_collidefx(cfx_base_proto) {

    visname_s = "MFX_Fireball_Collide4";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_rapidfirebolt_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_Firebolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_rapidicebolt(cfx_base_proto) {

    visname_s = "MFX_Icebolt_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_RapidIcebolt_COLLIDE";

    emfxcolldyn_s = "spellFX_RapidIcebolt_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_rapidicebolt_key_init(c_particlefxemitkey) {

    visname_s = "MFX_Icebolt_INIT";

    scaleduration = 0.5;

};



instance spellfx_rapidicebolt_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_Icebolt_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "mfx_thunderbolt_cast";

    emcheckcollision = 1;

};



instance spellfx_rapidicebolt_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    emcheckcollision = 0;

};



instance spellfx_rapidicebolt_collide(cfx_base_proto) {

    visname_s = "MFX_Icebolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

};



instance spellfx_rapidicebolt_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_Thunderbolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

    sendassessmagic = 1;

};
instance spellfx_geyser_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};
instance spellfx_druidskill_0(cfx_base_proto) {

    visname_s = "MFX_GOLEMSKILL_CAST";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    lightpresetname = "REDAMBIENCE";

    sfxid = "mfx_thunderbolt_cast";

    sfxisambient = 1;

};

instance spellfx_firebolt_likerh_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_firebolt_likerh_key_init(c_particlefxemitkey) {

    visname_s = "MFX_Firebolt_INIT";

    lightrange = 0.001;

};



instance spellfx_firebolt_likerh_key_cast(c_particlefxemitkey) {

    visname_s = "mfx_firebolt_cast";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "Torch_Enlight";

    lightrange = 100.0;

    emcheckcollision = 1;

};
instance spellfx_dragonflameball_collide_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide";

    sfxid = "MFX_Fireball_Collide1";

};



instance spellfx_dragonflameball_collide_key_invest_2(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide";

    sfxid = "MFX_Fireball_Collide2";

};



instance spellfx_dragonflameball_collide_key_invest_3(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide";

    sfxid = "MFX_Fireball_Collide3";

};



instance spellfx_dragonflameball_collide_key_invest_4(c_particlefxemitkey) {

    visname_s = "MFX_Fireball_Collide";

    sfxid = "MFX_Fireball_Collide4";

};
instance spellfx_unlockchest(cfx_base_proto) {

    visname_s = "MFX_CHARM_INIT";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjmode_s = "fixed";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxinvesttarget_s = "spellFX_UnlockChest_TARGET";

};



instance spellfx_unlockchest_key_init(c_particlefxemitkey) {

    visname_s = "MFX_CHARM_INIT";

};



instance spellfx_unlockchest_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_CHARM_ORIGIN";

    emtrjeasevel = 1400.0;

    sfxid = "MFX_UNLOCK_CAST";

};



instance spellfx_unlockchest_origin(cfx_base_proto) {

    visname_s = "MFX_CHARM_ORIGIN";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjdynupdatedelay = 0.0;

};



instance spellfx_unlockchest_target(cfx_base_proto) {

    lightpresetname = "AURA";

    visname_s = "MFX_CHARM_TARGET";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    emtrjdynupdatedelay = 0.0;

};
instance vob_magicburn_nosnd(cfx_base_proto) {

    emtrjoriginnode = "BIP01 FIRE";

    visname_s = "MFX_MagicFire_HUMANBURN_NOSND";

    emfxcreate_s = "VOB_MAGICBURN_NOSND_CHILD1";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

};



instance vob_magicburn_nosnd_child1(cfx_base_proto) {

    emtrjoriginnode = "BIP01 R UPPERARM";

    visname_s = "MFX_MagicFire_HUMANBURN_NOSND";

    emfxcreate_s = "VOB_MAGICBURN_NOSND_CHILD2";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

};



instance vob_magicburn_nosnd_child2(cfx_base_proto) {

    emtrjoriginnode = "BIP01 L UPPERARM";

    visname_s = "MFX_MagicFire_HUMANBURN_NOSND";

    emfxcreate_s = "VOB_MAGICBURN_NOSND_CHILD3";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

};



instance vob_magicburn_nosnd_child3(cfx_base_proto) {

    emtrjoriginnode = "BIP01 L HAND";

    visname_s = "MFX_MagicFire_HUMANBURN_NOSND";

    emfxcreate_s = "VOB_MAGICBURN_NOSND_CHILD4";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

};



instance vob_magicburn_nosnd_child4(cfx_base_proto) {

    emtrjoriginnode = "BIP01 R HAND";

    visname_s = "MFX_MAGICFIRE_HUMANBURN_NOSND";

    emfxcreate_s = "VOB_MAGICBURN_NOSND_CHILD5";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

};



instance vob_magicburn_nosnd_child5(cfx_base_proto) {

    emtrjoriginnode = "BIP01 L FOOT";

    visname_s = "MFX_MAGICFIRE_HUMANBURN_NOSND";

    emfxcreate_s = "VOB_MAGICBURN_NOSND_CHILD6";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

};



instance vob_magicburn_nosnd_child6(cfx_base_proto) {

    emtrjoriginnode = "BIP01 R FOOT";

    visname_s = "MFX_MAGICFIRE_HUMANBURN_NOSND";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    sendassessmagic = 1;

};

instance spellfx_adanosballred(cfx_base_proto) {

    visname_s = "MFX_ADANOSBALLRED_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emfxcolldyn_s = "spellFX_AdanosballRED_TARGET";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	emtrjdynupdatedelay = 20000;	
    lightpresetname = "AURA";

};



instance spellfx_adanosballred_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};


/*
instance spellfx_adanosballred_key_invest(c_particlefxemitkey) {

    lightrange = 100.0;

};
*/


instance spellfx_adanosballred_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_ADANOSBALLRED_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    sfxid = "MFX_THUNDERBOLT_CAST";
    lightrange = 100.0;
    emcheckcollision = 1;

};



instance spellfx_adanosballred_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};


/*
instance spellfx_adanosballred_key_back(c_particlefxemitkey) {

    visname_s = "";

    emtrjmode_s = "FIXED";

};
*/


instance spellfx_adanosballred_target(cfx_base_proto) {

    visname_s = "MFX_ADANOSBALLRED_TARGET";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    sendassessmagic = 1;

    sfxid = "MFX_THUNDERBOLT_CAST";

    sfxisambient = 1;

};
instance spellfx_elevate(cfx_base_proto) {

    visname_s = "MFX_ELEVATE_INIT";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emfxcreatedowntrj = 1;

    emtrjeasefunc_s = "LINEAR";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emfxinvestorigin_s = "spellFX_Elevate_Invest";

};



instance spellfx_elevate_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_ELEVATE_CAST";

    sfxid = "MFX_ELEVATE_CAST";

};



instance spellfx_elevate_invest(cfx_base_proto) {

    visname_s = "MFX_ELEVATE_INVEST";

    emfxcreatedowntrj = 1;

    emtrjoriginnode = "ZS_RIGHTHAND";

    emfxcreate_s = "spellFX_Elevate_Invest_LH";

    emtrjeasefunc_s = "LINEAR";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emfxlifespan = 3.0;

    sfxid = "MFX_ELEVATE_INVEST";

};



instance spellfx_elevate_invest_lh(cfx_base_proto) {

    visname_s = "MFX_ELEVATE_INVEST";

    emfxcreatedowntrj = 1;

    emtrjoriginnode = "ZS_LEFTHAND";

    emtrjeasefunc_s = "LINEAR";

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emfxlifespan = 3.0;

};



instance spellfx_elevator_dust_first(cfx_base_proto) {

    visname_s = "ELEVATOR_DUST";

    emfxcreate_s = "spellFX_ELEVATOR_BURST";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "NONE";

    emtrjoriginnode = "BIP01";

    emfxtriggerdelay = 0.55;

};



instance spellfx_elevator_burst(cfx_base_proto) {

    emfxcreate_s = "spellFX_ELEVATOR_STONEPARTICLES";

    emfxcreatedowntrj = 1;

    emfxtriggerdelay = 0.57;

    sfxid = "MFX_ELEVATE_BURST";

};



instance spellfx_elevator_stoneparticles(cfx_base_proto) {

    visname_s = "ELEVATOR_STONES";

    emfxcreate_s = "spellFX_ELEVATOR_STONESFALLING";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "NONE";

    emtrjoriginnode = "BIP01";

    emfxtriggerdelay = 0.61;

    sfxid = "MFX_ELEVATE_STONES";

    sfxisambient = 1;

};



instance spellfx_elevator_stonesfalling(cfx_base_proto) {

    visname_s = "ELEVATOR_STONESFALL";

    emfxcreatedowntrj = 1;

    emfxcreate_s = "spellFX_ELEVATOR_DUSTFALLING";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    emfxtriggerdelay = 0.0;

};



instance spellfx_elevator_dustfalling(cfx_base_proto) {

    visname_s = "ELEVATOR_DUST_FALLING";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    emfxtriggerdelay = 0.0;

};



instance spellfx_elevator_earthquake(cfx_base_proto) {

    visname_s = "earthquake.eqk";

    userstring = "2000";

    userstring[1] = "3";

    userstring[2] = "5 5 5";

};



instance spellfx_waterwall(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_waterwall_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_waterwall_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_waterwall_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

    emcreatefxid = "FX_EarthQuake";

};



instance spellfx_waterwall_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_firewave(cfx_base_proto) {

    visname_s = "MFX_FIREWAVE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_firewave_key_init(c_particlefxemitkey) {

    visname_s = "MFX_FIREWAVE_INIT";

};



instance spellfx_firewave_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_FIREWAVE_RIGHTHAND";

    emcreatefxid = "spellFX_FIREWAVE_LEFTHAND";

};



instance spellfx_firewave_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_FIREWAVE_EXPLOSION";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_firewave_explosion(cfx_base_proto) {

    visname_s = "MFX_FIREWAVE_EXPLOSION";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "Bip01 L Hand";

    emfxcreate_s = "spellFX_FIREWAVE_GROUND";

};



instance spellfx_firewave_ground(cfx_base_proto) {

    visname_s = "MFX_FIREWAVE_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "spellFX_FIREWAVE_COLLIDEDYNFX";

    emfxcolldynalign_s = "COLLISIONNORMAL";

    emcheckcollision = 1;

    lightpresetname = "REDAMBIENCE";

    sfxid = "MFX_FIREWAVE_CAST";

    sfxisambient = 1;

};



instance spellfx_firewave_lefthand(cfx_base_proto) {

    visname_s = "MFX_FIREWAVE_LEFTHAND";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "Bip01 L Hand";

    emfxcreate_s = "FX_EARTHQUAKE";

};



instance spellfx_firewave_sub(cfx_base_proto) {

    visname_s = "";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

};



instance spellfx_firewave_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_FIREWAVE_TARGET";

    emtrjoriginnode = "BIP01";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_FIREWAVE_TARGET";

};



instance spellfx_lightningsphere(cfx_base_proto) {

    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_LIGHTNINGSPHERE_SENDPERCEPTION";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
    lightpresetname = "AURA";
    sfxid = "MFX_BARRIERE_AMBIENT";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_lightningsphere_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_lightningsphere_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_LIGHTNINGSPHERE_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "MFX_BARRIERE_WARNING";
};



instance spellfx_lightningsphere_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_BARRIERE_SHOOT";
};


/*
instance spellfx_lightningsphere_invest(cfx_base_proto) {

    visname_s = "MFX_LIGHTNINGSPHERE_INVEST";
    emtrjmode_s = "FIXED";
};
*/


instance spellfx_lightningsphere_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_lightningsphere_bloodfly(cfx_base_proto) {

    visname_s = "MFX_LIGHTNINGSPHERE_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_lightningsphere_sendperception(cfx_base_proto) {

    visname_s = "MFX_LIGHTNINGSPHERE_TARGET";
    sendassessmagic = 1;
    sfxid = "MFX_BARRIERE_SHOOT";
};



instance spellfx_bloodrain(cfx_base_proto) {

    visname_s = "MFX_BLOODRAIN_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emfxinvestorigin_s = "spellFX_BLOODRAIN_INVESTGLOW";

};



instance spellfx_bloodrain_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_BLOODRAIN_RAIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_bloodrain_rain(cfx_base_proto) {

    visname_s = "MFX_BLOODRAIN_Rain";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldynalign_s = "COLLISIONNORMAL";

    emcheckcollision = 1;

    emtrjeasevel = 10000.0;

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_MASSDEATH_CAST";

    sfxisambient = 1;

};



instance spellfx_bloodrain_sub(cfx_base_proto) {

    visname_s = "";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

};



instance spellfx_bloodrain_investglow(cfx_base_proto) {

    visname_s = "MFX_BLOODRAIN_INVESTGLOW";

    emtrjoriginnode = "BIP01";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_SUCKENERGY_CAST";

    sfxisambient = 1;

    emfxcreate_s = "FX_EarthQuake";

};



instance spellfx_icerain(cfx_base_proto) {

    visname_s = "MFX_ICERAIN_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxinvestorigin_s = "spellFX_ICERAIN_INVESTGLOW";

};



instance spellfx_icerain_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellfx_ICERAIN_rain";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_icerain_rain(cfx_base_proto) {

    visname_s = "MFX_ICERAIN_Rain";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldynalign_s = "COLLISIONNORMAL";

    emcheckcollision = 1;

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Thunderstorm_IceRain";

    sfxisambient = 1;

};



instance spellfx_icerain_sub(cfx_base_proto) {

    visname_s = "";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

};



instance spellfx_icerain_investglow(cfx_base_proto) {

    visname_s = "MFX_ICERAIN_INVESTGLOW";

    emtrjoriginnode = "BIP01";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    lightpresetname = "REDAMBIENCE";

    sfxid = "MFX_ICERAIN_INVEST";

    sfxisambient = 1;

    emfxcreate_s = "FX_EarthQuake";

};



instance spellfx_abyssspell(cfx_base_proto) {

    visname_s = "MFX_ABYSSSPELL_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

   // emtrjloopmode_s = "PINGPONG_ONCE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
	

    emfxcolldynperc_s = "spellFX_ABYSSSPELL_SENDPERCEPTION";

    emfxcolldyn_s = "SPELLFX_ABYSSSPELL_SENDPERCEPTION";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    lightpresetname = "AURA";

 //   emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_abyssspell_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_abyssspell_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_ABYSSSPELL_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 2000.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "WSP_ATTACK";

};



instance spellfx_abyssspell_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

    pfx_ppsisloopingchg = 1;

};

/*

instance spellfx_abyssspell_invest(cfx_base_proto) {

    visname_s = "MFX_ABYSSSPELL_INVEST";

    emtrjmode_s = "FIXED";

};

*/

instance spellfx_abyssspell_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;

    emfxlifespan = 30.0;

    emselfrotvel_s = "0 400 0";

    visname_s = "morph.fov";

    userstring = "0.8";

    userstring[1] = "1.0";

    userstring[2] = "120";

    userstring[3] = "90";

};



instance spellfx_abyssspell_bloodfly(cfx_base_proto) {

    visname_s = "MFX_ABYSSSPELL_FLYTOPLAYER";

    emtrjeasevel = 0.01;

    emtrjmode_s = "TARGET LINE";

    emtrjoriginnode = "Bip01 Spine2";

    emtrjtargetnode = "ZS_RIGHTHAND";

    emtrjdynupdatedelay = 0.01;

};



instance spellfx_abyssspell_sendperception(cfx_base_proto) {

    visname_s = "MFX_ABYSSSPELL_TARGET";

    sendassessmagic = 1;

        sfxid = "WSP_WHOSH1";

};



instance spellfx_magsphere(cfx_base_proto) {

    visname_s = "MFX_MAGSPHERE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_MAGSPHERE_COLLIDE";

    emfxcolldyn_s = "spellFX_MAGSPHERE_COLLIDEDYNFX";

    emfxcollstatalign_s = "COLLISIONNORMAL";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_magsphere_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_magsphere_key_init(c_particlefxemitkey) {

    visname_s = "MFX_MAGSPHERE_INIT";

    lightrange = 0.01;

};



instance spellfx_magsphere_key_cast(c_particlefxemitkey) {

    emtrjmode_s = "TARGET";

    emtrjeasevel = 2200.0;

    visname_s = "MFX_MAGSPHERE_CAST";

    sfxid = "MFX_CHARM_CAST";

    sfxisambient = 1;

    emcheckcollision = 1;

    emselfrotvel_s = "10 10 10";

    emcreatefxid = "SPELLFX_MAGSPHERE_CAST2";

};



instance spellfx_magsphere_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_magsphere_collide(cfx_base_proto) {

    visname_s = "MFX_MAGSPHERE_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    lightpresetname = "FIRESMALL";

};



instance spellfx_magsphere_collidefx(cfx_base_proto) {

    visname_s = "MFX_MAGSPHERE_Collide";

    emtrjmode_s = "FIXED";

};



instance spellfx_magsphere_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_MAGSPHERE_Collide";

    visalpha = 1.0;

    emtrjoriginnode = "BIP01";

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_magsphere_firecloud(cfx_base_proto) {

    emtrjeasevel = 2000.0;

    visname_s = "MFX_MAGSPHERE_CAST";

    visalpha = 1.0;

    emtrjmode_s = "TARGET";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 2;

    emactioncolldyn_s = "COLLIDE";

    emactioncollstat_s = "COLLIDE";

    sendassessmagic = 1;

};



instance spellfx_magsphere_firecloud_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_magsphere_collide_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_MAGSPHERE_COLLIDE";

    sfxid = "Torch_Enlight";

};



instance spellfx_magsphere_collidedynfx_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_MAGSPHERE_COLLIDE";

    sfxid = "Torch_Enlight";

};



instance spellfx_stonefirst(cfx_base_proto) {

    visname_s = "MFX_STONEFIRST_Init";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_STONEFIRST_SPREAD";

    emfxcolldyn_s = "spellFX_STONEFIRST_SPREAD";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emfxinvestorigin_s = "spellFX_STONEFIRST_INVESTSOUND";

    userstring = "fireballquadmark.tga";

    userstring[1] = "100 100";

    userstring[2] = "MUL";

    lightpresetname = "FIRESMALL";

};



instance spellfx_stonefirst_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_stonefirst_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_stonefirst_spread(cfx_base_proto) {

    visname_s = "MFX_STONEFIRST_SPREAD_SMALL";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "spellFX_STONEFIRST_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    userstring = "fireballquadmark.tga";

    userstring[1] = "40 40";

    userstring[2] = "MUL";

    lightpresetname = "FIRESMALL";

    emfxcreate_s = "spellFX_STONEFIRST_COLLIDE";

    sfxid = "MFX_STONEFIRST_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_stonefirst_spread_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_stonefirst_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_STONEFIRST_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1300.0;

    sfxid = "MFX_STONEFIRST_CAST";

    sfxisambient = 1;

    emcheckcollision = 1;

    lightrange = 100.0;

};



instance spellfx_stonefirst_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_stonefirst_collide(cfx_base_proto) {

    visname_s = "MFX_STONEFIRST_Collide3";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_STONEFIRST_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_blueeyes(cfx_base_proto) {

    visname_s = "WHITEEYES_LEFT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreate_s = "SPELLFX_BLUEEYES_RIGHT";

    emfxcreatedowntrj = 1;

};



instance spellfx_blueeyes_right(cfx_base_proto) {

    visname_s = "BLUEEYES_RIGHT";

    visalpha = 1.0;

    visalphablendfunc_s = "ADD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

    emtrjtargetrange = 0.0;

    emtrjnumkeys = 0;

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emadjustshptoorigin = 1;

    emfxcreatedowntrj = 1;

};



instance spellfx_fear_wings_blue(cfx_base_proto) {

    visname_s = "MFX_FEAR_WINGS_BLUE";

    emtrjmode_s = "FIXED";

    emtrjeasefunc_s = "linear";

    emtrjoriginnode = "BIP01";

    emtrjdynupdatedelay = 0.4;

    emfxcreate_s = "FX_Earthquake";

    emtrjmode_s = "FOLLOW TARGET";

};



instance spellfx_fear_wings2_blue(cfx_base_proto) {

    visname_s = "MFX_FEAR_WINGS2_BLUE";

    emtrjmode_s = "FIXED";

    emtrjeasefunc_s = "linear";

    emtrjoriginnode = "BIP01";

    emtrjdynupdatedelay = 0.4;

    emtrjmode_s = "FOLLOW TARGET";

};



instance spellfx_greenstrike(cfx_base_proto) {

    visname_s = "MFX_GREENSTRIKE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_GREENSTRIKE_COLLIDEFX";

    emfxcolldyn_s = "spellFX_GREENSTRIKE_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    lightpresetname = "FIRESMALL";

    userstring = "fireballquadmark.tga";

    userstring[1] = "40 40";

    userstring[2] = "MUL";

};



instance spellfx_greenstrike_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_greenstrike_key_init(c_particlefxemitkey) {

    visname_s = "MFX_GREENSTRIKE_INIT";

    lightrange = 0.001;

};



instance spellfx_greenstrike_key_cast(c_particlefxemitkey) {

    visname_s = "mfx_GREENSTRIKE_cast";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "Torch_Enlight";

    lightrange = 100.0;

    emcheckcollision = 1;

};



instance spellfx_greenstrike_key_collide(c_particlefxemitkey) {

    visname_s = "";

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    sfxid = "TORCH_ENLIGHT";

};



instance spellfx_greenstrike_collidefx(cfx_base_proto) {

    visname_s = "MFX_GREENSTRIKE_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_greenstrike_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_GREENSTRIKE_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_firelance(cfx_base_proto) {

    visname_s = "MFX_FIRELANCE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_FIRELANCE_COLLIDEFX";

    emfxcolldyn_s = "spellFX_FIRELANCE_COLLIDEDYNFX";

    emfxcolldynperc_s = "VOB_MAGICBURN";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    userstring = "fireballquadmark.tga";

    userstring[1] = "40 40";

    userstring[2] = "MUL";

};



instance spellfx_firelance_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_firelance_key_init(c_particlefxemitkey) {

    visname_s = "MFX_FIRELANCE_INIT";

    lightrange = 0.001;

};



instance spellfx_firelance_key_cast(c_particlefxemitkey) {

    visname_s = "mfx_FIRELANCE_cast";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "Torch_Enlight";

    lightrange = 100.0;

    emcheckcollision = 1;

};



instance spellfx_firelance_key_collide(c_particlefxemitkey) {

    visname_s = "";

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    sfxid = "TORCH_ENLIGHT";

};



instance spellfx_firelance_collidefx(cfx_base_proto) {

    visname_s = "MFX_FIRELANCE_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

};



instance spellfx_firelance_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_FIRELANCE_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

};



instance spellfx_deathstrike(cfx_base_proto) {

    visname_s = "MFX_DEATHSTRIKE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_DEATHSTRIKE_COLLIDEFX";

    emfxcolldyn_s = "spellFX_DEATHSTRIKE_COLLIDEDYNFX";

    emfxcolldynperc_s = "VOB_MAGICBURN";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    lightpresetname = "FIRESMALL";

    userstring = "fireballquadmark.tga";

    userstring[1] = "40 40";

    userstring[2] = "MUL";

};



instance spellfx_deathstrike_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_deathstrike_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DEATHSTRIKE_INIT";

    lightrange = 0.001;

};



instance spellfx_deathstrike_key_cast(c_particlefxemitkey) {

    visname_s = "mfx_DEATHSTRIKE_cast";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "Torch_Enlight";

    lightrange = 100.0;

    emcheckcollision = 1;

};



instance spellfx_deathstrike_key_collide(c_particlefxemitkey) {

    visname_s = "";

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    sfxid = "TORCH_ENLIGHT";

};
instance spellfx_deathstrike_collidefx(cfx_base_proto) {

    visname_s = "MFX_DEATHSTRIKE_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_deathstrike_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_DEATHSTRIKE_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "FIRESMALL";

};



instance spellfx_necrobolt(cfx_base_proto) {

    visname_s = "MFX_NECROBOLT_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetrange = 20.0;

    emtrjnumkeys = 4;

    emtrjnumkeysvar = 1;

    emtrjangleelevvar = 0.0;

    emtrjangleheadvar = 0.0;

    emtrjeasefunc_s = "LINEAR";

    emtrjeasevel = 100.0;

    emtrjdynupdatedelay = 20000.0;

    emfxcreatedowntrj = 1;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 -400 0";

    secsperdamage = -1.0;

};



instance spellfx_necrobolt_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_necrobolt_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_NECROBOLT_NECROBOLT";

    pfx_ppsisloopingchg = 1;

    sfxid = "MFX_SKULL_Cast";

    sfxisambient = 1;

    emtrjeasevel = 1350.0;

};



instance spellfx_necrobolt_necrobolt(cfx_base_proto) {

    visname_s = "MFX_NECROBOLT_CAST";

    emtrjmode_s = "TARGET SPLINE";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetrange = 20.0;

    emtrjangleelevvar = 15.0;

    emtrjangleheadvar = 25.0;

    emtrjnumkeys = 2;

    emtrjnumkeysvar = 1;

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjdynupdatetargetonly = 1;

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_NECROBOLT_COLLIDEFX";

    emfxcolldyn_s = "spellFX_NECROBOLT_SPREAD";

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emtrjeasevel = 1350.0;

};



instance spellfx_necrobolt_necrobolt_key_cast(c_particlefxemitkey) {

    emcheckcollision = 1;

    sfxid = "MFX_SKULL_Fly";

};



instance spellfx_necrobolt_spread(cfx_base_proto) {

    visname_s = "MFX_NECROBOLT_SPREAD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "spellFX_NECROBOLT_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_FIrestorm_Collide";

    sfxisambient = 1;

};



instance spellfx_necrobolt_collidefx(cfx_base_proto) {

    visname_s = "MFX_NECROBOLT_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_SKULL_Collide";

};



instance spellfx_gurumass(cfx_base_proto) {

    visname_s = "MFX_GURUMASS_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetrange = 20.0;

    emtrjnumkeys = 4;

    emtrjnumkeysvar = 1;

    emtrjangleelevvar = 0.0;

    emtrjangleheadvar = 0.0;

    emtrjeasefunc_s = "LINEAR";

    emtrjeasevel = 100.0;

    emtrjdynupdatedelay = 20000.0;

    emfxcreatedowntrj = 1;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 -400 0";

    secsperdamage = -1.0;

};



instance spellfx_gurumass_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_gurumass_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_GURUMASS_GURUMASS";

    pfx_ppsisloopingchg = 1;

    sfxid = "MFX_SKULL_Cast";

    sfxisambient = 1;

    emtrjeasevel = 1000.0;

};



instance spellfx_gurumass_gurumass(cfx_base_proto) {

    visname_s = "MFX_GURUMASS_CAST";

    emtrjmode_s = "TARGET SPLINE";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetrange = 20.0;

    emtrjangleelevvar = 15.0;

    emtrjangleheadvar = 25.0;

    emtrjnumkeys = 2;

    emtrjnumkeysvar = 1;

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjdynupdatetargetonly = 1;

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_GURUMASS_COLLIDEFX";

    emfxcolldyn_s = "spellFX_GURUMASS_SPREAD";

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

    emtrjeasevel = 1200.0;

};



instance spellfx_gurumass_gurumass_key_cast(c_particlefxemitkey) {

    emcheckcollision = 1;

    sfxid = "MFX_SKULL_Fly";

};



instance spellfx_gurumass_spread(cfx_base_proto) {

    visname_s = "MFX_GURUMASS_SPREAD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "spellFX_GURUMASS_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_FIrestorm_Collide";

    sfxisambient = 1;

};



instance spellfx_gurumass_collidefx(cfx_base_proto) {

    visname_s = "MFX_GURUMASS_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_SKULL_Collide";

};



instance spellfx_darkheal(cfx_base_proto) {

    visname_s = "MFX_DARKHEAL_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_darkheal_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DARKHEAL_CAST";

    emcreatefxid = "spellFX_DARKHEAL_LEFTHAND";

};



instance spellfx_darkheal_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    emcreatefxid = "spellFX_DARKHEAL_ORIGIN";

};



instance spellfx_darkheal_origin(cfx_base_proto) {

    visname_s = "MFX_DARKHEAL_HEAVENLIGHT";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_DARKHEAL_CAST";

    sfxisambient = 1;

};



instance spellfx_darkheal_lefthand(cfx_base_proto) {

    visname_s = "MFX_DARKHEAL_CAST";

    emtrjoriginnode = "ZS_LEFTHAND";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "AURA";

};



instance spellfx_darkheal_lefthand_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_darkheal_lefthand_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_tplmediumheal(cfx_base_proto) {

    visname_s = "MFX_Heal_INIT_BLUE";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_tplmediumheal_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    emcreatefxid = "SPELLFX_TPLMEDIUMHEAL_ORIGIN";

};



instance spellfx_tplmediumheal_origin(cfx_base_proto) {

    visname_s = "MFX_Heal_HEAVENLIGHT_BLUE";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_HEAL_CAST";

    sfxisambient = 1;

};



instance spellfx_tplmediumheal_origin_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_tplmediumheal_origin_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_tplheavyheal(cfx_base_proto) {

    visname_s = "MFX_Heal_INIT_YELLOW";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_tplheavyheal_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    emcreatefxid = "SPELLFX_TPLHEAVYHEAL_ORIGIN";

};



instance spellfx_tplheavyheal_start(cfx_base_proto) {

    visname_s = "MFX_Heal_Start";

    sfxid = "MFX_Light_CAST";

    sfxisambient = 1;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 R FOOT";

};



instance spellfx_tplheavyheal_origin(cfx_base_proto) {

    visname_s = "MFX_Heal_HEAVENLIGHT_YELLOW";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_HEAL_CAST";

    sfxisambient = 1;

};



instance spellfx_tplheavyheal_origin_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_tplheavyheal_origin_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_tplsuperheal(cfx_base_proto) {

    visname_s = "MFX_Heal_INIT_RED";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_tplsuperheal_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    emcreatefxid = "SPELLFX_TPLSUPERHEAL_ORIGIN";

};



instance spellfx_tplsuperheal_start(cfx_base_proto) {

    sfxid = "MFX_Light_CAST";

    sfxisambient = 1;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 R FOOT";

};



instance spellfx_tplsuperheal_origin(cfx_base_proto) {

    visname_s = "MFX_Heal_HEAVENLIGHT_RED";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_HEAL_CAST";

    sfxisambient = 1;

};



instance spellfx_tplsuperheal_origin_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_tplsuperheal_origin_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_slowdown_vis(cfx_base_proto) {

    visname_s = "MFX_SLOWDOWN_ORIGIN";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    emtrjoriginnode = "BIP01 Head";

    emtrjeasevel = 0.0;

    emtrjloopmode_s = "HALT";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjtargetrange = 1.2;

    emtrjtargetelev = 89.0;

    emtrjeasevel = 1400.0;

};



instance spellfx_blink(cfx_base_proto) {

    visname_s = "MFX_Blink_INIT";

};



instance spellfx_blink_key_invest_1(c_particlefxemitkey) {

};



instance spellfx_blink_key_invest_2(c_particlefxemitkey) {

    sfxid = "MFX_Fireball_invest1";

    sfxisambient = 1;

};



instance spellfx_blink_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_Blink_CAST";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_blink_target(cfx_base_proto) {

    visname_s = "MFX_BLINK_DEST";

    emtrjoriginnode = "BIP01";

    emtrjdynupdatedelay = 0.0;

    emtrjeasevel = 6000.0;

};



instance spellfx_blink_cast(cfx_base_proto) {

    visname_s = "MFX_BLINK_CAST";

    emtrjoriginnode = "BIP01";

    sfxid = "MFX_Fireball_invest2";

    sfxisambient = 1;

    emfxcreate_s = "spellFX_Blink_SCX";

    emfxcreatedowntrj = 1;

};



instance spellfx_blink_scx(cfx_base_proto) {

    visname_s = "screenblend.scx";

    userstring = "1";

    userstring[1] = "0 0 0 150";

    userstring[2] = "0.1";

    userstring[3] = "BLINK_BLEND.TGA";

    visalphablendfunc_s = "ADD";

    emfxlifespan = 0.23;

    emfxcreate_s = "spellFX_Blink_FOV";

};



instance spellfx_blink_fov(cfx_base_proto) {

    visname_s = "morph.fov";

    userstring = "0.75";

    userstring[1] = "0.2";

    userstring[2] = "90";

    userstring[3] = "";

    emfxlifespan = 1.0;

};



instance spellfx_druidtrans_cast(cfx_base_proto) {

    visname_s = "MFX_DRUIDTRANS_CAST";

    emtrjoriginnode = "BIP01";

    sfxid = "MFX_Fireball_invest2";

    sfxisambient = 1;

    emfxcreatedowntrj = 1;

};







instance spellfx_icespell_sendperception_magicarrow(cfx_base_proto) {

    visname_s = "MFX_ICESPELL_TARGET_MAGICARROW";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    emtrjoriginnode = "BIP01 Head";

    emtrjeasevel = 0.0;

    emtrjloopmode_s = "HALT";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.01;

    emtrjtargetrange = 1.2;

    emtrjtargetelev = 89.0;

    emtrjeasevel = 1400.0;

};



instance spellfx_cbow_explosive(cfx_base_proto) {

    visname_s = "MFX_CBOW_EXPLOSIVE";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

};



instance spellfx_likerh_green(cfx_base_proto) {

    visname_s = "MFX_LIKERH_GREEN";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjeasevel = 0.0;

    emtrjloopmode_s = "HALT";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjtargetrange = 1.2;

    emtrjtargetelev = 89.0;

    emtrjeasevel = 1400.0;

};



instance spellfx_likerh_yellow(cfx_base_proto) {

    visname_s = "MFX_LIKERH_YELLOW";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjeasevel = 0.0;

    emtrjloopmode_s = "HALT";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjtargetrange = 1.2;

    emtrjtargetelev = 89.0;

    emtrjeasevel = 1400.0;

};



instance freeaim_trail(cfx_base_proto) {

    emfxlifespan = 1.0;

};



instance freeaim_trail_key_invest_1(c_particlefxemitkey) {

};



instance freeaim_trail_key_invest_2(c_particlefxemitkey) {

    visname_s = "FREEAIM_TRAIL";

};



instance freeaim_trail_key_invest_3(c_particlefxemitkey) {

    visname_s = "";

    pfx_ppsisloopingchg = 1;

};



instance freeaim_destroy(cfx_base_proto) {

    visname_s = "FREEAIM_IMPACT";

    emtrjoriginnode = "BIP01";

    sfxid = "PICKLOCK_BROKEN";

    sfxisambient = 1;

};


instance spellfx_iceexploision(cfx_base_proto) {

    visname_s = "MFX_ICEEXPLOISION_Init";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjtargetnode = "BIP01 FIRE";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emfxcollstat_s = "spellFX_ICEEXPLOISION_SPREAD";
    emfxcolldyn_s = "spellFX_ICEEXPLOISION_SPREAD";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
    emtrjdynupdatedelay = 20000.0;
    emfxinvestorigin_s = "spellFX_ICEEXPLOISION_INVESTSOUND";
};



instance spellfx_iceexploision_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_iceexploision_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_iceexploision_spread(cfx_base_proto) {

    visname_s = "MFX_ICEEXPLOISION_SPREAD_SMALL";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_Icelance_Collide";

    sfxisambient = 1;

};



instance spellfx_iceexploision_spread_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_iceexploision_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_ICEEXPLOISION_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1300.0;

    sfxid = "MFX_Icecube_cast";

    sfxisambient = 1;

    emcheckcollision = 1;

    lightrange = 100.0;

};



instance spellfx_iceexploision_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_iceexploision_collide(cfx_base_proto) {

    visname_s = "MFX_ICEEXPLOISION_Collide3";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Geyser_Rumble";

};
instance spellfx_darksleep(cfx_base_proto) {

    visname_s = "MFX_DARKSLEEP_INIT";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjmode_s = "fixed";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.0;

    emfxcolldyn_s = "SPELLFX_DARKSLEEP_TARGET";

};



instance spellfx_darksleep_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DARKSLEEP_INIT";

};



instance spellfx_darksleep_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DARKSLEEP_ORIGIN";

    emtrjeasevel = 1400.0;

    sfxid = "MFX_Sleep_Cast";

};



instance spellfx_darksleep_origin(cfx_base_proto) {

    visname_s = "MFX_DARKSLEEP_ORIGIN";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjdynupdatedelay = 0.0;

};



instance spellfx_darksleep_target(cfx_base_proto) {

    visname_s = "MFX_DARKSLEEP_TARGET";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    emtrjdynupdatedelay = 0.0;

};
instance spellfx_agro(cfx_base_proto) {

    visname_s = "MFX_AGRO_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_AGRO_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_AGRO_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxcreatedowntrj = 0;

};



instance spellfx_agro_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_agro_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_agro_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_AGRO_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1900.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "MFX_Skull_Fly";

};



instance spellfx_agro_key_collide(c_particlefxemitkey) {

    visname_s = "";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_agro_collidefx(cfx_base_proto) {

    visname_s = "MFX_AGRO_COLLIDE";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    sfxid = "MFX_deathbolt_COLLIDE";

};



instance spellfx_dot_first(cfx_base_proto) {

    visname_s = "MFX_DOT_FIRST_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_DOT_FIRST_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_DOT_FIRST_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxcreatedowntrj = 0;

};



instance spellfx_dot_first_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_dot_first_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_dot_first_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DOT_FIRST_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1800.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "MFX_SKULL_Fly";

};



instance spellfx_dot_first_key_collide(c_particlefxemitkey) {

    visname_s = "";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_dot_first_collidefx(cfx_base_proto) {

    visname_s = "MFX_DOT_FIRST_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    sfxid = "MFX_SKULL_Collide";

};

instance spellfx_imarah_red(cfx_base_proto) {

    visname_s = "MFX_IMARAH_RED";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    emtrjoriginnode = "BIP01 Head";

    emtrjeasevel = 0.0;

    emtrjloopmode_s = "HALT";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjtargetrange = 1.2;

    emtrjtargetelev = 89.0;

    emtrjeasevel = 1400.0;

};



instance spellfx_imarah_green(cfx_base_proto) {

    visname_s = "MFX_IMARAH_GREEN";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    emtrjoriginnode = "BIP01 Head";

    emtrjeasevel = 0.0;

    emtrjloopmode_s = "HALT";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjtargetrange = 1.2;

    emtrjtargetelev = 89.0;

    emtrjeasevel = 1400.0;

};



instance spellfx_specialattack_07(cfx_base_proto) {

    visname_s = "MFX_SPECIALATTACK_07";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    emtrjeasevel = 0.0;

    emtrjloopmode_s = "HALT";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjtargetrange = 1.2;

    emtrjtargetelev = 89.0;

    emtrjeasevel = 1400.0;

};



instance spellfx_imarah_firebolt(cfx_base_proto) {

    visname_s = "MFX_IMARAH_FIREBOLT_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_IMARAH_Firebolt_COLLIDEFX";

    emfxcolldyn_s = "spellFX_IMARAH_Firebolt_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    userstring = "fireballquadmark.tga";

    userstring[1] = "40 40";

    userstring[2] = "MUL";

};



instance spellfx_imarah_firebolt_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_imarah_firebolt_key_init(c_particlefxemitkey) {

    visname_s = "MFX_IMARAH_Firebolt_INIT";

    lightrange = 0.001;

};



instance spellfx_imarah_firebolt_key_cast(c_particlefxemitkey) {

    visname_s = "mfx_IMARAH_firebolt_cast";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "Torch_Enlight";

    lightrange = 100.0;

    emcheckcollision = 1;

};



instance spellfx_imarah_firebolt_key_collide(c_particlefxemitkey) {

    visname_s = "";

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    sfxid = "TORCH_ENLIGHT";

};



instance spellfx_imarah_firebolt_collidefx(cfx_base_proto) {

    visname_s = "MFX_IMARAH_Firebolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

};



instance spellfx_imarah_firebolt_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_IMARAH_Firebolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

};



instance spellfx_specialattack02_cloud(cfx_base_proto) {

    visname_s = "MFX_SPECIALATTACK02_CLOUD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    emtrjdynupdatedelay = 0.01;

};



instance spellfx_specialattack02_electrowave(cfx_base_proto) {

    visname_s = "MFX_SPECIALATTACK02_ELECTROWAVE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_specialattack02_electrowave_key_init(c_particlefxemitkey) {

    visname_s = "MFX_SPECIALATTACK02_ELECTROWAVE_INIT";

};



instance spellfx_specialattack02_electrowave_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_SPECIALATTACK02_ELECTROWAVE_RIGHTHAND";

    emcreatefxid = "SPELLFX_SPECIALATTACK02_ELECTROWAVE_LEFTHAND";

};



instance spellfx_specialattack02_electrowave_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_SPECIALATTACK02_ELECTROWAVE_EXPLOSION";

    emtrjeasevel = 2000.0;

    pfx_ppsisloopingchg = 1;

};



instance spellfx_specialattack02_electrowave_explosion(cfx_base_proto) {

    visname_s = "MFX_SPECIALATTACK02_ELECTROWAVE_EXPLOSION";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "Bip01 L Hand";

    emfxcreate_s = "SPELLFX_SPECIALATTACK02_ELECTROWAVE_GROUND";

};



instance spellfx_specialattack02_electrowave_ground(cfx_base_proto) {

    visname_s = "MFX_SPECIALATTACK02_ELECTROWAVE_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "SPELLFX_SPECIALATTACK02_ELECTROWAVE_COLLIDEDYNFX";

    emfxcolldynalign_s = "COLLISIONNORMAL";

    emcheckcollision = 1;

    lightpresetname = "REDAMBIENCE";

    sfxid = "MFX_SPECIALATTACK02_ELECTROWAVE_CAST";

    sfxisambient = 1;

};



instance spellfx_specialattack02_electrowave_lefthand(cfx_base_proto) {

    visname_s = "MFX_SPECIALATTACK02_ELECTROWAVE_LEFTHAND";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "Bip01 L Hand";

    emfxcreate_s = "FX_EARTHQUAKE";

};



instance spellfx_specialattack02_electrowave_sub(cfx_base_proto) {

    visname_s = "";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01 HEAD";

};



instance spellfx_specialattack02_electrowave_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_SPECIALATTACK02_ELECTROWAVE_TARGET";

    emtrjoriginnode = "BIP01";

    emfxcreatedowntrj = 1;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Lightning_ORIGIN";

};
instance spellfx_ud_deathball(cfx_base_proto) {

    visname_s = "MFX_UD_DEATHBALL_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldynperc_s = "spellFX_UD_DEATHBALL_SENDPERCEPTION";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_ud_deathball_key_init(c_particlefxemitkey) {

    lightrange = 0.0;

};



instance spellfx_ud_deathball_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_UD_DEATHBALL_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1200.0;

    lightrange = 0.0;

    emcheckcollision = 1;

    sfxid = "MFX_SuckEnergy_Cast";

};



instance spellfx_ud_deathball_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

    pfx_ppsisloopingchg = 1;

};



instance spellfx_ud_deathball_invest(cfx_base_proto) {

    visname_s = "MFX_UD_DEATHBALL_INVEST";

    emtrjmode_s = "FIXED";

};



instance spellfx_ud_deathball_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;

    emfxlifespan = 30.0;

    visname_s = "morph.fov";

    userstring = "0.8";

    userstring[1] = "1.0";

    userstring[2] = "120";

    userstring[3] = "90";

};



instance spellfx_ud_deathball_bloodfly(cfx_base_proto) {

    visname_s = "MFX_UD_DEATHBALL_FLYTOPLAYER";

    emtrjeasevel = 0.01;

    emtrjmode_s = "TARGET LINE";

    emtrjoriginnode = "Bip01 Spine2";

    emtrjtargetnode = "ZS_RIGHTHAND";

    emtrjdynupdatedelay = 0.01;

};



instance spellfx_ud_deathball_sendperception(cfx_base_proto) {

    visname_s = "MFX_UD_DEATHBALL_TARGET";

    sendassessmagic = 1;

    sfxid = "MFX_SuckEnergy_Target";

};
instance spellfx_beliarrune(cfx_base_proto) {

    visname_s = "MFX_Energyball_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_BELIARRUNE_SPREAD";

    emfxcolldyn_s = "SPELLFX_BELIARRUNE_SPREAD";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_beliarrune_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_beliarrune_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_beliarrune_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_ENERGYBALL_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1200.0;

    sfxid = "MFX_SuckEnergy_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_beliarrune_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_beliarrune_spread(cfx_base_proto) {

    visname_s = "MFX_ENERGYBALL_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_SuckEnergy_Target";

};



instance spellfx_beliarrune_spread_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_beliarrune_spread_key_collide(c_particlefxemitkey) {

};



instance spellfx_crestofelements(cfx_base_proto) {

    visname_s = "MFX_MasterOfDisaster_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_CRESTOFELEMENTS_COLLIDE";

    emfxcolldyn_s = "spellFX_CRESTOFELEMENTS_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_crestofelements_key_init(c_particlefxemitkey) {

};



instance spellfx_crestofelements_key_cast(c_particlefxemitkey) {

    emtrjmode_s = "TARGET";

    emtrjeasevel = 2500.0;

    sfxid = "MFX_DestroyUndead_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_crestofelements_trail(cfx_base_proto) {

    emtrjeasevel = 800.0;

    visname_s = "MFX_MasterOfDisaster_TRAIL";

    visalpha = 1.0;

    emtrjmode_s = "TARGET";

    emcheckcollision = 1;

    emactioncollstat_s = "COLLIDE";

    emactioncolldyn_s = "COLLIDE";

};



instance spellfx_crestofelements_trail_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_crestofelements_collide(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_MasterOfDisaster_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_crestofelements_collidedynfx(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_MasterOfDisaster_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_druidrunequest(cfx_base_proto) {

    visname_s = "MFX_MasterOfDisaster_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_DRUIDRUNEQUEST_COLLIDE";

    emfxcolldyn_s = "spellFX_DRUIDRUNEQUEST_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_druidrunequest_key_init(c_particlefxemitkey) {

};



instance spellfx_druidrunequest_key_cast(c_particlefxemitkey) {

    emtrjmode_s = "TARGET";

    emtrjeasevel = 2500.0;

    sfxid = "MFX_DestroyUndead_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_druidrunequest_trail(cfx_base_proto) {

    emtrjeasevel = 800.0;

    visname_s = "MFX_MasterOfDisaster_TRAIL";

    visalpha = 1.0;

    emtrjmode_s = "TARGET";

    emcheckcollision = 1;

    emactioncollstat_s = "COLLIDE";

    emactioncolldyn_s = "COLLIDE";

};



instance spellfx_druidrunequest_trail_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_druidrunequest_collide(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_MasterOfDisaster_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_druidrunequest_collidedynfx(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_MasterOfDisaster_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_electrowave(cfx_base_proto) {

    visname_s = "MFX_ELECTROWAVE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_ELECTROWAVE_SPREAD";

    emfxcolldyn_s = "SPELLFX_ELECTROWAVE_SPREAD";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_electrowave_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_electrowave_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_electrowave_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_ELECTROWAVE_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1200.0;

    sfxid = "MFX_ELECTROWAVE_CAST";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_electrowave_spread(cfx_base_proto) {

    visname_s = "MFX_ELECTROWAVE_SPREAD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "SPELLFX_ELECTROWAVE_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_Lightning_ORIGIN";

};



instance spellfx_electrowave_spread_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_electrowave_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0 0";

    emtrjeasevel = 1.0E-6;

};
instance spellfx_bigdarkball(cfx_base_proto) {

    visname_s = "MFX_BIGDARKBALL_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_BIGDARKBALL_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_BIGDARKBALL_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxcreatedowntrj = 0;

};



instance spellfx_bigdarkball_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_bigdarkball_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_bigdarkball_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_BIGDARKBALL_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "MFX_Fireball_Cast";

};



instance spellfx_bigdarkball_key_collide(c_particlefxemitkey) {

    visname_s = "";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_bigdarkball_collidefx(cfx_base_proto) {

    visname_s = "MFX_BIGDARKBALL_COLLIDE";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    sfxid = "MFX_SKULL_Collide";

};



instance spellfx_darkball(cfx_base_proto) {

    visname_s = "MFX_DARKBALL_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_DARKBALL_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_DARKBALL_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxcreatedowntrj = 0;

};



instance spellfx_darkball_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_darkball_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_darkball_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DARKBALL_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "MFX_Fireball_Cast";

};



instance spellfx_darkball_key_collide(c_particlefxemitkey) {

    visname_s = "";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_darkball_collidefx(cfx_base_proto) {

    visname_s = "MFX_DARKBALL_COLLIDE";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    sfxid = "MFX_SKULL_Collide";

};



instance spellfx_darkcontrol(cfx_base_proto) {

    visname_s = "MFX_DARKCONTROL_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_DARKCONTROL_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_DARKCONTROL_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxcreatedowntrj = 0;

};



instance spellfx_darkcontrol_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_darkcontrol_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_darkcontrol_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DARKCONTROL_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1800.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "MFX_SKULL_Fly";

};



instance spellfx_darkcontrol_key_collide(c_particlefxemitkey) {

    visname_s = "";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_darkcontrol_collidefx(cfx_base_proto) {

    visname_s = "MFX_DARKCONTROL_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    sfxid = "MFX_SKULL_Collide";

};



instance spellfx_darkspear(cfx_base_proto) {

    visname_s = "MFX_DARKSPEAR_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_DARKSPEAR_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_DARKSPEAR_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxcreatedowntrj = 0;

};



instance spellfx_darkspear_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_darkspear_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_darkspear_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DARKSPEAR_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1600.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "MFX_Skull_Cast";

};



instance spellfx_darkspear_key_collide(c_particlefxemitkey) {

    visname_s = "";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_darkspear_collidefx(cfx_base_proto) {

    visname_s = "MFX_DARKSPEAR_COLLIDE";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    sfxid = "MFX_SKULL_Collide";

};



instance spellfx_torture(cfx_base_proto) {

    visname_s = "MFX_TORTURE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcolldyn_s = "SPELLFX_TORTURE_TARGET";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

};



instance spellfx_torture_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_torture_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_TORTURE_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "MFX_Skull_Fly";

    lightrange = 100.0;

    emcheckcollision = 1;

};



instance spellfx_torture_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_torture_key_back(c_particlefxemitkey) {

    visname_s = "";

    emtrjmode_s = "FIXED";

};



instance spellfx_torture_target(cfx_base_proto) {

    visname_s = "MFX_TORTURE_TARGET";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

    sendassessmagic = 1;

    sfxid = "MFX_Skull_Collide";

    sfxisambient = 1;

};



instance spellfx_darkwave(cfx_base_proto) {

    visname_s = "MFX_DARKWAVE_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetrange = 20.0;

    emtrjangleelevvar = 0.0;

    emtrjangleheadvar = 0.0;

    emtrjeasefunc_s = "LINEAR";

    emtrjeasevel = 100.0;

    emtrjdynupdatedelay = 20000.0;

    emfxcreatedowntrj = 1;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

};



instance spellfx_darkwave_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_darkwave_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_DARKWAVE_Skull";

    pfx_ppsisloopingchg = 1;

    sfxid = "MFX_Skull_Cast";

    sfxisambient = 1;

};



instance spellfx_darkwave_skull(cfx_base_proto) {

    visname_s = "MFX_DARKWAVE_CAST";

    emtrjmode_s = "TARGET SPLINE RANDOM";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjnumkeysvar = 1;

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 0.1;

    emtrjdynupdatetargetonly = 1;

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_DARKWAVE_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_DARKWAVE_SPREAD";

    emfxlifespan = -1.0;

    secsperdamage = -1.0;

    emtrjeasevel = 1100.0;

};



instance spellfx_darkwave_skull_key_cast(c_particlefxemitkey) {

    emcheckcollision = 1;

    sfxid = "MFX_Skull_Fly";

};



instance spellfx_darkwave_spread(cfx_base_proto) {

    visname_s = "MFX_DARKWAVE_SPREAD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "SPELLFX_DARKWAVE_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_FIrestorm_Collide";

    sfxisambient = 1;

};



instance spellfx_darkwave_collidefx(cfx_base_proto) {

    visname_s = "MFX_DARKWAVE_COLLIDE";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Skull_Collide";

};



instance spellfx_dot_second(cfx_base_proto) {

    visname_s = "MFX_DOT_SECOND_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_DOT_SECOND_COLLIDE";

    emfxcolldyn_s = "SPELLFX_DOT_SECOND_COLLIDEDYNFX";

    emfxcollstatalign_s = "COLLISIONNORMAL";

    emfxcreatedowntrj = 0;

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_dot_second_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_dot_second_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DOT_SECOND_INIT";

    lightrange = 0.01;

};



instance spellfx_dot_second_key_cast(c_particlefxemitkey) {

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1800.0;

    visname_s = "MFX_DOT_SECOND_CAST";

    sfxid = "MFX_Skull_Fly";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_dot_second_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_dot_second_firecloud(cfx_base_proto) {

    emtrjeasevel = 1400.0;

    visname_s = "MFX_IFB_CAST";

    visalpha = 1.0;

    emtrjmode_s = "TARGET";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 2;

    emactioncolldyn_s = "COLLIDE";

    emactioncollstat_s = "COLLIDE";

};



instance spellfx_dot_second_firecloud_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;

};



instance spellfx_dot_second_collide(cfx_base_proto) {

    visname_s = "MFX_DOT_SECOND_COLLIDE";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "BIP01";

};



instance spellfx_dot_second_collide_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DOT_SECOND_COLLIDE";

    sfxid = "MFX_deathbolt_COLLIDE";

};



instance spellfx_dot_second_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_DOT_SECOND_COLLIDE";

    visalpha = 1.0;

    emtrjoriginnode = "BIP01";

    emtrjmode_s = "FIXED";

};



instance spellfx_dot_second_collidedynfx_key_invest_1(c_particlefxemitkey) {

    visname_s = "DOT_SECOND_COLLIDE";

    sfxid = "MFX_deathbolt_COLLIDE";

};



instance spellfx_dark_invis(cfx_base_proto) {

    visname_s = "MFX_DARK_INVIS_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_dark_invis_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DARK_INVIS_INIT";

};



instance spellfx_dark_invis_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DARK_INVIS_RIGHTHAND";

};



instance spellfx_dark_invis_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_DARK_INVIS_GROUND";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_dark_invis_ground(cfx_base_proto) {

    visname_s = "MFX_DARK_INVIS_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Firestorm_Cast";

    sfxisambient = 1;

};



instance spellfx_massagro(cfx_base_proto) {

    visname_s = "MFX_MASSAGRO_Init";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_MASSAGRO_SPREAD";

    emfxcolldyn_s = "SPELLFX_MASSAGRO_SPREAD";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_massagro_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_massagro_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_massagro_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_MASSAGRO_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1400.0;

    sfxid = "MFX_Skull_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

    lightrange = 100.0;

};



instance spellfx_massagro_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_massagro_spread(cfx_base_proto) {

    visname_s = "MFX_MASSAGRO_SPREAD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    emfxcreate_s = "SPELLFX_MASSAGRO_COLLIDE";

    sfxid = "MFX_SKULL_Collide";

    sfxisambient = 1;

};



instance spellfx_massagro_spread_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_massagro_spread_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_massagro_collide(cfx_base_proto) {

    visname_s = "MFX_MASSAGRO_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_SKULL_Collide";

};



instance spellfx_massdot(cfx_base_proto) {

    visname_s = "MFX_MASSDOT_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetrange = 20.0;

    emtrjangleelevvar = 0.0;

    emtrjangleheadvar = 0.0;

    emtrjeasefunc_s = "LINEAR";

    emtrjeasevel = 100.0;

    emtrjdynupdatedelay = 20000.0;

    emfxcreatedowntrj = 1;

    emfxlifespan = -1.0;

    emselfrotvel_s = "0 0 0";

    secsperdamage = -1.0;

};



instance spellfx_massdot_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_massdot_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_MASSDOT_Skull";

    pfx_ppsisloopingchg = 1;

    sfxid = "MFX_Skull_Cast";

    sfxisambient = 1;

};



instance spellfx_massdot_skull(cfx_base_proto) {

    visname_s = "MFX_MASSDOT_CAST";

    emtrjmode_s = "TARGET SPLINE";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjeasefunc_s = "LINEAR";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_MASSDOT_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_MASSDOT_SPREAD";

    emfxlifespan = -1.0;

    secsperdamage = -1.0;

    emtrjeasevel = 1200.0;

};



instance spellfx_massdot_skull_key_cast(c_particlefxemitkey) {

    emcheckcollision = 1;

    sfxid = "MFX_Skull_Fly";

};



instance spellfx_massdot_spread(cfx_base_proto) {

    visname_s = "MFX_MASSDOT_SPREAD";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emfxcolldyn_s = "SPELLFX_MASSDOT_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_FIrestorm_Collide";

    sfxisambient = 1;

};



instance spellfx_massdot_collidefx(cfx_base_proto) {

    visname_s = "MFX_MASSDOT_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_Skull_Collide";

};



instance spellfx_darkrune_absorb(cfx_base_proto) {

    visname_s = "MFX_ABSORB_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_darkrune_absorb_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_ABSORB_CAST";

    emcreatefxid = "SPELLFX_DARKRUNE_ABSORB_LEFTHAND";

};



instance spellfx_darkrune_absorb_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    sfxid = "MFX_HEAL_CAST";

    sfxisambient = 1;

};



instance spellfx_darkrune_absorb_origin(cfx_base_proto) {

    visname_s = "MFX_ABSORB_HEAVENLIGHT";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_HEAL_CAST";

    sfxisambient = 1;

};



instance spellfx_darkrune_absorb_lefthand(cfx_base_proto) {

    visname_s = "MFX_ABSORB_CAST";

    emtrjoriginnode = "ZS_LEFTHAND";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "AURA";

};



instance spellfx_darkrune_absorb_lefthand_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_darkrune_absorb_lefthand_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_darkrune_defense(cfx_base_proto) {

    visname_s = "MFX_DK_DEFENSE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_darkrune_defense_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DK_DEFENSE_INIT";

};



instance spellfx_darkrune_defense_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DK_DEFENSE_RIGHTHAND";

};



instance spellfx_darkrune_defense_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_DARKRUNE_DEFENSE_GROUND";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_darkrune_defense_ground(cfx_base_proto) {

    visname_s = "MFX_DK_DEFENSE_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Firestorm_Cast";

    sfxisambient = 1;

};



instance spellfx_darkrune_edefense(cfx_base_proto) {

    visname_s = "MFX_DK_EDEFENSE_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_darkrune_edefense_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DK_EDEFENSE_INIT";

};



instance spellfx_darkrune_edefense_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DK_EDEFENSE_RIGHTHAND";

};



instance spellfx_darkrune_edefense_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_DARKRUNE_EDEFENSE_GROUND";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_darkrune_edefense_ground(cfx_base_proto) {

    visname_s = "MFX_DK_EDEFENSE_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Firestorm_Cast";

    sfxisambient = 1;

};



instance spellfx_darkrune_healpet(cfx_base_proto) {

    visname_s = "MFX_DARKHEAL_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_darkrune_healpet_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DARKHEAL_CAST";

    emcreatefxid = "SPELLFX_DARKRUNE_HEALPET_LEFTHAND";

};



instance spellfx_darkrune_healpet_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

};



instance spellfx_darkrune_healpet_origin(cfx_base_proto) {

    visname_s = "MFX_DARKHEAL_HEAVENLIGHT";

    emtrjoriginnode = "BIP01";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "MFX_HEAL_CAST";

    sfxisambient = 1;

};



instance spellfx_darkrune_healpet_lefthand(cfx_base_proto) {

    visname_s = "MFX_DARKHEAL_CAST";

    emtrjoriginnode = "ZS_LEFTHAND";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "AURA";

};



instance spellfx_darkrune_healpet_lefthand_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_darkrune_healpet_lefthand_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_darkrune_illness(cfx_base_proto) {

    visname_s = "MFX_DK_ILLNESS_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_darkrune_illness_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DK_ILLNESS_INIT";

};



instance spellfx_darkrune_illness_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DK_ILLNESS_RIGHTHAND";

};



instance spellfx_darkrune_illness_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_DARKRUNE_ILLNESS_GROUND";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_darkrune_illness_ground(cfx_base_proto) {

    visname_s = "MFX_DK_ILLNESS_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Firestorm_Cast";

    sfxisambient = 1;

};



instance spellfx_darkrune_lord(cfx_base_proto) {

    visname_s = "MFX_DK_LORD_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_darkrune_lord_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DK_LORD_INIT";

};



instance spellfx_darkrune_lord_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DK_LORD_RIGHTHAND";

};



instance spellfx_darkrune_lord_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_DARKRUNE_LORD_GROUND";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_darkrune_lord_ground(cfx_base_proto) {

    visname_s = "MFX_DK_LORD_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Firestorm_Cast";

    sfxisambient = 1;

};



instance spellfx_darkstatsup(cfx_base_proto) {

    visname_s = "MFX_DARKSTATSUP_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

};



instance spellfx_darkstatsup_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DARKSTATSUP_CAST";

    emcreatefxid = "SPELLFX_DARKSTATSUP_LEFTHAND";

};



instance spellfx_darkstatsup_key_cast(c_particlefxemitkey) {

    pfx_ppsisloopingchg = 1;

    sfxid = "MFX_HEAL_CAST";

};



instance spellfx_darkstatsup_lefthand(cfx_base_proto) {

    visname_s = "MFX_DARKSTATSUP_CAST";

    emtrjoriginnode = "ZS_LEFTHAND";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    lightpresetname = "AURA";

};



instance spellfx_darkstatsup_lefthand_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_darkstatsup_lefthand_key_cast(c_particlefxemitkey) {

    lightrange = 150.0;

};



instance spellfx_darkrune_steal(cfx_base_proto) {

    visname_s = "MFX_DK_STEALHEALTH_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emfxcreatedowntrj = 0;

};



instance spellfx_darkrune_steal_key_init(c_particlefxemitkey) {

    visname_s = "MFX_DK_STEALHEALTH_INIT";

};



instance spellfx_darkrune_steal_key_invest_1(c_particlefxemitkey) {

    visname_s = "MFX_DK_STEALHEALTH_RIGHTHAND";

};



instance spellfx_darkrune_steal_key_cast(c_particlefxemitkey) {

    emcreatefxid = "SPELLFX_DARKRUNE_STEAL_GROUND";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_darkrune_steal_ground(cfx_base_proto) {

    visname_s = "MFX_DK_STEALHEALTH_CAST";

    emtrjoriginnode = "BIP01 R Foot";

    emactioncolldyn_s = "CREATEONCE";

    lightpresetname = "CATACLYSM";

    sfxid = "MFX_Firestorm_Cast";

    sfxisambient = 1;

};



instance spellfx_darkpetsummon(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_darkpetsummon_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_darkpetsummon_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_darkpetsummon_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

};



instance spellfx_darkpetsummon_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};


instance spellfx_roots(cfx_base_proto) {

    visname_s = "MFX_ROOTS_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_ROOTS_COLLIDEFX";

    emfxcolldyn_s = "SPELLFX_ROOTS_COLLIDEFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emfxcreatedowntrj = 0;

    lightpresetname = "AURA";

};



instance spellfx_roots_key_open(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_roots_key_init(c_particlefxemitkey) {

    lightrange = 0.001;

};



instance spellfx_roots_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_ROOTS_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 700.0;

    lightrange = 100.0;

    emcheckcollision = 1;

    sfxid = "MFX_Swarm_Cast";

};



instance spellfx_roots_key_collide(c_particlefxemitkey) {

    visname_s = "";

    emtrjeasevel = 1.0E-6;

};



instance spellfx_roots_collidefx(cfx_base_proto) {

    visname_s = "MFX_ROOTS_Target";

    visalpha = 1.0;

    emtrjmode_s = "FOLLOW TARGET";

    sfxid = "MFX_Greententacle_Grow";

};

instance spellfx_windfury(cfx_base_proto) {

    visname_s = "MFX_WINDFURY_HIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "CREATE CREATEQUAD";

    emactioncolldyn_s = "CREATEONCE";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

    emcheckcollision = 1;

    sfxid = "MFX_WINDFURY_HIT_SOUND";

    sfxisambient = 1;

};



instance spellfx_sumjina(cfx_base_proto) {

    visname_s = "MFX_ArmyOfDarkness_INIT";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    lightpresetname = "REDAMBIENCE";

};



instance spellfx_sumjina_key_open(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_sumjina_key_init(c_particlefxemitkey) {

    lightrange = 0.01;

};



instance spellfx_sumjina_key_invest_1(c_particlefxemitkey) {

    lightrange = 200.0;

};



instance spellfx_sumjina_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SummonCreature_ORIGIN";

    pfx_ppsisloopingchg = 1;

};



instance spellfx_tpllightstrike(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "SPELLFX_TPLLIGHTSTRIKE_COLLIDE";

    emfxcolldyn_s = "SPELLFX_TPLLIGHTSTRIKE_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_tpllightstrike_key_init(c_particlefxemitkey) {

    visname_s = "MFX_PalHolyBolt_INIT";

    scaleduration = 0.5;

};



instance spellfx_tpllightstrike_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_PalHolyBolt_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1500.0;

    sfxid = "MFX_Thunderbolt_Cast";

    emcheckcollision = 1;

};



instance spellfx_tpllightstrike_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    emcheckcollision = 0;

};



instance spellfx_tpllightstrike_collide(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

};



instance spellfx_tpllightstrike_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_Collide";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

};



instance spellfx_tplmediumstrike(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_INIT_RED";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_TPLMEDIUMSTRIKE_COLLIDE";

    emfxcolldyn_s = "spellFX_TPLMEDIUMSTRIKE_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_tplmediumstrike_key_init(c_particlefxemitkey) {

    visname_s = "MFX_PalHolyBolt_INIT_RED";

    scaleduration = 0.5;

};



instance spellfx_tplmediumstrike_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_PalHolyBolt_CAST_RED";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1500.0;

    sfxid = "MFX_Thunderbolt_Cast";

    emcheckcollision = 1;

};



instance spellfx_tplmediumstrike_key_collide(c_particlefxemitkey) {

    pfx_flygravity_s = "0 0.0002 0";

    emtrjeasevel = 1.0E-6;

    emcheckcollision = 0;

};



instance spellfx_tplmediumstrike_collide(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_Collide_RED";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

};



instance spellfx_tplmediumstrike_collidedynfx(cfx_base_proto) {

    visname_s = "MFX_PalHolyBolt_Collide_RED";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "Torch_Enlight";

};



instance spellfx_tplheavystrike(cfx_base_proto) {

    visname_s = "MFX_DestroyUndead_INIT";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_TplHeavyStrike_COLLIDE";

    emfxcolldyn_s = "spellFX_TplHeavyStrike_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_tplheavystrike_key_init(c_particlefxemitkey) {

};



instance spellfx_tplheavystrike_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DestroyUndead_CAST";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1500.0;

    sfxid = "MFX_DestroyUndead_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_tplheavystrike_collide(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_DESTROYUNDEAD_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    lightpresetname = "AURA";

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_tplheavystrike_collidedynfx(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_DESTROYUNDEAD_COLLIDE";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    lightpresetname = "AURA";

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_tplsuperstrike(cfx_base_proto) {

    visname_s = "MFX_MasterOfDisaster_INIT_RED";

    emtrjmode_s = "FIXED";

    emtrjoriginnode = "ZS_RIGHTHAND";

    emtrjtargetnode = "BIP01 FIRE";

    emtrjloopmode_s = "NONE";

    emtrjeasefunc_s = "LINEAR";

    emactioncollstat_s = "COLLIDE CREATE";

    emactioncolldyn_s = "COLLIDE CREATEONCE";

    emfxcollstat_s = "spellFX_TplSuperStrike_COLLIDE";

    emfxcolldyn_s = "spellFX_TTplSuperStrike_COLLIDEDYNFX";

    emtrjtargetrange = 20.0;

    emtrjtargetelev = 0.0;

    emtrjdynupdatedelay = 20000.0;

};



instance spellfx_tplsuperstrike_key_init(c_particlefxemitkey) {

};



instance spellfx_tplsuperstrike_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_DestroyUndead_CAST_RED";

    emtrjmode_s = "TARGET";

    emtrjeasevel = 1500.0;

    sfxid = "MFX_DestroyUndead_Cast";

    sfxisambient = 1;

    emcheckcollision = 1;

};



instance spellfx_tplsuperstrike_collide(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_DESTROYUNDEAD_COLLIDE_RED";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    lightpresetname = "AURA";

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};



instance spellfx_tplsuperstrike_collidedynfx(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_DESTROYUNDEAD_COLLIDE_RED";

    emtrjmode_s = "FIXED";

    emtrjdynupdatedelay = 0.0;

    lightpresetname = "AURA";

    sfxid = "MFX_DESTROYUNDEAD_COLLIDE";

    sfxisambient = 1;

};