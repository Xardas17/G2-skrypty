/******************************************************************************** 
 
     $Workfile:: oGame.h              $                $Date:: 13.04.01 18:27   $
     $Revision:: 42                   $             $Modtime:: 4.04.01 17:22    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oGame.h $
 * 
 * 42    13.04.01 18:27 Edenfeld
 * 
 * 41    13.03.01 19:49 Hildebrandt
 * 
 * 40    13.03.01 18:36 Wohlers
 * Patches 1.07 1.Teil
 * 
 * 39    13.02.01 21:33 Wohlers
 * 
 * 38    10.02.01 1:50 Speckels
 * 
 * 37    8.02.01 19:39 Edenfeld
 * 
 * 36    5.02.01 20:19 Wohlers
 * 
 * 35    1.02.01 21:47 Speckels
 * 
 * 34    30.01.01 16:16 Speckels
 * 
 * 33    25.01.01 20:09 Wohlers
 * 
 * 32    25.01.01 17:33 Speckels
 * 
 * 31    25.01.01 15:59 Wohlers
 * 
 * 30    23.01.01 19:02 Wohlers
 * 
 * 29    22.01.01 21:49 Speckels
 * 
 * 28    11.01.01 15:46 Wohlers
 * 
 * 27    8.01.01 14:55 Wohlers
 * 
 * 26    21.11.00 14:12 Wohlers
 * 
 * 25    8.11.00 18:18 Speckels
 * 
 * 24    7.11.00 18:53 Wohlers
 * 
 * 23    1.11.00 15:25 Speckels
 * 
 * 22    10.10.00 15:47 Speckels
 * 
 * 21    6.10.00 16:53 Speckels
 * 
 * 20    4/10/00 18:17 Luesebrink
 * 
 * 19    4.10.00 17:15 Wohlers 
 * 
 * 18    14.09.00 16:54 Wohlers
 * 
 * 17    8.09.00 15:52 Keskenti
 * 
 * 16    2.09.00 2:22 Wohlers
 * 
 *********************************************************************************/

// oGame
#ifndef __OGAME_H__
#define __OGAME_H__

#include "z3d.h"
#include "zWorld.h"
#include "zContainer.h"
#include "zview.h"
#include "zoption.h"
#include "zSession.h"

#include "oMusicZone.h"
#include "osavegame.h"

class zCViewProgressBar;
class zCView;
class oCHelp;
class oCGameInfo;
class oCWorld;
class zCCamera;
class zCAICamera;
class zCVob;
class oCVob;
class oCNpc;
class zCParser;
class zCConsole;

class oCItem;
class oCItemContainer_Slot;
class oCItemContainer;
class oCMob;
class oCTradeDialog;
class oCGuilds;
class oCInfoManager;
class oCNewsManager;
class oCSVMManager;
class oCTradeManager;
class oCPortalRoomManager;
class oCSpawnManager;
class oCWorldTimer;
class oCWorld;
class oCViewStatusBar;
class oCSavegameManager;
class oCSavegameInfo;

extern oCVob* SearchVobByInstance(zCTree<zCVob>* vobtree, int& index);

class oCGame : public zCSession {

public:

	// *******************************
	// Engine
	// *******************************

	//
	//	CODECHANGE [ROMAN]
	//
	typedef 
	enum oEGameDialogView
	{
		GAME_VIEW_SCREEN		,
		GAME_VIEW_CONVERSATION	,		
		GAME_VIEW_AMBIENT		,		
		GAME_VIEW_CINEMA		,		
		GAME_VIEW_CHOICE		,
		GAME_VIEW_NOISE			,
		GAME_VIEW_MAX
	}
	oTGameDialogView;
	//
	//	CODECHANGE [ROMAN] END
	//

	static zBOOL			GetUseOldControls			()						{ return s_bUseOldControls;		};
	static void				SetUseOldControls			(const zBOOL useOld)	{ s_bUseOldControls = useOld;	};
	static zBOOL			GetUseOnlineHelp			()						{ return s_bUseOnlineHelp;		};
	static void				SetUseOnlineHelp			(const zBOOL useOld)	{ s_bUseOnlineHelp	= useOld;	};
	static zBOOL			GetUsePotions				()						{ return s_bUsePotionKeys;		};
	static void				SetUsePotions				(const zBOOL useOld)	{ s_bUsePotionKeys	= useOld;	};
	static zREAL			GetUseSpeechReverbLevel		()						{ return s_fUseSpeechReverb;	};
	static void				SetUseSpeechReverbLevel		(const zREAL useRev)	{ s_fUseSpeechReverb = useRev;	};
	static zBOOL			GetUseQuickSave				()						{ return s_bUseQuickSave;		};
	static void				SetUseQuickSave				(const zBOOL useRev)	{ s_bUseQuickSave	= useRev;	};

