/******************************************************************************** 
 
     $Workfile:: oWorld.cpp           $                $Date:: 19.03.01 21:28   $
     $Revision:: 64                   $             $Modtime:: 19.03.01 21:19   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oWorld.cpp $
 * 
 * 64    19.03.01 21:28 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 63    18.03.01 18:49 Edenfeld
 * Demo Geschichten
 * 
 * 62    15.03.01 14:59 Wohlers
 * 
 * 61    14.03.01 21:30 Wohlers
 * 
 * 60    14.03.01 21:17 Wohlers
 * 
 * 59    13.02.01 19:27 Wohlers
 * 
 * 58    9.02.01 19:20 Speckels
 * 
 * 57    7.02.01 12:53 Moos
 * 
 * 56    5.02.01 18:01 Moos
 * 
 * 55    31.01.01 2:07 Wohlers
 * 
 * 54    30.01.01 15:03 Moos
 * 
 * 52    28.01.01 19:12 Wohlers
 * 
 * 51    26.01.01 14:18 Wohlers
 * 
 * 50    25.01.01 14:48 Moos
 * 
 * 49    24.01.01 18:37 Wohlers
 * 
 * 48    22.01.01 22:38 Wohlers
 * 
 * 47    18.01.01 2:00 Wohlers
 * 
 * 46    10.01.01 18:56 Speckels
 * 
 * 45    18.12.00 20:21 Wohlers
 * 
 * 44    3.11.00 16:08 Wohlers
 * 
 * 43    2.11.00 16:03 Speckels
 * 
 * 42    27.10.00 11:11 Moos
 * 
 * 41    26.10.00 14:16 Moos
 * 
 * 40    23.10.00 18:58 Moos
 * 
 * 39    23.10.00 18:19 Moos
 * 
 * 38    23.10.00 16:58 Moos
 * 
 * 37    20.10.00 16:41 Wohlers
 * 
 * 36    20.10.00 11:30 Moos
 * 
 * 35    19.10.00 21:49 Wohlers
 * 
 * 34    18.10.00 18:55 Wohlers
 * 
 * 33    18.10.00 0:51 Wohlers
 * 
 * 32    17.10.00 20:06 Moos
 * 
 * 31    16.10.00 12:58 Moos
 * 
 * 30    16.10.00 11:44 Moos
 * 
 * 29    13.10.00 19:57 Moos
 * 
 * 28    9.10.00 19:31 Moos
 * 
 * 27    19.09.00 20:57 Wohlers
 * 
 * 26    8.09.00 13:57 Wohlers
 * 
 * 25    2.09.00 9:24 Wohlers
 * 
 * 24    30.08.00 18:55 Moos
 * 
 * 23    28.08.00 12:15 Herget
 * 
 * 22    25.08.00 0:33 Wohlers
 * 
 * 21    17/08/00 13:55 Luesebrink
 * 
 * 20    17.08.00 2:38 Rueve
 * Bugfix 1694
 * 
 * 19    10.08.00 12:21 Herget
 * 
 * 18    9.08.00 12:53 Wohlers
 * 
 * 17    8.08.00 18:28 Herget
 * 
 * 16    3.08.00 20:51 Wohlers
 * 
 * 15    2.08.00 14:25 Wohlers
 * 
 * 14    27.07.00 17:04 Wohlers
 * 
 * 13    27.07.00 15:03 Wohlers
 * 
 * 12    21.07.00 15:35 Wohlers
 * 
 * 11    21.07.00 14:43 Wohlers
 * 
 * 10    19.07.00 20:05 Wohlers
 * 
 * 9     7.07.00 12:42 Wohlers
 * Gothic 0.87
 * 
 * 8     5.07.00 12:22 Wohlers
 * 
 * 6     5.06.00 22:36 Wohlers
 * uSrc 05.06.00
 * 
 * 5     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 4     7.05.00 22:48 Wohlers
 * LoadWorld -> zRELEASE Bug bei LevelCompo gefixed
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 20    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 19    30.03.00 20:35 Wohlers
 * Bugfixes ( Wegnetz, TAs etc. )
 * 
 * 18    29.03.00 15:32 Wohlers
 * Various Bugfixes ( Waynet, Klettern )
 * 
 * 17    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 16    23.02.00 3:47 Wohlers
 * Fixes
 * 
 * 15    22.02.00 20:35 Wohlers
 * 
 * 14    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 13    10.01.00 16:40 Wohlers
 * Add/RemoveVob Nullpointer erlaubt
 * 
 * 12    10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 11    6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 9     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 8     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 * 7     11.11.99 13:58 Wohlers
 * EnableVob um "Parent" erweitert
 * 
 * 6     9.11.99 15:35 Wohlers
 * MOBSI Bugfixes / Firehandling V0.5
 * Externals V0.69
 * 
 * 5     22.10.99 13:36 Wohlers
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 64 $ ($Modtime: 19.03.01 21:19 $)



#include "zCore.h"

#include "oWorld.h"
#include "oText.h"
#include "oRoutine.h"
#include "oobjfactory.h"
#include "zplayergroup.h"
#include "zSky.h"

#include "zMusic.h"

// oCWorld
#include "oNpc.h"
#include "oItem.h"
#include "oGame.h"
#include "oMobInter.h"
#include "zWayNet.h"
#include "zOption.h"
#include "oMagic.h"
#include "oSpawn.h"
#include "oBarrier.h"
#include "oCollisionObjectMiscChar.h"

#include "zAccount.h"

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

zCLASS_DEFINITION (oCWorld, zCWorld, 0, 0)

// ***************************************************************************************
// CON / DESTRUCTOR
// ***************************************************************************************


// Compare-function for sorted lists

static int CompareVobsByID(zCVob* vob1, zCVob* vob2)
{
	return (vob1 - vob2);
//	return vob1->GetVobID() - vob2->GetVobID();
};

static int CompareNpcsByID(oCNpc* vob1, oCNpc* vob2)
{
	return (vob1 - vob2);
//	return vob1->GetVobID() - vob2->GetVobID();
};

static int CompareItemsByID(oCItem* vob1, oCItem* vob2)
{
	return (vob1 - vob2);
//	return vob1->GetVobID() - vob2->GetVobID();
};


oCWorld :: oCWorld()
{
	zERR_MESSAGE(9,0,"U: (oCWorld) Construction");

    oCCollObjectCharacter::S_RegisterCollisionTestFuncs();   // Registriere die NPC-Kollisionsroutinen

	voblist			= zNEW( oTVobList() );
	voblist_npcs	= zNEW( oTVobListNpcs() );
	voblist_items	= zNEW( oTVobListItems() );

	voblist			-> SetCompare	(&CompareVobsByID);
	voblist_npcs	-> SetCompare	(&CompareNpcsByID);
	voblist_items	-> SetCompare	(&CompareItemsByID);

	this->SetSkyControlerOutdoor( zNEW(oCSkyControler_Barrier)() );

}

/* ----------------------------------------------------------------------
	
    oCWorld :: ~oCWorld()	

	30.08.2000	[Moos]	
                Anpassung an Änderung in zplayergroup.cpp


   ---------------------------------------------------------------------- */

