/******************************************************************************** 
 
     $Workfile:: zWorld.cpp           $                $Date:: 24.04.01 17:34   $
     $Revision:: 85                   $             $Modtime:: 23.04.01 19:54   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zWorld.cpp $
 * 
 * 85    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 84    19.03.01 21:31 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 83    18.03.01 18:49 Edenfeld
 * Demo Geschichten
 * 
 * 82    15.03.01 2:17 Hildebrandt
 * 
 * 81    16.02.01 21:29 Hildebrandt
 * 
 * 80    9.02.01 15:14 Moos
 * 
 * 79    9.02.01 13:24 Moos
 * 
 * 78    9.02.01 2:35 Hildebrandt
 * 
 * 77    8.02.01 19:08 Moos
 * 
 * 76    8.02.01 14:53 Moos
 * 
 * 75    8.02.01 12:12 Speckels
 * 
 * 74    8.02.01 6:54 Hildebrandt
 * 
 * 73    7.02.01 18:30 Hildebrandt
 * 
 * 72    5.02.01 19:13 Hildebrandt
 * 
 * 70    2.02.01 5:24 Hildebrandt
 * 
 * 69    1.02.01 19:26 Speckels
 * 
 * 68    1.02.01 5:22 Hildebrandt
 * 
 * 67    31.01.01 17:48 Moos
 * 
 * 66    27.01.01 19:42 Moos
 * 
 * 65    26.01.01 21:16 Hildebrandt
 * 
 * 64    26.01.01 21:04 Hildebrandt
 * 
 * 63    23.01.01 21:00 Hildebrandt
 * 
 * 62    19.01.01 0:13 Hildebrandt
 * 
 * 61    18.01.01 18:01 Speckels
 * 
 * 60    18.01.01 0:33 Speckels
 * 
 * 59    17.01.01 20:24 Speckels
 * 
 * 58    15.01.01 21:28 Hildebrandt
 * 
 * 57    15.01.01 14:28 Moos
 * 
 * 56    11.01.01 21:09 Hildebrandt
 * 
 * 55    6.12.00 18:35 Hildebrandt
 * 
 * 54    4.12.00 18:23 Moos
 * 
 * 53    29.11.00 12:53 Speckels
 * 
 * 52    25.11.00 3:32 Hildebrandt
 * 
 * 51    22.11.00 20:06 Hildebrandt
 * 
 * 50    22.11.00 19:14 Hildebrandt
 * 
 * 49    22.11.00 4:13 Hildebrandt
 * 
 * 48    17.11.00 19:29 Moos
 * 
 * 47    17.11.00 1:28 Hildebrandt
 * 
 * 46    9.11.00 19:35 Hildebrandt
 * 
 * 45    8.11.00 18:16 Hildebrandt
 * 
 * 44    7.11.00 18:24 Hildebrandt
 * 
 * 43    7.11.00 17:24 Hildebrandt
 * 
 * 42    3.11.00 19:03 Hildebrandt
 * 
 * 41    3.11.00 17:50 Hildebrandt
 * 
 * 40    26.10.00 17:45 Speckels
 * 
 * 39    25.10.00 15:07 Hildebrandt
 * 
 * 38    18.10.00 15:17 Speckels
 * 
 * 37    18.10.00 13:12 Speckels
 * 
 * 36    17.10.00 16:29 Hildebrandt
 * 
 * 35    5.10.00 22:25 Hildebrandt
 * 
 * 34    5.10.00 17:20 Moos
 * 
 * 33    29.09.00 21:20 Moos
 * 
 * 32    28.09.00 15:15 Hildebrandt
 * 
 * 31    23.09.00 18:12 Moos
 * 
 * 30    21.09.00 20:58 Moos
 * 
 * 29    21.09.00 17:57 Hoeller
 * 
 * 28    15.09.00 16:44 Hildebrandt
 * 
 * 27    11.09.00 19:51 Hildebrandt
 * 
 * 26    7.09.00 20:42 Hildebrandt
 * 
 * 25    1.09.00 18:01 Hildebrandt
 * 
 * 24    29.08.00 18:22 Hildebrandt
 * zCZone::Process..() gets called even if there is just a default zone in
 * the world
 * 
 * 23    23.08.00 17:31 Hildebrandt
 * zengin 0.92i
 * 
 * 22    22.08.00 19:47 Hildebrandt
 * 
 * 21    21.08.00 17:18 Hildebrandt
 * 
 * 20    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 19    31.07.00 19:18 Speckels
 * 
 * 18    21.07.00 15:12 Hildebrandt
 * 
 * 17    21.07.00 14:28 Hildebrandt
 * 
 * 16    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 15    6.07.00 13:45 Hildebrandt
 * 
 * 11    9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 10    8.05.00 20:30 Hildebrandt
 * 
 * 9     8.05.00 20:23 Hildebrandt
 * 
 * 8     8.05.00 18:17 Hildebrandt
 * zenGin 089g
 * 
 * 7     8.05.00 5:30 Hildebrandt
 * zenGin 089g
 * 
 * 6     8.05.00 2:18 Hildebrandt
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 19    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 18    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 17    23.02.00 1:19 Hildebrandt
 * 
 * 16    22.02.00 19:53 Hildebrandt
 * 
 * 15    22.02.00 19:38 Hildebrandt
 * MergeVobSubtree() now links to the correct parentVob
 * 
 * 14    22.02.00 2:02 Hildebrandt
 * zenGin 087d
 * 
 * 13    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 11    14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 10    11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 9     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 7     16.11.99 21:03 Hildebrandt
 * 
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 85 $ ($Modtime: 23.04.01 19:54 $)


#include <zCore.h>
#include <zWorld.h>
#include <z3d.h>
#include <zRenderer.h>
#include <zFile3d.h> 
#include <zOption.h>
#include <zWaynet.h>
#include <zSound.h>
#include <zParticle.h>
#include <zSky.h>
#include <zArchiver.h>
#include <zAI.h>
#include <zEventMan.h>
#include <zView.h>
#include <zViewProgressBar.h>
#include <zCcsplayer.h>
#include <zCcsmanager.h>
#include <zSession.h>
#include <zRayCache.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zSparseArray.h>
#include <zVertexBuffer.h>
#include <zRenderLightContainer.h>
#include <zFFT.h>
#include <zAccount.h>
#include <zProgMesh.h>

#ifdef COMPILING_GOTHIC
#include "oWorld.h"
#endif

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

#ifdef ZENGINE_DEBUG
//	#define zWLD_DONT_CONVERT_TRIS_2_NPOLYS
#endif

zCLASS_DEFINITION (zCWorld, zCObject, 0, 1)

///////////////////////////////////////////////////////////////////////////
//     World
///////////////////////////////////////////////////////////////////////////

// static element defs

// persistance
static	zCVob							*s_firstVobMergeVobSubtree		= 0;
static	zCTree<zCVob>					*s_firstVobSaveWorld			= 0;
static	zCTree<zCVob>					*s_unarcTraverseVobsFirstParent	= 0;
static	zBOOL							s_saveLevelMesh;
static	zBOOL							s_saveWayNet;
static	int								s_iVobsKilled					= 0;
static	int								s_iPolysAdded					= 0;

// FIXME: should be member of zCWorld!
zSTRING							s_worldFileName;
extern	zBOOL					s_bAddVobsToMesh;
	

zCWorld::zTWorldLoadMode		zCWorld::s_worldLoadMode;
zCWorld::zTWorldSaveMode		zCWorld::s_worldSaveMode;
zCWorld::zTWorldLoadMergeMode	zCWorld::s_worldMergeMode;

zBOOL zCWorld::s_bFadeOutFarVerts		= TRUE;
zBOOL zCWorld::s_bWaveAnisEnabled		= TRUE;
zBOOL zCWorld::s_bAmbientVobsEnabled	= TRUE;
zBOOL zCWorld::s_bEnvMappingEnabled		= TRUE;
zBOOL zCWorld::showTextureStats			= FALSE;


#ifdef COMPILING_SPACER
zBOOL zCWorld::s_bAlternateRenderOrder	= FALSE;
#else
zBOOL zCWorld::s_bAlternateRenderOrder	= FALSE;
#endif


/*	------------------------------------------------------------------

	constructor zCWorld

	26.07.00	[Speckels]
				ownerSession initialisiert

	17.04.01	[EDENFELD]
				Kastration für Gothic Demos mit Präprozessor Direktiven
				hinzugefügt
	------------------------------------------------------------------ */

zCWorld::zCWorld() : activeVobList(128) 
{ 
	masterFrameCtr			= 0;
	compiled				= FALSE;
	compiledEditorMode		= FALSE;
	vobFarClipZ				= 5000;
	vobFarClipZScalability	= zREAL(1.0F);
	showZonesDebugInfo		= FALSE;
	showTraceRayLines		= FALSE;
	showWaynet				= FALSE;
	renderingFirstTime		= TRUE;
	cbspTree				= 0;
	progressBar				= 0;
	unarchiveFileLen		= 0;
	unarchiveStartPosVobtree= 0;
	ownerSession			= 0;
	csPlayer				= 0;
	numVobsInWorld			= 0;
	wayNet					= zNEW(zCWayNet(this));
	
	// im Spacer sollen Zones als Vobs eingefügt & sichtbar sein
#ifdef COMPILING_SPACER
	addZonesToWorld			= TRUE;
#else						
	addZonesToWorld			= FALSE;
#endif						
							
#ifdef ZENGINE_DEBUG		 
//	addZonesToWorld			= TRUE;
//	showZonesDebugInfo		= TRUE;
#endif

	// FIXME: dieses nicht hier festlegen, sondern extern einstellbar machen
	// FIXME: lazy erzeugen?
	skyControlerIndoor		= 0;
	skyControlerOutdoor		= 0;

	SetSkyControlerIndoor	(zNEW(zCSkyControler_Indoor()));

#ifdef ZENGINE_DEBUG
	SetSkyControlerOutdoor	(zNEW(zCSkyControler_Outdoor(TRUE)));
#else
	SetSkyControlerOutdoor	(zNEW(zCSkyControler_Outdoor()));
#endif

	activeSkyControler		= GetActiveSkyControler();

	traceRayIgnoreVobFlag	= FALSE;
	m_bIsInventoryWorld		= FALSE;

//	SetWorldRenderMode		(zWLD_RENDER_MODE_VERT_LIGHT);	
	SetWorldRenderMode		(zWLD_RENDER_MODE_LIGHTMAPS);

    zoneBoxSorter.InsertHandle(zoneActiveHandle); // [Moos]

	// .ini auswerten
	{
		static zREAL vobFarZFromINI			= zREAL(-1.0F);
		if (vobFarZFromINI<=0)
		{
			vobFarZFromINI					= zoptions->ReadReal ("ENGINE", "zVobFarClipZScale", 4);
			zClamp							(vobFarZFromINI, zREAL(0.0001F), zREAL(9999999.0F));
			this->SetVobFarClipZScalability(zLerp(vobFarZFromINI/14.0f, 0.4f, 3.5f));
			this->SetFadeOutFarVertices		( zoptions->ReadBool("ENGINE", "zFarClipAlphaFade",TRUE) );
			this->SetWaveAnisEnabled		( zoptions->ReadBool("ENGINE", "zWaterAniEnabled",TRUE) );
#ifdef COMPILING_SPACER
			this->SetWaveAnisEnabled		( zoptions->ReadBool("SPACER", "zSpacerWaterAniEnabled",FALSE) );
#endif

		};
	};

};


/*	------------------------------------------------------------------

	destructor zCWorld

	26.07.00	[Speckels]
				ownerSession initialisiert

	------------------------------------------------------------------ */

zCWorld::~zCWorld() 
{
	DisposeWorld();

	zRELEASE				(wayNet);
	zRELEASE				(csPlayer);
	SetSkyControlerIndoor	(0);
	SetSkyControlerOutdoor	(0);
	zCPolygon::S_DeleteMorphedVerts	();

	delete cbspTree;		cbspTree=0;	
	activeSkyControler		= 0;
	ownerSession			= 0;	
};

zCSkyControler* zCWorld::GetActiveSkyControler () 
{ 
	if (bspTree.GetBspTreeMode()==zBSP_MODE_INDOOR)	activeSkyControler=skyControlerIndoor;
	else											activeSkyControler=skyControlerOutdoor;
	return activeSkyControler; 
};


void zCWorld::SetSkyControlerIndoor (zCSkyControler* s)		
{ 
	if (skyControlerIndoor==s)	return;
	if (skyControlerIndoor)		zRELEASE_ACCT_NONULL(skyControlerIndoor);
	skyControlerIndoor			= s; 
};

void zCWorld::SetSkyControlerOutdoor (zCSkyControler* s) 
{
	if (skyControlerOutdoor==s) return;
	if (skyControlerOutdoor)	zRELEASE_ACCT_NONULL(skyControlerOutdoor);
	skyControlerOutdoor			= s; 
};

void zCWorld::RenderWaynet (zCCamera *camera)
{
	if ((GetShowWaynet()) && (GetWayNet())) GetWayNet()->Draw (camera);
};

// ========================
//	ZONES
// ========================

int zCWorld::ActiveZoneListCompare (const void* ele1,const void* ele2) 
{
	if ((*((zCZone**)ele1))->GetZoneMotherClass()<((*(zCZone**)ele2))->GetZoneMotherClass())	return -1;
	if ((*((zCZone**)ele1))->GetZoneMotherClass()>((*(zCZone**)ele2))->GetZoneMotherClass())	return +1;
	else																						return  0;
};

void zCWorld::AddZone (zCZone* zone) 
{
	if (!zone) return;
	if (zoneGlobalList.IsInList(zone))	return;

	// defaults sind vorne in Liste, die anderen dahinter
	if (zone->IsDefaultZone())	
	{
		zoneGlobalList.InsertFront	(zone);

		#ifdef COMPILING_SPACER
			// Nur im Spacer ein Test auf deppelte Default-Zones..
			zCClassDef *inZoneClassDef = zone->GetClassDef();
			for (int i=0; i<zoneGlobalList.GetNum(); i++)
			{
				if (zoneGlobalList[i]->GetClassDef()==inZoneClassDef)
				{
					#ifdef COMPILING_SPACER
						zERR_WARNING ("D: WLD: Just ONE default zone allowed per world of class: "+inZoneClassDef->GetClassName_());
					#else
						zERR_FAULT   ("D: WLD: Just ONE default zone allowed per world of class: "+inZoneClassDef->GetClassName_());
					#endif
					break;
				};
			};
		#endif
	} else {
		zoneGlobalList.InsertEnd	(zone);
		zoneBoxSorter.Insert		(zone);//, zone->GetBBox3DWorld());
	};
};

void zCWorld::RemoveZone (zCZone* zone) 
{
	if (!zone) return;
	// defaults sind vorne in Liste, die anderen dahinter
	if (zone->IsDefaultZone())	{ 
		zoneGlobalList.RemoveOrder	(zone);
	} else {
		zoneGlobalList.Remove		(zone);
		zoneBoxSorter.Remove		(zone);
	};
	zoneLastClassList.Remove		(zone);
	zoneActiveList.Remove			(zone);
};

