


/*
SPELLFX_SPELLARCANEBALL3
SPELLFX_SPELLARCANEBALL2
SPELLFX_SPELLARCANEBALL1
SPELLFX_SPELLARCANEBALL

SPELLFX_SPELLWATERSTORM3
SPELLFX_SPELLWATERSTORM2
SPELLFX_SPELLWATERSTORM1
SPELLFX_SPELLWATERSTORM

spellfx_SPELLWATERLANCE3
spellfx_SPELLWATERLANCE2
spellfx_SPELLWATERLANCE1
spellfx_SPELLWATERLANCE

VOB_SPELLWATERBOLT3
VOB_SPELLWATERBOLT2
VOB_SPELLWATERBOLT1
VOB_SPELLWATERBOLT

SPELLFX_SPELLICEBOLT3
SPELLFX_SPELLICEBOLT2
SPELLFX_SPELLICEBOLT1
SPELLFX_SPELLICEBOLT

spellfx_SPELLICEBALL3
spellfx_SPELLICEBALL2
spellfx_SPELLICEBALL1
spellfx_SPELLICEBALL


// ogien

SPELLFX_FIRESPELLFIST3
SPELLFX_FIRESPELLFIST2
SPELLFX_FIRESPELLFIST1
SPELLFX_FIRESPELLFIST

spellfx_FIRESPELLBURNINGDREI
spellfx_FIRESPELLBURNINGZWEI
spellfx_FIRESPELLBURNINGEIN
spellfx_FIRESPELLBURNING

spellfx_MASIVEFIREBURN
spellfx_LARGEFIREBURN
spellfx_MEDIUMFIREBURN
spellfx_FIREBURN

SPELLFX_MEDIUMFIREBALL
SPELLFX_FIRELARGEBOLT
SPELLFX_FIREBOLTSPELL
SPELLFX_FIREARROWSPELL

SPELLFX_FIREBOMB
SPELLFX_FIRESHADES
SPELLFX_FIRESHADOW
SPELLFX_LARGEFB

SPELLFX_ICEGOLEMCUBE
SPELLFX_BLOODFLY
spellfx_MINECRAWLER
SPELLFX_FIREGOLEM
SPELLFX_INSTANTFIREGOLEM
SPELLFX_FIREGOLEMSTORM
SPELLFX_FIREWARANSTORM
SPELLFX_GOLEMDEATH
SPELLFX_ICEGOLEMLANCE
SPELLFX_ICEGOLEMBOLT


*/





instance SPELLFX_KORONA(CFX_BASE_PROTO)
{
	visname_s = "PFX_KORONA";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 2e+006;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
	emadjustshptoorigin = 1;
};
instance SPELLFX_DRAGON_FIREBALL_01(CFX_BASE_PROTO)
{
	visname_s = "PFX_DRAGON_FIREBALL_01";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "FIXED";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 2e+006;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
	emadjustshptoorigin = 1;
};



instance spellfx_GREEN(CFX_BASE_PROTO)
{
	visname_s = "FIRE_MODEL_GREEN";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "=";
	emtrjtargetrange = 10;
	emtrjnumkeys = 10;
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 2e+006;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	lightpresetname = "GREENSMALL";
	secsperdamage = -1;
	emadjustshptoorigin = 1;
//	emfxcreate_s = "SPELLFX_GREEN_SMOKE1";
};

instance SPELLFX_GREEN_KEY_CAST1(C_PARTICLEFXEMITKEY)
{
	lightrange = 500;
};

instance SPELLFX_GREEN_SMOKE1(CFX_BASE_PROTO)
{
	visname_s = "SMOKE_MODEL_GREEN";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "=";
	emtrjtargetrange = 10;
	emtrjnumkeys = 10;
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 2e+006;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	lightpresetname = "GREENSMALL";
	secsperdamage = -1;
	emadjustshptoorigin = 1;
};
















instance SPELLFX_MAGIC_SHIELD(CFX_BASE_PROTO)
{
	visname_s = "MFX_MAGIC_SHIELD_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emfxcreate_s = "spellFX_MAGIC_SHIELD_ACTIVE";
	emfxcreatedowntrj = 1;
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_MAGIC_SHIELD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_MAGIC_SHIELD_ACTIVE(CFX_BASE_PROTO)
{
	visname_s = "";
	visalpha = 1;
	emtrjmode_s = "FOLLOW TARGET";
	emtrjeasevel = 0;
	emtrjoriginnode = "BIP01";
	emtrjloopmode_s = "HALT";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 0.2;//0.4
	emtrjtargetrange = 0.1;//1.2
	emtrjtargetelev = 1;//89
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_MAGIC_SHIELD_ACTIVE_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_MAGIC_SHIELD_ACTIVE_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_MAGIC_SHIELD_ACTIVE_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_MAGIC_SHIELD"; //MFX_MAGIC_SHIELD_ORIGIN
	lightrange = 400;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
	emtrjeasevel = 1400;//1400
};
















instance SPELLFX_SPELLARCANEBALL3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL3_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_SPELLARCANEBALL3_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL3_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLARCANEBALL3_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL3_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_SPELLARCANEBALL3_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_SPELLARCANEBALL3_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL3_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL3_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL3_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL3_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL3_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 1500;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_SPELLARCANEBALL3_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_SPELLARCANEBALL3_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_SPELLARCANEBALL3";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance VOB_SPELLARCANEBALL3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALLA_COLLIDE";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLARCANEBALL3_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_SPELLARCANEBALL3_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLARCANEBALL2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL2_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_SPELLARCANEBALL2_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL2_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLARCANEBALL2_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL2_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_SPELLARCANEBALL2_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_SPELLARCANEBALL2_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL2_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL2_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL2_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL2_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL2_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 1200;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_SPELLARCANEBALL2_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_SPELLARCANEBALL2_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_SPELLARCANEBALL2";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance VOB_SPELLARCANEBALL2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALLA3_COLLIDE4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLARCANEBALL2_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_SPELLARCANEBALL2_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLARCANEBALL1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL1_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_SPELLARCANEBALL1_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL1_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLARCANEBALL1_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL1_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_SPELLARCANEBALL1_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_SPELLARCANEBALL1_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL1_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL1_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL1_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL1_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL1_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 1050;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_SPELLARCANEBALL1_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_SPELLARCANEBALL1_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_SPELLARCANEBALL1";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance VOB_SPELLARCANEBALL1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL_COLLIDE4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLARCANEBALL1_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_SPELLARCANEBALL1_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLARCANEBALL(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_SPELLARCANEBALL_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLARCANEBALL_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLARCANEBALL_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_SPELLARCANEBALL_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_SPELLARCANEBALL_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLARCANEBALL_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLARCANEBALL_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 900;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_SPELLARCANEBALL_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_SPELLARCANEBALL_COLLIDEDYNFX";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};



instance SPELLFX_SPELLARCANEBALL_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_SPELLARCANEBALL_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLWATERSTORM3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM3_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLWATERSTORM3_SPREAD";
	emfxcolldyn_s = "spellFX_SPELLWATERSTORM3_SPREAD";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	//emfxinvestorigin_s = "spellFX_SPELLWATERSTORM3_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERSTORM3_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM3_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM3_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_SPELLWATERSTORM3_INVESTBLAST1";
};

instance SPELLFX_SPELLWATERSTORM3_KEY_INVEST_2(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
	emcreatefxid = "spellFX_SPELLWATERSTORM3_INVESTBLAST2";
};

instance SPELLFX_SPELLWATERSTORM3_KEY_INVEST_3(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "spellFX_SPELLWATERSTORM3_INVESTBLAST3";
};

instance SPELLFX_SPELLWATERSTORM3_KEY_INVEST_4(C_PARTICLEFXEMITKEY)
{
	lightrange = 250;
	emcreatefxid = "spellFX_SPELLWATERSTORM3_INVESTBLAST4";
};

instance SPELLFX_SPELLWATERSTORM3_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERSTORM3_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 100;
};

instance SPELLFX_SPELLWATERSTORM3_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERSTORM3_INVESTSOUND(CFX_BASE_PROTO)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM3_INVESTBLAST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM3_INVESTBLAST1";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM3_INVESTBLAST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM3_INVESTBLAST2";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM3_INVESTBLAST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM3_INVESTBLAST3";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM3_INVESTBLAST4(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM3_INVESTBLAST4";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM3_SPREAD(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM3_SPREAD_SMALL";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "CREATE CREATEQUAD";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellFX_ChargeFireball_COLLIDEDYNFX";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
	emfxcreate_s = "spellFX_SPELLWATERSTORM3_COLLIDE";
	sfxid = "MFX_SPELLWATERSTORM3_Collide";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM3_SPREAD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERSTORM3_SPREAD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
};

instance SPELLFX_SPELLWATERSTORM3_COLLIDE(CFX_BASE_PROTO)
{
	//visname_s = "MFX_Fireball_Collide3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_DESTROYUNDEAD_CAST2";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLWATERSTORM2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM2_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLWATERSTORM2_SPREAD";
	emfxcolldyn_s = "spellFX_SPELLWATERSTORM2_SPREAD";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	//emfxinvestorigin_s = "spellFX_SPELLWATERSTORM2_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERSTORM2_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM2_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM2_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_SPELLWATERSTORM2_INVESTBLAST1";
};

instance SPELLFX_SPELLWATERSTORM2_KEY_INVEST_2(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
	emcreatefxid = "spellFX_SPELLWATERSTORM2_INVESTBLAST2";
};

instance SPELLFX_SPELLWATERSTORM2_KEY_INVEST_3(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "spellFX_SPELLWATERSTORM2_INVESTBLAST3";
};

instance SPELLFX_SPELLWATERSTORM2_KEY_INVEST_4(C_PARTICLEFXEMITKEY)
{
	lightrange = 250;
	emcreatefxid = "spellFX_SPELLWATERSTORM2_INVESTBLAST4";
};

