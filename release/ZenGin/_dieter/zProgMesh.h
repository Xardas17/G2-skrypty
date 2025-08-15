/******************************************************************************** 
 
     $Workfile:: zProgMesh.h          $                $Date:: 8.02.01 12:05    $
     $Revision:: 27                   $             $Modtime:: 7.02.01 3:08     $
        Author:: Hildebrandt                                                    
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Progressive Meshes
   created: 31.10.99

 * $Log: /current_work/zengin_work/_Dieter/zProgMesh.h $
 * 
 * 27    8.02.01 12:05 Hildebrandt
 * 
 * 26    5.02.01 19:13 Hildebrandt
 * 
 * 25    31.01.01 5:47 Hildebrandt
 * 
 * 24    30.01.01 5:16 Hildebrandt
 * 
 * 23    15.01.01 3:54 Hildebrandt
 * 
 * 22    20.12.00 3:01 Hildebrandt
 * 
 * 21    4.12.00 17:29 Hildebrandt
 * 
 * 20    17.11.00 1:29 Hildebrandt
 * 
 * 19    3.11.00 19:05 Hildebrandt
 * 
 * 18    25.10.00 15:06 Hildebrandt
 * 
 * 17    11.10.00 19:45 Hildebrandt
 * 
 * 16    28.09.00 19:20 Hildebrandt
 * 
 * 15    22.09.00 19:18 Hildebrandt
 * 
 * 14    22.09.00 2:37 Hildebrandt
 * 
 * 13    21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 12    6.09.00 16:30 Hildebrandt
 * 
 * 11    2.09.00 8:44 Hildebrandt
 * 
 * 10    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 9     6.07.00 13:45 Hildebrandt
 * 
 * 5     8.05.00 2:17 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 8     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 7     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 5     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     18.11.99 22:18 Hildebrandt
 * 
 * 3     16.11.99 19:49 Hildebrandt
 * 
 * 2     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 * 1     9.11.99 16:04 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revisio: 2 $ ($Modtime: 7.02.01 3:08 $)

// =======================================================================================================================

#ifndef __ZPROGMESH_H__
#define __ZPROGMESH_H__

#ifndef __ZVISUAL_H__
#include <zVisual.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif

#ifndef __ZSCANDIR_H__
#include <zScanDir.h>
#endif

class zCVertexBuffer;
class zCVertexBufferDyn;

// =======================================================================================================================

// forward declarations
class zCProgMeshBuilder;
class zCProgMeshProto;
//class zCProgMesh;
class zCRenderLight;
class zCRenderLightContainer;

// =======================================================================================================================

typedef zWORD zPMINDEX;

#define zPMINDEX_NONE				(zPMINDEX(0xFFFF))

/*
struct zTPMWedgeCache {
	zTFrameCtr					processed;
	zPMINDEX					packedIndex;
	zVEC3						color;
};

struct zTPMPosCache {
	zTFrameCtr					transformed;
	zVEC3						posCS;
	zREAL						posCSZInv;
	zVEC2						posScr;					// pro posIndex scrXY, clipFlags cachen (wird geshared)
};*/

struct zTPMWedge {
	zVEC3						normal;
	zVEC2						texUV;
	zPMINDEX					position;				// wird nicht 'remaped', wuerde man brauchen, wenn man alle Verts am Stueck beleuchten will, damit man auch direkt Zugriff auf die Pos hat..
//	zPMINDEX					activeIndex;			// wedge is active from 'activeIndex' downto it's index in wedgeList
};

struct zTPMTriangle {
	// alle [3] Eintraege werden remaped
	zPMINDEX					wedge[3];				// unique pos/normal/texUV combination
};													

struct zTPMTriangleEdges {
	zPMINDEX					edge[3];				// indexes into zTPMEdge
};													

struct zTPMEdge {
	// alle [3] Eintraege werden remaped
	zPMINDEX					wedge[2];				// indexes into zTPMWedge
};													

// ##########

struct zTPMVertexUpdate {
	zPMINDEX					numNewTri;
	zPMINDEX					numNewWedge;
//	zPMINDEX					numTrisModified;
//	zPMINDEX					firstTriModifiedIndex;
};

// - ein vertCollapse hat 0-n Veraenderungen der anderen Attribute zur Folge
// - color Eintraege werden ueber die Normalen/Wedge-Indizies indiziert (sind immer 1:1, klar pro Normal(/Pos) gibt's nur 1 color)

