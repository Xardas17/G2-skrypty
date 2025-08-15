/******************************************************************************** 
 
     $Workfile:: oAIShoot.cpp         $                $Date:: 9.02.01 19:56    $
     $Revision:: 55                   $             $Modtime:: 9.02.01 18:50    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oAIShoot.cpp $
 * 
 * 55    9.02.01 19:56 Moos
 * Accounting-Insrumentierung
 * 
 * 54    7.02.01 14:38 Moos
 * 
 * 53    1.02.01 20:09 Wohlers
 * 
 * 52    25.01.01 17:26 Keskenti
 * 
 * 51    22.01.01 22:38 Wohlers
 * 
 * 50    18.01.01 0:39 Speckels
 * 
 * 49    17.01.01 16:59 Keskenti
 * 
 * 48    16.01.01 18:16 Moos
 * 
 * 47    12.01.01 19:18 Keskenti
 * 
 * 46    11.01.01 16:23 Keskenti
 * 
 * 45    5.01.01 17:45 Keskenti
 * 
 * 44    21.12.00 21:24 Moos
 * 
 * 43    20.12.00 18:23 Moos
 * 
 * 42    20.12.00 17:50 Moos
 * 
 * 41    20.12.00 17:13 Moos
 * 
 * 40    20.12.00 12:34 Keskenti
 * 
 * 39    19.12.00 13:42 Keskenti
 * 
 * 38    19.12.00 13:33 Keskenti
 * 
 * 37    14.12.00 12:36 Keskenti
 * 
 * 36    14.12.00 11:50 Keskenti
 * 
 * 35    11.12.00 19:02 Moos
 * 
 * 34    11.12.00 15:11 Keskenti
 * 
 * 33    8.12.00 11:56 Moos
 * 
 * 32    5.12.00 19:47 Keskenti
 * 
 * 31    1.12.00 11:00 Keskenti
 * 
 * 30    30.11.00 15:34 Keskenti
 * 
 * 29    22.11.00 20:45 Wohlers
 * 
 * 28    21.11.00 14:12 Wohlers
 * 
 * 27    15.11.00 15:01 Keskenti
 * 
 * 26    13.11.00 22:08 Speckels
 * 
 * 25    8/11/00 16:02 Luesebrink
 * 
 * 24    2.11.00 17:55 Keskenti
 * 
 * 23    31.10.00 20:27 Keskenti
 * 
 * 22    27/10/00 13:03 Luesebrink
 * 
 * 21    26.10.00 19:28 Keskenti
 * 
 * 20    26/10/00 18:03 Luesebrink
 * 
 * 19    26.10.00 17:03 Keskenti
 * 
 * 18    19.10.00 19:18 Moos
 * 
 * 17    19/10/00 15:03 Luesebrink
 * 
 * 16    13.10.00 17:57 Keskenti
 * 
 * 15    13.10.00 15:59 Keskenti
 * 
 * 14    5.10.00 22:34 Keskenti
 * 
 * 13    12/09/00 16:49 Luesebrink
 * 
 * 12    7.09.00 21:05 Wohlers
 * 
 * 11    25.08.00 14:21 Wohlers
 * 
 * 10    23.08.00 16:32 Keskenti
 * 
 * 9     21.08.00 14:24 Wohlers
 * 
 * 8     2.08.00 14:25 Wohlers
 * 
 * 7     21.07.00 15:34 Wohlers
 * 
 * 6     19.07.00 12:45 Wohlers
 * 0.88
 * 
 * 5     25.05.00 14:50 Wohlers
 * Levelwechsel / Fernkampf
 * 
 * 4     22.05.00 18:41 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:07 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 10    14.05.00 19:54 Wohlers
 * 0.77d - Fernkampf, GoRoute-MetadatenBug behoben
 * 
 * 9     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 8     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 7     4.02.00 15:38 Wohlers
 * Bugfixes 
 * 
 * 6     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 5     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/


#include "zCore.h"
#include "zPolyStrip.h"

#include "z3d.h"
#include "zPhysics.h"
#include "zParticle.h"
#include "zModel.h"
#include "zAI.h"
#include "zArchiver.h"
#include "zEventMan.h"
#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

#include "oAIShoot.h"
#include "oNPC.h"
#include "oWorld.h"
#include "oMobInter.h"
#include "oAniCtrl.h"
#include "oGame.h"
#include "onpc_damage.h"
#include "onpcmessages.h"
#include "ovisfx.h"

#include <zAccount.h>

//#define NEW_COLL

const zSTRING	TRAIL_VOB_MESH_NAME = "ArrowTrail.3ds";
zREAL			TRAIL_STRIP_SEGMENT_TIME = 100.0f; // twice per second 
enum		{	TRAIL_STRIP_SEGMENTS_MAX = 64 }; 

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

// *******************************************************************************
// SOUND AI - BASE 
// *******************************************************************************

void oCAISound::RemoveSlideSound() {
	if (slideSoundOn) {
		slideSoundOn=FALSE;
		zsound->StopSound (slideSoundHandle);
	};
};

void oCAISound::CheckSlideSound(zCVob* vob) {
	if ((vob->GetPhysicsEnabled()) &&
		(vob->GetRigidBody()->GetMode()==zPHY_RBMODE_SLIDE)) 
	{
		if (!slideSoundOn) {
			int levelMat = 0;
			if (vob->GetGroundPoly())
				levelMat = vob->GetGroundPoly()->GetMaterial()->GetMatGroup();
			slideSoundOn	= TRUE;
			slideSoundHandle= zsndMan->StartSlideSound (vob, levelMat);
		} else
			zsound->UpdateSound3D (slideSoundHandle);
	} else {
		if (slideSoundOn) {
			slideSoundOn=FALSE;
			zsound->StopSound (slideSoundHandle);
		};
	};
};

int  oCAISound :: GetSoundMaterial (zCVob *vob, zCSoundManager::zTSndManMedium &mat_type)
{
	// FIXME : Vituals als Schnittstelle !!!!
	if (!vob) return 99;
	int type = vob -> GetVobType();
	if (type == zVOB_TYPE_ITEM) {
		mat_type = zCSoundManager::zSND_MAN_MEDIUM_ITEM;
		return ((oCItem*)vob)->GetSoundMaterial();
	}
	if (zDYNAMIC_CAST<oCMOB>(vob))	{
		//mat_type = zCSoundManager::zSND_MAN_MEDIUM_OBJECT;
		mat_type = zCSoundManager::zSND_MAN_MEDIUM_ITEM;
		return ((oCMOB* )vob)->GetSoundMaterial();
	}
	if (type == zVOB_TYPE_NSC)	{
		oCNpc *npc = zDYNAMIC_CAST<oCNpc>(vob);
		mat_type = zCSoundManager::zSND_MAN_MEDIUM_ITEM;
		// Mit oder ohne Rüstung
		if (npc && !npc->GetEquippedArmor())	return 0;		// Flesh
		else									return npc->GetEquippedArmor()->GetSoundMaterial();	
	}
	// Undefined Vob
	mat_type = zCSoundManager::zSND_MAN_MEDIUM_ITEM;

	if (vob->GetVisualClass()==zCProgMeshProto::GetStaticClassDef())
	{
		zCProgMeshProto* progMesh = static_cast<zCProgMeshProto*>(vob->GetVisual());
		// der einfachheit halber nehmen wir das erste material was ok ist 
		for (int i=0; i<progMesh->GetNumMaterial(); i++)
		{
			if (!progMesh->GetMaterialByIndex(i)->GetNoCollDet())
			{
				zCMaterial *mat = progMesh->GetMaterialByIndex(i);
				switch (mat->GetMatGroup())
				{
				case zMAT_GROUP_METAL: return SND_MAT_METAL; break;
				case zMAT_GROUP_STONE: return SND_MAT_STONE; break;
				case zMAT_GROUP_WOOD:  return SND_MAT_WOOD;  break;
				case zMAT_GROUP_SNOW:  return SND_MAT_LEATHER; break;
				case zMAT_GROUP_EARTH: return SND_MAT_CLAY;  break;
				case zMAT_GROUP_WATER: return SND_MAT_GLAS;  break;
				default:			   return SND_MAT_STONE; break;
				}
			}
		}
	}
	return 99;
}

void oCAISound :: StartCollisionSound (zCVob* source, const zCCollisionReport& collisionReport)
{
	zCSoundManager::zTSndManMedium source_mat_type; 
	int source_mat = GetSoundMaterial(source,source_mat_type);

	if	(collisionReport.m_poCollObject1->GetCollObjClass()==zCCollObjectLevelPolys::S_GetCollObjClass())
	{
		zCCollObjectLevelPolys	*collObjLevel = static_cast<zCCollObjectLevelPolys*> (collisionReport.m_poCollObject1);
		zERR_ASSERT				(collObjLevel->m_aoPolyList.GetNum()>0);
		int levelMat			= int(collObjLevel->m_aoPolyList[0]->GetMaterial()->GetMatGroup());
		switch (levelMat)
		{
		case zMAT_GROUP_METAL: levelMat = SND_MAT_METAL; break;
		case zMAT_GROUP_STONE: levelMat = SND_MAT_STONE; break;
		case zMAT_GROUP_WOOD:  levelMat = SND_MAT_WOOD;  break;
		case zMAT_GROUP_SNOW:  levelMat = SND_MAT_LEATHER; break;
		case zMAT_GROUP_EARTH: levelMat = SND_MAT_CLAY;  break;
		case zMAT_GROUP_WATER: levelMat = SND_MAT_GLAS;  break;
		default:			   levelMat = SND_MAT_STONE; break;
		}
		zsndMan->StartHitSound	(source, source_mat_type, zCSoundManager::zSND_MAN_MEDIUM_LEVEL, source_mat, levelMat, &collisionReport);
	} else 
	{
		// damit nicht beide Vobs den Coll-Sound ausloesen, macht bei einer Coll. dies nur der mit der kleineren Adresse!
		// AUSNAHME: der andere Vob hat keine AI und kann deshalb auch keinen Sound triggern !
		// [EDENFELD] nun wird immer ein Sound gespielt, aber der Fall das zwei Objekte gleichzeitig
		// einen Sound abspielen ist auch null!
		zCVob *otherVob	= static_cast<zCVob*>(collisionReport.m_poCollObject1->GetClientData());
		//if (/*(source<otherVob) || */(!otherVob->GetAI()))
		{	
			int other_mat = 99;
			zCSoundManager::zTSndManMedium other_mat_type; 
			other_mat = GetSoundMaterial(otherVob, other_mat_type);
			zsndMan->StartHitSound (source, source_mat_type,other_mat_type, source_mat, other_mat, &collisionReport);
		};
	};
}

