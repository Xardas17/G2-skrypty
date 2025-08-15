#include "zcore.h"
#include "zoption.h"
#include "zrenderer.h"
#include "zmenu.h"
#include "zviewobject.h"
#include "zviewdraw.h"
#include "zparser.h"
#include "zparser_const.h"
#include "zoption_const.h"
#include "zmusic.h"
#include "zmusic_dm.h"
#include "zzone.h"
#include "osysinfo.h"
#include "zsndmss.h"

#include "omenu_tools.h"

static const zSTRING APPLY_SOUND_NAME = "";

static void PlayApplySound()
{
	zCSoundFX *snd = zsound->LoadSoundFXScript("MENU_APPLY");
	if (!snd) snd = zsound->LoadSoundFXScript("TORCH_ENLIGHT");
	if (snd) zsound->PlaySound(snd);
	zRELEASE(snd);
};


//////////////////////////////////////////////////////////////////////////////
// 640  x 480	1.33333333	disabled (size)
//----------------------------------------------------------------------------
// 800  x 600	1.33333333
// 848  x 480	1.76666666	unsupported (ratio)
// 1024 x 768	1.33333333
// 1152 x 864	1.33333333
// 1280 x 720	1.77777777	unsupported (ratio)
// 1280 x 768	1.66666666	unsupported (ratio)
// 1280 x 960	1.33333333
// 1280 x 1024	1.25000000	(addon)
// 1360 x 768	1.77083333	unsupported (ratio)
// 1600 x 900	1.77777777	unsupported (ratio)
// 1600 x 1024	1.56250000	(addon)
// 1600 x 1200	1.33333333
//----------------------------------------------------------------------------
// 1920 x 1080	1.77777777	unsupported (size, ratio)	// untested
// 1920 x 1200	1.60000000	unsupported (size, ratio)	// untested
// 1920 x 1440	1.33333333	unsupported (size)			// untested
// 2048 x 1536	1.33333333	unsupported (size)			// untested
//////////////////////////////////////////////////////////////////////////////

static const int VID_MIN_XDIM = 800;
static const int VID_MIN_YDIM = 600;
static const int VID_MAX_XDIM = 1600;
static const int VID_MAX_YDIM = 1200;
static const float VID_MIN_RATIO = 1.2f;
static const float VID_MAX_RATIO = 1.6f;

zBOOL VidIsResolutionValid(int x, int y, int bpp)
{
	// bits per pixel
	if ((bpp != 16) && (bpp != 32))
		return FALSE;

	// minimum
	if ((x < VID_MIN_XDIM) || (y < VID_MIN_YDIM))
		return FALSE;

	if (!zoptions->ReadBool(zOPT_SEC_INTERNAL, "extendedMenu", FALSE))
	{
		// maximum
		if ((x > VID_MAX_XDIM) || (y > VID_MAX_YDIM))
			return FALSE;

		// ratio
		float r = float(x) / float(y);
		if ((r < VID_MIN_RATIO) || (r > VID_MAX_RATIO))
			return FALSE;
	}

	return TRUE;
};


extern zBOOL PlayVideo();	// -> oGameExternals.cpp

