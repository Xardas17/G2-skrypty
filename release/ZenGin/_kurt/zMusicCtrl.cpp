 

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DynamicMusic - Implementation
* File          : zMusicCtrl.cpp 
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



#include "zMusicCtrl.h"
#include "zArchiver.h"



// ============================================================================================================

zCLASS_DEFINITION			( zCMusicControler		, zCEffect		,	0,	0)
zCLASS_DEFINITION			( zCEventMusicControler	, zCEventMessage,	0,	0)

// ============================================================================================================



/*--------------------------------------------------------------------------

    zSTRING zCEventMusicControler :: MD_GetSubTypeString( int n )

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
zSTRING zCEventMusicControler :: MD_GetSubTypeString( int n )
{
	switch( n ) 
	{
	case	zEVENT_START_SPECIAL_SGT:	
			return zSTRING("START_SPECIAL_SGT");
	case	zEVENT_STOP_SPECIAL_SGT:	
			return zSTRING("STOP_SPECIAL_SGT");
	}
	return zSTRING("");
}



/*--------------------------------------------------------------------------

    zCEventMusicControler::zTTimeBehavior zCEventMusicControler :: MD_GetTimeBehavior()

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
zCEventMusicControler::zTTimeBehavior zCEventMusicControler :: MD_GetTimeBehavior() 
{ 
	return TBZero;
}



/*--------------------------------------------------------------------------

    zREAL zCEventMusicControler :: MD_GetMinTime()

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
zREAL zCEventMusicControler :: MD_GetMinTime() 
{ 
	return 0;
}



/*--------------------------------------------------------------------------

    void zCEventMusicControler :: Archive( zCArchiver& arc )

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCEventMusicControler :: Archive( zCArchiver& arc ) 
{
	zCEventMessage::Archive( arc );
	arc.WriteString( "SGT", sgt );
}



/*--------------------------------------------------------------------------

    void zCEventMusicControler :: Unarchive( zCArchiver& arc )

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCEventMusicControler :: Unarchive( zCArchiver& arc ) 
{
	zCEventMessage::Unarchive( arc );
	arc.ReadString( "SGT", sgt );
}



/*--------------------------------------------------------------------------

    zCMusicControler :: zCMusicControler()

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
zCMusicControler :: zCMusicControler() 
{
}



/*--------------------------------------------------------------------------

    void zCMusicControler :: OnMessage( zCEventMessage *eventMessage, zCVob* sourceVob )

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCMusicControler :: OnMessage( zCEventMessage *eventMessage, zCVob* sourceVob ) 
{
	zCEventMusicControler *msg = dynamic_cast<zCEventMusicControler*>(eventMessage);
	if( !msg ) 
		return;
	switch( msg->GetSubType() ) 
	{
		case	zCEventMusicControler::zEVENT_START_SPECIAL_SGT:	
				zCZoneMusic::SetAutochange( FALSE );
				zmusic->PlayThemeByScript( msg->sgt );
				break;
		case	zCEventMusicControler::zEVENT_STOP_SPECIAL_SGT:	
				zCZoneMusic::SetAutochange( TRUE );
				break;
	}
}



/*--------------------------------------------------------------------------

    void zCMusicControler :: ThisVobRemovedFromWorld( zCWorld *homeWorld )

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCMusicControler :: ThisVobRemovedFromWorld( zCWorld *homeWorld )
{
	if( !zCZoneMusic::SetAutochange( TRUE ) )
	{
		zmusic->Stop();
		zerr.Warning( "X: zCMusicControler stops music playback !" );
	}
}
