/******************************************************************************** 
 
     $Workfile:: zVobMisc.cpp         $                $Date:: 16.02.01 19:16   $
     $Revision:: 26                   $             $Modtime:: 16.02.01 19:16   $
       $Author:: Speckels                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zVobMisc.cpp $
 * 
 * 26    16.02.01 19:16 Speckels
 * 
 * 24    13.02.01 1:05 Hildebrandt
 * 
 * 23    2.02.01 0:56 Hildebrandt
 * 
 * 22    8.01.01 22:18 Hildebrandt
 * 
 * 21    8.01.01 17:56 Hildebrandt
 * 
 * 20    20.12.00 3:06 Hildebrandt
 * 
 * 19    13.11.00 20:18 Hildebrandt
 * 
 * 18    2.11.00 16:01 Hildebrandt
 * 
 * 17    2.11.00 2:26 Hildebrandt
 * 
 * 16    25.10.00 21:07 Speckels
 * 
 * 15    25.10.00 15:06 Hildebrandt
 * 
 * 14    14.10.00 0:24 Hildebrandt 
 * 
 * 13    28.09.00 19:19 Hildebrandt
 * 
 * 12    7.09.00 19:50 Hildebrandt
 * 
 * 11    7.09.00 19:39 Hildebrandt
 * 
 * 10    21.08.00 17:18 Hildebrandt
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 8     22.07.00 2:06 Hildebrandt
 * 
 * 7     21.07.00 14:28 Hildebrandt
 * 
 * 6     11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 5     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 8     22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 7     16.03.00 2:21 Hildebrandt
 * 
 * 6     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 5     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 3     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 2     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 1     6.12.99 15:51 Hildebrandt
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 26 $ ($Modtime: 16.02.01 19:16 $)


#include <zCore.h>
#include <zVobMisc.h>

#include <zWorld.h>
#include <zArchiver.h>
#include <zEventMan.h>
#include <zModel.h>
#include <zMorphMesh.h>
#include <zPhysics.h> 
#include <zParticle.h>
#include <zSound.h>
#include <zBuffer.h>
#include <zGrafix.h>
#include <zLensflare.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

// vob classes, that are not directly known to the engine 
// (extensions/modules, supporting the zCVob interface)
zCLASS_DEFINITION			( zCVobStair		, zCVob			,	0,	0)


zCLASS_DEFINITION_ABSTRACT	( zCTriggerBase		, zCVob			,	0	 )
	zCLASS_DEFINITION		( zCTriggerUntouch	, zCTriggerBase	,	0,	1)
	zCLASS_DEFINITION		( zCMessageFilter	, zCTriggerBase	,	0,	0)
	zCLASS_DEFINITION		( zCCodeMaster		, zCTriggerBase	,	0,	0)
	zCLASS_DEFINITION		( zCMoverControler	, zCTriggerBase	,	0,	0)
	zCLASS_DEFINITION		( zCTriggerWorldStart, zCTriggerBase,	0,	0)
	zCLASS_DEFINITION		( zCTrigger			, zCTriggerBase	,	0,	2)
		zCLASS_DEFINITION	( zCTriggerList		, zCTrigger		,	0,	0)
		zCLASS_DEFINITION	( zCMover			, zCTrigger		,	0,	1)
		zCLASS_DEFINITION	( zCTriggerTeleport	, zCTrigger		,	0,	0)
//		zCLASS_DEFINITION	( zCTriggerJumper	, zCTrigger		,	0,	0)

zCLASS_DEFINITION_ABSTRACT	( zCEffect			, zCVob			,	0	 )
	zCLASS_DEFINITION		( zCEarthquake		, zCEffect		,	0,	0)
	zCLASS_DEFINITION		( zCPFXControler	, zCEffect		,	0,	0)
	zCLASS_DEFINITION		( zCTouchDamage		, zCEffect		,	0,	1)
	zCLASS_DEFINITION		( zCTouchAnimate	, zCEffect		,	0,	0)
		zCLASS_DEFINITION	( zCTouchAnimateSound,zCTouchAnimate,	0,	0)
	zCLASS_DEFINITION		( zCVobAnimate		, zCEffect		,	0,	0)
	zCLASS_DEFINITION		( zCVobLensFlare	, zCEffect		,	0,	1)
	zCLASS_DEFINITION		( zCVobScreenFX		, zCEffect		,	0,	1)

// Event-Messages
zCLASS_DEFINITION			( zCEventCommon		, zCEventMessage,	0,	0)
zCLASS_DEFINITION			( zCEventMover		, zCEventMessage,	0,	0)
zCLASS_DEFINITION			( zCEventScreenFX	, zCEventMessage,	0,	0)

//
#ifdef ZENGINE_DEBUG
// test-class
	zCLASS_DEFINITION		( zCVobChar			, zCVob			,	0,	0)
#endif

/*
zVob.cpp
zVobTrigger.cpp
zVobEffects.cpp
zVobMisc.cpp
*/

// =============================================================================================================

zSTRING zCEventCommon::MD_GetSubTypeString (int n) 
{
	switch (n) {
		case 0:	return "ENABLE";			break;
		case 1:	return "DISBLE";			break;
		case 2:	return "TOGGLE_ENABLED";	break;
	};
	return "";
};

// =============================================================================================================

zSTRING zCEventMover::MD_GetSubTypeString (int n) 
{
	switch (n) {
		case 0:	return "GOTO_KEY_FIXED_DIRECTLY";	break;
//		case 1:	return "GOTO_KEY_FIXED_ORDER";		break;
		case 1:	return "_DISABLED_";				break;
		case 2:	return "GOTO_KEY_NEXT";				break;
		case 3:	return "GOTO_KEY_PREV";				break;
	};
	return "";
};


///////////////////////////////////////////////////////////////////////////
//    zCTriggerBase
///////////////////////////////////////////////////////////////////////////

zCTriggerBase::zCTriggerBase() {
	// zCVob inits
	SetCollisionClass			(zCCollObjectBoxPassThrough::S_GetCollObjClass());
	SetCollDetStat				(FALSE);
	SetCollDetDyn				(TRUE);
	SetIgnoredByTraceRay		(TRUE);
	SetShowVisual				(TRUE);
};

void zCTriggerBase::OnTouch (zCVob* otherVob) {
	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		targetVobList[i]->GetEM()->OnTrigger	(otherVob, otherVob);
	};
};

void zCTriggerBase::OnUntouch (zCVob* otherVob) {
	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		targetVobList[i]->GetEM()->OnUntrigger	(otherVob, otherVob);
	};
};

void zCTriggerBase::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) {
	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		targetVobList[i]->GetEM()->OnTrigger	(this, vobInstigator);
	};
};

void zCTriggerBase::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) {
	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		targetVobList[i]->GetEM()->OnUntrigger	(this, vobInstigator);
	};
};

void zCTriggerBase::Archive (zCArchiver &arc)
{
	zCVob::Archive		(arc);

	//
	arc.WriteString		("triggerTarget",		triggerTarget);
};

void zCTriggerBase::Unarchive (zCArchiver &arc)
{
	zCVob::Unarchive	(arc);

	//
	arc.ReadString		("triggerTarget",		triggerTarget);		triggerTarget.Upper();
};


///////////////////////////////////////////////////////////////////////////
//    zCTrigger
///////////////////////////////////////////////////////////////////////////

zCTrigger::zCTrigger() 
{
	// zCVob inits
	SetCollisionClass			(zCCollObjectBoxPassThrough::S_GetCollObjClass());
	SetCollDetStat				(FALSE);
	SetCollDetDyn				(TRUE);
	SetIgnoredByTraceRay		(TRUE);
	SetShowVisual				(TRUE);

	// activation filter
	memset (&filterFlags, 0, sizeof(filterFlags));
	filterFlags.reactToOnTrigger= TRUE;
	filterFlags.reactToOnTouch	= TRUE;
	filterFlags.reactToOnDamage	= TRUE;
	filterFlags.respondToObject	= 1;
	filterFlags.respondToPC		= 1;
	filterFlags.respondToNPC	= 1;
//	numTriggerToActivate		= 0;
	numCanBeActivated			= -1;	
	retriggerWaitSec			= 0;
	damageThreshold				= 0;

	// flags
	memset (&flags, 0, sizeof(flags));
	flags.startEnabled			= TRUE;
	flags.isEnabled				= TRUE;
	flags.sendUntrigger			= TRUE;
								
	// fire behavior			
	fireDelaySec				= 0;
	triggerTarget.Clear			();

	// internals
	savedOtherVob				= 0;
	countCanBeActivated  		= -1;	
	ClearStateInternals			();
};

void zCTrigger::ClearStateInternals () 
{
	nextTimeTriggerable			= 0;
	flags.isEnabled				= flags.startEnabled;
	zRELEASE					(savedOtherVob);
};

zCTrigger::~zCTrigger() {
	zRELEASE					(savedOtherVob);
};

zBOOL zCTrigger::CanBeActivatedNow (zCVob* vobInstigator) 
{
	// "Activation Filter" 
	if (!flags.isEnabled)		return FALSE;

	// wurde bereits die maximale Anzahl getriggert ?
	if (countCanBeActivated==0)	return FALSE;
 
	// Falls der Timer fuer den Trigger aktiv ist heisst das, dass noch eine Aktion in 
	// Verarbeitung ist (z.B. ein verzoegertes OnTrigger ueber das FireDelay, oder ein Repeat)
	if (IsOnTimer())			return FALSE;

	// darf Trigger noch nicht wieder getriggert werden ?
	if (ztimer.GetTotalTimeF()<nextTimeTriggerable) return FALSE;
	
	// ????? FIXME: lieber einen zCTriggerCounter einfuehren ????
//	if (numTriggerToActivate>0) .. 

	// Alle 'respondTo' Bedingungen sind mit 'oder' verknuepft !
	if (vobInstigator)
	if (!(
		((filterFlags.respondToObject)	 && (vobInstigator->GetCharacterClass ()==zVOB_CHAR_CLASS_NONE)) ||
		((filterFlags.respondToPC )		 && (vobInstigator->GetCharacterClass ()==zVOB_CHAR_CLASS_PC  )) ||
		((filterFlags.respondToNPC)		 && (vobInstigator->GetCharacterClass ()==zVOB_CHAR_CLASS_NPC )) ||
//		((!respondToClassName.IsEmpty()) && (vobInstigator->GetClassName_	 ()==respondToClassName	 )) ||
		((!respondToVobName  .IsEmpty()) && (vobInstigator->GetVobName		 ()==respondToVobName    ))
		)) return FALSE;

	// TriggerAngle testen
//	if (triggerAngle!=0) {
//	};

	//
	return TRUE;
};

// =======================================================================

// VIRTUALS

void zCTrigger::TriggerTarget (zCVob* vobInstigator) 
{
	// virtual
	if (triggerTarget.IsEmpty())	return;		// ist nur eine Optimierung

	// eine ganze Liste von Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) 
	{
		targetVobList[i]->GetEM()->OnTrigger (this, vobInstigator);
	};
};

void zCTrigger::UntriggerTarget (zCVob* vobInstigator) 
{
	// virtual
	if (triggerTarget.IsEmpty())	return;		// ist nur eine Optimierung

	// eine ganze Liste von Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) 
	{
		targetVobList[i]->GetEM()->OnUntrigger (this, vobInstigator);
	};
};

// =======================================================================

void zCTrigger::TriggerTargetPost () 
{
	// Hier werden nach einem TriggerTarget fuer diese Klasse spezifische Updates getaetigt.
	// fuer den Activation Filter
	if (countCanBeActivated>0) countCanBeActivated--;
	nextTimeTriggerable = ztimer.GetTotalTimeF() + (retriggerWaitSec * zREAL(1000.0F));	
};

void zCTrigger::ActivateTrigger (zCVob* vobInstigator) 
{
	// ist ein Trigger Prozess noch im Gange ? (über SetTimer)
	if (IsOnTimer())						return;
	if (!CanBeActivatedNow(vobInstigator))	return;
	if (!flags.isEnabled)					return;

	// Trigger feuern

	// FireDelay
	if (fireDelaySec>0) 
	{
		// savedOtherVob fuer spaetere Aktivierung merken
		zRELEASE			(savedOtherVob);
		savedOtherVob		= vobInstigator;
		if (savedOtherVob)	savedOtherVob->AddRef();

		SetOnTimer			(fireDelaySec * zREAL(1000.0F));
		return;
	};

	// Feuern !
	TriggerTarget		(vobInstigator);
	TriggerTargetPost	();
};

void zCTrigger::DeactivateTrigger (zCVob* vobInstigator) 
{
	// FIXME: CanBeActivatedNow ????
	// ist ein Trigger Prozess noch im Gange ? (über SetTimer)
	if (IsOnTimer())				return;
	if (!flags.isEnabled)			return;
	if (!flags.sendUntrigger)		return;

	// virtual call
	UntriggerTarget (vobInstigator);
};


/////////////////////////////
//	Event-Messages
/////////////////////////////

void zCTrigger::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) {
	if (filterFlags.reactToOnTrigger)	ActivateTrigger (vobInstigator);
};

void zCTrigger::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) {
	if (filterFlags.reactToOnTrigger)	DeactivateTrigger (vobInstigator);
}; 

void zCTrigger::OnTouch (zCVob* otherVob) {
	if (filterFlags.reactToOnTouch)		ActivateTrigger (otherVob);
};

void zCTrigger::OnUntouch (zCVob* otherVob) {
	if (filterFlags.reactToOnTouch)		DeactivateTrigger (otherVob);
};

void zCTrigger::OnDamage (zCVob*		otherVob, 
						  zCVob*		inflictorVob, 
						  zREAL			damage,  
						  int			damageType, 
						  const zVEC3&	hitLocation)
{
	if (filterFlags.reactToOnDamage)
	if (damage>0) 
	if (damage>damageThreshold)
		ActivateTrigger (inflictorVob);
};