// *******************************************************************************
// VOBMOVE - AI - BASE
// *******************************************************************************

oCAIVobMove :: oCAIVobMove ()
{
	owner	= NULL;
	vob		= NULL;
}

oCAIVobMove :: ~oCAIVobMove ()
{
	ClearIgnoreCDVob();
	zRELEASE(vob);
	zRELEASE(owner);
}

void oCAIVobMove :: Init (zCVob* inVob, zCVob* shootVob, zVEC3& startPos, zREAL angle, zREAL force, zMATRIX4* matrix)
{
	force = 1.0f; // TEMP !!!

	// old ones clearen....
	ClearIgnoreCDVob();
	zRELEASE(owner); zRELEASE(vob);
	
	// new ones init
	owner	= shootVob;		if (owner)	zADDREF_ACCT(owner);
	vob		= inVob;		if (vob)	zADDREF_ACCT(vob);

	// 0) [EDENFELD] 1.27 etwaige NPC parent vobs sind schlecht! wird nun hier korrigiert
	// sollte alle Item Drop Hänger beheben
	// die eigentliche Ursache war mal wieder superkrass: bei einem DropFromSlot() eines vobs
	// den man fallenlassen möchte wird nicht der bezug zum parentvob in der hierachie gelöscht.
	// bewegt sich nun das model nun in einer ganz bestimmten Weise (wzB beim Ohnmächtig werden)
	// meldet das Physiksystem ein Stillstand des Vobs da sich Modelbewegung und Fallbewegung gegenseitig
	// aufheben und deaktiviert die Physik. Weiter unten in oCAIVobMove::DoAI() wird dann der inVob
	// auf SetSleeping(TRUE) gesetzt. Noch Fragen ?
	// damit sich model und fallbewegung nicht gegenseitig aufheben muss hier auf jeden fall 
	// der bezug zum parent aufgehoben werden
	if (inVob->HasParentVob() && inVob->GetHomeWorld())
	{
		oCNpc *parentNpc = zDYNAMIC_CAST<oCNpc>(inVob->globalVobTreeNode->GetParent()->GetData());
		if (parentNpc)
		{
			// argh, der vob hängt an einem nsc. hier wird davon ausgegangen das nichts an einem
			// nsc hängen darf, daher enfernen wir den vob vom parent 
			// TODO: feststellen ob folgender code auch childs vom invob entfernt (fackeln!)
			inVob->globalVobTreeNode->MoveSubtreeTo(0);
		};
	};

	// 1) alte AI abkoppeln sofern vorhanden
	if (inVob->GetAI() && (inVob->GetAI()!=this)) zRELEASE_ACCT_NONULL(inVob->GetAI());
	// 2) Neue AI ankoppeln
	inVob->SetAI(this);
	
	// 3) Kollision mit ShootVob ignorieren
	AddIgnoreCDVob(shootVob);
	
	// 4) Vob in Welt einfügen, falls nötig
	if (!inVob->GetHomeWorld()) {
		if (shootVob && shootVob->GetHomeWorld()) {
			shootVob->GetHomeWorld()->AddVob(inVob);
		} else {
			zerr.Warning("U:VOBAI:No homeworld found.");
			return;
		}
	}
	
	// 5) Auf Kollision pruefen, falls möglich
	oCVob* ovob = zDYNAMIC_CAST<oCVob>(inVob);
	if (ovob && !ovob->SearchFreePosition(startPos,shootVob)) {
		//!ovob->HasEnoughSpace(startPos)) {
		zerr.Warning("U:VOBAI:Not enough space");
	}
	
	// 6) Ausgangsposition herstellen
	inVob->SetCollDet		    (FALSE);
	inVob->ResetRotationsWorld	();           // [Moos] 20.12.00 Anpassung an Vob-Änderung
	inVob->SetPositionWorld	    (startPos);
	inVob->SetCollDet		    (TRUE);
	inVob->SetSleeping		    (FALSE);
	
	// 7) Geschwindigkeit einsetzen
	if ((force>0) && matrix) {
		zMATRIX4 trafo		= *matrix * Alg_Rotation3DN ( zVEC3(1,0,0), -angle);
		zVEC3	 direction	= trafo.GetAtVector();
		
		inVob->SetPhysicsEnabled				(TRUE);
		inVob->GetRigidBody()->SetGravityEnabled(TRUE);
		inVob->GetRigidBody()->SetVelocity		(direction * force);
	} else {
		// Position beibehalten
		inVob->SetPhysicsEnabled				(FALSE);
	};		
}

