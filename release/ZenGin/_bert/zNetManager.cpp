/******************************************************************************** 
 
     $Workfile:: znetmanager.cpp      $                $Date:: 21.09.00 2:35    $
     $Revision:: 10                   $             $Modtime:: 21.09.00 2:35    $
       $Author:: Rueve                                                          $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Bert/znetmanager.cpp $
 * 
 * 10    21.09.00 2:35 Rueve
 * 
 * 9     21.09.00 0:11 Rueve
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
 * 3     4.12.99 20:49 Speckels
 * more implementation of the central networkmanager
 * 
 * 2     22.10.99 12:52 Speckels
 * Neue Klasse Netzwerk-Manager
 * 
 * 1     19.10.99 17:53 Speckels
 * 
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Rueve $
/// @version $Revision: 10 $ ($Modtime: 21.09.00 2:35 $)


#include "znetmanager.h"
#include "znet.h"
#include "zobject.h"
#include "zview.h"
#include "zworld.h"

// message-handlers
#include "zneteventman.h"
#include "znetvobcontrol.h"


zCLASS_DEFINITION ( zCNetManager, zCObject	, 0, 0)

////////////////////////////////////////////////////////////////////////
///
// zCNetManager
///
////////////////////////////////////////////////////////////////////////


// Nachrichten-IDs
const int NETID_PING			= 1;
const int NETID_WORLDTIME		= 2;


// Macros
#define zNET_MSG_CLASSID(id)					zWORD( ( (zDWORD(id) >> 16) & 0xFFFF ) - 1 )
#define zNET_MSG_MESSAGEID(id)					zWORD( ( (zDWORD(id)      ) & 0xFFFF ) - 1 )
#define zNET_MSG_IDENTIFIER(classid, msgid)		\
						( ( ( (zDWORD(classid) + 1) & 0xFFFF) << 16) + ( (zDWORD(msgid) + 1) & 0xFFFF) )


// Konstanten
const zDWORD zNET_TIMER_PING		= 5000;
const zDWORD zNET_TIMER_WORLDTIME	= 6000;
const zDWORD zNET_NUM_PINGTIMEOUT	= 3;



////////////////////////////////////////////////////////////////////////////////////////////
// Standard-Kopf f¸r netzwerk-relevante Klassen
////////////////////////////////////////////////////////////////////////////////////////////

enum // grob sortiert nach H‰ufigkeit
{
	/**/NETID_PING_REQ,
	/**/NETID_PING_REP,
	
	NETID_MAX
};

////////////////////////////////////////////////////////////////////////////////////////////

static char* NETMSG_NAME[NETID_MAX]
= 
{
	"NETID_EM_TRIGGER",
	"NETID_PING_REP"
};

////////////////////////////////////////////////////////////////////////////////////////////

#define NETMSG_PRIO(id)		10;



////////////////////////////////////////////////////////////////////////////////////////////


zBOOL zCNetManager::Temp_HandleNetMessage(zCNetMessage*& msg, zCWorld* world)
{
	zWORD classID	= zNET_MSG_CLASSID		(msg->GetID());
	zWORD messageID	= zNET_MSG_MESSAGEID	(msg->GetID());			
	zCClassDef* classDef = zCClassDef::GetClassDefByID(classID);
	zBOOL result = HandleNetMessage(msg,messageID, classDef, world);	
	delete msg;
	msg=0;
	return result;
};


zCNetManager::zCNetManager()
{
	timer.ResetTimer();
	timer_count_ping		= 0;
	timer_count_worldtime	= 0;
};

zCNetManager::~zCNetManager()
{
};



void zCNetManager::Process()
// Diese Methode wird regelm‰ﬂig aufgerufen
// Hier werden dann Timerfunktionen und angekommene Nachrichten bearbeitet 
{	
	// timer
	zDWORD timerFrameTime = timer.GetFrameTime();
	timer_count_ping	  += timerFrameTime;	
	timer_count_worldtime += timerFrameTime;

	// do timer-actions
	if (timer_count_ping>zNET_TIMER_PING) 
	{
		SendPing();
		timer_count_ping=0;
	};
	if (timer_count_worldtime>zNET_TIMER_WORLDTIME)
	{
		SendWorldTime();
		timer_count_worldtime=0;
	};

	ProcessMessages();	
};




