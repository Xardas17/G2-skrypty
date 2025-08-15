/******************************************************************************** 
 
     $Workfile:: zPolygon.cpp         $                $Date:: 8.02.01 7:16     $
     $Revision:: 36                   $             $Modtime:: 8.02.01 7:16     $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zPolygon.cpp $
 * 
 * 36    8.02.01 7:16 Hildebrandt
 * 
 * 35    8.02.01 6:40 Hildebrandt
 * 
 * 34    2.02.01 17:53 Moos
 * 
 * 33    1.02.01 13:13 Moos
 * 
 * 32    27.01.01 19:42 Moos
 * 
 * 31    26.01.01 15:02 Moos
 * 
 * 30    17.01.01 19:20 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 36 $ ($Modtime: 8.02.01 7:16 $)

// ==================================================================================================================

//#include <zPolygon.h>
#include <zCore.h>
#include <zMaterial.h>
#include <z3d.h>
#include <zVob.h>
#include <zSky.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zWorld.h>

#include "zpolypool.h"

// vertices über 'indizes' auf vert-Table referenzieren ? (vert-table: Mesh-lokal)

// evtl. hier mal irgendwann compiler-Switches, die dafuer sorgen, dass in der 
// Release-Game-Version die Konstanten wesentlich kleiner sind !
// FIXME: überarbeiten !! [2. Vertex Typ einführen ? a) database-def. b) after trafos]

/*
class zCVertexT {
public:
	zPOINT3			vertCamSpace;
	zFIX			vertScrX, vertScrY;
	zFIX			dynLight;				// hier ?
//	zCOLOR			dynLight;				// hier ?
	// obsolete:
	zPOINT3		vertNormal;		// hier ?
	zREAL		texu;			// hier ?
	zREAL		texv;
};
*/

/*
	zCVertex **vertList;
	poly->(*vertList)[0]->position

	poly->vertex[0]->position;
	zCVertex 
*/

zCVertex	  **zCPolygon::s_actClipVert=0;								// 'active' polygon clipped Vertex list
int				zCPolygon::s_actNumClipVert=0;							// 'active' polygon num clipped Vertex

zCVertex		zCPolygon::s_clipVertScene[zMAX_POLY_CLIP_VERTS_SCENE]; // holds all clipped verts per scene
int				zCPolygon::s_numClipVertScene;					
zCVertex	  *(zCPolygon::s_vertListScene[zMAX_POLY_VERT_LIST_SCENE]);
int				zCPolygon::s_numVertListScene;

zCVertFeature	zCPolygon::s_clipFeatScene[zMAX_POLY_CLIP_VERTS_SCENE];
int				zCPolygon::s_numClipFeatScene;
zCVertFeature *(zCPolygon::s_featListScene[zMAX_POLY_VERT_LIST_SCENE]);
int				zCPolygon::s_numFeatListScene;

zCArraySort<zCPolygon::zSVertexSavedValues>		zCPolygon::morphedVerticesList_Height;
zCArraySort<zCPolygon::zSVertexSavedValues>		zCPolygon::morphedVerticesList_Wall;
zCArraySort<zCPolygon::zSFeatureSavedValues>	zCPolygon::morphedFeatureList;
zCArray    <zCPolygon::zSPolySavedValues>		zCPolygon::morphedPolysSavedValuesList;



// Mempools
static zCMemPoolBase s_TrianglePointerPool     (sizeof(void *)        * 3,4 * 4096,4 *17 * 4096); 
static zCMemPoolBase s_TriangleVertFeaturePool (sizeof(zCVertFeature) * 3,    4096,        4096); 

void * zCPolygon::S_AllocPointers(int size){
    if (size == 3)
        return s_TrianglePointerPool.Alloc();
    else
        return zNEW(void *)[size];
}

void zCPolygon::S_DeletePointers(int size, void *data){
    if (size == 3)
        s_TrianglePointerPool.Free(data);
    else
        delete[] data;
}

zCVertFeature * zCPolygon::S_AllocVertFeatures(int size){
    if (size == 3)
        return (zCVertFeature *)s_TriangleVertFeaturePool.Alloc();
    else
        return zNEW(zCVertFeature)[size];
}

void zCPolygon::S_DeleteVertFeatures(int size, zCVertFeature *data){
    if (size == 3)
        s_TriangleVertFeaturePool.Free(data);
    else
        delete[] data;
}


/////////////////////////////////////////////////////////////////////
// Clip a polygon to a plane.
/////////////////////////////////////////////////////////////////////

/*

- bei neuen Verts (aus vorhergehender plane) werden unnoetig dot's berechnet, sind aber immer inside
- bei trivIn/trivOut werden u.U. viele unnoetige dot's/clips durchgefuehrt

Verbesserung:
- clipFlags pro Vert und Plane berechnen; trivOut schnell moeglich
- pro Vert cachen: clipFlags, pro plane das dot ?????

*/


/* ----------------------------------------------------------------

	zCPolygon::Constructors and zCPolygon::Destructor
	
	11.10.2000	[SPECKELS]	Aus dem Headerfile ins CPP-File 
	
   ---------------------------------------------------------------- */

#ifdef MEMPOOL_HOELLER
zCPolygon::zCPolygon (zCMesh *) 
{
	if(mesh!=NULL)
	{
		if(GetMeshesPool().IsPoolActive()==TRUE)
			Mesh = mesh;
		else
			Mesh = NULL;
	}
	else
		Mesh = NULL;

	material		= 0;
	numClipVert		= 0;
	polyNumVert		= 0;
	vertex			= 0;
	feature			= 0;
	lastTimeDrawn	= -1;
	lightmap		= 0;
	memset (&flags, 0, sizeof(flags));  
	flags.mustRelight = TRUE;
	flags.sectorIndex= (0xFFFF);		// zSECTOR_INDEX_UNDEF;
};
#else
zCPolygon::zCPolygon () 
{
	material		= 0;
	numClipVert		= 0;
	polyNumVert		= 0;
	vertex			= 0;
	feature			= 0;
	lastTimeDrawn	= -1;
	lightmap		= 0;
	memset (&flags, 0, sizeof(flags));  
	flags.mustRelight = TRUE;
	flags.sectorIndex= (0xFFFF);		// zSECTOR_INDEX_UNDEF;
};
#endif

zCPolygon::~zCPolygon () 
{
	zRELEASE (material);
	zRELEASE (lightmap);
	RemoveVerticesAndFeatures();
};


int Compare_Verts(const void* ele1,const void* ele2) 
{	
	if ( (*(zCPolygon::zSVertexSavedValues*)ele1).vert < (*(zCPolygon::zSVertexSavedValues*)ele2).vert )	return -1;
	if ( (*(zCPolygon::zSVertexSavedValues*)ele1).vert > (*(zCPolygon::zSVertexSavedValues*)ele2).vert )	return +1;
	else return  0;
};

int Compare_Features(const void* ele1,const void* ele2) 
{	
	if ( (*(zCPolygon::zSFeatureSavedValues*)ele1).feat < (*(zCPolygon::zSFeatureSavedValues*)ele2).feat )	return -1;
	if ( (*(zCPolygon::zSFeatureSavedValues*)ele1).feat > (*(zCPolygon::zSFeatureSavedValues*)ele2).feat )	return +1;
	else return  0;
};



void zCPolygon::S_InitMorph()
{
	morphedVerticesList_Height.SetCompare(Compare_Verts);
	morphedVerticesList_Wall  .SetCompare(Compare_Verts);
	morphedFeatureList		  .SetCompare(Compare_Features);
};


void zCPolygon::S_EmptyMorphedVerts()
{
	// diese Methode ist nur für den Spacer, da es dort beim DisposeWorld() öfters Crashes gibt
	// im Spacer werden die gemorphten Verts bei einem DisposeWorld() nicht reseted oder gelöscht, sondern nur entfernt (->Memory Leaks)
	morphedVerticesList_Height	.EmptyList();
	morphedVerticesList_Wall	.EmptyList();
	morphedFeatureList			.EmptyList();
	morphedPolysSavedValuesList	.EmptyList();
};

void zCPolygon::S_ResetMorphedVerts()
{
	// die verschobenen wasser vertices restaurieren
	// FIXME: memory leak bei Programm Ende.
	// Es muss zu Programm Ende noch ein DeleteList() ausgeführt werden
#ifndef COMPILING_SPACER
	if ( (zCCamera::activeCam == NULL)								|| 
		 (zCCamera::activeCam->GetVob() == NULL)					|| 
		 (zCCamera::activeCam->GetVob()->GetHomeWorld() == NULL)	|| 
		 (zCCamera::activeCam->GetVob()->GetHomeWorld()->GetBspTree() == NULL) ) 
	{
		return;
	}
#endif

	for (int i=0; i<morphedVerticesList_Height.GetNum(); i++)
	{
		morphedVerticesList_Height[i].vert->position[VY] = morphedVerticesList_Height[i].offset;
	}

	for (    i=0; i<morphedVerticesList_Wall.GetNum(); i++)
	{
		morphedVerticesList_Wall[i].vert->position[VX] -= morphedVerticesList_Wall[i].offset;
		morphedVerticesList_Wall[i].vert->position[VZ] -= morphedVerticesList_Wall[i].offset;
	}

	for (    i=0; i<morphedFeatureList.GetNum(); i++)
	{
		morphedFeatureList[i].feat->lightStat = morphedFeatureList[i].color;
		//morphedFeatureList[i].feat->SetMapping(morphedFeatureList[i].mapping);
		// TODO: vertex normal 
	}

	for (	 i=0; i<morphedPolysSavedValuesList.GetNum(); i++)
	{
		morphedPolysSavedValuesList[i].poly->SetPlane(morphedPolysSavedValuesList[i].plane);
	}

	morphedVerticesList_Height	.EmptyList();
	morphedVerticesList_Wall	.EmptyList();
	morphedFeatureList			.EmptyList();
	morphedPolysSavedValuesList	.EmptyList();
}

void zCPolygon::S_DeleteMorphedVerts()
{
	S_ResetMorphedVerts();
	morphedVerticesList_Height	.DeleteList();
	morphedVerticesList_Wall	.DeleteList();
	morphedFeatureList			.DeleteList();
	morphedPolysSavedValuesList	.DeleteList();
};


/* ----------------------------------------------------------------------
	
    zCPolygon::ClipToPlane()	

	16.11.2000	[Moos]	
                auf neue Vertices umgestellt
	14.01.2001	[HILDEBRANDT]	
                s_numClipVertScene ist nun FAULT_ONCE statt FATAL

   ---------------------------------------------------------------------- */

zBOOL zCCFASTCALL	zCPolygon::ClipToPlane (zCVertex		**pin, 
											zCVertFeature	**pinFeat,
											int				numPinVerts, 
											zCVertex		**pout, 
											zCVertFeature	**poutFeat,
											int&			numPoutVerts, 
											const zTPlane&	pplane)
{
	#ifdef zDEBUG_COLLECT_STATS
		zengineStats.numPlanesClipped++;
	#endif

	// konservativer Resourcen-Check
	if (s_numClipVertScene+(numPinVerts*4)>zMAX_POLY_CLIP_VERTS_SCENE)
	{
		zERR_FAULT_ONCE ("D: zCPolygon::ClipToPlane:  Too many clipped verts in scene");
		return FALSE;
	};


//	zCVertex	*(*pinvert);
//	zCVertex	*(*poutvert);
//	pinvert		= pin->clipVertPtr;
//	poutvert	= clipVertPtr;
//	curdot = ((*pinvert)->position) * pplane.normal;
//	curin = (curdot >= pplane.distance);

	// FIXME: Mit Quake-Code vergleichen ! (=> r_draw.c, R_RenderPoly())
	// FIXME: Mit Quake-Code vergleichen ! (=> r_draw.c, R_RenderPoly())
	// FIXME: Mit Quake-Code vergleichen ! (=> r_draw.c, R_RenderPoly())

    zREAL		curdot, nextdot, scale;
	const zBOOL smoothPoly	= GetMaterial()->GetSmooth();
	int			poutvert	= 0;
	int			pinvert		= numPinVerts-1;
	curdot					= pin[pinvert]->position * pplane.normal - pplane.distance;
//	curin					= (curdot >= pplane.distance);

	int nextvert=0;
	do
    {
        // Keep the current vertex if it's inside the plane
        if (curdot>0) { 
			pout	 [poutvert] = pin     [pinvert];
			poutFeat [poutvert] = pinFeat [pinvert];
			poutvert++;
		};
        
		nextdot = pin[nextvert]->position * pplane.normal - pplane.distance;

        // ** ACTUAL 3D-CLIPPING **
		// Add a *new* clipped vertex if one end of the current edge is
        // inside the plane and the other is outside
		// FIXME:	- hier bereits projezieren: x/y auf MAX/MIN-Screen, .. (aber Trafo muss vorher!)
        if ((curdot>0) != (nextdot>0))
		{
			scale = (curdot) / (curdot - nextdot);

			// FIXME: evtl. Abfragen, die nur clippen, was wirklich nötig ist

			// clip Vertex
			const zPOINT3&  pinNextPos		= (*pin[nextvert]).position; 
			const zPOINT3&  pinActPos		= (*pin[pinvert ]).position;
			zCVertex& newVert				= s_clipVertScene[s_numClipVertScene++];
			newVert.position				= pinActPos + scale * (pinNextPos - pinActPos);
//			newVert.transformed				= -1;
            newVert.ResetVertexTransform();
			pout[poutvert]					= &(newVert);

			// clip Feature
			const zCVertFeature& pinFNext	= *pinFeat			[nextvert];
			const zCVertFeature& pinFAct	= *pinFeat			[pinvert]; 

			// FIXME: zum GM wieder raus!
			//zERR_ASSERT_STRICT(s_numClipFeatScene<zMAX_POLY_CLIP_VERTS_SCENE);

			zCVertFeature& newFeat			= s_clipFeatScene	[s_numClipFeatScene++];
			
			newFeat.texu					= pinFAct.texu	+ (pinFNext.texu - pinFAct.texu) * scale;
			newFeat.texv					= pinFAct.texv	+ (pinFNext.texv - pinFAct.texv) * scale;

			int intScale					= zFloat2Int(scale*255.0F); 
			// FIXME: muss wohl noch was gemacht werden..
			//        haengt aber auch davon ab, ob vor oder nach dem clippen beleuchtet wird !
			newFeat.lightStat.LerpRGBA (intScale, pinFAct.lightStat, pinFNext.lightStat);
			newFeat.lightDyn .LerpRGBA (intScale, pinFAct.lightDyn, pinFNext.lightDyn);
//			newFeat.lightDyn = newFeat.lightStat;


			// nur die Vert-Normale clippen, falls es ein 'gesmoothtes' Poly ist
			// FIXME: normalisiern ??
			if (smoothPoly) {
				newFeat.vertNormal= pinFAct.vertNormal + (pinFNext.vertNormal- pinFAct.vertNormal) * scale;	
			};

			poutFeat [poutvert]= &(newFeat); 

			// 
			poutvert++;
        }

		curdot	= nextdot;
		pinvert	= nextvert;
		nextvert++;
    } while (nextvert<numPinVerts);

    numPoutVerts = poutvert;
    if (poutvert< 3) return 0;

    return 1;
}


/* ----------------------------------------------------------------------
	
    zCPolygon::ClipToPlane()	

	16.11.2000	[Moos]	
                auf neue Vertices umgestellt
	14.01.2001	[HILDEBRANDT]	
                s_numClipVertScene ist nun FAULT_ONCE statt FATAL

   ---------------------------------------------------------------------- */

