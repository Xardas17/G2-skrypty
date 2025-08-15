/******************************************************************************** 
 
     $Workfile:: zWorld.h             $                $Date:: 24.04.01 17:34   $
     $Revision:: 33                   $             $Modtime:: 23.04.01 18:32   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ World (Scene Management)
   created       : 1.8.97

 * $Log: /current_work/ZenGin/_Dieter/zWorld.h $
 * 
 * 33    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 32    9.02.01 2:35 Hildebrandt
 * 
 * 31    2.02.01 5:24 Hildebrandt
 * 
 * 30    15.01.01 19:36 Hildebrandt
 * 
 * 29    8.01.01 19:20 Hildebrandt
 * 
 * 28    8.01.01 17:56 Hildebrandt
 * 
 * 27    4.12.00 18:23 Moos
 * 
 * 26    7.11.00 17:24 Hildebrandt
 * 
 * 25    3.11.00 17:50 Hildebrandt
 * 
 * 24    26.10.00 17:45 Speckels
 * 
 * 23    26.10.00 2:23 Hildebrandt
 * 
 * 22    25.10.00 15:07 Hildebrandt
 * 
 * 21    29.09.00 21:20 Moos
 * 
 * 20    21.09.00 20:58 Moos
 * 
 * 19    29.08.00 18:22 Hildebrandt
 * zCZone::Process..() gets called even if there is just a default zone in
 * the world
 * 
 * 18    23.08.00 17:31 Hildebrandt
 * zengin 0.92i
 * 
 * 17    21.08.00 17:18 Hildebrandt
 * 
 * 16    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 15    31.07.00 19:18 Speckels
 * 
 * 14    21.07.00 14:28 Hildebrandt
 * 
 * 13    6.07.00 13:45 Hildebrandt
 * 
 * 7     8.05.00 20:25 Hildebrandt
 * 
 * 6     8.05.00 18:17 Hildebrandt
 * zenGin 089g
 * 
 * 5     8.05.00 5:30 Hildebrandt
 * zenGin 089g
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 11    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 10    18.02.00 1:39 Hildebrandt
 * 
 * 9     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 7     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 6     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     17.11.99 19:06 Hildebrandt
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 33 $ ($Modtime: 23.04.01 18:32 $)


#ifndef __ZWORLD_H__
#define __ZWORLD_H__

#ifndef __ZOBJECT_H__
#include <zObject.h>
#endif

#ifndef __ZBSP_H__
#include <zBsp.h>
#endif

#ifndef __ZVOB_H__
#include <zVob.h>
#endif

#ifndef __ZZONE_H__
#include <zZone.h>
#endif

class zCWayNet;				// <zWayNet.h>
class zCPlayerGroup;
class zCVob;
class zCViewProgressBar;	// <zViewProgressBar.h>
class zCSession;
class zCCSPlayer;
class zCRayCache;

///////////////////////////////////////////////////////////////////////////
//     WORLD
///////////////////////////////////////////////////////////////////////////

// basic callback-class
class zCCallback {
public:	
};

// callback-class for vobs
class zCVobCallback : public zCCallback {
public:
	virtual void HandleVob(zCVob* vob, void *callbackData)=0;
};

// callback-class for perFrame/perRender activities
class zCWorldPerFrameCallback : public zCCallback {
public:
	virtual void DoWorldPerFrameCallback (zCWorld *world, zCCamera *camera)=0;
};

struct zTTraceRayReport {
	zBOOL		foundHit;
	zCVob		*foundVob;
	zCPolygon	*foundPoly;			//									USE: zTRACERAY_STAT_POLY
	zVEC3		foundIntersection;	// world-space
	zVEC3		foundPolyNormal;	// world-space						USE: zTRACERAY_POLY_NORMAL
	zCVertex	*foundVertex;		// only filled by method 'PickVob', only static geometry

	void		Clear()				{ memset (this, 0, sizeof(*this));  };
};

enum zTTraceRayFlags {
		// Flags for vobs (exclusive)
		zTRACERAY_VOB_IGNORE_NO_CD_DYN		= 1<<0,		// ignores vobs, if they have not set the flag for dynamic collision
		zTRACERAY_VOB_IGNORE				= 1<<1,		// ignores vobs
		zTRACERAY_VOB_BBOX					= 1<<2,		// only tests vob bounding boxes	(always available)
		zTRACERAY_VOB_OBB					= 1<<3,		// only tests vob oriented bbox		(if available)
//		zTRACERAY_VOB_POLY		 		 * DEFAULT *	// tests vob's polys				(if available)

		// Flags for static world (exclusive)
		zTRACERAY_STAT_IGNORE				= 1<<4,		// ignores static world geometry
//		zTRACERAY_STAT_INTERS			 * DEFAULT *	// reports poly intersections
		zTRACERAY_STAT_POLY					= 1<<5,		// reports poly intersections & pointer to poly
		zTRACERAY_STAT_PORTALS				= 1<<6,		// tests static world geometry portals (e.g. invisible/walkthru)

		// Misc Flags (not exclusive)
		zTRACERAY_POLY_NORMAL				= 1<<7,		// reports normals of found polys		(VOB/STAT, worldSpace)
		zTRACERAY_POLY_IGNORE_TRANSP		= 1<<8,		// ignores transparent polys			(VOB/STAT) [material-alpha or texture-alphaChannel]
		zTRACERAY_POLY_TEST_WATER			= 1<<9,		// tests water polys					(VOB/STAT)
		zTRACERAY_POLY_2SIDED				= 1<<10,	// reports front and backfacing polys	(VOB/STAT)
		zTRACERAY_VOB_IGNORE_CHARACTER		= 1<<11,	// ignores vobs that are characters 

//		zTRACERAY_NEARESTHIT			 * DEFAULT *	// searches for the nearest intersection to rayOrigin
		zTRACERAY_FIRSTHIT					= 1<<12,	// INTERNAL; stops at the first intersection: LOS existance problem (faster)
		zTRACERAY_VOB_TEST_HELPER_VISUALS	= 1<<13,	// INTERNAL; tests against helper visuals (for editor/spacer)
		zTRACERAY_VOB_IGNORE_PROJECTILES	= 1<<14,
};

// TraceRay Defaults:
//
// polys: - give:		intersection, test AlphaPolys
//		  - don't give: poly (static only), polyNormal, PortalPolys, WaterPolys, noCollDetMaterial-Polys
//
// vobs:  - test:		bbox=>obb=>Poly, characters, vobs with any CD-Flags
//		  - don't test: vobs' helperVisuals (e.g. vobLights)

enum zTWld_RenderMode { zWLD_RENDER_MODE_VERT_LIGHT,		
						zWLD_RENDER_MODE_LIGHTMAPS  };		

class zCPatchMap;		// zWorld.cpp
class zCSkyControler;	// zSky.h


/*	------------------------------------------------------------------

	class zCWorld

	26.07.00	[Speckels]
				Session ist der Welt nun bekannt: Get/SetOwnerSession
				CutscenePlayer hinzugefügt
				Aufruf csPlayer->Process in Render-Methode eingebunden

	------------------------------------------------------------------ */


