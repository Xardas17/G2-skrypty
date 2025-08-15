/******************************************************************************** 
 
     $Workfile:: oRoutine.cpp         $                $Date:: 24.01.01 18:37   $
     $Revision:: 38                   $             $Modtime:: 24.01.01 17:56   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oRoutine.cpp $
 * 
 * 38    24.01.01 18:37 Wohlers
 * 
 * 37    18.01.01 15:29 Wohlers
 * 
 * 36    18.01.01 2:00 Wohlers
 * 
 * 35    16.01.01 18:04 Wohlers
 * 
 * 34    9.01.01 17:09 Wohlers
 * 
 * 33    20.12.00 17:05 Wohlers
 * 
 * 32    19.12.00 17:38 Wohlers
 * 
 * 31    30.11.00 15:02 Wohlers
 * 
 * 30    9.11.00 17:10 Wohlers
 * 
 * 29    2.11.00 16:13 Speckels
 * 
 * 28    27.10.00 16:35 Wohlers
 * 
 * 27    19.10.00 21:49 Wohlers
 * 
 * 26    18.10.00 18:55 Wohlers
 * 
 * 25    18.10.00 0:51 Wohlers
 * 
 * 24    16.10.00 21:28 Wohlers
 * 
 * 23    11.10.00 19:48 Wohlers
 * 
 * 22    14.09.00 18:30 Wohlers
 * 
 * 21    13.09.00 18:37 Moos
 * 
 * 20    6.09.00 15:16 Rueve
 * cleanup
 * 
 * 19    5.09.00 21:09 Wohlers
 * 
 * 18    2.09.00 6:46 Wohlers
 * 
 * 17    1.09.00 23:20 Wohlers
 * 
 * 16    21.08.00 18:56 Speckels
 * 
 * 15    4.08.00 13:53 Wohlers
 * 
 * 14    2.08.00 21:09 Wohlers
 * 
 * 13    2.08.00 14:25 Wohlers
 * 
 * 12    26.07.00 22:15 Wohlers
 * 
 * 11    21.07.00 15:35 Wohlers
 * 
 * 10    19.07.00 20:05 Wohlers
 * 
 * 9     12.07.00 14:52 Wohlers
 * Overlay-TA Bugfix
 * 
 * 8     5.07.00 12:22 Wohlers
 * 
 * 7     25.05.00 14:50 Wohlers
 * Levelwechsel / Fernkampf
 * 
 * 6     22.05.00 18:43 Wohlers
 * Gothic 0.82
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
 * 13    19.04.00 16:44 Wohlers
 * Bug-Fixes
 * 
 * 12    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 11    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 10    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 9     23.02.00 5:53 Wohlers
 * Fixes
 * 
 * 8     23.02.00 3:47 Wohlers
 * Fixes
 * 
 * 7     22.02.00 20:41 Wohlers
 * uSrc 0.73
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

#include "zCore.h"

#include "oRoutine.h"
#include "oNpc.h"
#include "oNpcStates.h" // Temp : fürs Debugging
#include "oAnictrl.h"
#include "oGame.h"
#include "oMobInter.h"
#include "oWorld.h"
#include "zWaynet.h"
#include "zModel.h"
#include "zCCSPool.h"
#include "zCCSManager.h"

void oCRtnCutscene::ResetPlayState()
{
	if (ogame) ogame->GetCutsceneManager()->PoolClrFlags(csName, CS_PLAYED);	
};

oCRtnCutscene::~oCRtnCutscene()
{
	ResetPlayState();
};

oCRtnCutscene::oCRtnCutscene()
{
	ignorePlayState = FALSE;
	npc = NULL;			
};

oCRtnEntry :: oCRtnEntry () 
{
	hour1		= 0;
	min1		= 0;
	hour2		= 0;
	min2		= 0;
	f_script	= -1;
	instance	= -1;

	npc			= NULL;
	poi			= NULL;
	cutscene	= NULL;
	overlay		= FALSE;
}

oCRtnEntry :: oCRtnEntry (int h1,int m1,int h2,int m2,int func,const zSTRING& wp,int i) 
{
	hour1		= h1;
	min1		= m1;
	hour2		= h2;
	min2		= m2;
	f_script	= func;
	wpname		= wp;
	instance	= i;

	npc			= NULL;
	poi			= NULL;
	cutscene	= NULL;
	overlay		= FALSE;
}

oCRtnEntry :: ~oCRtnEntry ()
{
	delete (cutscene); cutscene = NULL;
	poi	= NULL;
	npc = NULL;
}

void oCRtnEntry :: GetTime (int &h1, int &m1,int &h2, int &m2)
{
	h1 = hour1;
	m1 = min1;
	h2 = hour2;
	m2 = min2;
}

void oCRtnEntry :: SetTime (int h1, int m1,int h2, int m2)
{
	hour1	= h1;
	min1	= m1;
	hour2	= h2;
	min2	= m2;
}

int oCRtnEntry :: GetState ()
{
	return f_script;
}

zSTRING oCRtnEntry :: GetWaypoint ()
{
	return wpname;
}

// ***************************************************************************************
// Routine Manager
// ***************************************************************************************

oCRtnManager rtnMan;

int oCRtnManager :: Sort_Routine (oCRtnEntry *entry1, oCRtnEntry *entry2)
{
	if (entry1->hour1 < entry2->hour1)	return -1;		else
	if (entry1->hour1 > entry2->hour1)	return  1;		else
	// Gleiche Stunde
	if (entry1->min1  < entry2->min1)	return -1;		else
	if (entry1->min1  > entry2->min1)	return  1;
	// Gleiche Minute - Overlays sind wichtiger
	if (entry1->overlay)				return -1;		else
	
	return 1;
}

int	oCRtnManager :: Sort_WayBoxLimit (TRtn_WayBoxLimit *entry1, TRtn_WayBoxLimit *entry2)
{
	if (entry1->value <= entry2->value)	return -1;
	else								return  1;
}

int	oCRtnManager :: Sort_WayBoxX  (TRtn_WayBox *entry1, TRtn_WayBox *entry2)
{
	if (entry1->bbox.mins[VX] <= entry2->bbox.mins[VX])	return -1;
	else										return  1;
}

int	oCRtnManager :: Sort_WayBoxY  (TRtn_WayBox *entry1, TRtn_WayBox *entry2)
{
	if (entry1->bbox.mins[VY] <= entry2->bbox.mins[VY])	return -1;
	else										return  1;
}

int	oCRtnManager :: Sort_WayBoxZ  (TRtn_WayBox *entry1, TRtn_WayBox *entry2)
{
	if (entry1->bbox.mins[VZ] <= entry2->bbox.mins[VZ])	return -1;
	else										return  1;
}

oCRtnManager :: oCRtnManager ()
{
	for (int i=0; i<3; i++) {
		indexStart	[i] = 0;
		indexEnd	[i] = 0;
	};
	world			= NULL;
	nextEntryNode	= NULL;
	rtnList		.SetCompare ( Sort_Routine );
	wayboxListX	.SetCompare ( Sort_WayBoxX );
	wayboxListY	.SetCompare ( Sort_WayBoxY );
	wayboxListZ	.SetCompare ( Sort_WayBoxZ );
};

oCRtnManager :: ~oCRtnManager ()
{
	// Die einzelnen Routines Einträge werden von jeweiligen NSC selbst entfernt.
	rtnList.DeleteList ( );
	// Die WayboxListen leeren
	wayboxListX.DeleteList();
	wayboxListY.DeleteList();
	// Nur beim letzten alle Datas löschen, 
	// weil die anderen beiden die gleichen Elemente enthalten
	// nur in anderer Reihenfolge
	wayboxListZ.DeleteListDatas();
};

void oCRtnManager :: SetWorld (zCWorld* w)
{
	world = w;
}

void oCRtnManager :: ShowRoutine (int x, int y, oCNpc* npc)
{
	zCFont* oldFont = screen->GetFont();

	if (y+screen->FontY()>VIEW_VYMAX) return;
	screen->Print(x,y,npc->GetName());
	y += screen->FontY();

	oCRtnEntry* rtn;
	zCListSort <oCRtnEntry> *rtnNode = rtnList.GetNextInList();	
	while (rtnNode) {
		rtn		= rtnNode->GetData();
		rtnNode = rtnNode->GetNextInList();
		
		//if ((rtn->GetNpc()==npc) && (rtn->f_script!=-1)) {
		// [EDENFELD] zu 1.09 zweite if bedingung rausgenommen, sollte unkritisch sein, da dies eh nur debug ausgaben sind
		if ((rtn->GetNpc()==npc) /*&& (rtn->f_script!=-1)*/) {
			if (y+screen->FontY()>VIEW_VYMAX) break;
			zSTRING s = GetRoutineString(rtn);
			if (npc->state.IsInRoutine() && (rtn==npc->state.GetRoutineCurrent())) {
				s += "   <<<";
			}	
//			if (nextEntryNode && nextEntryNode->GetData()==rtn) {
//				s += "   >>> NextEntry";
//			}				
			screen->Print(x,y,s);
			y += screen->FontY();
		}
	}
	screen->SetFont(oldFont);
}

