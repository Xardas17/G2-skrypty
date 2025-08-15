//
// Windows 95 32Bit Platform specific code
//
// Changes:
// ---------
// 15.11.99: Windows Position wird wieder in die Registry rausgeschrieben


#define STRICT
#define OEMRESOURCE

#undef MESSAGE_DUMP
#undef TRACE_TIME

#include "zcore.h"



#ifdef CHASE_DEBUG
	#define NO_EXC_CHECK
#endif

// disable weird warning
#ifdef GetFirstChild
#undef GetFirstChild
#endif

#define _WIN32_WINNT 0x0400 

#include  <windows.h>
#include  <windowsx.h>


#include  <mmsystem.h>
#include  <commdlg.h>
#include  <commctrl.h>
#include  <process.h>
#include  <shellapi.h>
#include  <mmreg.h>
#include  <msacm.h>
#include  <richedit.h>
#include  <pbt.h>

#include  <stdlib.h>
#include  <stdio.h>
#include  <stdarg.h>
#include  <string.h>
#include  <memory.h>

// Includes for Win95 specific stuff
#include  "zExceptionHandler.h"
#include  "zVideo_Win32.h"
#include  "zInput_Win32.h"
#include  "zWin32.h"
#include  "zWin32_Internal.h"												// For our own windows core
#include  "zrenderer.h"

#include  "zWin32_Resource.h"									// Resource script stuff
#include  "zoption.h"


#ifdef COMPILING_GOTHIC
#ifndef COMPILING_SPACER
#include "ogame.h"
#endif
#endif






#define D_STRING(x,y) char	 *(x)=(y)

//
// Wichtig: Mit jeder neuen Version updaten !!!
//	 
#include "zWin32_Version.h"

	int	APP_VERSION_MAJOR = _APP_VERSION_MAJOR;
	int	APP_VERSION_MINOR = _APP_VERSION_MINOR;
	int	APP_VERSION_POINT = _APP_VERSION_POINT;
	int	APP_VERSION_INT = _APP_VERSION_INT;

	D_STRING (APP_NAME,		_APP_FULLNAME);
	D_STRING (APP_VERSION,	_APP_VERSION);		
	D_STRING (REG_PROGRAM,	_REG_PROGRAM);

	D_STRING (REG_VERSION,	_REG_VERSION);
	D_STRING (REG_COMPANY,	_REG_COMPANY);

	D_STRING (ENV_NOBROWSERSTRING,	"You must have a web browser installed to view HTML pages");
	D_STRING (HFILE_LOG,			"DemoW.log");


MENUITEM  ENV_STDMENU[]={
    { MENU_SUBMENU,			0,        "",                            NULL, 0 },
    { MENU_END_OF_MENU, 0, NULL, NULL, 0 }
  };

  
#define MAX_FPS_COUNT			512
#define MOUSE_QUEUESIZE 		64									// Queued mouse messages

 

// Window positions
struct
{
  zLONG	  xMain, yMain, wMain, hMain, maxMain;
  zLONG	  xSpy,  ySpy,	wSpy,  hSpy,  maxSpy;
  zBYTE	  Valid;
} iwPos;

// External Prototypes
extern int MainProg();

// Local Prototypes
static LRESULT	CALLBACK AppWndProc(HWND, zUWORD, WPARAM, LPARAM);
static LRESULT	CALLBACK AppKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);
static zBOOL 	CALLBACK OutOfMemProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
static zBOOL 	CALLBACK CrashDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
static zDWORD	AppCommand(HWND, zUWORD, WPARAM, LPARAM);
static zDWORD	GetHTime();
static zDWORD	GetHTime70();
static void 	winSaveWindowPos();
static void 	winInitSystem();
static void 	winCreateClasses();
static void 	sysInitTimer();
static void     kbInit ();
void			winSuspendThreads();
zBOOL			sysGotDebugger();
zBOOL			cfgGetBinary(char *Topic, char *Key, void *Data, int *Size);

// FIXME: net externals, can't include zNet_Win32.h w/o errors ??
extern	void	netInit();											// Initialise network functions
extern	void	netExit();											// Deinitialise network functions
extern	void	netAcceptPendingConnections();						// Accept pending connections

// FIXME: param "word msg" should be zWORD msg, can't include "ztypes.h" w/o errors ??
extern	LRESULT CALLBACK netWindowProc(HWND hwnd, zWORD msg, WPARAM wParam, LPARAM lParam);


void 	inCreateMouseMessage(DWORD wParam, DWORD lParam);

#ifdef TRACE
#undef TRACE
#endif

// Processor-level information

static HHOOK   winAppKeyboardHook;									// Application keyboard hook handle
static zBOOL   bLostFocus = FALSE;
HANDLE	winMainThread;												// Thread handle of main windows thread
zDWORD	winMainThreadID;											// Thread of main windows program
 
// Global data for Windows 98 programs
HINSTANCE hInstApp=NULL;											// Our instance
HDC 	dcScreen=NULL;												// Screen-compatible DC
HICON	hIconApp=NULL;												// Icon for application
HWND	hWndApp=NULL;												// Windows APP Window
zBOOL	sysExiting=FALSE;											// When TRUE, -> Exiting app
zBOOL	sysStopProcessingMessages=FALSE;							// When TRUE, -> Don't process messages any more
zBOOL	winNT=FALSE;												// Runnin' on Windows NT?
int		winBPP=0;													// Windows display mode depth
char	*sysCommandLine; 											// Command line data
zDWORD	sysTimeGap=0;												// Gap in time measurements
#ifndef COMPILING_SPACER
zBOOL	netEnable=TRUE; 											// Assume to use network
#else 
zBOOL	netEnable=FALSE; 											// Assume to use network
#endif
int 	winCursorShowState=0;										// Cursor show state

static UINT		g_uQueryCancelAutoPlay = 0;							// "QueryCancelAutoPlay" message id

static LPCFUNC		sysMenuCallback=NULL;							// -> Menu callback function
static LPMENUITEM	sysMenu=ENV_STDMENU;							// -> Application menu
static HICON	iconInfo;											// Info (asterisk) icon
static int		DlgResult;											// For Program <-> Dialog interaction
static HKEY 	cfgHKey=NULL;										// Registry key for program settings
static HKEY		cfgBaseKey=HKEY_CURRENT_USER;						// Current base key
static char		cfgKeyName[256];									// Name of new key
static HMENU	hMenuApp=NULL;										// Main menu
static zDWORD	sysPowerNextAllowedScrSave; 						// Next allowed screen save time
static zDWORD	sysPowerNextAllowedLowPower;						// Next allowed suspend
static zDWORD	sysPowerScrSaveTimeOut; 							// Screensaver timeout value
static zDWORD	sysPowerLowPowerTimeOut;							// Power-down timeout 
static zDWORD	sysPowerOptions;									// Power options
static zDWORD	sysCallBackLast;									// Last callback timer value
static LPCFUNC	sysCallBack=NULL;									// Callback function
static zDWORD	sysCallBackDelay=0; 								// Delay period for callback
static zBOOL 	sysCallBackSingle=FALSE;							// Callback single call flag
static zBOOL 	sysEventToggleFullScreen=FALSE; 					// Toggle fullscreen mode in sysEvent
static zBOOL 	sysEventScreenBlanked=FALSE;						// Enter screen blank mode in sysEvent
static zBOOL	bSysHandleExceptions = TRUE;
static HANDLE	sysInstLock=NULL;									// Handle of program lock
static char		sysLogName[MAX_PATH];								// Name of log file
static zBOOL		sysSafeLog=FALSE;									// Safe logging (flush after each write?)
static zBOOL 	winInMenu=FALSE;									// In menu loop?
static HANDLE	winTRACEMutex=NULL; 								// MuteX to make TRACE thread-safe
static zBOOL 	winUseRegistry=TRUE;								// Use windows registry?
static char 	winAppEXEName[MAX_PATH];							// Executable name
static RECT 	winWindowSize;										// Size of client area
static zBYTE 	winMode=0;											// 0=No window initialised
#ifdef _DEBUG
zBOOL	sysCrashGuardMode=FALSE;									// Find crashes?
static HANDLE	sysCrashGuardThread;								// Crash find iterator thread
static zDWORD	sysCrashGuardThreadID;								// Crash find iterator thread ID
static int		sysCrashGuardIter=0;								// Crash find iterator
static char		*sysCrashStack[1024]={ NULL };						// Crash call stack
#endif

// Win32 stuff
static UINT    CheckBool[2]={MF_UNCHECKED, MF_CHECKED}; 			// Easy INTs for checking
static UINT    GrayBool[2]={MF_GRAYED, MF_ENABLED}; 				// Easy INTs for graying
static CUSTOMCAPTION ccMain;										// Custom caption for main wnd
static CUSTOMCAPTION ccDialog;										// Custom caption for various dialogs

// Mouse info
// Mouse info structure

// Mouse message structure
typedef struct
{
	zBYTE   bMsg;													// Message type
	zBYTE	bButtons;												// Mouse button status
	zWORD	x;														// X Position
	zWORD   y;														// Y Position
} MOUSE_MESSAGE, *LPMOUSE_MESSAGE;

typedef struct
{
  zDWORD   Buttons;													// Mouse buttons
  zLONG	  MsgCur;													// Current message
  zLONG	  MsgRead;													// Highest read message
  MOUSE_MESSAGE mMsg[64];											// Mouse messages
} mouseInfoStruct;


static mouseInfoStruct mouseInf;									// Mouse info structure

// User-interface
zBOOL  usrSafeMode=FALSE;											// User in safe mode?
zBOOL  usrWantPause=FALSE;											// User wants to pause the game
zBOOL  usrWantQuit=FALSE;											// User wants to quite the game
 
// Video stuff
zBOOL	winMinimized=FALSE; 										// User in minimized fullscreen?
static zDWORD	winUserModeList[64];								// User screen mode list
static zDWORD	winSnapSize[32*2];									// Predefined snap size for window sizes
static zDWORD	winSnapSizes=0; 									// Amount of user defined snap sizes


#ifdef _DEBUG  // _DEBUG?
	// Debug data
	__declspec( thread ) char	*__cs_data[1024];
	__declspec( thread ) int	__cs_idx=0;
	__declspec( thread ) int	__cs_end=0x70000000;
	void __cs_error()
	{
		sysHardExit("Could not find EXIT_PROC() or RETURN() for function %s", __cs_data[__cs_idx]);
	}
	
	zBOOL	sysTimerInitialised=FALSE;
  
	// Debug functions
	INLINE void END_OF_CALLSTACK() { __cs_end=min(__cs_end, __cs_idx-1); }
#else
	INLINE void END_OF_CALLSTACK() { }
#endif

// Defines for extra window size (overhead from borders and stuff)
static zDWORD   winExtraX;											// Extra width around window
static zDWORD   winExtraY;											// Extra height around window

zBOOL    winShowMouse=2;										// Show mouse cursor?

// Timer services
static LARGE_INTEGER pTimeStart;									// Precise timer start
static LARGE_INTEGER pTimeFreq; 									// Precise timer frequency
static zDWORD   TimeStart;											// Starting time for timer
static zDWORD   BeginTime;											// Time of program start
static zDWORD   BeginTime70; 										// Time of program start 70 Hz
static zBOOL    PreciseTimer;										// System has precise timer?
static zDWORD   pTimeDiv;											// Precise timer divider
static zDWORD   pTimeDiv70;											// Precise timer divider 70Hz

// Random stuff
/* static	zBYTE CHAOS[256]={	198,126,129,107, 75,251,226,251, 84,246,189,223,124, 28,225,135,  1,191, 49,222, 86,114, 15, 71,103,102,135, 89,170,136, 60, 89,234, 86, 19,123,210,
							133,161,216, 60, 84, 85, 47, 55,174,101, 91,218,  2,121,152,204,227, 26,118,142, 95,217,153,143, 31, 63, 54,238, 67,120, 77, 13,250,190,166,218,228,
							134,142,220, 41,109, 78,255, 86,225,112, 32,251,143,177, 88,  5,144,197,  9,220, 83,205,170, 59, 72,153, 82,211, 82,157,  6,159,234,181,194,  6, 19,
							152, 73,178,  1, 30,172, 50,136, 49,156, 82, 70,149,113, 54,143, 87,246, 57, 29, 22,250,136,116,245,152,124, 23, 92, 65,187,109,113,142, 15,112, 89,
							199,  1, 27, 47, 51, 61,145,192, 29,165, 13, 13,171, 51,141,126, 94,143, 62,230,104,116,166, 58,177,195,147, 17,168,100,199,219,202,224, 96,225,243,
							191,  9,  0,103,162,227, 37,160, 33, 49,135,213, 98,197,168, 79,126, 46,  9,107,148,159,176,109,169,158, 90, 11, 70,112,128,182,207, 71, 12,166,165,
							 42,216,172,251,160,235,183,121, 36,114, 35,146, 72,128,197,166,167,133,183,215,140,144,228,171, 99, 68, 82,102,227,156, 51, 37,249, 94 };*/

// Static callbacks which allways return TRUE or FALSE. You can use these entries if a
// callback is used to override something (for example, to check something) and the
// default behaviour is TRUE or FALSE

#define cfunc					zBOOL __cdecl
#define cfuncp					zBOOL __cdecl
#define pfunc					__cdecl *

static cfunc  cfuncTRUE(zDWORD n)	{ return TRUE;	}
static cfunc  cfuncFALSE(zDWORD n)	{ return FALSE; }
static cfuncp cfuncpTRUE(void *p)	{ return TRUE;	}
static cfuncp cfuncpFALSE(void *p)	{ return FALSE; }


HHOOK g_lLowLevelHook;

typedef enum zTWindowsType
{
    WindowsType95,
    WindowsType98,
    WindowsTypeME,
    WindowsTypeNT3,
    WindowsTypeNT31,
    WindowsTypeNT35,
    WindowsTypeNT351,
    WindowsTypeNT4,
    WindowsType2000,
    WindowsTypeOther
};

struct zTWindowsVersionInformation
{
    zTWindowsType	nVersionName;
    zSTRING			sVersion;
    long			lBuild;
    zSTRING			szServicePack;
};


static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	bool fEatKeystroke = false;

    if (nCode == HC_ACTION) 
	{
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN || wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
		{
			#define LLKHF_ALTDOWN        (KF_ALTDOWN >> 8)

			typedef struct tagKBDLLHOOKSTRUCT {
				DWORD   vkCode;
				DWORD   scanCode;
				DWORD   flags;
				DWORD   time;
				ULONG_PTR dwExtraInfo;
			} KBDLLHOOKSTRUCT, FAR *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;


			KBDLLHOOKSTRUCT p;
			memcpy((void*)&p, (void*)lParam, sizeof(KBDLLHOOKSTRUCT));

            bool bAlt		= (p.flags & LLKHF_ALTDOWN) != 0;
            bool bCtrl		= (GetKeyState(VK_CONTROL) & 0x8000)	!= 0;
            bool bDelete	= (p.flags == VK_DELETE);

            switch(p.vkCode)
			{
            case VK_TAB:
                if (bAlt) fEatKeystroke = true;
				break;
            case VK_ESCAPE:
                if (bAlt || bCtrl) fEatKeystroke = true;
				break;
            case VK_LWIN:
			case VK_RWIN:
                fEatKeystroke = true;
				break;
			default:
				if (bDelete && bCtrl) fEatKeystroke = true;
            }
        }
    }

    if (fEatKeystroke) 
	{
		zERR_WARNING("C: ate keystroke!");
		return -1;
	}
    else               return CallNextHookEx(0, nCode, wParam, lParam);

}

zTWindowsVersionInformation GetWinVersion()
{
    //filled with OS information

    OSVERSIONINFO OSV;
    zSTRING sVer;
    zSTRING sBuild;
    zTWindowsVersionInformation wvi;

    OSV.dwOSVersionInfoSize = sizeof(OSV);
    if (GetVersionEx(&OSV) == 1)
	{
        //platformId contains a value representing the OS
        switch(OSV.dwPlatformId)
		{
        case VER_PLATFORM_WIN32s:   wvi.nVersionName = WindowsTypeOther; break;
        case VER_PLATFORM_WIN32_NT:
            //dwVerMajor = NT version.
            //dwVerMinor = minor version
            switch(OSV.dwMajorVersion)
			{
            case 3:
                switch(OSV.dwMinorVersion)
				{
                case 0:  wvi.nVersionName = WindowsTypeNT3;		break;
                case 1:  wvi.nVersionName = WindowsTypeNT31;	break;
                case 5:  wvi.nVersionName = WindowsTypeNT35;	break;
                case 51: wvi.nVersionName = WindowsTypeNT351;	break;
                }
            case 4: wvi.nVersionName = WindowsTypeNT4;	break;
            case 5: wvi.nVersionName = WindowsType2000; break;
			}
			break;
        case VER_PLATFORM_WIN32_WINDOWS:
            //The dwVerMinor bit tells if its 95 or 98.
            switch (OSV.dwMinorVersion)
			{
            case 0 : wvi.nVersionName = WindowsType95; break;
            case 90: wvi.nVersionName = WindowsTypeME; break;
            default: wvi.nVersionName = WindowsType98; break;
            }
			break;
		}
	}

    //the version number
    wvi.sVersion = zSTRING(OSV.dwMajorVersion) + "." + zSTRING(OSV.dwMinorVersion);

    //the build
    wvi.lBuild   = (OSV.dwBuildNumber & 0xFFFF);

    //Any additional info. In Win9x, this can be
    //any arbitrary string" provided by the
    //manufacturer. In NT, this is the service pack.
    // OSV.szCSDVersion

	return wvi;
}


