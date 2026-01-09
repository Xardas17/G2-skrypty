instance dragon_icexattack(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "3 2 2 1";

    ppsfps = 0.2;

    ppsislooping = 0;

    ppsissmooth = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "90 10 0";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1 2 3";

    shpscaleislooping = 0;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0.1 -0.1 100";

    diranglehead = 100.0;

    dirangleheadvar = 10.0;

    dirangleelev = 180.0;

    dirangleelevvar = 12.0;

    velavg = 1.0;

    velvar = 0.3;

    lsppartavg = 1000.0;

    lsppartvar = 200.0;

    flygravity_s = "0 0.0005 0";

    visname_s = "ICEXFLARE.TGA";

    visorientation_s = "NONE";

    vistexanifps = 8.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "9 8";

    vissizeendscale = 25.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance dragon_darkattack(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "3 2 2 1";

    ppsfps = 0.2;

    ppsislooping = 0;

    ppsissmooth = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "90 10 0";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1 2 3";

    shpscaleislooping = 0;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0.1 -0.1 100";

    diranglehead = 100.0;

    dirangleheadvar = 10.0;

    dirangleelev = 180.0;

    dirangleelevvar = 12.0;

    velavg = 1.0;

    velvar = 0.3;

    lsppartavg = 1000.0;

    lsppartvar = 200.0;

    flygravity_s = "0 0.0005 0";

    visname_s = "DARKFLARE.TGA";

    visorientation_s = "NONE";

    vistexanifps = 8.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "0 0 0";

    vissizestart_s = "9 8";

    vissizeendscale = 25.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};
instance bfx_preset3_dead(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1 0 0 0.8 0 0 0.5 0 0 0.3 0 0";

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "10";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 90.0;

    dirangleheadvar = 15.0;

    dirangleelev = 90.0;

    dirangleelevvar = 15.0;

    velavg = 0.15;

    velvar = 0.05;

    lsppartavg = 1500.0;

    lsppartvar = 300.0;

    flygravity_s = "0 -0.0005 0";

    visname_s = "BQM_MEATBUG2.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "9 9";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};
instance ice_hot(c_particlefx) {

    ppsvalue = 25.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "SPHERE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

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

    visname_s = "VFX_Env_Ice_01.tga";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 0";

    vissizestart_s = "40 40";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};
instance fire_smoke_volcano(c_particlefx) {

    ppsvalue = 10.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsissmooth = 1;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 1 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "5000";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirangleheadvar = 50.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.04;

    lsppartavg = 5500.0;

    lsppartvar = 400.0;

    flygravity_s = "0 0 0";

    visname_s = "FIRESMOKE_V2.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "140 140 140";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "1000 1000";

    vissizeendscale = 10.0;

    visalphafunc_s = "BLEND";

    visalphastart = 175.0;

};
instance groundfog_dark(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "500";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirangleheadvar = 50.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.02;

    velvar = 0.008;

    lsppartavg = 15000.0;

    lsppartvar = 400.0;

    flygravity_s = "0 -0.000005 0";

    visname_s = "FIREFOGLAVA.TGA";

    visorientation_s = "NONE";

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "20 20";

    vissizeendscale = 30.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};

instance dragon_hidden(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "3 2 2 1";

    ppsfps = 0.2;

    ppsislooping = 0;

    ppsissmooth = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "90 10 0";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 1;

    shpdim_s = "1";

    shpscalekeys_s = "1 2 3";

    shpscaleislooping = 0;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0.1 -0.1 100";

    diranglehead = 100.0;

    dirangleheadvar = 10.0;

    dirangleelev = 180.0;

    dirangleelevvar = 12.0;

    velavg = 1.0;

    velvar = 0.3;

    lsppartavg = 1000.0;

    lsppartvar = 200.0;

    flygravity_s = "0 0.0005 0";

    visname_s = "";

    visorientation_s = "NONE";

    vistexanifps = 8.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 100 100";

    vissizestart_s = "9 8";

    vissizeendscale = 25.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance darkcone(c_particlefx) {

    ppsvalue = 2.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    ppscreateem_s = "DARKCONE_PARTICLES";

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

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "255 0 0";

    vistexcolorend_s = "255 0 0";

    vissizestart_s = "30 150";

    vissizeendscale = 3.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

};



instance darkcone_particles(c_particlefx) {

    ppsvalue = 20.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 -80 0";

    shpdistribtype_s = "RAND";

    shpdim_s = "20";

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

    lsppartavg = 10000.0;

    lsppartvar = 500.0;

    flygravity_s = "0 0.00001 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "238 111 17";

    vistexcolorend_s = "238 111 17";

    vissizestart_s = "1 10";

    vissizeendscale = 1.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};


instance fieldburn(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 1 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirangleheadvar = 50.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.3;

    velvar = 0.01;

    lsppartavg = 1000.0;

    lsppartvar = 400.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Env_Fire_01.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "150 150 150";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "50 100";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance fieldburnbig(c_particlefx) {

    ppsvalue = 15.0;

    ppsscalekeys_s = "1 1 1 1 1 1 1 1 1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 1 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "50";

    shpscalekeys_s = "20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirangleheadvar = 50.0;

    dirangleelev = 90.0;

    dirangleelevvar = 20.0;

    velavg = 0.3;

    velvar = 0.01;

    lsppartavg = 1000.0;

    lsppartvar = 400.0;

    flygravity_s = "0 0 0";

    visname_s = "VFX_Env_Fire_01.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "150 150 150";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "50 100";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance well_water(c_particlefx) {

    ppsvalue = 100.0;

    ppsscalekeys_s = "1 0 1 0 2 0.4 12 16 0.3 0 1";

    shptype_s = "POINT";

    shpfor_s = "object";

    shpisvolume = 1;

    shpdim_s = "300";

    shpscalefps = 10.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 270.0;

    dirangleheadvar = 5.0;

    dirangleelev = 20.0;

    dirangleelevvar = 5.0;

    velavg = 0.2;

    velvar = 0.005;

    lsppartavg = 700.0;

    flygravity_s = "0 -0.002 0";

    visname_s = "BRUNNENWASSER.TGA";

    visorientation_s = "VELO";

    vistexcolorstart_s = "255 255 255";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "3 15";

    vissizeendscale = 2.0;

    visalphafunc_s = "BLEND";

    visalphastart = 80.0;

};



instance vfx_watf_exp2(c_particlefx) {

    ppsvalue = 40.0;

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 500 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "40 100 40";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 1.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    diranglehead = 10.0;

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 0.8;

    velvar = 0.3;

    lsppartavg = 700.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 3;

    visname_s = "WATERFIST_EXPL.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 200 200";

    vistexcolorend_s = "230 230 230";

    vissizestart_s = "30 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



instance monastery_light_particles5(c_particlefx) {

    ppsvalue = 3.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "BOX";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "0 80 0";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 200.0;

    dirangleelev = 585.0;

    velavg = 0.001;

    lsppartavg = 9000.0;

    lsppartvar = 1.0;

    flygravity_s = "0 0 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "30 30 30";

    vistexcolorend_s = "30 30 30";

    vissizestart_s = "4 30";

    vissizeendscale = 35.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    m_bisambientpfx = 1;

};



instance monastery_light_particles6(c_particlefx) {

    ppsvalue = 3.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "BOX";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "0 80 0";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 30.0;

    dirangleelev = 585.0;

    velavg = 0.001;

    lsppartavg = 9000.0;

    lsppartvar = 1.0;

    flygravity_s = "0 0 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "30 30 30";

    vistexcolorend_s = "30 30 30";

    vissizestart_s = "4 30";

    vissizeendscale = 35.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    m_bisambientpfx = 1;

};



instance monastery_light_particles7(c_particlefx) {

    ppsvalue = 3.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "BOX";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "0 80 0";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 50.0;

    dirangleelev = 585.0;

    velavg = 0.001;

    lsppartavg = 9000.0;

    lsppartvar = 1.0;

    flygravity_s = "0 0 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "30 30 30";

    vistexcolorend_s = "30 30 30";

    vissizestart_s = "4 30";

    vissizeendscale = 35.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    m_bisambientpfx = 1;

};



instance monastery_light_particles8(c_particlefx) {

    ppsvalue = 3.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "BOX";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "0 80 0";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 214.0;

    dirangleelev = 585.0;

    velavg = 0.001;

    lsppartavg = 9000.0;

    lsppartvar = 1.0;

    flygravity_s = "0 0 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "30 30 30";

    vistexcolorend_s = "30 30 30";

    vissizestart_s = "4 30";

    vissizeendscale = 35.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    m_bisambientpfx = 1;

};



instance monastery_light_particles9(c_particlefx) {

    ppsvalue = 3.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "BOX";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "0 80 0";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 240.0;

    dirangleelev = 585.0;

    velavg = 0.001;

    lsppartavg = 9000.0;

    lsppartvar = 1.0;

    flygravity_s = "0 0 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "30 30 30";

    vistexcolorend_s = "30 30 30";

    vissizestart_s = "4 30";

    vissizeendscale = 35.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    m_bisambientpfx = 1;

};



instance monastery_light_particles10(c_particlefx) {

    ppsvalue = 3.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "BOX";

    shpfor_s = "OBJECT";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "0 80 0";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 0";

    diranglehead = 251.0;

    dirangleelev = 585.0;

    velavg = 0.001;

    lsppartavg = 9000.0;

    lsppartvar = 1.0;

    flygravity_s = "0 0 0";

    visname_s = "HEAVENLIGHT.TGA";

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 2;

    vistexcolorstart_s = "30 30 30";

    vistexcolorend_s = "30 30 30";

    vissizestart_s = "4 30";

    vissizeendscale = 35.0;

    visalphafunc_s = "ADD";

    visalphastart = 200.0;

    m_bisambientpfx = 1;

};



instance pfx_watersplash_sea_n(c_particlefx) {

    ppsvalue = 150.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 3.0;

    shptype_s = "CIRCLE";

    shpfor_s = "WORLD";

    shpisvolume = 1;

    shpdim_s = "100";

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    dirangleheadvar = 45.0;

    dirangleelev = 85.0;

    dirangleelevvar = 45.0;

    velavg = 0.15;

    velvar = 0.03;

    lsppartavg = 1000.0;

    flygravity_s = "0 -0.0003 0";

    visname_s = "WAVEEFFECT_TOP.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexaniislooping = 1;

    vistexcolorstart_s = "225 225 225";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "5 5";

    vissizeendscale = 60.0;

    visalphafunc_s = "BLEND";

    visalphastart = 200.0;

    visalphaend = 0.0;

    m_bisambientpfx = 1;

};



instance vfx_watf_exp(c_particlefx) {

    ppsvalue = 110.0;

    ppsislooping = 1;

    ppsfps = 1.0;

    shptype_s = "BOX";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 500 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "40 400 40";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 1.0;

    dirmode_s = "DIR";

    dirfor_s = "WORLD";

    diranglehead = 10.0;

    dirangleheadvar = 5.0;

    dirangleelev = -90.0;

    dirangleelevvar = 5.0;

    velavg = 1.0;

    velvar = 0.3;

    lsppartavg = 1400.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 3;

    visname_s = "WATERFIST_EXPL.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "200 200 200";

    vistexcolorend_s = "200 200 200";

    vissizestart_s = "30 30";

    vissizeendscale = 20.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

};



prototype waterfall(c_particlefx) {

    ppsvalue = 13.0;

    ppsislooping = 1;

    ppsscalekeys_s = "1 1 1 1 0.8 0.7 0.9 1.1 1.1 1.2 1.1";

    shptype_s = "BOX";

    shpfor_s = "object";

    shpisvolume = 1;

    shpdim_s = "1 10 1";

    shpscalefps = 10.0;

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpdistribtype_s = "uniform";

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 270.0;

    dirangleheadvar = 5.0;

    dirangleelev = 20.0;

    dirangleelevvar = 5.0;

    velavg = 0.301;

    velvar = 0.05;

    flycolldet_b = 1;

    lsppartavg = 800.0;

    lsppartvar = 10.0;

    flygravity_s = "0 -0.001 0";

    visname_s = "PFX_WATERFALL1.TGA";

    vistexanifps = 1.0;

    visorientation_s = "VELO3D";

    vistexisquadpoly = 1;

    vistexcolorstart_s = "190 190 190";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "120 170";

    vissizeendscale = 1.8;

    visalphafunc_s = "ADD";

    visalphastart = 95.0;

    visalphaend = 95.0;

};



instance waterfall_down_orc_castle(waterfall) {

    ppsvalue = 59.0;

    shpdim_s = "1 130 531";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 20.0;

    dirangleelevvar = 5.0;

    velavg = 0.471;

    velvar = 0.09;

    lsppartavg = 3900.0;

    lsppartvar = 10.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

    flycolldet_b = 0;

};



instance waterfall_near_no_fields(waterfall) {

    ppsvalue = 40.0;

    shpdim_s = "1 100 500";

    diranglehead = 270.0;

    dirangleheadvar = 5.0;

    dirangleelev = 20.0;

    dirangleelevvar = 5.0;

    velavg = 0.421;

    velvar = 0.05;

    lsppartavg = 1700.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_orc_arena(waterfall) {

    ppsvalue = 26.0;

    shpdim_s = "1 30 101";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.271;

    velvar = 0.09;

    lsppartavg = 2000.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

    flycolldet_b = 0;

};



instance waterfall_in_monastarydng(waterfall) {

    ppsvalue = 20.0;

    shpdim_s = "1 10 21";

    diranglehead = 280.0;

    dirangleheadvar = 7.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.071;

    velvar = 0.03;

    lsppartavg = 800.0;

    lsppartvar = 200.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_monstary(waterfall) {

    ppsvalue = 66.0;

    shpdim_s = "1 30 501";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.671;

    velvar = 0.09;

    lsppartavg = 2000.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

    flycolldet_b = 0;

};



instance waterfall_near_xardastower_1(waterfall) {

    ppsvalue = 70.0;

    shpdim_s = "1 30 430";

    diranglehead = 280.0;

    dirangleheadvar = 5.0;

    dirangleelev = 40.0;

    dirangleelevvar = 5.0;

    velavg = 0.391;

    velvar = 0.01;

    lsppartavg = 4800.0;

    lsppartvar = 100.0;

    flygravity_s = "0.00007 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_xardastower_2_up(waterfall) {

    ppsvalue = 80.0;

    shpdim_s = "1 30 500";

    diranglehead = 280.0;

    dirangleheadvar = 50.0;

    dirangleelev = 20.0;

    dirangleelevvar = 5.0;

    velavg = 0.941;

    velvar = 0.09;

    lsppartavg = 3000.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_xardastower_2_1(waterfall) {

    ppsvalue = 56.0;

    shpdim_s = "1 30 500";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 20.0;

    dirangleelevvar = 5.0;

    velavg = 0.521;

    velvar = 0.01;

    lsppartavg = 3600.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_xardastower_2_2(waterfall) {

    ppsvalue = 56.0;

    shpdim_s = "1 30 500";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.631;

    velvar = 0.01;

    lsppartavg = 3600.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_1_1(waterfall) {

    ppsvalue = 50.0;

    shpdim_s = "1 30 450";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.431;

    velvar = 0.01;

    lsppartavg = 2400.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_1_2(waterfall) {

    ppsvalue = 50.0;

    shpdim_s = "1 30 500";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.431;

    velvar = 0.01;

    lsppartavg = 2600.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_1_3(waterfall) {

    ppsvalue = 50.0;

    shpdim_s = "1 30 550";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.431;

    velvar = 0.01;

    lsppartavg = 2600.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_2_1(waterfall) {

    ppsvalue = 50.0;

    shpdim_s = "1 30 700";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.31;

    velvar = 0.01;

    lsppartavg = 2200.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_2_2(waterfall) {

    ppsvalue = 46.0;

    shpdim_s = "1 30 650";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.31;

    velvar = 0.01;

    lsppartavg = 2200.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_2_3(waterfall) {

    ppsvalue = 46.0;

    shpdim_s = "1 30 720";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.31;

    velvar = 0.01;

    lsppartavg = 2200.0;

    lsppartvar = 100.0;

    flygravity_s = "0 -0.001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_half(waterfall) {

    ppsvalue = 23.0;

    shpdim_s = "1 30 620";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.31;

    velvar = 0.01;

    lsppartavg = 1200.0;

    lsppartvar = 1.0;

    flygravity_s = "0.0007 -0.0000001 0";

    vissizestart_s = "120 170";

};



instance waterfall_near_psi_half_longer(waterfall) {

    ppsvalue = 26.0;

    shpdim_s = "1 30 620";

    diranglehead = 280.0;

    dirangleheadvar = 10.0;

    dirangleelev = 10.0;

    dirangleelevvar = 5.0;

    velavg = 0.31;

    velvar = 0.01;

    lsppartavg = 2100.0;

    lsppartvar = 1.0;

    flygravity_s = "0.0007 -0.0000001 0";

    vissizestart_s = "120 170";

};



instance woodrays_night(c_particlefx) {

    ppsvalue = 4.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 400 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "4000";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirangleheadvar = 50.0;

    dirangleelev = 70.0;

    dirangleelevvar = 0.0;

    lsppartavg = 12000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "CZ_WOODRAYS.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "130 155 205";

    vissizestart_s = "100 590";

    vissizeendscale = 1.01;

    visalphafunc_s = "ADD";

    visalphastart = 205.0;

    visalphaend = 0.0;

};



instance woodrays(c_particlefx) {

    ppsvalue = 4.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 400 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "4000";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 2.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    dirangleheadvar = 50.0;

    dirangleelev = 70.0;

    dirangleelevvar = 0.0;

    lsppartavg = 12000.0;

    lsppartvar = 1000.0;

    flygravity_s = "0 0 0";

    flycolldet_b = 0;

    visname_s = "CZ_WOODRAYS.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 1.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "0 0 0";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "100 590";

    vissizeendscale = 1.01;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

    visalphaend = 0.0;

};






instance lhsmoke(c_particlefx) {

    ppsvalue = 7.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsissmooth = 1;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "10 0 0";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 21;

    shpdim_s = "10";

    shpscalekeys_s = "5";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 1.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 10.0;

    dirangleheadvar = 15.0;

    dirangleelev = 10.0;

    dirangleelevvar = 10.0;

    velavg = 2.0;

    lsppartavg = 4000.0;

    lsppartvar = 2000.0;

    flygravity_s = "-0.00005 0.00015 -0.00005";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "80 80 80";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "10 30";

    vissizeendscale = 35.0;

    visalphafunc_s = "BLEND";

    visalphastart = 255.0;

    flockmode = "WIND2";

    flockstrength = 0.008;

};



instance lhsmoke_2(c_particlefx) {

    ppsvalue = 5.0;

    ppsscalekeys_s = "1.0";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 5.0;

    shptype_s = "POINT";

    shpfor_s = "object";

    shpoffsetvec_s = "10 0 0";

    shpdistribtype_s = "UNIFORM";

    shpisvolume = 21;

    shpdim_s = "10";

    shpscalekeys_s = "5";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 1.0;

    dirmode_s = "DIR";

    dirfor_s = "object";

    diranglehead = 10.0;

    dirangleheadvar = 15.0;

    dirangleelev = 10.0;

    dirangleelevvar = 10.0;

    velavg = 2.0;

    velvar = 2.0;

    lsppartavg = 4000.0;

    lsppartvar = 2000.0;

    flygravity_s = "-0.00005 0.00015 -0.00005";

    visname_s = "GROUNDFOG.TGA";

    visorientation_s = "NONE";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "215 215 215";

    vistexcolorend_s = "255 255 255";

    vissizestart_s = "15 35";

    vissizeendscale = 35.0;

    visalphafunc_s = "BLEND";

    visalphastart = 225.0;

    visalphaend = 10.0;

    flockmode = "WIND2";

    flockstrength = 0.008;

};



instance barriere_daron(c_particlefx) {

    ppsvalue = 5000.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 2.0;

    shptype_s = "MESH";

    shpfor_s = "WORLD";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "200";

    shpmesh_s = "NW_BOSSBARRIER_DARON.3DS";

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

    velavg = 0.1;

    velvar = 0.005;

    lsppartavg = 1000.0;

    flygravity_s = "0 0 0";

    visname_s = "MFX_FEAR_DEMONFACE.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 18.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "20 20 20";

    vistexcolorend_s = "255 20 20";

    vissizestart_s = "25 25";

    vissizeendscale = 5.0;

    visalphafunc_s = "ADD";

    visalphastart = 255.0;

};



instance fire_massive(c_particlefx) {

    ppsvalue = 90.0;

    ppsscalekeys_s = "1";

    ppsislooping = 1;

    ppsissmooth = 1;

    ppsfps = 1.0;

    shptype_s = "CIRCLE";

    shpfor_s = "object";

    shpoffsetvec_s = "0 0 0";

    shpdistribtype_s = "RAND";

    shpisvolume = 1;

    shpdim_s = "250";

    shpscalekeys_s = "1";

    shpscaleislooping = 1;

    shpscaleissmooth = 1;

    shpscalefps = 3.0;

    dirmode_s = "DIR";

    dirmodetargetfor_s = "OBJECT";

    dirmodetargetpos_s = "0 0 400";

    dirangleelev = 90.0;

    velavg = 0.01;

    lsppartavg = 1000.0;

    lsppartvar = 300.0;

    flygravity_s = "0 0.0002 0";

    visname_s = "VFX_ENV_FIRE_02.TGA";

    visorientation_s = "VELO";

    vistexisquadpoly = 1;

    vistexanifps = 5.0;

    vistexaniislooping = 1;

    vistexcolorstart_s = "100 100 100";

    vistexcolorend_s = "100 100 0";

    vissizestart_s = "40 40";

    vissizeendscale = 4.0;

    visalphafunc_s = "ADD";

    visalphastart = 235.0;

    visalphaend = 120.0;

};
