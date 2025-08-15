/******************************************************************************** 
 
     $Workfile:: zWaynet.h            $                $Date:: 15.03.01 2:17    $
     $Revision:: 13                   $             $Modtime:: 14.03.01 20:36   $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zWaynet.h $
 * 
 * 13    15.03.01 2:17 Hildebrandt
 * 
 * 12    18.12.00 20:22 Wohlers
 * 
 * 11    4.12.00 18:23 Moos
 * 
 * 10    16.11.00 19:23 Wohlers
 * 
 * 9     18.10.00 17:02 Wohlers
 * 
 * 8     14.06.00 18:14 Wohlers
 * Gothic 0.85a
 * 
 * 7     9.06.00 18:39 Wohlers
 * 
 * 6     5.06.00 22:37 Wohlers
 * uSrc 05.06.00
 * 
 * 5     22.05.00 18:46 Wohlers
 * Gothic 0.82
 * 
 * 5     10.05.00 23:28 Wohlers
 * Gothic 0.81a
 * 
 * 4     8.05.00 23:10 Edenfeld
 * 
 * 4     8.05.00 15:02 Wohlers
 * Waynet CheckConsistency
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 11    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 9     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 8     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 7     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 6     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     7.12.99 22:09 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 3     6.12.99 16:06 Wohlers
 * Waynet Erweiterungen
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZWAYNET_H__
#define __ZWAYNET_H__

#ifndef __Z3D_H__
#include "z3d.h"
#endif

#ifndef __ZVOB_H__
#include "zVob.h"
#endif

#ifndef __ZLIST_H__
#include "zList.h"
#endif

// *****************************************
// lustige Wegnetze
// *****************************************

// Way - Eigenschaften
enum { zWAY_JUMP=1, zWAY_CLIMB=2, zWAY_SWIM=4, zWAY_DIVE=8, zWAY_FREE=16 };

class zCWay;
class zCRoute;

class zCVobWaypoint : public zCVob {
	zCLASS_DECLARATION( zCVobWaypoint )
	
public:
	zCVobWaypoint();
protected:
	virtual ~zCVobWaypoint();
};

class zCWaypoint : public zCObject {

	zCLASS_DECLARATION(zCWaypoint);

	friend class zCWay;
	friend class zCWayNet;
public:

	zCWaypoint							( );

	void			Init				( zVEC3 &pos );
	void			Init				( zCVobWaypoint *vob );
	void			Init				( float x, float y, float z );

	zCVobWaypoint*	GetVob				( );

	zVEC3&			GetAtVectorWorld	( ) { return dir; };
	zVEC3&			GetPositionWorld	( );
	void			UpdatePositionWorld	( );

	void			SetName				( zSTRING &s );
	const zSTRING&	GetName				( );

	zCWay*			HasWay				( zCWaypoint *way );
	int				GetNumberOfWays		( );
	void			SetWaypointVob		( zCVobWaypoint* vob );
	zCList <zCWay>& GetWayList			( );

	void			CorrectHeight		( zCWorld *wld );
	void			Draw				( );

	void			CalcProperties		( zCWorld *wld );
	virtual zBOOL	CanBeUsed			( const zCVob* vob ) {	return TRUE; };
	zBOOL			IsUnderwater		( ) { return underWater; };

protected :

	virtual			~zCWaypoint			( );

	virtual void	Archive				( zCArchiver &arc );
	virtual void	Unarchive			( zCArchiver &arc );

	void			InsertWay			( zCWay *way );
	void			RemoveWay			( zCWay *way );
	void			Save				( zFILE *f );	

	void			Free				( );

	// PathFinding used by zCWaynet
	int				routeCtr;
	int				curCost;
	int				estCost;
	int				score;
	int				curList;
	zCWay*			parent;

protected:
	// Properties
	int				waterDepth;
	zBOOL			underWater;

private :
	
	zVEC3			pos;				// Position dieses Waypoints
	zVEC3			dir;				// AtVector
	zSTRING			name;

	// dazugehöriger Vob in dér Welt
	zCVobWaypoint	*wpvob;
	
	// Liste der verknuepften Waypoints ( Ways )
	zCList <zCWay>	wayList;
};

class zCWay {
friend class zCWaypoint;
friend class zCWayNet;

public:

	zCWay								( zCWaypoint *w1, zCWaypoint *w2 );
	zCWay								( );
	virtual ~zCWay						( );

	virtual void	Init				( zCWaypoint *w1, zCWaypoint *w2 );

	inline zCWaypoint*	GetLeftWaypoint	( ) const { return left;	};
	inline zCWaypoint*	GetRightWaypoint( ) const { return right;	};
	zCWaypoint*		GetGoalWaypoint		( zCWaypoint *w1 );

	void			Draw				( zCCamera *camera );
	zVEC3			GetDistancePos		( zREAL xcm, zCWaypoint* wp1 );
	zREAL			GetLength			( );
	zREAL			GetJumpDistance		( );

	// **********************
	// Properties - virtuals
	// **********************

	virtual void	CalcProperties		( zCWorld *wld );
	virtual zREAL	GetChasm			( );
	virtual zBOOL	CanJump				( );
	virtual zBOOL	CanBeUsed			( const zCVob* vob );
	virtual zBOOL	IsObjectOnWay		( const zCVob* object ) { return FALSE; };

protected:
	
	void			Save				( zFILE *f );
	zVEC3			GetFloor			( zCWorld* wld,const zVEC3& pos1);
	
	void			Free				();
	
	// Pathfinding
	void			EstimateCost		();
	inline int		GetCost				() const { return cost; };

	// Pathfinding used by zCWaynet
	int				cost;
	int				usedCtr;

	// Properties
	zREAL			chasmDepth;
	zBOOL			chasm;
	zBOOL			jump;

private:

	zCWaypoint		*left,*right;


};

class zCWayNet : public zCObject {
	zCLASS_DECLARATION(zCWayNet);
public:

	zCWayNet							( );
	zCWayNet							( zCWorld *w3d );
	virtual ~zCWayNet					( );

	zCWaypoint*		InsertWaypoint		( float x, float y, float z );
	void			InsertWaypoint		( zCWaypoint *wp );
	void			InsertWaypoint		( zCWaypoint *wp1, zCWaypoint *wp2, zCWaypoint *wp3 );
	void			DeleteWaypoint		( zCWaypoint *wp );
	void			CreateWay			( zCWaypoint *wp1, zCWaypoint *wp2 );
	void			DeleteWay			( zCWaypoint *wp1, zCWaypoint *wp2 );

	inline zBOOL	HasWay				( zCWaypoint *w1, zCWaypoint *w2 ) const { return (w1->HasWay(w2)!=NULL);	};	// Gibt es bereits die Route w1 nach w2 ?
	inline zCWay*	GetWay				( zCWaypoint *w1, zCWaypoint *w2 ) const { return w1->HasWay(w2);			};  // Gibt es bereits die Route w1 nach w2 ?
	zCWaypoint*		HasWaypoint			( float x, float y, float z );
	zBOOL			HasWaypoint			( zCWaypoint *wp );
	zCWaypoint*		HasWaypoint			( zVEC3 &pos );
	void			CalcProperties		( zCWorld *wld );

	inline int		GetNumberOfWays		( ) const { return waylist.GetNumInList();	};
	inline int		GetNumberOfWaypoints( ) const { return wplist.GetNumInList();	};
	zCWaypoint* zCCFASTCALL GetNearestWaypoint	( const zVEC3 &vec );
	zCWaypoint*		GetSecNearestWaypoint( zVEC3 &vec );
	zCWaypoint* zCCFASTCALL GetWaypoint			( const zSTRING &s ) const;
	zCWaypoint*		SearchWaypoint		( zCVobWaypoint *w );
	zCWaypoint*		GetFirstWaypoint	( ) { return wplist.Get(0); };
	void			RemoveUnusedWPVobs	( );

	void			CorrectHeight		( );

	// Pathfinding ( von, nach )
	zCRoute*		FindRoute			( const zVEC3	&from, const zVEC3	 &to, const zCVob* usedBy = NULL );
	zCRoute*		FindRoute			( const zVEC3	&from, zCWaypoint	 *to, const zCVob* usedBy = NULL );
	zCRoute*		FindRoute			( const zVEC3	&from, const zSTRING &to, const zCVob* usedBy = NULL );
	zCRoute*		FindRoute			( zCWaypoint	*from, zCWaypoint	 *to, const zCVob* usedBy = NULL );
	zCRoute*		FindRoute			( const zSTRING	&from, const zSTRING &to, const zCVob* usedBy = NULL );

	// Specials
	void			GetWPList				( zCList <zVEC3> &wplist, zVEC3 &pos, zREAL mindist, zREAL maxdist );
	void			ClearVobDependencies	();					// Delete zCVobWaypoints -> affects not the functionality of the waynet !
	void			CreateVobDependencies	( zCWorld* wld );	// Create zCVobWaypoints from zCWaynet (zCWaypoint)
	void			UpdateVobDependencies	();
	zSTRING			CheckConsistency		( zBOOL isFault = FALSE );
	zSTRING			MergeWaypoints			( );
	void			AddWays					( zCWaypoint* wp1, zCWaypoint* wp2 );

	// Internals
	void			Save				( zFILE *f );
	void			Load				( zFILE *f );
	void			Draw				( zCCamera *round );

	// *************************************
	// Archive / Unarchive
	// *************************************

	virtual void	Archive				(zCArchiver &arc);
	virtual void	Unarchive			(zCArchiver &arc);

	void			ArchiveOldFormat	(zCArchiver &arc);
	void			UnarchiveOldFormat	(zCArchiver &arc);

private:

	zCWorld*						world;

	zCListSort	<zCWaypoint>		wplist;		// Alle Waypoints	im Netz
	zCList		<zCWay>				waylist;	// Alle Ways		im Netz

	// Route - Pathfinding
	void		InsertInOpen		(zCWaypoint* wp);
	zBOOL		IsInOpen			(zCWaypoint* wp);
	void		InsertInClosed		(zCWaypoint* wp);
	void		RemoveFromClosed	(zCWaypoint* wp);
	zBOOL		IsInClosed			(zCWaypoint* wp);
	zBOOL		IsInAnyList			(zCWaypoint* wp);
	int			EstimateCost		(zCWaypoint* from, zCWaypoint* to);
	zBOOL		AStar				(zCWaypoint* from, zCWaypoint* to, const zCVob* usedBy = NULL);
	zCRoute*	CreateRoute			(zCWaypoint* to);

	enum		{ WAY_LIST_NONE, WAY_LIST_OPEN, WAY_LIST_CLOSED };
	zCListSort	<zCWaypoint>		openList;
	int								routeCtr;	

	// static
	static int	SortOpenList		(zCWaypoint* w1, zCWaypoint* w2);
	static int	SortWpList			(zCWaypoint* w1, zCWaypoint* w2);
	
	void		CreateWPVobList		( zCList <zCVobWaypoint> &resultlist, zCTree <zCVob> *node );

};

class zCRoute {
friend class zCWayNet;
public:
	zCRoute								();
	virtual ~zCRoute					();	

	void			SetStart			(zCWaypoint* wp);
	
	zCWaypoint*		GetNextWP			();
	zCWaypoint*		GetTargetWP			();
	zCWay*			GetCurrentWay		();

	zSTRING			GetDesc				();
	zSTRING			GetRemainingDesc	();

	zBOOL			IsLastTarget		();
	int				GetNumberOfWaypoints();
	zBOOL			IsEmpty				();
	
	zBOOL			GetInterpolatedPosition	(zREAL kmperh, int passedMin, zVEC3& foundPos);

protected:
	zCList <zCWay>	wayList;

private:
	zCWaypoint*		startwp;
	zCWaypoint*		target;
	zCWay*			way;
	zCList <zCWay>* waynode;
};

// **************************************
// Vob - Helpers 
// **************************************

class zCVobSpot : public zCVob
{
	zCLASS_DECLARATION(zCVobSpot);
public:
	
					zCVobSpot	();	
	virtual			~zCVobSpot	();

	zBOOL			IsAvailable (zCVob* vob);
	void			MarkAsUsed	(zREAL timer, zCVob* vob);
	zBOOL			IsOnFP		(zCVob* vob) { return (inUseVob == vob); };

private:

	zREAL			timerEnd;
	zCVob*			inUseVob;

};

class zCVobStartpoint : public zCVob
{
	zCLASS_DECLARATION(zCVobStartpoint);
public :
	zCVobStartpoint() { SetVobType(zVOB_TYPE_STARTPOINT); };	
};
/*
class zCVobMarker : public zCVob
{
	zCLASS_DECLARATION(zCVobMarker);
public:
	zCVobMarker() { SetVobType(zVOB_TYPE_MARKER); };	
};
*/
#endif