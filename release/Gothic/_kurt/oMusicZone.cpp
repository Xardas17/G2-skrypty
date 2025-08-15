

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DynamicMusic - Implementation
* File          : oMusicZone.cpp
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.00
* last modified : 28.08.00
* erstellt      : 17.08.00										
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



#include "zEngine.h"
#include "oMusicZone.h"
#include "zArchiver.h"
#include "zWorld.h"
#include "oWorld.h"
#include "ogame.h"
#include "zsky.h"
#include <mmsystem.h>


long		oCZoneMusic::s_lastzonechange	= 0;
int			oCZoneMusic::s_zonetime			= 1;
zBOOL		oCZoneMusic::s_daytime			= TRUE;
oHEROSTATUS	oCZoneMusic::s_herostatus		= oHERO_STATUS_STD;
oCZoneMusic	*oCZoneMusic::s_musiczone		= NULL;
oCZoneMusic	*oCZoneMusic::s_oldmusiczone	= NULL;



// ============================================================================================================

zCLASS_DEFINITION				(oCZoneMusic				, zCZone			, 0, 0)
	zCLASS_DEFINITION			(oCZoneMusicDefault			, oCZoneMusic		, 0, 0)

// ============================================================================================================



/*--------------------------------------------------------------------------

    oCZoneMusic :: oCZoneMusic()

 

    28-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
oCZoneMusic :: oCZoneMusic()
{
	enabled				= TRUE;
	local_enabled		= TRUE;
	priority			= 1;
	ellipsoid			= FALSE;
	reverbLevel			= -3.219f;
	volumeLevel			= 1.0f;
	loop				= TRUE;
	dayEntranceDone		= FALSE;
	nightEntranceDone	= FALSE;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: ProcessZoneList( const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld )

 

    28-Aug-00       [PELZER]
	21-Jan-01		[PELZER]
					Beim Wechsel des Hero-Status wird nun im zSpy eine Meldung ausgegeben

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: ProcessZoneList( const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld )
{
	zBOOL daytimeChanged		= FALSE;
	zBOOL herostatusChanged		= FALSE;
	zBOOL musiczoneChanged		= FALSE;

	zBOOL daytime = IsDaytime(); //Stelle fest ob ein Tageszeiten-Wechsel vorliegt
	if( s_daytime!=daytime )
	{
		s_daytime		= daytime;
		daytimeChanged	= TRUE;
	}

	oHEROSTATUS herostatus = GetHerostatus(); //Stelle fest ob ein Herostatus-Wechsel vorliegt
	if( s_herostatus!=herostatus )
	{
		switch( herostatus )	// 21-Jan-01 [PELZER]
		{
		case	oHERO_STATUS_STD:
				zerr.Message( "X: [oCZoneMusic::ProcessZoneList]: Change hero status to oHERO_STATUS_STD." );
				break;
		case	oHERO_STATUS_THR:
				zerr.Message( "X: [oCZoneMusic::ProcessZoneList]: Change hero status to oHERO_STATUS_THR." );
				break;
		case	oHERO_STATUS_FGT:
				zerr.Message( "X: [oCZoneMusic::ProcessZoneList]: Change hero status to oHERO_STATUS_FGT." );
				break;
		}
		s_herostatus = herostatus;
		herostatusChanged = TRUE;
	}

	oCZoneMusicList *zone = NULL;
	SwitchInAndOutZones( zoneList, zoneDeactivateList ); //Führe die notwendigen Wechsel zwischen IN- und OUT-Zonen durch
	oCZoneMusicDefault *zoneDefault = (oCZoneMusicDefault*)homeWorld->SearchZoneDefaultByClass( oCZoneMusicDefault::GetStaticClassDef() );
	zone = BuildTempZoneList( zoneDefault, zoneList ); //Sortiere die Zonen nach Prios (beachte dabei das Ellipsoid-Flag)
	if( (zone!=NULL)&&(s_musiczone!=zone->entry) ) //Stelle fest ob eine Zonenwechsel vorliegt
	{
		s_oldmusiczone		= s_musiczone;
		s_musiczone			= zone->entry;
		musiczoneChanged	= TRUE;
	}
	if( (zone==NULL)||(zone->entry==NULL) )
	{
		s_canruleautochange = FALSE;
		if( !s_autochange ) //Falls das automatische Themenwechseln nicht erwünscht (evtl. bei Cutscene oder Scriptsteuerung) ...
		{
			//Bei einer späteren Wiederaktivierung des autom. Themenwechselns soll ein Musikzonen-Wechsel
			//simuliert werden, um einen Neueinstieg in das zugehörige Thema zu bewirken (daher hier: s_musiczone = NULL)
			s_oldmusiczone = NULL;
			s_musiczone = NULL;
			ReleaseTempZoneList( zone );
			return;
		}
		zmusic->Stop();
		zerr.Warning( "X: oCZoneMusic stops music playback !" );
		ReleaseTempZoneList( zone );
		return;
	}
	s_canruleautochange = TRUE;

	if( !s_autochange ) //Falls das automatische Themenwechseln nicht erwünscht (evtl. bei Cutscene oder Scriptsteuerung) ...
	{
		//Bei einer späteren Wiederaktivierung des autom. Themenwechselns soll ein Musikzonen-Wechsel
		//simuliert werden, um einen Neueinstieg in das zugehörige Thema zu bewirken (daher hier: s_musiczone = NULL)
		s_oldmusiczone = NULL;
		s_musiczone = NULL;
		ReleaseTempZoneList( zone );
		return;
	}

	zSTRING newTheme;			//INSTANCE  LLL_TTT_III    (C_MUSICTHEME_DEF)
								//LLL = Location-Kürzel, 3 Buchstaben oder weniger.
								//TTT = Time, 3 Buchstaben, 'DAY' oder 'NGT'.
								//III = Intensity, 3 Buchstaben, 'STD', 'THR', 'FGT' oder 'ENT'.
								//Beispiele: OC_DAY_STD oder PC_NGT_ENT                     
	GetNewTheme( &newTheme ); //Baue das neue Thema LLL_TTT_III aus dem aktuellen Status zusammen
	
	//Wähle das neue Thema aus bzw. bleibe gegebenenfalls beim bisherigen
	if( daytimeChanged||herostatusChanged ) //Bei Tageszeit- oder Herostatus-Wechsel
	{
		zerr.Message( "X: ProcessZoneList: Time or status changed - try to start new theme"+zSTRING( newTheme ) );

		// FIXME: hier wird schnee gehackt, falls im themennamen das wort "NCI/NCO (newcamp)" vorkommt
		// besser wäre eine seperate wetter zone, aber der aufwand wäre nicht gerechtfertigt
		if (newTheme.Search("NCI_")!=-1 || newTheme.Search("NCO_")!=-1)
		{
			zCSkyControler::GetActiveSkyControler()->SetWeatherType(zTWEATHER_SNOW);
		}
		else 
		{
			zCSkyControler::GetActiveSkyControler()->SetWeatherType(zTWEATHER_RAIN);
		}

		oCZoneMusicList	*nextzone = zone;
		zSTRING zoneName;
		while( nextzone ) //Wiederhole mit abnehmender Zonenprio bis Thema vorhanden
		{
			if( daytimeChanged )
			{
				if( PlayThemeVariation( newTheme, 2 ) )
				{										//Ist das Wunschthema vorhanden, dann wird nichtmehr weiter gesucht		
					ReleaseTempZoneList	( zone );
					return;
				}
			}
			if( herostatusChanged )
			{
				if( PlayThemeVariation( newTheme, 0 ) )
				{										//Ist das Wunschthema vorhanden, dann wird nichtmehr weiter gesucht		
					ReleaseTempZoneList	( zone );
					return;
				}
			}
			if( daytimeChanged&&!herostatusChanged )//Bei reinem Tageszeitenwechsel keine weitere Suche erforderlich 
			{
				ReleaseTempZoneList	( zone );
				return;
			}
			nextzone = nextzone->next;				//Ansonsten die nächst Zone aus der Prio-Liste untersuchen
			newTheme.Delete( "_", zSTR_BEFORE );
			zoneName = zone->entry->GetVobName();
			zoneName.Delete( "_", zSTR_BEFORE );
			zoneName.Delete( "_", zSTR_ONLY );
			newTheme.Insert( 0, zoneName );
		}
		ReleaseTempZoneList( zone );
		return;										//Waren alle Bemühungen vergeblich, so verändere nichts
	}
	if( musiczoneChanged )
	{
		zerr.Message( "X: ProcessZoneList: musiczone changed - try to start new theme"+zSTRING( newTheme ) );

		// FIXME: hier wird schnee gehackt, falls im themennamen das wort "NCI/NCO (newcamp)" vorkommt
		// besser wäre eine seperate wetter zone, aber der aufwand wäre nicht gerechtfertigt
		if (newTheme.Search("NCI_")!=-1 || newTheme.Search("NCO_")!=-1)
		{
			zCSkyControler::GetActiveSkyControler()->SetWeatherType(zTWEATHER_SNOW);
		}
		else 
		{
			zCSkyControler::GetActiveSkyControler()->SetWeatherType(zTWEATHER_RAIN);
		}

		if( PlayThemeVariation( newTheme, 1 ) )
		{											//Ist das Wunschthema vorhanden, dann wird nichtmehr weiter gesucht 
			ReleaseTempZoneList	( zone );
			return;
		}
		if( !s_daytime )
		{											//Versuche es mit dem Tag-Thema bei fehlendem Nacht-Thema
			newTheme.Overwrite( newTheme.SearchRev( "_NGT", 1 ), "_DAY" );
			if( PlayThemeVariation( newTheme, 1 ) )
			{										//Versuche das Bedrohungsthema  zu starten
				ReleaseTempZoneList	( zone );
				return;
			}
		}
		if( s_herostatus==oHERO_STATUS_FGT )
		{											//Befindet sich der Hero im Kampf ...
			zSTRING theme;
			if (zmusic->GetActiveTheme()) theme = zmusic->GetActiveTheme()->GetName();

			if( theme.SearchRev( "_FGT", 1 )>0 )	//... und das momentan wiedergegebene Thema ist ein Kampfthema,
			{										//so verändere nichts ...
				ReleaseTempZoneList( zone );
				return;
			}
			newTheme.Overwrite( newTheme.SearchRev( "_FGT", 1 ), "_THR" ); 
			if( PlayThemeVariation( newTheme, 1 ) )
			{										//Versuche das Bedrohungsthema zu starten
				ReleaseTempZoneList	( zone );
				return;
			}
		}
		newTheme.Overwrite( newTheme.SearchRev( "_", 1 ), "_STD" ); 
		PlayThemeVariation( newTheme, 1 );		//Waren alle Bemühungen vergeblich, so verwende das Grundthema
	}
	ReleaseTempZoneList( zone );
	return;
}



/*--------------------------------------------------------------------------

    zCClassDef*	oCZoneMusic :: GetDefaultZoneClass() const

 

    29-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zCClassDef*	oCZoneMusic :: GetDefaultZoneClass() const 
{ 
	return oCZoneMusicDefault::GetStaticClassDef();	
}



/*--------------------------------------------------------------------------

    zSTRING oCZoneMusic :: GetDebugDescString()

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zSTRING oCZoneMusic :: GetDebugDescString()
{
	return zCZone::GetDebugDescString();
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: OnTrigger (zCVob* otherVob) 

 

    26-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: OnTrigger (zCVob* otherVob) 
{
	SetEnabled( TRUE );
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: OnUntrigger (zCVob* otherVob)

 

    26-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: OnUntrigger (zCVob* otherVob) 
{
	SetEnabled( FALSE );
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetEnabled( const zBOOL e )

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetEnabled( const zBOOL e )
{
	local_enabled = e;
}



/*--------------------------------------------------------------------------

    zBOOL oCZoneMusic :: IsEnabled() const

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL oCZoneMusic :: IsEnabled() const
{
	return local_enabled;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetPriority( const int p )

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetPriority( const int p )
{
	priority = p;
}



/*--------------------------------------------------------------------------

    int oCZoneMusic :: GetPriority() const

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
int oCZoneMusic :: GetPriority() const
{
	return priority;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetEllipsoid( const zBOOL e )

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetEllipsoid( const zBOOL e )
{
	ellipsoid = e;
}



/*--------------------------------------------------------------------------

    zBOOL oCZoneMusic :: IsEllipsoid() const

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL oCZoneMusic :: IsEllipsoid() const
{
	return ellipsoid;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetReverb( const float r )

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetReverb( const float r )
{
	reverbLevel = r;
}



/*--------------------------------------------------------------------------

    float oCZoneMusic :: GetReverb() const

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
float oCZoneMusic :: GetReverb() const
{
	return reverbLevel;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetVolume( const float v )

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetVolume( const float v )
{
	volumeLevel = v;
}



/*--------------------------------------------------------------------------

    float oCZoneMusic :: GetVolume() const

 

    17-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
float oCZoneMusic :: GetVolume() const
{
	return volumeLevel;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetLoop( const zBOOL l )

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetLoop( const zBOOL l )
{
	loop = l;
}



/*--------------------------------------------------------------------------

    zBOOL oCZoneMusic :: IsLoop() const

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL oCZoneMusic :: IsLoop() const
{
	return loop;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetDayEntranceDone( const zBOOL d )

 

    27-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetDayEntranceDone( const zBOOL d )
{
	dayEntranceDone = d;
}



/*--------------------------------------------------------------------------

    zBOOL oCZoneMusic :: IsDayEntranceDone() const

 

    27-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL oCZoneMusic :: IsDayEntranceDone() const
{
	return dayEntranceDone;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: SetNightEntranceDone( const zBOOL d )

 

    27-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetNightEntranceDone( const zBOOL d )
{
	nightEntranceDone = d;
}



/*--------------------------------------------------------------------------

    zBOOL oCZoneMusic :: IsNightEntranceDone() const

 

    27-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL oCZoneMusic :: IsNightEntranceDone() const
{
	return nightEntranceDone;
}



/*--------------------------------------------------------------------------

    (static) void oCZoneMusic :: SetZonetime( const int t )

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SetZonetime( const int t )
{
	s_zonetime = t;
}



/*--------------------------------------------------------------------------

    (static) void oCZoneMusic :: GetZonetime( int *t )

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: GetZonetime( int *t )
{
	*t = s_zonetime;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: Archive( zCArchiver& arc )

 

    21-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: Archive( zCArchiver& arc )
{
	zCZone::Archive( arc );
	arc.WriteGroupBegin	( "DynaMusic" );
	arc.WriteBool		( "enabled",		enabled );
	arc.WriteInt		( "priority",		priority );
	arc.WriteBool		( "ellipsoid",		ellipsoid );
	arc.WriteFloat		( "reverbLevel",	reverbLevel );
	arc.WriteFloat		( "volumeLevel",	volumeLevel );
	arc.WriteBool		( "loop",			loop );
	arc.WriteGroupEnd	( "DynaMusic" );
	if( arc.InSaveGame() ) 
	{
		arc.WriteBool	( "local_enabled",		local_enabled );
		arc.WriteBool	( "dayEntranceDone",	dayEntranceDone );
		arc.WriteBool	( "nightEntranceDone",	nightEntranceDone );
	}
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: Unarchive( zCArchiver& arc )

 

    21-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: Unarchive( zCArchiver& arc )
{
	zCZone::Unarchive( arc );
	arc.ReadBool		( "enabled",		enabled );
	arc.ReadInt			( "priority",		priority );
	arc.ReadBool		( "ellipsoid",		ellipsoid );
	arc.ReadFloat		( "reverbLevel",	reverbLevel );
	arc.ReadFloat		( "volumeLevel",	volumeLevel );
	arc.ReadBool		( "loop",			loop );
	if( arc.InSaveGame() ) 
	{
		arc.ReadBool	( "local_enabled",		local_enabled );
		arc.ReadBool	( "dayEntranceDone",	dayEntranceDone );
		arc.ReadBool	( "nightEntranceDone",	nightEntranceDone );
	}
	else
		local_enabled = enabled;
}



/*--------------------------------------------------------------------------

    zREAL oCZoneMusic :: GetCamPosWeightElps()

 

    21-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zREAL oCZoneMusic :: GetCamPosWeightElps() 
{
	assert(	zCCamera::activeCam	);				//Ermittle die Lage im Ellipsoid
	assert(	zCCamera::activeCam->GetVob()	);
	const zTBBox3D&	box		= GetBBox3DWorld();
	const zPOINT3&	camPos	= zCCamera::activeCam->GetVob()->GetPositionWorld();
	zVEC3			rel		= camPos - box.GetCenter();
	zVEC3			scale	= (box.maxs-box.mins) * zREAL(0.5F);
	for( int i = 0; i<3; i++ ) 
	{
		if( scale[i]<=0 ) 
			return 0;						// sollte eigentlich nicht passieren..
		scale[i]		= zREAL(1.0) / scale[i];
	}
	zREAL dist			= Alg_Prod( rel, scale ).LengthApprox();
	return dist;								//dist>1.0f heisst ausserhalb des Ellipsoids
}



/*--------------------------------------------------------------------------

    (static) oCZoneMusicList *oCZoneMusic :: BuildTempZoneList( oCZoneMusicDefault *zoneDefault, const zCArraySort<zCZone*> &zoneList )

 

    28-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
oCZoneMusicList *oCZoneMusic :: BuildTempZoneList( oCZoneMusicDefault *zoneDefault, const zCArraySort<zCZone*> &zoneList )
{
	oCZoneMusicList *zone			= NULL;
	oCZoneMusicList	*newzone		= NULL;
	oCZoneMusicList	*prevzone		= NULL;
	oCZoneMusicList	*nextzone		= NULL;
	for( int i = 0; i<zoneList.GetNum(); i++ )	//Baue eine nach Priorities sortierte Zonenliste auf 
	{
		oCZoneMusic *vobMusic = ( oCZoneMusic* )zoneList[i];
		if( vobMusic==NULL )
			continue;
		if( !vobMusic->IsEnabled() )			//Beachte nur Zonen die enabled sind
			continue;
		if( vobMusic->IsEllipsoid()&&vobMusic->GetCamPosWeightElps()>1.0f )
			continue;							//Wird das Ellipsoid gewünscht, so muss nochmals nachgetestet werden
		if( zone==NULL )
		{
			zone = zNEW( oCZoneMusicList );
			zone->entry = vobMusic;				//Erste eingefügte Zone
			zone->next = NULL;
		}
		else
		{
			nextzone = zone;
			while( nextzone						//Suche den korrekten Platz in der einfach verketteten Liste
				&&((nextzone->entry->GetPriority()>vobMusic->GetPriority())
				||((nextzone->entry->GetPriority()==vobMusic->GetPriority())&&(nextzone->entry->GetCamPosWeightElps()<vobMusic->GetCamPosWeightElps()))) )
			{
				prevzone = nextzone;
				nextzone = prevzone->next;
			}
			newzone			= zNEW( oCZoneMusicList );
			newzone->entry	= vobMusic;
			newzone->next	= nextzone;
			if( nextzone==zone )
				zone = newzone;
			else
				prevzone->next = newzone;
		}
	}
	if( zoneDefault )
	{
		if( !zone ) //Falls keine Zonenliste vorhanden, so greife auf die Default-Zone zurück
		{
			zone			= zNEW( oCZoneMusicList );
			zone->entry		= zoneDefault;
			zone->next		= NULL;
		}
		else
		{
			nextzone = zone;
			while( nextzone )
			{
				prevzone = nextzone;
				nextzone = prevzone->next;
			}
			newzone			= zNEW( oCZoneMusicList );
			newzone->entry	= zoneDefault;
			newzone->next	= NULL;
			prevzone->next = newzone;
		}
	}
	return zone;
}



/*--------------------------------------------------------------------------

    (static) void oCZoneMusic :: ReleaseTempZoneList( oCZoneMusicList *zone )

 

    21-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: ReleaseTempZoneList( oCZoneMusicList *zone )
{
	oCZoneMusicList	*nextzone = NULL;		//Baue die temporäre, nach Priorities sortierte Zonenliste wieder ab
	while( zone )
	{
		nextzone = zone->next;
		delete zone;
		zone = nextzone;
	}
}



/*--------------------------------------------------------------------------

    (static) void oCZoneMusic :: SwitchInAndOutZones( const zCArraySort<zCZone*> &zoneList, const zCArraySort<zCZone*> &zoneDeactivateList )

 

    26-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: SwitchInAndOutZones( const zCArraySort<zCZone*> &zoneList, const zCArraySort<zCZone*> &zoneDeactivateList )
{
	oCZoneMusic *vobMusic	= NULL;
	zSTRING		vobName		= "";
	int			position	= 0;

	//Alle betretenen enabled IN-Zonen müssen disabled und die zugehörigen OUT-Zonen enabled werden
	for( int i = 0; i<zoneList.GetNum(); i++ )
	{
		vobMusic	= ( oCZoneMusic* )zoneList[i];
		if( vobMusic==NULL )
			continue;
		vobName		= vobMusic->GetVobName();
		if( vobMusic->IsEllipsoid()&&vobMusic->GetCamPosWeightElps()>1.0f )
		{			//Sonderfall ellipsoide OUT-Zone wird verlassen (wegen der Form jedoch in der zoneList)
			position	= vobName.SearchRev( "_O_", 1 );
			if( (position>0)&&vobMusic->IsEnabled() )
			{
				vobMusic->SetEnabled( FALSE );
				vobName.Overwrite( position, "_I_" );
				vobMusic = vobMusic->GetMusicZoneByName( vobMusic, vobName );
				if( vobMusic )
					vobMusic->SetEnabled( TRUE );
			}
			continue;
		}
		position	= vobName.SearchRev( "_I_", 1 );
		if( (position>0)&&vobMusic->IsEnabled() )
		{
			vobMusic->SetEnabled( FALSE );
			vobName.Overwrite( position, "_O_" );
			vobMusic = vobMusic->GetMusicZoneByName( vobMusic, vobName );
			if( vobMusic )
				vobMusic->SetEnabled( TRUE );
		}
	}

	//Alle verlassenen enabled OUT-Zonen müssen disabled und die zugehörigen IN-Zonen enabled werden
	for( i = 0; i<zoneDeactivateList.GetNum(); i++ )
	{
		vobMusic	= ( oCZoneMusic* )zoneDeactivateList[i];
		if( vobMusic==NULL )
			continue;
		vobName		= vobMusic->GetVobName();
		position	= vobName.SearchRev( "_O_", 1 );
		if( (position>0)&&vobMusic->IsEnabled() )
		{
			vobMusic->SetEnabled( FALSE );
			vobName.Overwrite( position, "_I_" );
			vobMusic = vobMusic->GetMusicZoneByName( vobMusic, vobName );
			if( vobMusic )
				vobMusic->SetEnabled( TRUE );
		}
	}
}



/*--------------------------------------------------------------------------

    (static) oCZoneMusic *oCZoneMusic :: GetMusicZoneByName( oCZoneMusic *vobMusic, zSTRING vobName )

 

    23-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
oCZoneMusic *oCZoneMusic :: GetMusicZoneByName( oCZoneMusic *vobMusic, zSTRING vobName )
{
	return ( oCZoneMusic* ) vobMusic->GetHomeWorld()->SearchVobByName( vobName );
}



/*--------------------------------------------------------------------------

    (static) void oCZoneMusic :: GetNewTheme( zSTRING *newTheme )

 

    21-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void oCZoneMusic :: GetNewTheme( zSTRING *newTheme )
{
	if( s_musiczone==NULL )
	{
		*newTheme = "NO_MUSIC_ZONE_ACTIVE";
		return;
	}
	*newTheme = s_musiczone->GetVobName();
	newTheme->Delete( "_", zSTR_BEFORE );
	newTheme->Delete( "_", zSTR_ONLY );		
	newTheme->Delete( "_", zSTR_BEFORE );	//Zweites Delete falls IN- oder OUT-Zone
	newTheme->Delete( "_", zSTR_ONLY );		//Beginne den Themennamen mit dem Zonen-Kürzel
	if( s_daytime )							//Füge das Tageszeit-Kürzel hinzu
		*newTheme += "_DAY";
	else
		*newTheme += "_NGT";
	switch( s_herostatus )					//Füge das Herostatus-Kürzel hinzu
	{
	case	oHERO_STATUS_THR:
			*newTheme += "_THR";			//Bei Bedrohung ...
			break;
	case	oHERO_STATUS_FGT:
			*newTheme += "_FGT";			//Im Kampf ...
			break;
	default:
			if( s_daytime )
			{
				if( !s_musiczone->IsDayEntranceDone() )		//Beim erstmaligen Zonenbetreten im Grundzustand am Tage versuche das
				{							//Day-Entrance-Thema zu finden
					s_musiczone->SetDayEntranceDone( TRUE );
					if( zmusic->IsAvailable( *newTheme+"_ENT" ) )
					{
						*newTheme += "_ENT";
							return;
					}
				}
			}
			else
			{
				if( !s_musiczone->IsNightEntranceDone() )	//Beim erstmaligen Zonenbetreten im Grundzustand in der Nacht versuche das
				{							//Night-Entrance-Thema zu finden
					s_musiczone->SetNightEntranceDone( TRUE );
					if( zmusic->IsAvailable( *newTheme+"_ENT" ) )
					{
						*newTheme += "_ENT";
							return;
					}
				}
			}
			*newTheme += "_STD";			//Im Grundzustand ...
	}
	return;
}



/*--------------------------------------------------------------------------

    void oCZoneMusic :: PlayThemeVariation( const zSTRING newTheme, int manipulate )

 

    28-Aug-00       [PELZER]
	21-Jan-01		[PELZER]
					Parameter 'manipulate' hinzugefügt

--------------------------------------------------------------------------*/ 
zBOOL oCZoneMusic :: PlayThemeVariation( zSTRING newTheme, int manipulate ) 
{	
	zBOOL done = TRUE;
	if( zmusic->IsAvailable( newTheme ) )
	{
		zmusic->PlayThemeByScript( newTheme, manipulate, &done );		//Starte das Thema
		if( done==FALSE )
		{
			s_musiczone = s_oldmusiczone;
			zerr.Warning( "X: PlayThemeVariation: Can't start new theme !!!!!" );
		}
		zerr.Message( "X: PlayThemeVariation: "+zSTRING( newTheme ) );
		return TRUE;
	}
	if( zmusic->IsAvailable( newTheme+"_A0" ) )
	{												//Starte eine zufällige Variation des Themas
		int i = 1;
		while( zmusic->IsAvailable( newTheme+"_A"+zSTRING( i ) ) )
			i++;
		i = rand()%i;	
		zmusic->PlayThemeByScript( newTheme+"_A"+zSTRING( i ), manipulate, &done ); 
		if( done==FALSE )
		{
			s_musiczone = NULL;
			zerr.Warning( "X: PlayThemeVariation: Can't start new theme !!!!!" );
		}
		zerr.Message( "X: PlayThemeVariation: "+zSTRING( newTheme ) );
		return TRUE;
	}
	return FALSE;
}



/*--------------------------------------------------------------------------

    (static) zBOOL oCZoneMusic :: IsDaytime()

 

    28-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL oCZoneMusic :: IsDaytime()
{
	return ogame->GetWorldTimer()->IsDay();
}



/*--------------------------------------------------------------------------

    (static) oHEROSTATUS oCZoneMusic :: GetHerostatus()

 

    21-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
oHEROSTATUS oCZoneMusic :: GetHerostatus()
{
	return ogame->GetHeroStatus();
}



/*--------------------------------------------------------------------------

    oHEROSTATUS oCZoneMusicDefault :: oCZoneMusicDefault()

 

    26-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
oCZoneMusicDefault :: oCZoneMusicDefault()
{
	priority = 0;
}
