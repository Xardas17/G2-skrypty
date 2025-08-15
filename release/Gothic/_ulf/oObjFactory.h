/******************************************************************************** 
 
     $Workfile:: oobjfactory.h        $                $Date:: 31.07.00 20:04   $
     $Revision:: 5                    $             $Modtime:: 27.07.00 16:48   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oobjfactory.h $
 * 
 * 5     31.07.00 20:04 Speckels
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
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
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
/// @author $Author: Speckels $
/// @version $Revision: 5 $ ($Modtime: 27.07.00 16:48 $)



#ifndef __OOBJFACTORY_H__
#define __OOBJFACTORY_H__

#include <zobject.h>
#include <zWaynet.h>

class zCWorld;
class zCPlayerInfo;
class zCGameInfo;
class zCEventManager;
class oCNpc;
class oCItem;

// ===============================================================================================================

class oCObjectFactory : public zCObjectFactory 
{
	zCLASS_DECLARATION	(oCObjectFactory)
public:
	virtual zCEventManager*		CreateEventManager	(zCVob* hostVob);	
	virtual zCCSManager*		CreateCSManager		();
	virtual zCGameInfo*			CreateGameInfo		();
	virtual zCPlayerInfo*		CreatePlayerInfo	();
	virtual zCWorld*			CreateWorld			();	

	virtual	oCNpc*				CreateNpc			(const int index);
	virtual	oCItem*				CreateItem			(const int index);

	virtual zCWaypoint*			CreateWaypoint		();
	virtual zCWay*				CreateWay			();
};

// ===============================================================================================================

#endif