bool sysKillWindowsKeys(bool bKillEm)
{
	// FIXME: hier abkachler beim runterfahren (zoptions nicht initialisiert?)
	if (!zoptions || !zoptions->ReadBool("ENGINE", "zKillSysKeys", FALSE)) return true;
#ifdef COMPILING_SPACER
	return TRUE;
#endif

    //returns the handle in the WINNT case.
    BOOL lRet = true;
    UINT bDummy;
    zTWindowsVersionInformation wvi;
    bool bNT = FALSE;
    long nVal;

    wvi = GetWinVersion();

    switch(wvi.nVersionName)
	{
    case WindowsType2000:
	case WindowsTypeNT4:
        //determine by the SP and version what to do
        
        if      (wvi.sVersion.ToFloat() > 4.0f)		bNT = true; 
		else if (wvi.sVersion.ToFloat() < 4.0f)		bNT = false;
		else if (wvi.sVersion.ToFloat() == 4.0f && 
			     wvi.szServicePack.ToFloat() >= 3)  bNT = true;        
    };

    if (bNT)
	{
        if (bKillEm)
		{
			if (g_lLowLevelHook > 0)
			{
				UnhookWindowsHookEx(g_lLowLevelHook);
				g_lLowLevelHook = 0;
			}

            if (g_lLowLevelHook == 0)
			{
                //kill the keys
                g_lLowLevelHook = SetWindowsHookEx(13 /*WH_KEYBOARD_LL*/, &LowLevelKeyboardProc, hInstApp, 0);
				if (g_lLowLevelHook==0) zERR_WARNING("C: could not set low level keyboard handler");
            }
		}
        else if (g_lLowLevelHook != 0)
		{
            //reset the hook
            UnhookWindowsHookEx(g_lLowLevelHook);
			g_lLowLevelHook = 0;
        };
    }
	else if (wvi.nVersionName == WindowsType95)
	{
        nVal = zAbs(bKillEm);
        lRet = SystemParametersInfo(SPI_SCREENSAVERRUNNING, nVal,(void*)&bDummy, 0);
        lRet = SystemParametersInfo(SPI_SETFASTTASKSWITCH,  nVal,(void*)&bDummy, 0);
	}
    else
	{
		if (bKillEm) nVal = 1;
		else		 nVal = 0;
        lRet = SystemParametersInfo(SPI_SCREENSAVERRUNNING,bKillEm, (void*)&bDummy, 0);
        lRet = SystemParametersInfo(SPI_SETFASTTASKSWITCH, bKillEm, (void*)&bDummy, 0);
    }

	return (lRet != 0);
};


bool SetForegroundWindowEx(HWND Wnd)
{
	BOOL Success = FALSE;

#ifndef COMPILING_SPACER
	// Validate param
	if ( (Wnd == NULL) )
		return FALSE;

	DWORD	OwnProcessId	= GetCurrentProcessId();
	UINT	OwnThreadId		= GetCurrentThreadId();
	HWND	TargetWndHandle	= GetForegroundWindow();
	DWORD	TargetProcessId	= GetCurrentProcessId();
	UINT	TargetThreadId	= GetWindowThreadProcessId(TargetWndHandle, &TargetProcessId);
	
	// Window already owns the input focus
	if ( (Wnd == TargetWndHandle) )
		return TRUE;
	// Our process already owns the input focus
	if (OwnProcessId == TargetProcessId)
	{
		SetForegroundWindow(Wnd);
		return TRUE;
	}

	// Attach to input queue of the thread of the window which has the focus
	// (if not our won thread, and so on)
	if ( (TargetWndHandle != NULL) && (TargetThreadId != 0) )
	{
		if ( (OwnThreadId == TargetThreadId) )
		{
			Success = (SetFocus(Wnd) != NULL);
		}
		else if ( AttachThreadInput(OwnThreadId, TargetThreadId, TRUE) )
		{
			// Set focus
			Success = (SetFocus(Wnd) != NULL);
			// Detach input queue
			AttachThreadInput(OwnThreadId, TargetThreadId, FALSE);
		}
	}

	// Call original function if no success
	if (!Success)
		Success = SetForegroundWindow(Wnd);

	// [EDENFELD] neuen Code musste ich erst mal wieder deaktivierten, da es häufiger zu Crashes bei Focusverlust führt als der alte Code
#else
	SetForegroundWindow(Wnd);
	return TRUE;
#endif
	
	return (Success != 0);
}

// Bring to foreground
/**{ sysSetWindowMode, Win32 }
@func

The sysSetWindowMode function is a low-level function that prepares the display window for
fullscreen or windowed display. It is used internally in @@vidSetMode, but it is
also exported from the library to aid people who are using a display method different
from the own video library.

@params
@return

@remarks
	A fullscreen window is a topmost window (which is always displayed on top of other
	windows) at the size of the screen and it is totally black. It doesn't have a menu,
	system menu or borders. 

	A normal window does have a border and a system menu. Therefore the windows accelerator
	keys (namely Alt and F10) do not work in a normal window.

	If you set the Show flag on a fullscreen window, the screen will go black and only the
	mouse cursor will be visible. If you don't set the Show flag on a fullscreen window it
	will change the window's properties so that it's border and menu will be removed, but
	it won't change the size of the window to fullscreen or force the window to be shown.
	
	It is possible to have a hidden fullscreen window. If you do not call @@vidSetMode the
	main window will be hidden. Calling sysSetWindowMode(TRUE, FALSE) will change the
	window's style to fullscreen, but it won't show it.

@portable
@see vidSetMode sysSetFocus
**/
void sysSetWindowMode(
	zBOOL	FullScreen,		/* Fullscreen flag
	When this flag is set to TRUE, the display window is prepared for fullscreen mode. If
	this flag is set to FALSE it is prepared for windowed mode. */

	zBOOL	Show			/* Show flag
	Show flag. Determines wether or not the window will be shown. This flag only has
	effect when FullScreen is set to TRUE. If FullScreen is set to FALSE, the window will
	always be shown. */
)
{
	// Show main window before start execution
	if (FullScreen)
	{
		// Windowed -> Full Screen, save window position
		if (winMode==VIDMODE_ANYWINDOWED)							// Currently still in windowed mode?
		{
			RECT winPos;											// Window position

			GetWindowRect(hWndApp, &winPos);						// Get window position
			iwPos.xMain=winPos.left;
			iwPos.yMain=winPos.top;
			iwPos.wMain=winPos.right-winPos.left;
			iwPos.hMain=winPos.bottom-winPos.top;
			iwPos.Valid=TRUE;
		}

		// Remove riff-raffs from window (we just need a black rectangle)
		SetMenu(hWndApp, NULL); 									// Remove menu
		SetWindowLong(hWndApp, GWL_STYLE, WS_POPUP);				// Popup window (no menus and shit)
		SetWindowLong(hWndApp, GWL_EXSTYLE, WS_EX_TOPMOST); 		// Set topmost style
		winMode=VIDMODE_ANYFULLSCREEN;								// We're fullscreen!
		if (Show) SetWindowPos(hWndApp, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED); // Put window to front
		if (Show && !IsZoomed(hWndApp)) ShowWindow(hWndApp, SW_SHOW);	// Show our maximized window
	}
	else
	{
		// Full Screen -> Windowed, restore window position (if we've got the rect for it)
		if (winMode==VIDMODE_ANYFULLSCREEN && iwPos.Valid)
		{
			ShowWindow(hWndApp, SW_HIDE);
			MoveWindow(hWndApp, iwPos.xMain, iwPos.yMain, iwPos.wMain, iwPos.hMain, TRUE);
			winResizeMainWindow();									// Resize window now
			ccRenderCaption(hWndApp, &ccMain);						// Re-render this caption
		}

		// Prepare window and show it
#ifndef COMPILING_SPACER
		SetWindowLong(hWndApp, GWL_STYLE, WS_CAPTION | WS_SYSMENU); 
#else
		SetWindowLong(hWndApp, GWL_STYLE, WS_OVERLAPPEDWINDOW);			// Normal window
#endif
		SetWindowLong(hWndApp, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW);	// Set overlapped window
		winCreateMenu();											// Create win32 menu

		SetWindowPos(hWndApp, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // Put window to front
		winMode=VIDMODE_ANYWINDOWED;								// We're fullscreen!
		ShowWindow(hWndApp, SW_SHOW);								// Show our window
		SetForegroundWindowEx(hWndApp);								// Bring to foreground
		UpdateWindow(hWndApp);										// Update window contents

		InvalidateRect(GetDesktopWindow(), NULL, TRUE); 			// Repaint background
	}
}

//
// Convert a size to a text string representation
//
static LPARAM winKBText(LONG Size)
{
	static char TextBuffer[32];										// Small text buffer
	char  *tBuf=TextBuffer;											// -> Output text string
	zDWORD sDiv=1; 													// Size divider
	
	// Set size and find largest divider
	if (Size<0)
	{
		*tBuf++='-';												// Put sign
		Size=-Size; 												// Make positive
	}
	Size=(Size+512)>>10;											// Round size to KBs
	while (Size/(sDiv*1000)) sDiv*=1000;							// Find largest quantisizer
	
	while (sDiv)
	{
		if (tBuf<=TextBuffer+1) 									// First group?
			sprintf(tBuf, "%u", Size/sDiv);							// Set 'head' (without 0's)
		else
			sprintf(tBuf, "%03u", Size/sDiv); 						// Set size in KBs
		tBuf+=strlen(tBuf); 										// Skip new chars
		Size%=sDiv; 												// Factor down size
		sDiv/=1000; 												// Size down divider
		if (sDiv) *tBuf++='.';										// Prefix with dot
	}
	*tBuf=0;														// Terminate string
	return (LPARAM)TextBuffer;										// Return string
}

//
// Out of memory dialog proc
//
static BOOL CALLBACK OutOfMemProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static zDWORD mSize; 											  // Memory size
	static MEMORYSTATUS mOldStatus; 								  // Previous memory state
	MEMORYSTATUS mStatus;											  // Memory info
	HRGN	  newRgn;												  // New region for clipping
	RECT	  cWinSize; 											  // Size of window (for clipping area)
	LPVOID	  Block;												  // New memory block
	CHAR	  TextBuffer[512];										  // Text string buffer
	ENTER_PROC(OutOfMemProc);

	switch (uMsg) {
	case WM_INITDIALOG: mSize=lParam;								// Save parameter

						// Show program name and memory request size
						sprintf(TextBuffer, "%s has run out of memory!\nCould not allocate %d KB memory block", APP_NAME, mSize);
						SendDlgItemMessage(hwndDlg, IDC_MEMERROR,	 WM_SETTEXT, 0, (LPARAM)TextBuffer);
						SendDlgItemMessage(hwndDlg, IDC_MEMREQUIRED, WM_SETTEXT, 0, winKBText(mSize));

						// Initialise update timer
						SetTimer(hwndDlg, 0xCAFE, 250, NULL);		// Set timer for 34 fps

						ccWM_INITDIALOG(hwndDlg, ccDialog, 1, NULL, FALSE);

						RETURN(TRUE);

	case WM_TIMER:		if (wParam==0xCAFE)
						{
						  GlobalMemoryStatus(&mStatus);
						  if (memcmp(&mStatus, &mOldStatus, sizeof(MEMORYSTATUS))==0) RETURN(0);
						  memcpy(&mOldStatus, &mStatus, sizeof(MEMORYSTATUS));

						  // Update memory stats (if changed)
						  SendDlgItemMessage(hwndDlg, IDC_MEMPHYS,	   WM_SETTEXT , 0, winKBText(mStatus.dwTotalPhys));
						  SendDlgItemMessage(hwndDlg, IDC_MEMPHYSFREE, WM_SETTEXT, 0, winKBText(mStatus.dwAvailPhys));
						  SendDlgItemMessage(hwndDlg, IDC_MEMSWAP,	   WM_SETTEXT, 0, winKBText(mStatus.dwTotalPageFile));
						  SendDlgItemMessage(hwndDlg, IDC_MEMSWAPFREE, WM_SETTEXT, 0, winKBText(mStatus.dwAvailPageFile));
						  SendDlgItemMessage(hwndDlg, IDC_MEMFREE,	   WM_SETTEXT, 0, winKBText(mStatus.dwAvailPageFile+mStatus.dwAvailPhys));
						  SendDlgItemMessage(hwndDlg, IDC_MEMDIFF,	   WM_SETTEXT, 0, winKBText(mStatus.dwAvailPageFile+mStatus.dwAvailPhys-mSize));
						  sprintf(TextBuffer, "%u%%", mStatus.dwMemoryLoad);
						  SendDlgItemMessage(hwndDlg, IDC_MEMLOAD,	   WM_SETTEXT, 0, (LPARAM)TextBuffer);

						  RETURN(0);								 // Processed
						}
						break;										// When no known timer -> default

	case WM_CLOSE:		EndDialog(hwndDlg, 0);
						RETURN(FALSE);

	case WM_COMMAND:	switch (LOWORD(wParam))
						{
						  case ID_CANCEL:	   EndDialog(hwndDlg, 0); RETURN(TRUE);
						  case ID_RETRY:	   ASSERT(sizeof(int)>=sizeof(LPVOID));
											   Block=(LPVOID)LocalAlloc(LPTR, mSize);
											   if (Block) EndDialog(hwndDlg, (int)Block);
											   RETURN(TRUE);
						};
						RETURN(FALSE);

	ccWM_FILTER(ccDialog, hwndDlg);

	default:			RETURN(FALSE);
  };

  RETURN(FALSE);
}

//
// Allocate system memory
//
void *sysAlloc(zDWORD Size)
{
	void *Block, *DlgRet;											// -> Memory block
	ENTER_PROC(sysAlloc);
	
	// Try to allocate block, if good in one go, return it
	Block=(void *)LocalAlloc(LPTR, Size);							// Allocate memory
	if (Block) RETURN(Block);										// Return block pointer
	
	// Block failed, let user clean up for a while and have options: Retry, Cancel
	TRACE("WIN: Could not allocate %u KB memory block, negotiating with user");
	DlgRet=(void *)winDialogParam(DIALOG_OUTOFMEM, OutOfMemProc, Size);
	if (DlgRet) 													// Got a block pointer?
	{
		TRACE("WIN: Memory block succesfully allocated");			// Show it worked out
		RETURN(DlgRet); 											// Return new block pointer
	}
	
	TRACE("WIN: Amnesia Error: Out of memory, user canceled memory request");
	sysExit();														// Bye Bye!

	RETURN(NULL);													// No return!
}
//
// Resize system memory
//
void *sysReAlloc(void *ptr, zDWORD Size)
{
	void *Block;													// -> Memory block
	ENTER_PROC(sysReAlloc);
	
	// Try to allocate or resize block
	if (ptr==NULL)
		Block=(void *)LocalAlloc(LPTR, Size);						// Allocate memory
	else
		Block=(void *)LocalReAlloc(ptr, Size, LMEM_MOVEABLE | LMEM_ZEROINIT); // Reallocate memory
	
	// Check if the call succeeded
	if (Block==NULL)
		sysHardExit("Could not resize memory block %08X to %u Kb (%u zBYTEs)\nError code %d", ptr, (Size+512)>>10, Size, GetLastError());

	RETURN(Block);													// Return block pointer
}



//
// Free system memory
//
void sysFree(void *Block)
{
#ifdef _DEBUG
	HLOCAL	fRet;													  // Freemem return value
	ENTER_PROC(sysFree);

	ASSERTT(Block, "Attempting to free NULL memory block");

	fRet=LocalFree(Block);											  // Attempt to free block
	ASSERTT(fRet==NULL, "Could not free memory block!");
	EXIT_PROC();
#else
	LocalFree(Block);												  // Free memory block
#endif
}

zBOOL sysHandleExceptions()
{
	return bSysHandleExceptions;
}

//
// Exit program neatly
//
/**{ sysExit, System }
@func

The sysExit function de-initializes the system and exits the program.

@params
@return
@remarks
	sysExit does not return. It does whatever is needed to exit the program gracefully. 
	It might prove wise to know what exactly is done at shutdown time on various
	platforms. This is what happens in summary:

	DOS:<BR>
	· De-initialise sound system<BR>
	· De-initialize network support<BR>
	· Unload GrIP library<BR>
	· Restore old keyboard handler<BR>
	· Set video mode back to text mode<BR>
	· Show exit message<BR>
	· Unmap linear VBE 2.0 memory<BR>
	· Flush configuration file<BR>
	· Exit<BR>

	Win32:<BR>
	· Close display object (return to windowed mode)<BR>
	· De-initialise sound system<BR>
	· De-initialise network support<BR>
	· Save window position<BR>
	· Write registry entries<BR>
	· Destroy spy<BR>
	· Destroy window interface (main window+resources)<BR>
	· Exit<BR>

@portable
@see sysHardExit
**/
void libExit()
{
	static zBOOL inSysExit=FALSE;

	ENTER_PROC(libExit);
	// Recursion check
	if (inSysExit) EXIT_PROC();
	inSysExit=TRUE;

	winSuspendThreads();											// Stop main thread if needed
	sysStopProcessingMessages=TRUE;

	TRACE("");
	TRACE("---- Exiting program");									// Show what we're doing

	netExit();														// De-initialise network
	winSaveWindowPos(); 											// Save window position for registry
	UnhookWindowsHookEx(winAppKeyboardHook);						// Remove keyboard handler

	while (DeleteMenu(hMenuApp, 0, MF_BYPOSITION)); 				// Remove windows menu

	TRACE("WIN: Closing window");
	if (hWndApp)		DestroyWindow(hWndApp); 					// Destory main window
	if (hMenuApp)		DestroyMenu(hMenuApp);						// Remove menu from memory
	if (dcScreen)		DeleteDC(dcScreen); 						// Delete screen-compatible DC
	if (cfgHKey)		RegCloseKey(cfgHKey);						// Close regisgtry key
	if (sysInstLock)	CloseHandle(sysInstLock);					// Close instance lock handle

	// Various frees and closes (the system is safe, we just need to clean up)
	if (sysCommandLine) { sysFree(sysCommandLine); sysCommandLine=NULL; }	// Free command line string

	// ExceptionHandler ReleaseCallbacks durchlaufen (nur für den Fall das D3D & co noch deinitialisiert werden müssen)
	sysKillWindowsKeys(false);
	if (sysHandleExceptions()) zexhnd.WalkReleaseCallbacks();

	TRACE("WIN: All done! Have a nice day");						// We're done
	EXIT_PROC();
}

