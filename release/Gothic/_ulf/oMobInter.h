/******************************************************************************** 
 
     $Workfile:: oMobInter.h          $                $Date:: 13.04.01 18:27   $
     $Revision:: 29                   $             $Modtime:: 8.04.01 14:09    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oMobInter.h $
 * 
 * 29    13.04.01 18:27 Edenfeld
 * 
 * 28    8.02.01 18:23 Moos
 * 
 * 27    7.02.01 20:55 Wohlers
 * 
 * 26    22.01.01 22:38 Wohlers
 * 
 * 25    22.01.01 13:09 Moos
 * 
 * 24    10.01.01 15:23 Wohlers
 * 
 * 23    18.12.00 10:02 Keskenti
 * 
 * 22    7.11.00 15:42 Wohlers
 * 
 * 21    6.11.00 18:17 Wohlers
 * 
 * 20    27/10/00 16:53 Luesebrink
 * 
 * 19    17.10.00 16:37 Wohlers
 * 
 * 18    12.10.00 13:18 Wohlers
 * 
 * 17    4.10.00 21:02 Keskenti
 * 
 * 16    4.10.00 20:35 Keskenti
 * 
 * 15    4.10.00 20:17 Keskenti
 * 
 * 14    4.10.00 20:03 Keskenti
 * 
 * 13    4.10.00 19:11 Keskenti
 * 
 * 12    4.10.00 18:39 Keskenti
 * 
 * 11    28/09/00 17:13 Luesebrink
 * 
 * 10    20.09.00 21:50 Rueve
 * typedef
 * 
 * 9     8.08.00 18:29 Keskenti
 * 
 * 8     8.08.00 18:14 Wohlers
 * 
 * 7     7.07.00 12:42 Wohlers
 * Gothic 0.87
 * 
 * 6     9.06.00 12:58 Wohlers
 * Fixes
 * 
 * 5     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 18    3.04.00 18:31 Wohlers
 * uSrc 0.76b
 * 
 * 17    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 14    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 13    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 12    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 11    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 9     12.01.00 15:21 Wohlers
 * IsDestroyed
 * 
 * 8     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 7     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 6     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __OMOB_INTER__
#define __OMOB_INTER__

#include "oVob.h"
#include "oItem.h"
#include "oNpc.h"
#include "zTypes.h"
#include "zModel.h"

class zCModel;
class oCNpc;
class oCItemContainer;
class zCVisual;
class zCEventMessage;

typedef struct {						// Optimal Positions
	zMATRIX4		trafo;
	zBOOL			distance;
	oCNpc*			npc;				// What npc blocks this slot ?
	zSTRING			nodeName;
} TMobOptPos;

class oCMOB : public oCVob {
	zCLASS_DECLARATION (oCMOB)
public :
	oCMOB			();

	virtual	void			SetName				(const zSTRING& n);
	virtual	zSTRING			GetName				();
	virtual zCModel*		GetModel			();
	virtual zSTRING			GetScemeName		();
	virtual void			SetVisual			(zCVisual* v);

			void			SetMoveable			(zBOOL moveable);
			zBOOL			IsMoveable			();
	
			void			SetTakeable			(zBOOL table)		{ takeable = table; };
			zBOOL			IsTakeable			()					{ return takeable;	};

			void			SetFocusOverride	(zBOOL inFocus)		{ focusOverride = inFocus;	};
			zBOOL			HasFocusOverride	()					{ return focusOverride;		};
			
	// *********************************
	// Sound
	// *********************************
	virtual void			GetSoundMaterial_AM	(zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2, int damage);
	virtual	void			SetSoundMaterial	(oTSndMaterial mat);
	virtual oTSndMaterial	GetSoundMaterial	();

	virtual zBOOL			IsOwnedByGuild		(int guild);
	virtual zBOOL			IsOwnedByNpc		(int instance);
			void			SetOwner			(const zSTRING& owner, const zSTRING& ownerGuild);
			void			SetOwner			(int owner, int ownerGuild);
			zBOOL			IsOwner				(oCNpc* npc);

			void			Hit					(int damage);
	virtual	void			Destroy				();
			zBOOL			IsDestroyed			()					{ return isDestroyed; };

			int				GetDamage			()					{ return damage; };
			void			SetDamage			(int dam)			{ damage = dam; };

	// ****************************
	// Basic Event-Messages
	// ****************************
//	virtual void			OnTouch				(zCVob* otherVob);
	virtual	void			OnDamage			(zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation);
	virtual void			OnMessage			(zCEventMessage *eventMessage,zCVob* otherVob);

	// *************************************
	// Archive / Unarchive
	// *************************************

	virtual void			Archive				(zCArchiver &arc);
	virtual void			Unarchive			(zCArchiver &arc);
    virtual zBOOL       AllowDiscardingOfSubtree();

	// *************************************
	// Static / Temp
	// *************************************
	static	void			ConvertOldMobsToNewMobs ();

protected:
	virtual ~oCMOB	();

	virtual zBOOL			CanThisCollideWith	(zCVob* vob);				// gives derived vobs the possibility to exclude special other vobs from collDet and collResp
	void					InsertInIgnoreList	(zCVob* vob);
	void					RemoveFromIgnoreList(zCVob* vob);

public:
	// Properties
	zSTRING			name;				// FocusName

	int				hitp            :12;				// Hitpoints
	int				damage          :12;

	zBOOL			isDestroyed     :1;

	zBOOL			moveable        :1;			// is Object Moveable ( Push / Pull )
	zBOOL			takeable        :1;
	zBOOL			focusOverride   :1;

	oTSndMaterial	sndMat          :3;

	zSTRING			visualDestroyed;

	zSTRING			ownerStr;
	zSTRING			ownerGuildStr;
	
	int				owner;
	int				ownerGuild;

	int				focusNameIndex;

	zCList<zCVob>	ignoreVobList;
};

////////////////////////////////////////////////////////////////////////////////
//
//	oCMobInter
//	
//	2002-05-11	[BENDLIN]
//
//				New: Direction (TMobInterDirection)
//					(for detecting/saving current direction of usage)
//				New: GetStateNum
//					(give objects the possibility to ask for the number of states)
//
////////////////////////////////////////////////////////////////////////////////

class oCMobInter : public oCMOB {
	zCLASS_DECLARATION (oCMobInter)
public :
	oCMobInter	();
	
	enum TMobInterDirection
	{
		MOBINTER_DIRECTION_NONE = 0,
		MOBINTER_DIRECTION_UP,
		MOBINTER_DIRECTION_DOWN
	};
	
	// Aus zCVob
	virtual void		SetVisual			(zCVisual *v);
	virtual int			GetState			() { return state; };
	
	virtual int			GetStateNum			() { return state_num; };
	virtual TMobInterDirection	GetDirection()							{ return Direction; };
	virtual void				SetDirection(TMobInterDirection dir)	{ Direction = dir; };
	
	void				SetTempState		(int tmpState);
	zBOOL				IsTempStateChanged	();
	void				SetStateToTempState	();

	virtual void		SetUseWithItem		(const zSTRING& name);
	virtual int			GetUseWithItem		();
			zBOOL		HasUseWithItem		(oCNpc* npc);

	virtual zSTRING		GetScemeName		();
	virtual void		Reset				();	

	virtual void		Interact			(oCNpc* npc,zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right);
	virtual void		EndInteraction		(oCNpc* npc,zBOOL playEndAni = TRUE);
	virtual void		InterruptInteraction(oCNpc* npc);
	virtual void		StopInteraction		(oCNpc* npc);

	virtual zBOOL		CanInteractWith		(oCNpc* npc);
	virtual	zBOOL		IsInteractingWith	(oCNpc* npc);
	virtual zBOOL		IsOccupied			() { return (npcsCurrent > 0);};

	zBOOL				IsMultiMob			();
	virtual void		OnTick				();					// called, if vob is not sleeping
	void				SetRewind			(zBOOL _rewind) { rewind = _rewind; };

	// Use of NSCs
	virtual zBOOL		AI_UseMobToState	(oCNpc* npc, int target);

	virtual int			IsIn				(int instance)	{ return FALSE; };
	virtual zBOOL		IsInState			(oCNpc* npc, int snr);

	// Temp -> Make protected
	zBOOL				GetFreePosition		(oCNpc* npc, zVEC3& pos);
	TMobOptPos*			GetFreeMobOptPos	(oCNpc* npc){ ScanIdealPositions();return(SearchFreePosition(npc,zREAL_MAX));};

	virtual void		OnTrigger			(zCVob *otherVob, zCVob *vobInstigator);
	virtual void		OnUntrigger			(zCVob *otherVob, zCVob *vobInstigator);

	// Timer Func
	zBOOL				IsAvailable			(oCNpc* npc);
	void				MarkAsUsed			(zREAL timer, zCVob* vob);

	// Set Npc-BodyState
	void				SetMobBodyState		(oCNpc* npc);

	virtual const zSTRING*	GetTriggerTarget(const int i=0) const { if (i==0) return &triggerTarget; else return 0; };

	// static mobsi-routine
	static int			SetAllMobsToState	(oCWorld* wld, const zSTRING& scheme, int stateNr);
	static void			TraverseMobs		(zCTree <zCVob> *node, const zSTRING& scheme, int stateNr, int *a_iCounter);
	// Patch 1.08
	static void			TriggerAllMobsToTmpState(zCWorld* wld);
	static void			TraverseTriggerMobs		(zCTree <zCVob>* node);

protected :
	virtual				~oCMobInter			();

	// Methods
	virtual	void		StartInteraction	(oCNpc* npc);
public:
	virtual void		StartStateChange	(oCNpc* npc, int from, int to);
	virtual void		CheckStateChange	(oCNpc* npc);
	virtual zBOOL		CanChangeState		(oCNpc* npc, int from, int to);
	virtual void		GetTransitionNames	(int from, int to, zSTRING& mobAni, zSTRING& npcAni);

	virtual void		OnBeginStateChange	(oCNpc* npc, int from, int to);
	virtual void		OnEndStateChange	(oCNpc* npc, int from, int to);

	void				SendStateChange		(int from, int to);
	void				SendEndInteraction	(oCNpc* npc, int from, int to);

	void				StartTransitionAniNpc(oCNpc* n, const zSTRING& aniName);

	virtual void		CallOnStateFunc		(oCNpc* npc, int state);
	virtual void		SendCallOnStateFunc	(oCNpc* npc, int state);

	void				SetHeading			(oCNpc* npc);
	void				ScanIdealPositions	();
	void				SetIdealPosition	(oCNpc* npc);
	virtual TMobOptPos*	SearchFreePosition	(oCNpc* npc, zREAL a_fMaxDist = 150);

	// Position Handling
	zCList<TMobOptPos>	optimalPosList;		// List of all Optimal Positions
	
	zSTRING				triggerTarget;		// Vobs To Trigger
	zSTRING				useWithItem;		// Oly useable with this Item
	zSTRING				sceme;				// ScemeName
	zSTRING				conditionFunc;		// SkriptFunc
	zSTRING				onStateFuncName;	// OnStateFuncName
	int					state;				// current State
	int					state_num;			// Number of states
	int					state_target;		// Next Target-State
	zBOOL				rewind;

	zTModelAniID		mobStateAni;
	zTModelAniID		npcStateAni;

//	int					usedNpcNode :8;		// Using Item in this slot ?

	// MultiMobs
	int					npcsMax     :8;
	int					npcsNeeded  :8;
	int					npcsCurrent :8;
	int					tmpState	:8;
	zBOOL				tmpStateChanged;

	TMobInterDirection	Direction;			// direction in which the mob is used

public:
	zBOOL				onInterruptReturnToSlotPos:1;
protected:

	// *************************************
	// Generic Messages
	// *************************************
	virtual	void		OnDamage			(zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation);
	virtual	void		OnMessage			(zCEventMessage* message, zCVob* otherVob);

	// *************************************
	// Archive / Unarchive
	// *************************************

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);

public:
	zVEC3				startPos;
	zREAL				aniCombHeight;
	zCVob*				inUseVob;
	zREAL				timerEnd;
};

class oCMobBed : public oCMobInter {
	zCLASS_DECLARATION (oCMobBed)
public:
	oCMobBed			();

	virtual	zSTRING		GetScemeName();

protected:
	virtual				~oCMobBed			();

	virtual	void		StartInteraction	(oCNpc* npc);
	virtual void		OnBeginStateChange	(oCNpc* npc, int from, int to);
	virtual void		OnEndStateChange	(oCNpc* npc, int from, int to);

	virtual TMobOptPos*	SearchFreePosition	(oCNpc* npc, zREAL maxDist = 150);

	zSTRING addName;
};

class oCMobSwitch : public oCMobInter {
	zCLASS_DECLARATION (oCMobSwitch)
public :

	oCMobSwitch			();

protected:

	virtual				~oCMobSwitch		();

	// *************************************
	// Archive / Unarchive
	// *************************************

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);

};

class oCMobItemSlot : public oCMobInter {
	zCLASS_DECLARATION (oCMobItemSlot)
public :

	oCMobItemSlot							();

	virtual int			IsIn				(int instance);
	virtual oCItem*		GetInsertedItem		();
	virtual zBOOL		PlaceItem			(oCItem* item);
	virtual oCItem*		RemoveItem			();

	virtual int			GetUseWithItem		();
	virtual zBOOL		CanInteractWith		(oCNpc* npc);

protected:

	virtual				~oCMobItemSlot		();

	oCItem*				insertedItem;
	zBOOL				removeable;

	// *************************************
	// Archive / Unarchive
	// *************************************

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);
	
};

class oCMobLockable : public oCMobInter 
{
	zCLASS_DECLARATION (oCMobLockable)

	// *************************************
	// Attributes
	// *************************************
protected:
	zBOOL				locked    :1;	
	zBOOL				autoOpen  :1;			// open automatically
	int					pickLockNr:30;			

	zSTRING				keyInstance;		// Script-Instance of key to unlock
	zSTRING				pickLockStr;		// LLLRRRRLRL

	// *************************************
	// Get / Set
	// *************************************
public:
	zBOOL				CanOpen				( oCNpc* npc);

	virtual void		SetLocked			( zBOOL _locked			) { locked		= _locked	; }
	virtual void		SetKeyInstance		( const zSTRING& key	) { keyInstance = key		; }
	virtual void		SetPickLockStr		( const zSTRING& unlock ) { pickLockStr = unlock	; }

	// *************************************
	// Open / Close
	// *************************************
protected:
	virtual void		Open				(oCNpc* npc) = NULL;
	virtual void		Close				(oCNpc* npc) = NULL;

	virtual void		Lock				(oCNpc* npc);
	virtual void		Unlock				(oCNpc* npc, zBOOL left);
	virtual zBOOL		PickLock			(oCNpc* npc, const char pickLockChar);

	// *************************************
	// Interaction
	// *************************************
public:
	virtual zBOOL		CanInteractWith		(oCNpc* npc);
	virtual void		Interact			(oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right);

protected:
	virtual zBOOL		CanChangeState		(oCNpc* npc, int from, int to);
	virtual void		OnEndStateChange	(oCNpc* npc, int from, int to);

	// *************************************
	// Generic Messages
	// *************************************
protected:
	virtual void		OnMessage			(zCEventMessage* message, zCVob* otherVob) { oCMobInter::OnMessage( message, otherVob ); }

	// *************************************
	// Archive / Unarchive
	// *************************************
protected:
	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);

	// *************************************
	// Con- / Destruction
	// *************************************
public:					 oCMobLockable		();
protected:	virtual		~oCMobLockable		();
};


class oCMobContainer : public oCMobLockable {
	zCLASS_DECLARATION (oCMobContainer)

	// *************************************
	// Attributes
	// *************************************
protected:
	zSTRING				contains;			// Script-Instances of Items
	oCItemContainer*	items;
	zCListSort<oCItem>	containList;

	// *************************************
	// Lock / Open	 derived f. oCMobockable
	// *************************************
protected:
	virtual void		Open				(oCNpc* npc);

	// *************************************
	// Content Management
	// *************************************
public:
	zCListSort<oCItem>*	GetContainList		( void ) { return &containList; }; 
	virtual int			IsIn				(int instance);

	virtual void		Insert				(oCItem* item);
	virtual void		Remove				(oCItem* item);
	virtual oCItem*		Remove				(oCItem* item, int anz);
	virtual void		CreateContents		(const zSTRING& s);

	virtual void		Close				(oCNpc* npc);
	// *************************************
	// Interaction
	// *************************************
public:
//	virtual zBOOL		CanInteractWith		(oCNpc* npc);
//	virtual void		Interact			(oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right);
	virtual void		Reset				();	

protected:
//	virtual zBOOL		CanChangeState		(oCNpc* npc, int from, int to);
//	virtual void		OnEndStateChange	(oCNpc* npc, int from, int to);

	// *************************************
	// Generic Messages
	// *************************************
protected:
	virtual void		OnMessage			(zCEventMessage* message, zCVob* otherVob);

	// *************************************
	// Archive / Unarchive
	// *************************************
protected:
	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);

	// *************************************
	// Creation / Deletion
	// *************************************
public :
	virtual	void		Destroy				();

	// *************************************
	// Con- / Destruction
	// *************************************
public:					oCMobContainer		();
protected:	virtual		~oCMobContainer		();
};

class oCMobDoor : public oCMobLockable{
	zCLASS_DECLARATION (oCMobDoor)
public:
	oCMobDoor			();

	virtual zSTRING		GetScemeName		();

protected:
	virtual void		Open				(oCNpc* npc) {;}
	virtual void		Close				(oCNpc* npc) {;}

	virtual				~oCMobDoor			();
	
	zSTRING				addName;			// FRONT / BACK
	
	virtual TMobOptPos*	SearchFreePosition	(oCNpc* npc, zREAL a_fMaxDist = 150);	
	//	virtual void		OnBeginStateChange	(oCNpc* npc, int from, int to);
};

class oCMobFire : public oCMobInter {
	zCLASS_DECLARATION (oCMobFire)

public:
	oCMobFire			();

	virtual	void		OnDamage			(zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation);
	virtual void		OnTrigger			(zCVob* otherVob, zCVob *vobInstigator);
	virtual void		OnUntrigger			(zCVob* otherVob, zCVob *vobInstigator);
	virtual void		OnEndStateChange	(oCNpc* npc, int from, int to);

	void				DeleteEffects		();					// Clean up

	virtual void		PreSave				();
	virtual void		PostSave			();

protected:
	virtual				~oCMobFire			();

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);

private:

	zSTRING				fireSlot;								// Where to Position the effect
	zSTRING				fireVobtreeName;
	
	zCVob*				fireVobtree;

};

// *******************************************************************************
// Mobs with more than two states
// *******************************************************************************


/*--------------------------------------------------------------------------

   class oCMobWheel : public oCMobInter

 

    28-Sep-00       [Dennis]
					
					interact in wheel


--------------------------------------------------------------------------*/

