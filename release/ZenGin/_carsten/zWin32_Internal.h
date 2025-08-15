#ifndef __WINCORE_H__
#define __WINCORE_H__

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

#ifndef _INC_WINDOWS
#include <windows.h>
#endif

// Palette data
#pragma pack (push, 1)
typedef struct
{
	unsigned short int	palVersion;
	unsigned short int	palNumEntries;
	PALETTEENTRY	palPalEntry[256];
} LARGELOGPAL;
#pragma pack (pop)

#pragma pack (4)

typedef zBOOL (__cdecl * LPCFUNC)(unsigned long);

// Macros
#define max(a,b)					(((a) > (b)) ? (a) : (b))
#define min(a,b)					(((a) < (b)) ? (a) : (b))
#define clip(a,l,h) 				((a) < (l)) ? (l) : (((a) > (h)) ? (h) : (a))

#define MAKEDWORD(a,b)				((unsigned long)(((unsigned short int)(a)) | ((unsigned long)((unsigned short int) (b)))<<16))


// Debug/tracing
// Call stacks, assertions, etc
#ifdef	_DEBUG
extern	void	__cs_error();
#ifdef _WIN32
extern __declspec( thread ) char *__cs_data[1024];
extern __declspec( thread ) int  __cs_idx;
#else
extern	char  *__cs_data[];
extern	int   __cs_idx;
#endif

// Various traces/debug code
#define DEBUG_ONLY(f)				f
#define ASSERT(f)					if (!(f)) { DEBUG_BREAK(); ASSERT_FAIL(#f, __FILE__, __LINE__, NULL); }
#define ASSERTT(f, s)				if (!(f)) { DEBUG_BREAK(); ASSERT_FAIL(#f, __FILE__, __LINE__, (s)); }
#define TRACE_DEBUG 				TRACE
#define TRACE_VAR(var, fmt) 		TRACE("" #var " = " ##fmt, (var));
#define BOUNDS(var, l, h)			if (((var)<(l)) || ((var)>(h))) { DEBUG_BREAK(); BOUNDS_FAIL(#var, var, l, h, __FILE__, __LINE__, NULL); }

#ifdef _PROFILE
// Profile time of each function in ENTER_PROC and EXIT_PROC
#define ENTER_PROC(proc)			unsigned long __tstart=sysGetTime(); static char * __cs_funcname="" #proc ""; __cs_data[__cs_idx++]=__cs_funcname; 
#define EXIT_PROC() 				{ if (sysGetTime()-__tstart>5) TRACE("%-40s %u", __cs_data[__cs_idx-1], sysGetTime()-__tstart); return; }
#define RETURN(f)					{ if (sysGetTime()-__tstart>5) TRACE("%-40s %u", __cs_data[__cs_idx-1], sysGetTime()-__tstart); return (f); }
#else
#define ENTER_PROC(proc)			static char * __cs_funcname="" #proc ""; __cs_data[__cs_idx++]=__cs_funcname; 
#define EXIT_PROC() 				{ if (__cs_data[--__cs_idx]!=__cs_funcname) __cs_error();  return; }
#define RETURN(f)					{ if (__cs_data[--__cs_idx]!=__cs_funcname) __cs_error();  return (f); }
#endif

#else	// ?_DEBUG

#define DEBUG_ONLY(f)				((void)(0))
#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(f)					((void)(0))
#define ASSERTT(f, s)				((void)(0))
#define TRACE_DEBUG 				1 ? (void)0 : TRACE
#define TRACE_VAR(var, fmt) 		TRACE("" #var " = " ##fmt, (var));
#define BOUNDS(var, l, h)			((void)(0))
#define ENTER_PROC(proc)			((void)(0))
#define EXIT_PROC() 				{ return; }
#define RETURN(f)					{ return (f); }
#endif	// ?_DEBUG


// Win32/DOS platform specifics
#if defined(_WIN32)
	#undef _WINDOWS
	#undef WINDOWS
	#define _WINDOWS
	#define WINDOWS
#endif

// Language extensions
#define INLINE  __inline
#define FASTCALL __fastcall


// Power-management defines
#define PWR_NORMAL					0x00							// Normal power-saving state
#define PWR_NOSCREENSAVE			0x01							// Don't allow screen saver
#define PWR_NOSUSPEND				0x02							// Don't allow power suspend
#define PWR_BUSY					0x03							// Don't allow screen saver or suspend

// Mouse messages
#define MMSG_MOVE					1								// Mouse moved
#define MMSG_LBDOWN 				2								// Left mouse button pressed
#define MMSG_LBUP					3								// left mouse button released
#define MMSG_RBDOWN 				4								// Right mouse button pressed
#define MMSG_RBUP					5								// Right mouse button released
#define MMSG_MBDOWN 				6								// Middle mouse button pressed
#define MMSG_MBUP					7								// Middle mouse button released