	oCGame												();
	virtual ~oCGame										();

	void	 UpdateViewSettings							();
	
	// Engine :
	virtual void			Init						();			
	virtual void			Done						();

	virtual void			Render						();
	virtual void			RenderBlit					();

	// Note : Kameraverwaltung ist noch sehr undurchsichtig, auf Engine vereinheitlichen ?
	// Wer erzeugt wo welche Vobs, wer entfernt diese, was passiert bei Kamerafahrten...
	virtual void			CamInit						();
	virtual void			CamInit						(zCVob* camera_vob, zCCamera* cam);
	
 	virtual void			SaveWorld					(const zSTRING& levelpath,	zCWorld::zTWorldSaveMode savemode, BOOL savemesh = FALSE, BOOL saveBin=TRUE);
	virtual	zBOOL			LoadWorld					(const zSTRING& fileName, const zCWorld::zTWorldLoadMode loadMode);
	virtual	void			EnterWorld					(oCNpc* playerVob = NULL, zBOOL changePlayerPos = TRUE, const zSTRING& startpoint = zSTR_EMPTY);

	virtual void			Pause						(zBOOL sessionHalted = FALSE);
	virtual void			Unpause						();

	virtual void			SetDrawWaynet				(zBOOL on)		{ game_showwaynet = on;				};
	virtual zBOOL			GetDrawWaynet				()				{ return game_showwaynet;			};
	virtual void			RenderWaynet				();

	// *******************************
	// possibly Engine ????? 
	// *******************************

	// Fogging/PlayerLight/CamLight (Default + CommandLine)
	virtual void			EnvironmentInit				();
	virtual void			SetRanges					();
	virtual void			SetRangesByCommandLine		();
	
	// Time
	virtual void			SetTime						(int  day, int  hour, int  min);
	virtual void			GetTime						(int& day, int& hour, int& min);

	// starting player position in the world
	virtual zPOINT3			GetStartPos					()				{ return startpos;	};

	// *******************************
	// Game
	// *******************************
	void					SetSavegameManager			(oCSavegameManager* man) { savegameManager = man; };
	virtual void			SetGameInfo					(oCGameInfo* _gameinfo);
	virtual zBOOL			LoadParserFile				(const zSTRING& parserfile);
	
	// SaveGames 
	virtual void			TriggerChangeLevel			(const zSTRING& levelpath, const zSTRING& start);
	virtual oCWorld*		GetGameWorld				();

	void					LoadGame					(int slotID, const zSTRING& levelpath);
	void					LoadSavegame				(int slotnr, zBOOL saveGlobals = FALSE);
	void					WriteSavegame				(int slotnr = SAVEGAME_SLOT_CURRENT, zBOOL saveGlobals = TRUE);	

	void					LoadWorld					(int slotID, const zSTRING& levelpath = zSTR_EMPTY);

	void					EnableTestmode				(zBOOL on) { game_testmode = on; };
	zBOOL					IsInDevMode					() const   { return game_testmode;	};

	// Getting important GameObjects
	oCNpc*					GetSelfPlayerVob			();
	oCWorldTimer*			GetWorldTimer				();
	oCGuilds*				GetGuilds					();
	oCInfoManager*			GetInfoManager				();
	oCNewsManager*			GetNewsManager				();
	oCTradeManager*			GetTradeManager				();
	oCSVMManager*			GetSVMManager				();
	oCPortalRoomManager*	GetPortalRoomManager		();
	oCSpawnManager*			GetSpawnManager				();
	
	virtual oCGameInfo*		GetGameInfo					();
	virtual zCView*			GetTextView					();

	// Setting Data
	void					SetShowTime					(zBOOL on)		{ game_showtime = on;				};
	zBOOL					GetShowTime					()				{ return game_showtime;				};
	void					SetShowDebug				(zBOOL on)		{ zCView::SetShowDebug(on);			};
	zBOOL					GetShowDebug				()				{ return zCView::GetShowDebug();	};	
	void					SetShowFramerate			(const zBOOL on){ this->game_frameinfo	= on;		};
	zBOOL					GetShowFramerate			() const		{ return this->game_frameinfo;		};	

	void					SetShowNews					(oCNpc* npc);

	// Menu
	zBOOL					IsPaused					()	{ return singleStep; };	

	// Screen + Progress
	virtual void			OpenLoadscreen				(bool gameStart, zSTRING worldName);	
	virtual void			OpenSavescreen				(bool saveGame);
	virtual void			CloseLoadscreen				();
	virtual void			CloseSavescreen				();	
	zCViewProgressBar*		GetProgressBar				() { return progressBar; };

	// For MusicSystem -> ThreatLevel
	oHEROSTATUS				GetHeroStatus				();
	