int MasterExceptionHandler()
{
	zexhnd.WalkReleaseCallbacks();
	return EXCEPTION_CONTINUE_SEARCH;
}

//#define NO_EXC_CHECK

static int ExceptionLoop(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
	if (!sysHandleExceptions()) return HandledWinMain(hInst,hPrev,szCmdLine,sw);

	__try {
		return HandledWinMain(hInst,hPrev,szCmdLine,sw);
	}
	__except(MasterExceptionHandler()) {};

	return -1;
}
 
//
// Main windows stuff
//
int WINAPI HandledWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw);


 
typedef struct tagGInputStruct 
{
	LPTSTR lpBuf;
	DWORD length;
	LPCTSTR lpQuery;
} GInputStruct, *lpGInputStruct;


BOOL CALLBACK InputDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static lpGInputStruct lpgs;

	switch(iMsg) 
	{

		case WM_INITDIALOG:
			lpgs=(lpGInputStruct)lParam;
			SendDlgItemMessage(hwnd, ID_QUERYTEXT, WM_SETTEXT, 0,(LPARAM)lpgs->lpQuery);
			SetFocus(GetDlgItem(hwnd, ID_USERTEXT));
			return FALSE;
		case WM_COMMAND:
			switch(LOWORD(wParam)) 
			{

				case IDCANCEL:
					EndDialog(hwnd, 0);
					return TRUE;

				case IDOK:
					lpgs->length=SendDlgItemMessage(hwnd, ID_USERTEXT,WM_GETTEXT, lpgs->length, (LPARAM)lpgs->lpBuf);
					EndDialog(hwnd, lpgs->length);
					return TRUE;
			}
			break;
	}
	return FALSE;
}


zSTRING CheckPassword()
{
	const int MAX_CHARS = 80;
	char  textIn[MAX_CHARS];
	char* textOut = "Please enter password";

	GInputStruct gis;
	gis.lpBuf	= textIn;
	gis.length	= MAX_CHARS;
	gis.lpQuery = textOut;
	DialogBoxParam( GetModuleHandle(NULL), "InputDlgBox", GetFocus(), InputDlgProc, (LPARAM)&gis );

	return zSTRING(textIn);
};

#if defined(SECUROM) && !defined(COMPILING_SPACER)
#include <tchar.h>
#include "special.h"
#include "crc32.inl"
#endif

//#define CHECK_PASSWORD
#ifndef COMPILING_SPACER
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
	InitCommonControls();

#if defined(SECUROM) && !defined(COMPILING_SPACER)
#include "check.inl"
#endif

	hInstApp=hInst;
	zBOOL passwordCorrect = TRUE;

	int res = -1;
	zerr.Init(szCmdLine);

	zSTRING cmdLine(szCmdLine);
	cmdLine.Upper();

	if (cmdLine.Search("ZNOEXHND") != -1) bSysHandleExceptions = FALSE;
	else bSysHandleExceptions = TRUE;

	if (sysHandleExceptions()) zexhnd.SetIsActive(TRUE);

#ifdef CHECK_PASSWORD
	zSTRING correctAnswerScrambled	= zSTRING("FWBMHBNF");	// "evalgame", scrambled
	zSTRING correctAnswer;
	for (int i=0; i<correctAnswerScrambled.Length(); i++) {
		correctAnswer += (char)(int(correctAnswerScrambled[i])-1);
	}
	correctAnswer.Upper();

	if (cmdLine.Search(correctAnswer) == -1)
	{
		zSTRING answer			= CheckPassword();
		answer.Upper();
		if (answer != correctAnswer) passwordCorrect = FALSE;
	}
#endif
	
	if (passwordCorrect) res = ExceptionLoop(hInst,hPrev,szCmdLine,sw);

	return res;
}
#endif



int WINAPI HandledWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
{
	zLONG	wStyle; 												// Our window style
	ENTER_PROC(WinMain);

	hInstApp=hInst; 												// Save global instance

	// Do a check for multiple instances if it's now allowed
	winDoInstanceCheck();

	// Create splash screen (multi-thread for updating it)			  
	//winDoSplash();													// Do the splash screen

	// Save instance, get resources, etc
	strcpy(sysLogName, HFILE_LOG);									// Create standard log file name
	winMainThreadID=GetCurrentThreadId();							// Grab current thread ID
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &winMainThread, 0, FALSE, DUPLICATE_SAME_ACCESS); // Get main window thread handle

	// Initialise memory pool
	sysInitTimer(); 												// Init timer functions

	// Get command line stuff
	sysParseCommandLine(szCmdLine);									// Parse command line stuff

	// First installation stuff
	winTRACEMutex=CreateMutex(NULL, FALSE, NULL);					// Create mutex for TRACE
	GetModuleFileName(NULL, winAppEXEName, sizeof(winAppEXEName));	// Get name of executable

	InitCommonControls();											// Load common controls DLL
																
	// Wipe out mouse stuff before anybody tries to use it			  
	memZero(&mouseInf, sizeof(mouseInf));							// Wipe out mouse data
																
	winInitSystem();												// Check if system is OK
	kbInit();

	// Load executable into memory if we're on a slow medium
//	if (DetachFromMedium(hInstApp, DETACH_ALWAYS | DETACH_COMMONPAGES)==FALSE)	// Detach from medium
//		TRACE("WIN: Warning - Failed to load executable into memory");	// Failed!

	// First of all, create a screen-compatible DC					  
	dcScreen=CreateCompatibleDC(NULL);								// Create DC compatible with screen

	//sysInitPower(); 												// Initialise power functions
	winCalcSizes(); 												// Check sizes of things
	winCreateClasses(); 											// Create window classes

	// Set defaults for spy window and normal window, overriden from registry
	iwPos.Valid=FALSE;												// Not valid
	// [BENDLIN] Addon Patch - Workarea for WindowPos
	iwPos.xMain = iwPos.yMain = 0;
	RECT rectWorkArea;
	if (SystemParametersInfo(SPI_GETWORKAREA, 0, &rectWorkArea, 0))
	{
		if ((rectWorkArea.left >= 0) && (rectWorkArea.top >= 0))
		{
			iwPos.xMain = rectWorkArea.left;
			iwPos.yMain = rectWorkArea.top;
		}
	}
	iwPos.xSpy=iwPos.ySpy=-0x70000000;								// Default positions for spy
	iwPos.wMain=800+winExtraX; iwPos.hMain=600+winExtraY;			// Default sizes of our window
	iwPos.wSpy=iwPos.hSpy=-0x70000000;								// Default sizes for spy
	iwPos.maxMain=iwPos.maxSpy=0;									// No maximize

	int	wPosSize=sizeof(iwPos);										// Size of window pos structure
	cfgGetBinary("System", "Window Position", (zBYTE *)&iwPos, &wPosSize);
																
	// Create a window for our application							  
#ifndef COMPILING_SPACER
	wStyle = WS_CAPTION | WS_SYSMENU;  // &~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
#else
	wStyle = WS_OVERLAPPEDWINDOW;										// Standard style
#endif
	if (iwPos.maxMain)												// Maximize window if user's choice
	{
		wStyle |= WS_MAXIMIZE;
		sw=SW_SHOWMAXIMIZED;
	}

	hWndApp=CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, 				// Extended style
							"DDWndClass",							// Class name
							APP_NAME,								// Caption
							wStyle & (~WS_VISIBLE), 				// Style
							iwPos.xMain, iwPos.yMain,				// Position
							iwPos.wMain, iwPos.hMain,				// Size
							(HWND)NULL, 							// Parent window (no parent)
							(HMENU)NULL,							// Use class menu
							hInstApp,								// Handle to window instance
							(LPSTR)NULL);							// No params to pass on
	if (!hWndApp) return FALSE; 									// Can't create main window

	netInit();														// Initialise network

	// Start game													  
	TRACE("---- Starting execution: invoke MainProg()");			// Show what we're doing
	TRACE("");

	// TEST

//	zSTRING cmdLine(szCmdLine);
//	cmdLine.Upper();

//	if (cmdLine.Search("DEVMODE") == -1) SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

	MainProg();

	libExit();

	RETURN(0);
}

#if defined(SECUROM) && defined(COMPILING_SPACER)
#include <tchar.h>
#include "special.h"
#include "crc32.inl"
#endif

int initializeSystemMFC()
{
	InitCommonControls();

#if defined(SECUROM) && defined(COMPILING_SPACER)
#include "check.inl"
#endif
	
	zLONG	wStyle; 												// Our window style
	ENTER_PROC(WinMain);

	// Do a check for multiple instances if it's now allowed
	winDoInstanceCheck();

	// Save instance, get resources, etc
	strcpy(sysLogName, HFILE_LOG);									// Create standard log file name
	winMainThreadID=GetCurrentThreadId();							// Grab current thread ID
	DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &winMainThread, 0, FALSE, DUPLICATE_SAME_ACCESS); // Get main window thread handle

	// Initialise memory pool
	sysInitTimer(); 												// Init timer functions

	// First installation stuff
	winTRACEMutex=CreateMutex(NULL, FALSE, NULL);					// Create mutex for TRACE
	GetModuleFileName(NULL, winAppEXEName, sizeof(winAppEXEName));	// Get name of executable

	InitCommonControls();											// Load common controls DLL
																
	// Wipe out mouse stuff before anybody tries to use it			  
	memZero(&mouseInf, sizeof(mouseInf));							// Wipe out mouse data
																
	winInitSystem();												// Check if system is OK

//	kbInitMask();

	// First of all, create a screen-compatible DC					  
	dcScreen=CreateCompatibleDC(NULL);								// Create DC compatible with screen

	//sysInitPower(); 												// Initialise power functions
	winCalcSizes(); 												// Check sizes of things
	winCreateClasses(); 											// Create window classes

	// Set defaults for spy window and normal window, overriden from registry
	iwPos.Valid=FALSE;												// Not valid
	// [BENDLIN] Addon Patch - Workarea for WindowPos
	iwPos.xMain = iwPos.yMain = 0;
	RECT rectWorkArea;
	if (SystemParametersInfo(SPI_GETWORKAREA, 0, &rectWorkArea, 0))
	{
		if ((rectWorkArea.left >= 0) && (rectWorkArea.top >= 0))
		{
			iwPos.xMain = rectWorkArea.left;
			iwPos.yMain = rectWorkArea.top;
		}
	}
	iwPos.xSpy=iwPos.ySpy=-0x70000000;								// Default positions for spy
	iwPos.wMain=320+winExtraX; iwPos.hMain=240+winExtraY;			// Default sizes of our window
	iwPos.wSpy=iwPos.hSpy=-0x70000000;								// Default sizes for spy
	iwPos.maxMain=iwPos.maxSpy=0;									// No maximize
																
	// Create a window for our application							  
#ifndef COMPILING_SPACER
	wStyle = WS_CAPTION | WS_SYSMENU;
#else
	wStyle = WS_OVERLAPPEDWINDOW;										// Standard style
#endif
	netInit();													// Init timer functions
	
	return 0;
}

//
// Check if another instance of this app is already running, if so -> exit immediately
//
void winDoInstanceCheck()
{
	CHAR	mapLockName[MAX_PATH];								// Name of program lock

	// Try to get a file mapping. If it already exists, an instance is already running
	sprintf(mapLockName, "Lock_%s", REG_PROGRAM);				// Set lock name
	sysInstLock=CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READONLY, 0, 32, mapLockName);
	if ((sysInstLock) && (GetLastError()==ERROR_ALREADY_EXISTS)) ExitProcess(1);
}



//
// Initialise keyboard routines
//
void kbInit()
{
	// Set keyboard hook, then init keyboard mask
//	winAppKeyboardHook=SetWindowsHookEx(WH_KEYBOARD, AppKeyboardHook, NULL, GetCurrentThreadId());
//	if (winAppKeyboardHook==NULL) sysHardExit("Could not obtain keyboard hook!");
//	kbInitMask();													// Init keyboard mask
}


//
// Register window classes
//
INLINE static void winCreateClasses()
{
	static char ClassErr[]="Could not register window class"; 		// Class creation error
	WNDCLASS cls;													// Our window class
	
	// Register a class for the main application window
	memZero(&cls, sizeof(cls));
#ifdef COMPILING_SPACER
	hMenuApp			= CreateMenu(); 							// Create empty menu
#endif
//	hIconApp			= LoadIcon(hInstApp, MAKEINTRESOURCE(ICON_APP));
	hIconApp			= LoadIcon(hInstApp, MAKEINTRESOURCE(IDR_GOTHIC)); // [BENDLIN]
#ifndef COMPILING_SPACER
	// [BENDLIN] Fenster kann nicht per Menü geschlossen werden,
	// und komplettes Neuzeichen bei Änderungen ist nicht notwendig!
	cls.style 			= CS_NOCLOSE;
#else
	cls.style 			= CS_VREDRAW | CS_HREDRAW;
#endif
	cls.lpfnWndProc		= (WNDPROC)AppWndProc;
	cls.hInstance 		= hInstApp;
	cls.hIcon 			= hIconApp;
    // [BENDLIN] Die Hintergundfarbe für den Client-Bereich ist schwarz
	// (fällt weniger auf, außerdem stehen mehr drauf als auf weiß;)
#ifndef COMPILING_SPACER
	cls.hbrBackground	= HBRUSH(GetStockObject(BLACK_BRUSH));
#endif
	cls.lpszClassName	= "DDWndClass";

	if (!RegisterClass(&cls)) sysHardExit(ClassErr);
	
	// Register a class for Network support (Winsock)
	memZero(&cls, sizeof(cls));
	cls.lpfnWndProc		= (WNDPROC)netWindowProc;
	cls.hInstance 		= hInstApp;
	cls.lpszClassName	= "DDWinSock";
	if (!RegisterClass(&cls)) sysHardExit(ClassErr);
}