// =======================================================================================================================

enum zTPMRenderFlags {
	zPM_RENDER_FLAG_SW_TRAFO_VERTS		= 1,		// software transforms verts explicitly, can add effects like scale/fatness; updates vertex pos data that might have been modified outside
	zPM_RENDER_FLAG_PACK_DYNAMIC_VB		= 2,		// packs data in dynamic vertex buffer every rendering
	zPM_RENDER_FLAG_DONT_SET_TRANSFROM	= 4,		// transform has been set before, pmesh rendering does not modify it
	zPM_RENDER_FLAG_MORPH				= 8
};

enum zTPMLightingMode { 
	zPM_LIGHTING_MODE_PRELIT			= 0,
	zPM_LIGHTING_MODE_EXACT
};

class zCProgMeshProto : public zCVisual {
	zCLASS_DECLARATION (zCProgMeshProto)
public:

	static void					InitProgMeshProto			();
	static void					CleanupProgMeshProto		();
	static zBOOL				BuildProgMeshProto			(zCMesh *sourceMesh, zCProgMeshProto *destProgMesh, zCArray<int> *posListRemap=0, int buildFlags=0);
	static void					SetLODParamStrength			(const zREAL strength)	{ s_lodParamStrengthOverride= strength; };	// debug, used to override the values stored in the meshes itself, -1= use value stored within mesh, 0(noLOD)..1..x(aggressive LOD)
	static void					SetLODParamStrengthModifier	(const zREAL strength);		// range: [0;1]
	static zREAL				GetLODParamStrengthModifier	();							// range: [0;1]
	static void					InitSetupLowestLOD			();
	static void					SetMarkMeshMaterials		(zBOOL b)				{ s_markMeshMaterials		= b;		};
	static zBOOL				GetMarkMeshMaterials		()						{ return s_markMeshMaterials;			};
	static void					SetAutoSubdivEnabled		(zBOOL b)				{ s_autoSubdivEnabled		= b;		};
	static zBOOL				GetAutoSubdivEnabled		()						{ return s_autoSubdivEnabled;			};
	static zCVisual*			Load						(const zSTRING& inFileName);	// loads pmesh from disk, shares it, if already in memory

	zCProgMeshProto();

	// zCVisual interface
	zBOOL						Render				(zTRenderContext& renderContext);
	zBOOL						IsBBox3DLocal		() { return TRUE;		};				// OS / WS
	zTBBox3D					GetBBox3D			() { return bbox3D;		};				// OS / WS
	zCOBBox3D*					GetOBBox3D			() { return &obbox3D;	};				// OS
	zSTRING						GetVisualName		();
	void						DynLightVisual		(const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld=0) {};
	inline zDWORD				GetRenderSortKey	() const { return renderSortKey; };	// while rendering vobs they are sorted by their visuals sort-key; 0xF is ored in order to keep all ProgMeshProtos/VB rendered in sequence

	// traceRay, ray and report defined in objectSpace
	zBOOL						CanTraceRay			() const		{ return TRUE; };	// gives a call to TraceRay() useful infos/allowed?
	zBOOL					 	TraceRay			(	const zVEC3&		rayOrigin, 
														const zVEC3&		ray, 
														const int			traceFlags, 
														zTTraceRayReport	&report);

	// zCProgMeshProto Interface (public)
	struct zTLODRenderArgs {
		zREAL		vertPerc;
		int			numPos;					// indexes into posList
		int			numMinMorphPos;
		zREAL		morphFrac;
	};
	zBOOL	zCCFASTCALL 		RenderProgMesh		(zTRenderContext&				renderContext, 
													 int							renderFlags, 
													 zTLODRenderArgs*				lodRenderArgs=0, 
													 zCRenderLightContainer			*renderLightCont=0,
													 zREAL							fatness=0,
													 zREAL							scale=1);
	// persistence
	static zWORD				GetFileVersion		();
	virtual zBOOL				Save				(zCFileBIN& file);
	virtual zBOOL				Load				(zCFileBIN& file);

	//
	void						SetLightingMode		(const zTPMLightingMode lightingMode)	{ this->lightingMode = lightingMode; };
	zTPMLightingMode			GetLightingMode		() const								{ return lightingMode; };
	zBOOL						HasLOD				() const { return (subMeshList[0].vertexUpdates.GetNum()>1);	};
	int							GetNumVert			() const { return posList.GetNum();				};
	int							GetNumTri			() const;
	zCPolygon*					GetPolygon			(const int a_iIndex);
	zCMesh*						GetMesh				(const int a_iLODIndex);