void zCWorld::RemoveAllZones () 
{
	zoneBoxSorter.Clear();
	for (int i=0; i<zoneGlobalList.GetNum(); i++) {
		zoneGlobalList[i]->ThisVobRemovedFromWorld	(this);		// FIXME: noetig?
//		zoneGlobalList[i]->RemovedZoneFromWorld		(this);
	};
	zoneActiveList		.EmptyList();
	zoneLastClassList	.EmptyList();
	zoneGlobalList		.EmptyList();
	zoneBoxSorter		.Clear();
};

void zCWorld::UpdateZone (zCZone* zone) 
{
	// zoneBoxSorter.Update() fuehrt statt der gesamten Neusortierung ein gezieltes Update der internen ZoneListen durch..
	zoneBoxSorter.Update		(zone);//, zone->GetBBox3DWorld());

	// zoneActiveHandle updaten !!
//	zoneBoxSorter.GetActiveList		(zCCamera::activeCam->GetVob()->GetBBox3DWorld(), zoneActiveHandle, zoneActiveList);
};

void zCWorld::ProcessZones () 
{
	// vorm durchgehen der fogzones melden wir dem skycontroler, dass keine override fog farben aktiv sind
	// (muss, ansonsten bleibt vielleicht die letzte farbe der letzten fogzone aktiv)
	GetActiveSkyControler()->SetOverrideColorFlag(FALSE);		
	GetActiveSkyControler()->SetGlobalSkyScale	 (1);

	// Zones updaten
	zTBBox3D tmpBox					= zCCamera::activeCam->GetVob()->GetBBox3DWorld();
	tmpBox.maxs = tmpBox.mins		= zCCamera::activeCam->GetVob()->GetPositionWorld();
	if (!zoneBoxSorter.IsSorted()) 
	{
		zoneBoxSorter.GetActiveList		(tmpBox, zoneActiveHandle, zoneActiveList);
//		zoneBoxSorter.GetActiveList		(zCCamera::activeCam->GetVob()->GetBBox3DWorld(), zoneActiveHandle, zoneActiveList);
	} else 
	{
//		zoneBoxSorter.GetActiveList		(tmpBox, zoneActiveHandle, zoneActiveList);
		zoneBoxSorter.UpdateActiveList	(tmpBox, zoneActiveHandle, zoneActiveList);
//		zoneBoxSorter.GetActiveList		(zCCamera::activeCam->GetVob()->GetBBox3DWorld(), zoneActiveHandle, zoneActiveList);
//		zoneBoxSorter.UpdateActiveList	(zCCamera::activeCam->GetVob()->GetBBox3DWorld(), zoneActiveHandle, zoneActiveList);
	};

	zoneActiveList.SetCompare			(ActiveZoneListCompare);
	zoneActiveList.QuickSort			();

	// [A] Hier werden erstmal alle Default-Zones der Welt in einer extra Liste gesammelt. Beim Erstellen der Zonenlisten
	// wird dann fuer jede Zonenliste dessen Defaultzone (falls vorhanden) aus dieser Liste entfernt (falls vorhanden).
	// Am Ende sollten dann also in dieser Liste alle Default-Zones üeber bleiben, zu denen keine nicht-Default Zonen
	// existieren. Diese bekommen dann noch extra einen Process-Aufruf mit leeren Listen.
	zCArray<zCZone*> zoneDefaultList;
	for (int i=0; i<zoneGlobalList.GetNum(); i++)
	{
		if (zoneGlobalList[i]->IsDefaultZone())		zoneDefaultList.Insert (zoneGlobalList[i]);
		else										break;
	};

	{
		// Die ZoneListen dieses Frames und des letzten Frames werden parallel durchlaufen. Dabei werden Listen
		// von Zonen derselben Klasse erstellt. Sobald 2 Listen fuer eine Klasse erstellt sind, wird aus der 
		// zweiten eine Differenz-Liste gemacht (also Zones, die letzten frame aktiv waren, es diesen aber nicht
		// mehr sind). Dann wird der Klasse die beiden Listen zur Bearbeitung übergeben.

		// 0 = workList
		// 1 = lastList
		int						i[2];				i[0]=i[1]=0;
		zCClassDef				*actClass[2];
		zCClassDef				*NO_CLASS	= (zCClassDef*)0xFFFFFFFF;
		zCArraySort<zCZone*>	zoneResList[2];
		zCArraySort<zCZone*>*	zoneList[2];
		zoneList[0] = &zoneActiveList;
		zoneList[1] = &zoneLastClassList;

		do
		{
			for (int j=0; j<2; j++){
				zoneResList[j].EmptyList();
				actClass[j]=NO_CLASS;
				if (i[j]<zoneList[j]->GetNum())	actClass[j] = zoneList[j]->Get(i[j])->GetZoneMotherClass();
			};
			if (actClass[0]==actClass[1])
			{
				// Abbruch, wenn beide Klassen=0xFFFFFFFF sind, d.h. beide Listen abgearbeitet sind.
				if (actClass[0]==NO_CLASS)	break;
				for (int j=0; j<2; j++) 
				{
					while ((i[j]<zoneList[j]->GetNum()) && (zoneList[j]->Get(i[j])->GetZoneMotherClass()==actClass[j]))
					{
						zoneResList[j].Insert (zoneList[j]->Get(i[j]));
						i[j]++;
					};
					zoneResList[j].QuickSort();		// das folgende 'IsInList' erwartet eine sortierte Liste
				};
				// Zones rausfiltern, die den letzten Frame aktiv waren, es diesen aber nicht mehr sind
				for (int k=0; k<zoneResList[1].GetNum(); k++)
				{
					if (zoneResList[0].IsInList(zoneResList[1].Get(k))) {
						zoneResList[1].RemoveIndex (k);
						k--;
					};
				};
			} else
			if (actClass[0]<actClass[1]) {
				// Liste 0 zuerst & ohne Liste 2 abarbeiten
				int j=0;
				while ((i[j]<zoneList[j]->GetNum()) && (zoneList[j]->Get(i[j])->GetZoneMotherClass()==actClass[j]))
				{
					zoneResList[j].Insert (zoneList[j]->Get(i[j]));
					i[j]++;
				};
			} else {
				// Liste 2 zuerst & ohne Liste 1 abarbeiten
				int j=1;
				while ((i[j]<zoneList[j]->GetNum()) && (zoneList[j]->Get(i[j])->GetZoneMotherClass()==actClass[j]))
				{
					zoneResList[j].Insert (zoneList[j]->Get(i[j]));
					i[j]++;
				};
			};

			// Zones dieser Klasse bearbeiten lassen
			{
				zCZone *callZone;
				if (zoneResList[0].GetNum()>0)	callZone= zoneResList[0].Get(0); else
				if (zoneResList[1].GetNum()>0)	callZone= zoneResList[1].Get(0);
				callZone ->ProcessZoneList				(zoneResList[0], zoneResList[1], this);

				// siehe [A] oben
				zERR_ASSERT (!callZone->IsDefaultZone());
				zCClassDef *callZoneDefaultClassDef		= callZone->GetDefaultZoneClass();
				if (callZoneDefaultClassDef)
				{
					for (int i=0; i<zoneDefaultList.GetNum(); i++)
						if (zoneDefaultList[i]->GetDefaultZoneClass()==callZoneDefaultClassDef)
						{
							zoneDefaultList.RemoveIndex (i);
							break;
						};
				};
			};

		} while (1);

		// siehe [A] oben
		{
			zoneResList[0].EmptyList();
			zoneResList[1].EmptyList();
			for (int i=0; i<zoneDefaultList.GetNum(); i++)
			{
				zERR_ASSERT (zoneDefaultList[i]->IsDefaultZone());
				zoneDefaultList[i]->ProcessZoneList (zoneResList[0],zoneResList[1], this);	// es wird hier mit _leeren_ Listen aufgerufen!
			};
		};
	};

	//
	zoneLastClassList = zoneActiveList;
};

																																							const char *tocotronic = "Gothic, wie es anfing: Ausgangspunkt des Projektes waren Ulf und Dieter, die sich nach dem Durchzocken der unglaublichen Ultima Underworld 1 und 2 in den Kopf gesetzt hatten, ein aehnlich cooles 3D Action Rollenspiel zu schreiben (war das nun 1994 oder 1995??). Als wir ein gutes Stueck (> 1 Jahr) allein gearbeitet hatten, und mittlerweile auch Bert zu uns gestossen war, machten wir uns auf, mit Firmen Kontakt aufzunehmen, um uns bei der Entwicklung unterstuetzen zu lassen, insbesondere durch Grafiker. Angebote von Firmen waren zahlreich (u.a. Sunflowers und Attic), schliesslich haben wir uns fuer Greenwood (spaeter halt PiranhaBytes) entschieden. Zu diesem Zeitpunkt war von den jetzigen Piranhas allein Alex Brueggemann bei Greenwood angestellt. Nyul, Hoge und Putzki wurden erst spaeter zur Verstaerkung des Teams eingestellt. Tja, etwas spaeter geschah dann schon die Spaltung Greenwoods und die Gruendung Piranha Bytes', und das Team wurde nach und nach aufgestockt. Der Rest ist Geschichte!!";

void zCWorld::ShowZonesDebugInfo() 
{
	if (!showZonesDebugInfo) return;

	zERR_MESSAGE (5, 0, "P: "+strlen(tocotronic));

	//
	zREAL time = GetActiveSkyControler()->GetTime()*24.0F + 12.0F;
	if (time>24.0F) time	-= 24.0F;

	zCCamera::activeCam->Activate();

	//
	int xpos = 0;
	int ypos = 1000;
	zSTRING s;
	screen->Print (xpos, ypos, "** Active Zones **     (time: "+zSTRING(time,3)+")");
	ypos += 250;
	for (int i=0; i<zoneActiveList.GetNum(); i++)
	{
		zCZone *zone = zoneActiveList[i];
		s = zone->GetClassName_() + ", ";
		if (!zone->GetVobName().IsEmpty())
		s += "\""+zone->GetVobName()+"\", ";
		s += zone->GetDebugDescString();
		screen->Print (xpos, ypos, s);
		ypos += 250;
		zone->GetBBox3DWorld().Draw ();
	};
};

// ***********************************************************************************************

void zCWorld::ShowTextureStats ()
{
	if (!zCWorld::GetShowTextureStats()) return;
	zTRnd_Stats stats;
	zrenderer->GetStatistics		(stats);
	screen->Print (0, 500, "mem: "+zSTRING(stats.texMemUsed   / 1000)+"k num: "+zSTRING(stats.numTexturesUsed)   +" (used), cardMem: "+zSTRING(zrenderer->GetTotalTextureMem()/1000)+"k");
	screen->Print (0, 700, "mem: "+zSTRING(stats.texMemFetched/ 1000)+"k num: "+zSTRING(stats.numTexturesFetched)+" (fetched)");
	// mem: 1323 num: 23 (used), cardMem: 32234k
	// mem: 1323 num: 1 (fetched)
	zrenderer->ResetStatistics	();
};


// ***********************************************************************************************

/* ----------------------------------------------------------------------
	zCWorld::Render
	28.07.2000	[Speckels]	
				Von Cutsceneplayer wird nun in jedem Frame die
				Process-Methode aufgerufen.

    17.11.2000  [Moos]
                kleine Anpassung an neue Vertex-Klassen

    19.01.2001  [HILDEBRANDT]
                cam.PreRenderProcessing() an die richtige stelle VOR dem cam.Activate()
				gerueckt => CamTremors sind nun auch wieder im Indoor sichtbar.

   ---------------------------------------------------------------------- */


void zCWorld::Render (zCCamera& cam) 
{
	// safety
	if ((&cam)==0)		return;
	if (!cam.GetVob())	return;
	if (cam.GetVob()->GetHomeWorld()!=this) return;	
	zBOOL mainRenderWorld = (!this->GetName().IsEmpty());

	// böser, böser gamecode, uarghhhh
#ifdef COMPILING_GOTHIC
	oCWorld *gameWorld = zDYNAMIC_CAST<oCWorld>(this);
	mainRenderWorld |= gameWorld && !gameWorld->worldFilename.IsEmpty();
#endif

#ifdef COMPILING_SPACER
	mainRenderWorld = TRUE;
#endif

	// [Moos] räumt die diversen Frame-To-Frame-Coherence-Caches frei
    zCCacheBase::S_PurgeCaches();

	// fft map updaten
	
	if (mainRenderWorld && zCWorld::GetWaveAnisEnabled())
	{
		zCFFT::S_SetFrameCtr(this->GetMasterFrameCtr());
	}

	// muss VOR dem cam.Activate()
	cam.PreRenderProcessing();

	// MUSS am Anfang: alles weitere erwartet eine gueltige 'zCCamera::activeCam' 
	cam.UpdateViewport	();							// Viewport Daten aus der zCView in die zCCamera uebertragen
	cam.Activate		();							// camMatrix & '::activeCam' wird hier gesetzt
 
	//
	GetActiveSkyControler()->Activate(); 

	if (renderingFirstTime)
	{
		zresMan->SetCacheInImmediately (1500.0F);		// die ersten n Sekunden lang alles sofort eincachen		
		renderingFirstTime				= FALSE;
	};

	if (mainRenderWorld) 
	{
		zsound->SetListener		(zCCamera::activeCam->GetVob());

		// Zones updaten
		// muss vorher: cam.Activate, SkyContrl.Activate

		ProcessZones();

		// Sound-Engine callen
		zsound->DoSoundUpdate	();
	}

	// Render-Vorgang starten
	// Innerhalb des Vorgangs sollten keine Vobs/Visuals geloescht werden
	zCPolygon::PrepareRendering	();

	// FIXME: *vor* Render ?
	// Beachte: MoveVobs() koennte Vobs loeschen, die in der GetNearestVisVobsR() bzw. renderVobList enthalten sind !!!

	// render Static World
	// render Dynamic Objects
	bspTree.vobFarClipZ		= GetVobFarClipZ();
	bspTree.Render			();

	cam.PostRenderProcessing();

	// Render-Vorgang abschliessen
	zrenderer->FlushPolys	();

	zCPolygon::S_ResetMorphedVerts();

	if (mainRenderWorld)
	{

		zlineCache.Flush		(cam.targetView);

		// debug infos
		RenderWaynet			(&cam);					// debug info
		ShowZonesDebugInfo		();
		ShowTextureStats		();
	}

	// Vobs bewegen: Physik, Model-Ani-Movement, AI
	// Hier koennten Vobs/Visuals geloescht werden

	// FIXME: TEMP
	cam.Activate();							// camMatrix wird hier gesetzt 
	MoveVobs ();	

	// - camMatrix   : world(obj)Space => camSpace
	// - camMatrixInv: camSpace		   => world(obj)Space

	if (mainRenderWorld)
	{
		zCEventManager			::DoFrameActivity	();
		zresMan					->DoFrameActivity	();
		if (csPlayer) csPlayer	->Process			(); // [Speckels]
		// PerFrameCallbackList abarbeiten
		for (int i=0; i<perFrameCallbackList.GetNum(); i++)
		{
			perFrameCallbackList[i]->DoWorldPerFrameCallback (this, &cam);
		};
	}


	masterFrameCtr++;
    zCVertex::ResetVertexTransforms(); // [Moos] Löscht auch alle transformierten Vertex-Daten

	zCTexAniCtrl::IncMasterFrameCtr (); 	

// FIXME: sollte eigentlich drin sein.....
//zCCamera::activeCam = 0;
};

