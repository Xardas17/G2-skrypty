/******************************************************************************** 
 
     $Workfile:: oNpcStates.cpp       $                $Date:: 8.02.01 18:10    $
     $Revision:: 76                   $             $Modtime:: 8.02.01 18:10    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNpcStates.cpp $
 * 
 * 76    8.02.01 18:10 Wohlers
 * 
 * 75    6.02.01 13:41 Moos
 * 
 * 74    29.01.01 22:45 Wohlers
 * 
 * 73    29.01.01 22:13 Wohlers
 * 
 * 72    29.01.01 22:09 Wohlers
 * 
 * 71    29.01.01 21:59 Wohlers
 * 
 * 70    29.01.01 17:45 Wohlers
 * 
 * 69    24.01.01 15:14 Speckels
 * 
 * 68    18.01.01 14:01 Wohlers
 * 
 * 67    18.01.01 13:25 Moos
 * 
 * 66    18.01.01 2:00 Wohlers
 * 
 * 65    16.01.01 18:53 Wohlers
 * 
 * 64    16.01.01 18:30 Speckels
 * 
 * 63    9.01.01 20:22 Wohlers
 * 
 * 62    20.12.00 0:03 Wohlers
 * 
 * 61    19.12.00 17:38 Wohlers
 * 
 * 60    5.12.00 21:57 Speckels
 * 
 * 59    30.11.00 15:02 Wohlers
 * 
 * 58    24.11.00 14:20 Speckels
 * 
 * 57    23.11.00 19:18 Wohlers
 * 
 * 56    20.10.00 16:41 Wohlers
 * 
 * 55    19.10.00 21:49 Wohlers
 * 
 * 54    18/10/00 15:17 Luesebrink
 * 
 * 53    18.10.00 0:51 Wohlers
 * 
 * 52    16.10.00 21:28 Wohlers
 * 
 * 51    5/10/00 15:15 Luesebrink
 * 
 * 50    5/10/00 14:32 Luesebrink
 * 
 * 49    4/10/00 15:28 Luesebrink
 * 
 * 48    22.09.00 16:58 Wohlers
 * 
 * 47    22.09.00 16:53 Wohlers
 * 
 * 46    22.09.00 16:48 Wohlers
 * 
 * 45    22.09.00 15:56 Wohlers
 * 
 * 44    22.09.00 15:52 Wohlers
 * 
 * 43    19.09.00 19:00 Wohlers
 * 
 * 42    14.09.00 16:54 Wohlers
 * 
 * 41    7.09.00 16:06 Wohlers
 * 
 * 40    6.09.00 21:11 Wohlers
 * 
 * 39    6.09.00 20:33 Wohlers
 * 
 * 38    5.09.00 21:09 Wohlers
 * 
 * 37    2.09.00 6:46 Wohlers
 * 
 * 36    2.09.00 4:44 Wohlers
 * 
 * 35    1.09.00 23:20 Wohlers
 * 
 * 34    1.09.00 14:37 Rueve
 * 
 * 33    21.08.00 20:20 Speckels
 * 
 * 32    21.08.00 18:56 Speckels
 * 
 * 31    17.08.00 15:49 Wohlers
 * 
 * 30    15.08.00 20:57 Wohlers
 * 
 * 29    15.08.00 19:06 Wohlers
 * 
 * 28    10.08.00 21:16 Wohlers
 * 
 * 27    10.08.00 18:37 Wohlers
 * 
 * 26    7.08.00 16:54 Wohlers
 * 
 * 25    4.08.00 13:53 Wohlers
 * 
 * 24    2.08.00 21:09 Wohlers
 * 
 * 23    2.08.00 15:53 Keskenti
 * 
 * 23    2.08.00 15:53 Wohlers
 *
 * 22    2.08.00 14:25 Wohlers
 * 
 * 21    1.08.00 15:20 Wohlers
 * 
 * 20    31.07.00 22:04 Wohlers
 * 
 * 19    26.07.00 22:15 Wohlers
 * 
 * 18    21.07.00 15:34 Wohlers
 * 
 * 17    19.07.00 20:54 Wohlers
 * 
 * 16    19.07.00 12:45 Wohlers
 * 0.88
 * 
 * 15    12.07.00 14:52 Wohlers
 * Overlay-TA Bugfix
 * 
 * 14    7.07.00 12:42 Wohlers
 * Gothic 0.87
 * 
 * 13    5.07.00 12:21 Wohlers
 * 
 * 11    14.06.00 21:59 Wohlers
 * 
 * 10    9.06.00 12:59 Wohlers
 * Fixes
 * 
 * 9     5.06.00 22:35 Wohlers
 * uSrc 05.06.00
 * 
 * 8     29.05.00 18:36 Wohlers
 * 
 * 7     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 12    12.05.00 3:37 Wohlers
 * 
 * 11    10.05.00 23:28 Wohlers
 * Gothic 0.81a
 * 
 * 10    9.05.00 20:20 Wohlers
 * Gothic 0.81
 * 
 * 9     8.05.00 23:08 Edenfeld
 * 
 * 6     8.05.00 22:30 Wohlers
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
 * 21    19.04.00 16:44 Wohlers
 * Bug-Fixes
 * 
 * 20    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 19    7.04.00 19:16 Wohlers
 * Day and Hour werden an Cutscenes uebergeben
 * 
 * 18    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 17    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 16    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 15    23.02.00 3:47 Wohlers
 * Fixes
 * 
 * 14    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 13    22.02.00 20:37 Wohlers
 * 
 * 12    6.02.00 18:42 Wohlers
 * Various Fixes
 * 
 * 11    4.02.00 15:38 Wohlers
 * Bugfixes 
 * 
 * 10    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 9     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 8     20.12.99 20:39 Wohlers
 * ParticleControl angepasst
 * Ani-Probs (Jump/Climb) gefixed
 * 
 * 7     7.12.99 22:09 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 6     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// TODO : An jedem neuen Tag das "cutscene->activ" 
// wieder auf FALSE für alle Tagesablaufpunkte mit Cutscene setzen

#include "zCore.h"

#include "zBuffer.h"
#include "zEventMan.h"
#include "zWaynet.h"
#include "zCCSManager.h"
#include "zCCSPlayer.h"
#include "zCCSPool.h"

#include "oNpc.h"
#include "oNpcStates.h"
#include "oNpcMessages.h"
#include "oMobInter.h"
#include "oAIHuman.h"
#include "oRoutine.h"
#include "oWorld.h"
#include "oGame.h"
#include "oCSPlayer.h"

#include "zAccount.h" 

// Globals
static int parOtherIndex	= -1;
static int parVictimIndex	= -1;
static int parItemIndex		= -1;
extern zBOOL s_bCheckRoutines;
extern zBOOL g_bDontKillOUSound;

static zSTRING strLastError;

// Zustaende, die fuer den Spieler freigeschaltet sind...
const int NPC_PLAYER_STATES_ENABLED_MAX = 9;

const zSTRING strPlayerStatesEnabled[NPC_PLAYER_STATES_ENABLED_MAX] = {
	"ZS_ASSESSMAGIC",
	"ZS_ASSESSSTOPMAGIC",
	"ZS_MAGICFREEZE",
	"ZS_WHIRLWIND",		// [BENDLIN] Addon FIXME
	"ZS_SHORTZAPPED",
	"ZS_ZAPPED",
	"ZS_PYRO",
	"ZS_MAGICSLEEP"
//	"ZS_MAGICBURN"
};

static int playerStatesEnabled[NPC_PLAYER_STATES_ENABLED_MAX] = { -1,-1,-1,-1,-1,-1 };

TNpcAIState	:: TNpcAIState ()
{
	index			= 0;
	loop			= 0;
	end				= 0;	
	timeBehaviour	= AITIME_NO;
	restTime		= 0.0f;
	phase			= -1;
	valid			= FALSE;
	stateTime		= 0.0f;
	prgIndex		= -1;
	isRtnState		= FALSE;
};

TNpcAIState	:: ~TNpcAIState ()
{
};

oCNpc_States :: oCNpc_States ()
{
	npc					= NULL;
	lastAIState			= 0;
	// Daily Routine
	hasRoutine			= FALSE;					// Any Routine Entrys available ?
	rtnChanged			= FALSE;
	rtnBefore			= NULL;						// Temp ? Used for Cutscene-Usage
	rtnNow				= NULL;						// Current Routine
	rtnRoute			= NULL;						// Route from "rtnBefore" to "rtnNow"
	rtnOverlay			= FALSE;					// In Routine Overlay ?
	rtnOverlayCount		= 0;						// How many Entries left ?
	startNewRoutine		= FALSE;
	walkmode_routine	= 0;
	weaponmode_routine	= 0;
	// aiStateDriven
	aiStateDriven		= 0;
	aiStatePosition		= zVEC3(0,0,0);
	// Parser-Vars
	parOther			= NULL;
	parVictim			= NULL;
	parItem				= NULL;
	// Temp, only for debugging purposes	
	rntChangeCount		= 0;

	// Ermitteln der Parser-Werte vor subneuronaler Implosion
	if (parOtherIndex	< 0) parOtherIndex	= parser.GetIndex("OTHER");
	if (parVictimIndex	< 0) parVictimIndex = parser.GetIndex("VICTIM");
	if (parItemIndex	< 0) parItemIndex	= parser.GetIndex("ITEM");

	// Initialiseren der playerStatesEnabled, sofern noetig.
	if ((NPC_PLAYER_STATES_ENABLED_MAX>0) && (playerStatesEnabled[0]==-1)) {
		for (int i=0; i<NPC_PLAYER_STATES_ENABLED_MAX; i++) {
			playerStatesEnabled[i] = parser.GetIndex(strPlayerStatesEnabled[i]);
		}
	}
};

oCNpc_States :: ~oCNpc_States ()
{
	CloseCutscenes();
	rtnNow		= NULL;
	rtnMan.RemoveRoutine(npc);
	rtnBefore	= NULL;

	delete (rtnRoute);	
	rtnRoute	= NULL;
	npc			= NULL;

	// Be sure to clear script-References
	ClearParserReferences();
	
	// Parser-Vars
	parOther			= NULL;
	parVictim			= NULL;
	parItem				= NULL;
};

void oCNpc_States :: ClearParserReferences()
{
	SetParserInstanceNpc	(parOtherIndex,NULL);
	SetParserInstanceNpc	(parVictimIndex,NULL);
	SetParserInstanceItem	(NULL);
}

void oCNpc_States :: SetOwner(oCNpc* n)
{
	npc = n;
}

int oCNpc_States :: GetState()
// FIXME : Besser IsInState benutzen !!!
{
	if (curState.valid) {		
		// Prgrammgesteuert (ZS_Unconscious / ZS_Dead)
		if (curState.prgIndex < -1) return curState.prgIndex;
		// Skriptgesteuert
		return curState.index;
	} else
		return 0;
}

zBOOL oCNpc_States :: IsInState(int stateID)
{
	if (curState.valid) {
		return ((curState.index==stateID) || (curState.prgIndex==stateID));
	} else if (nextState.valid) {
		return ((nextState.index==stateID) || (nextState.prgIndex==stateID));		
	}
	return FALSE;
}

zBOOL oCNpc_States :: IsScriptStateActive()
{
	return (curState.valid && !curState.name.IsEmpty());
};

int oCNpc_States :: GetStateTime()
// Liefere StateTime in Sekunden
{
	if (curState.valid) return (int)curState.stateTime / 1000;
	else				return 0;
}

void oCNpc_States :: SetStateTime(int seconds)
// Liefere StateTime in Sekunden
{
	if (curState.valid) curState.stateTime = (zREAL)seconds * 1000;
}

// **********************************************************************************
// AI - State Handling - Skriptgesteuerte + Programmgesteuerte
// **********************************************************************************

void oCNpc_States :: SetRoutine ( oCRtnEntry* nowTA, oCRtnEntry* beforeTA )
{		
	// Schon aktiv ?
	if ((rtnNow == nowTA) && (beforeTA!=NULL) && (beforeTA==rtnBefore)) return;
	
	// Werte setzen
	if (beforeTA)	rtnBefore = beforeTA;
	else			rtnBefore = rtnNow;

	if (rtnNow && rtnNow->cutscene) rtnNow->cutscene->ResetPlayState();
	
	rtnNow = nowTA;
	delete (rtnRoute);	rtnRoute = NULL;

	// Route berechnen ( einmal, um bei der TA-Vorausberechnung immer darauf zurückgreifen zu können. )
	if (rtnBefore && rtnNow) rtnRoute = ogame->GetWorld()->GetWayNet()->FindRoute(rtnBefore->GetWaypoint(), rtnNow->GetWaypoint(), npc);
	if (!rtnRoute) {
		//zERR_WARNING("U:AI: Failed to calculate Routine-Route :"+npc->GetInstanceName());
	};

	rntChangeCount = 0;

    if (rtnNow)
    	npc->wpname	= rtnNow->GetWaypoint();
}

zBOOL oCNpc_States :: StartRtnState (zBOOL force)
{
	if (npc->IsSelfPlayer()) return TRUE;
	
	SetStartNewRoutine				(FALSE);		// Aus, weil sonst Ringschluss möglich
	zBOOL res = ActivateRtnState	(force);
	SetStartNewRoutine				(!res);
	rntChangeCount++;
	if (rntChangeCount>10) {
//		zERR_WARNING("U:NPC: Tried several time to activate routine state : "+npc->GetInstanceName());
	}
	return res;
}

zBOOL oCNpc_States :: ActivateRtnState (zBOOL force)
{
	// Der Spieler macht hier gar nichts
	if (npc->IsSelfPlayer())				return FALSE;
	if (!oCNpc::IsScriptStateAIEnabled())	return FALSE;
	if (!npc->IsConditionValid()) {
		strLastError = "Condition not valid.";
		return FALSE;
	}
	if (npc->GetEM()->GetCutsceneMode()) {
		if (!force) {	
			strLastError = "In Cutscene Mode.";
			return FALSE;
		} else if (npc->GetEM()->GetCutscene()) {
			// Falls geforced, auch Cutscene beenden.
			npc->GetEM()->GetCutscene()->Stop();
		}
	}

	if (HasRoutine()) {
		// Tagesablauf
		if (!rtnNow) {
			strLastError = "No current Routine.";
			return FALSE;
		}
		if (!force) {
			if (!npc->GetEM()->IsEmpty(TRUE)) {
				strLastError = "EM not empty.";
				return FALSE;
			}
			if (GetState()==rtnNow->GetState()) return TRUE;	// Zustand ist bereits aktiv, deshalb hier True zurueck...	
			if (!IsInRoutine()) {
				strLastError = "No routine state currently running.";
				return FALSE;
			}
		}

		npc->wpname	= rtnNow->GetWaypoint();

		// Cutscenes weg, nur bei Änderung des Tagesablaufzustandes		

		if (!rtnBefore) zERR_WARNING("U: NPC: rtnBefore unknown");

		if (rtnBefore && npc->GetHomeWorld())
		{
			zCCSCutsceneContext* csContext = npc->GetHomeWorld()->GetCutscenePlayer()->GetStartedCutscene(npc);
			if (csContext && rtnBefore->cutscene) 
			{				
				if (csContext->AreU( rtnBefore->cutscene->csName )) csContext->Stop();
			}
		}	

		rtnChanged = FALSE;
		return StartAIState (rtnNow->GetState(), TRUE, AITIME_NO, 0.0f, TRUE); 
	
	} else if (IsAIStateDriven()) {
		//
		//	CODECHANGE [ROMAN]
		//
		if (force) { curState.valid = FALSE; nextState.valid = FALSE; } 
		//
		//	CODECHANGE [ROMAN] END
		//

		if (curState.valid || nextState.valid) return FALSE;
		// Zustandsgesteuert
		return StartAIState (npc->startAIState, TRUE, AITIME_NO, 0.0f); 
	}	
	return FALSE;
} 

zBOOL oCNpc_States :: StartAIState ( const zSTRING& name, zBOOL endOldState, int timeBehaviour, zREAL timed, zBOOL isRtnState )
// 1) Zustand soll nur einmal durchlaufen werden. (Blöcke a+b+c)
// 2) Zustand soll nur eine bestimmte Zeit (Loop) laufen.
// 3) Zustand soll unendlich laufen, bis eine Wahrnehmung diesen unterbricht.
// 4) Zustand ist nicht in den Skripten definiert, sondern Programmcode.
// 5) Falls der Zustand beendet wurde (TimeOut, ReturnWert) wird wieder der Tagesablauf gestartet.
{
	// String = kann nur ein Skriptzustand sein ?
	int index = parser.GetIndex(name);
	if (index<=0) {
		zERR_WARNING("U:AI: Scriptstate "+name+" not found.");
		return FALSE;
	}
	return StartAIState(index, endOldState, timeBehaviour, timed);
}

zBOOL oCNpc_States :: StartAIState( int index, zBOOL endOldState, int timeBehaviour, zREAL timed, zBOOL isRtnState)
{
	if (!oCNpc::IsScriptStateAIEnabled())	return FALSE;
	
	// Innerhalb von Cutscenes werden keine Statewechsel gemacht !
	// aber schon innerhalb von OUs.
	if (npc->GetEM()->GetCutscene()) {
		if (!static_cast<zCCSCutsceneContext*>(npc->GetEM()->GetCutscene())->IsCutscene()) {
			// OU beenden und Cutscene-Mode weg.
			CloseCutscenes();
			/*
			if (npc->GetEM()->GetCutscene()!=NULL) {
				zERR_FAULT("U:TMP: Fatal : Cutscene (OU) was not correctly stopped.");
			}
			*/

		} else {
			// Keine Zustandswechsel in Cutscenes !
			strLastError = "Cutscene mode active.";
			return FALSE;
		}
	}

	zBOOL	interrupt = TRUE;

	if (index>=0) {
		zSTRING stateName;
		int		type,ele;	
		stateName = parser.GetSymbolInfo(index,type,ele);
		// Skriptgesteuert : ZS_ oder B_
		if (stateName.Search("ZS_")==0) {
			// ZS_ Skriptgesteuert
			nextState.prgIndex	= 0;
			nextState.name		= stateName;
			nextState.index		= index;
			nextState.loop		= parser.GetIndex(nextState.name + "_LOOP");
			nextState.end		= parser.GetIndex(nextState.name + "_END");

		} else {
			// Nur ein Befehl -> sofort ausführen
			// [Wohlers] Rtn-Flag kurz ausblenden, weil Wahrnehmung B_ moeglicherweise
			// aus Skripte kommt (AtHome)
			int oldRtnState		= curState.isRtnState;
			curState.isRtnState = isRtnState;
			parser.SetInstance	("SELF",npc);
			parser.CallFunc		(index);
			curState.isRtnState = oldRtnState;
			return TRUE;			
		}

	} else if ((index<-1) && (index>-NPC_AISTATE_PRG_MAX)) {
		// Programmgesteuert
		nextState.prgIndex	= index;
		nextState.name		= npcStatesPrg[-index];
		nextState.index		= parser.GetIndex(nextState.name);
		nextState.loop		= parser.GetIndex(nextState.name + "_LOOP");
		nextState.end		= parser.GetIndex(nextState.name + "_END");
	
	} else {
		// Error, State not found
		zERR_WARNING("U:NPC: "+npc->GetInstanceName() + ": Illegal AI-State"+zSTRING(index)+" not found.");
		return FALSE;
	}

	// LookAt aus,,
	// Auf Geheiss von Stefan am 23.11.00 rausgenommen.
	// npc->GetAnictrl()->StopLookAtTarget();

	// Other setzen
	oCNpc*			tmpNpc	= NULL;
	zCPar_Symbol*	sym		= parser.GetSymbol(parOtherIndex);
	if (sym)		tmpNpc	= dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
	SetParserInstanceNpc (parOtherIndex, tmpNpc);

	// Victim setzen
	tmpNpc					= NULL;
	sym						= parser.GetSymbol(parVictimIndex);
	if (sym)		tmpNpc	= dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
	SetParserInstanceNpc (parVictimIndex, tmpNpc);	
	
	// Item setzen
	oCItem*		tmpItem		= NULL;
	sym						= parser.GetSymbol(parItemIndex);
	if (sym)	tmpItem		= dynamic_cast<oCItem*>((zCVob*)sym->GetInstanceAdr());
	SetParserInstanceItem (tmpItem);	

	nextState.timeBehaviour	= timeBehaviour;
	nextState.phase			= -1;					// not yet initialised
	nextState.valid			= TRUE;					// yes, use it.
	nextState.isRtnState	= isRtnState;

	if (endOldState) {
		// Alten Zustand noch entsprechend beenden.
		curState.phase = 1;

	} else if (interrupt) {
		// Abbrechen
		curState.phase = 2;
		curState.valid = FALSE;
		// FIXME : Ist das korrekt so ?
		// [EDENFELD]: Das Override Flag hat hier ab 1.24d keine Bedeutung mehr
		// hätte urbsprünglich bedeutet, das beim Abbrechen eine ZS noch AI Befehle in der Queue stehen dürfen, wenm
		// der nächste ZS erreicht ist
		// macht aber keinen Sinn, da man auf Skript Ebene eh die Kontrolle darüber hat.
		// Will sagen: es ist besser hier davon auszugehen, daß hier Aktionen immer beendet werden (Ausnahme seit Gothic 1: Mob- und Iteminteraktionen)
		if (!npc->GetInteractMob() && !npc->GetInteractItem() /*&&!npc->GetBodyStateInterruptableOverride()*/) {
			// Interagiert ein NSC mit einem MOBSI und es soll ein Statewechsel stattfinden, muss
			// a) keine Abmeldung vom Mobsi erfolgen, weil
			// b) das Skript dafuer die verantwortung hat ( per AI_StandUp )
			if (!npc->IsAPlayer() || CanPlayerUseAIState(nextState))
			{
				npc->GetModel()->StopAnisLayerRange();
				npc->Interrupt();
				npc->ClearEM();
			}
		}
		// 
	}

	// Nur DoAIState ausführen, wenn er nicht am Schlafen ist, 
	// NSC kann aufgrund der TA-Vorausberechnung noch nicht in der Welt sein
	if (npc->GetSleeping() || !npc->GetHomeWorld()) return FALSE;
	
	return DoAIState();
}


