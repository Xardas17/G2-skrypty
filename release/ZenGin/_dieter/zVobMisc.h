/******************************************************************************** 
 
     $Workfile:: zVobMisc.h           $                $Date:: 8.01.01 17:56    $
     $Revision:: 14                   $             $Modtime:: 4.01.01 23:16    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   ..
   created       : 13.1.2000

 * $Log: /current_work/zengin_work/_Dieter/zVobMisc.h $
 * 
 * 14    8.01.01 17:56 Hildebrandt
 * 
 * 13    4.12.00 17:29 Hildebrandt
 * 
 * 12    2.11.00 16:01 Hildebrandt
 * 
 * 11    25.10.00 21:07 Speckels
 * 
 * 10    28.09.00 19:19 Hildebrandt
 * 
 * 9     7.09.00 19:39 Hildebrandt
 * 
 * 8     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 7     11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 6     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 6     22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 5     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 4     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 2     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 1     13.01.00 1:54 Hildebrandt
 * speratet this file, was previosly part of "zVob.h"
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 14 $ ($Modtime: 4.01.01 23:16 $)

#ifndef __ZVOBMISC_H__
#define __ZVOBMISC_H__

// ============================================================================================================

#ifndef __ZVOB_H__
#include <zVob.h>
#endif

// declarations 
class zCModel;

// ============================================================================================================

class zCEventCommon : public zCEventMessage {
	zCLASS_DECLARATION	(zCEventCommon)
public:
	enum zTEventCommonSubType {
		zEVENT_ENABLE=0,
		zEVENT_DISABLE,
		zEVENT_TOGGLE_ENABLED,
		zEVENT_RESET,
		zEVENT_MISC_NUM_SUBTYPES
	};
	zCEventCommon	(const zTEventCommonSubType sub) { subType = zTSubType(sub); };

	// zCEventMessage Interface
	virtual	int				MD_GetNumOfSubTypes	()	{ return zEVENT_MISC_NUM_SUBTYPES; };
	virtual	zSTRING			MD_GetSubTypeString	(int n);
	virtual	zBOOL			IsNetRelevant		()	{ return TRUE; };

private:
	zCEventCommon() {};
};

// ============================================================================================================

// has a triggerTarget and can be activated by touching it
// OnTrigger and OnUntrigger messages are put through

class zENGINE_API zCTriggerBase : public zCVob {
	zCLASS_DECLARATION	(zCTriggerBase)
public:
	zCTriggerBase();

	// Message Interface
	virtual void		OnTouch					(zCVob* otherVob);
	virtual void		OnUntouch				(zCVob* otherVob);
	virtual	void		OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual	void		OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);

	// zCVob Interface
	virtual const zSTRING*	GetTriggerTarget	(const int i=0) const				{ return ((i==0) ? &triggerTarget : 0);	};

protected:
	// persistance
	virtual void		Archive					(zCArchiver &arc);
	virtual void		Unarchive				(zCArchiver &arc);

	zSTRING				triggerTarget;
};

// ============================================================================================================

class zCTrigger : public zCTriggerBase {
	zCLASS_DECLARATION	(zCTrigger)
public:
	zCTrigger();

	// Messages
	virtual void		OnTouch					(zCVob* otherVob);
	virtual void		OnUntouch				(zCVob* otherVob);
	virtual	void		OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual	void		OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void		OnDamage				(zCVob*			otherVob, 
												 zCVob*			inflictorVob, 
												 zREAL			damage,  
												 int			damageType, 
												 const zVEC3&	hitLocation);
	virtual void		OnMessage				(zCEventMessage *eventMessage, zCVob* sourceVob); 
	virtual void		OnTimer					();

	//
	zSTRING				GetTriggerTarget		() const							{ return triggerTarget;					};
	void				SetTriggerTarget		(const zSTRING& triggerTargetName)	{ triggerTarget=triggerTargetName;		};

	// persistance
	virtual void		Archive					(zCArchiver &arc);
	virtual void		Unarchive				(zCArchiver &arc);

protected:
	// props
	// activation filter
	struct {
		zUINT8			reactToOnTrigger: 1;
		zUINT8			reactToOnTouch	: 1;
		zUINT8			reactToOnDamage	: 1;

		zUINT8			respondToObject	: 1;
		zUINT8			respondToPC		: 1;
		zUINT8			respondToNPC	: 1;
	} filterFlags;
	struct {
		// state
		zUINT8			startEnabled	: 1;	
		zUINT8			isEnabled		: 1;	// only if object is enabled, it reacts to incomming messages
		zUINT8			sendUntrigger	: 1;	
	} flags;
	zSTRING				respondToVobName;
//	zSTRING				respondToClassName;
//	zBYTE				numTriggerToActivate;
	zSWORD				numCanBeActivated;
	zREAL				retriggerWaitSec;
	zREAL				damageThreshold;

	// fire behavior
	zREAL				fireDelaySec;
//	enum				zTRepeatTrigger { RT_NONE, RT_REPEAT, RT_REPEAT_TOUCHING } repeatTrigger;

	// internal
	zREAL				nextTimeTriggerable;
	zCVob				*savedOtherVob;
	zSWORD				countCanBeActivated;	// [SPECKELS]

	//
	virtual ~zCTrigger();			// use Release() instead!
	virtual void		TriggerTarget			(zCVob* vobInstigator);
	virtual void		UntriggerTarget			(zCVob* vobInstigator);
	virtual zBOOL		CanBeActivatedNow		(zCVob* vobInstigator);
	void				ResetNumCanBeActivated	(zSWORD num) { numCanBeActivated = countCanBeActivated = num; }	// [SPECKELS]

private:
	void				ActivateTrigger		(zCVob* vobInstigator);
	void				DeactivateTrigger	(zCVob* vobInstigator);
	void				TriggerTargetPost	();
	void				ClearStateInternals	();					// clears internal state-information (not properties), called within ctor and Unarchive()
};

// ============================================================================================================

class zCEventMover : public zCEventMessage {
	zCLASS_DECLARATION	(zCEventMover)
public:
	// IDEEN: a) KEY_NEXT/PREV wrap/noWrap, b) GOTO_KEY_RANDOM
	enum zTEventMoverSubType {
		zEVENT_GOTO_KEY_FIXED_DIRECTLY=0,	// e.g. directly from key 2 to key 6
		zEVENT_GOTO_KEY_FIXED_ORDER,		// e.g. from key 2 to key 6, passing keys 3,4,5
		zEVENT_GOTO_KEY_NEXT,				// wraps around
		zEVENT_GOTO_KEY_PREV,				// wraps around
		zEVENT_MISC_NUM_SUBTYPES
	};
	zCEventMover	(const zTEventMoverSubType sub)								 { subType = zTSubType(sub); };
	zCEventMover	(const zTEventMoverSubType sub, const int gotoFixedKeyframe) { subType = zTSubType(sub); this->gotoFixedKeyframe=gotoFixedKeyframe; };

	// zCEventMessage Interface
	virtual	int				MD_GetNumOfSubTypes	()	{ return zEVENT_MISC_NUM_SUBTYPES; };
	virtual	zSTRING			MD_GetSubTypeString	(int n);
	virtual	zBOOL			IsNetRelevant		()	{ return TRUE; };

	int						gotoFixedKeyframe;
private:
	zCEventMover() {};
};

// ============================================================================================================

class zCMover : public zCTrigger {
	zCLASS_DECLARATION	(zCMover)
public:
	zCMover();

	// Messages
	virtual void			OnTouch					(zCVob* otherVob);
	virtual void			OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnTick					();
	virtual void			OnDamage				(zCVob*			otherVob, 
													 zCVob*			inflictorVob, 
													 zREAL			damage,  
													 int			damageType, 
													 const zVEC3&	hitLocation);
	virtual void			OnMessage				(zCEventMessage *eventMessage, zCVob* sourceVob);

	// zCVob Interface
	virtual zBOOL			CanThisCollideWith		(zCVob* vob);
	virtual void			SetVisual				(zCVisual *v);
//	virtual void			PostUnarchive			(zCArchiver &arc);
	virtual void			PostLoad				();

	// Keyframes
	struct zTMov_Keyframe {
		zPOINT3		pos;
		zCQuat		quat;
	};
	zCArray<zTMov_Keyframe>	keyframeList;
	static zTMov_Keyframe	GetKeyframe				(zCVob* keyframeVob);

	//
	void					SetToKeyframe			(zREAL newKeyframe, zREAL advDir=0.0F);
	int						GetActKeyframe			() const	{ return actKeyframe;		};
	zBOOL					GetAutoLinkEnabled		() const	{ return autoLinkEnabled;	};

	//
	zBOOL					IsKeyToThisMover		(zCVob* otherVob);

	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

protected:
	virtual ~zCMover();

	// internals
	zVEC3					actKeyPosDelta;
	zREAL					actKeyframeF;
	int						actKeyframe;
	int						nextKeyframe;
	zREAL					moveSpeedUnit;
	zREAL					advanceDir;
	enum zTMoverState		{ MOVER_STATE_OPEN, 
							  MOVER_STATE_OPENING, 
							  MOVER_STATE_CLOSED, 
							  MOVER_STATE_CLOSING
							} moverState;
	int						numTriggerEvents;
	zREAL					stayOpenTimeDest;
//	zSTRING					keyframeVobChain;
	// following: no need to archive !
	zCModel					*model;
	zTSoundHandle			soundMovingHandle;
	zCSoundFX				*sfxMoving;

	// props
	zREAL					moveSpeed;
	zREAL					stayOpenTimeSec;
	zREAL					touchBlockerDamage;
	zBOOL8					moverLocked;
	zBOOL8					autoLinkEnabled;
	zBOOL8					autoRotate;

	enum zTMoverAniType		{ MA_KEYFRAME,
							  MA_MODEL_ANI, 
							  MA_WAYPOINT 
							} moverAniType;

	//
	enum zTMoverBehavior	{ MB_2STATE_TOGGLE,				// trigger: toggles	, untrigger: %
							  MB_2STATE_TRIGGER_CONTROL,	// trigger: open	, untrigger: close
							  MB_2STATE_OPEN_TIMED,			// trigger: open
							  MB_NSTATE_LOOP,
							  MB_NSTATE_SINGLE_KEYS
							} moverBehavior;

	enum zTTouchBehavior	{ TB_TOGGLE,
							  TB_WAIT
							} touchBehavior;

	// aniType: Keyframe
	enum zTPosLerpType		{ PL_LINEAR, 
							  PL_CURVE 
							} posLerpType;
	enum zTSpeedType		{ ST_CONST , 
							  ST_SLOW_START_END		, ST_SLOW_START		, ST_SLOW_END,
							  ST_SEG_SLOW_START_END	, ST_SEG_SLOW_START	, ST_SEG_SLOW_END 
							} speedType;

	// sound
	zSTRING					soundOpenStart;
	zSTRING					soundOpenEnd;
	zSTRING					soundMoving;
	zSTRING					soundCloseStart;
	zSTRING					soundCloseEnd;

	zSTRING					soundLock;
	zSTRING					soundUnlock;
	zSTRING					soundUseLocked;


	// keyframe
	void					AdvanceKeyframe_KF		();
	void					InterpolateKeyframes_KF	();
	void					SetToKeyframe_KF		(zREAL newKeyframe);

	// common
	void					AdvanceMover			();
	void					InvertMovement			();
	void					DoOpen					();
	void					FinishedOpening			();
	void					DoClose					();
	void					FinishedClosing			();
	void					TriggerMover			(zCVob* otherVob);
	void					Lock					(zCVob* otherVob);
	void					Unlock					(zCVob* otherVob);

	//
	zBOOL					Is2StateBehavior		() const { return (moverBehavior<=MB_2STATE_OPEN_TIMED); };
	void					MoveToKeyframe			(int index);	// for use in mover-Behaviour 'MB_NSTATE_SINGLE_KEYS'
private:
	void					ClearStateInternals		();		// clears internal state-information (not properties), called within ctor and Unarchive()
	void					UpdateInternals			();
	void					StartMovingSound		();
};

// ============================================================================================================

class zCTriggerTeleport : public zCTrigger {
	zCLASS_DECLARATION	(zCTriggerTeleport)
public:
			 zCTriggerTeleport();

	virtual void			OnTouch					(zCVob* otherVob);
	virtual void			OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);

	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

protected:
	virtual ~zCTriggerTeleport();		// use Release() instead!
	void					DoTeleport (zCVob* otherVob);
private:
	zSTRING					teleportSoundName;
	zCSoundFX				*teleportSound;
};

// ============================================================================================================
/*
class zCTriggerJumper: public zCTrigger {
	zCLASS_DECLARATION	(zCTriggerJumper)
public:

	virtual void			OnTouch					(zCVob* otherVob);

protected:
};
*/
// ============================================================================================================

