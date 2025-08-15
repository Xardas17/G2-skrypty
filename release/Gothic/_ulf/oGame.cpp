/******************************************************************************** 
 
     $Workfile:: oGame.cpp           $                 $Date:: 26.04.01 15:34   $
     $Revision:: 247                 $              $Modtime:: 25.04.01 18:06   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH

   Description::
   Game - Class

 * $Log: /current_work/Gothic/_Ulf/oGame.cpp $
 * 
 * 247   26.04.01 15:34 Edenfeld
 * Soundprovider Checks sicherer gemacht,
 * AIPlayer Sprungh�nger Bug gefixt
 * 
 * 246   24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 244   3.04.01 15:20 Integrator
 * 
 * 243   19.03.01 21:28 Edenfeld
 * Demo Kastration einfacher/r�ckg�ngig gemacht. 
 * 
 * 242   19.03.01 19:56 Integrator
 * 
 * 241   16.03.01 15:46 Speckels
 * 
 * 240   13.03.01 23:23 Hildebrandt
 * 
 * 239   13.03.01 21:27 Hildebrandt
 * 
 * 238   13.03.01 18:36 Wohlers
 * Patches 1.07 1.Teil
 * 
 * 237   12.03.01 20:01 Speckels
 * 
 * 236   12.03.01 19:58 Edenfeld
 * Reverb f�r Indoor
 * 
 * 235   5.03.01 16:30 Integrator
 * 
 * 234   16.02.01 19:57 Speckels
 * 
 * 233   16.02.01 16:38 Speckels
 * 
 * 232   15.02.01 19:22 Wohlers
 * 
 * 231   15.02.01 19:15 Wohlers
 * 
 * 230   14.02.01 21:38 Speckels
 * 
 * 229   14.02.01 16:14 Wohlers
 * 
 * 228   13.02.01 21:33 Wohlers
 * 
 * 227   13.02.01 20:41 Hildebrandt
 * display of focus name without popping
 * 
 * 226   13.02.01 19:11 Wohlers
 * 
 * 225   13.02.01 19:04 Hildebrandt
 * 
 * 224   13.02.01 18:49 Integrator
 * Fingerprints ge�ndert, nichts besonderes
 * 
 * 223   11.02.01 15:18 Wohlers
 * 
 * 222   11.02.01 15:05 Wohlers
 * 
 * 221   11.02.01 14:33 Wohlers
 * 
 * 220   10.02.01 20:48 Wohlers
 * 
 * 219   10.02.01 1:50 Speckels
 * 
 * 217   9.02.01 13:39 Speckels
 * 
 * 216   8.02.01 20:53 Integrator
 * 
 * 215   8.02.01 14:53 Moos
 * 
 * 214   7.02.01 20:55 Wohlers
 * 
 * 213   7.02.01 14:38 Wohlers
 * 
 * 212   6.02.01 21:00 Wohlers
 * 
 * 211   6.02.01 13:41 Moos
 * 
 * 210   5.02.01 20:19 Wohlers
 * 
 * 209   5.02.01 18:01 Moos
 * 
 * 208   1.02.01 21:47 Speckels
 * 
 * 207   1.02.01 21:06 Speckels
 * 
 * 206   1.02.01 19:26 Speckels
 * 
 * 205   31.01.01 2:07 Wohlers
 * 
 * 204   30.01.01 22:02 Speckels
 * 
 * 203   30.01.01 21:59 Speckels
 * 
 * 202   30.01.01 20:58 Speckels
 * 
 * 201   30.01.01 20:46 Speckels
 * 
 * 200   30.01.01 17:55 Wohlers
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 247 $ ($Modtime: 25.04.01 18:06 $)

#include "zCore.h"

#include "zOption.h"
#include "zMusic.h"
#include "zConsole.h"
#include "zWaynet.h"
#include "zAICamera.h"
#include "zSky.h"
#include "zwin32.h"
#include "zinput_win32.h"
#include "zvideo_win32.h"
#include "zParser.h"
#include "zParser_Const.h"
#include "zFonts.h"
#include "zrenderer.h"
#include "zIncViews.h"

// ************
// Game Files
// ************

#include "ooUlfi.h"
#include "ooBert.h"
#include "ooCarsten.h"

#include "oGame.h"
#include "oNpc.h"
#include "oItem.h"
#include "oHelp.h"
#include "oroutine.h"
#include "oWorld.h"
#include "oFocus.h"
#include "oGuilds.h"
#include "oInfo.h"
#include "oSVM.h"
#include "oAIHuman.h"
#include "oGameInfo.h"
#include "oPlayerInfo.h"
#include "oParticleControl.h"
#include "oobjfactory.h"
#include "zEventMan.h"
#include "oNpcMessages.h"
#include "oCSPlayer.h"
#include "otrigger.h"
#include "oItemReact.h"
#include "oMobInter.h"
#include "oViewProgressBar.h"
#include "oViewStatusBar.h"
#include "oPortals.h"
#include "oSpawn.h"
#include "oMagic.h"
#include "oMusicZone.h"
#include "oAIShoot.h"

#include <direct.h>
#include "zviewprogressbar.h"

#include "oMission.h"
#include "oVisFX.h"

#include "zCCSManager.h"

#include <oIncDialogs.h>
#include <oInfo.h>
#include <oGame.h>
#include <oInformationManager.h>

#include <zAccount.h>

void Game_StartParticleEffects(zCTree<zCVob>* vobtree);

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4706 ) 

oCGame* ogame = NULL;

// Static MusicControl-Flag. Per Konsole togglebar. (Carsten ist schuld !)
static zBOOL musicControlEnabled = TRUE;
static zBOOL game_holdTime		 = FALSE;			// Spy Messages

#ifdef COMPILING_SPACER
extern zBOOL g_bInsertNPCs;
#endif

zBOOL oCGame::s_bUseOldControls = TRUE;
zREAL oCGame::s_fUseSpeechReverb= TRUE;
zBOOL oCGame::s_bUseOnlineHelp	= TRUE;
zBOOL oCGame::s_bUsePotionKeys  = TRUE;
zBOOL oCGame::s_bUseQuickSave	= TRUE;

///////////////////////////////////////////////////////////////

oCVob* SearchVobByInstance(zCTree<zCVob>* vobtree, int& index)
{
	// recursive search
	oCVob* vob = zDYNAMIC_CAST<oCVob>(vobtree->GetData());
	
	if (vob && vob->GetInstance() == index) return vob;
	
	zCTree<zCVob>* child = vobtree->GetFirstChild();
	zCVob* vob2;
	while (child!=0) {
		vob2 = SearchVobByInstance(child, index);
		if (vob2!=0) return (oCVob*)vob2;
		child = child->GetNextChild();
	};
	return 0;								// nothing found
}

oCGame :: oCGame()
{
	//
	//	CODECHANGE [ROMAN]
	//
	for ( int nView = 0; nView < oTGameDialogView :: GAME_VIEW_MAX; nView++ )
	{
		array_view			[ nView ] = NULL ;			// init views
		array_view_enabled	[ nView ] = TRUE ;			// mark as enabled
		array_view_visible	[ nView ] = FALSE;			// mark as invisible
	}
	//
	//	CODECHANGE [ROMAN] END
	//

	game_text		= NULL;
	load_screen		= NULL;
	save_screen		= NULL;
	pause_screen	= NULL;
	game_drawall	= TRUE;
	game_frameinfo	= FALSE;
	game_showranges	= FALSE;
	game_showaniinfo= FALSE;
	game_showwaynet	= FALSE;
#ifdef COMPILING_SPACER
	game_testmode	= TRUE;	
#else
	game_testmode	= FALSE;	
#endif
	game_editwaynet = FALSE;
	game_showtime	= FALSE;
	drawWayBoxes	= FALSE;
	showFreePoints	= FALSE;
	showRoutineNpc	= FALSE;
	loadNextLevel	= FALSE;
	watchnpc		= NULL;
	scriptStartup	= TRUE;  // [Moos] 5.12.2000 nach Ulfs Telephonseelsorge ge�ndert
	inScriptStartup	= FALSE;
	inLoadSaveGame	= FALSE;
	inLevelChange	= FALSE;
	
	// The Player
	gameInfo		= NULL;				
	pl_light		= NULL;
	pl_lightval		= 5000.0f;
	wldTimer		= NULL;
	timeStep		= -1.0f;			// Erm�glicht Einzelbildschaltung
	singleStep		= FALSE;	
	// Info - Pool
	guilds			= NULL;
	infoman			= NULL;
	newsman			= NULL;
	svmman			= NULL;
	trademan		= NULL;
	portalman		= NULL;
	spawnman		= NULL;
	// Environment 
	cliprange		= 1600.0f;
	fogrange		= cliprange / 4;	
	
	progressBar		= NULL;
	hpBar			= NULL;
	swimBar			= NULL;	
	manaBar			= NULL;
	focusBar		= NULL;	
	showPlayerStatus= TRUE;
	savegameManager	= NULL;
	// Music
	music_delay		  = 0;			// Music sofort starten	

	// TestMode ?
#ifndef COMPILING_SPACER
	game_testmode	= zoptions->Parm("DEVMODE");
#endif
	// zoptions->ReadBool(zOPT_SEC_INTERNAL,"testmode",FALSE);

	objRoutineList.SetCompare(Sort_Routine);
	ResetObjectRoutineList	();

	SetEnableHandleEvent	(TRUE);

	m_bWorldEntered		= FALSE;
	m_fEnterWorldTimer	= 0;


	// CODECHANGE [STEFAN]
	/*
	debugChannels = 0;
	debugAllInstances = FALSE;
	*/

	debugChannels = ( zoptions->ReadBool(zOPT_SEC_INTERNAL, "debugAllChannels") ? 0xFFFFFFFF : 0 );
	debugAllInstances = zoptions->ReadBool(zOPT_SEC_INTERNAL, "debugAllInstances");
	if (debugChannels == 0) {
		zSTRING s,s2;
		zINT w,i;
		s = zoptions->ReadString(zOPT_SEC_INTERNAL, "debugChannels");
		s2 = s.PickWord(1, ",; ", ",; ");
		w = 1;
		while (!s2.IsEmpty()) {
			i = s2.ToInt();
			if ((i >= 1) && (i <= 32))
				debugChannels |= (1 << (i - 1));
			w++;
			s2 = s.PickWord(w, ",; ", ",; ");
		}
	}

	/*
	if (debugChannels==0) {
		zERR_MESSAGE(1,0,"S: SC: Debugging no channels");
	} else if(debugChannels==0xFFFFFFFF) {
		zERR_MESSAGE(1,0,"S: SC: Debugging all channels");
	} else {
		zSTRING sss;
		zINT i;
		for (i = 0; i < 32; i++)
			if ((debugChannels & (1 << i)) != 0) {
				if(!sss.IsEmpty())
					sss = sss + ',';
				sss = sss + zSTRING(i + 1);
			}
		sss = "S: SC: Debugging channels " + sss;
		zERR_MESSAGE(1,0,sss);
	}
	if (debugAllInstances) {
		zERR_MESSAGE(1,0,"S: SC: Debugging all instances");
	} else {
		zERR_MESSAGE(1,0,"S: SC: Debugging no instances");
	}
	*/
	// CODECHANGE [STEFAN] END
}

/* ----------------------------------------------------------------------
	
    oCGame :: ~oCGame()	

	26.08.2000	[Moos]	
                ExitFocusModes() eingef�gt

    13.09.2000  [Moos]
                statischen ogame-Pointer bei Bedarf l�schen

   ---------------------------------------------------------------------- */

oCGame :: ~oCGame()
{
	ClearObjectRoutineList	();

	delete	(guilds);	guilds		= NULL;
	delete	(infoman);	infoman		= NULL;
	delete	(newsman);	newsman		= NULL;
	delete	(svmman);	svmman		= NULL;
	delete	(trademan);	trademan	= NULL;
	delete	(portalman);portalman	= NULL;
	delete	(wldTimer);	wldTimer	= NULL;
	delete	(gameInfo);	gameInfo	= NULL;
	delete	(spawnman);	spawnman	= NULL;
	
	if (game_text)  { screen->RemoveItem(game_text);delete game_text;	game_text	= NULL; };
	if (hpBar)		{ screen->RemoveItem(hpBar);	delete hpBar;		hpBar		= NULL; };
	if (swimBar)	{ screen->RemoveItem(swimBar);	delete swimBar;		swimBar		= NULL; };
	if (manaBar)	{ screen->RemoveItem(manaBar);	delete manaBar;		manaBar		= NULL; };
	if (focusBar)	{ screen->RemoveItem(focusBar);	delete focusBar;	focusBar	= NULL; };

	//
	//	CODECHANGE [ROMAN]
	//
	for ( int nView = 0; nView < oTGameDialogView :: GAME_VIEW_MAX; nView++ )	
	{
		if ( array_view[ nView ] )
		{
			CloseView( (oCGame::oTGameDialogView) nView );
			delete array_view[ nView ];
			array_view[ nView ] = NULL;
		}
	}
	//
	//	CODECHANGE [ROMAN] END
	//

	zRELEASE(pl_light);

	oCarsten_ShutDown();
    oCNpcFocus::ExitFocusModes(); // [Moos]

    zCSession::Done(); // [Moos] Besser wir erledigen das, bevor wir den ogame-Pointer l�schen. ~zCSession h�tte es sowieso erledigt.

    if (ogame==this)
        ogame=NULL;  // [Moos] Pointer hierrauf beseitigen, w�re sowieso ung�ltig

}


// ********************************************************************************
// Init / Deinit - Proce
// ********************************************************************************

void oCGame :: WorldInit()
{
	// Bau mir die Welt
	GetWorld()->SetDrawVobBBox3D (FALSE);
	// und den Timer
	// FIXME : Timer nicht l�nger global !
	wldTimer = zNEW( oCWorldTimer() );
	// Getting WorldTime
	initial_hour   = 8;
	initial_minute = 0;
	if (zoptions->Parm("TIME"))
	{
		zSTRING time	= zoptions->ParmValue("TIME");
		initial_hour	= time.PickWord(1," :").ToInt();
		initial_minute	= time.PickWord(3," :").ToInt();	
	}
	// 
	rtnMan.SetWorld(GetWorld());
}

void oCGame :: CamInit()
{
	zCSession::CamInit();

	// ********************
	// Camera - Init
	// ********************
	
/*	camera  =  new zCCamera;
	camera  -> SetRenderTarget(game_viewport);

	// ********************
	// Camera - AI - Init
	// ********************
	
	aiCam	=  new zCAICamera	();
	aiCam   -> AddRef			();
	camVob	=  new zCVob		();
	camVob  -> AddRef			();
	aiCam	-> SetVob			(camVob);
	
	if (!camVob->GetHomeWorld()) GetWorld() ->AddVob(camVob); 

	camVob  ->SetCollDet		(FALSE);
	camVob  ->SetAICallback		(aiCam);
	camVob	->SetSleeping		(FALSE);
	camVob  ->SetPhysicsEnabled	(FALSE);	
	camVob	->SetPositionWorld	(GetSelfPlayerVob()->GetPositionWorld() - GetSelfPlayerVob()->GetAtVectorWorld()*150);
	camera  ->SetVob			(camVob);
	zsound -> SetListener		(camVob);*/
}

void oCGame :: CamInit(zCVob* camera_vob, zCCamera* cam)
{
	zCSession :: CamInit(camera_vob,cam);
	
	// ********************
	// Camera - Init
	// ********************
/*	
	camera  =  cam;
	camera  -> SetRenderTarget		(game_viewport);

	// ********************
	// Camera - AI - Init
	// ********************
	
	camVob  =  camera_vob;
	GetWorld()	-> AddVob			(camVob);
	camVob  -> SetCollDet		(FALSE);
	camVob	-> SetSleeping		(FALSE);
	camVob  -> SetPhysicsEnabled(FALSE);	
	camera  -> SetVob			(camVob);
	
	if (!aiCam) {
		aiCam =  new zCAICamera	();
		aiCam -> AddRef			();
	}
	aiCam  -> SetVob			(camVob);

	zsound -> SetListener		(camVob);*/
}

void oCGame :: SetCameraPosition()
{
	if (GetCameraVob() && GetWorld()) {
		// GameCamera
		GetCameraVob()	-> SetCollDet	(FALSE);
		GetWorld()		-> RemoveVob	(GetCameraVob());
		GetWorld()		-> AddVob		(GetCameraVob());
		// Sleeping on / off
		GetCameraVob()	-> SetAICallback(GetCameraAI());
		GetCameraVob()	-> SetSleeping	(FALSE);
	};
}

void oCGame :: DesktopInit()
{
	zoptions->ChangeDir(DIR_TEX_DESKTOP);

	screen			-> SetFont(0);
	// int sy			=  screen -> FontY();

	zCSession::DesktopInit();

	// Textfenster f�r Dialoge
	game_text		=  zNEW( zCView			(0,0,100,100) );	
	screen			-> InsertItem			(game_text);
	game_text		-> SetAutoScroll		(zoptions->ReadInt(zOPT_SEC_GAME, "gametextAutoScroll", 1000));
	game_text		-> SetFont				(NULL);
	
	/*
	int nMarginX = 1024;
	int nMarginY = 256;

	int nWidthScreen		= VIEW_VXMAX				;	int nHeightScreen		= VIEW_VYMAX;											
	
	int	nHeightConversation = 6 * sy	;	int nYConversation	= 3 * sy;		
	int nHeightAmbient		= 5 * sy	;	int nYAmbient		= nHeightScreen - nMarginY - nHeightAmbient;
	int nHeightDynamic		= 4 * sy	;	int nYDynamic		= nYAmbient - (5 * sy);				
	int nHeightChoice		= 4 * sy	;	int nYChoice		= nYConversation + nHeightConversation + sy;				
	int nHeightCinema		= 4 * sy	;	int nYCinema		= nHeightScreen - nMarginY - nHeightCinema + 0.5 * sy;
	*/

	array_view[ oTGameDialogView::GAME_VIEW_SCREEN		 ] = zNEW( zCView(0,0,100,100) );
	array_view[ oTGameDialogView::GAME_VIEW_CONVERSATION ] = zNEW( zCView(0,0,100,100) );	
	array_view[ oTGameDialogView::GAME_VIEW_AMBIENT		 ] = zNEW( zCView(0,0,100,100) );
	array_view[ oTGameDialogView::GAME_VIEW_CINEMA		 ] = zNEW( zCView(0,0,100,100) );
	array_view[ oTGameDialogView::GAME_VIEW_NOISE		 ] = zNEW( zCView(0,0,100,100) );
 	array_view[ oTGameDialogView::GAME_VIEW_CHOICE		 ] = zNEW( zCView(0,0,100,100) );


	zCView::zEViewFX defaultFX = zCView::zEViewFX::VIEW_FX_NONE;
	array_view[ oTGameDialogView::GAME_VIEW_SCREEN		 ] -> Create( ""					, defaultFX,defaultFX, -2.0f, FALSE );
	array_view[ oTGameDialogView::GAME_VIEW_CONVERSATION ] -> Create( "dlg_conversation.tga", defaultFX,defaultFX, -2.0f, FALSE );
	array_view[ oTGameDialogView::GAME_VIEW_AMBIENT		 ] -> Create( "dlg_ambient.tga"		, defaultFX,defaultFX, -2.0f, FALSE );
	array_view[ oTGameDialogView::GAME_VIEW_CINEMA		 ] -> Create( ""					, defaultFX,defaultFX, -2.0f, FALSE );
	array_view[ oTGameDialogView::GAME_VIEW_NOISE		 ] -> Create( "dlg_noise.tga"		, defaultFX,defaultFX, -2.0f, TRUE  );
	array_view[ oTGameDialogView::GAME_VIEW_CHOICE		 ] -> Create( "dlg_choice.tga"		, defaultFX,defaultFX, -2.0f, TRUE  );

	UpdateViewSettings();

	OpenView(  oTGameDialogView::GAME_VIEW_SCREEN		 );

	for ( int nView = 0; nView < oTGameDialogView :: GAME_VIEW_MAX; nView++ )		
	{
		if ( array_view[ nView ] )
		{
			array_view[ nView ] -> SetFont( NULL );						
		}
	}

	CloseView ( oTGameDialogView::GAME_VIEW_AMBIENT );
	EnableView( oTGameDialogView::GAME_VIEW_AMBIENT, FALSE );

	//
	//	CODECHANGE [ROMAN] END
	//

	zCView :: PrintDebug ("<Textfenster>\n");
	zCView :: stdoutput	= game_text;
}

void oCGame :: UpdateViewSettings()
{
	zCView::zEViewFX animateZoom = zCView::zEViewFX::VIEW_FX_ZOOM;	
	zCView::zEViewFX animateNone = zCView::zEViewFX::VIEW_FX_NONE;
	if (!zoptions->ReadBool(zOPT_SEC_GAME,"animatedWindows",TRUE))
	{
		animateZoom=animateNone;
	};

	
	array_view[oTGameDialogView::GAME_VIEW_SCREEN]->		SetCloseFX	(animateNone);
	array_view[oTGameDialogView::GAME_VIEW_SCREEN]->		SetOpenFX	(animateNone);

	array_view[oTGameDialogView::GAME_VIEW_CONVERSATION]->	SetCloseFX	(animateZoom);
	array_view[oTGameDialogView::GAME_VIEW_CONVERSATION]->	SetOpenFX	(animateZoom);

	array_view[oTGameDialogView::GAME_VIEW_AMBIENT]->		SetCloseFX	(animateNone);
	array_view[oTGameDialogView::GAME_VIEW_AMBIENT]->		SetOpenFX	(animateNone);

	array_view[oTGameDialogView::GAME_VIEW_CINEMA]->		SetCloseFX	(animateNone);
	array_view[oTGameDialogView::GAME_VIEW_CINEMA]->		SetOpenFX	(animateNone);

	array_view[oTGameDialogView::GAME_VIEW_NOISE]->			SetCloseFX	(animateZoom);
	array_view[oTGameDialogView::GAME_VIEW_NOISE]->			SetOpenFX	(animateZoom);

	array_view[oTGameDialogView::GAME_VIEW_CHOICE]->		SetCloseFX	(animateZoom);
	array_view[oTGameDialogView::GAME_VIEW_CHOICE]->		SetOpenFX	(animateZoom);

};

void oCGame :: NpcInit()
{
	NpcInit(&GetWorld()->globalVobTree);
	rtnMan.InitWayBoxes();
}

void oCGame :: NpcInit(zCTree<zCVob>* vobtree)
{
	// recursive search
	zCVob* vob = vobtree->GetData();
	if ((vob) && (vob->GetVobType()==zVOB_TYPE_NSC)) {
		vob -> SetSleepingMode(zVOB_AWAKE);
	};

	zCTree<zCVob>* child = vobtree->GetFirstChild();
	while (child!=0) {
		NpcInit	(child);
		child	= child->GetNextChild();
	};
}

/* ----------------------------------------------------------------------
	
    oCGame::Done()	

	26.08.2000	[Moos]	
                ReleaseStatistics() hinzugef�gt


   ---------------------------------------------------------------------- */

