// MainFrm.cpp : implementation of the CMainFrame class
//

// #include "zCompilerVcWin32.h"

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"

// z-Files
#include "zWaynet.h"
#include "zsndMSS.h"
#include "zworld.h"
#include "zvob.h"
#include "zConsole.h"
#include "zexceptionhandler.h"

#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "MainFrm.h"
#include "SpacerDoc.h"
#include "SpacerView.h"
#include "spcCSetView.h"
#include "spcCSetGeneral.h"
#include "spc_ParseTools.h"
#include "spcCCSSequencer.h"
#include "spcCConsoleDialog.h"
#include "spcCWorkInfoDlg.h"
#include "spcCClassInfo.h"

#include "spcCObjectBar.h"
#include "spcCInfoBar.h"
#include "spcCInfoBar_Lights.h"
#include "spcCInfoBar_Sounds.h"
#include "spcCInfoBar_Specials.h"
#include "spcCInfoBar_Camera.h"
#include "spcCInfoBar_Materials.h"
#include "spcCInfoBar_Events.h"
#include "spcCInfoBar_Vobs.h"
#include "spcCInfoBar_Vertex.h"
#include "spcCInfoBarVobsPlus.h"
#include "spcCVobLogicalDialog.h"
#include "spcCVobContainer.h"
#include "spcCInputDialog.h"

#include "spcCList_Vobs.h"
#include "spcCList_Materials.h"
#include "spcCList_ou.h"
#include "spcCObjectSheet.h"
#include "spcCHelpDlg.h"
#include "zinput.h"


#ifdef COMPILING_GOTHIC
#include "onpc.h"
#include "ogamemanager.h"
#include "oworld.h"
#include "ogame.h"
#include "ospawn.h"
#endif