class zCTriggerList : public zCTrigger {
	zCLASS_DECLARATION	(zCTriggerList)
public:
	zCTriggerList ();

	virtual void			OnTimer					();
	virtual const zSTRING*	GetTriggerTarget		(const int i=0) const;

protected:
	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

	virtual void			TriggerTarget			(zCVob* vobInstigator);
	virtual void			UntriggerTarget			(zCVob* vobInstigator);


private:
	// props
	enum					{ MAX_TARGETS = 6 };
	zSTRING					triggerTargetList		[MAX_TARGETS];
	zREAL					fireDelayList			[MAX_TARGETS];
	enum					zTListProcess			{ LP_ALL, LP_NEXT_ONE, LP_RAND_ONE } listProcess;

	// state
	int						actTarget;				// indexes into 'triggerTargetList'
	zBOOL					sendOnTrigger;			// FALSE = sendOnUntrigger

	void					Init					();
	void					TriggerActTarget		(zCVob *vobInstigator);
	zBOOL					ProcessActTarget		(zCVob* vobInstigator);
	void					FinishActivation		();
	void					DoTriggering			(zCVob* vobInstigator);

};

// ============================================================================================================

class zENGINE_API zCEffect : public zCVob {
	zCLASS_DECLARATION	(zCEffect)
};

