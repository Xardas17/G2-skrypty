/******************************************************************************** 
 
     $Workfile:: znetEventMan.cpp     $                $Date:: 21.09.00 0:11    $
     $Revision:: 8                    $             $Modtime:: 21.09.00 0:11    $
       $Author:: Rueve                                                          $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Network-handling event-manager. 

 * $Log: /current_work/ZenGin/_Bert/znetEventMan.cpp $
 * 
 * 8     21.09.00 0:11 Rueve
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
 * 8     7.02.00 17:57 Speckels
 * Update for Engine 0.86
 * 
 * 6     4.12.99 20:49 Speckels
 * more implementation of the central networkmanager
 * 
 * 4     16.11.99 11:42 Speckels
 * Item/MOB-Interaktion, Pre-Release Netzwerk
 * 
 * 3     21.10.99 23:29 Speckels
 * Work on error-handling and item-interaction
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Rueve $
/// @version $Revision: 8 $ ($Modtime: 21.09.00 0:11 $)
//
// TODO:
// - Shortcuts in Eventmessages umwandeln
// 
//
//

#include "znet.h"
#include "znetmanager.h"
#include "znetEventMan.h"
#include "znetmessage.h"
#include "znetvobcontrol.h"
#include "zworld.h"
#include "zworldinfo.h"



zCLASS_DEFINITION ( zCNetEventManager, zCEventManager	, 0, 0)


////////////////////////////////////////////////////////////////////////////////////////////
// Standard-Kopf für netzwerk-relevante Klassen
////////////////////////////////////////////////////////////////////////////////////////////

enum // grob sortiert nach Häufigkeit
{
	/**/NETID_EM,			// "Hier ist meine EventMessage von vob1 an vob2"
	/**/NETID_EM_REQ,		// "Mmmh, kannst Du diese EventMessage bitte an alle weiterleiten?"
	/**/NETID_EMCTRL_REQ,	// "So, jetzt will ich eine EventMessage von diesem unkontrollierten Vob abschicken. Kuemmerst Du Dich drum?"

	NETID_MAX
};

////////////////////////////////////////////////////////////////////////////////////////////

static char* NETMSG_NAME[NETID_MAX]
= 
{
	"NETID_EM",
	"NETID_EM_REQ",
	"NETID_EMCTRL_REQ"	
};

////////////////////////////////////////////////////////////////////////////////////////////

#define NETMSG_PRIO(id) 	(9)
		



////////////////////////////////////////////////////////////////////////////////////////////


zBOOL zCNetEventManager::HandleNetMessage(zCNetMessage* msg, zTNetMessageSubID messageID, zCWorld* world)
{			
	zTVobID				hostVobID	= 0;	
	zTVobID				otherVobID	= 0;
	zCVob*				otherVob	= 0;			
	
	// hostVob ermitteln (Ziel der EvMsg)
	msg->Get(&hostVobID,sizeof(hostVobID));		
	zCVob* hostVob = world->SearchVobByID(hostVobID);
	zERR_ASSERT_STRICT(hostVob);

	// otherVob ermitteln (Quelle der EvMsg)
	msg->Get(&otherVobID,sizeof(otherVobID));								
	otherVob = (otherVobID!=0) ? world->SearchVobByID(otherVobID) : 0;			
	zERR_ASSERT_STRICT(otherVob);

	// EventHandler von beiden Vobs ermitteln 
	zCNetEventManager*	otherEM	= dynamic_cast<zCNetEventManager*>(otherVob->GetEventManager(TRUE));	// nicht automatisch erzeugen
	zCNetEventManager*	hostEM	= dynamic_cast<zCNetEventManager*>(hostVob->GetEventManager(FALSE));		// automatisch erzeugen, falls noch nicht vorhanden
	zERR_ASSERT_STRICT(hostEM);

	// VobControl von beiden Vobs ermitteln
	zCNetVobControl*	otherCtrl= 0;
	if (hostEM)			otherCtrl= otherEM->GetNetVobControl(TRUE);	// nicht automatisch erzeugen
	// zCNetVobControl*	hostCtrl = hostEM->GetNetVobControl(TRUE);	// nicht automatisch erzeugen
	// zERR_ASSERT_STRICT(hostCtrl);

	zCEventMessage*	event = zCEventMessage::CreateFromBuffer(*msg->GetBuffer(),hostEM);
	zERR_MESSAGE(9,0,"B: EM: recved EM: "+event->MD_GetSubTypeString(event->GetSubType())+"("+zSTRING(event->IsNetRelevant())+"): "+zNET_VOB_DESCRIPTION(otherVob)+" -> "+zNET_VOB_DESCRIPTION(hostVob));

	zCPlayerInfo* sender = zCPlayerGroup::GetAllPlayerGroup()->GetPlayerByID(msg->GetSenderID());				

	switch (messageID)
	{

		// Event-Nachricht
		case NETID_EM:
			{																
				#ifdef _DEBUG
					zERR_MESSAGE(9, 0, "B: EM: ... EM from "+sender->GetName());
				#endif
				
				// Ok, die Nachricht ausführen
				hostEM->zCEventManager::OnMessage(event, otherVob);

				return TRUE;
			}
			break;
			
		// Request für eine Event-Nachricht von einem unkontrollierten vob
		case NETID_EMCTRL_REQ:
			{				
				#ifdef _DEBUG
					zERR_MESSAGE(9, 0, "B: EM: ... EMCTRL_REQ from "+sender->GetName());
				#endif

				// Nur erlauben, wenn der otherVob noch nicht kontrolliert wird
				if (otherCtrl)
				{
					#ifdef _DEBUG
						if (!otherCtrl->GetCtrlPlayer())
						{
							zERR_WARNING("B: EM: ...... VobCtrl exists but no CtrlPlayer is set!");
						};				
						if (otherCtrl->GetCtrlPlayer() == sender)
						{
							zERR_WARNING("B: EM: ...... VobCtrl exists and CtrlPlayer equals the Sender!");
						};
					#endif				
					
					break;	// Der Request wird ignoriert
				}
				
				// Der Request wird akzeptiert: Dem Sender die Kontrolle über otherVob geben
				otherCtrl = otherEM->GetNetVobControl(FALSE);
				otherCtrl->HandOverToPlayer(sender);

				zERR_MESSAGE(9, 0, "B: EM: ... Send EM");
				
				// Nachricht an alle anderen Mitspieler: NETID_EM
				zCNetMessage* _msg = znetman->CreateNetMessage(NETID_EM, hostEM);
					_msg -> CopyFrom(msg);				
					_msg -> SetTarget(sender->GetWorldInfo()->GetPlayerGroup());
					_msg -> Send();	
					
				// Ok, und die EvMsg selber ausführen
				hostEM->zCEventManager::OnMessage(event, otherVob);
			}
			break;

		// Request für eine Event-Nachricht: Einfach an alle anderen weiterleiten
		case NETID_EM_REQ:
			{								
				#ifdef _DEBUG					
					zERR_MESSAGE(9, 0, "B: EM: ... EM_REQ from "+sender->GetName());
				#endif

				zERR_MESSAGE(9, 0, "B: EM: ... Send EM");
				// Nachricht an alle anderen Mitspieler: NETID_EM
				zCNetMessage* _msg = znetman->CreateNetMessage(NETID_EM, hostEM);
					_msg -> CopyFrom(msg);
					_msg -> SetTarget(sender->GetWorldInfo()->GetPlayerGroup());
					_msg -> Send();	
				
				// Ok, und die EvMsg selber ausführen
				hostEM->zCEventManager::OnMessage(event, otherVob);

				return TRUE;
			}
			break;
	};

	return FALSE;
};

