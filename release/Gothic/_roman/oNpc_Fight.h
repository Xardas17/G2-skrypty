/******************************************************************************** 
 
     $Workfile:: oNpc_Fight.h         $                $Date:: 8.02.01 18:11    $
     $Revision:: 12                   $             $Modtime:: 8.02.01 17:43    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oNpc_Fight.h $
 * 
 * 12    8.02.01 18:11 Wohlers
 * 
 * 11    29.01.01 17:42 Keskenti
 * 
 * 10    14.12.00 20:46 Wohlers
 * 
 * 9     17.11.00 16:53 Wohlers
 * 
 * 8     10.11.00 17:34 Keskenti
 * 
 * 7     1.11.00 18:19 Wohlers
 * 
 * 6     1.11.00 16:13 Wohlers
 * 
 * 5     31.10.00 20:27 Keskenti
 * 
 * 4     26.10.00 17:54 Keskenti
 * 
 * 3     20.10.00 20:54 Wohlers
 * 
 * 2     12.10.00 19:18 Keskenti
 * 
 * 1     12.10.00 16:50 Keskenti
 * 
 * 1     12.10.00 16:20 Keskenti
 * 
 *********************************************************************************/

#ifndef __ONPC_FIGHT_H__
#define __ONPC_FIGHT_H__

//	
//class oCNpc : public oCVob 
//{