void oCGame::Done()
{
    oCNpc :: ReleaseStatics();

	ClearObjectRoutineList();

	delete	(guilds);	guilds		= NULL;
	delete	(infoman);	infoman		= NULL;
	delete	(newsman);	newsman		= NULL;
	delete	(svmman);	svmman		= NULL;
	delete	(trademan);	trademan	= NULL;
	delete	(portalman);portalman	= NULL;
	delete	(wldTimer);	wldTimer	= NULL;
	delete	(gameInfo);	gameInfo	= NULL;
	delete	(spawnman);	spawnman	= NULL;
	
	if (game_text)  { screen->RemoveItem(game_text);delete game_text;	game_text	= NULL; };
	if (hpBar)		{ screen->RemoveItem(hpBar);	delete hpBar;		hpBar		= NULL; };
	if (swimBar)	{ screen->RemoveItem(swimBar);	delete swimBar;		swimBar		= NULL; };
	if (manaBar)	{ screen->RemoveItem(manaBar);	delete manaBar;		manaBar		= NULL; };
	if (focusBar)	{ screen->RemoveItem(focusBar);	delete focusBar;	focusBar	= NULL; };

	//
	//	CODECHANGE [ROMAN]
	//
	for ( int nView = 0; nView < oTGameDialogView :: GAME_VIEW_MAX; nView++ )	
	{
		if ( array_view[ nView ] )
		{
			CloseView( (oCGame::oTGameDialogView) nView );
			delete array_view[ nView ];
			array_view[ nView ] = NULL;
		}
	}
	//
	//	CODECHANGE [ROMAN] END
	//

	zRELEASE(pl_light);

	oCarsten_ShutDown();
    oCNpcFocus::ExitFocusModes();

	// leere das current-verzeichnis	
	savegameManager->ClearCurrent();

    zCSession::Done();    
};

void oCGame::Init()
{	
	// Carsten Startup -> TEMP ?
	oCarsten_StartUp();

	zCSession::Init();

	sysEvent();

	// Welt erzeugen
	zCWorld* wld = (oCWorld*)zfactory->CreateWorld();
	SetWorld(wld);

	// Konsole
	zcon.SetWorld	(wld);
	zcon.SetParser	(&parser);	
	
	// initialisiere die welt
	WorldInit();		

	// leere das current-verzeichnis	
	savegameManager->ClearCurrent();

	// ****************
	// Parsefile laden
	// ****************
	
	// [BENDLIN] AddonMOD
	zSTRING parserfile;
	if (zgameoptions)
		parserfile = zgameoptions->ReadString(zOPT_SEC_FILES, "Game");
	else
		parserfile = zoptions->ReadString(zOPT_SEC_INTERNAL, "gameScript");
	if (parserfile.IsEmpty()) 
		parserfile = "Content\\Gothic";

	zERR_MESSAGE(4, 0, "N: GAME: Loading file " + parserfile + ".src or .dat");
	LoadParserFile(parserfile + ".src");		

	sysEvent();

	// Window / Fullscreen
//    if (zoptions->Parm("WINDOW"))	zrenderer->Vid_SetScreenMode(zRND_SCRMODE_WINDOWED);
//    else							zrenderer->Vid_SetScreenMode(zRND_SCRMODE_FULLSCREEN);	

	// ********************
	// Parserabh�ngige Vars 
	// ********************
	oCNpc :: InitStatics();

	// Infos saugen (besser: einmal in der Init-Methode)
	guilds		= zNEW( oCGuilds			()			);
	infoman		= zNEW( oCInfoManager		(&parser)	);
	newsman		= zNEW( oCNewsManager		()			);
	svmman		= zNEW( oCSVMManager		()			);	
	trademan	= zNEW( oCTradeManager		(&parser)	);
	portalman	= zNEW( oCPortalRoomManager	()			);
	spawnman	= zNEW( oCSpawnManager		()			);

	// oCViewStatusBar
	hpBar	=  zNEW			(oCViewStatusBar()); 						
	screen	-> InsertItem	(hpBar);
	hpBar	-> Init			(100,7800);
	hpBar	-> SetTextures	("BAR_back.tga","BAR_tempmax.tga","BAR_health.tga");
	hpBar	-> SetMaxRange	(0,30);	// Totales Maximum ist XXX
	screen	-> RemoveItem	(hpBar);

	swimBar	=  zNEW			(oCViewStatusBar());						
	screen	-> InsertItem	(swimBar);
	swimBar -> Init			(2900,7800);
	swimBar -> SetTextures	("BAR_back.tga","BAR_tempmax.tga","BAR_misc.tga");		
	screen	-> RemoveItem	(swimBar);

	manaBar	=  zNEW			(oCViewStatusBar());				
	screen	-> InsertItem	(manaBar);
	manaBar -> Init			(5700,7800);
	manaBar -> SetTextures	("BAR_back.tga","BAR_tempmax.tga","BAR_mana.tga");		
	manaBar -> SetMaxRange	(0,30);	// Totales Maximum ist XXX
	screen	-> RemoveItem	(manaBar);
	
	focusBar=  zNEW			(oCViewStatusBar(0,0,1000,1000));
	screen	-> InsertItem	(focusBar);
	focusBar-> Init			(500,500,0.75);				
	focusBar-> SetTextures	("BAR_back.tga","BAR_tempmax.tga","BAR_health.tga");				
	// Zentrieren
	int xs,ys;
	focusBar-> GetSize		(xs,ys);
	focusBar-> SetPos		((8192-xs)/2.0f , screen->FontY());
	screen	-> RemoveItem	(focusBar);

	sysEvent();

	if (progressBar) progressBar->SetPercent(10);

//#ifdef DEBUG_WOHLERS
	// Mouse on
	if (zinput->GetDeviceConnected(zINPUT_MOUSE)) {
		zinput->SetDeviceEnabled(zINPUT_MOUSE,TRUE);
	}	

	// Joystick on
	if (zinput->GetDeviceConnected(zINPUT_JOYSTICK1)) {
		zinput->SetDeviceEnabled(zINPUT_JOYSTICK1, TRUE);
	}	

	// VIEWKLASSE Init
	zCPar_Symbol *sym = parser.GetSymbol("VIEW_TIME_PER_CHAR");
	if (sym)
	{
		zREAL viewTime = 0;
		sym->GetValue(viewTime);
		zCView::SetViewTimePerChar(viewTime);
	}

//#endif 
}

/* ----------------------------------------------------------------------
	
    ocGame::SetGameInfo	

	30.08.2000	[Moos]	
                Leakfix, falls diese Funktion zweimal aufgerufen wird


   ---------------------------------------------------------------------- */


void oCGame :: SetGameInfo (oCGameInfo* _gameinfo)
{
    if (gameInfo != _gameinfo)
        delete gameInfo;  // [Moos]

	gameInfo = _gameinfo;
	if (!gameInfo)
	// erzeuge objekt fuer game-informationen	
	{
		gameInfo = (oCGameInfo*)zfactory->CreateGameInfo();
		gameInfo->Init();		
	}
};

void oCGame :: CallScriptStartup()
{
	if (scriptStartup) 
	{
		// [BENDLIN] 1.28
		// Scripte inkompatibel, da jetzt 'STARTUP_GLOBAL' zwingend erforderlich ist
		int indexGlobal = parser.GetIndex("STARTUP_GLOBAL");
		int indexWorld	= parser.GetIndex("STARTUP_" + GetGameWorld()->GetWorldName());

		if (indexGlobal <= 0)
			zERR_FATAL("Global Startup Function not found.");
		else
		{
			inScriptStartup = TRUE;
			parser.CallFunc(indexGlobal);
			if (indexWorld > 0)
			{
				zERR_MESSAGE(3,zERR_BEGIN,"U: GAM: Calling Startup-Script ...");
				parser.SetProgressBar(progressBar);
				parser.CallFunc(indexWorld);
				parser.SetProgressBar(0);
				zERR_MESSAGE(3,zERR_END,"U: GAM: Startup-Script finished.");
			}
			inScriptStartup = FALSE;
		}
	}
};

void oCGame :: CallScriptInit()
{
	// [BENDLIN] 1.28
	// Scripte inkompatibel, da jetzt 'INIT_GLOBAL' zwingend erforderlich ist
	int indexGlobal = parser.GetIndex("INIT_GLOBAL");
	int indexWorld	= parser.GetIndex("INIT_" + GetGameWorld()->GetWorldName());

	if (indexGlobal <= 0)
		zERR_FATAL("Global Init Function not found.");
	else
	{
		inScriptStartup = TRUE;
		parser.CallFunc(indexGlobal);
		if (indexWorld > 0)
		{
			zERR_MESSAGE(3,zERR_BEGIN,"U: GAM: Calling Init-Script ...");		
			parser.SetProgressBar(progressBar);
			parser.CallFunc(indexWorld);
			parser.SetProgressBar(0);
			zERR_MESSAGE(3,zERR_END,"U: GAM: Init-Script finished.");
		}
		inScriptStartup = FALSE;
	}
};

/* ------------------------------------------------------------------------------

	void oCGame::OpenSavescreen	(bool saveGame)

	6.10.2000	[SPECKELS]	Neue Methode erstellt

   ------------------------------------------------------------------------------ */


void oCGame::OpenSavescreen	(bool saveGame)
{
#ifdef COMPILING_SPACER
	return;
#endif

	if (save_screen) CloseSavescreen();

	zERR_MESSAGE(5,0,"B: GAM: OpenSavescreen ");	
			
	if (saveGame) 
	{	
		int mid = 8192 / 2;		
		int xWidth2 = screen->anx(320) / 2;
		int xHeight2= screen->any(200) / 2;
		save_screen	=  zNEW( zCView(mid-xWidth2,mid-xHeight2,mid+xWidth2,mid+xHeight2) );
		screen -> InsertItem (save_screen);	

		zoptions->ChangeDir(DIR_TEX_DESKTOP);
		save_screen->InsertBack("saving.tga");		

		progressBar = zNEW( oCViewGothicProgressBar(2000,5700,8192-2000,6900) );
		progressBar->SetMinimumStep(3);
	}	
	else
	{	
		save_screen	= 0;
	};	

	// ProgressBar erzeugen	
	if (progressBar) 
	{
		save_screen->InsertItem		(progressBar);
		progressBar->Init();
	}

	screen	 ->DrawItems			();		

	zrenderer->Vid_Blit(FALSE);

	if (GetWorld()) GetWorld()->SetProgressBar(progressBar);

	zERR_MESSAGE(5,0,"B: GAM: OpenSavescreen finished");
};

void oCGame :: CloseSavescreen()
{	
#ifdef COMPILING_SPACER
	return;
#endif
				
	delete progressBar;
	delete save_screen;
	save_screen = 0;	
	progressBar = 0;
	if (GetWorld()) GetWorld()->SetProgressBar(NULL);
};




////////////////////////////////////////
// LOAD-SCREEN
////////////////////////////////////////

void oCGame::OpenLoadscreen	(bool gameStart, zSTRING worldName)
{
#ifdef COMPILING_SPACER
	return;
#endif

	if (load_screen) CloseLoadscreen();

	zERR_MESSAGE(5,0,"B: GAME: OpenLoadscreen");
			
	if (gameStart) 
	// neustart
	{	
		load_screen	=  zNEW( zCView(0,0,8192,8192) );		
		screen -> InsertItem (load_screen);	

		zSTRING loadingBackground = zoptions->GetDirString(DIR_TEX_DESKTOP)+"loading.tga";				
		loadingBackground.Lower();
		load_screen->InsertBack(loadingBackground);
		
//		progressBar = zNEW( oCViewGothicProgressBar(2000,6100,8192-2000,6600) );		// gothic 1 
		progressBar = zNEW( oCViewGothicProgressBar(8192-3500,1000,8192-500,1500) );

		progressBar->SetMinimumStep(3);
	}	
	else
	// Levelwechsel
	{	

		load_screen	=  zNEW( zCView(0,0,8192,8192) );
		F -> InsertItem (load_screen);	

		zFILE_FILE filePath(worldName);

		// zSTRING loadingBackground = zoptions->GetDirString(DIR_TEX_DESKTOP)+"loading.tga";				
		zSTRING loadingBackground = zoptions->GetDirString(DIR_TEX_DESKTOP)+"loading_"+filePath.GetFilename()+".tga";		
		loadingBackground.Lower();
		load_screen->InsertBack(loadingBackground);		
		
		//progressBar = zNEW( oCViewGothicProgressBar(2000,6100,8192-2000,6600) );
		progressBar = zNEW( oCViewGothicProgressBar(8192-3500,1000,8192-500,1500) );
		progressBar->SetMinimumStep(3);
	};	

	// ProgressBar erzeugen	
	if (progressBar) 
	{
		load_screen->InsertItem		(progressBar);
		progressBar->Init();
	}

	screen	 ->DrawItems			();		
	zrenderer->Vid_Blit(FALSE);
	
	if (GetWorld()) GetWorld()->SetProgressBar(progressBar);

	zERR_MESSAGE(5,0,"B: GAME: OpenLoadscreen finished");
};

void oCGame :: CloseLoadscreen()
{	
#ifdef COMPILING_SPACER
	return;
#endif

	delete progressBar;
	delete load_screen;
	load_screen = 0;
	progressBar = 0;
	if (GetWorld()) GetWorld()->SetProgressBar(NULL);
};




// ****************************************************************************************
// Info Procs
// ****************************************************************************************

oCWorld* oCGame :: GetGameWorld()
{ 
	return zDYNAMIC_CAST<oCWorld>(GetWorld()); 
};

oCNpc* oCGame :: GetSelfPlayerVob()
{
	return oCNpc::player;
	//return (zCPlayerInfo::GetActivePlayer()->GetPlayerVob());
}

zCView* oCGame :: GetTextView()
{
	return game_text;
}

oCWorldTimer* oCGame :: GetWorldTimer()
{
	return wldTimer;
}

oCInfoManager* oCGame :: GetInfoManager()
{
	return infoman;
}

oCNewsManager* oCGame :: GetNewsManager()
{
	return newsman;
}

oCSVMManager* oCGame :: GetSVMManager()
{
	return svmman;
}

oCTradeManager* oCGame :: GetTradeManager()
{
	return trademan;
}

oCGuilds* oCGame :: GetGuilds()
{
	return guilds;
}

oCGameInfo* oCGame :: GetGameInfo ()
{
    return gameInfo;
};

oCPortalRoomManager* oCGame :: GetPortalRoomManager	()
{
	return portalman;
};

oCSpawnManager* oCGame :: GetSpawnManager ()
{
	return spawnman;
};

// ***********************************************************************************
// Music - Control
// ***********************************************************************************

oHEROSTATUS oCGame :: GetHeroStatus()
{
	oHEROSTATUS res = oHERO_STATUS_STD;
	if (oCNpc::player) {
		oCAIHuman* ai = zDYNAMIC_CAST<oCAIHuman>(oCNpc::player->GetAI());
		if (ai) res = ai->GetEnemyThreat();
	}
//	screen->Print(0,4000,"EnemyThreat: "+zSTRING(int(res)));
	return res;
};

// ***********************************************************************************
// TOOLS
// ***********************************************************************************

void oCGame :: SetShowNews(oCNpc* npc)
{
	oCNpc* found	= NULL;
	zCListSort<oCNpc>* node = GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (node) {
		found	= node->GetData();
		node	= node->GetNextInList();

		found->SetShowNews(npc==found);
	}
};

void oCGame :: SetShowPlayerStatus(zBOOL showIt)
{
	if (!showIt) {
		screen->RemoveItem(hpBar);
		screen->RemoveItem(swimBar);
		screen->RemoveItem(manaBar);
		screen->RemoveItem(focusBar);
	}
	showPlayerStatus = showIt;
}

zBOOL oCGame :: GetShowPlayerStatus()
{
	return showPlayerStatus;
}

void oCGame::UpdateScreenResolution()
{
	zoptions->ChangeDir(DIR_TEX_DESKTOP);

	screen			-> SetFont(0);
	int sy			=  screen -> FontY();
	
	int nWidthScreen	= VIEW_VXMAX;	
	int nHeightScreen	= VIEW_VYMAX;											
	int nViewWidth		= screen->anx(600);				// Breite (Pixeln -> Logical)
	int nMarginX		= (VIEW_VXMAX - nViewWidth)/2;	// Restrand, so dass die Anzeige mittig ist
	int nMarginY		= screen->any(20);				// Rand nach unten (Pixeln -> Logical)

	// Textfenster f�r Dialoge
	game_text->SetPos	(nMarginX,sy*2);
	game_text->SetSize	(nViewWidth,sy*2 + sy*4 + sy / 4);		
		
	int	nHeightConversation = 6 * sy	;	int nYConversation	= nMarginY;
	int nHeightAmbient		= 5 * sy	;	int nYAmbient		= nHeightScreen - nMarginY - nHeightAmbient;
	int nHeightDynamic		= 4 * sy	;	int nYDynamic		= nYAmbient - (5 * sy);				
	int nHeightChoice		= 4 * sy	;	int nYChoice		= nYConversation + nHeightConversation + sy;				
	int nHeightCinema		= 4 * sy	;	int nYCinema		= nHeightScreen - nMarginY - nHeightCinema + 0.5 * sy;

	array_view[oTGameDialogView::GAME_VIEW_SCREEN]			->SetPos	(0,0);
	array_view[oTGameDialogView::GAME_VIEW_SCREEN]			->SetSize	(nWidthScreen,nHeightScreen);

	array_view[ oTGameDialogView::GAME_VIEW_CONVERSATION]	->SetPos	(nMarginX	, nYConversation);	
	array_view[ oTGameDialogView::GAME_VIEW_CONVERSATION]	->SetSize	(nViewWidth	, nHeightConversation);	
	array_view[ oTGameDialogView::GAME_VIEW_AMBIENT]		->SetPos	(nMarginX	, nYAmbient);
	array_view[ oTGameDialogView::GAME_VIEW_AMBIENT]		->SetSize	(nViewWidth	, nHeightAmbient);
	array_view[ oTGameDialogView::GAME_VIEW_CINEMA]			->SetPos	(nMarginX	, nYCinema);
	array_view[ oTGameDialogView::GAME_VIEW_CINEMA]			->SetSize	(nViewWidth	, nHeightCinema);
	array_view[ oTGameDialogView::GAME_VIEW_NOISE]			->SetPos	(nMarginX	, nYDynamic);
	array_view[ oTGameDialogView::GAME_VIEW_NOISE]			->SetSize	(nViewWidth	, nHeightDynamic);
 	array_view[ oTGameDialogView::GAME_VIEW_CHOICE]			->SetPos	(nMarginX	, nYChoice);
	array_view[ oTGameDialogView::GAME_VIEW_CHOICE]			->SetSize	(nViewWidth	, nHeightChoice);

	// Groesse der normalen Bars am unteren Rand in Pixeln
	const int barSizeX = 180;
	const int barSizeY = 20;

	int bottomTop = 8192 - screen->any(10+barSizeY);
	int xs,ys;

	screen->InsertItem		(hpBar);
	screen->InsertItem		(swimBar);				
	screen->InsertItem		(manaBar);						
	screen->InsertItem		(focusBar);		
	// hpBar: unten links
	hpBar->Init				(screen->anx(10),bottomTop);
	// manaBar, unten rechts
	manaBar -> Init			(8192-screen->anx(barSizeX+10),bottomTop);
	// swimBar, unten mitte
	swimBar->Init			(0,0);	
	swimBar->GetSize		(xs,ys);
	swimBar->SetPos			((8192-xs)/2.0f , bottomTop);
	// focus bar, oben mitte
	focusBar->Init			(0,0,0.75);	
	focusBar->GetSize		(xs,ys);
	focusBar->SetPos		((8192-xs)/2.0f , screen->any(10));
	
	screen->RemoveItem		(hpBar);
	screen->RemoveItem		(swimBar);	
	screen->RemoveItem		(manaBar);
	screen->RemoveItem		(focusBar);
}

