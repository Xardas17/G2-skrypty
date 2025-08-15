/******************************************************************************** 
 
     $Workfile:: z3d.h                $                $Date:: 8.02.01 6:40     $
     $Revision:: 32                   $             $Modtime:: 8.02.01 6:40     $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ 3D-Engine
   created       : 20.2.97

 * $Log: /current_work/zengin_work/_Dieter/z3d.h $
 * 
 * 32    8.02.01 6:40 Hildebrandt
 * 
 * 31    2.02.01 17:52 Moos
 * 
 * 30    27.01.01 19:42 Moos
 * 
 * 29    11.01.01 21:09 Hildebrandt
 * 
 * 28    6.12.00 18:09 Moos
 * 
 * 27    5.12.00 15:34 Hildebrandt
 * 
 * 26    5.12.00 12:04 Moos
 * 
 * 25    4.12.00 18:23 Moos
 * 
 * 24    23.11.00 9:43 Moos
 * 
 * 23    22.11.00 17:47 Moos
 * 
 * 22    17.11.00 23:15 Hildebrandt
 * 
 * 21    17.11.00 19:29 Moos
 * 
 * 20    13.11.00 21:56 Hildebrandt
 * 
 * 19    3.11.00 19:03 Hildebrandt
 * 
 * 18    25.10.00 15:07 Hildebrandt
 * 
 * 17    19.10.00 17:48 Keskenti
 * 
 * 16    11.10.00 18:05 Speckels
 * 
 * 15    5.10.00 20:18 Hildebrandt
 * 
 * 14    5.10.00 15:30 Hoeller
 * 
 * 13    21.09.00 15:44 Hoeller
 * 
 * 12    2.09.00 6:53 Hildebrandt
 * 
 * 11    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 10    6.07.00 13:33 Hildebrandt
 * 
 * 5     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 16    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 15    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 14    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 12    14.01.00 21:08 Hildebrandt
 * zenGin 0.85c
 * 
 * 11    10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 9     18.11.99 22:18 Hildebrandt
 * 
 * 8     16.11.99 19:49 Hildebrandt
 * 
 * 7     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 32 $ ($Modtime: 8.02.01 6:40 $)

/*
	Baustelle
*/

#ifndef __Z3D_H__
#define __Z3D_H__

// ========================================================================================================

#ifndef __ZOBJECT_H__
#include <ZObject.h>
#endif

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZMATERIAL_H__
#include <zMaterial.h>
#endif

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

#ifndef __ZBVOLUME_H__
#include <zBVolume.h>
#endif

#ifndef __ZMEMPOOL_H__
#include <zMemPool.h>
#endif


// ========================================================================================================

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

// declarations
class zCMaterial;
class zCTexture;
class zCLightMap;
class zCVobLight;
class zCCamera;
class zCWorld;
class zCVob;
class zCVobLight;
enum  zTWld_RenderMode;
class zCViewBase;			// <zViewBase.h>
class zCView;				// <zView.h>

struct zTTraceRayReport;	// <zWorld.h>

// forward declarations
class zCPolygon;
class zCVertex;
class zCVertexTransform;
class zCVertFeature;

// forward declarations
class zCMesh;
	class zCPolygon;
	class zCVertex;

// ========================================================================================================

struct zENGINE_API zTEngineStats {
	// vobs/ai/movement
	int		numVobAI;
	int		numVobAI_only;
	int		numVobAI_full;
	int		numVob_EndMovement;
	int		numVobFirstTestInterpen;

	//
	int		numModelUpdateBBoxTree;

	// clipping
	int		numPolysClipped;
	int		numPlanesClipped;

	// traceRay
	int		numTraceRay;

	void	Clear		()					{ memset (this, 0, sizeof(*this)); };
	void	PrintScreen	(int xscr=-1, int yscr=-1);
};

zENGINE_API extern zTEngineStats zengineStats;

// =========================================================================

//const zVALUE zEPSILON = 0.0001F;

class zCLineCache {
	struct zTCacheEntry {
		int x1, y1, x2, y2, color;
	};
	int				numEntries;
	int				nextFree;
	zTCacheEntry	*cache;
public:
	zCLineCache() {
		numEntries  = 0;
		nextFree	= 0;
		cache		= 0;
	};
	~zCLineCache();
	void	Line	(int x1, int y1, int x2, int y2, zCOLOR color= zCOLOR(255,255,0,255));
	void	Line3D	(const zPOINT3& a, const zPOINT3& b, zCOLOR color= zCOLOR(255,255,0,255), zBOOL useZBuffer=FALSE);
	void	LineCS3D(const zPOINT3& a, const zPOINT3& b, zCOLOR color= zCOLOR(255,255,0,255));
	void	Flush	(zCViewBase* dtp);
};

extern zCLineCache zlineCache;


///////////////////////////////////////////////////////////////////////////
//     CAMERA
///////////////////////////////////////////////////////////////////////////

zENGINE_API extern int playerLightInt;