CMainFrame* CMainFrame::mainframe		 = NULL;
zBOOL       g_bIsPlayingGame			 = FALSE;
zBOOL		g_bInsertNPCs				 = FALSE;
bool noWinPositionsFound = true;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()	
	ON_COMMAND(ID_SETTINGS_VIEW, OnSettingsView)	
	ON_COMMAND(ID_SETTINGS_GENERAL, OnSettingsGeneral)
	ON_COMMAND(ID_SAVE_SETTINGS, OnSaveSettings)
	ON_COMMAND(ID_LOAD_SETTINGS, OnLoadSettings)
	ON_COMMAND(ID_SAVE_MATFILTER, OnSaveMatfilter)
	ON_COMMAND(ID_LOAD_MATFILTER, OnLoadMatfilter)	
	ON_COMMAND(ID_EXTRACTTEXT, OnExtracttext)
	ON_UPDATE_COMMAND_UI(ID_EXTRACTTEXT, OnUpdateExtracttext)
	ON_COMMAND(ID_IMPORTTEXT, OnImporttext)
	ON_UPDATE_COMMAND_UI(ID_IMPORTTEXT, OnUpdateImporttext)
	ON_COMMAND(ID_CUTSCENESEQ, OnCutsceneseq)
	ON_UPDATE_COMMAND_UI(ID_CUTSCENESEQ, OnUpdateCutsceneseq)
	ON_UPDATE_COMMAND_UI(ID_DOAI, OnUpdateDoAI)
	ON_COMMAND(ID_PRESETSAVE, OnPresetsave)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONSOLE, OnUpdateViewConsole)		
	ON_COMMAND(ID_WINDOWS_ANBINDEN, OnWindowsFix)
	ON_UPDATE_COMMAND_UI(ID_WINDOWS_ANBINDEN, OnUpdateWindowsFix)		
	ON_WM_MOVE()
	ON_COMMAND(ID_WINDOWS_ALIGNRIGHT, OnWindowsAlignright)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_VIEWVOB_VOB_INITEVENTS, OnViewvobVobInitevents)
	ON_UPDATE_COMMAND_UI(ID_VIEWVOB_VOB_INITEVENTS, OnUpdateViewvobVobInitevents)
	ON_COMMAND(ID_OBJ_TEXTURE, OnObjTexture)
	ON_COMMAND(ID_OBJ_CUTSCENES, OnObjCutscenes)
	ON_COMMAND(ID_OBJ_LIGHT, OnObjLight)	
	ON_COMMAND(ID_OBJ_SOUND, OnObjSound)
	ON_COMMAND(ID_OBJ_SPECIAL, OnObjSpecial)
	ON_COMMAND(ID_OBJ_EVENT, OnObjEvent)
	ON_COMMAND(ID_OBJ_VOBS, OnObjVobs)
	ON_COMMAND(ID_OBJ_ZONE, OnObjZone)	
	ON_COMMAND(ID_OBJ_CAMERAS, OnObjCameras)
	ON_COMMAND(ID_OBJ_LOGICAL, OnObjLogical)
	ON_COMMAND(ID_OBJ_VERTEX, OnObjVertex)	
	ON_COMMAND(ID_VIEW_CONSOLE, OnViewConsole)
	ON_UPDATE_COMMAND_UI(ID_OBJ_SCRIPT, OnUpdateObjCutscenes)
	ON_UPDATE_COMMAND_UI(ID_OBJ_LIGHT, OnUpdateObjLight)
	ON_UPDATE_COMMAND_UI(ID_OBJ_SOUND, OnUpdateObjSound)
	ON_UPDATE_COMMAND_UI(ID_OBJ_SPECIAL, OnUpdateObjSpecial)
	ON_UPDATE_COMMAND_UI(ID_OBJ_TEXTURE, OnUpdateObjTexture)	
	ON_UPDATE_COMMAND_UI(ID_OBJ_EVENT, OnUpdateObjEvent)
	ON_UPDATE_COMMAND_UI(ID_OBJ_VOBS, OnUpdateObjVobs)
	ON_UPDATE_COMMAND_UI(ID_OBJ_ZONE, OnUpdateObjZone)
	ON_UPDATE_COMMAND_UI(ID_OBJ_CAMERAS, OnUpdateObjCameras)
	ON_UPDATE_COMMAND_UI(ID_OBJ_VERTEX, OnUpdateObjVertex)
	ON_UPDATE_COMMAND_UI(ID_OBJ_LOGICAL, OnUpdateObjLogical)
	ON_COMMAND(IDC_WORLD_STORE_VOBSTATES, OnWorldStoreVobstates)
	ON_COMMAND(IDC_WORLD_RESTORE_VOBSTATES, OnWorldRestoreVobstates)
	ON_UPDATE_COMMAND_UI(ID_CS_REGET, OnUpdateCsReget)
	ON_COMMAND(ID_VIEWEDIT_TOGGLETOOLS, OnVieweditToggletools)
	ON_UPDATE_COMMAND_UI(ID_VIEWEDIT_TOGGLETOOLS, OnUpdateVieweditToggletools)
	ON_COMMAND(ID_WINDOWS_ALIGNWINDOWSOUTSIDE, OnWindowsAlignwindowsoutside)
	ON_UPDATE_COMMAND_UI(ID_WINDOWS_ALIGNWINDOWSOUTSIDE, OnUpdateWindowsAlignwindowsoutside)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_WINDOWS_VOBCONTAINER, OnWindowsVobcontainer)
	ON_UPDATE_COMMAND_UI(ID_WINDOWS_VOBCONTAINER, OnUpdateWindowsVobcontainer)
	ON_COMMAND(ID_VIEWVOB_VOB_INSERTTOCONTAINER, OnViewvobVobInserttocontainer)
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_OBJ_CUTSCENES, OnUpdateObjCutscenes)	
	ON_COMMAND(ID_PLAY_GAME, OnPlayGame)
	ON_UPDATE_COMMAND_UI(ID_PLAY_GAME, OnUpdatePlayGame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const int size_x =  640;
const int size_y =  480;


static void Handle_UnhandledException()
{
	if (!CMainFrame::mainframe) return;

	// Allgemeine Settings speichern
	
	// Alle Material-Libs speichern
	if (AfxMessageBox("An error occured.\r\nShould all material-libs be saved?",MB_YESNO) == IDYES)
	{
		spcCMatFilter* item;
		for (int z=0; z<spcConfig.matFilterList.GetNumInList(); z++)
		{
			item = spcConfig.matFilterList[z];
			if (item) CMainFrame::mainframe->GetMaterialListWindow()->SaveMatlib(item->name);
		}	
	}
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: presetLib()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of CMainFrame...");

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	mainframe				= this;
	windowsAreOnTop			= true;

	winCutsceneSequencer	= 0;	
	winBar					= 0;
	winInfoBar				= 0;
	winInfoBar_Specials		= 0;
	winInfoBar_Lights		= 0;
	winInfoBar_Sounds		= 0;
	winInfoBar_Materials	= 0;
	winInfoBar_Camera		= 0;
	winInfoBar_Events		= 0;
	winInfoBar_Vobs			= 0;
	winInfoBar_Zones		= 0;
	winInfoBar_Logical		= 0;
	winInfoBar_Vertex		= 0;

	winID					= 0;
	winHelp					= 0;
	winMaterialList			= 0;
	winVobList				= 0;
	winCutsceneList			= 0;
	winObjectDlg			= 0;
	
	zERR_MESSAGE(7,zERR_END,"");
}

CMainFrame::~CMainFrame()
{		
	spcCInfoBar* info		= GetInfoBar();	
	zCWorld*	 world		= (info)  ? info->GetActiveWorld() : 0;
	zCCSPlayer*	 csplayer	= (world) ? world->GetCutscenePlayer() : 0;	
	
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing CMainFrame-Instance ...");		
	
	delete winCutsceneSequencer;	
	winCutsceneSequencer	= 0;
	
	delete winVobContainer;
	winVobContainer=0;

	if (csplayer) csplayer->deb	= 0;
	mainframe				= 0;	

	zERR_MESSAGE(7,zERR_END,"");	
}

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_STATUSPANE_PICKVOB,
	ID_STATUSPANE_COPYVOB,
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

void CMainFrame::InitWindows()
{		
	if (zoptions->Parm("CRASHHANDLER")) zexhnd.AddUnhandledExceptionReleaseCallback ( Handle_UnhandledException ); 


	// [EDENFELD] 1.33 Window wird zu Programmstart gehidet (vom MOD-SOURCE)
	ShowWindow(SW_HIDE);

	//////////////////////////////////////////////
	// DIALOGBAR InfoBar and its Dialogs
	//////////////////////////////////////////////

	if (workingDlg) workingDlg->AddMessage("Initializing toolbars");	

	EnableDocking(CBRS_ALIGN_ANY);

	if (!m_wndObjectToolbar.Create(
					this, 
					WS_DLGFRAME | WS_CHILD | WS_VISIBLE | 
					//CBRS_SIZE_FIXED | 						
					CBRS_FLYBY | CBRS_TOOLTIPS)
		)	{ TRACE0("Failed to create object-toolbar\n"); return; }		
	
	m_wndObjectToolbar.LoadToolBar(IDR_OBJECTS);				
	
	if (!m_wndActionToolbar.Create(
					this, 
					WS_DLGFRAME | WS_CHILD | WS_VISIBLE | 
					//CBRS_SIZE_FIXED |						
					CBRS_FLYBY | CBRS_TOOLTIPS)
		) { TRACE0("Failed to create action-toolbar\n"); return; }	
	
	m_wndActionToolbar.LoadToolBar(IDR_OBJECTACTIONS);			

	POSITION id;
	spcTRegWindowInfo winInfo;

	id = spcConfig.GetWindowID("winToolbarObjects");		
	spcConfig.GetWindowPosition(id,winInfo);
	m_wndObjectToolbar.EnableDocking(0);	
	FloatControlBar( &m_wndObjectToolbar, CPoint(winInfo.position.pos.x, winInfo.position.pos.y),CBRS_ALIGN_TOP);	

	id = spcConfig.GetWindowID("winToolbarAction");	
	spcConfig.GetWindowPosition(id,winInfo);		
	m_wndActionToolbar.EnableDocking(0);		
	FloatControlBar( &m_wndActionToolbar, CPoint(winInfo.position.pos.x, winInfo.position.pos.y),CBRS_ALIGN_RIGHT);

	m_wndObjectToolbar.GetDockingFrame()->SetWindowText("Object-Toolbar");
	m_wndObjectToolbar.GetDockingFrame()->ModifyStyle(WS_CAPTION | WS_SYSMENU,0);	
	m_wndObjectToolbar.GetDockingFrame()->RecalcLayout(TRUE);
	
	m_wndActionToolbar.GetDockingFrame()->SetWindowText("Action-Toolbar");	
	m_wndActionToolbar.GetDockingFrame()->ModifyStyle(WS_CAPTION | WS_SYSMENU,0);				
	m_wndActionToolbar.GetDockingFrame()->RecalcLayout(TRUE);


	if (workingDlg) workingDlg->AddMessage("Initializing windows");	

	// Feste Fenster
	winBar = new spcCObjectBar();
	winBar->Create(IDD_INFO_EMPTY, 0);	
	winBar->ShowWindow(SW_SHOW);
	
	winInfoBar				= new spcCInfoBar();
	winInfoBar				->Create(IDD_INFO_DEFAULT, winBar);
	winInfoBar_Specials		= new spcCInfoBar_Specials();
	winInfoBar_Specials		->Create(IDD_INFO_SPECIALS, winBar);
	winInfoBar_Materials	= new spcCInfoBar_Materials();
	winInfoBar_Materials	->Create(IDD_INFO_MATERIALS, winBar);
	winInfoBar_Lights		= new spcCInfoBar_Lights();
	winInfoBar_Lights		->Create(IDD_INFO_LIGHT, winBar);
	winInfoBar_Sounds		= new spcCInfoBar_Sounds();
	winInfoBar_Sounds		->Create(IDD_INFO_SOUNDS, winBar);
	winInfoBar_Logical		= new spcCVobLogicalDialog();
	winInfoBar_Logical		->Create(IDD_INFO_LOGICAL, winBar);
	winInfoBar_Camera		= new spcCInfoBar_Camera();
	winInfoBar_Camera		->Create(IDD_INFO_CAMERA, winBar);
	winInfoBar_Events		= new spcCInfoBar_Events();
	winInfoBar_Events		->Create(IDD_INFO_EVENTS, winBar);
	winInfoBar_Zones		= new spcCInfoBar_VobsPlus();	
	winInfoBar_Zones		->Create(IDD_INFO_VOBSPLUS, winBar);
	winInfoBar_Vertex		= new spcCInfoBar_Vertex();	
	winInfoBar_Vertex		->Create(IDD_INFO_VERTEX, winBar);
	winInfoBar_Vobs			= new spcCInfoBar_Vobs();
	winInfoBar_Vobs			->Create(IDD_INFO_VOBS, winBar);

	winInfoBar->SetSession(CSpacerDoc::session);	
	
	//////////////////////////////////////////////
	// Presetlibrary / classdescriptions
	//////////////////////////////////////////////
	
	if (workingDlg) workingDlg->AddMessage("Initializing class-informations");
	spcCClassInfo::Init();

	if (workingDlg) workingDlg->AddMessage("Loading presets");
	presetLib.Load();

	/*
	//////////////////////////////////////////////
	// besser ein neues SoundObject anlegen
	//////////////////////////////////////////////
	
	if (workingDlg) workingDlg->AddMessage("Initializing the sound-system");
	
	if (zsound) delete zsound;	
	
	if (zoptions->Parm("ZNOSOUND"))	
	{
			zsound= new zCSoundSystemDummy();
	}
	else
	{
		zsound = new zCSndSys_MSS();
	}
	*/
		
	// Groesse des Hauptfensters

	bool knowsPosition = spcConfig.KnowsWindowPosition("winMain");
	
	RECT defRect;
	defRect.left	= defRect.top	= 0;
	defRect.right	= size_x;
	defRect.bottom	= size_y;	
	
	winID = spcConfig.GetWindowID("winMain",&defRect);	
	spcConfig.GetWindowPosition(winID,winInfo);

	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,
		winInfo.position.size.cx,
		winInfo.position.size.cy,
		TRUE);
		
	if (workingDlg) workingDlg->AddMessage("Creating floating windows");
	
	spcCWindowResizeStyle* style;

	style		= new spcCWindowResizeStyle;
	style		->Init(winBar,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, false);
	childResizeList.AddTail(style);	

	if (m_wndObjectToolbar.IsFloating())
	{
		style	= new spcCWindowResizeStyle;
		style	->Init(m_wndObjectToolbar.GetDockingFrame(),this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, false);
		childResizeList.AddTail(style);	
	}

	if (m_wndActionToolbar.IsFloating())
	{	
		style	= new spcCWindowResizeStyle;
		style	->Init(m_wndActionToolbar.GetDockingFrame(),this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, false);
		childResizeList.AddTail(style);	
	}

	if (workingDlg) workingDlg->AddMessage("-Info ...");	
	
	winHelp			= new spcCHelpDlg();
	style			= new spcCWindowResizeStyle;
	winHelp			->Create		(IDD_HELP_DLG, this);	
	winHelp			->ShowWindow	(SW_SHOW);
	style			->Init			(winHelp,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, false);
	childResizeList.AddTail			(style);

	if (workingDlg) workingDlg->AddMessage("-MaterialList ...");
	
	winMaterialList = new spcCListMaterialDlg();
	style			= new spcCWindowResizeStyle;
	winMaterialList	->Create		(IDD_LIST_MATS, this);
	winMaterialList	->ShowWindow	(SW_HIDE);	
	style			->Init			(winMaterialList,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, false);
	childResizeList.AddTail			(style);	

	if (workingDlg) workingDlg->AddMessage("-CutsceneList ...");	

	winCutsceneList = new spcCListCutsceneDlg();
	style			= new spcCWindowResizeStyle;
	winCutsceneList	->Create		(IDD_LIST_OUS, this);	
	winCutsceneList	->ShowWindow	(SW_HIDE);	
	style			->Init			(winCutsceneList,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, false);
	childResizeList.AddTail			(style);

	if (workingDlg) workingDlg->AddMessage("-VobList ...");	

	winVobList		= new spcCListVobDlg();
	style			= new spcCWindowResizeStyle;
	winVobList		->Create		(IDD_LIST_VOBS, this);
	winVobList		->ShowWindow	(SW_HIDE);		
	style			->Init			(winVobList,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, false);
	childResizeList.AddTail			(style);

	if (workingDlg) workingDlg->AddMessage("-ObjectDlg ...");	
	
	winObjectDlg	= new spcCObjectSheet();
	style			= new spcCWindowResizeStyle;
	winObjectDlg	->Init			("Objects",this);
	winObjectDlg	->ShowWindow	(SW_HIDE);	
	style			->Init			(winObjectDlg,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, false);
	childResizeList.AddTail			(style);

	if (workingDlg) workingDlg->AddMessage("-Cutscene-Sequencer ...");	
	
	winCutsceneSequencer	= new spcCCSSequencer();
	winCutsceneSequencer	->Create	(IDD_CS_SEQUENCER,this);
	winCutsceneSequencer	->ShowWindow(SW_HIDE);	

	if (workingDlg) workingDlg->AddMessage("-Vob-Container ...");	

	winVobContainer			= new spcCVobContainer();
	winVobContainer			->Create(IDD_VOB_CONTAINER, this);
	winVobContainer			->ShowWindow(SW_HIDE);	


	// csplayer->deb			= winCutsceneSequencer;
	style					->Init		(winCutsceneSequencer,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, false);
	childResizeList.AddTail(style);				

	if (!knowsPosition)
	{
		OnWindowsAlignright();
		OnWindowsFix();		
	};

	SetWorkMode(MODE_NONE);

	// Iitialisierung der Fenster
	if (workingDlg) workingDlg->AddMessage("Init dialogs: InfoBar-Contants");

	winInfoBar_Vobs->AddPresetClass(zSTRING("zCVob"),true);
	winInfoBar_Vobs->AddPresetClass(zSTRING("zCEffect"),true);
	winInfoBar_Vobs->AddPresetClass(zSTRING("oCMOB"),true);
	winInfoBar_Vertex->InitData();
	if (parseinfo) parseinfo->GetNameList(CLASS_SOUNDS,&winInfoBar_Sounds->ctrl_voblist);			
	
	if (zoptions->Parm("nospacercfg")) 
	{
		OnWindowsAlignright();
	}

	// [EDENFELD] 1.33 Output Unit Window anzeigen (vom MOD-SOURCE)
	OnObjCutscenes();

	if (workingDlg) workingDlg->AddMessage("Mainframe initialized");	

	// [EDENFELD] 1.33 Window wird nach Programmstart wieder angezeigt (vom MOD-SOURCE)
	ShowWindow(SW_SHOW);
};



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;		
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{				
	cs.x = 0;
	cs.y = 0;
	cs.cx = size_x;
	cs.cy = size_y;	
	cs.style		&= (~WS_SYSMENU & ~WS_THICKFRAME);  // Loeschen von StyleFlags
	cs.dwExStyle	|= WS_EX_NOPARENTNOTIFY;			// Setzen von ExStyleFlags
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// WINDOW: SIZING ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void CMainFrame::SetWorkMode(TWorkMode mode)
{
	windowsAreOnTop = true;

	ShowToolWindow(winBar);
	ShowToolWindow(winHelp);
	m_wndObjectToolbar.GetDockingFrame()->ShowWindow(SW_SHOW);
	m_wndActionToolbar.GetDockingFrame()->ShowWindow(SW_SHOW);


	workmode = mode;	
	// check which BrowseBar to show (right dialogbar)
				
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	if (workmode == MODE_CUTSCENE)
	{		
		HideToolWindow(winVobList);
		HideToolWindow(winMaterialList);
		ShowToolWindow(winCutsceneList);

		ShowToolWindow(winObjectDlg);
		winObjectDlg	->SetBaseClass("zCEventMessage");
		
		CSpacerView::view->PolyHideSelection(false);
	}
	else if (!world || !world->IsCompiled() || world->IsCompiledEditorMode())	
	{	
		HideToolWindow(winCutsceneList);
		HideToolWindow(winVobList);
		ShowToolWindow(winMaterialList);

		ShowToolWindow(winObjectDlg);
		winObjectDlg	->SetBaseClass("zCMaterial");
		
		CSpacerView::view->PolyHideSelection(false);
	}
	else if (world && world->IsCompiled())
	{
		HideToolWindow(winCutsceneList);
		HideToolWindow(winMaterialList);
		ShowToolWindow(winVobList);

		ShowToolWindow(winObjectDlg);
		if (mode==MODE_CUTSCENE) winObjectDlg->SetBaseClass("zCEventMessage");
		else winObjectDlg	->SetBaseClass("zCVob");
		
		CSpacerView::view->PolyHideSelection(false);
	}
	else
	{
		HideToolWindow(winMaterialList);
		HideToolWindow(winCutsceneList);
		HideToolWindow(winVobList);
		ShowToolWindow(winObjectDlg);
	}

	// Modi ermitteln, in denen keine Vobs ueber die VobCreationPage erzeugt werden sollen
	switch (workmode)
	{
	case MODE_MATERIAL:
	case MODE_LIGHT:	
	case MODE_SOUND:
	case MODE_CAMERA:		
	case MODE_SPECIAL:
	case MODE_ZONE:
	case MODE_VOBS:
	case MODE_VERTEX:
		winObjectDlg->DisableCreationPage(true);
		break;
	case MODE_CUTSCENE:	
	case MODE_LOGICAL:	
		winObjectDlg->DisableCreationPage(false);
		break;
	default: 
		winObjectDlg->DisableCreationPage(false);

	};

	winInfoBar_Materials->ShowWindow(SW_HIDE);
	winInfoBar_Lights	->ShowWindow(SW_HIDE);
	winInfoBar_Sounds	->ShowWindow(SW_HIDE);
	winInfoBar_Camera	->ShowWindow(SW_HIDE);
	winInfoBar_Vobs		->ShowWindow(SW_HIDE);
	winInfoBar_Specials	->ShowWindow(SW_HIDE);	
	winInfoBar_Events	->ShowWindow(SW_HIDE);
	winInfoBar_Zones	->ShowWindow(SW_HIDE);	
	winInfoBar_Logical	->ShowWindow(SW_HIDE);
	winInfoBar_Vertex	->ShowWindow(SW_HIDE);

	// Default-InfoBar anzeigen?
	switch (workmode)
	{
		case MODE_NONE:		// NONE-Mode
		case MODE_CUTSCENE:	// CUTSCENE-Mode
		case MODE_PROPS:	// PROPERTY-Mode
			// JA:
			winInfoBar->ShowWindow(SW_SHOW); 			
			break;
		default:
			// NEIN:
			winInfoBar->ShowWindow(SW_HIDE);
			// Welche Seite anzeigen:
			switch (workmode)
			{
					case MODE_MATERIAL: winInfoBar_Materials->ShowWindow(SW_SHOW);break;
					case MODE_LIGHT:	winInfoBar_Lights	->ShowWindow(SW_SHOW);break;
					case MODE_SOUND:	winInfoBar_Sounds	->ShowWindow(SW_SHOW);break;
					case MODE_CAMERA:	winInfoBar_Camera	->ShowWindow(SW_SHOW);break;
					case MODE_VOBS:		winInfoBar_Vobs		->ShowWindow(SW_SHOW);break;
					case MODE_SPECIAL:	winInfoBar_Specials	->ShowWindow(SW_SHOW);break;
					case MODE_EVENT:	winInfoBar_Events	->ShowWindow(SW_SHOW);break;
					case MODE_ZONE:		winInfoBar_Zones	->ShowWindow(SW_SHOW);break;
					case MODE_LOGICAL:	winInfoBar_Logical	->ShowWindow(SW_SHOW);break;
					case MODE_VERTEX:	winInfoBar_Vertex	->ShowWindow(SW_SHOW);break;
			}
			
	}
		
	// Entsprechende Toolbar laden	
	switch (workmode)
	{	
		case MODE_MATERIAL:	
			m_wndActionToolbar.LoadToolBar(IDR_MATERIALACTIONS);	
			break;
		default:
			m_wndActionToolbar.LoadToolBar(IDR_OBJECTACTIONS);						
	}	
}

void CMainFrame::OnObjStandardMode()
{
	SetWorkMode(MODE_NONE);
};

void CMainFrame::OnObjLight()	
{ 
	if (workmode != MODE_LIGHT) SetWorkMode(MODE_LIGHT);
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjSound()	
{ 
	if (workmode != MODE_SOUND) SetWorkMode(MODE_SOUND);
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjSpecial()	
{ 
	if (workmode != MODE_SPECIAL) SetWorkMode(MODE_SPECIAL);	
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjEvent()	
{ 
	if (workmode != MODE_EVENT) SetWorkMode(MODE_EVENT);	
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjVobs()	
{ 
	if (workmode != MODE_VOBS) SetWorkMode(MODE_VOBS);		
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjZone()	
{ 
	if (workmode != MODE_ZONE) SetWorkMode(MODE_ZONE);		
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjCameras() 
{ 
	if (workmode != MODE_CAMERA) SetWorkMode(MODE_CAMERA);			
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjLogical() 
{ 
	if (workmode != MODE_LOGICAL) SetWorkMode(MODE_LOGICAL);		
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjVertex()	
{ 	
	if (workmode != MODE_VERTEX) SetWorkMode(MODE_VERTEX);			
	else SetWorkMode(MODE_NONE);
}

void CMainFrame::OnObjCutscenes()	
{ 	
	if (workmode != MODE_CUTSCENE) SetWorkMode(MODE_CUTSCENE);	
	else SetWorkMode(MODE_NONE);
}
void CMainFrame::OnObjTexture()	
{ 	
	if (workmode != MODE_MATERIAL) SetWorkMode(MODE_MATERIAL);
	else SetWorkMode(MODE_NONE);
}



void CMainFrame::OnSettingsView() 
{

	BOOL resize = FALSE;
	BOOL reset = FALSE;

	spcCSetView dlg;
	// set dialog-data
	dlg.m_view_x		= spcConfig.view_x;
	dlg.m_view_y		= spcConfig.view_y;
	dlg.m_view_bpp		= spcConfig.view_bpp;
	// dlg.m_farclip    	= spcConfig.farclipping * 32000;

	// show dialog
	if (dlg.DoModal()==IDOK)
	{
		// check what changed
		if (spcConfig.view_x != dlg.m_view_x || 
			spcConfig.view_y != dlg.m_view_y
			)
			resize=TRUE;

		// query settings from dialog
		spcConfig.view_x	= dlg.m_view_x;
		spcConfig.view_y	= dlg.m_view_y;
		spcConfig.view_bpp	= dlg.m_view_bpp;
		
		// reinit view
		if (resize) 
			CSpacerView::view->ResizeViewport();

		if (reset)  
			CSpacerView::view->InitSettings();		
	}	
//#endif
}

void CMainFrame::OnSettingsGeneral() 
{	
	BOOL reset = FALSE;

	spcCSetGeneral dlg;

	dlg.SetMovespeed(spcConfig.movespeed);

	dlg.m_use_grid		= spcConfig.useGrid;
	dlg.m_move_grid		= spcConfig.moveGrid;
	dlg.m_rot_grid		= spcConfig.rotGrid;
	dlg.m_tex_use_grid	= spcConfig.useGridTex;
	dlg.m_tex_move_grid	= spcConfig.moveGridTex;
	dlg.m_tex_rot_grid	= spcConfig.rotGridTex;
	dlg.m_goldmaster	= spcConfig.goldmastering;

	dlg.m_interative_save = spcConfig.interativeSave;

	// show dialog
	if (dlg.DoModal()==IDOK)
	{
		if (
			
			spcConfig.movespeed	!= dlg.GetMovespeed()		|| 
			spcConfig.useGrid	!= dlg.m_use_grid			|| 
			spcConfig.moveGrid	!= dlg.m_move_grid			|| 
			spcConfig.rotGrid	!= dlg.m_rot_grid			|| 
			spcConfig.useGridTex!= dlg.m_tex_use_grid		|| 			
			spcConfig.rotGridTex!= dlg.m_tex_rot_grid		||
			spcConfig.moveGridTex	!= dlg.m_tex_move_grid	|| 
			spcConfig.interativeSave!= dlg.m_interative_save			

			) reset=TRUE;
		
		// query settings from dialog

		spcConfig.interativeSave= dlg.m_interative_save;
		spcConfig.movespeed		= dlg.GetMovespeed();
		spcConfig.useGrid		= dlg.m_use_grid;
		spcConfig.moveGrid		= dlg.m_move_grid;
		spcConfig.rotGrid		= dlg.m_rot_grid;
		spcConfig.useGridTex	= dlg.m_tex_use_grid;
		spcConfig.moveGridTex	= dlg.m_tex_move_grid;
		spcConfig.rotGridTex	= dlg.m_tex_rot_grid;
		spcConfig.goldmastering	= dlg.m_goldmaster ? true : false;
		
		CSpacerDoc::doc->UpdateWindowTitle();

		// reinit view		
		if (reset)  CSpacerView::view->InitSettings();

	}	

}
void CMainFrame::DeactivateCS()
{	
	HideToolWindow(winCutsceneSequencer);
}
bool CMainFrame::ActivateCutsceneSeq()
{	
	if (winCutsceneSequencer->IsWindowVisible())
	{
		HideToolWindow(winCutsceneSequencer);
	}
	else
	{
		ShowToolWindow(winCutsceneSequencer);
	}	
	return true;
}

void CMainFrame::CSSetOU(zCCSBlockBase* ou)
{
	if (winCutsceneSequencer)
	{
		zCCutscene* cs = dynamic_cast<zCCutscene*>(ou);
		if (cs) winCutsceneSequencer->AssignOutputUnit(cs);
	}
}
void CMainFrame::CSUpdate()
{
	winCutsceneList->UpdateSelected();
}
void CMainFrame::CSAssignParameter(zSTRING & p)
{
	if (winCutsceneSequencer)
		winCutsceneSequencer->AssignParameter(p);
}
void CMainFrame::CSAssignIntegratedRole(zCVob* irole)
{
	if (winCutsceneSequencer && irole)
	{
		// irole->AddRef();		
		
		bool removed = false;
		CSpacerDoc::doc->VobHandleBeforeSave(irole);
		if (winCutsceneSequencer->AssignIntegratedRole(irole))
		{			
			removed = CSpacerDoc::doc->RemoveVob(irole);						
		}		
		if (!removed) CSpacerDoc::doc->VobHandleAfterSave(irole);
	}
}

zCVob* CMainFrame::CSRegetIntegratedRole()
{
	if (winCutsceneSequencer)
	{
		zCVob* vob = winCutsceneSequencer->RegetIntegratedRole();
		return vob;
	};
	
	return 0;
};

void CMainFrame::OnUpdateCsReget(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(winCutsceneSequencer && winCutsceneSequencer->IsWindowVisible());	
}

void CMainFrame::PrepareForSave()
{	

}

void CMainFrame::AfterSave()
{
	winInfoBar_Events	->InitData();
	winInfoBar_Vobs		->InitData();
	winInfoBar_Zones	->InitData();
}


//////////////////////////////////////////////////
// OnUpdate-Routines
//////////////////////////////////////////////////

zCVob* CMainFrame::CreateNewVob()
{
	zCWorld* world = CSpacerDoc::doc->GetWorld();
	zCVob* newvob = 0;
	switch (workmode)
	{
		case MODE_SPECIAL:	newvob = winInfoBar_Specials->CreateNewVob();break;
		case MODE_SOUND:	newvob = winInfoBar_Sounds->CreateNewVob();break;			
		case MODE_LIGHT:	newvob = winInfoBar_Lights->CreateNewVob();break;
		case MODE_VOBS:		newvob = winInfoBar_Vobs->CreateNewVob();break;
		case MODE_CAMERA:	return 0;
		default:
			CString name;
			if (winObjectDlg->CreateNewObjectCheck(name))
			{
				newvob = dynamic_cast<zCVob*>(winObjectDlg->CreateNewObject()); 
				
				#ifdef COMPILING_GOTHIC
					oCNpc* npc = dynamic_cast<oCNpc*>(newvob); 				
					if (npc) npc->UseStandAI();					
				#endif

			}						
	}	

	// Vobname ist Pflicht
	if (
		dynamic_cast<zCMover*>(newvob)			||
		dynamic_cast<zCVobWaypoint*>(newvob)	||
		dynamic_cast<zCVobSpot*>(newvob)
		)
	{
		spcCInputDialog dlg;
		dlg.m_text = "This vob of type "+CString(newvob->GetClassName_().ToChar())+"\r\nmust have a VobName:";
		dlg.SetInput("");		

		zBOOL	ready	= false;
		zSTRING	name	= "";
		int		result	= 0;
		while (!ready)
		{
			result = dlg.DoModal();
			if (result == IDOK)
			{			
				zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);
				name = dlg.GetUpperInput().GetBuffer(0);
				ready= !name.IsEmpty() && arch->IsStringValid(name.ToChar());
				arch->Close();zRELEASE(arch);

				if (!dynamic_cast<zCMover*>(newvob))
				{
					zCVob* vob = world->SearchVobByName(name);
					ready = ready && !vob;				
				}				
			} 
			else 
			{
				ready = true;
				name.Clear();
			}
		}				

		if (!name.IsEmpty()) 
		{
			newvob->SetVobName(name);
		}
		else 
		{
			zRELEASE(newvob);
		}
	};
	
	return newvob;
};
zCVob* CMainFrame::InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob)
{	
	zCVob* newvob = NULL;

	CString name;
	
	switch (workmode)
	{				
		case MODE_CAMERA:	newvob = winInfoBar_Camera->InsertVob(pos,dir,vob);		break;		
	};	
	
	// if (newvob) HandleVobInsert(newvob,vob);

	return newvob;
}


/*
zCVob* CMainFrame::InsertMarker(const zPOINT3& pos, zCVob* vob)
{
	bool m_marker_old = (0!=winInfoBar_Specials->m_marker);
	winInfoBar_Specials->m_marker = true;   // aktivate -set marker-
	winInfoBar_Specials->m_posx = pos[0];   // fill dlg with data
	winInfoBar_Specials->m_posy = pos[1];
	winInfoBar_Specials->m_posz = pos[2];
	winInfoBar_Specials->UpdateData(FALSE);  // update it to dlg

	zCVob* newvob = winInfoBar_Specials->InsertVob(pos,pos,vob);
	winInfoBar_Specials->m_marker = m_marker_old;  // restore - set marker-
	winInfoBar_Specials->UpdateData(FALSE);       // update

	if (newvob)	winVobList->VobInsert(newvob, vob);
	return newvob;
}
*/

CString	CMainFrame::GetVobTypeName()
{
	if (workmode == MODE_LIGHT)
	{
		return "light";
	}
	else if (workmode == MODE_CAMERA)
	{
		return "camera/keyframe";
	}
	else if (workmode == MODE_SPECIAL)
	{
		return "specials";
	}
	else if (workmode == MODE_VOBS)
	{
		return "vob";
	}
	else if (winObjectDlg) 
	{
		CString name;
		winObjectDlg->CreateNewObjectCheck(name);
		zSTRING classname(name.GetBuffer(0));		
		zBOOL result = ("zCVob"==classname) || zCObject::CheckInheritance("zCVob",classname);
		if (result) return name;	
	}
	
	return "";
	/*
	switch(workmode)
	{
		case MODE_LIGHT:	return "light"; break;
		case MODE_SOUND:	return "sound"; break;
		case MODE_SPECIAL:	return "special"; break;
		case MODE_EVENT:	return "trigger"; break;
		case MODE_PROPS:	return "object"; break;
		case MODE_VOBS:		return "vob"; break;
		case MODE_CAMERA:	return "camera/keyframe"; break;
		default:			return ""; break;
	}
	*/
}


void CMainFrame::VobCopy(zCVob* vob)
{
	/*
	int index = m_wndStatusBar.CommandToIndex(ID_STATUSPANE_COPYVOB);
	if (index>=0) 
	{
		if (!vob) m_wndStatusBar.SetPaneText(index,"none copied");
		else      m_wndStatusBar.SetPaneText(index,"C:"+CString(vob->GetVobName().ToChar()));
	}
	*/	
};


zCMaterial* CMainFrame::GetMaterial()
{
	return winInfoBar_Materials->GetMaterial();
}

void CMainFrame::GetMaterialMapping(float& x, float& y)
{
	winInfoBar_Materials->GetMaterialMapping(x,y);
}

void CMainFrame::UpdateMatFilterList()
{
	winInfoBar_Materials->UpdateFilterList();
	winMaterialList->InitData();
}

void CMainFrame::UpdateVobList(zCWorld* world) 
{
	winVobList->BuildTree(world); 
};	


void CMainFrame::OnSaveSettings() 
{		
	// [EDENFELD] 1.33 vom ModSource. Speichern der Settings in illegalen Zuständen vermeiden
	if (!IsWindowEnabled() || !IsWindowVisible()) 
	{
		zERR_WARNING("B: SPC: Can't save setting of invisible or disabled spacer");
		return;
	}
	
	// Toolbar-Positionen holen	
	POSITION id;
	spcTRegWindowInfo winInfo;
	RECT rect;

	id = spcConfig.GetWindowID("winToolbarObjects");					
	m_wndObjectToolbar.GetDockingFrame()->GetWindowRect(&rect);
	spcConfig.SetWindowPosition(id,rect);

	id = spcConfig.GetWindowID("winToolbarAction");				
	m_wndActionToolbar.GetDockingFrame()->GetWindowRect(&rect);
	spcConfig.SetWindowPosition(id,rect);

	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Saving settings ..");
	spcConfig.Save();
	
	presetLib.SetDirty();
	presetLib.Save();
	zCVobLight::SaveLightPresets();
	zERR_MESSAGE(4,zERR_END,"");
}

void CMainFrame::OnLoadSettings() 
{
	zoptions->ChangeDir(DIR_DATA);
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"Extensionless file (*.*)|*.*||");

	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{
		if (MessageBox("You really want to replace your settings?",
			           "Replace settings",MB_YESNO)==IDNO) return;
		
		CString name = dlg.GetPathName();
		spcConfig.Load(name);
		playerLightInt = spcConfig.camlight;
		UpdateMaterialList();
		CSpacerView::view->InitViewport();
	}
}

void CMainFrame::UpdateMaterialList(const zSTRING& filterName)
{
	winMaterialList->UpdateMaterialList(filterName);	
}

void CMainFrame::UpdateWindowContents(zCWorld * world)
{
	zERR_MESSAGE(6,0,"B: SPC: Mainframe: UpdateWindowContents");

	UpdateWorkMode();
	
	zERR_MESSAGE(6,0,"B: SPC: Mainframe: Showpanel");
	UpdateChildWindows(NULL);

	zERR_MESSAGE(6,0,"B: SPC: Mainframe: Buildtree");
	winVobList->BuildTree(world);
	
	zERR_MESSAGE(6,0,"B: SPC: Mainframe: Updating Materiallist");
	UpdateMaterialList();

	/// Infobars
	zERR_MESSAGE(6,0,"B: SPC: Mainframe: Initializing Infobars");		
	zERR_MESSAGE(8,0,"B: SPC: Mainframe: ...Events");	winInfoBar_Events->InitData();	
	zERR_MESSAGE(8,0,"B: SPC: Mainframe: ...Vobs");		winInfoBar_Vobs->InitData();
	zERR_MESSAGE(8,0,"B: SPC: Mainframe: ...Zones");	winInfoBar_Zones->InitData();
	zERR_MESSAGE(8,0,"B: SPC: Mainframe: ...Cutscenes");winInfoBar_Camera->InitData();		
}

void CMainFrame::OnSaveMatfilter() 
{
	// [EDENFELD] 1.33 vom ModSource. Speichern der Settings 
	if (IsWindowEnabled() && IsWindowVisible()) 
	{
		spcConfig.Save();		
	}	
	
	zoptions->ChangeDir(DIR_TOOLS_DATA);

	spcConfig.Save();

	spcCMatFilter* item;
	int result = AfxMessageBox("Save all materialfilters?", MB_YESNO);
	if (result==IDYES)
	{	
		for (int z=0; z<spcConfig.matFilterList.GetNumInList(); z++)
		{
			item = spcConfig.matFilterList[z];
			if (item) winMaterialList->SaveMatlib(item->name);			
		}	
	}
	else
	{		
		for (int z=0; z<spcConfig.matFilterList.GetNumInList(); z++)
		{
			item = spcConfig.matFilterList[z];
			if (item && item->IsDirty())
			{
				int result = AfxMessageBox("Save changed materialfilter \""+item->name+"\" ?", MB_YESNO);
				if (result == IDYES)
				{
					winMaterialList->SaveMatlib(item->name);
				};
			};
		}	
	}	
}

void CMainFrame::OnLoadMatfilter() 
{
	zoptions->ChangeDir(DIR_TOOLS_DATA);
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"Extensionless file (*.*)|*.*||");

	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{
		CString name = dlg.GetFileTitle();
		// load a filter from lib but first create a new FilterItem

		spcCMatFilter* item=0;
		int index = spcConfig.FindMatFilterIndexByName(name);
		
		if (index>=0) item = spcConfig.matFilterList.GetSafe(index);
		if (!item) 
		{
			item = new spcCMatFilter;
			item->Init(name);
			spcConfig.matFilterList.Insert(item);
		}		
		winMaterialList->LoadMatlib(name,true);
		UpdateMatFilterList();
		UpdateMaterialList();
	}	
}
void CMainFrame::OnExtracttext() 
{
	winCutsceneList->Extracttext();
}

void CMainFrame::OnUpdateExtracttext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(winCutsceneList->m_language == 0);	
}

void CMainFrame::OnUpdateImporttext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(winCutsceneList->m_language != 0);	
}

void CMainFrame::OnCutsceneseq() 
{
	ActivateCutsceneSeq();
}

void CMainFrame::OnUpdateDoAI(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(true);
}

void CMainFrame::OnPresetsave() 
{
	presetLib.SetDirty();
	presetLib.Save();
}

int CMainFrame::GetVertexMoveSpeed()
{
	winInfoBar_Vertex->UpdateData();
	return winInfoBar_Vertex->m_mv_speed;
}

void CMainFrame::OnViewConsole() 
{
	spcCConsoleDialog dlg;
	dlg.DoModal();
	// zcon.Toggle();	
}

void CMainFrame::OnUpdateViewConsole(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(zcon.IsVisible());
}


void CMainFrame::Reset()
{
	zERR_MESSAGE(4,0,"B: SPC: Mainframe-Reset");	
		
	if (winCutsceneSequencer->IsWindowVisible())
	{
		ActivateCutsceneSeq();
	};

	if (workmode==MODE_CUTSCENE)
	{
		OnObjCutscenes();
	};
	
	

	UpdateChildWindows		(NULL,false);		
	winMaterialList			->Reset();	
	winVobList				->Reset();	
	winCutsceneSequencer	->Reset();		
};


void CMainFrame::OnClose() 
{
	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/
	
	if (MessageBox("Do you really wanna leave the spacer?", "Leaving Spacer",MB_YESNO)==IDYES)
	{	
		if (::g_bIsPlayingGame) 
		{
			gameMan->ExitGame();
		}

		OnSaveSettings();

		Reset();

		// vor dem Schliessen der Fenster.
		winMaterialList			->PreExit();		
		winInfoBar_Zones		->PreClose();
		winInfoBar_Events		->PreClose();

		// Presets speichern		
		presetLib.Dispose();		
		zCVobLight::SaveLightPresets();

		// Fenster verbergen und schliessen

		HideToolWindow(winMaterialList);
		HideToolWindow(winCutsceneList);
		HideToolWindow(winVobList);
		HideToolWindow(winObjectDlg);
		HideToolWindow(winCutsceneSequencer);

		// ... Propertypages
		CloseChildWindow(winInfoBar);			winInfoBar = 0;
		CloseChildWindow(winInfoBar_Specials);	winInfoBar_Specials = 0;
		CloseChildWindow(winInfoBar_Materials);	winInfoBar_Materials = 0;
		CloseChildWindow(winInfoBar_Lights);	winInfoBar_Lights = 0;
		CloseChildWindow(winInfoBar_Sounds);	winInfoBar_Sounds = 0;
		CloseChildWindow(winInfoBar_Logical);	winInfoBar_Logical = 0;
		CloseChildWindow(winInfoBar_Camera);	winInfoBar_Camera = 0;
		CloseChildWindow(winInfoBar_Events);	winInfoBar_Events = 0;
		CloseChildWindow(winInfoBar_Vobs);		winInfoBar_Vobs = 0;
		CloseChildWindow(winInfoBar_Zones);		winInfoBar_Zones = 0;
		CloseChildWindow(winInfoBar_Vertex);	winInfoBar_Vertex = 0;
		
		// ... Lists
		zERR_MESSAGE(7,0,"B: SPC: Closing Materiallist ... ");
		CloseChildWindow(winMaterialList);
		zERR_MESSAGE(7,0,"B: SPC: Closing VobList ... ");
		CloseChildWindow(winVobList);
		zERR_MESSAGE(7,0,"B: SPC: Closing CutsceneList ... ");
		CloseChildWindow(winCutsceneList);
		zERR_MESSAGE(7,0,"B: SPC: Closing ObjectDialog ... ");
		CloseChildWindow(winObjectDlg);
		
		// ... Bar
		winBar->CloseWindow();
		delete winBar;
		winBar=0;
			
		// ... Toolbars
		m_wndObjectToolbar.CloseWindow();
		m_wndActionToolbar.CloseWindow();		
		
		zoptions->ChangeDir(DIR_WORLD);
		zFILE* f = zoptions->GetDir(DIR_WORLD);
		zSTRING str = f->GetFullPath();
		str = str+zSTRING("~tmp.zen");
		zFILE_FILE delFile(str);
		delFile.FileDelete();				

		mainframe=0;

		/**** CHECK MEMORY *****/
		ASSERT(AfxCheckMemory());
		/**** CHECK MEMORY *****/

		CFrameWnd::OnClose();

		/**** CHECK MEMORY *****/
		ASSERT(AfxCheckMemory());
		/**** CHECK MEMORY *****/
	}
}

void CMainFrame::OnWindowsFix() 
{
	spcConfig.fixedWindows = !spcConfig.fixedWindows;
	if (spcConfig.fixedWindows)
	{		
		// Aktualisiere Resize-Styles der Childfenster
		spcCWindowResizeStyle* style;
		POSITION pos = childResizeList.GetHeadPosition();
		while (pos)
		{
			style = childResizeList.GetNext(pos);
			style->Calculate();					
		};
	};
}

void CMainFrame::OnMoveChild()
{
	/*
	if (spcConfig.fixedWindows)
	{
		// Aktualisiere Resize-Styles der Childfenster
		spcCWindowResizeStyle* style;
		POSITION pos = childResizeList.GetHeadPosition();
		while (pos)
		{
			style = childResizeList.GetNext(pos);
			style->Calculate();					
		};
	}
	*/
}


void CMainFrame::OnUpdateWindowsFix(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(spcConfig.fixedWindows);
}

void CMainFrame::UpdateFixedWindows()
{	
	// Aktualisieren Position der Childfenster 
	bool result;
	spcCWindowResizeStyle* style;
	POSITION pos = childResizeList.GetHeadPosition();
	while (pos)
	{
		style = childResizeList.GetNext(pos);
		result = style->UpdateSize();		
	};

};

void CMainFrame::OnMove(int x, int y) 
{
	CFrameWnd::OnMove(x, y);
	if (IsZoomed()) return;

	if (winID>0 && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
	}
	
	if (spcConfig.fixedWindows) UpdateFixedWindows();	
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{	
	CFrameWnd::OnSize(nType, cx,cy);

	if (nType==SIZE_MAXIMIZED) return;

	if (winID>0 && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);		
		spcConfig.SetWindowPosition(winID,rect);		
	}

	if (spcConfig.fixedWindows) UpdateFixedWindows();

}


CONST WIN_EXT_HEIGHT = 120;



void CMainFrame::OnWindowsAlignwindowsoutside() 
{	
	if (spcConfig.fixedWindows) OnWindowsFix();	

	RECT rect;
	GetWindowRect(&rect);

	CWnd* objwnd = winObjectDlg;
	CWnd* listwnd = 0;	
	if (winMaterialList->IsWindowVisible()) 
		listwnd = winMaterialList; 
	else if (winVobList->IsWindowVisible()) 
		listwnd = winVobList;
	else if (winCutsceneList->IsWindowVisible()) 
		listwnd = winCutsceneList; 

	RECT systemRect;
	SystemParametersInfo(SPI_GETWORKAREA,0,&systemRect,0);

	RECT wrect;
	int sysHeight	= systemRect.bottom - systemRect.top;
	int sysWidth	= systemRect.right - systemRect.left;

	int frameRight	= sysWidth;
	int frameBottom	= sysHeight;

	int height;
	int width;

	// Das Listwindow rechts oben
	if (listwnd)
	{	
		listwnd->GetWindowRect(&wrect);
		height = int (sysHeight / 2);
		width  = (wrect.right-wrect.left);
		frameRight = sysWidth-width;
		winVobList->SetWindowPos(&wndTop,frameRight,0,width,height,0);
		winMaterialList->SetWindowPos(&wndTop,frameRight,0,width,height,0);
		winCutsceneList->SetWindowPos(&wndTop,frameRight,0,width,height,0);						
	}	

	objwnd->GetWindowRect(&wrect);	
	height = sysHeight - int (sysHeight / 2);
	width  = (wrect.right-wrect.left);
	objwnd->SetWindowPos(&wndTop,sysWidth-width,int (sysHeight / 2),width,height,0);
	
	CWnd* wnd;	

	// InfoBar
	wnd = winBar;
	wnd->GetWindowRect(&wrect);
	height = (wrect.bottom-wrect.top);
	width  = (wrect.right-wrect.left);

	frameBottom = sysHeight-height;

	wnd->SetWindowPos(&wndTop,0,frameBottom,width,height,0);
	
	// HelpWindow
	wnd = winHelp;	
	wnd->SetWindowPos(&wndTop,width,frameBottom,frameRight-width,height,0);

	wnd = winCutsceneSequencer;
	wnd->GetWindowRect(&wrect);	
	wnd->SetWindowPos(&wndTop,0,0,wrect.right-wrect.left,wrect.bottom-wrect.top,0);
	
	// Toolbars
	if (m_wndActionToolbar.IsFloating())
	{	
		m_wndActionToolbar.GetDockingFrame()->GetWindowRect(&wrect);
		height = wrect.bottom-wrect.top;
		width  = wrect.right-wrect.left;
		m_wndActionToolbar.GetDockingFrame()->SetWindowPos(&wndTop,frameRight-width,0,0,0,SWP_NOSIZE);		
	}
		
	if (m_wndObjectToolbar.IsFloating())
	{
		m_wndObjectToolbar.GetDockingFrame()->GetWindowRect(&wrect);	
		height = wrect.bottom-wrect.top;
		width  = wrect.right-wrect.left;
		m_wndObjectToolbar.GetDockingFrame()->SetWindowPos(&wndTop,0,frameBottom-height,0,0,SWP_NOSIZE);		
	}
}

void CMainFrame::OnUpdateWindowsAlignwindowsoutside(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
}

void CMainFrame::OnWindowsAlignright() 
{	
	bool unfixedWindows = false;
	if (spcConfig.fixedWindows) 
	{
		OnWindowsFix();	
		unfixedWindows = true;
	}

	RECT rect;
	GetWindowRect(&rect);

	CWnd* objwnd = winObjectDlg;
	CWnd* listwnd = 0;	
	if (winMaterialList->IsWindowVisible()) 
		listwnd = winMaterialList; 
	else if (winVobList->IsWindowVisible()) 
		listwnd = winVobList;
	else if (winCutsceneList->IsWindowVisible()) 
		listwnd = winCutsceneList; 
		
	RECT wrect;
	int height;
	int width;
	
	// Toolbars
	if (m_wndActionToolbar.IsFloating())
	{	
		m_wndActionToolbar.GetDockingFrame()->SetWindowPos(&wndTop,rect.right,rect.top,0,0,SWP_NOSIZE);
		m_wndActionToolbar.GetDockingFrame()->GetWindowRect(&wrect);	
		rect.right = rect.right + (wrect.right-wrect.left);
	}
		
	if (m_wndObjectToolbar.IsFloating())
	{
		m_wndObjectToolbar.GetDockingFrame()->SetWindowPos(&wndTop,rect.left,rect.bottom,0,0,SWP_NOSIZE);
		m_wndObjectToolbar.GetDockingFrame()->GetWindowRect(&wrect);	
		rect.bottom = rect.bottom + (wrect.bottom-wrect.top);
	}		

	// Das Listwindow rechts
	if (listwnd)
	{	
		listwnd->GetWindowRect(&wrect);
		height = (rect.bottom-rect.top);
		width  = (wrect.right-wrect.left);
		winVobList->SetWindowPos(&wndTop,rect.right,rect.top,width,height,0);
		winMaterialList->SetWindowPos(&wndTop,rect.right,rect.top,width,height,0);	
		winCutsceneList->SetWindowPos(&wndTop,rect.right,rect.top,width,height,0);		
		
		rect.right = rect.right + width;
	}	

	objwnd->GetWindowRect(&wrect);	
	height = (rect.bottom-rect.top);
	width  = (wrect.right-wrect.left);
	objwnd->SetWindowPos(&wndTop,rect.right,rect.top,width,height,0);

	rect.right = rect.right + width;

	CWnd* wnd;

	// InfoBar
	wnd = winBar;
	wnd->GetWindowRect(&wrect);
	height = (wrect.bottom-wrect.top);
	width  = (wrect.right-wrect.left);
	wnd->SetWindowPos(&wndTop,rect.left,rect.bottom,width,height,0);
	
	// HelpWindow
	wnd = winHelp;
	wnd->GetWindowRect(&wrect);	
	wnd->SetWindowPos(&wndTop,rect.left + width,rect.bottom,rect.right - rect.left - width,height,0);

	wnd = winCutsceneSequencer;
	wnd->GetWindowRect(&wrect);	
	wnd->SetWindowPos(&wndTop,rect.left,rect.top,wrect.right-wrect.left,wrect.bottom-wrect.top,0);
	
	if (unfixedWindows) OnWindowsFix();
}

void CMainFrame::ObjectSelection(zCObject* obj, CWnd* wnd, BOOL show)	
{	
	zCVob*		vob = dynamic_cast<zCVob*>(obj);
	zCMaterial*	mat = dynamic_cast<zCMaterial*>(obj);
	
	// Hilfsfenster (Topic: Klassenname des Objekts)
	if (obj) GetHelpWindow()->SetHelpTopic(HELP_TOPIC_CLASS,obj->GetClassDef()->GetClassName_());
	else GetHelpWindow()->ClearTopics();
	
	///
	// Vob selektiert
	///	
	if (vob) 
	{				
		winInfoBar->SetSelectedObject(vob);
		HandleVobSelect(vob);		
	}
	else 
	///
	// Material selektiert
	///
	if (mat)
	{				
		// Selektion anderen Fenster mitteilen
		if (wnd != winObjectDlg) winObjectDlg->SelectObject(obj);
		if (wnd != winMaterialList)	winMaterialList->SelectMaterial(mat);
				
		winInfoBar_Materials->EditMaterial(mat);		
	}
	else 
	///
	// Sonstwas oder nix
	///	
	{				
		// Selektion anderen Fenster mitteilen		
		if (wnd != winObjectDlg) winObjectDlg->SelectObject(obj);
		UpdateChildWindows(obj,show==TRUE);		
	}		

	SetFocus();
}

CString CMainFrame::GetModeInformationString(zCObject* selectedObject)
{
	CString mode = "mode=";
	switch (workmode)
	{
		case MODE_NONE:		mode += "NONE";break;		
		case MODE_LIGHT:	mode += "LIGHT";break;
		case MODE_SOUND:	mode += "SND";break;
		case MODE_ZONE:		mode += "ZONE";break;
		case MODE_SPECIAL:	mode += "SPEC";break;
		case MODE_VOBS:		mode += "VOB";break;
		case MODE_MATERIAL:	mode += "MAT";break;
		case MODE_EVENT:	mode += "EV";break;
		case MODE_CUTSCENE:	mode += "CS";break; 
		case MODE_CAMERA:	mode += "CAM";break;
		case MODE_PROPS:	mode += "PROPS";break;
		case MODE_LOGICAL:	mode += "LOGIC";break;
		case MODE_VERTEX:	mode += "VERTEX";break;
		default: mode+="?";
	};
	
	zSTRING selected;
	zCVob* vob = dynamic_cast<zCVob*>(selectedObject);
	if (vob)
	{
		selected = "selected=";
		selected += vob->GetClassDef()->GetClassName_()+":";
		selected += "\""+vob->GetVobName()+"\"";
	};

	zSTRING dragging;	
	vob = GetObjectWindow()->IsEditingBoundingBox();
	if (vob)
	{
		dragging = "edit bbox=";
		dragging += vob->GetClassDef()->GetClassName_()+":"+vob->GetVobName();
	};

	CString returnValue = mode;
	if (!selected.IsEmpty()) returnValue += " | "+CString(selected.ToChar());
	if (!dragging.IsEmpty()) returnValue += " | "+CString(dragging.ToChar());
	return returnValue;
}


void CMainFrame::CloseChildWindow(CWnd* wnd)
{
	wnd->CloseWindow();
	delete wnd;
	wnd=0;
}


spcCInfoBar_Events* CMainFrame::GetInfoBarEvents()
{
	return winInfoBar_Events;
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	if (winID>0)
	{
		if (bShow)
		{
			spcTRegWindowInfo winInfo;
			spcConfig.GetWindowPosition(winID,winInfo);		
			MoveWindow(
				winInfo.position.pos.x,
				winInfo.position.pos.y,
				winInfo.position.size.cx,
				winInfo.position.size.cy,
				TRUE);		
		}
	}		
}

void CMainFrame::OnViewvobVobInitevents() 
{
	zCVob* vob = winInfoBar->GetSelectedVob();
	winInfoBar_Events->SetEventSourceVob(vob);
}

void CMainFrame::OnUpdateViewvobVobInitevents(CCmdUI* pCmdUI) 
{
	zCVob* vob = winInfoBar_Events->GetEventSourceVob();
	zCVob* pickedVob = winInfoBar->GetSelectedVob();
	pCmdUI->SetCheck(vob && (vob == pickedVob));
}


void CMainFrame::OnImporttext() 
{
	if (!winCutsceneList) return;

	CString filter = "Tabelle (*.csv)|*.csv|All Files(*.*)|*.*||";
	CFileDialog* dlg = new CFileDialog(true,"csv","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);

	zFILE::DirectFileAccess(true);
	int result = dlg->DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK) {

		winCutsceneList->Importtext(dlg->GetFileName());
	}
}

void CMainFrame::HandleKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar>=int('1') && nChar<=int('9'))
	{
		if (winInfoBar_Materials->IsWindowVisible())
		{
			winInfoBar_Materials->ActivateQuickSlot(nChar-int('1')+1);
		};
	};	
}

void CMainFrame::ResizeToView(CView *view, int x, int y)
{	
	static int oldX = -1;
	static int oldY = -1;	
	if (oldX==x && oldY==y) return;			// [EDENFELD] Fix 1.33 aus ModSource. "&&" War vorher "||"
	
	RECT winRect,winRect2;
	RECT viewRect;	
	view->GetWindowRect	(&viewRect);
	GetWindowRect		(&winRect);	
	winRect2 = winRect;
	
	RECT b;
	b.left			= viewRect.left		- winRect.left;	
	b.top			= viewRect.top		- winRect.top;
	b.right			= winRect.right		- viewRect.right;
	b.bottom		= winRect.bottom	- viewRect.bottom;	
	winRect.left	= viewRect.left		- b.left;
	winRect.right	= viewRect.left+x	+ b.right;
	winRect.top		= viewRect.top		- b.top;
	winRect.bottom	= viewRect.top+y	+ b.bottom;	

	MoveWindow(&winRect,TRUE);		
	oldX=x;
	oldY=y;	
}


void CMainFrame::OnUpdateObjCutscenes(CCmdUI* pCmdUI)
{
	zCCSManager* csmanager = GetInfoBar()?csmanager = GetInfoBar()->GetCurrentCutsceneManager():0;	
	pCmdUI->Enable		(csmanager!=0);
	pCmdUI->SetCheck	(csmanager!=0 && workmode==MODE_CUTSCENE);
};

void CMainFrame::OnUpdateCutsceneseq(CCmdUI* pCmdUI) 
{	
	zCCSManager* csmanager = 0;
	if (GetInfoBar()) csmanager = GetInfoBar()->GetCurrentCutsceneManager();
	pCmdUI->Enable(csmanager!=0 && winCutsceneSequencer!=0);
	pCmdUI->SetCheck(csmanager!=0 && winCutsceneSequencer!=0 && winCutsceneSequencer->IsWindowVisible());
}


void CMainFrame::OnUpdateObjVobs(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_VOBS);
}
void CMainFrame::OnUpdateObjZone(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_ZONE);
}
void CMainFrame::OnUpdateObjCameras(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_CAMERA);
}
void CMainFrame::OnUpdateObjLogical(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_LOGICAL);
}