class zENGINE_API zCWorld : public zCObject {
	zCLASS_DECLARATION	(zCWorld)

	// explicity disable copy-contstructor and assignment-operator
	zCWorld				(const zCWorld&);
	zCWorld&			operator=(const zCWorld&);
public:

		
	static zBOOL		GetFadeOutFarVertices	()									{ return s_bFadeOutFarVerts;};
	static void			SetFadeOutFarVertices   (const zBOOL a_bFadeOut)			{ s_bFadeOutFarVerts = a_bFadeOut;};
	static zBOOL		GetWaveAnisEnabled		()									{ return s_bWaveAnisEnabled;		};
	static void			SetWaveAnisEnabled		(const zBOOL a_bWaveEn)				{ s_bWaveAnisEnabled = a_bWaveEn;	};
	static zBOOL		GetShowTextureStats		()									{ return showTextureStats;	};
	static void			SetShowTextureStats		(const zBOOL b)						{ showTextureStats=b;		};
	static zBOOL		S_GetEnvMappingEnabled	()									{ return s_bEnvMappingEnabled;		};
	static void			S_SetEnvMappingEnabled	(const zBOOL a_bEn)					{ s_bEnvMappingEnabled = a_bEn;	};
	static zBOOL		S_GetAmbientVobsEnabled ()									{ return s_bAmbientVobsEnabled;		};
	static void			S_SetAmbientVobsEnabled (const zBOOL a_bEn)					{ s_bEnvMappingEnabled = a_bEn;	};
	

