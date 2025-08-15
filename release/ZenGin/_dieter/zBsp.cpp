/******************************************************************************** 
 
     $Workfile:: zBSP.cpp             $                $Date:: 24.04.01 17:33   $
     $Revision:: 71                   $             $Modtime:: 23.04.01 19:49   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created: 

 * $Log: /current_work/ZenGin/_Dieter/zBSP.cpp $
 * 
 * 71    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 70    15.03.01 2:17 Hildebrandt
 * 
 * 69    15.02.01 5:04 Hildebrandt
 * 
 * 68    9.02.01 18:41 Moos
 * AlphaVob-Leakfix
 * 
 * 67    9.02.01 15:15 Moos
 * 
 * 66    8.02.01 21:39 Hildebrandt
 * 
 * 65    8.02.01 6:53 Hildebrandt
 * 
 * 64    5.02.01 18:01 Moos
 * 
 * 63    1.02.01 19:58 Moos
 * 
 * 62    30.01.01 4:00 Hildebrandt
 * 
 * 61    29.01.01 16:04 Moos
 * 
 * 60    27.01.01 19:42 Moos
 * 
 * 59    27.01.01 13:03 Moos
 * 
 * 58    26.01.01 20:03 Hildebrandt
 * 
 * 57    26.01.01 19:18 Moos
 * 
 * 56    26.01.01 18:02 Hildebrandt
 * 
 * 55    25.01.01 22:20 Hildebrandt
 * 
 * 54    25.01.01 17:02 Hildebrandt
 * 
 * 53    25.01.01 17:01 Hildebrandt
 * 
 * 52    8.01.01 17:55 Hildebrandt
 * 
 * 51    20.12.00 3:05 Hildebrandt
 * 
 * 50    4.12.00 18:23 Moos
 * 
 * 49    22.11.00 19:59 Moos
 * 
 * 48    22.11.00 17:47 Moos
 * 
 * 47    17.11.00 23:16 Hildebrandt
 * 
 * 46    17.11.00 19:29 Moos
 * 
 * 45    17.11.00 16:35 Hildebrandt
 * 
 * 44    8.11.00 22:34 Hildebrandt
 * 
 * 43    7.11.00 18:24 Hildebrandt
 * 
 * 42    7.11.00 17:23 Hildebrandt
 * 
 * 41    3.11.00 19:05 Hildebrandt
 * 
 * 40    26.10.00 17:42 Hildebrandt
 * 
 * 39    26.10.00 16:49 Hildebrandt
 * 
 * 38    26.10.00 16:29 Hildebrandt
 * 
 * 37    26.10.00 2:36 Hildebrandt
 * 
 * 36    26.10.00 2:23 Hildebrandt
 * 
 * 35    25.10.00 15:06 Hildebrandt
 * 
 * 34    12.10.00 14:16 Hildebrandt
 * 
 * 33    11.10.00 21:42 Hildebrandt
 * 
 * 32    11.10.00 19:45 Hildebrandt
 * 
 * 31    22.09.00 20:25 Hildebrandt
 * 
 * 30    22.09.00 14:17 Moos
 * 
 * 29    21.09.00 20:58 Moos
 * 
 * 28    21.09.00 17:58 Hoeller
 * 
 * 27    14.09.00 17:25 Hildebrandt
 * 
 * 26    11.09.00 19:49 Hildebrandt
 * 
 * 25    2.09.00 6:53 Hildebrandt
 * 
 * 24    31.08.00 17:04 Hildebrandt
 * 
 * 23    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 22    21.08.00 17:18 Hildebrandt
 * 
 * 21    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 20    31.07.00 23:04 Rueve
 * 
 * 19    21.07.00 15:10 Hildebrandt
 * 
 * 18    21.07.00 14:28 Hildebrandt
 * 
 * 17    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 16    6.07.00 14:28 Hildebrandt
 * 
 * 15    6.07.00 13:33 Hildebrandt
 * 
 * 8     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 7     8.05.00 2:17 Hildebrandt
 * 
 * 6     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 5     3.05.00 23:57 Hildebrandt
 * zenGin 089d
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 18    24.03.00 20:45 Hildebrandt
 * fixed zCBspTree::DisposeTree() not disposing it's sectorList
 * 
 * 17    22.03.00 21:07 Hildebrandt
 * 
 * 16    22.03.00 2:58 Hildebrandt
 * zenGin 088a
 * 
 * 15    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 13    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 12    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 10    10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 8     18.11.99 22:18 Hildebrandt
 * 
 * 7     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 71 $ ($Modtime: 23.04.01 19:49 $)


#include <zCore.h>
#include <zWorld.h>
#include <zBsp.h>
#include <z3d.h>
#include <zFile3d.h>
#include <zoption.h>
#include <zSky.h>
#include <zRenderer.h>
#include <zInput_Win32.h>
#include <zGrafix.h>
#include <zView.h>
#include <zVertexBuffer.h>
#include <zRenderManager.h>
#include <zRayCache.h>
#include <zLensflare.h>
#include <zPolyStrip.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zSparseArray.h>
#include <zAccount.h>
#include <zFFT.h>


//#define zBSP_DEBUG_OUTDOOR

#ifdef ZENGINE_DEBUG
//	#define zBSP_DEBUG_OUTDOOR
//	#define zBSP_DONT_CULL_HORIZON
//	#define zBSP_DONT_CREATE_SECTORS				
//	#define zBSP_SHOW_GHOST_OCCLUDER
//	#define zBSP_FAST_MARK_OCCLUDER
#endif
//#define zBSP_DONT_CULL_HORIZON

#define zBSP_SHOW_VOBNAMES
//#define LEAF_NO_VOBS

int tr_numLeafs;
int tr_numLeafPolys;
int tr_numLeafVobs;
int tr_numLeafVobsSkip;

int			numFoundFarPolys;
int			numDrawnFarPolys;

int		bspFrameCtr;


//#define DEBUG_WAVES
#ifdef DEBUG_WAVES
static zREAL s_grid = 300;
static zREAL s_amp  = 30;
#endif
//#define E3_WATER


//#pragma optimize( "", off )
#pragma warning( disable: 4244 ) 




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static zBOOL				dontCull				= FALSE;
zBOOL						g_bIsInCompileLightMode	= FALSE;

static zVEC3				g_vecStartTrace;
static zVEC3				g_vecEndTrace;

static int					g_iNumTraversals	=	0;

static int					drawnLeafs;
zDWORD						bspCollectCtr		= 1;

static int					drawnVobs;
static zCBspTree*			actBspTree;
static zCCBspTree*			actCBspTree;

static zCArray<zCVobLight*> s_leafDynLights(10);
static zCArray<zCVobLight*> s_leafMovingLights(5);
static zBOOL				s_leafRelightPolys;

//
static int					numSectorsVisited;

// für: diverse BSP-Query Methoden (z.B. CollectPolysInBBox3D)
static zTBBox3D				ctestbbox3D; 
static zCArray<zCPolygon*>	cfoundPolyList(2048);



// ======================================================================================================================

// wird von zCBspTree::RenderVobList() benutzt

class zCRndAlphaSortObject_Vob : public zCRndAlphaSortObject {
public:
	//
    zCRndAlphaSortObject_Vob                                    () : vob(NULL), alpha(1) {}
    ~zCRndAlphaSortObject_Vob                                    (){ zRELEASE(vob); }

	void								Draw					(int currentIndex);

	//
	void								SetVob					(zCVob *vob) { zRELEASE(this->vob); this->vob = vob; zADDREF_ACCT(vob); };	// released on Draw()

	//
	static zCRndAlphaSortObject_Vob*	GetFreeAlphaVob			();
	static void							ResetFreeList			();

    static void                         ClearList               ();

protected:
	// Pool verfuegbarer AlphaVob Objekte
	enum								{ NUM_ALPHA_VOB = 256 };
	static zCRndAlphaSortObject_Vob		s_alphaVobList[NUM_ALPHA_VOB];
	static int							s_currentAlphaVob;

public:
	// Data
	zCVob		*vob;
	zREAL		alpha;		// 0..1
};

// Implementation

zCRndAlphaSortObject_Vob		zCRndAlphaSortObject_Vob::s_alphaVobList	[NUM_ALPHA_VOB];
int								zCRndAlphaSortObject_Vob::s_currentAlphaVob	= 0;

zCRndAlphaSortObject_Vob*	zCRndAlphaSortObject_Vob::GetFreeAlphaVob()
{
	if (s_currentAlphaVob>=NUM_ALPHA_VOB)	
	{
		zERR_FAULT_ONCE("D: RNDMAN: too few alphaVOBs!");
		s_currentAlphaVob=0;
	};
	return &(s_alphaVobList[s_currentAlphaVob++]);
};

void zCRndAlphaSortObject_Vob::ResetFreeList () 
{ 
	s_currentAlphaVob	= 0; 
};


void zCRndAlphaSortObject_Vob::Draw (int currentIndex)
{
	zERR_ASSERT						(vob);

	if (!vob) return;

	// fuer DrawVB Visuals..
	zTRenderContext renderContext;
	renderContext.Clear				();
	renderContext.clipFlags			= zCCamera::CLIP_FLAGS_FULL;
	renderContext.vob				= vob;
	renderContext.world				= vob->GetHomeWorld();
	renderContext.cam				= zCCamera::activeCam;
	
	// hier den alpha_blend_test eintragen, wenn ein poly des vobs 
	// TESTING aktiv hat, ansonsten normales blend
	zDWORD oldAlphaRefValue = zrenderer->GetAlphaReference();
	
	zrenderer->SetZBias(vob->GetZBias());

	if (vob->GetVisual()->GetAlphaTestingEnabled())		
	{
		zrenderer->SetAlphaReference	( oldAlphaRefValue * alpha );
		zrenderMan.SetOverrideAlpha		(alpha, zRND_ALPHA_FUNC_BLEND_TEST);
	}
	else 
	{
		zrenderMan.SetOverrideAlpha		(alpha, zRND_ALPHA_FUNC_BLEND);
	}
	vob->Render						(renderContext);
	zrenderMan.SetOverrideAlpha		(1, zRND_ALPHA_FUNC_NONE);
	zrenderer->SetAlphaReference	(oldAlphaRefValue);
//	zrenderer->SetZBias				(oldzbias);

	zRELEASE_ACCT(vob);
};

/* ----------------------------------------------------------------------
	
    zCRndAlphaSortObject_Vob::ClearList()

    Bringt die Liste wieder in den LEEREN Zustand

	 9.2.2001	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

void zCRndAlphaSortObject_Vob::ClearList () 
{ 
    s_currentAlphaVob   = NUM_ALPHA_VOB-1;

    while (s_currentAlphaVob >= 0)
    {
        zRELEASE(s_alphaVobList[s_currentAlphaVob].vob);
        s_currentAlphaVob--;
    }

	s_currentAlphaVob	= 0; 
};


/* ----------------------------------------------------------------------
	
     zCBspBase::ReleaseStaticReferences ()

     Löscht alle in dieser Datei gehaltene temporäre Refenenzen frei

	 9.2.2001	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCBspBase::ReleaseStaticReferences (){
    zCRndAlphaSortObject_Vob::ClearList();
}

// ***************************************************************************************************************
//		HORIZON
// ******************

#if 0
	static const int	HORI_PREC_SHIFT	= 0;
	static const zREAL	HORI_PREC_MUL	= zREAL(1.0F);
	static const zREAL	HORI_PREC_DIV	= zREAL(1.0F);
#elif 0
	static const int	HORI_PREC_SHIFT	= 1;
	static const zREAL	HORI_PREC_MUL	= zREAL(0.5F);
	static const zREAL	HORI_PREC_DIV	= zREAL(2.0F);
#elif 1
	static const int	HORI_PREC_SHIFT	= 2;
	static const zREAL	HORI_PREC_MUL	= zREAL(0.25F);
	static const zREAL	HORI_PREC_DIV	= zREAL(4.0F);
#elif 0
	static const int	HORI_PREC_SHIFT	= 4;
	static const zREAL	HORI_PREC_MUL	= zREAL(0.0625F);
	static const zREAL	HORI_PREC_DIV	= zREAL(16.0F);
#endif

//static zREAL	horizonZMax;
static zREAL	horizonYMin;
static zREAL	horizonY[1024];			// max screen xdim	// [BENDLIN] 800x600, should be 1600x1200???
static zREAL	horizonZ[1024];								// [BENDLIN] 800x600, should be 1600x1200???
static int		horizonXDim;			// 640;				// [BENDLIN] 800x600, should be 800???
static zBOOL	doScanHorizon;

static void		ScanHorizon		(zCPolygon* poly);							// call von: base
static void		RenderHorizon	();
static void		InitHorizon		();
static zBOOL	IsVisible		(const zTBBox3D& bbox3D, const int clipFlags);			// call von: base
static zBOOL	IsVisibleVob	(const zCVob *vob);								// call von: AddVobListOutdoor

//zCPolygon*	leafPolyList[1024];
//int			leafActPoly;

static void InitHorizon() {
	horizonXDim			= zCCamera::activeCam->vpData.xdim / int(HORI_PREC_DIV);
	const int fillValue	= zFloat2Int(zCCamera::activeCam->vpData.ymaxFloat);
	for (int i=0; i<horizonXDim; i++) {
		horizonY[i] = fillValue;
		horizonZ[i] =-99999;
	};
	horizonYMin = fillValue;
//	horizonZMax = -99999;
};

static void FillHorizon (int xstart, int xend, zREAL ypos) {
	xstart	= xstart	>> HORI_PREC_SHIFT;
	xend	= xend		>> HORI_PREC_SHIFT;
	for (int i=xstart; i<=xend; i++) {
		horizonY[i] = ypos; 
		horizonZ[i] = 0;
	};
	horizonYMin = zMin (horizonYMin, ypos);
};

static void DrawCamZ (int xleft, int xright, zREAL camz) {
//	zlineCache.Line (xpos, horizonY[xpos], xpos, horizonY[xpos]+2);
	int y = int((sqrt(camz) / 60000.0F) * -480.0F + 480.0F);  
	zlineCache.Line (xleft, y, xright, y+1, GFX_RED);
};
 
static zBOOL IsVisible (const zTBBox3D& bbox3D, const int clipFlags) 
{
#ifdef zBSP_DONT_CULL_HORIZON
	return TRUE;
#endif

//#ifdef ZENGINE_DEBUG
	if (dontCull) return TRUE;
	
//#endif

	// projecting 8 edge-vertices from bbox3D
//	int xscr[8], yscr[8];
	zCCamera *cam = zCCamera::activeCam;
	if (!cam) return TRUE;

	const zMATRIX4& mat = cam->camMatrix;
	/*zMATRIX4& mat = cam->camMatrixInv;
	zVEC3 at	= mat.GetAtVector();
	at[VY] = 0;

	zVEC3	up, right;
	zREAL	upLen;

	up		= zVEC3(0,1,0);					// 'default' UpVector
	up		= up - (((up * at)) * at);
	upLen	= up.Length();

	// Test, ob die Wahl des UpVectors(0,1,0) unguenstig war, d.h. up==newAtVector
	// (falls ja: alternatives up waehlen)
    // If this vector has near-zero length because the input specified a
    // bogus up vector, let's try a default up vector
    if (1e-6f>upLen)
    {
		up		= zVEC3(1,0,0) - at[VX] * at;
		upLen	= up.Length();
		
		// If we still have near-zero length, resort to a different axis.
		if (1e-6f>upLen)
		{
			up		= zVEC3(0,0,1) - at[VZ] * at;
			upLen	= up.Length();
		}
    }

	// kein SetHeading() moeglich?
	if (1e-6f<=upLen)
	{
		up		/= upLen;
		right	 = (up ^ at).Normalize();
	};

	mat.SetAtVector		(at);
	mat.SetUpVector		(up);
	mat.SetRightVector	(right);
	mat = mat.InverseLinTrafo();*/

	zVEC3	point[8];
	int		NUM;
	if (clipFlags==0)		// zCAM_CLIP_TRIV_IN
	{
		NUM		 = 4;
		point[0] = mat * zPOINT3(bbox3D.maxs.n[VX], bbox3D.maxs.n[VY], bbox3D.maxs.n[VZ]);
		point[1] = mat * zPOINT3(bbox3D.mins.n[VX], bbox3D.maxs.n[VY], bbox3D.mins.n[VZ]);
		point[2] = mat * zPOINT3(bbox3D.mins.n[VX], bbox3D.maxs.n[VY], bbox3D.maxs.n[VZ]);
		point[3] = mat * zPOINT3(bbox3D.maxs.n[VX], bbox3D.maxs.n[VY], bbox3D.mins.n[VZ]);
	} else {
		NUM		 = 8;
		
		zREAL xoff	= (bbox3D.maxs[VX]-bbox3D.mins[VX]);
		zREAL yoff	= (bbox3D.maxs[VY]-bbox3D.mins[VY]);
		zREAL zoff	= (bbox3D.maxs[VZ]-bbox3D.mins[VZ]);
		zVEC3 xinc	= zVEC3(mat[0][0]*xoff, mat[1][0]*xoff, mat[2][0]*xoff);
		zVEC3 yinc	= zVEC3(mat[0][1]*yoff, mat[1][1]*yoff, mat[2][1]*yoff);
		zVEC3 zinc	= zVEC3(mat[0][2]*zoff, mat[1][2]*zoff, mat[2][2]*zoff);
		zVEC3 base	= mat * bbox3D.mins;
		point[0]	= base;
		point[1]	= base + xinc;
		point[2]	= base		  +	yinc;
		point[3]	= base + xinc + yinc;
		point[4]	= base				 + zinc;
		point[5]	= base + xinc		 + zinc;
		point[6]	= base		  + yinc + zinc;
		point[7]	= base + xinc + yinc + zinc;
	};

	zREAL xscr, yscr;
	zREAL xmins		= 999999;
	zREAL xmaxs		=-999999;
	zREAL ymins		= 999999;
//	zREAL camMaxZ	=-999999;
	zREAL camMinZ;;
//	zREAL camMinZ	= zVALUE_MAX;

	int i=0;
	do {
		if (point[i].n[VZ]<=0)		return TRUE;
//		if (point[i].n[VZ]>camMaxZ) camMaxZ = point[i].n[VZ]; else 
//		if (point[i].n[VZ]<camMinZ) camMinZ = point[i].n[VZ]; 

		cam->Project (&point[i], xscr, yscr);
		xscr -= cam->vpData.xminFloat;				// offset wieder abziehen, um x-Koord im Bereich 0..Max zu haben
		if (xscr>xmaxs)	xmaxs = xscr;				// KEIN else !!
		if (xscr<xmins)	xmins = xscr;
		if (yscr<ymins)	ymins = yscr;
		i++;
	} while (i<NUM);

//	if (camMaxZ<horizonZMax) return TRUE;
//	camMinZ = (bbox3D.GetCenter()-zCCamera::activeCam->GetVob()->GetPositionWorld()).Length2(); 

	// konservativer, schneller check
	if (ymins<=1)			ymins=1;
	if (ymins<horizonYMin)	return TRUE;

	int xleft	= zFloat2Int(xmins * HORI_PREC_MUL);
	int xright	= zFloat2Int(xmaxs * HORI_PREC_MUL + 0.5F);

	if (xleft <0				) xleft= 0;					else
	if (xleft >horizonXDim-1	) return FALSE; 
	if (xright>horizonXDim-1	) xright = horizonXDim-1;	else
	if (xright<0				) return FALSE;

	// Variante A: length2
/*	{
		const zVEC3& camPos	= cam->GetVob()->GetPositionWorld();
		zVEC2 camPosWS		= zVEC2(camPos[VX], camPos[VZ]);
		zREAL xCenter		= (bbox3D.maxs[VX]+bbox3D.mins[VX]) * 0.5F;
		zREAL zCenter		= (bbox3D.maxs[VZ]+bbox3D.mins[VZ]) * 0.5F;
		if (camPos[VX]<xCenter) { 
			if (camPos[VZ]<zCenter)	camMinZ= (zVEC2(bbox3D.mins.n[VX], bbox3D.mins.n[VZ])-camPosWS).Length2();
			else					camMinZ= (zVEC2(bbox3D.mins.n[VX], bbox3D.maxs.n[VZ])-camPosWS).Length2();
		} else {
			if (camPos[VZ]<zCenter)	camMinZ= (zVEC2(bbox3D.maxs.n[VX], bbox3D.mins.n[VZ])-camPosWS).Length2();
			else					camMinZ= (zVEC2(bbox3D.maxs.n[VX], bbox3D.maxs.n[VZ])-camPosWS).Length2();
		};
	};*/
	
	// Variante B: zDist
	{
		const zVEC3& camPos	= cam->GetVob()->GetPositionWorld();
		zREAL xCenter		= (bbox3D.maxs[VX]+bbox3D.mins[VX]) * 0.5F;
		zREAL zCenter		= (bbox3D.maxs[VZ]+bbox3D.mins[VZ]) * 0.5F;
		zVEC3 bboxCorner;
		if (camPos[VX]<xCenter) { 
			if (camPos[VZ]<zCenter)	bboxCorner= (zVEC3(bbox3D.mins.n[VX], bbox3D.maxs.n[VY], bbox3D.mins.n[VZ]));
			else					bboxCorner= (zVEC3(bbox3D.mins.n[VX], bbox3D.maxs.n[VY], bbox3D.maxs.n[VZ]));
		} else {
			if (camPos[VZ]<zCenter)	bboxCorner= (zVEC3(bbox3D.maxs.n[VX], bbox3D.maxs.n[VY], bbox3D.mins.n[VZ]));
			else					bboxCorner= (zVEC3(bbox3D.maxs.n[VX], bbox3D.maxs.n[VY], bbox3D.maxs.n[VZ]));
		};
		//camMinZ = (bboxCorner - camPos) * at;
		camMinZ = (bboxCorner - camPos) * cam->GetVob()->GetAtVectorWorld();
	};

	// z-Test
	if (horizonZ[xright				]>camMinZ) return TRUE;  
	if (horizonZ[xleft				]>camMinZ) return TRUE;  
	if (horizonZ[(xright+xleft) >> 1]>camMinZ) return TRUE;  
//	if (horizonZ[(xright+xleft) >> 1]>((camMinZ+camMaxZ)*0.5F)) return TRUE;  

	// y-Test
	i=xleft;  
	do {
		if (ymins<=horizonY[i]) return TRUE;  
		i++;
	} while (i<xright);

//	bbox3D.Draw();
//	DrawCamZ (xleft, xright, camMinZ);

	return FALSE;
};

/* ----------------------------------------------------------------------
	
    IsVisibleVob()	

	17.11.2000	[Moos]	
                auf neue Vertex-Klasse umgestellt

   ---------------------------------------------------------------------- */


static zBOOL IsVisibleVob	(zCVob *vob) 
{
#ifndef COMPILING_SPACER
	if ( (!vob->GetVisual() ) || (!vob->GetShowVisual()) || (vob->GetVisualAlpha()==0)) return FALSE;
	if ( !zCWorld::S_GetAmbientVobsEnabled() && vob->GetIsAmbient())					return FALSE;
#endif

	const zTBBox2D &box2D = vob->GetScreenBBox2D();
	zREAL			ymins = box2D.mins[VY];
	zREAL			xmins = box2D.mins[VX] - zCCamera::activeCam->vpData.xminFloat;
	zREAL			xmaxs = box2D.maxs[VX] - zCCamera::activeCam->vpData.xminFloat;

	if (ymins<=1)			ymins=1;
	if (ymins<horizonYMin)	return TRUE;

	int xleft	= zFloat2Int(xmins * HORI_PREC_MUL);
	int xright	= zFloat2Int(xmaxs * HORI_PREC_MUL + 0.5F);

	if (xleft <0				) xleft= 0;					else
	if (xleft >horizonXDim-1	) return FALSE; 
	if (xright>horizonXDim-1	) xright = horizonXDim-1;	else
	if (xright<0				) return FALSE;

	{
		zREAL camMinZ;
/*		const zTBBox3D& bbox3D	= vob->GetBBox3DWorld();
		const zVEC3& camPos		= zCCamera::activeCam->GetVob()->GetPositionWorld();
		zVEC2 camPosWS			= zVEC2(camPos[VX], camPos[VZ]);
		zREAL xCenter			= (bbox3D.maxs[VX]+bbox3D.mins[VX]) * 0.5F;
		zREAL zCenter			= (bbox3D.maxs[VZ]+bbox3D.mins[VZ]) * 0.5F;
		zVEC3 camAt3			= zCCamera::activeCam->GetVob()->GetAtVectorWorld();
		zVEC2 camAt				= zVEC2(camAt3[VX], camAt3[VZ]);
		camAt.Normalize();
		if (camPos[VX]<xCenter) { 
			if (camPos[VZ]<zCenter)	camMinZ= (zVEC2(bbox3D.mins.n[VX], bbox3D.mins.n[VZ])-camPosWS) * camAt;
			else					camMinZ= (zVEC2(bbox3D.mins.n[VX], bbox3D.maxs.n[VZ])-camPosWS) * camAt;
		} else {
			if (camPos[VZ]<zCenter)	camMinZ= (zVEC2(bbox3D.maxs.n[VX], bbox3D.mins.n[VZ])-camPosWS) * camAt;
			else					camMinZ= (zVEC2(bbox3D.maxs.n[VX], bbox3D.maxs.n[VZ])-camPosWS) * camAt;
		};
*/
		camMinZ = (vob->GetPositionWorld() - zCCamera::activeCam->GetVob()->GetPositionWorld()) * zCCamera::activeCam->GetVob()->GetAtVectorWorld();
//		camMinZ *= camMinZ;

		// z-Test
		if (horizonZ[xright				]>=camMinZ) return TRUE;  
		if (horizonZ[xleft				]>=camMinZ) return TRUE;  
		if (horizonZ[(xright+xleft) >> 1]>=camMinZ) return TRUE;  

/*		int j;
		j =xleft; 
		do {
			if (camMinZ<=horizonZ[j]) return TRUE;
			j++;
		} while (j<xright);
*/
	};

	// y-Test
	int j;
	j =xleft; 
	do {
		if (ymins<=horizonY[j]) return TRUE;
		j++;
	} while (j<xright);
	return FALSE;
};

static void ScanHorizon (zCPolygon* poly) 
{
#ifdef zBSP_DONT_CULL_HORIZON
	return;
#endif
	if (dontCull) return;

	if (!poly->IsOccluder()) return;

	enum { SCRX=0, SCRY=1, CAMZ=2 };
	zVEC3	vertList[32];
	int		numVert=poly->numClipVert;

	for (int n=0; n<poly->numClipVert; n++) {
        zCVertexTransform *vert = poly->clipVert[n]->VertexTransform();

		vertList[n].n[SCRX]	= vert->vertScrX;
		vertList[n].n[SCRY]	= vert->vertScrY;
		vertList[n].n[CAMZ]	= vert->vertCamSpace[VZ];
	};

	zREAL	min_x;
	int		min_vtx	= 0; 
	zREAL	max_x;
	int		max_vtx	= 0;
	min_x = max_x = vertList[0].n[SCRX];

	zREAL vertx;
    for (n=1; n<poly->numClipVert; n++) {
		vertx = vertList[n].n[SCRX];
        if(vertx < min_x) {
            min_x   = vertx;
            min_vtx = n;
        } else
        if(vertx > max_x) {
            max_x   = vertx;
            max_vtx = n;
        }
    }

	int j;
	int i=min_vtx;

	// zpos ermitteln
	// ACHTUNG: damit Vobs gut gecullt werden, reicht es nicht mehr aus, die zpos aus einem zufaelligen Vert zu holen
	zREAL zpos;
/*
//	zpos		= poly->clipVert[i]->vertCamSpace[VZ];   
	zVEC3 p1	= poly->clipVert[i]->position;							p1[VY]=0;
	zVEC3 p2	= zCCamera::activeCam->GetVob()->GetPositionWorld();	p2[VY]=0;
	zpos		= (p1-p2).Length2();   
*/
	{
		zpos = vertList[0][CAMZ];
		for(int n=1; n<numVert; n++) {
			zpos = zMax (zpos, vertList[n][CAMZ]);
//			zpos = zMax (zpos, poly->clipVert[n]->vertCamSpace.Length2());
		};
//		zpos = zpos*zpos;
	};

	// die oberen Kanten des Polys abscannen
	do {
		j = i-1;
		if (j<0) j = numVert-1;
 
		//
		if (horizonYMin>vertList[i][SCRY])			horizonYMin = vertList[i][SCRY];
// 		if (horizonZMax<poly->clipVert[i]->vertCamSpace[VZ])	horizonZMax = poly->clipVert[i]->vertCamSpace[VZ]; 

		// eine Linie in den Y-Buffer scannen
		zREAL delta = (vertList[j][SCRX] - vertList[i][SCRX]) * HORI_PREC_MUL;
		if (delta>0) {
			delta = (vertList[j][SCRY] - vertList[i][SCRY]) / delta;
			int		xend = zFloat2Int(vertList[j][SCRX]) >> HORI_PREC_SHIFT;
			int		xpos = zFloat2Int(vertList[i][SCRX]) >> HORI_PREC_SHIFT;
			zREAL	ypos = vertList[i][SCRY];
			do {
				if (xpos>=horizonXDim) break;
				if (xpos>=0)
				if (ypos<horizonY[xpos]) 
				{
					horizonY[xpos]	= ypos;
					horizonZ[xpos]	= zpos;
				};
				ypos += delta;
				xpos ++;
			} while (xpos<xend);
			
		};
		i = j;
	} while (i!=max_vtx);
};

static void RenderHorizon() {
	horizonXDim = zCCamera::activeCam->vpData.xdim / int (HORI_PREC_DIV);
	for (int i=0; i<horizonXDim; i++) {
		int x = i << HORI_PREC_SHIFT;
		zlineCache.Line (x, horizonY[i], x, horizonY[i]+2);
		int y = int((    (horizonZ[i]) / 60000.0F) * -480.0F + 480.0F);
//		int y = int((sqrt(horizonZ[i]) / 60000.0F) * -480.0F + 480.0F);
		zlineCache.Line (x, y, x, y+1, GFX_GREEN);
	};
	zlineCache.Line		(0, horizonYMin, 640, horizonYMin);		// [BENDLIN] 800x600, should be 800???
	zlineCache.Flush	(zCCamera::activeCam->targetView);
}; 



// ***************************************************************************************************************
//		BSP-SECTOR
// **********************


int						zCBspSector::s_sectorsRendered;
zBOOL					zCBspSector::s_startPointOutdoor;
zBOOL					zCBspSector::s_outdoorPortal;
zCArray<zCBspSector*>	zCBspSector::s_activeSectorList;
zCArray<zTBBox2D>		zCBspSector::s_activeOutdoorPortals;

int zCBspSector::CompareOutdoorPortalBBox2D ( const void *arg1, const void *arg2 ) 
{
	int p1 = s_activeOutdoorPortals[*((int*)arg1)].maxs[VY];
	int p2 = s_activeOutdoorPortals[*((int*)arg2)].maxs[VY];
	return p1-p2;
//	if (p1<p2)	return -1; else
//	if (p1>p2)	return +1; else
//				return  0;
};



void zCBspSector::InitHorizonByOutdoorPortals() 
{
//	InitHorizon();
//return;

	zCArray<int> portalList(s_activeOutdoorPortals.GetNum());
	portalList.MarkNumAllocUsed();
	for (int i=0; i<s_activeOutdoorPortals.GetNum(); i++)
		portalList[i] = i;

	qsort (portalList.GetArray(), portalList.GetNum(), sizeof(portalList[0]), CompareOutdoorPortalBBox2D);

	horizonXDim = zCCamera::activeCam->vpData.xdim / int(HORI_PREC_DIV);
	horizonYMin = zFloat2Int(zCCamera::activeCam->vpData.ymaxFloat);
	FillHorizon (0,zCCamera::activeCam->vpData.xdim,0);
	for (i=0; i<s_activeOutdoorPortals.GetNum(); i++)
	{
		const zTBBox2D& box = s_activeOutdoorPortals[portalList[i]];
		FillHorizon (box.mins[VX], box.maxs[VX], box.maxs[VY]);
	};
};

void zCBspSector::CalcCenterByPortals () {
	sectorCenter = zVEC3(0);
	for (int i=0; i<sectorPortals.GetNum(); i++) {
		sectorCenter += sectorPortals[i]->GetCenter();
	};
	sectorCenter /= zREAL(sectorPortals.GetNum());
};



zBOOL zCBspSector::HasManyBigPortals () const
{
	int num=0;
	for (int i=0; i<sectorPortals.GetNum(); i++) 
	{
		zCPolygon *portal = sectorPortals[i];
		if (portal->GetPortalType()>=zCPolygon::zPORTAL_TYPE_BIG) num++;
		if (num>=7) return TRUE;
	};
	return FALSE;
}



// ***********************************************************************************************************
//  PORTALS
// ****************

zCMaterial* zCPortal::portalDummyMaterial = 0;

void zCPortal::RemoveFromBsp() {
	zCCBspNode* cnode;
	cnode = GetFrontCBspNode(); if (cnode) cnode->RemovePoly (this);
	cnode = GetBackCBspNode (); if (cnode) cnode->RemovePoly (this);
};

