/****************************************************************
*																
* C++ SoundSystem - Miles Sound System Implementation
* File          : zSndMSS.h ()									
* Projekt       : Engine										
* Autor         : Carsten Edenfeld
* Version       : 0.02
* last modified : 13.01.99
* erstellt      : 08.10.98
* Compiler OK   : 
*																
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations:
  zSTRING::Upper() : Wird nicht immer gebraucht

*****************************************************************
- missing features:  
	Streaming audio (ab welcher Grösse?)
*****************************************************************
- comments:

   - 3d Sounds müssen manuell geupdated werden / 
     können via SetAutoUpdate3DSounds() automatisch abgehandelt werden

   - wird ein Parameter eines zCSoundFX geändert, wirken sich diese auch
     auf alle Channels und Frames aus, es sei denn es wird
	 ein Defaultparameter übergeben. Dann werden die (default-)Werte aus den jeweiligen
	 Channels/Frames benutzt
*****************************************************************************************************/

#ifndef __ZSNDMSS_H__
#define __ZSNDMSS_H__

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

#ifndef MSS_VERSION
#include "MSS.h"
#endif

#ifndef __Z3D_H__
#include "z3d.h"
#endif

#ifndef __ZDISK_H__
#include "zDisk.h"
#endif

#ifndef __ZTOOLS_H__
#include "zTools.h"
#endif

#ifndef __ZSOUND_H__
#include "zSound.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif

#ifndef __ZPARSER_H__
#include "zParser.h"
#endif

#ifdef PlaySound
#undef PlaySound
#endif


class zCWaveData;
class zCSndFrame;
class zCSndFX_MSS;

const int		MAX_PROVIDER							= 20;


// driver props class
class zCDrvProperties_MSS
{
public:

	static int	GetScriptClassSize() {
		zCDrvProperties_MSS tmp;
		return int(&tmp.dScriptEnd)-int(&tmp.volume);
	}

	int	ProviderNameToIndex(const zSTRING &n) {
		for (int i=0; i<numProviders; i++) if (provNames[i] == n) return i;
		return -1;
	}

	// public parser vars start
	float	volume;
	int		bitResolution;
	int		sampleRate;
	int		useStereo;
	int		numSFXChannels;
	zSTRING use3dProvider;

	// public parser vars end

	zBYTE	dScriptEnd;

	// FIXME: move these vars out of here!
	PCMWAVEFORMAT   waveFormat;
	HPROVIDER		providers[MAX_PROVIDER];			// array of 3d providers
	zSTRING			provNames[MAX_PROVIDER];
	int				numProviders;

};

// ----------------------------------------------------------------------------------------------
// zCActiveSnd: active sounds actually being played or being updated each frame (3d snd)
// ----------------------------------------------------------------------------------------------

class zCActiveSnd  {
	
public:

	static void			 InitPreAllocedData ();
	static void			 CleanupPreAllocedData (); // [Moos]
	static zTSoundHandle GetNextFreeHandle	();
	static zCActiveSnd*	 AllocNextFreeSnd	();

	static zBOOL		 HandleUsed			(const zTSoundHandle handle);
	static zBOOL		 GetHandleActive	(const zTSoundHandle handle);
	static int			 GetHandleIndex		(const zTSoundHandle handle);
	static zCActiveSnd*  GetHandleSound		(const zTSoundHandle handle);

	static void			 AddSound			(zCActiveSnd *newSnd);
	static void			 RemoveSound		(zCActiveSnd *newSnd);

	static void			 StopSoundsByFrame  (zCSndFrame *frame);
	static void			 RemoveSoundsByFrame(zCSndFrame  *frame );
	static void			 RemoveSoundByVobSlot(const zCVob *vob, const int slot);

	static void			 UpdateSoundsByFrame(zCSndFrame  *frame );
	static void			 ResumeSoundsByFrame(zCSndFrame  *frame );
	
	static zBOOL		 GetSoundActive		(zCActiveSnd *snd);
	static zBOOL		 GetFrameActive		(zCSndFrame  *frm);
	static int			 GetNumActive		();
	static void			 NewFrame			();
	static int			 GetNum3DSamplesUsed();
	static int			 GetNumAmbientSamplesUsed();
	static void			 DebugInfo			();
	static void			 UpdateReverb		(const float weight);

