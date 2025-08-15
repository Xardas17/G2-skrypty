// SpacerView.cpp : implementation of the CSpacerView class
//
//
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "MainFrm.h"
#include "SpacerDoc.h"
#include "SpacerView.h"
#include "spcCVobContainer.h"
#include "spcCInfoBar_Lights.h"

// z-Files
#include "z3d.h"
#include "zsky.h"
#include "zInput_Win32.h"
#include "zconsole.h"
#include "zmodel.h" 
#include "zwaynet.h"
#include "zphysics.h"	
#include "zrenderer.h"
#include "zCSCamera.h"
#include "zplayerinfo.h"

// o-Files
#ifdef COMPILING_GOTHIC	
	#include "ogame.h"		// Verwendung beim Rendern und Initialisieren (SetCamera etc.)
	#include "oWorld.h"		// wegen worldTimer
	#include "ooCarsten.h"	// Freelook
	#include "onpc.h"		// Verwendung fuer AI/Cutscene
	#include "oFocus.h"		// Verwendung fuer AI/Cutscene
	#include "oaihuman.h"	// Verwendung fuer AI/Cutscene
	#include "ospawn.h"		// Verwendung fuer AI/Cutscene
	#include "omobinter.h"		// Verwendung fuer den Vobcontainer
	#include "ogamemanager.h"
#endif

// spc-Files
#include "spcMoving.h"
#include "spcCConfiguration.h"
#include "spcCCompileWorldDlg.h"
#include "spcCCompileLightDlg.h"
#include "spcCWorkInfoDlg.h"
#include "spcCMacroDlg.h"
#include "spcCPositionDlg.h"
#include "spcCInputDialog.h"
#include "spcCHelpDlg.h"
#include "spcCInfoBar_Camera.h"
#include "spcCInfoBar_Events.h"
#include "spcCObjectSheet.h"
#include "spcCCSSequencer.h"
#include "spcCTextInfoDlg.h"
#include "spcCInfoBar.h"


#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global variables
zCView*			viewport			= NULL;
CSpacerView*	CSpacerView::view	= 0;


static int	pxXm;
static int	pxYm;
static int	pxX;
static int	pxY;

static zBOOL colldet_disabled		= FALSE;
static zBOOL colldet_stat_backup	= FALSE;
static zBOOL colldet_dyn_backup		= FALSE;

extern zBOOL		 g_bIsPlayingGame;
extern CGameManager* gameMan;

// #define _MAIN_

#include "spcCDibSection.h"

#define PICKED_VOB() infoBar ? dynamic_cast<zCVob*>(infoBar->GetSelectedVob()) : 0;

/////////////////////////////////////////////////////////////////////////////
// CSpacerView

IMPLEMENT_DYNCREATE(CSpacerView, CView)

