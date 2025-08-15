/******************************************************************************** 
 
     $Workfile:: oobjfactory.cpp      $                $Date:: 2.08.00 14:25    $
     $Revision:: 7                    $             $Modtime:: 2.08.00 13:28    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oobjfactory.cpp $
 * 
 * 7     2.08.00 14:25 Wohlers
 * 
 * 6     31.07.00 20:04 Speckels
 * 
 * 5     21.07.00 15:34 Wohlers
 * 
 * 4     22.05.00 18:43 Wohlers
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
 * 3     6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 2     22.10.99 13:02 Wohlers
 * Neue Methoden CreateNpc und CreateItem hinzugefügt
 * 
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Wohlers $
/// @version $Revision: 7 $ ($Modtime: 2.08.00 13:28 $)

#include "zCore.h"

#include <oobjfactory.h>
#include "zeventman.h"
#include "oworld.h"
#include "oplayerinfo.h"
#include "ogameinfo.h"
#include "onpc.h"
#include "oitem.h"
#include "oWaynet.h"
#include "ocsmanager.h"

zCLASS_DEFINITION( oCObjectFactory	, zCObjectFactory, 0, 0	)

zCEventManager* oCObjectFactory::CreateEventManager	(zCVob* hostVob) 
{ 
	return zNEW( zCEventManager(hostVob) );	
}

zCCSManager* oCObjectFactory::CreateCSManager()
{	
	return zNEW(oCCSManager());
};



zCGameInfo*	oCObjectFactory::CreateGameInfo()
{
	return zNEW( oCGameInfo() );
};

zCPlayerInfo* oCObjectFactory::CreatePlayerInfo()
{
	return zNEW( oCPlayerInfo() );
};

zCWorld* oCObjectFactory::CreateWorld()
{	
	return zNEW(oCWorld);
};

oCNpc* oCObjectFactory::CreateNpc	(const int index)
{
	if (index == zPAR_INDEX_UNDEF) 
	{
		return zNEW( oCNpc() );
	}
	else
	{
		oCNpc* npc = zNEW( oCNpc() );
		npc->InitByScript (index);
		return npc;	
	}
};

oCItem*	oCObjectFactory::CreateItem	(const int index)
{
	if (index == zPAR_INDEX_UNDEF) 
	{
		return zNEW( oCItem() );
	}
	else
	{
		oCItem* item = zNEW( oCItem() );
		item->InitByScript(index);	
		return item;
	}
};

zCWaypoint* oCObjectFactory::CreateWaypoint()
{
	return zNEW( oCWaypoint() );
}

zCWay* oCObjectFactory::CreateWay()
{
	return zNEW( oCWay() );
}

// =================================================================================================================
