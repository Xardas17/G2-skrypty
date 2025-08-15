/******************************************************************************** 
 
     $Workfile:: oGameManager.cpp     $                $Date:: 12.04.01 17:27   $
     $Revision:: 189                  $             $Modtime:: 5.04.01 14:21    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oGameManager.cpp $
 * 
 * 189   12.04.01 17:27 Edenfeld
 * Patch 2 (1.08): �nderungen f�rs Sound System (Menu)
 * 
 * 188   16.03.01 15:45 Speckels
 * 
 * 187   15.03.01 14:00 Speckels
 * 
 * 186   14.03.01 18:40 Speckels
 * 
 * 185   14.03.01 18:01 Speckels
 * 
 * 184   13.03.01 18:57 Speckels
 * 
 * 183   12.03.01 20:17 Speckels
 * 
 * 182   18.02.01 21:26 Speckels
 * 
 * 181   18.02.01 13:50 Speckels
 * 
 * 179   18.02.01 13:34 Speckels
 * 
 * 178   18.02.01 13:24 Speckels
 * 
 * 177   17.02.01 16:17 Speckels
 * 
 * 176   16.02.01 21:02 Speckels
 * 
 * 175   16.02.01 21:01 Speckels
 * 
 * 174   16.02.01 15:17 Wohlers
 * 
 * 173   16.02.01 14:08 Speckels
 * 
 * 171   16.02.01 13:12 Speckels
 * 
 * 170   16.02.01 11:39 Moos
 * NPCs werden nun vor dem Verlassen geshrinkt. Verhindert Abkachler
 * sp�ter.
 * 
 * 169   15.02.01 21:17 Speckels
 * 
 * 168   15.02.01 21:17 Speckels
 * 
 * 167   15.02.01 21:16 Speckels
 * 
 * 165   15.02.01 2:46 Speckels
 * 
 * 163   15.02.01 0:47 Speckels
 * 
 * 162   14.02.01 23:54 Speckels
 * 
 * 161   14.02.01 22:51 Speckels
 * 
 * 160   14.02.01 22:48 Speckels
 * 
 * 159   14.02.01 21:32 Speckels
 * 
 * 158   14.02.01 21:04 Speckels
 * 
 * 157   14.02.01 20:04 Speckels
 * 
 * 156   14.02.01 17:12 Speckels
 * 
 * 155   14.02.01 15:50 Speckels
 * 
 * 154   14.02.01 14:30 Speckels
 * 
 * 153   13.02.01 20:28 Speckels
 * 
 * 152   13.02.01 18:15 Speckels
 * 
 * 151   13.02.01 11:26 Speckels
 * 
 * 150   11.02.01 18:30 Speckels
 * 
 * 149   11.02.01 13:34 Speckels
 * 
 * 148   10.02.01 20:09 Speckels
 * 
 * 147   10.02.01 18:13 Speckels
 * 
 * 146   10.02.01 15:17 Speckels
 * 
 * 145   9.02.01 18:44 Speckels
 * 
 * 144   8.02.01 21:58 Speckels
 * 
 * 143   8.02.01 16:25 Speckels
 * 
 * 142   6.02.01 23:25 Speckels
 * 
 * 113   26.01.01 15:57 Speckels
 * 
 * [...]
 * 
 * 58    19.10.00 18:22 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 189 $ ($Modtime: 5.04.01 14:21 $)


#include "ogamemanager.h"
#include "oanictrl.h"

// engine
#include "zcore.h"
#include "zengine.h"
#include "zoption.h"
#include "zoption_const.h"
#include "zviews.h"
#include "zscandir.h"
#include "ztexture.h"


// game

#include "zTypes.h"
#include "zList.h"
#include "zParser.h"
#include "zview.h"
#include "z3D.h"
#include "zVob.h"
#include "zFile3D.h"
#include "zRenderer.h"
#include "zAlgebra.h"
#include "zModel.h"
#include "zMorphMesh.h"
#include "zParticle.h"
#include "zSound.h"
#include "zPhysics.h"
#include "zSoundMan.h"
#include "zMusic.h"
#include "zBuffer.h"
#include "zArchiver.h"
#include "zAICamera.h"
#include "zCCSPlayer.h"
#include "zInput_Win32.h"
#include "zEventMan.h"
#include "zWayNet.h"
#include "zFonts.h"
#include "zSparseArray.h"

#include "oobert.h"
#include "ogame.h"
#include "omenu_main.h"
#include "omenu_tools.h"
#include "omenusavegame.h"
#include "ooCarsten.h"
#include "oworld.h"
#include "onpc.h"
#include "oNpcMessages.h"
#include "oobjfactory.h"
#include "obinkplayer.h"
#include "osysinfo.h"
#include <oIncDialogs.h>
#include "oInfo.h"
#include "oinformationmanager.h"
#include "zwin32_resource.h"
#include "oVisFX.h"
#include "ofocus.h"

#ifndef COMPILING_SPACER
	// #define _PROTECTCD_
#endif

#ifdef GOLDMASTER
//#define PROMO_VERSION
#endif 

#ifdef _PROTECTCD_
	#include <PCDSDK.H>
#endif

#ifdef USENET
	// network
	#include "ngame.h"	
	#include "nmenu_net.h"
 	#include "nmenu_chat.h"
	#include "nmenu_item.h"
	#include "nversion.h"
#endif

#include <CrtDbg.h>
#include <time.h>
#include <zWin32.h>

static bool		s_chapter_introduce = false;
static zSTRING	s_chapter_text1;
static zSTRING	s_chapter_text2;
static zSTRING	s_chapter_sound;
static zSTRING	s_chapter_texname;
static int		s_chapter_waittime;

extern int PROTECTCD_ID;

extern void NotifyInfoToSpy( char* pszMethod, char* pszOutput, char* pszStatus );


static void SetNumLock( BOOL bState )
{
  BYTE keyState[256];

  GetKeyboardState((LPBYTE)&keyState);
  if( (bState && !(keyState[VK_NUMLOCK] & 1)) ||
      (!bState && (keyState[VK_NUMLOCK] & 1)) )
  {
  // Simulate a key press
     keybd_event( VK_NUMLOCK,
                  0x45,
                  KEYEVENTF_EXTENDEDKEY | 0,
                  0 );

  // Simulate a key release
     keybd_event( VK_NUMLOCK,
                  0x45,
                  KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                  0);
  }
}

static void MenuRender()
{
	gameMan->Render();		
};


static void MenuEnter()
{
	
	oCGame *game = 0;

	if (gameMan->IsGameRunning()) game = gameMan->GetGame();				
	else
	{
		gameMan->InsertMenuWorld( zCMenu::GetActive()->GetBackWorld(), zCMenu::GetActive()->GetBackDatFile());	
	}
		
	if (game && gameMan->IsGameRunning()) 
	{
		zinput->ClearKeyBuffer();
		zinput->ResetRepeatKey();

		game->SetEnableHandleEvent(FALSE);
		if (game->GetSelfPlayerVob()) game->GetSelfPlayerVob()->SetMovLock(TRUE);
		
		/*
		if (gameMan -> IsIntroActive()) 
		{
			if (game->GetWorld()) 
			{
				if (game->GetWorld()) game->GetWorld()->GetActiveSkyControler()->SetFarZ(5000);
				//Wld_Timer->SetDay(0);
				//Wld_Timer->SetTime(18,0);
			}
		}
		*/

		zCMenu::SetWorld		((zCWorld*)game->GetWorld());
		zCMenu::SetCamera		(game->GetCamera());
		zCMenu::RegisterFrameCB (MenuRender);

		//
		//	CODECHANGE [ROMAN]
		//
		
		game->CloseView( oCGame::oEGameDialogView::GAME_VIEW_AMBIENT );

		//
		//	CODECHANGE [ROMAN] END
		//
	}
};

static void MenuLeave()
{
	if (!gameMan->IsGameRunning()) 
	{
		gameMan->RemoveMenuWorld();
	}

	oCGame *game = 0;
	if (gameMan->IsGameRunning()) game = gameMan->GetGame();

	if (game && gameMan->IsGameRunning()) 
	{
		zinput->ClearKeyBuffer();		
		zinput->ResetRepeatKey();	

		game->SetEnableHandleEvent(TRUE);

		if (game->GetSelfPlayerVob()) 
		{
			game->GetSelfPlayerVob()->SetMovLock(FALSE);
		}

		zCMenu::SetWorld		((zCWorld*)game->GetWorld());
		zCMenu::SetCamera		(game->GetCamera());
		// zCMenu::RegisterFrameCB (MenuRender);

		//
		//	CODECHANGE [ROMAN]
		//
		
		game->OpenView( oCGame::oEGameDialogView::GAME_VIEW_AMBIENT );

		//
		//	CODECHANGE [ROMAN] END
		//
	}
	else zCMenu::RegisterFrameCB (0);
};