BEGIN_MESSAGE_MAP(CSpacerView, CView)
	//{{AFX_MSG_MAP(CSpacerView)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()		
	ON_COMMAND(ID_VOB_INSERT, OnVobInsert)
	ON_COMMAND(ID_VOB_REMOVE, OnVobRemove)
	ON_UPDATE_COMMAND_UI(ID_VOB_REMOVE, OnUpdateVobRemove)
	ON_UPDATE_COMMAND_UI(ID_WORLD_COMPILE, OnUpdateWorldCompile)
	ON_COMMAND(ID_VOB_MOVE, OnVobMove)
	ON_UPDATE_COMMAND_UI(ID_VOB_MOVE, OnUpdateVobMove)
	ON_COMMAND(ID_VOB_TAKEOVER, OnVobTakeover)
	ON_UPDATE_COMMAND_UI(ID_VOB_TAKEOVER, OnUpdateVobTakeover)
	ON_COMMAND(ID_VOB_CONTROL, OnVobControl)
	ON_UPDATE_COMMAND_UI(ID_VOB_CONTROL, OnUpdateVobControl)
	ON_COMMAND(ID_VOB_COLLISION_DETECTION, OnVobCollisionDetection)
	ON_UPDATE_COMMAND_UI(ID_VOB_COLLISION_DETECTION, OnUpdateVobCollisionDetection)
	ON_COMMAND(ID_VOB_COLLDET, OnVobColldet)
	ON_COMMAND(ID_WAY_CREATE, OnWayCreate)
	ON_UPDATE_COMMAND_UI(ID_WAY_CREATE, OnUpdateWayCreate)
	ON_COMMAND(ID_POLY_PICKMATERIAL, OnPolyPickmaterial)
	ON_COMMAND(ID_POLY_APPLYM, OnPolyApplyTexWithMapping)
	ON_UPDATE_COMMAND_UI(ID_POLY_APPLYM, OnUpdatePolyApplyM)
	ON_COMMAND(ID_POLY_APPLY, OnPolyApplyTexture)
	ON_UPDATE_COMMAND_UI(ID_POLY_APPLY, OnUpdatePolyApplyTexture)
	ON_COMMAND(ID_VIEW_FOGGING, OnViewFogging)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FOGGING, OnUpdateViewFogging)
	ON_COMMAND(ID_WORLD_COMPILELIGHT, OnWorldCompilelight)
	ON_UPDATE_COMMAND_UI(ID_WORLD_COMPILELIGHT, OnUpdateWorldCompilelight)
	ON_COMMAND(ID_POLY_TOGGLE_SEL, OnPolyToggleSelection)	
	ON_UPDATE_COMMAND_UI(ID_POLY_PICKMATERIAL, OnUpdatePolyPickmaterial)
	ON_COMMAND(ID_VOB_SAVE_TREE, OnVobSaveTree)
	ON_COMMAND(ID_VOB_INSERT_TREE, OnVobInsertTree)
	ON_COMMAND(ID_VIEW_WIRE, OnViewWire)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WIRE, OnUpdateViewWire)
	ON_UPDATE_COMMAND_UI(ID_VOB_INSERT_TREE, OnUpdateVobInsertTree)
	ON_UPDATE_COMMAND_UI(ID_VOB_INSERTMESH_VOB, OnUpdateVobInsertmeshVob)
	ON_COMMAND(ID_VOB_PHYSICS, OnVobPhysics)
	ON_UPDATE_COMMAND_UI(ID_VOB_PHYSICS, OnUpdateVobPhysics)
	ON_COMMAND(ID_POLY_DESELECT, OnDeselect)
	ON_COMMAND(ID_POLY_APPLY_DES, OnPolyApplyDes)
	ON_COMMAND(ID_CS_INTEGRATE, OnCSIntegrate)
	ON_COMMAND(ID_POLY_PLANAR, OnPolyPlanar)
	ON_COMMAND(ID_CS_DECLARE_PC, OnCsDeclarePc)
	ON_UPDATE_COMMAND_UI(ID_CS_DECLARE_PC, OnUpdateCsDeclarePc)
	ON_UPDATE_COMMAND_UI(ID_CS_INTEGRATE, OnUpdateCsIntegrate)
	ON_COMMAND(ID_TOOLS_MACROS, OnToolsMacros)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullscreen)
	ON_COMMAND(ID_TOOLS_GOTOPOSITION, OnToolsGotoposition)
	ON_COMMAND(ID_TOOLS_GOTOORIGIN, OnToolsGotoOrigin)
	ON_COMMAND(ID_TOOLS_SPECIAL_SAVETMPDOC, OnToolsSpecialSavetmpdoc)
	ON_COMMAND(ID_TOOLS_SPECIAL_LOADTMPDOC, OnToolsSpecialLoadtmpdoc)	
	ON_COMMAND(ID_VIEWVOB_COPY, OnViewvobCopy)
	ON_COMMAND(ID_VIEWVOB_PASTE, OnViewvobPaste)
	ON_COMMAND(ID_VIEWVOB_PLAY, OnViewvobPlay)
	ON_UPDATE_COMMAND_UI(ID_VIEWVOB_PLAY, OnUpdateViewvobPlay)
	ON_COMMAND(ID_KEY_POPUP, OnKeyPopup)
	ON_UPDATE_COMMAND_UI(ID_VIEWVOB_PASTE, OnUpdateViewvobPaste)
	ON_UPDATE_COMMAND_UI(ID_VIEWVOB_COPY, OnUpdateViewvobCopy)
	ON_COMMAND(ID_VIEWVOB_GOTO_5METERS, OnViewvobGoto5meters)
	ON_COMMAND(ID_VIEWVOB_GOTO_2METERS, OnViewvobGoto2meters)
	ON_COMMAND(ID_VIEWVOB_GOTO_1METER, OnViewvobGoto1meter)
	ON_COMMAND(ID_VIEWVOB_GOTO_HALFMETER, OnViewvobGotoHalfmeter)
	ON_COMMAND(ID_SHORTCUT_1_DEF, OnShortcut1Def)
	ON_COMMAND(ID_SHORTCUT_1, OnShortcut1)
	ON_COMMAND(ID_SHORTCUT_2, OnShortcut2)
	ON_COMMAND(ID_SHORTCUT_2_DEF, OnShortcut2Def)
	ON_COMMAND(ID_SHORTCUT_3, OnShortcut3)
	ON_COMMAND(ID_SHORTCUT_3_DEF, OnShortcut3Def)
	ON_COMMAND(ID_SHORTCUT_4, OnShortcut4)
	ON_COMMAND(ID_SHORTCUT_4_DEF, OnShortcut4Def)	
	ON_COMMAND(ID_VIEWVOB_VOB_LETFALLDOWN, OnViewvobVobLetfalldown)			
	ON_COMMAND(ID_VIEWVOB_VOB_CREATEPRESET, OnVobCreatePreset)
	ON_UPDATE_COMMAND_UI(ID_VIEWVOB_VOB_CREATEPRESET, OnUpdateViewvobVobCreatepreset)
	ON_COMMAND(ID_VIEW_TOGGLESOUND, OnViewTogglesound)
	ON_COMMAND(ID_VIEW_WAYNET, OnViewWaynet)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WAYNET, OnUpdateViewWaynet)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOGGLESOUND, OnUpdateViewTogglesound)
	ON_UPDATE_COMMAND_UI(ID_POLY_TOGGLE_SEL, OnUpdatePolyToggleSel)
	ON_UPDATE_COMMAND_UI(ID_POLY_PLANAR, OnUpdatePolyPlanar)
	ON_UPDATE_COMMAND_UI(ID_POLY_DESELECT, OnUpdateDeselect)
	ON_UPDATE_COMMAND_UI(ID_POLY_APPLY_DES, OnUpdatePolyApplyDes)
	ON_UPDATE_COMMAND_UI(ID_VOB_COLLDET, OnUpdateVobColldet)	
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEWEDIT_TOGGLEBILINEARFILTERING, OnToggleBilinearFiltering)
	ON_UPDATE_COMMAND_UI(ID_VIEWEDIT_TOGGLEBILINEARFILTERING, OnUpdateToggleBilinearFiltering)
	ON_COMMAND(ID_VOB_INSERT_BY_KEY, OnVobInsertByKey)
	ON_COMMAND(ID_CS_REGET, OnCsReget)
	ON_COMMAND(ID_VIEWVOB_VOB_SIZEDOWNBBOX, OnViewvobVobSizedownbbox)		
	ON_COMMAND(ID_VIEWEDIT_TOGGLECAMSPLINES, OnVieweditTogglecamsplines)
	ON_UPDATE_COMMAND_UI(ID_VIEWEDIT_TOGGLECAMSPLINES, OnUpdateVieweditTogglecamsplines)
	ON_WM_CAPTURECHANGED()
	ON_COMMAND(ID_VOB_TEST, OnVobTest)
	ON_UPDATE_COMMAND_UI(ID_VOB_TEST, OnUpdateVobTest)
	ON_COMMAND(ID_VIEWEDIT_TEXTOUTPUT, OnVieweditTextoutput)
	ON_UPDATE_COMMAND_UI(ID_VIEWEDIT_TEXTOUTPUT, OnUpdateVieweditTextoutput)
	ON_COMMAND(ID_VIEWEDIT_TOGGLEINFOTEXT, OnVieweditToggleinfotext)
	ON_UPDATE_COMMAND_UI(ID_VIEWEDIT_TOGGLEINFOTEXT, OnUpdateVieweditToggleinfotext)
	ON_COMMAND(ID_VIEW_VOB, OnViewVob)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VOB, OnUpdateViewVob)
	ON_COMMAND(ID_VOB_VOBNAME, OnVobVobname)
	ON_UPDATE_COMMAND_UI(ID_VOB_VOBNAME, OnUpdateVobVobname)
	ON_UPDATE_COMMAND_UI(ID_VOB_VIEWALLPROPERTIES, OnUpdateVobProperties)
	ON_COMMAND(ID_VOB_VIEWALLPROPERTIES, OnVobProperties)	
	ON_COMMAND(ID_VIEWVOB_VOB_MOVEHERE, OnViewvobVobMovehere)
	ON_COMMAND(ID_TOGGLE_CAM_POS, OnToggleCamPos)
	ON_UPDATE_COMMAND_UI(ID_TOGGLE_CAM_POS, OnUpdateToggleCamPos)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_WORLD_COMPILE, OnWorldCompile)
	ON_COMMAND(ID_REMEMBER_CAM_POS, OnRememberCamPos)
	ON_UPDATE_COMMAND_UI(ID_REMEMBER_CAM_POS, OnUpdateRememberCamPos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpacerView construction/destruction

extern HWND d3d_preferedWindow;


zCSelPoly::zCSelPoly(zCPolygon* _poly)
{
	zERR_ASSERT(_poly);
	poly= _poly;
	mat	= 0;
	if (poly) 
	{
		mat= poly->GetMaterial();
		if (mat) mat->AddRef();
	}
};

zCSelPoly::~zCSelPoly()
{
	poly=0;
	zRELEASE(mat);
};

void zCSelPoly::SetMaterial(zCMaterial* _mat)
{
	zRELEASE(mat);
	mat=_mat;
	if (mat) mat->AddRef();
};

zCMaterial*	zCSelPoly::GetMaterial()
{
	return mat;
};

zCPolygon* zCSelPoly::GetPolygon()
{
	return poly;
};
	
CSpacerView::CSpacerView() 
			:lastCompileWorldAction(), selVertex()
{	
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of CSpacerView...");

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/
	
	view = this;	

	Init();
	
	counterfrequency.QuadPart	= 0;	
	QueryPerformanceFrequency(&counterfrequency);	

	rememberedPositions.AllocAbs(10);

	for (int i=0;i<=9; i++)
	{		
		rememberedPositions.InsertAtPos(zMAT4(0),i);
	}

	/*
	if (zrenderer) zrenderer->Vid_SetScreenMode(zRND_SCRMODE_HIDE);
	*/

	infoBar = 0;
	
	EnableDrawing(FALSE);

	zERR_MESSAGE(7,zERR_END,"");
}


CSpacerView::~CSpacerView()
{	
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing CSpacerView-Instance ...");	
	Deinit();
	InitNull();	
	view=0;	
	zERR_MESSAGE(7,zERR_END,"");	
}

static spcCMovement* movementCtrl;

void CSpacerView::InitNull()
{
	// modes
	modeMove	= MV_NORMAL;
	// modeWorld	= WORLD_NORMAL;
	modeView	= VIEW_PERSON;
	
	modeSelectPolygons	= true;
	modePickMaterial	= false;
	modeTexManip		= false;
	modeVertManip		= false;	
	modeFullscreen		= false;
	camLastRemembered	= false;
	camLastAutoRemembered = false;
	drawSuccess			= false;

	view_waynet		= FALSE;
	view_sound		= TRUE;

	SelectMaterial	= 0;

	leakPolyList	= 0;
	leakPolyCurrent	= 0;
	
	//movement		= 0;	
	selPolyList		= 0;
	selPolyList2	= 0;	
	int i;
	
	for (i=0;i<SPC_NUM_VIEWS;i++) 
	{
		view_show[i]	= false;
		dib[i]			= 0;	
		camera[i]		= 0;
		camera_vob[i]	= 0;	
		viewport[i]		= 0;
	}
	view_show[0] = true;
	viewInfoText = true;

	vobCopyBuffer	= 0;
	SelectMaterial	= 0;

	// view
	drawSmoothMesh	= -1;
	drawWire		= -1;
	drawMode		= -1;
	drawShadeMode	= -1;
	wire			= FALSE;
	big				= FALSE;
	
	pickedPoly		= 0;	
	pickedVertex	= 0;
	pickedWaypoint2nd	= 0;
	pickedWaypoint	= 0;
	
	leakPolyList	= 0;
	leakPolyCurrent = 0;	
	
	playAsVob		= 0;	
}

void CSpacerView::Init()
{			
	zERR_MESSAGE(6,0,"B: SPC: SpacerView::Init. All");
		
	InitNull();

	infoBar = 0;
	if (CMainFrame::mainframe) infoBar = CMainFrame::mainframe->GetInfoBar();

	zERR_MESSAGE(6,0,"B: SPC: SpacerView::Init. Polygonslists");
	
	selPolyList = new zCList<zCSelPoly>;		
	selPolyList->DeleteList();
	
	selPolyList2 = new zCList<zCSelPoly>;		
	selPolyList2->DeleteList();	

	SelectMaterial=0;

	viewTextOut=false;
};

void CSpacerView::Deinit()
{
	if (playAsVob) PlayAs(0);

	VobSelect(NULL,true);	

	zERR_MESSAGE(6,0,"B: SPC: SpacerView::Deinit. Deinit Camera.");
	camera[0]=0;
	zERR_MESSAGE(6,0,"B: SPC: SpacerView::Deinit. Deinit Movement.");
	// delete movement;movement=0;	
	zERR_MESSAGE(6,0,"B: SPC: SpacerView::Deinit. Deinit Polygonlistes.");
	delete selPolyList;		selPolyList=0;
	delete selPolyList2;	selPolyList2=0;

	zERR_MESSAGE(6,0,"B: SPC: SpacerView::Deinit. Deinit SelectMaterial.");
	zRELEASE(SelectMaterial);	SelectMaterial=0;
}

void CSpacerView::Reset()
{
	EnableDrawing(false);

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: SpacerView-Reset");

		zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: SpacerView-Reset. Deinit");
		Deinit();	
		zERR_MESSAGE(4,zERR_END,"");

		zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: SpacerView-Reset. Init");
		Init();	
		zERR_MESSAGE(4,zERR_END,"");

	zERR_MESSAGE(4,zERR_END,"B: SPC: SpacerView-Reset. Finished");

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/
};


/////////////////////////////////////////////////////////////////////////////
// CSpacerView drawing


zPOINT3 point1,point2;
//zSTRING vobname,str1,str2;

void CSpacerView::RenderInfo(CDC* dc)
{	
	
	static int frameCount=-1;frameCount = (frameCount<5)?frameCount+1:0;
	static int frameFps=0;
	// calculate frame-rate
	LARGE_INTEGER newcount;QueryPerformanceCounter(&newcount);
	LARGE_INTEGER dif;dif.QuadPart = newcount.QuadPart-counter.QuadPart;
	if (counterfrequency.QuadPart!=0)
	{
		int ms = int(1000 * dif.QuadPart / counterfrequency.QuadPart);
		int fps = 1000 / ms;
		counter = newcount;		

		if (frameCount==0) frameFps = fps;
	}
	viewport[0]->Print(100,50, "fps:"+zSTRING(frameFps));	
	viewport[0]->Print(100,50 + viewport[0]->FontY(), "clip:"+zSTRING(spcConfig.farclipping,2)+"x - light:"+zSTRING(playerLightInt)+"/"+zSTRING(spcConfig.camlight));
}

void CSpacerView::DrawLine ( zCCamera *cam, zCVob* v1, zCVob* v2, zCOLOR col )
{
	/*
	zPOINT3 csPoint1, csPoint2;	// world/camera-space
	zPOINT2 ssPoint1, ssPoint2;						// screen-space X,Y

	
	csPoint1 = zCCamera::activeCam->Transform (a);
	csPoint2 = zCCamera::activeCam->Transform (b);

	Alg_ClipAtZ1(csPoint1,csPoint2);

	if ( csPoint1[VZ] < 1 || csPoint1[VZ] < 1 ) return;

	zCCamera::activeCam->Project (&csPoint1, ssPoint1[VX], ssPoint1[VY]);
	zCCamera::activeCam->Project (&csPoint2, ssPoint2[VX], ssPoint2[VY]);

	int x1 = (int)ssPoint1[VX];
	int y1 = (int)ssPoint1[VY];
	int x2 = (int)ssPoint2[VX];
	int y2 = (int)ssPoint2[VY];	
	
	if (!screen->ClipLine(x1,y1,x2,y2)) return;
	
	zrenderer -> DrawLineZ	((float)x1,(float)y1,(float)1/csPoint1[VZ],(float)x2,(float)y2,(float)1/csPoint2[VZ],col);

	*/
	if (!cam || !v1 || !v2) return;
	
	zPOINT3 wsPoint1, wsPoint2, csPoint1, csPoint2;	// world/camera-space
	zPOINT2 ssPoint1, ssPoint2;						// screen-space X,Y

	wsPoint1 = v1	-> GetPositionWorld();
	wsPoint2 = v2	-> GetPositionWorld();

	csPoint1 = cam->Transform (wsPoint1);
	csPoint2 = cam->Transform (wsPoint2);
	Alg_ClipAtZ0(csPoint1,csPoint2);

	if (csPoint1[VZ]>=0) 
	{
		cam->Project (&csPoint1, ssPoint1[VX], ssPoint1[VY]);
	} 
	else return;
	
	if (csPoint2[VZ]>=0) 
	{
		cam->Project (&csPoint2, ssPoint2[VX], ssPoint2[VY]);
	}
	else return;

	float camSpaceInf1 = (csPoint1[VZ]!=0 ? 1/csPoint1[VZ] : 0);
	float camSpaceInf2 = (csPoint1[VZ]!=0 ? 1/csPoint2[VZ] : 0);	
	
	int x1 = (int)ssPoint1[VX];
	int y1 = (int)ssPoint1[VY];
	int x2 = (int)ssPoint2[VX];
	int y2 = (int)ssPoint2[VY];
	if (!screen->ClipLine(x1,y1,x2,y2)) return;
	
	if (zrenderer) zrenderer->DrawLineZ((float)x1,(float)y1,camSpaceInf1,(float)x2,(float)y2,camSpaceInf2,col);
	
	if (csPoint1[VZ]<1000) 
	{	
		screen -> Print(screen->anx(x1),screen->any(y1),v1->GetVobName());
	}
	if (csPoint2[VZ]<1000) 
	{
		screen -> Print(screen->anx(x2),screen->any(x2),v2->GetVobName());
	}

}



// [EDENFELD] 1.33 neu aus ModSource
void CSpacerView::OnDraw(CDC* pDC)
{	
	if ( ::g_bIsPlayingGame ) return;

	if (!CSpacerDoc::doc) return;
	
	drawSuccess=false;

	#ifdef COMPILING_GOTHIC			
		oCNpc::SetNpcAIDisabled(TRUE);	
		if (ogame && ogame->GetSpawnManager()) ogame->GetSpawnManager()->SetSpawningEnabled(FALSE);		
	#endif	
	
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (!world || !CSpacerDoc::doc->IsAWorldLoaded())
	{
		OnDrawStartScreen(pDC);		
	}
	else if (world && !world->IsCompiled())
	{
		RECT rect;
		CClientDC ClientDC(this);				
		ClientDC.GetClipBox		(&rect);
		ClientDC.FillSolidRect	(&rect, RGB(0,0,0));								
		ClientDC.SetTextColor	(RGB(255,255,255));
		ClientDC.TextOut		(100,100,"World loaded but uncompiled");
		ClientDC.TextOut		(100,200,"Compile to view and manipulate the world");
		
		EnableDrawing(false);
	}
	else if (world)
	{
		if (!viewport[0])	return;
		if (!dib[0])		return;
		if (!camera[0])		return;
						
		EnableDrawing(false);
		
		// Timerwerte ermitteln
		static int		frameFps = 0;
		static zREAL	secTimer = 0.0f;
		LARGE_INTEGER	newcount;QueryPerformanceCounter(&newcount);
		LARGE_INTEGER	dif;dif.QuadPart = newcount.QuadPart-counter.QuadPart;
		if (counterfrequency.QuadPart>0)
		{
			int ms = int(1000 * dif.QuadPart / counterfrequency.QuadPart);		
			int fps = (ms>0)? (1000/ms) : 0;
			// int fps = 1000/ms;
			counter = newcount;
			frameFps = fps;
			secTimer+=ms;

			int upperBound = 1000;

			// [EDENFELD] 1.33c: Neuer Button für schnelles Updaten des Vobcontainers
			if (CMainFrame::mainframe					 && 
				CMainFrame::mainframe->GetVobContainer() && 
				CMainFrame::mainframe->GetVobContainer()->m_bFastUpdate) 
			{
				upperBound = 100;
			}
			
			if (secTimer>upperBound) secTimer=0.0f;
		}
		if (frameFps>0) 
		{
			// dynamisches Licht ?
			if (CMainFrame::mainframe						&&
				CMainFrame::mainframe->GetLightInfoBar()	&&
				CMainFrame::mainframe->GetLightInfoBar()->m_bLightDynCompile )
			{
				static int frameCounter = 0;
				static zPOINT3 lastPos = zPOINT3(0,0,0);
				if ( CMainFrame::mainframe								 &&
					 CMainFrame::mainframe->GetLightInfoBar()			 &&
					 CMainFrame::mainframe->GetLightInfoBar()->cur_vob ) 
				{
					if (++frameCounter % 2) 
					{
						float distance = (CMainFrame::mainframe->GetLightInfoBar()->cur_vob->GetPositionWorld() - lastPos).Length();

						if (distance > 2)
						{
							spcCCompileLightAction compileAction;
							compileAction.dynCompile = true;
							Do_CompileLight(compileAction);
							lastPos = CMainFrame::mainframe->GetLightInfoBar()->cur_vob->GetPositionWorld();
						}
					}
				}
			}

			
			// Init Draw
			OnDrawInitialize(pDC);

			// Before Render
			OnDrawBeforeRender(pDC);	

			// Rendern
			CSpacerDoc::doc->session->Render();
	
			// After Render
			OnDrawAfterRender(pDC);			

			// Informationsanzeige
			if (viewInfoText)
			{
				viewport[0]->Print(100,50, "fclip:"+zSTRING(spcConfig.farclipping,2) + "x, light:"+zSTRING(playerLightInt)/*+"/"+zSTRING(spcConfig.camlight)*/+", movespeed:"+zSTRING(spcConfig.movespeed));
				viewport[0]->Print(100,50 + viewport[0]->FontY(), "fps:"+zSTRING(frameFps));
			}
			
			// Vobs in Boundingsbox einsammeln
			if (secTimer == 0.0f) CollectVobsInContainer(world);
			
			drawSuccess=true;					
					
			// Blitten
			CSpacerDoc::doc->session->RenderBlit();	
			OnDrawUpdate(pDC);
			
		}
		camera[0]->Activate();
		EnableDrawing();		
	}
	return;
}

void CSpacerView::CollectVobsInContainer(zCWorld* world)
{	
	spcCVobContainer* vc = CMainFrame::mainframe->GetVobContainer();
	if (!vc) return;

	if  (vc->mode != spcCVobContainer::VC_CUSTOM )
	{
		vc->ClearVoblist();
		
		zTBBox3D bbox;
		zVALUE x,y,z;
		camera_vob[0]->GetPositionWorld(x,y,z);
		if (vc->mode == spcCVobContainer::VC_COLLECT_10M)
		{
			bbox.mins = zPOINT3(x-1000,y-1000,z-1000);
			bbox.maxs = zPOINT3(x+1000,y+1000,z+1000);
		}
		else if (vc->mode == spcCVobContainer::VC_COLLECT_20M)
		{
			bbox.mins = zPOINT3(x-2000,y-2000,z-2000);
			bbox.maxs = zPOINT3(x+2000,y+2000,z+2000);
		}
		else if (vc->mode == spcCVobContainer::VC_COLLECT_30M)
		{
			bbox.mins = zPOINT3(x-3000,y-3000,z-3000);
			bbox.maxs = zPOINT3(x+3000,y+3000,z+3000);
		}
		else if (vc->mode == spcCVobContainer::VC_COLLECT_100M)
		{
			bbox.mins = zPOINT3(x-10000,y-10000,z-10000);
			bbox.maxs = zPOINT3(x+10000,y+10000,z+10000);
		}
		else if (vc->mode == spcCVobContainer::VC_COLLECT_ALL_VOBS)
		{
			bbox.mins = zPOINT3(zREAL_MIN,zREAL_MIN,zREAL_MIN);
			bbox.maxs = zPOINT3(zREAL_MAX,zREAL_MAX,zREAL_MAX);
		}
		else
		{
			bbox.mins = zPOINT3(x-1,y-1,z-1);
			bbox.maxs = zPOINT3(x+1,y+1,z+1);
		};

		zCArray<zCVob*> resVobList;
		world->CollectVobsInBBox3D(resVobList,bbox);

		// lichter auch noch reinpacken
		for (int j=0; j<world->GetBspTree()->renderLightList.GetNum(); j++)
		{
			zCVobLight* nextLight = world->GetBspTree()->renderLightList[j];
			if (bbox.IsTrivIn(nextLight->GetPositionWorld())) resVobList.Insert(nextLight);
		}

		zCVob *nextVob;
		zPOINT3 upTestPoint;
			
		for(int i=0;i<resVobList.GetNumInList();i++)
		{	
			nextVob		= resVobList.GetSafe(i);

			if	(vc->m_bVobCollect_All)		
			{
				vc->AddVob( nextVob );
				continue;
			}
			if (vc->m_bVobCollect_zCVobs)
			{
				if (zIS_OF_CLASS<zCVob>(nextVob))
				{
					vc->AddVob( nextVob );
					continue;
				}
			}
			if (vc->m_bVobCollect_Sounds)
			{
				if (zDYNAMIC_CAST<zCSoundFX>(nextVob))
				{
					vc->AddVob( nextVob );
					continue;
				}
			}
			if (vc->m_bVobCollect_Mobs)
			{
				if (zDYNAMIC_CAST<oCMOB>(nextVob))
				{
					vc->AddVob( nextVob );
					continue;
				}
			}
			if (vc->m_bVobCollect_Npcs)
			{
				if (zDYNAMIC_CAST<oCNpc>(nextVob))
				{
					vc->AddVob( nextVob );
					continue;
				}
			}
			if (vc->m_bVobCollect_Lights)
			{
				if (zDYNAMIC_CAST<zCVobLight>(nextVob))
				{
					vc->AddVob( nextVob );
					continue;
				}
			}
			if (vc->m_bVobCollect_Items)
			{
				if (zDYNAMIC_CAST<oCItem>(nextVob))
				{
					vc->AddVob( nextVob );
					continue;
				}
			}
			if (vc->m_bVobCollect_Waypoints)
			{
				if (zDYNAMIC_CAST<zCWaypoint>(nextVob))
				{
					vc->AddVob( nextVob );
					continue;
				}
			}

			if (vc->m_bVobCollect_Illegal)
			{
				// das ding ist illegal, wenn es kein bodenpoly gibt, und der vob kein bodenpoly durchdringt
				upTestPoint = zVEC3(nextVob->GetPositionWorld()[VX], nextVob->GetBBox3DWorld().maxs[VY], nextVob->GetPositionWorld()[VZ]);
				if ( FALSE == world->TraceRayFirstHit(upTestPoint, upTestPoint+zVEC3(0,zREAL_MIN,0), nextVob, zTRACERAY_STAT_POLY) )
				{
					vc->AddVob( nextVob );
					continue;
				}
			}
		};
	};
}


void CSpacerView::OnDrawExtView(CDC* pDC, int nr)
{	
};

void CSpacerView::OnDrawInitialize(CDC* pDC)
{         
	zrenderer->Vid_Clear(zCOLOR(0,0,0,0)); 
}

void CSpacerView::OnDrawUpdate(CDC* pDC, int left, int top, int right, int bottom) 
{     		
    if (!viewport[0] || !pDC) return;    	    
	screen->DrawItems();		
}

void CSpacerView::OnDrawStartScreen(CDC* pDC)
{
	RECT rect;
	CClientDC ClientDC(this);				
	ClientDC.GetClipBox(&rect);
	ClientDC.FillSolidRect(&rect, RGB(0,0,0));				

	CSize size = ClientDC.GetTextExtent("something");
	int height = size.cy;
	int line = 4;

	// Name und Beschreibung der Anwendung
	ClientDC.SetTextColor( RGB(255,255,255) );
	ClientDC.TextOut(40,line*height,CString(SPC_APPLICATION_NAME));line++;		
	ClientDC.TextOut(40,line*height,CString(SPC_APPLICATION_DESCRIPTION));line++;				

	line+=2;

	// Entwickler und Company
	ClientDC.SetTextColor( RGB(196,250,250) );		
	ClientDC.TextOut(40,line*height,"Copyright © "+CString(SPC_YEAR_START)+"-"+CString(SPC_YEAR_END)+" by "+CString(SPC_COMPANY_NAME));line++;		
	ClientDC.TextOut(40,line*height,"developed by "+CString(SPC_AUTHOR_NAMES));line++;		

	line+=2;
	
	// Compilezeit
	ClientDC.SetTextColor( RGB(128,128,128) );
	ClientDC.TextOut(40,line*height,"compiled: "+CString(SPC_COMPILE_DATE)+" "+CString(SPC_COMPILE_TIME));line++;

	line+=2;
	CString renderVersion = "Direct3D";

	CString s;s.Format("%s %ix%i",renderVersion,spcConfig.view_x,spcConfig.view_y);
	// Compilezeit
	ClientDC.SetTextColor( RGB(0,175,0) );		
	ClientDC.TextOut(40,line*height,s);line++;
	

	line+=2;

	// Informationstext
	ClientDC.SetTextColor( RGB(196,196,196) );
	ClientDC.TextOut(40,line*height,CString("Load and merge 3DS-Files and compile"));line++;
	ClientDC.TextOut(40,line*height,CString("or load a ZEN-File."));line++;	

	EnableDrawing(false);
}

static bool pickedVobBBoxMode;

void CSpacerView::OnDrawBeforeRender(CDC *pDC)
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	// Wegpunkte: 2.Wegpunkt blinkt
	if (pickedWaypoint2nd)	
	{
		static bool		blinkDrawIt		= true;
		static zDWORD	lastBlinkToggle	= 0;
		zREAL	timeValue	= ztimer.GetTotalTimeF();		
		zDWORD	now			= int(timeValue/500);
		if ( now != lastBlinkToggle ) 
		{
			blinkDrawIt = !blinkDrawIt;
			lastBlinkToggle = now;
		}
		pickedWaypoint2nd->SetDrawBBox3D(blinkDrawIt);
	}
		
	// Modus: Boundingbox bearbeiten?
	if (CMainFrame::mainframe) 
	{
		CMainFrame::mainframe->GetObjectWindow()->UpdateEditingBoundingBox();
	}
	
#ifdef COMPILING_GOTHIC
	// Uhrzeit aktualisieren
	static int hour=12, minute=0;	
	if (ogame->GetWorldTimer())
	{
		ogame->GetWorldTimer()->GetTime(hour,minute);	
		if (CMainFrame::mainframe->GetInfoBar()->UpdateTime(hour, minute))
		{
			ogame->GetWorldTimer()->SetTime(hour, minute);
		}
	}
#endif

	// Kamerasteuerung
	if (modeView!=VIEW_TOP)
	{
		if (!modeTexManip && !modeVertManip) 
		{
			movementCtrl->Movement();
			
			zCCamTrj_KeyFrame* isKeyframe = dynamic_cast<zCCamTrj_KeyFrame*>(pickedVob);				
			if (isKeyframe && modeMove!=MV_NORMAL) 
			{
				if (CMainFrame::mainframe) CMainFrame::mainframe->HandleObjChange(pickedVob);
			}
		}
	}
	else
	{
		if (modeMove!=MV_VOB_MOVE) AutomapMovement();
		else movementCtrl->Movement();
	}
		
	// Wegpunkt bewegt? Aktualisierung ...
	if (dynamic_cast<zCVobWaypoint*>(pickedVob)) 
	{
		CSpacerDoc::doc->WayMovePoint((zCVobWaypoint*) pickedVob);	
	}

	// Selektiertes Vob. BBox anschalten
	pickedVobBBoxMode = pickedVob && pickedVob->GetDrawBBox3D();
	if (pickedVob && !pickedVob->GetEM()->GetCutsceneMode()) pickedVob->SetDrawBBox3D(TRUE);		
}

void CSpacerView::OnDrawAfterRender(CDC *pDC)
{
	// Selektiertes Vob: BBox weg
	zCVob* pickedVob = PICKED_VOB();		
	if (pickedVob) pickedVob->SetDrawBBox3D(pickedVobBBoxMode);
	if (pickedWaypoint2nd) pickedWaypoint2nd->SetDrawBBox3D(FALSE);

#ifdef COMPILING_GOTHIC
	oCNpc* npc = dynamic_cast<oCNpc*>(pickedVob);
	if (npc)
	{
		zCModel  *model  = npc->GetModel();
		
		if (oCNpc::player) npc			-> ShowState			(0,1600);
		npc->GetEM()-> ShowList				(0,2100);
		model		-> PrintStatus			(0,6000);
		model		-> ShowAniList			(6200);		
	}
#endif

	// Triggertargets und -sources (Verbindungslinien darstellen)	
	spcCInfoBar_Events* eventWin = CMainFrame::mainframe->GetInfoBarEvents();
	if (eventWin)
	{
		zCVob*			refVob	= 0;
		zCList<zCVob>*	vobList = 0;
		// Targets
		vobList = eventWin->GetTargetVobList(refVob);					
		if (vobList && refVob)
		{
			for (int i=0; i<vobList->GetNumInList(); i++) DrawLine(camera[0],refVob, vobList->Get(i), GFX_BLUE );
		}		
		// Sources
		vobList = eventWin->GetSourceVobList(refVob);
		if (vobList && refVob)
		{
			for (int i=0; i<vobList->GetNumInList(); i++) DrawLine(camera[0],refVob, vobList->Get(i), GFX_RED );
		}	
	}	
	
	// Selektiertes Vertex
	for (int vertZ=0; vertZ<selVertex.GetNumInList(); vertZ++) selVertex[vertZ]->Draw();
	
	if (modeFullscreen)
	{			
		// Screen-Mittelpunkt als Koordinatenkreuz
		zCOLOR color = zCOLOR(modePickMaterial?255:0,modePickMaterial?0:255,0,255);
		
		screen->Line(pxXm-pxX*5,pxYm,pxXm+pxX*5,pxYm,color);
		screen->Line(pxXm,pxYm-pxY*5,pxXm,pxYm+pxY*5,color);
	};		
		
	// Informationen darstellen
	if (viewInfoText && pickedVob)
	{
		// Picked Vob
		zSTRING info = pickedVob->GetClassDef()->GetClassName_()+":"+pickedVob->GetVobName();
		#ifndef NDEBUG
			info = info + "(refCtr:"+zSTRING(pickedVob->GetRefCtr())+")";
		#endif
		viewport[0]->Print(100,8192-int(viewport[0]->FontY()*1.5), info);			
	
		// Positionsangaben
		zREAL x,y;
		if (pickedVob) 
		{
			pickedVob->GetPositionWorld(point1);
			CString s;s.Format("P:%.2f,%.2f,%.2f",point1.n[VX],point1.n[VY],point1.n[VZ]);
			viewport[0]->Print(100,50 + viewport[0]->FontY()*2, s.GetBuffer(0));
			point2 = camera[0]->Transform(point1);
			if (point2[VZ]>0) 
			{				
				camera[0]->Project(&point2,x,y);
				zSTRING vobname = pickedVob->GetVobName();
				if (vobname=="") vobname = pickedVob->GetClassName_();
				viewport[0]->Print(screen->anx(int(x)),screen->any(int(y)), vobname);
			}
		}	
	}		
}