oCWorld :: ~oCWorld()
{
	DisposeWorld();
    zCPlayerGroup::GetAllPlayerGroup()->ResetPlayerList(); // [Moos] ; hat jetzt denselben Effekt wie
  //	zRELEASE(oCNpc::player);

	delete voblist;			voblist			= NULL;
	delete voblist_npcs;	voblist_npcs	= NULL;
	delete voblist_items;	voblist_items	= NULL;

	zERR_MESSAGE(9,0,"U: (oCWorld) Destruction");
}

// ***************************************************************************************
// CREATION
// ***************************************************************************************

oCVob* oCWorld :: CreateVob (const zTVobType type, const zSTRING &name)
{
	zERR_MESSAGE(10,0,"U: (oCWorld::CreateVob) "+name);
	int index = parser.GetIndex(name);
	if (index<0) zERR_FAULT("U: OBJ: Script-object "+name+" not found ! Please correct instancename !");
	return CreateVob(type,index);
}

oCVob* oCWorld :: CreateVob     (const zTVobType type, const int index)
{
	zERR_MESSAGE(10,0,"U: (oCWorld::CreateVob) "+zSTRING(index));

    oCVob* v = NULL;
	
	switch (type)
	{
		case zVOB_TYPE_NSC    :	
			zERR_ASSERTT(dynamic_cast<oCObjectFactory*>(zfactory),"U: (oCWorld::CreateVob) Objectfactory has wrong type");			
			v = dynamic_cast<oCObjectFactory*>(zfactory)->CreateNpc(index);			
				
			break;
        case zVOB_TYPE_ITEM   : 
			zERR_ASSERTT(dynamic_cast<oCObjectFactory*>(zfactory),"U: (oCWorld::CreateVob) Objectfactory has wrong type");
			v = dynamic_cast<oCObjectFactory*>(zfactory)->CreateItem(index);
			break;
	};

	return v;
}

// ***************************************************************************************
// LOAD / SAVE
// ***************************************************************************************


