/******************************************************************************** 
 
     $Workfile:: zVisual.h            $                $Date:: 8.02.01 11:12    $
     $Revision:: 22                   $             $Modtime:: 8.02.01 0:19     $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Visuals
   created       : 20.2.97

 * $Log: /current_work/zengin_work/_Dieter/zVisual.h $
 * 
 * 22    8.02.01 11:12 Hildebrandt
 * Von Bert eingecheckt, da Engine-Sourcen  sonst nicht compilierbar.
 * 
 * 21    2.02.01 17:53 Moos
 * 
 * 20    1.02.01 19:58 Moos
 * 
 * 19    28.01.01 12:29 Moos
 * 
 * 18    27.01.01 19:42 Moos
 * 
 * 17    25.01.01 12:14 Moos
 * 
 * 16    25.01.01 5:07 Hildebrandt
 * 
 * 15    13.12.00 22:31 Hildebrandt
 * 
 * 14    5.12.00 15:36 Hildebrandt
 * 
 * 13    4.12.00 18:23 Moos
 * 
 * 12    17.11.00 1:29 Hildebrandt
 * 
 * 11    3.11.00 19:05 Hildebrandt
 * 
 * 10    25.10.00 15:06 Hildebrandt
 * 
 * 9     23.09.00 17:02 Hoeller
 * 
 * 8     22.09.00 0:41 Hildebrandt
 * fix for zCProgMeshProto lockup when dealing with degenerated meshes
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 6     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 3     22.02.00 2:02 Hildebrandt
 * zenGin 087d
 * 
 * 2     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 22 $ ($Modtime: 8.02.01 0:19 $)

// =========================================================================

#ifndef __ZVISUAL_H__
#define __ZVISUAL_H__

// =========================================================================

#ifndef __ZSTRING_H__
#include <zSTRING.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __Z3D_H__
#include <z3d.h>
#endif

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

#ifndef __ZBVOLUME_H__
#include <zBVolume.h>
#endif

#ifndef __ZOBJECT_H__
#include <zObject.h>
#endif

// =========================================================================

// declarations 
class zCBspTree;			// <zBSP.h>
class zCBspLeaf;			
class zCBspBase;
class zCVob;
class zCVobLight;
class zCWorld;
class zCCamera;
class zCMaterial;
class zCTexture;
class zCPolygon;
struct zTTraceRayReport;	// zWorld.h
enum zTAnimationMode;
class zCVertFeature;
class zCVertex;

// =========================================================================

enum zTVisualCamAlign{	zVISUAL_CAMALIGN_NONE=0,
						zVISUAL_CAMALIGN_YAW,
						zVISUAL_CAMALIGN_FULL,
						zVISUAL_CAMALIGN_COUNT
					 };

struct zTRenderContext {
	int					clipFlags;
	zCVob				*vob;
	zCWorld				*world;
	zCCamera			*cam;
	zREAL				distVobToCam;
	zTVisualCamAlign	visualCamAlign;
	zTAnimationMode		m_AniMode;
	zREAL				m_aniModeStrength;

	zCOLOR				hintLightingHighlightColor;			// color of highlight; alpha is strength of effect; only effective, if hintLightingHighlight enabled
	struct {
		zUINT8			hintLightingFullbright		: 1;	// fast lighting
		zUINT8			hintLightingSwell			: 1;	// soft sinus swell on lighting
		zUINT8			hintLightingHighlight		: 1;	// colored highlighting
	};
		
	void		Clear	()	{ memset (this, 0, sizeof(*this)); clipFlags=-1; };
};

///////////////////////////////////////////////////////////////////////////
//    Visual
///////////////////////////////////////////////////////////////////////////

class zENGINE_API zCVisual : public zCObject {
	zCLASS_DECLARATION	(zCVisual)
public:		
// FIXME: should be protected
	zCVisual				*nextLODVisual;
	zCVisual				*prevLODVisual;
	zREAL					lodFarDistance;
	zREAL					lodNearFadeOutDistance;		// < farDist

//	zREAL					lodScreenArea;				// ????
/*	zBOOL					bbox3DChanged;
public:						
	zBOOL					GetBBox3DChanged() const		{ return bbox3DChanged; };
	void					SetBBox3DChanged(const zBOOL b)	{ bbox3DChanged = b;	};*/
