#ifndef WIN32
#define WIN32
#endif
#define STRICT

//#include "Types.h"

#include "zcore.h"
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "ddraw.h"

//////////// TEMP HACK
//#undef  DEFINE_GUID
//#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
//        EXTERN_C const GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } } // Linking Module "dxguid.lib"
#include "d3d.h"
//////////// TEMP HACK

#include "zWin32.h"
#include "zWin32_Internal.h"
#include "zVideo_Win32.h"

// Size of the Pixel-Format in a Surface_INFO structure [BPP, rgbMasksValid, rgbXMask]
#define VID_PFSIZE			(offsetof(SURFACE_INFO, rgbBMask)+sizeof(tagSI.rgbBMask)-offsetof(SURFACE_INFO, BPP))
#define ALIGN32(x)			(((x)+31) & (~31))
#define MAX_FPS_COUNT		256

// Global video data
zLONG	VideoW; 													// Width of video screen
zLONG	VideoH; 													// Height of video screen
zLONG	VideoBPP;													// Bits of video screen
zLONG	VideoBPPShift;												// Video shifter
zLONG	VideoPitch; 												// Pitch of video screen
LPBYTE	Video;														// -> Video data
zDWORD	VideoRGBSize=0x565; 										// RGB Size mask
zDWORD	VideoBPos=0,  VideoBSize=5, VideoBMask=0x001f;				// Blue color element position & size
zDWORD	VideoGPos=5,  VideoGSize=6, VideoGMask=0x07e0;				// Green color element position & size
zDWORD	VideoRPos=11, VideoRSize=5, VideoRMask=0xf800;				// Red color element position & size
VIDMODE VideoModeCur   = { { VIDMEM_ANY, 0, 0, 0, FALSE, 0, 0, 0 }, VIDMODE_ANY, VAM_SIMPLE, 0, 0, { 0, 0 } };
VIDMODE VideoHwModeCur = { { VIDMEM_ANY, 0, 0, 0, FALSE, 0, 0, 0 }, 0xFF,		 VAM_SIMPLE, 0, 0, { 0, 0 } };
int 	vidGotMode[VIDMODES]={TRUE, TRUE, -1, -1, TRUE, -1 };		// Got this video mode

// Video data
zBOOL	vidCheckMemory=TRUE;										// Use memory checks
zBOOL	vidDontShowErrors=FALSE;									// Don't show errors in log?
zBOOL	vidOnlyFullScreen=FALSE;									// Only operate in fullscreen mode
zBOOL	vidHideMenu=FALSE;											// Don't hide menu
zBOOL	vidDisableMenuKeys=FALSE;									// Don't disable menu
zBOOL	vidDisableAltEnter=FALSE;									// Disable ALT+ENTER?
zBOOL	vidAllowMinimizeWindow=FALSE;								// Allow minimize to taskbar?
zBOOL	vidResetPaletteOnRestore=FALSE;								// Reset palette on window restore?
zDWORD	vidFreeStretch=FALSE;										// FALSE, TRUE or 2 (NONE)
zDWORD	vidWindowStretch=VIDSTRETCH_SNAP;							// Snap to sizes
zDWORD	vidShowBitDepths=0; 										// Bit depths to show
zDWORD	vidEnableBitDepths=0;										// Bit depths to enable
LPCFUNCP winSetVideoMode=NULL;										// CALLBACK to set video mode
LPCFUNCP vidModeFilter=NULL;										// CALLBACK to enumerate VModes
static LPCFUNC	vidAltEnterHandler=NULL;							// Alt+Enter handler
static zBOOL 	vidDisableCtrlAltDel=FALSE; 						// Disable Ctrl+Alt+Del
static zLONG 	vidDDLastEnumBPP=-1;								// Last enumerated list of modes
LARGELOGPAL 	vidWinPal={0x300, 256}; 							// LOGPAL with 256 entries

// Local Video data
zBOOL	(FASTCALL *vidBlitFunc[BLIT_COMMANDS])(LPBLIT_CMD pBlit);// -> Blit functions
zDWORD	vidDefSize[32]={MAKELONG(320,200), MAKELONG(320,240), MAKELONG(400,300), MAKELONG(512,384), MAKELONG(640,400), MAKELONG(640,480), MAKELONG(800,600),MAKELONG(1024,768), 0};
zBOOL	vidSetModeCalled=FALSE; 									// TRUE if once called.
zDWORD	vidBusyMode=0;												// Modified to indicate current state
VIDMODE *vidpModes=NULL;											// -> Video modes
int 	vidnModes=0;												// Amount of video modes
static char		*vidLastError=NULL;									// Last error string
static int      vidnMaxModes=0;										// Size mode list
static zDWORD	vidFrameTime[MAX_FPS_COUNT];						// Frame times
static zLONG 	vidFrames;											// Index for frame record
static zBOOL 	vidRestartSoundOnRestore=FALSE; 					// Start sound when restoring?
static LPSURFACE vidLL_Last=NULL;									// -> Last linked list surface
static zBOOL (FASTCALL *vidSimpleBlitFunc)(LPBLIT_CMD pBlit);		// Blitter for VAM_SIMPLE modes
static LPSURFACE vidVidBufs[3]={ NULL, NULL, NULL };				// Video memory buffers
static LPSURFACE vidSysBufs[3]={ NULL, NULL, NULL };				// System memory buffers
static SURFACE_INFO tagSI;											// Tag surface info for sizeof()

// Local Video Prototypes
static void 	INLINE	 vidSetRGBMasks();							// Set new mode parameters
static void 	INLINE	 vidLL_RemoveSurface(LPSURFACE Surface);	// Remove surface from linked list
static void		FASTCALL vidResetPalette();							// Wipe out non-static Win32 colors
static void 	FASTCALL vidCompleteSurfaceInfo(LPSURFACE_INFO Dest, LPSURFACE_INFO Source);
static void 	FASTCALL vidRestoreSurface(LPSURFACE pSurf);		// Restore surface data
static LPSURFACE FASTCALL vidCreateSurfaceEx(LPSURFACE_INFO SurfDesc, zBOOL DirectDraw); // Create video surface

// DirectDraw data
static zBOOL 	ddLocked=FALSE; 									// Direct Draw surface locked?
static zBOOL 	ddWindowed=FALSE;									// Windowed activation flag...
static zDWORD	ddMemEstimate=0;									// Estimated amount of memory for surfaces
static int      ddModes = 0;										// Amount of DirectDraw modes
static VIDMODE	*ddMode = NULL;										// -> DirectDraw mode list
static DDPIXELFORMAT ddPixelFormat;									// DirectDraw primary pixel format
static HMODULE	ddLib;												// DDraw.dll
//static IDirectDraw	*dd1 = NULL;								// IDirectDraw interface
//static IDirectDraw2 *dd2 = NULL;									// IDirectDraw2 interface
static IDirectDraw7 *dd7 = NULL;									// IDIrectDraw7 interface
static IDirectDrawPalette *ddPalette = NULL;						// Palette
static IDirectDrawClipper *ddClipper = NULL;						// Clipper
static DDBLTFX	ddBlitFX[BLIT_COMMANDS];							// Blitter FX structs

static HRESULT	(WINAPI *ddCreate)(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter);
static HRESULT	(WINAPI *ddCreateEx)(GUID FAR *lpGUID, LPDIRECTDRAW7 FAR *lplpDD, REFIID iid, IUnknown FAR *pUnkOuter);

// DirectDraw functions
zBOOL   ddCheck(HRESULT res);										// Check DirectDraw result code
//static zBOOL 	DirectDrawCheck();									// Check for DirectDraw support
static void 	DirectDrawSetPalette(); 							// Set palette
static zBOOL 	DirectDrawCreateSurface(LPSURFACE Surface, zDWORD PrimarySurfaces);	// Create a surface
static zBOOL 	DirectDrawFreeSurface(LPSURFACE Surface);			// Free Surface
static zBOOL 	DirectDrawInit(LPVIDMODE NewMode, zBOOL Resizing);	// Init mode
static void 	DirectDrawExit(zBOOL Resizing);						// Exit mode
static void 	DirectDrawGetBackBuffers(LPVIDMODE NewMode);		// Get backbuffers to vidVidBufs[]
static zBOOL 	DirectDrawFlip();									// Flip to a page
static zDWORD	DirectDrawGetCaps();								// Get DirectDraw capabilities
static void 	DirectDrawSave(zBOOL HideWin);						// Save DirectDraw state
static void 	DirectDrawRestore(zBOOL RestoreWin); 				// Restore DirectDraw state
static zBOOL 	DirectDrawLockSurface(LPSURFACE Surface);			// Lock a surface
static zBOOL 	DirectDrawUnLockSurface(LPSURFACE Surface); 		// UnLock a surface
static void		DirectDrawEnumModes(LPCFUNCP Filter);				// Enumerate all DirectDraw modes
static void 	DirectDrawFreeModule(); 							// Free ddraw.dll
static void 	DirectDrawWaitVSYNC();								// Wait for vertical blank
static void 	DirectDrawSetBlitters();							// Install DirectDraw blitters
static zBOOL 	FASTCALL DirectDraw_BLIT_COPY(LPBLIT_CMD pBlit);	// Do DirectDraw copy blit
static zBOOL 	FASTCALL DirectDraw_BLIT_SCKEY(LPBLIT_CMD pBlit);	// Do DirectDraw source color key blit
static zBOOL 	FASTCALL DirectDraw_BLIT_CALPHA_COPY(LPBLIT_CMD pBlit); 	// Do DirectDraw alpha copy blit
static LPDIRECTDRAWSURFACE7 INLINE GetDDSurf(LPSURFACE Surface); 	// Get DirectDraw surface from SURFACE structure

// Direct3D data
//static IDirect3D2	*d3d2 = NULL;									// Direct3D2 interface
static IDirect3D7	*d3d7 = NULL;									// Direct3D7 interface

// Direct3D functions
//static zBOOL 	Direct3DCheck();									// Check for Direct3D presence

// DIBSection data
static HBITMAP	winDIBSection=NULL; 								// DIB Section for OSB's
static HPALETTE winDIBPal=NULL; 									// Windows Palette
static HDC		winDIBDC=NULL;										// DIBSection device context
static BYTE 	winDIBSpace[sizeof(BITMAPINFOHEADER)+1024]; 		// Space for BITMAPINFO

// DIBSection functions
static void 	DIBSectionInit(LPVIDMODE NewMode);					// Init DIBSection
static void 	DIBSectionExit();									// Close DIBSection
static void 	DIBSectionSetPalette(); 							// Set DIB Palette
static void		DIBSectionEnumModes(LPCFUNCP Filter, zDWORD *WinSizes); // Get all DIB modes
static zBOOL 	FASTCALL DIBSection_BLIT_COPY(LPBLIT_CMD pBlit);	// DIBSection blitter

// We work a lot with rects, some macros might be useful, thus:
#define RECT_WIDTH(r)   ((r).right - (r).left)
#define RECT_HEIGHT(r)  ((r).bottom - (r).top)
#define RECT_SIZE(r)    (RECT_WIDTH(r) | (RECT_HEIGHT(r) << 16))

#define PRECT_WIDTH(r)  ((r)->right - (r)->left)
#define PRECT_HEIGHT(r) ((r)->bottom - (r)->top)
#define PRECT_SIZE(r)   (PRECT_WIDTH(r) | (PRECT_HEIGHT(r) << 16))

// Offset a pointer (ptr) when it is on a surface with bppshift (bppsh) and pitch (pitch)
// for the rectangle (rct). The X and Y coordinates offset the base pointer to a source
// or destination surface, this macro does the offset.
#define OFFSET_PTRPRECT(ptr, rct, bppsh, pitch) \
      (ptr)+=(rct)->left << (bppsh); \
      if ((rct)->top) (ptr)+=(rct)->top*(pitch); \

// Blitters
static zBOOL FASTCALL blitCopy(LPBLIT_CMD pBlit);

//
// Activate software blitters
//
static VOID vidSetSwBlitters(VOID)
{
	// Fill blit function table with software blitters
	vidBlitFunc[BLIT_NONE]=NULL;									// No BLIT_NONE
	vidBlitFunc[BLIT_COPY]=blitCopy;								// Set BLIT_COPY
	vidBlitFunc[BLIT_SCKEY]=NULL;									// No source color key	
	vidBlitFunc[BLIT_FILLRECT]=NULL;								// No BLIT_FILLRECT
	vidBlitFunc[BLIT_CALPHA_COPY]=NULL;
	vidBlitFunc[BLIT_CALPHA_SCKEY]=NULL;
}

//
// Normal copy blit
//
static zBOOL FASTCALL blitCopy(LPBLIT_CMD pBlit)
{
  BYTE    BPPShift;                                                 // BPP Shifter
  DWORD   BPL, Lines;                                               // Width (BYTEs) and Height
  LPBYTE  pDest, pSource;                                           // -> Dest, Source surface memory
  DWORD   DestPitch, SourcePitch;                                   // Pitch of destination and source
  
  ENTER_PROC(blitCopy);

  // Grab default source and dest pointer
  pDest = (LPBYTE)pBlit->dstSurf->APISpecific[API_PTR];             // -> Dest memory
  pSource = (LPBYTE)pBlit->srcSurf->APISpecific[API_PTR];           // -> Source memory
  DestPitch = pBlit->dstSurf->APISpecific[API_PITCH];               // Destination pitch
  SourcePitch = pBlit->srcSurf->APISpecific[API_PITCH];             // Source pitch
  BPPShift = pBlit->dstSurf->si.BPP >> 4;                           // 8->0, 16->1, 32->2
  ASSERT(pDest && pSource && DestPitch && SourcePitch);             // Must all be valid

  // Check if we have a dest rectangle, grab width/height, or set up for full screen blit
  if (pBlit->dstRect)
  {
    // Normal blit
    BPL   = PRECT_WIDTH(pBlit->dstRect) << BPPShift;                // Width of line
    Lines = PRECT_HEIGHT(pBlit->dstRect);                           // Height of block
    
    // Offset pointers (these are macros so they're not as slow as they look)
    OFFSET_PTRPRECT(pDest, pBlit->dstRect, BPPShift, DestPitch);
    OFFSET_PTRPRECT(pSource, pBlit->srcRect, BPPShift, SourcePitch);

    // No stretching!
    ASSERTT(PRECT_SIZE(pBlit->dstRect) == PRECT_SIZE(pBlit->srcRect), "Can't do stretchblit");
  }
  else
  {
    // No dest rectangle (blit full screen). This implies that we also
    // can't have a source rectangle (what's the use?)
    ASSERTT(pBlit->srcRect == NULL, "No dest rectangle given, can't specify source either");
    BPL   = pBlit->dstSurf->si.Width << BPPShift;                   // Height of dest
    Lines = pBlit->srcSurf->si.Height;                              // Lines of dest
  
    // We are doing a "full copy", which means that source and dest must be
    // equally sized.
    ASSERT(pBlit->dstSurf->si.Width  == pBlit->srcSurf->si.Width);
    ASSERT(pBlit->dstSurf->si.Height == pBlit->srcSurf->si.Height);
  
    // As we are blitting full screen, we might do this with one linear
    // memcpy instead of the regular loop overhead. Check it.
    if ((BPL==DestPitch) && (DestPitch==SourcePitch))
    {
      memcpy(pDest, pSource, BPL*Lines);                           // Copy in one go
      RETURN(TRUE);                                                 // Done!
    }
  }

  // Copy!
  while (Lines--)
  {
    memcpy(pDest, pSource, BPL);
    pDest   += DestPitch;
    pSource += SourcePitch;
  }

  RETURN(TRUE);
}

// Static callbacks which allways return TRUE or FALSE. You can use these entries if a
// callback is used to override something (for example, to check something) and the
// default behaviour is TRUE or FALSE
#define CFUNCP                  zBOOL __cdecl

static CFUNCP	cfuncpTRUE(LPVOID p)  { return TRUE;  }

#ifndef _DEBUG	// !_DEBUG??

#define ASSERT_VMODE(f) 		((void)(0))
#define ASSERT_NOCLIP(f, g) 	((void)(0))
#define ASSERTRECT(f)			((void)(0))
#define ASSERT_SURFACE(f)		((void)(0))
#define ASSERT_SURFACEINFO(f)	((void)(0))
#else			// _DEBUG

//
// Data used in DEBUG mode
//

//
// Assert that <pRect> doesn't clip the boundaries of <pSurf>
//
static void ASSERT_NOCLIP(RECT *pRect, LPSURFACE pSurf)
{
	ASSERT(pRect->left	 >= (zLONG)0);
	ASSERT(pRect->top	 >= (zLONG)0);
	ASSERT(pRect->right  <= (zLONG)pSurf->si.Width);
	ASSERT(pRect->bottom <= (zLONG)pSurf->si.Height);
}



//
// Assert that <pRect> is a proper rect (no weird top>bottom or anything)
//
static void ASSERTRECT(RECT *pRect)
{
	ENTER_PROC(ASSERTRECT);

	ASSERT(pRect->left <= pRect->right);
	ASSERT(pRect->top  <= pRect->bottom);

	EXIT_PROC();
}

//
// Validate SURFACE_INFO structure
//
static void ASSERT_SURFACEINFO(LPSURFACE_INFO s)
{
	ENTER_PROC(ASSERT_SURFACEINFO);

	ASSERTT(s!=NULL, "Surface pointer is NULL");
	ASSERTT((s->BPP==0) || (s->BPP==8) || (s->BPP==16) || (s->BPP==32), "Illegal BPP");
	ASSERTT((s->rgbMasksValid==TRUE) || (s->rgbMasksValid==FALSE), "Illegal rgbMasksValid");
	ASSERTT((s->MemType==VIDMEM_ANY) || (s->MemType==VIDMEM_VIDEO) || (s->MemType==VIDMEM_NONLOCALVIDEO) || (s->MemType==VIDMEM_SYSTEM), "Illegal MemType");
	ASSERTT(s->Width <= 32768, "Illegal width");
	ASSERTT(s->Height <= 32768, "Illegal height");

	EXIT_PROC();
}

//
// Validate VIDMODE structure
//
static void ASSERT_VMODE(LPVIDMODE m)
{
	ENTER_PROC(ASSERT_VMODE);

	ASSERT(m!=NULL);
	ASSERT_SURFACEINFO(&m->si);
	ASSERT((m->AccessMode==VAM_SIMPLE) || (m->AccessMode==VAM_DIRECT));
	ASSERT(m->hwModeType < VIDMODES);

	if (m->AccessMode==VAM_SIMPLE)
	{
		ASSERT(m->VidMemBuffers==0);
		ASSERT(m->SysMemBuffers==0);
	}
	else
	{
		ASSERTT(m->VidMemBuffers>=1, "You must have at least one video memory buffer in direct-write mode");
	}

	EXIT_PROC();
}
#endif	// ?_DEBUG

//
// Initialise Video stuff
//
//void FASTCALL vidInit()
//{
//	ENTER_PROC(vidInit);
//	
//	TRACE("VID: Checking for available video modes");
//	if (vidGotMode[VIDMODE_DDRAW]==-1)								// No DirectDraw forced?
//	{
//		vidGotMode[VIDMODE_DDRAW]=DirectDrawCheck();				// Check for DirectDraw
//		vidGotMode[VIDMODE_DIRECT3D]=Direct3DCheck();				// Check for Direct3D
//		vidGotMode[VIDMODE_DDRAWWIN]=FALSE;
//		if (vidGotMode[VIDMODE_DDRAWWIN]==-1) vidGotMode[VIDMODE_DDRAWWIN]=vidGotMode[VIDMODE_DDRAW]; // DDWin=DDNormal
//	}
//	else															// DirectDraw forced FALSE
//		TRACE("VID: DirectDraw check skipped on user request"); 	// Show in log
//	vidRefreshModeList();											// Get global mode list
//
//	EXIT_PROC();
//}

//
// Close video subsystem
//
//void FASTCALL vidExit()
//{
//	ENTER_PROC(vidExit);
//	
//	// Close display objects
//	vidCloseDisplay(FALSE); 										  // Close display stuff
//	
//	// Free DirectDraw library if it's there
//	DirectDrawFreeModule(); 										  // Free DirectDraw library
//	
//	EXIT_PROC();
//}

//
// Sort video modes
//
// Modes are sorted in this last (after they have been retrieved) with the
// following criteria:
//	- Mode type: DirectDraw -> DIBSection
//	- Bit depth: 32 -> 16 -> 8
//	- Size: Large to Small
//
static int vidSortModes(const void *arg1, const void *arg2)
{
	LPVIDMODE v1=(LPVIDMODE)arg1;									  // -> Video mode 1
	LPVIDMODE v2=(LPVIDMODE)arg2;									  // -> Video mode 2
	
	ENTER_PROC(vidSortModes);
	
	// Make sure these video modes are correc5
	ASSERT_VMODE(v1);
	ASSERT_VMODE(v2);
	
	// Select on video mode
	if (v1->hwModeType != v2->hwModeType)
	{
		if (v1->hwModeType > v2->hwModeType)
			RETURN(-1)
		else
			RETURN(1)
	}
	// Select on bit depth
	else if (v1->si.BPP != v2->si.BPP)
	{
		if (v1->si.BPP > v2->si.BPP)
			RETURN(-1)
		else
			RETURN(1)
	}
	// Select on size
	else if (v1->si.Width*v1->si.Height != v2->si.Width*v2->si.Height)
	{
		if (v1->si.Width*v1->si.Height > v2->si.Width*v2->si.Height)
			RETURN(-1)
		else
			RETURN(1)
	}
	else RETURN(0)
}



//
// Add a video mode to the list of video modes, called from video mode enumeration routines
//
static void vidAddMode(VIDMODE *vm)
{
	// Check if list needs resizing
	if (++vidnModes > vidnMaxModes)
	{
		// Reallocate memory for array
		vidnMaxModes = (vidnMaxModes>0) ? vidnMaxModes*2 : 16;		// Grow list by factor 2
		vidpModes=(VIDMODE*)sysReAlloc(vidpModes, vidnMaxModes*sizeof(VIDMODE)); // Enough for all modes
	}

	memcpy(vidpModes+vidnModes-1, vm, sizeof(VIDMODE));				// Copy mode
}



//
// Get a list of all video modes available . This list will be stored in
// VideoModeList (static) and is used by vidGetModeList() to filter individual
// entries to user lists.
//
void vidRefreshModeList()
{
	LPCFUNCP  pFilter=cfuncpTRUE;									// -> Callback function to check modes
	ENTER_PROC(vidRefreshModeList);
	
	// Check if we can use the user's callback
	if (vidModeFilter) pFilter=vidModeFilter;						// Use global callback
	
	// Free old list
	if (vidpModes) sysFree(vidpModes);								// Free mode list
	vidpModes=NULL;													// No -> List
	vidnModes=0;													// Nothing yet
	vidnMaxModes=0;													// Nothing in list

	// Add DirectDraw modes
//	if ((vidGotMode[VIDMODE_DDRAW]) || (vidGotMode[VIDMODE_DDRAWWIN]))
//		DirectDrawEnumModes(pFilter);								// Enumerate DirectDraw modes

	// Add DIBSection (windowed) modes
	if ((vidGotMode[VIDMODE_DIB]) && (!vidOnlyFullScreen))			// Don't allow when we can only run in fullscreen mode
		DIBSectionEnumModes(pFilter, vidDefSize);					// Enumerate DIBSection modes
	
	qsort(vidpModes, vidnModes, sizeof(VIDMODE), vidSortModes); 	// Sort video mode list
	
	EXIT_PROC();
}