zSTRING oCRtnManager :: GetRoutineString (oCRtnEntry* entry)
{
	zSTRING s = zSTRING(entry->hour1)+":"+zSTRING(entry->min1)+" - "+zSTRING(entry->hour2)+":"+zSTRING(entry->min2)+"  ";
	zCPar_Symbol* sym = parser.GetSymbol(entry->f_script);
	if (sym)	s+= sym->name;
	else		s+= "???";
	s+="  WP:" + entry->wpname;
	if (entry->cutscene) {
		s+="  CS:"+entry->cutscene->csName;
	}
	if (entry->overlay) s+="  (O)";
	return s;
}

void oCRtnManager :: Insert (oCNpc* npc, oCRtnEntry* rtn)
{
	if (rtn && npc) {
		rtn -> SetNpc		(npc);
		rtnList.InsertSort	(rtn);
	}
}

void oCRtnManager :: UpdateGlobalRoutineEntry()
{
	if (!ogame || !ogame->GetWorldTimer()) return; // [Moos] noch Test auf ogame eingefügt
	// nextENtryNode entsprechend setzen
	int				h1,m1,h2,m2;
	oCRtnEntry*		rtn;
	zCListSort <oCRtnEntry> *rtnNode = rtnList.GetNextInList();	
	// Default : Listenstart....
	nextEntryNode = rtnNode;
	while (rtnNode) {
		rtn	 = rtnNode->GetData();
		rtn -> GetTime(h1,m1,h2,m2);
		if (!ogame->GetWorldTimer()->IsLater(h1,m1)) {
			// Weltzeit später als h1,m1		
			nextEntryNode = rtnNode;
			break;
		};
		rtnNode = rtnNode->GetNextInList();
	};	
};

