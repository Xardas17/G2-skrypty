/******************************************************************************** 
 
     $Workfile:: znetvobcontrol.cpp          $         $Date:: 21.09.00 0:11    $
     $Revision:: 9                           $      $Modtime:: 21.09.00 0:10    $
       $Author:: Rueve                                                          $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   vob-controller
  
 * $Log: /current_work/ZenGin/_Bert/znetvobcontrol.cpp $
 * 
 * 9     21.09.00 0:11 Rueve
 * 
 * 8     28.08.00 14:24 Speckels
 * 
 * 15    23.08.00 21:47 Admin
 * 
 * 6     21.08.00 18:47 Speckels
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
 * 1     18.01.00 20:38 Speckels
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Rueve $
/// @version $Revision: 9 $ ($Modtime: 21.09.00 0:10 $)

#include "zcore.h"

#include "znetvobcontrol.h"
#include "znetmanager.h"
#include "zplayerinfo.h"
#include "zplayergroup.h"
#include "zarchiver.h"
#include "zeventman.h"
#include "zworld.h"

zCLASS_DEFINITION( zCNetVobControl, zCObject, 0, 0)


////////////////////////////////////////////////////////////////////////////////////////////
// Standard-Kopf für netzwerk-relevante Klassen
////////////////////////////////////////////////////////////////////////////////////////////

enum // grob sortiert nach Häufigkeit
{
	/**/NETID_HANDOVER, 

	NETID_MAX

};

////////////////////////////////////////////////////////////////////////////////////////////

static char* NETMSG_NAME[NETID_MAX]
= 
{
	"NETID_HANDOVER"	
};

////////////////////////////////////////////////////////////////////////////////////////////

#define NETMSG_PRIO(id) 	7


////////////////////////////////////////////////////////////////////////////////////////////


///
// construction and destruction
///

zCNetVobControl::zCNetVobControl()
{
	Init(NULL);
};

zCNetVobControl::~zCNetVobControl()
{
	hostVob			= NULL;
	ctrlPlayer		= NULL;
};

void zCNetVobControl::Init(zCVob* vob)
{	
	hostVob			= vob;
	ctrlPlayer		= NULL;
	isLocalChained	= FALSE;
};

///
// controling-methods
///





// Hier faellt die Entscheidung, ob der vob an einen anderen Spieler
// abgegeben werden soll. Diese Methode darf nur von dem kontrollierenden
// Spieler aufgerufen werden.


zBOOL zCNetVobControl::Process()
{
	zERR_ASSERTT(hostVob,"B: VOBCTRL: You must call zCNetVobControl::Init(zCVob* vob) first.");	

	// Ist der Vob vielleicht gerade angekettet? Dann darf wer nicht abgegeben werden!
	if (isLocalChained) return FALSE;

	// Ein Vob ohne Welt wird auch nicht freiwillig abgegeben.	
	if (!hostVob->GetHomeWorld()) return FALSE;	

	// Einfacher Algorithmus: Ermittle den nächstgelegenen Spieler und uebergib ihm die Kontrolle	
	
	zCPlayerInfo*	nearestPlayer	= ctrlPlayer;
	zCVob*			ctrlVob			= nearestPlayer	-> GetPlayerVob();	
	zVALUE			ctrlDist		= ctrlVob		-> GetDistanceToVob2(*hostVob);	
	// Innerhalb der Tolleranzweite wird jede Kontrollübergabe verhindert
	if (ctrlDist<=zNET_VOBCTRL_TOLERANCE) return FALSE;
	
	ctrlDist -= zNET_VOBCTRL_TOLERANCE;
	
	// Nächstgelegenen Spieler ermitteln
	int				iter;
	zVALUE			distance;
	zCVob*			vob;
	zCPlayerGroup*	group	=	hostVob->GetHomeWorld()->GetPlayerGroup();
	zCPlayerInfo*	player	=	group->GetFirstPlayer(iter);	
	while (player)
	{
		if (player != nearestPlayer)	// der nearestPlayer braucht nicht untersucht werden
		{
			vob = player->GetPlayerVob();
			distance = vob->GetDistanceToVob2(*hostVob);
			if (distance < ctrlDist)	// Distanz ist kleiner: neuer nearestPlayer
			{ 
				nearestPlayer = player;
				ctrlDist = distance; 
			};
		}
		player = group->GetNextPlayer(iter);
	};
	
	// einen Spieler gefunden, der dem Vob näher ist?
	if (nearestPlayer != ctrlPlayer)
	{
		HandOverToPlayer(nearestPlayer);
		return TRUE;
	}

	return FALSE;
};