/**{ vidGetCaps, Video }
@func

The vidGetCaps function is used to determine what type of functionality is supported
in a specified mode. You can use vidGetCaps to enable or disable certain options in
your application, etc.

@params
@return
	The return value is a mode capabilities mask. It is a combination of one of the
	following capability flags.

		VCAPS_HARDWARE		The video mode has direct access to the video hardware. With
							VC_HARDWARE it is possible to create surfaces in video memory,
							pageflip and do other actions that require access to the
							hardware display device.

		VCAPS_BANKSWITCHED	The video memory is actually bank-switched, but "paged flat"
							using the virtual memory manager. Writing directly to video
							memory in bankswitched modes can be extremely slow and writing
							to a non-aligned memory address in video memory can crash
							the computer.

		VCAPS_3D			This video mode is also capable of displaying 3D images

		VCAPS_BLIT			The blit operation is supported by the hardware.

		VCAPS_BLITQUEUE 	The hardware is capable of asynchronous (queued) blitting
							operations.

		VCAPS_BLITSTRETCH	Stretched blits are supported by the hardware.

		VCAPS_BLITSYSMEM	The hardware is capable of blitting to and/or from system
							memory surfaces.

		VCAPS_ALPHA 		The hardware has support for an alpha channel in its pixel-
							pipeline. This means you can either blit with constant alpha
							values, or there is alpha support in the pixel format of this
							mode.

		VCAPS_NONLOCALVIDMEM The hardware supports non-local video memory. Video memory
							doesn't have to be placed on the video board, but other
							memory, such as system memory, might apply too.

		VCAPS_AUTODMA		The hardware automatically supports using DMA for blits
							to and from system memory. There is no need to pagelock the
							appropriate surface for DMA to work.

		VCAPS_WIDESURF		Surfaces wider than the primary buffer (front buffer) can
							be created in video memory.

@portable
@see vidGetModeList
**/
zDWORD vidGetCaps(
	zDWORD Mode				/* Video mode to check capabilities
	Video mode to check capabilities of. This must be a real video mode, such as
	VIDMODE_DDRAW or VIDMODE_DIB and not a pseudo-mode such as VIDMODE_ANYFULLSCREEN. */
)
{
	zDWORD	Caps=0; 												// Capabilities
	ENTER_PROC(vidGetCaps);
	ASSERT(Mode==VIDMODE_DDRAW || Mode==VIDMODE_DIB);				// Must be a *valid* mode

	// DIB mode has no capabilities
	if (Mode==VIDMODE_DIB)											// DIB mode?
		Caps=0; 													// No caps
	else if (Mode==VIDMODE_DDRAW)
		Caps=DirectDrawGetCaps();									// Get DDraw caps

	RETURN(Caps);
}

/**{ vidGetModeList, Video }
@func

The vidGetModeList function aquires a list of available video modes. You can
select between retrieving a list of all modes available or just a
subset by using the VIDMODE structure Filter.

@params
@return
	The return value is the amount of video modes that have been enumerated. If
	there were more than MaxModes modes to be enumerated, the return value will be 0.

@remarks  
	Modes are always return in best-to-worst order. The video modes with the best
	hardware video mode type are returned first. This means you will first find
	DirectDraw modes for Win32, or VBE 2.0 modes for DOS, in general, VAM_DIRECT
	modes come first. Per video hardware mode, video modes are first sorted by
	the amount of bits per pixel, then on screen size (Width*Height). This behavior
	can be used to quickly check what the capabilities of the video board are.

	If you pass a VIDMODE structure, filled with 0's, as Filter you will also get
	a list of all modes, just as though you passed NULL for Filter. This is a
	positive side effect of the fact that all elements of VIDMODE default to 0.
	For example, width 0 means "any width", BPP 0 means "any BPP". This means
	you can take an empty VIDMODE structure, fill in the values you know, and
	pass it on to vidGetModeList. If you set MaxModes to 1, you will get the
	best video mode which matches Filter. This is how vidSetMode handles the
	video modes you pass to it. It calls vidGetModeList to get the best video
	mode that matches Filter, checks that mode and sets it. This also allows
	you to use vidGetModeList to scoop the hardware capabilities.

	Returned hicolor modes don't always have their RGB masks specified.

	An example of how to enumerate video modes:

//
// Show all video modes in log
//
void ShowModeList()
{
	LPVIDMODE	vidMode;
	LPVIDMODE	pMode;
	zDWORD			j, nModes;
	CHAR			ModeString[250];

	// Get mode list
	vidMode=(LPVIDMODE)memAlloc(512*sizeof(VIDMODE));
	nModes=vidGetModeList(NULL, vidMode, 512);
	TRACE("WIN: %u modes enumerated", nModes);

	// Show modes
	for (pMode=vidMode; pMode<vidMode+nModes; pMode++)
	{
		// Show basic mode informations (dimensions, provider, blit type)
		sprintf(ModeString, "Mode %ux%ux%u, VidBuffers %u, hwMode %u, %s",
					pMode->si.Width,	// Width of video mode [*1]
					pMode->si.Height,	// Height of video mode [*1]
					pMode->si.BPP,	// Bits per pixel [*1]
					pMode->VidMemBuffers,	// Number of video buffers
					pMode->hwModeType,	// Hardware mode type [*1]
					pMode->AccessMode==VAM_SIMPLE ? "VAM_SIMPLE" : "VAM_DIRECT");
					// Note: Entries marked with [*1] are always present and valid.

		// Add RGB masks if they are provided
		if (pMode->si.rgbMasksValid)
		{
			// Some data we can use as "shorthand"
			zDWORD rMask=pMode->si.rgbRMask;
			zDWORD gMask=pMode->si.rgbGMask;
			zDWORD bMask=pMode->si.rgbBMask;
			BYTE  mBPP=pMode->si.BPP;
			CHAR  rgbMask[33]="";

			// Create string with 0's in it for the bit spaces
			memSet(rgbMask, '0', mBPP);
			rgbMask[mBPP]=0;

			// Fill components (0 for unused bits, 'rgb' char for used bits)
			for (j=0; j<mBPP; j++)
				if (rMask & (1<<j)) rgbMask[mBPP-j-1]='r';
			for (j=0; j<mBPP; j++)
				if (gMask & (1<<j)) rgbMask[mBPP-j-1]='g';
			for (j=0; j<mBPP; j++)
				if (bMask & (1<<j)) rgbMask[mBPP-j-1]='b';

			sprintf(ModeString+strlen(ModeString), ", mask %s", rgbMask);
		}

		TRACE(ModeString);
	}

	memFree(vidMode);
}

@portable
@see vidSetMode vidSetModeEx
**/
int vidGetModeList(
	VIDMODE *Filter,		/* Video mode filter
	Pointer to a VIDMODE structure that specifies which video modes are to be
	enumerated. If this parameter is NULL, all modes are enumerated. If this
	parameter is not NULL, all modes that match Filter are copied to pModes
	(up to MaxModes entries). */
	
	VIDMODE *pModes,		/* Pointer to result mode list
	Pointer to a list of VIDMODE structures to hold the video mode list. This
	list must be sufficiently large to hold all modes to be enumerated. */
	
	int 	MaxModes		/* Maximum amount of modes to enumerate
	Maximum amount of modes to enumerate. If vidGetModeList reaches this
	maximum value, it stops enumerating and returns the amount of modes
	it enumerated (MaxModes). */
)
{
	VIDMODE *pvidMode;												// -> Current video mode
	ENTER_PROC(vidGetModeList);

	// Check parameters
	ASSERT(pModes);
	if (Filter) ASSERT_VMODE(Filter);
	vidRefreshModeList();											// Refresh global mode list
	
	// Check if the user wants all modes or just a filtered selection
	if (Filter)
	{
		// Copy modes that match <Filter> up to <MaxModes>
		int i, nEnumerated=0;										// Counter
		for (i=0, pvidMode=vidpModes; (i<vidnModes) && (MaxModes); i++, pvidMode++)
		{
			// We check for matches here. If we can't match the current video mode for some
			// reason, use "continue" to break to the next for() iteration (skips this mode).
			// If we pass all tests, we have a good video mode.
			
			// Check required mode type (if not VIDMODE_ANY)
			switch (Filter->hwModeType) {
			case VIDMODE_ANY:			break;
			case VIDMODE_ANYWINDOWED:	if (!isVModeWindowed(pvidMode)) continue;		break;
			case VIDMODE_ANYFULLSCREEN: if (!isVModeFullScreen(pvidMode)) continue; 	break;
			default:					if (pvidMode->hwModeType!=Filter->hwModeType) continue; break;
			}
			
			// Check for mode access
			if ((Filter->AccessMode == VAM_DIRECT) && (pvidMode->AccessMode == VAM_SIMPLE)) continue; // Direct wanted, but only simple supported?
			
			// Check width, height and BPP
			if ((Filter->si.Width)	&& (Filter->si.Width  != pvidMode->si.Width))  continue;
			if ((Filter->si.Height) && (Filter->si.Height != pvidMode->si.Height)) continue;
			if ((Filter->si.BPP)	&& (Filter->si.BPP	  != pvidMode->si.BPP))    continue;
			
			// Check RGB masks (bit position specificness)
			if ((Filter->si.rgbMasksValid) && ((Filter->si.rgbRMask != pvidMode->si.rgbRMask) || (Filter->si.rgbGMask != pvidMode->si.rgbGMask) || (Filter->si.rgbBMask != pvidMode->si.rgbBMask))) continue;
			
			// BINGO!
			//
			// Passed all tests. Copy this mode for the user
			memcpy(pModes, pvidMode, sizeof(VIDMODE));		// Copy video mode
			nEnumerated++;											// Increase enum count
			pModes++;												// Did one more mode
			MaxModes--; 											// One less to do		
			// Note: "for" has condition (MaxModes!=0), exit here if list is full
		}
		
		// Return amount of modes
		RETURN(nEnumerated);										// Return amount of 
	}
	else
	{
		// Copy up to <MaxModes> modes
		int BestModes=min(MaxModes, vidnModes);						// Max modes to copy
		memcpy(pModes, vidpModes, BestModes*sizeof(VIDMODE));		// Copy modes from list
		RETURN(BestModes);											// Return amount written
	}
}

/**{ vidSetModeEx, Video }
@func

The vidSetModeEx function sets the extended video mode attributes. This
includes video modes the user can select from, scaling, and screen sizes.
vidSetModeEx is especially useful in a graphical user interface (such as
Windows 95) where the user can select certain predefined video modes and
stretch windows as desired. vidSetModeEx does not, unlike vidSetMode,
change the current display mode.

For more information read the overview and see @@VIDEO_INFO.

@params
@return
	This function returns TRUE if the call succeeded and FALSE if the call
	failed. This call should not fail unless the lpVidInfo structure has
	not been filled in correctly. You can do a call to vidSetModeEx before
	your first call to vidSetMode to make sure the desired options are
	shown the first time the user sees the game window.

@portable
@see vidSetMode VIDEO_INFO
**/
zBOOL vidSetModeEx(
	LPVIDEO_INFO lpVidInfo	/* Video mode information structure
	Pointer to a valid VIDEO_INFO structure which describes the extended
	options to be set. */
)
{
	ENTER_PROC(vidSetModeEx);
	
	ASSERT(lpVidInfo);												// Must have a pointer!

	// Store global variables
	vidOnlyFullScreen		= lpVidInfo->bOnlyFullScreen;			// Store fullscreen lock mode
	vidHideMenu				= lpVidInfo->bHideMenu;					// Store menu hide flag
	vidDisableMenuKeys		= lpVidInfo->bDisableMenuKeys;			// Store menu disable flag
	vidDisableAltEnter		= lpVidInfo->bDisableAltEnter;			// Store Alt+Enter disable flag
	vidDisableCtrlAltDel	= lpVidInfo->bDisableCtrlAltDel;		// Store Ctrl+Alt+Del disable flag
	vidAllowMinimizeWindow	= lpVidInfo->bAllowMinimizeWindow;		// Store allow-minimize flag
	vidShowBitDepths		= lpVidInfo->dwShowBitDepths;			// Store bit depths to show
	vidEnableBitDepths		= lpVidInfo->dwEnableBitDepths; 		// Store bit depths to enable
	vidWindowStretch		= lpVidInfo->dwStretch; 				// Store stretch mode
	vidModeFilter			= lpVidInfo->fnCheckVMode;				// Store video mode enumerator
	vidAltEnterHandler		= lpVidInfo->fnAltEnter;				// Store ALT+ENTER handler
	winSetVideoMode 		= lpVidInfo->fnSetVideoMode;			// Store video size set proc

	// Check if structure is ok
	ASSERTT((vidShowBitDepths & ~(1+2+4+8))==0, "Illegal dwShowBitDepths in call to vidSetModeEx"); 	// Only valid bit depths (no trash!)
	ASSERTT((vidEnableBitDepths & ~(1+2+4+8))==0, "Illegal dwEnableBitDepths in call to vidSetModeEx"); // Only valid bit depths (no trash!)
	ASSERTT(vidWindowStretch<VIDSTRETCH_MODES, "Illegal dwStretch in call to vidSetModeEx");			// No out of bound modes
	DEBUG_ONLY(if (vidWindowStretch==VIDSTRETCH_CALLBACK) ASSERT(winSetVideoMode)); // Must have callback for resize
	
	// Set variables, depending on winWindowStretch
	vidFreeStretch=FALSE;											// Don't assume free stretch
	if (vidWindowStretch==VIDSTRETCH_FREE) vidFreeStretch=TRUE;		// We have free stretch!
	
	// Set new thingies
	vidRefreshModeList();											// Get mode list
	winCreateMenu();												// Create Win32 menu
	winCalcSizes();													// Calculate size of window
	winResizeMainWindow();											// Resize window (to reflect changes)
	
	RETURN(TRUE);
}

/**{ vidGetScreenModeName, Video }
@func

The vidGetScreenModeName function is used to get the name of a video mode.

@params
@return
	The return value is a pointer to a string containing a description of
	the video mode. This function is frequently used to show the user the
	current video mode.

@remarks
	To get the name of the current video mode, use:
	vidGetScreenModeName(VideoHwModeCur.hwModeType)

@portable
@see vidGetModeList
**/
char *vidGetScreenModeName(
	int 	Mode			/* Video mode to get name of
	Video mode to get name of. You can pass any hardware video mode number
	(see the VIDMODE_ANY, VIDMODE_ANYWINDOWED, … modes). You
	can also get hardware video mode numbers from the hwModeType member of
	VIDMODE structures. */
)
{
	ENTER_PROC(vidGetScreenModeName);
	
	// Check display modes
	switch (Mode) {
	case VIDMODE_ANY:			RETURN("Any compatible mode");
	case VIDMODE_ANYWINDOWED:	RETURN("Any windowed mode");
	case VIDMODE_ANYFULLSCREEN: RETURN("Any fullscreen mode");
	case VIDMODE_DIB:			RETURN("Window (DIB)");
	case VIDMODE_DDRAW: 		RETURN("DirectDraw");
	default:					RETURN(NULL);
	};
}


//
// Reset windows palette (wipes out all non-static colors)
//
void FASTCALL vidResetPalette()
{
	HDC ScreenDC=GetDC(hWndApp);
	SetSystemPaletteUse(ScreenDC, SYSPAL_NOSTATIC); 		// No static colors (0-pal)
	SetSystemPaletteUse(ScreenDC, SYSPAL_STATIC);			// Static colors (normal pal)
	ReleaseDC(hWndApp, ScreenDC);							// Release screen DC
}


/**{ vidSetPalette, Video }
@func

The vidSetPalette function sets the video display palette.

@params
@return
@remarks
	The given Red, Green and Blue values are 8-bits wide. Appropriate
	scaling to fewer bits is done automatically, depending on the hardware.

	The first and last 10 colors are always destroyed (Even when SysColors
	is set to FALSE) when the display is a DIB. No attempt is done to
	re-map the palette. Don't use the first and last 10 colors if you
	want your program to be able to run in a window (DIB).

	vidSetPalette has no effect in non-palletized display modes.
	
	vidSetPalette cannot be called and will exit with an error while the
	video memory is locked with vidLock. Call vidUnLock before issuing
	a call to vidSetPalette.

@portable
@see vidSetMode
**/
void vidSetPalette(
	zBYTE	*Palette,		/* Palette to be set
	Pointer to a 256-color palette. The palette must be in RGB0 layout
	(one zBYTE Red, one zBYTE Green, one zBYTE Blue and a discarded zBYTE).
	Because of Intel's zBYTE ordering (least significant zBYTE first) the
	format of one color entry in a zDWORD is 0x00bbggrr. Color 0 is the
	first color in the palette, color 255 is the last color in the
	palette. The entire palette is 1024 zBYTEs large. */

	zBOOL	SysColors		/* Copy system colors
	If this value is set to TRUE, the palette specified with Palette
	will be modified to include the system palette entries in Win32.
	The first and last 10 colors of the palette will be changed to
	reflect the colors that Windows uses to draw the user interface. */
)
{
	int 	i;														// Index
	ENTER_PROC(vidSetPalette);
	
	// Check if video buffer is locked
	ASSERTT(Video == NULL, "vidSetPalette attempt while video memory is locked");
	ASSERT(Palette != NULL);
	if (Video) EXIT_PROC(); 										// Quit if locked
	
	// Copy a max of 256 colours to WinPal
	for (i=0; i<256; i++)
	{
		vidWinPal.palPalEntry[i].peRed	 = Palette[i*4+0];
		vidWinPal.palPalEntry[i].peGreen = Palette[i*4+1];
		vidWinPal.palPalEntry[i].peBlue  = Palette[i*4+2];
	}
	
	// Get system palette entries if needed
	if ((isWindowed()) || (SysColors==TRUE))
	{
		// Get system palette entries
		HDC ScreenDC=GetDC(hWndApp);
		GetSystemPaletteEntries(ScreenDC,	0, 10, &vidWinPal.palPalEntry[	0]); // Get colors	 0..  9
		GetSystemPaletteEntries(ScreenDC, 246, 10, &vidWinPal.palPalEntry[246]); // Get colors 246..255
		ReleaseDC(hWndApp, ScreenDC);								// Release screen DC
	}
	
	// Windowed modes must have the first and last 10 colors from the windows palette
	if (isWindowed())
	{
		// Wipe out system palette, this is required for an identity palette
		if (IsIconic(hWndApp))
			vidResetPaletteOnRestore=TRUE;							// Reset palette on window restore
		else
			vidResetPalette();

		// Set appropriate flags in Windows palette
		for (i=0; i<256; i++)										// Srt all flags
			vidWinPal.palPalEntry[i].peFlags=(i<10 || i>245) ? 0 : PC_NOCOLLAPSE;

		// Do something, depending on display mode
		if (VideoHwModeCur.hwModeType==VIDMODE_DIB) 				// Got a DIB?
			DIBSectionSetPalette(); 								// Set palette in DIBSection
		else														// Nothing we know left
			{ ASSERTT(FALSE, "Unknown windowed video mode"); }		// Dunno!
	}
	else
	{
		// We're not windowed, do something depending on display mode
		if (VideoHwModeCur.hwModeType==VIDMODE_DDRAW)				// DirectDraw mode?
			DirectDrawSetPalette(); 								// Set palette in DirectDraw
		else														// Nothing we know
			{ ASSERTT(FALSE, "Unknown fullscreen video mode"); }	// Dunno!
	}
	
	EXIT_PROC();
}

/**{ vidCreatePalette, Video }
@func

The vidCreatePalette function converts a set of 24-bit color values (stored as 32
bit entries) to a native (videobuffer-compatible) 16- or 32-bit palette.

@params
@return
	This function returns TRUE when it could successfully convert the specified amount
	of colors to a native 16 or 32 bit palette. The return value is FALSE if the
	colors could not be converted (most likely because the desired palette is not
	available with the current bit depth). This happens when VideoBPP is not set to
	indicate a highcolor or realcolor mode, so there is no information about the
	position and size of the red, green and blue elements in a hardware pixel.

@portable
@see VideoXPos, VideoXSize, VideoXMask (global variables)
**/
zBOOL vidCreatePalette(
	int 	Type,			/* Type of destination palette required
	Type of destination palette format required. This value can be PALETTE_16 when a
	16-bit palette is required or PALETTE_32 when a 32-bit palette is required.
	
	The PALETTE_32 value can be used when VideoBPP is 16 or 32.
	The PALETTE_16 value can be used when VideoBPP is 16.

	If VideoBPP is 16 and a 32-bit palette is requested, the size of the red, green
	and blue components will all be 8 bits (as would be expected for a 32 bit
	palette). The order in which the components are placed will be in the same
	order as the current (native) 16-bit display mode.
	
	If VideoBPP is 32 and a 32-bit palette is requested, the returned palette will
	be identical to that used by the video buffer.
	
	If VideoBPP is 16 and a 16-bit palette is requested, the returned palette will
	be identical to that used by the video buffer. */

	void	*Dest,			/* Pointer to destination palette (in native format)
	Pointer to destination palette. */

	void	*Source,		/* Pointer to source palette in 32 bit color format
	Pointer to a source (32 bit) palette. Each palette entry is read as 4 zBYTEs,
	1 zBYTE red, 1 zBYTE green, 1 zBYTE blue and one discarded zBYTE. If you reference
	a palette entry as a zDWORD, the format of the zDWORD on the Intel (little endian)
	format is 0x00bbggrr, on Motorola (big endian) the format is 0xrrggbb00.*/

	int 	Colors			/* Amount of colors to convert
	Amount of colors to convert.*/
)
{
	LPWORD	pPal16=(LPWORD)Dest;									  // -> 16 bit palette
	LPDWORD pPal32=(LPDWORD)Dest;									  // -> 32 bit palette
	LPBYTE	pPal=(LPBYTE)Source;											  // -> 8 bit source palette
	zDWORD	nVidPos[3]; 											  // Real video bit positions
	BYTE	RGB32Shift[3]={0,0,0};									  // R, G and B shifter for 32 bit
	int 	i, j;													  // Indices
	
	ENTER_PROC(vidCreatePalette);
	
	// Chech input values
	ASSERT(Dest);													  // Must have a destination pointer
	ASSERT(Source); 												  // Must have a source pointer
	if (Colors==0) RETURN(TRUE);									  // No colors to convert, fine
	
	// Copy video positions
	nVidPos[0]=VideoRPos; nVidPos[1]=VideoGPos; nVidPos[2]=VideoBPos; // Copy video positions
	
	// Check for palette types
	if ((Type==PALETTE_16) && (VideoBPP==16))						  // 16 bit native palette
	{
		// Check for special 565 format
		if ((VideoRGBSize==0x565) && (VideoBPos==0) && (VideoGPos==5))
		{
			// Convert to 565 RGB format (optimized for compiler)
			for (i=0; i<Colors; i++)
			{
				// Create 16 bit palette in 565 RGB format format
				*pPal16++=((pPal[0]<<8) & 0xF800)|((pPal[1]<<3) & 0x07E0)|((pPal[2]>>3) & 0x001F);
				pPal+=4;													// Skip color
			}
		}
		else if ((VideoRGBSize==0x555) && (VideoBPos==0) && (VideoGPos==5))
		{
			// Convert to 555 RGB format (optimized for compiler)
			for (i=0; i<Colors; i++)
			{
				// Create 16 bit palette in 555 RGB format format
				*pPal16++=((pPal[0]<<7) & 0x7C00)|((pPal[1]<<2) & 0x03E0)|((pPal[2]>>3) & 0x001F);
				pPal+=4;													// Skip color
			}
		}
		else
		{
			// Go through colors and convert it (general approach), SLOOOW
			for (i=0; i<Colors; i++)
			{
				// Create 16 bit palette
				*pPal16=(WORD)((pPal[0]<<VideoRPos>>(8-VideoRSize)) & VideoRMask);
				*pPal16|=((pPal[1]<<VideoGPos>>(8-VideoGSize)) & VideoGMask);
				*pPal16|=((pPal[2]<<VideoBPos>>(8-VideoBSize)) & VideoBMask);
				pPal16++;													// Next palette entry
				pPal+=4;													// Skip color
			}
		}
		
		RETURN(TRUE);													// Converted palette
	}
	else if ((Type==PALETTE_32) && (VideoBPP>=16))
	{
		// Check RGB order for 32 bit color when using 15/16 bit color
		if (VideoBPP==16)												// 16 bit?
		{
			// Create shifters when in native 16 bit color mode to get a same color
			// order for a 32 bit palette
			//
			// For 3 components (R,G,B) check their relative positions and create a
			// shifter for 32 bit for it's relative position. Logic is: If there are x
			// colors who have a lower bit position than you, you have to shift x*8
			// bits up to get to "your spot", i is the color who is being investigated,
			// j is the color being compared with (to check which colors have a lower
			// bit position).
			for (i=0; i<3; i++)
				for (j=0; j<3; j++)
					if (nVidPos[j]<nVidPos[i]) RGB32Shift[i]+=8;
		}
		else															  // 24 bit or higher
		{
			for (i=0; i<3; i++) RGB32Shift[i]=(BYTE)nVidPos[i]; 			// Use Hardware values
		}
		
		// Go through colors and convert palette
		for (i=0; i<Colors; i++)
		{
			// Set 32 bit palette
			*pPal32= (pPal[0] << RGB32Shift[0]);						  // Set Red component
			*pPal32|=(pPal[1] << RGB32Shift[1]);						  // Set Green component
			*pPal32|=(pPal[2] << RGB32Shift[2]);						  // Set Blue component
			pPal32++;													  // Next palette entry
			pPal+=4;													  // Skip color
		}
		
		RETURN(TRUE);													// Converted palette
	}
	else RETURN(FALSE); 											  // No known palette!
}