zCPortal::zCPortal (const zTPlane& plane, zCMesh* containerMesh) 
{
// Create really big Portal-Poly from Plane ('QBSP.c')
	Init();

	if (portalDummyMaterial==0) portalDummyMaterial= zNEW(zCMaterial("Z_PORTALDUMMYMAT"));
	SetMaterial (portalDummyMaterial); 

	const zREAL BOGUS_RANGE= 30000.0F;			// 18000;
//	const zREAL BIG_SCALE	= 8192.0F;			// 8192;   cm !!
	const zREAL BIG_SCALE	= 10000.0F;			// 8192;   cm !!
	// FIXME: bei groesseren Werten als 100000 gibt es 'leafs w/o portals' wo eigentlich 
	//        welche sein sollten. Bei 8192 hingegen sind alle Portals da, doch die 
	//        bsp-node BBox3d haben manchmal illegalerweise werte bis 8192....
	int			i, x;
	zREAL		max, v;
	zPOINT3		org, vright, vup;
	
	// find the major axis
	max = -BOGUS_RANGE;
	x	= -1;
	for (i=0 ; i<3; i++) {
		v = zAbs(plane.normal.n[i]);
		if (v > max) {
			x   = i;
			max = v;
		}
	}
	if (x==-1) zERR_WARNING ("D: zBSP(zCPortal::CreateFromPlane): no axis found");
		
	vup = zPOINT3 (0,0,0);		// VectorCopy (vec3_origin, vup);
	switch (x) 	{
	case 0:
	case 1:
		vup[2] = 1;
		break;		
	case 2:
		vup[0] = 1;
		break;		
	}

	v		= vup * plane.normal;				// v = DotProduct (vup, p->normal);
	vup		= vup + (-v * plane.normal);		// VectorMA (vup, -v, p->normal, vup);, 
	vup.Normalize();							// VectorNormalize (vup);
	org		= plane.distance * plane.normal;	// VectorScale (p->normal, p->dist, org);
	vright	= vup ^ plane.normal;				// CrossProduct (vup, p->normal, vright);

	// project a really big	axis aligned box onto the plane
	// create 4 new vertices !!
	zCVertex* vert1 = zNEW(zCVertex);	//containerMesh->AddVertex (vert1);
	zCVertex* vert2 = zNEW(zCVertex); //containerMesh->AddVertex (vert2);
	zCVertex* vert3 = zNEW(zCVertex); //containerMesh->AddVertex (vert3);
	zCVertex* vert4 = zNEW(zCVertex); //containerMesh->AddVertex (vert4);
	
	vert1->position = org + (-vright + vup) * BIG_SCALE;
	vert2->position = org + ( vright + vup) * BIG_SCALE;
	vert3->position = org + ( vright - vup) * BIG_SCALE; 
	vert4->position = org + (-vright - vup) * BIG_SCALE;
	AllocVerts (4);
	SetVertex (0, vert4);
	SetVertex (1, vert3);
	SetVertex (2, vert2);
	SetVertex (3, vert1);
	
	// Plane eintragen (ist Plane konsistent mit der Vertex-Reihenfolge ???)
	polyPlane = plane;
};


void zCBspBase :: DescribeTree (int indent) {
	zSTRING s = "D: BSP: ";
	s = Spaces (indent*2);
	if (IsLeaf()) s = s + "- Leaf";
	else		  s = s + "- Node";
//	s += ", vobs: "+zSTRING(vobList.GetNumInList());
	if (IsNode()) {
		s+= ", numLeafs: "+zSTRING(((zCBspNode*)this)->numLeafs);  
	};
	if (IsLeaf()) {
		s+= ", leafVobs: "+zSTRING(((zCBspLeaf*)this)->leafVobList.GetNum()); 
		s+= ", leafLights: "+zSTRING(((zCBspLeaf*)this)->lightVobList.GetNum()); 
	};
//	if (front) s=s+ ", [front]";
//	if (back ) s=s+ " [back]";
//	s = s + ", "+plane.Print();
	zERR_MESSAGE (3, 0, s);

/*	s = "  " + Spaces (indent*2);
	s = s + "bbox: "+bbox3D.mins.GetString() + bbox3D.maxs.GetString();
	zERR_MESSAGE (s);*/

	if (IsNode()) {
		zCBspNode *node = (zCBspNode*)this;
		if (node->front) node->front->DescribeTree (indent+1);
		if (node->back ) node->back ->DescribeTree (indent+1);
	};
};


// ****************************************************************************
// Polygon
// ************

/*
	// Vertex-Ani, Welleneffekt

		vertCtr = polyNumVert-1; 
	do {
		zCVertex *actVert = (vertex[vertCtr]);
		if (material->GetMatGroup()==zMAT_GROUP_WATER) 
		{
			zPOINT3 pos = actVert->position;
			zREAL	t	= ( (pos[VX]+pos[VZ]) + ztimer.GetTotalTimeF()/500);
//			zREAL	t	= ( (pos[VX]+pos[VZ]) + ztimer.GetFrameTimeF()/500);
			pos[VY] -= 0.2F*(zSin(t));
			actVert->position = pos;
		};
	} while (vertCtr--);
*/
/*
	// Water-EnvMapping
	if (material->GetMatGroup()==zMAT_GROUP_WATER) 
	{
		zVEC2 texuv;
		zREAL radius;
		zVEC3 view, rv;
		for (int i=0; i<polyNumVert; i++) {
			// http://www.sgi.com/software/performer/brew/oceanenv.html
			view = vertex[i]->position - zCCamera::activeCamPos; 
			view.Normalize();
			// reflect view vector about normal 
			// a)
			rv= (( 2* ( view*feature[i]->vertNormal))*feature[i]->vertNormal) - view;  
			radius			= 0.29f * ( M_PI*.5f - asinf(rv[1]) ) / (M_PI * .5f); 
			texuv[0]		= rv[0];
			texuv[1]		= rv[2];
			texuv.Normalize();
			texuv			*= radius;

			// b)
			rv= (( 2* ( view*zVEC3(0,1,0)))*zVEC3(0,1,0)) - view;  
			texuv[0]		= rv[0];
			texuv[1]		= rv[2];
			feature[i]->texu= texuv[0] + 0.5F;
			feature[i]->texv= texuv[1] + 0.5F;

		};
	};
*/



/* ----------------------------------------------------------------------
	
    zCPolygon::RenderPoly()

	17.11.2000	[Moos]	
                Auf neue Vertex-Klassen umgestellt

   ---------------------------------------------------------------------- */

zBOOL zCPolygon::RenderPoly (const int clipFlags) 
{
	// ACHTUNG: Portals duerfen erst am Ende der Func rejected werden => sie muessen ja 
	//			transformiert & projeziert werden !!

	// Poly bereits in diesem Frame gemalt ?

	if (lastTimeDrawn==bspFrameCtr) return FALSE;

	// backface culling (in world(obj)Space)

	if (!IsPortal()) 
	{
		if (IsBackfacing()) 
		{
			lastTimeDrawn		= bspFrameCtr;
			flags.mustRelight   = TRUE;
			return FALSE;
		}
	};

	ApplyMorphing();

	//if (s_leafRelightPolys)
		LightClippedPoly	(actBspTree->worldRenderMode==zWLD_RENDER_MODE_VERT_LIGHT);			

	lastTimeDrawn = bspFrameCtr;

	const zBOOL hasTL = zrenderer->HasCapability(zRND_CAP_TNL) && zrenderMan.GetUseRendererTNL();

	if (hasTL)
	{
		if (!IsOccluder()) 
		{
			zrenderMan.AddPoly	(this);
			return TRUE;
		}
		// t&l & occluder: fast occluder version

		if (clipFlags>0) 
		{
			if (!ClipToFrustum_Occluder(clipFlags)) return FALSE; 
		} 
		else Unclip();
		
		// alle verts abgehen
		zREAL nearestZ	= 0;
		int   vertCtr	= numClipVert-1;
    
		zCVertex          *actVert;
		zCVertexTransform *trans=NULL;

		do 
		{
			actVert = (clipVert[vertCtr]);

			if (!actVert->IsTransformed()) 
			{
    			trans   = actVert->CreateVertexTransform();
				
				// Transform 
				trans->vertCamSpace= (zCCamera :: activeCam->camMatrix) * (actVert->position);

				// Project
				zCCamera::activeCam->Project		(trans);
				
			};
			if (!trans)	trans = actVert->VertexTransform();

			// far clipping plane ?
			// FIXME: hier das MINIMALE Z sammeln ! damit kann dann FarPlane & camLight getestet werden!
			nearestZ = zMin (nearestZ, trans->vertCamSpace.n[VZ]);

		} 
		while (vertCtr--);

		// put triangle in to-draw-list 
		if (nearestZ>=zCCamera::activeCam->GetFarClipZ()) return FALSE;

		if (!IsPortal()) 
		{ 
			zrenderMan.AddPoly			  (this);
			if (doScanHorizon) ScanHorizon(this);
		}; 
		return TRUE;

	};


	// hier alles ohne tl
	int vertCtr;

	// ACHTUNG: Wenn das Poly die FAR/NEAR Plane beruehrt, sind die "clipFlags>0" !! 
	//          Allerdings muss in diesem Fall NICHT exakt am Frustum geclippt werden, also =>UNCLIP !!

	if (clipFlags>0) 
	{
		if (!ClipToFrustum(clipFlags)) return FALSE; 
	} 
	else Unclip();

	// animated Texture-Mapping (muss vor clipping, wegen uv-Repraesentation)
	material->ApplyTexAniMapping (this);
	
	// alle verts abgehen
	zREAL nearestZ	= 0;
	vertCtr			= numClipVert-1;
    
    zCVertex          *actVert;
    zCVertexTransform *trans=NULL;

	do {
		actVert = (clipVert[vertCtr]);

		if (!actVert->IsTransformed()) {
    		trans   = actVert->CreateVertexTransform();
			
			// Transform 
			trans->vertCamSpace= (zCCamera :: activeCam->camMatrix) * (actVert->position);

			// Project
#ifdef _DEBUG
			if (trans->vertCamSpace.n[VZ] != 0) 
#endif
			zCCamera::activeCam->Project		(trans);
			
		};
		if (!trans)
			trans = actVert->VertexTransform();

		// far clipping plane ?
		// FIXME: hier das MINIMALE Z sammeln ! damit kann dann FarPlane & camLight getestet werden!
		nearestZ = zMin (nearestZ, trans->vertCamSpace.n[VZ]);

	} while (vertCtr--);

	// put triangle in to-draw-list 
	if (nearestZ>=zCCamera::activeCam->GetFarClipZ()) return FALSE;

	if (!IsPortal()) 
	{ 
		zrenderMan.AddPoly			  (this);
		//
		if (doScanHorizon) ScanHorizon	(this);

	}; 
	return TRUE;
};

static inline void CreateRandomSparkle(const zREAL dh, const zVEC3 &pos, const zCMaterial *mat)
{
	zBOOL underWater = zCSkyControler::GetActiveSkyControler()->GetUnderwaterFX();
	if      ( underWater )
	{
		if (dh>-0.5f)											return; 
		if (zRandF()>0.1f)										return;
		if ((zCCamera::activeCamPos-pos).LengthApprox()>800)	return;
	}
	else if ( dh<0.995f || mat->GetWaveMaxAmplitude()<15 || zRandF()>0.2f ) return;

	zCVob			*pfxVob		= zNEW(zCVob);
	zCParticleFX	*pfx		= zNEW(zCParticleFX);
	pfxVob->SetDontWriteIntoArchive	(TRUE);				// Effekt Vob, nicht ins Archive schreiben!
	pfxVob->SetCollDet				(FALSE);
	pfxVob->SetPositionWorld		(pos);
	zCCamera::activeCam->GetVob()->GetHomeWorld()->AddVobRelease(pfxVob);
	if (underWater) pfx->SetRenderUnderwaterOnly(TRUE);		

	pfxVob->SetVisual				(pfx);
	pfxVob->SetZBias				(1);				// immer auf dem wasser, niemals unterhalb (was ist unter wasser ?)

	if (!pfx->SetAndStartEmitter	(underWater ? "PFX_WATERLIGHT" : "PFX_WATERSPLASH_SEA", TRUE))
	{
		pfxVob->RemoveVobFromWorld();
	}

	zRELEASE (pfx);
};

void zCPolygon::ApplyMorphing()
{

#ifdef E3_WATER
	if (material->GetMatGroup() == zMAT_GROUP_WATER)
	{ 
		material->SetWaveAniMode		(zWAVEANI_GROUND_AMBIENT);
	}
#endif
#ifdef DEBUG_WAVES
	if (material->GetMatGroup() == zMAT_GROUP_WATER)
	{ 
		material->SetWaveAniMode		(zWAVEANI_GROUND);
		material->SetWaveGridSize		(s_grid);
		material->SetWaveMaxAmplitude	(s_amp);
		material->SetWaveAniSpeed		(zTFFT_SLOW);
	}
#endif

	if (zCWorld::GetWaveAnisEnabled())
	if (material->GetWaveAniMode() != zWAVEANI_NONE)
	{

#if 0
		// disabled, da es eh keiner braucht.
		if (material->GetWaveAniMode()==zWAVEANI_GROUND || material->GetWaveAniMode()==zWAVEANI_WALL || material->GetWaveAniMode()==zWAVEANI_WIND)
		{
			// die polyplane normale/distanz muss neu berechnet werden, damit
			// alle traceraytests im folgenden frame korrekt berechnet werden
			// beinhaltet: wasserkringel, regentropfen, character positionsveraenderungen, etc.
			static zSPolySavedValues savedValues;
			savedValues.poly = this;
			savedValues.plane= GetPlane();
			morphedPolysSavedValuesList.Insert(savedValues);
			CalcNormalApprox();
		}
#endif

		static zSVertexSavedValues savedVert;
		// vertices werden gemorphed.
		
		// alle verts abgehen
		int vertCtr			= polyNumVert-1;

		if (material->GetWaveAniMode()<zWAVEANI_WALL_AMBIENT) 
		{
			// höhenmässiges verschieben
			zCVertex          *actVert;
			do {
				actVert = (vertex[vertCtr]);
				savedVert.vert = actVert;

				if (!morphedVerticesList_Height.IsInList(savedVert)) 
				{
					savedVert.offset = actVert->position[VY];
					morphedVerticesList_Height	    .InsertSort(savedVert);
					zREAL dh = 	zCFFT::S_CalcWave2D(actVert->position[VX], 
															actVert->position[VZ],
															material->GetWaveGridSize(), 
															material->GetWaveAniSpeed()
															);
					if (dh<-1) dh = -1;
					if (dh>+1) dh = +1;

					actVert->position[VY] += dh * material->GetWaveMaxAmplitude();

					if (material->GetMatGroup()==zMAT_GROUP_WATER)
					{
						//material->GSetAlphaBlendFunc(zRND_ALPHA_FUNC_ADD);
						static zSFeatureSavedValues savedFeat;

						zCVertFeature *actFeat = (feature[vertCtr]);
						savedFeat.feat		   = actFeat;

						if (!morphedFeatureList.IsInList(savedFeat))
						{
							CreateRandomSparkle(dh, actVert->position, material);
							
							savedFeat.color		= actFeat->lightStat;
							//savedFeat.mapping	= zVEC2(actFeat->texu,actFeat->texv);
							
							int r = savedFeat.color.GetRedByte()   + (dh*40);	  zClamp(r, 20,255);
							int g = savedFeat.color.GetGreenByte() + (dh*40);	  zClamp(g, 20,255);
							int b = savedFeat.color.GetBlueByte()  + (dh*80);	  zClamp(b, 50,255);
							//int a = savedFeat.color.GetAlphaByte() + (dh*150);	  zClamp(a, 0,255);


							actFeat->lightStat.SetRGB(r,g,b);
														
						//	actFeat->texu += dh*0.01f;
						//	actFeat->texv += dh*0.01f;
							
							morphedFeatureList.InsertSort(savedFeat);
						}
					}
				}
			} 
			while (vertCtr--);
		}
		else
		{
			// pseudo 3d verschiebung
			zCVertex          *actVert;
			do {
				actVert = (vertex[vertCtr]);
				savedVert.vert = actVert;

				if (!morphedVerticesList_Wall.IsInList(savedVert))   
				{				
					zREAL d = zCFFT::S_CalcWave2D(actVert->position[VY], 
											actVert->position[VZ],
											material->GetWaveGridSize(),
											material->GetWaveAniSpeed()
										  );
					if (d<-1) d = -1;
					if (d>+1) d = +1;

					savedVert.offset = material->GetWaveMaxAmplitude() * d;
						
					morphedVerticesList_Wall.InsertSort(savedVert);

					actVert->position[VX] += savedVert.offset;
					actVert->position[VZ] += savedVert.offset;
				}
			} 
			while (vertCtr--);
		}
	}
}


#pragma optimize( "a", on )


void zCCFASTCALL zCPolygon::LightClippedPoly (const zBOOL noStaticLightmaps) 
{
	// FIXME: was is mit cloudShadows ???	
	// FIXME: es gibt noch eine schnellere variante von lightclippedpoly, 
	// die letzten drei bedingungen müssen nicht für jedes poly getestet werden

#ifndef COMPILING_SPACER
	if (!flags.mustRelight)
	{
		if ( (this->lastTimeDrawn==bspFrameCtr-1)						   &&			// war schon in der letzten szene gerendert
			 (this->GetNoLightNear())									   &&			// wird nicht von dyn. lichtern in der nähe beleuchtet
			 (!zCSkyControler::GetActiveSkyControler()->GetColorChanged()) &&			// die himmelsfarbe hat sich nicht geändert
			 (s_leafMovingLights.GetNum()==0) 							   &&			// es befinden sich keine bewegenden lichter im sektor
			 (zCCamera::activeCam->GetCamLightRange()<50))				  
		{
			return;
		}
	}
	else flags.mustRelight = FALSE;
#endif


	//if ((bspFrameCtr&2)!=0) return;				// bringt nicht viel (1fps in newworld_city, wo die meisten lichter sind)
	
	const int lightNumVert=polyNumVert;
	zCVertex		**lightVertex		= vertex;
	zCVertFeature	**lightFeature		= feature;

	// Indoor	:	lightDyn= lightStat
	// Outdoor	:	lightDyn= Daylight/Cloudshadow
	// + dynLight
	// + camLight
	zCOLOR	*polyLightCLUT	= zCSkyControler::GetActiveSkyControler()->polyLightCLUTPtr;

	if (polyLightCLUT)
	{
		zREAL	cloudShadowScale= zCSkyControler::GetActiveSkyControler()->cloudShadowScale;
		// Outdoor / CLUT vorhanden
		// Wolken wirken sich nicht auf Sektor-Polys aus
		if (material->GetIgnoreSunLight())
		{
			static zCOLOR fullBrightColor(200,200,200,255);
			for (int j=0; j<lightNumVert; j++)	lightFeature[j]->lightDyn=fullBrightColor;
		} 
		else if ((cloudShadowScale<=0) || (GetSectorFlag())) 
		{
			if ((GetLightmap()==0) || (noStaticLightmaps)) 
			{
				// Outdoor polys
				int j=0;
				do 
				{
					lightFeature[j]->lightDyn = polyLightCLUT[lightFeature[j]->lightStat.dword&255];
					++j;
				} 
				while (j<lightNumVert);
			} 
			else 
			{
				// outdoor-sektor polys
				//static zCOLOR resetColor(0,0,0,255);
				for (int j=0; j<lightNumVert; j++)		
				{
					if (lightFeature[j]->lightStat.GetAlphaByte()!=99) 
						lightFeature[j]->lightDyn=lightFeature[j]->lightStat;
					else
					{
						lightFeature[j]->lightDyn = polyLightCLUT[lightFeature[j]->lightStat.dword&255];
						lightFeature[j]->lightDyn.SetAlphaByte(0);
					}
				}
					
			};
		}
		else 
		{

			zREAL	pubs = ztimer.GetTotalTimeF()/2000;
			int		res; 
			for (int i=0; i<lightNumVert; i++) 
			{ 
				zCVertFeature*	actFeat = lightFeature[i]; 

				// dynamischer Wolken-Schatten
				const zPOINT3& pos		= lightVertex[i]->position;
				zREAL	t				= ( ((pos[VZ])*-0.0021F) + (pos[VX]*-0.001f) + pubs);
				zREAL scale				= 1.0F - cloudShadowScale*(0.80F * 0.5F*(zSinApprox(t)+1.0F));					// 0.3F .. 1.0F
				res						= ((int(actFeat->lightStat.GetRedByte())) * zFloat2Int(scale*255.0F)) >> 8;
				actFeat->lightDyn		= polyLightCLUT[res];
			};
		};
	} 
	else 
	{
		// Indoor
		if ((GetLightmap()==0) || (noStaticLightmaps)) 
		{
			for (int j=0; j<lightNumVert; j++)		lightFeature[j]->lightDyn = lightFeature[j]->lightStat;
		} else 
		{
			for (int j=0; j<lightNumVert; j++)		lightFeature[j]->lightDyn.Reset(); 
		};
	};


	if (IsPortal()) return; 

	for (int lightNr=0; lightNr<s_leafDynLights.GetNumInList(); lightNr++) 
	{
		if (!s_leafDynLights[lightNr]->GetPolyIsAffected(this)) continue;

		const zCVobLight	*light			= s_leafDynLights[lightNr];
		const zREAL			playerLIInv		= light->GetRangeInv();
		const int			lightR			= (int)light->GetColorR();
		const int			lightG			= (int)light->GetColorG();
		const int			lightB			= (int)light->GetColorB();
		const zPOINT3&		lightSourcePos	= light->GetPositionWorld();

		int actNumVert = lightNumVert-1;
		do {
			zCVertex		*actVert = lightVertex[actNumVert]; 
			zCVertFeature	*actFeat = lightFeature[actNumVert]; 

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
			if (zIsGreaterPositive(len, light->GetRange())) goto dontLightVert;

//				if (len>light->GetRange()) { r = g = b = 255; goto dontLightVert; };
			dist = 1-(len * playerLIInv);

			////////////////////////
			// 2. Diffuse         //
			////////////////////////
			// angle: face/light

			// dot<0 => poly ist lq abgewandt
			// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
			dot = -((view * actFeat->vertNormal) / len);

			if (dot<0) goto dontLightVert;
			i = dot*dist;			

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

	for (lightNr=0; lightNr<s_leafMovingLights.GetNumInList(); lightNr++) 
	{
		if (!s_leafMovingLights[lightNr]->GetPolyIsAffected(this)) continue;

		const zCVobLight	*light			= s_leafMovingLights[lightNr];
		const zREAL			playerLIInv		= light->GetRangeInv();
		const int			lightR			= (int)light->GetColorR();
		const int			lightG			= (int)light->GetColorG();
		const int			lightB			= (int)light->GetColorB();
		const zPOINT3&		lightSourcePos	= light->GetPositionWorld();

		int actNumVert = lightNumVert-1;
		do {
			zCVertex		*actVert = lightVertex[actNumVert]; 
			zCVertFeature	*actFeat = lightFeature[actNumVert]; 

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
			if (zIsGreaterPositive(len,light->GetRange())) goto dontLightVert2;
//				if (len>light->GetRange()) { r = g = b = 255; goto dontLightVert; };
			dist = 1-(len * playerLIInv);

			////////////////////////
			// 2. Diffuse         //
			////////////////////////
			// angle: face/light

			// dot<0 => poly ist lq abgewandt
			// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
			dot = -((view * actFeat->vertNormal) / len);

			if (dot<0) goto dontLightVert2;
			i = dot*dist;			

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
dontLightVert2:;
  		} while (actNumVert--);
	};

	// Camlight
	if (zCCamera::activeCam->GetCamLightRange()>50)
	{
		const zPOINT3	camPos	= zCCamera::activeCam->GetVob()->GetPositionWorld();
		const zREAL		range2	= zCCamera::activeCam->GetCamLightRange()*zCCamera::activeCam->GetCamLightRange();
		int actNumVert	= lightNumVert-1;
		do {
			zCVertex		*actVert = lightVertex[actNumVert]; 
			zCVertFeature	*actFeat = lightFeature[actNumVert]; 
			
			zVEC3	view	= (actVert->position-camPos);
			zREAL	dist2	= view.Length2();
			if (dist2>range2) continue;
			zREAL	i		= zREAL(1.0F) - (dist2 / range2);

			//
			zREAL	len		= view.LengthApprox();
			zREAL	dot		= -((view * actFeat->vertNormal) / len);
			if (dot<0) continue;
			i *= dot;

			int	intens = zFloat2Int(i*255.0F);
			int r = (int)actFeat->lightDyn.r + (intens); if (r>255) r=255;
			int g = (int)actFeat->lightDyn.g + (intens); if (g>255) g=255;
			int b = (int)actFeat->lightDyn.b + (intens); if (b>255) b=255;

			actFeat->lightDyn.r = r;
			actFeat->lightDyn.g = g;
			actFeat->lightDyn.b = b;
  		} while (actNumVert--);
	};
}; 

#pragma optimize( "a", off )



/* ----------------------------------------------------------------------
	
    zCPolygon::TransformProjectLight()	

	17.11.2000	[Moos]	
                Auf neue Vertex-Klassen umgestellt

   ---------------------------------------------------------------------- */

zBOOL zCPolygon::TransformProjectLight () {
	// assert: backface & FrustumClipping bereits erledigt

	// alle verts abgehen
	int outside	= 0;
	int	vertCtr = numClipVert-1;

    zCVertex          *actVert;
    zCVertexTransform *trans=NULL;
	do {
		actVert = (clipVert[vertCtr]);

		if (!actVert->IsTransformed()) {
            trans   = actVert->GetVertexTransform();

			// Transform 
			trans->vertCamSpace= (zCCamera :: activeCam->camMatrix) * (actVert->position);
//			trans->transformed = bspFrameCtr;

			// FIXME: hier noetig?
//			actVert->vertCamSpaceZInv = zREAL(1.0F) / actVert->vertCamSpace[VZ];

			// Project
			zCCamera::activeCam->ProjectClamp (trans);
//			zCWorld ::s_vertsTransformed++;
		};

        if (!trans)
            trans = actVert->VertexTransform();

		// far clipping plane ?
		if (trans->vertCamSpace.n[VZ]>=zCCamera::activeCam->GetFarClipZ()) {
			outside++;
		};  
	} while (vertCtr--);
	
	if (outside!=numClipVert) {
		LightDynCamSpace (zCCamera::activeCamPos, playerLightInt);		// ZAK  
		return TRUE;
	};
	return FALSE;
};

zBOOL zCPolygon::TransformProject() 
{
	// assert: backface & FrustumClipping bereits erledigt
	// assert: backface & FrustumClipping bereits erledigt

	// alle verts abgehen

	//return TransformProjectLight();

	int outside	= 0;
	int	vertCtr = numClipVert-1;

    zCVertex          *actVert;
    zCVertexTransform *trans=NULL;
	do {
		actVert = (clipVert[vertCtr]);

		if (!actVert->IsTransformed()) {
            trans   = actVert->GetVertexTransform();

			// Transform 
			trans->vertCamSpace= (zCCamera :: activeCam->camMatrix) * (actVert->position);
//			trans->transformed = bspFrameCtr;

			// FIXME: hier noetig?
//			actVert->vertCamSpaceZInv = zREAL(1.0F) / actVert->vertCamSpace[VZ];

			// Project
			zCCamera::activeCam->ProjectClamp (trans);
//			zCWorld ::s_vertsTransformed++;
		};

        if (!trans)
            trans = actVert->VertexTransform();

		// far clipping plane ?
		if (trans->vertCamSpace.n[VZ]>=zCCamera::activeCam->GetFarClipZ()) {
			outside++;
		};  
	} while (vertCtr--);

	return (outside!=numClipVert);

}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     RENDER - BSP
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

zBOOL		zCBspTree::s_showPortals=FALSE;
zBOOL		zCBspTree::s_renderAllPortals		= FALSE;

zCBspTree::zCBspTree() 
{
	InitTree();

};

zCBspTree::~zCBspTree() {
	DisposeTree();
	delete[] leafList;	leafList=0;			// loescht ggfs. das "Default" Leaf, das im InitTree() erzeugt worden ist 
	bspRoot=0;
};
							
void zCBspTree::InitTree() 
{
	numNodes			= 0;
	numLeafs			= 0;
	numPolys			= 0;
	nodeList			= 0;
	leafList			= zNEW(zCBspLeaf) [1];	// es muss immer mind. 1 Leaf vorhanden sein, in dem z.B. Vobs abgelegt werden
	treePolyList		= 0;
	mesh				= 0;
	masterFrameCtr		= 0;
	actPolyPtr			= 0;
	actNodePtr			= 0;
	actLeafPtr			= 0;
	bspRoot				= &(leafList[0]);		// referenziert nur, besitzt nicht
	bspRoot->bbox3D.SetMaximumBox();
	compiled			= FALSE;
	drawVobBBox3D		= FALSE;
	vobFarClipZ			= 0;
	vobFarPlaneSignbits	= 0;
	leafsRendered		= 0;
	vobsRendered		= 0;
						
//	worldRenderMode		= zWLD_RENDER_MODE_VERT_LIGHT;
	worldRenderMode		= zWLD_RENDER_MODE_LIGHTMAPS;
	SetRenderedFirstTime(TRUE);
	SetBspTreeMode		(zBSP_MODE_INDOOR);
	
	renderVobList.EmptyList		();
	renderLightList.EmptyList	();
};

void zCBspTree::DisposeTree() 
{

	// Im Mesh/Poly/Material alle Referenzen auf diesen BspTree loeschen

	if (mesh)
	{
		for (int i=0; i<mesh->numPoly; i++) {
			mesh->SharePoly(i)->GetMaterial()->SetBspSectorBack	(0);	// Die Sektoren selbst werden im folgenden geloescht..
			mesh->SharePoly(i)->GetMaterial()->SetBspSectorFront	(0);
		};
	};

	// 
	portalList.EmptyList();

	//
	zRELEASE (mesh);

	//
	delete[] nodeList;		nodeList=0;				// Tree muss also nicht rekursiv deleted werden
	delete[] leafList;		leafList=0;
	delete[] treePolyList;	treePolyList=0;
	bspRoot	= 0;

	//
	for (int i=0; i<sectorList.GetNum(); i++)
		delete sectorList[i];
	sectorList.DeleteList();

    // [Moos] lösche die Dinger
    zCRndAlphaSortObject_Vob::ClearList();

	// "frischen" Zustand herstellen via Default-Inits
	InitTree();

	// Release spatial database
	zCRayTurboAdmin::GetInstance().ReleaseSpatialDatabase();
};



zCBspBase* zCBspTree::BuildRecursive (zCCBspNode *cnode) 
{
	// !! der letzte Node ist immer der parent !!
	zCBspNode *parent;
	if (actNodePtr==nodeList) parent=0;		// ?? richtig ??
	else parent = actNodePtr-1;

	if (cnode->IsLeaf()) 
	{
		// leaf
		zCBspLeaf *leaf = actLeafPtr;
		leaf->bbox3D	= cnode->bbox3D;
		leaf->parent	= parent;
		// polys eintragen, falls vorhanden
		// VERSION: leaf-bsp, Quake-Style
		if (cnode->polyList.GetNumInList()>0)
		{
			leaf->numPolys			= cnode->polyList.GetNumInList();
			leaf->polyList	= actPolyPtr;
			zTPolyNode *polyNode	= cnode->polyList.Get(0);
			while (polyNode!=0) 
			{
				*actPolyPtr	= polyNode->poly;
				// extra-Behandlung für Portal => Connections übertragen
				if (polyNode->poly==0)
				{
					zERR_WARNING ("D: zBSP(zCBspTree::BuildRecursive): Illegal Poly in List !"); 
				}
				else

/*				if ((GetBspTreeMode()==zBSP_MODE_INDOOR) && (polyNode->poly->IsPortal())) { 
					zCPortal *portal = (zCPortal*)polyNode->poly;
					if (portal->GetFrontCBspNode()==cnode) portal->SetFrontBspNode ((zCBspNode*)leaf); else
					if (portal->GetBackCBspNode ()==cnode) portal->SetBackBspNode  ((zCBspNode*)leaf); else
						zERR_WARNING ("D: zBSP(zCBspTree::BuildRecursive): Illegal Portal Connection !");
				} else {
//					if (!polyNode->marked) 
//						zERR_WARNING ("D: zBSP(zCBspTree::BuildRecursive): Unmarked Poly in Leaf !");
				};*/
				polyNode	= polyNode->next;
				actPolyPtr++;
			};
		} else {
			// Leaf without polys
		};

		actLeafPtr++;
		return leaf;
	} else 
	{
		// node
		zCBspNode *node			= actNodePtr;
		node->plane				= cnode->plane;
		node->bbox3D			= cnode->bbox3D;
		node->parent			= parent;
		node->CalcPlaneSignbits (this);

		actNodePtr++;

		// letztes Leaf merken fuer leafList
		zCBspLeaf *lastLeaf = actLeafPtr;

		// recurse
		if (cnode->front) node->front	= BuildRecursive (cnode->front);
		if (cnode->back ) node->back	= BuildRecursive (cnode->back );

		// leafList-Info eintragen..
		node->leafList	= lastLeaf;
		node->numLeafs	= int((actLeafPtr - lastLeaf));
//		zERR_MESSAGE (zSTRING(node->numLeafs));

		// polys-info eintragen, da jetzt die Söhne alle korrekt initialisiert
		if (GetBspTreeMode()==zBSP_MODE_OUTDOOR) {
			// outdoor/LOD
			if (cnode->polyList.GetNumInList()>0) {
				node->numPolys			= cnode->polyList.GetNumInList();
				node->polyList	= actPolyPtr;
				zTPolyNode *polyNode	= cnode->polyList.Get(0);
				while (polyNode!=0) {
					*actPolyPtr	= polyNode->poly;
					polyNode	= polyNode->next;
					actPolyPtr++;
				};
			} else {
				node->numPolys			= 0;
				node->polyList	= 0;
			};
		} else {
			// VERSION: leaf-bsp, Quake-Style
			if (node->front) node->polyList	= node->front->polyList; else
			if (node->back ) node->polyList	= node->back ->polyList;
			int polySum = 0;
			if (node->front) polySum += node->front->numPolys;
			if (node->back ) polySum += node->back ->numPolys;
			node->numPolys = polySum;
		};
		return node;
	};
};

void zCBspTree::Build (zCCBspTree* ctree) 
{
	// FIXME: wird das initiale dummy-bspRoot auch richtig geloescht ???

	zERR_MESSAGE(3, 0, "D: RBSP: Building RENDER-BSP from CONSTR-BSP ...");
	zERR_ASSERT	(ctree!=0);
	zERR_ASSERT	(!compiled);

	// sonstiges kopieren
	bspTreeMode = ctree->GetBspTreeMode();

	//
	compiled			= TRUE;	 
	zERR_ASSERT			(bspRoot->IsLeaf());
	zCBspLeaf* oldTree	= (zCBspLeaf*)(bspRoot);	// "zCBspLeaf" ist hier wichtig (nicht zCBspBase!)
	
	// Poly/Vert-Container
	mesh		= (zCMesh*)(ctree->mesh->AddRef());

	// Nodes erzeugen
	numNodes	= ctree->CountNodes();
	nodeList	= zNEW(zCBspNode) [numNodes];
	actNodePtr	= nodeList;

	// Leafs erzeugen
	numLeafs	= ctree->CountLeafs();
	leafList	= zNEW(zCBspLeaf) [numLeafs];
	actLeafPtr	= leafList;

	// PolyList erzeugen
	// Achtung: mesh->numPolys != ctree->numPolys, weil Polys mehrfach vorkommen können !
	numPolys	= ctree->CountPolys();
	treePolyList= zNEW(zCPolygon*) [numPolys];
	actPolyPtr	= treePolyList;

	// ctree rekursiv abgehen und dabei nodes/leafs & polys/meshes/bsps eintragen
	actCBspTree = ctree; 
	bspRoot		= BuildRecursive (&(ctree->bspRoot));

	// Poly/Vert-Container
//	ctree->mesh->Release();
//	ctree->mesh = 0;

	// Vobs aus dem alten Tree in den neuen übertragen
	// (Vobs muessen unbed. sauber aus dem alten Tree entfernt werden um keine toten Refs zu behalten!)
	// (hmm.. koennte man nicht evtl. die Liste der Vobs _vor_ dem BuildRecursive() sammeln und dann hier nur nich in den neuen Tree einfuegen?)
	{
		zCArray<zCVob*> oldVobList;
		oldTree->CollectVobsSubtree		(oldVobList);		// sammelt keine lights..
		oldTree->CollectLightVobsSubtree(oldVobList);
		for (int i=0; i<oldVobList.GetNum(); i++) {
			oldTree->RemoveVobFromLeafs	(oldVobList[i]);	// wichtig!
			this->AddVob				(oldVobList[i]);
		};
	};

	// oldTree ist an dieser Stelle gleich bspRoot
	// Da diese Methode nur aufgerufen werden kann, wenn der Tree noch "uncompiled" ist, gilt an dieser Stelle:
	// nodeList==0; leafList==zNEW(zCBspLeaf)[1]; bspRoot==leafList[0];
	// die bspRoot/oldTree sollte demnache mit einem "delete[]" geloescht werden.
	delete[] oldTree; oldTree=0;

	// Sektoren bauen ?
	if (GetBspTreeMode()==zBSP_MODE_OUTDOOR) {
		CreateBspSectors2	(ctree); 
		MarkOccluderPolys	();
	};

	OptimizeLight(); 

	// Polys sortieren
	bspRoot->SortNodePolys (this);

	//
	zERR_MESSAGE (3, 0, "D: RBSP: ... Finished Building RENDER-BSP.");
};

void zCBspTree::OptimizeLight() 
{
	zERR_MESSAGE(5,0,"C: BSP: optimizing lights");
	int numPolyLit = 0;
	int j = 0;

	for (int i=0; i<numLeafs; i++)
	{
		zCBspLeaf *leaf = &(leafList[i]);

		for (int p=0; p<leaf->GetNumPolys(); p++)
		{
			zCPolygon *nextPoly = leaf->GetPolyList()[p];

			zBOOL tooFar = TRUE;

			if (nextPoly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER && nextPoly->GetMaterial()->GetWaveAniMode()!=zWAVEANI_NONE) 
			{
				tooFar = FALSE;
				goto dontOptimizePoly;
			}

			for (j=0; j<leaf->lightVobList.GetNum(); j++) 
			{
				zCVobLight *light = leaf->lightVobList[j];
				if (light->GetIsStatic()) continue;
				if (light->GetCanMove())  continue;
				
				for (int v=0; v<nextPoly->polyNumVert; v++)
				{
					if ((nextPoly->vertex[v]->position-light->GetPositionWorld()).Length()<light->GetRange())
					{
						// dieses licht wird das poly beleuchten, also raus hier
						tooFar = FALSE;
						goto dontOptimizePoly;
					}
				}
			}
dontOptimizePoly:
			nextPoly->SetNoLightNear(tooFar);
			if (!tooFar) numPolyLit++;
		}

	}
	zERR_MESSAGE(5,0,"C: BSP: optimizing lights done. polys lit: " + zSTRING(numPolyLit) + " of total " + zSTRING(mesh->numPoly) + " polys");
};


int zCBspBase::CountNodes () {
	if (IsLeaf()) return 1;
	zCBspNode *node = (zCBspNode*)this;
	int a=0;
	if (node->front) a = node->front->CountNodes();
	if (node->back ) a+= node->back ->CountNodes();
//	return a+1;
	return a;
};

void zCBspTree::UpdateVertexDependencies (zCVertex *vert)
{
	if (!vert)	return;

	// alle Normalen von Polys updaten, die diesen Vertex benutzen

	zCPolygon**	foundPolyList;
	int			foundPolyNum;
	zTBBox3D	box;
	box.Init();
	box.AddPoint (vert->position-zVEC3(1,1,1));
	box.AddPoint (vert->position+zVEC3(1,1,1));
	zBOOL b = GetRoot()->CollectPolysInBBox3D (box, foundPolyList, foundPolyNum);
	if (b) 
	{
		for (int i=0; i<foundPolyNum; i++)
		{
			foundPolyList[i]->CalcNormal();
		};
	};
};

zBOOL zCBspTree::CollectPolysInBBox3DAngle(const zTBBox3D&	testbbox3D, 
										   const zVEC3&		axis, 
										   const zREAL		angleMinDeg, 
										   const zREAL		angleMaxDeg, 
										   zCPolygon**&		foundPolyList, 
										   int&				foundPolyNum) const
{
	if (!GetRoot()->CollectPolysInBBox3D (testbbox3D, foundPolyList, foundPolyNum)) return FALSE;
	
	// Polys mit groesserem Winkel rausfiltern
	zREAL	angleMinRad	= Alg_Deg2Rad (angleMinDeg);
	zREAL	angleMaxRad	= Alg_Deg2Rad (angleMaxDeg);
	zVEC3	axisNormal	= axis;
	axisNormal.Normalize();
	for (int i=0; i<foundPolyNum; i++)
	{
		zCPolygon	*poly	= foundPolyList[i];
		zREAL		angle	= Alg_AngleUnitRad (poly->GetNormal(), axisNormal);
		if (zNotInRange (angle, angleMinRad, angleMaxRad)) {
			foundPolyList[i] = foundPolyList[--foundPolyNum];
			i--;
		};
	};
	return (foundPolyNum>0);
};

// **********
// Rendern 
// **********

void zCBspTree::RenderLightList () 
{
	for (int i=0; i<renderLightList.GetNum(); i++) 
	{
		zCVobLight *light = renderLightList[i];

		// Light-Animation
		light->DoAnimation();

		// Lensflare-Effekte rendern
		zCLensFlareFX* lensFlareFX = light->GetLensFlareFX();
		if (lensFlareFX)
			lensFlareFX->RenderLensFlares(light);

  		if (zCVobLight::GetRenderLightVisuals())
			renderVobList.Insert (light);
	};
};

// =========================================================================================================

static int CompareVobsByVisual(const void *arg1, const void *arg2) {
	const zCVisual* v1 = (*((zCVob**)arg1))->GetVisual();	const zDWORD	p1 = v1 ? v1->GetRenderSortKey() : 0;
	const zCVisual* v2 = (*((zCVob**)arg2))->GetVisual();	const zDWORD	p2 = v2 ? v2->GetRenderSortKey() : 0;
//	const zCVisual* p1 = (*((zCVob**)arg1))->GetVisual();
//	const zCVisual* p2 = (*((zCVob**)arg2))->GetVisual();
	return p1-p2;
};

// =========================================================================================================

void zCBspTree::RenderVobList () 
{
	// ASSERT: zCCamera::activeCam->Activate();
 
	// Alpha-Vobs rausfiltern und wegpacken
	zCRndAlphaSortObject_Vob::ResetFreeList();
	const zPOINT3 camPos = zCCamera::activeCam->GetVob()->GetPositionWorld();
	for (int i=0; i<renderVobList.GetNum(); i++)
	{
		zCVob		*vob			= renderVobList[i];

		// visual->RendersVertexBufferBased()
		if ((vob->GetVisual()) && (vob->GetShowVisual()) &&
		    (vob->GetVisual()->GetClassDef()!=zCDecal		::GetStaticClassDef()) &&
		    (vob->GetVisual()->GetClassDef()!=zCParticleFX	::GetStaticClassDef()) &&
		    (vob->GetVisual()->GetClassDef()!=zCQuadMark	::GetStaticClassDef()) &&
			(vob->GetVisual()->GetClassDef()!=zCPolyStrip	::GetStaticClassDef()))
		{
			zCVisual	*dummyVis;
			zREAL		alpha;
			zREAL		distVobToCam	= (vob->GetPositionWorld() - camPos).LengthApprox();

			vob->CalcRenderAlpha		(distVobToCam, dummyVis, alpha);

			if (alpha<=0)
			{
				// Vob komplett unsichtbar (weil z.B. auch zu weit entfernt)
				renderVobList.RemoveIndex			(i);
				--i;
			} else 
			{
				if (alpha<1)
				{
					// Vob hat ein Alpha zwischen 0 und 1 oder groesser
					zCRndAlphaSortObject_Vob *alphaVob	= zCRndAlphaSortObject_Vob::GetFreeAlphaVob ();
					alphaVob->SetVob					(vob);
					alphaVob->alpha						= alpha;
					alphaVob->SetZValue					(distVobToCam);
					zrenderer->AddAlphaSortObject		(alphaVob);

					renderVobList.RemoveIndex			(i);
					--i;
				};
			};
		};

		// DrawBBox3D
		if ((vob->GetDrawBBox3D()) || (GetDrawVobBBox3D())) 
		if (vob!=zCCamera::activeCam->GetVob())
		{
			zCCamera::activeCam->Activate();
			int colUp	= GFX_WHITE;
			int colAt	= GFX_YELLOW;
			int colRight= GFX_ORANGE;
			zCVobLight *vobLight = dynamic_cast<zCVobLight*>(vob);
			if (vobLight)
			{
				vob->bbox3D.Draw (vobLight->GetIsStatic()	? GFX_GREEN : GFX_BLUE);	// worldSpace 
			} else {
				vob->bbox3D.Draw (vob->GetSleeping()		? GFX_RED : GFX_ORANGE);	// worldSpace 
			};
			const	zREAL DIM	= 30.0F;
			static	zREAL wave;
			if (!vob->GetSleeping())	wave	= zSin(ztimer.GetTotalTimeF()*0.005F);
			else						wave	= 1.0F;
			zREAL	size		= DIM + wave*(DIM*0.1F);

			zlineCache.Line3D (vob->GetPositionWorld(), vob->GetPositionWorld()+vob->GetUpVectorWorld()	*size	, colUp);
			zlineCache.Line3D (vob->GetPositionWorld(), vob->GetPositionWorld()+vob->GetAtVectorWorld()	*size	, colAt);
			zlineCache.Line3D (vob->GetPositionWorld(), vob->GetPositionWorld()+vob->GetRightVectorWorld()*size	, colRight);
//			vob->bspTreeNode->bbox3D.Draw();

			// Text-Infos ueber Vob einblenden
			// (nicht im Spacer)
			#ifdef zBSP_SHOW_VOBNAMES
			#ifndef COMPILING_SPACER
			{
				int xscr, yscr;
				zPOINT3 pos = zCCamera::activeCam->Transform(vob->GetPositionWorld());
				if (pos[VZ]>0) 
				if (pos[VZ]<700) 
				{
					zSTRING				name	= vob->GetClassName_();
					if (pos[VZ]<500)	name	= name + ":"+vob->GetVobName();
					if (pos[VZ]<200)	name	= name + ":"+((vob->GetVisual()) ? (vob->GetVisual()->GetVisualName()) : "%");
					zCCamera::activeCam->Project	(&pos, xscr, yscr);
					screen->Print					(screen->anx(xscr), screen->any(yscr), name);
				};
			};
			#endif
			#endif
		};

	};

	// Vobs nach deren Visual sortieren (alphaVobs sind bereits herausgefiltert)
	qsort (renderVobList.GetArray(), renderVobList.GetNum(), sizeof(renderVobList[0]), CompareVobsByVisual);

//#ifdef DEBUG_HILDEBRANDT
#if 0
	// PARANOID (korrekt sortierte renderVobList testen)
	if (zinput->KeyPressed(KEY_U))
	{
		for (int i=0; i<renderVobList.GetNum(); i++)
		{
			const zSTRING visName = (renderVobList[i]->GetVisual()) ? renderVobList[i]->GetVisual()->GetVisualName() : "";
			zERR_MESSAGE (1, 0, "D: "+zSTRING(i)+": "+renderVobList[i]->GetClassDef()->GetClassName_()+", "+renderVobList[i]->GetVobName()+", vis: "+visName);
		};
	};
#endif

	// Von der renderVobList eine Kopie erzeugen, da diese ggfs. durch das Entfernen von
	// Vobs aus der Welt (visual->Died() oder vob->Render()) veraendert werden koennte.
	zCArray<zCVob*> renderVobListCopy(renderVobList.GetNum());
	renderVobListCopy = renderVobList;

	// RenderContext erstellen
	zTRenderContext renderContext;
	renderContext.Clear					();

	// Nicht gerenderte Vobs werden nicht aus der renderVobList entfernt (das war einmal so). Deshalb ist dieser immer
	// ein gutes Stueck ueberschaetzt (Frustum Culling und Distanz-Fade Culling fehlen mindestens).
	for (i=0; i<renderVobListCopy.GetNum(); i++)
	{
		zCVob *vob = renderVobListCopy[i];
		zERR_ASSERT (vob);
		zERR_ASSERT (vob->GetRefCtr()>0);

		if (zrenderer->GetSurfaceLost()) break;

		if ((zCVob::GetRenderVobs()) &&
			((vob->GetShowVisual()) || (zCVob::GetShowHelperVisuals() && (!vob->GetVisual()))))
		{
			// pfx und decals wegen drawPoly/Alpha gesondert behandeln (fixme..)
			// FIXME: ??????
			// Problem: diese Visuals erzeugen 'DrawPoly-AlphaPolys', sollten also nicht als AlphaVobs gerendert werden,
			// sondern schon vorher, damit ihre enthaltenen Polys fruehzeitig in die Buckets gelangen. Allerdings:
			// wer setzt das zrenderer Ausfade-Alpha in diesem Fall ??
			zREAL		alpha		= 1;
			zCClassDef	*visClass	= vob->GetVisualClass();
			if ((visClass==zCDecal		::GetStaticClassDef()) || 
				(visClass==zCParticleFX	::GetStaticClassDef()) || 
				(visClass==zCQuadMark	::GetStaticClassDef()) || 
				(visClass==zCPolyStrip	::GetStaticClassDef()))
			{
				zCVisual	*dummyVis;
				zREAL		distVobToCam		= (vob->GetPositionWorld() - camPos).LengthApprox();
				vob->CalcRenderAlpha			(distVobToCam, dummyVis, alpha);
				if (alpha<=0)
				{
					continue;
				} else
				if (alpha<1)
				{
					// fuer DrawPoly Visuals..
					zrenderer->SetAlphaBlendSource	(zRND_ALPHA_SOURCE_CONSTANT);
					zrenderer->SetAlphaBlendFactor	(alpha);
				};
			};

			// RenderContext erstellen
			renderContext.clipFlags				= zCCamera::CLIP_FLAGS_FULL;
			renderContext.vob					= vob;
			renderContext.world					= vob->GetHomeWorld();
			renderContext.cam					= zCCamera::activeCam;
			renderContext.hintLightingFullbright= FALSE;
			renderContext.hintLightingSwell		= FALSE;
			renderContext.hintLightingHighlight	= FALSE;

			//
			if (!vob->Render(renderContext)) 
			{
				// RendererState zuruecksetzen
				if (alpha<1)
				{
					zrenderer->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_MAT_DEFAULT);
					zrenderer->SetAlphaBlendSource	(zRND_ALPHA_SOURCE_MATERIAL);
				};
				// FALSE => invisible => aus Liste loeschen
				continue;
			} else 
			{
				// RendererState zuruecksetzen
				if (alpha<1)
				{
					zrenderer->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_MAT_DEFAULT);
					zrenderer->SetAlphaBlendSource	(zRND_ALPHA_SOURCE_MATERIAL);
				};
				// Vob ist im Frustum sichtbar
				drawnVobs++;
			};
		};

		if ((vob->GetVisual()) &&
			(vob->GetVisual()->GetVisualDied()))
		{
			// Vob wird released und aus Welt entfernt
			// (wird auch deleted, falls keine weiteren Referenzen auf das Objekt bestehen)
			// zerr.Message ("D: killing vob: "+vob->GetObjectName()+", ptr: "+zSTRING(int(vob))+", frameCtr: "+zSTRING(vob->GetHomeWorld()->GetMasterFrameCtr()));
			vob->GetHomeWorld()->RemoveVob	(vob);
			vob								= 0;
			// continue;
		}
	};
};

