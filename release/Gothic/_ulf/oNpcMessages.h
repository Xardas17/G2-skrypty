/******************************************************************************** 
 
     $Workfile:: oNpcMessages.h       $                $Date:: 25.01.01 21:19   $
     $Revision:: 40                   $             $Modtime:: 25.01.01 20:55   $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   
 * 
 *********************************************************************************/

#ifndef __NPCMESSAGES__
#define __NPCMESSAGES__

#include "zVob.h"
#include "zBuffer.h"
#include "zSound.h"
#include "zModel.h"
#include "oNpc.h"

class	oCVob;
class	oCItem;
class	oCNpc;
class	zCRoute;
class	zCWaypoint;

class oCNpcMessage : public zCEventMessage 
{
zCLASS_DECLARATION	(oCNpcMessage)
public:
	oCNpcMessage								();
	virtual ~oCNpcMessage						();

	virtual void			Delete				()				{ deleted	= TRUE;	};
	virtual void			SetInUse			(zBOOL in)		{ inUse		= in;	};
	virtual zBOOL			IsInUse				()				{ return inUse;		};
	virtual void			SetHighPriority		(zBOOL high)	{ highPriority = high; };
	virtual zBOOL			GetIgnoreCutsceneMode()				{ return FALSE; };

protected:
	// Methoden
	virtual zBOOL			IsOverlay			()				{ return FALSE;		};
	virtual zBOOL			IsJob				()				{ return TRUE;		};
	virtual zBOOL			IsDeleted			()				{ return deleted;	};
	virtual zBOOL			IsDeleteable		()				{ return TRUE;		};
	
	virtual zBOOL			IsHighPriority		()				{ return highPriority; };

	// Archive 
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

	// Andre -> Spacer -> muss wohl immer da sein ? 
	zSTRING					targetVobName;		
	// Standard Attribute
	zBOOL					highPriority  :1;
	zBOOL					deleted       :1;
	zBOOL					inUse         :1;	
};

class oCMsgDamage : public oCNpcMessage
{
	zCLASS_DECLARATION	( oCMsgDamage )

	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
public:
	enum TDamageSubType 
	{
		EV_DAMAGE_ONCE		= 0	,
		EV_DAMAGE_PER_FRAME		,	
		EV_DAMAGE_MAX
	};

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************

	oCMsgDamage									( TDamageSubType enuSubType, const oCNpc::oSDamageDescriptor& descDescDamage );

	virtual zBOOL			IsNetRelevant		()	{ return TRUE; };
	virtual zBOOL			IsOverlay			()	{ return ( this->subType == EV_DAMAGE_PER_FRAME ); }
	virtual zBOOL			IsDeleteable		()	{ return FALSE; };
	virtual zBOOL			IsHighPriority		()	{ return (this->highPriority = TRUE); };

	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	( int nSubType );
	
#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			( const zSTRING & strInfo );
#endif

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
	oCNpc::oSDamageDescriptor	descDamage	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
protected:

	oCMsgDamage									();
	oCMsgDamage									( TDamageSubType enuSubType );
	virtual	~oCMsgDamage						();

	// Pack / Unpack
	virtual void			Pack				( zCBuffer& buffer, zCEventManager* evManContext );
	virtual void			Unpack				( zCBuffer& buffer, zCEventManager* evManContext );

	// Archive 
	virtual void			Archive				( zCArchiver& arc );
	virtual void			Unarchive			( zCArchiver& arc );
};

class oCMsgWeapon : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgWeapon)
public:
	enum TWeaponSubType {
		EV_DRAWWEAPON = 0,
		EV_DRAWWEAPON1,
		EV_DRAWWEAPON2,
		EV_REMOVEWEAPON,
		EV_REMOVEWEAPON1,
		EV_REMOVEWEAPON2,
		EV_CHOOSEWEAPON,
		EV_FORCEREMOVEWEAPON,
		EV_ATTACK,
		EV_EQUIPBESTWEAPON,
		EV_EQUIPBESTARMOR,
		EV_UNEQUIPWEAPONS,
		EV_UNEQUIPARMOR,
		EV_EQUIPARMOR,
		EV_WEAPON_MAX
	};

	// Std-Con
	oCMsgWeapon									();
	oCMsgWeapon									(TWeaponSubType subType, int targetMode = 0, zBOOL useFist = FALSE);
	virtual ~oCMsgWeapon						() {};

	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	(int n);

	//			- TimeBehavior
	virtual zTTimeBehavior	MD_GetTimeBehavior	();
	virtual zREAL			MD_GetMinTime		();