/**{ vidSetFrameReady, Video }
@func

The vidSetFrameReady function is called to notify the system that a frame is ready
and displayed. Subsequent calls to vidGetFPSRate return the amount of times
vidSetFrameReady has been called in the last second.

@params
@return
@remarks
	If you call vidFlip or vidBlit(NULL), vidSetFrameReady will automatically be
	called because both routines show an entirely new screen.

	You should call vidSetFrameReady when your application runs in direct-write
	mode and you use vidGetFPSRate to get the frame rate.

@portable
@see vidGetFPSRate
**/
void vidSetFrameReady()
{
	ENTER_PROC(vidSetFrameRead);
	
	// Register frame time
	vidFrameTime[vidFrames++]=sysGetTime(); 						  // Record this frame time
	if (vidFrames==MAX_FPS_COUNT) vidFrames=0;						  // Loop counter
	
	EXIT_PROC();
}



/**{ vidGetFPSRate, Video }

The vidGetFPSRate function returns the amount of frames per second displayed,
also known as the FPS-rate.

@params
@return
@remarks
	Each time vidSetFrameReady is called, the current tick-count is stored in a
	small ring buffer. vidGetFPSRate scans this ring buffer to see how much frames
	have been blitted within the last second and returns this value. This gives a
	more steady and representable value than just checking the time it took to
	display the current frame and assume all of the frames will take as much time.

@portable
@see vidSetFrameReady
**/
int vidGetFPSRate()
{
	zDWORD	OneSecBack=sysGetTime()-1000;								// Minimum frame time
	LPDWORD t=vidFrameTime; 											// -> Frame times
	
	ENTER_PROC(vidGetFPSRate);
	
	__asm
	{
		mov 	ebx,[OneSecBack]
		mov 	eax,256
		xor 	edx,edx
		mov 	esi,[t]
		lea 	edi,[esi+1024]
TLoop:
		cmp 	[esi],ebx
		sbb 	eax,edx
		cmp 	[esi+4],ebx
		sbb 	eax,edx
		cmp 	[esi+8],ebx
		sbb 	eax,edx
		cmp 	[esi+12],ebx
		sbb 	eax,edx
		cmp 	[esi+16],ebx
		sbb 	eax,edx
		cmp 	[esi+20],ebx
		sbb 	eax,edx
		cmp 	[esi+24],ebx
		sbb 	eax,edx
		cmp 	[esi+28],ebx
		sbb 	eax,edx
		add 	esi,32
		cmp 	esi,edi
		jb		TLoop
		mov 	[OneSecBack],eax
	}
	
	RETURN(OneSecBack); 											  // Scan the FPS list
}

/**{ vidSetMode, Video }
@func

The vidSetMode function sets the current video mode.

@params
@return 
	The return value is TRUE if the call succeeded and FALSE when the call
	failed. This function will fail when the system can't find a way to set
	the specified video mode. Switching to and to fullscreen modes is handled
	automatically in Win32.

@remarks
	If NewMode.AccessMode is set to VAM_SIMPLE, you should set NewMode.VidMemBuffers
	and NewMode.SysMemBuffers to 0. In simple video modes it will always use one
	(system-memory) backbuffer and one video buffer, you are not allowed to change this.

	If NewMode.AccessMode is set to VAM_DIRECT, both NewMode.VidMemBuffers and
	NewMode.SysMemBuffers should be set to the requested values. If there is not
	enough video memory to create NewMode.VidMemBuffers video buffers, vidSetMode will
	return FALSE. The system memory buffers are only created for convenience, you don't
	have to use them.

	vidSetMode will not switch to modes that do not pass the callback specified as the
	fnCheckVMode member of the VIDEO_INFO structure passed to vidSetModeEx, the reason
	being that your callback specifies that your program cannot and will not support
	certain modes so they are hidden entirely.

	If the call succeeds (returns TRUE) the video memory will be cleared. If the call
	fails (returns FALSE) the video memory might be cleared, but it can also leave the
	video memory unchanged.

	Video buffer memory will always be allocated from the system, not from the global
	memory pool that is also used for your program's memory management.

	On Win32 the splash screen is removed and the main window is brought up at your
	first call to vidSetMode. On DOS, the mouse is centered on the first call to
	vidSetMode.

	If vidSetMode successfully sets a new video mode, the VIDMODE structure you pass as
	NewMode will be copied to the global VIDMODE structure VideoModeCur. The hardware
	video mode that vidSetMode picked before setting the video mode will be copied to
	the global VIDMODE structure VideoHwModeCur. If you set a video mode with AccessMode
	set to VAM_SIMPLE, VideoHwModeCur might specify a VAM_DIRECT mode to show that
	it is emulating the video mode.

	If you want to set a new video mode which is almost the same as the current video
	mode (for example, you would only like to change the dimensions of the mode, but
	not windowed/fullscreen mode, bit depth, etc) you can make a copy of the
	VideoModeCur structure and change only the member you want modified and pass the
	new structure on to vidSetMode.

	You can check the members of VideoHwModeCur to check in what display mode you
	currently are, what buffer configuration is chosen in case you are in a simple
	(VideoModeCur.AccessMode is VAM_SIMPLE) video mode, etc. The VideoHwModeCur
	structure will have rgbMasksValid set to TRUE if the video mode is hicolor or
	realcolor.

	If you want to know if you are in a simple or direct video mode you should always
	check VideoModeCur.AccessMode, not VideoHwModeCur.AccessMode, because your simple
	video mode might be emulated through a direct video mode (like DirectDraw).
	Therefore, VideoHwModeCur.AccessMode will be set to VAM_DIRECT.

	Setting a video mode:


// Attempt to set an 8 BPP video mode. We clone VideoModeCur because the
// command-line options "-Windowed" and "-FullScreen" set the hwModeType
// of VideoModeCur to VIDMODE_ANYWINDOWED or VIDMODE_ANYFULLSCREEN. By
// cloning VideoModeCur we will respect these options in our first
// vidSetMode call.
VIDMODE 	NewMode;

// Create video mode structure
memcpy(&NewMode, &VideoModeCur, sizeof(VIDMODE));// Set video mode to defaults
vidMode.AccessMode=VAM_SIMPLE;	// Don't need direct access
vidMode.si.Width=0; // Any width (maximum)
vidMode.si.Height=0;	// Any height (maximum)
vidMode.si.BPP=8;		// Must be 8 BPP
if (!vidSetMode(&vidMode))
{
	// Couldn't set video mode, that is bad
	sysHardExit("Could not set video mode! ");
}

@portable
@see vidSetModeEx
**/  
zBOOL vidSetMode(
	LPVIDMODE NewMode	/* New video mode to set
	A VIDMODE structure describing a video mode, or some of its properties.
	Mostly you will only set the si.Width, si.Height, si.BPP and possible
	hwModeType member of this structure, but none of these modes is required.
	You can, for example, specify only a Width or BPP, or even less: nothing at
	all. vidSetMode uses vidGetModeList to get the best match for the video mode
	you specified. */
)
{
	static zBOOL   SplashGone=FALSE; 								  // Killed splash window?
	SURFACE_INFO  siVidBuffer;										  // Video Buffer surface info
	VIDMODE RealMode;												  // Real (hardware) video mode
	zLONG	i;														  // General counter
	zBOOL	SameHwMode=FALSE;										  // Just resizing?
	
	ENTER_PROC(vidSetMode);
	
	ASSERTT(NewMode!=NULL, "You must specify a video mode for vidSetMode");
	ASSERTT(NewMode!=&VideoModeCur, "VideoModeCur is not a valid argument for vidSetMode");
	ASSERTT(NewMode!=&VideoHwModeCur, "VideoModeCur is not a valid argument for vidSetMode");
	ASSERT_VMODE(NewMode);

	// Block recursion (this shouldn't happen!)
	ASSERTT(!isBusyWith(SETMODE), "vidSetMode is recursing!");
	vidSetBusyWith(SETMODE);										// We're in
	
	// Get the real mode we have to set. If we can't get a real mode, exit here.
	if (vidGetModeList(NewMode, &RealMode, 1)==0)					// Get a mode
	{
		TRACE_DEBUG("VID: vidSetMode %ux%ux%u failed (no modes matched required mode)", NewMode->si.Width, NewMode->si.Height, NewMode->si.BPP); // Show in debug log
		vidSetDoneWith(SETMODE);									// Done!
		RETURN(FALSE);												// Report error
	}
	
	// Show what video mode we're setting
	TRACE_DEBUG("VID: vidSetMode %ux%ux%u (%s)", NewMode->si.Width, NewMode->si.Height, NewMode->si.BPP, vidGetScreenModeName(RealMode.hwModeType));
	
	// If old video is locked, unlock it
	if (Video)
	{
		TRACE_DEBUG("VID: Warning! vidSetMode while video memory is locked");
		vidUnLock(NULL);												// Free!
	}
	
	// Check video mode, set flag for resizing and free all surfaces (soft exit)
	ASSERT_VMODE(&RealMode);
	SameHwMode=(VideoHwModeCur.hwModeType == RealMode.hwModeType);	  // Set resize flag
	
	// Set amount of System and Video Memory buffers
	if (NewMode->AccessMode==VAM_SIMPLE)							  // Simple mode
	{
		// Prepare for simple (1 System (Back-)Buffer, 1 Video (Front-)Buffer)
		RealMode.SysMemBuffers=1;										// One backbuffer
		if (isVModeDirectDraw(&RealMode))								// DirectDraw mode?
			RealMode.VidMemBuffers=2;									// Use pageflipping
		else if (isVModeDispDIB(&RealMode)) 							// DispDIB mode?
			RealMode.VidMemBuffers=0;									// No video buffers in DIB
		else
			ASSERT(FALSE);												// Unknown mode, exit
	}
	else if (NewMode->AccessMode==VAM_DIRECT)
	{
		// Prepare RealMode for user's front and backbuffer settings
		RealMode.VidMemBuffers = NewMode->VidMemBuffers;				// Take user video buffer settings
		RealMode.SysMemBuffers = NewMode->SysMemBuffers;				// Take user system buffer settings
	}
	
	// Kill splash if it's there
//	if (!SplashGone) { winKillSplash(); SplashGone=TRUE; }			  // Kill splash if there
	
	// Accept new screen dimensions (when windows are inited in the various init things,
	// at least VideoHwModeCur and stuff will be valid)
	VideoW			= NewMode->si.Width;							// Accept new Width
	VideoH			= NewMode->si.Height;							// Accept new Height
	VideoBPP		= NewMode->si.BPP;								// Accept new BPP
	VideoBPPShift	= VideoBPP >> 4;								// 8->0, 16->1, 32->2
	memcpy(&VideoModeCur, NewMode, sizeof(VIDMODE));			// Copy source mode
	memcpy(&VideoHwModeCur, &RealMode, sizeof(VIDMODE));		// Copy hardware mode

	// Set new video mode
	ASSERT(isVModeValid(&RealMode));								// Must specify a valid mode
	vidCloseDisplay(SameHwMode);									// Close current display
	switch (RealMode.hwModeType) {									// Set new mode
	case	VIDMODE_DIB:
			DIBSectionInit(&RealMode);								// Create DIBSection
			winResizeMainWindow();									// Set new window size
			sysSetWindowMode(FALSE, TRUE);							// Set window windowed (not fullscreen)
			break;

//	case	VIDMODE_DDRAWWIN:
//			DirectDrawInit(&RealMode, TRUE);						// Set video mode for windowed DirectDraw
//			break;

	case	VIDMODE_DDRAW:
			sysSetWindowMode(TRUE, TRUE);							// Show on first call
			if (!DirectDrawInit(&RealMode, SameHwMode))
			{
				// Couldn't set mode. If we attempted to resize, make
				// sure we close DirectDraw before returning FALSE.
				if (SameHwMode) DirectDrawExit(TRUE);				// Close it
				vidSetDoneWith(SETMODE);							// We're done, ready for next call
				RETURN(FALSE);
			}
			break;

	default: ASSERT(FALSE); break;
	};

	// Set new video RGB masks
	vidSetRGBMasks();												// Set RGB masks

	// Allocate system memory buffers (if it's not a DIB who creates its own)
	if (RealMode.hwModeType != VIDMODE_DIB)
	{
		memcpy(&siVidBuffer, &VideoHwModeCur.si, sizeof(SURFACE_INFO)); // Copy surface info
		siVidBuffer.MemType=VIDMEM_SYSTEM;							// Create system memory buffers
		for (i=0; i<RealMode.SysMemBuffers; i++)
		{
			vidSysBufs[i]=vidCreateSurfaceEx(&siVidBuffer, isVModeDirectDraw(&RealMode)); // Create system mem surface
			if (vidSysBufs[i]==NULL)
			{
				// Can't create back buffers, we should exit
				vidSetDoneWith(SETMODE);							// We're done, ready for next call
				RETURN(FALSE);										// Can't set mode! No memory!
			}
		}
	}

	// In debug mode we track the video memory, it has been lost now
	SetForegroundWindowEx(hWndApp);									// Move to foreground
	vidSetDoneWith(SETMODE);										// We're done, ready for next call
	vidSetModeCalled=TRUE;											// Called once


	TRACE_DEBUG("VID: vidSetMode done");
	RETURN(TRUE);													// No problems
}

//
// Set global parameters (such as RGB masks, video Width and Height, etc)
//
static void INLINE vidSetRGBMasks()
{
	zDWORD i, j; 													  // Counters
	ENTER_PROC(vidSetRGBMasks);

	// Continue, depending if we are in a 256 color, or a HighColor/RealColor mode
	if (VideoBPP==8)
	{
		// Wipe out all color-mask related variables
		VideoRMask	  = 0;												// Reset Red Mask
		VideoGMask	  = 0;												// Reset Green Mask
		VideoBMask	  = 0;												// Reset Blue Mask
		VideoRPos	  = 0;												// Reset Red Position
		VideoRSize	  = 0;												// Reset Red Size
		VideoGPos	  = 0;												// Reset Green Position
		VideoGSize	  = 0;												// Reset Green Size
		VideoBPos	  = 0;												// Reset Blue Position
		VideoBSize	  = 0;												// Reset Blue Size
		VideoRGBSize  = 0;												// Reset size mask
	}
	else if (VideoBPP>8)
	{
		// Copy masks to global variables
		VideoRMask	  = VideoHwModeCur.si.rgbRMask; 					// Copy Red Mask
		VideoGMask	  = VideoHwModeCur.si.rgbGMask; 					// Copy Green Mask
		VideoBMask	  = VideoHwModeCur.si.rgbBMask; 					// Copy Blue Mask
		
		// Check bit positions and sizes
		for (i=0, j=1; i<32; i++, j<<=1) if ((VideoRMask & j)==j) { VideoRPos=i; break; }
		for (		 ; i<32; i++, j<<=1) if ((VideoRMask & j)==0) { VideoRSize=i-VideoRPos; break; }
		for (i=0, j=1; i<32; i++, j<<=1) if ((VideoGMask & j)==j) { VideoGPos=i; break; }
		for (		 ; i<32; i++, j<<=1) if ((VideoGMask & j)==0) { VideoGSize=i-VideoGPos; break; }
		for (i=0, j=1; i<32; i++, j<<=1) if ((VideoBMask & j)==j) { VideoBPos=i; break; }
		for (		 ; i<32; i++, j<<=1) if ((VideoBMask & j)==0) { VideoBSize=i-VideoBPos; break; }
		
		// Set VideoRGBSize mask (in form 0x565)
		VideoRGBSize  = (VideoRSize<<8)+(VideoGSize<<4)+(VideoBSize);	// Set size mask
	}
	else ASSERT(FALSE);

	EXIT_PROC();
}

/**{ vidWaitVSYNC, Video }
@func

vidWaitVSYNC waits for the vertical blank. Synchronizing with the vertical blank (therefore also known as the vertical sync) will reduce tearing (also called shearing) on the display. 

@params
@return
@remarks
	You should wait for the vertical blank if you are blitting a lot of graphics, 
	specifically before copying a system memory buffer to the active video surface. 
	If you use page-flipping (i.e. you are always blitting to invisible pages and
	using vidFlip to show all of the changes to an invisible buffer at once) you
	will not need vidWaitVSYNC. Page-flipping always occurs at the start of each
	frame, when you flip the page while the electron beam is halfway past the
	monitor, the video board will continue to send the active page to the monitor,
	it will not switch to the new page halfway the monitor.

@portable
	This function is portable, but when there is no way of checking (and or
	waiting) for the vertical blank, this function will return immediately.

@see vidBlit vidFlip
**/
void vidWaitVSYNC()
{
  ENTER_PROC(vidWaitVSYNC);

  if (VideoHwModeCur.hwModeType!=VIDMODE_DDRAW) EXIT_PROC();		// Only possible on DirectDraw
  DirectDrawWaitVSYNC();											// Wait for VSYNC

  EXIT_PROC();
}

/**{ vidFlip, Video }
@func

vidFlip flips to the next display surface. This causes a different video buffer
to become visible.

@params
@return
	The return value is TRUE if the page has been flipped. The return value
	is FALSE if page flipping is not supported.

@remarks
	You can get the SURFACE associated with the next surface (which is not currently
	visible) with @!vidGetStdSurface(VIDMEM_VIDEO, 1). You can lock that surface with
	@@vidLock, modify its contents, unlock it with @@vidUnLock and then flip to the
	surface with vidFlip.

	If there is only one display page and you are in VAM_DIRECT mode, calling
	vidFlip will flip to page 0, but the call is redundant (it will not do anything).

@portable
@see vidBlit vidSetMode vidGetStdSurface
**/
zBOOL vidFlip()
{
	zBOOL	res;

	ENTER_PROC(vidFlip);

//	ASSERTT(VideoModeCur.AccessMode==VAM_DIRECT, "You can only call vidFlip in a direct write mode");
//	if (VideoModeCur.VidMemBuffers==1) RETURN(TRUE);				// Done already :)

	// Flip to surface (by now, all requirements should've only left DirectDraw modes,
	// which is the only way to flip in Windows).
	ASSERT(isDirectDraw()); 										// Valid DDraw mode
	vidSetFrameReady(); 											// "Mount" this frame
	res=DirectDrawFlip();											// Flip

	RETURN(res);
}

/**{ vidGetStdSurface, Video }
@func

vidGetStdSurface returns a pointer to the SURFACE structure that represents
a system or video memory surface.

@params
@return
	The return value is a pointer to the SURFACE structure for the
	specified video buffer. If the specified surface is not present
	(BufNum is out of range), the returned value will be NULL.

@remarks
	In simple video modes you can request a video surface (MemType is
	VIDMEM_VIDEO). Only video buffer 0 will be present. You can use this
	surface as a destination for vidBlit, but you can not lock the surface.
	You can only lock the video surfaces in direct video modes. 

	Video buffer 0 is always the current (visible) video buffer. If you
	write to video buffer 0, the changes will be immediate (you are writing
	directly to video memory). Video buffer 1 (if present) is always the
	next video page (the one that will be visible after vidFlip). Video
	buffer 2 is the page that will be visible with 2 vidFlip calls. After
	each vidFlip the pages are cycled. If you retrieve a pointer to a
	video buffer with vidGetStdSurface, you should consider this pointer
	invalid after the next vidFlip.

@portable

@see vidSetMode vidCreateSurface vidFreeSurface
**/
SURFACE *vidGetStdSurface(
	int 	MemType,		/* Memory type of buffer to get
	Memory type flag. Specify VIDMEM_SYSTEM if you would like a pointer
	to one of the system memory buffers. Specify VIDMEM_VIDEO to get a
	pointer to one of the video memory buffers. */

	int 	BufNum			/* Buffer number to retrieve
	Buffer number to retrieve. This must always be a number in the range 0
	up to (but not including) 3. Depending on MemType this value must also
	be less than VideoHwModeCur.VidMemBuffers (if MemType is VIDMEM_VIDEO)
	or VideoHwModeCur.SysMemBuffers (if MemType is VIDMEM_SYSTEM). */
)
{
	ENTER_PROC(vidGetStdSurface);
	
	ASSERTT((MemType==VIDMEM_SYSTEM) || (MemType==VIDMEM_VIDEO), "vidGetStdSurface must have VIDMEM_SYSTEM or VIDMEM_VIDEO as MemType parameter");
	ASSERTT(BufNum<3, "Buffers >=3 do not exist, only buffers 0, 1 and 2 are supported");
	
	if (MemType==VIDMEM_SYSTEM) 									  // System memory surface?
	{
		if (BufNum>=VideoHwModeCur.SysMemBuffers) RETURN(NULL); 		// Out of range
		RETURN(vidSysBufs[BufNum])										// Return -> Sysmem Surface
	}
	else if (MemType==VIDMEM_VIDEO) 								  // Video memory surface?
	{
		if ((BufNum==0) && (VideoHwModeCur.hwModeType==VIDMODE_DIB)) RETURN(vidVidBufs[0]);
		if (BufNum>=VideoHwModeCur.VidMemBuffers) RETURN(NULL); 		// Out of range
		RETURN(vidVidBufs[BufNum])										// Return -> Video Surface
	}
	else
		RETURN(NULL);
}

//
// Complete a surface description. Fill in missing values, etc. This is used when a
// user passes a surface it wants and the system needs to find out various optional
// members of the surface description.
//
static void FASTCALL vidCompleteSurfaceInfo(LPSURFACE_INFO Dest, LPSURFACE_INFO Source)
{
	zBYTE  smType;													// Surface memory type
	
	ENTER_PROC(vidCompleteSurfaceInfo);
	
	// Check integrity of SURFACE_INFO structure, so we can memcpy the pixel format
	ASSERTT(VID_PFSIZE==4*4, "Source was compiled with 4-zBYTE packing assumed, caution");
	ASSERT(offsetof(SURFACE_INFO, BPP)			 < offsetof(SURFACE_INFO, rgbMasksValid));
	ASSERT(offsetof(SURFACE_INFO, rgbMasksValid) < offsetof(SURFACE_INFO, rgbRMask));
	ASSERT(offsetof(SURFACE_INFO, rgbRMask) 	 < offsetof(SURFACE_INFO, rgbGMask));
	ASSERT(offsetof(SURFACE_INFO, rgbGMask) 	 < offsetof(SURFACE_INFO, rgbBMask));
	
	// Check user arguments
	ASSERT(Dest);
	ASSERT(Source);
	
	// Source must be a good surface
	ASSERT_SURFACEINFO(Source);
	ASSERT(Source->Width>0);
	ASSERT(Source->Height>0);
	
	// User must not mess with the RGB Masks.
	//	When BPP is 0,	user wants a screen-compatible surface, rgbMasksValid must be FALSE
	//	When BPP is 8,	user wants an 8-bit surface, rgbMasksValid must be FALSE
	//	When BPP is >8, user wants a highcolor surface, rgbMasksValid must be TRUE
	DEBUG_ONLY(if (Source->BPP==0) ASSERTT(Source->rgbMasksValid==FALSE, "Cannot specify RGB masks when creating a screen-compatible surface"));
	DEBUG_ONLY(if (Source->BPP==8) ASSERTT(Source->rgbMasksValid==FALSE, "Cannot specify RGB masks for an 8-bit surface"));
	DEBUG_ONLY(if (Source->BPP>8)  ASSERTT(Source->rgbMasksValid==TRUE,  "You must specify the RGB Masks for a HiColor surface"));
	DEBUG_ONLY(if (Source->rgbMasksValid) ASSERTT(Source->rgbRMask | Source->rgbGMask | Source->rgbBMask, "You must specify RGB masks if you set rgbMasksValid"));

	// Copy dimensions and memory type
	smType=Source->MemType; 										// Source memory type
	Dest->MemType = (smType==VIDMEM_ANY) ? VIDMEM_SYSTEM : smType;	// Set memory type
	Dest->Width=Source->Width;										// Set width
	Dest->Height=Source->Height;									// Set height

	// Either copy current hardware pixel format (if BPP is 0), or use the one provided by the user
	if (Source->BPP==0) 											// No bit depth set?
		memcpy(&Dest->BPP, &VideoHwModeCur.si.BPP, VID_PFSIZE); // Copy default pixel format
	else
		memcpy(&Dest->BPP, &Source->BPP, VID_PFSIZE); 		// Copy user pixel format

	// After-check, destination surface must meet our criteria
	ASSERT(Dest->BPP!=0);
	DEBUG_ONLY(if (Dest->BPP==8) ASSERT(Dest->rgbMasksValid==FALSE)); //  8 bit = No pixel format
	DEBUG_ONLY(if (Dest->BPP>8)  ASSERT(Dest->rgbMasksValid==TRUE));  // >8 bit = Required pixel format
	DEBUG_ONLY(if (Dest->BPP>8)  ASSERT(Dest->rgbRMask | Dest->rgbGMask | Dest->rgbBMask)); // >8 bit = RGB Masks present
	
	EXIT_PROC();
}