zBOOL zCCFASTCALL	zCPolygon::ClipToPlane_Occluder (zCVertex		**pin, 
													int				numPinVerts, 
													zCVertex		**pout, 
													int&			numPoutVerts, 
													const zTPlane&	pplane)
{
	#ifdef zDEBUG_COLLECT_STATS
		zengineStats.numPlanesClipped++;
	#endif

	// konservativer Resourcen-Check
	if (s_numClipVertScene+(numPinVerts*4)>zMAX_POLY_CLIP_VERTS_SCENE)
	{
		zERR_FAULT_ONCE ("D: zCPolygon::ClipToPlane:  Too many clipped verts in scene");
		return FALSE;
	};


    zREAL		curdot, nextdot, scale;
	int			poutvert	= 0;
	int			pinvert		= numPinVerts-1;
	curdot					= pin[pinvert]->position * pplane.normal - pplane.distance;

	int nextvert=0;
	do
    {
        // Keep the current vertex if it's inside the plane
        if (curdot>0) { 
			pout	 [poutvert] = pin     [pinvert];
			poutvert++;
		};
        
		nextdot = pin[nextvert]->position * pplane.normal - pplane.distance;

        // ** ACTUAL 3D-CLIPPING **
		// Add a *new* clipped vertex if one end of the current edge is
        // inside the plane and the other is outside
		// FIXME:	- hier bereits projezieren: x/y auf MAX/MIN-Screen, .. (aber Trafo muss vorher!)
        if ((curdot>0) != (nextdot>0))
		{
			scale = (curdot) / (curdot - nextdot);

			// clip Vertex
			const zPOINT3&  pinNextPos		= (*pin[nextvert]).position; 
			const zPOINT3&  pinActPos		= (*pin[pinvert ]).position;
			zCVertex& newVert				= s_clipVertScene[s_numClipVertScene++];
			newVert.position				= pinActPos + scale * (pinNextPos - pinActPos);
            newVert.ResetVertexTransform();

			pout[poutvert]					= &(newVert);
			poutvert++;
        }

		curdot	= nextdot;
		pinvert	= nextvert;
		nextvert++;
    } 
	while (nextvert<numPinVerts);

    numPoutVerts = poutvert;
    if (poutvert< 3) return 0;

    return 1;
}



/////////////////////////////////////////////////////////////////////
// Clip a polygon to the frustum.
/////////////////////////////////////////////////////////////////////

void zCPolygon::PrepareRendering() {
	s_numClipVertScene = 0;
	s_numVertListScene = 0;

	s_numClipFeatScene = 0;
	s_numFeatListScene = 0;
};

void zCPolygon::Unclip() {
	clipVert	= vertex;
	numClipVert = polyNumVert;

	clipFeat	= feature;
	CopyClipFeaturesForTexAniMapping();
};

void zCPolygon::Unclip_Occluder() {
	clipVert	= vertex;
	numClipVert = polyNumVert;

	clipFeat	= feature;
};


void zCPolygon::CopyClipFeaturesForTexAniMapping()
{
	zERR_ASSERT (GetMaterial());
	if (GetMaterial()->GetTexAniMapping())
	{
		clipFeat			= &(s_featListScene[s_numFeatListScene]);
		s_numFeatListScene += numClipVert;

		for (int i=0; i<numClipVert; i++)
		{
			zCVertFeature& newFeat	= s_clipFeatScene	[s_numClipFeatScene++];
			newFeat					= *(feature[i]);
			clipFeat[i]				= &newFeat;
		};
	};
};

int zCCFASTCALL	zCPolygon::ClipToFrustum (const int clipFlags) 
{
//int clipFlags = clipFlags_in;

	// - Falls das Material des Polys 'TexAniMapping' (= UV Ani) hat, muessen die UV-Koords (also die Features
	//   des Polys komplett kopiert werden, da sie im folgenden modifiziert werden.

	// FIXME: optimieren ! => mit Quake-Code vergleichen
	// FIXME: der Fall, dass ein Poly hier hinein gelangt, allerdings gar kein Clipping noetig ist,
	//        geschieht sehr oft => a) diesen Fall optimieren, b) arbeiten die hoeheren Ebenen korrekt (Bbox/Frustum) ?

	// 0 = nicht clippen
	// 1 = links clippen, 2 = links&rechts clippen, ...
//	clipFlags = clipFlags & zCCamera::CLIP_FLAGS_FULL_WO_FAR;

	// Frustum-Planes aussortieren, gegen die nicht 'hart' geclippt werden soll
	if ((clipFlags & zCCamera::CLIP_FLAGS_FULL_WO_FAR)<=0) {
		Unclip();
		return TRUE;
	};

	#ifdef zDEBUG_COLLECT_STATS
		zengineStats.numPolysClipped++;
	#endif

	// clipFlags: bits 0-3 stehen fuer die Frustum-Planes gegen die geclippt werden soll
	// ACHTUNG: falls nicht innerhalb des Frustums: numClipVert=0 !
	// tmp-Poly für 2-Platz-Ring-Buffer (hin&her-schaufeln)
	static zCVertex		 *(tempVert[zMAX_POLY_CLIP_VERTS]);
	static zCVertFeature *(tempFeat[zMAX_POLY_CLIP_VERTS]);
	
	// scene-vertex-list buffers
	int				i, curpoly;
    zCVertex		**(ppoly    [2]);  
    zCVertFeature	**(ppolyFeat[2]);  
	int				pnum[2];
	zTPlane			*frustumplanes;
	frustumplanes	= zCCamera::activeCam->frustumplanes;

	// Liste von Vertices vergeben
	if (s_numVertListScene>zMAX_POLY_VERT_LIST_SCENE-32) {	// -32 => safety
		static zBOOL gaveWarning = FALSE;
//		if (!gaveWarning) {
			zERR_WARNING("D: (zCPolygon::ClipToFrustum) too many clipped Polys in Scene ");
//			gaveWarning = TRUE;
//		};
		// tue so, als ob Poly degeneriert sei
		return FALSE;
	};
	clipVert = &(s_vertListScene[s_numVertListScene]);
	clipFeat = &(s_featListScene[s_numFeatListScene]);

	// vert-Daten nach Clip-Vert kopieren
	numClipVert = polyNumVert;
	memcpy (clipVert, vertex , sizeof (zCVertex*     )*numClipVert ); // dest, source
//	memcpy (clipFeat, feature, sizeof (zCVertFeature*)*numClipVert ); // dest, source (jetzt etwas weiter unten..)

	// Feature kopieren
	zERR_ASSERT (GetMaterial());
	if (GetMaterial()->GetTexAniMapping())
	{
		for (i=0; i<numClipVert; i++)
		{
			zCVertFeature& newFeat	= s_clipFeatScene	[s_numClipFeatScene++];
			newFeat					= *(feature[i]);
			clipFeat[i]				= &newFeat;
		};
	} else
	{
		memcpy (clipFeat, feature, sizeof (zCVertFeature*)*numClipVert ); // dest, source
	};
    
	// loop setup
    curpoly		  = 0;
    ppoly     [0] = clipVert;	pnum[0] = numClipVert;
	ppoly	  [1] = tempVert;	//pnum[1] = numTempVert;

    ppolyFeat [0] = clipFeat;
	ppolyFeat [1] = tempFeat;

	for (i=0 ; i<(zCCamera::NUM_FRUSTUM_PLANES_WO_FAR); i++)
//	for (i=0 ; i<(zCCamera::NUM_FRUSTUM_PLANES_WO_FAR-1); i++)
//	for (i=0 ; i<(zCCamera::NUM_FRUSTUM_PLANES-1); i++)
    {
		if ((clipFlags & (1<<i))==0) continue;

        // in, out
		// stoppen, falls Poly 'degeneriert'
		if (! ClipToPlane(	ppoly			[curpoly], 
							ppolyFeat		[curpoly],
							pnum			[curpoly],
							ppoly			[curpoly^1],
							ppolyFeat		[curpoly^1],
							pnum			[curpoly^1],
							frustumplanes	[i] ) ) 
		{
			numClipVert = 0;
			return FALSE;
		};
        curpoly ^= 1;
    };

	// war das letzte Target auch "this" ?
	// wenn nicht: von pin nach target kopieren
	if (curpoly==1) {
		memcpy (clipVert, tempVert, sizeof (zCVertex*     )*pnum[1]); // dest, source
		memcpy (clipFeat, tempFeat, sizeof (zCVertFeature*)*pnum[1]); // dest, source
		numClipVert = pnum[1];
	} else 
		numClipVert = pnum[0];

	// s_numVertListScene Anzahl updaten
	s_numVertListScene += numClipVert;
	s_numFeatListScene += numClipVert;

	return TRUE;
}



int zCCFASTCALL	zCPolygon::ClipToFrustum_Occluder(const int clipFlags) 
{

	// Frustum-Planes aussortieren, gegen die nicht 'hart' geclippt werden soll
	if ((clipFlags & zCCamera::CLIP_FLAGS_FULL_WO_FAR)<=0) {
#ifdef COMPILING_SPACER
		Unclip();
#else
		Unclip_Occluder();
#endif
		return TRUE;
	};

	#ifdef zDEBUG_COLLECT_STATS
		zengineStats.numPolysClipped++;
	#endif

	// clipFlags: bits 0-3 stehen fuer die Frustum-Planes gegen die geclippt werden soll
	// ACHTUNG: falls nicht innerhalb des Frustums: numClipVert=0 !
	// tmp-Poly für 2-Platz-Ring-Buffer (hin&her-schaufeln)
	static zCVertex		 *(tempVert[zMAX_POLY_CLIP_VERTS]);
	
	// scene-vertex-list buffers
	int				i, curpoly;
    zCVertex		**(ppoly    [2]);  
	int				pnum[2];
	zTPlane			*frustumplanes;
	frustumplanes	= zCCamera::activeCam->frustumplanes;

	// Liste von Vertices vergeben
	if (s_numVertListScene>zMAX_POLY_VERT_LIST_SCENE-32) {	// -32 => safety
		static zBOOL gaveWarning = FALSE;
//		if (!gaveWarning) {
			zERR_WARNING("D: (zCPolygon::ClipToFrustum_Occluder) too many clipped polys in Scene ");
//			gaveWarning = TRUE;
//		};
		// tue so, als ob Poly degeneriert sei
		return FALSE;
	};
	clipVert = &(s_vertListScene[s_numVertListScene]);

	// vert-Daten nach Clip-Vert kopieren
	numClipVert = polyNumVert;
	memcpy (clipVert, vertex , sizeof (zCVertex*     )*numClipVert ); // dest, source

    
	// loop setup
    curpoly		  = 0;
    ppoly     [0] = clipVert;	pnum[0] = numClipVert;
	ppoly	  [1] = tempVert;	

	for (i=0 ; i<(zCCamera::NUM_FRUSTUM_PLANES_WO_FAR); i++)
    {
		if ((clipFlags & (1<<i))==0) continue;

        // in, out
		// stoppen, falls Poly 'degeneriert'
		if (! ClipToPlane_Occluder(	ppoly			[curpoly], 
									pnum			[curpoly],
									ppoly			[curpoly^1],
									pnum			[curpoly^1],
									frustumplanes	[i] ) ) 
		{
			numClipVert = 0;
			return FALSE;
		};
        curpoly ^= 1;
    };

	// war das letzte Target auch "this" ?
	// wenn nicht: von pin nach target kopieren
	if (curpoly==1) {
		memcpy (clipVert, tempVert, sizeof (zCVertex*     )*pnum[1]); // dest, source
		numClipVert = pnum[1];
	} else 
		numClipVert = pnum[0];

	// s_numVertListScene Anzahl updaten
	s_numVertListScene += numClipVert;

	return TRUE;
}



int zCPolygon::ClassifyPlane (const zTPlane& plane) {
	int front	= 0;
	int back	= 0;
	int onplane = 0;
	
	for(int n=0; n<polyNumVert; n++) {
		switch (plane.ClassifyPoint (vertex[n]->position)) {
		case zPLANE_INFRONT:
			front++;
			break;
		case zPLANE_BEHIND:
			back++;
			break;
		case zPLANE_ONPLANE:
			front++;
			back++;
			onplane++;
			break;
		}
	}
	if (onplane== polyNumVert)  return zPLANE_ONPLANE ; else	// FIRST !!!!
	if (front  == polyNumVert)	return zPLANE_INFRONT ; else 
	if (back   == polyNumVert)	return zPLANE_BEHIND  ; else
								return zPLANE_SPANNING;
}

int zCPolygon::ClassifyPlaneBSPBuild (const zTPlane& plane) {
	int front	= 0;
	int back	= 0;
	int onplane = 0;
	
	for(int n=0; n<polyNumVert; n++) {
		switch (plane.ClassifyPointBSPBuild (vertex[n]->position)) {
		case zPLANE_INFRONT:
			front++;
			break;
		case zPLANE_BEHIND:
			back++;
			break;
		case zPLANE_ONPLANE:
			front++;
			back++;
			onplane++;
			break;
		}
	}
	if (onplane== polyNumVert)  return zPLANE_ONPLANE ; else	// FIRST !!!!
	if (front  == polyNumVert)	return zPLANE_INFRONT ; else 
	if (back   == polyNumVert)	return zPLANE_BEHIND  ; else
								return zPLANE_SPANNING;
}
/*
inline float _Abs	(const float a) {
	// src: sin dll-Source1.01
	int tmp = * ( int * ) &a;
	tmp &= 0x7FFFFFFF;
	return * ( float * ) &tmp;
};

		zBOOL _IsEqualEps (const zVEC3& u, const zVEC3& b) {									// fuzzy compare with small epsilon
			zREAL a,c;
			a = zREAL(u.n[0]-b.n[0]); c = _Abs(a);		zerr.Message ("D: "+zSTRING(a,8)+", "+zSTRING(c,8));
			a = zREAL(u.n[1]-b.n[1]); c = _Abs(a);		zerr.Message ("D: "+zSTRING(a,8)+", "+zSTRING(c,8));
			a = zREAL(u.n[2]-b.n[2]); c = _Abs(a);		zerr.Message ("D: "+zSTRING(a,8)+", "+zSTRING(c,8));
			return ((_Abs(zREAL(u.n[0]-b.n[0])) < zALG_EQUAL_EPSILON) &&
					(_Abs(zREAL(u.n[1]-b.n[1])) < zALG_EQUAL_EPSILON) &&
					(_Abs(zREAL(u.n[2]-b.n[2])) < zALG_EQUAL_EPSILON));
		};

		inline zBOOL _IsColinear (const zVEC3& a, const zVEC3& b, const zVEC3& c) {
			// Achtung: Reihenfolge der Verts ist wichtig (Abs darf nicht!)
			zVEC3 u = (b-a);
			zVEC3 v = (c-b);
			u.Normalize();
			v.Normalize();
			return _IsEqualEps(u,v);
		};
*/

zBOOL zCPolygon::CalcNormal() {
	assert (polyNumVert>=3);
	zBOOL	colinear;
	zVEC4	plane;
	int		n=2;
	do {
		// make sure that the 3 chosen points are not colinear
		zVEC3 u		= (vertex[1]->position-vertex[0]->position);
		zVEC3 v		= (vertex[n]->position-vertex[1]->position);
		zREAL lenu	= u.Length();
		zREAL lenv	= v.Length();
		if ((u!=0) && (v!=0))
		{
			u		/= lenu;
			v		/= lenv;
			colinear= u.IsEqualEps(v) || u.IsEqualEps(-v);
			if (!colinear) 
			{
				plane = Alg_FindPlaneCoeff(vertex[0]->position,
										   vertex[1]->position,
										   vertex[n]->position);
				goto found;
			};
		};
		n++;
	} while (n<polyNumVert);

	// Fehler !! Alle Kombis bereits probiert !
#ifndef zDEBUG_DONT_WARN_POLY_DEGEN
	zERR_MESSAGE(8,0,"zCPolygon::CalcNormal(): Degenerate Polygon, center at:"+GetCenter().GetString());
#endif
/*	{
		zCMaterial *mat = zNEW(zCMaterial());
		mat->SetColor	(255,0,0);
		mat->SetTexture	(0);
		SetMaterial (mat);
	};*/ 
	// korrekte PolyPlane kann nicht berechnet werden
	// trotzdem mit irgendwelchen 'neutralen' Werten fuellen, um Probs zu vermeiden.
	polyPlane.distance	= 0;
	polyPlane.normal	= zVEC3(1,0,0);
	return FALSE;

	// Oki
found:;
	polyPlane.distance	  = plane.n[VD];
	polyPlane.normal.n[0] = plane.n[0];		// ugly...
	polyPlane.normal.n[1] = plane.n[1];
	polyPlane.normal.n[2] = plane.n[2];

	//CalcNormalMainAxis();

	return TRUE;
};


