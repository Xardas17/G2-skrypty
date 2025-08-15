#ifndef __ZVIDEO_WIN32_H__
#define __ZVIDEO_WIN32_H__

#ifndef __DDRAW_INCLUDED__
#include <ddraw.h>
#endif

#ifndef __ZTYPES_H__
#include "zTypes.h"
#endif

#ifndef __ZWIN32_INTERNAL_H__
#include "zWin32_internal.h"
#endif

// Video refresh modes
#define VIDREFRESH_UNKNOWN			(-1)							// Unknown refresh rate
#define VIDREFRESH_ANY				0								// Any refresh rate

// Video modes (system dependant)
#define VIDMODE_ANY 			0								// Any video mode
#define VIDMODE_ANYWINDOWED 	1								// Any windowed mode
#define VIDMODE_ANYFULLSCREEN	2								// Any fullscreen mode
#define VIDMODE_DDRAWWIN		3								// Directdraw windowed
#define VIDMODE_DIB 			4								// Windowed DIBSection
#define VIDMODE_DDRAW			5								// DirectDraw Fullscreen
#define VIDMODE_DIRECT3D		6								// Direct3D Fullscreen
#define VIDMODES				7								// 7 Video modes for Win32

// Video memory types
#define VIDMEM_ANY					0								// Put it anywhere
#define VIDMEM_VIDEO				1								// Video memory
#define VIDMEM_NONLOCALVIDEO		2								// Non-local video memory
#define VIDMEM_SYSTEM				3								// System memory

#define VCAPS_HARDWARE				0x00000001						// Hardware support in mode
#define VCAPS_BANKSWITCHED			0x00000002						// Bankswitched video mode
#define VCAPS_3D					0x00000004						// 3D Support
#define VCAPS_BLIT					0x00000008						// Hardware blitter
#define VCAPS_BLITQUEUE 			0x00000010						// Async blit queue
#define VCAPS_BLITSTRETCH			0x00000020						// Hardware stretch support
#define VCAPS_BLITSYSMEM			0x00000040						// Blits system memory
#define VCAPS_ALPHA 				0x00000080						// Alpha support
#define VCAPS_NONLOCALVIDMEM		0x00000100						// Supports non-local video memory
#define VCAPS_AUTODMA				0x00000200						// Automatic DMA support
#define VCAPS_WIDESURF				0x00000400						// Wide surface support

// Video access modes
#define VAM_SIMPLE					0								// Simple video mode
#define VAM_DIRECT					1								// Direct-write video mode

// Blit commands
#define BLIT_NONE					0								// No operation
#define BLIT_COPY					1								// Copy Source -> Dest
#define BLIT_SCKEY					2								// Copy with source color key
#define BLIT_CALPHA_COPY			3								// Blit with constant alpha
#define BLIT_CALPHA_SCKEY			4								// Blit with constant alpha and source color key
#define BLIT_FILLRECT				5								// Fill with single color
#define BLIT_COMMANDS				6								// Amount of blit commands

// Blit information for each command
#define BLTI_NOSUPPORT				0								// No blit support
#define BLTI_SOFTWARE_SLOW			1								// Slow software support
#define BLTI_SOFTWARE				2								// Normal software support
#define BLTI_SOFTWARE_FAST			3								// Fast software support
#define BLTI_HARDWARE				4								// Hardware support

// Stretching defines
#define VIDSTRETCH_NONE 			0								// No stretching
#define VIDSTRETCH_FREE 			1								// Free window resizing
#define VIDSTRETCH_SNAP 			2								// Scale by integer factors
#define VIDSTRETCH_USER 			3								// Free or snap up to user
#define VIDSTRETCH_CALLBACK 		4								// Stretch using callback function
#define VIDSTRETCH_MODES			5								// Amount of stretch modes


// Defines for the APISpecific[] DWORDS in SURFACE structures
#define API_PTR                 0                                   // Mem Surface: Pointer
#define API_PITCH               1                                   // Mem Surface: Pitch
#define API_DDSURF              0                                   // DDraw Surface: ->DDSURFACE
#define API_MODE                2                                   // Video mode (VIDMODE_*)
#define API_MEMSTAMP            3                                   // Memory cycle stamp
#define API_BACKUP              4                                   // Surface data backup

// Macros that modify the video "busy" state
#define isBusyWith(flag)        ((vidBusyMode & VIDBUSY_##flag)!=0)
#define vidSetBusyWith(flag)    ((void)(vidBusyMode |= VIDBUSY_##flag))
#define vidSetDoneWith(flag)    ((void)(vidBusyMode &= ~(VIDBUSY_##flag)))