void oCWorld :: Archive (zCArchiver& arc)
{
	zCWorld::Archive(arc);
	
	if (arc.InSaveGame()) {
		// a) Alle NSCs speichern, die nicht physikalisch (nur logisch) im Level sind.
		int		npcCount = 0;
		oCNpc*	npc				= NULL;
		// Diese zaehlen.
		zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
		while (node) {
			npc		= node->GetData();
			node	= node->GetNextInList();
			if (!npc->IsSelfPlayer() && !npc->GetHomeWorld()) npcCount++;
		}
		arc.WriteInt("npcCount",npcCount);

		// und speichern.		
		zSTRING arcID;
		npcCount	= 0;
		node		= GetVobListNpcs()->GetNextInList();
		while (node) {
			npc		= node->GetData();
			node	= node->GetNextInList();
			if (!npc->IsSelfPlayer() && !npc->GetHomeWorld()) {
				arcID = "npc" + zSTRING(npcCount);
				arc.WriteObject(arcID.ToChar(),npc);
				npcCount++;
			}
		}
		
		// SpawnManager sichern
		if (ogame) ogame->GetSpawnManager()->Archive(arc);
	}
}

void oCWorld :: Unarchive (zCArchiver& arc)
{
	zCWorld::Unarchive(arc);
	
	if (arc.InSaveGame()) {
		
		oCNpc* npc		= NULL;
		int npcCount	= arc.ReadInt("npcCount");

		// und laden.		
		zSTRING arcID;
		for (int i=0; i<npcCount; i++) {
			arcID	= "npc"+zSTRING(i);
			npc		= (oCNpc*)arc.ReadObject1(arcID.ToChar());
			InsertInLists(npc);
			zRELEASE(npc);
		}
		
		// SpawnManager sichern
		if (ogame) ogame->GetSpawnManager()->Unarchive(arc);
	}
}

zBOOL oCWorld ::	SaveWorld (const zSTRING& fileName, const zTWorldSaveMode saveMode, const zBOOL	writeBinary, const zBOOL _saveLevelMesh)
{
	zERR_MESSAGE(9,0,"U: (oCWorld::SaveWorld) "+fileName);

	if (GetWayNet()) {
#ifdef COMPILING_SPACER
		// Ausrichtung und Position aus aktuellen SpacerVobs uebernehmen
		// ansonsten kriegt's Waynet evt. Aenderungen im Spacer nicht mit.
		if (GetWayNet()) GetWayNet()->UpdateVobDependencies(); 
#endif
		GetWayNet()->ClearVobDependencies(); 
	}
	zBOOL result = zCWorld::SaveWorld(fileName,saveMode,writeBinary,_saveLevelMesh);
#ifdef COMPILING_SPACER
	if (GetWayNet()) GetWayNet()->CreateVobDependencies(this); 
#endif
	return result;
}

zBOOL oCWorld :: LoadWorld (const zSTRING& fileName, const zTWorldLoadMode loadMode)
{
	zERR_MESSAGE(9,0,"U: (oCWorld::LoadWorld) "+fileName);

	zBOOL	success		= FALSE;
	zSTRING curFileName = fileName;
	curFileName.Upper();


	if (loadMode!=zCWorld::zWLD_LOAD_GAME_SAVED_DYN) {
		// setze worldFilename (ausser beim Laden von nur dynamischen Daten)
		worldFilename = curFileName;	
		// setze worldName
		zFILE_FILE path(worldFilename);
		worldName = path.GetFilename();
	}
	
	if (curFileName.Search(".3DS")>0) {
		zCVob* levelVob = zNEW( zCVobLevelCompo );		
		levelVob->SetVobName("Level-Vob");
		levelVob->SetVisual	(curFileName);
		AddVob (levelVob);
		zRELEASE(levelVob);
		success = TRUE;

	} 
	else
	{
		zoptions->ChangeDir( DIR_WORLD );
		success = zCWorld :: LoadWorld(curFileName,loadMode);
	}
	return success;
}

zCTree<zCVob>* oCWorld::AddVobAsChild (zCVob *childVob, zCTree<zCVob>* parentVob)
{
	if (!childVob) return NULL;

	InsertVobInWorld(childVob);// logisches Eintragen des Vobs in die Welt

//	oCVob* ovob = dynamic_cast<oCVob*>(childVob);
//	if (ovob) {
//		ovob->PreInsert	();	
//	};
		
	zCTree<zCVob>* tree = zCWorld::AddVobAsChild(childVob, parentVob);
//	if (ovob) ovob->PostInsert	();		

	zERR_MESSAGE(10,0,"U: (oCWorld::AddVobAsChild) "+childVob->GetVobName()+" ("+zSTRING(childVob->GetVobID())+")");
	
	return tree;
};