void oCRtnManager :: UpdateSingleRoutine(oCNpc* npc)
// Wird nach Anhaengen eines Overlay-TAs ausgeführt.
// a) aktuellen TA-Punkt dieses NSCs aus Gesamtliste raussuchen und diesen aktivieren 
// b) kein hinbeamen !
// c) aktuellen Global - Listen Pointer updaten (könnte jetzt auf OverlayTA-Punkt zeigen)
{
	if (npc->state.HasRoutine()) {
	
		// *************************************
		// TA Driven
		// *************************************

		oCRtnEntry *rtnNow		= NULL;
		oCRtnEntry *rtnBefore	= NULL;

		// aktuellen Routine-Punkt ermitteln.
		if (FindRoutine(npc,rtnNow,rtnBefore)) {
			if (npc->state.IsInRoutine()) {
				// Falls gefunden, den Zustand aktivieren
				if (npc->GetEM()->IsEmpty(TRUE)) {
					npc->ClearEM();						// EM leeren
					npc->Interrupt();					// überall abmelden
				}
				npc->state.rtnNow		= NULL;
				npc->state.SetRoutine	(rtnNow,rtnBefore);
				if (npc->GetEM()->IsEmpty(TRUE)) {
					npc->state.StartRtnState(TRUE);		
				}
			} else {
				// Nicht starten, nur vorbereiten....
				npc->state.rtnNow		= NULL;
				npc->state.SetRoutine	(rtnNow,rtnBefore);									
			}
		}
		
		// Globalen nextEntryNode neu errechnen
		UpdateGlobalRoutineEntry();
	
	} else {
		
		// *************************************
		// State Driven
		// *************************************
		if (npc->state.IsInRoutine()) {
			npc->ClearEM();								// EM leeren
			npc->Interrupt();							// überall abmelden
			npc->state.rtnNow = NULL;
			npc->state.StartRtnState();
		}
	};
};

void oCRtnManager :: RestartRoutines()
// a) Setzt alle "now", "before" und "route" jedes NSCs, der einen Tagesablauf hat.
// b) FIXME : Overlay-Tagesablaufpunkte werden entfernt, wenn Weltzeit später ist als Ende des OTA.
// c) Setzt nextNodeEntry auf nächsten zu startenden TA-Punkt
// Durchläuft komplette Liste !
// FIXME : Besser ein Array ???
{
	oCRtnEntry *rtnNow		= NULL;
	oCRtnEntry *rtnBefore	= NULL;
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = ogame->GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while(node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		
		if (!npc->IsSelfPlayer()) {
			npc->state.curState.valid = FALSE;				// aktueller Zustand nicht mehr valid
			if (npc->state.HasRoutine()) {
				if (FindRoutine(npc,rtnNow,rtnBefore)) {
					npc->ClearEM();						// EM leeren
					npc->Interrupt();							// überall abmelden
					npc->state.rtnNow			= NULL;
					npc->state.curState.valid	= FALSE;
					npc->state.nextState.valid	= FALSE;
					npc->state.SetRoutine		(rtnNow,rtnBefore);
					if (!npc->state.StartRtnState(TRUE)) {
						if (npc->GetHomeWorld()) {
							zSTRING strRtnError = npc->state.GetLastError();
							zERR_WARNING("U:AI: Failed to start npc routine : "+npc->GetInstanceName()+" :" + strRtnError);					
							npc->state.StartRtnState(TRUE);					
						}
					}
				} else {
					zERR_WARNING("U:AI: Npc routine position calculation failed :"+npc->GetInstanceName());
				}
			} else if (npc->state.IsAIStateDriven()) {
				npc->ClearEM();								// EM leeren
				npc->Interrupt();							// überall abmelden
				npc->state.rtnNow = NULL;
				npc->state.StartRtnState();
			}
		}
	};
		
	// nextENtryNode entsprechend setzen
	UpdateGlobalRoutineEntry();
}