void CMainFrame::OnUpdateObjLight(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_LIGHT);
}

void CMainFrame::OnUpdateObjSound(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_SOUND);
}

void CMainFrame::OnUpdateObjSpecial(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_SPECIAL);
}

void CMainFrame::OnUpdateObjTexture(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && (!world->IsCompiled() || world->IsCompiledEditorMode()));
	pCmdUI->SetCheck(workmode==MODE_MATERIAL);
}

void CMainFrame::OnUpdateObjVertex(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_VERTEX);
}

void CMainFrame::OnUpdateObjEvent(CCmdUI* pCmdUI) 
{
	zCWorld* world = winInfoBar?winInfoBar->GetActiveWorld():0;
	pCmdUI->Enable(world && world->IsCompiled() && !world->IsCompiledEditorMode());
	pCmdUI->SetCheck(workmode==MODE_EVENT);
}

spcCInfoBar* CMainFrame::GetInfoBar()
{
	return winInfoBar;
}


void CMainFrame::OnWorldStoreVobstates() 
{	
	if (GetInfoBar()) GetInfoBar()->StoreVobStates();
}

void CMainFrame::OnWorldRestoreVobstates() 
{
	if (GetInfoBar()) GetInfoBar()->RestoreVobStates();
}




void CMainFrame::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{	
	zERR_MESSAGE(9,0,"B: SPC: CMainFrame::HandleVobInsert");

	winInfoBar_Lights	->HandleVobInsert(vob,parentVob);
	winInfoBar_Sounds	->HandleVobInsert(vob,parentVob);
	winInfoBar_Events	->HandleVobInsert(vob,parentVob);
	winInfoBar_Zones	->HandleVobInsert(vob,parentVob);
	winInfoBar_Specials	->HandleVobInsert(vob,parentVob);
	winInfoBar_Camera	->HandleVobInsert(vob,parentVob);
	winObjectDlg		->HandleVobInsert(vob,parentVob);
	winVobList			->HandleVobInsert(vob,parentVob);
	CSpacerView::view	->HandleVobInsert(vob,parentVob); // nach allen anderen	

	SetFocus();
};


