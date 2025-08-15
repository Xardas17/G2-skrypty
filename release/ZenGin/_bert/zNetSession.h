/******************************************************************************** 
 
     $Workfile:: znetsession.h       $                 $Date:: 4.12.00 18:22    $
     $Revision:: 8                   $              $Modtime:: 4.12.00 18:09    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   the class zCNetSession handles unary network-informations used in a
   network-session
 
 * $Log: /current_work/ZenGin/_Bert/znetsession.h $
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
 * 4     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
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
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:09 $)


#ifndef __ZNETSESSION_H__
#define __ZNETSESSION_H__


// #include "znettypes.h"

#ifndef __ZNETHOST_H__
#include "znethost.h"
#endif

/** 
  * 
  */
class zCNetSession
{	
public:
	zCNetSession(zWORD _protocol);	
	virtual ~zCNetSession();	
	void Reset();
	
	zTNetAddress&		GetListenPacketAddress() { return listenPacketAddress; };
	zTNetAddress&		GetListenStreamAddress() { return listenStreamAddress; };
	zWORD			GetProtocol() { return protocol; };

	zBOOL IsValid() { return valid; };
	
private:	

	/// network-protocol used by grade
	zWORD protocol;
	
	/// listing for packets (IPX or UDP)
	zTNetAddress listenPacketAddress;

	/// listing for stream-connenction (SPX or TCP)
	zTNetAddress listenStreamAddress;	

	zBOOL valid;
};


// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znetsession.h
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////

#endif