/******************************************************************************** 
 
     $Workfile:: zworldinfo.cpp       $                $Date:: 28.08.00 14:24   $
     $Revision:: 8                    $             $Modtime:: 24.08.00 12:09   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:

 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 8 $ ($Modtime: 24.08.00 12:09 $)

#include "zcore.h"

// Network
#include "zworldinfo.h"
#include "zworld.h"
#include "zplayergroup.h"

///////////////////////////////////////////////////////////////////////////
/////
///
// zCWorldInfo
///
/////
///////////////////////////////////////////////////////////////////////////


zCWorldInfo::zCWorldInfo(const zSTRING& _name)
{
	name				= _name;
	playerGroup_Level	= zNEW(zCPlayerGroup("World_"+_name));
	isRunning = FALSE;
};



zCWorldInfo::~zCWorldInfo()
{	
	delete playerGroup_Level; playerGroup_Level = NULL;
	historyList.DeleteList();
	name.Clear();
};

zSTRING	zCWorldInfo::GetName() 
{ 
	return name; 
};

zCPlayerGroup* zCWorldInfo::GetPlayerGroup()	
{ 
	return playerGroup_Level; 
};

zBOOL zCWorldInfo::IsMember(zCPlayerInfo* levelMaster) 
{ 
	return playerGroup_Level->IsMember(levelMaster); 
};


zCPlayerInfo* zCWorldInfo::GetLevelMaster()
{
	zCPlayerInfo* masterPlayer = 0;

	// Suche den ersten Spieler im Level
	int iter;
	masterPlayer = playerGroup_Level->GetFirstPlayer(iter);
	
	if (!masterPlayer)
	{
		if (historyList.GetNumInList()>0)
		{
			// kein Spieler im Level: dann nimm den ersten aus der history-list
			masterPlayer = historyList.Get(0);
		}
		else 
		{
			// neuer Level ohne History: 0; den Gamemaster liefern?
			masterPlayer = 0;
		};
	}
	
	return masterPlayer;
};


///
// Ein Spieler betritt die Welt
// Er wird aus der History entfernt und als Spieler in der Welt registriert
///
void zCWorldInfo::EnterWorld(zCPlayerInfo* player)
{
	zERR_ASSERT(player);
	#ifdef _DEBUG		
		if (playerGroup_Level->IsMember(player))	zERR_FATAL("B: (netCWorldInfo::EnterLevel) player is already member of world "+name);
		if (this == player->GetWorldInfo())			zERR_FATAL("B: (netCWorldInfo::EnterLevel) player is already member of world "+name+" (equal worldinfos)");
	#endif
			
	// Spieler aus der World-History entfernen
	if (historyList.IsInList(player)) historyList.Remove(player);
	
	// Spieler in die Welt-Gruppe eintragen
	playerGroup_Level->AddPlayer(player);	

	player->SetWorldInfo(this);
	ShowDebugInfo();
};

///
// Ein Spieler verlaesst die Welt
///
void zCWorldInfo::LeaveWorld(zCPlayerInfo* player)
{
	zERR_ASSERT(player);
	#ifdef _DEBUG		
		if (!playerGroup_Level->IsMember(player))	zERR_FATAL("B: (netCWorldInfo::LeaveLevel) player is not member of world "+name);
		if (this != player->GetWorldInfo())			zERR_FATAL("B: (netCWorldInfo::LeaveLevel) player is not member of world "+name+" (unequal worldinfos)");
	#endif
	
	// Den Spieler in die History eintragen
	if (!historyList.IsInList(player)) historyList.InsertFront(player);		
	
	// Den Spieler aus der Welt-Gruppe entfernen
	playerGroup_Level->RemPlayer(player);	
	
	player->SetWorldInfo(0);
	ShowDebugInfo();
};

void zCWorldInfo::ShowDebugInfo()
{
	zerr.Separator();
	zERR_MESSAGE(1, 0, "B: LEVEL: "+GetName());		
	GetPlayerGroup()->ShowDebugInfo();	
	int count = historyList.GetNumInList();	

	zERR_MESSAGE(1, 0, "B:   History-List");
	zCPlayerInfo* player;
	for (int i=0;i<count;i++)
	{		
		player = historyList.Get(i);				
		zERR_MESSAGE(1, 0, "B:   ... Player: \""+player->GetName()+"\" id="+zSTRING(player->GetID()));
	};
	zerr.Separator();
};

