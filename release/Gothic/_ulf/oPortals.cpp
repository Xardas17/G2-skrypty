
/******************************************************************************** 
 
     $Workfile:: oPortals.cpp         $                $Date:: 6.02.01 21:00    $
     $Revision:: 9                    $             $Modtime:: 6.02.01 16:00    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   
 *********************************************************************************/

#include "zCore.h"

#include "oPortals.h"
#include "zVob.h"
#include "oNpc.h"

// TMP : debugging purposes
#include "ogame.h"
#include "oguilds.h"

// *******************************************************************************
// Single PortalRoom
// *******************************************************************************

oCPortalRoom :: oCPortalRoom()
{
	portalName	.Clear();
	ownerNpc	.Clear();		
	ownerGuild	= -1;
};

oCPortalRoom :: oCPortalRoom(const zSTRING& name)
{
	portalName	= name;
	portalName	.Upper();
	ownerNpc	.Clear();
	ownerGuild	= -1;
};

oCPortalRoom :: ~oCPortalRoom()
{
};

oCNpc* oCPortalRoom :: GetOwnerNpc()
{
	if (ownerNpc.IsEmpty()) return NULL;
	if (!ogame)				return NULL;
	return zDYNAMIC_CAST<oCNpc>(ogame->GetWorld()->SearchVobByName(ownerNpc));
};

int oCPortalRoom :: GetOwnerGuild()
{
	return ownerGuild;
};

zSTRING& oCPortalRoom :: GetPortalName()
{
	return portalName;
}

zBOOL oCPortalRoom :: IsPortalMyRoom(oCNpc* npc)
{
	zBOOL myRoom = FALSE;
	if (ownerNpc>=0)				myRoom = (ownerNpc == npc->GetInstance());
	if (!myRoom && (ownerGuild>=0))	myRoom = (ownerGuild == npc->GetTrueGuild());
	return myRoom;
};

void oCPortalRoom :: SavePortalData(zCArchiver& arc)
{
	arc.WriteString	("portalName",	portalName);
	arc.WriteString	("ownerNpc",	ownerNpc);
	arc.WriteInt	("ownerGuild",	ownerGuild);
};

void oCPortalRoom :: LoadPortalData(zCArchiver& arc)
{
	arc.ReadString	("portalName",	portalName);
	arc.ReadString	("ownerNpc",	ownerNpc);
	arc.ReadInt		("ownerGuild",	ownerGuild);
};

// *******************************************************************************
// PortalRoom Manager
// *******************************************************************************

int oCPortalRoomManager :: SortPortals (const void* ele1,const void* ele2)
{
	oCPortalRoom* room1 = *((oCPortalRoom**)ele1);
	oCPortalRoom* room2 = *((oCPortalRoom**)ele2);

	if (room1->GetPortalName() < room2->GetPortalName()) 
		return -1;
	else
		return 1;
}

oCPortalRoomManager :: oCPortalRoomManager ()
{
	oldPlayerPortal = NULL;
	oldPlayerRoom	= NULL;
	curPlayerPortal = NULL;
	curPlayerRoom	= NULL;
	portals.SetCompare(SortPortals);
};

void oCPortalRoomManager :: CleanUp()
{
	oldPlayerPortal = NULL;
	oldPlayerRoom	= NULL;
	curPlayerPortal = NULL;
	curPlayerRoom	= NULL;
	int i = 0, c = portals.GetNumInList();
	while (i<c) {
		delete (portals[i]);
		i++;
	}
	portals.EmptyList();
};

oCPortalRoomManager :: ~oCPortalRoomManager()
{
	CleanUp();
};

void oCPortalRoomManager :: AssignPortalToNpc(const zSTRING& portal, const zSTRING& npcInstance)
{	
	oCPortalRoom* room = zNEW( oCPortalRoom(portal) );
	room->SetOwnerNpc(npcInstance);
	portals.InsertSort(room);
};

void oCPortalRoomManager :: AssignPortalToGuild(const zSTRING& portal, int guildNr)
{	
	oCPortalRoom* room = zNEW( oCPortalRoom(portal) );
	room->SetOwnerGuild(guildNr);
	portals.InsertSort(room);
};

