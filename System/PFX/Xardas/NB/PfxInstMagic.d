instance mfx_deathbolt_init(c_particlefx) {

    ppsvalue = 75.0;
    ppsscalekeys_s = "1";
    ppsislooping = 1;
    ppsissmooth = 1;
    ppsfps = 1.0;
    shptype_s = "POINT";
    shpfor_s = "object";
    shpoffsetvec_s = "0 0 0";
    shpdistribtype_s = "RAND";
    shpdim_s = "10";
    shpscalekeys_s = "1";
    shpscaleislooping = 1;
    shpscaleissmooth = 1;
    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "BQM_SCAVENGER.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 128 128";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "6 6";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_deathbolt_cast(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 0.03;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Magic_Glow_Evil.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 128 128";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "2 5";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_deathbolt_collide(c_particlefx) {

    ppsvalue = 10.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "VFX_Magic_BigGlow_Evil.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 128 128";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "10 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};
instance mfx_itemfind(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.4 0.1";

    ppsfps = 0.2;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpisvolume = 1;

    shpdim_s = "15";

    shpscalekeys_s = "1 0.3 1.2 0.8 0.1 1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    velavg = 0.01;

    lsppartavg = 300.0;

    lsppartvar = 100.0;

    visname_s = "MFX_LIGHT_SINGLERAY.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "10 10 10";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "3 30";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

    useemittersfor = 1;

};
instance mfx_magic_footsteps(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 180.0;

    dirangleheadvar = 1.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    flygravity_s = "0 0.0002 0";

    visname_s = "MFX_SLEEP_STAR.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.1;

    trltexture_s = "WHITECLOUD.TGA";

};



instance mfx_heal_heavenlight_blue(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "-30 0 30";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpisvolume = 1;

    shpdim_s = "1";

    shpmesh_s = "TELEPORT_AURA.3ds";

    shpscalekeys_s = "1";

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    velavg = 0.09;

    lsppartavg = 600.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "TELSTURM.TGA";

    vistexcolorstart_s = "21 80 240";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "10 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "mfx_masterofdisaster_aura_16bit.TGA";

};



instance mfx_heal_heavenlight_yellow(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "-30 0 30";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpisvolume = 1;

    shpdim_s = "1";

    shpmesh_s = "TELEPORT_AURA.3ds";

    shpscalekeys_s = "1";

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    velavg = 0.09;

    lsppartavg = 600.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "TELSTURM.TGA";

    vistexcolorstart_s = "255 250 90";

    vistexcolorend_s = "255 250 90";

    vissizestart_s = "10 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "mfx_masterofdisaster_aura_16bit.TGA";

};



instance mfx_heal_heavenlight_red(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "-30 0 30";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpisvolume = 1;

    shpdim_s = "1";

    shpmesh_s = "TELEPORT_AURA.3ds";

    shpscalekeys_s = "1";

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    velavg = 0.09;

    lsppartavg = 600.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "TELSTURM.TGA";

    vistexcolorstart_s = "255 84 0";

    vistexcolorend_s = "255 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "mfx_masterofdisaster_aura_16bit.TGA";

};



instance mfx_heal_heavenlight_green(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "-30 0 30";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpisvolume = 1;

    shpdim_s = "1";

    shpmesh_s = "TELEPORT_AURA.3ds";

    shpscalekeys_s = "1";

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    velavg = 0.09;

    lsppartavg = 600.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "TELSTURM.TGA";

    vistexcolorstart_s = "0 244 0";

    vistexcolorend_s = "0 244 0";

    vissizestart_s = "10 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "mfx_masterofdisaster_aura_16bit.TGA";

};

instance mfx_transform_blend_druid(c_particlefx) {

    ppsvalue = 350.0;

    ppsscalekeys_s = "2";

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    dirmode_s = "TARGET";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    velavg = 1.0;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 150";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "5 4";

    vissizeendscale = 4.0;

    visalphafunc_s = "ADD";

    visalphastart = 233.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};
instance mana_potion_new(item_glimmer_proto) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "100";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "0 0 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};
instance health_potion_new(item_glimmer_proto) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "100";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};
instance yellow_potion_new(item_glimmer_proto) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "100";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "150 150 0";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};
instance poison_arrow(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "-60 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Magic_Rootnoose.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 225 255";

    vissizestart_s = "5 5";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 150.0;

    useemittersfor = 1;

};



