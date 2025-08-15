/******************************************************************************** 
 
     $Workfile:: zPolyStrip.h         $                $Date:: 4.12.00 17:29    $
     $Revision:: 11                   $             $Modtime:: 4.12.00 17:28    $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Polystrip effects visual
   created       : 10.9.98

 * $Log: /current_work/zengin_work/_Dieter/zPolyStrip.h $
 * 
 * 11    4.12.00 17:29 Hildebrandt
 * 
 * 10    13.11.00 23:51 Hildebrandt
 * 
 * 9     7.10.00 0:41 Hildebrandt
 *  
 * 8     6.10.00 1:05 Hildebrandt
 * 
 * 7     23.09.00 17:44 Hildebrandt
 * 
 * 6     23.09.00 17:08 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 5     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 3     16.11.99 19:50 Hildebrandt
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 11 $ ($Modtime: 4.12.00 17:28 $)

// =======================================================================================================================

#ifndef __ZPOLYSTRIP_H__
#define __ZPOLYSTRIP_H__

#ifndef __ZVISUAL_H__
#include <zVisual.h>
#endif

#ifndef __ZMATERIAL_H__
#include <zMaterial.h>
#endif

// =======================================================================================================================

class zCPolyStrip : public zCVisual {
	zCLASS_DECLARATION	(zCPolyStrip) 
public:
	// zCVob Interface
	zBOOL				Render					(zTRenderContext& renderContext);
	zBOOL				IsBBox3DLocal			();
	zTBBox3D			GetBBox3D				();
	zSTRING				GetVisualName			() { return ""; };
	void				SetVisualUsedBy			(zCVob* vob);

	//
			 zCPolyStrip();
	void				AllocateResources		(int numSeg);
	virtual void		FreeResources			();
	void				EmptyEffect				();				// reset effect but keep resources
	int					GetNumAllocSegments		() const			{ return numPoly;	};
	int					GetNumVisibleSegments	() const			{ return numSeg;	};
	// frame of reference (local or world)
	void				SetIsLocalFOR			(const zBOOL local)	{ localFOR = local; };
	zBOOL				GetIsLocalFOR			() const			{ return localFOR;	};

	//
	enum zTCamAlign {
		zCAM_ALIGN_NONE,	// fastest
		zCAM_ALIGN_STRIP,	// align strip as whole
		zCAM_ALIGN_POLY		// align each poly of strip
	};
	void				SetCamAlign				(const zTCamAlign newCamAlign)	{ camAlign = newCamAlign;	};
	zTCamAlign			GetCamAlign				()  const						{ return camAlign;			};
	void				SetVisibleSegments		(zREAL visibleFirst, zREAL visibleLast);	// range [0;1]

	// alpha
	void				SetAlphaFadeSpeed		(const zREAL fadeSpeed)		{ alphaFadeSpeed	= fadeSpeed;	};
	zREAL				GetAlphaFadeSpeed		() const					{ return alphaFadeSpeed;			};
	void				SetNewSegmentAlpha		(const zREAL newSegAlpha)	{ newAlpha			= newSegAlpha;	};
	zREAL				GetNewSegmentAlpha		() const					{ return newAlpha;					};

	// ?
	void				SetGlobalAlpha			(const int alpha)	{ material->SetAlpha			(alpha);	};
	int					GetGlobalAlpha			() const			{ return material->GetAlpha	();				};
	
	// nur sinnvoll, bei (camAlign!=CAM_ALIGN_NONE)
	void				ProjectToSphere			(const zTBSphere3D& sphere);
	void				GenerateCPLightning0	(const zPOINT3& startPos, const zPOINT3& endPos, zREAL wildness=zREAL(0.6F));	// wildness= [0;1], num allocated segments must be pow2+1 (eg 65)
	void				GenerateCPLightning1	(const zPOINT3& startPos, const zPOINT3& endPos, zREAL wildness);				// wildness= [0;1]
	void				GenerateCircle			(const zTBSphere3D& sphere, const zPOINT3& startPos, const zVEC3& dirNormal);

	void				SetWidth				(const zREAL w)		{ width = w;	};
	zREAL				GetWidth				() const			{ return width; };
												
	//											
	void				AddSegment				(const zPOINT3& pos1, const zPOINT3& pos2);			// vertices & centerPoint
//	void				AddSegment				(const zPOINT3& centerPoint, zREAL segWidth=1.0F);	// centerPoint
	void				AddSegment				(const zPOINT3& centerPoint);						// centerPoint
	void				AddSegmentSmart			(const zPOINT3& pos1, const zPOINT3& pos2);			// high curvature: addNewSegment, low curv: updateLastSegment
	void				UpdateSegment			(int segNr, const zPOINT3& posUp, const zPOINT3& posDown, const zPOINT3& center);	// segNr==-1 means: update last segment
	void				UpdateSegmentAlpha		(int segNr, const zREAL inNewAlpha);
	zPOINT3				GetCenterPoint			(int segNr)		{ if (segNr<numSeg) return centerPointList[segNr]; else return zVEC3(0,0,0); };
	void				SetHeightCheckEnabled	(const zBOOL en){ heightCheck = en;	};
	void				SetHeightBound			(const zREAL f) { heightBound = f;	};
	void				SetEveryFrameUpdate		(const zBOOL b)	{ everyFrameUpdate = b;};
	zBOOL				GetEveryFrameUpdate		()const			{ return everyFrameUpdate;};
												
	//											
//	void				StitchStartTo			(const zCPolyStrip& polyStrip);
	void				CalcBBox3D				();

	//
	zCMaterial			*material;				// FIXME: oeffentlich ?
protected:				
	zCVertex			*vertList;
	zCPolygon			*polyList;
	int					numPoly;
	int					numVert;
						
	zVEC3				*centerPointList;
	zREAL				*alphaList;
	zREAL				width;

	zCVob				*connectedVob;
	zTBBox3D			bbox3D;
	zTCamAlign			camAlign;
	zBOOL				heightCheck;
	zBOOL				everyFrameUpdate;
	zREAL				heightBound;

	// generated segments
	int					firstSeg;
	int					lastSeg;
	int					numSeg;

	// visible segments (fractions)
	zREAL				visLastFrac;
	zREAL				visFirstFrac;

	//
	zREAL				alphaFadeSpeed;
	zREAL				newAlphaFadeSpeed;
	zREAL				newAlpha;

	//
	virtual ~zCPolyStrip();		
	void				Lightning0Subdivide		(const zPOINT3& startPos, const zPOINT3& endPos, zREAL s, int n);
	void				AlignToCamera			();

private:
	int					lastDirSeg;					// for AddSegmentSmart
	zVEC3				lastDirNormal;
	struct {
		zUINT8			localFOR			: 1;
	};
};

// =======================================================================================================================

class zCLightning : public zCVisual {
public:
	// zCVob Interface
	zBOOL				Render				(zTRenderContext& renderContext);			// TRUE=visible, FALSE=not visible
	zBOOL				IsBBox3DLocal		() { return TRUE;			};				// OS / WS
	zTBBox3D			GetBBox3D			() { zTBBox3D box; box.mins = -zVEC3(999,999,999); box.maxs=zVEC3(999,999,999); return box; };
	void				SetVisualUsedBy		(zCVob* vob);
	zSTRING				GetVisualName		() { return ""; };
	zBOOL				GetVisualDied		()						{ return FALSE; };

	//
	class zCBolt : public zCPolyStrip {
	public:
		zCArray<zCBolt*>	childList;

		void			Generate_R			(const zPOINT3& startPos, const zPOINT3& endPos, zREAL depth=1.0F);
		zBOOL			Render				(zTRenderContext& renderContext);
		void			FreeResources		();
	};

	zCBolt				rootBolt;
	void				Generate			(const zPOINT3& startPos, const zPOINT3& endPos);
	void				SetProjectionSphere	(const zTBSphere3D& sphere);
};

// =======================================================================================================================

class zCQuadMark : public zCVisual {
	zCLASS_DECLARATION	(zCQuadMark) 
public:
	// zCVob Interface
	zBOOL				Render					(zTRenderContext& renderContext);
	zBOOL				IsBBox3DLocal			() { return TRUE; };
	zTBBox3D			GetBBox3D				();
	zSTRING				GetVisualName			() { return ""; };
	void				SetVisualUsedBy			(zCVob* vob);

	//
	zCQuadMark();
	enum zTTexAniType {
		zTEXANI_NONE,
		zTEXANI_SCALEUP,
		zTEXANI_SCALEUP_GRAV,
		zTEXANI_SCALEUP_AUTO,
		zTEXANI_SCALEDOWN
	};

	struct zTEffectParams {
		 zTTexAniType	texAniType;
		 zREAL			texAniScaleStart;		// 0..1
		 zREAL			texAniSpeed;			// 0 .. 1.0 ..
		 zREAL			alphaFadeSpeed;			// 0 .. .1 ..
	};

	/*
		Material/Texture Handling:
		Usually a default-material is used for new quadmarks, that can be obtained and adjusted via the
		GetDefaultMaterial() method. If within a quadmark Visual, some quadmarks need different textures/materials,
		then these textures/materials are passed as arguments in the CreateQuadMark() methods. Passed textures/materials
		are only used for that call, after that a CreateQuadMark() call without tex/mat again uses the default material.
	*/

	//
	zCMaterial&			GetDefaultMaterial		() const						{ return (*material);				};
	void				SetTexture				(zSTRING&		texName)		{ material->SetTexture (texName);	};
	void				SetTexture				(zCTexture*		texture)		{ material->SetTexture (texture);	};
	void				SetAlphaFadeSpeed		(const zREAL	alphaFadeSpeed) { this->alphaFadeSpeed = alphaFadeSpeed;	};
	void				SetDontRepositionConnectedVob (const zBOOL b)			{ dontRepositionConnectedVob = b;			};
	void				CreateQuadMark			(const zPOINT3& rayOrg, 
												 const zVEC3&	ray, 
												 const zVEC2&	quadMarkDim, 
												 zTEffectParams	*aniEffects=0);
	void				CreateQuadMark			(const zPOINT3& rayOrg, 
												 const zVEC3&	ray, 
												 const zVEC2&	quadMarkDim, 
												 zSTRING&		texName,
												 zTEffectParams	*aniEffects=0);
	void				CreateQuadMark			(const zPOINT3& rayOrg, 
												 const zVEC3&	ray, 
												 const zVEC2&	quadMarkDim, 
												 zCMaterial		*newMaterial,
												 zTEffectParams	*aniEffects=0);
	void				CreateQuadMark			(zCPolygon		*hitPoly,
												 const zPOINT3&	hitLocation,
												 const zVEC2&	quadMarkDim, 
												 zTEffectParams	*aniEffects=0);
	int					GetNumActive			();		// quadMarks that are not faded out