public:
	static	zCVisual*		LoadVisual					(const zSTRING& visualName);
	static	void			InitVisualSystem			();
	static	void			CleanupVisualSystem			();
														
	// zCVisual interface								
	zCVisual();								
	virtual	zBOOL			Render						(zTRenderContext& renderContext) = 0;		// TRUE=visible, FALSE=not visible
	virtual	zBOOL			IsBBox3DLocal				()				{ return TRUE; };			// OS / WS
	virtual zTBBox3D		GetBBox3D					() = 0;										// OS / WS
	virtual zCOBBox3D*		GetOBBox3D					()				{ return 0; };				// OS
	virtual zSTRING			GetVisualName				() = 0;
	virtual zBOOL			GetVisualDied				()				{ return FALSE; };
	virtual void			SetVisualUsedBy				(zCVob* vob)	{};
	virtual void			DynLightVisual				(const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld=0) {};
	virtual zDWORD			GetRenderSortKey			() const		{ return zDWORD(this);	};	// while rendering vobs they are sorted by their visuals sort-key
	// traceRay, ray and report defined in objectSpace
	virtual zBOOL			CanTraceRay					() const		{ return FALSE;			};	// gives a call to TraceRay() useful infos/allowed?
	virtual zBOOL			TraceRay					(const zVEC3&		rayOrigin, 
														 const zVEC3&		ray, 
														 const int			traceFlags, 
														 zTTraceRayReport	&report);
	virtual void			HostVobRemovedFromWorld		(zCVob* hostVob, zCWorld* hostWorld) {};	// informs the visual, called BEFFORE the actual removal
	virtual void			HostVobAddedToWorld			(zCVob* hostVob, zCWorld* hostWorld) {};	// informs the visual, called AFTER   the actual addition
	virtual const zSTRING*	GetFileExtension			(int i) { return 0; };		// (eg ".TGA"), visual class can have more than 1, return 0 indicates end of list
														
	//													
	virtual void			GetLODVisualAndAlpha		(const zREAL distToCam, zCVisual* &vis, zREAL& alpha);
	// alpha testing
	virtual zBOOL			GetAlphaTestingEnabled		()	const						{ return FALSE;	};
	virtual void			SetAlphaTestingEnabled		(const zBOOL a_btest)			{ };
	//
	void					AddNextLODVisual			(zCVisual *nextVis);
	void					AddEndLODVisual				(zCVisual *endVis);
	zCVisual*				GetNextLODVisual			() const		{ return nextLODVisual; };
	void					RemoveNextLODVisual			();
	void					SetLODFarDistance			(const zREAL v)	{ lodFarDistance = v;				};
	zREAL					GetLODFarDistance			() const		{ return lodFarDistance;			};
	void					SetLODNearFadeOutDistance	(const zREAL v)	{ lodNearFadeOutDistance= v;		};
	zREAL					GetLODNearFadeOutDistance	() const		{ return lodNearFadeOutDistance;	};

							
protected:
	// zCVisual interface								
	virtual ~zCVisual();			// use Release() instead						
	virtual zCVisual*		LoadVisualVirtual			(const zSTRING& visualName) const { return 0; };	// this method is static in nature, 'this' object only needed because static virt. are impossible

private:
	static zCArray<zCVisual*> s_visualClassList;
};


///////////////////////////////////////////////////////////////////////////
//    Visual : zCVisualAnimate
///////////////////////////////////////////////////////////////////////////

// FIXME: animation handles !

class zCVisualAnimate : public zCVisual {
	zCLASS_DECLARATION	(zCVisualAnimate)
public:
	virtual void			StartAnimation		(const zSTRING& aniName)=0;
	virtual void			StopAnimation		(const zSTRING& aniName)=0;
	virtual zBOOL			IsAnimationActive	(const zSTRING& aniName)=0;
	virtual const zSTRING*	GetAnyAnimation		()=0;
protected:
//	virtual void			StartAnyAnimation	()=0;			// useful if there is just one of them
};


