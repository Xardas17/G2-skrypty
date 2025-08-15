/******************************************************************************** 
 
     $Workfile:: oSpawn.cpp           $                $Date:: 18.02.01 20:44   $
     $Revision:: 40                   $             $Modtime:: 18.02.01 20:44   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:

 * 
 *********************************************************************************/

// **************************************
// Spawning
// **************************************
// a) NSC im Tagesablauf 
// Entfernen:
// * falls ausserhalb 40m Radius
// 
// Einfügen:
// * Position errechnen (jede Sekunde)
// * falls in 40m Radius -> einfügen
// 
// **************************************
// b) NSC mit Tagesablauf aber in anderem Zustand (ZS_Flee, Attack etc.)
// Entfernen:
// * falls ausserhalb 40m Radius
// * npcInRangeAllowed = FALSE;
// 
// Einfügen:
// * Position errechnen (jede Sekunde)
// * falls in 40 Radius und npcInRangeAllowed -> einfügen
// * falls nicht in 40m Radius -> npcInRangeAllowed = TRUE;
// 
// **************************************
// c) NSC zustandsgesteuert (Monster)
// Entfernen:
// * falls ausserhalb 40m Radius
// * npcInRangeAllowed = FALSE
// 
// Einfügen:
// * Entfernung zur StatePosition checken (jede Sekunde)
// * falls in 40m Radius und targetInRangeNotAllowed == 0 -> einfügen
// * falls nicht in 40m Radius -> targetInRangeNotAllowed = 0;
//
// **************************************
// d) Spawning von Monstern
// Entfernen : -
// Einfügen :
// * Einmal : npcInrangeAllowed = FALSE; Nicht im AliveRadius respawnen
// * falls in 40m Radius und targetInRangeNotAllowed == 0 -> einfügen
// * falls nicht in 40m Radius -> targetInRangeNotAllowed = 0;
// 
// Check : Wie ist das mit dem Respawnen von TA-gesteuerten NSCs nach derem Tod ?
// Die brauchen doch nicht in die RespawnListe eingetragen werden, oder ?

#include "zCore.h"

#include "oSpawn.h"
#include "oGame.h"
#include "oNpc.h"
#include "oWorld.h"
#include "oRoutine.h"
#include "zWaynet.h"
#include "zVob.h"

#include "zAccount.h"

zREAL SPAWN_INSERTTIME_MAX	= 1 * 1000;		// 1 Sekunde
zREAL SPAWN_INSERTRANGE		= 45 * 100;
zREAL SPAWN_REMOVERANGE		= 50 * 100;		// grosser als SPAWN_INSERTRANGE !!

oCSpawnManager :: oCSpawnManager()
{
	insertTime	= SPAWN_INSERTTIME_MAX;
	camPos		= zVEC3 (0,0,0);
	spawnFlags	= 0;
	SetSpawningEnabled(TRUE);	
}

oCSpawnManager :: ~oCSpawnManager()
{
	ClearList();
}

void oCSpawnManager :: SetInsertRange(zREAL rangecm)
{
	// unsauber, besser als Member benutzen
	SPAWN_INSERTRANGE = rangecm;
}

zREAL oCSpawnManager :: GetInsertRange()
{
	// unsauber, besser als Member benutzen
	return SPAWN_INSERTRANGE;
}

void oCSpawnManager :: SetRemoveRange(zREAL rangecm)
{
	// unsauber, besser als Member benutzen
	SPAWN_REMOVERANGE = rangecm;
}

zREAL oCSpawnManager :: GetRemoveRange()
{
	// unsauber, besser als Member benutzen
	return SPAWN_REMOVERANGE;
}

void oCSpawnManager :: SetSpawnTime(zREAL timems)
{
	// unsauber, besser als Member benutzen
	SPAWN_INSERTTIME_MAX = timems;
}

zREAL oCSpawnManager :: GetSpawnTime()
{
	// unsauber, besser als Member benutzen
	return SPAWN_INSERTTIME_MAX;
}

void oCSpawnManager :: ClearList()
{
	for (int i=0; i<spawnList.GetNumInList(); i++) { 
		zRELEASE_ACCT_NONULL(spawnList[i]->npc);
		delete spawnList[i]; 
	};
	spawnList.EmptyList();
};

void oCSpawnManager :: InsertInList(oCSpawnManager::oTSpawnNode* spawnNode)
{
	// FIXME : AddRef auf NSC ?
	if (spawnNode) zADDREF_ACCT(spawnNode->npc);
	spawnList.Insert(spawnNode);
};