class oCMobWheel : public oCMobInter {
	zCLASS_DECLARATION (oCMobWheel)
public:
	oCMobWheel			();

	virtual void		Interact			(oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right);
protected:
	virtual ~oCMobWheel	();

	virtual void		OnTrigger			(zCVob *otherVob, zCVob *vobInstigator);
	virtual void		OnUntrigger			(zCVob *otherVob, zCVob *vobInstigator);
	
	//	virtual void		OnBeginStateChange	(oCNpc* npc, int from, int to);
};

////////////////////////////////////////////////////////////////////////////////
//
//	oCMobLadder
//					
//	2002-05-11	[BENDLIN]
//
//				new: GetStateNum
//				new: Interacting, PrevAction
//				new: EndInteraction
//				chg: Interact
//
////////////////////////////////////////////////////////////////////////////////

class oCMobLadder : public oCMobInter {
	zCLASS_DECLARATION (oCMobLadder)
public:
	oCMobLadder			();

	virtual zBOOL		CanInteractWith		(oCNpc* npc);

protected:
	virtual				~oCMobLadder		();

	virtual zBOOL		DoFocusCheckBBox	()	{ return TRUE; };

	virtual	TMobOptPos*	SearchFreePosition	(oCNpc* npc, zREAL a_fMaxDist = 150);
	virtual void		StartInteraction	(oCNpc* npc);
	virtual void		EndInteraction		(oCNpc* npc,zBOOL playEndAni = TRUE);
	zBOOL				CanChangeState		(oCNpc* npc, int from, int to);