/*************************************************************************/
/** C O N S T R U C T   /   D E S T R U C T  *****************************/
/*************************************************************************/


CGameManagerPtr gameMan = 0;


CGameManager::CGameManager()
{	
	#ifdef USENET
		zERR_MESSAGE(1,0,"B: GMAN: gothic-network protocol-version "+zSTRING(NET_VERSION));
	#endif

	gameMan				= this;	

	gameSession			= 0;
	backLoop			= 0;
	vidScreen			= 0;
	initScreen			= 0;
	menu_chgkeys		= 0;
	menu_save_savegame	= 0;
	menu_load_savegame	= 0;
	exitGame			= FALSE;
	exitSession			= FALSE;
	gameIdle			= TRUE;  // menu stops game by default
	lastWorldWasGame	= FALSE;
	introActive			= FALSE;	
	dontStartGame		= FALSE;
	savegameManager		= 0;
	videoPlayer			= zNEW(oCBinkPlayer);
	videoPlayInGame		= 0;

	backWorldRunning.Clear(); 
	backDatFileRunning.Clear();	

	playTime			= 0;
};

static time_t playTimeStart;
static time_t playTimeEnd;

CGameManager::~CGameManager()
{
	if (gameSession) zERR_WARNING("B: GMAN: gameSession is existing. Call CGameManager::Done() before!");		

	if (videoPlayInGame)
	{
		videoPlayer->PlayDeinit();
		videoPlayer->CloseVideo();
	};
	delete videoPlayer; videoPlayer	= 0;
	delete gameSession;	gameSession = 0;
	delete backLoop;	backLoop	= 0;
	delete initScreen;	initScreen	= 0;
	
	lastDatFileList.EmptyList();
	lastWorldList.EmptyList();

	gameMan = 0;
};



/*************************************************************************/
/** I N I T **************************************************************/
/*************************************************************************/

static void PruefeVerfallsdatum(void)
{
#ifndef _DEBUG
	// Verfallsdatum f�r EXE hier!
	//
	// Falls  2. EXE �lter als 1,5 Tage (Systemdatum)
	//        1. Version hei�t "...pre"
	//   Schreie laut auf!
#ifndef PROMO_VERSION
	if (zSTRING(APP_NAME).Search("pre") != -1)
#else
		int WARNPromo_Version=0;
#endif
		// Version ist eine pre
	{
		zFILE_FILE   gothicexe;
		zFILE_STATS  gothicexestats;

		if ((gothicexe.Exists("..\\System\\Gothic2.exe") && gothicexe.Open("..\\System\\Gothic2.exe",FALSE) == zERR_NONE) ||
			(gothicexe.Exists("..\\..\\System\\Gothic2.exe") && gothicexe.Open("..\\..\\System\\Gothic2.exe",FALSE) == zERR_NONE))

		{
			gothicexe.Close();
			
			if (gothicexe.GetStats(gothicexestats) == zERR_NONE)
			{
				if (time(NULL) - (gothicexestats.modifyDate).ToTime_t() > 3600*36)
				{ zERR_FAULT(" Diese Version ist VERALTET und keine Release-Version!! "); }
				else
				{ zERR_MESSAGE(8,0,"M: Version is a valid prerelease."); }
			}
			else
			{
				zERR_WARNING("M: GetStats of Gothic2.exe failed.");
			}
		}
		else
		{
			zERR_WARNING("M: Could not open Gothic2.exe.");
		}
	}
#ifndef PROMO_VERSION

	else
	{
		zERR_MESSAGE(8,0,"M: Version is a release.");
	}	
#endif
#endif
}


void CGameManager::Tool_ConvertData()
{
	zERR_MESSAGE(1,zERR_BEGIN,"B: Converting all data ...");
			
	zCScanDir dirScanner;
	
	zCModelConvertFileHandler		modelConvert;
	zCMorphMeshConvertFileHandler	morphMeshConvert;
	zCProgMeshConvertFileHandler	pmeshConvert;
	zCTextureFileHandler			textureConvert;

	//dirScanner.RegisterFileHandler (&textureConvert,	"zCTexture");
	dirScanner.RegisterFileHandler (&modelConvert,		"zCModel");
	dirScanner.RegisterFileHandler (&morphMeshConvert,	"zCMorphMesh");
	dirScanner.RegisterFileHandler (&pmeshConvert,		"zCProgMeshProto");
	
	dirScanner.Scan(zoptions->GetDirString(DIR_DATA));
			
	zERR_MESSAGE(1,zERR_END,"B: finished");
};

void CGameManager::Init(zTSystemContextHandle& handle)
{		
	sysContextHandle = handle;

	zERR_MESSAGE(3,zERR_BEGIN,"B: GMAN: Initialize GameManager");		

	delete vidScreen;	vidScreen=0;
	delete gameSession;	gameSession=0;

#ifdef PROMO_VERSION
	PruefeVerfallsdatum();
#endif
	//
	// Initialisiere grundlegende Game-Module etc.
	//
	zERR_MESSAGE(6,0,"B: GMAN: Initializing the game");

	sysEvent();

	GameInit();	

	sysEvent();

	// �berpr�fe, ob etwas anderes als ein Gamestart gewuenscht ist:
	if (zoptions->Parm("ZCONVERTALL"))
	{	
		Tool_ConvertData();
	}
	
	//
	// Beruecksichtige Einstellungen in den Settings
	//

	zoptions->InsertChangeHandler(zOPT_SEC_SOUND,	"musicEnabled",		ChangeMusicEnabled);

	// SFX und Music-Volume
	zREAL volume;
	
	volume = zoptions->ReadReal(zOPT_SEC_SOUND,ZOPT_SND_SFX_VOL,1.0f);
	if (zsound) zsound->SetMasterVolume	(volume);	

	volume = zoptions->ReadReal(zOPT_SEC_SOUND,ZOPT_SND_MUSIC_VOL,0.8f);
	if (zmusic) zmusic->SetVolume		(volume);

	savegameManager = zNEW(oCSavegameManager);
	savegameManager->Reinit();
	
	//
	// Initializing Menu-System
	//

	sysEvent();

	zERR_MESSAGE(6,0,"B: GMAN: Initializing the menu-system");
	zCMenu::CreateParser();	
	DefineMenuScriptFunctions();		

	///
	// Option-Variablen schreiben (Defaultwerte beruecksichtigen)
	///

	zoptions->ReadBool(zOPT_SEC_INTERNAL,	"extendedMenu",		0);

	zoptions->ReadInt	(zOPT_SEC_PERFORMANCE,	"sightValue",		4); // 4 is default (100%)
	zoptions->ReadReal	(zOPT_SEC_PERFORMANCE,	"modelDetail",		0.5f); // hohes Detailreichtum	
	
	zoptions->ReadReal	(zOPT_SEC_INTERNAL,		"texDetailIndex",	0.6f); // maximale Detailstufe	

	zoptions->ReadInt	(zOPT_SEC_GAME,			"skyEffects",		1); // Skyeffects active	
	zoptions->ReadInt	(zOPT_SEC_GAME,			"bloodDetail",		2);

	zoptions->ReadReal	(zOPT_SEC_VIDEO,		"zVidBrightness",	0.5f);		
	zoptions->ReadReal	(zOPT_SEC_VIDEO,		"zVidContrast",		0.5f);		
	zoptions->ReadReal	(zOPT_SEC_VIDEO,		"zVidGamma",		0.5f);		
	
	//
	// Programm Parameter auslesen
	//
	zERR_MESSAGE(6,0,"B: GMAN: Analysing commandline-parameters");
	zSTRING value;
	if (zoptions->Parm("PLAYER"))
	{
		value = zoptions->ParmValue("PLAYER");
		// [BENDLIN] AddonMOD
		if (zgameoptions)
			zgameoptions->WriteString(zOPT_SEC_SETTINGS, "Player", value, TRUE);
		else
			zoptions->WriteString(zOPT_SEC_INTERNAL, "playerInstanceName", value, TRUE);
	};
	
	sysEvent();

	SetEnableHandleEvent(TRUE);

	GameSessionInit();
	
	sysEvent();

	zCMenu::Startup();

	zERR_MESSAGE(3,zERR_END,"");
};


/*************************************************************************/
/** D O N E **************************************************************/
/*************************************************************************/


/* ----------------------------------------------------------------------
	
    emergency_exit()	

	22.09.2000	[Moos]	
                erzeugt; quick-exit-routine f�r die Demo

   ---------------------------------------------------------------------- */

