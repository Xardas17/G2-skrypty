/******************************************************************************** 
 
     $Workfile:: zvideoplayer.h       $                $Date:: 4.12.00 18:22    $
     $Revision:: 9                    $             $Modtime:: 4.12.00 18:00    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
  
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 9 $ ($Modtime: 4.12.00 18:00 $)

#ifndef __ZVIDEOPLAYER_H__
#define __ZVIDEOPLAYER_H__


class zCVideoPlayer
{
public:	

	zCVideoPlayer				();
	virtual ~zCVideoPlayer		();

	virtual zBOOL	OpenVideo	(zSTRING filename);
	virtual zBOOL	CloseVideo	();			

	// Playing the Video beginning with frame "frameNr"
	// This Methode will return only when the video has stopped.
	zBOOL			Play		(int frameNr = 0);		

	// virtual play-Methods for external use.
	// used also in method Play(frameNr).	
	virtual zBOOL	PlayInit	(int frameNr=0);
	virtual zBOOL	PlayFrame	();
	virtual zBOOL	PlayDeinit	();		
	
	// Pause, Unpause and Stop the video
	virtual zBOOL	Pause		();
	virtual zBOOL	Unpause		();
	virtual zBOOL	Stop		();

	void	SetLooping			(zBOOL loop)		{ mLooping		= loop;		};	
	void	SetScaleValue		(zREAL value=1)		{ mScaleValue	= value;	};
	zREAL	GetScaleValue		()					{ return mScaleValue;		};

	// Get some informations	
	virtual zBOOL	IsPlaying	()  { return mPlaying;		};	

	virtual zBOOL	ToggleSound			()	{ return (mSoundOn = !mSoundOn); };
	virtual zREAL	SetSoundVolume(zREAL v) { return mSoundVolume=v; };
		
	zBOOL	IsScaleOn			()	{ return mScaleValue!=1; };	
	zBOOL	IsSoundOn			()	{ return mSoundOn;		};
	zBOOL	IsLooping			()	{ return mLooping;		};
	zBOOL	IsPaused			()  { return mPaused;		};			
	
	zSTRING	GetVideoFilename	()	{ return mVideoFilename; };
	zREAL	GetSoundVolume		()  { return mSoundVolume; };	

protected:

	// virtual methods for internal use
	// used in method PlayFrame();
	virtual zBOOL	PlayGotoNextFrame();
	virtual zBOOL	PlayWaitNextFrame();
	
protected:
	
	zSTRING	mVideoFilename;
	zBOOL	mLooping;
	zBOOL	mPaused;	// Is playing paused?		
	zBOOL	mPlaying;	// Is the video playing?
	zBOOL	mSoundOn;	
	zREAL	mSoundVolume;	// 0..1	
	zREAL	mScaleValue;
};

#endif