	int							GetLowestLODNumPolys();
	zVEC3*						GetLowestLODPoly	(const int a_iPoly, zVEC3* &normal);

	void						GetLowestLODMeshLazy(zCArray<zPOINT3> &pointList);
	int							GetNumMaterial		() const		{ return numSubMeshes;			};
	zCMaterial*					GetMaterialByIndex	(int i) const	{ return subMeshList[i].material;		};
	
	// alpha testing
	virtual zBOOL				GetAlphaTestingEnabled		()	const						{ return m_bUsesAlphaTesting;	};
	virtual void				SetAlphaTestingEnabled		(const zBOOL a_btest)			{ m_bUsesAlphaTesting = a_btest; };

	// LOD controling parameters
	struct zTLODParams {
		zREAL					strength;				// Scales the (not necessarily linear) falloff of vertices with distance
		zREAL					zDisplace2;				// Z displacement for LOD distance-dependency tweaking (square)
		zREAL					morphPerc;				// >0.0 = allow morphing ; 0.0-1.0 = range of vertices to morph
		int						minVerts;				// Minimum number of vertices with which to draw a model
	};
	void						GetLODParams		(zTLODParams		&lodParams) { lodParams			= this->lodParams;	};
	void						SetLODParams		(const zTLODParams	&lodParams) { this->lodParams	= lodParams;		};
	zBOOL	zCCFASTCALL			CalcLODRenderArgs	(const zTRenderContext& renderContext, zTLODRenderArgs &lodRenderArgs);		// returns false, if mesh is collapsed down to nothing
	zBOOL	zCCFASTCALL			CalcLODRenderArgsMin(const zTRenderContext& renderContext, zTLODRenderArgs &lodRenderArgs);		// returns false, if mesh is collapsed down to nothing

	class zCSubMesh {
	public:
		 zCSubMesh();
		~zCSubMesh();

		// dataPool
		zCMaterial*						material;
		zCArrayAdapt<zTPMTriangle>		triList;
		zCArrayAdapt<zTPMWedge>			wedgeList;
		zCArrayAdapt<zREAL>				colorList;				// prelit		, indexed the same as wedgeList
		zCArrayAdapt<zPMINDEX>			triPlaneIndexList;		// can be empty!, indexed the same as triList
		zCArrayAdapt<zTPlane>			triPlaneList;			// can be empty!, for static/highest lod traceRays (, backface culling)
		zCArrayAdapt<zTPMTriangleEdges>	triEdgeList;
		zCArrayAdapt<zTPMEdge>			edgeList;
		zCArrayAdapt<zREAL>				edgeScoreList;
		
		// progressive mesh			
		zCArrayAdapt<zPMINDEX>			wedgeMap;				// (empty if no LOD) genausoviele Eintraege wie wedges, wedge auf den kollabiert wird
		zCArrayAdapt<zTPMVertexUpdate>	vertexUpdates;			// (num=1 if no LOD) numVert entries
//		zCArrayAdapt<zPMINDEX>			triModifiedList;		// (empty if no LOD) referenced by vertexUpdates, tris modified per collapse

		// static vertexBuffer
		int								vbStartIndex;			// vbNumVerts = wedgeList.GetNum()
	};

	// dataPool
	zCArrayAdapt<zPOINT3>		posList;
	zCArrayAdapt<zVEC3>			posNormalList;			// can be empty!, indexed the same as posList (for fatness)

	void						PackStaticVertexBuffers	();
	void	zCCFASTCALL			SoftwareTransformVerts	(int					renderFlags, 
														 zTLODRenderArgs		*lodRenderArgs,
														 zREAL					fatness, 
														 zREAL					scale);


protected:
	virtual ~zCProgMeshProto();			// use Release() instead!

	// zCVisual interface								
	const zSTRING*				GetFileExtension	(int i);
	zCVisual*					LoadVisualVirtual	(const zSTRING& visualName) const;