void oCWorld :: RemoveVob (zCVob *vob)
{
	// aus der Welt und aus der Logik entfernen -> Vob für immer dahin !
	if (!vob) return;
	zERR_MESSAGE(10,0,"U: (oCWorld::RemoveVob) "+vob->GetVobName()+" ("+zSTRING(vob->GetVobID())+")");

	zBOOL wasInWorld = (vob->GetHomeWorld()!=NULL);

	RemoveFromLists(vob);
	
	if (wasInWorld) zCWorld::RemoveVob(vob);							// RefCtr geht hier Minus eins !
};

void oCWorld::InsertVobInWorld(zCVob *vob)
{	
	if (vob) InsertInLists(vob);	// Hier sollte die Vob-ID schon vergeben sein
};

// Aktivieren eines Vobs (einfuegen in das World-Mesh)
void oCWorld::EnableVob(zCVob* vob,zCVob* papa)
{	
	zERR_ASSERTT(vob,"U: (oCWorld::EnableVob) Can't enable null-pointer-vob");

	if (vob->GetHomeWorld()) return;

	zERR_MESSAGE(9,0,"U: (oCWorld::EnableVob) "+vob->GetVobName());
	
	zERR_ASSERTT(dynamic_cast<oCVob*>(vob),"U: (oCWorld,) You can only enable instances of oCVob until other vobs will be stored in internal vob-list");

	oCNpc* npc = dynamic_cast<oCNpc*>(vob);
	if (npc) {
		vob->globalVobTreeNode=NULL;
	}

	// RefCtr geht hier +1
	if (papa)	zCWorld::AddVobAsChild(vob,papa);			// physikalisch in die Welt einfügen
	else		zCWorld::AddVobAsChild(vob,&globalVobTree);  
	
	vob->SetSleeping(FALSE);	
}

void oCWorld::DisableVob(zCVob* vob)
// Deaktivieren eines Vobs (entfernen aus dem World-Mesh)
// bleibt aber noch in den Listen enthalten
{
	zERR_ASSERTT(vob,"U: (oCWorld::DisableVob) Can't disable null-pointer-vob");

	if (!vob->GetHomeWorld())	return;
	if (!voblist->IsInList(vob))	{
#ifdef _DEBUG
		zERR_FAULT("U: Disabling Vob which is not in List");
#endif
	}

	zERR_MESSAGE(9,0,"U: (oCWorld::DisableVob) "+vob->GetVobName());
	
	zERR_ASSERTT(dynamic_cast<oCVob*>(vob),"U: (oCWorld::DisableVob) You can only disable instances of oCVob until other vobs will be stored in internal vob-list");

	zCWorld::RemoveVobSubtree(vob);
	
	vob->SetSleeping (TRUE);	
};

zCVob* oCWorld::SearchVob(zCVob *vob, zCTree<zCVob>* vobNode)
{
	zCVob* found_vob = zCWorld::SearchVob(vob,vobNode);
	if (found_vob || vobNode) return found_vob;
	
	oTVobList* list_node = voblist;
	while (list_node)
	{
		if (list_node->GetData() == vob) return vob;
		list_node = list_node->GetNextInList();
	};

	return 0;
}

zCVob* oCWorld::SearchVobByID	(const zTVobID	vobID	, zCTree<zCVob>* vobNode)
{
	zCVob* found_vob = zCWorld::SearchVobByID(vobID,vobNode);
	if (found_vob || vobNode) return found_vob;

	// binaeres suchen?
	oTVobList* list_node = voblist;	
	while (list_node)
	{
		found_vob = list_node->GetData();
		if (found_vob && found_vob->GetVobID() == vobID) return found_vob;
		list_node = list_node->GetNextInList();
	};

	return 0;
};

zCVob* oCWorld::SearchVobByName	(const zSTRING& vobName)
{
	zCVob* found_vob = zCWorld::SearchVobByName(vobName);
	if (found_vob) return found_vob;

	oTVobList* list_node = voblist;	
	while (list_node)
	{
		found_vob = list_node->GetData();
		if (found_vob && found_vob->GetVobName() == vobName) return found_vob;
		list_node = list_node->GetNextInList();
	};

	return 0;
};

// CODECHANGE [STEFAN]
void oCWorld::SearchVobListByName (const zSTRING& vobName, zCArray<zCVob*>& resultVobList)
{
	zCWorld::SearchVobListByName(vobName, resultVobList); 

	zCVob* found_vob;
	oTVobList* list_node = voblist;	
	while (list_node)
	{
		found_vob = list_node->GetData();
		if (found_vob && found_vob->GetVobName() == vobName)
			resultVobList.Insert (found_vob);
		list_node = list_node->GetNextInList();
	};
};
// CODECHANGE [STEFAN] END

