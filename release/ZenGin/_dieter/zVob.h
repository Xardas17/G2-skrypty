/******************************************************************************** 
 
     $Workfile:: zVob.h               $                $Date:: 24.04.01 17:34   $
     $Revision:: 41                   $             $Modtime:: 16.04.01 16:23   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Engine-level vob-classes: zCVob, zCVobLight, zCVobSound,..
   ("actor","entity","thing")
   created       : 15.4.99

 * $Log: /current_work/ZenGin/_Dieter/zVob.h $
 * 
 * 41    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 40    15.03.01 2:17 Hildebrandt
 * 
 * 39    13.02.01 22:08 Hildebrandt
 * 
 * 38    9.02.01 2:36 Hildebrandt
 * 
 * 37    8.02.01 19:08 Moos
 * 
 * 36    8.02.01 14:53 Moos
 * 
 * 35    8.02.01 6:54 Hildebrandt
 * 
 * 34    1.02.01 2:52 Hildebrandt
 * 
 * 33    25.01.01 2:59 Hildebrandt
 * 
 * 32    23.01.01 18:11 Hildebrandt
 * 
 * 31    14.01.01 16:36 Hildebrandt
 * 
 * 30    10.01.01 17:27 Hildebrandt
 * 
 * 29    8.01.01 17:56 Hildebrandt
 * 
 * 28    20.12.00 3:03 Hildebrandt
 * 
 * 27    5.12.00 19:04 Hildebrandt
 * 
 * 26    17.11.00 1:28 Hildebrandt
 * 
 * 25    8.11.00 18:15 Hildebrandt
 * 
 * 24    7.11.00 17:24 Hildebrandt
 * 
 * 23    3.11.00 19:05 Hildebrandt
 * 
 * 22    26.10.00 2:23 Hildebrandt
 * 
 * 21    25.10.00 15:06 Hildebrandt
 * 
 * 20    12.10.00 23:57 Hildebrandt
 * 
 * 19    11.10.00 19:44 Hildebrandt
 * 
 * 18    7.09.00 19:39 Hildebrandt
 * 
 * 17    1.09.00 18:01 Hildebrandt
 * 
 * 16    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 15    22.08.00 19:47 Hildebrandt
 * 
 * 14    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 13    6.07.00 13:45 Hildebrandt
 * 
 * 5     3.05.00 23:57 Hildebrandt
 * zenGin 089d
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 14    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 13    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 12    22.02.00 2:02 Hildebrandt
 * zenGin 087d
 * 
 * 11    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 9     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 8     10.01.00 21:34 Hildebrandt
 * 
 * 7     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     16.11.99 19:50 Hildebrandt
 * 
 * 4     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 41 $ ($Modtime: 16.04.01 16:23 $)

// ============================================================================================================

#ifndef __ZVOB_H__
#define __ZVOB_H__

// ============================================================================================================

#ifndef __Z3D_H__
#include <z3d.h>
#endif


#ifndef __ZBSP_H__
#include <zBsp.h>
#endif


#ifndef __ZSOUND_H__
#include <zSound.h>
#endif

#ifndef __ZVISUAL_H__
#include <zVisual.h>
#endif

// ============================================================================================================

// declarations
class zCAIBase;				// <zAI.h>
class zCModelNodeInst;		// <zModel.h>
class zCAIBase;				// <zAI.h>
class zCRigidBody;			// <zPhysics.h>
class zCBuffer;				// <zBuffer.h>
class zCBspTree;			// <zBSP.h>
class zCBspLeaf;			
class zCBspBase;
class zCLensFlareFX;		// <zLensflare.h>
class zCClassDef;
class zCEventManager;

class zCCollisionObject;
class zCCollisionObjectDef;
class zCCollisionDetector;
class zCCollisionReport;

// forward
class zCVob;
class zCEventMessage;

// ============================================================================================================

/*
class zCEventInterface {
public:

	// messages a vob can receive (vob<=>vob, engine=>vob)
	// convenience interface
	virtual	void			OnTrigger			(zCVob* otherVob, zCVob *vobInstigator)	{};
	virtual	void			OnUntrigger			(zCVob* otherVob)				{};
	virtual void			OnTouch				(zCVob* otherVob)				{};
	virtual void			OnUntouch			(zCVob* otherVob)				{};
	virtual void			OnTouchLevel		()								{};
	virtual void			OnDamage			(zCVob*			otherVob, 
												 zCVob*			inflictorVob,
												 zREAL			damage, 
												 int			damageType, 
												 const zVEC3&	hitLocation)	{};
												
	// generic messages							
//	virtual void			OnMessage			(zCEventMessage *eventMessage)	{};

	// FIXME: WAS soll hier der 'sourceVob', Ulf ?

	virtual void			OnMessage			(zCEventMessage *eventMessage, zCVob* sourceVob)	{};

};
*/

// included by classes "zCVob" and "zCEventManager"
// no multiple inheritance because of MSVC++ compiler bug

// messages a vob can receive (vob<=>vob, engine=>vob)
// convenience interface
// generic messages							
#define zEVENT_INTERFACE \
	virtual	void			OnTrigger			(zCVob* otherVob, zCVob *vobInstigator)				; \
	virtual	void			OnUntrigger			(zCVob* otherVob, zCVob *vobInstigator)				; \
	virtual void			OnTouch				(zCVob* otherVob)				; \
	virtual void			OnUntouch			(zCVob* otherVob)				; \
	virtual void			OnTouchLevel		()								; \
	virtual void			OnDamage			(zCVob*			otherVob, \
												 zCVob*			inflictorVob, \
												 zREAL			damage,  \
												 int			damageType, \
												 const zVEC3&	hitLocation)	; \
	virtual void			OnMessage			(zCEventMessage *eventMessage, zCVob* sourceVob); 

// ============================================================================================================

typedef zDWORD zTEventMessageID;

class zCEventMessage : public zCObject {
	zCLASS_DECLARATION	(zCEventMessage)
public:
	static void				TestClassIntegrity	();		// tests all derived class in the archiver

	typedef zWORD			zTSubType;
	
	zTSubType				GetSubType			() const { return subType; };
	void					PackToBuffer		(zCBuffer& buffer, zCEventManager* evManContext);
	static zCEventMessage*	CreateFromBuffer	(zCBuffer& buffer, zCEventManager* evManContext);	

	// message properties
	virtual zBOOL			IsOverlay			() { return FALSE; };
	virtual	zBOOL			IsNetRelevant		() { return FALSE; };
	virtual	zBOOL			IsHighPriority		() { return FALSE; };
	virtual zBOOL			IsJob				() { return FALSE; };
	virtual zBOOL			GetIgnoreCutsceneMode(){ return FALSE; };

	// Deleted
	virtual void			Delete				() { };
	virtual zBOOL			IsDeleteable		() { return TRUE;	};
	virtual zBOOL			IsDeleted			() { return FALSE;	};

	// Cutscene - Message
	virtual void			SetCutsceneMode		(zBOOL on)	{ inCutscene = on;	 };
	virtual zBOOL			GetCutsceneMode		()			{ return inCutscene; };

	// MetaData	- Subtypes
	virtual int				MD_GetNumOfSubTypes	()			{ return 0; };
	virtual zSTRING			MD_GetSubTypeString	(int n)		{ return zSTR_EMPTY; };