zBOOL oCNpc_States :: CanPlayerUseAIState(const TNpcAIState& state)
// Ist der Currrent State fdür den Spieler erlaubt
// zB. : Unconscious
{
	if (state.valid) {
		
		if (state.prgIndex<-1) {
			// Programmgesteuerte Zustaende, die fuer den Spieler erlaubt sind.
			return ((state.prgIndex == NPC_AISTATE_UNCONSCIOUS)
				||	(state.prgIndex == NPC_AISTATE_DEAD));
		
		} else {
				
			// Skriptgesteuerte Zustaende, die fuer den Spieler erlaubt sind.
			for (int i=0; i<NPC_PLAYER_STATES_ENABLED_MAX; i++) {
				if (state.index == playerStatesEnabled[i]) return TRUE;
			}
		}
	}
	return FALSE;
}


zBOOL oCNpc_States :: CanPlayerUseAIState()
// Ist der Currrent State fdür den Spieler erlaubt
// zB. : Unconscious
{
	if (curState.valid) {
		
		if (curState.prgIndex<-1) {
			// Programmgesteuerte Zustaende, die fuer den Spieler erlaubt sind.
			return ((curState.prgIndex == NPC_AISTATE_UNCONSCIOUS)
				||	(curState.prgIndex == NPC_AISTATE_DEAD));
		
		} else {
				
			// Skriptgesteuerte Zustaende, die fuer den Spieler erlaubt sind.
			for (int i=0; i<NPC_PLAYER_STATES_ENABLED_MAX; i++) {
				if (curState.index == playerStatesEnabled[i]) return TRUE;
			}
			ClearAIState();
		}
	}
	return FALSE;
}