/////////////////////////////////////////////////////////////////////////////
// CSpacerView diagnostics

#ifdef _DEBUG
void CSpacerView::AssertValid() const
{
	CView::AssertValid();
}

void CSpacerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpacerDoc* CSpacerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpacerDoc)));
	return (CSpacerDoc*)m_pDocument;
}
#endif //_DEBUG


////////////////////////////////////////////////////////////
// MOUSE MOVE //////////////////////////////////////////////
////////////////////////////////////////////////////////////


void CSpacerView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!CMainFrame::mainframe || !infoBar) return;

	zCWorld* world = infoBar->GetActiveWorld();
	if (!world) return;
	
	if (modeFullscreen) 
	{		
		point.x = screen->nax(pxXm);
		point.y = screen->nay(pxYm);		
	};	
		
	if (nFlags & MK_LBUTTON==MK_LBUTTON) 
	{		
		if (!world) return;
		if (!world->IsCompiled() || world->IsCompiledEditorMode())
		{
			PolyMouseOver(nFlags,point);
		}
	}
		
	CView::OnMouseMove(nFlags, point);	

	if (modeFullscreen)
	{
		CMainFrame::mainframe->SetFocus();
	};
}


////////////////////////////////////////////////////////////
// MOUSE R-BUTTON //////////////////////////////////////////
////////////////////////////////////////////////////////////


// [EDENFELD] neu 1.33 aus ModSource, Untermenu Popup-.Punkt: Add As child 
void CSpacerView::ShowPopupMenue(CPoint point)
{
	if (!CMainFrame::mainframe || !infoBar) return;
	
	zCVob* pickedVob = PICKED_VOB();	

	// get rectangle of view
	RECT rc;
	GetWindowRect(&rc);

	// get popup-menu
	CMenu mainmenu;		
	VERIFY(mainmenu.LoadMenu(IDR_POPUPS));
	CMenu* menu = NULL;			
	CString s;
		
	if (
		CMainFrame::mainframe->workmode!=MODE_MATERIAL &&
		CMainFrame::mainframe->workmode!=MODE_VERTEX)
	{
		menu = mainmenu.GetSubMenu(0);
		ASSERT(menu != NULL);

		menu->InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR, 0, "VOB");
		menu->InsertMenu(0, MF_BYPOSITION | MF_STRING | MF_DISABLED, 0, "VOB");
		SetMenuDefaultItem(menu->m_hMenu, 0, TRUE);

		//
		// Insertvob-Text
		//
		CString vobTypeName		= CMainFrame::mainframe->GetVobTypeName();
			
		bool enabled = !vobTypeName.IsEmpty() ;
		
		if (enabled) 
		{		
			zSTRING s = "Insert ["+vobTypeName+"]";
			if (pickedVob) 
			{
				s+=" as child of ";
				if (!pickedVob->GetVobName().IsEmpty())				
					s+="\""+pickedVob->GetVobName()+"\"";
				else
					s+="["+pickedVob->GetClassDef()->GetClassName_()+"]";
			}
			menu->ModifyMenu	( ID_VOB_INSERT, MF_BYCOMMAND | MF_STRING, ID_VOB_INSERT, s.ToChar() );
			menu->EnableMenuItem( ID_VOB_INSERT, MF_BYCOMMAND | MF_ENABLED );
		}				
		else
		{			
			menu->ModifyMenu	( ID_VOB_INSERT, MF_BYCOMMAND | MF_STRING, ID_VOB_INSERT, "no insert");
			menu->EnableMenuItem( ID_VOB_INSERT, MF_BYCOMMAND | MF_GRAYED);
		}
			
		//
		// Class-Conversations
		//
		menu->EnableMenuItem(ID_VOB_CLASS_UP, MF_BYCOMMAND | MF_GRAYED);
		menu->EnableMenuItem(ID_VOB_CLASS_DN, MF_BYCOMMAND | MF_GRAYED);
				
		zCClassDef* classDef = pickedVob ? pickedVob->GetClassDef() : 0;
		if (classDef && !classDef->IsAbstractClass())
		{
			zSTRING classname;
			classname = classDef->GetBaseClassName();
			if (!classname.IsEmpty()) 
			{
				menu->ModifyMenu	(ID_VOB_CLASS_UP, MF_BYCOMMAND | MF_STRING, ID_VOB_CLASS_UP, classname.ToChar());
				menu->EnableMenuItem(ID_VOB_CLASS_UP, MF_BYCOMMAND | MF_ENABLED);
			}
			for (int i=0;i<zCClassDef::GetNum();i++)
			{
				zCClassDef* checkClassDef = zCClassDef::GetClassDefByIndex(i);
				if (checkClassDef->GetBaseClassDef() == classDef)
				{					
					menu->ModifyMenu	(ID_VOB_CLASS_DN, MF_BYCOMMAND | MF_STRING, ID_VOB_CLASS_UP, checkClassDef->GetClassName_().ToChar());
					menu->EnableMenuItem(ID_VOB_CLASS_DN, MF_BYCOMMAND | MF_ENABLED);
				};
			};
		}				

		//
		// Copy and Paste
		//
		if (vobCopyBuffer)
		{			
			menu->ModifyMenu	( ID_VIEWVOB_PASTE, MF_BYCOMMAND | MF_STRING, ID_VIEWVOB_PASTE,"Paste "+vobCopyName+"\t^V");		
		}
		if (dynamic_cast<zCVobSound*>(pickedVob) == NULL)
		{
			menu->EnableMenuItem( ID_VIEWVOB_PLAY, MF_BYCOMMAND | MF_GRAYED);
		};
		
		//
		// Show the menu
		//
		menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, rc.left+point.x, rc.top+point.y, AfxGetMainWnd());
	} 
	if (CMainFrame::mainframe->workmode==MODE_MATERIAL)
	{
		menu = mainmenu.GetSubMenu(1);
		ASSERT(menu != NULL);
		menu->InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR, 0, "POLYGON");
		menu->InsertMenu(0, MF_BYPOSITION | MF_STRING | MF_DISABLED, 0, "POLYGON");
		SetMenuDefaultItem(menu->m_hMenu, 0, TRUE);
		menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, rc.left+point.x, rc.top+point.y, AfxGetMainWnd());	
	}
	if (CMainFrame::mainframe->workmode==MODE_VERTEX)
	{
		VertClearSelection();
	}
}


void CSpacerView::OnRButtonDown(UINT nFlags, CPoint point) 
{	
	if (!CMainFrame::mainframe || !infoBar) return;
	
	zCWorld* world = infoBar->GetActiveWorld();
	if (!world) return;

	if (!camera[0]) return;

	if (modeFullscreen) 
	{		
		point.x = screen->nax(pxXm);
		point.y = screen->nay(pxYm);	
	};

	// get vob and polygone under mouse
	zCVob* xVob;
	zCPolygon* xPoly;
	zCVertex* xVert;
	zPOINT3 foundInters;	
	world->PickScene (*camera[0], point.x, point.y);	
	xVob  = world->traceRayReport.foundVob;
	xPoly = world->traceRayReport.foundPoly;
	xVert = world->traceRayReport.foundVertex;	
	// stop drawing	
	
	if (modeFullscreen) 
	{
		if (CMainFrame::mainframe->workmode==MODE_MATERIAL)
		{
			OnPolyApplyTexWithMapping();
		};
		return;
	}

	if (CMainFrame::mainframe->workmode!=MODE_MATERIAL &&
		CMainFrame::mainframe->workmode!=MODE_VERTEX)
	{		
		
		VobSelect(xVob,false);
		
		CDC* pDC = GetDC();
		OnDraw(pDC);		
	} 	

	EnableDrawing(FALSE);

	ShowPopupMenue(point);
	
	EnableDrawing();

	CView::OnRButtonDown(nFlags, point);
}



////////////////////////////////////////////////////////////
// MOUSE L-BUTTON //////////////////////////////////////////
////////////////////////////////////////////////////////////


void CSpacerView::OnLButtonDown(UINT nFlags, CPoint point) 
{		
	if ( ::g_bIsPlayingGame ) return;
	if (!camera[0]) return;
	if (!CMainFrame::mainframe || !infoBar) return;
	
	zCWorld* world = infoBar->GetActiveWorld();
	if (!world) return;

	if (modeFullscreen) 
	{		
		point.x = screen->nax(pxXm);
		point.y = screen->nay(pxYm);	
	};
	
	if (modeTexManip) return;

	// Search for VOBs and POLYs
	zCVob* xVob;
	zCPolygon* xPoly;
	zCVertex* xVert;
	zPOINT3 foundInters;
	world->PickScene (*camera[0], point.x, point.y);	
	xVob  = world->traceRayReport.foundVob;	
	xPoly = world->traceRayReport.foundPoly;
	xVert = world->traceRayReport.foundVertex;
	if (world->IsCompiled() && !world->IsCompiledEditorMode())
	{
		xPoly = 0; // dann nicht selektieren
	}

	// select something
	if (spcConfig.view_x>=point.x && spcConfig.view_y>=point.y)
	{
		if (CMainFrame::mainframe->workmode==MODE_MATERIAL)	PolyMouseClick(xPoly);	
		else if (CMainFrame::mainframe->workmode==MODE_VERTEX) VertMouseClick(xVert);
		else 
		{
			VobSelect(xVob);
		}
	}
	// sent to cutsceneseq
	if (xVob)
	{
		zSTRING name = xVob->GetVobName();
		CMainFrame::mainframe->CSAssignParameter(name);
	}

	modePickMaterial=false;	
	CView::OnLButtonDown(nFlags, point);
}

void CSpacerView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (modeFullscreen) return;	

	OnLButtonDown(nFlags, point);	
	
	zCVob* pickedVob = PICKED_VOB();	
	if (!pickedVob) return;

	// this might be more differential (takeover for camera)?
	if (pickedVob->GetVobType()!=zVOB_TYPE_LEVEL_COMPONENT)
	{
		OnVobMove();
	}
	CView::OnLButtonDblClk(nFlags, point);
}


////////////////////////////////////////////////////////////
// KEYBOARD ////////////////////////////////////////////////
////////////////////////////////////////////////////////////


///
// Textur-Manipulation
///
void CSpacerView::OnKey_TextureManipulate(UINT nChar) 
{		
	if (!CMainFrame::mainframe || !infoBar) return;

	zCWorld* world = infoBar->GetActiveWorld();
	if (!world) return;

	if (modeTexManip)
	// Nur wenn gerade eine Textur manipuliert wird ...
	{
		switch(nChar)		
		{		
			// scaling
			case DOSKEY_PAD_END: TextureScale(-10,-10);break;
			case DOSKEY_PAD_PGUP: TextureScale(+10,+10);break;
			case DOSKEY_PAD_DOWN: TextureScale(0,-10);break;
			case DOSKEY_PAD_LEFT: TextureScale(-10,0);break;
			case DOSKEY_PAD_RIGHT: TextureScale(+10,0);break;
			case DOSKEY_PAD_UP: TextureScale(0,+10);break;

			// moving
			case DOSKEY_UP:   TextureMove(0,+1);break;
			case DOSKEY_DOWN: TextureMove(0,-1);break;
			case DOSKEY_LEFT: TextureMove(-1,0);break;			
			case DOSKEY_RIGHT:TextureMove(+1,0);break;

			case DOSKEY_DEL:  TextureRotate(-1);break;
			case DOSKEY_PGDN: TextureRotate(+1);break;
			case DOSKEY_INS:  TextureRotate(-spcConfig.rotGridTex);break;
			case DOSKEY_PGUP: TextureRotate(spcConfig.rotGridTex);break;

			// shearing
			case DOSKEY_PAD_DIV:  TextureShear(-1,0);break;
			case DOSKEY_PAD_MUL:  TextureShear(+1,0);break;
			case DOSKEY_GREYMINUS:TextureShear(0,+1);break;
			case DOSKEY_GREYPLUS: TextureShear(0,-1);break;

			// mirrors
			case DOSKEY_PAD_INS:	TextureMirror(1,0);break;
			case DOSKEY_PAD_ENTER:	TextureMirror(0,1);break;
			case DOSKEY_PAD_DEL:	TextureRotateByAngle(180);break;
			/*default: zerr.Message(zSTRING((long)nChar));*/
		};
	}
	else
	// Nur wenn gerade KEINE Textur manipuliert wird ...
	{
		switch(nChar)
		{
			case DOSKEY_SPACE:	modeTexManip=true;
							PolyHideSelection(TRUE);
							TextureCalcCenter(poly_center);
							break;							
		}
	};

	// Immer:
	switch(nChar)
	{			
		case DOSKEY_G:		spcConfig.useGridTex = !spcConfig.useGridTex;							
						break;
	}
};



///
// Vertex-Manipulation
///
void CSpacerView::OnKey_VertexManipulate(UINT nChar) 
{	
	if (!CMainFrame::mainframe || !infoBar) return;

	float speed = (float)CMainFrame::mainframe->GetVertexMoveSpeed();

	if (modeVertManip)
	// Nur wenn gerade ein Vertex manipuliert wird
	{	
		switch(nChar)
		{
			case DOSKEY_UP:	VertMove(0.0,0.0,speed); break;
			case DOSKEY_RIGHT: VertMove(speed,0.0,0.0); break;
			case DOSKEY_DOWN:	VertMove(0.0,0.0,-speed); break;
			case DOSKEY_LEFT:	VertMove(-speed,0.0,0.0);break;
			case DOSKEY_A:		VertMove(0.0,speed,0.0); break;
// [BENDLIN] Addon - KeybFix
#ifdef LANG_ENU
			case DOSKEY_Z:		VertMove(0.0,-speed,0.0);break;
#else
			case DOSKEY_Y:		VertMove(0.0,-speed,0.0);break;
#endif
			case DOSKEY_X:		VertClearSelection();
		}
	}
	else
	// Nur wenn gerade KEIN Vertex manipuliert wird
	{
		switch(nChar)
		{
			case DOSKEY_SPACE:	modeVertManip = true;
							break;					
		}
	};

	// Immer:
};


///
// Vob-Manipulation
///
void CSpacerView::OnKey_VobManipulate(UINT nChar)
{	
	switch (nChar)
	{				
		case DOSKEY_DEL:			OnVobRemove();break;
		case DOSKEY_Q:				if (modeMove!=MV_NORMAL)
								{
									zCVob* pickedVob  = PICKED_VOB();	
									if (colldet_disabled)
									{
										colldet_disabled = false;
										pickedVob->SetCollDetStat(colldet_stat_backup);
										pickedVob->SetCollDetDyn(colldet_dyn_backup);			
									}
									else
									{
										colldet_disabled = true;
										pickedVob->SetCollDetStat(FALSE);
										pickedVob->SetCollDetDyn(FALSE);			
									}
								}
								break;		
		case DOSKEY_ESC:			if (::g_bIsPlayingGame) break;
								if (modeMove == MV_VOB_MOVE)		OnVobMove();
								else if (modeMove == MV_VOB_CONTROL)	OnVobControl();
								else if (modeMove == MV_VOB_OVERTAKEN)	OnVobTakeover();								
								break;		
		case DOSKEY_G:				if (::g_bIsPlayingGame) break;
								spcConfig.useGrid = !spcConfig.useGrid;
								InitSettings();
								break;
		case DOSKEY_F6			:	if (::g_bIsPlayingGame) break;
								if (camera_vob[0]) 
								{
									camera_vob[0]->ResetRotationsWorld();
								}
								break;								
	};

	if (::g_bIsPlayingGame) return;
	// ACHTUNG: Den PickedVob NICHT vor dem Aufruf von OnVobRemove abfragen: Er koennte danach nicht mehr gueltig sein!
	zCVob* pickedVob  = PICKED_VOB();	
	if (dynamic_cast<zCDecal*>(pickedVob) && modeMove!=MV_NORMAL)
	{
		zVALUE x,y;
		((zCDecal*)pickedVob->GetVisual())->GetDecalDim(x,y);		
		switch (nChar)
		{
			case DOSKEY_PAD_UP     : ((zCDecal*)pickedVob->GetVisual())->SetDecalDim(x,y+5);break;
			case DOSKEY_PAD_DOWN   : ((zCDecal*)pickedVob->GetVisual())->SetDecalDim(x,(y>5?y-5:y));break;
			case DOSKEY_PAD_RIGHT  : ((zCDecal*)pickedVob->GetVisual())->SetDecalDim(x+5,y);break;
			case DOSKEY_PAD_LEFT   : ((zCDecal*)pickedVob->GetVisual())->SetDecalDim((x>5?x-5:x),y);break;
			case DOSKEY_PAD_PGUP   : ((zCDecal*)pickedVob->GetVisual())->SetDecalDim(x+5,y+5);break;
			case DOSKEY_PAD_END    : ((zCDecal*)pickedVob->GetVisual())->SetDecalDim((x>5?x-5:x),(y>5?y-5:y));break;
		}
		pickedVob->UpdateVisualDependencies();
	}

};