////////////////////////////////////////////////////////////////////////////////////////////
// Ende des Netzwerk-Kopfes
////////////////////////////////////////////////////////////////////////////////////////////



zCNetEventManager::zCNetEventManager()
{	
	Init();
};

zCNetEventManager::zCNetEventManager(zCVob* hostVob) : zCEventManager(hostVob)
{		
	Init();
};

zCNetEventManager::~zCNetEventManager() 
{	
};

void zCNetEventManager::Init()
{
	netVobCtrl=NULL;
};


void zCNetEventManager::OnMessage (zCEventMessage *eventMessage, zCVob* otherVob)
{					
	zERR_MESSAGE(9,0,"B: EM: "+eventMessage->MD_GetSubTypeString(eventMessage->GetSubType())+"("+zSTRING(eventMessage->IsNetRelevant())+"): "+zNET_VOB_DESCRIPTION(otherVob)+" -> "+zNET_VOB_DESCRIPTION(hostVob));

 	if (!eventMessage->IsNetRelevant()) 
	// Wenn die nicht Event-Nachricht netzwerk-relevant ist, dann nur Basismethode aufrufen
	{
		zCEventManager::OnMessage(eventMessage, otherVob);
		return;
	};
	// Testing ... one two ...
	if (!otherVob)
	{
		zERR_WARNING("B: EM: otherVob is NULL: "+eventMessage->MD_GetSubTypeString(eventMessage->GetSubType()));
		zCEventManager::OnMessage(eventMessage, otherVob);
		return;
	}
	
	zERR_ASSERTT(otherVob,"B: EM: otherVob not defined");
	zTVobID otherID		= otherVob->GetVobID();
	zTVobID hostID		= GetHostVob()->GetVobID();
	if ((otherID<=0) || (hostID<=0)) { zERR_WARNING( "B: EM: Eventmessage will not be sent cause of a not net-relevant vob");return; }		
	
	zCNetMessage*		msg = 0;	
	zCPlayerInfo*		selfplayer = zCPlayerInfo::GetActivePlayer();
	zCPlayerInfo*		levelMaster = selfplayer->GetWorldInfo()->GetLevelMaster();
	zCPlayerGroup*		levelGroup	= selfplayer->GetWorldInfo()->GetPlayerGroup();
	zCNetEventManager*	otherEM	= dynamic_cast<zCNetEventManager*>(otherVob->GetEventManager(TRUE));	// nicht automatisch erzeugen	
	
	// VobControl von beiden Vobs ermitteln
	zCNetVobControl*	otherCtrl= 0;	
	if (otherEM)		otherCtrl= otherEM->GetNetVobControl(TRUE);	// nicht automatisch erzeugen
	zCNetVobControl*	hostCtrl = GetNetVobControl(TRUE);			// nicht automatisch erzeugen	
	if (otherCtrl && !otherCtrl->GetCtrlPlayer()) 
		zERR_WARNING("B: EM: VobCtrl of otherVob "+zNET_VOB_DESCRIPTION(otherVob)+" exists but no CtrlPlayer is defined"); 
	if (hostCtrl && !hostCtrl->GetCtrlPlayer()) 
		zERR_WARNING("B: EM: VobCtrl of hostVob "+zNET_VOB_DESCRIPTION(hostVob)+" exists but no CtrlPlayer is defined"); 
	

	// ABBRUCH, wenn otherVob von jemand anderem kontrolliert wird
	if (otherCtrl && otherCtrl->GetCtrlPlayer() && !otherCtrl->IsLocalControlled())
	{
		return;
	};
		
	// EMCTRL_REQ senden, wenn otherVob noch nicht kontrolliert wird
	if (!otherCtrl || !otherCtrl->GetCtrlPlayer())
	{
		zERR_MESSAGE(9,0,"B: EM: ... Send EM (CTRL_REQ) to levelmaster "+levelMaster->GetName());

		msg = znetman->CreateNetMessage(NETID_EMCTRL_REQ,this);
			msg				->SetTarget(levelMaster);// Levelmaster
			msg				->Add(&hostID,sizeof(hostID));
			msg				->Add(&otherID,sizeof(otherID));
			eventMessage	->PackToBuffer(*msg->GetBuffer(),this);		
			msg				->Send();	

		return;
	};

	// EM_REQ senden, wenn hostVob nicht von selfplayer kontrolliert wird
	if (!hostCtrl || !hostCtrl->IsLocalControlled())
	{		
		
		msg = znetman->CreateNetMessage(NETID_EM_REQ,this);		
			if (hostCtrl && hostCtrl->GetCtrlPlayer()) {
				msg->SetTarget(hostCtrl->GetCtrlPlayer()); // CtrlPlayer
				zERR_MESSAGE(9,0,"B: EM: ... Send EM (EM_REQ) to "+hostCtrl->GetCtrlPlayer()->GetName());
			} else {
				msg->SetTarget(levelMaster);	// Levelmaster
				zERR_MESSAGE(9,0,"B: EM: ... Send EM (EM_REQ) to levelmaster "+levelMaster->GetName());
			}
			msg				->Add(&hostID,sizeof(hostID));
			msg				->Add(&otherID,sizeof(otherID));
			eventMessage	->PackToBuffer(*msg->GetBuffer(),this);		
			msg				->Send();	

		return;
	};
			
	// EM senden, wenn hostVob und otherVob von selfplayer kontrolliert
	if (hostCtrl && otherCtrl && hostCtrl->IsLocalControlled() && otherCtrl->IsLocalControlled())
	{
		zERR_MESSAGE(9,0,"B: EM: ... Send EM to everybody in the same level.");
			
		msg = znetman->CreateNetMessage(NETID_EM,this);
			msg				->SetTarget(levelGroup);	// alle im Level
			msg				->Add(&hostID,sizeof(hostID));
			msg				->Add(&otherID,sizeof(otherID));
			eventMessage	->PackToBuffer(*msg->GetBuffer(),this);		
			msg				->Send();	

		zCEventManager::OnMessage(eventMessage,otherVob);

		return;
	};
	
	zERR_WARNING("B: EM: Undefined state of vobCtrl for "+zNET_VOB_DESCRIPTION(hostVob)+" or "+zNET_VOB_DESCRIPTION(otherVob));
};



  

