// zSndMSS.cpp
// Carsten Edenfeld

// MSS hat keine Funktion um WAV Parameter auszugeben ohne das File geladen zu haben -> würg
// korrektes skalieren von script sound parametern ins MSS Format

/*****************************************************************************************************
Rev.:

0.1:	Sounds sind jetzt von zCResource abgeleitet -> Cache Handling
0.08e:  Handle Verwaltung Bugfix
0.08d:  GetSound3DProps Fix
0.08c:	Per sample volume weight
0.08b:	Interface Änderungen. UpdateSound3d Radius implementiert
0.08:	Klassen Checks, PlaySound3DAmbient Fix, Stereo Files werden abgefangen
0.07:	Interface Änderungen, Obstruction Features, Reverb Features, Sound Cones, Ambient 3D Sounds, Loop Points
0.06:	GetPlayingTimeMSEC implementiert
0.05:	3d sound exit-crash fix
0.04:   3d provider support inkl. doppler effect(EAX, DirectSound3D Software, DirectSound3D Hardware, A3d, Dolby Surround, RSX, Fast Miles 2d), 
		neue PlaySound3d Methode - die Instanzen/Waves können nun für bequemeres Abspielen von Sounds direkt angegeben werden
		diese Sounds werden nach 30 Sec. automatisch aus dem Speicher entfernt
0.03d:  dito, nu aber
0.03c:  pro vobSlot kann nur ein Sound gespielt werden -> Bugfix
0.03b:  pfxName zu Script Sounds hinzugefügt, LoadSoundFX lädt bei Bedarf WAV Files falls Name mit Endung übergeben, sonst Instanz
0.03:   geloopte Sounds ausserhalb Hörweite werden beim Wieder-Eintritt in diesen Bereich korrekt abgespielt
0.02e   SetIsLooping virtual korrigiert
0.02d   helpWave als Ptr. , gab Probleme bei Cmd-Switch zNoSound
0.02c   Upper() Bug Fix, 3d sounds auch ohne listener lauffähig
0.02b	sounds laden beschleunigt, sort bug fix
0.01g   console-commando soundstat
0.01f	*fiesen Bug der sich bei hoher Kanalbelastung zeigte, gefixed
		+Per sample reverberation hinzugefügt. Wenn auch nicht in berauschender Qualität
		+sound system preferences editierbar (realtime für alle Parameter)
		+sound preferences editierbar (realtime)

 * $Log: /current_work/zengin/_Carsten/zSndMSS.cpp $
 * 
 * 67    22.05.01 18:45 Edenfeld
 * 
 * 66    26.04.01 15:35 Edenfeld
 * Soundprovider Checks sicherer gemacht,
 * AIPlayer Sprunghänger Bug gefixt
 * 
 * 65    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 64    12.04.01 17:29 Edenfeld
 * Patch 2 (1.08): Änderungen fürs Sound System (HW Provider Support)
 * 
 * 63    12.03.01 19:59 Edenfeld
 * 3D Provider Fix Teil 1
 * 
 * 62    9.02.01 3:53 Edenfeld
 * 
 * 61    7.02.01 22:50 Edenfeld
 * 
 * 60    7.02.01 22:47 Edenfeld
 * 
 * 59    7.02.01 22:08 Edenfeld
 * 
 * 58    7.02.01 14:38 Moos
 * 
 * 57    2.02.01 23:40 Edenfeld
 * 
 * 56    29.01.01 23:36 Edenfeld
 * 
 * 55    29.01.01 18:59 Edenfeld
 * 
 * 54    24.01.01 15:41 Edenfeld
 * 
 * 53    22.01.01 22:41 Edenfeld
 * 
 * 51    18.01.01 20:25 Edenfeld
 * 
 * 50    17.01.01 20:24 Speckels
 * 
 * 49    16.01.01 20:03 Edenfeld
 * 
 * 48    20.12.00 14:15 Edenfeld
 * 
 * 47    3.11.00 18:18 Edenfeld
 * 
 * 46    19.10.00 18:26 Speckels
 * 
 * 45    18.10.00 17:52 Edenfeld
 * 
 * 44    18.10.00 17:31 Edenfeld
 * Multithreading & Wartung
 * 
 * 43    11.10.00 16:27 Edenfeld
 * 
 * 42    10.10.00 15:30 Speckels
 * 
 * 41    4.10.00 13:19 Moos
 * 
 * 40    3.10.00 19:08 Moos
 * 
 * 39    3.10.00 15:18 Moos
 * 
 * 38    29.09.00 14:50 Edenfeld
 * 
 * 37    26.09.00 1:57 Edenfeld
 * 
 * 34    25.09.00 10:30 Edenfeld
 * 
 * 33    25.09.00 0:21 Edenfeld
 * 
 * 32    21.09.00 4:25 Edenfeld
 * 
 * 31    12.09.00 13:38 Moos
 * 
 * 30    11.09.00 20:27 Rueve
 * 
 * 29    11.09.00 19:40 Speckels
 * 
 * 28    7.09.00 19:21 Edenfeld
 * 
 * 27    6.09.00 21:23 Edenfeld
 * 
 * 26    2.09.00 7:48 Edenfeld
 * 
 * 25    1.09.00 17:41 Edenfeld
 * 
 * 24    29.08.00 20:33 Moos
 * 
 * 23    29.08.00 20:20 Moos
 * 
 * 22    25.08.00 17:51 Edenfeld
 * 
 * 21    25.08.00 11:30 Moos
 * 
 * 20    15.08.00 14:25 Edenfeld
 * 
 * 19    10.08.00 20:25 Edenfeld
 * 
 * 18    28.07.00 13:33 Edenfeld
 * Lautstärke Ausblendverhalten gefixt & für ambiente Sounds angeglichen
 * 
 * 17    21.07.00 18:29 Edenfeld
 * 
 * 16    21.07.00 17:04 Edenfeld
 * 
 * 15    21.07.00 15:34 Edenfeld
 * 
 * 14    21.07.00 0:37 Edenfeld
 * 
 * 13    18.07.00 19:06 Edenfeld
 * 
 * 12    13.07.00 12:38 Edenfeld
 * 
 * 11    3.07.00 12:30 Edenfeld
 * 
 * 10    24.05.00 19:22 Edenfeld
 * 
 * 9     22.05.00 15:27 Edenfeld
 * 
 * 8     11.05.00 5:44 Edenfeld
 * 
 * 8     11.05.00 5:11 Edenfeld
 * 
 * 7     9.05.00 21:03 Edenfeld
 * 
 * 6     8.05.00 23:09 Edenfeld
 * 
 * 6     8.05.00 18:20 Edenfeld
 * 
 * 5     5.05.00 21:02 Edenfeld
 * 
 * 5     4.05.00 23:12 Edenfeld
 * Release 0.79b
 * 
 * 4     4.05.00 20:29 Edenfeld
 * 
 * 4     2.05.00 17:41 Edenfeld
 * zCResource Crash Fix Part 3
 * 
 * 3     28.04.00 12:58 Edenfeld
 * 
 * 2     21.04.00 17:27 Edenfeld
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 24    19.04.00 17:03 Edenfeld
 * 
 * 23    19.04.00 13:10 Edenfeld
 * 
 * 22    12.04.00 18:31 Edenfeld
 * 
 * 20    16.03.00 21:57 Edenfeld
 * 
 * 19    16.03.00 13:50 Edenfeld
 * Anpassungen an Engine 0.88
 * 
 * 17    5.03.00 19:00 Edenfeld
 * Spacer Lautstärke Fix, Terratec Support
 * 
 * 16    3.03.00 13:30 Edenfeld
 * Spacer Lautstärke Regler Fix
 * 
 * 15    1.03.00 15:56 Edenfeld
 * 
 * 14    23.02.00 1:37 Edenfeld
 * 
 * 13    3.02.00 16:20 Edenfeld
 * zengin 0.86
 * 
 * 12    27.01.00 13:10 Edenfeld
 * 
 * 11    24.01.00 15:17 Edenfeld
 * 
 * 10    24.01.00 14:39 Edenfeld
 * zTSound3DParams::pitchOffset
 * 
 * 9     19.01.00 0:32 Edenfeld
 * Logging niedriger priorisiert
 * 
 * 8     10.01.00 15:18 Edenfeld
 * Handle Verwaltung Bugfix
 * 
 * 7     12.12.99 22:57 Edenfeld
 * Karten unterstützt, die über den Wave Mapper laufen (Terratec Maestro)
 * 
 * 6     7.12.99 16:28 Edenfeld
 * 
 * 5     1.12.99 13:16 Edenfeld
 * MSS6 eingebaut. 

*****************************************************************************************************/
#if 0
#ifdef CHASE_DEBUG
	#define CHECK_WAVREFCTR
	#define CHECK_MSSWAVREF
//	#define SOUND_NIL
	static int nilHandle = 0;
#endif
#endif


#include "zcore.h"
#include "zOption.h"
#include "zoption_const.h"
#include "zSndMSS.h"
#include "z3d.h"
#include "zConsole.h"
#include "zvob.h"
#include "dsound.h"
#include "zexceptionhandler.h"
#include "zworld.h"
#include "zMathTools.h"
#include "zAccount.h"
#include "zSky.h"

#pragma warning( disable : 4244 )

#define SFX_VER zSTRING("v 0.1")

// *******************************************************************************************
// Miles Version
// *******************************************************************************************

#if defined(MSS_MAJOR_VERSION) && defined(MSS_MINOR_VERSION)

#if (MSS_MAJOR_VERSION == 6) && (MSS_MINOR_VERSION >= 5)
#define MSS_VERSION_65_UP
#elif (MSS_MAJOR_VERSION > 6)
#define MSS_VERSION_65_UP
#endif

#endif


// *******************************************************************************************
// Variables
// *******************************************************************************************


zCDrvProperties_MSS			  zCSndSys_MSS  ::  prefs;
zCArraySort	<zCActiveSnd*>	  zCActiveSnd	::	activeSndList;
zCArray		<zCActiveSnd*>	  zCActiveSnd	::  preAllocedSndList;
zCActiveSnd*				  zCActiveSnd	::  nextFreeSnd		= 0;

zDWORD						  zCActiveSnd	::	lastHandle		= 0;	
int							  zCActiveSnd	::	maxChannels		= 16;	
zBOOL						  zCActiveSnd	::	autoUpdate3D	= FALSE;		// (FIXME) buggy


const float		MIN_DIST_MAX_VOL_SCALE					= 0.3F;
// 0.05f: eax2, 1.0f mss soft, 0.15 ds hw
float			RANGE_SCALE								= 1.0f;
const float		EAX_AIR_ABSORPTION_DEFAULT				= 0;
const float		CONST_ZERO								= 0;
const float		MAX_OBSTRUCTION							= 0.7F;
const float		SC_PITCH_HALVE_OCT_UP					= 1.059463094F;
const float		SC_PITCH_HALVE_OCT_DOWN					= 0.943874312F;
const int		MSS_VOL_DEFAULT							= 30;
const int		MSS_VOL_MIN								= 0;
const int		MSS_VOL_MAX								= 127;
const int		MSS_PAN_LEFT							= 0;
const int		MSS_PAN_CENTER							= 64;
const int		MSS_PAN_RIGHT							= 127;
const int		MIN_ACTSND_PREALLOCED					= 50;
const int		MAX_MUTE_MSEC_BEFORE_RELEASE			= 3000;
const int		AUTODELETION_WAIT_MSEC_BEFORE_RELEASE	= 30000;
const float		MIN_DISCARD_VOLUME						= 0.05F;
const float		SOFTREVERB_SCALEFACTOR					= 0.5F;


const zSTRING	ID_CHANNEL_CHAR							= zSTRING("V");
const zSTRING	ID_FRAME_CHAR							= zSTRING("A");
const zSTRING   DIRECTLOAD_PREFIX						= zSTRING("%");
const zSTRING	DIRECTLOAD_INSTANCENAME					= zSTRING("Internal");
const zSTRING   UNDERBAR								= zSTRING("_");
const zSTRING   MSS_DEF_WAVE							= zSTRING("DEFAULT.WAV");
const zSTRING	MSS_NO_WAVE								= zSTRING("NOWAVE");

const zSTRING	PROV_MILES_2D							= "Miles Fast 2D Positional Audio";
const zSTRING	PROV_DOLBY_SURR							= "Dolby Surround";
const zSTRING	PROV_DS3D_SW							= "DirectSound3D Software Emulation";
const zSTRING	PROV_DS3D_HW							= "DirectSound3D Hardware Support";
const zSTRING	PROV_DS3D7_PANVOL						= "DirectSound3D 7+ Software - Pan and Volume";
const zSTRING	PROV_DS3D7_LIGHT						= "DirectSound3D 7+ Software - Light HRTF";
const zSTRING	PROV_DS3D7_HRTF							= "DirectSound3D 7+ Software - Full HRTF";
const zSTRING	PROV_EAX								= "Creative Labs EAX (TM)";
const zSTRING	PROV_EAX2								= "Creative Labs EAX 2 (TM)";
const zSTRING	PROV_EAX3								= "Creative Labs EAX 3 (TM)";
const zSTRING	PROV_A3D								= "Aureal A3D Interactive (TM)";
const zSTRING	PROV_A3D2								= "Aureal A3D 2.0 (TM)";
const zSTRING	PROV_RSX								= "RAD Game Tools RSX 3D Audio";


#ifdef MSS_VERSION_65_UP

const int NUM_PROVIDERS = 13;
static zSTRING s_m3d_names[NUM_PROVIDERS<<2] =
{
	// short	menu name					filename		internal miles name
	"MILES",	"Miles Fast",				"MssSoft.m3d",	PROV_MILES_2D,
	"DS3D_HW",	"DirectSound3D HW",			"MssDS3D.m3d",	PROV_DS3D_HW,
	"EAX2",		"Creative EAX 2",			"MssEAX.m3d",	PROV_EAX2,
	// [extended]
	"DOLBY",	"Dolby Surround",			"MssSoft.m3d",	PROV_DOLBY_SURR,
	"RSX",		"RSX 3D Audio",				"MssRSX.m3d",	PROV_RSX,
	"DS3D_SW",	"DirectSound3D SW",			"MssDS3D.m3d",	PROV_DS3D_SW,
	"DX7_PV",	"DS3D7 SW - Pan/Volume",	"MssDX7.m3d",	PROV_DS3D7_PANVOL,
	"DX7_HRTF",	"DS3D7 SW - light HRTF",	"MssDX7.m3d",	PROV_DS3D7_LIGHT,
	"DX7_FULL",	"DS3D7 SW - full HRTF",		"MssDX7.m3d",	PROV_DS3D7_HRTF,
	"EAX",		"Creative EAX",				"MssEAX.m3d",	PROV_EAX,
	"EAX3",		"Creative EAX 3",			"MssEAX.m3d",	PROV_EAX3,
	"A3D",		"Aureal A3D",				"MssA3D.m3d",	PROV_A3D,
	"A3D2",		"Aureal A3D 2.0",			"MssA3D.m3d",	PROV_A3D2
};
static float s_m3d_distance_factors[NUM_PROVIDERS] =
{
	1.00f,	// Miles Fast
	0.01f,	// DirectSound3D HW
	0.01f,	// Creative EAX 2
	0.01f,	// Dolby Surround
	0.01f,	// RSX 3D Audio
	0.01f,	// DirectSound3D SW
	0.01f,	// DS3D7 SW - Pan/Volume
	0.01f,	// DS3D7 SW - light HRTF
	0.01f,	// DS3D7 SW - full HRTF
	0.01f,	// Creative EAX
	0.01f,	// Creative EAX 3
	0.01f,	// Aureal A3D
	0.01f	// Aureal A3D 2.0
};

#else

const int NUM_PROVIDERS = 5;
static zSTRING s_m3d_names[NUM_PROVIDERS<<2] =
{
	// short	menu name					filename			internal miles name
	"MILES",	"Miles Fast",				"MssFast.m3d",		PROV_MILES_2D,
	"DS3D_HW",	"DirectSound HW",			"MssDS3DH.m3d",		PROV_DS3D_HW,
	"EAX2",		"Creative EAX 2",			"MssEAX2.m3d",		PROV_EAX2,
	// [extended]
	"DOLBY",	"Dolby Surround",			"MssDolby.m3d",		PROV_DOLBY_SURR,
	"RSX",		"RADGameTools RSX",			"MssRSX.m3d",		PROV_RSX
};
static float s_m3d_distance_factors[NUM_PROVIDERS] =
{
	1.00f,	// Miles Fast
	0.01f,	// DirectSound3D HW
	0.01f,	// Creative EAX 2
	0.01f,	// Dolby Surround
	0.01f	// RSX 3D Audio
};

#endif // MSS_VERSION_65_UP

const zSTRING zSND_DEFAULT_PROVIDER = "MILES";


static	zSTRING			scriptCfgInstance("sndSysConfig");
static	zCHandleManager	handleMan;
static  zMAT4			trafoWStoLS;
static	zCVob*			listener			= 0;
static  zCParser*		sfxParser			= 0;
static  zCConsole*		sfxCon				= 0;
static  zCConsole*		frmCon				= 0;

static  zCSndFrame*		actFrameEdited		= 0;

static  HDIGDRIVER		sndDrv				= 0; 
static  HPROVIDER		act3dProvider		= 0;
static  int				act3dProviderIndex	= -1;
static  zSTRING			act3dProviderName   = zSTRING("");
static  HPROVIDER		reverb3Filter		= 0;
static  int				sndMemUsed			= 0;
static  float			globalOcclusion		= 0;
static	float			globalReverbWeight  = 1;
static	zBOOL			d_showSndInfo		= FALSE;
static	zBOOL			d_showSndCache		= FALSE;
static	zBOOL			d_noUpdate			= FALSE;

 
// *******************************************************************************************
// static sort routines & other global funcs
// *******************************************************************************************

static int CompareActHandles( const void *e1, const void *e2 )
{
	return ( (*(zCActiveSnd **)e1)->handle - (*(zCActiveSnd **)e2)->handle ) ;
}
static int CompareWaves( const void *e1, const void *e2 )
{
	return strcmp( (*(zCWaveData**)e2)->GetName().ToChar(),(*(zCWaveData**)e1)->GetName().ToChar());
}

static inline zSTRING GetPathWOFileName(zPATH &path)
{
	zSTRING end;
	zSTRING drive= path.GetDrive();
	zSTRING dir  = path.GetDir();
	if (drive.Length() > 0) drive += zSTRING(":");
	if (dir.Length() > 0 && &dir[dir.Length()-1] != "\\") end = "\\"; else end = "";
	return drive + dir + end;
}

static int ProviderOptNameToIndex (const zSTRING &name)
{
	for (int i=0; i<NUM_PROVIDERS; i++)
	{
		if (name == s_m3d_names[i<<2]) return i;
	}
	return -1;
};

static zSTRING ProviderIndexToName(const int index)
{
	return s_m3d_names[(index<<2)+2];
};

static zSTRING SpeakerTypeToString(const zCSoundSystem::zTSpeakerType speakerType)
{
	switch (speakerType)
	{
	case zCSoundSystem::zSPEAKER_TYPE_2_SPEAKER: return "TWO_SPEAKER";	break;
	case zCSoundSystem::zSPEAKER_TYPE_HEADPHONE: return "HEADPHONE";	break;
	case zCSoundSystem::zSPEAKER_TYPE_SURROUND:  return "SURROUND";		break;
	case zCSoundSystem::zSPEAKER_TYPE_4_SPEAKER: return "FOUR_SPEAKER";	break;
	}
	return "UNKNOWN";
};

static zCSoundSystem::zTSpeakerType SpeakerStringToType(const zSTRING speakerType)
{
	zSTRING speaker = speakerType;
	speaker.Upper();

	if (speaker == "TWO_SPEAKER")	return zCSoundSystem::zSPEAKER_TYPE_2_SPEAKER; else
	if (speaker == "HEADPHONE"  )	return zCSoundSystem::zSPEAKER_TYPE_HEADPHONE; else 
	if (speaker == "SURROUND"   )	return zCSoundSystem::zSPEAKER_TYPE_SURROUND;  else 
	if (speaker == "FOUR_SPEAKER")	return zCSoundSystem::zSPEAKER_TYPE_4_SPEAKER; 
	return zCSoundSystem::zSPEAKER_TYPE_2_SPEAKER;
};