// ============================================================================================================

class zCEarthquake: public zCEffect {
	zCLASS_DECLARATION	(zCEarthquake)
public:
	zCEarthquake();
	// messages
	virtual void			OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);

	//
	void					SetProperties			(const zREAL radius, const zREAL timeSec, const zVEC3& amp) { radiusSquare = radius*radius; timeMSec = timeSec * zREAL(1000.0F); amplitude=amp; };

protected:
	// props
	zREAL					radiusSquare;
	zREAL					timeMSec;
	zVEC3					amplitude;

	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);
};

// ============================================================================================================

class zCParticleFX;		// "zParticle.h"

class zCPFXControler : public zCEffect {
	zCLASS_DECLARATION	(zCPFXControler) 
public:
	zCPFXControler();

	// messages
	virtual void			OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);

	//
	virtual void			PostLoad				();
	void					SetPFXName				(const zSTRING& s)	{ pfxName=s;		};
	const zSTRING&			GetPFXName				() const			{ return pfxName;	};

protected:

	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

	//
	zCParticleFX*			GetPFX					();
private:
	zSTRING					pfxName;
	struct {
		zUINT8				killVobWhenDone	: 1;
		zUINT8				pfxStartOn		: 1;
	};
};

// ============================================================================================================

class zENGINE_API zCTouchDamage : public zCEffect {
	zCLASS_DECLARATION	(zCTouchDamage) 
public:
	enum zTDamageCollType	{ CT_NONE,
							  CT_BOX,				// test: other->bbox		<=> this->bbox*scale 
							  CT_POINT,				// test: other->bbox*scale	<=> this->point		(pfx-visuals: every particle is being tested!)
							};