zBOOL oCRtnManager :: FindRoutine(oCNpc* npc, oCRtnEntry* &rtnNow, oCRtnEntry* &rtnBefore)
{
	oCRtnEntry* rtnNowOld = rtnNow;
	oCRtnEntry* rtnBefOld = rtnBefore;
	rtnBefore	= NULL;
	rtnNow		= NULL;

	zCListSort <oCRtnEntry>*	rtnNode = rtnList.GetNextInList();	
	oCWorldTimer*				timer	= ogame->GetWorldTimer();
	oCRtnEntry*					rtn		= NULL;
	oCNpc*						curNpc	= NULL;
	
	int h1,m1,h2,m2;
	
	while (rtnNode) {
		rtn		= rtnNode->GetData();
		rtnNode = rtnNode->GetNextInList();
		
		if ((curNpc = rtn->GetNpc()) == npc) {			
		
			rtn -> GetTime(h1,m1,h2,m2);
			if (timer->IsTimeBetween(h1,m1,h2,m2)) {
				if (rtnNow) 
				{
					// schon mal gesetzt, dann nur gibts nur diesen einen Tagesablaufpunkt					
					rtnBefore	= rtn;					
					if (rtnBefore->cutscene && rtnBefore!=rtnBefOld)
						rtnBefore->cutscene->ResetPlayState();					
					return TRUE;
				} 
				else 
				{					
					rtnNow		= rtn;					
					if (rtnNow->cutscene && rtnNow!=rtnNowOld)
						rtnNow->cutscene->ResetPlayState();					
				}
			
			} else {
				rtnBefore	= rtn;
			}
				
			if (rtnNow && rtnBefore) {
				// a) berechnet Route
				// b) startet Zustand
				return TRUE;
			}
		}
	}
	// Nanu ? Nur einen Eintrag gefunden ?
	if (rtnNow)		{ rtnBefore = rtnNow;		return TRUE; };
	if (rtnBefore)	{ rtnNow	= rtnBefore;	return TRUE; };
	return FALSE;
}

void oCRtnManager :: CheckRoutines()
// a) Guckt, ob nächster Tagesablaufpunkt gestartet werden muss.
// b) entfernt TA, wenn es ein Overlay-TA war
{	
	// Von Begin an Liste durchackern ??????
	if (!nextEntryNode) nextEntryNode = rtnList.GetNextInList();
	
	int h1,m1,h2,m2;
	oCWorldTimer* timer		= ogame->GetWorldTimer();
	oCRtnEntry* nextEntry	= NULL;
	while (nextEntryNode) {
		nextEntry = nextEntryNode->GetData();
		nextEntry -> GetTime(h1,m1,h2,m2);
		if (timer -> IsTimeBetween(h1,m1,h2,m2)) {
			// naechster TA, oder Restart Routine nach TA-Overlay....
			if (nextEntry->f_script==-1) {
				// Restart Routine
				nextEntry->npc->state.RemoveOverlay();
				return;

			} else {
				// Dieser Tagesablaufpunkt muss jetzt aktiviert werden.
				nextEntry -> npc -> state.SetRoutine	(nextEntry,nextEntry->npc->state.rtnNow);
				// Nur aktivieren, wenn auch wirklich in Routine
				if (nextEntry -> npc -> state.IsInRoutine())
					nextEntry -> npc -> state.StartRtnState	(rtnList.GetNumInList()>1);
			}

		} else {
			// Wenn es ein OverlayTagesablauf ist, dann muss dieser hier rausgeworfen werden
			if (nextEntry->overlay && timer->IsLater(h1,m1)) {
				nextEntryNode = nextEntryNode->GetNextInList();
				nextEntry->npc->state.RemoveOverlayEntry(nextEntry);					
			}	
			return;
		}
		
		nextEntryNode = nextEntryNode->GetNextInList();
	}	
}

zVEC3 oCRtnManager :: GetRoutinePos(oCNpc* npc)
// a) Liefert aktuelle Position des NSC innerhalb seines Tagesablaufes zurück ( Interpolation )
// b) dazu müssen richtig initialisiert sein : "now", "route"
{
	zVEC3 pos = npc->GetPositionWorld();

	// aktuelle Tagesablaufpunkte ermitteln
	int h1,m1,h2,m2;

	// In Abhängigkeit von der Tageszeit wird der NSC an die Position gesetzt, 
	// an der er sich laut Tagesablauf befinden sollte ( interpoliert )
	zREAL speed		= 0.5000f;			// 5 kmh
	oCRtnEntry*	now = npc->state.GetRoutineCurrent	();
	zCRoute* rt		= npc->state.GetRoutineRoute	();
	
	if (!rt) {
		//zERR_WARNING("U:AI: No route found, cannot calculate routine-position. Npc:"+npc->GetInstanceName());
	}
	if (!now) {
		//zERR_WARNING("U:AI: No running routine found, cannot calculate routine-position."+npc->GetInstanceName());
	}

	// Hier muss alles benoetigte da sein... sonst nichts machen...
	if (!ogame || !ogame->GetWorld() || !ogame->GetWorld()) {
		zERR_WARNING("U: RTN: GetRoutinePos failed !!!!!.");			
		return pos;
	}

	if (now && rt) {
		// gefunden, jetzt Route berechnen
		oCWorldTimer* timer	= ogame->GetWorldTimer();
		// Zeit holen
		now->GetTime(h1,m1,h2,m2);
		// Route gefunden,Zeitdelta errechnen
		int h,m;
		timer->GetTime(h,m);
		if (h<h1) h += 24;
		int dmin = (h*60+m) - (h1*60+m1);
		rt->GetInterpolatedPosition(speed,dmin,pos);
	} else {
		// irgendwas nicht gefunden, alternativen Platz aussuchen
		zCWaypoint* wp = NULL;
		if (now) {
			wp = ogame->GetGameWorld()->GetWayNet()->GetWaypoint(now->GetWaypoint());
			if (wp) return wp->GetPositionWorld();
		} 
		if (npc->state.rtnBefore) {
			wp = ogame->GetGameWorld()->GetWayNet()->GetWaypoint(npc->state.rtnBefore->GetWaypoint());
			if (wp) return wp->GetPositionWorld();
		} else {
			// Nichts mehr zu machen....
			zERR_WARNING("U:AI: No alternative routine position possible.");
		};
	}

	return pos;
}

