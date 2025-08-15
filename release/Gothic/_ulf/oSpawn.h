
/******************************************************************************** 
 
     $Workfile:: oSpawn.h             $                $Date:: 13.02.01 19:11   $
     $Revision:: 9                    $             $Modtime:: 13.02.01 18:42   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:

 * 
 *********************************************************************************/

#ifndef __OSPAWN__
#define __OSPAWN__

#include "zTypes.h"
#include "zString.h"
#include "zVob.h"

class oCNpc;

class oCSpawnManager
{
public:
	oCSpawnManager									();
	~oCSpawnManager									();

	zBOOL					IsSpawningEnabled		();
	void					SetSpawningEnabled		(zBOOL spawnOn);

	void					SpawnImmediately		(zBOOL resetSpawnNodeTime = FALSE);

	void					ClearList				();
	void					CheckInsertNpcs			();
	zBOOL					CheckRemoveNpc			(oCNpc* npc);

	oCNpc*					SpawnNpc				(int instanceNr, const zSTRING& spawnVobName, zREAL delayTime);
	void					SpawnNpc				(oCNpc* npc, const zSTRING& spawnVobName, zREAL delayTime);
	void					SpawnNpc				(oCNpc* npc, const zVEC3& spawnPos, zREAL delayTime);

	oCNpc*					SummonNpc				( int nInstance, const zVEC3& posSpawn, zREAL timeDelay );

	void					DeleteNpc				(oCNpc* npc);
	void					DeleteAllSummoned		( void );

	static void				SetInsertRange			(zREAL rangecm);
	static zREAL			GetInsertRange			();
	static void				SetRemoveRange			(zREAL rangecm);
	static zREAL			GetRemoveRange			();
	static void				SetSpawnTime			(zREAL timems);
	static zREAL			GetSpawnTime			();

	void					ShowDebugInfo			();

	void					Archive					(zCArchiver &arc);
	void					Unarchive				(zCArchiver &arc);

//#if defined(SECUROM) && !defined(COMPILING_SPACER)
	int						GetSpawnFlags			()			{ return spawnFlags;	};
	void					SetSpawnFlags			(int flags)	{ spawnFlags = flags;	};
	void					AddSpawnFlags			(int flags)	{ spawnFlags |= flags;	};
//#endif

private:
	typedef struct oSSpawnNode{
		oCNpc*		npc;
		zVEC3		spawnPos;
		zREAL		timer;
    
        oSSpawnNode():npc(NULL),spawnPos(0,0,0),timer(0){} // [Moos] immer brav alles initialisierten :)
	} oTSpawnNode;

	void					InsertInList			(oCSpawnManager::oTSpawnNode* spawnNode);
	void					RemoveFromList			(oCSpawnManager::oTSpawnNode* spawnNode);
	void					InitCameraPos			();
	
	void					CheckInsertNpc			();
	zBOOL					InsertNpc				(oCNpc* npc, const zVEC3& spawnPos);

	// TMP : It's only for Debugging.... Disable it later !
	void					CheckForInvalidDialogCamPos	(zREAL dist, oCNpc* npc);

	// [BENDLIN] Addon Patch - Totenwanderung Fixes
	zBOOL					UseDeadNpcRoutinePos	(oCNpc* npc);
	// [BENDLIN] Addon Patch - Entfernen der Leichen konfigurierbar
	zBOOL					CanDeadNpcBeRemoved		(oCNpc* npc);

	zCArray<oTSpawnNode*>	spawnList;
	zBOOL					spawningEnabled;
	zVEC3					camPos;
	zREAL					insertTime;

//#if defined(SECUROM) && !defined(COMPILING_SPACER)
	int						spawnFlags;
//#endif

};

#endif