void oCSpawnManager :: RemoveFromList(oCSpawnManager::oTSpawnNode* spawnNode)
{
	if (spawnNode) zRELEASE_ACCT_NONULL(spawnNode->npc);
	spawnList.Remove(spawnNode);
	delete spawnNode;
};

zBOOL oCSpawnManager :: IsSpawningEnabled()
{
	return spawningEnabled;
};

void oCSpawnManager :: SetSpawningEnabled(zBOOL spawnOn)
{
	spawningEnabled = spawnOn;
};

void oCSpawnManager :: SpawnImmediately(zBOOL resetSpawnNodeTime)
// Spawn all NSCs now
{
	insertTime = SPAWN_INSERTTIME_MAX;
	if (resetSpawnNodeTime) {
		// Zeitdelta auf Null setzen.
		for (int i=0; i<spawnList.GetNumInList(); i++) spawnList[i]->timer = 0;
	}

    zBOOL noLazy = zoptions->Parm("NOLAZYLOAD");

	// Npc-Liste durchgehen und einfügen in Alive-Radius erlauben
	oCNpc* npc  = NULL;
	zCListSort<oCNpc>* npcNode = ogame->GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (npcNode) {
		npc		= npcNode->GetData();
		npcNode = npcNode->GetNextInList();

        if (noLazy)
            npc->AvoidShrink();  // das lädt die Visuals der NPCs und sorgt für Konvertierung.

		CheckRemoveNpc(npc);
		//npc->SetSpawnInRangeAllowed(TRUE);
	}
	CheckInsertNpcs();
}

void oCSpawnManager :: CheckInsertNpcs()
{
//	ShowDebugInfo();

	if (!IsSpawningEnabled()) return;

	insertTime += ztimer.GetFrameTimeF();
	if (insertTime < SPAWN_INSERTTIME_MAX) return;
	insertTime -= SPAWN_INSERTTIME_MAX;

	InitCameraPos();

	// Watch closely : Cycling von NSCs immer noch vorhanden ?
	CheckInsertNpc();	// Einfügen
};

void oCSpawnManager :: ShowDebugInfo()
{
	int y = 500;
	screen->Print(   0,y,"Instance:");		
	screen->Print(3000,y,"Distance:");		
	screen->Print(5000,y,"Allowed:");		
	screen->Print(7000,y,"Delay:");
	y+=screen->FontY();

	oCNpc* npc = NULL;
	zREAL dist = 0.0f;

	for (int i=0; i<spawnList.GetNumInList(); i++) {

		dist	=  (spawnList[i]->spawnPos - camPos).LengthApprox();
		npc		=  spawnList[i]->npc;
		screen	-> Print(   0,y,npc->GetInstanceName());				
		screen	-> Print(3000,y,zSTRING( int(dist) ) );
		screen	-> Print(5000,y,zSTRING(npc->SpawnInRangeAllowed()));  
		screen	-> Print(7000,y,zSTRING(spawnList[i]->timer));  
		y += screen->FontY();
	}		
};