	// Object Routines
	void					ResetObjectRoutineList		();
	void					ClearObjectRoutineList		();
	void					InsertObjectRoutine			(int type, const zSTRING& name, int hour1, int min1, int state);
	void					CheckObjectRoutines			();
	void					SetObjectRoutineTimeChange	(int hour1,int min1,int hour2, int min2);

	// Refresh Mechanismen
	void					RefreshNpcs					();
	void					DeleteTorches				();

	void					UpdateScreenResolution		();

	// Debug
	void					DeleteNpcs					(oCNpc* npc1, oCNpc* np2, zREAL radius);
	void					SwitchCamToNextNpc			();
	void					ToggleShowFreePoints		();
	void					ShowFreePoints				();

	// Konsole		
	static zBOOL			ConsoleEvalFunc				( const zSTRING &s, zSTRING &msg );

	//
	//	CODECHANGE [ROMAN]
	//
	zBOOL					IsEnabled					( oTGameDialogView enuView )					{ return array_view_enabled[ enuView ]; }
	zBOOL					IsVisible					( oTGameDialogView enuView )					{ return array_view_visible[ enuView ]; }
	void					EnableView					( oTGameDialogView enuView, zBOOL bEnabled  )	{ array_view_enabled[ enuView ] = bEnabled; }
	zCView*					GetView						( oTGameDialogView enuView ) const				{ return array_view[ enuView ]; }
	zBOOL					OpenView					( oTGameDialogView enuView ) ;
	zBOOL					CloseView					( oTGameDialogView enuView ) ;
	//
	//	CODECHANGE [ROMAN] END
	//

	void					SetShowPlayerStatus			(zBOOL showIt);
	zBOOL					GetShowPlayerStatus			();
	void					UpdatePlayerStatus			();
	void					InitNpcAttitudes			();

	zBOOL					IsInScriptStartup			() { return inScriptStartup; };
	zBOOL					IsInLoadSaveGame			() { return inLoadSaveGame;  };
	zBOOL					ForceKeyEvent				(int key)										{ return HandleEvent(key);	};

private:	

	// *******************************
	// private methods
	// Game relevant
	// *******************************

	void					ClearGameState				();

	oCNpc*					RemovePlayerFromWorld		();
	void					InsertPlayerIntoWorld		(oCNpc* npc, zMATRIX4& trafo);

	virtual void			ChangeLevel					(const zSTRING& levelpath, const zSTRING& start);

	virtual	void			LoadWorldStartup			(const zSTRING& levelpath);
	virtual	void			LoadWorldStat				(	   zSTRING  levelpath);
	virtual	void			LoadWorldDyn				(const zSTRING& levelpath);

	virtual void			InitWorldSavegame			(int& slotID, zSTRING& levelpath);
	virtual zBOOL			CheckIfSavegameExists		(const zSTRING& levelpath);

	virtual void			CompileWorld				();
	void					SetupPlayers				(oCNpc*& playerVob, const zSTRING& startpoint);
	void					SetCameraPosition			();

	zBOOL					IsInWorld					(const zSTRING& levelpath = zSTR_EMPTY);
	zBOOL					CheckObjectConsistency		(zBOOL checkItems = TRUE);
	
	void					PreSaveGameProcessing		(zBOOL saveGlobals);
	void					PostSaveGameProcessing		();

	// Inits
	virtual void			DesktopInit					();
	virtual void			WorldInit					();
	virtual void			NpcInit						();
	virtual void			NpcInit						(zCTree<zCVob>* vobtree);

	// Tools
	void					CreateVobList				(zCList <zCVob> &resultlist, zCTree <zCVob> *node, zTVobType vobtyp);
	void					RemoveHelperVobs			(zCTree <zCVob> *node);	
	virtual void			SetAsPlayer					(const zSTRING& name);
	
#ifdef COMPILING_SPACER
public:
#endif

	zBOOL					HandleEvent					(int key);
	zBOOL					TestKeys					(int key);
	zBOOL					IA_TestWay					(int key);

	// Visuals
	void					CacheVisualsIn				();
	void					CacheVisualsOut				();
	void					RecurseCacheVobs			(zCTree<zCVob>* vobtree);

	// SkriptStartup
	void					EnableScriptStartup			(zBOOL enable) { scriptStartup = enable; };
	void					CallScriptStartup			();
	void					CallScriptInit				();

	// Debug
	void					ShowDebugInfos				();

	// Parser - External Funktions
	void					DefineExternals_Ulfi		(zCParser *p);

	// CODECHANGE [STEFAN]
	// Script-Debugging
public:
	zBOOL					IsDebuggingChannel			(int ch);
	zBOOL					IsDebuggingInstance			(zCVob *vob);
	zBOOL					IsDebuggingAllInstances		();
	// CODECHANGE [STEFAN] END


private:

