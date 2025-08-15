/******************************************************************************** 
 
     $Workfile:: zAI.cpp              $                $Date:: 20.12.00 3:05    $
     $Revision:: 8                    $             $Modtime:: 19.12.00 1:31    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/zengin_work/_Dieter/zAI.cpp $
 * 
 * 8     20.12.00 3:05 Hildebrandt
 * 
 * 7     7.09.00 20:41 Hildebrandt
 * 
 * 6     21.08.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 8 $ ($Modtime: 19.12.00 1:31 $)


#include <zCore.h>
#include <z3d.h>
#include <zPhysics.h>
#include <zAi.h>
#include <zSound.h>
#include <zSoundMan.h>
#include <zVob.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

zCLASS_DEFINITION_ABSTRACT (zCAIBase		, zCObject	,0)
zCLASS_DEFINITION_ABSTRACT (zCAIBaseSound	, zCAIBase	,0)


void zCAIBaseSound::RemoveSlideSound() {
	if (slideSoundOn) {
		slideSoundOn=FALSE;
		zsound->StopSound (slideSoundHandle);
	}; 
};

void zCAIBaseSound::CheckSlideSound(zCVob* vob) {
	if ((vob->GetPhysicsEnabled()) &&
		(vob->GetRigidBody()->GetMode()==zPHY_RBMODE_SLIDE)) 
	{
		if (!slideSoundOn) {
			int levelMat = 0;							// einsetzen !!
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

void zCAIBaseSound::StartDefaultCollisionSound	(zCVob* vob, const zCCollisionReport& collisionReport) 
{
	int thisMat = 99;
	if	(collisionReport.m_poCollObject1->GetCollObjClass()==zCCollObjectLevelPolys::S_GetCollObjClass())
	{
		zCCollObjectLevelPolys	*collObjLevel = static_cast<zCCollObjectLevelPolys*> (collisionReport.m_poCollObject1);
		zERR_ASSERT				(collObjLevel->m_aoPolyList.GetNum()>0);
		int levelMat			= int(collObjLevel->m_aoPolyList[0]->GetMaterial()->GetMatGroup());
		zsndMan->StartHitSound	(vob, zCSoundManager::zSND_MAN_MEDIUM_OBJECT, zCSoundManager::zSND_MAN_MEDIUM_LEVEL, thisMat, levelMat, &collisionReport);
	} else 
	{
		// damit nicht beide Vobs den Coll-Sound ausloesen, macht bei einer Coll. dies nur der mit der kleineren Adresse!
		// AUSNAHME: der andere Vob hat keine AI und kann deshalb auch keinen Sound triggern !
		zCVob *otherVob	= static_cast<zCVob*>(collisionReport.m_poCollObject1->GetClientData());
		if ((vob<otherVob) || (!otherVob->GetAI()))
		{
			int otherVobMat = 99;
			zsndMan->StartHitSound (vob, zCSoundManager::zSND_MAN_MEDIUM_ITEM, zCSoundManager::zSND_MAN_MEDIUM_ITEM, thisMat, otherVobMat, &collisionReport);
		};
	};
};