void oCSpawnManager :: CheckInsertNpc()
{
	// *********************************************
	// NSCs ohne TA - oder am frisch respawnen
	// *********************************************
	for (int i=0; i<spawnList.GetNumInList(); i++)
	{
		// [BENDLIN] Addon
		if (!spawnList[i])
			break;

		// [BENDLIN] 1.30 Safety (occured in customer savegame)
		if (!spawnList[i]->npc)
		{
       		zERR_WARNING("N: SPAWN: Invalid NPC in List!");
			oTSpawnNode *sp = spawnList[i];
			RemoveFromList(sp);
			// [BENDLIN] Addon
			// weiter in der Liste...
			i--; continue;
		}

		// ZeitDelta ?
		if (spawnList[i]->timer<=0)
		{
			// Falls NPC tot ist, diesen komplett aus Spiel entfernen
			if ((spawnList[i]->npc->IsDead()) && CanDeadNpcBeRemoved(spawnList[i]->npc))
			{
				// NSC kann komplett aus der Welt entfernt werden
				// Aber nur, wenn Out of Range
				if ((spawnList[i]->npc->GetPositionWorld() - camPos).LengthApprox() >= SPAWN_REMOVERANGE)
				{					
					// [BENDLIN] Addon Patch - FIXME: Spawnpoint muss auch ausserhalb der SPAWN_REMOVERANGE liegen, 
					// damit NSC entfernt werden kann.
					zVEC3 spawnPoint;
					if (spawnList[i]->npc->IsDead() && !UseDeadNpcRoutinePos(spawnList[i]->npc))
						spawnPoint = spawnList[i]->npc->GetPositionWorld();
					else if (spawnList[i]->npc->state.HasRoutine())
						spawnPoint = rtnMan.GetRoutinePos(spawnList[i]->npc);
					else
						spawnPoint = spawnList[i]->npc->state.GetAIStatePosition();
					if ((spawnPoint - camPos).LengthApprox() >= SPAWN_REMOVERANGE)
					{
						DeleteNpc(spawnList[i]->npc);
						// [BENDLIN] Addon
						// DeleteNpc() kann mehrere Indizes entfernen,
						// also MUSS hier die Schleife verlassen werden!
						break;
					}

				}
				// [BENDLIN] Addon
				// Ist zwar tot, wurde aber nicht entfernt,
				// also weiter in der Liste...
				continue;
			} 

			// NSC spawnen
			// [BENDLIN] Addon Patch - FIXME: spawnPos aktuell? (was mit TA-Wechsel)
			if (InsertNpc(spawnList[i]->npc,spawnList[i]->spawnPos)) {
				// Erfolgreich eingesetzt, aus Liste entfernen
                oTSpawnNode *sp=spawnList[i];  // [Moos]
				RemoveFromList(sp);
				// [BENDLIN] Addon
				// weiter in der Liste...
				i--; continue;
			}
		}
		else
		{			
			spawnList[i]->timer -= SPAWN_INSERTTIME_MAX;
		}
	}

	// *********************************************
	// NSCs mit TA
	// *********************************************
	// Ermittle Liste der NSCs die TA haben und eingefügt werden muessten.
	// alle gelieferten NSCs 
	// a) haben TA 
	// b) sind nicht in der Welt
	// c) sind nicht der Spieler
	zTBBox3D bbox;
	bbox.mins		= camPos - (SPAWN_INSERTRANGE * zVEC3(1,1,1));
	bbox.maxs		= camPos + (SPAWN_INSERTRANGE * zVEC3(1,1,1));

	zCList<oCNpc> npcInRangeList;
	rtnMan.CollidesWithWayBox(bbox,npcInRangeList);			
	
	oCNpc*			npc		= NULL;
	zCList<oCNpc>*	npcNode = npcInRangeList.GetNextInList();
	while (npcNode) {
		npc		= npcNode->GetData();
		npcNode = npcNode->GetNextInList();
		if (!npc->GetHomeWorld() && !npc->IsAPlayer())
		{
			// [BENDLIN] Addon - Keine Totenwanderung
			zVEC3 spawnPoint;
			if (npc->IsDead() && !UseDeadNpcRoutinePos(npc))
				spawnPoint = npc->GetPositionWorld();
			else if (npc->state.HasRoutine())
				spawnPoint = rtnMan.GetRoutinePos(npc);
			else
				spawnPoint = npc->state.GetAIStatePosition();

			InsertNpc(npc, spawnPoint);
		};
	};
	npcInRangeList.DeleteList();
};

void oCSpawnManager :: InitCameraPos()
{
	zCVob*		camVob	= oCNpc::player;
	zCAICamera* ai		= zCAICamera::GetCurrent();
	if (ai)		camVob	= ai->GetVob();
	if (camVob)	camPos	= camVob->GetPositionWorld();
};
	
//*********************************************************************************
//**																	  InsertNpc
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCSpawnManager :: InsertNpc(oCNpc* npc, const zVEC3& spawnPos)
{
	// Achtung : Nicht GetDistanceToVob2 benutzen, da es in der 
	// riesigen Oberwelt zu Float-Überläufen kommt.
	// und jetzt je nach Entfernung wieder einfügen

	zREAL dist = (spawnPos - camPos).LengthApprox();
	if (dist < SPAWN_INSERTRANGE) {
		
		if (npc->SpawnInRangeAllowed()) {
			npc -> Enable ((zVEC3)spawnPos);

#if defined(SECUROM) && !defined(COMPILING_SPACER)
			npc->variousFlags |= this->spawnFlags;
#endif

			return TRUE;
		}
		return FALSE;

	} else {
		// Ausserhalb des Radius und in Liste.
		npc -> SetSpawnInRangeAllowed (TRUE);
	};
	return FALSE;
};

