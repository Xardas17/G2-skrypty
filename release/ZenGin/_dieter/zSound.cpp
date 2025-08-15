 /******************************************************************************** 
 
     $Workfile:: zSound.cpp           $                $Date:: 21.08.00 17:18   $
     $Revision:: 6                    $             $Modtime:: 21.08.00 15:08   $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zSound.cpp $
 * 
 * 6     21.08.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 3     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 2     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 6 $ ($Modtime: 21.08.00 15:08 $)


#include <zCore.h>
#include <zSound.h>
#include <zOption.h>

zCLASS_DEFINITION_ABSTRACT (zCSoundFX, zCResource, zCLASS_FLAG_SHARED_OBJECTS | zCLASS_FLAG_RESOURCE)

zCSoundSystem *zsound=0;

/*

  IDEEN:

  x "ambient3D" Sounds: falloff, aber keine Orientierung (also 3 Typen: local, 3d, ambient-3D)
  x Sounds mit Orientierung und Cone-Angle ?
  x Occlusion-Daempfung
  x Doppler Effekt
  - Sounds mit 'innerRadius' ?
  - als falloff-Volumen auch Ellipse zulassen ?
  - Reverb-Zonen: globales Reverb (Staerke und Type) fuer alle Sounds einstellbar (Voices als Sonderfall?)
  - (streaming) ? (wofuer?)
  - (Filter Effekte (Unterwasser, etc.)?)
  - (realtime codec?)

  - Reverb:
	- Presets ? wo festgelegt ? editierbar ?
	- emulation ?
	- Zonen disjunkt ? lerp moeglich ?


  MISC:

  - Falls die Klasse PositionsDaten speichert... Wie verhaelt es sich mit verschiedenen Worlds,
    auch: was, wenn Inv-Items gerendert werden (Haupt-Game sfx sollten weiterlaufen)

  - Cam-Pos-Switch (abrupt)
  - World-Switch

  - sfx laden
  - sfx abspielen (mit/ohne Params)
  - Listener Objekt verwalten
  - 

  Abspiel-Params fuer sfx:
  - Volume
  - Freq/Pitch					Pitch-Variation?
  - (Pan) (nicht bei 3D/Mono)

  3D-Sound Props:
  - Pos, Orient, Velo

  Play-Varianten:
  - PlayFlat
	- mono/stereo
  - Play3D
	- mono
	- sndQuelle darf Position veraendern
		- Vob muss diese Position laufend updaten
	- sndQuelle bleibt statisch
  - Loops muessen explizit beendet werden !

  Fuers Soundsystem relevante Informationen ueber einen Vob:
  - position
  - orientierung	(bei cone-SoundQuellen)
  - velocity		(fuer Doppler-Effekt)

  - pan		: float		-1..0.++1
  - volume	: float		0..1
  - freq	: int		0.. 65536 ?

  - freq-Multiplier ? 0.5 -	1 - 1.5
  - vol -Multiplier ? 0.5 -	1 - 1.5

  - Variationen:
	- voice / Stimme
	- Variationen in derselben Stimme
	- Pitch-Random

// =========================================================================================

demon_p400.wav	= demon.wav
demon2.wav
demon3.wav

voice_shout_v0_0.wav
voice_shout_v0_1.wav
voice_shout_v0_2.wav

// =========================================================================================

	zCSoundFX* zSND_DEMON_MOAN;

	RegisterSound (zSND_DEMON_MOAN, "SND_DEMON_MOAN");		// Skript-Konstante

				zsound->PlaySound	(zSND_DEMON_MOAN);
	sfxHandle = zsound->PlaySound3D	(zSND_DEMON_MOAN, vob);

	// vobSound:

	zsound->PlaySound3D();

	// bei Bewegung;
	zsound->UpdateSound3D (sfxHandle, vob);		// position

*/

/*
	Multi-Sounds:
	-channel		-1-2-
	-	
		voice_shout_v0_0.wav 
		voice_shout_v0_1.wav
		voice_shout_v0_2.wav

		voice_shout_v1_0.wav

		voice_shout_v2_0.wav
		voice_shout_v2_1.wav

		demon_P400.wav	= demon.wav

		dem
		demon2.wav
		demon3.wav

		voice_shout_v0_0.wav
		voice_shout_v0_1.wav
		voice_shout_v0_2.wav
*/

enum { zNUM_REVERB_PRESETS = 26 };