void oCGame :: UpdatePlayerStatus ( )
{
	// Nur vom Player anzeigen
	if (!oCNpc::player)			return;	// Spieler nicht definitiert
	if (!GetShowPlayerStatus()) return;	// Ausgeschaltet	

	screen->RemoveItem(hpBar);
	screen->RemoveItem(swimBar);
	screen->RemoveItem(manaBar);
	screen->RemoveItem(focusBar);
	
	if (GetWorld() && (GetWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene()!=0)) return;	
	//if (GetCamera()->IsScreenFadeEnabled())		return;
	//if (GetCamera()->IsCinemaScopeEnabled())	return;

	// [EDENFELD] 1.09
	// precalc preview values if inventory is opened
	int selItemAtrHitpoints	= 0;
	int selItemAtrMana		= 0;
	if (oCNpc::player->inventory2.IsOpen())
	{
		oCItem* item = oCNpc::player->inventory2.GetSelectedItem();
		if (item)
		{
			// Hitpoints
			selItemAtrHitpoints = item->nutrition;
			if (!selItemAtrHitpoints)
				for (int i = 0; i < ITM_COND_MAX; i++)
					if (item->change_atr[i] == NPC_ATR_HITPOINTS)
						selItemAtrHitpoints += item->change_value[i];
			
			// Mana
			for (int i = 0; i < ITM_COND_MAX; i++)
				if (item->change_atr[i] == NPC_ATR_MANA)
					selItemAtrMana += item->change_value[i];
		}
	}

	// ********************
	// Hitpointsbar
	// ********************
	screen->InsertItem	(hpBar);	
	
	hpBar ->SetMaxRange	(0,oCNpc::player->GetAttribute(NPC_ATR_HITPOINTSMAX));
	hpBar ->SetRange	(0,oCNpc::player->GetAttribute(NPC_ATR_HITPOINTSMAX));	
	hpBar ->SetPreview	(oCNpc::player->GetAttribute(NPC_ATR_HITPOINTS) + selItemAtrHitpoints);
	hpBar ->SetValue	(oCNpc::player->GetAttribute(NPC_ATR_HITPOINTS));
	
	// ********************
	// DiveBar
	// ********************
	if (oCNpc::player->GetAnictrl()) {
		int wm = oCNpc::player->GetAnictrl()->GetWalkMode();
		if (wm==ANI_WALKMODE_DIVE)
		{	
			//
			//	CODECHANGE [ROMAN|SPECKELS]
			//
			zREAL swimtime,divetime,dive_value;
			oCNpc::player->GetSwimDiveTime	(swimtime,divetime,dive_value);
			screen->InsertItem				(swimBar);		
			
			// int dive_max = 120 * 1000.0;
			int dive_max = divetime;
			
			if (divetime == ANI_TIME_INFINITE) dive_value = dive_max;
			// else if ((divetime>0) && (divetime <= dive_max)) dive_max = divetime;
			
			swimBar->SetMaxRange	(0,dive_max);
			swimBar->SetRange		(0,dive_max);
			swimBar->SetValue		(dive_value);
							
			//
			//	CODECHANGE [ROMAN|SPECKELS] END
			//
		}
	}

	// ********************
	// ManaBar
	// ********************
	if (oCNpc::player->inventory2.IsOpen() || oCNpc::player->GetWeaponMode()==NPC_WEAPON_MAG) 
	{
		int nManaMax = oCNpc::player->GetAttribute(NPC_ATR_MANAMAX);
		if ( nManaMax > 0 )
		{
			screen	-> InsertItem	(manaBar);			
			manaBar	-> SetMaxRange	(0,nManaMax);
			manaBar	-> SetRange		(0,nManaMax);		
			manaBar -> SetPreview	(oCNpc::player->GetAttribute(NPC_ATR_MANA) + selItemAtrMana);
			manaBar	-> SetValue		(oCNpc::player->GetAttribute(NPC_ATR_MANA));
		}
	}

	// [BENDLIN] AddonMOD
	static bool  read_FocusOpt	= true;
	static zBOOL show_Focus		= TRUE;
	static zBOOL show_FocusItm	= TRUE;
	static zBOOL show_FocusMob	= TRUE;
	static zBOOL show_FocusNpc	= TRUE;
	static zBOOL show_FocusBar	= TRUE;
	if (read_FocusOpt)
	{
		read_FocusOpt = false;
		if (zgameoptions)
		{
			show_Focus		= zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "show_Focus",	show_Focus		);
			show_FocusItm	= zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "show_FocusItm",	show_FocusItm	);
			show_FocusMob	= zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "show_FocusMob",	show_FocusMob	);
			show_FocusNpc	= zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "show_FocusNpc",	show_FocusNpc	);
			show_FocusBar	= zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "show_FocusBar",	show_FocusBar	);
		}
	}
	if (show_Focus)
	{
		// ********************
		// FokusInfo
		// ********************
		zSTRING text;
		int		hp			= 0;
		int		hpMax		= 0;
		zCVob*	focus		= oCNpc::player->GetFocusVob();
		oCNpc*	other		= NULL;
		zBOOL	bShowFocus	= TRUE;

		if (zDYNAMIC_CAST<oCMOB>(focus)) 
		{
			text		= static_cast<oCMOB*>(focus)->GetName();	
			bShowFocus	= show_FocusMob;
		} 
		else if (other = zDYNAMIC_CAST<oCNpc>(focus)) 
		{	
			text		= other->GetName		();
			hp			= other->GetAttribute	(NPC_ATR_HITPOINTS);
			hpMax		= other->GetAttribute	(NPC_ATR_HITPOINTSMAX);		
			bShowFocus	= other->GetCanBeFocused() && (show_FocusNpc || show_FocusBar);
		} 
		else if (dynamic_cast<oCItem*>(focus)) 
		{		
			text		= static_cast<oCItem*>(focus)->GetName(TRUE);
			bShowFocus	= show_FocusItm;
		}

		if (!bShowFocus) return;
		
		if ((hp > 0) && show_FocusBar) 
		{		
			screen	 -> InsertItem	(focusBar);
			focusBar -> SetMaxRange	(0,hpMax);
			focusBar -> SetRange	(0,hpMax);
			focusBar -> SetValue	(hp);
		}

		// Fokus Namen anzeigen
		if (focus && focus->GetVisual() && (!other || show_FocusNpc))
		{
			zPOINT3 focusNamePosWS;

			const zCClassDef *classDef0	= focus->GetVisual()->GetClassDef();
			const zCClassDef *classDef1	= zCModel::GetStaticClassDef();
			// SUPER: mal wieder ein Compiler-Bug folgender zweiter Teil folgendes if Statements liefert IMMER FALSE!
			// if ((focus->GetVisual()) && (focus->GetVisual()->GetClassDef==zCModel::GetStaticClassDef()))
			if ((focus->GetVisual()) && (classDef0==classDef1))
			{
				zCModel *model						= static_cast<zCModel*>(focus->GetVisual());
				const zTBBox3D& modelBoxLocalFixed	= model->GetBBox3DLocalFixed();
				focusNamePosWS						= focus->GetPositionWorld();
				focusNamePosWS.n[VY]				+= (modelBoxLocalFixed.maxs[VY])*1.6F;

				const zREAL bboxTopWS				= (focus->GetBBox3DWorld().maxs[VY]) + zREAL(100.0F); 
				if (focusNamePosWS.n[VY]>bboxTopWS)
					focusNamePosWS.n[VY]			= bboxTopWS;
			} else
			{
				focusNamePosWS						= focus->GetBBox3DWorld().GetCenter();
				focusNamePosWS.n[VY]				+= (focus->GetBBox3DWorld().maxs.n[VY] - focus->GetBBox3DWorld().mins.n[VY])*0.82F;
			};

			zCCamera::activeCam->Activate();
			zPOINT3	  ProjPoint1	= zCCamera::activeCam->Transform (focusNamePosWS);
			if (ProjPoint1[VZ]>0.0f) 
			{
				zPOINT2	  ProjPoint2;
				zCCamera::activeCam->Project (&ProjPoint1, ProjPoint2[VX], ProjPoint2[VY]);
				ProjPoint2[VX]		= ProjPoint2[VX] - screen->nax(screen->FontSize(text+"\n") / 2);

				// CLAMP
				int nX				= screen->anx(ProjPoint2[VX]);
				int nY				= screen->any(ProjPoint2[VY]);

				if ( nY <		 screen->FontY() ) nY =			screen->FontY();
				if ( nY > 8192 - screen->FontY() ) nY = 8192 -  screen->FontY();

				// [Ulf] Clampen auch in X-Richtung
				zClamp				(nX,0,8191-screen->FontSize(text));

				// NOTE Here is focus vob print -> use it to fix floating UI in mod
				// PRINT
				if (oCNpc::GetTargetLocked()) text+= " (locked)";
				screen->Print		(nX,nY, text+"\n");

			};
		}
		//screen->PrintCX(0,text+"\n");
	}
};

void oCGame :: RemoveHelperVobs ( zCTree <zCVob> *node )
{
	if (node == NULL) return;
	
	zTVobType t;
	zCVobWaypoint* wp;

	t = node -> GetData() -> GetVobType();
	
	// Besondere Behandlung der Helper-Vobs
	switch (t) {
	
		case zVOB_TYPE_LIGHT	:	node -> GetData() -> SetVisual		(NULL);
									node -> GetData() -> SetShowVisual	(TRUE);
									break;
		case zVOB_TYPE_WAYPOINT	:	wp = (zCVobWaypoint *)node -> GetData();
									wp -> SetShowVisual	(FALSE);
									wp -> SetCollDet	(FALSE);
									break;
		case zVOB_TYPE_SOUND	:	case zVOB_TYPE_SPOT			:
		case zVOB_TYPE_CAMERA	:	case zVOB_TYPE_STARTPOINT	:

									node -> GetData() -> SetShowVisual	(FALSE);
//									node -> GetData() -> SetDrawBBox3D	(TRUE);
									node -> GetData() -> SetCollDetDyn	(FALSE);
									node -> GetData() -> SetCollDetStat	(FALSE);
									break;
//		case zVOB_TYPE_NSC		:	if (node -> GetData() != oCNpc::player)
//										node -> GetData() -> SetAICallback (NULL);
									break;
	}

	RemoveHelperVobs ( node->GetFirstChild() );
	RemoveHelperVobs ( node->GetNextChild() );
}

void oCGame :: CreateVobList(zCList <zCVob> &resultlist, zCTree <zCVob> *node, zTVobType vobtyp)
{
	if (node == NULL) return;

	if (node -> GetData() -> GetVobType() == vobtyp) {
		// found one
		resultlist.Insert(node->GetData());
	}

	CreateVobList ( resultlist, node->GetFirstChild(), vobtyp );
	CreateVobList ( resultlist, node->GetNextChild(), vobtyp );					
}

void oCGame :: SetAsPlayer(const zSTRING& name)
{
	int index	= parser.GetIndex(name);
	oCNpc* npc	= (oCNpc*)SearchVobByInstance(&GetWorld()->globalVobTree,index);
	if (!npc) {
		// Nix gefunden, dann in der vobList_Npc suchen
		zCListSort<oCNpc>* npcNode = GetGameWorld()->GetVobListNpcs()->GetNextInList();
		while (npcNode) {
			npc		= npcNode->GetData();
			npcNode = npcNode->GetNextInList();
			if (npc->GetInstanceName()==name) {
				// Nicht in der Welt...
				if (!npc->GetHomeWorld()) {
					npc->Enable(npc->GetPositionWorld());	
				}
				break;
			}
		}
	}
	
	if (npc) 
	{
		npc -> SetAsPlayer();
	} 
	else 
	{
		zERR_MESSAGE(5,0,"U: GAME: Npc "+name+" not found.");
	}
}

void oCGame::SetupPlayers(oCNpc*& playerVob, const zSTRING& startpoint)
// Es gibt drei Faelle :
// a) STARTUP		: SC erzeugen und an Startpunkt setzen
// b) LEVELCHANGE	: SC an Startpunkt setzen
// c) LOAD GAME     : SC beh�lt Position aus Zen-File
{		
	if (progressBar) progressBar->SetPercent(0);	

	///
	// 1. Startpunkt suchen
	///

	zMAT4 initialStartMatrix;
	initialStartMatrix = Alg_Identity3D();

	if (!startpoint.IsEmpty())
	// 1.a) Benutze uebergebenen Startpunkt-Namen
	{
		// i) Normalen Vob suchen
		zCVob* startVob = GetGameWorld()->SearchVobByName(startpoint);
		if (startVob) initialStartMatrix = startVob->trafoObjToWorld;			
		else 
		{
			// ii) Wegpunkt suchen
			zCWaypoint* wp = GetGameWorld()->GetWayNet()->GetWaypoint((zSTRING)startpoint);
			if (wp) 
			{
				initialStartMatrix.SetTranslation	( wp->GetPositionWorld() );
				initialStartMatrix.SetAtVector		( wp->GetAtVectorWorld() );	
			} else {
				zERR_WARNING("U: WLD: Startpoint "+startpoint+" not found.");
				initialStartMatrix.SetTranslation	( zVEC3(0,150,0) );
				initialStartMatrix.SetAtVector		( zVEC3(1,0,0) );
			}
		}
	}
	else
	// 1.b) Eine beliebige Position auswaehlen
	{
		zCList <zCVob> resultlist;
		CreateVobList (resultlist,GetWorld()->globalVobTree.GetFirstChild(), zVOB_TYPE_STARTPOINT );
		if (resultlist.GetNumInList()>0) 
		// i) Den erstbesten START-POINT
		{
			zVEC3 pos;
			zCVob* startVob  = resultlist.Get(0);			
			initialStartMatrix.SetTranslation	( startVob->GetPositionWorld() );
			initialStartMatrix.SetAtVector		( startVob->GetAtVectorWorld() );				
		}
		else 
		// ii) am Ursprung
		{
			initialStartMatrix.SetTranslation	( zVEC3(0,150,0) );
			initialStartMatrix.SetAtVector		( zVEC3(1,0,0) );
		}
		resultlist.DeleteList();
	};	

	if (progressBar) progressBar->SetPercent(30);

	///
	// 2. Der eigene Spieler
	///

	// 2.a) erzeugen
	zBOOL	playerCreated = FALSE;
	zSTRING instanceName;
	if (!playerVob) 
	{	
		// [BENDLIN] AddonMOD
		if (zgameoptions)
			instanceName = zgameoptions->ReadString(zOPT_SEC_SETTINGS, "Player");
		else
			instanceName = zoptions->ReadString(zOPT_SEC_INTERNAL, "playerInstanceName");
		if (instanceName.IsEmpty())
			instanceName = "PC_Hero";

		playerVob = (oCNpc*) GetGameWorld() -> CreateVob (zVOB_TYPE_NSC, instanceName);
		if (!playerVob)
			zERR_FATAL("U: GAME: Player-creation failed: " + instanceName);			

		playerCreated = TRUE;
	}
	
	if (progressBar) progressBar->SetPercent(90);

	// 2.b) initialisieren

	startpos = initialStartMatrix.GetTranslation(); // globale startposition fuer Reset
	playerVob	->SetCollDet			(FALSE);
	// playerVob	->SetTrafoObjToWorld	(initialStartMatrix);

    playerVob->GetModel(); // [Moos] sorge daf�r, dass das Model existiert, bevor der Spieler in die Welt kommt; sonst sitzt er mit der H�fte im Mesh
	InsertPlayerIntoWorld(playerVob,initialStartMatrix);
	
	playerVob	->SetOnFloor			(startpos);
	playerVob	->ResetXZRotationsWorld ();             // [Moos] 20.12.00 Anpassung an Vob-�nderung
	playerVob	->SetCollDet			(TRUE);

	// Wenn der Player neu erzeugt wurde, muss hier wieder ein Release stattfinden,
	// Fire & Forget -> Den Vob kennt zCWorld und die oCWorld-Listen �ber (InsertPlayerIntoWorld)
	if (playerCreated) zRELEASE_ACCT_NONULL(playerVob);

	oCPlayerInfo* player = dynamic_cast<oCPlayerInfo*>(zCPlayerInfo::GetActivePlayer());
	if (!player)
	{
		// 2.c) als Spieler definieren
		player = (oCPlayerInfo*)zfactory->CreatePlayerInfo();	
		gameInfo	->AddPlayer		(player);					
		player		->SetPlayerVob	(playerVob);		
		player		->SetActive();
	}		

	// 2.d) Referenz setzen	
	oCNpc::player = playerVob;	
	playerVob->SetAsPlayer();

	if (progressBar) progressBar->SetPercent(100);

	// Check, ob Player auch initialisiert wurde :
	if (!oCNpc::player || (oCNpc::player->GetInstance()<0)) {
		zERR_FATAL ("U: GAME: Player-Script-Instance not found : "+instanceName);
	} 
}
		
void oCGame :: SetRanges()
{
	// FarClip
	GetCamera()	-> SetFarClipZ		( cliprange );
	zrenderer	-> SetFogRange		( fogrange, GetCamera()->GetFarClipZ() );
	zrenderer	-> SetFog			( TRUE );
}

void oCGame :: SetRangesByCommandLine()
{
	// Set Viewrange per CommandLine ?
	if (zoptions->Parm("CLIPRANGE"))	cliprange		= (float)zoptions->ParmValueInt("CLIPRANGE");
	if (zoptions->Parm("FOGRANGE"))		fogrange		= (float)zoptions->ParmValueInt("FOGRANGE");
	
	playerLightInt = zoptions->ReadInt(zOPT_SEC_GAME,"cameraLightRange",0);
	if (zoptions->Parm("CAMLIGHTRANGE")) 
	{
		playerLightInt	= zoptions->ParmValueInt("CAMLIGHTRANGE");
		zoptions->WriteInt(zOPT_SEC_GAME,"cameraLightRange",playerLightInt,TRUE);
	}
	
	
	if (zoptions->Parm("LIGHTRANGE") && pl_light) {
		pl_lightval	= (float)zoptions->ParmValueInt("LIGHTRANGE");
		pl_light   -> SetRange(pl_lightval);
	}
	else if (pl_light)
	{
		pl_light   -> SetRange(0);
	};

	SetRanges();
}

void oCGame :: EnvironmentInit()
// Initialize World with Standard - Values
{
	// *********************************
	// Setup Standard Environment Values
	// *********************************
	zTBspTreeMode game_leveltype = GetWorld() -> GetBspTree() -> GetBspTreeMode();
	if (game_leveltype==zBSP_MODE_INDOOR) {		
		// *****************************
		// INDOOR
		// *****************************
		// Create Player Light - TEMP
        zRELEASE(pl_light); // [Moos] Leakfix f�r Laden
		pl_light  = zNEW(zCVobLight);
		pl_light -> Move			(200,170,-150);
		pl_light -> SetRange		(100);
		pl_light -> SetColor		(255,200,155);
		pl_light -> SetIsStatic		(FALSE);
		playerLightInt = 5000;
		//		GetWorld()	 -> AddVobAsChild	(pl_light,GetSelfPlayerVob());
	} else {
		// *****************************
		// OUTDOOR
		// *****************************
		
		float farz = 60000;

		zCOLOR fogCol;
		fogCol.SetRGB	(100,100,100);
		cliprange		= farz;
		fogrange		= farz * 0.25F;		
		playerLightInt	= 0;
		GetCamera()->SetFarClipZ(farz);
		zrenderer->SetFogRange	(farz, GetCamera()->GetFarClipZ(), zRND_FOG_FALLOFF_LINEAR);
		zrenderer->SetFog		(TRUE);
		zrenderer->SetFogColor	(fogCol);	
	}
	// Set Ranges by CommandLine
	SetRangesByCommandLine();
}

// ****************************************************************************************
// Load / Save
// ****************************************************************************************

zBOOL oCGame :: LoadParserFile (const zSTRING &parserfile)
{
	zSTRING file = parserfile;
	file.Upper					();
	parser.Reset				();

//	zCList<zSTRING> funclist;
//	funclist.Insert				(new zSTRING("AI_OUTPUT"));
//	parser.SetInfoFile			(&funclist,"TESTINFO.TXT");
	// ****
	DefineExternals_Ulfi		(&parser);
	parser.EnableTreeLoad		(FALSE);
	parser.EnableTreeSave		(FALSE);
	parser.Parse				(file);	

	// Offset Correction for Classes
	parser.AddClassOffset		(zSTRING("C_NPC" ),sizeof(oCVob));
	parser.AddClassOffset		(zSTRING("C_ITEM"),sizeof(oCVob));
	parser.CreatePCode			();

	return !parser.Error		();
}

void oCGame :: SetTime(int day, int hour, int min) 
{
	// aktuelle Zeit speichern
	int hour1,min1;
	GetWorldTimer()->GetTime(hour1,min1);
	// neue Zeit setzen
	GetWorldTimer()->SetDay (day + (hour/24));
	GetWorldTimer()->SetTime(hour,min);	
	// NSC - Tagesabl�ufe
	rtnMan.SetDailyRoutinePos(TRUE);
	// Object - Tagesablaufe 
	SetObjectRoutineTimeChange(hour1,min1,hour,min);
	// Respawning aktivieren
	if (spawnman) spawnman->SpawnImmediately(TRUE);
}

void oCGame :: GetTime(int& day, int& hour, int& min) 
{
	day = GetWorldTimer()->GetDay();
	GetWorldTimer()->GetTime(hour,min);
};

zBOOL oCGame :: LoadWorld (const zSTRING& pwf, zCWorld::zTWorldLoadMode loadmode)
{
	// FIXME : Nur Spacer-relevant ?
	zBOOL f = FALSE;
	if (GetWorld()) 
	{
		f = GetWorld()->LoadWorld(pwf,loadmode);
		// Removing Helper Vobs 
		// FIXME : hier doppelt gemoppelt 
		RemoveHelperVobs( GetWorld()->globalVobTree.GetFirstChild() );
	}
	return f;
}

void oCGame :: SaveWorld (const zSTRING& pwf, zCWorld::zTWorldSaveMode savemode, BOOL savemesh, BOOL saveBin)
{
	zMATRIX4 trafo;
	oCNpc* oldPlayer = NULL;
	// Player entfernen
	if (oCNpc::player) {
		trafo		= oCNpc::player -> trafoObjToWorld;
		oldPlayer	= RemovePlayerFromWorld();
	}
	if (GetWorld()) {
		// Die Welt speichern
		GetWorld()->SaveWorld(pwf,savemode,saveBin,savemesh);
	}
	// Player einf�gen
	if (oldPlayer) {
		InsertPlayerIntoWorld(oldPlayer,trafo);
	}
}

oCNpc* oCGame :: RemovePlayerFromWorld()
{
	oCNpc* tmp = GetSelfPlayerVob();
	if (tmp) {
		zADDREF_ACCT(tmp);
		
		tmp->SetGroundPoly					(NULL);
		tmp->ClearPerceptionLists			();
		// aus Welt und Listen entfernen
		GetGameWorld()->RemoveVob			(tmp);
		// Player auf Null.
		oCNpc::player = NULL;
	}
	return tmp;
}

void oCGame :: InsertPlayerIntoWorld(oCNpc* npc, zMATRIX4& trafo)
{
	if (npc && !npc->GetHomeWorld()) {
		
		trafo.MakeOrthonormal();

		npc		-> SetGroundPoly		(NULL);	// FIXME : ohne den Befehl gabs hier nochmal abnippler !
		GetWorld()	-> AddVob				(npc);
		npc		-> SetCollDet			(FALSE);		
		npc		-> SetTrafoObjToWorld	(trafo);		
		npc     -> SetOnFloor			(trafo.GetTranslation());
		npc		-> SetCollDet			(TRUE);
		
		// Player aktivieren
		oCNpc::player = npc;
	}
}

void oCGame :: PreSaveGameProcessing(zBOOL saveGlobals)
{	
	// Allen NSCs die InteractItems aus den Haenden nehmen....
	zCListSort<oCNpc>* npcNode = GetGameWorld()->GetVobListNpcs()->GetNextInList();
	oCNpc* npc = NULL;
	while (npcNode) {
		npc		= npcNode->GetData();
		npcNode = npcNode->GetNextInList();
		npc->PreSaveGameProcessing();
	}
	// Aus allen Feuermobsis die Vobtrees entfernen....
	zCListSort<zCVob>* mobNode = GetGameWorld()->GetVobList()->GetNextInList();
	oCMobFire* mob = NULL;
	while (mobNode) {
		mob		= zDYNAMIC_CAST<oCMobFire>(mobNode->GetData());
		mobNode = mobNode->GetNextInList();
		if (mob) mob->PreSave();
	}	
	// Visual FX entfernen
	oCVisualFX::PreSaveGameProcessing(!saveGlobals);
};

void oCGame :: PostSaveGameProcessing()
{
	// Allen NScs die InteractItems wieder in die Haende druecken...
	zCListSort<oCNpc>* npcNode = GetGameWorld()->GetVobListNpcs()->GetNextInList();
	oCNpc* npc = NULL;
	while (npcNode) {
		npc		= npcNode->GetData();
		npcNode = npcNode->GetNextInList();
		npc->PostSaveGameProcessing();
	}
	// Patch 1.08 : FeuerTrees muessen bei Levelchange nicht wieder aktiviert werden
	// (Level wird ja verlassen). Spart ein paar Sekunden.
	if (!inLevelChange) {
		// und allen Feuermobsis die Vobtrees wieder anhaengen....
		zCListSort<zCVob>* mobNode = GetGameWorld()->GetVobList()->GetNextInList();
		oCMobFire* mob = NULL;
		while (mobNode) {
			mob		= zDYNAMIC_CAST<oCMobFire>(mobNode->GetData());
			mobNode = mobNode->GetNextInList();
			if (mob) mob->PostSave();
		}	
	}
	// Visual FX einsetzen
	oCVisualFX::PostSaveGameProcessing();
};

/* ------------------------------------------------------------------------------

	void oCGame::WriteSavegame (int slotnr, zBOOL saveGlobals)

	6.10.2000	[SPECKELS]	Savescreen bei einem Savegame hinzugefuegt

   ------------------------------------------------------------------------------ */