	// sound handler related
						 zCActiveSnd		();
						~zCActiveSnd		();

	int					 CalcListenerPan	();
	int					 CalcListenerVolume	();
	void				 IncAge				()									{ age++; };
	zBOOL				 RequestChannel		(); // looks for oldest sample and removes it !
	zBOOL				 RequestChannel3D	();
	zBOOL				 Is3DSnd			() const							{ return is3D; };
	zBOOL				 IsAmbient			() const							{ return isAmbient; };
	zBOOL				 IsAssigned			()									{ return (sample || sample3D);	};
	zBOOL				 IsOnHold			()									{ return (IsAssigned() && !active); };
	zBOOL				 HasBeenUpdatedThisFrame();
	float				 GetVolume			();
	// auto thingys
	void				 AutoCalcObstruction(zBOOL immediate=FALSE);


	void				 Release			();
	void				 Initialize			();
	

	friend zBOOL	operator== (const zCActiveSnd& s1, const zCActiveSnd& s2) 	{ return (s1.handle == s2.handle); };

	// variables

	static zCArraySort <zCActiveSnd*>  activeSndList;
	static zDWORD				lastHandle ;
	static int					maxChannels;
	static zBOOL				autoUpdate3D;

	zTSoundHandle				handle;

	HSAMPLE						sample;
	H3DSAMPLE					sample3D;

	zDWORD						age;

	zCSoundSystem::zTLoopType	loopType;
	
	float						radius;
	float						reverbLevel;
	float						pitchOffset;
	float						volWeight;
	float						obstruction;
	float						obstructionToGo;
	float						volumeToGo;
	int							autoObstructTimer;

	// bit props
	struct {
		zBYTE						active			:	1;
		zBYTE						looping			:	1;
		zBYTE						isAmbient		:	1;
		zBYTE						is3D			:	1;
		zBYTE						allocated		:	1;
		zBYTE						vobSlot			:	3;			// [0..7]
	};

	// other props
	zUINT8						pan;			// [0..				
	zUINT8						volume;
	zUINT16						rate;			// 0-65000

	int							muteTime;
	int							frameCtr;

	zPOINT3						lastPos;
	float						lastTime;	
	zCVob*						sourceVob;
	zCSndFrame*					sourceFrm;
	zCSndFX_MSS*				sourceSnd;

private:
	static zCArray<zCActiveSnd*>preAllocedSndList;
	static zCActiveSnd*			nextFreeSnd;

};

// ----------------------------------------------------------------------------------------------
// zCSndChannel: (Stimmbänder/Voices)
// ----------------------------------------------------------------------------------------------
class zCSndChannel {
public:
			   zCSndChannel		(); 
			  ~zCSndChannel		();

	int		   GetRefCtr		() const									{ return refCtr; };
	void	   AddRef			()											{ ++refCtr; };

	int		   GetNumFrames		() const									{ return frameList.GetNumInList(); };
	zBOOL	   Loaded			() const									{ return loaded; };
	void	   SetLoaded		(zBOOL b)									{ loaded = b; };

	// variables
	int							actFrame;
	int							refCtr;
	zBOOL						loaded;
	zCArray	<zCSndFrame*>		frameList;
};


// ----------------------------------------------------------------------------------------------
// zCSndFrame : basis sample definitionen wie in im script beschrieben (C_SFX_DEF)
// ----------------------------------------------------------------------------------------------
class zCSndFrame {
public:

	static int		   GetScriptClassSize	()								{ zCSndFrame tmp; return int(&tmp.dScriptEnd) -int(&tmp.fileName);	};

					   zCSndFrame			();
					  ~zCSndFrame			();

	// resource handling
	void			   CacheIn				();
	void			   CacheOut				();
	
	// other
	int				   CalcPitchVariance	();
	void			   CalcPitchOffset		(const float offset);
	void			   SetDefaultProperties	();
	inline void		   SetWave				(zCWaveData *newWave)			{ wav = newWave;	};
	inline zCWaveData* GetWave				() const						{ return wav;		};

public:

	// public parser vars
	zSTRING				fileName;
	float				pitchOffset;
	float				pitchVariance;
	int					defVolume;
	zBOOL				looping;
	int					loopStartOffset;
	int					loopEndOffset;
	float				reverbLevel;
	zSTRING				pfxName;
	// public parser vars end

	zBYTE				dScriptEnd;
	
	zSTRING				instance;

	int					actVolume;
	int					actRate;
	int					actPan;

private:
	zCWaveData			*wav;
	
};

// ----------------------------------------------------------------------------------------------
// zCWaveData: map data to be cached in/out
// ----------------------------------------------------------------------------------------------

class zCWaveData {
public:
							zCWaveData			()																{ Init();			  };
							zCWaveData			(zSTRING &name);

	// Ref Ctr Geschichten
	int						GetRefCtr			() const						{ return refCtr; };
	zCWaveData*				AddRef				()								{ ++refCtr; return this; };
	int						Release				();  


	// cache methods
	void					CacheIn				();
	void					CacheOut			();
	inline const zSTRING&	GetName				()	const						{ return fileName; };

	// data access
	int						GetSize				();
	zSTRING					GetName				()								{ return fileName;		};
	AILSOUNDINFO*			GetInfo				() const						{ return info;			};
	void*					GetAddr				() const						{ return memAddr;		};
	int						GetRate				() const						{ return info->rate;	};

	// various
	zBOOL					CheckForCorrectFormat(const zBOOL is3D = FALSE);

	// variables
	int					size;						// size of frame 
	void*				memAddr;					// addr. in mem 
	float				msLength;

	AILSOUNDINFO*		info;
	zSTRING				fileName;
	int					refCtr;


protected:
							~zCWaveData			();
private:
	void					Init				();

	int					cacheInCount;
	zBOOL				adpcmCompressed;
};

// ----------------------------------------------------------------------------------------------
// zCWavePool: Container für alle alloziierten zCWaveData Objekte. Thread Safe.
// kann nur eine globale Instanz geben. Access über zCWavePool::GetPool()
// ----------------------------------------------------------------------------------------------

class zCWavePool : public zCArraySort <zCWaveData*> 
{
public:

	static zCWavePool&	GetPool			()							{	static zCWavePool thePool; return thePool;	};

	~zCWavePool();

	zCWaveData*			CacheIn			(zSTRING &fileName);
	void				CacheIn			(zCWaveData* wave);
	void				CacheOut		(zCWaveData* wave);
	int					ReleaseWave		(zCWaveData* wave);
	void				DebugInfo		();
	void				DebugInfo2		();

	// active wave list methods
	void				NewFrame		();
	zBOOL				IsWaveActive	(zCWaveData* wave)			{	return activeWaveList.IsInList(wave);		};
	int					GetNumActive	()							{	return activeWaveList.GetNum();				};
	zCWaveData*			GetActiveWave	(const int num)				{	return activeWaveList[num];					};

private:

	zCWavePool();

	zCWaveData*			helpWave;
	zCCriticalSection	waveGuard;
	zCArray<zCWaveData*>activeWaveList;			// liste mit allen aktiven waves (wird pro (n) frames aufgebaut)

};


// ----------------------------------------------------------------------------------------------
// zCSndSys_MSS : Main MSS SoundSys Class
// ----------------------------------------------------------------------------------------------

class zCSndSys_MSS : public zCSoundSystem {
public:

	// initial sound system states can be set via these static methods at startup;
	// can be overridden by a C_SNDSYS_CFG Instance in sfx.d
	static void		SetPreferedSampleRate(const int freq)		{ prefs.sampleRate = freq; };
	static int		GetPreferedSampleRate()						{ return prefs.sampleRate; };

	static void		SetStereoSFXEnabled	(const zBOOL st)		{ prefs.useStereo = st;    };
	static zBOOL	GetStereoSFXEnabled	(const zBOOL st)		{ return prefs.useStereo ; };
	
	static void		SetSFXResolution(const int numBits)			{ prefs.bitResolution = numBits; };
	static int		GetSFXResolution()							{ return prefs.bitResolution; };

	static void		SetInitialSFXVolume(const float v)			{ prefs.volume	= v;		};
	static float	GetInititalSFXVolume()						{ return prefs.volume;		};