void zCTrigger::OnMessage (zCEventMessage *eventMessage, zCVob* sourceVob)
{
	// relevante Messages rausfiltern
	zCEventCommon *em = dynamic_cast<zCEventCommon*>(eventMessage);
	if (em) {
		switch (em->GetSubType()) {
			case zCEventCommon::zEVENT_ENABLE:
				flags.isEnabled	= TRUE;
				break;
			case zCEventCommon::zEVENT_DISABLE:
				flags.isEnabled	= FALSE;
				break;
			case zCEventCommon::zEVENT_TOGGLE_ENABLED:
				flags.isEnabled	= !flags.isEnabled;
				break;
		};
	};
}; 

void zCTrigger::OnTimer () 
{
	SetSleeping (TRUE);
	if (fireDelaySec>0) 
	{
		TriggerTarget		(savedOtherVob);
		TriggerTargetPost	();
		zRELEASE			(savedOtherVob);		// Referenz freigeben, wird nicht mehr benoetigt
	} 
};

/////////////////////////////////////////////////////////////////////

void zCTrigger::Archive (zCArchiver &arc) {
	zCTriggerBase::Archive (arc);

	//
	arc.WriteGroupBegin	("Trigger");

	//
	arc.WriteGroupBegin	("ActivationFilter");
	if (!arc.InProperties()) {
		// flags.startEnabled
		// flags.isEnabled
		// flags.sendUntrigger	
		arc.WriteRaw	("flags", &flags, sizeof(flags));								// a b c
	};
	if (arc.InProperties()) {
		arc.WriteBool	("reactToOnTrigger",	filterFlags.reactToOnTrigger);	
		arc.WriteBool	("reactToOnTouch",		filterFlags.reactToOnTouch);	
		arc.WriteBool	("reactToOnDamage",		filterFlags.reactToOnDamage);	
		arc.WriteBool	("respondToObject",		filterFlags.respondToObject);	
		arc.WriteBool	("respondToPC",			filterFlags.respondToPC);	
		arc.WriteBool	("respondToNPC",		filterFlags.respondToNPC);	

		//
		arc.WriteBool	("startEnabled",		flags.startEnabled);					// a
	} else {
		arc.WriteRaw	("filterFlags",			&filterFlags, sizeof(filterFlags));
	};
//	arc.WriteString		("respondToClassName",	respondToClassName);	
	arc.WriteString		("respondToVobName",	respondToVobName);	
//	arc.WriteByte		("numTriggerToActivate",numTriggerToActivate);	
	arc.WriteInt		("numCanBeActivated",	numCanBeActivated);		
	arc.WriteFloat		("retriggerWaitSec",	retriggerWaitSec);	
	arc.WriteFloat		("damageThreshold",		damageThreshold);	
	arc.WriteGroupEnd	("ActivationFilter");

	//
	arc.WriteGroupBegin	("FireBehavior");
//	arc.WriteString		("triggerTarget",		triggerTarget);	
	arc.WriteFloat		("fireDelaySec",		fireDelaySec);	
//	arc.WriteEnum		("repeatTrigger",		"RT_NONE;RT_REPEAT;RT_REPEAT_TOUCHING", repeatTrigger);	
	if (arc.InProperties()) 
		arc.WriteBool	("sendUntrigger",		flags.sendUntrigger);					// c

	arc.WriteGroupEnd	("FireBehavior");

	//
	if (arc.InSaveGame()) 
	{
		// das absolute 'nextTimeTriggerable' muss hier beim Speichern relativ gemacht werden!
		zREAL			writeNextTimeTriggerable = nextTimeTriggerable - ztimer.GetTotalTimeF();
		if (writeNextTimeTriggerable<0)	writeNextTimeTriggerable=0;
		arc.WriteFloat	("nextTimeTriggerable",	writeNextTimeTriggerable);	
		arc.WriteObject	("savedOtherVob",		savedOtherVob);	
		arc.WriteInt	("countCanBeActivated",	countCanBeActivated);		
		arc.WriteBool	("isEnabled", flags.isEnabled);
	};

	arc.WriteGroupEnd	("Trigger");
};

void zCTrigger::Unarchive (zCArchiver &arc) 
{
	// zunaechst einen sauberen Zustand herstellen
	ClearStateInternals ();

	//
	zCTriggerBase::Unarchive (arc);

	//
	if (!arc.InProperties()) {
		arc.ReadRaw		("flags", &flags, sizeof(flags));
	};

	//
	if (arc.InProperties()) {
		filterFlags.reactToOnTrigger	= arc.ReadBool	("reactToOnTrigger");
		filterFlags.reactToOnTouch		= arc.ReadBool	("reactToOnTouch");
		filterFlags.reactToOnDamage		= arc.ReadBool	("reactToOnDamage");
		filterFlags.respondToObject		= arc.ReadBool	("respondToObject");	
		filterFlags.respondToPC			= arc.ReadBool	("respondToPC");
		filterFlags.respondToNPC		= arc.ReadBool	("respondToNPC");
		flags.startEnabled				= arc.ReadBool	("startEnabled");
	} else {
		arc.ReadRaw		("filterFlags",			&filterFlags, sizeof(filterFlags));
	};
//	arc.ReadString		("respondToClassName",	respondToClassName);	
	arc.ReadString		("respondToVobName",	respondToVobName);	
//	arc.ReadByte		("numTriggerToActivate",numTriggerToActivate);
	numCanBeActivated = countCanBeActivated = arc.ReadInt			("numCanBeActivated");	
	arc.ReadFloat		("retriggerWaitSec",	retriggerWaitSec);	
	arc.ReadFloat		("damageThreshold",		damageThreshold);	

	//
//	arc.ReadString		("triggerTarget",		triggerTarget);		triggerTarget.Upper();
	arc.ReadFloat		("fireDelaySec",		fireDelaySec);	
//	repeatTrigger		= zTRepeatTrigger(arc.ReadEnum ("repeatTrigger"));
	if (arc.InProperties()) {
		flags.sendUntrigger	= arc.ReadBool	("sendUntrigger");
	};

	//
	if (arc.InSaveGame()) 
	{
		// das relative 'nextTimeTriggerable' aus dem Archive muss hier beim Laden wieder absolut gemacht werden!
		arc.ReadFloat	("nextTimeTriggerable",	nextTimeTriggerable);	
		arc.ReadObject	("savedOtherVob",		savedOtherVob);	
		countCanBeActivated = arc.ReadInt ("countCanBeActivated");
		if (nextTimeTriggerable>0)	nextTimeTriggerable += ztimer.GetTotalTimeF();
		arc.ReadBool	("isEnabled"),			flags.isEnabled;
	}	
	else flags.isEnabled	= flags.startEnabled;
};


///////////////////////////////////////////////////////////////////////////
//    zCMover
///////////////////////////////////////////////////////////////////////////

/*
	FIXME:
	- kubische Interpolation der Rotations-keys (ueber Quat-Squad)
	- letztes Segment eines Movers mit nur Rot-Keys hat falsche/zu grosse Geschwindigkeit !?
*/

zCMover::zCMover () 
{
	// vob
	SetCollisionClass	(zCCollObjectComplex::S_GetCollObjClass());
	SetCollDetStat		(FALSE);
	SetStaticVob		(TRUE);
	SetIgnoredByTraceRay(FALSE);

	// Trigger
	filterFlags.reactToOnTrigger= TRUE;
	filterFlags.reactToOnTouch	= FALSE;
	filterFlags.reactToOnDamage	= FALSE;

	// internals
	sfxMoving			= 0;
	ClearStateInternals	();
						
	// props			
	moveSpeed			= 0.3F;
	stayOpenTimeSec		= 2.0F;
	touchBlockerDamage	= 0;
	moverLocked			= FALSE;
	moverAniType		= MA_KEYFRAME;
	autoLinkEnabled		= FALSE;

	// 
//	posLerpType			= PL_LINEAR;
	posLerpType			= PL_CURVE;
						
	//					
//	speedType			= ST_CONST;
	speedType			= ST_SLOW_START_END;
//	speedType			= ST_SLOW_START;
//	speedType			= ST_SLOW_END;
//	speedType			= ST_SEG_SLOW_START_END;
//	speedType			= ST_SEG_SLOW_START;
//	speedType			= ST_SEG_SLOW_END;
						
	//					
	moverBehavior		= MB_2STATE_TOGGLE;
//	moverBehavior		= MB_2STATE_TRIGGER_CONTROL;
//	moverBehavior		= MB_2STATE_OPEN_TIMED;
//	moverBehavior		= MB_NSTATE_LOOP;
//	moverBehavior		= MB_NSTATE_SINGLE_KEYS;
						
	//					
	touchBehavior		= TB_TOGGLE;
//	touchBehavior		= TB_WAIT;
};

void zCMover::ClearStateInternals () {
	actKeyPosDelta	= 0;
	actKeyframeF	= 0;
	actKeyframe		= 0;
	nextKeyframe	= 0;
	moveSpeedUnit	= 0;
	advanceDir		= 0;
	moverState		= MOVER_STATE_CLOSED;
	numTriggerEvents= 0;
	stayOpenTimeDest= 0;
	model			= 0;
	autoRotate		= FALSE;

	// Sound entfernen
	if (sfxMoving) {
		zsound->StopSound	(soundMovingHandle);
		zRELEASE			(sfxMoving);
	};
};

zCMover::~zCMover()
{
	model				= 0;
	zRELEASE			(sfxMoving);
};


zBOOL zCMover::CanThisCollideWith (zCVob* vob) 
{ 
	assert (vob);
	// Mover sollen nicht kollidieren mit:
	// - anderen Movern
	// - allen anderen Trigger-Objekten
	if (dynamic_cast<zCTriggerBase*>(vob))		return FALSE;

	// ACHTUNG: Gothic 2 Workaround: zCMover kollidieren auch nicht mit static vobs	(leveldesign muss darauf angepasst werden)
	if (vob->GetStaticVob())					return FALSE;

	// Keine Kollision mit:
	// - was nicht 'gelinkt' werden kann wird ignoriert
	// - Objekte ignorieren, die bereits gelinkt sind (also ParentVob haben)
	if (vob->HasParentVob())					return FALSE;
	if (GetAutoLinkEnabled())
		if (!zCVob::CanAutoLinkWith (vob, this))return FALSE;

	return TRUE;
};

/*
void zCMover::CollectDependentVobs () 
{
	if (!GetHomeWorld()) return;
	zCArray<zCVob*>	vobList;
	zTBBox3D		bbox;

	GetHomeWorld()->CollectVobsInBBox3D (vobList, bbox);
};
*/

void zCMover::UpdateInternals () 
{
	// 
	zRELEASE (sfxMoving);
	if (!soundMoving.IsEmpty()) {
		sfxMoving = zsound->LoadSoundFX (soundMoving);
	};

	//
	if (GetVisual()) {
		model		=  dynamic_cast<zCModel*> (GetVisual());
	};
};

/////////////////////////////
//	Keyframe-specific
/////////////////////////////

zCMover::zTMov_Keyframe zCMover::GetKeyframe (zCVob* keyframeVob) 
{
	zTMov_Keyframe key;
	if (keyframeVob) {
		key.pos = keyframeVob->GetPositionWorld();
		key.quat.Matrix4ToQuat( keyframeVob->trafoObjToWorld );	
	} else {
		key.pos = zVEC3(0);
		key.quat.Identity();
	};
	return key;
};

void zCMover::AdvanceKeyframe_KF () 
{
	SetToKeyframe_KF	(actKeyframeF + ztimer.GetFrameTimeF() * moveSpeedUnit * advanceDir);
};

void zCMover::SetToKeyframe_KF (zREAL newKeyframe) 
{
	if (keyframeList.GetNum()<=1) return;

	actKeyframeF	= newKeyframe;

	//
	if (advanceDir>0) {
		if (Is2StateBehavior()) 
		{
			// 2STATE
			if (actKeyframeF>=keyframeList.GetNum()-1)	{
				actKeyframeF	= zREAL(keyframeList.GetNum()-1);
				advanceDir		= 0;
			};
		} else {
			// NSTATE
			if (moverBehavior==MB_NSTATE_LOOP) {
				if (actKeyframeF>=keyframeList.GetNum())	{
					actKeyframeF	= 0;						// FIXME: step-delta
				};
			} else
			if (moverBehavior==MB_NSTATE_SINGLE_KEYS) {
//				if (actKeyframeF>=nextKeyframe)	
				if (zFloat2Int(zFloor(actKeyframeF))!=actKeyframe)
				{
					actKeyframeF	= zREAL(nextKeyframe);
					advanceDir		= 0;
				};
			};
		};
	} else {	
		if (Is2StateBehavior()) 
		{
			// 2STATE
			if (actKeyframeF<0)	{
				actKeyframeF	= 0;
				advanceDir		= 0; 
			};
		} else {
			// NSTATE
			if (moverBehavior==MB_NSTATE_LOOP) {
				if (actKeyframeF<0)	{
					actKeyframeF	= zREAL(keyframeList.GetNum())-0.00001F;						// FIXME: step-delta
				};
			} else
			if (moverBehavior==MB_NSTATE_SINGLE_KEYS) {
				if (actKeyframeF<=nextKeyframe)	{
					actKeyframeF	= zREAL(nextKeyframe);
					advanceDir		= 0;
				};
			};
		};
	};

	// 
	if (advanceDir>0)	actKeyframe		= zFloat2IntFloor(actKeyframeF);
	else				actKeyframe		= (int)zCeil	 (actKeyframeF);	// 'zFloat2IntCeil' hat leider Grenzprobleme..
	if (actKeyframe<0)						actKeyframe = keyframeList.GetNum()-1; else
	if (actKeyframe>=keyframeList.GetNum())	actKeyframe = 0;

	//
	if (moverBehavior!=MB_NSTATE_SINGLE_KEYS) {
		nextKeyframe	= (actKeyframe+zFloat2Int(advanceDir));
		if (nextKeyframe<0)							nextKeyframe = keyframeList.GetNum()-1; else
		if (nextKeyframe>=keyframeList.GetNum())	nextKeyframe = 0;
	};

	// Der Parameter 'moveSpeed' bezieht sich auf die positionale Bewegungsgeschwindigkeit.
	// Die Rotationsgeschwindigkeit ordnet sich also in der Regel der Bewegung unter.
	// Nur im Falle eines Rot-Only Movers wird 'moveSpeed' als Rotationsgeschw. interpretiert.
	actKeyPosDelta	= keyframeList[nextKeyframe].pos - keyframeList[actKeyframe].pos;
	zREAL lerpLen	= actKeyPosDelta.LengthApprox();
	// 
	if (lerpLen<=0.01F) {
		// nur Rot wird interpoliert
		zVEC3 axis0, axis1;
		zREAL angle;
		keyframeList[actKeyframe] .quat.QuatToAxisAngle (axis0, angle);
		keyframeList[nextKeyframe].quat.QuatToAxisAngle (axis1, angle);
		axis0.NormalizeApprox();
		axis1.NormalizeApprox();
//		zlineCache.Line3D (GetPositionWorld(), GetPositionWorld()+axis0*30, GFX_GREEN);
//		zlineCache.Line3D (GetPositionWorld(), GetPositionWorld()+axis1*30, GFX_RED);
		// FIXME: scheint nicht ganz korrekt zu laufen... stimmen denn axis0, axis1 ????
		lerpLen			= (1-(axis0*axis1));			// misst den Unterschied beider Vektoren im Bereich [0..2], 0=0°,1=90°,2=180°
		lerpLen			= zREAL(500.0F) * lerpLen;
		if (lerpLen<=0) lerpLen=moveSpeed*zREAL(10000.0F);
		moveSpeedUnit	= moveSpeed / lerpLen;
	} else {
		moveSpeedUnit	= moveSpeed / lerpLen;
	};

	if (advanceDir==0) {
		nextKeyframe = actKeyframe;
		if (moverState==MOVER_STATE_OPENING)	FinishedOpening(); else
		if (moverState==MOVER_STATE_CLOSING)	FinishedClosing();
		return;
	};
};