instance SPELLFX_SPELLWATERSTORM2_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERSTORM2_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 100;
};

instance SPELLFX_SPELLWATERSTORM2_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERSTORM2_INVESTSOUND(CFX_BASE_PROTO)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM2_INVESTBLAST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM2_INVESTBLAST1";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM2_INVESTBLAST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM2_INVESTBLAST2";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM2_INVESTBLAST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM2_INVESTBLAST3";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM2_INVESTBLAST4(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM2_INVESTBLAST4";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM2_SPREAD(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM2_SPREAD_SMALL";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "CREATE CREATEQUAD";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellFX_ChargeFireball_COLLIDEDYNFX";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
	emfxcreate_s = "spellFX_SPELLWATERSTORM2_COLLIDE";
	sfxid = "MFX_SPELLWATERSTORM2_Collide";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM2_SPREAD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERSTORM2_SPREAD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
};

instance SPELLFX_SPELLWATERSTORM2_COLLIDE(CFX_BASE_PROTO)
{
	//visname_s = "MFX_Fireball_Collide3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_DESTROYUNDEAD_CAST2";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLWATERSTORM1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM1_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLWATERSTORM1_SPREAD";
	emfxcolldyn_s = "spellFX_SPELLWATERSTORM1_SPREAD";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	//emfxinvestorigin_s = "spellFX_SPELLWATERSTORM1_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERSTORM1_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM1_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM1_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_SPELLWATERSTORM1_INVESTBLAST1";
};

instance SPELLFX_SPELLWATERSTORM1_KEY_INVEST_2(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
	emcreatefxid = "spellFX_SPELLWATERSTORM1_INVESTBLAST2";
};

instance SPELLFX_SPELLWATERSTORM1_KEY_INVEST_3(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "spellFX_SPELLWATERSTORM1_INVESTBLAST3";
};

instance SPELLFX_SPELLWATERSTORM1_KEY_INVEST_4(C_PARTICLEFXEMITKEY)
{
	lightrange = 250;
	emcreatefxid = "spellFX_SPELLWATERSTORM1_INVESTBLAST4";
};

instance SPELLFX_SPELLWATERSTORM1_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERSTORM1_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 100;
};

instance SPELLFX_SPELLWATERSTORM1_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERSTORM1_INVESTSOUND(CFX_BASE_PROTO)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM1_INVESTBLAST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM1_INVESTBLAST1";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM1_INVESTBLAST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM1_INVESTBLAST2";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM1_INVESTBLAST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM1_INVESTBLAST3";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM1_INVESTBLAST4(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM1_INVESTBLAST4";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM1_SPREAD(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM1_SPREAD_SMALL";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "CREATE CREATEQUAD";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellFX_ChargeFireball_COLLIDEDYNFX";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
	emfxcreate_s = "spellFX_SPELLWATERSTORM1_COLLIDE";
	sfxid = "MFX_SPELLWATERSTORM1_Collide";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM1_SPREAD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERSTORM1_SPREAD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
};

instance SPELLFX_SPELLWATERSTORM1_COLLIDE(CFX_BASE_PROTO)
{
	//visname_s = "MFX_Fireball_Collide3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_DESTROYUNDEAD_CAST2";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLWATERSTORM(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLWATERSTORM_SPREAD";
	emfxcolldyn_s = "spellFX_SPELLWATERSTORM_SPREAD";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	//emfxinvestorigin_s = "spellFX_SPELLWATERSTORM_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERSTORM_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SPELLWATERSTORM_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_SPELLWATERSTORM_INVESTBLAST1";
};

instance SPELLFX_SPELLWATERSTORM_KEY_INVEST_2(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
	emcreatefxid = "spellFX_SPELLWATERSTORM_INVESTBLAST2";
};

instance SPELLFX_SPELLWATERSTORM_KEY_INVEST_3(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "spellFX_SPELLWATERSTORM_INVESTBLAST3";
};

instance SPELLFX_SPELLWATERSTORM_KEY_INVEST_4(C_PARTICLEFXEMITKEY)
{
	lightrange = 250;
	emcreatefxid = "spellFX_SPELLWATERSTORM_INVESTBLAST4";
};

instance SPELLFX_SPELLWATERSTORM_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERSTORM_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 100;
};

instance SPELLFX_SPELLWATERSTORM_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERSTORM_INVESTSOUND(CFX_BASE_PROTO)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM_INVESTBLAST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM_INVESTBLAST1";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM_INVESTBLAST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM_INVESTBLAST2";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM_INVESTBLAST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM_INVESTBLAST3";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM_INVESTBLAST4(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM_INVESTBLAST4";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ARCANEMISSILE_CAST01";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM_SPREAD(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERSTORM_SPREAD_SMALL";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "CREATE CREATEQUAD";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellFX_ChargeFireball_COLLIDEDYNFX";
	//emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
	lightpresetname = "AURAMEDIUM";
	emfxcreate_s = "spellFX_SPELLWATERSTORM_COLLIDE";
	sfxid = "MFX_SPELLWATERSTORM_Collide";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERSTORM_SPREAD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERSTORM_SPREAD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
};

instance SPELLFX_SPELLWATERSTORM_COLLIDE(CFX_BASE_PROTO)
{
	//visname_s = "MFX_Fireball_Collide3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_DESTROYUNDEAD_CAST2";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_SPELLWATERLANCE3(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE3_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_SPELLWATERLANCE3_SENDPERCEPTION";
    emfxcolldyn_s = "SPELLFX_SPELLWATERLANCE3_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "AURAMEDIUM";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_SPELLWATERLANCE3_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_SPELLWATERLANCE3_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_SPELLWATERLANCE3_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "SFX_MAGIC_MAGICMISSILE_CAST_01";
};



instance spellfx_SPELLWATERLANCE3_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_FIREBALL_COLLIDE03";
};




instance spellfx_SPELLWATERLANCE3_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_SPELLWATERLANCE3_bloodfly(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE3_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_SPELLWATERLANCE3_sendperception(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE3_TARGET";
    sendassessmagic = 1;
    sfxid = "MFX_FIREBALL_COLLIDE04";

};

instance SPELLFX_SPELLWATERLANCE3_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	//visname_s = "MFX_FIRELARGEBOLT_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "SFX_MAGIC_MAGICMISSILE_IMPACT_01";
};
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/


instance spellfx_SPELLWATERLANCE2(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE2_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_SPELLWATERLANCE2_SENDPERCEPTION";
    emfxcolldyn_s = "SPELLFX_SPELLWATERLANCE2_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "AURAMEDIUM";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_SPELLWATERLANCE2_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_SPELLWATERLANCE2_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_SPELLWATERLANCE2_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "SFX_MAGIC_MAGICMISSILE_CAST_01";
};



instance spellfx_SPELLWATERLANCE2_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_FIREBALL_COLLIDE03";
};




instance spellfx_SPELLWATERLANCE2_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_SPELLWATERLANCE2_bloodfly(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE2_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_SPELLWATERLANCE2_sendperception(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE2_TARGET";
    sendassessmagic = 1;
    sfxid = "MFX_FIREBALL_COLLIDE04";

};

instance SPELLFX_SPELLWATERLANCE2_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	//visname_s = "MFX_FIREBOLTSPELL_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "SFX_MAGIC_MAGICMISSILE_IMPACT_01";
};
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_SPELLWATERLANCE1(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE1_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_SPELLWATERLANCE1_SENDPERCEPTION";
	emfxcolldyn_s = "SPELLFX_SPELLWATERLANCE1_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "AURAMEDIUM";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_SPELLWATERLANCE1_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_SPELLWATERLANCE1_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_SPELLWATERLANCE1_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "SFX_MAGIC_MAGICMISSILE_CAST_01";
};



instance spellfx_SPELLWATERLANCE1_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_FIREBALL_COLLIDE03";
	
};




instance spellfx_SPELLWATERLANCE1_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_SPELLWATERLANCE1_bloodfly(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE1_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_SPELLWATERLANCE1_sendperception(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE1_TARGET";
    sendassessmagic = 1;
    sfxid = "SFX_MAGIC_MAGICMISSILE_IMPACT_01";

};

instance SPELLFX_SPELLWATERLANCE1_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	//visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "SFX_MAGIC_MAGICMISSILE_IMPACT_01";
};
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_SPELLWATERLANCE(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_SPELLWATERLANCE_SENDPERCEPTION";
//	emfxcolldyn_s = "SPELLFX_SPELLWATERLANCE_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "AURAMEDIUM";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_SPELLWATERLANCE_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_SPELLWATERLANCE_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_SPELLWATERLANCE_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "SFX_MAGIC_MAGICMISSILE_CAST_01";
};



instance spellfx_SPELLWATERLANCE_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "SFX_MAGIC_MAGICMISSILE_IMPACT_01";
	
	
};