void oCAIVobMove::DoAI (zCVob* inVob, BOOL &vobDeleted) 
{
	// Die Touch Liste durcheiern
	zCVob* ignoreVob = NULL;
	zCList<zCVob>* ignoreVobNode = ignoreVobList.GetNextInList();
	while (ignoreVobNode) {
		ignoreVob		= ignoreVobNode->GetData();
		ignoreVobNode	= ignoreVobNode->GetNextInList();
		if ((owner!=ignoreVob) && !inVob->IsTouching(ignoreVob)) {
			ignoreVobList.Remove(ignoreVob);
			zRELEASE_ACCT_NONULL(ignoreVob);
			zerr.Message("U:VOBMOVE:No longer touching Vob:"+ignoreVob->GetVobName());
		}
	}
	
	if (!inVob->GetPhysicsEnabled()) {
		inVob->SetSleeping	(TRUE);
	}
};

void oCAIVobMove::ReportCollisionToAI	(const zCCollisionReport& collisionReport)
{
	StartCollisionSound(vob,collisionReport);

	// *****************************
	// Logischer Sound
	// *****************************
	if (vob) oCNpc::AssessQuietSound_S(vob,vob->GetPositionWorld());
}

void oCAIVobMove::Archive(zCArchiver& arc)
{
	oCAISound::Archive(arc);

	if	(!arc.InSaveGame())	return;
	
	zCVob* writeVob		= NULL;
	zCVob* writeOwner	= NULL;
	
	if (oCNpc::dontArchiveThisNpc!=vob)		writeVob = vob;
	arc.WriteObject("vob"	,writeVob);
	
	if (oCNpc::dontArchiveThisNpc!=owner)	writeOwner = owner;	
	arc.WriteObject("owner"	,writeOwner); 
}

void oCAIVobMove::Unarchive(zCArchiver& arc)
{
	oCAISound::Unarchive(arc);

	if (!arc.InSaveGame())	return;

	ClearIgnoreCDVob();
	zRELEASE(vob);
	zRELEASE(owner);
	
	vob    = (zCVob *) arc.ReadObject2("vob"		,vob);
	owner  = (zCVob *) arc.ReadObject2("owner"	,owner);
	
	AddIgnoreCDVob(owner);

	// [Wohlers] - Auskommentiert - scheint nicht mehr noetig.. -> verschoben nach PutInSlot...	
	// [Moos] Hack; setzt das Torch-Overlay
    /*oCNpc   *npc = dynamic_cast<oCNpc *>(owner);
    if (npc && vob && vob->GetObjectName() == "ITLSTORCHBURNING" && npc->GetSlotVob(NPC_NODE_LEFTHAND) == vob)
        npc->SetTorchAni(true);
    */
}

void oCAIVobMove :: AddIgnoreCDVob	(zCVob *inVob)
{
	if (inVob) {
		ignoreVobList.Insert(inVob);
		zADDREF_ACCT(inVob);
	}
};

void oCAIVobMove :: ClearIgnoreCDVob()
{
	zCList<zCVob>*	ignoreNode = ignoreVobList.GetNextInList();
	while (ignoreNode) {
		zRELEASE_ACCT_NONULL(ignoreNode ->GetData());
		ignoreNode = ignoreNode->GetNextInList();
	};
	ignoreVobList.DeleteList();	
};

// *******************************************************************************
// TORCH - AI
// *******************************************************************************

oCAIVobMoveTorch :: oCAIVobMoveTorch ()
{
	timer = 0.0f;
}

oCAIVobMoveTorch :: ~oCAIVobMoveTorch ()
{
}

void oCAIVobMoveTorch::Init	(zCVob* inVob, zCVob* shootVob, zVEC3& startPos, zREAL angle, zREAL force, zMATRIX4* matrix)
{
	timer	= 30 * 1000; // 30 Sekunden
	oCAIVobMove :: Init(inVob,shootVob,startPos,angle,force,matrix);
}

void oCAIVobMoveTorch::DoAI (zCVob* inVob, BOOL &vobDeleted) 
{
	zBOOL deleted = CheckWater();
	oCAIVobMove :: DoAI (inVob, vobDeleted);
	if (!vobDeleted) vobDeleted = deleted;
	if (vobDeleted) {
		// delete(vob);
	}
}