//
// Create Win32 App menu
//
void winCreateMenu()
{
#ifndef COMPILING_SPACER
	return;
#endif
	
	LPMENUITEM	pMenu=sysMenu;										// -> Current menu
	LPVIDMODE   pMode;												// -> 
	MENUITEMINFO mItem; 											// Menu item info
	HMENU	menuStack[8];											// Up to 8 levels nesting
	zDWORD	menuPos[8]; 											// Position in menu
	zLONG	aMenu, i;												// Active menu, counter
	zLONG	LastType=-1, Type;										// Last entry's type & new type
	zDWORD	vmodeIdx=0; 											// Mode index, Mode zDWORD
	CHAR	mText[128]; 											// Menu text
	zDWORD	sState; 												// Saved menu state
	ENTER_PROC(winCreateMenu);
	// Don't make a menu in fullscreen mode
	if (isFullScreen()) EXIT_PROC();								// Bye!
	
	// If there is a menu callback, call it now!
	if (sysMenuCallback!=NULL) sysMenuCallback(0);					// Do callback

	// Delete old menu (but can't destroy, we must keep the same menu handle)
	while (DeleteMenu(hMenuApp, 0, MF_BYPOSITION)); 				// Remove items
	if (vidHideMenu) EXIT_PROC();									// Hidden, don't show items
	
	// Start making a menu
	aMenu=0;														// Current menu
	menuStack[0]=hMenuApp;											// Root menu is application
	menuPos[0]=0;													// Position in menu
	while ((pMenu->Type & 0xFF)!=MENU_END_OF_MENU)					// Until we find an end marker
	{
		if ((pMenu->Type & MENUSTYLE_HIDDEN)==0)
		{
			// If it's one of the default menu items, already load the menu item with text
			memZero(&mItem, sizeof(mItem)); 						// Wipe out menu item
			mItem.cbSize=sizeof(mItem); 							// Set size
			mItem.fMask=MIIM_TYPE | MIIM_STATE | MIIM_ID;			// Set type, state and ID
			mItem.fType=MFT_STRING; 								// Text!
			mItem.wID=ID_USERMENU+(pMenu-sysMenu);					// ID=Index in menu
			
			// Set text for item if needed
			Type=pMenu->Type & 0xFF;								// Get new type
			if ((Type!=MENU_ENDSUBMENU) && (Type!=MENU_LINE))
			{
				mItem.dwTypeData=pMenu->Text;						// Set text for item
				mItem.cch=strlen(pMenu->Text);						// Size of text
			}
			
			// Set grayed and checked states if required
			if (pMenu->Type & MENUSTYLE_GRAYED) 					// Disabled?
				mItem.fState|=MFS_GRAYED;							// Menu item is grayed
			if (pMenu->Type & (MENUSTYLE_CHECK | MENUSTYLE_RADIOCHECK))   // Checked or Radiochecked?
				mItem.fState|=MFS_CHECKED;							// Check
			if (pMenu->Type & (MENUSTYLE_RADIOCHECK))				// Radiochecked?
				mItem.fType|=MFT_RADIOCHECK;						// Radio check thing
			
			// Remove double separators
			if ((Type==MENU_LINE) && (LastType==MENU_LINE)) Type=MENU_NONE; // Wipe out second separator
			
			// Add menu items depending on type
			switch (Type)
			{
			case	MENU_SUBMENU:									// Create new submenu
					ASSERTT(aMenu<7, "Menu nesting too deep");
					menuStack[aMenu+1]=CreateMenu();				// Create empty submenu
					menuPos[aMenu+1]=0; 							// Position 0 in new menu
					// Insert new submenu
					mItem.fMask|=MIIM_SUBMENU;						// Submenu too
					mItem.hSubMenu=menuStack[aMenu+1];				// Submenu
				
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					aMenu++;										// Increase nesting
					LastType=MENU_SUBMENU;							// Update last type value
					break;
				
			case	MENU_ENDSUBMENU:								// End of sub-menu (walk down menu stack)
					ASSERTT(aMenu>0, "Negative menu nesting");
					if (LastType==MENU_LINE) RemoveMenu(menuStack[aMenu], --menuPos[aMenu], MF_BYPOSITION);
					LastType=MENU_ENDSUBMENU;						// Update last type value
					aMenu--;
					break;
				
			case	MENU_LINE:										// Horizontal separator line
					mItem.fType=MFT_SEPARATOR;						// Separator
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_LINE; 							// Update last type value
					break;
				
			case	MENU_TOGGLE:									// Toggle menu item, set check, depending on BOOL value
					if (*((zBOOL *)pMenu->pCommand)) mItem.fState|=MFS_CHECKED;
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_TOGGLE;							// Update last type value
					break;
				
			case	MENU_TOGGLEBMASK:								// Toggle menu item, set check, depending on zBYTE mask
					if (*((zBYTE *)pMenu->pCommand) & (zBYTE)pMenu->CommandData) mItem.fState|=MFS_CHECKED;
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_TOGGLEBMASK;						// Update last type value
					break;
				
			case	MENU_TOGGLEDMASK:								// Toggle menu item, set check, depending on zDWORD mask
					if (*((zDWORD *)pMenu->pCommand) & (zDWORD)pMenu->CommandData) mItem.fState|=MFS_CHECKED;
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_TOGGLEDMASK;						// Update last type value
					break;
				
			case	MENU_RADIO: 									// Radio button, set check depending on zLONG variable match
					if (*((zDWORD *)pMenu->pCommand) == (zDWORD)pMenu->CommandData) mItem.fState|=MFS_CHECKED;
					mItem.fType|=MFT_RADIOCHECK;					// Radio check thing
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_RADIO;							// Update last type value
					break;
				
			case	MENU_SOUNDMUS:									// Sound and music properties, disable if no audio support
					break;
				
			case	MENU_MUTEMUS:									// Mute music, check if music is muted now
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_MUTEMUS;							// Update last type value
					break;
				
			case	MENU_MUTESND:									// Mute music, check if music is muted now
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_MUTESND;							// Update last type value
					break;
				
			case	MENU_PAUSE: 									// Pause, check if it is checked because Pause is active
					if (usrWantPause) mItem.fState|=MFS_CHECKED;	// Paused!
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_PAUSE;							// Update last type value
					break;
				
			case	MENU_VID_BPP:									// Video bit depths
					if (!winSetVideoMode) break;					// Must have bit depth proc
					sState=mItem.fState;							// Always use same state
					mItem.fType|=MFT_RADIOCHECK;					// Radio checked string entry
					mItem.dwTypeData=mText; 						// Set text for bit depth
					for (i=0; i<4; i++) 							// Check for 4 bit depths
					{
						if (vidShowBitDepths & (1<<i))				// Show this one?
						{
							// Add menu item
							mItem.fState=sState|(((VideoBPP/8)-1==(zLONG)i)*MFS_CHECKED);  // Check if bit mode is current
							if ((vidEnableBitDepths & (1<<i))==0) mItem.fState|=MFS_GRAYED;
							mItem.wID=ID_VIDEO_8BIT+i;				// Item ID is bit depth set
							sprintf(mText, pMenu->Text, (i+1)*8);	// Bit depth description
							mItem.cch=strlen(mText);				// Size of entry
							InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
							LastType=MENU_VID_BPP;					// Update last type value
						}
					}
					break;
				
			case	MENU_VID_WINMODES:								// Standard window sizes (as supported by app)
					if (!vidModeFilter) break;						// Must have vmode proc
					sState=mItem.fState;							// Always use same state
					mItem.fType|=MFT_RADIOCHECK;					// Radio checked string entry
					mItem.fMask|=MIIM_DATA; 						// Mask for filled entries
					mItem.dwTypeData=mText; 						// -> Text for resolution
					
					// Check all windowed video modes from the video mode list
					for (i=vidnModes-1, pMode=vidpModes+i; i>=0; i--, pMode--) // Go through video modes
					{
						if ((pMode->hwModeType==VIDMODE_DIB) && (vidGotMode[VIDMODE_DDRAWWIN])) break;
						if ((isVModeWindowed(pMode)) && (pMode->si.BPP==VideoBPP) && (vidModeFilter(pMode)))
						{
							// Add resolution item (normal window size)
							if (vmodeIdx==64) break;				// Enough is enough!
							sprintf(mText, pMenu->Text, pMode->si.Width, pMode->si.Height);
							mItem.dwItemData=vidDefSize[i]; 		// Data parameter is window size
							mItem.fState=sState | (((pMode->si.Width==(zDWORD)VideoW) && (pMode->si.Height==(zDWORD)VideoH))*MFS_CHECKED);  // Check if size is current
							mItem.cch=strlen(mText);				// Length of text string for resolution
							mItem.wID=ID_VIDEO_VMODESET+vmodeIdx;
							winUserModeList[vmodeIdx++]=MAKEDWORD(pMode->si.Width, pMode->si.Height) | (VideoHwModeCur.hwModeType << 28);
							InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
							LastType=MENU_VID_WINMODES; 			// Update last type value
						}
					}
					break;
				
			case	MENU_VID_FSMODES:  // Add fullscreen modes
					if (!vidModeFilter) break;			// Must have VMode proc
					mItem.dwTypeData=mText; 			// -> Text for resolution
					for (i=vidnModes-1, pMode=vidpModes+i; i>=0; i--, pMode--) // Go through video modes
					{
						if ((isVModeFullScreen(pMode)) && (pMode->si.BPP==VideoBPP) && (vidModeFilter(pMode)))
						{
							// Add resolution item (normal window size)
							if (vmodeIdx==64) break;
							
							// Set text for mode
							sprintf(mText, pMenu->Text, pMode->si.Width, pMode->si.Height, "DirectDraw");
							
							// Set rest of item
							mItem.wID=ID_VIDEO_VMODESET+vmodeIdx;  // Set video mode ID
							mItem.cch=strlen(mText);
							winUserModeList[vmodeIdx++]=MAKEDWORD(pMode->si.Width, pMode->si.Height) | (pMode->hwModeType<<28);
							InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
							LastType=MENU_VID_FSMODES;
						}
					}
					break;
				
			case	MENU_VID_FSTRETCH: // Free scale menu toggle
					if (vidWindowStretch!=VIDSTRETCH_USER) break;
					if (vidFreeStretch) mItem.fState|=MFS_CHECKED;
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=MENU_VID_FSTRETCH; 		// Update last type value
					break;
				
			case	MENU_NONE:
					break;
				
			default:												// Default item (just add text string)
					InsertMenuItem(menuStack[aMenu], menuPos[aMenu]++, TRUE, &mItem);
					LastType=Type;
					break;
			}
		}
		pMenu++;													// -> Next menu item
	}

	// Redraw!
	SetMenu(hWndApp, hMenuApp); 									// Make sure it's liked to it
	DrawMenuBar(hWndApp);											// Update display

	EXIT_PROC();
}

//
// KeyboardProc - Hook for keyboard messages, allows us to receive ALL keyboard messages!
//
static LRESULT CALLBACK AppKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
/*	static	zBOOL KillPause=FALSE;									// Kill pause key press?
	zBYTE	NewState;												// State=Up or down?
	zDWORD	Extended;												// Extended key bit
	ENTER_PROC(AppKeyboardHook);
	
	// Check to see if we can process it or pass it on
	if (nCode<0)													// Pass on?
		{ RETURN (CallNextHookEx(winAppKeyboardHook, nCode, wParam, lParam)); } // Call next hook in chain 
	else
	{
		NewState=(((zLONG)lParam)>=0);								// New keyboard state (bit 31)
		Extended=(lParam & 0x1000000)>>16;							// Flag set when extended key
		if (winMinimized) NewState=0;								// When minimized, all keys go DOWN

		// Special case: There is no difference between left and right shift, except for scancode
		if (NewState==1)
		{
			//sysPowerBusy(); 										// User did something
			if ((wParam==KEY_F4) && (GetAsyncKeyState(VK_MENU) & 0x8000)) usrWantQuit=2; // User wants to quit!
		}
		if ((wParam<256) && (!winInMenu))							// Normal chars only!
		{
			// Pause key is special (it has no keyup message and is forced to be a toggle)
			if (wParam==KEY_PAUSE)
			{
				if (KillPause==FALSE) kbMask[KEY_PAUSE | Extended]^=1; // One in 2 pauses is discarded
				KillPause^=1;										// Kill every other pause press
			}
			else if ((wParam==KEY_ENTER) && (NewState==1) && (!vidDisableAltEnter) && (kbMask[KEY_LALT] || kbMask[KEY_RALT]))
			{
				// ALT-Return video mode switch
				sysEventToggleFullScreen^=1;						// Pressed once more
			}
			else
			{
				int Code = wParam | Extended;						// Key code

				// Check for special "toggle" keys
				if (Code==KEY_CAPSLOCK)
					kbMask[KEY_CAPS_TOGGLE]		= GetKeyState(KEY_CAPSLOCK) & 1;
				else if (Code==KEY_SCROLLLOCK)
					kbMask[KEY_SCROLL_TOGGLE]	= GetKeyState(KEY_SCROLLLOCK) & 1;
				else if (Code==KEY_NUMLOCK)
					kbMask[KEY_NUM_TOGGLE]		= GetKeyState(KEY_NUMLOCK & 0xFF) & 1;

				// Adjust keyboard buffer and keyboard mask
				kbKeyBuffer[kbKeyIndex++ & 0xFF]=Code | (NewState ? 0 : KEY_RELEASE);
				kbToggledMask[Code] = (kbMask[Code] != NewState);

				kbMask[Code]=NewState; 								// Set new key state
			}
			
		}
		
		RETURN(0);													// Allow code for window proc
	}*/
	return 0;
}
void HandleFocusLoose()
{
	if ( zrenderer )
	{
		if (zrenderer->Vid_GetScreenMode()==zRND_SCRMODE_FULLSCREEN)
		{
			zERR_WARNING("C: lost focus in fullscreen, setting to windowed mode");
			zrenderer->SetSurfaceLost(TRUE);
			#ifdef COMPILING_GOTHIC
			#ifndef COMPILING_SPACER
			if (ogame) ogame->Pause();
			#endif
			#endif

			zrenderer->Vid_SetScreenMode(zRND_SCRMODE_WINDOWED);
			SetWindowPos(hWndApp, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSENDCHANGING | SWP_NOSIZE);
			bLostFocus = TRUE;
		}
	}
};