instance spellfx_SPELLWATERLANCE_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_SPELLWATERLANCE_bloodfly(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_SPELLWATERLANCE_sendperception(cfx_base_proto) {

    visname_s = "MFX_SPELLWATERLANCE_TARGET";
    sendassessmagic = 1;
    sfxid = "SFX_MAGIC_MAGICMISSILE_IMPACT_01";

};


/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance VOB_SPELLWATERBOLT3(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 FIRE";
	visname_s = "MFX_SPELLWATERBOLT3_TARGET";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERBOLT3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT3_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "spellFX_SPELLWATERBOLT3_FOUNTAIN";
	emfxcolldynperc_s = "VOB_SPELLWATERBOLT3";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERBOLT3_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERBOLT3_KEY_INVEST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_Geyser_Rumble";
};

instance SPELLFX_SPELLWATERBOLT3_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERBOLT3_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1600;
	lightrange = 100;
	emcheckcollision = 1;
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT3_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERBOLT3_FOUNTAIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT3_FOUNTAIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_Geyser_Fountain";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT3_RUMBLE(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
instance VOB_SPELLWATERBOLT2(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 FIRE";
	visname_s = "MFX_SPELLWATERBOLT2_TARGET";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERBOLT2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT2_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "spellFX_SPELLWATERBOLT2_FOUNTAIN";
	emfxcolldynperc_s = "VOB_SPELLWATERBOLT2";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERBOLT2_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERBOLT2_KEY_INVEST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_Geyser_Rumble";
};

instance SPELLFX_SPELLWATERBOLT2_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERBOLT2_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	lightrange = 100;
	emcheckcollision = 1;
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT2_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERBOLT2_FOUNTAIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT2_FOUNTAIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_Geyser_Fountain";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT2_RUMBLE(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
instance VOB_SPELLWATERBOLT1(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 FIRE";
	visname_s = "MFX_SPELLWATERBOLT1_TARGET";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERBOLT1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT1_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "spellFX_SPELLWATERBOLT1_FOUNTAIN";
	emfxcolldynperc_s = "VOB_SPELLWATERBOLT1";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	lightpresetname = "AURAMEDIUM";
};

instance SPELLFX_SPELLWATERBOLT1_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERBOLT1_KEY_INVEST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_Geyser_Rumble";
};

instance SPELLFX_SPELLWATERBOLT1_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERBOLT1_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1200;
	lightrange = 100;
	emcheckcollision = 1;
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT1_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERBOLT1_FOUNTAIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT1_FOUNTAIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_Geyser_Fountain";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT1_RUMBLE(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLWATERBOLT(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "spellFX_SPELLWATERBOLT_FOUNTAIN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	lightpresetname = "AURAMEDIUM";
};
	
instance SPELLFX_SPELLWATERBOLT_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLWATERBOLT_KEY_INVEST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_Geyser_Rumble";
};

instance SPELLFX_SPELLWATERBOLT_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLWATERBOLT_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1000;
	lightrange = 100;
	emcheckcollision = 1;
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_SPELLWATERBOLT_FOUNTAIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLWATERBOLT_FOUNTAIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_Geyser_Fountain";
	sfxisambient = 1;
};

instance SPELLFX_SPELLWATERBOLT_RUMBLE(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sfxid = "MFX_MIRROR_KONIEC1";
	sfxisambient = 1;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLICEBOLT3(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT3_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLICEBOLT3_COLLIDEFX";
	emfxcolldyn_s = "spellFX_SPELLICEBOLT3_COLLIDEDYNFX";
	//emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "AURASMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_SPELLICEBOLT3_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT3_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLICEBOLT3_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT3_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_SPELLICEBOLT3_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ICELANCE_COLLIDE11";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_SPELLICEBOLT3_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "MFX_ICELANCE_COLLIDE_011";
};

instance SPELLFX_SPELLICEBOLT3_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT3_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

instance SPELLFX_SPELLICEBOLT3_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT3_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLICEBOLT2(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT2_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLICEBOLT2_COLLIDEFX";
	emfxcolldyn_s = "spellFX_SPELLICEBOLT2_COLLIDEDYNFX";
	//emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "AURASMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_SPELLICEBOLT2_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT2_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLICEBOLT2_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT2_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_SPELLICEBOLT2_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ICELANCE_COLLIDE11";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_SPELLICEBOLT2_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "MFX_ICELANCE_COLLIDE_011";
};

instance SPELLFX_SPELLICEBOLT2_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT2_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

instance SPELLFX_SPELLICEBOLT2_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT2_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLICEBOLT1(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT1_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLICEBOLT1_COLLIDEFX";
	emfxcolldyn_s = "spellFX_SPELLICEBOLT1_COLLIDEDYNFX";
	//emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "AURASMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_SPELLICEBOLT1_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT1_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLICEBOLT1_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT1_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_SPELLICEBOLT1_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ICELANCE_COLLIDE11";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_SPELLICEBOLT1_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "MFX_ICELANCE_COLLIDE_011";
};

instance SPELLFX_SPELLICEBOLT1_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT1_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

instance SPELLFX_SPELLICEBOLT1_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT1_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_SPELLICEBOLT(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_SPELLICEBOLT_COLLIDEFX";
	emfxcolldyn_s = "spellFX_SPELLICEBOLT_COLLIDEDYNFX";
	//emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "AURASMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_SPELLICEBOLT_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_SPELLICEBOLT_INIT";
	lightrange = 0.001;
};

instance SPELLFX_SPELLICEBOLT_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_SPELLICEBOLT_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ICELANCE_COLLIDE11";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_SPELLICEBOLT_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "MFX_ICELANCE_COLLIDE_011";
};

instance SPELLFX_SPELLICEBOLT_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

instance SPELLFX_SPELLICEBOLT_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_SPELLICEBOLT_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "AURASMALL";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_SPELLICEBALL3(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL3_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_SPELLICEBALL3_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_SPELLICEBALL3_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL3_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL3_bridge(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL3_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 1500.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_SPELLICEBALL3_Target";
	emfxcolldyn_s = "SPELLFX_SPELLICEBALL3_COLLIDEDYNFX";
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL3_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL3_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL3_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_SPELLICEBALL3_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;


};

instance SPELLFX_SPELLICEBALL3_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "";//MFX_MEDIUMFIREBALL_Collide4
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_ICELANCE_COLLIDE_021";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_SPELLICEBALL2(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL2_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_SPELLICEBALL2_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_SPELLICEBALL2_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL2_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL2_bridge(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL2_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 1200.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_SPELLICEBALL2_Target";
	emfxcolldyn_s = "SPELLFX_SPELLICEBALL2_COLLIDEDYNFX";
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL2_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL2_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL2_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_SPELLICEBALL2_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;


};

instance SPELLFX_SPELLICEBALL2_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "";//MFX_MEDIUMFIREBALL_Collide4
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_ICELANCE_COLLIDE_021";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_SPELLICEBALL1(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL1_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_SPELLICEBALL1_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_SPELLICEBALL1_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL1_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL1_bridge(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL1_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 1050.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_SPELLICEBALL1_Target";
	emfxcolldyn_s = "SPELLFX_SPELLICEBALL1_COLLIDEDYNFX";
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL1_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL1_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL1_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_SPELLICEBALL1_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;


};

instance SPELLFX_SPELLICEBALL1_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "";//MFX_MEDIUMFIREBALL_Collide4
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_ICELANCE_COLLIDE_021";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_SPELLICEBALL(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_SPELLICEBALL_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_SPELLICEBALL_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL_bridge(cfx_base_proto) 
{
    visname_s = "MFX_SPELLICEBALL_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 900.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_SPELLICEBALL_Target";
	emfxcolldyn_s = "SPELLFX_SPELLICEBALL_COLLIDEDYNFX";
	
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_ICELANCE_COLLIDE11";
};



instance spellfx_SPELLICEBALL_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_SPELLICEBALL_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;
};

instance SPELLFX_SPELLICEBALL_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "";//MFX_MEDIUMFIREBALL_Collide4
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "AURAMEDIUM";
	sfxid = "MFX_ICELANCE_COLLIDE_021";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIRESPELLFIST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST3_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_FIRESPELLFIST3_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST3_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIRESPELLFIST3_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST3_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_FIRESPELLFIST3_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_FIRESPELLFIST3_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST3_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST3_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST3_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST3_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST3_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 1500;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_FIRESPELLFIST3_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_FIRESPELLFIST3_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_FIRESPELLFIST3";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance VOB_FIRESPELLFIST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRELARGEBOLT_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIRESPELLFIST3_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_FIRESPELLFIST3_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIRESPELLFIST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST2_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_FIRESPELLFIST2_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST2_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIRESPELLFIST2_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST2_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_FIRESPELLFIST2_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_FIRESPELLFIST2_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST2_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST2_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST2_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST2_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST2_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 1200;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_FIRESPELLFIST2_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_FIRESPELLFIST2_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_FIRESPELLFIST2";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance VOB_FIRESPELLFIST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRELARGEBOLT_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIRESPELLFIST2_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_FIRESPELLFIST2_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIRESPELLFIST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST1_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_FIRESPELLFIST1_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST1_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIRESPELLFIST1_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST1_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_FIRESPELLFIST1_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_FIRESPELLFIST1_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST1_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST1_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST1_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST1_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST1_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 1050;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_FIRESPELLFIST1_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_FIRESPELLFIST1_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_FIRESPELLFIST1";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance VOB_FIRESPELLFIST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIRESPELLFIST1_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_FIRESPELLFIST1_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIRESPELLFIST(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetrange = 50;
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 1;
	emtrjangleelevvar = 0;
	emtrjangleheadvar = 0;
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 100;
	emtrjdynupdatedelay = 20000;
	emfxcreatedowntrj = 1;
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};

instance SPELLFX_FIRESPELLFIST_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIRESPELLFIST_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIRESPELLFIST_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellfx_FIRESPELLFIST_Abyss";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_FIRESPELLFIST_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_METEOR_COLLIDE1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESPELLFIST_ABYSS(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESPELLFIST_CAST";
	visalpha = 1;
	visalphablendfunc_s = "ADD";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjnumkeys = 4;
	emtrjnumkeysvar = 2;
	emtrjangleelevvar = 5;
	emtrjangleheadvar = 10;
	//emtrjloopmode_s = "NONE";
	emtrjloopmode_s 	= "PINGPONG_ONCE";
	emtrjeasefunc_s = "LINEAR";
	emtrjeasevel = 900;
	emtrjdynupdatedelay = 0.1;
	emtrjdynupdatetargetonly = 1;
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emactioncollstat_s = "COLLIDE CREATE";
	emfxcollstat_s = "SPELLFX_FIRESPELLFIST_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_FIRESPELLFIST_COLLIDEDYNFX";
	emfxlifespan = -1;
	emselfrotvel_s = "0 0 0";
	secsperdamage = -1;
};