	zCTouchDamage();

	// message interface
	virtual void			OnTouch					(zCVob* otherVob);
	virtual void			OnUntouch				(zCVob* otherVob);
	virtual void			OnTimer					();

	// zCVob interface
	virtual void			SetVisual				(zCVisual *v);

	// props
	void					SetDamage				(const zREAL dam)					{ damage=dam;						};
	void					SetDamageType			(const int	 damType)				{ damageType=damType;				};
	void					SetDamageRepeatDelaySec	(const zREAL repDelay)				{ damageRepeatDelaySec=repDelay;	};
	void					SetDamageVolDownScale	(const zREAL scale)					{ damageVolDownScale=scale;			};
	void					SetDamageCollType		(const zTDamageCollType collType)	{ damageCollType=collType;			};

	zREAL					GetDamage				() const							{ return damage;					};
	int						GetDamageType			() const							{ return damageType;				};
protected:
	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

	virtual const char* 	GetDamageTypeArcEnum	(const zDWORD index);

private:
	zREAL					damage;
	int						damageType;
	zREAL					damageRepeatDelaySec;
	zREAL					damageVolDownScale;		// [0..1], 1.0 default
	zTDamageCollType		damageCollType;

	void					ProcessToucher			(zCVob* otherVob);
	void					FireDamageMessage		(zCVob* otherVob);
	zBOOL					TestCollType			(zCVob* otherVob);
	void					SetVobProperties		();
};