zBOOL oCNpc_States :: DoAIState ()
{
	// State Time weiterrechnen ( nur im Loop ! )
	if (curState.valid && (curState.phase==0)) curState.stateTime += ztimer.GetFrameTimeF();
	
	// AI - Disabled
	if (!oCNpc::IsScriptStateAIEnabled()) return FALSE;
	
	// Output-Units durchlassen ? Kann eigentlich nur beim Statewechsel passieren.
	if (npc->GetEM()->GetCutscene() && static_cast<zCCSCutsceneContext*>(npc->GetEM()->GetCutscene())->IsCutscene()) return FALSE;

	// Nur starten, wenn der AI-Manager leer ist (ignore Overlays)
	if ( npc->GetEM()->IsEmpty(TRUE) ) 
	{
		// Falls neue Routine gestartet werden soll, dieses jetzt hier tun
		if (startNewRoutine && IsInRoutine() && !npc->IsSelfPlayer()) {
			StartRtnState();
		}

		if (!curState.valid) {
			if (nextState.valid) {
				// Zuletzt aktiven State merken
				lastAIState			= curState.index;
				// nachrückenden State aktivieren
				curState.valid		= TRUE;
				curState.index		= nextState.index;				
				curState.loop		= nextState.loop;
				curState.end		= nextState.end;
				curState.phase		= nextState.phase;
				curState.name		= nextState.name;
				curState.prgIndex	= nextState.prgIndex;
				curState.isRtnState = nextState.isRtnState;
				curState.stateTime	= 0.0f;
				// perceptions löschen
				nextState.valid = FALSE;
				npc -> ClearPerception();
				
			} else {

				// Tagesablauf aktivieren
				StartRtnState();
			}
		}

		// Falls es der Spieler ist, muss der curState auch 
		// ein Zustand sein, der fuer den Spieler erlaubt ist
		if (npc->IsSelfPlayer() && !CanPlayerUseAIState()) return FALSE;
		
		if (curState.valid) {
		
			parser.SetInstance("SELF"			,npc);
			parser.SetInstance(parOtherIndex	,parOther);
			parser.SetInstance(parVictimIndex	,parVictim);
			parser.SetInstance(parItemIndex		,parItem);	

			// ***********************
			// *** Skriptgesteuert ***
			// ***********************
			if (curState.phase == -1) {
				// Bei neuen Zustand wird die perceptionTime 
				// wieder auf Default gesetzt
				npc->SetPerceptionTime(5000);
				// Vorbereitungsphase
				if (curState.index>0) parser.CallFunc(curState.index);
				// PRogrammgesteuert
/*				else if (curState.prgIndex < 0) {					
					switch (curState.prgIndex) {
							
							case NPC_AISTATE_FOLLOW		:	{	// TMP : 
																if (npc->GetLeader()) npc->RbtInit(npc->GetLeader()->GetPositionWorld(),npc->GetLeader());
															}
					};
				}
*/
				
				curState.phase = 0;
			
			} else if (curState.phase == 0) {
				// Looping
				zBOOL end = FALSE;
				if (curState.loop>0)		end = *(zBOOL*)parser.CallFunc(curState.loop);
				else						end = TRUE;

				// *************************
				// *** Programmgesteuert ***
				// *************************
				if (curState.prgIndex < 0) {					
					switch (curState.prgIndex) {
							
						case NPC_AISTATE_FOLLOW			:	npc->Follow				(); end = FALSE;	break;
						case NPC_AISTATE_UNCONSCIOUS	:	npc->CheckUnconscious	();					break;	
						//						case NPC_AISTATE_FADEAWAY	:	npc->FadeAway	(); end = FALSE;						break;
						
					};
				}

				// Loop zuende, nächste Phase einleiten.
				if (end) 					curState.phase = 1;

			} else if (curState.phase == 1) {
				
				// Nachbereitungsphase
				if (curState.end>0)			parser.CallFunc (curState.end);
				curState.phase	= 2;
				curState.valid	= FALSE;
			}	
			
		}
	}

	// Timing + CS
	if (curState.valid && (curState.phase==0)) {
		
		// *******************
		// Cutscene starten ?
		// *******************
		if (IsInRoutine() && rtnNow && rtnNow->cutscene && npc->GetHomeWorld()) 
		{
			zBOOL wasPlayed = ogame->GetCutsceneManager()->PoolHasFlags(rtnNow->cutscene->csName,CS_PLAYED);			
			zBOOL isPlaying = ogame->GetCutsceneManager()->PoolHasFlags(rtnNow->cutscene->csName,CS_PLAYING);			

			// Hier eine eventuelle CS aktivieren (NSC anmelden)			
			if ( !isPlaying && (rtnNow->cutscene->ignorePlayState || !wasPlayed) )
			{
				oCRtnCutscene* cutscene	= rtnNow->cutscene;
				zBOOL inMovement		= npc->GetInMovement();

				if (inMovement)	npc->EndMovement();
				
				zCCSCutsceneContext* cs = npc->GetHomeWorld()->GetCutscenePlayer()->StartCutscene(cutscene->csName, npc);
				if (cs) rtnNow->cutscene->ignorePlayState = cs->ReplayCutscene();
				
				// Hier kann auch Null geliefert werden,
				// Der CS-Player kümmert sich um Fehlverhalten
				// ->also hier keine zusätzliche Warning nötig
				if (inMovement) npc->BeginMovement();
			}
		}

		// ***************
		// Time Behaviour 
		// ***************
		switch (curState.timeBehaviour) {
			
			case AITIME_ONCE	:	curState.phase		 = 1;		break;
			case AITIME_TIMED	:	curState.restTime	-= ztimer.GetFrameTimeF();
									if (curState.restTime < 0.0f) curState.phase = 1;
									break;
			case AITIME_NO		:	break;	// Do nothing
		
		}

	}

	return TRUE;
}

