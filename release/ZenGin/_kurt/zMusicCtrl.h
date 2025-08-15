 

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DynamicMusic - Implementation
* File          : zMusicCtrl.h 
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.97pre
* last modified : 21.10.00
* erstellt      : 06.09.00										
* Compiler OK   : 
*																
*********************************************************************************
- known bugs: 

*********************************************************************************
- possible optimizations: 

*********************************************************************************
- missing features: 

*********************************************************************************
- comments:
  
TODO:

*********************************************************************************/



#ifndef __ZMUSICCTRL_H__
#define __ZMUSICCTRL_H__

#ifndef __ZENGINE_H__
#include <zEngine.h>
#endif

#ifndef __ZVOBMISC_H__
#include <zVobMisc.h>
#endif


class zCEventMusicControler : public zCEventMessage {
	zCLASS_DECLARATION	( zCEventMusicControler )
public:
	enum zTEventMusicControlerSubType {
		zEVENT_START_SPECIAL_SGT,
		zEVENT_STOP_SPECIAL_SGT,
		zEVENT_MUSICCONTROLER_COUNT
	};

	zCEventMusicControler( const zTEventMusicControlerSubType sub, const zSTRING sgt );

	// zCEventMessage Interface
	int						MD_GetNumOfSubTypes	() { return zEVENT_MUSICCONTROLER_COUNT; };
	zSTRING					MD_GetSubTypeString	( int n );
	zTTimeBehavior			MD_GetTimeBehavior	();
	zREAL					MD_GetMinTime		();

protected:
	zCEventMusicControler() { sgt = ""; };

	void					Archive				( zCArchiver& arc );
	void					Unarchive			( zCArchiver& arc );

	zSTRING					sgt;

private:
	friend class zCMusicControler;
};


class zCMusicControler : public zCEffect 
{
	zCLASS_DECLARATION	( zCMusicControler ) 
public:
	zCMusicControler();

	virtual void			OnMessage					( zCEventMessage *eventMessage, zCVob* sourceVob ); 
	virtual void			ThisVobRemovedFromWorld		(zCWorld *homeWorld);
};




#endif //#ifndef __zMusicCtrl_H__