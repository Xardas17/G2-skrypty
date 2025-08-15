/******************************************************************************** 
 
     $Workfile:: zSound.h             $                $Date:: 12.04.01 17:29   $
     $Revision:: 11                   $             $Modtime:: 15.03.01 17:28   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ SoundSysten Interface
   created       : 25.8.98

 * $Log: /current_work/ZenGin/_Dieter/zSound.h $
 * 
 * 11    12.04.01 17:29 Edenfeld
 * Patch 2 (1.08): Änderungen fürs Sound System
 * 
 * 10    18.01.01 20:25 Edenfeld
 * 
 * 9     4.12.00 17:32 Hildebrandt
 * 
 * 8     28.09.00 23:21 Hildebrandt
 * 
 * 7     28.09.00 19:19 Hildebrandt
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 5     21.07.00 14:28 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 5     19.01.00 19:30 Hildebrandt
 * zCSoundSystem Interface change: zTSoundParams now has 'pitchOffset'
 * instead of 'freq'
 * 
 * 4     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 11 $ ($Modtime: 15.03.01 17:28 $)

// =======================================================================================================================

#ifndef __ZSOUND_H__
#define __ZSOUND_H__
 
#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __ZRESOURCE_H__
#include <zResource.h>
#endif

#ifdef PlaySound
#undef PlaySound
#endif

class zCVob;		// z3d.h
class zCParser;		// zParser.h

// =======================================================================================================================

//class zCAudioSystem;

// int		freq;			Hz
// float	vol;			0..1		(loudest)
// float	pan;			-1..0..+1	(left..center..right), Dolby-Surround: +100
// float	obstruction;	0..1		(percent)
// float	coneAngleDeg;	0°..360°	(degrees, 0 => point source, not 0 => cone source)
// float	reverbLevel;	0..1		
// float	pitchOffset		-x..0..+y	(halftones)

// Note on reverb:
// The global reverb weight (set in SetGlobalReverbPreset()) and the reverbLevel that is 
// specified in PlaySound3D() are modulated:
// resultReverb = sound->reverbLevel * globalReverbWeight.

const int	zSND_FREQ_DEFAULT		= -1;
const float zSND_PAN_DEFAULT		= -2;
const float zSND_PAN_LEFT			=-1.0F;
const float zSND_PAN_CENTER			= 0.0F;
const float zSND_PAN_RIGHT			= 1.0F;
const float	zSND_PAN_SURROUND		= 100.0F;
#define		zSND_VOL_DEFAULT		zREAL(-1)
#define		zSND_RADIUS_DEFAULT		zREAL(-1)
#define		zSND_PITCH_DEFAULT		zREAL(-999999)
const int	zSND_SLOT_NONE			=  0;	// special slot 0 => does not interrupt any other sounds, auto-locate
const int	zSND_SLOT_MAX			=  8;	// 1..zSND_SLOT_MAX

typedef int zTSoundHandle;					// 0 = noHandle

class zCSoundFX;


class zENGINE_API zCSoundSystem {
public:
	enum zTLoopType { zSND_LOOPING_DEFAULT=0, zSND_LOOPING_ENABLED, zSND_LOOPING_DISABLED };

	struct zTSound3DParams {
		float		obstruction;			// range: [0;1], percent
		float		volume;					// range: [0;1], (scripted sounds: vol=script.vol * params.vol)
		float		radius;					// range: [0;~[, cm
		zTLoopType	loopType;				// (zSND_LOOPING_DEFAULT: if scripted, uses looping specified there)
		float		coneAngleDeg;			// 0°..360°	(degrees, 0 => point source, not 0 => cone source)
		float		reverbLevel;			// range: [0;1]
		zBOOL		isAmbient3D;			// ambient3D: sound has position but no direction
		float		pitchOffset;				// halftones

		void		SetDefaults() { 
			obstruction		= 0; 
			volume			= 1;
			radius			= zSND_RADIUS_DEFAULT; 
			loopType		= zSND_LOOPING_DEFAULT;
			coneAngleDeg	= 0; 
			reverbLevel		= 1; 
			isAmbient3D		= FALSE; 
			pitchOffset		= zSND_PITCH_DEFAULT;
		};
	};

	virtual	~zCSoundSystem() {};

	virtual	zCSoundFX*			LoadSoundFX				(const zSTRING& fileName)			{ return 0; };	// a) ".wav" wave file, b) else: scriptInstance
	virtual	zCSoundFX*			LoadSoundFXScript		(const zSTRING& scriptIdentifier)	{ return 0; };
	virtual zCParser*			GetSFXParser			()									{ return 0; };
	virtual float				GetPlayingTimeMSEC		(const zSTRING& fileName)			{ return 0; };	// a) ".wav" wave file, b) else: scriptInstance

	virtual	void				SetSound3DDefaultRadius	(float defRad)	{ defaultRadius=defRad; };			// def: e.g. 15 meters
	virtual	float				GetSound3DDefaultRadius	() const		{ return defaultRadius; };

	virtual	void				SetMasterVolume			(float vol)		{};									// range: [0;1]
	virtual	float				GetMasterVolume			()				{ return 1.0F; };					// range: [0;1]

	virtual	zTSoundHandle		PlaySound				(zCSoundFX*			sfx, int slot=zSND_SLOT_NONE)=0;
	virtual	zTSoundHandle		PlaySound				(zCSoundFX*			sfx, int slot, int freq, float vol, float pan)=0;
	virtual	zTSoundHandle		PlaySound3D				(zCSoundFX*			sfx,						
														 zCVob*				sourceVob, 
														 int				vobSlot=zSND_SLOT_NONE, 
														 zTSound3DParams	*sound3DParams=0)=0;
	virtual	zTSoundHandle		PlaySound3D				(const zSTRING&		soundName,					// a) ".wav" wave file, b) else: scriptInstance
														 zCVob*				sourceVob, 
														 int				vobSlot=zSND_SLOT_NONE, 
														 zTSound3DParams	*sound3DParams=0)=0;
	virtual	void				StopSound				(const zTSoundHandle& sfxHandle) {};
	virtual	void				StopAllSounds			()								 {};
	virtual	zBOOL				GetSound3DProps			(const zTSoundHandle& sfxHandle, zTSound3DParams &sound3DParams)=0;
	virtual	zBOOL				UpdateSound3D			(const zTSoundHandle& sfxHandle, zTSound3DParams *sound3DParams=0)=0;				// spatial update (pos, orient, velo)
	virtual	void				GetSoundProps			(const zTSoundHandle& sfxHandle, int &freq, float &vol, float &pan) {};		
	virtual	void				UpdateSoundProps		(const zTSoundHandle& sfxHandle, int freq=zSND_FREQ_DEFAULT, float vol=zSND_VOL_DEFAULT, float pan=zSND_PAN_DEFAULT) {};
	virtual	zBOOL				IsSoundActive			(const zTSoundHandle& sfxHandle) { return FALSE; };

	virtual	void				DoSoundUpdate			()=0;							// called each frame
	virtual	void				SetListener				(zCVob* listenerVob) {};		// (called each frame) (pos, orient, velo)

	// Reverb
	// (only one reverbPreset can be active at one time)
	// (this interface defines the reverbPreset list, implementations have to emulate if not directly available)
	int							GetNumReverbPresets		();
	const zSTRING*				GetReverbPresetName		(int i);
	virtual	void				SetGlobalReverbPreset	(int i, float weight)	{ };			// weight range: [0;1], reverb influence
	virtual void				SetReverbEnabled		(const zBOOL bReverbEn) { };
	virtual zBOOL				GetReverbEnabled		()						{ return TRUE;	};

	// Sound Provider
	virtual	int					GetNumProvider			()						{ return 1;		};
	virtual	const zSTRING*		GetProviderName			(int i)					{ return 0;		};
	virtual	zBOOL				SetProvider				(int i)					{ return TRUE;	};

	// Speaker 
	enum zTSpeakerType {
		zSPEAKER_TYPE_2_SPEAKER=0,
		zSPEAKER_TYPE_HEADPHONE,
		zSPEAKER_TYPE_SURROUND,
		zSPEAKER_TYPE_4_SPEAKER,
		zSPEAKER_TYPE_51_SPEAKER,
		zSPEAKER_TYPE_71_SPEAKER,
		zMaxSpeakerType
	};
	virtual void				SetSpeakerType			(const zTSpeakerType speakerType)	{};
	virtual zTSpeakerType		GetSpeakerType			()									{ return zSPEAKER_TYPE_2_SPEAKER; };

	// misc
	virtual void				SetGlobalOcclusion		(float occlusion)=0;			// range: [0;1] percent, for global damping effects (like underwater), modulates obstruction of individual sounds
	virtual	float				GetCPULoad				()		{ return -1.0F; };		// result range [0;1] percent; <0 means unavailable service

	// Get/SetDopplerFactor()
	// Get/SetRollOff()

protected:
	float	defaultRadius;
};

// =======================================================================================================================

enum { zSND_CHANNEL_FRAME_RANDOM =-1 };

class zENGINE_API zCSoundFX : public zCResource {
	zCLASS_DECLARATION (zCSoundFX)
public:
			 zCSoundFX () {};
	virtual ~zCSoundFX () {};

//	const zSTRING&		zSTRING				GetName					() const					{ return soundName; };
	const zSTRING&				GetName					() const					{ return GetObjectName(); };
																					
	// Multi-Sounds																	
	virtual int					GetNumChannels			() const					{ return 0; };
	virtual int					GetNumChannelFrames		(int channel) const			{ return 0; };
	virtual	void				GetChannelFrame			(int channel, int frameNr) const {};
	virtual	void				SetChannelFrame			(int channel, int frameNr)	{};

	virtual float				GetPlayingTimeMSEC		() const					{ return 0; };	// msec
	virtual	float				GetPan					() const					{ return 0; };
	virtual	void				SetPan					(float pan)					{};
	virtual	float				GetVolume				() const					{ return 0; };
	virtual	void				SetVolume				(float vol)					{};
	virtual	int					GetFrequency			() const					{ return 0; };
	virtual	void				SetFrequency			(int freq)					{};
																					
	virtual	void				SetLooping				(zBOOL b)					{};
	virtual	zBOOL				IsLooping				() const					{ return FALSE; };

	// neu 1.25d: fixed sounds werden nicht rausgeschmissen, wenn ein neues spiel gestartet wird, oder der level wechselt!
	virtual	void				SetIsFixed				(zBOOL b)					{};
	virtual	zBOOL				GetIsFixed				() const					{ return FALSE; };


	// derived classes should implement the virtual zCResource interface !
	virtual void				GetCacheConfig			(zDWORD &cacheOutTimeMSec, zDWORD &cacheSizeMaxBytes);

protected:
//	zSTRING		soundName;
};																					

zENGINE_API extern zCSoundSystem *zsound;

// *****************************************************************************************************
//	Noop-Dummy
// *****************************************************************************************************

class zCSoundFXDummy : public zCSoundFX {
public:
	 zCSoundFXDummy() {};
	~zCSoundFXDummy() {};
	zSTRING				GetName					() const { return zSTRING(""); };
};

class zCSoundSystemDummy : public zCSoundSystem {
public:
	void				DoSoundUpdate			() {};							// called each frame
	zCSoundFX*			LoadSoundFX				(const zSTRING& fileName) { return zNEW(zCSoundFXDummy()); };

	virtual	zTSoundHandle		PlaySound				(zCSoundFX*		sfx, int slot=zSND_SLOT_NONE) { return 0;} ;
	virtual	zTSoundHandle		PlaySound				(zCSoundFX*		sfx, int slot, int freq, float vol, float pan) { return 0;} ;
	virtual void				SetGlobalOcclusion		(float){};			// range: [0;1] percent, for global damping effects (like underwater), modulates obstruction of individual sounds
	virtual	zTSoundHandle		PlaySound3D				(zCSoundFX*			sfx,						
														 zCVob*				sourceVob, 
														 int				vobSlot=zSND_SLOT_NONE, 
														 zTSound3DParams	*sound3DParams=0) {return 0;};
	virtual	zTSoundHandle		PlaySound3D				(const zSTRING&		soundName,					// a) ".wav" wave file, b) else: scriptInstance
														 zCVob*				sourceVob, 
														 int				vobSlot=zSND_SLOT_NONE, 
														 zTSound3DParams	*sound3DParams=0) {return 0;};

	virtual	zBOOL				GetSound3DProps			(const zTSoundHandle& sfxHandle, zTSound3DParams &sound3DParams)	{ return FALSE; };
	virtual	zBOOL				UpdateSound3D			(const zTSoundHandle& sfxHandle, zTSound3DParams *sound3DParams=0)  { return FALSE; };
};

#endif