//*********************************************************************************
//**																	  SummonNpc
//*********************************************************************************
//**	18.12.00	(RK)	Initial implementation
//*********************************************************************************
oCNpc* oCSpawnManager :: SummonNpc(int nInstance, const zVEC3& posSpawn, zREAL timeDelay)
{
	oCVob*	pVob = ::ogame->GetGameWorld()->CreateVob( zVOB_TYPE_NSC, nInstance );
	oCNpc*	pNpc = dynamic_cast< oCNpc* > ( pVob );

	if ( ! pNpc ) return NULL;

#if defined(SECUROM) && !defined(COMPILING_SPACER)
	pNpc->variousFlags |= this->spawnFlags;
#endif

	pNpc->SetPositionWorld(posSpawn);

	::ogame->GetGameWorld()->AddVob(pNpc);

	zVEC3 vecPosition	= posSpawn;
	zBOOL bHasFreeSpace = pNpc -> SearchNpcPosition( vecPosition );	

	if ( ! bHasFreeSpace )
	{
		::ogame->GetWorld()->RemoveVob( pNpc );
		return NULL;
	}

	pNpc -> SetSpawnInRangeAllowed	( TRUE );
	pNpc -> SetSummoned				( TRUE );
	pNpc ->	Enable					( vecPosition );

	this->SpawnNpc( pNpc, posSpawn, timeDelay );
	pNpc->Release();

	return pNpc;
}

//*********************************************************************************
//**																	   SpawnNpc
//*********************************************************************************
//**
//*********************************************************************************
oCNpc* oCSpawnManager :: SpawnNpc(int instanceNr, const zSTRING& spawnVobName, zREAL delayTime)
// Erzeuge neuen Npc und respawne
{	
	oCNpc* npc = zDYNAMIC_CAST<oCNpc>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_NSC,instanceNr));

	if (npc) 
	{
		SpawnNpc(npc,spawnVobName,delayTime);
		zRELEASE_ACCT_NONULL(npc);
	};
	return npc;
}

//*********************************************************************************
//**																	   SpawnNpc
//*********************************************************************************
//**
//*********************************************************************************
void oCSpawnManager :: SpawnNpc(oCNpc* npc, const zSTRING& spawnVobName, zREAL delayTime)
{
	// SpawnPosition ermitteln
	// a) Waypoint
	// b) Freepoint (nur falls nicht mehr als Objekte im Spiel)
	// c) anderes Vob
	zVEC3		pos (0,0,0);
	zCVob*		vob = NULL;
	zCWaypoint* wp	= ogame	-> GetWorld()->GetWayNet()->GetWaypoint(spawnVobName);
	if (wp) {
		pos	= wp	-> GetPositionWorld();
	} else if ( (vob  =  ogame -> GetWorld()->SearchVobByName(spawnVobName))!=NULL ) {
		pos = vob	-> GetPositionWorld();
	} else {
		zERR_WARNING("U: SPAWN: Spawnpoint "+spawnVobName+" not found. Npc "+npc->GetInstanceName()+" cannot be spawned.");
		return;
	}

	// SpawnpointName speichern.
	npc->spawnPoint = spawnVobName;
	SpawnNpc(npc,pos,delayTime);
}

//*********************************************************************************
//**																	   SpawnNpc
//*********************************************************************************
//**
//*********************************************************************************
void oCSpawnManager :: SpawnNpc(oCNpc* npc, const zVEC3& spawnPos, zREAL delayTime)
{
	if (!npc) return;
	
	// Spawnen niemals sofort im Sichtbereich !
	// npc -> SetSpawnInRangeAllowed	(FALSE);
	
	// Check : Wie ist das mit dem Respawnen von TA-gesteuerten NSCs nach derem Tod ?
	// Die brauchen doch nicht in die RespawnListe eingetragen werden, oder ?
	// Nur wenn sie tot sind.
	if (npc->state.HasRoutine() && !npc->IsDead()) return;
	
	// Zustandsgesteuert, PositionPoint speichern
	if (npc->state.IsAIStateDriven()) {
		npc->state.InitAIStateDriven(spawnPos);
	}

	// Listeneintrag erzeugen
	oTSpawnNode* spawnInfo	= zNEW( oTSpawnNode );
	spawnInfo -> npc		= npc;
	spawnInfo -> spawnPos	= spawnPos;
	spawnInfo -> timer		= delayTime;
	InsertInList(spawnInfo);
};