void oCGame :: WriteSavegame (int slotnr, zBOOL saveGlobals)
{
	if (saveGlobals) OpenSavescreen(TRUE);

	if (progressBar) progressBar->SetPercent(0);

	zoptions->ChangeDir(DIR_SAVEGAMES);		
	zSTRING sourceDir = savegameManager->GetSlotDirName(SAVEGAME_SLOT_CURRENT);
	zSTRING targetDir = savegameManager->GetSlotDirName(slotnr);

	if (GetWorld()) {		

		// *******************************
		// SaveGame Verzeichnis ermitteln
		// *******************************
		zSTRING levelname;
	
		if (progressBar) progressBar->SetPercent(5);

		// **********************************
		// Copy Current Dir to Savegame Slot
		// **********************************
		if (slotnr>=SAVEGAME_SLOT_QUICK && slotnr<=SAVEGAME_SLOT_MAX) 
		{
			savegameManager->CopyFromCurrent(slotnr);			
		}
		
		if (progressBar) progressBar->SetPercent(10);

		// ***********************
		// Header Datei schreiben
		// ***********************
		zSTRING wn				= GetGameWorld()->GetWorldFilename();
		zSTRING headerfilename	= targetDir + "savehdr.sav";
		zFILE* f				= zfactory->CreateZFile(headerfilename);
		f -> Create();
		f -> Write (wn+"\n");
		f -> Close ();
		delete f;
		
		if (progressBar) progressBar->SetPercent(12);

		// **************************
		// Dynamische Welt schreiben
		// **************************		
		zPATH path(wn);
		levelname = zoptions->GetDirString(DIR_SAVEGAMES)+targetDir+path.GetFilename()+"."+SAVEGAME_EXT;
		if (progressBar) progressBar->SetRange(12,92);
		
		PreSaveGameProcessing(saveGlobals);
		/* BINARY */ GetWorld()->SaveWorld(levelname,zCWorld::zWLD_SAVE_GAME_SAVED_DYN,TRUE,FALSE);
		/* ASCII  */ // GetWorld()->SaveWorld(levelname,zCWorld::zWLD_SAVE_GAME_SAVED_DYN,FALSE,FALSE);
		PostSaveGameProcessing();
		
		if (progressBar) progressBar->ResetRange();

		if (progressBar) progressBar->SetPercent(92);
	
		// **************************
		// Kamera wieder an
		// **************************
		SetCameraPosition();
	}
	if (saveGlobals) {

		if (progressBar) progressBar->SetPercent(95);

		// komplettes SaveGame 
		// bei einem Levelwechsel darf dieser Teil nicht durchgef�hrt werden.
		zCArchiver* Archiver = zarcFactory.CreateArchiverWrite(zoptions->GetDirString(DIR_SAVEGAMES)+targetDir+SAVEGAME_GLOBAL_FILE,/*zARC_MODE_ASCII,TRUE);*/zARC_MODE_BINARY_SAFE,TRUE);
		
		int hour,min,day;
		GetWorldTimer()->GetTime(hour,min);
		day = GetWorldTimer()->GetDay ();
		Archiver->WriteInt("day", day);
		Archiver->WriteInt("hour", hour);
		Archiver->WriteInt("min", min);
		GetInfoManager()->Archive(*Archiver);
		misMan.Archive(*Archiver);
		oCLogManager::GetLogManager().Archive(*Archiver);
		Archiver->WriteObject(GetCutsceneManager());
		parser.SaveGlobalVars(*Archiver);
		guilds->SaveGuildTable(*Archiver);
		Archiver->Close();
		zRELEASE(Archiver);		

		if (progressBar) progressBar->SetPercent(98);
	}

	// Activate Camera
	SetCameraPosition();
	
	if (gLogStatistics)
		LogStatisticsWrite(zoptions->GetDirString(DIR_SAVEGAMES)+targetDir); // Patch2, added by Bert (LogStatistics)

	if (progressBar) progressBar->SetPercent(100);

	if (saveGlobals) CloseSavescreen();
}

zBOOL oCGame :: CheckObjectConsistency(zBOOL checkItems)
{
	// Checke auf fehlerhaft �briggebliebene Objekte
	// a) Es darf keine NSCs mehr geben
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		zERR_FAULT("U: GAME: There is an illegal NSC still in NpcList :"+npc->GetInstanceName());
	}
	// a) Es darf keine Items mehr geben
	if (checkItems) {
		oCItem* item = NULL;
		zCListSort<oCItem>* nodeI = GetGameWorld()->GetVobListItems()->GetNextInList();
		while (nodeI) {
			item	= nodeI->GetData();
			nodeI	= nodeI->GetNextInList();
			zERR_WARNING("U: GAME: There is an illegal Item still in ItemList :"+item->GetInstanceName());
		}
	}

	// NSC check 2
	zCClassDef* cdef	= oCNpc::GetClassDef("oCNpc");
	int num				= 0;
	int maxNum			= 0;
	if (!checkItems)	maxNum = 1;		// Spieler ist ok.
	if (cdef) num		= cdef->GetNumLivingObjects();
	if (num>maxNum) {
        cdef->ReportLeaks();
#ifdef GOLDMASTER
		zERR_WARNING("U:NPC: Someone has an illegal Reference to an Npc ! AAArrrrggghhhh :" + zSTRING(num));
#else
		zERR_FAULT("U:NPC: Someone has an illegal Reference to an Npc ! AAArrrrggghhhh :" + zSTRING(num));
#endif

	}

	// News Check....
	if (oCNews::GetRemainingNews()>0) {
		zERR_FAULT("U: NEWS: Illegal News detected holding references to npcs !");
		oCNews::CheckRemainingNews();
	}

	return TRUE;
}

void oCGame :: ClearGameState()
// Spielabhaengige Vars l�schen
{
	// Parser Global Vars resetten
	parser.ResetGlobalVars	();
	parser.SetInstance		("SELF",	NULL);
	parser.SetInstance		("OTHER",	NULL);
	parser.SetInstance		("VICTIM",	NULL);
	parser.SetInstance		("ITEM",	NULL);
	// SpawnListe leeren 
	spawnman->ClearList		();
	// InfoMan clearen
	delete infoman;
	infoman = zNEW( oCInfoManager )( &parser );
	// Clear MissionMan
	misMan.ClearMissions	();
	// Clear Logs
	oCLogManager::GetLogManager().Clear();
	// Clear NewsManager
	delete newsman;
	newsman	= zNEW( oCNewsManager () );
	// Clear Soundos
	zsound->StopAllSounds();
	// delete all homeworld references of all CVisualFX Objects 
	oCVisualFX::PreSaveGameProcessing	(TRUE); 
	oCVisualFX::PostSaveGameProcessing	(); 
	// Clear Cam ?!
	CamInit();
	// Clear DebugList
	oCVob::ClearDebugList();
	// Clear ProtalManager
	if (portalman) portalman->CleanUp();
	// Clear ObjectRoutineList
	ClearObjectRoutineList();
}

void oCGame :: InitNpcAttitudes()
{
	oCNpc* player = GetSelfPlayerVob();
	if (player) {
		// Die pers�nlichen Attit�den initialisieren (aus Gildentabelle)
		zCListSort<oCNpc>* npcNode = GetGameWorld()->GetVobListNpcs()->GetNextInList();
		oCNpc* npc = NULL;
		while (npcNode) {
			npc		= npcNode->GetData();
			npcNode = npcNode->GetNextInList();
			if (npc!=player) {
				int pAtt = ogame->GetGuilds()->GetAttitude(npc->GetTrueGuild(),player->GetTrueGuild());
				npc -> SetTmpAttitude	(pAtt);
				npc -> SetAttitude		(pAtt);
			}
		}
	}
}

void oCGame :: RecurseCacheVobs(zCTree<zCVob>* vobtree)
{
	if (!vobtree) return;
	zCVob* vob = vobtree->GetData();
	
	if (vob && vob->GetVisual()) {		
		visualList.Insert(vob->GetVisual());
		vob->GetVisual()->AddRef();	
	}

	zCTree<zCVob>* child = vobtree->GetFirstChild();
	while (child) {
		RecurseCacheVobs(child);
		child	= child->GetNextChild();
	};
}

void oCGame :: CacheVisualsIn()
{
	if (!GetWorld()) return;

	visualList.DeleteList();
	RecurseCacheVobs(&GetWorld()->globalVobTree);
		
	zERR_MESSAGE(5,0,"U: Cached "+zSTRING(visualList.GetNumInList())+" visuals.");

/*	zCListSort<zCVob>* vobNode = GetGameWorld()->GetVobList()->GetNextInList();
	zCVob* vob = NULL;
	while (vobNode) {
		vob		= vobNode->GetData();
		vobNode = vobNode->GetNextInList();
		if (vob && vob->GetVisual()) {
			visualList.Insert(vob->GetVisual());
			vob->GetVisual()->AddRef();
		}
	}	*/
};

void oCGame :: CacheVisualsOut()
{
	zCVisual* visual = NULL;
	for (int i=0; i<visualList.GetNumInList(); i++) {
		visual = visualList[i];
		if (visual) zRELEASE(visual);
	}
	visualList.DeleteList();
};


void oCGame :: LoadGame(int slotID, const zSTRING& levelpath)
{
#ifdef COMPILING_SPACER
	// folgend Abfrage erspart einem im Spacer beim Menupunkt "PLAY THE GAME" das nochmalige Einladen aller Infos
	if (!levelpath.IsEmpty())
#endif
	ClearGameState			();
	OpenLoadscreen			(TRUE,"");

	if (progressBar) progressBar->SetPercent(0);

	if (progressBar) progressBar->SetRange(0,92);
	LoadWorld		(slotID,levelpath);
	if (progressBar) progressBar->ResetRange();

	if (progressBar) progressBar->SetRange(92,100);
	EnterWorld		();
	if (progressBar) progressBar->ResetRange();

	// Attituden Initialisieren...
	if (slotID == SAVEGAME_SLOT_NEW) {
		InitNpcAttitudes();
	}

	// Reset Time -> schmeisst Tagesablaufvorausberechnung an.	
	SetTime(0,initial_hour, initial_minute);	
	
	if (progressBar) progressBar->SetPercent(100);
	CloseLoadscreen	();
}

void oCGame :: LoadSavegame (int slotnr, zBOOL loadGlobals)
{
	ClearGameState();
	OpenLoadscreen(TRUE,"");
	if (progressBar) progressBar->SetPercent(0);

	zSTRING targetDir = savegameManager->GetSlotDirName(slotnr);
	zSTRING _levelpath;
	
	// Slot IF untersuchen...
	// SaveGame wird vorbereitet -> .
	// SAV und Header ins Current Verzeichnis kopieren.
	if (progressBar) progressBar->SetRange(0,5);
	InitWorldSavegame(slotnr, _levelpath);		
	if (progressBar) progressBar->ResetRange();

	// header-datei lesen		
	zSTRING dirSlotCurrent	= savegameManager->GetSlotDirName(SAVEGAME_SLOT_CURRENT);
	zFILE* headerFile = zfactory->CreateZFile(dirSlotCurrent + "savehdr.sav");
	headerFile->Open();
	headerFile->Read(_levelpath);
	headerFile->Close();
	delete headerFile;		

	if (progressBar) progressBar->SetPercent(5);

	zBOOL visualsCached = FALSE;

	// Komplette alte Welt wegschmeissen (auch den Player)
	oCPlayerInfo* player = dynamic_cast<oCPlayerInfo*>(zCPlayerInfo::GetActivePlayer());
	if (player) player->SetPlayerVob(NULL);	
	// ***************************************************
	// Alte Welt disposen....
	// ***************************************************
	if (GetGameWorld()->worldFilename!=_levelpath) {
		// Alles rauswerfen....
		GetGameWorld()->DisposeWorld();
	} else {
		// Gleicher Level. Statisches Mesh bleibt, nur Vobs raus
		visualsCached = TRUE;
		CacheVisualsIn();
		GetGameWorld()->DisposeVobs();
	}	

	// Hier duerfen keine Objekte mehr in den Listen eingetragen sein....
	CheckObjectConsistency();	

	if (progressBar) progressBar->SetPercent(8);
	
	// Spieler weg.
	oCNpc::player = NULL;
	
	// Hier schon Zeit laden, weil sonst NSC - Routine - Init falsch initialisiert wird
	// (falsche Weltzeit....)
	zCArchiver* Archiver = NULL;
	int day,hour,min;
	GetWorldTimer()->GetTime(hour,min);

	if (loadGlobals) {
		Archiver = zarcFactory.CreateArchiverRead(zoptions->GetDirString(DIR_SAVEGAMES)+targetDir+SAVEGAME_GLOBAL_FILE);
		Archiver->ReadInt("day",day);
		Archiver->ReadInt("hour",hour);
		Archiver->ReadInt("min",min);
		GetWorldTimer()->SetDay	(day);
		GetWorldTimer()->SetTime(hour,min);		
	}
	
	// und neue Welt laden 
	// Hier wird auch der Spieler initialisiert (befindet sich im SaveGame)
	// Passiert in oCNpc::Unarchive
	if (progressBar) progressBar->SetRange(10,92);
	LoadWorld(slotnr,_levelpath);
	if (progressBar) progressBar->ResetRange();

	// gecachte Visuals raushauen
	if (visualsCached) CacheVisualsOut();

	// Spieler initialisieren
	if (progressBar) progressBar->SetRange(92,98);
	if (!oCNpc::player) {
		zERR_FATAL("U: GAME: No player found. Did you try to load an incompatible savgame ?");
	}

	EnterWorld(oCNpc::player,FALSE);
	if (progressBar) progressBar->ResetRange();
	
	if(loadGlobals)
	{
		GetInfoManager()->Unarchive(*Archiver);
		misMan.Unarchive(*Archiver);
		oCLogManager::GetLogManager().Clear();
		oCLogManager::GetLogManager().Unarchive(*Archiver);
		Archiver->ReadObject(GetCutsceneManager());
		parser.LoadGlobalVars(*Archiver);
		guilds->LoadGuildTable(*Archiver);
		Archiver->Close();
		zRELEASE(Archiver);

		// Globalen nextEntryNode neu errechnen
		rtnMan.UpdateGlobalRoutineEntry();
	}

	// Patch 1.08
	// Hier jetzt erst ScriptInit aufrufen, weil sonst evt. globale
	// Parser Vars noch nicht gesetzt waren....
	// Wurde sonst in LoadWorldDyn ausgefuehrt, dort aber jetzt nur noch, wenn gerade
	// kein Savegame felaen wurde.
	CallScriptInit();

	if (gLogStatistics) 
		LogStatisticsRead(zoptions->GetDirString(DIR_SAVEGAMES)+targetDir); // Patch2, added by Bert (LogStatistics)

	// Kamera an.
	SetCameraPosition();
	
	// Resetting NSC Position - may differ 'cos actual Animation was not saved..... !!!
	// Durchlaufe Npc-List
	oCNpc*		npc				= NULL;
	zCVob*		standingOnVob	= NULL;
	oCMobInter* mob				= NULL;
	zBOOL		oldCollDetDyn	= FALSE;
	zBOOL		oldCollDetStat	= FALSE;

	zVEC3 oldPos;
	zCListSort<oCNpc>* node = GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		if (npc && npc->GetHomeWorld()) {
			
			if (npc->IsDead() && npc->GetAnictrl() && npc->GetModel()) {
				// Patch 1.08
				// Already Dead....
				if ((npc->GetAnictrl()->GetActionMode()==ANI_ACTION_SWIM) || (npc->GetAnictrl()->GetActionMode()==ANI_ACTION_DIVE)) {
					npc->GetModel()	-> StartAni		("S_DROWNED");
					npc->SetPhysicsEnabled			(FALSE);
				} else {
					if (zRand()%1)	npc->GetModel()->StartAni("S_DEAD");
					else			npc->GetModel()->StartAni("S_DEADB");
					npc->GetModel()	-> AdvanceAnis();

					zCAIPlayer::zTSurfaceAlignMode sa = npc->GetAnictrl()->GetConfigDoSurfaceAlign();
					npc->GetAnictrl()->SetConfigDoSurfaceAlign(zCAIPlayer::zMV_SURFACE_ALIGN_NORMAL);
					npc->GetAnictrl()->Begin(npc);
					npc->GetAnictrl()->End();
					npc->GetAnictrl()->SetConfigDoSurfaceAlign(sa);
				}

			} else {
				oldPos = npc->GetPositionWorld();
				oldPos[VY] += 100;
				npc->GetFloorPositionWithVob(oldPos,standingOnVob);
				
				oldCollDetDyn	= npc->GetCollDetDyn  ();
				oldCollDetStat	= npc->GetCollDetStat ();

				mob = zDYNAMIC_CAST<oCMobInter>(standingOnVob);
				if (mob && mob->GetFreePosition(npc,oldPos)) {	
					// Position setzen
					npc->SearchNpcPosition	(oldPos);				// Setzt H�he und checkt auf Platz.
				}
				npc->SetPositionWorld	(oldPos);
				npc->SetCollDetDyn		(oldCollDetDyn);
				npc->SetCollDetStat		(oldCollDetStat);
			}
		}
	}	

	// Object - Tagesablaufe anstossen
	SetObjectRoutineTimeChange(0,0,hour,min);

	if (progressBar) progressBar->SetPercent(100);
	CloseLoadscreen();
}

void oCGame :: ChangeLevel(const zSTRING& levelpath, const zSTRING& startpoint)
{
	parser.ClearAllInstanceRefs();
	
	if (zresMan) {
		zresMan->PurgeCaches();
		zresMan->SetCacheInImmediately  (99999999.0F);                          // oo sec       NEU v108!
	}

	OpenLoadscreen	(FALSE, levelpath);

	// [BENDLIN] Addon - SFX statt Musik bei Levelchange
	zBOOL musicEnabled = zoptions->ReadBool(zOPT_SEC_SOUND, "musicEnabled", TRUE);
	zCZoneMusic::SetAutochange(FALSE);
	zCMusicSystem::DisableMusicSystem(TRUE);		
	if (zsound)
	{
		zsound->StopAllSounds();

		zFILE_FILE filePath(levelpath);
		zSTRING scriptIdentifier = "LOADING_SFX_" + filePath.GetFilename();
		scriptIdentifier.Upper();
		Game_PlaySound(scriptIdentifier);
	}

	if (progressBar) progressBar->SetPercent(0);

	// Spieler aus Welt und Listen nehmen, aber merken (brauchen wir ja noch !)
	// oCNpc::player ist danach NULL 
	// Beachte : auf OldPlayer wurde ein AddRef ausgef�hrt
	oCNpc* oldPlayer = RemovePlayerFromWorld();

	if (progressBar) progressBar->SetPercent(2);
	
	// Player darf nicht per Archive geschrieben werden !
	oCNpc::dontArchiveThisNpc = oldPlayer;

	// Torches removen
	DeleteTorches();

	// Patch 1.08 : In Levelchange muss der PostProcessSavegame 
	// nicht komplett ausgefuehrt werden
	inLevelChange = TRUE;
	
	// aktuelle dynamische Welt speichern (ohne den Spieler)
	if (progressBar) progressBar->SetRange(5,35);
	WriteSavegame	(SAVEGAME_SLOT_CURRENT, FALSE);
	if (progressBar) progressBar->ResetRange();	
	
	// Patch 1.08 : In Levelchange muss der PostProcessSavegame 
	// nicht komplett ausgefuehrt werden
	inLevelChange = FALSE;

	// ok, ab jetzt wieder erlaubt.
	oCNpc::dontArchiveThisNpc = NULL;

	// Schaue nach, ob ein Savegame existiert und liefere den abgeaenderten Filenamen zurueck
	// Falls nicht, muss "normales" ZEN benutzt werden
	int slotID = SAVEGAME_SLOT_CURRENT;
	zSTRING _levelpath = levelpath;
	if (CheckIfSavegameExists(_levelpath)) 
	{
		zERR_MESSAGE(9,0,"B: (oCGame::ChangeLevel) Savegame exists");
		slotID = SAVEGAME_SLOT_CURRENT;
	}
	else 
	{
		zERR_MESSAGE(9,0,"B: (oCGame::ChangeLevel) Savegame does not exist");
		slotID = SAVEGAME_SLOT_NEW;
	}

	if (progressBar) progressBar->SetPercent(37);

	// SpawnListe leeren 
	spawnman->ClearList		();
	// Komplette alte Welt wegschmeissen (bis auf Player -> siehe oben)
	GetGameWorld()->DisposeWorld();	
	// Clear Los Soundos
//	zsound->StopAllSounds();
	// ReInit Cam...
	// [Ulf] - 27.01.01 - 	Hier _muss_ die Kamera ihre Referenzen auf andere Objekte freigeben.
	//                      Das geht laut Carsten nur indem man sie loescht. 
	CamInit();    // [Moos] Nix da! Das macht den (im Moment nicht vorhandenen) BSP-Tree kaputt. Wird sp�ter bei EnterWorld() nachgeholt.

	// Clear DebugList
	oCVob::ClearDebugList();
	// Clear ProtalManager
	if (portalman) portalman->CleanUp();
	// Clear ObjectRoutineList
	ClearObjectRoutineList();

	// Es duerfen keine NSCs mehr in den Listen vorhanden sein !
	// Items sehr wohl -> die im PlayerInventory
	// FIXME:Besser InvItems auch aus Welt bei RemovePlayerFromWorld entfernen !
	CheckObjectConsistency(FALSE);

	if (progressBar) progressBar->SetPercent(40);

	// Jetzt die Welt laden -> keinen neuen Spieler erzeugen ! Den alten benutzen
	// a) statische Welt laden
	// b) dynamische Welt laden
	// c) Spieler initialisieren, sofern sich dieser im dyn. Anteil befand (oCNpc::player!=NULL)

	if (progressBar) progressBar->SetRange(40,92);
	LoadWorld	(slotID,_levelpath);
	if (progressBar) progressBar->ResetRange();

	// Player Init
	// Gabs Spieler im dyn. Anteil & oldPlayer !!=!=!=
	if (progressBar) progressBar->SetRange(95,98);
	if (oldPlayer && oCNpc::player) zERR_FAULT	("U: CHL: Two Players found...");
	EnterWorld	(oldPlayer,TRUE,startpoint);
	if (progressBar) progressBar->ResetRange();

	// Patch 1.08
	// Hier jetzt erst ScriptInit aufrufen, weil sonst evt. globale
	// Parser Vars noch nicht gesetzt waren....
	// Wurde sonst in LoadWorldDyn ausgefuehrt, dort aber jetzt nur noch, wenn gerade
	// kein Savegame felaen wurde.
	CallScriptInit();

	// oldPlayer Releasen / AddRef durch RemovePlayerFromWorld (siehe oben)
	zRELEASE	(oldPlayer);
	// bei einem Levelwechsel werden die NSCs refreshed.
	RefreshNpcs	();
	loadNextLevel = FALSE;
	
	// *****************************************
	// Zustaende anschmeissen / NSCs spawnen...
	// *****************************************
	// NSC - Tagesabl�ufe
	rtnMan.SetDailyRoutinePos( slotID!=SAVEGAME_SLOT_NEW );		// Std: FALSE
	// Object - Tagesablaufe 
	int day,hour,min;
	GetTime(day,hour,min);
	SetObjectRoutineTimeChange(0,0,hour,min);
	// Respawning aktivieren
	if (spawnman) spawnman->SpawnImmediately(TRUE);
	// Attituden Initialisieren, falls Level zum ersten Mal betreten wird...
	if (slotID == SAVEGAME_SLOT_NEW) {
		InitNpcAttitudes();
	}

	//
	//	PARSER-INFO-INSTANZEN RESTAURIEREN
	//
	   ::ogame->GetInfoManager()->RestoreParserInstances();

	if (progressBar) progressBar->SetPercent(100);
	
	// [BENDLIN] Addon - SFX statt Musik bei Levelchange
	zCZoneMusic::SetAutochange(musicEnabled);		
	zCMusicSystem::DisableMusicSystem(!musicEnabled);

	CloseLoadscreen();
    
	if (zresMan)    zresMan->SetCacheInImmediately  (1500.0F);              // 1.5 sec      NEU v108!
}

void oCGame :: TriggerChangeLevel	(const zSTRING& levelpath, const zSTRING& start)
{
	loadNextLevel		= TRUE;
	loadNextLevelName	= levelpath;
	loadNextLevelStart	= start;
	
	// Player has to Remove Weapon in Magic-Mode !!!
	if (oCNpc::player && oCNpc::player->GetWeaponMode()==NPC_WEAPON_MAG) {
		oCNpc::player->EV_ForceRemoveWeapon(NULL);
	};
}

zBOOL oCGame::CheckIfSavegameExists(const zSTRING& levelpath)
{	
	zSTRING savegame;
	// Neues Level schon einmal betreten ?
	zoptions->ChangeDir(DIR_SAVEGAMES);	
	zFILE_FILE path(levelpath);
	savegame = savegameManager->GetSlotDirName(SAVEGAME_SLOT_CURRENT) + path.GetFilename()+"."+SAVEGAME_EXT;
	zFILE* f = zfactory->CreateZFile(savegame);
	
	zBOOL found = f->Exists();
	delete f;
	return found;	
}