void zCMover::InterpolateKeyframes_KF () 
{
	if (keyframeList.GetNum()<=1) return;

	// pos
	zREAL	frac = actKeyframeF - zFloor(actKeyframeF);

	if (speedType==ST_CONST)				{}										else
	if (speedType==ST_SEG_SLOW_START_END)	frac	= zSinusEase		(frac);		else
	if (speedType==ST_SEG_SLOW_START)		frac	= zSinusSlowStart	(frac);		else
	if (speedType==ST_SEG_SLOW_END)			frac	= zSinusSlowEnd		(frac);		else
	if (moverBehavior!=MB_NSTATE_LOOP)
	{
		zBOOL	startSeg	= (actKeyframeF<1);
		zBOOL	endSeg		= (actKeyframeF>=keyframeList.GetNum()-2);
		if ((speedType==ST_SLOW_START_END) && (startSeg && endSeg))	frac	= zSinusEase		(frac);		else
		if ((speedType==ST_SLOW_START_END) && (startSeg)		  )	frac	= zSinusSlowStart	(frac);		else
		if ((speedType==ST_SLOW_START_END) && (endSeg)			  ) frac	= zSinusSlowEnd		(frac);		else
		if ((speedType==ST_SLOW_START)	   && (startSeg)		  )	frac	= zSinusSlowStart	(frac);		else
		if ((speedType==ST_SLOW_END)	   && (endSeg)			  ) frac	= zSinusSlowEnd		(frac);
	};

	if (advanceDir<0) frac = 1.0F - frac;

	zVEC3	newPosWorld;
	zVEC3   lastPosWorld = this->GetPositionWorld();
	if ((posLerpType==PL_CURVE) &&
	    (keyframeList.GetNum()>2))
	{
		// kubische Interpolation
		int		dir	= zFloat2Int(advanceDir);
		int		v0	= actKeyframe -dir;
		int		v1	= actKeyframe;
		int		v2	= nextKeyframe;
		int		v3	= nextKeyframe+dir;
		if (v0<0)						v0 = keyframeList.GetNum()-1; else
		if (v0>=keyframeList.GetNum())	v0 = 0;
		if (v3<0)						v3 = keyframeList.GetNum()-1; else
		if (v3>=keyframeList.GetNum())	v3 = 0;
		zVEC3	P	= (keyframeList[v3].pos - keyframeList[v2].pos) - (keyframeList[v0].pos-keyframeList[v1].pos);
		zVEC3	Q	= (keyframeList[v0].pos - keyframeList[v1].pos) - P;
		zVEC3	R	= (keyframeList[v2].pos - keyframeList[v0].pos);
		zREAL	frac2= frac*frac;
		newPosWorld	= P*(frac2*frac) + Q*frac2 + R*frac + keyframeList[v1].pos;
	} else {
		// lineare Interpolation
		newPosWorld	= keyframeList[actKeyframe].pos + actKeyPosDelta * frac;
	};

	zVEC3 deltaMove = newPosWorld-lastPosWorld;	

	
	if (!autoRotate)
	{
		SetPositionWorld(newPosWorld);
	}
	else if (deltaMove.Length2()>0)
	{
		SetHeadingWorld	(newPosWorld);
		SetPositionWorld(newPosWorld);
		return;
	}
	else SetPositionWorld(newPosWorld);
	
	
	// rot
	// (FIXME: koennte wie die Pos auch kubisch interpoliert werden ..)
	// lineare Interpolation
	if (0)
//	if ((posLerpType==PL_CURVE) && (keyframeList.GetNum()>2))
	{
// FIXME: klappt leider nocht nicht.....
		int		dir	= zFloat2Int(advanceDir);
		int		v0	= actKeyframe -dir;
		int		v1	= actKeyframe;
		int		v2	= nextKeyframe;
		int		v3	= nextKeyframe+dir;
/*		zClamp (v0, 0, keyframeList.GetNum()-1);
		zClamp (v1, 0, keyframeList.GetNum()-1);
		zClamp (v2, 0, keyframeList.GetNum()-1);
		zClamp (v3, 0, keyframeList.GetNum()-1);
*/
		if (v0<0)						v0 = keyframeList.GetNum()-1; else
		if (v0>=keyframeList.GetNum())	v0 = 0;
		if (v3<0)						v3 = keyframeList.GetNum()-1; else
		if (v3>=keyframeList.GetNum())	v3 = 0;
		for (int i=0; i<keyframeList.GetNum(); i++) {
			keyframeList[i].quat.Normalize();
			keyframeList[i].quat.Unit();
		};
		zCQuat	quat;
		quat.Squad			(frac,	keyframeList[v0].quat, keyframeList[v1].quat,
									keyframeList[v2].quat, keyframeList[v3].quat);
		quat.QuatToMatrix4	(trafoObjToWorld);
		SetTrafo			(trafoObjToWorld); 
//speedType=ST_CONST;
	} else 
	{
		// lineare Interpolation
		zCQuat	quat;
		quat.Slerp			(frac, keyframeList[actKeyframe].quat, keyframeList[nextKeyframe].quat);
		SetRotationWorld	(quat);
	}
};

//////////////////////////////////////////////////////////////

void zCMover::AdvanceMover () 
{
	if (advanceDir==0) return;

	if (moverAniType==MA_KEYFRAME) 
	{
		if (keyframeList.GetNum()>0)
		{
			AdvanceKeyframe_KF		();
			InterpolateKeyframes_KF	();
		};
	} 
	else if (moverAniType==MA_MODEL_ANI) 
	{
		// auf ...
		if ((!model->IsAniActive ("T_OPEN_2_CLOSED")) && (!model->IsAniActive ("T_CLOSED_2_OPEN")))
			advanceDir=0;

//		if (model->IsStateActive ("S_OPEN"))	advanceDir=0; else
//		if (model->IsStateActive ("S_CLOSED"))	advanceDir=0;
		
		if (advanceDir==0) {
			if (moverState==MOVER_STATE_OPENING)	FinishedOpening(); else
			if (moverState==MOVER_STATE_CLOSING)	FinishedClosing();
		};
	};
};

void zCMover::SetToKeyframe (zREAL newKeyframe, zREAL advDir)
{
	advanceDir = advDir;

	//
	if (moverAniType==MA_KEYFRAME) 
	{
		SetToKeyframe_KF (newKeyframe);
		if (advDir==0) {
			// FIXME: dieser Aufruf nur in diesem Fall ?????
			AdvanceKeyframe_KF		();
			InterpolateKeyframes_KF	();
		};
	} 
	else if (moverAniType==MA_MODEL_ANI) 
	{
		int index = int(newKeyframe);

		if (Is2StateBehavior()) {
			if (index==0) 
			{
				if (advanceDir==0)	model->StartAni ("S_CLOSED");
				else				model->StartAni	("T_CLOSED_2_OPEN");
			} else {
				if (advanceDir==0)	model->StartAni ("S_OPEN");
				else				model->StartAni	("T_OPEN_2_CLOSED");
			};
		} else 
		{
			if (index>=model->GetModelProto()->GetAniList().GetNum()) return;
			model->StartAni (zTModelAniID(index));
		};
	};
};

void zCMover::InvertMovement () 
{
	if (Is2StateBehavior()) 
	{
		if (moverState==MOVER_STATE_OPENING)	moverState = MOVER_STATE_CLOSING; else
		if (moverState==MOVER_STATE_CLOSING)	moverState = MOVER_STATE_OPENING;
	};
	SetToKeyframe	(actKeyframeF, -advanceDir);

	if (moverAniType==MA_MODEL_ANI) 
	{
		for (int i=0; i<model->numActiveAnis; i++) {
			if (model->aniChannels[i]->GetDirection()==zMDL_ANIDIR_FORWARD)
				model->aniChannels[i]->SetDirection (zMDL_ANIDIR_REVERSE);
			else
				model->aniChannels[i]->SetDirection (zMDL_ANIDIR_FORWARD);
		};
	};
}; 


//////////////////////////////////////////////
//	Interface	(moverAniType unabh.)
//////////////////////////////////////////////


void zCMover::SetVisual (zCVisual *v) 
{
	zCVob::SetVisual (v);
	model			= 0;
	moverAniType	= MA_KEYFRAME;

	if (GetVisual()) {
		model		=  dynamic_cast<zCModel*> (GetVisual());
		if (model)
			moverAniType=MA_MODEL_ANI;
	};

	//
	if (model) {
		if (moverLocked)	model->StartAni ("S_LOCKED");
		else				model->StartAni ("S_UNLOCKED");
	};
};

void zCMover::StartMovingSound()
{
	zCSoundSystem::zTSound3DParams soundParams;
	soundParams.SetDefaults	();
	soundParams.loopType	= zCSoundSystem::zSND_LOOPING_ENABLED;
	soundMovingHandle		= zsound->PlaySound3D (sfxMoving, this, 2, &soundParams);
};

void zCMover::MoveToKeyframe	(int index) 
{
	if (advanceDir!=0)							return;
	if (moverBehavior!=MB_NSTATE_SINGLE_KEYS)	return;

	SetSleeping			(FALSE);
	moverState			= MOVER_STATE_OPENING;
						
	zClamp				(index, 0, keyframeList.GetNum()-1);
	nextKeyframe		= index;
	SetToKeyframe		(actKeyframeF, +1);
};

void zCMover::DoOpen ()  
{ 
//	zerr.Message		("D: Mover: opening "+zSTRING(actKeyframe));
	SetSleeping			(FALSE);
	moverState			= MOVER_STATE_OPENING;
	SetToKeyframe		(0, +1);
	zsound->PlaySound3D (soundOpenStart	, this, 1);
	StartMovingSound	();
};

void zCMover::FinishedOpening () 
{
//	zerr.Message		("D: Mover: opened "+zSTRING(actKeyframe));
	SetSleeping			(TRUE);
	moverState			= MOVER_STATE_OPEN;
	zsound->StopSound	(soundMovingHandle);
	zsound->PlaySound3D (soundOpenEnd, this, 1);

	if (moverBehavior==MB_2STATE_OPEN_TIMED) {
		stayOpenTimeDest = ztimer.GetTotalTimeF() + (stayOpenTimeSec * zREAL(1000.0F));
		SetSleeping		(FALSE);
	};

	// trigger
	TriggerTarget		(this);		// Das Trigger wird ohne weitere Filter-Tests verschickt
};
	
void zCMover::DoClose () 
{
//	zerr.Message		("D: Mover: closing "+zSTRING(actKeyframe));
	SetSleeping			(FALSE);
	moverState			= MOVER_STATE_CLOSING;
	SetToKeyframe		(zREAL(keyframeList.GetNum()-1), -1);
	zsound->PlaySound3D (soundCloseStart	, this, 1);
	StartMovingSound	();
};

void zCMover::FinishedClosing () 
{
//	zerr.Message		("D: Mover: closed, "+zSTRING(actKeyframe));
	SetSleeping			(TRUE);
	moverState			= MOVER_STATE_CLOSED;
	zsound->PlaySound3D (soundCloseEnd, this, 1);
	zsound->StopSound	(soundMovingHandle);
						
	// untrigger		
	UntriggerTarget		(this);		// Das UnTrigger wird ohne weitere Filter-Tests verschickt
};

void zCMover::Unlock (zCVob* otherVob) 
{
	if (!moverLocked) return;
	if (moverState!=MOVER_STATE_CLOSED) return;

	// der passende Vob zum Aufschliessen ?
	if (!IsKeyToThisMover(otherVob)) return;

	//
	zCModel* model = dynamic_cast<zCModel*> (GetVisual());
	if (model) 
	{
		model->StartAni ("T_LOCKED_2_UNLOCKED");
	};

	//
	zsound->PlaySound3D (soundUnlock, this, 1);
	moverLocked = FALSE;
};

void zCMover::Lock (zCVob* otherVob) 
{
	if (moverLocked) return;
	if (moverState!=MOVER_STATE_CLOSED) return;

	// der passende Vob zum Abschliessen ?
	if (!IsKeyToThisMover(otherVob)) return;

	//
	zCModel* model = dynamic_cast<zCModel*> (GetVisual());
	if (model) 
	{
		model->StartAni ("T_UNLOCKED_2_LOCKED");
	};

	//
	zsound->PlaySound3D (soundLock, this, 1);
	moverLocked = TRUE;
};

zBOOL zCMover::IsKeyToThisMover (zCVob* otherVob) 
{
	if (respondToVobName.IsEmpty()) return TRUE;
	return (respondToVobName==otherVob->GetVobName()) ;
};