// ******************************************************
// Remove Npcs
// ******************************************************

// Temp : Debug-Method, only Safety 
// TODO : disable later
void oCSpawnManager :: CheckForInvalidDialogCamPos(zREAL dist, oCNpc* npc)
{
	zCAICamera* ai		= zCAICamera::GetCurrent();
	if (ai && ai->IsModeActive(CamModDialog)) {
		// Kamera ist in Dialog-Modus....
		// Npc auch ?
		if (npc->state.IsInState(parser.GetIndex("ZS_TALK"))) {
			if (dist>3000) {
				zERR_FAULT("U:SPAWN:Shitty DialogCam is not in valid range... >30m. Your dialog-npc may disappear...");
			}
		}
	}
};

// [BENDLIN] Addon Patch - Totenwanderung Fixes
zBOOL oCSpawnManager::UseDeadNpcRoutinePos(oCNpc* npc)
{
	if (!npc)
		return TRUE;

	// Gothic.INI (old behaviour can be reactivated!)
	static zBOOL s_spawnDeadNpcRoutinePos = -2;
	if (s_spawnDeadNpcRoutinePos == -2)
		s_spawnDeadNpcRoutinePos = (zoptions->ReadBool(zOPT_SEC_GAME, "spawnUseDeadNpcRoutinePos", TRUE)) ? TRUE : FALSE;
	if (s_spawnDeadNpcRoutinePos)
		return TRUE;

	// SPECIAL: Invalid Position (NPC not yet inserted in World)
	if (npc->GetPositionWorld() == zPOINT3(0,0,0))
		return TRUE;

	return FALSE;
};

// [BENDLIN] Addon Patch - Entfernen der Leichen konfigurierbar
zBOOL oCSpawnManager::CanDeadNpcBeRemoved(oCNpc* npc)
{
	if (!npc)
		return FALSE;

	// SPECIAL: Dragons are not removed at all
	if (npc->GetGuild() == NPC_GIL_DRAGON)
		return FALSE;

	// Gothic.INI
	static zBOOL s_spawnRemoveOnlyIfEmpty = -2;
	if (s_spawnRemoveOnlyIfEmpty == -2)
		s_spawnRemoveOnlyIfEmpty = (zoptions->ReadBool(zOPT_SEC_GAME, "spawnRemoveNpcOnlyIfEmpty", FALSE)) ? TRUE : FALSE;

	// Empty / no Mission Item
	if (s_spawnRemoveOnlyIfEmpty)
		return npc->inventory2.IsEmpty(TRUE, TRUE);
	else
		return !npc->HasMissionItem();
}

zBOOL oCSpawnManager :: CheckRemoveNpc(oCNpc* npc)
{
	if (!npc || !npc->GetHomeWorld()) return FALSE;
	// Entfernen von NSCs, die nicht im validen Zustand sind, verhindern
	if (npc->GetEM()->GetCutsceneMode() || npc->IsAPlayer()) return FALSE;
	// Tote NSCs sollen schon geprüft werden, alles andere nicht.
	if (!npc->IsConditionValid() && !npc->IsDead()) return FALSE;
	
	// Achtung : Nicht GetDistanceToVob2 benutzen, da es in der 
	// riesigen Oberwelt zu Float-Überläufen kommt.
	InitCameraPos();
	zREAL dist = (npc->GetPositionWorld() - camPos).LengthApprox();

	if (dist > SPAWN_REMOVERANGE) {

		// Spawnpoint muss auch ausserhalb der SPAWN_REMOVERANGE liegen, 
		// damit NSC entfernt werden kann.

		// [BENDLIN] Addon - Keine Totenwanderung
		zVEC3 spawnPoint;
		if (npc->IsDead() && !UseDeadNpcRoutinePos(npc))
			spawnPoint = npc->GetPositionWorld();
		else if (npc->state.HasRoutine())
			spawnPoint = rtnMan.GetRoutinePos(npc);
		else
			spawnPoint = npc->state.GetAIStatePosition();

		if ((spawnPoint - camPos).LengthApprox() < SPAWN_REMOVERANGE) {
			// Nicht entfernen, weil Spawnpoint noch in Range.
			return FALSE;	
		}

		// Tmp:Debug
		CheckForInvalidDialogCamPos(dist,npc);

		// Aus dem Level nehmen
		if ( npc->IsSummoned() ) {	
			this->DeleteNpc( npc ); 
			return TRUE; 
		
		} else {						
			
			npc->Disable();		
			// Test : AI loeschen....

		}

		npc->SetSpawnInRangeAllowed(TRUE);

		// Tote NSCs (Menschen oder Monster) werden komplett aus dem Spiel entfernt, 
		// sobald sie nicht mehr sichtbar sind und die SC-Glocke verlassen. 
		// Dies gilt aber NUR, falls dieser NSC kein Quest-Item im Inventory trägt 
		// (Flag ITEM_MISSION gesetzt). 
		// Mit Quest-Items im Inv bleiben Leichen liegen.
		if (npc->IsDead()) {
			// Tote Npcs mit MissionsItems werden hier respawned, 
			// Tote Npcs ohne MissionsItems werden im CheckInsertNpc entgültig aus Welt entfernt.
			// [BENDLIN] Addon Patch - berechneten spawnPoint verwenden (statt GetPositionWorld)
			SpawnNpc(npc, spawnPoint, 0.0f);
			return TRUE;
		}
		// Kein Spawning in Range erlaubt !
		// Falls kein TA aktiv ist, in SpawnListe aufnehmen.
		if (npc->state.IsAIStateDriven()) {
			SpawnNpc(npc,npc->state.GetAIStatePosition(),0.0f);
		}
		return TRUE;
	};
	return FALSE;
};