	static zBOOL		S_GetAlternateRenderOrder()									{ return s_bAlternateRenderOrder;	};
	static void			S_SetAlternateRenderOrder(const zBOOL b)					{ s_bAlternateRenderOrder = b;		};

	
	// dynamic part of the world
	zCTree<zCVob>		globalVobTree;				// every vob in the world is registered here

	// methods
	zCWorld	();
	enum				zTWorldLoadMode			{	zWLD_LOAD_GAME_STARTUP,			// dyn + stat, remove levelCompos
													zWLD_LOAD_GAME_SAVED_DYN,		// dyn       , remove levelCompos
													zWLD_LOAD_GAME_SAVED_STAT,		//       stat, remove levelCompos
													zWLD_LOAD_EDITOR_COMPILED,		// dyn + stat, deactivate levelCompos
													zWLD_LOAD_EDITOR_UNCOMPILED,	// dyn       , activate   levelCompos
													zWLD_LOAD_MERGE };
	enum				zTWorldSaveMode			{	zWLD_SAVE_GAME_SAVED_DYN,		// dyn
													zWLD_SAVE_EDITOR_COMPILED,		// dyn + stat
													zWLD_SAVE_EDITOR_UNCOMPILED,	// dyn
													zWLD_SAVE_COMPILED_ONLY			//       stat
												};
	enum				zTWorldLoadMergeMode	{	zWLD_LOAD_MERGE_ADD,					// add whole independent vobSubtree
													zWLD_LOAD_MERGE_REPLACE_ROOT_VISUAL	};	// the visual of a specified vob is replaced by first vob visual from file, childVobs from file are added	

	virtual zBOOL		LoadWorld				(const zSTRING& fileName, const zTWorldLoadMode loadMode);
	virtual zBOOL		SaveWorld				(const zSTRING& fileName, const zTWorldSaveMode saveMode, 
												 const zBOOL	writeBinary=FALSE, const zBOOL _saveLevelMesh=FALSE);
	// paramVob: in mergeMode 'ADD' this is the parent for the inserted subtree, in mergeMode 'REPLACE' this vob is replaced by the first vob in subtree
	virtual zCVob*		MergeVobSubtree			(const zSTRING& fileName, zCVob* paramVob=0, zTWorldLoadMergeMode mergeMode=zWLD_LOAD_MERGE_ADD); // result= first inserted vob
	virtual zBOOL		SaveVobSubtree			(const zSTRING& fileName, zCVob* vob, 
												 const zBOOL	writeBinary=FALSE, const zBOOL _saveLevelMesh=FALSE);
	//
	void				SetProgressBar			(zCViewProgressBar *progressBar)	{ this->progressBar=progressBar;};	// progressbar that is updated during world saves/loads
	zCViewProgressBar*	GetProgressBar			() const							{ return progressBar;			};

	void				SetOwnerSession			(zCSession* owner);
	zCSession*			GetOwnerSession			();

	zCCSPlayer*			GetCutscenePlayer		() const { return csPlayer; };

	//
	virtual void		DisposeWorld			();										// dyn&stat, vobs&bsp
	virtual zBOOL		DisposeVobs				(zCTree<zCVob> *node=0);				// releases (!) every vob in the world, resets waynet, resets cutscenePlayer
	virtual zBOOL		DisposeVobsDbg			(zCTree<zCVob> *node=0);				// releases (!) every vob in the world, resets waynet, resets cutscenePlayer
	virtual void		DisposeStaticWorld		();										// deletes bsp & level-mesh
	void				Render					(zCCamera& cam);
	void				MoveVobs				();										// was private: only public use for pre caching data on level startup

	void				AdvanceClock			(const zREAL timeDeltaSec=-1);			// -1 means: use realtime
	zSTRING&			GetName					()				{ return m_strlevelName;	};