// ***********************************************************************************************
//  zCWorld:: TRACE RAY
// ***********************************************************************************************

/*
  - unterscheiden zw.
	- compilierter Welt (Game)
		- statische Teil:
			- Der Strahl wird in den BSP-Tree geclippt.
			  BSP-Leaf		: der Teil des Strahls, der hier ankommt, ist ok
			  Octree-Leaf	: dieser Strahl-Teil muss noch gegen die enthaltenen Polys gecheckt werden.
			  Dabei werden alle in den Nodes/Leafs enthaltenen Vobs eingesammelt.
		- dynamischer Teil:
			- Die gesammelten Vobs aus dem stat. Teil werden gecheckt.
			  Entweder:
				- Ray-BBox-Check
				- Ray-Mesh-Check
	- nicht-compiliert Welt (Spacer)
		- .. derselbe Algo..
*/

// FIXME:	- Ray/BBox-Check, Ray/OBB, Ray/OBB-Tree

zBOOL zCCFASTCALL zCWorld::TraceRayFirstHit (const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList, int traceFlags) 
{
	// Stoppt bei dem ersten Hit.
	if (GetShowTraceRayLines())	zlineCache.Line3D (rayOrigin, rayOrigin+ray, GFX_LBLUE);

	//
	traceFlags	|= zTRACERAY_FIRSTHIT;
	traceRayVobList.EmptyList();

	traceRayReport.Clear();
	traceRayReport.foundHit			= bspTree.TraceRay (rayOrigin, rayOrigin+ray, 
														traceFlags,
														traceRayReport.foundIntersection, traceRayReport.foundPoly, 
														(traceFlags & zTRACERAY_VOB_IGNORE) ? 0 : &traceRayVobList);

	// (eigentlich sollte Bsp::TraceRay auch in diesem Fall immer FALSE zurueckliefern..)
	if ((traceFlags & zTRACERAY_STAT_IGNORE)!=0) traceRayReport.foundHit=FALSE;	// reset

	// statischer Hit ?
	if (traceRayReport.foundHit) {
		if ((traceFlags & zTRACERAY_POLY_NORMAL)!=0)	
		if (traceRayReport.foundPoly) {
			traceRayReport.foundPolyNormal = traceRayReport.foundPoly->GetNormal();
		};
		return TRUE;
	};

	// Vobs unberuecksichtigt lassen ?
	if ((traceFlags & zTRACERAY_VOB_IGNORE)!=0) return FALSE;

	// nun muessen noch alle Vobs gegen den Ray gecheckt werden !
	if (traceRayVobList.GetNum()<=0)	return FALSE;

	const zBOOL		ignoreCharacters	= (traceFlags & zTRACERAY_VOB_IGNORE_CHARACTER);
	const zBOOL		testHelperVisuals	= (traceFlags & zTRACERAY_VOB_TEST_HELPER_VISUALS);
	const zBOOL		ignoreProjectiles	= (traceFlags & zTRACERAY_VOB_IGNORE_PROJECTILES);

	for (int i=0; i<traceRayVobList.GetNum(); i++) 
	{
		zCVob* vob = traceRayVobList[i];
		zERR_ASSERT (vob);
		if (((vob->GetVisual()) && (vob->GetShowVisual())) || (testHelperVisuals && (!vob->GetVisual())))
		if ((traceRayIgnoreVobFlag) || (!vob->GetIgnoredByTraceRay()))
		{
			// ignoreList
			if (ignoreVobList)
			if (ignoreVobList->IsInList(vob)) goto nextOne;

			// ignore Characters ?
			if (ignoreCharacters)
			if (vob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NONE)
				goto nextOne;

			if (ignoreProjectiles)
				if (vob->GetIsProjectile())
					goto nextOne;
			//
			if ((traceFlags & zTRACERAY_VOB_IGNORE_NO_CD_DYN) &&
				(!vob->GetCollDetDyn())) goto nextOne;

			// Vob (inklusive Visual) sich selbst gegen Ray testen lassen
			if (vob->TraceRay (rayOrigin, ray, traceFlags, traceRayReport))
			{
				return TRUE;
			};
		
		};
nextOne:;
	};
	return FALSE;
};

zBOOL zCCFASTCALL zCWorld::TraceRayNearestHit (const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList, int traceFlags) 
{
	// Sucht den naechstliegendsten Hit.
	if (GetShowTraceRayLines())	zlineCache.Line3D (rayOrigin, rayOrigin+ray, GFX_BLUE);

	//
	traceRayVobList.EmptyList();

	// a) statischen BSP-Tree checken
	traceRayReport.Clear();
	traceRayReport.foundHit			= bspTree.TraceRay (rayOrigin, rayOrigin+ray, 
														traceFlags,
														traceRayReport.foundIntersection, traceRayReport.foundPoly, 
														(traceFlags & zTRACERAY_VOB_IGNORE) ? 0 : &traceRayVobList);

	// Vobs unberuecksichtigt lassen ?
	if ((traceFlags & zTRACERAY_VOB_IGNORE)!=0) goto leave;

	// (eigentlich sollte Bsp::TraceRay auch in diesem Fall immer FALSE zurueckliefern..)
	if ((traceFlags & zTRACERAY_STAT_IGNORE)!=0) traceRayReport.foundHit=FALSE;	// reset

	// keine Vobs gefunden ?
	if (traceRayVobList.GetNum()<=0)					goto leave;

	// Vobs testen
	{
		zTTraceRayReport	report;
		zTTraceRayReport	bestReport;
		zVALUE				bestDist			= zVALUE_MAX;

		bestReport.foundVob	= 0;
		if (traceRayReport.foundHit) {
			bestDist = (traceRayReport.foundIntersection-rayOrigin).Length2();
		};

		const zBOOL ignoreCharacters	= (traceFlags & zTRACERAY_VOB_IGNORE_CHARACTER)!=0;
		const zBOOL	testHelperVisuals	= (traceFlags & zTRACERAY_VOB_TEST_HELPER_VISUALS);
		const zBOOL	ignoreProjectiles	= (traceFlags & zTRACERAY_VOB_IGNORE_PROJECTILES);

		for (int i=0; i<traceRayVobList.GetNum(); i++) 
		{
			zCVob* vob = traceRayVobList[i];
			zERR_ASSERT (vob);
			if (((vob->GetVisual()) && (vob->GetShowVisual())) || (testHelperVisuals && (!vob->GetVisual())))
			if ((traceRayIgnoreVobFlag) || (!vob->GetIgnoredByTraceRay()))
			{
				// ignoreList
				if (ignoreVobList)
				if (ignoreVobList->IsInList(vob)) goto nextOne;

				// ignore Characters ?
				if (ignoreCharacters)
				if (vob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NONE)
					goto nextOne;

				if (ignoreProjectiles)
					if (vob->GetIsProjectile())
						goto nextOne;

				//
				if ((traceFlags & zTRACERAY_VOB_IGNORE_NO_CD_DYN) &&
					(!vob->GetCollDetDyn())) goto nextOne;

				// Vob (inklusive Visual) sich selbst gegen Ray testen lassen
				if (vob->TraceRay (rayOrigin, ray, traceFlags, report))
				{
					const zVALUE dist = (report.foundIntersection - rayOrigin).Length2();
					if (dist<bestDist) 
					{
						bestReport	= report;
						bestDist	= dist;
					}
					goto nextOne;
				};
			};
nextOne:;
		}; 
		if (bestReport.foundVob) {
			traceRayReport			= bestReport;
			traceRayReport.foundHit	= TRUE;
			traceRayReport.foundPoly= 0;
			// Achtung !! Inters ist im World-Space !!!
		};
	};

leave:;
	// PolyNormal erwuenscht ?
	if ( traceFlags & zTRACERAY_POLY_NORMAL) 
	if ( traceRayReport.foundHit)
	if ( traceRayReport.foundPoly) 
	if (!traceRayReport.foundVob)	
		traceRayReport.foundPolyNormal = traceRayReport.foundPoly->GetNormal();

	return traceRayReport.foundHit;
};

zBOOL zCCFASTCALL zCWorld::TraceRayFirstHit (const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob, int traceFlags) 
{
	if (!ignoreVob) return TraceRayFirstHit (rayOrigin, ray, (zCArray<zCVob*>*)0, traceFlags);
	else 
	{
		// (ATT: die Benutzung von 'traceRayTempIgnoreVobList' macht diese Methode nicht multiThreading faehig)
		traceRayTempIgnoreVobList.Insert	(ignoreVob);
		const zBOOL res = TraceRayFirstHit	(rayOrigin, ray, &traceRayTempIgnoreVobList, traceFlags);
		traceRayTempIgnoreVobList.EmptyList	();
		return res;
	};
};

zBOOL zCCFASTCALL zCWorld::TraceRayNearestHit	(const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob, int traceFlags) 
{
	if (!ignoreVob) return TraceRayNearestHit (rayOrigin, ray, (zCArray<zCVob*>*)0, traceFlags);
	else 
	{ 
		// (ATT: die Benutzung von 'traceRayTempIgnoreVobList' macht diese Methode nicht multiThreading faehig)
		traceRayTempIgnoreVobList.Insert	(ignoreVob);
		const zBOOL res = TraceRayNearestHit(rayOrigin, ray, &traceRayTempIgnoreVobList, traceFlags);
		traceRayTempIgnoreVobList.EmptyList	();
		return res;
	};
};


/* ----------------------------------------------------------------------
	
    TraceRay...Cache()	

	21.09.2000	[Moos]	
                Einfache Wrapper-Funktionen

   ---------------------------------------------------------------------- */

#define DISPLAYCOLOR_BASE GFX_DGREEN
#define DISPLAYCOLOR_ADD  GFX_RED

static inline void Visualize(const zCWorld *w, const zPOINT3& rayOrigin, const zPOINT3& ray){
   if (w->GetShowTraceRayLines()){
        int color = zCRayCache::LastTraceRayEffort()*512;
        if (color>255)
            color = 255;
    
    	zlineCache.Line3D (rayOrigin, rayOrigin+ray, DISPLAYCOLOR_BASE + DISPLAYCOLOR_ADD * color);
    }

    // FIXME: a) die Rays werden zweimal gezeichnet
    //        b) diese Funktion ist nicht gerade schön...
}

zBOOL zCCFASTCALL zCWorld::TraceRayFirstHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList	, int traceFlags, zCRayCache *cache){
    zCBspTree::SetRayCache(cache);
    zBOOL ret=TraceRayFirstHit(rayOrigin, ray, ignoreVobList, traceFlags);

    Visualize(this, rayOrigin, ray);

    return ret;
}

zBOOL zCCFASTCALL zCWorld::TraceRayFirstHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob						, int traceFlags, zCRayCache *cache){
    zCBspTree::SetRayCache(cache);
    zBOOL ret=TraceRayFirstHit(rayOrigin, ray, ignoreVob, traceFlags);

    Visualize(this, rayOrigin, ray);

    return ret;
}

zBOOL zCCFASTCALL zCWorld::TraceRayNearestHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, const zCArray<zCVob*> *ignoreVobList	, int traceFlags, zCRayCache *cache){
    zCBspTree::SetRayCache(cache);
    zBOOL ret=TraceRayNearestHit(rayOrigin, ray, ignoreVobList, traceFlags);

    Visualize(this, rayOrigin, ray);

    return ret;
}

zBOOL zCCFASTCALL zCWorld::TraceRayNearestHitCache		(const zPOINT3& rayOrigin, const zPOINT3& ray, zCVob *ignoreVob						, int traceFlags, zCRayCache *cache){
    zCBspTree::SetRayCache(cache);
    zBOOL ret=TraceRayNearestHit(rayOrigin, ray, ignoreVob, traceFlags);

    Visualize(this, rayOrigin, ray);

    return ret;
 }

zBOOL zCCFASTCALL zCWorld::PickScene (zCCamera& cam, int xscr, int yscr, zREAL rayLength)
{
	// Sucht den naechstliegendsten Hit.
	const zVALUE RAY_DIST = 600000.0F;
	// alle Vobs in der räumlichen Nähe durchlaufen.
	// - check, ob vob-center im Frustum ?
	// - check, ob vob-bbox/sphere im Frustum ?
	// - check, ob ray die bbox/sphere schneidet ?
	// - check, ob ray exakt ein vob-Poly trifft ?

	cam.Activate();									// FIXME: checken, welche 'activate' Aktionen wirklich noetig sind !!

	zPOINT3 ray00, ray, p;
	// create ray00, ray by backprojection
	// ray00, ray sind im world(obj)Space
	// 'ray00	= cam.camMatrixInv * zPOINT3(0,0,0);'  =
	cam.camMatrixInv.GetTranslation( ray00 );
	p.n[VZ] = RAY_DIST;  
	cam.BackProject	(xscr, yscr, p);				// p im camSpace
	p		= cam.camMatrixInv * p;					// p im world(obj)Space  
	ray		= p - ray00;

	// wuenscht der Benutzer eine bestimmte Ray-Laenge?
	if (rayLength>0)
	{
		ray.Normalize();
		ray *= rayLength;
	};

	traceRayReport.Clear	();
	traceRayIgnoreVobFlag	= TRUE;
	int	traceFlags			= zTRACERAY_STAT_POLY		| 
							  zTRACERAY_POLY_TEST_WATER;

	// Nur falls HelperVisuals auch dargestellt werden, sollen diese beim TraceRay getestet werden
	if (zCVob::GetShowHelperVisuals())
		traceFlags		   |= zTRACERAY_VOB_TEST_HELPER_VISUALS;

	const zBOOL hit			= TraceRayNearestHit (ray00, ray, (zCVob*)0, traceFlags); 
	traceRayIgnoreVobFlag	= FALSE;

	if (hit) 
	if (traceRayReport.foundPoly)
	if (!traceRayReport.foundVob)
	{
		// foundVertex, only static geom
		// nearest vertex finden
		zCPolygon	*poly	= traceRayReport.foundPoly;
		zREAL		best	= zREAL_MAX;
		for (int i=0; i<poly->polyNumVert; i++)
		{
			zCVertex	*vert	= poly->GetVertexPtr(i);
			zREAL		dist	= (vert->position-traceRayReport.foundIntersection).Length2();
			if (dist<best) {
				best						= dist;
				traceRayReport.foundVertex	= vert;
			};
		};
	};

	return hit;
};


// ***********************************************************************************************
//  zCWorld :: BSP
// ***********************************************************************************************