void oCWorld::TraverseVobList(zCVobCallback &callback, void *callbackData)
{
	oTVobList* list_node = voblist;
	zCVob* vob;
	while (list_node)
	{
		vob = list_node->GetData();
		if (vob) callback.HandleVob(vob, callbackData);
		list_node = list_node->GetNextInList();
	};	
};

void oCWorld::ClearNpcPerceptionVobLists()
{
	// Die Wahrnehmung von an globalen Cutscenes teilnehmenden Vobs 
	// wird unterbunden. Startet eine Cutscene, so werden die 
	// Wahrnehmungslisten aller (!) Vobs gelöscht.
	// ogame->ClearNpcPerceptionVobList();
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
	while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		if (!npc->IsSelfPlayer()) {
			// Voblisten löschen
			npc -> ClearPerceptionLists();
			npc -> SetEnemy(NULL);
		};
	};	
};

///
// protected methods
///

// Einfügen des Vobs in die diversen Vob-Listen
void zCCFASTCALL oCWorld::InsertInLists(zCVob* v)
{
	// Refs: 1 - zCWorld
	//       2 - oCWorld - vobList
	//       3 - oCWorld - item/nscList
	
	// nur oCVobs in der Liste verwalten
	//changed[dennis]
//	if (dynamic_cast<oCVob*>(v) && !dynamic_cast<oCMOB*>(v) && !voblist -> IsInList(v))	{ 
	if (zDYNAMIC_CAST<oCVob>(v)) {	
		if (!voblist -> IsInList(v)) { 
			// allgemeine Liste aller Vobs:
			voblist	-> InsertSort(v);							
			// Welt hat Kenntnis über diesen Vob
			zADDREF_ACCT(v);
			// v -> AddRefVobSubtree();
		}
		if (zDYNAMIC_CAST<oCNpc>(v)	&& !voblist_npcs -> IsInList(static_cast<oCNpc*>(v))) {
			// npc-liste
			voblist_npcs -> InsertSort(static_cast<oCNpc*> (v));
			// Welt hat Kenntnis über diesen Vob
			zADDREF_ACCT(v);
			// v -> AddRefVobSubtree();
		
		} else if (zDYNAMIC_CAST<oCItem>(v) && !voblist_items -> IsInList(static_cast<oCItem*>(v))) {
			// item-liste
			voblist_items -> InsertSort(static_cast<oCItem*> (v));	
			// Welt hat Kenntnis über diesen Vob
			zADDREF_ACCT(v);
			// v -> AddRefVobSubtree();
		}
	}
};

// Entfernen des Vobs aus den diversen Vob-Listen
void zCCFASTCALL oCWorld::RemoveFromLists(zCVob* v)
{
    if (v->GetRefCtr()<=0){
        zERR_WARNING("RemoveFromList(vob) called from vob destructor!\n");
        return; // [Moos] Dann sind wir schon im Destruktor von v, und v kann gar nicht mehr in den Listen sein
                // Sollte allerdings gar nicht vorkommen.
    }
    
    zADDREF_ACCT(v); // [Moos] Damit das Vob erst am Ende beseitigt wird; dynamic_cast stürzt sonst ab.

	//changed[dennis]
//	if (dynamic_cast<oCVob*>(v) && !dynamic_cast<oCMOB*>(v)) {
	if (zDYNAMIC_CAST<oCVob>(v) ) {
		
		zERR_ASSERT(v->GetRefCtr()>=1); // allgemeine Vobs brauchen nur refctr 1 [Moos]

		if (voblist->IsInList(static_cast<oCVob*>(v))) {
			// allgemeine Liste aller Vobs:
			voblist	-> Remove(v);		
			// FIXME : RemoveVobSubtree funktioniert nur, wenn Objekt in Welt eingefügt ist
			//if (v->GetHomeWorld())	v -> ReleaseVobSubtree();
			//else					v -> Release();			
			zRELEASE_ACCT_NONULL(v);
		}
	} else {
		// Wenn es kein oCVob war, dann ist auch der Rest uninteressant
        zRELEASE_ACCT_NONULL(v); // [Moos] Jetzt ist die Sache gefahrlos.
		return;
	};

	if (zDYNAMIC_CAST<oCNpc>(v) && voblist_npcs->IsInList(static_cast<oCNpc*>(v))) {
		// npc-liste
		zERR_ASSERT(v->GetRefCtr()>=1); // [Moos] eigentlich Schwachsinn; jedes zCObjekt erfüllt das...

		oCNpc* npc = (static_cast<oCNpc*>(v));
		// Hier auf Nummer sicher gehen, sonst koennen fehlerhaft liegengebleibene NSCs (Save/Loadgame)
		// noch Referenzen auf "alte" Objekte haben.
		npc->CleanUp();
		//npc -> ClearPerceptionLists	();
		//npc -> state.SetRoutine		(NULL,NULL);	// Alte rtn-route wird geloescht -> wichtig falls NSCs liegenbleiben -> Route haette Verweise auf Objekte, die es nicht mehr gibt.

		voblist_npcs -> Remove(npc);
				
		zRELEASE_ACCT_NONULL(v);
	
	} else if (zDYNAMIC_CAST<oCItem>(v) && voblist_items->IsInList(static_cast<oCItem*>(v))) {
		zERR_ASSERT(v->GetRefCtr()>=1);
		// item-liste
		voblist_items -> Remove(static_cast<oCItem*>(v));
		//if (v->GetHomeWorld())	v -> ReleaseVobSubtree();
		//else					v -> Release();
		zRELEASE_ACCT_NONULL(v);		
	};

    zRELEASE_ACCT_NONULL(v); // [Moos] Jetzt ist die Sache gefahrlos.
};