// [EDENFELD] neu 1.33 aus ModSource. Neue Tasten für Geschwindigkeit der Camera, etc...
void CSpacerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	if (!CMainFrame::mainframe || !infoBar) return;

	zCWorld* world = infoBar->GetActiveWorld();
	
	if (! ::g_bIsPlayingGame)
	switch (nChar)
	{
		case DOSKEY_0		  :		
								OnPolyPickmaterial();	
								if (world) for (int k=0;k<MAX_KEYS;k++) zCView::MFC_KeyUp(k);
								break;		
		
		case DOSKEY_TAB	  :		if (CMainFrame::mainframe) 								
									CMainFrame::mainframe->OnVieweditToggletools();
								break;							

		case DOSKEY_F3		  : 		
		case DOSKEY_BACKSPACE:		OnViewFullscreen();		
								if (world) for (int k=0;k<MAX_KEYS;k++) zCView::MFC_KeyUp(k);			
								break;

		// Player-Light-Intensitaet
		case DOSKEY_GREYMINUS	:	if (!modeVertManip && !modeTexManip && (playerLightInt>=500)) 
								{																			
									playerLightInt = playerLightInt - 500;
									spcConfig.camlight = playerLightInt;
									InitSettings();
									zERR_MESSAGE(3,0,"B: SPC: Lightintentity decreased to :"+zSTRING(playerLightInt));
								}
								break;
		case DOSKEY_GREYPLUS	:	if (!modeVertManip && !modeTexManip && (playerLightInt<=20000)) 
								{
									playerLightInt = playerLightInt + 500;
									spcConfig.camlight = playerLightInt;
									InitSettings();
									zERR_MESSAGE(3,0,"B: SPC: Lightintentity increased to :"+zSTRING(playerLightInt));
								}
								break;		
							
		// Movement-Speed
		case DOSKEY_PAD_DOWN:		if (!modeVertManip && !modeTexManip) 
									if (spcConfig.movespeed>1)
									{
										spcConfig.movespeed--;
										InitSettings();
										zERR_MESSAGE(4,0,"B: SPC: Movement speed decreased to "+zSTRING(spcConfig.movespeed));
									}
								break;
		
		case DOSKEY_PAD_UP:		if (!modeVertManip && !modeTexManip) 
									if (spcConfig.movespeed<100) 
									{
										spcConfig.movespeed++;
										InitSettings();
										zERR_MESSAGE(4,0,"B: SPC: Movement speed increased to "+zSTRING(spcConfig.movespeed));
									}
								break;
		
		// Farclipping-Factor
		case DOSKEY_PAD_DIV:		if (!modeVertManip && !modeTexManip && (spcConfig.farclipping>0.1f))
								{
									// naechste Zweierpotenz finden				
									spcConfig.farclipping = spcConfig.farclipping - 0.1f;
									InitSettings();
									zERR_MESSAGE(4,0,"B: SPC: FarClipping decreased to factor "+zSTRING(spcConfig.farclipping,2));									
								}
								break;			

		case DOSKEY_PAD_MUL:		if (!modeVertManip && !modeTexManip && (spcConfig.farclipping<2.0f)) 
								{
									// naechste Zweierpotenz finden
									spcConfig.farclipping = spcConfig.farclipping + 0.1f;
									InitSettings();				
									zERR_MESSAGE(4,0,"B: SPC: FarClipping increased to factor "+zSTRING(spcConfig.farclipping,2));									
								}
								break;

		// Keyboard-Buffer
		case DOSKEY_F8	      :		if (world) for (int k=0;k<MAX_KEYS;k++) zCView::MFC_KeyUp(k);
								break;
		
	};
	
	if (CSpacerDoc::doc->GetWorld()) 
	{
		zCView::MFC_KeyDown(nChar);	
		/*if (::g_bIsPlayingGame) 
		{	// testkeys
			if (!zcon.IsVisible())
			if (gameMan->GetGame()->TestKeys(nChar)) for (int k=0;k<MAX_KEYS;k++) zCView::MFC_KeyUp(k);
		}*/
	}

	if (CMainFrame::mainframe->workmode==MODE_MATERIAL)		
	{
		if (!::g_bIsPlayingGame) OnKey_TextureManipulate(nChar);
	}
	else if (CMainFrame::mainframe->workmode==MODE_VERTEX)
	{
		if (!::g_bIsPlayingGame) OnKey_VertexManipulate(nChar);
	}
	else
	{
		OnKey_VobManipulate(nChar);
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	if (!::g_bIsPlayingGame)
	if (CMainFrame::mainframe) CMainFrame::mainframe->HandleKeyDown(nChar, nRepCnt, nFlags);
}

void CSpacerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// ACHTUNG: Alle hier hereinkommenden Keycodes sind DOS32 Keycodes.
	// d.h. alle Key-Konstanten die hier und in den aufzurufenden Unterfunktionen benutzt
	// werden müssen das PREFIX "DOS" haben. z.B. statt KEY_ESC muss hier also DOSKEY_ESC benutzt werden
	// Das zCInput Interface verarbeitet intern allerdings nach wie vor mit Win32/Direct Input Keycodes.
	// Nur hier werden also DOS32 Keycodes ins Inputinterface via MFC_Keydown() reingegeben und dort in Win32 Codes
	// umgewandelt

	if (!CMainFrame::mainframe || !infoBar) return;

	zCWorld* world = infoBar->GetActiveWorld();
	if (world) zCView::MFC_KeyUp (nChar);

	if (!::g_bIsPlayingGame)
	switch(nChar)		
	{
	case DOSKEY_SPACE    : 
		if (world)
		{
			modeTexManip	=	false;
			modeVertManip	=	false;
			PolyHideSelection	(FALSE);						

			zCBspTree* bsp	=	world->GetBspTree();

			for (int vz=0; vz<selVertex.GetNumInList(); vz++)
			{
				bsp->UpdateVertexDependencies(selVertex[vz]);
			}
		} break;
	}		

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CSpacerView::EnableDrawing(BOOL draw)
{ 
	((CSpacerApp*)AfxGetApp())->EnableDrawing(draw==TRUE);	
}

/////////////////////////////////////////////////////
// INITIALIZATION
/////////////////////////////////////////////////////


void CSpacerView::InitViewport(BOOL newworld)
{						
	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);			

	if (!CMainFrame::mainframe) return;
	infoBar = CMainFrame::mainframe->GetInfoBar();
	if (!infoBar) return;

	zERR_MESSAGE(3,zERR_BEGIN,"B: SPC: InitViewport");	

	EnableDrawing(FALSE);


	zERR_MESSAGE(6,0,"B: SPC: SpacerView::Init. Ignore Anis");
	zCModelPrototype::SetIgnoreAnis(FALSE);			
	
	if (!SelectMaterial)
	{
		zERR_MESSAGE(6,0,"B: SPC: SpacerView::Init. Select-Material");
		// Create material for selections
		zerr.Message("B: ... modeSelectPolygons");
		zSTRING filename("select.tga");
		SelectMaterial = new zCMaterial("<Select>");
		SelectMaterial ->SetTexture(filename);
		SelectMaterial ->color.r = 255;
		SelectMaterial ->color.g = 0;
		SelectMaterial ->color.b = 0;		
		SelectMaterial ->AddRef();	
		SelectMaterial ->SetUsage(zCMaterial::zMAT_USAGE_OTHER);
		zERR_MESSAGE(6,0,"B: SPC: SpacerView::Init. Finished");
	}


	zERR_MESSAGE(3,0,"B: SPC: Init video");	
	
	///
	// Initializing Video
	///
					
	CMainFrame::mainframe->ResizeToView(this,spcConfig.view_x,spcConfig.view_y);

	InitVideo();	
					
	zCView::SetMode(spcConfig.view_x,spcConfig.view_y,spcConfig.view_bpp);		
	ShowCursor(TRUE);
				
	zERR_MESSAGE(3,0,"B: SPC: Init DIB-Section, textview and viewport");		
	
	// dibsection
	dib[0] = new spcCDibSection();
	dib[0]->Create(spcConfig.view_x,spcConfig.view_y,spcConfig.view_bpp);		
	
	// viewport
	viewport[0] = pDoc->session->GetViewport();
	if (viewport[0]->GetOwner()) 
	{
		viewport[0]->GetOwner()->RemoveItem(viewport[0]);
	}
	zCView::MFC_CreateScreen(dib[0]->GetDataPtr(),spcConfig.view_x,spcConfig.view_y,spcConfig.view_bpp);									
	viewport[0] = pDoc->session->GetViewport();		
	if (viewport[0]) 
	{			
		screen->InsertItem(viewport[0]);
		viewport[0]->SetSize(8192,8191);
	}
	

	///
	// Neue Welt ...
	///
	zCWorld* world = infoBar->GetActiveWorld();	
	if (world && (newworld==TRUE))
	{				

		#ifdef COMPILING_GOTHIC
		ogame->GetWorldTimer()->SetTime(12,00);
		#endif

		zERR_MESSAGE(3,0,"B: SPC: Init camera");		
				
		// camera		
		
		zERR_MESSAGE(3,0,"B: SPC: Creating new Camera");		
		pDoc->session->CamInit();		
		camera		[0]	= pDoc->session->GetCamera();
		camera_vob	[0]	= pDoc->camera_vob = camera[0]->GetVob();
		camera_vob	[0]	->SetVobName(VOBNAME_SPACER_CAMERA);
		camera_vob	[0]	->SetAICallback(0);		
					
		// movement

		zERR_MESSAGE(3,0,"B: SPC: Init movement");						
		movementCtrl	= new spcCMovement(0);				
		view_waynet		= FALSE;
		dynamic_cast<oCGame*>(pDoc->session)->SetDrawWaynet(view_waynet);
		
	}	 
	
	zERR_MESSAGE(3,0,"B: SPC: Final init for camera, movement and sound");	

	if (camera[0]) camera[0]->SetRenderTarget(viewport[0]);
		
	if (movementCtrl) 
	{
		movementCtrl->SetVob	(camera_vob[0],MOV_WALKING);
		movementCtrl->SetCamVob	(camera_vob[0]);
	}	

	if (infoBar) infoBar->SetPositionVob(camera_vob[0]);
	
	pxXm = (int)(screen->anx(spcConfig.view_x) / 2);
	pxYm = (int)(screen->any(spcConfig.view_y) / 2);
	pxX  = screen->anx(1);
	pxY	 = screen->any(1);	

	zERR_MESSAGE(3,zERR_END,"B: CSpacerView::InitViewport ready");	
	
	if (world) world->SetDrawVobBBox3D (FALSE);
	QueryPerformanceCounter(&counter);	

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	InitSettings();

	for (int k=0;k<MAX_KEYS;k++) zCView::MFC_KeyUp(k);
	EnableDrawing();
}

void CSpacerView::InitSettings()
{	
	// Movement
	if (movementCtrl) 
	{
		movementCtrl->SetSpeed(spcConfig.movespeed);			
		if ( (modeMove!=MV_NORMAL) )
		{
			movementCtrl->Grid		(bool(spcConfig.useGrid>0));
			movementCtrl->GridRot	(bool(spcConfig.useGrid>0));
			movementCtrl->SetGrid	(float(spcConfig.moveGrid));
			movementCtrl->SetGridRot(float(spcConfig.rotGrid));
		}
	}
	
	// Renderer
	if (zrenderer)
	{
		if (wire)	zrenderer->SetPolyDrawMode(zRND_DRAW_WIRE);
		else		zrenderer->SetPolyDrawMode(zRND_DRAW_MATERIAL); 
		
		if (spcConfig.modeFogging)
		{
			zrenderer->SetFog(TRUE);
			//zrenderer->SetFogRange	(float(spcConfig.farclip*0.50),float(spcConfig.farclip));
		}
		else
		{
			zrenderer->SetFog(FALSE);
			//zrenderer->SetFogRange	(float(spcConfig.farclip), float(spcConfig.farclip));
		}
	};
	
	// Sky-Controler
	if (CSpacerDoc::doc->GetWorld())
	{
		zCSkyControler* sky = CSpacerDoc::doc->GetWorld()->GetActiveSkyControler();
		if (sky) sky->SetFarZScalability(spcConfig.farclipping);
	};	

	playerLightInt	= spcConfig.camlight;	
}

void CSpacerView::InitVideo()
{
	if (viewport[0]) screen->RemoveItem(viewport[0]);
	if (dib[0])		 { delete dib[0];dib[0]=NULL; }
	drawMode = zCAM_DRAW_FLAT;
	drawWire = FALSE;
	drawShadeMode = zSHADE_GOURAUD;
	drawSmoothMesh = FALSE;
}



void CSpacerView::ResizeViewport()
{	
	InitViewport();
}


//////////////////////////////////////////////////////////
// VOB-METHODS
//////////////////////////////////////////////////////////

void CSpacerView::VobSelect(zCVob * vob, bool show)
{				
	if (!CMainFrame::mainframe || !infoBar) return;	

	if (modeMove!=MV_NORMAL) SetMoveMode(MV_NORMAL);	
	
	if (zinput->KeyPressed(KEY_LSHIFT))
	{			
		// zweiten Vob (de)selektieren
		pickedWaypoint2nd = dynamic_cast<zCVobWaypoint*>(vob);
		if (pickedWaypoint2nd) zERR_MESSAGE(9,0,"B: SPC: Picked 2nd waypoint");			
	}
	else
	{				
		// Hauptvob (pickedVob) (de)selektieren
		infoBar->SetSelectedObject(vob);
		pickedWaypoint = dynamic_cast<zCVobWaypoint*>(vob);

		if  (show) CMainFrame::mainframe->HandleVobSelect(vob);		
	}		
}

//////////////////////////////////////////////////////////
// POLY-METHODS
//////////////////////////////////////////////////////////


bool CSpacerView::PolySelect(bool select, zCSelPoly* selPoly)
{
	if (!selPolyList) return FALSE;
	if (!selPoly || !selPoly->GetPolygon()) return FALSE;
		
	if (select)
	{	
		if (!selPoly->GetMaterial()) return TRUE;		
		selPoly->GetPolygon()	->SetMaterial(SelectMaterial);		
		selPolyList				->Insert(selPoly);
		SelectMaterial			->SetLibFlag(MATLIB_INVISIBLE);
		SelectMaterial			->SetUsage(zCMaterial::zMAT_USAGE_OTHER);		
		return TRUE;
	}
	else
	{		
		if (!selPoly->GetMaterial()) return TRUE;
		selPoly->GetPolygon()	->SetMaterial(selPoly->GetMaterial());		
		selPolyList				->Remove(selPoly);
		SelectMaterial			->SetLibFlag(MATLIB_INVISIBLE);
		SelectMaterial			->SetUsage(zCMaterial::zMAT_USAGE_OTHER);		
		return TRUE;
	}
}


void CSpacerView::PolyMouseClick(zCPolygon* xPoly)
{
	if (!CMainFrame::mainframe || !infoBar) return;

	if (!xPoly) return;		
	if (modePickMaterial)
	{
		CMainFrame::mainframe->ObjectSelection(xPoly->GetMaterial(),this);
		modePickMaterial=false;		
		return;		
	}

	// BOOL ShiftKey = (GetKeyState(VK_SHIFT)<0);	
	
	pickedPoly = xPoly;
	zCSelPoly* selPoly = PolyIsSelected(xPoly);

	if (selPoly)				// polygon is selected ---> deselect
	{
		if (PolySelect(FALSE, selPoly)) 
		{ 
			delete selPoly;
			selPoly=NULL;
		}
		modeSelectPolygons = FALSE;
	}
	else						// polygon is not selected ---> delect
	{
		selPoly = new zCSelPoly(xPoly);
		PolySelect(TRUE, selPoly);
		modeSelectPolygons = TRUE;
	}		
}

void CSpacerView::VertMouseClick(zCVertex* v)
{
	modeSelectPolygons = !VertIsSelected(v);
	VertSelect(modeSelectPolygons,v);	
}
void CSpacerView::VertClearSelection()
{
	selVertex.EmptyList();
}
bool CSpacerView::VertSelect(bool select, zCVertex* v)
{
	if (!v) return false;

	if (select)
	{
		if (selVertex.Search(v)<0) selVertex.Insert(v);
		pickedVertex = v;
	} 
	else 
	{
		selVertex.RemoveOrder(v);
		pickedVertex = NULL;
	}
	return true;
}


void CSpacerView::OnUpdateVobRemove(CCmdUI* pCmdUI) 
{	
	zCVob* pickedVob = PICKED_VOB();	

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	bool enable = true;
	enable = enable && world && world->IsCompiled();
	enable = enable && (modeMove == MV_NORMAL);
	enable = enable && pickedVob;
	enable = enable && (pickedVob!=camera_vob[0]);
	pCmdUI->Enable( enable );	
}

/*
void CSpacerView::VobDoAI(zCCSBlockBase* cs)
{	
	zCVob* pickedVob = PICKED_VOB();	

	#ifdef COMPILING_GOTHIC
		if (!pickedVob || !csplayer || !cs) return;
		if (pickedVob->GetVobType()!=zVOB_TYPE_NSC) return;

		if (!oCNpc::player) 
		{ 
			oCNpc::player = new oCNpc();
			oCNpc::player->InitByScript(parser.GetIndex(zSTRING("PC_HERO")));
			if (!oCNpcFocus :: focus) oCNpcFocus :: InitFocusModes();
		}
		if (!oCNpc::player->GetAnictrl()) return;

		int ounr = csplayer->LibValidateOU(cs->GetRoleName());
		((oCNpc*)pickedVob)	->state	.StartOutputUnit(ounr);
	#endif	
}
*/


/*
void CSpacerView::VobDoCS(zCCSBlockBase* cs)
{	
	zCVob* pickedVob = PICKED_VOB();	

	#ifdef COMPILING_GOTHIC
		if (!dynamic_cast<zCCSCutscene*>(cs)) return;				
		
		oCNpc* npc = dynamic_cast<oCNpc*>(pickedVob);
		if (!npc) return;

		if (!oCNpc::player) 
		{			
			oCNpc::player = new oCNpc();
			oCNpc::player->InitByScript(parser.GetIndex(zSTRING("PC_HERO")));	
			if (!oCNpcFocus :: focus) oCNpcFocus :: InitFocusModes();
		}
		if (!oCNpc::player->GetAnictrl()) return;
		
		if (npc->state.cs_context) 
		{
			npc->state.cs_context-> Free();
			npc->state.cs_context = NULL;
		}

		npc->state.cs_context = csplayer -> PlayCutscene(dynamic_cast<zCCSCutscene*>(cs),pickedVob);
	#endif
}
*/