zBOOL zCNetVobControl::HandOverToPlayer(zCPlayerInfo* newCtrlPlayer)
{
	zERR_MESSAGE(9,0,"B: VOBCTRL: Send HANDOVER for "+zNET_VOB_DESCRIPTION(hostVob)+" to "+newCtrlPlayer->GetName());

	SetCtrlPlayer(newCtrlPlayer);	
	
	zBYTE playerID = (newCtrlPlayer) ? newCtrlPlayer->GetID() : 0;

	zCNetMessage* msg = CreateNetMessage(NETID_HANDOVER);
	msg->Add(&playerID, sizeof(playerID));
	msg->Send();

	return TRUE;
};

///
// network-methods
///


zBOOL zCNetVobControl::HandleNetMessage(zCNetMessage* msg, const zTNetMessageSubID& messageID, zCWorld* world)
{
	// Vob ermitteln
	zCVob*	vob;
	zTVobID	vobID;
	
	msg->Get(&vobID,sizeof(vobID));
	vob = world->SearchVobByID(vobID);
	
	if (!vob)
	{
		zERR_WARNING("B: VOBCTRL: Could not find vob for network-message "+zSTRING(NETMSG_NAME[messageID]));
		return FALSE;
	};
	
	// Sender ermitteln
	zBYTE			senderID	= msg->GetSenderID();
	zCPlayerInfo*	sender		= zCPlayerGroup::GetAllPlayerGroup()->GetPlayerByID(senderID);
	zERR_ASSERT(sender);

	// Nachricht kann bearbeitet werden
	switch (messageID)
	{
	
	case NETID_HANDOVER:
		{			
			zERR_MESSAGE(9,0,"B: VOBCTRL: Recv HANDOVER for "+zNET_VOB_DESCRIPTION(vob)+" from "+sender->GetName());
			// ctrlPlayer ermitteln
			zBYTE ctrlPlayerID;
			msg->Get(&ctrlPlayerID,sizeof(ctrlPlayerID));			
			zCPlayerInfo* ctrlPlayer = zCPlayerGroup::GetAllPlayerGroup()->GetPlayerByID(ctrlPlayerID);

			// changing control-state ofg the vob
			vob->GetEventManager()->GetNetVobControl()->SetCtrlPlayer(ctrlPlayer);
		}
		break;
	};
	return FALSE;
};

zCNetMessage* zCNetVobControl::CreateNetMessage(const zTNetMessageSubID& messageID)
{
	zERR_ASSERTT(hostVob,"B: VOBCTRL: You must call zCNetVobControl::Init(zCVob* vob) first.");
	zERR_MESSAGE(NETMSG_PRIO(messageID),0,"B: VOBCTRL: "+zNET_VOB_DESCRIPTION(hostVob)+" creates network-message "+NETMSG_NAME[messageID]);

	zCNetMessage* netmsg = znetman->CreateNetMessage(messageID, this);
	netmsg->SetTarget(zCPlayerGroup::GetAllPlayerGroup());	// Besser: an alle Spieler, die sich in der selben Welt befinden!
	zTVobID id = hostVob->GetVobID();
	netmsg->Add(&id,sizeof(id));
	return netmsg;
};

void zCNetVobControl::SetCtrlPlayer(zCPlayerInfo* pinfo)
{
	zERR_MESSAGE(9,0,"B: VOBCTRL: Setting controlling player of vob "+zNET_VOB_DESCRIPTION(hostVob)+" to player "+pinfo->GetName());	
	
	ctrlPlayer = pinfo;	
};

zBOOL zCNetVobControl::IsLocalControlled()
{
	if (!ctrlPlayer) return FALSE;	// TODO
	return ctrlPlayer->IsActive();
};


zBOOL zCNetVobControl::IsPlayerVob()
{
	return FALSE;

	if (!ctrlPlayer) return FALSE;	// TODO
	return (ctrlPlayer->GetPlayerVob() == hostVob);
};

void zCNetVobControl::CopyCtrlState(zCVob* vob)
{
	if (!vob) return;
	SetCtrlPlayer(vob->GetEM()->GetNetVobControl()->GetCtrlPlayer());
};


///
// archiving
///

void zCNetVobControl::Archive(zCArchiver &arc)
{
	if (!hostVob) zERR_WARNING("B: VOBCTRL: You must call zCNetVobControl::Init(zCVob* vob) first.");
	zCObject::Archive(arc);	
};

void zCNetVobControl::Unarchive(zCArchiver &arc)
{	
	zCObject::Unarchive(arc);	
	
};