	// data
	enum						{ NUM_WEDGE_CACHE	= 4096 };	// 2048
	enum						{ NUM_POS_CACHE		= 2048 };
	enum						{ NUM_LOD_CACHE		= 4096 };
	static zTFrameCtr			s_frameCtr;
	static zPMINDEX				s_wedgeRemap		[NUM_WEDGE_CACHE];
	static zVEC3				s_posCacheList		[NUM_POS_CACHE];
	static zVEC3				s_posNormalCSList	[NUM_POS_CACHE];
	static zCArray<zWORD>		s_workIndexList;
	static int					s_subMeshRenderDir;
	static zVEC3				s_posCacheListLOD		[NUM_LOD_CACHE];
	static int					s_posCacheListLODIndices[NUM_LOD_CACHE*3];
	static int					s_posCacheCount;
	static int					s_posCacheCountLOD;
	static int					s_posCacheIndex;

	// mesh definition
	zTBBox3D					bbox3D;
	zCOBBox3D					obbox3D;

	// static vertexBuffer
	zCVertexBuffer*				vertexBufferStatic;

	//
	zCSubMesh*					subMeshList;
	int							numSubMeshes;

	// Daten komplett in 1 Block allokieren und hier nur ptr/num fuehren
	zBYTE						*dataPool;				// zCArrayAdapt memory pool
	zDWORD						dataSize;
	zREAL						avgTriArea;
	zBOOL						m_bUsesAlphaTesting;

	zBOOL						HasSubdivData			() const { return ((numSubMeshes>0) && (subMeshList[0].triEdgeList.GetNum()>0)); };

	struct zTLODRenderArgsSubMesh {
		int			numTri;
		int			numWedge;
		int			numMinMorphWedge;
		int			numSubdivEdges;
	};

	zBOOL	zCCFASTCALL			CalcLODRenderArgsSubMesh(const zTRenderContext				&renderContext, 
														 const zTLODRenderArgs				&lodRenderArgs, 
														 const zCProgMeshProto::zCSubMesh	*subMesh,
														 zTLODRenderArgsSubMesh				&lodRenderArgsSub);


private:
	static zCVertexBufferDyn*	s_vertBufferColor;
	static zCVertexBufferDyn*	s_vertBufferNormal;
	static zREAL				s_lodParamStrengthOverride;		// debug/console
	static zREAL				s_lodParamStrengthModifier;		// detail setting
	static zBOOL				s_markMeshMaterials;
	static zBOOL				s_autoSubdivEnabled;
	static zDWORD				s_classCtorCtr;
	static zBOOL				CreateDynamicVertexBuffer	();

	//
	zTLODParams					lodParams;
	zTPMLightingMode			lightingMode; 
	zDWORD						pmeshID;
	zDWORD						renderSortKey;

	// misc
	//zCProgMesh				*shadowPMesh;			// pm of this prototype, at constant lod, for shadow-rendering only


	// rendering
	void						InitStaticCaches		();
	void						ReleaseStaticCaches		();
	zREAL	zCCFASTCALL 		CalcLODRenderVertPerc	(const zTRenderContext& renderContext);
	void	zCCFASTCALL			CalcSubdiv				(int renderFlags, const zTLODRenderArgs *lodRenderArgs);
	void	zCCFASTCALL			CalcNumSubdivEdges		(zCSubMesh				*subMesh,			// in
														 const zTLODRenderArgs	*lodRenderArgs, 
														 zTLODRenderArgsSubMesh &lodRenderArgsSub);	// out
	void	zCCFASTCALL			CalcSubdivSubMesh		(zCSubMesh				*subMesh,			// in
														 zCVertexBuffer			*vertexBuffer,
														 const zTLODRenderArgs	*lodRenderArgs, 
														 zCRenderLightContainer	*renderLightCont,
														 zTLODRenderArgsSubMesh	&lodRenderArgsSub);	// out

	//
	zBOOL	zCCFASTCALL 		CheckRayPolyIntersection		(zCSubMesh *subMesh, int triIndex, const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& inters, zVALUE& alpha) const;
	zBOOL	zCCFASTCALL 		CheckRayPolyIntersection2Sided	(zCSubMesh *subMesh, int triIndex, const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& inters, zVALUE& alpha) const;
	void						CalcRenderSortKey		();