// [EDENFELD] neu 1.33 aus Modsource. 
void CSpacerView::Do_CompileWorld(const spcCCompileWorldAction &mode)
{	
	if (!infoBar && CMainFrame::mainframe) infoBar = CMainFrame::mainframe->GetInfoBar();
	if (!CMainFrame::mainframe || !infoBar) return;
	
	zCWorld* world = infoBar->GetActiveWorld();
	if (!world) return;

	PolyClearSelection();
	VobSelect(0,true);	
	
	//CSpacerDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);	
		
	::SetCursor(spcConfig.MouseWait);

	zREAL value;
	
	if (mode.quick)			value=0.2F; else value=1.0F;
	if (mode.editormode)	value=0.1F; // Editormode don't need optimization
	
	if (leakPolyList)		{ delete leakPolyList;leakPolyList = NULL; }
	
	if (mode.detectLeaks)	leakPolyList = new zCArray<zCPolygon*>;
	
	int bsp_mode = mode.inout;
	
	// compile
	world->DisposeStaticWorld();

	bool workingDlgOpened = false;
	if (!workingDlg)
	{
		workingDlgOpened = true;
		workingDlg = new spcCWorkInfoDlg();
		workingDlg->Init();		
	}	
	bool winDisabled = true;
	if (CMainFrame::mainframe) 
	{
		winDisabled = CMainFrame::mainframe->DeactivateApplicationWindows();		
	}
		
	if (bsp_mode==0)
	{		
		if (workingDlg) workingDlg->AddMessage(" Compile indoor");
		if (mode.detectLeaks)	workingDlg->AddMessage(" - detecting leaks");		
	}
	else if (bsp_mode==1)
	{
		workingDlg->AddMessage(" Compile outdoor");		
	}
	if (mode.editormode)	workingDlg->AddMessage(" - editormode ");
	if (mode.quick)			workingDlg->AddMessage(" - quick compile");			

	// Invisible-Vobs sind im editor-mode nicht erwuenscht		
	if (mode.editormode && CSpacerDoc::doc->modeViewHelperVobs) CSpacerDoc::doc->OnViewInvisibleVobs();


	workingDlg->AddMessage(" compiling ...");	
	if (bsp_mode==0)
	{		
		world->CompileWorld(zBSP_MODE_INDOOR, value,FALSE, mode.editormode,leakPolyList);
	}
	else if (bsp_mode==1)
	{		
		world->CompileWorld(zBSP_MODE_OUTDOOR, value,FALSE, mode.editormode,0);
	}
	
	if (mode.polycheck) 
	{
		workingDlg->AddMessage(" checking for deg. polys ...");

		zCTree<zCVob>* tree = world->globalVobTree.GetFirstChild();

		while (tree && tree->GetData()->GetVobType()!=zVOB_TYPE_LEVEL_COMPONENT) 
							tree = tree->GetNextChild();			
	}
	

	// restore mainwindow and remove working-dialog

	if (CMainFrame::mainframe && winDisabled) 
	{
		CMainFrame::mainframe->ReactivateApplicationWindows();		
	}

	if (workingDlgOpened && workingDlg)
	{				
		workingDlg->CloseWindow();
		workingDlg->DestroyWindow();
		workingDlg = 0;
		SetFocus();
	}
		
	::SetCursor(spcConfig.MouseArrow);

	CMainFrame::mainframe->UpdateWindowContents(world);

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	VobSelect(0,true);

	InitSettings();

	EnableDrawing();
}

void CSpacerView::OnWorldCompile() 
{
	if (modeFullscreen) return;	

	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	if (!pDoc->IsAWorldLoaded()) return;		

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (!world) return;
	if (world->IsCompiledEditorMode()) return;

	spcCCompileWorldDlg dlg;
	if (lastCompileWorldAction.valid && lastCompileWorldAction.force)
	{
		dlg.m_quick_compile	= lastCompileWorldAction.quick;
		dlg.m_editormode	= lastCompileWorldAction.editormode;
		dlg.m_detect_leaks	= lastCompileWorldAction.detectLeaks;
		dlg.m_polycheck		= lastCompileWorldAction.polycheck;
		dlg.m_inout_door	= lastCompileWorldAction.inout;
		lastCompileWorldAction.force	= false;
	}
	else
	{
		dlg.m_editormode = (world && !world->IsCompiled());	
		if (dlg.DoModal()==IDCANCEL) return;
	}	
		
	::SetCursor(spcConfig.MouseWait);

	spcCCompileWorldAction compile_mode;
	compile_mode.quick			= dlg.m_quick_compile;
	compile_mode.editormode		= dlg.m_editormode;
	compile_mode.detectLeaks	= dlg.m_detect_leaks;
	compile_mode.polycheck		= dlg.m_polycheck;
	compile_mode.inout			= dlg.m_inout_door;
	
	EnableDrawing(FALSE);
	
	Do_CompileWorld(compile_mode);		
	
	bool result = pDoc->VobDetectCollision();
	if (!result) AfxMessageBox("There are colliding vobs.\r\nHave a look at the list of vobs in the vobtree.");

	// are there poly-leaks?
	if (leakPolyList)
	{
		if (leakPolyList->GetNumInList()>0) { AfxMessageBox("There are leaks in your world.");leakPolyCurrent=0;}
		else { delete leakPolyList;leakPolyList=NULL;leakPolyCurrent=0;	}
		zerr.Message("B: Ready. World compiled successfully");
	}
	
	// save compile-options
	lastCompileWorldAction = compile_mode;
	lastCompileWorldAction.valid=true;

	VobSelect(0,true);

	InitSettings();

	::SetCursor(spcConfig.MouseArrow);
	
	EnableDrawing();
}

void CSpacerView::OnUpdateWorldCompile(CCmdUI* pCmdUI) 
{
	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	zBOOL editorCompiled = FALSE;
	if (world) editorCompiled = world->IsCompiledEditorMode();

	pCmdUI->Enable(	pDoc->IsAWorldLoaded() && !editorCompiled);
}

// [EDENFELD] neu 1.33 aus ModSource
void CSpacerView::VobGoto(zCVob * vob)
{
	if (!vob) return;

	RememberCamPos();
	camLastAutoRemembered=true;		

	if (vob->GetVobType()!=zVOB_TYPE_CAMERA)
	{
		SetCamInFrontOfVob(vob, 400);
	}
	else
	{		
		zPOINT3 dir = vob -> GetAtVectorWorld();
		zPOINT3 pos;  vob -> GetPositionWorld(pos);		
					
		camera_vob[0] -> SetPositionWorld(pos);
		camera_vob[0] -> SetHeadingWorld(pos+dir*400);
	}		
}

///////////////////////////////////////////////
// main routine to change vob-movement
void CSpacerView::SetMoveMode(zTModeMove newmode)
{				
	if (!CMainFrame::mainframe || !infoBar) return;

	// Tastaturbuffer leeren
	for (int k=0;k<MAX_KEYS;k++) zCView::MFC_KeyUp(k);

	zCVob* pickedVob = PICKED_VOB();	
	if (!pickedVob) return;	
	
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);  
	pDoc->SetDirty();

	if (modeMove != newmode)
	{
		if (newmode == MV_NORMAL)
		{			
			pickedVob->SetCollDetStat(colldet_stat_backup);
			pickedVob->SetCollDetDyn(colldet_dyn_backup);
			colldet_disabled = false;			
		}
		else
		{
			colldet_stat_backup		= pickedVob->GetCollDetStat();
			colldet_dyn_backup		= pickedVob->GetCollDetDyn();
			colldet_disabled		= false;
		};
	}

	switch (modeMove)
	{
	case MV_VOB_OVERTAKEN:
		if (pickedVob && pickedVob->GetVobType()==zVOB_TYPE_NSC) 
			pickedVob->SetShowVisual(true);
		break;
	case MV_VOB_CONTROL:
		if (pickedVob && pickedVob->GetVobType()==zVOB_TYPE_NSC) 
			pickedVob->SetPhysicsEnabled(FALSE);
		break;
	case MV_VOB_MOVE:
		break;
	case MV_NORMAL:
		break;
	}

	zCVob* movement_vob = pDoc->camera_vob;

	tmov_mode mt = MOV_WALKING;
	movementCtrl->Grid			(bool(spcConfig.useGrid>0));
	movementCtrl->GridRot		(bool(spcConfig.useGrid>0));
	movementCtrl->SetGrid		(float(spcConfig.moveGrid));
	movementCtrl->SetGridRot	(float(spcConfig.rotGrid));

	switch (newmode)
	{
	case MV_VOB_OVERTAKEN:
		{
			movementCtrl->BackupLook();
			camera_vob[0]	= pickedVob;
			movement_vob	= pickedVob;
			mt				= MOV_WALKING;
			if (pickedVob && pickedVob->GetVobType()==zVOB_TYPE_NSC) 
				pickedVob->SetShowVisual(false);

			#ifdef COMPILING_GOTHIC
				oCNpc* npc = dynamic_cast<oCNpc*>(pickedVob);
				if (npc) 	
				{												
					zERR_MESSAGE(6,0,"B: SPC: Use StandAI for npc "+npc->GetName(TRUE)+" (View::SetMoveMode)");
					npc->UseStandAI();
					npc->SetPhysicsEnabled(TRUE);
				}
			#endif

		}
		break;
	case MV_VOB_CONTROL:
		{
			movementCtrl->BackupLook();
			camera_vob[0]	= pDoc->camera_vob;
			movement_vob	= pickedVob;		
			mt				= MOV_WALKING;

			#ifdef COMPILING_GOTHIC
				oCNpc* npc = dynamic_cast<oCNpc*>(pickedVob);
				if (npc) 
				{	
					zERR_MESSAGE(6,0,"B: SPC: Use StandAI for npc "+npc->GetName(TRUE)+" (View::SetMoveMode)");				
					npc->UseStandAI();
					pickedVob->SetPhysicsEnabled(TRUE);
				}
			#endif

			pickedVob->SetPhysicsEnabled(TRUE);
		}
		break;
	case MV_VOB_MOVE:
		{
			if (modeMove==MV_VOB_OVERTAKEN || modeMove==MV_VOB_CONTROL) 
				movementCtrl->RestoreLook();
			camera_vob[0]   = pDoc->camera_vob;
			movement_vob	= pickedVob;		
			if (modeView==VIEW_TOP) mt=MOV_VOB_PAR; else mt=MOV_VOB_CAM;			

			#ifdef COMPILING_GOTHIC
				oCNpc* npc = dynamic_cast<oCNpc*>(pickedVob);
				if (npc) 
				{	
					zERR_MESSAGE(6,0,"B: SPC: Use StandAI for npc "+npc->GetName(TRUE)+" (View::SetMoveMode)");				
					npc->UseStandAI();
					npc->SetPhysicsEnabled(TRUE);
				}
			#endif

		}
		break;
	case MV_NORMAL:
		{
			if (modeMove==MV_VOB_OVERTAKEN || modeMove==MV_VOB_CONTROL) 
				movementCtrl->RestoreLook();
			camera_vob[0]   = pDoc->camera_vob;
			movement_vob	= pDoc->camera_vob;		
			mt				= MOV_WALKING;		
			movementCtrl->Grid(FALSE);
			movementCtrl->GridRot(FALSE);		
		}
		break;
	}

	if (camera[0])
	{
		camera[0]->SetVob	(camera_vob[0]);
	}
	
	movementCtrl->SetVob	(movement_vob,mt);
	movementCtrl->SetCamVob	(camera_vob[0]);
	
	infoBar->SetPositionVob(camera_vob[0]);
	
	modeMove = newmode;	
	if (modeMove == MV_NORMAL) 
	{
		CMainFrame::mainframe->HandleObjChange(pickedVob, UPDATE_OBJECT_SHEET);
	}	
	SetFocus();
}

void CSpacerView::OnVobMove() 
{
	if (!CMainFrame::mainframe || !infoBar) return;
	
	if (CMainFrame::mainframe->workmode==MODE_MATERIAL)  return;

	if (modeMove!=MV_VOB_MOVE) 
		SetMoveMode(MV_VOB_MOVE);
	else 
		SetMoveMode(MV_NORMAL);
}

void CSpacerView::OnUpdateVobMove(CCmdUI* pCmdUI) 
{	
	zCVob* pickedVob = PICKED_VOB();	

	// pCmdUI->Enable(modeMove == MV_NORMAL || modeMove == MV_VOB_MOVE);	
	zCWorld* world = CSpacerDoc::doc->GetWorld();	
	pCmdUI->Enable(	
		pickedVob && 
		world && 
		world->IsCompiled() && 
		!world->IsCompiledEditorMode() && 
		(pickedVob->GetVobType()!=zVOB_TYPE_LEVEL_COMPONENT) 
	);
	;
	pCmdUI->SetCheck(modeMove == MV_VOB_MOVE);
}

void CSpacerView::OnVobTakeover() 
{
	if (!CMainFrame::mainframe || !infoBar) return;
	
	if (CMainFrame::mainframe->workmode==MODE_MATERIAL)  return;
	
	if (modeMove!=MV_VOB_OVERTAKEN) SetMoveMode(MV_VOB_OVERTAKEN);
	else SetMoveMode(MV_NORMAL);
}

void CSpacerView::OnUpdateVobTakeover(CCmdUI* pCmdUI) 
{	
	zCVob* pickedVob = PICKED_VOB();	

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	pCmdUI->Enable(	
		pickedVob && 
		world && 
		world->IsCompiled() && 
		!world->IsCompiledEditorMode() && 
		(pickedVob->GetVobType()!=zVOB_TYPE_LEVEL_COMPONENT) 
	);	

	pCmdUI->SetCheck(modeMove == MV_VOB_OVERTAKEN);
}

void CSpacerView::OnVobControl() 
{	
	if (!CMainFrame::mainframe || !infoBar) return;

	if (CMainFrame::mainframe->workmode==MODE_MATERIAL)  return;

	if (modeMove!=MV_VOB_CONTROL) 
	{
		SetMoveMode(MV_VOB_CONTROL);
		/*
		modeMove=MV_VOB_CONTROL;
		zCVob* pickedVob = PICKED_VOB();
		PlayAs(pickedVob);
		*/
	}
	else  
	{
		SetMoveMode(MV_NORMAL);
		/*
		modeMove=MV_NORMAL;
		PlayAs(0);
		*/
	}
}

void CSpacerView::OnUpdateVobControl(CCmdUI* pCmdUI) 
{	
	zCVob* pickedVob = PICKED_VOB();	

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	pCmdUI->Enable(	
		pickedVob && 
		world && 
		world->IsCompiled() && 
		!world->IsCompiledEditorMode() && 
		(pickedVob->GetVobType()!=zVOB_TYPE_LEVEL_COMPONENT) 
	);	

	pCmdUI->SetCheck(modeMove == MV_VOB_CONTROL);
}



void CSpacerView::OnVobCollisionDetection() 
{
	if (modeFullscreen) return;	
	zCVob* pickedVob = PICKED_VOB();	

	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	bool result = pDoc->VobDetectCollision(pickedVob);
	if (!result) AfxMessageBox("There are colliding vobs.\r\nHave a look at the list of vobs in the vobtree.");

}

void CSpacerView::OnUpdateVobCollisionDetection(CCmdUI* pCmdUI) 
{		
	zCVob* pickedVob = PICKED_VOB();	

	pCmdUI->Enable(pickedVob!=0 && pickedVob->GetVobType()!=zVOB_TYPE_LEVEL_COMPONENT );
}

void CSpacerView::OnVobColldet() 
{
	if (modeFullscreen) return;

	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	bool result = pDoc->VobDetectCollision();
	if (!result) AfxMessageBox("There are colliding vobs.\r\nHave a look at the list of vobs in the vobtree.");
}
void CSpacerView::OnUpdateWayCreate(CCmdUI* pCmdUI) 
{
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	
	// Enable
	zCWorld* world = pDoc->GetWorld();
	pCmdUI->Enable(	
		pickedWaypoint &&
		world &&
		world->IsCompiled() &&
		!world->IsCompiledEditorMode()  && 
		zDYNAMIC_CAST<zCVobWaypoint>(pickedWaypoint) && 
		zDYNAMIC_CAST<zCVobWaypoint>(pickedWaypoint2nd) &&
		(pickedWaypoint2nd!=pickedWaypoint)
	);
	if (!world) return;

	// SetCheck
	if (!pickedWaypoint || !pickedWaypoint2nd || (pickedWaypoint==pickedWaypoint2nd)) return;
	
	zCWayNet* waynet = world->GetWayNet();if (!waynet) return;
	
	zCWaypoint* wp1 = waynet->SearchWaypoint((zCVobWaypoint*)pickedWaypoint2nd);
	zCWaypoint* wp2 = waynet->SearchWaypoint((zCVobWaypoint*)pickedWaypoint);
	if (!wp1 || !wp2) return;
	
	pCmdUI->SetCheck(pDoc->GetWorld()->GetWayNet()->HasWay(wp1,wp2));
}


void CSpacerView::OnWayCreate() 
{
	if (!pickedWaypoint2nd || !pickedWaypoint) return;
	if (pickedWaypoint2nd==pickedWaypoint) return;
	
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

	pDoc->WayToggleWay(pickedWaypoint2nd,pickedWaypoint);
}

void CSpacerView::PolyClearSelection()
{		
	zCSelPoly* selPoly = NULL;
	if (selPolyList)
	{
		int count = selPolyList->GetNumInList();
		for (int i=0;i<count;i++)
		{
			selPoly = selPolyList->Get(i);
			if (selPoly && selPoly->GetPolygon()) 
			{			
				selPoly->GetPolygon()->SetMaterial(selPoly->GetMaterial());				
			}
		}
	}

	zCList<zCSelPoly>* tmp	= selPolyList2;
	selPolyList2			= selPolyList;
	selPolyList				= tmp;
	if (selPolyList) 
	{
		selPolyList->DeleteListDatas();
		selPolyList->DeleteList();
	}
	pickedPoly=NULL;	
}

zCSelPoly* CSpacerView::PolyIsSelected(zCPolygon * xPoly)
{
	/*
	int count = selPolyList->GetNumInList();
	zCSelPoly* selPoly = NULL;	
	for (int i=0;i<count;i++)
	{
		selPoly = selPolyList->Get(i);
		if (!selPoly || (selPoly->GetPolygon() == xPoly)) break;
	}
	if (selPoly && (selPoly->GetPolygon()!=xPoly)) selPoly = NULL;
	return selPoly;
	*/
	if (!selPolyList) return 0;

	if (selPolyList->GetNumInList()==0) return 0;

	zCList<zCSelPoly>* lList = selPolyList->GetNextInList();
	while (lList && lList->GetData()->GetPolygon()!=xPoly)
		lList = lList->GetNextInList();
	if (lList) return lList->GetData();
	else return 0;
	
}

void CSpacerView::VertMove(zVALUE x, zVALUE y, zVALUE z)
{
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	for (int vz=0; vz<selVertex.GetNumInList(); vz++)
	{
		selVertex[vz]->position[0]+=x;
		selVertex[vz]->position[1]+=y;
		selVertex[vz]->position[2]+=z;
	}
}

void CSpacerView::TextureCalcCenter(zPOINT2& center)
{
	if (!selPolyList) return;

	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	zVALUE uSum = 0;
	zVALUE vSum = 0;
	int count = selPolyList->GetNumInList();
	zCSelPoly* selPoly = NULL;
	int num=0;
	for (int i=0;i<count;i++)
		{
			selPoly = selPolyList->Get(i);
			if (selPoly==NULL) continue;
			if (selPoly->GetPolygon()==NULL) continue;
			for (int j=0;j<selPoly->GetPolygon()->polyNumVert;j++)
			{
				uSum += selPoly->GetPolygon()->feature[j]->texu;
				vSum += selPoly->GetPolygon()->feature[j]->texv;
				num++;
			}
		}
	center.n[VX] = uSum/num;
	center.n[VY] = vSum/num;	
}


void CSpacerView::TextureMirror(zVALUE u, zVALUE v)
{	
	if (!selPolyList) return;

	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	int count = selPolyList->GetNumInList();	
	zCSelPoly* selPoly = NULL;		
	for (int i=0;i<count;i++)
	{			
		selPoly = selPolyList->Get(i);
		if (selPoly==NULL) continue;
		if (u) selPoly->GetPolygon()->TexMirrorU(poly_center.n[VX]);
		if (v) selPoly->GetPolygon()->TexMirrorV(poly_center.n[VY]);
	}
}