void oCWorld :: DisposeVobs()
{
    // Effizienter: Lösche immer den Ersten aus jeder Lsite

    {
    	oCNpc* npc = NULL;
    	zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
    	while (node) {
		    npc		= node->GetData();
		    node	= node->GetNextInList();

		    npc -> CleanUp(); // [Moos] Das hier muss vor zCWorld::DisposeWorld erledigt werden, da zCWorld::DisposeWorld diese listen hier teilweise leert...
            npc -> DestroySpellBook();
            npc -> RemoveFromAllSlots(false);

            zRELEASE_ACCT_NONULL(npc);
            GetVobListNpcs()->Remove(npc);

            node = GetVobListNpcs()->GetNextInList();
        };
    }

    {
        zCListSort<oCItem> *node = GetVobListItems()->GetNextInList();
        while (node){
            oCItem *v = node->GetData();
            GetVobListItems()->Remove(v);
            zRELEASE(v);

            node = GetVobListItems()->GetNextInList();
        }

    }

    {
        zCListSort<zCVob> *node = GetVobList()->GetNextInList();
        while (node){
            zCVob *v = node->GetData();
            GetVobList()->Remove(v);
            zRELEASE(v);

            node = GetVobList()->GetNextInList();
        }

    }

    zCWorld::DisposeVobs();
// Alter Code:
/*
    {
    	oCNpc* npc = NULL;
    	zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
    	while (node) {
		    npc		= node->GetData();
		    node	= node->GetNextInList();

		    npc -> ClearPerceptionLists(); // [Moos] Das hier muss vor zCWorld::DisposeWorld erledigt werden, da zCWorld::DisposeWorld diese listen hier teilweise leert...
            npc -> DestroySpellBook();
            npc -> RemoveFromAllSlots(false);
        };
    }

	zCWorld :: DisposeVobs();

    zCVob* vob = NULL;
    zCListSort<zCVob>* node = GetVobList()->GetNextInList();
    while (node) {
		vob			= node->GetData();
//        node->data	= NULL; // [Moos] wird nachher von RemoveFromLists erledigt.
//		node		= node->GetNextInList();
		
		assert(vob->GetRefCtr()>=1);

		RemoveFromLists(vob);

        node = GetVobList()->GetNextInList(); // [Moos] Da gelöschte NPCs die Liste durcheinanderbrignen, fangen wir lieber immer von Anfang an.
	};
    
    zERR_ASSERT(GetVobList()->GetNumInList() == 0);

    GetVobList()->DeleteList(); 

    */
};