//	virtual zBOOL			IsDeleteable		()				{ if (subType >= EV_REMOVEWEAPON && subType <= EV_FORCEREMOVEWEAPON ) return FALSE; else return TRUE; };
//	virtual zBOOL			GetIgnoreCutsceneMode()				{ return (!IsDeleteable()); };


#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

	int						targetMode;
	zBOOL					duringRun       :1;
	zBOOL					initDone        :1;
	zBOOL					firstTime       :1;
	zBOOL					useFist         :1;
	zBOOL					showMagicCircle :1;

	zTModelAniID			ani;

protected:

	// Archive 
	virtual void			Archive			(zCArchiver& arc);
	virtual void			Unarchive		(zCArchiver& arc);
};

class oCMsgMovement : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgMovement)
public:
	enum TMovementSubType {
		EV_ROBUSTTRACE = 0,
		EV_GOTOPOS,
		EV_GOTOVOB,
		EV_GOROUTE,
		EV_TURN,
		EV_TURNTOPOS,
		EV_TURNTOVOB,
		EV_TURNAWAY,
		EV_JUMP,
		EV_SETWALKMODE,
		EV_WHIRLAROUND,
		EV_STANDUP,
		EV_CANSEENPC,
		EV_STRAFE,
		EV_GOTOFP,
		EV_DODGE,
		EV_BEAMTO,
		EV_ALIGNTOFP,
		EV_MOVE_MAX
	};
	oCMsgMovement								();
	oCMsgMovement								(TMovementSubType subType, const zSTRING&	target);
	oCMsgMovement								(TMovementSubType subType,		 zCVob*		target);
	oCMsgMovement								(TMovementSubType subType, const zVEC3&		target);
	oCMsgMovement								(TMovementSubType subType,		 zREAL	 	 angle);
	oCMsgMovement								(TMovementSubType subType,		 int		target);

	virtual ~oCMsgMovement						();		

	void					Init				();
	virtual void			Delete				();

	// MetaData	- Subtypes
	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	(int n);

	//			- Parameter
	virtual zSTRING			MD_GetVobRefName	();
	virtual void			MD_SetVobRefName	(const zSTRING & name);
	virtual void			MD_SetVobParam		(zCVob* vob);

	//			- TimeBehavior
	virtual zTTimeBehavior	MD_GetTimeBehavior	();
	virtual zREAL			MD_GetMinTime		();

#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif
/*	virtual zBOOL			IsDeleteable		()				
	{ 		
		if (subType == EV_BEAMTO) return FALSE;
		return TRUE;
	}*/
	//virtual zBOOL			GetIgnoreCutsceneMode()				{ return (!IsDeleteable()); };
 
	zSTRING					targetName;
	zCRoute*				route;
	zCVob*					targetVob;
	zVEC3					targetPos;
	zREAL					angle;
	zREAL					timer;
	int						targetMode;
	zTModelAniID			ani;

protected:
	// Archive 
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);
};

class oCMsgAttack : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgAttack)
public:
	enum TAttackSubType {
		EV_ATTACKFORWARD = 0,
		EV_ATTACKLEFT,
		EV_ATTACKRIGHT,
		EV_ATTACKRUN,
		EV_ATTACKFINISH,
		EV_PARADE,
		EV_AIMAT,
		EV_SHOOTAT,
		EV_STOPAIM,
		EV_DEFEND,
		EV_ATTACKBOW,
		EV_ATTACKMAGIC,
		EV_ATTACK_MAX
	};
	oCMsgAttack									();
	oCMsgAttack									(TAttackSubType	subType, zTModelAniID ani, int combo = 1);
	oCMsgAttack									(TAttackSubType	subType, zCVob* target, zREAL startFrame = 0.0f);

	virtual zBOOL			IsNetRelevant		()	{ return TRUE; };
	virtual zBOOL			IsOverlay			()	{ return ((subType == EV_AIMAT) || (subType == EV_DEFEND)); }


	// MetaData	- Subtypes
	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	(int n);
	