//
// Windows procedure
//
static LRESULT CALLBACK AppWndProc(HWND hwnd, zUWORD msg, WPARAM wParam, LPARAM lParam)
{
	LPMINMAXINFO	winMinMax;										// Minimum and maximum sizes of window
	LRESULT winRes; 												// Result value
	VIDMODE NewMode;												// New video mode
	LPRECT	WinSize;												// Window size
	RECT	rectWorkArea;											// Working area on screen
	RECT	cWinSize;												// Window size for clipping
	zLONG	ExWin;													// Extra space
	zDWORD	i, FacX, FacY;											// Counter, factor X and factor Y
#ifdef COMPILING_SPACER
	zLONG	rVal;													// Return value, general counter
	HRGN	newRgn; 												// New region for caption drawing
#endif
	ENTER_PROC(AppWndProc);

	// Because there is a lot of stuff happening in the message proc
	// we might want to stop processing messages somtimes (at exit)
	if (sysStopProcessingMessages)
	{
		winRes=DefWindowProc(hwnd, msg, wParam, lParam);			// Default handler
		RETURN(winRes); 											// Return result
	}

	switch (msg) {
//	case	WM_KILLFOCUS:
//			memset(kbMask, 0, MAX_KEYS);							// Wipe mask (nothing pressed)
//			break;
	
//	case	WM_SETFOCUS:
//			kbInitMask();											// Reset keyboard mask	
//			break;

	case	WM_CREATE:
			ccMain.hDC=NULL;										// No device context yet
			ccMain.hBmp=NULL;										// No bitmap yet
			ccMain.hIcon=hIconApp;									// Icon for window
			ccMain.iButtons=1+2+4;									// All buttons
			ccMain.bSizeBorder=TRUE;								// Sizing frame
			ccMain.bmpBackground=NULL;								// No background picture
			ccRenderCaption(hwnd, &ccMain); 						// Init caption renderer
			break;

	case	WM_CLOSE:
			usrWantQuit=1;											// User wants to exit!
			RETURN(0);

	case	WM_ERASEBKGND:
			RETURN(TRUE);											// No background!

	case	WM_INITMENU:
			winCreateMenu();										// Create video mode menu
			RETURN(0);												// Processed message

	case	WM_ENTERMENULOOP:
			winInMenu=TRUE;
			RETURN(0);

	case	WM_EXITMENULOOP:
			winInMenu=FALSE;
//			kbLoseAllKeys();										// Clears pressed state, etc
			RETURN(0);

	case	WM_DEADCHAR:
//	case	WM_CHAR:
//			if (!winInMenu)
//				kbCharBuffer[kbCharIndex++ & 0xFF]=(CHAR)wParam;	// Store key in buffer
//			RETURN(0);

  // Power management

	// Lose activation when being disactivated in fullscreen mode
	case	WM_ACTIVATE:

			// da hat sich ein anderes programm den focus geholt, das kann passieren, für den fall das 
			// der gfx treiber kein surface rescue beherrscht, gibt es dann einen crash :(
			// TOPIC: einen taskwechsel zu unterbinden kann man niemals 100% ig. deswegen sollte man nur ein 
			// paar grundlegende funktionen sperren (z.B. Winkeys, Alt-Tab), aber niemals davon ausgehen das ein Focuswechsel
			// _niemals_ passieren wird
			zERR_MESSAGE(8,0,"C: WM_ACTIVATE received");
			if ( LOWORD(wParam)==WA_INACTIVE )
				HandleFocusLoose();
 
			break;	  

	// Lose activation when receiving WM_CANCELMODE in fullscreen mode
	case	WM_CANCELMODE:
			zERR_MESSAGE(8,0,"C: WM_CANCELMODE received");
			HandleFocusLoose();

			//RETURN(0);

//			if (isActiveFullScreen()) sysEventToggleFullScreen=TRUE;
			break;

	// Activate or disactivate app by a different program
	case	WM_ACTIVATEAPP:
			zERR_MESSAGE(8,0,"C: WM_ACTIVATEAPP received");
			if (wParam==FALSE)
				HandleFocusLoose();

			//usrWantPause=(wParam==FALSE);							// User wants to pause if focus is lost
			break;

	// System command
	case	WM_SYSCOMMAND:
			switch (wParam & 0xFFF0) {
			case	SC_KEYMENU:
					// Check to see if menu is blocked
					if (vidDisableMenuKeys) RETURN(0);
					break;

			case	SC_SCREENSAVE:
					// Check if the screensaver is blocked
					RETURN(FALSE);


					if ((sysPowerOptions & PWR_NOSCREENSAVE) || (sysGetTime()<sysPowerNextAllowedScrSave)) RETURN(FALSE);

					// Activate screensaver
					TRACE("WIN: Screensaver activating");
					zERR_WARNING("C: tried to activate screen saver... ignoring..." );
					//sysEventScreenBlanked=TRUE; 					// Set wait flag
					break;

			case	SC_MONITORPOWER:

					RETURN(FALSE);
					// Check if monitor low-power mode is blocked
					if ((sysPowerOptions & PWR_NOSCREENSAVE) || (sysGetTime()<sysPowerNextAllowedLowPower)) RETURN(FALSE);

					// Go to low-power mode
					TRACE("WIN: Monitor low-power activating");
					zERR_WARNING("C: tried to monitor low power... ignoring..." );
					sysEventScreenBlanked=TRUE; 					// Set wait flag
					break;

			case	SC_MINIMIZE:
					if (vidAllowMinimizeWindow && isWindowed()) break; // Allow default handler to process it
					vidMinimize(TRUE);								// Minimize and wait
					RETURN(FALSE);									// Processed!
			}
			break;

	// Command
	case	WM_COMMAND:
			AppCommand(hwnd, msg, wParam, lParam);
			break;

	// Any mouse buttons down
	case	WM_LBUTTONDOWN:
	case	WM_RBUTTONDOWN:
	case	WM_MBUTTONDOWN:
			SetForegroundWindowEx(hwnd);

	// Any mouse buttons up or down
	case	WM_LBUTTONUP:
	case	WM_RBUTTONUP:
	case	WM_MBUTTONUP:

	// Any mouse message
	case	WM_MOUSEMOVE:	   
			inCreateMouseMessage(wParam, lParam); 
			break; 

	case	WM_GETMINMAXINFO:
			winMinMax=(LPMINMAXINFO)lParam; 						// winMinMax -> WINDOW SIZES
			if ((VideoW<=0) || (VideoH<=0)) RETURN(TRUE);
			if (vidWindowStretch!=VIDSTRETCH_CALLBACK)
			{
				winMinMax->ptMinTrackSize.x=VideoW+winExtraX;
				winMinMax->ptMinTrackSize.y=VideoH+winExtraY;
			}
			RETURN(0);

	case	WM_SIZE:
			GetClientRect(hwnd, &winWindowSize);					// Refetch size
			GetWindowRect(hwnd, &cWinSize); 						// Get size of window
			ccCHECK_RESIZE(ccMain, hwnd, cWinSize); 				// Check & Render caption
			if ((isActiveWindowed()) && (vidWindowStretch==VIDSTRETCH_CALLBACK))
			{
				ASSERT(winSetVideoMode);							// Must have callback!
				memcpy(&NewMode, &VideoModeCur, sizeof(VIDMODE));   // Clone current video mode
				NewMode.si.Width=winWindowSize.right-1; 			// Set width of new video mode
				NewMode.si.Height=winWindowSize.bottom-1;			// Set height of new video mode
				winSetVideoMode(&NewMode);							// Set new video mode
			}
			RETURN(0);												// Continue processing

	case	WM_SIZING:
			WinSize=(LPRECT)lParam; 								// winSize -> WINDOW SIZES

			if ((vidFreeStretch==TRUE) || (VideoW<=0) || (VideoH<=0)) RETURN(TRUE);

			// Get working area for windows
			SystemParametersInfo(SPI_GETWORKAREA, 0, &rectWorkArea, 0);

			// No resize?
			if (vidWindowStretch==VIDSTRETCH_NONE)
			{
				// Don't allow resize
				if ((wParam == WMSZ_LEFT)	|| (wParam == WMSZ_BOTTOMLEFT)		|| (wParam == WMSZ_TOPLEFT))		WinSize->left=WinSize->right-VideoW-winExtraX;
				if ((wParam == WMSZ_RIGHT)	|| (wParam == WMSZ_BOTTOMRIGHT) 	|| (wParam == WMSZ_TOPRIGHT))		WinSize->right=WinSize->left+VideoW+winExtraX;
				if ((wParam == WMSZ_TOP)	|| (wParam == WMSZ_TOPLEFT) 		|| (wParam == WMSZ_TOPRIGHT))		WinSize->top=WinSize->bottom-VideoH-winExtraY;
				if ((wParam == WMSZ_BOTTOM) || (wParam == WMSZ_BOTTOMLEFT)		|| (wParam == WMSZ_BOTTOMRIGHT))	WinSize->bottom=WinSize->top+VideoH+winExtraY;

				RETURN(TRUE);										// Done!
			}
			else if (vidWindowStretch==VIDSTRETCH_CALLBACK) RETURN(TRUE);

			// Adjust left side of rectable
			if ((wParam == WMSZ_LEFT) || (wParam == WMSZ_BOTTOMLEFT) || (wParam == WMSZ_TOPLEFT))
			{
				ExWin=(((((WinSize->right-WinSize->left-winExtraX)+VideoW/2)/VideoW)*VideoW)+winExtraX);
				while ((WinSize->right-ExWin)<rectWorkArea.left) ExWin-=VideoW;
				WinSize->left=WinSize->right-ExWin;
			}

			// Adjust right side of rectable
			if ((wParam == WMSZ_RIGHT) || (wParam == WMSZ_BOTTOMRIGHT) || (wParam == WMSZ_TOPRIGHT))
			{
				ExWin=(((((WinSize->right-WinSize->left-winExtraX)+VideoW/2)/VideoW)*VideoW)+winExtraX);
				while ((WinSize->left+ExWin)>rectWorkArea.right) ExWin-=VideoW;
				WinSize->right=WinSize->left+ExWin;
			}

			// Adjust top of rectangle
			if ((wParam == WMSZ_TOP) || (wParam == WMSZ_TOPLEFT) || (wParam == WMSZ_TOPRIGHT))
			{
				ExWin=(((((WinSize->bottom-WinSize->top-winExtraY)+VideoH/2)/VideoH)*VideoH)+winExtraY);
				while ((WinSize->bottom-ExWin)<rectWorkArea.top) ExWin-=VideoH;
				WinSize->top=WinSize->bottom-ExWin;
			}

			// Adjust bottom of rectangle
			if ((wParam == WMSZ_BOTTOM) || (wParam == WMSZ_BOTTOMLEFT) || (wParam == WMSZ_BOTTOMRIGHT))
			{
				ExWin=(((((WinSize->bottom-WinSize->top-winExtraY)+VideoH/2)/VideoH)*VideoH)+winExtraY);
				while ((WinSize->top+ExWin)>rectWorkArea.bottom) ExWin-=VideoH;
				WinSize->bottom=WinSize->top+ExWin;
			}

			// Update new sizing parameters with user selection presets
			FacX=(WinSize->right-WinSize->left-winExtraX)/VideoW;
			FacY=(WinSize->bottom-WinSize->top-winExtraY)/VideoH;

			if ((FacX==1) && (FacY==1))
			{
				// Default 1x1 size, if there was a preset, remove it now
				for (i=0; i<winSnapSizes; i++)
				{
					// Remove screen size if there
					if ((zDWORD)MAKELONG(VideoW, VideoH)==winSnapSize[i*2])
					{
						// Last entry, then just decrease last element counter, else move entry up
						if (i!=(winSnapSizes-1))
						{
							// Copy entry so that the last in the row can be deleted
							winSnapSize[i*2]=winSnapSize[(winSnapSizes-1)*2];
							winSnapSize[i*2+1]=winSnapSize[(winSnapSizes-1)*2+1];
						}
						winSnapSizes--;
					}
				}
			}
			else
			{
				for (i=0; i<winSnapSizes; i++)
				{
					// Modify any exisiting entries
					if ((zDWORD)MAKELONG(VideoW, VideoH)==winSnapSize[i*2])
						{ winSnapSize[i*2+1]=MAKELONG(FacX, FacY); break; }
				}

				// Add new entry if new preset
				if ((i==winSnapSizes) && (winSnapSizes<32))
				{
					winSnapSize[i*2]=MAKELONG(VideoW, VideoH);
					winSnapSize[i*2+1]=MAKELONG(FacX, FacY);
					winSnapSizes++; 								// Got one more
				}
			}

			RETURN(TRUE);

#ifdef COMPILING_SPACER

	// When left button is pressed, the caption is fucked up, restore caption ASAP (but can't prevent :(
	case	WM_NCLBUTTONDOWN:
			if ((winMode==VIDMODE_ANYFULLSCREEN) || ccMain.bActive==FALSE) break;
			DefWindowProc(hwnd, WM_NCLBUTTONDOWN, wParam, lParam);
			ccDrawCaption(hwnd, &ccMain, GetActiveWindow()==hwnd, NULL);
			RETURN(TRUE);

	case	WM_NCACTIVATE:
			// No clipping supplied, create clipping region at the size of the entire window
			if (!isActiveWindowed()) break; 						// Don't do stuff when not active windowed
			if (ccMain.bActive==FALSE) break;						// No processing, caption is off
			ccDrawCaption(hwnd, &ccMain, (zBOOL)wParam, NULL);		// Draw caption with clipping region
			RETURN(TRUE);											// All fine

	// Settext destroys the caption, restore caption ASAP
	case	WM_SETTEXT:
			if ((winMode==VIDMODE_ANYFULLSCREEN) || ccMain.bActive==FALSE) break;
			LockWindowUpdate(hwnd);
			DefWindowProc(hwnd, WM_SETTEXT, wParam, lParam);
			LockWindowUpdate(NULL);
			ccDrawCaption(hwnd, &ccMain, GetActiveWindow()==hwnd, NULL);
			RETURN(TRUE);

	case	WM_NCPAINT:
			// If window resized, rerender caption
			if (!isActiveWindowed()) RETURN(FALSE); 				// Don't do stuff when not active windowed
			GetWindowRect(hwnd, &cWinSize); 						// Get size of window
			ccCHECK_RESIZE(ccMain, hwnd, cWinSize); 				// Check & Render caption

			// If no clipping supplied, create clipping area at the size of the entire window
			if (ccMain.bActive==FALSE) break;						// No processing, caption is off
			if (wParam<=1)											// No clipping region supplied?
			{
				// Draw caption with a fresh new region we create of our own
				newRgn=CreateRectRgnIndirect(&cWinSize);											  // Create new region at size of window
				ccDrawCaption(hwnd, &ccMain, GetActiveWindow()==hwnd, newRgn);
				rVal=DefWindowProc(hwnd, msg, (WPARAM)newRgn, lParam);
				DeleteObject(newRgn);								// Delete clipping region
			}
			else
			{
				// Draw caption with the specified clipping region (wParam)
				ccDrawCaption(hwnd, &ccMain, GetActiveWindow()==hwnd, (HRGN)wParam);
				rVal=DefWindowProc(hwnd, msg, wParam, lParam);
			}
			RETURN(rVal);											// Done!

	case	WM_SYSCOLORCHANGE:
	case	WM_DEVMODECHANGE:
	case	WM_SETTINGCHANGE:	 
			winBPP=GetDeviceCaps(dcScreen, BITSPIXEL);				// Windows display mode depth
			winCalcSizes(); 										// Check sizes of things
			winResizeMainWindow();									// Set new window size
			vidRefreshModeList();									// Get global mode list
			ccRenderCaption(hwnd, &ccMain); 						// Rerender caption
			RETURN(0);												// Done!

	case	WM_PAINT:		   
			if ((winMode == VIDMODE_ANYFULLSCREEN) || (ccMain.bActive == FALSE))
			{
				HDC hdc;											// guess.
				PAINTSTRUCT ps; 									// Dummy
				hdc=BeginPaint(hwnd,&ps);							// Begin painting
				EndPaint(hwnd,&ps); 								// Done with paint
				RETURN(TRUE);										// Done!
			}															
			else														
			{															
				vidPaintWindow(hwnd);								// Draw window contents
				RETURN(FALSE);										// Continue
			}

#else

	// [BENDLIN] Wer ist bloß auf die Idee gekommen, die Caption selbst zu zeichnen
	case	WM_NCACTIVATE:
	case	WM_NCPAINT:
		{
			if ( zrenderer && (zrenderer->Vid_GetScreenMode() == zRND_SCRMODE_FULLSCREEN) )
			{
				RETURN(0);
			}
			else
			{
				RETURN(DefWindowProc(hwnd, msg, wParam, lParam));
			}
		}
		break;
	case	WM_PAINT:		   
		{
			if ( zrenderer && (zrenderer->Vid_GetScreenMode() == zRND_SCRMODE_FULLSCREEN) )
			{
				HDC hdc;
				PAINTSTRUCT ps;
				hdc = BeginPaint(hwnd, &ps);
				// do nothing at all
				EndPaint(hwnd, &ps);
				RETURN(TRUE);
			}															
			else														
			{
				RETURN(DefWindowProc(hwnd, msg, wParam, lParam));
			}
		}
		break;

#endif

	case	WM_SETCURSOR:		 
			// We takle care of the client area
			if (LOWORD(lParam)==HTCLIENT) 
			{
				// This window, check if we need to show or hide
				if ((winShowMouse==FALSE) || ((winShowMouse==2) && (isFullScreen())))
				{
					// Hide mouse cursor
					if (winCursorShowState>=0) winCursorShowState=ShowCursor(FALSE);
					RETURN(TRUE);									// Processed message
				}
				else
				{
					// Show mouse cursor
					if (winCursorShowState<0) winCursorShowState=ShowCursor(TRUE);
					SetCursor(LoadCursor(NULL, IDC_ARROW)); 		// Show arrow
					RETURN(TRUE);									// Processed message
				}
			}

			// We're not in the client area. We let WM_SETCURSOR_BODY()
			// define the shape of the mouse cursor, but we show the
			// mouse cursor (it must be visible to navigate the GUI)
			if (winCursorShowState<0) winCursorShowState=ShowCursor(TRUE);
			ccWM_SETCURSOR_BODY();

	case WM_DESTROY:
			sysKillWindowsKeys(false);
			RETURN(FALSE);

	// Default handler
	default:
		
		// if our main window has the focus, it might ask us if autorun should be canceled...
		if (!g_uQueryCancelAutoPlay)
        { 
            g_uQueryCancelAutoPlay = RegisterWindowMessage(TEXT("QueryCancelAutoPlay"));
        } 

        if (msg && msg == g_uQueryCancelAutoPlay)
        { 
			// the answer is - yeah, skip that damn autorun stuff
            winRes = TRUE;
        }
		else
		{
			winRes = DefWindowProc(hwnd, msg, wParam, lParam);				// Default handler
		}
		RETURN(winRes); 												// Return result
    }

	RETURN(TRUE);										
}

//
// Handle windows commands, as in menu's, shortcuts, etc.
//
static zDWORD AppCommand (HWND hwnd, zUWORD msg, WPARAM wParam, LPARAM lParam)
{
	LPMENUITEM  usrMenu;												// -> User menu item
	VIDMODE NewMode;													// New video mode
	zLONG	  i;														// General index
	zDWORD   id=wParam & 0xFFFF, dwMode;								// ID of action
	
	if ((id>=ID_VIDEO_VMODESET) && (id<=ID_VIDEO_VMODESETEND))		// Video mode set?
	{
		// Video mode switch
		if (!winSetVideoMode) return 0; 								// No callback? Quit!
		dwMode=winUserModeList[id-ID_VIDEO_VMODESET];					// Video mode number
		memcpy(&NewMode, &VideoModeCur, sizeof(VIDMODE)); 		// Copy current mode
		NewMode.si.Width=LOWORD(dwMode);								// Patch desired width
		NewMode.si.Height=HIWORD(dwMode) & 0xFFF;						// Patch desired height
		NewMode.hwModeType=(zBYTE) (dwMode>>28) & 0xF;							// Patch mode provider
		if (winSetVideoMode) winSetVideoMode(&NewMode); 				// Set video mode
	}
	else if ((id>=ID_USERMENU) && (id<ID_USERMENU+0400))
	{
		// User menu action. Check which item was selected and continue depending on selection
		usrMenu=sysMenu+(id-ID_USERMENU);								// -> User menu
		switch (usrMenu->Type & 0xFF) {									// What entry?
		case MENU_PAUSE:		usrWantPause^=4; break;				// Toggle pause
		case MENU_EXIT:			usrWantQuit=3; break; 				// Exit now!
		//case MENU_WWWBROWSE:	ASSERT(usrMenu->pCommand); if (ShellExecute(hWndApp, "open", (char*)usrMenu->pCommand, "", "", SW_SHOWNORMAL)<=(HINSTANCE)32) sysMessage(ENV_NOBROWSERSTRING); break;
		case MENU_MUTEMUS:		break;
		case MENU_MUTESND:		break;
		case MENU_ACTION: 		ASSERT(usrMenu->pCommand); ((LPCFUNC)usrMenu->pCommand)(usrMenu->CommandData);				break;
		case MENU_TOGGLE: 		ASSERT(usrMenu->pCommand); *((zBOOL *)usrMenu->pCommand)   = !*((zBOOL *)usrMenu->pCommand);	break;
		case MENU_TOGGLEBMASK:  ASSERT(usrMenu->pCommand); *((zBYTE *)usrMenu->pCommand)  ^= (zBYTE)usrMenu->CommandData;		break;
		case MENU_TOGGLEDMASK:  ASSERT(usrMenu->pCommand); *((zDWORD *)usrMenu->pCommand) ^= (zDWORD)usrMenu->CommandData;		break;
		case MENU_RADIO:		ASSERT(usrMenu->pCommand); *((zDWORD *)usrMenu->pCommand)  = (zDWORD)usrMenu->CommandData;		break;
		case MENU_VID_FSTRETCH:	vidFreeStretch^=1; if (vidFreeStretch==FALSE) winResizeMainWindow(); break;
		}
	}
	else switch(id) {
	case ID_VIDEO_8BIT:
	case ID_VIDEO_16BIT:
	case ID_VIDEO_32BIT:	  i=((wParam & 0xFFFF)-ID_VIDEO_8BIT+1)*8;
		TRACE("WIN: Switch to bit depth %u BPP", i);
		ASSERT(winSetVideoMode);				// Must have callback!
		memcpy(&NewMode, &VideoModeCur, sizeof(VIDMODE)); // Clone current video mode
		NewMode.si.BPP=(zBYTE)i; 					// Set width of new video mode
		NewMode.si.rgbMasksValid=FALSE;		// Don't know about them!
		winSetVideoMode(&NewMode);			// Set new video mode
		break;								// Done
		
	};
	return 0;
}