// Menu item types
#define MENU_NONE					0x00							// Empty flag
#define MENU_SUBMENU				0x01							// Sub-menu
#define MENU_ENDSUBMENU 			0x02							// End of sub-menu
#define MENU_LINE					0x10							// Horizontal line
#define MENU_END_OF_MENU			0x11							// End of menu
#define MENU_TEXT					0x20							// Menu text item
#define MENU_ACTION 				0x21							// Do user action (callback)
#define MENU_TOGGLE 				0x22							// Toggle zBOOL Item
#define MENU_TOGGLEBMASK			0x23							// Toggle BYTE Item
#define MENU_TOGGLEDMASK			0x24							// Toggle unsigned long Item
#define MENU_RADIO					0x25							// Radio button item
#define MENU_VID_BPP				0x30							// Video bit depths
#define MENU_VID_WINMODES			0x31							// Video windowed modes
#define MENU_VID_FSMODES			0x32							// Video fullscreen modes
#define MENU_VID_FSTRETCH			0x33							// Video free-stretch toggle
#define MENU_WWWBROWSE				0x40							// Start WWW Browser
#define MENU_READRTF				0x41							// Read RTF file
#define MENU_SOUNDMUS				0x42							// Sound and Music Properties dialog
#define MENU_MUTEMUS				0x43							// Toggle Mute Music
#define MENU_MUTESND				0x44							// Toggle Mute Sound
#define MENU_EXIT					0x45							// Set usrWantExit to TRUE
#define MENU_PAUSE					0x46							// Set usrWantPause to TRUE

// Flags to apply to menu items
#define MENUSTYLE_GRAYED			0x1000							// Disable (grey) menu item
#define MENUSTYLE_CHECK 			0x2000							// Check (mark) menu item
#define MENUSTYLE_RADIOCHECK		0x4000							// Radio check (dot) menu item
#define MENUSTYLE_HIDDEN			0x8000							// Hide menu item


// Menu item structure
typedef struct
{
	unsigned short int	Type;													// Menu item type
	unsigned short int	ID;														// Identifier
	char	*Text;													// Menu item text
	void	*pCommand;												// Command pointer
	unsigned long	CommandData;											// Command data
} MENUITEM, *LPMENUITEM;

// System time struct
typedef struct
{
	int		Year;     
	int		Month; 
    int		DayOfWeek;     
	int		Day;     
	int		Hour;     
	int		Minute; 
    int		Second;     
	int		Milliseconds;
} SYSTEM_TIME, *LPSYSTEM_TIME; 



extern	zBOOL	usrSafeMode;										// User in safe mode
extern	zBOOL	usrWantPause;										// User wants to pause
extern	zBOOL	usrWantQuit;										// User wants to quit

// Data
extern	zBOOL	winNT;												// Running on Windows NT?
extern	int		winBPP;												// Windows display mode depth
extern	zBOOL	winMinimized;										// User in minimized fullscreen?
extern	int		winCursorShowState;									// Cursor show state
extern	unsigned long	sysTimeGap;											// Gap in time measurements
extern	int		spyEnable;											// When 1 -> Activate spy
//extern	int		vidGotMode[VIDMODES];								// Video mode enable list
extern	HDC		dcScreen;											// Screen-compatible DC
extern	HWND	hWndApp;											// Application window
extern	HICON	hIconApp;											// Main App's icon
extern	HINSTANCE	hInstApp;										// Application's instance
extern	LARGELOGPAL	vidWinPal;										// LOGPAL with 256 entries

// Functions
extern	void	sysProcessIdle();									// Do system idle time
extern	void	*sysAlloc(unsigned long Size);								// Allocate memory
extern	void	*sysReAlloc(void *ptr, unsigned long Size);					// Resize memory
extern	void	sysFree(void *Block);								// Free memory
extern	void	sysHardExit(char *Message,...);						// Exit with message
extern	void	sysSetWindowMode(zBOOL FullScreen, zBOOL Show);		// Set window style



extern	void	winCreateMenu();									// Create Window menu
extern	void	winResizeMainWindow();								// Resize main window
extern	void	winCalcSizes();										// Calculate window sizes
extern	void	winWaitMessage(WORD Message, DWORD wParam, DWORD wParamAND, DWORD lParam, DWORD lParamAND, zBOOL QuitIfNotMinimized); // Wait for message to arrive
extern	zLONG	winDialog(WORD resID, DLGPROC Proc);				// Do a dialog
extern	zLONG	winDialogParam(WORD resID, DLGPROC Proc, DWORD Param);// Do a dialog with parameter
extern	zLONG	winDialogParamFinal(WORD resID, DLGPROC Proc, DWORD Param); // Do a dialog box before exiting
extern  zBOOL 	CALLBACK ExceptionDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern  zBOOL	CALLBACK ASSERTDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


extern	void	TRACE(char *Message,...);							// Trace program
typedef void (__cdecl *MEMCOPYFUNC)(void *, void *, unsigned long);			// Memory copy function
#define memCopySmall(x,y,z) memcpy((x),(y),(z))
#define memZeroSmall(x,y)	memset((x), 0, (y))
#define memSetSmall(x,y,z)	memset((x),(y),(z))
#define memSet(x,y,z)		memset((x),(y),(z))
#define memZero(x,y)		memset((x), 0, (y))
#define memWipe(x)			memset(&(x), 0, sizeof(x))
extern	MEMCOPYFUNC 		memCopy;

extern	HINSTANCE	hInstApp;										// Application's instance
extern void winDoInstanceCheck();

// Debug functions
#ifdef _DEBUG
extern	void	winDumpMessage(unsigned short int msg, WPARAM wParam, LPARAM lParam);
#endif

#pragma pack ()

#endif