zBOOL oCAIVobMoveTorch :: CheckWater()
{
	// Im Wasser ?
	zVEC3 centerPos = vob->GetPositionWorld();
	centerPos[VY]	= vob->GetBBox3DWorld().maxs[VY];
	zVEC3 dir_up	= zVEC3(0,1000,0);
	zCWorld* world	= vob->GetHomeWorld();

	if (world) {
		world->TraceRayNearestHit (centerPos, dir_up, vob, zTRACERAY_STAT_POLY);
		if (world->traceRayReport.foundHit) {
			// Wasser-Decke ?
			zCPolygon* ceilingPoly = world->traceRayReport.foundPoly;
			if (ceilingPoly)
			if (ceilingPoly->GetMaterial())
			if (ceilingPoly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER) {
				// ja, Decke ist ein Wasser-Poly
				BurnedOut();
				return TRUE;
			};
		};
	}

	// Brenndauer Timer
/*	timer -= ztimer.GetFrameTimeF();
	if (timer<=0) {
		BurnedOut();
		return TRUE;
	}
*/
	return FALSE;
}

void oCAIVobMoveTorch :: BurnedOut()
{	
	timer = 0;

	// Instanz auswechseln
	zCWorld*	world	= vob->GetHomeWorld();
	zMATRIX4	trafo	= vob->trafoObjToWorld;
	zVEC3		oldVel	= vob->GetVelocity();

	// Das Ding noch in der Hand ?
	oCNpc* npc = zDYNAMIC_CAST<oCNpc>(owner);
	if (npc && npc->GetHomeWorld()) 
	{
		npc->GetHomeWorld()->RemoveVobSubtree(vob);
		npc->RemoveFromSlot(npc->GetInvSlot(vob),FALSE);
	}

	oCItem* torch = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCHBURNED");
	
	torch	-> SetCollDet			(FALSE);
	torch	-> SetTrafoObjToWorld	(trafo);
	world	-> AddVob				(torch);
	torch	-> SetPhysicsEnabled	(TRUE);
	torch	-> SetSleeping			(FALSE);
	torch	-> GetRigidBody() -> SetVelocity (oldVel);	
	torch	-> SetCollDet			(TRUE);
}

// *******************************************************************************
// Pfeil AI
// *******************************************************************************

oCAIArrowBase :: oCAIArrowBase()
{
	collisionOccured	= FALSE;
	timeLeft			= -1.0f;
	vob					= NULL;
	startDustFX			= FALSE;

	//
	//	CODECHANGE [ROMAN]
	//
	this->trailVob		= NULL ;
	this->trailStrip	= NULL ;
	this->trailActive	= FALSE;
	this->hasHit		= TRUE;
	//
	//	CODECHANGE [ROMAN] END
	//
}

oCAIArrowBase :: ~oCAIArrowBase()
{
	zRELEASE(vob);

	//
	//	REMOVE TRAIL VOB AND STRIP
	//
	if ( this->trailVob && trailVob->GetHomeWorld())
	{
		trailVob->GetHomeWorld()->RemoveVob( this->trailVob );		
	}
	zRELEASE( this->trailVob );

	if ( this->trailStrip )
	{
		zRELEASE( this->trailStrip );
	}
}

void oCAIArrowBase :: AddIgnoreCDVob	(zCVob *inVob)
{
	if (inVob) {
		ignoreVobList.Insert(inVob);
		zADDREF_ACCT(inVob);
	}
};

void oCAIArrowBase :: ClearIgnoreCDVob()
{
	zCList<zCVob>*	ignoreNode = ignoreVobList.GetNextInList();
	while (ignoreNode) {
		zRELEASE_ACCT_NONULL(ignoreNode->GetData());
		ignoreNode = ignoreNode->GetNextInList();
	};
	ignoreVobList.DeleteList();	
};

void oCAIArrowBase :: CreateTrail( zCVob* inVob )
{
	//
	//	ARROW TRAIL (POLY STRIP)
	//
	this->trailStrip = zNEW( zCPolyStrip );

	trailStrip->			SetCamAlign				( /*zCPolyStrip::zCAM_ALIGN_POLY*/ zCPolyStrip::zCAM_ALIGN_STRIP );
	trailStrip->			SetAlphaFadeSpeed		( 0.30f );
	trailStrip->material->	SetAlphaBlendFunc		( zRND_ALPHA_FUNC_BLEND );
	trailStrip->material->	SetTexture				( zSTRING( "ARROWSTRIP.TGA" ) );
	trailStrip->material->	texAniCtrl.SetAniFPS	( 10.0f );
	trailStrip->material->	texAniCtrl.SetOneShotAni( TRUE );
	trailStrip->material->	SetAlpha				( 255 );
	trailStrip->			AllocateResources		( TRAIL_STRIP_SEGMENTS_MAX );
	trailStrip->SetEveryFrameUpdate(TRUE);

	//
	//	PRESET TRAIL SEGMENT TIMER
	//
	trailTime = TRAIL_STRIP_SEGMENT_TIME;

	//
	//	ARROW TRAIL (VOB)
	//
	this->trailVob = zNEW( zCVob );
	this->trailVob->SetDontWriteIntoArchive(TRUE);

	this->trailVob->SetVisual( this->trailStrip /*TRAIL_VOB_MESH_NAME*/ );

	zCProgMeshProto* pMesh = zDYNAMIC_CAST< zCProgMeshProto > (this->trailVob->GetVisual());
	if ( pMesh )
	{
		zCMaterial* pMaterial = pMesh->GetMaterialByIndex( 0 );
		pMaterial->SetAlphaBlendFunc( zRND_ALPHA_FUNC_ADD );
		pMaterial->SetAlpha( 0xff );
	}

	//
	//	ADD TRAIL VOB TO ARROW VOB
	//
	zCWorld* pWorld		 = inVob->GetHomeWorld();
	zVEC3	 vecPosArrow = inVob->GetPositionWorld();

	if ( pWorld )
	{
		zTBBox3D boxArrow = inVob->GetBBox3DLocal();

		this->trailVob->BeginMovement		();
		this->trailVob->SetTrafoObjToWorld	( inVob->trafoObjToWorld );
		this->trailVob->SetPositionWorld	( vecPosArrow );
		this->trailVob->MoveLocal			( 0, 0, boxArrow.maxs[VZ] );
		this->trailVob->EndMovement			();

		pWorld->AddVobAsChild( this->trailVob, inVob );
	}
}