instance SPELLFX_FIRESPELLFIST_ABYSS_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcheckcollision = 1;
	sfxid = "MFX_METEOR_CAST1";
};

instance SPELLFX_FIRESPELLFIST_ABYSS_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/


instance spellfx_FIRESPELLBURNINGDREI(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGDREI_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_FIRESPELLBURNINGDREI_SENDPERCEPTION";
    emfxcolldyn_s = "SPELLFX_FIRESPELLBURNINGDREI_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "FIRESMALL";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_FIRESPELLBURNINGDREI_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_FIRESPELLBURNINGDREI_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_FIRESPELLBURNINGDREI_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "MFX_FIREBALL_CAST1";
};



instance spellfx_FIRESPELLBURNINGDREI_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_FIREBALL_COLLIDE03";
};




instance spellfx_FIRESPELLBURNINGDREI_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_FIRESPELLBURNINGDREI_bloodfly(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGDREI_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_FIRESPELLBURNINGDREI_sendperception(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGDREI_TARGET";
    sendassessmagic = 1;
    sfxid = "MFX_FIREBALL_COLLIDE04";

};

instance SPELLFX_FIRESPELLBURNINGDREI_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRELARGEBOLT_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/


instance spellfx_FIRESPELLBURNINGZWEI(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGZWEI_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_FIRESPELLBURNINGZWEI_SENDPERCEPTION";
    emfxcolldyn_s = "SPELLFX_FIRESPELLBURNINGZWEI_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "FIRESMALL";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_FIRESPELLBURNINGZWEI_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_FIRESPELLBURNINGZWEI_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_FIRESPELLBURNINGZWEI_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "MFX_FIREBALL_CAST1";
};



instance spellfx_FIRESPELLBURNINGZWEI_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_FIREBALL_COLLIDE03";
};




instance spellfx_FIRESPELLBURNINGZWEI_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_FIRESPELLBURNINGZWEI_bloodfly(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGZWEI_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_FIRESPELLBURNINGZWEI_sendperception(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGZWEI_TARGET";
    sendassessmagic = 1;
    sfxid = "MFX_FIREBALL_COLLIDE04";

};

instance SPELLFX_FIRESPELLBURNINGZWEI_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOLTSPELL_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_FIRESPELLBURNINGEIN(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGEIN_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_FIRESPELLBURNINGEIN_SENDPERCEPTION";
	emfxcolldyn_s = "SPELLFX_FIRESPELLBURNINGEIN_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "FIRESMALL";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_FIRESPELLBURNINGEIN_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_FIRESPELLBURNINGEIN_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_FIRESPELLBURNINGEIN_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "MFX_FIREBALL_CAST1";
};



instance spellfx_FIRESPELLBURNINGEIN_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_FIREBALL_COLLIDE03";
	
};




instance spellfx_FIRESPELLBURNINGEIN_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_FIRESPELLBURNINGEIN_bloodfly(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGEIN_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_FIRESPELLBURNINGEIN_sendperception(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNINGEIN_TARGET";
    sendassessmagic = 1;
    sfxid = "MFX_FIREBALL_COLLIDE04";

};

instance SPELLFX_FIRESPELLBURNINGEIN_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_FIRESPELLBURNING(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNING_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
    //emtrjloopmode_s = "PINGPONG_ONCE";
    emtrjeasefunc_s = "LINEAR";
    emactioncollstat_s = "COLLIDE";
    emactioncolldyn_s = "COLLIDE CREATEONCE";//emactioncolldyn_s = "CREATEONCE";
    emfxcolldynperc_s = "spellFX_FIRESPELLBURNING_SENDPERCEPTION";
//	emfxcolldyn_s = "SPELLFX_FIRESPELLBURNING_COLLIDEDYNFX";
    emtrjtargetrange = 20.0;
    emtrjtargetelev = 0.0;
	lightpresetname = "FIRESMALL";



//    sfxid = "MFX_FIREBALL_COLLIDE02";
//    emfxinvestorigin_s = "spellFX_DARKRITUAL_Invest";

};



instance spellfx_FIRESPELLBURNING_key_init(c_particlefxemitkey) {

//    visname_s = "MFX_LIGHTNINGSPHERE_INIT";
    lightrange = 0.001;
};



instance spellfx_FIRESPELLBURNING_key_cast(c_particlefxemitkey) {

    visname_s = "MFX_FIRESPELLBURNING_CAST";
    emtrjmode_s = "TARGET";
    emtrjeasevel = 1400.0;
    lightrange = 100.0;
    emcheckcollision = 1;
    sfxid = "MFX_FIREBALL_CAST1";
};



instance spellfx_FIRESPELLBURNING_key_collide(c_particlefxemitkey) {

    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    sfxid = "MFX_FIREBALL_COLLIDE03";
	
	
};




instance spellfx_FIRESPELLBURNING_slowtime(cfx_base_proto) {

    emfxtriggerdelay = 6.0;
    emfxlifespan = 30.0;
    visname_s = "morph.fov";
    userstring = "0.8";
    userstring[1] = "1.0";
    userstring[2] = "120";
    userstring[3] = "90";
};



instance spellfx_FIRESPELLBURNING_bloodfly(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNING_FLYTOPLAYER";
    emtrjeasevel = 0.01;
    emtrjmode_s = "TARGET LINE";
    emtrjoriginnode = "Bip01 Spine2";
    emtrjtargetnode = "ZS_RIGHTHAND";
    emtrjdynupdatedelay = 0.01;
};



instance spellfx_FIRESPELLBURNING_sendperception(cfx_base_proto) {

    visname_s = "MFX_FIRESPELLBURNING_TARGET";
    sendassessmagic = 1;
    sfxid = "MFX_FIREBALL_COLLIDE04";

};


/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_MASIVEFIREBURN(cfx_base_proto) 
{
    visname_s = "MFX_MASIVEFIREBURN_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_MASIVEFIREBURN_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_MASIVEFIREBURN_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_MASIVEFIREBURN_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_MASIVEFIREBURN_bridge(cfx_base_proto) 
{
    visname_s = "MFX_MASIVEFIREBURN_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 1500.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_MASIVEFIREBURN_Target";
	emfxcolldyn_s = "SPELLFX_MASIVEFIREBURN_COLLIDEDYNFX";
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_Fireball_Collide1";
};



instance spellfx_MASIVEFIREBURN_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_FIRESTORM_CAST1";
};



instance spellfx_MASIVEFIREBURN_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_MASIVEFIREBURN_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_MASIVEFIREBURN_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 30000;
	lightpresetname = "FIRESMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";

};

instance SPELLFX_MASIVEFIREBURN_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRELARGEBOLT_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_LARGEFIREBURN(cfx_base_proto) 
{
    visname_s = "MFX_LARGEFIREBURN_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_LARGEFIREBURN_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_LARGEFIREBURN_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_LARGEFIREBURN_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_LARGEFIREBURN_bridge(cfx_base_proto) 
{
    visname_s = "MFX_LARGEFIREBURN_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 1200.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_LARGEFIREBURN_Target";
	emfxcolldyn_s = "SPELLFX_LARGEFIREBURN_COLLIDEDYNFX";
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_Fireball_Collide1";
};



instance spellfx_LARGEFIREBURN_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_FIRESTORM_CAST1";
};



instance spellfx_LARGEFIREBURN_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_LARGEFIREBURN_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_LARGEFIREBURN_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 30000;
	lightpresetname = "FIRESMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";

};

instance SPELLFX_LARGEFIREBURN_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOLTSPELL_Collide";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_MEDIUMFIREBURN(cfx_base_proto) 
{
    visname_s = "MFX_MEDIUMFIREBURN_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_MEDIUMFIREBURN_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_MEDIUMFIREBURN_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_MEDIUMFIREBURN_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_MEDIUMFIREBURN_bridge(cfx_base_proto) 
{
    visname_s = "MFX_MEDIUMFIREBURN_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 1050.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_MEDIUMFIREBURN_Target";
	emfxcolldyn_s = "SPELLFX_MEDIUMFIREBURN_COLLIDEDYNFX";
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_Fireball_Collide1";
};



instance spellfx_MEDIUMFIREBURN_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_FIRESTORM_CAST1";
};



instance spellfx_MEDIUMFIREBURN_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_MEDIUMFIREBURN_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_MEDIUMFIREBURN_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 30000;
	lightpresetname = "FIRESMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";

};