zBOOL zCWorld::TraverseBsp (zCCBspTree *bspTree, zCTree<zCVob> *node, const zBOOL removeLevelCompos) 
{
	if (node==0) return FALSE;
	
	// Process Vob
	zBOOL levelMeshFound = FALSE;
	zCVob *vob = node->GetData();
	if (vob)
	if (dynamic_cast<zCVobLevelCompo*>(vob))
	if (vob->GetVisualClass	()==zCMesh::GetStaticClassDef())
	{
		zCTree<zCVob>*	parent;
		zCVob*			parentVob;

		parent		= node->GetParent();
		parentVob	= parent->GetData();
//		if (parentVob!=0) vob->trafoObjToWorld = parentVob->trafoObjToWorld * vob->trafo;
//		else			  vob->trafoObjToWorld = vob->trafo;

		zCMesh *levelMesh = dynamic_cast<zCMesh*>(vob->GetVisual());
		if (levelMesh)
		{
			bspTree->AddMesh (levelMesh, vob->trafoObjToWorld);
			levelMeshFound = TRUE;
		}
	}
	
	// Process childs
	zCTree<zCVob>* child = node->GetFirstChild();
	while (child) {
		// Wenn der gerade bearbeitete Node gelöscht wurde, wird in der aktuellen Liste wieder
		// von vorne begonnen, da sich diese geändert haben kann !
		if (TraverseBsp (bspTree, child, removeLevelCompos)==TRUE)	child = node->GetFirstChild();
		else														child = child->GetNextChild();
	};
	
	// Wenn es eine Level-Komponente war: 
	// vob (& dessen Mesh) löschen, den dranhängenden Subtree an den Parent des Vobs hängen
	zBOOL deletedThis = FALSE;
	if (vob)
//	if (vob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT) 
	if (dynamic_cast<zCVobLevelCompo*>(vob))
	{
		if (removeLevelCompos) {
			// lösche Vob-Knoten aus globalVobTree
			// lösche Vob aus BSP-Tree
			// lösche Vob
			// - Vob muss aus World 'removed' werden, ein Release() alleine wuerde den Vob nicht
			//   ordnungsgemaess aus der Welt entfernen, wenn dieser nach dem Remove weiter existiert.
			deletedThis = TRUE;
			RemoveVob (vob);
		} else {
			vob->SetShowVisual (FALSE);
			// meshVisual->CacheOut();
		};
	};
	return deletedThis;
}; 


zBOOL zCWorld::TraverseBspAddVobsToMesh(zCCBspTree *bspTree, zCTree<zCVob> *node) 
{
	if (node==0) return FALSE;
	
	// Process Vob
	zCVob *vob = node->GetData();
	zBOOL vobOutsideSector = TRUE;
	zBOOL mustRemove	   = FALSE;

	if (vob)
	{
		if (vob->GetClassDef()==zCVob::GetStaticClassDef()				&&
//			vob->GetCollDetDyn()										&&
//			vob->GetCollDetStat()										&&
			vob->GetStaticVob()											&&
			vob->GetVisualClass()==zCProgMeshProto::GetStaticClassDef()	&&
			vob->GetVobType()==zVOB_TYPE_NORMAL							&&
			vob->GetVisualAniMode()==zVISUAL_ANIMODE_NONE)
		{
			vob->CalcGroundPoly();
			if (vob->GetGroundPoly() && vob->GetGroundPoly()->GetSectorFlag()) vobOutsideSector = FALSE;

			if (vobOutsideSector)
			{
				zCProgMeshProto *levelProgMesh = dynamic_cast<zCProgMeshProto*>(vob->GetVisual());
				zCMesh			*levelMesh	   = levelProgMesh ? levelProgMesh->GetMesh(0) : NULL;

				if (levelMesh)
				{
					if (levelMesh->numPoly<170)
					{
						// folgende strategie für vobs die das noCollDetDyn Flag gesetzt haben
						// alle materialien des meshes durchgehen.
						// hat das material das noCollDetFlag gesetzt, so lassen
						// hat es das noCollDetFlag _nicht_ gesetzt: neues Material mit Prefix "VOB_" erzeugen, und dieses
						// mit noCollDet Flag versehen, damit nicht versehentlich andere Polys in der Welt mit diesem Mat
						// keine Coll mehr haben 
						if (!vob->GetCollDetDyn())
						{
							zCArray<zCMaterial*> materialList;
							for (int i=0; i<levelMesh->numPoly; i++)
							{
								if (!materialList.IsInList(levelMesh->SharePoly(i)->GetMaterial()))
									materialList.InsertEnd(levelMesh->SharePoly(i)->GetMaterial());
							}

							for (i=0; i<materialList.GetNum(); i++)
							{
								zCMaterial *mat = materialList[i];
								if (mat->GetNoCollDet()) continue;
								// so dieses Material muss kopiert werden und alle polys die dieses material besitzen müssen ein neues bekommen
								zSTRING newMatName	= "VOB_"+ mat->GetName();
								zCMaterial *newMat  = zCMaterial::SearchName(newMatName);
								if (!newMat)
								{
									newMat	= zNEW(zCMaterial)(*mat);
									newMat->SetName(newMatName);
								}
								newMat->SetNoCollDet(TRUE);

								for (int p=0; p<levelMesh->numPoly; p++)
								{
									if (levelMesh->SharePoly(p)->GetMaterial()==mat) levelMesh->SharePoly(p)->SetMaterial(newMat);
								}

								zRELEASE(newMat);
							}

							materialList.DeleteList();
						}


						bspTree->AddMesh (levelMesh, vob->trafoObjToWorld);
						s_iVobsKilled ++;
						s_iPolysAdded += levelMesh->numPoly;
						mustRemove = TRUE;
					}

					levelMesh->DeleteAll();
					zRELEASE(levelMesh);
				}
			};
		};

	};
	
	// Process childs
	zCTree<zCVob>* child = node->GetFirstChild();
	while (child) {
		// Wenn der gerade bearbeitete Node gelöscht wurde, wird in der aktuellen Liste wieder
		// von vorne begonnen, da sich diese geändert haben kann !
		if (TraverseBspAddVobsToMesh(bspTree, child)==TRUE)	child = node->GetFirstChild();
		else												child = child->GetNextChild();
	};

	if (mustRemove)
	{
		RemoveVob (vob);
		return TRUE;
	};

	return FALSE;
	
}; 

void zCWorld::SaveBspTreeMesh3DS (const zSTRING& fileName) {
	zCFile3DS file3ds;
	zoptions->ChangeDir	(DIR_MESHES);
	file3ds.Save3DS (fileName, GetBspTree()->mesh);

	// Auch als Mesh speichern ? Problem => (Mem: muss Tris, disk: muss npolys)... 
};




static zBOOL s_wasCompiled=FALSE; // [Moos] Fixme: das sollte eine membervariable von zCWorld werden, die anzeigen soll, ob diese Welt nach dem letzten Laden compiliert wurde


void zCWorld::CompileWorld (const zTBspTreeMode& bspTreeMode, 
							const zREAL optimize,  
							const zBOOL removeLevelCompos, 
							const zBOOL editorMode,
							zCArray<zCPolygon*> *leakPolyList) 
{
	// Editor-Mode:
	// - kein LOD						(weil Mesh dann ein Multi-Res Mesh ist)
	// - kein Tris=>nPolys				(weil ungewuenschte Poly-Segmentierung, Probs bei nPoly 3DS-Export?)
	// - keine Outdoor-Sectoren builden	(wegen den neuen Materialien, weil Portale texturiert werden muessen)

	if (compiled) {
		zERR_WARNING ("D: zWorld(zCWorld::CompileWorld): World already compiled !");
		return;
	};

    s_wasCompiled = TRUE;

	// hohe FPU Precision sicherstellen
	const zDWORD fpuControlWord	= zfpuControler.GetCurrentControlWord();
	zfpuControler.SetPrecision_53();


	//
	zERR_MESSAGE (2, zERR_BEGIN, "D: WORLD: *** STARTING BSP-TREE COMPILING ***");
	// der globalVobTree wird durchgelaufen und alle Vob-Meshes werden dem 
	// Construction-BSP übergeben
	cbspTree = zNEW(zCCBspTree);
	cbspTree->SetBspTreeMode		(bspTreeMode);	

	TraverseBsp						(cbspTree, &globalVobTree, removeLevelCompos);

	if (cbspTree->GetBspTreeMode()==zBSP_MODE_INDOOR) 
	{
		// INDOOR
		zerr.Message ("D: WORLD: BspMode: INDOOR");
		// tris => nPolys
		#ifndef	zWLD_DONT_CONVERT_TRIS_2_NPOLYS
			if (!editorMode) {
				cbspTree->mesh->ConvertTrisToNPolys	();
			};
		#endif
		zCArray<zCBuildPortal*> portalList;
		if (!editorMode) 
			bspTree.PreprocessIndoorPortals	(cbspTree->mesh, portalList);
		// build
		cbspTree->BuildTree					(optimize);
		bspTree.Build						(cbspTree);
		if (!editorMode) 
			bspTree.PostprocessIndoorPortals(portalList);
		// Check for leaks ?
		if (leakPolyList) {
			if (bspTree.FindLeaks(*leakPolyList)) {};
		};
	} else 
	{
		// OUTDOOR
		zerr.Message ("D: WORLD: BspMode: OUTDOOR"); 
		zBOOL		sectorFound = FALSE;
		// FIXME: uuuhh.. eigentlich duerften hier nur die Mats der Polys betrachtet werden, die wirklich in dieser World sind..
		for (int i=0; i<zCMaterial::GetStaticClassDef()->GetNumObjects(); i++)
		{
			zCMaterial *mat = static_cast<zCMaterial*>(zCMaterial::GetStaticClassDef()->GetObjectByIndex(i));
//			if (mat->GetName().Search("P:")!=-1)	{ sectorFound=TRUE; break; };
			if (mat->IsPortalMaterial())			{ sectorFound=TRUE; break; };
		};
		if (editorMode) sectorFound = FALSE;

		s_iVobsKilled = 0;
		s_iPolysAdded = 0;

		// 1.
		if (sectorFound)
		{
			zerr.Message ("D: WORLD: Building Sector-BSP...");
			cbspTree->BuildTree			(optimize);
			// Sector-Polys
			cbspTree->CreateBspSectors	();

			if (zoptions->Parm("MERGEVOBSWITHLEVEL"))
			{
				bspTree.Build				(cbspTree);
				s_bAddVobsToMesh = TRUE;
				TraverseBspAddVobsToMesh	(cbspTree, &globalVobTree);
				s_bAddVobsToMesh = FALSE;
				bspTree.DisposeTree();
				UpdateVobTreeBspDependencies(&globalVobTree);
				cbspTree->CreateBspSectors	();
			}	

			// Tree killen
			cbspTree->DeleteTree		();
			// tris => nPolys
			#ifndef	zWLD_DONT_CONVERT_TRIS_2_NPOLYS
				if (!editorMode) {
					zCMesh::ConvertTrisToNPolys (cbspTree->mesh->PolyList(), cbspTree->mesh->numPoly, cbspTree->mesh, TRUE);
				};
			#endif
		}
		else if (zoptions->Parm("MERGEVOBSWITHLEVEL"))
		{
			bspTree.Build				(cbspTree);
			s_bAddVobsToMesh = TRUE;
			TraverseBspAddVobsToMesh	(cbspTree, &globalVobTree);
			s_bAddVobsToMesh = FALSE;
			bspTree.DisposeTree();
			UpdateVobTreeBspDependencies(&globalVobTree);
			cbspTree->CreateBspSectors	();
		}
		// 2.
		{
			zerr.Message ("D: WORLD: Building real BSP...");
			// compile
			cbspTree->MarkGhostOccluder	();					// muss vor dem BuildTree(), da dort die GhostOccluder bereits bekannt sein muessen
			cbspTree->BuildTree			(optimize);
			// Generating LOD: nur, wenn nicht im Editor-Mode
		};
		// 3.
		bspTree.Build					(cbspTree);
	};


	

	//
	delete cbspTree; cbspTree=0;
	compiled			= TRUE;
	compiledEditorMode	= editorMode;


	//
	zfpuControler.SetControlWord	(fpuControlWord);

	//
	zERR_MESSAGE (2, 0,		   "C: WORLD: vobs removed: " + zSTRING(s_iVobsKilled) + " , polys added: " + zSTRING(s_iPolysAdded));
	zERR_MESSAGE (2, zERR_END, "D: WORLD: *** FINISHED BSP-TREE COMPILING ***");
	

};

/*
	- load
	- reload
		- bestehende Vobs werden nicht neu erschaffenm, sondern nur neu initialisiert
		- nicht bestehende Vobs werden neu erschaffen & init
	- merge
		- keine Neu-Erschaffung, vobID bleibt bestehen, aber: INIT
			- add
			- replace
*/

// -------------------------------------------------------------------------------------------------------

zBOOL zCWorld::DisposeVobs (zCTree<zCVob> *node) 
{
    zCRenderLightContainer::S_ReleaseVobLightRefs(); // zerstöre den Light-Cache.

	if (node==0) {
		node = &globalVobTree;
		// Waypoint-Netz resetten
		// FIXME: sollte zusammen mit den vobs geloescht werden ??
		zRELEASE (wayNet);
		wayNet = zNEW(zCWayNet(this));

		// csPlayer resetten
		ResetCutscenePlayer();

//		// sonstiges
//		lastVobSoundList.EmptyList();

		//
		RemoveAllZones	();

		//
		renderingFirstTime	= TRUE;
	};
	
	// Process childs
	zCTree<zCVob>* child = node->GetFirstChild();
	while (child) {
		// Wenn der gerade bearbeitete Node gelöscht wurde, wird in der aktuellen Liste wieder
		// von vorne begonnen, da sich diese geändert haben kann !
		if (DisposeVobs (child)==TRUE) 
			child = node->GetFirstChild();
		else						   
			child = child->GetNextChild();
	};
	
	// Process Vob
	// vob (& dessen Mesh) löschen, den dranhängenden Subtree an den Parent des Vobs hängen
	zBOOL deletedThis = FALSE;
	zCVob *vob = node->GetData();
	if (vob) {
		// lösche Vob-Knoten aus globalVobTree
		// lösche Vob aus BSP-Tree
		// lösche Vob
		// lösche den globalVobTreeNode, ACHTUNG: darf ja nicht auf dem globalVobTree ausgefuehrt werden !!
		// - Vob wird beim Remove dann geloescht, wenn dessen RefCtr vorher == 1 ist
		// - Vob muss aus World 'removed' werden, ein Release() alleine wuerde den Vob nicht
		//   ordnungsgemaess aus der Welt entfernen, wenn dieser nach dem Remove weiter existiert.
		deletedThis	= TRUE;				// Vob wird auf jeden Fall aus globalVobTree entfernt
		RemoveVob (vob);
	};
	return deletedThis;
};