/**{ vidLock, Video }
@func

The vidLock function locks a video surface. When the surface is locked, its
contents (the surface memory) can be accessed. The Ptr and Pitch members of
the SURFACE structure will be valid. If Surf is NULL, the default backbuffer
will be locked and the global variables Video and VideoPitch will be valid.

@params
@return
	The return value is TRUE if the surface is locked. The SURFACE structure
	will have a valid Ptr and Pitch that can be used to modify the surface data.

	The return value is FALSE if the surface cannot be locked. The SURFACE
	structure's Ptr and Pitch values will still NULL and 0, respectively.

@remarks
	If a surface is already locked, the call to vidLock will be ignored.
	
	When a surface is locked a system-wide Win16 Lock is held on Win32 with
	all DirectX versions prior to 5. This causes all other tasks in the computer
	to stop, multi-tasking is disabled. If you lock your surfaces too long, the
	sound might stop, the network will not work, etc. Locked surfaces should be
	unlocked as soon as possible.

	If you have set a video mode with AccessMode set to VAM_SIMPLE and pass
	NULL as Surf, the video memory backbuffer (create in vidSetMode) will be
	locked. The variables Video and VideoPitch will be a pointer to the
	backbuffer and it's pitch. You should call vidUnLock(NULL) to unlock the
	video memory and vidBlit(NULL) to blit all of it.

	Exceptions that occur when the video memory is locked (and would normally
	cause your computer to crash) are captured.

@portable
@see vidUnLock vidCreateSurface vidGetStdSurface vidBlit
**/
zBOOL vidLock(
	LPSURFACE Surf			/* Surface to lock
	Surface to be locked. This parameter can be NULL in simple video modes;
	the default backbuffer will then be locked. */
)
{
	ENTER_PROC(vidLock);
	
	// Check for different modes, either Surf!=NULL for real surface, or NULL for default surface
	if (Surf==NULL)
	{
		// Locking (NULL), the default surface, only works in simple modes
		ASSERTT(VideoModeCur.AccessMode==VAM_SIMPLE, "You can only use vidLock(NULL) in VAM_SIMPLE modes");
		ASSERT(vidSysBufs[0]);											// Must have a backbuffer
		
		if (Video)
		{
			TRACE_DEBUG("VID: vidLock(NULL) failed, video memory already locked");
			RETURN(FALSE);												// Already locked? no change
		}
		
		// Lock the first system memory buffer
		vidLock(vidSysBufs[0]); 										// Lock backbuffer
		Video=vidSysBufs[0]->Ptr;										// -> BackBuffer
		VideoPitch=vidSysBufs[0]->Pitch;								// Backbuffer pitch
	}
	else
	{
		if (Surf->Ptr) RETURN(FALSE);									// Already locked
		
		// Should not be locked, so Ptr should be NULL and Pitch hould be 0
		ASSERT(Surf->Ptr==NULL);
		ASSERT(Surf->Pitch==0);
		
		// Check lock by DirectDraw, or just pointer copy for dumb surfaces
		if (Surf->APISpecific[API_MODE]==VIDMODE_DDRAW)
		{
			if (DirectDrawLockSurface(Surf)==FALSE) RETURN(FALSE);		  // Lock surface
			
			// Lock succeeded, so Ptr and Pitch must be valid
			ASSERT(Surf->Ptr != NULL);
			ASSERT(Surf->Pitch != 0);
		}
		else
		{
			// Dumb memory surface
			Surf->Ptr=(LPBYTE)Surf->APISpecific[API_PTR];				  // Set pointer
			Surf->Pitch=Surf->APISpecific[API_PITCH];					  // Set pitch
			
			// Lock succeeded, so Ptr and Pitch must be valid
			ASSERT(Surf->Ptr != NULL);
			ASSERT(Surf->Pitch != 0);
		}
	}
	
	RETURN(TRUE);													  // Locked!
}

/**{ vidUnLock, Video }
@func

The vidUnLock function will unlock a video surface. The exclusive access to the
surface is released and the SURFACE structure's Ptr and Pitch members will be
reset to NULL and 0 respectively. If Surf is NULL, the default backbuffer will
be unlocked and the global variables Video and VideoPitch will be reset.

@params
@return
	The return value is TRUE if the surface was unlocked successfully. The return
	value is FALSE if the surface could not be unlocked.

@remarks
	If you call vidUnLock when the video memory was not locked, this function
	will have no effect.

	If the locking of Surf caused a Win16 Lock to be held, this lock is removed
	when that surface is unlocked with vidUnLock. When in a DIB mode, no Win16
	Lock is held and multitasking will occur as usual.

	You must unlock your video memory before blitting it. This is asserted in
	the vidBlit function.

@portable
@see vidLock vidCreateSurface vidGetStdSurface vidBlit
**/
zBOOL vidUnLock(
	LPSURFACE Surf			/* Surface to unlock
	Surface to be unlocked. This parameter can be NULL in simple video modes;
	the default backbuffer will then be unlocked. */
)
{
  ENTER_PROC(vidUnLock);

  // Check for unlocking (NULL), the default mode, or any surface
  if (Surf==NULL)
  {
	// Lock the entire screen and set the Video and VideoPitch variables
	ASSERTT(VideoModeCur.AccessMode==VAM_SIMPLE, "You can only use vidUnLock(NULL) in VAM_SIMPLE modes");

	if (Video==NULL) RETURN(FALSE); 								// Video already locked, quit
	
	// UnLock backbuffer and reset global variables
	vidUnLock(vidSysBufs[0]);										// Lock backbuffer
	Video=NULL; 													// No video pointer
	VideoPitch=0;													// No pitch
  }
  else
  {
	// Unlock surface, fill in its Ptr and Pitch members
	if (Surf->Ptr==NULL) RETURN(FALSE); 							// Already unlocked

	// Remove DirectDraw lock if it's locked
	if (Surf->APISpecific[API_MODE]==VIDMODE_DDRAW) DirectDrawUnLockSurface(Surf); // Remove DDLock
	
	// The surface is unlocked, remove pitch and pointer info
	Surf->Ptr=NULL; 												// Reset pointer
	Surf->Pitch=0;													// Set pitch
  }

  RETURN(TRUE);
}

//
// Add a surface to the linked list of surfaces
//
// The linked list is ordered so that the surfaces that are created last are at the
// end of the list, vidLL_Last always points to the last entry, or is NULL when the list
// is empty. We can delete surfaces from any position because the list is double-linked.
// When all surfaces need to be deleted, we start at vidLL_Last and delete all surfaces,
// last-first, a LIFO process.
//
static INLINE void vidLL_AddSurface(LPSURFACE Surface)
{
	ENTER_PROC(vidLL_AddSurface);

	ASSERT(Surface);
	ASSERT(Surface->pNext == NULL);
	ASSERT(Surface->pPrev == NULL);

	// If this is the first surface to be added, set the "Last" pointer to this surface
	if (!vidLL_Last) { vidLL_Last=Surface; EXIT_PROC(); }			  // Set root surface

	// There is a root, link this one in one position behind the root
	vidLL_Last->pNext=Surface;										  // Append at end
	Surface->pPrev=vidLL_Last;										  // Our link back to them
	vidLL_Last=Surface; 											  // This is the last surface

	EXIT_PROC();
}

//
// Remove a surface from the linked list of surfaces
//
static void INLINE vidLL_RemoveSurface(LPSURFACE Surface)
{
  ENTER_PROC(vidLL_RemoveSurface);
  
  ASSERT(Surface);
  
  // If this surface is the last, adjust vidLL_Last
  if (Surface==vidLL_Last)
  {
	// Remove last entry from list by adjusting vidLL_Last and deleting the prev. item's pNext
	vidLL_Last=(SURFACE*)Surface->pPrev;										// Decrease last one
	if (vidLL_Last) vidLL_Last->pNext=NULL; 						// Last doesn't have "Next"
  }
  else
  {
	// Remove entry
	ASSERT(Surface->pNext); 										// Only last entry has pNext=NULL
	((LPSURFACE)Surface->pNext)->pPrev = Surface->pPrev;			// Next -> Previous
	if (Surface->pPrev) 											// First entry has no pPrev
	  ((LPSURFACE)Surface->pPrev)->pNext = Surface->pNext;			// Previous -> Next
  }
  
  EXIT_PROC();
}

/**{ vidCreateSurface, Video }
@func
  
The vidCreateSurface function creates a new surface in video or in
system memory. A surface is used as a source or target of graphics
(blitting) operations.

@params
@return
	The return value is a pointer to a new SURFACE structure. If the surface
	could not be created, the returned value is NULL.

@remarks
	You can modify the newly created surface's contents by using the various
	blitting calls or vidLock and modifying the pixel data directly.

	System memory surfaces are not allocated from the global memory pool (the
	fixed memory pool that is used by memAlloc, etc.). Surface memory will be
	allocated from system memory or video memory; if there is not enough memory of 
	either type left to satisfy the request, the vidCreateSurface will return NULL.

	DOS32 uses a video memory manager to allow video memory surfaces. The
	primary display buffer (video memory buffers) will be located at the
	start of the video memory; the rest of the buffers created by the user
	with vidCreateSurface will be located beyond this memory.

	On DOS32 in Mode 13h there are 65536 zBYTEs of accessible video memory, of
	which 64000 is taken by a 320x200 image. The 1536 zBYTEs beyond the video
	page are available for allocation. In VBE 2.0 modes all of the video
	memory will be managed and is available for allocation.

	When there is no access to the video memory (in DIB mode), any
	vidCreateSurface with VIDMEM_VIDEO will fail. You can always create
	VIDMEM_SYSTEM surfaces (surfaces in system memory).

	All video surfaces are lost in vidSetMode. A linked list of video
	surfaces is kept and annihilated when vidSetMode switches to a
	different video mode. If you attempt to use a surface after it has
	been lost in a vidSetMode call, you might expect warnings in the
	log file of the debug build of your program.

@portable
@see vidGetStdSurface vidFreeSurface SURFACE SURFACE_INFO
**/
LPSURFACE vidCreateSurface(
	LPSURFACE_INFO SurfDesc /* Description of the surface to create
	Description of the surface to create. You must fill in at least the
	Width and Height members of this structure.

	If BPP is set to 0, the surface will be created with a pixel format
	(bit depth and RGB masks) compatible with the current display mode.

	If MemType is set to VIDMEM_ANY the surface will always be created
	in system memory. If MemType is set to VIDMEM_VIDEO and there is no
	more free video memory, the call will fail (the return value is NULL). */
)
{
	LPSURFACE res;
	ENTER_PROC(vidCreateSurface);
	res=vidCreateSurfaceEx(SurfDesc, isDirectDraw());
	RETURN(res);
}
LPSURFACE FASTCALL vidCreateSurfaceEx(LPSURFACE_INFO SurfDesc, zBOOL DirectDraw)
{
	SURFACE_INFO  hwSurf;											// Completed surface info
	LPSURFACE nSurface=NULL;										// New surface
	
	ENTER_PROC(vidCreateSurfaceEx);
	
	// Sanity check
	if ((SurfDesc->Width==0) || (SurfDesc->Height==0)) RETURN(NULL);// Must have dimensions
	
	// Convert SurfDesc to a complete interpretable SURFACE_INFO
	vidCompleteSurfaceInfo(&hwSurf, SurfDesc);						// Get hardware surface
	
	// Check for DirectDraw (the only way to real video surfaces)
	if (DirectDraw)
	{
		// We're in DirectDraw, create IDirectDrawSurface objects
		nSurface=(LPSURFACE)sysAlloc(sizeof(SURFACE));				// Allocate memory for surface
		memcpy(&nSurface->si, &hwSurf, sizeof(SURFACE_INFO)); // Copy surface info
		if (!DirectDrawCreateSurface(nSurface, 0)) RETURN(NULL);	// Create a DirectDraw surface
	}
	else
	{
		zDWORD	SurfSize;											// Size of surface
		
		// We're not in DirectDraw, deny Video memory surfaces, create only system memory stuff
		ASSERTT(hwSurf.MemType != VIDMEM_VIDEO, "Can't create Video memory surfaces");
		ASSERT(hwSurf.MemType == VIDMEM_SYSTEM);					// Only option
		
		// Only create system memory surfaces
		if (hwSurf.MemType != VIDMEM_SYSTEM) RETURN(NULL);			// Can't do! Not in DirectDraw!
		
		// Attempt to create surface in main memory
		SurfSize=hwSurf.Width*hwSurf.Height*hwSurf.BPP/8;			// Get surface size
		nSurface=(LPSURFACE)sysAlloc(sizeof(SURFACE)+SurfSize+32);	// Allocate memory for surface
		memcpy(&nSurface->si, &hwSurf, sizeof(SURFACE_INFO)); // Copy surface info
		nSurface->APISpecific[API_PTR]=ALIGN32((zDWORD)(nSurface+1));// -> Surface
		nSurface->APISpecific[API_PITCH]=hwSurf.Width*hwSurf.BPP/8; // Set pitch
		nSurface->APISpecific[API_MODE]=VideoHwModeCur.hwModeType;	// Set "creator"
	}
	
	// Copy SURFACE_INFO from the one vidCompleteSurfaceInfo() created and
	// fill in other fields (Pitch and Ptr)
	nSurface->Ptr=NULL; 											// No locked pointer
	nSurface->Pitch=0;												// No active Pitch
	vidLL_AddSurface(nSurface); 									// Add surface to linked list
	
	RETURN(nSurface);
}

/**{ vidFreeSurface, Video }
@func

The vidFreeSurface function frees a surface. The surface can be located
in system or video memory.

@params
@return
	The return value is TRUE if the surface has been freed. The return
	value is FALSE if the surface could not be freed.

@remarks
	All memory associated with the surface will be freed.
	
	You are only allowed to free surfaces you created with vidCreateSurface.
	You should not free surfaces created.

@portable
@see vidGetStdSurface vidCreateSurface SURFACE
**/
zBOOL vidFreeSurface(
	LPSURFACE	Surf		/* Surface to be freed
	Pointer to a SURFACE structure previously obtained with vidCreateSurface. */
)
{
	ENTER_PROC(vidFreeSurface);

	ASSERT(Surf);
	ASSERT_SURFACEINFO(&Surf->si);
	ASSERTT(Surf->APISpecific[API_MODE], "This provided surface handle is not valid");

	if (Surf==NULL) RETURN(FALSE);									// No locked or NULL surfaces!
	if (Surf->APISpecific[API_MODE]==0) RETURN(FALSE);				// Can't free twice

	// Unlock surface if it's locked
	if (Surf->Ptr)
	{
		TRACE_DEBUG("VID: Warning! Had to unlock surface in vidFreeSurface");
		vidUnLock(Surf);											// Unlock surface
	}

	// Free surface
	switch(Surf->APISpecific[API_MODE]) {
	case VIDMODE_DDRAW:   DirectDrawFreeSurface(Surf); break;
	case VIDMODE_DIB:	  break;
	}

	// Free old backup copy if there is one
	if (Surf->APISpecific[API_BACKUP])								// Old backup?
	sysFree((LPVOID)Surf->APISpecific[API_BACKUP]); 				// Free!

	// Set video mode (APISpecific[API_MODE] to 0 to indicate that the surface is freed)
	vidLL_RemoveSurface(Surf);										// Remove surface from linked list
	memZero(Surf, sizeof(SURFACE)); 								// FREED!
	sysFree((LPVOID)Surf);											// Free structure

	RETURN(TRUE);
}

//
// Set source color key for surface
//
zBOOL vidSetColorKey(LPSURFACE Surface, zDWORD Color)
{
	zBOOL	res=FALSE;												// Result code
	ENTER_PROC(vidSetColorKey);

	// Check for color key on normal or DirectDraw surface
	if (Surface->APISpecific[API_PTR]==0xDEADBEAF) 
	{
		ASSERTT(FALSE, "Color key for software surfaces not yet implemented");
	}
	else
	{
		DDCOLORKEY	cKey={ Color, Color };							// Color key to set
		res=ddCheck(IDirectDrawSurface2_SetColorKey(GetDDSurf(Surface), DDCKEY_SRCBLT, &cKey));
	}

	RETURN(res);
}

//
// Paint contents of window
//
void FASTCALL vidPaintWindow(HWND hWnd)
{
  BLIT_CMD dibBlit={ vidVidBufs[0], NULL, vidSysBufs[0], NULL, BLIT_COPY, 0 };
  PAINTSTRUCT ps;													// Structure for painting
  RECT	  cRect;													// Client are of window rect
  HDC	  wDC;														// Device context for paint

  ENTER_PROC(vidPaintWindow);

  // Get client area
  if (GetClientRect(hWnd, &cRect)==FALSE) EXIT_PROC();				// Check for client rectangle

  // Start paint thing and draw contents
  wDC=BeginPaint(hWnd, &ps);										// Begin painting
  switch (VideoHwModeCur.hwModeType)
  {
	case VIDMODE_DIB:		DIBSection_BLIT_COPY(&dibBlit); break;	// Bit with DIB
	case VIDMODE_DDRAWWIN:	/*// We need screen coordinates of this thing, get them
							  FrameRect(wDC, &WindowRect, GetStockObject(BLACK_BRUSH));
							  GetDCOrgEx(wDC, &WinOrg); 			// Position of window
							  OffsetRect(&WindowRect, WinOrg.x, WinOrg.y);
							  WindowRect.right--; WindowRect.bottom--; // Border size of 1
							  DirectDrawUpdateWindow(&WindowRect);	// Blit with DirectDraw
							*/
	default: FillRect(wDC, &cRect, (HBRUSH)GetStockObject(BLACK_BRUSH)); // Fill with black stuff
  };

  // Done!
  EndPaint(hWnd, &ps);												// Done with paint
  EXIT_PROC();
}

/*
  HDC	  WinDC;													// Window client device context
  RECT	  WinRect;													// Window size
  POINT   WinOrg;													// Window origin

  // Do something for windowed display
  switch (VideoHwModeCur.hwModeType)
  {
	case VIDMODE_DIB:		WinDC=GetDC(hWndApp);					// Window client device context
							DIBSectionBlitWindow(WinDC, vidVideoPage);	// Blit to window
							ReleaseDC(hWndApp, WinDC);				// Release DC
							break;									// Did Blit
	case VIDMODE_DDRAWWIN:	WinDC=GetDC(hWndApp);					// Window client device context
							if (WinDC==NULL) break; 				// Don't draw (no device context)
							if (GetDCOrgEx(WinDC, &WinOrg)==FALSE) break;		// Position of window
							if (GetClientRect(hWndApp, &WinRect)==FALSE) break; // Get size of client area
							if ((WinRect.right==0) && (WinRect.bottom==0)) break;
							OffsetRect(&WinRect, WinOrg.x, WinOrg.y);	// Offset to client area
							WinRect.right--; WinRect.bottom--;		// 1 Pixel border
							DirectDrawUpdateWindow(&WinRect);		// Blit with DirectDraw
							ReleaseDC(hWndApp, WinDC);				// Release DC
							break;
  }
*/

//
// Close fullscreen display modes when set
//
void FASTCALL vidCloseDisplay(zBOOL Resizing)
{
	zDWORD	CurHwMode, i, y;										// Current hardware mode
	CHAR	LogString[128]="VID: "; 								  // String to log
	ENTER_PROC(vidCloseDisplay);
	
	// Set string stuff
	strcat(LogString, Resizing ? "Resizing display " : "Closing display ");
	
	// Check if we're not recursing, or if everything's already closed
	if ((isBusyWith(DISPLAYCLOSE)) || (vidVidBufs[0]==NULL)) EXIT_PROC(); // Done!
	
	// Record current hardware mode now by looking at who created the primary surfaces
	CurHwMode=vidVidBufs[0]->APISpecific[API_MODE]; 				  // Get hardware mode
	
	// Free video buffers (in Video and System Memory)
	for (i=0; i<3; i++)
	{ 
		if (vidSysBufs[i]) vidFreeSurface(vidSysBufs[i]);			// Free surface
		if ((vidVidBufs[i]) && (CurHwMode==VIDMODE_DDRAW) && (vidLock(vidVidBufs[i])))
		{
			// Wipe out all video buffers (fill with 0's) to avoid ugly garbage / pallet flicker
			zDWORD	dwBPL=vidVidBufs[0]->si.Width*vidVidBufs[0]->si.BPP/8;	// Bytes/Line
			zDWORD	Pitch=vidVidBufs[i]->Pitch; 					// Pitch of surface
			for (y=0; y<vidVidBufs[0]->si.Height; y++)				// Do all lines
				memZero(vidVidBufs[i]->Ptr+(y*Pitch), dwBPL);		// Wipe out!
			vidUnLock(vidVidBufs[i]);								// Done!
		}
	}
	if (vidVidBufs[0]) vidFreeSurface(vidVidBufs[0]);				// Free primary video surface
	for (i=0; i<3; i++) vidSysBufs[i]=vidVidBufs[i]=NULL;			// Zero out pointers


	// Check what needs to be closed and pad to log string
	vidSetBusyWith(DISPLAYCLOSE);
	switch (CurHwMode) {
	case VIDMODE_DDRAW: strcat(LogString, "(DirectDraw)");	TRACE(LogString);	DirectDrawExit(Resizing);	break;
	case VIDMODE_DIB:	strcat(LogString, "(DIBSection)");	TRACE(LogString);	DIBSectionExit();			break;
	}
	ASSERTT(vidVidBufs[0]==0, "Video buffers must be NULL after display has closed");
	vidSetDoneWith(DISPLAYCLOSE);									  // We closed it and will be leaving the function

	EXIT_PROC();
}

//
// Toggle between fullscreen mode and windowed mdoe. For applications that can only
// run in fullscreen mode, or direct access video mode, this minimizes the application
// and waits for it to be restored
//
void FASTCALL vidToggleFullScreenMode()
{
	ENTER_PROC(vidToggleFullScreenMode);

	// Check if the user wants to handle Alt+Enter
	if (vidAltEnterHandler) { vidAltEnterHandler(0); EXIT_PROC(); } // User does the job

	if ((VideoModeCur.AccessMode==VAM_DIRECT) || (vidOnlyFullScreen))
		vidMinimize(TRUE);											// Go AWAY!
	else if (VideoModeCur.AccessMode==VAM_SIMPLE)
	{
		VIDMODE NewMode;											// New video mode
		
		// Prepare standard (clone mode and remove ALT+ENTER flag)
		memcpy(&NewMode, &VideoModeCur, sizeof(VIDMODE)); 	// Clone current mode
		
		// Check if we want to switch to windowed or fullscreen
		if (isWindowed())											// Currently windowed?
			NewMode.hwModeType=VIDMODE_ANYFULLSCREEN;				// Window -> Fullscreen
		else if (isFullScreen())									// Currently fullscreen?
			NewMode.hwModeType=VIDMODE_ANYWINDOWED; 				// Fullscreen -> Window
		
		// Set mode
		TRACE_DEBUG("VID: Switching screen mode");					// Show what we're doing
		SetVMode(&NewMode);									// Set new mode
	}
	else ASSERT(FALSE); 											// Video mode must be VAM_DIRECT or VAM_SIMPLE

	EXIT_PROC();
}

//
// Enter idle mode for screensave/power-down
//
void vidIdleEnter()
{
	ENTER_PROC(vidIdleEnter);

	// Check sound (stop it if it's running)
	winMinimized=TRUE;												// Minimized!

	vidSetBusyWith(MINIMIZING); 									// We're busy, don't interrupt
	if (isDirectDraw()) DirectDrawSave(TRUE);						// Return window to normal
	vidSetDoneWith(MINIMIZING); 									// Done!

	EXIT_PROC();
}

//
// Wait for the computer to unblank its screen (when the power of the monitor is down)
//
void FASTCALL vidWaitScreenUnblank()
{
	zDWORD	tStart; 												// Start time
	ENTER_PROC(vidIdleWait);

	tStart=sysGetTime();											// Get start time

	// Check sound (stop it if it's running)
	winMinimized=TRUE;												// Minimized!

	// Wait until we reactivate
	TRACE_DEBUG("Waiting for app to be restored by WM_PAINT");
	winWaitMessage(WM_PAINT, 0, 0, 0, 0, FALSE);					// Wait for WM_PAINT message
	TRACE_DEBUG("VID: Restoring from idle mode");

	winMinimized=FALSE; 											// Not minimized any more

	// Fix time gap
	sysTimeGap+=sysGetTime()-tStart;								// Add to total time gap

	EXIT_PROC();
}

