/******************************************************************************** 
 
     $Workfile:: oParticleControl.h   $                $Date:: 22.05.00 18:43   $
     $Revision:: 4                    $             $Modtime:: 9.05.00 14:23    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oParticleControl.h $
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
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/
// oCParticleControl.h: interface .
//
//////////////////////////////////////////////////////////////////////

#ifndef __O_PARTICLE_CONTROL__
#define __O_PARTICLE_CONTROL__

#include <zTypes3D.h>
#include <zParticle.h>
#include "zVob.h"

class zCConsole;

class oCParticleControl
{
public:
	oCParticleControl			();
	oCParticleControl			(zCWorld* theWorld);
	~oCParticleControl			();

	zCVob*	GetPFXVob			();
	void	SelectActivePFX		();
	void	EditActivePFX		();
	void	StartActivePFX		();
	void	StartActivePFX		(zCVob *homeVob, zSTRING &node);
	void	CreateNewPFX		(zSTRING& newPFXName);

	void	SetStartPos			(zVEC3 &pos);
	void	SetPFXName			(zSTRING& newPFXName);
	void	SetWorld			(zCWorld* theWorld);
	void	BeginEditActive		(void(*cf)(const zSTRING &s));
	void	EndEditActive		();

	void	DeleteLastPFX		();
	void	UpdateInternals		();

private:
	zCParticleFX*	partFX;
	zCVob*			pfxVob;
	zTVobID			pfxVobID;
	zSTRING			pfxName;
	zVEC3			startpos;
	zBOOL			IsInEditMode;

	zCWorld*		rnd_world;
	zCConsole*		part_edit;

};


#endif