void emergency_exit(){
    zsound = NULL; // [Moos] Sonst: Crash, wenn das Soundsystem weg ist, aber noch sounds gel�scht werden...


    OSVERSIONINFO OSV;
    zSTRING sVer;
    zSTRING sBuild;
	zBOOL noFastExit = FALSE;

    OSV.dwOSVersionInfoSize = sizeof(OSV);
    if (GetVersionEx(&OSV) == 1)
	{
        //platformId contains a value representing the OS
        switch(OSV.dwPlatformId)
		{
        case VER_PLATFORM_WIN32_WINDOWS:		// win98/95/me am start -> kein fast exit (macht probleme)
			noFastExit = TRUE;
		}
	}

	if (noFastExit)
	{
		zDieter_ShutDown();
		zCarsten_ShutDown();
	}
	else
	{
		zDieter_ShutDown_Fast();    
		//zCarsten_ShutDown_Fast();
	}

    exit(0);
}

void CGameManager::Done()
{			
	if (dontStartGame) return;
	
	zERR_MESSAGE(3,0,"B: GOTHIC: Exiting game ...");

    zCCacheBase::S_ClearCaches(); // [Moos] beseitige die Visuals aller NPCs und so...
	
	sysKillWindowsKeys(false);

	if (!zoptions->Parm("ZNOFASTEXIT"))
        emergency_exit(); // [Moos] kleiner exit-hack
 	
	GameSessionDone();
	GameDone();

	delete savegameManager;
	savegameManager=0;
};

zBOOL CGameManager::ExitGame()
{
	exitGame=TRUE;
	return TRUE;
};

zBOOL CGameManager::ExitSession()
{
	exitSession = TRUE;
	if (gameSession)
	{
		if (gameSession->IsPaused())
			gameSession->Unpause();
		gameSession->Pause(TRUE);
		//if (oCNpc::player) oCNpc::player->SetFocusVob(0);
		gameSession->SetShowPlayerStatus(FALSE);
	}
	return TRUE;
};

/*************************************************************************/
/** R U N ****************************************************************/
/*************************************************************************/

/* ----------------------------------------------------------------------
	
    CGameManager::Run()	

	31.08.2000	[Moos]	
                Menu aufger�umt

   ---------------------------------------------------------------------- */


const zSTRING MENU_SAVEGAME_SAVE = "MENU_SAVEGAME_SAVE";
const zSTRING MENU_SAVEGAME_LOAD = "MENU_SAVEGAME_LOAD";

void CGameManager::Run()
{			
	if (dontStartGame) return;	

	ShowIntro();
		
	exitGame = FALSE;
	exitSession = FALSE;

	// Init Menue
	menu_chgkeys		= zNEW(oCMenu_ChgKeys(zSTRING(MENU_CHG_KEYS)));
	menu_chgkeys_ext	= zNEW(oCMenu_ChgKeys(zSTRING(MENU_CHG_KEYS_EXT)));

	menu_save_savegame	= zNEW(oCMenuSavegame(zSTRING(MENU_SAVEGAME_SAVE),oCMenuSavegame::SAVE));
	menu_load_savegame	= zNEW(oCMenuSavegame(zSTRING(MENU_SAVEGAME_LOAD),oCMenuSavegame::LOAD));
	if (menu_save_savegame) menu_save_savegame->SetSavegameManager(savegameManager);
	if (menu_load_savegame) menu_load_savegame->SetSavegameManager(savegameManager);	
	
	// Outgame-Menue

	InitScreen_Menu();

	zoptions->WriteBool(zOPT_SEC_INTERNAL,"gameStartFailed",FALSE);
	zSTRING inivalue = zoptions->ParmValue("ini");
	if  (inivalue.IsEmpty())
		inivalue = "Gothic.ini";
	zoptions->Save(inivalue);
	
	while (!exitGame && !IsGameRunning())
	{
		zCMenu::SetIsInGame(FALSE);
		Menu(FALSE);
		zCMenu::SetIsInGame(TRUE);		
	};

#ifdef COMPILING_SPACER	
	gameSession->LoadGame(SAVEGAME_SLOT_NEW, "");	
#endif
		
	zBOOL saveGame = FALSE;

	InitScreen_Close();

	if (!exitGame)
	{
		// Ingame-Rendering
		do
		{
			if (exitSession)
			{
				// FIXME: eine andere M�glichkeit als die
				// aktuelle IsGameRunning() Implementation,
				// damit nicht die Session nicht freigegeben
				// werden muss!!! (sonst geht Men� wieder zu)
/*
				if (gameSession)
				{
					GameSessionReset();
					GameSessionDone();
					GameSessionInit();
				}
*/
				InitScreen_Open();
				vidScreen->SetEnableHandleEvent(TRUE);
				InitScreen_Menu();
				while (!exitGame && exitSession)
				{
					zCMenu::SetIsInGame(FALSE);
					Menu(FALSE);
					zCMenu::SetIsInGame(TRUE);		
				};
				InitScreen_Close();

				exitSession = FALSE;
			}
			else
			{
				sysEvent();			

				zCView::GetInput();

#ifdef COMPILING_SPACER
				if (zinput->KeyPressed(KEY_ESC))
					exitGame = TRUE;
#endif
				
				Render(TRUE);
				
				if (s_chapter_introduce && MenuEnabled(saveGame) && saveGame)
				{
					IntroduceChapter();
				}
			}
		}
		while (!exitGame);	
	}

	// Game exited

	ShowExtro();	

    delete menu_chgkeys; 		menu_chgkeys		= 0;
	delete menu_chgkeys_ext; 	menu_chgkeys_ext	= 0;
	delete menu_save_savegame; 	menu_save_savegame	= 0;
	delete menu_load_savegame; 	menu_load_savegame	= 0;
}

/*************************************************************************/
/** G A M E **************************************************************/
/*************************************************************************/

void ExitGameFunc()
{	
	gameMan->Done();
	delete gameMan;	
	gameMan=0;
	sysExit();
}

zCEngine *zengine=0;




void CGameManager::InitScreen_Open()
{
	#ifdef COMPILING_SPACER
	return;
	#endif

	zERR_MESSAGE(4,0,"B: GMAN: Open InitScreen");
	if (initScreen) InitScreen_Close();
		
	// Hintergrundgrafik ermitteln und einbauen
	zSTRING backPic="";

	initScreen	=  zNEW( zCView(0,0,8192,8192) );			
	
	zoptions	->ChangeDir(DIR_TEX_DESKTOP);
	screen		->InsertItem (initScreen);		
	initScreen	->InsertBack("startscreen.tga");					

	zrenderer	->BeginFrame();
	screen		->Render();
	zrenderer	->EndFrame();
	zrenderer	->Vid_Blit();
};


void CGameManager::InitScreen_Menu()
{
	#ifdef COMPILING_SPACER
	return;
	#endif	

	zERR_MESSAGE(4,0,"B: GMAN: MenuScreen");

	// zoptions		-> ChangeDir(DIR_TEX_DESKTOP);
	// initScreen	-> InsertBack("loading.tga");					

	zrenderer	->BeginFrame();
	screen		->Render();
	zrenderer	->EndFrame();
	zrenderer	->Vid_Blit();
};

void CGameManager::InitScreen_Close()
{
	zERR_MESSAGE(4,0,"B: GMAN: Close InitScreen");

	#ifdef COMPILING_SPACER
	return;
	#endif

	if (initScreen) delete initScreen;
	initScreen = 0;	
};





void CGameManager::InitSettings()
{	
	zerr.Separator();
	oCSystemInfo sysInfo;	
	// Copmputer analysieren
	sysInfo.AnalyseNow();				// => Analysieren
	zerr.Separator();
	// SystemInfos bewerten
	sysInfo.SetCpuSpecs		(700,1200);	//
	sysInfo.SetMemorySpecs	( 256,512);	//
	sysInfo.SetGraphicsSpecs(  16, 64);	// restlicher Grafikkartenspeicher allein fuer Texturen
	sysInfo.ScoreNow();					// => Bewerten
	zerr.Separator();
	// Einstellungen �ndern	
	sysInfo.ResetSettings();

	zerr.Separator();
};

///////////////////////////////////////////////////////
// SPLASH-Screen
///////////////////////////////////////////////////////

static HWND		hSplashWnd		 = NULL;
static HBITMAP	hSplashBitmap    = NULL;
static INT		SplashBitmapX    = 502;
static INT		SplashBitmapY    = 202;
static DWORD	SplashThreadID   = 0;
HANDLE			hSplashThread    = 0;
HINSTANCE		hSplashInstance	 = 0;

extern HINSTANCE hInstApp;

BOOL CALLBACK SplashDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( uMsg==WM_DESTROY )
	{
		PostQuitMessage(0);
	}
	return 0;
}