	// render
	zBOOL	zCCFASTCALL			RenderStatic			(	zTRenderContext&		renderContext, 
															int						renderFlags, 
															zTLODRenderArgs			*lodRenderArgs, 
															zCRenderLightContainer	*renderLightCont);
	zBOOL	zCCFASTCALL			RenderStaticLOD			(	zTRenderContext&		renderContext, 
															int						renderFlags, 
															zTLODRenderArgs			*lodRenderArgs, 
															zCRenderLightContainer	*renderLightCont);
	zBOOL	zCCFASTCALL			RenderDynamicLOD		(	zTRenderContext&		renderContext, 
															int						renderFlags, 
															zTLODRenderArgs			*lodRenderArgs, 
															zCRenderLightContainer	*renderLightCont,
															zREAL					fatness, 
															zREAL					scale);
	zBOOL	zCCFASTCALL			RenderDynamicSubdiv		(	zTRenderContext&		renderContext, 
															int						renderFlags, 
															zTLODRenderArgs			*lodRenderArgs, 
															zCRenderLightContainer	*renderLightCont,
															zREAL					fatness, 
															zREAL					scale);
	zBOOL	zCCFASTCALL			RenderStaticLODShadow	(	zTRenderContext&		renderContext, 
															int						renderFlags, 
															zTLODRenderArgs			*lodRenderArgs, 
															zCRenderLightContainer	*renderLightCont);


	//
	friend class  zCProgMesh;
	friend class  zCProgMeshBuilder;
	friend struct zTPMProtoDirectoryMain;
	friend struct zTPMProtoDirectorySubMesh;
	friend zBOOL  RecreateLostVBCallback_Dyn (zCVertexBuffer* vertexBuffer, void *pmProto);
};

// =======================================================================================================================

enum zTPMBuildFlags {
	zPM_BUILD_FLAG_NO_LOD					= 1,
	zPM_BUILD_FLAG_NO_TRIPLANES				= 2,
	zPM_BUILD_FLAG_NO_POSNORMALS			= 4,
	zPM_BUILD_FLAG_FORCE_SMOOTH_NORMALS		= 8,
	zPM_BUILD_FLAG_DONT_REMOVE_DEGEN_POLYS	= 16,
	zPM_BUILD_FLAG_CREATE_SUBDIV_DATA		= 32,
};

struct zTLazyMesh;

class zCProgMeshBuilder {
public:
	 zCProgMeshBuilder() {};
	~zCProgMeshBuilder() {};
	zBOOL						BuildProgMeshProto	(zCMesh *sourceMesh, zCProgMeshProto *destProgMesh, zCArray<int> *posListRemap=0, int buildFlags=0);

private:
	void						Clear				();
	void						CreatePMTriPosList	();
	void						CreateLazySubMesh	(int buildFlags, zTLazyMesh& fullMesh, zTLazyMesh& subMesh);
	void						CopySubMeshData		(zBYTE* &dataWalk, const zTLazyMesh& lazyMesh, zCProgMeshProto::zCSubMesh *subMesh);

	void						CreateFinalPMData	(int buildFlags);
	void						CalcPrelight		(zTLazyMesh &fullMesh, zTLazyMesh &subMesh);
	void						CalcPosNormals		(zTLazyMesh &fullMesh);
	void						CalcTriPlaneList	(const zTLazyMesh &fullMesh, zTLazyMesh &subMesh);
	void						CalcSubdivData		(const zTLazyMesh &fullMesh, zTLazyMesh &subMesh);
};


// =======================================================================================================================

#if 0
class zCProgMesh : public zCVisual {
	zCLASS_DECLARATION (zCProgMesh)
public:
	// zCVisual interface

protected:
	// zCVisual interface								
	const zSTRING*				GetFileExtension	(int i);
	zCVisual*					LoadVisualVirtual	(const zSTRING& visualName) const;

private:
	zCProgMeshProto				*pmProto;
								
	// state information		
	zWORD						numPos;					// dictating
	zWORD						numTri;
	zWORD						numWedge;

	// flushed when cachedOut
	zPMINDEX					*wedgeRemap;
								
	// cached ligthing			
	zVEC3						*colorList;				// cached ligthing, indexed the same as wedgeList
	zVEC3						*colorModifierList;		// for dynamic effects (e.g. blood)

	// geomorph State Data

	friend zCProgMeshProto;
};
#endif

// =======================================================================================================================

// ************************************************************************************************************
//   Deformable Mesh
// ************************************************************************************************************

class zCMeshSoftSkin : public zCProgMeshProto {
	zCLASS_DECLARATION (zCMeshSoftSkin)
public:

#pragma pack (push, 1)
	struct zTWeightEntry {					// FIXME: pack this ?	(weight and nodeIndex in 1 DWORD? => 16Byte!)
		zREAL			weight;
		zPOINT3			vertPosOS;
		zBYTE			nodeIndex;			// direct index to zCModel::nodeList	, dependency:  zCModelPrototype::ReadSoftSkinVertList (255 nodes max)
	};
#pragma pack (pop)