	//			- Parameter
	virtual zSTRING			MD_GetVobRefName	()			{ return zSTR_EMPTY; };
	virtual void			MD_SetVobRefName	(const zSTRING & name)	{};
	virtual void			MD_SetVobParam		(zCVob* vob)			{};

#ifdef COMPILING_SPACER  
	// für den Cutscene Sequenzer: ein string, der die Parameter enthält ( in gekürzter aussagekräftiger Form )
	virtual zSTRING			MD_GetInfo			()			{ return MD_GetSubTypeString(subType); };
	virtual void			MD_SetInfo			(const zSTRING & str) {};
#endif

	//			- TimeBehavior
	enum zTTimeBehavior {TBZero, TBFix, TBUnknown, TBAssembled};
	virtual zTTimeBehavior	MD_GetTimeBehavior	()			{ return TBZero; };
	virtual zREAL			MD_GetMinTime		()			{ return 0.0F; };		// seconds

protected:
	zTSubType				subType;
	zBOOL					inCutscene;

							zCEventMessage		(const zTSubType subType);
							zCEventMessage		() { subType=0; };		// disable
	static zCEventMessage*	CreateFromID		(zTEventMessageID id);

	//
	zTEventMessageID		GetMessageID		() const;

	// Pack / Unpack
	virtual void			Pack				(zCBuffer& buffer, zCEventManager* evManContext) {};		// dont include ID !
	virtual void			Unpack				(zCBuffer& buffer, zCEventManager* evManContext) {};		// dont include ID !

	// Archive / Unarchive (inherited from zCObject)
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

	//
	virtual					~zCEventMessage		() {};			// use Release() instead !

private:
	// TODO:
	// - flags (high priority,..?)
	// - time stamp
	
	static void				AnalyzeMessageID			(const zTEventMessageID id, zTClassID& outClassID, zTSubType& outSubType) ;
	friend void				TestClassIntegrity_Callback	(zCObject *object, int currentCtr, zCClassDef *classDef, int& numLoops);
};


// ============================================================================================================

class zCEventCore : public zCEventMessage {
	zCLASS_DECLARATION	(zCEventCore)
public:
	enum zTEventCoreSubType {
		zEVENT_TRIGGER=0,
		zEVENT_UNTRIGGER,
		zEVENT_TOUCH,
		zEVENT_UNTOUCH,
		zEVENT_TOUCHLEVEL,
		zEVENT_DAMAGE,
		zEVENT_CORE_NUM_SUBTYPES
	};

	zCEventCore		(const zTEventCoreSubType sub)											{ Clear(); subType = zTSubType(sub); };
	zCEventCore		(const zTEventCoreSubType sub, zCVob* inOtherVob)						{ Clear(); subType = zTSubType(sub); otherVob = inOtherVob; };
	zCEventCore		(const zTEventCoreSubType sub, zCVob* inOtherVob, zCVob* inInstigator)	{ Clear(); subType = zTSubType(sub); otherVob = inOtherVob; vobInstigator=inInstigator; };
	zCEventCore		(const zTEventCoreSubType sub, 
					 zCVob* inOtherVob, zCVob* inInflictorVob, const zREAL dam, const int damType=0, const zVEC3& hitLoc=zVEC3(0))	
						{ Clear(); subType = zTSubType(sub); otherVob = inOtherVob; inflictorVob = inInflictorVob; damage = dam; damageType=damType; hitLocation=hitLoc; };

	// zCEventMessage Interface
	virtual	int				MD_GetNumOfSubTypes	()	{ return zEVENT_CORE_NUM_SUBTYPES; };
	virtual	zSTRING			MD_GetSubTypeString	(int n);
	virtual	zBOOL			IsNetRelevant		()	{ return !((subType>=zEVENT_TOUCH) && (subType<=zEVENT_TOUCHLEVEL)); };

	// subType specific interface
	zCVob*					GetOtherVob			() const { return otherVob;		};

	// zEVENT_TRIGGER, zEVENT_UNTRIGGER
	zCVob*					GetVobInstigator	() const { return vobInstigator;};

	// zEVENT_DAMAGE
	zREAL					GetDamage			() const { return damage;		};
	int						GetDamageType		() const { return damageType;	};
	zCVob*					GetInflictorVob		() const { return inflictorVob;	};
	zPOINT3					GetHitLocation		() const { return hitLocation;	};

protected:
	zCEventCore () { Clear(); };

	// Pack / Unpack
	virtual void			Pack				(zCBuffer& buffer, zCEventManager* evManContext);
	virtual void			Unpack				(zCBuffer& buffer, zCEventManager* evManContext);

	// Archive / Unarchive
	virtual void			Archive				(zCArchiver& arc);
	virtual void			Unarchive			(zCArchiver& arc);

	virtual					~zCEventCore		();			// use Release() instead !
private:
	zCVob*					otherVob;
	
	// zEVENT_TRIGGER, zEVENT_UNTRIGGER
	zCVob*					vobInstigator;		

	// zEVENT_DAMAGE
	zREAL					damage;
	int						damageType;
	zCVob*					inflictorVob;
	zPOINT3					hitLocation;

	//
	void					Clear				();
};

/*
unklar:
- EventInterface Virtuals sicher machen (def-param)
- pack/arc kontext, vobs saven ? namen/id?
- den Sender in das Base-Class Interface aufnehmen ?
x enum-Stringliste im ::archive => keine Hierarchiene erlaubt, in denen jede Klasse einen subType hat!
x subType aus Base-Class werfen ? dort nur das virt GetSubTpye ?
*/

// ============================================================================================================

///////////////////////////////////////////////////////////////////////////
//    VOB
///////////////////////////////////////////////////////////////////////////

/*
	Translation/Rotation:
	local => relativ to local coordinate system
	world => relativ to "world"
	
		"local" (or nothing) means:
		- rotation axis and translations are given in the vob's "local coordinate system"
	    "world" means:
	  	- rotation axis and translations are given in the "world's coordinate system"
	
	- translate (relativ)
		- local system						MoveLocal
		- world system						Move
	- rotate 
		- local system						RotateLocal
		- world system (in place)			Rotate
		- world system (distant origin)		RotateWorld / RotateDistant 		// need this ??
*/

enum zTVobType {		zVOB_TYPE_NORMAL, 
						zVOB_TYPE_LIGHT,
						zVOB_TYPE_SOUND,
						// only present in the Level-Editor's construction phase
						zVOB_TYPE_LEVEL_COMPONENT,
						// helper-Vobs
						zVOB_TYPE_SPOT,
						zVOB_TYPE_CAMERA,
						zVOB_TYPE_STARTPOINT,
						zVOB_TYPE_WAYPOINT,
						zVOB_TYPE_MARKER,
						zVOB_TYPE_SEPARATOR=127,
						// FIXME: move this out of here !
						zVOB_TYPE_MOB=128, zVOB_TYPE_ITEM=129, zVOB_TYPE_NSC=130 };

enum zTVobSleepingMode {zVOB_SLEEPING				=0, 
						zVOB_AWAKE					=1,  
						zVOB_AWAKE_DOAI_ONLY		=2 
					}; // ATT: keep in sync with bitfield size

enum zTAnimationMode {
						zVISUAL_ANIMODE_NONE	= 0,
						zVISUAL_ANIMODE_WIND,
						zVISUAL_ANIMODE_WIND2,
					};


typedef zDWORD		 zTVobID;
#define zVOB_ID_NULL zTVobID(0)