DWORD WINAPI SplashThreadProc( VOID* Parm )
{
	hSplashWnd = CreateDialog(hSplashInstance, MAKEINTRESOURCEA(IDD_SPLASH), NULL, SplashDialogProc);
	if( hSplashWnd )
	{
		HWND hWndLogo = GetDlgItem(hSplashWnd,IDC_SPLASH_DISPLAY);
		if( hWndLogo )
		{
			SetWindowPos(hSplashWnd,HWND_TOPMOST,(GetSystemMetrics(SM_CXSCREEN)-SplashBitmapX)/2,(GetSystemMetrics(SM_CYSCREEN)-SplashBitmapY)/2,SplashBitmapX,SplashBitmapY,SWP_SHOWWINDOW);
			SetWindowPos(hSplashWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			SendMessage( hWndLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hSplashBitmap );
			UpdateWindow( hSplashWnd );
			MSG Msg;
			while( GetMessage(&Msg,NULL,0,0) )
			{
				DispatchMessage(&Msg);
			}
		}
	}
	return 0;
}

void CGameManager::ShowSplashScreen()
{
	//SplashBitmapX = 460;
	//SplashBitmapY = 208;
	hSplashBitmap = ::LoadBitmap(hInstApp,MAKEINTRESOURCEA(IDB_SPLASH));
	hSplashThread=CreateThread(NULL,0,&SplashThreadProc,NULL,0,&SplashThreadID);
};

void CGameManager::RemoveSplashScreen()
{
	if( SplashThreadID )
	{
		PostThreadMessageA(SplashThreadID,WM_QUIT,0,0);
	}
};

void CGameManager::GameInit()
{			
	zerr.SetExitFunction(ExitGameFunc);				

	ShowSplashScreen();

#ifdef COMPILING_SPACER
	SetNumLock(FALSE);
#endif
		
	if (!zengine) zengine= zNEW(zCEngine);
	zengine->Init(&sysContextHandle);

	RemoveSplashScreen();

	//
	// Videos spielen
	//

#ifndef COMPILING_SPACER
	// patch 1.07: "playLogoVideos" eingefuehrt
	zBOOL playVideos = zoptions->ReadBool(zOPT_SEC_GAME,"playLogoVideos",TRUE);
	if (playVideos)
	{
		this->PlayVideo("logo1.bik");
		this->PlayVideo("logo2.bik");
	}
#endif

	sysEvent();
	
	//
	// Soll das Spiel resettet werden?
	//	

	zBOOL reset = TRUE;
	reset = zoptions->ReadBool(zOPT_SEC_PERFORMANCE,"recalc",TRUE);	
	zoptions->WriteBool(zOPT_SEC_PERFORMANCE,"recalc",FALSE);		
	if (reset) 
	{
		InitSettings();			
	}	
	
	InitScreen_Open();
	
	zRELEASE(zfactory);
	zfactory = zNEW(oCObjectFactory);

	oBert_StartUp();
				
	// input: Keyboard, Mouse, Joystick
	vidScreen = screen;	
	vidScreen->SetEnableHandleEvent(TRUE);

	sysEvent();

	oCarsten_StartUp();
	zCMenu::RegisterEnterCB(MenuEnter);
	zCMenu::RegisterLeaveCB(MenuLeave);
}



void CGameManager::Render(zBOOL blit)
{	
	if (backLoop)
	{
		backLoop->Render();
		if (blit) backLoop->RenderBlit();
		return;
	}

	oCGame* game = GetGame();
	if (game && IsGameRunning())
	{		
		game->Render();
		if (blit) game->RenderBlit();
	}	
};

void CGameManager::GameDone()
{	
	oCarsten_ShutDown();
	zengine->Shutdown();
	delete zengine; zengine=0;
};



/*************************************************************************/
/** G A M E S E SS I O N *************************************************/
/*************************************************************************/


void CGameManager::GameSessionReset()
{
	if (!gameSession) zERR_FATAL("B: GameMan: Call GameSessionInit before GameSessionReset() ");
	
	savegameManager->ClearCurrent();
	gameSession->SetGameInfo(0);	
};

void CGameManager::GameSessionInit()
{
	if (gameSession) zERR_FATAL("B: GameMan: Call GameSessionInit once, not twice!");

	ogame = gameSession = zNEW(oCGame);	
	gameSession->Init();
	gameSession->SetSavegameManager(savegameManager);
	gameSession->SetGameInfo(0);
};

void CGameManager::GameSessionDone()
{
	if (!gameSession) zERR_FATAL("B: GameMan: Call GameSessionInit before GameSessionDone");

	gameSession->Done();
	delete gameSession;
	ogame = gameSession = 0;
};



/*************************************************************************/
/** I N T R O  / E X T R O ***********************************************/
/*************************************************************************/



void CGameManager::ShowIntro()
{
};


void CGameManager::ShowExtro()
{
};


/*************************************************************************/
/** I N T R O  / E X T R O ***********************************************/
/*************************************************************************/



void CGameManager::PreMenu()
{			
	zoptions->SetFlag(zOPT_SEC_VIDEO,ZOPT_VID_RES.ToChar(),ENTRY_DONT_SAVE);

	// Aktuell eingestellte Aufl�sung auslesen
	int x	= zoptions->ReadInt	(zOPT_SEC_VIDEO, "zVidResFullscreenX"	, 800);		// [BENDLIN] 800x600, old = 640
	int y	= zoptions->ReadInt	(zOPT_SEC_VIDEO, "zVidResFullscreenY"	, 600);		// [BENDLIN] 800x600, old = 480
	int bpp	= zoptions->ReadInt	(zOPT_SEC_VIDEO, "zVidResFullscreenBPP"	, 16);		// [BENDLIN] 800x600, old = 16

	// entsprechenden Videomode suchen
	zTRnd_DeviceInfo  devInfo;
	zTRnd_VidModeInfo modeInfo;
	
	int optionNr = -1;
	int secureNr = -1;
	int count	 = 0;
	for (int modeEnum=0; modeEnum<zrenderer->Vid_GetNumModes(); modeEnum++) F
	{
		zrenderer->Vid_GetModeInfo(modeInfo,modeFEnum);			
		if (VidIsResolutionValid(modeInfo.xdim, modeInfo.ydim, modeInfo.bpp))
		{
			if (x==modeInfo.xdim && y==modeInfo.ydim && bpp==modeInfo.bpp)
			{
				optionNr = count;
				zERR_MESSAGE(3,0,"B: VID: Videomode found");
			}			
			if (modeInfo.xdim==800 && modeInfo.ydim==600 && modeInfo.bpp==16)		// [BENDLIN] 800x600, old = 640x480x16
			{
				zERR_MESSAGE(3,0,"B: VID: Secure videomode found: 800x600x16");		// [BENDLIN] 800x600, old = 640x480x16
				secureNr = count;
			}			
			count++;
		}
	}

	zERR_ASSERTT(secureNr>=0,"B: VID: No standard-videomode (800x600x16) found");	// [BENDLIN] 800x600, old = 640x480x16

	// Aufloseung gefunden?
	if (optionNr<0) 
	{
		optionNr = secureNr;
		x = 800; y = 600; bpp = 16;													// [BENDLIN] 800x600, old = 600x480x16
		zoptions->WriteInt	(zOPT_SEC_VIDEO, "zVidResFullscreenX"	, x);
		zoptions->WriteInt	(zOPT_SEC_VIDEO, "zVidResFullscreenY"	, y);
		zoptions->WriteInt	(zOPT_SEC_VIDEO, "zVidResFullscreenBPP"	, bpp);
	};

	zoptions->WriteInt(zOPT_SEC_INTERNAL,ZOPT_VID_RES.ToChar(),optionNr);
	
	// Welche Texture-Details
	int size = zoptions->ReadInt(zOPT_SEC_VIDEO, "zTexMaxSize", 256);
	float gameTextureDetail = 0.6f;
	if (size<=32)		gameTextureDetail = 0.10f;
	else if (size<= 64)	gameTextureDetail = 0.20f;
	else if (size<=128)	gameTextureDetail = 0.40f;
	else if (size<=256)	gameTextureDetail = 0.60f;
	else if (size<=512)	gameTextureDetail = 0.80f;
	else				gameTextureDetail = 1.0f;	
	zoptions->WriteReal(zOPT_SEC_INTERNAL,"texDetailIndex",gameTextureDetail);

	// Mouse
	zBOOL eleEnabled = zoptions->ReadBool(zOPT_SEC_GAME,"enableMouse",TRUE);
	zREAL eleSense	 = zoptions->ReadReal(zOPT_SEC_GAME,"mouseSensitivity",0.5f);
	zinput->SetDeviceEnabled(zINPUT_MOUSE,eleEnabled);
	eleSense = eleSense*0.5f + 0.3f;
	zinput->SetMouseSensitivity(eleSense,eleSense);

	// [BENDLIN] Joystick
	zBOOL joyEnabled = zoptions->ReadBool(zOPT_SEC_GAME, "enableJoystick", FALSE);
	zinput->SetDeviceEnabled(zINPUT_JOYSTICK1, joyEnabled);
};


void CGameManager::PostMenu(zSTRING action)
{
	// Einstellungen vornehmen
	ApplySomeSettings();
	if (gameSession) gameSession->UpdateScreenResolution();	

	zinput->ProcessInputEvents();	
	zinput->ClearKeyBuffer();
	zinput->ResetRepeatKey();
};

void CGameManager::ApplySomeSettings()
{
	//
	// Einstellungen auslesen und dem Spiel uebergeben
	//

	zERR_MESSAGE(3,zERR_BEGIN,"B: OPT: Applying settings ...");
	zBOOL bak = zoptions->SetReadTemp(FALSE); // fuer NEEDS_APPLY-Options

		// ::Apply_Options_Video();	

		zoptions->ReadBool(zOPT_SEC_INTERNAL,	"extendedMenu",		0);
		
		zREAL	gameTextureDetail	= zoptions->ReadReal(zOPT_SEC_INTERNAL,	"texDetailIndex",	1.0f);		

 		int		gameSightSetting	= zoptions->ReadInt (zOPT_SEC_PERFORMANCE, "sightValue",	4); // 4 is default (100%)		
		zREAL	gameModelDetail		= zoptions->ReadReal(zOPT_SEC_PERFORMANCE, "modelDetail",	0.5f);		

		
		int		gameSkyEffects		= zoptions->ReadInt (zOPT_SEC_GAME,  "skyEffects",	1);
		int		gameBloodDetail		= zoptions->ReadInt (zOPT_SEC_GAME,  "bloodDetail",	2);

		zREAL	vidBrightness		= zoptions->ReadReal(zOPT_SEC_VIDEO, "zVidBrightness",		0.5f);		
		zREAL	vidContrast			= zoptions->ReadReal(zOPT_SEC_VIDEO, "zVidContrast",		0.5f);		
		zREAL	vidGamma			= zoptions->ReadReal(zOPT_SEC_VIDEO, "zVidGamma",			0.5f);		

		zREAL	sndSoundVol			= zoptions->ReadReal(zOPT_SEC_SOUND, ZOPT_SND_SFX_VOL,		1.0f);
		zREAL	sndMusicVol			= zoptions->ReadReal(zOPT_SEC_SOUND, ZOPT_SND_MUSIC_VOL,	0.8f);
		
		zBOOL	inverse				= zoptions->ReadBool(zOPT_SEC_GAME, "camLookaroundInverse",	FALSE);
		zBOOL	eleEnabled			= zoptions->ReadBool(zOPT_SEC_GAME, "enableMouse",		TRUE);
		zREAL	eleSense			= zoptions->ReadReal(zOPT_SEC_GAME, "mouseSensitivity",	0.5f);

		zREAL   vobSightSetting		= zoptions->ReadReal("ENGINE"		 , "zVobFarClipZScale", 4);
		zBOOL	waterAniEnabled		= zoptions->ReadBool("ENGINE"		 , "zWaterAniEnabled",  TRUE);
		zBOOL	envMapEnabled		= zoptions->ReadBool("ENGINE"		 , "zEnvMappingEnabled",TRUE);
		zBOOL	farFadeEnabled		= zoptions->ReadBool("ENGINE"		 , "zFarClipAlphaFade", TRUE);
		zBOOL	windEnabled			= zoptions->ReadBool("ENGINE"		 , "zWindEnabled"	  , TRUE);
		zBOOL	ambientVobsEnabled  = zoptions->ReadBool("ENGINE"		 , "zAmbientVobsEnabled" , TRUE);
		zBOOL	ambientPFXEnabled   = zoptions->ReadBool("ENGINE"		 , "zAmbientPFXEnabled" , TRUE);
		zBOOL	gothic1OldControls  = zoptions->ReadBool("GAME"			 , "useGothic1Controls" , TRUE);
		zBOOL   radialFog			= zoptions->ReadBool("RENDERER_D3D"	 , "zFogRadial", TRUE);
		zREAL	cloudShadow			= zoptions->ReadReal("ENGINE"		 , "zCloudShadowScale", 0.0f);
		zREAL   speechRevLevel		= zoptions->ReadReal("GAME"			 , "useSpeechReverbLevel", 1);
		int	    meleeFocusLevel		= zoptions->ReadInt ("GAME"			 , "highlightMeleeFocus");
		zBOOL   interactFocus       = zoptions->ReadBool("GAME", "highlightInteractFocus");
		
		// Camera-Lookaround				
		zCAICamera::SetLookaroundInverse(inverse);
		zERR_MESSAGE(3,0,"B: OPT: Lookaround inverse = "+zSTRING(inverse));

		// Sound (patch 1.07: Provider, Speekertype etc. eingefuehrt)
		
		//SOUND-OPTIONS  
		int		sndProviderIndex	= zoptions->ReadInt(zOPT_SEC_INTERNAL,	"soundProviderIndex",	FALSE);
		int		sndSpeakerType		= zoptions->ReadInt(zOPT_SEC_INTERNAL,	"soundSpeakerIndex",	FALSE);
		
		zsound->SetProvider			(sndProviderIndex);
		zsound->SetSpeakerType		(zCSoundSystem::zTSpeakerType(sndSpeakerType));
		

		zERR_MESSAGE(3,0,"B: OPT: Music-Volume: Value="+zSTRING(sndMusicVol));
		zERR_MESSAGE(3,0,"B: OPT: Sound-Volume: Value="+zSTRING(sndSoundVol));			

		// Mouse
		zinput->SetDeviceEnabled(zINPUT_MOUSE,eleEnabled);
		eleSense = eleSense*0.5f + 0.3f;
		zinput->SetMouseSensitivity(eleSense,eleSense);
		zERR_MESSAGE(3,0,"B: OPT: Mouse-Enabled = "+zSTRING(eleEnabled));
		zERR_MESSAGE(3,0,"B: OPT: Mouse-Sensitivity = "+zSTRING(eleSense));

		if (gameSession) 
		{		
			// Sight
			gameSightSetting=(gameSightSetting+1)*20;
			gameSightSetting = zMax(gameSightSetting,20);
			gameSightSetting = zMin(gameSightSetting,300); // (0=20%, 4=100%, 14=300%)			
			zREAL gameSightFactor = gameSightSetting/100.0f;
			gameSession->GetWorld()->GetActiveSkyControler()->SetFarZScalability(gameSightFactor);	// von 0-1 auf 0.2 skalieren				
			zERR_MESSAGE(3,0,"B: OPT: Level-Sight: Value="+zSTRING(gameSightSetting)+", resulting factor="+zSTRING(gameSightFactor));

			gameSession->GetWorld()->SetVobFarClipZScalability(zLerp(vobSightSetting/14.0f, 0.4f, 3.5f));
			zERR_MESSAGE(3,0,"B: OPT: Vob-Sight: Value="+zSTRING(vobSightSetting));

			zCParticleFX::S_SetAmbientPFXEnabled( ambientPFXEnabled );
			zCWorld::S_SetAmbientVobsEnabled	( ambientVobsEnabled );
			zCWorld::S_SetEnvMappingEnabled		( envMapEnabled );
			zCWorld::SetWaveAnisEnabled			( waterAniEnabled );
			zCVob::SetAnimationsEnabled         ( windEnabled );
			zCWorld::SetFadeOutFarVertices      ( farFadeEnabled);
			oCGame::SetUseOldControls			( gothic1OldControls);
			if (zrenderer) zrenderer->SetRadialFog(radialFog);
			if (zCSkyControler::GetActiveSkyControler()) zCSkyControler::GetActiveSkyControler()->SetCloudShadowScale(cloudShadow?1.0f:0);
			oCGame::SetUseSpeechReverbLevel(speechRevLevel);
			oCNpcFocus::SetHighlightMeleeFocus	 (meleeFocusLevel);
			oCNpcFocus::SetHighlightInteractFocus(interactFocus);

			// Wettereffekte						
			zCSkyControler::SetSkyEffectsEnabled(gameSkyEffects==1);
			zERR_MESSAGE(3,0,"B: OPT: Sky: Value="+zSTRING(gameSkyEffects));
			
			// Textur-Detail
			int oldValue = zoptions->ReadInt(zOPT_SEC_VIDEO,"zTexMaxSize",-1);
			int size=1024*16;
			zClamp(gameTextureDetail,0.0f,1.0f);
			if		(gameTextureDetail>=0.95)	size=1024*16;	// 1.0 =  oo
			else if (gameTextureDetail>=0.75)	size=512;		// 0.8 = 512 Pixel
			else if (gameTextureDetail>=0.55)	size=256;		// 0.6 = 256 Pixel
			else if (gameTextureDetail>=0.35)	size=128;		// 0.4 = 128 Pixel
			else if (gameTextureDetail>0.15)	size=64;		// 0.2 =  64 Pixel
			else								size=32;		// 0.0 =  32 Pixel
						
			if (oldValue != size)
			{			
				zCTexture::RefreshTexMaxSize(size);
				if (zresMan) zresMan->PurgeCaches(zCTexture::GetStaticClassDef());
				zERR_MESSAGE(3,0,"B: OPT: TextureDetails: Value="+zSTRING(gameTextureDetail)+", resulting size = "+zSTRING(size));
			}						

			// Model-Detail			
			zClamp(gameModelDetail,0.0f,1.0f);
			zCProgMeshProto::SetLODParamStrengthModifier	(gameModelDetail);
			zERR_MESSAGE(3,0,"B: OPT: Model-Details: Value="+zSTRING(gameModelDetail));
			
			// Blood-Detail
			zClamp(gameBloodDetail,0,3);
			if (gameBloodDetail==0) oCNpc::SetBloodMode(oCNpc::oEBloodMode_None);
			if (gameBloodDetail==1) oCNpc::SetBloodMode(oCNpc::oEBloodMode_Particles);
			if (gameBloodDetail==2) oCNpc::SetBloodMode(oCNpc::oEBloodMode_Decals);
			if (gameBloodDetail>=3) oCNpc::SetBloodMode(oCNpc::oEBloodMode_Trails);
			zERR_MESSAGE(3,0,"B: OPT: Blood-Details: Value="+zSTRING(gameBloodDetail));
			
			// Textfenster
			zBOOL viewWindows = zoptions->ReadBool(zOPT_SEC_GAME, "subTitles", FALSE);
			// [BENDLIN] AddonMOD
			if (zgameoptions)
			if (zgameoptions->ReadBool(zOPT_SEC_OPTIONS, "force_Subtitles", FALSE))
				viewWindows = TRUE;

			oCNpc::EnableTalkBox(viewWindows);
			zBOOL viewWindowsPlayer = zoptions->ReadBool(zOPT_SEC_GAME, "subTitlesPlayer", TRUE);
			oCNpc::EnableTalkBoxPlayer(viewWindowsPlayer);
			zBOOL viewWindowsAmbient = zoptions->ReadBool(zOPT_SEC_GAME,"subTitlesAmbient", TRUE);
			oCNpc::EnableTalkBoxAmbient(viewWindowsAmbient);
			zBOOL viewWindowsNoise = zoptions->ReadBool(zOPT_SEC_GAME, "subTitlesNoise", FALSE);
			oCNpc::EnableTalkBoxNoise(viewWindowsNoise);

			// Textfenster aktualisieren (animationen etc.)
			oCInformationManager::GetInformationManager().UpdateViewSettings();									
			if (ogame) ogame->UpdateViewSettings();
		}
		if (zrenderer)
		{					
			// [EDENFELD] Gothic Patch 1: Kontrast nicht mehr invertiert
			zrenderer->Vid_SetGammaCorrection(vidGamma, vidContrast, vidBrightness);
		};		

	zoptions->SetReadTemp(bak);

	// INI-Datei speichern
	zSTRING inifile = zoptions->ParmValue("ini");
	if  (inifile.IsEmpty())
		inifile = "Gothic.ini";
	zoptions->Save(inifile);

	zERR_MESSAGE(3,zERR_END,"");
};

int CGameManager::GetPlaytimeSeconds()
{
	time(&playTimeEnd);
	playTime += int(fabs(difftime(playTimeEnd,playTimeStart)));
	time(&playTimeStart);	
	return playTime;
}

void CGameManager::Menu(zBOOL saveGame)
{		
	zERR_MESSAGE(3,0,"B: GMAN: Entering Menu-Section");
	zinput->ResetRepeatKey(); // [SPECKELS] Hack, um toggle zu vermeiden

	gameSession->SetShowPlayerStatus(FALSE);

	zSTRING action;
	zoptions->WriteString("internal","menuAction", "RESUME_GAME");
	
	if (exitGame) return;

	zBOOL nomenu = zoptions->Parm("NOMENU");	
	
	PreMenu();		
	
	if (!IsGameRunning()) 	
	//
	// Out-Game-Menue
	//
	{		
		if (nomenu) // kein Menue anzeigen? -> Standardaktion (Neues Game starten)
		{			
			zoptions->WriteString("internal","menuAction","NEW_GAME");
		}
		else
		{
			zERR_MESSAGE(4,0,"B: GMAN: Menu started (outgame)");
			zCMenu *menu = zCMenu::Create(zSTRING("MENU_MAIN"));												
			menu->Run();			
			menu->Release(); 			

			menu=0;			
			zERR_MESSAGE(4,0,"B: GMAN: Menu finished");
		}
	}
	else 
	//
	// In-Game-Menue
	//
	{			
		if (nomenu) // kein Menue anzeigen? -> Exit
		{
			exitGame = TRUE;
			return;
		}
		else
		{
			zERR_MESSAGE(4,0,"B: GMAN: Menu started (ingame)");
			if (gameSession) gameSession->Pause(exitSession);
						
			zBOOL inGame = zCMenu::IsInGame();
			if (!saveGame)	zCMenu::SetIsInGame(FALSE);

			zCMenu *menu = zCMenu::Create(zSTRING("MENU_MAIN"));			
			menu->Run();			
			menu->Release();
			menu=0;			

			zCMenu::SetIsInGame(inGame);

			if (gameSession) gameSession -> Unpause();		
			zERR_MESSAGE(4,0,"B: GMAN: Menu finished");
		}
	}	
	
	if (zrenderer) 
	{
		screen	 ->DrawItems			();		
		zrenderer->Vid_Blit(FALSE);
	}

	//
	// Aktion, die der Benutzer im Menue durchgefuehrt hat, bearbeiten
	//////////////////////////////////////////////////////////////////////

	action = zoptions->ReadString("internal","menuAction");	
	
	//
	// Menueaktion ausf�hren
	//

	zERR_MESSAGE(4,0,"B: MENU: "+action);

	//
	// SPIEL VERLASSEN ****
	//
	if (action == "LEAVE_GAME") 
	{		
		zERR_MESSAGE(4,0,"B: GMAN: Menu-Selection \"exit\"");		
		exitGame = TRUE;		

		// [BENDLIN] 1.30 eigentlich m��te zDeinitOptions aufgerufen werden
		// (emergency_exit ist zum Normalfall geworden - zDeinitOptions gibt aber zoptions frei...)
#ifndef COMPILING_SPACER
		zoptions->WriteBool(zOPT_SEC_INTERNAL, "gameAbnormalExit", FALSE);
#endif
	}
	else

	// 
	// NEUES SPIEL 
	// 
	if (action == "NEW_GAME") 
	{
		// if (zmusic) zmusic->PlayThemeByScript("SYS_LOADING");					

		zSTRING gamePath;
		// [BENDLIN] AddonMOD
		if (zgameoptions)
			gamePath = zgameoptions->ReadString(zOPT_SEC_SETTINGS, "World");
		else
			gamePath = zoptions->ReadString(zOPT_SEC_INTERNAL, "gamePath");
		if (gamePath.IsEmpty())
			gamePath = "NewWorld\\NewWorld.zen";
		zERR_MESSAGE(4, 0, "B: GMAN: Menu-Selection NEW_GAME " + gamePath);
		
		GameSessionReset();
		
		// Wenn Session vorher beendet, Flag zur�cksetzen
		exitSession = FALSE;

		zERR_MESSAGE(1,0,"B: GMAN: Loading the World ...");		
						
		gameSession->LoadGame(SAVEGAME_SLOT_NEW, gamePath);	
						
		if (zmusic) zmusic->Stop();		

		zERR_MESSAGE(1,0,"B: GMAN: Completed loading the world ...");		

		playTime = 0;
		time(&playTimeStart);
	}
	else	

	// 
	// SPIEL LADEN (SAVEGAME)
	// 
	if (action == "SAVEGAME_LOAD") 
	{		
		int slotNr = menu_load_savegame->GetSelectedSlot();
		Read_Savegame(slotNr);
	}

	else

	//
	// SPIEL SPEICHERN (SAVEGAME)	
	//
	if (action == "SAVEGAME_SAVE")  
	{
		int slotNr = menu_save_savegame->GetSelectedSlot();
		Write_Savegame(slotNr);
	}

	else

	//
	// SPIEL FORTFUEHREN
	//
	if (action == "RESUME_GAME") 
	{
		// resume Game		
	}

	else 
	// **** unbekannter Menuebefehl ****
	{ 
		zERR_FATAL("C: oGameManager.cpp(CGameManager::Menu()): Menu Selection not known :" + action );
	}


	// INI-Datei speichern
	zSTRING inifile = zoptions->ParmValue("ini");
	if  (inifile.IsEmpty())
		inifile = "Gothic.ini";
	zoptions->Save(inifile);

	introActive = FALSE;

	PostMenu(action);	

	if (!exitSession) 	
		gameSession->SetShowPlayerStatus(TRUE);

	zinput->ProcessInputEvents();
	zinput->ClearKeyBuffer();		
	zinput->ResetRepeatKey();	

	zERR_MESSAGE(3,0,"B: GMAN: Leaving Menu-Section");
};

void CGameManager::Read_Savegame(int slotNr)
{
	if (slotNr<0) return;
	
	// wenn erstes Load, dann aus INI-File auslesen
	oCSavegameInfo* info = savegameManager->GetSavegame(slotNr);
	if (info && info->IsCompatible() && info->DoesSavegameExist())
	{
		zERR_MESSAGE(4,0,"B: GMAN: Loading game from slot "+zSTRING(slotNr));

		// Wenn Session vorher beendet, Flag zur�cksetzen
		exitSession = FALSE;
		// if (zmusic) zmusic->PlayThemeByScript("SYS_LOADING");	

		GameSessionReset();
		gameSession->LoadSavegame(info->GetSlot(),TRUE);

		if (zmusic) zmusic->Stop();

		playTime = info->GetPlaytimeSeconds();
		time(&playTimeStart);
	}
};

void CGameManager::Write_Savegame(int slotNr)
{
	if (slotNr<0) return;

	//
	// Safegame-Info setzen
	//
	oCSavegameInfo* info = savegameManager->GetSavegame(slotNr);

	if (info->GetName().IsEmpty()) info->SetName("... "+info->GetWorldName());
	zERR_MESSAGE(4,0,"B: GMAN: Saving game to slot "+zSTRING(slotNr));

	info->SetPlaytimeSeconds(GetPlaytimeSeconds());

	int day,hour,min;			
	ogame->GetTime(day,hour,min);			
	info->SetWorldName(static_cast<oCWorld*>(ogame->GetWorld())->GetWorldName());
	info->SetGameTime(day,hour,min);									
		
	// savegame speichern
	zCTextureConvert* texCvt = zrenderer->CreateTextureConvert();
	gameSession->Render					();
	zrenderer->Vid_GetFrontBufferCopy	(*texCvt);
	gameSession->WriteSavegame			(info->GetSlot());
	info->UpdateThumbPic				(texCvt);
	delete texCvt;texCvt=0;

	// Am Ende auch die Savegame-Informationen speichern
	// Dies ist unbedingt nach WriteSavegame noetig, da dieser das Verzeichnis leert.
	savegameManager->SetAndWriteSavegame(slotNr,info);												
};

zBOOL CGameManager::HandleCancelKey(int key)
{
	if (!IsGameRunning() || !gameSession->GetWorld() || !oCNpc::player) return FALSE;
	
	zCCSPlayer* csPlayer = gameSession->GetWorld()->GetCutscenePlayer();

	// Globale Cutscene abbrechen?

	if (csPlayer && csPlayer->GetPlayingGlobalCutscene())
	{							
		zCCSCutsceneContext* cs = csPlayer->GetPlayingGlobalCutscene();
		if (cs->TryToCancel()) 
				zERR_MESSAGE(4,0,"B: CS: User canceled global cutscene");
		else 
				zERR_MESSAGE(4,0,"B: CS: User tried to cancel global cutscene: Not allowed at this moment!");
	
		return TRUE;
	}	
	
	// Outputunits beenden (Talk)
	
	else if (csPlayer && oCNpc::player && oCNpc::player->GetTalkingWith())
	{									
		zERR_MESSAGE(4,zERR_BEGIN,"B: CS: User tried to cancel OutputUnits ...");

		int count=0;
		count += csPlayer->StopAllOutputUnits(oCNpc::player);
		count += csPlayer->StopAllOutputUnits(oCNpc::player->GetTalkingWith());

		oCNpc::player->StopAllVoices();					
		oCNpc::player->GetTalkingWith()->StopAllVoices();

		oCNpc::player->StopFaceAni(NPC_TALK_ANI);
		oCNpc::player->GetTalkingWith()->StopFaceAni(NPC_TALK_ANI);		
		
		zERR_MESSAGE(4,zERR_END,"");		
		
		return count>0;
	};

	return FALSE;
};

zBOOL CGameManager::MenuEnabled(zBOOL& enableSave)
{
	int bodyState = oCNpc::player->GetBodyState();	

	oCNpc* talkPartner = oCNpc::player->GetTalkingWith();
	int stateTalk = parser.GetIndex("ZS_TALK");							
	oCInformationManager& infoMan = oCInformationManager::GetInformationManager();	
				
	// ~BS_FLAG_INTERRUPTABLE
		
	zBOOL enable1		= TRUE;
	zBOOL enable2		= TRUE;
	zBOOL enable3		= TRUE;
	zBOOL enable4		= TRUE;
	zBOOL enableSave1	= TRUE;
	zBOOL enableSave2	= TRUE;
		
	// Globale ununterbrechbare Aktionen
	enable1		=	oCNpc::player 
					&& IsGameRunning()
					&& !gameSession->GetWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene();

	// Bodystate (Bewegungen und Inventory)
	enable2		=	(bodyState != BS_FALL)					 
					&& (bodyState != BS_INVENTORY)
					&& (bodyState != BS_PICKPOCKET);		

	// Talk
	enable3		=	(!talkPartner || (talkPartner->state.GetState() != stateTalk))
					&& (infoMan.HasFinished());

	// [EDENFELD] neu 1.09 aus ModSource �bertragen: npc-mode ber�cksichtigen
	enable4		= 	oCNpc::player 
					&& oCNpc::game_mode==NPC_GAME_NORMAL					
					&& !oCNpc::player->inventory2.IsOpen();

	// Speichern erlauben?	
	enableSave1	=	(bodyState != BS_MOBINTERACT)
					&& (bodyState != BS_MOBINTERACT_INTERRUPT)
					&& (bodyState != BS_SIT)
					&& (bodyState != BS_LIE)					
					&& (bodyState != BS_ITEMINTERACT)
					&& (bodyState != BS_TAKEITEM)
					&& (bodyState != BS_DROPITEM);
					
	enableSave2	=	(bodyState != BS_CASTING)
					&& (!oCNpc::player->HasBodyStateModifier(BS_MOD_CONTROLLED))
					&& (!oCNpc::player->HasBodyStateModifier(BS_MOD_CONTROLLING))
					&& (!oCNpc::player->HasBodyStateModifier(BS_MOD_TRANSFORMED))
					&& (!oCNpc::player->GetHumanAI()->IsDead());
	
	if (!enableSave1)
	{
					
	};
	if (!enableSave2)
	{
	};

	
	zBOOL enable=	enable1 && enable2 && enable3 && enable4;
	enableSave	=	enable &&
					enableSave1 && enableSave2;
		
	return enable;
};

zBOOL CGameManager::HandleEvent(int key)
{
	if (!gameSession) return FALSE;

	zBOOL saveGame	= TRUE;
	zBOOL result	= FALSE;
	switch (key) 
	{					
		case KEY_ESC: 		
			
			if (zinput->KeyPressed(KEY_LSHIFT))
			{	
				Menu(FALSE);
				result=TRUE;
				break; // fertig
			}
			else if (MenuEnabled(saveGame))
			{				
				Menu(saveGame);								
				result=TRUE;				
				break; // fertig
			}			
			// SONST: Das gleiche machen wie bei Mouse-ButtonRight 
			// Deshalb hier kein BREAK!!!

		case MOUSE_BUTTONRIGHT:	// zusaetzlich zu KEY_ESC

			result = HandleCancelKey(key);
			if (result)
			{				
				zinput->ClearKeyBuffer();
				zinput->ResetRepeatKey();
			}				
			break; // fertig
		case KEY_F5:	// Quicksave ( [STRG+F5] im devmode )
			if ( oCGame::GetUseQuickSave() && zinput->KeyToggled(KEY_F5) && GetGame() && IsGameRunning() && (zinput->KeyPressed(KEY_LCTRL) ^ !GetGame()->IsInDevMode()) )
			{
				// [BENDLIN] TODO: Additional checks
				zBOOL saveGame=FALSE;
				MenuEnabled(saveGame);
				if (saveGame)
				{
					gameMan->Write_Savegame(SAVEGAME_SLOT_QUICK);					
					result = TRUE;
				}
			}
			break;
		case KEY_F9:	// Quickload ( [STRG+F9] im devmode )
			if ( oCGame::GetUseQuickSave() && zinput->KeyToggled(KEY_F9) && !GetGame() || (zinput->KeyPressed(KEY_LCTRL) ^ !GetGame()->IsInDevMode()) )
			{
				gameMan->Read_Savegame(SAVEGAME_SLOT_QUICK);
				result = TRUE;
			}
			break;
		default:
			{
				zWORD logicalKey = zinput->GetFirstBindedLogicalKey(key);
				switch (logicalKey)
				{
				case GAME_LAME_POTION:
					if ( oCGame::GetUsePotions() && zinput->KeyToggled(key) && GetGame() && IsGameRunning() && !GetGame()->IsInDevMode() )
					{
						if ( oCNpc::player )
						{
							// Hotkey POTION
							int lameHotkeyPotionFunc = parser.GetIndex("PLAYER_HOTKEY_LAME_POTION");
							if ( lameHotkeyPotionFunc > 0 )
							{
								oCNpc::player->GetEM(TRUE)->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, lameHotkeyPotionFunc), oCNpc::player);
								result = TRUE;
							}
						}
					}
					break;
				case GAME_LAME_HEAL:
					if ( oCGame::GetUsePotions() && zinput->KeyToggled(key) && GetGame() && IsGameRunning() && !GetGame()->IsInDevMode() )
					{
						if ( oCNpc::player )
						{
							// Hotkey HEAL
							int lameHotkeyHealFunc = parser.GetIndex("PLAYER_HOTKEY_LAME_HEAL");
							if ( lameHotkeyHealFunc > 0 )
							{
								oCNpc::player->GetEM(TRUE)->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, lameHotkeyHealFunc), oCNpc::player);
								result = TRUE;
							}
						}
					}
					break;
				}
			}
			break;
	};

	return result;
};