void oCWorld :: DisposeWorld ()				// deletes (!) every vob in the world
// Wird als Folge von DisposeWorld aufgerufen und
// erfasst auch alle NSCs, die zwar logisch, 
// aber nicht physikalisch in der Welt sind,
// weil sie sich ausserhalb der AI-Aktivierungsreichweite 
// befinden. Diese werden aus den aktiven Voblisten mit 
// RemoveFromLists entfernt.
{
    DisposeVobs();

    /* Macht alles DisposeVobs()
    {
    	oCNpc* npc = NULL;
    	zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
    	while (node) {
		    npc		= node->GetData();
		    node	= node->GetNextInList();

		    npc -> ClearPerceptionLists(); // [Moos] Das hier muss vor zCWorld::DisposeWorld erledigt werden, da zCWorld::DisposeWorld diese listen hier teilweise leert...
            npc -> DestroySpellBook();
            npc -> RemoveFromAllSlots(false);
        };
    }
    */

	zCWorld::DisposeWorld();

    /*
    {
    	zCVob* vob = NULL;
    	zCListSort<zCVob>* node = GetVobList()->GetNextInList();
    	while (node) {
		    vob		= node->GetData();
            node->data = NULL;
		    node	= node->GetNextInList();
		    assert(vob->GetRefCtr()>=1);

			if (vob->GetHomeWorld())	vob -> ReleaseVobSubtree();
			else					    vob -> Release();
	    };
        
        GetVobList()->DeleteList();
    }


    // [Moos] Das folgende ist ein Leakfix und Ersatz für Kronkel-Leakfixes in oCInventory und ~oCMobContainer. 
    // wenn es hier noch Crashes gibt, erstmal die neuen oInventory.cpp und oMobInter.cpp holen.
    // Wenn das nicht hilft, zu mir kommmen.

    {
    	oCItem* item = NULL;
    	zCListSort<oCItem>* node = GetVobListItems()->GetNextInList();
    	while (node) {
		    item		= node->GetData();
            node->data = NULL;
		    node	= node->GetNextInList();
		    assert(item->GetRefCtr()>=1);

			if (item->GetHomeWorld())	item -> ReleaseVobSubtree();
			else					    item -> Release();
	    };
        
        GetVobListItems()->DeleteList();
    }

    {
    	zCVob* vob = NULL;
    	zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
    	while (node) {
		    vob		= node->GetData();
            node->data = NULL;
		    node	= node->GetNextInList();
		    assert(vob->GetRefCtr()>=1);

			if (vob->GetHomeWorld())	vob -> ReleaseVobSubtree();
			else					    vob -> Release();
	    };
        
        GetVobListNpcs()->DeleteList();
    } */


    /* Alte Methode
    {
    	oCNpc* npc = NULL;
    	zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
    	while (node) {
		    npc		= node->GetData();
		    node	= node->GetNextInList();
		    assert(npc->GetRefCtr()>=2);
		    // Damits nicht beim RemoveFromList gelöscht wird.
		    npc -> AddRef();
		    RemoveFromLists(npc);
		    npc -> Release();
	    };
    } */
    
};

/*
zBOOL oCWorld :: DisposeVobs (zCTree<zCVob> *treeNode)
// releases (!) every vob in the world, resets waynet, resets cutscenePlayer
{
	// Npc-Liste weghauen
    oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
    while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		npc -> CleanUp();
        npc -> DestroySpellBook();
        npc -> RemoveFromAllSlots(false);
		npc -> Release();
	}
	GetVobListNpcs()->DeleteList();
	// Item-Liste weghauen
    oCItem* item = NULL;
    zCListSort<oCItem>* nodeI = GetVobListItems()->GetNextInList();
    while (node) {
		item	= nodeI->GetData();
		nodeI	= nodeI->GetNextInList();
		item -> Release();
	}
	GetVobListItems()->DeleteList();
	// Vob-Liste weghauen
    zCVob* vob = NULL;
    zCListSort<zCVob>* nodeV = GetVobList()->GetNextInList();
    while (node) {
		vob		= nodeV->GetData();
		nodeV	= nodeV->GetNextInList();
		vob -> Release();
	}
	GetVobList()->DeleteList();

	return zCWorld::DisposeVobs(treeNode);
};

void oCWorld::DisposeWorld()
{
    oCNpc* npc = NULL;
    zCListSort<oCNpc>* node = GetVobListNpcs()->GetNextInList();
    while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();

		npc -> ClearPerceptionLists(); // [Moos] Das hier muss vor zCWorld::DisposeWorld erledigt werden, da zCWorld::DisposeWorld diese listen hier teilweise leert...
        npc -> DestroySpellBook();
        npc -> RemoveFromAllSlots(false);
    };
	zCWorld::DisposeWorld();
};
*/






















// ***************************************************************************************
// WORLDTIMER
// ***************************************************************************************

oCWorldTimer :: oCWorldTimer ()
{
	worldTime	= 0.0f;
	day			= 0;
}

oCWorldTimer :: ~oCWorldTimer ()
{
}

void oCWorldTimer :: Timer ()
{
	worldTime += ztimer.GetFrameTimeF();
	if (worldTime > WLD_TICKSPERDAY) {
		worldTime -= WLD_TICKSPERDAY;
		day++;
		
		// RefreshMechanismen
		if (ogame) ogame->RefreshNpcs	();
	}
	// Routines weitermachen ?
	rtnMan.CheckRoutines();
};	

