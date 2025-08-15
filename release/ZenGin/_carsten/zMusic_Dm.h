/****************************************************************
*																
* C++ dynamisches MusikSystem - Direct Music Implementation
* File          : zMusic_DM.h ()								
* Author		: Carsten Edenfeld	
* Projekt       : Engine										
* Version       : 0.03
* last modified : 20.12.98
* erstellt      : 20.12.98
* Compiler OK   : 
*																
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations:
*****************************************************************
- missing features:  
*****************************************************************
- comments:
****************************************************************/

#ifndef __ZMUSIC_DM_H__
#define __ZMUSIC_DM_H__

#ifndef __ZMUSIC_H__
#include "zMusic.h"
#endif

#ifndef __ZTOOLS_H__
#include "zTools.h"
#endif

const int NUM_MOTIFS = 16;

struct IDirectMusicSegment;
struct IDirectSoundBuffer;

class zCMusicSys_DirectMusic;

// dm theme class
class zCMusicTheme_DM : public zCMusicTheme  {
friend class zCMusicSys_DirectMusic;
 
public:	
	IDirectMusicSegment *seg;
	//IDirectMusicBand	*band;  // contains DLS Data, assumes only 1 default band per segment

	zCMusicTheme_DM () { seg = 0; };
	~zCMusicTheme_DM () ;

	zBOOL	IsActive ()	const			   { return FALSE;	   };
};

// dm jingle class 
class zCMusicJingle_DM : public zCMusicJingle {
public:	

	zCMusicJingle_DM()	{};
	~zCMusicJingle_DM() {};
	
	// virtuals
	zCMusicJingle*	AddRef					()			{ ++refCtr; return (zCMusicJingle*)this; };
	int				Release					()			{ delete this; return 0; };

	zBOOL			IsPlaying			    () const    { return FALSE;  };
	void			StopPlaying				()			{};

	void			CacheIn					() {};
	void			CacheOut				() {};
};


// dm music system class - fixme: this should be part of the base class (dito: zCSndSys_MSS::CSndDrvProperties)
class CMusDrvProperties {
public:
	// public parser vars start
	float volume;
	int	  bitResolution;
	int	  globalReverbEnabled;
	int	  sampleRate;
	int	  numChannels;
	int   reverbBufferSize;
	// public parser vars end
	zBYTE dScriptEnd;

	static int GetScriptClassSize() {
		CMusDrvProperties tmp;
		return int(&tmp.dScriptEnd) - int(&tmp.volume);
	}

} ;

class zCMusicSys_DirectMusic : public zCMusicSystem  {
private:
	IDirectSoundBuffer* DMLoad3DSoundBuffer();
public:

	CMusDrvProperties prefs;
	zCMusicTheme *actTheme;
	zCMusicTheme *defTheme;    // default theme being loaded at startup, includes loading themes & default jingles

	void	LoadDefaultData();

public:
	
	zCMusicSys_DirectMusic();
	~zCMusicSys_DirectMusic();

	void				PlayThemeByScript	( const zSTRING &id, const int manipulate = 0, zBOOL *done = NULL ); // 21-Jan-01 [PELZER]Optionalen Parameter 'manipulate' hinzugefügt
	zCMusicTheme*		LoadThemeByScript	( const zSTRING &id );
	zCMusicTheme*		LoadTheme			( const zSTRING &file );
	
	void				PlayTheme			(	zCMusicTheme*			theme,
												const float				&volume = zMUS_THEME_VOL_DEFAULT,
												const zTMus_TransType	&tr		= zMUS_TR_DEFAULT,
												const zTMus_TransSubType &trSub  = zMUS_TRSUB_DEFAULT );


	zCMusicTheme*		GetActiveTheme		()											{	return actTheme;	};
	zTMus_JingleHandle	PlayJingleByScript	( const zSTRING &id   );
	void				StopJingleByScript	( const zSTRING &id   );
	zCMusicJingle*		LoadJingleByScript	( const zSTRING &id   );
	zCMusicJingle*		LoadJingle			( const zSTRING &file );
	
	zTMus_JingleHandle  PlayJingle			( const zCMusicJingle		*jingle,
											  const float				&volume = zMUS_JINGLE_VOL_DEFAULT,
									          const zTMus_TransSubType  &trSub  = zMUS_TRSUB_DEFAULT );

	void		   StopJingle				( const zTMus_JingleHandle& jHandle)		{};
	zBOOL		   IsJingleActive			( const zTMus_JingleHandle& jHandle)		{ return FALSE; };

	void		   DoMusicUpdate			();	// called each frame

	void	Mute							();
	void	Stop							();
	void	SetVolume						( const float v );
	float	GetVolume						()	const									{ return prefs.volume; };

	zBOOL	IsAvailable						( const zSTRING &id ); //[PELZER] New function.
};
#endif