void oCNpc_States :: ClearAIState()
{
	curState.valid		= FALSE;
	curState.index		= -1;
	curState.prgIndex	= -1;
	curState.phase		= -1;
	curState.name.Clear();
	nextState.valid		= FALSE;
	nextState.index		= -1;
	nextState.prgIndex	= -1;
	nextState.phase		= -1;
	nextState.name.Clear();
};

void oCNpc_States :: EndCurrentState()
{
	if (curState.valid) {
		curState.phase = 1;		
		DoAIState();
	}
};

// **********************************************************************************
// Cutscene
// **********************************************************************************


zBOOL oCNpc_States :: IsInRoutine()
{
	if (curState.valid && curState.isRtnState)	return TRUE;
	// Noch nichts initialisiert ?
	if (!curState.valid && !nextState.valid)	return TRUE;
	return FALSE;
}

zBOOL oCNpc_States :: IsInCutscene()
{
	return npc->GetEM()->GetCutsceneMode();
}

void oCNpc_States :: StartOutputUnit(int csNumber)
{
	if (!npc->GetHomeWorld()) return;
	// unnötige Zuweisung zCCSCutsceneContext* cs = 

	npc->GetHomeWorld()->GetCutscenePlayer()-> StartOutputUnit (csNumber, npc);
}