//
// Minizimze if we are currently in full-screen, if we are in windowed mode, do nothing
//
void FASTCALL vidMinimize(zBOOL WaitRestore)
{
	zDWORD	tStart; 												// Start time
	ENTER_PROC(vidMinimize);

	// Start the 'minimizing' process by setting some flags
	TRACE_DEBUG("VID: Minimizing");

	// Minimize fullscreen window
	vidSetBusyWith(MINIMIZING); 									// We're busy, don't interrupt
	tStart=sysGetTime();											// Get start time
	winMinimized=TRUE;												// Minimized!
	DirectDrawSave(TRUE);											// Save surface contents
	ShowWindow(hWndApp, SW_SHOWMINIMIZED);							// Minimze Main App
	vidSetDoneWith(MINIMIZING); 									// Done!

	// Check sound (stop it if it's running)
	vidRestartSoundOnRestore=FALSE;						// Set restore flag

	// We're done minimizing (we might wait for the app to restore here)
	if (WaitRestore) vidWaitRestore();								// Do optional wait until restore
	
	// Fix time gap
	sysTimeGap+=sysGetTime()-tStart;								// Add to total time gap

	EXIT_PROC();
}

//
// Wait until the program is restored
//
void FASTCALL vidWaitRestore()
{
	ENTER_PROC(vidWaitRestore);

	// Wait until we are re-activated
	winWaitMessage(WM_SYSCOMMAND, SC_RESTORE, 0xFFF0, 0, 0, TRUE);	// Wait for restore message
	vidRestore();													// Restore from minimized mode

	EXIT_PROC();
}



//
// Restore from minimized or idle mode mode
//
void FASTCALL vidRestore()
{
	ENTER_PROC(vidRestore);
	TRACE_DEBUG("VID: Restoring");

	// Restore fullscreen window
	vidSetBusyWith(RESTORING);										// In restore stuff
	if (isFullScreen()) 											// Set fullscreen stuff
	{
		// Set a topmost, fullscreen (maximized) window
		SetWindowLong(hWndApp, GWL_EXSTYLE, WS_EX_TOPMOST); 		// Set topmost style
		ShowWindow(hWndApp, SW_RESTORE);							// Restore window position
	}
	DirectDrawRestore(TRUE);										// Restore DirectDraw stuff
	if (vidResetPaletteOnRestore) vidResetPalette();				// Reset win32 palette
	vidSetDoneWith(RESTORING);										// Not restoring any more
	winMinimized=FALSE; 											// Not minimized any more

	EXIT_PROC();
}



//
// Check if the application is currently minimized
//
zBOOL vidIsMinimized()
{
	return IsIconic(hWndApp);
}


//
// Restore a surface from its backup copy
//
static void FASTCALL vidRestoreSurface(LPSURFACE pSurf)
{
//	LPBYTE	pBackup;												// -> Backup data
//	zDWORD	Line, dwBPL;											// Line counter, BPL

	ENTER_PROC(vidRestoreSurface);

	// Restore DirectDraw surface if this is a DirectDraw surface
	if (pSurf->APISpecific[API_MODE]==VIDMODE_DDRAW)
	{
		LPDIRECTDRAWSURFACE7 pddSurf=GetDDSurf(pSurf);				// Get -> IDirectDraw interface
		if (IDirectDrawSurface_IsLost(pddSurf)) 					// This surface lost?
		{
			pSurf->Lost=TRUE;										// Set lost surface flag
			ddCheck(IDirectDrawSurface_Restore(pddSurf));			// Restore surface if needed
		}
	}
  
	EXIT_PROC();
}

/**{ vidBlit, Video }
@func

The vidBlit function performs one blitting operation.

@params

@return
	The return value is TRUE when the blit was performed successfully or has been
	queued. The return value is FALSE if the blit could not be performed.

@remarks
	There are a lot of assertions in the debug version of the libraries to see
	if the @@BLIT_CMD structure you pass is valid and to check if your aren't trying
	to do something that is illegal. These checks aren't done in the release version of
	the executable for performance reasons. The amount of code from your call to
	vidBlit and where the blitter code starts is kept to an absolute minimum; no
	error checking is done (except to detect if the blit command is supported). It
	is important that you test your application thoroughly with the debug libraries.

	In simple video modes, @!vidBlit(NULL) blits the entire system memory backbuffer to
	a visual buffer. Currently, this is the only supported blitting operation in simple
	video modes. On all platforms in most circumstances, you will be able to get into
	any direct-write mode where you can do more "advanced" blitting operations.

	vidBlit will use hardware blitting whenever possible.

	There are restrictions on what you can blit, depending on the video access mode.
	Almost anything is possible in VAM_DIRECT mode; VAM_SIMPLE mode poses a lot more
	limitations on blitting functionality. For more information, see the video mode
	overview.

	For more information on the members of pBlit and how they can be used, refer to
	the @@BLIT_CMD documentation.

@portable

@see vidBlitEx vidBlitBatch vidFlip vidGetStdSurface BLIT_CMD
**/
zBOOL vidBlit(
	LPBLIT_CMD pBlit		/* Blit command to perform
	Pointer to a @@BLIT_CMD structure that specifies the blit operation. This
	parameter can be NULL in simple video modes; the default backbuffer will
	then be blitted to the visual surface.*/
)
{
	static BLIT_CMD lBlit = { NULL, NULL, NULL, NULL, BLIT_COPY, 0 };	// Local blit command
	zBOOL	res;													// Result value

	ENTER_PROC(vidBlit);

	// When pBlit is NULL, we have a "full screen" simple copy
	if (pBlit==NULL)
	{
		zBOOL	ddrawMode=isDirectDraw();							// In DirectDraw?
		
		// When the structure changes, these ASSERTs will fail		
		ASSERT((ddrawMode==FALSE) || (ddrawMode==TRUE));			// Must be valid BOOL
		ASSERT(lBlit.dstRect==NULL);								// Full rectangle
		ASSERT(lBlit.srcRect==NULL);								// Full rectangle
		ASSERT(lBlit.Command==BLIT_COPY);							// Simple blit copy
		ASSERT(lBlit.Data==0);										// No blit data

		// Create new blit command
		lBlit.srcSurf=vidSysBufs[0];								// ->Backbuffer
		lBlit.dstSurf=vidGetStdSurface(VIDMEM_VIDEO, ddrawMode);	// -> Front(0) or Back(1) Buffer

		// If we're doing DirectDraw, perform the blit and flip here
		if (ddrawMode)
		{
			ASSERT(vidBlitFunc[BLIT_COPY]); 						// Must support blit command
			ASSERT(vidVidBufs[0]->APISpecific[API_PTR]!=0xDEADBEAF);// Can't have fake surfaces here
			ASSERT(vidVidBufs[1]->APISpecific[API_PTR]!=0xDEADBEAF);// Can't have fake surfaces here
			res = vidBlitFunc[BLIT_COPY](&lBlit);					// Blit it and save result
			res &= vidFlip();										// Flip DirectDraw surfaces
			RETURN(res);											// Return result
		}
		else
		{
			// Mark this frame as "ready" and accept this blit command
			vidSetFrameReady(); 									// "Mount" this frame
			pBlit=&lBlit;											// Do this
		}
	}

	// Check if the minimal parameters have been passed
#ifdef _DEBUG
	ASSERT(pBlit != NULL);
	ASSERTT(pBlit->Command < BLIT_COMMANDS, "Illegal blit command (>=BLIT_MODES)!");

	// Check destination surface if it's there
	if (pBlit->dstSurf)
	{
		ASSERTT(pBlit->dstSurf->Ptr==NULL, "The destination surface for vidBlit is locked!");
		if (pBlit->dstRect)
		{
			ASSERT_NOCLIP(pBlit->dstRect, pBlit->dstSurf);
			ASSERTRECT(pBlit->dstRect);
		}
	}

	// Check source surface if it's there
	if (pBlit->srcSurf)
	{
		ASSERTT(pBlit->srcSurf->Ptr==NULL, "The source surface for vidBlit() may not be locked!");
		if (pBlit->srcRect)
		{
			ASSERT_NOCLIP(pBlit->srcRect, pBlit->srcSurf);
			ASSERTRECT(pBlit->srcRect);
		}
	}

	// Check properties of "simple" surfaces that act as a dummy for DIB
	if (pBlit->dstSurf->APISpecific[API_PTR]==0xDEADBEAF)
	{
		ASSERTT(!isDirectDraw(), "Bogus \"special\" VAM_SIMPLE surface in DirectDraw mode");
		ASSERTT(vidSimpleBlitFunc!=NULL, "No destination blitter");
	}
	ASSERTT(pBlit->srcSurf->APISpecific[API_PTR] != 0xDEADBEAF, "Illegal source surface - can't blit from display");

	// Check if blit command is supported
	if (vidBlitFunc[pBlit->Command]==NULL) TRACE("VID: Warning! vidBlit failed - Blit Command %u not supported", pBlit->Command);
#endif

	// If the destination surface has a API_PTR of 0xDEADBEAF it is a signal to us that
	// that surface specifies a simple mode
	if (pBlit->dstSurf->APISpecific[API_PTR]==0xDEADBEAF) 
	{
		res=vidSimpleBlitFunc(pBlit);								// Do simple blitter
		RETURN(res);
	}

	// Check if blit command is supported, if not, return FALSE
	if (vidBlitFunc[pBlit->Command]==NULL) RETURN(FALSE);			// Blit not supported

	// Blit it!
	res=vidBlitFunc[pBlit->Command](pBlit); 						// Blit it and save result
	RETURN(res);
}

/**{ vidBlitBatch, Video }
@func

vidBlitBatch performs a number of blitting operations in sequence. If the hardware supports batch blitting and it is supported by the system, this can have a positive impact on blitting speed.

@params
@return
	The return value is TRUE if all blits were performed or queued
	successfully. The return value is FALSE if one or more blits
	could not be performed.

@remarks
	vidBlitBatch currently doesn't support hardware batch blitting.
	DirectDraw has a function for it, but it is not yet implemented. It
	is expected that future video boards can exploit the use of batch
	blitting to improve speed. Video boards might be able to generate
	an IRQ when a blit has finished, that would allow a software interrupt
	handler to schedule the next blit in the batch, thus maximizing video
	memory bandwidth.

	This function will be improved as time comes.

@portable
@see vidBlit vidBlitEx BLIT_CMD
**/
zBOOL vidBlitBatch(
	BLIT_CMD *pBlits,		/* -> List of rectangles to blit
	Pointer to an array of BLIT_CMD structures. There must be nBlitEntries
	BLIT_CMD structures at pBlits.*/
	
	int 	nBlits			/* Amount of rectangles to blit
	The amount of BLIT_CMD structures at pBlits. */
)
{
	zBOOL	res=TRUE;												  // Blit result
	
	ENTER_PROC(vidBlitBatch);
	
	// Do all blits. Return TRUE if all worked out, return FALSE if one ore more failed
	while (nBlits--) res&=vidBlit(pBlits++);						  // Do blit
	
	RETURN(res);
}

//
// Check for focus loss by checking if the front buffer surface has been lost
//
zBOOL FASTCALL vidLostFocus()
{
	// Must have a DirectDraw object, IDirectDrawSurface, etc
	if (!dd7) return FALSE;
	if (!vidVidBufs[0]) return FALSE;
	if (vidVidBufs[0]->APISpecific[API_MODE]!=VIDMODE_DDRAW) return FALSE;
	if (!GetDDSurf(vidVidBufs[0])) return FALSE;

	return IDirectDrawSurface_IsLost(GetDDSurf(vidVidBufs[0])); 	// Return TRUE if surface is lost
}

#ifdef _DEBUG
/**{ vidBlitEx, Video }
@func

vidBlitEx performs a single blit. Its functionality is the same as
vidBlit, only the way the parameters for the blit are passed is
different. vidBlit is slightly faster than vidBlitEx.

@params
@return
	The return value is TRUE when the blit was performed successfully or
	has been queued. The return value is FALSE if the blit could not be
	performed.

@portable
@see vidBlit vidBlitBatch BLIT_CMD
**/
zBOOL vidBlitEx(
	SURFACE *dstSurf,		/* Destination surface
	Destination surface for blitting operation. This surface must not be locked. */
	
	RECT	*dstRect,		/* Destination rectangle
	Rectangle on destSurf that will be the destination rectangle of the
	blitting operation. */
	
	SURFACE *srcSurf,		/* Source surface
	Source surface for blitting operation. This surface must not be locked. */
	
	RECT	*srcRect,		/* Source rectangle
	Rectangle on srcSurf that will be the source of the blitting operation. */
	
	int 	Command,		/* Blit command
	Blit command. You can find a list of blit command at the documentation
	of the BLIT_CMD structure. */
	
	zDWORD	Data			/* Blit command data
	Data value for blitting operation. This is an optional parameter to
	Command. Its interpretation relies on Command. */
)
{
	BLIT_CMD bCmd;													  // Blit command
	
	ENTER_PROC(vidBlitEx);
	
	// Copy parameters to a blit structure and pass it on to vidBlit
	//
	// We have to have it in a structure anyway, because it is passed on to a blitting
	// function that takes a pointer to a blit command structure
	bCmd.dstSurf=dstSurf;											  // Copy Destination surface
	bCmd.dstRect=dstRect;											  // Copy Destination rectangle
	bCmd.srcSurf=srcSurf;											  // Copy Source surface
	bCmd.srcRect=srcRect;											  // Copy Source rectangle
	bCmd.Command=Command;											  // Copy Blit command
	bCmd.Data=Data; 												  // Copy Blit parameter
	
	RETURN(vidBlit(&bCmd)); 										  // Pass on to blit
}
#endif

// Video mode set (replaces setVidMode)
zBOOL FASTCALL SetVMode(LPVIDMODE NewMode)
{
  if (winSetVideoMode)
	return winSetVideoMode(NewMode);
  else
	return vidSetMode(NewMode);
}

/***********************************************************************************\
**																				   **
**								   DirectDraw code								   **
**																				   **
\***********************************************************************************/
// DirectDraw error structure
typedef struct
{
  HRESULT Error;													// Error code
  char*  Text; 													// -> Error text
} DirectDrawError;

// DirectDraw error codes + description
static DirectDrawError ddErrors[]={
	{ DDERR_ALREADYINITIALIZED, 		  "Already initialized" },
	{ DDERR_BLTFASTCANTCLIP,			  "BltFast Can't Clip" },
	{ DDERR_CANNOTATTACHSURFACE,		  "Surface can't be Attached" },
	{ DDERR_CANNOTDETACHSURFACE,		  "Surface can't be Detached" },
	{ DDERR_CANTCREATEDC,				  "Can't Create DC" },
	{ DDERR_CANTDUPLICATE,				  "Can't Duplicate Surface" },
	{ DDERR_CANTPAGELOCK,				  "Can't Lock Page" },
	{ DDERR_CANTPAGEUNLOCK, 			  "Can't Unlock Page" },
	{ DDERR_CLIPPERISUSINGHWND, 		  "Clipper is monitoring a HWND" },
	{ DDERR_COLORKEYNOTSET, 			  "No Color key set" },
	{ DDERR_CURRENTLYNOTAVAIL,			  "Support is currently not available" },
	{ DDERR_DIRECTDRAWALREADYCREATED,	  "DirectDraw object already created" },
	{ DDERR_DCALREADYCREATED,			  "DC Already created" },
	{ DDERR_EXCEPTION,					  "Exception occured" },
	{ DDERR_EXCLUSIVEMODEALREADYSET,	  "Exclusive mode is already set" },
	{ DDERR_GENERIC,					  "Generic Failure" },
	{ DDERR_HEIGHTALIGN,				  "H-Alignment Error" },
	{ DDERR_HWNDALREADYSET, 			  "HWND already set" },
	{ DDERR_HWNDSUBCLASSED, 			  "HWND is subclassed" },
	{ DDERR_IMPLICITLYCREATED,			  "Can't restore implicit surface" },
	{ DDERR_INCOMPATIBLEPRIMARY,		  "Incompatible primary buffer" },
	{ DDERR_INVALIDCAPS,				  "Invalid Caps" },
	{ DDERR_INVALIDCLIPLIST,			  "Invalid Cliplist" },
	{ DDERR_INVALIDDIRECTDRAWGUID,		  "Invalid GUID" },
	{ DDERR_INVALIDMODE,				  "Invalid Display mode" },
	{ DDERR_INVALIDOBJECT,				  "Invalid Object" },
	{ DDERR_INVALIDPARAMS,				  "Invalid Parms" },
	{ DDERR_INVALIDPIXELFORMAT, 		  "Invalid PixelFormat" },
	{ DDERR_INVALIDPOSITION,			  "Invalid Position" },
	{ DDERR_INVALIDRECT,				  "Invalid Rectangle" },
	{ DDERR_INVALIDSURFACETYPE, 		  "Invalid Surface Type" },
	{ DDERR_LOCKEDSURFACES, 			  "Locked surface" },
	{ DDERR_NO3D,						  "No 3D" },
	{ DDERR_NOALPHAHW,					  "No Alpha hardware" },
	{ DDERR_NOBLTHW,					  "No Blitter hardware" },
	{ DDERR_NOCLIPPERATTACHED,			  "No Clipper attached" },
	{ DDERR_NOCLIPLIST, 				  "No cliplist" },
	{ DDERR_NOCOLORCONVHW,				  "No color conversion hardware" },
	{ DDERR_NOCOLORKEY, 				  "No color key" },
	{ DDERR_NOCOLORKEYHW,				  "No hardware color key" },
	{ DDERR_NOCOOPERATIVELEVELSET,		  "No Cooperative level set" },
	{ DDERR_NODC,						  "No DC for surface" },
	{ DDERR_NODDROPSHW, 				  "No DirectDraw ROP hardware" },
	{ DDERR_NODIRECTDRAWHW, 			  "No DirectDraw hardware" },
	{ DDERR_NODIRECTDRAWSUPPORT,		  "No DirectDraw support currently" },
	{ DDERR_NOEMULATION,				  "No emulation available" },
	{ DDERR_NOEXCLUSIVEMODE,			  "No exclusive mode" },
	{ DDERR_NOFLIPHW,					  "No page flip support" },
	{ DDERR_NOGDI,						  "No GDI present" },
	{ DDERR_NOHWND, 					  "No HWND for cooperation" },
	{ DDERR_NOMIRRORHW, 				  "No mirror hardware" },
	{ DDERR_NOOVERLAYDEST,				  "No overlay destination" },
	{ DDERR_NOOVERLAYHW,				  "No overlay hardware" },
	{ DDERR_NOPALETTEATTACHED,			  "No palette attached" },
	{ DDERR_NOPALETTEHW,				  "No palette hardware" },
	{ DDERR_NORASTEROPHW,				  "No ROP hardware" },
	{ DDERR_NOROTATIONHW,				  "No rotation hardware" },
	{ DDERR_NOSTRETCHHW,				  "No stretching hardware" },
	{ DDERR_NOT8BITCOLOR,				  "Not an 8 bit mode" },
	{ DDERR_NOTAOVERLAYSURFACE, 		  "Not an overlay surface" },
	{ DDERR_NOTEXTUREHW,				  "No texture hardware" },
	{ DDERR_NOTFLIPPABLE,				  "Not flippable" },
	{ DDERR_NOTFOUND,					  "Item was not found" },
	{ DDERR_NOTINITIALIZED, 			  "Not initialized" },
	{ DDERR_NOTLOCKED,					  "Not locked" },
	{ DDERR_NOTPAGELOCKED,				  "Page not locked" },
	{ DDERR_NOTPALETTIZED,				  "Not palettized" },
	{ DDERR_NOVSYNCHW,					  "No VSYNC hardware" },
	{ DDERR_NOZBUFFERHW,				  "No hardware Z buffer" },
	{ DDERR_NOZOVERLAYHW,				  "No hardware Z overlay" },
	{ DDERR_OUTOFCAPS,					  "Out of Caps" },
	{ DDERR_OUTOFMEMORY,				  "Out of Memory" },
	{ DDERR_OUTOFVIDEOMEMORY,			  "Out of Video Memory" },
	{ DDERR_OVERLAYCANTCLIP,			  "No clip overlay support" },
	{ DDERR_OVERLAYCOLORKEYONLYONEACTIVE, "Only one color key for overlay" },
	{ DDERR_OVERLAYNOTVISIBLE,			  "Overlay hidden" },
	{ DDERR_PALETTEBUSY,				  "Palette busy" },
	{ DDERR_PRIMARYSURFACEALREADYEXISTS,  "Primary surface already exists" },
	{ DDERR_REGIONTOOSMALL, 			  "Region for clipper too small" },
	{ DDERR_SURFACEALREADYATTACHED, 	  "Surface already attached" },
	{ DDERR_SURFACEALREADYDEPENDENT,	  "Surface already dependant" },
	{ DDERR_SURFACEBUSY,				  "Surface busy" },
	{ DDERR_SURFACEISOBSCURED,			  "Surface obscured" },
	{ DDERR_SURFACELOST,				  "Surface lost" },
	{ DDERR_SURFACENOTATTACHED, 		  "Surface not attached" },
	{ DDERR_TOOBIGHEIGHT,				  "Height is too big" },
	{ DDERR_TOOBIGSIZE, 				  "Size is too big" },
	{ DDERR_TOOBIGWIDTH,				  "Width is too big" },
	{ DDERR_UNSUPPORTED,				  "Unsupported action" },
	{ DDERR_UNSUPPORTEDFORMAT,			  "Unsupported FOURCC format" },
	{ DDERR_UNSUPPORTEDMODE,			  "Unsupported mode" },
	{ DDERR_UNSUPPORTEDMASK,			  "Unsupported mask" },
	{ DDERR_VERTICALBLANKINPROGRESS,	  "Vertical blank in progress" },
	{ DDERR_WASSTILLDRAWING,			  "DirectDraw still drawing" },
	{ DDERR_WRONGMODE,					  "Wrong mode" },
	{ DDERR_XALIGN, 					  "X-Alignment error" }
  };
#define DD_ERRORS (sizeof(ddErrors)/sizeof(DirectDrawError))

// Small functions

//
// Return a pointer to a DIRECTDRAWSURFACE from a SURFACE that was allocated with
// a valid DIRECTDRAWSURFACE
//
static LPDIRECTDRAWSURFACE7 INLINE GetDDSurf(LPSURFACE Surface)
{
  ENTER_PROC(GetDDSurf);

  ASSERT(Surface);
  ASSERT(Surface->APISpecific[API_MODE]==VIDMODE_DDRAW);
  ASSERT(Surface->APISpecific[API_DDSURF]!=0);

  RETURN((LPDIRECTDRAWSURFACE7)Surface->APISpecific[API_DDSURF]);
}