zBOOL zCWorld::DisposeVobsDbg (zCTree<zCVob> *node) 
{
    zCRenderLightContainer::S_ReleaseVobLightRefs(); // zerstöre den Light-Cache.

	if (node==0) 
	{
		node = &globalVobTree;
		// Waypoint-Netz resetten
		// FIXME: sollte zusammen mit den vobs geloescht werden ??
		zRELEASE (wayNet);
		wayNet = zNEW(zCWayNet(this));

		// csPlayer resetten
		ResetCutscenePlayer();

		//
		RemoveAllZones	();

		//
		renderingFirstTime	= TRUE;
	};
	
	// Process childs
	zCTree<zCVob>* child = node->GetFirstChild();
	while (child) 
	{
		// Wenn der gerade bearbeitete Node gelöscht wurde, wird in der aktuellen Liste wieder
		// von vorne begonnen, da sich diese geändert haben kann !
		if (DisposeVobsDbg(child)==TRUE) 
			child = node->GetFirstChild();
		else						   
			child = child->GetNextChild();
	};
	
	// Process Vob
	// vob (& dessen Mesh) löschen, den dranhängenden Subtree an den Parent des Vobs hängen
	zBOOL deletedThis = FALSE;
	zCVob *vob = node->GetData();

	/*
	zVOB_TYPE_NORMAL, 
	zVOB_TYPE_LIGHT,
	zVOB_TYPE_SOUND,
	zVOB_TYPE_LEVEL_COMPONENT,
	zVOB_TYPE_SPOT,
	zVOB_TYPE_CAMERA,
	zVOB_TYPE_STARTPOINT,
	zVOB_TYPE_WAYPOINT,
	zVOB_TYPE_MARKER,
	zVOB_TYPE_SEPARATOR,
	zVOB_TYPE_MOB,
	zVOB_TYPE_ITEM,
	zVOB_TYPE_NSC*/

	if (vob) 
	{
		// lösche Vob-Knoten aus globalVobTree
		// lösche Vob aus BSP-Tree
		// lösche Vob
		// lösche den globalVobTreeNode, ACHTUNG: darf ja nicht auf dem globalVobTree ausgefuehrt werden !!
		// - Vob wird beim Remove dann geloescht, wenn dessen RefCtr vorher == 1 ist
		// - Vob muss aus World 'removed' werden, ein Release() alleine wuerde den Vob nicht
		//   ordnungsgemaess aus der Welt entfernen, wenn dieser nach dem Remove weiter existiert.
		deletedThis	= TRUE;				// Vob wird auf jeden Fall aus globalVobTree entfernt
		RemoveVob (vob);
	};
	return deletedThis;
};


void zCWorld::DisposeStaticWorld () {
	// FIXME: am Besten einfach keine 'disposeStaticWorld' zulassen ... !

	// Bsptree
	// Achtung: Falls im Spacer hier noch bei S_ResetMorphedVerts Crashes auftreten, den folgenden 
	// Call durch zCPolygon::S_EmptyMorphedVerts ersetzen!

	if (bspTree.numPolys!=0)		// nicht im inventory, aber schön ist das so nicht (aber wen interessierts, in drei tagen ist goldmaster, hähä, NACH MIR DIE SINNFLUT <tschööööööö>
	{
		zCSkyControler_Outdoor *sky = zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler());
		if (sky) sky->SetLevelChanged(TRUE);
	}

	zCPolygon::S_DeleteMorphedVerts();
	bspTree.DisposeTree	();
	compiled			= FALSE;
	compiledEditorMode	= FALSE;
	renderingFirstTime	= TRUE;



	// (u.a. Vob::GroundPolys)
	UpdateVobTreeBspDependencies ();
};

void zCWorld::DisposeWorld () 
{
	zERR_MESSAGE (8, zERR_BEGIN, "D: WORLD: Disposing zCWorld..");

	// Lösche den Vob-Hierarchie, globalVobTree (inkl. deren Links zu dem BSP-Tree)
	DisposeVobs ();

	// Lösche den Render-BSP-Tree
	DisposeStaticWorld();

	zERR_MESSAGE (8, zERR_END, "D: WORLD: ..zCWorld disposed.");
};


// ===========================================================================================================
// ===========================================================================================================

zCVob*	zCWorld::SearchVob (zCVob *vob , zCTree<zCVob>* vobNode) {
	if (vobNode==0) vobNode = &globalVobTree;

	if (vobNode->GetData()==vob)
		return vob;

	// recursive traversal
	zCTree<zCVob> *child = vobNode->GetFirstChild(); 
	while (child) {
		zCVob* vobRes = SearchVob (vob, child);
		if (vobRes) return vobRes;
		child = child->GetNextChild();
	};
	return 0;
};

zCVob* zCWorld::SearchVobByID (const zTVobID vobID, zCTree<zCVob>* vobNode) {
	if (vobNode==0) {
		vobNode = &globalVobTree;
		if (vobID==zVOB_ID_NULL)	return 0;
	};

	if (vobNode->GetData())
		if (vobNode->GetData()->GetVobID()==vobID) return vobNode->GetData();

	// recursive traversal
	zCTree<zCVob> *child = vobNode->GetFirstChild(); 
	while (child) {
		zCVob* vob = SearchVobByID (vobID, child);
		if (vob) return vob;
		child = child->GetNextChild();
	};
	return 0;
};
/*
zCVob* zCWorld::SearchVobByName (const zSTRING& vobName, zCTree<zCVob>* vobNode) {
	if (vobNode==0) {
		if (vobName.IsEmpty()) return 0;
		vobNode = &globalVobTree;
	};

	if (vobNode->GetData()) {
		if (vobNode->GetData()->GetVobName()==vobName) return vobNode->GetData();
	};

	// recursive traversal
	zCTree<zCVob> *child = vobNode->GetFirstChild(); 
	while (child) {
		zCVob* vob = SearchVobByName (vobName, child); 
		if (vob) return vob;
		child = child->GetNextChild();
	};
	return 0;
};

void zCWorld::SearchVobListByName (const zSTRING& vobName, zCArray<zCVob*>& resultVobList, zCTree<zCVob>* vobNode)
{
	if (vobNode==0) {
		if (vobName.IsEmpty()) return;
		vobNode = &globalVobTree;
	};

	if (vobNode->GetData()) {
		if (vobNode->GetData()->GetVobName()==vobName) 
			resultVobList.Insert (vobNode->GetData());
	};

	// recursive traversal
	zCTree<zCVob> *child = vobNode->GetFirstChild(); 
	while (child) {
		SearchVobListByName (vobName, resultVobList, child); 
		child = child->GetNextChild();
	};
};
*/

zCVob* zCWorld::SearchVobByName (const zSTRING& vobName) {
	return SearchVobHashTable(vobName);
};

void zCWorld::SearchVobListByName (const zSTRING& vobName, zCArray<zCVob*>& resultVobList)
{
	SearchVobListHashTable(vobName, resultVobList);
};

void zCWorld::SearchVobListByClass (zCClassDef* classDef, zCArray<zCVob*>& resultVobList, zCTree<zCVob>* vobNode)
{
	if (vobNode==0) {
		assert (classDef);
		vobNode = &globalVobTree;
	};

	if (vobNode->GetData()) {
		if (vobNode->GetData()->GetClassDef()==classDef) 
			resultVobList.Insert (vobNode->GetData());
	};

	// recursive traversal
	zCTree<zCVob> *child = vobNode->GetFirstChild(); 
	while (child) {
		SearchVobListByClass (classDef, resultVobList, child); 
		child = child->GetNextChild();
	};
};

void zCWorld::SearchVobListByBaseClass(zCClassDef* baseClassDef, zCArray<zCVob*>& resultVobList, zCTree<zCVob>* vobNode) 
{
	if (vobNode==0) vobNode = &globalVobTree;

	if (vobNode->GetData()) {
		if (zCObject::CheckInheritance (baseClassDef, vobNode->GetData()->GetClassDef()))
			resultVobList.Insert (vobNode->GetData());
	};

	// recursive traversal
	zCTree<zCVob> *child = vobNode->GetFirstChild(); 
	while (child) {
		SearchVobListByBaseClass (baseClassDef, resultVobList, child); 
		child = child->GetNextChild();
	};
};

void zCWorld::SearchZoneListByClass	(zCClassDef* classDef, zCArray<zCZone*>& resultVobList) 
{
	for (int i=0; i<zoneGlobalList.GetNum(); i++) 
		if (zoneGlobalList[i]->GetClassDef()==classDef)	resultVobList.Insert (zoneGlobalList[i]);
};

zCZone* zCWorld::SearchZoneDefaultByClass (zCClassDef* classDef) 
{
	for (int i=0; i<zoneGlobalList.GetNum(); i++) {
		if (zoneGlobalList[i]->GetClassDef()==classDef)	{
			return zoneGlobalList[i];
		};
		// Ende der Default-Liste erreicht ?
		if (!zoneGlobalList[i]->IsDefaultZone())	break;
	};
	return 0;
};


// ===========================================================================================================


zCTree<zCVob>*	zCWorld::AddVobAsChild (zCVob *childVob, zCTree<zCVob>* parentVob) 
{		
	// nullptr ?
	if ((!childVob) || (!parentVob)) return 0;

	// ist Vob bereits in dieser oder einen anderen Welt eingefuegt ?
	if (childVob->GetHomeWorld()) return 0;

	// world-Ptr (auch Zones brauchen diesen)
	childVob->SetHomeWorld (this);

	// Zone ?
	// Unterschiede zu normalen Vobs (im Game, im Spacer genauso wie normale Vobs):
	// - werden nicht in den BSP-Tree einsortiert
	// - bekommen keine globalVobTreeNode
	if (zDYNAMIC_CAST<zCZone>(childVob)) 
	{
		AddZone ((zCZone*)childVob);
		// Zones werden im Game nicht als Vobs eingefuegt
//		if (!GetAddZonesToWorld()) return 0;
	};


	// globalVobTree
	if (childVob->globalVobTreeNode) 
	{
		// Mini-Subtree
		if (!childVob->globalVobTreeNode->GetParent()) 
		{
			// Nur in globalVobTree einfügen, wenn dies der Root-Knoten eines Subtrees ist, und dieser Vob deshalb
			// zwar eine Tree-Node aber keinen Parent hat
			parentVob->AddChild (childVob->globalVobTreeNode);
		};

		// childs einfuegen
		// Die Verbindungen für die Childs müssen hergestellt werden (allerdings nicht die globalVobTreeNodes..)

		// recursive traversal
		zCTree<zCVob> *child = childVob->globalVobTreeNode->GetFirstChild(); 
		while (child) {
			AddVobAsChild	(child->GetData(), childVob->globalVobTreeNode);
			child = child->GetNextChild();
		};
	} else 
	{
		zCTree<zCVob>* node			= parentVob->AddChild (childVob);
		childVob->globalVobTreeNode = node;
	};

	// folgendes macht Move() bereits
//	childVob->CalcGroundPoly();				// assert (homeWorld);

	childVob->AddVobToWorld_CorrectParentDependencies();

	// Collision aus, damit beim Einfuegen keine Collisionen mit anderen Vobs ausgeloest werden
	const zBOOL collDyn		= childVob->GetCollDetDyn();
	const zBOOL collStat	= childVob->GetCollDetStat();
	childVob->SetCollDet	(FALSE);
	// 'TouchMovement', damit internals geupdatet werden & die 0-Bewegung nicht abgewiesen wird
	childVob->BeginMovement	();
	childVob->TouchMovement	();
	childVob->EndMovement	();
	//
	childVob->SetCollDetDyn	(collDyn);
	childVob->SetCollDetStat(collStat);

	// 
	zADDREF_ACCT(childVob);

	// bspTree
	if (ShouldAddThisVobToBsp(childVob)) 
		bspTree.AddVob(childVob);

	if (!childVob->GetSleeping()) AddActiveVob (childVob);

	// inform the AI/Visual of this event
	if (childVob->GetAI())		childVob->GetAI()    ->HostVobAddedToWorld (childVob, this);
	if (childVob->GetVisual())	childVob->GetVisual()->HostVobAddedToWorld (childVob, this);

	//
	VobAddedToWorld (childVob);

	//
	return childVob->globalVobTreeNode;
};

zBOOL zCWorld::ShouldAddThisVobToBsp	(zCVob* vob) const
{
	// zum BSP hinzufuegen, wenn..
	// - entweder keine Zone
	// - oder eine Zone und Flag fuer Hinzufuegen gesetzt
	return ((zDYNAMIC_CAST<zCZone>(vob))==0) || GetAddZonesToWorld();
};

zCTree<zCVob>*	zCWorld::AddVobAsChild (zCVob *childVob, zCVob* parentVob) {		
	if ((!parentVob) || (!parentVob->globalVobTreeNode)) return 0;
	return AddVobAsChild (childVob, parentVob->globalVobTreeNode);
};

zCTree<zCVob>*	zCWorld::AddVob		(zCVob *vob) { 
	return AddVobAsChild (vob, &globalVobTree); 	
};

// ===========================================================================================================

void zCWorld::VobAddedToWorld (zCVob *vob) 
{
	// this is AFTER actual addition
	InsertVobHashTable			(vob);
	vob->ThisVobAddedToWorld	(this);
	++numVobsInWorld;
	zERR_ASSERT (numVobsInWorld>=0);
};

void zCWorld::VobRemovedFromWorld (zCVob *vob)
{
	// this is BEFORE actual removal
	vob->ThisVobRemovedFromWorld(this);
	RemoveVobFromLists			(vob);
	--numVobsInWorld;
	zERR_ASSERT (numVobsInWorld>=0);
};

void zCWorld::RemoveVob	(zCVob *vob) 
{
	if (!vob)						return;
	if (vob->GetHomeWorld()!=this)	return;
	VobRemovedFromWorld				(vob);
	vob->RemoveWorldDependencies	(TRUE);
};	

void zCWorld::RemoveVob	(zCTree<zCVob> *vobNode) 
{
	if (!vobNode) return;
	RemoveVob (vobNode->GetData()); 
};

