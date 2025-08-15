/******************************************************************************** 
 
     $Workfile:: zAI.h                $                $Date:: 20.12.00 3:05    $
     $Revision:: 7                    $             $Modtime:: 19.12.00 1:59    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Behavior / Artificial Intelligence Interface
   created       : 24.2.97

 * $Log: /current_work/zengin_work/_Dieter/zAI.h $
 * 
 * 7     20.12.00 3:05 Hildebrandt
 * 
 * 6     4.12.00 17:39 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 5     15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 4     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 7 $ ($Modtime: 19.12.00 1:59 $)


#ifndef __ZAI_H__
#define __ZAI_H__

#ifndef __ZOBJECT_H__
#include <zObject.h>
#endif

#ifndef __ZTOOLS_H__
#include <zTools.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZDISK_H__
#include <zDisk.h>
#endif

class			zCVob;					// zVob.h
typedef int		zTSoundHandle;			// zSound.h
class			zCCollisionReport;		// zCCollisionDetector.h


class zENGINE_API zCAIBase : public zCObject {
	zCLASS_DECLARATION	(zCAIBase)
public:
			 zCAIBase() {};
	virtual void	DoAI							(zCVob* vob, zBOOL& vobDeleted) = 0;

	// Collision / Physics
	virtual zBOOL	CanThisCollideWith				(zCVob* vob)	{ return TRUE; };
	virtual void	ReportCollisionToAI				(const zCCollisionReport& collisionReport) {};

	// OLD
	virtual zBOOL	HasAIDetectedCollision			()				{ return FALSE; };	// AIDetectCollisionStat()
	virtual void	AICollisionResponseSelfDetected (const zVEC3& absolutMoveDist, zBOOL& tryAgain) { };

	//
	virtual void	HostVobRemovedFromWorld			(zCVob* hostVob, zCWorld* hostWorld) {};	// informs the AI, called BEFFORE the actual removal
	virtual void	HostVobAddedToWorld				(zCVob* hostVob, zCWorld* hostWorld) {};	// informs the AI, called AFTER   the actual addition
	virtual	zBOOL	GetIsProjectile					()											{ return FALSE;	};

protected:
	virtual ~zCAIBase() {};		// use Release() instead !
};


class zENGINE_API zCAIBaseSound : public zCAIBase {
	zCLASS_DECLARATION	(zCAIBaseSound)
public:
					zCAIBaseSound				() { slideSoundOn=FALSE; };
	
	void			RemoveSlideSound			();
	void			CheckSlideSound				(zCVob* vob);
	void			StartDefaultCollisionSound	(zCVob* vob, const zCCollisionReport& collisionReport);

protected:
	virtual			~zCAIBaseSound				() { RemoveSlideSound(); };	// use Release() instead !
private:
	zTSoundHandle	slideSoundHandle;
	zBOOL8			slideSoundOn;
};

#endif