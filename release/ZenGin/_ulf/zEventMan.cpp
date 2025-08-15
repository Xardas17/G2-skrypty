/******************************************************************************** 
 
     $Workfile:: zEventMan.cpp        $                $Date:: 16.02.01 14:23   $
     $Revision:: 33                   $             $Modtime:: 16.02.01 14:23   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zEventMan.cpp $
 * 
 * 33    16.02.01 14:23 Speckels
 * 
 * 32    26.01.01 18:30 Wohlers
 * 
 * 31    18.01.01 1:53 Speckels
 * 
 * 30    18.01.01 0:53 Speckels
 * 
 * 29    17.01.01 20:24 Speckels
 * 
 * 28    20.12.00 19:49 Hildebrandt
 * unnoetige include von o-Files entfernt
 * 
 * 27    20.12.00 0:03 Wohlers
 * 
 * 26    22.11.00 16:48 Wohlers
 * 
 * 25    16.11.00 14:08 Wohlers
 * 
 * 24    30.10.00 19:06 Moos
 * 
 * 23    26.10.00 17:57 Wohlers
 * 
 * 22    26.10.00 17:50 Wohlers
 * 
 * 21    26.10.00 17:33 Wohlers
 * 
 * 20    25.10.00 21:07 Speckels
 * 
 * 19    19.10.00 17:15 Keskenti
 * 
 * 18    17.10.00 19:34 Schrieber
 * 
 * 17    11.10.00 19:53 Keskenti
 * 
 * 16    21.09.00 19:01 Speckels
 * 
 * 15    19.09.00 20:57 Wohlers
 * 
 * 14    29.08.00 14:00 Wohlers
 * 
 * 13    21.08.00 14:24 Wohlers
 * 
 * 12    18.08.00 15:44 Wohlers
 * 
 * 11    10.08.00 18:37 Wohlers
 * 
 * 10    2.08.00 21:09 Wohlers
 * 
 * 9     31.07.00 22:04 Wohlers
 * 
 * 8     26.07.00 22:15 Wohlers
 * 
 * 7     21.07.00 15:35 Wohlers
 * 
 * 6     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 5     8.05.00 15:02 Wohlers
 * Waynet CheckConsistency
 * 
 * 4     7.05.00 22:08 Wohlers
 * SetCutsceneMode -> SetCutscene
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 13    30.03.00 20:36 Wohlers
 * Bugfixes ( Wegnetz, TAs etc. )
 * 
 * 12    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 11    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 10    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 9     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 7     11.01.00 22:59 Wohlers
 * CS-Fixes / NSC-Equip-Message
 * 
 * 6     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 5     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zEventMan.h"
#include "zCCSCutscene.h"
#include "zViewBase.h"
#include "zView.h"

// FIXME: VC++ specific, move to another file!
#include <CrtDbg.h>

#define zVOB_DESCRIPTION(vob) \
	( (vob) ? (vob)->GetClassDef()->GetClassName_()+":"+(vob)->GetVobName() : "NULL")

zCLASS_DEFINITION ( zCEventManager, zCObject	, 0, 0)

// ****************************************************************************************
// Event-Manager
// ****************************************************************************************

// *** Statics ***
zCArray<zCEventManager*>zCEventManager :: activeEM;
zBOOL					zCEventManager :: disableEventManagers	= FALSE;
zBOOL					zCEventManager :: showMsgCommunication	= FALSE;

void zCEventManager :: DoFrameActivity()
{
	if (disableEventManagers) return;

	zCEventManager* em = NULL; 

	for (int i=0; i<activeEM.GetNumInList(); i++) {
		
		em = activeEM[i];
		if (em) em->ProcessMessageList();
	
	}
}

// *** Con/Destruktor ***
zCEventManager::zCEventManager() 
{
	hostVob			= NULL;
	active			= FALSE;
	cleared			= FALSE;
	cutscene		= NULL;
	SetCutscene		( NULL );
};

zCEventManager::zCEventManager(zCVob* hostVob) 
{
	this->hostVob	= hostVob;
	active			= FALSE;
	cleared			= FALSE;
	cutscene		= NULL;
	SetCutscene		( NULL );
};

zCEventManager::~zCEventManager() 
{
	SetActive		( FALSE );
	zRELEASE		( cutscene );
	KillMessages	();

	hostVob			= NULL;
	cutscene		= NULL;
};

void zCEventManager :: KillMessages()
{
	// Messages aus Listen entfernen
	int c = messageList.GetNumInList()-1;
	for (int i = c; i>=0; i--) {
		zRELEASE(messageList[i]);
	}
	messageList.DeleteList();
};

void zCEventManager :: OnMessage (zCEventMessage *eventMessage, zCVob* sourceVob)	
{	
	zERR_ASSERT(eventMessage);
	zERR_ASSERT(hostVob);	

	zERR_MESSAGE(8,zERR_BEGIN,
			"U: EM: "
		+	zVOB_DESCRIPTION(sourceVob)
		+	" ---["+eventMessage->GetClassDef()->GetClassName_()+":"+eventMessage->MD_GetSubTypeString(eventMessage->GetSubType())+(eventMessage->IsJob()?"(Job)":"")+"]---> "
		+	zVOB_DESCRIPTION(hostVob)
	);
	
	if ( !hostVob->GetHomeWorld() && !GetCutscene() ) 	
	
		//
		// Ignorieren
		//
		{
            Delete(eventMessage); // [Moos] Leakfix
			zERR_MESSAGE(8,0,"U: EM: ... ignored: "+zVOB_DESCRIPTION(hostVob)+" is not in world");		
		}

	else

		//
		// Bearbeiten der Event-Nachricht
		//
		{					
			eventMessage->SetCutsceneMode(GetCutsceneMode());	// cutscene-mode setzen
					
			if	(
					!eventMessage->IsJob()							// ist ein Nicht-Job
				&&													// UND
					(		
							eventMessage->IsHighPriority()			// hat hoechste Prioritaet oder
						||	(messageList.GetNumInList()<=0)			// Liste ist leer oder
						||	dynamic_cast<zCEventCore*>(eventMessage)// eine Core-Message
					) 
				)

				//
				// sofort bearbeiten
				//
				{			
					SendMessageToHost	(eventMessage, hostVob, sourceVob);
					Delete				(eventMessage);							
				}

			else

				//
				// in die message-queue einfuegen
				//
				{
					InsertInList	(eventMessage);
					SetActive		(TRUE);
				}
		}

	zERR_MESSAGE(8,zERR_END,"");
};

void zCEventManager :: SendMessageToHost(zCEventMessage* eventMessage, zCVob* hostVob, zCVob* sourceVob)
{
	ShowMessageCommunication(sourceVob,hostVob);
	// Core Message ?
	zCEventCore* coreMsg = dynamic_cast<zCEventCore*>(eventMessage);
	if (coreMsg) {
		switch(coreMsg->GetSubType()) {
			case zCEventCore::zEVENT_TRIGGER	:	hostVob->OnTrigger		(sourceVob, coreMsg->GetVobInstigator());	break;
			case zCEventCore::zEVENT_UNTRIGGER	:	hostVob->OnUntrigger	(sourceVob, coreMsg->GetVobInstigator());	break;
			case zCEventCore::zEVENT_TOUCH		:	hostVob->OnTouch		(sourceVob);				break;
			case zCEventCore::zEVENT_UNTOUCH	:	hostVob->OnUntouch		(sourceVob);				break;
			case zCEventCore::zEVENT_TOUCHLEVEL	:	hostVob->OnTouchLevel	();							break;
			case zCEventCore::zEVENT_DAMAGE		:	hostVob->OnDamage		(coreMsg->GetOtherVob(),sourceVob,coreMsg->GetDamage(),coreMsg->GetDamageType(),coreMsg->GetHitLocation());		break;
			default								:	zERR_WARNING			("U:EVM: new CoreMessage not yet implemented !");	break;
		}
	} else {
		hostVob->OnMessage(eventMessage, sourceVob);
	}
}

void zCEventManager :: SetShowMessageCommunication(zBOOL show)
// STATIC 
{
	showMsgCommunication = show;
}

zBOOL zCEventManager :: GetShowMessageCommunication()
// STATIC 
{
	return showMsgCommunication;
}

void zCEventManager :: ShowMessageCommunication(zCVob* sourceVob, zCVob* targetVob)
{
	if (showMsgCommunication) {
		if (!sourceVob || !targetVob) return;
		zCCamera* camera = zCCamera::activeCam;
		if (!camera) return;
		
		zPOINT2 ssPoint1, ssPoint2;								// screen-space X,Y
		
		zPOINT3 wsPoint1 = sourceVob -> GetPositionWorld();
		zPOINT3 wsPoint2 = targetVob -> GetPositionWorld();
		
		zPOINT3 csPoint1 = camera	-> Transform (wsPoint1);
		zPOINT3 csPoint2 = camera	-> Transform (wsPoint2);
		
		Alg_ClipAtZ0(csPoint1,csPoint2);

		if (csPoint1[VZ]>=0)	camera->Project (&csPoint1, ssPoint1[VX], ssPoint1[VY]);
		else					return;
		if (csPoint2[VZ]>=0)	camera->Project (&csPoint2, ssPoint2[VX], ssPoint2[VY]);
		else					return;

		int x1 = (int)ssPoint1[VX];
		int y1 = (int)ssPoint1[VY];
		int x2 = (int)ssPoint2[VX];
		int y2 = (int)ssPoint2[VY];	
		if (!screen->ClipLine(x1,y1,x2,y2)) return;
	
		zrenderer -> DrawLineZ	((zREAL)x1,(zREAL)y1,1/csPoint1[VZ],(zREAL)x2,(zREAL)y2,1/csPoint2[VZ],GFX_GREEN);
	}
}

void zCEventManager :: ProcessMessageList()
{
	// Dont do it, if HostVob is not in World
	if (!hostVob->GetHomeWorld()) return;

	if (messageList.GetNumInList()>0) {

		// *********************************
		// First delete all marked Messages
		// *********************************
		int index = 0;
		int count = messageList.GetNumInList();
		zCEventMessage* ev = NULL;
		while (index < count) {
			ev = messageList[index];
			if (ev->IsDeleted()) {
				//zerr.Message("U:EVM:"+ev->MD_GetSubTypeString(ev->GetSubType())+" removed.");
				messageList.RemoveOrderIndex(index);
				count--;
				zRELEASE(ev);
			} else
				index++;
		}
		
		// *********************************
		// Now Send Messages
		// *********************************
		if (count<=0) return;
		
		cleared = FALSE;
		index	= 0;
		do {
			ev = messageList[index];
			// Nur, wenn Modi identisch

			// AAAAARRRRGGGGGGHHH: das hier ist skurrilerweise der grund, warum
			// die Waffen nicht weggesteckt werden: der Cutscene Mode der EV_RemoveWeapon
			// Message ist anders, wenn zwischendurch eine EV_PlayAniSound Message als Kommentar
			// läuft ? Man könnte die RemoveWeapon Message trotzdem spielen, neues Flag ?
			// AHA: Es sieht so aus als ob eine OU als eine Cutscene angesehen wird, so das 
			// bestimmte Messages schalten den EM des Vobs in einen Cutscene Modus (AI_Output(), B_Say() usw)
			// bis zum Ablauf dieser Events werden alle anderen die nicht aus der Cutscene kommen ignoriert.
			// dies macht allerdings keinen Sinn für wichtige Messages, die unbedingt durchkommen müssen, 
			// wie: Waffe wegstecken
			// weitere Fragen: gibt es noch mehr Messages ausser EV_Output_SVM(), die den CS Mode ändern ?
			// welche Messages genau sind es ?
			// gibt es einen nicht Cutscene Modus, obwohl noch Cutscene Messages in der Queue sind ?
			// wer setzt den Cutscene Modus, und wer schaltet ihn wieder aus ?

			// [EDENFELD] ACHTUNG: Ab 1.24d wird der Cutscene Mode ignoriert,
			// alle Messages werden immer ausgeführt, und alle Messages werden immer bei einem ClearEM() gelöscht.
			// d.h. die gesamte CS Funktionalität der Engine wird HIER ausgehebelt.

			if (GetCutsceneMode() == ev->GetCutsceneMode() || ev->GetIgnoreCutsceneMode()) 
			{
				// Message verschicken			
				SendMessageToHost(ev,hostVob,NULL);
				// hostVob -> OnMessage( ev, NULL );
				// Zwischenzeitlich gelöscht ?
				// (als Reaktion auf Message kann der EM gelöscht worden sein !)
				// Dann darf Queue nicht weiterverarbeitet werden.
				if (cleared) break;
				// Message löschen
				if (!ev -> IsJob()) ev -> Delete();
				// Kein Overlay, dann beenden
//				if (!ev -> IsOverlay() && !GetCutsceneMode()) break;
				if (!ev -> IsOverlay()) break;
			}
			
			index++;
		} while (index < count);

	} else {
		// Ist leer, schlafen legen
		SetActive(FALSE);
	}
}

void zCEventManager :: SetActive(zBOOL active)
{
	if (this->active==active) return;
	this->active = active;
	// Remove or Insert in List.
	if (active) 
		activeEM.Insert(this);
	else
		activeEM.Remove(this);
}

void zCEventManager :: Delete(zCEventMessage* eventMessage)
{
	if ( eventMessage->IsDeleteable() )
	{
		RemoveFromList(eventMessage);
		zRELEASE(eventMessage);
	}
}

void zCEventManager :: RemoveFromList(zCEventMessage* eventMessage)
{
	messageList.RemoveOrder(eventMessage);
}

void zCEventManager :: InsertInList(zCEventMessage* eventMessage)
{
//	zerr.Message("U:EVM:"+eventMessage->MD_GetSubTypeString(eventMessage->GetSubType())+" inserted.");

	// Insert it in List.
	if (eventMessage->IsHighPriority() || eventMessage->IsOverlay()) 
		// High Priority -> Insert as first Element in List
		// messageList.InsertFirst(eventMessage);
		messageList.InsertAtPos(eventMessage,0);
	else
		messageList.Insert(eventMessage);	
}

void zCEventManager :: SetCutscene(zCCutscene* _cutscene)
{
	zRELEASE(cutscene);
	cutscene = _cutscene;
	if (cutscene) cutscene -> AddRef();

	if (!cutscene) {
		// Beim Ausschalten alle CS-Messages, die noch drinliegen können ( weil Interrupt ) 
		// aus der Cutscene zuende machen -> in den Normalmodus wechseln
		int c = messageList.GetNumInList();
		for (int i=0; i<c; i++) {
			if (messageList[i]->GetCutsceneMode()) messageList[i]->SetCutsceneMode(FALSE);
		}
	}
}

zCCutscene* zCEventManager :: GetCutscene()
{
	return cutscene;
}

zBOOL zCEventManager :: GetCutsceneMode()
{
	return (cutscene!=NULL);
}

void zCEventManager :: Clear()
{
	zERR_MESSAGE(9,0,"U: Cleared EM : "+zVOB_DESCRIPTION(hostVob));
	// Empty List
	int c = messageList.GetNumInList()-1;
	for (int i = c; i>=0; i--) {


		// [EDENFELD] ACHTUNG: Ab 1.24d wird der Cutscene Mode ignoriert,
		// alle Messages werden immer ausgeführt, und alle Messages werden immer bei einem ClearEM() gelöscht.
		// d.h. die gesamte CS Funktionalität der Engine wird HIER ausgehebelt (auch: ProcessMessageList()).

		if (GetCutsceneMode() == messageList[i]->GetCutsceneMode()) Delete(messageList[i]);
	}
	cleared = TRUE;
}

zBOOL zCEventManager :: IsEmpty	(zBOOL ignoreOverlays)
{
	if (ignoreOverlays) {
		int c = messageList.GetNumInList();
		for (int i=0; i<c; i++) if (!messageList[i]->IsDeleted() && !messageList[i]->IsOverlay()) return FALSE;
		return TRUE;
	} else 
		return (messageList.GetNumInList()<=0);
}

zBOOL zCEventManager :: IsRunning (zCEventMessage* eventMessage)
{
	int c = messageList.GetNumInList();
	for (int i=0; i<c; i++) {
		if (messageList[i] == eventMessage) return TRUE;
	}	
	return FALSE;
}

zCEventMessage* zCEventManager :: GetActiveMessage ()
{
	int c = messageList.GetNumInList();
	for (int i=0; i<c; i++) {
		if (!messageList[i]->IsOverlay()) return messageList[i];
	}	
	return NULL;
}

// **************************************************************************************
// Debug
// **************************************************************************************

void zCEventManager::Print_db (const zSTRING& s, zCVob *otherVob) 
{ 
#if zDEBUG_EVENT_MESSAGES
	if (!hostVob) return;
	zSTRING t;
	t =  "D: EM: Message, ";
	if (otherVob)
	t += "from: "+otherVob->GetClassName_()+", "+otherVob->GetVobName()+"";
	t += "   \""+s+"\"   ";
	t += " to: "  +hostVob->GetClassName_()+", "+hostVob->GetVobName()+"";
	zerr.Message (t);
#endif
};

// **************************************************************************************
// ShortCuts
// **************************************************************************************

void zCEventManager::OnTouch	(zCVob* otherVob) 
{ 
	Print_db ("OnTouch", otherVob);
	ShowMessageCommunication	(otherVob,hostVob);
	hostVob->OnTouch			(otherVob); 
};

void zCEventManager::OnUntouch	(zCVob* otherVob) 
{ 
	Print_db ("OnUntouch", otherVob);
	ShowMessageCommunication	(otherVob,hostVob);
	hostVob->OnUntouch			(otherVob); 
};

void zCEventManager::OnTouchLevel() 
{ 
//	Print_db ("OnTouchLevel");
//	ShowMessageCommunication	(hostVob,hostVob);
	hostVob->OnTouchLevel		(); 
};

void zCEventManager::OnTrigger	(zCVob* otherVob, zCVob *vobInstigator) 
{ 
	Print_db ("OnTrigger", otherVob);
	ShowMessageCommunication	(otherVob,hostVob);
	hostVob->OnTrigger			(otherVob, vobInstigator); 
};

void zCEventManager::OnUntrigger(zCVob* otherVob, zCVob *vobInstigator) 
{ 
	Print_db ("OnUntrigger", otherVob);
	ShowMessageCommunication	(otherVob,hostVob);
	hostVob->OnUntrigger		(otherVob, vobInstigator); 
};

void zCEventManager::OnDamage(			zCVob*			otherVob, 
												zCVob*			inflictorVob,
												 zREAL			damage, 
												 int			damageType, 
												 const zVEC3&	hitLocation)
{ 
	Print_db ("OnDamage", otherVob);
	ShowMessageCommunication	(otherVob,hostVob);
	hostVob->OnDamage			(otherVob, inflictorVob,damage,damageType,hitLocation); 
};

// **************************************************************************************
// Debug
// **************************************************************************************

zCEventMessage* zCEventManager::GetEventMessage(int nr)
{
	return messageList[nr];
}

void zCEventManager::ShowList(int x, int y)
{
	zSTRING name;
	int dy	= screen->FontY();

	int c = messageList.GetNumInList();
	for (int i=0; i<c; i++) {
		name = messageList[i]->MD_GetSubTypeString(messageList[i]->GetSubType());
		if (messageList[i]->IsOverlay())		name += "(O)";		
		if (messageList[i]->GetCutsceneMode())	name += "(CS)";
		if (messageList[i]->IsDeleted())		name += "(D)";
		
		screen -> Print(x,y,name);
		y += dy;
		if (y + dy >= VIEW_VYMAX) return;
	}	
}

void zCEventManager::Archive	(zCArchiver& arc)
{
	zCObject::Archive(arc);
	arc.WriteBool	("cleared",		cleared);
	arc.WriteBool	("active",		active);
	arc.WriteObject	("emCutscene",	cutscene);
	
};

#include "zccscontext.h"

void zCEventManager::Unarchive	(zCArchiver& arc)
{
	zCObject::Unarchive(arc);
	
	zBOOL _active;

	arc.ReadBool	("cleared",		cleared);
	arc.ReadBool	("active",		_active);SetActive(_active);
	cutscene = dynamic_cast<zCCutscene*>(arc.ReadObject("emCutscene"));
};

 