void CMainFrame::HandleVobRemove(zCVob *vob)
{
	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	zERR_MESSAGE(9,0,"B: SPC: CMainFrame::HandleVobRemove");

	CSpacerView::view	->HandleVobRemove(vob);	// vor allen anderen
	winInfoBar_Lights	->HandleVobRemove(vob);
	winInfoBar_Sounds	->HandleVobRemove(vob);
	winInfoBar_Events	->HandleVobRemove(vob);
	winInfoBar_Zones	->HandleVobRemove(vob);
	winInfoBar_Specials	->HandleVobRemove(vob);
	winInfoBar_Camera	->HandleVobRemove(vob);
	winObjectDlg		->HandleVobRemove(vob);
	winVobList			->HandleVobRemove(vob);	

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	SetFocus();
}

void CMainFrame::HandleVobSelect(zCVob *vob)
{
	zERR_MESSAGE(9,0,"B: SPC: CMainFrame::HandleVobSelect");
	CSpacerView::view->HandleVobSelect(vob);		

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	winInfoBar_Lights	->HandleVobSelect(vob);
	winInfoBar_Sounds	->HandleVobSelect(vob);
	winInfoBar_Events	->HandleVobSelect(vob);
	winInfoBar_Zones	->HandleVobSelect(vob);
	winInfoBar_Specials	->HandleVobSelect(vob);		
	winInfoBar_Camera	->HandleVobSelect(vob);		
	winVobList			->HandleVobSelect(vob);
	winObjectDlg		->HandleObjSelect(vob);

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	
	// Licht
	if (dynamic_cast<zCVobLight*>(vob))	
	{
		if (workmode!=MODE_LIGHT) OnObjLight();		
	}
	// Special
	else if (dynamic_cast<zCVobSpot*>(vob) || dynamic_cast<zCVobWaypoint*>(vob)) 	
	{ 
		if (workmode!=MODE_SPECIAL) OnObjSpecial();		
	}
	// CSCamera oder -Keyframe
	else if (dynamic_cast<zCCSCamera*>(vob) || dynamic_cast<zCCamTrj_KeyFrame*>(vob))	
	{
		if (workmode!=MODE_CAMERA) OnObjCameras();		
	}
	// Trigger
	else if (dynamic_cast<zCTrigger*>(vob))
	{
		if (workmode!=MODE_EVENT) OnObjEvent();
	}
	
	/*
	if (winCutsceneSequencer->IsWindowVisible())
	{		
		if (dynamic_cast<zCEventMessage*>(vob)) winCutsceneSequencer->ViewRefresh();
		winCutsceneSequencer->UpdateWindow();
	};
	*/

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	SetFocus();
};