class zENGINE_API zCVob : public zCObject {
	zCLASS_DECLARATION	(zCVob)
public:					
						
	zCTree<zCVob>		*globalVobTreeNode;					// => zCWorld.globalVobTree
	zTFrameCtr			lastTimeDrawn;
	zDWORD				lastTimeCollected;

	zCArray<zCBspLeaf*>	vobLeafList;
	zMATRIX4			trafoObjToWorld;					// [S]
	zTBBox3D			bbox3D;//WorldSpace;				// [S] in worldSpace

	// opti für statische vobs
	zTBSphere3D			bsphere3D;

public:

	zEVENT_INTERFACE

	// methods
	static void			InitVobSystem				();
	static void			CleanupVobSystem			();
	static zBOOL		GetIgnoreVisuals			()					{ return s_ignoreVisuals;		};
	static void			SetIgnoreVisuals			(zBOOL b)			{ s_ignoreVisuals		= b;	};
	static void			SetRenderVobs				(const zBOOL b)		{ s_renderVobs			= b;	};
	static zBOOL		GetRenderVobs				()					{ return s_renderVobs;			};
	static void			SetShowHelperVisuals		(const zBOOL b)		{ s_showHelperVisuals	= b;	};
	static zBOOL		GetShowHelperVisuals		()					{ return s_showHelperVisuals;	};
	static zBOOL		GetAnimationsEnabled		()					{ return s_enableAnimations;	};
	static void			SetAnimationsEnabled		(const zBOOL en)    { s_enableAnimations = en;		};

			 zCVob();
protected:
	virtual ~zCVob();		// use Release() instead !
public:
	void				SetCollTypeDefaultFromVisual(); 

	// removing this vob/vobTree from world (the world is called within)
	void				RemoveVobSubtreeFromWorld	();						// shortcut for: GetHomeWorld()->RemoveVob		 (this)
	void				RemoveVobFromWorld			();						// shortcut for: GetHomeWorld()->RemoveVobSubtree(this)

	void				DoFrameActivity				();						// called by world, calls OnTick,OnTimer
	virtual void		OnTick						() {};					// called, if vob is not sleeping
	virtual void		OnTimer						() {};					// called on time, if vob is not sleeping

	//
	void				SetOnTimer					(zREAL deltaTime);
	zBOOL				IsOnTimer					() const;				// is scheduled onTimer ?
	void				ResetOnTimer				();						// cancels current OnTimer schedule

	zCEventManager*		GetEventManager				(const zBOOL dontCreateIfNotPresent=FALSE)		{ return GetEM(dontCreateIfNotPresent);		};
   	zCEventManager*		zCCFASTCALL		GetEM 		(const zBOOL dontCreateIfNotPresent=FALSE);
	virtual void		PostLoad					()						{ };						// is called after whole level is loaded, before game loop starts

	zBOOL				IsTouching					(zCVob *otherVob)		{ return touchVobList.IsInList (otherVob); };
	
	enum zTVobCharClass	{ zVOB_CHAR_CLASS_NONE, 
						  zVOB_CHAR_CLASS_PC, 
						  zVOB_CHAR_CLASS_NPC
						};
	virtual zTVobCharClass GetCharacterClass		()						{ return zVOB_CHAR_CLASS_NONE; };


	virtual void		SetSleepingMode				(const zTVobSleepingMode smode);
	zTVobSleepingMode	GetSleepingMode				() const				{ return zTVobSleepingMode(sleepingMode);	};
	void				SetSleeping					(const zBOOL sleep);
	zBOOL				GetSleeping					() const				{ return (sleepingMode==zVOB_SLEEPING);		};
	void				SetPhysicsEnabled			(const zBOOL enable);
	zBOOL				GetPhysicsEnabled			() const				{ return physicsEnabled;	};
	void				SetStaticVob				(const zBOOL stat)		{ staticVob=stat;			};
	zBOOL				GetStaticVob				() const				{ return staticVob;			};
	void				SetIgnoredByTraceRay		(const zBOOL i)			{ ignoredByTraceRay = i;	};
	zBOOL				GetIgnoredByTraceRay		() const				{ return ignoredByTraceRay; };

	// Movement-Transaction / Collision / Physics
	void				BeginMovement				();		// starts transaction, only 1 vob (with enabled coll-flags) can be in this transaction state
	virtual void		EndMovement					(const zBOOL a_bHintTrafoChanged=TRUE);		// ends transaction
	virtual zBOOL		CanThisCollideWith			(zCVob* vob)			{ return TRUE; };	// gives derived vobs the possibility to exclude special other vobs from collDet and collResp
	void				ResetToOldMovementState		();
	zBOOL				GetInMovement				() const				{ return (isInMovementMode!=zVOB_MOVE_MODE_NOTINBLOCK); };
	enum zTMovementMode { zVOB_MOVE_MODE_NOTINBLOCK=0, zVOB_MOVE_MODE_INBLOCK, zVOB_MOVE_MODE_INBLOCK_NOCD };	// (att: keep bitfield in sync)
	zTMovementMode		GetInMovementMode			() const				{ return zTMovementMode(isInMovementMode); };
	enum				{ zVOB_CDMODE_EXACT, zVOB_CDMODE_SPEEDBOX, zVOB_CDMODE_ALL };
	zBOOL				DetectCollision				(zMATRIX4 *trafoObjToWorldNew=0);	// if a 'trafoObjToWorldNew' is specified, dynamic collision is tested from its current pos/rot to the specified destination; in this case the current state is supposed to be collision-free and within the world
	zCRigidBody*		GetRigidBody				();
	zVEC3				GetVelocity					();						// units: cm/sec
	void				SetFarClipZScale			(const zREAL a_fFarZScale){ m_fVobFarClipZScale = a_fFarZScale;	};
	zREAL				GetFarClipZScale			()	const				{ return m_fVobFarClipZScale;	};

	zCPolygon*			GetGroundPoly				() const				{ return groundPoly;	};
	void				SetGroundPoly				(zCPolygon* poly)		{ groundPoly=poly;		};
	void				CalcGroundPoly				();
	void				CalcWaterVob				();
	zBOOL				GetIsInWater				() const				{ return bIsInWater;	};
	zBOOL				GetIsProjectile				() const;
													
	void				SetAICallback				(zCAIBase* cbai)		{ SetAI (cbai);			};
	zCAIBase*			GetAICallback				() const				{ return GetAI();		};
	void				SetAI						(zCAIBase* cbai);
	zCAIBase*			GetAI						() const				{ return callback_ai;	};

	zTVisualCamAlign	GetVisualCamAlign			() const						{ return visualCamAlign; };
	void				SetVisualCamAlign			(const zTVisualCamAlign a)		{ visualCamAlign=a; };

	void				SetVisualAlphaEnabled		(const zBOOL b)		{ visualAlphaEnabled=b;			};
	zBOOL				GetVisualAlphaEnabled		() const			{ return visualAlphaEnabled;	};
	void				SetVisualAlpha				(const zREAL a)		{ visualAlpha=a;				};
	zREAL				GetVisualAlpha				() const			{ return visualAlpha;			};

	// visual animation
	void				SetVisualAniMode			(const zTAnimationMode &aniMode)	{ m_AniMode = aniMode; };
	zTAnimationMode		GetVisualAniMode			()	const							{ return m_AniMode;    };
	void				SetVisualAniModeStrength	(zREAL aniModeStrength)				{ m_aniModeStrength = aniModeStrength; };
	zREAL				GetVisualAniModeStrength	()  const							{ return m_aniModeStrength; };