void zCMover::TriggerMover (zCVob* otherVob) 
{
	// Locked ?
	if (moverLocked) {
		if (!IsKeyToThisMover(otherVob)) {
			zsound->PlaySound3D (soundUseLocked, this, 1);
			return;
		};
	};

	// Activation Filter
	if (!CanBeActivatedNow(otherVob)) return;
	
	// Locked ?
	if (moverLocked) {
		Unlock (otherVob);
		if (moverLocked) return;	// immer noch locked ?
	};

	//
	if (moverBehavior==MB_NSTATE_SINGLE_KEYS) 
	{
		// ein solches Behaviour kann nicht sinnvoll auf OnTrigger reagieren...
	} 
	else if (moverBehavior==MB_NSTATE_LOOP)  
	{
		if (advanceDir==0)	DoOpen();
		else			InvertMovement();
	} 
	else if (moverBehavior==MB_2STATE_TRIGGER_CONTROL) 
	{
		numTriggerEvents++;
		if (moverState==MOVER_STATE_CLOSED)	DoOpen ();
	} 
	else if (moverBehavior==MB_2STATE_TOGGLE) 
	{
		if (moverState==MOVER_STATE_CLOSED)	DoOpen (); else
		if (moverState==MOVER_STATE_OPEN)	DoClose(); else
			InvertMovement();
	}
	else if (moverBehavior==MB_2STATE_OPEN_TIMED) 
	{
		if (moverState==MOVER_STATE_CLOSED)	DoOpen (); else
		if (moverState==MOVER_STATE_OPEN)	
		{
			if (stayOpenTimeDest==0) {
				stayOpenTimeDest=1;
			} else {
				// Counter wieder auffuellen
				stayOpenTimeDest = ztimer.GetTotalTimeF() + (stayOpenTimeSec * zREAL(1000.0F));
			};
		} else
			InvertMovement();
	};
};

/////////////////////////////
//	Event-Messages
/////////////////////////////


void zCMover::OnTick ()  
{
	//
#ifdef ZENGINE_DEBUG
/*	zrenderer->Vid_BeginLfbAccess();
	screen->Print (0,2000, "state: "+zSTRING(moverState)+", frame: "+zSTRING(actKeyframeF,4));
	zrenderer->Vid_EndLfbAccess();						
*/
#endif

	// openTimed ?
	if (moverState==MOVER_STATE_OPEN) {
		if (stayOpenTimeDest!=0) {
			if (ztimer.GetTotalTimeF()>=stayOpenTimeDest) {
				stayOpenTimeDest=0;
				DoClose();
			};
		};
	};

	// Advance Mover
	AdvanceMover();
};

void zCMover::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	if (!flags.isEnabled) return;

	zERR_MESSAGE(8,0,"D: zMOV: Trigger Mover "+this->GetVobName());

	if (filterFlags.reactToOnTrigger)
	{
		TriggerMover(vobInstigator);
		// TriggerTargetPost();
	}
};


void zCMover::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	if (!flags.isEnabled)		return;	

	zERR_MESSAGE(8,0,"D: zMOV: Untrigger Mover "+this->GetVobName());

	if (moverBehavior==MB_2STATE_TRIGGER_CONTROL) 
	{		
		numTriggerEvents--;		
		if (numTriggerEvents<=0)
		{			
			if (moverState==MOVER_STATE_OPENING)	InvertMovement(); else
			if (moverState==MOVER_STATE_OPEN)		DoClose();
		};
	};
};

void zCMover::OnTouch (zCVob* otherVob) 
{
	// soll der beruehrte Vob als Child gelinkt werden ?
	if (GetAutoLinkEnabled())
	{
		zCVob::CheckAutoLink	(otherVob, this);
	};

	//
	if (!flags.isEnabled)		return;

	// Hier die Blocker-Logik
	if (!otherVob) return;

//	if (otherVob->GetCollType()==zVOB_COLL_TYPE_NO_COLLRESP) return;

	// FIXME: hier evtl. noch ein Behavior, bei dem alles, was im Weg steht gekillt wird (OnDamage)
	//        und dessen Coll-Det mit diesem Mover disabled wird 

	// ignorieren, wenn selbst im Ruhezustand
	if ((GetSleeping()) || (advanceDir==0)) {
		if (filterFlags.reactToOnTouch)
			TriggerMover (otherVob);
		return;
	};

	// Schaden zufuegen ?
	if (touchBlockerDamage>0)
	{
		otherVob->GetEM()->OnDamage	(this, this, touchBlockerDamage, 1, 0);
	};

	// FIXME ???
//	if (touchBehavior==TB_TOGGLE)	InvertMovement();
};

void zCMover::OnDamage (  zCVob*		otherVob, 
						  zCVob*		inflictorVob, 
						  zREAL			damage,  
						  int			damageType, 
						  const zVEC3&	hitLocation)
{
	if (!flags.isEnabled)		return;
	if (filterFlags.reactToOnDamage)
	if (damage>0) 
	if (damage>damageThreshold)
		TriggerMover (inflictorVob);
};

void zCMover::OnMessage (zCEventMessage *eventMessage, zCVob* sourceVob) 
{
	// relevante Messages rausfiltern
	zCTrigger::OnMessage (eventMessage, sourceVob);

	// zCEventMover
	{
		zCEventMover *em = dynamic_cast<zCEventMover*>(eventMessage);
		if (em) {
			switch (em->GetSubType()) {
				case zCEventMover::zEVENT_GOTO_KEY_FIXED_DIRECTLY:
					MoveToKeyframe (em->gotoFixedKeyframe);
					break;
				case zCEventMover::zEVENT_GOTO_KEY_FIXED_ORDER:
					// FIXME: order...
					MoveToKeyframe (em->gotoFixedKeyframe);
					break;
				case zCEventMover::zEVENT_GOTO_KEY_NEXT: 
					{
						int nextKey		= (zFloat2IntFloor(actKeyframeF)+1) % keyframeList.GetNum();
						MoveToKeyframe (nextKey);
						break;
					};
				case zCEventMover::zEVENT_GOTO_KEY_PREV:
					{
						int prevKey		= zFloat2IntFloor(actKeyframeF)-1;
						if (prevKey<0)	 {
							prevKey = keyframeList.GetNum()-1;
							if (prevKey<0)	prevKey=0;
						};
						MoveToKeyframe (prevKey);
						break;
					};
			};
			return;
		};
	};

	// Reset
	{
		zCEventCommon *em = dynamic_cast<zCEventCommon*>(eventMessage);
		if (em) {
			switch (em->GetSubType()) {
				case zCEventCommon::zEVENT_RESET:
					// Reset: in den Keyframe 0 bzw. Zustand CLOSED versetzen
					switch (moverBehavior)
					{
						case MB_NSTATE_SINGLE_KEYS:
							MoveToKeyframe (0);
						case MB_2STATE_TRIGGER_CONTROL:
							// hier ist ein Reset nicht sinnvoll
							break;
						case MB_2STATE_TOGGLE:
							{
								if (moverState==MOVER_STATE_OPEN)	DoClose(); else
									InvertMovement();
							}
							break;
						case MB_2STATE_OPEN_TIMED:
							// hier ist ein Reset nicht sinnvoll
							break;
					};
					break;
			};
			return;
		};
	};
};

// ============================================================

void zCMover::PostLoad () 
//void zCMover::PostUnarchive (zCArchiver &arc)
{
	return;

//	zCTrigger::PostUnarchive (arc);
#if 0
	// eine optionale 'keyframeVobChain' wird ermittelt und deren Keyframes in den Mover eingetragen
	//
	if (!GetHomeWorld())			return;
	if (keyframeVobChain.IsEmpty()) return;

	//
	int				i=0;
	zCVob			*vob =0;
	zTMov_Keyframe	keyframe;
	zSTRING			name(keyframeVobChain);
	vob = GetHomeWorld()->SearchVobByName (keyframeVobChain);

	name.Delete ("0", zSTR_FROM);
	keyframeList.EmptyList();
	while (vob) {
		keyframeList.InsertEnd (GetKeyframe (vob));
		i++;
		vob = GetHomeWorld()->SearchVobByName (name+zSTRING(i));
	};

	// Startposition einnehmen
	SetToKeyframe (0, 0);
#endif
};

// ============================================================

void zCMover::Archive (zCArchiver &arc) {
	zCTrigger::Archive (arc);

	//
	arc.WriteGroupBegin	("Mover");

	//
	arc.WriteEnum		("moverBehavior",		"2STATE_TOGGLE;2STATE_TRIGGER_CTRL;2STATE_OPEN_TIME;NSTATE_LOOP;NSTATE_SINGLE_KEYS", moverBehavior);
//	arc.WriteEnum		("touchBehavior",		"TOGGLE;WAIT", touchBehavior);
	arc.WriteFloat		("touchBlockerDamage",	touchBlockerDamage);	
	arc.WriteFloat		("stayOpenTimeSec",		stayOpenTimeSec);	
	arc.WriteBool		("moverLocked",			moverLocked);	
	arc.WriteBool		("autoLinkEnabled",		autoLinkEnabled);	
	arc.WriteBool		("autoRotate"	  ,		autoRotate);

	// keyframe-dependent
	// spezielle Daten nur speichern, falls wirklich Keyframes vorhanden sind !
	arc.WriteGroupBegin	("Keyframe");
//	arc.WriteString		("vobChainName",		keyframeVobChain);
	arc.WriteWord		("numKeyframes",		keyframeList.GetNum());
	if (keyframeList.GetNum()>0) {
		arc.WriteFloat		("moveSpeed",			moveSpeed);	
		arc.WriteEnum		("posLerpType",			"LINEAR;CURVE", posLerpType);
		arc.WriteEnum		("speedType",			"CONST;SLOW_START_END;SLOW_START;SLOW_END;SEG_SLOW_START_END;SEG_SLOW_START;SEG_SLOW_END", speedType);
		if (!arc.InProperties()) {
			arc.WriteRaw	("keyframes",			keyframeList.GetArray(), sizeof(keyframeList[0])*keyframeList.GetNum());
		};
	};
	arc.WriteGroupEnd	("Keyframe");

	//
//	if (!arc.InProperties()) 
	if (arc.InSaveGame()) 
	{
// FIXME: muessen die alle gespeichert/geladen werden ? sind manche abhaengige-Werte ?
		arc.WriteVec3	("actKeyPosDelta",		actKeyPosDelta);	// KF
		arc.WriteFloat	("actKeyframeF",		actKeyframeF);
		arc.WriteInt	("actKeyframe",			actKeyframe);		// KF
		arc.WriteInt	("nextKeyframe",		nextKeyframe);		
		arc.WriteFloat	("moveSpeedUnit",		moveSpeedUnit);		// KF
		arc.WriteFloat	("advanceDir",			advanceDir);	
		arc.WriteEnum	("moverState",			"", moverState);
		arc.WriteInt	("numTriggerEvents",	numTriggerEvents);
		arc.WriteFloat	("stayOpenTimeDest",	stayOpenTimeDest);
	};

	//
	arc.WriteGroupBegin	("Sound");
	arc.WriteString		("sfxOpenStart",		soundOpenStart);
	arc.WriteString		("sfxOpenEnd",			soundOpenEnd);
	arc.WriteString		("sfxMoving",			soundMoving);
	arc.WriteString		("sfxCloseStart",		soundCloseStart);
	arc.WriteString		("sfxCloseEnd",			soundCloseEnd);
	arc.WriteString		("sfxLock",				soundLock);
	arc.WriteString		("sfxUnlock",			soundUnlock);
	arc.WriteString		("sfxUseLocked",		soundUseLocked);
	arc.WriteGroupEnd	("Sound");

	//
	arc.WriteGroupEnd	("Mover");
};

void zCMover::Unarchive (zCArchiver &arc) {
	zCTrigger::Unarchive (arc);

	// zunaechst einen sauberen Zustand herstellen
	ClearStateInternals();

	//
	moverBehavior	= zTMoverBehavior(arc.ReadEnum ("moverBehavior"));
//	touchBehavior	= zTTouchBehavior(arc.ReadEnum ("touchBehavior"));
	arc.ReadFloat		("touchBlockerDamage",	touchBlockerDamage);	
	arc.ReadFloat		("stayOpenTimeSec",		stayOpenTimeSec);	
	moverLocked			= arc.ReadBool		("moverLocked");	
	zBOOL doAutoLink	= autoLinkEnabled;
	arc.ReadBool		("autoLinkEnabled",		doAutoLink);
	autoLinkEnabled		= doAutoLink;
	zBOOL doAutoRotate = autoRotate;
	arc.ReadBool		("autoRotate"	  ,		doAutoRotate);
	autoRotate = doAutoRotate;
	
#ifdef ZENGINE_DEBUG
//	autoLinkEnabled		= TRUE;
#endif 

	// keyframe-dependent
//	arc.ReadString		("vobChainName",		keyframeVobChain);
	int numKeys = arc.ReadWord		("numKeyframes");
	if (numKeys>0) {
		arc.ReadFloat		("moveSpeed",			moveSpeed);	
		posLerpType		= zTPosLerpType(arc.ReadEnum	("posLerpType"));
		speedType		= zTSpeedType  (arc.ReadEnum	("speedType"));
		if (!arc.InProperties()) {
			keyframeList.EmptyList		();
			keyframeList.AllocAbs		(numKeys);
			keyframeList.MarkNumAllocUsed();
			arc.ReadRaw ("keyframes"	, keyframeList.GetArray(), sizeof(keyframeList[0])*numKeys);
		};
	};
#ifdef ZENGINE_DEBUG
//	moveSpeed = 0.02F;
#endif
	//
//	if (!arc.InProperties()) 
	if (arc.InSaveGame()) 
	{
// FIXME: muessen die alle gespeichert/geladen werden ? sind manche abhaengige-Werte ?
		arc.ReadVec3	("actKeyPosDelta",		actKeyPosDelta);
		arc.ReadFloat	("actKeyframeF",		actKeyframeF);
		arc.ReadInt		("actKeyframe",			actKeyframe);
		arc.ReadInt		("nextKeyframe",		nextKeyframe);
		arc.ReadFloat	("moveSpeedUnit",		moveSpeedUnit);
		arc.ReadFloat	("advanceDir",			advanceDir);
		moverState = zTMoverState (arc.ReadEnum	("moverState"));
		arc.ReadInt		("numTriggerEvents",	numTriggerEvents);
		arc.ReadFloat	("stayOpenTimeDest",	stayOpenTimeDest);
	};

	// Sound
	arc.ReadString		("sfxOpenStart",		soundOpenStart);
	arc.ReadString		("sfxOpenEnd",			soundOpenEnd);
	arc.ReadString		("sfxMoving",			soundMoving);
	arc.ReadString		("sfxCloseStart",		soundCloseStart);
	arc.ReadString		("sfxCloseEnd",			soundCloseEnd);
	arc.ReadString		("sfxLock",				soundLock);
	arc.ReadString		("sfxUnlock",			soundUnlock);
	arc.ReadString		("sfxUseLocked",		soundUseLocked);
#ifdef ZENGINE_DEBUG
//	moveSpeed=0.05F;
#endif

	//
	UpdateInternals();

	// Startposition/Ausgangsposition herstellen
	// (ausser beim Laden eines SaveGame)
	if (!arc.InSaveGame()) 
	{
		SetToKeyframe (0, 0);
	};

	// PostLoad() / vobChains auswerten, muss man bei den Props manuell machen
/*	if (arc.InProperties()) 
	{
		PostLoad();
	};*/
};