/*
			//
			if (vob->GetVisual())
			{
				int xscr, yscr;
				zPOINT3 pos;
				pos = zCCamera::activeCam->Transform(vob->GetPositionWorld());
				if (pos[VZ]>0) {
					zCCamera::activeCam->Project		(&pos, xscr, yscr);
					screen->Print						(screen->anx(xscr),screen->any(yscr), zSTRING(res));
				};
			};
		};

		if (vob->GetVobType()==zVOB_TYPE_LIGHT) {
			zCCamera::activeCam->camMatrix = camTrafoWorldToCam;
//			vob->bspTreeNode->bbox3D.Draw(GFX_RED);
			vob->bbox3D.Draw (GFX_BLUE);
//			if (vob->bspTreeNode->IsNode()) 
			{
//				zCBspNode *node = (zCBspNode*)vob->bspTreeNode; 
//				for (int i=0; i<node->numLeafs; i++)
//					node->leafList[i].bbox3D.Draw (GFX_ORANGE);
				zCVobLight *light = (zCVobLight*)vob;
				for (int i=0; i<light->vobLeafList.GetNumInList(); i++)
					light->vobLeafList[i]->bbox3D.Draw (GFX_ORANGE);
			};
		};
*/





/* ----------------------------------------------------------------------
	
    zCBspLeaf::~zCBspLeaf()	

	21.09.2000	[Moos]	
                Erzeugt, um den PlueckerBuffer wieder loszuwerden

   ---------------------------------------------------------------------- */



zCBspLeaf::~zCBspLeaf ()
{
    if (polyPlueckerRefCtr)
        zCRayCache::NodeDeleted(this);

    // eigentlich sollte jetzt der PlueckerCache gelöscht sein
    zERR_ASSERT (!polyPlueckerRefCtr);

    // und falls nicht, mache es jetzt.
    if (!(--polyPlueckerRefCtr)){
        delete[] polyPluecker;
        polyPluecker = NULL;
    }


#ifdef COMPILING_SPACER
    static zBOOL reported = TRUE;
#else
    static zBOOL reported = FALSE;
#endif
    if (leafVobList.GetNumInList())
    {
        if (!reported)
            zERR_FAULT("M: BSP leaf destroyed, but had still vob(s) in it´s lists.");
        reported = TRUE;

        for (int i = leafVobList.GetNumInList() -1 ; i>=0; i--)
            leafVobList[i]->vobLeafList.Remove(this);
    }

    if (lightVobList.GetNumInList())
    {
        if (!reported)
            zERR_FAULT("M: BSP leaf destroyed, but had still light(s) in it´s lists.");
        reported = TRUE;

        for (int i = lightVobList.GetNumInList() -1 ; i>=0; i--)
            lightVobList[i]->vobLeafList.Remove(this);
    }
}

/* ----------------------------------------------------------------------
	
    zCBspLeaf::polyPlueckerAddRef()	

	21.09.2000	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

void zCBspLeaf::PolyPlueckerAddRef()
{
    if (!polyPlueckerRefCtr)
	{
        zERR_ASSERT(!polyPluecker);

        int i;
        // zähle die Ecken aller Polygone
        int numEdges=0;
        for (i=numPolys-1; i>=0 ; i--)
            numEdges += polyList[i]->polyNumVert;


        // Erzeuge die Pluecker-Koordinaten der Polygone

        polyPluecker = zNEW_ARRAY(zCPluecker, numEdges);
        zERR_ASSERT_STRICT(polyPluecker);
        
        zVEC3 center = (bbox3D.mins+bbox3D.maxs)*.5;
        zREAL scale  = 1/(bbox3D.mins-bbox3D.maxs).Length();

        zCPluecker *runPluecker = polyPluecker;

        for (i=numPolys-1; i>=0 ; i--){
            zCPolygon *poly = polyList[i];
            int numVert = poly->polyNumVert;

            for (int j=numVert-1; j>=0; j--){
                *runPluecker = zCPluecker((poly->vertex[j]->position -  center)*scale, poly->vertex[(j+1) % numVert]->position - poly->vertex[j]->position);
                runPluecker->Normalize();  // Schmeisse die Pluecker-Koordinaten einfach der Reihe nach in das Array. Die auslesende Funktion zCRayCache::NextNode() muss sie natürlich in eben dieser Reihenfolge bearbeiten.
                runPluecker++;
            }
        }

    }
    polyPlueckerRefCtr++;
}


/* ----------------------------------------------------------------------
	zCBspLeaf::polyPlueckerRelease()	

	21.09.2000	[Moos]	
                Erzeugt
   ---------------------------------------------------------------------- */

void zCBspLeaf::PolyPlueckerRelease()
{
    zERR_ASSERT (polyPluecker);
    if (!(--polyPlueckerRefCtr))
	{
        // lösche die Pluecker-Koordinaten
        delete[] polyPluecker;

        polyPluecker = NULL;
    }
}

void zCCFASTCALL zCBspLeaf::AddVobsToRenderList (zTBBox2D *sectorPortal2D)
{
	// ACHTUNG: bspFrameCtr
	int i;

	// vobs
	if (leafVobList.GetNum()>0) 
	{
		if (sectorPortal2D)
		{
			i=0;
			do {
				zCVob *vob = leafVobList[i]; 

				if (vob->lastTimeDrawn==bspFrameCtr) continue;
				vob->lastTimeDrawn = bspFrameCtr;

				// F_IXME: Bei der Aktivierung dieses Tests gibt es noch Probleme! (Z.B. im OrcGraceyard, ORC_WALL_FIRE_01)
				//        Anscheinend wurde ein Vob, der sich in demselben Sektor wie die Kamera befand, gegen ein direkt				//        angrenzendes/nach aussen fuehrendes Portal getestet (oben sectorPortal2D, rechts am Screen).
				//		  Dabei wurde der Vob nicht als sichtbar markiert. (???????)
				// Update: scheint jetzt zu funzen, Grund: Bei Sektor-Aktivierungen muss zuerst in die Tiefe, dann erst this aktiviert werden!
				if (zCCamera::activeCam->ScreenProjectionTouchesPortal (vob->GetBBox3DWorld(), *sectorPortal2D)) 
				{
					actBspTree->renderVobList.Insert (vob);
				};
			} while (++i<leafVobList.GetNum());
		} else 
		{
			i=0;
			do {
				zCVob *vob = leafVobList[i]; 

				if (vob->lastTimeDrawn==bspFrameCtr) continue;
				vob->lastTimeDrawn = bspFrameCtr;
				actBspTree->renderVobList.Insert (vob);
			} while (++i<leafVobList.GetNum());
		};
	};

	// lights (nur dyn und RenderLights..)
	if (lightVobList.GetNum()>0) {
		int i=lightVobList.GetNum()-1;
		do {
			zCVobLight *vob = lightVobList[i]; 
			if ((vob->GetIsStatic()) && (!vob->HasVisual()) && (!zCVobLight::GetRenderLightVisuals()))	break;			// nur dyn Lights und Lights mit RenderVisual (z.B. LensFlare oder zCVisual)
			if (vob->lastTimeDrawn==bspFrameCtr)				continue;
			vob->lastTimeDrawn = bspFrameCtr;
			actBspTree->renderLightList.Insert (vob);
		} while (--i>=0);
	};
};


void zCBspLeaf::AddVobsToRenderListOutdoor () 
{ 
	
	// fuer startpunkt outdoor
	for (int i=0; i<leafVobList.GetNumInList(); i++) 
	{
		zCVob		*vob		= leafVobList[i]; 
			
		if (vob->lastTimeDrawn==bspFrameCtr) continue;
		zCPolygon	*groundPoly	= vob->GetGroundPoly();
		if (groundPoly) {
			zCBspSector	*vobSector = groundPoly->GetMaterial()->GetBspSectorFront();
			if (vobSector) continue;
		};

		// 
		if (!IsVisibleVob(vob)) continue;

		//
		actBspTree->renderVobList.Insert (vob);
		vob->lastTimeDrawn=bspFrameCtr;
	};

	// lights
	if (lightVobList.GetNum()>0) {
		int i=lightVobList.GetNum()-1;
		do 
		{
			zCVobLight *vob = lightVobList[i]; 
			if ((vob->GetIsStatic()) && (!vob->HasVisual()) && (!zCVobLight::GetRenderLightVisuals()))	break;			// nur dyn Lights und Lights mit RenderVisual (z.B. LensFlare oder zCVisual)
			if (vob->lastTimeDrawn==bspFrameCtr) continue;
			vob->lastTimeDrawn = bspFrameCtr;
			actBspTree->renderLightList.Insert (vob);
		} while (--i>=0);
	};
}; 

void zCCFASTCALL zCBspLeaf::AddVobsToRenderListOutdoor (zCBspSector* sector, const zTBBox2D& sectorPortal2D) 
{ 
	// aus einem Sektor-Rendering heraus 
	

	zERR_ASSERT (sector);
	{
		for (int i=0; i<leafVobList.GetNumInList(); i++) 
		{
			//
			zCVob		*vob		= leafVobList[i]; 

			if (vob->lastTimeDrawn==bspFrameCtr) continue;
			//
			zCPolygon	*groundPoly	= vob->GetGroundPoly();
			zCBspSector	*vobSector	= 0;
			if (groundPoly) vobSector = groundPoly->GetMaterial()->GetBspSectorFront();

			{
				if (vobSector!=sector) 
				{
					// FIXME: einige PFX werden in portalräumen immer noch nicht dargestellt.
					// allerdings waren die verschwundenen pfx in einem savegame
					// kann es sein, das pfx mit der zeit den vob killen, der dann natürlich nicht 
					// mehr ins savegame reinwandert ?
					zCParticleFX* pfx = zDYNAMIC_CAST<zCParticleFX>(vob->GetVisual());
					if ( !pfx || !pfx->GetForceEveryFrameUpdate() ) continue;
				}

				// Ist Vob-BBox2D im Sektor-Portal ?
				// ACHTUNG: dies ist gleichzeitig ein 'Frustum-Test' !!
				if (!zCCamera::activeCam->ScreenProjectionTouchesPortal (vob->GetBBox3DWorld(), sectorPortal2D))
					continue;
			} 

			actBspTree->renderVobList.Insert (vob);
		vob->lastTimeDrawn=bspFrameCtr;
		};
	} 

	// lights
	if (lightVobList.GetNum()>0) {
		int i=lightVobList.GetNum()-1;
		do {
			zCVobLight *vob = lightVobList[i]; 
			if ((vob->GetIsStatic()) && (!vob->HasVisual()) && (!zCVobLight::GetRenderLightVisuals()))	break;			// nur dyn Lights und Lights mit RenderVisual (z.B. LensFlare oder zCVisual)
			if (vob->lastTimeDrawn==bspFrameCtr) continue;
			vob->lastTimeDrawn = bspFrameCtr;
			actBspTree->renderLightList.Insert (vob);
		} while (--i>=0);
	};
};

void zCCFASTCALL zCBspBase::AddVobsToRenderListSubtree (int clipFlags) 
{
	if (IsLeaf()) 
	{
		zCBspLeaf* leaf = (zCBspLeaf*)this;
		if (actBspTree->GetBspTreeMode()==zBSP_MODE_OUTDOOR)	leaf->AddVobsToRenderListOutdoor();
		else													leaf->AddVobsToRenderList();
		return;
	} else
	{
		zCBspNode *thisNode = (zCBspNode*)this;
		// Triv-in ? 
		if (clipFlags>0) 
		{
			zTCam_ClipType nodeClip = zCCamera::activeCam->BBox3DInFrustum (bbox3D, clipFlags);
			if (nodeClip==zCAM_CLIP_TRIV_OUT) return;
			if (thisNode->front) thisNode->front->AddVobsToRenderListSubtree	(clipFlags);
			if (thisNode->back ) thisNode->back ->AddVobsToRenderListSubtree	(clipFlags);
		} else {
			// Triv-in ! => Leafs ohne weitere Checks einsammeln
			if (actBspTree->GetBspTreeMode()==zBSP_MODE_OUTDOOR) {
				for (int i=0; i<thisNode->numLeafs; i++)
					thisNode->leafList[i].AddVobsToRenderListOutdoor();
			} else {
				for (int i=0; i<thisNode->numLeafs; i++)
					thisNode->leafList[i].AddVobsToRenderList();
			};
		};
	};
};

zTBBox2D zCBspBase::GetScreenBBox2D() const 
{
	// assert: zCCamera::activeCam->camMatrix stimmt
	zERR_ASSERT(zCCamera::activeCam);

	zREAL			xc,yc,xr,yr;
	zTBBox2D		box2D; 
	zTBSphere3D		sphere;
	sphere.center	= bbox3D.GetCenter	();
	sphere.radius	= zREAL(0.5F) * (bbox3D.maxs - bbox3D.mins).LengthApprox();
	// FIXME: ist so leider immer noch nicht ganz perfekt, die Sphere ist manchmal zu klein, besonders,
	//        wenn das BBoxCenter nah an der Cam ist => liegt daran, dass SphereCenter=vobCenter...

	sphere.center	= zCCamera::activeCam->Transform (sphere.center);
	zPOINT3 p2		= sphere.center + zVEC3(-sphere.radius, sphere.radius,0);
	
	// Prob: was, wenn das VobCenter hinter der Cam ist ? 
	if (sphere.center[VZ]<=2) {
		box2D.mins[VX] = box2D.mins[VY] = 0;
		box2D.maxs[VX] = box2D.maxs[VY] = zVALUE_MAX;
//		box2D.Draw();
		return box2D;
	};
	zREAL zrecip	= (zREAL(1)) / sphere.center[VZ];

	zCCamera::activeCam->Project (&(sphere.center)	, zrecip, xc, yc);
	zCCamera::activeCam->Project (&(p2)				, zrecip, xr, yr);

	box2D.mins[VX] = xr;
	box2D.mins[VY] = yr;
	box2D.maxs[VX] = xc+(xc-xr);
	box2D.maxs[VY] = yc+(yc-yr);
//	box2D.Draw();
	return box2D;
};

void zCBspBase::CollectNodeLights() 
{
	// Hier sollen nur die relevanten Dyn-lights eingesammelt werden. Die Beleuchtung findet dann in RenderPoly
	// statt (nur onscreen/frontFace Polys). Da dann Beleuchtung von ClipVerts im WorldSpace und vorher der 
	// obligatorische Reset des lightDyn auf das lightStat.

#if 0
	
	// FIXME: passt nicht 100%ig: Ist im Leaf ein animiertes Wasserpoly vorhanden, so muss
	// das Licht _jeden_ Frame neu berechnet werden

	s_leafRelightPolys	= TRUE;

	s_leafDynLights.EmptyList();
	s_leafMovingLights.EmptyList();

	// Beleuchtung dieses leafes/nodes festlegen
	zTFrameCtr relightCtr=zCSkyControler::GetActiveSkyControler()->GetRelightCtr();
	if (lastTimeLighted!=relightCtr )
	{
		lastTimeLighted	= relightCtr;
		s_leafRelightPolys			= TRUE;
	}
	else return;


	if (IsNode()) return;
	
	// Beleuchtung eines LEAFS durch VOBLIGHTS
	zCBspLeaf *thisLeaf = (zCBspLeaf*)this;

	if (numPolys<=0)						return;

	if (thisLeaf->lightVobList.GetNum()>0)
	{
		for (int i=thisLeaf->lightVobList.GetNum()-1; i>=0; i--) 
		{
			// nur dyn. Lights beruecksichtigen
			zCVobLight *light			= thisLeaf->lightVobList[i];
			if (light->GetIsStatic())	break;		// nur dyn Lights, Lights sind im Leaf sortiert: static,dynamic
			s_leafDynLights.Insert		(light);
		};
	};
	//if (s_leafRelightPolys)	screen->Print (0,3000, "relight");

#endif
	s_leafRelightPolys	= TRUE;

	s_leafDynLights.EmptyList();
	s_leafMovingLights.EmptyList();

	if (IsNode()) return;

	// Beleuchtung eines LEAFS durch VOBLIGHTS
	{
		zCBspLeaf *thisLeaf = (zCBspLeaf*)this;

		if (numPolys<=0)						return;

		if (thisLeaf->lightVobList.GetNum()>0)
		{
			//s_leafRelightPolys	= TRUE;
			zCVobLight *light;
			for (int i=thisLeaf->lightVobList.GetNum()-1; i>=0; i--) 
			{
				// nur dyn. Lights beruecksichtigen
				light	= thisLeaf->lightVobList[i];
				if (light->GetIsStatic())	break;		// nur dyn Lights, Lights sind im Leaf sortiert: static,dynamic
				if (!light->GetCanMove()) s_leafDynLights.Insert	(light); 	
				else		  			  s_leafMovingLights.Insert (light);
			};
		};
	};
//	if (s_leafRelightPolys)	screen->Print (0,3000, "relight");

};