#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

	/*virtual zBOOL			IsDeleteable		()				
	{ 		
		if (subType == EV_STOPAIM) return FALSE;
		return TRUE;
	}*/

	//virtual zBOOL			GetIgnoreCutsceneMode()				{ return (!IsDeleteable()); };


	int						combo;
	zCVob*					target;
	zTModelAniID			hitAni;
	zREAL					startFrame;

	zBOOL					enableNextHit:1;
	zBOOL					reachedTarget:1;

protected:

	// Pack / Unpack
	virtual void			Pack				(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void			Unpack				(zCBuffer& buffer, zCEventManager* evManContext);

	// Archive 
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);
};

class oCMsgUseItem : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgUseItem)
public:
	enum TUseItemSubType {
		EV_DRINK = 0,
		EV_EQUIPITEM,
		EV_UNEQUIPITEM,
		EV_USEITEM_MAX
	};
	
	// Std-Con
	oCMsgUseItem								();
	oCMsgUseItem								(TUseItemSubType subType, zCVob* vob);
	virtual ~oCMsgUseItem						();

	virtual zBOOL			IsNetRelevant		()	{ return TRUE; };

#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

	/*virtual zBOOL			IsDeleteable		()				
	{ 		
		if (subType == EV_EQUIPITEM || subType == EV_UNEQUIPITEM) return FALSE;
		return TRUE;
	}*/
	//virtual zBOOL			GetIgnoreCutsceneMode()		{ return (!IsDeleteable()); };

	zCVob*					vob;
	zTModelAniID			ani;
	int						state;

protected:
	// Pack / Unpack
	virtual void			Pack				(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void			Unpack				(zCBuffer& buffer, zCEventManager* evManContext);

	// Archive / Unarchive
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);
	
};

class oCMsgState : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgState)
public:
	enum TStateSubType {
		EV_STARTSTATE = 0,
		EV_WAIT,
		EV_SETNPCSTOSTATE,
		EV_SETTIME,
		EV_APPLYTIMEDOVERLAY,
		EV_STATE_MAX
	};
	
	// Std-Con
	oCMsgState									();
	oCMsgState									(TStateSubType subType, zREAL timer);
	oCMsgState									(TStateSubType subType, int func);
	oCMsgState									(TStateSubType subType, int func, zBOOL param, const zSTRING& wp);

	virtual ~oCMsgState							();

#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

/*	virtual zBOOL			IsDeleteable		()				
	{ 		
		if (subType == EV_SETTIME) return FALSE;
		return TRUE;
}*/

//	virtual zBOOL			GetIgnoreCutsceneMode()				{ return (!IsDeleteable()); };	// ACHTUNG: Timingprobleme mit B_Say möglich -> beobachten


	int						function;
	int						minutes;
	int						instance;
	zSTRING					wp;
	zREAL					timer;
	oCNpc					*other,*victim;

	zBOOL					endOldState    :1;
	zBOOL					inRoutine      :1;

	int						MD_GetNumOfSubTypes	();
	zSTRING					MD_GetSubTypeString	(int n);
	zTTimeBehavior			MD_GetTimeBehavior	();
	zREAL					MD_GetMinTime		();

protected:
	virtual zBOOL			IsOverlay			()	{ return ( subType == EV_APPLYTIMEDOVERLAY ); }
	// Pack / Unpack
//	virtual void			Pack				(zCBuffer& buffer, zCEventManager* evManContext);
//	virtual void			Unpack				(zCBuffer& buffer, zCEventManager* evManContext);

	// Archive / Unarchive
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);
	
};