//
// Init all DirectDraw stuff
//
static zBOOL DirectDrawInit(LPVIDMODE NewMode, zBOOL Resizing)
{
	int   i;														// Counter
	ENTER_PROC(DirectDrawInit);

	ASSERTT(dd7, "No IDirectDraw7 object");

	// Do some window and cooperative level setting when not resizing
	if (!Resizing)
	{
		// Create a full-screen DirectDraw mode
		zDWORD	dwFlags=DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN; 		// Exclusive fullscreen mode
		if (!vidDisableCtrlAltDel) dwFlags |= DDSCL_ALLOWREBOOT;	// And allow Ctrl+Alt+Del
		if (!ddCheck(IDirectDraw7_SetCooperativeLevel(dd7, hWndApp, dwFlags)))
			RETURN(FALSE);											// Can't set, bye!
	}
	
	// Set display mode
	if (!ddCheck(IDirectDraw7_SetDisplayMode(dd7, NewMode->si.Width, NewMode->si.Height, NewMode->si.BPP, 0, 0)))
		RETURN(FALSE);												// Return FALSE if can't set VMode
	
	// Allocate as much SURFACE structures as there are front buffers. We should not
	// encounter a non-NULL pointer as vidVidBufs[0..2] (all primary surfaces should be
	// destroyed at this point, we're creating new ones from scratch)
	ASSERTT(NewMode->VidMemBuffers >= 1, "Must have video memory buffers");
	for (i=0; i<3; i++)
	{
		ASSERT(vidVidBufs[i] == NULL);
		
		// Check if we need to allocate this buffer
		if (i < NewMode->VidMemBuffers) 							// In user range?
		{
			// Create a screen-compatible video memory SURFACE structure
			vidVidBufs[i]=(LPSURFACE)sysAlloc(sizeof(SURFACE)); 	// Allocate memory for surface
			memcpy(&vidVidBufs[i]->si, &NewMode->si, sizeof(SURFACE_INFO));// Clone surface info
			
			// Fill in parameters for clone
			vidVidBufs[i]->APISpecific[API_MODE]=VIDMODE_DDRAW; 	// DirectDraw surface!
			vidVidBufs[i]->si.MemType=VIDMEM_VIDEO; 				// Create Video memory surfac
			vidVidBufs[i]->Ptr=NULL;								// No pointer
			vidVidBufs[i]->Pitch=0; 								// No pitch
			vidVidBufs[i]->APISpecific[API_MODE]=VIDMODE_DDRAW; 	// DirectDraw surface identifier
		}
		else vidVidBufs[i]=NULL;									   // Make sure it's unused
	}
  
	// Create flippable primary display surfaces
	//
	// Note: After this call the first primary structure is known and 
	// vidVidBufs[0]->APISpecific[API_DDSURF] is a valid LPDIRECTDRAWSURFACE
	// pointer.  The vidVidBufs[1] and vidVidBufs[2] structures have been allocated
	// and properly filled in if they should be, they only miss a valid
	// LPDIRECTDRAWSURFACE pointer (see DirectDrawGetBackBuffers);
	DirectDrawCreateSurface(vidVidBufs[0], NewMode->VidMemBuffers); // Create primary surfaces
	vidLL_AddSurface(vidVidBufs[0]);								// Add surface to linked list
	DirectDrawGetBackBuffers(NewMode);								// Get backbuffer pointers
	DirectDrawSetPalette(); 										// Keep palette

	// Check actual pixelformat in highcolor modes
	if (NewMode->si.BPP>8)
	{
		memZeroSmall(&ddPixelFormat, sizeof(ddPixelFormat));		// Wipe pixel format
		ddPixelFormat.dwSize=sizeof(DDPIXELFORMAT);					// Set size of structure
		IDirectDrawSurface_GetPixelFormat(GetDDSurf(vidVidBufs[0]), &ddPixelFormat);
		
		VideoHwModeCur.si.rgbMasksValid=TRUE;						// RGB masks are valid
		VideoHwModeCur.si.rgbRMask=ddPixelFormat.dwRBitMask;		// Red color mask
		VideoHwModeCur.si.rgbGMask=ddPixelFormat.dwGBitMask;		// Green color mask
		VideoHwModeCur.si.rgbBMask=ddPixelFormat.dwBBitMask;		// Blue color mask
	}

	// Install DirectDraw blitters
	DirectDrawSetBlitters();										// Install
	vidSimpleBlitFunc=NULL; 										// Remove blit func
	
	RETURN(TRUE);
}

//
// Save DirectDraw state (contents of the surfaces) and hide DirectDraw window
//
static void DirectDrawSave(zBOOL HideWin)
{
	ENTER_PROC(DirectDrawSave);

	if ((dd7==NULL) || (!isDirectDraw())) EXIT_PROC();				// Must have DirectDraw object

	// Hide window if required
	if (HideWin)
	{
		// Return window to normal
		ShowWindow(hWndApp, SW_HIDE);								// Hide main window
		SetWindowLong(hWndApp, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW);// Normal window

		// Increase cooperative level and reset display mode
		ddCheck(IDirectDraw7_SetCooperativeLevel(dd7, hWndApp, DDSCL_NORMAL));
		IDirectDraw2_FlipToGDISurface(dd7);							// Flip to GDI surface
	}

	EXIT_PROC();
}

//
// Restore DirectDraw mode and surfaces
//
static void DirectDrawRestore(zBOOL RestoreWin)
{
	LPSURFACE pSurf=vidLL_Last; 									// -> Surface list
	ENTER_PROC(DirectDrawRestore);

	// Check if we're in DirectDraw, if not, quit right away
	if ((dd7==NULL) || (!isDirectDraw())) EXIT_PROC();				// No DirectDraw object

	// Restore video mode if needed
	if (RestoreWin)
	{
		zDWORD	dwFlags=DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN; 		// Exclusive fullscreen mode
		if (!vidDisableCtrlAltDel) dwFlags |= DDSCL_ALLOWREBOOT;	// And allow Ctrl+Alt+Del
		ddCheck(IDirectDraw7_SetCooperativeLevel(dd7, hWndApp, dwFlags));
		ddCheck(IDirectDraw7_SetDisplayMode(dd7, VideoHwModeCur.si.Width, VideoHwModeCur.si.Height, VideoHwModeCur.si.BPP, 0, 0));
	}
	vidRestoreSurface(vidVidBufs[0]);								// Restore primary surface

	DirectDrawSetPalette(); 										// Keep palette <please?>

	// Restore all surfaces
	while (pSurf)
	{
		vidRestoreSurface(pSurf);									// Restore surface state please
		pSurf=(LPSURFACE)pSurf->pPrev;								// -> Previous item
	}

	// Restore backbuffers (they are not in the linked list)
	if (vidVidBufs[1]) vidRestoreSurface(vidVidBufs[1]);			// Save first backbuffer
	if (vidVidBufs[2]) vidRestoreSurface(vidVidBufs[2]);			// Save second backbuffer

	EXIT_PROC();
}

//
// Shut DirectDraw down
//
// "Resizing" means that this DirectDraw mode is closed, but a next one is immediately
// following. Some steps are omitted to make the process more fluent.
//
static void DirectDrawExit(zBOOL Resizing)
{
	ENTER_PROC(DirectDrawExit);
	
	// Don't be too hard when resizing, don't restore the display mode, that looks bad
	if (!Resizing)
	{
		// Wipe video memory
		
		// Get out of exclusive video mode access
		if (!ddWindowed)											// No display mode crap for windowed mode
		{
			IDirectDraw7_SetCooperativeLevel(dd7, hWndApp, DDSCL_NORMAL);  // Remove exclusive mode
			IDirectDraw7_FlipToGDISurface(dd7);						// Flip to GDI surface
		}
	}
	
	// Free clipper and palette
	if (ddClipper) { IDirectDrawClipper_Release(ddClipper); ddClipper=NULL; }
	if (ddPalette) { IDirectDrawPalette_Release(ddPalette); ddPalette=NULL; }
	
	EXIT_PROC();
}

//
// Initialise a DirectDraw windowed mode
//
static void DirectDrawWindowedInit(LPVIDMODE NewMode, zBOOL Windowed)
{
  ENTER_PROC(DirectDrawWindowedInit);

  TRACE("VID: Initialising DirectDraw Windowed %ux%ux%u", NewMode->si.Width, NewMode->si.Height, NewMode->si.BPP);


  EXIT_PROC();
}

//
// Create an IDirectDraw2 surface
//
// We are only allowed to fill in <Surface>'s APISpecific[0..2] members, APISpecific[3]
// is already used by video memory management.
//
const static zDWORD ddMemFlags[4] = {
	DDSCAPS_VIDEOMEMORY,											// For VIDMEM_ANY
	DDSCAPS_VIDEOMEMORY,											// For VIDMEM_VIDEO
	DDSCAPS_VIDEOMEMORY | DDSCAPS_NONLOCALVIDMEM,					// For VIDMEM_NONLOCALVIDEO
	DDSCAPS_SYSTEMMEMORY											// For VIDMEM_SYSTEM
};
static zBOOL DirectDrawCreateSurface(LPSURFACE Surface, zDWORD PrimarySurfaces)
{
	DDSURFACEDESC2 ddsd; 											 // DirectDraw surface description
	zBOOL	res;
	ENTER_PROC(DirectDrawCreateSurface);
	
	ASSERTT(Surface->si.MemType<4, "Unknown memory type");
	
	// Create surface description structure
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize  = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;

	// Set pixel format, width and height only for offscreen surfaces. The specifics
	// of the primary surfaces are determined by the current video mode.
	if (!PrimarySurfaces)
	{
		ddsd.dwFlags					   |= DDSD_PIXELFORMAT | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.dwWidth						= Surface->si.Width;
		ddsd.dwHeight						= Surface->si.Height;
		ddsd.ddsCaps.dwCaps 				= DDSCAPS_OFFSCREENPLAIN | ddMemFlags[Surface->si.MemType];
		ddsd.ddpfPixelFormat.dwSize 		= sizeof(ddsd.ddpfPixelFormat);
		ddsd.ddpfPixelFormat.dwFlags		= DDPF_RGB;
		ddsd.ddpfPixelFormat.dwRGBBitCount	= Surface->si.BPP;
		if (Surface->si.BPP > 8)
		{
			ASSERT(Surface->si.BPP==16 || Surface->si.BPP==32);
			ASSERT(Surface->si.rgbMasksValid);
			ddsd.ddpfPixelFormat.dwRBitMask = Surface->si.rgbRMask;
			ddsd.ddpfPixelFormat.dwGBitMask = Surface->si.rgbGMask;
			ddsd.ddpfPixelFormat.dwBBitMask = Surface->si.rgbBMask;
			ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = ddPixelFormat.dwRGBAlphaBitMask;
		}
		else
		{
			ASSERT(Surface->si.BPP == 8);
			ddsd.ddpfPixelFormat.dwFlags   |= DDPF_PALETTEINDEXED8;
			ddsd.ddpfPixelFormat.dwRBitMask = 0;
			ddsd.ddpfPixelFormat.dwGBitMask = 0;
			ddsd.ddpfPixelFormat.dwBBitMask = 0;
		}
	}
	
	// If <PrimarySurfaces> is set, this call is used to create multiple (<PrimarySurfaces>)
	// video buffers that are used as flipping surfaces. Adjust everything accordingly. For
	// all normal buffers, <PrimarySurfaces> is set to 0.
	if (PrimarySurfaces)
	{
		ASSERT(PrimarySurfaces>=1 && PrimarySurfaces<=3);
		ASSERTT(Surface->si.MemType == VIDMEM_VIDEO, "Can only create multiple surfaces at once in Video memory");
		
		// Set primary surface caps
		ddsd.ddsCaps.dwCaps 				= DDSCAPS_PRIMARYSURFACE;
		// | DDSCAPS_FRONTBUFFER
		
		// If there are backbuffers, enable them
		if (PrimarySurfaces>1)
		{
			ddsd.dwFlags					 |= DDSD_BACKBUFFERCOUNT;
			ddsd.ddsCaps.dwCaps 			  = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
			ddsd.dwBackBufferCount			  = PrimarySurfaces - 1;
		}
	}
	
	// Create DirectDraw surface
	res=ddCheck(IDirectDraw7_CreateSurface(dd7, &ddsd, (LPDIRECTDRAWSURFACE7 FAR *)&Surface->APISpecific[API_DDSURF], NULL));
	
	// Mark surface as DirectDraw surface
	if (res) Surface->APISpecific[API_MODE]=VIDMODE_DDRAW;			  // DirectDraw surface identifier
	
	RETURN(res);
}

//
// Free DirectDraw surface
//
INLINE static zBOOL DirectDrawFreeSurface(LPSURFACE Surface)
{
	IDirectDrawSurface7 *pSrf=GetDDSurf(Surface);					  // Get -> IDirectDraw2 surface
	zBOOL	res;

	ENTER_PROC(DirectDrawFreeSurface);

	ASSERTT(pSrf, "No IDirectDrawSurface7 pointer!");
	ASSERTT(dd7, "No IDirectDraw7 object");
	ASSERTT(Surface->Ptr == 0, "Cannot free a locked surface");

	res=ddCheck(IDirectDrawSurface_Release(pSrf));
	RETURN(res);
}

//
// Fill in the APISpecific[API_DDSURF] (pointer to IDirectDrawSurface) for the back-
// buffers of <NewMode> into vidVidBufs[]. vidVidBufs[0] is already the primary
// DirectDraw surface.
//
static void DirectDrawGetBackBuffers(LPVIDMODE NewMode)
{
	LPDIRECTDRAWSURFACE7 pDDFrontBuffer=GetDDSurf(vidVidBufs[0]), pDDBackBuffer1=NULL, pDDBackBuffer2=NULL; // ->Surfaces
	DDSCAPS2 ddscaps;												  // Surface caps
	
	ENTER_PROC(DirectDrawGetBackBuffers);
	
	ASSERT(NewMode->VidMemBuffers>=1 && NewMode->VidMemBuffers<=3);
	ASSERTT(pDDFrontBuffer != NULL, "IDirectDrawSurface7 pointer not found in primary buffer");
	
	// Get pointers of 0, 1 or 2 backbuffers
	if (NewMode->VidMemBuffers>1)									  // Got 1 backbuffer?
	{
		// Get a pointer to the first back buffer
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;							// Get BackBuffer
		ddCheck(IDirectDrawSurface7_GetAttachedSurface(pDDFrontBuffer, &ddscaps, &pDDBackBuffer1));
		vidVidBufs[1]->APISpecific[API_DDSURF]=(zDWORD)pDDBackBuffer1;	// Save ->BackBuffer1
		
		// Check for second backbuffer
		if (NewMode->VidMemBuffers>2)									// Got 2 backbuffers?
		{
			// Get a pointer to the second back buffer
			ddscaps.dwCaps = DDSCAPS_FLIP;								  // Get extra flippable buffer
			ddCheck(IDirectDrawSurface7_GetAttachedSurface(pDDBackBuffer1, &ddscaps, &pDDBackBuffer2));
			vidVidBufs[2]->APISpecific[API_DDSURF]=(zDWORD)pDDBackBuffer2; // Save ->BackBuffer2
		}
	}
	
	EXIT_PROC();
}

//
// Flip to a different page
//
INLINE static zBOOL DirectDrawFlip()
{
	LPDIRECTDRAWSURFACE7 pPrimSurf=GetDDSurf(vidVidBufs[0]); 		// -> Primary surface
	HRESULT 	res;

	ENTER_PROC(DirectDrawFlip);

	// Flip to this surface. The Flip() function is called on a IDirectDrawSurface,
	// rather than the more logical IDirectDraw2. So, to flip to one of the primary video
	// surface, choose any of them and call that surface's Flip() function with an
	// override to the current surface to flip to it.
//	DirectDrawEnsureSurface(pPrimSurf); 							// Make sure surface is present
	res=ddCheck(IDirectDrawSurface_Flip(pPrimSurf, NULL, DDFLIP_WAIT));
/*
if (res==DDERR_SURFACELOST)
{
	TRACE("Surface lost: Restoring");
	ddCheck(IDirectDrawSurface_Restore(pPrimSurf));
}
*/
	RETURN(res);													// Flip to this page
}

//
// Wait for VSYNC
//
INLINE static void DirectDrawWaitVSYNC()
{
	ENTER_PROC(DirectDrawWaitVSYNC);
	
	ddCheck(IDirectDraw2_WaitForVerticalBlank(dd7, DDWAITVB_BLOCKBEGIN, NULL));
	
	EXIT_PROC();
}

//
// Return combination of VC_* capability bits for DirectDraw
//
INLINE static zDWORD DirectDrawGetCaps()
{
	DDCAPS	hwCaps; 												// HAL caps
	DDCAPS	swCaps; 												// HEL caps
	zDWORD	Caps=0; 												// Returned caps
	ENTER_PROC(DirectDrawGetCaps);

	// Check if there is a DirectDraw object at all
	if (dd7==NULL) RETURN(0);										// No IDirectDraw -> no caps

	// Get capabilities
	memZero(&swCaps, sizeof(DDCAPS));								// Wipe software caps
	memZero(&hwCaps, sizeof(DDCAPS));								// Wipe hardware caps
	swCaps.dwSize = sizeof(DDCAPS); 								// Set size of HEL caps
	hwCaps.dwSize = sizeof(DDCAPS); 								// Set size of HAL caps

	if (!ddCheck(IDirectDraw7_GetCaps(dd7, &hwCaps, &swCaps))) RETURN(0);	// Get driver caps

	if ((hwCaps.dwCaps	& DDCAPS_NOHARDWARE)==0)		Caps |= VCAPS_HARDWARE;
	if	(hwCaps.dwCaps	& DDCAPS_BANKSWITCHED)			Caps |= VCAPS_BANKSWITCHED;
	if	(hwCaps.dwCaps	& DDCAPS_3D)					Caps |= VCAPS_3D;
	if	(hwCaps.dwCaps	& DDCAPS_BLT)					Caps |= VCAPS_BLIT;
	if	(hwCaps.dwCaps	& DDCAPS_BLTQUEUE)				Caps |= VCAPS_BLITQUEUE;
	if	(hwCaps.dwCaps	& DDCAPS_BLTSTRETCH)			Caps |= VCAPS_BLITSTRETCH;
	if	(hwCaps.dwCaps	& DDCAPS_CANBLTSYSMEM)			Caps |= VCAPS_BLITSYSMEM;
	if	(hwCaps.dwCaps	& DDCAPS_ALPHA) 				Caps |= VCAPS_ALPHA;
	if	(hwCaps.dwCaps2 & DDCAPS2_NONLOCALVIDMEM)		Caps |= VCAPS_NONLOCALVIDMEM;
	if	(hwCaps.dwCaps2 & DDCAPS2_NOPAGELOCKREQUIRED)	Caps |= VCAPS_AUTODMA;
	if	(hwCaps.dwCaps2 & DDCAPS2_WIDESURFACES) 		Caps |= VCAPS_WIDESURF;

	RETURN(Caps);
}



//
// Set palette for directdraw surfaces
//
// Note: DirectDrawSetPalette is also called from DirectDrawInit where the video system
//		 isn't in a stable state yet. We don't rely on the contents of VideoModeCur.
//
static void DirectDrawSetPalette()
{
	zDWORD	i;														// Counter
	
	ENTER_PROC(DirectDrawSetPalette);
	
	// If there's no display, or it isn't 8 BPP, forget it
	if ((vidVidBufs[0]==NULL) || (vidVidBufs[0]->si.BPP!=8)) EXIT_PROC();
	
	// Create IDirectDrawPalette object if it's not yet there
	if (ddPalette)
	{
		// Change the colors in the existing IDirectDrawPalette
		if (!ddCheck(IDirectDrawPalette_SetEntries(ddPalette, 0, 0, 256, vidWinPal.palPalEntry))) EXIT_PROC();
	}
	else
	{
		// Create a new IDirectDrawPalette
		if (!ddCheck(IDirectDraw7_CreatePalette(dd7, DDPCAPS_8BIT | DDPCAPS_ALLOW256 | DDPCAPS_INITIALIZE, vidWinPal.palPalEntry, &ddPalette, NULL))) EXIT_PROC();
		ASSERT(ddPalette);											// Should be here by prev. line

		// Set the new palette to all primary surfaces
		for (i=0; i<3; i++) if ((vidVidBufs[i]) && (!ddCheck(IDirectDrawSurface_SetPalette(GetDDSurf(vidVidBufs[i]), ddPalette)))) EXIT_PROC();
	}
	
	EXIT_PROC();
}