void oCNpc_States :: StartCutscene(const zSTRING& csName, const zSTRING& roleName)
{
	if (!npc->GetHomeWorld()) return;
	npc->GetHomeWorld()->GetCutscenePlayer()->StartCutscene((zSTRING)csName, npc);
}

void oCNpc_States :: CloseCutscenes()
{
	// Falls er gerade in einer Cutscene ist :
	if (npc->GetEM()->GetCutsceneMode()) {
		npc->StopFaceAni("VISEME");	
	}
	
	// Spielt gerade eine Cutscene? Dann beenden!
	zCCutscene* cs = npc->GetEM()->GetCutscene();
	if (cs) cs->Stop();
		
	// Schlummernde Cutscene beenden
	if (!npc->GetHomeWorld()) return;
	cs = npc->GetHomeWorld()->GetCutscenePlayer()->GetStartedCutscene(npc);
	if (cs) cs->Stop();
}

void oCNpc_States :: SetParserInstanceNpc ( int index, oCNpc* npc )
{
	if (index == parOtherIndex) {

		if (parOther!=npc) {
			zRELEASE_ACCT(parOther);
			parser.SetInstance(index,npc);
			parOther = npc;
			if (npc) zADDREF_ACCT(npc);
		}

	} else if (index == parVictimIndex) {
		
		if (parVictim!=npc) {
			zRELEASE_ACCT(parVictim);
			parser.SetInstance(index,npc);
			parVictim = npc;
			if (npc) zADDREF_ACCT(npc);	
		}
	}
}

