/******************************************************************************** 
 
     $Workfile:: obinkplayer.cpp      $                $Date:: 14.03.01 18:40   $
     $Revision:: 20                   $             $Modtime:: 14.03.01 18:28   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
 
   Attention: 
 
 *********************************************************************************/


#include "zcore.h"
#include "zrenderer.h"
#include "zinput_win32.h"
#include "zzbert.h"
#include "zoption.h"

#include "obinkplayer.h"

oCBinkPlayer::oCBinkPlayer()
{		
	extendedKeys=FALSE;
}

oCBinkPlayer::~oCBinkPlayer()
{
}

zBOOL oCBinkPlayer::PlayInit(int frameNr)
{	
	disallowInputHandling = zoptions->ReadBool(zOPT_SEC_GAME,"disallowVideoInput",FALSE);

	zBOOL result = zCBinkPlayer::PlayInit(frameNr);	

	zinput->ProcessInputEvents();
	zinput->ClearKeyBuffer();
	zinput->ResetRepeatKey();

	return result;
};

zBOOL oCBinkPlayer::PlayDeinit()
{
	zBOOL result = zCBinkPlayer::PlayDeinit();	
	return result;
};





zBOOL oCBinkPlayer::PlayFrame()
{
	return zCBinkPlayer::PlayFrame();		
};

zBOOL oCBinkPlayer::PlayHandleEvents()
{	
	if (disallowInputHandling)				return FALSE;
	if (!mVideoHandle)						return FALSE;
	if (zCBinkPlayer::PlayHandleEvents())	return TRUE;
	
	//sysEvent();		
	zWORD key = zinput->GetKey(FALSE,FALSE);// kein Key-Repeat!!!
	zinput->ProcessInputEvents();

	zBOOL returnValue = FALSE;
	s32 frame;

	if (extendedKeys)
	{
		switch (key)	
		{
			case KEY_HOME:
				zERR_MESSAGE(6,0,"B: VP: Restart video.");
				BinkGoto(mVideoHandle,1,BINKGETKEYPREVIOUS);  
				break;
			case KEY_RIGHT:		
				frame = mVideoHandle->FrameNum+30; 
				zERR_MESSAGE(6,0,"B: VP: Set new video-frame to "+zSTRING(frame));
				if (frame<mVideoHandle->Frames)	BinkGoto(mVideoHandle,frame,BINKGETKEYNEXT);  
				break;		
			case KEY_UP:
			{
				zREAL volume = GetSoundVolume() + 0.05f;
				if (volume>1) volume=1;
				zERR_MESSAGE(6,0,"B: VP: Set sound-volume to "+zSTRING(volume));
				SetSoundVolume(volume);
				returnValue = TRUE;
			} break;
			case KEY_DOWN:
			{
				zREAL volume = GetSoundVolume() - 0.05f;		
				if (volume<0) volume=0;
				zERR_MESSAGE(6,0,"B: VP: Set sound-volume to "+zSTRING(volume));
				SetSoundVolume(volume);
				returnValue = TRUE;
			} break;
			case KEY_Q:
			{		
				zBOOL soundOn = ToggleSound();		
				if (soundOn) zERR_MESSAGE(3,0,"B: VP: Toggle Sound On");
				else zERR_MESSAGE(3,0,"B: VP: Toggle Sound Off");
				returnValue = TRUE;
			} break;
		}
	}

	switch (key)
	{
		case KEY_SPACE:
		{
 			if (!IsPaused())	{ Pause();zERR_MESSAGE(5,0,"B: VP: Paused"); }
			else				{ Unpause();zERR_MESSAGE(5,0,"B: VP: Unpaused"); };
			returnValue = TRUE;
		} break;
		case KEY_ESC:
		{
			zERR_MESSAGE(6,0,"B: VP: Cancel video ...");
			Stop();
			returnValue = TRUE;
		} break;
	}			
	return returnValue;	
};

//
// List of resolutions to check
// Ordered from highest to lowest
//
static const int		vidResNum = 3;
static const zSTRING	vidResChecks[vidResNum] = {"1024x768","800x600","640x480"};

//
// Overwritten OpenVideo-Methods with given filename
// Versucht zuerst das angegeben Videofile zu oeffnen und 
// Testet bei Misserfolg die in vidResChecks angegebenen Versionen für
// verschiedenen Auflösungen. Sucht sich also das passenden Videofile heraus.
//
zBOOL oCBinkPlayer::OpenVideo(zSTRING filename)
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: VP: Start opening video \""+filename+"\"");

	zSTRING base_filename = filename;
	base_filename.Upper();
	base_filename.Delete(".BIK");
	zBOOL success = zCBinkPlayer::OpenVideo(base_filename+".BIK");
	if (!success && zrenderer)	
	{
		zTRnd_VidModeInfo modeInfo;
		int modeNr = zrenderer->Vid_GetActiveModeNr();
		zrenderer->Vid_GetModeInfo(modeInfo,modeNr);		
		for (int i=0;i<vidResNum;i++)
		{
			zERR_MESSAGE(6,0,"B: VP: Checking resolution "+vidResChecks[i]);
			int xres = vidResChecks[i].PickWord(1,"x","x").ToInt();
			int yres = vidResChecks[i].PickWord(2,"x","x").ToInt();
			if (xres!=0 && yres!=0 && xres<=modeInfo.xdim && yres<=modeInfo.ydim)
			{				
				filename = base_filename+vidResChecks[i]+".BIK";
				zERR_MESSAGE(5,0,"B: VP: Trying videofile \""+filename+"\"");
				success = zCBinkPlayer::OpenVideo(filename);
				if (success) break;
			}
		}		
	}
	
	extendedKeys = zoptions->ReadBool(zOPT_SEC_GAME,"extendedVideoKeys",FALSE);

	zERR_MESSAGE(3,zERR_END,"");	

	return success;
};