void CSpacerView::TextureMove(zREAL x, zREAL y)
{	
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	zREAL grid=(zREAL)spcConfig.moveSpeedTex; // something between 0.1 and 2.0
	if (spcConfig.useGridTex) grid = (zREAL)spcConfig.moveGridTex;
	x = -x * grid;
	y = y * grid;
	x /= 100;y /= 100;

	zPOINT2 p;
	p.n[VX]=x;p.n[VY]=y;	

	zCSelPoly* selPoly = NULL;
	int count = selPolyList->GetNumInList();
	if (count==0)	// no polys selected: use polygone under cursor
		{
			if (!pickedPoly) return;
			pickedPoly->TexTranslate(p);
		}
	else			// polys selected
		for (int i=0;i<count;i++)
		{
			selPoly = selPolyList->Get(i);
			selPoly->GetPolygon()->TexTranslate(p);
		}
	// this operation change the PolyCenter, so refresh it
	TextureCalcCenter(poly_center);
}

void CSpacerView::TextureScale(zVALUE x, zVALUE y)
{	
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	int grid = 1;
	if (spcConfig.useGridTex) grid = spcConfig.moveGridTex;

	int count = selPolyList->GetNumInList();
	if (count==0) return;
	x = zVALUE(-int(x) * grid);
	y = zVALUE(-int(y) * grid);
	x /= 800;y /= 800;	
	
	x+=1;y+=1;
	
	zCSelPoly* selPoly = NULL;			
	for (int i=0;i<count;i++)
	{
		selPoly = selPolyList->Get(i);
		if (selPoly && selPoly->GetPolygon()) 
		{
			selPoly->GetPolygon()->TexScale(poly_center, x,y);			
		}
		
	}	
}

void CSpacerView::TextureShear(zVALUE x, zVALUE y)
{	
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	int grid = 1;
	if (spcConfig.useGridTex) grid = spcConfig.moveGridTex;

	int count = selPolyList->GetNumInList();
	if (count==0) return;
	x = zVALUE(int(x) * grid);
	y = zVALUE(-int(y) * grid);
	x /= 200;y /= 200;	
	
	zCSelPoly* selPoly = NULL;			
	for (int i=0;i<count;i++)
	{
		selPoly = selPolyList->Get(i);
		if (selPoly && selPoly->GetPolygon()) 
		{
			selPoly->GetPolygon()->TexShearU(x);
			selPoly->GetPolygon()->TexShearV(y);
		}
		
	}	
}

void CSpacerView::TextureRotateByAngle(zVALUE angle)
{		
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	if (angle==0) return;
	// alt:
	int count = selPolyList->GetNumInList();
	if (count==0) return;
	
	// zCPolygon* poly = NULL;
	zCSelPoly* selPoly = NULL;	
	for (int i=0;i<count;i++)
	{		
		selPoly = selPolyList->Get(i);
		if (selPoly && selPoly->GetPolygon()) selPoly->GetPolygon()->TexRotate(poly_center,angle);
	}			
}

void CSpacerView::TextureRotate(zVALUE value)
{				
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	int grid = 1;
	if (!spcConfig.useGridTex) grid = spcConfig.moveGridTex;
	
	float angle;
	angle = float(-value * grid);
	TextureRotateByAngle(angle);
	return;
	if (angle==0) return;
	// alt:
	int count = selPolyList->GetNumInList();
	if (count==0) return;
		
	zCSelPoly* selPoly = NULL;	
	for (int i=0;i<count;i++)
	{		
		selPoly = selPolyList->Get(i);
		if (selPoly && selPoly->GetPolygon()) selPoly->GetPolygon()->TexRotate(poly_center,angle);
	}		
	
}

void CSpacerView::PolyHideSelection(bool hide)
{
	if (!selPolyList) return;
	zCSelPoly* selPoly = 0;

	int count = selPolyList->GetNumInList();
	for (int i=0;i<count;i++)
	{
		selPoly = selPolyList->Get(i);
		if (selPoly && selPoly->GetPolygon()) 
		{
			if (hide)	selPoly->GetPolygon()->SetMaterial(selPoly->GetMaterial());				
			else		selPoly->GetPolygon()->SetMaterial(SelectMaterial);	
		}
	}
}

void CSpacerView::PolyFloatSelect(zCPolygon* xPoly)
{
	if (!xPoly) return;
	// Find the mesh in world, where the poly is part of
	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;
	zCMesh* lmesh = pDoc->GetWorld()->GetBspTree()->mesh;   

	int polyi=0;
	while (polyi<lmesh->numPoly && lmesh->Poly(polyi)!=xPoly)
		polyi++;
	if (polyi==lmesh->numPoly) return;
	// found: mesh ok



	/*
	for (int polyi=0; polyi<lmesh->numPoly; polyi++) 
		if (lmesh->polyList[polyi]->CalcNormal()==FALSE)
		{
			
		}
	*/
}


void CSpacerView::PolyMouseOver(UINT nFlags, CPoint point)
{
	if (!camera[0] || !CMainFrame::mainframe || !infoBar) return;	

	if (spcConfig.view_x<point.x || spcConfig.view_y<point.y) return;

	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	if (!pDoc) 
	{
		zERR_WARNING("C: CSpacerView::PolyMouseOver(): no pDoc ptr.!");
		return;
	}

	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;
	
	if (CMainFrame::mainframe->workmode==MODE_MATERIAL)
	{
		// find polygon under mouse-pointer
		zCVob* xVob;
		zCPolygon* xPoly;
		zCVertex* xVert;
		zPOINT3 foundInters;
		CSpacerDoc::doc->GetWorld()->PickScene (*camera[0], point.x, point.y);	
		xVob  = CSpacerDoc::doc->GetWorld()->traceRayReport.foundVob;
		xPoly = CSpacerDoc::doc->GetWorld()->traceRayReport.foundPoly;	
		xVert = CSpacerDoc::doc->GetWorld()->traceRayReport.foundVertex;
		if (CMainFrame::mainframe->workmode==MODE_MATERIAL)
		{
			if (!xPoly) return;
			if (xPoly==pickedPoly) return; // still over the same polygon
		

			// Look if Polygon is still selected
			pickedPoly = xPoly;
			zCSelPoly* selPoly = PolyIsSelected(xPoly);

			// if Polygone not selected: select it (if in selection-mode)
			if (!selPoly && modeSelectPolygons)
			{
				selPoly = new zCSelPoly(xPoly);				
				PolySelect(TRUE, selPoly);
			}	
			// if Polygone selected: deselect it (if in delection-mode)
			else if (selPoly && !modeSelectPolygons)
			{
				if (PolySelect(FALSE, selPoly)) { delete selPoly;selPoly=NULL;}
			}
		}
		if (CMainFrame::mainframe->workmode==MODE_VERTEX)
		{
			if (!xVert) return;
			if (xVert==pickedVertex) return; // still over the same polygon
			if (modeSelectPolygons && !VertIsSelected(xVert)) VertSelect(true,xVert);
			if (!modeSelectPolygons && VertIsSelected(xVert))  VertSelect(false,xVert);
		}
	}
}

void CSpacerView::OnPolyPickmaterial() 
{	
	modePickMaterial = !modePickMaterial;		
	// if (modePickMaterial) PolyClearSelection();
}


void CSpacerView::PolyApplyMapping()
{
	if (!CMainFrame::mainframe || !infoBar) return;

	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	// iterate all selected polygons and create Polygon-List
	zCSelPoly* selPoly = NULL;
	int count = selPolyList->GetNumInList();
	if (count==0) return;

	// hide selection: re-apply texture to the polygons
	PolyHideSelection(TRUE);

	zCList<zCPolygon>* polylist = new zCList<zCPolygon>;
	for (int i=0;i<count;i++)
	{
		selPoly = selPolyList->Get(i);
		if (selPoly) polylist->Insert(selPoly->GetPolygon());
	}	
		// now apply planar mapping to all polygons in generated list
	float x,y;
	CMainFrame::mainframe->GetMaterialMapping(x,y);
	selPolyList->Get(0)->GetPolygon()->TexApplyPlanarMapping(*polylist, x,y);	                     
	// re-select polygons
	PolyHideSelection(FALSE);	
	delete polylist;
}

void CSpacerView::WorldPolyApplyMapping(zVALUE su, zVALUE sv, zCMaterial* mat)
{
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();
	
	zCMesh* lmesh = pDoc->GetWorld()->GetBspTree()->mesh;

	for (int z=0; z<lmesh->numPoly;z++)
		if (lmesh->Poly(z)->GetMaterial()==mat) // i hope it goes :-)
			lmesh->Poly(z)->TexApplyPlanarMapping(su,sv);
	// selPolyList->Get(0)->poly->TexApplyPlanarMapping(*polylist, x,y);	                     
	
}

void CSpacerView::OnPolyApplyTexWithMapping() 
{
	OnPolyApplyTexture();
	PolyApplyMapping();
}

void CSpacerView::OnUpdatePolyApplyM(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CSpacerDoc::doc->IsAWorldLoaded() );
}

void CSpacerView::OnPolyApplyTexture()
{
	if (!CMainFrame::mainframe || !infoBar) return;

	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	zCMaterial* mat = CMainFrame::mainframe->GetMaterial();
	if (!mat) return;

	// iterate all selected polygons and apply
	zCSelPoly* selPoly = NULL;
	int count = selPolyList->GetNumInList();
	for (int i=0;i<count;i++)
	{
		selPoly = selPolyList->Get(i);
		if (selPoly) selPoly->SetMaterial(mat);		
	}
}

void CSpacerView::OnUpdatePolyApplyTexture(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CSpacerDoc::doc->IsAWorldLoaded() );
}

void CSpacerView::OnViewFogging() 
{
	spcConfig.modeFogging = !spcConfig.modeFogging;
	InitSettings();
}

void CSpacerView::OnUpdateViewFogging(CCmdUI* pCmdUI) 
{
	if (modeView==VIEW_TOP)
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->Enable(CSpacerDoc::doc->IsAWorldLoaded());
		pCmdUI->SetCheck(spcConfig.modeFogging);
	}
}

void CSpacerView::VobApplyPhysics(zCVob* _vob, zVEC3 vec)
{
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDoc->SetDirty();

	zCWorld* world = CSpacerDoc::doc->GetWorld();

	// kein Vob?
	if (!_vob) return;

	// Ist der Vob statisch?
	if (_vob->GetStaticVob()) return;

	// Welt nicht ompiliert? Kein ApplyPhysics
	if (!world || !world->IsCompiled() || world->IsCompiledEditorMode()) return;	

	// Bei Wegpunkt	nur die Hoehe korrigieren
	if (dynamic_cast<zCVobWaypoint*>(_vob)) 
	{
		zCWayNet* waynet = world->GetWayNet();
		zCWaypoint* wp = waynet->SearchWaypoint(dynamic_cast<zCVobWaypoint*>(_vob));
		if (wp) wp->CorrectHeight(CSpacerDoc::doc->GetWorld());
		return;
	}
	
#ifdef COMPILING_GOTHIC
	// Bei NSCs auf den Boden stellen
	oCNpc* npc = dynamic_cast<oCNpc*>(_vob);
	if (npc) 
	{ 		
		zERR_MESSAGE(6,0,"B: SPC: Use StandAI for npc "+npc->GetName(TRUE)+" (View::ApplyPhysics)");
		npc->UseStandAI();
		npc->SetPhysicsEnabled(TRUE);
		return;
	}
#endif
	
	// Vobs ohne CollisionDetection duerfen auch nicht fallen!!!
	if (!_vob->GetCollDetStat()) return;

	// So, wenn es denn einen RigidBody gibt, kann es losgehen ...
	if (_vob && _vob->GetRigidBody()) 
		{				
			CDC* pDC = GetDC();

			// aktuelle Position holen ...
			zPOINT3 oldpos, pos, posneu;
			_vob->GetPositionWorld(oldpos);
			pos = posneu = oldpos;

			// Sleepingmode und Physics entsprechend merken und setzen
			// zTVobSleepingMode	mode	= _vob->GetSleepingMode();
			zBOOL				physics	= _vob->GetPhysicsEnabled();
			_vob->SetSleeping		(FALSE);
			_vob->SetPhysicsEnabled	(TRUE);			
											
			if (zinput->KeyPressed(KEY_LSHIFT)) 
			{
				vec=vec*10000;				
			}
			else 
			{
				vec.n[VX]=0;
				vec.n[VZ]=0;
				vec.n[VY]=-300;
			}
			zerr.Message("B: (Spacer) ApplyForceCM on Vob "+zSTRING(vec.n[VX])+"/"+zSTRING(vec.n[VY])+"/"+zSTRING(vec.n[VZ]));
			_vob->GetRigidBody()->ApplyImpulseCM(vec);
			
			// Fall-Loop ...
			int maxTime = 7;
			zCTimer timer;
			timer.ResetTimer();
			zBOOL finished		= FALSE;
			zBOOL canceled		= FALSE;
			zDWORD frameCount	= 0;
			
			time_t startTime;time(&startTime);
			time_t currentTime;
			zDWORD difTime;

			do
			{
				// Schleife (fallen und fallen und fallen ...)
				int eqcount=0;
				do 
				{
					pos = posneu;

					// Naechster Frame ...					
					OnDraw(pDC);
					while (!LastDrawSuccess()) OnDraw(pDC);
					frameCount++;

					// Ist der Vob ion Ruhe?
					_vob->GetPositionWorld(posneu);										
					if (pos==posneu)
						eqcount++;

					zERR_MESSAGE(6,0,"B: APPLYPHYSICS: Position "+zSTRING(posneu.n[VX])+","+zSTRING(posneu.n[VY])+","+zSTRING(posneu.n[VZ]));

					time(&currentTime);
					difTime = (zDWORD)difftime(currentTime, startTime);					

				} while 
					(
					eqcount<3 && 
					difTime<maxTime	&& 
					!canceled
					);

				// Warum wurde Fall-Schleife beendet?
				if (eqcount>=3) 
				// RUhezustand erreicht
				{
					finished=TRUE;	
				}
				else 
				{
					if (timer.GetFrameTime()>=maxTime)
					// Zeit abgelaufen
					{
						int result = MessageBox("Time elapsed\r\nContinue?","Apply Physics",MB_YESNO);
						finished=(result==IDNO);
						if (!finished) time(&startTime);
					}
					else if (canceled)
					// ESC gedrückt
					{
						int result = MessageBox("Cancelled\r\nStop?","Apply Physics",MB_YESNO);
						finished=(result==IDYES);
					};

					if (finished)
					{						
						int result = MessageBox("Reset position of vob?","Apply Physics",MB_YESNO);
						if (result==IDYES)
						{						
							zBOOL cdDyn		= _vob->GetCollDetDyn();
							zBOOL cdStat	= _vob->GetCollDetStat();
							_vob->SetSleeping(FALSE);
							_vob->SetPhysicsEnabled(FALSE);
							_vob->SetCollDetDyn(FALSE);
							_vob->SetCollDetStat(FALSE);		
							_vob->SetPositionWorld(oldpos);
							_vob->SetCollDetDyn(cdDyn);
							_vob->SetCollDetStat(cdStat);		
							pos = oldpos;
						};
					}
				}			
			} while (!finished);

			zerr.Message("B: SPC: calculated physics for "+zSTRING(frameCount)+" frames.");								

			// SleepingMOde und Physics restaurieren
			// _vob->SetSleepingMode(mode);
			_vob->SetPhysicsEnabled(physics);			

			// Nochmal die aktuelle Position setzen
			_vob->SetPositionWorld(pos);

			zCView::MFC_KeyUp (KEY_LCTRL);			
		}		
}

// [EDENFELD] neu 1.33 aus ModSource
void CSpacerView::Do_CompileLight(const spcCCompileLightAction& action)
{
	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);             	
	
	// Boundingbox aufbauen
	zTBBox3D* bbox = 0;

	if (action.dynCompile)
	{
		bbox = new zTBBox3D;
		zVALUE x,y,z;
		zCVobLight *light = CMainFrame::mainframe->GetLightInfoBar()->cur_vob;
		light->GetPositionWorld(x,y,z);			
		bbox->maxs = light->GetBBox3DWorld().maxs;
		bbox->mins = light->GetBBox3DWorld().mins;
	}
	else if (action.region && action.region_value>0)
	{
		bbox = new zTBBox3D;
		zVALUE x,y,z;
		camera_vob[0]->GetPositionWorld(x,y,z);			
		bbox->maxs = zVEC3(x+1,y+1,z+1);
		bbox->mins = zVEC3(x-1,y-1,z-1);	
		bbox->Scale(action.region_value * 100.0f);
	};

	bool workingDlgOpened = false;
	bool winDisabled	  = true;

	if (!action.dynCompile)
	{
		PolyClearSelection();	
		VobSelect(0,true);
		
		if (!workingDlg)
		{
			workingDlgOpened = true;
			workingDlg = new spcCWorkInfoDlg();		
			workingDlg->Init();
		}
		if (workingDlg) workingDlg->AddMessage(" Compile light");

		if (CMainFrame::mainframe) 
		{
			winDisabled = CMainFrame::mainframe->DeactivateApplicationWindows();		
		}	
	}

	if (action.vertex_only)
	{
		if (workingDlg) workingDlg->AddMessage(" compiling (vertex) ...");
		pDoc->GetWorld()->SetWorldRenderMode(zWLD_RENDER_MODE_VERT_LIGHT);
		pDoc->GetWorld()->GenerateStaticWorldLighting(zCWorld::zWLD_LIGHT_VERTLIGHT_ONLY, bbox);
	}
	else
	{
		int level = action.lightmap_level;
		
		if (action.dynCompile) level = 1;

		switch (level)
		{
			case 0:
			case 1: 
				if (workingDlg) workingDlg->AddMessage(" compiling (low) ...");
				pDoc->GetWorld()->SetWorldRenderMode(zWLD_RENDER_MODE_LIGHTMAPS);
				pDoc->GetWorld()->GenerateStaticWorldLighting(zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_LOW_QUAL, bbox);

				break;
			case 2: 
				if (workingDlg) workingDlg->AddMessage(" compiling (mid) ...");
				pDoc->GetWorld()->SetWorldRenderMode(zWLD_RENDER_MODE_LIGHTMAPS);
				pDoc->GetWorld()->GenerateStaticWorldLighting(zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL, bbox);
				break;
			case 3: 				
			default:
				if (workingDlg) workingDlg->AddMessage(" compiling (high) ...");
				pDoc->GetWorld()->GenerateStaticWorldLighting(zCWorld::zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_HI_QUAL, bbox);
				break;
		};
	};

	if (!action.dynCompile)
	{
	
		if (CMainFrame::mainframe && winDisabled) 
		{
			CMainFrame::mainframe->ReactivateApplicationWindows();		
		}

		// restore mainwindow and remove working-dialog	
		if (workingDlgOpened && workingDlg)
		{
			workingDlg->CloseWindow();
			workingDlg->DestroyWindow();		
			workingDlg = 0;
			AfxGetMainWnd()->SetFocus();
		};	
	}

	delete bbox;bbox=0;

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/	
};

