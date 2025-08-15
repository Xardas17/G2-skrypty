/******************************************************************************** 
 
     $Workfile:: z3d.cpp              $                $Date:: 13.12.00 10:11   $
     $Revision:: 24                   $             $Modtime:: 13.12.00 9:44    $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/ZenGin/_Dieter/z3d.cpp $
 * 
 * 24    13.12.00 10:11 Moos
 * 
 * 23    6.12.00 18:05 Moos
 * 
 * 22    5.12.00 12:04 Moos
 * 
 * 21    4.12.00 18:23 Moos
 * 
 * 20    17.11.00 19:29 Moos
 * 
 * 19    19.10.00 17:48 Keskenti
 * 
 * 18    4.10.00 23:36 Hildebrandt
 * 
 * 17    4.10.00 23:33 Hildebrandt
 * 
 * 16    21.08.00 17:18 Hildebrandt
 * 
 * 15    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 14    21.07.00 15:10 Hildebrandt
 * 
 * 13    21.07.00 14:28 Hildebrandt
 * 
 * 12    6.07.00 13:33 Hildebrandt
 * 
 * 7     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 6     4.05.00 22:14 Hildebrandt
 * 
 * 5     3.05.00 23:57 Hildebrandt
 * zenGin 089d
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 15    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 14    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 12    14.01.00 21:08 Hildebrandt
 * zenGin 0.85c
 * 
 * 11    10.01.00 15:12 Hildebrandt
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
/// @author   Author: Hildebrandt 
/// @version $Revision: 24 $ ($Modtime: 13.12.00 9:44 $)


/*
	- zCBsp...
	- zCWorld

	- zCDecal	
	- zCPolygon, zCPortal
	- zCVertex, zCVertFeature
 
	- zCVisual

	- zCVob
	- zCVobLight, ..
	- zCVobSound
	- zCLensFlareFX
	- zTEngineStats
	- zCCamera
	- zTPlane
	- zCLineCache
*/

/*

zCCamera sollte Objekte von folgenden Klassen enthalten:
- Clipper
- Frustum (==Clipper?)

*/

#ifdef ZENGINE_DEBUG
	#define zDEBUG_COLLECT_STATS
#endif


#include <zCore.h>
#include <z3d.h>
#include <zVob.h>
#include <zView.h>
#include <zMemPool.h>
#include <zVertexTransform.h>

#pragma warning( disable : 4244 ) 


zMEMPOOL_DEFINITION        (zCVertex)
zMEMPOOL_DEFINITION        (zCVertFeature)
zMEMPOOL_DEFINITION        (zCPolygon)
zMEMPOOL_DEFINITION        (zCPortal)


int playerLightInt = 7000; 

zTEngineStats zengineStats;

void zTEngineStats::PrintScreen	(int xscr, int yscr)
{
	if (xscr==-1) xscr=6600;
	if (yscr==-1) yscr=1000;
	screen->Print (xscr,yscr+0*200, "ai       : "+zSTRING(numVobAI));
	screen->Print (xscr,yscr+1*200, "ai_only  : "+zSTRING(numVobAI_only));
	screen->Print (xscr,yscr+2*200, "ai_full  : "+zSTRING(numVobAI_full));
	screen->Print (xscr,yscr+3*200, "aiEndMove: "+zSTRING(numVob_EndMovement));
	screen->Print (xscr,yscr+4*200, "mdBoxTree: "+zSTRING(numModelUpdateBBoxTree));
	screen->Print (xscr,yscr+5*200, "cdIntrp  : "+zSTRING(numVobFirstTestInterpen));

	screen->Print (xscr,yscr+6*200, "clPolys  : "+zSTRING(numPolysClipped));
	screen->Print (xscr,yscr+7*200, "cdPlanes : "+zSTRING(numPlanesClipped));

	screen->Print (xscr,yscr+8*200, "traceRay : "+zSTRING(numTraceRay));
	
	Clear();
};

///////////////////////////////////////////////////////////////////////////
//     Line-Cache
///////////////////////////////////////////////////////////////////////////

zCLineCache zlineCache;

zCLineCache::~zCLineCache() { 
	delete cache;
};

