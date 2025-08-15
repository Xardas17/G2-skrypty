#ifndef __OMAGFRONTIER_H__
#define __OMAGFRONTIER_H__

#include "zcore.h"
#include "ztypes.h"
#include "ztypes3d.h"
#include "zalgebra.h"



class oCVisualFX;
class zCFlash;
class oCNpc;

class oCMagFrontier
{
public:
	oCMagFrontier();
	~oCMagFrontier();

	void		SetNPC						(oCNpc *newnpc);
	void		DoCheck();

    void        DisposeFX                   (){ DisposeWarningFX(); DisposeShootFX(); }
	zREAL       GetDistanceNewWorld			( const zVEC3& pos, zREAL& dist, zVEC3& nearestPoint );
	zREAL       GetDistanceDragonIsland		( const zVEC3& pos, zREAL& dist, zVEC3& nearestPoint );
	zREAL       GetDistanceAddonWorld		( const zVEC3& pos, zREAL& dist, zVEC3& nearestPoint );
	void		StartLightningAtPos			(zPOINT3 &a, zPOINT3 &b);
	void		DoWarningFX					( const int level );
	void		DisposeWarningFX			();
	void		DoShootFX					( const zVEC3& startPoint );
	void		DisposeShootFX				();

private:


	oCVisualFX	*warningFX;
	oCVisualFX	*shootFX;
	oCNpc		*npc;

	zUINT8		isWarning	: 1;		// zBOOL
	zUINT8		isShooting	: 1;		// zBOOL
};



#endif