void zCCFASTCALL zCBspLeaf::RenderLeafIndoor (int clipFlags) 
{
	// Polys beleuchten
	// Polys rendern 

	// Ist leaf diesen Frame aktiviert worden?
	if (lastTimeActivated!=bspFrameCtr) return;

	// Occlusion Test der Leaf-BBox gegen das aktivierende Sektor-Portal?
	// (sectorIndex==zSECTOR_INDEX_UNDEF, wenn das Leaf sich im StartSektor befindet, der Sektor mit allen Leafs also komplett sichtbar ist)
	if (sectorIndex!=zSECTOR_INDEX_UNDEF)
	{
		zCBspSector *sector = actBspTree->sectorList[sectorIndex];
		if ((sector) &&
			(!actBspTree->GetShowPortals()))		// im Debug Mode nicht gegen BBox clippen, um Portal-Aktivierung besser zu sehen
		{
//			if (GetScreenBBox2D().Classify(sector->activePortal)==zCAM_CLIP_TRIV_OUT) return;
			if (!zCCamera::activeCam->ScreenProjectionTouchesPortalRough (this->bbox3D, sector->activePortal))	return;
		};

		// Beim Einsammeln der Vobs diese gegen das SectorPortal testen
		AddVobsToRenderList	(&sector->activePortal); 
	} else 
	{
		// Beim Einsammeln der Vobs diese NICHT gegen das SectorPortal testen
		AddVobsToRenderList	(0); 
	};

	//
	clipFlags &= zCCamera::CLIP_FLAGS_FULL_WO_FAR;

	CollectNodeLights ();  

	zCPolygon **ppoly = polyList;
	for (int i=0; i<numPolys; i++) 
	{
		zCPolygon *poly = (*ppoly);

		// Hier koennte man evtl. per Flag im Leaf ankuendigen, ob das Leaf ueberhaupt Portale
		// enthaelt (das tun die wenigsten). In dem Falle koennte man diesen Test hier in 98% aller Faelle
		// umgehen.
		if (poly->IsPortal()) break;
 
		poly->RenderPoly	(clipFlags); 
		ppoly++;
	};
	drawnLeafs++;
};

void zCBspBase::RenderTrivInIndoor () 
{ 
	// FIXME: statt Rekursion einfach die LeafList der aktuellen Node linear abgehen.
	//        (und dabei die Vobs aus den Leafs ziehen ??)
	if (IsLeaf())
	{
		static_cast<zCBspLeaf*>(this)->RenderLeafIndoor	(0);
		return; 
	} else 
	{
		zCBspNode *node = static_cast<zCBspNode*>(this);
		for (int i=0; i<node->numLeafs; i++)
		{
			node->leafList[i].RenderLeafIndoor (0);
		};
	};
};

void zCCFASTCALL zCBspBase::RenderIndoor (int clipFlags) 
{
//	if (actBspTree->cfg_renderBBox3D) zCCamera::activeCam->DrawBBox3D(bbox3D);

	// Lage der BBox zum Camera-Viewport
	// FIXME: koennte noch schneller sein: die hier emittelten clipFlags gelten ja auch fuer den Subtree und koennen
	//        diesem mitgegeben werden (=> dort dann nur noch gegen diese testen, => Quake, r_bsp.c)
//	int clipFlags;
	zTCam_ClipType nodeClip = zCCamera::activeCam->BBox3DInFrustum (bbox3D, clipFlags);
	switch (nodeClip) {
	case zCAM_CLIP_TRIV_IN:
		// node + subtree rendern, ohne weitere Tests
		RenderTrivInIndoor();
		return;
		break;
	case zCAM_CLIP_TRIV_OUT:
		// node + subtree komplett wegwerfen
		return;
		break;
	case zCAM_CLIP_CROSSING:
		// falls möglich weitere Rekursion, sonst: rendern 
		// Leaf ? => sofort Rendern
		if (IsLeaf()) {
			// Leaf => Draw
			((zCBspLeaf*)this)->RenderLeafIndoor	(clipFlags);
			return;
		};
		// Rekursion
		// an dieser Stelle: nodeType==zBSP_NODE
		// FIXME: 'DO WHILE' statt Rekursion
		zCBspNode *thisNode;
		thisNode = (zCBspNode*)this;
		if (thisNode->front) thisNode->front->RenderIndoor(clipFlags);
		if (thisNode->back ) thisNode->back ->RenderIndoor(clipFlags);
		break;
	};
};

void zCCFASTCALL zCBspBase::RenderNodeOutdoor (int clipFlags) 
{
	// Polys beleuchten
	drawnLeafs++;
	CollectNodeLights ();  

//	leafActPoly=0;

	//
	clipFlags &= zCCamera::CLIP_FLAGS_FULL_WO_FAR;

	// Polys rendern 
	zCPolygon **ppoly = polyList;
	zCPolygon *poly;
	int i=numPolys-1;
	do {
		poly = *ppoly;

		// arg..doerti [EDENFELD] die folgende zeile muss wohl rein, da einige polys schon gerendert wurden ????
		if (poly->lastTimeDrawn==bspFrameCtr) 
		{
			ppoly++; continue;
		}

		// FIXME: Polys sortieren: polys, portale, sectorPolys	(das bringt noch ~0.5fps, ist aber buggy)
		if (poly->IsPortal()) 
		{
			poly->lastTimeDrawn=bspFrameCtr;

			if (poly->GetGhostOccluder()) 
			{
				// ghost-occluder (2-sided?):	clip, trafo/project, ScanHorizon
				if (poly->ClipToFrustum_Occluder (clipFlags)) 
				{ 
					// kein doScanHorizon
					poly->TransformProject();

					#ifdef zBSP_SHOW_GHOST_OCCLUDER
						poly->ClipToFrustum		();
						poly->TransformProjectLight ();
						zrenderer->DrawPoly		(poly);
					#endif

					ScanHorizon					(poly);
				}; 
				ppoly++; continue;
			};

			// Hier duerfen nur outdoor=>indoor Portals aktiviert werden
			if (poly->GetMaterial()->GetBspSectorFront()!=0) 
			{
				ppoly++; continue;
			}

			zCBspSector *sector = poly->GetMaterial()->GetBspSectorBack();

			if (sector) 
			{
				// ghost-occluder (2-sided):	clip, trafo/project, ScanHorizon
				// 1) backface Culling
				if (poly->IsBackfacing()) 
				{
					ppoly++; continue;
				}
				
				if (sector->ShouldActivatePortal (poly)) 
				{
					if (poly->ClipToFrustum (clipFlags)) 
					{ 
						// kein doScanHorizon
						if (poly->GetMaterial()->GetAlpha()>1) 
						{ 
							poly->TransformProjectLight ();
							poly->GetMaterial()->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND); 
							zrenderer->DrawPoly (poly);
						}
						else
						{
							poly->TransformProject();
						}
						zTBBox2D portalBBox2D; 
						poly->GetScreenBBox2D				(portalBBox2D);		// trafo & project noetig !!!
						sector->ActivateSectorRec			(portalBBox2D);
						// Die Sektoren werden an Ort und Stelle (d.h. also auch tiefensortiert) gerendert, damit
						// ihre potentielle Occlusion wirksam wird
						zCBspSector::RenderActiveSectorList	();
					}; 
				} else {
					poly->lastTimeDrawn--;
					poly->GetMaterial()->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_NONE); 
					const zCPolygon::zTPortalType pt = poly->GetPortalType();
					poly->SetPortalType	(zCPolygon::zPORTAL_TYPE_NONE);
					poly->RenderPoly	(clipFlags);	// inkl. doScanHorizon, FIXME: backfaceCulling ist hier doppelt !
					poly->SetPortalType	(pt);
				}
				// Portale sollten immer gerendert werden (nur indoor/outdoor)
				// => damit sie durch das 'ScanHorizon()' als Occluder dienen
				// FIXME: nur rendern, wenn alpha>0
				// FIXME: hier nur Sectoren mit 1 in=>out Portal 
			};
		} else {
			// erstes 'nur-Sektor' Poly ? (also kein Portal) => ende
			if (poly->GetSectorFlag()) return;
			
			poly->RenderPoly	(clipFlags);
		};
		ppoly++;
	} 
	while (i--);
};

/*
static void ShowTopView (zTBBox3D bbox3D) {
	// topview
	zREAL S = 0.004F; 
	zREAL x1,y1,x2,y2;
	x1 = int(bbox3D.mins[VX]*S)+320;	y1 = int(bbox3D.mins[VZ]*S)+240;
	x2 = int(bbox3D.maxs[VX]*S)+320;	y2 = int(bbox3D.maxs[VZ]*S)+240;
	zlineCache.Line (x1,y1, x2,y1);	zlineCache.Line (x2,y1, x2,y2);
	zlineCache.Line (x2,y2, x1,y2);	zlineCache.Line (x1,y2, x1,y1);
	zlineCache.Line (x1,y1, x2,y2);	zlineCache.Line (x2,y1, x1,y2);
	zPOINT3 camPos = (zCCamera::activeCam->GetVob()->GetPositionWorld());
	x1 = int (camPos[VX]*S)+320;		y1 = int (camPos[VZ]*S)+240;
	zlineCache.Line (x1,y1, x1+1,y1+1);
}
*/



void zCCFASTCALL zCBspBase::RenderOutdoor (zCBspBase* node, zTBBox3D bbox3DCell, int clipFlags, zBOOL crossingVobFarPlane) 
{
	while (node) 
	{
		// trivial_in ?
		if (clipFlags>0) 
		{
			// FIXME: vorausberechnen
			// maxYWorld - camY - maxYBBoxNode
			zREAL		worldYMax	= actBspTree->GetRoot()->bbox3D.maxs[VY];
			zTBBox3D	nodeBox		= node->bbox3D;
			zREAL		nodeYMax	= zMin (worldYMax, zCCamera::activeCamPos[VY]);
						nodeYMax	= zMax (nodeYMax , node->bbox3D.maxs[VY]);
			nodeBox.maxs[VY]		= nodeYMax;
			zTCam_ClipType nodeClip = zCCamera::activeCam->BBox3DInFrustum (nodeBox, clipFlags); 
			// node + subtree komplett wegwerfen 
			if (nodeClip==zCAM_CLIP_TRIV_OUT) return;
		};
	
		//
		if (crossingVobFarPlane) 
		{
			crossingVobFarPlane	= (node->bbox3D.ClassifyToPlane (actBspTree->vobFarPlane, actBspTree->vobFarPlaneSignbits)!=zPLANE_BEHIND);
		};

		// Occlusion-Culling
		bbox3DCell.mins[VY]	= node->bbox3D.mins[VY];
		bbox3DCell.maxs[VY]	= node->bbox3D.maxs[VY];
		if (node->numPolys>=4) 
		{
			// (!IsVisible(bbox3DCell, clipFlags))			// aggresive	: die wirkliche bbox der Zelle

			// folgende Zeile ist ohne Bugs, aber: Performance testen!!!
//			if (!s_bCullOldMethod)
//			{
				if (!IsVisible(node->bbox3D, clipFlags))		// conservative	: die bbox aller Polys dieser Zelle (groesser!)
				{
					//bbox3DCell.Draw();
					//ShowTopView (bbox3DCell);
					return;
				};
//			}
//			else
//			{
//				if (!IsVisible(bbox3DCell, clipFlags))	return;		// aggresive	: die wirkliche bbox der Zelle
//			};

			
		};

		if ((node->IsLeaf()))
		{
			if (crossingVobFarPlane)
				node->AddVobsToRenderListSubtree (clipFlags);	// hier muessen noch die 'weiteren' clipFlags benutzt werden...

			// Nur, wenn nicht sowieso TRIV_IN
			if (clipFlags>0) 
			{
				// Clipflags werden hier auf die wirklichen statischen Polys reduziert
				// evtl. kann sogar noch ein Triv_out passieren
				if (zCCamera::activeCam->BBox3DInFrustum (node->bbox3D, clipFlags)==zCAM_CLIP_TRIV_OUT) return;
			};
			node->RenderNodeOutdoor (clipFlags);
			return;
		};

		// Rekursion
		// an dieser Stelle: nodeType==zBSP_NODE
		zCBspNode *thisNode;
		thisNode = (zCBspNode*)node;

		// front-to-back
		int			planeAxis	= thisNode->planeSignbits;
		
//		bbox3DCell.mins[VY]	= node->bbox3D.mins[VY];
//		bbox3DCell.maxs[VY]	= node->bbox3D.maxs[VY];

		zTBBox3D	tmpbox		= bbox3DCell;
// FIXME: anhand der Groesse des Dot-Wertes kann man feststellen, ob der Subtree bereits hinter der FarClipPlane ist !!!
		if ((thisNode->plane.normal * zCCamera::activeCam->GetVob()->GetPositionWorld())>thisNode->plane.distance)
		{ 
			if (thisNode->front) {
				tmpbox.mins[planeAxis]	= thisNode->plane.distance;
				RenderOutdoor(thisNode->front, tmpbox, clipFlags, crossingVobFarPlane);
			};

			bbox3DCell.maxs[planeAxis]	= thisNode->plane.distance;
			node = thisNode->back;
		} else 
		{
			if (thisNode->back ) {
				tmpbox.maxs[planeAxis]	= thisNode->plane.distance;
				RenderOutdoor(thisNode->back, tmpbox, clipFlags, crossingVobFarPlane);
			};

			bbox3DCell.mins[planeAxis]	= thisNode->plane.distance;
			node = thisNode->front;
		};
	};
};

// ************
// BspTree
// ************

extern int s_morphedVerts;


//***************************************************************************************************
//																	  ProfileGetTicks
//	METHOD ProfileGetTicks
//	Get ticks
//
//***************************************************************************************************
inline void ProfileGetTicks (__int64* a_pi64Ticks)
{
	__asm
	{
		push edx;
		push ecx;
		mov ecx, a_pi64Ticks;
		_emit 0Fh
		_emit 31h
		mov [ecx],eax;
		mov [ecx+4],edx;
		pop ecx;
		pop edx;
	}
}


//***************************************************************************************************
//																   ProfileGetTickRate
//	METHOD ProfileGetTickRate
//	Get ticks
//
//***************************************************************************************************
inline float ProfileGetTickRate (void)
{
	static float fCPUFrequency	=	-1.0f;
	
	if (-1.0f == fCPUFrequency) 
	{
		__int64 i64CurrRate	=	0;
		::QueryPerformanceFrequency ( (LARGE_INTEGER*) &i64CurrRate );
		fCPUFrequency	=	(float)i64CurrRate;
	} 
	
	return fCPUFrequency;
}




void zCBspTree::Render () 
{ 
/*
	__int64 i64Time;
	__int64 i64StartTime;
	__int64 i64AllStartTime;
			
	static char pcBuffer[400];
			
	ProfileGetTicks( &i64AllStartTime );
			
*/
	s_morphedVerts = 0;
#ifdef DEBUG_WAVES
	if (zinput->KeyPressed(KEY_F11))
	{
		if (zinput->KeyPressed(KEY_LSHIFT))
		{
			s_grid-=10;
		}
		else s_grid += 10;
		zERR_WARNING("C: grid size is now: " + zSTRING(s_grid));
	}
	else 
	if (zinput->KeyPressed(KEY_F8))
	{
		if (zinput->KeyPressed(KEY_LSHIFT))
		{
			s_amp-=10;
		}
		else s_amp += 10;
		zERR_WARNING("C: amplitude is now: " + zSTRING(s_amp));
	}
#endif

	drawnLeafs	  = 0;
	drawnVobs	  = 0;
	bspFrameCtr   = masterFrameCtr;		// inkr. am Ende des Renderns
	actBspTree	  = this;
	renderVobList.EmptyList();
	renderLightList.EmptyList();
	
	numDrawnFarPolys= 0;

	// zBias für statischen Level auf Default Werte setzen
	zrenderer->SetZBias(DEFAULT_LEVEL_ZBIAS);
	zBOOL renderSky = FALSE;

	//
	if (GetBspTreeMode()==zBSP_MODE_INDOOR) 
	{
 		// FIXME:
		zCSkyControler::GetActiveSkyControler()->RenderSkyPre();
		doScanHorizon	= FALSE;

		// Startsektor ermitteln
		zCBspSector	*startSector=0;
		{
			const zCVob		*camVob	= zCCamera::activeCam->GetVob();
			const zPOINT3	start	= camVob->GetPositionWorld();
			zPOINT3			inters;
			zCPolygon		*hitPoly=0;
			// das 'camVob->GetGroundPoly()' darf hier nicht genommen werden, da bei groundPolys die
			// Portale rausgefiltert werden, die hier aber u.U. gebraucht werden
			TraceRay (start, start + zVEC3(0,-500000,0), zTRACERAY_STAT_POLY | zTRACERAY_STAT_PORTALS, inters, hitPoly, 0);
			if ((hitPoly) && (hitPoly->IsPortal()))
			{
				TraceRay (start, start + zVEC3(0,+500000,0), zTRACERAY_STAT_POLY | zTRACERAY_STAT_PORTALS, inters, hitPoly, 0);
			};
			if (hitPoly)
			{
				int sectorIndex = hitPoly->GetSectorIndex();
				if (sectorIndex!=zSECTOR_INDEX_UNDEF)
				{
					// Portal getroffen ?
					if (hitPoly->IsPortal())
					{
						// duerfte hier nicht mehr auftreten
					} else
					// BorderPoly getroffen ?
					if (sectorIndex>=zSECTOR_INDEX_PORTAL)
					{
						// BorderPoly: ueber das Portal den Sektor ermitteln
						int portalIndex = (sectorIndex & (zSECTOR_INDEX_PORTAL-1)) << 1;
						if (portalList[portalIndex]->GetPlane().GetDistanceToPlane(start)<0)	sectorIndex	= portalList[portalIndex]->GetSectorIndex();
						else																	sectorIndex	= portalList[portalIndex+1]->GetSectorIndex();
					};
					startSector = sectorList[sectorIndex];
				};
				if (actBspTree->GetShowPortals())
					screen->Print (0,4000, "startSector: "+zSTRING(sectorIndex));

/*{
	screen->Print (0,4000, "startSector: "	+ zSTRING(sectorIndex));
};*/
			};
/*{
	zSTRING s;
	zCBspLeaf *leaf = actBspTree->FindLeaf (start);
	leaf->bbox3D.Draw();
	for (int i=0; i<actBspTree->sectorList.GetNum(); i++)
	{
		for (int j=0; j<sectorList[i]->sectorNodes.GetNum(); j++)
		{
			if (sectorList[i]->sectorNodes[j]==leaf)
			{
				s += zSTRING(i)+", ";
				break;
			};
		};
	};
	s+= " numPolys: "+zSTRING(leaf->numPolys);
	screen->Print (0,4200, "camLeafs: "		+ s);
};*/
			zCBspSector::SetStartPointOutdoor	(FALSE);
			if (!startSector)
			{
				// CamPos ist keinem Sektor zuordbar: alle Leafs markieren
				for (int leafNr=0; leafNr<numLeafs; leafNr++) 
				{
					zCBspLeaf *leaf = &(leafList[leafNr]);
					leaf->lastTimeActivated	= bspFrameCtr;
					leaf->sectorIndex		= zSECTOR_INDEX_UNDEF;
				};
				// numLeafs ist 0, wenn die World nicht compiled ist. In diesem Fall auch die bspRoot getrennt aktivieren.
				if (numLeafs==0)
				{
					zCBspLeaf *leaf = (zCBspLeaf*)(bspRoot);
					if (bspRoot) {
					if (bspRoot->IsLeaf())
						leaf->lastTimeActivated	= bspFrameCtr;
						leaf->sectorIndex		= zSECTOR_INDEX_UNDEF;
					};
				};
			} else
			{
				zTBBox2D cullBox2D;
				cullBox2D.mins[VX] = zCCamera::activeCam->vpData.xminFloat;
				cullBox2D.mins[VY] = zCCamera::activeCam->vpData.yminFloat;
				cullBox2D.maxs[VX] = zCCamera::activeCam->vpData.xmaxFloat;
				cullBox2D.maxs[VY] = zCCamera::activeCam->vpData.ymaxFloat;
 				startSector->ActivateSectorRecIndoor		(cullBox2D); 
			};
		};

		//
		zBOOL firstPath = ((zrenderer->HasCapability(zRND_CAP_TNL)) && (zrenderMan.GetUseRendererTNL())) || 
						  (worldRenderMode==zWLD_RENDER_MODE_VERT_LIGHT);
//		zBOOL firstPath = (FALSE) || (worldRenderMode==zWLD_RENDER_MODE_VERT_LIGHT);

//		if (worldRenderMode==zWLD_RENDER_MODE_VERT_LIGHT) 
		if (firstPath)
		{
			// 1-pass, vertLight
			zrenderer->SetRenderMode	(zRND_MODE_1_PASS_VERT_LIGHT);
			bspRoot->RenderIndoor		();
			// Polys flushen (nach Texture sortiert), stat. Level abschliessen
			zrenderMan.Flush			();
		} else {
			// lightmaps
//			if (zrenderer->HasCapability (zRND_CAP_MULTITEXTURE)) 
			if (0)
			{
				// 1-pass, multitexture
				zrenderer->SetRenderMode	(zRND_MODE_1_PASS_MULTITEXTURE);
				bspRoot->RenderIndoor		();
			} else {
				// #1, 2-pass, texture
				zrenderer->SetRenderMode	(zRND_MODE_2_PASS_TEXTURE);
				bspRoot->RenderIndoor		();

				// Polys flushen (nach Texture sortiert), stat. Level abschliessen
				zrenderMan.Flush			();
				{
					// #2, 2-pass, lightmaps
					//zrenderer->SetRenderMode		(zRND_MODE_2_PASS_LIGHTMAP);
					//zrenderer->DrawLightmapList	(renderedPolyList.GetArray(), renderedPolyList.GetNumInList());
				};
			};
		}

		// fuer vobs
		zrenderer->SetRenderMode			(zRND_MODE_DYN_POLYS_VERT_LIGHT); 

		RenderLightList						();
		RenderVobList						();

	} 
	else if (GetBspTreeMode()==zBSP_MODE_OUTDOOR) 
	{
		zrenderer->SetRenderMode	(zRND_MODE_2_PASS_TEXTURE);

		// vobFarPlane
		// FIXME: z-Wert nicht hier festlegen !!
		{
			const zREAL	VOB_FAR_Z= vobFarClipZ;
			const zPOINT3& p	= zCCamera::activeCam->camMatrixInv * zPOINT3(0,0, VOB_FAR_Z);
			vobFarPlane.normal	= zVEC3(0,0,-1) * zCCamera::activeCam->camMatrix;
			vobFarPlane.distance= (p * vobFarPlane.normal);
			vobFarPlaneSignbits	= vobFarPlane.CalcSignbits ();
		};
		numSectorsVisited=0;

		// Startpunkt: outdoor oder sector ?
		zBOOL		startOutdoor;
		zCBspSector	*startSector=0;
		{
			zCVob		*camVob	= zCCamera::activeCam->GetVob();
			zPOINT3		start	= camVob->GetPositionWorld();
			zPOINT3		inters;
			zCPolygon	*hitPoly=0;
			// das 'camVob->GetGroundPoly()' darf hier nicht genommen werden, da bei groundPolys die
			// Portale rausgefiltert werden, die hier aber u.U. gebraucht werden
			
			TraceRay (start, start + zVEC3(0,-50000,0), zTRACERAY_STAT_POLY | zTRACERAY_STAT_PORTALS, inters, hitPoly, 0);

			startOutdoor = TRUE;
			if (hitPoly) 
			{
				if (hitPoly->GetSectorFlag())  
				{
					// indoor => outdoor Portal ?
					if ((hitPoly->IsPortal()) && (hitPoly->GetMaterial()->GetBspSectorFront()==0)) 
					{
					}
					else 
					{
						startSector		= hitPoly->GetMaterial()->GetBspSectorFront();
						if (startSector) startOutdoor	= FALSE;
					};
				}; 
			};
		};
		zCBspSector::SetStartPointOutdoor	(startOutdoor);

		//
		if (startOutdoor) 
		{
			InitHorizon								(); 
			zCSkyControler::GetActiveSkyControler()->RenderSkyPre();				// kein zbuffer noetig
			doScanHorizon							= TRUE;
			renderSky								= TRUE;
			bspRoot->RenderOutdoor					(bspRoot, bspRoot->bbox3D);
			doScanHorizon							= FALSE;
		}
		else 
		{
			doScanHorizon							= FALSE;

			zTBBox2D cullBox2D;
			cullBox2D.mins[VX] = zCCamera::activeCam->vpData.xminFloat;
			cullBox2D.mins[VY] = zCCamera::activeCam->vpData.yminFloat;
			cullBox2D.maxs[VX] = zCCamera::activeCam->vpData.xmaxFloat;
			cullBox2D.maxs[VY] = zCCamera::activeCam->vpData.ymaxFloat;

 			startSector->ActivateSectorRec			(cullBox2D); 
			if (zCBspSector::IsOutdoorActive()) 
			{
				zCBspSector::InitHorizonByOutdoorPortals();
				zCSkyControler::GetActiveSkyControler()->RenderSkyPre ();				// kein zbuffer noetig
				renderSky								= TRUE;
				zCBspSector::RenderActiveSectorList	();
				doScanHorizon						= TRUE;
				bspRoot->RenderOutdoor				(bspRoot, bspRoot->bbox3D);
				doScanHorizon						= FALSE;
			} 
			else 
			{
				// [EDENFELD] Addon: hier muss für den fall das die camera in einem sektor startet, und KEIN
				// Outdoor Bereich sichtbar ist, trotzdem für einen Frame der Sky gerendert werden, 
				// damit dortige Tabellen initialisiert werden. Ansonsten werden 
				// Sektor Polys falsch eingefärbt, bis der Outdoor Sky zum ersten Mal gerendert wird
				// (Bunte Polys an Höhleneingängen-Bug)
				if (GetRenderedFirstTime()) zCSkyControler::GetActiveSkyControler()->RenderSkyPre ();				


				// hier ist z.B. nur der zBuffer-Clear noetig ...
				zCOLOR col	= zCSkyControler::GetActiveSkyControler()->GetBackgroundColor();
				if (zrenderer->GetPolyDrawMode ()==zRND_DRAW_WIRE)	zrenderer->Vid_Clear(zCOLOR(0,0,0,255));  
				else												zrenderer->Vid_Clear(col, zRND_CLEAR_ZBUFFER);  
				zCBspSector::RenderActiveSectorList	();
			};			
		};
		
		// camLocation Hint an den SkyControler
		if (startOutdoor)
		{
			zsound->SetGlobalReverbPreset(0,0.0f);		// none

			zCSkyControler::GetActiveSkyControler()->SetCameraLocationHint		(zCSkyControler::zCAM_OUTSIDE_SECTOR);
		} else 
		{
			zsound->SetGlobalReverbPreset(2,0.6f);		// room

			if (zCBspSector::IsOutdoorActive()) 
				zCSkyControler::GetActiveSkyControler()->SetCameraLocationHint	(zCSkyControler::zCAM_INSIDE_SECTOR_CAN_SEE_OUTSIDE);
			else
			{
				zCSkyControler::GetActiveSkyControler()->SetCameraLocationHint	(zCSkyControler::zCAM_INSIDE_SECTOR_CANT_SEE_OUTSIDE);
			}
		};


		
		if (0/*zCWorld::S_GetAlternateRenderOrder()*/)
		{
			zrenderer->SetRenderMode			(zRND_MODE_DYN_POLYS_VERT_LIGHT); 

			RenderVobList						();

			zrenderer->SetRenderMode	(zRND_MODE_2_PASS_TEXTURE);
			
			zCCamera::activeCam->UpdateViewport	();							// Viewport Daten aus der zCView in die zCCamera uebertragen
			zCCamera::activeCam->Activate		();							// camMatrix & '::activeCam' wird hier gesetzt

			// Polys flushen (nach Texture sortiert)	
			// stat. Level abschliessen
			zrenderMan.Flush ();
			
			zrenderer->SetRenderMode			(zRND_MODE_DYN_POLYS_VERT_LIGHT); 

			RenderLightList						();

			zrenderer->SetRenderMode	(zRND_MODE_2_PASS_TEXTURE);
		}
		else
		{
			// fuer vobs

			// Polys flushen (nach Texture sortiert)	
			// stat. Level abschliessen
			zrenderMan.Flush ();

			zrenderer->SetRenderMode			(zRND_MODE_DYN_POLYS_VERT_LIGHT); 

			RenderLightList						();
			RenderVobList						();
		}

		//
/*		if (!zrenderMan.GetUseRendererTNL())
		{
			// #2, 2-pass, lightmaps					
			if (renderedPolyList.GetNum()>0) {			
				zrenderer->SetRenderMode				(zRND_MODE_2_PASS_LIGHTMAP);
				zrenderer->DrawLightmapList				(renderedPolyList.GetArray(), renderedPolyList.GetNumInList());
			};
		};*/
		if (zCWorld::S_GetAlternateRenderOrder())
		{
			// FIXME: hack!!! ansonsten kann es sein, das die colorlayer sphere nicht gerendert
			// wird, wenn man in einem sektor anfängt
			// hier wird nun beim ersten rendern ein "aktivieren" der color sphere erzwungen
			// evtl. macht das noch probs bei mehreren levelwechseln
			static int cnt = 2;
			if (startOutdoor && cnt>0)
			{
				cnt--;
				zCSkyControler::GetActiveSkyControler()->SetColorChanged(TRUE);
				zCSkyControler::GetActiveSkyControler()->SetGlobalSkyScale(0.9f);
				zCSkyControler::GetActiveSkyControler()->SetGlobalSkyScale(1.0f);
			};
		}


#ifdef zBSP_DEBUG_OUTDOOR
		// Display
		zSTRING s;
		if (dontCull)	s+= "hs ";
		if (s.Length()>0)		screen->Print (7000, 7600, "off: "+s);
		if (startSector) 
		screen->Print (0,7400, "startSector: "+startSector->sectorName
			+", portals: "+zSTRING(startSector->sectorPortals.GetNum())
			+", nodes: "+zSTRING(startSector->sectorNodes.GetNum())
			);
		screen->Print (0,7600, "sectorsRendered: "+zSTRING(zCBspSector::s_sectorsRendered));
		screen->Print (0,7800, "sectorsVisited: "+zSTRING(numSectorsVisited));
		
//	if (zinput->KeyPressed(KEY_F6)) skyVari	= (skyVari+1)%2;
	if (zinput->KeyPressed(KEY_F8)) dontCull = !dontCull;

	zSTRING camHint = startOutdoor ? zSTRING("camera is in outdoor") : zCBspSector::IsOutdoorActive() ? zSTRING("sector + outdoor") : zSTRING("sector only");
	screen->Print (4000,7600, camHint);
	camHint = zSTRING("R: ") + zSTRING(zrenderer->GetFogColor().GetRedByte()) + zSTRING(", G: ") + zSTRING(zrenderer->GetFogColor().GetGreenByte()) + zSTRING("B: ") + zSTRING(zrenderer->GetFogColor().GetBlueByte());
	screen->Print (4000,7000, camHint);

//		RenderHorizon					();

#endif
	}


	zCSkyControler::GetActiveSkyControler()->RenderSkyPost(renderSky);	

	leafsRendered = drawnLeafs;
	vobsRendered  = drawnVobs;

	//
	SetRenderedFirstTime(FALSE);
	++masterFrameCtr;
};

// **************
//  Vob-Handling 
// **************

void zCBspNode::CalcPlaneSignbits (zCBspTree *hostBspTree) 
{
/*	if (hostBspTree->GetBspTreeMode()==zBSP_MODE_INDOOR) 
	{
		planeSignbits = plane.CalcSignbits ();		// leafy bsp
	} else 
*/
	{
		if (plane.normal[VX]!=0)	planeSignbits=0; else
		if (plane.normal[VY]!=0)	planeSignbits=1; else
									planeSignbits=2;
//		planeSignbits += 128;		// outdoor-Kennung
	};
};

void zCCFASTCALL zCBspBase::AddVobToLeafs (zCVob* vob) 
{
	// FIXME x  : fuer die node->plane signbits verwenden, wie bei Quake1 in mathlic.b Box_On_Plane_Side()
	// FIXME	: fuer Octree speziell Fast-Variante ! (axial-plane oder nicht koennte mit in den Signbits eincodiert sein !!!!!
	// FIXME x  : Lights sollten als Spheres reingeclippt werden !	

	zCBspNode *node = (zCBspNode*)this;
	while (node) 
	{
		if (node->IsLeaf()) 
		{
			// Leaf erreicht
			zCBspLeaf *leaf = (zCBspLeaf*)node;
			leaf->leafVobList.Insert	(vob);
			vob->vobLeafList.Insert		(leaf);
			return;
		};

		int sides	= vob->GetBBox3DWorld().ClassifyToPlaneSides (node->plane.distance, node->planeSignbits);
//		if (node->planeSignbits>=128)	sides = vob->GetBBox3DWorld().ClassifyToPlaneSides (node->plane.distance, node->planeSignbits & 3);
//		else							sides = vob->GetBBox3DWorld().ClassifyToPlaneSides (node->plane, node->planeSignbits);
		switch (sides) 
		{
			case 1:
				node = (zCBspNode*)node->front;
				break;
			case 2:
				node = (zCBspNode*)node->back;
				break;
			case 3:
				if (node->front) node->front->AddVobToLeafs (vob);
//				if (node->back ) node->back ->AddVobToLeafs (vob);
				node = (zCBspNode*)node->back;
				break;
		};
	};
};

