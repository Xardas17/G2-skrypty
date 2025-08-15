
/****************************************************************
*																*
* Phoenix Object-System	( Header File )                			*
* Projekt       : Phoenix										*
* Datei         : oMob.h										*
* Autor         : Ulfi			   								*
* Version       : 0.01											*
* last modified : 26.09.97										*
* erstellt      : 26.09.97										*
*																*
*****************************************************************
- bekannte Bugs:
*****************************************************************
- moegliche Optimierungen:
*****************************************************************
- noch fehlende Funktionalitaeten:
*****************************************************************
- Kommentare:
****************************************************************/

#ifndef __OMOB_H__
#define __OMOB_H__

//#include "Grade.h"

#include "zSTRING.h"
#include "zParser.h"
#include "zFile3d.h"
#include "z3D.h"

#include "oVob.h"
#include "oNpc.h"
#include "oItem.h"
#include "oText.h"

const int OBJ_STATUS_CLOSED		= 0;
const int OBJ_STATUS_OPEN		= 1;
const int OBJ_STATUS_LOCKED		= 2;

const int OBJ_FLAG_MOVEABLE		= 1;		// Bewegbar
const int OBJ_FLAG_TAKEABLE		= 2;		// Tragbar
const int OBJ_FLAG_HIDE			= 4;		// Versteck
const int OBJ_FLAG_CONTAINER	= 8;		// Behälter
const int OBJ_FLAG_TRAP			= 16;		// Falle
const int OBJ_FLAG_SWITCH		= 32;
const int OBJ_FLAG_SITDOWN		= 64;		// Stuhl
const int OBJ_FLAG_LIEDOWN		= 128;		// Bett

const int OBJ_FLAG_INVINCIBLE	= 512;

const int OBJ_DIR_NORTH			= 1;
const int OBJ_DIR_EAST			= 2;
const int OBJ_DIR_SOUTH			= 4;
const int OBJ_DIR_WEST			= 8;

class oCWorld;
class zCArchiver;

class oCMob : public oCVob  
{
	zCLASS_DECLARATION	(oCMob)
public:
	// PARSER ON
	int id;
	zSTRING name;
	int hp,hp_max;
	int flags;
	int damage;								// Schaden beim Werfen
	int status;

	int key_hole,key_level;
	int on_action;
	int on_spotted;
	int on_item;

	int sides;

	int owner;
	int owner_guild;

	zSTRING mesh;
	zSTRING destroyed_mesh;

	int	sound_material;

	// PARSER OFF

	int spotted;
	int action;

	int		c_manipulation;						// Counter für Manipulationen
	zREAL	last_manipulation;

	BOOL	destroyed;

//	zList <oCItem> contains;
//	oCItemContainer *cont;	

public :
	// Statics
	static zList <oCMob> MobList;
	static oCWorld* world_3d;
	static BOOL IA_ObjContainer (int key);

	// Constructors
	oCMob				( );
	oCMob				( int instance );
	oCMob				( zSTRING instance );
	~oCMob				( );

	void Init();

	void		InitByScript	( int nr );
	// Member-Functions
	zSTRING		GetName			( );
	BOOL		HasFlag			( int f );
	void		InsertItem		( oCItem *item );
	void		RemoveItem		( oCItem *item );
	oCItem *	RemoveItem		( int nr );
	zSTRING		GetStatus		( );
	zSTRING		DoAction		( );
	BOOL		IsOpen			( );
	BOOL		Unlock			( oCItem *key );
	void		OnAction		( );

	// Besitzer ?!
	zBOOL IsOwned				(int instance, int guild);
	zBOOL IsOwnedByNpc			(int instance);
	zBOOL IsOwnedByGuild		(int guild);

	// Manipulation
	int	 AddManipulation		();
	void SetManipulation		(int count) { c_manipulation = count; };

//	void		Move			( float xv, float yv, float zv );

	BOOL		Carry			( zCVob *vob );
	BOOL		Drop			( zCVob *vob );

	void		Hit				( int dam );
	zSTRING		GetStatusHP		( );

	void		OnSpotted		( );
	// 3D - Member - Functions
	void		PutIn3D			( float x, float y, float z, zCVob *parent = NULL );
	void		PutIn3D			( zVEC3& pos, zCVob *parent = NULL );
	BOOL		RemoveFrom3D	( );
	
	void		GetHitpoints	( int &hitp, int &maxhitp );

	void		Destroy			( );

	int			GetSoundMaterial( ) { return sound_material; };

	// *************************************
	// Archive / Unarchive
	// *************************************

	virtual void	Archive				(zCArchiver &arc);
	virtual void	Unarchive			(zCArchiver &arc);
		
	// *********************************
	//		Save / Load Functions
	// *********************************
	oCMob *next;
	int instanz;
	int GetInstance()		{ return instanz; };
	zSTRING GetInstanceName ();

	void	RenderMob		( zCView *v );
};

#endif