class oCMsgManipulate : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgManipulate)
public:
	enum TManipulateSubType {
		EV_TAKEVOB	= 0,
		EV_DROPVOB,
		EV_THROWVOB,
		EV_EXCHANGE,
		EV_USEMOB,
		EV_USEITEM,
		EV_INSERTINTERACTITEM,		// NET
		EV_REMOVEINTERACTITEM,		// NET
		EV_CREATEINTERACTITEM,		// NET
		EV_DESTROYINTERACTITEM,		// NET
		EV_PLACEINTERACTITEM,		// NET
		EV_EXCHANGEINTERACTITEM,	// NET
		EV_USEMOBWITHITEM,			// NET
		EV_CALLSCRIPT,				// NET
		EV_EQUIPITEM,				// NET
		// Neu
		EV_USEITEMTOSTATE,
		EV_TAKEMOB,
		EV_DROPMOB,
		EV_MANIP_MAX
	};

	oCMsgManipulate								();
	oCMsgManipulate								(TManipulateSubType subType);
	oCMsgManipulate								(TManipulateSubType subType, zCVob* vob );
	oCMsgManipulate								(TManipulateSubType subType, int slot	);
	oCMsgManipulate								(TManipulateSubType subType, const zSTRING& mobScheme, int targetState);
	oCMsgManipulate								(TManipulateSubType subType, const zSTRING& itemName, const zSTRING& slotname);
	oCMsgManipulate								(TManipulateSubType subType, zCVob* vob, int targetState);
	virtual ~oCMsgManipulate					();

		// MetaData	- Subtypes
	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	(int n);

	//			- Parameter
	virtual zSTRING			MD_GetVobRefName	();
	virtual void			MD_SetVobRefName	(const zSTRING & name);
	virtual void			MD_SetVobParam		(zCVob* vob);

	//			- TimeBehavior
	virtual zTTimeBehavior	MD_GetTimeBehavior	();
	virtual zREAL			MD_GetMinTime		();

	virtual zBOOL			IsNetRelevant		()		{ return ((GetSubType()>=EV_INSERTINTERACTITEM) && (GetSubType()<=EV_EQUIPITEM)); };

	/*virtual zBOOL			IsDeleteable		()				
	{ 		
		if (subType == EV_EXCHANGE || (subType >= EV_INSERTINTERACTITEM && subType <= EV_EXCHANGEINTERACTITEM) || subType == EV_EQUIPITEM) return FALSE;
		return TRUE;
	}
	virtual zBOOL			GetIgnoreCutsceneMode()		{ return (!IsDeleteable()); };*/



#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

	zSTRING	name;
	zSTRING slot;
	zCVob*	targetVob;
	zBOOL	flag;				// General purpose Flag
	zREAL	aniCombY;
	union {
		int				npcSlot;
		int				targetState;
		zTModelAniID	aniID;
	};

protected:

	// Archive 
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

	// Pack / Unpack
	virtual void			Pack				(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void			Unpack				(zCBuffer& buffer, zCEventManager* evManContext);
};

class oCMsgConversation : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgConversation)
public:
	enum TConversationSubType {
		EV_PLAYANISOUND = 0,		// Default Anis
		EV_PLAYANI,
		EV_PLAYSOUND,
		EV_LOOKAT,
		EV_OUTPUT,
		EV_OUTPUTSVM,
		EV_CUTSCENE,
		EV_WAITTILLEND,
		EV_ASK,
		EV_WAITFORQUESTION,
		EV_STOPLOOKAT,
		EV_STOPPOINTAT,
		
		EV_POINTAT,
		EV_QUICKLOOK,
		EV_PLAYANI_NOOVERLAY,
		EV_PLAYANI_FACE,

		EV_PROCESSINFOS,
		EV_STOPPROCESSINFOS,
		EV_OUTPUTSVM_OVERLAY,
		EV_SNDPLAY,
		EV_SNDPLAY3D,
		EV_PRINTSCREEN,
		EV_STARTFX,
		EV_STOPFX,
		EV_CONV_MAX
	};

	oCMsgConversation							();
	oCMsgConversation							(TConversationSubType subType);
	oCMsgConversation							(TConversationSubType subType, const zSTRING& aniName);
	oCMsgConversation							(TConversationSubType subType, const zSTRING& sndName, const zSTRING& _text);
	oCMsgConversation							(TConversationSubType subType, zCVob* _target);
	oCMsgConversation							(TConversationSubType subType, int number);
	oCMsgConversation							(TConversationSubType subType, int f_yes, int f_no, zREAL timer);

	/*virtual zBOOL			IsDeleteable		()				
	{ 		
		if (subType == EV_STOPLOOKAT || subType == EV_STOPPOINTAT || subType == EV_STOPFX) return FALSE;
		return TRUE;
	}
	virtual zBOOL			GetIgnoreCutsceneMode()				{ return (!IsDeleteable()); };*/

	
	virtual ~oCMsgConversation					();

	virtual zBOOL			IsOverlay			();				
	virtual	void			Delete				();

		// MetaData	- Subtypes
	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	(int n);

	//			- Parameter
	virtual zSTRING			MD_GetVobRefName	();
	virtual void			MD_SetVobRefName	(const zSTRING & name);
	virtual void			MD_SetVobParam		(zCVob* vob);

	//			- TimeBehavior
	virtual zTTimeBehavior	MD_GetTimeBehavior	();
	virtual zREAL			MD_GetMinTime		();