void CMainFrame::HandleObjChange(zCObject *obj, int flag)
{
	zERR_MESSAGE(9,0,"B: SPC: CMainFrame::HandleVobChange");

	if ( (flag & UPDATE_OBJECT_SHEET) == UPDATE_OBJECT_SHEET)
	{
		winObjectDlg->HandleObjChange(obj);		
	}
	
	zCMaterial*		mat		= dynamic_cast<zCMaterial*>(obj);
	zCVob*			vob		= dynamic_cast<zCVob*>(obj);	

	// zCVob
	if (vob)
	{
		CSpacerView::view->HandleVobSelect(vob);	

		winVobList->HandleVobChange(vob);		
		// winInfoBar_Camera->HandleVobChange(vob);		
	}
	// zCMaterial
	else if (mat)
	{
		zBYTE filterID = mat->GetLibFlag();
		if (filterID != spcCMatFilter::NullLib)
		{
			int index = spcConfig.FindMatFilterIndexById(filterID);
			spcCMatFilter* item = spcConfig.matFilterList[index];
			if (item) item->SetDirty();
			winInfoBar_Materials->EditMaterial(mat);
		}
	}
	else
	{
		winCutsceneSequencer->HandleObjChange(obj);
	};	

	if ( (flag & UPDATE_FOCUS) == UPDATE_FOCUS)
	{
		SetFocus();
	};

};