void oCAIArrowBase::DoAI (zCVob* inVob, zBOOL& vobDeleted) { 
	// Arrow-Verhalten:
	// - Coll. mit Holz		: steckenbleiben, wegfaden?, nach bestimmter Zeit & nicht in Frustum removen ?
	// - Coll. mit sonst	: abprallen und langsam wegfaden
	// ? Coll. mit Vob/Model: sofort verschwinden

	//
	//	ADD TRAIL VOB SEGMENT
	//
	if ( this->trailStrip )
	{
		this->trailTime -= ztimer.GetFrameTimeF();

		if ( this->trailTime <= 0.0f )
		{
			//
			//	RESET FRAME TIMER
			//
			this->trailTime = TRAIL_STRIP_SEGMENT_TIME;

			//
			//	ADD POLY STRIP 
			//
			zVEC3 vecCenter = inVob->GetPositionWorld();
			this->trailStrip->AddSegment( vecCenter );
		}
	}

	// - Partikel-Effekte:
	//		- collision (abh. von Material/Speed ?)

	vobDeleted = FALSE;

	if (collisionOccured) 
	{
		collisionOccured		= FALSE;
		oCItem *weapon = zDYNAMIC_CAST<oCItem>(inVob);
		if (weapon && weapon->GetEffect()) weapon->GetEffect()->SetLevel(3,TRUE);

		// Partikel-Effekt
		if (startDustFX)
		{
			inVob->EndMovement(); 
			zCParticleFX	*partFX	= zNEW( zCParticleFX );
			zCVob			*vobFX	= zNEW( zCVob );
			vobFX	->SetCollDet				(FALSE);
			vobFX	->SetPositionWorld			(inVob->GetPositionWorld());  
			vobFX	->SetVisual					(partFX);
			vobFX	->SetDontWriteIntoArchive	(TRUE);
			partFX	->SetEmitter				("PFX_DUST", TRUE);		// TRUE = copy des Emitters erzeugen, damit's verändert werden kann !
			partFX	->GetEmitter()->visSizeStart *= 0.5F;
			partFX	->CreateParticles			();
			inVob	->GetHomeWorld()->AddVob	(vobFX);

			zRELEASE(partFX);
			zRELEASE(vobFX);
		};
	};

	if (timeLeft!=-1) 
	{
		zREAL vel	= 1.0F / (1000.0F*20.0F);
		timeLeft	-= vel * ztimer.GetFrameTimeF();
		if (timeLeft<=0) vobDeleted = TRUE; 
		zREAL a = float((sin (timeLeft*M_PI - M_PI/2)+1)/2);
		vob->SetVisualAlpha			(a);
		vob->SetVisualAlphaEnabled	(TRUE);
	};

	if (vobDeleted)
	{
		if (trailVob && trailVob->GetHomeWorld())
		{
			trailVob->GetHomeWorld()->RemoveVob( this->trailVob );		
		}
		zRELEASE( this->trailVob );

		if ( this->trailStrip )
		{
			zRELEASE( this->trailStrip );
		}

		oCItem* item = zDYNAMIC_CAST<oCItem>(inVob);
		if (item && item->GetEffect()) item->RemoveEffect();
	};
};

/* ----------------------------------------------------------------------
	
    oCAIArrowBase::ReportCollisionToAI()

	 19.12.2000	[Moos]	
                auf neue Kollision umgestellt


   ---------------------------------------------------------------------- */
void oCAIArrowBase::ReportCollisionToAI (const zCCollisionReport& collisionReport) 
{
	//if(collisionReport.m_poCollObject1->GetCollObjClass()==zCCollObjectBoxPassThrough::S_GetCollObjClass()) return;

	startDustFX			= TRUE;

	if (!vob) return;

	vob->SetSleeping(FALSE);

	// pfeil fading beginnen
	if (timeLeft==-1)	timeLeft = 1;
	
	if (!collisionReport.m_poCollObject1) return;

	if	(collisionReport.m_poCollObject1->GetCollObjClass()==zCCollObjectLevelPolys::S_GetCollObjClass())
	{
		startDustFX = TRUE;
		zCCollObjectLevelPolys	*collObjLevel = static_cast<zCCollObjectLevelPolys*> (collisionReport.m_poCollObject1);
		zERR_ASSERT				(collObjLevel->m_aoPolyList.GetNum()>0);

		if (collisionOccured == FALSE)
		for (int i=0; i<(collObjLevel->m_aoPolyList.GetNum()); i++) 
		{
			const zTMat_Group matGroup = collObjLevel->m_aoPolyList[i]->GetMaterial()->GetMatGroup();
			if (matGroup==zMAT_GROUP_WOOD) 
			{
				vob->SetCollDet			(FALSE);
				vob->SetPhysicsEnabled	(FALSE);
				vob->Move				(-vob->GetRightVectorWorld()*15);
				break;
			};
		}
		vob->GetRigidBody()->SetGravityEnabled	(TRUE);			// cm/sec
		vob->GetRigidBody()->SetVelocity(vob->GetRigidBody()->GetVelocity()*0.8f);
	} 
	else 
	{
	    zCCollObjectCharacter *character = (zCCollObjectCharacter *)(collisionReport.m_poCollObject1);
		zCVob* targetVob = character->GetVob();
    	oCNpc* targetNpc = zDYNAMIC_CAST<oCNpc>(targetVob);
		if (targetNpc)
		{
			//vob->SetCollDetDyn		(FALSE);
			oCItem *armor = targetNpc->GetEquippedArmor();
			zBOOL abprallen = (armor && armor->GetSoundMaterial()==SND_MAT_METAL && !hasHit);
			if (!abprallen)
			{
				// character getroffen, pfeil sofort ausblenden
				vob->SetPhysicsEnabled(FALSE);
				if (timeLeft>0.1f) timeLeft = 0.05f;
			};
		}
		else if (targetVob)
		{
			zCProgMeshProto *proto = zDYNAMIC_CAST<zCProgMeshProto>(targetVob->GetVisual());
			if (proto)
			{
				if (collisionOccured == FALSE)
				for (int i=0; i<proto->GetNumMaterial(); i++) 
				{
					const zTMat_Group matGroup = proto->GetMaterialByIndex(i)->GetMatGroup();
					if (matGroup==zMAT_GROUP_WOOD) 
					{
						vob->SetCollDet			(FALSE);
						vob->SetPhysicsEnabled	(FALSE);
						vob->Move				(-vob->GetRightVectorWorld()*15);
						break;
					};
				};
			};
		};

		vob->GetRigidBody()->SetGravityEnabled	(TRUE);			// cm/sec		
	};

	collisionOccured	= TRUE; 
};

// ******************************************************
// Archive...
// ******************************************************

void oCAIArrowBase :: Archive (zCArchiver& arc)
{
	oCAISound :: Archive(arc);
	if (arc.InProperties()) return;
	if (!arc.InSaveGame())	return;

	zCVob* writeVob = NULL;
	if (oCNpc::dontArchiveThisNpc!=vob) writeVob = vob;
	arc.WriteObject	("vob"			,writeVob);
	
	arc.WriteBool	("collision"	,collisionOccured);
	arc.WriteFloat	("timeLeft"		,timeLeft);
	arc.WriteBool	("startDustFX"	,startDustFX);	
}