// ============================================================================================================

// Vob must be identifiable as Stairs, especially if they are steep. 
// This prevents AIs from treating them as walls or obstacles.

class zCVobStair : public zCVob {
	zCLASS_DECLARATION	(zCVobStair) 
public:
};

// ============================================================================================================

class zCTouchAnimate : public zCEffect {
	zCLASS_DECLARATION	(zCTouchAnimate) 
public:

	zCTouchAnimate();

	// message interface
	virtual void			OnTouch					(zCVob* otherVob);
	virtual void			OnUntouch				(zCVob* otherVob);
	virtual void			OnTick					();

	// zCVob interface
	virtual void			SetVisual				(zCVisual *v);

protected:
	// zCTouchAnimate interface
	virtual ~zCTouchAnimate();					// use Release() instead!
	virtual zSTRING			GetSoundName			();

	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

private:
	zSTRING					touchSoundName;
	zCSoundFX				*touchSound;

	void					StartAni				();
	void					StopAni					();
	zBOOL					IsAniActive				();
	void					SetVobProperties		();
	zBOOL					IsTouching				(zCVob *otherVob);
};

// ============================================================================================================

class zCTouchAnimateSound : public zCTouchAnimate {
	zCLASS_DECLARATION	(zCTouchAnimateSound) 
public:
	zCTouchAnimateSound();

protected:
	// zCTouchAnimate interface
	virtual zSTRING			GetSoundName			();

	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

private:
	zSTRING					touchSoundName;
};

// ============================================================================================================

class zCVobAnimate : public zCEffect {
	zCLASS_DECLARATION	(zCVobAnimate) 
public:
	zCVobAnimate();

	// EventMessage Interface
	virtual void			OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual void			OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);

	// zCVob interface
	virtual void			SetVisual				(zCVisual *v);

protected:
	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

private:
	zBOOL8					startOn;
	zBOOL8					isRunning;

	void					StartAni				();
	void					StopAni					();

};

// ============================================================================================================

class zCVobLensFlare : public zCEffect {
	zCLASS_DECLARATION	(zCVobLensFlare) 
public:
	zCVobLensFlare();

	// zCVob interface
	virtual zBOOL zCCFASTCALL Render				(zTRenderContext &renderContext);

	//
	void					SetLensFlareFXByName	(const zSTRING& lensFlareFXName);

protected:
	virtual ~zCVobLensFlare();			// use Release() instead!
	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);
private:
	zCLensFlareFX			*lensFlareFX;
	// memory optimziation/editor robustness
	#ifdef COMPILING_SPACER
		zSTRING				lensFlareFXName;
	#endif
};


// ============================================================================================================

class zCEventScreenFX : public zCEventMessage {
	zCLASS_DECLARATION	(zCEventScreenFX)
public:
	enum zTEventScreenFXSubType {
		zEVENT_BLEND_FADEIN,
		zEVENT_BLEND_FADEOUT,
		zEVENT_CINEMA_FADEIN,
		zEVENT_CINEMA_FADEOUT,
		zEVENT_FOV_MORPH,
		zEVENT_SCREENFX_COUNT
	};

	zCEventScreenFX			(const zTEventScreenFXSubType sub, const zREAL duration, const zCOLOR color, const zREAL fovDeg);