zBOOL zCPolygon::CalcNormalApprox() {
	assert (polyNumVert>=3);
	zBOOL	colinear;
	zVEC4	plane;
	int		n=2;
	do {
		// make sure that the 3 chosen points are not colinear
		zVEC3 u		= (vertex[1]->position-vertex[0]->position);
		zVEC3 v		= (vertex[n]->position-vertex[1]->position);
		zREAL lenu	= u.LengthApprox();
		zREAL lenv	= v.LengthApprox();
		if ((u!=0) && (v!=0))
		{
			u		/= lenu;
			v		/= lenv;
			colinear= u.IsEqualEps(v) || u.IsEqualEps(-v);
			if (!colinear) 
			{
				plane = Alg_FindPlaneCoeffApprox(vertex[0]->position,
												 vertex[1]->position,
												 vertex[n]->position);
				goto found;
			};
		};
		n++;
	} while (n<polyNumVert);

	// korrekte PolyPlane kann nicht berechnet werden
	// trotzdem mit irgendwelchen 'neutralen' Werten fuellen, um Probs zu vermeiden.
	polyPlane.distance	= 0;
	polyPlane.normal	= zVEC3(1,0,0);
	return FALSE;

	// Oki
found:;
	polyPlane.distance	  = plane.n[VD];
	polyPlane.normal.n[0] = plane.n[0];		// ugly...
	polyPlane.normal.n[1] = plane.n[1];
	polyPlane.normal.n[2] = plane.n[2];

	return TRUE;
};


/* ----------------------------------------------------------------------

    zCPolygon::GetScreenBBox2D()

	16.11.2000	[Moos]	
                auf neue Vertices umgestellt

   ---------------------------------------------------------------------- */

void zCPolygon::GetScreenBBox2D (zTBBox2D& outbbox2D) {
	outbbox2D.Init();
	for (int i=0; i<numClipVert; i++) {
		zCVertexTransform *vert = clipVert[i]->VertexTransform();
		// X
		zREAL x = zREAL(vert->vertScrX);
		if (x<outbbox2D.mins[VX]) outbbox2D.mins[VX]= x;
		if (x>outbbox2D.maxs[VX]) outbbox2D.maxs[VX]= x;
		// Y
		zREAL y = zREAL(vert->vertScrY);
		if (y<outbbox2D.mins[VY]) outbbox2D.mins[VY]= y;
		if (y>outbbox2D.maxs[VY]) outbbox2D.maxs[VY]= y;
	};
};

/* ----------------------------------------------------------------------

    zCPolygon::DrawWire()

	16.11.2000	[Moos]	
                auf neue Vertices umgestellt

   ---------------------------------------------------------------------- */

void zCPolygon::DrawWire (zCOLOR color) const {
	for (int vertCtr=0; vertCtr<numClipVert; vertCtr++) {
		int next = (vertCtr+1) % numClipVert;

        zCVertexTransform *v1 = clipVert[vertCtr]->VertexTransform();
        zCVertexTransform *v2 = clipVert[next   ]->VertexTransform();

		int x1 = zFloat2Int(v1->vertScrX);
		int y1 = zFloat2Int(v1->vertScrY);

		int x2 = zFloat2Int(v2->vertScrX);
		int y2 = zFloat2Int(v2->vertScrY);

		zlineCache.Line (x1,y1,x2,y2, color);
//		zCCamera::activeCam->targetDtpItem->Line (x1,y1,x2,y2, color);
	};
};


// mlight
/*
void zCPolygon::Light (zCVobLight& light) {
	Light (light.GetPositionWorld(), light.GetRange());

	// spec.
	zPOINT3	lightSourcePos	= light.GetPositionWorld();						// richtig ??
	zPOINT3 viewerPos		= zCCamera::activeCamPos;
	zREAL	rangeInv		= zREAL(1) / zREAL(light.GetRange());
	zPOINT3 half			= (lightSourcePos + viewerPos).Normalize();

	zREAL	ka,kd,ks,ksm;
	if (material==0) {
		ka  = 0.0f;
		kd  = 0.6f;
		ks  = 0.4f;
		ksm = 1.0f;
	} else {
		ka  = material->kambient;
		kd  = material->kdiffuse;
		ks  = material->kspecular;
		ksm = material->kspecularPower;
	};

	zBOOL smooth = FALSE;
	if (material) smooth = material->GetSmooth();

	for (int i=0; i<numClipVert; i++) {
		zCVertex		*actVert = clipVert[i]; 
		zCVertFeature	*actFeat = clipFeat[i]; 

		zPOINT3 view;
		zREAL	dot;
		zREAL	i = 0;
		
		////////////////////////
		// 1. Diffuse         //
		////////////////////////
		// angle: face/light
		// dot<0 => poly ist lq abgewandt
		// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
		view = actVert->position - lightSourcePos;
		view.Normalize(); 
		if (smooth) dot = -(view * actFeat->vertNormal);
		else		dot = -(view * polyPlane.normal);
		i += (kd*dot);

		////////////////////////
		// 2. Specular        //
		////////////////////////
		zREAL s;
		zPOINT3		normal;
		if (smooth) normal = actFeat->vertNormal;
		else		normal = polyPlane.normal;
		zPOINT3 l= lightSourcePos - actVert->position;
		zPOINT3 r= 2 * normal * (normal * l) - l;
		r.Normalize();
		zPOINT3 v = viewerPos - actVert->position;
		v.Normalize();
//		s = normal * half;
		s = (r * v);
		if (s<0) s = 0;
		i += ks * pow( s, ksm);
		

		////////////////////////
		// 3. Distance-Falloff /
		////////////////////////
		{//			zREAL dist = (actVert->vertCamSpace).Length();
			zREAL dist = (actVert->position-lightSourcePos).Length();
//			zREAL dist = (actVert->vertCamSpace[VZ]);
			if (dist>light.GetRange())	dist = 0; else
										dist = 1-(dist * rangeInv);
			i *= (dist);
		};

		////////////////////////
		// 4. Ambient		  //
		////////////////////////
		i += ka;

		// combine
		zClamp (i, zREAL(0.0), zREAL(1.0));
		i = 1.0-i;
//		actVert->lightInt = int(i*65536);
//		actVert->lightInt = int(32768);

		// Farbe des Lichtes durch die Intensitaet skalieren
		int		intens		= int(i*255);
		zCOLOR	lightColor	= light.GetColor();

		lightColor.r = (lightColor.r * intens) >> 8;
		lightColor.g = (lightColor.g * intens) >> 8;
		lightColor.b = (lightColor.b * intens) >> 8;

		// Die Effektive Farbe des Lichtes dem Vert-Feature hinzuaddieren (lightDyn)
		actFeat->lightDyn.r		+= lightColor.r; 
		actFeat->lightDyn.g		+= lightColor.g;
		actFeat->lightDyn.b		+= lightColor.b;
		actFeat->lightDyn.alpha	+= lightColor.alpha;
	};
};
*/
/*
void zCPolygon::Light (zPOINT3 lightSourcePos, int playerLightInt) {
//	playerLightInt = 200;
	zREAL	playerLIInv = zREAL(1) / zREAL(playerLightInt);

	for (int i=0; i<numClipVert; i++) {
		zCVertex		*actVert = clipVert[i];
		zCVertFeature	*actFeat = clipFeat[i]; 

		zREAL i;
		zREAL dist = (actVert->vertCamSpace[VZ]);
		if (dist>playerLightInt) dist = 0; else
								 dist = 1-(dist * playerLIInv);
		i = dist;
		// Farbe des Lichtes durch die Intensitaet skalieren
		{
			int	intens		= int(i*255);
			int	lightInt	= (200 * intens) >> 8;

			int r = int(actFeat->lightDyn.r) + lightInt;
			int g = int(actFeat->lightDyn.g) + lightInt;
			int b = int(actFeat->lightDyn.b) + lightInt;
			zClamp (r, 0, 255);
			zClamp (g, 0, 255);
			zClamp (b, 0, 255);

			// Die Effektive Farbe des Lichtes dem Vert-Feature hinzuaddieren (lightDyn)
			actFeat->lightDyn.r = r;
			actFeat->lightDyn.g = g;
			actFeat->lightDyn.b = b;
		};
	};
};
*/

/*
// VARIANTE: alles im WorldSpace, loop: polys, verts, lights
void zCPolygon::LightPolyList (const zCArray<zCVob*>& vobLightList, 
							   zCPolygon** polyList, 
							   int numPoly,
							   zMATRIX4 *trafoWorldToObj) {
//return;
	// Beleuchtung im World-Space !

//actPoly->clipFeat[vertCtr]->lightDyn = actPoly->clipFeat[vertCtr]->lightStat;
	if (vobLightList.GetNumInList()<=0) return;

//	zCPolygon	*poly	= polyList[0];
	zCPolygon	**poly = polyList;

	for (int polyNr=0; polyNr<numPoly; poly++, polyNr++) {
//		poly = polyList[polyNr];
		if ((*poly)->IsPortal()) continue; 
		zCMaterial	*mat	= (*poly)->GetMaterial();
		if (!mat) continue;

		zPOINT3	normal;

		zREAL	ka,kd,ks,ksm, kprea;
		kprea	= mat->kpreAmbient;
		ka		= mat->kambient;
		kd		= mat->kdiffuse;
		ks		= mat->kspecular;
		ksm		= mat->kspecularPower; 

		zBOOL smooth = FALSE;
		if (mat)		smooth = mat->GetSmooth();
		if (!smooth)	normal = (*poly)->polyPlane.normal;

		for (int i=0; i<(*poly)->polyNumVert; i++) 
		{
			zCVertex		*actVert = (*poly)->vertex [i]; 
			zCVertFeature	*actFeat = (*poly)->feature[i]; 
//			actFeat->lightDyn = actFeat->lightStat;
			// PROBLEM: Ein Poly kann x-mal in diese Methode gelangen =>
			//          alte Ergebniss werden durch folgendes dann wieder ueberschrieben...
			int r = int(actFeat->lightStat.GetRedByte	());
			int g = int(actFeat->lightStat.GetGreenByte	()); 
			int b = int(actFeat->lightStat.GetBlueByte	());

			for (int lightNr=0; lightNr<vobLightList.GetNumInList(); lightNr++) 
			{

				if (vobLightList[lightNr]->GetVobType()!=zVOB_TYPE_LIGHT) continue;
				zCVobLight	*light			= (zCVobLight*)vobLightList[lightNr];
				zPOINT3		lightSourcePos	= light->GetPositionWorld();
				zREAL		playerLIInv		= light->GetRangeInv();
//if (light->GetVobName()!="VOBM2") continue;

				zVEC3	view;
				zREAL	dot;
				zREAL	i;

				i		= 0;
				view	= actVert->position - lightSourcePos;

				///////////////////////////
				// 1. Distance-Falloff A //
				///////////////////////////

				zREAL dist; 
				zREAL len = view.LengthApprox();
				if (len>light->GetRange()) goto dontLightVert;
//				if (len>light->GetRange()) { r = g = b = 255; goto dontLightVert; };
				dist = 1-(len * playerLIInv);
//				dist = 1;

				////////////////////////
				// 2. Diffuse         //
				////////////////////////
				// angle: face/light

				// dot<0 => poly ist lq abgewandt
				// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
				if (len!=0)
				view = view / len;
//				view.Normalize();
//				dot = -(view * normal);
				if (smooth) dot = -(view * actFeat->vertNormal);
				else		dot = -(view * normal);

				if (dot<0) goto dontLightVert;
				i += (kd*dot);

				////////////////////////
				// 4. PreAmbient	  //
				////////////////////////
				i += kprea;

				///////////////////////////
				// 5. Distance-Falloff B //
				///////////////////////////
				i *= (dist);

				////////////////////////
				// 6. Ambient		  //
				////////////////////////
				i += ka;

				// if (i==0.0F) continue;
				// zClamp (i, zREAL(0.0), zREAL(1.0));

				// Farbe des Lichtes durch die Intensitaet skalieren
				{
//					int	intens = int(i*255.0F);
					int	intens = zFloat2Int(i*255.0F);

					r += (((int)light->GetColorR() * intens) >> 8);
					g += (((int)light->GetColorG() * intens) >> 8);
					b += (((int)light->GetColorB() * intens) >> 8);
//					r = g = 0;
//					b = 255;
				};
dontLightVert:;

			};
			zClamp (r, 0, 255);
			zClamp (g, 0, 255);
			zClamp (b, 0, 255);

			// Die Effektive Farbe des Lichtes dem Vert-Feature hinzuaddieren (lightDyn)
			actFeat->lightDyn.r = r;
			actFeat->lightDyn.g = g;
			actFeat->lightDyn.b = b;
		};
	};
}; 
*/