int oCWorldTimer :: GetDay ()
{
	return day;
}

void oCWorldTimer :: SetDay (int dayNr)
{
	day = dayNr;
}

void oCWorldTimer :: GetTime (int& hour, int& min)
{
	hour	= (int)(worldTime / WLD_TICKSPERHOUR);
	min		= (int)(worldTime - hour * WLD_TICKSPERHOUR) / WLD_TICKSPERMIN;
}

void oCWorldTimer :: SetTime (int hour, int min)
{
	worldTime	= (hour%24) * WLD_TICKSPERHOUR + (min%60) * WLD_TICKSPERMIN;
}

zREAL oCWorldTimer :: GetFullTime ()
{
	return (worldTime + day*WLD_TICKSPERDAY);
}

void oCWorldTimer :: SetFullTime (zREAL fullTime)
{
	day			= fullTime / WLD_TICKSPERDAY;
	worldTime	= fullTime - (day * WLD_TICKSPERDAY);
}

// CODECHANGE [HERGET]
zSTRING oCWorldTimer :: GetTimeString()
{
	int hour,min;
	zSTRING m;
	GetTime (hour,min);
	m = zSTRING(min);
	if (m.Length() == 1 )
		m = '0' + m;
	return zSTRING(hour)+":"+m;
}
// CODECHANGE [HERGET] END

zBOOL oCWorldTimer :: IsLater(int h1, int m1)
// Ist es schon später als die angegebene Uhrzeit ?
{
	zREAL time1 = h1 * WLD_TICKSPERHOUR + m1 * WLD_TICKSPERMIN + (WLD_TICKSPERMIN - 1);
	return (worldTime>time1);
}

zBOOL oCWorldTimer :: IsLaterEqual(int h1, int m1)
// Ist es schon später als die angegebene Uhrzeit ?
{
	zREAL time1 = h1 * WLD_TICKSPERHOUR + m1 * WLD_TICKSPERMIN + (WLD_TICKSPERMIN - 1);
	return (worldTime>=time1);
}

zBOOL oCWorldTimer :: IsTimeBetween(int h1, int m1, int h2, int m2)
{
	zREAL time1 = zREAL(h1) * WLD_TICKSPERHOUR + zREAL(m1) * WLD_TICKSPERMIN;
	zREAL time2 = zREAL(h2) * WLD_TICKSPERHOUR + zREAL(m2) * WLD_TICKSPERMIN;

	// Endzeit Minus 1 Minute, damit es bei Tagesabläufen nicht zu einer zeitlichen 
	// Überschneidung kommt und damit zu einem Bug ! 
	// TA(0,6,ZS_Sit) TA (18,0,ZS_Sit) 
	// -> Bei RestartRoutine und 0 Uhr wird letzterer TA-Punkt zu unrecht aktiviert.
	// ausser, wenn beide Zeiten gleich sind.... (End Overlay Befehl)
	if (time2!=time1) time2 -= WLD_TICKSPERMIN;

	if (time2<time1) 
		// Tageswechsel ?
		return ((worldTime>=time1) || (worldTime<=time2));
	else
		return ((time1<=worldTime) && (worldTime<=time2));	
}

int oCWorldTimer :: GetPassedTime (zREAL fullTime)
// Liefert Anzahl der vergangenen Spielminuten seit fullTime.
{
	zREAL diff = GetFullTime() - fullTime;
	return (int)(diff / WLD_TICKSPERMIN);
}

zREAL oCWorldTimer :: GetSkyTime()
// Return Time for Dieters Skycontroller
{
	// Tageszeit mit SetTime() zu setzen 
	// (0..1, 0=12h, 0.5=24h, 1=12h). 
	//	0.5	=	 0 Uhr		= 0
	//  0.75=	 6 Uhr		= 6*60
	//	1	=	12 Uhr		= 12*60
	//	0.25=	18 Uhr		= 18*60
	//	0.5	=	24 Uhr		= 24*60
	
	//  0 - 24  =  0.0 - 2.0
	zREAL y = (worldTime / (WLD_TICKSPERHOUR * 24)) + 0.5;
	while (y>1.0f) y -= 1.0f;
	return y;
}

zBOOL oCWorldTimer :: IsDay()
{
	return IsTimeBetween(6,30,18,30);
}

zBOOL oCWorldTimer :: IsNight()
{
	return !IsTimeBetween(6,30,18,30);
}

void oCWorldTimer :: AddTime (int &h, int &m, int dh, int dm)
{
	m += dm;
	h += (m / 60);
	m  = (m % 60);
	h += dh;
	if (h>23) h = h % 24;
}

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
