/******************************************************************************** 
 
     $Workfile:: oAniCtrl.h           $                $Date:: 29.01.01 22:35   $
     $Revision:: 39                   $             $Modtime:: 29.01.01 22:24   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oAniCtrl.h $
 * 
 * 39    29.01.01 22:35 Wohlers
 * 
 * 38    29.01.01 22:18 Wohlers
 * 
 * 37    26.01.01 16:21 Moos
 * 
 * 36    17.01.01 0:04 Hildebrandt
 * methods inlined, autoRoll activated for diving
 * 
 * 35    12.01.01 12:38 Moos
 * 
 * 34    10.01.01 15:31 Moos
 * 
 * 33    10.01.01 9:00 Moos
 * 
 * 32    8.01.01 14:55 Wohlers
 * 
 * 31    14.12.00 20:45 Wohlers
 * 
 * 30    17.11.00 16:52 Wohlers
 * 
 * 29    8.11.00 16:46 Wohlers
 * 
 * 28    26.10.00 15:48 Wohlers
 * 
 * 27    19.10.00 21:49 Wohlers
 * 
 * 26    11.10.00 22:56 Keskenti
 * 
 * 25    10.10.00 13:39 Wohlers
 * 
 * 24    21.09.00 17:15 Wohlers
 * 
 * 23    20.09.00 16:51 Wohlers
 * 
 * 22    6.09.00 14:48 Wohlers
 * 
 * 21    30.08.00 19:59 Wohlers
 * 
 * 20    24/08/00 17:06 Luesebrink
 * 
 * 19    17.08.00 16:56 Wohlers
 * 
 * 18    17.08.00 15:49 Wohlers
 * 
 * 17    15.08.00 18:07 Wohlers
 * 
 * 16    9.08.00 18:21 Keskenti
 * 
 * 15    9.08.00 18:11 Keskenti
 * 
 * 14    2/08/00 19:45 Luesebrink
 * 
 * 13    31.07.00 22:04 Wohlers
 * 
 * 12    19.07.00 20:54 Wohlers
 * 
 * 11    5.07.00 12:20 Wohlers
 * 
 * 9     9.06.00 18:18 Wohlers
 * 
 * 8     29.05.00 18:35 Wohlers
 * 
 * 7     25.05.00 14:50 Wohlers
 * Levelwechsel / Fernkampf
 * 
 * 6     24.05.00 20:28 Wohlers
 * Gothic 0.83
 * 
 * 5     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 5     8.05.00 23:07 Edenfeld
 * 
 * 4     8.05.00 19:31 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 11    18.04.00 20:14 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 10    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 9     16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 8     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 7     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 6     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 5     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 4     7.12.99 22:08 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ANICTRL_H__
#define __ANICTRL_H__

#include "zModel.h"
#include "zAIPlayer.h"
#include "zArchiver.h"

class oCNpc;
class oCItem;


enum {	ANI_WALKMODE_RUN		,ANI_WALKMODE_WALK	,ANI_WALKMODE_SNEAK	,
		ANI_WALKMODE_WATER		,ANI_WALKMODE_SWIM	,ANI_WALKMODE_DIVE	};

enum {  ANI_ACTION_STAND		,ANI_ACTION_WALK	,ANI_ACTION_SNEAK	,ANI_ACTION_RUN,
		ANI_ACTION_WATERWALK	,ANI_ACTION_SWIM	,ANI_ACTION_DIVE	,ANI_ACTION_CHOOSEWEAPON
	 };

enum { ANI_HITTYPE_NONE			,ANI_HITTYPE_FORWARD };



const int		WMODE_NONE				= 1;
const int		WMODE_CHOOSE			= 2;
const int		WMODE_STAND				= 3;

const int		ANI_NUM					= 10;
const int		ANI_HITLIMB_MAX			= 4;
const int		ANI_TURN_LAYER			= 20;

const int		ANI_MAX_HIT				= 10;
const zREAL		ANI_TIME_INFINITE		= -1000000.0f;	

// extern
extern zBOOL	ANI_ENABLE_TURN;

extern const zSTRING	ANI_EYEBLINK;

class oCAniCtrl_Human : public zCAIPlayer {
	zCLASS_DECLARATION	(oCAniCtrl_Human)

public:
	
	oCAniCtrl_Human							();
	
	// Inits
	virtual void	Init					(oCNpc *npc);
	void			InitAllAnis				();
	void			InitFightAnis			(int fm);
	void			InitAnimations			();
	// void			SetModel				(zCModel *m);
	void			SetAnis					(int fm);
	void			SetFightAnis			(int fm);
	void			SetInterruptFollowAni	(zTModelAniID ani);
	void			SetScaleModel			(zREAL x, zREAL y, zREAL z);
	void			Reset					();
	void			SearchStandAni			(zBOOL forceStartAni = FALSE);
	void			StartStandAni			();
	void			SetScriptValues			();

	void			SetWalkMode				(int fm);
	int				GetWalkMode				() const {			// [HILDEBRANDT] inlined!
													return walkmode;
												};
	void			SetActionMode			(int am);
	int				GetActionMode			() const {			// [HILDEBRANDT] inlined!
													return actionMode;	
												};

	// Kampfsystem - Anis
	static zSTRING	GetWeaponString			(int wm);
	static zSTRING	GetWeaponHitString		(int wm);

	void			StartHitCombo			(zTModelAniID aniID, zCVob* target = NULL);
	void			SetComboHitTarget		(const zCVob *a_pTarget);
	zBOOL			HitCombo				(zBOOL enableNextCombo = FALSE);

	void			StartHitGraphical		(zTModelAniID aniID, zCVob* stopTurnVob = NULL);
	zBOOL			HitGraphical			();

	zCVob*			CheckHitTarget			();
	zBOOL			CheckMeleeWeaponHitsLevel(oCItem *a_pWeapon);

	void			CreateHit				(zCVob* target);
	zSTRING			GetHitDirection			();

	void			HitInterrupt			();

	zBOOL			IsInPreHit				();
	zBOOL			IsInPostHit				();
	zBOOL			IsInCombo				();

	void			CorrectFightPosition	();
	zBOOL			CanParade				(oCNpc* enemy);
	void			StartParadeEffects		(oCNpc* enemy);
	zCModelAniActive* IsParadeRunning		();

	void			GetFightLimbs			();
	zBOOL			CheckLimbHit			(const zSTRING &nname, zCList<zCModelNodeInst> &hitModelNodeList);
	
	void			StartAniWithOffset		(zTModelAniID ani, zREAL offset);
	void			DoAniWithOffset			();

	void			ShowWeaponTrail			();
	zBOOL			IsDefending				();

	// Waffe ziehen / wegstecken
	zBOOL			DrawWeapon1				(int last = -1, zBOOL ignoreFistCondition = FALSE, zBOOL showMagicCircle = TRUE);
	zBOOL			DrawWeapon2				();
	zBOOL			ChooseNextWeapon2		(int dir);
	zBOOL			RemoveWeapon1			();
	zBOOL			RemoveWeapon2			();

	// Movement
	void			TurnDegrees				(zREAL degrees, zBOOL playAni=TRUE);
	zREAL			Turn					(zREAL dir, zBOOL playani=TRUE);
	void			DoAutoRoll				();
	void			StopTurnAnis			();
	void			SetAlwaysWalk			(zBOOL pressed);
	zBOOL			IsAlwaysWalk			();
	zBOOL			CanToggleWalkModeTo		(int wm);
	zBOOL			CanToggleWalkMode		();
	void			ToggleWalkMode			(zTModelAniID nextAni = zMDL_ANI_ID_ILLEGAL);
	zSTRING			GetWalkModeString		();
	void			CorrectAniStates		();
	//void			SetDoOops				(zBOOL on); [Moos] Oopsen wurde abgeschafft

	void			PC_GoForward			();
	void			PC_GoBackward			();
	void			PC_JumpForward			();

	void			_Stand					();
	void			_Forward				();
	void			_Backward				();


	// Zustaende
	int				GetFootPos				();
	void			StrafeLeft				();
	void			StrafeRight				();
	int				JumpForward				();
	zBOOL			IsWalking				();
	zBOOL			IsRunning				();
	zBOOL			IsWalkingBackward		();
	zBOOL			IsAiming				();
	zBOOL			IsStanding				();
	zBOOL			IsJumpStanding			();
	zBOOL			IsDead					();
	zBOOL			IsFallen				();

	// Magic Anis	
	void			SetAnimations			(int spellEnergy, const zSTRING& scut);
	zBOOL			TransitionToInvest		();
	zBOOL			TransitionToCast		();
	zBOOL			TransitionToStand		();
	zBOOL			IsInCastAni				();
	zBOOL			IsInWeaponChoose		();

	// Schwimmen
	int				CanJumpLedge			();
	void			Swim_ClimbLedge			();
	zBOOL			Swim_CanClimbLedge		();
	int				GetWaterLevel			();
	zBOOL			IsInWater				();
	zBOOL			CheckWaterLevel			();
	virtual void	StartFallDownAni		();
	zBOOL			CanJump					(int level = 0);
	zBOOL			CanWalkOnPoly			(const zVEC3& polyNormal);
	void			HackNPCToSwim			();


//	int				GetState				() { return state; };  [Moos] Diese Funktionen hat jetzt schon die AIPlaer
//	void			SetState				(int st);
//	int				GetOldState				();

	// Kopfbewegungen
	zREAL			CombineAniLerp			(const zREAL curx, const zREAL targetx, const zREAL time, const zREAL maxTime);
	zBOOL			InterpolateCombineAni	(const zREAL targetx, const zREAL targety, const zTModelAniID lookAni);
	void			SetLookAtTarget			(zREAL targetx, zREAL targety);
	void			SetLookAtTarget			(zVEC3& pos);
	void			SetLookAtTarget			(zCVob* target);
	void			LookAtTarget			();
	void			StopLookAtTarget		();
	
	// Combine Anis
	void			StartCombineAni			(zVEC3& pos, zTModelAniID ani, const zREAL angleHeight, const zREAL angleWidth);
	void			StartCombineAni			(zCVob* target, zTModelAniID ani, const zREAL angleHeight, const zREAL angleWidth);
	void			StopCombineAni			(zTModelAniID ani);

	// Helpers
	zTModelAniID		CheckLayerAni			(int layer, const zSTRING &s);
	zCModelAniActive*	GetLayerAni				(int layer);
	zBOOL				IsStateAniActive		(zTModelAniID aniID);
	zBOOL				IsStateAniActive		(zCModelAni* ani);
	zBOOL				WallInFront				(zREAL dist = 100.0f);
	zBOOL				DetectChasm				(const zVEC3 &pos, const zVEC3 &dir, zREAL &floorDist, zVEC3 &cdNormal);
	zBOOL				IsInCriticalAni			();
	void				SetNextAni				(zTModelAniID ani	, zTModelAniID nextAni);
	zBOOL				StartAni				(zTModelAniID aniID	, zTModelAniID nextAniID = zMDL_ANI_ID_ILLEGAL);
	void				FirstPersonDrawWeapon	();

	// TEMP
	void				InitAngleValuesForConsole();

	// TEMP : für SpeziesConsole : Werte zum Umrechnen von Bogenmass nach Winkel
	zREAL			angle_slide1;
	zREAL			angle_slide2;
	zREAL			angle_heading;
	zREAL			angle_horiz;
	zREAL			angle_ground;

protected :	

	virtual			~oCAniCtrl_Human		();

	// Every Frame
	void			StartUp					(zCVob *invob);
    void            LerpFeetToTarget        (zTModelAniID ani_now, zTModelAniID ani_final, const zVEC3 &targetPos);
    void            RelaxHandToTarget       (const zVEC3 &targetPos, const zVEC3 &wishAt, zBOOL changeSpeed=TRUE, zREAL relax = 1.0f);
	void			CheckSpecialStates		();					// Jump / Fall
	void			CheckFallStates			();
	void			CheckJump				();

	// Kampfsystem 
	void			DoSparks				(zVEC3 &pos, const zSTRING& strPFX );	
	int				GetStopTurnVobSign		();

	// Archiver
	void			Archive					(zCArchiver &arc);
	void			Unarchive				(zCArchiver &arc);	
	
public:	
	
	oCNpc*				npc;
	zCVob*				targetVob;			
	zCVob*				stopTurnVob;
	int					stopTurnVobSign;
	
	zCModelNodeInst*	hitlimb[ANI_HITLIMB_MAX];		// FightLimbs

	int					actionMode;
	
	// Waffen toggeln
	int					wmode;
	int					wmode_last;
	int					wmode_selected;
	zBOOL				changeweapon;	

	// Walkmode
	int					walkmode;
	int					nextwalkmode;		
	int					lastRunWalkSneak;
	zBOOL				always_walk;
	zBOOL				do_jump;
	int					defaultSurfaceAlign;
	zREAL				autoRollDirection;

	// Kopfbewegungen
	zREAL				lookTargetx, lookTargety;

	// Fight
	int					distance;
	zVEC3				hitpos;
	zSTRING				limbname;
	zREAL				paradeBeginFrame, paradeEndFrame;

	struct {
		zUINT8			canEnableNextCombo				: 1;
		zUINT8			endCombo						: 1;
		zUINT8			comboCanHit						: 1;
		zUINT8			hitPosUsed						: 1;
		zUINT8			hitGraphical					: 1;
		zUINT8			canDoCollisionFX				: 1;
	};	
	
	int					comboNr;
	int					comboMax;
	zREAL				lastHitAniFrame;
	zTModelAniID		hitAniID;
	zCVob*				hitTarget;

	typedef struct {
		zTModelAniID	hitAni;								
		int				hitOptFrame;
		int				hitEndFrame;
		int				comboStartFrame;
		int				comboEndFrame;
		int				comboDir;
	} oTComboInfo;
	
	oTComboInfo			comboInfo[ANI_MAX_HIT];

	// Kampfsystem - Tuning
	zREAL				anioffset_lastper;
	zREAL				anioffset_thisper;
	zREAL				anioffset;
	zTModelAniID		anioffset_ani;

	// *****************************************************************************************

	// Normal
	zTModelAniID		s_dead1, s_dead2;
	zTModelAniID		s_hang,  t_hang_2_stand;

	// Run Mode
	zTModelAniID		s_run				[ANI_NUM],t_run_2_runl		[ANI_NUM],	t_runl_2_run	[ANI_NUM],
						s_runl				[ANI_NUM],t_runl_2_runr		[ANI_NUM],	t_runr_2_runl	[ANI_NUM],
						s_runr				[ANI_NUM],t_runr_2_run		[ANI_NUM],
						t_runturnl			[ANI_NUM],t_runturnr		[ANI_NUM],
						t_runstrafel		[ANI_NUM],t_runstrafer		[ANI_NUM];
	
	// runbackward - Loop
	zTModelAniID		t_run_2_runbl		[ANI_NUM],t_runbl_2_run		[ANI_NUM],
						s_runbl				[ANI_NUM],t_runbl_2_runbr	[ANI_NUM],	t_runbr_2_runbl	[ANI_NUM],
						s_runbr				[ANI_NUM],t_runbr_2_run		[ANI_NUM];


	zTModelAniID		t_jumpb				[ANI_NUM];

	// 
	// Walk / Sneak Mode
	// 

	// Transitions
	zTModelAniID		t_run_2_walk		[ANI_NUM],t_walk_2_run		[ANI_NUM],
						t_run_2_sneak		[ANI_NUM],t_sneak_2_run		[ANI_NUM];

	zTModelAniID		s_walk				[ANI_NUM],t_walk_2_walkl	[ANI_NUM],	t_walkl_2_walk	[ANI_NUM],
						s_walkl				[ANI_NUM],t_walkl_2_walkr	[ANI_NUM],	t_walkr_2_walkl	[ANI_NUM],
						s_walkr				[ANI_NUM],t_walkr_2_walk	[ANI_NUM],
						t_walkturnl			[ANI_NUM],t_walkturnr		[ANI_NUM],
						t_walkstrafel		[ANI_NUM],t_walkstrafer		[ANI_NUM];

	// Walkbackward - Loop
	zTModelAniID		t_walk_2_walkbl		[ANI_NUM],t_walkbl_2_walk	[ANI_NUM],
						s_walkbl			[ANI_NUM],t_walkbl_2_walkbr	[ANI_NUM],	t_walkbr_2_walkbl[ANI_NUM],
						s_walkbr			[ANI_NUM],t_walkbr_2_walk	[ANI_NUM];

	// Jump aus dem Lauf
	zTModelAniID		t_runl_2_jump		[ANI_NUM],t_runr_2_jump		[ANI_NUM],
						t_jump_2_runl		[ANI_NUM];

	// JumpLow / Mid
	zTModelAniID		t_stand_2_jumpuplow, s_jumpuplow, t_jumpuplow_2_stand,
						t_stand_2_jumpupmid, s_jumpupmid, t_jumpupmid_2_stand;

	zTModelAniID		s_sneak				[ANI_NUM],	t_sneak_2_sneakl	[ANI_NUM],	t_sneakl_2_sneak	[ANI_NUM],
						s_sneakl			[ANI_NUM],	t_sneakl_2_sneakr	[ANI_NUM],	t_sneakr_2_sneakl	[ANI_NUM],
						s_sneakr			[ANI_NUM],	t_sneakr_2_sneak	[ANI_NUM],
						t_sneakturnl		[ANI_NUM],	t_sneakturnr		[ANI_NUM],
						t_sneakstrafel		[ANI_NUM],	t_sneakstrafer		[ANI_NUM];

	// sneakbackward - Loop
	zTModelAniID		t_sneak_2_sneakbl	[ANI_NUM],	t_sneakbl_2_sneak	[ANI_NUM],
						s_sneakbl			[ANI_NUM],	t_sneakbl_2_sneakbr	[ANI_NUM],	t_sneakbr_2_sneakbl	[ANI_NUM],
						s_sneakbr			[ANI_NUM],	t_sneakbr_2_sneak	[ANI_NUM];

	// Kampf
	zTModelAniID		t_walkl_2_aim		[ANI_NUM],	t_walkr_2_aim		[ANI_NUM],
						t_walk_2_aim		[ANI_NUM],	s_aim				[ANI_NUM],	t_aim_2_walk	[ANI_NUM],
						t_hitl				[ANI_NUM],	t_hitr				[ANI_NUM],	t_hitback		[ANI_NUM],
						t_hitf				[ANI_NUM],	s_hitf				[ANI_NUM],
						t_aim_2_defend		[ANI_NUM],	s_defend			[ANI_NUM],	t_defend_2_aim	[ANI_NUM],
						t_paradeL			[ANI_NUM],	t_paradeM			[ANI_NUM],	t_paradeS		[ANI_NUM],
						t_hitfrun			[ANI_NUM];

	// Interrupt Anis
	zTModelAniID		t_stumble,	t_stumbleb,	t_fallen_2_stand, t_fallenb_2_stand;

	// Water Walk
	zTModelAniID		t_walk_2_walkwl		,t_walkwl_2_walk		,
						s_walkwl			,t_walkwl_2_walkwr		,	t_walkwr_2_walkwl,
						s_walkwr			,t_walkwr_2_walk;

	// Walkbackward - Loop
	zTModelAniID		t_walk_2_walkwbl	,t_walkwbl_2_walk		,
						s_walkwbl			,t_walkwbl_2_walkwbr	,	t_walkwbr_2_walkwbl,
						s_walkwbr			,t_walkwbr_2_walk;

	zTModelAniID		_s_walk				,_t_walk_2_walkl		,	_t_walkl_2_walk,
						_s_walkl			,_t_walkl_2_walkr		,	_t_walkr_2_walkl,
						_s_walkr			,_t_walkr_2_walk		,
						_t_turnl			,_t_turnr				,
						_t_strafel			,_t_strafer;		

	// Walkbackward - Loop
	zTModelAniID		_t_walk_2_walkbl	,_t_walkbl_2_walk		,
						_s_walkbl			,_t_walkbl_2_walkbr		,	_t_walkbr_2_walkbl,
						_s_walkbr			,_t_walkbr_2_walk;					
					
	// Jumpstand
	zTModelAniID		s_jumpstand			,t_stand_2_jumpstand,	t_jumpstand_2_stand,
						_t_jumpb			,
						_t_stand_2_jump		,_s_jump			,	t_jump_2_stand,
						_t_stand_2_jumpup	,_s_jumpup;
	
	// Anderer Jumpkram
	zTModelAniID		_t_jumpup_2_falldn	,_t_jump_2_falldn;

	// Schwimmen / Tauchen
	zTModelAniID		t_walkwl_2_swimf	,s_swimf			,t_swimf_2_walkwl,
						t_walkwbl_2_swimb	,s_swimb			,t_swimb_2_walkwbl,
						t_swimf_2_swim		,s_swim				,t_swim_2_swimf,
						t_swim_2_swimb		,t_swimb_2_swim		,t_warn,
						t_swim_2_dive		,s_dive				,t_divef_2_swim,
						t_dive_2_divef		,s_divef			,t_divef_2_dive,
						t_dive_2_drowned	,s_drowned			,
						t_swimturnl			,t_swimturnr		,
						t_diveturnl			,t_diveturnr;				

	// Kampf
	zTModelAniID		_t_walkl_2_aim		,_t_walkr_2_aim		,
						_t_walk_2_aim		,_s_aim				,_t_aim_2_walk,
						_t_hitl				,_t_hitr			,_t_hitback,
						_t_hitf				,_t_hitfstep		,_s_hitf,
						_t_aim_2_defend		,_s_defend			,_t_defend_2_aim,
						_t_paradeL			,_t_paradeM			,_t_paradeS,
						_t_hitfrun;
					
	// Item aim 
	zTModelAniID		t_stand_2_iaim		,s_iaim				,t_iaim_2_stand;
	// Item drop
	zTModelAniID		t_iaim_2_idrop		,s_idrop			,t_idrop_2_stand;
	// Item throw
	zTModelAniID		t_iaim_2_ithrow		,s_ithrow			,t_ithrow_2_stand;
	// Item take
	zTModelAniID		t_stand_2_iget		,s_iget				,t_iget_2_stand;
	zTModelAniID		s_oget;

	// Fackel Specials
	zTModelAniID		_t_stand_2_torch	,_s_torch			,_t_torch_2_stand;

	// aktueller Schlag
	zTModelAniID		hitani;

	// Hilfsanis
	zTModelAniID		help,help1,help2;
	zTModelAniID		s_fall			,s_fallb			, s_fallen			,s_fallenb,		s_falldn;
	zTModelAniID		_t_runl_2_jump	,_t_runr_2_jump		,_t_jump_2_runl;
	zTModelAniID		s_look,s_point;
	zTModelAniID		dummy1,dummy2,dummy3,dummy4;
	zTModelAniID		s_weapon[ANI_NUM];
	zTModelAniID		togglewalk;

	// Magic Anis
	zTModelAniID		t_stand_2_cast;
	zTModelAniID		s_cast;	
	zTModelAniID		t_cast_2_shoot;
	zTModelAniID		t_cast_2_stand;
	zTModelAniID		s_shoot;
	zTModelAniID		t_shoot_2_stand;
	
	int					dummyLastVar;
};

#endif
