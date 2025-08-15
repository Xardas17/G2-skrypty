/******************************************************************************** 
 
     $Workfile:: oNpc_Damage.h        $                $Date:: 10.02.01 20:45   $
     $Revision:: 12                   $             $Modtime:: 10.02.01 14:36   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oNpc_Damage.h $
 * 
 * 12    10.02.01 20:45 Moos
 * Monstermässige Magie-Leakfixes
 * 
 * 11    20.01.01 2:32 Edenfeld
 * 
 * 10    20.11.00 15:14 Keskenti
 * 
 * 9     7.11.00 21:07 Edenfeld
 * 
 * 8     2.11.00 21:04 Keskenti
 * 
 * 7     31.10.00 20:27 Keskenti
 * 
 * 6     30.10.00 14:19 Keskenti
 * 
 * 5     26.10.00 19:07 Keskenti
 * 
 * 4     26.10.00 17:54 Keskenti
 * 
 * 3     26.10.00 16:49 Edenfeld
 * 
 * 2     12.10.00 19:18 Keskenti
 * 
 * 1     12.10.00 14:04 Keskenti
 * 
 * 7     11.10.00 22:56 Keskenti
 * 
 * 6     11.10.00 19:53 Keskenti
 * 
 * 5     10.10.00 15:52 Keskenti
 * 
 * 4     9.10.00 20:00 Keskenti
 *
 *********************************************************************************/

#ifndef __ONPC_DAMAGE_H__
#define __ONPC_DAMAGE_H__

//	
//class oCNpc : public oCVob 
//{

	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
public:
	//
	//	DAMAGE DESCRIPTOR VALIDITY FLAGS
	//
	typedef
	enum	oEFlagsDamageDescriptor
	{
											// 0 makes no sens - cannot be tested 
		oEDamageDescFlag_Attacker			= 1										 ,
		oEDamageDescFlag_Npc				= oEDamageDescFlag_Attacker			<< 1 ,
		oEDamageDescFlag_Inflictor			= oEDamageDescFlag_Npc				<< 1 ,
		oEDamageDescFlag_Weapon				= oEDamageDescFlag_Inflictor		<< 1 ,
		oEDamageDescFlag_VisualFX			= oEDamageDescFlag_Weapon			<< 1 ,
		oEDamageDescFlag_SpellID			= oEDamageDescFlag_VisualFX			<< 1 ,
		oEDamageDescFlag_SpellLevel			= oEDamageDescFlag_SpellID			<< 1 ,
		oEDamageDescFlag_DamageType			= oEDamageDescFlag_SpellLevel		<< 1 ,
		oEDamageDescFlag_WeaponType			= oEDamageDescFlag_DamageType		<< 1 ,
		oEDamageDescFlag_Damage				= oEDamageDescFlag_WeaponType		<< 1 ,
		oEDamageDescFlag_HitLocation		= oEDamageDescFlag_Damage			<< 1 ,
		oEDamageDescFlag_FlyDirection		= oEDamageDescFlag_HitLocation		<< 1 ,
		oEDamageDescFlag_OverlayActivate	= oEDamageDescFlag_FlyDirection		<< 1 ,
		oEDamageDescFlag_OverlayInterval	= oEDamageDescFlag_OverlayActivate	<< 1 ,
		oEDamageDescFlag_OverlayDuration	= oEDamageDescFlag_OverlayInterval	<< 1 ,
		oEDamageDescFlag_OverlayDamage		= oEDamageDescFlag_OverlayDuration	<< 1 ,
		oEDamageDescFlag_ForceDWORD			= 0xffffffff				
	}	
	oEDescDamageFlags,
	oEFlagsDamageDesc;

	//
	//	DAMAGE DESCRIPTOR
	//
	typedef
	struct	oSDamageDescriptor
	{
		friend class oCNpc												;		// only On_Damage() - which resides in oCNpc - may access protected members
																		
		//																
		//	CONTROL														
		//																
	public:																
			zDWORD			 dwFieldsValid								;		// determines which fields are valid
																		
			//															
			//	SETTINGS												
			//															
			zCVob			*pVobAttacker								;
			oCNpc			*pNpcAttacker								;
			zCVob			*pVobHit									;
			oCVisualFX		*pFXHit;
			oCItem			*pItemWeapon								;
			zUINT32			 nSpellID									;
			zUINT32			 nSpellCat									;
			zUINT32			 nSpellLevel								;
			oTDamageMode	 enuModeDamage								;
			oTWeaponMode	 enuModeWeapon								;
			zUINT32			 aryDamage			[ oEDamageIndex_MAX ]	;
			zREAL			 fDamageTotal								;
			zREAL			 fDamageMultiplier							;
			zVEC3			 vecLocationHit								;
			zVEC3			 vecDirectionFly							;
			zSTRING			 strVisualFX								;
	//		zBOOL			 bStartDamageOverlay						;
			zREAL			 fTimeDuration								;
			zREAL			 fTimeInterval								;
			zREAL			 fDamagePerInterval							;
			zBOOL			 bDamageDontKill							;

		//
		//	COMPUTED VALUES -> DO NOT MODIFY EXTERNALLY
		//
	protected:
		struct //oSDamageDescriptorFlagsProtected
		{					 
			zUINT32			 bOnce				: 1						;		// 0
			zUINT32			 bFinished			: 1						;		// 1
			zUINT32			 bIsDead			: 1						;		// 2
			zUINT32			 bIsUnconscious		: 1						;		// 3
			zUINT32			 lReserved			: 28					;		// 31
		};																
			zREAL			 fAzimuth									;
			zREAL			 fElevation									;
			zREAL			 fTimeCurrent								;
			zREAL			 fDamageReal								;
			zREAL			 fDamageEffective							;
			zUINT32			 aryDamageEffective	[ oEDamageIndex_MAX ]	;
			zCVob			*pVobParticleFX								;
			zCParticleFX	*pParticleFX								; 
			oCVisualFX		*pVisualFX									; 

		//
		//	CONSTRUCTOR
		//
	public:
		oSDamageDescriptor()
		{
			::memset( this, 0, sizeof( *this ) );
			this->fDamageMultiplier = 1.0f;
		}

		~oSDamageDescriptor(){ Release(); }

		oSDamageDescriptor(const oSDamageDescriptor &o);
		oSDamageDescriptor &operator =(const oSDamageDescriptor &o);

        void SetVisualFX(oCVisualFX *fx);
        void SetFXHit   (oCVisualFX *fx);

		void Release();

	}
	oSDescDamage,
	DAMAGE_DESC	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************