void zCWorld::RemoveVobSubtree_r (zCTree<zCVob>* node, zBOOL firstVob) 
{
	// Die globalVobTreeNodes werden nicht geloescht, da sie denn Subtree zusammenlinken.
	// Nur die Verbindung des SubtreeRoots zum Parent wird geleost.
	// Fuer jeden Vob des Subtrees muessen gewisse 'unlinkt' werden.
	if (!node) return;

	const zBOOL vobHasSubtree	= (node->GetFirstChild()!=0);

	// process node
	zCVob *vob = node->GetData();
	if (vob) 
	{
		// 'RemoveWorldDependencies' koennte den Vob loeschen, deshalb hier per AddRef sicherstellen,
		// das der Vob existiert, solange er bearbeitet wird 
		// (wuerde er hier geleoscht werden, koennte man den Subtree nicht mehr sauber bearbeiten)
		VobRemovedFromWorld				(vob);
		zADDREF_ACCT                    (vob);
        // nur den globalVobTreeNode entfernen, falls der RootVob (this) keine childs hat!
		const zBOOL removeFromGlobalVobTree	= !vobHasSubtree && (firstVob);
		vob->RemoveWorldDependencies	(removeFromGlobalVobTree);
	};

	if (vobHasSubtree) 
	{
		// recursive traversal
		zCTree<zCVob> *child = node->GetFirstChild(); 
		while (child) 
		{
			zCTree<zCVob> *nextChild= child->GetNextChild(); // Ptr sichern, da er nach dem naechsten Aufruf nicht mehr zur Verfuegung stehen koennte
			RemoveVobSubtree_r		(child, FALSE);			 // bei diesem Aufruf koennte der child-Vob deleted werden !
			child					= nextChild;
		};
	};
	
	if (vob) 
	{
		// ist dieses letzte Release() ein loeschendes Release?
		// in diesem Fall muss auch die globalVobTreeNode freigegeben werden
		if ((vob->GetRefCtr()==1) && (vob->globalVobTreeNode))
		{
			// Falls aber ein parentVob geloescht wird, an dem noch childVobs haengen, so kann dieser Fall nicht 
			// korrekt behandelt werde, und es handelt sich aller Wahrscheinlichkeit nach um einen Programmierfehler
			// uebergeordneter Ebenen.
			if (vob->globalVobTreeNode->GetFirstChild())
			{
				zERR_FAULT ("D: WLD: zCVobs leaking, uneven refCtrs in vobSubTree! (Removing vobSubtree from world; Release() deletes parentVob but not children");
			};
			// vob->RemoveVobFromGlobalVobTree		();
		};
		zRELEASE_ACCT(vob);
	};
};

void zCWorld::RemoveVobSubtree (zCVob *vob) 
{
	if (!vob) return;

	// aus dem globalVobTree entfernen: unlink!
	// Die globalVobTreeNode darf allerdings nicht geloescht werden, da diese den Subtree zusammenhaelt.
	MoveVobSubtreeTo				(vob, (zCTree<zCVob>*) 0);

	// Verbindungen innerhalb des Subtrees zu anderen Objekten loesen
	RemoveVobSubtree_r				(vob->globalVobTreeNode, TRUE);

/*
	RemoveSubtree:
		- homeWorlds muessen ueberall auf 0
		- parent-Verbindung (root) muss geloest werden
		- ueberall SetSleeping (TRUE)
		- alle BspNodes muessen geloescht werden
	AddSubtree:
		- homeWorlds neu binden
		- parent-Verb.
		- SetSleeping (FALSE)
		- bspNodes
	*/
};	

void zCWorld::RemoveVobSubtree	(zCTree<zCVob> *vobNode) 
{ 
	if (!vobNode) return;
	RemoveVobSubtree (vobNode->GetData()); 
};

void zCWorld::MoveVobSubtreeTo (zCVob *vobSubtree, zCTree<zCVob> *destParent) 
{
	if (!vobSubtree) return;
	if (!vobSubtree->globalVobTreeNode) return;
	vobSubtree->globalVobTreeNode->MoveSubtreeTo (destParent);
	//
	zBOOL local		= !vobSubtree->GetInMovement();
	if (local)		vobSubtree->BeginMovement();
	vobSubtree->TouchMovement	();
	vobSubtree->Move			(0,0,0);
	if (local)		vobSubtree->EndMovement();
};

void zCWorld::MoveVobSubtreeTo (zCVob *vobSubtree, zCVob *destParent) 
{
	if (!destParent) return;
	if (!destParent->globalVobTreeNode) return;
	MoveVobSubtreeTo (vobSubtree, destParent->globalVobTreeNode);
};

void zCWorld::MoveVobSubtreeToWorldSpace (zCVob *vobSubtree) 
{
	MoveVobSubtreeTo (vobSubtree, &globalVobTree);
};

void zCWorld::RemoveVobFromLists (zCVob *vob) 
{
	bspTree.renderVobList.Remove (vob);
	for (int i=0; i<walkList.GetNumInList(); i++) {
		if (walkList[i]==vob) { walkList[i]=0; break; };
	};

	// Zone ?
	if (zDYNAMIC_CAST<zCZone>(vob)) {
		RemoveZone ((zCZone*)vob);
	};

	//
	RemoveVobHashTable	(vob);
};


// ===========================================================================================================
// ===========================================================================================================


void zCWorld::PrintStatus () 
{
	zerr.Message ("D: *** World-Status ************************************");
	zerr.Message ("D: Engine, Date: "+zSTRING()+", "+zSTRING(__DATE__));
	zerr.Message ("D: Objects in Main-Mem, shared between worlds:");
	zerr.Message ("D: - Num Meshes      : "+zSTRING(zCMesh		::NumInList()));
	zerr.Message ("D: - Num Materials   : "+zSTRING(zCMaterial	::GetStaticClassDef()->GetNumObjects()));
	zerr.Message ("D: - Num Textures    : "+zSTRING(zCTexture	::GetStaticClassDef()->GetNumObjects()));
	zerr.Message ("D: - Num LightPresets: "+zSTRING(zCVobLight	::lightPresetList.GetNumInList()));
	zerr.Message ("D: - Num ParticleFX  : "+zSTRING(zCParticleFX::s_emitterPresetList.GetNumInList()));
	zerr.Message ("D: World:");
	zerr.Message ("D: - Num Vobs        : "+zSTRING(globalVobTree.CountNodes()));
	zerr.Message ("D: - Num activeVobs  : "+zSTRING(activeVobList.GetNumInList()));
	zerr.Message ("D: - vobFarClipZ     : "+zSTRING(GetVobFarClipZ()));
	zerr.Message ("D: - perFrameCallback: "+zSTRING(perFrameCallbackList.GetNum()));
	
	if (IsCompiled()) {
	zerr.Message ("D: BSP: ");
	if (bspTree.GetBspTreeMode()==zBSP_MODE_INDOOR)
	zerr.Message ("D: - Mode            : indoor");
	else
	zerr.Message ("D: - Mode            : outdoor");
	zerr.Message ("D: - Num meshPolys   : "+zSTRING(bspTree.mesh->numPoly));
	zerr.Message ("D: - Num treePolys   : "+zSTRING(bspTree.numPolys)); 
	zerr.Message ("D: - Num Leafs       : "+zSTRING(bspTree.numLeafs));
	zerr.Message ("D: - Num Nodes       : "+zSTRING(bspTree.numNodes));
	} else
	zerr.Message ("D: uncompiled world");
	zerr.Message ("D: *****************************************************");
};

void zCWorld::PrintGlobalVobTree(zCTree<zCVob>* node, int indent) 
{
	if (node==0) {
		node = &globalVobTree;
		
		// zones 
		zerr.Message ("D: ****** ZoneList ********");
		for (int i=0; i<zoneGlobalList.GetNum(); i++)
			zerr.Message ("D: "+zoneGlobalList[i]->GetVobInfo());
		zerr.Message ("D: ****** VobTree ********");
	};

	// process node
	zCVob* vob = node->GetData();
	if (vob) {
		zerr.Message ("D: "+Spaces(indent*2)+"- "+vob->GetVobInfo());
	};

	// recursive traversal
	zCTree<zCVob> *child = node->GetFirstChild(); 
	while (child) {
		PrintGlobalVobTree (child, indent+1);
		child = child->GetNextChild();
	};
};

void zCWorld::PrintActiveVobs () 
{
	zerr.Message ("D: *** World: ActiveVobList ************************************");
	for (int i=0; i<activeVobList.GetNumInList(); i++) {
		zerr.Message ("D: "+zSTRING(i)+": "+activeVobList[i]->GetVobInfo());
	};
};

void zCWorld::UpdateVobTreeBspDependencies (zCTree<zCVob>* node) 
{
	if (node==0) node = &globalVobTree;

	// process node
	zCVob* vob = node->GetData();
	if (vob) {
		// polyGround ?
		vob->SetGroundPoly				(0);
		vob->CalcGroundPoly				();

		// Leafs ?
		vob->vobLeafList.EmptyList		();
		vob->RemoveVobFromBspTree		();
		bspTree.AddVob					(vob);

		// .... ist das alles ???
		// FIXME: am Besten einfach keine 'disposeStaticWorld' zulassen ... !
	};

	// recursive traversal
	zCTree<zCVob> *child = node->GetFirstChild(); 
	while (child) {
		UpdateVobTreeBspDependencies (child);
		child = child->GetNextChild();
	};
};

void zCWorld::MoveVobs () 
{
	// Es koennte sein, dass 'DoAI' den Vob im Verlauf aus der Liste loescht...
	// es koennte sogar so sein, dass ein SetSleeping das NEXTVOB loescht !!!!
	// Abhilfe: diesen Durchlauf auf einer vorher erstellten Kopie machen
	// => (zCArray)
#ifdef ZENGINE_DEBUG
	if (ztimer.GetFrameTimeF()<=0) return;
#endif

	walkList = activeVobList;
	for (int i=0; i<walkList.GetNumInList(); i++) {
		if (walkList[i]) walkList[i]->DoFrameActivity();
	};
	walkList.EmptyList();
};

void zCWorld::AdvanceClock (const zREAL timeDeltaSec) 
{
	if (timeDeltaSec<0) {
		ztimer.ResetTimer();
	} else {
		ztimer.SetFrameTime (timeDeltaSec*1000);		// sec nach msec
	};
};

void zCWorld::SaveBspTree (zFILE& file) 
{
	zerr.Message		("D: WORLD: Saving BSP: "+file.GetFilename());

	zCFileBIN fileBin;  
	fileBin.BinSetFile	(&file);
	bspTree.SaveBIN		(fileBin);
};

zBOOL zCWorld::LoadBspTree (zFILE& file, zBOOL skipThisChunk) 
{
	zBOOL res;
	zCFileBIN fileBin; 
	fileBin.BinSetFile		(&file);
	res = bspTree.LoadBIN	(fileBin, skipThisChunk);
	
	if (!skipThisChunk) 
	{
		if (bspTree.mesh) {
			if (bspTree.mesh->GetHasLightmaps ())	
				SetWorldRenderMode		(zWLD_RENDER_MODE_LIGHTMAPS);
			else									
				SetWorldRenderMode		(zWLD_RENDER_MODE_VERT_LIGHT); 
		};
		compiled = res;
	};
	return res;
};

void zCWorld::DebugMarkOccluderPolys () 
{
	if (!IsCompiled()) return;
	zCMaterial *mat = zNEW(zCMaterial("Occluder_Poly_Mat"));  
	mat->SetColor (255,50,50);

	// [EDENFELD] 1.09 Crash bei ZMARK OCCLUDERPOLYS behoben
	bspTree.mesh->CreateListsFromArrays();

	for (int i=0; i<bspTree.mesh->numPoly; i++) {
		zCPolygon *poly = bspTree.mesh->Poly(i);
		// [EDENFELD] 1.09 Portale werden nicht mit markiert
		if (poly->GetOccluder() && (!poly->IsPortal())) {
			poly->SetMaterial (mat);
		};
	};
};

// ===========================================================================================================

/*

	[oCWorld:zCWorld]
		[zCWorldData]
			..
		[]
		[MeshAndBsp]
			..
		[]
		[VobTree]
			..
		[]
		[EndMarker]
		[]
	[]

*/

///////////////////////////////////
//     LOAD
///////////////////////////////////

static int				arcNumChildCtr;
static zCArray<zCVob*>	arcNewVobList;

