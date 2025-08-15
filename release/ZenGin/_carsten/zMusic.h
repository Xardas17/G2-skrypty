/******************************************************************************** 
 
     $Workfile:: zMusic.h            $              $Date:: 31.01.01 18:23  $
     $Revision:: 13                  $             $Modtime:: 31.01.01 14:20 $
     $Author:: Speckels               $
	 Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description: c++ dynamic music system - abstract base class
 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 13 $ ($Modtime: 31.01.01 14:20 $)

#ifndef __ZMUSIC_H__
#define __ZMUSIC_H__

#ifndef __ZCORE_H__
#include "zcore.h"
#endif

#ifndef __ZSTING_H__
#include "zstring.h"
#endif

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

// transition types to be used from last theme to current theme, determins the embellishment type of the transition pattern
enum zTMus_TransType	{ 
	zMUS_TR_DEFAULT		= 0, 
	zMUS_TR_NONE		= 1,
	zMUS_TR_GROOVE		= 2,
	zMUS_TR_FILL		= 3, 
	zMUS_TR_BREAK		= 4, 
	zMUS_TR_INTRO	    = 5, 
	zMUS_TR_END			= 6,
	zMUS_TR_ENDANDINTRO = 7
};
// transition sub types to be used from last theme to current theme, determins if jingles/themes should start 
// immedeately.on next beat or on next measure
enum zTMus_TransSubType  { 
	zMUS_TRSUB_DEFAULT  = 0,
	zMUS_TRSUB_IMMEDIATE= 1, 
	zMUS_TRSUB_BEAT		= 2, 
	zMUS_TRSUB_MEASURE	= 3
};

enum zTMus_EventType {
	zMUS_EVENT_THEME_CHG = 1,
	zMUS_EVENT_BEAT		 = 2,
	zMUS_EVENT_MEASURE	 = 4,
	zMUS_EVENT_TRANSITION= 8
};


const float zMUS_JINGLE_VOL_DEFAULT = -1;
const float zMUS_THEME_VOL_DEFAULT  = -1;

// base theme class
class zCMusicTheme {
protected:
	zSTRING			    fileName;
	float				vol;
	zBOOL				loop;
	float				reverbMix;		// 21-Jan-01 [PELZER]
	float				reverbTime;		// 21-Jan-01 [PELZER]
	zTMus_TransType		trType;
	zTMus_TransSubType	trSubType;
	zBYTE				dScriptEnd;
	zSTRING				name;
public:	
	
	static int  GetScriptClassSize	 ()									{
		zCMusicTheme tmp;
		return int(&tmp.dScriptEnd)-int(&tmp.fileName);
	}

			 zCMusicTheme () {};
	virtual ~zCMusicTheme () {};

	const zSTRING&		GetName				 ()		   { return name;	   };
	const zSTRING&		GetFileName			 ()		   { return fileName;};
	zTMus_TransType		GetTransitionType	 () const  { return trType;    };
	zTMus_TransSubType  GetTransitionSubType () const  { return trSubType; };
	zBOOL				GetIsLooping		 () const  { return loop;	   };
	float				GetVolume			 () const  { return vol;	   };	
	float				GetReverbMix		 () const  { return reverbMix; };	// 21-Jan-01 [PELZER]
	float				GetReverbTime	     () const  { return reverbTime;};	// 21-Jan-01 [PELZER]	

	void SetName			 ( const zSTRING &id   )			{ name		= id;	 };
	void SetFileName		 ( const zSTRING &name  )			{ fileName	= name;  };
	void SetTransitionType	 ( const zTMus_TransType &tr )		{ trType	= tr;    };
	void SetTransitionSubType( const zTMus_TransSubType &trSub ){ trSubType	= trSub; };
	void SetIsLooping		 ( const zBOOL b )					{ loop		= b;     };
	void SetVolume			 ( const float v )					{ vol		= v;	 };			
	void SetReverbMix		 ( const float r )					{ reverbMix = r;	 };	// 21-Jan-01 [PELZER]
	void SetReverbTime	     ( const float r )					{ reverbTime = r;	 };	// 21-Jan-01 [PELZER]
	
		
	
	virtual zBOOL	IsActive ()	const			   { return FALSE;	   };
};

// base jingle class 

typedef int zTMus_JingleHandle;

class zCMusicJingle {
			
protected:
	zSTRING			   fileName;
private:
	zBOOL			   loop;
	float			   vol;
	zTMus_TransSubType trSubType;	// need only sub types for jingles
	zBYTE			   dScriptEnd;
protected:
	int				   refCtr;
	zSTRING			   name;

public:	

	static int  GetScriptClassSize	 ()									{
		zCMusicJingle tmp;
		return int(&tmp.dScriptEnd)-int(&tmp.fileName);
	}

			 zCMusicJingle() {  refCtr = 1; };
	virtual ~zCMusicJingle() {};
	
	const	zSTRING&		GetName					() const	{ return name;       };
	const	zSTRING&		GetFileName				() const	{ return fileName; };
	zTMus_TransSubType		GetTransitionSubType	() const	{ return trSubType;  };
	int						GetRefCtr				() const	{ return refCtr;     };

	void					SetName					( const zSTRING &n    )				{ name = n; };
	void					SetFileName				( const zSTRING &name )				{ fileName = name;	 };
	void					SetTransitionSubType    ( const zTMus_TransSubType &trSub ) { trSubType = trSub; };

	virtual zCMusicJingle*	AddRef					()			{ ++refCtr; return this; };
	virtual int				Release					()			{ delete this; return 0; };
	zBOOL					GetIsLooping			() const	{ return loop;	   };
	virtual zBOOL			IsPlaying			    () const    { return FALSE;  };
	virtual void			StopPlaying				()			{};

	virtual	void			CacheIn					() {};
	virtual	void			CacheOut				() {};
};


// base music system class
class zCMusicSystem {
protected:
	float volume;
	float reverb; //[PELZER] New variable.

	static zBOOL s_musicSystemDisabled;
public:

	static void		DisableMusicSystem(zBOOL disable=TRUE);
	static zBOOL	IsMusicSystemDisabled()					{ return s_musicSystemDisabled; };

    virtual ~zCMusicSystem(){}; // [Moos], nur so werden die echten Musiksysteme auch gelöscht.

	// simple access, load and plays new theme at once, disposes last played theme automatically & releases theme when finished
	virtual void		  PlayThemeByScript( const zSTRING &id, const int manipulate = 0, zBOOL *done = NULL )				{};	//[PELZER] 01/19/01 Optionalen Parameter 'manipulate' hinzugefügt

	// advanced access, cache handling upon caller
	virtual zCMusicTheme *LoadThemeByScript( const zSTRING &id )				{	return 0;	};
	virtual zCMusicTheme *LoadTheme		   ( const zSTRING &file )				{	return 0;	};
	virtual void		  PlayTheme		   ( zCMusicTheme		*theme,
										     const float				&volume = zMUS_THEME_VOL_DEFAULT,
										     const zTMus_TransType		&tr		= zMUS_TR_DEFAULT,
										     const zTMus_TransSubType	&trSub  = zMUS_TRSUB_DEFAULT )	{};

	virtual zCMusicTheme  *GetActiveTheme ()									{	return 0;	};

	// Jingles. There must be a theme already active before calling any related funcs

	// simple access, load and plays jingle at once, disposes jingle when finished
	// (however looped jingles have to be stopped seperately)
	virtual zTMus_JingleHandle PlayJingleByScript( const zSTRING &id   )			{   return 0;   };
	virtual void		   StopJingleByScript( const zSTRING &id   )			{};

	// advanced access, cache handling upon caller
	virtual zCMusicJingle *LoadJingleByScript( const zSTRING &id   )			{	return 0;	};
	virtual zCMusicJingle *LoadJingle		 ( const zSTRING &file )			{	return 0;	};
	
	virtual zTMus_JingleHandle PlayJingle	 ( const zCMusicJingle	*jingle,
										   const float				&volume = zMUS_JINGLE_VOL_DEFAULT,
										   const zTMus_TransSubType &trSub  = zMUS_TRSUB_DEFAULT ) { return 0; };

	virtual	void		   StopJingle	 (const zTMus_JingleHandle& jHandle) {};
	virtual	zBOOL		   IsJingleActive(const zTMus_JingleHandle& jHandle) { return FALSE; };

	virtual	void		   DoMusicUpdate	 ()=0;	// called each frame

	// experimental

	virtual void	AddEventCallBackFunc	( const zTMus_EventType &flags, void (*ev)(const zTMus_EventType &occuredEvents) ) {};
	virtual void	RemoveEventCallBackFunc ( void (*ev)(const zTMus_EventType &occuredEvents) ) {};

	virtual void	Mute()										{};
	virtual void	Stop()										{};

	virtual void	SetVolume		  ( const float v )			{ volume = v; };   // 0..1
	virtual float	GetVolume		  ( )	const				{ return volume; };
//	virtual void	SetReverb		  ( const float r )			{ reverb = r; };   // <= 0.0f //[PELZER] New function.
//	virtual float	GetReverb		  ( )	const				{ return reverb; }; //[PELZER] New function.


	virtual zBOOL	IsAvailable		  ( const zSTRING &id )		{ return FALSE; }; //[PELZER] New function.

};

// *****************************************************************************************************
//	Noop-Dummy
// *****************************************************************************************************

class zCMusicSys_Dummy : public zCMusicSystem {
public:
	zCMusicTheme  *LoadThemeByScript( const zSTRING &id )				{	return zNEW( zCMusicTheme );	};
	zCMusicTheme  *LoadTheme		( const zSTRING &file )				{	return zNEW( zCMusicTheme );	};
	zCMusicJingle *LoadJingleByScript( const zSTRING &id   )			{	return zNEW( zCMusicJingle);	};
	zCMusicJingle *LoadJingle		 ( const zSTRING &file )			{	return zNEW( zCMusicJingle);	};

	void		  DoMusicUpdate	 ()	 {};	// called each frame
};

extern zCMusicSystem *zmusic;

#endif