public:
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
	enum oEBloodMode
	{
		oEBloodMode_None			,
		oEBloodMode_Particles		,
		oEBloodMode_Decals			,
		oEBloodMode_Trails			,
		oEBloodMode_Amplification	
	};

	enum { FA_MAX_SITUATIONS	= 19	};
	enum { FA_MAX_ENTRY			= 6		};

	static zSTRING	FightAIInstances[ FA_MAX_SITUATIONS ];

	typedef
	enum oEFightAction {

		NPC_FIGHTMOVE_NOTINITIALISED	=	 0,		// Not set by Script
		NPC_FIGHTMOVE_RUN				=	 1,
		NPC_FIGHTMOVE_RUNBACK			=	 2,
		NPC_FIGHTMOVE_JUMPBACK			=	 3,
		NPC_FIGHTMOVE_TURN				=	 4,
		NPC_FIGHTMOVE_STRAFE			=	 5,
		NPC_FIGHTMOVE_ATTACK			=	 6,
		NPC_FIGHTMOVE_SIDEATTACK		=	 7,
		NPC_FIGHTMOVE_FRONTATTACK		=	 8,
		NPC_FIGHTMOVE_TRIPLEATTACK		=	 9,
		NPC_FIGHTMOVE_WHIRLATTACK		=	10,
		NPC_FIGHTMOVE_MASTERATTACK		=	11,
		NPC_FIGHTMOVE_PREHIT			=	12,
		NPC_FIGHTMOVE_COMBOZONE			=	13,
		NPC_FIGHTMOVE_POSTHIT			=	14,
		NPC_FIGHTMOVE_TURNTOHIT			=	15,
		NPC_FIGHTMOVE_STORMPREHIT		=	16,
		NPC_FIGHTMOVE_PARADE			=	17,
		NPC_FIGHTMOVE_STANDUP			=	18,
		NPC_FIGHTMOVE_WAIT				=	19,
		NPC_FIGHTMOVE_ONGROUND			=	20,
		NPC_FIGHTMOVE_STUMBLE			=	21,
		NPC_FIGHTMOVE_SKIP				=	22,
		NPC_FIGHTMOVE_WAIT_LONG			=	23,
		NPC_FIGHTMOVE_WAIT_EXT			=	24,

		NPC_FIGHTMOVE_MAX				
	}
	TFAction;

	typedef
	struct oSActionBlock 
	{
		// FOE FWD
		int ownaction	[FA_MAX_ENTRY];
		int max;

		void		InitBlock		(zCParser* par, int sitNr, int faiNr);
		int			GetOwnAction	(int quality);
	}
	TActionBlock;

	// **************************************************
	// Instanzen der C_FightAI
	// **************************************************
	typedef
	struct oSFightAI 
	{
		TActionBlock myactions[FA_MAX_SITUATIONS];
		
		void		Init			(zCParser* par, int aiNumber);
		int			GetOwnAction	(int situationNr);
		
	}
	TFightAI;

	typedef oCNpc::oSFightAI TFightAI;


	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
	static void			SetBloodMode			( oEBloodMode enuMode )						{ oCNpc::modeBlood = enuMode; }
	static oEBloodMode	GetBloodMode			( void )									{ return oCNpc::modeBlood	; }

	//
	//	IS/HAS
	//
	int				IsBloodEnabled				( void )									{ return this->bloodEnabled	; }
	int				IsBloodFlowEnabled			( void )									{ return this->bloodFlow	; }
	zBOOL			IsConditionValid			( void )									;	
	zBOOL			IsDead						( void )									;	
	zBOOL			IsInFightFocus				( zCVob* target )							;
	zBOOL			IsInFightRange				( zCVob* vob, zREAL &dist )					;
	zBOOL			IsInDoubleFightRange		( zCVob* vob, zREAL &dist )					;
	zBOOL			IsMunitionAvailable			( oCItem* weapon )							;
	zBOOL			IsSameHeight				( zCVob* other )							;
	zBOOL			IsUnconscious				( void )									;	
	zBOOL			IsNpcBetweenMeAndTarget		( zCVob* target )							;
	zBOOL			HasArrowInHand				( void )									;	
	zBOOL			HasArrowInInv				( void )									;	
	zBOOL			HasBoltInHand				( void )									;	
	zBOOL			HasBoltInInv				( void )									;	
	zBOOL			HasMunitionInHand			( oCItem* weapon )							;
	zBOOL			HasRangedWeaponAndAmmo		( void )									;
	zBOOL			ShieldEquipped				( void )									;
	zBOOL			CanDrawWeapon				( void )									;

	//
	//	GET
	//
	int				GetBloodAmount				( void )									{ return this->bloodAmount	; }
	int				GetBloodDistance			( void )									{ return this->bloodDistance; }
	zSTRING			GetBloodEmitter				( void )									{ return this->bloodEmitter	; }
	zSTRING			GetBloodTexture				( void )									{ return this->bloodTexture	; }
	int				GetBluntDamage				( oCItem* weapon )							;
	zREAL			GetDamageMultiplier			( void )									;
	oTModeDamage 	GetDamageMode				( void )									{ return this->damagetype	; }
	oCNpc*			GetEnemy					( void )									{ return this->enemy		; }
	oCItem*			GetEquippedArmor			( void )									;	
	oCItem*			GetEquippedMeleeWeapon		( void )									;	
	oCItem*			GetEquippedRangedWeapon		( void )									;	
	int				GetFightRange				( void )									;
	int				GetFightRangeBase			( void )									;
	int				GetFightRangeFist			( void )									;
	int				GetFightRangeG				( void )									;
	int				GetFightRangeDynamic		( void )									;
	oCNpc*			GetNearestFightNpcLeft		( void )									;	
	oCNpc*			GetNearestFightNpcRight		( void )									;	
	oCNpc*			GetNextEnemy				( void )									;	
	int				GetNextWeaponMode			( int from, int dir, zBOOL useFist = FALSE );
	int				GetShieldValue				( void )									;
	oCItem*			GetWeapon					( void )									;	
	int				GetWeaponDamage				( oCItem* weapon )							;
	int				GetWeaponDamage				( void )									;	
	int				GetWeaponMode				( void )									;
		
	//
	//	ENABLE
	//
	void			EnableBlood					( int enabled	  )							{ this->bloodEnabled	= enabled			?			1		 : 0		; } 	
	void			EnableBloodFlow				( int flow		  )							{ this->bloodFlow		= flow				?			1		 : 0		; }

	//
	//	SET
	//
	void			SetBloodDistance			( int distance	  )							{ this->bloodDistance	= (!distance)		?		 1000		 : distance	; }	
	void			SetBloodAmount				( int amount	  )							{ this->bloodAmount		= (!amount)			?		   10		 : amount	; }
	void			SetBloodEmitter				( zSTRING emitter )							{ this->bloodEmitter	= emitter.IsEmpty() ? "PFX_BLOOD"		 : emitter	; }
	void			SetBloodTexture				( zSTRING texture )							{ this->bloodTexture	= texture.IsEmpty() ? "ZBLOODSPLAT2.TGA" : texture	; }
	void			SetDamageMultiplier			( zREAL dm )								;								
	void			SetDamageMode				( oTModeDamage enuModeDamage )				{ this->damagetype		= enuModeDamage; }
	void			SetEnemy					( oCNpc* npc )								;
	void			SetFightRangeBase			( int n )									;
	void			SetFightRangeFist			( int n )									;
	void			SetFightRangeG				( int n )									;
	void			SetToFightMode				( oCItem *item, zBOOL startStandAni = TRUE );
	void			SetToFistMode				( void )									;
	virtual void	SetWeaponMode				( int fm )									;
	virtual void	SetWeaponMode2				( int fm )									;
	void			SetWeaponMode2				( const zSTRING& mode )						;

	//
	//	EXTERNALS
	//
	oCItem*			AI_CheckWeapon				( int talent )								;
	oCItem*			AI_ChooseWeapon				( void )									;
	void			AI_FightAction				( void )									;

	//
	//	EQUIP
	//
	void			EquipArmor					( oCItem *item )							;
	void			EquipFarWeapon				( oCItem *item )							;
	void			EquipWeapon					( oCItem *item )							;

	//
	//	DO
	//
	virtual void	DoDie						( oCNpc* attacker = NULL )					;
	virtual	oCItem*	DoInsertMunition			( const zSTRING& slotName )					;
	virtual void	DoRemoveMunition			( void )									;	
	virtual zBOOL	DoSetToFightMode			( oCItem *item)								;
	virtual zBOOL	DoShootArrow				( zBOOL autoaim = FALSE )					;

	//
	//	ACTIONS
	//
	void			DropUnconscious				( zREAL azi, oCNpc* attacker = NULL )		;
	void			CheckUnconscious			( void )									;
	void			Fighting					( void )									;	
	void			TurnToEnemy					( void )									;	

	zBOOL			InitAim						( oCMsgAttack* csg, oCNpc** pEnemy, zBOOL *pDrawn, zBOOL *pAmmo, zBOOL bKillFormerMsg );
	zBOOL			InterpolateAim				( oCNpc* pEnemy );
	zBOOL			FinalizeAim					( zBOOL bStartMelee = FALSE, zBOOL bStandUp = FALSE );
	zBOOL			TransitionAim				( zTModelAniID idCurrentAni, zTModelAniID idTargetAni );

	//
	//	EVENTS
	//
	virtual	void	OnDamage					( zCVob* otherVob, zCVob* inflictorVob, zREAL damage, int damageType, const zVEC3& hitLocation );

	zBOOL			EV_ChooseWeapon				( oCMsgWeapon* csg );
	
	zBOOL			EV_DrawWeapon				( oCMsgWeapon* csg );
	zBOOL			EV_DrawWeapon1				( oCMsgWeapon* csg );
	zBOOL			EV_DrawWeapon2				( oCMsgWeapon* csg );

	zBOOL			EV_RemoveWeapon				( oCMsgWeapon* csg );
	zBOOL			EV_RemoveWeapon1			( oCMsgWeapon* csg );
	zBOOL			EV_RemoveWeapon2			( oCMsgWeapon* csg );
	zBOOL			EV_ForceRemoveWeapon		( oCMsgWeapon* csg );

	zBOOL			EV_EquipArmor				( oCMsgWeapon* csg );
	zBOOL			EV_EquipBestWeapon			( oCMsgWeapon* csg );
	zBOOL			EV_EquipBestArmor			( oCMsgWeapon* csg );
	zBOOL			EV_UnequipWeapons			( oCMsgWeapon* csg );
	zBOOL			EV_UnequipArmor				( oCMsgWeapon* csg );

	zBOOL			EV_AttackBow				( oCMsgAttack* csg );
	zBOOL			EV_AttackMagic				( oCMsgAttack* csg );
	zBOOL			EV_AttackRun				( oCMsgAttack* csg );
	zBOOL			EV_AttackLeft				( oCMsgAttack* csg );
	zBOOL			EV_AttackRight				( oCMsgAttack* csg );
	zBOOL			EV_AttackFinish				( oCMsgAttack* csg );
	zBOOL			EV_AttackForward			( oCMsgAttack* csg );

	zBOOL			EV_Defend					( oCMsgAttack* csg );
	zBOOL			EV_Parade					( oCMsgAttack* csg );

	zBOOL			EV_AimAt					( oCMsgAttack* csg );
	zBOOL			EV_StopAim					( oCMsgAttack* csg );
	zBOOL			EV_ShootAt					( oCMsgAttack* csg );

	//
	//	CODECHANGE [ROMAN] END
	//

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************

private:
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
	void			CheckRunningFightAnis		( void )			;
	int				GetCurrentFightMove			( void )			;
	int				GetFightActionFromTable		( int situationNr )	;
	zBOOL			FightAttackMelee			( int myMove )		;
	zBOOL			FightAttackBow				( void )			;	
	zBOOL			FightAttackMagic			( void )			;
	int				FindNextFightAction			( void )			;
	int				ThinkNextFightAction		( void )			;
	void			GotoFightPosition			( void )			;

	static void		InitFightAI					( void )			;
	static void		ExitFightAI					( void )			; // Moos

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
	static	oEBloodMode	modeBlood	;

	int 			bloodEnabled	;	
	int 			bloodDistance	;	
	int				bloodAmount		;	
	int 			bloodFlow		;	
	zSTRING			bloodEmitter	;	
	zSTRING			bloodTexture	;	

	zBOOL			didHit			;
	zBOOL			didParade		;
	zBOOL			didShoot		;
	zBOOL			hasLockedEnemy	;
	zBOOL			isDefending		;
	zBOOL			wasAiming		;
	TFAction		lastAction		;

	oCNpc*			enemy			;
//}
//

#endif // __ONPC_FIGHT_H__