// Video busy modifiers
#define VIDBUSY_MINIMIZING		0x01								// Busy with minimizing
#define VIDBUSY_RESTORING		0x02								// Busy with restoring
#define VIDBUSY_SETMODE			0x04								// Busy with setting mode
#define VIDBUSY_DISPLAYCLOSE	0x08								// Busy with closing display


// Palette types
#define PALETTE_16					0x00							// 16 Bit native palette
#define PALETTE_32					0x01							// 32 Bit native palette

//
// Structures
//
typedef BOOL (__cdecl * LPCFUNCP)(LPVOID);

// Video mode extended information structure
typedef struct
{
	zBOOL	bOnlyFullScreen;										// Only operate on fullscreen
	zBOOL	bHideMenu;												// Hide menu
	zBOOL	bDisableMenuKeys;										// Disable menu keys
	zBOOL	bDisableAltEnter;										// Disable Alt+Enter
	zBOOL	bDisableCtrlAltDel;										// Disable Ctrl+Alt+Del in FullScreen mode
	zBOOL	bAllowMinimizeWindow;									// Allow windowed mode to minimize to taskbar
	zDWORD	dwShowBitDepths;										// Bit masks for bit depths on menu
	zDWORD	dwEnableBitDepths;										// Bit masks for bit depths to enable
	zDWORD	dwStretch;												// Stretch mode
	LPCFUNC	fnAltEnter;												// Alt+Enter handler
	LPCFUNCP fnCheckVMode;											// Check Video Mode add proc
	LPCFUNCP fnSetVideoMode;										// Set video size proc
} VIDEO_INFO, *LPVIDEO_INFO;

// Video memory information structure
typedef struct
{
	zDWORD	vidMem;													// Local video memory available
	zDWORD	vidMemFree;												// Local video memory free
	zDWORD	agpMem;													// AGP memory available
	zDWORD	agpMemFree;												// AGP memory free
} VIDMEM_INFO;

// Surface information structure
typedef struct
{
	zBYTE	MemType;												// Type of video buffer memory
	zDWORD	Width;													// Width of video mode
	zDWORD	Height;													// Height of video mode
	zBYTE	BPP;													// Bits/pixel
	zBOOL	rgbMasksValid;											// RGB Masks specified?
	zDWORD	rgbRMask;												// Red color component mask
	zDWORD	rgbGMask;												// Green color component mask
	zDWORD	rgbBMask;												// Blue color component mask
} SURFACE_INFO, *LPSURFACE_INFO;

// Video surface information structure
typedef struct
{
	SURFACE_INFO  si;												// Surface info
	zBYTE	*Ptr;													// -> Data (if locked, NULL if not locked)
	zDWORD	Pitch;													// Bytes/line
	zDWORD	APISpecific[5]; 										// API specific DWORDs
	zBOOL	Lost;													// Surface contents lost?
	void	*pNext, *pPrev;											// -> Next & Previous surface
} SURFACE, *LPSURFACE;

// Single video mode information structure
typedef struct
{
	SURFACE_INFO  si;												// Video mode visual properties
	zBYTE	hwModeType; 											// System dependant mode type
	zBYTE	AccessMode; 											// Simple, nondirect or direct access
	zBYTE	VidMemBuffers;											// Video memory buffers
	zBYTE	SysMemBuffers;											// System memory buffers
	zBYTE	BlitInfo[BLIT_COMMANDS];								// Video blitter info
	zDWORD	APISpecific[4]; 										// API specific DWORDs
} VIDMODE, *LPVIDMODE;

// Video blitter command
typedef struct
{
	SURFACE *dstSurf;												// -> Destination surface
	RECT	*dstRect;												// -> Destination rect
	SURFACE *srcSurf;												// -> Source surface
	RECT	*srcRect;												// -> Source rect
	zDWORD	Command;												// Blit command
	zDWORD	Data;													// Command data
} BLIT_CMD, *LPBLIT_CMD;