void oCNpc_States :: SetParserInstanceItem ( oCItem* item )
{
	if (item!=parItem) {
		parser.SetInstance(parItemIndex,item);
		
		zRELEASE(parItem);
		parItem = item;
		
		if (item) item->AddRef();
	}
}

// **********************************************************************************
// Daily Routine
// **********************************************************************************

void oCNpc_States :: InitRoutine ()
{
	rtnBefore	= NULL;
	rtnNow		= NULL;
	if (npc->daily_routine != 0) {
		parser.SetInstance		("SELF",npc);
		parser.CallFunc			(npc->daily_routine);
		if (ogame->GetWorld()->GetWayNet()) rtnMan.CreateWayBoxes(npc);
	}
}

void oCNpc_States :: ChangeRoutine(const zSTRING& routineName)
{
	zSTRING name = routineName;
	name = "RTN_"+name+"_"+zSTRING(npc->idx);
	ChangeRoutine(parser.GetIndex(name));
}

void oCNpc_States :: ChangeRoutine(int newRoutineFunc)
{
	if (newRoutineFunc>0) {
		// Alte daily - Routine - Eintrage + WayBoxes löschen
		rtnMan.RemoveRoutine	(npc);
		// Auf neue Daily Routine setzen
		npc -> daily_routine	= newRoutineFunc;
		InitRoutine				();
		// Restart Single Routine
		rtnMan.UpdateSingleRoutine	(npc);
		zerr.Message("U:RTN:Routine change :"+npc->GetInstanceName());

	} else 
		zerr.Warning("U:RTN:Routine change failed:"+npc->GetInstanceName());
}

zSTRING oCNpc_States :: GetRoutineName ( )
{
	if (npc->daily_routine>0) {
		zCPar_Symbol* sym = parser.GetSymbol(npc->daily_routine);
		if (sym)	return sym->name;
	}
	return "";
}

void oCNpc_States :: BeginInsertOverlayRoutine	()
{
	// Alte Routine erstmal raus

	//[EDENFELD] 1.09  Wenn bereits einer aktiv ist, sollte er rausgeworfen werden
	if (rtnOverlayCount > 0)
	{
		RemoveOverlay();
	}

	rtnMan.RemoveRoutine(npc);
	rtnOverlay		= TRUE;
	rtnOverlayCount = 0;
	rtnNow			= NULL;
	rtnBefore		= NULL;
}

void oCNpc_States :: StopInsertOverlayRoutine	()
{
	if (rtnBefore) {
		int h1 = rtnBefore->hour2;
		int m1 = rtnBefore->min2;
		
		oCRtnEntry* entry	= zNEW( oCRtnEntry(h1,m1,h1,m1,-1,rtnBefore->GetWaypoint()) );
		entry->npc			= npc;
		entry->overlay		= rtnOverlay;
		rtnMan.Insert(npc,entry);
	}

	// Overlay-Routine berechnen
	rtnMan.CreateWayBoxes		(npc);
	rtnMan.UpdateSingleRoutine	(npc);
	rtnOverlay = FALSE;
}

void oCNpc_States :: RemoveOverlayEntry (oCRtnEntry* entry)
{
	// Overlay-Tagesablaufeintrag raus 
	if (entry && entry->overlay) {
		rtnMan.RemoveEntry(entry);
		rtnOverlayCount--;
		if (rtnOverlayCount<=0) {
			InitRoutine();	
			rtnNow = NULL;
			rtnMan.UpdateSingleRoutine(npc);
		} else if (rtnNow==entry) {
			rtnNow = NULL;
		}
	}
}

void oCNpc_States :: RemoveOverlay()
// Removes full overlay - Routine
{
	rtnOverlayCount = 0;
	rtnMan.RemoveOverlay(npc);
	InitRoutine();
	rtnNow = NULL;
	rtnMan.UpdateSingleRoutine(npc);
}

void oCNpc_States :: InsertRoutine	( int h1, int m1, int h2, int m2, int func, const zSTRING &s, int instance )
{
	// Ja, der Typ hat nen Tagesablauf
	hasRoutine = TRUE;
	// Erzeugen
	if (rtnOverlay) {
		int timeHour, timeMin;
		// Aktuelle Zeit holen
		ogame->GetWorldTimer()->GetTime(timeHour,timeMin);
		// Absolute Zeit aus Delta-Zeit-Angaben errechnen
		int dh = timeHour;	
		int dm = timeMin;
		oCWorldTimer::AddTime(dh,dm,h1,m1);
		h1 = dh; m1 = dm;
		oCWorldTimer::AddTime(timeHour,timeMin,h2,m2);
		h2 = timeHour;
		m2 = timeMin;
		rtnOverlayCount++;
	}
	
	// TEMP : Test for unavailable Waypoints / Freepoints
/*	zVEC3		pos (0,0,0);
	zCVob*		vob = NULL;
	zCWaypoint* wp	= ogame	-> GetWorld()->GetWayNet()->GetWaypoint(s);
	if (!wp && !ogame -> GetWorld()->SearchVobByName(s) ) {
		zERR_FAULT("U: NPC: Waypoint in NPC-Routine not found. NPC : "+npc->GetInstanceName()+" / WP :"+s);
	}
*/
	oCRtnEntry* entry	= zNEW( oCRtnEntry(h1,m1,h2,m2,func,s) );
	entry->overlay		= rtnOverlay;
	// Eintragen
	rtnMan.Insert(npc,entry);
	rtnBefore = entry;	// Wichtig, hiermit wird in StopInsertOverlay gearbeitet.

	if (s_bCheckRoutines) rtnMan.CheckConsistency(npc);
}

void oCNpc_States :: InsertRoutineCS( const zSTRING &csName, const zSTRING& roleName )
{
	if (rtnBefore) {
		oCRtnCutscene* cs = zNEW( oCRtnCutscene() );
		cs -> csName			= csName;		cs -> csName.Upper();
		if (cs->csName.Search(".")<=0) cs->csName += ".CS";
		cs -> roleName			= roleName;		cs -> roleName.Upper();
		cs -> npc				= npc;
		cs -> active			= FALSE;
		rtnBefore -> cutscene	= cs;
	};
}

