/******************************************************************************** 
 
     $Workfile:: zEventMan.h          $                $Date:: 26.01.01 18:30   $
     $Revision:: 9                    $             $Modtime:: 26.01.01 18:08   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zEventMan.h $
 * 
 * 9     26.01.01 18:30 Wohlers
 * 
 * 8     4.12.00 18:23 Moos
 * 
 * 7     18.08.00 15:44 Wohlers
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
 * 10    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 9     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 8     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 6     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZEVENTMANAN_H__
#define __ZEVENTMANAN_H__

#ifndef __ZOBJECT_H__
#include "zObject.h"
#endif

#ifndef __ZVOB_H__
#include "zVob.h"
#endif

#ifndef __ZARCHIVER_H__
#include "zArchiver.h"
#endif

class zCNetVobControl;
class zCCutscene;

class zCEventManager : public zCObject {
	zCLASS_DECLARATION	(zCEventManager)
public:
	zEVENT_INTERFACE

	zCEventManager			();

			 zCEventManager(zCVob* hostVob);
	virtual ~zCEventManager();

	zCVob*					GetHostVob			() const { return hostVob; };

	// messages
/*	virtual void			OnTouch				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnUntouch			(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnTouchLevel		();
	virtual	void			OnTrigger			(zCVob* otherVob);
	virtual	void			OnUntrigger			(zCVob* otherVob);
	virtual void			OnDamage			(zCVob*			otherVob, 
												 zCVob*			inflictorVob,
												 zREAL			damage, 
												 int			damageType, 
												 const zVEC3&	hitLocation);

	// generic messages							
	virtual void			OnMessage			(zCEventMessage *eventMessage, zCVob* sourceVob);
*/	
	// Status
	virtual void			Clear				();								// Dispose all Messages
			void			KillMessages		();
	virtual zBOOL			IsEmpty				(zBOOL ignoreOverlays=FALSE);	
	
	virtual zBOOL			GetCutsceneMode		();

	virtual void			SetCutscene			(zCCutscene* context);						// Special Mode for Cutscenes
	virtual zCCutscene*		GetCutscene			();

	virtual zBOOL			IsRunning			(zCEventMessage* eventMessage);
	virtual void			SetActive			(zBOOL active);

	// Check single Messages
	virtual	int				GetNumMessages		()			{ return messageList.GetNumInList(); };
	virtual zCEventMessage*	GetEventMessage		(int nr);
	virtual zCEventMessage* GetActiveMessage	();

	// Debug
	virtual void			ShowList			(int x, int y);

	// Network
	virtual zCNetVobControl*GetNetVobControl	(zBOOL dontCreateIfNotPresent = FALSE) { return NULL; };

	// Static - call per frame
	static void				DoFrameActivity		();
	static zBOOL			disableEventManagers;

	// Static
	static void				SetShowMessageCommunication (zBOOL show);
	static zBOOL			GetShowMessageCommunication ();

protected:
	
	virtual void			RemoveFromList		(zCEventMessage* eventMessage);
	virtual void			InsertInList		(zCEventMessage* eventMessage);
	virtual void			ProcessMessageList	();
	virtual void			SendMessageToHost	(zCEventMessage* eventMessage, zCVob* hostVob, zCVob* sourceVob);
	
	virtual void			Delete				(zCEventMessage* event);

	// Archive / Unarchive (inherited from zCObject)
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

	// Debug
	void					Print_db			(const zSTRING& s, zCVob *otherVob=0);		// debug
	void					ShowMessageCommunication(zCVob* sourceVob, zCVob* targetVob);

	// Vars
	zBOOL					cleared;			// Cleared during Msg-processing ?
	zBOOL					active;				// EM active ?
	zCCutscene*				cutscene;			// Special Cutscene Mode ?
	zCArray<zCEventMessage*>messageList;
	zCVob*					hostVob;

	// Statics
	static zCArray<zCEventManager*>	activeEM;
	static zBOOL					showMsgCommunication;
};

#endif