	// zCEventMessage Interface
	int						MD_GetNumOfSubTypes	()		{ return zEVENT_SCREENFX_COUNT; };
	zSTRING					MD_GetSubTypeString	(int n);
	zTTimeBehavior			MD_GetTimeBehavior	();
	zREAL					MD_GetMinTime		();

protected:
	zCEventScreenFX () { Clear(); };

	// Pack / Unpack
	void					Pack				(zCBuffer& buffer, zCEventManager* evManContext);
	void					Unpack				(zCBuffer& buffer, zCEventManager* evManContext);

	// Archive / Unarchive
	void					Archive				(zCArchiver& arc);
	void					Unarchive			(zCArchiver& arc);

private:
	// props
	zREAL					duration;
	zCOLOR					color;
	zREAL					fovDeg;

	void					Clear					();
	friend class zCVobScreenFX;
};

class zCVobScreenFX : public zCEffect {
	zCLASS_DECLARATION	(zCVobScreenFX) 
public:
	zCVobScreenFX();

	// MessageInterface
	virtual void			OnMessage				(zCEventMessage *eventMessage, zCVob* sourceVob); 

	// zCVob interface
	virtual void			OnTick					();

	//
	void					StartEffect_BlendFadeIn		(const zREAL durationSec, const zCOLOR color, const zSTRING texName, const zREAL a_texAniFPS = 0.0f, const zTRnd_AlphaBlendFunc blendFunc = zRND_ALPHA_FUNC_BLEND) 
														{ blend.texName = texName; blend.texAniFPS = a_texAniFPS; blend.blendFunc = blendFunc; StartEffect (durationSec, color, FALSE, blend); };
	void					StartEffect_BlendFadeOut	(const zREAL durationSec, const zCOLOR color) 
														{ StartEffect (durationSec, color, TRUE, blend); };
	void					StartEffect_CinemaFadeIn	(const zREAL durationSec, const zCOLOR color) 
														{ StartEffect (durationSec, color, TRUE, cinema); };
	void					StartEffect_CinemaFadeOut	(const zREAL durationSec, const zCOLOR color) 
														{ StartEffect (durationSec, color, FALSE, cinema); };
	void					StartEffect_FOVMorph		(const zREAL durationSec, const zREAL fovDeg) 
														{ StartEffect (durationSec, zCOLOR(0,0,0,0), FALSE, fovMorph); fovMorph.fovDeg= fovDeg; };

protected:
	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

private:
	struct zTScreenFXSet {
		zREAL				weight;
		zREAL				velo;
		zCOLOR				color;
		zREAL				fovDeg;
		zBOOL				visible;
		zSTRING				texName;
		zREAL				texAniFPS;
		zTRnd_AlphaBlendFunc blendFunc;

		void Clear() { weight=0; velo=0; color.SetRGBA(0,0,0,255); fovDeg=0; visible = FALSE; texAniFPS = 0; blendFunc = zRND_ALPHA_FUNC_BLEND; };
	};
	zTScreenFXSet			blend;
	zTScreenFXSet			cinema;
	zTScreenFXSet			fovMorph;
	zVEC2					fovSaved;
	zVEC2					fovSavedFirst;

	void					StartEffect				(const zREAL				duration, 
													 const zCOLOR				color, 
													 const zBOOL				fadeIn, 
													 zTScreenFXSet				&effectSet);
	zCOLOR					CalcEffectColor			(zTScreenFXSet &effectSet);
};

// ============================================================================================================

class zCMessageFilter : public zCTriggerBase {
	zCLASS_DECLARATION	(zCMessageFilter) 
public:
	zCMessageFilter();

	// Message Interface
	virtual	void			OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual	void			OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);

	// disable..
	virtual void			OnTouch					(zCVob* otherVob) {};
	virtual	void			OnUntouch				(zCVob* otherVob) {};

protected:
	// persistance
	virtual void			Archive					(zCArchiver &arc);
	virtual void			Unarchive				(zCArchiver &arc);

private:
	enum zTMessageType {
		MT_NONE=0,
		MT_TRIGGER,
		MT_UNTRIGGER,
		MT_ENABLE,
		MT_DISABLE,
		MT_TOGGLE_ENABLED,
		MT_RESET
	};
	struct {
		zUINT8				sendWhenTriggered	: 4;
		zUINT8				sendWhenUntriggered	: 4;
	};

	void					ProcessMessage (const zTMessageType outMessageType, zCVob *vobInstigator);
};

