/******************************************************************************** 
 
     $Workfile:: zplayerinfo.cpp      $                $Date:: 6.02.01 13:41    $
     $Revision:: 13                   $             $Modtime:: 6.02.01 13:15    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zplayerinfo.cpp $
 * 
 * 13    6.02.01 13:41 Moos
 * 
 * 12    28.08.00 14:24 Speckels
 * 
 * 17    23.08.00 21:47 Admin
 * 
 * 10    21.08.00 20:50 Speckels
 * 
 * 9     21.08.00 18:47 Speckels
 * 
 * 8     21.08.00 18:26 Speckels
 * 
 * 15    16.08.00 12:32 Admin
 * 
 * 7     10.08.00 21:47 Speckels
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 6     21.07.00 15:17 Speckels
 * 
 * 5     10.07.00 15:24 Speckels
 * 
 * 3     5.05.00 13:46 Speckels
 * 
 * 4     3.05.00 19:14 Speckels
 * 
 * 3     1.05.00 16:07 Edenfeld
 * 
 * 2     26.04.00 11:26 Admin
 * 
 * 2     19.04.00 18:35 Speckels
 * 
 * 5     30.03.00 14:24 Speckels
 * 
 * 7     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 6     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 5     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 4     21.10.99 23:27 Speckels
 * new pingmethods (moved from
 * netCPlayerInfo)
 * 
 * 3     29.09.99 17:38 Speckels
 * Debuginformationen entfernt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 13 $ ($Modtime: 6.02.01 13:15 $)


#include "zcore.h"
#include "zplayerinfo.h"
#include "zoption.h"
#include "znethost.h"
#include "zplayergroup.h"
#include "zarchiver.h"

#include "zAccount.h"

// Verwaltung von Spieler-IDs
zCArray<int> zCPlayerInfo::free_ids;
zBYTE zCPlayerInfo::next_id=1;

///////////////////////////////////////////////////////////////////////
// PLAYER-Informations
///////////////////////////////////////////////////////////////////////

zCPlayerInfo::zCPlayerInfo()
{	
	name.Clear();			
	netHost			=	NULL;
	hostVob			=	NULL;
	scriptBuffer	= NULL;
	
	id					= 0;
	pingLost			= 0;
	pingTime			= 0;
	pingTimeStart		= 0;

	worldInfo			= 0;

	deactivated			= FALSE;
	ready				= FALSE;	
};

zCPlayerInfo::~zCPlayerInfo()
{	
	if (IsActive()) activePlayer = NULL;
	
	// Entferne den Spieler aus allen Gruppen.
	int iter;
	zCPlayerGroup* group = zCPlayerGroup::GetFirstGroup(iter);
	while (group)
	{
		group->RemPlayer(this);
		group = group->GetNextGroup(iter);
	};	

	worldInfo			= 0;

	// Gib die id wieder frei
	if (id>0)
	{
		if (id==next_id-1) next_id = id; else free_ids.InsertEnd(id);
		
		zERR_MESSAGE(4, 0, "B: PINFO: Removed player "+GetName()+" with id "+zSTRING(id));
	}	

	SetPlayerVob(0);
};



zCPlayerInfo* zCPlayerInfo::CreateDistinctPlayer()
{
	if (free_ids.GetNumInList()>0)
	{
		id = free_ids[0];
		free_ids.RemoveIndex(0);
	}
	else 
	{
		id = next_id;
		next_id++;
	}	

	if (netHost) netHost->SetID(id);

	zERR_MESSAGE(4, 0, "B: PINFO: Created distinct player "+GetName()+" with id: "+zSTRING(id));

	return this;
};


void zCPlayerInfo::Init(const zSTRING& _name, zNET_HANDLE _handle)
{ 		
	name = _name;	
	// initialize network-host
	if (_handle!=0)
	{
		if (netHost) { delete netHost; netHost=0; }
		netHost = zNEW(zCNetHost(_handle));
	}
}


void zCPlayerInfo::Init(const zSTRING& _name, const zSTRING& addr)
{ 		
	name = _name;

	// initialize network-host
	if (!addr.IsEmpty())
	{
		if (netHost) { delete netHost; netHost=0; }
		netHost = zNEW(zCNetHost(addr));
	}
}


void zCPlayerInfo::Pack(zCBuffer& buffer)
{
	// write network-host (if existent)
	zBOOL hasNetHost = (netHost!=0);
	buffer.WriteBool(hasNetHost,1);
	if (hasNetHost) netHost->PackToBuffer(buffer);
	
	// write rest of data
	buffer.WriteString(name);
	buffer.WriteByte(id);
	buffer.WriteBool(ready,1);
};

void zCPlayerInfo::Unpack(zCBuffer& buffer)
{
	// initialize network-host
	if (netHost) { delete netHost;netHost=0; }
	zBOOL hasNetHost = buffer.ReadBool(1);
	if (hasNetHost)	netHost = zCNetHost::CreateFromBuffer(buffer);	
	
	// read rest of the data
	name = buffer.ReadString();
	id   = buffer.ReadByte();
	ready = buffer.ReadBool(1);
};

zBYTE zCPlayerInfo::GetID() const
{
	return id;
};

zCPlayerInfo*	zCPlayerInfo::CreateFromBuffer(zCBuffer& buffer)
{
	zCPlayerInfo* player = zfactory->CreatePlayerInfo();
	player->Unpack(buffer);
	return player;
};

void zCPlayerInfo::PackToBuffer(zCBuffer& buffer)
{
	Pack(buffer);
};

zCPlayerInfo* zCPlayerInfo::activePlayer = 0;

zCPlayerInfo* zCPlayerInfo::GetActivePlayer() 
{ 
	return activePlayer; 
};

void zCPlayerInfo::SetActive()
{
	if (IsActive()) return;

	zERR_MESSAGE(7,0,"B: PINFO: Setting player "+GetName()+"("+zSTRING(GetID())+") as active player");
	activePlayer = this;
};

zBOOL zCPlayerInfo::IsActive()
{
	return this == GetActivePlayer();
};

void zCPlayerInfo::Reset()
{
	
};

void zCPlayerInfo::StorePlayerVobAsScript()
{
	if (scriptBuffer) delete scriptBuffer;
	scriptBuffer = 0;

	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_BINARY, TRUE);

	arch->WriteObject("playerHostVob",hostVob);

	zCBuffer* buffer = arch->GetBuffer();;
	scriptBuffer = zNEW(zCBuffer(buffer->GetSize()+1));
	scriptBuffer->Write(buffer->GetBuffer(),buffer->GetSize());

	arch->Close();	
	zRELEASE(arch);

	scriptBuffer->SetPosBegin();
};

zCVob* zCPlayerInfo::CreatePlayerVobFromScript()
{
	if (hostVob) zRELEASE(hostVob);
	
	scriptBuffer->SetPosBegin();

	zCArchiver* arch = zarcFactory.CreateArchiverRead(scriptBuffer);	
	zCVob* vob = dynamic_cast<zCVob*>(arch->ReadObject("playerHostVob"));
	arch->Close();
	zRELEASE(arch);

	hostVob = vob;
	
	return vob;
};

zCBuffer* zCPlayerInfo::GetPlayerVobScript()
{
	scriptBuffer->SetPosBegin();
	return scriptBuffer;
};

void zCPlayerInfo::SetPlayerVobScript(zCBuffer* buffer)
{
	if (scriptBuffer) delete scriptBuffer;
	scriptBuffer = 0;

	scriptBuffer = zNEW(zCBuffer(buffer->GetSize()+1));
	scriptBuffer->Write(buffer->GetBuffer(),buffer->GetSize());		
};

void zCPlayerInfo::SetPlayerVob(zCVob* _vob)
{ 
	if (hostVob) zRELEASE_ACCT(hostVob);
	hostVob = _vob; 
	if (hostVob) zADDREF_ACCT(hostVob);
};

void zCPlayerInfo::Deactivate(zBOOL deactivate)
{
	deactivated = deactivate;
}; 

zBOOL zCPlayerInfo::IsDeactivated()	const
{
	return deactivated;
};

void zCPlayerInfo::SetReady(const zBOOL _ready)
{
	ready = _ready;
};

zBOOL zCPlayerInfo::IsReady() const
{
	return ready;
};


zDWORD zCPlayerInfo::SetPingStart()
{
	if (pingTimeStart!=0) pingLost++;
	pingTimeStart = sysGetTime();
	return 0;
};

zDWORD zCPlayerInfo::SetPingEnd()
{
	pingTime = 0;
	if (pingTimeStart>0) pingTime = sysGetTime() - pingTimeStart;
	pingTimeStart = 0;
	pingLost=0;
	return pingTime;
};