	virtual void		Interact			(oCNpc* npc, zBOOL action, zBOOL up, zBOOL down, zBOOL left, zBOOL right);

//	virtual void		OnBeginStateChange	(oCNpc* npc, int from, int to);

private:
	zBOOL				Interacting;	// Ladder <-> (N)PC are interacting
	zBOOL				PrevAction;		// saved action state to detect new actions
};

// *******************************************************************************
// Dummy - Generator
// *******************************************************************************

class oCDummyVobGenerator : public zCVob
{
	zCLASS_DECLARATION	(oCDummyVobGenerator)
public:
	oCDummyVobGenerator	();

	virtual void		OnTrigger	(zCVob* otherVob, zCVob *vobInstigator);
protected:
	virtual ~oCDummyVobGenerator	() { };
};

extern void ConvertAllMobsInWorld();

// *********************************************************************************
// Static : Konvertierung der alten Mobs ins neue Format
// *********************************************************************************

class oCMobMsg : public zCEventMessage
{
zCLASS_DECLARATION	(oCMobMsg)
public:
	enum TMobMsgSubType {
		EV_STARTINTERACTION = 0,
		EV_STARTSTATECHANGE,
		EV_ENDINTERACTION,
		EV_UNLOCK,
		EV_LOCK,
		EV_CALLSCRIPT
	};
	
	oCMobMsg			(TMobMsgSubType subType, oCNpc* npc);
	oCMobMsg			(TMobMsgSubType subType, oCNpc* npc, zBOOL flag);

	virtual zBOOL		IsNetRelevant		()	{ return TRUE; };

	oCNpc*				npc;

	int					from;

	int					to     :31;
	zBOOL				playAni:1;

	virtual int			MD_GetNumOfSubTypes	();
	virtual zSTRING		MD_GetSubTypeString	(int n);

protected:
	// Pack / Unpack
	virtual void		Pack				(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void		Unpack				(zCBuffer& buffer, zCEventManager* evManContext);

	// Archive / Unarchive
//	virtual void		Archive				(zCArchiver& arc);
//	virtual void		Unarchive			(zCArchiver& arc);
	
	// Std-Con
	oCMobMsg			();
};

#endif