void CSpacerView::OnWorldCompilelight() 
{
	if (modeFullscreen) return;

	CSpacerDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);             	
		
	if (!pDoc->IsAWorldLoaded()) return;
	if (!pDoc->GetWorld()->IsCompiled()) return;
	
	spcCCompileLightDlg lightdlg;
	lightdlg.m_light_quality = spcConfig.compileLightQuality;
	lightdlg.m_region_compile = false;
	lightdlg.m_region_value = spcConfig.compileLightRegion;
	if (lightdlg.DoModal()!=IDCANCEL) 
	{				
		spcCCompileLightAction mode;
		mode.vertex_only = (lightdlg.m_light_quality == 0);	// 0 means vertex_only
		mode.lightmap_level = lightdlg.m_light_quality;		// 0-3 (1-3 are valid)
		mode.region = lightdlg.m_region_compile;
		mode.region_value = lightdlg.m_region_value;
		
		spcConfig.compileLightRegion = lightdlg.m_region_value;
		spcConfig.compileLightQuality = lightdlg.m_light_quality;

		Do_CompileLight(mode);

		pDoc->SetDirty();	
	}
}

void CSpacerView::OnUpdateWorldCompilelight(CCmdUI* pCmdUI) 
{
//	CSpacerDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);	

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	pCmdUI->Enable(	
		world && 
		world->IsCompiled() &&
		modeMove == MV_NORMAL
	);
}

void CSpacerView::OnPolyToggleSelection() 
{
	PolyHideSelection(TRUE);
	zCList<zCSelPoly>* tmp	= selPolyList2;
	selPolyList2			= selPolyList;
	selPolyList				= tmp;
	PolyHideSelection(FALSE);	
}


void CSpacerView::AutomapMovement()
{
	int mult=1;
	if (zinput->KeyPressed(KEY_LSHIFT)) mult=10;

	if (zinput->KeyPressed(KEY_LEFT))
	{
		if (camera_vob[0]) camera_vob[0]->MoveLocal(float(-200*mult),0,0);
	}
	if (zinput->KeyPressed(KEY_RIGHT))
	{
		if (camera_vob[0]) camera_vob[0]->MoveLocal(float(+200*mult),0,0);
	}
	if (zinput->KeyPressed(KEY_UP))
	{
		if (camera_vob[0]) camera_vob[0]->MoveLocal(0,float(200*mult),0);
	}
	if (zinput->KeyPressed(KEY_DOWN))
	{
		if (camera_vob[0]) camera_vob[0]->MoveLocal(0,float(-200*mult),0);
	}
	if (zinput->KeyPressed(KEY_A))
	{
		if (camera_vob[0]) camera_vob[0]->MoveLocal(0,0,float(50*mult));
	}
	if (zinput->KeyPressed(KEY_Z))	// [BENDLIN] Addon, KeybFix
	{
		if (camera_vob[0]) camera_vob[0]->MoveLocal(0,0,float(-50*mult));
	}  
}


void CSpacerView::OnVobSaveTree() 
{		
	if (!CMainFrame::mainframe || !infoBar) return;

	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;	
		
	zCVob* pickedVob = PICKED_VOB();	
	if (!pickedVob) return;

	CString filter = "Zenfile (*.zen)|*.zen||";
	
	zoptions->ChangeDir(DIR_WORLD);

	CString expectedName = pickedVob->GetVobName().ToChar();

	CFileDialog dlg(FALSE,"zen",expectedName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{		
		CSpacerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);             		
		pDoc->HandleWorldBeforeSave();
			
		CString name = dlg.GetPathName();
		CSpacerDoc::doc->GetWorld()->SaveVobSubtree(zSTRING(name.GetBuffer(0)), pickedVob );

		pDoc->HandleWorldAfterSave();
	}	
}

void CSpacerView::OnVobInsertTree() 
{	
	if (!CMainFrame::mainframe || !infoBar) return;

	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;	

	zCVob* pickedVob = PICKED_VOB();	
	
	CString filter = "Zenfile (*.zen)|*.zen||";
	
	zoptions->ChangeDir(DIR_WORLD);

	CFileDialog dlg(TRUE,"zen","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{		
		// who should be parent		
		zCVob* parentVob = GetParentVob(pickedVob);
		
		parentVob->AddRef();
			CString name = dlg.GetPathName();
			
			zCVob* vob = CSpacerDoc::doc->GetWorld()->MergeVobSubtree(zSTRING(name.GetBuffer(0)), parentVob);
			
			zPOINT3	pos		= camera_vob[0]->GetPositionWorld();
			zPOINT3	dir		= camera_vob[0]->GetAtVectorWorld();
			zBOOL	lcddyn	= vob->GetCollDetDyn();
			zBOOL	lcdstat	= vob->GetCollDetStat();
			vob->SetCollDet			(FALSE);
			vob->SetPositionWorld	(pos+dir*100);
			vob->SetCollDetDyn		(lcddyn);
			vob->SetCollDetStat		(lcdstat);
					
			CMainFrame::mainframe->HandleVobInsert(vob,parentVob);

		zRELEASE(parentVob);
		
		CSpacerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);             		
		pDoc->SetDirty();	
		pDoc->HandleWorldAfterLoad();
	}		
}


void CSpacerView::OnViewWire() 
{
	wire=!wire;	
	InitSettings();
}

void CSpacerView::OnUpdateViewWire(CCmdUI* pCmdUI) 
{
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	pCmdUI->Enable(world && world->IsCompiled());
	pCmdUI->SetCheck(world && wire);	
}

void CSpacerView::OnUpdateVobInsertTree(CCmdUI* pCmdUI) 
{
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	pCmdUI->Enable(
		modeMove == MV_NORMAL && 
		world->IsCompiled() && 
		!world->IsCompiledEditorMode()
	);	
	
}

void CSpacerView::OnUpdateVobInsertmeshVob(CCmdUI* pCmdUI) 
{
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	pCmdUI->Enable(
		modeMove == MV_NORMAL && 
		world->IsCompiled() && 
		!world->IsCompiledEditorMode()
	);	
}

void CSpacerView::RepeatLastCompileAction(bool emode)
{
	lastCompileWorldAction.force=true;
	lastCompileWorldAction.editormode=emode;
	OnWorldCompile();
}

void CSpacerView::UpdateParticleControl(bool onoff)
{
	if (onoff)
	{
		CSpacerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);             	
		particleControl.SetWorld(pDoc->GetWorld());
	}
	else particleControl.SetWorld(0);
}

void CSpacerView::OnVobPhysics() 
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (world && 
		world->IsCompiled() && 
		!world->IsCompiledEditorMode() && 
		pickedVob && 
		camera_vob[0] 
	)
	{		
		zVEC3 vec = camera_vob[0]->GetAtVectorWorld();
		EnableDrawing	();
		VobApplyPhysics	(pickedVob, vec);		
	}
}

void CSpacerView::OnUpdateVobPhysics(CCmdUI* pCmdUI) 
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	pCmdUI->Enable(
		world && 
		world->IsCompiled() && 
		!world->IsCompiledEditorMode() && 
		pickedVob
	);
}

void CSpacerView::OnDeselect() 
{
	if (CMainFrame::mainframe->workmode==MODE_MATERIAL)
	{
		PolyClearSelection();
	}
	else
	{
		VobSelect(0);
	};
}
void CSpacerView::OnPolyApplyDes() 
{
	OnPolyApplyTexture();
	PolyClearSelection();
}



void CSpacerView::OnCSIntegrate() 
{
	if (!CMainFrame::mainframe || !infoBar) return;

	if (!CMainFrame::mainframe->CSActive()) return;	

	zCVob* pickedVob = PICKED_VOB();	
	
	if (!pickedVob) return;
	
/*
	zCClassDef* classDef = pickedVob->GetClassDef();
	if (classDef->IsScriptedClass())
	{
		MessageBox("You can't use scripted objects for integration!");
		return;
	};
*/
	if (pickedVob->GetVobName().IsEmpty())
	{
		AfxMessageBox("Please set a vobname to integrate this vob!");
		return;
	};

	CMainFrame::mainframe->CSAssignIntegratedRole(pickedVob);
}

void CSpacerView::OnCsReget() 
{	
	zCVob* vob = CMainFrame::mainframe->CSRegetIntegratedRole();

	// Der Vob wurde erzeugt und noch nicht release, deshalb muss das hier am Ende geschehen!!

	if (vob)
	{
		CSpacerDoc::doc->InsertVob(vob);
		VobGoto(vob);

		// Bei einer CSCamera muessen die Keyframe-Vobs noch erzeugt werden
		zCCSCamera* cam = dynamic_cast<zCCSCamera*>(vob);
		if (cam)
		{		
			// Auch die Keyframes haben einen um 1 zu hohen RefCtr: RELEASE THEM
			zCVob* keyvob;
			for (int pcount=0; pcount<cam->GetNumCamKeys(); pcount++)
			{	
				keyvob = cam->GetCamKey(pcount);
				CSpacerDoc::doc->InsertVob(keyvob,0,0,cam);		
				//zRELEASE(keyvob);
			}
			for (int tcount=0; tcount<cam->GetNumTargetKeys(); tcount++)
			{
				keyvob = cam->GetTargetKey(tcount);
				CSpacerDoc::doc->InsertVob(keyvob,0,0,cam);
				//zRELEASE(keyvob);
			}
			
			cam->Refresh();				
		};

		CSpacerDoc::doc->VobHandleAfterLoad(vob);
		AfxMessageBox("Vob "+CString(vob->GetVobName().ToChar())+" inserted succesfully");
	}
	else
	{
		AfxMessageBox("Did not find a vob to insert.");
	};

	zRELEASE(vob);
}


void CSpacerView::OnCsDeclarePc() 
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	#ifdef COMPILING_GOTHIC
		if (pickedVob->GetVobType()!=zVOB_TYPE_NSC) return;

		if (oCNpc::player != pickedVob) 
		{ 
			zMATRIX4 trafo = camera_vob[0]->trafoObjToWorld;

			oCNpc::player = dynamic_cast<oCNpc*>(pickedVob);
			if (oCNpc::player) oCNpc::player->SetAsPlayer();
			
			zCPlayerInfo* playerInfo = dynamic_cast<zCPlayerInfo*>(zCPlayerInfo::GetActivePlayer());
			if (!playerInfo) playerInfo	= (zCPlayerInfo*)zfactory->CreatePlayerInfo();
			playerInfo	-> SetPlayerVob	(oCNpc::player);
			playerInfo	-> SetActive	();

			camera_vob[0]->SetTrafoObjToWorld(trafo);
		}
		else if (pickedVob)
		{
			oCNpc::player=0;
			zCPlayerInfo* playerInfo = dynamic_cast<zCPlayerInfo*>(zCPlayerInfo::GetActivePlayer());
			if (playerInfo) playerInfo->SetPlayerVob(0);
		};
	#endif
}

void CSpacerView::OnUpdateCsDeclarePc(CCmdUI* pCmdUI) 
{		
	zCVob* pickedVob = PICKED_VOB();	
	
	#ifdef COMPILING_GOTHIC
		pCmdUI->Enable(pickedVob && dynamic_cast<oCNpc*>(pickedVob));
		pCmdUI->SetCheck(pickedVob && pickedVob == oCNpc::player);
	#else
		pCmdUI->Enable(FALSE);
	#endif	
}

void CSpacerView::OnUpdateCsIntegrate(CCmdUI* pCmdUI) 
{
	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);             		
	zCWorld* world = pDoc->GetWorld();
	pCmdUI->Enable(world!=NULL && CMainFrame::mainframe && CMainFrame::mainframe->GetCutsceneSeqWindow()->IsWindowVisible());
	pCmdUI->SetCheck(world->GetDrawVobBBox3D());	
}

void CSpacerView::OnPolyPlanar() 
{
	int result = AfxMessageBox("Do you really want to make them planar?",MB_YESNO);
	if (result==IDYES)
	{
		zCArray<zCPolygon*> polyList;
		zCSelPoly* selPoly = NULL;
		int count = selPolyList->GetNumInList();
		for (int i=0;i<count;i++)
		{
			selPoly = selPolyList->Get(i);
			if (selPoly) polyList.Insert(selPoly->GetPolygon()); 
		}

		zCPolygon::AlignPolyListToAvgPlane		(polyList);

		CSpacerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->SetDirty();
	}
}



void CSpacerView::OnToolsMacros() 
{
	CSpacerDoc* pDoc = GetDocument();

	spcCMacroDlg	dlg;
	spcCMacro*		macro;
	if (dlg.DoModal()==IDOK)
	{
		macro = dlg.GetExecuteMacro();		
		if (macro)
		{
			macro->Run(pDoc, this);
		};		
	};
}

/*
void CSpacerView::OnUpdateToolsMacros(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
}
*/

void CSpacerView::OnViewFullscreen() 
{	

		static float old_friction, old_friction_rot, old_speed;
		if (!modeFullscreen) 
		{			
			modeFullscreen	= true;

	#ifdef COMPILING_GOTHIC
			freeLook		= TRUE;
	#endif				

			movementCtrl->GetFriction(old_friction, old_friction_rot);
			movementCtrl->SetFriction(0.9f,0.9f);		
			movementCtrl->LookForward();
			SetCapture();
			while (ShowCursor(FALSE)>=0);
		}
		else 
		{					
			modeFullscreen	= false;
			ReleaseCapture();

	#ifdef COMPILING_GOTHIC
			freeLook		= FALSE;			
	#endif
						
			movementCtrl->SetFriction(old_friction, old_friction_rot);
			movementCtrl->LookForward();
			ShowCursor(TRUE);
		}
}

void CSpacerView::OnUpdateViewFullscreen(CCmdUI* pCmdUI) 
{
	bool enabled = infoBar && (infoBar->GetActiveWorld()!=0);	
	pCmdUI->Enable(enabled);
	pCmdUI->SetCheck(modeFullscreen);
}


void CSpacerView::OnToolsGotoposition() 
{
	if (!CSpacerDoc::doc->GetWorld()) return;
	if (camera_vob[0]) 
	{	
		RememberCamPos();
		camLastAutoRemembered=true;

		spcCPositionDlg dlg;
		float x,y,z;
		camera_vob[0]->GetPositionWorld(x,y,z);		
		zPOINT3 atvec = camera_vob[0]->GetAtVectorWorld();
		dlg.m_edit_x = x; dlg.m_edit_y = y; dlg.m_edit_z = z;
		dlg.m_at_x = atvec[VX]; dlg.m_at_y = atvec[VY]; dlg.m_at_z = atvec[VZ];
		dlg.m_levelname = "unknown";
		if (dlg.DoModal()==IDOK)
		{			
			camera_vob[0]->BeginMovement();
			camera_vob[0]->SetPositionWorld(dlg.m_edit_x, dlg.m_edit_y, dlg.m_edit_z);
			camera_vob[0]->EndMovement();
		};		
	}	
}

void CSpacerView::OnToolsGotoOrigin() 
{	
	zMAT4 trafo(0);
	zVEC3 pos(0,200,0);
	trafo.SetTranslation(pos);
	if (camera_vob[0]) 
	{
		RememberCamPos();
		camLastAutoRemembered=true;

		camera_vob[0]->BeginMovement();
		camera_vob[0]->SetPositionWorld(0,200,0);
		camera_vob[0]->EndMovement();
	}	
}



void CSpacerView::OnToolsSpecialSavetmpdoc() 
{
	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnQuickSave();
}

void CSpacerView::OnToolsSpecialLoadtmpdoc() 
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->GetWorld())
	{	
		zSTRING lastPickName;
		if (pickedVob) lastPickName = pickedVob->GetVobName();
		pDoc->OnQuickOpen();
		if (!lastPickName.IsEmpty()) pickedVob = pDoc->GetWorld()->SearchVobByName(lastPickName);
	}
}


void CSpacerView::OnViewvobCopy() 
{
	if (!CMainFrame::mainframe || !infoBar) return;	

	zCVob* pickedVob = PICKED_VOB();	
	if (!pickedVob) return;	
		
	if (pickedVob->GetClassDef()->IsScriptedClass())
	{
		MessageBox("You can't copy and paste scripted objects!");
		return;
	};

	vobCopyName = pickedVob->GetVobName().ToChar();

	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_BINARY, TRUE);		

		arch->WriteObject("spcVobCopy",pickedVob);
		zCBuffer* buffer = arch->GetBuffer();

		delete vobCopyBuffer;	
		vobCopyBuffer = new zCBuffer(buffer->GetSize()+1);
		vobCopyBuffer->Write(buffer->GetBuffer(),buffer->GetSize());	

		vobCopyBuffer->SetPosBegin();
	
		CMainFrame::mainframe->VobCopy(pickedVob);

	arch->Close();	
	zRELEASE(arch);
}

void CSpacerView::OnViewvobPaste() 
{
	if (modeFullscreen) return;
	if (!vobCopyBuffer) return;	
	zCVob* pickedVob = PICKED_VOB();			

	CSpacerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	if (!pDoc->IsAWorldLoaded()) return;

	zCVob* newvob=0;

	zCArchiver* arch = zarcFactory.CreateArchiverRead(vobCopyBuffer);
	if (arch)
	{
		newvob = dynamic_cast<zCVob*>(arch->ReadObject("spcVobCopy"));
		arch->Close();
		zRELEASE(arch);
	}

	if (!newvob) return;

	zBOOL cddyn;
	zBOOL cdstat;
	if (!newvob->GetClassDef()->IsScriptedClass())
	{
		cddyn = newvob->GetCollDetDyn();
		cdstat = newvob->GetCollDetStat();		
	}
	
	zPOINT3 pos = camera_vob[0]->GetPositionWorld();		
	zPOINT3 dir = camera_vob[0]->GetAtVectorWorld();
	pos = pos + dir*200;
	
	pDoc->InsertVob(newvob,&pos,&dir,pickedVob);
	
	if (!newvob->GetClassDef()->IsScriptedClass())
	{		
		newvob->SetCollDetDyn(cddyn);
		newvob->SetCollDetStat(cdstat);

		VobSelect(newvob);
	}

	zRELEASE(newvob);	
}

void CSpacerView::OnViewvobPlay() 
{	
	if (modeFullscreen) return;	
	zCVob* pickedVob = PICKED_VOB();	
	
	zCVobSound*	soundVob = dynamic_cast<zCVobSound*>(pickedVob);
	if (!soundVob) return;

	soundVob->StopSound();

	soundVob->StartSound();
	sysIdle(2000);
	soundVob->StopSound();
}

void CSpacerView::OnUpdateViewvobPlay(CCmdUI* pCmdUI) 
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	pCmdUI->Enable(dynamic_cast<zCVobSound*>(pickedVob) != NULL);
}


void CSpacerView::OnKeyPopup() 
{
	ShowPopupMenue( CPoint(50,50) );
}

void CSpacerView::OnUpdateViewvobPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(vobCopyBuffer != NULL);
	
}

void CSpacerView::OnUpdateViewvobCopy(CCmdUI* pCmdUI) 
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	pCmdUI->Enable(pickedVob != NULL);	
}

void CSpacerView::OnViewvobGoto5meters() 
{		
	zCVob* pickedVob = PICKED_VOB();	
	
	if (pickedVob) SetCamInFrontOfVob(pickedVob,500);
}

void CSpacerView::OnViewvobGoto2meters() 
{	
	zCVob* pickedVob = PICKED_VOB();		

	if (pickedVob) SetCamInFrontOfVob(pickedVob,200);
}

void CSpacerView::OnViewvobGoto1meter() 
{	
	zCVob* pickedVob = PICKED_VOB();	
	
	if (pickedVob) SetCamInFrontOfVob(pickedVob,100);
}

void CSpacerView::OnViewvobGotoHalfmeter() 
{	
	zCVob* pickedVob = PICKED_VOB();

	if (pickedVob) SetCamInFrontOfVob(pickedVob,50);
}

