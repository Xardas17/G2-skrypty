/******************************************************************************** 
 
     $Workfile:: zbinkplayer.h        $                $Date:: 4.12.00 18:22    $
     $Revision:: 8                    $             $Modtime:: 4.12.00 18:20    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
  
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:20 $)

#ifndef __ZBINKPLAYER_H__
#define __ZBINKPLAYER_H__

#ifndef __ZVIDEOPLAYER_H__
#include "zvideoplayer.h"
#endif

#include "bink.h"

#ifndef __ZRENDERER_H__
#include "zrenderer.h"
#endif

class zCView;

class zCBinkPlayer : public zCVideoPlayer
{
public:
	zCBinkPlayer				();
	virtual ~zCBinkPlayer	();

	virtual zBOOL	OpenVideo	(zSTRING filename);	
	virtual zBOOL	CloseVideo	();
	
	virtual	zBOOL	PlayInit	(int frameNr = 0);	
	virtual zBOOL	PlayFrame	();			// handle current frame (call PlayGotoNextFrame before)
	virtual	zBOOL	PlayDeinit	();			// playing of video has finished
	virtual zBOOL	PlayHandleEvents();		// handle user-defined events (keyboard input)
		
	virtual zBOOL	ToggleSound	();
	virtual zREAL	SetSoundVolume(zREAL v);

	virtual zBOOL	IsPlaying	();
	virtual zBOOL	Pause		();
	virtual zBOOL	Unpause		();		

	void	EnableBlit(zBOOL blit) { mDoBlit = blit; };
	void	EnableEventHandler(zBOOL eh) { mDoHandleEvents = eh; };
	void	SetFullscreen(zBOOL full, zSTRING tex);

protected:

	virtual zBOOL	PlayGotoNextFrame();	// player switched to the next frame to be shown (call before each PlayFrame)
	virtual zBOOL	PlayWaitNextFrame();	// wait until the next frame could be started (call before GotoNextFrame)

	s32				GetPixelFormat(zTRndSurfaceDesc& sf);
	
protected:

	HBINK	mVideoHandle;	
	s32		mCopyMode;
	zINT	mXpos, mYpos;
	zBOOL	mDoBlit;
	zBOOL	mDoHandleEvents;
	zBOOL	mDoFullscreen;
	zSTRING	mBackTexture;
	zCView*	mBackView;	
	RECT	mSourceRect;
	RECT	mTargetRect;
};

#endif