void zCPolygon::LightPolyList (const zCArray<zCVobLight*>& vobLightList, 
							   zCPolygon** polyList, 
							   int numPoly,
							   zMATRIX4 *trafoWorldToObj) {
//approxdistance=max(dx,dy,dz)+((min(dx,dy,dz)+med(dx,dy,dz))>>2)

//actPoly->clipFeat[vertCtr]->lightDyn = actPoly->clipFeat[vertCtr]->lightStat;
	if (vobLightList.GetNumInList()<=0) return;

	for (int lightNr=0; lightNr<vobLightList.GetNumInList(); lightNr++) 
	{
		zCVobLight	*light			= vobLightList[lightNr];
		zREAL		playerLIInv		= light->GetRangeInv();
		int			lightR			= (int)light->GetColorR(); 
		int			lightG			= (int)light->GetColorG();
		int			lightB			= (int)light->GetColorB();
		zPOINT3		lightSourcePos;
		if (trafoWorldToObj)	lightSourcePos = *trafoWorldToObj * light->GetPositionWorld();
		else					lightSourcePos = light->GetPositionWorld();

		if (light->GetLightQuality()==zVOBLIGHT_QUAL_FASTEST) {
			zCPolygon **poly = polyList;
			for (int polyNr=0; polyNr<numPoly; poly++, polyNr++) { 
				int actNumVert = (*poly)->polyNumVert-1;
				do {
					zCVertex		*actVert = (*poly)->vertex [actNumVert]; 
					zCVertFeature	*actFeat = (*poly)->feature[actNumVert]; 
					if (lightNr==0) actFeat->lightDyn = actFeat->lightStat;

					zVEC3	view= actVert->position - lightSourcePos; 
					zREAL	len = zAbs(view.n[VX]) + zAbs(view.n[VY]) + zAbs(view.n[VZ]);
//					zREAL	xa	= zAbs(view.n[VX]);
//					zREAL	ya	= zAbs(view.n[VY]);
//					zREAL	za	= zAbs(view.n[VZ]);
//					zREAL	len = xa+ya+za - zMin(zMin (xa, ya), za) * 0.5F; 
					if (len>light->GetRange()) continue;
					len	= 1-(len * playerLIInv);
					{
						int	intens = zFloat2Int(len*255.0F);
						int r = (int)actFeat->lightDyn.r + ((lightR * intens) >> 8); if (r>255) r=255;
						int g = (int)actFeat->lightDyn.g + ((lightG * intens) >> 8); if (g>255) g=255;
						int b = (int)actFeat->lightDyn.b + ((lightB * intens) >> 8); if (b>255) b=255;
						actFeat->lightDyn.r = r;
						actFeat->lightDyn.g = g;
						actFeat->lightDyn.b = b;
					};
  				} while (actNumVert--);
			};
		} else 
		if (light->GetLightQuality()==zVOBLIGHT_QUAL_MID) {
			zCPolygon **poly = polyList;
			for (int polyNr=0; polyNr<numPoly; poly++, polyNr++) { 
				int actNumVert = (*poly)->polyNumVert-1;
				do {
					zCVertex		*actVert = (*poly)->vertex [actNumVert]; 
					zCVertFeature	*actFeat = (*poly)->feature[actNumVert]; 
					if (lightNr==0) actFeat->lightDyn = actFeat->lightStat;

					zVEC3	view= actVert->position - lightSourcePos; 
					zREAL	len = view.LengthApprox();
					if (len>light->GetRange()) continue;
					len	= 1-(len * playerLIInv);
					{
						int	intens	= zFloat2Int(len*255.0F);
						int r		= (int)actFeat->lightDyn.r + ((lightR * intens) >> 8); if (r>255) r=255;
						int g		= (int)actFeat->lightDyn.g + ((lightG * intens) >> 8); if (g>255) g=255;
						int b		= (int)actFeat->lightDyn.b + ((lightB * intens) >> 8); if (b>255) b=255;
						actFeat->lightDyn.r = r;
						actFeat->lightDyn.g = g;
						actFeat->lightDyn.b = b;
					};
  				} while (actNumVert--);
			};
		} else {
			zCPolygon **poly = polyList;

			for (int polyNr=0; polyNr<numPoly; poly++, polyNr++) { 
				if ((*poly)->IsPortal()) continue; 
				zCMaterial	*mat	= (*poly)->GetMaterial();
				if (!mat) continue;


				zREAL	ka,kd;
//				kprea	= mat->kpreAmbient;
				ka		= mat->kambient;
				kd		= mat->kdiffuse;
//				ks		= mat->kspecular;
//				ksm		= mat->kspecularPower; 

				zVEC3 normal;
				zBOOL smooth;
				smooth = mat->GetSmooth();
				if (!smooth) normal = (*poly)->polyPlane.normal;

				int actNumVert = (*poly)->polyNumVert-1;
				do {
					zCVertex		*actVert = (*poly)->vertex [actNumVert]; 
					zCVertFeature	*actFeat = (*poly)->feature[actNumVert]; 
					if (lightNr==0) actFeat->lightDyn = actFeat->lightStat;
					// PROBLEM: Ein Poly kann x-mal in diese Methode gelangen =>
					//          alte Ergebniss werden durch folgendes dann wieder ueberschrieben...
	//				int r = int(actFeat->lightStat.GetRedByte	());
	//				int g = int(actFeat->lightStat.GetGreenByte	()); 
	//				int b = int(actFeat->lightStat.GetBlueByte	());

					zVEC3	view;
					zREAL	dot;
					zREAL	i;

					i		= 0;
					view	= actVert->position - lightSourcePos;

					///////////////////////////
					// 1. Distance-Falloff A //
					///////////////////////////

					zREAL dist; 
					zREAL len = view.LengthApprox();
					if (len>light->GetRange()) goto dontLightVert;
	//				if (len>light->GetRange()) { r = g = b = 255; goto dontLightVert; };
					dist = 1-(len * playerLIInv);
	//				dist = 1;

					////////////////////////
					// 2. Diffuse         //
					////////////////////////
					// angle: face/light

					// dot<0 => poly ist lq abgewandt
					// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
					if (len!=0)
					view = view / len;
	//				view.Normalize();
	//				dot = -(view * normal);
					if (smooth) dot = -(view * actFeat->vertNormal);
					else		dot = -(view * normal);

					if (dot<0) goto dontLightVert;
					i += (kd*dot);

					////////////////////////
					// 4. PreAmbient	  //
					////////////////////////
//					i += kprea;

					///////////////////////////
					// 5. Distance-Falloff B //
					///////////////////////////
					i *= (dist);

					////////////////////////
					// 6. Ambient		  //
					////////////////////////
					i += ka;

					// if (i==0.0F) continue;
					// zClamp (i, zREAL(0.0), zREAL(1.0));

					// Farbe des Lichtes durch die Intensitaet skalieren
					{
						// Die Effektive Farbe des Lichtes dem Vert-Feature hinzuaddieren (lightDyn)
						int	intens = zFloat2Int(i*255.0F);
						int r = (int)actFeat->lightDyn.r + ((lightR * intens) >> 8); if (r>255) r=255;
						int g = (int)actFeat->lightDyn.g + ((lightG * intens) >> 8); if (g>255) g=255;
						int b = (int)actFeat->lightDyn.b + ((lightB * intens) >> 8); if (b>255) b=255;

						actFeat->lightDyn.r = r;
						actFeat->lightDyn.g = g;
						actFeat->lightDyn.b = b;
					};
	dontLightVert:;
  				} while (actNumVert--);
	//			};
			};
		};
	};
}; 

#if 0
void zCPolygon::LightClippedPoly (const zCArray<zCVobLight*>& vobLightList) {
//actPoly->clipFeat[vertCtr]->lightDyn = actPoly->clipFeat[vertCtr]->lightStat;
	if (IsPortal()) return; 

	for (int lightNr=0; lightNr<vobLightList.GetNumInList(); lightNr++) 
	{

		const zCVobLight	*light			= vobLightList[lightNr];
		const zREAL		playerLIInv		= light->GetRangeInv();
		const int			lightR			= (int)light->GetColorR();
		const int			lightG			= (int)light->GetColorG();
		const int			lightB			= (int)light->GetColorB();
		const zPOINT3&		lightSourcePos	= light->GetPositionWorld();
		const zCMaterial	*mat			= GetMaterial();

		zREAL	ka,kd;
//		kprea	= mat->kpreAmbient;
		ka		= mat->kambient;
		kd		= mat->kdiffuse;
//		ks		= mat->kspecular;
//		ksm		= mat->kspecularPower; 

		int actNumVert = numClipVert-1;
		do {
			zCVertex		*actVert = clipVert[actNumVert]; 
			zCVertFeature	*actFeat = clipFeat[actNumVert]; 

			// PROBLEM: Ein Poly kann x-mal in diese Methode gelangen =>
			//          alte Ergebniss werden durch folgendes dann wieder ueberschrieben...
//				int r = int(actFeat->lightStat.GetRedByte	());
//				int g = int(actFeat->lightStat.GetGreenByte	()); 
//				int b = int(actFeat->lightStat.GetBlueByte	());

			zVEC3	view;
			zREAL	dot;
			zREAL	i;

			i		= 0;
			view	= actVert->position - lightSourcePos;

			///////////////////////////
			// 1. Distance-Falloff A //
			///////////////////////////

			zREAL dist; 
			zREAL len = view.LengthApprox();
			if (len>light->GetRange()) goto dontLightVert;
//				if (len>light->GetRange()) { r = g = b = 255; goto dontLightVert; };
			dist = 1-(len * playerLIInv);

			////////////////////////
			// 2. Diffuse         //
			////////////////////////
			// angle: face/light

			// dot<0 => poly ist lq abgewandt
			// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
//			if (len!=0)
//			view = view / len;
//			if (smooth) dot = -(view * actFeat->vertNormal);
//			else		dot = -(view * normal);
			dot = -((view * actFeat->vertNormal) / len);

			if (dot<0) goto dontLightVert;
			i = dot*dist;
/*			i += (kd*dot);

			////////////////////////
			// 4. PreAmbient	  //
			////////////////////////
			i += kprea;

			///////////////////////////
			// 5. Distance-Falloff B //
			///////////////////////////
			i *= (dist);

			////////////////////////
			// 6. Ambient		  //
			////////////////////////
			i += ka;
*/
			// if (i==0.0F) continue;
			// zClamp (i, zREAL(0.0), zREAL(1.0));

			// Farbe des Lichtes durch die Intensitaet skalieren
			{
				// Die Effektive Farbe des Lichtes dem Vert-Feature hinzuaddieren (lightDyn)
				int	intens = zFloat2Int(i*255.0F);
				int r = (int)actFeat->lightDyn.r + ((lightR * intens) >> 8); if (r>255) r=255;
				int g = (int)actFeat->lightDyn.g + ((lightG * intens) >> 8); if (g>255) g=255;
				int b = (int)actFeat->lightDyn.b + ((lightB * intens) >> 8); if (b>255) b=255;

				actFeat->lightDyn.r = r;
				actFeat->lightDyn.g = g;
				actFeat->lightDyn.b = b;

			};
dontLightVert:;
  		} while (actNumVert--);
	};
}; 
#endif

/* ----------------------------------------------------------------------

    zCPolygon::LightDynCamSpace()

	16.11.2000	[Moos]	
                auf neue Vertices umgestellt

   ---------------------------------------------------------------------- */

void zCPolygon::LightDynCamSpace (const zPOINT3& lightSourcePos, int playerLightInt) {
	// - Phong-Reflection-Model
	// - Allerdings: die Farbe ist fuer Amb, Diff, Spec gleich
	// - Beleuchtung im Cam-Space !
	// - lightDyn wird modifiziert
	// - clipVerts/clipFeats

	// Zur Zeit:
	// - Parallel-Licht Beleuchtung 
	// - Distanz-Messung = z-Distanz

	// FIXME: lightSourcePos als const& !!
	// FIXME: noch stark optimierbar, auch einige Sonderfälle möglich!

//lightSourcePos = (0,0,0);

	if (playerLightInt<50) return;

	// spec.
//	zPOINT3 viewerPos	= zCCamera::activeCamPos;
//	zPOINT3 half		= (lightSourcePos + viewerPos).Normalize();
	zREAL	playerLIInv = zREAL(1) / zREAL(playerLightInt);				// FIXME !!
	zPOINT3	normal;

	if (!material) return;
	zREAL	ka,kd;
//	kprea	= material->kpreAmbient;
	ka		= material->kambient;
	kd		= material->kdiffuse; 
//	ks		= material->kspecular;
//	ksm		= material->kspecularPower;

	zBOOL smooth = FALSE;
	if (material)	smooth = material->GetSmooth(); 
	if (!smooth)	normal = polyPlane.normal;

//	zVEC3 viewNorm = (clipVert[0]->position - lightSourcePos);
//	viewNorm.Normalize();

	for (int i=0; i<numClipVert; i++) { 
		zCVertex		*actVert = clipVert[i];
		zCVertFeature	*actFeat = clipFeat[i]; 

		zVEC3	view = actVert->position - lightSourcePos;
//		zVEC3	view = viewNorm;

		zREAL	dot;
		zREAL	i	 = 0;

		///////////////////////////
		// 1. Distance-Falloff A //
		///////////////////////////
		zREAL dist;
//		zREAL len = view.LengthApprox();
//		zREAL len = actVert->vertCamSpace.LengthApprox();
		zREAL len = actVert->VertexTransform()->vertCamSpace[VZ];

		if (len>playerLightInt) goto outOfRange;
		dist = 1-(len * playerLIInv);

		if (smooth) normal = actFeat->vertNormal;

		////////////////////////
		// 2. Diffuse         //
		////////////////////////
		// angle: face/light

		// dot<0 => poly ist lq abgewandt
		// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
		view = view / len;
		dot = -(view * normal);

//		dot = -(viewNorm * normal);
//		if (smooth) dot = -(view * actFeat->vertNormal);
//		else		dot = -(view * polyPlane.normal);
		
		i += (kd*dot);

		////////////////////////
		// 3. Specular        //
		////////////////////////
/*
		zREAL s;
//		zPOINT3		normal;

//		if (smooth) normal = actFeat->vertNormal;
//		else		normal = polyPlane.normal;

		zPOINT3 l= lightSourcePos - actVert->position;
		zPOINT3 r= 2 * normal * (normal * l) - l;
		r.Normalize();

		zPOINT3 v = viewerPos - actVert->position;
		v.Normalize();
//		s = normal * half;
		s = (r * v);
		if (s<0) s = 0;
		i += ks * pow( s, ksm);
*/
		////////////////////////
		// 4. PreAmbient	  //
		////////////////////////
//		i += kprea;

		///////////////////////////
		// 5. Distance-Falloff B //
		///////////////////////////
		i *= (dist);


		////////////////////////
		// 6. Ambient		  //
		////////////////////////
		i += ka;

		if (i<0) i=0;				// scheint noetig, i<0 kommt vor !!

		// Farbe des Lichtes durch die Intensitaet skalieren
		{
//			int	intens		= int(i*255);
//			int	intens		= zFloat2Int(i*255.0F);
//			int	lightInt	= (255 * intens) >> 8;
			// assert: white-light
			int	lightIntens	= zFloat2Int(i * 255.0F);

			int r = int(actFeat->lightDyn.r) + lightIntens; if (r>255) r=255;
			int g = int(actFeat->lightDyn.g) + lightIntens; if (g>255) g=255;
			int b = int(actFeat->lightDyn.b) + lightIntens; if (b>255) b=255;

			// Die Effektive Farbe des Lichtes dem Vert-Feature hinzuaddieren (lightDyn)
			actFeat->lightDyn.r = r;
			actFeat->lightDyn.g = g;
			actFeat->lightDyn.b = b;
//			actFeat->lightDyn.alpha = 255;
		};
outOfRange:;
	};
};


/* ----------------------------------------------------------------------
	
    zCPoygon::GetLightStatAtPos()	

	29.11.2000	[Moos]	
                auf neue Lightmap-Klasse umgestellt

   ---------------------------------------------------------------------- */

zVEC3 zCPolygon::GetLightStatAtPos (const zPOINT3& pos)
{
	zVEC3 color(255,0,0);
	if (lightmap)
//if (0)
	{
//zrenderer->SetBilerpFilterEnabled	(FALSE);
		// mapping: 3D Pos => UV
		zREAL	u, v;
		int		xdim, ydim;
		lightmap->GetLightmapTexCoords			(pos, u, v);

        zERR_ASSERT(lightmap->Texture());
		lightmap->Texture()->GetPixelSize		(xdim, ydim); // [Moos] 29.11.00 neu
		zVEC4 col	= lightmap->Texture()->GetRGBAAtTexel	(zREAL(xdim)*u, zREAL(ydim)*v);

		color		= zVEC3(col[0], col[1], col[2]);
	} else
	{
		zVEC3 col0	= feature[0]->lightStat.GetVEC3();
		zVEC3 q		= pos - vertex[0]->position;

		const zREAL MIN_THRESH = zREAL(-0.05F);
		const zREAL MAX_THRESH = zREAL(+1.05F);
		zBOOL found = FALSE;

		// Poly triangulieren
		int i,j;					// 0..i..j
		for (j=2; j<polyNumVert; j++)
		{ 
			// FIXME: bei nPolys koennten Werte des letzten Tris (eine Edge) wiederbenutzt werden..
			i = j-1;
			zVEC3 a			= vertex[j]->position - vertex[0]->position;
			zVEC3 b			= vertex[i]->position - vertex[0]->position;

			zREAL ab,bb,qb;
			ab				= (a*b);
			bb				= (b*b);
			qb				= (q*b);

			zREAL div		= ((a*a)*(bb) - ((ab)*(ab)));
			if (div!=0)
			{
				zREAL x			= ((bb) * (q*a) - (ab) * (qb)) / div;
				// triangle getroffen ?
				if ((MIN_THRESH<=x) && (x<=MAX_THRESH))
				{
					zREAL y		= ((qb) - x*(ab)) / (bb);
					if ( (MIN_THRESH<=y) && (y<=MAX_THRESH) && ((x+y)<=MAX_THRESH)) 
					{
						if ((polyNumVert>3) && (Alg_IsColinear (a,b))) continue;

						if (zIsNegative(x)) x = 0;
						if (zIsNegative(y)) y = 0;

						zVEC3 coli		= feature[i]->lightStat.GetVEC3();
						zVEC3 colj		= feature[j]->lightStat.GetVEC3();
						zVEC3 deltaa	= colj - col0;
						zVEC3 deltab	= coli - col0;
						color			= col0 + x*deltaa + y*deltab;
						found			= TRUE;
						break;
					};
				};
			};
		};
#ifndef ZENGINE_DEBUG
		if (!found) {
			color = zREAL(0.33333F) * (feature[0]->lightStat.GetVEC3() + feature[1]->lightStat.GetVEC3() + feature[2]->lightStat.GetVEC3());
		};
#endif
	};
	return color;
};


/*
> > I know a point lie in the plane of a triangle,
> > I would like to know if it is in the triangle...
> > Can you help me please ?
> >
> > Vertex : v
> > Triangle : v1,v2,v3

n = (v3 - v1) x (v2 - v1) (ie normal to plane)

(((v - v1) x (v2 - v1)) . n) >= 0
(((v - v2) x (v3 - v2)) . n) >= 0
(((v - v3) x (v1 - v3)) . n) >= 0

I may have the signs reversed, but I don't think so.
*/

