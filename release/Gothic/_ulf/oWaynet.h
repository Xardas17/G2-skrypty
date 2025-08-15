
/******************************************************************************** 
 
     $Workfile:: oWaynet.h           $                $Date:: 22.05.00 18:44   $
     $Revision:: 4                    $             $Modtime:: 9.05.00 14:24    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oWaynet.h $
 * 
 * 4     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 3     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 2     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 1     6.12.99 15:14 Wohlers
 * 
 *********************************************************************************/

#ifndef __OWAYNET__
#define __OWAYNET__

#include "zWaynet.h"

class oCMobLadder;
class oCMobDoor;

class oCWaypoint : public zCWaypoint
{
public:
	oCWaypoint								();
	virtual ~oCWaypoint						();

	virtual		zBOOL	CanBeUsed			( const zCVob* vob );

private:

};

class oCWay : public zCWay
{
public:
	oCWay									();
	virtual ~oCWay							();

	virtual	void	Init					(zCWaypoint *w1, zCWaypoint *w2);
	virtual	zBOOL	CanBeUsed				(const zCVob* npc);
	virtual zBOOL	IsObjectOnWay			(const zCVob* object);

	oCMobLadder*	GetLadder				();
	oCMobDoor*		GetDoor					();

private:
	
	oCMobLadder*	ladder;
	oCMobDoor*		door;

};

#endif