int	oCNpc_States :: GetLastRoutineState ()
{
	if (rtnNow)	return rtnNow->GetState();	
	else		return 0;
}

int	oCNpc_States :: GetLastState ()
{
	return lastAIState;
}

// *********************************
// State - Driven
// *********************************

zBOOL oCNpc_States :: IsAIStateDriven ()
{
	return (!HasRoutine() && (npc->startAIState>0));
};

void oCNpc_States :: InitAIStateDriven	(const zVEC3& posPoint)
{
	aiStatePosition = posPoint;
	zCWaypoint* wp	= ogame->GetWorld()->GetWayNet()->GetNearestWaypoint((zVEC3)posPoint);
	if (wp) npc->wpname = wp->GetName();
};

const zVEC3& oCNpc_States :: GetAIStatePosition()
{
	return aiStatePosition;
};

// *********************************
//		Debug
// *********************************

zSTRING	oCNpc_States :: GetStateInfo ()
{
	zSTRING s;
//	if (curState.valid) {
		s = curState.name;
		if (curState.phase == 0) s+="_LOOP";
		if (curState.phase == 1) s+="_END";
		if (curState.phase == 2) s+="_INTERRUPT";
//	}
	s+="/";
	if (IsInRoutine())	s+="R/";
	if (IsInCutscene())	s+="CS/";
	s += "("+zSTRING(GetStateTime())+")";
	s += " Ref:"+zSTRING(npc->GetRefCtr());
	return s;
}

zSTRING oCNpc_States :: GetLastError()
{
	return strLastError;
}

void oCNpc_States :: Archive (zCArchiver& arc)
{
	if (!arc.InSaveGame())	return;

	arc.WriteBool	("curState.valid"		,curState.valid);
	arc.WriteString	("curState.name"		,curState.name);
	arc.WriteInt	("curState.prgIndex"	,curState.prgIndex);		
	arc.WriteBool	("curState.isRtnState"	,curState.isRtnState);

	arc.WriteBool	("nextState.valid"		,nextState.valid);
	arc.WriteString	("nextState.name"		,nextState.name);
	arc.WriteInt	("nextState.prgIndex"	,nextState.prgIndex);		
	arc.WriteBool	("nextState.isRtnState"	,nextState.isRtnState);

	arc.WriteInt	("lastAIState"			,lastAIState);
	arc.WriteBool	("hasRoutine"			,hasRoutine);
	arc.WriteBool	("rtnChanged"			,rtnChanged);
	arc.WriteBool	("rtnOverlay"			,rtnOverlay);				
	arc.WriteInt	("rtnOverlayCount"		,rtnOverlayCount);		
	arc.WriteInt	("walkmode_routine"		,walkmode_routine);
	arc.WriteBool	("weaponmode_routine"	,weaponmode_routine);
	arc.WriteBool	("startNewRoutine"		,startNewRoutine);
	arc.WriteInt	("aiStateDriven"		,aiStateDriven);
	arc.WriteVec3	("aiStatePos"			,aiStatePosition);

	if (rtnOverlayCount>0) {
		rtnMan.WriteRoutine(arc,npc,TRUE);
	}
};

void oCNpc_States :: Unarchive (zCArchiver& arc)
{
	if (!arc.InSaveGame())	return;

	curState.phase = -1;
	arc.ReadBool	("curState.valid"		,curState.valid);
	arc.ReadString	("curState.name"		,curState.name);
	arc.ReadInt		("curState.prgIndex"	,curState.prgIndex);		
	arc.ReadBool	("curState.isRtnState"	,curState.isRtnState);

	// Zustand ueber den Namen wieder aufloesen
	if ((curState.prgIndex<-1) && (curState.prgIndex>-NPC_AISTATE_PRG_MAX)) curState.name= npcStatesPrg[-curState.prgIndex];
	curState.index		= parser.GetIndex(curState.name);
	curState.loop		= parser.GetIndex(curState.name + "_LOOP");
	curState.end		= parser.GetIndex(curState.name + "_END");
	if (curState.valid && (curState.index==-1)) zERR_FAULT("U:NPC: Cannot reinitialize AI-State of "+npc->GetInstanceName()+". ScriptState : "+curState.name );

	nextState.phase = -1;
	arc.ReadBool	("nextState.valid"		,nextState.valid);
	arc.ReadString	("nextState.name"		,nextState.name);
	arc.ReadInt		("nextState.prgIndex"	,nextState.prgIndex);		
	arc.ReadBool	("nextState.isRtnState"	,nextState.isRtnState);
	
	// Zustand ueber den Namen wieder aufloesen
	if ((nextState.prgIndex<-1) && (nextState.prgIndex>-NPC_AISTATE_PRG_MAX)) nextState.name = npcStatesPrg[-nextState.prgIndex];
	nextState.index		= parser.GetIndex(nextState.name);
	nextState.loop		= parser.GetIndex(nextState.name + "_LOOP");
	nextState.end		= parser.GetIndex(nextState.name + "_END");

	arc.ReadInt		("lastAIState"			,lastAIState);
	arc.ReadBool	("hasRoutine"			,hasRoutine);
	arc.ReadBool	("rtnChanged"			,rtnChanged);
	arc.ReadBool	("rtnOverlay"			,rtnOverlay);				
	arc.ReadInt		("rtnOverlayCount"		,rtnOverlayCount);		
	arc.ReadInt		("walkmode_routine"		,walkmode_routine);;
	arc.ReadBool	("weaponmode_routine"	,weaponmode_routine);
	arc.ReadBool	("startNewRoutine"		,startNewRoutine);
	arc.ReadInt		("aiStateDriven"		,aiStateDriven);
	arc.ReadVec3	("aiStatePos"			,aiStatePosition);

	if (rtnOverlayCount>0) {
		rtnMan.ReadRoutine(arc,npc);
	}
	
	rtnMan.FindRoutine(npc,rtnNow,rtnBefore);
}

