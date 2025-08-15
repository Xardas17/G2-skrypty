/******************************************************************************** 
 
     $Workfile:: zgameinfo.cpp        $                $Date:: 28.08.00 14:24   $
     $Revision:: 8                    $             $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zgameinfo.cpp $
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
 * 5     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 4     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 3     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 8 $ ($Modtime: 24.08.00 12:09 $)



#include "zcore.h"
#include "zgameinfo.h"
#include "zplayerinfo.h"
#include "zplayergroup.h"
#include "znethost.h"

zCGameInfo::zCGameInfo()
{		
	name.Clear();	
};

	/// destructor
zCGameInfo::~zCGameInfo() 
{
}	

void zCGameInfo::Init()
{ 			
	zCPlayerGroup::GetAllPlayerGroup()->ResetPlayerList();
};

void zCGameInfo::Reset()  
{ 		
	Init();
};

zBOOL zCGameInfo::AddPlayer(zCPlayerInfo* player)
{	
	return zCPlayerGroup::GetAllPlayerGroup()->AddPlayer(player);		
};

zBOOL zCGameInfo::RemPlayer(zCPlayerInfo* player)
{
	return zCPlayerGroup::GetAllPlayerGroup()->RemPlayer(player);	
};

zCPlayerInfo* zCGameInfo::GetPlayerByID(int id)
{	
	return zCPlayerGroup::GetAllPlayerGroup()->GetPlayerByID(id);
};


zCPlayerInfo* zCGameInfo::GetPlayerByVobID(zTVobID vobID)
{
	int iter;
	zCPlayerInfo* player = zCPlayerGroup::GetAllPlayerGroup()->GetFirstPlayer(iter);
	while (player)
	{
		if (player->GetPlayerVob()->GetVobID() == vobID) return player;
		player = (zCPlayerInfo*)zCPlayerGroup::GetAllPlayerGroup()->GetNextPlayer(iter);
	};
	return 0;
};

void zCGameInfo::PackToBuffer(zCBuffer& buffer, zBYTE flag)
{
	Pack(buffer,flag);	
};

zCGameInfo*	zCGameInfo::CreateFromBuffer(zCBuffer& buffer)
{
	zCGameInfo* gameinfo = zfactory->CreateGameInfo();	
	gameinfo->Unpack(buffer);
	return gameinfo;
};

int	zCGameInfo::GetNumPlayers()
{
	return 	zCPlayerGroup::GetAllPlayerGroup()->GetNumPlayers();	
};

/// packs all relevant data into a network-packet
void zCGameInfo::Pack(zCBuffer& buffer, zBYTE flag)
{ 
	buffer.WriteByte(flag);

	// generell information about the game
	if (flag & zPCK_GAMEINFO_INFO)
	{	
		buffer.WriteString(GetName());
	}

	// informations about the players	
	if (flag & zPCK_GAMEINFO_PLAYER)
	{				
		buffer.WriteWord(zCPlayerGroup::GetAllPlayerGroup()->GetNumPlayers());

		int iter;
		zCPlayerInfo* player = zCPlayerGroup::GetAllPlayerGroup()->GetFirstPlayer(iter);
		while (player)
		{			
			player->PackToBuffer(buffer);
			player = zCPlayerGroup::GetAllPlayerGroup()->GetNextPlayer(iter);
		}
	}	
};


/// unpacks the needed information from a network-packet
void zCGameInfo::Unpack(zCBuffer& buffer) 
{	
	zCPlayerGroup::GetAllPlayerGroup()->ResetPlayerList();	

	zBYTE flag;
	flag = buffer.ReadByte();;

	// general info about the game
	if (flag & zPCK_GAMEINFO_INFO)
	{	
		name = buffer.ReadString();
	};

	// information about all players
	if (flag & zPCK_GAMEINFO_PLAYER)
	{
		zCPlayerInfo* player;
		zWORD count;
		count = buffer.ReadWord();
		for (int i=0;i<count;i++)
		{			
			player = zCPlayerInfo::CreateFromBuffer(buffer);
			AddPlayer(player);
		};	
	}
};

zCPlayerInfo* zCGameInfo::GetPlayerByNetAddress(zTNetAddress& addr)
{
	int iter;
	zCPlayerGroup*	group	= zCPlayerGroup::GetAllPlayerGroup();	
	zCPlayerInfo*	player	= group->GetFirstPlayer(iter);
	zCNetHost*		host	= 0;

	while (player)
	{
		host = player->GetNetHost();		
		if (host->HasAddress(&addr)) return player;		
		player = group->GetNextPlayer(iter);
	};
	return 0;
};