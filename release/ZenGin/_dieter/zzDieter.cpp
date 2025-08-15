/******************************************************************************** 
 
     $Workfile:: zzDieter.cpp         $                $Date:: 22.05.01 18:45   $
     $Revision:: 54                   $             $Modtime:: 24.04.01 0:19    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zzDieter.cpp $
 * 
 * 54    22.05.01 18:45 Edenfeld
 * 
 * 53    19.03.01 21:31 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 52    18.03.01 18:49 Edenfeld
 * Demo Geschichten
 * 
 * 51    14.02.01 7:28 Hildebrandt
 * 
 * 50    12.02.01 23:10 Hildebrandt
 * 
 * 49    5.02.01 22:20 Speckels
 * 
 * 48    1.02.01 19:40 Speckels
 * 
 * 47    1.02.01 19:36 Hildebrandt
 * 
 * 46    30.01.01 19:10 Speckels
 * 
 * 45    30.01.01 16:58 Speckels
 * 
 * 44    30.01.01 10:27 Moos
 * 
 * 43    29.01.01 1:36 Hildebrandt
 * 
 * 42    28.01.01 19:08 Speckels
 * 
 * 41    28.01.01 19:00 Speckels
 * 
 * 40    27.01.01 14:59 Speckels
 * 
 * 39    25.01.01 1:21 Hildebrandt
 * 
 * 38    15.01.01 20:09 Speckels
 * 
 * 37    15.01.01 19:42 Speckels
 * 
 * 36    15.01.01 19:30 Speckels
 * 
 * 35    13.12.00 10:11 Moos
 * 
 * 34    5.12.00 12:04 Moos
 * 
 * 33    22.11.00 4:13 Hildebrandt
 * 
 * 32    14.11.00 0:25 Hildebrandt
 * 
 * 31    7.11.00 23:35 Hildebrandt
 * 
 * 30    7.11.00 17:24 Hildebrandt
 * 
 * 29    26.10.00 2:23 Hildebrandt
 * 
 * 28    25.10.00 15:07 Hildebrandt
 * 
 * 27    12.10.00 18:02 Hildebrandt
 * 
 * 26    4.10.00 18:34 Hildebrandt
 * 
 * 25    28.09.00 19:18 Hildebrandt
 * 
 * 24    21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 23    14.09.00 16:10 Keskenti
 * 
 * 22    2.09.00 6:53 Hildebrandt
 * 
 * 21    23.08.00 21:09 Hildebrandt 
 * 
 * 20    21.08.00 17:18 Hildebrandt
 * 
 * 19    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    28.07.00 13:55 Hoeller
 * 
 * 17    22.07.00 2:06 Hildebrandt
 * 
 * 16    21.07.00 15:12 Hildebrandt
 * 
 * 15    21.07.00 13:50 Hildebrandt
 * 
 * 14    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 13    6.07.00 13:45 Hildebrandt
 * 
 * 6     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 16    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 15    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 14    20.02.00 18:08 Hildebrandt
 * zenGin 087c
 * 
 * 13    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 11    14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 10    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 9     12/08/99 7:49p Hildebrandt
 * new commandline param: "-zNoTex" => no textures are loaded
 * 
 * 7     13.11.99 1:10 Hildebrandt
 * 
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 54 $ ($Modtime: 24.04.01 0:19 $)


#include <zCore.h>
#include <zSoundMan.h>
#include <zArchiver.h>
#include <zArchiverGeneric.h>
#include <zEventMan.h>
#include <zmusic_dm.h>
#include <zResource.h>
#include <zzDieter.h>
#include <zOption.h>
#include <zRenderManager.h>
#include <zLensflare.h>
#include <zVobMisc.h>
#include <zRenderLightContainer.h>

 
// FIXME: TMP!
#ifndef ZD3D
#define ZD3D
#endif

#ifdef ZD3D
//	#ifndef ZENGINE_DEBUG
//		#include <zRndGlide.h>
//	#endif 
	#include <zRndD3D.h>
#else
//	#include <zRndGlide.h>
#endif

// Console-Commands

static void PrintRendererStatistics()
{
	zTRnd_Stats stat;
	zrenderer->GetStatistics (stat);
	zerr.Message("D: *** zCRenderer Statistics ***");
	zerr.Message("D: texture memory fetched   : " + zSTRING(stat.texMemFetched));
	zerr.Message("D: texture memory used      : " + zSTRING(stat.texMemUsed));
};

class zCVobCallback_PrintBigBBox : public zCVobCallback {
public:
	 zCVobCallback_PrintBigBBox() { zERR_MESSAGE (1,zERR_BEGIN,"D: ***********"); };
	~zCVobCallback_PrintBigBBox() { zERR_MESSAGE (1,zERR_END  ,"D: ***********"); };
	virtual void HandleVob(zCVob* vob, void *callbackData) {
		if (dynamic_cast<zCZone*>(vob))		return;
		zCVobLight *light = dynamic_cast<zCVobLight*>(vob);
		if ((light) && (light->GetIsStatic())) return;

		zTBBox3D box = vob->GetBBox3DWorld();
		for (int i=0; i<3; i++) {
//			if (1)
			if ((box.maxs[i]-box.mins[i])>zREAL(5000.0F)) 
			{
				zSTRING visName;
				visName = (vob->GetVisual() ? vob->GetVisual()->GetClassName_()+":"+vob->GetVisual()->GetVisualName() : "-none-");
				zERR_MESSAGE (1, 0, "D: Name: "+vob->GetVobName()+", class: "+vob->GetClassName_());
				zERR_MESSAGE (1, 0, "D: objname: "+vob->GetObjectName());
				zERR_MESSAGE (1, 0, "D:   visual: "+visName);
				zERR_MESSAGE (1, 0, "D:   bbox  : "+box.GetDescription()); 
				zERR_MESSAGE (1, 0, "D:   pos: X: "+zSTRING(vob->GetPositionWorld()[VX]) + " Y: " + zSTRING(vob->GetPositionWorld()[VY]) + " Z: " + zSTRING(vob->GetPositionWorld()[VZ]) );
				zCVobLight *light = dynamic_cast<zCVobLight*>(vob);
				if (light)
				{
					zERR_MESSAGE (1, 0, "D:   lightRange : "+zSTRING(light->GetRange(),1));
					zERR_MESSAGE (1, 0, "D:   preset: "+zSTRING(light->GetPresetInUseName()));
					zERR_MESSAGE (1, 0, "D:   canMove:"+zSTRING(light->GetCanMove()));					
				};
				break;
			};
		};
	};
};

static zCVob* GetVob (const zSTRING& s, int pos=2) 
{
	const zSTRING&	vobName = s.PickWord (pos, " ", " ");
	const int		vobID	= vobName.ToInt();
	zCVob *vob = 0;
	if (vobID!=0)	vob = zcon.GetWorld()->SearchVobByID	(vobID);
	else			vob = zcon.GetWorld()->SearchVobByName	(vobName);
	return vob;
};

class zCShowMemCallback : public zCWorldPerFrameCallback {
public:
	zTMallocStats	mallocStatsLast;
	zBOOL			firstTime;

	zCShowMemCallback() {
		firstTime	= TRUE;
	};
	void DoWorldPerFrameCallback (zCWorld *world, zCCamera *camera)
	{
		zTMallocStats mallocStats;
		zmalloc.GetStats (mallocStats);

		zTMallocStats mallocStatsDiff;
		#define MALLOC_STATS_DIFF( entry ) mallocStatsDiff.##entry = mallocStats.##entry - mallocStatsLast.##entry;
			MALLOC_STATS_DIFF(numBlocks);
			MALLOC_STATS_DIFF(numBlocksPeak);
			MALLOC_STATS_DIFF(numBytesAllocated);
			MALLOC_STATS_DIFF(numBytesAllocatedPeak);
			MALLOC_STATS_DIFF(numAllocs);
			MALLOC_STATS_DIFF(numFrees);
			MALLOC_STATS_DIFF(numBytesAllocatedTotal);
			MALLOC_STATS_DIFF(numBytesFreedTotal);
		#undef	MALLOC_STATS_DIFF
		mallocStatsLast = mallocStats;

		int numObjTotal;
		int numBytesTotal;
		zCObject::GetMemStats (numObjTotal, numBytesTotal);

		int fonty	= screen->FontY();
		int xpos0	= 2600;
		int xpos1	= xpos0 + 3000;
		int xpos2	= xpos1 + 1600;
		int ypos	= 5000;
		screen->Print	(xpos0, ypos+0*fonty, "numBlocks");
		screen->Print	(xpos0, ypos+1*fonty, "numBlocksPeak");
		screen->Print	(xpos0, ypos+2*fonty, "numBytesAllocated");
		screen->Print	(xpos0, ypos+3*fonty, "numBytesAllocatedPeak");
		screen->Print	(xpos0, ypos+4*fonty, "numAllocs");
		screen->Print	(xpos0, ypos+5*fonty, "numFrees");
		screen->Print	(xpos0, ypos+6*fonty, "numBytesAllocatedTotal");
		screen->Print	(xpos0, ypos+7*fonty, "numBytesFreedTotal");
		screen->Print	(xpos0, ypos+8*fonty, "numzCObject");
		screen->Print	(xpos0, ypos+9*fonty, "numzCObjectBytes");

		screen->Print	(xpos1, ypos+0*fonty, zSTRING(mallocStats.numBlocks));
		screen->Print	(xpos1, ypos+1*fonty, zSTRING(mallocStats.numBlocksPeak));
		screen->Print	(xpos1, ypos+2*fonty, zSTRING(mallocStats.numBytesAllocated));
		screen->Print	(xpos1, ypos+3*fonty, zSTRING(mallocStats.numBytesAllocatedPeak));
		screen->Print	(xpos1, ypos+4*fonty, zSTRING(mallocStats.numAllocs));
		screen->Print	(xpos1, ypos+5*fonty, zSTRING(mallocStats.numFrees));
		screen->Print	(xpos1, ypos+6*fonty, zSTRING(float(mallocStats.numBytesAllocatedTotal)));
		screen->Print	(xpos1, ypos+7*fonty, zSTRING(float(mallocStats.numBytesFreedTotal)));
		screen->Print	(xpos1, ypos+8*fonty, zSTRING(numObjTotal));
		screen->Print	(xpos1, ypos+9*fonty, zSTRING(numBytesTotal));

		screen->Print	(xpos2, ypos+0*fonty, zSTRING(mallocStatsDiff.numBlocks));
		screen->Print	(xpos2, ypos+1*fonty, zSTRING(mallocStatsDiff.numBlocksPeak));
		screen->Print	(xpos2, ypos+2*fonty, zSTRING(mallocStatsDiff.numBytesAllocated));
		screen->Print	(xpos2, ypos+3*fonty, zSTRING(mallocStatsDiff.numBytesAllocatedPeak));
		screen->Print	(xpos2, ypos+4*fonty, zSTRING(mallocStatsDiff.numAllocs));
		screen->Print	(xpos2, ypos+5*fonty, zSTRING(mallocStatsDiff.numFrees));
		screen->Print	(xpos2, ypos+6*fonty, zSTRING(float(mallocStatsDiff.numBytesAllocatedTotal)));
		screen->Print	(xpos2, ypos+7*fonty, zSTRING(float(mallocStatsDiff.numBytesFreedTotal)));
		
		screen->Print	(xpos0, ypos+10*fonty, "assigned mem");
		screen->Print	(xpos1, ypos+10*fonty, zSTRING(mallocStats.numAllocs-mallocStats.numFrees));


	};
};

static void InstallShowMem ()
{
	static zCShowMemCallback showMemCallback;
	static zBOOL toggle=FALSE;
	toggle=!toggle;
	if (toggle)		zcon.GetWorld()->RegisterPerFrameCallback	(&showMemCallback);
	else			zcon.GetWorld()->UnregisterPerFrameCallback	(&showMemCallback);
};

/*--------------------------------------------------------------------------

    ConsoleEval()
    14-Sep-00       [Roman Keskenti]
                      Added console commands for modifying the timer's
					  motion-speed-factor
	19-Sep-00		[HILDEBRANDT]
					Adjustment in ZLIST MESHESWITHLOTSOFMATERIALS for changed zCProgMeshProto interface;
					Neu: ZTOGGLE MARKPMESHMATERIALS
--------------------------------------------------------------------------*/ 

