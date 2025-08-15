/******************************************************************************** 
 
     $Workfile:: znethost.h          $                 $Date:: 4.12.00 18:22    $
     $Revision:: 8                   $              $Modtime:: 4.12.00 18:11    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   this class handles network-computers (host) with a network-address
 
 * $Log: /current_work/ZenGin/_Bert/znethost.h $
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
 * 6     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
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
/// @version $Revision: 8 $ ($Modtime: 4.12.00 18:11 $)



#ifndef __ZNETHOST_H__
#define __ZNETHOST_H__

#ifndef __ZNET_H__
#include "znet.h"
#endif

#ifndef __ZBUFFER_H__
#include "zbuffer.h"
#endif

class zCNetMessage;
class zCVob;

/** this class is representing a host
  * A host represents a player in the game. It's computer (the host) has a name, adress and id.
  * All the hosts could be iterated by the (static) GetFirst()- and (nonstatic) GetNext()-methods.
  */
class zCNetHost
{		
public:
	
	static zCNetHost* GetFirst();
	static zCNetHost* GetLocalHost()					{ return localhost; }		
	static void       SetLocalHost(zCNetHost* host)		{ localhost = host; }			
		
	//
	// construction and deconstruction
	//

	/** construct host using a tcp-handle (received by netListenStream)
	  * host will be added to the hostgroup "all"
	  */
	zCNetHost(zNET_HANDLE _stream_handle);

	/** construct host using its hostname or IP
	  * host will be added to the hostgroup "all"
	  */
	zCNetHost(const zSTRING& _hostName);

	/** construct host using his hostaddress
	  * host will be added to the hostgroup "all"
	  */
	zCNetHost(const zTNetAddress& _hostAddr);
	
	/** destructing
	  * host will be removed from the hostgroup "all"
	  */
	virtual			~zCNetHost();	

	/** initialize this host by the given hostName	  
	  */
	zBOOL			InitHost(const zSTRING& _hostName);

	/** create a broadcast-host
	  */
	zBOOL			InitHostForBroadcast();	

	/// retrieve the hosts ID	
	
	//
	// getting host-properties
	//
	
	void			SetID			(const zBYTE _id)					{ id = _id; };	
	void			SetStreamHandle	(zNET_HANDLE _handle)				{ stream_handle = _handle; };

	zBYTE			GetID			()	const							{ return id; };
	zNET_HANDLE		GetStreamHandle	()	const							{ return stream_handle; }	
	zSTRING			GetHostname		()	const							{ return hostName;	}
	zSTRING			GetReadableAddr	()									{ return zSTRING(netAddrToString(&hostPacketAddr,false)); } 	
	zTNetAddressPtr	GetPacketAddr	()									{ return &hostPacketAddr; }	
	zTNetAddressPtr	GetStreamAddr	()									{ return &hostStreamAddr; }	
	
	zBOOL			IsValid			()									{ return valid; };
	
	zBOOL			HasAddress(zTNetAddressPtr addr);

	static zCNetHost*	CreateFromBuffer(zCBuffer& buffer);
	void				PackToBuffer(zCBuffer& buffer);

	zCNetHost* GetNext();

protected:	

	void Init();

	/** default-constructor	  
	  */
	zCNetHost() {};

	void InitHostAddr(const zTNetAddressPtr pHostAddr);

	void Pack	(zCBuffer& buffer);

	void Unpack	(zCBuffer& buffer);	
	
	/** remove this host from the list of all groups (hostgroup "all")	  
	  */
	void RemoveHostFromList();

	/** add this host to the list of all groups (hostgroup "all")	  
	  */
	void AddHostToList();

private:

	// host-properties		
	zBYTE				id;
	zSTRING				hostName;
	zTNetAddress		hostStreamAddr;
	zTNetAddress		hostPacketAddr;
	zBOOL				valid;

	zNET_HANDLE			stream_handle;

	// other member
	static zBYTE		iter;
	static zCNetHost*	localhost;		


	zCNetHost(zCNetHost&);
	zCNetHost& operator=(zCNetHost&);

};



typedef zCNetHost* zCNetHostPtr;


// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znethost.h
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////

#endif