public:
			void			InitDamage				( void );
	static	void			EnableDamageDebugOutput	( zBOOL			bEnable = TRUE	);

			zBOOL			EV_DamageOnce			( oCMsgDamage*	pMsg			);
			zBOOL			EV_DamagePerFrame		( oCMsgDamage*	pMsg			);

	virtual	void			OnDamage				( oSDamageDescriptor& descDamage );
			void			OnDamage_Anim			( oSDamageDescriptor& descDamage );
			void			OnDamage_Condition		( oSDamageDescriptor& descDamage );
			void			OnDamage_Effects		( oSDamageDescriptor& descDamage );
			void			OnDamage_Effects_End	( oSDamageDescriptor& descDamage );
			void			OnDamage_Effects_Start	( oSDamageDescriptor& descDamage );
			void			OnDamage_Events			( oSDamageDescriptor& descDamage );
			void			OnDamage_Hit			( oSDamageDescriptor& descDamage );
			void			OnDamage_Script			( oSDamageDescriptor& descDamage );
			void			OnDamage_State			( oSDamageDescriptor& descDamage );
			void			OnDamage_Sound			( oSDamageDescriptor& descDamage );

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	static	zBOOL			isEnabledDamageDebug;

private:
	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************

	static	void			NotifyDamageToSpy		( zSTRING& str );
	static	void			NotifyDamageToSpy		( zSTRING strMethod, zSTRING strPart, zSTRING strOutcome );
	static	void			NotifyDamageToSpy		( zSTRING strMethod, zSTRING strPart, zSTRING strOutcome, int nValue );
	static	void			NotifyDamageToSpy		( zSTRING strMethod, zSTRING strPart, zSTRING strOutcome, zSTRING strValue );

			zBOOL			HasFlag					( zDWORD dwValue, zDWORD dwFlag );
	//		int				GetDamageType			( oTModeDamage dwDamageType		);
	//		oTModeDamage	GetDamageType			( int		   nDamageType		);

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************

//};

#endif // __ONPC_DAMAGE_H__
