/******************************************************************************** 
 
     $Workfile:: Ovob.h               $                $Date:: 11.02.01 15:06   $
     $Revision:: 11                   $             $Modtime:: 11.02.01 14:42   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/Ovob.h $
 * 
 * 11    11.02.01 15:06 Wohlers
 * 
 * 10    8.02.01 15:44 Wohlers
 * 
 * 9     26.01.01 16:21 Moos
 * 
 * 8     19.01.01 1:05 Wohlers
 * 
 * 7     8.01.01 20:09 Keskenti
 * 
 * 6     30.10.00 16:24 Wohlers
 * 
 * 5     20.09.00 21:30 Rueve
 * typedef
 * 
 * 4     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 9     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 8     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 7     6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 5     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 4     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __OVOB_H__
#define __OVOB_H__

#include "z3d.h"
#include "zVob.h"
#include "zVobMisc.h"
#include "zSoundMan.h"

class oCWorld;
class oCAIVobMove;
class zCCamera;

// Sound Material Namen für oVobs

enum oTSndMaterial {
	SND_MAT_WOOD,		SND_MAT_STONE,		SND_MAT_METAL, 
	SND_MAT_LEATHER,	SND_MAT_CLAY,		SND_MAT_GLAS 
};

extern const zSTRING SndMaterialName[6];

class oCVob : public zCVob
{
	zCLASS_DECLARATION	(oCVob)
public:

			oCVob									();
	virtual void			Init					();

	static	void			ShowVobDebugInfo		(zCCamera *camera);
	virtual void			ShowDebugInfo			(zCCamera *camera);

	void					SetShowDebug			(BOOL debugon);
	zBOOL					GetShowDebug			();
	void					ToggleShowDebug			();

	zBOOL					SearchNpcPosition		(zVEC3& fit);
	zBOOL					SearchFreePosition		(zVEC3& fit, zCVob* origin);

	zBOOL					HasEnoughSpace			(zVEC3& vec);
	zBOOL					HasNpcEnoughSpace		(zVEC3& vec);
	zBOOL					GetFloorPosition		(zVEC3& pos);
	zBOOL					GetFloorPositionWithVob	(zVEC3& centerPos, zCVob* &standingOnThisVob);
	void					SetOnFloor				(zVEC3& pos);

	virtual int				GetInstance				();
	virtual zSTRING			GetInstanceName			();

	virtual zBOOL			IsOwnedByGuild			(int guild)		{ return FALSE; };
	virtual zBOOL			IsOwnedByNpc			(int instance)	{ return FALSE;	};

	virtual zBOOL			DoFocusCheckBBox		()				{ return FALSE; };
	void					StartParticleEffects	(zCTree<zCVob>* vobtree);

	virtual oCAIVobMove*	GetAIVobMove			();

	// *********************************
	// Sound
	// *********************************
	virtual void			GetSoundMaterial_AM		(zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2, int damage) {};
	virtual	void			SetSoundMaterial		(oTSndMaterial mat)		{};
	virtual oTSndMaterial	GetSoundMaterial		()						{ return SND_MAT_WOOD; };

	// **************************************
	// Archiver
	// **************************************

	virtual	void			Archive					(zCArchiver &arc);
	virtual	void			Unarchive				(zCArchiver &arc);

	// **************************************
	// Cutscene
	// **************************************
	virtual int				GetCSStateFlags			()		{ return 0; };

	static void				ClearDebugList			();

protected:
	virtual ~oCVob									();

	zBOOL zCCFASTCALL		Render					(zTRenderContext &renderContext);
};

// ***************************************************************************************
// Neue Vob-Klasse zCTouchDamage (damit koennen u.a. PFX Schaden bei Beruehrung anrichten)
// Ulf: ableiten & GetDamageTypeArcEnum() ueberschreiben!
// ***************************************************************************************

class oCTouchDamage : public zCTouchDamage
{
	zCLASS_DECLARATION	(oCTouchDamage)
public:

private:
	virtual const char*		GetDamageTypeArcEnum	(const zDWORD index);	
};

#endif