	// z-Biasing
	int					GetZBias					() const							{ return m_zBias;	};
	void				SetZBias					(const a_iZBias)					{ m_zBias = a_iZBias;};

	// Ambient Flags
	int					GetIsAmbient				() const							{ return bIsAmbientVob;	};
	void				SetIsAmbient				(const a_b)							{ bIsAmbientVob = a_b;};


	void				CalcRenderAlpha				(const zREAL distVobToCam, zCVisual* &activeVisual, zREAL& alpha);

	void				SetVobName					(const zSTRING& n);
	const zSTRING&		GetVobName					() const			{ return GetObjectName();	};
	void				SetVobType					(const zTVobType t)	{ type = t;					};
	zTVobType			GetVobType					() const			{ return type;				};
	void				SetShowVisual				(zBOOL show)		{ showVisual = show;		};
	zBOOL				GetShowVisual				() const			{ return showVisual;		};
	const zTBBox3D&		GetBBox3DWorld				() const			{ return bbox3D;			};
	void				SetBBox3DWorld				(const zTBBox3D& b);
	zTBBox3D			GetBBox3DLocal				() const;
	void				SetBBox3DLocal				(const zTBBox3D& b);
													
	virtual zBOOL zCCFASTCALL  Render				(zTRenderContext &renderContext);		// TRUE=visible, FALSE=invisible
	virtual void		SetVisual					(zCVisual *v);						// does implicit 'AddRef' on input-visual
	virtual void		SetVisual					(const zSTRING& visualFileName);	// loads&assigns visual from File, shares visual if already in memory
	zCVisual*			GetVisual					() const			{ return visual;		};
	zCClassDef*			GetVisualClass				() const			{ return (visual ? visual->GetClassDef() : 0); };	// convenience method
	zBOOL				GetDrawBBox3D				() const			{ return drawBBox3D;	};
	void				SetDrawBBox3D				(zBOOL b)			{ drawBBox3D=b;			};
	zBOOL				RegisteredInWorld			() const			{ return (homeWorld!=0);/*((globalVobTreeNode!=0) && (bspTreeNode!=0));*/ };
	void				SetHomeWorld				(zCWorld* world)	{ homeWorld = world;	}; 
	zCWorld*			GetHomeWorld				() const			{ return homeWorld;		}; 
	const zSTRING*		GetSectorNameVobIsIn		() const;		// returns the name of the sector (portal-enclosed), if vob is within a sector(determined by groundPoly); returns 0 if not in sector
	
	//												
	void				SetCollDet					(const zBOOL b)		{ SetCollDetStat(b); SetCollDetDyn(b); };
	void	zCCFASTCALL SetCollDetStat				(const zBOOL b);
	zBOOL				GetCollDetStat				() const			{ return collDetectionStatic; };
	void	zCCFASTCALL SetCollDetDyn				(const zBOOL b);
	zBOOL				GetCollDetDyn				() const			{ return collDetectionDynamic; };

	enum zTDynShadowType {
		zDYN_SHADOW_TYPE_NONE=0,
		zDYN_SHADOW_TYPE_BLOB,
		zDYN_SHADOW_TYPE_COUNT
	};
	void				SetCastDynShadow			(const zTDynShadowType b)		{ castDynShadow=b;						};
	zTDynShadowType		GetCastDynShadow			() const						{ return zTDynShadowType(castDynShadow);};

	// lighting
	zCOLOR				CalcLightSampleAtOrigin		();			// calcs combined static and dyn lighting of vob, results are cached until dirty, assert: vob has HomeWorld
	zCOLOR				GetLightColorStat			();
	zCOLOR				GetLightColorStatGroundPoly	();
	zCOLOR				GetLightColorDyn			();
	void				SetLightColorDynDirty		()					{ lightColorDynDirty	= TRUE; };
	zBOOL				GetLightColorDynDirty		() const			{ return lightColorDynDirty;	};
	void				SetLightColorStatDirty		()					{ lightColorStatDirty	= TRUE; };
	zBOOL				GetLightColorStatDirty		() const			{ return lightColorStatDirty;	};
	void				SetLightDirectionStat		(const zVEC3& dir) 	{ lightDirectionStat	= dir;	};
	const zVEC3&		GetLightDirectionStat		() const			{ return lightDirectionStat;	};
	
	inline zTVobID		GetVobID					() const			{ return zTVobID(1);			};		// not in use currently..
	void				SetVobID					(const zTVobID& id);
	static zTVobID		GetNextFreeVobID			();
	static void			ResetIDCtr					();
	
	zVALUE				GetDistanceToVob			(zCVob& v);
	zVALUE				GetDistanceToVob2			(zCVob& v);			// RETURN zVALUE = squared distance
	zVALUE				GetDistanceToVobApprox		(zCVob& v);			// approximation
	void				GetAziElev					(const zCVob& vob, zVALUE& azi, zVALUE& elev) const { Alg_CalcAziElev (vob.GetPositionWorld() - GetPositionWorld(), azi, elev); };

	// DScript related (ask 'zCClassDef' if class is scripted and the following methods are supported)
	virtual zBOOL		GetScriptInstance			(zSTRING* &scriptInstanceName, int &scriptInstanceIndex)			{ scriptInstanceName=0; scriptInstanceIndex=0; return FALSE;	};	// returns name/index, as available
	virtual zBOOL		SetByScriptInstance			(const zSTRING* scriptInstanceName, const int scriptInstanceIndex)	{ return FALSE;	};	// use 'name' or 'index' exclusively, but not both
	// GetScriptedMode () => dataScripted, genericScripted

	// Cutscene specific
	virtual int			GetCSStateFlags				()									{ return 0;		};				

	// Position / Rotation							
	void				Move (zVALUE x, zVALUE y, zVALUE z);
	void				Move (const zVEC3& trans)										{ Move(trans[0], trans[1], trans[2]); };

    zMAT4&              GetTrafoLocal               ()									{ if (!trafo) CreateTrafoLocal(); return *trafo;}  // the vob´s transformation matrix relative to its parent vob
    const zMAT4&        GetTrafoLocal               () const							{ if (!trafo) CreateTrafoLocal(); return *trafo;}  // the vob´s transformation matrix relative to its parent vob
    void                DoneWithTrafoLocal          ();                                                         // destroy the local matrix again if the vob has no parent
    void                CreateTrafoLocal            () const;                                                   // create the local matrix