void oCAIArrowBase :: Unarchive	(zCArchiver& arc)
{	
	oCAISound :: Unarchive(arc);

	if (arc.InProperties()) return;
	if (!arc.InSaveGame())	return;

	zRELEASE(vob);
	// Others
	vob = (zCVob*) arc.ReadObject1	("vob");		// AddRef +1 !

	arc.ReadBool	("collision"	,collisionOccured);
	arc.ReadFloat	("timeLeft"		,timeLeft);
	arc.ReadBool	("startDustFX"	,startDustFX);

	// Zur Sicherheit trailVob entfernen (auf NULL setzen)
	zRELEASE(trailVob);
}

// *******************************************************************************
// Pfeil AI - Ulf
// *******************************************************************************

const int ARROW_VELOCITY = 2000.0f; // cm/s
// const int ARROW_VELOCITY = 100.0f; 

oCAIArrow::oCAIArrow()
{
	removeVob	= FALSE;
	arrow		= NULL;
	owner		= NULL;
	targetNPC	= NULL ;
}

oCAIArrow::~oCAIArrow()
{
	ClearUsedVobs();
}

void oCAIArrow :: SetTarget(zCVob *pTargetVob)
{	
	zRELEASE(targetNPC);
	targetNPC = pTargetVob; 
	if (targetNPC) zADDREF_ACCT(targetNPC);
}

void oCAIArrow :: ClearUsedVobs()
{
	ClearIgnoreCDVob();

	zRELEASE(arrow);
	zRELEASE(owner);
	zRELEASE(targetNPC);	
};

void oCAIArrow::SetupAIVob (zCVob *inVob, zCVob *shootVob, zCVob *target) 
{
	ClearUsedVobs();
	
	//
	//	SPEICHERE DAS ZIEL
	//
	SetTarget(target);

	//
	//	SETZTE PFEIL IN DIE WELT
	//

	collisionOccured			= FALSE;
	
	vob							= inVob;					
	if (vob) zADDREF_ACCT(vob);
	
	owner						= zDYNAMIC_CAST<oCNpc>		(shootVob);
	if (owner) zADDREF_ACCT(owner);
	
	arrow						= zDYNAMIC_CAST<oCItem>		(inVob);
	if (arrow) zADDREF_ACCT(arrow);

	zMATRIX4 trafoObjToWorld	= shootVob -> GetTrafoModelNodeToWorld("ZS_RIGHTHAND");

	oCItem *weapon = zDYNAMIC_CAST<oCItem>(inVob);
	if (weapon && weapon->GetEffect()) weapon->GetEffect()->SetLevel(2,TRUE);

	AddIgnoreCDVob							(shootVob); 
	inVob->SetSleeping						(FALSE);
	inVob->SetPhysicsEnabled				(TRUE);
	inVob->SetTrafoObjToWorld				(trafoObjToWorld);
	trafoObjToWorld.PostRotateY				(-90); 
	zVEC3 force	=							trafoObjToWorld.GetAtVector();
	inVob->GetRigidBody()->SetVelocity		(ARROW_VELOCITY*force);		// cm/sec
	inVob->GetRigidBody()->SetGravityEnabled(FALSE);		
	inVob->SetCollDet						(TRUE);

	// Korrigiere At-Vector des Pfeils wenn Target angegeben wird
	if (target) {
		zVEC3 at = (target->GetPositionWorld()) - (inVob->GetPositionWorld());	//[Keskenti] 25.01.01 Pfeil statt NPC als Ursprung
		at.Normalize		        ();
		inVob->SetHeadingAtWorld	(at);      // [Moos] 20.12.00 Anpassung an Vob-Änderung
		zMATRIX4 trafoObjToWorld = inVob->trafoObjToWorld;
		trafoObjToWorld.PostRotateY	(90);
		inVob->SetTrafoObjToWorld	(trafoObjToWorld);
		inVob->GetRigidBody()->SetVelocity(ARROW_VELOCITY*at);		// cm/sec
	} 

	//inVob -> SetCollType(zVOB_COLL_TYPE_SMALL_OBJECT);
    inVob -> SetCollisionClass	(zCCollObjectProjectile::S_GetCollObjClass());               // [Moos] 20.12.00 Anpassung an Vob-Änderung
	arrow -> SetFlag			(ITM_FLAG_NFOCUS);

	//
	//	HAENG EINEN SCHICKEN ARROWTRAIL DRAN
	//
	oCAIArrowBase::CreateTrail( inVob );
};

void oCAIArrow::DoAI(zCVob *inVob, zBOOL &del)
{
	oCAIArrowBase::DoAI(inVob,del);
	/*if (removeVob) {
		del = TRUE;
		inVob -> SetAI(NULL);
	};*/
	if (del) 
	{	
		removeVob = TRUE;
		inVob -> SetAI(NULL);
	};
}

zBOOL oCAIArrow::CanThisCollideWith	(zCVob* vob)	
{ 
	//
	//	SPIELER ODER KEIN NPC ALS ZIEL -> KOLLIDIERT MIT ALLEM AUSSER DEN ZU IGNORIERENDEN VOBS
	//
	if (	(  this->owner->IsAPlayer() )
		||	( !this->targetNPC			) )
		return !ignoreVobList.InList(vob); 

	
	//
	//	NICHT SPIELER -> KANN NUR MIT FESTGELEGTEM NPC KOLLIDIEREN
	//
	oCNpc* pTargetNpc = zDYNAMIC_CAST< oCNpc > (vob);

    if		(      pTargetNpc					)	//	Ein Npc wurde getroffen
	{
		if	(	( pTargetNpc == this->targetNPC )	//	Ziel ist das gewaelte Ziel
			||	( pTargetNpc->IsMonster() )		)	//	Ziel ist ein Monster
    			return TRUE	;
		else	return FALSE;						
	}
	else		return TRUE	;						// Kollision fuer Waende etc.
}

/* --------------------------------------------------------------------------
   void ReportCollisionToAI 

   13.11.2000	[Speckels]	OnDamage auch fuer tote Objekte
   21.12.2000   [Moos]      Anpassung an neue Kollisionsklamotten

   --------------------------------------------------------------------------*/