void CMainFrame::UpdateChildWindows(zCObject *obj, bool show)
{
	///// Aktualisierung jedes Panels /////
		
	zCVob* vob = dynamic_cast<zCVob*>(obj);
	winInfoBar_Lights	->HandleVobSelect(vob);
	winInfoBar_Sounds	->HandleVobSelect(vob);
	winInfoBar_Events	->HandleVobSelect(vob);
	winInfoBar_Zones	->HandleVobSelect(vob);
	winInfoBar_Specials	->HandleVobSelect(vob);
	winInfoBar_Camera	->HandleVobSelect(vob);	
	
	zCMaterial* mat = dynamic_cast<zCMaterial*>(obj);
	winInfoBar_Materials->EditMaterial(mat);
	
	winInfoBar_Vobs	->SelectVob(vob);

	if (!show) return;

	///// AB HIER: Automatische Anzeige eines entsprechenden Panels /////	

	if (dynamic_cast<zCVobLight*>(vob))
	{
		if (workmode!=MODE_LIGHT) OnObjLight();		
	}
	else if (dynamic_cast<zCVobSpot*>(vob) ||	dynamic_cast<zCVobWaypoint*>(vob))
	{ 
		if (workmode!=MODE_SPECIAL) OnObjSpecial();		
	}
	else if (dynamic_cast<zCCSCamera*>(vob) || dynamic_cast<zCCamTrj_KeyFrame*>(vob))	
	{
		if (workmode!=MODE_CAMERA) OnObjCameras();		
	}
	else if (dynamic_cast<zCTrigger*>(vob))
	{
		if (workmode!=MODE_EVENT) OnObjEvent();
	}
	else if (vob)
	{		
		if (workmode!=MODE_PROPS) SetWorkMode(MODE_PROPS);
	}	
	if (winCutsceneSequencer->IsWindowVisible())
	{		
		if (dynamic_cast<zCEventMessage*>(vob)) winCutsceneSequencer->ViewRefresh();
		winCutsceneSequencer->UpdateWindow();	
	};

	SetFocus();
}