void zCCFASTCALL zCWorld::UnarcTraverseVobs (zCArchiver& arc, zCTree<zCVob>* parent) 
{
/*
  - Falls eine bestimmte Vob-Klasse das Visual selber setzen will, also das 'visual' Feld des zCVob
    ignorieren will, so muss in der entsptr. Unarchive Routine der Vob-Klasse vor dem Unarchive der
	Basisklasse das SetIgnoreVisuals(TRUE) gesetzt werden (und danach wieder zurueck).
  - MergeModes:
	- => Ein VobSubtree aus einem File wird in die Welt eingefuegt. Zurueckgeliefert wird der 
	     RootVob des neu eingefuegten VobSubtrees.
	- Add:
		- Der Subtree wird entweder an einen übergebenen Vob oder voellig frei eingefuegt. VobIDs
		  muessen direkt nach dem Laden allerdings neu vergeben werden, da die aus dem File in der
		  Welt bereits vorkommen koennten
	- Replace:
		- Macht nur Sinn, wenn ein Vob als Param uebergeben worden ist. In diesem Fall wird der VobSubtree
		  in diesem Vob 'expandiert'. D.h., dass der Vob quasi geloescht wird, und durch den RootVob
		  des VobSubtrees ersetzt wird. Auch hier muessen voellig neue, noch freie VobIDs vergeben werdens
  - Levelcompos

  - FIXME: evtl. irgendwo eine Tabelle mit allen Load/Save-Modi und die Auflistung deren Eigenschaften ?	
		   also z.B. 'dontLoadLevelCompVisual', 'removeLevelCompo', ..

	zTWorldLoadMode			{	zWLD_LOAD_GAME_STARTUP,			// dyn + stat, remove levelCompos
								zWLD_LOAD_GAME_SAVED_DYN,		// dyn       , remove levelCompos
								zWLD_LOAD_GAME_SAVED_STAT,		//       stat, remove levelCompos
								zWLD_LOAD_EDITOR_COMPILED,		// dyn + stat, deactivate levelCompos
								zWLD_LOAD_EDITOR_UNCOMPILED,	// dyn       , activate   levelCompos
								zWLD_LOAD_MERGE };
*/
	// Progress Bar
	if ((GetProgressBar()) && ((arcNumChildCtr & 7)==0))	// nur bei jedem 8. Vob ein ProgBar Update
	{
		int filePos = zFloat2Int (zREAL(arc.GetFile()->Pos()-unarchiveStartPosVobtree) / zREAL(unarchiveFileLen+0.1F) * 100.0F); // [SPECKELS] 0.1 addiert, um div0 zu vermeiden
		GetProgressBar()->SetPercent	(filePos);
	};

	zCVob			*vob				= 0;
	zCTree<zCVob>	*newParent			= 0;
	zBOOL			vobExisting			= FALSE;
	zBOOL			removeLevelCompoMode= FALSE; 
	zBOOL			removeThisLevelCompo= FALSE;
	zBOOL			vobIsLevelCompo		= FALSE;

	if (parent==0) {
		// parent '0' bedeutet hier: erster Durchgang
		newParent	= (s_unarcTraverseVobsFirstParent) ? s_unarcTraverseVobsFirstParent : &globalVobTree;
		goto readChilds;
	};

	// LevelCompo Visuals ignorieren ?
	// (nicht beim mergen..!)
	removeLevelCompoMode =	((s_worldLoadMode==zWLD_LOAD_GAME_STARTUP)   || 
							 (s_worldLoadMode==zWLD_LOAD_GAME_SAVED_DYN));
	zCVobLevelCompo::UnarcSetIgnoreVisuals (removeLevelCompoMode);

	// vob erzeugen & laden
	vob = static_cast<zCVob*>(arc.ReadObject0 ());
	assert (vob);
	if (!vob) goto readChilds;

	// Merge
	if (s_worldLoadMode==zWLD_LOAD_MERGE) {
		if (s_worldMergeMode==zWLD_LOAD_MERGE_REPLACE_ROOT_VISUAL) 
		{
			// Das Visual des gerade gelesenen Vobs wird in den Argument-Vob uebertragen.
			// 
			s_worldMergeMode	= zWLD_LOAD_MERGE_ADD;					// ein evtl. vorhergehendes REPLACE wird zu ADD
			assert (s_firstVobMergeVobSubtree);
			if (!s_firstVobMergeVobSubtree) goto readChilds;			// Notsprung
			s_firstVobMergeVobSubtree->SetVisual (vob->GetVisual());	// Visual uebertragen
			zRELEASE_ACCT_NONULL(vob);									// Der gerade gelesene Vob wird geloescht
			vob			= s_firstVobMergeVobSubtree;
			vobExisting	= TRUE;											// "alten" vob nicht erneut in die Welt einfuegen
		} else {
			// mergen ? => komplett neue vobIDs vergeben.
			// allerdings erst nach dem laden/initen, da die hoeheren Layer auf die IDs aus dem Script angewiesen sind !
			// aber: noch vor dem einfuegen in die Welt !
			vob->SetVobID (zCVob::GetNextFreeVobID ());
			if (s_firstVobMergeVobSubtree==0) s_firstVobMergeVobSubtree=vob;
		};
	};

	// LevelCompo removen ?
	vobIsLevelCompo		= (dynamic_cast<zCVobLevelCompo*>(vob))!=0;
	removeThisLevelCompo= (vobIsLevelCompo && removeLevelCompoMode);

	// LevelCompo deaktivieren ? Fuer ein evtl. Recompile muss diese allerdings trotzdem geladen
	// werden und wird halt nur 'versteckt'
	if (vobIsLevelCompo) {
		if (s_worldLoadMode==zWLD_LOAD_EDITOR_COMPILED)		vob->SetShowVisual (FALSE);
		if (s_worldLoadMode==zWLD_LOAD_EDITOR_UNCOMPILED)	vob->SetShowVisual (FALSE);
	};

	// ***************************
	// **   INSERT INTO WORLD	**
	// ***************************

		// [BENDLIN] 1.30 - SCALELIGHTRANGE für Spacer2 1.53 deaktiviert!
#ifdef COMPILING_SPACER
/*		vobLight = zDYNAMIC_CAST<zCVobLight>(vob);
		if (vobLight && zoptions->Parm("SCALELIGHTRANGE"))
		{
			vobLight->SetRange(vobLight->GetRange()*zoptions->ParmValue("SCALELIGHTRANGE").ToFloat());
		}; */
#endif

	if (!vobExisting) {
		// LevelCompo ?
		if (removeThisLevelCompo ) {
			zRELEASE		(vob);
			newParent		= parent;
		} else {
			newParent		= AddVobAsChild (vob, parent);
			if (newParent==0) newParent = parent;
			// Dieser Kontext, in dem der Vob erzeut word ist benoetigt diesen nicht mehr => release.
			// Zuvor wurde der Vob offiziell in die Welt eingefuegt. Die Welt hat somit nun eine Ref auf den Vob.
			zERR_ASSERT		(vob->GetRefCtr()>=2);
			zRELEASE_ACCT_NONULL(vob);
		};
	} else {
		newParent			= vob->globalVobTreeNode;
	};

	if (vob) 
	{
		// [BENDLIN] 1.30 - noch nötig ?
		// FIXME: temporaer ! (bis die Spacer-ppf Daten hier korrekt ankommen...)
		// ohne das SetRange scheinen die Lights nur auf ihr Origin-Leaf begrenzt zu sein.... why ?
		if (vob->GetVobType()==zVOB_TYPE_LIGHT) {
			zCVobLight* light	= (zCVobLight*)vob;
			light->SetRange		(light->GetRange());
		};

		//
		arcNewVobList.Insert (vob);
	};

	// ***********************
	// **   RECURSE			**
	// ***********************

readChilds:;
	// numChilds
	const zSTRING	s			= "childs"+zSTRING	(arcNumChildCtr++);
	int				numChilds	= arc.ReadInt		(s.ToChar());	

	// recursive traversal
	for (int i=0; i<numChilds; i++) {
		UnarcTraverseVobs (arc, newParent);
	};
};

void zCWorld::Unarchive (zCArchiver &arc) 
{
    s_wasCompiled = FALSE;

	zCObject::Unarchive	(arc);

	// Progress Bar
	{
		unarchiveFileLen				= 0;
		unarchiveStartPosVobtree		= 0;
		if ((GetProgressBar())	&& (arc.GetFile()))
		{
			unarchiveFileLen			= arc.GetFile()->Size();
			GetProgressBar()->SetPercent(0);
		};
	};

	// ACHTUNG: Routine darf erst angesprungen werden, wenn gewisse Variablen die gewuenschten Werte haben
	// - worldLoadMode
	// - worldMergeMode
	// - worldFileIOMode

	// Skip static Part ?
	// (natuerlich auch beim mergen)
	zBOOL skipStatic = ((s_worldLoadMode == zWLD_LOAD_GAME_SAVED_DYN)		|| 
						(s_worldLoadMode == zWLD_LOAD_EDITOR_UNCOMPILED)	||
						(s_worldLoadMode == zWLD_LOAD_MERGE));

	// Skip dynamic Part ?
	zBOOL skipDynamic = (s_worldLoadMode == zWLD_LOAD_GAME_SAVED_STAT);

	// Chunks parsen, die der zCWorld bekannt sind
	// der Chunk "EndMarker" signalisiert das Ende und uebergibt evtl. die Kontrolle an eine abgel. Klasse
	zSTRING chunkName;
	zWORD	chunkVersion;
	zBOOL	foundStatic = FALSE;
	do {
		arc.ReadChunkStart	(chunkName, chunkVersion);
		//
		if (chunkName=="MeshAndBsp") {
			// Load Static: BSP-Tree
			if (arc.GetFile()) 
			{
				// nur Static loeschen, wenn danach auch wirklich Static geladen werden soll !
				if (!skipStatic)
					DisposeStaticWorld		();
				foundStatic= LoadBspTree(*arc.GetFile(), skipStatic); 
				if (s_worldLoadMode==zWLD_LOAD_GAME_SAVED_STAT) {
					if (!foundStatic) {
						zERR_WARNING ("D: loadMode==zWLD_LOAD_GAME_SAVED_STAT, but could not load static World");
					};
	//				return;
				};
			};
			arc.SkipOpenChunk	();
		} else 

		//
		if (chunkName=="VobTree") {
			if (skipDynamic) {
				arc.SkipOpenChunk	();
			} else {
				// Sollen doch die LevelCompos geladen werden ?
				// Nur im Fall, dass mann eigentlich den Static Teil einladen wollte, dieser aber doch nicht
				// vorhanden ist, oder in einem alten Versions-Format vorliegt
				if (!skipStatic)
				if (!foundStatic) 
				{
					if (s_worldLoadMode!=zWLD_LOAD_GAME_SAVED_DYN) {
						DisposeStaticWorld	();
						s_worldLoadMode = zWLD_LOAD_EDITOR_UNCOMPILED;
					};
				};

				if (GetProgressBar())	
				{
					if (arc.GetFile())
						unarchiveStartPosVobtree = arc.GetFile()->Pos();
					unarchiveFileLen			-= unarchiveStartPosVobtree;
					GetProgressBar()->SetRange		(10,80);
				};

				// Load Dynamic: Vob-Hierarchy
				zerr.Message		("D: WORLD: Loading VobTree ..");

                int saveArcNumChildCtr  = arcNumChildCtr;  // [Moos] speicher den aktuellen Stand zwischen; sichert Rekursionssicherheit (Ulf hat manchmal beim Speichern Vobtrees geladen...)
				arcNumChildCtr		    = 0;
				arcNewVobList.EmptyList ();
				UnarcTraverseVobs	    (arc, 0);	// MUSS hier '0' sein!
				arc.SkipOpenChunk	    ();
                arcNumChildCtr          = saveArcNumChildCtr;

				if (GetProgressBar())	GetProgressBar()->ResetRange();

				// Vob: PostLoad()
				for (int i=0; i<arcNewVobList.GetNum(); i++)
					arcNewVobList[i]->PostLoad();
				arcNewVobList.EmptyList();
			};
		} else 

		//
		if (chunkName=="CutscenePlayer") {
			// Wenn die Welt keinen gueltigen csPlayer hat, wird der Chunk geskippt
			if (GetCutscenePlayer()) {
				csPlayer		= static_cast<zCCSPlayer*>(arc.ReadObject2("", GetCutscenePlayer()));
			};
			arc.SkipOpenChunk	();
		} else

		if (chunkName=="SkyCtrl") {
			// aktiviert den SkyCtrl aus dem NEUEN Level! Jetzt muessten die Klassen aus Archive
			// und in dieser zCWorld matchen, falls nicht lief irgendetwas schief..
			this->GetActiveSkyControler	();		
			activeSkyControler			= static_cast<zCSkyControler*>(arc.ReadObject2("", activeSkyControler));
			arc.SkipOpenChunk			();
		} else
			
		//
		if (chunkName=="WayNet") {
			if (!skipDynamic) {
				wayNet	= static_cast<zCWayNet*> (arc.ReadObject1 (GetWayNet()));
			};
			arc.SkipOpenChunk	();
		} else 

		//
		if (chunkName=="EndMarker") {
			arc.SkipOpenChunk	();
			break;
		};
	} while(1);

	// FIXME: kompatibel zum alten Format, bald ENTFERNEN!
	if (arc.GetCurrentChunkVersion()<1)		// zCWorld Chunk
	{
		// Waynet
		if (skipDynamic) 
		{
			// auch Waynet skippen, falls dynamische Daten nicht gelesen werden sollen
			zSTRING chunkName;
			zWORD	chunkVers;
			arc.ReadChunkStart	(chunkName, chunkVers);
			arc.SkipOpenChunk	();
			if (!wayNet)
				wayNet	= zNEW(zCWayNet(this));
		} 
		else {
			wayNet	= static_cast<zCWayNet*> (arc.ReadObject1 (GetWayNet()));
		};
	}

	if (GetProgressBar())	GetProgressBar()->SetPercent	(100);
};

zBOOL zCWorld::LoadWorld (const zSTRING& fileName, const zTWorldLoadMode loadMode) 
{
	//
	zERR_MESSAGE	(1, zERR_BEGIN, "D: WORLD: Loading WorldFile.. "+fileName);

	// Setup
	{
		s_worldLoadMode = loadMode;

		// dispose dynamic world
		// Der Dynamische Anteil der Welt muss IMMER geloescht werden. Falls man ein Archive mit Vobs
		// laedt sowieso, beim Laden eines Archives mit statischen Level Daten haetten nicht entfernte Vobs
		// noch illegale Refs auf bereits tote BspLeafs.
		// (Alternative Loesungen: Vobs bei einem LoadDyn in den Level mergen, Vobs bei einem LoadStat neu 
		//  zu den BspLeafs linken).
		// if (loadMode!=zWLD_LOAD_GAME_SAVED_STAT) 
		{
			DisposeVobs			();
			zCVob::ResetIDCtr	();
		};

		// dispose static world
		if ((loadMode==zWLD_LOAD_GAME_STARTUP)    || 
			(loadMode==zWLD_LOAD_GAME_SAVED_STAT) || 
			(loadMode==zWLD_LOAD_EDITOR_COMPILED) ||
			(loadMode==zWLD_LOAD_EDITOR_UNCOMPILED)
			) {
			DisposeStaticWorld	();
		};

/*		// Set FileIOMode
		if ((loadMode==zWLD_LOAD_GAME_SAVED_DYN) || (loadMode==zWLD_LOAD_GAME_SAVED_STAT)) 
				SetWorldFileIOMode	(zWLD_FILEIO_SAVED_STATE);
		else	SetWorldFileIOMode	(zWLD_FILEIO_STARTUP_STATE);*/
	};

	// Hints an den VertexBufferManager
	zvertexBufferMan.StartChangeWorld	();

	//
	zoptions->ChangeDir		(DIR_WORLD);
	zCArchiver *arc			= zarcFactory.CreateArchiverRead (fileName);
	zBOOL		res			= (arc!=0);
	if (arc)	
	{
		arc->ReadObject1		(this);
		arc->Close			();
		zRELEASE			(arc);
	};

	// Hints an den VertexBufferManager
	zvertexBufferMan.EndChangeWorld	();

	SetFadeOutFarVertices		( zoptions->ReadBool("ENGINE", "zFarClipAlphaFade",TRUE) );
	
	if ( IsCompiled() && GetBspTree() &&  GetBspTree()->GetBspTreeMode() == zBSP_MODE_INDOOR )
	{
		SetFadeOutFarVertices		( FALSE );
	}

	//
	zERR_MESSAGE	(1, zERR_END, "");
	if (res)
	{
		zFILE_FILE path(fileName);
		m_strlevelName  = path.GetFilename();

		//int warnTotal2 = TRUE;
		if (GetBspTree())
		{
			// den BspTree informieren, das ein neuer Level am Start ist
			GetBspTree()->SetRenderedFirstTime(TRUE);


			
			//DisposeVobsDbg();

			//GetBspTree()->OptimizeLight();
			//GetBspTree()->MarkOccluderPolys();
		//	GenerateStaticVertexLighting ();			
		}
	}
	return res;
};

zCVob* zCWorld::MergeVobSubtree (const zSTRING& fileName, zCVob* paramVob, zTWorldLoadMergeMode mergeMode)
{
	//
	zCTree<zCVob>* parentNode;
	s_worldMergeMode = mergeMode; 
	if (mergeMode==zWLD_LOAD_MERGE_ADD) {
		if ((paramVob) && (paramVob->globalVobTreeNode))	parentNode = paramVob->globalVobTreeNode;
		else												parentNode = &globalVobTree;
		s_firstVobMergeVobSubtree		= 0;
		s_unarcTraverseVobsFirstParent	= parentNode;
	} else {
		if (!paramVob)	return 0;
		if (paramVob)						parentNode = paramVob->globalVobTreeNode->GetParent();
		if ((!paramVob) || (!parentNode))	parentNode = &globalVobTree;
		s_firstVobMergeVobSubtree		= paramVob;
		s_unarcTraverseVobsFirstParent	= 0;
	};

	//
//	SetWorldFileIOMode		(zWLD_FILEIO_STARTUP_STATE);
	s_worldLoadMode			= zWLD_LOAD_MERGE;

	//
	zoptions->ChangeDir		(DIR_WORLD);
	zCArchiver *arc			= zarcFactory.CreateArchiverRead (fileName);
	if (arc)	
	{
		arc->ReadObject1	(this);
		arc->Close			();
		zRELEASE			(arc);
	};
 
	//
	zCVob *tmp						= s_firstVobMergeVobSubtree;
	s_firstVobMergeVobSubtree		= 0;
	s_unarcTraverseVobsFirstParent	= 0;
	return tmp;
};


