/******************************************************************************** 
 
     $Workfile:: zbinkplayer.cpp      $                $Date:: 14.03.01 19:10   $
     $Revision:: 22                   $             $Modtime:: 14.03.01 18:19   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
 
   Attention: 
 
 *********************************************************************************/

#include "zcore.h"
#include "zbinkplayer.h"
#include "zsndMss.h"
#include "zdisk.h"
#include "zoption.h"
#include "zview.h"
#include "zsndmss.h"
#include "zdisk.h"
#include "zmusic.h"


/*********************************************************************************
*	Bink Version
*********************************************************************************/

#if defined(BINKMAJORVERSION) && defined(BINKMAJORVERSION)

#if (BINKMAJORVERSION == 1) && (BINKMINORVERSION >= 5)
#define BINK_VERSION_15_UP
#elif (BINKMAJORVERSION > 1)
#define BINK_VERSION_15_UP
#endif

#endif


static bool s_firstBlit = true;

zCBinkPlayer::zCBinkPlayer()
{
	zERR_MESSAGE(3,0,"B: VP: Initialize zBinkPlayer");
	mVideoHandle	= 0;		
	mCopyMode		= -1;
	mXpos			= 0;
	mYpos			= 0;	
	mDoBlit			= TRUE;
	mDoHandleEvents	= TRUE;
	mDoFullscreen	= TRUE;	
	mBackView		= 0;		
};	

zCBinkPlayer::~zCBinkPlayer()
{	
	if (mVideoHandle!=0)
	{
		CloseVideo();
	};
	zERR_MESSAGE(3,0,"B: VP: zBinkPlayer deinitialized");
};

zBOOL zCBinkPlayer::OpenVideo(zSTRING filename)
{	
	//
	// Ermittlung des passenden Files
	//
	zFILE_FILE file(filename);
	if (file.GetExt().IsEmpty()) file.SetExt("BIK");
	if (!file.Exists()) 
	{		
		zERR_WARNING("B: VP: File \""+file.GetFile()+"\" does not exist.");
		return FALSE;
	}
	
	zERR_MESSAGE(4,zERR_BEGIN,"B: VP: Open Videofile: \""+file.GetFile()+"\"");

	//
	// Einzelne Werte initialisieren
	//
	if (dynamic_cast<zCSndSys_MSS*>(zsound))
	{
		HDIGDRIVER drv = static_cast<zCSndSys_MSS*>(zsound)->GetDigitalDriverHandle();
		if (drv!=0)
		{
			BinkSoundUseMiles(drv);		
			BinkSetSoundOnOff(mVideoHandle,1);
#ifdef BINK_VERSION_15_UP
			BinkSetVolume(mVideoHandle, 0, 65536);
#else
			BinkSetVolume(mVideoHandle, 65536);
#endif
		}
	}
	SetScaleValue(1);

	//
	// Basismethode
	//	

	filename = file.GetFullPath();	
	mVideoHandle = BinkOpen(filename.ToChar(),0);	
	
	if (mVideoHandle)
	{
		zCVideoPlayer::OpenVideo(filename);
		zERR_MESSAGE(4,0,"B: VP: Filesize: "+zSTRING(float(mVideoHandle->Size)/1024,2)+" kb");
		zERR_MESSAGE(4,0,"B: VP: Resolution: "+zSTRING(mVideoHandle->decompwidth)+"x"+zSTRING(mVideoHandle->decompheight));
		zERR_MESSAGE(4,0,"B: VP: Framecount: "+zSTRING(mVideoHandle->Frames));				
		zERR_MESSAGE(4,0,"B: VP: Framerate: "+zSTRING(mVideoHandle->fileframerate)+" fps");
		zERR_MESSAGE(4,0,"B: VP: Trackcount (Sound): "+zSTRING(mVideoHandle->NumTracks));						
	}
	else
	{		
		zERR_WARNING("B: VP: Could not open videofile \""+file.GetFullPath()+"\"");		
	};
	zERR_MESSAGE(4,zERR_END,"B: VP: Open Videofile finished");	

	return (mVideoHandle!=0);	
};

zBOOL zCBinkPlayer::CloseVideo()
{				
	if (!mVideoHandle) return FALSE;

	zERR_MESSAGE(4,zERR_BEGIN,"B: VP: Closing Videofile: \""+GetVideoFilename()+"\"");

	BinkClose(mVideoHandle);mVideoHandle= 0;				
	
	zBOOL result = zCVideoPlayer::CloseVideo();	

	zERR_MESSAGE(4,zERR_END,"B: VP: Closing Videofile finished");

	return result;
};
	