/*

  "Mover"-Interface
  
	DoOpen				()
	DoClose				()
	
	MoveToNextKeyframe	()
	MoveToKeyframe		(int)
	SetToKeyframe		(int)
	  
	x Models/Morphs als Ani-Mover
	x Trigger Kopplung
	x Touch/Untouch (=> Trigger/untrigger)
	
	- Mover für Camera-Fahrten
	- Mover von Trigger ableiten ?
	x Mover: Blocker-Verhalten
	x Open/Move/Close Sounds (Cutscenes? pfx? ?)
	x Mover triggern beim FinishedOpen und untriggern beim FinishedClose
	- Master/Slave Mover (Train, Linked Doors)

	  #########
	  
	- Trigger: das Triggern einer ganzen VobListe (zCVob::, zCWorld::)
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void zCTriggerJumper::OnTouch (zCVob* otherVob) 
{
	if (otherVob->GetPhysicsEnabled()) return;

	//
	zVEC3 vel;
	vel = zVEC3(0,1,0);
	vel += otherVob->GetAtVectorWorld() * 1.5F;
	vel.Normalize();

	vel = zVEC3(0,1,0);
	vel.Normalize();
	vel *= 60000*2;

	EndMovement();

	zVEC3 pos = otherVob->GetPositionWorld();
	pos += zVEC3(0,200,0);
	otherVob->SetPositionWorld			(pos);
	otherVob->SetPhysicsEnabled			(TRUE);
	otherVob->RigidBody()->ApplyForceCM	(vel);
//	otherVob->RigidBody()->SetVelocity	(vel);  
};
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

zCEarthquake::zCEarthquake() {
	// zCVob inits
	SetCollDet				(FALSE);
	SetIgnoredByTraceRay	(TRUE);
	SetShowVisual			(FALSE);
	SetStaticVob			(TRUE);

	//
	radiusSquare			= (200*200);
	timeMSec				= 5000;
	amplitude				= zVEC3(2,30,2);
};

void zCEarthquake::OnTrigger(zCVob* otherVob, zCVob *vobInstigator) 
{
	assert (zCCamera::activeCam);
	zCCamera::activeCam->AddTremor (GetPositionWorld(), radiusSquare, timeMSec, amplitude);
};

void zCEarthquake::OnUntrigger(zCVob* otherVob, zCVob *vobInstigator) 
{
	assert (zCCamera::activeCam);
	zCCamera::activeCam->AddTremor (GetPositionWorld(), radiusSquare, timeMSec, amplitude);
};

void zCEarthquake::Archive (zCArchiver &arc) {
	//
	zCEffect::Archive	(arc);

	//
	arc.WriteGroupBegin	("Earthquake");
	arc.WriteFloat		("radius"		, float(sqrt(radiusSquare)));
	arc.WriteFloat		("timeSec"		, (timeMSec / zREAL(1000.0F)));
	arc.WriteVec3		("amplitudeCM"	, amplitude);
	arc.WriteGroupEnd	("Earthquake");
};

void zCEarthquake::Unarchive (zCArchiver &arc) {
	//
	zCEffect::Unarchive	(arc);

	//
	arc.ReadFloat		("radius"		, radiusSquare);	radiusSquare	*= radiusSquare;
	arc.ReadFloat		("timeSec"		, timeMSec);		timeMSec		*= zREAL(1000.0F);
	arc.ReadVec3		("amplitudeCM"	, amplitude);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

zCTriggerTeleport::zCTriggerTeleport() {
	teleportSoundName.Clear();
	teleportSound	= 0;
};

zCTriggerTeleport::~zCTriggerTeleport() {
	zRELEASE (teleportSound);
};

void zCTriggerTeleport::DoTeleport (zCVob* otherVob) 
{
	if (!CanBeActivatedNow(otherVob)) return;

	zCVob *destVob				= GetHomeWorld()->SearchVobByName (triggerTarget);
	if (!destVob) {
		zerr.Warning ("D: (zCTriggerTeleport::DoTeleport): destination vob does not exist");
		return;
	};
	destVob->SetCollDet			(FALSE);	// safety..

	zERR_MESSAGE(5,0,"D: teleport from: "+GetVobName()+", to: "+triggerTarget);

	//
	EndMovement();
	otherVob->EndMovement();

	//
	const zBOOL collDyn			= otherVob->GetCollDetDyn();
	const zBOOL collStat		= otherVob->GetCollDetStat();
	otherVob->SetCollDet		(FALSE);

	// Teleport !
	otherVob->SetTrafo			(destVob->trafoObjToWorld);
//	otherVob->SetPositionWorld	(destVob->GetPositionWorld());
//	otherVob->ResetXZRotations	();
	zsound->PlaySound3D			(teleportSound, otherVob);
/*
	was noch denkbar ist:
	- visuelle Effekte (z.B. PFX)
	- spezielle Effekte beim Model, z.B.
		- spezielle Ani
		- modelScale Effekte / Transparenz
		- Physik-Push mitgeben => auf die Nase fallen
*/
	// cleanup
	otherVob->SetCollDetStat	(collStat);
	otherVob->SetCollDetDyn		(collDyn);
};

void zCTriggerTeleport::OnTouch (zCVob* otherVob) 
{
	DoTeleport (otherVob);
};

void zCTriggerTeleport::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	DoTeleport (otherVob);
};

void zCTriggerTeleport::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	DoTeleport (otherVob);
};

void zCTriggerTeleport::Archive (zCArchiver &arc) {
	//
	zCTrigger::Archive	(arc);

	//
	arc.WriteString	("sfxTeleport"	, teleportSoundName);
};

void zCTriggerTeleport::Unarchive (zCArchiver &arc) {
	//
	zCTrigger::Unarchive	(arc);

	//
	arc.ReadString	("sfxTeleport"	, teleportSoundName);

	// Soundeffekte initialisieren
	if (teleportSound)	teleportSound->Release();
	teleportSound = zsound->LoadSoundFX	(teleportSoundName);

	// FIXME: uuhhh.. damit meshes erlaubt sind und auf Collision reagieren
	SetCollisionClass			(zCCollObjectBoxPassThrough::S_GetCollObjClass());
};

// ==================================================================================================================

/*
weitere denkbare Params:
x startOn
- stopAtOnce
- shapeLineLen (bei diesem Emitter-Typ)
x killVobWhenDone

*/

zCPFXControler::zCPFXControler() {
	killVobWhenDone = TRUE;
	pfxStartOn		= TRUE;
};

zCParticleFX* zCPFXControler::GetPFX () 
{
	zCParticleFX *pfx	= zDYNAMIC_CAST<zCParticleFX>(GetVisual());

	if (!pfx) 
	{
		SetVisual (pfxName);
		pfx	= zDYNAMIC_CAST<zCParticleFX>(GetVisual());
	};
	return pfx;
};

void zCPFXControler::PostLoad ()
{
	// FIXME: NICHT bei saveGames !
#ifndef COMPILING_SPACER
	if (pfxStartOn)	OnTrigger (0,0);
#endif
};

void zCPFXControler::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	zCParticleFX *pfx	= GetPFX();
 
	if (pfx)
	{
#ifdef COMPILING_SPACER
		// im Spacer duerfen Objekte niemals geloescht werden, im Game hingegen schon
		pfx->SetDontKillPFXWhenDone	(TRUE);
#else
		pfx->SetDontKillPFXWhenDone	(!killVobWhenDone);
#endif
		pfx->RestoreEmitterOutput	();
		pfx->CreateParticles		();
	};
};

void zCPFXControler::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	zCParticleFX *pfx	= dynamic_cast<zCParticleFX*>(GetVisual());
	if (!pfx) return;

	pfx->StopEmitterOutput();

#ifdef COMPILING_SPACER
	SetVisual(0);
#endif
};

void zCPFXControler::Archive (zCArchiver &arc) {
	//
	zCEffect::Archive	(arc);

	//
	arc.WriteString ("pfxName",			pfxName);
	arc.WriteBool	("killVobWhenDone", killVobWhenDone);
	arc.WriteBool	("pfxStartOn",		pfxStartOn);
};

void zCPFXControler::Unarchive (zCArchiver &arc) {
	//
	zCEffect::Unarchive	(arc);

	//
	arc.ReadString	("pfxName",			pfxName);
	killVobWhenDone = arc.ReadBool	("killVobWhenDone");
	pfxStartOn		= arc.ReadBool	("pfxStartOn");

	if (arc.InSaveGame())
		pfxStartOn=FALSE;

	if (pfxName.Search(".PFX")==-1)	pfxName += ".PFX";
};


//pfxName=STRING:ZPEE.PFX

// ==================================================================================================================

zCTriggerList::zCTriggerList() {
	Init();
};

void zCTriggerList::Init() {
	listProcess				= LP_ALL;
	actTarget				= 0;
	sendOnTrigger			= TRUE;
	for (int i=0; i<MAX_TARGETS; i++) {
		triggerTargetList[i].Clear();
		fireDelayList[i]	= 0;
	};
};

const zSTRING*	zCTriggerList::GetTriggerTarget (const int i) const 
{
	if (i>=MAX_TARGETS)	return 0;
	return &(triggerTargetList[i]);
};

void zCTriggerList::TriggerActTarget(zCVob *vobInstigator)
{
	// triggert 'list[actTarget]' durch 'vobInstigator'
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTargetList[actTarget], targetVobList);
	for (int j=0; j<targetVobList.GetNum(); j++) {
		if (sendOnTrigger)	targetVobList[j]->GetEM()->OnTrigger	(this, vobInstigator);
		else				targetVobList[j]->GetEM()->OnUntrigger	(this, vobInstigator);
	};
};

zBOOL zCTriggerList::ProcessActTarget (zCVob *vobInstigator) 
{
	if (fireDelayList[actTarget]>0) 
	{
		// 'savedOtherVob' fuer spaetere Aktivierung merken (=> OnTimer())
		zRELEASE			(savedOtherVob);
		savedOtherVob		= vobInstigator;
		if (savedOtherVob)	savedOtherVob->AddRef();

		SetOnTimer			(fireDelayList[actTarget] * zREAL(1000.0F));
		return FALSE;
	} else {
		// 'savedOthervob' wird hier 'missbraucht'
		TriggerActTarget	(vobInstigator);
		return TRUE;
	};
};

void zCTriggerList::FinishActivation() 
{
	// erstmal wieder pennen legen..
	SetSleeping (TRUE);

	// Referenz nicht mehr noetig
	zRELEASE	(savedOtherVob);

	// fuer den Activation Filter
	if (countCanBeActivated>0) countCanBeActivated--;
	nextTimeTriggerable = ztimer.GetTotalTimeF() + (retriggerWaitSec * zREAL(1000.0F));

	// TriggerTargetPost();
};

void zCTriggerList::OnTimer () 
{
	// einen 'delaytes' Target jetzt triggern
	TriggerActTarget(savedOtherVob);

	// evtl. gleich das naechste bearbeiten
	if (listProcess==LP_ALL) {
		actTarget++;	// kein wrap !
		DoTriggering	(savedOtherVob);
	} else {
		// Schluss jetzt? => cleanup für nächste Benutzung
		FinishActivation();
	};
};

void zCTriggerList::DoTriggering (zCVob* vobInstigator) 
{
	if (!flags.isEnabled)			return;
	// ist ein Trigger Prozess noch im Gange ? (über SetTimer)
	if (IsOnTimer())				return;

	// Trigger feuern

	//
	zBOOL			checked[MAX_TARGETS];
	int				numChecked=0;
	memset (checked, 0, sizeof(checked));

	if (listProcess==LP_NEXT_ONE) 
	{
		// das naechste nichtleere triggerTarget aus der Liste finden
		while (triggerTargetList[actTarget].IsEmpty()) {
			if (!checked[actTarget]) {
				checked[actTarget]=TRUE; 
				numChecked++; 
				if (numChecked>=MAX_TARGETS) return;
			};
			actTarget = (actTarget+1) % MAX_TARGETS;
		} 
		if (!ProcessActTarget(vobInstigator))	return;
		actTarget = (actTarget+1) % MAX_TARGETS;	// weiterzaehlen fuer das naechste mal
	} else
	if (listProcess==LP_RAND_ONE) 
	{
		do 
		{
			if (!checked[actTarget]) { 
				checked[actTarget]=TRUE; 
				numChecked++; 
				if (numChecked>=MAX_TARGETS) return;
			};
			// neues Element per Zufall auswaehlen, allerdings sicherstellen, dass nicht dasselbe 2x in Folge kommt
			int oldActTarget = actTarget;
			do {
				actTarget = zRand(MAX_TARGETS);
			} while (actTarget==oldActTarget);
		} while (triggerTargetList[actTarget].IsEmpty());
		if (!ProcessActTarget(vobInstigator))	return;
	} else
	{
		for (; actTarget<MAX_TARGETS; actTarget++)
		{
			if (triggerTargetList[actTarget].IsEmpty()) continue;
			if (!ProcessActTarget(vobInstigator))		return;
		};
		// eine Runde durch alle Targets ist absolviert, counter reseten
		actTarget = 0;
	};

	// Schluss jetzt? => cleanup für nächste Benutzung
	FinishActivation();
};