void oCAIArrow::ReportCollisionToAI (const zCCollisionReport& collisionReport)
{

	//if	(collisionReport.m_poCollObject1->GetCollObjClass()==zCCollObjectBoxPassThrough::S_GetCollObjClass()) return;

	// Testen: pfeil bleibt nicht mehr in Holz stecken!!!
	collisionOccured	= FALSE; 
    //	tryAgain			= FALSE;
	zCVob *otherVob		= NULL;

    if (collisionReport.m_poCollObject0->GetCollObjClass() != zCCollObjectProjectile::S_GetCollObjClass())
        return; // kein richtiger Pfeil-Report. Verschwinde hier.

	
	StartCollisionSound(arrow,collisionReport);
																											// [Roman] Manuel: Was getroffen werden kann wird in CanThisCollideWith() festgelegt
	{
	    zCCollObjectCharacter *character = dynamic_cast<zCCollObjectCharacter*>(collisionReport.m_poCollObject1);
		if (character) 	otherVob = character->GetVob();

		AddIgnoreCDVob (otherVob);		
		hasHit = TRUE;

		if (arrow && otherVob)
		{
			oCNpc* target	= zDYNAMIC_CAST<oCNpc>(otherVob);
			oCNpc* offender	= zDYNAMIC_CAST<oCNpc>(owner);			
			if (target) 
			//
			// NSC wurde getroffen
			//
			{
				// Movement aus
				// arrow -> EndMovement(); [Moos] Wir sind schon im EndMovement-Block
				// NSC wurde getroffen -> Hit him				
				if( offender == target ) return;

				zVEC3 distV = target->GetPositionWorld() - offender->GetPositionWorld();
				zREAL distL = distV.Length();
				//zREAL chance = (100 - 3.33f * (distL*0.01f)) + offender->GetAttribute(NPC_ATR_DEXTERITY) + offender->GetAttribute(NPC_ATR_DEXTERITY);

				

				// [EDENFELD] 1.09: Treffer Chance des Pfeils nicht mehr mit DEX verknüpft, sondern mit der 
				// echten Hitchance des jeweiligen Weapon Modes
				zERR_ASSERT(offender->GetWeaponMode()==NPC_WEAPON_BOW || offender->GetWeaponMode()==NPC_WEAPON_CBOW);
				int hitChanceIndex	  =  (offender->GetWeaponMode()==NPC_WEAPON_BOW) ? NPC_HITCHANCE_BOW : NPC_HITCHANCE_CROSSBOW;
				int hitChance		  =  offender->GetHitChance(hitChanceIndex);
				static float MIN_DIST = 1000;			// 10m
				static float MAX_DIST = 10000;			// 100m
				static zBOOL shootDistancesInitialized = FALSE;

				if (!shootDistancesInitialized)
				{
					shootDistancesInitialized = TRUE;
					zCPar_Symbol *sym = parser.GetSymbol("RANGED_CHANCE_MINDIST");
					if (sym) sym->GetValue(MIN_DIST);
								  sym = parser.GetSymbol("RANGED_CHANCE_MAXDIST");
					if (sym) sym->GetValue(MAX_DIST);
				}

				if (distL<=MIN_DIST)
				{
					float distScale = distL/MIN_DIST;
					hitChance = zLerp( distScale, 100.0f, float(hitChance) );
				}
				else 
				{
					float distScale = distL/MAX_DIST;
					hitChance = zLerp( distScale, float(hitChance), 0.0f);
				}

				zERR_MESSAGE(9,0,"C: Arrow could hit " + target->GetObjectName() + " calculated a final damagechance of " + zSTRING(hitChance) + " percent");

				if( zRand(100) < hitChance )
				{

					oCNpc::oSDamageDescriptor	descDamage	;
					zDWORD				dwFlags		= 0;

					//
					//	FILL DESCRIPTOR
					//
					descDamage.pVobAttacker			= offender											;
					descDamage.pVobHit				= arrow												;
					descDamage.fDamageTotal			= arrow->GetFullDamage()							;
					descDamage.vecLocationHit		= collisionReport.m_oContactPoint					;
					descDamage.vecDirectionFly		= collisionReport.m_oContactPoint					;

					descDamage.pNpcAttacker			= offender											;
					descDamage.pItemWeapon 			= arrow												;
					descDamage.SetFXHit              (FALSE)											;

					descDamage.nSpellID				= -1;
					descDamage.nSpellLevel			= -1;

					descDamage.fDamageMultiplier	= 1.0f;

					//	---	INIT MODES
					descDamage.enuModeWeapon	 = oETypeWeapon_Range;
					descDamage.enuModeDamage	 = oEDamageType_Point;

					//
					//	EVALUATE FLAGS
					//
																								dwFlags						|=	oCNpc::oEDamageDescFlag_DamageType		;
					if ( descDamage.pVobAttacker	)											dwFlags						|=	oCNpc::oEDamageDescFlag_Attacker		;
					if ( descDamage.pNpcAttacker	)											dwFlags						|=	oCNpc::oEDamageDescFlag_Npc			;
					if ( descDamage.pVobHit			)											dwFlags						|=	oCNpc::oEDamageDescFlag_Inflictor		;
					if ( descDamage.pItemWeapon		)											dwFlags						|=	oCNpc::oEDamageDescFlag_Weapon			;

					oCMsgDamage* pMsgDamage = zNEW(oCMsgDamage(oCMsgDamage::EV_DAMAGE_ONCE,descDamage));

					target->GetEM()->OnMessage(pMsgDamage , NULL);
				//	zCView::StdPrintwin(zSTRING("Treffer!")+"\n");
				}
				else hasHit = FALSE;
				// *****************************
				// Logischer Sound 
				// *****************************   "OTHER"
				if (vob && hasHit) oCNpc::AssessFightSound_S(owner,vob->GetPositionWorld(),target);
			}
			else
			//
			// Ein toter Gegenstand wurde getroffen [SPECKELS]
			//
			{
				// Movement aus
				// arrow -> EndMovement(); [Moos] Wir sind schon im EndMovement-Block
				if( offender == otherVob ) return;
				int				damage		= arrow->GetFullDamage();				
				oTDamageMode	damageTypes = arrow->GetDamageTypes();
				otherVob->GetEM()->OnDamage( arrow, offender, damage, damageTypes, arrow->GetPositionWorld() );
			//	zCView::StdPrintwin("Treffer to "+otherVob->GetClassDef()->GetClassName_()+"\n");
			};
		}
		if (arrow) AddIgnoreCDVob(arrow);
		removeVob = TRUE;
	}	
	oCAIArrowBase::ReportCollisionToAI (collisionReport);

};

// ******************************************************
// Archive...
// ******************************************************

void oCAIArrow :: Archive (zCArchiver& arc)
{
	oCAIArrowBase :: Archive(arc);
	if (arc.InProperties()) return;
	if (!arc.InSaveGame())	return;

	// Others
	arc.WriteObject	("arrow"		,arrow);
	
	// Die Mistbrake von Spieler braucht Sonderbehandlung....
	oCNpc* useThisOwner = NULL;
	if (oCNpc::dontArchiveThisNpc!=owner) useThisOwner = owner;
		
	arc.WriteObject	("ownerNpc", useThisOwner);
}