void zCCFASTCALL zCBspBase::AddVobLightToLeafs (zCVobLight* vob) 
{
	// FIXME	: fuer die node->plane signbits verwenden, wie bei Quake1 in mathlic.b Box_On_Plane_Side()
	// FIXME	: fuer Octree speziell Fast-Variante ! (axial-plane oder nicht koennte mit in den Signbits eincodiert sein !!!!!
	// FIXME  x : Lights sollten als Spheres reingeclippt werden !

	zCBspNode	*node = (zCBspNode*)this;
	while (node) 
	{
		if (node->IsLeaf()) 
		{
			// Leaf erreicht
			// Light in der Liste an die richtige, sortierte Stelle bringen: 
			// a) 0 stat Lights							
			// b) 1 stat Lights mit Visual/Lensflare
			// c) 2 dyn  Lights mit Visual/Lensflare
			// d) 3 dyn  Lights							
			zCBspLeaf *leaf = (zCBspLeaf*)node;
			vob->vobLeafList.Insert		(leaf);

			if (leaf->lightVobList.GetNum()<=0)
			{
				leaf->lightVobList.Insert	(vob);
			} else 
			{
				if (vob->HasVisual()) {
					if (vob->GetIsStatic()) {
						// b)
						for (int i=0; i<leaf->lightVobList.GetNum()-1; i++) 
						{
							zCVobLight *otherLight = leaf->lightVobList[i];
							if (!(otherLight->GetIsStatic()) || (otherLight->HasVisual()))	break;
						};
						if (i>=leaf->lightVobList.GetNum()-1)	leaf->lightVobList.InsertEnd	(vob);
						else									leaf->lightVobList.InsertAtPos	(vob, i);
					} else {
						// c)
						for (int i=leaf->lightVobList.GetNum()-1; i>=0; i--) 
						{
							zCVobLight *otherLight = leaf->lightVobList[i];
							if ((otherLight->GetIsStatic()) || (otherLight->HasVisual()))	break;
						};
						leaf->lightVobList.InsertAtPos	(vob, i+1);
					};
				} else {
					// a), b)
					if (vob->GetIsStatic())		leaf->lightVobList.InsertFront	(vob); 
					else						leaf->lightVobList.InsertEnd	(vob);
				};
			};
			
			// Bei den Vobs im Leaf das Lighting 'dirty' machen
			if (vob->GetIsStatic())
			{
				for (int i=0; i<leaf->leafVobList.GetNum(); i++)
					leaf->leafVobList[i]->SetLightColorStatDirty();
			} else {
				for (int i=0; i<leaf->leafVobList.GetNum(); i++)
					leaf->leafVobList[i]->SetLightColorDynDirty();
			};
			return;
		};

		// Light als Sphere in den BSP clippen
//		int	sides = vob->GetBBox3DWorld().ClassifyToPlaneSides (node->plane);
/*		zTBBox3D box;
		zREAL r		= vob->GetRange(); 
		box.mins	= zVEC3(-r,-r,-r) + vob->GetPositionWorld();
		box.maxs	= zVEC3( r, r, r) + vob->GetPositionWorld();
		int	sides = box.ClassifyToPlaneSides (node->plane);
*/
		int		sides;
		zREAL	dist = vob->GetPositionWorld() * node->plane.normal - node->plane.distance;
		if (dist > vob->GetRange()) sides = 1; else		// 1 front		// FIXME: richtig so ??
		if (dist <-vob->GetRange())	sides = 2; else		// 2 back
									sides = 3;

		// Folgendes ist noetig, da Polys in versch. Leafs sich befinden koennen, allerdings beim ersten auftreffen
		// gerendert werden. Hierbei koennten ohne das Folgende Lights fuer ein Poly verlorengehen
		if (sides==1) {
			zCBspNode *node2= (zCBspNode*)node->back;
			if ((node2) && (vob->GetBBox3DWorld().IsIntersecting (node2->bbox3D))) sides=3;
		} else 
		if (sides==2) {
			zCBspNode *node2= (zCBspNode*)node->front;
			if ((node2) && (vob->GetBBox3DWorld().IsIntersecting (node2->bbox3D))) sides=3; 
		};

		switch (sides) {
		case 1:
			node = (zCBspNode*)node->front;
			break;
		case 2:
			node = (zCBspNode*)node->back;
			break;
		case 3:
			if (node->front) node->front->AddVobLightToLeafs (vob);
			node = (zCBspNode*)node->back;
			break;
		};
	};
};


void zCCFASTCALL zCBspBase::RemoveVobFromLeafs (zCVob* vob) 
{
	if (vob->GetVobType()==zVOB_TYPE_LIGHT) 
	{
		// light
		for (int i=0; i<vob->vobLeafList.GetNum(); i++) {
			vob->vobLeafList[i]->lightVobList.RemoveOrder ((zCVobLight*)vob); 
		};
	} else 
	{
		for (int i=0; i<vob->vobLeafList.GetNum(); i++) {
			vob->vobLeafList[i]->leafVobList.Remove (vob); 
		};
	};
	vob->vobLeafList.EmptyList();
};

void zCBspTree::RemoveVob (zCVob* vob) {
	zERR_ASSERT	(bspRoot);
	bspRoot->RemoveVobFromLeafs	(vob);
};

void zCBspTree::AddVob (zCVob* vob) 
{
	zERR_ASSERT	(bspRoot);
	AdjustVob	(vob);
};

void zCBspTree::AdjustVob (zCVob* vob) 
{
#ifdef LEAF_NO_VOBS
	return;
#endif
	zERR_ASSERT	(bspRoot);
	if (vob->GetVobType()==zVOB_TYPE_LIGHT) 
	{
		// Dyn-Lights werden nur jeden 2. Frame geupdated
		if (((bspFrameCtr&1)==1) || (vob->vobLeafList.GetNum()==0) || (((zCVobLight*)vob)->GetCanMove()==TRUE)) 
		{
			bspRoot->RemoveVobFromLeafs		(vob);
			bspRoot->AddVobLightToLeafs		((zCVobLight*)vob);

			// folgender Aufruf darf auch im Game/Engine, nur um hier im Augenblick SICHER zu gehen, dass keine
			// Game Runtime Perf-Verluste entstehen
			#ifdef COMPILING_SPACER
				//this->CalcStaticLeafLightData	();
			#endif
		};
	} else 
	{
		//if (((bspFrameCtr&2)==1) || (vob->vobLeafList.GetNum()==0))
		{
			bspRoot->RemoveVobFromLeafs	(vob);
			bspRoot->AddVobToLeafs		(vob);
		};
	};
};
 
void zCCFASTCALL zCBspBase::CollectVobsSubtree (zCArray<zCVob*>& resVobList) const
{
	bspCollectCtr++;
	CollectVobsSubtree_I (resVobList);
};

void zCCFASTCALL zCBspBase::CollectVobsInBBox3D (zCArray<zCVob*>& resVobList, const zTBBox3D& inbbox3D) const
{
	bspCollectCtr++;
	CollectVobsInBBox3D_I (resVobList, inbbox3D);
};

void zCCFASTCALL zCBspBase::CollectVobsSubtree_I (zCArray<zCVob*>& resVobList) const 
{
	// alle Vobs des Subtrees sammeln
	// ACHTUNG: bspFrameCtr
	// ACHTUNG: es werden keine Lights eingesammelt !!
	zDWORD collectCtr = bspCollectCtr;

	if (IsLeaf()) 
	{
		zCBspLeaf *leaf = (zCBspLeaf*)this;
tr_numLeafVobs += leaf->leafVobList.GetNum();
		if (leaf->leafVobList.GetNum()<=0) return;
		int		j=0;
		zCVob	*vob;
		do 
		{
			vob = leaf->leafVobList[j];
			if (vob->lastTimeCollected!=collectCtr) 
			{
				resVobList.Insert (vob);
				vob->lastTimeCollected = collectCtr;						// FIXME: VTUNE bottleneck, cache-miss?
			};
			j++;
		} while (j<leaf->leafVobList.GetNum());
	} else 
	{
		zCBspNode *node = (zCBspNode*)this;
		for (int i=0; i<node->numLeafs; i++) 
		{
			zCBspLeaf	*leaf	= &(node->leafList[i]);
			int			max		= leaf->leafVobList.GetNumInList();
			for (int j=0; j<max; j++) 
			{
				zCVob *vob = leaf->leafVobList[j];

				if (vob->lastTimeCollected!=collectCtr) 
				{
					vob->lastTimeCollected = collectCtr;
					resVobList.Insert (vob);
				};
			};
		};
	};
};

void zCCFASTCALL zCBspBase::CollectLightVobsSubtree (zCArray<zCVob*>& resVobList) const
{
	bspCollectCtr++;
	CollectLightVobsSubtree_I (resVobList);
};

void zCCFASTCALL zCBspBase::CollectLightVobsSubtree_I (zCArray<zCVob*>& resVobList) const 
{
	// alle Vobs des Subtrees sammeln
	// ACHTUNG: bspFrameCtr
	// ACHTUNG: es werden NUR Lights eingesammelt !!

	zDWORD collectCtr = bspCollectCtr;

	if (IsLeaf()) 
	{
		zCBspLeaf *leaf = (zCBspLeaf*)this;
tr_numLeafVobs += leaf->lightVobList.GetNum();
		if (leaf->lightVobList.GetNum()<=0) return;
		int		j=0;
		zCVob	*vob;
		do 
		{
			vob = leaf->lightVobList[j];
			if (vob->lastTimeCollected!=collectCtr) 
			{
				resVobList.Insert (vob);
				vob->lastTimeCollected = collectCtr;						// FIXME: VTUNE bottleneck, cache-miss?
			};
			j++;
		} while (j<leaf->lightVobList.GetNum());
	} else 
	{
		zCBspNode *node = (zCBspNode*)this;
		for (int i=0; i<node->numLeafs; i++) 
		{
			zCBspLeaf	*leaf	= &(node->leafList[i]);
			int			max		= leaf->lightVobList.GetNumInList();
			for (int j=0; j<max; j++) 
			{
				zCVob *vob = leaf->lightVobList[j];
				if (vob->lastTimeCollected!=collectCtr) 
				{
					vob->lastTimeCollected = collectCtr;
					resVobList.Insert (vob);
				};
			};
		};
	};
};

void zCCFASTCALL zCBspBase::CollectVobsInBBox3D_I (zCArray<zCVob*>& resVobList, const zTBBox3D& inbbox3D) const 
{
	// ACHTUNG: bspFrameCtr
	// ACHTUNG: es werden keine Lights eingesammelt !!

	zCBspNode *node = (zCBspNode*)this;
	while (node) 
	{
		if (node->IsLeaf()) 
		{
			// Leaf
			zCBspLeaf *leaf = (zCBspLeaf*)node;
			for (int j=0; j<leaf->leafVobList.GetNumInList(); j++) 
			{
				zCVob *vob = leaf->leafVobList[j];

				if ((vob->lastTimeCollected!=bspCollectCtr) && 
					(inbbox3D.IsIntersecting (vob->bbox3D)))
				{
					vob->lastTimeCollected = bspCollectCtr;
					resVobList.Insert (vob);
				};
			};
			return;
		};

		int sides;
		sides = inbbox3D.ClassifyToPlane (node->plane.distance, node->planeSignbits);
//		if (node->planeSignbits>=128)	sides = inbbox3D.ClassifyToPlane (node->plane.distance, node->planeSignbits & 3);
//		else							sides = inbbox3D.ClassifyToPlane (node->plane, node->planeSignbits);
		switch (sides) 
		{
			case zPLANE_INFRONT:
				node = (zCBspNode*)node->front;
				break;
			case zPLANE_BEHIND:
				node = (zCBspNode*)node->back;
				break;
			case zPLANE_SPANNING:
				if (node->front) node->front->CollectVobsInBBox3D_I (resVobList, inbbox3D);
				node = (zCBspNode*)node->back;
				break;
		};
	};
};

void zCCFASTCALL zCBspLeaf::TraceRayCollectVobs (zCArray<zCVob*>& resVobList, const zTBBox3D& rayBBox, int traceFlags) const 
{
	// ACHTUNG: bspFrameCtr

	zDWORD collectCtr = bspCollectCtr;

	if (leafVobList.GetNum()>0) 
	{
		tr_numLeafVobs += leafVobList.GetNum();
		if (traceFlags & zTRACERAY_VOB_TEST_HELPER_VISUALS)
		{
			// falls auch gegen Helper-Visuals getestet werden soll, wird kein ray/vob bbox test durchgefuehrt
			for (int j=0; j<leafVobList.GetNum(); ++j)
			{
				zCVob *vob = leafVobList[j];

				if (vob->lastTimeCollected!=collectCtr)
				{
					resVobList.Insert (vob);
					vob->lastTimeCollected = collectCtr;
				};
			};
		} else 
		{
			int		j=0;
			zCVob	*vob;
			do 
			{
				vob = leafVobList[j];

				if ((vob->lastTimeCollected!=collectCtr) &&
					(vob->GetBBox3DWorld().IsIntersecting (rayBBox)))
				{
					resVobList.Insert (vob);
					vob->lastTimeCollected = collectCtr;						// FIXME: VTUNE bottleneck, cache-miss?
				};
				++j;
			} while (j<leafVobList.GetNum());
		};
	};

	// lights ?
	if (traceFlags & zTRACERAY_VOB_TEST_HELPER_VISUALS)
	if (lightVobList.GetNum()>0) 
	{
		int		j=0;
		do 
		{
			zCVob *vob = lightVobList[j];
			if (vob->lastTimeCollected!=collectCtr)
			{
				resVobList.Insert (vob);
				vob->lastTimeCollected = collectCtr;
			};
			++j;
		} while (j<lightVobList.GetNum());
	};
};

zCBspLeaf* zCBspBase::FindLeaf (const zPOINT3& point) 
{
	zCBspBase* bspNode = this;
	while (!bspNode->IsLeaf()) 
	{
		if (((zCBspNode*)bspNode)->plane.ClassifyPoint (point)==zPLANE_BEHIND) 
			bspNode = ((zCBspNode*)bspNode)->back; else
			bspNode = ((zCBspNode*)bspNode)->front;
		if (bspNode==0) return 0;
	};
	return (zCBspLeaf*)bspNode;
};

zTBBox3D zCBspTree::CalcLeafRealBBox3D (const zPOINT3& point) 
{
	zCBspBase*	bspNode = GetRoot();
	zTBBox3D	box		= GetRoot()->bbox3D;
	
	while (!bspNode->IsLeaf()) 
	{
		zCBspNode* node = (zCBspNode*)bspNode;
		
		int axis = node->planeSignbits;

		if (((zCBspNode*)bspNode)->plane.ClassifyPoint (point)==zPLANE_BEHIND) 
		{
			box.maxs[axis]	= node->plane.distance;
			bspNode			= ((zCBspNode*)bspNode)->back; 
		} 
		else 
		{
			box.mins[axis]	= node->plane.distance;
			bspNode			= ((zCBspNode*)bspNode)->front;
		}
		if (bspNode==0) return box;
	};
	return box;
};


// *******************************************************************************************************************
// *******************************************************************************************************************

static zCArray<zCVob*>	*traceRayVobList=0;
static zCPolygon		*traceRayHitPoly;
static zREAL			 traceRayHitAlpha;				// noch nicht im Betrieb
static zBOOL			 traceRayFindStatPoly;
static zBOOL			 traceRayIgnoreTranspPoly;
static zBOOL			 traceRayIgnoreWaterPoly;
static zBOOL			 traceRayIgnorePortals;
static zBOOL			 traceRayIgnoreStatPoly;
static zTBBox3D			 traceRayBBox;
static int				 traceRayFlags;

static zCRayCache       *s_RayCache=NULL; // der Cache, den CheckRayAgainstPolysCache verwendet

// Rays, die gegen die Polys getestet werden, werden um diesen Faktor verlaengert.
#define zTRACE_RAY_UPSCALE	zREAL(1.001F)

zBOOL zCCFASTCALL zCBspBase::CheckRayAgainstPolys (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters, zCRayTurbo* a_pRayTurbo) const 
{
//	const zREAL ALPHA_EPS= 0.031F;
//	const zREAL ALPHA_EPS= 0.001F;
//	const zREAL ALPHA_EPS= 0.0001F;				// FIXME ?

//	if (numPolys<=0) return FALSE;				// sollte kaum vorkommen
//	zVEC3	ray			= (end-start)*2;				// EVIL !
	if (numPolys== 0) return FALSE;

	zVEC3	ray			= (end-start)*zTRACE_RAY_UPSCALE;			// muss sein ! (1.01??), 1.001F reicht nicht
	zREAL	alpha;
	zBOOL	twoSided	= (traceRayFlags & zTRACERAY_POLY_2SIDED);

	
	if(NULL == a_pRayTurbo)
	{
		for (int i=0; i<numPolys; i++) 
		{
			zCPolygon* const &poly = polyList[i];
			zBOOL hit;
			if (twoSided)	hit	= poly->CheckRayPolyIntersection2Sided	(start, ray, inters, alpha);
			else			hit	= poly->CheckRayPolyIntersection		(start, ray, inters, alpha);
			if (hit) 
			{
				// FIXME: falls die Poly-Suppe eines Leafs NICHT KONVEX ist, dann muss
				//        auch noch DER NEARESTHIT gesucht werden !
				// FIXME: alpha-Check nicht hier ... oder ?
				if (traceRayIgnorePortals) {
					if (poly->IsPortal()) continue;
				};

				const zCMaterial *mat = poly->GetMaterial();
				if (mat->GetMatGroup()==zMAT_GROUP_WATER)
				{
					if (traceRayIgnoreWaterPoly)							continue;
				} else {
					if (traceRayIgnoreTranspPoly) {
						if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE) continue;
						if (mat->GetTexture())
						if (mat->GetTexture()->HasAlphaChannel())			continue;
					};
				};

				if (mat->GetNoCollDet() && !g_bIsInCompileLightMode)		continue;
	//			if (alpha<= 1 + ALPHA_EPS) {
					traceRayHitPoly = poly;
	//				if (alpha>=1) inters = end; 
					return TRUE;
	//			};
			};
		};
	}
	else
	{
		//
		// RAY TURBO
		//
		static zCMeshOctreeNode::zCArrPolys ms_arrPolys;
		a_pRayTurbo->CalculateOptimizedPolyList( ms_arrPolys );

		for (int j = 0; j < ms_arrPolys.GetNum(); j++) 
		{
			zCPolygon* const &poly	=	ms_arrPolys[j];
			zBOOL hit;
			if (twoSided)	hit	= poly->CheckRayPolyIntersection2Sided	(start, ray, inters, alpha);
			else			hit	= poly->CheckRayPolyIntersection		(start, ray, inters, alpha);
			if (hit) 
			{
				// FIXME: falls die Poly-Suppe eines Leafs NICHT KONVEX ist, dann muss
				//        auch noch DER NEARESTHIT gesucht werden !
				// FIXME: alpha-Check nicht hier ... oder ?
				if (traceRayIgnorePortals) {
					if (poly->IsPortal()) continue;
				};

				const zCMaterial *mat = poly->GetMaterial();
				if (mat->GetMatGroup()==zMAT_GROUP_WATER)
				{
					if (traceRayIgnoreWaterPoly)							continue;
				} else {
					if (traceRayIgnoreTranspPoly) {
						if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE) continue;
						if (mat->GetTexture())
						if (mat->GetTexture()->HasAlphaChannel())			continue;
					};
				};

				if (mat->GetNoCollDet() && !g_bIsInCompileLightMode)		continue;
	//			if (alpha<= 1 + ALPHA_EPS) {
					traceRayHitPoly = poly;
	//				if (alpha>=1) inters = end; 
					return TRUE;
	//			};
			};
		};
	}
	return FALSE;
};

zBOOL zCCFASTCALL zCBspBase::CheckRayAgainstPolysNearestHit (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters, zCRayTurbo* a_pRayTurbo) const 
{
//	if (numPolys<=0) return FALSE;					// sollte kaum vorkommen
	// offset noetig, da start/end bereits an den Bsp-ClipPlanes geclippt worden sind, in denen auch die Polys liegen.
	// Ohne Offset hoert der Ray genau/kurz vor dem Poly auf.
	if (numPolys==0) return FALSE;

	const zVEC3	ray			= (end-start)*zTRACE_RAY_UPSCALE;			// muss sein ! (1.01??), 1.001F reicht nicht
	zREAL		alpha;
	zPOINT3		bestInters;
	zREAL		bestAlpha	= 9999;
	zCPolygon	*bestPoly	= 0;
	zBOOL		twoSided	= (traceRayFlags & zTRACERAY_POLY_2SIDED);

	if(NULL == a_pRayTurbo)
	{
		for (int i=0; i<numPolys; i++) 
		{
			zCPolygon* const &poly = polyList[i];
			zBOOL hit;
			if (twoSided)	hit	= poly->CheckRayPolyIntersection2Sided	(start, ray, inters, alpha);
			else			hit	= poly->CheckRayPolyIntersection		(start, ray, inters, alpha);
			if (hit) 
			{
				// FIXME: falls die Poly-Suppe eines Leafs NICHT KONVEX ist, dann muss
				//        auch noch DER NEARESTHIT gesucht werden !
				// FIXME: alpha-Check nicht hier ... oder ?
				if (alpha<bestAlpha) {
					// hier ist die Tests, ob das Poly evtl. rausgefiltert werden soll 
					// (das ist nur bei relativ wenigen der Fall)
					if (traceRayIgnorePortals) {
						if (poly->IsPortal()) continue;
					};
					const zCMaterial *mat = poly->GetMaterial();
					if (mat->GetMatGroup()==zMAT_GROUP_WATER)
					{
						if (traceRayIgnoreWaterPoly)							continue;
					} else {
						if (traceRayIgnoreTranspPoly) {
							if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE) continue;
							if (mat->GetTexture())
							if (mat->GetTexture()->HasAlphaChannel())			continue;
						};
					};
					if (mat->GetNoCollDet() && !g_bIsInCompileLightMode)		continue;
					bestPoly	= poly;
					bestAlpha	= alpha;
					bestInters	= inters;
				};
			};
		};

	}
	else
	{
		//
		// RAY TURBO
		//
		static zCMeshOctreeNode::zCArrPolys ms_arrPolys;
		a_pRayTurbo->CalculateOptimizedPolyList( ms_arrPolys );

		for (int j = 0; j < ms_arrPolys.GetNum(); j++) 
		{
			zCPolygon* const &poly	=	ms_arrPolys[j];

			zBOOL hit;
			if (twoSided)	hit	= poly->CheckRayPolyIntersection2Sided	(start, ray, inters, alpha);
			else			hit	= poly->CheckRayPolyIntersection		(start, ray, inters, alpha);
			if (hit) 
			{
				// FIXME: falls die Poly-Suppe eines Leafs NICHT KONVEX ist, dann muss
				//        auch noch DER NEARESTHIT gesucht werden !
				// FIXME: alpha-Check nicht hier ... oder ?
				if (alpha<bestAlpha) {
					// hier ist die Tests, ob das Poly evtl. rausgefiltert werden soll 
					// (das ist nur bei relativ wenigen der Fall)
					if (traceRayIgnorePortals) {
						if (poly->IsPortal()) continue;
					};
					const zCMaterial *mat = poly->GetMaterial();
					if (mat->GetMatGroup()==zMAT_GROUP_WATER)
					{
						if (traceRayIgnoreWaterPoly)							continue;
					} else {
						if (traceRayIgnoreTranspPoly) {
							if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE) continue;
							if (mat->GetTexture())
							if (mat->GetTexture()->HasAlphaChannel())			continue;
						};
					};
					if (mat->GetNoCollDet() && !g_bIsInCompileLightMode)		continue;
					bestPoly	= poly;
					bestAlpha	= alpha;
					bestInters	= inters;
				};
			};
		};
	}
	
	if (bestAlpha<9999) {
		traceRayHitPoly = bestPoly;
		inters			= bestInters;
		return TRUE;
	};
	return FALSE;
};


/* ----------------------------------------------------------------------
	
    zCBspTree::CheckRayAgainstPolysCache()

	21.09.2000	[Moos]	
                Erzeugt (von Check...NearestHit kopiert);
                verwendet RayCache-Mechanismus

   ---------------------------------------------------------------------- */

// #define CHECKCACHE

zBOOL zCCFASTCALL zCBspBase::CheckRayAgainstPolysCache (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters) const 
{
//	if (numPolys<=0) return FALSE;					// sollte kaum vorkommen
	// offset noetig, da start/end bereits an den Bsp-ClipPlanes geclippt worden sind, in denen auch die Polys liegen.
	// Ohne Offset hoert der Ray genau/kurz vor dem Poly auf.
	if (numPolys == 0) return FALSE;
	const zVEC3	ray = (end-start)*zTRACE_RAY_UPSCALE;			// muss sein ! (1.01??), 1.001F reicht nicht
	zREAL		alpha;
	zPOINT3		bestInters;
	zREAL		bestAlpha	= 9999;
	zCPolygon	*bestPoly	= 0;


    zERR_ASSERT(s_RayCache);
    s_RayCache->NextNode(this);
    zCArray<zWORD> &hit_list = s_RayCache->HitList();


#ifdef CHECKCACHE
    char *hit = s_RayCache->Hit();
        
    for (int j=numPolys-1;j>=0;j--){
        zBOOL Hit = polyList[j]->CheckRayPolyIntersection (start, ray, inters, alpha);
        zERR_ASSERT_STRICT ( hit[j] || !Hit );
    }
#endif

	for (int i=hit_list.GetNum()-1; i>=0; i--) {
		zCPolygon* const &poly = polyList[hit_list[i]];

		if (poly->CheckRayPolyIntersection (start, ray, inters, alpha)) 
		{
			// FIXME: falls die Poly-Suppe eines Leafs NICHT KONVEX ist, dann muss
			//        auch noch DER NEARESTHIT gesucht werden !
			// FIXME: alpha-Check nicht hier ... oder ?
			if (alpha<bestAlpha || !traceRayFindStatPoly) {
				// hier ist die Tests, ob das Poly evtl. rausgefiltert werden soll 
				// (das ist nur bei relativ wenigen der Fall)
				if (traceRayIgnorePortals) {
					if (poly->IsPortal()) continue;
				};
				const zCMaterial *mat = poly->GetMaterial();
				if (mat->GetMatGroup()==zMAT_GROUP_WATER)
				{
					if (traceRayIgnoreWaterPoly)							continue;
				} else {
					if (traceRayIgnoreTranspPoly) {
						if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE) continue;
						if (mat->GetTexture())
						if (mat->GetTexture()->HasAlphaChannel())			continue;
					};
				};
				if (mat->GetNoCollDet() && !g_bIsInCompileLightMode)		continue;
				bestPoly	= poly;

                if (!traceRayFindStatPoly)
                    return TRUE;

				bestAlpha	= alpha;
				bestInters	= inters;
			};
		};
	};
	if (bestAlpha<9999) {
		traceRayHitPoly = bestPoly;
		inters			= bestInters;
		return TRUE;
	};
	return FALSE;
};

/* ----------------------------------------------------------------------
	
    zCBspTree::RayIntersection()

	21.09.2000	[Moos]	
                RayCache-Aufruf hinzugefügt

   ---------------------------------------------------------------------- */

zBOOL zCCFASTCALL zCBspBase::RayIntersection (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters) const 
{ 
	// return TRUE		=> intersection, output = end
	// 1/32 epsilon to keep floating point happy
//	const zREAL DIST_EPSILON = (1.0F / 32.0F);
	const zREAL DIST_EPSILON = 0.0001F;


	g_iNumTraversals++;

	zCBspNode *node = (zCBspNode*)this;
	
	//
	// @DEVNOTE: @CHANGED HOELLER -> SPATIAL INFORMATION FOR POLYGONS
	//
	inters			= end;					// muss das sein ?

	while (node) 
	{

		if (node->IsLeaf()) 
		{

			// Leaf erreicht, 2 Moeglichkeiten:
			// a) leafy-Bsp		: Ray ist ok & es liegt keine Intersection vor
			// b) octree-leaf	: Der Ray muss noch gegen alle Polys gecheckt werden
			// Strahl gegen alle Polys checken.. und raus.
			tr_numLeafs++;
			
			// Vobs einsammeln
			if (traceRayVobList)
				((zCBspLeaf*)node)->TraceRayCollectVobs (*traceRayVobList, traceRayBBox, traceRayFlags);

			// early recjection: ist Ray komplett oberhalb der Node-BBox ? 
			// (die BBox bezieht sich auf die statischen Polys, deshalb muessen die Vob-Tests vorher, damit keine davon durch die Lappen gehen)
			
			if ((end[VY] > node->bbox3D.maxs[VY]) && (start[VY] > node->bbox3D.maxs[VY])) 
				return FALSE;

			// Polys checken & einsammeln
			if (traceRayIgnoreStatPoly)	
				return FALSE;
			
			tr_numLeafPolys += node->numPolys;

            if (s_RayCache)					
				return node->CheckRayAgainstPolysCache      ( start, end, inters );
			else 
				if (traceRayFindStatPoly)  
					return node->CheckRayAgainstPolysNearestHit ( start, end, inters, zCRayTurboAdmin::GetInstance().GetOrCreate( node ) ); 
					//return node->CheckRayAgainstPolysNearestHit ( start, end, inters ); 
				else                            
					//return node->CheckRayAgainstPolys           ( start, end, inters, zCRayTurboAdmin::GetInstance().GetOrCreate( node ) );		// FIXME: ok so ?
					return node->CheckRayAgainstPolys           ( start, end, inters );		// FIXME: ok so ?
			return FALSE;
		};

		// oder: zTPlane::ClassifyPoint
		
		const int	signBitsAxis= node->planeSignbits;
		const zREAL	dist1		= start[signBitsAxis] - node->plane.distance;
		const zREAL	dist2		= end  [signBitsAxis] - node->plane.distance;

//		zREAL dist1 = node->plane.normal * start - node->plane.distance;
//		zREAL dist2 = node->plane.normal * end   - node->plane.distance;

		// both in front of plane 

		if ((dist1>=0) && (dist2>=0)) 
		{
			node	=	static_cast<zCBspNode*> (node->front);
			if (0 == node) 
				return FALSE; 		// inters = end
		} 
		else
		// both behind plane
		if ((dist1 < 0) && (dist2 < 0)) 
		{
			node	=	static_cast<zCBspNode*> (node->back);  
			if (0 == node)  
				return FALSE;		// inters = end
		} 
		else 
		{
			// Ray is cut by split-Plane
			const zVEC3&	ray		=	end - start;
			const zREAL		dn		=	ray[signBitsAxis];
			const zREAL		alpha	=	(node->plane.distance - (start[signBitsAxis])) / dn;
			const zPOINT3&	mid		=	start + alpha*ray;

			zPOINT3			split1	=	mid;	split1[signBitsAxis] += DIST_EPSILON;
			zPOINT3			split2	=	mid;	split2[signBitsAxis] -= DIST_EPSILON;
			
			if (dist1>=0) 
			{ 
				// If start in front of plane
				if (node->front)	
				{
					if (node->front->RayIntersection (start, split1, inters))
						return TRUE;
				}
				if (node->back)		
				{
					if (node->back ->RayIntersection ( split2, end, inters ))	
						return TRUE;
					
				}
				return FALSE;
			} 
			else 
			{
				if (dist1<0) 
				{
					//else If start behind plane
					if (node->back)		
					{
						if (node->back ->RayIntersection ( start, split1, inters ))
							return TRUE;
					}
					if (node->front)	
					{
						if (node->front->RayIntersection ( split2, end, inters ))	
							return TRUE;
					}
					return FALSE;
				}
			}
		};
	};
	return FALSE;
};


/* ----------------------------------------------------------------------
	
    zCBspTree::TraceRay()

	21.09.2000	[Moos]	
                der RayCache wird zurückgesetzt

   ---------------------------------------------------------------------- */



zBOOL zCBspTree::TraceRay (const zPOINT3&	start, 
						   const zPOINT3&	end, 
						   const int		traceFlags,
						   zPOINT3&			inters, 
						   zCPolygon*		&hitPoly, 
						   zCArray<zCVob*>	*vobList) const 
{ 
	if (vobList) vobList->EmptyList();
	traceRayVobList			= vobList; 
	// Flags
	// um transpPolys zu erkennen muessen erstmal auch die Polys gecheckt werden..
	traceRayIgnoreTranspPoly= (traceFlags & zTRACERAY_POLY_IGNORE_TRANSP);
	traceRayIgnoreWaterPoly	=!(traceFlags & zTRACERAY_POLY_TEST_WATER);
	traceRayFindStatPoly	= (traceFlags & zTRACERAY_STAT_POLY) | traceRayIgnoreTranspPoly;
	traceRayIgnorePortals	=!(traceFlags & zTRACERAY_STAT_PORTALS);
	traceRayIgnoreStatPoly	= (traceFlags & zTRACERAY_STAT_IGNORE);
	traceRayFlags			= traceFlags;
	traceRayHitPoly			= 0;

	traceRayBBox.Init		();
	traceRayBBox.AddPoint	(start);
	traceRayBBox.AddPoint	(end);

	// @ugly global static tracing vector for octree scan
	g_vecStartTrace	=	start;
	g_vecEndTrace	=	end;

	// WICHTIG ! damit schnell geprueft werden kann, ob ein Vob bereits eingesammelt worden ist
	// (=> 	CollectVobsSubtree(), CollectVobsInBBox3D()
	bspCollectCtr++;

	//
	zBOOL result;

			
    if (s_RayCache) s_RayCache->StartTraceRay(start, end); // [Moos]

	g_iNumTraversals	=	0;
	result = GetRoot()->RayIntersection	(start, end, inters);
	
	//	if (GetBspTreeMode()==zBSP_MODE_OUTDOOR) 	result = GetRoot()->RayIntersectionOutdoor (start, end, inters);
	//	else										result = GetRoot()->RayIntersectionIndoor  (start, end, inters);

    
	if (s_RayCache) s_RayCache->StopTraceRay(); // [Moos]

    s_RayCache = 0;  // [Moos] zurücksetzen, damit der nächste dumme TraceRay-Aufruf nicht einen wichtigen (oder schon gelöschten) Cache verwendet

	hitPoly					= traceRayHitPoly;
	traceRayVobList			= 0;

	zengineStats.numTraceRay++;

	return result;
};



/* ----------------------------------------------------------------------
	
    zCBspTree::SetCache()

	21.09.2000	[Moos]	
                Erzeugt; für den RayCache-Mechanismus

   ---------------------------------------------------------------------- */


void zCBspTree::SetRayCache(zCRayCache *cache){
    s_RayCache=cache;
}


// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************

zBOOL zCCBspNode::CheckRayAgainstPolysNearestHit (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters, zCRayTurbo* a_pRayTurbo) const 
{
//	const zREAL ALPHA_EPS= 0.0001F;				// FIXME ?????????????????

	zERR_ASSERT( this == NULL );

	if (polyList.GetNumInList()<=0) return FALSE;
	zVEC3		ray = (end-start)*1.01F;			// muss sein ! (1.01??), 1.001F reicht nicht
	zREAL		alpha;
	zPOINT3		bestInters;
	zREAL		bestAlpha	= 9999;
	zCPolygon	*bestPoly	= 0;

//	for (int i=0; i<polyList.GetNumInList(); i++) {
//		zCPolygon* const &poly = (polyList.Get(i)->poly);
	for (zTPolyNode *node = polyList.Get(0); node; node =node->next) {
		zCPolygon* const &poly = (node->poly);
//if (poly->IsPortal()) continue;
		if (poly->CheckRayPolyIntersection (start, ray, inters, alpha)) {
			if (alpha<bestAlpha) {
				bestPoly	= poly;
				bestAlpha	= alpha;
				bestInters	= inters;
			};
		};
	};
	if (bestAlpha<9999) {
		traceRayHitPoly = bestPoly;
		inters			= bestInters;
		return TRUE;
	};
	return FALSE;
};

zBOOL zCCBspNode::RayIntersectionOctree (const zPOINT3& start, const zPOINT3& end, zPOINT3& inters)  
{
	// return TRUE		=> intersection, output = end
	// 1/32 epsilon to keep floating point happy
//	const zREAL DIST_EPSILON = (1.0F / 32.0F);
	const zREAL DIST_EPSILON = 0.0001F;

	zCCBspNode *node	= this;
	inters				= end;					// muss das sein ?

	while (node) {
		if (node->IsLeaf()) {
			// Leaf erreicht, 2 Moeglichkeiten:
			// a) leafy-Bsp		: Ray ist ok & es liegt keine Intersection vor
			// b) octree-leaf	: Der Ray muss noch gegen alle Polys gecheckt werden
			// Strahl gegen alle Polys checken.. und raus.
			return node->CheckRayAgainstPolysNearestHit (start, end, inters); 
		};

		// oder: zTPlane::ClassifyPoint
		zREAL dist1 = node->plane.normal * start - node->plane.distance;
		zREAL dist2 = node->plane.normal * end   - node->plane.distance;

		// both in front of plane 
		if ((dist1>=0) && (dist2>=0)) {
			node = node->front;
			if (node==0) { return TRUE; }		// inters = end
		} else

		// both behind plane
		if ((dist1<0) && (dist2<0)) {
			node = node->back;  
			if (node==0) { return TRUE; }		// inters = end
		} else {
			// Ray is cut by split-Plane
			zPOINT3 offs, mid, split1, split2;

			// FIXME: schneller ist es hier manuell...
			node->plane.Intersection(start, end-start, mid);
			offs	= DIST_EPSILON * node->plane.normal;
			split1	= mid + offs;
			split2	= mid - offs;

			if (dist1>=0) { 
				// If start in front of plane
				if (node->front)	if (node->front->RayIntersectionOctree(start, split1, inters))return TRUE;
				if (node->back)		if (node->back ->RayIntersectionOctree(split2, end, inters))	return TRUE;
				return FALSE;
			} else if (dist1<0) {
				//else If start behind plane
				if (node->back)		if (node->back ->RayIntersectionOctree(start, split1, inters))return TRUE;
				if (node->front)	if (node->front->RayIntersectionOctree(split2, end, inters))	return TRUE;
				return FALSE;
			}
		};
	};
	return FALSE; 
};

zBOOL zCCBspNode::TraceRay (const zPOINT3& start, const zPOINT3& end, zCPolygon* &hitPoly, zVEC3& inters) { 

	// FIXME: soll das so hier ??? warum nur 'Octree'-Test ???
	// um transpPolys zu erkennen muessen erstmal auch die Polys gecheckt werden..

	traceRayHitPoly	= 0;
	zBOOL result	= RayIntersectionOctree (start, end, inters);
	hitPoly			= traceRayHitPoly;
	return result;
};

zBOOL zCCBspNode::TraceRay (const zPOINT3& start, const zPOINT3& end, zCPolygon* &hitPoly) { 
	// FIXME: soll das so hier ??? warum nur 'Octree'-Test ???
	zPOINT3 inters;
	return TraceRay(start, end, hitPoly, inters);
};

// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************


/*
void zCBspBase::CollectPolysInBBox3DRec () const {
	// Falls die aktuelle Node-BBox die TestBox schneidet, wird entweder rekursiv weiter gesucht(Node) oder die
	// enthaltenen Polys in die Liste eingetragen(Leaf)

	// evtl. schneller special-Case fuer: NodeBBox komplett in testbbox3d enthalten ?
	// aber wann kommt denn das schon mal vor ???

	// FIXME	: besser die ctestbbox3D gegen die Split-Planes testen !!!!!!! (=> wie beim Frustum-Check !!)
	//			  oder: gegen die Portal-Node-Boxen checken (alle Portals eines Leafs als Grundlage der BBox)
	// ACHTUNG	: bei einem NICHT-SPLIT BSP koennen Polys MEHRMALS vorkommen !!! Problematisch ??

	// FIXME	: fuer die node->plane signbits verwenden, wie bei Quake1 in mathlic.b Box_On_Plane_Side()

	if (IsNode()) {
		zCBspNode *node = (zCBspNode*)this;
		switch (ctestbbox3D.ClassifyToPlane (node->plane)) {
		case zPLANE_INFRONT:
			if (node->front) node->front->CollectPolysInBBox3DRec ();
			break;
		case zPLANE_BEHIND:
			if (node->back ) node->back ->CollectPolysInBBox3DRec ();
			break;
		case zPLANE_SPANNING:
			if (node->front) node->front->CollectPolysInBBox3DRec ();
			if (node->back ) node->back ->CollectPolysInBBox3DRec ();
			break;
		};
	} else {
		if (numPolys>0) {
			// Leaf
			// Polys einsammeln
			// memcpy geht leider nicht, da portale rausgefiltert werden muessen..
			// FIXME: ..aber nur wenn zCBspTree::cfg_portalize auf TRUE ist !!!!!
			for (int i=0; i<numPolys; i++) {
if (polyList[i]->IsPortal()) continue;
				cfoundPolyList.Insert (polyList[i]);
			};
		};
	};
};
*/
void zCBspBase::CollectPolysInBBox3DRec () const 
{
	// Falls die aktuelle Node-BBox die TestBox schneidet, wird entweder rekursiv weiter gesucht(Node) oder die
	// enthaltenen Polys in die Liste eingetragen(Leaf)

	// evtl. schneller special-Case fuer: NodeBBox komplett in testbbox3d enthalten ?
	// aber wann kommt denn das schon mal vor ???

	// FIXME	: besser die ctestbbox3D gegen die Split-Planes testen !!!!!!! (=> wie beim Frustum-Check !!)
	//			  oder: gegen die Portal-Node-Boxen checken (alle Portals eines Leafs als Grundlage der BBox)
	// ACHTUNG	: bei einem NICHT-SPLIT BSP koennen Polys MEHRMALS vorkommen !!! Problematisch ??
	// FIXME	: fuer die node->plane signbits verwenden, wie bei Quake1 in mathlic.b Box_On_Plane_Side()

	zCBspNode *node = (zCBspNode*)this;
	while (node) {

		if (node->IsLeaf()) {
			zCBspLeaf *leaf = (zCBspLeaf*)node;
			if (leaf->numPolys>0) {
				// Leaf, Polys einsammeln 
				// BBox-Test
				if (!ctestbbox3D.IsIntersecting (node->bbox3D)) return;
				// memcpy geht leider nicht, da portale rausgefiltert werden muessen..
				// FIXME: ..aber nur wenn zCBspTree::cfg_portalize auf TRUE ist !!!!!

				for (int i=0; i<leaf->numPolys; i++) {
					zCPolygon *poly = leaf->polyList[i];
		if (poly->IsPortal()) continue;
					cfoundPolyList.Insert (poly);
				};
			};
			return;
		};

		int sides;
		sides = ctestbbox3D.ClassifyToPlane (node->plane.distance, node->planeSignbits);
//		if (node->planeSignbits>=128)	sides = ctestbbox3D.ClassifyToPlane (node->plane.distance, node->planeSignbits & 3);
//		else							sides = ctestbbox3D.ClassifyToPlane (node->plane, node->planeSignbits);
		switch (sides) {
//		switch (ctestbbox3D.ClassifyToPlane (node->plane, node->planeSignbits)) {
		case zPLANE_INFRONT:
			node = (zCBspNode*)node->front;
			break;
		case zPLANE_BEHIND:
			node = (zCBspNode*)node->back; 
			break;
		case zPLANE_SPANNING:
			if (node->front) node->front->CollectPolysInBBox3DRec ();
			node = (zCBspNode*)node->back;
			break;
		}; 
	};
};

zBOOL zCCFASTCALL zCBspBase::CollectPolysInBBox3D (const zTBBox3D& testbbox3D, zCPolygon**& foundPolyList, int& foundPolyNum) const 
{
	cfoundPolyList.EmptyList();
	ctestbbox3D				= testbbox3D;
	CollectPolysInBBox3DRec ();
	foundPolyList			= cfoundPolyList.GetArray();
	foundPolyNum			= cfoundPolyList.GetNumInList();
	return (foundPolyNum!=0);
};

// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************

void zCCBspNode::CollectPolysInBBox3DRec () 
{
	// Falls die aktuelle Node-BBox die TestBox schneidet, wird entweder rekursiv weiter gesucht(Node) oder die
	// enthaltenen Polys in die Liste eingetragen(Leaf)

	// evtl. schneller special-Case fuer: NodeBBox komplett in testbbox3d enthalten ?
	// aber wann kommt denn das schon mal vor ???

	// FIXME	: besser die ctestbbox3D gegen die Split-Planes testen !!!!!!! (=> wie beim Frustum-Check !!)
	//			  oder: gegen die Portal-Node-Boxen checken (alle Portals eines Leafs als Grundlage der BBox)
	// ACHTUNG	: bei einem NICHT-SPLIT BSP koennen Polys MEHRMALS vorkommen !!! Problematisch ??

	if (!IsLeaf()) {
		zCCBspNode *node = this;
		switch (ctestbbox3D.ClassifyToPlane (node->plane)) {
		case zPLANE_INFRONT:
			if (node->front) node->front->CollectPolysInBBox3DRec ();
			break;
		case zPLANE_BEHIND:
			if (node->back ) node->back ->CollectPolysInBBox3DRec ();
			break;
		case zPLANE_SPANNING:
			if (node->front) node->front->CollectPolysInBBox3DRec ();
			if (node->back ) node->back ->CollectPolysInBBox3DRec ();
			break;
		};
	} else {
		if (polyList.GetNumInList()>0) {
			// Leaf
			// Polys einsammeln
			// memcpy geht leider nicht, da portale rausgefiltert werden muessen..
			// FIXME: ..aber nur wenn zCBspTree::cfg_portalize auf TRUE ist !!!!!
			zTPolyNode *node = polyList.Get(0);
			while (node) {
				cfoundPolyList.Insert (node->poly);
				node = node->next;
			};
		};
	};
};

zBOOL zCCBspNode::CollectPolysInBBox3D (const zTBBox3D& testbbox3D, zCPolygon**& foundPolyList, int& foundPolyNum) {
	cfoundPolyList.EmptyList();
	ctestbbox3D		= testbbox3D;
	CollectPolysInBBox3DRec ();
	foundPolyList	= cfoundPolyList.GetArray();
	foundPolyNum	= cfoundPolyList.GetNumInList();
	return (foundPolyNum!=0);
/*	cfoundPolyNum	= 0;
	ctestbbox3D		= testbbox3D;
	CollectPolysInBBox3DRec ();
	foundPolyList	= cfoundPolyList;
	foundPolyNum	= cfoundPolyNum;
	return (cfoundPolyNum!=0);*/
};

// ****************************************************************************************************************
// ****************************************************************************************************************
// ****************************************************************************************************************

zBOOL zCBspTree::FindLeaks (zCArray<zCPolygon*>& leakPolyList) {

	// Polylist abgehen
	int numLeakPolys = 0;
	leakPolyList.EmptyList();
	for (int i=0; i<numPolys; i++) {
		zCPolygon* poly = treePolyList[i];
		if (poly->IsPortal()) continue;
		if (poly->GetMaterial())
		if (poly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER) continue;
			
		zPOINT3 center	= poly->GetCenter	();
		zVEC3	normal	= poly->GetNormal	();
		center = center - 1.0F * normal;
		if (FindLeaf (center)!=0) {
			numLeakPolys++;
			if (!leakPolyList.IsInList (poly))
				leakPolyList.Insert (poly);
		};
	};

	if (numLeakPolys>0) {
		zCMaterial *leakMat = zNEW(zCMaterial);
		leakMat->SetColor (0,255,0); 
		for (int i=0; i<leakPolyList.GetNumInList(); i++) {
			leakPolyList[i]->SetMaterial (leakMat);
		};
		zERR_WARNING ("D: RBSP: Leaks found, numLeakPolys: "+zSTRING(leakPolyList.GetNumInList()));
	} else 
		zERR_MESSAGE (3, 0, "D: RBSP: No Leaks found !");


	return numLeakPolys>0;
};



// **************************************************************************************************
//  Finding Occluder-Polys (zBSP_MODE_OUTDOOR)
// **************************************************************************************************

static int Compare_Occluder( const void *arg1, const void *arg2 ) 
{
	int poly1 = int(*((zCPolygon**) arg1));
	int poly2 = int(*((zCPolygon**) arg2));

	return (poly1-poly2);
};


void zCBspTree::MarkOccluderPolys () 
{
	zERR_MESSAGE (3, 0, "D: RBSP: Marking Occluder Polys...");

	int numOccluder=0;
	for (int i=0; i<mesh->numPoly; i++) {
		zCPolygon	*poly	= mesh->SharePoly(i);

		// Ghost-Occluder ?
		if (poly->GetGhostOccluder()) 
		{
			poly->SetOccluder (TRUE);
			continue;
		};

		// [EDENFELD] 1.09 Alle Polys, die ein Material mit noCollDet Flag 
		// auf TRUE gesetzt haben, sind _immer_ nicht-occluder
		// ausserdem: neue Material Eigenschaft "forceOccluder" eingeführt,
		// die alle Polys, die dieses Material benutzen automatisch zum Occluder 
		// werden lässt
		if (poly->GetMaterial())
		{
			if (poly->GetMaterial()->GetNoCollDet(TRUE))
			{
				poly->SetOccluder (FALSE); 
				continue;
			}
			else if (poly->GetMaterial()->GetOccluder())
			{
				poly->SetOccluder (TRUE); 
				//continue;
			};
		};


		if ((poly->polyPlane.normal[VY]<-0.01F) || (poly->polyPlane.normal[VY]>0.8F)) 
		{ 
			poly->SetOccluder (FALSE); 
			continue; 
		};

		if (poly->GetMaterial()->GetTexture())
			poly->GetMaterial()->GetTexture()->CacheIn(-1);

		if (poly->GetMaterial()->GetTexture() && poly->GetMaterial()->GetTexture()->HasAlpha())
		{
			poly->SetOccluder (FALSE); 
			continue; 
		}

		if (poly->GetMaterial()->GetAlpha()<255)
		{
			poly->SetOccluder (FALSE); 
			continue; 
		}

		if (poly->GetMaterial()->GetAlphaBlendFunc()>zRND_ALPHA_FUNC_NONE)
		{
			poly->SetOccluder (FALSE); 
			continue; 
		}

		if (poly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER)
		{
			poly->SetOccluder (FALSE); 
			continue; 
		}
	
		zCPolygon**	foundPolyList;
		int			foundPolyNum;
		zTBBox3D	polyBBox = poly->GetBBox3D(); 

		// Alle Polys aus der nahen Umgebung einsammeln
		zTBBox3D searchBox = polyBBox;
		const zREAL INC = zREAL(1.0F);
		if (searchBox.mins[VX]==searchBox.maxs[VX])		{ searchBox.mins[VX] -= INC; searchBox.maxs[VX] += INC; };
		if (searchBox.mins[VZ]==searchBox.maxs[VZ])		{ searchBox.mins[VZ] -= INC; searchBox.maxs[VZ] += INC; };
		searchBox.Scale (zREAL(1.2F));		// scale x/z
		searchBox.mins[VY] = -999999;
		searchBox.maxs[VY] = +999999;

		zBOOL		occluder= TRUE;
#ifdef zBSP_FAST_MARK_OCCLUDER
	if (0)
#endif
		{
			GetRoot()->CollectPolysInBBox3D (searchBox, foundPolyList, foundPolyNum);
			for (int j=0; j<foundPolyNum; j++) {
				zCPolygon *poly2 = foundPolyList[j];
				if (poly==poly2) continue;
				
				// Sector-Poly Handling

				if (poly2->GetSectorFlag()) continue;
/*				if (poly2->GetSectorFlag()) 
				if (!poly->GetSectorFlag()) continue;
				// Sektor-Polys aus verschiedenen Sektoren behindern sich nicht, wenn diese NICHT benachbart sind !
				if (poly->GetSectorFlag()) {
					if (poly2->GetSectorFlag()) {
						if ((poly->GetMaterial()->GetBspSectorFront()!=poly2->GetMaterial()->GetBspSectorFront()) &&
							(poly->GetMaterial()->GetBspSectorBack ()!=poly2->GetMaterial()->GetBspSectorBack ()) &&
							(poly->GetMaterial()->GetBspSectorFront()!=poly2->GetMaterial()->GetBspSectorBack ()) &&
							(poly->GetMaterial()->GetBspSectorBack ()!=poly2->GetMaterial()->GetBspSectorFront()))
						continue;
					};
				};
*/
				if (poly2->polyPlane.normal[VY]<zREAL(0.0001F)) continue;

				// Wasser ?
				if (poly2->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER) continue;

				// haben beide Polys fast identische Normalen ?
				if (poly->polyPlane.normal.IsEqualEps (poly2->polyPlane.normal)) continue;
				
				// Das zweite Poly darf nicht ueber dem ersten liegen
#if 1
				zTBBox3D poly2BBox = poly2->GetBBox3D();
				if (poly2BBox.maxs[VY]>polyBBox.mins[VY]) continue;
#else
				zREAL p1MaxY = zREAL_MIN;
				zREAL p2MinY = zREAL_MAX;
				for (int p1=0; p1<poly->polyNumVert; p1++)
				{
					if (poly->vertex[p1]->position[VY]>p1MaxY) p1MaxY = poly->vertex[p1]->position[VY];
				}
				for (int p2=0; p2<poly2->polyNumVert; p2++)
				{
					if (poly2->vertex[p2]->position[VY]<p2MinY) p2MinY = poly2->vertex[p2]->position[VY];
				}
				if (p2MinY>=p1MaxY) continue;
#endif

				// Schneiden sie die X/Z Projektionen der beiden Polys ?
				
				//if (poly->GetMaterial() != poly2->GetMaterial())
				{
					if (poly->IsIntersectingProjection	(poly2, zVEC3(0,1,0))) { occluder = FALSE; break; }; 
				}
				//else
				//{
				//	if (poly->IsIntersectingProjection	(poly2, zVEC3(0,1,0))) 
				//	if (poly2->IsIntersectingProjection	(poly, zVEC3(0,1,0))) { occluder = FALSE; break; };
				//}
		
			};
		};

		poly->SetOccluder (occluder);
		numOccluder += int(occluder);
	};

	// zweiter pass: alle occluder rausschmeissen, die ineffizient sind.
	// dazu gehören: 
	// a) occluder ohne occluder nachbarn die sehr klein sind
	// b) occluder polys mit occluder nachbarn, dessen flächen-summe zu klein ist
	zCArray<zCPolygon*>		occluderNeighbours;
	zCArraySort<zCPolygon*> occluderTested;
	occluderTested.SetCompare(Compare_Occluder);

	int maxNeighbourOccluders = 0;
	int maxArea				  = 0;

	//zCMaterial *mat = zNEW(zCMaterial("Occluder_Poly_Mat"));  
	//mat->SetColor (0,255,0);

	for (i=0; i<mesh->numPoly; i++)
	{
		zCPolygon *poly = mesh->SharePoly(i);

		static int count = 0;
		if ((count++==10000))
		{
			count = 0;
			zERR_MESSAGE(5,0,"C: unmarking inefficient occluders, still working: " + zSTRING((float(i)/float(mesh->numPoly)) * 100));
		}

		if (!poly->IsOccluder())				 continue;
		if (poly->GetGhostOccluder())			 continue;
		if (occluderTested.IsInList(poly))		 continue;

		occluderTested    .InsertSort(poly);
		occluderNeighbours.InsertEnd (poly);

		zREAL sumOccluderArea = GetOccluderAreaRec(poly, occluderNeighbours);

		if (sumOccluderArea>maxArea) 
		{
			maxArea = sumOccluderArea;
		}
		if (occluderNeighbours.GetNum()>maxNeighbourOccluders)
		{
			maxNeighbourOccluders=occluderNeighbours.GetNum();
		}

		const zBOOL big	= (sumOccluderArea>(300*300));
		
		if (!big)
		{
			for (int j=0; j<occluderNeighbours.GetNum(); j++)
			{
				occluderNeighbours[j]->SetOccluder(FALSE);
				//occluderNeighbours[j]->SetMaterial(mat);
				numOccluder--;
			}
		}
		else
		{
			for (int j=0; j<occluderNeighbours.GetNum(); j++)
			{
				if (!occluderTested.IsInList(occluderNeighbours[j]))
					occluderTested.InsertSort(occluderNeighbours[j]);
			}
		}

		occluderNeighbours.DeleteList();

	}
	occluderTested.DeleteList();


	zERR_MESSAGE (3, 0, "D: RBSP: ... numOccluder: "+zSTRING(numOccluder)+" of "+zSTRING(mesh->numPoly));
	zERR_MESSAGE (3, 0, "D: RBSP: ... maxOccluderSize: "+zSTRING(maxArea));
	zERR_MESSAGE (3, 0, "D: RBSP: ... maxOccluderNeighbours: "+zSTRING(maxNeighbourOccluders));
};




zREAL zCBspTree::GetOccluderAreaRec(const zCPolygon* rootPoly , zCArray<zCPolygon*>&nearOccluderPolys)
{
	zCArray<zCPolygon*>	neighbourOccluder;
	zCPolygon**			foundPolyList;
	int					foundPolyNum;
	zREAL				localArea		= rootPoly->GetArea();
	zTBBox3D			searchBox		= rootPoly->GetBBox3D();
	const zREAL			INC				= zREAL(1.0F);

	// Alle Polys aus der nahen Umgebung einsammeln
	if (searchBox.mins[VX]==searchBox.maxs[VX])		{ searchBox.mins[VX] -= INC; searchBox.maxs[VX] += INC; };
	if (searchBox.mins[VY]==searchBox.maxs[VY])		{ searchBox.mins[VY] -= INC; searchBox.maxs[VY] += INC; };
	if (searchBox.mins[VZ]==searchBox.maxs[VZ])		{ searchBox.mins[VZ] -= INC; searchBox.maxs[VZ] += INC; };
	searchBox.Scale (zREAL(1.2F));		// scale x/z

	GetRoot()->CollectPolysInBBox3D (searchBox, foundPolyList, foundPolyNum);

	// ermittle die occluder in der bbox und teste ggfs., ob diese das rootPoly als nachbar haben
	for (int j=0; j<foundPolyNum; j++)
	{
		zCPolygon *poly2 = foundPolyList[j];
		if (rootPoly==poly2)	 continue;
		
		if (poly2->IsOccluder() && !poly2->GetGhostOccluder() && (!nearOccluderPolys.IsInList(poly2)))
		{
			// shared der gefundene occluder die edges des nun gefundenen neuen occluders ?
			if (poly2->IsNeighbourOf(rootPoly))
			{
				neighbourOccluder.InsertEnd(poly2);
				nearOccluderPolys.InsertEnd(poly2);
			}
		}
	}

	if (neighbourOccluder.GetNum()>0) 
	{
		// nun alle für alle edge occluder rekursiv die gesamt area finden
		for (int n=0; n<neighbourOccluder.GetNum(); n++)
		{				
			localArea += GetOccluderAreaRec(neighbourOccluder[n],nearOccluderPolys);
		}
		neighbourOccluder.DeleteList();
	}
	
	return localArea;

};

static int ComparePolyType ( const void *arg1, const void *arg2 ) {
	zCPolygon *poly1 = *((zCPolygon**) arg1);
	zCPolygon *poly2 = *((zCPolygon**) arg2);

	int score1, score2;
	score1 = score2 = 0;
	if (poly1->IsPortal())		score1 = 1; else
	if (poly1->GetSectorFlag()) score1 = 2;
	if (poly2->IsPortal())		score2 = 1; else
	if (poly2->GetSectorFlag()) score2 = 2;

	if (score1<score2)	return -1; else
	if (score1>score2)	return +1; else
						return  0;
};
 
void zCBspBase::SortNodePolys (zCBspTree *hostTree) {
	// Sort-Order:
	// - Solid Polys
	// - Portal Polys
	// - Sector Polys
	if (numPolys>0) {
		zBOOL doSort = TRUE;
		// Bei indoor-Mode nur die Leafs sortieren, bei outdoor alle Nodes mit Polys sortieren
		if ((hostTree->GetBspTreeMode()==zBSP_MODE_INDOOR) && !IsLeaf()) doSort = FALSE;
		if (doSort)
		qsort (polyList, numPolys, sizeof(zCPolygon*), ComparePolyType);
	};
	if (IsNode()) {
		zCBspNode *node = (zCBspNode*)this;
		if (node->front)	node->front->SortNodePolys (hostTree);
		if (node->back)		node->back ->SortNodePolys (hostTree);
	};
};

// **************************************************************************************************
//		OUTDOOR:	BSP - SECTOREN
// **************************************************************************************************

void zCBspSector::RenderSector() 
{ 
	if (IsRendered()) return;
	Rendered();
	s_sectorsRendered++;

	for (int i=0; i<sectorNodes.GetNumInList(); i++) 
	{
		zCBspBase *node = sectorNodes[i]; 
		
		// BBox der Node am Frustum clippen
		int clipFlags = zCCamera::CLIP_FLAGS_FULL;
		zTCam_ClipType nodeClip = zCCamera::activeCam->BBox3DInFrustum (node->bbox3D, clipFlags);
		if (nodeClip==zCAM_CLIP_TRIV_OUT) continue; 

		// Leaf beleuchten
		node->CollectNodeLights();

		// Vobs werden nicht hier, sondern bereits bei (jeder) Aktivierung des Sektors hinzugefuegt
//		((zCBspLeaf*)node)->AddVobsToRenderListOutdoor (this, activePortal);

		int j = node->numPolys-1;
		do {
			zCPolygon *poly = node->polyList[j];
			if (poly->IsPortal())					break;
			if (!poly->GetSectorFlag())				break;

			// Nur Polys aus dem eigenen Sektor rendern
			zCMaterial *polyMat = poly->GetMaterial();
			if (polyMat->GetBspSectorFront()!=this)	continue;
			poly->RenderPoly (clipFlags);

		} while (j--); 
	};

	// Portale des Sektors rendern, falls sie beim Faden sind
	for (i=0; i<sectorPortals.GetNum(); i++) {
		zCPolygon	*poly		= sectorPortals[i];
		
		if (sectorPortalInfo[i].alpha>1)
		{ 
			poly->GetMaterial()->SetAlpha(sectorPortalInfo[i].alpha);
            zrenderer->DrawPoly (poly);
		};
	};

};


/* ----------------------------------------------------------------------
	
    zCBspSector::ActivateSectorRec()

	22.11.2000	[Moos]	
                Crashfix/Beseitigung eines visuellen Artefakts

   ---------------------------------------------------------------------- */

void zCBspSector::ActivateSectorRec (const zTBBox2D& cullBox2D, zCBspSector* lastSector, int depth) 
{
	// debug/safety
	if (depth>40) {
		static zBOOL haveWarned = FALSE;
		if (!haveWarned)
			zERR_FAULT ("D: seemingly endless sector activation recursion, sector/portals modeling error !?, lastSector: "+lastSector->GetSectorName()+", thisSector: "+GetSectorName());
		haveWarned = TRUE;
		return;
	};

	numSectorsVisited++;

/*
Notes:
	- In der zCBspSector::sectorPortals Liste befinden sich folgende Portale:
		- front-Normale zeigt in den Sektor hinein
		- alle Outdoor/Indoor Portale des Sektors

	- Es gibt 2 Arten von Outdoor/Indoor Portalen: bei den einen ist das outdoor
	  'front', bei den anderen 'back'.
	- Bei ActivateSectorRec() wird die eine Art Outdoor/Indoor Portale gleich zu Beginn
	  rausgefiltert, ueber die andere Art wird das Outdoor aktiviert

	- Da verschiedene Portale dasselbe Material benutzen koennen, allerdings Alpha-Berechnung (ActivateSectorRec())
	  und Rendern (RenderSector()) nicht zur selben Zeit passieren, kann der Alpha Wert eines
	  Portals leider nicht im Material gespeichert werden, sondern muss extern gecacht werden... (sectorPortalInfo)

	- Vorsicht:
	  Da die Sektoren nicht konvex sein muessen, kann es zyklische Portalketten geben (deren 2D-BBoxen sich auch
	  überlagern!). (z.B. OldCamp HH1-HH3 endlos-Schleife)
	  Loesungen:
	  - 100%: beim Durchschreiten eines Portals pruefen, ob dieses im selben Stab-Vorgang schon mal durchschritten 
	    worden ist (also quasi durch den Callstack alle Portale bis zum ersten testen) => slow
	  - Die Light-Version (schneller, aber immer noch nicht fehlerfrei) der 100%-Variante:
	    Aus einem Sektor heraus keinen 2. Sektor betreten, der der vorherige in der Kette ist
	  - In kritischen Stellen Portale anders setzen

	// - FIXME: gewisse Performance-Einbrueche im AL-Keller ??

	// x FIXME: noch buggy, falls 2 Portale nebeneinander in denselben Sektor fuehren
	// Darf dann passieren, wenn dieser Sektor nur 1 Zugang hat !
	//if (IsActivated()) return;

*/


	zBOOL activatedFirstTime = !IsActivated();

	if (!IsActivated()) {
		Activate();
		activePortal = cullBox2D;
	} else { 
		activePortal.CalcGreaterBBox2D (cullBox2D);
	};

	// Die Vobs des Sektors muessen bei jeder Portale Kette neu ueberprueft und ggfs. in die RenderList 
	// mitaufgenommen werden, da die Vobs eines Sektors unter Umstaenden allein durch die erste Portal Kette
	// nicht komplett/korrekt aktiviert werden und ein Sektor selbst bereits bei der ersten Aktivierung gerendert wird.
	// => Waldwaben
	// FIXME: potentiell zu langsam, da viele Vobs zu oft/redundant geprueft werden !?
	for (int i=0; i<sectorNodes.GetNumInList(); i++) 
	{
//		zCBspBase *node = sectorNodes[i]; 
		zCBspLeaf *leaf= (zCBspLeaf*)sectorNodes[i]; 
		leaf->AddVobsToRenderListOutdoor (this, activePortal);
		leaf->lastTimeActivated	= bspFrameCtr;
		leaf->sectorIndex		= 0;
	};

	for (i=0; i<sectorPortals.GetNum(); i++) {
		zCPolygon	*poly		= sectorPortals[i];
		zCMaterial	*portalMat	= poly->GetMaterial();

		// keine outdoor => indoor Portale
		if (portalMat->GetBspSectorFront()==0) continue; 

		// FIXME: hier spezielle Flags fuehren, ob Portal bereits backface, geclipt, etc..
		//        beachte: ein Portal&Sektor kann mehrfach ueber verschiedene Portal-Ketten aktiviert werden
		// HMMM: .. ist dass denn nicht der Fall, wenn genau dieser Sektor das 2.,3... mal durchlaufen wird ?? JA !!!!!

		if (activatedFirstTime) 
		{
			zBOOL	open	= FALSE;
			zBYTE	alpha	= 0;
			do {
				// 1) backface Culling
				if (poly->IsBackfacing()) break;

				// 2) Frustum Clipping
				// FIXME: ??? hier reicht bereits die Aussage on-screen oder nicht, komplettes Clipping nicht noetig
				// FIXME: hier waeren gueltige clipFlags hilfreich !!
				if (!poly->ClipToFrustum()) break; 
				
				// ist Portal durchlaessig ?
				if (!ShouldActivatePortal (poly)) {
					// Portal ist 100% opak 
					alpha	= 255;
					open	= FALSE;
					break;
				};

				//
				alpha	= poly->GetMaterial()->GetAlpha();
				open	= TRUE;
			} while (0);

			sectorPortalInfo[i].alpha	= alpha;
			sectorPortalInfo[i].visible = open;


            // [Moos] Hier war das TransformProjectLight vorher

			//
			if (!open) {
				// indoor => outdoor Portale sollen occluden, wenn sie vollkommen opak sind..
				if (alpha==255){
                	poly->TransformProjectLight();
					ScanHorizon (poly);
                }
				continue;
			};
		} else {
			// backface, opak oder offscreen(clip) => weiter
			if (!sectorPortalInfo[i].visible) continue;
		};


        // [Moos] hier weiss man ganz genau, dass das ding gebraucht wird

		// noetig um das 2D-Portal bilden zu koennen
        // if ((open) || (alpha>1))
		if (poly->GetMaterial()->GetAlpha()>0) 	poly->TransformProjectLight();
		else									poly->TransformProject();

		// bbox2D von Portal bilden
		// FIXME: koennte gecacht werden !
		zTBBox2D portalBBox2D;
		poly->GetScreenBBox2D (portalBBox2D);
//		portalBBox2D.Draw ();

		// Portal klassifizieren
		int cullType = cullBox2D.Classify (portalBBox2D);
		if (cullType!=zCAM_CLIP_TRIV_OUT) {
			// neues Portal an dem alten clippen
			portalBBox2D.ClipToBBox2D (cullBox2D);
			
			// Portal sichtbar, weitere Rekursion
			zCBspSector *backSector= portalMat->GetBspSectorBack();
			if (backSector) {
				// So sollen Portal-Aktivierungs-Zyklen vermieden werden: aber ist das so sicher genug ... ??
				if (lastSector==backSector) continue;
				// indoor	=> indoor
				backSector->ActivateSectorRec	(portalBBox2D, this, depth+1);
			} else {
				// indoor	=> outdoor
				// FIXME: Distanz-Fade ??
//				if (zAbsApprox(poly->GetPlane().normal[VY])<0.1F)
				{
					zCBspSector::AddOutdoorPortal	(portalBBox2D);
/*					zlineCache.Line (portalBBox2D.mins[VX], portalBBox2D.mins[VY], portalBBox2D.maxs[VX], portalBBox2D.mins[VY]);
					zlineCache.Line (portalBBox2D.maxs[VX], portalBBox2D.mins[VY], portalBBox2D.maxs[VX], portalBBox2D.maxs[VY]);
					zlineCache.Line (portalBBox2D.maxs[VX], portalBBox2D.maxs[VY], portalBBox2D.mins[VX], portalBBox2D.maxs[VY]);
					zlineCache.Line (portalBBox2D.mins[VX], portalBBox2D.maxs[VY], portalBBox2D.mins[VX], portalBBox2D.mins[VY]);
*/
				};

			};
		};
	};
};