// Dialog Proc for exception handler
//
static BOOL CALLBACK CrashDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static	CUSTOMCAPTION ccCrash;									  // Custom caption for crash dialog
	static	CHAR  crashTitle[]="Fatal Application Error";			  // Error title
	LPDRAWITEMSTRUCT pDrwItem;										  // -> DrawItem struct
	HFONT	FatBoldErrorFont, OldFont;								  // Some font stuff
	HRGN	newRgn; 												  // New region for clipping
	RECT	cWinSize;												  // Size of window (for clipping area)
	CHAR	ErrorMessage[512];
	ENTER_PROC(CrashDlgProc);

	switch (uMsg) {
	case	WM_INITDIALOG:
			sprintf(ErrorMessage, "%s signaled the following internal error:\n\n%s", APP_NAME, (char*)lParam);
			SendDlgItemMessage(hwndDlg, IDC_ERRORTEXT, WM_SETTEXT, (WPARAM)0, (LPARAM)ErrorMessage);
			ccWM_INITDIALOG(hwndDlg, ccCrash, 1, NULL, FALSE);
			RETURN(TRUE);
		
	case	WM_DRAWITEM:
			if (wParam!=IDC_ERRORCAPTION) RETURN(FALSE);
			pDrwItem=(LPDRAWITEMSTRUCT)lParam;
		
			FatBoldErrorFont=CreateFont(GetDeviceCaps(pDrwItem->hDC, LOGPIXELSY)/3, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_SWISS, "Arial");
			OldFont=(HFONT)SelectObject(pDrwItem->hDC, FatBoldErrorFont);
			DrawText(pDrwItem->hDC, crashTitle, strlen(crashTitle), &pDrwItem->rcItem, DT_CENTER | DT_NOPREFIX | DT_VCENTER | DT_SINGLELINE);
			SelectObject(pDrwItem->hDC, OldFont);
		
			RETURN(TRUE);
		
	case	WM_CLOSE:
			EndDialog(hwndDlg, 0);
			RETURN(FALSE);
		
	case	WM_COMMAND:
			if (LOWORD(wParam)==IDC_QUIT) { EndDialog(hwndDlg, 0); RETURN(TRUE); }
			RETURN(FALSE);
		
			ccWM_FILTER(ccCrash, hwndDlg);
		
	default:RETURN(FALSE);
	};
	
	RETURN(FALSE);
}



/**{ sysHardExit, System }
@func

The sysHardExit function exits the program with an error. An attempt is done to close
down the system gracefully by de-initialising all interfaces.

@params
@return
@remarks
	Because sysHardExit accepts C-strings (with parameters), you can format a string
	with a better description of the error. For example:

--- CODE START ---
void CheckConfig(zLONG NewCSUM)
{
	zLONG OldCSUM;
	// Get old checksum and compare with new one
	OldCSUM=cfgGetInt("Config", "Checksum", 0)
	if (OldCSUM!=NewCSUM)
		HardExit("Checksum mismatch: Old=%u, New=%u", OldCSUM, NewCSUM);
}
--- CODE END ---

sysHardExit is called when fatal errors occur.

@portable
@see sysExit
**/
void sysHardExit(
	char* Message,...	/* Message to show to user
	A C-string containing the text to show to the user when exiting.
	*/
)
{
	// Check if we're not already in a "panic" state
	if (sysExiting) return;
	sysExiting=TRUE;

#ifndef COMPILING_SPACER
	CHAR		TextBuffer[512];									  // Text buffer
	va_list 	Args;												  // Arguments Buffer

	// Convert string + arguments to ASCIIZ string
	va_start(Args, Message);										  // Set arguments pointer
	vsprintf(TextBuffer, Message, Args);							  // Copy the arguments
	va_end(Args);													  // Done with the arguments

	TRACE("WIN: Application notified error: %s", TextBuffer);		  // TRACE to log

	if (isFullScreen()) vidCloseDisplay(FALSE); 					  // Die

	ShowWindow(hWndApp, SW_HIDE);									  // Hide main window

	// Create error message and show message
	winDialogParamFinal(DIALOG_CRASH, CrashDlgProc, (zDWORD)TextBuffer);



#endif
	// Clean up and exit
	
	sysExit();														  // Exit with some error
}



//
// Adjust size of main window to <w>*VideoW, <h>*VideoH or closest match near it
//
void winResizeMainWindow()
{
#ifdef COMPILING_SPACER
	return;	// Ein Resize des Spacerfensters ist nicht erlaubt
#endif

	RECT	  CurWinPos;												// Current window position
	zDWORD   w=1, h=1, i;												// Width and Height in screen width/height units
	
	if ((vidFreeStretch==TRUE) || (hWndApp==NULL) || (IsZoomed(hWndApp)) || (IsIconic(hWndApp))) return;	// No main window or free scaling -> return
	
	// Snap to a size, if user has a preset for this size, accept that size preset
	if ((vidWindowStretch==VIDSTRETCH_SNAP) || ((vidWindowStretch==VIDSTRETCH_USER) && (vidFreeStretch==FALSE)))
	{
		// Check mode list to see if we've got a preset for this size
		for (i=0; i<winSnapSizes; i++)							  // Go through all presets
		{
			if ((zDWORD)MAKELONG(VideoW, VideoH)==winSnapSize[i*2])  // Same mode?
			{
				w=LOWORD(winSnapSize[i*2+1]);						  // Accept width scale
				h=HIWORD(winSnapSize[i*2+1]);						  // Accept height scale
			}
		}
	}
	
	ASSERT(w>=1);
	ASSERT(h>=1);
	
	// Move window to new position
	GetWindowRect(hWndApp, &CurWinPos);								// Get current position
	MoveWindow(hWndApp, CurWinPos.left, CurWinPos.top, (w*VideoW)+winExtraX, (h*VideoH)+winExtraY, TRUE);
	RedrawWindow(hWndApp, NULL, NULL, RDW_INVALIDATE);				// Invalidate entire window
}

//
// Calculate sizes of window overhead
//
void winCalcSizes()
{
	// Check sizes at left/right, top/bottom of window
	winExtraX=GetSystemMetrics(SM_CXSIZEFRAME)*2+5;
	winExtraY=GetSystemMetrics(SM_CYSIZEFRAME)*2+GetSystemMetrics(SM_CYCAPTION)+5;
	if (!vidHideMenu) winExtraY+=GetSystemMetrics(SM_CYMENU);
}

//
// Return hardware current time
//
INLINE static zDWORD GetHTime()
{
	if (PreciseTimer)
	{
		// Get new benchmark time
		LARGE_INTEGER CurrentTime;									// Current time (precise)
		QueryPerformanceCounter(&CurrentTime);						// Get time (precise)
		__asm {
			mov	edx,[CurrentTime.HighPart]
				mov	eax,[CurrentTime.LowPart]
				div	[pTimeDiv]
				mov	[CurrentTime.LowPart],eax
		}
		
		return CurrentTime.LowPart; 								// Return divided time
	}
	else
	{
		return (timeGetTime()); 									// Return 1/1000 timer
	}
}

//
// Return hardware current time
//
INLINE static zDWORD GetHTime70()
{
	if (PreciseTimer)
	{
		// Get new benchmark time
		LARGE_INTEGER CurrentTime;									// Current time (precise)
		QueryPerformanceCounter(&CurrentTime);						// Get time (precise)
		__asm {
			mov		edx,[CurrentTime.HighPart]
			mov		eax,[CurrentTime.LowPart]
			div		[pTimeDiv70]
			mov		[CurrentTime.LowPart],eax
		}
		return CurrentTime.LowPart; 								// Return divided time
	}
	else
	{
		return (timeGetTime()/14);									// Return 1/70 timer
	}
}





//
// Initialise timer service
//
static void sysInitTimer()
{
	ENTER_PROC(sysInitTimer);
	
	// See if we can use a high-precision timer on this computer. Do not accept a timer which is tooo precise because the di-
	// vision we have to do on the large integer is too complicated and the timer may pass too fast around a complete cycle.
	QueryPerformanceFrequency(&pTimeFreq);							// Get high-precision frequency
	PreciseTimer=(pTimeFreq.LowPart >= 1000) && (pTimeFreq.HighPart==0);
	if (PreciseTimer) pTimeDiv=pTimeFreq.LowPart/1000;				// HiFreq Divider (1000 Hz)
	if (PreciseTimer) pTimeDiv70=pTimeFreq.LowPart/70;				// HiFreq Divider	(70 Hz)
	BeginTime=GetHTime(); 											// Fetch begin timer
	BeginTime70=GetHTime70(); 										// Fetch begin timer
	
	DEBUG_ONLY(sysTimerInitialised=TRUE); 							// Don't use timer unless initialised
	EXIT_PROC();
}

//
// Return current time
//
zDWORD sysGetTime()
{
	zDWORD hTime;													// Read timer value
	ENTER_PROC(sysGetTime);

	// Get time
	ASSERTT(sysTimerInitialised, "Timer has not been intialised");
	hTime=GetHTime()-BeginTime;										// Get time

	RETURN(hTime);													// Return relative time unit
}

//
// This routine stops the main thread if it's not currently running. This is required when sysExit()
// or something similar is called from a background thread. If the main program would continue running
// during shutdown of the system a general protection fault would be the most likely consequence
//
void winSuspendThreads()
{
  if (GetCurrentThreadId()!=winMainThreadID) SuspendThread(winMainThread); // Suspend if needed
}


void sysExit()
{
#ifndef COMPILING_SPACER
	ENTER_PROC(sysExit);
	libExit();
	if (winMainThread) CloseHandle(winMainThread);					// Close main thread (cloned) handle
	if (winTRACEMutex) CloseHandle(winTRACEMutex);					// Close TRACE sync Mutex
	ExitProcess(0); 												// Exit program
	EXIT_PROC();
#endif
}

// Do processing that needs to be done in idle time (internal function)
//
void sysProcessIdle()
{
	ENTER_PROC(sysProcessIdle);
	
	// Update various stuff
	netAcceptPendingConnections();									// Accept pending connections
	
	// Check callback
	if (sysCallBack)													// Must have callback pointer
	{
		zDWORD	time;													  // Current time
		while ((time=sysGetTime())>(sysCallBackLast+sysCallBackDelay))	// Callback expired?
		{
			(*sysCallBack)(sysCallBackLast);								// Issue callback
			if (sysCallBackSingle)										// Only one callback?
				{ sysCallBackLast+=(time-sysCallBackLast)/sysCallBackDelay*sysCallBackDelay; break; } // Update last value and return!
			else															// Check for another callback
				sysCallBackLast+=sysCallBackDelay;							// Update last value
		}
	}
	
	EXIT_PROC();
}

//
// Do system event
//
void sysEvent()
{
	static	zBOOL	inSysEvent=FALSE;								// In sysEvent?
	MSG 	msg;													// Windows message
	ENTER_PROC(sysEvent);

	ASSERTT(Video==NULL, "sysEvent() called while video memory was locked!"); // Video must be unlocked

	DEBUG_ONLY(sysCrashGuardIter++);								// Update iterator

	if (inSysEvent) EXIT_PROC();									// Don't recurse
	inSysEvent=TRUE;												// We're here now

	// Do normal idle-time processing
	sysProcessIdle();												// Do idle-time processing

	// Keep on polling messages
	
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))				// Fetch message
	{
		TranslateMessage(&msg); 									// Translate accelerators
		DispatchMessage(&msg);										// Send message to window proc
	}

	// Flags modified in window proc
	if (sysEventScreenBlanked)
	{
		// Check if we are entering "blanked" mode
		vidWaitScreenUnblank(); 									// Wait until unblanked
	}
	else if ((sysEventToggleFullScreen) || (vidLostFocus()))
	{
		// Check for video mode change
		TRACE_DEBUG("VID: Changing mode");
		vidToggleFullScreenMode();									// Do the fullscreen switch thing
	}
	
	// Remove flags
	sysEventScreenBlanked=sysEventToggleFullScreen=FALSE;			// Turn off flags
	inSysEvent=FALSE;												// No longer in sysEvent

	{
		if (GetForegroundWindow() != hWndApp && (!zrenderer || zrenderer->Vid_GetScreenMode()==zRND_SCRMODE_FULLSCREEN)) 
		{
			HandleFocusLoose();
		}
		else if (bLostFocus)
		{
			if (zoptions && (!zoptions->ReadBool("RENDERER_D3D", "zEnableTaskSwitch", TRUE) && !zoptions->Parm("DEVMODE")))
			{
				if (zrenderer) zrenderer->Vid_SetScreenMode(zRND_SCRMODE_FULLSCREEN);
				sysSetFocus();
				#ifdef COMPILING_GOTHIC
				#ifndef COMPILING_SPACER
				if (ogame) ogame->Unpause();
				#endif
				#endif
				bLostFocus = FALSE;
			}
			else if (GetActiveWindow() == hWndApp)
			{
				bLostFocus = FALSE;
				if (zrenderer) zrenderer->Vid_SetScreenMode(zRND_SCRMODE_FULLSCREEN);
				sysSetFocus();
				#ifdef COMPILING_GOTHIC
				#ifndef COMPILING_SPACER
				if (ogame) ogame->Unpause();
				#endif
				#endif

			}
		}
	}

	EXIT_PROC();
}

/**{ sysIdle, System }
@func

The sysIdle function is used to return time to the system when an application is idle.

@params
@return

@portable
	This function is only exported from the Win32 libraries

@see sysEvent
**/
void sysIdle(
	int		Time			/* Amount of milliseconds to sleep
	Amount of milliseconds to sleep. When Time is 0, the current time slice is returned to the
	Windows task scheduler. When Time is larger than 0, the application will not get a new time
	slice for the specified amount of milliseconds. When your application is idle and does not
	require any processing power, you should call sysIdle with a Time value larger than 0.
	*/
)
{
	ENTER_PROC(sysIdle);
	
	Sleep(Time);

	EXIT_PROC();
}



//
// Wait for a message to arrive
//
void winWaitMessage(zUWORD Message, zDWORD wParam, zDWORD wParamAND, zDWORD lParam, zDWORD lParamAND, zBOOL QuitIfNotMinimized)
{
	MSG 	msg;													// Message to retrieve
	ENTER_PROC(winWaitMessage);

	// Process messages until we're done
	for (;;)
	{
		// Do idle time processing until the application is restore
		sysProcessIdle();											// Do system idle time
		if ((QuitIfNotMinimized) && (!IsIconic(hWndApp))) break;	// Not minimized any more?
		if (!PeekMessage(&msg, hWndApp, 0, 0, PM_REMOVE)) { Sleep(2); continue; }	// Check for message

		// Check to see if this is the correct message
		if (msg.message!=Message) continue; 						// Incorrect message
		if ((msg.wParam & wParamAND) != wParam) continue;			// Incorrect wParam
		if ((msg.lParam & lParamAND) != lParam) continue;			// Incorrect lParam

		// We passed all tests, exit
		break;
	}

	EXIT_PROC();
}

//
// Send message to spying thread (when activated) to log a message
//
// TRACE is also used from other threads to log their activity/errors. When two routines
// call TRACE at the same time this would produce garbage (TextBuffer is trashed, and the
// writes to the file won't be synchronous). A mutex is used to prevent two threads from
// TRACEing at the same time.
//

void TRACE(char *Message,...)
{
#ifdef TRACE_TIME
	static	zDWORD	TRACE_Last=0;									// Last trace time
	zDWORD	TRACE_Now;												// Current time
#endif
	va_list Args;													// Arguments Buffer
	char  tBuf[2048], tBuf2[2048];									// Pointers to Buffers
	ENTER_PROC(TRACE);

	WaitForSingleObject(winTRACEMutex, INFINITE);					// Hold Mutex for TRACE

	va_start(Args, Message);										// Set arguments pointer
#ifdef TRACE_TIME
	TRACE_Now=sysGetTime(); 										// Get current time
	sprintf(tBuf, "%-6u ", TRACE_Now-TRACE_Last);					// Show time delta
	TRACE_Last=TRACE_Now;											// Save time
	vsprintf(tBuf+7, Message, Args);								// Copy the arguments
#else
	vsprintf(tBuf, Message, Args);									// Copy the arguments
#endif	
	va_end(Args);													// Done with the arguments
	sprintf(tBuf2, "%s\r\n", tBuf); 								// Make string with CRLF

#ifdef _DEBUG
	OutputDebugString(tBuf2);										// Show string in debugger
#endif

	ReleaseMutex(winTRACEMutex);									// Allow other threads to TRACE
	EXIT_PROC();
}




//
// Save window position
//

//
// Make sure we have a key in the requested topic
//
void cfgFetchTopic(char *NewTopic)
{
#ifndef COMPILING_SPACER
	return;
#endif	

	static char emptyTopic[]="";									// Empty topic name
	static char oTopic[64]={""};									// Old topic (for detecting changes)
	DWORD	cKey;													// Key disposition value

	if (NewTopic==NULL) NewTopic=emptyTopic;						// -> Empty thing
	if ((cfgHKey==NULL) || (strcmp(NewTopic, oTopic)))
	{
		// Clean up old mess
		cfgBaseKey=HKEY_CURRENT_USER;								// CURRENT_USER or LOCAL_MACHINE
		strcpy(oTopic, NewTopic);									// Make a copy of the topic name
		if (cfgHKey) RegCloseKey(cfgHKey);							// Close old key if neccesary

		// Create new key
		if (_strnicmp(NewTopic, "HKEY_LOCAL_MACHINE:", strlen("HKEY_LOCAL_MACHINE:"))==0) { cfgBaseKey=HKEY_LOCAL_MACHINE; NewTopic+=strlen("HKEY_LOCAL_MACHINE:"); }
		if (NewTopic[0]=='\\')										// Full registry key name?
			strcpy(cfgKeyName, NewTopic+1);							// Copy full nume
		else
			sprintf(cfgKeyName, "Software\\%s\\%s\\%s\\%s", REG_COMPANY, REG_PROGRAM, REG_VERSION, NewTopic); // Name of new key

		RegCreateKeyEx(cfgBaseKey, cfgKeyName, 0, "", 0, KEY_ALL_ACCESS, NULL, &cfgHKey, &cKey);
	}
}
//
// Write a piece of binary data to the configuration settings
//
void cfgSetBinary(char *Topic, char *Key, void *Data, int Size)
{
#ifndef COMPILING_SPACER
	return;
#endif	

	cfgFetchTopic(Topic);											  // Make sure we have a key with the right topic
	RegSetValueEx(cfgHKey, Key, 0, REG_BINARY, (LPBYTE)Data, Size);   // Write data
}