	// debug helper
	void				PrintStatus				();										// debug
	void				PrintGlobalVobTree		(zCTree<zCVob>* node=0, int indent=0);	// debug
	void				PrintActiveVobs			();										// debug
	zBOOL				GetShowZonesDebugInfo	() const		{ return showZonesDebugInfo;};
	void				SetShowZonesDebugInfo	(const zBOOL b) { showZonesDebugInfo=b;		};
	zBOOL				GetShowTraceRayLines	() const		{ return showTraceRayLines;	};
	void				SetShowTraceRayLines	(const zBOOL b) { showTraceRayLines=b;		};
	zBOOL				GetShowWaynet			() const 		{ return showWaynet;		};
	void				SetShowWaynet			(const zBOOL on){ showWaynet= on;			};
	const zTBBox3D&		GetBBox3DWorldStatic	()				{ return GetBspTree()->GetRoot()->bbox3D; };
	zBOOL				GetIsInventoryWorld		() const		{ return m_bIsInventoryWorld;};
	void				SetIsInventoryWorld		(const zBOOL b) { m_bIsInventoryWorld = b	;}   ;

	//
	zTFrameCtr			GetMasterFrameCtr		() const { return masterFrameCtr; };
	void				UpdateZone				(zCZone* zone);
	zBOOL				ShouldAddThisVobToBsp	(zCVob * vob) const;	// (filters zones)
						
	// Bsp				
	void				CompileWorld			(const zTBspTreeMode& bspTreeMode, 
												 const zREAL optimize=zREAL(1.0F), 
												 const zBOOL removeLevelCompos=TRUE, 
												 const zBOOL editorMode=FALSE,			// for Spacer, enables texturing/meshSaving in compiled-Mode, 
												 zCArray<zCPolygon*> *leakPolyList=0);
	zBOOL				IsCompiled				() const { return compiled;				};
	zBOOL				IsCompiledEditorMode	() const { return compiledEditorMode;	};
	zCBspTree*			GetBspTree				()		 { return &bspTree; };
	zBOOL				LoadBspTree				(zFILE& file, zBOOL skipThisChunk=FALSE);
	void				SaveBspTree				(zFILE& file);
	void				SaveBspTreeMesh3DS		(const zSTRING& fileName);
	void				DebugMarkOccluderPolys	();
	
	zCSkyControler*		GetActiveSkyControler		();
	void				SetSkyControlerIndoor		(zCSkyControler* s);
	void				SetSkyControlerOutdoor		(zCSkyControler* s);
							
	zCWayNet*			GetWayNet					() const			{ return wayNet;		};

	// VOBs
	//
	// ACHTUNG: Vobs sollten immer über die folgenden Methoden manipuliert werden,
	// und _nicht_ direkt über den 'globalVobTree'. 
	zBOOL				GetDrawVobBBox3D			()					{ return bspTree.GetDrawVobBBox3D();	};
	void				SetDrawVobBBox3D			(zBOOL b)			{ bspTree.SetDrawVobBBox3D (b);			};
	virtual zCTree<zCVob>* AddVobAsChild			(zCVob *childVob, zCTree<zCVob>* parentVob);	// vob/vobSubtree is inserted into world, vobSubtrees(torches etc) are handled correctly
	zCTree<zCVob>*		AddVobAsChild				(zCVob *childVob, zCVob* parentVob);
	zCTree<zCVob>*		AddVob						(zCVob *vob);
	zCTree<zCVob>*		AddVobRelease				(zCVob *vob)						{ zCTree<zCVob>* res = AddVob(vob); vob->Release(); return res; };	// convenience method for 'add & forget' a vob to the world
	zCTree<zCVob>*		AddVobAsChildRelease		(zCVob *childVob, zCVob* parentVob) { zCTree<zCVob>* res = AddVobAsChild(childVob, parentVob); childVob->Release(); return res; };	// convenience method for 'add & forget' a vob to the world
	virtual void		RemoveVob					(zCVob *vob);									// childs get childs of vob's parent
	void				RemoveVob					(zCTree<zCVob> *vobNode);
	virtual void		RemoveVobSubtree			(zCVob *vob);									// childs are removed from world, but stay connected with vob
	void				RemoveVobSubtree			(zCTree<zCVob> *vobNode);
	virtual void		MoveVobSubtreeTo			(zCVob *vobSubtree, zCTree<zCVob> *destParent);	// everything stays within the world but changes parent
	void				MoveVobSubtreeTo			(zCVob *vobSubtree, zCVob *destParent);
	void				MoveVobSubtreeToWorldSpace	(zCVob *vobSubtree);
	void				RemoveVobFromLists			(zCVob* vob);
	void				TraverseVobTree				(zCVobCallback &callback, void *callbackData=0, zCTree<zCVob>* vobNode=0);