zBOOL zCBinkPlayer::PlayInit(int frameNr)
{
	if (mVideoHandle==0) return FALSE;	
	
	zERR_MESSAGE(3,zERR_BEGIN,"B: VP: Initialize Videoplay: \""+GetVideoFilename()+"\"");

	zBOOL success = zCVideoPlayer::PlayInit(frameNr);
	if (!success) 
	{
		CloseVideo();
		return FALSE;
	}
	
	int goto_flags = 0;
	if (frameNr>0) BinkGoto(mVideoHandle, frameNr, goto_flags);

	mCopyMode=-1;
	mXpos	= -1;
	mYpos	= -1;				

	//
	// Get information about direct-draw
	//
	zTRndSurfaceDesc sf;
	success = zrenderer->Vid_Lock(sf);
	if (success)	zrenderer->Vid_Unlock();
	else			zERR_FAULT("B: VP: Renderer is locked.");	
		
	//
	// copy-flags bestimmen
	//
	if (success)
	{					
		mCopyMode = GetPixelFormat(sf);
		if (mCopyMode<0)	zERR_FAULT("B: VP: Unknown pixelformat.");			
		else				zERR_MESSAGE(4,0,"B: VP: Pixelformat: "+zSTRING(mCopyMode));				
		success = (mCopyMode>=0);
	}

	//
	// Kann das Video dargestellt werden?
	//
	if (success)
	{			

		// aureichende aufloesung fuer das video?
		if (
			(mVideoHandle->Height > sf.pixelHeight) ||
			(mVideoHandle->Width > sf.pixelWidth)
			)
		{					
			zERR_WARNING("B: VP: Video won't play because of low resolution: "+zSTRING(sf.pixelWidth)+"x"+zSTRING(sf.pixelHeight));
			success = FALSE;
		}
	}

	//
	// Offset
	//

	zBOOL scaleVideo = zoptions->ReadBool(zOPT_SEC_GAME,"scaleVideos",TRUE);

	float scalex, scaley, scale;
	if (success)		
	{		
		scalex = float(sf.pixelWidth)/float(mVideoHandle->Width);
		scaley = float(sf.pixelHeight)/float(mVideoHandle->Height);
		scale  = zMin(scalex,scaley);
		if (!scaleVideo) scale = 1.0f;
		mXpos	= (int)((sf.pixelWidth - mVideoHandle->Width*scale) / 2.0f);
		mYpos	= (int)((sf.pixelHeight - mVideoHandle->Height*scale) / 2.0f);
		success = (mXpos>=0) && (mYpos>=0);
	}

	if (success)
	{
		mSourceRect.left	= 0;
		mSourceRect.top		= 0;
		mSourceRect.right	= mVideoHandle->Width+mXpos*2;
		mSourceRect.bottom	= mVideoHandle->Height+mYpos*2;									
		
		mTargetRect.left	= 0;
		mTargetRect.top		= 0;
		mTargetRect.right	= sf.pixelWidth;
		mTargetRect.bottom	= sf.pixelHeight;		
		
		zERR_MESSAGE(4,0,"B: VP: Scale-Factor: "+zSTRING(scale,2));
		zERR_MESSAGE(4,0,"B: VP: Video-Offset: "+zSTRING(mXpos)+"/"+zSTRING(mYpos));		
	}									
	
	//
	// Hintergrund fuer Fullscreenmode vorbereiten
	//
	if (success)	
	{		
		if (mDoFullscreen)
		{		
			// if (mBackTexture.IsEmpty()) mBackTexture="default.tga";
			mBackTexture="default.tga";
			delete mBackView;
			mBackView = zNEW(zCView(0,0,8192,8192));			
			mBackView->SetColor(GFX_BLACK);
			mBackView->InsertBack(mBackTexture);
			screen->InsertItem(mBackView);
			
			screen->Render();			
			zrenderer->Vid_Blit(true,&mSourceRect,&mTargetRect);

			screen->Render();			
			zrenderer->Vid_Blit(true,&mSourceRect,&mTargetRect);
		};		
	}	

	s_firstBlit = true;

	if (!success) CloseVideo();
	
	zERR_MESSAGE(3,zERR_END,"B: VP: Initialize Videoplay finished");
	return success;
};

zBOOL zCBinkPlayer::PlayDeinit()
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: VP: Deinitialize Videoplay: \""+GetVideoFilename()+"\"");
	
	if (mVideoHandle)
	{
		zERR_MESSAGE(4,0,"B: VP: Frames played: "+zSTRING(mVideoHandle->playedframes));				
		zERR_MESSAGE(4,0,"B: VP: Skipped blits: "+zSTRING(mVideoHandle->skippedblits));
#ifndef BINK_VERSION_15_UP
		zERR_MESSAGE(4,0,"B: VP: Soundbuffer-Size: "+zSTRING(mVideoHandle->sndbufsize)+" bytes");
#endif
		zERR_MESSAGE(4,0,"B: VP: Memory used: "+zSTRING(float(mVideoHandle->totalmem)/1024,0)+" kb");		
		zERR_MESSAGE(4,0,"B: VP: Time open: "+zSTRING(mVideoHandle->timeopen)+"sec.");		
		zERR_MESSAGE(4,0,"B: VP: Time blit: "+zSTRING(mVideoHandle->timeblit)+"sec.");				
	}
	
	zBOOL result = zCVideoPlayer::PlayDeinit();

	delete mBackView;mBackView=0;

	zERR_MESSAGE(3,zERR_END,"B: VP: Deinitialize Videoplay finished");
	return result;
};