oCGame* CGameManager::GetGame()
{ 
	return gameSession; 
};

zBOOL CGameManager::IsIntroActive()				
{ 
	return (introActive && backLoop); 
};



// FIXME: was anderes �berlegen. Mehrere Welten parallel!!!
void CGameManager::InsertMenuWorld(zSTRING &backWorld,zSTRING &backDatFile)
{
	/*
	if (backLoop)				return;
	if (backWorld.IsEmpty())	return;
	if (backDatFile.IsEmpty())	return;

	savegameManager->ClearCurrent();

	backLoop	= zNEW(oCGame);	
	backLoop	->Init();
	backLoop->SetSavegameManager(savegameManager);
	backLoop->SetGameInfo(0);
	backLoop->LoadGame(SAVEGAME_SLOT_NEW, backWorld);	
	backLoop->LoadParserFile(backDatFile);
	backDatFileRunning = backDatFile;
	zCMenu::SetWorld		((zCWorld*)backLoop->GetWorld());
	zCMenu::SetCamera		(backLoop->GetCamera());
	zCMenu::RegisterFrameCB (MenuRender);*/
};


void CGameManager::RemoveMenuWorld()
{	
	/*if (backLoop) 
	{	
		backLoop -> Done();
		delete backLoop;
		backLoop = 0;
	}*/
};



					
zBOOL CGameManager::IsGameRunning()
{ 
	return (gameSession && gameSession->GetCamera()!=0) ; 
};

