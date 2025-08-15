/******************************************************************************** 
 
     $Workfile:: znetvobcontrol.h    $                 $Date:: 4.12.00 18:22    $
     $Revision:: 9                   $              $Modtime:: 4.12.00 18:06    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   vob-controller
  
 * $Log: /current_work/ZenGin/_Bert/znetvobcontrol.h $
 * 
 * 9     4.12.00 18:22 Moos
 * 
 * 8     8.09.00 17:37 Hildebrandt
 * fixed minor compiler warnings
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
 * 5     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 1     18.01.00 20:38 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 9 $ ($Modtime: 4.12.00 18:06 $)


#ifndef __ZNETVOBCONTROL_H__
#define __ZNETVOBCONTROL_H__

#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

#ifndef __ZNETTYPES_H__
#include "znettypes.h"
#endif

#ifndef __ZOBJECT_H__
#include "zobject.h"
#endif


class zCVob;
class zCWorld;
class zCPlayerInfo;
class zCNetMessage;
class zCPlayerGroup;
class zCClassDef;

const int zNET_VOBCTRL_TOLERANCE = 200*200; // in cm 

//
// An instance of zCNetVobControl stores the control-state
// of a vob including the controling player.
// The class implements basic algorithms for handling controled vob
//

class zCNetVobControl : public zCObject
{	
	zCLASS_DECLARATION	(zCNetVobControl)

public:	
			
	// construction and destruction

			zCNetVobControl();	

	virtual void		Init(zCVob* vob);

	// get-methods
	
	zCVob*				GetHostVob()				{ return hostVob;		};
	zCPlayerInfo*		GetCtrlPlayer()				{ return ctrlPlayer;	};	
	virtual zBOOL		IsLocalChained()			{ return isLocalChained;};
	virtual zBOOL		IsLocalControlled();
	virtual zBOOL		IsPlayerVob();

	// set-methods

	virtual void		SetLocalChained(zBOOL chain = TRUE)		{ isLocalChained = chain;		};		
	virtual void		SetCtrlPlayer(zCPlayerInfo* pinfo);

	virtual void		CopyCtrlState(zCVob* vob);

	// controling ...

	virtual	zBOOL		Process();
	virtual	zBOOL		HandOverToPlayer(zCPlayerInfo* newCtrlPlayer);

	// network

	virtual	zCNetMessage*	CreateNetMessage(const zTNetMessageSubID& messageID);
	static	zBOOL			HandleNetMessage(zCNetMessage* msg, const zTNetMessageSubID& messageID, zCWorld* world);
	
protected:		

	virtual	~zCNetVobControl();

	// archiving

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);
	
private:			
			
	// data-members

	zCVob*				hostVob;		// the controlled vob
	zCPlayerInfo*		ctrlPlayer;
	zBOOL				isLocalChained;
};




#endif