//
// Try to lock direct draw, signal error when failed
//
INLINE static zBOOL DirectDrawLockSurface(LPSURFACE Surface)
{
	IDirectDrawSurface7 *pSrf=GetDDSurf(Surface);					  // Get -> IDirectDraw surface
	DDSURFACEDESC2 ddsd; 											  // Surface description
	HRESULT ddRes;													  // Result of locking operation
	
	ENTER_PROC(DirectDrawLockSurface);
	
	ASSERTT(pSrf, "No IDirectDrawSurface7 pointer!");
	ASSERTT(dd7, "No IDirectDraw7 object");
	
/*	// If surface is lost, attempt to restore it
	if (IDirectDrawSurface_IsLost(pSrf)==DDERR_SURFACELOST) IDirectDrawSurface_Restore(pSrf);
	ASSERT(IDirectDrawSurface_IsLost(pSrf) == FALSE);
*/
	// Lock surface
	ZeroMemory(&ddsd, sizeof(ddsd));								  // Wipe out surface description
	ddsd.dwSize=sizeof(ddsd);										  // Set struct size
	ddRes=IDirectDrawSurface7_Lock(pSrf, NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_NOSYSLOCK | DDLOCK_WAIT, NULL);
	// Old DirectDraw implementations don't have DDLOCK_NOSYSLOCK
	if (ddRes==DDERR_INVALIDPARAMS) ddRes=IDirectDrawSurface_Lock(pSrf, NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	if (!ddCheck(ddRes)) RETURN(FALSE); 							  // Check lock result

	// Fill in surface bits and pieces
	Surface->Ptr=(LPBYTE)ddsd.lpSurface;							  // -> Video memory
	Surface->Pitch=ddsd.lPitch; 									  // Set width of offscreen buffer

	RETURN(TRUE);
}

//
// Unlock DirectDraw
//
INLINE static zBOOL DirectDrawUnLockSurface(LPSURFACE Surface)
{
	IDirectDrawSurface7 *pSrf=GetDDSurf(Surface);					  // Get -> IDirectDraw surface
	HRESULT ddRes;													  // Result of DirectDraw operation
	
	ENTER_PROC(DirectDrawUnLockSurface);
	
	ASSERTT(pSrf, "No IDirectDrawSurface7 pointer!");
	ASSERTT(dd7, "No IDirectDraw7 object");
	
	// UnLock surface
	ddRes=IDirectDrawSurface7_Unlock(pSrf, NULL);			  // Unlock surface
	if (!ddCheck(ddRes)) RETURN(FALSE); 							  // Exit with error
	
	RETURN(TRUE);
}



//
// DirectDraw mode enumeration proc
//
static HRESULT WINAPI ddEnumModes(LPDDSURFACEDESC2 lpSurf, LPVOID lpContext)
{
	VIDMODE *ddEntry;												// -> New entry

	// Return if this is some weirdo YUV surface or anything
	if ((lpSurf->ddpfPixelFormat.dwFlags & DDPF_RGB)==0) return DDENUMRET_OK;
	if ((lpSurf->ddpfPixelFormat.dwRGBBitCount!=8) && (lpSurf->ddpfPixelFormat.dwRGBBitCount!=16) && (lpSurf->ddpfPixelFormat.dwRGBBitCount!=32)) return DDENUMRET_OK; // Bye!

	// Add mode to list
	ddMode  = (VIDMODE*)sysReAlloc(ddMode, ++ddModes * sizeof(VIDMODE));		// Reallocate list
	ddEntry = ddMode+ddModes-1;										// -> Last entry
	ddEntry->hwModeType		= VIDMODE_DDRAW;						// DirectDraw video mode
	ddEntry->AccessMode		= VAM_DIRECT;							// DirectDraw direct access
	ddEntry->VidMemBuffers	= 1;									// Can create video buffers
	ddEntry->SysMemBuffers	= 0;									// Set to 0 (default)
	ddEntry->si.Width		= lpSurf->dwWidth;						// Get width
	ddEntry->si.Height		= lpSurf->dwHeight; 					// Get height
	ddEntry->si.BPP			= (zBYTE)lpSurf->ddpfPixelFormat.dwRGBBitCount;// Get bit count

	return DDENUMRET_OK;
}



//
// Get list of available directdraw modes
//
static void DirectDrawEnumModes(LPCFUNCP Filter)
{
	int   i;
	ENTER_PROC(DirectDrawEnumModes);

	ASSERT(vidGotMode[VIDMODE_DDRAW] || vidGotMode[VIDMODE_DDRAWWIN]);

	// Check if this is the first time we have to enumerate the modes
//	if (ddMode == NULL)
//	{
//		// Get mode list
//		ddModes = 0;												// No modes yet
//		ASSERTT(dd7, "Must have IDirectDraw7 object");
//		IDirectDraw2_EnumDisplayModes(dd7, 0, NULL, NULL, ddEnumModes); // Enum all display modes and set in list
//	}

	// Check all modes
	for (i=0; i<ddModes; i++)
		if (Filter(ddMode+i))										// Mode passes through filter?
			vidAddMode(ddMode+i);									// Then add it

	
	EXIT_PROC();
}

//
// Checks if DirectDraw is available. Returns TRUE or FALSE
//
typedef HRESULT (WINAPI *DDCREATEPROC) (GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter);
typedef HRESULT (WINAPI *DDCREATEEXPROC) (GUID FAR *lpGUID, LPDIRECTDRAW7 FAR *lplpDD, REFIID iid, IUnknown FAR *pUnkOuter);


//static zBOOL DirectDrawCheck()
//{
//	VIDMEM_INFO MemInfo;											// Info about video memory
//	char  ddPath[MAX_PATH]; 										// Path for ddraw.dll
//	char  ddVersion[512];											// Version string
//	ENTER_PROC(DirectDrawCheck);
//	
//	ASSERTT(sizeof(LPDIRECTDRAWSURFACE) == 4, "Pointer must be 4 zBYTEs!");
//	
//	// Find DirectDrawCreate() function
//	ddLib=LoadLibrary("ddraw.dll"); 								// Open library
//
//	// Check some stuff from the library
//	if (ddLib)
//	{
//		zBYTE  *viData, *pvBuf;										// -> Version info data
//		zDWORD viSize, vSize;										// Size of version info
//		zDWORD ignored;												// crap
//		
//		// Get ddraw.dll full path
//		//((FARPROC)ddCreate)=GetProcAddress(ddLib, "DirectDrawCreate");	// Get address of create function
//		ddCreate=(DDCREATEPROC)GetProcAddress(ddLib, "DirectDrawCreate");	// Get address of create function
//		ddCreateEx=(DDCREATEEXPROC)GetProcAddress(ddLib, "DirectDrawCreateEx"); // Get address of create function
//		GetModuleFileName(ddLib, ddPath, MAX_PATH-1);				// Get filename
//		viSize=GetFileVersionInfoSize(ddPath, &ignored);			// Size of req. mem block
//		
//		// Check if we could get some version info from ddraw.dll in either in English, the
//		// code pages tried are UniCode (preferred) and Windows, Western/International
//		if (viSize) 												// Only if was able to get size
//		{
//			zWORD  *pwLang;
//			char  verKey[512], verUni[512];							// Version key name
//			
//			viData=(zBYTE*)sysAlloc(viSize+32); 							// Get some mem
//			GetFileVersionInfo(ddPath, 0, viSize+32, viData);		// Get version info
//			VerQueryValue(viData, "\\VarFileInfo\\Translation", (void **)&pwLang, (PUINT)&vSize);
//			sprintf(verKey, "\\StringFileInfo\\%04X04E4\\ProductVersion", pwLang[0]);
//			sprintf(verUni, "\\StringFileInfo\\%04X04B0\\ProductVersion", pwLang[0]);
//			if ((VerQueryValue(viData, verKey, (void**)&pvBuf, (PUINT)&vSize)) ||
//				(VerQueryValue(viData, verUni, (void**)&pvBuf, (PUINT)&vSize)))
//				sprintf(ddVersion, " v%s", (char*)pvBuf); // Set version
//			sysFree(viData);										// Remove data
//		}
//	}
//	
//	// Check for DirectDraw presence
//	if  ((ddLib==NULL)
//		|| (ddCreateEx==NULL)
//		|| (ddCreateEx(NULL, &dd7, IID_IDirectDraw7, NULL) != DD_OK)
//		)
///*	if	((ddLib==NULL)												// No library?
//		|| (ddCreate==NULL) 										// Got a proc address?
//		|| (ddCreate(NULL, &dd1, NULL) != DD_OK)					// Can create IDirectDraw?
//		|| (IDirectDraw_QueryInterface(dd1, IID_IDirectDraw, (void**)&dd) != DD_OK) // Can get IDirectDraw2?
//		)			// Can get display mode?*/
///*	if	((ddLib==NULL)												// No library?
//		|| (ddCreate==NULL) 										// Got a proc address?
//		|| (ddCreate(NULL, &dd1, NULL) != DD_OK)					// Can create IDirectDraw?
//		|| (IDirectDraw_QueryInterface(dd, &IID_IDirectDraw2, &dd) != DD_OK) // Can get IDirectDraw2?
//		)			// Can get display mode?*/
//	{
//		// Something was wrong (either DirectDraw wasn't found at all, or only the IDirectDraw
//		// interface could be found and not IDirectDraw2
//		TRACE("VID:     DirectDraw not found or too old - Disabled"); // Can't do
//		FreeLibrary(ddLib); ddLib=NULL; 							// Remove library from memory
//		RETURN(FALSE);												// And it failed
//	}
//	
//	// Show DirectDraw info
//	TRACE("VID:     DirectDraw%s found", ddVersion);
//
//	// Get some info on DirectDraw memory
///	if (vidGetMemInfo(&MemInfo))
//	{
//		char   memString[128];										// String with memory staatistics
//		sprintf(memString, "VID:     Video memory %uKb (%uKb Free), AGP memory", MemInfo.vidMem>>10, MemInfo.vidMemFree>10);
//		if (MemInfo.agpMem)
//			sprintf(memString+strlen(memString), " %uKb (%uKb Free)", MemInfo.agpMem>>10, MemInfo.agpMemFree>>10);
//		else
//			strcat(memString, " N/A");
//		TRACE(memString);
//	}
//
//	RETURN(TRUE);
//}

//
// Return information about the video memory in pMemInfo
//
zBOOL vidGetMemInfo(VIDMEM_INFO *pMemInfo)
{
	DDSCAPS2 sCaps;													// Surface caps
	DDSURFACEDESC2 vMode;											// Video mode description
	ENTER_PROC(vidGetMemInfo);

	ASSERT(pMemInfo);

	// Check if we've got DirectDraw to provide us with the information we need
	if (!dd7) RETURN(FALSE);											// Ain't got no DirectDraw
	if (!vidCheckMemory) RETURN(FALSE);								// Don't allow memory check

	// Init structures and variables
	memZero(pMemInfo, sizeof(VIDMEM_INFO)); 						// Wipe out returned stats
	memZero(&vMode, sizeof(vMode)); 								// Wipe out video mode
	vMode.dwSize=sizeof(DDSURFACEDESC); 							// Set size of video mode
	sCaps.dwCaps=DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM; 		// Get local vid mem info
	
	if (!SUCCEEDED(IDirectDraw7_GetDisplayMode(dd7, &vMode))) RETURN(FALSE);
	if (!SUCCEEDED(IDirectDraw7_GetAvailableVidMem(dd7, &sCaps, &pMemInfo->vidMem, &pMemInfo->vidMemFree))) RETURN(FALSE)

	// Adjust estimation of video memory by adding the size of the frontbuffer to it
	pMemInfo->vidMem+=(vMode.dwBackBufferCount+1)*vMode.dwWidth*vMode.dwHeight*vMode.ddpfPixelFormat.dwRGBBitCount/8;
		
	// Get info on AGP mem too
	sCaps.dwCaps=DDSCAPS_NONLOCALVIDMEM;							// Get AGP mem stats
	IDirectDraw2_GetAvailableVidMem(dd7, &sCaps, &pMemInfo->agpMem, &pMemInfo->agpMemFree);

	RETURN(TRUE);
}


//
// Install the DirectDraw blitters
//
static void DirectDrawSetBlitters()
{
	zDWORD	i;														  // Counter
	
	// Set the Blit FX structures for the DirectDraw blitters (so we don't have to create
	// new FX structures every time we blit)
	for (i=0; i<BLIT_COMMANDS; i++)
	{
		memZero(&ddBlitFX[i], sizeof(DDBLTFX)); 						// Wipe out structure
		ddBlitFX[i].dwSize=sizeof(DDBLTFX); 							// Set struct size
	}
	
	// Fill blit function table with software blitters
	vidBlitFunc[BLIT_NONE]=NULL;									// No BLIT_NONE
	vidBlitFunc[BLIT_COPY]=DirectDraw_BLIT_COPY;					// Set BLIT_COPY
	vidBlitFunc[BLIT_SCKEY]=DirectDraw_BLIT_SCKEY;					// Set BLIT_SCKEY
	vidBlitFunc[BLIT_CALPHA_COPY]=DirectDraw_BLIT_CALPHA_COPY;		// Set BLIT_CALPHA_COPY
	vidBlitFunc[BLIT_FILLRECT]=NULL;								// No BLIT_FILLRECT
}

//
// Free DirectDraw library if it's loaded
//
static void DirectDrawFreeModule()
{
	ENTER_PROC(DirecDrawFreeModule);

	// Free interfaces, note: The IDirectDraw2 interface will have a reference count of 2
//	if (dd1)	{ IDirectDraw_Release(dd1); dd1=NULL; }
//	if (dd2)	{ if (IDirectDraw2_Release(dd2)) IDirectDraw2_Release(dd2); dd2=NULL; }
	if (dd7)	{ dd7->Release(); dd7=NULL; }
	if (ddLib)	{ FreeLibrary(ddLib); ddLib=NULL; }

	EXIT_PROC();
}

//
// Normal DirectDraw Blit Copy
//
static zBOOL FASTCALL DirectDraw_BLIT_COPY(LPBLIT_CMD pBlit)
{
	LPDIRECTDRAWSURFACE7 pSurf;										  // ->Destination surface
	HRESULT blitRes;												  // Blit result
	zBOOL	res;													  // Result value
	ENTER_PROC(DirectDraw_BLIT_COPY);
	
	pSurf=GetDDSurf(pBlit->dstSurf);								  // ->Destination surface
//	DirectDrawCheckSurf(pSurf); 									// Check surface for being lost, etc

	blitRes=IDirectDrawSurface7_Blt(pSurf, pBlit->dstRect, GetDDSurf(pBlit->srcSurf), pBlit->srcRect, DDBLT_WAIT, &ddBlitFX[BLIT_COPY]);
	res=ddCheck(blitRes);											  // Check and log error
	RETURN(res);
}

//
// DirectDraw blit with source color key
//
static zBOOL FASTCALL DirectDraw_BLIT_SCKEY(LPBLIT_CMD pBlit)
{
	LPDIRECTDRAWSURFACE7 pSurf;										  // ->Destination surface
	HRESULT blitRes;												  // Blit result
	zBOOL	res;													  // Result value
	ENTER_PROC(DirectDraw_BLIT_COPY);

	pSurf=GetDDSurf(pBlit->dstSurf);								  // ->Destination surface
//	DirectDrawCheckSurf(pSurf); 									// Check surface for being lost, etc

	blitRes=IDirectDrawSurface7_Blt(pSurf, pBlit->dstRect, GetDDSurf(pBlit->srcSurf), pBlit->srcRect, DDBLT_WAIT | DDBLT_KEYSRC, &ddBlitFX[BLIT_SCKEY]);
	res=ddCheck(blitRes);											  // Check and log error
	RETURN(res);
}

//
// DirectDraw blit with constant destination alpha
//
static zBOOL FASTCALL DirectDraw_BLIT_CALPHA_COPY(LPBLIT_CMD pBlit)
{
	LPDIRECTDRAWSURFACE7 pSurf;										  // ->Destination surface
	HRESULT blitRes;												  // Blit result
	zBOOL	res;													  // Result value
	ENTER_PROC(DirectDraw_BLIT_COPY);
	
	pSurf=GetDDSurf(pBlit->dstSurf);								  // ->Destination surface
//	  DirectDrawCheckSurf(pSurf);										// Check surface for being lost, etc
	
	ddBlitFX[BLIT_CALPHA_COPY].dwAlphaDestConstBitDepth=8;			// 8 Bits of alpha
	ddBlitFX[BLIT_CALPHA_COPY].dwAlphaDestConst=20; 				// 8 Bits of alpha
	blitRes=IDirectDrawSurface7_Blt(pSurf, pBlit->dstRect, GetDDSurf(pBlit->srcSurf), pBlit->srcRect, DDBLT_WAIT | DDBLT_ALPHADESTCONSTOVERRIDE, &ddBlitFX[BLIT_CALPHA_COPY]);
	res=ddCheck(blitRes);											  // Check and log error
	RETURN(res);
}

//
// Check DirectDraw function result, log an error if they fail
//
zBOOL ddCheck(HRESULT res)
{
	static char ukError[256];										// Unknown error code string
	int	 ddErrNo;													// DirectDraw error number
	
	if (res==DD_OK) return TRUE;

	// If the don't-show-errors flag is set, return immediately
	if (vidDontShowErrors) return FALSE;							// Return now, don't show error

	// Check all error to see if this is a known error
	for (ddErrNo=0; ddErrNo<DD_ERRORS; ddErrNo++)  if (ddErrors[ddErrNo].Error==res) break;
	
	// If we "fell through" all known error, show unknown error (analyse HRESULT value)
	if (ddErrNo==DD_ERRORS)
	{
#ifdef _DEBUG
		TRACE("VID: Warning! Unknown DirectDraw7 Error in proc %s", __cs_data[__cs_idx-1]);
		TRACE("              Error code : %u", res);
		TRACE("              Code       : %u", HRESULT_CODE(res));
		TRACE("              Facility   : %u", HRESULT_FACILITY(res));
		TRACE("              Severity   : %u", HRESULT_SEVERITY(res));
#endif
		sprintf(ukError, "Unknown DirectDraw7 error code %08X", res);
		vidLastError = ukError;										// Last error string
	}
	else
	{
		// 
#ifdef _DEBUG
		TRACE("VID: Warning! DirectDraw7 Error \"%s\" in proc %s <- %s <- %s", ddErrors[ddErrNo].Text, __cs_data[__cs_idx-1], __cs_data[max(0, __cs_idx-2)], __cs_data[max(0, __cs_idx-3)]);
#endif
		vidLastError = ddErrors[ddErrNo].Text;
	}
	
	return FALSE;
}



//
// Return pointer to last string
//
char *vidGetLastError()
{
	return (vidLastError==NULL) ? "No error" : vidLastError;
}



/***********************************************************************************\
**																				   **
**									Direct3D code								   **
**																				   **
\***********************************************************************************/

//
// Checks if DirectDraw is available. Return TRUE or FALSE
//
//static zBOOL Direct3DCheck()
//{
//	ENTER_PROC(Direct3DCheck);
//
//	// Find Check if we can get an IDirect3D2 interface from DirectDraw
//	if ((dd == NULL) ||
//		(IDirectDraw_QueryInterface(dd, &IID_IDirect3D2, &d3d) != DD_OK))
//	if ((dd7 == NULL) ||
//		(IDirectDraw7_QueryInterface(dd7, IID_IDirect3D7, (void**)&d3d7) != DD_OK))
//	{
//		TRACE("VID:     Direct3D7 not found - Disabled");			// Can't do
//		RETURN(FALSE);
//	}
//
//	// Show Direct3D info
//	TRACE("VID:     Direct3D7 found");
//
//	RETURN(TRUE);
//}

/***********************************************************************************\
**																				   **
**								   DIBSection code								   **
**																				   **
\***********************************************************************************/

//
// Normal DirectDraw Blit Copy
//
static zBOOL FASTCALL DIBSection_BLIT_COPY(LPBLIT_CMD pBlit)
{
	HPALETTE OldPal;												// Old palette for restore
	RECT	cRect;													// Client rectangle
	HDC 	winDC;													// App Window device context
	
	ENTER_PROC(DIBSection_BLIT_COPY);
	
	// We can only do BLIT_COPY to a DIB
	ASSERTT(pBlit->Command == BLIT_COPY, "You can only use BLIT_COPY to simple modes");
	
	// Select palette
	winDC=GetDC(hWndApp);											// Main app's DC
	SaveDC(winDC);
	OldPal=SelectPalette(winDC, winDIBPal, FALSE);					// Select our new palette in HDC
	SelectObject(winDC, GetStockObject(HOLLOW_BRUSH));				// Select hollow brush
	SelectObject(winDC, GetStockObject(BLACK_PEN)); 				// Select black pen
	RealizePalette(winDC);											// And Realize it!
	
	// Get update area size and adjust for border
	GetClientRect(hWndApp, &cRect); 								// Size of client window
	cRect.right--; cRect.bottom--;									// A little less please
	
	// Blit
	StretchBlt(winDC, 0, 0, cRect.right, cRect.bottom, winDIBDC, 0, 0, VideoW, VideoH, SRCCOPY);
	
	// Draw black rectangle around image
	Rectangle(winDC, cRect.left-1, cRect.top-1, cRect.right+1, cRect.bottom+1);
	
	// Select old stuff into DC
	RestoreDC(winDC, -1);											// Restore DC state
	SelectPalette(winDC, OldPal, FALSE);							// Re-select old palette in DC
	ReleaseDC(hWndApp, winDC);										// Release DC
	
	RETURN(TRUE);
}

//
// Add all DIBSection "video modes" to the list pModes and update nModes
//
static void DIBSectionEnumModes(LPCFUNCP Filter, zDWORD *WinSizes)
{
	VIDMODE WinEntry;												// Windowed video mode entry
	int   i; 														// Window sizes+window modes
	ENTER_PROC(DIBSectionEnumModes);
	
	// Add windowed modes
	memZero(&WinEntry, sizeof(WinEntry));							// Clear entry
	WinEntry.hwModeType    = VIDMODE_DIB;							// Windowed video mode
	WinEntry.AccessMode    = VAM_SIMPLE; 							// Only dumb video port
	WinEntry.VidMemBuffers = 0;										// No video buffers
	WinEntry.SysMemBuffers = 0;										// Set to 0 (default)
	for (WinEntry.si.BPP=8; WinEntry.si.BPP<=32; WinEntry.si.BPP*=2)// Try all bit depths
	{
		// Go through all window sizes and add modes to list
		for (i=0; WinSizes[i]!=0; i++) 								// Go through window sizes
		{
			// Fill entry variables (width and height)
			WinEntry.si.Width  = LOWORD(WinSizes[i]);				// Width of mode
			WinEntry.si.Height = HIWORD(WinSizes[i]);				// Height of mode
			if (Filter(&WinEntry)) vidAddMode(&WinEntry);			// Add entry
		}
	}

	EXIT_PROC();
}

//
// Init DIBSection
//
static void DIBSectionInit(LPVIDMODE NewMode)
{
	LPBITMAPINFO  pCT;												  // -> Bitmap info structure
	RGBQUAD *RC;													  // -> Color table
	zLONG	i, PalMode=DIB_RGB_COLORS;								  // Set dependant of the amount of colours
	zDWORD	dibPitch, dibSize;										  // Size of DIB line
	LPBYTE	dibDataBase=NULL;										  // -> DIB Pixels
	LPWORD	OTO;													  // For creating 1-to-1 table
	LPDWORD pBitFields; 											  // -> RGB Bit masks
	
	ENTER_PROC(DIBSectionInit);
	
	ASSERT(NewMode->SysMemBuffers >= 1);							  // Must have buffers
	
	// Prepare bitmap header for a CreateDIBSection call. We don't set up the colour to a 1 to 1 colour table yet. If the
	// current display is RealColour we don't want one as RealColour devices don't have a colour table anyway.
	pCT=(LPBITMAPINFO)winDIBSpace;									  // -> BitmapInfoHeader
	pBitFields=(LPDWORD)((LPBYTE)pCT+sizeof(BITMAPINFOHEADER)); 	  // -> Bitfields
	memZero(pCT, sizeof(BITMAPINFOHEADER)); 						  // Set all values to 0
	pCT->bmiHeader.biSize=sizeof(BITMAPINFOHEADER); 				  // Size of structure
	pCT->bmiHeader.biWidth=(NewMode->si.Width+3) & ~3;				  // Width
	pCT->bmiHeader.biHeight=-(zLONG)NewMode->si.Height*NewMode->SysMemBuffers; // Top-down x-buffering
	pCT->bmiHeader.biPlanes=1;										  // Linear adressing
	pCT->bmiHeader.biBitCount=(WORD)NewMode->si.BPP;				  // Bits per pixel
	pCT->bmiHeader.biCompression=BI_RGB;							  // No compression, RGB values
	dibPitch=((NewMode->si.Width+3) & (~3))*NewMode->si.BPP/8;		  // Pitch for bitmap
	dibSize=dibPitch*NewMode->si.Height;							  // Size of each buffer
	
	// Check for bit depth specific (palette/rgb masks) stuff
	if (NewMode->si.BPP == 8)
	{
		// Create a one-to-one color table or one with color values in it
		if (GetDeviceCaps(dcScreen, BITSPIXEL)==8)						// Windows running in 8 bit mode?
		{
			// Windows is running in 8 bit mode, do an identity palette
			OTO=(LPWORD)((LPBYTE)pCT+sizeof(BITMAPINFOHEADER)); 		  // -> One-2-One color table
			PalMode=DIB_PAL_COLORS; 									  // Palette mode
			for (i=0; i<256; i++) *OTO++=(zUWORD)i;						  // HDC(x) maps to Screen(x)
		}
		else
		{
			RC=(RGBQUAD *)((LPBYTE)pCT+sizeof(BITMAPINFOHEADER));		  // -> RGB table
			for (i=0; i<256; i++)
			{
				RC->rgbRed	 = vidWinPal.palPalEntry[i].peRed;
				RC->rgbGreen = vidWinPal.palPalEntry[i].peGreen;
				RC->rgbBlue  = vidWinPal.palPalEntry[i].peBlue;
				RC->rgbReserved=0;
				RC++;
			}
		}
	}
	else if (NewMode->si.BPP > 8)
	{
		zBOOL	bitDepth=(NewMode->si.BPP/16)-1;					// 0=16, 1=32
		zDWORD	stdRGBMask[2][3]={ { 0xf800, 0x7e0, 0x1f }, { 0xff0000, 0xff00, 0xff } };

		ASSERT(NewMode->si.rgbMasksValid == FALSE); 				// RGB may not be set

		// If this is a high color mode, set RGB masks
		VideoHwModeCur.si.rgbMasksValid=TRUE;						// RGB masks are valid
		VideoHwModeCur.si.rgbRMask=stdRGBMask[bitDepth][0]; 		// Red color mask
		VideoHwModeCur.si.rgbGMask=stdRGBMask[bitDepth][1]; 		// Green color mask
		VideoHwModeCur.si.rgbBMask=stdRGBMask[bitDepth][2]; 		// Blue color mask
		pCT->bmiHeader.biCompression=BI_BITFIELDS;					// Set RGB Masks
		pBitFields[0]=stdRGBMask[bitDepth][0];						// Red Mask
		pBitFields[1]=stdRGBMask[bitDepth][1];						// Green Mask
		pBitFields[2]=stdRGBMask[bitDepth][2];						// Blue Mask
	}
	else ASSERT(FALSE);
	
	// Create a DC to go with the DIB
	ASSERT(winDIBDC==NULL); 										// No leftovers
	if (winDIBDC) DeleteDC(winDIBDC);								// Remove old
	winDIBDC=CreateCompatibleDC(NULL);								// Create screen-compatible DC
	
	// Create a DIB section, note that the palette has to be selected into the device context whereof the Hdc is passed to the
	// CreateDIBSection() call to function properly. This is because the CreateDIBSection uses a one-to-one color table in
	// 256 color modes. This will map the palette colors to those in the hdc.
	if (NewMode->si.BPP==8)
	{
		if (winDIBPal==NULL) winDIBPal=CreatePalette((LPLOGPALETTE)&vidWinPal);// If no palette -> Create new palette
		SelectPalette(winDIBDC, winDIBPal, FALSE);					// Select our new palette in HDC
		RealizePalette(winDIBDC);									// And Realize it!
	}
	
	// Create da DIB
	winDIBSection=CreateDIBSection(winDIBDC, pCT, PalMode, (LPVOID *)&dibDataBase, NULL, 0);
	if (winDIBSection==NULL) sysHardExit("Could not create DIBSection");
	memZero(dibDataBase, dibSize*NewMode->SysMemBuffers);			// Wipe DIB
	SelectObject(winDIBDC, winDIBSection);							// Select DIBSection into DC
	
	// Create vidSysBufs[x] (backbuffers) that occupy the DIB space
	for (i=0; i<NewMode->SysMemBuffers; i++)
	{
		ASSERT(vidSysBufs[i]==NULL);									// Can't have leftovers
		vidSysBufs[i]=(LPSURFACE)sysAlloc(sizeof(SURFACE)); 			// Allocate memory for surface
		memcpy(&vidSysBufs[i]->si, &NewMode->si, sizeof(SURFACE_INFO));// Clone surface info
		vidSysBufs[i]->si.MemType=VIDMEM_SYSTEM;						// Create system memory surfac
		vidSysBufs[i]->Ptr=NULL;										// No pointer
		vidSysBufs[i]->Pitch=0; 										// No pitch
		vidSysBufs[i]->APISpecific[API_MODE]=VIDMODE_DIB;				// DIB Backbuffer
		vidSysBufs[i]->APISpecific[API_PTR]=(zDWORD)dibDataBase+(i*dibSize); // -> Data area
		vidSysBufs[i]->APISpecific[API_PITCH]=dibPitch; 				// Set DIB pitch
		vidLL_AddSurface(vidSysBufs[i]);								// Add surface to linked list
	}
	
	// Create a dummy vidVidBufs[0] (frontbuffer) to service as destination for blitting
	ASSERT(vidVidBufs[0] == NULL);									  // No display when we're initialising!
	vidVidBufs[0]=(LPSURFACE)sysAlloc(sizeof(SURFACE)); 			  // Allocate memory for surface
	memcpy(&vidVidBufs[0]->si, &NewMode->si, sizeof(SURFACE_INFO));  // Clone surface info
	vidVidBufs[0]->si.MemType=VIDMEM_VIDEO; 						  // Create Video memory surfac
	vidVidBufs[0]->Ptr=NULL;										  // No pointer
	vidVidBufs[0]->Pitch=0; 										  // No pitch
	vidVidBufs[0]->APISpecific[API_MODE]=VIDMODE_DIB;				  // DIB Frontbuffer
	vidVidBufs[0]->APISpecific[API_PTR]=0xDEADBEAF; 				  // Frontbuffer marker
	vidLL_AddSurface(vidVidBufs[0]);								  // Add surface to linked list
	
	// Set blitters
	vidSetSwBlitters(); 											  // Install software blitters
	vidSimpleBlitFunc=DIBSection_BLIT_COPY; 						  // Install DIBsection blitter
	
	EXIT_PROC();
}

//
// Exit DIBSection display mode
//
void DIBSectionExit()
{
	ENTER_PROC(DIBSectionExit);
	
	// When we have a DIBSection, remove it and assign it a NULL pointer
	if (winDIBSection)
	{
		if (winDIBSection)	DeleteObject(winDIBSection);			// Delete DIB Section
		if (winDIBPal)		DeleteObject(winDIBPal);				// Delete DIB Palette
		if (winDIBDC)		DeleteDC(winDIBDC); 					// Delete DIB Device context
		
		winDIBSection=NULL;
		winDIBPal=NULL;
		winDIBDC=NULL;													
	}
	
	EXIT_PROC();
}

//
// Set palette from WinPal to DIBSection
//
static void DIBSectionSetPalette()
{
	HPALETTE	oldPal; 											// Old palette from DC
	RGBQUAD dibPal[256];											// DIB palette
	zDWORD	i;														// Counter
	ENTER_PROC(DIBSectionSetPalette);

	// Recreate the DIB palette with the new palette and select palette into DC
	SelectPalette(winDIBDC, NULL, TRUE);							// Unselect palette
	if (winDIBPal) DeleteObject(winDIBPal); 						// Remove old
	winDIBPal=CreatePalette((LPLOGPALETTE)&vidWinPal);				// Create new palette
	oldPal=SelectPalette(winDIBDC, winDIBPal, FALSE);				// Select our new palette in HDC
	RealizePalette(winDIBDC);										// And Realize it!
	SelectPalette(winDIBDC, oldPal, TRUE);							// Restore DC state

	// Create DIB color table and set it for the bitmap
	for (i=0; i<256; i++)											// Colours to copy
	{
		dibPal[i].rgbRed	  = vidWinPal.palPalEntry[i].peRed;
		dibPal[i].rgbGreen	  = vidWinPal.palPalEntry[i].peGreen;
		dibPal[i].rgbBlue	  = vidWinPal.palPalEntry[i].peBlue;
		dibPal[i].rgbReserved = 0;
	}
	SetDIBColorTable(winDIBDC, 0, 256, dibPal); 					// Set palette

	EXIT_PROC();
}


// Halftoning/dithering stuff
static	void	Dither32BPPBitmap(CUSTOMCAPTION *cap, zLONG Height, zLONG YOfs);	// Dither 32BPP bitmap to 16BPP
static	zBYTE	Halftone8x8[64] = { 0,	11, 2,	14, 0,	12, 3,	15,
									7,	3,	10, 6,	8,	4,	11, 7,
									1,	13, 0,	12, 2,	14, 1,	12,
									9,	5,	8,	4,	10, 6,	9,	5,
									0,	11, 3,	14, 0,	11, 3,	14,
									8,	4,	10, 6,	7,	3,	10, 6,
									2,	13, 1,	12, 2,	13, 0,	12,
									9,	6,	9,	5,	9,	5,	8,	4 };

//
// Our overridden caption drawer for <wnd>
//
void ccDrawCaption(HWND wnd, CUSTOMCAPTION *cap, zBOOL Active, HRGN Clip)
{
	NONCLIENTMETRICS  nc;											// NonClient sizes
	RECT	CaptionRect;											// Rectangle for caption
	POINT	WindowPoint;											// Left-upper coordinate of window
	zLONG	BorderSize=3;											// Size of border
	HDC 	hdc;													// Device context for window
	
	// Check if window is visible
	if (!IsWindowVisible(wnd)) return;								// Not visible, return!
	if (IsIconic(wnd)) return;										// Iconic, return!
	
	// Get size of window and extract caption space
	nc.cbSize=sizeof(NONCLIENTMETRICS); 							// Fill in size of structure
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &nc, 0);		// Read non-client sizes
	
	if (GetWindowRect(wnd, &CaptionRect)==FALSE) return;			// Get size of window
	WindowPoint.x=CaptionRect.left;
	WindowPoint.y=CaptionRect.top;
	
	// Check caption area
	if (cap->bSizeBorder) BorderSize+=nc.iBorderWidth;				// Width of sizing border
	CaptionRect.top+=BorderSize;									// Top of caption
	CaptionRect.left+=BorderSize;									// Left of caption
	CaptionRect.bottom=CaptionRect.top+nc.iCaptionHeight;			// Bottom of caption
	CaptionRect.right-=BorderSize;									// Right side of caption
	
	// Convert to window coordinates to coordinates relative to window's non-client area
	OffsetRect(&CaptionRect, -WindowPoint.x, -WindowPoint.y);		// Relative to upper-left corner
	
	// Paint it
	hdc=GetWindowDC(wnd);											// Get non-client area
	
	if (Clip)
	{
		SelectClipRgn(hdc, Clip);
		OffsetClipRgn(hdc, -WindowPoint.x, -WindowPoint.y);
	}
	
	BitBlt(hdc, CaptionRect.left, CaptionRect.top, CaptionRect.right-CaptionRect.left, CaptionRect.bottom-CaptionRect.top, cap->hDC, 0, (Active!=0)*nc.iCaptionHeight, SRCCOPY);
	
	// Set new clipping area
	if (Clip)
	{
		ExcludeClipRect(hdc, CaptionRect.left, CaptionRect.top, CaptionRect.right, CaptionRect.bottom);
		OffsetClipRgn(hdc, WindowPoint.x, WindowPoint.y);			// Reset to normal coordinates
		GetClipRgn(hdc, Clip);										// Get new clipping region
	}
	
	ReleaseDC(wnd, hdc);											// Release window DC
	return;
}