instance SPELLFX_MEDIUMFIREBURN_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance spellfx_FIREBURN(cfx_base_proto) 
{
    visname_s = "MFX_FIREBURN_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};

instance spellfx_FIREBURN_key_cast(c_particlefxemitkey)
{
    emcreatefxid = "spellFX_FIREBURN_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    //emtrjeasevel = 1400.0;
	emtrjeasevel = 52100; //2000 szybkosc poruszania sie spella
    emcheckcollision = 1;
	sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_FIREBURN_key_collide(c_particlefxemitkey) 
{
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_FIREBURN_bridge(cfx_base_proto) 
{
    visname_s = "MFX_FIREBURN_CAST";
    visalpha = 1.0;
    visalphablendfunc_s = "ADD";
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjnumkeys = 4;//4
    emtrjnumkeysvar = 2;//2
    emtrjangleelevvar = 5.0;//5.0
    emtrjangleheadvar = 10.0;//
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
    emtrjeasevel = 900.0;//900.0
    emtrjdynupdatedelay = 0.1;
    emtrjdynupdatetargetonly = 1;
    emactioncolldyn_s = "COLLIDE CREATEONCE";
    emactioncollstat_s = "COLLIDE";
    emfxcolldynperc_s = "SPELLFX_FIREBURN_Target";
	emfxcolldyn_s = "SPELLFX_FIREBURN_COLLIDEDYNFX";
	
    emfxlifespan = -1.0;
    emselfrotvel_s = "0 0 0";
    //secsperdamage = -1.0;
		sfxid = "MFX_Fireball_Collide1";
};



instance spellfx_FIREBURN_bridge_key_cast(c_particlefxemitkey) 
{
    emcheckcollision = 1;
	sfxid = "MFX_FIRESTORM_CAST1";
};



instance spellfx_FIREBURN_bridge_key_collide(c_particlefxemitkey) 
{
    visname_s = "";
    emtrjeasevel = 1.0E-6;
	    sfxid = "MFX_FIREWAVE_CAST1";
};



instance spellfx_FIREBURN_target(cfx_base_proto) 
{
    emtrjoriginnode = "BIP01";
    visname_s = "MFX_FIREBURN_Target";
    visalpha = 1.0;
    emtrjmode_s = "FIXED";
    sendassessmagic = 1;
};

instance SPELLFX_FIREBURN_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "";//MFX_MEDIUMFIREBALL_Collide4
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_MEDIUMFIREBALL(CFX_BASE_PROTO)
{
	visname_s = "MFX_MEDIUMFIREBALL_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_MEDIUMFIREBALL_COLLIDE";
	emfxcolldyn_s = "spellFX_MEDIUMFIREBALL_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emfxcollstatalign_s = "COLLISIONNORMAL";
	emfxcreatedowntrj = 0;
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_MEDIUMFIREBALL_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_MEDIUMFIREBALL_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_MEDIUMFIREBALL_INIT";
	lightrange = 0.01;
};

instance SPELLFX_MEDIUMFIREBALL_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	visname_s = "MFX_IFB_PFXTRAIL";
	emtrjmode_s = "TARGET";
	emselfrotvel_s = "100 100 100";
	emtrjeasevel = 1400;
	sfxid = "MFX_MEDIUMFIREBALL_Cast";
	sfxisambient = 1;
	emcreatefxid = "spellFX_MEDIUMFIREBALL_FIRECLOUD";
	emcheckcollision = 1;
};

instance SPELLFX_MEDIUMFIREBALL_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_MEDIUMFIREBALL_FIRECLOUD(CFX_BASE_PROTO)
{
	emtrjeasevel = 1400;
	visname_s = "MFX_IFB_CAST";
	visalpha = 1;
	emtrjmode_s = "TARGET";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 2;
	emactioncolldyn_s = "COLLIDE";
	emactioncollstat_s = "COLLIDE";
};

instance SPELLFX_MEDIUMFIREBALL_FIRECLOUD_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_MEDIUMFIREBALL_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_MEDIUMFIREBALL_COLLIDE_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	sfxid = "MFX_Fireball_Collide1";
};

instance SPELLFX_MEDIUMFIREBALL_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_MEDIUMFIREBALL_COLLIDEDYNFX_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_MEDIUMFIREBALL_Collide4";
	sfxid = "MFX_Fireball_Collide1";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIRELARGEBOLT(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRELARGEBOLT_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "SPELLFX_FIRELARGEBOLT_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_FIRELARGEBOLT_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 30000;
	lightpresetname = "FIRESMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_FIRELARGEBOLT_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIRELARGEBOLT_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIRELARGEBOLT_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIRELARGEBOLT_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_FIRELARGEBOLT_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "Torch_Enlight";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_FIRELARGEBOLT_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "TORCH_ENLIGHT";
};

instance SPELLFX_FIRELARGEBOLT_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRELARGEBOLT_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIRELARGEBOLT_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRELARGEBOLT_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIREBOLTSPELL(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOLTSPELL_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "SPELLFX_FIREBOLTSPELL_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_FIREBOLTSPELL_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 30000;
	lightpresetname = "FIRESMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_FIREBOLTSPELL_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIREBOLTSPELL_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIREBOLTSPELL_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIREBOLTSPELL_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_FIREBOLTSPELL_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "Torch_Enlight";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_FIREBOLTSPELL_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "TORCH_ENLIGHT";
};

instance SPELLFX_FIREBOLTSPELL_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOLTSPELL_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIREBOLTSPELL_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOLTSPELL_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIREARROWSPELL(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREARROW_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "SPELLFX_FIREARROWSPELL_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_FIREARROWSPELL_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 30000;
	lightpresetname = "FIRESMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_FIREARROWSPELL_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIREARROWSPELL_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIREARROW_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIREARROWSPELL_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_FIREARROW_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "Torch_Enlight";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_FIREARROWSPELL_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "TORCH_ENLIGHT";
};

instance SPELLFX_FIREARROWSPELL_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREARROW_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIREARROWSPELL_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREARROW_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
instance SPELLFX_FIREBOMB(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOMB_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_FIREBOMB_SPREAD";
	emfxcolldyn_s = "spellFX_FIREBOMB_SPREAD";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellFX_FIREBOMB_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIREBOMB_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_FIREBOMB_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_FIREBOMB_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_FIREBOMB_INVESTBLAST1";
};

instance SPELLFX_FIREBOMB_KEY_INVEST_2(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
	emcreatefxid = "spellFX_FIREBOMB_INVESTBLAST2";
};

instance SPELLFX_FIREBOMB_KEY_INVEST_3(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "spellFX_FIREBOMB_INVESTBLAST3";
};

instance SPELLFX_FIREBOMB_KEY_INVEST_4(C_PARTICLEFXEMITKEY)
{
	lightrange = 250;
	emcreatefxid = "spellFX_FIREBOMB_INVESTBLAST4";
};

instance SPELLFX_FIREBOMB_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIREBOMB_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_Firestorm_Cast";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 100;
};

instance SPELLFX_FIREBOMB_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_FIREBOMB_INVESTSOUND(CFX_BASE_PROTO)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "MFX_Firestorm_Invest";
	sfxisambient = 1;
};

instance SPELLFX_FIREBOMB_INVESTBLAST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOMB_INVESTBLAST1";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest1";
	sfxisambient = 1;
};

instance SPELLFX_FIREBOMB_INVESTBLAST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOMB_INVESTBLAST2";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest2";
	sfxisambient = 1;
};

instance SPELLFX_FIREBOMB_INVESTBLAST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOMB_INVESTBLAST3";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest3";
	sfxisambient = 1;
};

instance SPELLFX_FIREBOMB_INVESTBLAST4(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOMB_INVESTBLAST4";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest4";
	sfxisambient = 1;
};

instance SPELLFX_FIREBOMB_SPREAD(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOMB_SPREAD_SMALL";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "SPELLFX_LARGEFB_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 25000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
	emfxcreate_s = "spellFX_FIREBOMB_COLLIDE";
	sfxid = "MFX_FIrestorm_Collide";
	sfxisambient = 1;
};

instance SPELLFX_FIREBOMB_SPREAD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIREBOMB_SPREAD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
};

instance SPELLFX_FIREBOMB_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIREBOMB_COLLIDE3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_Collide3";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIRESHADES(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADES_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_FIRESHADES_SPREAD";
	emfxcolldyn_s = "spellFX_FIRESHADES_SPREAD";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellFX_FIRESHADES_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIRESHADES_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_FIRESHADES_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_FIRESHADES_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_FIRESHADES_INVESTBLAST1";
};

instance SPELLFX_FIRESHADES_KEY_INVEST_2(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
	emcreatefxid = "spellFX_FIRESHADES_INVESTBLAST2";
};

instance SPELLFX_FIRESHADES_KEY_INVEST_3(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "spellFX_FIRESHADES_INVESTBLAST3";
};

instance SPELLFX_FIRESHADES_KEY_INVEST_4(C_PARTICLEFXEMITKEY)
{
	lightrange = 250;
	emcreatefxid = "spellFX_FIRESHADES_INVESTBLAST4";
};

instance SPELLFX_FIRESHADES_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIRESHADES_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_Firestorm_Cast";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 100;
};

instance SPELLFX_FIRESHADES_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_FIRESHADES_INVESTSOUND(CFX_BASE_PROTO)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "MFX_Firestorm_Invest";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADES_INVESTBLAST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADES_INVESTBLAST1";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADES_INVESTBLAST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADES_INVESTBLAST2";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest2";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADES_INVESTBLAST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADES_INVESTBLAST3";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest3";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADES_INVESTBLAST4(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADES_INVESTBLAST4";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest4";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADES_SPREAD(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADES_SPREAD_SMALL";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "SPELLFX_LARGEFB_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 25000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
	emfxcreate_s = "spellFX_FIRESHADES_COLLIDE";
	sfxid = "MFX_FIrestorm_Collide";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADES_SPREAD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIRESHADES_SPREAD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
};

instance SPELLFX_FIRESHADES_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADES_COLLIDE3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_Collide3";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

instance SPELLFX_FIRESHADOW(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADOW_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_FIRESHADOW_SPREAD";
	emfxcolldyn_s = "spellFX_FIRESHADOW_SPREAD";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellFX_FIRESHADOW_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIRESHADOW_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_FIRESHADOW_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_FIRESHADOW_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	emcreatefxid = "spellFX_FIRESHADOW_INVESTBLAST1";
};

instance SPELLFX_FIRESHADOW_KEY_INVEST_2(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
	emcreatefxid = "spellFX_FIRESHADOW_INVESTBLAST2";
};

instance SPELLFX_FIRESHADOW_KEY_INVEST_3(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "spellFX_FIRESHADOW_INVESTBLAST3";
};

instance SPELLFX_FIRESHADOW_KEY_INVEST_4(C_PARTICLEFXEMITKEY)
{
	lightrange = 250;
	emcreatefxid = "spellFX_FIRESHADOW_INVESTBLAST4";
};

instance SPELLFX_FIRESHADOW_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_FIRESHADOW_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_Firestorm_Cast";
	sfxisambient = 1;
	emcheckcollision = 1;
	lightrange = 100;
};

