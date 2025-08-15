 

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DynamicMusic - Implementation
* File          : oMusicZone.h 
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



#ifndef __oMusicZone_H__
#define __oMusicZone_H__

#include "zZone.h"
#include "zMusic_DM.h"

enum oHEROSTATUS { oHERO_STATUS_STD, oHERO_STATUS_THR, oHERO_STATUS_FGT };



class oCZoneMusic;
class oCZoneMusicDefault;
struct oCZoneMusicList
{
	oCZoneMusic				*entry;
	oCZoneMusicList			*next;
};

	
class oCZoneMusic : public zCZoneMusic 
{
	zCLASS_DECLARATION	( oCZoneMusic )
public:
	oCZoneMusic();

	virtual void			ProcessZoneList		( const zCArraySort<zCZone*> &zoneList, const zCArraySort<zCZone*>& zoneDeactivateList, zCWorld* homeWorld );
	virtual zCClassDef*		GetDefaultZoneClass	() const;
	virtual zSTRING			GetDebugDescString	();

	virtual void			OnTrigger			(zCVob* otherVob);
	virtual void			OnUntrigger			(zCVob* otherVob);

	void					SetEnabled			( const zBOOL e );
	zBOOL					IsEnabled			() const;
	void					SetPriority			( const int p );
	int						GetPriority			() const;
	void					SetEllipsoid		( const zBOOL e );
	zBOOL					IsEllipsoid			() const;
	void					SetReverb			( const float r );
	float					GetReverb			() const;
	void					SetVolume			( const float v );
	float					GetVolume			() const;
	void					SetLoop				( const zBOOL l );
	zBOOL					IsLoop				() const;
	void					SetDayEntranceDone	( const zBOOL d );
	zBOOL					IsDayEntranceDone	() const;
	void					SetNightEntranceDone( const zBOOL d );
	zBOOL					IsNightEntranceDone	() const;

	static	void			SetZonetime			( const int t );
	static	void			GetZonetime			( int *t );

protected:
	virtual void			Archive				( zCArchiver& arc );
	virtual void			Unarchive			( zCArchiver& arc );

	static	void			GetNewTheme			( zSTRING *newTheme );
	static	zBOOL			PlayThemeVariation	( zSTRING newTheme, int manipulate ); // 21-Jan-01 [PELZER]Parameter 'manipulate' hinzugefügt

	zREAL					GetCamPosWeightElps	();
	static	zBOOL			IsDaytime			();
	static	oHEROSTATUS		GetHerostatus		();
	static	oCZoneMusicList	*BuildTempZoneList	( oCZoneMusicDefault *zoneDefault, const zCArraySort<zCZone*> &zoneList );
	static	void			ReleaseTempZoneList	( oCZoneMusicList *zone );
	static	void			SwitchInAndOutZones	( const zCArraySort<zCZone*>& zoneList, const zCArraySort<zCZone*>& zoneDeactivateList );
	static	oCZoneMusic		*GetMusicZoneByName	( oCZoneMusic *vobMusic, zSTRING vobName );

	zBOOL					enabled;			//Enable/Disable
	zBOOL					local_enabled;		//Local copy of the enabled-flag
	int						priority;			//Priority of musiczone
	zBOOL					ellipsoid;			//Ellipsoid zone or Box zone
	float					reverbLevel;		//Reverb-Level of musiczone
	float					volumeLevel;		//Volume-Level of musiczone
	zBOOL					loop;				//Loop/Once

	zBOOL					dayEntranceDone;
	zBOOL					nightEntranceDone;

	static	long			s_lastzonechange;	//Timestamp of last zone change
	static	int				s_zonetime;			//Min. time 'till next zone change (in milliseconds)
	static	zBOOL			s_daytime;			//Act. time: Day or night
	static	oHEROSTATUS		s_herostatus;		//Act. state: Base, threat oder fighting
	static	oCZoneMusic		*s_musiczone;		//Act. zone
	static	oCZoneMusic		*s_oldmusiczone;	//Last act. zone
};


class oCZoneMusicDefault : public oCZoneMusic 
{
	zCLASS_DECLARATION	( oCZoneMusicDefault )
public:
	oCZoneMusicDefault();
};



#endif //#ifndef __oMusicZone_H__