static zBOOL ConsoleEval (const zSTRING &s, zSTRING &msg) {
	if (!zcon.GetWorld()) {
		msg = "ERROR: no zCWorld registered to zcon !";
		return FALSE;
	};

	msg = "ok";
	
	if (s.Search("ZFOGZONE")!=-1) {
		static zBOOL done = FALSE;
		if (done) return FALSE;
		done = TRUE;

		//
		zCZoneZFog			*zone	= zNEW(zCZoneZFog);
		zCZoneZFogDefault	*zoneDef= zNEW(zCZoneZFogDefault);

		// PsiCamp
		zVEC3		cent(50327, -2527, -11829);
		zTBBox3D	vbox;
		vbox.mins					= cent + zVEC3(-1,-1,-1)*30000;
		vbox.maxs					= cent + zVEC3(+1,+1,+1)*30000;
		zone->Move					(cent);
		zone->SetBBox3DWorld		(vbox);
		zone->SetInnerRangePerc		(0.5F);
		zone->SetFogRange			(5000.0F);
		zcon.GetWorld()->AddVob		(zone);

		// Mine
		zone	= zNEW(zCZoneZFog);
		vbox.mins					= zVEC3(-61574, 0000,-130000);
		vbox.maxs					= zVEC3(-42000,16000,+30000);
		zone->SetPositionWorld		(vbox.GetCenter());
		zone->SetBBox3DWorld		(vbox);
		zone->SetInnerRangePerc		(0.5F);
		zone->SetFogRange			(4500.0F);
		zcon.GetWorld()->AddVob		(zone);

		//
		zoneDef->SetPositionWorld	(0,0,0);
		zoneDef->SetFogRange		(50000.0F);
		zcon.GetWorld()->AddVob		(zoneDef);
		
	} else 
	if (s.Search("ZMARK")!=-1) {
		zcon.GetWorld()->DebugMarkOccluderPolys();
		msg = "marking occluder polys (outdoor)";
	} else 
	if (s.Search("ZWORLD STATUS")!=-1) {
		zcon.GetWorld()->PrintStatus();
	} else
	if (s.Search("ZWORLD VOBTREE")!=-1) {
		zcon.GetWorld()->PrintGlobalVobTree();
	} else
	if (s.Search("ZWORLD ACTIVEVOBS")!=-1) {
		zcon.GetWorld()->PrintActiveVobs();
	} else
	if (s.Search("ZTOGGLE PFXINFOS")!=-1) {
		zCParticleFX::SetShowDebugInfo(!zCParticleFX::GetShowDebugInfo());
	} else
	if (s.Search("ZSET RELIGHTTIME")!=-1) {
		zREAL lightPerfCtr = s.PickWord (3, " ", " ").ToFloat();
		if (zCSkyControler::GetActiveSkyControler())
		{
			zCSkyControler::GetActiveSkyControler()->SetRelightTime(lightPerfCtr);
		}
	}else
	if (s.Search("ZTOGGLE LIGHTSTAT")!=-1) {
		if (zcon.GetWorld()->GetWorldRenderMode()==zWLD_RENDER_MODE_LIGHTMAPS)
			zcon.GetWorld()->SetWorldRenderMode(zWLD_RENDER_MODE_VERT_LIGHT);
		else
			zcon.GetWorld()->SetWorldRenderMode(zWLD_RENDER_MODE_LIGHTMAPS);
	} else
	if (s.Search("ZTOGGLE SHOWZONES")!=-1) {
		zcon.GetWorld()->SetShowZonesDebugInfo (!zcon.GetWorld()->GetShowZonesDebugInfo());
	} else
	if (s.Search("ZTOGGLE SHOWTRACERAY")!=-1) {
		zcon.GetWorld()->SetShowTraceRayLines	(!zcon.GetWorld()->GetShowTraceRayLines());
	} else
	if (s.Search("ZRMODE MAT")!=-1) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_MATERIAL);
	} else
	if (s.Search("ZRMODE WMAT")!=-1) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_MATERIAL_WIRE);
	} else
	if (s.Search("ZRMODE FLAT")!=-1) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_FLAT);
	} else
	if (s.Search("ZRMODE WIRE")!=-1) {
		zrenderer->SetPolyDrawMode (zRND_DRAW_WIRE);
	} else
	if (s.Search("ZTOGGLE VOBBOX")!=-1) {
		zcon.GetWorld()->SetDrawVobBBox3D (!zcon.GetWorld()->GetDrawVobBBox3D());
	} else
	if (s.Search("ZTOGGLE RENDERVOB")!=-1) {
		zCVob::SetRenderVobs (!zCVob::GetRenderVobs());
	} else
	if (s.Search("ZRNDSTAT")!=-1) {
		PrintRendererStatistics();
	} else 
	if (s.Search("ZVIDEORES")!=-1) {
		int x	= s.PickWord (2, " ", " ").ToInt();
		int y	= s.PickWord (3, " ", " ").ToInt();
		int bpp	= s.PickWord (4, " ", " ").ToInt();
		zCView::SetMode (x, y, bpp);
	} else 
	if (s.Search("ZTOGGLE MARKPMESHMATERIALS")!=-1) {
		zCProgMeshProto::SetMarkMeshMaterials (!zCProgMeshProto::GetMarkMeshMaterials ());
	} else 
	if (s.Search("ZTOGGLE PMESHSUBDIV")!=-1) {
		zCProgMeshProto::SetAutoSubdivEnabled(!zCProgMeshProto::GetAutoSubdivEnabled());
	} else 
	if (s.Search("ZTOGGLE TNL")!=-1) {
		zCRenderManager::SetUseRendererTNL (!zCRenderManager::GetUseRendererTNL());
		if (zCRenderManager::GetUseRendererTNL()) msg = "tnl on";
		else									  msg = "tnl off";
	} else
	if (s.Search("ZLIST MESHESWITHLOTSOFMATERIALS")!=-1) {
		int numMats = s.PickWord (3, " ", " ").ToInt();
		if (numMats<4) numMats=4;
		for (int i=0; i<zCProgMeshProto::GetStaticClassDef()->GetNumObjects(); i++)
		{
			zCProgMeshProto *pmProto = dynamic_cast<zCProgMeshProto*>(zCProgMeshProto::GetStaticClassDef()->GetObjectByIndex(i));
			if (pmProto->GetNumMaterial()>=numMats)
//			if (pmProto->materialList.GetNum()==1)
				zerr.Message ("D: "+zSTRING(i)+", "+pmProto->GetObjectName()+": "+zSTRING(pmProto->GetNumMaterial()));
		};
		{
			const int MAX=8;
			int buckets[MAX];
			for (int i=0; i<MAX; i++) buckets[i]=0;

			//
			int numMatsTotal=0;
			int numTriTotal=0;
			int numVertTotal=0;
			for (i=0; i<zCProgMeshProto::GetStaticClassDef()->GetNumObjects(); i++)
			{
				zCProgMeshProto *pmProto = dynamic_cast<zCProgMeshProto*>(zCProgMeshProto::GetStaticClassDef()->GetObjectByIndex(i));
				buckets[pmProto->GetNumMaterial()]++;
				numMatsTotal	+= pmProto->GetNumMaterial();
				numTriTotal		+= pmProto->GetNumTri();
				numVertTotal	+= pmProto->GetNumVert();
			};
			float numMeshes = float(zCProgMeshProto::GetStaticClassDef()->GetNumObjects());
			zERR_MESSAGE (0,0, "D: avgMatsPerMesh: "+zSTRING(float(numMatsTotal)/numMeshes,3));
			zERR_MESSAGE (0,0, "D: avgTrisPerMesh: "+zSTRING(float(numTriTotal)/numMeshes,3));
			zERR_MESSAGE (0,0, "D: avgVertsPerMesh: "+zSTRING(float(numVertTotal)/numMeshes,3));
			for (i=0; i<MAX; i++)
			{
				zERR_MESSAGE (0,0, "D: numMat: "+zSTRING(i)+", numMeshes: "+zSTRING(buckets[i]));
			};
		};
	} else 
	if (s.Search("ZLIST MESH")!=-1) {
		zerr.Message ("D: *** enumerating zCMesh ***");
		zCMesh *mesh=zCMesh::GetFirstInList();
		int i=0;
		while (mesh) {
			// FIXME: GetName() und GetRef() !!!
			zerr.Message ("D: "+zSTRING(i)+": "+mesh->GetMeshName()+" (ref: "+zSTRING(mesh->GetRefCtr())+")");
			i++;
			mesh = mesh->GetNextInList();
		};
		zerr.Message ("D: ****************************");
	} else
	if (s.Search("ZTOGGLE FARFADE")!=-1) {
		zCWorld::SetFadeOutFarVertices(!zCWorld::GetFadeOutFarVertices());
	} else
	if (s.Search("ZLIST TEX")!=-1) {
		zerr.Message ("D: *** enumerating zCTexture ***");
		{
			int num=0;
			int locked=0;
			for (int i=0; i<zCTexture::GetStaticClassDef()->GetNumObjects(); i++)
			{
				if (static_cast<zCTexture*>(zCTexture::GetStaticClassDef()->GetObjectByIndex(i))->GetCacheState()==zRES_CACHED_IN) num++;
				if (static_cast<zCTexture*>(zCTexture::GetStaticClassDef()->GetObjectByIndex(i))->GetCacheOutLock()) locked++;
			};
			zERR_MESSAGE (0,0,"D: numLiving objects: "+zSTRING(zCTexture::GetStaticClassDef()->GetNumLivingObjects()));
			zERR_MESSAGE (0,0,"D: numObjectList    : "+zSTRING(zCTexture::GetStaticClassDef()->GetNumObjects()));
			zERR_MESSAGE (0,0,"D: numCachedIn      : "+zSTRING(num));
			zERR_MESSAGE (0,0,"D: numLocked        : "+zSTRING(locked));
		};

		if (s.Search("ZLIST TEX FULL")!=-1) 
		{
			int mem=0;
			for (int i=0; i<zCTexture::GetStaticClassDef()->GetNumObjects(); i++)
			{
				zCTexture *tex = static_cast<zCTexture*>(zCTexture::GetStaticClassDef()->GetObjectByIndex(i));
				int xdim, ydim;
				tex->GetPixelSize (xdim, ydim);
				zerr.Message ("D: "+zSTRING(i)+": "+tex->GetName()+", "+zSTRING(xdim)+"x"+zSTRING(ydim)+" (ref: "+zSTRING(tex->GetRefCtr())+")");
				mem += tex->GetMemSizeBytes();
			};
			zerr.Message ("D: mem total: "+zSTRING(mem));
		};
		zerr.Message ("D: ****************************");
	} else
	if (s.Search("ZLIST MAT")!=-1) {
		zerr.Message ("D: *** enumerating zCMaterial ***");
		for (int i=0; i<zCMaterial::GetStaticClassDef()->GetNumObjects(); i++)
		{
			zCMaterial *mat = static_cast<zCMaterial*>(zCMaterial::GetStaticClassDef()->GetObjectByIndex(i));
			zerr.Message ("D: "+zSTRING(i)+": "+mat->GetName()+" (ref: "+zSTRING(mat->GetRefCtr())+")");
		};
		zerr.Message ("D: ****************************");
	} else
	if (s.Search("ZLIST CLASSTREE")!=-1) {
		zCObject::PrintClassHierarchy();
	} else 
	if (s.Search("ZLIST VOBSWITHBIGBBOX")!=-1) {
		zCVobCallback_PrintBigBBox vobCallback;
		zcon.GetWorld()->TraverseVobTree (vobCallback);
	} else
	if (s.Search("ZLIST")!=-1) {
		zSTRING className(s.PickWord (2, " ", " "));
		zCClassDef *classDef= zCClassDef::GetClassDefTypeInsensitive(className);
		if (classDef) 
		{
			zerr.Message ("D: *** Enumerating "+className+" ***");
			for (int i=0; i<classDef->GetNumObjects(); i++) {
				zCObject *obj = classDef->GetObjectByIndex (i);
				zerr.Message ("D: "+zSTRING(i)+": "+obj->GetObjectName()+" (ref: "+zSTRING(obj->GetRefCtr())+")");
			};
			zerr.Message ("D: ****************************");
		};
	} else
	if (s.Search("ZMOVECAMTOVOB")!=-1) {
		zCVob* vob = GetVob (s, 2);
		if (vob) 
		if (zCCamera::activeCam)
		if (zCCamera::activeCam->GetVob())
		{
			zCCamera::activeCam->GetVob()->SetPositionWorld (vob->GetPositionWorld());
		};
		if (!vob)
			msg = "no vob found";
	} else
	if (s.Search("ZWORLD VOBPROPS")!=-1) {
		zCVob* vob = GetVob (s, 3);
		if (vob) {
			zSTRING props;
			zCArchiver *arc			= zarcFactory.CreateArchiverWrite (zARC_MODE_ASCII_PROPS);
			zERR_ASSERT_STRICT (arc);
			arc->WriteObject		(vob);
			arc->GetBufferString	(props);
			arc->Close				();
			zRELEASE				(arc);

			//
			zSTRING line;
			int		pos=1;
			do {
				line = props.PickWord (pos, "", "\r\n");
				if (line.IsEmpty()) break;
				pos++;
				zerr.Message ("D: "+line);
			} while (pos<100);
		} else
			msg = "no vob found";
	} else 
	if (s.Search("ZMODEL PRINTTREE")!=-1) {
		const zSTRING& protoName = s.PickWord (3, " ", " ");
		zCModelPrototype *modelProto = zCModelPrototype::SearchName (protoName);
		if (modelProto)
			modelProto->DescribeTree();
	} else 
	if (s.Search("ZSOUNDMAN DEBUG")!=-1) {
		if (zsndMan)
			zsndMan->debugMessageEnabled = !zsndMan->debugMessageEnabled;
	} else 
	if (s.Search("ZTRIGGER")!=-1) {
		const zSTRING&	vobName = s.PickWord (2, " ", " ");
		if (vobName.Search("TIMEDEMO")==-1)
		{
			zCArray<zCVob*> targetVobList;
			zcon.GetWorld()->SearchVobListByName (vobName, targetVobList);
			for (int i=0; i<targetVobList.GetNum(); i++) {
				targetVobList[i]->GetEM()->OnTrigger (zCCamera::activeCam->GetVob(), zCCamera::activeCam->GetVob());
			};
		}
	} else 
	if (s.Search("ZUNTRIGGER")!=-1) {
		const zSTRING&	vobName = s.PickWord (2, " ", " ");
		zCArray<zCVob*> targetVobList;
		zcon.GetWorld()->SearchVobListByName (vobName, targetVobList);
		for (int i=0; i<targetVobList.GetNum(); i++) {
			targetVobList[i]->GetEM()->OnUntrigger (zCCamera::activeCam->GetVob(), zCCamera::activeCam->GetVob());
		};
	} else 
	if (s.Search("ZTOGGLE MODELSKELETON")!=-1) {
		zCModel::SetDrawSkeleton (!zCModel::GetDrawSkeleton());
	}
	else
	if (s.Search("ZTOGGLE SMOOTHROOTNODE")!=-1) {
		zCModel::S_SetSmoothRootNode(!zCModel::S_GetSmoothRootNode());
		if (zCModel::S_GetSmoothRootNode())	msg = "smoothing on";
		else								msg = "smoothing off";
	} else 
	if (s.Search("ZSTARTANI")!=-1) {
		zCVob*	vob		= GetVob (s, 2);
		if (vob) {
			zCVisualAnimate *vis	= dynamic_cast<zCVisualAnimate*>(vob->GetVisual());
			zSTRING aniName			= s.PickWord (3, " ", " ");
			vob->SetSleeping		(FALSE);
			vis->StartAnimation		(aniName);
		}; 
	} else 
	if (s.Search("ZARCTEST")!=-1) {
		zCArchiverGeneric::TestClassIntegrity();
		zCEventMessage::TestClassIntegrity();
	} else 
	if (s.Search("ZRNDMODELIST")!=-1) {
		if (zrenderer)
		{
			zerr.Message ("D: Enumerating renderer modes/devices...");
			for (int i=0; i<zrenderer->Vid_GetNumDevices(); i++)
			{
				zTRnd_DeviceInfo deviceInfo;
				zrenderer->Vid_GetDeviceInfo (deviceInfo, i);
				const zSTRING s = (zrenderer->Vid_GetActiveDeviceNr()==i) ? " (active)" : "";
				zerr.Message ("D: device "+zSTRING(i)+": "+deviceInfo.deviceName + s);
			};
			for (i=0; i<zrenderer->Vid_GetNumModes(); i++)
			{
				zTRnd_VidModeInfo modeInfo;
				zrenderer->Vid_GetModeInfo (modeInfo, i);
				zerr.Message ("D: mode "+zSTRING(i)+": "+zSTRING(modeInfo.xdim)+"x"+zSTRING(modeInfo.ydim)+"x"+zSTRING(modeInfo.bpp)
					+ (modeInfo.fullscreenOnly ? " f" : " f/w"));
			};
		};
	} else 
	if (s.Search("ZOVERLAYMDS APPLY")!=-1) {
		zCVob *vob = GetVob(s, 3);
		if ((vob) &&
		    (vob->GetVisual()) &&
		    (dynamic_cast<zCModel*>(vob->GetVisual())))
		{
			zCModel* model = dynamic_cast<zCModel*>(vob->GetVisual());
			model->ApplyModelProtoOverlay	(s.PickWord (4," ", " "));
		} else msg="not found";
	} else 
	if (s.Search("ZTOGGLE TEXSTATS")!=-1) {
		zcon.GetWorld()->SetShowTextureStats (!zcon.GetWorld()->GetShowTextureStats());
	} else 
	if (s.Search("ZTOGGLE RESMANSTATS")!=-1) {
		zERR_ASSERT (zresMan);
		zresMan->SetShowDebugInfo (!zresMan->GetShowDebugInfo());
	} else 
	if (s.Search("ZPROGMESHLOD")!=-1) {
		zCProgMeshProto::SetLODParamStrength (s.PickWord (2, " ", " ").ToFloat());
	} else 
	if (s.Search("ZTOGGLE SHOWMEM")!=-1) {
		//
		InstallShowMem ();
	} else 
	if (s.Search("ZTOGGLE VOBMORPH")!=-1) {
		//
		zCVob::SetAnimationsEnabled(!zCVob::GetAnimationsEnabled());
	} else 
	if (s.Search("ZTOGGLE MATMORPH")!=-1) {
		//
		zCWorld::SetWaveAnisEnabled(!zCWorld::GetWaveAnisEnabled());
	} else
	if (s.Search("ZMEM DUMPHEAP BYTESPERLINE")!=-1) {
		zmalloc.DumpHeap	(zMALLOC_SORT_BY_BYTES_PER_LINE);
	} else 
	if (s.Search("ZMEM DUMPHEAP BLOCKSPERLINE")!=-1) {
		zmalloc.DumpHeap	(zMALLOC_SORT_BY_BLOCKS_PER_LINE);
	} else 
	if (s.Search("ZMEM DUMPHEAP SORTBYTIME")!=-1) {
		zmalloc.DumpHeap	(zMALLOC_SORT_BY_TIME);
	} else 
	if (s.Search("ZMEM CHECKHEAP")!=-1) {
		zBOOL res		= zmalloc.CheckHeap	();
		if (!res)	msg = "CheckHeap() failed";
	} else 
	if (s.Search("ZTOGGLE SHOWPORTALS")!=-1) {
		zCBspTree::SetShowPortals (!zCBspTree::GetShowPortals());
	} else 
	if (s.Search("ZTOGGLE SHOWHELPVERVISUALS")!=-1) {
		zCVob::SetShowHelperVisuals (!zCVob::GetShowHelperVisuals());
	} else 
	if (s.Search("ZSTARTRAIN")!=-1) 
	{
		zCSkyControler_Outdoor *skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(zcon.GetWorld()->GetActiveSkyControler());
		if (skyCtrl)
		{
			skyCtrl->SetWeatherType(zTWEATHER_RAIN);
			zREAL weight = s.PickWord (2, " ", " ").ToFloat();
			skyCtrl->SetRainFXWeight (weight, 0.1F);
			msg = "started rain";
		};
	} else 
	if (s.Search("ZSTARTSNOW")!=-1) 
	{
		zCSkyControler_Outdoor *skyCtrl = dynamic_cast<zCSkyControler_Outdoor*>(zcon.GetWorld()->GetActiveSkyControler());
		if (skyCtrl)
		{
			skyCtrl->SetWeatherType(zTWEATHER_SNOW);
			zREAL weight = s.PickWord (2, " ", " ").ToFloat();
			skyCtrl->SetRainFXWeight (weight, 0.1F);
			msg = "started rain";
		};
	} else 
	if (s.Search("ZSET VOBFARCLIPZSCALER")!=-1) {
		zREAL value = s.PickWord (3, " ", " ").ToFloat();
		zcon.GetWorld()->SetVobFarClipZScalability	(value);
	} else 
	if (s.Search("ZSET LEVELFARCLIPZSCALER")!=-1) {
		zREAL value = s.PickWord (3, " ", " ").ToFloat();
		zcon.GetWorld()->GetActiveSkyControler()->SetFarZScalability (value);
	} else 
	if (s.Search("ZHIGHQUALITYRENDER")!=-1) {
		zcon.GetWorld()->SetVobFarClipZScalability					(zREAL(30.0F));
		zcon.GetWorld()->GetActiveSkyControler()->SetFarZScalability(zREAL(30.0F));
		zCProgMeshProto::SetLODParamStrengthModifier				(zREAL(1.0F));
		zCTexture::RefreshTexMaxSize								(16384);
	} else 

	if (s.Search("ZOVERLAYMDS REMOVE")!=-1) {
		zCVob *vob = GetVob(s, 3);
		if ((vob) &&
		    (vob->GetVisual()) &&
		    (dynamic_cast<zCModel*>(vob->GetVisual())))
		{
			zCModel* model = dynamic_cast<zCModel*>(vob->GetVisual());
			model->RemoveModelProtoOverlay	(s.PickWord (4," ", " "));
		} else msg="not found";
	//
	//	CODECHANGE [ROMAN]
	//
	} else 
	if (s.Search("ZTIMER MULTIPLIER")!=-1) {
		float fMotionFactor = s.PickWord( 3, " ", " " ).ToFloat();
		::ztimer.SetMotionFactor( fMotionFactor );
	} else 
	if (s.Search("ZTIMER REALTIME")!=-1) {
		::ztimer.SetMotionFactor( 1.0f );
	//
	//	CODECHANGE [ROMAN]
	//
	} else {
		msg.Clear(); 
		return FALSE; 
	};
	return TRUE;
};


