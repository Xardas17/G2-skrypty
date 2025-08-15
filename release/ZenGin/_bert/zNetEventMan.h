/******************************************************************************** 
 
     $Workfile:: znetEventMan.h      $                 $Date:: 4.12.00 18:22    $
     $Revision:: 8                   $              $Modtime:: 4.12.00 18:12    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   network-eventmanager sending messages of network-relevant events
 
 * $Log: /current_work/ZenGin/_Bert/znetEventMan.h $
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
 * 5     30.03.00 14:23 Speckels
 * 
 * 8     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 7     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 6     4.12.99 20:49 Speckels
 * more implementation of the central networkmanager
 * 
 * 5     2.12.99 22:51 Speckels
 * Release-Candidate Stage Objektinteraktion
 * 
 * 4     16.11.99 11:42 Speckels
 * Item/MOB-Interaktion, Pre-Release Netzwerk
 * 
 * 3     21.10.99 23:29 Speckels
 * Work on error-handling and
 * item-interaction
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:12 $)

#ifndef __ZNETEVENTMAN_H__
#define __ZNETEVENTMAN_H__

#ifndef __ZEVENTMAN_H__
#include "zeventman.h"
#endif

#ifndef __ZNETTYPES_H__
#include "znettypes.h"
#endif

class zCNetVobControl;
class zCNetMessage;
class zCWorld;

class zCNetEventManager : public zCEventManager
{
	zCLASS_DECLARATION		(zCNetEventManager)	
public:
	
	zCNetEventManager();	
	zCNetEventManager(zCVob* hostVob);		

	virtual void OnMessage (zCEventMessage *eventMessage, zCVob* otherVob);

	// Static - call per frame
	static void				DoFrameActivity		();

	virtual	zCNetVobControl*GetNetVobControl	(zBOOL dontCreateIfNotPresent = FALSE);
	
	
	static	zBOOL			HandleNetMessage(zCNetMessage* msg, zTNetMessageSubID messageID, zCWorld* world = 0);
	
protected:

	virtual ~zCNetEventManager();

	void	Init();

	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

private:

	zCNetVobControl*		netVobCtrl;

};

#endif