void zCTriggerList::TriggerTarget (zCVob* vobInstigator) 
{
	sendOnTrigger		= TRUE;
	DoTriggering		(vobInstigator);
};

void zCTriggerList::UntriggerTarget (zCVob* vobInstigator)
{
	//
	if (!flags.sendUntrigger)	return;

	//
	sendOnTrigger		= FALSE;
	DoTriggering		(vobInstigator);

	// FIXME: ??
	// es wird hier noch nichts 'untriggert'
	// moeglich waere:
	// - beim untrigger einfach die gesamte Liste sofort bearbeiten (ohne delays)
	// x Untrigger genau wie Trigger behandeln: dasselbe scheduling mit einer anderen Message
};

void zCTriggerList::Archive (zCArchiver &arc) {
	//
	zCTrigger::Archive	(arc);

	//
	arc.WriteGroupBegin		("TriggerList");
	arc.WriteEnum			("listProcess"		, "LP_ALL;LP_NEXT_ONE;LP_RAND_ONE",	int(listProcess));
	int num=MAX_TARGETS;
	if (!arc.InProperties()) {
		num--;
		for (; num>=0; num--) {
			if (!triggerTargetList[num].IsEmpty()) break;
		};
		num++;
		arc.WriteByte		("numTarget", num);
	};

	zSTRING n;
	for (int i=0; i<num; i++) {
		n = zSTRING(i);
		arc.WriteString		(zSTRING("triggerTarget"+n).ToChar(), triggerTargetList[i]);
		arc.WriteFloat		(zSTRING("fireDelay"+n).ToChar()	, fireDelayList[i]);
	};
	if (arc.InSaveGame()) {
		arc.WriteByte		("actTarget"		, actTarget);
		arc.WriteBool		("sendOnTrigger"	, sendOnTrigger);
	};
	arc.WriteGroupEnd		("TriggerList");
};

void zCTriggerList::Unarchive (zCArchiver &arc) {
	//
	zCTrigger::Unarchive	(arc);

	//
	Init();

	//
	listProcess = zTListProcess(arc.ReadEnum ("listProcess"));
	int num=MAX_TARGETS;
	if (!arc.InProperties()) {
		num = arc.ReadByte		("numTarget");
	};
	zSTRING n;
	for (int i=0; i<num; i++) {
		n = zSTRING(i);
		arc.ReadString			(zSTRING("triggerTarget"+n).ToChar(), triggerTargetList[i]);
		arc.ReadFloat			(zSTRING("fireDelay"+n).ToChar()	, fireDelayList[i]);
		triggerTargetList[i].Upper	();
	};
	if (arc.InSaveGame()) {
		actTarget		= arc.ReadByte	("actTarget");
		arc.ReadBool	("sendOnTrigger", sendOnTrigger);
	};
};

// ==================================================================================================================

zCTouchDamage::zCTouchDamage()
{
	// zCVob inits
	SetVobProperties			();
	
	//
	damage						= 0;
	damageType					= 1;		// bitfield, 0 ist illegal, erster gueltiger Wert ist 1
	damageRepeatDelaySec		= 0;
	damageVolDownScale			= 1.0F;
	damageCollType				= CT_BOX;
};

void zCTouchDamage::OnTouch (zCVob* otherVob)
{
//	zerr.Message ("D: touching: "+otherVob->GetVobName());
	if (!otherVob)	return;
	ProcessToucher	(otherVob);

	if (damageRepeatDelaySec>0) 
	if (!IsOnTimer())
		SetOnTimer	(damageRepeatDelaySec * zREAL(1000.0F));
};

void zCTouchDamage::OnUntouch (zCVob* otherVob)
{
//	zerr.Message ("D: untouching: "+otherVob->GetVobName());
	if (touchVobList.IsEmpty()) {
		SetSleeping (TRUE);
		return;
	};
};

void zCTouchDamage::OnTimer ()
{
	if (touchVobList.IsEmpty()) {
		SetSleeping (TRUE);
		return;
	};

	for (int i=0; i<touchVobList.GetNum(); i++) 
		ProcessToucher (touchVobList[i]);

	if (damageRepeatDelaySec>0) 
		SetOnTimer	(damageRepeatDelaySec * zREAL(1000.0F));
};

void zCTouchDamage::ProcessToucher (zCVob* otherVob)
{
	if (TestCollType(otherVob))	FireDamageMessage (otherVob);
};

zBOOL zCTouchDamage::TestCollType (zCVob* otherVob)
{
	if (damageCollType==CT_NONE)	return FALSE; else
	if (damageCollType==CT_BOX) {
		zTBBox3D bbox = this->GetBBox3DWorld();
		bbox.Scale (damageVolDownScale);
		return bbox.IsIntersecting(otherVob->GetBBox3DWorld());
	} else
	if (damageCollType==CT_POINT) {
		zTBBox3D bbox = otherVob->GetBBox3DWorld();
		bbox.Scale (damageVolDownScale);
		zCParticleFX *pfx = dynamic_cast<zCParticleFX*>(GetVisual());
		if (pfx) 
		{
			// die gescalte 'other' BBox3D gegen alle Partikel des Effektes testen
			zTParticle *particle = pfx->GetFirstParticle();
			if (!particle)	return FALSE;
			do
			{
				if (bbox.IsTrivIn (particle->position))	return TRUE;
				particle = particle->next;
			}while (particle);
		} else 
			return bbox.IsTrivIn (this->GetPositionWorld());
	};
	return FALSE;
};

void zCTouchDamage::FireDamageMessage (zCVob* otherVob)
{
//	zerr.Message ("D: damage: "+otherVob->GetVobName());
	otherVob->GetEM()->OnDamage (this, this, damage, damageType, (otherVob->GetPositionWorld()+this->GetPositionWorld())*0.5F);
};

void zCTouchDamage::Archive (zCArchiver &arc)
{
	//
	zCEffect::Archive	(arc);

	//
	arc.WriteGroupBegin	("TouchDamage");
	arc.WriteFloat		("damage"				, damage);
	arc.WriteGroupBegin	("DamageType");
	{
		// DamageType
		int index=0;
		do
		{
			const char*		damageTypeName		= GetDamageTypeArcEnum(index);
			if (damageTypeName)
			{
				const zBOOL		damageActive	= ((1 << index) & this->damageType)!=0;
				arc.WriteBool	(damageTypeName	,  damageActive);
				index++;
			} else
				break;
		} while(1);
	};
	arc.WriteGroupEnd	("DamageType");
	arc.WriteFloat		("damageRepeatDelaySec"	, damageRepeatDelaySec);
	arc.WriteFloat		("damageVolDownScale"	, damageVolDownScale);
	arc.WriteEnum		("damageCollType"		, "NONE;BOX;POINT"		, damageCollType);
	arc.WriteGroupEnd	("TouchDamage");
};

void zCTouchDamage::Unarchive (zCArchiver &arc)
{
	//
	zCEffect::Unarchive (arc);

	//
	arc.ReadFloat		("damage"				, damage);
	{
		// DamageType
		int	index			= 0;
		this->damageType	= 0;
		do
		{
			const char*		damageTypeName		= GetDamageTypeArcEnum(index);
			if (damageTypeName)
			{
				zBOOL			damageActive	= FALSE;
				arc.ReadBool	(damageTypeName	,  damageActive);
				damageType						|= (damageActive << index);
				index++;
			} else
				break;
		} while(1);
		if (index==0)
			this->damageType	= 1;
	};
	arc.ReadFloat		("damageRepeatDelaySec"	, damageRepeatDelaySec);
	arc.ReadFloat		("damageVolDownScale"	, damageVolDownScale);
	damageCollType		= zTDamageCollType(arc.ReadEnum		("damageCollType"));
};

const char* zCTouchDamage::GetDamageTypeArcEnum	(const zDWORD index)
{
	// higher levels override and put out strings for each index, like "damagePoint", "damageBlunt", "damageMagic", ..
	if (index==0)	return "damageTypeDefault";
	else			return 0;
};

void zCTouchDamage::SetVisual (zCVisual *v)
{
	zCEffect::SetVisual	(v);

	// Ein Visual koennte Vob-Props veraendern. Die noetigen VobProps werden hier
	// wieder zurueckgesetzt.
	SetVobProperties	();
};

void zCTouchDamage::SetVobProperties ()
{
	SetCollisionClass			(zCCollObjectBoxPassThrough::S_GetCollObjClass());
	SetCollDetStat				(FALSE);
	SetCollDetDyn				(TRUE);
	SetIgnoredByTraceRay		(TRUE);
	SetShowVisual				(TRUE);
};

// ==================================================================================================================

zCTouchAnimate::zCTouchAnimate()
{
	SetVobProperties();
	touchSound=0;
};

zCTouchAnimate::~zCTouchAnimate()
{
	zRELEASE (touchSound);
};

void zCTouchAnimate::OnTouch (zCVob* otherVob)
{
	if (!otherVob)				return;
	// LOD: nicht aktivieren, wenn zu weit von der aktiven Cam entfernt
	if (GetSleeping())
	if (zCCamera::activeCam)
	if ((zCCamera::activeCam->GetVob()->GetPositionWorld()-this->GetPositionWorld()).LengthApprox()>zREAL(1500.0F))
	{
		return;
	};

//	zerr.Message ("D: touching: "+otherVob->GetVobName());
	SetSleeping		(FALSE);
};

void zCTouchAnimate::OnUntouch (zCVob* otherVob)
{
//	zerr.Message ("D: untouching: "+otherVob->GetVobName());
	if (touchVobList.IsEmpty()) {
		SetSleeping (TRUE);
		return;
	};
};

void zCTouchAnimate::OnTick ()
{
	// wieder einschlafen ?
	if (touchVobList.IsEmpty()) {
		if (IsAniActive())	return;
//		zerr.Message ("D: onTick, goToSleep");
		SetSleeping (TRUE);
		return;
	};

	// dieser Vob ist zur Ruhe gekommen, wird aber nun von einem bereits in Beruehrung
	// stehenden Vob erneut angestossen (falls dieser sich schnell genug bewegt)..
	if (!IsAniActive())	
	{
		zBOOL goToSleep = TRUE;
		for (int i=0; i<touchVobList.GetNum(); i++)
		{
			zCVob *otherVob = touchVobList[i];
			zREAL vel		= otherVob->GetVelocity().Length2();
			if (vel>zREAL(10.0F))
			if (IsTouching(otherVob))
			{
				StartAni();
				goToSleep = FALSE;
				break;
			};
			if (( otherVob->GetPhysicsEnabled())	||
				(!otherVob->GetSleeping())		
			   )
				goToSleep = FALSE;
		};

		// Vob soll sich trotz Beruehrung wieder schlafenlegen, wenn ...
		if (goToSleep) {
//			zerr.Message ("D: onTick, goToSleep");
			SetSleeping (TRUE);
			return;
		};
	};
};

zBOOL zCTouchAnimate::IsTouching (zCVob *otherVob)
{
	zTBBox3D bbox = this->GetBBox3DWorld();
	bbox.Scale (zREAL(0.5F));
	return bbox.IsIntersecting (otherVob->GetBBox3DWorld());
};

void zCTouchAnimate::StartAni ()
{
	zCVisualAnimate *visual = dynamic_cast<zCVisualAnimate*>(GetVisual());
	if (!visual) return;

	//
	const zSTRING *aniName;
	aniName = visual->GetAnyAnimation();
	if (aniName)	visual->StartAnimation (*aniName);

	// Sound
	if (!touchSound)
	{
		// hier wird der Sound 'onDemand' geladen, es wird sowohl scriptInstanz als auch .wave File versucht
		zSTRING soundName = GetSoundName();
		touchSound = zsound->LoadSoundFX (soundName);
		if (!touchSound)
			touchSound = zsound->LoadSoundFX (soundName+".wav");
	};
	zsound->PlaySound3D (touchSound, this, 1);
};

zSTRING zCTouchAnimate::GetSoundName ()
{
	if (!GetVisual())	return "";
	zPATH path(GetVisual()->GetVisualName());
	return path.GetFilename();
};

void zCTouchAnimate::StopAni ()
{
	zCVisualAnimate *visual = dynamic_cast<zCVisualAnimate*>(GetVisual());
	if (!visual) return;

	//
	const zSTRING *aniName;
	aniName = visual->GetAnyAnimation();
	if (aniName)	visual->StopAnimation (*aniName);
};

zBOOL zCTouchAnimate::IsAniActive ()
{
	zCVisualAnimate *visual = dynamic_cast<zCVisualAnimate*>(GetVisual());
	if (!visual) return FALSE;

	//
	const zSTRING *aniName;
	aniName = visual->GetAnyAnimation();
	if (aniName)	return visual->IsAnimationActive(*aniName);
	else			return FALSE;
};

void zCTouchAnimate::Archive (zCArchiver &arc)
{
	//
	zCEffect::Archive	(arc);
};

void zCTouchAnimate::Unarchive (zCArchiver &arc)
{
	//
	zCEffect::Unarchive (arc);

	// alten Soundeffekt entfernen (neuer wird onDemand eingeladen, wichtig: Name koennte sich geaendert haben!)
	zRELEASE (touchSound);

	//
	SetVobProperties	();
};

void zCTouchAnimate::SetVisual (zCVisual *v)
{
	zCEffect::SetVisual	(v);

	// Ein Visual koennte Vob-Props veraendern. Die noetigen VobProps werden hier
	// wieder zurueckgesetzt.
	SetVobProperties	();
};