static void InitRenderer (zTSystemContextHandle* initContextHandle)
{
	// Renderer erzeugen
	int commandLineDeviceNr = -1;
 	if (zoptions->Parm("ZRND")) 
	{
		zSTRING s (zoptions->ParmValue ("ZRND"));
		if (s.Search ("D3D")!=-1)	
		{
			zrenderer	= zNEW(zCRnd_D3D);
			if (s.Search ("1")!=-1) commandLineDeviceNr = 1;
		} 
	} else {
		if (!zrenderer)
		{
			zerr.Message ("D: RENDERER: no renderer specified, trying D3D (dev0)");
			zrenderer	= zNEW(zCRnd_D3D);	
		}
	};

	// Aufloesung erfragen (Kommandozeile, options)
	int		resXDim			= 800;	// Default Werte	// [BENDLIN] 800x600, old = 640
	int		resYDim			= 600;						// [BENDLIN] 800x600, old = 480
	int		resBPP			= 16;						// [BENDLIN] 800x600, old = 16
	zBOOL	startupWindowed	= FALSE;
	int		vidDevice		= 0;
	zREAL	vidGamma		= zREAL(0.5F);
	zREAL	vidContrast		= zREAL(0.5F);
	zREAL	vidBrightness	= zREAL(0.5F);

	// 1) zunaechst aus der .ini
	resXDim					= zoptions->ReadInt		(zOPT_SEC_VIDEO, "zVidResFullscreenX"	, resXDim);
	resYDim					= zoptions->ReadInt		(zOPT_SEC_VIDEO, "zVidResFullscreenY"	, resYDim);
	resBPP					= zoptions->ReadInt		(zOPT_SEC_VIDEO, "zVidResFullscreenBPP"	, resBPP);	
	vidDevice				= zoptions->ReadInt		(zOPT_SEC_VIDEO, "zVidDevice"			, vidDevice);	
	vidGamma				= zoptions->ReadReal	(zOPT_SEC_VIDEO, "zVidGamma"			, vidGamma);	
	vidContrast				= zoptions->ReadReal	(zOPT_SEC_VIDEO, "zVidContrast"			, vidContrast);	
	vidBrightness			= zoptions->ReadReal	(zOPT_SEC_VIDEO, "zVidBrightness"		, vidBrightness);	
	
	// 2) ggfs. durch CmdLine ueberschreiben
	if (zoptions->Parm("ZRES")) {
		const zSTRING		s (zoptions->ParmValue ("ZRES"));
		resXDim				= s.PickWord (1, ",", ",").ToInt();
		resYDim				= s.PickWord (2, ",", ",").ToInt();
		resBPP				= s.PickWord (3, ",", ",").ToInt();
	};	

	//
	if (commandLineDeviceNr>=0) {
		vidDevice			= commandLineDeviceNr;
	};	

	startupWindowed			= zoptions->ReadBool(zOPT_SEC_VIDEO, "zStartupWindowed"		, FALSE);
	if (zoptions->Parm("ZWINDOW")) 
		startupWindowed		= TRUE;

	// Renderer initialisieren
	zrenderer->Vid_SetDevice				(vidDevice);
	zrenderer->Vid_SetScreenMode			(startupWindowed ? zRND_SCRMODE_WINDOWED : zRND_SCRMODE_FULLSCREEN); 
	zrenderer->Vid_SetMode					(resXDim, resYDim, resBPP, initContextHandle);			// Methode sucht sich autom. passenden Mode, falls es gerade diesen nicht gibt
	zrenderer->Vid_Clear					(zCOLOR(0));
	zrenderer->Vid_SetGammaCorrection		(vidGamma, vidContrast, vidBrightness);

	// Erst nach gesetztem 'zrenderer->Vid_SetMode()' aufrufen!
	zCTexture::AutoDetectRendererTexScale	();
	zCTexture::SetGlobalLoadTextures		(!zoptions->Parm("ZNOTEX"));

	// Hier wird 'nochmal' das SetMode aufgerufen, damit auch die zCView vom gesetzten Mode erfaehrt.
	zCView::SetMode							(resXDim, resYDim, resBPP, initContextHandle);			// Methode sucht sich autom. passenden Mode, falls es gerade diesen nicht gibt

};