// ****************************************************************************************
// Main - RenderLoop
// ****************************************************************************************

void oCGame :: RenderWaynet()
{
	if ((game_showwaynet) && (GetWorld()->GetWayNet())) GetWorld()->GetWayNet()->Draw(GetCamera());
}


void oCGame :: ShowDebugInfos()
{
	// Framerate
	if (game_frameinfo) 
	{
		int y = 0, dy = GetViewport()->FontY();
		zSTRING s;
		s = int(vidGetFPSRate());
		// if (zoptions->Parm("ZFPS")) s=zoptions->ParmValueInt("ZFPS"); 
		GetViewport()->Print(0,y,s+" fps");	y += dy;	

		//
		zTRnd_Stats stat;
		zrenderer->GetStatistics(stat);
		GetViewport()->Print (0,y, zSTRING(int(stat.numTrisRendered))+" tris"); y+=dy;

		//
		//GetViewport()->Print (0, y, "numTex: "+zSTRING(stat.numTexturesUsed));
	}

	if (game_showranges) 
	{
		int y = 0, dy = GetViewport()->FontY();
		zSTRING s;
		GetViewport()->Print (0	 , 1200 + (2*dy), "farclipz: "			+zSTRING(zCCamera::activeCam->GetFarClipZ()));
		GetViewport()->Print (0	 , 1200 + (3*dy), "userFogFar: "		+zSTRING(zCCamera::activeCam->GetVob()->GetHomeWorld()->GetActiveSkyControler()->GetFarZ()));
		GetViewport()->Print (0	 , 1200 + (4*dy), "userFogFarScale: "   +zSTRING(zCCamera::activeCam->GetVob()->GetHomeWorld()->GetActiveSkyControler()->GetFarZScalability()));

		//
		zTRnd_Stats stat;
		zrenderer->GetStatistics(stat);
		GetViewport()->Print (0,y, zSTRING(int(stat.numTrisRendered))+" tris"); y+=dy;

		//
		//GetViewport()->Print (0, y, "numTex: "+zSTRING(stat.numTexturesUsed));
	}


	if (game_showtime) {
		// Show Time
		zSTRING s = GetWorldTimer() -> GetTimeString();
		int dx    = screen -> FontSize(s);
		screen -> Print(8191-dx,0,s);
	}
		
	if (game_showaniinfo) {
		// AnimationsListe
		oCNpc* n = GetSelfPlayerVob();
		n -> GetModel() -> PrintStatus(0,6000);
		n -> GetModel() -> ShowAniList(6200);
	}

	if ((game_species_con) && (game_species_con->IsVisible())) game_species_con->Update();

//	screen->Print(0,1000,"WayBoxes :"+zSTRING(rtnMan.GetNumOfWayBoxes()));
	if (showRoutineNpc) rtnMan.ShowRoutine(0,1500,showRoutineNpc);
};

/*--------------------------------------------------------------------------

    oCGame::Render()

 

    20-Oct-00       [Roman Keskenti]

                      Added call to new screen's render method


--------------------------------------------------------------------------*/ 
void oCGame :: Render ()
{
	const float PRECACHING_TIME = 2.5f * 1000;				

	if (!game_testmode)
	if (m_bWorldEntered)
	{
		GetWorld()->AdvanceClock(timeStep);
	    zCTimer::FrameUpdate(); // [Moos] to enable smooth timer  [Moos] wieder weg, wegen diversen Probs

		GetCamera()->Activate();							// camMatrix wird hier gesetzt 
		GetWorld ()->MoveVobs();	

		//zCEventManager			::DoFrameActivity	();
		if (zresMan) zresMan->DoFrameActivity		();


		// SpawnManager
		spawnman -> CheckInsertNpcs();

		m_fEnterWorldTimer	+= ztimer.GetFrameTimeF();
		// nix f�r 2 sekunden rendern (precaching & auf boden pl�ppen der nsc's abwarten
		if ( m_fEnterWorldTimer >= PRECACHING_TIME )
		{
			m_bWorldEntered		= FALSE;
			m_fEnterWorldTimer	= 0;
		}

		return;
	}

	zCSkyControler* sky;

	zrenderer->BeginFrame();

	if (gLogStatistics) LogStatistics(oCNpc::player); // Patch2, added by Bert (LogStatistics)
//	xxx
		
	// Inventory Items
	oCItemContainer	:: Container_PrepareDraw();

	// Tageszeit
	if (!game_holdTime) wldTimer -> Timer();
	sky  = GetWorld() -> GetActiveSkyControler();
	sky -> SetTime (wldTimer -> GetSkyTime());

	// Rendering wird durchgef�hrt
	oCVisualFX::SetupAIForAllFXInWorld();			// ai der spezialeffekte an oder ausschalten (von der dist. zur camera abh�ngig, nur unbewegliche oCVisualFX Objekte)
	GetWorld() -> Render (*GetCamera());	

//	int warnLocal = TRUE;
//	zLocal_PerFrame();

    zCTimer::FrameUpdate(); // [Moos] to enable smooth timer  [Moos] wieder weg, wegen diversen Probs

	// SpawnManager
	spawnman -> CheckInsertNpcs();
	
	// TMP : [Ulf] Debugging and console tests for ai
	oCNpc::ProcessAITimer();

	//----------------------------------------------

	// *** FIXME : geht das nicht besser ? ***
	if (loadNextLevel) 
	{
		zERR_MESSAGE(5,0,"B: GAM: Start changing level");
		ChangeLevel(loadNextLevelName, loadNextLevelStart);
		zERR_MESSAGE(5,0,"B: GAM: Level changed suucessfully");
	}

	if (game_drawall) {

		RenderWaynet();
		ShowDebugInfos();
		
		// Player-Status-Anzeigen
		UpdatePlayerStatus();
		screen -> DrawItems();		

		// Inventory Rotation
		oCItemContainer :: Container_Draw();

		// Wayboxes

		/*
		zCList<oCNpc> npcList;
		zTBBox3D bbox = oCNpc::player->GetBBox3DWorld();
		if (rtnMan.CollidesWithWayBox(bbox,npcList)) {
			screen->Print(0,1000,"Collision : Yes");
		} else {
			screen->Print(0,1000,"Collision : No");
		}
//		screen->Print(0,1900,"Npcs in List :" +zSTRING(oCNpc::NpcList.Count()));
//		screen->Print(0,1600,"Npcs in World :"+zSTRING(oCNpc::CountNpcsInWorld()));
//		screen->Print(0,1900,"Num of Waybox :"+zSTRING(rtnMan.GetNumOfWayBoxes()));		
		*/

		if (drawWayBoxes)	rtnMan.DrawWayBoxes();
		if (showFreePoints) ShowFreePoints();
//		if (GetPortalRoomManager()) GetPortalRoomManager()->ShowDebugInfo();

		//
		//	CODECHANGE [ROMAN]
		//
		static oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();
		if ( mgrInfos.WaitingForEnd() ) mgrInfos.Update();
		zCViewDraw::GetScreen().Render	();			
		//
		//	CODECHANGE [ROMAN] END
		//

	}

	oCVob :: ShowVobDebugInfo(GetCamera());

	zrenderer->Vid_Unlock();			// Video freigeben

	// FIXME : Tmp ? oder nur im Testmode ?
	oCarsten_PerFrame();
	
	CheckObjectRoutines	();

	GetWorld()->AdvanceClock(timeStep);

	zrenderer->EndFrame();
	
	// FIXME : Tmp - SingleStepMode
	if (singleStep) timeStep = 0.0f;
}

// **************************************************************************************
// Menu 
// **************************************************************************************

void oCGame :: Pause(zBOOL sessionHalted)
{
	if (!singleStep) 
	{
		zERR_MESSAGE(5,0,"B: GAM: Game paused");

		if (!sessionHalted)
		{
			zoptions->ChangeDir(DIR_TEX_DESKTOP);	
			pause_screen = zNEW(zCView(100,100,2000,500));
			screen		->InsertItem		(pause_screen);
			pause_screen->Print(10,10,"PAUSED");	

			zrenderer->BeginFrame();
			screen->DrawItems();
			zrenderer->EndFrame();
		}

		singleStep = TRUE;
		timeStep = 0.0f;	
	}
};

void oCGame :: Unpause()
{
	if (singleStep)  
	{
		zERR_MESSAGE(5,0,"B: GAM: Game unpaused");

		if (pause_screen) 
		{
			delete pause_screen;
			pause_screen=0;
		}
		screen->Render();

		singleStep = FALSE;
		timeStep = -1.0f;
	}
};

// **************************************************************************************
// Debug 
// **************************************************************************************

void oCGame :: DeleteNpcs(oCNpc* npc1, oCNpc* npc2, zREAL radius)
{
	// Durchlaufe Npc-List
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		if ((npc!=npc1) && npc2 && (npc!=npc2)) {
			zREAL dist = (npc2->GetPositionWorld() - npc->GetPositionWorld()).LengthApprox();
			if (dist > radius) {
				npc -> state.hasRoutine = FALSE;
				GetGameWorld()->RemoveVob (npc);
			}		
		}
	}	
}

// **************************************************************************************
// Game Vars
// **************************************************************************************

oCParticleControl *pfxc = NULL;

void Game_Particle_Changed(const zSTRING &s)
{
	if (pfxc) pfxc -> UpdateInternals();
}

void Game_OpenParticleConsole(zSTRING &name)
{
	if (pfxc) {
		pfxc -> SetPFXName (name);
		pfxc -> BeginEditActive(Game_Particle_Changed);
	}
}

void Game_CloseParticleConsole()
{
	if (pfxc) {
		pfxc -> EndEditActive();
		if (pfxc) delete(pfxc);
	}
}

void Game_DeleteAllPfx( zCTree <zCVob> *node )
{
	zCTree <zCVob> *nextnode1;
	zCTree <zCVob> *nextnode2;
	if (node == NULL) return;

	zCVob *vob = node->GetData();
	if (vob && dynamic_cast<zCParticleFX*>(vob->GetVisual())) {
		nextnode1 = node -> GetFirstChild();
		nextnode2 = node -> GetNextChild();
		zRELEASE(vob);
	}

	Game_DeleteAllPfx(nextnode1);
	Game_DeleteAllPfx(nextnode2);
}

// **************************************************************************************
// Game Vars
// **************************************************************************************

/*BOOL game_drawall		= TRUE;
BOOL game_frameinfo		= FALSE;
BOOL game_showaniinfo	= FALSE;
BOOL game_showwaynet	= FALSE;
BOOL game_showranges	= FALSE;*/
BOOL game_showerror		= TRUE;			// Spy Messages


#ifdef COMPILING_SPACER
	BOOL game_testmode		= TRUE;		
#else
	BOOL game_testmode		= FALSE;		
#endif

zVEC3 game_pos;

///
// Lade neue Weltdaten 
// je nach Situation komplett oder nur dynamisch
///
void oCGame::LoadWorld(int slotID, const zSTRING& levelpath)
{	
	zERR_MESSAGE(9,0,"B: (oCGame::LoadWorld)");

	if (levelpath.IsEmpty()) 
	{
#ifndef COMPILING_SPACER
		zERR_MESSAGE(9,0,"B: (oCGame::LoadWorld) fileName is empty");
#else
		if (g_bInsertNPCs)
		{
			CallScriptStartup();
			CallScriptInit();
		}
#endif
		return;
	}

	if (progressBar) progressBar->SetPercent(12);
	
	zSTRING _levelpath = levelpath;		
		
	if (slotID==SAVEGAME_SLOT_NEW)
	// lade die komplette Welt				
	// von  15%  bis  97%!!
	{		
		GetSpawnManager()->ClearList();
		GetGameWorld()->DisposeWorld();				

		if (progressBar) progressBar->SetRange(15,97);		
		LoadWorldStartup(_levelpath);		
		if (progressBar) progressBar->ResetRange();
	
		if (!GetWorld()->IsCompiled()) CompileWorld();
	} 
	else 
	// Lade statischen und dynamischen Anteil getrennt
	// von  15%  bis  97%!!
	{		
		int nextPercent = 15;
				
		if (GetGameWorld()->worldFilename!=_levelpath) 
		// Neue statische Welt laden, sofern erforderlich.				
		// von 15%  bis  40%!!
		{
			nextPercent = 40;
			if (progressBar) progressBar->SetRange(15,nextPercent);			
			LoadWorldStat(_levelpath);
			if (progressBar) progressBar->ResetRange();			
		}		

		if (progressBar) progressBar->SetPercent(nextPercent+2);
		
		// Welt noch compilieren?
		if (!GetWorld()->IsCompiled()) CompileWorld();
	
		// Dynamische Welt laden
		// von 15% bzw. 40%  bis  97%!!
		inLoadSaveGame = TRUE;
		if (progressBar)	progressBar->SetRange	(nextPercent+4,97);
		LoadWorldDyn		(_levelpath);
		if (progressBar)	progressBar->ResetRange	();	
		inLoadSaveGame = FALSE;
	}	
	
	// Waynet Correction durchf�hren
	// Doesnt work correctly in "Unarchive" if Level is not yet compiled
	GetWorld()->GetWayNet()->CorrectHeight		();

	if (dynamic_cast<zCSkyControler_Indoor*>(GetWorld()->GetActiveSkyControler()))
	{
		zsound->SetGlobalReverbPreset(8,0.4f);		// cave
	}
	else
	{
		zsound->SetGlobalReverbPreset(0,0.0f);		// none
	}

	/* GetWorld()->GetWayNet()->CalcProperties		(GetWorld());*/

	if (progressBar)		progressBar->SetPercent(100);
};

/*

	// betrete die "neue" Welt
	if (progressBar) progressBar->SetRange(90,100);
	EnterWorld(rememberPlayer, startpoint);
	if (progressBar) progressBar->ResetRange();

	if (progressBar) progressBar->SetPercent(100);
	
	// Reset Time -> schmeisst Tagesablaufvorausberechnung an.
	int hour,min,day;
	GetWorldTimer()->GetTime(hour,min);
	day = GetWorldTimer()->GetDay ();
	SetTime(day,hour,min);	

	zRELEASE(rememberPlayer);
	CloseLoadscreen();
};
*/



///
// Das Savegame wird vorbereitet (Kopieren und Header auslesen)
// Dabei werden die beiden Parameter (call by Ref) entsprechend geaendert
///
void oCGame::InitWorldSavegame(int& slotID, zSTRING& levelname)
{	
	OpenLoadscreen(TRUE, "");

	zERR_MESSAGE(5,0,"B: GAM: InitWorldSavegame");
	
	// kopiere die Savegamedaten in das current-verzeichnis
	/*
	zSTRING dirSlot			= savegameManager->GetSlotDirName(slotID);
	zSTRING dirSlotCurrent	= savegameManager->GetSlotDirName(SAVEGAME_SLOT_CURRENT);
	zoptions->ChangeDir(DIR_SAVEGAMES);
	if ((slotID>=SAVEGAME_SLOT_MIN) && (slotID<=SAVEGAME_SLOT_MAX)) 
	{
		zerr.Message("B: (oCGame::InitWorldSavegame) Copying Savegame to current-dir ...");
		savegameManager->CopyToCurrent(slotID);
		slotID = SAVEGAME_SLOT_CURRENT;	// die slotID wird jetzt auf die neue Position der Daten umgelenkt:
	}
	*/

	savegameManager->CopyToCurrent(slotID);
	slotID = SAVEGAME_SLOT_CURRENT;	// die 	
	
};



///
// Eine neue Welt wird betreten (vor dem ersten Rendern)
///
void oCGame :: EnterWorld(oCNpc* playerVob, zBOOL changePlayerPos, const zSTRING& startpoint)
{
	zERR_MESSAGE	(9,0,"B: (oCGame::EnterWorld)");

	if (progressBar) progressBar->SetPercent(0);
	
	//
	// Spieler initialisieren 	
	//
	if (progressBar) progressBar->SetRange(0,55);	
	if (changePlayerPos)		
	{		
		SetupPlayers(playerVob, startpoint);				
	}
	else	
	{		
		oCPlayerInfo* player = dynamic_cast<oCPlayerInfo*>(zCPlayerInfo::GetActivePlayer());
		if (!player)
		{			
			player = (oCPlayerInfo*)zfactory->CreatePlayerInfo();	
			gameInfo	->AddPlayer		(player);					
			player		->SetPlayerVob	(playerVob);		
			player		->SetActive();
		}			
	}
	if (progressBar) progressBar->ResetRange();
	
	//
	// Kamera initialisieren
	//
	CamInit();
	
	//
	// Spieler endgueltig setzen
	//
	GetSelfPlayerVob()->SetAsPlayer	();		
	if (playerVob && playerVob->GetAnictrl()) {
		playerVob->GetAnictrl()->SetFightAnis(playerVob->GetWeaponMode());
	};

	if (progressBar) progressBar->SetPercent(60);

	EnvironmentInit();

	if (progressBar) progressBar->SetPercent(75);		

	NpcInit();

	if (progressBar) progressBar->SetPercent(96);

	// [SPECKELS] F4-Simulation ist nicht mehr noetig und fuehrt zu Problemen, falls F4 etwas zugewiesen wurde
	// HandleEvent(KEY_F4);

/*	// -------- PATCH2 ----- von Bert ---- InExtremoVolume -----------
	zCVob* vob = GetWorld()->SearchVobByName("INEXTREMO_MUSIK");
	zCVobSound* snd = dynamic_cast<zCVobSound*>(vob);
	if (snd)
	{		
		zREAL vol	= snd->GetSoundVolume();
		zREAL range = snd->GetSoundRadius();

		if (vol<=31)
		{
			zREAL scaleVol=zoptions->ReadReal(zOPT_SEC_SOUND,"inExtremoVolumeScale",1.0f);
			vol		= vol*scaleVol;
			if (vol>100)	vol=100;
			if (vol<0)		vol=0;		
			snd->SetSoundVolume( vol );
		}
		if (range<=1400)
		{			
			zREAL scaleRange=zoptions->ReadReal(zOPT_SEC_SOUND,"inExtremoRangeScale",2.0f);
			range	= range * scaleRange;
			if (range>3000)	range=3000;
			if (range<0)	range=0;
			snd->SetSoundRadius( range );
		}
	};
	// ---------------------------------------------------------------- */

	if (progressBar) progressBar->SetPercent(100);

	// Temp: Die interne Debug-Vobliste muss natuerlich beim Disposen der Welt mit aufgraeumt werden!
	//oCVob::ResetDebugInfos();

	CloseLoadscreen();

	m_bWorldEntered		= TRUE;
	m_fEnterWorldTimer	= 0;

	
};

void oCGame::CompileWorld()
{
	if (!GetWorld()->IsCompiled()) {

		zTBspTreeMode bspmode;
		if (zoptions->Parm("OUTDOOR"))	bspmode = zBSP_MODE_OUTDOOR;
		else							bspmode = zBSP_MODE_INDOOR;
		// Compile Value
		zSTRING comval;
		comval = zoptions->ReadString(zOPT_SEC_INTERNAL,"gameCompile","1.0");

		GetWorld()->CompileWorld				(bspmode,comval.ToFloat(),FALSE);
		GetWorld()->GenerateStaticWorldLighting	(zCWorld::zWLD_LIGHT_VERTLIGHT_ONLY); 
	}
};


///
// Lade die komplette Welt (Startup)
///
void oCGame::LoadWorldStartup(const zSTRING& levelpath)
{
	//
	// Laden der Welt (0% bis 75%)
	//
	zERR_MESSAGE(3,zERR_BEGIN,"U: GAM: Loading startup-data: \""+levelpath+"\"...");	
	if (progressBar) progressBar->SetRange(0,75);
	GetWorld()->LoadWorld(levelpath,zCWorld::zWLD_LOAD_GAME_STARTUP);	
	if (progressBar) progressBar->ResetRange();
	zERR_MESSAGE(3,zERR_END,"U: GAM: Loading startup-data \""+levelpath+"\" finished.");	

	if (progressBar) progressBar->SetPercent(76);
	
	//
	// Removing Helper Vobs (76% bis 79%)
	//
	zERR_MESSAGE(3,0,"U: GAM: Cleaning world...");	
	RemoveHelperVobs( GetWorld()->globalVobTree.GetFirstChild() );
	zERR_MESSAGE(3,0,"U: GAM: .. finished");	

	if (progressBar) progressBar->SetPercent(79);

	//
	// Call Script Startup Function (80% bis 100%)
	//
	if (progressBar) progressBar->SetRange(80,100);
	CallScriptStartup();
	CallScriptInit();
	if (progressBar) progressBar->ResetRange();
};

///
// Lade den statischen Anteil einer Welt
///
void oCGame::LoadWorldStat(zSTRING levelpath)
{
	zERR_MESSAGE(3,zERR_BEGIN,"U: GAM: Loading static data: "+levelpath);	

	// Statischer Lavelanteil wird nur aus Zens geladen.
	if (progressBar) progressBar->SetRange(0,100);
	int pos	=	levelpath.Search	("."+SAVEGAME_EXT);
	if (pos>=0) levelpath.Overwrite	(pos,".ZEN");
	GetWorld()->LoadWorld(levelpath,zCWorld::zWLD_LOAD_GAME_SAVED_STAT);		
	if (progressBar) progressBar->ResetRange();

	zERR_MESSAGE(3,zERR_END,"");	
};

///
// Lade den dynamischen Anteil einer Welt aus einem Savegame-ZEN
///
void oCGame::LoadWorldDyn(const zSTRING& levelpath)
{	
	// ermittle den Namen des SAV-Files
	zFILE_FILE file(levelpath);
	zSTRING filename = zoptions->GetDirString(DIR_SAVEGAMES)+savegameManager->GetSlotDirName(SAVEGAME_SLOT_CURRENT) + file.GetFilename()+"."+SAVEGAME_EXT;	
	
	if (progressBar) progressBar->SetRange(0,95);
	zERR_MESSAGE(3,zERR_BEGIN,"U: GAM: Loading dynamic data: \""+filename+"\" ...");	
	GetWorld()->LoadWorld(filename,zCWorld::zWLD_LOAD_GAME_SAVED_DYN);
	zERR_MESSAGE(3,zERR_END,"U: GAM: Loading dynamic data \""+filename+"\" finished.");	
	if (progressBar) progressBar->ResetRange();

	// Removing Helper Vobs
	if (progressBar) progressBar->SetRange(95,100);
	zERR_MESSAGE(3,0,"U: GAM: Cleaning world...");	
	RemoveHelperVobs( GetWorld()->globalVobTree.GetFirstChild() );
	zERR_MESSAGE(3,0,"U: GAM: .. finished");
	if (progressBar) progressBar->ResetRange();

	// Activate FireMobsis....
	// und allen Feuermobsis die Vobtrees wieder anhaengen....
	// Kann weg, sobald es so ein "PostLoad" bei Objekten gibt.
	zCListSort<zCVob>* mobNode = GetGameWorld()->GetVobList()->GetNextInList();
	oCMobFire* mob = NULL;
	while (mobNode) {
		mob		= zDYNAMIC_CAST<oCMobFire>(mobNode->GetData());
		mobNode = mobNode->GetNextInList();
		if (mob) mob->PostSave();
	}
	
	// Calling Script-Init
	// Patch 1.08
	if (!IsInLoadSaveGame()) CallScriptInit();
};