void zCLineCache::Line (int x1, int y1, int x2, int y2, zCOLOR color) { 
	if (nextFree>=numEntries) {
		if (numEntries==0) {
			numEntries	= 4096;
			cache		= zNEW(zTCacheEntry) [numEntries];
		} else {
			nextFree=0;
			return;
		};
	};
	cache [nextFree].x1		= (x1);
	cache [nextFree].y1		= (y1);
	cache [nextFree].x2		= (x2);
	cache [nextFree].y2		= (y2);
	cache [nextFree].color  = color;
	nextFree++;
}; 

void zCLineCache::Flush(zCViewBase* view) {
	if (nextFree==0) return;
	for (int i=0; i<nextFree; i++) {
		view->Line (view->anx(cache[i].x1), view->any(cache[i].y1),
			        view->anx(cache[i].x2), view->any(cache[i].y2), cache[i].color);	// clippt die Line an den View-Boundaries
//		zrenderer->DrawLine (  (cache[i].x1), (cache[i].y1),
//						       (cache[i].x2), (cache[i].y2), cache[i].color);
	};
	nextFree=0; 
};

void zCLineCache::Line3D (const zPOINT3& a, const zPOINT3& b, zCOLOR color, zBOOL useZBuffer) {
	if (!zCCamera::activeCam) return;
	if (!zCCamera::activeCam->GetVob()) return;
	const zMAT4& camMatrix = zCCamera::activeCam->GetVob()->trafoObjToWorld.InverseLinTrafo();

	zPOINT3 point1, point2;
	int xscr[2], yscr[2];

	point1 = camMatrix * a;	
	point2 = camMatrix * b;	
	if ((point1[VZ]<=0) && (point2[VZ]<=0)) return;

	Alg_ClipAtZ0 (point1, point2);

	// guard div0
	if (point1[VZ]<=0) point1[VZ]=0.00001F;
	if (point2[VZ]<=0) point2[VZ]=0.00001F;

	zCCamera::activeCam->Project ( &point1, xscr[0], yscr[0]);
	zCCamera::activeCam->Project ( &point2, xscr[1], yscr[1]); 
	if (!useZBuffer) {
		zlineCache.Line (xscr[0], yscr[0], xscr[1], yscr[1], color);
	} else {
		screen->nax (xscr[0]);
		screen->nay (yscr[0]);
		screen->nax (xscr[1]);
		screen->nay (yscr[1]);
		if (!screen->ClipLine (xscr[0], yscr[0], xscr[1], yscr[1])) return;
		screen->anx (xscr[0]);
		screen->any (yscr[0]);
		screen->anx (xscr[1]);
		screen->any (yscr[1]);
		zrenderer->DrawLineZ (xscr[0], yscr[0], 1 / point1[VZ], xscr[1], yscr[1], 1 / point2[VZ], color);
	};
};

void zCLineCache::LineCS3D (const zPOINT3& a, const zPOINT3& b, zCOLOR color) {
	if (!zCCamera::activeCam) return;
	zCCamera::activeCam->Activate();
	zPOINT3 point1, point2;
	int xscr[2], yscr[2];

	point1 = a;
	point2 = b;
	if ((point1[VZ]<=0) && (point2[VZ]<=0)) return;

	Alg_ClipAtZ0 (point1, point2);

	if (point1[VZ]<=0) return;
	if (point2[VZ]<=0) return;

	zCCamera::activeCam->Project ( &point1, xscr[0], yscr[0]);
	zCCamera::activeCam->Project ( &point2, xscr[1], yscr[1]); 
	screen->nax (xscr[0]);
	screen->nay (yscr[0]);
	screen->nax (xscr[1]);
	screen->nay (yscr[1]);
	if (!screen->ClipLine (xscr[0], yscr[0], xscr[1], yscr[1])) return;
	screen->anx (xscr[0]);
	screen->any (yscr[0]);
	screen->anx (xscr[1]);
	screen->any (yscr[1]);
//	zlineCache.Line (xscr[0], yscr[0], xscr[1], yscr[1], color);
/*	if (0)
	zerr.Message (
		zSTRING(xscr[0])+", "+
		zSTRING(yscr[0])+", "+
		zSTRING(xscr[1])+", "+
		zSTRING(yscr[1])+", "+
		zSTRING(point1[VZ])+", "+
		zSTRING(point2[VZ]));
		*/
	zrenderer->DrawLineZ (xscr[0], yscr[0], 1 / point1[VZ], xscr[1], yscr[1], 1 / point2[VZ], color);
};

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