instance holy_arrow(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "-60 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "100";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 200";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "15 15";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance holy_bolt(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "-20 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "100";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 200";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "15 15";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};
instance magic_crossbow_ice(c_particlefx) {

    ppsvalue = 40.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "NONE";

    velavg = 1.0E-11;

    lsppartavg = 300.0;

    flygravity_s = "0 0.000 0";

    visname_s = "MAGICDUMMY16BIT_4.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "45 126 255";

    vistexcolorend_s = "231 226 213";

    vissizestart_s = "6 6";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    useemittersfor = 0;

};
instance magic_poison(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "NONE";

    velavg = 0.0;

    lsppartavg = 30.0;

    flygravity_s = "0 0.000 0";

    visname_s = "Decal_Telestorm.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "000 100 255";

    vissizestart_s = "5 5";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 0;

};

instance mfx_energyball_collide(c_particlefx) {

    ppsvalue = 125.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "300";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 1200.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_MAGIC_CLOUD.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "255 148 63";

    vissizestart_s = "25 25";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 230.0;

    trltexture_s = "VFX_MAGIC_ADANOS_DARK_CLOUD.TGA";

    flockmode = "NONE";

};



instance mfx_energyball_collide2(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1";

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "50 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};
instance mfx_whirlwind_spread(c_particlefx) {

    ppsvalue = 125.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "100";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelevvar = 180.0;

    velavg = 0.1;

    velvar = 0.03;

    lsppartavg = 1200.0;

    flygravity_s = "0 0 0";

    visname_s = "WHIRLWIND.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "128 128 128";

    vissizestart_s = "50 50";

    vissizeendscale = 9.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 30.0;

};
instance mfx_windfist_init_windfury(c_particlefx) {

    ppsvalue = 100.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "3";

    shpscalekeys_s = "1 2 3 4 5 4 3 4 6 8 7 5 4 2 6 5 4 3 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "DIR";

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "7 7";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 230.0;

};
instance mfx_adanosballred_init(c_particlefx) {

    ppsvalue = 10.0;
    ppsscalekeys_s = "1";
    ppsislooping = 1;
    ppsfps = 2.0;
    shptype_s = "POINT";
    shpfor_s = "object";
    shpoffsetvec_s = "0 0 0";
    shpscalekeys_s = "1";
    dirmode_s = "NONE";
    dirfor_s = "OBJECT";
    dirmodetargetfor_s = "OBJECT";
    velavg = 0.001;
    lsppartavg = 800.0;
    lsppartvar = 300.0;
    flygravity_s = "0 -0.0000001 0";
    visname_s = "KOPFBALL.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexcolorstart_s = "205 42 24";
    vistexcolorend_s = "205 42 24";
    vissizestart_s = "10 10";
    vissizeendscale = 8.0;//10
    visalphafunc_s = "ADD";
    visalphastart = 255.0;
    useemittersfor = 1;

};



instance mfx_adanosballred_cast(c_particlefx) {

    ppsvalue = 50.0;
    ppsscalekeys_s = "1";
    ppsislooping = 1;
    ppsfps = 2.0;
    shptype_s = "POINT";
    shpfor_s = "object";
    shpoffsetvec_s = "0 0 0";
    shpscalekeys_s = "1";
    dirmode_s = "NONE";
    dirfor_s = "OBJECT";
    dirmodetargetfor_s = "OBJECT";
    velavg = 0.001;
    lsppartavg = 800.0;
    lsppartvar = 300.0;
    flygravity_s = "0 -0.0000001 0";
    visname_s = "KOPFBALL.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexcolorstart_s = "205 42 24";
    vistexcolorend_s = "205 42 24";
    vissizestart_s = "30 30";
    vissizeendscale = 8.0;//10
    visalphafunc_s = "ADD";
    visalphastart = 255.0;

};



instance mfx_adanosballred_target(c_particlefx) {

    ppsvalue = 3.0;
    ppsscalekeys_s = "10 9 8 7 6 5 4 3 2 1";
    ppsissmooth = 1;
    ppsfps = 4.0;
    shptype_s = "POINT";
    shpfor_s = "object";
    shpoffsetvec_s = "0 0 0";
    shpscalekeys_s = "1";
    dirmode_s = "NONE";
    dirfor_s = "OBJECT";
    dirmodetargetfor_s = "OBJECT";
    velavg = 0.001;
    lsppartavg = 800.0;
    lsppartvar = 300.0;
    flygravity_s = "0 -0.0000001 0";
    visname_s = "KOPFBALL.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexcolorstart_s = "205 42 24";
    vistexcolorend_s = "205 42 24";
    vissizestart_s = "30 30";
    vissizeendscale = 18.0;//20
    visalphafunc_s = "ADD";
    visalphastart = 255.0;
    useemittersfor = 1;

};
instance mfx_urizel_spread(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1 1 2 2";

    ppsissmooth = 1;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "25";

    shpscalekeys_s = "1 2 3 4";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00008 0";

    visname_s = "VFX_MAGIC_FIREBALL_EVIL.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "107 227 244";

    vistexcolorend_s = "107 227 244";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_urizel_collide(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpisvolume = 1;

    shpdim_s = "20";

    shpscalekeys_s = "1";

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 100.0;

    visname_s = "BELIARSRAGE_CLOUD.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexaniislooping = 2;

    vistexcolorstart_s = "107 227 244";

    vistexcolorend_s = "107 227 244";

    vissizestart_s = "50 50";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_deathball_init(c_particlefx) {

    ppsvalue = 55.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 25.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "193 22 13";

    vistexcolorend_s = "193 22 13";

    vissizestart_s = "8 8";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_deathball_invest(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 10 10 10 10 10 10 10 10 10 10 10 ";

    ppsislooping = 1;

    ppsfps = 3.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "80";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 800.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 0.4;

    visalphafunc_s = "BLEND";

    visalphaend = 255.0;

};



instance mfx_deathball_cast(c_particlefx) {

    ppsvalue = 300.0;

    ppsscalekeys_s = "10";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 400.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Magic_BeliarRage_Cloud.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 0.4;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_deathball_target(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "50 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_deathball_ani(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 10";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "20 20 1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.05;

    velvar = 0.025;

    lsppartavg = 3000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "BADWEATH.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "12 12";

    vissizeendscale = 3.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_deathball_flytoplayer(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "40";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "WORLD";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.3;

    velvar = 0.055;

    lsppartavg = 8000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "BADWEATH.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};
instance mfx_beliarsrage_cast(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 3.0;

    velavg = 0.1;

    velvar = 0.03;

    lsppartavg = 100.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Magic_Lightning_Beliar_A0.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};
instance mfx_beliaridol(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "3 3 3 2 2 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 1.0E-4;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "VFX_Magic_Blood.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "5 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};



instance darkconebeliar(c_particlefx) {

    ppsvalue = 2.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "15";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 1.0;

    dirmode_s = "DIR";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = 90.0;

    velavg = 0.01;

    lsppartavg = 5000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Magic_Blood.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 150";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

};



instance mfx_beliaridolpray(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "3 3 3 2 2 3 3 2 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    ppscreateem_s = "DARKCONEBELIAR";

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 1.0E-4;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "VFX_Magic_Blood.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "5 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};
instance mfx_dragonbreathofdeath(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1 10";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "1000 0 0";

    velavg = 2.0;

    velvar = 0.5;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_FIRE_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "20 0 0";

    vissizestart_s = "5 5";

    vissizeendscale = 150.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    trltexture_s = "WHITECLOUD.TGA";

};



instance mfx_dragonbreathofdeath_magic(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1 10";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "1000 0 0";

    velavg = 2.0;

    velvar = 0.5;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_MAGIC_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "20 0 0";

    vissizestart_s = "5 5";

    vissizeendscale = 150.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    trltexture_s = "WHITECLOUD.TGA";

};


instance smoke_model_ice(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_ICE_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 50.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_ice_full(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_ICE_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 150.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_moon(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";
    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "MFX_ICE_SMOKE.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 100.0;

};



instance smoke_model_sand(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "WHIRLWIND.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "128 128 128";

    vissizestart_s = "100 100";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 200.0;

};



instance smoke_model_snow(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "MAGICCLOUD_BLUE.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "128 128 128";

    vissizestart_s = "100 100";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 100.0;

};



instance smoke_model_fires(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "MAGICCLOUD_FIRE.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "128 128 128";

    vissizestart_s = "100 100";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 100.0;

};



instance smoke_model_light(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "MAGICCLOUD_WHITE.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "128 128 128";

    vissizestart_s = "100 100";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 100.0;

};



instance smoke_fog(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "51 68 22";

    vistexcolorend_s = "69 96 22";

    vissizestart_s = "50 90";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance smoke_model_fire(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_FIRE_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 50.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_fire_full(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_FIRE_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 150.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_swamp(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_SWAMP_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 50.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_swamp_full(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_SWAMP_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 150.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_redflame(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_REDFLAME_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 50.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_redflame_full(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_REDFLAME_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 150.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_magic(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_MAGIC_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 50.0;

    flockmode = "ARMOR_XARDAS.ASC";

};



instance smoke_model_magic_full(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RANDOM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 4.0E-4;

    lsppartavg = 1500.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_MAGIC_SMOKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 40";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 150.0;

    flockmode = "ARMOR_XARDAS.ASC";

};
instance ice_dragonaura(fire_sword_proto) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 180.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.1;

    lsppartavg = 300.0;

    flygravity_s = "0 0.0003 0";

    visname_s = "MAGICCLOUD_BLUE.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 100";

    vissizestart_s = "5 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance swamp_dragonaura(fire_sword_proto) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 180.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.1;

    lsppartavg = 300.0;

    flygravity_s = "0 0.0003 0";

    visname_s = "MAGICCLOUD_TRANS.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 100";

    vissizestart_s = "5 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance magic_dragonaura(fire_sword_proto) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 180.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.1;

    lsppartavg = 300.0;

    flygravity_s = "0 0.0003 0";

    visname_s = "MAGICCLOUD_MAGIC.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 100";

    vissizestart_s = "5 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance fire_dragonaura(fire_sword_proto) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 180.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.1;

    lsppartavg = 300.0;

    flygravity_s = "0 0.0003 0";

    visname_s = "MAGICCLOUD_FIRE.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 100";

    vissizestart_s = "5 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance redflame_dragonaura(fire_sword_proto) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 180.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.1;

    lsppartavg = 300.0;

    flygravity_s = "0 0.0003 0";

    visname_s = "MAGICCLOUD_REDFLAME.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 100";

    vissizestart_s = "5 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};
instance fire_spell(c_particlefx) {

    ppsvalue = 120.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "UNIFORM";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "MESH";

    dirangleheadvar = 180.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.01;

    lsppartavg = 400.0;

    flygravity_s = "0 0.0003 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "5 5";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};
instance mfx_beliarshrine(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 400 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1 2 3 4 5 6 7";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-4;

    lsppartavg = 5000.0;

    flygravity_s = "0 -0.0001 0";

    visname_s = "VFX_Magic_Blood.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "32 128";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};
instance mfx_monsterspawn_flash(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 400 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    velavg = 0.001;

    lsppartavg = 200.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "VFX_Magic_Lightning_Black_A0.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 20.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "100 500";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_monsterspawn_target(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1";

    ppsissmooth = 1;

    ppsfps = 2.5;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "300";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.6;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Magic_MONSTERSPAWN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "36 36";

    vissizeendscale = 24.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "WHITECLOUD.TGA";

};



instance mfx_waterwall_init(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1 2 1 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.5;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.001;

    velvar = 1.0E-4;

    lsppartavg = 150.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_BREATHOFDEATH.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_waterwall_wave(c_particlefx) {

    ppsvalue = 90.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80";

    ppsissmooth = 1;

    ppsfps = 80.0;

    ppscreateem_s = "MFX_WATERWALL_WAVE2";

    ppscreateemdelay = 3000.0;

    shptype_s = "CIRCLE";

    shpfor_s = "world";

    shpoffsetvec_s = "0 -50 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80";

    shpscalefps = 80.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.001;

    lsppartavg = 2350.0;

    flygravity_s = "0";

    visname_s = "MFX_BREATHOFDEATH.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "200 220 255";

    vissizestart_s = "50 50";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};



instance mfx_waterwall_wave2(c_particlefx) {

    ppsvalue = 90.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80";

    ppsissmooth = 1;

    ppsfps = 80.0;

    shptype_s = "CIRCLE";

    shpfor_s = "world";

    shpoffsetvec_s = "0 -50 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80";

    shpscalefps = 80.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 1.0E-4;

    lsppartavg = 1000.0;

    lsppartvar = 100.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_BREATHOFDEATH.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 225 255";

    vistexcolorend_s = "200 220 255";

    vissizestart_s = "50 50";

    vissizeendscale = 0.1;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};



instance mfx_waterwall_target(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    ppscreateem_s = "MFX_WATERWALL_TARGETEND";

    ppscreateemdelay = 20000.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "30 100 30";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-6;

    lsppartavg = 20000.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_BREATHOFDEATH.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_waterwall_targetend(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "30 100 30";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.1;

    velvar = 0.04;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.001 0";

    flycolldet_b = 1;

    visname_s = "MFX_BREATHOFDEATH.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 180.0;

    visalphaend = 100.0;

    mrkfadespeed = 0.1;

    mrktexture_s = "MFX_BREATHOFDEATH.TGA";

    mrksize = 20.0;

};



instance whiteeyes_left(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 -3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 200";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance whiteeyes_right(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 200";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance greeneyes_left(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 -3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 70 20";

    vistexcolorend_s = "0 0 60";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance greeneyes_right(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 70 20";

    vistexcolorend_s = "0 0 60";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance redeyes_left(c_particlefx) {

    ppsvalue = 7.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 -3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "180 70 20";

    vistexcolorend_s = "180 0 60";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance redeyes_right(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "180 70 20";

    vistexcolorend_s = "180 0 60";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};

instance mfx_ghost_candle(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 30 30";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "100";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "mfx_masterofdisaster_aura_16bit.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "0 70 20";

    vistexcolorend_s = "0 0 60";

    vissizestart_s = "100 100";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_ghost_torch(c_particlefx) {

    ppsvalue = 25.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 -30 -30";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 400";

    dirangleelev = 90.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0002 0";

    visname_s = "VFX_Env_Fire_02.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 0";

    vissizestart_s = "5 5";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_fire_torch(c_particlefx) {

    ppsvalue = 25.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "9 -30 3";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 400";

    dirangleelev = 90.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0002 0";

    visname_s = "VFX_Env_Fire_02.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 0";

    vissizestart_s = "5 5";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_warcandle(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 -15 -30";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 400";

    dirangleelev = 90.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0002 0";

    visname_s = "VFX_Env_Fire_02.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 0";

    vissizestart_s = "1 1";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_spiderweb_init(c_particlefx) {

    ppsvalue = 40.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "MODISPIDERSILK01.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 225 255";

    vissizestart_s = "20 20";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_spiderweb_cast(c_particlefx) {

    ppsvalue = 40.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 5 5";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    flygravity_s = "0 ROOTNOOSE 0";

    visname_s = "MODISPIDERSILK01.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255 ";

    vissizestart_s = "50 50";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_spiderweb_spread(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 -60 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1500";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = 90.0;

    dirangleelevvar = 10.0;

    velavg = 0.001;

    lsppartavg = 20000.0;

    visname_s = "MODISPIDERSILK03.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_spiderweb_target(c_particlefx) {

    ppsvalue = 20.0;
    ppsscalekeys_s = "1";
    ppsfps = 2.0;
    ppscreateem_s = "MFX_SPIDERWEB_BURST";
    ppscreateemdelay = 20500.0;
    shptype_s = "CIRCLE";
    shpfor_s = "WORLD";
    shpoffsetvec_s = "0 -60 0";
    shpdistribtype_s = "RAND";
    shpisvolume = 1;
	shpdim_s = "60";
    shpmeshrender_b = 1;
    shpscalekeys_s = "1";
    shpscaleissmooth = 1;
    dirmode_s = "RAND";
    dirfor_s = "WORLD";
    dirmodetargetfor_s = "OBJECT";
    dirmodetargetpos_s = "0 0 0";
    dirangleheadvar = 10.0;
    dirangleelev = 90.0;
    dirangleelevvar = 10.0;
    velavg = 0.001;
    lsppartavg = 1000.0; // czas twania   efektu na ziemi
    visname_s = "MODISPIDERSILK03.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexanifps = 18.0;
    vistexcolorstart_s = "255 255 255";
    vistexcolorend_s = "255 255 255";
    vissizestart_s = "90 90";
    vissizeendscale = 1.0;
    visalphafunc_s = "ADD";
    visalphastart = 255.0;
    visalphaend = 255.0;

};



instance mfx_spiderweb_burst(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "200";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = 90.0;

    dirangleelevvar = 10.0;

    velavg = 0.2;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.001 0";

    flycolldet_b = 3;

    visname_s = "MODISPIDERSILK03.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "100 100";

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

    useemittersfor = 1;

};



instance mfx_spiderweb_groundglow(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 400 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "500 10 500";

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = -90.0;

    dirangleelevvar = 10.0;

    velavg = 2.0;

    lsppartavg = 3000.0;

    lsppartvar = 1500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 3;

    visname_s = "MFX_SLEEP_STAR.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexcolorstart_s = "50 50 50";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "35 35";

    vissizeendscale = 0.1;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

    mrkfadespeed = 1.0;

    mrktexture_s = "MODISPIDERSILK03.TGA";

    mrksize = 100.0;

};



instance cast_guru(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 1 0";

    shpdistribtype_s = "WALK";

    shpdim_s = "5";

    shpdistribwalkspeed = 0.001;

    shpdim_s = "600 0 600";

    shpscalekeys_s = "0 1 2 0.4 1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirfor_s = "WORLD";

    velavg = 2.0E-4;

    lsppartavg = 6000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 -0.00004 0";

    flycolldet_b = 0;

    visname_s = "FLARESTAR.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "100 50 33";

    vissizestart_s = "50 50";

    vissizeendscale = 0.025;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 50.0;

};



instance mfx_dragonicecube_init(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1 2 1 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.5;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.001;

    velvar = 1.0E-4;

    lsppartavg = 150.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_FREEZE_MULTIICE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_dragonicecube_cast(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "20";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-4;

    lsppartavg = 4000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "MFX_FREEZE_MULTIICE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};
instance mfx_firewave_init(c_particlefx) {

    ppsvalue = 100.0;

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1 2 3 3 2 2 2 1 2 3 2 3 4 3 2 1 2 3 2 1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.001;

    velvar = 1.0E-4;

    lsppartavg = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "FIREBALL16BIT_A11.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "200 150 0";

    vissizestart_s = "5 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_firewave_lefthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    velavg = 0.001;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "FIREBALL16BIT_A11.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "200 150 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_firewave_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "FIREBALL16BIT_A11.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "200 150 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_firewave_init_glow(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1 2 1 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.5;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.6;

    velvar = 0.02;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_Spell_Star.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "200 150 0";

    vissizestart_s = "1 1";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.8;

    trltexture_s = "FIREBALL16BIT_A11.TGA";

    trlwidth = 1.0;

};



instance mfx_firewave_explosion(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.01;

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0";

    visname_s = "FIREBALL16BIT_A11.TGA";

    visorientation_s = "VELO";

    vistexanifps = 2.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "200 150 0";

    vissizestart_s = "1 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_firewave_cast(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";

    ppsissmooth = 1;

    ppsfps = 15.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 -50 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "40";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20";

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 1.0E-4;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00008 0";

    visname_s = "WHITECLOUD.TGA";

    visorientation_s = "VELO";

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "200 150 0";

    vissizestart_s = "25 25";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

    trltexture_s = "FIREBALL16BIT_A11.TGA";

};



instance mfx_firewave_target(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1 1 0.8 0.6 0.4 0.2";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 -100 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 1.0E-4;

    lsppartavg = 2500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "WHITECLOUD.TGA";

    visorientation_s = "NONE";

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "200 150 0";

    vissizestart_s = "100 200";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

    trltexture_s = "FIREBALL16BIT_A11.TGA";

};



instance mfx_bloodrain_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "BQM_SCAVENGER.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "15 15";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 50.0;

    useemittersfor = 1;

};



instance mfx_bloodrain_investglow(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1";

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "50 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_bloodrain_rain(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1 1 1 1 1 0.8 0.7 0.6 0.5 0.4 0.3 0.2 0.1";

    ppsfps = 2.0;

    ppscreateem_s = "MFX_BLOODRAIN_GROUND";

    ppscreateemdelay = 4000.0;

    shptype_s = "CIRCLE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 1000 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1000";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    diranglehead = 10.0;

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 0.7;

    velvar = 0.3;

    lsppartavg = 2000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0002 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "155 0 0";

    vistexcolorend_s = "155 0 0";

    vissizestart_s = "25 80";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

    trlwidth = 25.0;

};



instance mfx_bloodrain_ground(c_particlefx) {

    ppsvalue = 35.0;

    ppsscalekeys_s = "1 1 1 1 1 1 0.8 0.6 0.4 0.2";

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 -120 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1000";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleelev = 90.0;

    velavg = 0.03;

    lsppartavg = 2000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 3;

    visname_s = "BQM_SCAVENGER.TGA";

    visorientation_s = "0";

    vistexisquadpoly = 1;

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "50 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "BLEND";

    visalphaend = 255.0;

    trltexture_s = "BQM_SCAVENGER.TGA";

};



instance mfx_bloodrain_target(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "50 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};
instance mfx_icerain_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 20 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 40.0;

    dirangleelev = -89.0;

    velavg = 1.0E-4;

    lsppartavg = 100.0;

    lsppartvar = 0.0;

    flygravity_s = "0 -0.003 0";

    visname_s = "ICEXFLARE.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "2 5";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_icerain_investglow(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "100 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "10 1000 10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = -89.0;

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 100.0;

    flygravity_s = "0 0.001 0";

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 255 255";

    vistexcolorend_s = "0 0 255";

    vissizestart_s = "6 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_icerain_rain(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 1 1 1 1 0.8 0.7 0.6 0.5 0.4 0.3 0.3 0.3 0.3";

    ppsfps = 5.0;

    shptype_s = "CIRCLE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 1000 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1000";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 25.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    diranglehead = 10.0;

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 0.6;

    velvar = 0.1;

    lsppartavg = 1000.0;

    lsppartvar = 500.0;

    flygravity_s = "0.0001 -0.0004 0.0000";

    visname_s = "Mfx_Freeze_MultiIce.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "70 113 255";

    vistexcolorend_s = "29 67 155";

    vissizestart_s = "8 80";

    vissizeendscale = 15.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_icerain_ground(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1 1 1 1 1 1 0.8 0.6 0.4 0.2";

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 -120 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1000";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleelev = 90.0;

    velavg = 0.03;

    lsppartavg = 2000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 3;

    visname_s = "ICEXFLARE.TGA";

    visorientation_s = "0";

    vistexisquadpoly = 1;

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "50 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

    trltexture_s = "ICEXFLARE.TGA";

    mrktexture_s = "=";

};



instance mfx_icerain_target(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "30 30 30";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.1;

    velvar = 0.04;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.001 0";

    flycolldet_b = 1;

    visname_s = "MFX_FREEZE_ICEQUADMARK.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 180.0;

    visalphaend = 100.0;

    mrkfadespeed = 0.1;

    mrktexture_s = "MFX_FREEZE_ICEQUADMARK.TGA";

    mrksize = 1.0;

};



instance mfx_magsphere_init(c_particlefx) {

    ppsvalue = 75.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 30 172";

    vistexcolorend_s = "25 30 172";

    vissizestart_s = "9 9";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_magsphere_cast(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "5 3 5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 30 172";

    vistexcolorend_s = "25 30 172";

    vissizestart_s = "8 8";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_magsphere_collide(c_particlefx) {

    ppsvalue = 10.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "VFX_Magic_BigGlow_Evil.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "74 30 172";

    vistexcolorend_s = "74 30 172";

    vissizestart_s = "10 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_stonefirst_init(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "6";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "25";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.01;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_QUAKE.TGA";

    visorientation_s = "VELO";

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "24 24 24";

    vistexcolorend_s = "24 24 24";

    vissizestart_s = "7 8";

    vissizeendscale = 7.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_stonefirst_cast(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_QUAKE.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "6 6";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_stonefirst_spread_small(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppscreateemdelay = 1.0;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "WALK";

    shpisvolume = 1;

    shpdim_s = "0.01";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 21.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_QUAKE.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexisquadpoly = 1;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 225.0;

    visalphaend = 220.0;

};



instance mfx_stonefirst_collide_sparks(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.2;

    velvar = 0.05;

    lsppartavg = 5000.0;

    flygravity_s = "0 -0.0005 0";

    flycolldet_b = 1;

    visname_s = "MFX_QUAKE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "10 10";

    vissizeendscale = 0.1;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_stonefirst_collide3(mfx_fireball_collide_proto) {

    ppsvalue = 30.0;

    lsppartavg = 1800.0;

    vissizeendscale = 14.0;

    visalphastart = 220.0;

    ppscreateem_s = "MFX_STONEFIRST_COLLIDE_SPARKS";

};



instance mfx_quakesplash_init(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 20 0";

    shpdim_s = "2";

    shpscalekeys_s = "1";

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 150.0;

    lsppartvar = 50.0;

    flygravity_s = "0 -0.000005 0";

    flycolldet_b = 1;

    visname_s = "";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_quakesplash_cast(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40";

    ppsissmooth = 1;

    ppsfps = 80.0;

    shptype_s = "CIRCLE";

    shpfor_s = "world";

    shpoffsetvec_s = "0 -150 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40";

    shpscalefps = 80.0;

    dirmode_s = "NONE";

    dirfor_s = "object";

    velavg = 0.001;

    lsppartavg = 2350.0;

    flygravity_s = "0 0.0002 0";

    visname_s = "";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "230 195 122";

    vistexcolorend_s = "209 180 164";

    vissizestart_s = "10 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 150.0;

};



instance mfx_splashsword_init(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "255 100 0";

    vissizestart_s = "6 6";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance blueeyes_left(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 -3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 200";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance blueeyes_right(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "11 3 10";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 0.0;

    dirangleelev = 0.0;

    velavg = 1.0E-4;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 200";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "3 3";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_fear_wings_blue(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "200";

    shpmesh_s = "MFX_FEAR4.3DS";

    shpmeshrender_b = 2;

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.01;

    velvar = 0.005;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_FIREBALL.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "47 120 216";

    vistexcolorend_s = "47 120 216";

    vissizestart_s = "25 25";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_fear_wings2_blue(c_particlefx) {

    ppsvalue = 25.0;

    ppsscalekeys_s = "1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "MESH";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "200";

    shpmesh_s = "MFX_FEAR4.3DS";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.01;

    velvar = 0.005;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_FIREBALL.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "47 120 216";

    vistexcolorend_s = "47 120 216";

    vissizestart_s = "25 25";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_greenstrike_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 555.0;

    lsppartvar = 501.0;

    flygravity_s = "0 0 0";

    visname_s = "WATERLIGHT.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 128 0";

    vistexcolorend_s = "0 128 0";

    vissizestart_s = "8 16";

    vissizeendscale = 7.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_greenstrike_cast(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 5 5";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "66 255 25";

    vistexcolorend_s = "66 255 25";

    vissizestart_s = "6 12";

    vissizeendscale = 7.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.5;

    trltexture_s = "THUNDERSTORM_LIGHTNING.TGA";

    trlwidth = 1.0;

    useemittersfor = 1;

};



instance mfx_greenstrike_collide(c_particlefx) {

    ppsvalue = 30.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 164 25";

    vistexcolorend_s = "25 164 25";

    vissizestart_s = "10 10";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_firelance_init(c_particlefx) {

    ppsvalue = 40.0;

    ppsscalekeys_s = "2 2 2 2 2 2";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "12";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.001;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "FIREFLARE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 128 128";

    vistexcolorend_s = "25 25 25";

    vissizestart_s = "7 2";

    vissizeendscale = 14.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_firelance_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1 2 1 2";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 25 5";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.0;

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    lsppartavg = 600.0;

    flygravity_s = "0 0 0";

    visname_s = "FIREFLARE.TGA";

    visorientation_s = "VELO";

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "2 8";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.1;

    trltexture_s = "SKYRAIN.TGA";

    trlwidth = 6.0;

    useemittersfor = 1;

};



instance mfx_firelance_collide(c_particlefx) {

    ppsvalue = 20.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "FIREFLARE.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 220 220";

    vistexcolorend_s = "255 220 220";

    vissizestart_s = "5 5";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_deathstrike_init(c_particlefx) {

    ppsvalue = 122.0;

    ppsscalekeys_s = "1 2 1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "12";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 25.0;

    flygravity_s = "0 0 0";

    visname_s = "ONION_TENTACLES.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "25 25 0";

    vissizestart_s = "15 15";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 111.0;

    useemittersfor = 1;

};



instance mfx_deathstrike_cast(c_particlefx) {

    ppsvalue = 300.0;

    ppsscalekeys_s = "1 2 1 2";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 5 5";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "12";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    lsppartavg = 500.0;

    velavg = 0.008;

    velvar = 0.001;

    flygravity_s = "0 0 0";

    visname_s = "ONION_TENTACLES.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "25 25 0";

    vissizestart_s = "15 15";

    vissizeendscale = 5.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_deathstrike_collide(c_particlefx) {

    ppsvalue = 30.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "ONION_TENTACLES.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "25 25 0";

    vissizestart_s = "10 10";

    vissizeendscale = 8.0;

    visalphafunc_s = "BLEND";

};



instance mfx_gurumass_init(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "14";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 501.0;

    flygravity_s = "0 0 0";

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "52 71 166";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "12 12";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_gurumass_cast(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 5 5";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.3;

    shpisvolume = 1;

    shpdim_s = "12";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "52 71 166";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "25 25";

    vissizeendscale = 7.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.5;

    useemittersfor = 1;

};



instance mfx_gurumass_spread(c_particlefx) {

    ppsvalue = 111.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 6;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "45";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "52 71 166";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "12 12";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_gurumass_collide(c_particlefx) {

    ppsvalue = 45.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 6;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "45";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "55 71 199";

    vistexcolorend_s = "55 71 199";

    vissizestart_s = "15 15";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_concussionbolt_init(c_particlefx) {

    ppsvalue = 55.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-4;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 25 255";

    vistexcolorend_s = "25 25 255";

    vissizestart_s = "16 12";

    vissizeendscale = 16.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_concussionbolt_cast(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 25 255";

    vistexcolorend_s = "25 25 255";

    vissizestart_s = "15 15";

    vissizeendscale = 15.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_concussionbolt_collide(c_particlefx) {

    ppsvalue = 50.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.001;

    velvar = 0.001;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "WATERFIST_EXPLOSION.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 25 255";

    vistexcolorend_s = "25 25 255";

    vissizestart_s = "10 10";

    vissizeendscale = 15.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_darkheal_init(c_particlefx) {

    ppsvalue = 100.0;

    ppsislooping = 1;

    ppsissmooth = 0;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "world";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpdim_s = "6";

    shpscalekeys_s = "2 1.5 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 1.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    lsppartavg = 500.0;

    visname_s = "TELSTURM.TGA";

    vistexcolorstart_s = "255 20 40";

    vistexcolorend_s = "50 0 255";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 245.0;

};



instance mfx_darkheal_cast(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1 1 1 1 1";

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpmeshrender_b = 1;

    shpscalekeys_s = "300 1";

    shpscalefps = 10.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    lsppartavg = 5000.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 20 40";

    vistexcolorend_s = "50 0 255";

    vissizestart_s = "2 10";

    vissizeendscale = 25.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_darkheal_heavenlight(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 400 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1 2 3 4 5 6 7";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-4;

    lsppartavg = 5000.0;

    flygravity_s = "0 -0.0001 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 20 40";

    vistexcolorend_s = "50 0 255";

    vissizestart_s = "32 128";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_icespell_target_magicarrow(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    ppscreateem_s = "MFX_ICESPELL_TARGETEND_MAGICARROW";

    ppscreateemdelay = 3000.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50 50 50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-6;

    lsppartavg = 3000.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_FREEZE_MULTIICE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "10 10";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 110.0;

    visalphaend = 220.0;

    useemittersfor = 1;

};



instance mfx_icespell_targetend_magicarrow(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "30 100 30";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.1;

    velvar = 0.04;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.001 0";

    flycolldet_b = 1;

    visname_s = "MFX_FREEZE_ICEQUADMARK.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 180.0;

    visalphaend = 100.0;

    mrkfadespeed = 0.1;

    mrktexture_s = "MFX_FREEZE_ICEQUADMARK.TGA";

    mrksize = 20.0;

};



instance mfx_cbow_explosive(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "WALK";

    shpdistribwalkspeed = 0.01;

    shpisvolume = 1;

    shpdim_s = "200";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "TARGET";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-4;

    lsppartavg = 1000.0;

    lsppartvar = 15.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_FIREBALL.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexcolorstart_s = "234 104 20";

    vistexcolorend_s = "234 104 20";

    vissizestart_s = "15 15";

    vissizeendscale = 15.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    visalphaend = 60.0;

    flockmode = "WIND";

    flockstrength = 0.05;

};



instance freeaim_trail(c_particlefx) {

    ppsvalue = 100.0;

    ppsislooping = 1;

    ppsscalekeys_s = "1";

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 270.0;

    dirangleheadvar = 0.0;

    dirangleelevvar = 0.0;

    velavg = 1.0E-7;

    lsppartavg = 300.0;

    lsppartvar = 1.0E-7;

    flygravity_s = "0 0 0";

    visname_s = "SMK_16BIT_A0.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexaniislooping = 0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "2 2";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphastart = 200.0;

    trlfadespeed = 0.5;

    trltexture_s = "SMK_16BIT_A0.TGA";

    trlwidth = 3.0;

    useemittersfor = 1;

};



instance freeaim_impact(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 20.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 1 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0.1 -0.1 0";

    diranglehead = 180.0;

    dirangleheadvar = 10.0;

    dirangleelev = 180.0;

    dirangleelevvar = 10.0;

    velavg = 0.12;

    velvar = 0.06;

    lsppartavg = 2500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0003 0";

    flycolldet_b = 1;

    visorientation_s = "VELO3D";

    vistexisquadpoly = 0;

    visname_s = "CPFX_WOOD.TGA";

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "8 8";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 50.0;

};



instance mfx_imarah_red(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1 1 1 1 1 1";

    ppsislooping = 0;

    ppsissmooth = 0;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 150 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "255 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_imarah_green(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1 1 1 1 1 1";

    ppsislooping = 0;

    ppsissmooth = 0;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 150 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "15 255 0";

    vistexcolorend_s = "15 255 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_specialattack_07(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1 1 1 1 1 1";

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 150 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.1;

    velvar = 0.01;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 0 100";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_imarah_firebolt_init(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "SHADOWBEAST_FIRE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 128 128";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "4 4";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_imarah_firebolt_cast(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    ppscreateem_s = "";

    ppscreateemdelay = 0.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 5 5";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "5";

    shpmesh_s = "";

    shpmeshrender_b = 0;

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 0.0;

    dirangleheadvar = 180.0;

    dirangleelev = 0.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    velvar = 0.0;

    lsppartavg = 500.0;

    lsppartvar = 0.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "SHADOWBEAST_FIRE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 0;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 200 200";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "6 6";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 0.0;

    trlfadespeed = 0.5;

    trltexture_s = "";

    trlwidth = 0.0;

    mrkfadespeed = 0.0;

    mrktexture_s = "";

    mrksize = 0.0;

    flockmode = "";

    flockstrength = 0.0;

    useemittersfor = 1;

    timestartend_s = "";

    m_bisambientpfx = 0;

};



instance mfx_imarah_firebolt_collide(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "";

    ppsislooping = 0;

    ppsissmooth = 0;

    ppsfps = 10.0;

    ppscreateem_s = "";

    ppscreateemdelay = 0.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.0;

    shpisvolume = 1;

    shpdim_s = "8";

    shpmesh_s = "";

    shpmeshrender_b = 0;

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 0.0;

    dirangleheadvar = 180.0;

    dirangleelev = 0.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 1000.0;

    lsppartvar = 0.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "FIREFLARE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 0;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 220 220";

    vistexcolorend_s = "255 220 220";

    vissizestart_s = "10 10";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 0.0;

    trlfadespeed = 0.0;

    trltexture_s = "";

    trlwidth = 0.0;

    mrkfadespeed = 0.0;

    mrktexture_s = "";

    mrksize = 0.0;

    flockmode = "";

    flockstrength = 0.0;

    useemittersfor = 0;

    timestartend_s = "";

    m_bisambientpfx = 0;

};



instance mfx_specialattack02_cloud(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1 1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 9.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "300";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.6;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "LIGHTNING_ORIGIN_A0.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "30 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "WHITECLOUD.TGA";

};



instance mfx_specialattack02_electrowave_init(c_particlefx) {

    ppsvalue = 100.0;

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1 2 3 3 2 2 2 1 2 3 2 3 4 3 2 1 2 3 2 1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.001;

    velvar = 1.0E-4;

    lsppartavg = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "5 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_specialattack02_electrowave_lefthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    velavg = 0.001;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_specialattack02_electrowave_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_specialattack02_electrowave_init_glow(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1 2 1 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.5;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.6;

    velvar = 0.02;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_Spell_Star.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "1 1";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.8;

    trltexture_s = "LIGHTNING_BIG_A2.TGA";

    trlwidth = 1.0;

};



instance mfx_specialattack02_electrowave_explosion(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.01;

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "VELO";

    vistexanifps = 2.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "1 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_specialattack02_electrowave_cast(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "120";

    shpscalekeys_s = "1 2 3 4 5 6";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00008 0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "10 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};



instance mfx_specialattack02_electrowave_target(c_particlefx) {

    ppsvalue = 40.0;

    ppsscalekeys_s = "4 3 2 1";

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 150.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_THUNDERSPELL_ELECTRO.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "70 70";

    vissizeendscale = 1.5;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_likerh_green(c_particlefx) {

    ppsvalue = 70.0;

    ppsscalekeys_s = "1";

    ppsislooping = 0;

    ppsissmooth = 0;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 125 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-6;

    lsppartavg = 1500.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "15 255 0";

    vistexcolorend_s = "15 255 0";

    vissizestart_s = "50 50";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_likerh_yellow(c_particlefx) {

    ppsvalue = 70.0;

    ppsscalekeys_s = "1";

    ppsislooping = 0;

    ppsissmooth = 0;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 125 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-6;

    lsppartavg = 1500.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 15";

    vistexcolorend_s = "255 255 15";

    vissizestart_s = "50 50";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_ud_deathball_init(c_particlefx) {

    ppsvalue = 55.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 25.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "13 22 60";

    vistexcolorend_s = "13 22 60";

    vissizestart_s = "8 8";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_ud_deathball_invest(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 10 10 10 10 10 10 10 10 10 10 10 ";

    ppsislooping = 1;

    ppsfps = 3.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "80";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 800.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "0 0 60";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 0.4;

    visalphafunc_s = "BLEND";

    visalphaend = 255.0;

};



instance mfx_ud_deathball_cast(c_particlefx) {

    ppsvalue = 300.0;

    ppsscalekeys_s = "10";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 400.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Magic_BeliarRage_Cloud.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "0 0 60";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 0.4;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_ud_deathball_target(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "0 0 60";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "50 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_ud_deathball_ani(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 10";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "20 20 1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.05;

    velvar = 0.025;

    lsppartavg = 3000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "BADWEATH.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 60";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "12 12";

    vissizeendscale = 3.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_ud_deathball_flytoplayer(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "40";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "WORLD";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.3;

    velvar = 0.055;

    lsppartavg = 8000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "BADWEATH.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};
instance cannon_strike_smoke(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "WALK";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "1";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "TARGET";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-4;

    lsppartavg = 3000.0;

    lsppartvar = 10.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_BREATHOFDEATH.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 30.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    visalphaend = 30.0;

    flockmode = "WIND";

    flockstrength = 0.05;

};



instance cannon_fire(c_particlefx) {

    ppsvalue = 300.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 1 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    diranglehead = 45.0;

    dirangleheadvar = 10.0;

    dirangleelev = 45.0;

    dirangleelevvar = 90.0;

    velavg = 0.001;

    velvar = 0.25;

    lsppartavg = 4000.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.0008 0";

    flycolldet_b = 3;

    visname_s = "CPFX_WOOD.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "8 8";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance cannon_wood_damage(c_particlefx) {

    ppsvalue = 400.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 1 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "10";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    diranglehead = 35.0;

    dirangleheadvar = 90.0;

    dirangleelev = 90.0;

    dirangleelevvar = 120.0;

    velavg = 0.006;

    velvar = 0.7;

    lsppartavg = 4500.0;

    lsppartvar = 50.0;

    flygravity_s = "0 -0.002 0";

    visname_s = "PLAGUE3.TGA";

    visorientation_s = "VEL";

    vistexisquadpoly = 1;

    vistexanifps = 15.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "77 41 12";

    vistexcolorend_s = "77 41 12";

    vissizestart_s = "3 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

    trlfadespeed = 1.0;

    trltexture_s = "RootNoose_Burst";

    trlwidth = 2.0;

    mrkfadespeed = 0.2;

    mrksize = 2.0;

    flockmode = "WIND";

    flockstrength = 0.01;

};



instance mfx_slowdown_origin(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1 1 1 1 1 1";

    ppsislooping = 0;

    ppsissmooth = 0;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 150 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 3.0E-4;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 120 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance smoke_soul_fog(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 2 3 2 1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "=";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "0.1 1 2 3";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirangleheadvar = 5.0;

    dirangleelev = 90.0;

    dirangleelevvar = 5.0;

    velavg = 0.1;

    lsppartavg = 1200.0;

    lsppartvar = 1200.0;

    flygravity_s = "0.000001 0 0";

    visname_s = "GROUND_SMOKE.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "234 21 0";

    vistexcolorend_s = "234 21 0";

    vissizestart_s = "12 52";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 220.0;

    trlfadespeed = 1.0;

    trltexture_s = "THUNDERSTORM_LIGHTNING.TGA";

    trlwidth = 5.0;

    mrktexture_s = "KOPFBALL2.TGA";

    flockmode = "NONE";

    flockstrength = 2.0;

};
instance mfx_abyssspell_init(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "PESTILENCE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 255 255";

    vissizestart_s = "8 8";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_abyssspell_invest(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 10 10 10 10 10 10 10 10 10 10 10 ";

    ppsislooping = 1;

    ppsfps = 3.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "80";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 800.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 0.4;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

};



instance mfx_abyssspell_cast(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "15";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "PESTILENCE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_abyssspell_target(c_particlefx) {

    ppsvalue = 20.0;
    ppsscalekeys_s = "1";
    ppsissmooth = 1;
    ppsfps = 1.0;
	ppscreateem_s = "MFX_abyssspell_TARGET_EXPLODE";
    ppscreateemdelay = 1.0;
    shptype_s = "SPHERE";
    shpfor_s = "object";
    shpoffsetvec_s = "0 0 0";
    shpdistribtype_s = "RAND";
    shpisvolume = 1;
    shpdim_s = "1";
    shpscalekeys_s = "1";
    shpscaleislooping = 1;
    shpscaleissmooth = 1;
    shpscalefps = 21.0;
    dirmode_s = "TARGET";
    dirfor_s = "object";
    dirmodetargetfor_s = "OBJECT";
    dirmodetargetpos_s = "0 0 0";
    dirangleheadvar = 180.0;
    dirangleelevvar = 180.0;
    velavg = 0.003;
    velvar = 0.001;
    lsppartavg = 500.0;
    flygravity_s = "0 0 0";
    visname_s = "PESTILENCE.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexanifps = 18.0;
    vistexaniislooping = 1;
    vistexcolorstart_s = "255 255 255";
    vistexcolorend_s = "0 255 255";
    vissizestart_s = "20 20";
    vissizeendscale = 10.0;
    visalphafunc_s = "ADD";
    visalphastart = 225.0;
    visalphaend = 220.0;

};
instance MFX_abyssspell_TARGET_EXPLODE(C_PARTICLEFX)
{
	ppsvalue = 40;//20
	ppsscalekeys_s = "1 1";
	ppsissmooth = 1;
	ppsfps = 5;//2.5
	shptype_s = "POINT";
	shpfor_s = "object";
	shpoffsetvec_s = "0 0 0";
	shpdistribtype_s = "RAND";
	shpdim_s = "300";
	shpmeshrender_b = 1;
	shpscalekeys_s = "1";
	shpscaleislooping = 1;
	shpscaleissmooth = 1;
	shpscalefps = 0.6;
	dirmode_s = "RAND";
	dirfor_s = "object";
	dirmodetargetfor_s = "OBJECT";
	dirmodetargetpos_s = "0 0 0";
	dirangleheadvar = 180;
	dirangleelevvar = 180;
	velavg = 0.01;
	velvar = 0.0001;
	lsppartavg = 900;
	flygravity_s = "0 0 0";
	visname_s = "PESTILENCE.TGA";
	visorientation_s = "VELO";
	vistexisquadpoly = 1;
	vistexanifps = 18;
	vistexaniislooping = 1;
    vistexcolorstart_s = "255 255 255";
    vistexcolorend_s = "0 255 255";
	vissizestart_s = "30 30";
	vissizeendscale = 10;
	visalphafunc_s = "ADD";
	visalphastart = 255;
	trltexture_s = "WHITECLOUD.TGA";
};



instance mfx_abyssspell_ani(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 10";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "20 20 1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.05;

    velvar = 0.025;

    lsppartavg = 3000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "GEYSER.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "12 12";

    vissizeendscale = 3.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_abyssspell_flytoplayer(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "40";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "WORLD";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.3;

    velvar = 0.055;

    lsppartavg = 8000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "GEYSER.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_agro_init(c_particlefx) {

    ppsvalue = 75.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "7";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VEL";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "171 65 233";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "5 5";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_agro_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "4";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "NONE";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 0.03;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "63 42 192";

    vistexcolorend_s = "209 170 128";

    vissizestart_s = "5 5";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_agro_collide(c_particlefx) {

    ppsvalue = 20.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "24 22 233";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "5 5";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_bigdarkball_init(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "2";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "21 21 255";

    vistexcolorend_s = "174 84 255";

    vissizestart_s = "7 7";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 220.0;

};



instance mfx_bigdarkball_cast(c_particlefx) {

    ppsvalue = 125.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "14";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "21 21 255";

    vistexcolorend_s = "105 63 171";

    vissizestart_s = "12 12";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 25.0;

};



instance mfx_bigdarkball_collide(c_particlefx) {

    ppsvalue = 30.0;

    ppsfps = 10.0;

    ppscreateem_s = "MFX_FIREBALL_COLLIDE_WALLGLOW";

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 1400.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 25 255";

    vistexcolorend_s = "130 25 255";

    vissizestart_s = "12 12";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 230.0;

};



instance mfx_darkball_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "2";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "21 21 255";

    vistexcolorend_s = "174 84 255";

    vissizestart_s = "5 5";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

};



instance mfx_darkball_cast(c_particlefx) {

    ppsvalue = 125.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "12";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "21 21 255";

    vistexcolorend_s = "105 63 171";

    vissizestart_s = "9 9";

    vissizeendscale = 9.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 25.0;

};



instance mfx_darkball_collide(c_particlefx) {

    ppsvalue = 30.0;

    ppsfps = 10.0;

    ppscreateem_s = "MFX_FIREBALL_COLLIDE_WALLGLOW";

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 1400.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "25 25 255";

    vistexcolorend_s = "130 25 255";

    vissizestart_s = "10 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 230.0;

};



instance mfx_darkwave_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1 2 3 2";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 25.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_HUMANCONTROL.TGA";

    visorientation_s = "VEL";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "193 63 244";

    vistexcolorend_s = "63 227 168";

    vissizestart_s = "7 7";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 190.0;

    useemittersfor = 1;

};



instance mfx_darkwave_cast(c_particlefx) {

    ppsvalue = 125.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 800.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "126 147 234";

    vistexcolorend_s = "189 105 150";

    vissizestart_s = "45 45";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    trltexture_s = "DECAL_EARTHQUAKE_DISABLED.TGA";

    flockmode = "NONE";

};



instance mfx_darkwave_spread(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 0;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "500";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 1200.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_MAGIC_CLOUD.TGA";

    visorientation_s = "VEL";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "150 21 213";

    vistexcolorend_s = "129 147 129";

    vissizestart_s = "25 25";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    trltexture_s = "VFX_MAGIC_ADANOS_DARK_CLOUD.TGA";

    flockmode = "NONE";

};



instance mfx_darkwave_collide(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 0;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "500";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 800.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_MAGIC_CLOUD.TGA";

    visorientation_s = "ADD";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "150 21 213";

    vistexcolorend_s = "129 147 129";

    vissizestart_s = "25 25";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 225.0;

    trltexture_s = "VFX_MAGIC_ADANOS_DARK_CLOUD.TGA";

    flockmode = "NONE";

};



instance mfx_darkcontrol_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_EARTHQUAKE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "192 106 212";

    vistexcolorend_s = "255 21 23";

    vissizestart_s = "6 6";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    visalphaend = 20.0;

    useemittersfor = 1;

};



instance mfx_darkcontrol_cast(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 0.03;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_EARTHQUAKE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "213 65 65";

    vistexcolorend_s = "171 63 128";

    vissizestart_s = "4 4";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_darkcontrol_collide(c_particlefx) {

    ppsvalue = 10.0;

    ppsislooping = 0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_EARTHQUAKE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "234 104 128";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "10 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_darkspear_init(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "LINE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = 180.0;

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "237 58 66";

    vistexcolorend_s = "227 21 171";

    vissizestart_s = "8 8";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 10.0;

    useemittersfor = 1;

};



instance mfx_darkspear_cast(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.1;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexcolorstart_s = "227 58 66";

    vistexcolorend_s = "1 1 1";

    vissizestart_s = "15 65";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 235.0;

};



instance mfx_darkspear_collide(c_particlefx) {

    ppsvalue = 30.0;

    ppsfps = 10.0;

    ppscreateem_s = "MFX_FIREBALL_COLLIDE_WALLGLOW";

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 1400.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 1;

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "227 58 66";

    vistexcolorend_s = "130 25 255";

    vissizestart_s = "16 16";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

};



instance mfx_dot_first_init(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "1 2 1 2";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "6";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "NONE";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "DESTROYUNDEAD2.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "42 21 168";

    vistexcolorend_s = "150 108 121";

    vissizestart_s = "4 5";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 60.0;

    useemittersfor = 1;

};



instance mfx_dot_first_cast(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 0.03;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "DESTROYUNDEAD2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "24 44 233";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "4 4";

    vissizeendscale = 4.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 30.0;

    useemittersfor = 1;

};



instance mfx_dot_first_collide(c_particlefx) {

    ppsvalue = 10.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "DESTROYUNDEAD2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "24 44 233";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "5 5";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_dot_second_init(c_particlefx) {

    ppsvalue = 75.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.003;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 50.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_INVISIBLE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "87 44 128";

    vistexcolorend_s = "148 126 128";

    vissizestart_s = "7 7";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_dot_second_cast(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 0.03;

    lsppartavg = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_INVISIBLE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "128 64 233";

    vistexcolorend_s = "150 65 125";

    vissizestart_s = "5 5";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_dot_second_collide(c_particlefx) {

    ppsvalue = 10.0;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_INVISIBLE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "129 107 128";

    vistexcolorend_s = "255 128 128";

    vissizestart_s = "10 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_golemskill_cast(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "200";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00006 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "100 220 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_Pyrokinesis_TargetTrail.TGA";

};



instance mfx_dark_invis_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "87 45 234";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 9";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dark_invis_righthand(c_particlefx) {

    ppsvalue = 25.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "87 24 234";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "4 10";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dark_invis_cast(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "1 3 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "120";

    shpscalekeys_s = "1 3 5";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "87 24 234";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_FIRERAIN_RAINTRAIL.TGA";

};

instance mfx_massagro_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "14";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 501.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 29 145";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "8 8";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    visalphaend = 10.0;

    useemittersfor = 1;

};



instance mfx_massagro_cast(c_particlefx) {

    ppsvalue = 75.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 5 5";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VEL";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "199 71 166";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "12 12";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    trlfadespeed = 0.5;

    useemittersfor = 1;

};



instance mfx_massagro_collide(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexcolorstart_s = "223 71 199";

    vistexcolorend_s = "55 71 199";

    vissizestart_s = "12 12";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    visalphaend = 25.0;

};



instance mfx_massagro_spread(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "KOPFBALL2.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexcolorstart_s = "223 71 199";

    vistexcolorend_s = "55 71 199";

    vissizestart_s = "12 12";

    vissizeendscale = 12.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    visalphaend = 25.0;

};



instance mfx_massdot_init(c_particlefx) {

    ppsvalue = 75.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 501.0;

    flygravity_s = "0 0 0";

    visname_s = "ELECTRIC_A7.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "136 71 166";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "6 5";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 100.0;

    useemittersfor = 1;

};



instance mfx_massdot_cast(c_particlefx) {

    ppsvalue = 85.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "DECAL_INSANE.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "71 45 211";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "12 12";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 50.0;

    trlfadespeed = 0.5;

    useemittersfor = 1;

};



instance mfx_massdot_spread(c_particlefx) {

    ppsvalue = 75.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 6;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "45";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "DECAL_INSANE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "52 71 166";

    vistexcolorend_s = "52 71 166";

    vissizestart_s = "15 15";

    vissizeendscale = 15.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_massdot_collide(c_particlefx) {

    ppsvalue = 45.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 6;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "45";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "DECAL_INSANE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "55 71 199";

    vistexcolorend_s = "55 71 199";

    vissizestart_s = "25 25";

    vissizeendscale = 15.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_darksleep_init(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.03;

    lsppartavg = 1400.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_SLEEP_STAR.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "63 45 192";

    vistexcolorend_s = "189 108 129";

    vissizestart_s = "8 8";

    vissizeendscale = 0.01;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 200.0;

};



instance mfx_darksleep_origin(c_particlefx) {

    ppsvalue = 400.0;

    ppsfps = 10.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "15";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.1;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_SLEEP_STAR.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "63 45 192";

    vistexcolorend_s = "189 45 192";

    vissizestart_s = "20 20";

    vissizeendscale = 0.01;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_darksleep_target(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 0.7 0.4";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 120 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 25.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    lsppartavg = 3000.0;

    flygravity_s = "0 -0.00003 0";

    visname_s = "MFX_SLEEP_STAR.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "63 45 192";

    vistexcolorend_s = "181 105 137";

    vissizestart_s = "20 20";

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_torture_init(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpscalekeys_s = "1";

    dirmode_s = "NONE";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "DECAL_INVISIBLE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "227 65 213";

    vistexcolorend_s = "143 128 255";

    vissizestart_s = "8 8";

    vissizeendscale = 7.0;

    visalphafunc_s = "ADD";

    visalphastart = 230.0;

    useemittersfor = 1;

};



instance mfx_torture_cast(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpscalekeys_s = "1";

    dirmode_s = "NONE";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "KOPFBALL.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "277 66 233";

    vistexcolorend_s = "135 147 87";

    vissizestart_s = "15 15";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_torture_target(c_particlefx) {

    ppsvalue = 3.0;

    ppsscalekeys_s = "10 9 8 7 6 5 4 3 2 1";

    ppsissmooth = 1;

    ppsfps = 4.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpscalekeys_s = "1";

    dirmode_s = "NONE";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.001;

    lsppartavg = 800.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "KOPFBALL.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "143 128 255";

    vistexcolorend_s = "143 128 255";

    vissizestart_s = "15 15";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_blink_init(c_particlefx) {

    ppsvalue = 350.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpdim_s = "8";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 5 0";

    shpscalekeys_s = "1";

    shpisvolume = 1;

    dirmode_s = "NONE";

    dirfor_s = "OBJECT";

    velavg = 0.08;

    lsppartavg = 400.0;

    lsppartvar = 0.0;

    visname_s = "MFX_MASTEROFDISASTER_AURA_16BIT.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "250 180 150";

    vistexcolorend_s = "40 100 250";

    vissizestart_s = "6 6";

    vissizeendscale = 2.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 10.0;

    useemittersfor = 1;

};



instance mfx_blink_dest(c_particlefx) {

    ppsvalue = 400.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 25 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 0;

    shpdim_s = "75";

    dirmode_s = "DIR";

    dirfor_s = "object";

    velavg = 0.001;

    lsppartavg = 450.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "MFX_LIGHT_SINGLERAY.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "250 180 150";

    vistexcolorend_s = "40 100 250";

    vissizestart_s = "3 20";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 0.0;

    useemittersfor = 1;

};



instance mfx_blink_cast(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 0;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 -100 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 0;

    shpdim_s = "75";

    dirmode_s = "NONE";

    dirfor_s = "OBJECT";

    velavg = 1.0E-8;

    lsppartavg = 650.0;

    flygravity_s = "0 0.0008 0";

    visname_s = "MFX_MASTEROFDISASTER_AURA_16BIT.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "250 180 150";

    vistexcolorend_s = "40 100 250";

    vissizestart_s = "15 15";

    vissizeendscale = 1.5;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 50.0;

    useemittersfor = 0;

};



instance mfx_druidtrans_cast(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 0;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 -100 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "90";

    dirmode_s = "NONE";

    dirfor_s = "OBJECT";

    velavg = 1.0E-8;

    lsppartavg = 650.0;

    flygravity_s = "0 0.0008 0";

    visname_s = "STARGATE_BLEND.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "189 138 84";

    vistexcolorend_s = "82 225 103";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 35.0;

};



instance mfx_absorb_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 120 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_absorb_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "80";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00006 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "200 120 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_Pyrokinesis_TargetTrail.TGA";

};



instance mfx_absorb_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 120 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_defense_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 155 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_defense_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 155 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_defense_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "80";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00006 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "200 155 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_Pyrokinesis_TargetTrail.TGA";

};



instance mfx_dk_edefense_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "10 25 235";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "12 12";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_edefense_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "10 25 235";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_edefense_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "80";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00006 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "10 25 235";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_Pyrokinesis_TargetTrail.TGA";

};



instance mfx_dk_illness_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "Decal_Invisible.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "40 233 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "6 12";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_illness_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "Decal_Invisible.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "40 233 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_illness_cast(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "80";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00006 0";

    visname_s = "Decal_Invisible.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "40 233 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "25 25";

    vissizeendscale = 25.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_Pyrokinesis_TargetTrail.TGA";

};



instance mfx_dk_lord_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 10 150";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_lord_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 10 150";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_lord_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "80";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00006 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "200 10 150";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_Pyrokinesis_TargetTrail.TGA";

};



instance mfx_darkstatsup_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "10 240 15";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_darkstatsup_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "80";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00006 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "10 240 15";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_Pyrokinesis_TargetTrail.TGA";

};



instance mfx_dk_stealhealth_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_stealhealth_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_dk_stealhealth_cast(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "120";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00008 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_FIRERAIN_RAINTRAIL.TGA";

};



instance mfx_electrowave_init(c_particlefx) {

    ppsvalue = 100.0;

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1 2 3 3 2 2 2 1 2 3 2 3 4 3 2 1 2 3 2 1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.001;

    velvar = 1.0E-4;

    lsppartavg = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "6 6";

    vissizeendscale = 4.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_electrowave_lefthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    velavg = 0.001;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_electrowave_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_electrowave_init_glow(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1 2 1 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.5;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.6;

    velvar = 0.02;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_Spell_Star.tga";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "1 1";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.8;

    trltexture_s = "LIGHTNING_BIG_A2.TGA";

    trlwidth = 1.0;

};



instance mfx_electrowave_explosion(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.01;

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0";

    visname_s = "LIGHTNING_BIG_A2.TGA";

    visorientation_s = "VELO";

    vistexanifps = 2.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "1 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_electrowave_target(c_particlefx) {

    ppsvalue = 40.0;

    ppsscalekeys_s = "4 3 2 1";

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 150.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_THUNDERSPELL_ELECTRO.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "70 70";

    vissizeendscale = 1.5;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_electrowave_spread(c_particlefx) {

    ppsvalue = 175.0;

    ppsscalekeys_s = "1";

    ppsislooping = 0;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "500";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "world";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 900.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_THUNDERSPELL_ELECTRO.TGA";

    visorientation_s = "VEL";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "150 168 255";

    vistexcolorend_s = "61 147 129";

    vissizestart_s = "25 25";

    vissizeendscale = 8.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 35.0;

    trltexture_s = "VFX_MAGIC_ADANOS_DARK_CLOUD.TGA";

    flockmode = "NONE";

};



instance mfx_electrowave_cast(c_particlefx) {

    ppsvalue = 180.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "20";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 150.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_THUNDERSPELL_ELECTRO.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "66 213 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 180.0;

};



instance mfx_firelight_init(c_particlefx) {

    ppsvalue = 50.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "8";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.01;

    velvar = 1.0E-4;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "10 10";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_firelight_lefthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    velavg = 0.001;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};
instance mfx_firelight_righthand(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 6.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "3";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleelev = 90.0;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 2.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "2 35";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_firelight_init_glow(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1 2 1 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 0.5;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.6;

    velvar = 0.02;

    lsppartavg = 2000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "FIREFLARE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 150 0";

    vistexcolorend_s = "255 0 0";

    vissizestart_s = "1 1";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.8;

    trltexture_s = "MFX_FIRERAIN_RAINTRAIL.TGA";

    trlwidth = 1.0;

};



instance mfx_firelight_explosion(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "5";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.01;

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexanifps = 2.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "1 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_firelight_cast(c_particlefx) {

    ppsvalue = 60.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "120";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00008 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "20 20";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_FIRERAIN_RAINTRAIL.TGA";

};



instance mfx_firelight_target(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "3 3 3 2 2 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscalefps = 15.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 1.0E-4;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0001 0";

    visname_s = "HUMANBURN.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "5 50";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "MFX_FIRERAIN_RAINTRAIL.TGA";

};







instance mfx_roots_init(c_particlefx) 
{
    ppsvalue = 20.0;
    ppsscalekeys_s = "1";
    ppsislooping = 1;
    ppsissmooth = 1;
    ppsfps = 1.0;
    shptype_s = "SPHERE";
    shpfor_s = "OBJECT";
    shpoffsetvec_s = "0 0 0";
    shpdistribtype_s = "RAND";
    shpdistribwalkspeed = 0.1;
    shpisvolume = 1;
    shpdim_s = "5";
    shpscalekeys_s = "1";
    shpscaleislooping = 1;
    shpscaleissmooth = 1;
    shpscalefps = 2.0;
    dirmode_s = "RAND";
    dirfor_s = "object";
    dirmodetargetfor_s = "OBJECT";
    dirmodetargetpos_s = "0 0 0";
    dirangleheadvar = 180.0;
    dirangleelevvar = 180.0;
    velavg = 0.01;
    lsppartavg = 1000.0;
    flygravity_s = "0 0 0";
    visname_s = "NW_SEQ_NATURE_CANYONBUSH_01.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexanifps = 18.0;
    vistexaniislooping = 1;
    vistexcolorstart_s = "255 255 255";
    vistexcolorend_s = "255 225 255";
    vissizestart_s = "20 20";
    vissizeendscale = 2.0;
    visalphafunc_s = "BLEND";
    visalphastart = 255.0;
    useemittersfor = 1;
};



instance mfx_roots_cast(c_particlefx) 
{
    ppsvalue = 20.0;
    ppsscalekeys_s = "1";
    ppsislooping = 1;
    ppsissmooth = 1;
    ppsfps = 1.0;
    shptype_s = "SPHERE";
    shpfor_s = "OBJECT";
    shpoffsetvec_s = "20 5 5";
    shpdistribtype_s = "RAND";
    shpdistribwalkspeed = 0.1;
    shpisvolume = 1;
    shpdim_s = "5";
    shpscalekeys_s = "1";
    shpscaleislooping = 1;
    shpscaleissmooth = 1;
    shpscalefps = 2.0;
    dirmode_s = "RAND";
    dirfor_s = "object";
    dirmodetargetfor_s = "OBJECT";
    dirmodetargetpos_s = "0 0 0";
    dirangleheadvar = 180.0;
    dirangleelevvar = 180.0;
    velavg = 0.01;
    lsppartavg = 1000.0;
    flygravity_s = "0 ROOTNOOSE 0";
    visname_s = "NW_SEQ_NATURE_CANYONBUSH_01.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexanifps = 18.0;
    vistexcolorstart_s = "255 255 255";
    vistexcolorend_s = "255 255 255 ";
    vissizestart_s = "50 50";
    vissizeendscale = 2.0;
    visalphafunc_s = "BLEND";
    visalphastart = 255.0;
};



instance mfx_roots_spread(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1";

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 -60 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "1500";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = 90.0;

    dirangleelevvar = 10.0;

    velavg = 0.001;

    lsppartavg = 20000.0;

    visname_s = "NW_SEQ_NATURE_CANYONBUSH_01.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 8.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_roots_target(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1";

    ppsfps = 2.0;

    ppscreateem_s = "MFX_ROOTS_BURST";

    ppscreateemdelay = 200.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 -60 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "60";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = 90.0;

    dirangleelevvar = 10.0;

    velavg = 0.001;

    lsppartavg = 20000.0;

    visname_s = "NW_SEQ_NATURE_CANYONBUSH_01.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "15 15";

    vissizeendscale = 8.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_roots_burst(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsfps = 5.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "200";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "RAND";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = 90.0;

    dirangleelevvar = 10.0;

    velavg = 0.2;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.001 0";

    flycolldet_b = 3;

    visname_s = "NW_SEQ_NATURE_CANYONBUSH_01.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "100 100";

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    visalphaend = 255.0;

    useemittersfor = 1;

};



instance mfx_roots_groundglow(c_particlefx) {

    ppsvalue = 1000.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 400 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "500 10 500";

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    shpscalefps = 5.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = -90.0;

    dirangleelevvar = 10.0;

    velavg = 2.0;

    lsppartavg = 3000.0;

    lsppartvar = 1500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 3;

    visname_s = "MFX_SLEEP_STAR.TGA";

    visorientation_s = "NONE";

    vistexanifps = 18.0;

    vistexcolorstart_s = "50 50 50";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "35 35";

    vissizeendscale = 0.1;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

    mrkfadespeed = 1.0;

    mrktexture_s = "NW_SEQ_NATURE_CANYONBUSH_01.TGA";

    mrksize = 100.0;

};


instance mfx_windfury_hit(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1 1 1 1 1";

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 20 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "10";

    shpmeshrender_b = 1;

    shpscalekeys_s = "1";

    shpscaleissmooth = 1;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 10.0;

    dirangleelev = 90.0;

    dirangleelevvar = 10.0;

    velavg = 0.4;

    velvar = 0.25;

    lsppartavg = 1000.0;

    lsppartvar = 100.0;

    flygravity_s = "0 0 0";

    visname_s = "WHIRLWIND.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "128 128 128";

    vissizestart_s = "28 10";

    vissizeendscale = 3.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_windfist_gobbo_init(c_particlefx) {

    ppsvalue = 200.0;

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "3";

    shpscalekeys_s = "1 2 3 4 5 4 3 4 6 8 7 5 4 2 6 5 4 3 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "DIR";

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "7 7";

    vissizeendscale = 50.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_windfist_gobbo_init_windfury(c_particlefx) {

    ppsvalue = 100.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "3";

    shpscalekeys_s = "1 2 3 4 5 4 3 4 6 8 7 5 4 2 6 5 4 3 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "DIR";

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "7 7";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 230.0;

};



instance mfx_windfist_gobbo_collisiondummy(c_particlefx) {

    ppsvalue = 300.0;

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "120";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "DIR";

    lsppartavg = 500.0;

    lsppartvar = 200.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "10 10";

    vissizeendscale = 20.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_windfist_gobbo_invest(c_particlefx) {

    ppsvalue = 80.0;

    ppsislooping = 1;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "200";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 1750.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "220 220 255";

    vistexcolorend_s = "220 220 255";

    vissizestart_s = "200 200";

    visalphafunc_s = "BLEND";

    visalphaend = 255.0;

};



instance mfx_windfist_gobbo_invest_blast(c_particlefx) {

    ppsvalue = 2000.0;

    ppsscalekeys_s = "1";

    ppsfps = 20.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "250";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.4;

    lsppartavg = 800.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "220 220 255";

    vistexcolorend_s = "220 220 255";

    vissizestart_s = "100 100";

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance mfx_windfist_gobbo_cast(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1 10";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 90.0;

    velavg = 2.0;

    velvar = 0.5;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "NONE";

    vistexanifps = 3.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 200 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "16 16";

    vissizeendscale = 100.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "WHITECLOUD.TGA";

};



instance mfx_windfist_gobbo_castdummy(c_particlefx) {

    ppsvalue = 30.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "LIGHTNING_BIG_A0.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 255 255";

    vissizestart_s = "6 6";

    vissizeendscale = 4.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_windfist_gobbo_target(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "15";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.08;

    velvar = 0.02;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 30.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_iceexploision_init(c_particlefx) {

    ppsvalue = 75.0;

    ppsscalekeys_s = "5";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.03;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "MFX_FREEZE_MULTIICE.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "47 72 216";

    vissizestart_s = "5 5";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_iceexploision_spread_small(c_particlefx) {

    ppsvalue = 250.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 50.0;

    dirangleelevvar = 180.0;

    velavg = 0.29;

    velvar = 0.03;

    lsppartavg = 1200.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_FREEZE_ICEQUADMARK.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "108 137 242";

    vistexcolorend_s = "24 87 234";

    vissizestart_s = "25 100";

    vissizeendscale = 4.0;

    visalphafunc_s = "ADD";

    visalphastart = 220.0;

    trlfadespeed = 1.5;

    trltexture_s = "MFX_FREEZE_ICE.TGA";

    trlwidth = 10.0;

};



instance mfx_iceexploision_collide_sparks(c_particlefx) {

    ppsvalue = 600.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 10.0;

    shptype_s = "POINT";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.2;

    velvar = 0.05;

    lsppartavg = 5000.0;

    flygravity_s = "0 -0.0005 0";

    flycolldet_b = 1;

    visname_s = "MFX_FREEZE_MULTIICE.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "30 30";

    vissizeendscale = 0.1;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 255.0;

};



instance mfx_iceexploision_collide3(mfx_fireball_collide_proto) {

    ppsvalue = 30.0;

    lsppartavg = 1800.0;

    vissizeendscale = 14.0;

    visalphastart = 220.0;

    ppscreateem_s = "MFX_ICEEXPLOISION_COLLIDE_SPARKS";

};
instance mfx_lightningsphere_init(c_particlefx) {

    ppsvalue = 35.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "15";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 566.0;

    lsppartvar = 555.0;

    flygravity_s = "0 0 0";

    visname_s = "LIGHTNING_BIG_A0.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "1 1";

    vissizeendscale = 80.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_lightningsphere_invest(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1 2 3 4 5 6 7 8 9 10 10 10 10 10 10 10 10 10 10 10 10 ";

    ppsislooping = 1;

    ppsfps = 3.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 2.0;

    shpdim_s = "80";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 10.0;

    dirmode_s = "TARGET";

    dirmodetargetfor_s = "OBJECT";

    velavg = 0.1;

    lsppartavg = 800.0;

    flygravity_s = "0 0 0";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "VELO";

    vistexanifps = 3.0;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 0.4;

    visalphafunc_s = "ADD";

    visalphaend = 255.0;

};



instance mfx_lightningsphere_cast(c_particlefx) {

    ppsvalue = 35.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "11";

    shpscalekeys_s = "1 2 3 1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "LIGHTNING_BIG_A0.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "50 100 255";

    vissizestart_s = "25 25";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_lightningsphere_target(c_particlefx) {

    ppsvalue = 200.0;
    ppsscalekeys_s = "1";
    ppsissmooth = 1;
    ppsfps = 2.0;
    shptype_s = "POINT";
    shpfor_s = "OBJECT";
    shpoffsetvec_s = "0 0 0";
    shpdistribtype_s = "RAND";
    shpisvolume = 1;
    shpdim_s = "50";
    shpscalekeys_s = "1";
    shpscaleislooping = 1;
    shpscaleissmooth = 1;
    shpscalefps = 2.0;
    dirmode_s = "RAND";
    dirfor_s = "object";
    dirmodetargetfor_s = "OBJECT";
    dirmodetargetpos_s = "0 0 0";
    dirangleheadvar = 180.0;
    dirangleelevvar = 180.0;
    velavg = 0.1;
    velvar = 0.05;
    lsppartavg = 200.0;
    visname_s = "LIGHTNING_BIG_A0.TGA";
    visorientation_s = "VELO";
    vistexisquadpoly = 1;
    vistexanifps = 18.0;
    vistexaniislooping = 1;
    vistexcolorstart_s = "255 255 255";
    vistexcolorend_s = "50 100 255";
    vissizestart_s = "20 20";
    vissizeendscale = 15.0;
    visalphafunc_s = "ADD";
    visalphastart = 255.0;
    visalphaend = 255.0;

};



instance mfx_lightningsphere_ani(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 10";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "20 20 1";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.05;

    velvar = 0.025;

    lsppartavg = 3000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "BADWEATH.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "12 12";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance mfx_lightningsphere_flytoplayer(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1 1 1 1 1";

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "40";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "TARGET";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "WORLD";

    dirmodetargetpos_s = "0 0 0";

    velavg = 0.3;

    velvar = 0.055;

    lsppartavg = 8000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "BADWEATH.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "128 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "30 30";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};
instance mfx_masterofdisaster_init_red(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelev = -90.0;

    velavg = 0.001;

    lsppartavg = 2000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 -0.0000001 0";

    visname_s = "MFX_MASTEROFDISASTER_AURA_16BIT.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "255 200 200";

    vissizestart_s = "50 50";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    useemittersfor = 1;

};



instance mfx_necrobolt_init(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "14";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 0.008;

    velvar = 0.001;

    lsppartavg = 1000.0;

    lsppartvar = 501.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 10.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "155 12 0";

    vistexcolorend_s = "55 12 0";

    vissizestart_s = "6 6";

    vissizeendscale = 6.0;

    visalphafunc_s = "ADD";

    visalphastart = 180.0;

    useemittersfor = 1;

};



instance mfx_necrobolt_cast(c_particlefx) {

    ppsvalue = 200.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "20 5 5";

    shpdistribtype_s = "RAND";

    shpdistribwalkspeed = 0.1;

    shpisvolume = 1;

    shpdim_s = "12";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    dirangleheadvar = 180.0;

    dirangleelevvar = 180.0;

    velavg = 1.0E-5;

    lsppartavg = 500.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "52 0 0";

    vistexcolorend_s = "52 0 0";

    vissizestart_s = "25 25";

    vissizeendscale = 7.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trlfadespeed = 0.5;

    useemittersfor = 1;

};



instance mfx_necrobolt_spread(c_particlefx) {

    ppsvalue = 80.0;

    ppsscalekeys_s = "3 4 5 5";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "400";

    shpscalekeys_s = "0.100000001 0.400000006 0.700000048 1 1.29999995 1.5999999 1.89999986";

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "RAND";

    dirfor_s = "OBJECT";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "176 10 10";

    vistexcolorend_s = "166 0 0";

    vissizestart_s = "8 8";

    vissizeendscale = 10.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};



instance mfx_necrobolt_collide(c_particlefx) {

    ppsvalue = 45.0;

    ppsscalekeys_s = "1 1 2 2 2 3 3 4 4 5";

    ppsissmooth = 6;

    ppsfps = 20.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "45";

    shpscalekeys_s = "1 2 3 4 5 6 7 8 9 10";

    shpscaleissmooth = 1;

    shpscalefps = 20.0;

    dirmode_s = "RAND";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 45.0;

    dirangleelev = 90.0;

    dirangleelevvar = 45.0;

    velavg = 0.1;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "THUNDERSTORM_LIGHTNING.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 25.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "166 30 0";

    vistexcolorend_s = "166 30 0";

    vissizestart_s = "15 15";

    vissizeendscale = 20.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    trltexture_s = "LIGHTNING_BIG_A0.TGA";

};
instance fire_sword_nb(fire_sword_proto) {

    shpmesh_s = "NB_PFX_BELIAR_2h.3DS";

    visname_s = "HUMANBURN.tga";

    vistexcolorstart_s = "45 255 255";

};