zBOOL zCBinkPlayer::PlayGotoNextFrame()
{
	BinkNextFrame	(mVideoHandle);	 
	return TRUE;
};

zBOOL zCBinkPlayer::PlayWaitNextFrame()
{		
	while( IsPlaying() && BinkWait(mVideoHandle) )
	{
		PlayHandleEvents();  
	} 	

	return TRUE; 
};

zBOOL zCBinkPlayer::PlayFrame() 
{			
	if (IsPlaying()) 
	{					
		zCVideoPlayer::PlayFrame();
		
		PlayHandleEvents();

		if (IsPlaying()) 
		{		
			BinkDoFrame(mVideoHandle);

			PlayGotoNextFrame();

			PlayWaitNextFrame();						

			zTRndSurfaceDesc sf;										
			if (zrenderer->Vid_Lock(sf))
			{				
				if (mCopyMode>=0)			
					BinkCopyToBuffer(mVideoHandle,sf.pSurface,sf.bytePitch, sf.pixelHeight, mXpos,mYpos, mCopyMode);
				else 			
					zERR_WARNING("B: VP: Unknown pixel-format");								

				zrenderer->Vid_Unlock();				

				if (mDoBlit) 
				{			
					// Blitte ohne flip (FALSE) von sourceRect auf targetRect					
					zrenderer->Vid_Blit(FALSE,&mSourceRect,&mTargetRect);					
					s_firstBlit = true;
				}
			}

		}

		return TRUE;	
	}
	
	return FALSE;
};
  
zBOOL zCBinkPlayer::Pause()
{
	BinkPause(mVideoHandle,1);
	return zCVideoPlayer::Pause();
};

zBOOL zCBinkPlayer::Unpause()
{
	BinkPause(mVideoHandle,0);
	return zCVideoPlayer::Unpause();
};


zBOOL zCBinkPlayer::PlayHandleEvents()
{
	if (!mDoHandleEvents) return TRUE;	// EventHandling nicht weiter verfolgen
	
	return FALSE;
};

zBOOL zCBinkPlayer::IsPlaying()
{
	return 
		mVideoHandle &&
		zCVideoPlayer::IsPlaying() && 
		(IsLooping() || (mVideoHandle->Frames>mVideoHandle->FrameNum));
};

s32 zCBinkPlayer::GetPixelFormat(zTRndSurfaceDesc& sf)
{
	s32 format = -1;
	switch (sf.bitRGBCount)
	{
	case 16:
		if		((sf.bitGMask & 0x400) == 0x400) format = BINKSURFACE565;	// 565
		else if	((sf.bitGMask & 0x400) == 0)	 format = BINKSURFACE555;	// 555
		break;
	case 24:
		if		((sf.bitRMask & 1) == 1)		 format = BINKSURFACE24R;	// RGB
		else if	((sf.bitBMask & 1) == 1)		 format = BINKSURFACE24;	// BGR
		break;
	case 32:		
		if		((sf.bitRMask & 1) == 1)		 format = BINKSURFACE32R;	// RGB
		else if	((sf.bitBMask & 1) == 1)		 format = BINKSURFACE32;	// BGR
		break;
	default:
		zERR_WARNING("B: VP: Unknown rgb-count!");
	};
	return format;
}

zBOOL zCBinkPlayer::ToggleSound()
{
	zBOOL soundOn = zCVideoPlayer::ToggleSound();
	if (soundOn)
	{
#ifdef BINK_VERSION_15_UP
		BinkSetVolume(mVideoHandle, 0, (long)(mSoundVolume * 65536));
#else
		BinkSetVolume(mVideoHandle, (long)(mSoundVolume * 65000));
#endif
	}
	else
	{
#ifdef BINK_VERSION_15_UP
		BinkSetVolume(mVideoHandle, 0, 0);
#else
		BinkSetVolume(mVideoHandle, 0);
#endif
	};
	return soundOn;
};

zREAL zCBinkPlayer::SetSoundVolume(zREAL v)
{
	zREAL volume = zCVideoPlayer::SetSoundVolume(v);
#ifdef BINK_VERSION_15_UP
	BinkSetVolume(mVideoHandle, 0, (long)(GetSoundVolume() * 65536));
#else
	BinkSetVolume(mVideoHandle, (long)(GetSoundVolume() * 65000));
#endif
	return volume;
};

void zCBinkPlayer::SetFullscreen(zBOOL full, zSTRING tex)
{
	mDoFullscreen	= full;
	mBackTexture	= tex;
};