//const zSTRING zSHADE_MODE_DESC[] = { "normal", "nothing", "constant", "gouraud", "lightmap" };
enum zTShadeMode	{ zSHADE_NORMAL, zSHADE_NOTHING, zSHADE_CONSTANT, zSHADE_GOURAUD, zSHADE_LIGHTMAP };

enum zPROJECTION	{ PERSPECTIVE, ORTHOGONAL };
enum zTCam_ClipType { zCAM_CLIP_TRIV_IN, zCAM_CLIP_TRIV_OUT, zCAM_CLIP_CROSSING };
enum zTCam_DrawMode	{ zCAM_DRAW_NORMAL, zCAM_DRAW_NOTHING, 
					  zCAM_DRAW_WIRE, zCAM_DRAW_FLAT, zCAM_DRAW_TEX };

struct zTViewportData {					// viewport parameters
	int			xmin;					// topright corner (offset)
	int			ymin;
	int			xdim;					// relative dimensions
	int			ydim;
	zVALUE		xminFloat;				// topLeft corner
	zVALUE		yminFloat;
	zVALUE		xmaxFloat;				// bottomRight corner
	zVALUE		ymaxFloat;
	zVALUE		xdimFloat;				// relative dimensions
	zVALUE		ydimFloat;
	zVALUE		xdimFloatMinus1;
	zVALUE		ydimFloatMinus1;
	zVALUE		xcenter;			// xdim / 2
	zVALUE		ycenter;			// ydim / 2
};

enum zTCamTrafoType
{
	zCAM_TRAFO_WORLD,
	zCAM_TRAFO_VIEW,
	zCAM_TRAFO_WORLDVIEW,
	zCAM_TRAFO_WORLDVIEW_INV,	// read-only
	zCAM_TRAFO_VIEW_INV			// read-only
};

template <class T, int SIZE> class zCMatrixStack {
    int		pos;
    T		stack[SIZE];
public:
    zCMatrixStack() : pos(0) {};
    void Push(const T& m) {
        zERR_ASSERT(pos < SIZE);
        stack[pos++] = m;
    };
    T Pop(void) {
        zERR_ASSERT(pos > 0);
        return stack[--pos];
    };
};

class zENGINE_API zCCamera {
public:
	// 3D-frustum definition
	enum { CLIP_FLAGS_FULL		= 63, CLIP_FLAGS_FULL_WO_FAR	= 15 };
	enum { NUM_FRUSTUM_PLANES	=  6, NUM_FRUSTUM_PLANES_WO_FAR	=  4 };
//	enum { FRUSTUM_PLANE_FAR	=  4 };

	// FIXME: frustum-class !
	zTPlane			frustumplanes	[NUM_FRUSTUM_PLANES];
	zBYTE			signbits		[NUM_FRUSTUM_PLANES];						// signx + signy<<1 + signz<<1

	// physical viewport
	zTViewportData	vpData;
	zCViewBase		*targetView;

	// Transformation matrices
	zMATRIX4		camMatrix;				// = trafoWorldView		// trafo: world(obj) => camSpace		 (pos & dir)
	zMATRIX4		camMatrixInv;			// = trafoWorldViewInv	// trafo: cam		 => world(obj)Space  (=vobMatrix)
	void			PushTransform			(const zTCamTrafoType trafoType);
	void			PopTransform			(const zTCamTrafoType trafoType);
	void			SetTransform			(const zTCamTrafoType trafoType, const zMATRIX4& trafo);
	const zMATRIX4& GetTransform			(const zTCamTrafoType trafoType);

	// active camera
	static zCCamera *activeCam;				// deklar. active for one rendering run, set by world
	static zPOINT3  activeCamPos;
	
	// 
	 zCCamera();
	~zCCamera();
	void				SetFarClipZ				(const zVALUE z);
	zVALUE				GetFarClipZ				() const						{ return farClipZ;					};
	zREAL				GetNearClipZ			() const						{ return nearClipZ;					};
	void				SetNearClipZ			(const zVALUE a_fZ)				{ nearClipZ = zMax(zVALUE(0),a_fZ);	UpdateProjectionMatrix		();		};
							
	void				SetVob					(zCVob *vob)					{ connectedVob = vob;				};
	zCVob*				GetVob					() const						{ return connectedVob;				};
	void				SetFOV					(const zREAL fov);				// fieldOfView (degrees)
	zREAL				GetFOV					() const;
	void				SetFOV					(const zREAL fovHori, const zREAL fovVert);
	void				GetFOV					(zREAL& fovHori, zREAL& fovVert) const;
	void				UpdateViewport			();
	void				SetRenderTarget			(zCViewBase *target);
	zPOINT2				GetScreenCenter			() const				{ return zPOINT2(vpData.xcenter, vpData.ycenter);	};
	zBOOL				InViewport				(const zPOINT2& p) const{ return ( (p.n[VX]>=vpData.xminFloat) && (p.n[VX]<vpData.xmaxFloat) ) && ( (p.n[VY]>=vpData.yminFloat) && (p.n[VY]<vpData.ymaxFloat) ); };
	void				GetCamPos				(zPOINT3& camPos) const;
	zREAL				GetCamLightRange		() const				{ return zREAL(playerLightInt); };
	void				SetCamLightRange		(const zREAL range)		{ playerLightInt=int(range);	};
						