	typedef int zTNumWeightEntry;

	// die Vertices sind mit einer Menge von Nodes gelinkt, die kleiner sein kann, als die Menge der Nodes des Models.
	// 'nodeIndexList' enhaelt nun fuer einen jeden mit Vertices gelinkten Node einen Eintrag, der die auf einen Eintrag
	// in der NodeList des Models zeigt
	// 'nodeIndexList' mapt nun die Nodes der Ani auf die Nodes des Models:	node = zCModel::nodeList[nodeIndexList[i]]; i=die i'te benutzte Node des Meshes
	// in diesem Array sind einfach alle Nodes gesammelt, um über die Model-NodeList auf sie zugreifen zu koennen
	zCArray<int>		nodeIndexList;			// node = zCModel::nodeList [nodeIndexList[i]]
	zCArray<zCOBBox3D*>	nodeOBBList;

	struct zTNodeWedgeNormal {
		zVEC3			normal;
		int				nodeIndex;
	};
	zCArray<zTNodeWedgeNormal>	nodeWedgeNormalList;		// for bone-accurate-Lighting


	zCMeshSoftSkin();

	void					AllocVertWeightStream	(int numSVerts, int numWeightEntrys);
	void					DeleteVertWeightStream	();
	int						GetVertWeightStreamSize ();
	void					AddNumWeightEntry		(const zTNumWeightEntry& numSVert);
	void					AddWeightEntry			(const zTWeightEntry& weightEntry);
	void					BuildNodeIndexList		();

	// obb, assert: nodeIndexList is filled
	void					BuildNodeOBBList		();
	void					DeleteNodeOBBList		();
	
	void	zCCFASTCALL		SetupLowestLOD			(zTRenderContext&			renderContext, 
													 const zCArray<zMAT4*>		&nodeTrafoList, 
													 zREAL						fatness,
													 int& numPolys) ;		
							
	int						GetLowestLODNumPolys	();
	zVEC3*					GetLowestLODPoly		(const int a_iPoly, zVEC3* &normal);

	void					ResetVertWeightIterator	();
	inline zTNumWeightEntry	GetIterNumWeightEntry	();
	inline zTWeightEntry*	GetIterWeightEntry		();
	inline void				SkipIterNumWeightEntry	(int skipNum) { zERR_ASSERT (skipNum>=0); iterator	+= skipNum * sizeof (zTWeightEntry); };
						
	zBOOL	zCCFASTCALL		RenderSoftSkin			(zTRenderContext&		renderContext, 
													 const zCArray<zMAT4*>	&nodeTrafoList, 
													 zCRenderLightContainer *renderLightCont,
													 zREAL					fatness=0);
							
	// zCProgMeshProto Interface (public)
	// persistence
	static zWORD			GetFileVersion			();
	virtual zBOOL			Save					(zCFileBIN& file);
	virtual zBOOL			Load					(zCFileBIN& file);
	static void				StartSetupLowestLOD		();

protected:
	~zCMeshSoftSkin();		// use Release() instead!

private:
	zBYTE					*vertWeightStream;
	zBYTE					*iterator;
							
	zCMeshSoftSkin(const zCMeshSoftSkin&);					// disable
	zCMeshSoftSkin& operator=(const zCMeshSoftSkin&);		// disable
};

// zCMeshSoftSkin inlines

zCMeshSoftSkin::zTNumWeightEntry zCMeshSoftSkin::GetIterNumWeightEntry() 
{
	const zBYTE *old	= iterator;
	iterator			+= sizeof (zTNumWeightEntry);
	return *((zTNumWeightEntry*)old);
};

zCMeshSoftSkin::zTWeightEntry* zCMeshSoftSkin::GetIterWeightEntry () 
{
	const zBYTE *old	= iterator;
	iterator			+= sizeof (zTWeightEntry);
	return (zTWeightEntry*)old;
};

// =======================================================================================================================

// Callback class that converts model-engine source data into compiled data

class zCProgMeshConvertFileHandler : public zCScanDirFileHandler
{
public:
	zCProgMeshConvertFileHandler();

	virtual zBOOL HandleFile(const zSTRING& fname, const char* directory, _finddata_t fileinfo);	
};

// =======================================================================================================================

#endif