static inline void D_SpyFrameInfo(const zCActiveSnd *snd,zBOOL stop = FALSE) 
{
	if (d_showSndInfo) 
	{
	
		zSTRING sndDescr;
		zSTRING startStopStr;

		if (snd->sourceFrm->GetWave()->GetSize()==0) return;
		switch (snd->sourceFrm->GetWave()->info->format) {
		case DIG_F_MONO_8		: sndDescr = zSTRING(" MONO 8 BITS "); break;
		case DIG_F_MONO_16		: sndDescr = zSTRING(" MONO 16 BITS "); break;
		case DIG_F_STEREO_8		: sndDescr = zSTRING(" STEREO 8 BITS "); break;
		case DIG_F_STEREO_16	: sndDescr = zSTRING(" STEREO 16 BITS "); break;
		case DIG_F_ADPCM_MONO_16: sndDescr = zSTRING(" ADPCM MONO 16 BITS "); break;
		case DIG_F_ADPCM_STEREO_16: sndDescr = zSTRING(" ADPCM STEREO 16 BITS "); break;
		default:					sndDescr = zSTRING(" UNKNOWN FORMAT "); break;
		}

		sndDescr += snd->Is3DSnd() ? zSTRING(" 3D") : zSTRING(" AMBIENT");
		startStopStr = stop ? zSTRING("stopping") : zSTRING("starting");

		zERR_MESSAGE(10,0,"C: " + startStopStr + " wave: " + snd->sourceFrm->fileName + 
					 " channels:"				   + zSTRING(		snd->sourceFrm->GetWave()->info->channels)  +
					 " orig. rate: "			   + zSTRING((int)	snd->sourceFrm->GetWave()->info->rate)		+ 
					 " orig. bits: "			   + zSTRING(		snd->sourceFrm->GetWave()->info->bits)		+
					 " samples: "				   + zSTRING((int)	snd->sourceFrm->GetWave()->info->samples)	+ 
					 " volume:  "				   + zSTRING((int)	snd->volume)					+ 
					 " pan: "					   + zSTRING((int)	snd->pan)						+ 
					 " radius:"					   + zSTRING((int)	snd->radius)					+ 
					 " looping: "				   + zSTRING((int)	snd->looping)					+
					 " freq: "					   + zSTRING((int)	snd->rate)						+
					  sndDescr );
	}
}


static zBOOL IsNT()
{
	// Get the build number for Windows NT/Windows 2000 or Win32s.
	if (GetVersion() < 0x80000000) return TRUE; else return FALSE;
};


static void Exc_ReleaseSound()
{
	if (zsound)	   
	{ 
		delete zsound;    zsound    = 0; 
	};
}

// callback-class for perFrame/perRender activities
class zCSndDebugCallback : public zCWorldPerFrameCallback {
public:
	virtual void DoWorldPerFrameCallback (zCWorld *world, zCCamera *camera)
	{
		zCWavePool::GetPool().DebugInfo2();
	};
};

zCSndDebugCallback sndDebugCallback;

// *******************************************************************************************
// zCSndSys_MSS
// *******************************************************************************************

// constructor
zCSndSys_MSS :: zCSndSys_MSS  () 
{
#ifdef SOUND_NIL
	return;
#endif

	zexhnd.AddUnhandledExceptionReleaseCallback   ( Exc_ReleaseSound	); 

	zERR_MESSAGE(5,0,zSTRING("C: *** Miles Sound System implementation ") + SFX_VER);

	listener			= 0;
	defaultRadius		= 3500;
	speakerType			= zSPEAKER_TYPE_2_SPEAKER;
	globalReverbPreset	= 0;

	prefs.sampleRate			= 22100;
	prefs.numSFXChannels		= 16;
	prefs.useStereo				= 1;
	prefs.bitResolution			= 16;
	prefs.volume				= 1;

	zCActiveSnd  :: activeSndList.SetCompare(CompareActHandles);
	zCActiveSnd  :: maxChannels = prefs.numSFXChannels;
	
	zoptions->ChangeDir(DIR_SCRIPTS);

    if (!sfxParser) // [Moos] : safety
	    sfxParser = zNEW (zCParser);

	// [BENDLIN] AddonMOD
	zSTRING filename = "";
	if (zgameoptions)
		filename = zgameoptions->ReadString(zOPT_SEC_FILES, "SoundEffects");
	if (filename.IsEmpty())
		filename = "System\\Sfx";
	zERR_MESSAGE(4, 0, "N: SND: Loading file " + filename + ".src or .dat");

	sfxParser -> Parse(filename + ".src");
	sfxParser -> CreatePCode();
	sfxParser -> CheckClassSize(zSTRING("C_SFX"),zCSndFrame::GetScriptClassSize());
	sfxParser -> CheckClassSize(zSTRING("C_SNDSYS_CFG"),zCDrvProperties_MSS::GetScriptClassSize());

	if (sfxParser->GetSymbol(scriptCfgInstance)) 
	{
	   sfxParser->CreateInstance(scriptCfgInstance,&prefs);
	   zCActiveSnd	::	maxChannels = prefs.numSFXChannels;
	}


	InitializeMSS();

	SetGlobalReverbPreset(0,0);

	SetSpeakerType(zCSoundSystem::zTSpeakerType(zoptions->ReadInt(zOPT_SEC_INTERNAL,	"soundSpeakerIndex",	FALSE)));

	zcon.Register( "TOGGLE SOUNDINFO"	, "Toggles sound debugging messages");
	zcon.Register( "ZTOGGLE SHOWSOUNDS"	, "Toggles sound debugging messages(2)");
	zcon.Register( "EDIT SOUNDSYSPREFS"	, "edits sound system preferences");
	zcon.Register( "EDIT SOUND"			, "edits a sound effect");
	zcon.Register( "SOUNDSTAT"			, "shows sound mem used");

	zcon.AddEvalFunc( zCSndSys_MSS::EvalFunc );

	// Liste mit bereits allokierten zCActiveSnds erstellen (damit kein new zCActiveSnd für jeden Aufruf von PlaySound3D nötig ist)
	zCActiveSnd::InitPreAllocedData();
	actFrameEdited = zNEW(zCSndFrame);

	zERR_MESSAGE(5,0,"");
}

// destructor

zCSndSys_MSS :: ~zCSndSys_MSS() 
{
#ifdef SOUND_NIL
	return;
#endif

	zexhnd.RemoveUnhandledExceptionReleaseCallback(Exc_ReleaseSound);

	zERR_MESSAGE(5,0,"C: Shutting down MSS");

	delete actFrameEdited;			// FIXME: crash ???? [Moos] Falls ja, biiiitte genauere Ursache feststellen. Die Zeile ist jedenfalls absolut korrekt.
	actFrameEdited = NULL;

	DisposeAllSampleHandles();
	RemoveAllActiveSounds();
	handleMan.DisposeAllSamples();

	// alle sounds die noch im speicher sind, releasen
	for (int i=0; i<zCSndFX_MSS::GetStaticClassDef()->GetNumObjects(); i++) 
	{
		zCObject *snd = zCSndFX_MSS::GetStaticClassDef()->GetObjectByIndex(i);
		static_cast<zCSndFX_MSS*>(snd)->SetCacheOutLock(FALSE);
    	//	snd->Release();  [Moos] : dieser Teil ist nicht mehr nötig; ~zCActiveSnd erledigt das.
	}

	CloseProvider();
	AIL_waveOutClose(sndDrv);
	AIL_shutdown();

    zCActiveSnd::CleanupPreAllocedData(); // [Moos] Leakfix

	zERR_MESSAGE(10,0,"C: done");

    delete sfxParser; // [Moos] Leakfix
    sfxParser=NULL;

    SetListener(NULL);  // [Moos] Leakfix
}

void zCSndSys_MSS::InitializeMSS() 
{
	#ifdef SOUND_NIL
		return;
	#endif

    const int VER_STR_LEN = 80;
    char mssVer[VER_STR_LEN];
    int  len=VER_STR_LEN;

	// hier code einfügen, der den aktuellen provider aus der gothic.ini ins system verzeichnis kopiert 
	// (vorher alle m3d files löschen)

	// alle aktuellen m3d files im system verzeichnis löschen
	zoptions->ChangeDir(DIR_EXECUTABLE);
	Dir_Clear(".\\","*.M3D");	

	// nun den gewünschten provider ins system verzeichnis kopieren (inkl. den default provider)
	int     currentProvIndex= zoptions->ReadInt(zOPT_SEC_INTERNAL,	"soundProviderIndex",	ProviderOptNameToIndex (zSND_DEFAULT_PROVIDER));
	zSTRING fileName		= s_m3d_names[(currentProvIndex<<2)+2];

	zFILE_FILE targetFile;	
	targetFile.SearchFile("\\MILES\\"+fileName,"\\");
	
	if ( targetFile.FileCopy(zoptions->GetDirString(DIR_EXECUTABLE)+fileName) == FALSE )
	{
		zERR_FATAL("C: could not copy file: " + zoptions->GetDirString(DIR_EXECUTABLE)+fileName + " into the system directory");
	}

	int currentDefProvIndex	= ProviderOptNameToIndex (zSND_DEFAULT_PROVIDER);
	fileName				= s_m3d_names[(currentDefProvIndex<<2)+2];

	targetFile.SearchFile("\\MILES\\"+fileName,"\\");
	if ( targetFile.FileCopy(zoptions->GetDirString(DIR_EXECUTABLE)+fileName) == FALSE )
	{
		zERR_FATAL("C: could not copy file: " + zoptions->GetDirString(DIR_EXECUTABLE)+fileName + " into the system directory");
	}

	SetReverbEnabled(zoptions->ReadBool  ( zOPT_SEC_SOUND, ZOPT_SND_USEREVERB,	 TRUE));

	// mit ail_startup werden nun alle m3d files aus dem system verzeichnis alloziiert und können in 
	// SetProvider() gesetzt werden
	AIL_startup();
	AIL_MSS_version(mssVer,len);

	zERR_MESSAGE(5,0,zSTRING("C: SND: *** mss.dll version " + zSTRING(mssVer) )) ;

	U16 digitalChans = prefs.useStereo ? 2 : 1 ;
	// samplerate aus der ini datei holen
	int		sndSampleRateIndex	= zoptions->ReadInt(zOPT_SEC_INTERNAL,	"soundSampleRateIndex",	0);	
	prefs.sampleRate			= (sndSampleRateIndex == 1) ? 44100 : 22050;
	U16 digitalRate  = prefs.sampleRate;
	zDWORD res;
	char buf[128];

	while (prefs.sampleRate>=11025) 
	{
		 prefs.waveFormat.wf.wFormatTag      = WAVE_FORMAT_PCM;
		 prefs.waveFormat.wf.nChannels       = (U16)digitalChans;
		 prefs.waveFormat.wf.nSamplesPerSec  = prefs.sampleRate;
		 prefs.waveFormat.wf.nAvgBytesPerSec = prefs.sampleRate * (prefs.bitResolution / 8) * digitalChans;
		 prefs.waveFormat.wf.nBlockAlign     = (U16)( (prefs.bitResolution / 8) * digitalChans);
		 prefs.waveFormat.wBitsPerSample     = (U16)prefs.bitResolution;

		 res = AIL_waveOutOpen(&sndDrv,0,WAVE_MAPPER,(LPWAVEFORMAT)&prefs.waveFormat);

		 if ( res==0 ) 
		 {
			// the waveOut succeeded!
			// get the text description of the sound driver

			strcpy(buf,"Device: ");
			AIL_digital_configuration(sndDrv,0,0,buf+strlen(buf));

			// if we're using DirectSound, check to see if it is in emulated
			// mode.  if so, then close the device and re-open with waveOut

			// FIXME: why ? what are the advantages ? direct music does not work parallel, if
			// we force waveout on wave mapper cards (e.g. terratec maestro)

			if (IsNT())
			if (AIL_get_preference(DIG_USE_WAVEOUT)==FALSE) 
			{
				// see if DirectSound is emulated
				if ( strstr(buf, "Emulated")!=0 ) 
				{
				   // we're emulated, so close down the driver and reset the
				   // preference
				   zERR_MESSAGE(4,0,"C: SND: DirectSound is emulated, switching to MME");
				   AIL_waveOutClose(sndDrv);
  				   AIL_set_preference(DIG_USE_WAVEOUT, TRUE);
				   continue;
				}
			}

	 		// yep. so use it
	 		zERR_MESSAGE(5,0,"C: SND: success :" + zSTRING(buf) );

#ifdef MSS_VERSION_65_UP
			AIL_set_digital_master_volume_level(sndDrv, prefs.volume);
#else
			AIL_set_digital_master_volume(sndDrv,(int) Lerp( prefs.volume, MSS_VOL_MIN, MSS_VOL_MAX ));
#endif

			if (!Start3DProvider(currentProvIndex))
			{
				zERR_FATAL("C: zCSndSys_MSS::InitializeMSS(): could not initialize 3D Provider. wrong/illegal provider in gothic.ini ?");
			}

			HPROENUM  next = HPROENUM_FIRST;
			HPROVIDER dest = 0;
			char *    name = 0;

			while (AIL_enumerate_filters(&next, &dest, &name)) 
			{
				zSTRING filtName(name);
				zERR_MESSAGE(5,0,"C: SND: found filter: " + filtName);
				if (filtName.Upper().Search("REVERB3")!=-1) {
					reverb3Filter = next;
				}
			}

			if (!reverb3Filter) {
				zerr.Warning("C: SND: no reverb filter for ambient sounds found. Ambient sounds won't have reverb and occlusion!");
			}
			else 
			{
				zERR_MESSAGE(4,0,"C: SND: opening reverb3 filter processor");
				AIL_open_filter(reverb3Filter,sndDrv);
			}

			zERR_MESSAGE(5,0,"");

			return;
		}

		// this rate didn't work, try a slower rate
		prefs.sampleRate=prefs.sampleRate/2;
		// if all of the 16-bit opens have failed, try 8-bit
		if ((prefs.sampleRate<11025) ) 
		{
			if ((prefs.bitResolution==16)) 
			{
				prefs.sampleRate	=	digitalRate;
				prefs.bitResolution	=	8;
			} 
			else if (AIL_get_preference(DIG_USE_WAVEOUT)==FALSE) 
			{
				zERR_WARNING("C: SND: failed opening DirectSound, MSS reported error: " + zSTRING(AIL_last_error()) );
				zERR_WARNING("C: SND: trying to open standard windows MME driver (not recommended)" );
  				AIL_set_preference(DIG_USE_WAVEOUT, TRUE);
				prefs.sampleRate=digitalRate;
				prefs.bitResolution=16;
			}
		}
	}


	zERR_FATAL("C: failed to initialize sound, MSS reported: " + zSTRING(AIL_last_error()));

}

HDIGDRIVER  zCSndSys_MSS::GetDigitalDriverHandle()
{
	return sndDrv;
};