protected:
	struct zTQuadMarkVert {
		zVEC3		position;
		zVEC2		texCoord;
	};

	struct zTQuadMarkPoly {
		zCArray<zTQuadMarkVert>	vertex;
	};

	zCMesh				*quadMesh;
	zCVob				*connectedVob;
	zCMaterial			*material;
	zCMaterial			*actMaterial;
	zREAL				alphaFadeSpeed;
	zBOOL				dontRepositionConnectedVob;
	
	struct zTQuadMarkAniState {
		int				firstPolyIndex;
		int				lastPolyIndex;
		zREAL			scaleStart;
		zREAL			scaleCur;
		zREAL			scaleSpeed;
		zREAL			scaleSpeedCur;
		zVEC2			uvDelta;
		zVEC2			uvScale;
		zTTexAniType	texAniType;
		zREAL			alpha;
	};
	zCArray<zTQuadMarkAniState>	quadMarkAniTracker;

	virtual ~zCQuadMark();		// use Release() instead!
	zBOOL				ClipQuadPolyToPlane		(zTQuadMarkPoly& inPoly		, zTQuadMarkPoly& outPoly	, const zTPlane& pplane);
	void				ClipQuadPolyToWorldPoly (zTQuadMarkPoly& inQuadPoly	, zCPolygon* worldPoly		, zCArray<int> &clipEdgeList);
	void				InitFirstQuadPoly		(zCPolygon* worldPoly		, const zPOINT3& hitLocation, const zVEC3& xvec, const zVEC3& yvec, zTEffectParams *aniEffects);
	void				InitQuadPoly			(zTQuadMarkPoly& quadPoly	, zCPolygon* worldPoly);
	void				AddQuadPolyToQuadMesh	(zTQuadMarkPoly& quadPoly	, zCPolygon* worldPoly);
	void				ProjectQuadPolyToPlane	(const zTQuadMarkPoly &inQuadPoly, zTQuadMarkPoly &outQuadPoly, const zTPlane& plane);
	zCPolygon*			GetNextWorldPoly		(zCVertex* vert1, zCVertex* vert2);
	void				ProcessWorldPoly		(zCPolygon *worldPoly);
	void				CalcQuadAxis			(zCPolygon* worldPoly, zVEC3& xvec, zVEC3& yvec);

	void				ProcessAniTracker		();

private:
	// construction
	zCPolygon			**worldPolyList;
	int					numWorldPoly;
	zCArray<zCPolygon*>	visitedPolyList;
	zTQuadMarkPoly		firstQuadPoly;
	zCPolygon			*firstWorldPoly;
	zVEC3				averageNormal;
};

// =======================================================================================================================

#endif