	// These callbacks are called within zCWorld::Render(), after the frame has been rendered
	void				RegisterPerFrameCallback	(zCWorldPerFrameCallback *perFrameCallback);
	void				UnregisterPerFrameCallback	(zCWorldPerFrameCallback *perFrameCallback);
	zBOOL				IsRegisteredPerFrameCallback(zCWorldPerFrameCallback *perFrameCallback) { return perFrameCallbackList.IsInList (perFrameCallback); };

	// Ray-Tracing, TRUE=foundHit, Results => traceRayReport
	zTTraceRayReport	traceRayReport;
	zBOOL	zCCFASTCALL	PickScene					(zCCamera& cam, int xscr, int yscr, zREAL rayLength=-1);	// rayLength specifies how far to pick into the scene, -1 picks to infinity
	zBOOL	zCCFASTCALL	TraceRayFirstHit			(const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList	, int traceFlags);
	zBOOL	zCCFASTCALL	TraceRayFirstHit			(const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob						, int traceFlags);
	zBOOL	zCCFASTCALL	TraceRayNearestHit			(const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList	, int traceFlags);
	zBOOL	zCCFASTCALL	TraceRayNearestHit			(const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob						, int traceFlags);

	zBOOL	zCCFASTCALL	TraceRayFirstHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList	, int traceFlags, zCRayCache *cache);
	zBOOL	zCCFASTCALL	TraceRayFirstHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob						, int traceFlags, zCRayCache *cache);
	zBOOL	zCCFASTCALL	TraceRayNearestHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList	, int traceFlags, zCRayCache *cache);
	zBOOL	zCCFASTCALL	TraceRayNearestHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob						, int traceFlags, zCRayCache *cache);

	// FIXME:	Wozu ist das gut ???
	virtual zCPlayerGroup* GetPlayerGroup		() { return 0; };

	// vob related
	void				AddActiveVob			(zCVob* vob) { if (!activeVobList.IsInList(vob)) activeVobList.Insert (vob); };
	void				RemoveActiveVob			(zCVob* vob) { activeVobList.Remove (vob); };
						
	virtual zCVob*		SearchVob				(zCVob *vob				, zCTree<zCVob>* vobNode=0);
	virtual zCVob*		SearchVobByID			(const zTVobID	vobID	, zCTree<zCVob>* vobNode=0);
	virtual zCVob*		SearchVobByName			(const zSTRING& vobName);
	virtual void		SearchVobListByName		(const zSTRING& vobName	, zCArray<zCVob*>& resultVobList);	// collects all vobs with the same name, list is not cleared!
	virtual void		SearchVobListByClass	(zCClassDef* classDef	, zCArray<zCVob*>& resultVobList, zCTree<zCVob>* vobNode=0);
	virtual void		SearchVobListByBaseClass(zCClassDef* baseClassDef, zCArray<zCVob*>& resultVobList, zCTree<zCVob>* vobNode=0);	// collects all vobs that are of or derived from 'baseClassDef'
	void				CollectVobsInBBox3D		(zCArray<zCVob*>& resVobList, const zTBBox3D& inbbox3D) { bspTree.GetRoot()->CollectVobsInBBox3D(resVobList,inbbox3D); };
	zCArray<zCVob*>*	GetLastRenderVobList	() { return bspTree.GetLastRenderVobList(); };
	void				SearchZoneListByClass	(zCClassDef* classDef	, zCArray<zCZone*>& resultVobList);
	zCZone*				SearchZoneDefaultByClass(zCClassDef* classDef);

	void				SetVobFarClipZ			(const zREAL z)				{ vobFarClipZ = zMax (zVALUE(0),z);				};
	zREAL				GetVobFarClipZ			() const					{ return vobFarClipZ * vobFarClipZScalability;	};
	void				SetVobFarClipZScalability(const zREAL zscaler)		{ vobFarClipZScalability = zscaler;				};		// 0..1..x (1 being default)
	zREAL				GetVobFarClipZScalability() const					{ return vobFarClipZScalability;				};

	// lighting
	enum zTStaticWorldLightMode {	
		zWLD_LIGHT_VERTLIGHT_ONLY,
		zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_LOW_QUAL,
		zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL,
		zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_HI_QUAL
	};
	void				GenerateStaticWorldLighting	(const zTStaticWorldLightMode& lightMode=zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL, zTBBox3D *updateBBox3D=0);	// set 'updateBBox3D' if you want to limit the light calculation area (for fastspacer light previews)
	void				GenerateStaticVertexLighting();
	void				GenerateLightmaps			(const zTStaticWorldLightMode& lightMode=zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL, zTBBox3D *updateBBox3D=0);	

	zTWld_RenderMode	GetWorldRenderMode			() const								{ return worldRenderMode; };
	void				SetWorldRenderMode			(const zTWld_RenderMode& rmode)			{ worldRenderMode = rmode; bspTree.worldRenderMode=rmode;};
	zBOOL				IsOutdoor					() const { return bspTree.GetBspTreeMode()==zBSP_MODE_OUTDOOR; };