// ============================================================================================================

// triggers when it is 'untouched' by the last non-living object

class zCTriggerUntouch : public zCTriggerBase {
	zCLASS_DECLARATION	(zCTriggerUntouch)
public:
	// Messages
	virtual void		OnUntouch				(zCVob* otherVob);

	// disable..
	virtual void		OnTouch					(zCVob* otherVob) {};
	virtual	void		OnTrigger				(zCVob* otherVob, zCVob *vobInstigator) {};
	virtual	void		OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator) {};
};

// ============================================================================================================

// triggers when it is 'untouched' by the last non-living object

class zCTriggerWorldStart : public zCTriggerBase {
	zCLASS_DECLARATION	(zCTriggerWorldStart)
public:
	zCTriggerWorldStart();

	// Messages
	virtual	void		OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);

	// disable..
	virtual void		OnTouch					(zCVob* otherVob) {};
	virtual void		OnUntouch				(zCVob* otherVob) {};
	virtual	void		OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator) {};

	// zCVob Interface
	virtual void		PostLoad				();

protected:
	// persistance
	virtual void		Archive					(zCArchiver &arc);
	virtual void		Unarchive				(zCArchiver &arc);

private:
	zBOOL8				fireOnlyFirstTime;
	zBOOL8				hasFired;
};

// ============================================================================================================

class zCCodeMaster : public zCTriggerBase {
	zCLASS_DECLARATION	(zCCodeMaster)
public:
	zCCodeMaster();

	// Messages
	virtual	void		OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual	void		OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator);
	virtual	void		OnMessage				(zCEventMessage *eventMessage, zCVob* sourceVob);

	// disable..
	virtual void		OnUntouch				(zCVob* otherVob) {};
	virtual void		OnTouch					(zCVob* otherVob) {};

	// zCVob Interface
	virtual const zSTRING*	GetTriggerTarget	(const int i=0) const;

protected:
	// persistance
	virtual void		Archive					(zCArchiver &arc);
	virtual void		Unarchive				(zCArchiver &arc);

	virtual ~zCCodeMaster();
private:
	// props
	enum				{ MAX_SLAVES = 6 };
	zSTRING				slaveVobNameList		[MAX_SLAVES];
	zSTRING				triggerTargetFailure;
	struct {
		zUINT8			orderRelevant			: 1;
		zUINT8			untriggerCancels		: 1;		// if order NOT relevant
		zUINT8			firstFalseIsFailure		: 1;		// if order IS  relevant
	} flags;

	// state
	zCVob*				slaveTriggeredList		[MAX_SLAVES];
	int					numSlavesTriggered;

	void				Init					();
	void				Reset					();
	void				FireTriggerSuccess		(zCVob *vobInstigator);
	void				FireTriggerFailure		(zCVob *vobInstigator);
	int					GetSlaveNr				(zCVob *otherVob);
};

// ============================================================================================================

class zCMoverControler : public zCTriggerBase {
	zCLASS_DECLARATION	(zCMoverControler)
public:
	zCMoverControler();

	// Messages
	virtual	void		OnTrigger				(zCVob* otherVob, zCVob *vobInstigator);

	// disable..
	virtual	void		OnUntrigger				(zCVob* otherVob, zCVob *vobInstigator) {};
	virtual void		OnUntouch				(zCVob* otherVob) {};
	virtual void		OnTouch					(zCVob* otherVob) {};

protected:
	// persistance
	virtual void		Archive					(zCArchiver &arc);
	virtual void		Unarchive				(zCArchiver &arc);

private:
	zCEventMover::zTEventMoverSubType	moverMessage;
	int									gotoFixedKeyframe;
};

// ============================================================================================================

#ifdef ZENGINE_DEBUG
// tmp

class zENGINE_API zCVobChar : public zCVob {
	zCLASS_DECLARATION	(zCVobChar) 
public:
	zTVobCharClass			GetCharacterClass		()	{ return zVOB_CHAR_CLASS_PC; };
};
#endif

// ============================================================================================================

#endif