void oCSpawnManager :: DeleteNpc(oCNpc* npc)
// Dieser NSC darf nicht mehr respawned werden, er wird demnach komplett aus der Welt entfernt.
{
	// Safety : Noch was davon in der Liste ?
	for (int i=0; i<spawnList.GetNumInList(); i++) {
		if (spawnList[i]->npc == npc) {
			RemoveFromList(spawnList[i]);
			i--;
		}
	}
	// Und aus dem Game und den Listen austragen
	ogame->GetWorld()->RemoveVob(npc);
}

void oCSpawnManager :: DeleteAllSummoned(void)
{
	int				nNodes	= this->spawnList.GetNumInList();
	oTSpawnNode*	pNode	= NULL;
	oCNpc*			pNpc	= NULL;

	for ( int nNode = 0; nNode < nNodes; nNode++ )
	{
		pNode = this->spawnList[ nNode ];	if ( ! pNode ) continue;
		pNpc  = pNode->npc;
		
		if ( pNpc				)
		if ( pNpc->IsSummoned() )
		{
			this->DeleteNpc			( pNpc );		// list indices will change !!!
			this->DeleteAllSummoned	();				// -> recurse since we cannot rely on the indices any more

			return;
		}
	}
}

void oCSpawnManager::Archive(zCArchiver &arc)
{
	if(!arc.InSaveGame())return;

	arc.WriteInt("NoOfEntries", spawnList.GetNumInList() );
	for( int i = 0; i < spawnList.GetNumInList(); i++ )
	{
		arc.WriteObject	("npc"		, spawnList[i]->npc		 );
		arc.WriteVec3	("spawnPos"	, spawnList[i]->spawnPos );
		arc.WriteFloat	("timer"	, spawnList[i]->timer	 );
	}
	arc.WriteBool("spawningEnabled", spawningEnabled);
//#if defined(SECUROM) && !defined(COMPILING_SPACER)
	arc.WriteInt("spawnFlags", this->spawnFlags);
//#endif
}

void oCSpawnManager::Unarchive(zCArchiver &arc)
{
	if (!arc.InSaveGame())
		return;
	spawnList.EmptyList();
	
	int NoOfEntries = 0;
	arc.ReadInt("NoOfEntries", NoOfEntries);
	
	bool readFailed = (NoOfEntries < 0);
	oTSpawnNode *Entry = NULL;
	for( int i = 0; i < NoOfEntries; i++ )
	{
		Entry = zNEW(oTSpawnNode);

		Entry->npc =	(oCNpc*)arc.ReadObject("npc", Entry->npc);
		if (!Entry->npc) {
			readFailed = true;
			break;
		}
		arc.ReadVec3	("spawnPos", Entry->spawnPos);
		arc.ReadFloat	("timer", Entry->timer);
		spawnList.Insert(Entry);
	}

	if (!readFailed) {
		arc.ReadBool("spawningEnabled", spawningEnabled);
		arc.ReadInt("spawnFlags", this->spawnFlags);
	} else {
		// Set default values for safety
		spawningEnabled = TRUE;
		this->spawnFlags = 0;
	}
}