protected:
	virtual ~zCWorld	();							// use Release() instead!
	// persistance
	virtual void		Archive						(zCArchiver &arc);
	virtual void		Unarchive					(zCArchiver &arc);

	//
	// Is called for every vob that is addedTo/removedFrom the world, opportunity for derived classes to plug in own code, 
	// called AFTER the actual addition. Derived implementations should call the base class methods.
	virtual void		VobAddedToWorld				(zCVob *vob);			// called AFTER the actual addition
	virtual void		VobRemovedFromWorld			(zCVob *vob);			// called BEFFORE the actual removal

	// debug
	virtual void		RenderWaynet				(zCCamera *camera);

protected:
	// Lighting
	// VobLight
	void				LightWorldStaticUncompiled	(zCTree<zCVob>* node);
	void				LightWorldStaticCompiled	();
						
	// Lightmaps		
	// common			
	zBOOL				LightingTestRay				(const zPOINT3& start, const zPOINT3& end, zVEC3& inters, zCPolygon* &hitPoly);
	zBOOL				GetSurfaceLightmapBBox2D	(zCArray<zCPolygon*>& surface, zTBBox2D& lmBox, int realDim[2]);
	zCPatchMap*			GeneratePatchMapFromSurface (zCArray<zCPolygon*>& surface);
	void				GenerateLightmapFromPatchMap(zCPatchMap *patchMap);
						
	void				LightPatchMap				(zCPatchMap *patchMap);
	void				GenerateLightmapsRaytracing ();
						
	void				GenerateSurfaces			(const zBOOL doRaytracing, zTBBox3D *updateBBox3D);
						
	// radiosity		
	void				GenerateLightmapsRadiosity	(zTBBox3D *updateBBox3D);
	void				MakeTransfers				();

protected:
	static zTWorldLoadMode		s_worldLoadMode;		// FIXME: make non-static ?
	static zTWorldSaveMode		s_worldSaveMode;
	static zTWorldLoadMergeMode	s_worldMergeMode;

	static zTWorldLoadMode		GetWorldLoadMode	()									{ return s_worldLoadMode; };

	//
	void	zCCFASTCALL			ArcTraverseVobs			(zCArchiver& arc, zCTree<zCVob>* node, const zBOOL firstVob=TRUE);
	void	zCCFASTCALL			UnarcTraverseVobs		(zCArchiver& arc, zCTree<zCVob>* parent=0);
								
	//							
	void						UpdateVobTreeBspDependencies (zCTree<zCVob>* node=0);