//
// Get an integer from the configuration settings
//
zBOOL cfgGetBinary(char *Topic, char *Key, void *Data, int *Size)
{
#ifndef COMPILING_SPACER
	return TRUE;
#endif	

	zDWORD ValueType;												// Receives type of value

	ASSERT(sizeof(DWORD) == sizeof(int));
	if (!winUseRegistry) return FALSE;								// No registry use, return default

	// Query value from registry
	cfgFetchTopic(Topic);											// Make sure we have a key with the right topic
	return ((RegQueryValueEx(cfgHKey, Key, 0, &ValueType, (unsigned char*)Data, (DWORD *)Size)==ERROR_SUCCESS) && (ValueType==REG_BINARY));
}


static void winSaveWindowPos()
{
#ifndef COMPILING_SPACER
	return;
#endif	

	RECT	WindowedPos;											// Windowed position
	ENTER_PROC(winSaveWindowPos);
	
	// Get window rectangle to 'WindowedPos'
	GetWindowRect(hWndApp, &WindowedPos); 							// Get window position
	
	// Now, record new sizes to iwPos, but only when in windowed mode
	if (!isWindowed()) EXIT_PROC();
	iwPos.Valid=TRUE; 												// Validating it now
	iwPos.maxMain=IsZoomed(hWndApp);								// Maximize flag
	if (!iwPos.maxMain && !IsIconic(hWndApp)) 						// Record size of normal window, not maximized
	{
		iwPos.xMain=WindowedPos.left;
		iwPos.yMain=WindowedPos.top;
		iwPos.wMain=WindowedPos.right-WindowedPos.left;
		iwPos.hMain=WindowedPos.bottom-WindowedPos.top;
	}

	if (iwPos.Valid)
	cfgSetBinary("System",	"Window Position",		(void *)&iwPos, sizeof(iwPos));
	
	EXIT_PROC();
}



//
// Check if the specified string (command-line string) contains the specified option
//
static zBOOL CmdLineGotOption(char* cmdLine, const char *Option, zBOOL RemoveOption)
{
	char* pOption = cmdLine;										// -> Where we found the option matched
	int   OptionLen = strlen(Option);								// Length of option string

	// Check if we've found this option at all
	while ((pOption=strstr(pOption, Option))!=NULL)
	{
		// Found a spot, see if we can match this option
		char Trailer = pOption[OptionLen];							// Trailing char behind string
		if (Trailer==' ' || Trailer=='\t' || Trailer==0)			// Found it!
		{
			// Found the option (and a trailing space, tab or end-of-string), see if we gotta remove this option from the string
			if (RemoveOption)
			{
				int Index = pOption-cmdLine;						// Index in string
				if (Trailer==' ' || Trailer=='\t') OptionLen++;		// Remove trailing stuff too
				memmove(pOption, pOption+OptionLen, strlen(pOption));
				memmove(sysCommandLine+Index, sysCommandLine+Index+OptionLen, strlen(sysCommandLine+Index));
			}
			
			return TRUE;
		}

		// We didn't find the option restart scanning at next character
		pOption++;													// Start searching at next character
	}

	return FALSE;
}

// This macro is used to check if the commandline contains a certain option, it will remove it and then allow for some code, ended by a '}'
#define IS_OPTION(x, var, val)	if (CmdLineGotOption(cmdLineLwr, x, TRUE)) (var)=(val);

//
// Parse command line options 
//
void sysParseCommandLine(char* Cmd)
{
	zLONG	Index, OptionLen;										  // Index of option in command line and length of option
	CHAR	cmdLineLwr[2048];										  // lowerCased command-line
	
	// Create normal and lowered command line
	sysCommandLine=(char*)sysAlloc(strlen(Cmd)+2); 						  // Allocate space for command line
	strcpy(sysCommandLine, Cmd);									  // Copy normal command line
	strcpy(cmdLineLwr, Cmd);										  // Clone it
	_strlwr(cmdLineLwr);											  // Lower this clone
	
	// Check for "-log=filename" command-line option
	if (strstr(cmdLineLwr, "-log="))
	{
		CHAR  logChar;													// Character for log name
		OptionLen=5;													// Length of "-log="
		Index=strstr(cmdLineLwr, "-log=")-cmdLineLwr;					// Index in string
		do
		{
			// Copy characters until we find a space or an end-of-string
			logChar=sysCommandLine[Index+OptionLen];					  // Grab char from log name
			sysLogName[OptionLen-5]=logChar;							  // Copy char
			OptionLen++;												  // Got one more
		} while ((logChar) && (logChar!=' '));							// Until end of string
		sysLogName[OptionLen-6]=0;										// Terminate string
		
		// Remove filename from string
		memmove(cmdLineLwr+Index,	  cmdLineLwr+Index+OptionLen, strlen(cmdLineLwr)-Index);
		memmove(sysCommandLine+Index, sysCommandLine+Index+OptionLen, strlen(sysCommandLine)-Index);
	}
	
	// Check other command-line options
	IS_OPTION("-safe",				usrSafeMode,					TRUE);
	IS_OPTION("-windowed",			VideoModeCur.hwModeType,		VIDMODE_ANYWINDOWED);
	IS_OPTION("-fullscreen",		VideoModeCur.hwModeType,		VIDMODE_ANYFULLSCREEN);
	IS_OPTION("-safelog",			sysSafeLog,						TRUE);
	IS_OPTION("-nonetwork",			netEnable,						FALSE);
	IS_OPTION("-noddrawwin",		vidGotMode[VIDMODE_DDRAWWIN],	FALSE);
	IS_OPTION("-noddraw",			vidGotMode[VIDMODE_DDRAW],		FALSE);
	IS_OPTION("-noddrawmemcheck",	vidCheckMemory,					FALSE);
	IS_OPTION("-noreg", 			winUseRegistry,					FALSE);
#ifdef _DEBUG
	IS_OPTION("-crashguard",		sysCrashGuardMode,				TRUE);
#endif

	// When in safe mode, remove lots' of support
	if (usrSafeMode)
	{
		TRACE("WIN: Safe mode startup");								// Show we're in safe mode
		VideoModeCur.hwModeType=VIDMODE_DIB;
		netEnable=FALSE;
		vidGotMode[VIDMODE_DDRAW]=FALSE;
		vidGotMode[VIDMODE_DDRAWWIN]=FALSE;
	}
	
}



//
// Check if the specified string is empty
//
static zBOOL EmptyString(char *str)
{
	while (1)
	{
		if (*str == 0)
			return TRUE;
		else if ((*str == ' ') || (*str == '\t'))
			str++;
		else
			return FALSE;
	}
}



//
// Check if system is OK: It has enough colors, it's TRUEly Win32 (no Win32s) and whatever might be needed
//
static void winInitSystem()
{
	OSVERSIONINFO vInfo;											// Version info
	HDC 	hdc;													// Windows device context
	CHAR	OSName[64]; 											// Name of operating system
	
	// Check if user isn't running this under Win32s (Yuck!)
	memset(&vInfo, 0, sizeof(vInfo));								// Clear out info structure
	vInfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);				// Fill in size of header
	GetVersionEx(&vInfo);											// Get version information
	if (vInfo.dwPlatformId==VER_PLATFORM_WIN32s)					// Get platform type
	{
		MessageBox(hWndApp, "This program cannot be run under Win32s.\nYou must this program under Windows 95 or Windows NT.", NULL, MB_OK|MB_ICONERROR|MB_SETFOREGROUND);
		exit(3);
	}
	
	// Check if we have enough colors
	hdc=GetDC(NULL);												// Get DC for color check
	winBPP=GetDeviceCaps(hdc, BITSPIXEL);							// Windows display mode depth
	ReleaseDC(NULL, hdc);											// Release temp. DC
	if (winBPP<8)													// Less than 256 colors?
	{
		MessageBox(hWndApp, "This program requires a 256 color display mode.", NULL, MB_OK|MB_ICONERROR|MB_SETFOREGROUND);
		exit(2);
	}
	
	// Log current operating system
	switch (vInfo.dwPlatformId) {
	case  VER_PLATFORM_WIN32_WINDOWS:	strcpy(OSName, "Microsoft Windows"); break;
	case  VER_PLATFORM_WIN32_NT:		strcpy(OSName, "Microsoft Windows NT"); winNT=TRUE; break;
	default: strcpy(OSName, "an unknown operating system"); break;
	}
	if (!EmptyString(vInfo.szCSDVersion)) { strcat(OSName, " "); strcat(OSName, vInfo.szCSDVersion); }
	TRACE("WIN: Running %s version %u.%u, Build %u", OSName, vInfo.dwMajorVersion, vInfo.dwMinorVersion, vInfo.dwBuildNumber & 0xFFFF);
	
	// Check available swap space
	
	// Check available resources
	
}




/**{ sysSetFocus, System }
@func

The sysSetFocus function makes sure that the application has input focus.

@params
@return
@remarks
	On multi-tasking systems, only one program can have focus. Normally you have focus
	when you are in fullscreen mode or when the application's window is selected. If
	you are using a custom way of accessing the display (for example OpenGL, Glide or
	WinDoctor) you might want to grab the input focus to make sure that calls to
	@@kbGetKey and other input functions return correct information.

	Calling sysSetFocus will set the focus to the window that has been created.
	This window does not have to be visible; if you never call @@vidSetMode you won't
	have a visible window, but you can still grab the input focus by calling sysSetFocus.

	Only one program can have the input focus.

@see kbGetKey
**/
void sysSetFocus()
{
	SetWindowPos(hWndApp, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSENDCHANGING | SWP_NOSIZE);
	SetForegroundWindowEx(hWndApp);
	SetFocus(hWndApp);

	ShowWindow(hWndApp, SW_RESTORE);							// Restore window position
	ShowWindow(hWndApp, SW_SHOWNORMAL);							// Restore window position
}

//
// Do a dialog (with parameter and/or with exit)
//
zLONG winDialog(WORD resID, DLGPROC Proc)
{
	return winDialogParam(resID, Proc, 0); 							// Show dialog
}
zLONG winDialogParam(WORD resID, DLGPROC Proc, zDWORD Param)
{
	zLONG	res;													// Dialog result value
	zBOOL	fullScreen; 											// In fullscreen mode?
	zDWORD	tStart; 												// Start time

	// Get into right video mode, do dialog, and restore
	tStart=sysGetTime();											// Start time before dialog
	fullScreen=isFullScreen();										// Now in fullscreen mode?
	if (fullScreen) vidMinimize(FALSE); 							// Minimize fullscreen display
	res=DialogBoxParam(hInstApp, MAKEINTRESOURCE(resID), hWndApp, Proc, (LPARAM)Param); 	// Do dialog
	if (fullScreen) vidRestore();									// Restore fullscreen stuff
	sysTimeGap+=sysGetTime()-tStart;								// Add to time gap

	return res;
}
zLONG winDialogParamFinal(WORD resID, DLGPROC Proc, zDWORD Param)
{
	zLONG	res;													  // Dialog result value
	zDWORD	tStart; 												// Start time

	// Get into right video mode, do dialog, and restore
	tStart=sysGetTime();											// Start time before dialog
	vidCloseDisplay(FALSE); 										  // Bye Bye!
	ShowWindow(hWndApp, SW_HIDE);									  // Hide main window
	res=DialogBoxParam(hInstApp, MAKEINTRESOURCE(resID), NULL, Proc, (LPARAM)Param); // Do dialog
	sysTimeGap+=sysGetTime()-tStart;								// Add to time gap

	return res;
}


//
// Dialog Proc for exception dialog
//

void ExcSpyInfo ( EXCEPTION_INFO *exInfo)
{

	zerr.Warning("======================================= UNHANDLED EXCEPTION OCCURED ======================================================");
	zerr.Warning("============================================== CRASH INFOS: ==============================================================");

	for (int i=0; i<exInfo->csDepth; i++) {
		if (zSTRING(exInfo->callStack[i]).Search("START")!=-1) {
			zERR_WARNING("Startup Options:");
			zERR_WARNING(sysCommandLine+zSTRING("\r\n"));
			zerr.Warning("=============================================== CALLSTACK : ==============================================================");
			continue;
		}
		zerr.Warning(exInfo->callStack[i]);
	}
	zerr.Warning("======================================= UNHANDLED EXCEPTION OCCURED ======================================================");
	
	HANDLE hText = NULL;
	HANDLE hData;      
	LPSTR  lpData, lpszText;
	zSTRING excLines;
	excLines = zSTRING("======================================= UNHANDLED EXCEPTION OCCURED ======================================================\r\n") +
			   zSTRING("======================================= CRASH INFOS: =====================================================================\r\n");

	for (i=0; i<exInfo->csDepth; i++) {
		if (zSTRING(exInfo->callStack[i]).Search("START")!=-1) {
			excLines += "Startup Options:";
			excLines += sysCommandLine ;
			excLines += "\r\n";
			excLines += zSTRING("=============================================== CALLSTACK : ==============================================================\r\n");
		} else excLines+=exInfo->callStack[i] + zSTRING("\r\n");
	}

	if ( (hText = GlobalAlloc(GMEM_MOVEABLE,(DWORD)excLines.Length())) != NULL) {

		if ( (lpszText = (char*)GlobalLock(hText)) != NULL) {
			strcpy(lpszText, excLines.ToChar());
			GlobalUnlock(hText);
			if (hText)
			if ( (hData = GlobalAlloc(GMEM_DDESHARE, GlobalSize (hText))) != NULL) {

				if ( (lpData = (char*)GlobalLock(hData)) != NULL) {
					if ( (lpszText = (char*)GlobalLock (hText)) != NULL) {
						strcpy(lpData, lpszText);

						GlobalUnlock(hData);
						GlobalUnlock(hText);
						if (OpenClipboard(hWndApp)) {
							EmptyClipboard();
							SetClipboardData(CF_TEXT, hData);
							CloseClipboard();
                        }
                        hData = NULL;
					}
				}
			}
		}
	}
};