	void				MoveLocal					(const zVALUE x, const zVALUE y, const zVALUE z);
	void				MoveLocal					(const zPOINT3& dir)			{ MoveLocal (dir.n[VX], dir.n[VY], dir.n[VZ]); };
	void				MoveWorld					(const zVALUE x, const zVALUE y, const zVALUE z);
	void				MoveWorld					(const zPOINT3& dir)			{ MoveWorld (dir.n[VX], dir.n[VY], dir.n[VZ]); };
	void				SetPositionLocal			(const zPOINT3& pos);
	void				SetPositionLocal			(const zVALUE x, const zVALUE y, const zVALUE z)  { SetPositionLocal (zPOINT3(x,y,z)); };
	void				SetPositionWorld			(const zPOINT3& pos);
	void				SetPositionWorld			(const zVALUE x, const zVALUE y, const zVALUE z)  { SetPositionWorld (zPOINT3(x,y,z)); };
	zPOINT3				GetPositionWorld			() const						{ return trafoObjToWorld.GetTranslation (); };
	void				GetPositionWorld			(zPOINT3& pos) const			{ trafoObjToWorld.GetTranslation (pos); };
	void				GetPositionWorld			(zVALUE& x, zVALUE& y, zVALUE& z) const;
	zPOINT3				GetPositionLocal			() const						{ return GetTrafoLocal().GetTranslation (); };
	void				GetPositionLocal			(zPOINT3& pos) const			{ GetTrafoLocal().GetTranslation (pos); };
	void				GetPositionLocal			(zVALUE& x, zVALUE& y, zVALUE& z) const;
	void				SetRotationWorld			(const zCQuat& quat);		// sets rotation absolut
	void				RotateWorld					(const zCQuat& quat);		// rotates relative
	void				RotateWorld					(const zVALUE x, const zVALUE y, const zVALUE z, const zVALUE angle)	{ RotateWorld (zVEC3(x,y,z), angle); };
	void				RotateWorld					(const zVEC3& rotAxis, const zVALUE angle);
	void				RotateWorldX				(const zVALUE angle);
	void				RotateWorldY				(const zVALUE angle);
	void				RotateWorldZ				(const zVALUE angle);
	void				RotateLocal					(const zVALUE x, const zVALUE y, const zVALUE z, const zVALUE angle)	{ RotateLocal (zVEC3(x,y,z), angle); };
	void				RotateLocal					(const zVEC3& rotAxis, const zVALUE angle);
	void				RotateLocalX				(const zVALUE angle);
	void				RotateLocalY				(const zVALUE angle);
	void				RotateLocalZ				(const zVALUE angle);
	zPOINT3				GetAtVectorWorld			() const { return trafoObjToWorld.GetAtVector(); };
	zPOINT3				GetUpVectorWorld			() const { return trafoObjToWorld.GetUpVector(); };
	zPOINT3				GetRightVectorWorld			() const { return trafoObjToWorld.GetRightVector(); };
	void				ResetRotationsLocal			();		// reset relative to parent coordinate system
	void				ResetRotationsWorld			();		// reset relative to world coordinate system
	void				ResetXZRotationsLocal		();		// reset relative to parent coordinate system
	void				ResetXZRotationsWorld		();		// reset relative to world coordinate system
	void				SetHeadingAtLocal			(const zVEC3& newAtVector);		// at vector must be normalized
	void				SetHeadingAtWorld			(const zVEC3& newAtVector);		// at vector must be normalized
	void				SetHeadingWorld				(zCVob* targetVob);
	void				SetHeadingLocal				(const zPOINT3& targetPos);
	void				SetHeadingWorld				(const zPOINT3& targetPos);
	void				SetHeadingYWorld			(zCVob* targetVob);
	void				SetHeadingYLocal			(const zPOINT3& targetPos);
	void				SetHeadingYWorld			(const zPOINT3& targetPos);
	void				SetTrafo					(const zMATRIX4& intrafo);
	void				SetTrafoObjToWorld			(const zMATRIX4& intrafo);
	zMATRIX4			GetTrafoModelNodeToWorld	(const zSTRING& modelNodeName);
	zMATRIX4			GetTrafoModelNodeToWorld	(zCModelNodeInst *modelNode);
	void				TouchMovement				();
	// 'new trafo' is only defined within BeginMovement()/EndMovement() Blocks and represents the accumulated, un-cd-tested current state
	const zMATRIX4&		GetNewTrafoObjToWorld		() const;
	zMATRIX4&			GetNewTrafoObjToWorld		();
	void				SetNewTrafoObjToWorld		(const zMATRIX4& newTrafo);
	// 'old trafo' is always defined, this is the last testet, collisionfree state. Does not change within a Begin/EndMove() block, EndMove() updates this though.
	const zMATRIX4&		GetOldTrafoObjToWorld		() const	{ return trafoObjToWorld; };
	zMATRIX4&			GetOldTrafoObjToWorld		()			{ return trafoObjToWorld; };

	// misc
	void				UpdateVisualDependencies	(const zBOOL a_bHintTrafoChanged=TRUE);
	zCOLOR				GetLightColorAtCenter		() const;
	zTBBox2D			GetScreenBBox2D				();
	zSTRING				GetVobInfo					();			// debug
	zBOOL				HasParentVob				() const { return ((globalVobTreeNode) && (globalVobTreeNode->GetParent()) && globalVobTreeNode->GetParent()->GetData()); };
	void				SetDontWriteIntoArchive		(const zBOOL b)	{ dontWriteIntoArchive= b;		};		// this vob (and it's subtree) isn't written into an archive if this flag is set (e.g. for unimportant/transient effect objects)
	zBOOL				GetDontWriteIntoArchive		() const		{ return dontWriteIntoArchive;	};

	// traceRay, ray defined in worldSpace
	virtual zBOOL		TraceRay					(	const zVEC3&		rayOrigin, 
														const zVEC3&		ray, 
														const int			traceFlags, 
														zTTraceRayReport	&report);

	// znet, binary state packing/unpacking
	void				PackStateBinary				(zCBuffer& buffer) const;
	void				UnpackStateBinary			(zCBuffer& buffer);

	// 'Auto-Linking' between zCMover and other vobs
	static zCVob*		GetAutoLinkParent			(zCVob *childVob);
	static zBOOL		CanAutoLinkWith				(zCVob *childVob, zCVob *parentVob=0);
	static void			CheckAutoLink				(zCVob *childVob, zCVob *parentVob=0);
	static void			CheckAutoUnlink				(zCVob *childVob);

	// Collision Model / Limb(Model)
	struct zTModelLimbColl {
		zCVob					*hitVob;
		zCMaterial				*hitMaterial;
		zCList<zCModelNodeInst> hitModelNodeList;
		zPOINT3					approxCollisionPos;
	};

	// detectet model/limb collisions are reported in 'resCollList'
	// ATTENTION: resCollList.DeleteListDatas() has to be called, to delete it's contents entirely from memory !!
	//            if not: mem-leaks.
	void				CheckModelLimbCollision	(	zCModelNodeInst			*weaponNode, 
													const zBOOL				findApproxCollisionPos,
													zCList<zTModelLimbColl> &resCollList);

	void				CheckModelLimbCollisionLevel(zCModelNodeInst			*weaponNode, 
													const zBOOL				findApproxCollisionPos,
													zCList<zTModelLimbColl> &resCollList);

	void				CheckModelLimbCollisionPolys(zCModelNodeInst		*weaponNode, 
													const zBOOL				findApproxCollisionPos,
													zCPolygon**				polyList,
													const int&				polyNum,
													zCList<zTModelLimbColl> &resCollList);



	// VobPresets (for Spacer-Tool)
	virtual const zSTRING*	GetTriggerTarget		(const int i=0) const		{ return 0;						};	// if any, for Spacer-Tool; last=0
	void				SetVobPresetName			(const zSTRING& presetName);
	const zSTRING&		GetVobPresetName			() const;

	void				AddRefVobSubtree			(zCTree<zCVob>* node=0, const zBOOL a_bLightChildsMove=TRUE);
	void				ReleaseVobSubtree			(zCTree<zCVob>* node=0);