void oCAIArrow :: Unarchive	(zCArchiver& arc)
{
	oCAIArrowBase :: Unarchive(arc);
	if (arc.InProperties()) return;
	if (!arc.InSaveGame())	return;

	ClearUsedVobs();

	// Others
	arrow	= (oCItem*) arc.ReadObject1	("arrow");
	owner	= (oCNpc*)	arc.ReadObject1	("ownerNpc");
}

// ***********************************************************************************
// Drop
// ***********************************************************************************

oCAIDrop :: oCAIDrop()
{
	vob					= NULL;
	owner				= NULL;
	collisionOccured	= FALSE;
	timer				= 0.0f;
	count				= 0.0f;

}

oCAIDrop :: ~oCAIDrop()
{
	ClearIgnoreCDVob();
	zRELEASE		(vob);
	zRELEASE		(owner);
}

void oCAIDrop :: AddIgnoreCDVob	(zCVob *inVob)
{
	if (inVob) {
		ignoreVobList.Insert(inVob);
		zADDREF_ACCT(inVob);
	}
};

void oCAIDrop :: ClearIgnoreCDVob()
{
	zCList<zCVob>*	ignoreNode = ignoreVobList.GetNextInList();
	while (ignoreNode) {
		zRELEASE_ACCT_NONULL(ignoreNode->GetData());
		ignoreNode = ignoreNode->GetNextInList();
	};
	ignoreVobList.DeleteList();	
};

void oCAIDrop::SetupAIVob (zCVob *inVob, zCVob *shootVob) 
{
	// old ones clearen....
	ClearIgnoreCDVob();
	zRELEASE(owner); zRELEASE(vob);

	// Init new ones
	vob					= inVob;		if (vob)	zADDREF_ACCT(vob);
	owner				= shootVob;		if (owner)	zADDREF_ACCT(owner);

	collisionOccured	= FALSE;
	count				= 0;
	
	zMATRIX4	trafo	= shootVob	-> GetTrafoModelNodeToWorld("ZS_RIGHTHAND");
	zVEC3		pos		= trafo		.  GetTranslation();
	zVEC3		origin	= pos;

	inVob -> SetCollDet	(FALSE);
	if (!inVob->RegisteredInWorld()) ogame->GetGameWorld()->EnableVob (inVob);  // [Moos] 11.12.  dynamic_cast<oCWorld*>(shootVob->GetHomeWorld()), womit früher die Welt geholt wurde, ist manchmal NULL.
	inVob -> ResetRotationsWorld();                                             // [Moos] 20.12.00 Anpassung an Vob-Änderung
	
	SetStartPosition(pos);

	inVob -> GetRigidBody() -> SetVelocity			(50*shootVob->GetAtVectorWorld());	// cm/sec
	inVob -> GetRigidBody() -> SetGravityEnabled	(TRUE);		
	inVob -> SetSleeping		(FALSE);
	inVob -> SetPhysicsEnabled	(TRUE);
	
	AddIgnoreCDVob	(shootVob); 
	timer = 0;
	
	if (inVob->GetVobType()==zVOB_TYPE_ITEM) {
		((oCItem*)inVob)->ClearFlag(ITM_FLAG_NFOCUS);
	};

	inVob -> SetCollDet	(FALSE);  // [Moos] aktivieren wir die Kollision lieber gleich wieder...
};

void oCAIDrop::DoAI (zCVob* inVob, BOOL &vobDeleted) 
{
	count++;
	if (!inVob->GetPhysicsEnabled()) {

		if (count>10) {
			inVob->SetCollDet	(TRUE);
			inVob->SetSleeping	(TRUE);
			inVob->SetAICallback(NULL);
		} else {
			inVob->SetPhysicsEnabled(TRUE);
		}
	}
};

void oCAIDrop::ReportCollisionToAI	(const zCCollisionReport& collisionReport)
{
	StartCollisionSound(vob,collisionReport);
	
	// *****************************
	// Logischer Sound
	// *****************************
	if (vob) oCNpc::AssessQuietSound_S(vob,vob->GetPositionWorld());
};

void oCAIDrop::SetVelocity(zREAL f, zREAL angle)
{
	zMATRIX4 trafo	= owner -> trafoObjToWorld * Alg_Rotation3DN ( zVEC3(1,0,0), -angle);
	zVEC3	 force	= trafo.GetAtVector();
	vob->GetRigidBody()->SetVelocity(force * f);
}

void oCAIDrop::SetStartPosition(zVEC3 &f)
{
	vob->SetCollDet(FALSE);

	// Hier der Einfüge-Test
	vob->SetPositionWorld(f);
	vob->ResetRotationsWorld(); // [Moos] 20.12.00 Anpassung an Vob-Änderung
	if (zDYNAMIC_CAST<oCVob>(vob)) {
		if (((oCVob*)vob)->SearchFreePosition(f,owner)) {
			vob->SetPositionWorld(f);
		} else {
			zerr.Warning("U:DROP:Not enough space for object.");
		}
	}

    vob->SetCollDet(TRUE);       // [Moos] lieber ganz aktivieren, sonst fällt das Ding noch durchs Mesh....
}

void oCAIDrop :: Archive (zCArchiver& arc)
{
	oCAISound :: Archive(arc);
	if (arc.InProperties()) return;

	// Others
/*	arc.WriteObject	("vob"			,vob);
	
	arc.WriteBool	("collision"	,collisionOccured);
	arc.WriteFloat	("timeLeft"		,timer);*/
}

void oCAIDrop :: Unarchive	(zCArchiver& arc)
{
	oCAISound :: Unarchive(arc);
	if (arc.InProperties()) return;
	
/*	ClearIgnoreCDVob	();
	zRELEASE			(vob);
	zRELEASE			(owner);

	// Others
	vob					= (zCVob*) arc.ReadObject1	("vob"	);	// AddRef +1 (!)
	
	arc.ReadBool		("collision"	,collisionOccured);
	arc.ReadFloat		("timeLeft"		,timer);*/
}

// ******************************************************
// Archive...
// ******************************************************

zCLASS_DEFINITION_ABSTRACT	(oCAISound,			zCAIBase,		0)
zCLASS_DEFINITION			(oCAIArrowBase,		oCAISound,		0, 0)
zCLASS_DEFINITION			(oCAIArrow,			oCAIArrowBase,	0, 0)
zCLASS_DEFINITION			(oCAIDrop,			oCAISound,		0, 0)

zCLASS_DEFINITION			(oCAIVobMove,		oCAISound,		0, 0)
zCLASS_DEFINITION			(oCAIVobMoveTorch,	oCAIVobMove,	0, 0)

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 


	
	