void oCRtnManager :: WriteRoutine (zCArchiver& arc, oCNpc* npc, zBOOL onlyOverlays)
{
	zCListSort	<oCRtnEntry>*	rtnNode = rtnList.GetNextInList();
	oCRtnEntry*					rtn		= NULL;

	// Count them
	int count = 0;
	while (rtnNode) {
		rtn		= rtnNode->GetData();
		rtnNode = rtnNode->GetNextInList();
		if (rtn && rtn->npc==npc) {
			if (onlyOverlays && !rtn->overlay) continue;
			count++;
		}
	}
	
	// Write them
	arc.WriteInt("rtnCount",count);

	rtnNode = rtnList.GetNextInList();
	while (rtnNode) {
		rtn		= rtnNode->GetData();
		rtnNode = rtnNode->GetNextInList();
		if (rtn) {
			if (!rtn->overlay && (onlyOverlays)) continue;
			
			if (rtn->npc == npc) {
				// Write it 
				arc.WriteInt	("rtnHour1"		,rtn->hour1);
				arc.WriteInt	("rtnMin1"		,rtn->min1);
				arc.WriteInt	("rtnHour2"		,rtn->hour2);
				arc.WriteInt	("rtnMin2"		,rtn->min2);
				arc.WriteInt	("rtnScript"	,rtn->f_script);
				arc.WriteInt	("rtnInstance"	,rtn->instance);
				// Cutscenes nicht speichern -> bei Overlays nicht noetig
				//			arc.WriteObject ("rtnCutscene"	,rtn->cutscene);
				arc.WriteBool	("rtnOverlay"	,rtn->overlay);
				arc.WriteString	("rtnWp"		,rtn->wpname);
			}
		}
	}
};

void oCRtnManager :: ReadRoutine (zCArchiver& arc, oCNpc* npc)
{
	zCList <oCNpc>	npcList;
	oCRtnEntry*		rtn			= NULL;

	// Anzahl lesen
	int count = 0;
	arc.ReadInt("rtnCount",count);
	// Evt. vorhandenen wegschmeissen....
	if (count>0) RemoveRoutine (npc);

	for (int i=0; i<count; i++) {
	
		rtn = zNEW( oCRtnEntry() );

		// Read it 
		arc.ReadInt		("rtnHour1"		,rtn->hour1);
		arc.ReadInt		("rtnMin1"		,rtn->min1);
		arc.ReadInt		("rtnHour2"		,rtn->hour2);
		arc.ReadInt		("rtnMin2"		,rtn->min2);
		arc.ReadInt		("rtnScript"	,rtn->f_script);
		arc.ReadInt		("rtnInstance"	,rtn->instance);
		arc.ReadBool	("rtnOverlay"	,rtn->overlay);
		arc.ReadString	("rtnWp"		,rtn->wpname);
		rtn->npc		= npc;
		
		Insert(rtn->npc,rtn);
	}
	
	// Wayboxen neu berechnen fuer benutzte NPCs
	CreateWayBoxes	(npc);
};

// ********************************************************************************
// old
// ********************************************************************************

void oCRtnManager :: RemoveEntry (oCRtnEntry* entry)
{
	if (entry) {
		if (nextEntryNode && (nextEntryNode->GetData()==entry)) nextEntryNode->GetNextInList();
		rtnList.Remove(entry);
		delete(entry);
	}
}

void oCRtnManager :: RemoveRoutine (oCNpc* npc)
// Alle Tagesablaufpunkte dieses NSCs aus der Liste entfernen und löschen
{
	oCRtnEntry* rtn;
	zCListSort <oCRtnEntry> *rtnNode = rtnList.GetNextInList();	
	while (rtnNode) {
		rtn		= rtnNode->GetData();
		rtnNode = rtnNode->GetNextInList();
		if (rtn->GetNpc()==npc) {
			if (nextEntryNode && nextEntryNode->GetData()==rtn) {
				nextEntryNode = rtnNode;
			}
			rtnList.Remove(rtn);
			delete (rtn);
		}
	}
	RemoveWayBoxes(npc);

	UpdateGlobalRoutineEntry();
}