	// "protected" DONT CALL DIRECTLY
	// Is called for everytime this vob is addedTo/removedFrom the world, opportunity for derived classes to plug in own code, 
	// called AFTER the actual addition. Derived implementations should call the base class methods.
	virtual void		ThisVobAddedToWorld			(zCWorld *homeWorld);		// called AFTER the actual addition
	virtual void		ThisVobRemovedFromWorld		(zCWorld *homeWorld);		// called BEFFORE the actual removal
	void				RemoveWorldDependencies		(zBOOL removeFromGlobalVobTree);
	void				RemoveVobFromBspTree		();
	void				RemoveVobFromGlobalVobTree	(); 

	void				AddVobToWorld_CorrectParentDependencies();

protected: 
	// methods
	// explicity disable copy-contstructor and assignment-operator
//	zCVob				(const zCVob&);
//	zCVob&				operator=(const zCVob&);

	// persistance
	virtual void		Archive								(zCArchiver &arc);
	virtual void		Unarchive							(zCArchiver &arc);

	zCArray<zCVob*>		touchVobList;

	static void			RepairIllegalFloats					(zMAT4& matrix);		// tries to repair this pos/rot matrix, if illegal floats are present

private:
	// data
	static zBOOL		s_ignoreVisuals;						// for tools
	static zCMesh*		s_shadowMesh;
	static zTVobID		s_nextFreeID;
	static zBOOL		s_vobAlreadyInMovement;
	static zBOOL		s_renderVobs;
	static zBOOL		s_showHelperVisuals;
	static zBOOL		s_enableAnimations;

	void				ProcessOnTimer					();
	void	zCCFASTCALL	SetInMovement					(zBOOL b);
	void	zCCFASTCALL	SetInMovementMode				(zTMovementMode moveMode);
	void				SetMovementHintTrafoLocalConst	(const zBOOL b)		{ mbHintTrafoLocalConst = b;		};
	zBOOL				GetMovementHintTrafoLocalConst	() const			{ return mbHintTrafoLocalConst;		};	
	void				SetInsideEndMovementMethod		(const zBOOL b)		{ mbInsideEndMovementMethod = b;	};
	zBOOL				GetInsideEndMovementMethod		() const			{ return mbInsideEndMovementMethod;	};
														
	void				UpdatePhysics					();
	void	zCCFASTCALL	UpdateTouchList					(const zCArray<zCVob*> &newTouchVobList);
	void	zCCFASTCALL	CalcDestinationBBox3DWorld		(zTBBox3D &resultBBox3D) ;

	zTVobType			type;								// [S]
//	zTVobID				vobID;
	zDWORD				groundShadowSizePacked;					// size of current shadowX/Y, cached for smoothing lerp, quantized and packed
	zCWorld				*homeWorld;
	zCPolygon			*groundPoly;
	zCAIBase			*callback_ai;
	zMATRIX4			*trafo;								// [S]

	zCVisual			*visual;							// visualisation
	zREAL				visualAlpha;
	zREAL				m_fVobFarClipZScale;
	zTAnimationMode		m_AniMode;
	zREAL				m_aniModeStrength;
	int					m_zBias;

	zCRigidBody			*rigidBody;

	zCOLOR				lightColorStat;						// lighting samples are cached for whole vob/visual, recalc if dirty
	zCOLOR				lightColorDyn;
	zVEC3				lightDirectionStat;					// ATT: pack this?
	zSTRING				*vobPresetName;						// [S]

	zCEventManager		*eventManager;
	zREAL				nextOnTimer;						// [S]
	// flags
	struct {			// 29 Bits
		zUINT8			showVisual					: 1;	// [S]
		zUINT8			drawBBox3D					: 1;	// [S]
		zUINT8			visualAlphaEnabled			: 1;	
		zUINT8			physicsEnabled				: 1;	// [S]
		zUINT8			staticVob					: 1;	// [S] no reactions to collision, fixed in place
		zUINT8			ignoredByTraceRay			: 1;	
		zUINT8			collDetectionStatic			: 1;	// [S]
		zUINT8			collDetectionDynamic		: 1;	// [S]
		zUINT8			castDynShadow				: 2;	// zTDynShadowType
		zUINT8			lightColorStatDirty			: 1;	
		zUINT8			lightColorDynDirty			: 1;	
		zTMovementMode	isInMovementMode			: 2;	// zTMovementMode
		zUINT8			sleepingMode				: 2;	// zTVobSleepingMode	
		zUINT8			mbHintTrafoLocalConst		: 1;	// defined within movementBlock, if set trafoLocal remains constant (trafoObjToWorld not) and does not have to be recomputed
		zUINT8			mbInsideEndMovementMethod	: 1;
		zTVisualCamAlign visualCamAlign				: 2;
		zUINT8			collButNoMove				: 4;
		zUINT8			dontWriteIntoArchive		: 1;	// this vob (and it's subtree) isn't written into an archive if this flag is set (e.g. for unimportant/transient effect objects)
		zUINT8			bIsInWater					: 1;
		zUINT8			bIsAmbientVob				: 1;
	};	

	static void			LoadGroundShadowMesh		();
	static void			DeleteGroundShadowMesh		();
	zBOOL	zCCFASTCALL	CalcStaticLight				(zVEC3& color) const;
	void	zCCFASTCALL	RenderGroundShadow			(zTRenderContext& renderContext);
	zCVisual*			GetClassHelperVisual		() const;
	void	zCCFASTCALL	SetGroundShadowSize			(const zVEC2& sizeXY);
	zVEC2	zCCFASTCALL	GetGroundShadowSize			() const;

	// archive/unarchive
	void	zCCFASTCALL	ArchivePacked				(zCArchiver &arc);
	void	zCCFASTCALL	ArchiveVerbose				(zCArchiver &arc);
	void	zCCFASTCALL	UnarchivePacked				(zCArchiver &arc, int pack);
	void	zCCFASTCALL	UnarchiveVerbose			(zCArchiver &arc);

	// ==========================================================================================================

public:
	//
	void				SetCollisionObject				(zCCollisionObject* collObject);
	void				SetCollisionClass				(zCCollisionObjectDef* collClass);
	zCCollisionObjectDef* GetCollisionClass				() const							{ return m_poCollisionObjectClass; };
	zCCollisionObject*	GetCollisionObject				() const;	// can return 0 outside movementBlock if collObjectClass is volatile
	void				CreateCollisionObject	 		();		// creates, if not already present
	void	zCCFASTCALL	DestroyCollisionObject			(const zBOOL destroyEvenIfVolatile=FALSE);		// deletes, if objectClass is volatile

	static zCCollisionDetector* S_GetCollisionDetector	() { return s_poCollisionDetector; };

private:

	//
	struct zTCollisionContext;
	void	zCCFASTCALL	CollectCollisionContext_Vobs	(const zTBBox3D& speedBox, zTCollisionContext &collisionContext);
	void	zCCFASTCALL	CollectCollisionContext_Static	(const zTBBox3D& speedBox, zCArray<zCCollisionObject*> &otherCollObjectList);
	void	zCCFASTCALL	CollectCollisionContext			(      zTCollisionContext &collisionContext);
	void	zCCFASTCALL CleanupCollisionContext			(const zTCollisionContext &collisionContext);
	void	zCCFASTCALL NotifyCollisionPair				(zCCollisionReport *collReport, const zCArray<zCCollisionReport*> &collReportList, zBOOL dontSendTouchMessages=FALSE);
	void	zCCFASTCALL	ExecuteCollisionResponse		(const zCArray<zCCollisionReport*> &collReportList, zBOOL& simulateFurther);
	void				CheckAndResolveCollisions		();		// checks for collisions and tries to resolve them through collResponses into a collision free new state 
	zBOOL				IsColliding						();		// simple collision check, returns true if object is currently colliding (i.e. "stuck"), soft-collisions don't count (i.e. triggerBoxes)