/*
> The best coordinate axis to drop is the one closest to the
> plane normal this is the coordinate axis for which the normal has the
> largest absolute value.

  => SOLID ??

inline int Vector::closestAxis() const {
  Scalar a[2];
  a[X] = abs(coor[X]);
  a[Y] = abs(coor[Y]);
  int axis = a[X] < a[Y] ? Y : X;
  return a[axis] < abs(coor[Z]) ? Z : axis;
}

bool Polygon::contains(const Point& p) const {
	// aus: SOLID	
	int z = plneq.normal().closestAxis();
	int x = (z + 1) % 3;
	int y = (z + 2) % 3;
	
	bool inside = false;
	for (int i = 0, j = nverts-1; i < nverts; j = i++) { 
		Point& u = verts[i];
		Point& v = verts[(i + 1) % nverts];

		if ((u[y] >= p[y]) != (v[y] >= p[y])) {

			bool right = u[x] >= p[x];
			if (right != (v[x] >= p[x])) {
				Scalar t = (u[y] - p[y]) / (u[y] - v[y]);
				if (u[x] + (v[x] - u[x]) * t >= p[x]) inside = !inside;
			}
			else if (right) inside = !inside;
		}
	}
	return inside;
}

	int i, j, right, inside = 0;
	for (i = 0, j = n-1; i < n; j = i++) {

		if ((y[i] <= Y) != (y[j]<= Y)) {

			if ((right = x[i] >= X) != (x[j] >= X)) {
				if ((X - x[i]) * (y[j] - y[i]) < (x[j] - x[i]) * (Y - y[i]))
					inside = !inside;
			}
			else if (right) inside = !inside; 
		}
	}

int pnpoly(int npol, float *xp, float *yp, float x, float y)
{
	int i, j, c = 0;
	for (i = 0, j = npol-1; i < npol; j = i++) {
        if ((((yp[i]<=y) && (y<yp[j])) ||
			((yp[j]<=y) && (y<yp[i]))) &&
            (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
			
			c = !c;
	}
	return c;
}
*/
/*
SRC: Eberly
int PointInPolygon (int N, double* x, double* y, double xt, double yt)
{
    int c = 0;
    for (int i = 0, j = N-1; i < N; j = i++)
    {
        if ((y[i]<=yt && yt<y[j] && (y[j]-y[i])*(xt-x[i])<(x[j]-x[i])*(yt-y[i]))
        ||  (y[j]<=yt && yt<y[i] && (y[j]-y[i])*(xt-x[i])>(x[j]-x[i])*(yt-y[i])))
        {
            c ^= 1;
        }
    }
    return c;
}

int PointInPolygon (int N, double* x, double* y, double xt, double yt)
{
    int c = 0;
    for (int i = 0, j = polyNumVert-1; i < polyNumVert; j = i++)
    {
		const zPOINT3& u = vertex[i]->position;
		const zPOINT3& v = vertex[j]->position;
        if ((u[vy]<=inters[vy] && inters[vy]<v[vy] && (v[vy]-u[vy])*(inters[vx]-u[vx])<(v[vx]-u[vx])*(inters[vy]-u[vy]))
        ||  (v[vy]<=inters[vy] && inters[vy]<u[vy] && (v[vy]-u[vy])*(inters[vx]-u[vx])>(v[vx]-u[vx])*(inters[vy]-u[vy])))
        {
            c ^= 1;
        }
    }
    return c;
}
*/

/*
3. Really simple. Say you are working on the XY plane(the others are the same but you use the
      appropriate components). To get the parallel projection you dont do any calculation at all.
      Quite to the contrary. You discard the other component, z in this case. Then you use the rise
      and run of the triangle edges to find the normals to each line(there are normals in any
      dimensional space, they just have less components). Find the free term in the equation the
      same as with the planes. Use the dotproduct formula to find the same distance as in 3D. Do
      this to all the edges. Then check the signs. If they all have the same sign, the point is
      inside, if not, well... Note that its important not to just check if they're all positive(or
      whatever your convention is), since the orientation of the triangle's projection is not
      guaranteed. But the sign should stay the same.
*/


#if 0

int
intersect_triangle_barycentric(
   double orig[3], double dir[3],
   double vert0[3], double vert1[3], double vert2[3],
   double planeq[4], int i1, int i2,
   double *t, double *alpha, double *beta)