	static zBOOL			s_bUseOldControls;
	static zREAL			s_fUseSpeechReverb;
	static zBOOL			s_bUseOnlineHelp;
	static zBOOL			s_bUsePotionKeys;
	static zBOOL			s_bUseQuickSave;


	// *******************************
	// private members
	// Engine relevant !?
	// *******************************

	// Environment 
	zREAL					cliprange;
	zREAL					fogrange;

	zBOOL					inScriptStartup;
	zBOOL					inLoadSaveGame;
	zBOOL					inLevelChange;

	// *******************************
	// private members
	// Game relevant
	// *******************************
	
	// Layout

	//
	//	CODECHANGE [ROMAN]
	//
	zCView*					array_view			[ oTGameDialogView :: GAME_VIEW_MAX ];
	zBOOL					array_view_visible	[ oTGameDialogView :: GAME_VIEW_MAX ];
	zBOOL					array_view_enabled	[ oTGameDialogView :: GAME_VIEW_MAX ];
	//
	//	CODECHANGE [ROMAN] END
	//

	oCSavegameManager*		savegameManager;
	zCView*					game_text;
	zCView					*load_screen, *save_screen, *pause_screen;		
	oCViewStatusBar*		hpBar;
	oCViewStatusBar*		swimBar;
	oCViewStatusBar*		manaBar;
	oCViewStatusBar*		focusBar;
	zBOOL					showPlayerStatus;
	// Debug
	zBOOL					game_drawall;
	zBOOL					game_frameinfo;
	zBOOL					game_showaniinfo;
	zBOOL					game_showwaynet;
	zBOOL					game_testmode;	
	zBOOL					game_editwaynet;
	zBOOL					game_showtime;
	zBOOL					game_showranges;
	zBOOL					drawWayBoxes;
	zBOOL					scriptStartup;
	zBOOL					showFreePoints;
	oCNpc*					showRoutineNpc;

	// Level
	zBOOL					loadNextLevel;
	zSTRING					loadNextLevelName;
	zSTRING					loadNextLevelStart;	

	// The Player
	zVEC3					startpos;
	oCGameInfo*				gameInfo;				// Berts Klasse mit PlayerInfos
	zCVobLight*				pl_light;
	zREAL					pl_lightval;

	// Timer
	oCWorldTimer*			wldTimer;
	zREAL					timeStep;			// Ermöglicht Einzelbildschaltung
	zBOOL					singleStep;	

	// Info - Pool
	oCGuilds*				guilds;
	oCInfoManager*			infoman;
	oCNewsManager*			newsman;
	oCSVMManager*			svmman;
	oCTradeManager*			trademan;
	oCPortalRoomManager*	portalman;
	oCSpawnManager*			spawnman;
	
	// TEMP Debug
	zREAL					music_delay;
	oCNpc*					watchnpc;

	// startup screen blend/precaching time
	zBOOL					m_bWorldEntered;
	zREAL					m_fEnterWorldTimer;


	int						initial_hour, initial_minute;

// CODECHANGE [STEFAN]
	zCArray<zCVob*>			debugInstances;
	int						debugChannels;
	zBOOL					debugAllInstances;
// CODECHANGE [STEFAN] END

private:

	// *****************************
	// Object-Routine-Data-Structure
	// *****************************
	typedef struct {
		// FIXME : Argh, zCListSort
		void		Release()		{ delete(this); };

		zSTRING		objName;
		int			stateNum;
		int			hour1,min1;
		int			type;
	} TObjectRoutine;

	int							oldRoutineDay;
	zCListSort<TObjectRoutine>	objRoutineList;
	zCListSort<TObjectRoutine>* currentObjectRoutine;
	zCViewProgressBar*			progressBar;
	zCArray   <zCVisual*>		visualList;

	static int		Sort_Routine		(TObjectRoutine *entry1, TObjectRoutine *entry2);
};

extern oCGame* ogame;

// **********************************************
// Console / Debug
// **********************************************

extern zCConsole* game_species_con, *game_aiConsole;

extern void Game_OpenConsole		();
extern void Game_OpenSpeciesConsole	();
extern void Game_OpenFightConsole	();

extern void	Game_SaveSCPos			();
extern void	Game_LoadSCPos			();

extern void Game_ToggleTestMode		(BOOL on);
extern void Game_ToggleHoldTime		();
extern void Game_ToggleScreenMode	();
extern void Game_GotoWP				(const zSTRING &s, zSTRING &s2);
extern void Game_PlaySound			(zSTRING &s);

extern void	Game_ToggleAIConsole	();
extern void	Game_ChangeAIConsole	(const zSTRING &var);

#endif
 