instance SPELLFX_FIRESHADOW_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_FIRESHADOW_INVESTSOUND(CFX_BASE_PROTO)
{
	visname_s = "simpleglow.tga";
	visalpha = 0.01;
	sfxid = "MFX_Firestorm_Invest";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADOW_INVESTBLAST1(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADOW_INVESTBLAST1";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest1";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADOW_INVESTBLAST2(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADOW_INVESTBLAST2";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest2";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADOW_INVESTBLAST3(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADOW_INVESTBLAST3";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest3";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADOW_INVESTBLAST4(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADOW_INVESTBLAST4";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_invest4";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADOW_SPREAD(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADOW_SPREAD_SMALL";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "SPELLFX_LARGEFB_COLLIDEDYNFX";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 1;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
	emfxcreate_s = "spellFX_FIRESHADOW_COLLIDE";
	sfxid = "MFX_FIrestorm_Collide";
	sfxisambient = 1;
};

instance SPELLFX_FIRESHADOW_SPREAD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIRESHADOW_SPREAD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 150;
};

instance SPELLFX_FIRESHADOW_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_FIRESHADOW_COLLIDE3";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_Fireball_Collide3";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/


instance SPELLFX_LARGEFB(CFX_BASE_PROTO)
{
	visname_s = "MFX_LARGEFB_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "SPELLFX_LARGEFB_COLLIDE";
	emfxcolldyn_s = "SPELLFX_LARGEFB_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emfxcollstatalign_s = "COLLISIONNORMAL";
	emfxcreatedowntrj = 0;
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_LARGEFB_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_LARGEFB_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_LARGEFB_INIT";
	lightrange = 0.01;
};

instance SPELLFX_LARGEFB_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	visname_s = "MFX_LARGEFB_PFXTRAIL";
	emtrjmode_s = "TARGET";
	emselfrotvel_s = "100 100 100";
	emtrjeasevel = 1400;
	sfxid = "MFX_Fireball_Cast";
	sfxisambient = 1;
	emcreatefxid = "SPELLFX_LARGEFB_FIRECLOUD";
	emcheckcollision = 1;
};

instance SPELLFX_LARGEFB_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_LARGEFB_FIRECLOUD(CFX_BASE_PROTO)
{
	emtrjeasevel = 1400;
	visname_s = "MFX_LARGEFB_CAST";
	visalpha = 1;
	emtrjmode_s = "TARGET";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 2;
	emactioncolldyn_s = "COLLIDE";
	emactioncollstat_s = "COLLIDE";
};

instance SPELLFX_LARGEFB_FIRECLOUD_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_LARGEFB_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_LARGEFB_Collide4";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_LARGEFB_COLLIDE_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_LARGEFB_Collide4";
	sfxid = "MFX_Fireball_Collide4";
};

instance SPELLFX_LARGEFB_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_LARGEFB_Collide4";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_LARGEFB_COLLIDEDYNFX_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_LARGEFB_Collide4";
	sfxid = "MFX_Fireball_Collide4";
};

/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/



instance SPELLFX_ICEGOLEMSPELL_SENDPERCEPTION(CFX_BASE_PROTO)
{
	visname_s = "MFX_ICEGOLEMSPELL_TARGET";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sendassessmagic = 1;
	emadjustshptoorigin = 1;
	sfxid = "MFX_Icecube_Target";
};

instance SPELLFX_ICEGOLEMCUBE(CFX_BASE_PROTO)
{
	visname_s = "MFX_ICEGOLEMcube_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "SPELLFX_ICEGOLEMCube_COLLIDE";
	emfxcolldynperc_s = "SPELLFX_ICEGOLEMspell_SENDPERCEPTION";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "SPELLFX_ICEGOLEMspell_Invest";
	lightpresetname = "AURA";
};

instance SPELLFX_ICEGOLEMCUBE_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_ICEGOLEMCUBE_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_ICEGOLEMcube_INIT";
	lightrange = 0.01;
	scaleduration = 0.5;
};

instance SPELLFX_ICEGOLEMCUBE_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_ICEGOLEMCUBE_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1000;
	emcheckcollision = 1;
	sfxid = "MFX_ICEGOLEMcube_cast";
	sfxisambient = 1;
	lightrange = 100;
};

instance SPELLFX_ICEGOLEMCUBE_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_ICEGOLEMCUBE_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_ICEGOLEMSPELL_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ICEGOLEMCUBE_COLLIDE";
};

instance SPELLFX_ICEGOLEMSPELL_INVEST(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ICEGOLEMCUBE_INVEST";
	sfxisambient = 1;
};

instance SPELLFX_ICEGOLEMWAVE(CFX_BASE_PROTO)
{
	visname_s = "MFX_ICEGOLEMCUBE_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjloopmode_s = "NONE";
	emfxinvestorigin_s = "SPELLFX_ICEGOLEMspell_Invest";
};

instance SPELLFX_ICEGOLEMWAVE_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_ICEGOLEMCUBE_INIT";
};

instance SPELLFX_ICEGOLEMWAVE_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "SPELLFX_ICEGOLEMwave_WAVE";
	pfx_ppsisloopingchg = 1;
	sfxid = "MFX_ICEGOLEMwave_Cast";
	sfxisambient = 1;
};

instance SPELLFX_ICEGOLEMWAVE_WAVE(CFX_BASE_PROTO)
{
	visname_s = "MFX_ICEGOLEMwave_WAVE";
	emtrjoriginnode = "BIP01 R HAND";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldynperc_s = "SPELLFX_ICEGOLEMspell_SENDPERCEPTION";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "WHITEBLEND";
};

instance SPELLFX_ICEGOLEMWAVE_WAVE_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_ICEGOLEMWAVE_WAVE_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_ICEGOLEMWAVE_WAVE_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
};

instance SPELLFX_ICEGOLEMWAVE_SUB(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 HEAD";
};

////////////////////////////////////////////////////////////////

instance SPELLFX_BLOODFLY(CFX_BASE_PROTO)
{
	visname_s = "MFX_BLOODFLY_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 HOLD STING";//ZS_RIGHTHAND
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_BLOODFLY_COLLIDEFX";
	emfxcolldyn_s = "spellFX_BLOODFLY_COLLIDEDYNFX";
//	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "GREEN";
//	userstring[0] = "fireballquadmark.tga";
//	userstring[1] = "40 40";
//	userstring[2] = "MUL";
};

instance SPELLFX_BLOODFLY_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_BLOODFLY_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_BLOODFLY_INIT";
	lightrange = 0.001;
};

instance SPELLFX_BLOODFLY_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_BLOODFLY_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "BLO_ATTACK";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_BLOODFLY_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "BLO_ATTACK";
};

instance SPELLFX_BLOODFLY_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_BLOODFLY_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "GREEN";
};

instance SPELLFX_BLOODFLY_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_BLOODFLY_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "GREEN";
};

///////////////////////////////////////////////////////////////


instance spellfx_MINECRAWLER(cfx_base_proto) {

    visname_s = "MFX_SPIDERWEB_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "BIP01 R CLAW2";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
};



instance spellfx_MINECRAWLER_key_cast(c_particlefxemitkey) {

    emcreatefxid = "spellFX_SPIDERWEB_Bridge";
    emtrjeasevel = 1.0E-6;
    pfx_ppsisloopingchg = 1;
    emtrjmode_s = "TARGET SPLINE RANDOM";
    emtrjeasevel = 1400.0;
    emcheckcollision = 1;
	sfxid = "CRW_DIE_LAST";
};



instance spellfx_MINECRAWLER_key_collide(c_particlefxemitkey) {

};



instance spellfx_MINECRAWLER_bridge(cfx_base_proto) {

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



instance spellfx_MINECRAWLER_bridge_key_cast(c_particlefxemitkey) {

    emcheckcollision = 1;
};



instance spellfx_MINECRAWLER_bridge_key_collide(c_particlefxemitkey) {

    visname_s = "";
    emtrjeasevel = 1.0E-6;

};



instance spellfx_MINECRAWLER_target(cfx_base_proto) {

    emtrjoriginnode = "BIP01";

    visname_s = "MFX_SPIDERWEB_Target";

    visalpha = 1.0;

    emtrjmode_s = "FIXED";

    sfxid = "CRW_AMBIENT_SHORT_A2";

    sendassessmagic = 1;

};

//////////////////////////////////////////////////////

instance SPELLFX_FIREGOLEM(CFX_BASE_PROTO)
{
	visname_s = "MFX_Firebolt_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_FIREGOLEM_COLLIDEFX";
	emfxcolldyn_s = "spellFX_FIREGOLEM_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "FIRESMALL";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "40 40";
	userstring[2] = "MUL";
};

instance SPELLFX_FIREGOLEM_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_FIREGOLEM_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_Firebolt_INIT";
	lightrange = 0.001;
};

instance SPELLFX_FIREGOLEM_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "mfx_firebolt_cast";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "Torch_Enlight";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_FIREGOLEM_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "TORCH_ENLIGHT";
};

instance SPELLFX_FIREGOLEM_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_Firebolt_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_FIREGOLEM_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_Firebolt_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

/////////////////////////////


instance SPELLFX_INSTANTFIREGOLEM(CFX_BASE_PROTO)
{
	visname_s = "MFX_Fireball_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_INSTANTFIREGOLEM_COLLIDE";
	emfxcolldyn_s = "spellFX_INSTANTFIREGOLEM_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_MAGICBURN";
	emfxcollstatalign_s = "COLLISIONNORMAL";
	emfxcreatedowntrj = 0;
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_INSTANTFIREGOLEM_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_INSTANTFIREGOLEM_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_Fireball_INIT";
	lightrange = 0.01;
};

instance SPELLFX_INSTANTFIREGOLEM_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
	visname_s = "MFX_IFB_PFXTRAIL";
	emtrjmode_s = "TARGET";
	emselfrotvel_s = "100 100 100";
	emtrjeasevel = 1400;
	sfxid = "MFX_Fireball_Cast";
	sfxisambient = 1;
	emcreatefxid = "spellFX_INSTANTFIREGOLEM_FIRECLOUD";
	emcheckcollision = 1;
};