zBOOL zCCFASTCALL	zCPolygon::CheckRayPolyIntersection (const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& inters, zREAL& alpha) const {
{
	const zREAL EPSILON = 0.000001F;
	zREAL		dot, dot2;
	zREAL		u0, v0, u1, v1, u2, v2;
	
	// is ray parallel to plane? 
	dot = ray[0] * planeq[0] + ray[1] * planeq[1] + ray[2] * planeq[2];
	if (dot < EPSILON && dot > -EPSILON)         // or use culling check 
		return 0;
	
	// find distance to plane and intersection point 
	dot2	= rayOrigin[0] * planeq[0] + rayOrigin[1] * planeq[1] + rayOrigin[2] * planeq[2];
	*t		= -(planeq[3] + dot2 ) / dot;
	point[0]= rayOrigin[i1] + ray[i1] * *t;
	point[1]= rayOrigin[i2] + ray[i2] * *t;
	
	// begin barycentric intersection algorithm 
	u0 = point[0] - vert0[i1];
	v0 = point[1] - vert0[i2];
	u1 = vert1[i1] - vert0[i1];
	u2 = vert2[i1] - vert0[i1];
	v1 = vert1[i2] - vert0[i2];
	v2 = vert2[i2] - vert0[i2];
	
	// calculate and compare barycentric coordinates 
	if (u1 == 0) {               // uncommon case 
		*beta = u0 / u2;
		if (*beta < 0 || *beta > 1)
			return 0;
		*alpha = (v0 - *beta * v2) / v1;
	}
	else {                       // common case, used for this analysis 
		*beta = (v0 * u1 - u0 * v1) / (v2 * u1 - u2 * v1);
		if (*beta < 0 || *beta > 1)
			return 0;
		*alpha = (u0 - *beta * u2) / u1;
	}
	
	if (*alpha < 0 || (*alpha + *beta) > 1.0)
		return 0;
	
	return 1;
}
#endif


/*	------------------------------------------------------------------
	zCPolygon::CheckRayPolyIntersection()
	30.07.00	[Rueve]
				Optimierungen: Entfernung überflüssiger Variable, Special-Case für Triangle (90% der Aufrufe)
	21.08.00	[Hildebrandt]	
				Ausgehebelte 'dnInv' Div-Pipelining Optimierung wieder aktiviert; & kleinere Optimierungen.
	22.11.00	[Hildebrandt]	
				div0 sicher gemacht (3Vert Test)
	------------------------------------------------------------------ */

zBOOL zCCFASTCALL	zCPolygon::CheckRayPolyIntersection (const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& inters, zREAL& alpha) const 
{
	// Quelle : news.raypoly.txt, web-page
	// output : intersection, alpha
	// Achtung: alles im WorldSpace !! (bzw. im Object-Space des Polygons)
	// - Backface-Culling: Schnittpunkte werden nur gemeldet, wenn der Ray das Poly von VORNE durchdringt
	// - nur Schnittpunkte im alpha-Bereich 0..1 sind valid.

	// 1) Schnitt Ray/Plane finden, Backface-Culling	
	zREAL dn;
 	dn		= ray * polyPlane.normal;
	if (!zIsNegative (dn)) return FALSE;										// parallel, backface ?
	// ACHTUNG: dn ist negativ (<0 , s.o.!)
	alpha	= (polyPlane.distance - (polyPlane.normal * rayOrigin));
	if ((zIsGreaterZero(alpha)) || (alpha<dn)) return FALSE;					// vor/hinter Betrachter ?

	// Ausnutzung von Pipelining: Division wird berechnet, waehrend mit Integer-Arith. die optimale Plane gesucht wird..
	const zREAL	dnInv	= zREAL(1.0F) / dn;

	// 2) Closest Axis finden (solid) (Achse, mit groesstem Abs-Wert)
	// FIXME: die Axis bereits in jedem Poly cachen ?? => 2 bit
	int		vx, vy, vz;
	zVEC2	a(zAbsApprox(polyPlane.normal[VX]), zAbsApprox(polyPlane.normal[VY]));
	vz		= (zIsSmallerPositive (a.n[VX], a.n[VY]))							? VY : VX;
	vz		= (zIsSmallerPositive (a.n[vz], zAbsApprox(polyPlane.normal[VZ])))	? VZ : vz;
	vx		= vz+1; if (vx>2) vx=0;
	vy		= vx+1; if (vy>2) vy=0;

	// .. nun ist die Division in dnInv ausgefuehrt und der Wert kann verwendet werden
	alpha   *= dnInv;
	inters	= rayOrigin + alpha*ray;
	// nun enthält inters den Schnittpunkt mit der Ebene des Polys	
	// 3) point-in-poly Test
	zBOOL inside;
	if (polyNumVert == 3)
	{
		// [rueve]: 300700  Optimierung vorgenommen
		// Triangle - special case, schneller!
		// gemäß   http://www.cs.brown.edu/people/scd/facts.html
		const zREAL a_c0		= ((vertex[0]->position)[vx] - (vertex[2]->position)[vx]);
		const zREAL a_c1		= ((vertex[0]->position)[vy] - (vertex[2]->position)[vy]);
		const zREAL b_c0		= ((vertex[1]->position)[vx] - (vertex[2]->position)[vx]);
		const zREAL b_c1		= ((vertex[1]->position)[vy] - (vertex[2]->position)[vy]);
		const zREAL p_c0		= (inters[vx] - (vertex[2]->position)[vx]);
		const zREAL p_c1		= (inters[vy] - (vertex[2]->position)[vy]);

		const zREAL denom		= (a_c0*b_c1 - a_c1*b_c0);			if (denom==0)	return FALSE;
		const zREAL denomInv	= zREAL(1.0F) / denom;
		const zREAL u			= (p_c0*b_c1 - p_c1*b_c0) * denomInv;
		const zREAL v			= (a_c0*p_c1 - a_c1*p_c0) * denomInv;
		
		inside = ((u + v < 1) && (u < 1) && (v < 1) && (!zIsNegative(u)) && (!zIsNegative(v)));
	}
	else
	{		
		inside = FALSE;
		for (int i = 0, j = polyNumVert-1; i < polyNumVert; j = i++)
		{
			const zPOINT3& u = vertex[i]->position;
			const zPOINT3& v = vertex[j]->position;
			if ((u.n[vy]<=inters.n[vy] && inters.n[vy]<v.n[vy] && (v.n[vy]-u.n[vy])*(inters.n[vx]-u.n[vx])<(v.n[vx]-u.n[vx])*(inters.n[vy]-u.n[vy]))
			||  (v.n[vy]<=inters.n[vy] && inters.n[vy]<u.n[vy] && (v.n[vy]-u.n[vy])*(inters.n[vx]-u.n[vx])>(v.n[vx]-u.n[vx])*(inters.n[vy]-u.n[vy])))
			{
	            inside = !inside;
			}
		}
	}
	return inside;
};

/*	------------------------------------------------------------------
	zCPolygon::CheckRayPolyIntersection2Sided()
	30.07.00	[Rueve]
				Optimierungen: Special-Case für Triangle
	21.08.00	[Hildebrandt]	
				kleinere Optimierungen.
	------------------------------------------------------------------ */

zBOOL zCCFASTCALL	zCPolygon::CheckRayPolyIntersection2Sided (const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& inters, zREAL& alpha) const {
	// Quelle : news.raypoly.txt, web-page
	// output : intersection, alpha
	// Achtung: alles im WorldSpace !! (bzw. im Object-Space des Polygons)
	// - KEIN Backface-Culling (=> z.B. fuer BBox-Check, diags)
	// - nur Schnittpunkte im alpha-Bereich 0..1 sind valid.

	// 1) Schnitt Ray/Plane finden, Backface-Culling
	zREAL dn;
 	dn		= ray * polyPlane.normal;
	if (dn==0) return FALSE;													// parallel?
	alpha	= (polyPlane.distance - (polyPlane.normal * rayOrigin)) / dn;
	if (!zIsInRange01(alpha)) return FALSE;
	inters	= rayOrigin + alpha*ray;

	// 2) Closest Axis finden (src: solid) (Achse, mit groesstem Abs-Wert)
	int		vx, vy, vz;
	zVEC2	a;
	a[VX]	= zAbsApprox(polyPlane.normal[VX]);
	a[VY]	= zAbsApprox(polyPlane.normal[VY]);
	vz		= (zIsSmallerPositive (a.n[VX], a.n[VY]))							? VY : VX;
	vz		= (zIsSmallerPositive (a.n[vz], zAbsApprox(polyPlane.normal[VZ])))	? VZ : vz;
	vx		= vz+1; if (vx>2) vx=0;
	vy		= vx+1; if (vy>2) vy=0;

	// 3) point-in-poly Test
	zBOOL inside;
	if (polyNumVert == 3)
	{
		// [rueve]: 300700  Optimierung vorgenommen
		// Triangle - special case, schneller!
		// gemäß   http://www.cs.brown.edu/people/scd/facts.html
		const zREAL a_c0		= (vertex[0]->position)[vx] - (vertex[2]->position)[vx];
		const zREAL a_c1		= (vertex[0]->position)[vy] - (vertex[2]->position)[vy];
		const zREAL b_c0		= (vertex[1]->position)[vx] - (vertex[2]->position)[vx];
		const zREAL b_c1		= (vertex[1]->position)[vy] - (vertex[2]->position)[vy];
		const zREAL p_c0		= (inters[vx] - (vertex[2]->position)[vx]);
		const zREAL p_c1		= (inters[vy] - (vertex[2]->position)[vy]);

#ifdef _DEBUG
		if ( (a_c0*b_c1 - a_c1*b_c0) == 0) return FALSE;
#endif

		const zREAL denomInv	= zREAL(1.0F) / ( a_c0*b_c1 - a_c1*b_c0);
		const zREAL u			= ( p_c0*b_c1 - p_c1*b_c0) * denomInv;
		const zREAL v			= ( a_c0*p_c1 - a_c1*p_c0) * denomInv;
		
		inside = ((u + v < 1) && (u < 1) && (v < 1) && (!zIsNegative(u)) && (!zIsNegative(v)));
	}
	else
	{
		inside = FALSE;

		for (int i = 0, j = polyNumVert-1; i < polyNumVert; j = i++) {
			const zPOINT3& u = vertex[i]->position;
			const zPOINT3& v = vertex[j]->position;
	
			if ((u[vy] >= inters[vy]) != (v[vy] >= inters[vy])) {
				zBOOL right = u[vx] >= inters[vx];
				if (right != (v[vx] >= inters[vx])) {
					zREAL t = (u[vy] - inters[vy]) / (u[vy] - v[vy]);
					if (u[vx] + (v[vx] - u[vx]) * t >= inters[vx]) inside = !inside;
				}
				else if (right) inside = !inside;
			}
		}
	}

	return inside;
};



/*
void zCPolygon::CalcNormalMainAxis () {
	int		vz;
	zVEC2	a;
	a[VX]	= zAbs(polyPlane.normal[VX]);
	a[VY]	= zAbs(polyPlane.normal[VY]);
	vz		= a[VX]	< a[VY]						 ? VY : VX;
	vz		= a[vz]	< zAbs(polyPlane.normal[VZ]) ? VZ : vz;

	flags.normalMainAxis = vz;
};
*/
//-------------------------------------------

zTBBox3D zCPolygon::GetBBox3D () const {
	zTBBox3D polyBBox;
	polyBBox.Init();
	for (int vertCtr=0; vertCtr<polyNumVert; vertCtr++) {
		zCVertex *vert = vertex[vertCtr];
		for (int j=0; j<3; j++) {
			polyBBox.mins[j] = zMin (polyBBox.mins[j], vert->position.n[j]);
			polyBBox.maxs[j] = zMax (polyBBox.maxs[j], vert->position.n[j]);
		}; 
	};
	return polyBBox;
};

zPOINT3 zCPolygon::GetCenter() {
	zPOINT3 p(0,0,0);
	for (int i=0; i<polyNumVert; i++)  p += vertex[i]->position;
	return (p * (zREAL(1) / polyNumVert));
};

void zCPolygon::SetMapping (const zPOINT2& a, const zPOINT2& b, const zPOINT2& c) {
	assert (polyNumVert>=3);
	feature[0]->SetMapping (a);
	feature[1]->SetMapping (b);
	feature[2]->SetMapping (c);
};

void zCPolygon::SetMapping (const int vertNr, const zPOINT2& texuv) {
	feature [vertNr]->SetMapping (texuv); 
};

void zCPolygon::Flip () {									// FIXME: buggy !!!
	for (int i=0; i<(polyNumVert/2)-1; i++) zSwap (vertex[i], vertex[polyNumVert-i]);
	CalcNormal();
};

zBOOL zCPolygon::VertPartOfPoly				(zCVertex *vert) const {
	for (int i=0; i< polyNumVert; i++) if (vertex[i]==vert) return TRUE;
	return FALSE;
};

zBOOL zCPolygon::EdgePartOfPoly				(zCVertex *vert1, zCVertex *vert2) const {
	int inext	= 0;
	int i		= polyNumVert-1;
	do {
		if ((vertex[i]==vert1) && (vertex[inext]==vert2)) return TRUE;
		i = inext;
		inext++;
	} while (inext<polyNumVert);
	return FALSE;
};


zBOOL zCPolygon::EdgePositionsPartOfPoly(zCVertex *vert1, zCVertex *vert2) const 
{
	return (VertPartOfPoly(vert1) && VertPartOfPoly(vert2));

};



///////////////////////////////////////////////////////////////////////////

void zCPolygon::TexTranslate (const zPOINT2 &deltaDir) {
	for (int i=0; i<polyNumVert; i++) {
		feature[i]->texu += deltaDir.n[VX];
		feature[i]->texv += deltaDir.n[VY];
	};
};

void zCPolygon::TexSetTranslation (const zPOINT2 &pos) {
	for (int i=0; i<polyNumVert; i++) {
		feature[i]->texu = pos.n[VX];
		feature[i]->texv = pos.n[VY];
	};
};

void zCPolygon::TexScale (const zREAL sx, const zREAL sy) {
	for (int i=0; i<polyNumVert; i++) {
		feature[i]->texu *= sx;
		feature[i]->texv *= sy;
	};
};

void zCPolygon::TexScale (zPOINT2 &center, const zREAL sx, const zREAL sy) {
	TexTranslate	(-center);
	TexScale		(sx, sy);
	TexTranslate	(center);
};

void zCPolygon::TexRotate (zPOINT2 &center, const zREAL angle) 
{
	assert (GetMaterial());

	// Texturen mit aspectRatio != 1 brauchen eine spezielle Skalierung/Translation vor
	// und nach der Rotation
	zREAL aspect	= 1.0F;
	zBOOL doScale	= FALSE;
	if (GetMaterial()->GetTexture())
	{
		int xdim, ydim;
		GetMaterial()->GetTexture()->GetPixelSize (xdim, ydim);
		aspect	= float(xdim) / float(ydim);
		doScale	= TRUE;
	};

	zMAT3	rot			= Alg_Rotation2D	(center, angle);
	if (doScale) {
		zMAT3	scale	= Alg_Scaling2D		(zVEC2(1.0F, aspect));
		zMAT3	trans	= Alg_Translation2D	(center);
		scale			= trans * scale * trans.Inverse();
		rot				= scale * rot   * scale.Inverse();
	};

	for (int i=0; i<polyNumVert; i++) {
		zPOINT2 uv		= zVEC2(feature[i]->texu, feature[i]->texv);
		uv				= (rot * uv);
		feature[i]->texu= uv[0];
		feature[i]->texv= uv[1];
	};
};

void zCPolygon::TexMirrorU (const zREAL center) {
	for (int i=0; i<polyNumVert; i++) {
		feature[i]->texu = center - feature[i]->texu;
	};
};

void zCPolygon::TexMirrorV (const zREAL center) {
	for (int i=0; i<polyNumVert; i++) {
		feature[i]->texv = center - feature[i]->texv;
	};
};

void zCPolygon::TexShearU (const zREAL deltak) {
	zMAT3 shear = Alg_Identity2D();
	shear[0][1] = deltak;
	for (int i=0; i<polyNumVert; i++) {
		zPOINT2 uv = (shear * zVEC2(feature[i]->texu, feature[i]->texv));
		feature[i]->texu = uv[0];
		feature[i]->texv = uv[1];
	};
};

void zCPolygon::TexShearV (const zREAL deltak) {
	zMAT3 shear = Alg_Identity2D();
	shear[1][0] = deltak;
	for (int i=0; i<polyNumVert; i++) {
		zPOINT2 uv = (shear * zVEC2(feature[i]->texu, feature[i]->texv));
		feature[i]->texu = uv[0];
		feature[i]->texv = uv[1];
	};
};

/* FIXME: bessere Routine in...(ohne die Bugs)
"The best way to figure out texture mapping in Quake is to download
their comprehensive source. What you're looking for is in the QE4
directory, the file is "SetBrush.m", the routine is BasePolyForPlane.
There is a section there that calculates S, T."

"Yup, I was looking in the Quake 1 directory, sorry. Here's what you
need. You'll need to track the other routines referenced.
I struggled with this routine for some time on my Quake editor, then
magically found the previously mentioned routine. It works, and allows
you to render exactly the same way that Quake does.
Quake uses the DotProduct calc to get the "neutral" coordinates. These
are where your texture will be if there is no rotation, scaling, or
offset. These factors are then accounted for, and the result here is s
and t."
void EmitTextureCoordinates ( float *xyzst, qtexture_t *q, face_t *f)
{
        float   s, t, ns, nt;
        float   ang, sinv, cosv;
        vec3_t  vecs[2];
        texdef_t        *td;

        // get natural texture axis
        TextureAxisFromPlane(&f->plane, vecs[0], vecs[1]);

        td = &f->texdef;

        ang = td->rotate / 180 * Q_PI;
        sinv = zSin(ang);
        cosv = zCos(ang);
        
        if (!td->scale[0])
                td->scale[0] = 1;
        if (!td->scale[1])
                td->scale[1] = 1;

        s = DotProduct(xyzst, vecs[0]);
        t = DotProduct(xyzst, vecs[1]);

        ns = cosv * s - sinv * t;
        nt = sinv * s +  cosv * t;

        s = ns/td->scale[0] + td->shift[0];
        t = nt/td->scale[1] + td->shift[1];

        // gl scales everything from 0 to 1
        s /= q->width;
        t /= q->height;

        xyzst[3] = s;
        xyzst[4] = t;
}*/

void zCPolygon::TexApplyPlanarMapping (const zPOINT3& origin, const zPOINT3& up, const zPOINT3& right, zBOOL scaleByTexture) {
	float	ab,bb,qb;
	zPOINT3 q;
	zPOINT3 a = up;
	zPOINT3 b = right;

	//
	if (scaleByTexture)
	if (material)
//	if (material->texture)
	{
		zPOINT2 texScale = material->GetTexScale();	// implizites zCTexture::zCResource::CacheIn(-1)
//		a *= texScale.n[VY];		// up
//		b *= texScale.n[VX];		// right
		a *= texScale.n[VX];		// up			beide werden mit texScale[x] skaliert !!
		b *= texScale.n[VY];		// right
	};

	ab		= (a*b);
	bb		= (b*b);
	for (int i=0; i<polyNumVert; i++) {
		zREAL	u,v;

		q	= vertex[i]->position - origin;
		qb	= (q*b);
	
		u	= ((bb) * (q*a) - (ab) * (qb)) / ((a*a)*(bb) - ((ab)*(ab)));
		v	= ((qb) - u*(ab)) / (bb);
//		if ((0.0F<=x) && (x<=1.0F))
//		if ( (0.0F<=y) && (y<=1.0F) && ((x+y)<=1))
		feature[i]->texu = u;
		feature[i]->texv = v;
	};
//	TexCorrectUV();
};


void zCPolygon::TexApplyPlanarMapping (const zREAL scaleu, const zREAL scalev, zBOOL scaleByTexture) {
	zPOINT3 a,b, origin;
	polyPlane.GetOriginUpRight (origin, a, b);
	a		= a * scaleu;
	b		= b * scalev;
	TexApplyPlanarMapping (origin, a, b, scaleByTexture);
};

void zCPolygon::TexApplyPlanarMapping (const zCList<zCPolygon>& polyList,
									   const zREAL scaleu, const zREAL scalev, zBOOL scaleByTexture) {
	// die avg plane aller Polys ermitteln
	zTPlane avgPlane;
	avgPlane.normal		= zPOINT3(0.0F, 0.0F, 0.0F);
	avgPlane.distance	= 0.0F;
	for (int i=0; i<polyList.GetNumInList(); i++) {
		avgPlane.normal   += polyList[i]->polyPlane.normal;
		avgPlane.distance += polyList[i]->polyPlane.distance;
	};
	avgPlane.normal   /= zREAL(polyList.GetNumInList());
	avgPlane.distance /= zREAL(polyList.GetNumInList());
	avgPlane.normal.Normalize();
	
	// Apply Mapping
	zPOINT3 a,b, origin;
	avgPlane.GetOriginUpRight (origin, a, b);
	a		= a * scaleu;
	b		= b * scalev;

	// jetzt alle Polys der Liste neu mappen
	for (i=0; i<polyList.GetNumInList(); i++)
		polyList[i]->TexApplyPlanarMapping (origin, a, b, scaleByTexture);
};

void zCPolygon::AlignPolyListToAvgPlane (const zCArray<zCPolygon*> polyList)
{
	// Aus der uebergebenen Polylist wird eine durchschnittliche Plane ermittelt.
	// Alle Vertices werden so justiert, dass sie auf der Plane liegen.
	if (polyList.GetNum()<=1) return;
	int i;

	// calc. avg plane
	zTPlane plane;
	plane.normal=0;
	for (i=0; i<polyList.GetNum(); i++)
	{
		plane.normal	+= polyList[i]->GetNormal() * polyList[i]->GetArea();
	};
	plane.normal.Normalize();

	// Achsen werden 'gesnappt'
	const zREAL THRESH = zREAL(0.99F);
	for (i=0; i<3; i++)
	{
		if (zAbs(plane.normal[i])>THRESH)
		{
			plane.normal[i]		= plane.normal[i] < 0 ? -1.0F : 1.0F;
			plane.normal[(i+1)%3]= 0;
			plane.normal[(i+2)%3]= 0;
			break;
		};
	};

	plane.distance=0;
	int numVert	= 0;
	for (i=0; i<polyList.GetNum(); i++)
	{
		zCPolygon *poly = polyList[i];
		for (int j=0; j<poly->polyNumVert; j++)
		{
			plane.distance += poly->vertex[j]->position * plane.normal;
			numVert++;
		};
	};
	plane.distance /= zREAL(numVert);

	// vertices verschieben
	for (i=0; i<polyList.GetNum(); i++)
	{
		zCPolygon *poly = polyList[i];
		for (int j=0; j<poly->polyNumVert; j++)
		{
			zREAL d = poly->vertex[j]->position * plane.normal - plane.distance;
			poly->vertex[j]->position -= d * plane.normal;
		};
		poly->CalcNormal();
	};
};

void zCPolygon::TexCorrectUV () {
	int i;
	zREAL umax, vmax, vmin, umin;
	umax = zREAL(-99999);
	vmax = zREAL(-99999);
	umin = zREAL(+99999);
	vmin = zREAL(+99999);
	for (i=0;i<polyNumVert; i++) {
		umax = zMax (feature[i]->texu, umax);
		umin = zMin (feature[i]->texu, umin);
		vmax = zMax (feature[i]->texv, vmax);
		vmin = zMin (feature[i]->texv, vmin);
	};
	zREAL	deltau = (umin + umax) * -0.5F;
	zREAL	deltav = (vmin + vmax) * -0.5F;
	if (deltau<0)	deltau = zCeil	(deltau);
	else			deltau = zFloor	(deltau);
	if (deltav<0)	deltav = zCeil	(deltav);
	else			deltav = zFloor	(deltav);
	for (i=0;i<polyNumVert; i++) {
		feature[i]->texu += deltau;
		feature[i]->texv += deltav;
	};
};

// Alloc-Num : plus-delta

void zCPolygon::AllocVerts (const int addNum) 
{
	// addNum = DELTA !
	zCVertex		**newVertList	= NULL;
	zCVertFeature	**newFeatList	= NULL;

	zCVertFeature	 *newFeat		= NULL;

	
#ifdef MEMPOOL_HOELLER
	if((Mesh==NULL)||(GetMeshesPool().IsPoolActive()==FALSE))
#endif
	{
//		newFeat		= zNEW(zCVertFeature 	)[polyNumVert+addNum];
//		newFeatList = zNEW(zCVertFeature*	)[polyNumVert+addNum];
//		newVertList = zNEW(zCVertex*		)[polyNumVert+addNum];
		newFeat		=                   S_AllocVertFeatures   (polyNumVert+addNum);
		newFeatList = (zCVertFeature **)S_AllocPointers       (polyNumVert+addNum);
		newVertList = (zCVertex **     )S_AllocPointers       (polyNumVert+addNum);
	}

#ifdef MEMPOOL_HOELLER
	else
	{
		GetMeshesPool().GetMesh(Mesh->poolIndex)->AllocateVertexFeatures(addNum);

		zCVertex **oldVPtrPtr = GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexPool()->GetVertexPtrPtrList();
		GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexPool()->AllocNewVerticesPtr(addNum);
		if(oldVPtrPtr!=GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexPool()->GetVertexPtrPtrList())
		{
			// recalc internal vertexaddresses
			int i = GetMeshesPool().GetMesh(Mesh->poolIndex)->GetPolygonPool()->GetPolygonCount();
			if(i>0) while(i--)
			{
				zCPolygon *polygon = GetMeshesPool().GetMesh(Mesh->poolIndex)->GetPolygonPool()->GetPolygonPtr(i);
				if(polygon->vertex!=NULL)
				{
					int ptrOffs = int(polygon->vertex) - int(oldVPtrPtr);
					ptrOffs = ptrOffs >> 2;
					polygon->vertex = GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexPool()->GetVertexPtrPtrList() + ptrOffs;
				}
			}
		}
	}
#endif
		
	if (polyNumVert!=0)	
	{
		
		// feature
#ifdef MEMPOOL_HOELLER
		if(Mesh==NULL)
#endif
		{
			memcpy (newFeat    , *feature, sizeof( zCVertFeature  )*polyNumVert );		// dest, source
			//delete[] *feature;
            S_DeleteVertFeatures (polyNumVert, *feature);
			// feature-list

			memcpy (newFeatList, feature , sizeof( zCVertFeature* )*polyNumVert );		// dest, source
            //delete[] feature;
            S_DeletePointers     (polyNumVert, feature);
			// vertex

			memcpy (newVertList, vertex  , sizeof( zCVertex*      )*polyNumVert );		// dest, source
			//delete[] vertex;
            S_DeletePointers     (polyNumVert, vertex);
		}

	};

	//vertex		= newVertList;
#ifdef MEMPOOL_HOELLER
	if((Mesh==NULL)||(GetMeshesPool().IsPoolActive()==FALSE))
#endif
	{
		feature		 = newFeatList;
		vertex		= newVertList;
	}
#ifdef MEMPOOL_HOELLER
	else
	{
		zCVertFeature vertFeature;
		zCVertex* vertexPtr = NULL;
		int lastCn = GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexFeaturePool()->GetVertexFeatureCount();
		for (int i=polyNumVert; i<(polyNumVert+addNum); i++)
		{
			GetMeshesPool().GetMesh(Mesh->poolIndex)->AddVertexFeature(&vertFeature);
			GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexPool()->AddVertexPtr(vertexPtr);
		}
		newFeat = &GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexFeaturePool()->GetVertexFeaturePtrList()[lastCn];
		feature = &GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexFeaturePool()->GetVertexFeaturePtrPtrList()[lastCn];
		vertex	= &GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexPool()->GetVertexPtrPtrList()[lastCn];
	}
#endif

	polyNumVert += addNum;

#ifdef MEMPOOL_HOELLER
	if((Mesh==NULL)||(GetMeshesPool().IsPoolActive()==FALSE))
#endif
		for (int i=0; i<polyNumVert; i++)
			feature[i] = newFeat+i;
//	zerr.Message ("D: AllocVerts "+zSTRING(numVertAlloc));
};

void zCPolygon::AddVertex (zCVertex* a) { 
	AllocVerts (1);
	vertex[polyNumVert-1] = a;
};

void zCPolygon::AddVertexAndFeature (zCVertex *vert, zCVertFeature *feat) { 
	AllocVerts (1);
	  vertex [polyNumVert-1]  = vert;
	*(feature[polyNumVert-1]) = *feat;
};

void zCPolygon::SetVertices (zCVertex* a, zCVertex* b, zCVertex* c) {
	if (polyNumVert<3)	AllocVerts (3-polyNumVert);
	vertex[polyNumVert-3] = a;
	vertex[polyNumVert-2] = b;
	vertex[polyNumVert-1] = c;
	CalcNormal();
};

void zCPolygon::SetVertices (zCVertex* a, zCVertex* b, zCVertex* c, zCVertex* d, zBOOL calcNormal) {
	if (polyNumVert<4)	AllocVerts (4-polyNumVert);
//	AllocVerts (4);
	vertex[polyNumVert-4] = a;
	vertex[polyNumVert-3] = b;
	vertex[polyNumVert-2] = c;
	vertex[polyNumVert-1] = d;
	if (calcNormal)
		CalcNormal();
};

void zCPolygon::SetVertex (const int nr, zCVertex* vert) {
	if (polyNumVert<=nr) AllocVerts (nr-polyNumVert+1);
	vertex[nr] = vert;
};

void zCPolygon::SetFeature (const int nr, zCVertFeature* feat) {
	if (polyNumVert<=nr) AllocVerts (nr-polyNumVert+1);
	*(feature[nr]) = *feat;
};

// FIXME: dirty coding ...
void zCPolygon::CopyValuesInto (zCPolygon* destPoly) const { 
	destPoly->polyPlane = polyPlane;
	destPoly->flags		= flags;
	if (material)	
	destPoly->material	= (zCMaterial*)material->AddRef();
	
	// features werden gleich miterzeugt & kopiert, da sie nicht geshared werden
//	zCVertFeature  *newFeat	    = zNEW(zCVertFeature  )[polyNumVert];
//	zCVertFeature **newFeatList = zNEW(zCVertFeature* )[polyNumVert];

	zCVertFeature  *newFeat	    =                     S_AllocVertFeatures(polyNumVert);
	zCVertFeature **newFeatList = (zCVertFeature **)  S_AllocPointers    (polyNumVert);
	destPoly->feature = newFeatList;
	for (int i=0; i<polyNumVert; i++) {
		destPoly->feature[i]    = newFeat+i;
		*(destPoly->feature[i]) = *(feature[i]);
	};
};

void zCPolygon::CopyPolyInto (zCPolygon *poly) const {
	// Assert: beide Polys sind im selben Poly-Container
	(*poly)					= *(this);
	{
		poly->vertex		= 0;
		poly->polyNumVert	= 0;

		poly->AllocVerts		(this->polyNumVert); 
		this->CopyValuesInto	(poly);

		for (int j=0; j<this->polyNumVert; j++) {
			poly->vertex[j] = this->vertex[j];
		};
	};
};

void zCPolygon::RemoveVerticesAndFeatures () {
	// remove, but dont delete
	if (vertex)
#ifdef MEMPOOL_HOELLER
		if((Mesh==NULL)||(GetMeshesPool().IsPoolActive==FALSE))
#endif
            S_DeletePointers(polyNumVert, vertex);
//			delete[] vertex;
	if (feature) 
	{
#ifdef MEMPOOL_HOELLER
		if((Mesh==NULL)||(GetMeshesPool().IsPoolActive()==FALSE))
#endif
		{
            S_DeleteVertFeatures(polyNumVert, *feature);
            S_DeletePointers    (polyNumVert, feature );

//			delete[] *feature;
//            delete[] feature; // [Moos] Leakfix
		}
#ifdef MEMPOOL_HOELLER
		else
		{
			GetMeshesPool().GetMesh(Mesh->poolIndex)->GetVertexFeaturePool()->ClearVertexFeatures();
		}
#endif
	};

	vertex		= 0;
	feature		= 0;
	polyNumVert = 0;
};

/*
Subject 2.01: How do I find the area of a polygon?
    The signed area can be computed in linear time by a simple sum.
    The key formula is this:
        If the coordinates of vertex v_i are x_i and y_i,
        twice the signed area of a polygon is given by
        2 A( P ) = sum_{i=0}^{n-1} (x_i y_{i+1} - y_i x_{i+1}).
    Here n is the number of vertices of the polygon.
    References: [O' Rourke (C)] pp. 18-27; [Gems II] pp. 5-6:
    "The Area of a Simple Polygon", Jon Rokne.
    To find the area of a planar polygon not in the x-y plane, use:
       2 A(P) = abs(N . (sum_{i=0}^{n-1} (v_i x v_{i+1})))
       where N is a unit vector normal to the plane. The `.' represents the
       dot product operator, the `x' represents the cross product operator,
       and abs() is the absolute value function.
    [Gems II] pp. 170-171:
    "Area of Planar Polygons and Volume of Polyhedra", Ronald N. Goldman.

 Area = |(V1 - V0) cross (V2 - V0)| / 2
 Where V0, V1, V2 are position vectors of the three vertices and
        | | denotes vector magnitude.

*/

zREAL zCPolygon::GetArea () const {
	zVEC3 sum(0,0,0);
	for (int i=0; i<polyNumVert; i++) {
		sum += vertex[i]->position ^ vertex[(i+1)%polyNumVert]->position;
//		sum += (vertex[i+1]->position-vertex[i]->position) ^ (vertex[(i+1)%polyNumVert]->position-vertex[i+1]->position);
	}; 
	return zREAL(0.5F) * zAbs (polyPlane.normal * sum);
};

zREAL zCPolygon::GetLongestEdgeLen() const {
	zREAL len=0;
	for (int i=0; i<polyNumVert; i++) {
		len = zMax (len, (vertex[i]->position-vertex[(i+1)%polyNumVert]->position).Length());
	}; 
	return len;
};

void zCPolygon::ResetStaticLight () {
	if (!feature) return;
	for (int i=0; i<polyNumVert; i++) feature[i]->lightStat.Reset();
};

// --------------------------------------------------------------------------

void zCPolygon::SetStaticLight (const zCOLOR lightStat) {
	if (!feature) return;
	for (int i=0; i<polyNumVert; i++) feature[i]->lightStat = lightStat;
};

// --------------------------------------------------------------------------

void zCPolygon::SetLightDyn (const zCOLOR lightDyn) {
	if (!feature) return;
	for (int i=0; i<polyNumVert; i++) feature[i]->lightDyn = lightDyn;
};

// --------------------------------------------------------------------------

void zCPolygon::SetLightStatAlpha (const zBYTE alpha) {
	if (!feature) return;
	for (int i=0; i<polyNumVert; i++) feature[i]->lightStat.alpha = alpha;
};

// --------------------------------------------------------------------------

void zCPolygon::ResetLightDynToLightStat () {
	if (!feature) return;
	for (int i=0; i<polyNumVert; i++) feature[i]->lightDyn = feature[i]->lightStat;
};


// --------------------------------------------------------------------------

void zCPolygon::AddToLightDyn (const zCOLOR lightDelta) {
	if (!feature) return;
	for (int i=0; i<polyNumVert; i++) feature[i]->lightDyn.AddRGB (lightDelta);
};

// --------------------------------------------------------------------------

// FIXME: den Slab-Test benutzen (=> aus BBox/Ray Intersection)
/*
Oder Eberly?:

The following approach uses the method of separating axes.
Let the plane of the polygon contain point P and have unit
length normal N, so the plane is Dot(N,X-P) = 0.  Let the
bounding box have center C, axes U0, U1, U2, and extents
e0, e1, and e2.

(1) Test if a normal line separates the polygon and box.
Project the box onto the line C + t*N.  The center of the
box projects to t = 0.  The radius of the interval of
projection is

    Rb = e0*|Dot(N,U0)|+e1*|Dot(N,U1)|+e2*|Dot(N,U2)|

The plane projects to a single value Rp = Dot(N,P-C).  If
|Rp| > Rb, then the plane and box do not intersect, so the
polygon and box do not intersect.

(2) Otherwise, the plane and box intersect.  Project the
box onto the plane of the polygon.  If N is not perpendicular
to any of the box axes, the projection is a hexagon with
three pairs of parallel sides.  If N is perpendicular to one
of the box axes, the projection is a rectangle.

The problem is now in 2D.  You need to determine if
a hexagon or rectangle intersect a convex polygon.  The
method of separating axes applies here also.  Let the
convex polygon have E edges.  If the box projection is
a hexagon, you have E+3 directions to test for separation.
If the box projection is a rectangle, you have E+2 directions
to test.

I have code for separation of two 2D point sets at my
web site.  The first part of the code computes the convex
hulls of each point set.  That code can be ripped out for
your problem since your point sets are already convex.
http://www.magic-software.com


*/
zBOOL zCCFASTCALL	zCPolygon::CheckBBoxPolyIntersection (const zTBBox3D& bbox3D) const {
	// Testetappen:
	// 1) Check, ob alle Verts auf einer der 6 Seite der BBox liegen
	// 2) Check, ob eine Poly-Kante eine der 6 Seite der BBox durchdringt
	// 3) Check, ob eine der 4 BBox-Diagonalen das Poly schneiden
	
	// FIXME: zur Optimierung evtl. alle Vert-Positions lokal kopieren !

	// => Arnfold2, File "aabbIntersection.cpp"

	// sollte der Test nicht anders lauten:
	// intersection, falls ein vert in der box

	int i,j; 
	// 1a) Check, ob alle Verts auf einer der 6 Seite der BBox liegen
	//     Early rejection
	//     => es koennen aber trotzdem noch Polys durchkommen, die zwar nicht die BBox 
	//        schneiden, aber ausserhalb 2 Planes der BBox schneiden
	for (i=0; i<3; i++) {
		for (j=0; j<polyNumVert; j++) if (vertex[j]->position[i]>=bbox3D.mins[i]) goto testFailed; 
		return FALSE;
testFailed:;
		for (j=0; j<polyNumVert; j++) if (vertex[j]->position[i]<=bbox3D.maxs[i]) goto testFailed2; 
		return FALSE;
testFailed2:;
	}; 

	// 1b) Check, ob BBox komplett auf der einen oder anderen Seite der polyPlane liegt..
	//     Early rejection
	//     (eliminiert fehlende Faelle des Tests 1a)
	if (bbox3D.ClassifyToPlane (polyPlane)!=zPLANE_SPANNING) return FALSE;

	// An dieser Stelle MUSS sichergestellt sein:
	// - KEINE Verts befinden sich IN der BBox !
	// - die polyPlane SCHNEIDET die BBox

	// 2) Check, ob eine Poly-Kante eine der 6 Seite der BBox durchdringt
	//    FIXME: noch optimierbar ??
	//	  FIXME: => BBox/Ray Test !!
	int dim2, dim3;
	dim2 = 0;
	dim3 = 1;
	for (i=0; i<3; i++) {
		zREAL	dn, alpha, intersDIM2, intersDIM3;
		zPOINT3	start, ray, inters;
		dim2++; if (dim2==3) dim2=0;
		dim3++; if (dim3==3) dim3=0;

		for (j=0; j<polyNumVert; j++) {
			int nextVert = j+1; if (nextVert>=polyNumVert) nextVert=0;
			start	= vertex[j		 ]->position;
			ray		= vertex[nextVert]->position-start;

			zREAL planeNormal, planeDistance;
			// Mins
			planeNormal		=-1;
			planeDistance	=-bbox3D.mins[i];
			for (int k=0; k<2; k++) {
				dn = ray[i]*planeNormal;
				if (dn!=0) {							// parallel ?
					alpha	= (planeDistance - (planeNormal * start[i])) / dn;
					if ((alpha>=0) && (alpha<=1)) {
						// Plane auch im Bereich der BBox getroffen ?
						intersDIM2		= start[dim2] + alpha*ray[dim2]; 
						if ((intersDIM2>=bbox3D.mins[dim2]) && (intersDIM2<=bbox3D.maxs[dim2])) {
							intersDIM3	= start[dim3] + alpha*ray[dim3];
							if ((intersDIM3>=bbox3D.mins[dim3]) && (intersDIM3<=bbox3D.maxs[dim3])) {
//								zerr.Message ("A");
								return TRUE;
							};
						};
					};
				};
				// Maxs
				planeNormal		=+1; 
				planeDistance	= bbox3D.maxs[i];
			};
		};
	};

	// 3) Check, ob die eine der 4 BBox-Diagonalen das Poly schneiden
	//    (_muss_ vor Test 2, oder ?)
	//    ACHTUNG: das schnellere Plane::Intersection geht definitiv nicht ! Es muss geprueft werden,
	//             ob der Diagonalen-Hit auch im Poly liegt !!
	zVEC3	start, ray, inters;
	zREAL	alpha;
	 
	start	= bbox3D.mins;
	ray		= bbox3D.maxs-start;
	// erwartet, dass Intersection den alpha-Test [0..1] macht !!
//	if (polyPlane.Intersection (start, ray, inters)) return TRUE;
	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) return TRUE; 
//	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) { zerr.Message ("1"); return TRUE; };

	start	= zVEC3(bbox3D.mins[0], bbox3D.maxs[1], bbox3D.mins[2]);
	ray		= zVEC3(bbox3D.maxs[0], bbox3D.mins[1], bbox3D.maxs[2])-start;
//	if (polyPlane.Intersection (start, ray, inters)) return TRUE;
	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) return TRUE;