// Checkt die Routinen dieses npcs auf Konsistenz
void oCRtnManager :: CheckConsistency(oCNpc* npc)
{
	// alle entrys dieses nsc's in eine neue liste packen
	oCRtnEntry* rtn;
	zCListSort <oCRtnEntry> *rtnNode = rtnList.GetNextInList();	
	zCArray<oCRtnEntry*>npcRoutines;
	while (rtnNode) {
		rtn		= rtnNode->GetData();
		rtnNode = rtnNode->GetNextInList();
		if (rtn->GetNpc()==npc) 
		{
			npcRoutines.InsertEnd(rtn);
		}
	}

	// nun die liste durchgehen, und auf fehler überprüfen
	if (npcRoutines.GetNum()<=1) return;			// wenn nur ein ta, raus hier

	for (int i=0; i<npcRoutines.GetNum(); i++)
	{
		oCRtnEntry *nextRtn = npcRoutines[i];
		if (nextRtn->overlay)		  continue;				// overlays werden nicht überprüft (FIXME)

		for (int j=0; j<npcRoutines.GetNum(); j++)
		{
			if (nextRtn == npcRoutines[j]) continue;
			if (npcRoutines[j]->overlay)   continue;				// overlays werden nicht überprüft (FIXME)
			// überlappen sich zeiten ?
			zREAL start1 = nextRtn->hour1 + (nextRtn->min1*0.01F);
			zREAL end1	 = nextRtn->hour2 + (nextRtn->min2*0.01F);
			zREAL start2 = npcRoutines[j]->hour1 + (npcRoutines[j]->min1*0.01F);
			zREAL end2   = npcRoutines[j]->hour2 + (npcRoutines[j]->min2*0.01F);

			// liegt die startzeit oder die endzeit zwischen der zu checkenden routine ?
			if ( ((start2 > start1) && (start2 < end1 )) ||
				 ((end2   < end1  ) && (end2   > start1 ))
				 ) 
			{
				// fehler !!!
				zERR_FAULT("C: TA Error for NPC " + npc->GetInstanceName() + " please check the daily routines !");
				continue;
			}
		}
	}
	npcRoutines.DeleteList();
}





void oCRtnManager :: RemoveOverlay (oCNpc* npc)
// Alle Overlay-Tagesablaufpunkte dieses NSCs aus der Liste entfernen und löschen
{
	oCRtnEntry* rtn;
	zCListSort <oCRtnEntry> *rtnNode = rtnList.GetNextInList();	
	while (rtnNode) {
		rtn		= rtnNode->GetData();
		rtnNode = rtnNode->GetNextInList();
		if ((rtn->overlay) && (rtn->GetNpc()==npc)) {
			if (nextEntryNode && nextEntryNode->GetData()==rtn) {
				nextEntryNode = rtnNode;
			}
			rtnList.Remove(rtn);
			delete (rtn);
		}
	}
	RemoveWayBoxes(npc);
	CreateWayBoxes(npc);

	UpdateGlobalRoutineEntry();
}

#ifdef COMPILING_SPACER
extern zBOOL g_bIsPlayingGame;
#endif

void oCRtnManager :: SetDailyRoutinePos (zBOOL onlyRoutineDriven)
{
#ifdef COMPILING_SPACER
	if ( (!g_bIsPlayingGame) ) return;
#endif

	// Los gehts...
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = ogame->GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (node) {
		npc		=  node->GetData();
		node	=  node->GetNextInList();
		if (onlyRoutineDriven && npc->state.IsAIStateDriven()) continue;
		npc	-> Disable();
	}
	// Gesamte Liste neu durchforsten
	RestartRoutines();
}

void oCRtnManager :: InitWayBoxes()
{
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = ogame->GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		if (!npc->IsDead() || !npc->IsAPlayer()) CreateWayBoxes (npc);
	}
}

void oCRtnManager :: InsertWaybox(oCNpc* npc, zVEC3& mins, zVEC3& maxs)
{
	for (int i=0; i<3; i++) {
		// "putem on the glass" 
		TRtn_WayBoxLimit* wb= zNEW( TRtn_WayBoxLimit );
		wb->begin			= TRUE;
		wb->npc				= npc;
		wb->value			= mins[i];
		wb->bbox.mins		= mins;		// TEMP
		wb->bbox.maxs		= maxs;		// TEMP
		wayboxList[i].InsertSort(wb);

		wb					= zNEW( TRtn_WayBoxLimit );
		wb->begin			= FALSE;
		wb->npc				= npc;
		wb->value			= maxs[i];
		wb->bbox.mins		= mins;		// TEMP
		wb->bbox.maxs		= maxs;		// TEMP
		wayboxList[i].InsertSort(wb);
	}
}

void oCRtnManager :: RemoveWayBoxes(oCNpc* npc)
{
	TRtn_WayBox* wb = NULL;
	zCListSort	<TRtn_WayBox>* wbnode = wayboxListX.GetNextInList();
	while (wbnode) {
		wb		= wbnode->GetData();
		wbnode	= wbnode->GetNextInList();
		if (wb->npc == npc) {
			wayboxListX.Remove(wb);
			wayboxListY.Remove(wb);
			wayboxListZ.Remove(wb);		
			delete wb;
			break;
		}
	}
}