instance SPELLFX_INSTANTFIREGOLEM_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_INSTANTFIREGOLEM_FIRECLOUD(CFX_BASE_PROTO)
{
	emtrjeasevel = 1400;
	visname_s = "MFX_IFB_CAST";
	visalpha = 1;
	emtrjmode_s = "TARGET";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 20000;
	emcheckcollision = 2;
	emactioncolldyn_s = "COLLIDE";
	emactioncollstat_s = "COLLIDE";
};

instance SPELLFX_INSTANTFIREGOLEM_FIRECLOUD_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_INSTANTFIREGOLEM_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_Fireball_Collide1";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_INSTANTFIREGOLEM_COLLIDE_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_Fireball_Collide1";
	sfxid = "MFX_Fireball_Collide1";
};

instance SPELLFX_INSTANTFIREGOLEM_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_Fireball_Collide1";
	visalpha = 1;
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};

instance SPELLFX_INSTANTFIREGOLEM_COLLIDEDYNFX_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_Fireball_Collide1";
	sfxid = "MFX_Fireball_Collide1";
};

///////////////////////////

instance SPELLFX_FIREGOLEMSTORM(CFX_BASE_PROTO)
{
	visname_s = "MFX_FireStorm_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_Firestorm_SPREAD";
	emfxcolldyn_s = "spellFX_Firestorm_SPREAD";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellFX_Firestorm_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

/////////////////////////////////////

instance SPELLFX_FIREWARANSTORM(CFX_BASE_PROTO)
{
	visname_s = "MFX_FireStorm_Init";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 TONGUE04";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATEONCE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_Firestorm_SPREAD";
	emfxcolldyn_s = "spellFX_Firestorm_SPREAD";
	emfxcolldynperc_s = "vob_magicburn";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	emfxinvestorigin_s = "spellFX_Firestorm_INVESTSOUND";
	userstring[0] = "fireballquadmark.tga";
	userstring[1] = "100 100";
	userstring[2] = "MUL";
	lightpresetname = "FIRESMALL";
};

/////////////////////////////////////


instance SPELLFX_GOLEMDEATH(CFX_BASE_PROTO)
{
	visname_s = "MFX_GOLEMDEATH_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjloopmode_s = "NONE";
	emfxcreatedowntrj = 0;
};

instance SPELLFX_GOLEMDEATH_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_GOLEMDEATH_INIT";
};

instance SPELLFX_GOLEMDEATH_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_GOLEMDEATH_RIGHTHAND";
	emcreatefxid = "spellFX_GOLEMDEATH_LEFTHAND";
};

instance SPELLFX_GOLEMDEATH_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_GOLEMDEATH_EXPLOSION";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_GOLEMDEATH_EXPLOSION(CFX_BASE_PROTO)
{
	visname_s = "MFX_GOLEMDEATH_EXPLOSION";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 L Hand";
	emfxcreate_s = "spellFX_GOLEMDEATH_GROUND";
};

instance SPELLFX_GOLEMDEATH_GROUND(CFX_BASE_PROTO)
{
	visname_s = "MFX_GOLEMDEATH_CAST";
	emtrjoriginnode = "BIP01 R Foot";
	emactioncolldyn_s = "CREATEONCE";
	emfxcolldyn_s = "spellFX_GOLEMDEATH_COLLIDEDYNFX";
	emfxcolldynalign_s = "COLLISIONNORMAL";
	emcheckcollision = 1;
	lightpresetname = "REDAMBIENCE";
	sfxid = "MFX_FIREBALL_COLLIDE04";
	sfxisambient = 1;
};

instance SPELLFX_GOLEMDEATH_LEFTHAND(CFX_BASE_PROTO)
{
	visname_s = "MFX_GOLEMDEATH_LEFTHAND";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "Bip01 L Hand";
	emfxcreate_s = "FX_EARTHQUAKE";
};

instance SPELLFX_GOLEMDEATH_SUB(CFX_BASE_PROTO)
{
	visname_s = "";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 HEAD";
};

instance SPELLFX_GOLEMDEATH_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_GOLEMDEATH_TARGET";
	emtrjoriginnode = "BIP01";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_FIREBALL_COLLIDE04";
};

////////////////////////////////////////////////


instance SPELLFX_ICEGOLEMLANCE(CFX_BASE_PROTO)
{
	visname_s = "MFX_Icelance_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "SPELLFX_ICEGOLEMLANCE_COLLIDEFX";
	emfxcolldyn_s = "SPELLFX_ICEGOLEMLANCE_COLLIDEFX";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emfxcreatedowntrj = 0;
	lightpresetname = "AURA";
};

instance SPELLFX_ICEGOLEMLANCE_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_ICEGOLEMLANCE_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_ICEGOLEMLANCE_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_Icelance_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	lightrange = 100;
	emcheckcollision = 1;
	sfxid = "MFX_Icelance_Cast";
};

instance SPELLFX_ICEGOLEMLANCE_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_ICEGOLEMLANCE_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_Icelance_Collide";
	visalpha = 1;
	emtrjmode_s = "FOLLOW TARGET";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_Icelance_Collide";
};

///////////////////////////


instance SPELLFX_ICEGOLEMBOLT(CFX_BASE_PROTO)
{
	visname_s = "MFX_Icebolt_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01 R HAND";
	emtrjtargetnode = "BIP01 FIRE";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "SPELLFX_ICEGOLEMBOLT_COLLIDE";
	emfxcolldyn_s = "SPELLFX_ICEGOLEMBOLT_COLLIDEDYNFX";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
};

instance SPELLFX_ICEGOLEMBOLT_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_Icebolt_INIT";
	scaleduration = 0.5;
};

instance SPELLFX_ICEGOLEMBOLT_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_Icebolt_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	sfxid = "MFX_ICELANCE_CAST1";
	emcheckcollision = 1;
};

instance SPELLFX_ICEGOLEMBOLT_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	emcheckcollision = 0;
};

instance SPELLFX_ICEGOLEMBOLT_COLLIDE(CFX_BASE_PROTO)
{
	visname_s = "MFX_Icebolt_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ICELANCE_CAST1";
};

instance SPELLFX_ICEGOLEMBOLT_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_Thunderbolt_Collide";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	sfxid = "MFX_ICELANCE_CAST1";
	sendassessmagic = 1;
};














































////////////////////////////////////////////////




instance SPELLFX_BELIARSWORD(CFX_BASE_PROTO)
{
	visname_s = "MFX_BELIARSWORD_INIT";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncollstat_s = "COLLIDE CREATE";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_BELIARSWORD_COLLIDEFX";
	emfxcolldyn_s = "spellFX_BELIARSWORD_COLLIDEFX";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emfxcreatedowntrj = 0;
	lightpresetname = "AURA";
};

instance SPELLFX_BELIARSWORD_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_BELIARSWORD_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_BELIARSWORD_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_BELIARSWORD_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 1400;
	lightrange = 100;
	emcheckcollision = 1;
	sfxid = "MFX_BELIARSWORD_Cast";
};

instance SPELLFX_BELIARSWORD_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	emtrjeasevel = 1e-006;
};

instance SPELLFX_BELIARSWORD_COLLIDEFX(CFX_BASE_PROTO)
{
	visname_s = "MFX_BELIARSWORD_Collide";
	visalpha = 1;
	emtrjmode_s = "FOLLOW TARGET";
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_BELIARSWORD_Collide";
};



INSTANCE spellfx_firemeteor (CFx_Base_Proto)
{
	visname_s = "mfx_firemeteor2_cast";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcolldyn_s = "spellFX_firemeteor_HEAVENSRAGE";
	emtrjtargetrange = 20;
	emtrjtargetelev = 0;
	emtrjdynupdatedelay = 20000;
	lightpresetname = "CATACLYSM";
};

instance SPELLFX_firemeteor_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.001;
};

instance SPELLFX_firemeteor_KEY_INVEST(C_PARTICLEFXEMITKEY)
{
	lightrange = 100;
};

instance SPELLFX_firemeteor_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	visname_s = "MFX_firemeteor_CAST";
	emtrjmode_s = "TARGET";
	emtrjeasevel = 12000; //2000 szybkosc poruszania sie spella
	sfxid = "MFX_FIREBALL_CAST1";
	//lightrange = 500;
	emcheckcollision = 1;
};

instance SPELLFX_firemeteor_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	emtrjeasevel = 1e-006;
};

instance SPELLFX_firemeteor_HEAVENSRAGE(CFX_BASE_PROTO)
{
	visname_s = "MFX_firemeteor_FLASH";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	sendassessmagic = 1;
	emfxcreate_s = "spellFX_firemeteor_target_CLOUD";
	//sfxid = "MFX_FIREWAVE_CAST1";
	sfxisambient = 1;
};

instance SPELLFX_firemeteor_TARGET_CLOUD(CFX_BASE_PROTO)
{
	visname_s = "MFX_firemeteor_TARGET_EXPLODE";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	emtrjdynupdatedelay = 0.01;
	sfxid = "MFX_METEOR_COLLIDE1";
};

instance VOB_SPIDER(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 FIRE";
	visname_s = "MFX_MAGICSPIDER";
	emfxcreate_s = "VOB_SPIDER_CHILD1";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	lightpresetname = "FIRESMALL";
	sfxid = "MFX_Firespell_Humanburn";
};
instance VOB_SPIDER_CHILD1(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 R UPPERARM";
	visname_s = "MFX_MAGICSPIDER";
	emfxcreate_s = "VOB_SPIDER_CHILD2";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
};

instance VOB_SPIDER_CHILD2(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 L UPPERARM";
	visname_s = "MFX_MAGICSPIDER";
	emfxcreate_s = "VOB_SPIDER_CHILD3";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
};