/* **************************************************

        zCVertex und zCVertexTransform

***************************************************** */


void zCVertex::Draw (const zCOLOR& col, const zBOOL useZBuffer)
{
	const zREAL LEN = zREAL(5.0F);
	zlineCache.Line3D (position-zVEC3(0,LEN,0), position+zVEC3(0,LEN,0), col, useZBuffer);
	zlineCache.Line3D (position-zVEC3(LEN,0,0), position+zVEC3(LEN,0,0), col, useZBuffer);
};

//zCVertexTransform         s_vertexTransformData[zMAX_VERTEX_TRANSFORM];           // statisches Array der transformierten Vertices
//zCVertexTransform * const zCVertex::gibtsnichtmehr=s_vertexTransformData;     // und pointer darauf
//int                       zCVertex::gibtsnichtmehrCurrent=1;                  // und der aktuelle Index darin
//bool                      zCVertex::s_overflow = false;                           // hat obiger Index schon einmal zMAX_VERTEX_TRANSFORM überschritten?



/* ----------------------------------------------------------------------
	
    zCVertex::ResetVertexTransforms()	

    Setzt die Daten aller Vertices auf den Ursprungszustand 
    (= keine Transformation) zurück

	15.11.2000	[Moos]	
                Erzeugt

    01.12.2000  [Moos]
                Auf allgemeine MemPool-Klasse umgestellt

   ---------------------------------------------------------------------- */

void zCVertex::ResetVertexTransforms(){

    zCVertexTransform::PoolRestore(); 
    zNEW(zCVertexTransform);           // Hack: Element 0 wollen wir nicht.

    /*
    int i;// = sizeof(zCVertex);;

    if (s_overflow)
        i=zMAX_VERTEX_TRANSFORM-1;
    else
        i = gibtsnichtmehrCurrent-1;

    for (;i>=1;i--)
        ResetVertexTransform(&gibtsnichtmehr[i]);
    gibtsnichtmehrCurrent = 1;

    s_overflow = false; */
}

/* ----------------------------------------------------------------------
	
    zCVertex::CreateVertexTransform()	

    Erzeugt die zu diesem Vertex gehörende Transform-Instanz

	15.11.2000	[Moos]	
                Erzeugt

    01.12.2000  [Moos]
                Auf allgemeine MemPool-Klasse umgestellt

   ---------------------------------------------------------------------- */

// use this function if you are sure the vertex has NOT been transformed
zCVertexTransform* zCVertex::CreateVertexTransform(){
    zERR_ASSERT(!transformedIndex);

    /*
    zUWORD            index =  gibtsnichtmehrCurrent++;
    zCVertexTransform    *v = &gibtsnichtmehr[index];

    if (gibtsnichtmehrCurrent >= zMAX_VERTEX_TRANSFORM){
        gibtsnichtmehrCurrent = 1;
        s_overflow = true;
    }

    if (s_overflow)
        ResetVertexTransform(v);

    */

    zCVertexTransform *v = NULL;

    while (!transformedIndex){ // Hack: Element 0 wollen wir nicht.
        v                    = zNEW(zCVertexTransform);
        transformedIndex     = zCVertexTransform::PoolLastAllocatedIndex();


        if (!transformedIndex)
            v->untransformed = NULL;
    }

    v ->untransformed = this;

    return v;
}

#ifdef DEBUG_MOOS
#define zMAX_VERTEX_TRANSFORM 100         // Stresstest für den Überlauf
#else
#define zMAX_VERTEX_TRANSFORM 20000
#endif

zMEMPOOL_VOLATILE_DEFINITION_OVERFLOW(zCVertexTransform, zMAX_VERTEX_TRANSFORM, zVOLATILE_OVERFLOW_RESIZE)

// *******************************************************************************************************************
// *******************************************************************************************************************
// *******************************************************************************************************************


///////////////////////////////////////////////////////////////////////////

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