/* Old Ones - Saving parser Indizes - Wrong !

// archive
void oCNpc_States :: Archive (zCArchiver& arc)
{
	// FIXME : SaveGame-Mode
	// Keine Basisklasse vorhanden !
	if (!arc.InSaveGame())	return;

	zCPar_Symbol *symbol = parser.GetSymbol( curState.index );
	if( symbol ) arc.WriteString("curState.index", symbol->name );
	else arc.WriteString("curState.index", "" );
	symbol = parser.GetSymbol( curState.loop );
	if( symbol ) arc.WriteString("curState.loop", symbol->name );
	else arc.WriteString("curState.loop", "" );
	symbol = parser.GetSymbol( curState.end );
	if( symbol ) arc.WriteString("curState.end", symbol->name );
	else arc.WriteString("curState.end", "" );
	
	arc.WriteInt("curState.timeBehaviour",curState.timeBehaviour);
	arc.WriteFloat("curState.restTime",curState.restTime);
//	arc.WriteInt("curState.phase",curState.phase);;
	arc.WriteBool("curState.valid",curState.valid);
	arc.WriteString("curState.name",curState.name);
	arc.WriteFloat("curState.stateTime",curState.stateTime);
	arc.WriteInt("curState.prgIndex",curState.prgIndex);		
	arc.WriteBool("curState.isRtnState",curState.isRtnState);

	symbol = parser.GetSymbol( nextState.index );
	if( symbol ) arc.WriteString("nextState.index", symbol->name );
	else arc.WriteString("nextState.index", "" );
	symbol = parser.GetSymbol( nextState.loop );
	if( symbol ) arc.WriteString("nextState.loop", symbol->name );
	else arc.WriteString("nextState.loop", "" );
	symbol = parser.GetSymbol( nextState.end );
	if( symbol ) arc.WriteString("nextState.end", symbol->name );
	else arc.WriteString("nextState.end", "" );
	
	arc.WriteInt	("nextState.timeBehaviour"	,nextState.timeBehaviour);
	arc.WriteFloat	("nextState.restTime"		,nextState.restTime);
//	arc.WriteInt	("nextState.phase"			,nextState.phase);;
	arc.WriteBool	("nextState.valid"			,nextState.valid);
	arc.WriteString	("nextState.name"			,nextState.name);
	arc.WriteFloat	("nextState.stateTime"		,nextState.stateTime);
	arc.WriteInt	("nextState.prgIndex"		,nextState.prgIndex);		
	arc.WriteBool	("nextState.isRtnState"		,nextState.isRtnState);

	arc.WriteInt	("lastAIState"				,lastAIState);
	arc.WriteBool	("hasRoutine"				,hasRoutine);
	arc.WriteBool	("rtnChanged"				,rtnChanged);
	arc.WriteBool	("rtnOverlay"				,rtnOverlay);				
	arc.WriteInt	("rtnOverlayCount"			,rtnOverlayCount);		
	arc.WriteInt	("walkmode_routine"			,walkmode_routine);
	arc.WriteBool	("weaponmode_routine"		,weaponmode_routine);
	arc.WriteBool	("startNewRoutine"			,startNewRoutine);
	arc.WriteInt	("aiStateDriven"			,aiStateDriven);
	arc.WriteVec3	("aiStatePos"				,aiStatePosition);

	if (rtnOverlayCount>0) {
		rtnMan.WriteRoutine(arc,npc,TRUE);
	}
//	rtnMan.FindRoutine(npc,rtnNow,rtnBefore);
}

void oCNpc_States :: Unarchive (zCArchiver& arc)
{
	// FIXME : SaveGame-Mode
	// Keine Basisklasse vorhanden !
	if (!arc.InSaveGame())	return;

	zSTRING temp;
	arc.ReadString( "curState.index", temp );
	curState.index = parser.GetIndex(temp);
	arc.ReadString( "curState.loop", temp );
	curState.loop = parser.GetIndex(temp);
	arc.ReadString( "curState.end", temp );
	curState.end = parser.GetIndex(temp);
	arc.ReadInt("curState.timeBehaviour",curState.timeBehaviour);
	arc.ReadFloat("curState.restTime",curState.restTime);
//	arc.ReadInt("curState.phase",curState.phase);
	curState.phase = -1;
	arc.ReadBool("curState.valid",curState.valid);
	arc.ReadString("curState.name",curState.name);
	arc.ReadFloat("curState.stateTime",curState.stateTime);
	arc.ReadInt("curState.prgIndex",curState.prgIndex);		
	arc.ReadBool("curState.isRtnState",curState.isRtnState);

	arc.ReadString( "nextState.index", temp );
	nextState.index = parser.GetIndex(temp);
	arc.ReadString( "nextState.loop", temp );
	nextState.loop = parser.GetIndex(temp);
	arc.ReadString( "nextState.end", temp );
	nextState.end = parser.GetIndex(temp);
	arc.ReadInt		("nextState.timeBehaviour",nextState.timeBehaviour);
	arc.ReadFloat	("nextState.restTime",nextState.restTime);
//	arc.ReadInt		("nextState.phase",nextState.phase);
	nextState.phase = -1;
	arc.ReadBool	("nextState.valid",nextState.valid);
	arc.ReadString	("nextState.name",nextState.name);
	arc.ReadFloat	("nextState.stateTime",nextState.stateTime);
	arc.ReadInt		("nextState.prgIndex",nextState.prgIndex);		
	arc.ReadBool	("nextState.isRtnState",nextState.isRtnState);

	arc.ReadInt		("lastAIState",lastAIState);
	arc.ReadBool	("hasRoutine",hasRoutine);
	arc.ReadBool	("rtnChanged",rtnChanged);
	arc.ReadBool	("rtnOverlay",rtnOverlay);				
	arc.ReadInt		("rtnOverlayCount",rtnOverlayCount);		
	arc.ReadInt		("walkmode_routine",walkmode_routine);;
	arc.ReadBool	("weaponmode_routine",weaponmode_routine);
	arc.ReadBool	("startNewRoutine",startNewRoutine);
	arc.ReadInt		("aiStateDriven", aiStateDriven);
	arc.ReadVec3	("aiStatePos",aiStatePosition);

	if (rtnOverlayCount>0) {
		rtnMan.ReadRoutine(arc,npc);
	}
	
	rtnMan.FindRoutine(npc,rtnNow,rtnBefore);
}
*/

void oCNpc_States :: PackState(zCBuffer& buffer)
{	
	buffer.Write	(&curState	,sizeof(curState));
	buffer.Write	(&nextState	,sizeof(nextState));
	buffer.WriteInt	(lastAIState);
};

void oCNpc_States :: UnpackState(zCBuffer& buffer)
{
	buffer.Read		(&curState	,sizeof(curState));
	buffer.Read		(&nextState	,sizeof(nextState));
	lastAIState =	buffer.ReadInt();
}