	static int		GetInitialNumSFXChannels()					{ return prefs.numSFXChannels; };
	static void     SetInitialNumSFXChannels(const int numCh)	{ prefs.numSFXChannels = numCh; };
	static zBOOL	EvalFunc				(const zSTRING &s, zSTRING &msg);
	static void		FrmCon_ParamChanged		(const zSTRING &s);
	static void		SfxCon_ParamChanged		(const zSTRING &s);

	// virtuals
						zCSndSys_MSS			() ;
	virtual			   ~zCSndSys_MSS			() ;

	zCSoundFX*			LoadSoundFX				(const zSTRING& fileName) ;
	zCSoundFX*			LoadSoundFXScript		(const zSTRING& fileName) ;

	zTSoundHandle		PlaySound				(zCSoundFX* sfx, int slot=zSND_SLOT_NONE);
	zTSoundHandle		PlaySound				(zCSoundFX* sfx, int slot, int freq, float vol, float pan);
	zTSoundHandle		PlaySound3D				(zCSoundFX* sfx, zCVob* sourceVob, int vobSlot=zSND_SLOT_NONE,zTSound3DParams *sound3DParams=0);
	zTSoundHandle		PlaySound3D				(const zSTRING& fileName, zCVob* sourceVob, int slot=zSND_SLOT_NONE,zTSound3DParams	*sound3DParams=0);
	void				StopSound				(const zTSoundHandle & sfxHandle);
	void				StopAllSounds			();
	zBOOL				UpdateSound3D			(const zTSoundHandle& sfxHandle, zTSound3DParams *sound3DParams);
	void				GetSoundProps			(const zTSoundHandle& sfxHandle, int &freq, float &vol, float &pan);
	zBOOL				GetSound3DProps			(const zTSoundHandle& sfxHandle, zTSound3DParams &sound3DParams);
	void				UpdateSoundProps		(const zTSoundHandle& sfxHandle, int freq=zSND_FREQ_DEFAULT, float vol=zSND_VOL_DEFAULT, float pan=zSND_PAN_DEFAULT) ;
	zBOOL				IsSoundActive			(const zTSoundHandle& sfxHandle) ; 
	float				GetPlayingTimeMSEC		(const zSTRING& fileName);

	void				DoSoundUpdate			();							// called each frame
	void				SetListener				(zCVob* listenerVob);
	zCParser*			GetSFXParser			();

	// Reverb
	// (only one reverbPreset can be active at one time)
	void				SetGlobalReverbPreset	(int i, float weight);		// weight range: [0;1], reverb influence
	void				SetReverbEnabled		(const zBOOL bReverbEn);
	zBOOL				GetReverbEnabled		()						{ return m_bReverbEnabled;	};


	// Sound Provider
	int					GetNumProvider			();
	const zSTRING*		GetProviderName			(int i);
	zBOOL				SetProvider				(int i);

	// misc
	void				SetGlobalOcclusion		(float occlusion);				// range: [0;1] percent, for global damping effects (like underwater), modulates obstruction of individual sounds
	float				GetCPULoad				();								// result range [0;1] percent; <0 means unavailable service

	void				SetSpeakerType			(const zTSpeakerType speakerType);
	zTSpeakerType		GetSpeakerType			()					 { return speakerType;	};

	// additional MSS related public methods
	HDIGDRIVER			GetDigitalDriverHandle	();
	void				InitializeMSS			();
	void				SetAutoUpdate3DSounds	(const zBOOL auto3D) { zCActiveSnd::autoUpdate3D = auto3D; };
	zBOOL				GetAutoUpdate3DSounds	() const			 { return zCActiveSnd::autoUpdate3D ;  };
	void				SetNumAudioChannels		(int ch); 
	int					GetNumAudioChannels		() const			{ return prefs.numSFXChannels ;};

	void				SetVolumeSFX			(const float vol); 
	void				SetMasterVolume			(float vol);									// range: [0;1]
	float				GetMasterVolume			(); 
	void				MuteSFX					();
	int					GetUsedSoundMem			();

	int					GetNumSoundsPlaying		();
	void				RemoveAllActiveSounds	();

	// tmp, Debug
	float				GetActiveVolume			(const zTSoundHandle& sfxHandle);
private:

