/******************************************************************************** 
 
     $Workfile:: oAIHuman.h        $                $Date:: 5.02.01 20:19    $
     $Revision:: 28                   $             $Modtime:: 5.02.01 18:40    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oAIHuman.h $
 * 
 * 28    5.02.01 20:19 Wohlers
 * 
 * 27    22.01.01 13:09 Moos
 * 
 * 26    12.01.01 12:38 Moos
 * 
 * 25    10.01.01 17:47 Hildebrandt
 * removed ReportCollisionToAI()
 * 
 * 24    20.12.00 18:23 Moos
 * 
 * 23    20.12.00 17:13 Moos
 * 
 * 22    11.12.00 18:45 Hildebrandt
 * 
 * 21    26.10.00 16:49 Edenfeld
 * 
 * 20    21/10/00 13:01 Luesebrink
 * 
 * 19    13.10.00 15:35 Wohlers
 * 
 * 18    6.10.00 12:30 Wohlers
 * 
 * 17    4.10.00 16:36 Wohlers
 * 
 * 16    27/09/00 19:50 Luesebrink
 * 
 * 15    23.09.00 17:51 Edenfeld
 * 
 * 14    23.09.00 2:58 Edenfeld
 * 
 * 13    21.09.00 19:35 Edenfeld
 * 
 * 12    12.09.00 22:00 Edenfeld
 * 
 * 11    2.09.00 2:22 Wohlers
 * 
 * 10    1/09/00 13:08 Luesebrink
 * 
 * 9     26/07/00 18:12 Luesebrink
 * 
 * 8     25/07/00 13:50 Luesebrink
 * 
 * 7     5.07.00 12:20 Wohlers
 * 
 * 5     5.06.00 22:34 Wohlers
 * uSrc 05.06.00
 * 
 * 4     22.05.00 18:41 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:07 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 8     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 7     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 6     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 5     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZAIHUMAN_H__
#define __ZAIHUMAN_H__

#include <z3D.h>
#include <zAI.h>
#include <zCollisionDetector.h>

#include "oAniCtrl.h"
#include "oSpell.h"
#include "oMusicZone.h"

#include "oRoutine.h"
#include "zList.h"

class oCNpc;
class oCMobInter;
class oCAI_NpcManager;
class zCAICamera;
class oCMsgAttack;

class oCAICamera : public zCAIBase {
	zCLASS_DECLARATION	(oCAICamera)
public:

	oCAICamera ();
	
	void	DoAI					(zCVob* inVob, zBOOL& vobDeleted);
	zBOOL	HasAIDetectedCollision	() { return FALSE; };
	// [HILDEBRANDT] removed ReportCollisionToAI()
private:
	zCTimer	localTimer;				// [HILDEBRANDT]
};

// *********************************************************************************

class oCAIHuman : public oCAniCtrl_Human {

	zCLASS_DECLARATION	(oCAIHuman)

public :

	// Init
	oCAIHuman									();

	virtual void		Init					(oCNpc* npc);
	void				SetShowAI				(zBOOL f);
	zBOOL				GetShowAI				();

	// Camera 
	void				InitCamModes			(int val = -1);	
	void				SetCamMode				(const zSTRING& activateCamMode, zBOOL checkSpecial = FALSE);
	void				SetCamModeMob			(oCMobInter* mob);
	void				ChangeCamMode			(const zSTRING& activateCamMode);		

	oHEROSTATUS			GetEnemyThreat			();

	// Per Frame	
	virtual void		DoAI					(zCVob* inVob, zBOOL& vobDeleted);

	// Movement
	void				SetCrawlMode			(zBOOL on);
	void				SetSprintMode			(zBOOL on);
	zBOOL				DoSimpleAI				();
	void				PC_Turnings				( zBOOL forceRotation = FALSE );
	zBOOL				IsSprintActive			( void ){ return sprintActive; }
	zBOOL				IsReleased				() const{ return spellReleased;};

	// Interaction
	zBOOL				CheckMobInteraction		();
	zBOOL				CheckItemInteraction	();

	// Collision
	virtual zBOOL		CanThisCollideWith		(zCVob *v);	
	virtual void		AddIgnoreCD				(zCVob *v);
	virtual void		SubIgnoreCD				(zCVob *v);
	virtual void		DoHackSpecials			();
	// [HILDEBRANDT] removed ReportCollisionToAI()

	void				StartFlyDamage			(zREAL damage, zVEC3& flyDir);

	// Magic
	zBOOL				MagicInvestSpell		();
	zBOOL				MagicCheckSpellStates	(zBOOL action);

	// Temp
	// zTInterferenceReport ir; [Moos] Durch GetInterferenceReport() zu ersetzen

protected :
	virtual				~oCAIHuman				();

	//changed [dennis]
	// Focus
	void				CheckFocusVob			(const zBOOL a_bForce = FALSE);
	// Camera
	zBOOL				MoveCamera				();								// LookAround
	void				CheckFightCamera		();
	void				CamMessages				();

	// Keys 
	zBOOL				Pressed					(int key);
	zBOOL				Toggled					(int key);

	// Per Frame
	void				Moving					();
	void				DoMonsterSpecial		();

	// Movement
	zBOOL				StandActions			();

	// Fight
	void				WeaponChoose			();
	zBOOL				FightMelee				();
	zBOOL				BowMode					(zBOOL pressed);

	// Magic
	zBOOL				MagicMode				();
	zBOOL				CheckActiveSpells		();

	// Sound
	void				CreateFootStepSound			(zBOOL first = FALSE);
	void				ResetObserveSuspectCounter	();
	void				CreateObserveSuspect		(zBOOL first = FALSE);
	void				ResetAssessUseMobCounter	();
	void				CreateAssessUseMob			();

	// PC-Actions 
	void				PC_Turn					(zREAL dir, zBOOL playAnis = TRUE);
	zBOOL				PC_ActionMove			(zBOOL pressed);
	zBOOL				PC_WeaponMove			(zBOOL pressed);
	zBOOL				PC_SlowMove				(zBOOL pressed);
	zBOOL				PC_SpecialMove			(zBOOL pressed);
	zBOOL				PC_Sneak				(zBOOL pressed);
	zBOOL				PC_Strafe				(zBOOL pressed);
	zBOOL				PC_CheckSpecialStates	();
	void				PC_Diving				();
	void				_WalkCycle				();
	
	// Archive
	void				Archive					(zCArchiver &arc);
	void				Unarchive				(zCArchiver &arc);
	void				ChangeCamModeBySituation();
	
	// Vars	
	zCList<zCVob>		ignoreVobList;
	zCAICamera*			aiCam;
	
	zBOOL				forcejump               :1;
	zBOOL				lookedAround            :1;
	zBOOL				sprintActive            :1;
	zBOOL				crawlActive             :1;
	zBOOL				showai                  :1;
	zBOOL				startObserveIntruder    :1;
	zBOOL				dontKnowAniPlayed       :1;
	zBOOL				spellReleased           :1;
	zBOOL				spellCastedLastFrame    :1;
	zBOOL				eyeBlinkActivated       :1;
	zBOOL				thirdPersonFallback		:1;

	zREAL				createFlyDamage;

	// statics 	

	// activation of Cameramodes
	static zSTRING		Cam_Normal;
	static zSTRING		Cam_Run;
	static zSTRING		Cam_Fight;

//	static int			sleepRange;
	static zCList<oCNpc>npcInRangeList;
};

// ********************************************
// Bert Special Spacer NSC -.AI
// ********************************************

class oCAIHuman_Stand : public zCAIBase {
	zCLASS_DECLARATION	(oCAIHuman_Stand)

public:
	oCAIHuman_Stand					() {}; 

	oCAIHuman_Stand					(zCVob *v);
	~oCAIHuman_Stand				();

	void	DoAI					(zCVob* inVob, zBOOL& vobDeleted);
	
};

#endif