void CSpacerView::SetCamInFrontOfVob(zCVob *vob, int distance)
{
	if (modeFullscreen)	return;
	if (!vob)			return;
	if (!camera_vob[0])	return;
	zPOINT3 vob_pos = vob->GetPositionWorld();
	zPOINT3 cam_vec = camera_vob[0]->GetAtVectorWorld();

	camera_vob[0]->SetPositionWorld(vob_pos-cam_vec*(float)distance);
}


void CSpacerView::PositionShortcut(int nr, bool jump) 
{	
	if (!jump)
	{
		// Define Shortcut
		if (camera_vob[0]) 
		{
			rememberedPositions.InsertAtPos(camera_vob[0]->trafoObjToWorld, nr);
			zERR_MESSAGE(2,0,"B: SPC: (Re)defined shortcut "+zSTRING((int)nr));
			Beep(4000,150);
		}
	}
	else
	{
		// Jump to Position
		if (camera_vob[0] && rememberedPositions[nr] != zMAT4(0))
		{
			camera_vob[0]->BeginMovement();
			camera_vob[0]->SetTrafoObjToWorld(rememberedPositions[nr]);
			camera_vob[0]->EndMovement();
			
			zERR_MESSAGE(2,0,"B: SPC: Jumped to shortcut "+zSTRING((int)nr));
			Beep(4000,100);
		}
	}			
}

void CSpacerView::OnShortcut1()		{ PositionShortcut(1,true); }
void CSpacerView::OnShortcut1Def()	{ PositionShortcut(1,false); }
void CSpacerView::OnShortcut2()		{ PositionShortcut(2,true); }
void CSpacerView::OnShortcut2Def() 	{ PositionShortcut(2,false); }
void CSpacerView::OnShortcut3() 	{ PositionShortcut(3,true); }
void CSpacerView::OnShortcut3Def() 	{ PositionShortcut(3,false); }
void CSpacerView::OnShortcut4() 	{ PositionShortcut(4,true); }
void CSpacerView::OnShortcut4Def() 	{ PositionShortcut(4,false); }

void CSpacerView::OnViewvobVobLetfalldown() 
{
	zCVob* pickedVob = PICKED_VOB();	
	
	if (!pickedVob) return;

	zERR_WARNING("B: SPC: right mouseclick -> Applying physic on object");
	zVEC3 vec;
	vec = camera_vob[0]->GetAtVectorWorld();
	//*** EnableDrawing();
	VobApplyPhysics(pickedVob, vec);
}




void CSpacerView::AddVobToWorld(zCVob* childVob, zCVob* parentVob)
{
	if (!CMainFrame::mainframe || !infoBar) return;

	zCWorld* world = infoBar->GetActiveWorld();
	if (!world) return;

	parentVob = GetParentVob(parentVob);
	CSpacerDoc::doc->InsertVob(childVob,0,0,parentVob);
	
	CMainFrame::mainframe->HandleVobInsert(childVob,parentVob);
	childVob->ResetXZRotationsWorld();	

	VobSelect(childVob);					
};


void CSpacerView::OnVobCreatePreset() 
{	
	zCVob* pickedVob = PICKED_VOB();
	if (!pickedVob) return;

	zCObjPresetLib* lib = &CMainFrame::mainframe->presetLib;

	zCClassDef* classDef = pickedVob->GetClassDef();
	if (classDef->IsScriptedClass())
	{
		MessageBox("You can't create presets of scripted objects");
		return;
	};
	if (classDef->IsAbstractClass())
	{
		MessageBox("Fatal.Fatal.Fatal\r\nHow does this object of an abstract class could exist?");
		zERR_FATAL("B: SPC: Object of abstract class found. What went wrong?");
		return;
	};

	CString className = classDef->GetClassName_().ToChar();
	zSTRING presetName;
	bool ready = false;
	int result;
	zCObject* obj;
	spcCInputDialog dlg;
	dlg.m_text = "Type name of new preset\r\nclass \""+className+"\"";
	dlg.SetInput(pickedVob->GetVobName().ToChar());
	do 
	{		
		result = dlg.DoModal();
		if (result==IDOK)
		{
			presetName = dlg.GetInput().GetBuffer(0);
			obj = lib->GetObjectByName(presetName);
			ready = (obj==NULL);
			dlg.m_text = "Type another name! "+dlg.GetInput()+" is already in use.\r\nclass \""+className+"\"";
		}
		else ready=true;

	} while (!ready);

	if (result==IDOK)
	{
		lib->AddPreset(pickedVob, presetName);
	}
}

void CSpacerView::OnUpdateViewvobVobCreatepreset(CCmdUI* pCmdUI) 
{
	zCVob* pickedVob = PICKED_VOB();
	pCmdUI->Enable(pickedVob!=NULL);	
}

void CSpacerView::OnViewTogglesound() 
{
	view_sound = !view_sound;
}

void CSpacerView::OnViewWaynet() 
{
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (!world) return;

	view_waynet = !view_waynet;
	dynamic_cast<oCGame*>(CSpacerDoc::doc->session)->SetDrawWaynet(view_waynet);
	
}

void CSpacerView::OnUpdateViewWaynet(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CSpacerDoc::doc->IsAWorldLoaded());
	pCmdUI->SetCheck(view_waynet);
}

void CSpacerView::OnUpdateViewTogglesound(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

zCVob* CSpacerView::GetParentVob(zCVob* candidate)
{	
	return CSpacerDoc::doc->GetParentVob(candidate);
}

void CSpacerView::SetViewMode(zTModeView mode)
{
	// VIEW_PERSON, VIEW_TOP, VIEW_BOTTOM, VIEW_SPLIT2
	modeView = mode;
}


void CSpacerView::OnUpdatePolyToggleSel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CSpacerDoc::doc->IsAWorldLoaded() );
}

void CSpacerView::OnUpdatePolyPlanar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CSpacerDoc::doc->IsAWorldLoaded() );
}

void CSpacerView::OnUpdateDeselect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CSpacerDoc::doc->IsAWorldLoaded() );
}

void CSpacerView::OnUpdatePolyApplyDes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CSpacerDoc::doc->IsAWorldLoaded() );
}

void CSpacerView::OnUpdatePolyPickmaterial(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(
		CMainFrame::mainframe 
		&& (CMainFrame::mainframe->workmode==MODE_MATERIAL)
		&& CSpacerDoc::doc->IsAWorldLoaded()
	);
	pCmdUI->SetCheck(modePickMaterial);
}

void CSpacerView::OnUpdateVobColldet(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CSpacerDoc::doc->IsAWorldLoaded() );
}


CSpacerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;	
	
	return 0;
}

void CSpacerView::PlayAs(zCVob *vob)
{	
	#ifdef COMPILING_GOTHIC
	if (!vob) 
	{
		oCNpc* npc = dynamic_cast<oCNpc*>(playAsVob);
		if (!npc) return;	
		
		zERR_MESSAGE(6,0,"B: SPC: Use StandAI for npc "+npc->GetName(TRUE)+" (View::PlayAs)");
		npc->UseStandAI();
		npc->SetPhysicsEnabled(TRUE);

		oCNpc::player=0;		
		
		zRELEASE(playAsVob);

		// npc->SetMovLock(TRUE);
	}
	else
	{
		if (playAsVob) PlayAs(0);
		
		oCNpc* npc = dynamic_cast<oCNpc*>(vob);
		if (!npc) return;

		CSpacerDoc::doc->session->CamInit(camera_vob[0],camera[0]);

		oCAIHuman* humanAI = new oCAIHuman();
		humanAI->Init(npc);
		npc->SetSleeping(FALSE);
		//npc->SetAIDisabled(FALSE);
		npc->SetAI(humanAI);
		npc->SetAsPlayer();		
		
		playAsVob = vob;
		playAsVob->AddRef();

		npc->SetMovLock(FALSE);
	}
#endif
}

void CSpacerView::OnToggleBilinearFiltering() 
{
	zrenderer->SetBilerpFilterEnabled( !zrenderer->GetBilerpFilterEnabled() );
}

void CSpacerView::OnUpdateToggleBilinearFiltering(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CSpacerDoc::doc->IsAWorldLoaded() && zrenderer!=NULL);
	if (zrenderer) pCmdUI->SetCheck(zrenderer->GetBilerpFilterEnabled());	
}



void CSpacerView::OnVobRemove() 
{
	zCVob* pickedVob = PICKED_VOB();

	if (!pickedVob)					return;	
	if (modeMove!=MV_NORMAL)		return;
	if (pickedVob==camera_vob[0])	return;	

	EnableDrawing(FALSE);

	if (pickedVob==pickedWaypoint) pickedWaypoint=NULL;
	if (pickedVob==pickedWaypoint2nd) pickedWaypoint2nd=NULL;
		
	CSpacerDoc::doc->RemoveVob(pickedVob);

	EnableDrawing();	
}

void CSpacerView::OnVobInsertByKey() 
{
	zCVob* vob = pickedWaypoint; // Wegpunkt merken 
	VobSelect(0,false);
	pickedWaypoint = vob;
	OnVobInsert();
}

void CSpacerView::OnVobInsert() 
{		
	if (!CMainFrame::mainframe || !infoBar) return;	
	
	zCVob* pickedVob = PICKED_VOB();		
	zCVob* parent = GetParentVob(pickedVob);

	zPOINT3 pos = camera_vob[0]->GetPositionWorld();
	zPOINT3 dir = camera_vob[0]->GetAtVectorWorld();							

	zCVob* newvob = CMainFrame::mainframe->CreateNewVob();

	if (newvob)
	{		
		pos = pos + dir*200;
		
		CSpacerDoc::doc->InsertVob(newvob,&pos, &dir, pickedVob);
	}
	else
	{			
		newvob = CMainFrame::mainframe->InsertVob(pos,dir,parent);						
	}

	zRELEASE(newvob);
}



void CSpacerView::HandleVobInsert(zCVob *vob, zCVob* parentVob)
{		
	if (dynamic_cast<zCVobWaypoint*>(vob)) 
	{
		pickedWaypoint2nd = pickedWaypoint;
		pickedWaypoint = dynamic_cast<zCVobWaypoint*>(vob);		
		if (pickedWaypoint && pickedWaypoint2nd) 
		{
			CSpacerDoc::doc->WayToggleWay(pickedWaypoint,pickedWaypoint2nd);
		}
	}

	VobSelect(vob,true);
};


void CSpacerView::PrepareInsertedWaypoint(zCVob *vob)
{	
	// kann weg
	
}


void CSpacerView::HandleVobRemove(zCVob *vob)
{
	VobSelect(0,true);
};


void CSpacerView::HandleVobSelect(zCVob *vob)
{	
};


void CSpacerView::OnViewvobVobSizedownbbox() 
{
	zCVob* pickedVob = PICKED_VOB();	
	if (!pickedVob) return;
	/* Einkommentieren und CTRK+SHIFT+B druecken->Absturz
		zCVob* vob=0;
		vob->GetPositionWorld(0,0,0);
	*/
	zVALUE x,y,z;
	pickedVob->GetPositionWorld(x,y,z);
	zTBBox3D bbox;
	bbox.maxs = zPOINT3(x+50,y+50,z+50);
	bbox.mins = zPOINT3(x-50,y-50,z-50);
	pickedVob->SetBBox3DWorld(bbox);
}


void CSpacerView::OnVieweditTogglecamsplines() 
{
	zCCSCamera::SetDrawEnabled( !zCCSCamera::GetDrawEnabled() );
}

void CSpacerView::OnUpdateVieweditTogglecamsplines(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(zCCSCamera::GetDrawEnabled());
}

void CSpacerView::OnCaptureChanged(CWnd *pWnd) 
{
	zERR_MESSAGE(1,0,"B: SPC: OnCaptureChanged");
	if (modeFullscreen)
	{
		SetForegroundWindow();
		SetFocus();
		SetCapture();		
	}
	// CView::OnCaptureChanged(pWnd);
}

void CSpacerView::OnVobTest() 
{
	
}

void CSpacerView::OnUpdateVobTest(CCmdUI* pCmdUI) 
{
	#ifdef _DEBUG
		pCmdUI->Enable(TRUE);
	#else
		pCmdUI->Enable(FALSE);		
	#endif	
}


void CSpacerView::OnVieweditTextoutput() 
{
	viewTextOut = !viewTextOut;

	if (zCView::stdoutput->GetOwner()) zCView::stdoutput->GetOwner()->RemoveItem(zCView::stdoutput);
	#ifdef COMPILING_GOTHIC
	zCView* textview = ogame->GetView(oCGame::GAME_VIEW_AMBIENT);
	if (textview->GetOwner()) textview->GetOwner()->RemoveItem(textview);
	#endif
	

	if (!viewTextOut)
	{						
		screen->RemoveItem(zCView::stdoutput);
		#ifdef COMPILING_GOTHIC		
			oCGame::oEGameDialogView enuViewAmbient = oCGame::oEGameDialogView::GAME_VIEW_AMBIENT;			
			ogame->CloseView( enuViewAmbient );
			ogame->EnableView	( enuViewAmbient, FALSE );		
		#endif
	}
	else
	{
		screen->InsertItem(zCView::stdoutput);
		#ifdef COMPILING_GOTHIC												
			oCGame::oEGameDialogView enuViewAmbient = oCGame::oEGameDialogView::GAME_VIEW_AMBIENT;			
			ogame->EnableView( enuViewAmbient, TRUE);		
			ogame->OpenView( enuViewAmbient );			
		#endif

	}	
}

void CSpacerView::OnUpdateVieweditTextoutput(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CSpacerDoc::doc->IsAWorldLoaded());
	pCmdUI->SetCheck(viewTextOut);
}

void CSpacerView::OnVieweditToggleinfotext() 
{
	viewInfoText = !viewInfoText;
}

void CSpacerView::OnUpdateVieweditToggleinfotext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CSpacerDoc::doc->IsAWorldLoaded());
	pCmdUI->SetCheck(CSpacerDoc::doc->IsAWorldLoaded() && viewInfoText);
}

void CSpacerView::OnViewVob() 
{
	zCVob* pickedVob = PICKED_VOB();
	if (!pickedVob) return;
	zCVisual* visual = pickedVob->GetVisual();
	if (!visual) 
	{
		CSpacerDoc::doc->VobHandleAfterLoad(pickedVob); // sichbar machen
	}
	else
	{		
		CSpacerDoc::doc->VobHandleBeforeSave(pickedVob); // unsichtbar machen
	};
}

void CSpacerView::OnUpdateViewVob(CCmdUI* pCmdUI) 
{
	zCVob* pickedVob = PICKED_VOB();
	pCmdUI->Enable(pickedVob!=0);	
	pCmdUI->SetCheck(pickedVob && !modeFullscreen && (pickedVob->GetVisual()!=0));
}

void CSpacerView::OnUpdateVobProperties(CCmdUI* pCmdUI) 
{
	zCVob* pickedVob = PICKED_VOB();
	pCmdUI->Enable(pickedVob!=0);
};

void CSpacerView::OnVobProperties() 
{
	zCVob* pickedVob = PICKED_VOB();

	if (!pickedVob) return;

	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII, TRUE);
	
	zSTRING eol = arch->GetStringEOL();	
	arch->SetStringEOL("\r\n");	
	arch->WriteObject("spcVobView",pickedVob);

	zSTRING infotext;
	arch->GetBufferString(infotext);
	spcCTextInfoDlg dlg;
	zSTRING name = pickedVob->GetClassDef()->GetClassName_()+"::"+pickedVob->GetVobName();
	dlg.SetTitle(name.ToChar());
	dlg.m_contents = infotext.ToChar();
	dlg.DoModal();		

	arch->SetStringEOL(eol);
	arch->Close();	
	zRELEASE(arch);
};

void CSpacerView::OnVobVobname() 
{
	if (!CSpacerDoc::doc) return;

	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (!world) return;

	zCVob* pickedVob = PICKED_VOB();	
	if (!pickedVob) return;
	

	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);

	zSTRING vobname = pickedVob->GetVobName();
	spcCInputDialog dlg;
	dlg.m_text = "Enter vobname:";	
	dlg.SetInput(vobname.ToChar());
	zBOOL ready = FALSE;
	while (!ready)
	{
		int result = dlg.DoModal();
		if (result == IDOK)
		{	
			vobname = dlg.GetUpperInput().GetBuffer(0);
			zCVob* vob = world->SearchVobByName(vobname);
			if (!vob)
			{
				// Check typed name
				if (arch->IsStringValid(dlg.GetUpperInput().GetBuffer(0)))
				{
					// Set Name
					pickedVob->SetVobName(dlg.GetUpperInput().GetBuffer(0));
					ready=true;
				}
				else
				{
					MessageBox("String is not valid.");
				};
			}
		} else ready = true;
	}	

	arch->Close();
	zRELEASE(arch);
}

void CSpacerView::OnUpdateVobVobname(CCmdUI* pCmdUI) 
{
	zCVob* pickedVob = PICKED_VOB();
	pCmdUI->Enable(pickedVob!=0);
}


void CSpacerView::OnViewvobVobMovehere() 
{
	zCVob* pickedVob = PICKED_VOB();
	if (!pickedVob) return;	

	zBOOL cdDyn		= pickedVob->GetCollDetDyn();
	zBOOL cdStat	= pickedVob->GetCollDetStat();
	pickedVob->SetCollDet(FALSE);	

	zPOINT3 pos		= camera_vob[0]->GetPositionWorld();	
	zPOINT3 dir		= camera_vob[0]->GetAtVectorWorld();	

	pickedVob->SetPositionWorld(pos+dir*100);

	pickedVob->SetCollDetDyn(cdDyn);
	pickedVob->SetCollDetStat(cdStat);

}

void CSpacerView::RememberCamPos(bool remember)
{
	if (remember)
	{
		camLastRemembered = true;
		camLastPos = camera_vob[0]->GetPositionWorld();
		camLastDir = camera_vob[0]->GetAtVectorWorld();
	}
	else camLastRemembered = false;
};

void CSpacerView::ResetCamPos()
{
	if (camLastRemembered)
	{
		zPOINT3 pos = camLastPos;
		zPOINT3 dir = camLastDir;
		RememberCamPos();
		camLastAutoRemembered=true;
		camera_vob[0]->SetPositionWorld(pos);
		camera_vob[0]->SetHeadingAtWorld(dir);
	};
};

//::GetFocus()
//::GetForegroundWindow();


void CSpacerView::OnToggleCamPos() 
{
	ResetCamPos();
}

void CSpacerView::OnUpdateToggleCamPos(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(camLastRemembered);	
}

void CSpacerView::OnRememberCamPos() 
{
	RememberCamPos();
	camLastAutoRemembered=false;
}

void CSpacerView::OnUpdateRememberCamPos(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(camera_vob[0]!=0);
	pCmdUI->SetCheck(camLastRemembered && !camLastAutoRemembered);	
}

void CSpacerView::ResetCameraAfterPlay()
{
	infoBar->SetSelectedObject(camera_vob[0]);
	if (!camera[0]) return;
	camera[0]->SetVob(camera_vob[0]);
	this->SetMoveMode(MV_NORMAL);

	if (zCAICamera::GetCurrent() && zCAICamera::GetCurrent()->GetVob())
		zCAICamera::GetCurrent()->GetVob()->RemoveVobFromWorld();
};