	zTCam_ClipType		BBox3DInFrustum			(const zTBBox3D& bbox3D);
	zTCam_ClipType		BBox3DInFrustum			(const zTBBox3D& bbox3D, int& clipFlags);		// clipFlags is input AND output
	zTCam_ClipType		BBox3DInViewport		(const zTBBox3D& bbox3D);
	zBOOL zCCFASTCALL	ScreenProjectionTouchesPortal		(const zTBBox3D& bbox3D, const zTBBox2D& portal2D);
	zBOOL zCCFASTCALL	ScreenProjectionTouchesPortalRough	(const zTBBox3D& bbox3D, const zTBBox2D& portal2D);

	// Camera is activated for all following rendering activities
	void				Activate				();			// resets trafoView to attached camVob, sets trafoWorld to identity, updates frustum/viewport/renderer trafos
	void				SetUpFrustum			(void);
						
	// Tremor			
	void				AddTremor				(const zPOINT3& posWorldSpace, const zREAL radiusSquare, const zREAL timeMsec, const zVEC3& amplitude);
	void				StopTremor				();
	void				PreRenderProcessing		();
	void				PostRenderProcessing	();

	// DrawSimplePoly
	struct zTCamVertSimple {
		zREAL		x,y,z;		// camSpace / screenSpace
		zVEC2		texuv;
		zCOLOR		color;
	};
	void				DrawPolySimple			(zTCamVertSimple *vertList, int numVert, zCMaterial *material, int drawFlags=0);

	// Screen-Effects
	void				SetRenderScreenFade				(const zCOLOR color);
	void				SetRenderScreenFadeTex			(const zSTRING texName);
	void				SetRenderScreenFadeTexAniFPS	(const zREAL a_aniFPS);
	void				SetRenderScreenFadeTexBlendFunc	(const zTRnd_AlphaBlendFunc a_blendFunc);
	void				SetRenderCinemaScope	(const zCOLOR color);

	// Transformation, Projection, Back-Projection
	zPOINT3				Transform				(const zPOINT3& point) const	{ return camMatrix * point; };	// cam should be 'acitve'
	inline void			Project					(const zPOINT3* const p, int& xscr, int& yscr);
	inline void			Project					(const zPOINT3* const p, zFIX& xscr, zFIX& yscr) const;
	inline void			Project					(const zPOINT3* const p, zVALUE& xscr, zVALUE& yscr) const;
	inline void			Project					(const zPOINT3* const p, const zVALUE zrecip, zVALUE& xscr, zVALUE& yscr) const;
	inline void			Project					(const zPOINT3& p, const zREAL zrecip, zVEC2& posScr) const;
												
	inline void			Project					(zCVertexTransform* vert) const;
	inline void			ProjectClamp			(zCVertexTransform* vert) const;
	inline void			ProjectClamp			(zCVertexTransform* vert, const zVALUE zinv) const;
												
	inline void			Project					(zCVertex* vert) const;
	inline void			ProjectClamp			(zCVertex* vert) const;
	inline void			ProjectClamp			(zCVertex* vert, const zVALUE zinv) const;
												
	inline void			BackProject				(const int xscr, const int yscr, zPOINT3& p) const;
	inline void			BackProject				(const zVALUE xscr, const zVALUE yscr, zPOINT3& p) const;

private:
	zBOOL			tremorToggle;
	zREAL			tremorScale;
	zVEC3			tremorAmplitude;
	zVEC3			tremorOrigin;
	zREAL			tremorVelo;

	// Transformation matrices
	zMATRIX4		trafoView;
	zMATRIX4		trafoViewInv;
	zMATRIX4		trafoWorld;
	zCMatrixStack<zMATRIX4,8>	trafoViewStack;
	zCMatrixStack<zMATRIX4,8>	trafoWorldStack;
	zCMatrixStack<zMATRIX4,8>	trafoWorldViewStack;
	zMATRIX4		trafoProjection;

	// DrawSimplePoly
	enum { zTCAM_POLY_NUM_VERT = 4 };
	zTCamVertSimple polyCamVerts[zTCAM_POLY_NUM_VERT];
	zCPolygon		*poly;
	zCMesh			*polyMesh;
	zCMaterial		*polyMaterial;

	// Screen-Effects
	zBOOL			screenFadeEnabled;
	zCOLOR			screenFadeColor;
	zSTRING			screenFadeTexture;
	zREAL			screenFadeTextureAniFPS;
	zTRnd_AlphaBlendFunc screenFadeTextureBlendFunc;
	zBOOL			cinemaScopeEnabled;
	zCOLOR			cinemaScopeColor;

	// not used
	zPROJECTION		projection;
	zTCam_DrawMode	drawMode;
	zTShadeMode		shadeMode;
	zBOOL			drawWire;

	// 
	zVALUE			farClipZ;
	zVALUE			nearClipZ;
	zVALUE			viewDistanceX;
	zVALUE			viewDistanceY;
	zVALUE			viewDistanceXInv;
	zVALUE			viewDistanceYInv;
	zBOOL			vobFarClipZ;
	zREAL			fovH;				// radians
	zREAL			fovV;
	zCVob			*connectedVob;
	// Backdrop ?