zBOOL CGameManager::IntroduceChapter()
{
	if (!s_chapter_introduce) return FALSE;

	s_chapter_introduce = false;

	if (zsound && !s_chapter_sound.IsEmpty()) 
	{
		zCSoundFX* snd = zsound->LoadSoundFX(s_chapter_sound);
		zsound->PlaySound(snd);
		zRELEASE(snd);
	}

	zCView* view = zNEW( zCView(0,0,8192,8192) );
	screen->InsertItem(view);
	
	view->InsertBack(s_chapter_texname);

		int dx = screen->anx(800);
		int dy = screen->any(600);

		view->SetPos((8192-dx)/2,(8192-dy)/2);
		view->SetSize(dx,dy);					

		zCView* textView1 = zNEW( zCView(0,0,8192,8192) );
		view->InsertItem(textView1);		
		textView1->SetPos(0,700);
		textView1->SetSize(8192,600);

		//[EDENFELD] 1.09 : Fonts in Constants.d enthalten
		zCPar_Symbol *sym = NULL;
		zSTRING fontName("font_old_20_white.tga");
		sym = parser.GetSymbol("TEXT_FONT_20");
		if (sym) sym->GetValue(fontName);
		textView1->SetFont(fontName);

		textView1->PrintCXY(s_chapter_text1);				

		zCView* textView2 = zNEW( zCView(0,0,8192,8192) );
		view->InsertItem(textView2);		
		textView2->SetPos(0,7100);
		textView2->SetSize(8192,600);

		//[EDENFELD] 1.09 : Fonts in Constants.d enthalten
		fontName = "font_old_10_white.tga";
		sym = parser.GetSymbol("TEXT_FONT_10");
		if (sym) sym->GetValue(fontName);

		textView2->SetFont(fontName);

		textView2->PrintCXY(s_chapter_text2);
		
		view->Blit();
		textView1->Blit();
		textView2->Blit();
		zrenderer->Vid_Blit();

		zCTimer timer;
		zREAL	timeCount=0;
		zBOOL	finished=FALSE;
		while (!finished) 
		{			
			zinput->ProcessInputEvents();
			timeCount += timer.GetFrameTime();
			timer.ResetTimer();

			finished = finished || (timeCount>s_chapter_waittime);
			finished = finished || zinput->KeyPressed(KEY_ESC) || zinput->GetMouseButtonPressedRight();
			finished = finished || zinput->GetState(GAME_END)>0;
		}

	view->RemoveItem(textView1);
	view->RemoveItem(textView2);
	screen->RemoveItem(view);	

	delete view;view=0;
	delete textView1;textView1=0;
	delete textView2;textView2=0;

	zinput->ClearKeyBuffer();
	zinput->ResetRepeatKey();

	return TRUE;
};