// Prototypes
//extern	void	FASTCALL vidInit();									// Initialise video routines
//extern	void	FASTCALL vidExit();									// Close entire video subsystem
extern	void	FASTCALL vidPaintWindow(HWND hWnd);					// Paint contents of window
extern	void	FASTCALL vidCloseDisplay(zBOOL Resizing);			// Close display object
extern	void	FASTCALL vidToggleFullScreenMode();					// Toggle fullscreen mode
extern	void	FASTCALL vidMinimize(zBOOL WaitRestore);				// Minimize fullscreen window
extern	void	FASTCALL vidWaitRestore();							// Wait until app restores
extern	void	FASTCALL vidRestore();								// Restore from minimized mode
extern	void	FASTCALL vidWaitScreenUnblank();					// Wait until screen unblanks
extern	void	FASTCALL vidInitWindowForFullScreen();				// Initialise window for fullscreen stuff
extern	zBOOL	FASTCALL vidLostFocus();							// Lost fullscreen focus?
extern	zBOOL	FASTCALL SetVMode(LPVIDMODE NewMode);				// Set <NewMode>

extern	char	*vidGetScreenModeName(int Mode);					// Get screen mode name
extern	int		vidGetModeList(VIDMODE *Filter, VIDMODE *pModes, int MaxModes); // Get video mode list
extern	char	*vidGetLastError();									// Get last error string
extern	zDWORD	vidGetCaps(zDWORD Mode);								// Get video mode caps
extern	zBOOL	vidGetMemInfo(VIDMEM_INFO *pMemInfo);				// Get memory information
extern	void	vidRefreshModeList();								// Refresh global mode list
extern	zBOOL	vidSetModeEx(VIDEO_INFO *lpVidInfo);				// Set extended video options
extern	zBOOL	vidCreatePalette(int Type, void *Dest, void *Source, int Colors); // Create special palette
extern	zBOOL	vidSetMode(VIDMODE *NewMode);						// Set Video Mode
extern	void	vidSetFrameReady(); 								// Mark frame as ready
extern	zBOOL	vidSetColorKey(SURFACE *Surface, zDWORD Color); 		// Set color key for surface
extern	SURFACE *vidGetStdSurface(int MemType, int BufNum); 		// Get standard surface
extern	SURFACE *vidCreateSurface(SURFACE_INFO *SurfDesc);			// Create video surface
extern	zBOOL	vidFreeSurface(SURFACE *Surf); 						// Free video surface
extern	void	vidSetPalette(zBYTE *Palette, zBOOL SysColors);		// Set palette for video mode
extern	zBOOL	vidBlit(BLIT_CMD *pBlit);							// Do single blit
extern	zBOOL	vidBlitBatch(BLIT_CMD *pBlits, int nBlits);			// Perform batch blit
extern	void	vidWaitVSYNC(); 									// Wait for the vertical blank
extern	zBOOL	vidIsMinimized();									// Check to see if window is minimized
extern	zBOOL	vidFlip();											// Flip to destinatio surface
extern	zBOOL	vidLock(SURFACE *Surf);								// Lock specified surface
extern	zBOOL	vidUnLock(SURFACE *Surf);							// UnLock specified surface
extern	int		vidGetFPSRate();									// Get FPS rate


// External Data
extern  int		vidGotMode[VIDMODES];								// Got this video mode?
extern	zBOOL	vidAllowMinimizeWindow;								// Allow minimize to taskbar?
extern	zBOOL	vidCheckMemory;										// Check video memory amounts?
extern  zDWORD	vidBusyMode;										// Video busy mode
extern  zBOOL	vidOnlyFullScreen;									// Only operate in fullscreen mode
extern	zBOOL	vidHideMenu;										// Hide menu?
extern	zBOOL	vidDisableMenuKeys;									// Disable menu?
extern	zBOOL	vidDisableAltEnter;									// Disable ALT+ENTER?
extern  zDWORD	vidShowBitDepths;									// Bit depths to show
extern  zDWORD	vidEnableBitDepths;									// Bit depths to enable
extern  zDWORD	vidWindowStretch;									// Window snap mode
extern  zDWORD	vidFreeStretch;										// FALSE, TRUE or 2 (NONE)
extern  zDWORD	vidDefSize[32];										// Default window sizes
extern  int		vidnModes;											// Amount of video modes
extern	zBOOL	vidSetModeCalled;									// TRUE if once called.
extern  VIDMODE	*vidpModes;											// -> Video modes
extern  LPCFUNCP winSetVideoMode;									// CALLBACK to set video mode
extern  LPCFUNCP vidModeFilter;										// CALLBACK to enumerate VModes
extern	zBYTE	*Video;												// -> Video memory
extern	zLONG	VideoPitch; 										// Pitch of screen
extern	zLONG	VideoW; 											// Width of screen
extern	zLONG	VideoH; 											// Height of screen
extern	zLONG	VideoBPP;											// Screen bits/pixel
extern	zLONG	VideoBPPShift;										// Video shifter
extern	zDWORD	VideoRGBSize;										// Video RGB Mask (as in 0x565)
extern	zDWORD	VideoRPos, VideoRSize, VideoRMask;					// Red color element position & size
extern	zDWORD	VideoGPos, VideoGSize, VideoGMask;					// Green color element position & size
extern	zDWORD	VideoBPos, VideoBSize, VideoBMask;					// Blue color element position & size
extern	VIDMODE VideoModeCur;										// Current video mode info
extern	VIDMODE VideoHwModeCur; 									// Current hardware video mode info
extern	zBOOL	vidDontShowErrors;									// Suppress error flag