int oCPortalRoomManager :: GetPortalRoomIndex ( const zSTRING& name )
{
	if (portals.GetNumInList()<=0) return -1;
	if (name.IsEmpty()) return -1;

	// Binary Search	
	// return value= found index, -1=not found
	int ind_low		= 0;
	int ind_high	= portals.GetNumInList()-1;
	int index		= ( ind_low + ind_high ) / 2;
	int erg;
	zSTRING foundName;

	do {
		foundName = portals[index] -> GetPortalName();
		if (foundName > name)	erg = -1;	else
		if (foundName < name)	erg =  1;	else
								erg =  0;

		if (ind_high <= ind_low) {
			if (erg==0) return index;
			return -1;
		}

		if (erg>0) 	ind_low	= index + 1; else
		if (erg<0)  ind_high= index - 1; else
					return index;

		index = ( ind_low + ind_high ) / 2;
	
	} while (1);
	
	return -1;
}

zBOOL oCPortalRoomManager :: IsPlayerInMyRoom(oCNpc* owner)
{
	if (!oCNpc::player)		return FALSE;
	curPlayerPortal = (zSTRING*)oCNpc::player->GetSectorNameVobIsIn();
	if (!curPlayerPortal)	return FALSE;

	return IsPortalMyRoom(*curPlayerPortal,owner);
}

zBOOL oCPortalRoomManager :: IsNSCInPlayerRoom(oCNpc* owner)
{
	if (!oCNpc::player)		return FALSE;
	if (!owner)				return FALSE;
	zSTRING *p1 = NULL; 
	zSTRING *p2 = NULL;
	p1 = (zSTRING*)oCNpc::player->GetSectorNameVobIsIn();
	p2 = (zSTRING*)owner->GetSectorNameVobIsIn();

	return (p2 == p1);
};

zBOOL oCPortalRoomManager :: WasPlayerInMyRoom(oCNpc* owner)
{
	if (!oCNpc::player)		return FALSE;
	if (!oldPlayerPortal)	return FALSE;

	return IsPortalMyRoom(*oldPlayerPortal,owner);
}

zBOOL oCPortalRoomManager :: IsPortalMyRoom(const zSTRING &name, oCNpc* npc)
{
	oCPortalRoom* portal = NULL;
		
	// Suche entsprechende Portalnamen
	int startIndex  = GetPortalRoomIndex(name);
	int index		= startIndex;
	
	// Valid, und nach unten wandern....
	while (zInRange(index,0,portals.GetNumInList())) {
		
		portal = portals[index];
		if (portal->GetPortalName() == *curPlayerPortal) {
			
			if (portal->IsPortalMyRoom(npc)) return TRUE;
			index -= 1;
			
		} else {
			// Stop now
			index = -1;
		}
	}

	// Valid, und nach oben wandern....
	index = startIndex+1;
	while (zInRange(index,0,portals.GetNumInList())) {
		
		portal = portals[index];
		if (portal->GetPortalName() == *curPlayerPortal) {
			
			if (portal->IsPortalMyRoom(npc)) return TRUE;
			index += 1;
			
		} else {
			// Stop now
			index = -1;
		}
	}

	return FALSE;
};

oCNpc* oCPortalRoomManager :: GetCurPlayerPortalRoomOwner()
{
	if (curPlayerRoom)	return curPlayerRoom->GetOwnerNpc();
	else				return NULL;
}

int oCPortalRoomManager :: GetCurPlayerPortalRoomGuild()
{
	if (curPlayerRoom)	return curPlayerRoom->GetOwnerGuild();
	else				return NULL;
}

oCNpc* oCPortalRoomManager :: GetFormerPlayerPortalRoomOwner()
{
	if (oldPlayerRoom)	return oldPlayerRoom->GetOwnerNpc();
	else				return NULL;
}

int oCPortalRoomManager :: GetFormerPlayerPortalRoomGuild()
{
	if (oldPlayerRoom)	return oldPlayerRoom->GetOwnerGuild();
	else				return NULL;
}

zBOOL oCPortalRoomManager :: HasPlayerChangedPortalRoom()
{
	zSTRING* activePortal = (zSTRING*)oCNpc::player->GetSectorNameVobIsIn();
	if (activePortal != curPlayerPortal) {
		// Changed Portal
		oldPlayerPortal = curPlayerPortal;
		oldPlayerRoom	= curPlayerRoom;
		curPlayerPortal = activePortal;
		curPlayerRoom	= NULL;
		if (curPlayerPortal) {
			int index = GetPortalRoomIndex(*curPlayerPortal);
			if (index>=0) curPlayerRoom = portals[index];
		}
		return TRUE;
	}
	return FALSE;
};