///////////////////////////////////
//     SAVE
///////////////////////////////////

static inline int S_CountVobTreeChilds_RegardingDontWrite (zCTree<zCVob>* node)
{
	int num	= 0;
	node	= node->GetFirstChild();
	while (node) 
	{
		if (!node->GetData()->GetDontWriteIntoArchive())
			++num;
		node	= node->GetNextChild();
	};
	return num;
};

void zCCFASTCALL zCWorld::ArcTraverseVobs (zCArchiver &arc, zCTree<zCVob>* node, const zBOOL firstVob) 
{
	if (!node) return;

	// [2 Faelle: a) saveGlobalVobTree, b) saveVobSubtree]

	// - numChilds		(!!)
	// - [VOB]
	// - numChilds
	// - ..
	// - [VOB]
	// - numChilds

	// Progress Bar
	if ((GetProgressBar()) && ((arcNumChildCtr & 7)==0))	// nur bei jedem 8. Vob ein ProgBar Update
	{
		int filePos = zFloat2Int		((float(arcNumChildCtr) / (float(numVobsInWorld)+0.1F)) * 100.0F); // [SPECKELS] 0.1 addiert, um div0 zu vermeiden
		GetProgressBar()->SetPercent	(filePos);
	};

	// wieviele zu schreibende Vob-Childs hat diese Node?
	const int thisNodeNumChildsToWrite = S_CountVobTreeChilds_RegardingDontWrite (node);

	if (firstVob) 
	{
		// numChilds
		const  zSTRING s ("childs"+zSTRING(arcNumChildCtr++));
		if (node->GetData()) {
			// save vobSubTree
			arc.WriteInt		(s.ToChar(), 1);
			zERR_ASSERT_STRICT	(!node->GetData()->GetDontWriteIntoArchive());
		} else {
			// save globalVobTree
			arc.WriteInt		(s.ToChar(), thisNodeNumChildsToWrite);
		};
	};

	{
		// process node
		zCVob* vob = node->GetData();
		if ((vob) && (!vob->GetDontWriteIntoArchive()))
		{
			// Save Vob
			arc.WriteObject (vob);

			// Save Vob-Mesh-Def (nur fuer Level-Componenten)
			{
				zCVisual *vis = vob->GetVisual();
				if (s_saveLevelMesh)
				if (vob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT)
				if (vis)
				if (vis->GetClassDef()==zCMesh::GetStaticClassDef()) 
				{
					zCMesh	*mesh		= static_cast<zCMesh*>(vis);
					zCFile3DS file3ds;
					zoptions->ChangeDir	(DIR_MESHES);
					file3ds.Save3DS		(mesh->GetMeshName(), mesh);
				};
			};

			// numChilds
			const  zSTRING s ("childs"+zSTRING(arcNumChildCtr++));
			arc.WriteInt	 (s.ToChar(), thisNodeNumChildsToWrite);	
		};

		// Childs schreiben? => wenn entweder this kein vob ist (also globalVobTreeRoot), oder this ein 
		//						Vob ist, der gerade ins Archive geschrieben worden ist.
		//						Die Childs von 'GetDontWriteIntoArchive()' Parents werden hier also uebergangen.
		if ((!vob) || (!vob->GetDontWriteIntoArchive()))
		{
			// recursive traversal
			zCTree<zCVob> *child = node->GetFirstChild(); 
			while (child) 
			{
				ArcTraverseVobs (arc, child, FALSE);
				child = child->GetNextChild();
			};
		};
	};
};


void zCWorld::Archive (zCArchiver &arc) 
{
	zCObject::Archive	(arc);

	// ACHTUNG: Routine darf erst angesprungen werden, wenn gewisse Variablen die gewuenschten Werte haben
	// - saveLevelMesh
	// - firstVobSaveWorld
	// - worldSaveMode
	// - worldFileIOMode

	// VobLightRefs des RenderLightContainers releasen, damit bereits inaktive Lights auch wirklich geloescht werden
	zCRenderLightContainer::S_ReleaseVobLightRefs ();

	// Progress Bar
	{
		if ((GetProgressBar())	&& (arc.GetFile()))
		{
			GetProgressBar()->SetPercent(0);
		};
	};

	// Chunk "zCWorldData"
	// 'SaveVobSubtree': worldData darf nicht gespeichert werden
	// ..

	// Chunk "MeshAndBsp"
	// Es duerfen NIEMALS rein binaere Daten in ein ASCII-Archiv geschrieben werden !
	// 'SaveVobSubtree': statische Level darf nicht gespeichert werden
	if (s_firstVobSaveWorld==&globalVobTree)
//	if (arc.InBinaryMode())
	if (arc.GetFile())
	if (((s_worldSaveMode==zWLD_SAVE_COMPILED_ONLY) || (s_worldSaveMode==zWLD_SAVE_EDITOR_COMPILED)) && (IsCompiled())) {
		arc.WriteChunkStart ("MeshAndBsp");

        if (!s_wasCompiled)
            bspTree.mesh->ShareFeatures(); // [Moos] nach einer Neucompilierung klappt das nicht. Warum???

		SaveBspTree			(*arc.GetFile());
		arc.WriteChunkEnd	();
	};


	// Chunk "VobTree"
	// (nicht schreiben, wenn sich gar keine keine Vobs in der Welt befinden)
	zBOOL vobsInWorld = (zoneGlobalList.GetNum()>0) || 
						((s_firstVobSaveWorld) && ((s_firstVobSaveWorld->GetData()) || (s_firstVobSaveWorld->GetFirstChild())));
	if (vobsInWorld)
	if (s_worldSaveMode!=zWLD_SAVE_COMPILED_ONLY) 
	{
		// ProgressBar
		if (GetProgressBar())	GetProgressBar()->SetRange	(10,80);

		//
		arc.WriteChunkStart ("VobTree");

        int saveArcNumChildCtr  = arcNumChildCtr;
		arcNumChildCtr		    = 0;
		ArcTraverseVobs		    (arc, s_firstVobSaveWorld);
		arc.WriteChunkEnd	    ();
        arcNumChildCtr          = saveArcNumChildCtr;

		// ProgressBar
		if (GetProgressBar())	GetProgressBar()->ResetRange();
	};

	// Chunk "csPlayer"
	// (nur im SavedGame speichern)
	if (arc.InSaveGame())
	{
		if (GetCutscenePlayer())
		{
			arc.WriteChunkStart ("CutscenePlayer");
			arc.WriteObject		(GetCutscenePlayer());
			arc.WriteChunkEnd	();
		};
	};

	// Chunk "SkyControler"
	// (nur im SavedGame speichern)
	if (arc.InSaveGame())
	{
		arc.WriteChunkStart ("SkyCtrl");
		arc.WriteObject		(this->GetActiveSkyControler());
		arc.WriteChunkEnd	();
	};

	// Chunk "WayNet"
	if (s_saveWayNet) 
	{
		arc.WriteChunkStart ("WayNet");
		arc.WriteObject		(GetWayNet());
		arc.WriteChunkEnd	();
	};

	
	// Chunk "EndMarker"
	{
		arc.WriteChunkStart ("EndMarker");
		arc.WriteChunkEnd	();
	};

	// ProgressBar
	if (GetProgressBar())	GetProgressBar()->SetPercent	(100);
};

zBOOL zCWorld::SaveWorld (const zSTRING& fileName, const zTWorldSaveMode saveMode, 
						  const zBOOL writeBinary, const zBOOL _saveLevelMesh)
{
	
	zCPolygon::S_ResetMorphedVerts();

	//
	zERR_MESSAGE (5, 0, "D: WORLD: Saving World: \""+fileName+"\""); 

	// CamVob entfernen
	zCVob *camVob = 0; 
	if (zCCamera::activeCam) 
	if (zCCamera::activeCam->GetVob()) 
	{
		camVob = zCCamera::activeCam->GetVob();
        zADDREF_ACCT(camVob);
		RemoveVob (camVob);
	};

	// Setup
	zBOOL saveGame;
	{
		// saveGame ?
		saveGame			= (saveMode==zWLD_SAVE_GAME_SAVED_DYN);

		// fileIOMode
		s_worldSaveMode		= saveMode;

		//
		s_firstVobSaveWorld	= &globalVobTree;
		s_saveLevelMesh		= _saveLevelMesh;
		s_saveWayNet		= (s_worldSaveMode!=zWLD_SAVE_COMPILED_ONLY);
	};

	// ArcMode ermitteln
	zTArchiveMode arcSaveMode	= writeBinary ? zARC_MODE_BINARY_SAFE : zARC_MODE_ASCII;
	if ((writeBinary) && (saveGame))
	{
		// .ini auswerten: falls gewuenscht den schnellen/unsicheren Modus benutzen
		zBOOL fastBinSaveGames	= zoptions->ReadBool ("INTERNAL", "zFastSaveGames", TRUE);
		if (fastBinSaveGames)
			arcSaveMode		= zARC_MODE_BINARY; 
	};

	// Archiv schreiben
	zoptions->ChangeDir		(DIR_WORLD);
	zCArchiver *arc			= zarcFactory.CreateArchiverWrite (fileName, arcSaveMode, saveGame);
	zBOOL res				= (arc!=0);
	if (arc) {
		arc->WriteObject	(this);
		arc->Close			();
		zRELEASE			(arc);
	};

	// CamVob einfuegen
	if (camVob) {
		AddVob (camVob);
		zRELEASE_ACCT_NONULL(camVob);
	};

	// cleanup
	s_firstVobSaveWorld=0;

	return res;
};

zBOOL zCWorld::SaveVobSubtree (const zSTRING& fileName, zCVob* vob, const zBOOL writeBinary, const zBOOL _saveLevelMesh) 
{
	//
	if (!vob) return FALSE;
	if (vob->GetHomeWorld()!=this) return FALSE;

	// Setup
	{
		//
		s_worldSaveMode		= zWLD_SAVE_EDITOR_UNCOMPILED;		// keine statischen/compileten Daten schreiben

		//
		s_firstVobSaveWorld	= vob->globalVobTreeNode;
		s_saveLevelMesh		= _saveLevelMesh;
		s_saveWayNet		= FALSE;
	};

	// Archiv schreiben
	zoptions->ChangeDir					(DIR_WORLD);
	zCArchiver *arc			= zarcFactory.CreateArchiverWrite	(fileName, writeBinary ? zARC_MODE_BINARY_SAFE : zARC_MODE_ASCII, FALSE);
	zBOOL res				= (arc!=0);
	if (arc)
	{
		arc->WriteObject	(this);
		arc->Close			();
		zRELEASE			(arc);
	};

	// cleanup
	s_firstVobSaveWorld=0;
	return res;
};

void zCWorld::TraverseVobTree(zCVobCallback &callback, void *callbackData, zCTree<zCVob>* vobNode)
{       
    if (vobNode==0) vobNode = &globalVobTree;

    // vob schon mal merken (darf noch nicht bearbeitet werden!)
    zCVob* vob = vobNode->GetData();

    // nun erstmal den dranhaengenden VobTree durcharbeiten
    zCTree<zCVob> *newchild;
    zCTree<zCVob> *child = vobNode->GetFirstChild();                
    while (child) 
    {
            newchild = child->GetNextChild();
            TraverseVobTree(callback, callbackData, child);
            child = newchild;
    };      

    // jetzt den Vob bearbeiten
    if (vob) callback.HandleVob(vob, callbackData);       
}

// ===========================================================================================================

zDWORD zCWorld::GetVobHashIndex (const zSTRING& name)
{
	return (zCChecksum::GetBufferCRC32 ((unsigned char*)name.ToChar(), name.Length())) & (zNUM_VOB_HASH-1);
};

zDWORD zCWorld::GetVobHashIndex (zCVob *vob)
{
	return (zCChecksum::GetBufferCRC32 ((unsigned char*)vob->GetVobName().ToChar(), vob->GetVobName().Length())) & (zNUM_VOB_HASH-1);
};

void zCWorld::InsertVobHashTable (zCVob* vob)
{
	if (vob->GetVobName().IsEmpty()) return;
	const zDWORD hash	= GetVobHashIndex(vob);
	vobHashTable[hash].Insert (vob);
};

void zCWorld::RemoveVobHashTable (zCVob* vob) 
{
	if (vob->GetVobName().IsEmpty()) return;
	const zDWORD hash = GetVobHashIndex(vob);
	vobHashTable[hash].Remove (vob);
};

zCVob* zCWorld::SearchVobHashTable (const zSTRING& vobName)
{
	if (vobName.IsEmpty()) return 0;
	const zDWORD hash = GetVobHashIndex(vobName);
	for (int i=0; i<vobHashTable[hash].GetNum(); i++)
	{
		if (vobHashTable[hash][i]->GetVobName()==vobName)	return vobHashTable[hash][i];
	}
	return 0;
};

void zCWorld::SearchVobListHashTable (const zSTRING& vobName, zCArray<zCVob*>& resultVobList)
{
	if (vobName.IsEmpty()) return;
	const zDWORD hash = GetVobHashIndex(vobName);
	for (int i=0; i<vobHashTable[hash].GetNum(); i++)
	{
		if (vobHashTable[hash][i]->GetVobName()==vobName)	
			resultVobList.Insert (vobHashTable[hash][i]);
	}
	return;
};

/* ------------------------------------------------------------------------------
   zCWorld::SetOwnerSession
   28.07.2000	[Speckels]
				Neue Methode: Setzt die Besitzer-Session der Welt
				Muss nicht unbedingt aufgerufen werden. Dann ist 
				ownerSession==0 und auch csPlayer==0 !!!
   ------------------------------------------------------------------------------ */

void zCWorld::SetOwnerSession(zCSession* owner)
{
	ownerSession = owner;
	if (!ownerSession) 
	{
		zRELEASE(csPlayer);
	}
	else 
	{
		csPlayer = ownerSession->GetCutsceneManager()->CreateCutscenePlayer(this);
	}
};

zCSession*	zCWorld::GetOwnerSession()
{
	return ownerSession;
};

/* ----------------------------------------------------------------------
	
	void ResetCutscenePlayer() 

	18.10.2000	[SPECKELS]	Reset und 
							Entfernen des Cutsceneplayer aus dem Manager

   ---------------------------------------------------------------------- */
void zCWorld::ResetCutscenePlayer() 
{	
	if (csPlayer) csPlayer->ResetCutscenePlayer();

	zRELEASE(csPlayer);	

	if (GetOwnerSession())
		csPlayer = ownerSession->GetCutsceneManager()->CreateCutscenePlayer(this);
};


// ===========================================================================================================

void zCWorld::RegisterPerFrameCallback (zCWorldPerFrameCallback *perFrameCallback)
{
	if (!perFrameCallbackList.IsInList (perFrameCallback))
		perFrameCallbackList.Insert (perFrameCallback);
};

void zCWorld::UnregisterPerFrameCallback	(zCWorldPerFrameCallback *perFrameCallback)
{
	perFrameCallbackList.Remove (perFrameCallback);
};

// ===========================================================================================================

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 