	//
	void				ResetCollisionObjectState		();


	//
	zCCollisionObjectDef*			m_poCollisionObjectClass;
	zCCollisionObject*				m_poCollisionObject;
	static zCCollisionDetector*		s_poCollisionDetector;

	void				AdoptCollObjResults				();
	void				CheckEmergencyPutToSleep		();

	// ==========================================================================================================

//	friend class zCWorld;
	friend zCEventManager;

private:
	void				CorrectTrafo				();
};


// ============================================================================================================

enum zTVobLightType
{
	zVOBLIGHT_TYPE_POINT	= 0	,
	zVOBLIGHT_TYPE_SPOT			,
	zVOBLIGHT_TYPE_DIR			,	// [not available yet]	
	zVOBLIGHT_TYPE_AMBIENT			// [not available yet]	
	// change zCVobLightData bitfield member if adding enums
};

enum zTVobLightQuality
{
	zVOBLIGHT_QUAL_HI		= 0	,
	zVOBLIGHT_QUAL_MID			,
	zVOBLIGHT_QUAL_FASTEST			
	// change zCVobLightData bitfield member if adding enums
};

class zCVobLight;
class zCVobLightData;
class zCVobLightPreset;

class zCVobLightData {
public:
	zCArray<zVALUE>		rangeAniScaleList;
	zCArray<zCOLOR>		colorAniList;

	zTVobLightType		GetLightType		()  const						{ return zTVobLightType(lightType);		};
	void				SetLightType		(const zTVobLightType ltype)	{ lightType=ltype;						};
	zREAL				GetSpotConeAngle	() const						{ return spotConeAngleDeg;				};
	void				SetSpotConeAngle	(const zREAL spotConeAngle)		{ this->spotConeAngleDeg=spotConeAngle; };

	zBOOL				IsRangeAnimated		() const			{ return (rangeAniFPS!=0) && (rangeAniScaleList.GetNumInList()>0); };
	void				SetRangeAniFPS		(const zVALUE fps)	{ rangeAniFPS=fps / 1000; rangeAniActFrame=0; };
	zREAL				GetRangeAniFPS		() const			{ return rangeAniFPS * 1000; };
	void				SetRangeAniSmooth	(const zBOOL  b)	{ rangeAniSmooth = b; };
	zBOOL				GetRangeAniSmooth	() const			{ return rangeAniSmooth; };
	void				SetRangeAniLoop		(const zBOOL  b)	{ rangeAniLoop= b; };
	zBOOL				GetRangeAniLoop		() const			{ return rangeAniLoop; };

	zBOOL				IsColorAnimated		() const			{ return (colorAniFPS!=0) && (colorAniList.GetNumInList()>0); };
	void				SetColorAniFPS		(const zVALUE fps)	{ colorAniFPS=fps / 1000; colorAniActFrame=0; };
	zREAL				GetColorAniFPS		() const			{ return colorAniFPS * 1000; };
	void				SetColorAniSmooth	(const zBOOL  b)	{ colorAniSmooth = b; };
	zBOOL				GetColorAniSmooth	() const			{ return colorAniSmooth; };
	void				SetColorAniLoop		(const zBOOL  b)	{ colorAniLoop= b; };
	zBOOL				GetColorAniLoop		() const			{ return colorAniLoop; };
	
	//
	void				SetWhiteLight		(zBYTE intensity)			{ lightColor.SetRGB (intensity); };
	void				SetColor			(zBYTE r, zBYTE g, zBYTE b) { lightColor.SetRGB (r,g,b);		};
	void				SetColor			(zCOLOR col)				{ lightColor= col;  };
	zCOLOR				GetColor			() const					{ return lightColor; };
	int					GetColorR			() const					{ return int(lightColor.r); };
	int					GetColorG			() const					{ return int(lightColor.g); };
	int					GetColorB			() const					{ return int(lightColor.b); };
											
	void				SetRange			(const zVALUE r, const zBOOL doBackup=TRUE);
	zVALUE				GetRange			() const					{ return range;			};
	zVALUE				GetRangeInv			() const					{ return rangeInv;		};
	zVALUE				GetRangeFixed		() const					{ return rangeBackup;	};	// returns the fixed reference value (unaffected by rangeAnimation)
	zBOOL				GetCanMove			() const					{ return m_bCanMove;	};
	void				SetCanMove			(const zBOOL a_bCanMove)	{ m_bCanMove=a_bCanMove;};
											
	void				SetIsStatic			(const zBOOL b)				{ isStatic=b; };
	zBOOL				GetIsStatic			() const					{ return isStatic;	};
											
	void				SetLightQuality		(const zTVobLightQuality q)	{ lightQuality=q;							};
	zTVobLightQuality	GetLightQuality		() const					{ return zTVobLightQuality(lightQuality);	};
						
	zBOOL				SetLensFlareFXByName(const zSTRING& lensFlareFXName);
	const zSTRING& 		GetLensFlareFXName	() const;
	zCLensFlareFX*		GetLensFlareFX		() const					{ return lensFlareFX;	};
						
protected:
	zCVobLightData();
	~zCVobLightData();

	// persistance
	void				Archive				(zCArchiver &arc);
	void				Unarchive			(zCArchiver &arc);

private:
	int					lensFlareFXNo;
	zCLensFlareFX		*lensFlareFX;


	// for all light-types
//	zBOOL				turnedOn;
	zCOLOR				lightColor;						// alpha: unused
	zVALUE				range;							// state, current range
	zVALUE				rangeInv;						// state, current range
	zVALUE				rangeBackup;					// definition

	// light-animation
	// a) rangeAni
	zVALUE				rangeAniActFrame;
	zVALUE				rangeAniFPS;

	// b) colorAni
	zVALUE				colorAniActFrame;
	zVALUE				colorAniFPS;

	// spotLights
	zREAL				spotConeAngleDeg;

	struct {
		zUINT8			isStatic		: 1;
		zUINT8			rangeAniSmooth	: 1;
		zUINT8			rangeAniLoop	: 1;
		zUINT8			colorAniSmooth	: 1;
		zUINT8			colorAniLoop	: 1;
		zUINT8			isTurnedOn		: 1;
		zUINT8			lightQuality	: 4;
		zUINT8			lightType		: 4;
		zUINT8			m_bCanMove		: 1;
	};

	friend zCVobLight;
	friend zCVobLightPreset;
};

// ============================================================================================================

class zCVobLightPreset : public zCObject {
	zCLASS_DECLARATION (zCVobLightPreset)
public:
	zCVobLightData	lightData;

	const zSTRING&	GetName						()						{ return presetName; };
	void			SetName						(const zSTRING& name)	{ presetName = name; };
	// persistance
	void			Archive						(zCArchiver &arc);
	void			Unarchive					(zCArchiver &arc);

private:

	zSTRING			presetName;
	friend zCVobLight;
};

// ============================================================================================================

class zENGINE_API zCVobLight : public zCVob {
	zCLASS_DECLARATION (zCVobLight)

public:
	static void		CleanupVobLight			();