void CMainFrame::UpdateWorkMode()
{	
	zCWorld* world=0;
	if (winInfoBar) world = winInfoBar->GetActiveWorld();
	if (!world)
	{
		SetWorkMode(MODE_NONE);
	}	
	else
	{
		if (!world->IsCompiled() || world->IsCompiledEditorMode())
		{
			SetWorkMode(MODE_MATERIAL);
		}
		else
		{
			SetWorkMode(MODE_NONE);
		};
	};

	SetFocus();
};

void CMainFrame::ToggleWindowZOrder(CWnd* win)
{
	if (!win->IsWindowVisible()) return;		

	if (windowsAreOnTop)
	{
		//win->SetWindowPos( &wndBottom, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
		win->ShowWindow(SW_MINIMIZE);
	}
	else					
	{
		//win->SetWindowPos( &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);			
		win->ShowWindow(SW_RESTORE);
	}	
};

void CMainFrame::OnVieweditToggletools() 
{
	if (windowsAreOnTop && spcConfig.fixedWindows) windowsAreOnTop = !windowsAreOnTop;

	ToggleWindowZOrder(winBar);	
	ToggleWindowZOrder(winCutsceneSequencer);	
	ToggleWindowZOrder(winCutsceneList);	
	ToggleWindowZOrder(winMaterialList);
	ToggleWindowZOrder(winObjectDlg);
	ToggleWindowZOrder(winVobList);
	ToggleWindowZOrder(winHelp);
	ToggleWindowZOrder(winVobContainer);
	
	if (windowsAreOnTop)
	{
		m_wndObjectToolbar.GetDockingFrame()->ShowWindow(SW_HIDE);
		m_wndActionToolbar.GetDockingFrame()->ShowWindow(SW_HIDE);
	}
	else
	{
		m_wndObjectToolbar.GetDockingFrame()->ShowWindow(SW_SHOW);
		m_wndActionToolbar.GetDockingFrame()->ShowWindow(SW_SHOW);
	};
	
	windowsAreOnTop = !windowsAreOnTop;

	if (windowsAreOnTop)
	{
		SetWorkMode(workmode);
	};	
		
	SetFocus();
}