void zCTouchAnimate::SetVobProperties ()
{
	SetCollisionClass			(zCCollObjectBoxPassThrough::S_GetCollObjClass());
	SetCollDetStat				(FALSE);
	SetCollDetDyn				(TRUE);
	SetIgnoredByTraceRay		(TRUE);
	SetShowVisual				(TRUE);
};

// ==================================================================================================================

// zCTouchAnimateSound

zCTouchAnimateSound::zCTouchAnimateSound()
{
	touchSoundName.Clear();
};

void zCTouchAnimateSound::Archive (zCArchiver &arc)
{
	zCTouchAnimate::Archive	(arc);

	//
	arc.WriteString	("sfxTouch"	, touchSoundName);
};

void zCTouchAnimateSound::Unarchive (zCArchiver &arc)
{
	zCTouchAnimate::Unarchive (arc);

	//
	arc.ReadString	("sfxTouch"	, touchSoundName);
};

zSTRING zCTouchAnimateSound::GetSoundName ()
{
	return touchSoundName;
};

// ==================================================================================================================

zCVobAnimate::zCVobAnimate ()
{
	// 'factory defaults'
	SetCollDetStat				(FALSE);
	SetCollDetDyn				(FALSE);
	SetIgnoredByTraceRay		(TRUE);

	//
	startOn						= TRUE;
	isRunning					= FALSE;
};

void zCVobAnimate::SetVisual (zCVisual *v)
{
	//
	zCEffect::SetVisual (v);

	if ((startOn) || (isRunning))
		StartAni();
};

void zCVobAnimate::StartAni ()
{
	isRunning = TRUE;

	// Ani starten
	zCVisualAnimate *visual = dynamic_cast<zCVisualAnimate*>(GetVisual());
	if (visual) 
	{
		const zSTRING *aniName;
		aniName = visual->GetAnyAnimation();
		if (aniName)	visual->StartAnimation (*aniName);
	};
};

void zCVobAnimate::StopAni ()
{
	isRunning = FALSE;
	// FIXME:...;
};

void zCVobAnimate::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	StartAni();
};

void zCVobAnimate::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) {
	StopAni();
};

void zCVobAnimate::Archive (zCArchiver &arc) 
{
	zCEffect::Archive (arc);

	//
	arc.WriteBool		("startOn", startOn);
	if (arc.InSaveGame()) {
		arc.WriteBool	("isRunning", isRunning);
	};
};

void zCVobAnimate::Unarchive (zCArchiver &arc) 
{
	zCEffect::Unarchive (arc);

	//
	isRunning=FALSE;

	//
	startOn		= arc.ReadBool	("startOn");
	if (arc.InSaveGame()) {
		isRunning= arc.ReadBool	("isRunning");
	};

	//
	if (((arc.InSaveGame() && (isRunning)) ||
		(startOn)))
	{
		StartAni();
	};
};


// ==================================================================================================================

zCVobLensFlare::zCVobLensFlare()
{
	// 'factory defaults'
	SetCollDetStat				(FALSE);
	SetCollDetDyn				(FALSE);
	SetIgnoredByTraceRay		(TRUE);

	//
	lensFlareFX=0;
};

zCVobLensFlare::~zCVobLensFlare()
{
	lensFlareFX	= 0;		// nicht deleten!
};

zBOOL zCCFASTCALL  zCVobLensFlare::Render (zTRenderContext &renderContext)
{
	zBOOL res = zCEffect::Render(renderContext);

	if (lensFlareFX)
		lensFlareFX->RenderLensFlares(this);
	return res;
};

void zCVobLensFlare::SetLensFlareFXByName (const zSTRING& lensFlareFXName)
{
	zRELEASE (lensFlareFX);
	if (lensFlareFXName.Length()<=0)	return;
	zCClassDef *lensClass	= zCLensFlareFX::GetStaticClassDef();
	lensFlareFX				= (zCLensFlareFX*)(lensClass->SearchObject (lensFlareFXName));
};

void zCVobLensFlare::Archive (zCArchiver &arc)
{
	//
	zCEffect::Archive		(arc);

	// Die "#ifdef COMPILING_SPACER" Klauseln sind eine Speicher-Optimierung:
	// Im Game braucht der Name des FX nicht explizit in diesem Objekt gespeichert werden, falls es
	// den Effekt gar nicht gibt. Im Spacer hingegen schon, damit falls der Effekt nicht 
	// vorhanden ist (weil z.B. Daten fehlen), der Name des Effekts nicht verloren geht.

#ifdef COMPILING_SPACER
	arc.WriteString			("lensflareFX", lensFlareFXName);
#else
	arc.WriteString			("lensflareFX", lensFlareFX ? lensFlareFX->GetObjectName() : "");
#endif
};

void zCVobLensFlare::Unarchive (zCArchiver &arc)
{
	//
	zCEffect::Unarchive		(arc);
#ifdef COMPILING_SPACER
	arc.ReadString			("lensflareFX", lensFlareFXName);	lensFlareFXName.Upper();
	SetLensFlareFXByName	(lensFlareFXName);
#else
	SetLensFlareFXByName	(arc.ReadString ("lensflareFX"));
#endif

	this->SetShowVisual		(TRUE);
};

// ==================================================================================================================

zCEventScreenFX::zCEventScreenFX (const zTEventScreenFXSubType	sub, 
								  const zREAL					duration, 
								  const zCOLOR					color,
								  const zREAL					fovDeg
								  )
{ 
	Clear(); 
	this->subType		= zTSubType(sub); 
	this->duration		= duration;
	this->color			= color;
	this->fovDeg		= fovDeg;
};

void zCEventScreenFX::Clear() 
{
	duration	= 2.0F;
	color		= zCOLOR(0,0,0,255);
	fovDeg		= 0.0F;
};

zSTRING zCEventScreenFX::MD_GetSubTypeString	(int n)
{
	switch (n) {
		case zEVENT_BLEND_FADEIN:	return zSTRING("BLEND_FADE_IN");
		case zEVENT_BLEND_FADEOUT:	return zSTRING("BLEND_FADE_OUT");
		case zEVENT_CINEMA_FADEIN:	return zSTRING("CINEMA_FADE_IN");
		case zEVENT_CINEMA_FADEOUT:	return zSTRING("CINEMA_FADE_OUT");
		case zEVENT_FOV_MORPH:		return zSTRING("FOV_MORPH");
	};
	return zSTRING("");
};

zCEventScreenFX::zTTimeBehavior zCEventScreenFX::MD_GetTimeBehavior () 
{ 
	return (duration<=0) ? TBZero : TBFix;
};

zREAL zCEventScreenFX::MD_GetMinTime () 
{ 
	return duration;
};

void zCEventScreenFX::Pack (zCBuffer& buffer, zCEventManager* evManContext) {
	zCEventMessage::Pack	(buffer, evManContext);
	buffer.WriteFloat		(duration);
	if (GetSubType()==zEVENT_FOV_MORPH)		buffer.WriteFloat		(fovDeg);
	else									buffer.Write			(&color, sizeof(color));
};

void zCEventScreenFX::Unpack (zCBuffer& buffer, zCEventManager* evManContext) {
	zCEventMessage::Unpack	(buffer, evManContext);
	duration				= buffer.ReadFloat();
	if (GetSubType()==zEVENT_FOV_MORPH)		fovDeg					= buffer.ReadFloat();
	else									buffer.Read				(&color, sizeof(color));
};

void zCEventScreenFX::Archive (zCArchiver& arc) {
	zCEventMessage::Archive (arc);
	arc.WriteFloat			("duration"		, duration);
	arc.WriteColor			("color"		, color);
	arc.WriteFloat			("fovDeg"		, fovDeg);
};

void zCEventScreenFX::Unarchive (zCArchiver& arc) {
	zCEventMessage::Unarchive (arc);
	arc.ReadFloat			("duration"		, duration);
	arc.ReadColor			("color"		, color);
	arc.ReadFloat			("fovDeg"		, fovDeg);
};

// ==================================================================================================================

zCVobScreenFX::zCVobScreenFX()
{
	blend.Clear		();
	cinema.Clear	();
	fovMorph.Clear	();
	fovSaved		= fovSavedFirst = 0;
};

void zCVobScreenFX::OnMessage (zCEventMessage *eventMessage, zCVob* sourceVob)
{
	zCEventScreenFX *msg = dynamic_cast<zCEventScreenFX*>(eventMessage);
	if (!msg) return;
	switch (msg->GetSubType()) {
		case zCEventScreenFX::zEVENT_BLEND_FADEIN:	StartEffect	(msg->duration, msg->color, TRUE, blend);	break;
		case zCEventScreenFX::zEVENT_BLEND_FADEOUT:	StartEffect	(msg->duration, msg->color, FALSE, blend);	break;
		case zCEventScreenFX::zEVENT_CINEMA_FADEIN:	StartEffect	(msg->duration, msg->color, TRUE, cinema);	break;
		case zCEventScreenFX::zEVENT_CINEMA_FADEOUT:StartEffect	(msg->duration, msg->color, FALSE, cinema); break;
		case zCEventScreenFX::zEVENT_FOV_MORPH:		
			StartEffect		(msg->duration, msg->color, FALSE, fovMorph); 
			fovMorph.fovDeg	= msg->fovDeg;
			break;
	};
}; 


void zCVobScreenFX::StartEffect (	const zREAL					duration, 
									const zCOLOR				color, 
									const zBOOL					fadeIn, 
									zTScreenFXSet				&effectSet)
{
	effectSet.weight	= zREAL(fadeIn ? 1 : 0);
	effectSet.velo		= (duration<=0) ? 999999.0F : 1 / (duration * zREAL(1000.0F));
	effectSet.color		= color;
	effectSet.visible	= TRUE;

	if (fadeIn)		effectSet.velo = -effectSet.velo;
	SetSleepingMode (zVOB_AWAKE_DOAI_ONLY);

	// hier bereits fuer den naechsten Frame den Effekt sichtbar machen (??)
	OnTick			();
};

zCOLOR zCVobScreenFX::CalcEffectColor (zTScreenFXSet &effectSet)
{
	effectSet.weight	+= ztimer.GetFrameTimeF() * effectSet.velo;
	if (effectSet.weight<0) {
		effectSet.weight	= 0;
		effectSet.visible	= FALSE;
	} else 
	if (effectSet.weight>1) {
		effectSet.weight	= 1;
		effectSet.visible	= TRUE;
	};
	zCOLOR col			= effectSet.color;
	col.SetAlphaByte	(zBYTE(zFloat2Int (effectSet.weight*effectSet.color.GetAlphaByte())));
	return col;
};

void zCVobScreenFX::OnTick () 
{
	zCCamera *cam = zCCamera::activeCam;
	if (cam)
	{
		if (blend.visible)	
		{
			cam->SetRenderScreenFade			(CalcEffectColor (blend));
			cam->SetRenderScreenFadeTex			(blend.texName);
			cam->SetRenderScreenFadeTexAniFPS	(blend.texAniFPS);
			cam->SetRenderScreenFadeTexBlendFunc(blend.blendFunc);

		}
		if (cinema.visible)	cam->SetRenderCinemaScope	(CalcEffectColor (cinema));

		// FOV-Morph
		if (fovMorph.visible) {
			if (fovMorph.weight==0) {
				cam->GetFOV		(fovSaved[0], fovSaved[1]);
				if (fovSavedFirst[0]==0)
					fovSavedFirst = fovSaved;
			};

			if (fovMorph.fovDeg<=0) {
				// deg <=0 ? => UrsprungsFOV wieder herstellen
				fovMorph.fovDeg	= fovSavedFirst[0];
			};

			CalcEffectColor (fovMorph);
			zREAL	aspect	= fovSavedFirst[1] / fovSavedFirst[0];
			zREAL	fovY	= fovMorph.fovDeg * aspect;
			zVEC2	fov		= zLerp (fovMorph.weight, fovSaved, zVEC2(fovMorph.fovDeg, fovY));
			cam->SetFOV		(fov[0], fov[1]);
		};
	};

	// wieder einschlafen ?
	if ((!blend.visible) && (!cinema.visible) && (!fovMorph.visible)) {
		SetSleeping (TRUE);
	};
};					

void zCVobScreenFX::Archive (zCArchiver &arc) 
{
	zCEffect::Archive (arc);
	if (arc.InSaveGame()) {
		arc.WriteRaw		("blend"		, &blend		, sizeof(blend));
		arc.WriteRaw		("cinema"		, &cinema		, sizeof(cinema));
		arc.WriteRaw		("fovMorph"		, &fovMorph		, sizeof(fovMorph));
		arc.WriteRawFloat	("fovSaved"		, &fovSaved		, sizeof(fovSaved));
		arc.WriteRawFloat	("fovSaved1st"	, &fovSavedFirst, sizeof(fovSavedFirst));
	};
};

void zCVobScreenFX::Unarchive (zCArchiver &arc) 
{
	zCEffect::Unarchive (arc);
	if (arc.InSaveGame()) {
		arc.ReadRaw			("blend"		, &blend		, sizeof(blend));
		arc.ReadRaw			("cinema"		, &cinema		, sizeof(cinema));
		arc.ReadRaw			("fovMorph"		, &fovMorph		, sizeof(fovMorph));
		arc.ReadRawFloat	("fovSaved"		, &fovSaved		, sizeof(fovSaved));
		arc.ReadRawFloat	("fovSaved1st"	, &fovSavedFirst, sizeof(fovSavedFirst));
	};
};

// ==================================================================================================================

zCMessageFilter::zCMessageFilter() {
	sendWhenTriggered	= MT_TRIGGER;
	sendWhenUntriggered	= MT_UNTRIGGER;
};

