/******************************************************************************** 
 
     $Workfile:: zFlash.h         $                 $Date:: 24.04.01 17:33      $
     $Revision:: 6                $                 $Modtime:: 19.04.01 0:56    $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Carsten/zFlash.h $
 * 
 * 6     24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 5     4.12.00 18:23 Moos
 * 
 * 4     12.10.00 16:17 Moos
 * 
 * 3     22.09.00 20:10 Simon
 * 
 * 2     29.08.00 14:45 Edenfeld
 * 
 * 1     29.08.0 13:05 Simon
 * ZenGin v0.92
 * 
 *********************************************************************************/

#ifndef __ZFLASH_H__
#define __ZFLASH_H__

#ifndef __ZVISUAL_H__
#include <zVisual.h>
#endif

#ifndef __ZMATERIAL_H__
#include <zMaterial.h>
#endif

#ifndef __ZPOLYSTRIP_H__
#include <zPolyStrip.h>
#endif

// =======================================================================================================================

class zCFlash : public zCVisual {
//	zCLASS_DECLARATION (zCFlash)
public:

	zCFlash();
	~zCFlash();

	// zCVob Interface
	zBOOL				Render				(zTRenderContext& renderContext);			// TRUE=visible, FALSE=not visible
	zBOOL				IsBBox3DLocal		() { return TRUE;			};				// OS / WS
	zTBBox3D			GetBBox3D			() { zTBBox3D box; box.mins = -zVEC3(999,999,999); box.maxs=zVEC3(999,999,999); return box; };
	void				SetVisualUsedBy		(zCVob* vob);
	zSTRING				GetVisualName		() { return ""; };
	void				DynLightVisual		(const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld=0) {};
	zBOOL				PerformZTest		() const				{ return FALSE; };

	zBOOL				GetVisualDied		();

	void				SetTexture			(const zSTRING& texName);
	void				SetProjectionSphere (const zTBSphere3D& sphere);

	//
	class zCBolt : public zCPolyStrip {
	public:

		zCBolt();
        ~zCBolt(){FreeResources();}

		zVEC3*				GetCenterPointList		() { return centerPointList; };
		int					GetNumSeg				() { return numSeg; };

		zCArray<zCBolt*>	childList;

		void            InterpolateTo		( zCBolt *boltTo, zREAL ipolate );
		void			Copy				( zCBolt *bolt );

		void			Generate_R			( const zPOINT3& startPos, const zPOINT3& endPos, zREAL depth=1.0F, zBOOL addEnd=FALSE );
		zBOOL			Render				(zTRenderContext& renderContext);
		void			FreeResources		();

		void            SetTexture			(const zSTRING& texName);
		void            SetProjectionSphere (const zTBSphere3D& sphere);

		zBOOL           isRootBolt;
		zBOOL           isChildOne;
		zBOOL           isChildTwo;
		int             numberOfChilds;
		zREAL           roughness;
		int             boltIndex;
		zTBSphere3D		projectionSphere;		

		zREAL			aniPhase;
	};

//
//

	zREAL               timeAlive;
	zVEC3				step;
	BOOL				recalcStep;

	zCBolt				*rootBolt;
	zCBolt              *splitBolt;

	zPOINT3             boltStartPos;
	zPOINT3             boltEndPos;
	zREAL               boltRoughness;
	zSTRING             textureName;

	void                Create( zPOINT3 startPos, zPOINT3 endPos, zREAL roughness );

	void				Generate ( zCBolt *bolt, const zPOINT3& startPos, const zPOINT3& endPos, zREAL roughness1=0.65f );

	zREAL LastUpdateTime;
	void				Update   ( zREAL aniSpeed );
};

// =======================================================================================================================

#endif