///////////////////////////////////////////////////////////////////////////
//    Visual : zCDecal
///////////////////////////////////////////////////////////////////////////

class zCDecal : public zCVisual {
	zCLASS_DECLARATION	(zCDecal)
public:
	static void		CreateDecalMeshes		();
	static void		CleanupDecals			();

	// zCVisual interface								
	zBOOL			Render				(zTRenderContext& renderContext);	// TRUE=visible, FALSE=not visible
	zBOOL			IsBBox3DLocal		() { return TRUE; };				// OS / WS
	zTBBox3D		GetBBox3D			();
	zSTRING			GetVisualName		();
	void			SetVisualUsedBy		(zCVob* vob);
	void			DynLightVisual		(const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld=0);
	zDWORD			GetRenderSortKey	() const;

	//
			 zCDecal();

	zCMaterial		*decalMaterial;

	void			SetDecalDim			(zVALUE xd, zVALUE yd);
	void			GetDecalDim			(zVALUE& xd, zVALUE& yd) const		{ xd = xdim; yd = ydim; };
	void			SetDecalOffset		(const zVALUE xo, const zVALUE yo)	{ xoffset=xo; yoffset=yo; };
	void			GetDecalOffset		(zVALUE& xo, zVALUE& yo)			{ xo=xoffset; yo=yoffset; };
	void			SetTexture			(zSTRING& texName);
	void			SetTexture			(zCTexture *texture);
	void			SetDecal2Sided		(const zBOOL b)						{ decal2Sided = b; };
	zBOOL			GetDecal2Sided		() const							{ return decal2Sided; };
	void			SetIsOnTop			(const zBOOL b)						{ m_bOnTop		= b; };
	zBOOL			GetIsOnTop			() const							{ return m_bOnTop; };
	void			SetIgnoreDayLight   (const zBOOL b)						{ ignoreDayLight= b; };
	zBOOL			GetIgnoreDayLight	() const							{ return ignoreDayLight; };



	// alpha testing
	virtual zBOOL	GetAlphaTestingEnabled		()	const;
										
protected:
	virtual	~zCDecal();		// use Release() instead!

	// persistance
	virtual void	Archive				(zCArchiver &arc);
	virtual void	Unarchive			(zCArchiver &arc);

	// zCVisual interface								
	const zSTRING*	GetFileExtension	(int i);
	zCVisual*		LoadVisualVirtual	(const zSTRING& visualName) const;

private:
	static zCMesh	*decalMesh1Sided;
	static zCMesh	*decalMesh2Sided;
	zVALUE			xdim;	
	zVALUE			ydim;
	zVALUE			xoffset;
	zVALUE			yoffset;
	zBOOL			decal2Sided;
	zBOOL			ignoreDayLight;
	zBOOL			m_bOnTop;

	zCMesh*			GetDecalMesh		() { return (GetDecal2Sided() ? decalMesh2Sided : decalMesh1Sided); };
};

///////////////////////////////////////////////////////////////////////////
//     Mesh
///////////////////////////////////////////////////////////////////////////


struct zTLODEdge;

class zENGINE_API zCMesh : public zCVisual {
	zCLASS_DECLARATION	(zCMesh)
private:
	// explicity disable copy-contstructor and assignment-operator
	zCMesh			(const zCMesh&);
	zCMesh&			operator=(const zCMesh&);
public:
	//
	void			AllocVerts			(int num);
	void			AllocPolys			(int num);
	void			FitPolyVertAlloc	();
	//

	// index of pool entry (oh)
#ifdef MEMPOOL_HOELLER
	int				poolIndex;
#endif

	int				numPoly;
	int				numVert;
    int             numFeat;

protected:
	zCVertex		**vertList;
	zCPolygon		**polyList;
    zCVertFeature   **featList;