	zVALUE			topBottomSin, topBottomCos;
	zVALUE			leftRightSin, leftRightCos;

	void			SetWorldspaceClipPlane	(const zPOINT3& normal, zTPlane *plane);
	void			InitDrawPolySimple		();
	void			CleanupDrawPolySimple	();
	void			RenderScreenFade		();
	void			RenderCinemaScope		();
private:
//	void			SetNearClipZ			(const zREAL z);
	void			UpdateProjectionMatrix	();
	void			CreateProjectionMatrix	(zMAT4& matrix,
											 const zREAL near_plane,		// distance to near clipping plane
											 const zREAL far_plane,			// distance to far clipping plane
											 const zREAL fov_horiz,			// horizontal field of view angle, in radians
											 const zREAL fov_vert);			// vertical field of view angle, in radians
};

///////////////////////////////////////////////////////////////////////////
//     Vertex
///////////////////////////////////////////////////////////////////////////


class zCVertex {
    zMEMPOOL_DECLARATION        (zCVertex)
public:
	zPOINT3		                     position;				// def.

	// methods
    zCVertex    (const zCVertex &v)    {position = v.position; transformedIndex = 0;}
	zCVertex	()                     {transformedIndex = 0;}
    ~zCVertex   ()                     {ResetVertexTransform();}

    zCVertex &  operator =  (const zCVertex &v)     { ResetVertexTransform(); position = v.position; return *this;}
	void		SetPosition	(const zPOINT3& pos)	{ position = pos; };
	void		Draw		(const zCOLOR&  col=zCOLOR(255,255,0,255), const zBOOL useZBuffer=FALSE);

    static	zCVertexTransform* const s_vertexTransforms;

    static void ResetVertexTransforms();

    inline void ResetVertexTransform();

    inline zBOOL IsTransformed() const;

    // use this function if you are sure the vertex has been transformed
    inline zCVertexTransform *VertexTransform		() const;
    inline int		          VertexTransformIndex	() const;

    // use this function if you are sure the vertex has NOT been transformed
    zCVertexTransform* CreateVertexTransform();

    //  automatically create the transformed data
    inline zCVertexTransform* GetVertexTransform();

    union
    {
        struct
        {
            int             transformedIndex;
            int				myIndex;
        };
        unsigned int hackData; // For the usual hacks
    };
private:

    static int               s_vertexTransformsCurrent;
    static bool              s_overflow;

    static void ResetVertexTransform(zCVertexTransform *v);

    friend class zCPolygon;
    friend class zCVertexTransform;
};


class zCVertFeature {
    zMEMPOOL_DECLARATION  (zCVertFeature)
public:
	zPOINT3			vertNormal;
	zCOLOR			lightStat;
	zCOLOR			lightDyn;
	zVALUE			texu, texv;				// Achtung: features sind so nicht share-bar (nur wenn tex&light gleich !)
#ifdef COMPILING_SPACER
	zBOOL			hintSectorFeature;
#endif
	//zVALUE			_padding;				// 32 byte

	void SetMapping		(const zPOINT2& coord)	{
		texu = coord.n[VX];
		texv = coord.n[VY];
	};

	zCVertFeature() {			// FIXME: TEMP !!
		lightStat.Reset();
		lightDyn.Reset();
#ifdef COMPILING_SPACER
		hintSectorFeature = FALSE;
#endif
	};
};

///////////////////////////////////////////////////////////////////////////
//     Polygon
///////////////////////////////////////////////////////////////////////////


const int zMAX_POLY_VERTS					= 21;
const int zMAX_POLY_CLIP_VERTS				= zMAX_POLY_VERTS * 2; 
#ifdef COMPILING_SPACER
	const int zMAX_POLY_CLIP_VERTS_SCENE	= 8192	*2;
	const int zMAX_POLY_VERT_LIST_SCENE		= 16384	*2;		
#else
//	const int zMAX_POLY_CLIP_VERTS_SCENE	= 8192*2;
//	const int zMAX_POLY_VERT_LIST_SCENE		= 16384*2;		// num clipped polys FIXME: zu viele !!
	const int zMAX_POLY_CLIP_VERTS_SCENE	= 8192;
	const int zMAX_POLY_VERT_LIST_SCENE		= 16384;	 	// num clipped polys FIXME: zu viele !!
#endif

class zCMesh;

class zCPolygon 
{
    zMEMPOOL_DECLARATION        (zCPolygon)

//	zCMesh				*Mesh;
public:
//private:
	struct zSPolySavedValues
	{
		zCPolygon* poly;
		zTPlane	   plane;
	};

	struct zSVertexSavedValues
	{
		zCVertex* vert;
		zREAL	  offset;
	};

	struct zSFeatureSavedValues
	{
		zCVertFeature* feat;
		zCOLOR		   color;
		zVEC3		   mapping;
		zVEC3		   vertNormal;
	};


	zCVertex			**vertex;				// array von pointern
public:

