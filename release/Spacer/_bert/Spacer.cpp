// Spacer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "zoption.h"
#include "zwin32.h"
#include "zinput_win32.h"

// z
#include "zoption_const.h"
#include "zengine.h"
#include "zexceptionhandler.h"

// o
#include "oobjfactory.h"
#include "ogamemanager.h"

// spacer
#include "MainFrm.h"
#include "SpacerDoc.h"
#include "SpacerView.h"

// spc
#include "spcCConfiguration.h"
#include "spcCWorkInfoDlg.h"


extern char* REG_COMPANY;

/////////////////////////////////////////////////////////
//// DATA

const char* SPC_APPLICATION_NAME		= _APP_NAME;
const char* SPC_VERSION					= _APP_VERSION;
const char* SPC_APPLICATION_DESCRIPTION	= "The Editor for the ZenGin";
const char* SPC_COMPANY_NAME			= _REG_COMPANY;
const char* SPC_AUTHOR_NAMES			= "Bert Speckels, Carsten Edenfeld and Andre Schrieber";
const char* SPC_YEAR_START				= "1997";
const char* SPC_YEAR_END				= "2003";
const char* SPC_COMPILE_DATE			= __DATE__;
const char* SPC_COMPILE_TIME			= __TIME__;

////
/////////////////////////////////////////////////////////

static CGameManager* gameMan = 0;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


zFILE*				mainpath	= 0;
spcCWorkInfoDlg*	workingDlg	= 0;

static void SetNumLock( BOOL bState )
{
  BYTE keyState[256];

  GetKeyboardState((LPBYTE)&keyState);
  if( (bState && !(keyState[VK_NUMLOCK] & 1)) ||
      (!bState && (keyState[VK_NUMLOCK] & 1)) )
  {
  // Simulate a key press
     keybd_event( VK_NUMLOCK,
                  0x45,
                  KEYEVENTF_EXTENDEDKEY | 0,
                  0 );

  // Simulate a key release
     keybd_event( VK_NUMLOCK,
                  0x45,
                  KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                  0);
  }
}

int MainProg()
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CSpacerApp

BEGIN_MESSAGE_MAP(CSpacerApp, CWinApp)
	//{{AFX_MSG_MAP(CSpacerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)	
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpacerApp construction

CSpacerApp::CSpacerApp()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of CSpacerApp...");

	enable_drawing = false;

	zERR_MESSAGE(7,zERR_END,"");
}

CSpacerApp::~CSpacerApp()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing CSpacerApp-Instance...");
	zERR_MESSAGE(7,zERR_END,"");
};

/////////////////////////////////////////////////////////////////////////////
// The one and only CSpacerApp object

CSpacerApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CSpacerApp initialization

extern	HINSTANCE	hInstApp;

BOOL CSpacerApp::InitInstance()
{		
	// Aktiviere das Überporüfen von Speicherüberschreibungen bei new und delete	
	
	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	hInstApp	= m_hInstance;

#ifdef _DEBUG
	afxMemDF = 0; // |= checkAlwaysMemDF;	
#endif	

	char mpath[MAX_PATH];
	GetModuleFileName(NULL,mpath,MAX_PATH);
		
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif	

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T(REG_COMPANY));
	
	LoadStdProfileSettings(6);  // Load standard INI file options (including MRU)

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

		// Parse command line for standard shell commands, DDE, file open		
	
	//workingDlg=0;	
	//workingDlg = new spcCWorkInfoDlg();
	//workingDlg->Init();	
	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
		
#undef new
	sysCommandLine = new char[2048];