zBOOL CGameManager::IntroduceChapter(zSTRING text1, zSTRING text2, zSTRING texName, zSTRING sndName, int milliseconds)
{	
	s_chapter_introduce = true;

	s_chapter_text1		= text1;
	s_chapter_text2		= text2;
	s_chapter_texname	= texName;
	s_chapter_sound		= sndName;
	s_chapter_waittime	= milliseconds;

	return TRUE;
}

zBOOL CGameManager::PlayVideo(zSTRING s)
{	
	if (!videoPlayer) return FALSE;	
	
	videoPlayInGame=FALSE;
	
	zBOOL musicEnabled = zoptions->ReadBool(zOPT_SEC_SOUND,"musicEnabled",TRUE);
			
	if (zsound) zsound->StopAllSounds();
	
	zCZoneMusic::SetAutochange(FALSE);
	zCMusicSystem::DisableMusicSystem(TRUE);		

	if (gameSession)
		gameSession->Pause(exitSession);
	videoPlayer->OpenVideo(zoptions->GetDirString(DIR_VIDEO)+s);
	videoPlayer->SetFullscreen(TRUE,"videoback.tga");
	videoPlayer->Play();	
	videoPlayer->CloseVideo();						
	if (gameSession && !exitSession)
		gameSession->Unpause();

	zCZoneMusic::SetAutochange(musicEnabled);		
	zCMusicSystem::DisableMusicSystem(!musicEnabled);
		
	return TRUE;
};