	// 
	zTFrameCtr			lastTimeDrawn;
	zTPlane				polyPlane;
	zCMaterial			*material;				// texture, color, light(spec,amb,diff)
	zCLightMap			*lightmap;

	// just the same for every instance
	// clipped vertices
	zCVertex			**clipVert;
	zCVertFeature		**clipFeat;
	int					numClipVert;	

	// unclipped vertices
	zCVertFeature		**feature;				// pointer auf array
	zBYTE				polyNumVert;

	enum zTPortalType	{ zPORTAL_TYPE_NONE			= 0, 
						  zPORTAL_TYPE_SMALL		= 1, 
						  zPORTAL_TYPE_BIG			= 2, 
						  zPORTAL_TYPE_BIG_NOFADE	= 3 
						};

#pragma pack (push, 1)							// Alignment ausschalten
	struct TFlags {
		zUINT8			portalPoly			: 2;		// transparent portal Polygon ? (used for 3D-Culling etc.)
		zUINT8			occluder			: 1;		// outdoor-renderer: occluder-poly?
		zUINT8			sectorPoly			: 1;		// outdoor-renderer
		zUINT8			mustRelight			: 1;		// outdoor-renderer: preprocessing: poly created in lod-run
		zUINT8			portalIndoorOutdoor	: 1;		// outdoor-renderer (prepocressing)
		zUINT8			ghostOccluder		: 1;		// outdoor-renderer: ghost occluder-poly?
		zUINT8			noDynLightNear		: 1;		// for light optimisation. is not affected by any near dyn. lights (does not include lights inserted by program, e.g. torches, spells, etc.)
		//zUINT8			normalMainAxis		: 2;		// for e.g. ray/poly intersection tests
		zUINT16			sectorIndex			: 16;		// 
	} flags;
#pragma pack (pop)								// Alignment ausschalten
	// methods 
	// Flags
	
	////////////////////////////////////////////////////////
	// new interface methods, here inline for now
	////////////////////////////////////////////////////////
	zCVertex*		__fastcall			GetVertexPtr(int index)
	{
		return vertex[index];
	}

	void			__fastcall			SetVertexPtr(zCVertex* vert, int index)
	{
		vertex[index] = vert;
	}

	void			__fastcall			SetVertexPtr(zCVertex& vert, int index)
	{
		zCVertex *newVert = zNEW(zCVertex);
		*newVert = vert;
		vertex[index] = newVert;
	}
	////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////

    // MemPool-Functions
    static void *           S_AllocPointers         (int size);
    static void             S_DeletePointers        (int size, void *data);
    static zCVertFeature *  S_AllocVertFeatures     (int size);
    static void             S_DeleteVertFeatures    (int size, zCVertFeature *data);
	
	////////////////////////////////////////////////////////

	static void				S_EmptyMorphedVerts();
	static void				S_ResetMorphedVerts();
	static void				S_DeleteMorphedVerts();
	static void				S_InitMorph		   ();
	
	zBOOL			GetPortalIndoorOutdoorFlag	() const				{ return flags.portalIndoorOutdoor;	};
	void			SetPortalIndoorOutdoorFlag	(const zBOOL p)			{ flags.portalIndoorOutdoor= p;		};
	zBOOL			GetSectorFlag				() const				{ return flags.sectorPoly;			};
	void			SetSectorFlag				(const zBOOL p)			{ flags.sectorPoly= p;				};
	zBOOL			GetStaticLODPossible		();
//	zBOOL			GetLODFlag					() const				{ return flags.lodFlag;				};
//	void			SetLODFlag					(const zBOOL p)			{ flags.lodFlag= p;					};
	zBOOL			IsOccluder					() const				{ return flags.occluder;			};
	zBOOL			GetOccluder					() const				{ return flags.occluder;			};
	void			SetOccluder					(const zBOOL p)			{ flags.occluder= p;				};
	void			SetNoLightNear				(const zBOOL p)			{ flags.noDynLightNear = p;			};
	zBOOL			GetNoLightNear				()const 				{ return flags.noDynLightNear;		};
	zBOOL			GetGhostOccluder			() const				{ return flags.ghostOccluder;		};
	void			SetGhostOccluder			(const zBOOL p)			{ flags.ghostOccluder= p;			};
	zBOOL			IsPortal					() const				{ return flags.portalPoly!=zPORTAL_TYPE_NONE; };
	zBOOL			GetPortal					() const				{ return flags.portalPoly!=zPORTAL_TYPE_NONE; };
	zTPortalType	GetPortalType				() const				{ return zTPortalType(flags.portalPoly);			};
	void			SetPortalType				(const zTPortalType p)	{ flags.portalPoly = p;				};
	zDWORD			GetSectorIndex				() const				{ return flags.sectorIndex;			};
	void			SetSectorIndex				(const zWORD index)		{ flags.sectorIndex=index;			};
	void			CopyValuesInto				(zCPolygon* destPoly)	const;
	void			CopyPolyInto				(zCPolygon *poly)		const;
	zBOOL			IsNeighbourOf				(const zCPolygon *testPoly);

#ifdef MEMPOOL_HOELLER	
	zCPolygon (zCMesh *mesh);
#else
	zCPolygon ();
#endif
	~zCPolygon();
	
