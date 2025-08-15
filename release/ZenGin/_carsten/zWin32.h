//
// Win32 Include file
//
#ifndef __ZWIN32_H__
#define __ZWIN32_H__

#ifndef _INC_WINDOWS
#include  <windows.h>
#endif

#ifndef __ZTYPES3D_H__
#include  "zTypes.h"
#endif

#ifndef __ZSTRING_H__
#include  "zString.h"
#endif

//
// Functions
//

// System functions

extern	zDWORD		sysGetTime		();										// Get current time
extern	void		sysExit			();											// Exit program neatly
extern	void		sysEvent		(); 										// Do system events
extern	void		sysIdle			(int Time);									// Give up time slice
extern	void		sysSetFocus		();										// Set input focus
extern  zBOOL		sysGotDebugger	();
extern  zBOOL		sysHandleExceptions();
extern  bool		sysKillWindowsKeys(bool doit);
extern	void 		sysParseCommandLine(char *Cmd);

extern	bool		SetForegroundWindowEx(HWND Wnd);

// called by exception handler:
extern  int	WINAPI	HandledWinMain	(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw);
extern  int			initializeSystemMFC();

// zerror externals (hier ??)

#define DEBUG_BREAK()	{ if (sysGotDebugger()) { __asm int 3 } }

extern	void		ASSERT_FAIL		(char *, char *, int, const zSTRING &r);
extern	void		BOUNDS_FAIL		(char *, int, int, int, char *, int, const zSTRING& r);
extern	int			MasterExceptionHandler();

//
// Data
//

extern	char	*sysCommandLine; 									// Command line stuff
extern  char	*APP_NAME;
extern	char	*APP_VERSION;

#endif	