oCNpc* oCPortalRoomManager :: GetCurNpcPortalRoomOwner( oCNpc* npc )
{
	oCNpc* owner= NULL;

	if (npc)
	{
		zSTRING* curNpcPortal = (zSTRING*)npc->GetSectorNameVobIsIn();
		if (curNpcPortal)
		{
			int index = GetPortalRoomIndex(*curNpcPortal);
			if (index >= 0)
			{
				oCPortalRoom* curNpcRoom = portals[index];
				if (curNpcRoom) owner = curNpcRoom->GetOwnerNpc();
			}
		}
	}
	return owner;
}

int oCPortalRoomManager :: GetCurNpcPortalRoomGuild( oCNpc* npc )
{
	int guild = -1;
	
	if (npc)
	{
		zSTRING* curNpcPortal = (zSTRING*)npc->GetSectorNameVobIsIn();
		if (curNpcPortal)
		{
			int index = GetPortalRoomIndex(*curNpcPortal);
			if (index >= 0)
			{
				oCPortalRoom* curNpcRoom = portals[index];
				if (curNpcRoom) guild = curNpcRoom->GetOwnerGuild();
			}
		}
	}
	return guild;
}

void oCPortalRoomManager :: ShowDebugInfo()
{
	int y = 0;
	zSTRING s = "CurPortal : ";
	if (curPlayerRoom) {
		s += curPlayerRoom->GetPortalName();
		if (curPlayerRoom->GetOwnerNpc()) {
			s += "("+curPlayerRoom->GetOwnerNpc()->GetInstanceName()+")";
		}
		if (curPlayerRoom->GetOwnerGuild()>0) {
			s += "/Guild:" +zSTRING(curPlayerRoom->GetOwnerGuild()) + "  " + ogame->GetGuilds()->GetGuildName(curPlayerRoom->GetOwnerGuild())+"/";				
		}
	}
	screen->Print(0,y,s);
	y+=screen->FontY();

	s = "FormerPortal : ";
	if (oldPlayerRoom) {
		s += oldPlayerRoom->GetPortalName();
		if (oldPlayerRoom->GetOwnerNpc()) {
			s += "("+oldPlayerRoom->GetOwnerNpc()->GetInstanceName()+")";
		}
		if (oldPlayerRoom->GetOwnerGuild()>0) {
			s += "/Guild: " + zSTRING(oldPlayerRoom->GetOwnerGuild()) + "  " + ogame->GetGuilds()->GetGuildName(oldPlayerRoom->GetOwnerGuild())+"/";				
		}
	}
	screen->Print(0,y,s);
};

void oCPortalRoomManager :: ShowPortalInfo()
{	
	zSTRING name;

	zerr.Separator();
	zERR_MESSAGE	(0,0,"U: PRT: PortalList");
	zerr.Separator();
	for (int i = 0; i < portals.GetNumInList(); i++) {
		
		name = portals[i]->GetPortalName();
		zERR_MESSAGE(0,0,"U: PRT: - "+name);

	}
	zerr.Separator();
	name.Clear();
	if (oldPlayerPortal) name = *oldPlayerPortal;
	zERR_MESSAGE	(0,0,"U: PRT: Player was in Portal: "+name);
	
	name.Clear();
	if (curPlayerPortal) name = *curPlayerPortal;
	zERR_MESSAGE	(0,0,"U: PRT: Player in in Portal: "+name);
	
	zerr.Separator();
}

void oCPortalRoomManager :: SavePortalData(zCArchiver& arc)
{
	int num = portals.GetNumInList();
	arc.WriteInt("numPortals",num);

	for (int i=0; i<portals.GetNumInList(); i++) {
		portals[i]->SavePortalData(arc);
	}
};

void oCPortalRoomManager :: LoadPortalData(zCArchiver& arc)
{
	oldPlayerPortal = NULL;
	oldPlayerRoom	= NULL;
	curPlayerPortal = NULL;
	curPlayerRoom	= NULL;
	int i = 0, c = portals.GetNumInList();
	while (i<c) {
		delete (portals[i]);
		i++;
	}
	portals.EmptyList();

	int num;
	arc.ReadInt("numPortals",num);

	oCPortalRoom* room = NULL;
	for (i=0; i<num; i++) {
		room = zNEW(oCPortalRoom());
		room->LoadPortalData(arc);
		portals.InsertSort(room);
	}
};