zBOOL DefineMenuScriptFunctions()
{
	zCParser* parser = zCMenu::GetParser();
	parser->DefineExternal	("Update_ChoiceBox",		Update_ChoiceBox, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal	("Apply_Options_Performance",Apply_Options_Performance, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
	parser->DefineExternal	("Apply_Options_Video",		Apply_Options_Video, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
	parser->DefineExternal	("Apply_Options_Audio",		Apply_Options_Audio, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
	parser->DefineExternal	("Apply_Options_Game",		Apply_Options_Game, zPAR_TYPE_VOID, zPAR_TYPE_VOID);
	parser->DefineExternal	("Apply_Options_Controls",	Apply_Options_Controls, zPAR_TYPE_VOID, zPAR_TYPE_VOID);

	parser->DefineExternal	("PlayVideo",				PlayVideo,	zPAR_TYPE_INT,	 zPAR_TYPE_STRING, zPAR_TYPE_VOID);

	return TRUE;
};

zBOOL Apply_Options_Video()
{		
	zERR_MESSAGE(3,zERR_BEGIN,"B: MENUE_APPLY_VIDEO");

	// gewählte Option auslesen
	int option = zoptions->ReadInt(zOPT_SEC_INTERNAL,ZOPT_VID_RES.ToChar());	
		
	// Ermitteln des gewünschten VideoModes (unerwünschte Auflösungen herausfiltern)
	zTRnd_DeviceInfo  devInfo;
	zTRnd_VidModeInfo modeInfo;
	
	int count	= 0;
	int x		= -1;
	int y		= -1;
	int bpp		= -1;

	for (int modeEnum=0; modeEnum<zrenderer->Vid_GetNumModes(); modeEnum++) 
	{
		zrenderer->Vid_GetModeInfo(modeInfo,modeEnum);			
		if (VidIsResolutionValid(modeInfo.xdim, modeInfo.ydim, modeInfo.bpp)) 
		{
			if (count==option) 
			{
				x = modeInfo.xdim;
				y = modeInfo.ydim;
				bpp = modeInfo.bpp;
			}
			count++;
		}
	}
		
	// Gültige Auflösung gefunden?
	if (!VidIsResolutionValid(x,y,bpp))
	{ 
		zERR_MESSAGE(3,0,"B: Forbidden Resolution: "+zSTRING(x)+" x "+zSTRING(y)+" x "+zSTRING(bpp));
		x=VID_MIN_XDIM;y=VID_MIN_YDIM;bpp=16; 
	}
	
	zERR_MESSAGE(3,0,"B: New Resolution: "+zSTRING(x)+" x "+zSTRING(y)+" x "+zSTRING(bpp));

	// Auflösung ändern?
	zrenderer->Vid_GetModeInfo(modeInfo,zrenderer->Vid_GetActiveModeNr());		
	if ( x!=modeInfo.xdim || y!=modeInfo.ydim || bpp!=modeInfo.bpp ) 
	{
		zCView::SetMode(x,y,bpp);
		zCViewDraw::GetScreen().SetSize(zPOS(8192,8192));
	}		

	// Auflösung in Option.ini schreiben
	zoptions->WriteInt	(zOPT_SEC_VIDEO, "zVidResFullscreenX"	, x);
	zoptions->WriteInt	(zOPT_SEC_VIDEO, "zVidResFullscreenY"	, y);
	zoptions->WriteInt	(zOPT_SEC_VIDEO, "zVidResFullscreenBPP"	, bpp);		
	
	PlayApplySound();

	zERR_MESSAGE(3,zERR_END,"");
	return FALSE;
};

zBOOL Apply_Options_Performance()
{	
	int index = zoptions->ReadInt(zOPT_SEC_INTERNAL,"perfQualityIndex",0);
	
	oCSystemInfo sysInfo;		
	sysInfo.AnalyseNow();
	sysInfo.ScoreNow();	

	switch (index)
	{
		case 0:		break;
		case 1:		sysInfo.ResetSettings(0.0f);break;
		case 2:		sysInfo.ResetSettings(0.5f);break;
		case 3:		sysInfo.ResetSettings(1.0f);break;
	};	
	
	PlayApplySound();

	return FALSE;
};

zBOOL ChangeMusicEnabled(zCOptionValue &newValue)
{
	zBOOL musicEnabled = zoptions->ReadBool(zOPT_SEC_SOUND,"musicEnabled",TRUE);

	
	if (musicEnabled)
	{		
		zCMusicSystem::DisableMusicSystem(FALSE);
		zCZoneMusic::SetAutochange(TRUE);
		if (zCMenu::GetActive()) zCMenu::GetActive()->RestartMusicTheme();
		zERR_MESSAGE(3,0,"B: MUSIC: Turned ON");
	}
	else	
	{	
		zCZoneMusic::SetAutochange(FALSE);
		zCMusicSystem::DisableMusicSystem(TRUE);		
		zERR_MESSAGE(3,0,"B: MUSIC: Turned OFF");
	};	

	//
	// Volume
	//

	zREAL volume;
	volume = zoptions->ReadReal(zOPT_SEC_SOUND,ZOPT_SND_SFX_VOL,1.0f);
	zClamp(volume, 0.0f, 1.0f);
	if (zsound) zsound->SetMasterVolume(volume);
	
	volume = zoptions->ReadReal(zOPT_SEC_SOUND,ZOPT_SND_MUSIC_VOL,0.8f);
	zClamp(volume, 0.0f, 1.0f);
	if (zmusic) zmusic->SetVolume(volume);

	return TRUE;
};

zBOOL Apply_Options_Audio()
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: MENUE_APPLY_AUDIO");

	
	PlayApplySound();

	zERR_MESSAGE(3,zERR_END,"");
	return FALSE;
};

zBOOL Apply_Options_Game()
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: MENUE_APPLY_GAME");
	
	PlayApplySound();

	zERR_MESSAGE(3,zERR_END,"");
	return FALSE;
};

zBOOL Apply_Options_Controls()
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: MENUE_APPLY_CONTROLS");
	

	PlayApplySound();

	zERR_MESSAGE(3,zERR_END,"");
	return FALSE;
};


zBOOL Update_ChoiceBox()
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: Update ChoiceBox");

	zSTRING s;
	zCParser *p = zCMenu :: GetParser();
	p->GetParameter(s);
	zCMenuItemChoice *box= (zCMenuItemChoice*)zCMenuItem::GetByName(s);
	if (!box) 
	{
		zERR_FAULT("C: Update_CB_Resolution: Box " + s + zSTRING(" unknown"));
	}
	else if (s == "MENUITEM_AUDIO_PROVIDER_CHOICE")
	{
		if (zsound && dynamic_cast<zCSndSys_MSS*>(zsound))
		{
			int numProviders = zsound->GetNumProvider();		
			zSTRING sndEnumList;
			
			for (int i=0; i<numProviders; i++) 
			{
				if (!sndEnumList.IsEmpty()) sndEnumList = sndEnumList + "|";
				sndEnumList = sndEnumList + zsound->GetProviderName(i);
			}

			box->SetText(sndEnumList);
		}
	}
	else if (s == "MENUITEM_VID_DEVICE_CHOICE") 
	{
		zTRnd_DeviceInfo  devInfo;
		zSTRING vidEnumOutList;
		zSTRING nextLine;

		for (int deviceEnum=0; deviceEnum<zrenderer->Vid_GetNumDevices(); deviceEnum++) 
		{
			zrenderer->Vid_GetDeviceInfo(devInfo,deviceEnum);			
			if (!vidEnumOutList.IsEmpty()) vidEnumOutList = vidEnumOutList + "|";
			vidEnumOutList = vidEnumOutList + devInfo.deviceName;
		}

		box->SetText(vidEnumOutList);
	}
	else if (s == "MENUITEM_VID_RESOLUTION_CHOICE") 
	{
		zTRnd_DeviceInfo  devInfo;
		zTRnd_VidModeInfo modeInfo;
		zSTRING vidEnumOutList;
		zSTRING nextLine;
		
		for (int modeEnum=0; modeEnum<zrenderer->Vid_GetNumModes(); modeEnum++) 
		{
			zrenderer->Vid_GetModeInfo(modeInfo,modeEnum);			
			if (VidIsResolutionValid(modeInfo.xdim, modeInfo.ydim, modeInfo.bpp))
			{
				nextLine = zSTRING(zSTRING(modeInfo.xdim)+zSTRING("x")+zSTRING(modeInfo.ydim)+zSTRING("x")+zSTRING(modeInfo.bpp));
				if (!vidEnumOutList.IsEmpty()) vidEnumOutList = vidEnumOutList + "|";
				vidEnumOutList = vidEnumOutList + nextLine;
			}
		}

		box->SetText(vidEnumOutList);				
	}
	zERR_MESSAGE(3,zERR_END,"");
	return FALSE;
};