#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

	zSTRING					text;		// text der gesprochen werden soll/Cutscene-Rolle
	zSTRING					name;		// name der animation/des wave/Cutscene/svm
	zCVob*					target;		// ziel von lookat
	zVEC3					targetPos;
	zTModelAniID			ani;
	union {
		zCModelAni*			cAni;			
		zCEventMessage*		watchMsg;
	};
	zTSoundHandle			handle;
	zREAL					timer;
	int						number;
	int						f_no;
	int						f_yes;

protected:

	// Archive 
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

};

class oCMsgMagic: public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgMagic)
public:
	enum TConversationSubType {
		EV_OPEN		= 0,		
		EV_CLOSE,
		EV_MOVE,
		EV_INVEST,
		EV_CAST,
		EV_SETLEVEL,
		EV_SHOWSYMBOL,
		EV_SETFRONTSPELL,
		EV_CASTSPELL,
		EV_READY,
		EV_UNREADY,
		EV_MAGIC_MAX
	};

	oCMsgMagic									();
	oCMsgMagic									(TConversationSubType subType);
	oCMsgMagic									(TConversationSubType subType, int what, zBOOL removeSymbol = FALSE);

	/*virtual zBOOL			IsDeleteable		()				
	{ 		
		if (subType == EV_INVEST || subType == EV_CAST || subType == EV_CASTSPELL || subType == EV_MOVE) return TRUE;
		return FALSE;
	}

	virtual zBOOL			GetIgnoreCutsceneMode()				{ return (!IsDeleteable()); };*/

	
	virtual ~oCMsgMagic();

	virtual zBOOL			IsJob				()		{ return (GetSubType()==EV_CASTSPELL); };
	virtual zBOOL			IsHighPriority		()		{ return (GetSubType()!=EV_CASTSPELL);  };
	virtual zBOOL			IsNetRelevant		()		{ return FALSE;	};

	// MetaData	- Subtypes
	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	(int n);

#ifdef COMPILING_SPACER
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

	int		what;			// What spellbook ?
	int		level;			// SpellLevel
	zBOOL	removeSymbol;
	int		manaInvested;
	int		energyLeft;
	zCVob*	target;
	zVEC3	targetPos;
	int		activeSpell;	// ActiveSpellNr

protected:

	// Archive 
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

	// Pack / Unpack
	virtual void			Pack				(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void			Unpack				(zCBuffer& buffer, zCEventManager* evManContext);
};

#if defined(SECUROM) && !defined(COMPILING_SPACER)
class oCMsgRequest : public oCNpcMessage
{
zCLASS_DECLARATION	(oCMsgRequest)
public:
	enum TRequestSubType
	{
		EV_REQUEST_0,
		EV_REQUEST_1,
		EV_REQUEST_2,
		EV_REQUEST_3,
		EV_REQUEST_4,
		EV_REQUEST_5,
		EV_REQUEST_6,
		EV_REQUEST_7,
		EV_REQUEST_8,
		EV_REQUEST_9,
		EV_REQUEST_MAX
	};
	
	oCMsgRequest();
	oCMsgRequest(TRequestSubType subType, float delay = 0);
	virtual ~oCMsgRequest();

	virtual zBOOL IsDeleteable() { return FALSE; };

	TRequestSubType subType;
	float delay;

protected:
	virtual void Pack		(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void Unpack		(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void Archive	(zCArchiver& arc);
	virtual void Unarchive	(zCArchiver& arc);
	
};
#endif

#endif