// **************************************************************************************
// ShortCuts
// **************************************************************************************





void zCNetEventManager::Archive	(zCArchiver& arc)
{
	zCEventManager::Archive(arc);

	if (arc.InSaveGame())
	{
		arc.WriteObject(netVobCtrl);
	};
};




void zCNetEventManager::Unarchive	(zCArchiver& arc)
{
	zCEventManager::Unarchive(arc);

	if (arc.InSaveGame())
	{				
		// Erzeuge das Vob-Control-Objekt
		GetNetVobControl(FALSE);
		// Fuelle es mit Inhalt
		zCNetVobControl* vc = dynamic_cast<zCNetVobControl*>(arc.ReadObject(netVobCtrl));
		// Falls nciht vorhanden: wieder loeschen
		if (!vc) zRELEASE(netVobCtrl);
		netVobCtrl=vc;
	};
};


zCNetVobControl* zCNetEventManager::GetNetVobControl(zBOOL dontCreateIfNotPresent)
{ 	
	if (!netVobCtrl && !dontCreateIfNotPresent) 
	{		
		netVobCtrl = zfactory->CreateNetVobControl(hostVob);
		zERR_MESSAGE(9,0,"B: EM: VobController created for "+zNET_VOB_DESCRIPTION(GetHostVob()));
	}
	return netVobCtrl;
};