void oCRtnManager :: CreateWayBoxes(oCNpc* npc)
{
	if (!npc->state.HasRoutine()) return;
	
	// Alle Tagesablaufrelevanten Waypoints in eine Liste packen
	zVEC3 pos;
	zSTRING wpName;
	zCWaypoint* wp;
	oCRtnEntry* rtn;
	int h1,m1,h2,m2;
	
	zVEC3 maxs;
	zVEC3 mins;

	int intervall	= 24; 
	int loopCtr		= 24 / intervall;
	if ((24 % intervall)>0) loopCtr++;

	int hourStart	= 0;
	int hourEnd		= intervall;

	zCListSort <oCRtnEntry>* rtnNode = NULL;

	for (int i=0; i<loopCtr; i++) {
	
		mins	= zVEC3(zREAL_MAX,zREAL_MAX,zREAL_MAX);
		maxs	= zVEC3(zREAL_MIN,zREAL_MIN,zREAL_MIN);
		rtnNode	= rtnList.GetNextInList();
		
		while (rtnNode) {
			rtn		= rtnNode->GetData();
			rtnNode	= rtnNode->GetNextInList();
			
			if (rtn->GetNpc()==npc) {

				wpName	= rtn->GetWaypoint();
				wp		= world->GetWayNet()->GetWaypoint(wpName);
				if (wp) {
					
					rtn->GetTime(h1,m1,h2,m2);
					if ((h1>=hourStart) && (h1<=hourEnd)) {
						// In TimeRange
						pos = wp ->GetPositionWorld();
						if (pos[VX]<mins[VX]) mins[VX] = pos[VX];
						if (pos[VX]>maxs[VX]) maxs[VX] = pos[VX];
						if (pos[VY]<mins[VY]) mins[VY] = pos[VY];
						if (pos[VY]>maxs[VY]) maxs[VY] = pos[VY];
						if (pos[VZ]<mins[VZ]) mins[VZ] = pos[VZ];
						if (pos[VZ]>maxs[VZ]) maxs[VZ] = pos[VZ];
					}
				}
			}
		}

		// "putem on the glass"
		TRtn_WayBox* waybox = zNEW( TRtn_WayBox );
		waybox->bbox.mins	= mins;
		waybox->bbox.maxs	= maxs;
		waybox->npc			= npc;
		waybox->found		= 0;
		// In die ersten 3 Listen eintragen
		// CHECK : getrennt Listen für jeden Tagesablauf-Intervall ?
		wayboxListX.InsertSort(waybox);
		wayboxListY.InsertSort(waybox);
		wayboxListZ.InsertSort(waybox);

		hourStart = hourEnd;
		hourEnd	 += intervall;
	}
}
/*
void oCRtnManager :: DrawWayBoxes()
{
	TRtn_WayBoxLimit* waybox = NULL;
	for (int i=0; i<wayboxList[VX].GetNumInList(); i++) {
		waybox = wayboxList[VX][i];
		if (waybox->begin) waybox -> bbox.Draw();
	}
}
*/
void oCRtnManager :: DrawWayBoxes()
{
	TRtn_WayBox* waybox = NULL;
	zCListSort<TRtn_WayBox>* wbnode = wayboxListX.GetNextInList();
	while (wbnode) {
		waybox	= wbnode->GetData();
		wbnode	= wbnode->GetNextInList();
		waybox -> bbox.Draw();
	}
}

void oCRtnManager :: CreateActiveList(oCNpc* npc, zTBBox3D& bbox)
// Liste durchlaufen und alle Wayboxes von aktiven NSCs eintragen
{
	activeList.DeleteList();

	TRtn_WayBoxLimit* waybox = NULL;
	for (int i=0; i<wayboxList[VX].GetNumInList(); i++) {
		waybox = wayboxList[VX][i];
		// In Range -> In activeList einfügen
		if (waybox->begin) {
			// FIXME : Wenn hier rechts ausserhalb -> dann komplett beenden
			if ((waybox->value >= bbox.mins[VX]) && (waybox->value <= bbox.maxs[VX])) {
				activeList.Insert(waybox->npc);
			}
		
		}
	}

	for (int n=1; n<=2; n++) {
		for (i=0; i<wayboxList[n].GetNumInList(); i++) {
			waybox = wayboxList[n][i];		
			// In Range -> In activeList einfügen
			if (waybox->begin) {
				// Ausserhalb der Range, dann Eintrag rausnehmen, falls er vorher drin war.
				if ((waybox->value < bbox.mins[n]) || (waybox->value > bbox.maxs[n])) {
					activeList.Remove(waybox->npc);
				}
			}
		}
	}

	// Aktive Liste ist gefüllt ( oder auch nicht )
	// Jetzt SpielerBox - Position ermitteln
	// FIXME : Das geht besser !!!!!
/*	for (n=0; n<3; n++) {

		indexStart	[n] = -1;
		indexEnd	[n] = -1;

		for (i=0; i<wayboxList[n].GetNumInList(); i++) {
			waybox = wayboxList[n][i];
			// Das erste gefundene Objekt in Range ist der Startpunkt
			if ((indexStart[n]<0) && (waybox->value >= bbox.mins[n])) {
				indexStart[n]  = i;
			}
			// Das erste gefundene Objekt outof Range ist der Endpunkt - 1
			if ((indexEnd[n]<0) && (waybox->value  > bbox.maxs[n])) {
				indexEnd[n]	   = i-1;
			}
			// Alle hierhin stehenden WayBoxes besitzen drei Treffer
			waybox->hits = 3;
		}
	}*/
}
/*
zBOOL oCRtnManager :: CollidesWithWayBox(oCNpc* npc, zTBBox3D& bbox, zCList<oCNpc>& foundNpcList)
{
	// Aktive Liste durchgehen und nach veränderungen suchen

	// 1. Startpunkt nach links	?
	TRtn_WayBoxLimit* waybox;
	
	n		= VX;
	
	// *** Start ***
	// Links oder rechts Element am Wickel
	index	= indexStart[n]-1;
	waybox	= wayboxList[n][index];

	if (bbox.mins[n] <= waybox->value) {
		
		// Nach Links wandern
		do {
			// Element relevant, also eintragen
			if (waybox->begin) {
				waybox->hits++;
				if (waybox->hits==3) activeList.Insert(waybox->npc);
			}
			index--;
			if (index>=0) 
				waybox = wayboxList[index];
			else
				break;
		} while (waybox->value >= bbox.mins[n]);
		indexStart[n] = index+1;

	} else {
		
		// Nach rechts wandern
		do {
			// Element rauswerfen
			if (!waybox->begin) {
				activeList.Remove(waybox->npc);
				waybox->hits = 0;
			}
			index++;
			if (index<wayboxList.GetNumInList()) 
				waybox = wayboxList[index];
			else
				break;
		} while (waybox->value >= bbox.mins[n]);
		indexStart[n] = index - 1;
	}

	// *** End ***
	// Links oder rechts Element am Wickel
	index	= indexEnd[n]-1;
	waybox	= wayboxList[n][index];

	if (bbox.mins[n] <= waybox->value) {
		
		// Nach Links wandern
		do {

			if (waybox->begin) {
				activeList.Remove(waybox->npc);
				waybox->hits = 0;
			}
			index--;
			if (index>=0) 
				waybox = wayboxList[index];
			else
				break;
		} while (waybox->value >= bbox.mins[n]);
		indexEnd[n] = index+1;

	} else {
		
		// Nach rechts wandern
		do {
			// Element einfügen
			if (waybox->begin) {
				waybox->hits++;
				if (waybox->hits==3) activeList.Insert(waybox->npc);
			}
			index++;
			if (index<wayboxList.GetNumInList()) 
				waybox = wayboxList[index];
			else
				break;
		} while (waybox->value >= bbox.mins[n]);
		indexEnd[n] = index - 1;
	}

	// ActiveList durchlaufen und alle hit < 3 rauswerfen
	zCList <
}
*/