    zCVertex        *vertArray;
    zCPolygon       *polyArray;
    zCVertFeature   *featArray;

public:
	zTBBox3D		bbox3D;
	zCOBBox3D		obbox3D;
	zTFrameCtr		masterFrameCtr;

	// methods
	zCMesh();
protected:
	virtual ~zCMesh();			// use 'Release' instead.
public:

    zCVertex       *ShareVertex                      (int i) const      {zERR_ASSERT(0 <= i && i < numVert); if (vertArray) return vertArray+i; else return vertList[i] ;}
    zCPolygon      *SharePoly                        (int i) const      {zERR_ASSERT(0 <= i && i < numPoly); if (polyArray) return polyArray+i; else return polyList[i] ;}
    zCVertFeature  *ShareFeature                     (int i) const      {zERR_ASSERT(0 <= i && i < numFeat); if (featArray) return featArray+i; else return featList[i] ;}

    zCVertex       *Vertex                      (int i) const           {zERR_ASSERT(0 <= i && i < numVert && vertList); return vertList[i] ;}
    zCPolygon      *Poly                        (int i) const           {zERR_ASSERT(0 <= i && i < numPoly && polyList); return polyList[i] ;}
    zCVertFeature  *Feature                     (int i) const           {zERR_ASSERT(0 <= i && i < numFeat && featList); return featList[i] ;}

    zCVertex      *&VertexWritable              (int i)                 {zERR_ASSERT(0 <= i && i < numVert); ArraysToLists(); return vertList[i] ;}
    zCPolygon     *&PolyWritable                (int i)                 {zERR_ASSERT(0 <= i && i < numPoly); ArraysToLists(); return polyList[i] ;}
    zCVertFeature *&FeatureWritable             (int i)                 {zERR_ASSERT(0 <= i && i < numFeat); ArraysToLists(); return featList[i] ;}

    zCVertex      **VertList                    ()                      {ArraysToLists(); return vertList ;}
    zCPolygon     **PolyList                    ()                      {ArraysToLists(); return polyList ;}
    zCVertFeature **FeatList                    ()                      {ArraysToLists(); return featList ;}

    
    void            CreateListsFromArrays() const;     // initializes the pointer lists from the arrays
    void            ClearLists() const;                // clears the lists if there are arrays, too

    void            ArraysToLists() const;             // converts the arrays back to lists and deletes the arrays

	// zCVisual interface
	zSTRING			GetVisualName				()						{ return GetMeshName(); };
	void			DynLightVisual				(const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld=0);
	zBOOL			Render						(zTRenderContext& renderContext);						// TRUE=visible, FALSE=not visible
	zTBBox3D		GetBBox3D					()						{ return bbox3D;		}; 
	zCOBBox3D*		GetOBBox3D					()						{ return &obbox3D;		};
	zBOOL			CanTraceRay					() const				{ return TRUE; };	// gives a call to TraceRay() useful infos/allowed?
	zBOOL			TraceRay					(const zVEC3&		rayOrigin, 
												 const zVEC3&		ray, 
												 const int			traceFlags, 
												 zTTraceRayReport	&report);

	// Search for Mesh in list using fileName as key
	const zSTRING&	GetMeshName					() const				{ return meshName;		};
	void			SetMeshName					(const zSTRING& name)	{ meshName = name;		};
	static int		NumInList					()						{ return s_numMeshes;	};
	static zCMesh*	SearchName					(const zSTRING& name);
	static void		SetAutoConvertMeshes		(const zBOOL b)			{ s_autoConvertMeshes=b;		};
	static zBOOL	GetAutoConvertMeshes		()						{ return s_autoConvertMeshes;	};

	// iterators
	static zCMesh*	GetFirstInList				()						{ return s_meshRoot;	};
	zCMesh*			GetPrevInList				() const				{ return prev;			};
	zCMesh*			GetNextInList				() const				{ return next;			};

	//
	zBOOL			GetHasLightmaps				() const				{ return hasLightmaps;	};
	void			SetHasLightmaps				(const zBOOL b)			{ hasLightmaps=b;		};