	zCLightMap*		GetLightmap					() const			{ return lightmap;			};
	void			SetLightmap					(zCLightMap* lm)	{ if (lightmap==lm) return; if (lightmap) lightmap->Release(); lightmap=lm; if (lm) lm->AddRef(); };
	zPOINT3			GetCenter					();
					
	void			SetMapping					(const zPOINT2& a, const zPOINT2& b, const zPOINT2& c);
	void			SetMapping					(const int vertNr, const zPOINT2& texuv);
	void			Flip						();
					
	zBOOL			CalcNormal					();
	zBOOL			CalcNormalApprox			();
	const zVEC3&	GetNormal					() const { return polyPlane.normal; };
	//void			CalcNormalMainAxis			();
					
	// Vertex		
	void			AllocVerts					(const int addNum);
	void			SetVertices					(zCVertex* a, zCVertex* b, zCVertex* c);
	void			SetVertices					(zCVertex* a, zCVertex* b, zCVertex* c, zCVertex* d, zBOOL calcNormal=TRUE);
	void			AddVertex					(zCVertex* a);
	void			AddVertexAndFeature			(zCVertex *vert, zCVertFeature *feat);
	void			SetVertex					(const int nr, zCVertex* vert);
	void			SetFeature					(const int nr, zCVertFeature* feat);
	void			RemoveVerticesAndFeatures	();										// remove, but dont delete
	zBOOL			VertPartOfPoly				(zCVertex *vert) const;
	zBOOL			EdgePartOfPoly				(zCVertex *vert1, zCVertex *vert2) const;
	zBOOL			EdgePositionsPartOfPoly		(zCVertex *vert1, zCVertex *vert2) const;

	static void		AlignPolyListToAvgPlane		(const zCArray<zCPolygon*> polyList);

	// Texture		
	void			TexTranslate				(const zPOINT2 &deltaDir);
	void			TexSetTranslation			(const zPOINT2 &pos);
	void			TexScale					(const zVALUE sx, const zVALUE sy);
	void			TexScale					(zPOINT2 &center, const zVALUE sx, const zVALUE sy);
	void			TexRotate					(zPOINT2 &center, const zVALUE angle);
	void			TexMirrorU					(const zVALUE center);
	void			TexMirrorV					(const zVALUE center);
	void			TexShearU					(const zVALUE deltak);
	void			TexShearV					(const zVALUE deltak);
					
	void			TexCorrectUV				();
	void			TexApplyPlanarMapping		(const zVALUE scaleu, const zVALUE scalev, zBOOL scaleByTexture=TRUE);
	void			TexApplyPlanarMapping		(const zPOINT3& origin,
												 const zPOINT3& up,
												 const zPOINT3& right, zBOOL scaleByTexture=TRUE);
	static void		TexApplyPlanarMapping		(const zCList<zCPolygon>& polyList,
												 const zVALUE scaleu, const zVALUE scalev, zBOOL scaleByTexture=TRUE);
					
	// Material		
	zCMaterial*		GetMaterial					() const		  { return material; };
	void			SetMaterial					(zCMaterial* mat) { 
		if (mat==material)	return;
		if (material)		material->Release(); 
		material = mat ? (zCMaterial*)mat->AddRef() : 0;
	};

	// Lighting
	static void		LightPolyList				(const zCArray<zCVobLight*>& vobLightList, zCPolygon** polyList, int numPoly, zMATRIX4 *trafoWorldToObj=0); 
	void zCCFASTCALL LightClippedPoly			(const zBOOL noStaticLightmaps); 
	void			LightDynCamSpace			(const zPOINT3& lightSourcePos, int playerLightInt);
	void			Light						(zCVobLight& light);
	void			ResetStaticLight			();
	void			SetStaticLight				(const zCOLOR lightStat);
	void			LightStatic					(zCVobLight& light, 
												 const zPOINT3& lightSourcePos, 
												 zMATRIX4& polyTrafoObjToWorld,
												 zCWorld* world);
	void			SmoothSectorBorder			(zCWorld *world);
	void			ResetLightDynToLightStat	();
	void			AddToLightDyn				(const zCOLOR lightDelta);
	void			SetLightDyn					(const zCOLOR lightDyn);
	void			SetLightStatAlpha			(const zBYTE alpha);

	//
	zVEC3			GetLightStatAtPos			(const zPOINT3& pos);	// examines lightmap if available, else vertex RGB

	zBOOL			zCCFASTCALL	CheckRayPolyIntersection2Sided	(const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& inters, zVALUE& alpha) const;
	zBOOL			zCCFASTCALL	CheckRayPolyIntersection		(const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& inters, zVALUE& alpha) const;
	zBOOL			zCCFASTCALL	CheckBBoxPolyIntersection		(const zTBBox3D& bbox3D) const;
	zBOOL			zCCFASTCALL	CheckBSpherePolyIntersection	(const zTBSphere3D& sphere3D) const;
	zBOOL			zCCFASTCALL	IsIntersecting					(zCPolygon *poly2);
	zBOOL			zCCFASTCALL	IsIntersectingProjection		(zCPolygon *poly2, const zVEC3& projNormal);
					