// [BENDLIN] TODO: ScreenBlend
zBOOL CGameManager::PlayVideoEx(zSTRING s, zINT screenBlend, zBOOL sessionExit)
{	
	if (!videoPlayer)
	{
		if (sessionExit)
			return ExitSession();
		return FALSE;
	}
	
	videoPlayInGame=FALSE;
	
	zBOOL musicEnabled = zoptions->ReadBool(zOPT_SEC_SOUND, "musicEnabled", TRUE);
			
	if (zsound) zsound->StopAllSounds();
	
	zCZoneMusic::SetAutochange(FALSE);
	zCMusicSystem::DisableMusicSystem(TRUE);		

	if (gameSession)
		gameSession->Pause(sessionExit);
	
	videoPlayer->OpenVideo(zoptions->GetDirString(DIR_VIDEO)+s);
	videoPlayer->SetFullscreen(TRUE,"videoback.tga");
	videoPlayer->Play();	
	if (screenBlend && !sessionExit && oCNpc::player)
	{
		oCVisualFX* blendFX = oCVisualFX::CreateAndPlay("BLACK_SCREEN", oCNpc::player);
		zRELEASE(blendFX);
	}
	videoPlayer->CloseVideo();

	if (sessionExit)
		ExitSession();
	else if (gameSession)
		gameSession->Unpause();

	zCZoneMusic::SetAutochange(musicEnabled);		
	zCMusicSystem::DisableMusicSystem(!musicEnabled);

	return TRUE;
};

void CGameManager::ShowRealPlayTime()
{	
	int seconds = GetPlaytimeSeconds();
	int _hours		= (seconds / 3600);
	int _minutes	= (seconds / 60) - (_hours * 60);
	
	zSTRING s;
	if (_minutes<10) s="0";
	zCView* view	= ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN );
	if (view) view->PrintTimed(100,300,zSTRING(_hours)+":"+s+zSTRING(_minutes)+" played", 3000);
};