zBOOL oCRtnManager :: CollidesWithWayBox(zTBBox3D& bbox, zCList<oCNpc>& foundNpcList)
{ 
	// Check, welche Wegboxen mit NSC-Tagesablauf-Wegbox ( der übergebenen ) kollidiert.
	
	zCList <TRtn_WayBox> resultlist;
	TRtn_WayBox* waybox = NULL;

	// 1. X - Test
	zREAL x1 = bbox.mins[VX];
	zREAL x2 = bbox.maxs[VX];
	zCListSort <TRtn_WayBox>* wbnode = wayboxListX.GetNextInList();
	while (wbnode) {
		waybox	= wbnode->GetData();
		wbnode	= wbnode->GetNextInList();
		waybox -> found = 0;
		// Ausserhalb der Range (1) : Liste muss nicht weiter durchsucht werden.
		if (waybox->bbox.mins[VX] > x2) break;
		// Ausserhalb der Range (2) : Liegt links ausserhalb -> nachfolgende können aber passen
		if (waybox->bbox.maxs[VX] < x1) continue;
		// So, diese Box kollidiert (in X-Richtung) mit SpielerRadius-bbox
		resultlist.Insert(waybox);
	}

	// 2. Y - Test
	x1 = bbox.mins[VY];
	x2 = bbox.maxs[VY];
	wbnode = wayboxListY.GetNextInList();
	while (wbnode) {
		waybox	= wbnode->GetData();
		wbnode	= wbnode->GetNextInList();
		// Ausserhalb der Range (1) : Liste muss nicht weiter durchsucht werden.
		if (waybox->bbox.mins[VY] > x2) break;
		// Ausserhalb der Range (2) : Liegt links ausserhalb -> nachfolgende können aber passen
		if (waybox->bbox.maxs[VY] < x1) continue;
		// So, diese Box kollidiert (in X-Richtung) mit SpielerRadius-bbox
		// Ist aber nur noch relevant wenn auch eine Kolli in X-Richtung stattgefunden hat.
		if (resultlist.InList(waybox)) waybox->found++;
	}

	// 3. Z - Test
	x1 = bbox.mins[VZ];
	x2 = bbox.maxs[VZ];
	wbnode = wayboxListZ.GetNextInList();
	while (wbnode) {
		waybox	= wbnode->GetData();
		wbnode	= wbnode->GetNextInList();
		// Ausserhalb der Range (1) : Liste muss nicht weiter durchsucht werden.
		if (waybox->bbox.mins[VZ] > x2) break;
		// Ausserhalb der Range (2) : Liegt links ausserhalb -> nachfolgende können aber passen
		if (waybox->bbox.maxs[VZ] < x1) continue;
		// So, diese Box kollidiert (in X-Richtung) mit SpielerRadius-bbox
		// Ist aber nur noch relevant wenn auch eine Kolli in X-Richtung stattgefunden hat.
		if (resultlist.InList(waybox)) {
			waybox->found++;
			// Und in Ergebnisliste packen 
			if (waybox->found==2) {
				// Alle 3 Koordinaten relvant -> Kollision
				// "2" nur deshalb, weil 1.Kriterium (X-Koo) bereits duch einfügen in Liste erfüllt wurde.
				if (!foundNpcList.InList(waybox->npc)) foundNpcList.Insert(waybox->npc);
			}
		}
	}
	return (foundNpcList.GetNumInList()>0);
}

int oCRtnManager :: GetNumOfWayBoxes ()
{
	return wayboxListX.GetNumInList();
}