	zREAL			GetArea						() const;
	zREAL			GetLongestEdgeLen			() const;
	zTBBox3D		GetBBox3D					() const;
	void			GetScreenBBox2D				(zTBBox2D& outbbox2D);
	zBOOL			IsPolyTrivOutBBox2D			(const zTBBox2D& outbbox2D);
	int				ClassifyPlane				(const zTPlane& plane);
	int				ClassifyPlaneBSPBuild		(const zTPlane& plane);
	void			GetPlane					(zTPlane& plane) const	{ plane = polyPlane; };
	const zTPlane&	GetPlane					() const				{ return polyPlane; };
	void			SetPlane					(const zTPlane& plane)	{ polyPlane = plane; };
	void			SplitPoly					(const zTPlane& pplane, zCPolygon *frontPoly, zCPolygon *backPoly, zCMesh* mesh);

	// Rendering / Drawing		(uses zCCamera::activeCam)
	zBOOL			RenderPoly					(const int clipFlags=zCCamera::CLIP_FLAGS_FULL_WO_FAR);
	zBOOL			IsBackfacing				() const	{ return ((zCCamera::activeCamPos*polyPlane.normal) <= polyPlane.distance); };
	zBOOL			TransformProject			();
	zBOOL			TransformProjectLight		();
	void			DrawWire					(zCOLOR color =zCOLOR(0,255,0,255)) const;
	void			ApplyMorphing				();
//	zBOOL			IsRendered					();
//	void			SetIsRendered				();

	// Frustum-Clipping
	zBOOL	zCCFASTCALL	ClipToFrustum			(const int clipFlags=zCCamera::CLIP_FLAGS_FULL_WO_FAR);	// clip at frustum of activeCam
	zBOOL	zCCFASTCALL ClipToFrustum_Occluder  (const int clipFlags=zCCamera::CLIP_FLAGS_FULL_WO_FAR); // fast version for occluder
	zBOOL	zCCFASTCALL	ClipToPlane				(	zCVertex		**pin, 
													zCVertFeature	**pinFeat,
													int				numPinVerts, 
													zCVertex		**pout, 
													zCVertFeature	**poutFeat,
													int&			numPoutVerts, 
													const zTPlane&	pplane);

	zBOOL	zCCFASTCALL	ClipToPlane_Occluder	(	zCVertex		**pin, 
													int				numPinVerts, 
													zCVertex		**pout, 
													int&			numPoutVerts, 
													const zTPlane&	pplane);


	void			Unclip();						
	void			Unclip_Occluder();						

	static void		PrepareRendering();

	static int		GetNumClipVertScene		() { return s_numClipVertScene; };
private:
	// holds all clipped verts per scene
	static zCVertex			s_clipVertScene[zMAX_POLY_CLIP_VERTS_SCENE];
	static int				s_numClipVertScene;
							
	static zCVertFeature	s_clipFeatScene[zMAX_POLY_CLIP_VERTS_SCENE];
	static int				s_numClipFeatScene;
							
	// max num verts in scene (without sharing)
	static zCVertex			*(s_vertListScene[zMAX_POLY_VERT_LIST_SCENE]);
	static int				s_numVertListScene;
							
	static zCVertFeature	*(s_featListScene[zMAX_POLY_VERT_LIST_SCENE]);
	static int				s_numFeatListScene;
							
	// for 'active' polygon (used for speedups)
	static zCVertex			**s_actClipVert;			// 'active' polygon clipped Vertex list
	static int				s_actNumClipVert;			// 'active' polygon num clipped Vertex


	static zCArraySort<zSVertexSavedValues>		morphedVerticesList_Height;
	static zCArraySort<zSVertexSavedValues>		morphedVerticesList_Wall;
	static zCArraySort<zSFeatureSavedValues>	morphedFeatureList;
	static zCArray    <zSPolySavedValues>		morphedPolysSavedValuesList;

	// for frustum/plane clipping
	void			CopyClipFeaturesForTexAniMapping	();


	friend class zCCamera;
};

class zCBspNode;
class zCCBspNode;

class zCPortal : public zCPolygon {
    zMEMPOOL_DECLARATION        (zCPortal)

	static zCMaterial* portalDummyMaterial;
	zCBspNode*	frontBspNode;	// for Portals, FIXME: OPTIMIZE !!
	zCBspNode*	backBspNode;
	void Init() {
		frontBspNode = backBspNode = 0;
		SetPortalType (zPORTAL_TYPE_SMALL);
		lastTimeCompletely = -1;
	};
public:
	zTFrameCtr	lastTimeCompletely;

#ifdef MEMPOOL_HOELLER
	zCPortal	(zCMesh* mesh) : zCPolygon(mesh)
	{ 
		Init(); 
	};
#else
	zCPortal	() : zCPolygon()
	{ 
		Init(); 
	};
#endif

	zCPortal	(const zTPlane& plane, zCMesh* containerMesh);

