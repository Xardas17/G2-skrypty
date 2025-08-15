/******************************************************************************** 
 
     $Workfile:: oNpcStates.h         $                $Date:: 26.01.01 16:06   $
     $Revision:: 15                   $             $Modtime:: 26.01.01 15:40   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNpcStates.h $
 * 
 * 15    26.01.01 16:06 Moos
 * 
 * 14    9.01.01 20:22 Wohlers
 * 
 * 13    30.11.00 15:02 Wohlers
 * 
 * 12    22.09.00 15:52 Wohlers
 * 
 * 11    6.09.00 20:33 Wohlers
 * 
 * 10    5.09.00 21:09 Wohlers
 * 
 * 9     4.08.00 13:53 Wohlers
 * 
 * 8     5.07.00 12:21 Wohlers
 * 
 * 6     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 7     10.05.00 23:28 Wohlers
 * Gothic 0.81a
 * 
 * 6     8.05.00 23:08 Edenfeld
 * 
 * 5     8.05.00 19:31 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 12    19.04.00 16:44 Wohlers
 * Bug-Fixes
 * 
 * 11    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 10    7.04.00 19:16 Wohlers
 * Day and Hour werden an Cutscenes uebergeben
 * 
 * 9     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 7     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 6     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 5     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 4     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ONPC_STATES__
#define __ONPC_STATES__

#include "zTypes.h"
#include "zList.h"

// Forwards
class zCCSCutsceneContext;
class oCRtnEntry;
class oCNpc;
class zCRoute;

enum { AITIME_NO, AITIME_ONCE, AITIME_TIMED };

typedef struct TNpcAIState {

	TNpcAIState		();
	~TNpcAIState	();

	int				index;
	int				loop;
	int				end;
	int				timeBehaviour;
	zREAL			restTime;
	int				phase;
	zBOOL			valid;
	zSTRING			name;
	zREAL			stateTime;
	int				prgIndex;		
	zBOOL			isRtnState;

} TNpcAIState;


// ************************************
// AI - States
// ************************************

// -1 Skripterror
// -2 Alles was Programmgesteuert ist.

enum	{	NPC_AISTATE_ANSWER		= -2,	NPC_AISTATE_DEAD	= -3,	NPC_AISTATE_UNCONSCIOUS = -4,
			NPC_AISTATE_FADEAWAY	= -5,	NPC_AISTATE_FOLLOW	= -6 };
const int	NPC_AISTATE_PRG_MAX		=  7;

extern const zSTRING	npcStatesPrg	[NPC_AISTATE_PRG_MAX];  // defined in oCNpc.cpp

class oCNpc_States 
{
public:
	zSTRING name;

	oCNpc_States								();
	~oCNpc_States								();
	
	void			SetOwner					(oCNpc* n);

	int				GetState					();
	zBOOL			IsInState					(int stateID);
	zBOOL			IsScriptStateActive			();
	int				GetStateTime				();
	void			SetStateTime				(int seconds);

	// Start States
	zBOOL			StartRtnState				(zBOOL force = FALSE);
	zBOOL			StartAIState				(const zSTRING& name, zBOOL endOldState, int timeBehaviour, zREAL timed=0.0f, zBOOL isRtnState = FALSE );
	zBOOL			StartAIState				(int index, zBOOL endOldState, int timeBehaviour, zREAL timed=0.0f, zBOOL isRtnState = FALSE );
	zBOOL			DoAIState					();
	void			ClearAIState				();
	void			EndCurrentState				();

	// Daily Routine
	void			InitRoutine					();
	void			InsertRoutine				(int h1, int m1, int h2, int m2, int func, const zSTRING &s, int instance=-1 );
	void			InsertRoutineCS				(const zSTRING &csName, const zSTRING& roleName );
	zBOOL			HasRoutine					() { return hasRoutine; };
	void			SetRoutineName				(const zSTRING& routineName);
	zSTRING			GetRoutineName				();
	void			ChangeRoutine				(const zSTRING& routineName);
	void			ChangeRoutine				(int newRoutineFunc);
	zBOOL			IsInRoutine					();
	oCRtnEntry*		GetRoutineCurrent			() { return rtnNow;		};
	zCRoute*		GetRoutineRoute				() { return rtnRoute;	};
	void			SetRoutine					(oCRtnEntry* nowTA, oCRtnEntry* beforeTA);
	void			SetStartNewRoutine			(zBOOL start) { startNewRoutine = start; };

	// Overlay Routine
	void			BeginInsertOverlayRoutine	();
	void			StopInsertOverlayRoutine	();
	void			RemoveOverlayEntry			(oCRtnEntry* entry);
	void			RemoveOverlay				();

	// AI-State Driven
	zBOOL			IsAIStateDriven				();
	void			InitAIStateDriven			(const zVEC3& posPoint);
	const zVEC3&	GetAIStatePosition			();
	
	// Cutscenes
	zBOOL			IsInCutscene				();
	void			StartOutputUnit				(int csNumber);
	void			StartCutscene				(const zSTRING& csName, const zSTRING& roleName);
	void			CloseCutscenes				();
	
	// Debug
	int				GetLastState				();
	int				GetLastRoutineState			();
	zSTRING			GetStateInfo				();
	zSTRING			GetLastError				();

	// Archive
	virtual void	Archive						(zCArchiver& arc);
	virtual void	Unarchive					(zCArchiver& arc);
	virtual void	PackState					(zCBuffer& buffer);
	virtual void	UnpackState					(zCBuffer& buffer);

	void			ClearParserReferences		();

public:	// FIXME : Private

	
	zBOOL				ActivateRtnState		(zBOOL force = FALSE);
	zBOOL				CanPlayerUseAIState		();
	zBOOL				CanPlayerUseAIState		(const TNpcAIState& state);

	
	void				SetParserInstanceNpc	(int index, oCNpc* npc);
	void				SetParserInstanceItem	(oCItem* item);

	// Vars

	oCNpc*				npc;

	TNpcAIState			curState;
	TNpcAIState			nextState;
	int					lastAIState;
	// Daily Routine
	zBOOL				hasRoutine;					// Any Routine Entrys available ?
	zBOOL				rtnChanged;
	oCRtnEntry*			rtnBefore;					// Temp ? Used for Cutscene-Usage
	oCRtnEntry*			rtnNow;						// Current Routine
	zCRoute*			rtnRoute;					// Route from "rtnBefore" to "rtnNow"
	zBOOL				rtnOverlay;					// In Routine Overlay ?
	int					rtnOverlayCount;			// How many Entries left ?
	int					walkmode_routine;
	zBOOL				weaponmode_routine;
	zBOOL				startNewRoutine;
	// State Driven
	int					aiStateDriven;
	zVEC3				aiStatePosition;
	
	// Global Parser Var Saves
	oCNpc				*parOther,*parVictim;
	oCItem				*parItem;

	// Temp, only for debugging purposes
	int					rntChangeCount;
};

#endif