//	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) { zerr.Message ("2"); return TRUE; };

	start	= zVEC3(bbox3D.maxs[0], bbox3D.mins[1], bbox3D.mins[2]);
	ray		= zVEC3(bbox3D.mins[0], bbox3D.maxs[1], bbox3D.maxs[2])-start;
//	if (polyPlane.Intersection (start, ray, inters)) return TRUE;
	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) return TRUE;
//	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) { zerr.Message ("3"); return TRUE; };

	start	= zVEC3(bbox3D.mins[0], bbox3D.mins[1], bbox3D.maxs[2]);
	ray		= zVEC3(bbox3D.maxs[0], bbox3D.maxs[1], bbox3D.mins[2])-start;
//	if (polyPlane.Intersection (start, ray, inters)) return TRUE;
	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) return TRUE;
//	if (CheckRayPolyIntersection2Sided (start, ray, inters, alpha)) { zerr.Message ("4"); return TRUE; };

	return FALSE;
};

/*
zBOOL zCPolygon::CheckBSpherePolyIntersection(const zTBSphere3D& sphere3D, const zVEC3 moveDir) const {
	// Strategie:
	// - 

	zPOINT3 inters;
	zREAL	alpha;

	// hullPoint= Punkt auf Sphere, der PolyPlane am naechsten liegt.
	// inters	= Punkt auf PolyPlane, mit dem bei vorgeg. moveDir collidiert wird, falls dieser Punkt IM Poly liegt
	zPOINT3 hullPoint = sphere3D.center + (-polyPlane.normal * sphere3D.radius);
//	polyPlane.Intersection (hullPoint, moveDir, inters);
	// Exit, falls der Strahl nicht das Poly trifft (hit im Poly?), oder
	// das Poly nicht innerhalb dier moveDir getroffen wird (alpha 0..1)
	zVEC3 moveVec = moveDir*100000;
	// FALSE=> Punkt liegt nicht im Poly
	if (CheckRayPolyIntersection (hullPoint, moveVec, inters, alpha)) {
		// TRUE=> Punkt liegt IM Poly
		// Collision, falls moveDir>=shortDist
		zREAL shortDist = (inters-hullPoint).Length2();
		if (moveDir.Length2()>=shortDist) return TRUE;
		return FALSE;
	} else {
		// FALSE=> Punkt liegt NICHT im Poly
		// Sphere koennte nun noch mit den Edges collidieren
		// Nun alle Poly-Edges checken
		for (int i=0; i<polyNumVert; i++) {
			int nextVert=i+1; if (nextVert>=polyNumVert) nextVert=0;
			zTPlane edgePlane;
			edgePlane.Calc (vertex[i]->position, vertex[i]->position + moveDir, vertex[nextVert]->position);
		};
	};
	return FALSE;
};*/