// Macros for checking what state you're in
#define isFullScreen()			(VideoHwModeCur.hwModeType==VIDMODE_DDRAW)
#define isDirectDraw()			(VideoHwModeCur.hwModeType==VIDMODE_DDRAW)
#define isWindowed()			(VideoHwModeCur.hwModeType==VIDMODE_DIB)
#define isValidMode()			(isWindowed() || isFullScreen())

#define isVModeDirectDraw(mode)	((mode)->hwModeType==VIDMODE_DDRAW)
#define isVModeDispDIB(mode)	((mode)->hwModeType==VIDMODE_DIB)
#define isVModeWindowed(mode)	((mode)->hwModeType==VIDMODE_DIB)
#define isVModeFullScreen(mode)	((mode)->hwModeType==VIDMODE_DDRAW)
#define isVModeValid(mode)		(isVModeDirectDraw(mode) || isVModeDispDIB(mode))

#define isVideoBusy()			(vidBusyMode != 0)
#define isVideoCritical()		((vidBusyMode & (VIDBUSY_MINIMIZING | VIDBUSY_RESTORING)) != 0)

// These macros check if the display is active (not busy or minimized) in either mode
#define isActiveWindowed()		(isWindowed()	&& (!IsIconic(hWndApp)) && (!isVideoCritical()))
#define isActiveFullScreen()	(isFullScreen()	&& (!IsIconic(hWndApp)) && (!isVideoCritical()) && (vidSetModeCalled))

#ifdef NDEBUG
	extern zBOOL (FASTCALL *vidBlitFunc[BLIT_COMMANDS])(BLIT_CMD *pBlit); // -> Blit functions
	static zBOOL INLINE vidBlitEx(SURFACE *dstSurf, RECT *dstRect, SURFACE *srcSurf, RECT *srcRect, int Command, zDWORD Data) { BLIT_CMD bCmd; bCmd.dstSurf=dstSurf; bCmd.dstRect=dstRect; bCmd.srcSurf=srcSurf; bCmd.srcRect=srcRect; bCmd.Command=Command; bCmd.Data=Data; return (VideoHwModeCur.hwModeType==VIDMODE_DDRAW) ? vidBlitFunc[Command](&bCmd) : vidBlit(&bCmd); }
#else	// NDEBUG??
	extern  zBOOL    vidBlitEx(SURFACE *dstSurf, RECT *dstRect, SURFACE *srcSurf, RECT *srcRect, int Command, zDWORD Data);
#endif	// NDEBUG??

//
// Interface for custom caption renderer
//

typedef struct
{
  HICON   hIcon;                                                    // Icon to use for caption
  zLONG    iButtons;                                                 // Buttons on caption
  HDC     hDC;                                                      // Device context
  HBITMAP hBmp;                                                     // Bitmap
  zLONG    iWidth;                                                   // Width of caption
  zLONG    winWidth;                                                 // Width of window
  zBOOL    bActive;                                                  // Active or not?
  zBOOL    bSizeBorder;                                              // Set to TRUE for sizing frame
  zDWORD   bmpWidth;                                                 // Width of bitmap (in 32-pixel units)
  zBYTE * bmpData;                                                  // -> Data of image
  zBYTE * bmpBackground;                                            // -> Background image
} CUSTOMCAPTION;

extern  void  ccRenderCaption(HWND hwnd, CUSTOMCAPTION *cap);
extern  void  ccDrawCaption(HWND wnd, CUSTOMCAPTION *cap, zBOOL Active, HRGN Clip);

