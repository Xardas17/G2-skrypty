/******************************************************************************** 
 
     $Workfile:: oBarrier.h           $                $Date:: 24.04.01 17:33    $
     $Revision:: 11                   $             $Modtime:: 22.04.01 16:14    $
       $Author:: Edenfeld                                                 $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Archiver (persistance system)
   created       : 19.10.00

 * $Log: /current_work/Gothic/_Ulf/oBarrier.h $
 * 
 * 11    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 10    19.03.01 21:28 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 9     18.03.01 18:49 Edenfeld
 * Demo Geschichten
 * 
 * 8     16.02.01 2:49 Hildebrandt
 * die Wahnsinns Barriere am Start!!!!!!!!
 * 
 * 7     14.11.00 16:43 Simon
 * 
 * 6     14.11.00 9:46 Simon
 * 
 * 5     14.11.00 9:19 Simon
 * 
 * 4     13.11.00 16:46 Simon
 * 
 * 3     10.11.00 10:33 Simon
 * 
 * 2     3.11.00 16:03 Simon
 * 
 * 1     3.11.00 15:45 Simon
 * 
 * 1     19.10.00 16:03 Simon
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 11 $ ($Modtime: 22.04.01 16:14 $)

#ifndef _OBARRIERE_H_
#define _OBARRIERE_H_

/* ================================================================================================================ */ 

class zCPolyStrip;
class zCMesh;

/* ================================================================================================================ */ 

typedef struct myVert
{
	int   vertIndex;
	int   vertNeighbours[8];
	int   numNeighbours;
	
	int   polyIndices[50];
	int   numPolyIndices;
	
	zBOOL active;
	
}myVert;

/* ================================================================================================================ */ 

enum zTThunderSector
{
	zTThunderSector_None,
	zTThunderSector_1,
	zTThunderSector_2,
	zTThunderSector_3,
	zTThunderSector_4,
};

typedef struct myThunder
{
	zVEC3        originVec;

	myThunder*   childs;
	int          numChilds;

	zREAL        startTime[5];

	zCPolyStrip* polyStrip;
	int          numSegs;

	zBOOL        valid;

	zREAL        t0, t1;
	int          numSplits;
	zBOOL        dead;

	zBOOL		 isChild;

	zTThunderSector sector;

	~myThunder();

}myThunder;

/* ================================================================================================================ */ 

typedef struct myPoly
{
	int Alpha;

}myPoly;

/* ================================================================================================================ */ 
/* ================================================================================================================ */ 

class oCBarrier
{

public:
 
	oCBarrier( void );
   ~oCBarrier( void );

	void Init				 ( );
	void Initialise          ( int newNumMaxThunders );

   	zBOOL Render             ( zTRenderContext& rndContext, zBOOL fadeInOut, zBOOL alwaysVisible );

protected:

	void  InitThunder       ( myThunder* thunder );
	void  RemoveThunder     ( myThunder* thunder );

	int   AddThunderSub     ( myThunder* rootThunder, int startIndex, int startNexIntex, int length, int numSplits );
	int   AddThunder        ( int startIndex, int length, zREAL random, zTThunderSector sector );

	zBOOL RenderThunder     ( myThunder* thunder, zTRenderContext& rndContext );
	void  RenderThunderList ( zTRenderContext& rndContext );

	void  SetAlphaRecursive ( int index, int addAlpha, int rec_step, int max_rec );
	
	zCMesh*    skySphereMesh;
	
	myPoly*    myPolyList;	
	myVert*    myVertList;
	
	int        numMyVerts;
	int        numMyPolys;
	
    myThunder* myThunderList;
    int        numMaxThunders;
    int        numMyThunders;
	
    int        actualIndex;
    int        rootBoltIndex;
	
    int        startPointList1[10];
	int        numStartPoints1;
	int        startPointList2[10];
	int        numStartPoints2;
	int        startPointList3[10];
	int        numStartPoints3;
	int        startPointList4[10];
	int        numStartPoints4;
	
	int        topestPoint;
	
	zBOOL      bFadeInOut;
	int			fadeState;
	
	zBOOL      fadeIn;
	zBOOL      fadeOut;
	zBOOL	   bFlashing;
	float	   fFlashTime;

	
	zCSoundFX    *sfx1;
	zTSoundHandle sfxHandle1;
	zCSoundFX    *sfx2;
	zTSoundHandle sfxHandle2;
	zCSoundFX    *sfx3;
	zTSoundHandle sfxHandle3;
	zCSoundFX    *sfx4;
	zTSoundHandle sfxHandle4;
	
	zCDecal      *thunderStartDecal;
	
private:

	zBOOL activeThunder_Sector1;
	zBOOL activeThunder_Sector2;
	zBOOL activeThunder_Sector3;
	zBOOL activeThunder_Sector4;

	zVEC2		*originalTexUVList;

	void RenderLayer			(zTRenderContext& rndContext, int layerNumber, zBOOL &addNewThunder);
	void AddTremor				(zTRenderContext& renderContext);
};

/* ================================================================================================================ */ 

class oCSkyControler_Barrier : public zCSkyControler_Outdoor
{
public:
	oCSkyControler_Barrier();
	~oCSkyControler_Barrier();

	void RenderSkyPre();
 
//	void SetFadeInOut			( zBOOL fadeInOut    ) { bFadeInOut = fadeInOut;       };
//	void SetShowBarrier			( zBOOL showBarrier  ) { bShowBarrier = showBarrier;   };
//	void SetShowThunders		( zBOOL showThunders ) { bShowThunders = showThunders; };
//	void SetTimeIsFullVisible	( zREAL isFullVisible ) { fTimeIsFullVisible = isFullVisible; };

private:

	oCBarrier *barrier;
	zBOOL      bFadeInOut;
};

#endif

/* ================================================================================================================ */ 