	static void			CloseProvider			();

	zCSoundFX *			LoadMulti				(const zSTRING &id, const int reqChannel);
	zCSoundFX *			LoadSingle				(const zSTRING &id);

	// ambient sounds
	zTSoundHandle		PlaySound3DAmbient		(zCSoundFX* sfx, zCVob* sourceVob, int vobSlot=zSND_SLOT_NONE,zTSound3DParams *sound3DParams=0);
	void				UpdateSoundPropsAmbient	(zCActiveSnd *snd, zTSound3DParams *params = 0) ;

	// various
	void				DisposeAllSampleHandles	();
	zBOOL				Start3DProvider			(int index);

	static zCDrvProperties_MSS	prefs;  // tmp, can be made private after reverbVars are moved out !
	zTSpeakerType				speakerType;
	int							globalReverbPreset;
	zBOOL						m_bReverbEnabled;

};


// ----------------------------------------------------------------------------------------------
// zCSndSys_MSS : Main MSS SoundFX Class
// ----------------------------------------------------------------------------------------------

class zCSndFX_MSS : public zCSoundFX {

public:
	static void		    NewFrame				();

						zCSndFX_MSS				() ;

	// Multi-Sounds
	int					GetNumChannels			() const			{ return channelList.GetNumInList(); };
	int					GetNumChannelFrames		(int channel) const	{ return channelList[channel]->GetNumFrames(); };
	void				GetChannelFrame			(int channel, int frameNr) const;
	void				SetChannelFrame			(int channel, int frameNr) ;

	float				GetPan					() const			{ return pan; };
	float				GetVolume				() const		    { return volume; };
	int					GetFrequency			() const			{ return rate; };
	void				SetPan					(float newPan);
	void				SetVolume				(float inVol);
	void				SetFrequency			(int   freq);

	float				GetPlayingTimeMSEC		() const;
	zBOOL				LoadResourceData		();
	zBOOL				ReleaseResourceData		();

	void				SetLooping				(zBOOL loop);
	zBOOL				IsLooping				() const			{ return ( channelList[0]->frameList[0]->looping );		};

	// neu 1.25d: fixed sounds werden nicht rausgeschmissen, wenn ein neues spiel gestartet wird, oder der level wechselt!
	void				SetIsFixed				(zBOOL b)					{ m_bIsFixed= b;};
	zBOOL				GetIsFixed				() const					{ return m_bIsFixed; };


	zBOOL				IsActive				();

	zCSndFrame*			GetFrame				(int c, int f)		{ return channelList[c]->frameList[f];				   };
	zCSndFrame*			GetActFrame				()					{ return channelList[actChannel]->frameList[actFrame]; };

	zDWORD				GetResSizeBytes			();

private:
	virtual			   ~zCSndFX_MSS				();

	// channel access
	void				LoadChannel				(const int chNr); // does explicit AddRef() on sfx if necessary!
	void				CacheInActChannel		();
	void				CacheOutActChannel		();

	// frame access
	void				CacheInActFrame			();
	void				CacheOutActFrame		();
	void				ChooseVariance			();

	// properties
	void				SetDefaultProperties	();
	void				SetAutoDeletion			(const zBOOL &b)	{ autoDelete = b; };
	zBOOL				GetAutoDeletion			()	const			{ return autoDelete; };
	
	void				CheckCanBeCachedOut		();

	float			volume;
	float			pan;
	int				rate;
	zBOOL			autoDelete;
	float			startPlayTime;
	zBOOL			m_bIsFixed;
	
	int				actChannel;
	int				actFrame;
	int				actChannelFrame;

	zCArray<zCSndChannel*> channelList;			// chord channels

	friend class zCSndSys_MSS;

};


// helpclass, which avoids heavy allocating of miles internal 3d-sample heap objects
class zCHandleManager
{
public:
	H3DSAMPLE Alloc3DSample		();
	HSAMPLE	  AllocSample		();
	void	  Free3DSample		(H3DSAMPLE sample);
	void	  FreeSample		(HSAMPLE   sample);
	void	  DisposeAllSamples	();
private:

	zCArray<H3DSAMPLE>free3DSamples;
	zCArray<HSAMPLE  >freeSamples;
	
};


// enable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 

#endif