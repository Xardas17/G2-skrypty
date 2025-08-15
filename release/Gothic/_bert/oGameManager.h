/******************************************************************************** 
 
     $Workfile:: oGameManager.h       $                $Date:: 15.03.01 14:00   $
     $Revision:: 30                   $             $Modtime:: 14.03.01 21:32   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oGameManager.h $
 * 
 * 30    15.03.01 14:00 Speckels
 * 
 * 29    13.03.01 18:57 Speckels
 * 
 * 28    16.02.01 21:01 Speckels
 * 
 * 27    16.02.01 13:12 Speckels
 * 
 * 26    14.02.01 21:04 Speckels
 * 
 * 25    13.02.01 20:28 Speckels
 * 
 * 24    13.02.01 18:15 Speckels
 * 
 * 23    31.01.01 18:24 Speckels
 * 
 * 22    19.01.01 0:59 Speckels
 * 
 * 31    19.01.01 0:56 Speckels
 * 
 * 30    16.01.01 19:51 Admin
 * 
 * 21    16.01.01 16:42 Speckels
 * 
 * 20    15.01.01 20:44 Speckels
 * 
 * 19    9.01.01 20:22 Speckels
 * 
 * 18    20.11.00 22:00 Speckels
 * 
 * 17    15.11.00 21:03 Speckels
 * 
 * 16    17.10.00 16:12 Speckels
 * 
 * 15    13.10.00 14:32 Speckels
 * 
 * 14    10.10.00 14:48 Speckels
 * 
 * 13    5.10.00 14:02 Speckels
 * 
 * 12    28.09.00 21:08 Speckels
 * 
 * 11    26.09.00 16:02 Speckels
 * 
 * 10    13.09.00 15:57 Wohlers
 * 
 * 9     8.09.00 17:33 Speckels
 * 
 * 8     28.08.00 14:31 Speckels
 * 
 * 19    26.08.00 19:48 Speckels
 * 
 * 18    24.08.00 12:17 Speckels
 * 
 * 17    23.08.00 21:46 Admin
 * 
 * 6     21.08.00 18:47 Speckels
 * 
 * 15    16.08.00 12:32 Admin
 * 
 * 5     10.08.00 21:46 Speckels
 * 
 * 14    9.08.00 17:11 Admin
 * 
 * 4     10.07.00 15:53 Speckels
 * 
 * 2     26.04.00 11:28 Admin
 * 
 * 2     19.04.00 18:36 Speckels
 * 
 * 3     30.03.00 14:23 Speckels
 * 
 * 5     7.02.00 17:58 Speckels
 * 
 * 4     1.12.99 13:27 Speckels
 * Functioncall InitAfterParsing added.
 * 
 * 3     21.10.99 23:37 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 30 $ ($Modtime: 14.03.01 21:32 $)

#ifndef __OGAMEMANAGER_H__
#define __OGAMEMANAGER_H__


#include "ztypes.h"
#include "zstring.h"
#include "zview.h"


class oCGame;
class oCSavegameManager;
class oCBinkPlayer;
class oCMenuSavegame;
class zCMenu;

class CGameManager : public zCInputCallback
{		
public:

	CGameManager();
	virtual ~CGameManager();
	
	void	Init	(zTSystemContextHandle& handle);	
	void	Run		();	
	void	Done	();

	oCGame* GetGame			();

	zBOOL   IsGameRunning	();
	zBOOL	IsIntroActive	();

	zBOOL	ExitGame		();
	zBOOL	ExitSession		();

	zBOOL	PlayVideo		(zSTRING s);
	zBOOL	PlayVideoEx		(zSTRING s, zINT screenBlend = 0, zBOOL sessionExit = FALSE);
	
	zBOOL	IntroduceChapter();
	zBOOL	IntroduceChapter(zSTRING text1, zSTRING text2, zSTRING texName, zSTRING sndName, int milliseconds);

	void	ShowRealPlayTime();

	inline	void Render		(zBOOL blit=TRUE);

	int		GetPlaytimeSeconds();

	void	Write_Savegame(int slotNr);
	void	Read_Savegame(int slotNr);

	void	InsertMenuWorld(zSTRING &backWorld,zSTRING &backDatFile);
	void    RemoveMenuWorld();	

protected:

	zBOOL	HandleCancelKey(int key);
	zBOOL	HandleEvent(int key);

	void	SetMenuStopsGame(zBOOL &b)		{ gameIdle = b; };		

	void	ShowSplashScreen();
	void	RemoveSplashScreen();
	
	// Game	
	void	GameInit();
	void	GameDone();

	void	ApplySomeSettings();
	void	InitSettings();	

	void	InitScreen_Open();
	void	InitScreen_Menu();
	void	InitScreen_Close();	
	
	void	Tool_ConvertData();

protected:
	
	// Game-Session
	void	GameSessionInit();
	void	GameSessionDone();	
	void	GameSessionReset();

	// Intro/Extro
	void	ShowIntro();
	void	ShowExtro();

	// Menu
	void	PreMenu	();
	void	PostMenu(zSTRING action);
	void	Menu(zBOOL saveGame);	
	zBOOL	MenuEnabled(zBOOL& enableSave);	
		

private:

	zTRnd_AlphaBlendFunc oldAlphaBlendFunc;

	zTSystemContextHandle	sysContextHandle;

	oCGame*				gameSession;
	oCGame*				backLoop;
	zBOOL				exitGame;	
	zBOOL				exitSession;	
	zBOOL				gameIdle;
	zBOOL				lastWorldWasGame;
	oCSavegameManager*	savegameManager;

	zCArray<zSTRING>	lastDatFileList;
	zCArray<zSTRING>	lastWorldList;
	zSTRING				backWorldRunning;
	zSTRING				backDatFileRunning;

	zCView*				vidScreen;
	zCView*				initScreen;

	zBOOL				introActive;
	zBOOL				dontStartGame;

	oCBinkPlayer*		videoPlayer;
	zBOOL				videoPlayInGame;

	zCMenu*				menu_chgkeys;
	zCMenu*				menu_chgkeys_ext;
	oCMenuSavegame*		menu_save_savegame;
	oCMenuSavegame*		menu_load_savegame;	

	int					playTime;
};

typedef CGameManager* CGameManagerPtr;

extern CGameManagerPtr gameMan;

#endif
 