void CMainFrame::OnUpdateVieweditToggletools(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
}	

void CMainFrame::HideToolWindow(CWnd* wnd)
{
	if (!wnd) return;
	wnd->ShowWindow(SW_RESTORE);
	wnd->ShowWindow(SW_HIDE);
};

void CMainFrame::ShowToolWindow(CWnd* wnd)
{
	if (!wnd) return;	
	wnd->ShowWindow(SW_RESTORE);
	wnd->ShowWindow(SW_SHOW);
};

void CMainFrame::OnWindowsVobcontainer() 
{
	if (winVobContainer->IsWindowVisible())
	{
		winVobContainer->ShowWindow(SW_HIDE);		
	}
	else
	{
		winVobContainer->ShowWindow(SW_SHOW);
	};
	SetFocus();
}

void CMainFrame::OnUpdateWindowsVobcontainer(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
}

void CMainFrame::OnViewvobVobInserttocontainer() 
{
	zCVob* pickedVob = winInfoBar->GetSelectedVob();
	if (winVobContainer->mode == spcCVobContainer::VC_CUSTOM)
	{
		winVobContainer->AddVob(pickedVob);
	};
}

//[EDENFELD] 1.33 neu aus ModSource. Sound beim Reaktivieren ausgeben (Betrifft Compilevorgänge etc.)

static bool isWinEnabled = true;

bool CMainFrame::DeactivateApplicationWindows()
{			
	return TRUE;
	ShowWindow(SW_HIDE);
	if (windowsAreOnTop) OnVieweditToggletools();

	if (!isWinEnabled)  return false;
	else				isWinEnabled = false;
	return true;
};

bool CMainFrame::ReactivateApplicationWindows()
{	
	static zFILE_FILE* soundfile = 0;
	if (soundfile==0)
	{
		soundfile = new zFILE_FILE(zoptions->GetDirString(DIR_SYSTEM)+"ready.wav");
	}
	zSTRING s = soundfile->GetFullPath();

	
	zERR_MESSAGE(3,0,"B: SPC: Playing sound "+s);
	sndPlaySound(s.ToChar(),SND_ASYNC);		

	return TRUE;

	ShowWindow(SW_SHOW);
	if (!windowsAreOnTop) OnVieweditToggletools();

	


	if (isWinEnabled)	return false;	
	else				isWinEnabled = true;
	return true;
};

extern CGameManager* gameMan;

void CMainFrame::OnPlayGame() 
{
	// TODO: 
	// Spacer Menu ausblenden keine Spacer Tasten mehr annehmen (Ausnahme evtl. Vobmove,Pickvob,insert Kram, Invisible Kram, Viewport, Farclip)
	// ALT Taste macht Probs (Springen geht schlecht, da das Menu im Spacer jedesmal aufgeht)
	// einige Spacer Funktionalitäten klappen auch im Game Mode noch, sollten aber deaktiviert werden (Pickvob z.B.)
	// An aktueller Cameraposition starten

	// problem: im spacer eingefügt NSCs habe die Stand AI bzw. gar keine
	// zusätzlich wird der Spawnmanager ausgeschaltet
	// also hier während des spielens im spacer alles aktivieren

	oCWorld*	world	= 0;
	zCSession*	session	= 0;

	if ( CSpacerDoc::doc && CSpacerDoc::doc->GetWorld() ) world   = dynamic_cast<oCWorld*>(CSpacerDoc::doc->GetWorld());
	if ( CSpacerDoc::doc								) session = CSpacerDoc::doc->session;

	if ( !world || (!world->IsCompiled() && !world->IsCompiledEditorMode()) || !session ) return;

	// [BENDLIN] Addon Patch2 - 'Play the game'-Flag erst setzen, wenn es auch passiert
	g_bIsPlayingGame = TRUE;

	oCNpc::SetNpcAIDisabled(FALSE);
	zCVob::SetShowHelperVisuals(FALSE);
	CSpacerView::view->RememberCamPos();
	dynamic_cast<oCGame*>(session)->GetSpawnManager()->SetSpawningEnabled(TRUE);

		
	oTVobListNpcs* npclist = (world ? world->GetVobListNpcs():0);
	oTVobListNpcs* npcListCopy = zNEW(oTVobListNpcs);

	if (npclist)
	{
		for (int i=0;i<npclist->GetNumInList();i++)
		{
			if (npclist->Get(i))
			{
				oCNpc *nextNpc = npclist->Get(i);
				npcListCopy->Insert(nextNpc );
				nextNpc->AddRef();
				nextNpc->DeleteHumanAI();
				nextNpc->InitHumanAI();
			}
		};
	};		

	if (zinput->KeyPressed(KEY_LSHIFT))
	{
		g_bInsertNPCs = TRUE;
	}
	else 
	{
		g_bInsertNPCs = FALSE;
	}

	gameMan->Run();
	
	g_bInsertNPCs = FALSE;

	// und wieder alles so wie es war
	oCNpc::SetNpcAIDisabled(TRUE);
	dynamic_cast<oCGame*>(session)->GetSpawnManager()->SetSpawningEnabled(FALSE);

	if (npclist)
	{
		for (int i=0;i<npclist->GetNumInList();i++)
		{
			oCNpc *nextNpc = npclist->Get(i);
			if (nextNpc)
			{
				if (npcListCopy->IsInList(nextNpc))
				{
					// war vor "PLAY THE GAME" auch schon drin. nur die stand ai wieder einschalten, dann is gut
					nextNpc->UseStandAI();
					npcListCopy->Remove(nextNpc);
					zRELEASE(nextNpc);
				}
				else
				{
					// wurde in CGameManager::Run() neu eingefügt. Kann also komplett aus der Welt verschwinden
					world->RemoveVob(nextNpc);
				}
			}
		};
	};		
	zCVob::SetShowHelperVisuals(CSpacerDoc::doc->modeViewHelperVobs);
	if (zCAICamera::GetCurrent() && zCAICamera::GetCurrent()->GetVob())
	{
		zCAICamera *aiCam = zCAICamera::GetCurrent();		
		zCVob *aiCamVob	  = aiCam ->GetVob();
		aiCamVob->RemoveVobFromWorld();
	}

	CSpacerView::view->ResetCameraAfterPlay();
	CSpacerView::view->ResetCamPos();

	// ARGHH: irgendein zCAICamera Vob is noch in der Welt. Weg damit. Leaked zwar, aber darf auch nicht
	// drin bleiben. Der ganze Camerasetupkram ist eh fürn Arsch
	while (zCVob* nextCamera = world->SearchVobByName("ZCAICAMERA")) nextCamera->RemoveVobFromWorld();

	delete npcListCopy; npcListCopy = 0;
	zinput->ClearKeyBuffer();

	g_bIsPlayingGame = FALSE;
}

// [BENDLIN] Addon Patch2 - 'Play the game' nicht im Editormodus
void CMainFrame::OnUpdatePlayGame(CCmdUI* pCmdUI) 
{
	bool enabled = false;
	if (!g_bIsPlayingGame && CSpacerDoc::doc && CSpacerDoc::doc->session)
	{
		oCWorld* world = dynamic_cast<oCWorld*>(CSpacerDoc::doc->GetWorld());
		if (world)
			enabled = true;
	}
	pCmdUI->Enable(enabled);
	pCmdUI->SetCheck(g_bIsPlayingGame);
}