///
// Check, ob die Welt (oder ueberhaupt eine) schon geladen ist.
///
zBOOL oCGame::IsInWorld(const zSTRING& levelpath)
{	
	zBOOL result = FALSE;
	if (levelpath.IsEmpty())
	{
		// ueberhaupt schon eine Welt geladen?
		result = !GetGameWorld()->GetWorldName().IsEmpty();
	}
	else
	{
		zFILE_FILE path(levelpath);
		zSTRING levelname = path.GetFilename();

		// ist die angegebene Welt geladen?
		result = GetGameWorld()->GetWorldName() == levelname;
	}
	return result;
};

void oCGame :: RenderBlit()
{
	zrenderer->Vid_Blit();				// Grade
}

// ********************************************************************************
// Game - Object - Routines
// ********************************************************************************

int oCGame :: Sort_Routine (TObjectRoutine *entry1, TObjectRoutine *entry2)
{
	if (entry1->hour1 < entry2->hour1)	return -1;		else
	if (entry1->hour1 > entry2->hour1)	return  1;		else
	// Gleiche Stunde
	if (entry1->min1  < entry2->min1)	return -1;		else
	if (entry1->min1  > entry2->min1)	return  1;	
	return 1;
}

void oCGame :: InsertObjectRoutine(int type, const zSTRING& name, int hour1, int min1, int state)
{
	TObjectRoutine* rtn = zNEW(TObjectRoutine);
	// Init members
	rtn->objName	= name;
	rtn->hour1		= hour1;
	rtn->min1		= min1;
	rtn->stateNum	= state;
	rtn->type		= type;
	objRoutineList.InsertSort(rtn);
};

void oCGame :: ResetObjectRoutineList()
// Set all "called" to false 
{
	currentObjectRoutine	= NULL;
	oldRoutineDay			= -1;
};

void oCGame :: ClearObjectRoutineList()
{
	objRoutineList.DeleteListDatas();
	currentObjectRoutine = NULL;
};

void oCGame :: CheckObjectRoutines()
{
	if (!currentObjectRoutine && (oldRoutineDay!=GetWorldTimer()->GetDay())) {
		// Liste nur restarten, wenn sich auch der Tag geaendert hat
		currentObjectRoutine = objRoutineList.GetNextInList();
		oldRoutineDay = GetWorldTimer()->GetDay();
	}
	TObjectRoutine* rtn = NULL;

	while (currentObjectRoutine) {
		rtn		= currentObjectRoutine->GetData();		
		if (GetWorldTimer()->IsLater(rtn->hour1,rtn->min1)) {
			// Mobsis aktivieren
			if (rtn->type==0) oCMobInter::SetAllMobsToState(GetGameWorld(),rtn->objName,rtn->stateNum); else 
			// Single Objekt aktivieren
			if (rtn->type==1) {
				zCVob* vob = GetGameWorld()->SearchVobByName(rtn->objName);
				if (vob) {
					if (rtn->stateNum==0) vob->GetEM()->OnUntrigger	(NULL,NULL);	else
					if (rtn->stateNum==1) vob->GetEM()->OnTrigger	(NULL,NULL);	
				}
			}
			currentObjectRoutine	= currentObjectRoutine->GetNextInList();
		} else {
			return;
		}
	}
};

void oCGame :: SetObjectRoutineTimeChange(int hour1, int min1, int hour2, int min2)
// F�hre ObjectTagesablauf-Trigger von hour1 bis hour2 Zeit aus
{
	zCListSort<TObjectRoutine>* firstRtn	= NULL;
	TObjectRoutine* rtn						= NULL;

	int	day				= 0;
	int	timeRtn			= 0;
	int timeStart		= (hour1*60+min1) % (24*60);
	int timeEnd			= (hour2*60+min2) % (24*60);

	int numTrigger		= 0;

	if (timeEnd<timeStart) timeEnd += 24*60;	// einen Tag draufaddieren
	
	if (!currentObjectRoutine) currentObjectRoutine = objRoutineList.GetNextInList();
	firstRtn = currentObjectRoutine;

	while (currentObjectRoutine) {
		rtn		= currentObjectRoutine->GetData();
		timeRtn = rtn->hour1*60 + rtn->min1 + day*24*60;
		
		if ((timeStart<=timeRtn) && (timeRtn<=timeEnd)) {
			// Innerhalb der TimeRange, ausf�hren
			if (rtn->type==0) {
				numTrigger += oCMobInter::SetAllMobsToState(GetGameWorld(),rtn->objName,rtn->stateNum);
			
			} else if (rtn->type==1) {
				// Single Objekt aktivieren
				zCVob* vob = GetGameWorld()->SearchVobByName(rtn->objName);
				if (vob) {
					if (rtn->stateNum==0) {
						oCMobInter* mob = zDYNAMIC_CAST<oCMobInter>(vob);
						if (mob)	mob->SetTempState(0);
						else		vob->GetEM()->OnUntrigger	(NULL,NULL);							
						
					} else if (rtn->stateNum==1) {
						oCMobInter* mob = zDYNAMIC_CAST<oCMobInter>(vob);
						if (mob)	mob->SetTempState(1);
						else		vob->GetEM()->OnTrigger		(NULL,NULL);	
						numTrigger++;
					};
				}
			}
		
		} else {
			oCMobInter::TriggerAllMobsToTmpState(GetGameWorld());
			zERR_MESSAGE(4,0,"U:MOB: Mobsis triggered :"+zSTRING(numTrigger));
			// Ausserhalb der Range, also verlassen;
			return;	
		}
		
		currentObjectRoutine = currentObjectRoutine->GetNextInList();
		if (!currentObjectRoutine) {
			// Liste wieder von vorne durchlaufen.
			// ResetObjectRoutineList();
			currentObjectRoutine = objRoutineList.GetNextInList();
			day++;
		}
	
		if (currentObjectRoutine == firstRtn) {
			// Wieder am Start angekommen, es reicht....
			// Einen kompletten tag durchlaufen....
			oCMobInter::TriggerAllMobsToTmpState(GetGameWorld());
			zERR_MESSAGE(4,0,"U:MOB: Mobsis triggered :"+zSTRING(numTrigger));
			return;
		}
	}	
	oCMobInter::TriggerAllMobsToTmpState(GetGameWorld());
	zERR_MESSAGE(4,0,"U:MOB: Mobsis triggered :"+zSTRING(numTrigger));
}

void oCGame :: ToggleShowFreePoints()
{
	showFreePoints = !showFreePoints;
}

void oCGame :: ShowFreePoints()
{
	if (showFreePoints && GetCameraVob()) {

		// Einsammeln
		zTBBox3D bbox;
		zCArray<zCVob*> found;
		zREAL distance	= 3000;

		bbox.maxs		 = bbox.mins = GetCameraVob()->GetPositionWorld();	
		bbox.maxs[0]	+= distance; bbox.maxs[1]	+= distance; bbox.maxs[2]	+= distance;
		bbox.mins[0]	-= distance; bbox.mins[1]	-= distance; bbox.mins[2]	-= distance;
		GetWorld()  -> CollectVobsInBBox3D (found, bbox);	
		
		zCVobSpot* spot = NULL;
		zCOLOR color;
		zPOINT3 wsPoint1,csPoint1;
		zPOINT2 ssPoint1;
		// Nach zCVobSpots durchsuchen
		for (int i=0; i<found.GetNumInList(); i++) 
		{	
			if (spot = dynamic_cast<zCVobSpot*>(found[i])) 
			{
				const zREAL FPBOX_DIMENSION = 50;
				zTBBox3D fpBox;
				fpBox.maxs = fpBox.mins = spot->GetPositionWorld();		
				fpBox.maxs[0] += FPBOX_DIMENSION; fpBox.maxs[1] += FPBOX_DIMENSION*2; fpBox.maxs[2] += FPBOX_DIMENSION;
				fpBox.mins[0] -= FPBOX_DIMENSION; fpBox.mins[1] -= FPBOX_DIMENSION*2; fpBox.mins[2] -= FPBOX_DIMENSION;
				
				// BBox
				if (spot->IsAvailable(GetSelfPlayerVob()))	color = GFX_YELLOW;
				else										color = GFX_RED;
				fpBox.Draw(color);

				// NOTE This is how you get camera position of wob and its text
				// Und Name
				wsPoint1 = spot			-> GetPositionWorld		();
				csPoint1 = GetCamera()	-> Transform			(wsPoint1);
				if (csPoint1[VZ]>=0)	GetCamera()	-> Project	(&csPoint1, ssPoint1[VX], ssPoint1[VY]);
				if ((csPoint1[VZ]<1000) && (csPoint1[VZ]>0))	screen		-> Print	(screen->anx(ssPoint1[VX]),screen->any(ssPoint1[VY]),spot->GetVobName());
			};
		}
	}
};

void oCGame :: RefreshNpcs()
// Bei Levelwechsel und um 24 Uhr aufgerufen
{
	// Alle NSC durchsuchen und FullRegenerate durchf�hren
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* npcNode = GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (npcNode) {
		npc		= npcNode->GetData();
		npcNode = npcNode->GetNextInList();
		if (!npc->IsAPlayer()) npc->RefreshNpc();
	}
	DeleteTorches();
}

void oCGame :: DeleteTorches()
{
	// Alle Items durchsuchen und Fackel entfernen....
	oCItem* item = NULL;
	zCListSort<zCVob>* npcNode = GetGameWorld()->GetVobList()->GetNextInList();
	while (npcNode) {
		item	= zDYNAMIC_CAST<oCItem>(npcNode->GetData());
		npcNode = npcNode->GetNextInList();
		if (item && item->GetHomeWorld() && (item->GetInstanceName()=="ITLSTORCHBURNING")) {
			if (/*(item->GetRefCtr()<=5) &&*/ zDYNAMIC_CAST<oCAIVobMove>(item->GetAI())) {
				item->SetAI(NULL);
				item->GetHomeWorld()->RemoveVobSubtree(item);
				item = NULL;
			}
		};
	};
}

// **************************************************************************************
// Game Console Functions
// **************************************************************************************

static void MarkOccluderPolys (zCMesh* mesh) {
	zCMaterial *mat = zNEW(zCMaterial("Occluder_Poly_Mat"));  
	mat->SetColor (255,50,50);

	for (int i=0; i<mesh->numPoly; i++) {
//		zCPolygon *poly = mesh->Poly(i);
//		if (poly->GetOccluder()) poly->SetMaterial (mat);
	};
};

void Game_CreateInstance ( zSTRING &s, zSTRING &msg )
{
	BOOL ok = FALSE;
	zVEC3 vec;
	int base;
	int index = parser.GetIndex(s);
	if (index>=0) {
		zCPar_Symbol *sym = parser.GetSymbolInfo(index);

		if (sym->type==zPAR_TYPE_INSTANCE) {
		
			// Falls Base ein Prototype, von diesem die Base ermitteln
			int typ,ele;
			parser.GetSymbolInfo (index,typ,ele);
			
			base = parser.GetBase		(index);
			sym	 = parser.GetSymbolInfo	(base);
			
			if (sym->type==zPAR_TYPE_PROTOTYPE) {
				base = parser.GetBase(base);
			}
			
			// Check Type
			int nsc		= parser.GetIndex(zSTRING("C_NPC"));
			int item	= parser.GetIndex(zSTRING("C_Item"));
			// unn�tig: int mob		= parser.GetIndex(zSTRING("C_MOB"));
			
			oCNpc		:: player -> GetPositionWorld(vec);
			vec += oCNpc :: player -> GetAtVectorWorld() * 200;
			if (base==nsc) {
				oCNpc *npc		= (oCNpc*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_NSC,index);
//                npc		-> SetPositionWorld(vec);
				npc		-> Enable(vec);
//	            ogame	-> GetGameWorld() -> AddVob(npc);						
				// Und Attitude zum Spieler setzen
				int pAtt = ogame->GetGuilds()->GetAttitude(npc->GetTrueGuild(),oCNpc::player->GetTrueGuild());
				npc -> SetTmpAttitude	(pAtt);
				npc -> SetAttitude		(pAtt);

				npc	-> Release();
				// TA anschmeissen
				if (npc->state.HasRoutine()) {
					//rtnMan.CreateWayBoxes(npc);
					oCRtnEntry *rtnNow, *rtnBefore;
					if (rtnMan.FindRoutine(npc,rtnNow,rtnBefore)) {
						npc->state.SetRoutine	(rtnNow,rtnBefore);
						npc->state.StartRtnState();
					}
				} else {
					zCWaypoint* wp = ogame->GetWorld()->GetWayNet()->GetNearestWaypoint(vec);
					if (wp) npc->wpname = wp->GetName();
				}
				
				npc->GetModel()->StartAni("S_FALLDN");
				ok = TRUE;

			} else if (base==item) {
                oCItem *item = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,index);                          
				item->SetPositionWorld(vec);
				ogame->GetGameWorld()->AddVob(item);
				zRELEASE(item);
				ok = TRUE;
			}
		}
	}
	if (ok)	msg = "'" + s + "' inserted";
	else	msg = "'" + s + "' not found.";	
}

void Game_GotoWP (const zSTRING &s, zSTRING &msg)
{
	if (oCNpc::player->BeamTo(s)) {
		msg = "Player beamed to Waypoint "+s+".";
	} else {
		msg = "Way- or Freepoint not found.";
	}
}
	
void Game_SaveSCPos()
{
	game_pos = oCNpc :: player -> GetPositionWorld();
}

void Game_LoadSCPos()
{
	oCNpc :: player -> SetCollDet(FALSE);
	oCNpc :: player -> SetPositionWorld(game_pos);
	oCNpc :: player -> SetCollDet(TRUE);
}

void Game_ToggleTestMode(BOOL on)
{
#ifdef COMPILING_SPACER
	return;
#endif
	game_testmode = on;
	if (ogame) ogame->EnableTestmode(on);
}

void Game_ToggleHoldTime()
{
	game_holdTime = !game_holdTime;
}


void Game_ParserDebug(zSTRING &s)
{
	parser.ShowCode(parser.GetIndex(s));
}

void Game_ParserDebugOff()
{
	parser.CloseViews();
}

void Game_PlaySound(zSTRING &s)
{
	zCSoundFX* snd = zsound->LoadSoundFXScript(s);
	if (snd!=NULL) zsound->PlaySound(snd);
	zRELEASE(snd);
}

void Game_ToggleScreenMode()
{			
	zTRnd_ScreenMode game_scrm = zrenderer ->Vid_GetScreenMode();
	if (game_scrm==zRND_SCRMODE_WINDOWED)	game_scrm= zRND_SCRMODE_FULLSCREEN;
	else									game_scrm= zRND_SCRMODE_WINDOWED;
	zrenderer->Vid_SetScreenMode(game_scrm);
}

// **************************************************************************************
// Game Console
// **************************************************************************************

BOOL game_con = FALSE;
zCConsole *game_species_con		= NULL;
zCConsole *game_fight_con		= NULL;
zCConsole *edit_con				= NULL;
zCConsole *game_cam_con			= NULL;
zCConsole *game_aiConsole		= NULL;

void Edit_Changed(const zSTRING &var)
{
	if (var=="ATTRIBUTE") 
		oCNpc :: player -> CheckModelOverlays();
}


/*--------------------------------------------------------------------------
    oCGame::ConsoleEvalFunc()

    28-Sep-00       [Michael]
                      VERSION Konsolenkommando wegen Fingerprint
--------------------------------------------------------------------------*/ 