	// Presets
	static zCArray<zCVobLightPreset*>		lightPresetList;

	static	void	LoadLightPresets		();
	static	void	SaveLightPresets		();
			void	AddThisToPresetList		(const zSTRING& newPresetName) const;
			zBOOL	SetByPreset				(const zSTRING& presetName);
			zBOOL	SetByPresetInUse		();
			void	ResetPresetInUse		() { lightPresetInUse.Clear(); };
	const zSTRING&	GetPresetInUseName		() const { return lightPresetInUse; };

	static zBOOL	GetRenderLightVisuals	()				{ return renderLightVisuals; };
	static void		SetRenderLightVisuals	(const zBOOL b)	{ renderLightVisuals=b; };

	// Event-Messages
	virtual	void	OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);		// turns dynamic light on
	virtual	void	OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);		// turns dynamic light off
	virtual void	EndMovement				(const zBOOL a_bHintTrafoChanged=TRUE);
	virtual void	ThisVobAddedToWorld		(zCWorld *homeWorld);		// called AFTER the actual addition

public:
	zCVobLightData	lightData;
	zTRayTurboValMap<zCPolygon*, int>affectedPolyMap;

	zTVobLightType	GetLightType			()  const						{ return lightData.GetLightType();	};
	void			SetLightType			(const zTVobLightType ltype)	{ lightData.SetLightType (ltype);	};
	zBOOL			GetPolyIsAffected		(zCPolygon *poly)	const		{ int dummy=0; return affectedPolyMap.GetAt(poly, dummy);	};

	zBOOL			IsRangeAnimated			() const			{ return lightData.IsRangeAnimated	();		};
	void			SetRangeAniFPS			(const zVALUE fps)	{		 lightData.SetRangeAniFPS	(fps);	};
	zREAL			GetRangeAniFPS			() const			{ return lightData.GetRangeAniFPS	();		};
	void			SetRangeAniSmooth		(const zBOOL  b)	{		 lightData.SetRangeAniSmooth(b);	};
	zBOOL			GetRangeAniSmooth		() const			{ return lightData.GetRangeAniSmooth();		};
	void			SetRangeAniLoop			(const zBOOL  b)	{		 lightData.SetRangeAniLoop	(b);	};
	zBOOL			GetRangeAniLoop			() const			{ return lightData.GetRangeAniLoop	();		};
											
	zBOOL			IsColorAnimated			() const			{ return lightData.IsColorAnimated	();		};
	void			SetColorAniFPS			(const zVALUE fps)	{		 lightData.SetColorAniFPS	(fps); };
	zREAL			GetColorAniFPS			() const			{ return lightData.GetColorAniFPS	();		};
	void			SetColorAniSmooth		(const zBOOL  b)	{		 lightData.SetColorAniSmooth(b);	};
	zBOOL			GetColorAniSmooth		() const			{ return lightData.GetColorAniSmooth();		};
	void			SetColorAniLoop			(const zBOOL  b)	{		 lightData.SetColorAniLoop	(b);	};
	zBOOL			GetColorAniLoop			() const			{ return lightData.GetColorAniLoop	();		};
#ifdef COMPILING_SPACER
	void			SetShowLightSphere		(const a_bShowSphere)	{ m_bShowLightSphere = a_bShowSphere;	};
	zBOOL			GetShowLightSphere		() const				{ return m_bShowLightSphere;			};
	zBOOL			m_bShowLightSphere;
	static zCMesh*	s_pLightSphereMesh;
#endif

public:
			 zCVobLight();
protected:
	virtual ~zCVobLight();
public:

	//           no intensity, full intensity
	// Byte			0				255
	// Float	  0.0				1.0

	void			SetWhiteLight			(zBYTE intensity)			{ lightData.lightColor.SetRGB (intensity); };
	void			SetColor				(zBYTE r, zBYTE g, zBYTE b) { lightData.lightColor.SetRGB (r,g,b);		};
	void			SetColor				(zCOLOR col)				{ lightData.lightColor= col;  };
	zCOLOR			GetColor				() const					{ return lightData.lightColor; };
	int				GetColorR				() const					{ return int(lightData.lightColor.r); };
	int				GetColorG				() const					{ return int(lightData.lightColor.g); };
	int				GetColorB				() const					{ return int(lightData.lightColor.b); };
											
	void			SetRange				(const zVALUE r, const zBOOL doBackup=TRUE);
	zVALUE			GetRange				() const					{ return lightData.range;		};	// returns the current range in cm (state, affected by rangeAnimation)
	zVALUE			GetRangeInv				() const					{ return lightData.rangeInv;	};
	zVALUE			GetRangeFixed			() const					{ return lightData.rangeBackup;	};	// returns the fixed reference value (unaffected by rangeAnimation)
											
	void			SetIsStatic				(const zBOOL b)				{ lightData.isStatic=b; };
	zBOOL			GetIsStatic				() const					{ return lightData.isStatic;	};
	zBOOL			GetCanMove				() const					{ return lightData.m_bCanMove;	};
	void			SetCanMove				(const zBOOL canMove)		{ lightData.m_bCanMove = canMove;};

											
	void			SetLightQuality			(const zTVobLightQuality q)	{ lightData.lightQuality=q; };
	zTVobLightQuality GetLightQuality		() const					{ return lightData.GetLightQuality();	};

	zBOOL			HasVisual				() const					{ return (GetVisual()!=0) || (GetLensFlareFX()!=0); };
			
	// misc			
	static zCOLOR	SumLightsAtPositionWS	(const zCArray<zCVobLight*>& vobLightList, const zPOINT3& position, const zBOOL checkOcclusion=FALSE);
	void			DoAnimation				();
//	void			DieDown					(const zVALUE timeDelta);
//	void			SetTurnedOn				(const zBOOL b)				{ turnedOn = b;		};
//	zBOOL			GetTurnedOn				() const					{ return turnedOn;	};

	// lensFlares
	zBOOL			SetLensFlareFXByName	(const zSTRING& lensFlareFXName)	{ return lightData.SetLensFlareFXByName	(lensFlareFXName); };
	const zSTRING&	GetLensFlareFXName		() const							{ return lightData.GetLensFlareFXName	(); };
	zCLensFlareFX*	GetLensFlareFX			() const							{ return lightData.GetLensFlareFX		(); };

protected:
	// persistance
	virtual void	Archive					(zCArchiver &arc);
	virtual void	Unarchive				(zCArchiver &arc);

	zSTRING			lightPresetInUse;
private:
	static zBOOL	renderLightVisuals;
};

// ============================================================================================================

class zENGINE_API zCVobLevelCompo : public zCVob {
	zCLASS_DECLARATION (zCVobLevelCompo)
public:
			 zCVobLevelCompo();
	//
	virtual void	SetVisual				(zCVisual *v);
	virtual void	SetVisual				(const zSTRING& visualFileName);

	// persistance
	virtual void	Archive					(zCArchiver &arc);
	virtual void	Unarchive				(zCArchiver &arc);
	static  void	UnarcSetIgnoreVisuals	(const zBOOL ignore)	{ unarcIgnoreVisuals = ignore; };
protected:
	virtual ~zCVobLevelCompo() {};

private:
	static zBOOL	unarcIgnoreVisuals;
	zBOOL			HasIdentityTrafo		() const;

};
						
// ============================================================================================================

#endif
