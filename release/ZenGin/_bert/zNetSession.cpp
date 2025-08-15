/******************************************************************************** 
 
     $Workfile:: znetsession.cpp      $                $Date:: 28.08.00 14:24   $
     $Revision:: 7                    $             $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/znetsession.cpp $
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
 * 4     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 3     21.10.99 23:29 Speckels
 * Work on error-handling and
 * item-interaction
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 7 $ ($Modtime: 24.08.00 12:09 $)




#include "znetsession.h"

zCNetSession::zCNetSession(zWORD _protocol)
{				
	memset(&listenPacketAddress,0,sizeof(zTNetAddress));
	memset(&listenStreamAddress,0,sizeof(zTNetAddress));   
		
	protocol = _protocol;
	switch (protocol)
	{
		case zNET_PROTOCOL_IPX:		
		listenPacketAddress.IPX.Socket = zNET_PORT_IPX_LISTEN;
		listenStreamAddress.IPX.Socket = zNET_PORT_SPX_LISTEN;		
		break;
		case zNET_PROTOCOL_TCP: 		
		listenPacketAddress.INET.Port  = zNET_PORT_UDP_LISTEN;
		listenStreamAddress.INET.Port  = zNET_PORT_TCP_LISTEN;				
		break;
	}		
	listenPacketAddress.Protocol = protocol;
	listenStreamAddress.Protocol = protocol;
	
	valid = netGetProtocolSupported(protocol);
};

void zCNetSession::Reset()
{			
	valid = netGetProtocolSupported(protocol);
};

zCNetSession::~zCNetSession()
{	
};