void zCNetManager::ProcessMessages()
// In dieser Methode werden die eingetroffenen Netzwerknachrichten 
// "abgeholt" und analysiert. Aus der NachrichtenID werden die 
// MessageID sowie die classID ermittelt. Mit letzterer kann 
// der Bearbeitungsmethode die ClassDefinition ¸bergeben werden.
{
	zCNetMessage* msg;
	znet->Handle();
	do
	{
		znet->MsgGet(msg,0);

		// Nachricht bearbeiten:
		if (msg) 
		{
			zWORD classID	= zNET_MSG_CLASSID		(msg->GetID());
			zWORD messageID	= zNET_MSG_MESSAGEID	(msg->GetID());			

			zCClassDef* classDef = zCClassDef::GetClassDefByID(classID);
			HandleNetMessage(msg,messageID, classDef);
			delete msg;
			msg=0;
		}
	}
	while (msg!=NULL);
};


zBOOL zCNetManager::HandleNetMessage(zCNetMessage* msg, const zTNetMessageSubID& messageID, zCClassDef* classDef, zCWorld* world)
// Diese Methode nimmt eine Nachricht entgegen und verteilt sie gem‰ﬂ der 
// ClassDefinition an die entsprechende Methode zur Bearbeitung der Nachricht
{
	if (classDef == this->GetStaticClassDef())
	{
		zCPlayerInfo* sender = zCPlayerGroup::GetAllPlayerGroup()->GetPlayerByID(msg->GetSenderID());
		switch (messageID)
		{
		case NETID_PING_REQ:	SendPingReply(sender);break;
		case NETID_PING_REP:	sender->zCPlayerInfo::SetPingEnd();break;
		}
	}
	else 
	if (classDef == zCNetEventManager::GetStaticClassDef())
	{
		return zCNetEventManager::HandleNetMessage(msg,messageID, world);		
	}	
	else
	if (classDef == zCNetVobControl::GetStaticClassDef())
	{
		return zCNetVobControl::HandleNetMessage(msg, messageID, world);
	};
	return FALSE;
};


zCNetMessage* zCNetManager::CreateNetMessage(const zTNetMessageSubID& messageID, zCObject* obj)
// Diese Methode nimmt eine Nachricht entgegen und verteilt sie gem‰ﬂ der 
// ClassDefinition an die entsprechende Methode zur Bearbeitung der Nachricht
{	
	zCNetMessage* msg = zNEW(zCNetMessage)
		( 
			zNET_MSG_IDENTIFIER( obj->GetClassDef()->GetClassID() , messageID ) 
		);
	return msg;
};






void zCNetManager::SendPing()
// Jeder Spieler sendet seinen Mitspielern 
// eine Ping-Nachricht. Dadurch kˆnnen die Spieler erkennen, ob 
// ein Spieler das Spiel unangemeldet verlassen hat oder seine 
// Internetverbindung beendet wurde.
{	
	if (!zCPlayerInfo::GetActivePlayer()) return;
	
	int iter;
	zCPlayerGroup* group = zCPlayerGroup::GetAllPlayerGroup();
	zCPlayerInfo* target= group->GetFirstPlayer(iter);
	while (target)
	{	
		// Sende Ping-Request
		zCNetMessagePtr msg = CreateNetMessage(NETID_PING_REQ, this);
		msg->SetTarget(target);
		msg->Send();
		target->SetPingStart();
		
		target = group->GetNextPlayer(iter);
	}
};

void zCNetManager::SendPingReply(zCPlayerInfo* target)
{	
	if (!target) return;

	// Sende Ping-Request
	zCNetMessagePtr msg = CreateNetMessage(NETID_PING_REP, this);
	msg->SetTarget(target);
	msg->Send();		
};



void zCNetManager::SendWorldTime()
// Der Hauptrechner im Netzwerk schickt allen Mitspieler in einem
// regelm‰ﬂigen Intervall die aktuelle Spielzeit. 
{

};





zCNetManager* znetman=0;

