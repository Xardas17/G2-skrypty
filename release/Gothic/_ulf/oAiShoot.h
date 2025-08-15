/******************************************************************************** 
 
     $Workfile:: oAIShoot.h           $                $Date:: 22.01.01 22:38   $
     $Revision:: 14                   $             $Modtime:: 22.01.01 20:30   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oAIShoot.h $
 * 
 * 14    22.01.01 22:38 Wohlers
 * 
 * 13    11.01.01 16:23 Keskenti
 * 
 * 12    20.12.00 18:23 Moos
 * 
 * 11    20.12.00 17:13 Moos
 * 
 * 10    20.12.00 12:34 Keskenti
 * 
 * 9     1.12.00 11:00 Keskenti
 * 
 * 8     21.11.00 14:12 Wohlers
 * 
 * 7     19/10/00 15:03 Luesebrink
 * 
 * 6     19.10.00 13:38 Moos
 * 
 * 5     5.10.00 22:34 Keskenti
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

#ifndef __OAI_SHOOT__
#define __OAI_SHOOT__

#include "z3d.h"
#include "zAI.h"
#include "zSoundMan.h"
#include "zArchiver.h"
#include "zCollisionDetector.h"

class oCItem;
class oCNpc;

class oCAISound : public zCAIBase 
{
	zCLASS_DECLARATION (oCAISound)

public:
	oCAISound					() { slideSoundOn=FALSE; };
	
	void			RemoveSlideSound			();
	void			CheckSlideSound				(zCVob* vob);
	int				GetSoundMaterial			(zCVob* vob, zCSoundManager::zTSndManMedium &mat_type);
	void			StartCollisionSound			(zCVob* source, const zCCollisionReport& collisionReport);

protected:
	virtual			~oCAISound					() { RemoveSlideSound(); };

private:
	zTSoundHandle	slideSoundHandle;
	zBOOL8			slideSoundOn;
};

class oCAIArrowBase : public oCAISound {
	zCLASS_DECLARATION (oCAIArrowBase)

public:
	oCAIArrowBase									();

	// virtuals
	void			DoAI							(zCVob* inVob, zBOOL& vobDeleted);
	zBOOL			HasAIDetectedCollision			() { return FALSE; }
	void			ReportCollisionToAI				(const zCCollisionReport& collisionReport);
	void			AICollisionResponseSelfDetected (const zVEC3& absolutMoveDist, zBOOL& tryAgain) {}; 

	// other
	// Schuetze, andere Pfeile, ein bereits getroffenes Opfer, ...
	void			AddIgnoreCDVob					(zCVob *inVob);
	void			ClearIgnoreCDVob				();
	void			CreateTrail						(zCVob *inVob);

	// ******************************************************
	// Archive...
	// ******************************************************
	virtual void	Archive							(zCArchiver& arc);
	virtual void	Unarchive						(zCArchiver& arc);
	virtual	zBOOL	GetIsProjectile					()						{ return TRUE;	};

protected :
	virtual			~oCAIArrowBase					();

	zCList<zCVob>	ignoreVobList;
	zBOOL			collisionOccured;
	zREAL			timeLeft;
	zCVob*			vob;
	zBOOL			startDustFX;
	zCVob*			trailVob;
	zCPolyStrip*	trailStrip;
	zBOOL			trailActive;
	zREAL			trailTime;
	zBOOL			hasHit;
};


// PfeilAI
class oCAIArrow : public oCAIArrowBase {
	
	zCLASS_DECLARATION (oCAIArrow)
	
public:
	oCAIArrow								();
	
	// Schuetze, andere Pfeile, ein bereits getroffenes Opfer, ...
	void			SetupAIVob				(zCVob *inVob, zCVob *shootVob, zCVob *target = NULL);
	void			DoAI					(zCVob* inVob, zBOOL& vobDeleted);
	void			ReportCollisionToAI		(const zCCollisionReport& collisionReport);

	void			SetTarget				(zCVob *pTargetVob);	
	void			ClearUsedVobs			();
	zBOOL			CanThisCollideWith		(zCVob* vob);	

	// ******************************************************
	// Archive...
	// ******************************************************
	virtual void	Archive					(zCArchiver& arc);
	virtual void	Unarchive				(zCArchiver& arc);

protected:
	virtual			~oCAIArrow				();

private:
	oCItem*			arrow;
	oCNpc*			owner;
	zBOOL			removeVob;
	zCVob*			targetNPC;
};

// Drop - AI
class oCAIDrop : public oCAISound {
	
	zCLASS_DECLARATION (oCAIDrop)
	
public:
	oCAIDrop();

	// virtuals
	void			DoAI					(zCVob* inVob, zBOOL& vobDeleted);
	zBOOL			HasAIDetectedCollision	()				{ return FALSE; }
	zBOOL			CanThisCollideWith		(zCVob* vob)	{ return !ignoreVobList.InList(vob); };
	void			ReportCollisionToAI		(const zCCollisionReport& collisionReport);

	// other
	void			AddIgnoreCDVob			(zCVob *inVob);
	void			ClearIgnoreCDVob		();				
	
	void			SetupAIVob				(zCVob *inVob, zCVob *shootVob);
	void			SetVelocity				(zREAL f, zREAL angle);
	void			SetStartPosition		(zVEC3 &f);

	// ******************************************************
	// Archive...
	// ******************************************************
	virtual void			Archive			(zCArchiver& arc);
	virtual void			Unarchive		(zCArchiver& arc);

protected :
	virtual			~oCAIDrop				();

private:

	zCList<zCVob>	ignoreVobList;
	zCVob*			vob;
	zCVob*			owner;
	zBOOL			collisionOccured;
	zREAL			timer;
	zREAL			count;

};

class oCAIVobMove : public oCAISound {
	
	zCLASS_DECLARATION (oCAIVobMove)

public :

	oCAIVobMove								();

	virtual void	Init					(zCVob* inVob, zCVob* shootVob, zVEC3& startPos, zREAL angle = 0, zREAL force = 0, zMATRIX4* matrix = NULL);
	void			AddIgnoreCDVob			(zCVob *inVob);
	void			ClearIgnoreCDVob		();				

	zCVob*			GetOwner				()	{ return owner; };

	// virtuals
	virtual void	DoAI					(zCVob* inVob, zBOOL& vobDeleted);
	virtual zBOOL	CanThisCollideWith		(zCVob* vob)	{ return !ignoreVobList.InList(vob); };
	virtual void	ReportCollisionToAI		(const zCCollisionReport& collisionReport);

	virtual void	Archive					(zCArchiver& arc);
	virtual void	Unarchive				(zCArchiver& arc);

protected :
	virtual			~oCAIVobMove			();

	zCVob			*vob, *owner;
	zCList<zCVob>	ignoreVobList;
	
};

class oCAIVobMoveTorch : public oCAIVobMove {

	zCLASS_DECLARATION (oCAIVobMoveTorch)

public:

	oCAIVobMoveTorch						();

	virtual void	Init					(zCVob* inVob, zCVob* shootVob, zVEC3& startPos, zREAL angle = 0, zREAL force = 0, zMATRIX4* matrix = NULL);
	virtual void	DoAI					(zCVob* inVob, zBOOL& vobDeleted);
	
protected:
	virtual			~oCAIVobMoveTorch		();

	zBOOL			CheckWater				();
	void			BurnedOut				();

	zREAL			timer;
};

#endif