void zCBspSector::ActivateSectorRecIndoor (const zTBBox2D& cullBox2D, zCBspSector* lastSector, int depth) 
{
	// debug/safety
	if (depth>15) {
		static zBOOL haveWarned = FALSE;
		if (!haveWarned)
			zERR_FAULT ("D: seemingly endless sector activation recursion, sector/portals modeling error !?, lastSector: "+lastSector->GetSectorName()+", thisSector: "+GetSectorName());
		haveWarned = TRUE;
		return;
	};

	numSectorsVisited++;

	zBOOL activatedFirstTime = !IsActivated();

	if (!IsActivated()) {
		Activate();
		activePortal = cullBox2D;
	} else { 
		activePortal.CalcGreaterBBox2D (cullBox2D);
	};

	// Die Vobs des Sektors muessen bei jeder Portale Kette neu ueberprueft und ggfs. in die RenderList 
	// mitaufgenommen werden, da die Vobs eines Sektors unter Umstaenden allein durch die erste Portal Kette
	// nicht komplett/korrekt aktiviert werden und ein Sektor selbst bereits bei der ersten Aktivierung gerendert wird.
	// => Waldwaben
	// FIXME: potentiell zu langsam, da viele Vobs zu oft/redundant geprueft werden !?

	for (int i=0; i<sectorPortals.GetNum(); i++) 
	{
		zCPolygon	*poly		= sectorPortals[i];
//		zCMaterial	*portalMat	= poly->GetMaterial();

		// FIXME: hier spezielle Flags fuehren, ob Portal bereits backface, geclipt, etc..
		//        beachte: ein Portal&Sektor kann mehrfach ueber verschiedene Portal-Ketten aktiviert werden
		// HMMM: .. ist dass denn nicht der Fall, wenn genau dieser Sektor das 2.,3... mal durchlaufen wird ?? JA !!!!!

		if (activatedFirstTime) 
		{
			zBOOL	open	= FALSE;
			zBYTE	alpha	= 0;
			do {
				// 1) backface Culling
				if (poly->IsBackfacing()) break;

				// 2) Frustum Clipping
				// FIXME: hier waeren gueltige clipFlags hilfreich !!
				if (!poly->ClipToFrustum()) break; 
				
				// ist Portal durchlaessig ?
				if (!ShouldActivatePortal (poly)) {
					// Portal ist 100% opak 
					alpha	= 255;
					open	= FALSE;
					break;
				};

				//
				alpha	= poly->GetMaterial()->GetAlpha();
				open	= TRUE;
			} while (0);

			sectorPortalInfo[i].alpha	= alpha;
			sectorPortalInfo[i].visible = open;

			// noetig um das 2D-Portal bilden zu koennen
			// FIXME: unnoetig ist das lighting (falls alpha==0)
			if ((open) || (alpha>1))
				poly->TransformProjectLight();

			// Portale des Sektors rendern
			if (sectorPortalInfo[i].alpha>1)
			{ 
				poly->GetMaterial()->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
				poly->GetMaterial()->SetAlpha			(sectorPortalInfo[i].alpha);
				zrenderer->DrawPoly (poly);
			};

			//
			if (!open) {
				// indoor => outdoor Portale sollen occluden, wenn sie vollkommen opak sind..
//				if (alpha==255)	ScanHorizon (poly);
				continue;
			};
		} else {
			// backface, opak oder offscreen(clip) => weiter
			if (!sectorPortalInfo[i].visible) continue;
		};

		// bbox2D von Portal bilden
		// FIXME: koennte gecacht werden !
		zTBBox2D portalBBox2D;
		poly->GetScreenBBox2D (portalBBox2D);
		if (actBspTree->GetShowPortals())
			portalBBox2D.Draw ();

		// Portal klassifizieren
		int cullType = cullBox2D.Classify (portalBBox2D);
		if (cullType!=zCAM_CLIP_TRIV_OUT) 
		{
			// neues Portal an dem alten clippen
			portalBBox2D.ClipToBBox2D (cullBox2D);

			// Portal sichtbar, weitere Rekursion
			// So sollen Portal-Aktivierungs-Zyklen vermieden werden: aber ist das so sicher genug ... ??
			int sectorIndex = poly->GetSectorIndex();
			zERR_BOUNDS (sectorIndex, 0, actBspTree->sectorList.GetNum()-1);
			zCBspSector *sector = actBspTree->sectorList[sectorIndex];
			if (lastSector==sector) continue;

			sector->ActivateSectorRecIndoor	(portalBBox2D, this, depth+1);
		};
	};

	// Die Leafs des Sektors aktivieren
	{
		// Die Leafs des ersten Sektors brauchen nicht gegen die Aktivierungs-Portal-BBox getestet werden, da sie
		// eh immer durchkommen wuerden!
		const zWORD sectorIndexActivation = (depth==0) ? zSECTOR_INDEX_UNDEF : this->GetSectorIndex();

		for (int i=0; i<sectorNodes.GetNumInList(); i++) 
		{
			zCBspLeaf *leaf			= (zCBspLeaf*)sectorNodes[i]; 
	//		if (leaf->lastTimeActivated!=bspFrameCtr)
			{
				leaf->lastTimeActivated	= bspFrameCtr;
				leaf->sectorIndex		= sectorIndexActivation;
			};
		};
	};
};

void zCBspSector::RenderActiveSectorList () 
{
	for (int i=0; i<s_activeSectorList.GetNumInList(); i++) {
		s_activeSectorList[i]->RenderSector ();
	};
	s_activeSectorList.EmptyList();
};

zCBspSector* zCCBspTree::GetBspSectorByName (const zSTRING& name) const {
	if (name.Length()==0) return 0;
	for (int i=0; i<sectorList.GetNumInList(); i++) {
		zCBspSector *sector = sectorList[i];
		if (sector->GetSectorName()==name) return sector;
	};
	return 0;
};

const zSTRING* zCBspTree::GetSectorNameVobIsIn (const zCVob *vob) const
{
	zERR_ASSERT (vob);
	const zSTRING *sectorName=0;
	if (vob->GetGroundPoly())
		sectorName = &(vob->GetGroundPoly()->GetMaterial()->GetBspSectorFront()->GetSectorName());
	return sectorName;
};

static void CutSectorNames (const zSTRING& in, zSTRING& out1, zSTRING& out2) {
	out1 = in;
	out2 = in;
	out1.Delete (zSTRING(":"), zSTR_TO);
	out1.Delete (zSTRING("_"), zSTR_FROM);
	out2.Delete (zSTRING("_"), zSTR_TO);
};

void zCCBspTree::GetPolyNeighbours (zCPolygon *sourcePoly, zCPolygon**& foundPolyList, int& foundPolyNum) {
	zTBBox3D	searchBox = sourcePoly->GetBBox3D();
	searchBox.Scale (1.1F);
	bspRoot.CollectPolysInBBox3D (searchBox, foundPolyList, foundPolyNum);

	// Aussortieren: doppelte Polys, Sector-Polys 
	// (Portale bleiben allerdings drin !!!)
	for (int k=0; k<foundPolyNum; k++) {
		zCPolygon *poly = foundPolyList[k];
		if ((poly==sourcePoly) ||
			((poly->GetSectorFlag()) && (!poly->IsPortal())))
		{
			foundPolyList[k] = foundPolyList[--foundPolyNum];
			k--;
			continue;
		};
		for (int j=k+1; j<foundPolyNum; j++) { 
			zCPolygon *poly2 = foundPolyList[j];
			if (poly2==poly) {
				foundPolyList[j] = foundPolyList[--foundPolyNum];
				j--;
				continue;
			};
		};
	};
};

/*
static zREAL GetFullDot (const zVEC3& a, const zVEC3& b, const zVEC3& axis) {
	// -1	0	1	2	3
	// -180	-90	0	90	180		(- => rechts)
	zREAL	dot		= a * b;
	zVEC3	cross	= a^b;
//	if (cross*axis<0) dot = -(dot-1)+1;
	if (cross*axis>=0) dot = -(dot-1)+1;
//	cross.Normalize();
//	if (cross.IsEqualEps(axis))	dot = -(dot-1)+1;
	return dot;
};

struct zTEdgePoly {
	zCPolygon	*poly;
	int			index;
};
*/

void zCCBspTree::MarkGhostOccluder() {
	int num=0;
	for (int i=0; i<mesh->numPoly; i++) {
		zCPolygon	*poly	= mesh->SharePoly(i);
		zCMaterial	*mat	= poly->GetMaterial();
		poly->SetGhostOccluder	(FALSE);

		// Ghost-Occluder ?
		if (mat->GetName().Search("GHOSTOCCLUDER")!=-1) {
			poly->SetGhostOccluder	(TRUE);
			poly->SetOccluder		(TRUE);
			poly->SetPortalType		(zCPolygon::zPORTAL_TYPE_SMALL);		// damit Poly nicht in BSP-Queries gelangt (Collision, TraceRay)
			num++;
			if (mat->GetTexture()) mat->SetTexture (0);
		};
	};
	zERR_MESSAGE (3, 0, "D: BSP: Num GhostOccluder: "+zSTRING(num));
};

void zCCBspTree::CreateBspSectors() {

	int matsGenerated = 0;

	// *****************************
	//	1. Portale sammeln
	// *****************************

	zSTRING onlySectorName;
	if (zoptions->Parm ("ZSECTOR")) {
		onlySectorName = "P:"+zoptions->ParmValue ("ZSECTOR");
	}
	const zBOOL skipSectors = zoptions->Parm ("ZSKIPSECTORS");
	

//onlySectorName = "WD1";
//onlySectorName = "ARENA";

	sectorList.EmptyList();
	{  
		int numPortalType1	= 0;
		int numPortalType2	= 0;
		int numPortalType3	= 0;
		for (int i=0; i<mesh->numPoly; i++) {
			zCPolygon	*poly	= mesh->SharePoly(i);
			zCMaterial	*mat	= poly->GetMaterial();
			poly->SetSectorFlag		(FALSE);
			poly->SetPortalType		(zCPolygon::zPORTAL_TYPE_NONE);
			poly->SetGhostOccluder	(FALSE);

			if (onlySectorName.Length()>0)
			if (mat->GetName().Search(onlySectorName)==-1) continue;

#ifdef zBSP_DONT_CREATE_SECTORS
			if (0)
#else
			if (mat->IsPortalMaterial())
#endif
			if (!skipSectors)
			{
				zSTRING frontName, backName, sectorName;
//				portalList.Insert	(poly);
				poly->SetSectorFlag (TRUE); 
				CutSectorNames		(mat->GetName(), frontName, backName);
				
				// Portal klassifizieren
				{
					if (mat->GetName().Search("PN:")!=-1) {
						poly->SetPortalType	(zCPolygon::zPORTAL_TYPE_BIG_NOFADE);
						numPortalType3++;
					} else {
						// FIXME: arbeitet GetArea() korrekt ? doch lieber laengste Edge nehmen (bei 1Portal=nTris) ?
						const zBOOL big	= (poly->GetArea()>(970*500)) || (poly->GetLongestEdgeLen()>500);
						if (big)	{ poly->SetPortalType	(zCPolygon::zPORTAL_TYPE_BIG);	numPortalType2++; }
						else		{ poly->SetPortalType	(zCPolygon::zPORTAL_TYPE_SMALL);numPortalType1++; };
					};
				};

//				zERR_MESSAGE ("D: Portal: >"+frontName+":"+backName+"<");
				// Gibt es den Sektor bereits ? Wenn nicht, dann erzeugen
				// indoor => outdoor Portale skippen (damit kein 'Aussenwelt'-Sektor erzeugt wird)
				if (frontName.Length()==0)	{
					sectorName = backName;
					poly->SetPortalIndoorOutdoorFlag	(TRUE);
				} else {
					sectorName = frontName;
					poly->SetPortalIndoorOutdoorFlag	(FALSE);
				};

				zCBspSector *sector = GetBspSectorByName (sectorName); 
				if (sector==0) {
//					zERR_MESSAGE ("D: New Sector: "+sectorName+", "+zSTRING(sectorName.Length()));
					sector					= zNEW(zCBspSector);
					sector->SetSectorName	(sectorName);
					sectorList.Insert		(sector);
				};
				sector->sectorPortals.Insert		(poly);

				// hasBigNoFade ?
				if (!sector->hasBigNoFade)
					sector->hasBigNoFade= (mat->GetName().Search("PN:")!=-1);
			};
		};
		zERR_MESSAGE (3, 0, "D: BSP: numPortalTypes: "+zSTRING(numPortalType1)+", "+zSTRING(numPortalType2)+", "+zSTRING(numPortalType3));
	};

	zERR_MESSAGE (3, 0, "D: BSP: Creating BSP Sectors: "+zSTRING(sectorList.GetNum()));
	if (sectorList.GetNum()<=0) return; 

	// ********************************************
	//	2. ConWalk: Sector-Polys finden
	// ********************************************

	// zu diesem Zeitpunkt:
	// - Sektoren sind ermittelt und Portale bei diesen registriert

	zCArray<zCPolygon*>	activePolys;	// keine Portale, Polys bei denen noch nicht alle Edges gescannt wurden
	zSTRING newMatName;
	for (int i =0; i<sectorList.GetNumInList(); i++) {
		zCBspSector	*sector = sectorList[i];
		zCPolygon	*portal;
		{
			zERR_MESSAGE (3, 0, "D: BSP: Sector#: "+zSTRING(i)+", \""+sector->GetSectorName()+"\", portals: "+zSTRING(sector->sectorPortals.GetNum()));
//							+", nodes: "+sector->sectorNodes.GetNum()
//			zERR_MESSAGE (3, 0, "D: BSP: Sector#: "+zSTRING(i));
		};

		// Sector Center berrechnen
		sector->CalcCenterByPortals();

		//
		activePolys.EmptyList	();

		// indoor => outdoor Portals werden geskippt
/*		{
			// Alle Portale (ausser ind=>out) sind StartPolys
			for (int q=0; q<sector->sectorPortals.GetNumInList(); q++) {
				if (sector->sectorPortals[q]->GetPortalIndoorOutdoorFlag ()) continue;
				activePolys.Insert (sector->sectorPortals[q]);
			};
			if (activePolys.GetNumInList()==0)
				zERR_FATAL ("D: zBSP(zCBspTree::CreateBspSectors): Illegal Sector Portals: "+sector->GetSectorName()); 
			portal = activePolys[0];
		};*/
		{ 
			int q=0;
			portal = sector->sectorPortals[q];
			while (portal->GetPortalIndoorOutdoorFlag ()) {
				q++;
				if (q>=sector->sectorPortals.GetNumInList()) {
					zERR_FATAL ("D: zBSP(zCBspTree::CreateBspSectors): Illegal Sector Portals: "+sector->GetSectorName()); 
				};
				portal = sector->sectorPortals[q];
			};
		};

		// Connectivity-Walk
		// Start-Poly(s) ermitten
		const zREAL	OFS			= zREAL(5.0F); 
		zCPolygon	*hitPolyFront;
		zVEC3		inters;
		zPOINT3		center		= portal->GetCenter();
		zPOINT3		start		= center + portal->polyPlane.normal*OFS;
		const zVEC3& normal		= portal->polyPlane.normal;
		zVEC3		dir;
//		if (zAbs(normal[VY])>zREAL(0.95F)) {
//			dir = normal * 50000;
//		} else
		{
			dir	= ((zVEC3(0,1,0)^normal)^normal)*50000;
			if (dir[VY]>0) dir= -dir; 
		};

		// 1
		bspRoot.TraceRay (start, start+dir, hitPolyFront);
		if (hitPolyFront)	if (!activePolys.IsInList(hitPolyFront)) activePolys.Insert (hitPolyFront);
		// 2
		dir = -dir;
		bspRoot.TraceRay (start, start+dir, hitPolyFront);
		if (hitPolyFront) { if (!activePolys.IsInList(hitPolyFront)) goto foundStartPoly; };
		// 3
		dir = normal * 50000;
		bspRoot.TraceRay (start, start+dir, hitPolyFront);
		if (hitPolyFront) { if (!activePolys.IsInList(hitPolyFront)) goto foundStartPoly; else goto foundStartPolySkip; };

		if (!hitPolyFront) {
			// FIXME: hier noch weitere Versuche starten: start & dir variieren ..
			zERR_WARNING ("D: zBSP(zCBspTree::CreateBspSectors):  No startPoly found, Illegal Sector Portals: "+sector->GetSectorName());
			zERR_MESSAGE (3, 0, "D: start: "+start.GetString()+", dir: "+dir.GetString());
			continue;
		};
foundStartPoly:;
		activePolys.Insert		(hitPolyFront);
foundStartPolySkip:;

		// "Schwebende Polys" ermitteln und als StartPolys hinzufuegen
		// Strategie: von jedem Vert jedes Portal-Polys einen Ray zu jedem Vert jedes anderen Portal-Polys
		//            schiessen (Polys koennten übersehen werden)
//		if (sector->GetSectorName().Search("WALD17")!=-1)
//		if (0)
		if (sector->hasBigNoFade)
		{
			for (int i=0; i<sector->sectorPortals.GetNum(); i++) 
			{
				zCPolygon *portal = sector->sectorPortals[i];
				if (portal->GetPortalIndoorOutdoorFlag ()) continue;
				for (int j=0; j<portal->polyNumVert; j++) 
				{
					for (int k=0; k<sector->sectorPortals.GetNum(); k++) 
					{
						if (i==k) continue;
						zCPolygon *portal2 = sector->sectorPortals[k];
						if (portal2->GetPortalIndoorOutdoorFlag ()) continue;
						for (int l=0; l<portal->polyNumVert; l++) 
						{
							if (portal->GetVertexPtr(j)==portal2->GetVertexPtr(l)) continue;
							// etwas in die Mitte des Sectors hineinsteppen, ansonsten koennte man Polys ausserhalb des Sectors erwischen
							const zVEC3&	a	= portal ->GetVertexPtr(j)->position + 0.05F*(sector->sectorCenter-portal->GetVertexPtr(j)->position);
							const zVEC3&	b	= portal2->GetVertexPtr(l)->position + 0.05F*(sector->sectorCenter-portal2->GetVertexPtr(l)->position);
							zVEC3	delta		= b-a;
							zVEC3	end			= a + 0.9F*delta;	// 0.1 .. 0.9
							zREAL	alpha		= 0.1F;
							zVEC3	inters;
							do {
								zVEC3	start	= a + alpha*delta;
								zVEC3	dir		= end-start;
								bspRoot.TraceRay (start, start+dir, hitPolyFront, inters);
								if (hitPolyFront) 
//								if (hitPolyFront->GetMaterial()->GetName().Search("P:")==-1)
								if (!hitPolyFront->GetMaterial()->IsPortalMaterial())
								{
									if (!activePolys.IsInList(hitPolyFront)) 
										activePolys.Insert (hitPolyFront);
									zREAL intersAlpha = (inters-a).Length2() / delta.Length2();
									if (intersAlpha<0.8F)	{
										const zREAL S = 0.03F;
										alpha		= zMax (alpha + S, intersAlpha + S);
										if (alpha<=0.9F) continue;
									};
								};
								break;
							} while (1);
						};
					};
				};
			};
		};

		// Potentielle Sector-Polys aus dem Bsp ziehen
		// Polys in der Umgebung aus dem BSP ziehen, diese werden dann untersucht 
		zCPolygon	**foundPolyList;
		int			foundPolyNum;

foundPolyNum=0;	// fuer debug-breakpoint

		// ConWalk
		while (activePolys.GetNum()>0) 
		{
			zCPolygon *poly = activePolys[0];
			activePolys.RemoveIndex (0);

			// Dem Poly wird ein neues Material zugewiesen
			if (!poly->GetSectorFlag()) 
			{
				newMatName		= zSTRING("S:")+sector->GetSectorName()+zSTRING("_")+poly->GetMaterial()->GetName();
				zCMaterial	*mat= zCMaterial::SearchName (newMatName);
				if (!mat) 
				{
					// Neues Material per Copy-Konstruktor erzeugen, und abweichende Eigenschaften setzen
					mat						= zNEW(zCMaterial (*(poly->GetMaterial())));
					mat->SetName			(newMatName);
					mat->SetBspSectorFront	(sector);
					mat->SetBspSectorBack	(sector);

					/*
					mat = zNEW(zCMaterial	(newMatName));
					zCTexture *oldTex		= poly->GetMaterial()->GetTexture();
					mat->SetTexture			(oldTex);
					mat->SetColor			(poly->GetMaterial()->GetColor	());
					mat->SetBspSectorFront	(sector);
					mat->SetBspSectorBack	(sector);*/
					matsGenerated++;
				};
				if (poly->GetMaterial()!=mat)	poly->SetMaterial	(mat);
				poly->SetSectorFlag (TRUE);
			}

			GetPolyNeighbours (poly, foundPolyList, foundPolyNum);

			// Edges des aktiven Polys scannen
			for (int j=0; j<poly->polyNumVert; j++) 
			{
				int jnext=j+1;	if (jnext>=poly->polyNumVert) jnext=0;
				zCVertex *vert1	= poly->GetVertexPtr(j);
				zCVertex *vert2	= poly->GetVertexPtr(jnext);

				// Ist die aktuelle Edge in einem anderen Poly enthalten ?
				zCPolygon	*foundPoly	= 0;
				int			foundPolyInd= 0;
				zBOOL		insertThis	= FALSE;
				for (int k=0; k<foundPolyNum; k++) {
					zCPolygon *poly2 = foundPolyList[k];

					if (poly2==poly)			goto skipThisPoly;;
//					if (poly2->IsPortal())		goto skipThisPoly;;
//					if (poly2->GetSectorFlag())	goto skipThisPoly;
					if (poly2->EdgePartOfPoly (vert2, vert1)) {
//					if (poly2 ->EdgePartOfPoly (vert1, vert2) || poly2->EdgePartOfPoly (vert2, vert1)) {
						// bereits ein Poly gefunden ? 
						// => das Walk-Poly grenzt an eine PolyRaum1/Portal1/Portal2/PolyRaum2 Kante
//						if (poly2->GetSectorFlag() && !poly2->IsPortal()) goto skipThisPoly;
						if (foundPoly) {
							insertThis	= FALSE;
//							foundPoly	= 0;
							break;
						};
						if (poly2->IsPortal()) break;
						insertThis		= TRUE;
						foundPoly		= poly2;
						foundPolyInd	= k; 
					};
skipThisPoly:;
				};
				if (insertThis)
//				if (foundPoly)  
//				if (!foundPoly->IsPortal())
				{
					if (!foundPoly->GetSectorFlag())
					if (!activePolys.IsInList(foundPoly)) 
					{

						zBOOL ok = TRUE;
						
//						if (0)
						if (sector->hasBigNoFade)
						{
							// Sind die beiden Polys durch ein Portal getrennt ? 
							// (Portal muesste durch deren gemeinsame Kante laufen)
							zCPolygon* newPoly;
							const zVEC3&	a	= poly->GetCenter()		+ poly		->polyPlane.normal*5;
							const zVEC3&	b	= foundPoly->GetCenter()+ foundPoly	->polyPlane.normal*5;
							zVEC3	delta = b-a;
							zVEC3	start = zREAL(0.1F) * delta + a;
									delta = zREAL(0.8F) * delta;
							bspRoot.TraceRay (start, start+delta, newPoly);
							if (newPoly) 
	//						if (newPoly->GetMaterial()->GetName().Search("P:")!=-1)
							if (newPoly->GetMaterial()->IsPortalMaterial())
								ok = FALSE;
						};

						if (ok)
							activePolys.Insert (foundPoly);
					};
					foundPolyList[foundPolyInd]	= foundPolyList[--foundPolyNum];
				};
			};
		};
	};

/*	for (i =0; i<sectorList.GetNumInList(); i++) {
		zCBspSector	*sector = sectorList[i];
		zERR_MESSAGE ("D: Sector: "+sector->GetSectorName()+", portals: "+sector->sectorPortals.GetNumInList()+", nodes: "+sector->sectorNodes.GetNumInList()); 
	};
*/
//	zERR_MESSAGE ("D: RBSP: Creating BSP Sectors: "+zSTRING(sectorList.GetNumInList())+", mats: "+zSTRING(matsGenerated));
}; 

zCBspSector* zCBspTree::GetBspSectorByName (const zSTRING& name) const {
	if (name.Length()==0) return 0;
	for (int i=0; i<sectorList.GetNumInList(); i++) {
		zCBspSector *sector = sectorList[i];
		if (sector->GetSectorName()==name) return sector;
	};
	return 0;
};

void zCBspTree::CreateBspSectors2 (zCCBspTree *ctree) 
{
	// ***********************************************************
	//	3. Sector-Leafs finden & Portal-Mats front/back-Sect
	// ***********************************************************

	if (ctree->sectorList.GetNum()<=0) return;
	sectorList = ctree->sectorList;

	for (int i=0; i<sectorList.GetNum(); i++) {
		sectorList[i]->sectorPortals.EmptyList();
	};

	// Fuer jeden Sector dessen BspNodes und Portale suchen
	for (int leafNr=0; leafNr<numLeafs; leafNr++) {
		zCBspLeaf *leaf = &(leafList[leafNr]);

		for (int i=0; i<leaf->numPolys; i++) {
			zCPolygon	*poly		= leaf->polyList[i];

			if (poly->GetSectorFlag()) {
				zCBspSector *sector		= 0; 
				zCMaterial	*polyMat	= poly->GetMaterial();

				if (poly->IsPortal()) {
					zSTRING		frontName, backName;
					CutSectorNames					(polyMat->GetName(), frontName, backName);
					polyMat->SetAlphaBlendFunc		(zRND_ALPHA_FUNC_BLEND); 
					polyMat->SetBspSectorFront		(ctree->GetBspSectorByName(frontName));
					polyMat->SetBspSectorBack		(ctree->GetBspSectorByName(backName ));
					if (polyMat->GetBspSectorFront()==0) {
						// Portal: indoor => outdoor
						sector = polyMat->GetBspSectorBack	();	
					} else {
						// Portal: outdoor => indoor
						sector = polyMat->GetBspSectorFront	();
					};
					// Portal eintragen
					if (sector)
					if (!sector->sectorPortals.IsInList(poly))
						sector->sectorPortals.Insert (poly); 
				} else {
					sector = polyMat->GetBspSectorFront();
				};

				// Leafs eintragen
				if (!sector) {
					// error
				} else
				if (!sector->sectorNodes.IsInList (leaf)) {
					sector->sectorNodes.Insert (leaf);
				};
			};
		};
	}; 
	ctree->sectorList.EmptyList();
};

/*
	- alle Portale sammeln ("P:_HAUS1", "P:HAUS1_", oder "P:RAUM1_RAUM2")	"front_back"
	- allein aus den Portal-Namen kann die Menge aller Sektoren ermittelt werden

	- Fuer jeden Sektor:
		- Alle Portale dieses Sektors sammeln. "P:RAUM1_..", "P:HAUS1_"
		- Ab einem beliebigem Startportal einen ConWalk durchfuehren.
		- Alle Polys des Walks bekommen spezielle neue Materialien, die nur in diesem Sektor vorkommen "S:RAUM1_BODEN".
		- 
*/

/*
zBSP.cpp
zBSPTool.cpp

	- Preprocessing:
2/3		- CBSP compile
		CBSP
4		-  	cbsp	- Create BSP-Sectors	- braucht BSP TraceRay/CollectPolys
											- nur Triangles
		-	mesh	- tris => n-Polys		- nur   Sektor/Portal-Polys
											- aendert mesh/polylist
		-	cbsp	- LOD Generierung		- keine Sektor/Portal-Polys
											- braucht CBSP
		RBSP
1		-	rbsp	- Mark Occluder Polys	- Sektor Polys muessen bekannt sein
*/


static const zWORD zBSP_FILE_VERS					= (00*256 + 03);

static const zWORD zFCHUNK_BSP						= 0xC000;
static const zWORD		zFCHUNK_BSP_POLYLIST		= 0xC010;
static const zWORD		zFCHUNK_BSP_TREE			= 0xC040;
static const zWORD		zFCHUNK_BSP_LEAF_LIGHT		= 0xC045;
static const zWORD		zFCHUNK_BSP_OUTDOOR_SECTORS	= 0xC050;
static const zWORD		zFCHUNK_BSP_END				= 0xC0FF;

zWORD zCBspTree::GetFileVersion () { return zBSP_FILE_VERS; };

/*
	********|********|********|********
      Bsp   |  Mesh  |     --frei--
*/

static zDWORD GetFileBinaryVersion() {
	return (zDWORD(0) +
				  (zDWORD(zCMesh::GetFileVersion())		<<16) + 
				  (zDWORD(zCBspTree::GetFileVersion())	<<24));
};

struct zTBsp_FileBase {
	zDWORD		polyIndex;
	int			numPolys;
	zTBBox3D	bbox3D;
	zBYTE		flag;
};

void zCBspBase::SaveBINRec (zCFileBIN& file) 
{
	// BASE: write contents
	bbox3D.SaveBIN		(file);
	if (numPolys<=0)	file.BinWriteDWord	(zDWORD(0));	// Ptr => Index
	else				file.BinWriteDWord	(zDWORD(polyList - actBspTree->treePolyList));	// Ptr => Index
	file.BinWriteInt	(numPolys);

	if (IsNode()) 
	{
		// Flag
		zBYTE flag = 0;
		zCBspNode *node = (zCBspNode*)this;
		if (node->front) {
			flag |= 1;
			if (node->front->IsLeaf()) flag |= 4;
		};
		if (node->back) {
			flag |= 2;
			if (node->back->IsLeaf()) flag |= 8;
		};
		file.BinWriteByte	(flag);

		// NODE: write contents
		file.BinWrite		(&node->plane	, sizeof(node->plane));
//		file.BinWrite		(&node->numLeafs, sizeof(node->numLeafs));

		// recurse
		if (node->front)	node->front->SaveBINRec (file);
		if (node->back)		node->back ->SaveBINRec (file);
	} else {
		// LEAF: write contents
	};
};

void zCBspBase::LoadBINRec (zCFileBIN& file) 
{
//	zERR_MESSAGE ("-------------------------------------");
//	actBspTree->bspRoot->DescribeTree();

	// BASE: read contents
	zDWORD treePolyIndex;
	bbox3D.LoadBIN			(file);
	file.BinReadDWord		(treePolyIndex);
	file.BinReadInt			(numPolys);
	if (numPolys>0)	polyList		= actBspTree->treePolyList + treePolyIndex;		// [BC] BOUNDSCHECKER: 636x assigning ptr out of range
	else			polyList		= 0;
	
	if (IsNode()) 
	{
		// Flag
		zBYTE flag;
		file.BinReadByte		(flag);
		// NODE: read contents
		zCBspNode *node	= (zCBspNode*)this;
		file.BinRead	(&node->plane	, sizeof(node->plane));
		node->CalcPlaneSignbits (actBspTree);

		// letztes Leaf merken fuer leafList
		zCBspLeaf *lastLeaf = actBspTree->actLeafPtr;
		node->front			= node->back = 0; 
		if ((flag & 1)!=0)	{
			if ((flag & 4)!=0)	node->front	= actBspTree->actLeafPtr++;	// Leaf
			else				node->front	= actBspTree->actNodePtr++;	// Node
			node->front->parent = node;
			node->front->LoadBINRec (file);
		};
		if ((flag & 2)!=0)	{
			if ((flag & 8)!=0)	node->back = actBspTree->actLeafPtr++;	// Leaf
			else				node->back = actBspTree->actNodePtr++;	// Node
			node->back->parent = node;
			node->back->LoadBINRec (file);
		};
		// leafList-Info eintragen..
		node->leafList	= lastLeaf;
		node->numLeafs	= int((actBspTree->actLeafPtr - lastLeaf));
	} else {
		// Leaf
	};
};