	//
	void			RenderDecal					(zTRenderContext& renderContext, const zBOOL onTop = FALSE);
	void			RenderDecal					(const zVALUE xscr, const zVALUE yscr, const zVALUE z, const zBOOL onTop = TRUE);
	void			RenderDecalHorizon			(const zVALUE xscr, const zVALUE yscr, const zVALUE z, const zVALUE depth);
	zBOOL			RenderHorizon				(zTRenderContext& renderContext, zREAL farClipZ);
	zBOOL			Render						(zTRenderContext& renderContext, zCOLOR *vertexColor);	// a) vertexColor==0, does not light the mesh, vertex-color can be set before calling, b) vertexColor!=0, sets every vertex-color to the specified colorvalue


	// Poly/Vert Container
//	zCPolygon*		AddPoly						(zPOINT3 &a, zPOINT3 &b, zPOINT3 &c);
	zCPolygon*		AddPoly						(zPOINT3& a, zPOINT3& b, zPOINT3& c, 
												 zPOINT2& texa, zPOINT2& texb, zPOINT2& texc );
	zCPolygon*		AddPoly						(zCVertex* va, zCVertex* vb, zCVertex* vc);
	zCPolygon*		AddPoly						(zCVertex* va, zCVertex* vb, zCVertex* vc, zCVertex* vd);
	zCPolygon*		AddPoly						(zCPolygon* poly);
	zCPolygon*		AddPoly						();
	zCVertex*		AddVertex					(zCVertex* vertex);
	zCVertex*		AddVertex					(zPOINT3& a);
	zCVertex*		AddVertexSmart				(zPOINT3& a);
										
	// Deletes Poly from PolyList, but NOT it's associated vertices !!
	void			DeletePoly					(zCPolygon* poly);
	void			DeletePolyAndVerts			(const zDWORD polyListIndex);
	void			DeletePolyAndVerts			(zCPolygon* poly);
	void			RemoveDegeneratePolys		();

	// deletes everything that is contained: polys and vertices
	void			DeleteAll					();

	// Picking, Ray-Mesh/Poly Intersection
	// PickPoly :   searches for the Intersection that is nearest to rayOrigin (tests all Polys)
	// CheckRay :   stops at first Intersection encountered
	zCPolygon*		PickPolygon					(const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& intersection);
	zCPolygon*		PickPolygon					(zCCamera& cam, int xscr, int yscr, zPOINT3& intersection);
	zCPolygon*		CheckRayPolyIntersection	(const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& intersection);
	zCPolygon*		CheckRayPolyIntersection	(zCCamera& cam, int xscr, int yscr, zPOINT3& intersection);

	// Misc
	static zWORD	GetFileVersion				();
	static void		SaveMSH						(zCFileBIN& file, zCPolygon** polyList, int numPoly, zCMesh* mesh=0);
	static void     S_InitVertexMergeCache		(zCMesh* a_pMesh);
	static void     S_DeleteVertexMergeCache	();
	zBOOL			LoadMSH						(const zSTRING& fileName, zBOOL tryToShare=TRUE);
	zBOOL			LoadMSH						(zCFileBIN& file,         zBOOL tryToShare=TRUE);
	void			SaveMSH						(const zSTRING& fileName);
	void			SaveMSH						(zCFileBIN& file);
	void			ShareFeatures				();
	void			UnshareFeatures				();
	static zCMesh*	Load						(const zSTRING& meshFileName,const zBOOL a_bDontConvertToNPolys = FALSE);
	static zCMesh*	CreateQuadMesh				(const zBOOL twoSided);
	static zCMesh*	CreateTriMesh				();
	void			CalcBBox3D					(const zBOOL fastApprox=FALSE);
	void			SetDefaultPlanarMapping		(const zVALUE scaleu, const zVALUE scalev);
	void			FlipPolys					();
	void			SetMaterial					(zCMaterial *mat);
	void			CalcNormals					();
	void			ScaleXZ						(const zVALUE xs, const zVALUE zs);
	void			Scale						(const zVALUE xs, const zVALUE ys, const zVALUE zs);
	void			MergeMesh					(zCMesh *inMesh, const zMATRIX4& trafo);
	enum			zTCalcVertNormalMode		{ zMSH_VERTNORMAL_MAT, zMSH_VERTNORMAL_SMOOTH, zMSH_VERTNORMAL_FACET};
	void			CalcVertexNormals			(zTCalcVertNormalMode mode = zMSH_VERTNORMAL_MAT, zCBspTree* bspTree=0);
	void			UnSmoothMesh				();
	void			GetPolysOnPlane				(zCPolygon* rootPoly, zCList<zCPolygon>& outList, 
												 const zBOOL  onlySameMaterial=FALSE, 
												 const zVALUE tolerance=0.0F) const;
	void			GetAdjacentPolysOnPlane		(zCPolygon* rootPoly, zCList<zCPolygon>& outList, 
												 const zBOOL  onlySameMaterial=FALSE, 
												 const zVALUE tolerance=0.0F) const;
	void			TransformAllVerts			(const zMATRIX4& trafo, const zBOOL autoUpdateInternals=FALSE);		// autoUpdateInternals= normals,bbox,..
	void			Center						();
	void			CheckForMaterials			() const;
	void			SortPolysByMaterial			();
    void            SortPolysByList             (zCPolygon **list, int listLength);