static int megamorzel = (591 * 999);    // Hidden VAR f�r Fingerprint
//////////////////////////////////////////////////////////////////////////
// Gothic2
// [BENDLIN] 1.28,			'303',		JoWooD, Goldmaster
// [BENDLIN] 1.28promo,		'7311',		JoWooD, J�rgen Sch�pker - MARVIN mit 'M�CKE' oder 'M�CKE'
//////////////////////////////////////////////////////////////////////////
// G2Addon
// [BENDLIN] 2.4c (beta),	'216398'	Gothic2-2.4c(beta)_intern.exe Spacer2.exe
// [BENDLIN] 2.4c (beta),	'307'		Gothic2-2.4c(beta)_jwd00.exe
// [BENDLIN] 2.4c (beta),	'1306'		Gothic2-2.4c(beta)_jwd01.exe
// [BENDLIN] 2.4c (beta),	'102743'	Gothic2-2.4c(beta)_jwd02.exe
// [BENDLIN] 2.4c (beta),	'19442'		Gothic2-2.4c(beta)_jwd03.exe
// [BENDLIN] 2.4c (beta),	'13601'		Gothic2-2.4c(beta)_jwd04.exe
// [BENDLIN] 2.4m (dev),	'54330'		Gothic2-2.4m(dev)_intern.exe
// [BENDLIN] 2.4m (gmc),	'8991'		Gothic2-2.4m(gmc)_jowood.exe
// [BENDLIN] 2.4n (dev),	'20594'		Gothic2-2.4n(dev)_intern.exe
// [BENDLIN] 2.4n (gmc),	'33735'		Gothic2-2.4n(gmc)_jowood.exe
// [BENDLIN] 2.5  (dev),	'30661'		Gothic2-2.5_intern.exe  // 399
// [BENDLIN] 2.5  (mod),	'45416'		Gothic2-2.5_master.exe  // 591
zBOOL oCGame :: ConsoleEvalFunc( const zSTRING &s, zSTRING &msg )
{
	zSTRING w1 = s.PickWord(1," ");
	zSTRING w2 = s.PickWord(2," ");
	zSTRING w3 = s.PickWord(3," ");
	w1.Upper();
	w2.Upper();
	w3.Upper();

	if (w1=="INSERT") {
		// Erschaffe Vob
		Game_CreateInstance(w2,msg);
		return TRUE;

	} else if (w1=="GOTO") {
		if (w2=="WAYPOINT") {
			// Gehe zu Wegpunkt
			Game_GotoWP(w3,msg);
			return TRUE;
		// CODECHANGE [STEFAN]
		} else if (w2=="VOB") {
			// Gehe zu Vob
			zCArray<zCVob*> vobList;
			ogame->GetWorld()->SearchVobListByName(w3, vobList);

			if (vobList.IsEmpty()) {
				msg = "No vobs found.";
				return TRUE;
			}

			zPOINT3 pt;
			zSTRING str;
			zINT i;

			str = s.PickWord(4," ");

			if (str.IsEmpty()) {
				i = 1;
			} else {
				i = str.ToInt();
				if ((i < 1) || (i > vobList.GetNum())) {
					msg = "Not a valid vob number.";
					return TRUE;
				}
			}

			pt = vobList[i-1]->GetPositionWorld();
			// [BENDLIN] Addon Patch - GOTO VOB auch bei NPC ohne Position (ausserhalb der Spawnrange)
			if (pt == zPOINT3(0,0,0))
			{
				oCNpc * npc = zDYNAMIC_CAST<oCNpc>(vobList[i-1]);
				if (npc && !npc->IsSelfPlayer())
				{
					if (npc->state.HasRoutine())
						pt = rtnMan.GetRoutinePos(npc);
					else
						pt = npc->state.GetAIStatePosition();
				}
			}

			oCNpc *plr = oCNpc :: player;

			zBOOL cdDyn = plr->GetCollDetDyn();
			zBOOL cdStat = plr->GetCollDetStat();
			plr->SetCollDet(FALSE);
			plr->SetPositionWorld(pt);
			plr->SetCollDetDyn(cdDyn);
			plr->SetCollDetStat(cdStat);

			return TRUE;
		// CODECHANGE [STEFAN] END
		}
	
	// CODECHANGE [STEFAN]
	} else if (w1=="PRINT") {
		if (w2=="VOB") {
			// Drucke Infos �ber Vob
			zCArray<zCVob*> vobList;
			zINT i;
			zSTRING str;
			ogame->GetWorld()->SearchVobListByName(w3, vobList);
			str = "Print vob: Found " + zSTRING(vobList.GetNum()) + " vobs.";
			zERR_MESSAGE(1,zERR_BEGIN,"S: SC: " + str );
			for (i = 0; i < vobList.GetNum(); i++) {
				zCVob *vob = vobList[i];
				oCItem *item = dynamic_cast<oCItem*>(vob);
				oCNpc *npc = dynamic_cast<oCNpc*>(vob);
				str = "S: " + zSTRING(i + 1) + ": " + vob->GetClassName_() + ": " + vob->GetVobName();
				zERR_MESSAGE(1,zERR_BEGIN,str);

				if (npc != NULL) {
					str = "S: Name: " + npc->GetName(FALSE) + "/" + npc->GetName( TRUE );
					zERR_MESSAGE(1,0,str);
				} else if (item != NULL) {
					str = "S: Name: " + item->GetName();
					zERR_MESSAGE(1,0,str);
				}

				zPOINT3 pt;

				pt = npc->GetPositionWorld();
				str = "S: Position: X:" + zSTRING(pt.n[VX], 0) + " Y:" + zSTRING(pt.n[VY], 0) + " Z:" + zSTRING(pt.n[VZ], 0) + " ";
				if (vob->GetHomeWorld()) {
					str += "(enabled)";
				} else {
					str += "(disabled)";
				}
				zERR_MESSAGE(1,0,str);

				zERR_MESSAGE(1,zERR_END,"" );
			}
			zERR_MESSAGE(1,zERR_END,"" );
			return TRUE;
		}
	// CODECHANGE [STEFAN] END
	
	} else if (w1=="DELETE") {
		if (w2=="PARTICLEFX") {
			if (pfxc) {
				pfxc -> DeleteLastPFX();
				msg = "ParticleFX deleted";
			}
			return TRUE;
		}

	} else if (w1=="TOGGLE") {
		// **************************************************
		// TOGGLE
		// **************************************************
		if (w2=="HOLDTIME") {
			Game_ToggleHoldTime();
			return TRUE;
		} else
		if (w2=="DESKTOP") {
			ogame->game_drawall = !ogame -> game_drawall;		
			return TRUE;
		} else if (w2=="DEBUG") {
			// Debug Messages
			zBOOL deb = !ogame->GetShowDebug();
			ogame->SetShowDebug(deb);
			if (deb)	msg = "Debug Infos an.";
			else		msg = "Debug Infos aus.";
			return TRUE;
		} else if (w2=="SPY") {
			// Spy Messages
			if (game_showerror) {
//				zerr.SetOutputLevel(zERR_FATAL);
				msg = "zSpy-Messages off.";
				game_showerror = FALSE;
			} else {
//				zerr.SetOutputLevel(zERR_INFO);
				msg = "zSpy-Messages on.";
				game_showerror = TRUE;
			}
			return TRUE;
		} else if (w2=="TEXT") {
			// Text Window
			if (ogame -> game_text -> IsVisible()>0)	screen -> RemoveItem(ogame -> game_text);
			else										screen -> InsertItem(ogame -> game_text);
			return TRUE;
		} else if (w2=="WAYNET") {
			// Waynet
			ogame->game_showwaynet = !ogame->game_showwaynet;
			return TRUE;
		} else if (w2=="WAYBOXES") {
			// Waynet
			ogame->drawWayBoxes = !ogame->drawWayBoxes;
			return TRUE;
		} else if (w2=="FREEPOINTS") {
			// Waynet
			ogame->ToggleShowFreePoints();
			return TRUE;
		} else if (w2=="FRAME") {
			// FrameInfo
			ogame->game_frameinfo = !ogame->game_frameinfo;
			return TRUE;
		} else if (w2=="RANGES") {
			// FrameInfo
			ogame->game_showranges= !ogame->game_showranges;
			return TRUE;
		} else if (w2=="ANIINFO") {
			// Show AniInfo
			ogame->game_showaniinfo = !ogame->game_showaniinfo;
			return TRUE;
		} else if (w2=="SCREEN") {
			// Toggle Screen Mode
			Game_ToggleScreenMode();
			return TRUE;
		} else if (w2=="CAMERA") {
			zCAICamera::SetModeChangeEnabled(!zCAICamera::GetModeChangeEnabled());
			if (zCAICamera::GetModeChangeEnabled())		msg = "CamChanges on.";
			else										msg = "CamChanges off.";
			return TRUE;
		} else if (w2=="TURNS")  {
			ANI_ENABLE_TURN = !ANI_ENABLE_TURN;
			if (ANI_ENABLE_TURN)	msg = "Turns on.";
			else					msg = "Turns off.";
			return TRUE;
		} else if (w2=="TIME") {
			zBOOL mip = ogame -> GetShowTime();
			mip = !mip;
			ogame -> SetShowTime(mip);
			if (mip)	msg = "Time on.";
			else		msg = "Time off.";
			return TRUE;
		} else if (w2=="MUSICCONTROL") {
			musicControlEnabled = !musicControlEnabled;
			msg = "Music Control ";
			if (musicControlEnabled)	msg = "on.";
			else						msg = "off.";
		// CODECHANGE [STEFAN]
		} else if (w2=="DEBUGFOCUS") {
			zCVob *v = oCNpc :: player -> GetFocusVob();
			if (!v) { msg = "No focus Vob."; return TRUE; };
			if (ogame->debugAllInstances) { msg = "Not possible while debugging all instances."; return TRUE; };
			if (ogame->debugInstances.IsInList(v) ) {
				ogame->debugInstances.Remove(v);
				msg = "Stopped debugging Focus object";
			} else {
				ogame->debugInstances.Insert(v);
				msg = "Started debugging Focus object";
			}
			return TRUE;
		} else if (w2=="DEBUGCHANNEL") {
			int ch;
			ch = w3.ToInt();
			if (ch < 1 || ch > 32) { msg = "Channel must be an integral value between 1 and 32."; return TRUE; };
			ogame->debugChannels = ogame->debugChannels ^ ( 1 << (ch - 1));
			if (ogame->debugChannels & ( 1 << (ch - 1))) {
				msg = "Channel activated";
			} else {
				msg = "Channel deactivated";
			}
			return TRUE;
		} else if (w2=="ALLDEBUGCHANNELS") {
			ogame->debugChannels = ~ogame->debugChannels;
			msg = "All channels toggled";
			return TRUE;
		// CODECHANGE [STEFAN] END
		}
		msg = "Unknown Command : "+w2;
		return FALSE;
		
	} else if (w1=="START") {
		if (w2=="PARTICLEFX") {
			// Temp
			if (!pfxc) pfxc = zNEW(oCParticleControl(ogame->GetGameWorld()));

			pfxc -> SetPFXName(w3);

			zSTRING w4 = s.PickWord(4," ");
			if (w4=="") {
				pfxc -> SetStartPos(oCNpc::player->GetPositionWorld() + oCNpc::player->GetAtVectorWorld()*200 );
				pfxc -> StartActivePFX();
			} else {
				// An Limb gebunden...
//				pfxc -> StartActivePFX(worldhandler.GetHostPlayer(), w4);
			}
			msg = w3 + " started.";
			return TRUE;
		}

	} else if (w1=="CREATE") {
		if (w2=="PARTICLEFX") {
			// Temp
			if (!pfxc) pfxc = zNEW(oCParticleControl(ogame->GetGameWorld()));

			pfxc -> CreateNewPFX(w3);
			msg = w3 + " created.";
			return TRUE;
		}

	} else if (w1=="EDIT") {
		// **************************************************
		// EDIT
		// **************************************************
		if (w2=="PARTICLEFX") {
			 // Temp
			if (!pfxc) pfxc = zNEW(oCParticleControl(ogame->GetGameWorld()));
			zcon.Hide();
			Game_OpenParticleConsole(w3);
			return TRUE;
		} else if (w2=="COMBAT") {
			zcon.Hide();
			Game_OpenFightConsole();
			return TRUE;
		} else if (w2=="SPECIES") {
			//zcon.Hide();
			Game_OpenSpeciesConsole();
			return TRUE;
		} else if (w2=="AI") {
			Game_ToggleAIConsole();
			return TRUE;
		} else if (w2=="ABILITIES") {
			zcon.Hide();
			if (edit_con) delete edit_con;
			edit_con = zNEW( zCConsole() );
			edit_con -> SetPos			(0,0);
			edit_con -> SetParser		(&parser);
			edit_con -> EditInstance	(oCNpc :: player -> GetInstance(), oCNpc :: player);
			edit_con -> SetChangedFunc	(Edit_Changed);

		} else if (w2=="FOCUS") {
			zCVob *v = oCNpc :: player -> GetFocusVob();
			if (!v) { msg = "No focus Vob."; return TRUE; };
			zcon.Hide();
			if (edit_con) delete edit_con;
			edit_con = zNEW( zCConsole() );
			edit_con -> SetPos		(0,0);
			edit_con -> SetParser	(&parser);
			switch(v->GetVobType()) {
				case zVOB_TYPE_NSC	:	edit_con->EditInstance(((oCNpc*)v) -> GetInstance(), v);
										break;
				case zVOB_TYPE_ITEM	:	edit_con->EditInstance(((oCItem*)v) -> GetInstance(), v);
										break;				
			}
			return TRUE;
		} else if (w2=="THROW") {
			zcon.Hide();
			oCNpcFocus::SetFocusMode(FOCUS_THROW_ITEM);
			if (edit_con) delete edit_con;
			edit_con = zNEW( zCConsole() );
			edit_con -> SetPos		(0,0);
			edit_con -> SetParser	(&parser);
			edit_con -> EditInstance(oCNpcFocus::GetFocusName(),oCNpcFocus::focus);
			return TRUE;
		}
	} else if (w1=="CAMERA") {
		// **************************************************
		// Alles f�r die CAMERA
		// **************************************************
		if (w2=="AUTOSWITCH") {
			zCAICamera::SetModeChangeEnabled(!zCAICamera::GetModeChangeEnabled());
			if (zCAICamera::GetModeChangeEnabled())		msg = "CamChanges on.";
			else										msg = "CamChanges off.";
			return TRUE;
		} else if (w2=="MODE") {
			ogame->GetCameraAI()->SetMode(w3);
			zCAICamera::SetModeChangeEnabled(FALSE);
			msg = "Switched CamMode.";
			return TRUE;
		}
	} else if (w1=="CHEAT") {
		// **************************************************
		// CHEATS
		// **************************************************
		if (w2=="GOD") {
			oCNpc :: godmode = !oCNpc :: godmode;
			if (oCNpc :: godmode) msg = "Godmode on.";
			else					 msg = "Godmode off";
			return TRUE;
		} else if (w2=="FULL") {
			oCNpc :: player -> CompleteHeal();
			msg = "Player healed.";
			return TRUE;
		}
	} else if (w1=="SAVE") {
		// **************************************************
		// Alles was man SAVEN kann
		// **************************************************
		if (w2=="POSITION") {
			Game_SaveSCPos();
			msg = "Position saved.";
			return TRUE;
		
		} else if (w2=="PWF") {
			ogame->SaveWorld(w3,zCWorld::zWLD_SAVE_EDITOR_COMPILED);
			msg = w3 + " saved.";
			return TRUE;

		} else if (w2=="ZEN") {
			ogame->SaveWorld(w3,zCWorld::zWLD_SAVE_EDITOR_COMPILED);
			msg = w3 + " saved.";
			return TRUE;
		
		} else if (w2=="DYNPWF") {
			ogame->SaveWorld(w3,zCWorld::zWLD_SAVE_EDITOR_UNCOMPILED);
			msg = w3 + " saved.";
			return TRUE;
		} else if (w2=="GAME") {
			ogame->WriteSavegame(SAVEGAME_SLOT_MIN);
			return TRUE;
		}
	
	} else if (w1=="LOAD") {
		// **************************************************
		// Alles was man LADEN kann
		// **************************************************
		if (w2=="POSITION") {
			Game_LoadSCPos();
			msg = "Position loaded.";
			return TRUE;
			
		} else if (w2=="GAME") {
			ogame->LoadSavegame(SAVEGAME_SLOT_MIN);
			//ogame->LoadWorld(SAVEGAME_SLOT_MIN);
			return TRUE;
		}


	} else if (w1=="AIGOTO") {
		// **************************************************
		// AI GOTO
		// **************************************************
		oCNpc::player->GetEM()->OnMessage(zNEW( oCMsgMovement(oCMsgMovement::EV_GOROUTE,w2)),oCNpc::player);
		msg = "AI_Goto started ("+w2+").";
		return TRUE;
	
	} else if (w1=="PLAY") {
		if (w2=="ANI") {
			zTModelAniID ani = oCNpc :: player -> GetModel() -> GetAniIDFromAniName(w3);
			if (ani != zMDL_ANI_ID_ILLEGAL) {
				//ani -> SetNextAni( oCNpc :: player -> GetAnictrl() -> _s_walk );
				oCNpc :: player -> GetModel() -> StartAni (ani);
				msg = "Ani "+w3+" started.";
			} else 
				msg = "Ani "+w3+" not found.";
			return TRUE;
		} else if (w2=="SOUND") {
			zCSoundFX* snd = zsound->LoadSoundFXScript (w3);
			if (snd && oCNpc::player) {
				// FIXME : PlaySound geht nicht !
				zsound->PlaySound3D(snd,oCNpc::player);
				msg = "Sound "+w3+ " started.";
			} else
				msg = "Sound "+w3+ " not found.";

			zRELEASE(snd);
			return TRUE;
		} else if (w2=="FACEANI") {
			w3.Upper();
			oCNpc::player -> StartFaceAni(w3);
			msg = "FaceAni "+w3+ " started.";
			return TRUE;
		}
	} else if (w1=="KILL") {
		oCNpc *npc = oCNpc :: player -> GetFocusNpc();
		if (npc) {
			npc->ChangeAttribute( NPC_ATR_HITPOINTS, -999 );
		} else {
			msg = "No focus npc.";
		}
		return TRUE;
	} else if (w1=="SET") {
		if (w2=="TIME") {
			zSTRING w4 = s.PickWord(4," ");
			ogame->SetTime(ogame->GetWorldTimer()->GetDay(),w3.ToInt(),w4.ToInt());
			msg = "Weltzeit : "+ogame->GetWorldTimer()->GetTimeString();
			return TRUE;
		} else if (w2=="THROW") {
			zREAL d = w3.ToInt();
			oCNpcFocus::SetFocusMode(FOCUS_THROW_ITEM);
//			oCNpcFocus::focus->i_range2 = d * d;
			msg = "Wurfweite : "+zSTRING(d);
			return TRUE;
		} else if (w2=="FTHROW") {
			zCVob *v = oCNpc :: player -> GetFocusVob();
			if ((v) && (v->GetVobType()==zVOB_TYPE_ITEM)) {
				((oCItem*)v)->SetFlag(ITM_FLAG_THROW);
				msg = "Throwflag enabled.";
				return TRUE;
			}
			msg = "Failed.";
			return TRUE;
		} else if (w2=="FBBOX") {
			zCVob *v = oCNpc :: player -> GetFocusVob();
			if (v) {
				v->SetDrawBBox3D(TRUE);
				msg = "BBox enabled.";
				return TRUE;
			}
			msg = "Failed.";
			return TRUE;
		
		} else if (w2=="ANISCALE") {
			zREAL f = w3.ToFloat();
			msg = "Aniscale set to "+zSTRING(f);
			return TRUE;

		} else if (w2=="MODELFATNESS") {
			zREAL value = w3.ToFloat();
			oCNpc* npc = oCNpc::player;
			if (npc && npc->GetModel()) {
				npc->SetFatness(value);
				msg = "Modelfatness :"+zSTRING(value);
			} else
				msg = "failed.";
			return TRUE;
		// CODECHANGE [STEFAN]
		} else if (w2=="DEBUGCHANNEL") {
			int ch;
			ch = w3.ToInt();
			if (ch < 1 || ch > 32) { msg = "Channel must be an integral value between 1 and 32."; return TRUE; };
			ogame->debugChannels = ogame->debugChannels | ( 1 << (ch - 1));
			msg = "Channel activated";
			return TRUE;
		} else if (w2=="ALLDEBUGINSTANCES") {
			ogame->debugAllInstances = TRUE;
			ogame->debugInstances.DeleteList();
			msg = "All instances activated";
			return TRUE;
		} else if (w2=="ALLDEBUGCHANNELS") {
			ogame->debugChannels = 0xFFFFFFFF;
			msg = "All channels activated";
			return TRUE;
		} else if (w2=="DEBUGFOCUS") {
			zCVob *v = oCNpc :: player -> GetFocusVob();
			if (!v) { msg = "No focus Vob."; return TRUE; };
			if (ogame->debugAllInstances) ogame->debugAllInstances = FALSE;
			if (!ogame->debugInstances.IsInList(v) )
				ogame->debugInstances.Insert(v);
			msg = "Started debugging focus Object";
			return TRUE;
		} else if (w2=="PERMATTITUDE") {
			oCNpc *v = oCNpc :: player -> GetFocusNpc();
			if (!v) { msg = "No focus Npc."; return TRUE; };
			int att;
			if (w3=="FRIENDLY") 
				att = NPC_ATT_FRIENDLY;
			else if (w3=="NEUTRAL") 
				att = NPC_ATT_NEUTRAL;
			else if (w3=="ANGRY") 
				att = NPC_ATT_ANGRY;
			else if (w3=="HOSTILE") 
				att = NPC_ATT_HOSTILE;
			else
				{
					msg = "Unknown attitude.";
					return TRUE;
				}
			v->SetAttitude(att);
			int tempatt;
			tempatt = v->GetAttitude(oCNpc::player);
			switch (att) {
			case NPC_ATT_FRIENDLY:
				break;
			case NPC_ATT_NEUTRAL:
				if (tempatt == NPC_ATT_FRIENDLY)
					tempatt = NPC_ATT_NEUTRAL;
				break;
			case NPC_ATT_ANGRY:
				if (tempatt == NPC_ATT_FRIENDLY || tempatt == NPC_ATT_NEUTRAL)
					tempatt = NPC_ATT_ANGRY;
				break;
			case NPC_ATT_HOSTILE:
				if (tempatt == NPC_ATT_FRIENDLY || tempatt == NPC_ATT_NEUTRAL || tempatt == NPC_ATT_ANGRY)
					tempatt = NPC_ATT_HOSTILE;
				break;
			}
			v->SetTmpAttitude(tempatt);
			return TRUE;
		} else if (w2=="TEMPATTITUDE") {
			oCNpc *v = oCNpc :: player -> GetFocusNpc();
			if (!v) { msg = "No focus Npc."; return TRUE; };
			int att;
			if (w3=="FRIENDLY") 
				att = NPC_ATT_FRIENDLY;
			else if (w3=="NEUTRAL") 
				att = NPC_ATT_NEUTRAL;
			else if (w3=="ANGRY") 
				att = NPC_ATT_ANGRY;
			else if (w3=="HOSTILE") 
				att = NPC_ATT_HOSTILE;
			else
				{
					msg = "Unknown attitude.";
					return TRUE;
				}
			v->SetTmpAttitude(att);
			return TRUE;
		} else if (w2=="TRUEGUILD") {
			oCNpc *v = oCNpc :: player -> GetFocusNpc();
			if (!v) v = oCNpc::player; // { msg = "No focus Npc."; return TRUE; };

			zCParser *p = zCParser :: GetParser();
			zCPar_Symbol *sym = p->GetSymbol(w3);
			int gn;

			if (!sym || (sym->type != zPAR_TYPE_INT)) { msg = "Not a valid guild name."; return TRUE; };

			sym->GetValue(gn);
			v->SetTrueGuild(gn);

			return TRUE;
		} else if (w2=="GUILD") {
			oCNpc *v = oCNpc :: player -> GetFocusNpc();
			if (!v) v = oCNpc::player; // { msg = "No focus Npc."; return TRUE; };

			zCParser *p = zCParser :: GetParser();
			zCPar_Symbol *sym = p->GetSymbol(w3);
			int gn;

			if (!sym || (sym->type != zPAR_TYPE_INT)) { msg = "Not a valid guild name."; return TRUE; };

			sym->GetValue(gn);
			v->SetGuild(gn);

			return TRUE;
		// CODECHANGE [STEFAN] END
		}
    // CODECHANGE [MICHAEL]
	} else if (w1=="VERSION") {
		static long VCallCount = 0;

		if ((++VCallCount % 13) != 0)
			msg = "Version number is: " + zSTRING(APP_VERSION);
		else {
			msg = (megamorzel / VCallCount);
			megamorzel += megamorzel;
		}

		return TRUE;
	// CODECHANGE [MICHAEL] END
	// CODECHANGE [STEFAN]
	} else if (w1=="CLEAR") {
		if (w2=="DEBUGCHANNEL") {
			int ch;
			ch = w3.ToInt();
			if (ch < 1 || ch > 32) { msg = "Channel must be an integral value between 1 and 32."; return TRUE; };
			ogame->debugChannels = ogame->debugChannels & ~( 1 << (ch - 1));
			msg = "Channel deactivated";
			return TRUE;
		} else if (w2=="ALLDEBUGCHANNELS") {
			ogame->debugChannels = 0;
			msg = "All channels deactivated";
			return TRUE;
		} else if (w2=="DEBUGFOCUS") {
			if (ogame->debugAllInstances) { msg = "Not possible while debugging all instances."; return TRUE; };
			zCVob *v = oCNpc :: player -> GetFocusVob();
			if (!v) { msg = "No focus Vob."; return TRUE; };
			if (ogame->debugInstances.IsInList(v) )
				ogame->debugInstances.Remove(v);
			msg = "Stopped debugging focus object";
			return TRUE;
		} else if (w2=="ALLDEBUGINSTANCES") {
			ogame->debugInstances.DeleteList();
			ogame->debugAllInstances = FALSE;
			msg = "Stopped debugging instances";
			return TRUE;
		}
	// CODECHANGE [STEFAN] END

	} else if (w1=="AUTOCOMPLEMENT") {
		if (zcon.HasAutoCompletion()) 
			msg = "Autocomplement off.";
		else
			msg = "Autocomplement on.";
		zcon.SetAutoCompletion(!zcon.HasAutoCompletion());
		return TRUE;
	
	} else if (w1=="ZMARK") {
		MarkOccluderPolys( ogame->GetGameWorld() -> GetBspTree() -> mesh );
		msg = "Occluder Polys marked.";
		return TRUE;
	}
	
	else if (w1=="PARSERD") {
		if (w2=="OFF") {
			Game_ParserDebugOff();
			msg = "Parser Debug Windows off";
		} else if (w2=="ON") {
			Game_ParserDebug(w2);
			msg = "Parser Debug Windows on";
		} else if (w2=="MERGE") {
			parser.MergeFile(w3);
			msg = "File "+w3+" merged.";
		} else if (w2=="PCODE") {
			parser.ShowPCodeSpy(w3);
			msg = "PCode written to zSpy.";
		}
		return TRUE;
	} 

	else if (s.Search("LC1")!=-1)
	{
		zPOINT3 pos = ogame->GetSelfPlayerVob()->GetPositionWorld();
		zPOINT3 at = ogame->GetSelfPlayerVob()->GetAtVectorWorld();

		pos = pos + at*150;

		oCTriggerChangeLevel* lvChg = zNEW(oCTriggerChangeLevel());		
		lvChg->SetStaticVob(TRUE);
		lvChg->SetDrawBBox3D(TRUE);

		lvChg->SetLevelName("NET/NETLEVEL1.ZEN","A");
		lvChg->SetPositionWorld(pos);
		ogame->GetGameWorld()->AddVob(lvChg);

		return TRUE;
	}
	else if (s.Search("LC2")!=-1)
	{
		zPOINT3 pos = ogame->GetSelfPlayerVob()->GetPositionWorld();
		zPOINT3 at = ogame->GetSelfPlayerVob()->GetAtVectorWorld();

		pos = pos + at*150;

		oCTriggerChangeLevel* lvChg = zNEW(oCTriggerChangeLevel());		
		lvChg->SetStaticVob(TRUE);
		lvChg->SetDrawBBox3D(TRUE);

		lvChg->SetLevelName("NET/NETLEVEL2.ZEN","A");
		lvChg->SetPositionWorld(pos);
		ogame->GetGameWorld()->AddVob(lvChg);

		return TRUE;
	}
	else if (w1=="FORCE") {
		if (w2=="AIDETECTION") {
			oCNpc :: player -> AI_ForceDetection();
			msg = "AI Detection started.";
		}
		return TRUE;
	}
	
	else if (w1=="APPLY") {
		if (w2=="OVERLAYMDS") {

			if (w3.Search(".")<0) w3 += ".MDS";	

			if (oCNpc::player->GetModel()->HasAppliedModelProtoOverlay(w3)) {
				msg = w3 + " already applied.";
			
			} else if (oCNpc :: player -> GetModel() -> ApplyModelProtoOverlay(w3)) {			
				oCNpc :: player -> GetAnictrl()	-> InitAnimations();
				msg = w3+" applied.";
			
			} else 
				msg = "failure - mds not found.";
			
			return TRUE;
		
		} else if (w2=="RANDOMANI") {
			zCModel* model = oCNpc::player->GetModel();
			zSTRING w4 = s.PickWord(4," "); w4.Upper();
			zTModelAniID ani = model -> GetAniIDFromAniName(w3);
			zTModelAniID ran = model -> GetAniIDFromAniName(w4);
			if (!ani) { msg = "Ani" + w3 + " not found."; return TRUE; }
			if (!ran) { msg = "Ani" + w4 + " not found."; return TRUE; }
			model -> InsertRandAni	(ani, ran);
			model -> SetRandAniFreq	(ani,1.0F);
			msg = "Randomani applied.";			
			return TRUE;
		} else if (w2=="ANIFREQ") {
			zCModel* model = oCNpc::player->GetModel();
			zSTRING w4 = s.PickWord(4," "); w4.Upper();
			zTModelAniID ani = model -> GetAniIDFromAniName(w3);
			if (!ani) { msg = "Ani" + w3 + " not found."; return TRUE; }
			model -> SetRandAniFreq	(ani, w4.ToFloat());
			msg = "Random-Ani-Freq " + w4;
			return TRUE;
		}
		return TRUE;
	} 
	else if (w1=="REMOVE") {
		if (w2=="OVERLAYMDS") {

			if (w3.Search(".")<0) w3 += ".MDS";	

			if (!oCNpc::player->GetModel()->HasAppliedModelProtoOverlay(w3)) {
				oCNpc::player->GetModel()->RemoveModelProtoOverlay(w3);
				msg = w3 + " removed.";
			
			} else {

				msg = w3+" is not applied.";
			}
			return TRUE;

		} 
	
	} else if (w1=="TORCH") {
		zoptions->ChangeDir(DIR_WORLD);
		zCWorld* _wld	= ogame->GetGameWorld();
		zCVob *torch	= _wld->MergeVobSubtree("TORCH_BURNED.ZEN",oCNpc::player);
		_wld->RemoveVobSubtree	(torch);
		_wld->AddVob			(torch);
		torch->SetCollDet		(FALSE);
		torch->SetPositionWorld (oCNpc::player->GetPositionWorld()+oCNpc::player->GetAtVectorWorld()*200);
		Game_StartParticleEffects(torch->globalVobTreeNode);
	}

	/*
	} else if (w1=="MARKOP") {
		MarkOccluderPolys( oCNpc :: world_3d -> GetBspTree() -> mesh );
		msg = "Occluder Polys marked.";
	
	} else if (w1=="LOADBSP") {
		oCNpc :: world_3d -> LoadBspTree(w2+".zsp");		
		msg = "Bsp loaded.";

	
	} else if (w1=="KILL") {
		zCVob *v = oCNpc :: player -> GetFocusVob();
		if ((!v) || (v->GetVobType()!=zVOB_TYPE_NSC)) {
			msg = "No focus npc.";
			return TRUE;
		}
		((oCNpc*)v) -> Hit(0,10000,200);

//	} else if (w1=="RENDERDRAW") {
//		zrenderer -> SetPolyDrawMode( zTRnd_PolyDrawMode(w2.ToInt()) );
	
//	} else {*/
	msg = "Unknown command : " + w1;
	return FALSE;
//	return TRUE;
}