/*--------------------------------------------------------------------------

    zDieter_StartUp()
    14-Sep-00       [Roman Keskenti]
                    Added console commands for modifying the timer's
					motion-speed-factor
	19-Sep-00		[HILDEBRANDT]
					Added zTSystemContextHandle* initContextHandle
	04-Oct-00		[HILDEBRANDT]
					Initialisierungsreihenfolge geaendert, zrenderer/zCView::SetMode()
					(war wichtig 
    05-Dec-00       [MOOS]
                    Notbremse gegen den Zeitlupenbug eingebaut
                    MemPool-Deaktivierung ueber -znomempool eingebaut
	01-Feb-01		[SPECKELS]
					Abfrage vonn Sound- und Musikeinstellungen angepasst
	--------------------------------------------------------------------------*/ 

void zDieter_StartUp(zTSystemContextHandle* initContextHandle)
{
	//
	Trg_Init();

    // [Moos] Frameratenbegrenzung als letzte Maßnahme gegen den Zeitlupenbug
    if (zoptions->Parm("ZMAXFRAMERATE"))
    {
        int fps = zoptions->ParmValue("ZMAXFRAMERATE").ToInt();
        ztimer.LimitFPS(fps); // [Moos]
    }

    // MemPools zur Not deaktivieren
    zCMemPoolBase::DisablePools((zoptions->Parm("ZNOMEMPOOL")));

	// Renderer
	InitRenderer(initContextHandle);

	// Music 
	// [SPECKELS] Abfrage bzgl. Musik- und Sound-Einstellungen angepasst
#ifdef ZENGINE_DEBUG
	zmusic  = zNEW(zCMusicSys_Dummy		());
#else	
	if (zoptions->Parm("ZNOMUSIC")) zoptions->WriteBool(zOPT_SEC_SOUND,"musicEnabled",FALSE,TRUE);
	zBOOL musicOn = zoptions->ReadBool(zOPT_SEC_SOUND,"musicEnabled",TRUE);
	zCMusicSystem::DisableMusicSystem(!musicOn);

	if (!zmusic)
	{
		if (zoptions->Parm("ZNOMUSIC"))	zmusic  = zNEW(zCMusicSys_Dummy		());
		else							zmusic  = zNEW(zCMusicSys_DirectMusic());
	}
#endif

	// SoundSystem
	if (zoptions->Parm("ZNOSOUND")) zoptions->WriteBool(zOPT_SEC_SOUND,"soundEnabled",FALSE,TRUE);
	zBOOL soundEnabled = zoptions->ReadBool(zOPT_SEC_SOUND,"soundEnabled",TRUE);	

	if (!zsound)
	{
		if (soundEnabled)	zsound	= zNEW(zCSndSys_MSS			());
		else				zsound	= zNEW(zCSoundSystemDummy	());
	}

	//
#ifdef COMPILING_SPACER
	if (!zsndMan)
	{
		zsndMan = zNEW(zCSoundManager());
	}
	else return;
#else
		zsndMan = zNEW(zCSoundManager());
#endif


	zBOOL autoConvertData = zoptions->Parm("ZAUTOCONVERTDATA");
	zCModelPrototype::SetAutoConvertAnis		(autoConvertData);
	zCMesh			::SetAutoConvertMeshes		(autoConvertData);
	zCMorphMeshProto::SetAutoConvertBinaryFiles	(autoConvertData);

	// Console 
	zcon.Register		("ZMARK"						, "marks outdoor occluder polys");
	zcon.Register		("ZWORLD STATUS"				, "prints some engine-world data");
	zcon.Register		("ZWORLD ACTIVEVOBS"			, "prints engine-world activeVobList");
	zcon.Register		("ZWORLD VOBTREE"				, "prints engine-world globalVobTree");
	zcon.Register		("ZWORLD VOBPROPS"				, "prints props of vob with specified name [VOB_NAME | VOB_ID]");
	zcon.Register		("ZRMODE MAT"					, "rendermode material/normal");
	zcon.Register		("ZRMODE WMAT"					, "rendermode material with overlaid wireframe");
	zcon.Register		("ZRMODE FLAT"					, "rendermode flat");
	zcon.Register		("ZRMODE WIRE"					, "rendermode wireframe");
	zcon.Register		("ZTOGGLE LIGHTSTAT"			, "toggles lightmaps/vertLight");
	zcon.Register		("ZTOGGLE VOBBOX"				, "toggles bbox3D drawing of vobs");
	zcon.Register		("ZTOGGLE RENDERVOB"			, "toggles drawing of vobs");
	zcon.Register		("ZTOGGLE MODELSKELETON"		, "toggles drawing of all models node-hierarchies");
	zcon.Register		("ZTOGGLE SMOOTHROOTNODE"		, "toggles smooothing of model root nodes translation");
	zcon.Register		("ZTOGGLE TEXSTATS"				, "toggles display of scene texture statistics");
	zcon.Register		("ZRNDSTAT"						, "renderer statistics");
	zcon.Register		("ZRNDMODELIST"					, "enumerates the renderers available modes and devices");
	zcon.Register		("ZVIDEORES"					, "sets video resolution");
	zcon.Register		("ZLIST MAT"					, "enumerating materials");
	zcon.Register		("ZLIST TEX"					, "enumerating textures");
	zcon.Register		("ZLIST MESH"					, "enumerating meshes");
	zcon.Register		("ZLIST CLASSTREE"				, "enumerating class hierarchy");
	zcon.Register		("ZMODEL PRINTTREE"				, "prints a model's node hierarchy [MODEL_NAME]");
	zcon.Register		("ZMOVECAMTOVOB"				, "[VOB_NAME | VOB_ID]");
	zcon.Register		("ZSOUNDMAN DEBUG"				, "toggles SoundManager debug info");
	zcon.Register		("ZTRIGGER"						, "sends trigger-message to vob [VOB_NAME | VOB_ID]");
	zcon.Register		("ZUNTRIGGER"					, "sends untrigger-message to vob [VOB_NAME | VOB_ID]");
	zcon.Register		("ZARCTEST"						, "tests integrity of each classes' arc/unarc funcs");
	zcon.Register		("ZOVERLAYMDS APPLY"			, "applies overlay-.MDS to vob's model [VOB_NAME | VOB_ID] [MDS_NAME]");
	zcon.Register		("ZOVERLAYMDS REMOVE"			, "removes overlay-.MDS from vob's model [VOB_NAME | VOB_ID] [MDS_NAME]");
	zcon.Register		("ZLIST"						, "list every living object of class [CLASS_NAME], if the class has SHARED_OBJECTS flag");
	zcon.Register		("ZTOGGLE SHOWZONES"			, "lists all zones the camera is currently located in (sound,reverb,fog,..)");
	zcon.Register		("ZTOGGLE SHOWTRACERAY"			, "displays all rays traced in the world as lines");
	zcon.Register		("ZTOGGLE SHOWPORTALS"			, "displays portals processed during occlusion during");
	zcon.Register		("ZTOGGLE SHOWHELPVERVISUALS"	, "displays helper visuals for vobs that don't have a natural visualization (eg zCTriggers)");
	zcon.Register		("ZTOGGLE PFXINFOS"				, "");
	zcon.Register		("ZSTARTANI"					, "starts ani on specified vob if it has a animatable visual [VOB_NAME] [ANI_NAME]");
	zcon.Register		("ZLIST VOBSWITHBIGBBOX"		, "lists suspicious vobs with very large bboxes");
	zcon.Register		("ZLIST MESHESWITHLOTSOFMATERIALS","lists suspicious meshes with large material counts [NUM_MIN]");
	zcon.Register		("ZTOGGLE RESMANSTATS"			, "displays resource manager statistics (textures,sounds,..)");
	zcon.Register		("ZPROGMESHLOD"					, "apply global strength value to all pm LOD rendering, -1(default), 0..1..x");
	zcon.Register		("ZTOGGLE MARKPMESHMATERIALS"	, "marks vob/pmesh materials with color-code: red=1st mat, blue=2nd mat, green=3rd, yellow..white..brown..black=7th");
	zcon.Register		("ZTOGGLE PMESHSUBDIV"			, "debug");
	zcon.Register		("ZTOGGLE SHOWMEM"				, "displays information on heap allocations realtime onscreen");
	zcon.Register		("ZTOGGLE VOBMORPH"				, "toggles morphing of vobs");
	zcon.Register		("ZTOGGLE MATMORPH"				, "toggles morphing of materials");
	zcon.Register		("ZTOGGLE TNL"					, "toggles using of hardware transform and lightning");

//	zcon.Register		("ZTOGGLE ALPHASKY"				, "toggles rendering of the alpha sky layer");
//	zcon.Register		("ZTOGGLE OCCLUSION"			, "toggles engine occlusion culling");
//	zcon.Register		("ZTOGGLE FARFADE"				, "toggles far-fading and angle based alpha change of static water polys");

	zcon.Register		("ZMEM DUMPHEAP BYTESPERLINE"	, "dumps current heap allocations sorted by bytes per line");
	zcon.Register		("ZMEM DUMPHEAP BLOCKSPERLINE"	, "dumps current heap allocations sorted by block per line");
	zcon.Register		("ZMEM CHECKHEAP"				, "checks consistency of current heap allocations");
	zcon.Register		("ZSTARTRAIN"					, "starts outdoor rain effect [STRENGTH]");
	zcon.Register		("ZSTARTSNOW"					, "starts outdoor snow effect [STRENGTH]");
	zcon.Register		("ZSET VOBFARCLIPZSCALER"		, "adjusts far clipping plane for objects, 1 being default");
	zcon.Register		("ZSET LEVELFARCLIPZSCALER"		, "adjusts far clipping plane for static level mesh, 1 being default");
	zcon.Register		("ZHIGHQUALITYRENDER"			, "batch activation of high-quality render options: vob/level farClip, LevelLOD-Strength, Object-LOD, TexMaxSize");
 
	//
	//	CODECHANGE [ROMAN]
	//
	zcon.Register		("ZTIMER MULTIPLIER"			, "sets factor for slow/quick-motion timing");
	zcon.Register		("ZTIMER REALTIME"				, "resets factor for slow/quick-motion timing to realtime");
	//
	//	CODECHANGE [ROMAN] END
	//

	// tmp
	zcon.Register		("ZFOGZONE"						, "inserts test fog-zones");

	zcon.AddEvalFunc	(ConsoleEval);
	zrenderMan.InitRenderManager					();
	zCMapDetailTexture		::S_Init				();
	zCVisual				::InitVisualSystem		();
	zCVob					::InitVobSystem			();
	zCLensFlareFX			::LoadLensFlareScript	();
	zCVobLight				::LoadLightPresets		();
	zCDecal					::CreateDecalMeshes		();
	zCParticleFX			::InitParticleFX		();
	zCProgMeshProto			::InitProgMeshProto		();

	zCRayTurboAdmin::SetPolyTreshold( zoptions->ReadInt("ENGINE", "zRayTurboPolyTreshold", zCRayTurboAdmin::GetPolyTreshold()) );
}