	// Lighting
	void			LightMesh					(zCVobLight& light, zMATRIX4& meshTrafoObjToWorld, zCWorld* world);
	void			ResetStaticLight			();
	void			SetStaticLight				(const zCOLOR lightStat);
	void			ResetLightDynToLightStat	();
	void			AddToLightDyn				(const zCOLOR lightDelta);
	void			PrelightMesh				(zMATRIX4 *trafoObjToWorld=0);
	void			DynLightScalePrelit			(const zCOLOR scaleColor);
	void			SetLightDyn					(const zCOLOR lightDyn);
	void			SetLightStatAlpha			(const zBYTE alpha);
    void            CombineLightmaps            ();
	// LOD
	void			LODGenerate					(zCArraySort<zCPolygon*>& inPolyList, zCArraySort<zCPolygon*>& outPolyList);
	static void		ConvertTrisToNPolys			(zCPolygon **inPolyList, int inPolyNum, zCMesh* homeMesh, const zBOOL onlySectorPolys=FALSE);
	void			ConvertTrisToNPolys			()		{ ArraysToLists(); zCMesh::ConvertTrisToNPolys (polyList, numPoly, this); };

	// alpha testing
	virtual zBOOL	GetAlphaTestingEnabled		()	const						{ return m_bUsesAlphaTesting;	};
	virtual void	SetAlphaTestingEnabled		(const zBOOL a_btest)			{ m_bUsesAlphaTesting = a_btest; };

protected:
	// zCVisual interface								
	const zSTRING*	GetFileExtension			(int i);
	zCVisual*		LoadVisualVirtual			(const zSTRING& visualName) const;

private:

#ifdef COMPILING_SPACER
	public:
	zSTRING			pathToMesh;
	private:
#endif
	static zBOOL	s_autoConvertMeshes;
	static zBOOL	s_usesVertexCache;
	static int		s_numMeshes;
	static zCMesh	*s_meshRoot;
	static zCArraySort<zCVertex*>	s_vertexCache;
	zCMesh			*next;
	zCMesh			*prev;
	zSTRING			meshName;					// e.g. "sword.3ds", filename, with extension, no path
	zBOOL8			hasLightmaps;
	zBOOL			m_bUsesAlphaTesting;

	int				numVertAlloc;
	int				numPolyAlloc;

	zCVertex*		VertexInMesh				(const zPOINT3& v);
	void			LODRecalcEdge				(zTLODEdge& edge, zCArraySort<zCPolygon*>& inPolyList);
	static zBOOL	CheckTexUVOnPlane			(const zCArray<zCVertex*> &vertList, const zCArray<zCVertFeature> &featList);	// helper for ConvertTrisToNPolys
};

//------------------------------------------------------------------------

#endif
    