zBOOL CALLBACK ExceptionDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CUSTOMCAPTION ccException;								  // Custom caption for exception handler
	static CHAR    ExcTitle[64];									  // Exception title
	LPEXCEPTION_INFO exInfo;
	EXCEPTION_POINTERS *pExcInfo;									  // Exception information
	EXCEPTION_RECORD *pExc; 										  // -> Exception record
	LPDRAWITEMSTRUCT pDrwItem;										  // -> DrawItem struct
	PCONTEXT  pCPU; 												  // -> Processor context
	char *CallStackText=NULL;
	char *pCSWrite=NULL;						  // -> Call stack text
	HRGN	newRgn; 												  // New region for clipping
	HFONT	FatBoldErrorFont, OldFont;								  // Some font stuff
	RECT	cWinSize;												  // Size of window (for clipping area)
	CHAR	Text[512];												  // Text buffer
	CHAR	rwText[2][16]={ "\"read\" from", "\"write\" to" };		  // For access violations
	LONG	i;														  // Counter
	ENTER_PROC(ExceptionDlgProc);
	END_OF_CALLSTACK();
	zBOOL doIt = FALSE;
	switch (uMsg) {
	case WM_INITDIALOG: exInfo  = (LPEXCEPTION_INFO)lParam;
						pExcInfo= exInfo->exPtrs;					// Parameter to dialog box
						pCPU=pExcInfo->ContextRecord;				// -> CPU Context
						pExc=pExcInfo->ExceptionRecord; 			// -> Exception information

						// Show registers (machine state)
						sprintf(Text, "%Xh\n%Xh\n%Xh\n%Xh\n%Xh\n%Xh\n%Xh", pCPU->Eax, pCPU->Ebx, pCPU->Ecx, pCPU->Edx, pCPU->Esi, pCPU->Edi, pCPU->Ebp);
						SendDlgItemMessage(hwndDlg, IDC_INTREGLIST, WM_SETTEXT, (WPARAM)0, (LPARAM)Text);
						sprintf(Text, "%04Xh\n%04Xh\n%04Xh\n%04Xh", pCPU->SegDs, pCPU->SegEs, pCPU->SegFs, pCPU->SegGs);
						SendDlgItemMessage(hwndDlg, IDC_SEGREGLIST, WM_SETTEXT, (WPARAM)0, (LPARAM)Text);
						sprintf(Text, "%04Xh:%08Xh\n%04Xh:%08Xh\n%04Xh:%08Xh", pCPU->SegCs, pCPU->Eip, pCPU->SegSs, pCPU->Esp, pCPU->SegSs, pCPU->Ebp);
						SendDlgItemMessage(hwndDlg, IDC_PTRREGLIST, WM_SETTEXT, (WPARAM)0, (LPARAM)Text);

						// Describe exception
						sprintf(Text, "%s has ", APP_NAME);
						switch (pExc->ExceptionCode)
						{
						  case EXCEPTION_ACCESS_VIOLATION:	  strcpy(ExcTitle, "Access Violation"); 	strcat(Text, "caused an access violation"); break;
						  case EXCEPTION_BREAKPOINT:		  strcpy(ExcTitle, "Breakpoint");			strcat(Text, "caused a Breakpoint Exception"); break;
						  case EXCEPTION_FLT_STACK_CHECK:	  strcpy(ExcTitle, "Stack Overflow");		strcat(Text, "caused a (floating point) Stack Overflow"); break;
						  case EXCEPTION_STACK_OVERFLOW:	  strcpy(ExcTitle, "Stack Overflow");		strcat(Text, "caused a Stack Overflow"); break;
						  case EXCEPTION_IN_PAGE_ERROR: 	  strcpy(ExcTitle, "Page Fault");			strcat(Text, "caused a Page Fault"); break;
						  case EXCEPTION_ILLEGAL_INSTRUCTION: strcpy(ExcTitle, "Illegal Opcode");		strcat(Text, "attempted to execute an Illegal Instruction"); break;
						  case EXCEPTION_PRIV_INSTRUCTION:	  strcpy(ExcTitle, "Private Instruction");	strcat(Text, "attempted to execute a Priviledged Instruction"); break;
						  case EXCEPTION_INT_DIVIDE_BY_ZERO:  strcpy(ExcTitle, "Divide by Zero");		strcat(Text, "performed a Divide by Zero"); break;
						  case EXCEPTION_FLT_DIVIDE_BY_ZERO:  strcpy(ExcTitle, "Divide by Zero");		strcat(Text, "performed a floating-point Divide by Zero"); break;
						};
						// Pad faulting address
						sprintf(Text+strlen(Text), " at address %08Xh", pExc->ExceptionAddress);
						// Pad Access Violation faulting address and mode
						if (pExc->ExceptionCode==EXCEPTION_ACCESS_VIOLATION)
						  sprintf(Text+strlen(Text), " by attempting to %s address %08Xh", rwText[pExc->ExceptionInformation[0]], pExc->ExceptionInformation[1]);
						TRACE("WIN: %s", Text);
						strcat(Text, ".");
						SendDlgItemMessage(hwndDlg, IDC_EXCEPTIONTEXT, WM_SETTEXT, (WPARAM)0, (LPARAM)Text);

						// Do call stack thing for debug apps
						CallStackText=(char *)sysAlloc(32768);				// Alloc some memory
						CallStackText[0]=0; 						// Terminate string
						pCSWrite=CallStackText; 					// Write pointer

						for (i=0; i<exInfo->csDepth; i++) // Walk call stack
						{
							// Auf das Window kommt nur der Call Stack, aber nicht die User Infos, böser Hack
							zSTRING s(exInfo->callStack[i]);

							// Igittigitt
							if (!doIt) {
								if (s.Search("START")!=-1) { doIt = TRUE; continue; }
								else continue;
							}
							
							
							sprintf(pCSWrite, "%s\r\n",s.ToChar() );// Add text
							if (i==0) sprintf(pCSWrite+strlen(s.ToChar()), " <-\r\n");
  						    pCSWrite+=strlen(pCSWrite);				// Next line
						}
						pCSWrite[0]=pCSWrite[1]=0;
						SendDlgItemMessage(hwndDlg, IDC_CALLSTACK, WM_SETTEXT, (WPARAM)0, (LPARAM)CallStackText);
						sysFree(CallStackText); 					// Free callstack text

						// Set window caption text
						sprintf(Text, "Application Error - %s", ExcTitle);
						SendMessage(hwndDlg, WM_SETTEXT, (WPARAM)0, (LPARAM)Text);

						ccWM_INITDIALOG(hwndDlg, ccException, 1, NULL, FALSE);
						ExcSpyInfo(exInfo);

						RETURN(TRUE);

	case	WM_DRAWITEM:

			if (wParam!=IDC_EXCEPTIONCAPTION) RETURN(FALSE);
			pDrwItem=(LPDRAWITEMSTRUCT)lParam;

			FatBoldErrorFont=CreateFont(GetDeviceCaps(pDrwItem->hDC, LOGPIXELSY)/3, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_SWISS, "Arial");
			OldFont=(HFONT)SelectObject(pDrwItem->hDC, FatBoldErrorFont);
			DrawText(pDrwItem->hDC, ExcTitle, strlen(ExcTitle), &pDrwItem->rcItem, DT_CENTER | DT_NOPREFIX | DT_VCENTER | DT_SINGLELINE);
			SelectObject(pDrwItem->hDC, OldFont);

			RETURN(TRUE);

	case	WM_CLOSE:
			EndDialog(hwndDlg, EXCEPTION_EXECUTE_HANDLER);
			RETURN(FALSE);

	case	WM_COMMAND:
			if (LOWORD(wParam)==IDC_CLOSE) EndDialog(hwndDlg, 0);
			RETURN(TRUE);

	ccWM_FILTER(ccException, hwndDlg);
	
	default:RETURN(FALSE);
	};

	RETURN(FALSE);
}

//
// Dialog Proc for failing assertions dialog
//
BOOL CALLBACK ASSERTDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CUSTOMCAPTION ccASSERT;									// Custom caption for assertion handler
	static LPASSERT_FAIL_INFO afInfo;								// Failed assertion struct
	static LPEXCEPTION_INFO exInfo;
	LPDRAWITEMSTRUCT pDrwItem;										// -> DrawItem struct
	char*	CallStackText=NULL;
	char*   pCSWrite=NULL;						// -> Call stack text
	HRGN	newRgn; 												// New region for clipping
	HFONT	FatBoldErrorFont, OldFont;								// Some font stuff
	RECT	cWinSize;												// Size of window (for clipping area)
	char	Text[512];												// Text buffer
	zLONG	i;														// Counter
	ENTER_PROC(ASSERTDlgProc);
	END_OF_CALLSTACK();


	zBOOL doIt = FALSE;
	switch (uMsg) {
	case	WM_INITDIALOG:
			// Show assertion info
			afInfo=(LPASSERT_FAIL_INFO)lParam;			// Get -> Assertion info
			exInfo= (LPEXCEPTION_INFO) afInfo->extInfo;
			sprintf(Text, "%s (line %u)", afInfo->File, afInfo->Line);
			SendDlgItemMessage(hwndDlg, IDC_ASSERTION, WM_SETTEXT, (WPARAM)0, (LPARAM)afInfo->AssertText);
			SendDlgItemMessage(hwndDlg, IDC_FILE,	   WM_SETTEXT, (WPARAM)0, (LPARAM)Text);

			// Make sure the mouse is shown
			while ((winCursorShowState=ShowCursor(TRUE))<=0);  // Show mouse
			SetCursor(LoadCursor(NULL, IDC_ARROW)); 	// Show arrow

			// Check if it's one with reason (ASSERTT)
			if (afInfo->Reason) 						// Reason, show reason
				SendDlgItemMessage(hwndDlg, IDC_REASON,  WM_SETTEXT, (WPARAM)0, (LPARAM)afInfo->Reason);
			else										// No reason, hide "Reason:" item
				ShowWindow(GetDlgItem(hwndDlg, IDC_REASON_TEXT), SW_HIDE);

			// Do call stack thing
			CallStackText=(char*)sysAlloc(32768);				// Alloc some memory
			CallStackText[0]=0; 						// Terminate string
			pCSWrite=CallStackText; 					// Write pointer
			for (i=1; i<exInfo->csDepth; i++) // Walk call stack
			{
				zSTRING s(exInfo->callStack[i]);
											// Igittigitt
				if (!doIt) {
					if (s.Search("START")!=-1) { doIt = TRUE; continue; }
					else continue;
				}

				zSTRING sym  = s.PickWord(2,",",",");
				zSTRING file;
				int pos = s.SearchRev("line");
				if ( pos != -1) { // es gibt eine line info
					pos  = s.SearchRev(",",2)+1;
					file = s.Copied(pos);
					pos = file.SearchRev("\\") ;
					if (pos != -1) file = file.Copied(pos+1);
				}
				zSTRING line;
				if (!file.IsEmpty()) line = sym + ", file:" + file; 
				else {
					zSTRING module = s.PickWord(1,",",",");
					module = module.Copied(module.Search(")")+1);
					line = sym + ", module: " + module;
				}
				
				sprintf(pCSWrite, "%s\r\n",line.ToChar() );// Add text
				if (i==1) sprintf(pCSWrite+strlen(line.ToChar()), " <-\r\n");
				pCSWrite+=strlen(pCSWrite); 			  // Next line
			}
			pCSWrite[0]=pCSWrite[1]=0;
			SendDlgItemMessage(hwndDlg, IDC_CALLSTACK, WM_SETTEXT, (WPARAM)0, (LPARAM)CallStackText);
			sysFree(CallStackText); 					// Free callstack text

			ccWM_INITDIALOG(hwndDlg, ccASSERT, 1, NULL, FALSE);

			SetForegroundWindowEx(hwndDlg);				// Show us
			RETURN(TRUE);

	case	WM_DRAWITEM:
			if (wParam!=IDC_ASSERTCAPTION) RETURN(FALSE);
			pDrwItem=(LPDRAWITEMSTRUCT)lParam;

			FatBoldErrorFont=CreateFont(GetDeviceCaps(pDrwItem->hDC, LOGPIXELSY)/3, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_SWISS, "Arial");
			OldFont=(HFONT)SelectObject(pDrwItem->hDC, FatBoldErrorFont);
			DrawText(pDrwItem->hDC, afInfo->HeaderText, strlen(afInfo->HeaderText), &pDrwItem->rcItem, DT_CENTER | DT_NOPREFIX | DT_VCENTER | DT_SINGLELINE);
			SelectObject(pDrwItem->hDC, OldFont);
			RETURN(TRUE);

	case	WM_CLOSE:
			EndDialog(hwndDlg, 0);
			RETURN(TRUE);

	case	WM_COMMAND:
			switch (LOWORD(wParam)) {
			case IDC_CLOSE: EndDialog(hwndDlg, 0); break;
			case IDC_DEBUG: __asm { int 3 }; break;
			default:        break;
			};
			RETURN(TRUE);

	ccWM_FILTER(ccASSERT, hwndDlg);
	};

	RETURN(FALSE);
}

//
// Fail a boundscheck
//

#define CRASH_CODE	__try {	void *ptr = 0;	*(int *) ptr = 0; }

void BoundsSpyInfo ( ASSERT_FAIL_INFO* afInfo, EXCEPTION_INFO *exInfo)
{

	zSTRING ext = afInfo->Reason ? ", Reason: " + zSTRING(afInfo->Reason) : "";
	zerr.Warning("Boundary check failed: " + zSTRING(afInfo->AssertText) + " in file " + zSTRING(afInfo->File) + ", Line: " + zSTRING(afInfo->Line) + ext);
	zerr.Warning("Call stack: ");

	for (int i=0; i<exInfo->csDepth; i++) {
		zerr.Warning(exInfo->callStack[i]);
	}
};

void BOUNDS_FAIL(char *varName, int Value, int Low, int High, char *File, int Line, const zSTRING &r)
{
	char *Reason = r.ToChar();
	ASSERT_FAIL_INFO afInfo={ "Bounds Violation", NULL, File, Line, Reason };			// Failed assertion struct
	char	ErrString[512];
	EXCEPTION_INFO   exInfo;

	// Check if we're not already in a "panic" state
	sprintf(ErrString, "Variable %s (%d) not in bounds [%d, %d]", varName, Value, Low, High);
	afInfo.AssertText=ErrString;									// Set -> Error text
	if (sysExiting) { TRACE("WIN: Warning! Bounds failed; %s", ErrString); return; }
	sysExiting=TRUE;

	// Check if we've failed an assertion in the debugger, if so -> break debugg
	if (sysGotDebugger()) __asm { int 3 };

	// Dump assertion to log
	TRACE("WIN: Bounds Check Failed!");
	TRACE("");
	TRACE("WIN: Bounds Check : %s", ErrString);
	TRACE("WIN: File         : %s (line %u)", File, Line);
	if (Reason) TRACE("WIN: Reason       : %s", Reason);
	TRACE("");

	// throw exception, save ASSERT_FILE_INFO into options (and prev. delete old values)

	zBOOL exActive = zexhnd.GetIsActive();
	zexhnd.SetIsActive(FALSE);

	CRASH_CODE
	__except(zexhnd.BoundsExceptionFilter(GetExceptionInformation(),&afInfo,&exInfo)){};

	zexhnd.SetIsActive(exActive);

	afInfo.extInfo = (void*)&exInfo;
	BoundsSpyInfo ( &afInfo, &exInfo);

	// Show dialog


	// Show dialog
	winDialogParamFinal(DIALOG_BOUNDS, ASSERTDlgProc, (zDWORD)&afInfo);
	sysExit();														// Exit!
}



//
// Fail an assertion
//

void AssertSpyInfo ( ASSERT_FAIL_INFO* afInfo, EXCEPTION_INFO *exInfo)
{

	zSTRING ext = afInfo->Reason ? ", Reason: " + zSTRING(afInfo->Reason) : "";
	zerr.Warning("ASSERTION failed: " + zSTRING(afInfo->AssertText) + " in file " + zSTRING(afInfo->File) + ", Line: " + zSTRING(afInfo->Line) + ext);
	zerr.Warning("Call stack: ");

	for (int i=0; i<exInfo->csDepth; i++) {
		zerr.Warning(exInfo->callStack[i]);
	}
};


void ASSERT_FAIL(char *Assertion, char *File, int Line, const zSTRING &r)
{
	char *Reason = r.ToChar();
	ASSERT_FAIL_INFO afInfo={ "Assertion Failed", Assertion, File, Line, Reason };	// Failed assertion struct
	EXCEPTION_INFO   exInfo;

	// Check if we're not already in a "panic" state
	if (sysExiting)
	{
		TRACE("WIN: Warning! ASSERT(%s) Failed in %s (line %u)", Assertion, File, Line);
		return;
	}
	sysExiting=TRUE;

	// Dump assertion to log
	TRACE("WIN: Assertion Failed!");
	TRACE("");
	TRACE("WIN: Assertion : ASSERT(%s)", Assertion);
	TRACE("WIN: File      : %s (line %u)", File, Line);
	if (Reason) TRACE("WIN: Reason    : %s", Reason);
	TRACE("");

	// throw exception, save ASSERT_FILE_INFO into options (and prev. delete old values)

	zBOOL exActive = zexhnd.GetIsActive();
	zexhnd.SetIsActive(FALSE);

	CRASH_CODE
	__except(zexhnd.AssertExceptionFilter(GetExceptionInformation(),&afInfo,&exInfo)){};

	zexhnd.SetIsActive(exActive);

	afInfo.extInfo = (void*)&exInfo;
	AssertSpyInfo ( &afInfo, &exInfo);

	// Show dialog
	winDialogParamFinal(DIALOG_ASSERT, ASSERTDlgProc, (zDWORD)&afInfo);
	sysExit();														  // Exit!
}

//
// Return true if a debugger is present, return false if a debugger is not present
//

static zBOOL didDebuggerCheck = FALSE;
static int (__stdcall * gotDebugger)();

zBOOL sysGotDebugger()
{
	// Check if we've already imported IsDebuggerPresent() from Kernel32.dll
	if (!didDebuggerCheck)
	{
		HINSTANCE hKernel  = LoadLibrary("kernel32.dll");
		FARPROC   dbgCheck = GetProcAddress(hKernel, "IsDebuggerPresent");

		gotDebugger = dbgCheck;
		didDebuggerCheck = TRUE;
	}
	
	// Do debugger check
	return (gotDebugger==NULL) ? FALSE: gotDebugger();
}


//
// Create a mouse message from the wParam and lParam of a mouse message (this holds the mouse
// position and coordinates).
//
void inCreateMouseMessage(DWORD wParam, DWORD lParam)
{
  static  zLONG OldX=-1, OldY=-1, OldButtons=0;						// Old X and Y values
  LPMOUSE_MESSAGE pMsg; 											// -> Current mouse message
  zBYTE	  tMsg=0;													// Mouse message to place
  zLONG	  x=LOWORD(lParam); 										// Mouse X position
  zLONG	  y=HIWORD(lParam); 										// Mouse Y position
  zLONG	  bMask, Buttons=(wParam & 3) | ((wParam & 0x10)>>2);		// Only with proper MK_* defs!
  zLONG	  i;														// Counter
  ENTER_PROC(inCreateMouseMessage);

  ASSERT((MK_LBUTTON==0x01) && (MK_RBUTTON==0x02) && (MK_MBUTTON==0x10));

  if (winMinimized) EXIT_PROC();									// Don't do new messages

  // Convert X and Y client coordinates to Application's screen coordinates
  if ((x != 0xFFFF) && (isWindowed()))								// Only if not offscreen and in window
  {
	x=x*VideoW/(winWindowSize.right+1); 							// Adjust X for scaled window
	y=y*VideoH/(winWindowSize.bottom+1);							// Adjust Y for scaled window
  }
  mouseInf.Buttons=Buttons; 										// Copy buttons

  // Check for mouse movement
  if ((x!=OldX) || (y!=OldY))										// Movement?
  {
	tMsg=MMSG_MOVE; 												// Move message
	OldX=x; OldY=y; 												// Update variables
  }

  // Check for button changes
  bMask=Buttons^OldButtons; 										// Button flip mask
  OldButtons=Buttons;												// Update OldButtons
  for (i=0; i<3; i++)												// Check mouse buttons
	if (bMask & (1<<i)) 											// Changed this button?
	{
	  tMsg=MMSG_LBUP+(2*i)-((Buttons>>i) & 1);						// <MMSG Base>-<New State>
	  break;
	}

  // If we have a message, place it
  if (tMsg)
  {
	// If previous message is an unread MMSG_MOVE message, overwrite it.
	if ((mouseInf.MsgCur>mouseInf.MsgRead) && (mouseInf.mMsg[(mouseInf.MsgCur-1) & (MOUSE_QUEUESIZE-1)].bMsg==MMSG_MOVE))
	  mouseInf.MsgCur--;											// Overwrite previous

	// Write new message
	pMsg=&mouseInf.mMsg[mouseInf.MsgCur & (MOUSE_QUEUESIZE-1)]; 	// Message to write
	pMsg->bMsg=tMsg;												// Put message
	pMsg->bButtons=(BYTE)Buttons;									// Put button status
	pMsg->x=(WORD)x;												// Put X coordinate
	pMsg->y=(WORD)y;												// Put Y coordinate
	mouseInf.MsgCur++;												// Wrote a message
  }

  EXIT_PROC();
}