private:
	// private Data
	static zBOOL				s_bFadeOutFarVerts;
	static zBOOL				s_bWaveAnisEnabled;
	static zBOOL				s_bAlternateRenderOrder;
	static zBOOL				s_bEnvMappingEnabled;
	static zBOOL				s_bAmbientVobsEnabled;
	static zBOOL				showTextureStats;			// debug


	zCSession*					ownerSession;
	zCCSPlayer*					csPlayer;
								
	zSTRING						m_strlevelName;
	zBOOL						compiled;
	zBOOL						compiledEditorMode;
	zBOOL						traceRayIgnoreVobFlag;
	zBOOL						m_bIsInventoryWorld;
	zTWld_RenderMode			worldRenderMode;
	zCWayNet					*wayNet;
	zTFrameCtr					masterFrameCtr;
	zREAL						vobFarClipZ;
	zREAL						vobFarClipZScalability;		// 0..1 dynamically scales vobFarClipZ
	zCArray<zCVob*>				traceRayVobList;			// traceRay methods use this (optm.)
	zCArray<zCVob*>				traceRayTempIgnoreVobList;	// traceRay methods use this (optm.)
	zBOOL						renderingFirstTime;
	zBOOL						showWaynet;					// debug
	zBOOL						showTraceRayLines;			// debug
	
	zCViewProgressBar			*progressBar;
	zDWORD						unarchiveFileLen;			// for progress bar
	zDWORD						unarchiveStartPosVobtree;	// for progress bar
	int							numVobsInWorld;
	zCArray<zCWorldPerFrameCallback*> perFrameCallbackList;

	// sky/weather/daylight 
	zCSkyControler				*skyControlerIndoor;
	zCSkyControler				*skyControlerOutdoor;
	zCSkyControler				*activeSkyControler;
								
	// zones					
	zCArray<zCZone*>			zoneGlobalList;				// list of zones contained in this world, default zones in front, others in back of list
	zCArraySort<zCZone*>		zoneActiveList;
	zCArraySort<zCZone*>		zoneLastClassList;
	zCVobBBox3DSorter<zCZone>	zoneBoxSorter;
	zCVobBBox3DSorter<zCZone>::zTBoxSortHandle	zoneActiveHandle;
	zBOOL						addZonesToWorld;
	zBOOL						showZonesDebugInfo;

	// static part of the world
	zCCBspTree					*cbspTree;						// construction Bsp
	zCBspTree					bspTree;						// real-thing bsp
															
	// dynamic part of the world							
//	zCArray<zCVob*>				globalVobList;					// sorted by id
	zCArray<zCVob*>				activeVobList;					// vobs that are moving(physics) and/or thinking(ai)
	zCArray<zCVob*>				walkList;						// 
	enum						{ zNUM_VOB_HASH	= 2048 };
	zCArray<zCVob*>				vobHashTable[zNUM_VOB_HASH];	// for fast vob searching by name
								
	// zones					
	static int					ActiveZoneListCompare		(const void* ele1,const void* ele2);
	void						ProcessZones				();
	void						AddZone						(zCZone* zone);
	void						RemoveZone					(zCZone* zone);
	void						RemoveAllZones				();
	zBOOL						GetAddZonesToWorld			() const		{ return addZonesToWorld;	};
	void						SetAddZonesToWorld			(const zBOOL b) { addZonesToWorld=b;		};
	void						ShowZonesDebugInfo			();
	void						ShowTextureStats			();
								
	// Lighting					
	zVEC3						GetPhongNormal				(zCPolygon *poly, const zPOINT3 &pos);
								
	//														
	zBOOL						TraverseBsp					(zCCBspTree *bspTree, zCTree<zCVob> *node, const zBOOL removeLevelCompos);
	zBOOL						TraverseBspAddVobsToMesh	(zCCBspTree *bspTree, zCTree<zCVob> *node);
	void						RemoveVobSubtree_r			(zCTree<zCVob>* node, zBOOL firstVob);
	void						InsertVobHashTable			(zCVob*	vob);
	void						RemoveVobHashTable			(zCVob*	vob);
	zCVob*						SearchVobHashTable			(const zSTRING& vobName);
	void						SearchVobListHashTable		(const zSTRING& vobName, zCArray<zCVob*>& resultVobList);
	zDWORD						GetVobHashIndex				(zCVob *vob);
	zDWORD						GetVobHashIndex				(const zSTRING& name);
	void						ResetCutscenePlayer			();		
								
	void						MakeVobLightingDirty		();

	friend class zCVob;
};

#endif