#define new DEBUG_NEW

	strcpy(sysCommandLine," ");	
	strcat(sysCommandLine,m_lpCmdLine);	
	strcat(sysCommandLine," -nomenu -nonetwork -zwindow");	
	zerr.Init(sysCommandLine);
	sysParseCommandLine(sysCommandLine);	
		
	initializeSystemMFC();	

	zERR_MESSAGE(1,0,"Version of Spacer is "+zSTRING(SPC_VERSION)+", compiled: "+zSTRING(SPC_COMPILE_DATE));
	
	if (workingDlg) workingDlg->AddMessage("Creating basic Spacer-resources");	
	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSpacerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSpacerView));
	AddDocTemplate(pDocTemplate);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)) return FALSE;	

	zERR_ASSERT(CMainFrame::mainframe);			

	if (workingDlg) workingDlg->AddMessage("Initialize ...");		

	// [EDENFELD] 1.33 aus ModSource. Handle Handling sicherer gemacht
	zTSystemContextHandle handle = CSpacerView::view?CSpacerView::view->m_hWnd:0;
	Initialize(handle);		


	if (dynamic_cast<zCInput_Win32*>(zinput)) 
		dynamic_cast<zCInput_Win32*>(zinput)->SetFocusWindow(CSpacerView::view->m_hWnd);

	zrenderer->Vid_SetScreenMode(zRND_SCRMODE_HIDE);

	ShowCursor(TRUE);

	if (workingDlg) workingDlg->AddMessage("Loading configurations");	
	spcConfig.Load();

	if (workingDlg) workingDlg->AddMessage("Initializing windows ...");	
	
	CSpacerDoc::doc->Init();	

	if (dynamic_cast<CMainFrame*>(m_pMainWnd)) 
	{
		static_cast<CMainFrame*>(m_pMainWnd)->InitWindows();
	}		

	ShowCursor(TRUE);

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	RegisterShellFileTypes();	

	if (workingDlg)
	{
		workingDlg->CloseWindow();
		workingDlg->DestroyWindow();
		workingDlg = 0;
	}

	SetNumLock(TRUE);

	zERR_MESSAGE(3,0,"B: SPC: InitInstance finished");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_srcversion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_srcversion = _T(SPC_VERSION) + CString(", compiled: ") + _T(SPC_COMPILE_DATE) + " "+ + _T(SPC_COMPILE_TIME);
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_SRCVERSION, m_srcversion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSpacerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;	
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSpacerApp commands

BOOL CSpacerApp::OnIdle(LONG lCount) 
{	
	if (enable_drawing) 
	{
		// zERR_MESSAGE(4,0,"B: OnIdle 1");
		CSpacerView::view->RedrawWindow(0,0,RDW_INVALIDATE);		
		// zERR_MESSAGE(4,0,"B: OnIdle 2");
	}
	CWinApp::OnIdle(lCount);
	return 1;
}


void CSpacerApp::EnableDrawing(bool enable)
{
	enable_drawing = enable;
}

int CSpacerApp::ExitInstance() 
{			
	zERR_MESSAGE(3,zERR_BEGIN,"B: SPC: ExitInstance ...");

	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Deinit ...");
		Deinitialize();	
	zERR_MESSAGE(4,zERR_END,"");
	
	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Exit Spacerinstance ...");
		int result = CWinApp::ExitInstance();
	zERR_MESSAGE(4,zERR_END,"");

	zERR_MESSAGE(3,0,"B: SPC: ExitInstance finished ...");

	return result;
}


#include <process.h>
#include "spc_ParseTools.h"

static zCEngine *zengine = 0;

void CSpacerApp::Initialize(zTSystemContextHandle& handle)
{	
	delete parseinfo;
	parseinfo = new spcCParseInfo();	
	parseinfo->PrepareParseInfo();	
	
	gameMan = new CGameManager();	
	gameMan->Init(handle);		

	parseinfo->UpdateParseInfo();	
}

void CSpacerApp::Deinitialize()
{
	if (gameMan) 
	{
		gameMan->Done();	
		// delete gameMan;
		gameMan=0;
	}

	// zEngineClose();
	if (zengine) 
	{
		zengine->Shutdown();
		delete zengine; zengine=0;
	};
}

extern int MasterExceptionHandler();

int CSpacerApp::Run( )
{
// #define	SPC_EXCEPTION_HANDLING
#ifdef	SPC_EXCEPTION_HANDLING
	__try 
	{
#endif	

	return CWinApp::Run();	

#ifdef	SPC_EXCEPTION_HANDLING
	}
	_except(MasterExceptionHandler()) {};
#endif

	return 0;
};