static zSTRING s_reverbPresetName[zNUM_REVERB_PRESETS] = {
	"GENERIC",                              // ENVIRONMENT_GENERIC
	"PADDEDCELL",                           // ENVIRONMENT_PADDEDCELL
	"ROOM",                                 // ENVIRONMENT_ROOM
	"BATHROOM",                             // ENVIRONMENT_BATHROOM
	"LIVINGROOM",                           // ENVIRONMENT_LIVINGROOM
	"STONEROOM",                            // ENVIRONMENT_STONEROOM
	"AUDITORIUM",                           // ENVIRONMENT_AUDITORIUM
	"CONCERTHALL",                          // ENVIRONMENT_CONCERTHALL
	"CAVE",									// ENVIRONMENT_CAVE
	"ARENA",								// ENVIRONMENT_ARENA
	"HANGAR",								// ENVIRONMENT_HANGAR
	"CARPETEDHALLWAY",                      // ENVIRONMENT_CARPETEDHALLWAY
	"HALLWAY",								// ENVIRONMENT_HALLWAY
	"STONECORRIDOR",                        // ENVIRONMENT_STONECORRIDOR
	"ALLEY",                                // ENVIRONMENT_ALLEY
	"FOREST",								// ENVIRONMENT_FOREST
	"CITY",									// ENVIRONMENT_CITY
	"MOUNTAINS",							// ENVIRONMENT_MOUNTAINS
	"QUARRY",								// ENVIRONMENT_QUARRY
	"PLAIN",								// ENVIRONMENT_PLAIN
	"PARKINGLOT",							// ENVIRONMENT_PARKINGLOT
	"SEWERPIPE",							// ENVIRONMENT_SEWERPIPE
	"UNDERWATER",							// ENVIRONMENT_UNDERWATER
	"DRUGGED",								// ENVIRONMENT_DRUGGED
	"DIZZY",								// ENVIRONMENT_DIZZY
	"PSYCHOTIC"								// ENVIRONMENT_PSYCHOTIC
};

int zCSoundSystem::GetNumReverbPresets () 
{ 
	return zNUM_REVERB_PRESETS;	
};

const zSTRING* zCSoundSystem::GetReverbPresetName (int i)
{ 
	zERR_BOUNDS (i, 0, GetNumReverbPresets());
	if (i>=GetNumReverbPresets()) return 0;
	return &s_reverbPresetName[i];
};

void zCSoundFX::GetCacheConfig (zDWORD &cacheOutTimeMSec, zDWORD &cacheSizeMaxBytes)
{
	static zBOOL	configRead = FALSE;
	static zDWORD	s_cacheOutTimeMSec;
	static zDWORD	s_cacheSizeMaxBytes;

	if (!configRead)
	{
		configRead = TRUE;
		// .ini auswerten
		s_cacheOutTimeMSec	= zoptions->ReadDWord ("ENGINE", "zSndCacheOutTimeMSec"	, 10000);		// 10 secs 
		s_cacheSizeMaxBytes = zoptions->ReadDWord ("ENGINE", "zSndCacheSizeMaxBytes", 20000000);	// 20 MB
		// Die CacheSize wird unter bestimmten Bedingungen verdoppelt
		zBOOL doubleCacheSize		= FALSE;
		zBOOL tripleCacheSize		= FALSE;

		// a) bei mehr als 256MB Hauptspeicher 
		// FIXME FIXME: Windows-spezischischer Code: an einen Platform spezifischen Ort verlegen!!
		{
			enum {	ONEM			= (1024*1024)	};
			MEMORYSTATUS			memInfo;
			memInfo.dwLength		= sizeof(memInfo);
			GlobalMemoryStatus		(&memInfo);
			int memoryTotalMB		= (memInfo.dwTotalPhys + ONEM - 1) / ONEM;
			
			if (memoryTotalMB>512)
				tripleCacheSize		= TRUE;
			else if (memoryTotalMB>256)
				doubleCacheSize		= TRUE;
		};

		if (tripleCacheSize)
		{
			s_cacheSizeMaxBytes	*= 3;
			s_cacheOutTimeMSec	*= 3;
		}
		else if (doubleCacheSize)
		{
			s_cacheSizeMaxBytes	*= 2;
			s_cacheOutTimeMSec	*= 2;
		};
	};

	cacheOutTimeMSec = s_cacheOutTimeMSec;
	cacheSizeMaxBytes= s_cacheSizeMaxBytes;
};
