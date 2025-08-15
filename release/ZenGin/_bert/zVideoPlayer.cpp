/******************************************************************************** 
 
     $Workfile:: zvideoplayer.cpp     $                $Date:: 25.10.00 21:07   $
     $Revision:: 8                    $             $Modtime:: 24.10.00 15:35   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
 
   Attention: 
 
 *********************************************************************************/

#include "zcore.h"
#include "zvideoplayer.h"

zCVideoPlayer::zCVideoPlayer()
{	
	mPaused		= FALSE;
	mPlaying	= FALSE;
	mLooping	= FALSE;	
	mSoundOn	= TRUE;
	mSoundVolume= 1;	
	mScaleValue	= 1;
};

zCVideoPlayer::~zCVideoPlayer()
{
};

zBOOL zCVideoPlayer::OpenVideo(zSTRING filename)
{
	if (IsPlaying())
	{
		zERR_FAULT("B: VP: Can't open a video: Another video is still playing!");
		return FALSE;
	};
		
	mVideoFilename	= filename;
	mPaused		= FALSE;
	mPlaying	= FALSE;
	return TRUE;
};

zBOOL zCVideoPlayer::CloseVideo()
{
	if (IsPlaying())
	{
		zERR_FAULT("B: VP: Can't close video: It's still playing!");
		return FALSE;
	};	
	mPaused		= FALSE;
	mPlaying	= FALSE;
	return TRUE;
};

zBOOL zCVideoPlayer::Play(int frameNr)
{
	zerr.Separator();
	PlayInit(frameNr);	
	while (IsPlaying())
	{
		PlayFrame();		
	};
	PlayDeinit();
	zerr.Separator();	
	return TRUE;
};


zBOOL zCVideoPlayer::PlayInit(int frameNr)
{
	mPaused		= FALSE;		
	mPlaying	= TRUE;	
	return TRUE;
};

zBOOL zCVideoPlayer::PlayGotoNextFrame()
{	
	return TRUE;
};

zBOOL zCVideoPlayer::PlayWaitNextFrame()
{
	return TRUE;
};
	

zBOOL zCVideoPlayer::PlayFrame()
{
	return FALSE;	// did not draw a frame
};

zBOOL zCVideoPlayer::PlayDeinit()
{
	mPaused		= FALSE;		
	mPlaying	= FALSE;
	return TRUE;
};

zBOOL zCVideoPlayer::Pause()
{
	if (!mPlaying)	return FALSE;	// Could not pause a not playing video	
	if (mPaused)	return FALSE;	// Could pause a paused video again
	mPaused=TRUE;
	return TRUE;
};

zBOOL zCVideoPlayer::Unpause()
{
	if (!mPlaying)	return FALSE;	// Could not unpause a not playing video	
	mPaused=FALSE;
	return TRUE;
};

zBOOL zCVideoPlayer::Stop()
{
	if (!mPlaying)	return FALSE;	// Could not stop a not playing video	
	mPlaying=FALSE;
	return TRUE;
};

