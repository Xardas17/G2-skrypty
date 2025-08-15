/******************************************************************************** 
 
     $Workfile:: znethost.cpp         $                $Date:: 28.08.00 14:24   $
     $Revision:: 8                    $             $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/znethost.cpp $
 * 
 * 8     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 6     21.08.00 18:26 Speckels
 * 
 * 13    16.08.00 12:32 Admin
 * 
 * 5     10.08.00 21:47 Speckels
 * 
 * 12    9.08.00 17:12 Admin
 * 
 * 4     21.07.00 15:16 Speckels
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
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 8 $ ($Modtime: 24.08.00 12:09 $)




#include "znethost.h"
#include "znetmessage.h"


zBYTE zCNetHost::iter=0;

zCNetHost* zCNetHost::localhost=0;








// /////////////////////////////////////////////////////////////////////////
// zCNetHost
// /////////////////////////////////////////////////////////////////////////






zBOOL zCNetHost::InitHost(const zSTRING& _name)
{	
	stream_handle = 0;	

	if (_name==zNET_ADDR_BROADCAST) 
	{
		return InitHostForBroadcast();
	}

	zCNetSession* session = znet->GetSessionData();
	if (!session)
	{
		zerr.Fault("B: (zCNetHost) No session-data available!");
		return FALSE;
	};
	
	zSTRING _hostName = _name;
	memset(&hostPacketAddr,0,sizeof(hostPacketAddr));		
	memset(&hostStreamAddr,0,sizeof(hostStreamAddr));
	
	// if localhost get the real ip
	if (_hostName==zNET_ADDR_LOCALHOST)
	{
		_hostName = netGetLocalHost();
		SetLocalHost(this);
	}
	
	// now get the address (as zTNetAddressPtr) by hostname oder -adress
	zTNetAddressPtr pHostAddr = netGetHostAddr(_hostName.ToChar());	
	if (pHostAddr) 
	{
		InitHostAddr(pHostAddr);		
	}	
	else 
	{
		zerr.Message("B: (zCNetHost) Could not retrieve ip for "+_hostName);
		return FALSE;
	}
			
	hostName = GetReadableAddr();
	

	return TRUE;
}


zCNetHost::zCNetHost(zNET_HANDLE _stream_handle)
{
	Init(); 

	stream_handle = _stream_handle;
	
	InitHostAddr(netGetRemoteAddr(_stream_handle));	

	valid = TRUE;
}

zCNetHost::zCNetHost(const zSTRING& _hostName)
{	
	Init(); 

	valid = InitHost(_hostName);
}

zCNetHost::zCNetHost(const zTNetAddress& _hostAddr)
{
	Init(); 
	
	stream_handle = 0;	

	InitHostAddr((zTNetAddress*)&_hostAddr);	

	valid=TRUE;
}

void zCNetHost::Init()
{	
	id				= 0;
	stream_handle	= 0;
	valid			= false;
	
	hostName.Clear();

	memset(&hostStreamAddr,0,sizeof(hostStreamAddr));
	memset(&hostPacketAddr,0,sizeof(hostPacketAddr));	
};

zBOOL zCNetHost::InitHostForBroadcast()
{		
	stream_handle = 0;	

	zCNetSession* session = znet->GetSessionData();
	if (!session)
	{
		zERR_FAULT("B: (zCNetHost) No session-data available!");
		return FALSE;
	};

	zTNetAddress hostAddr;
	hostAddr.INET.IP = zNET_MAKEIP(255,255,255,255);
	InitHostAddr(&hostAddr);

	hostName = GetReadableAddr();

	return TRUE;
};


void zCNetHost::InitHostAddr(zTNetAddressPtr pHostAddr)
{			
	if (!pHostAddr) return; 

	memcpy(&hostPacketAddr,pHostAddr,sizeof(zTNetAddress));
	memcpy(&hostStreamAddr,pHostAddr,sizeof(zTNetAddress));

	zCNetSession* session = znet->GetSessionData();
	if (!session)
	{
		zERR_FAULT("B: (zCNetHost) No session-data available!");
		return;
	};
	switch (session->GetProtocol())
	{
	case  zNET_PROTOCOL_IPX:
		hostStreamAddr.IPX.Socket = session->GetListenStreamAddress().IPX.Socket;
		hostPacketAddr.IPX.Socket = session->GetListenPacketAddress().IPX.Socket;
		hostPacketAddr.Protocol = zNET_PROTOCOL_IPX;	
		hostStreamAddr.Protocol = zNET_PROTOCOL_IPX;
		break;
	case zNET_PROTOCOL_TCP:
		hostStreamAddr.INET.Port  = session->GetListenStreamAddress().INET.Port;			
		hostPacketAddr.INET.Port  = session->GetListenPacketAddress().INET.Port;			
		hostPacketAddr.Protocol = zNET_PROTOCOL_TCP;	
		hostStreamAddr.Protocol = zNET_PROTOCOL_TCP;
		break;					
	default:
		zERR_FATAL("B: (zCNetHost) unknown port-specifier");			
	}		
}

zCNetHost::~zCNetHost()
{	
	valid=FALSE;
}

/*
zCNetHost* zCNetHost::GetFirst() 
{ 
	return zCNetHostGroup::GetGameGroup()->GetFirstHost();	
}

zCNetHost* zCNetHost::GetNext()
{
	return zCNetHostGroup::GetGameGroup()->GetNextHost();	
}
*/

