/******************************************************************************** 
 
     $Workfile:: zplayergroup.cpp     $                $Date:: 25.01.01 12:14   $
     $Revision:: 11                   $             $Modtime:: 25.01.01 11:53   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/zplayergroup.cpp $
 * 
 * 11    25.01.01 12:14 Moos
 * 
 * 10    30.08.00 18:56 Moos
 * 
 * 9     29.08.00 17:48 Moos
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
 * 4     21.07.00 15:17 Speckels
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
 * 8     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 7     19.01.00 1:11 Speckels
 * class zERROR with indent (begin and end-flags)
 * 
 * 6     3.12.99 16:10 Speckels
 * complete checkin from 3.12.99
 * 
 * 5     21.10.99 23:29 Speckels
 * Work on error-handling and
 * item-interaction
 * 
 * 4     29.09.99 17:38 Speckels
 * Debuginformationen entfernt
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 11 $ ($Modtime: 25.01.01 11:53 $)



#include "zcore.h"
#include "zplayergroup.h"
#include "zplayerinfo.h"
#include "znethost.h"



zCList<zCPlayerGroup> zCPlayerGroup::group_list;
zCPlayerGroup zCPlayerGroup::allPlayerGroup("all");


// /////////////////////////////////////////////////////////////////////////
// class zCPlayerGroup
// /////////////////////////////////////////////////////////////////////////


static int SortListEntries (zCPlayerInfo *player1, zCPlayerInfo *player2)
{
	if (player1->GetID()==player2->GetID()) return 0;
	else if (player1->GetID()<player2->GetID()) return -1;
	else if (player1->GetID()>player2->GetID()) return 1;
	return 1;
};


void zCPlayerGroup::AddGroupToList()
{
	if (group_list.IsInList(this)) { zERR_WARNING("B: (zCPlayerGroup::AddGroupToList) Group is already in list");return; }
    group_list.PreAlloc(10);
	group_list.Insert(this);
}

void zCPlayerGroup::RemoveGroupFromList()
{
	if (!group_list.IsInList(this)) { zERR_FAULT("B: (zCPlayerGroup::RemoveGroupFromList) Group is not in list");return; }
	group_list.Remove(this);
}




zCPlayerGroup::zCPlayerGroup(const zSTRING& _name)
{
	name	= _name;		
	player_list.SetCompare(&SortListEntries);

	AddGroupToList();
}

zCPlayerGroup::~zCPlayerGroup()
{
	ResetPlayerList();
	
	RemoveGroupFromList();
};


zCPlayerInfo* zCPlayerGroup::GetFirstPlayer(int& iter) 
{ 
	iter = 0;
	if (iter>=player_list.GetNumInList()) return 0;
	return player_list.Get(iter);
}

zCPlayerInfo* zCPlayerGroup::GetNextPlayer(int& iter) 
{	
	iter++;
	if (iter>=player_list.GetNumInList()) return 0;
	return player_list.Get(iter);	
}

zCPlayerGroup* zCPlayerGroup::GetFirstGroup(int& iter) 
{ 	
	iter = 0;
	if (iter>=group_list.GetNumInList()) return 0;
	return group_list.Get(iter);	
}

zCPlayerGroup* zCPlayerGroup::GetNextGroup(int& iter) 
{	
	iter++;	
	if (iter>=group_list.GetNumInList()) return 0;
	return group_list.Get(iter);	
}


// Adding Host to this group by host-object
zBOOL zCPlayerGroup::AddPlayer(zCPlayerInfo* player)		
{	
	if (player_list.IsInList(player)) return FALSE;

	player_list.InsertSort(player);
	return FALSE;
};

// Removing Host from this group by host-object
zBOOL zCPlayerGroup::RemPlayer(zCPlayerInfo* player)
{ 
	if (!player_list.IsInList(player)) return FALSE;
	
	player_list.Remove(player);	
	return TRUE;

};

// Asking if the host (specified by host-object) is in the group
zBOOL zCPlayerGroup::IsMember(zCPlayerInfo* player)	
{ 
	return player_list.IsInList(player);	
}

zCPlayerInfo* zCPlayerGroup::GetPlayerByID(zBYTE id)
{	
	int iter;
	zCPlayerInfo* player = GetFirstPlayer(iter);
	while (player)
	{
		if (player->GetID()==id) return player;
		player = GetNextPlayer(iter);
	};
	return 0;
};

void zCPlayerGroup::ShowDebugInfo()
{
	zSTRING text;
	zERR_MESSAGE(1, zERR_BEGIN, "B: PGROUP: PlayerGroup \""+GetName()+"\")");
	zERR_MESSAGE(1, 0, "B: PGROUP: "+zSTRING(GetNumPlayers())+" players");

	int iter;
	zCPlayerInfo* player = GetFirstPlayer(iter);
	while (player)
	{
		if (player->GetNetHost()) text = player->GetNetHost()->GetHostname()+":"+zSTRING(player->GetNetHost()->GetID()); else text="no host";
		zERR_MESSAGE(1, 0, "B: PGROUP: Player: \""+player->GetName()+"\" ("+text+") id="+zSTRING(player->GetID()));
		player = GetNextPlayer(iter);
	};

	zERR_MESSAGE(0,zERR_END,"");
};

/* ----------------------------------------------------------------------
	
    zCPlayerGroup::ResetPlayerList()	

	30.08.2000	[Moos]	
                Daten werden nun gelöscht

   ---------------------------------------------------------------------- */

void zCPlayerGroup::ResetPlayerList()
{ 
    zCListSort<zCPlayerInfo> *ptr=&player_list;
    while (ptr){
        zCPlayerInfo *del = ptr->data;
        ptr->data=NULL;
        ptr=ptr->next;
        delete del;   // [Moos] Räume den kram richtig weg. Wenn das abstürze macht:
                      // auch Ulf/oWorld.cpp aktualisieren...
    }

	player_list.DeleteList();  
}

void zCPlayerGroup::ResetGroupList()
{
	zCPlayerGroup* tempgroup;
	int iter;
	zCPlayerGroup* group = zCPlayerGroup::GetFirstGroup(iter);
	while (group)
	{
		group->ResetPlayerList();
		tempgroup = group;
		group = group->GetNextGroup(iter);
		delete tempgroup;
	};
	group_list.DeleteList(); 
}

zCPlayerInfo* zCPlayerGroup::GetNearestPlayerToVob(zCVob* vob, zCPlayerInfo* excludedPlayer)
{
	zCPlayerInfo *player, *nearestPlayer = 0;
	zCVob* playerVob;
	zREAL nearestDist=zREAL_MAX, dist;

	int iter;
	player = GetFirstPlayer(iter);
	while (player)
	{
		playerVob = player->GetPlayerVob();
		if (playerVob)
		{
			dist = playerVob->GetDistanceToVob2(*vob);
			if ((dist<nearestDist) && (player!=excludedPlayer)) 
			{
				nearestDist = dist;
				nearestPlayer = player;
			}

		};
		player = GetNextPlayer(iter);
	};

	return nearestPlayer;
};

// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
// END OF znethost.cpp
// /////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////