zBOOL zCCFASTCALL	zCPolygon::CheckBSpherePolyIntersection(const zTBSphere3D& sphere3D) const {
	// FIXME: evtl. noch cookies Variante implementieren => SHORTDIST Berechnung, Intervall Suche bleibt erspart !
	if (sphere3D.ClassifyPlane (polyPlane)!=zCAM_CLIP_CROSSING) return FALSE;

	zPOINT3 inters;
	zREAL  alpha;
	// FIXME:  !!! ACHTUNG !!!!
	//         CheckPolyRayInters scheint nicht korrekt zu sein! Bei einem Poly-Split-BSP gibt es oft 
	//         FALSCH POSITIVE FAELLE, d.h. TRUE wird geliefert, obwohl das Poly nicht getroffen wird !!!!!!!
	if (CheckRayPolyIntersection (sphere3D.center, -polyPlane.normal*sphere3D.radius*2, inters, alpha)) {
//		DrawWire (GFX_RED);
//		zlineCache.Line3D (sphere3D.center, sphere3D.center -polyPlane.normal*sphere3D.radius, GFX_ORANGE); 
//		zlineCache.Line3D (inters, inters+zVEC3(0,50,0), GFX_BLUE); 
//		zerr.Message ("poly: "+zSTRING(int(this))+inters.GetString()+", "+zSTRING(alpha)+", "+zSTRING(polyNumVert));
//		if ((alpha<0) || (alpha>1)) zerr.Message ("poihh");
		return TRUE;
	}; 
 
	// Plane schneidet Sphere, aber der closesPoint liegt nicht im Poly.
	// Schneidet eine Poly-Edge die Sphere ?
	// Kann es sein: plane schneidet Sphere, closestPoint NICHT im Poly, aber keine Edge schneidet Sphere ??

	// Sphere koennte nun noch mit den Edges collidieren
	// Nun alle Poly-Edges checken
	for (int i=0; i<polyNumVert; i++) {
		int nextVert=i+1; if (nextVert>=polyNumVert) nextVert=0;
		zPOINT3 rayOrg	= vertex[i]->position;
		zVEC3	ray		= vertex[nextVert]->position - rayOrg;
		if (ray.Length()==0) continue;
		if (sphere3D.IsIntersecting (rayOrg, ray)) return TRUE;
	};
	return FALSE;
};

const zDOUBLE zEPS = zDOUBLE(0.001);
static inline int Classify (zDOUBLE dist) {
	if(dist > zEPS) return zPLANE_INFRONT; else 
	if(dist <-zEPS) return zPLANE_BEHIND ; else 
					return zPLANE_ONPLANE;
};


// Erzeugte Clip-Verts muessen in den übergeorndeten Container eingetragen
// werden !!
// das Mesh ist der Poly/Vert-Container, dem auch das Poly/dessen Verts angehören.

/* ----------------------------------------------------------------------

    zCPolygon::SplitPoly()

	16.11.2000	[Moos]	
                auf neue Vertices umgestellt

   ---------------------------------------------------------------------- */

void zCPolygon::SplitPoly (const zTPlane& pplane, zCPolygon *frontPoly, zCPolygon *backPoly, zCMesh* mesh) {
    int		i, j, nextvert;
	zBOOL	curin, nextin;
    zDOUBLE	curdot, nextdot, scale;

	// 
//	frontPoly->SetSourcePoly (GetSourcePoly());		// damit mehrfach-splits moeglich sind..
//	backPoly ->SetSourcePoly (GetSourcePoly());

//    curdot = vertex[0]->position * pplane.normal; 
    curdot = zDOUBLE(vertex[0]->position.n[VX]) * zDOUBLE(pplane.normal.n[VX]) +
			 zDOUBLE(vertex[0]->position.n[VY]) * zDOUBLE(pplane.normal.n[VY]) +
			 zDOUBLE(vertex[0]->position.n[VZ]) * zDOUBLE(pplane.normal.n[VZ]); 
	curin  = Classify (curdot - pplane.distance);

    for (i=0 ; i<polyNumVert; i++)  
    {
		nextvert = i+1; if (nextvert>=polyNumVert) nextvert=0;
//		nextdot	 = vertex[nextvert]->position * pplane.normal; 
		nextdot  = zDOUBLE(vertex[nextvert]->position.n[VX]) * zDOUBLE(pplane.normal.n[VX]) +
				   zDOUBLE(vertex[nextvert]->position.n[VY]) * zDOUBLE(pplane.normal.n[VY]) +
				   zDOUBLE(vertex[nextvert]->position.n[VZ]) * zDOUBLE(pplane.normal.n[VZ]); 
		nextin   = Classify (nextdot - pplane.distance);
        
		// Keep the current vertex if it's inside the plane
		if (curin==zPLANE_ONPLANE) {
			backPoly ->AddVertexAndFeature (vertex[i], feature[i]);
			frontPoly->AddVertexAndFeature (vertex[i], feature[i]);
		} else if (curin==zPLANE_BEHIND) {
			backPoly ->AddVertexAndFeature (vertex[i], feature[i]);
		} else if (curin==zPLANE_INFRONT) {
			frontPoly->AddVertexAndFeature (vertex[i], feature[i]);
		};

        // ** ACTUAL 3D-CLIPPING **
		// Add a *new* clipped vertex if one end of the current edge is
        // inside the plane and the other is outside
		// FIXME:	- clip prelit, etc.
        if (curin != nextin)
		{
			scale = (pplane.distance - curdot) / (nextdot - curdot);
			zCVertex& pinAct	 = *vertex[i]; 
			zCVertex& pinNext	 = *vertex[nextvert];
			zPOINT3&  pinNextPos = pinNext.position; 
			zPOINT3&  pinActPos  = pinAct .position;
			zCVertex  *newVert   = zNEW(zCVertex);
			// clip position
            for (j=0 ; j<3 ; j++) {
				newVert->position.n[j] = zREAL((zDOUBLE)pinActPos.n[j] + (zDOUBLE)(pinNextPos.n[j] - pinActPos.n[j]) * scale);
            }
			// clip tex-coords, light
//			newVert->vertNormal= pinAct.vertNormal + (pinNext.vertNormal - pinAct.vertNormal) * scale;	// FIXME: normalisiern ??
			// set flags
//			newVert->transformed= -1;
            newVert->ResetVertexTransform();
//			newVert->projected	= -1;
			backPoly ->AddVertex (newVert);
			frontPoly->AddVertex (newVert);

			// clip Feature
			// nur clippen, falls Source-Poly auch Features hat
			if (feature) {
				zCVertFeature& pinFAct	= *feature [i]; 
				zCVertFeature& pinFNext	= *feature [nextvert];
				zCVertFeature& newFeat	= *(backPoly->feature[backPoly->polyNumVert-1]);
				
				newFeat.texu		= zREAL(pinFAct.texu       + (pinFNext.texu      - pinFAct.texu		 ) * scale);
				newFeat.texv		= zREAL(pinFAct.texv       + (pinFNext.texv      - pinFAct.texv		 ) * scale);
				int intScale		= int(scale*255.0F);
				newFeat.lightStat.LerpRGBA (intScale, pinFAct.lightStat, pinFNext.lightStat);

				newFeat.vertNormal	= (pinFAct.vertNormal + (pinFNext.vertNormal- pinFAct.vertNormal) * zREAL(scale));	// FIXME: normalisiern ??
				newFeat.vertNormal.Normalize();
				*(frontPoly->feature[frontPoly->polyNumVert-1]) = newFeat;
			};
	
			// Vert ins Container-Mesh eintragen
			if (mesh) mesh->AddVertex (newVert);
        }
        curdot = nextdot;
        curin  = nextin;
    };
	// Plane zuweisen
	frontPoly->SetPlane (polyPlane); 
	backPoly ->SetPlane (polyPlane);
	// Material zuweisen
	if (material) {
		frontPoly->material = (zCMaterial*)material->AddRef();
		backPoly ->material = (zCMaterial*)material->AddRef();
	} else {
		frontPoly->material = 0;
		backPoly ->material = 0;
	};
	// flags
	backPoly->flags = frontPoly->flags = flags;
//	zerr.Message ("D: BSP: Front #: "+zSTRING(frontPoly->polyNumVert)+" Back  #: "+zSTRING(backPoly ->polyNumVert));
};

zBOOL zCCFASTCALL	zCPolygon::IsIntersectingProjection (zCPolygon *poly2, const zVEC3& projNormal) 
{
	// Die betrachteten Polys werden bei den Tests immer etwas "verkleinert"
//	const zREAL SCALE = zREAL(0.5F);

	zCPolygon *polyA = this;
	zCPolygon *polyB = poly2;

	int		vx, vy;
	{
		int vz;
		zVEC2	a;
		a[VX]	= zAbsApprox(projNormal[VX]);
		a[VY]	= zAbsApprox(projNormal[VY]);
		vz		= (zIsSmallerPositive (a.n[VX], a.n[VY]))						? VY : VX;
		vz		= (zIsSmallerPositive (a.n[vz], zAbsApprox(projNormal[VZ])))	? VZ : vz;
		vx		= vz+1; if (vx>2) vx=0;
		vy		= vx+1; if (vy>2) vy=0;
	};

	{
		for (int k=0; k<1; k++) 
		{
			zPOINT3 polyACenter = polyA->GetCenter();
			for (int l=0; l<polyA->polyNumVert; l++) 
			{
//				const zPOINT3& inters = polyA->vertex[l]->position;
				zPOINT3 inters	= polyA->vertex[l]->position + zREAL(0.2F)*(polyACenter - polyA->vertex[l]->position);
				inters			= inters - polyA->polyPlane.normal;

				// point-in-poly Test
				zBOOL inside = FALSE;
				for (int i = 0, j = polyB->polyNumVert-1; i < polyB->polyNumVert; j = i++) {
					const zPOINT3& u = polyB->vertex[i]->position;
					const zPOINT3& v = polyB->vertex[j]->position;

					if ((u[vy] >= inters[vy]) != (v[vy] >= inters[vy])) {
						zBOOL right = u[vx] >= inters[vx];
						if (right != (v[vx] >= inters[vx])) {
							zREAL t = (u[vy] - inters[vy]) / (u[vy] - v[vy]);
							if (u[vx] + (v[vx] - u[vx]) * t >= inters[vx]) inside = !inside;
			//				if ((v[vx] - u[vx]) * (u[vy] - inters[vy]) >= (inters[vx] - u[vx]) * (u[vy] - v[vy])) inside = !inside;
						}
						else if (right) inside = !inside;
					}
				};
				if (inside) return TRUE;
			};
//			zSwap (polyA, polyB);
		};	
	};

//	polyA = this;
//	polyB = poly2;

	for (int k=0; k<1; k++) 
	{
		zPOINT3 polyACenter = polyA->GetCenter();
		zPOINT3 polyBCenter = polyB->GetCenter();
		for (int l=0; l<polyA->polyNumVert; l++) 
		{
			int lnext = l+1;	if (lnext>=polyA->polyNumVert) lnext=0;
//			zPOINT3 p1	= polyA->vertex[l	 ]->position;
//			zPOINT3 p2	= polyA->vertex[lnext]->position;
 			zPOINT3 p1	= polyA->vertex[l	 ]->position + zREAL(0.1F)*(polyACenter - polyA->vertex[l	   ]->position);
			zPOINT3 p2	= polyA->vertex[lnext]->position + zREAL(0.1F)*(polyACenter - polyA->vertex[lnext]->position);
//			if (zAbs(polyA->polyPlane.normal[VY])<0.001F) 
			{
				p1 -= 2.0F*polyA->polyPlane.normal;
				p2 -= 2.0F*polyA->polyPlane.normal;
			};

			// edge/edge intersection test
			for (int i=0; i<polyB->polyNumVert; i++) {
				int inext = i+1;	if (inext>=polyB->polyNumVert) inext=0;
				zPOINT3 p3 = polyB->vertex[i		]->position;
				zPOINT3 p4 = polyB->vertex[inext	]->position;

				zREAL a,b,c,ua,ub;
				b = (p4[vy]-p3[vy]) * (p2[vx]-p1[vx]) - (p4[vx]-p3[vx]) * (p2[vy]-p1[vy]);
				if (b==0) continue;
				a = (p4[vx]-p3[vx]) * (p1[vy]-p3[vy]) - (p4[vy]-p3[vy]) * (p1[vx]-p3[vx]);
				c = (p2[vx]-p1[vx]) * (p1[vy]-p3[vy]) - (p2[vy]-p1[vy]) * (p1[vx]-p3[vx]);

				ua = a/b;
				if ((ua<zREAL(0.0F)) || (ua>zREAL(1.0F))) continue;
				ub = c/b;
				if ((ub<zREAL(0.0F)) || (ub>zREAL(1.0F))) continue;
				return TRUE;
			};
		};
//		zSwap (polyA, polyB);
	};	

	return FALSE;
};

zBOOL zCCFASTCALL	zCPolygon::IsIntersecting (zCPolygon *poly2)
{
	// Die beiden Polys durchdringen sich gdw mind. eine Edge eines Polys das andere durchdringt
	zCPolygon	*poly		= this;
	for (int i=0; i<2; i++)
	{
		for (int j=0; j<poly->polyNumVert; j++)
		{
			const int		jnext	= (j+1) % poly->polyNumVert;
			const zPOINT3	rayOrg	= poly->vertex[j]->position;
			const zVEC3		ray		= poly->vertex[jnext]->position-rayOrg;
			zPOINT3	inters;
			zREAL	alpha;
			if (poly2->CheckRayPolyIntersection2Sided (rayOrg, ray, inters, alpha))
			{
				return TRUE;
			};
		};
		zSwap (poly, poly2);
	};
	return FALSE;
};

zBOOL zCPolygon::IsNeighbourOf(const zCPolygon *a_pTestPoly)
{
	for (int v=1; v<a_pTestPoly->polyNumVert; v++)
	{
		if (this->EdgePositionsPartOfPoly(a_pTestPoly->vertex[v-1], a_pTestPoly->vertex[v]))
		{
			return TRUE;
		}
	}
	if (this->EdgePositionsPartOfPoly(a_pTestPoly->vertex[a_pTestPoly->polyNumVert-1], a_pTestPoly->vertex[0]))
	{
		return TRUE;
	}
	return FALSE;
};

zBOOL zCPolygon::GetStaticLODPossible()
{
	if (!GetMaterial()->GetTexture()) return FALSE;
	if ( GetMaterial()->GetTextureName().Search("FLOOR")!=-1	||
		 GetMaterial()->GetTextureName().Search("BODEN")!=-1	||
		 GetMaterial()->GetTextureName().Search("GROUND")!=-1	||
		 GetMaterial()->GetTextureName().Search("PATH")!=-1		||
		 GetMaterial()->GetTextureName().Search("WAY")!=-1		||
		 GetMaterial()->GetTextureName().Search("ACKER")!=-1	||
		 GetMaterial()->GetTextureName().Search("MOUNTAIN")!=-1 ||
		 GetMaterial()->GetTextureName().Search("SURFACE")!=-1 )
	{
		return TRUE;
	}

	return FALSE;
}