void zCNetHost::Pack(zCBuffer& buffer)
{
	buffer.Write(&id,sizeof(id));	
	buffer.WriteString(hostName);
}

void zCNetHost::Unpack(zCBuffer& buffer)
{
	buffer.Read(&id,sizeof(id));		
	hostName = buffer.ReadString();	
}

zCNetHost* zCNetHost::CreateFromBuffer(zCBuffer& buffer)
{	
	zTNetAddress packetAddr, streamAddr;
	// read adress
	buffer.Read(&packetAddr, sizeof(zTNetAddress));
	buffer.Read(&streamAddr, sizeof(zTNetAddress));
	// create object
	zCNetHost* host = zNEW(zCNetHost(packetAddr));
	host->Unpack(buffer);

	return host;
};

void zCNetHost::PackToBuffer(zCBuffer& buffer)
{
	// write adress
	buffer.Write(&hostPacketAddr, sizeof(zTNetAddress));		
	buffer.Write(&hostStreamAddr, sizeof(zTNetAddress));		
	// pack the rest
	Pack(buffer);
};

zBOOL zCNetHost::HasAddress(zTNetAddressPtr addr)
{
	zTNetAddress addr1 = hostPacketAddr;
	zTNetAddress addr2 = *addr;

	if (addr1.Protocol != addr2.Protocol) return FALSE;

	if (addr1.Protocol==zNET_PROTOCOL_TCP)
	{		
		addr1.INET.Port = 0;
		addr2.INET.Port = 0;		
	}
	else if (hostPacketAddr.Protocol==zNET_PROTOCOL_IPX)
	{
		addr1.IPX.Socket = 0;
		addr2.IPX.Socket = 0;		
	}		
	return (memcmp(&addr1, &addr2, sizeof(zTNetAddress))==0);
};

// /////////////////////////////////////////////////////////////////////////
// class zCNetHostGroup
// /////////////////////////////////////////////////////////////////////////




/*

void zCNetHostGroup::AddGroupToList()
{
	// search free space in host-list and apply host-id
	if (list.IsInList(this)) { zerr.Warning("B: (zCNetHostGroup::AddGroupToList) Group is already in list");return; }
	list.Insert(this);
}

void zCNetHostGroup::RemoveGroupFromList()
{
	if (!list.IsInList(this)) { zerr.Fault("B: (zCNetHostGroup::RemoveGroupFromList) Group is not in list");return; }
	list.Remove(this);
}

zCNetHostGroup::zCNetHostGroup(const zSTRING _name)
{
	name	= _name;		
	AddGroupToList();
}

zCNetHostGroup::~zCNetHostGroup()
{
	RemoveGroupFromList();
};

zCNetHost* zCNetHostGroup::GetHostByID(int id) 
{
	zCNetHost* host = GetFirstHost();
	while (host && host->GetID()!=id)
	{
		host = GetNextHost();
	};
	return host;
};

zCNetHost* zCNetHostGroup::GetFirstHost() 
{ 
	hostiter=0;
	if (hostiter>=hostlist.GetNumInList()) return 0;
	return hostlist.Get(hostiter);	
}

zCNetHost* zCNetHostGroup::GetNextHost() 
{	
	hostiter++;
	if (hostiter>=hostlist.GetNumInList()) return 0;
	return hostlist.Get(hostiter);	
}

zCNetHostGroup* zCNetHostGroup::GetFirst() 
{ 	
	iter=0;
	if (iter>=list.GetNumInList()) return 0;
	return list.Get(iter);	
}

zCNetHostGroup* zCNetHostGroup::GetNext() 
{	
	iter++;	
	if (iter>=list.GetNumInList()) return 0;
	return list.Get(iter);	
}


// Adding Host to this group by host-object
void zCNetHostGroup::AddHost(zCNetHost* _host)		
{ 		
	if (hostlist.IsInList(_host)) return;

	hostlist.Insert(_host);

	// set port to PACKET-PORT
	_host->SetPort(UNRELIABLE);
};

// Removing Host from this group by host-object
void zCNetHostGroup::RemHost(zCNetHost* _host)
{ 
	if (!hostlist.IsInList(_host)) return;
	hostlist.Remove(_host);
};

// Asking if the host (specified by host-object) is in the group
zBOOL zCNetHostGroup::IsMember(zCNetHost* _host)	
{ 
	return hostlist.IsInList(_host);	
}

*/

// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znethost.cpp
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