// Macros for processing nonclient messages for custom captions
#define ccCHECK_RESIZE(obj, wnd, rect) { \
	if ((rect).right - (rect).left != (obj).winWidth) { \
		ccRenderCaption((wnd), &(obj)); \
		(obj).winWidth=(rect).right-(rect).left; } \
}

#define ccWM_INITDIALOG(wnd, obj, but, icon, size) \
		SetWindowLong((wnd), GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW); \
		SetForegroundWindowEx((wnd)); \
		while (winCursorShowState<0) winCursorShowState=ShowCursor(TRUE); \
		memZero(&(obj), sizeof(obj)); \
		(obj).iButtons=(but); \
		(obj).hIcon=(icon); \
		(obj).bSizeBorder=(size); \
		ccRenderCaption((wnd), &(obj));

#define ccWM_NCLBUTTONDOWN(obj, wnd) \
	case WM_NCLBUTTONDOWN: \
		if ((obj).bActive==FALSE) break; \
		DefWindowProc((wnd), WM_NCLBUTTONDOWN, wParam, lParam); \
		ccDrawCaption((wnd), &(obj), GetActiveWindow()==(wnd), NULL); \
		RETURN(TRUE);

#define ccWM_ACTIVATE(obj, wnd) \
	case WM_ACTIVATE: \
		if ((obj).bActive==FALSE) break; \
		ccDrawCaption((wnd), &(obj), (wParam==WA_ACTIVE) || (wParam==WA_CLICKACTIVE), NULL); \
		RETURN(TRUE);

#define ccWM_NCACTIVATE(obj, wnd) \
	case WM_NCACTIVATE: \
		if ((obj).bActive==FALSE) break; \
		ccDrawCaption((wnd), &(obj), (zBOOL)wParam, NULL); \
		RETURN(wParam);

#define ccWM_NCPAINT(obj, wnd) \
	case WM_NCPAINT: \
		if ((obj).bActive==FALSE) break; \
		GetWindowRect((wnd), &cWinSize); \
		ccCHECK_RESIZE((obj), (wnd), cWinSize); \
		if (wParam<=1) \
		{ \
			newRgn=CreateRectRgnIndirect(&cWinSize); \
			ccDrawCaption((wnd), &(obj), GetActiveWindow()==(wnd), newRgn); \
			DefWindowProc((wnd), WM_NCPAINT, (WPARAM)newRgn, lParam); \
			DeleteObject(newRgn); \
		} \
		else \
		{ \
			ccDrawCaption((wnd), &(obj), GetActiveWindow()==(wnd), (HRGN)wParam); \
			DefWindowProc((wnd), WM_NCPAINT, wParam, lParam); \
		} \
		RETURN(TRUE);

#define ccWM_SETCURSOR_BODY() \
		if ((LOWORD(lParam)==HTBOTTOM) || (LOWORD(lParam)==HTTOP)) \
			SetCursor(LoadCursor(NULL, IDC_SIZENS)); \
		else if ((LOWORD(lParam)==HTLEFT) || (LOWORD(lParam)==HTRIGHT)) \
			SetCursor(LoadCursor(NULL, IDC_SIZEWE)); \
		else if ((LOWORD(lParam)==HTTOPLEFT) || (LOWORD(lParam)==HTBOTTOMRIGHT)) \
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); \
		else if ((LOWORD(lParam)==HTTOPRIGHT) || (LOWORD(lParam)==HTBOTTOMLEFT)) \
			SetCursor(LoadCursor(NULL, IDC_SIZENESW)); \
		else \
			SetCursor(LoadCursor(NULL, IDC_ARROW)); \
		RETURN(TRUE);

#define ccWM_SETCURSOR() \
		case WM_SETCURSOR: \
		ccWM_SETCURSOR_BODY()

#define ccWM_SETTINGCHANGE(obj, wnd) \
		case WM_SYSCOLORCHANGE: \
		case WM_DEVMODECHANGE: \
		case WM_SETTINGCHANGE: \
			winBPP=GetDeviceCaps(dcScreen, BITSPIXEL); \
			ccRenderCaption((wnd), &(obj)); \
			RETURN(TRUE); \

#define ccWM_FILTER(obj, wnd) \
		ccWM_SETTINGCHANGE((obj), (wnd)); \
		ccWM_ACTIVATE((obj), (wnd)); \
		ccWM_NCACTIVATE((obj), (wnd)); \
		ccWM_NCPAINT((obj), (wnd)); \
		ccWM_NCLBUTTONDOWN((obj), (wnd)); \
		ccWM_SETCURSOR();


#endif