void Game_StartParticleEffects(zCTree<zCVob>* vobtree)
{
	if (!vobtree) return;

	zCVob* vob = vobtree->GetData();
	if (vob) {
		zCParticleFX* pfx	= dynamic_cast<zCParticleFX*>(vob->GetVisual());
		if (pfx) pfx->CreateParticles();
	}
		
	// recursive search
	zCTree<zCVob>* child = vobtree->GetFirstChild();
	while (child!=0) {
		Game_StartParticleEffects(child);
		child	= child->GetNextChild();
	};
}


/*--------------------------------------------------------------------------
    Game_InitConsole()

    28-Aug-00       [Michael]
                      VERSION Konsolenkommando wegen Fingerprint
--------------------------------------------------------------------------*/ 
void Game_InitConsole()
{
	zcon.AddEvalFunc (oCGame::ConsoleEvalFunc);
	zcon.Register("insert"			,"insert a script-instance [name]",2);
	zcon.Register("goto waypoint"	,"beam player to waypoint [name]");
	
	zcon.Register("toggle desktop"	,"desktop on/off");
	zcon.Register("toggle debug"	,"debug-Messages on/off");	
	zcon.Register("toggle spy"		,"spy-Messages on/off");
	zcon.Register("toggle text"		,"text window on/off");
	zcon.Register("toggle waynet"	,"waynet on/off");
	zcon.Register("toggle frame"	,"frame-info on/off");
	zcon.Register("toggle screen"	,"fullscreen / window");
	zcon.Register("toggle aniinfo"	,"animation-info on/off");
	zcon.Register("toggle camera"	,"change camera mode on/off");
	zcon.Register("toggle turns"	,"turn player on/off");
	zcon.Register("toggle time"		,"show worldtime on/off");
	zcon.Register("toggle wayboxes"	,"wayboxes on/off");
	zcon.Register("toggle freepoints","freepoints on/off");
	zcon.Register("toggle musiccontrol","game music logic on/off");

	zcon.Register("edit combat"		,"fight console on/off");
	zcon.Register("edit abilities"	,"edit player-instance");
	zcon.Register("edit species"	,"edit species values");
	zcon.Register("edit focus"		,"edit focus object");
	zcon.Register("edit ai"			,"edit ai parameters");

	zcon.Register("set throw"		,"set throw range");

	zcon.Register("camera mode"			,"set camera mode [name]");
	zcon.Register("camera autoswitch"	,"toggle camera autoswitch");

	zcon.Register("cheat full"		,"heal player");
	zcon.Register("cheat god"		,"godmode on/off");

	zcon.Register("save position"	,"save player position");
	zcon.Register("save zen"		,"save level [name.ZEN]");

	zcon.Register("load position"	,"restore player position");

	zcon.Register("lc1"				,"Include LevelChanger to net/netlevel1.zen.");
	zcon.Register("lc2"				,"Include LevelChanger to net/netlevel2.zen.");

	zcon.Register("play ani"		,"play animation [name]");
	zcon.Register("play sound"		,"player sound instance [name]");
	zcon.Register("kill"			,"kill focus npc");
	zcon.Register("set time"		,"set worldtime [hh mm]");
	
	zcon.Register("aigoto"			,"player goes to waypoint [name]");

	zcon.Register("autocomplement"	,"autocomplement on/off");

	zcon.Register("witness attack"	,"call reaction attack");
	zcon.Register("witness aim"		,"call reaction aim");
	zcon.Register("witness steal"	,"call reaction steal");

	zcon.Register("parserd on"		,"show parser debug info");
	zcon.Register("parserd off"		,"hide parser debug info");
	zcon.Register("parserd merge"	,"merge 'SRC' oder 'D'-File");
	zcon.Register("parserd pcode"	,"print pcode to spy.");

	zcon.Register("set fbbox"		,"show boundingbox of focus object");

	zcon.Register("apply overlaymds",	"enable overlay-MDS [mds-name]");
	zcon.Register("remove overlaymds",	"remove overlay-MDS [mds-name]");
	
	zcon.Register("apply randomani" ,	"apply a random-ani [ani-name, random-ani-name]");
	zcon.Register("apply anifreq"	,	"set random-ani frequency [ani-name, frequency]");

	zcon.Register("edit particlefx"		,"edit particle-effect-instance [name]");
	zcon.Register("start particlefx"	,"start particle-effect-instance [name]");
	zcon.Register("create particlefx"	,"create new particle-effect-instance [name]");
	zcon.Register("delete particlefx"	,"delete last used particle-effect-instance");

	zcon.Register("play faceani"		,"play a face-ani [name]");

	zcon.Register("save game"			,"save game in slot 0");
	zcon.Register("load game"			,"load game from Slot 0");
	
	zcon.Register("set modelfatness"	,"set model fatness [value]");

	// CODECHANGE [STEFAN]
	zcon.Register("set debugfocus"		,"set debug focus object");
	zcon.Register("clear debugfocus"		,"clear debug focus object");
	zcon.Register("toggle debugfocus"		,"toggle debug focus object");
	zcon.Register("set alldebuginstances"		,"set all debug instances");
	zcon.Register("clear alldebuginstances"		,"clear all debug instances");
	zcon.Register("set debugchannel"		,"set debug channel [ch]");
	zcon.Register("clear debugchannel"		,"clear debug channel [ch]");
	zcon.Register("toggle debugchannel"		,"toggle debug channel [ch]");
	zcon.Register("set alldebugchannels"		,"set all debug channels");
	zcon.Register("clear alldebugchannels"		,"clear all debug channels");
	zcon.Register("toggle alldebugchannels"		,"toggle all debug channels");
	zcon.Register("set permattitude"		,"set permanent attitude [attitude]");
	zcon.Register("set tempattitude"		,"set temporary attitude [attitude]");
	zcon.Register("set trueguild"		,"set true guild [guild]");
	zcon.Register("set guild"		,"set guild [guild]");
	zcon.Register("goto vob"	,"beam player to vob [name] ([num])");
	zcon.Register("print vob"	,"print info for vob(s) [name]");
	// CODECHANGE [STEFAN] END

	// CODECHANGE [MICHAEL]
	zcon.Register("version"	,"print version info");
	// CODECHANGE [MICHAEL] END
	

	game_con = TRUE;
}

void Game_OpenConsole()
{
	if (!game_con) Game_InitConsole();
	zcon.Toggle();
}

// CODECHANGE [STEFAN, MICHAEL]

static zINT			Game_SpeciesConsole_TempFightRange;
static zINT			Game_SpeciesConsole_JumpupHeight;
static zREAL		Game_SpeciesConsole_TurnSpeed;
static zINT			Game_SpeciesConsole_BloodMaxDistance;
static zINT			Game_SpeciesConsole_BloodFlow;
static zINT			Game_SpeciesConsole_BloodAmount;
static zSTRING		Game_SpeciesConsole_BloodTexture;
static zREAL		Game_SpeciesConsole_SwimTime;  
static zREAL		Game_SpeciesConsole_DiveTime;  
static zBOOL		Game_SpeciesConsole_DisableAutoroll;  
static zBOOL		Game_SpeciesConsole_SurfaceAlign;  
static oTDamageMode Game_SpeciesConsole_DamageType;  



// CODECHANGE [STEFAN, MICHAEL] END

static int game_aicon_spawnTime;
static int game_aicon_spawnInsertRange;
static int game_aicon_spawnRemoveRange;
static int game_aicon_scriptStateSkip;
static int game_aicon_messagesSkip;
static int game_aicon_baseAIenabled;

void Game_ChangeAIConsole(const zSTRING &var)
{
	if (var=="SPAWN")		oCSpawnManager::SetSpawnTime	(game_aicon_spawnTime);				else
	if (var=="INSERT")		oCSpawnManager::SetInsertRange	(game_aicon_spawnInsertRange);		else
	if (var=="REMOVE")		oCSpawnManager::SetRemoveRange	(game_aicon_spawnRemoveRange);		else
	if (var=="SCRIPT")		oCNpc::SetScriptStateSkip		(game_aicon_scriptStateSkip);		else
	if (var=="MESSAGES")	oCNpc::SetMessagesSkip			(game_aicon_messagesSkip);			else
	if (var=="BASE")		oCNpc::SetBaseAIEnabled			(game_aicon_baseAIenabled>0);
}

void Game_ToggleAIConsole()
{
	if (game_aiConsole) {
		delete (game_aiConsole);
		game_aiConsole = NULL;
	}

	game_aicon_spawnTime			= (int)ogame->GetSpawnManager()->GetSpawnTime();
	game_aicon_spawnInsertRange		= (int)ogame->GetSpawnManager()->GetInsertRange();
	game_aicon_spawnRemoveRange		= (int)ogame->GetSpawnManager()->GetRemoveRange();
	game_aicon_scriptStateSkip		= (int)oCNpc::GetScriptStateSkip();
	game_aicon_messagesSkip			= (int)oCNpc::GetMessagesSkip();
	game_aicon_baseAIenabled		= (int)oCNpc::GetBaseAIEnabled();
	
	game_aiConsole  = zNEW(zCConsole(0,2500,zSTRING("AI - Konsole")));
	game_aiConsole -> InsertVar("Spawntime (ms)"				,"SPAWN"	,zCON_TYPE_INT,&game_aicon_spawnTime);
	game_aiConsole -> InsertVar("Spawn-Insert-Range (cm)"		,"INSERT"	,zCON_TYPE_INT,&game_aicon_spawnInsertRange);
	game_aiConsole -> InsertVar("Spawn-Remove-Range (cm)"		,"REMOVE"	,zCON_TYPE_INT,&game_aicon_spawnRemoveRange);
	game_aiConsole -> InsertVar("Scriptstates skiptimer (ms)"	,"SCRIPT"	,zCON_TYPE_INT,&game_aicon_scriptStateSkip);
	game_aiConsole -> InsertVar("Messages skiptimer (ms)"		,"MESSAGES"	,zCON_TYPE_INT,&game_aicon_messagesSkip);
	game_aiConsole -> InsertVar("Base AI enabled"				,"BASE"		,zCON_TYPE_INT,&game_aicon_baseAIenabled);
	game_aiConsole -> SetChangedFunc (Game_ChangeAIConsole);
	game_aiConsole -> Toggle();
};

void Game_SpeciesChanged(const zSTRING &var)
{
	oCAniCtrl_Human *ac = oCNpc :: player -> GetAnictrl();
	if (var=="SLIDE1") {
		ac -> config.zMV_MAX_GROUND_ANGLE_WALK		= Alg_Deg2Rad(ac->angle_slide1);
	} else if (var=="SLIDE2") {
		ac -> config.zMV_MAX_GROUND_ANGLE_SLIDE2	= Alg_Deg2Rad(ac->angle_slide2);
	} else if (var=="HEADING") {
		ac -> config.zMV_DCUL_WALL_HEADING_ANGLE	= Alg_Deg2Rad(ac->angle_heading);
	} else if (var=="HORIZ") {
		ac -> config.zMV_DCUL_WALL_HORIZ_ANGLE		= Alg_Deg2Rad(ac->angle_horiz);	
	} else if (var=="GROUND") {
		ac -> config.zMV_DCUL_GROUND_ANGLE			= Alg_Deg2Rad(ac->angle_ground);	
// CODECHANGE [MICHAEL]
// SWIM_TIME, DIVE_TIME, DISABLE_AUTOROLL, SURFACE_ALIGN, DAMAGE_TYPE
	} else if (var=="SWIM_TIME") {
		oCNpc::player->SetSwimDiveTime(Game_SpeciesConsole_SwimTime, Game_SpeciesConsole_DiveTime);  
	} else if (var=="DIVE_TIME") {
		oCNpc::player->SetSwimDiveTime(Game_SpeciesConsole_SwimTime, Game_SpeciesConsole_DiveTime);  
	} else if (var=="DISABLE_AUTOROLL") {  
		ac -> SetAutoRollEnabled(!Game_SpeciesConsole_DisableAutoroll);  
	} else if (var=="SURFACE_ALIGN") {
		ac ->SetConfigDoSurfaceAlign(zCAIPlayer::zTSurfaceAlignMode(Game_SpeciesConsole_SurfaceAlign));  
/*	} else if (var=="DAMAGE_TYPE") {
		oCNpc::player->SetDefaultDamage(Game_SpeciesConsole_DamageType);  
*/
	} else if (var=="TURN") {
		oCNpc::player->SetTurnSpeed(Game_SpeciesConsole_TurnSpeed);  
	} else if (var=="JUMPUP") {
		ac->SetJumpUpForceByHeight(Game_SpeciesConsole_JumpupHeight);
	} else if (var=="BL_DIST") {
		oCNpc::player->SetBloodDistance(Game_SpeciesConsole_BloodMaxDistance);
	} else if (var=="BL_FLOW") {
		oCNpc::player->EnableBloodFlow(Game_SpeciesConsole_BloodFlow);
	} else if (var=="BL_AMOUNT") {
		oCNpc::player->SetBloodAmount(Game_SpeciesConsole_BloodAmount);
	} else if (var=="BL_TEX") {
		oCNpc::player->SetBloodTexture(Game_SpeciesConsole_BloodTexture);
// CODECHANGE [MICHAEL]
// CODECHANGE [STEFAN]
	} else if (var=="RANGE") {
//		oCNpc::player->SetFightRangeBase(Game_SpeciesConsole_TempFightRange);
// CODECHANGE [STEFAN] END
	}
}

void Game_OpenSpeciesConsole()
{
	if (game_species_con) {
		delete (game_species_con);
		game_species_con = NULL;
	}
	oCNpc :: player -> GetAnictrl() -> InitAngleValuesForConsole();
	
	game_species_con =  zNEW(zCConsole(0,1500,zSTRING("Spezies abh�ngige Konstanten")));
	game_species_con -> SetDim(6000,6000);

	game_species_con -> InsertVar ( zSTRING("Slide-Winkel 1"),			zSTRING("SLIDE1"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> angle_slide1);							
	game_species_con -> InsertVar ( zSTRING("Slide-Winkel 2"),			zSTRING("SLIDE2"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> angle_slide2);							
	game_species_con -> InsertVar ( zSTRING("JumpUpMid bis"),			zSTRING("MID"),		zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> config.zMV_YMAX_JUMPMID);							
	game_species_con -> InsertVar ( zSTRING("JumpUpLow bis"),			zSTRING("LOW"),		zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> config.zMV_YMAX_JUMPLOW);							
//	game_species_con -> InsertVar ( zSTRING("Tauchzeit (ms)"),			zSTRING("DIVE"),	zCON_TYPE_FLOAT,&oCNpc :: player -> divetime);							
//	game_species_con -> InsertVar ( zSTRING("Schwimmzeit (ms)"),		zSTRING("SWIM"),	zCON_TYPE_FLOAT,&oCNpc :: player -> swimtime);							
	game_species_con -> InsertVar ( zSTRING("Wasserh�he Knie"),			zSTRING("KNEE"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> config.zMV_WATER_DEPTH_KNEE);
	game_species_con -> InsertVar ( zSTRING("Wasserh�he Brust"),		zSTRING("CHEST"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> config.zMV_WATER_DEPTH_CHEST);
// CODECHANGE [MICHAEL]

	Game_SpeciesConsole_JumpupHeight = (oCNpc :: player -> GetAnictrl())->GetJumpUpHeight();
	game_species_con -> InsertVar ( zSTRING("JumpUpHeight"),	zSTRING("JUMPUP"),	zCON_TYPE_INT,&Game_SpeciesConsole_JumpupHeight);							
	Game_SpeciesConsole_TurnSpeed = oCNpc::player->GetTurnSpeed()*1000.0f;     // warum die Methoden unsymmetrisch sind, bleibt ein Geheimnis...
	game_species_con -> InsertVar ( zSTRING("TurnSpeed"),		zSTRING("TURN"),	zCON_TYPE_FLOAT,&Game_SpeciesConsole_TurnSpeed);
	Game_SpeciesConsole_BloodMaxDistance = oCNpc::player->GetBloodDistance();
	game_species_con -> InsertVar ( zSTRING("BloodDistance"),	zSTRING("BL_DIST"),	zCON_TYPE_INT,&Game_SpeciesConsole_BloodMaxDistance);							
	Game_SpeciesConsole_BloodFlow        = oCNpc::player->IsBloodFlowEnabled();
	game_species_con -> InsertVar ( zSTRING("BloodFlow"),		zSTRING("BL_FLOW"),	zCON_TYPE_INT,&Game_SpeciesConsole_BloodFlow);							
	Game_SpeciesConsole_BloodAmount      = oCNpc::player->GetBloodAmount();
	game_species_con -> InsertVar ( zSTRING("BloodAmount"),		zSTRING("BL_AMOUNT"),zCON_TYPE_INT,&Game_SpeciesConsole_BloodAmount);							
	Game_SpeciesConsole_BloodTexture     = oCNpc::player->GetBloodTexture();
	game_species_con -> InsertVar ( zSTRING("BloodTexture"),	zSTRING("BL_TEX"),	zCON_TYPE_STRING,&Game_SpeciesConsole_BloodTexture);

	zREAL pseudo;
	oCNpc::player->GetSwimDiveTime(Game_SpeciesConsole_SwimTime,Game_SpeciesConsole_DiveTime,pseudo); 
	Game_SpeciesConsole_SwimTime		/= 1000.0f;
	Game_SpeciesConsole_DiveTime		/= 1000.0f;
	game_species_con -> InsertVar ( zSTRING("SwimTime"),	zSTRING("SWIM_TIME"),	zCON_TYPE_FLOAT,&Game_SpeciesConsole_SwimTime);							
	game_species_con -> InsertVar ( zSTRING("DiveTime"),	zSTRING("DIVE_TIME"),	zCON_TYPE_FLOAT,&Game_SpeciesConsole_DiveTime);							
	Game_SpeciesConsole_DisableAutoroll = ! (oCNpc :: player -> GetAnictrl()) -> GetAutoRollEnabled();
	game_species_con -> InsertVar ( zSTRING("DisableAutoroll"),	zSTRING("DISABLE_AUTOROLL"),	zCON_TYPE_INT,&Game_SpeciesConsole_DisableAutoroll);							
    Game_SpeciesConsole_SurfaceAlign	= ( oCNpc :: player -> GetAnictrl()) -> GetConfigDoSurfaceAlign();  
   	game_species_con -> InsertVar ( zSTRING("SurfaceAlign"),	zSTRING("SURFACE_ALIGN"),	zCON_TYPE_INT,&Game_SpeciesConsole_SurfaceAlign);							
	



// CODECHANGE [MICHAEL] END
	game_species_con -> InsertVar ( zSTRING("Stufenh�he"),				zSTRING("STEP"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> config.zMV_STEP_HEIGHT);							
	game_species_con -> InsertVar ( zSTRING("Climb-Wall Heading"),		zSTRING("HEADING"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> angle_heading);
	game_species_con -> InsertVar ( zSTRING("Climb-Wall Horiz."),		zSTRING("HORIZ"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> angle_horiz);							
	game_species_con -> InsertVar ( zSTRING("Climb-Ground"),			zSTRING("GROUND"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAnictrl() -> angle_ground);							
//	game_species_con -> InsertVar ( zSTRING("Wallsliding"),				zSTRING("WALL"),	zCON_TYPE_INT  ,&oCNpc :: player -> GetAnictrl() -> zMV_DO_WALL_SLIDING);							
	
//	game_species_con -> InsertVar ( zSTRING("Inner"),					zSTRING("INNER"),	zCON_TYPE_FLOAT,&oCNpc :: player -> GetAIManager() -> dis_r0);							
//	game_species_con -> InsertVar ( zSTRING("Outer"),					zSTRING("OUTER"),	zCON_TYPE_FLOAT  ,&oCNpc :: player -> GetAIManager() -> dis_r1);								
// CODECHANGE [STEFAN]
	Game_SpeciesConsole_TempFightRange = oCNpc::player->GetFightRange();
	game_species_con -> InsertVar ( zSTRING("Fight-Range"),				zSTRING("RANGE"),	zCON_TYPE_INT,&Game_SpeciesConsole_TempFightRange);							
// CODECHANGE [STEFAN] END
	game_species_con -> SetChangedFunc (Game_SpeciesChanged);
	game_species_con -> Toggle();
}

void Game_OpenFightConsole()
{
	if (game_fight_con) {
		delete (game_fight_con);
		game_fight_con = NULL;
	}
	// ConsolenTest
	game_fight_con  = zNEW(zCConsole(0,4000,zSTRING("Kampfsystem")));
	game_fight_con -> InsertVar ( zSTRING("AutoAim H�henwinkel"),		zSTRING("UPANGLE"), zCON_TYPE_INT,	&oCNpc :: angle_far_up);
	game_fight_con -> InsertVar ( zSTRING("AutoAim Seitenwinkel"),		zSTRING("SIANGLE"),	zCON_TYPE_INT,	&oCNpc :: angle_far_side);
	game_fight_con -> InsertVar ( zSTRING("Nahkampf-Heading Winkel"),	zSTRING("HEADING"), zCON_TYPE_INT,	&oCNpc :: angle_near);
	
//	game_fight_con -> InsertVar ( zSTRING("Nahkampf-Reichweite"),		zSTRING("RANGE"),		zCON_TYPE_INT,	&oCNpc :: player -> fight_range);
//	game_fight_con -> InsertVar ( zSTRING("Run2Walk-Distance"),			zSTRING("RUN2WALK"),	zCON_TYPE_INT,	&oCNpc :: player -> fight_run2walk_len);

	game_fight_con -> Toggle();
}



// CODECHANGE [STEFAN]
zBOOL oCGame::IsDebuggingChannel(int ch)
{
	return ((debugChannels & (1 << (ch - 1))) != 0);
}

zBOOL oCGame::IsDebuggingInstance(zCVob *vob)
{
	return debugInstances.IsInList(vob);
}

zBOOL oCGame::IsDebuggingAllInstances()
{
	return debugAllInstances;
}
// CODECHANGE [STEFAN] END

//
//	CODECHANGE [ROMAN]
//

////////////////////////////////////////
// VIEW-MANAGEMENT
////////////////////////////////////////

zBOOL oCGame::OpenView( oTGameDialogView enuView )
{
	if ( ( ! array_view_visible[ enuView ] ) && ( array_view_enabled[ enuView ] ) )
	{
		array_view_visible[ enuView ] = TRUE;
		array_view[ enuView ] -> Open();								
	}
	return TRUE;
}

zBOOL oCGame::CloseView( oTGameDialogView enuView )
{
	if ( ( array_view_visible[ enuView ] ) && ( array_view_enabled[ enuView ] ) )
	{
		array_view_visible[ enuView ] = FALSE;
		array_view[ enuView ] -> Close();								
	}
	return TRUE;
}

//
//	CODECHANGE [ROMAN] END
//


#pragma warning ( default:4244 )
#pragma warning ( default:4706 )