void zCMessageFilter::ProcessMessage (const zTMessageType outMessageType, zCVob *vobInstigator) 
{
	if (outMessageType==MT_NONE) return;

	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);

	int i;
	switch (outMessageType)
	{
		case MT_TRIGGER:
			for (i=0; i<targetVobList.GetNum(); i++) 
				targetVobList[i]->GetEM()->OnTrigger (this, vobInstigator);
			break;
		case MT_UNTRIGGER:
			for (i=0; i<targetVobList.GetNum(); i++) 
				targetVobList[i]->GetEM()->OnUntrigger (this, vobInstigator);
			break;
		case MT_ENABLE:
			for (i=0; i<targetVobList.GetNum(); i++) {
				zCEventMessage *em = zNEW(zCEventCommon(zCEventCommon::zEVENT_ENABLE));
				targetVobList[i]->GetEM()->OnMessage (em, this);
			};
			break;
		case MT_DISABLE:
			for (i=0; i<targetVobList.GetNum(); i++) {
				zCEventMessage *em = zNEW(zCEventCommon(zCEventCommon::zEVENT_DISABLE));
				targetVobList[i]->GetEM()->OnMessage (em, this);
			};
			break;
		case MT_TOGGLE_ENABLED:
			for (i=0; i<targetVobList.GetNum(); i++) {
				zCEventMessage *em = zNEW(zCEventCommon(zCEventCommon::zEVENT_TOGGLE_ENABLED));
				targetVobList[i]->GetEM()->OnMessage (em, this);
			};
			break;
		case MT_RESET:
			for (i=0; i<targetVobList.GetNum(); i++) {
				zCEventMessage *em = zNEW(zCEventCommon(zCEventCommon::zEVENT_RESET));
				targetVobList[i]->GetEM()->OnMessage (em, this);
			};
			break;

	};
};

void zCMessageFilter::OnTrigger	(zCVob *otherVob, zCVob *vobInstigator) {
	ProcessMessage (zTMessageType(sendWhenTriggered), vobInstigator);
};

void zCMessageFilter::OnUntrigger (zCVob *otherVob, zCVob *vobInstigator) {
	ProcessMessage (zTMessageType(sendWhenUntriggered), vobInstigator);
};

void zCMessageFilter::Archive (zCArchiver &arc) 
{
	zCTriggerBase::Archive	(arc);

	//
	static const char enumString[] = "MT_NONE;MT_TRIGGER;MT_UNTRIGGER;MT_ENABLE;MT_DISABLE;MT_TOGGLE_ENABLED";
	arc.WriteEnum		("onTrigger",		enumString, sendWhenTriggered);
	arc.WriteEnum		("onUntrigger",		enumString, sendWhenUntriggered);
};

void zCMessageFilter::Unarchive (zCArchiver &arc) 
{
	zCTriggerBase::Unarchive (arc);

	//
	sendWhenTriggered	= arc.ReadEnum	("onTrigger");
	sendWhenUntriggered	= arc.ReadEnum	("onUntrigger");
};

// ==================================================================================================================

void zCTriggerUntouch::OnUntouch (zCVob* otherVob)
{
	// triggers when it is 'untouched' by the last non-living object
	// kein totes Objekt => raus
	if (otherVob->GetCharacterClass()!=zVOB_CHAR_CLASS_NONE)	return;

	//
	int numObj = 0;
	for (int i=0; i<touchVobList.GetNum(); i++)
	{
		if (touchVobList[i]->GetCharacterClass()==zVOB_CHAR_CLASS_NONE) {
			numObj++;
			break;
		};
	};

	zCVob* itemVob = NULL;

	for (i=0; i<touchVobList.GetNum(); i++)
	{
		if (touchVobList[i]->GetVobType()==zVOB_TYPE_ITEM) 
		{
			itemVob = touchVobList[i];
			break;
		};
	}

	
	if (numObj==1 || itemVob) 
	{
		// eine ganze Liste von TriggerTarget Vobs ermitteln !
		zCArray<zCVob*> targetVobList;
		GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
		for (int i=0; i<targetVobList.GetNum(); i++) {
			targetVobList[i]->GetEM()->OnTrigger	(this, otherVob);
		};
	}
};

// ==================================================================================================================

zCCodeMaster::zCCodeMaster() {
	memset (slaveTriggeredList, 0, sizeof(slaveTriggeredList[0])*MAX_SLAVES);
	Init();
};

zCCodeMaster::~zCCodeMaster() {
	Init();
};

void zCCodeMaster::Init() {
	for (int i=0; i<MAX_SLAVES; i++) 
		slaveVobNameList[i].Clear();
	//
	triggerTargetFailure.Clear	();
	flags.orderRelevant			= FALSE;
	flags.untriggerCancels		= FALSE;
	flags.firstFalseIsFailure	= FALSE;

	//
	Reset();
};

void zCCodeMaster::Reset() {
	for (int i=0; i<MAX_SLAVES; i++)
		zRELEASE (slaveTriggeredList[i]);
	numSlavesTriggered	= 0;
};

void zCCodeMaster::FireTriggerSuccess (zCVob *vobInstigator) {
	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		targetVobList[i]->GetEM()->OnTrigger	(this, vobInstigator);
	};
	Reset();
};

void zCCodeMaster::FireTriggerFailure (zCVob *vobInstigator) {
	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTargetFailure, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		targetVobList[i]->GetEM()->OnTrigger	(this, vobInstigator);
	};
	Reset();
};

int zCCodeMaster::GetSlaveNr (zCVob* otherVob) 
{
	if (!otherVob) return -1;
	const zSTRING& otherVobName = otherVob->GetVobName();
	if (otherVobName.IsEmpty()) return -1;
	for (int i=0; i<MAX_SLAVES; i++) 
	{
		if (otherVobName==slaveVobNameList[i]) {
			return i;
		};
	};
	return -1;
};

void zCCodeMaster::OnTrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	// ist der SourceVob ueberhaupt Teil der Sequenz?
	int		i;
	int		slaveNr = GetSlaveNr (otherVob);
	if (slaveNr<0) return;

	// SourceVob in Sequenz eintragen
	// und feuern bei Bedarf
	if (flags.orderRelevant)
	{
		slaveTriggeredList[numSlavesTriggered]	= otherVob;	
		otherVob->AddRef();

		// Sequenz vollendet ?
		zBOOL matching = TRUE;
		for (i=0; i<numSlavesTriggered+1; i++) {
			if (!(slaveTriggeredList[i]) ||
				 (slaveTriggeredList[i]->GetVobName()!=slaveVobNameList[i]))
			{ 
				matching=FALSE; 
				break; 
			};
		};

		// 
		int numSlaves = 0;
		for (i=0; i<MAX_SLAVES; i++) 
			if (!slaveVobNameList[i].IsEmpty()) numSlaves++;

		//
		numSlavesTriggered++;

		//
		if (matching)
		{
			if (numSlavesTriggered==numSlaves)
				FireTriggerSuccess (vobInstigator);
		} else {
			if ((numSlavesTriggered==numSlaves) || (flags.firstFalseIsFailure)) 
				FireTriggerFailure (vobInstigator);
		};

		//
		if (numSlavesTriggered>=MAX_SLAVES)		numSlavesTriggered=0;
	} else 
	{
		otherVob->AddRef			();
		zRELEASE					(slaveTriggeredList[slaveNr]);
		slaveTriggeredList[slaveNr]	= otherVob;	

		zBOOL complete=TRUE;
		for (i=0; i<MAX_SLAVES; i++) {
			if (!slaveTriggeredList[i])
			if (!slaveVobNameList[i].IsEmpty())
			{
				complete=FALSE; 
				break; 
			};
		};
		if (complete)
			FireTriggerSuccess(vobInstigator);
	};
};

void zCCodeMaster::OnUntrigger (zCVob* otherVob, zCVob *vobInstigator) 
{
	if (!flags.orderRelevant)
	if (flags.untriggerCancels)
	{
		int slaveNr = GetSlaveNr (otherVob);
		if (slaveNr<0) return;
		zRELEASE (slaveTriggeredList[slaveNr]);
	};
};

void zCCodeMaster::OnMessage (zCEventMessage *eventMessage, zCVob* sourceVob) 
{
	// relevante Messages rausfiltern
	zCEventCommon *em = dynamic_cast<zCEventCommon*>(eventMessage);
	if (em) {
		switch (em->GetSubType()) {
			case zCEventCommon::zEVENT_RESET:
				Reset();
				break;
		};
	};
};

void zCCodeMaster::Archive (zCArchiver &arc) 
{
	zCTriggerBase::Archive	(arc);

	//
	arc.WriteGroupBegin		("CodeMaster");
	arc.WriteBool			("orderRelevant",		flags.orderRelevant);
	
	arc.WriteGroupBegin		("OrderRelevant");
	arc.WriteBool			("firstFalseIsFailure", flags.firstFalseIsFailure);
	arc.WriteString			("triggerTargetFailure", triggerTargetFailure);
	arc.WriteGroupEnd		("OrderRelevant");

	arc.WriteGroupBegin		("OrderNotRelevant");
	arc.WriteBool			("untriggerCancels",	flags.untriggerCancels);
	arc.WriteGroupEnd		("OrderNotRelevant");

	int num=MAX_SLAVES;
	if (!arc.InProperties()) {
		num--;
		for (; num>=0; num--) {
			if (!slaveVobNameList[num].IsEmpty()) break;
		};
		num++;
		arc.WriteByte		("numSlaves", num);
	};

	for (int i=0; i<num; i++) {
		arc.WriteString		(zSTRING("slaveVobName"+zSTRING(i)).ToChar(), slaveVobNameList[i]);
	};
	if (arc.InSaveGame()) {
		arc.WriteByte		("numSlavesTriggered", numSlavesTriggered);
		for (int i=0; i<num; i++) {
			arc.WriteObject	(("slaveTriggered"+zSTRING(i)).ToChar(), slaveTriggeredList[i]);
		};
	};
	arc.WriteGroupEnd		("CodeMaster");
};

void zCCodeMaster::Unarchive (zCArchiver &arc) 
{
	zCTriggerBase::Unarchive (arc);

	//
	Init();

	//
	flags.orderRelevant			= arc.ReadBool	("orderRelevant");
	flags.firstFalseIsFailure	= arc.ReadBool	("firstFalseIsFailure");
								  arc.ReadString("triggerTargetFailure", triggerTargetFailure);	triggerTargetFailure.Upper();
	flags.untriggerCancels		= arc.ReadBool	("untriggerCancels");

	int num=MAX_SLAVES;
	if (!arc.InProperties()) {
		num = arc.ReadByte			("numSlaves");
	};
	for (int i=0; i<num; i++) {
		arc.ReadString				(zSTRING("slaveVobName"+zSTRING(i)).ToChar(), slaveVobNameList[i]);
		slaveVobNameList[i].Upper	();
	};
	if (arc.InSaveGame()) {
		numSlavesTriggered		= arc.ReadByte		("numSlavesTriggered");
		for (int i=0; i<num; i++) {
			// AddRef()!
			slaveTriggeredList[i]	= static_cast<zCVob*>(arc.ReadObject	(("slaveTriggered"+zSTRING(i)).ToChar()));
		};
	};
};

const zSTRING*	zCCodeMaster::GetTriggerTarget	(const int i) const				
{ 
	switch (i) {
		case 0:  return &triggerTarget;
		case 1:  return &triggerTargetFailure;
	};
	return 0;
};

// ==================================================================================================================

zCMoverControler::zCMoverControler() {
	moverMessage		= zCEventMover::zEVENT_GOTO_KEY_FIXED_DIRECTLY;
	gotoFixedKeyframe	= 0;
};

void zCMoverControler::OnTrigger (zCVob* otherVob, zCVob *vobInstigator)
{
	zCEventMover *em		= zNEW(zCEventMover(moverMessage));
	em->gotoFixedKeyframe	= this->gotoFixedKeyframe;

	// Message verschicken
	// eine ganze Liste von TriggerTarget Vobs ermitteln !
	zCArray<zCVob*> targetVobList;
	GetHomeWorld()->SearchVobListByName (triggerTarget, targetVobList);
	for (int i=0; i<targetVobList.GetNum(); i++) {
		targetVobList[i]->GetEM()->OnMessage (em, this);
	};
};

void zCMoverControler::Archive (zCArchiver &arc)
{
	zCTriggerBase::Archive (arc);

	//
	if (arc.InProperties()) 
	{
		zCEventMover *em= zNEW(zCEventMover(moverMessage));				// nur um an den Enum-String zu kommen..
		zSTRING s;
		for (int i=0; i<em->MD_GetNumOfSubTypes(); i++) {
			if (i!=0) s += ";";
			s += em->MD_GetSubTypeString (i);
		};
		arc.WriteEnum	("moverMessage", s.ToChar(),	moverMessage);
	} else {
		arc.WriteEnum	("moverMessage", "",			moverMessage);
	};
	arc.WriteInt	("gotoFixedKey",	gotoFixedKeyframe);
};

void zCMoverControler::Unarchive (zCArchiver &arc) 
{
	zCTriggerBase::Unarchive (arc);

	//
	moverMessage	= zCEventMover::zTEventMoverSubType(arc.ReadEnum	("moverMessage"));
	arc.ReadInt		("gotoFixedKey",	gotoFixedKeyframe);
};

// ==================================================================================================================

zCTriggerWorldStart::zCTriggerWorldStart() {
	fireOnlyFirstTime	= FALSE;
	hasFired			= FALSE;
};

void zCTriggerWorldStart::PostLoad () 
{
	// Im Spacer nicht bei WeltStart feuern..
#ifndef COMPILING_SPACER
	if (fireOnlyFirstTime)
	{
		if (!hasFired) OnTrigger (this,this);
	}
	else
	{
		OnTrigger (this,this);
	}
#endif
};

void zCTriggerWorldStart::OnTrigger (zCVob* otherVob, zCVob *vobInstigator)
{
	zCTriggerBase::OnTrigger (otherVob, vobInstigator);
	hasFired = TRUE;
};

void zCTriggerWorldStart::Archive (zCArchiver &arc)
{
	zCTriggerBase::Archive (arc);
	
	arc.WriteBool		("fireOnlyFirstTime", fireOnlyFirstTime);
	if (arc.InSaveGame()) {
		arc.WriteBool	("hasFired"			, hasFired);
	};
};

void zCTriggerWorldStart::Unarchive (zCArchiver &arc) 
{
	zCTriggerBase::Unarchive (arc);

	fireOnlyFirstTime	= arc.ReadBool	("fireOnlyFirstTime");
	if (arc.InSaveGame()) {
		hasFired		= arc.ReadBool	("hasFired");
	};
};


// ==================================================================================================================