instance VOB_SPIDER_CHILD3(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 L HAND";
	visname_s = "MFX_MAGICSPIDER";
	emfxcreate_s = "VOB_SPIDER_CHILD4";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
};

instance VOB_SPIDER_CHILD4(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 R HAND";
	visname_s = "MFX_MAGICSPIDER";
	emfxcreate_s = "VOB_SPIDER_CHILD5";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
};

instance VOB_SPIDER_CHILD5(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 L FOOT";
	visname_s = "MFX_MAGICSPIDER";
	emfxcreate_s = "VOB_SPIDER_CHILD6";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
};

instance VOB_SPIDER_CHILD6(CFX_BASE_PROTO)
{
	emtrjoriginnode = "BIP01 R FOOT";
	visname_s = "MFX_MAGICSPIDER";
	//emfxcreate_s = "spellFX_MagicFire_HUMANSMOKE";
	emfxcreatedowntrj = 1;
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	sendassessmagic = 1;
};


instance spellfx_spiderwebNew(cfx_base_proto) {

    visname_s = "MFX_SPIDERWEB_INIT";
    emtrjmode_s = "FIXED";
    emtrjoriginnode = "ZS_RIGHTHAND";
    emtrjloopmode_s = "NONE";
    emtrjeasefunc_s = "LINEAR";
	//
	emactioncollstat_s = "COLLIDE CREATE CREATEQUAD";
	emactioncolldyn_s = "COLLIDE CREATEONCE";
	emfxcollstat_s = "spellFX_spiderwebNew_COLLIDEFX";
	emfxcolldyn_s = "spellFX_spiderwebNew_COLLIDEDYNFX";
	emfxcolldynperc_s = "VOB_SPIDER";
};
instance SPELLFX_spiderwebNew_KEY_OPEN(C_PARTICLEFXEMITKEY){
	lightrange = 0.001;
};
instance SPELLFX_spiderwebNew_KEY_INIT(C_PARTICLEFXEMITKEY){
	visname_s = "MFX_SPIDERWEB_INIT";
	lightrange = 0.001;
};
instance SPELLFX_spiderwebNew_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	//visname_s = "mfx_firebolt_cast";
	//emcreatefxid = "spellFX_SPIDERWEB_Bridge";
	visname_s = "MFX_SPIDERWEB_CAST";
	//emtrjmode_s = "TARGET";
	emtrjmode_s = "TARGET SPLINE RANDOM";
	emtrjeasevel = 1400;
	sfxid = "Torch_Enlight";
	lightrange = 100;
	emcheckcollision = 1;
};

instance SPELLFX_spiderwebNew_KEY_COLLIDE(C_PARTICLEFXEMITKEY)
{
	visname_s = "";
	pfx_flygravity_s = "0 0.0002 0";
	emtrjeasevel = 1e-006;
	sfxid = "TORCH_ENLIGHT";
};
instance SPELLFX_spiderwebNew_COLLIDEFX(CFX_BASE_PROTO)
{
	//visname_s = "MFX_Firebolt_Collide";
	visname_s = "MFX_SPIDERWEB_CAST";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};
instance SPELLFX_spiderwebNew_COLLIDEDYNFX(CFX_BASE_PROTO)
{
	//visname_s = "MFX_Firebolt_Collide";
	visname_s = "MFX_SPIDERWEB_CAST";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	lightpresetname = "FIRESMALL";
};



instance SPELLFX_SUMMONCREATUREG_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_GrenSumm_ORIGIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_Transform_Cast";
	sfxisambient = 1;
	emfxcreate_s = "FX_EarthQuake";
};
instance SPELLFX_SUMMONCREATUREY_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_YellowSumm_ORIGIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_Transform_Cast";
	sfxisambient = 1;
	emfxcreate_s = "FX_EarthQuake";
};
instance SPELLFX_SUMMONCREATUREB_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_BlueSumm_ORIGIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_Transform_Cast";
	sfxisambient = 1;
	emfxcreate_s = "FX_EarthQuake";
};
instance SPELLFX_SUMMONCREATURER_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_RedSumm_ORIGIN";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "BIP01";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_Transform_Cast";
	sfxisambient = 1;
	emfxcreate_s = "FX_EarthQuake";
};


instance SPELLFX_SUMMONGreen(CFX_BASE_PROTO)
{
	visname_s = "MFX_GrenSumm_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	lightpresetname = "WHITEBLEND";
};

instance SPELLFX_SUMMONGreen_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONGreen_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONGreen_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "FX_EarthQuake";
};

instance SPELLFX_SUMMONGreen_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "SPELLFX_SUMMONCREATUREG_ORIGIN";
	pfx_ppsisloopingchg = 1;
};
instance SPELLFX_SUMMONBlue(CFX_BASE_PROTO)
{
	visname_s = "MFX_BlueSumm_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	lightpresetname = "WHITEBLEND";
};

instance SPELLFX_SUMMONBlue_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONBlue_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONBlue_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "FX_EarthQuake";
};

instance SPELLFX_SUMMONBlue_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "SPELLFX_SUMMONCREATUREB_ORIGIN";
	pfx_ppsisloopingchg = 1;
};
instance SPELLFX_SUMMONYellow(CFX_BASE_PROTO)
{
	visname_s = "MFX_YellowSumm_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	lightpresetname = "WHITEBLEND";
};

instance SPELLFX_SUMMONYellow_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONYellow_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONYellow_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "FX_EarthQuake";
};

instance SPELLFX_SUMMONYellow_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "SPELLFX_SUMMONCREATUREY_ORIGIN";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_SUMMONRed(CFX_BASE_PROTO)
{
	visname_s = "MFX_RedSumm_INIT";
	visalpha = 1;
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	lightpresetname = "WHITEBLEND";
};

instance SPELLFX_SUMMONRed_KEY_OPEN(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONRed_KEY_INIT(C_PARTICLEFXEMITKEY)
{
	lightrange = 0.01;
};

instance SPELLFX_SUMMONRed_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	lightrange = 200;
	emcreatefxid = "FX_EarthQuake";
};

instance SPELLFX_SUMMONRed_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "SPELLFX_SUMMONCREATURER_ORIGIN";
	pfx_ppsisloopingchg = 1;
};

instance SPELLFX_TRANSFORMG(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformG_INIT";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjmode_s = "fixed";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 5000;
};

instance SPELLFX_TRANSFORMG_KEY_INVEST_0(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformG_ORIGIN";
};

instance SPELLFX_TRANSFORMG_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformG_ORIGIN";
};

instance SPELLFX_TRANSFORMG_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	pfx_ppsisloopingchg = 1;
	emcreatefxid = "spellFX_TransformG_BLEND";
};

instance SPELLFX_TRANSFORMG_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformG_ORIGIN";
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emselfrotvel_s = "0 0 50";
};

instance SPELLFX_TRANSFORMG_BLEND(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformG_BLEND";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_TransformG_Cast";
	sfxisambient = 1;
};
instance SPELLFX_TRANSFORMR(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformR_INIT";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjmode_s = "fixed";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 5000;
};

instance SPELLFX_TRANSFORMR_KEY_INVEST_0(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformR_ORIGIN";
};

instance SPELLFX_TRANSFORMR_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformR_ORIGIN";
};

instance SPELLFX_TRANSFORMR_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	pfx_ppsisloopingchg = 1;
	emcreatefxid = "spellFX_TransformR_BLEND";
};

instance SPELLFX_TRANSFORMR_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformR_ORIGIN";
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emselfrotvel_s = "0 0 50";
};

instance SPELLFX_TRANSFORMR_BLEND(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformR_BLEND";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_TransformR_Cast";
	sfxisambient = 1;
};
instance SPELLFX_TRANSFORMY(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformY_INIT";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjmode_s = "fixed";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 5000;
};

instance SPELLFX_TRANSFORMY_KEY_INVEST_0(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformY_ORIGIN";
};

instance SPELLFX_TRANSFORMY_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformY_ORIGIN";
};

instance SPELLFX_TRANSFORMY_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	pfx_ppsisloopingchg = 1;
	emcreatefxid = "spellFX_TransformY_BLEND";
};

instance SPELLFX_TRANSFORMY_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformY_ORIGIN";
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emselfrotvel_s = "0 0 50";
};

instance SPELLFX_TRANSFORMY_BLEND(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformY_BLEND";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_TransformY_Cast";
	sfxisambient = 1;
};
instance SPELLFX_TRANSFORMB(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformB_INIT";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjmode_s = "fixed";
	emtrjloopmode_s = "NONE";
	emtrjeasefunc_s = "LINEAR";
	emtrjdynupdatedelay = 5000;
};

instance SPELLFX_TRANSFORMB_KEY_INVEST_0(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformB_ORIGIN";
};

instance SPELLFX_TRANSFORMB_KEY_INVEST_1(C_PARTICLEFXEMITKEY)
{
	emcreatefxid = "spellFX_TransformB_ORIGIN";
};

instance SPELLFX_TRANSFORMB_KEY_CAST(C_PARTICLEFXEMITKEY)
{
	pfx_ppsisloopingchg = 1;
	emcreatefxid = "spellFX_TransformB_BLEND";
};

instance SPELLFX_TRANSFORMB_ORIGIN(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformB_ORIGIN";
	emtrjoriginnode = "BIP01";
	emtrjmode_s = "FIXED";
	emtrjdynupdatedelay = 0;
	emselfrotvel_s = "0 0 50";
};

instance SPELLFX_TRANSFORMB_BLEND(CFX_BASE_PROTO)
{
	visname_s = "MFX_TransformB_BLEND";
	emtrjmode_s = "FIXED";
	emtrjoriginnode = "ZS_RIGHTHAND";
	emtrjdynupdatedelay = 0;
	sfxid = "MFX_TransformB_Cast";
	sfxisambient = 1;
};