//
// Render active and inactive caption
//
void ccRenderCaption(HWND hwnd, CUSTOMCAPTION *cap)
{
	NONCLIENTMETRICS  nc;											// NonClient sizes
	BITMAPINFO	TempBmp;											// Bitmap for caption
	COLORREF  CaptionCol[2], CaptionTextCol[2]; 					// Caption colors
	COLORREF  CurCol;												// Current color
	HFONT	CaptionFont;											// Font for caption
	HFONT	OldFont;												// Old font
	LONG	i, j, k, l, m;											// Counters
	LONG	IconMax;												// Icon to maximize or restore
	zBYTE*	p;
	zBYTE*  src; 												// Just a pointer
	LPDWORD pixels; 												// DWORD pixel pointer
	CHAR	CaptionText[256];										// Program title in caption
	RECT	CaptionRect;											// Size of caption
	LONG	CaptionFontAddY;										// Y-Adder for caption font
	LONG	CaptionButtons; 										// Amount of buttons on caption
	LONG	CaptionBPL; 											// Width of line in caption
	LONG	BorderSize=3;											// Size of border
	LONG	ColIntensity, ColMul;									// Intensity of color and color multiplier
	RECT	IconRect;												// Rectangle used for drawing small icons on caption
	HDC 	hdcWin; 												// Device context for window
	
	// Get system colors and sizes
	CaptionCol[0]=GetSysColor(COLOR_INACTIVECAPTION);				// Inactive caption color
	CaptionCol[1]=GetSysColor(COLOR_ACTIVECAPTION); 				// Active caption color
	CaptionTextCol[0]=GetSysColor(COLOR_INACTIVECAPTIONTEXT);		// Inactive caption text color
	CaptionTextCol[1]=GetSysColor(COLOR_CAPTIONTEXT);				// Active caption text color
	
	// Brighten caption colors enough so they will make some contrast with the black fade in the background
	for (i=0; i<2; i++) 											// 2 Caption colos
	{
		if (CaptionTextCol[i]==0x000000) CaptionTextCol[i]=0xFFFFFF;	// Black text -> white text (black = invisible)
		ColIntensity=14471*(CaptionTextCol[i] & 0xFF)+35470*((CaptionTextCol[i] >> 8) & 0xFF)+17595*((CaptionTextCol[i] >> 16) & 0xFF);
		if (ColIntensity<0x300000)
		{
			ColMul=0x30000000/ColIntensity; 						// Color multiplier for intensity
			CaptionTextCol[i]=(CaptionTextCol[i] & 0xFFFF00) | (__min(255,((CaptionTextCol[i]>>0x00) & 0xFF)*ColMul/256) << 0x00);
			CaptionTextCol[i]=(CaptionTextCol[i] & 0xFF00FF) | (__min(255,((CaptionTextCol[i]>>0x08) & 0xFF)*ColMul/256) << 0x08);
			CaptionTextCol[i]=(CaptionTextCol[i] & 0x00FFFF) | (__min(255,((CaptionTextCol[i]>>0x10) & 0xFF)*ColMul/256) << 0x10);
			//Y' = 0.299 * Rprime + 0.587 * Gprime + 0.114 * Bprime;
		}
	}
	
	nc.cbSize=sizeof(NONCLIENTMETRICS); 							// Fill in size of structure
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &nc, 0);		// Read non-client sizes
	
	// Assume we can't use this caption and check for color depth
	cap->bActive=FALSE; 											// Assume not active
	if (winBPP==8) return;											// 256 Color -> Don't render caption
	
	// If there's a caption, remove the old one
	hdcWin=GetDC(hwnd);
	if (cap->hDC)
	{
		DeleteDC(cap->hDC); 										// Remove old caption
		DeleteObject(cap->hBmp);									// Bitmap for caption
	}
	
	// Calculate amount of buttons on caption
	CaptionButtons=0;												// Assume no buttons
	if (cap->iButtons & 1) CaptionButtons++;						// Got one!
	if (cap->iButtons & 2) CaptionButtons++;						// Got another!
	if (cap->iButtons & 4) CaptionButtons++;						// Got third!
	
	// Get size of window and extract caption space
	if (cap->bSizeBorder) BorderSize+=nc.iBorderWidth;				// Width of sizing border
	if (GetWindowRect(hwnd, &CaptionRect)==FALSE) return;			// Get size of window
	OffsetRect(&CaptionRect, -CaptionRect.left, -CaptionRect.top);	// Relative to upper-left corner
	CaptionRect.bottom=nc.iCaptionHeight;							// Bottom is just height of caption
	CaptionRect.right-=BorderSize*2;								// Substract frame on both sides
	
	// Fill in header for caption DIBSection
	cap->iWidth=(CaptionRect.right+3) & (0xFFFFFFFF ^ 3);			// Width of caption on DWORD align
	CaptionBPL=cap->iWidth*4;										// Width of line (in zBYTEs)
	memset(&TempBmp, 0, sizeof(BITMAPINFO));						// Wipe out bitmap info
	TempBmp.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);				// Fill size of header
	TempBmp.bmiHeader.biWidth=cap->iWidth;							// Fill width of header
	TempBmp.bmiHeader.biHeight=(nc.iCaptionHeight*-2)-1;			// Fill height
	TempBmp.bmiHeader.biPlanes=1;									// Always 1 plane
	TempBmp.bmiHeader.biBitCount=32;								// Use realcolor bitmap
	TempBmp.bmiHeader.biCompression=BI_RGB; 						// Uncompressed & no bitfields
	
	// Create new caption device context and bitmap for our temporary drawing in RealColor
	cap->hDC=CreateCompatibleDC(hdcWin);
	cap->hBmp=CreateDIBSection(hdcWin, &TempBmp, DIB_PAL_COLORS, (void**)&cap->bmpData, NULL, 0); // Create DIB section for caption
	SelectObject(cap->hDC, cap->hBmp);								// Select bitmap drawing caption
	
	// Release window's device context, we're done with it
	ReleaseDC(hwnd, hdcWin);
	
	// Create font for caption
	nc.lfCaptionFont.lfQuality=ANTIALIASED_QUALITY; 				// Want that high quality!
	nc.lfCaptionFont.lfOutPrecision=OUT_TT_PRECIS;					// Precise please!
	CaptionFont=CreateFontIndirect(&nc.lfCaptionFont);				// Create caption font
	CaptionFontAddY=(nc.iCaptionHeight+nc.lfCaptionFont.lfHeight)/2-nc.iCaptionHeight/20;// Adder for centering
	OldFont=(HFONT)SelectObject(cap->hDC, GetStockObject(SYSTEM_FONT));	// Just select a font to retrieve old
	
	// Draw gradient in captions
	for (j=0; j<2; j++)
	{
		// We have a DC and a bitmap with two captions on top of each other, blit to either upper or lower caption
		CaptionRect.top=nc.iCaptionHeight*j;
		CaptionRect.bottom=nc.iCaptionHeight*(j+1);
		
		// Draw gradiented or bitmapped background for caption
		p=cap->bmpData+(j*nc.iCaptionHeight*cap->iWidth)*4; 		// Make pointer to caption data
		if (cap->bmpBackground)
			CurCol=0xFFFFFF;										// Background bitmap -> Mutlipliers
		else
			CurCol=CaptionCol[j];									// Get caption color
		
		// ASM loop for gradient drawing (for speed, using brushes or C for this is soooo slow!)
		p+=2;														// Begin with 'lowest' zBYTE
		for (i=0; i<3; i++) __asm
		{
			// Prepare fractional adders:
			//	  ESI = INT Step	  EAX = INT Count
			//	  EBX = FRAC Step ECX = FRAC Count
			mov   eax,[CurCol]										// Get current color
				mov   edx,eax										// Save CurCol
				and   eax,0xFF										// Keep only current component
				push  eax											// Save full color (need it later)
				shr   edx,8 										// Use next component next time
				mov   [CurCol],edx									// Save new component in place
				// We need: Component/Width in fractional steps
				shl   eax,16										// EAX = 16bits stip
				xor   edx,edx										// EDX:EAX = Number
				mov   ebx,[nc.iCaptionWidth]						// Width of one icon
				imul  ebx,[CaptionButtons]							// Amount of buttons on caption
				neg   ebx
				add   ebx,[CaptionRect.right]						// Width of caption (=Size of caption - 3 icons)
				push  ebx											// Save width to do
				div   ebx											// EAX = INT Step, EDX = Rest
				mov   ebx,eax										// Save FRAC step
				mov   esi,eax										// Save INT step
				shl   ebx,16										// Bring FRAC step to upper bits
				shr   esi,16										// Bring INT step to lower bits
				// Set counters for FRAC and INT to 0
				xor   ecx,ecx										// No fractional count
				xor   eax,eax										// No integer count
				// Prepare destination
				mov   edi,[p]										// Base pointer
				dec   [p]											// Next time take last component
				pop   edx											// Width to do
				
				// Main loop, fixed point gradient adder
ILoop:
			add   ecx,ebx											// Fractional add
				adc   eax,esi										// AL is color
				add   edi,4 										// Pre-increase pointer (for pipes)
				dec   edx											// Decrease counter
				mov   [edi],al										// Put pixel
				jg	  ILoop 										// Loop!
				
				// Draw a small part in the normal color (filled)
				mov   edx,[nc.iCaptionWidth]						// Width of an icon
				pop   eax											// Restore saved color
				imul  edx,[CaptionButtons]							// Amount of buttons on caption
				add   edx,4 										// 4 Extra pixels (for gradient)
				
				// Inner loop for normal fill (slow)
FLoop:
			add   edi,4 											// Next destination
				dec   edx											// Did a line
				mov   [edi],al										// Store pixel component
				jg	  FLoop 										// Until done
		}

		// Copy the single line we rendered to all other lines in this caption
		for (i=1; i<nc.iCaptionHeight; i++) memcpy(cap->bmpData+((j*nc.iCaptionHeight+i)*cap->iWidth)*4, cap->bmpData+(j*nc.iCaptionHeight*cap->iWidth)*4, CaptionBPL);
		
		// Show icons for buttons
		SetBkMode(cap->hDC, TRANSPARENT);							// Set background to transparent
		
		// Show program name in caption
		SelectObject(cap->hDC, CaptionFont);						// Just select a font to retrieve old
		SetTextColor(cap->hDC, (COLORREF)0);						// Shadow
		GetWindowText(hwnd, CaptionText, 256);						// Get caption text
		TextOut(cap->hDC, ((cap->hIcon != NULL)*nc.iCaptionWidth)+4, CaptionRect.top+CaptionFontAddY, CaptionText, strlen(CaptionText));
		
		// Blur for shadow
		pixels=(LPDWORD)cap->bmpData+(j*nc.iCaptionHeight)*cap->iWidth; // Make pointer to caption data
		if (cap->bmpBackground) 									// On background -> more shadow
			for (k=0; k<cap->iWidth-1; k++) pixels[k]=0x3F3F3F; 	// Pretty dark (-> 3D effect)
		else
			for (k=0; k<cap->iWidth-1; k++) pixels[k]=(pixels[k]>>1) & 0x7F7F7F; // Darken top-line for 3D-effect
				
		p=(zBYTE*)pixels;											// Now need zBYTE pointer
		for (i=1; i<nc.iCaptionHeight; i++)
		{
			p+=cap->iWidth*4;										// Pointer to next line
			for (l=0; l<3; l++) 									// Go through Red, Green or Blue plane
				for (k=4+l; k<(cap->iWidth*4+l); k+=4)				// Go through pixels
					p[k]=(p[k]+p[k-4]+p[k-CaptionBPL]+p[k-4-CaptionBPL])/4; 	  // Take 4 pixels and average
		}
				
		// Now, if we have a bimapped background, shade it with the shade made we just created
		if (cap->bmpBackground) 									// Background bitmap?
		{
			// Bitmapped background
			for (i=0; i<nc.iCaptionHeight; i++) 					// Go through all lines
			{
				p=cap->bmpData+((j*nc.iCaptionHeight+i)*cap->iWidth)*4; // Make pointer to caption data
				src=cap->bmpBackground+(i & 31)*cap->bmpWidth*4;		// Make pointer to background line
				for (k=0; k<cap->iWidth; k+=cap->bmpWidth)
				{
					l=__min(cap->iWidth-k, (LONG)cap->bmpWidth);	// Amount of pixels to do
					for (m=0; m<l; m++) 							// Go through all pixels
					{
						if (j)
							p[0]=(src[m*4]*p[0]) >> 9;
						else
							p[0]=(src[m*4]*p[0]) >> 8;
						p[1]=(src[m*4+1]*p[1]) >> 8;
						p[2]=(src[m*4+2]*p[2]) >> 8;
						p+=4;										// Next pixel
					}
				}
			}
		}
		
		// Put text on top of it
		SetTextColor(cap->hDC, CaptionTextCol[j]);					// Set color for text
		TextOut(cap->hDC, ((cap->hIcon != NULL)*nc.iCaptionWidth)+3, CaptionRect.top+CaptionFontAddY-1, CaptionText, strlen(CaptionText));
		
		// Dither bitmap (before putting icons on top of it)
		if (winBPP<24) Dither32BPPBitmap(cap, nc.iCaptionHeight, nc.iCaptionHeight*j);	// Dither when in HighColor
		
		// Prepare caption icons (buttons)
		IconRect.top=CaptionRect.top+2;
		IconRect.bottom=CaptionRect.top+nc.iCaptionHeight-2;
		IconRect.left=CaptionRect.right-nc.iCaptionWidth;
		IconRect.right=CaptionRect.right-2;
		if (cap->iButtons & 1) DrawFrameControl(cap->hDC, &IconRect, DFC_CAPTION, DFCS_CAPTIONCLOSE);
		IconRect.left-=nc.iCaptionWidth;
		IconRect.right-=nc.iCaptionWidth;
		IconMax=DFCS_CAPTIONMAX;
		if (IsZoomed(hwnd)) IconMax=DFCS_CAPTIONRESTORE;
		if (cap->iButtons & 2) DrawFrameControl(cap->hDC, &IconRect, DFC_CAPTION, IconMax);
		IconRect.left-=nc.iCaptionWidth-2;
		IconRect.right-=nc.iCaptionWidth-2;
		if (cap->iButtons & 4) DrawFrameControl(cap->hDC, &IconRect, DFC_CAPTION, DFCS_CAPTIONMIN);
		
		// Draw icon
		if (cap->hIcon) DrawIconEx(cap->hDC, 1, CaptionRect.top+1, cap->hIcon, nc.iCaptionWidth-2, nc.iCaptionHeight-2, 0, NULL, DI_NORMAL);
	}

	// Release objects and device contexts
	SelectObject(cap->hDC, OldFont);
	DeleteObject(CaptionFont);
	cap->bActive=TRUE;												// We're here, so everything was ok

	// Post re-paint message to window to indicate change
	PostMessage(hwnd, WM_NCPAINT, 1, 0);								// Re-paint non-client area
}


//
// Dither a 32-bit bitmap to 15 bits to make the gradient look smoother
//
static void Dither32BPPBitmap(CUSTOMCAPTION *cap, zLONG Height, zLONG YOfs)
{
	static	zBOOL	LUTGen=FALSE;									  // LUT's generated?
	static	zBYTE	Rnd17[256], Mod17[256], Mul17[16];				  // Lookup Tables
	zBYTE	R, G, B;												  // RGB Values
	zBYTE*	bmpPtr;
	zBYTE*  htPtr;													  // -> Bitmap, -> Halftone matrix
	zLONG	x, y, i, rx, ry;										  // Pixel Counters
	
	// Create pointer to bitmap
	bmpPtr=cap->bmpData+YOfs*cap->iWidth*4; 						  // Get to right offset
	
	// Create look-up tables
	if (LUTGen==FALSE)
	{
		zBYTE t, j;
		for (i=t=j=0; i<256; i++) { Rnd17[i]=t; j++; if (j==17) { j=0; t+=17; } } // Create Round(i,17)
		for (i=t=0; i<256; i++)   { Mod17[i]=t; t++; if (t==17) t=0; }	// Create i MOD 17
		for (i=t=0; i<16; i++)	  { Mul17[i]=t; t+=17; }				// Create i*17
		LUTGen=TRUE;													// Generated now
	}
	
	// Step through, converting each pixel in each scan lineto the nearest halftone match
	for (y=0, ry=0; y<Height; y++)
	{
		x=0;															// We're at the left side!
		htPtr=&Halftone8x8[ry]; 										// Set halftone matrix pointer
		while (x<cap->iWidth)
		{
			// Long run dithering routine (normal)
			while (cap->iWidth-x>=8)
			{
				for (i=0; i<8; i++)
				{
					// Dither pixel
					R=bmpPtr[0]; G=bmpPtr[1]; B=bmpPtr[2];
					bmpPtr[0] = Rnd17[R] + (Mod17[R] > *htPtr ? 17 : 0);	  // Dither red
					bmpPtr[1] = Rnd17[G] + (Mod17[G] > *htPtr ? 17 : 0);	  // Dither green
					bmpPtr[2] = Rnd17[B] + (Mod17[B] > *htPtr ? 17 : 0);	  // Dither blue
					bmpPtr+=4; htPtr++; 									  // Next 'reduced' x
				}
				htPtr-=8;													// Undo 8 pixel steps
				x+=8;														// Did some x
			}
			
			for (rx=0; x<cap->iWidth; x++)
			{
				// Get RGB values
				R=bmpPtr[0]; G=bmpPtr[1]; B=bmpPtr[2];
				bmpPtr[0] = Rnd17[R] + (Mod17[R] > htPtr[rx] ? 17 : 0);
				bmpPtr[1] = Rnd17[G] + (Mod17[G] > htPtr[rx] ? 17 : 0);
				bmpPtr[2] = Rnd17[B] + (Mod17[B] > htPtr[rx] ? 17 : 0);
				x++; rx++; bmpPtr+=4;										// Next 'reduced' x
			}
			
		}
		ry+=8; ry&=63;													// Next 'reduced' y
	}
}