zBOOL zCSndSys_MSS::EvalFunc(const zSTRING &in, zSTRING &msg)
{
	zSTRING s = in;
	s.Upper();
	if ( s.PickWord(1, " ") == "SOUNDSTAT" ) 
	{
		msg = "sound Mem Used: "+zSTRING(sndMemUsed);
		zCWavePool::GetPool().DebugInfo();
		zCActiveSnd::DebugInfo();
		return TRUE;
	}
	else if ( s.PickWord(1, " ") == "TOGGLE" ) 
	{
		if ( s.PickWord(2, " ") == "SOUNDUPDATE" ) 
		{
			d_noUpdate = !d_noUpdate;
			if (d_noUpdate) msg = "no sound update on";
			else msg = "no sound update off";
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "SOUNDINFO" ) 
		{
			d_showSndInfo= !d_showSndInfo;
			if (d_showSndInfo) msg = "sound debug messages enabled";
			else msg = "sound debug messages disabled";
			return TRUE;
		} 
	}
	else if ( s.PickWord(1, " ") == "ZTOGGLE" ) 
	{
		if ( s.PickWord(2, " ") == "SHOWSOUNDS" ) 
		{
			d_showSndCache = !d_showSndCache;
			if (d_showSndCache) 
			{
				msg = "sound cache messages enabled";
				if ( listener && listener->GetHomeWorld() ){
					listener->GetHomeWorld()->RegisterPerFrameCallback(&sndDebugCallback);
				}
			}
			else 
			{
				if ( listener && listener->GetHomeWorld() ){
					listener->GetHomeWorld()->UnregisterPerFrameCallback(&sndDebugCallback);
				}
				msg = "sound cache messages disabled";
			};
			return TRUE;
		};
	}
	else if ( s.PickWord(1, " ") == "EDIT" ) 
	{
		if ( s.PickWord(2, " ") == "SOUNDSYSPREFS" ) 
		{
			zcon.Hide();
			
			if (sfxCon) delete sfxCon;
			sfxCon = zNEW (zCConsole());
			sfxCon -> SetPos  (0,0);
			sfxCon -> SetParser (sfxParser);
			sfxCon -> SetChangedFunc ( SfxCon_ParamChanged );  
			sfxCon -> EditInstance(zSTRING("SNDSYSCONFIG"), &prefs);
			sfxCon->SetFocus();
			return TRUE;
		}
		else if ( s.PickWord(1, " ") == "EDIT" ) 
		{
			if ( s.PickWord(2, " ") == "SOUND" ) 
			{
				zcon.Hide();
				zSTRING id = s.PickWord(3, " ");
				if (id != zSTRING("")) {
					if (frmCon) delete frmCon;
					frmCon = zNEW(zCConsole());
					frmCon -> SetPos  (0,0);
					frmCon -> SetParser (sfxParser);
					frmCon -> SetChangedFunc ( FrmCon_ParamChanged );  
					sfxParser->CreateInstance(id,actFrameEdited);
					actFrameEdited->fileName.Upper();
					actFrameEdited->instance = id;
					frmCon -> EditInstance(id, actFrameEdited);
					frmCon -> SetFocus();
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}


void zCSndSys_MSS::FrmCon_ParamChanged(const zSTRING &in) 
{
	zSTRING s = in;
	s.Upper();
	int sfxNum, chNum, frNum;
	for (sfxNum=0; sfxNum<zCSndFX_MSS::GetStaticClassDef()->GetNumObjects(); sfxNum++) 
	{	
		zCSndFX_MSS *snd = static_cast<zCSndFX_MSS*>(zCSndFX_MSS::GetStaticClassDef()->GetObjectByIndex(sfxNum));

		for (chNum=0; chNum< snd->GetNumChannels(); chNum++) 
		{

			for (frNum=0; frNum < snd->channelList[chNum]->GetNumFrames(); frNum++) 
			{
				zCSndFrame *actFr = snd->channelList[chNum]->frameList[frNum];

				if (actFr->instance == actFrameEdited->instance) 
				{
					zBOOL newWave = FALSE;
					if ( actFrameEdited->fileName  != actFr->fileName && !actFrameEdited->fileName.IsEmpty() )
					{
						newWave = TRUE;
						actFr->fileName			= actFrameEdited->fileName;
						zCActiveSnd::StopSoundsByFrame(actFr);
						actFr->CacheIn();
					}
					actFr->fileName			= actFrameEdited->fileName;
					actFr->pitchOffset		= actFrameEdited->pitchOffset;
					actFr->pitchVariance	= actFrameEdited->pitchVariance;
					actFr->defVolume		= actFrameEdited->defVolume;
					actFr->looping			= actFrameEdited->looping;
					actFr->reverbLevel		= actFrameEdited->reverbLevel;
					zCActiveSnd::UpdateSoundsByFrame(actFr);
					if (newWave) zCActiveSnd::ResumeSoundsByFrame(actFr);
				}
			}
		}
	}
}

void zCSndSys_MSS::SfxCon_ParamChanged(const zSTRING &s) 
{
	//AIL_waveOutClose(sndDrv);
	//zsound->InitializeMSS();
}


void zCSndSys_MSS :: CloseProvider() 
{
#ifdef SOUND_NIL
	return;
#endif
	 if (act3dProvider == 0) return;
	 AIL_close_3D_provider(act3dProvider);
	 act3dProvider		= 0;
	 act3dProviderIndex = -1;
	 act3dProviderName.Clear();
};



void zCSndSys_MSS :: SetNumAudioChannels		(int ch) 
{ 
	AIL_set_preference(DIG_MIXER_CHANNELS,ch); 
	zCActiveSnd::maxChannels = ch;
	prefs.numSFXChannels = ch;
};

float zCSndSys_MSS :: GetMasterVolume		()	
{ 
#ifdef MSS_VERSION_65_UP
	if ( prefs.volume == AIL_get_preference(MDI_DEFAULT_VOLUME) ) return zSND_VOL_DEFAULT;
#else
	if ( prefs.volume == AIL_get_preference(DIG_DEFAULT_VOLUME) ) return zSND_VOL_DEFAULT;
#endif
	return float( prefs.volume - MSS_VOL_MIN ) / float( MSS_VOL_MAX - MSS_VOL_MIN );
};

int	zCSndSys_MSS :: GetNumSoundsPlaying		() 
{
	int cnt = 0 ;
	for (int i=0; i<zCActiveSnd::GetNumActive(); i++) if (zCActiveSnd::activeSndList[i]->active) cnt++;
	return cnt;
};
void zCSndSys_MSS :: RemoveAllActiveSounds	() 
{
	for (int i=0; i<zCActiveSnd::GetNumActive(); i++) {
		if (zCActiveSnd::activeSndList[i]->active) zCActiveSnd::RemoveSound(zCActiveSnd::activeSndList[i]);
	}
};


void zCSndSys_MSS :: DisposeAllSampleHandles()
{
	for (int i=0; i<zCActiveSnd::GetNumActive(); i++) 
	{
		zCActiveSnd *snd = zCActiveSnd::activeSndList[i];
		if (snd->Is3DSnd()) 
		{
			H3DSAMPLE s = snd->sample3D;
			if ( s && AIL_3D_sample_status(s) != SMP_FREE ) 
			{
				AIL_end_3D_sample(s);
				AIL_release_3D_sample_handle(s);
				//while(AIL_3D_sample_status(s) != SMP_FREE );			// FIXME: darf nicht! Wieso aber bei 2d sounds ?
				snd->active  =FALSE;
				snd->sample3D=0;
			}
		}
		else 
		{
			HSAMPLE s = zCActiveSnd::activeSndList[i]->sample;
			if ( s && AIL_sample_status(s) != SMP_FREE ) 
			{
				AIL_stop_sample(s);
				AIL_release_sample_handle(s);
				while(AIL_sample_status(s) != SMP_FREE );
				snd->active =FALSE;
				snd->sample =0;
			}
		}
	}
};

void zCSndSys_MSS :: SetListener (zCVob* listenerVob) 
{ 
	zRELEASE(listener);
	if (!listenerVob) return;
	listener	= listenerVob; 
	zADDREF_ACCT(listener);
	trafoWStoLS = listener->trafoObjToWorld.InverseLinTrafo();
};

void	zCSndSys_MSS ::	SetMasterVolume(const float vol)	 
{

#ifdef SOUND_NIL
	return;
#endif

#ifdef MSS_VERSION_65_UP
	if ( vol == zSND_VOL_DEFAULT ) prefs.volume = float(MSS_VOL_MAX)/float(AIL_get_preference(MDI_DEFAULT_VOLUME)) ; 
	else prefs.volume = vol;
	AIL_set_digital_master_volume_level(sndDrv, prefs.volume);
#else
	if ( vol == zSND_VOL_DEFAULT ) prefs.volume = float(MSS_VOL_MAX)/float(AIL_get_preference(DIG_DEFAULT_VOLUME)) ; 
	else prefs.volume = vol;
	AIL_set_digital_master_volume(sndDrv,(int) Lerp( prefs.volume, MSS_VOL_MIN, MSS_VOL_MAX ));
#endif
};

void	zCSndSys_MSS ::	MuteSFX					()		 
{ 
	static float lastVol=0;
	zSwap(prefs.volume,lastVol);
#ifdef MSS_VERSION_65_UP
	AIL_set_digital_master_volume_level(sndDrv, prefs.volume);
#else
	AIL_set_digital_master_volume(sndDrv,(int) Lerp( lastVol, MSS_VOL_MIN, MSS_VOL_MAX ));
#endif
};


// LoadSoundFX 
// Parameter : Sound-Dateiname 
// only single sounds, no alternatives, no parameters

zCSoundFX*	zCSndSys_MSS :: LoadSoundFX(const zSTRING& fileName) 
{ 
#ifdef SOUND_NIL
	zERR_MESSAGE(5,0,zSTRING("C: Loading Sound ") + fileName );
	return (zCSoundFX*) zNEW(zCSndFX_MSS);
#endif

	zSTRING fName(fileName);
	fName.Upper();
	if (fName.IsEmpty()) fName = MSS_NO_WAVE;

	//zERR_WARNING("C: LoadSoundFX: " + fileName);
	
	zSTRING ext;
	if (fName.Search(".WAV") != -1) ext = ".WAV"; else if (fName.Search(".MP3") != -1) ext = ".MP3";

	if (ext == ".MP3") 
	{
		zERR_FAULT("C: SND: MP3 Files are not supported directly. You have to use a Mpeg Layer-3 file which is encapsulated into a WAV file (RIFF Format!)");
		return 0;
	}

	if (!ext.IsEmpty()) 
	{
		// Wave or mp3 File to be loaded

		zCSndFX_MSS* snd = zDYNAMIC_CAST<zCSndFX_MSS>(zCSoundFX::GetStaticClassDef()->SearchObject(DIRECTLOAD_PREFIX + fName));

		if (snd){
            zADDREF_ACCT(snd);
            return static_cast<zCSndFX_MSS*>(snd);
        }

		zCSndFX_MSS*	newSnd		= zNEW(zCSndFX_MSS);
		zCSndChannel*	newChannel	= zNEW(zCSndChannel);
		zCSndFrame*		newFrame	= zNEW(zCSndFrame);

		newFrame	->	instance = DIRECTLOAD_INSTANCENAME; 
		newFrame	->	fileName = fName;

		zERR_MESSAGE(5,0,zSTRING("C: SND: Creating Sound ") + fileName + zSTRING("   (single) "));
		newChannel	->	frameList.Insert(newFrame);
		newChannel	->	SetLoaded(TRUE);
		newSnd		->	channelList.Insert(newChannel);

		newSnd		->	SetObjectName(DIRECTLOAD_PREFIX + fName);

		return (zCSoundFX*)newSnd;
	}
	else return LoadSoundFXScript(fName);
	//zERR_WARNING("C: LoadSoundFX: End " + fileName);
}

zCSoundFX*	zCSndSys_MSS :: LoadSoundFXScript(const zSTRING& identifier) 
{ 
	
#ifdef SOUND_NIL
	zERR_MESSAGE(5,0,zSTRING("C: Loading Sound ") + identifier );
	return (zCSoundFX*) zNEW(zCSndFX_MSS);
#endif

	zSTRING id(identifier);
	id.Upper();

	//zERR_WARNING("C: LoadSoundFXScript: " + id);

	// check if identifier is valid and known in sfx.d
	if (id.IsEmpty() || (!sfxParser->GetSymbol(id))) 
	{
		zERR_WARNING("C: zSndMSS(zCSndSys_MSS::LoadSoundFXByIdentifier): Sound Identifier \"" + id + "\" unknown !");
		return 0;
	}

	// Check if frame identifier belongs to a multi-sound
	zSTRING word,name;
	int num = 1, reqChannel = 0, l= 0;
	zBOOL multi = FALSE;

	do 
	{ 
		word	  = id.PickWord(num, "_", "_");
		if ( word[0] == ID_CHANNEL_CHAR && isdigit(word[1]) ) 
		{ 
			reqChannel = word[1]-48;
			multi	= TRUE; 
			break; 
		};
		name += word ;
		l	 += word.Length();

		if ( l >= id.Length() ) 
		{ 
			name = name.PickWord(1, ".", "."); 
			break; 
		};
		name += UNDERBAR; l++;
		num++; 
	} 
	while (word.Length() > 0);

	zoptions->ChangeDir(DIR_SOUND);

	if (multi) {
		return LoadMulti(name.Copied(0,name.Length()-1),reqChannel);
	}
	else return LoadSingle(name);

	//zERR_WARNING("C: LoadSoundFXScript: End " + name);

}

zCSoundFX *zCSndSys_MSS::LoadMulti(const zSTRING &id, const int reqChannel)
{
	// if we got a multi sound, check wether it is already in the sfx List
	// multisounds names are stored as prefix only ( parameter: name_vn.wav, sfx stored
	// as name
	//zERR_WARNING("C: LoadMulti: " + id);

	zCSndFX_MSS* snd = zDYNAMIC_CAST<zCSndFX_MSS>(zCSoundFX::GetStaticClassDef()->SearchObject(id));
	
	if (snd) 
	{
		snd->LoadChannel(reqChannel);
		return snd;
	}

	// multi sound does not yet exist, so allocate new one
	// allocate multiple chord channels + possible variation frames
	zCSndFX_MSS*	newSnd		= zNEW(zCSndFX_MSS);
	zCSndChannel*	newChannel	= zNEW(zCSndChannel);

	int frCntr ;
	int chCntr = 0;
	zSTRING ch(UNDERBAR + ID_CHANNEL_CHAR + "0");
	zSTRING fr(UNDERBAR + ID_FRAME_CHAR + "0");
	int numChannels =1;

	do 
	{
		// alle channels durchgehen und allokieren
		frCntr = 0;
		zSTRING newID(id + ch) ;
		if (sfxParser->GetSymbol(newID) == 0) break;
		if (chCntr == reqChannel) newChannel ->	SetLoaded(TRUE);

		do 
		{
			// alle frames in diesem channel durchgehen und allokieren
			zCSndFrame *nextFrame = zNEW(zCSndFrame);
			sfxParser->CreateInstance(newID, nextFrame);
			nextFrame->fileName.Upper();
			if (nextFrame->fileName.IsEmpty()) nextFrame->fileName = MSS_NO_WAVE;
			nextFrame->instance = newID; // tmp

			// send spy message for frame if it belongs to the requested channel
			if (chCntr == reqChannel) 
			{
				zERR_MESSAGE(5,0,zSTRING("C: SND: Creating Sound Instance ") + id + zSTRING("   (voice: ") +zSTRING(numChannels-1) + zSTRING(" alternative:") + zSTRING(frCntr) + zSTRING(")"));
			}

			newChannel -> frameList.Insert(nextFrame);
			frCntr++;
			fr = UNDERBAR + ID_FRAME_CHAR + zSTRING(frCntr);
			newID = id + ch + fr ;

			if (sfxParser->GetSymbol(newID) == 0) break;
		} 
		while (1);

		numChannels++;
		newSnd -> channelList.Insert(newChannel);
		chCntr++;
		ch = UNDERBAR + ID_CHANNEL_CHAR + zSTRING(chCntr) ; 
		newChannel = zNEW( zCSndChannel );

	} 
	while (1);

	newSnd -> SetObjectName(id);

	//zERR_WARNING("C: LoadMulti: End " + id);

	return (zCSoundFX*)newSnd;

}


zCSoundFX *zCSndSys_MSS::LoadSingle(const zSTRING &id)
{
	// check wether sound id is already in the sfx List
	//zERR_WARNING("C: LoadSingle: " + id);
	zCSndFX_MSS* snd = zDYNAMIC_CAST<zCSndFX_MSS>(zCSoundFX::GetStaticClassDef()->SearchObject(id));

	if (snd) return static_cast<zCSoundFX*>(snd->AddRef());

	zCSndFX_MSS  *newSnd		= zNEW( zCSndFX_MSS );
	zCSndChannel *newChannel	= zNEW( zCSndChannel);
	// sound does not yet exist, so allocate new one
	int frCntr=0 ;
	zSTRING fr;
	zSTRING newID(id);

	do 
	{
		zCSndFrame *newFrame = zNEW(zCSndFrame);
		sfxParser->CreateInstance(newID, newFrame);

		newFrame->fileName.Upper();
		if (newFrame->fileName.IsEmpty()) newFrame->fileName = MSS_NO_WAVE;
		newFrame->instance = newID;
		// load wave for frame if it belongs to the requested channel
		zERR_MESSAGE(5,0,zSTRING("C: SND: Creating Sound Instance ") + id + zSTRING("   (alternative: ") +zSTRING(frCntr) + zSTRING(")"));
	
		newChannel -> frameList.Insert(newFrame);
		frCntr++;
		fr = UNDERBAR + ID_FRAME_CHAR + zSTRING(frCntr);
		newID = id + fr ;
	}
	while (sfxParser->GetSymbol(newID) != 0);

	newChannel->SetLoaded(TRUE);
	newSnd -> channelList.Insert(newChannel);
	newSnd -> SetObjectName(id);
 
	//zERR_WARNING("C: LoadSingle: End" + id);
	return (zCSoundFX*)newSnd;
}
 
zTSoundHandle zCSndSys_MSS :: PlaySound(zCSoundFX* sfx, int slot)										
{	
#ifdef SOUND_NIL
	return nilHandle++;
#endif
	// TODO: streamed audio
	if (sfx == 0) return 0;

	zCSndFX_MSS *sndFX = (zCSndFX_MSS *) sfx;
	//zERR_WARNING("C: PlaySound: " + sndFX->GetObjectName());

	sndFX -> ChooseVariance	();
	sndFX -> SetCacheOutLock(TRUE);
	sndFX -> CacheIn		(-1); // safety, for resource management
	sndFX -> GetActFrame	() -> SetDefaultProperties();

	if ( sndFX->GetActFrame()->GetWave()->CheckForCorrectFormat() == FALSE ) return 0;

	zCActiveSnd *newSound = zCActiveSnd::AllocNextFreeSnd();
	if (!newSound) return 0;
	newSound -> handle	 = zCActiveSnd::GetNextFreeHandle();;

	newSound -> sourceFrm	= sndFX->GetActFrame();
	newSound -> rate		= sndFX->GetActFrame()->CalcPitchVariance();
	newSound -> pan			= sndFX->GetActFrame()->actPan;
	newSound -> volume		= sndFX->GetActFrame()->actVolume;
	newSound -> looping     = sndFX->GetActFrame()->looping;
	newSound -> reverbLevel = GetReverbEnabled() ? sndFX->GetActFrame()->reverbLevel : 0;
	newSound -> reverbLevel*= globalReverbWeight * SOFTREVERB_SCALEFACTOR;

	if (slot != zSND_SLOT_NONE) zCActiveSnd::RemoveSoundByVobSlot(0,slot);

	if (!newSound -> RequestChannel()) return -1;  
	if (newSound->sample==0) 
	{
		zERR_WARNING("C: could not allocate sample");
		return -1;
	}

	AIL_init_sample				( newSound->sample );

	if (globalReverbPreset != 0) 
	{
		float reverbPreset = (float)globalReverbPreset;
		AIL_set_sample_processor	( newSound->sample,DP_FILTER,reverb3Filter);
		AIL_set_filter_sample_preference( newSound->sample,"Reverb EAX Environment",(void*)&reverbPreset);
		AIL_set_filter_sample_preference( newSound->sample,"Reverb Mix",(void*)&newSound->reverbLevel);
	}

	AIL_set_sample_file			( newSound->sample,(void*)sndFX->GetActFrame()->GetWave()->GetAddr(), 0);
	AIL_set_sample_playback_rate( newSound->sample, newSound->rate );
#ifdef MSS_VERSION_65_UP
	AIL_set_sample_volume_pan	( newSound->sample, (float)newSound->volume / (float)MSS_VOL_MAX, (float)newSound->pan / (float)MSS_PAN_RIGHT );
#else
	AIL_set_sample_pan			( newSound->sample, newSound->pan  );
	AIL_set_sample_volume		( newSound->sample, newSound->volume );
#endif
	AIL_set_sample_loop_block	( newSound->sample, sndFX->GetActFrame()->loopStartOffset,sndFX->GetActFrame()->loopEndOffset );
	AIL_set_sample_loop_count	( newSound->sample, !newSound->looping );	
	AIL_start_sample			( newSound->sample );
	
	zCActiveSnd::AddSound(newSound);
	D_SpyFrameInfo(newSound);

	newSound -> active	 = TRUE;
	newSound -> sourceSnd= sndFX;
	sndFX->AddRef();
	//zERR_WARNING("C: PlaySound: End" + sndFX->GetObjectName());
	return newSound -> handle; 


}

zTSoundHandle zCSndSys_MSS :: PlaySound(zCSoundFX* sfx, int slot, int freq, float vol, float pan)
{	
#ifdef SOUND_NIL
	return nilHandle++;
#endif
	// TODO: streamed audio
	if (sfx == 0) return 0;

	zCSndFX_MSS *sndFX = (zCSndFX_MSS *) sfx;
	//zERR_WARNING("C: PlaySound: " + sndFX->GetObjectName());
	
	sndFX -> ChooseVariance		();
	sndFX -> SetCacheOutLock	(TRUE);
	sndFX -> CacheIn			(-1); // safety, for resource management
	sndFX -> GetActFrame		() -> SetDefaultProperties();

	if ( sndFX->GetActFrame()->GetWave()->CheckForCorrectFormat() == FALSE ) return 0;

	zCActiveSnd *newSound = zCActiveSnd::AllocNextFreeSnd();
	if (!newSound) return 0;
	newSound -> handle = zCActiveSnd::GetNextFreeHandle();

	newSound ->	is3D		= FALSE;
	newSound -> sourceFrm	= sndFX->GetActFrame();

	if (slot != zSND_SLOT_NONE) zCActiveSnd::RemoveSoundByVobSlot(0,slot);

	if (!newSound -> RequestChannel()) return -1;  
	if (newSound->sample==0) 
	{
		zERR_WARNING("C: could not allocate sample");
		return -1;
	};

	AIL_set_sample_file(newSound->sample,(void*)sndFX->GetActFrame()->GetWave()->GetAddr(), 0);
	
	if ( pan == zSND_PAN_DEFAULT ) newSound -> pan = MSS_PAN_CENTER; 
	else 
	{
		float s = ( pan - zSND_PAN_LEFT ) / ( zSND_PAN_RIGHT - zSND_PAN_LEFT );
		newSound -> pan = (int) Lerp(s, MSS_PAN_LEFT, MSS_PAN_RIGHT);
	}
	if ( vol == zSND_VOL_DEFAULT) newSound -> volume = sndFX -> GetActFrame() -> defVolume; else
	newSound -> volume = (int) Lerp( vol, MSS_VOL_MIN, MSS_VOL_MAX );
	if ( freq == zSND_FREQ_DEFAULT ) newSound -> rate = sndFX -> GetActFrame() -> GetWave() -> GetRate(); else
	newSound -> rate			= freq;
	newSound -> looping			= sndFX->GetActFrame()->looping;
	newSound -> reverbLevel		= GetReverbEnabled() ? sndFX->GetActFrame()->reverbLevel : 0;
	newSound -> reverbLevel	   *= globalReverbWeight * SOFTREVERB_SCALEFACTOR;

	if (newSound->sample==0) zERR_WARNING("C: could not allocate sample");
	AIL_init_sample				( newSound->sample );

	if (globalReverbPreset != 0) 
	{
		float reverbPreset = (float)globalReverbPreset;
		AIL_set_sample_processor	( newSound->sample,DP_FILTER,reverb3Filter);
		AIL_set_filter_sample_preference( newSound->sample,"Reverb EAX Environment",(void*)&reverbPreset);
		AIL_set_filter_sample_preference( newSound->sample,"Reverb Mix",(void*)&newSound->reverbLevel);
	}

	AIL_set_sample_file			( newSound->sample, (void*)sndFX->GetActFrame()->GetWave()->GetAddr(), 0);
	AIL_set_sample_playback_rate( newSound->sample, newSound->rate );
#ifdef MSS_VERSION_65_UP
	AIL_set_sample_volume_pan	( newSound->sample, (float)newSound->volume / (float)MSS_VOL_MAX, (float)newSound->pan / (float)MSS_PAN_RIGHT );
#else
	AIL_set_sample_pan			( newSound->sample, newSound->pan  );
	AIL_set_sample_volume		( newSound->sample, newSound->volume );
#endif
	AIL_set_sample_loop_block	( newSound->sample, sndFX->GetActFrame()->loopStartOffset,sndFX->GetActFrame()->loopEndOffset );
	AIL_set_sample_loop_count	( newSound->sample, !newSound->looping );
	AIL_start_sample			( newSound->sample );

	newSound -> active	 = TRUE;
	newSound -> sourceSnd= sndFX;
	sndFX->AddRef();

	zCActiveSnd::AddSound(newSound);

	D_SpyFrameInfo(newSound);
	//zERR_WARNING("C: PlaySound: End" + sndFX->GetObjectName());

	return newSound -> handle; 
}

zTSoundHandle zCSndSys_MSS ::PlaySound3D(const zSTRING& fileName, zCVob* sourceVob, int slot,zTSound3DParams *sound3DParams)
{
#ifdef SOUND_NIL
	return nilHandle++;
#endif

	if (fileName.IsEmpty()) return 0;
	zCSndFX_MSS *sndFX = zDYNAMIC_CAST<zCSndFX_MSS>(LoadSoundFX(fileName));
	if (!sndFX) return 0;

	// FIXME: Autodeletion ist buggy! Orctempel Trigger Crash. Vermutlicher Fehler: Ein fehlerhaftes zCSoundFX::Release()
	// in zCSndFX_MSS::NewFrame() für Sounds mit (autoDeletion == TRUE)
//	sndFX->SetAutoDeletion(TRUE);
	sndFX->startPlayTime = ztimer.GetTotalTimeF();
	zTSoundHandle hnd = PlaySound3D(sndFX,sourceVob,slot,sound3DParams);
	zRELEASE(sndFX);
	return hnd;
};


zTSoundHandle zCSndSys_MSS :: PlaySound3D(zCSoundFX* sfx, zCVob* sourceVob, int vobSlot, zTSound3DParams *sound3DParams)	
{	
#ifdef SOUND_NIL
	return nilHandle++;
#endif

	if (sfx == 0) return 0;

	if (sound3DParams && sound3DParams->isAmbient3D) {
		// ambient 3d sounds have only a position, but no orientation
		return PlaySound3DAmbient(sfx,sourceVob,vobSlot,sound3DParams);
	}
	
	zCSndFX_MSS *sndFX = zDYNAMIC_CAST<zCSndFX_MSS>(sfx);
	zERR_ASSERTT_STRICT(sndFX,"C: PlaySound3D: Bad SFX Ptr!");

	zERR_MESSAGE(10,0,"C: SND: PlaySound3D: " + sfx->GetName() + " for vob: " + sourceVob->GetObjectName() );
	
	sndFX -> ChooseVariance	();
	sndFX -> SetCacheOutLock(TRUE);
	//zERR_MESSAGE(10,0,"C: SND: Cachein()" );
	sndFX -> CacheIn		(-1); // safety, for resource management
	sndFX -> GetActFrame	() -> SetDefaultProperties();
	
	if ( sndFX->GetActFrame()->GetWave()->CheckForCorrectFormat(TRUE) == FALSE ) return 0;

//	zERR_MESSAGE(10,0,"C: SND: Alloc Free snd" );
	zCActiveSnd *newSound = zCActiveSnd::AllocNextFreeSnd();
	if (!newSound) return 0;

	F32 coneAngleDegLocal = 360;
	
	newSound -> volWeight = 1;
	newSound -> reverbLevel = GetReverbEnabled() ? sndFX->GetActFrame()->reverbLevel : 0;

	zBOOL hasObstruction = FALSE;
	if (sound3DParams) 
	{
		newSound->obstruction = Lerp(sound3DParams->obstruction,float(0),MAX_OBSTRUCTION);
		if (newSound->obstruction>0) hasObstruction = TRUE;
		newSound->reverbLevel = GetReverbEnabled() ? sound3DParams->reverbLevel : 0;

		if (sound3DParams->coneAngleDeg==0) coneAngleDegLocal = 360;
		else coneAngleDegLocal = sound3DParams->coneAngleDeg;
		if (sound3DParams->volume == zSND_VOL_DEFAULT) newSound->volWeight = 1;
		else newSound->volWeight = sound3DParams->volume;
		if (newSound->volWeight>1) newSound->volWeight = 1;

		sndFX->GetActFrame()->CalcPitchOffset(sound3DParams->pitchOffset);
		newSound->pitchOffset = sndFX->GetActFrame()->pitchOffset;
		
		newSound->loopType = sound3DParams->loopType;
	} 

	newSound -> handle	= zCActiveSnd::GetNextFreeHandle();

	newSound -> is3D		= TRUE;
	newSound -> rate		= sndFX->GetActFrame()->CalcPitchVariance();
	newSound -> radius		= (sound3DParams == 0 || sound3DParams->radius == zSND_RADIUS_DEFAULT) ? defaultRadius : sound3DParams->radius;
	newSound -> sourceVob	= sourceVob;
//	zERR_WARNING("C: AddRef for vob " + newSound->sourceVob->GetObjectName() + " , refCtr: " + zSTRING(newSound->sourceVob->GetRefCtr()));
	zADDREF_ACCT(newSound -> sourceVob);
	
	newSound -> vobSlot		= vobSlot;
	newSound -> sourceFrm	= sndFX->GetActFrame();

	newSound -> lastPos     = sourceVob->GetPositionWorld();//sourceVob -> GetPositionWorld();
	newSound -> lastTime	= ztimer.GetTotalTimeF();

	if (newSound->loopType == zCSoundSystem::zSND_LOOPING_DEFAULT){
		newSound -> looping = sndFX->GetActFrame()->looping;
	}
	else {
		newSound -> looping = (newSound->loopType == zCSoundSystem::zSND_LOOPING_ENABLED) ? TRUE:FALSE;
	}

	if (!hasObstruction) newSound->AutoCalcObstruction(TRUE);

	newSound -> CalcListenerPan   ();
	newSound -> CalcListenerVolume();

	if ( int(Lerp(newSound -> GetVolume()*newSound->volWeight,MSS_VOL_MIN,MSS_VOL_MAX)) > 0 )
	{
		if (!newSound -> RequestChannel()) return -1;

		if (newSound->sample3D==0) 
		{
			zERR_WARNING("C: could not allocate sample");
			return -1;
		}
		
		AIL_set_3D_sample_file			( newSound->sample3D, (void*)sndFX->GetActFrame()->GetWave()->GetAddr() );
		AIL_set_3D_sample_playback_rate	( newSound->sample3D, newSound->rate );
#ifdef MSS_VERSION_65_UP
		AIL_set_3D_sample_volume		( newSound->sample3D, (float)newSound->volume / (float)MSS_VOL_MAX);
#else
		AIL_set_3D_sample_volume		( newSound->sample3D, newSound->volume);
#endif

		// neue Berechnungsmethode für den Lautstärke Verlauf:
		// ist die Distanz zum sourceVob grösser als die Minimal distanz, wird der Wert
		// bis zum Erreichen der maximal Distanz auf 0 skaliert
		// dann ist gewährleistet, das die Lautstärke beim erreichen von max_dist _immer_ 0 ist

		float origMinDist = MIN_DIST_MAX_VOL_SCALE * newSound->radius;
		float minDist	  = origMinDist;
		float actDist	  = (newSound->sourceVob->GetPositionWorld() - listener->GetPositionWorld()).LengthApprox();

		//if (act3dProviderIndex==0)			// für MILES werden alle Sounds am Radius Ende auf Lautstärke 0 gesetzt
		if ( actDist > origMinDist ) 
		{
			float minDistScale = 1- ( (actDist - origMinDist)/(newSound->radius-origMinDist) );
			minDist = origMinDist * minDistScale;
		}

		AIL_set_3D_sample_distances		( newSound->sample3D, newSound->radius*RANGE_SCALE, minDist*RANGE_SCALE );
		
		if (globalReverbWeight==0)	AIL_set_3D_sample_effects_level ( newSound->sample3D, 0 );
		else						AIL_set_3D_sample_effects_level ( newSound->sample3D, globalReverbWeight * newSound -> reverbLevel );
		
		AIL_set_3D_sample_obstruction   ( newSound->sample3D, Lerp(newSound->obstruction,float(0),MAX_OBSTRUCTION) );
		AIL_set_3D_sample_occlusion		( newSound->sample3D, globalOcclusion );
		AIL_set_3D_sample_cone			( newSound->sample3D, coneAngleDegLocal , 360 - coneAngleDegLocal, 0);
		AIL_set_3D_sample_loop_block	( newSound->sample3D, sndFX->GetActFrame()->loopStartOffset,sndFX->GetActFrame()->loopEndOffset );
		AIL_set_3D_sample_loop_count	( newSound->sample3D, !newSound->looping );

		zMAT4 trafoObjToListener = trafoWStoLS * sourceVob->trafoObjToWorld;
		zPOINT3 lws = trafoObjToListener.GetTranslation();
		zVEC3   at  = trafoObjToListener.GetAtVector();
		zVEC3   up  = trafoObjToListener.GetUpVector();
		
		if (listener == sourceVob) AIL_set_3D_position		(newSound->sample3D,0,10,0);
		else					   AIL_set_3D_position		(newSound->sample3D,lws[VX],lws[VY],lws[VZ]);

		AIL_set_3D_orientation	(newSound->sample3D,at[VX],at[VY],at[VZ],up[VX],up[VY],up[VZ]);

//		zERR_MESSAGE(10,0,"C: SND: setting eax absorption");
//		AIL_set_3D_sample_preference	( newSound->sample3D, "EAX2 sample air absorption",(void*)&EAX_AIR_ABSORPTION_DEFAULT);

		//zERR_MESSAGE(10,0,"C: SND: start" );
		AIL_start_3D_sample				( newSound->sample3D );
#ifdef DEBUG_EDENFELD
		if (AIL_3D_sample_status		(newSound->sample3D) == SMP_DONE) 
		{ 
			zERR_WARNING("C: snd is done immediately after being played: " + sndFX->GetObjectName());
		}
#endif

		newSound -> active		= TRUE;
	}

	zCActiveSnd::AddSound(newSound);
	D_SpyFrameInfo(newSound);

	newSound -> sourceSnd	= sndFX;
	sndFX->AddRef();
	//zERR_MESSAGE(10,0,"C: SND: end" );

	return newSound -> handle; 
}



zTSoundHandle zCSndSys_MSS :: PlaySound3DAmbient(zCSoundFX* sfx, zCVob* sourceVob, int vobSlot, zTSound3DParams *sound3DParams)	
{	
	zCSndFX_MSS *sndFX = zDYNAMIC_CAST<zCSndFX_MSS>(sfx);
	zERR_ASSERTT_STRICT(sndFX,"C: PlaySound3DAmbient: Bad SFX Ptr!");
	//zERR_WARNING("C: PlaySound3DAmbient: " + sndFX->GetObjectName());

	zERR_MESSAGE(10,0,"C: PlaySound3DAmbient: " + sfx->GetName() + " for vob: " + sourceVob->GetObjectName() );

	sndFX -> ChooseVariance	();
	sndFX -> SetCacheOutLock(TRUE);
	sndFX -> CacheIn		(-1); // safety
	sndFX -> GetActFrame	() -> SetDefaultProperties();

	if ( sndFX->GetActFrame()->GetWave()->CheckForCorrectFormat() == FALSE ) return 0;

	zCActiveSnd *newSound = zCActiveSnd::AllocNextFreeSnd();
	if (!newSound) return 0;

	newSound -> volWeight  = 1;
	newSound -> reverbLevel= GetReverbEnabled() ? sndFX->GetActFrame()->reverbLevel : 0;
	zBOOL hasObstruction = FALSE;
	if (sound3DParams) 
	{
		sndFX->GetActFrame()->CalcPitchOffset(sound3DParams->pitchOffset);
		newSound->pitchOffset = sndFX->GetActFrame()->pitchOffset;
		newSound->obstruction = Lerp(sound3DParams->obstruction,float(0),MAX_OBSTRUCTION);
		if (newSound->obstruction>0) hasObstruction = TRUE;
		newSound->reverbLevel = sound3DParams->reverbLevel;

		if (sound3DParams->volume == zSND_VOL_DEFAULT) newSound->volWeight = 1;
		else newSound->volWeight = sound3DParams->volume;
		if (newSound->volWeight>1) newSound->volWeight = 1;
		newSound->loopType = sound3DParams->loopType;
	} 

	newSound -> handle = zCActiveSnd::GetNextFreeHandle();
	newSound -> sourceFrm	= sndFX->GetActFrame();

	if (vobSlot != zSND_SLOT_NONE) zCActiveSnd::RemoveSoundByVobSlot(sourceVob,vobSlot);

	newSound -> pan = MSS_PAN_CENTER; 

	newSound -> rate		= sndFX->GetActFrame()->CalcPitchVariance();
	newSound -> radius		= (sound3DParams == 0 || sound3DParams->radius == zSND_RADIUS_DEFAULT) ? defaultRadius : sound3DParams->radius;
	newSound -> sourceVob	= sourceVob;
	newSound -> sourceVob -> AddRef();
	newSound -> vobSlot		= vobSlot;
	newSound -> isAmbient   = TRUE;

	if (newSound->loopType == zCSoundSystem::zSND_LOOPING_DEFAULT){
		newSound -> looping = sndFX->GetActFrame()->looping;
	}
	else {
		newSound -> looping = (newSound->loopType == zCSoundSystem::zSND_LOOPING_ENABLED) ? TRUE:FALSE;
	}

	newSound -> reverbLevel*= globalReverbWeight * SOFTREVERB_SCALEFACTOR;

	if (!hasObstruction) newSound->AutoCalcObstruction(TRUE);
	newSound -> CalcListenerVolume();

	if ( newSound->volume > 0 )
	{
		if (!newSound -> RequestChannel()) 
		{
			return -1;
		}
		if (newSound->sample==0) 
		{
			zERR_WARNING("C: could not allocate sample");
			return -1;
		}

		float cutoff	   = Lerp(globalOcclusion,20000.0F,200.0F);

		if (newSound->sample==0) zERR_WARNING("C: could not allocate sample");
		AIL_init_sample				( newSound->sample );
		AIL_set_sample_file			( newSound->sample, (void*)sndFX->GetActFrame()->GetWave()->GetAddr(), 0);
		AIL_set_sample_playback_rate( newSound->sample, newSound->rate );
#ifdef MSS_VERSION_65_UP
		AIL_set_sample_volume_pan	( newSound->sample, (float)((1-newSound->obstruction) * newSound->volume) / (float)MSS_VOL_MAX, (float)newSound->pan / (float)MSS_PAN_RIGHT );
#else
		AIL_set_sample_pan			( newSound->sample, newSound->pan  );
		AIL_set_sample_volume		( newSound->sample, (1-newSound->obstruction) * newSound->volume );
#endif
		AIL_set_sample_processor	( newSound->sample,DP_FILTER,reverb3Filter);
		float reverbPreset = (float)globalReverbPreset;
		AIL_set_filter_sample_preference( newSound->sample,"Reverb EAX Environment",(void*)&reverbPreset);
		if (globalReverbPreset==0) 	AIL_set_filter_sample_preference( newSound->sample,"Reverb Mix",(void*)&CONST_ZERO);
		else						AIL_set_filter_sample_preference( newSound->sample,"Reverb Mix",(void*)&newSound->reverbLevel);
		AIL_set_filter_sample_preference( newSound->sample,"Lowpass Cutoff",(void*)&cutoff);
		AIL_set_sample_loop_block	( newSound->sample, sndFX->GetActFrame()->loopStartOffset,sndFX->GetActFrame()->loopEndOffset );
		AIL_set_sample_loop_count	( newSound->sample, !newSound->looping );
		AIL_start_sample			( newSound->sample );
#ifdef DEBUG_EDENFELD
		if (AIL_3D_sample_status		(newSound->sample3D) == SMP_DONE) 
		{ 
			zERR_WARNING("C: snd is done immediately after being played: " + sndFX->GetObjectName());
		}
#endif


		newSound -> active	 = TRUE;
	}

	newSound -> sourceSnd= sndFX;
	sndFX->AddRef();

	zCActiveSnd::AddSound(newSound);
	D_SpyFrameInfo(newSound);
	//zERR_WARNING("C: PlaySound3DAmbient: End" + sndFX->GetObjectName());

	return newSound -> handle; 

}

void zCSndSys_MSS :: StopSound	(const zTSoundHandle& sfxHandle) 
{
#ifdef SOUND_NIL
	return;
#endif

	zCActiveSnd *snd = zCActiveSnd :: GetHandleSound(sfxHandle);
	if (snd) zCActiveSnd::RemoveSound(snd);
}


void zCSndSys_MSS :: StopAllSounds() 
{
#ifdef SOUND_NIL
	return;
#endif
	for (int i=zCActiveSnd::activeSndList.GetNum()-1; i>=0; i--)
	{
		if (zCActiveSnd::activeSndList[i]->sourceSnd && zCActiveSnd::activeSndList[i]->sourceSnd->GetIsFixed()) continue;
		zCActiveSnd::RemoveSound(zCActiveSnd::activeSndList[i]);
	}
	handleMan.DisposeAllSamples();
}


zBOOL zCSndSys_MSS :: UpdateSound3D	(const zTSoundHandle& sfxHandle, zTSound3DParams *sound3DParams) 
{
/*	    Lautstärke == 0: 
		  sound aktiv ? ja:   Pause, aktiv auf FALSE setzen
		                nein: -
		Lautstärke > 0:
		  sound aktiv ? ja:   Vol/Pan/Rate Update
		                nein: aktiv = TRUE, HSAMPLE != 0 ? ja: resume sound, nein: RequestChannel(), 
						Assign HSAMPLE, Reset Values, Play
*/
#ifdef SOUND_NIL
	return TRUE;
#endif

	//zERR_MESSAGE(5,0,"C: UpdateSound3D called");
	
	
	if (sfxHandle == -1) return FALSE;
	zCActiveSnd *snd = zCActiveSnd :: GetHandleSound(sfxHandle);

	if (snd && !snd->HasBeenUpdatedThisFrame() ) 
	{
		snd->sourceSnd->CacheIn();

		if (listener && listener->GetHomeWorld()) snd->frameCtr = listener->GetHomeWorld()->GetMasterFrameCtr();

		if ( snd->sourceSnd->GetCacheState()!=zRES_CACHED_IN ) return TRUE;

		//zERR_WARNING("C: UpdateSound3d : " + snd->sourceFrm->fileName);

		if (!snd->sourceVob) return FALSE;		// FIXME: Nötig ?

		if (snd->IsAmbient()) 
		{
			UpdateSoundPropsAmbient(snd,sound3DParams);
			return TRUE;
		}

		zBOOL hasObstruction = FALSE;
		if (sound3DParams) 
		{
			// FIXME: Realtime modification of the radius does not work (yet?)!
			if (sound3DParams->radius == zSND_RADIUS_DEFAULT) snd->radius = defaultRadius;
			else snd->radius = sound3DParams->radius;
			if (sound3DParams->volume == zSND_VOL_DEFAULT) snd->volWeight = 1;
			else snd->volWeight = sound3DParams->volume;
			if (snd->volWeight>1) snd->volWeight = 1;
			snd->loopType = sound3DParams->loopType;
			if (sound3DParams->obstruction>0) hasObstruction = TRUE;
		}

		if (!hasObstruction) snd->AutoCalcObstruction();

		if ( int(Lerp(snd -> GetVolume()*snd->volWeight,MSS_VOL_MIN,MSS_VOL_MAX)) > 0 ) 
		{
			zBOOL resumed = TRUE;

			if ( snd->sample3D==0 ) 
			{
				//zERR_WARNING("C: wav:" + snd->sourceFrm->fileName + " has been reactivated");
				if (!snd->RequestChannel()) return FALSE;  

				assert(snd->sourceFrm->GetWave()->GetAddr()!=0);
				if (snd->sample3D==0) 
				{
					zERR_WARNING("C: could not allocate sample");
					return FALSE;
				}
				AIL_set_3D_sample_file			( snd->sample3D, (void*)snd->sourceFrm->GetWave()->GetAddr() );
				//AIL_set_3D_sample_preference	( snd->sample3D, "EAX2 sample air absorption",(void*)&EAX_AIR_ABSORPTION_DEFAULT);
				snd->muteTime	=	0;
				resumed			=	FALSE;
			}

			F32 cone = 0;
			if (sound3DParams) 
			{
				if (sound3DParams->coneAngleDeg==0) cone = 360;
				else cone = sound3DParams->coneAngleDeg;
				AIL_set_3D_sample_cone			( snd->sample3D, cone, 360 - cone, 0);
				AIL_set_3D_sample_obstruction   ( snd->sample3D, Lerp(sound3DParams->obstruction,float(0),MAX_OBSTRUCTION) );
				snd->reverbLevel = GetReverbEnabled() ? sound3DParams->reverbLevel : 0;
			}
			snd -> CalcListenerVolume();

			// FIXME: hier sind nicht immer alle Updates nötig, evtl. nur beim resumen/restarten			
			AIL_set_3D_sample_occlusion		( snd->sample3D, globalOcclusion );
			AIL_set_3D_sample_playback_rate	( snd->sample3D, snd->rate );

			// neue Berechnungsmethode für den Lautstärke Verlauf:
			// ist die Distanz zum sourceVob grösser als die Minimal distanz, wird der Wert
			// bis zum Erreichen der maximal Distanz auf 0 skaliert
			// dann ist gewährleistet, das die Lautstärke beim erreichen von max_dist _immer_ 0 ist
			// (FIXME: allerdings klingt dann absolut jeder sound in der nähe von max_dist gleich dumpf, egal wie gross
			// max_dist ist)
			// Update: Dieses Fragment ist hier vielleicht unsinnig, denn die distanz wurde ja bereits
			// zu start festgelegt, oder ?

			float origMinDist = MIN_DIST_MAX_VOL_SCALE * snd->radius;
			float minDist	  = origMinDist;
			float actDist	  = (snd->sourceVob->GetPositionWorld() - listener->GetPositionWorld()).LengthApprox();

			if ( actDist > origMinDist ) 
			{
				if ( (snd->radius-origMinDist) != 0 ) 
				{
					float minDistScale = 1- ( (actDist - origMinDist)/(snd->radius-origMinDist) );
					minDist = origMinDist * minDistScale;
				}
			}

			AIL_set_3D_sample_distances		( snd->sample3D, snd->radius*RANGE_SCALE, minDist*RANGE_SCALE);

#ifdef MSS_VERSION_65_UP
			AIL_set_3D_sample_volume		( snd->sample3D, (float)snd->volume / (float)MSS_VOL_MAX);
#else
			AIL_set_3D_sample_volume		( snd->sample3D, snd->volume);
#endif

			if (globalReverbWeight==0)	AIL_set_3D_sample_effects_level ( snd->sample3D, 0 );
			else						AIL_set_3D_sample_effects_level ( snd->sample3D, globalReverbWeight * snd-> reverbLevel );

			AIL_set_3D_sample_loop_block	( snd->sample3D, snd->sourceFrm->loopStartOffset,snd->sourceFrm->loopEndOffset );

			if (snd->loopType == zCSoundSystem::zSND_LOOPING_DEFAULT){
				snd -> looping = snd->sourceFrm->looping;
			}
			else {
				snd -> looping = (snd->loopType == zCSoundSystem::zSND_LOOPING_ENABLED) ? TRUE:FALSE;
			}

			AIL_set_3D_sample_loop_count	( snd->sample3D, !snd->looping );

			//get trafo object -> listener
			zMAT4 trafoObjToListener = trafoWStoLS * snd->sourceVob->trafoObjToWorld;
			
			float   thisTime	= ztimer.GetTotalTimeF();
			float   deltaT		= (thisTime - snd->lastTime);
			zPOINT3 lws			= trafoObjToListener.GetTranslation();
			zVEC3   at			= trafoObjToListener.GetAtVector();
			zVEC3   up			= trafoObjToListener.GetUpVector();
			zVEC3   dvec		= zVEC3(0,0,0);
			zVEC3   center		= snd->sourceVob->GetPositionWorld();
			if (deltaT>0) dvec  = (center - snd->lastPos)/(deltaT*100);

			snd->lastPos		= center;
			snd->lastTime		= thisTime;

			if (listener == snd->sourceVob) AIL_set_3D_position			(snd->sample3D,0,10,0);
			else							AIL_set_3D_position			(snd->sample3D,lws[VX],lws[VY],lws[VZ]);

			AIL_set_3D_orientation		(snd->sample3D,at[VX],at[VY],at[VZ],up[VX],up[VY],up[VZ]);
			AIL_set_3D_velocity_vector	(snd->sample3D,dvec[VX],dvec[VY],dvec[VZ]);

			if (!snd->active) 
			{
				snd->active   = TRUE;
				snd->muteTime = 0;
				if ( resumed ) 	AIL_resume_3D_sample( snd->sample3D ); 
				else			AIL_start_3D_sample	( snd->sample3D );
			}
		} 
		else if ( snd->active ) 
		{
			//zERR_WARNING("C: wav:" + snd->sourceFrm->fileName + " has been stopped");
			snd->active = FALSE;
			AIL_stop_3D_sample(snd->sample3D);
		}

		return TRUE;
		//zERR_WARNING("C: UpdateSound3d : End" + snd->sourceFrm->fileName);
	} 
	return FALSE;
}						

void zCSndSys_MSS :: UpdateSoundPropsAmbient(zCActiveSnd *snd, zTSound3DParams *sound3DParams) 
{
//	    Lautstärke == 0: 
//		sound aktiv ? ja:   Muten, aktiv auf FALSE setzen
//	                nein: -
//		Lautstärke > 0:
//		sound aktiv ? ja:   Vol/Pan/Rate Update
//					  nein: aktiv = TRUE, HSAMPLE != 0 ? ja: resume sound, nein: RequestChannel(), 
//						    Assign HSAMPLE, Vol/Pan/Rate Update, Play
	zBOOL hasObstruction = FALSE;		
	if (sound3DParams) 
	{
		if (sound3DParams->radius == zSND_RADIUS_DEFAULT) snd->radius = defaultRadius;
		else snd->radius = sound3DParams->radius;
		if (sound3DParams->volume == zSND_VOL_DEFAULT) snd->volWeight = 1;
		else snd->volWeight = sound3DParams->volume;
		if (snd->volWeight>1) snd->volWeight = 1;
		snd->loopType = sound3DParams->loopType;
		if (sound3DParams->obstruction>0) hasObstruction = TRUE;
	}

	if (!hasObstruction) snd->AutoCalcObstruction();
	snd -> CalcListenerVolume();

	if ( snd->volume > 0 ) 
	{
		zBOOL resumed = TRUE;
		if ( snd->sample==0 ) 
		{
			if (!snd->RequestChannel()) return;  // FIXME: RequestChannel könnte return Wert zurückgeben
			if (snd->sample==0)
			{
				zERR_WARNING("C: could not allocate sample");
				return;
			}
			AIL_init_sample				( snd->sample );
			AIL_set_sample_file			( snd->sample, (void*)snd->sourceFrm->GetWave()->GetAddr(), 0 );
			AIL_set_sample_processor	( snd->sample,DP_FILTER,reverb3Filter);
			snd->muteTime	=	0;
			resumed			=	FALSE;
		}

		if (sound3DParams) 
		{
			snd->obstruction = Lerp(sound3DParams->obstruction,float(0),MAX_OBSTRUCTION);
			snd->reverbLevel = GetReverbEnabled() ? sound3DParams->reverbLevel : 0;
		}


		float cutoff	   = Lerp(globalOcclusion,20000.0F,200.0F);

		AIL_set_sample_playback_rate( snd->sample, snd->rate );
#ifdef MSS_VERSION_65_UP
		AIL_set_sample_volume_pan	( snd->sample, (float)((1-snd->obstruction) * (snd->volume*snd->volWeight)) / (float)MSS_VOL_MAX, (float)snd->pan / (float)MSS_PAN_RIGHT );
#else
		AIL_set_sample_pan			( snd->sample, snd->pan  );
		AIL_set_sample_volume		( snd->sample, (1-snd->obstruction) * (snd->volume*snd->volWeight) );
#endif
		AIL_set_sample_loop_block	( snd->sample, snd->sourceFrm->loopStartOffset,snd->sourceFrm->loopEndOffset );

		if (snd->loopType == zCSoundSystem::zSND_LOOPING_DEFAULT){
			snd-> looping = snd->sourceFrm->looping;
		}
		else {
			snd -> looping = (snd->loopType == zCSoundSystem::zSND_LOOPING_ENABLED) ? TRUE:FALSE;
		}

		AIL_set_sample_loop_count	( snd->sample, !snd->looping );

		if (GetReverbEnabled())
		{
			float reverbPreset = (float)globalReverbPreset;
			AIL_set_filter_sample_preference( snd->sample,"Reverb EAX Environment",(void*)&reverbPreset);
			if (globalReverbPreset ==0) AIL_set_filter_sample_preference( snd->sample,"Reverb Mix",(void*)&CONST_ZERO);
			else						AIL_set_filter_sample_preference( snd->sample,"Reverb Mix",(void*)&snd->reverbLevel);
		}
		AIL_set_filter_sample_preference( snd->sample,"Lowpass Cutoff",(void*)&cutoff);

		if (!snd->active) 
		{
			snd->active	  = TRUE;
			snd->muteTime = 0;
			if ( resumed ) AIL_resume_sample(snd->sample); 
			else AIL_start_sample( snd->sample );
		}
	} 
	else if ( snd->active ) 
	{
		snd->active = FALSE;
		AIL_stop_sample(snd->sample);
	}

}


void zCSndSys_MSS :: GetSoundProps	(const zTSoundHandle& sfxHandle, int &freq, float &vol, float &pan) 
{

#ifdef SOUND_NIL
	return ;
#endif

	zCActiveSnd *snd = zCActiveSnd :: GetHandleSound(sfxHandle);
	if (!snd) 
	{ 
		zERR_WARNING("C: zSndMSS.cpp(zCSndSys_MSS::GetSoundProps): Handle not used!");
		vol = 0; 
		freq= zSND_FREQ_DEFAULT;
		pan = zSND_PAN_DEFAULT;
		return;
	}

	if ( snd->volume == snd->sourceFrm->defVolume ) vol=zSND_VOL_DEFAULT;
	else vol = float( snd->volume - MSS_VOL_MIN ) / float( MSS_VOL_MAX - MSS_VOL_MIN );
	
	if ( snd->pan == MSS_PAN_CENTER ) pan = zSND_PAN_DEFAULT;
	else 
	{
		float s = float( snd->pan -  MSS_PAN_LEFT ) / float( MSS_PAN_RIGHT - MSS_PAN_LEFT );
		pan = Lerp( s, zSND_PAN_LEFT, zSND_PAN_RIGHT ) ;
	}

	if ( snd->rate == snd->sourceFrm->GetWave()->GetRate() ) freq = zSND_FREQ_DEFAULT; else freq= snd->rate;

}

zBOOL zCSndSys_MSS :: GetSound3DProps(const zTSoundHandle& sfxHandle, zTSound3DParams &sound3DParams)
{
#ifdef SOUND_NIL
	return TRUE;
#endif

	zCActiveSnd *snd = zCActiveSnd :: GetHandleSound(sfxHandle);

	if (!snd) 
	{
		sound3DParams.SetDefaults();
		return FALSE;
	}

	if (snd->Is3DSnd()) 
	{
#ifdef MSS_VERSION_65_UP
		F32 tmp, tmp2;
		AIL_3D_sample_cone		(snd->sample3D,&sound3DParams.coneAngleDeg,&tmp,&tmp2);
#else
		F32 tmp; long tmp2;	// FIXME:necessary ?
		AIL_3D_sample_cone		(snd->sample3D,&sound3DParams.coneAngleDeg,&tmp,&tmp2);
#endif
	}

	sound3DParams.obstruction = snd->obstruction/MAX_OBSTRUCTION;
	sound3DParams.radius	  = snd->radius;
	sound3DParams.reverbLevel = GetReverbEnabled() ? snd->reverbLevel : 0;
	sound3DParams.volume      = snd->volWeight;
	sound3DParams.isAmbient3D = snd->IsAmbient();
	sound3DParams.pitchOffset = snd->pitchOffset;
	sound3DParams.loopType	  = snd->loopType;

	return TRUE;
};


float zCSndSys_MSS :: GetActiveVolume(const zTSoundHandle& sfxHandle)
{
	zCActiveSnd *snd = zCActiveSnd :: GetHandleSound(sfxHandle);
	if (snd) return snd->GetVolume()*snd->volWeight;
	return -1;
};


		
void zCSndSys_MSS :: UpdateSoundProps(const zTSoundHandle& sfxHandle, int freq, float vol, float pan) 
{
//	    Lautstärke == 0: 
//		sound aktiv ? ja:   Muten, aktiv auf FALSE setzen
//	                nein: -
//		Lautstärke > 0:
//		sound aktiv ? ja:   Vol/Pan/Rate Update
//					  nein: aktiv = TRUE, HSAMPLE != 0 ? ja: resume sound, nein: RequestChannel(), 
//						    Assign HSAMPLE, Vol/Pan/Rate Update, Play
// TODO: 3d sounds ??
#ifdef SOUND_NIL
	return;
#endif
	zCActiveSnd *snd = zCActiveSnd :: GetHandleSound(sfxHandle);

	if (snd) 
	{
		if (snd->Is3DSnd()) 
		{
			zERR_WARNING("C: shit happens: a sound which should be an ambient sound is suddenly 3d, what the heck!!??!!");
			return;
		}

		if ( pan == zSND_PAN_DEFAULT ) snd->pan = MSS_PAN_CENTER;
		else 
		{
			float s = ( pan - zSND_PAN_LEFT ) / ( zSND_PAN_RIGHT - zSND_PAN_LEFT );
			snd->pan = (int) Lerp(s, MSS_PAN_LEFT, MSS_PAN_RIGHT);
		}

		if ( vol == zSND_VOL_DEFAULT ) snd->volume = snd->sourceFrm->defVolume; 
		else snd->volume = (int) Lerp( vol, MSS_VOL_MIN, MSS_VOL_MAX );

		if ( freq == zSND_FREQ_DEFAULT ) snd->rate	= snd->sourceFrm->GetWave()->GetRate(); 
		else snd->rate = freq;
		
		
		if ( snd->volume > 0 ) 
		{
			zBOOL resumed = TRUE;
			if ( snd->sample==0 ) 
			{
				if (!snd->RequestChannel()) return ;  
				if (!snd->sample) 
				{
					zERR_WARNING("C: could not allocate sample for 2d sound");
					return;
				}

				AIL_init_sample				( snd->sample );
				AIL_set_sample_file			( snd->sample, (void*)snd->sourceFrm->GetWave()->GetAddr(), 0 );

				if (globalReverbPreset!=0)
				{
					AIL_set_sample_processor	( snd->sample,DP_FILTER,reverb3Filter);
				}
				snd->muteTime=0;
				resumed = FALSE;
			}

			AIL_set_sample_playback_rate( snd->sample, snd->rate );
#ifdef MSS_VERSION_65_UP
			AIL_set_sample_volume_pan	( snd->sample, (float)snd->volume / (float)MSS_VOL_MAX, (float)snd->pan / (float)MSS_PAN_RIGHT );
#else
			AIL_set_sample_pan			( snd->sample, snd->pan  );
			AIL_set_sample_volume		( snd->sample, snd->volume );
#endif
			
			if (globalReverbPreset !=0 && GetReverbEnabled()) 
			{
				float reverbPreset = (float)globalReverbPreset;
				AIL_set_filter_sample_preference( snd->sample,"Reverb EAX Environment",(void*)&reverbPreset);
				AIL_set_filter_sample_preference( snd->sample,"Reverb Mix",(void*)&snd->reverbLevel);
			}

			AIL_set_sample_loop_block	( snd->sample, snd->sourceFrm->loopStartOffset,snd->sourceFrm->loopEndOffset );
			AIL_set_sample_loop_count	( snd->sample, !snd->looping );


			if (!snd->active) 
			{
				snd->active	  = TRUE;
				snd->muteTime = 0;
				if ( resumed ) AIL_resume_sample(snd->sample); 
				else AIL_start_sample( snd->sample );
			}
		} 
		else if ( snd->active ) 
		{
			snd->active = FALSE;
			AIL_stop_sample(snd->sample);
		}

	}

}




void zCSndSys_MSS ::	DoSoundUpdate()
{
#ifdef SOUND_NIL
	return ;
#endif

	if (d_noUpdate) return;

#ifdef CHECK_WAVREFCTR
	// für jedes Wave File überprüfen, ob der RefCtr stimmt
	for (int w=0; w<zCWaveData::loadedList.GetNumInList(); w++) {
		zCWaveData *wav = zCWaveData::loadedList[w]; 
		int refCtr = 0;

		for (int i=0; i<zCSndFX_MSS::GetStaticClassDef()->GetNumObjects(); i++) {
			zCSndFX_MSS * snd = (zCSndFX_MSS*)zCSndFX_MSS::GetStaticClassDef()->GetObjectByIndex(i);
			for (int c=0; c<snd->GetNumChannels(); c++) {

				for (int f=0; f<snd->GetNumChannelFrames(c); f++) {
					zCSndFrame *frm = snd->GetFrame(c,f);
					if (frm->GetWave() == wav) {
						refCtr ++;
					}
				}
			}
		}

		assert(wav->GetRefCtr() == refCtr);
	}
#endif

	if (listener) trafoWStoLS = listener->trafoObjToWorld.InverseLinTrafo();

	zCWavePool	 :: GetPool().NewFrame();	
	zCActiveSnd  :: NewFrame();
	zCSndFX_MSS  :: NewFrame();

}

zBOOL zCSndSys_MSS ::IsSoundActive(const zTSoundHandle& sfxHandle) 
{
#ifdef SOUND_NIL
	return TRUE;
#endif

	return zCActiveSnd::GetHandleActive(sfxHandle);
}


float zCSndSys_MSS :: GetPlayingTimeMSEC		(const zSTRING& fileName)
{
#ifdef SOUND_NIL
	return 0;
#endif
	
	if (fileName.IsEmpty()) return 0;
	
	zSTRING name = fileName;
	if (fileName.Search(".WAV") != -1) name = DIRECTLOAD_PREFIX + fileName;

	zCSndFX_MSS *snd = zDYNAMIC_CAST<zCSndFX_MSS>(zCSoundFX::GetStaticClassDef()->SearchObject(name));
	if (snd) return snd->GetPlayingTimeMSEC();

	return 0;
};

zCParser* zCSndSys_MSS::GetSFXParser() 
{
	return sfxParser;
};

int zCSndSys_MSS ::GetUsedSoundMem() 
{
	return sndMemUsed;
};

void zCSndSys_MSS :: SetGlobalReverbPreset	(int i, float weight)
{
	
#ifdef SOUND_NIL
	return;
#endif
	//i = 0; weight = 0;

	if (!m_bReverbEnabled) return;
	float realWeight = weight;
	
	if ( act3dProviderName != PROV_EAX2 ) realWeight*=SOFTREVERB_SCALEFACTOR;
 
	if ( (globalReverbPreset==i) && (globalReverbWeight == realWeight) ) return;

	// bei eax wird der room preset auf sewerpipe umgeleitet
	//if (act3dProviderIndex==2 && i==2) { weight=1; };

	AIL_set_3D_room_type(act3dProvider,i);

	// nun für alle gerade gespielten sounds den reverb weight updaten
	
	globalReverbPreset = i;
	if (globalReverbPreset !=0 ) globalReverbWeight = realWeight;
	else						 globalReverbWeight = 0;

//	zCActiveSnd::UpdateReverb(globalReverbWeight);		// nicht nötig, UpdateSound3D() erledigt das.
};

void	zCSndSys_MSS ::	SetReverbEnabled		(const zBOOL bReverbEn) 
{ 
	if (m_bReverbEnabled && !bReverbEn) SetGlobalReverbPreset(0,0);
	m_bReverbEnabled = bReverbEn;
}; 

// Sound Provider
int	zCSndSys_MSS ::	GetNumProvider			()
{
	zBOOL allProviders = zoptions->ReadInt(zOPT_SEC_SOUND,	"extendedProviders",	FALSE);
	if (allProviders) return NUM_PROVIDERS;
	else return 3;
};

const zSTRING* zCSndSys_MSS :: GetProviderName			(int i)
{
	zERR_ASSERT(i<GetNumProvider());
	return &s_m3d_names[(i<<2)+1];
};

zBOOL zCSndSys_MSS :: SetProvider	(int index)
{
	//zoptions->WriteString( zOPT_SEC_SOUND, ZOPT_SND_3DPROV.ToChar(), s_m3d_names[index<<2]);
	return TRUE;
};

zBOOL zCSndSys_MSS :: Start3DProvider	(int index)
{
	char*		name;
	int			n				= 0;
	HPROENUM	next			= HPROENUM_FIRST;
	zBOOL		foundProvider	= FALSE;
	HPROVIDER	provider;

	while (AIL_enumerate_3D_providers(&next, &provider, &name)) 
	{
		zERR_MESSAGE(5,0,"C: found 3d sound provider: " + zSTRING(name));
		n++;
		if (name == s_m3d_names[(index<<2)+3])
		{
			foundProvider = TRUE;
			break;
		}
	}
	prefs.numProviders = n;
	zERR_ASSERTT_STRICT( n > 0 && foundProvider,"illegal number of provider found. there has to be at least one M3D provider in the system directory!" )

	zDWORD res = AIL_open_3D_provider(provider);
    
	if (res == M3D_NOERR) 
	{
		AIL_3D_provider_attribute(act3dProvider, "EAX environment selection", &res);
		act3dProvider	   = provider;
		act3dProviderIndex = index;
		act3dProviderName  = name;
		// provider abhängige konstanten setzen
		// 0.05f: eax2, 1.0f mss soft, 0.15 ds hw
		/*if (act3dProviderIndex==0)	RANGE_SCALE = 1.0f; else 
		if (act3dProviderIndex==1)	RANGE_SCALE = 0.15f; else 
		if (act3dProviderIndex==2)	RANGE_SCALE = 0.05f; */

		AIL_set_3D_distance_factor(act3dProvider, s_m3d_distance_factors[act3dProviderIndex]);

		zERR_MESSAGE(5,0,"C: used 3d sound provider: " + act3dProviderName);
		return TRUE;
	} 
	else 
	{
		// sound ging nicht mit dem gewünschten provider, dann den default nehmen, 
		zERR_WARNING("C: could not initialize 3d provider, reason: " + zSTRING(AIL_last_error()));
		
		int currentProvIndex = ProviderOptNameToIndex (zSND_DEFAULT_PROVIDER);
		zoptions->WriteInt(zOPT_SEC_INTERNAL,	"soundProviderIndex",	currentProvIndex);

		next = HPROENUM_FIRST;
		while (AIL_enumerate_3D_providers(&next, &provider, &name)) 
		{
			zERR_MESSAGE(5,0,"C: found 3d sound provider: " + zSTRING(name));
			n++;
			if (name == s_m3d_names[(currentProvIndex<<2)+3])
			{
				foundProvider = TRUE;
				break;
			};
		}
		zERR_ASSERTT_STRICT( n > 0 && foundProvider,"illegal number of provider found. there has to be at least one M3D provider in the system directory!" )

		res = AIL_open_3D_provider(provider);
    
		if (res == M3D_NOERR) 
		{
			act3dProvider	   = provider;
			act3dProviderIndex = currentProvIndex;
			act3dProviderName  = name;

			// provider abhängige konstanten setzen
			// 0.05f: eax2, 1.0f mss soft, 0.15 ds hw
			/*if (act3dProviderIndex==0)	RANGE_SCALE = 1.0f; else 
			if (act3dProviderIndex==1)	RANGE_SCALE = 0.15f; else 
			if (act3dProviderIndex==2)	RANGE_SCALE = 0.05f; */

			AIL_set_3D_distance_factor(act3dProvider, s_m3d_distance_factors[act3dProviderIndex]);
			//AIL_set_3D_doppler_factor(act3dProvider, 0);
			
			zERR_MESSAGE(5,0,"C: used 3d sound provider: " + act3dProviderName);
			return TRUE;
		}
		else
		{
			zERR_WARNING("C: could not initialize 3d provider, reason: " + zSTRING(AIL_last_error()));
		}

	}

	// something went wrong. caller has to avoid illegal 3d provider if returning false
	return FALSE;
}

// misc
// range: [0;1] percent, for global damping effects (like underwater), modulates obstruction of individual sounds
void	zCSndSys_MSS :: SetGlobalOcclusion (float occlusion)
{
	globalOcclusion = occlusion;
};

float	zCSndSys_MSS :: GetCPULoad				()
{
#ifdef SOUND_NIL
	return 0;
#endif

	return float(AIL_digital_CPU_percent(sndDrv))/100.0F;
};

void zCSndSys_MSS :: SetSpeakerType(const zTSpeakerType speakerType)
{
#ifdef SOUND_NIL
	return;
#endif

	switch (speakerType) 
	{
	case zSPEAKER_TYPE_2_SPEAKER:	AIL_set_3D_speaker_type(act3dProvider,AIL_3D_2_SPEAKER); break;
	case zSPEAKER_TYPE_4_SPEAKER:	AIL_set_3D_speaker_type(act3dProvider,AIL_3D_4_SPEAKER); break;
	case zSPEAKER_TYPE_HEADPHONE:	AIL_set_3D_speaker_type(act3dProvider,AIL_3D_HEADPHONE); break;
	case zSPEAKER_TYPE_SURROUND:	AIL_set_3D_speaker_type(act3dProvider,AIL_3D_SURROUND);  break;
#ifdef MSS_VERSION_65_UP
	case zSPEAKER_TYPE_51_SPEAKER:	AIL_set_3D_speaker_type(act3dProvider,AIL_3D_51_SPEAKER); break;
	case zSPEAKER_TYPE_71_SPEAKER:	AIL_set_3D_speaker_type(act3dProvider,AIL_3D_71_SPEAKER); break;
#endif
	default:						zERR_MESSAGE(zERR_LV_DETAIL,0,"C: speaker type not supported");
	}

	this->speakerType = speakerType;
};


// *******************************************************************************************
// zCSndFX_MSS
// *******************************************************************************************

// constructor 
zCSndFX_MSS::zCSndFX_MSS () 
{
	actChannel			= 0;
	actFrame			= 0;
	actChannelFrame		= zSND_CHANNEL_FRAME_RANDOM;
	autoDelete			= FALSE;

	volume				= 1;
	pan					= zSND_PAN_DEFAULT;
	rate				= 44100;
	startPlayTime		= -1;
	m_bIsFixed			= FALSE;
}

// destructor
zCSndFX_MSS :: ~zCSndFX_MSS() 
{
	//zERR_WARNING("zCSndFX_MSS:: Destructor called for :"  + GetObjectName());
	for (int i=0; i<channelList.GetNumInList(); i++) delete channelList[i];
	channelList.DeleteList();
	if (GetRefCtr() != 0){
		zERR_FATAL("C: zSndMSS.cpp(zCSndFX_MSS:Destructor): Reference Counter not zero !");
	}
}

void zCSndFX_MSS::LoadChannel(const int reqChannel)
{

	zCSndChannel *chan = channelList[reqChannel];

	if ( !chan->Loaded() )  
	{
		// channel does not yet exist -> load it in 
		zSTRING id( GetObjectName() ); 
		zSTRING ch(UNDERBAR + ID_CHANNEL_CHAR + zSTRING(reqChannel));

		zSTRING newID(id + ch);

		if (sfxParser->GetSymbol(newID) == 0) {
			zERR_FATAL("C: zSndMSS.cpp(zCSndFX_MSS::LoadChannel) channel not known. INSTANCE " + newID);
		}

		zSTRING fr(UNDERBAR + ID_FRAME_CHAR + "1");
		int frCntr = 1;
		do 
		{
			// Im Spy das Laden dieses Channels ausgeben
			zERR_MESSAGE(5,0,zSTRING("C: Loading Sound Instance ") + id + zSTRING("   (voice: ") +zSTRING(reqChannel) + zSTRING(" alternative:") + zSTRING(frCntr-1) + zSTRING(")"));
			fr = UNDERBAR + ID_FRAME_CHAR + zSTRING(frCntr++);
			newID = id + ch + fr ;
			if (sfxParser->GetSymbol(newID) == 0) break;
		} 
		while (1);

		channelList[reqChannel]->SetLoaded(TRUE);
	}

	// if this channel has already been loaded, we perhaps have to increase 
	// refCtr for this sfx, compare this refCtr with the greatest of all channels

	chan->AddRef();
	if ( chan->GetRefCtr() > GetRefCtr() ) AddRef();
}

void zCSndFX_MSS :: SetFrequency (int newFreq)		
{   // default frequencies in each frame are NOT being considered if freq != zSND_FREQ_DEFAULT
	// does not modify already playing sounds!

	if ( newFreq == zSND_FREQ_DEFAULT ) 
	{
		for (int i=0; i<channelList.GetNumInList(); i++) 
		{
			for (int j=0; j<channelList[i]->frameList.GetNumInList(); j++) 
			{
				channelList[i]->frameList[j]->actRate = channelList[i]->frameList[j]->GetWave()->GetRate();
			}
		}
	}
	else 
	{
		for (int i=0; i<channelList.GetNumInList(); i++) 
		{
			for (int j=0; j<channelList[i]->frameList.GetNumInList(); j++) 
			{
				channelList[i]->frameList[j]->actRate= newFreq;
			}
		}
	}
	rate = newFreq;
};

void zCSndFX_MSS :: SetPan(float newPan)
{	// default pannings in each frame are NOT being considered if pan != zSND_PAN_DEFAULT
	// does not modify already playing sounds!

	if ( newPan == zSND_PAN_DEFAULT ) 
	{
		for (int i=0; i<channelList.GetNumInList(); i++) 
		{
			for (int j=0; j<channelList[i]->frameList.GetNumInList(); j++) {
				channelList[i]->frameList[j]->actPan = MSS_PAN_CENTER;
			}
		}
	}
	else 
	{
		float s = ( newPan - zSND_PAN_LEFT ) / ( zSND_PAN_RIGHT - zSND_PAN_LEFT );
		int p = (int) Lerp(s, MSS_PAN_LEFT, MSS_PAN_RIGHT);

		for (int i=0; i<channelList.GetNumInList(); i++) 
		{
			for (int j=0; j<channelList[i]->frameList.GetNumInList(); j++) 
			{
				channelList[i]->frameList[j]->actPan = p;
			}
		}
	}

	pan = newPan;
};


void zCSndFX_MSS :: SetVolume	(float inVol)		
{   // default volumes in each frame are being considered
	// does not modify already playing sounds!
	float outVol;
	if ( inVol == zSND_VOL_DEFAULT ) outVol = 1; 
	else outVol = inVol;

	for (int i=0; i<channelList.GetNumInList(); i++) 
	{
		for (int j=0; j<channelList[i]->frameList.GetNumInList(); j++) 
		{
			channelList[i]->frameList[j]->actVolume = int(outVol * channelList[i]->frameList[j]->defVolume);
		}
	}
	volume = inVol;
};

void zCSndFX_MSS :: SetDefaultProperties() 
{
	for (int i=0; i<GetNumChannels(); i++) 
	{ 
		for (int j=0; j<channelList[i]->GetNumFrames(); j++) { 
			channelList[i]->frameList[j]->SetDefaultProperties();
		}
	}
}

zBOOL zCSndFX_MSS :: LoadResourceData ()
{
#ifdef SOUND_NIL
	return TRUE;
#endif

	// main thread kann:  zCSoundFX::CacheIn(-1)/zCSoundFX::CacheOut()
	// haupt thread kann: zCSoundFX::CacheIn(-1)/zCSoundFX::CacheIn ()
	// Die Waves vom Typ zCWaveData in zCSndFrame sind geshared, daher kann es vorkommen
	// das ein wave während es ausgecacht wird, in einem anderen zCSoundFX wieder geladen werden soll 
	// -> daher finden thread kritische Zugriffe auf die Waves über die zCWavePool Klasse statt
	
	zERR_MESSAGE(8,0,"C: zCSndFX_MSS :: LoadResourceData() for " + GetObjectName());
	for (int i=0; i<GetNumChannels(); i++) { 
		for (int j=0; j<channelList[i]->GetNumFrames(); j++) { 
			channelList[i]->frameList[j]->CacheIn();
		}
	}	
	return TRUE;
};

zBOOL  zCSndFX_MSS :: ReleaseResourceData ()
{
#ifdef SOUND_NIL
	return TRUE;
#endif
	zERR_MESSAGE(9,0,"C: zCSndFX_MSS :: ReleaseResourceData() for " + GetObjectName());

	for (int i=0; i<GetNumChannels(); i++) { 
		for (int j=0; j<channelList[i]->GetNumFrames(); j++) { 
			// und weg
			channelList[i]->frameList[j]->CacheOut();
		}
	}
	zERR_MESSAGE(9,0,"");
	return TRUE;
};

zBOOL zCSndFX_MSS :: IsActive()
{
	for (int i=0; i<GetNumChannels(); i++) {
		for (int j=0; j<channelList[i]->GetNumFrames(); j++) {
			zCSndFrame *frm = channelList[i]->frameList[j];
			if (zCActiveSnd::GetFrameActive(frm)) return TRUE;
		}
	}
	return FALSE;
};


float zCSndFX_MSS :: GetPlayingTimeMSEC		() const
{

#ifdef SOUND_NIL
	return 0;
#endif

	const_cast<zCSndFX_MSS*>(this)->CacheIn(-1);
	
	return const_cast<zCSndFX_MSS*>(this)->GetActFrame()->GetWave()->msLength;
};


zDWORD	zCSndFX_MSS :: GetResSizeBytes()
{
#ifdef SOUND_NIL
	return 0;
#endif

	CacheIn(-1);		// auf jeden Fall müssen alle Waves geladen sein, 
						// bevor die Grössen der Waves bekannt sind.

	zDWORD resSize = 0;
	for (int i=0; i<GetNumChannels(); i++) {
		for (int j=0; j<channelList[i]->GetNumFrames(); j++) {
			zCSndFrame *frm = channelList[i]->frameList[j];
			if (frm->GetWave()) resSize += frm->GetWave()->GetSize();
		}
	}
	return resSize;
};


void zCSndFX_MSS :: CheckCanBeCachedOut() 
{

	// darf schon ausgecacht werden ? dann raus hier
	if ( GetCacheOutLock() == FALSE ) return;

	// schaue, ob ein wave das in diesem Objekt vorkommt noch aktiv ist
	zCSndFrame *frm;
	for (int c=0; c<GetNumChannels(); c++) 
	{
		for (int f=0; f<GetNumChannelFrames(c); f++) 
		{
			frm = GetFrame(c,f);			
			if (zCWavePool::GetPool().IsWaveActive(frm->GetWave())) return;
		}
	}

	SetCacheOutLock(FALSE);

};


void zCSndFX_MSS :: NewFrame()
{
	for (int i=0; i<zCSndFX_MSS::GetStaticClassDef()->GetNumObjects(); i++) 
	{
		zCSndFX_MSS *snd = static_cast<zCSndFX_MSS*>(zCSndFX_MSS::GetStaticClassDef()->GetObjectByIndex(i));

		snd->CheckCanBeCachedOut();

		// FIXME: buggy: (siehe PlaySound3D(zSTRING...)
		/*if (!snd->IsActive()) 
		{
			if (snd->GetAutoDeletion() && !snd->IsLooping()) 
			{
				if (ztimer.GetTotalTimeF() - snd->startPlayTime >= AUTODELETION_WAIT_MSEC_BEFORE_RELEASE) {
					snd->Release();
				}
			}
		}*/
	}

};

void zCSndFX_MSS :: SetLooping(zBOOL loop) 
{
	for (int i=0; i<channelList.GetNumInList(); i++) 
	{
		for (int j=0; j<channelList[i]->frameList.GetNumInList(); j++) 
		{
			channelList[i]->frameList[j]->looping = loop ;	
		}
	}
};


void zCSndFX_MSS ::	GetChannelFrame	(int channel, int frameNr) const 
{ 
	channel = actChannel;
	frameNr = actFrame; 
};

void zCSndFX_MSS ::	SetChannelFrame	(int channel, int frameNr) 
{ 
	actChannelFrame = frameNr; 
	actChannel      = channel; 
	ChooseVariance();
	channelList[channel]->actFrame = actFrame; 
};


void  zCSndFX_MSS :: CacheInActFrame()
{
	channelList[actChannel]->frameList[actFrame]->CacheIn();
};

void  zCSndFX_MSS :: CacheOutActFrame()
{
	channelList[actChannel]->frameList[actFrame]->CacheOut();
};

void zCSndFX_MSS :: CacheInActChannel()
{
	for (int i=0; i<channelList[actChannel]->GetNumFrames(); i++) { 
		channelList[actChannel]->frameList[i]->GetWave()->CacheIn();
	}
};
void zCSndFX_MSS ::	CacheOutActChannel()
{
	for (int i=0; i<channelList[actChannel]->GetNumFrames(); i++) { 
		channelList[actChannel]->frameList[i]->GetWave()->CacheOut();
	}
};

void zCSndFX_MSS :: ChooseVariance() 
{
	// frame variance
	if (channelList[actChannel]->GetNumFrames() > 1 ) {
		if (actChannelFrame == zSND_CHANNEL_FRAME_RANDOM) {
			actFrame =  (int) ((zRandF() * (channelList[actChannel]->GetNumFrames()-1)) + 0.5F) ;
		} else actFrame = actChannelFrame;
	} else actFrame = 0;
};



// *******************************************************************************************
// zCActiveSnd
// *******************************************************************************************

zCActiveSnd::zCActiveSnd() 
{
	Initialize();
};

zCActiveSnd::~zCActiveSnd() 
{
    Release(); // [Moos] Leakfix
    nextFreeSnd=NULL; // [Moos] Release() hat den auf this gesetzt, und das ist natürlich hier Blödsinn.
};

zTSoundHandle zCActiveSnd :: GetNextFreeHandle() 
{
	// ACHTUNG: Änderung ab 1.17
	// Bis 1.17 wurden Handles auch von schon älteren beendeten Sounds zurückgegeben, zwecks besserem Überlaufschutz
	// allerdings war das auch kein 100%iger Schutz und ausserdem falsch, denn
	// es konnte der Fall auftreten, daß ein Modul von aussen sich ein Handle merkte und den dazugehörigen Sound
	// auf Aktivität testete. Wenn nun aber der gleiche Handle für einen anderen Sound vergeben wurde (wohlmöglich noch
	// für einen anderen Soundtyp!) gab es Chaos.
	// Daher muss für jeden Sound der Handle wirklich eindeutig sein.
	// Ein Überlauf ist für die Anwendung ausserdem wohl auch wirklich vernachlässigbar

	lastHandle ++;
	return lastHandle;

	
	/*int numActive = GetNumActive();
	
	if (numActive == 0) 
	{
		lastHandle += 1;
		return lastHandle ; 
	}
	int nextCandidate = activeSndList[numActive-1]->handle + 1;
	if ( GetHandleIndex(nextCandidate) == -1 ) 
	{
		lastHandle = nextCandidate;
		return nextCandidate;
	}
	return 0;  // never here !
	*/
}


zCActiveSnd* zCActiveSnd::AllocNextFreeSnd()
{
	zCActiveSnd* snd;

	if (nextFreeSnd) 
	{
		snd = nextFreeSnd;
		snd->allocated = TRUE;
		nextFreeSnd = 0;
		return snd;
	}

	for (int i=0; i<MIN_ACTSND_PREALLOCED; i++) 
	{
		snd = preAllocedSndList[i];
		if (!snd->allocated) 
		{
			snd->allocated = TRUE;
			return snd;
		}
	};

	// okay, falls alle sounds in der Liste benutzt wurden, hier die dynamische Vergrösserung:
	zCActiveSnd *newSnd = zNEW(zCActiveSnd);
	preAllocedSndList.Insert(newSnd);
	newSnd->allocated = TRUE;
	return newSnd;
};

void zCActiveSnd :: Release()
{
	// (alt)
	// (E3 Hotfix: Memory Leaks für Pfeile in Kauf nehmen = KEIN zRELEASE auf den sourceVob = kein Crash bei PfeilSchuss auf NPC)

	zRELEASE(sourceVob);
	zRELEASE(sourceSnd);

    if (sample3D)
	    AIL_release_3D_sample_handle(sample3D); // [Moos] verhindert ein HANDLE-Leak -> kein ARGLKABARGL mehr
    if (sample)
	    AIL_release_sample_handle(sample); // [Moos] verhindert ein HANDLE-Leak -> kein ARGLKABARGL mehr

	Initialize();			// FIXME: nicht alles davon nötig, aber um sicher zu sein, erst mal drin lassen
	nextFreeSnd = this;
};

void zCActiveSnd :: Initialize()
{
	allocated = FALSE;
	sourceVob = 0;	
	sourceFrm = 0;
	sourceSnd = 0;
	vobSlot	  = zSND_SLOT_NONE;
	age		  = 0;
	sample	  = 0;
	sample3D  = 0;
	muteTime  = 0;
	looping   = FALSE;
	loopType  = zCSoundSystem::zSND_LOOPING_DEFAULT;
	is3D	  = FALSE;
	isAmbient = FALSE;
	handle	  = 0;
	volume	  = 127;
	pan		  = MSS_PAN_CENTER;
	rate	  = 44100;
	pitchOffset=zSND_PITCH_DEFAULT;
	radius	  = zSND_RADIUS_DEFAULT;
	active	  = FALSE;
	lastTime  = 0;
	volWeight = 1;
	obstruction = 0;
	reverbLevel = 0;
	obstructionToGo = 0;
	volumeToGo		= 1;
	autoObstructTimer=0;

	if (listener && listener->GetHomeWorld())	frameCtr    = listener->GetHomeWorld()->GetMasterFrameCtr();
	else										frameCtr	= 0;
};

int zCActiveSnd :: GetHandleIndex(const zTSoundHandle hnd)
{
	static zCActiveSnd tmpsnd;
	tmpsnd.handle = hnd;
	if (activeSndList.GetNumInList() == 0) return -1;
	return activeSndList.Search(&tmpsnd);
}
zBOOL zCActiveSnd :: GetHandleActive(const zTSoundHandle hnd)
{	
	if (hnd == 0) return FALSE;
	int foundIndex = GetHandleIndex(hnd);
	if (foundIndex == -1) return FALSE;
	if (activeSndList.GetSafe(foundIndex)->active) return TRUE;
	if (activeSndList.GetSafe(foundIndex)->sample) return TRUE;
	if (activeSndList.GetSafe(foundIndex)->sample3D) return TRUE;
	return FALSE;
}
zBOOL zCActiveSnd :: GetSoundActive(zCActiveSnd *snd)
{	
	if ( snd == 0 )			   return FALSE;
	if ( GetNumActive() == 0 ) return FALSE;

	int foundIndex = activeSndList.Search(snd);
	if ( foundIndex == -1 ) return FALSE;
	return ( activeSndList[foundIndex]->active );
}

zBOOL zCActiveSnd :: GetFrameActive(zCSndFrame  *frm)
{
	if ( frm == 0 )			   return FALSE;
	// FIXME: evtl. zweite activeSndList nach sourceFrames sortieren, oder andere struktur, falls
	// nötig -> profile

	for (int i=0; i<activeSndList.GetNumInList(); i++) 
	{
		if (activeSndList[i]->active && activeSndList[i]->sourceFrm == frm) return TRUE;
	};
	return FALSE;
};

zCActiveSnd*	zCActiveSnd :: GetHandleSound		(const zTSoundHandle hnd)
{
	int index = GetHandleIndex(hnd);
	if (index == -1) return 0; else return activeSndList.GetSafe(index);
}

void zCActiveSnd ::  AddSound			(zCActiveSnd *newSnd)
{	
	assert(newSnd);
	activeSndList.InsertSort(newSnd);
}

void zCActiveSnd ::  RemoveSound	(zCActiveSnd *newSnd)
{	
	assert(newSnd);
	//zERR_WARNING("C: RemoveSound for: " + newSnd->sourceFrm->fileName);

	if (newSnd->Is3DSnd()) 
	{
		if (newSnd->sample3D) 
		{
			if (AIL_3D_sample_status(newSnd->sample3D) != SMP_DONE) 
			{
				AIL_end_3D_sample(newSnd->sample3D);
				while(AIL_3D_sample_status(newSnd->sample3D) != SMP_DONE);			
			}
			handleMan.Free3DSample(newSnd -> sample3D);
			newSnd->sample3D=0;
		}
	}
	else 
	{
		if (newSnd->sample) 
		{
			if (AIL_sample_status(newSnd->sample) != SMP_DONE) 
			{
				AIL_end_sample(newSnd->sample);
			}
			handleMan.FreeSample(newSnd -> sample);
			newSnd->sample=0;
		}
	}

	// okay, die Referenz auf den Source SFX kann jetzt freigegeben werden

	D_SpyFrameInfo(newSnd,TRUE);
	activeSndList.RemoveOrder(newSnd);

	//zERR_WARNING("C: RemoveSound (End) for: " + newSnd->sourceFrm->fileName);
	newSnd->Release();
	
}

void zCActiveSnd ::  RemoveSoundsByFrame(zCSndFrame *frame)
{	
	assert(frame);
	// FIXME: besser rückwärts
	for (int i=0; i<GetNumActive(); i++) 
	{
		if ( activeSndList[i]->sourceFrm == frame ) 
		{
			RemoveSound(activeSndList[i]);
			i--; continue;
		}
	}

}
void zCActiveSnd ::  RemoveSoundByVobSlot(const zCVob *vob, const int slot)
{	
	for (int i=0; i<GetNumActive(); i++) 
	{
		if ( activeSndList[i]->sourceVob == vob) 
		{ 
			if (activeSndList[i]->vobSlot == slot) 
			{
#ifdef DEBUG_EDENFELD
				zERR_WARNING("C: sound has been canceled on VOBSLOT " + zSTRING(slot) + ", stopped wave: " + activeSndList[i]->sourceSnd->GetObjectName());
#endif
				RemoveSound(activeSndList[i]);
				return;
			}
		}
	}
}
void zCActiveSnd ::  StopSoundsByFrame(zCSndFrame *frame)
{	
	assert(frame);
	for (int i=0; i<GetNumActive(); i++) 
	{
		if ( activeSndList[i]->sourceFrm == frame ) 
		{
			if (activeSndList[i]->Is3DSnd() && activeSndList[i]->sample3D ) 
			{ 
				AIL_stop_3D_sample(activeSndList[i]->sample3D);		
			}
			else if (activeSndList[i]->sample) 
			{ 
				AIL_stop_sample(activeSndList[i]->sample);		
			}
		}
	}
}
void zCActiveSnd ::  ResumeSoundsByFrame(zCSndFrame *frame)
{	
	assert(frame);
	for (int i=0; i<GetNumActive(); i++) 
	{
		if ( activeSndList[i]->sourceFrm == frame ) 
		{ 
			if (activeSndList[i]->Is3DSnd()) AIL_resume_3D_sample(activeSndList[i]->sample3D); 			
			else AIL_resume_sample(activeSndList[i]->sample); 			
		}
	}
}
void zCActiveSnd ::  UpdateSoundsByFrame(zCSndFrame *frame)
{	
	assert(frame);
	for (int i=0; i<GetNumActive(); i++) 
	{
		if ( activeSndList[i]->sourceFrm == frame ) 
		{ 
			if (activeSndList[i]->sourceFrm->GetWave()->GetSize()==0) continue;
			activeSndList[i]->sourceFrm->SetDefaultProperties();
			activeSndList[i]->rate		= activeSndList[i]->sourceFrm->CalcPitchVariance();
			activeSndList[i]->looping	= activeSndList[i]->sourceFrm->looping;
			if (activeSndList[i]->Is3DSnd()) 
			{
				AIL_set_3D_sample_file			( activeSndList[i]->sample3D, (void*)activeSndList[i]->sourceFrm->GetWave()->GetAddr() );
				AIL_set_3D_sample_playback_rate	( activeSndList[i]->sample3D, activeSndList[i]->rate );
				AIL_set_3D_sample_distances		( activeSndList[i]->sample3D, activeSndList[i]->radius*RANGE_SCALE,MIN_DIST_MAX_VOL_SCALE * activeSndList[i]->radius*RANGE_SCALE);
#ifdef MSS_VERSION_65_UP
				AIL_set_3D_sample_volume		( activeSndList[i]->sample3D, (float)activeSndList[i]->CalcListenerVolume() / (float)MSS_VOL_MAX );
#else
				AIL_set_3D_sample_volume		( activeSndList[i]->sample3D, activeSndList[i]->CalcListenerVolume());
#endif
				AIL_set_3D_sample_loop_block	( activeSndList[i]->sample3D, activeSndList[i]->sourceFrm->loopStartOffset,activeSndList[i]->sourceFrm->loopEndOffset );
				AIL_set_3D_sample_loop_count	( activeSndList[i]->sample3D, !activeSndList[i]->looping );
			}
			else 
			{
				AIL_set_sample_file			( activeSndList[i]->sample, (void*)activeSndList[i]->sourceFrm->GetWave()->GetAddr(), 0 );
				AIL_set_sample_playback_rate( activeSndList[i]->sample, activeSndList[i]->rate );
#ifdef MSS_VERSION_65_UP
				AIL_set_sample_volume_pan	( activeSndList[i]->sample, (float)activeSndList[i]->CalcListenerVolume() / (float)MSS_VOL_MAX, (float)activeSndList[i]->CalcListenerPan() / (float)MSS_PAN_RIGHT );
#else
				AIL_set_sample_pan			( activeSndList[i]->sample, activeSndList[i]->CalcListenerPan());
				AIL_set_sample_volume		( activeSndList[i]->sample, activeSndList[i]->CalcListenerVolume());
#endif
				AIL_set_sample_loop_block	( activeSndList[i]->sample, activeSndList[i]->sourceFrm->loopStartOffset,activeSndList[i]->sourceFrm->loopEndOffset );
				AIL_set_sample_loop_count	( activeSndList[i]->sample, !activeSndList[i]->looping );
			}
		}
	}
}

int	zCActiveSnd ::  GetNumActive()
{
	return activeSndList.GetNumInList();
}
void zCActiveSnd ::  NewFrame()
{
	// Note: Sounds (HSAMPLES) die gerade ausserhalb Hörweite liegen (-> vol = 0), werden nicht sofort
	// discarded, sondern erst nach einer best. Zeit
	// Ansonsten kann es passieren, das ein (geloopter) Sound gestoppt wird, und dann
	// vielleicht sofort wieder gestartet wird, allerdings dann an der falschen Loop-position
	// Zusätlziche Aufgaben dieser Methode:
	// Alle Aktiven Sounds, die gestoppt wurden (d.h. active == 0 && sample == 0)
	// und die _nicht_ geloopt sind, können nach potentieller Ablaufzeit aus der activeList entfernt werden
	// weiterhin: die Grösse der preAllocedSoundList wird hier dynamisch auf ein Minimum gekürzt, falls möglich

	for (int i=0; i<GetNumActive(); i++) 
	{
		zCActiveSnd *snd = activeSndList[i];

		if (snd->Is3DSnd()) 
		{
		
			if (snd->sample3D)
			if (AIL_3D_sample_status(snd->sample3D) == SMP_DONE) 
			{ 
				RemoveSound(snd); 
				i--; continue; 
			};

			if ( !snd->active ) 
			{
				snd->muteTime += ztimer.GetFrameTime();
				if  (snd->muteTime > MAX_MUTE_MSEC_BEFORE_RELEASE) 
				{
					if ( snd->sample3D > 0) 
					{
						if (AIL_3D_sample_status(snd->sample3D) == SMP_PLAYING) AIL_stop_3D_sample(snd->sample3D);
						AIL_release_3D_sample_handle(snd->sample3D);
						snd->sample3D = 0;
						continue;
					}
					else if (!snd->looping) 
					{
						RemoveSound(snd); 
						i--; continue; 
					}
				}
			} 
		}
		else 
		{

			if (snd->sample)
			if (AIL_sample_status(snd->sample) == SMP_DONE) 
			{ 
				RemoveSound(snd); 
				i--; continue; 
			};

			if ( !snd->active ) 
			{
				snd->muteTime += ztimer.GetFrameTime();
				if  (snd->muteTime > MAX_MUTE_MSEC_BEFORE_RELEASE) 
				{
					if ( snd->sample > 0) 
					{
						if (AIL_sample_status(snd->sample) == SMP_PLAYING) AIL_stop_sample(snd->sample);
						AIL_release_sample_handle(snd->sample);
						snd->sample = 0;
						continue;
					}
					else if (!snd->looping) 
					{
						RemoveSound(snd);
						i--; continue;
					}
				}
			} 
		}

		snd->IncAge();
		if (autoUpdate3D) zsound->UpdateSound3D(snd->handle);
	}

	// nun dynamisch die preAllocedSndList falls möglich auf ein minimum reduzieren

	if (preAllocedSndList.GetNumInList()>MIN_ACTSND_PREALLOCED*2) // [Moos] Grenze erhöht, um Speichermanager-Aufrufe zu minimieren
	{
		for (i=0; i<preAllocedSndList.GetNumInList();i++) 
		{
			if (!preAllocedSndList[i]->allocated) 
			{
                zCActiveSnd *rem = preAllocedSndList[i];
				preAllocedSndList.RemoveIndex(i);
                RemoveSound(rem);                       // [Moos] Sicherheit...
                delete rem;                             // [Moos] Leakfix; Nebenwirkungen (ARGLKABARGL....) sind hoffentlich beseitigt.
				i--; 
				if (preAllocedSndList.GetNumInList()==MIN_ACTSND_PREALLOCED) return;
			}
		}
	}
}



void	zCActiveSnd :: UpdateReverb		(const float weight)
{
	for (int i=0; i<GetNumActive(); i++) 
	{
		zCActiveSnd *snd = activeSndList[i];

		if (snd->active && snd->Is3DSnd() && snd->sample3D>0)
		{
			if (weight>0) 	AIL_set_3D_sample_effects_level(snd->sample3D, -1);
			else			AIL_set_3D_sample_effects_level(snd->sample3D, 0);
		}
	}
};

int	zCActiveSnd :: CalcListenerPan()
{
	return MSS_PAN_CENTER;
}

// ermittelt die aktuelle Lautstärke eines Sounds in Abhängigkeit von der Entfernung zum Listener
int	zCActiveSnd::CalcListenerVolume()
{
	if (IsAmbient()) volume = Lerp(GetVolume(),MSS_VOL_MIN,MSS_VOL_MAX);
	else			 volume = sourceFrm->actVolume ;
	volume *= volWeight;
	//zERR_WARNING("C: CalcListenerVolume: " + zSTRING(volume));
	return volume;
}


int zCActiveSnd::GetNum3DSamplesUsed()
{
	int cnt = 0 ;
	zCActiveSnd *snd;
	for (int i=0; i<GetNumActive(); i++) 
	{
		snd = activeSndList[i];
		if (snd->Is3DSnd() && snd->sample3D) cnt++;
	}
	return cnt;
}

int zCActiveSnd::GetNumAmbientSamplesUsed()
{
	int cnt = 0 ;
	zCActiveSnd *snd;
	for (int i=0; i<GetNumActive(); i++) 
	{
		snd = activeSndList[i];
		if (!snd->Is3DSnd() && snd->sample) cnt++;
	}
	return cnt;
}

zBOOL zCActiveSnd::RequestChannel()
{
	// Besser: Erst nach samples mit Lautstärke < MIN_DISCARD_VOL für zu löschende Sounds suchen,
	// und dann LRU Schema.
	// auch möglich: doppelt gespielte waves finden

	if (Is3DSnd()) return RequestChannel3D();

	sample = handleMan.AllocSample();
	if (sample != 0) return TRUE;

	// Kein sample geliefert. 
	// Suche Sounds mit minimaler Lautstärke, und stoppe diese

	int minIndex=0;
	for (int i=0; i<GetNumActive(); i++) 
	{
		if ( activeSndList[i]->sample ) 
		{
			if ( activeSndList[i]->GetVolume() <= MIN_DISCARD_VOLUME) 
			{
				minIndex = i; 
				break;
			}
			if ( activeSndList[i]->age <= activeSndList[minIndex]->age ) minIndex = i;
		}
	}

	// nun haben wir einen Sounds mit minimaler Lautstärke, oder den ältesten aktiven Sound
	if (activeSndList[minIndex]->sample == 0) 
	{
		// brute force: wir steppen einmal durch alle aktiven sounds und picken uns den ersten raus
		for (int i=0; i<GetNumActive(); i++) if ( activeSndList[i]->sample ) minIndex = i;
	}

	if (activeSndList[minIndex]->sample == 0) 
	{
		zERR_WARNING("C: ARGLKABARGL: (zCActiveSnd::RequestChannel): no sample found");
		return FALSE;
	}
	
	if (activeSndList[minIndex]->sample) AIL_release_sample_handle(activeSndList[minIndex]->sample);
	activeSndList[minIndex]->sample = 0;

	// Der Sound ist jetzt discarded, und wird in UpdateSound3d aber sofort wieder neu gestarted (wahrscheinlich)
	activeSndList[minIndex]->active = FALSE;
	sample = AIL_allocate_sample_handle(sndDrv);

	if (!sample) 
	{
		zERR_WARNING("C: ARGLKABARGL2: (zCActiveSnd::RequestChannel): no sample found");
		return FALSE;
	}
	return TRUE;
}


/* ----------------------------------------------------------------------
	
    zCActiveSnd::RequestChannel3D()	

	3.10.2000	[Moos]	
                Assertion wegen leerer actSound-Liste hinzugefügt.

   ---------------------------------------------------------------------- */

zBOOL zCActiveSnd::RequestChannel3D()
{
	// Besser: Erst nach samples mit Lautstärke < MIN_DISCARD_VOL für zu löschende Sounds suchen,
	// und dann LRU Schema.
	// auch möglich: doppelt gespielte waves finden
	// Prioritäten:
	// 1. Sounds die leiser als MIN_DISCARD_VOLUME finden, und löschen
	// 2. schauen ob schon ein gleicher sound in der aktiv Liste, wenn ja: nicht spielen!
	// 3. doppelt gespielte sounds löschen
	// 4. ältesten sound löschen

	sample3D = handleMan.Alloc3DSample();
	if (sample3D != 0) return TRUE;

    if (GetNumActive() == 0){ // [Moos] Kein Handle von MSS mehr verfügbar, aber auch kein aktiver Sound? Verursacher war fehlerhafter zCActiveSnd-Destruktor.
    	zERR_WARNING("C: ARGLKABARGL: (zCActiveSnd::RequestChannel3D): no sample3d found");
        return FALSE;
    }

	int minIndex=0;
	for (int i=0; i<GetNumActive(); i++) 
	{
		if ( activeSndList[i]->sample3D ) 
		{
			if ( activeSndList[i]->GetVolume() <= MIN_DISCARD_VOLUME) 
			{
				minIndex = i; 
				break;
			}
			if ( activeSndList[i]->age <= activeSndList[minIndex]->age ) minIndex = i;
		}
	}

	if (activeSndList[minIndex]->sample3D == 0) 
	{
		// brute force: wir steppen einmal durch alle aktiven sounds und picken uns den ersten raus
		for (int i=0; i<GetNumActive(); i++) if ( activeSndList[i]->sample3D ) minIndex = i;
	}

   	if (activeSndList[minIndex]->sample3D == 0) 
	{
    	zERR_WARNING("C: ARGLKABARGL: (zCActiveSnd::RequestChannel3D): no sample3d found");
	    return FALSE;
    }

   	AIL_release_3D_sample_handle(activeSndList[minIndex]->sample3D);
    activeSndList[minIndex]->sample3D = 0;

   // Der Sound ist jetzt discarded, und wird in UpdateSound3d aber sofort wieder neu gestarted (wahrscheinlich)
    activeSndList[minIndex]->active = FALSE;
    sample3D = AIL_allocate_3D_sample_handle(act3dProvider);
    if (!sample3D) 
	{
		zERR_WARNING("C: ARGLKABARGL: (zCActiveSnd::RequestChannel3D): no sample3d found");
		return FALSE;
	}

    return TRUE;
}

float zCActiveSnd :: GetVolume()
{
	if (Is3DSnd() || IsAmbient())	
	{
		if (!listener ) return 0;
		if (!sourceVob) return 0;

		zVEC3 center= sourceVob->GetPositionWorld();
		zVEC3 v1	= listener -> GetAtVectorWorld();
		zVEC3 v2	= (center - listener -> GetPositionWorld());
		v2.n[1]		= 0;

		float origMinDist = MIN_DIST_MAX_VOL_SCALE * radius;
		float minDist	  = origMinDist;
		float actDist	  = (center - listener->GetPositionWorld()).LengthApprox();
		if (actDist>radius) return 0;
		float vol;

		//if (act3dProviderIndex==0)			// für MILES werden alle Sounds am Radius Ende auf Lautstärke 0 gesetzt
		if ( actDist > origMinDist ) 
		{
			float minDistScale = 1- ( (actDist - origMinDist)/(radius-origMinDist) );
			minDist = origMinDist * minDistScale;
		}

		if (actDist != 0) vol = minDist/actDist * (float(sourceFrm->actVolume)/MSS_VOL_MAX);
		else			  vol =				1   * (float(sourceFrm->actVolume)/MSS_VOL_MAX);

		zClamp01(vol);
		return vol;
	}
	else return (float) ( sourceFrm->actVolume - MSS_VOL_MIN ) / float( MSS_VOL_MAX - MSS_VOL_MIN ) ;
};

void zCActiveSnd::DebugInfo()
{
	zERR_MESSAGE(10,0,"listing active sounds");
	for (int i=0; i<activeSndList.GetNumInList(); i++) 
	{
		zCActiveSnd *snd = activeSndList[i];
		if (snd->is3D) 
		{
			zERR_MESSAGE(10,0,zSTRING(i) + zSTRING(": ") + snd->sourceFrm->fileName + 
							  zSTRING(" is a 3d sound ") +
							  zSTRING(" active:")+zSTRING(snd->active) +
							  zSTRING(" looping:")+zSTRING(snd->looping) +
							  zSTRING(" radius:")+zSTRING(snd->radius) +
							  zSTRING(" sample3D:")+zSTRING((int)snd->sample3D)
			);
		}
		else 
		{
			zERR_MESSAGE(10,0,zSTRING(i) + zSTRING(": ") + snd->sourceFrm->fileName + 
							  zSTRING(" is a 2d sound ") +
							  zSTRING(" active:")+zSTRING(snd->active) +
							  zSTRING(" looping:")+zSTRING(snd->looping) +
							  zSTRING(" radius:")+zSTRING(snd->radius) +
							  zSTRING(" sample:")+zSTRING((int)snd->sample)
			);
		}
	}

};

void zCActiveSnd::InitPreAllocedData()
{
	for (int i=0; i<MIN_ACTSND_PREALLOCED; i++) 
	{
		zCActiveSnd *newSnd =  zNEW(zCActiveSnd);
		preAllocedSndList.Insert(newSnd);
	}
}

/* ----------------------------------------------------------------------
	
    zCActiveSnd::CleanupPreAllocatedData()	

	29.08.2000	[Moos]	
                erzeugt, um Soundleaks zu stopfen

   ---------------------------------------------------------------------- */


void zCActiveSnd::CleanupPreAllocedData()
{

	for (int i=preAllocedSndList.GetNum()-1; i>=0; i--)
		delete preAllocedSndList[i];
	
    preAllocedSndList.DeleteList();
}

zBOOL zCActiveSnd::HasBeenUpdatedThisFrame()
{
	if (!listener || !listener->GetHomeWorld()) return TRUE;
	return (frameCtr == listener->GetHomeWorld()->GetMasterFrameCtr());
};

// *******************************************************************************************
// zCSndChannel
// *******************************************************************************************
zCSndChannel::zCSndChannel() 
{ 
	actFrame = zSND_CHANNEL_FRAME_RANDOM; 
	refCtr   = 1;
	loaded	 = FALSE;
}

zCSndChannel::~zCSndChannel() 
{ 
	for (int i=0; i<frameList.GetNumInList(); i++) delete frameList[i];
	frameList.DeleteList();
};

void zCActiveSnd :: AutoCalcObstruction(zBOOL immediate)
{
	// auto-lautstärkeangleich indoor/outdoor
	// rules:
	// a) camera in sector, outdoor sichtbar, vobsound outdoor:  lautstärke - (50%*distFak), obstruction + 30%
	// b) camera in sector, outdoor invisible,vobsound outdoor:  lautstärke - (80%*distFak), obstruction + 50%
	// c) camera outdoor  , vobsound sector:  lautstärke - (100% * distanzfak), obstruction + 30%
	// d) both in different sectors
	zCSkyControler_Outdoor* sky = zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler());
	zBOOL situationChanged		= FALSE;
	if (sky && sourceVob)	// nur wenn engine nicht sowieso obstruction berechnet
	{
		// wie siehts denn aus ?
		// a)?
		if (sky->GetCameraLocationHint()==zCSkyControler::zCAM_INSIDE_SECTOR_CAN_SEE_OUTSIDE && ((!sourceVob->GetGroundPoly()) || (!sourceVob->GetGroundPoly()->GetSectorFlag())))
		{
			if (volumeToGo != 0.7f || obstructionToGo !=0.3f) situationChanged = TRUE;
			volumeToGo		= 0.7f;
			obstructionToGo	= 0.3f;
		} 
		else if (sky->GetCameraLocationHint()==zCSkyControler::zCAM_INSIDE_SECTOR_CANT_SEE_OUTSIDE&& ((!sourceVob->GetGroundPoly()) || (!sourceVob->GetGroundPoly()->GetSectorFlag())))
		{
			if (volumeToGo != 0.5f || obstructionToGo !=0.5f) situationChanged = TRUE;
			volumeToGo		= 0.5f;
			obstructionToGo	= 0.5f;
		} 
		else if (sky->GetCameraLocationHint()==zCSkyControler::zCAM_OUTSIDE_SECTOR && ((sourceVob->GetGroundPoly()) && (sourceVob->GetGroundPoly()->GetSectorFlag())))
		{
			if (volumeToGo != 0.6f || obstructionToGo !=0.5f) situationChanged = TRUE;
			volumeToGo		= 0.6f;
			obstructionToGo	= 0.5f;
		}
		else if (sky->GetCameraLocationHint()!=zCSkyControler::zCAM_OUTSIDE_SECTOR				&& 
			    ((sourceVob->GetGroundPoly()) && (sourceVob->GetGroundPoly()->GetSectorFlag())) &&
				zCCamera::activeCam															    && 
				zCCamera::activeCam->GetVob()													&& 
				zCCamera::activeCam->GetVob()->GetGroundPoly()									&&
				zCCamera::activeCam->GetVob()->GetGroundPoly()->GetMaterial()->GetBspSectorFront() != sourceVob->GetGroundPoly()->GetMaterial()->GetBspSectorFront())
		{	
			if (volumeToGo != 0.5f || obstructionToGo !=0.5f) situationChanged = TRUE;
			volumeToGo		= 0.5f;
			obstructionToGo	= 0.5f;
		}
		else
		{
			if (volumeToGo != 1 || obstructionToGo != 0) situationChanged = TRUE;
			volumeToGo		= 1;
			obstructionToGo	= 0;
		}
	}

	if ( situationChanged )
	{
		autoObstructTimer = 0;
	};

	autoObstructTimer+=ztimer.GetFrameTime();
	if (autoObstructTimer>1000 || immediate) autoObstructTimer = 1000;
	float t = zSinusEase(float(autoObstructTimer)/1000.0f);

	volWeight	= zLerp( t, volWeight,   volumeToGo		 );
	obstruction	= zLerp( t, obstruction, obstructionToGo );
};

// *******************************************************************************************
// zCSndFrame
// *******************************************************************************************

zCSndFrame::zCSndFrame()	 
{ 
	wav				= 0 ;
	pitchOffset		= 0 ;
	pitchVariance	= 0 ;
	defVolume		= MSS_VOL_MAX;
	looping			= FALSE;
	loopStartOffset	= 0;
	loopEndOffset	= -1;
	reverbLevel		= 0.5F;
	pfxName.Clear();
	fileName.Clear();
};

zCSndFrame::~zCSndFrame() 
{ 
	// Problem: Wenn dieser Destruktor via zCSndFX_MSS->Release() aufgerufen wird,
	// können noch Samples abgespielt werden, die diesen Frame benutzen
	// also muss man alle aktiven Sounds nach diesem sourceframe durchsuchen,und diese
	// stoppen und aus der activeSndList entfernen.
	// das ist teuer, da die activeSndList nach Handles sortiert ist, und nicht
	// nach sourceFrames.
	// Lösungen: 
	// 1.zweite activeSndList, Sortierung nach sourceFrames -> trotzdem teuer beim einfügen.
	zCActiveSnd::RemoveSoundsByFrame(this);

	zCWavePool::GetPool().ReleaseWave(wav);
	wav = 0;
};


void zCSndFrame::CalcPitchOffset(const float offset)	
{	
	pitchOffset = offset;
	actRate = wav->GetRate();
	if (offset != zSND_PITCH_DEFAULT)
	{
		if ( pitchOffset < 0 ) actRate = int(pow( SC_PITCH_HALVE_OCT_DOWN,zAbs((float)pitchOffset) ) * actRate); else
		if ( pitchOffset > 0 ) actRate = int(pow( SC_PITCH_HALVE_OCT_UP  ,zAbs((float)pitchOffset) ) * actRate);
	}
};

int zCSndFrame::CalcPitchVariance ()	
{	

	if ( pitchVariance == 0 ) return actRate;

	float minPitch = (float)pow((double)SC_PITCH_HALVE_OCT_DOWN,(double)pitchVariance) * actRate;
	float maxPitch = (float)pow((double)SC_PITCH_HALVE_OCT_UP  ,(double)pitchVariance) * actRate;

	return int( Lerp( zRandF() , minPitch, maxPitch ) + 0.5F ) ;
};

void zCSndFrame::SetDefaultProperties() 
{
	actVolume = defVolume;
	actPan    = MSS_PAN_CENTER;

	if (wav->GetSize()!=0) actRate = wav->GetRate(); else { actRate = 0; return; };

	if (pitchOffset != zSND_PITCH_DEFAULT)
	{
		if ( pitchOffset < 0 ) actRate = int(pow( SC_PITCH_HALVE_OCT_DOWN,zAbs((float)pitchOffset) ) * actRate); else
		if ( pitchOffset > 0 ) actRate = int(pow( SC_PITCH_HALVE_OCT_UP  ,zAbs((float)pitchOffset) ) * actRate);
	}
}

void zCSndFrame:: CacheIn()
{
	//zERR_WARNING("C: zCSndFrame::CacheIn() for: " + fileName);
	if (wav)   zCWavePool::GetPool().CacheIn(wav);
	else wav = zCWavePool::GetPool().CacheIn(fileName);
	//zERR_WARNING("C: zCSndFrame::CacheIn() End for: " + fileName);
};

void zCSndFrame::CacheOut()
{
	//zERR_WARNING("C: zCSndFrame::CacheOut() for: " + fileName);
	zCWavePool::GetPool().CacheOut(wav);
	//zERR_WARNING("C: zCSndFrame::CacheOut() End for: " + fileName);
};


// *******************************************************************************************
// zCWavePool
// *******************************************************************************************
zCWavePool::zCWavePool()
{
	SetCompare(CompareWaves);
	helpWave = zNEW(zCWaveData);
};

zCWavePool::~zCWavePool()
{
	helpWave->Release();
	helpWave = 0;
	activeWaveList.DeleteList();
};

zCWaveData* zCWavePool::CacheIn(zSTRING &fileName)
{
	waveGuard.Lock();

	zCWaveData *resWave = 0;

	helpWave -> fileName = fileName;
	int i = Search(helpWave);

	if (i==-1) 	
	{
		resWave = zNEW( zCWaveData(fileName) );
		InsertSort(resWave);
	}
	else
	{	
		resWave = array[i];
		resWave->AddRef();
	}

	resWave->CacheIn();

	waveGuard.Unlock();
	return resWave;
};

void zCWavePool::CacheIn(zCWaveData *wav)
{
	if (!wav) return;
	zERR_MESSAGE(10,0, "C: SND: zCWavePool::CacheIn() for wave: " + wav->GetName() );
	waveGuard.Lock();
	wav->CacheIn();
	waveGuard.Unlock();
};

void zCWavePool::CacheOut(zCWaveData *wav)
{
	if (!wav) return;
	zERR_MESSAGE(10,0, "C: SND: zCWavePool::CacheOut() for wave: " + wav->GetName() );

	waveGuard.Lock();
	wav->CacheOut();
	waveGuard.Unlock();
};

int zCWavePool::ReleaseWave(zCWaveData* wav)
{
	if (!wav) return -1;
	waveGuard.Lock();
	RemoveOrder(wav);
	int res = wav->Release();
	waveGuard.Unlock();
	return res;
};

void zCWavePool::NewFrame()
{
	//if (listener && listener->GetHomeWorld()) 
	//if (listener->GetHomeWorld()->GetMasterFrameCtr() % 3)
	{
		activeWaveList.DeleteList();
		// baue eine liste mit allen aktiven waves auf

		for (int i=0; i<zCActiveSnd::activeSndList.GetNumInList();  i++) 
		{
			zCActiveSnd *snd = zCActiveSnd::activeSndList[i];
			
			if (!snd->sourceFrm /*|| !snd->IsAssigned()*/ ) continue;

			zCWaveData *wav = snd->sourceFrm->GetWave();

			if ( wav==NULL || wav->GetAddr()==NULL ) continue;
			if ( !activeWaveList.IsInList(wav) ) activeWaveList.InsertEnd(wav);
		}
	}
};

void zCWavePool::DebugInfo()
{
	zERR_MESSAGE(1,0,"C: Actual loaded waves:");
	int totalSize = 0;
	zSTRING cacheState;

	for (int i=0; i<GetNumInList(); i++) 
	{
		cacheState = (array[i]->GetAddr()==0) ? "out)" : "in)";
		zERR_MESSAGE(1,0,"C: " + array[i]->fileName + " (cached " + cacheState);
		if (array[i]->GetAddr()!=0) totalSize+=array[i]->GetSize();
	};

	zERR_MESSAGE(1,0,"C: total memory used by all wave files : " + zSTRING(totalSize));
};

void zCWavePool::DebugInfo2()
{
	zCArray<zCActiveSnd*>usedSndList;
	int used3D = 0, usedAmbient = 0;
	int row    = 0;

	for (int i=0; i<zCActiveSnd::activeSndList.GetNumInList();  i++) 
	{
		zCActiveSnd *snd = zCActiveSnd::activeSndList[i];
		
		if (!snd->sourceFrm || !snd->IsAssigned()) continue;

		if ( !usedSndList.IsInList(snd) ) 
		{
			usedSndList.InsertEnd(snd);
			zSTRING type;
			int vol;

			if (snd->Is3DSnd()) 
			{
				type =  "3D";
				used3D ++;
				vol  =  int(Lerp(snd->GetVolume()*snd->volWeight,MSS_VOL_MIN,MSS_VOL_MAX));
			}
			else 
			{
				type =  "AMBIENT";
				usedAmbient++;
				vol  = snd->volume;
			};

			zSTRING ds = snd->sourceFrm->fileName + " (" + (snd->Is3DSnd() ? "3D" : "AMBIENT") + "), vol: " +zSTRING(vol);
			screen -> Print(0,row,(ds + zSTRING("\n")).ToChar()); 
			row += 300;
		}
	}
	row = 7000;
	zSTRING ds = "num 3d: " + zSTRING(used3D);
	screen -> Print(0,row,(ds + zSTRING("\n")).ToChar()); 
	row +=300;
	ds = "num ambient: " + zSTRING(usedAmbient);
	screen -> Print(0,row,(ds + zSTRING("\n")).ToChar()); 
	row +=300;
	ds = "mem: " + zSTRING(sndMemUsed);
	screen -> Print(0,row,(ds + zSTRING("\n")).ToChar()); 
};



// *******************************************************************************************
// zCWaveData
// *******************************************************************************************
zCWaveData::zCWaveData(zSTRING &name) 
{ 
	Init();
	fileName = name;
}

zCWaveData::~zCWaveData()
{
	if (refCtr != 0) zERR_FATAL("C: zSndMSS.h(zCWaveData::~zCWaveData()) refCtr not zero!");

	//zERR_WARNING("C: zCWaveData::Destruktor: " + fileName);

	CacheOut();		// safety

	if (info) 
	{
		delete info;
		info = 0;
	}

#ifdef CHECK_MSSWAVREF
	for (int i=0; i<zCActiveSnd::activeSndList.GetNumInList(); i++) {
		if (zCActiveSnd::activeSndList[i]->sourceFrm) {
			if (zCActiveSnd::activeSndList[i]->sourceFrm->GetWave()==this) {
				if (zCActiveSnd::activeSndList[i]->sample || zCActiveSnd::activeSndList[i]->sample3D) {
					assert(1!=1);
				}
			}
		}
	}
#endif


};

void zCWaveData::Init() 
{
	info			= 0;
	refCtr			= 1;
	memAddr			= 0;
	size			= 0;
	msLength		= 0;
	cacheInCount	= 0;
	adpcmCompressed	= FALSE;
	fileName.Clear();
}

/* ----------------------------------------------------------------------
	
	zCWaveData::CacheIn()

	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void zCWaveData::CacheIn() 
{	
	//zERR_WARNING("C: zCWaveData::CacheIn(): " + fileName);
	if (memAddr == NULL) 
	{
		zPATH sndPath(fileName);
		if (sndPath.SearchFile( fileName,zoptions->GetDirString(DIR_SOUND) ) == zERR_PATH_NOTFOUND) 
		{
			zERR_WARNING("C: zSndMSS.h(zCWaveData::zCWaveData): Wave not found: " + fileName);			
			if ( sndPath.SearchFile(MSS_DEF_WAVE,zoptions->GetDirString(DIR_SOUND)) ) zERR_FATAL("C: zSndMSS.h(zCWaveData::zCWaveData): Wave not found: " + MSS_DEF_WAVE);
		}
		zFILE *file = zfactory->CreateZFile(sndPath.GetPath());

		if (file->Open() == zERR_NONE) 
		{
			size		= file->Size();
			// ATT: Speicher wird hier oft bereitgestellt. Evtl. ist ein prealloc Memory Pool hier besser
			memAddr		= zNEW_ARRAY(char,size); // malloc(size);

			file -> Read (memAddr, size);
			file -> Close();

			if (!info) 
			{
				info = zNEW(AILSOUNDINFO);
				AIL_WAV_info( (void*)GetAddr(), info );
			}

			// ADPCM compressed 3d samples are being decompressed now
			if (AIL_file_type((void*)GetAddr(),GetSize()) == AILFILETYPE_ADPCM_WAV)
			{
				U32		milesSize;
				void*	newAddr;
				zERR_MESSAGE( 9,0,"C: SND: zCWaveData::CacheIn(): decompressing ADPCM Wave: " + this->GetName() );

				if (!AIL_decompress_ADPCM(GetInfo(),&newAddr,&milesSize))
				{
					zERR_FATAL("C: zCWaveData::CacheIn(): could not decompress ADPCM file " + this->GetName());
				}
				delete[] memAddr;		// miles kümmert sich um den neuen alloziierten speicher
				memAddr = newAddr;

				AIL_WAV_info( (void*)GetAddr(), info );
				size			= milesSize;
				adpcmCompressed = TRUE;
			}
		}
		else zERR_FAULT("C: zCWaveData::CacheIn(): could not open file: " +  sndPath.GetPath());

		delete file;

		sndMemUsed	+=size;
	}

	if (msLength==0) 
	{

		assert(memAddr);
		S32 length;

		zCActiveSnd *snd = zCActiveSnd::AllocNextFreeSnd();

		if (!snd->RequestChannel()) 
		{
			zERR_WARNING("C: SND: (zCWaveData::CacheIn()) could not allocate sample handle for wave duration evaluation (Name:"+ GetName() + ")");
			return;
		}

		AIL_set_sample_file(snd->sample,memAddr, 0);
		AIL_sample_ms_position(snd->sample,&length,0);
		msLength = (float) length;
		AIL_release_sample_handle(snd->sample);

		snd->Release();
	}

	cacheInCount++;

	//zERR_WARNING("C: zCWaveData::CacheIn()End : " + fileName);
}

/* ----------------------------------------------------------------------
	
	zCWaveData::CacheOut()

	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void zCWaveData::CacheOut() 
{	
	if (--cacheInCount == 0)
	if (memAddr) 
	{
		if (!adpcmCompressed) delete[] memAddr;
		else				  
		{
			AIL_mem_free_lock(memAddr);
			delete info;
			info = NULL;
		}
		memAddr = NULL;
		sndMemUsed-=size;
	}
}


zBOOL zCWaveData::CheckForCorrectFormat(const zBOOL is3D) 
{
	if (GetSize()==0) return FALSE;
	if (is3D) 
	{
		zBOOL stereo = FALSE;

		if ( GetInfo()->channels==2 )  
		{
			zERR_WARNING("C: SND: PlaySound3D: SoundFile " + fileName + " has to be a mono file"); 
			return FALSE;
		}

		switch (GetInfo()->format) 
		{
			case DIG_F_MONO_8		:   return TRUE;	break;
			case DIG_F_MONO_16		:   return TRUE;	break;
			case DIG_F_STEREO_8		:   stereo = TRUE;	break;
			case DIG_F_STEREO_16	:   stereo = TRUE;	break;
			case DIG_F_ADPCM_MONO_16:   return TRUE;	break;
			case DIG_F_ADPCM_STEREO_16: stereo = TRUE;	break;
			default:					zERR_WARNING("C: PlaySound3D: SoundFile " + fileName + " is a unknown format (did you try to play a compressed file as non-ambient 3d sound ?)"); return FALSE;
		}

		if (stereo)  
		{
			zERR_WARNING("C: PlaySound3D: SoundFile " + fileName + " has to be a mono file"); 
			return FALSE;
		}

	}
	return TRUE;
};


int	zCWaveData::Release					()			
{ 
	//zERR_WARNING("C: zCWaveData::Release(): " + fileName);
	--refCtr; 
	int c=refCtr;
	if ( refCtr == 0 ) delete this; 
	return c;
};


int zCWaveData::GetSize() 
{
	if (size == 0) CacheIn();
	return size;
};



H3DSAMPLE zCHandleManager::Alloc3DSample()
{
	if (free3DSamples.GetNum()>0) 
	{
		H3DSAMPLE sample = free3DSamples[free3DSamples.GetNum()-1];
		free3DSamples.RemoveIndex(free3DSamples.GetNum()-1);
		return sample;
	}
	return AIL_allocate_3D_sample_handle(act3dProvider);
};

HSAMPLE zCHandleManager::AllocSample()
{
	if (freeSamples.GetNum()>0) 
	{
		HSAMPLE sample = freeSamples[freeSamples.GetNum()-1];
		freeSamples.RemoveIndex(freeSamples.GetNum()-1);
		return sample;
	}
	return AIL_allocate_sample_handle(sndDrv);;
};

void zCHandleManager::Free3DSample(H3DSAMPLE sample)
{
	zERR_ASSERT(!free3DSamples.IsInList(sample));
	if (sample==0) return;
	free3DSamples.Insert(sample);
};

void zCHandleManager::FreeSample(HSAMPLE sample)
{
	zERR_ASSERT(!freeSamples.IsInList(sample));
	if (sample==0) return;
	freeSamples.Insert(sample);
};

void zCHandleManager::DisposeAllSamples()
{	
	for (int i=0; i<free3DSamples.GetNum(); i++)
	{
		H3DSAMPLE s = free3DSamples[i];
		if ( s && AIL_3D_sample_status(s) != SMP_FREE ) 
		{
			AIL_end_3D_sample			(s);
			AIL_release_3D_sample_handle(s);
		}
	}
	free3DSamples.DeleteList();
	for (    i=0; i<freeSamples.GetNum(); i++)
	{
		HSAMPLE s = freeSamples[i];
		if ( s && AIL_sample_status(s) != SMP_FREE ) 
		{
			AIL_stop_sample(s);
			AIL_release_sample_handle(s);
			while(AIL_sample_status(s) != SMP_FREE );
		}
	}
	freeSamples.DeleteList();
};




#pragma warning( default : 4244 )