	zCBspNode*	GetFrontBspNode ()					{ return frontBspNode; };
	void		SetFrontBspNode (zCBspNode* node)	{ frontBspNode = node; };
	zCBspNode*	GetBackBspNode  ()					{ return backBspNode;  };
	void		SetBackBspNode  (zCBspNode* node)	{ backBspNode  = node; };

	zCCBspNode*	GetFrontCBspNode ()					{ return (zCCBspNode*)frontBspNode; };
	void		SetFrontCBspNode (zCCBspNode* node)	{ frontBspNode = (zCBspNode*)node; };
	zCCBspNode*	GetBackCBspNode  ()					{ return (zCCBspNode*)backBspNode;  };
	void		SetBackCBspNode  (zCCBspNode* node)	{ backBspNode  = (zCBspNode*)node; };

	void RemoveFromBsp();
};

///////////////////////////////////////////////////////////////////////////
//     CAMERA - Inline implementations
///////////////////////////////////////////////////////////////////////////

inline void zCCamera::Project (const zPOINT3* const p, int& xscr, int& yscr) {
	zVALUE zrecip = zVALUE(1) / p->n[VZ];
	xscr = zFloat2Int(vpData.xcenter) + zFloat2Int((p->n[VX] * viewDistanceX) * zrecip);
	yscr = zFloat2Int(vpData.ycenter) - zFloat2Int((p->n[VY] * viewDistanceY) * zrecip);
	// temp: (für line) auf device-coords umrechnen
//		xscr = xscr * 8192 / vpData.xdim;
//		yscr = yscr * 8192 / vpData.ydim;
};
inline void zCCamera::Project (const zPOINT3* const p, zFIX& xscr, zFIX& yscr) const {
	// FIXME: int-float conv. kann durch FastFloat2Int, falls sicher, daß xscr/yscr immer >=0 !!!
	// FIXME: die Shifts bei xcenter/ycenter sind unnötig !!
	zVALUE zrecip = (zVALUE(1)*65536) / p->n[VZ];
	xscr = (zFloat2Int(vpData.xcenter) << 16) + zFloat2Int ((p->n[VX] * viewDistanceX) * zrecip);
	yscr = (zFloat2Int(vpData.ycenter) << 16) - zFloat2Int ((p->n[VY] * viewDistanceY) * zrecip);
};
inline void zCCamera::Project (const zPOINT3* const p, zVALUE& xscr, zVALUE& yscr) const {
	zVALUE zrecip = (zVALUE(1)) / p->n[VZ];
	xscr = (vpData.xcenter) + zVALUE((p->n[VX] * zVALUE(viewDistanceX)) * zrecip);
	yscr = (vpData.ycenter) - zVALUE((p->n[VY] * zVALUE(viewDistanceY)) * zrecip);
};
inline void zCCamera::Project (const zPOINT3* const p, const zVALUE zrecip, zVALUE& xscr, zVALUE& yscr) const {
	xscr = (vpData.xcenter) + zVALUE((p->n[VX] * zVALUE(viewDistanceX)) * zrecip);
	yscr = (vpData.ycenter) - zVALUE((p->n[VY] * zVALUE(viewDistanceY)) * zrecip);
};

inline void zCCamera::Project (const zPOINT3& p, const zREAL zrecip, zVEC2& posScr) const {
	posScr.n[VX]		= (vpData.xcenter) + zVALUE((p.n[VX] * zVALUE(viewDistanceX)) * zrecip);
	posScr.n[VY]		= (vpData.ycenter) - zVALUE((p.n[VY] * zVALUE(viewDistanceY)) * zrecip);
};


inline void zCCamera::Project (zCVertex* vert) const {
    Project(vert->VertexTransform());
};
inline void zCCamera::ProjectClamp (zCVertex* vert) const {
    ProjectClamp(vert->VertexTransform());
};
inline void zCCamera::ProjectClamp (zCVertex* vert, const zVALUE zinv) const {
    ProjectClamp(vert->VertexTransform(), zinv);
};

inline void zCCamera::BackProject (const int xscr, const int yscr, zPOINT3& p) const {
	// coord-trafo: screen->3d
	// Assumption : p.n[VZ] must have been set before call !
	p.n[VX] = zVALUE(xscr - zFloat2Int(vpData.xcenter)) * zVALUE(viewDistanceXInv) * p.n[VZ];
	p.n[VY] = zVALUE(zFloat2Int(vpData.ycenter) - yscr) * zVALUE(viewDistanceYInv) * p.n[VZ];
};
inline void zCCamera::BackProject (const zVALUE xscr, const zVALUE yscr, zPOINT3& p) const {
	// coord-trafo: screen->3d
	// Assumption : p.n[VZ] must have been set before call !
	p.n[VX] = zVALUE(xscr - vpData.xcenter) * zVALUE(viewDistanceXInv) * p.n[VZ];;
	p.n[VY] = zVALUE(vpData.ycenter - yscr) * zVALUE(viewDistanceYInv) * p.n[VZ];;
};













// enable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 

// ========================================================================================================

#endif