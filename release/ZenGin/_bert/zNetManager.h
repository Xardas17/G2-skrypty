/******************************************************************************** 
 
     $Workfile:: znetmanager.h        $                $Date:: 4.12.00 18:22    $
     $Revision:: 8                    $             $Modtime:: 4.12.00 18:11    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/znetmanager.h $
 * 
 * 8     4.12.00 18:22 Moos
 * 
 * 7     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 5     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 4     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 3     5.05.00 13:45 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 5     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 4     4.12.99 20:49 Speckels
 * more implementation of the central networkmanager
 * 
 * 3     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 2     22.10.99 12:52 Speckels
 * Neue Klasse Netzwerk-Manager
 *
 * 1     19.10.99 17:55 Speckels
 * 
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:11 $)

#ifndef __ZNETMANAGER_H__
#define __ZNETMANAGER_H__

#ifndef __ZNETTYPES_H__
#include "znettypes.h"
#endif

#ifndef __ZNETMESSAGE_H__
#include "znetmessage.h"
#endif

#ifndef __ZTOOLS_H__
#include "ztools.h"
#endif

#ifndef __ZOBJECT_H__
#include "zobject.h"
#endif

class zCNetMessage;
class zCApplication;
class zCWorld;

class zCNetManager : public zCObject
{
	zCLASS_DECLARATION(zCNetManager)
public:

	zCNetManager();
	virtual ~zCNetManager();
	
	virtual void Process();	
	
	virtual zCNetMessage*	CreateNetMessage	(const zTNetMessageSubID&, zCObject*);

	zBOOL			Temp_HandleNetMessage	(zCNetMessage*&, zCWorld*);
	virtual zBOOL	HandleNetMessage	(zCNetMessage*, const zTNetMessageSubID&, zCClassDef*, zCWorld* world = 0);

protected:

	virtual	void ProcessMessages();
	
	void	SendPing();
	void	SendPingReply(zCPlayerInfo* target);
	void	SendWorldTime();

private:

	zCTimer	timer;
	zDWORD	timer_count_ping;	
	zDWORD	timer_count_worldtime;
};

extern zCNetManager* znetman;

#endif