void zCBspTree::SaveBIN	(zCFileBIN& file) 
{
	// - save mesh
	// - save Tree Header (mode,..)
	// - save nodes
	// - save leafs
	// - save tree structure (mit Indizies)

	// die gemorphten verts wiederherstellen

	
	zCPolygon::S_ResetMorphedVerts(); 

	int i;
	actBspTree = this;

	// Header & Laenge eintragen
	int		fileStartPos	= file.file->Pos();
	zDWORD	version			= GetFileBinaryVersion();
	zDWORD	chunkLen		= 0;
	file.file->Write	(&version , sizeof(version));
	file.file->Write	(&chunkLen, sizeof(chunkLen));

	// Die Polyliste des Meshes wird sortiert (nach ptr-adr..)
	//zCArraySort<zCPolygon*> sortPolyList(mesh->numPoly);
	//for (i=0; i<mesh->numPoly; i++)		sortPolyList.Insert (mesh->polyList[i]);
	//sortPolyList.QuickSort();
	//for (i=0; i<mesh->numPoly; i++)		mesh->polyList[i] = sortPolyList[i];

    // [Moos] vielleicht implementiere ich das ja noch...
    // mesh->ShareFeatures();  // Lassen wir das lieber die Welt erledigen

    // Sortiere das Mesh räumlich kohärent
    mesh->SortPolysByList(treePolyList, numPolys);

    // besorge die Indices der Mesh-Polygone
    zCSparseArray<const void *, int> polyIndices;
    for (i = mesh->numPoly-1; i>=0; i--)
        *(polyIndices.Insert(mesh->SharePoly(i))) = i;

    // prüfe sie
    for (i = mesh->numPoly-1; i>=0; i--)
        zERR_ASSERT_STRICT (polyIndices[mesh->SharePoly(i)] && *(polyIndices[mesh->SharePoly(i)]) == i);

	// Save Mesh

	mesh->SaveMSH (file);

	// Save Tree-Header
	file.BinStartChunk		(zFCHUNK_BSP);
	{
		zTBspTreeMode mode = GetBspTreeMode();
		file.BinWriteWord	(zBSP_FILE_VERS);
		file.BinWrite		(&mode, sizeof(mode));
	};

	// PolyList
	file.BinStartChunk		(zFCHUNK_BSP_POLYLIST);
	{
		file.BinWriteInt	(numPolys);
		// Ptr nach Index umwandeln
		for (int i=0; i<numPolys; i++) {
			zCPolygon	*poly = treePolyList[i];
//			zDWORD		index = sortPolyList.Search(poly);
			zDWORD		index = *polyIndices[poly];
			file.BinWriteDWord	(index);
		};
	};

	// Tree-Structure
	file.BinStartChunk		(zFCHUNK_BSP_TREE);
	{
		file.BinWriteInt	(numNodes);
		file.BinWriteInt	(numLeafs);
		bspRoot->SaveBINRec	(file);
	};

	// Leaf Light Info
	file.BinStartChunk		(zFCHUNK_BSP_LEAF_LIGHT);
	{
		for (int i=0; i<numLeafs; i++) 
		{
			file.BinWrite	(&(leafList[i].lightPosition), sizeof(leafList[i].lightPosition));
		};
	};

	// Outdoor-Sektoren
	if (sectorList.GetNum()>0)
	{
		file.BinStartChunk				(zFCHUNK_BSP_OUTDOOR_SECTORS);
		{
			// SectorList
			file.BinWriteInt			(sectorList.GetNumInList());
			for (int i=0; i<sectorList.GetNumInList(); i++) {
				zCBspSector *sector = sectorList[i];
				file.BinWriteString		(sector->sectorName);
				file.BinWriteInt		(sector->sectorNodes.GetNumInList());
				file.BinWriteInt		(sector->sectorPortals.GetNumInList());
				for (int j=0; j<sector->sectorNodes.GetNumInList(); j++) {
					zCBspBase	*base = sector->sectorNodes[j];
					zDWORD		index;
					// FIXME: Wenn auch NODES moeglich sein sollen, muss das hier geaendert werden !!!
					if (!base->IsLeaf()) {
						zERR_FATAL ("D: Save-BSP: Leafs expected !!!");
					};
					index = (zDWORD(base)-zDWORD(leafList)) / sizeof(zCBspLeaf);
					file.BinWriteDWord	(index);
				};
				for (    j=0; j<sector->sectorPortals.GetNumInList(); j++) {
					zCPolygon	*portal		= sector->sectorPortals[j];
//					zDWORD		index		= sortPolyList.Search(portal);
					zDWORD		index		= *polyIndices[portal];
					file.BinWriteDWord	(index);
				};
			};

			// PortalList
			file.BinWriteInt			(portalList.GetNum());
			for (i=0; i<portalList.GetNum(); i++) 
			{
				zCPolygon	*portal		= portalList[i];
//				zDWORD		index		= sortPolyList.Search(portal);
				zDWORD		index		= *polyIndices[portal];
				file.BinWriteDWord		(index);
			};
		};
	};

	// End-Markierung 
	file.BinStartChunk		(zFCHUNK_BSP_END);
	file.BinWriteByte		(zBYTE(66));	

	// Header & Laenge eintragen
	int actPos		= file.file->Pos();
	chunkLen		= actPos-fileStartPos-(8);	 //6
	file.file->Seek  (fileStartPos+sizeof(version));
	file.file->Write (&chunkLen, sizeof(chunkLen));
	file.file->Seek  (actPos);

	// ?? SANITY ?? 
	if (chunkLen>90000000)	// 90MB
		zERR_FAULT ("D: BSP: SAVEBIN: problem !!?? An Hersteller wenden :( !!! chunkLen: "+zSTRING(chunkLen));

	//
//	file.BinEndChunk	();			// kein BinClose() !
//	bspRoot->DescribeTree();
};


//S:RM4_TUER

void zCBspTree::ConnectMaterialsToSectors () 
{
	for (int i=0; i<zCMaterial::GetStaticClassDef()->GetNumObjects(); i++)
	{
		zCMaterial *mat = static_cast<zCMaterial*>(zCMaterial::GetStaticClassDef()->GetObjectByIndex(i));
		const zSTRING& matName = mat->GetName();
		if (!matName.IsEmpty()) 
		{
			if (matName[1]==':') {
				if (matName[0]=='P') {
					// Portal-Material
					zSTRING		frontName, backName;
					CutSectorNames				(matName, frontName, backName);
					mat->SetAlphaBlendFunc		(zRND_ALPHA_FUNC_BLEND); 
					mat->SetBspSectorFront		(GetBspSectorByName(frontName));
					mat->SetBspSectorBack		(GetBspSectorByName(backName ));
				} else
				if (matName[0]=='S') {
					// Sektor-Material
					zSTRING name(mat->GetName());
					name.Delete (zSTRING(":"), zSTR_TO);
					name.Delete (zSTRING("_"), zSTR_FROM);
					zCBspSector *sector = GetBspSectorByName(name); 
					mat->SetBspSectorFront		(sector);
					mat->SetBspSectorBack		(sector);
				};
			}
		};
	};
};

zBOOL zCBspTree::LoadBIN	(zCFileBIN& file, zBOOL skipThisChunk) 
{
	zERR_MESSAGE (3, 0, "D: BSP: Loading Mesh & BSP..");

	// Zur Sicherheit entleert sich das Objekt ersteinmal
	DisposeTree			();

	// Header laden
	zDWORD	versionNow	= GetFileBinaryVersion();
	zDWORD	version;
	zDWORD	chunkLen;
	zDWORD  skipTarget;
	file.file->Read		(&version , sizeof(version));
	file.file->Read		(&chunkLen, sizeof(chunkLen));

	//
	skipTarget			= file.file->Pos() + chunkLen;

	// ?? SANITY ?? 
	if (chunkLen>90000000)	// 50MB
		zERR_FAULT ("D: BSP: LOADBIN: problem !!?? An Hersteller wenden :( !!! chunkLen: "+zSTRING(chunkLen));

	if (skipThisChunk) {
		zERR_MESSAGE (3, 0, "D: BSP: Skipping BSP/Mesh File-Chunk..");
	} else
	if (version!=versionNow) {
		zERR_WARNING ("D: BSP: Skipping BSP/Mesh Chunk, cannot read old format, file: "+zSTRING(int(version))+", now: "+zSTRING(int(versionNow)));
	};
	if ((skipThisChunk) || (version!=versionNow))
	{
		file.file->Seek (skipTarget);
		return FALSE;
	};
	
	// 
	actBspTree = this;
	sectorList.DeleteList();

	// Mesh
	{
		zERR_MESSAGE (3, 0, "D: MESH: Loading Mesh..");
		if (!mesh) mesh = zNEW(zCMesh());
 		zBOOL loadOK = mesh->LoadMSH (file);
		// Mesh im alten Format ?
		if (!loadOK) 
		{
			file.file->Seek (skipTarget);
			return FALSE;
		};
	};
 
	// BSP
	zERR_MESSAGE (3, 0, "D: BSP : Loading Tree..");
	int		num;
	zWORD	id;
	zLONG	len;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
		case zFCHUNK_BSP:
			{
				zTBspTreeMode	mode;
				zWORD			vers;
				file.BinReadWord (vers);
				if (vers!=zBSP_FILE_VERS) {
					zERR_FATAL ("D: zBSP(zCBspTree::LoadBIN): wrong bsp-file version, engine: "+zSTRING(zBSP_FILE_VERS)+", file: "+zSTRING(vers));
					return FALSE;
				};
				file.BinRead	(&mode, sizeof(mode));
				SetBspTreeMode	(mode);
			};
			break;
		case zFCHUNK_BSP_POLYLIST:
			{
				file.BinReadInt	(numPolys);
				treePolyList	= zNEW(zCPolygon*) [numPolys];
				zDWORD	*block	= zNEW(zDWORD	 ) [numPolys];
				file.BinRead	(block, sizeof(*block)*numPolys);
				for (int i=0; i<numPolys; i++)
					treePolyList[i] = mesh->SharePoly(block[i]);
				delete[] block;
			};
			break;
		case zFCHUNK_BSP_TREE:
			{
				
				file.BinReadInt	(numNodes);
				file.BinReadInt	(numLeafs);
				nodeList	= zNEW(zCBspNode) [numNodes];
				delete[] leafList;
				leafList	= zNEW(zCBspLeaf) [numLeafs];
				actNodePtr	= nodeList;
				actLeafPtr	= leafList;
				bspRoot		= actNodePtr++;
				bspRoot->parent		= 0;
				bspRoot->LoadBINRec (file);
			};
			break;
		case zFCHUNK_BSP_LEAF_LIGHT:
			if (numLeafs>0)
			{
				zPOINT3 *lightPositionList		= zNEW(zPOINT3) [numLeafs];
				file.BinRead					(lightPositionList, sizeof(zPOINT3)*numLeafs);
				for (int i=0; i<numLeafs; i++)
				{
					leafList[i].lightPosition	= lightPositionList[i];
				};
				delete[] lightPositionList;
			};
			break;
		case zFCHUNK_BSP_OUTDOOR_SECTORS:
			{
				file.BinReadInt		(num);
				sectorList.AllocAbs	(num);
				for (int i=0; i<num; i++) 
				{
					zCBspSector *sector = zNEW(zCBspSector);
					int numSectorNodes, numSectorPortals;
					file.BinReadString				(sector->sectorName);
					file.BinReadInt					(numSectorNodes);
					file.BinReadInt					(numSectorPortals);
					sector->sectorNodes  .AllocAbs	(numSectorNodes);
					sector->sectorPortals.AllocAbs	(numSectorPortals);
					sector->sectorIndex				= i;
					int j;
					zDWORD index;
					// FIXME: hier evtl. BLOCKREADS !
					for (j=0; j<numSectorNodes; j++) {
						file.BinReadDWord			(index);
						sector->sectorNodes.Insert	(&leafList[index]);
					};
					for (j=0; j<numSectorPortals; j++) {
						file.BinReadDWord			(index);
						zCPolygon	*portal		= mesh->SharePoly(index);
						sector->sectorPortals.Insert(portal);
					};
					sectorList.Insert (sector);
				};
				ConnectMaterialsToSectors();

				// PortalList
				file.BinReadInt		(num);
				portalList.AllocAbs	(num);
				zDWORD index;
				for (i=0; i<num; i++) {
					file.BinReadDWord		(index);
					zCPolygon	*portal		= mesh->SharePoly(index);
					portalList.Insert		(portal);
				};
			};
			break;
		case zFCHUNK_BSP_END: 
			file.BinSkipChunk();
			goto fileEnd;
			break;
			
		default:
			file.BinSkipChunk();
		};
	}
fileEnd:;

	return TRUE;
};


/*	
#ifdef zBSP_DEBUG_OUTDOOR 
	if (zinput->KeyPressed(KEY_F6)) skyVari	= (skyVari+1)%2;
	if (zinput->KeyPressed(KEY_F8)) dontCull = !dontCull;
	if (zinput->KeyPressed(KEY_F7)) useLOD	= !useLOD;
	if (zinput->KeyPressed(KEY_LSHIFT)) {
		if (zinput->KeyPressed(KEY_PLUS))	lodValue += 1000;
		if (zinput->KeyPressed(KEY_MINUS))	lodValue -= 1000;
		if (lodValue<0) lodValue = 0;
	};
#endif
*/

/*
  // pseudocode for a preorder traversal with subtree culling
        //

        Traverse()
        {
           initialise_stack()
           push(root)

           while (stack_not_empty) {
              pop()
              if (node != NULL) {
                 if (node_is_a_leaf)
                    visit_node()
                 else {
                    if (camera_in_front_of_partition) {
                       if (view_frustum_intersects_partition)
                          push(back_child)
                       push(front_child)
                    } else {
                       if (view_frustum_intersects_partition)
                          push(front_child)
                       push(back_child)
                    }
                 }
              }
           }
        }


     the stack is an array and the geometry is assumed to be stored in the
     external nodes of the tree.  if, however, the geometry is stored in
     the internal nodes, modify the algorithm to yield an inorder traversal.

*/

/*
Detail-Objects

struct zTDetailObject {
	zPOINT3		pos;
	zVEC3		normalWS;
};

static zCArray<zTDetailObject>	detailObjectList;
	detailObjectList.EmptyList();

  		{
			if (this->polyPlane.normal[VY]>0.7F) {
//				zPOINT3 center = this->GetCenter();
//				zlineCache.Line3D (center, center+zVEC3(0,10,0), GFX_GREEN);
				zTDetailObject detailObject;
				detailObject.pos		= this->GetCenter();
				detailObject.normalWS	= this->polyPlane.normal;
				detailObjectList.Insert (detailObject);
			};
		};

  	//
	{
		zCMesh *detailMesh = 0;
		if (!detailMesh)	detailMesh = zCMesh::Load ("OW_LOB_BUSH_V4.3DS");
		zCCamera::activeCam->Activate();
		zMATRIX4 camTrafoWorldToCam = zCCamera::activeCam->camMatrix;
		zMAT4 matrix = Alg_Identity3D();
		zTRenderContext renderContext;
		renderContext.Clear();
		renderContext.cam	= zCCamera::activeCam;
		
		for (int i=0; i<detailObjectList.GetNum(); i++)
		{
			matrix.SetUpVector		(detailObjectList[i].normalWS);
//			matrix.SetUpVector		(zVEC3(0,1,0));
			matrix.SetAtVector		(zVEC3(1,0,0));
			matrix.SetRightVector	(zVEC3(0,0,1));
			matrix.MakeOrthonormal	();
			matrix.SetTranslation	(detailObjectList[i].pos);

			zCCamera::activeCam->camMatrix    = camTrafoWorldToCam * matrix;
			zCCamera::activeCam->camMatrixInv = zCCamera::activeCam->camMatrix.InverseLinTrafo(); 
			zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
			zCCamera::activeCam->SetUpFrustum(); 
			detailMesh->Render(renderContext);
		};
	};

*/

struct zTLightScore {
	int		index;
	zREAL	score;
};

static int CompareLightScore ( const void *arg1, const void *arg2 ) 
{
	const zTLightScore* const light1= (zTLightScore*)arg1; 
	const zTLightScore* const light2= (zTLightScore*)arg2;
//	return (light1->score - light2->score);
	if (light1->score<light2->score)	return -1;
	else								return +1;	// "gleich" gibt's nicht
};

void zCBspTree::CalcStaticLeafLightData () 
{
	zERR_MESSAGE (8, 0, "D: BSP: calculating static leaf lightData ..");			// [EDENFELD] 1.09: Errorlevel hochgesetzt
	for (int i=0; i<numLeafs; i++)
	{
		zCBspLeaf *leaf = &(leafList[i]);

		zPOINT3 samplePos = leaf->bbox3D.GetCenter();

		zCArray<zCVobLight*>		vobStatLightList(8);	
		zCArraySort<zTLightScore>	statLightScore	(8);
		statLightScore.SetCompare	(CompareLightScore);

		for (int j=0; j<leaf->lightVobList.GetNum(); j++) 
		{
			zCVobLight *light	= leaf->lightVobList[j];
			if (light->GetIsStatic())
			{
				// Wichtigkeit der Lichquelle berechnen
				zTLightScore			lightScore;
				zREAL lightIntensity	= zREAL(1.0F) - (light->GetColor().GetIntensityFloat() / zREAL(255.0F));
				lightScore.score		= ((samplePos  - light->GetPositionWorld()).LengthApprox()) * light->GetRangeInv();
				lightScore.score		*= lightIntensity;
				zClamp01				(lightScore.score);

				//
				lightScore.index		= statLightScore.GetNum();
				statLightScore.Insert	(lightScore);
				vobStatLightList.Insert	(light);
			};
		};

		if (vobStatLightList.GetNum()>0)
		{
			// Sortierreihenfolge: kleiner...groesser
			statLightScore.QuickSort();

			leaf->lightPosition	= vobStatLightList[statLightScore[0].index]->GetPositionWorld();
		} else
		{
			leaf->lightPosition	= zVEC3(-99);
		};
	};
};



//																																		
//---------------------------------------------------------------------------------------------------
//**************************************    MACROS   ***************************************
//---------------------------------------------------------------------------------------------------
//																																		
template<class ELEMENT> 
class zTArrayEx : public zCArray<ELEMENT>
{
public:
	
		void			InsertEnd		( const zCArray< ELEMENT >& a_arrSource );
		ELEMENT*		AccessData		( void	);
		const ELEMENT*	GetData			( void	) const;
	
		typedef	zTArrayEx<ELEMENT>		zCArrayEx;
};


template < class ELEMENT > 
ELEMENT* zTArrayEx<ELEMENT>::AccessData	( void	) 
{
	return this->array;
}

template < class ELEMENT > 
const ELEMENT* zTArrayEx<ELEMENT>::GetData	( void	) const
{
	return this->array;
}

template < class ELEMENT > 
void	zTArrayEx<ELEMENT>::InsertEnd ( const zCArray< ELEMENT >& a_arrSource )
{
	// @DEVNODE: optimize via memcpy, already prepared
	for(int i = 0; i < a_arrSource.GetNum(); i++)
		this->Insert( a_arrSource[i] );
}


//***************************************************************************
//	CLASS zCBBox3D
//	Extended Box3D
//***************************************************************************
struct zCBBox3D : public zTBBox3D
{
	zVEC3			GetMagnitude			( void	) const
	{
		return	( this->maxs - this->mins );
	}

	zVEC3			GetCenter				( void	) const
	{
		zVEC3 vecCenter( this->maxs );
		vecCenter	+=		this->mins;
		vecCenter	*=		0.5f;

		return	vecCenter;
		
	}
};

//***************************************************************************
//	GLOBAL STUFF
//	zMIN, zMAX, IntersectsBox, DrawBox
//***************************************************************************


#define			zMIN( a, b ) ( a < b ? a : b )
#define			zMAX( a, b ) ( a > b ? a : b )


void DrawBox ( const zTBBox3D& a_Box )
{
	zVEC3 vec1, vec2;	
	
	// #1
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec2[VY]	=	a_Box.mins[VY];	vec2[VZ]	=	a_Box.mins[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #2
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec2[VY]	=	a_Box.mins[VY];	vec1[VZ]	=	a_Box.maxs[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #3
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec1[VY]	=	a_Box.maxs[VY];	vec2[VZ]	=	a_Box.mins[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #4
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec1[VY]	=	a_Box.maxs[VY];	vec1[VZ]	=	a_Box.maxs[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #5
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec2[VX]	=	a_Box.mins[VX];	vec2[VZ]	=	a_Box.mins[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #6
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec2[VX]	=	a_Box.mins[VX];	vec1[VZ]	=	a_Box.maxs[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #7
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec1[VX]	=	a_Box.maxs[VX];	vec2[VZ]	=	a_Box.mins[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #8
	vec1		=	a_Box.mins;		vec2		=	a_Box.maxs;
	vec1[VX]	=	a_Box.maxs[VX];	vec1[VZ]	=	a_Box.maxs[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #9
	vec1		=	a_Box.mins;		vec2		=	a_Box.mins;
	vec2[VZ]	=	a_Box.maxs[VZ];	
	zlineCache.Line3D( vec1, vec2 );
	// #10
	vec1		=	a_Box.mins;		vec2		=	a_Box.mins;
	vec1[VX]	=	a_Box.maxs[VX];	vec2[VX]	=	a_Box.maxs[VX];	vec2[VZ]	=	a_Box.maxs[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #11
	vec1		=	a_Box.maxs;		vec2		=	a_Box.maxs;
	vec1[VX]	=	a_Box.mins[VX];	vec2[VX]	=	a_Box.mins[VX];	vec1[VZ]	=	a_Box.mins[VZ];
	zlineCache.Line3D( vec1, vec2 );
	// #12
	vec1		=	a_Box.maxs;		vec2		=	a_Box.maxs;
	vec1[VZ]	=	a_Box.mins[VZ];	
	zlineCache.Line3D( vec1, vec2 );

}

//***************************************************************************
//	CLASS zCRayTurboAdmin
//	TurboRay Admin to manage rayturbo nodes
//***************************************************************************
//																			

int zCRayTurboAdmin::s_iPolyTreshold = zCRayTurboAdmin::zEMaxPolyThreshold;

//---------------------------------------------------------------------------------------------------
//**************************************    CON-/DESTRUCTOR   ***************************************
//---------------------------------------------------------------------------------------------------
//																																		
zCRayTurboAdmin::zCRayTurboAdmin ( void	)
{
}

zCRayTurboAdmin::~zCRayTurboAdmin ( void)
{
	this->ReleaseSpatialDatabase();
}

zCRayTurboAdmin& zCRayTurboAdmin::GetInstance( void	)
{
	static zCRayTurboAdmin ms_RayTurboAdmin;

	return ms_RayTurboAdmin;
}

zCRayTurbo* zCRayTurboAdmin::GetRayTurboItem ( const zCBspNode* a_pNode	)	const
{
	zCRayTurbo* pRayTurbo	=	NULL;
	this->m_mapRayTurbos.GetAt( const_cast<zCBspNode*>(a_pNode), pRayTurbo );
	return pRayTurbo;
}

zCRayTurbo* zCRayTurboAdmin::CreateRayTurboItem ( const zCBspNode* a_pNode	)
{
	zCRayTurbo* pRayTurbo	=	NULL;
	pRayTurbo	=	new zCRayTurbo( *a_pNode );

	this->m_mapRayTurbos.SetAt( const_cast<zCBspNode*>(a_pNode), pRayTurbo );

	return pRayTurbo;
}

zCRayTurbo* zCRayTurboAdmin::GetOrCreate( const zCBspNode* a_pNode	)
{
	if( FALSE == this->CanHaveSpatialInfo( a_pNode ) )
		return NULL;

	zCRayTurbo* pRayTurbo	=	this->GetRayTurboItem( a_pNode);
	if(NULL == pRayTurbo)
		pRayTurbo	=	this->CreateRayTurboItem( a_pNode );

	zERR_ASSERT( NULL != pRayTurbo );

	return pRayTurbo;
}

zBOOL zCRayTurboAdmin::CanHaveSpatialInfo( const zCBspNode* a_pNode	)
{
	// ***************************************************************
	// @DEVNOTE: INSERT HERE ACTIVATION AND DEACTIVATION
	// ***************************************************************
	if (s_iPolyTreshold<=0) return FALSE;
	return ( a_pNode->numPolys > s_iPolyTreshold );
}

void zCRayTurboAdmin::ReleaseSpatialDatabase( void	)
{
	this->m_mapRayTurbos.DeleteAll();
}


void  zCRayTurboAdmin::SetPolyTreshold( const int a_iPolyTreshold )
{
	s_iPolyTreshold=a_iPolyTreshold;
};


int	zCRayTurboAdmin::GetPolyTreshold()
{
	return s_iPolyTreshold;
};


//***************************************************************************
//	CLASS zCRayTurbo
//	TurboRay Admin to manage rayturbo nodes
//***************************************************************************
zCRayTurbo::zCRayTurbo( const zCBspNode& a_BSPNode	) : 
m_BspNode( a_BSPNode ),
m_MeshOctreeRoot( TRUE )
{
#ifdef _DEBUG
	static char pcBuffer[200];
	sprintf( pcBuffer, "** zCRayTurbo::zCRayTurbo created - Node 0x%08x: Maxpolys: %d \n", &a_BSPNode, a_BSPNode.numPolys );
	OutputDebugString( pcBuffer );
#endif

	// allocate indices
	zCMeshOctreeNode::zCArrPolys arrPolys;
	arrPolys.AllocAbs( a_BSPNode.numPolys );
	
	//
	// @DEVNOTE: Optimize
	//
	for(int i = 0; i < a_BSPNode.numPolys; i++)
		arrPolys.Insert( a_BSPNode.polyList[ i ] );

	this->m_MeshOctreeRoot.Build( arrPolys, zCRayTurboAdmin::GetPolyTreshold() / 6 );
}

zCRayTurbo::~zCRayTurbo ( void	)
{
}

void zCRayTurbo::CalculateOptimizedPolyList	( zCMeshOctreeNode::zCArrPolys& a_arrMatchedPolys	)
{
	// get hit information
	a_arrMatchedPolys.EmptyList();
	this->TraverseTree( a_arrMatchedPolys, this->m_MeshOctreeRoot );
}

void zCRayTurbo::TraverseTree ( zCMeshOctreeNode::zCArrPolys& a_arrMatchedPolys, const zCMeshOctreeNode& a_OctreeNode )
{

	zREAL scaleMin = 1.0f;
	zREAL scaleMax = 1.0f;

	// Only leaves _may_ have valid poly data
	if( TRUE == a_OctreeNode.IsLeaf() && a_OctreeNode.GetPolys().GetNum() > 0 )
	{
		// check if ray/box intersection
		if(TRUE == a_OctreeNode.GetBox().IsIntersecting( g_vecStartTrace, g_vecEndTrace - g_vecStartTrace, scaleMin, scaleMax ) && scaleMax>=0.0f && scaleMin<=1.0f ) 
		{
			zTArrayEx<zCPolygon*>& arrPolyEx	=	static_cast<zTArrayEx<zCPolygon*>&> ( a_arrMatchedPolys );
			arrPolyEx.InsertEnd( a_OctreeNode.GetPolys() );
		}
	}
	
	// Convert children, if any
	if( FALSE == a_OctreeNode.IsLeaf() )
	{
		zERR_ASSERT( 0 == a_OctreeNode.GetPolys().GetNum() );

		// check if ray/box intersection
		if(TRUE == a_OctreeNode.GetBox().IsIntersecting( g_vecStartTrace, g_vecEndTrace - g_vecStartTrace, scaleMin, scaleMax ) && scaleMax>=0.0f && scaleMin<=1.0f ) 
			for(int i = zCMeshOctreeNode::zEOctreeChild_Min; i < zCMeshOctreeNode::zEOctreeChild_Max; i++)
				this->TraverseTree( a_arrMatchedPolys, *a_OctreeNode.GetChild( static_cast<zCMeshOctreeNode::zEOctreeChild> (i) )	);
	}
}


//***************************************************************************
//	CLASS zCMeshOctreeNode
//	Octtree
//***************************************************************************

//*****************************************************************************
//** Default constructor
//*****************************************************************************
zCMeshOctreeNode::zCMeshOctreeNode(zBOOL a_bIsRoot)
{
	::memset( m_parrChildren, 0, sizeof( m_parrChildren ) );

	this->m_Box.Init();

	this->m_bIsRoot	=	a_bIsRoot;
	this->m_bIsNode	=	FALSE;
	this->m_bIsLeaf	=	FALSE;
}

//*****************************************************************************
//** Destructor
//*****************************************************************************
zCMeshOctreeNode::~zCMeshOctreeNode()
{
	int i	=	8;
	while(i--)
		delete this->m_parrChildren[i];
}

void zCMeshOctreeNode::EnlargeBox(const zCArrPolys& a_arrPolyList)
{
	zVEC3		vecMerge;
	float		fMax, fMin;
	int	i	=	a_arrPolyList.GetNum();

	if( i > 0 ) while( i-- )
	{
		zCPolygon* pPolygon	=	a_arrPolyList[i];
		int j	=	3;
		while(j--)
		{
			fMax	=	zMAX( pPolygon->vertex[j]->position[VX], pPolygon->vertex[j]->position[VY] );
			fMax	=	zMAX( pPolygon->vertex[j]->position[VZ], fMax);
			
			vecMerge	=	(fMax + 0.01f);
			this->m_Box.AddPoint( vecMerge );
			
			fMin	=	zMIN( pPolygon->vertex[j]->position[VX], pPolygon->vertex[j]->position[VY] );
			fMin	=	zMIN( pPolygon->vertex[j]->position[VZ], fMin);

			vecMerge	=	(fMin - 0.01f);
			this->m_Box.AddPoint( vecMerge );

		}
	}
}

void zCMeshOctreeNode::CopyPolys( const zCArrPolyInside& a_arrInsidePolygons, const zCArrPolys& a_arrPolys, 
								  int a_iCount, zCArrPolys&	a_arrPolysDst	)
{
	a_arrPolysDst.AllocAbs( a_iCount );

	zERR_ASSERT( a_arrPolys.GetNum() == a_arrInsidePolygons.GetNum() );

	for( int i = 0; i < a_arrPolys.GetNum(); i++ )
	{
		if( TRUE == a_arrInsidePolygons[ i ] )
			a_arrPolysDst.Insert(  a_arrPolys[ i ] );
	}
	
}


// octtree klasse bzw template sollte bei Gothic3 ein wenig strukturierter implementiert werden. 
void zCMeshOctreeNode::Build(const zCArrPolys& a_arrPolyList, int a_iVertexLimit)
{
	// Build bounding _cube_
	if( TRUE == this->IsRoot() )
		this->EnlargeBox( a_arrPolyList );
	
	
	// Determine faces which are (partially) inside the cube
	zVEC3 vecCenter;


	zCArrPolyInside arrPolyInside;
	arrPolyInside.AllocAbs( a_arrPolyList.GetNum() );


	int iVertexCount	=	0;
	for(int iPoly = 0; iPoly < a_arrPolyList.GetNum(); iPoly++)
	{

		zCPolygon* pPolygon	=	a_arrPolyList[ iPoly ];

		// unsafe method to set equal iPolyIndex == arrPolyInside.GetUpperBound() 
		// @DEVNOTE: Optimize
		int iDummy	=	FALSE;
		arrPolyInside.Insert( iDummy );

		// Is the center of the face inside the cube?
		if( TRUE == this->m_Box.IsTrivIn( pPolygon->GetCenter()) )
		{
			arrPolyInside[iPoly]		=	TRUE;
			iVertexCount				+=	3;
			continue;
		}
	}
	
	// No vertices inside the cube makes this node a leaf
	if( 0 == iVertexCount )
	{
		this->m_bIsLeaf		=	TRUE;
		return;
	}

	// Is this node a leaf or has it too many vertices to be one?
	if( iVertexCount > a_iVertexLimit )
	{
		// Set node status
		this->m_bIsNode		=	TRUE;

		// Build temporary local array
		zCArrPolys arrPolys;

		this->CopyPolys( arrPolyInside, a_arrPolyList, iVertexCount / 3, arrPolys );

		// Set child node box sizes
		zVEC3 vecParentHalf(this->m_Box.GetMaxExtent());
		zVEC3 vecChildMin, vecChildMax;
		zVEC3 vecParentMin( this->m_Box.mins );
		//zVEC3 vecParentMax( this->m_Box.maxs );

		// Create child nodes
		// standard constructor ?
		int i = 8;
		while(i--)
			this->m_parrChildren[ i ]	=	new zCMeshOctreeNode;

		int iCount = 0;
		for(int x = 0; x < 2; x++)
			for(int y = 0; y < 2; y++)
				for(int z = 0; z < 2; z++)
				{
					vecChildMin			=	vecParentMin;	
					vecChildMax			=	vecParentMin;	
					vecChildMin[VX]		+=	(x * vecParentHalf[VX]);
					vecChildMax[VX]		+=	((x + 1) * vecParentHalf[VX]);
					vecChildMin[VY]		+=	(y * vecParentHalf[VY]);
					vecChildMax[VY]		+=	((y + 1) * vecParentHalf[VY]);
					vecChildMin[VZ]		+=	(z * vecParentHalf[VZ]);
					vecChildMax[VZ]		+=	((z + 1) * vecParentHalf[VZ]);
					this->m_parrChildren[iCount]->m_Box.mins		=	vecChildMin;
					this->m_parrChildren[iCount]->m_Box.maxs		=	vecChildMax;
					iCount++;
				}

		// Build child nodes
		for(i = 0; i < 8; i++)
			this->m_parrChildren[i]->Build( arrPolys, a_iVertexLimit);

		// Rebuild boxes nodes
		for(i = 0; i < 8; i++)
			this->m_Box.CalcGreaterBBox3D( this->m_parrChildren[i]->GetBox() );

	}
	else
	{
		// Set leaf status
		this->m_bIsLeaf		=	TRUE;

		// Copy data to member array
		this->CopyPolys( arrPolyInside, a_arrPolyList, iVertexCount / 3, this->m_arrPolys );

		// resize bbox -> conservative size
		for(int i = 0; i < this->m_arrPolys.GetNum(); i++)
		{
			int j = this->m_arrPolys[i]->polyNumVert;
			if(j > 0) while(j--)
				this->m_Box.AddPoint( this->m_arrPolys[i]->vertex[j]->position );
			
			// add border
			this->m_Box.mins	-=	0.01f;
			this->m_Box.maxs	+=	0.01f;
		}
	}
}



// *******************************************************************************************************************
#pragma warning( default: 4244 ) 
//#pragma optimize( "", on)