void zDieter_ShutDown()
{
	zCRenderLightContainer	::S_ReleaseVobLightRefs	();
	zCProgMeshProto			::CleanupProgMeshProto	();
	zCParticleFX			::CleanupParticleFX		();
	zCDecal					::CleanupDecals			();
	zCVobLight				::CleanupVobLight		();
	zCLensFlareFX			::ReleaseLensFlareScript();
	zCVob					::CleanupVobSystem		();
	zCVisual				::CleanupVisualSystem	();
	zCMapDetailTexture		::S_Cleanup				();
	zrenderMan.CleanupRenderManager					();		// muss VOR dem zrenderer delete !
	// Hier vor dem Runterfahren des Renderers und des SoundSystems (also der Resourcen-verwaltenen Systemen)
	// den Resource-Manager anweisen, alle cacheIn Requests zu vergessen. Sonst koennte auch nach dem Runterfahren von
	// Rnd/Sound noch etwas in der Queue sein, was auf 0Ptr zugreift.
	zERR_ASSERT (zresMan);
	zresMan->PurgeCaches	();
	delete zsndMan;		zsndMan		=0;
	delete zrenderer;	zrenderer	=0;
	delete zsound;		zsound		=0;
}

void zDieter_ShutDown_Fast()
{
	zrenderMan.CleanupRenderManager	();		// muss VOR dem zrenderer delete !
	//zresMan->PurgeCaches();
	//delete zsndMan;		zsndMan		=0;
	//delete zrenderer;	zrenderer	=0;
	//delete zsound;		zsound		=0;
}



/*
	'*' means that I added a feature.
	'!' means that it's only an idea.
	'-' means that I removed a 'feature' or dropped an idea.
	'+' means that I fixed something.
	' ' just a note.
	
	When I accomplish something, I write a * line that day.
	Whenever a bug / missing feature is mentioned during the day and I don't fix
	it, I make a note of it.  Some things get noted many times before they get
	fixed.
	Occasionally I go back through the old notes and mark with a + the things
	I have since fixed.
*/
