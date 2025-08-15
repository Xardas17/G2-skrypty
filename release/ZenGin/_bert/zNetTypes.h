/******************************************************************************** 
 
     $Workfile:: znettypes.h         $                 $Date:: 4.12.00 18:22    $
     $Revision:: 8                   $              $Modtime:: 4.12.00 18:08    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   generell network types and constants used in different algorithms
  
 * $Log: /current_work/ZenGin/_Bert/znettypes.h $
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
 * 6     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 5     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 4     4.12.99 20:49 Speckels
 * more implementation of the central networkmanager
 * 
 * 3     16.11.99 11:42 Speckels
 * Item/MOB-Interaktion, Pre-Release Netzwerk
 * 
 * 2     24.09.99 20:40 Speckels
 * VSS-kompatiblen Header eingefügt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:08 $)


#ifndef __ZNETTYPES_H__
#define __ZNETTYPES_H__


#ifndef __ZTYPES_H__
#include "ztypes.h"
#endif

#ifndef __ZSTRING_H__
#include "zstring.h"
#endif

#ifndef __ZERROR_H__
#include "zerror.h"
#endif

#ifndef _INC_MEMORY
#include <memory.h>
#endif

#ifndef __ZNET_WIN32_H__ 
#include "znet_win32.h"
#endif

#ifndef __ZDISK_H__
#include "zdisk.h"
#endif


// ////////////////////////////////////////////////////////////////
// constants
// ////////////////////////////////////////////////////////////////

const int		zNET_MAX_TYPES			= 10;	/// maximum of message-types
const int		zNET_MAX_HOSTS			= 5;	/// maximum of host in the game (including the local host)
const int		zNET_MAX_HOSTID			= 255;	/// largest hostid
const int		zNET_MAX_GROUPS			= 20;	/// maximum of groups
const int		zNET_MAX_PRIORITY		= 4;	/// number of different priorities (0 = highest priority)
const int		zNET_MAX_STREAMSIZE		= 20480;/// maximum size of streaming-buffers (grade will only allow int-values for buffer-length!!!)
const int		zNET_FAULT_ID			= 255;	/// error-ID
const int		zNET_LOCALHOST_ID		= 0;	/// ID for the local host


const zSTRING	zNET_ADDR_BROADCAST		("broadcast");
const zSTRING	zNET_ADDR_LOCALHOST		("127.0.0.1");

const zWORD		zNET_PORT_UDP_LISTEN	= 7207;
const zWORD		zNET_PORT_TCP_LISTEN	= 7208;

const zWORD		zNET_PORT_IPX_LISTEN	= 0;
const zWORD		zNET_PORT_SPX_LISTEN	= 0;

// ////////////////////////////////////////////////////////////////
// error-constants
// ////////////////////////////////////////////////////////////////


enum 
{
	zERR_NET_NO_NET			= 6001,
	zERR_NET_NO_INIT,
	zERR_NET_NO_PROVIDER,	
	zERR_NET_NO_MESSAGE,	
	zERR_NET_RECV,
	zERR_NET_SEND,
	zERR_NET_READ,
	zERR_NET_MISC,
	zERR_NET_CONNECT,

	zERR_NET_NO_HOST,
	zERR_NET_NO_VOB,	
	zERR_NET_NO_AIC,
	zERR_NET_NO_VISUAL,

	zERR_NET_DENIED
};


// ////////////////////////////////////////////////////////////////
// types and enumerations
// ////////////////////////////////////////////////////////////////

enum TNetMessage      { SEND, RECV };
enum TNetTarget       { NET_TARGET_ALL };
enum TNetPort		  { NET_SERVICE_PORT, NET_DGRAM_PORT, NET_STREAM_PORT };
enum TNetState		  { NET_NONE, NET_DISCONNECTED, NET_CONNECTED };
enum TNetMode		  { NET_SINGLEPLAYER, NET_MULTIPLAYER };

typedef zWORD	zNET_PORT;

typedef zDWORD	zTNetMessageID;
typedef zWORD	zTNetMessageSubID;


// ZenGin-Network-Messages

const int zNETID_EVENT			= 1000;
const int zNETID_EVENT_END		= 1999;

const int zNETID_VOBCTRL		= 2000;
const int zNETID_VOBCTRL_END	= 2999;


// Makros

// Vob-Description: "zCVobTrigger(&345)" or "netCNpc(Born&82732)"
#define zNET_VOB_DESCRIPTION(vob) \
	( (vob) ? (vob)->GetClassDef()->GetClassName_()+"("+(vob)->GetVobName()+"&"+zSTRING((vob)->GetVobID())+")" : "NULL")



// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znettypes.h
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////



#endif