/******************************************************************************** 
 
     $Workfile:: oNpc_Damage.cpp      $                $Date:: 14.02.01 21:34   $
     $Revision:: 81                   $             $Modtime:: 14.02.01 21:06   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oNpc_Damage.cpp $
 * 
 * 81    14.02.01 21:34 Speckels
 * 
 * 80    14.02.01 16:24 Wohlers
 * 
 * 79    12.02.01 18:29 Wohlers
 * 
 * 78    10.02.01 20:45 Moos
 * Monstermässige Magie-Leakfixes
 * 
 * 77    9.02.01 22:39 Edenfeld
 * VisualFX Memleaks work in progress
 * 
 * 76    9.02.01 19:02 Keskenti
 * 
 * 75    5.02.01 17:47 Keskenti
 * 
 * 74    5.02.01 17:23 Keskenti
 * 
 * 73    2.02.01 23:40 Edenfeld
 * 
 * 71    31.01.01 20:01 Moos
 * 
 * 70    31.01.01 4:57 Keskenti
 * 
 * 69    29.01.01 17:42 Keskenti
 * 
 * 68    29.01.01 16:17 Keskenti
 * 
 * 67    29.01.01 13:57 Keskenti
 * 
 * 66    29.01.01 13:47 Keskenti
 * 
 * 65    26.01.01 21:54 Wohlers
 * 
 * 64    26.01.01 19:03 Edenfeld
 * 
 * 63    26.01.01 18:25 Edenfeld
 * 
 * 62    25.01.01 18:29 Keskenti
 * 
 * 61    24.01.01 15:40 Keskenti
 * 
 * 60    24.01.01 13:16 Keskenti
 * 
 * 59    23.01.01 12:37 Keskenti
 * 
 * 58    22.01.01 17:19 Keskenti
 * 
 * 57    20.01.01 2:32 Edenfeld
 * 
 * 56    19.01.01 16:13 Keskenti
 * 
 * 55    18.01.01 16:53 Keskenti
 * 
 * 54    12.01.01 21:26 Keskenti
 * 
 * 53    12.01.01 19:23 Keskenti
 * 
 * 52    12.01.01 10:36 Keskenti
 * 
 * 51    9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 50    8.01.01 16:54 Keskenti
 * 
 * 49    8.01.01 16:55 Edenfeld
 * 
 * 48    18.12.00 15:51 Edenfeld
 * 
 * 47    14.12.00 18:08 Keskenti
 * 
 * 46    14.12.00 17:37 Keskenti
 * 
 * 45    14.12.00 15:52 Keskenti
 * 
 * 44    14.12.00 14:19 Pankratz
 * 
 * 43    14.12.00 14:05 Keskenti
 * 
 * 42    14.12.00 13:36 Keskenti
 * 
 * 41    14.12.00 13:03 Keskenti
 * 
 * 40    14.12.00 13:02 Keskenti
 * 
 * 39    13.12.00 16:18 Keskenti
 * 
 * 38    12.12.00 13:31 Keskenti
 * 
 * 37    11.12.00 19:14 Keskenti
 * 
 * 36    5.12.00 21:57 Speckels
 * 
 * 35    29.11.00 12:52 Speckels
 * 
 * 34    28.11.00 18:34 Keskenti
 * 
 * 33    22.11.00 18:00 Keskenti
 * 
 * 32    22.11.00 17:35 Keskenti
 * 
 * 31    22.11.00 16:56 Edenfeld
 * 
 * 30    22.11.00 14:19 Keskenti
 * 
 * 29    20.11.00 15:14 Keskenti
 * 
 * 28    17.11.00 22:01 Edenfeld
 * 
 * 27    16.11.00 19:09 Keskenti
 * 
 * 26    10.11.00 17:34 Keskenti
 * 
 * 25    9.11.00 16:55 Edenfeld
 * 
 * 24    9.11.00 14:14 Keskenti
 * 
 * 23    8.11.00 19:14 Keskenti
 * 
 * 22    8.11.00 15:32 Edenfeld
 * 
 * 21    8.11.00 13:29 Wohlers
 * 
 * 20    7.11.00 21:07 Edenfeld
 * 
 * 19    3.11.00 17:58 Keskenti
 * 
 * 18    2.11.00 21:51 Edenfeld
 * 
 * 17    2.11.00 21:04 Keskenti
 * 
 * 16    2/11/00 16:54 Luesebrink
 * 
 * 15    2.11.00 16:42 Edenfeld
 * 
 * 14    2.11.00 15:24 Keskenti
 * 
 * 13    1.11.00 19:12 Moos
 * 
 * 12    1.11.00 17:58 Moos
 * 
 * 11    31.10.00 20:27 Keskenti
 * 
 * 10    30.10.00 19:22 Edenfeld
 * 
 * 9     30.10.00 14:19 Keskenti
 * 
 * 8     26.10.00 19:07 Keskenti
 * 
 * 7     26.10.00 18:32 Speckels
 * 
 * 6     26.10.00 18:20 Keskenti
 * 
 * 5     26.10.00 17:54 Keskenti
 * 
 * 4     26.10.00 16:49 Edenfeld
 * 
 * 3     25.10.00 0:09 Edenfeld
 * 
 * 2     12.10.00 19:18 Keskenti
 * 
 * 1     12.10.00 14:04 Keskenti
 * 
 * 6     12.10.00 13:53 Keskenti
 * 
 * 5     11.10.00 22:15 Keskenti
 * 
 * 4     11.10.00 19:53 Keskenti
 * 
 * 3     10.10.00 19:08 Keskenti
 * 
 * 2     10.10.00 15:52 Keskenti
 *
 *********************************************************************************/

#include <zCore.h>

#include <zParser.h>
#include <zview.h>
#include <z3D.h>
#include <zVob.h>
#include <zFile3D.h>
#include <zOption.h>
#include <zRenderer.h>
#include <zAlgebra.h>
#include <zModel.h>
#include <zMorphMesh.h>
#include <zParticle.h>
#include <zSound.h>
#include <zPhysics.h>
#include <zSoundMan.h>
#include <zMusic.h>
#include <zBuffer.h>
#include <zArchiver.h>
#include <zAICamera.h>
#include <zCCSPlayer.h>
#include <zInput_Win32.h>
#include <zEventMan.h>
#include <zWayNet.h>

#include <oNpc.h>
#include <oNpcMessages.h>
#include <oVisFX.h>
#include <oAIHuman.h>
#include <oAniCtrl.h>
#include <oMagic.h>
#include <zAccount.h>

const int NPC_BURN_TICKS_PER_DAMAGE_POINT		= 1000;
const int NPC_BURN_DAMAGE_POINTS_PER_INTERVALL	= 10;
const int NPC_VOICE_VARIATION_MAX				= 5;

const int BLOOD_AMOUNT_DEFAULT					= 500;

/*--------------------------------------------------------------------------

    oSDamageDescriptor::~oSDamageDescriptor()	

    19-Jan-01       [Edenfeld]

					  Initial implementation

--------------------------------------------------------------------------*/ 
void oCNpc::oSDamageDescriptor::Release()
{
	zRELEASE(this->pVisualFX);
	zRELEASE(this->pFXHit);
	//zRELEASE(pVobParticleFX);
	//zRELEASE(pParticleFX); 
};

void oCNpc::oSDamageDescriptor::SetVisualFX(oCVisualFX *p){
    if (p == pVisualFX) return;
    
    zRELEASE_ACCT(pVisualFX);
    pVisualFX = p;
    if (p) zADDREF_ACCT(p);
}

void oCNpc::oSDamageDescriptor::SetFXHit   (oCVisualFX *p){
    if (p == pFXHit) return;
    
    zRELEASE_ACCT(pFXHit);
    pFXHit = p;
    if (p) zADDREF_ACCT(p);
}

oCNpc::oSDamageDescriptor::oSDamageDescriptor(const oSDamageDescriptor &o){
    pFXHit = pVisualFX = NULL;

    operator =(o);
}

oCNpc::oSDamageDescriptor &oCNpc::oSDamageDescriptor::operator =(const oSDamageDescriptor &o){
    zERR_ASSERT(&o);

    Release();
    
    ::memcpy( this, &o, sizeof( *this ) );

    // vorsicht ist bei folgenden Daten angebracht:
    memset(&strVisualFX, 0, sizeof (strVisualFX));
    strVisualFX = o.strVisualFX;

    if (pFXHit   ) zADDREF_ACCT(pFXHit   );
    if (pVisualFX) zADDREF_ACCT(pVisualFX);

    return *this;
}


/*--------------------------------------------------------------------------

    oCNpc::EnableDamageDebugOutput()	[static]

    20-Nov-00       [Roman Keskenti]

					  Initial implementation

--------------------------------------------------------------------------*/ 
void oCNpc :: EnableDamageDebugOutput ( zBOOL bEnable )
{
	oCNpc :: isEnabledDamageDebug = bEnable;
}

zBOOL oCNpc :: isEnabledDamageDebug = FALSE;

#define oNOTIFY_SPY_DAMAGE(pszMethod,pszPart,pszOutcome,pszValue)	{				\
	if ( oCNpc::isEnabledDamageDebug )						{						\
		zSTRING strMethod	= zSTRING( pszMethod  );								\
		zSTRING strPart		= zSTRING( pszPart	  );								\
		zSTRING strOutcome	= zSTRING( pszOutcome );								\
		zSTRING strValue	= zSTRING( pszValue   );								\
																					\
		strMethod	.Align( zSTR_LEFT, 30 );										\
		strPart		.Align( zSTR_LEFT, 30 );										\
		strOutcome	.Align( zSTR_LEFT, 40 );										\
		strValue	.Align( zSTR_LEFT, 40 );										\
																					\
		oCNpc::NotifyDamageToSpy( strMethod		+ " -> "							\
								+ strPart		+ " -> "							\
								+ strOutcome	+ ": "								\
								+ strValue				);	}		}				\

/*--------------------------------------------------------------------------

    oCNpc::NotifyDamageToSpy()			[static]

    20-Nov-00       [Roman Keskenti]

					  Initial implementation

--------------------------------------------------------------------------*/ 
void oCNpc::NotifyDamageToSpy( zSTRING& str )	
{ 
	//
	//	OUTPUT DEBUG MESSAGE
	//
	zERR_MESSAGE( 6, 0, "R: DAM: " + str ); 
}

/*--------------------------------------------------------------------------

    oCNpc::InitDamage ()

    20-Nov-00       [Roman Keskenti]

					  Initial implementation

--------------------------------------------------------------------------*/ 
void oCNpc :: InitDamage ( void )
{
	bloodEnabled				= 0						;
	bloodDistance				= 1000					;
	bloodAmount					= BLOOD_AMOUNT_DEFAULT	;
	bloodFlow					= 0						;
	bloodEmitter				= "PFX_BLOOD"			;
	bloodTexture				= "ZBLOODSPLAT2.TGA"	;
								
	speedTurn					= NPC_TURNVELOCITY * 0.001f;
								
	hasLockedEnemy				= FALSE;
	didShoot					= FALSE;
	didHit						= FALSE;
	wasAiming					= FALSE;
								
	waypointFlee				= NULL;
	foundFleePoint				= FALSE;
	reachedFleePoint			= FALSE;
								
	isDefending					= FALSE;
	didParade					= FALSE;

	damagetype					= oEDamageType_Blunt;
	::memset( damage, 0, sizeof( damage ) );
}

/*--------------------------------------------------------------------------

    oCNpc::EV_DamageOnce()

    10-Oct-00       [Roman Keskenti]

					  Initial implementation

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_DamageOnce ( oCMsgDamage* pMsg )
{
	oNOTIFY_SPY_DAMAGE( "EV_DamageOnce()", "", "", "" );

	this->OnDamage( pMsg->descDamage );

	return TRUE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_DamageOnce()

    10-Oct-00       [Roman Keskenti]

					  Initial implementation

	25-Oct-00		[Edenfeld]
					  Umstellung für oCVisualFX Implementation

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_DamagePerFrame ( oCMsgDamage* pMsg )
{
	oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "", "", "" );

	//
	//	FIRST RUN
	//
	if ( ! pMsg->IsInUse() )
	{
		pMsg->descDamage.fTimeCurrent	 = pMsg->descDamage.fTimeInterval		;
		pMsg->descDamage.fDamageTotal	 = pMsg->descDamage.fDamagePerInterval	; 
		pMsg->descDamage.dwFieldsValid	|= oEDamageDescFlag_OverlayActivate		;

		pMsg->SetInUse( TRUE );

		oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "First Run", "", "" );
		oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "First Run", "Current Time", pMsg->descDamage.fTimeCurrent  );
		oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "First Run", "Total Damage", pMsg->descDamage.fDamageTotal  );
		oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "First Run", "Valid Fields", pMsg->descDamage.dwFieldsValid );
	}

	//
	//	CONTINUOUS DAMAGE
	//
	oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "Subsequent Run", "", "" );
	oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "Subsequent Run", "Current Time", pMsg->descDamage.fTimeCurrent );
	oNOTIFY_SPY_DAMAGE( "EV_DamagePerFrame()", "Subsequent Run", "Total Damage", pMsg->descDamage.fDamageTotal );

	zBOOL bFinished	 = FALSE; 
	zREAL fTimeFrame = ::ztimer.GetFrameTimeF();

	pMsg->descDamage.fTimeCurrent  -= fTimeFrame;
	pMsg->descDamage.fTimeDuration -= fTimeFrame;

	if ( pMsg->descDamage.fTimeCurrent <= 0.0f )
	{
		this->OnDamage( pMsg->descDamage );

		pMsg->descDamage.fTimeCurrent	= pMsg->descDamage.fTimeInterval;
		bFinished						= pMsg->descDamage.bFinished	;
	}

	return bFinished;
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage()

    09-Oct-00       [Roman Keskenti]

					  Initial implementation

	25-Oct-00		[Edenfeld]
					  Umstellung für oCVisualFX Implementation


--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage ( oSDamageDescriptor& descDamage )
{
	oNOTIFY_SPY_DAMAGE( "OnDamage()", "Descriptor Version", "", "" );

	//
	//	EVALUATE FLAGS
	//

	descDamage.bOnce	  = ! this->HasFlag( descDamage.dwFieldsValid, oEDamageDescFlag_OverlayActivate );
	descDamage.bFinished  = ! descDamage.bOnce;
	descDamage.bFinished &=	 (descDamage.fTimeDuration <= 0.0f) || (descDamage.pVisualFX && descDamage.pVisualFX->IsFinished());

	//
	//	CHECK CONDITION
	//
	if ( this->IsConditionValid()	) 
	{

#if defined(SECUROM) && !defined(COMPILING_SPACER)
		if (descDamage.pNpcAttacker && descDamage.pNpcAttacker->IsSelfPlayer() &&
			((this->variousFlags & NPC_FLAG_PROTECTED) == NPC_FLAG_PROTECTED))
		{
			this->variousFlags |= NPC_FLAG_IMMORTAL;
			
			// Call 'PLAYER_VICTIM_IS_IMMORTAL'
			#define _(x) ((unsigned char)(((unsigned char)(x)) ^ 90))
			{
				char FunctionName[32] =
				{
					_('P'), _('L'), _('A'), _('Y'), _('E'), _('R'), _('_'),
					_('V'), _('I'), _('C'), _('T'), _('I'), _('M'), _('_'),
					_('I'), _('S'), _('_'),
					_('I'), _('M'), _('M'), _('O'), _('R'), _('T'), _('A'), _('L'),
					_('\0')
				};
				int i;
				for (i = 0; i < 32; i++)
					FunctionName[i] = (char)_(FunctionName[i]);
				CallScript(zSTRING(FunctionName));
				for (i = 0; i < 32; i++)
					FunctionName[i] = (char)_(FunctionName[i]);
			}
			#undef _
		}
#endif
		
		
		//
		//	PROCESS VARIOUS ASPECTS ...	
		//
		
		//
		// [BENDLIN] HACK: NO DAMAGE IF SOMEONE IS PROCESSING INFOS (DIALOG)
		// (The SelfPlayer and NPC are invulnerable while processing infos!)
		//
		if (IsSelfPlayer() || (descDamage.pNpcAttacker && descDamage.pNpcAttacker->IsSelfPlayer()))
		{
			int nr = GetEM()->GetNumMessages();
			for (int i = nr - 1; i >= 0; i--)
			{
				oCMsgConversation* msg = dynamic_cast<oCMsgConversation*>(GetEM()->GetEventMessage(i));
				if (msg)
				{
					switch (msg->GetSubType())
					{
					case oCMsgConversation::EV_PROCESSINFOS:
					case oCMsgConversation::EV_STOPPROCESSINFOS:
//					case oCMsgConversation::EV_ASK:
//					case oCMsgConversation::EV_WAITFORQUESTION:
						{
							//
							// DROP THE DAMAGE MESSAGE
							//
							descDamage.bFinished = TRUE;
							return;
						}
					}
				}
			}
		}

		// else
		{
										this->OnDamage_Hit			( descDamage );
										this->OnDamage_Condition	( descDamage );
			
			if ( descDamage.bOnce )	{	this->OnDamage_Anim			( descDamage );
										// [Wohlers] - 11.02.01 - Erst die Anims (clearen evtl. den EM, dann die Skriptreaktion darauf...)
										//                        Roman : bitte mal gegenchecken, ob Seiteneffekte gibt...	!!!!
										this->OnDamage_Effects_Start( descDamage );
										this->OnDamage_Script		( descDamage );
										this->OnDamage_State		( descDamage ); }
										
										this->OnDamage_Events		( descDamage );	
			
			if ( descDamage.bOnce )	{	this->OnDamage_Sound		( descDamage );	}
		}
	}

	if ( descDamage.bFinished )	this->OnDamage_Effects_End	( descDamage );
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Hit()

    09-Oct-00       [Roman Keskenti]

						Initial implementation
						Calculates the actual damage	

    31-Oct-00       [Roman Keskenti]

						Applies strength & dexterity modifiers
						Applies protection

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Hit ( oSDamageDescriptor& descDamage )
{

	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "", "", "" );
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "", "", zSTRING( "Victim : " ) + this->GetName() );

	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Init", "HP ", this->GetAttribute( NPC_ATR_HITPOINTS ) );
	//
	//	APPLY CRITICAL DAMAGE CHANCE
	//

	zBOOL bHasHit		= TRUE;
	zBOOL bUseRanged	= descDamage.pVisualFX ? TRUE : FALSE;

	if ( descDamage.pNpcAttacker )
	{
		bUseRanged |= ( descDamage.pNpcAttacker->GetWeaponMode() >  NPC_WEAPON_2HS  );

		if ( ! descDamage.pNpcAttacker->IsMonster() && !bUseRanged)
		{
			//
			//	GET CHANCE INDEX FROM WEAPON MODE
			//
			oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "getting Hitchance", "Attacker is an NPC", "" );

			//
			// [BENDLIN] Addon - FIXME: Drachen machen immer nur Mindestschaden,
			// da sie bekanntermassen nicht im WEAPON_1HS oder WEAPON_2HS sind!
			//

			int		hitChanceNr = -1;
			bool	chanceValid = true;

			if		( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_1HS	) hitChanceNr = NPC_HITCHANCE_1H;
			else if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_2HS	) hitChanceNr = NPC_HITCHANCE_2H;
			else if ((descDamage.pNpcAttacker->GetTrueGuild()  == NPC_GIL_DRAGON)		||
					 (descDamage.pNpcAttacker->GetTrueGuild()  == NPC_GIL_FIREGOLEM)	||
					 (descDamage.pNpcAttacker->GetTrueGuild()  == NPC_GIL_ICEGOLEM)		)
			{
				hitChanceNr = 100;
				chanceValid = false;
			}
			
			if ( hitChanceNr != -1 )
			{
				//
				//	"ROLL DICE"
				//					
				int nChance	= chanceValid ? descDamage.pNpcAttacker->GetHitChance(hitChanceNr) : 100;

				int nPercentage = ::zRand( 100 ) + 1 ;	// [1..100]

				oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Damagechance", zSTRING( "Rolling dice" ) + " ( "+nChance+" % )", "" );

				if ( nPercentage <= nChance )
				{
					oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Damagechance success", "Hit !!!", "" );
				}
				else bHasHit = FALSE;
			}
			else
			{
				bHasHit = FALSE;
				oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Damagechance", "First weapon- or invalid weapon Mode!", "" );
			}

		}
	}

	//
	//	APPLY MULTIPLIER ( .MSD AND CRITICAL DAMAGE )	
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Multiplier", "", "" );

	if ( descDamage.fDamageMultiplier != 1.0f )
	{
		//
		//	... ON SEPERATED DAMAGES
		//
		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Multiplier", "Applying to Serepate Damages", "" );
		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Multiplier", "Multiplier", descDamage.fDamageMultiplier );

		for ( int nIndex = 0; nIndex < oEDamageIndex_MAX; nIndex++ )
		{
			descDamage.aryDamage[ nIndex ] = zUINT32(descDamage.aryDamage[ nIndex ] * descDamage.fDamageMultiplier);
			oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Multiplier", zSTRING( "Damage[ " ) + nIndex + " ] ", descDamage.aryDamage[ nIndex ] );
		}

		//
		//	... ON TOTAL DAMAGE
		//
		descDamage.fDamageTotal *= descDamage.fDamageMultiplier;

		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Multiplier", "Applying to Total Damages", "" );
		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Multiplier", "Total Damage", descDamage.fDamageMultiplier );
	}

	//
	//	CHECK IF DAMAGES PER TYPE ARE NOT GIVEN AND THERE IS A TOTAL DAMAGE GIVEN
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Split", "Checking Seperate Damage", "" );

	zBOOL bDivideTotalDamage;

	int nDamageTotal = 0;
	for ( int nIndex = 0; nIndex < oEDamageIndex_MAX; nIndex++ )
	{
		if ( this->HasFlag( descDamage.enuModeDamage, ( 1 << nIndex ) ) )
		{
			nDamageTotal += descDamage.aryDamage[ nIndex ];
		}
	}

	bDivideTotalDamage = ( nDamageTotal == 0 );

	//
	//	SPLIT TOTAL DAMAGE UP FOR MONSTERS
	//
	zBOOL bIsSemiHuman =	descDamage.pNpcAttacker	&&
						(	descDamage.pNpcAttacker->IsHuman	() 
						||	descDamage.pNpcAttacker->IsOrc		() 
						||	descDamage.pNpcAttacker->IsGoblin	() 
						||	descDamage.pNpcAttacker->IsSkeleton	() );

	if ( bDivideTotalDamage )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Split", "No Seperate Damage", "" );

		if ( descDamage.pNpcAttacker )
		if ( ! bIsSemiHuman )
		{
			oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Split", "Attacker is a Monster", "" );

			if ( descDamage.pFXHit )
			{
				oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Split", "Monster is casting a spell", "" );
			}
			else if (descDamage.fDamageTotal==0)
			{
				oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Split", "Using Monster's Strength", "" );
				descDamage.fDamageTotal = float(descDamage.pNpcAttacker->GetAttribute( NPC_ATR_STRENGTH ));
			}
		}

		int nDamageTotal = (int) descDamage.fDamageTotal;
		::ApplyDamages( descDamage.enuModeDamage, (int*) descDamage.aryDamage, nDamageTotal );
		descDamage.fDamageTotal = (zREAL) nDamageTotal;

		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Split", "Splitting Damage Per Type", "" );
		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Split", "Total Damage", descDamage.fDamageTotal );
	}

	//
	//	APPLY DAMAGE BONI FROM MAGIC ITEMS FOR NON-MONSTERS
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Damage Boni", "", "" );

	if ( descDamage.pNpcAttacker )
	if ( bIsSemiHuman )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Damage Boni", "Attacker is an NPC", "" );

		for ( int nIndex = 0; nIndex < oEDamageIndex_MAX; nIndex++ )
		{
			descDamage.aryDamage[ nIndex ] += descDamage.pNpcAttacker->GetDamageByIndex( (oEDamageIndex) nIndex );

			oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Damage Boni", zSTRING( "Damage[ " ) + nIndex + " ] ", descDamage.aryDamage[ nIndex ] );
		}
	}

	//
	//	APPLY STRENGTH & DEXTERITY BONI TO PRIMARY DAMAGE MODE FOR NON-MONSTERS
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Attribute Boni", "", "" );

	if ( descDamage.pNpcAttacker )
	{
		if ( descDamage.pFXHit )
		{
			oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Attribute Boni", "Attacker is a spell-caster", "No attribute boni added" );
		}
		else
		if ( bIsSemiHuman )
		{
			oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Attribute Boni", "Attacker is at least semi-human (fights with weapon)", "" );

			//
			//	EVALUATE PRIMARY DAMAGE MODEs
			//
			zBOOL bBlunt		= ( ( descDamage.enuModeDamage & oEDamageType_Blunt	) == oEDamageType_Blunt	);
			zBOOL bEdge			= ( ( descDamage.enuModeDamage & oEDamageType_Edge	) == oEDamageType_Edge	);
			zBOOL bPoint		= ( ( descDamage.enuModeDamage & oEDamageType_Point	) == oEDamageType_Point	);
			
			//
			//	IF THE ATTACKER IS A MONSTER AND DOES NOT CAUSE PRIMARY DAMAGE -> ASSUME EDGE DAMAGE (EDGE is DEADLY)
			//
			if ( ! ( bBlunt || bEdge || bPoint ) )
			if ( descDamage.pNpcAttacker->IsMonster() )
			{
				oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Attribute Boni", "Assuming Edge Damage (No primary damage contained) !", "" );

				descDamage.enuModeDamage   |= oEDamageType_Edge	;
				bEdge						= TRUE				;
			}

			//
			//	SPLIT UP DAMAGE MODIFYING SKILLS 
			//
			zREAL fDivisor		= 0.0f;
			zREAL fStrength		= float(descDamage.pNpcAttacker->GetAttribute( NPC_ATR_STRENGTH  ));
			zREAL fDexterity	= float(descDamage.pNpcAttacker->GetAttribute( NPC_ATR_DEXTERITY ));

			if ( bBlunt ) fDivisor += 1.0f;
			if ( bEdge	) fDivisor += 1.0f;
			if ( bPoint	) fDivisor += 1.0f;

			if ( fDivisor != 0.0f )
			{
				fStrength  /= fDivisor;
				fDexterity /= fDivisor;

				if ( bBlunt ) { descDamage.aryDamage[ oEDamageIndex_Blunt ] += zUINT32(fStrength)	;	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Attribute Boni", "Blunt Damage", descDamage.aryDamage[ oEDamageIndex_Blunt ] ); }
				if ( bEdge  ) { descDamage.aryDamage[ oEDamageIndex_Edge  ] += zUINT32(fStrength)	;	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Attribute Boni", "Edge  Damage", descDamage.aryDamage[ oEDamageIndex_Edge  ] ); }
				if ( bPoint ) { descDamage.aryDamage[ oEDamageIndex_Point ] += zUINT32(fDexterity)	;	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Attribute Boni", "Point Damage", descDamage.aryDamage[ oEDamageIndex_Point ] ); }
			}
		}
	}

	//
	//	APPLY PROTECTION
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Protection", "", "" );

	int nDamageEffective		= 0;
	int nDamageApplied			= 0;
	int nDamageCurrent			= 0;
	int nProtectionTotal		= 0;
	int nProtectionCurrent		= 0;
	zBOOL immortalByProtection		= FALSE;
	zBOOL canBeImmortalByProtection = TRUE;

	for ( int nDamageIndex = 0; nDamageIndex < oEDamageIndex_MAX; nDamageIndex++ )
	{
		//
		//	ONLY APPLY THOSE DAMAGES AND PROTECTIONS THAT ARE ACTIVE
		//
		if ( ( descDamage.enuModeDamage & ( 1 << nDamageIndex ) ) == ( 1 << nDamageIndex ) )
		{
			nDamageCurrent											= descDamage.aryDamage			[ nDamageIndex ]					;
			nProtectionCurrent										= this->GetProtectionByIndex	( (oEDamageIndex) nDamageIndex )	;
			if (nProtectionCurrent > 0)	canBeImmortalByProtection	= FALSE;
			
			if (canBeImmortalByProtection && nProtectionCurrent < 0)	
			{	
				immortalByProtection = TRUE;
			}
				
			nDamageTotal											+= nDamageCurrent													;
			nProtectionTotal										+= nProtectionCurrent												;
			nDamageApplied											= ( nDamageCurrent - nProtectionCurrent )							;	if ( nDamageApplied < 0 ) nDamageApplied = 0;
			nDamageEffective										+= nDamageApplied													;
			descDamage.aryDamageEffective[ nDamageIndex ]			= nDamageApplied													;
		}
		else
			descDamage.aryDamageEffective[ nDamageIndex ]	 = 0																;

		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Protection", zSTRING( "EffectiveDamage[ " ) + nDamageIndex + " ] ", descDamage.aryDamageEffective[ nDamageIndex ] );
	}

	/*if ( nDamageEffective > 0 )*/	descDamage.fDamageTotal = (zREAL) nDamageEffective;

	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Protection", "Total Damage", descDamage.fDamageTotal );

	//
	//	AM I INVINCIBLE ?
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Immortal", "Checking", "" ); 

 	if ( this->HasFlag( NPC_FLAG_IMMORTAL ) || immortalByProtection ) 
	{
		descDamage.fDamageTotal = 0.0f;

		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Immortal", "Vitcim is immortal !", "" ); 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Immortal", "Total Damage", descDamage.fDamageTotal );
	}

	//
	//	CALCULATE EFFECTIVE DAMAGE
	//
	descDamage.fDamageEffective  = descDamage.fDamageTotal;
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Update", "Effective Damage", descDamage.fDamageEffective );

	//
	//	ASSURE MAXIMUM DAMAGE
	//
	int nDamage = (int) descDamage.fDamageEffective;

	if ( nDamage < 0 ) 
	{
		descDamage.fDamageEffective = 0.0f;
		nDamage						= (int) descDamage.fDamageEffective;
	}

	//
	//	STORE REAL DAMAGE
	//
	descDamage.fDamageReal		= descDamage.fDamageEffective;
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Update", "Real Damage", descDamage.fDamageEffective );

	//
	//	BARRIER DAMAGE IS ALWAYS DEADLY (HEHE!)
	//
	zBOOL	bBarrier		= this->HasFlag( descDamage.enuModeDamage, oEDamageType_Barrier	);
	zBOOL	bDeathByBarrier = FALSE;

	if ( bBarrier )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Condition()", "Death", "Barrier does damage", "" ); 

		if ( this->GetAnictrl() )
		{
			zBOOL	bInWater		= this->GetAnictrl()->GetWaterLevel() > 1;
					bDeathByBarrier	= bInWater;
		}
	}

	if ( bDeathByBarrier )	
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Condition()", "Death", "Victim is being hit by barrier whilst swimming/diving", "" );
		nDamage = this->GetAttribute( NPC_ATR_HITPOINTS );
	}

	//
	//	SUBTRACT HITPOINTS
	//
	
	// [Wohlers] - 14.02.01 - Mal wieder Mindestschaden eingebaut : Ueber Skriptkonstante
	static int		g_minDamageIndex		= -2;
	static int		g_minDamage				= 0;
	static int		g_minDamagePercIndex	= -2;
	static int		g_minDamagePerc			= 0;
	static float	g_fMinDamagePerc		= 0;

	if (g_minDamageIndex	== -2) {
		g_minDamageIndex	= parser.GetIndex("NPC_MINIMAL_DAMAGE");
		zCPar_Symbol* sym	= parser.GetSymbol(g_minDamageIndex);
		if (sym) sym->GetValue(g_minDamage);
		g_minDamagePercIndex= parser.GetIndex("NPC_MINIMAL_PERCENT");
		sym	= parser.GetSymbol(g_minDamagePercIndex);
		if (sym) sym->GetValue(g_minDamagePerc);
		g_fMinDamagePerc	= float(g_minDamagePerc) / 100.0f;
		
	}

	// war eigentlich kein treffer, daher wird nun der minimalschaden aus den skripten ermittelt
	if ( !bHasHit ) 
	{
		nDamage = int(g_fMinDamagePerc * float(nDamage));
	}


	//if ( !bUseRanged )			// Ranged Waffen machen keinen Mindestschaden
	if ( (!descDamage.pVisualFX) && (!descDamage.pFXHit) )
	if ( nDamage < g_minDamage ) 
	{
		nDamage = g_minDamage;
		descDamage.fDamageReal = (float)nDamage;
	}

	if ( !this->HasFlag( NPC_FLAG_IMMORTAL ) && !immortalByProtection )
	{
		this->ChangeAttribute( NPC_ATR_HITPOINTS, - nDamage );
	}

	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Update", "HP ", this->GetAttribute( NPC_ATR_HITPOINTS ) );

	//
	//	RESET REGENERATION COUNTERS
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Hit()", "Regeneration", "Resetting Values", "" );

	this->hpHeal	= GetAttribute( NPC_ATR_REGENERATEHP	) * 1000.0f;
	this->manaHeal	= GetAttribute( NPC_ATR_REGENERATEMANA	) * 1000.0f;
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Condition()

    09-Oct-00       [Roman Keskenti]

					  Initial implementation
						Checks npcs condition

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Condition ( oSDamageDescriptor& descDamage )
{
	oNOTIFY_SPY_DAMAGE( "OnDamage_Condition()", "", "", "" ); 

	//
	//	RELEVANTE MEMBER HOLEN
	//
	oCAniCtrl_Human *pAniCtrl = this->GetAnictrl();
	if ( ! pAniCtrl )	{ 	oNOTIFY_SPY_DAMAGE( "OnDamage_Condition()", "", "", "No valid Ani-Controler!" ); return; }

	//
	//	SCHADENS HOEHE UND TYP ERMITTELN
	//
	//zBOOL							bBarrier = this->HasFlag( descDamage.enuModeDamage, oEDamageType_Barrier	);
	zBOOL							bBlunt	 = this->HasFlag( descDamage.enuModeDamage, oEDamageType_Blunt		);
	zBOOL							bEdge	 = this->HasFlag( descDamage.enuModeDamage, oEDamageType_Edge		);
	if ( descDamage.pNpcAttacker )	bEdge	&= ! ( descDamage.pNpcAttacker->IsMonster() );

	//
	//	ZUSTANDS-FLAGS VORBESETZZEN
	//
	descDamage.bIsUnconscious	= FALSE;
	descDamage.bIsDead			= FALSE;

	//
	//	OHNMACHT
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Condition()", "Unconsciousness", "", "" ); 

	zBOOL	bUnconscious		 = ( this->GetAttribute( NPC_ATR_HITPOINTS ) == 1 );
	zBOOL	bDamageNotLethal	 =	this->IsDead();
	
	if	(   descDamage.pNpcAttacker ) 
	if	( ! descDamage.pNpcAttacker->IsHuman()  )	bDamageNotLethal	&=   (bBlunt || descDamage.bDamageDontKill)			;
	else											bDamageNotLethal	&=   (bBlunt || bEdge || descDamage.bDamageDontKill)	;


	zBOOL bScriptLegalGuild = this->IsHuman();


	if (descDamage.pNpcAttacker)
	{
		parser.SetInstance("SELF"	,this);
		parser.SetInstance("OTHER"	,descDamage.pNpcAttacker);

		int index = parser.GetIndex("C_DropUnconscious");
		if (index>0) bScriptLegalGuild = *(int*)parser.CallFunc(index);
	}

	if (	bDamageNotLethal || bUnconscious	)
	if (	descDamage.pNpcAttacker				)
	if ( !	pAniCtrl	->IsInWater		()		)
	if ( 	bScriptLegalGuild		)
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Condition()", "Unconsciousness", "Victim becomes unconscious", "" ); 

		descDamage.bIsUnconscious = TRUE ;
		if( IsSelfPlayer() ) oCNpc::player->CloseInventory();
	}

	//
	//	TOD
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Condition()", "Death", "", "" ); 

	zBOOL	bDeathByDamage	= ( ! descDamage.bIsUnconscious ) && ( this->IsDead() );

	if ( bDeathByDamage )
	{
		oNOTIFY_SPY_DAMAGE( "OnDa1mage_Condition()", "Death", "Victim will die", "" ); 

		descDamage.bIsDead	= TRUE ;
	}
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Script()

    09-Oct-00       [Roman Keskenti]

					  Initial implementation
						Activates script states accordingly

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Script ( oSDamageDescriptor& descDamage )
{
	oNOTIFY_SPY_DAMAGE( "OnDamage_Script()", "", "", "" ); 
	oNOTIFY_SPY_DAMAGE( "OnDamage_Script()", "", "", "Interrupting" ); 

	if ( !((IsAPlayer() && (GetWeaponMode()>=NPC_WEAPON_FIST) && (GetWeaponMode()<=NPC_WEAPON_MAG) )))
	{
		///*if ( GetBodyStateInterruptableOverride() != BS_INT_OVERRIDE_STUMBLE_ONLY )*/ 
		this->Interrupt( TRUE, FALSE );
	}

	//
	//	ASSESS DAMAGE
	//
	if ( ! descDamage.bIsDead )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Script()", "Assessions", "Assess Damage", "" ); 

		int nDamage = (int) descDamage.fDamageEffective;
		this->AssessDamage_S( descDamage.pNpcAttacker, nDamage );
	}
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Effects()

	27-Oct-00		[Keskenti]

						Initial implementation

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Effects( oSDamageDescriptor& descDamage )
{
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects()", "", "", "" ); 

	if ( descDamage.bFinished )	this->OnDamage_Effects_End	( descDamage );
	if ( descDamage.bOnce	  )	this->OnDamage_Effects_Start( descDamage );
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Effects_Start()

    10-Oct-00       [Keskenti]

					  Initial implementation
						Starts neccessary particle fx

	25-Oct-00		[Edenfeld]
						Umstellung für oCVisualFX Implementation

	26-Oct-00		[Speckels]
						NPC_BLOOD_MAX_DAMAGE eingefuehrt

    22-Nov-00       [Keskenti]
						NPC_BLOOD_MAX_DAMAGE und
						NPC_BLOOD_SIZE_DIVISOR werden vom Skript ausgelesen

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Effects_Start( oSDamageDescriptor& descDamage )
{
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "", "", "" ); 

	//
	//	RELEVANTE MEMBER HOLEN
	//

	zBOOL isInMovement = this->GetInMovement();
	if (isInMovement) this->EndMovement();

	oCAniCtrl_Human *pAniCtrl = this->GetAnictrl();
	if ( ! pAniCtrl )	{ 	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "", "", "No valid Ani-Controler!" ); return; }

	//
	//	SCHADENS HOEHE UND TYP ERMITTELN
	//
	zBOOL	bInWater		= ( pAniCtrl->GetWaterLevel() > 0 );
	zBOOL	bBurning		= this->HasFlag( descDamage.enuModeDamage, oEDamageType_Fire );
	zBOOL	bBurningAlready = this->HasBodyStateModifier( BS_MOD_BURNING );
	int		nDamageBurn		= (int) descDamage.aryDamageEffective[ oEDamageIndex_Fire ];
	int		nDamage			= (int) descDamage.fDamageEffective;


	//
	//	BLUTEN
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "", "" ); 

	zBOOL bBlood = TRUE;

	bBlood &= (	  descDamage.fDamageEffective > 0.0f								);
	bBlood &= ( ! this->HasFlag( NPC_FLAG_IMMORTAL )								);
	bBlood &= ( ! bBurning													 		);
	bBlood &= ( ! ( this->HasFlag( descDamage.enuModeWeapon, oETypeWeapon_Fist ) )
			 && ! (descDamage.pNpcAttacker && descDamage.pNpcAttacker->IsMonster() ));

	if ( bBlood ) 
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "Hit causes blood", "" ); 

		//
		//	BLOOD-MODE ?
		//
		if ( this->IsBloodEnabled() ) 
		if ( oCNpc::GetBloodMode() >= oCNpc::oEBloodMode_Particles )
		{
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "Starting Blood Trail Emitter", "" ); 

			//
			//	SELBER BLUTEN
			//
			zCParticleFX	*pParticleFX = zNEW( zCParticleFX	);
			zCVob			*pVobFX		 = zNEW( zCVob			);
			zCWorld			*pWorld		 = this->GetHomeWorld(  );

			pVobFX->SetPositionWorld( descDamage.vecLocationHit );		
			pVobFX->SetVisual		( pParticleFX );	
			pVobFX->SetCollDet		( FALSE );

			if ( pWorld ) pWorld->AddVob( pVobFX );

			pParticleFX->SetAndStartEmitter( this->bloodEmitter );
		
			//
			//	PARTICLE EFFECT FREIGEBEN
			//
			zRELEASE( pParticleFX	);
			zRELEASE( pVobFX		);

			//
			//	WAENDE UND BODEN VOLLBLUTEN
			//
			if ( oCNpc::GetBloodMode() >= oCNpc::oEBloodMode_Decals )
			{
				zVEC3	vecDirection;
				zVEC3	vecOrigin	;
				zREAL	fSize		;

				// -- ORIGIN & DIRECTION
				vecOrigin	 = 
				vecDirection = this->GetPositionWorld();

				if ( descDamage.pNpcAttacker != NULL )
				if ( descDamage.pNpcAttacker != this )	
				{
					vecDirection -= descDamage.pNpcAttacker->GetPositionWorld();
					vecDirection  .NormalizeApprox();
				}
				else
				{
					vecDirection *= -1;
				}

				vecDirection *= (zREAL) this->bloodDistance;
				
				// -- SIZE
				int		nBloodDamageMax		= 0;
				int		nBloodSizeDivisor	= 1;
				int		nSpread				= 1;

				zCPar_Symbol*	pSym = ::parser.GetSymbol( "BLOOD_DAMAGE_MAX"	);	if ( pSym ) pSym->GetValue( nBloodDamageMax		);
								pSym = ::parser.GetSymbol( "BLOOD_SIZE_DIVISOR" );	if ( pSym ) pSym->GetValue( nBloodSizeDivisor	);	if ( nBloodSizeDivisor == 0 ) nBloodSizeDivisor = 1;

									fSize		 = (zREAL) zMin( nDamage, nBloodDamageMax ); 
									fSize		*= this->bloodAmount;
									fSize		/= (zREAL) nBloodSizeDivisor;
									nSpread		 = (int) (fSize * 0.1);						// 10 % 
				if ( nSpread > 0 )	fSize		+= (zREAL)( zRand( nSpread ));				// 0% - 10%
				
				pAniCtrl->AddBlood( vecOrigin, vecDirection, fSize, this->IsBloodFlowEnabled(), &this->bloodTexture );

				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "Starting Blood Decals Emitter", "" ); 
				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "Size"		, fSize ); 
				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "Texture"	, this->bloodTexture ); 

			}
			else
				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "Blood decals disabled", "" ); 
		}
		else
				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Blood", "Blood particles disabled", "" ); 
	}
	//
	//	FEUER FANGEN
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Burn", "", "" ); 

	if (   nDamageBurn > 1	) 
	if (   bBurning			)
	if ( ! bBurningAlready	)
	if ( ! bInWater			)
	{
		//
		//	BURNING FX STARTEN
		//
		descDamage.strVisualFX	 = "VOB_BURN";

		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Burn", "VisualFX", descDamage.strVisualFX ); 

		//
		// DAUER SETZEN
		//
		int nTicksPerDamagePoint = NPC_BURN_TICKS_PER_DAMAGE_POINT;
		zCPar_Symbol  *pSymbol = ::parser.GetSymbol( "NPC_BURN_TICKS_PER_DAMAGE_POINT" );
		if ( pSymbol ) pSymbol->GetValue( nTicksPerDamagePoint );

		int nDamagePerIntervall = NPC_BURN_DAMAGE_POINTS_PER_INTERVALL;
		pSymbol = ::parser.GetSymbol( "NPC_BURN_DAMAGE_POINTS_PER_INTERVALL" );
		if ( pSymbol ) pSymbol->GetValue( nDamagePerIntervall );

		zREAL splitDamage				= zREAL(descDamage.aryDamageEffective[ oEDamageIndex_Fire ]);
		if (splitDamage == 0) splitDamage= float(descDamage.pNpcAttacker->GetAttribute( NPC_ATR_STRENGTH ));
		descDamage.fTimeDuration		= float(nTicksPerDamagePoint) * splitDamage;
		descDamage.fTimeInterval		= (zREAL) (nTicksPerDamagePoint);
		descDamage.fDamagePerInterval	= (float)nDamagePerIntervall;

		//
		//	SCHADENSART UND HOEHE SETZTEN
		//
		descDamage.enuModeDamage		= oEDamageType_Fire;
		::memset( descDamage.aryDamage, 0, oEDamageIndex_MAX * sizeof( zUINT32 ) );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Burn", "Duration"			, descDamage.fTimeDuration		 ); 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Burn", "Interval"			, descDamage.fTimeInterval		 ); 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "Burn", "Damage/Interval"	, descDamage.fDamagePerInterval ); 
	}


	//
	//	VISUAL FX STARTEN
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "", "" ); 

	if ( ! descDamage.strVisualFX.IsEmpty() )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "FX Name", descDamage.strVisualFX ); 

		//
		//	SUCHE EXISTIERENDE OVERLAY NACHRICHTEN
		//
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Searching former overlay damage messages", "" ); 

		oCMsgDamage *pMsgDamageCurrent	= NULL;
		oCMsgDamage *pMsgDamage			= NULL;
		int		 	 nMessages			= this->GetEM()->GetNumMessages();
		int		 	 nMessage			= 0;

		for ( ; nMessage < nMessages; nMessage ++ ) 
		{
			pMsgDamageCurrent = zDYNAMIC_CAST< oCMsgDamage > ( this->GetEM()->GetEventMessage( nMessage ) );

			if ( pMsgDamageCurrent )														//	MESSAGE IS VALID ( OF DESIRED TYPE )
			if ( pMsgDamageCurrent->GetSubType() == oCMsgDamage::EV_DAMAGE_PER_FRAME )		//	MESSAGE IS CONTINUOUS
			if ( pMsgDamageCurrent->descDamage.fTimeDuration > 0.0f )						//	MESSAGE HAS NOT FINISHED YET 
			{
				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Found active overlay damage", "" ); 

				pMsgDamage = pMsgDamageCurrent;
				break;
			}
		}

		//
		//	UPDATE FORMER MESSAGE'S VISUAL FX
		//
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Update", "" ); 

		zBOOL bCreateNew = TRUE;

		if ( pMsgDamage )
		{
			if	(	( pMsgDamage->descDamage.pVisualFX )											
				&&	( pMsgDamage->descDamage.pVisualFX->GetName () == descDamage.strVisualFX ) )
			{
				// der alte effekt wird gestoppt, da unten eh ein neuer erzeugt wird. Allerdings 
				// darf der alte effekt kein AssessMagic bei PFX Ende erzeugen, da nun der nächste Effekt dafür verantwortlich ist
				pMsgDamage->descDamage.pVisualFX->SetSendsAssessMagic(FALSE);
				pMsgDamage->descDamage.pVisualFX->Stop();
				pMsgDamage->descDamage.bFinished = TRUE;
			}
			else 
			{
				//
				//	STOP FORMER MESSAGE
				//
				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Former active overlay message cannot be modified", "Setting Duration to Zero" ); 
				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Duration", descDamage.fTimeDuration ); 

				pMsgDamage->descDamage.fTimeDuration = 0;
			};
		}
		
		//
		//	CREATE NEW VISUAL FX
		//
		if ( bCreateNew )
		{
			//
			//	NEUEN VISUAL FX ERZEUGEN
			//
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Creating new VisualFX", "" ); 

			oCVisualFX* visFX = zNEW(oCVisualFX);
			visFX->SetPositionWorld(GetPositionWorld());
			if ( GetHomeWorld() )	GetHomeWorld()->AddVob(visFX);

			visFX->SetLevel			( descDamage.nSpellLevel			);
			visFX->SetDamage		( descDamage.fDamageTotal			);
			visFX->SetDamageType	( descDamage.enuModeDamage			);
			visFX->SetSpellType		( descDamage.nSpellID				);
			visFX->SetSpellCat		( descDamage.nSpellCat				);
			visFX->SetByScript		( descDamage.strVisualFX			);
			visFX->Init				( this, 0, descDamage.pVobAttacker	);
			
			//
			//	OVERLAY SCHADEN AKTIVIEREN
			//
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Creating overlay damage message", "" ); 

			descDamage.SetVisualFX(visFX);

			oSDamageDescriptor descDamageFX = descDamage;

			// [Moos] Leakfix; wer auch immer den PFX da rein hat, hat das  AddRef schon gemacht.
			// [Edenfeld] AddRef wieder drin, bis der descriptor seinen copy operator überladen kriegt
//			if (descDamageFX.pFXHit)	descDamageFX.pFXHit	  ->AddRef();  
//			if (descDamageFX.pVisualFX)	descDamageFX.pVisualFX->AddRef();
            // [Moos] So. Die umstellung ist nun gemacht.

			if (descDamage.fTimeDuration==0)
			{
				// kein regelmässiger Schaden. Da aber die Npc Klasse dafür verantwortlich ist, das nur ein
				// Effekt gleichzeitig gespielt werden kann, muss dieser Effekt auch in einer Liste gespeichert
				// und reegelmässig überprüft werden. Benutzt wird dafür das EV_DAMAGE_PER_FRAME Interface, allerdings
				// ohne regelmässig Schaden abzuziehen
			    descDamageFX.Release();

				memset(&descDamageFX,0,sizeof(descDamageFX));
				descDamageFX.fTimeDuration	= FLT_MAX;
				descDamageFX.fTimeInterval  = 1000;						// alle Sekunde ein Check
				//descDamageFX.pNpcAttacker   = descDamage.pNpcAttacker;
				descDamageFX.SetVisualFX    (descDamage.pVisualFX);
			}

			//
			//	NACHRICHT VERSCHICKEN
			//
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Duration"			, descDamage.fTimeDuration		 ); 
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Interval"			, descDamage.fTimeInterval		 ); 
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Damage/Interval"	, descDamage.fDamagePerInterval ); 
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Sending overlay damage message", "" ); 

			oCMsgDamage* pMsg = zNEW( oCMsgDamage )( oCMsgDamage::EV_DAMAGE_PER_FRAME, descDamageFX );
			pMsg->SetHighPriority(TRUE);
			this->GetEM()->OnMessage( pMsg, this );

			//
			//	VISUAL FX "CAST"-EN
			//
			oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_Start()", "VisualFX", "Casting VisualFX", "" ); 

			visFX->Cast				();
			zRELEASE_ACCT(visFX);
        }
	}

	if (isInMovement) this->BeginMovement();
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Effects_End()

	25-Oct-00		[Edenfeld]
					  Neu erstellt:
					  Umstellung für oCVisualFX Implementation


--------------------------------------------------------------------------*/ 
void oCNpc::OnDamage_Effects_End( oSDamageDescriptor& descDamage )
{
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "", "", "" ); 

	//
	//	GET RELEVANT MEMBERS
	//
	zCModel	*pModel	= this->GetModel();	if ( ! pModel	)	{ 	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "", "", "No valid Model!" ); return; }

	//
	//	STOP PARTICLE EMITTER
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Particle Emitter", "", "" ); 

	if ( descDamage.pParticleFX )	
	{ 
		descDamage.pParticleFX->StopEmitterOutput();
		zRELEASE( descDamage.pParticleFX );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Particle Emitter", "Emitter Stopped", "" ); 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Particle Emitter", "Particle Released", "" ); 
	}

	//
	//	RELEASE PARTICLE'S VOB
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Visual Object", "", "" ); 

	if ( descDamage.pVobParticleFX )	
	{
		zRELEASE( descDamage.pVobParticleFX );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Visual Object", "Visual Object Released", "" ); 
	}

	if ( descDamage.pVisualFX)	
	{
		descDamage.pVisualFX->Stop();
		zRELEASE(descDamage.pVisualFX);
	}

	//
	//	APPLY BODY STATE MODIFICATION
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Body States", "", "" ); 

	if ( this->HasFlag( descDamage.enuModeDamage, oEDamageType_Fire ) )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Body States", "Stopped Burn", "" ); 
		this->ModifyBodyState( 0, BS_MOD_BURNING );
	}


	//
	//	STOP EFFECT-DEPENDANT ANIMATIONS
	//
	// [EDENFELD] ab 1.20 wird keine fire victim ani mehr getriggert, vergiss also auch das stoppen
#if 0
	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Animation", "", "" ); 

	if ( this->HasFlag( descDamage.enuModeDamage, oEDamageType_Fire ) )
	{
		//
		//	STOP ANIMATION 
		//
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Animation", "Stopping victim's fire animation", "" ); 

		pModel->StopAni( pModel->GetAniFromAniName( "S_FIRE_VICTIM" ) );

		//
		//	DELETE ANIMATION MESSAGES
		//
		oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Animation", "Searching fire animation messages", "" ); 

		oCMsgConversation *	pMsg		= NULL;
		int					nMessages	= this->GetEM()->GetNumMessages();
		int					nMessage	= 0;

		for (	; nMessage < nMessages; nMessage++ ) 
		{
			pMsg = zDYNAMIC_CAST< oCMsgConversation > ( this->GetEM()->GetEventMessage( nMessage ) );

			if ( pMsg )
			if ( pMsg->GetSubType() == oCMsgConversation::EV_PLAYANI_NOOVERLAY	) 
			if ( pMsg->name			== "S_FIRE_VICTIM"							)
			{
				pMsg->Delete();

				oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "Animation", "Fire animation message found and deleted", "" ); 
			}
		}
	}
#endif
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Anim()

    09-Oct-00       [Roman Keskenti]

					  Initial implementation
						Starts neccessary animations

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Anim ( oSDamageDescriptor& descDamage )
{
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "", "", "" ); 

	//
	//	RELEVANTE MEMBER HOLEN
	//
	oCAIHuman		*pAIHuman	= zDYNAMIC_CAST< oCAIHuman >( this->GetAI() );
	oCAniCtrl_Human *pAniCtrl	= this->GetAnictrl();
	zCModel			*pModel		= this->GetModel  ();

	if ( ! pAIHuman	)	{ 	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "", "", "Npc has no valid HumanAI!"		 ); return; }
	if ( ! pAniCtrl )	{ 	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "", "", "Npc has no valid Ani-Controler!" ); return; }
	if ( ! pModel	)	{ 	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "", "", "Npc has no valid Model!"		 ); return; }

	//
	//	SCHADENSTYP ERMITTELN
	//
	zBOOL	bBarrier		= this->HasFlag( descDamage.enuModeDamage, oEDamageType_Barrier	);
	zBOOL	bFall			= this->HasFlag( descDamage.enuModeDamage, oEDamageType_Fall	);
	zBOOL	bFlyAway		= this->HasFlag( descDamage.enuModeDamage, oEDamageType_Fly		);
//	zBOOL	bInWater		= ( pAniCtrl->GetWaterLevel() > 0 );
//	zBOOL	bBurning		= this->HasFlag( descDamage.enuModeDamage, oEDamageType_Fire	);
//	zBOOL	bBurningAlready = this->HasBodyStateModifier( BS_MOD_BURNING );
//	int		nDamageBurn		= (int) descDamage.aryDamageEffective[ oEDamageIndex_Fire ];
	int		nDamageFly		= (int) descDamage.aryDamageEffective[ oEDamageIndex_Fly  ] +  (int) descDamage.aryDamageEffective[ oEDamageIndex_Barrier ];

			bFlyAway	   |= bBarrier			;
			bFlyAway	   &= ( nDamageFly > 0 );

	//
	//	FALLEN? -> KEINE ANIS
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fall", "", "" ); 

	if ( bFall )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fall", "Returning", "" ); 

		return;
	}

	//
	//	BOGEN-ANI ZUREUCKSETZTEN
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Reset Bow", "", "" ); 

	if ( this->GetWeaponMode() == NPC_WEAPON_BOW )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Reset Bow", "Victim is in bow mode", "" ); 

		zCMorphMesh* pMeshMorph = zDYNAMIC_CAST<zCMorphMesh> ( this->GetWeapon() );
		if ( pMeshMorph )
		{
			oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Reset Bow", "Victim's weapon is a morph mesh", "Started Ani: S_RELAX" ); 

			pMeshMorph->StartAni( "S_RELAX" );
		}
	}

	//
	//	POLARKOORDINATEN HOLEN
	//
	if ( descDamage.pNpcAttacker )	this->GetAngles ( descDamage.pVobAttacker, descDamage.fAzimuth, descDamage.fElevation );

	//
	//	FIRE VICTIM ANI
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fire", "", "" ); 


	// [EDENFELD] ab 1.20 wird keine fire victim ani mehr getriggert
#if 0
	if (   nDamageBurn > 1	) 
	if (   bBurning			)
	if ( ! bBurningAlready	)
	if ( ! bInWater			)
	{
		oCMsgConversation *pMsg = zNEW( oCMsgConversation( oCMsgConversation::EV_PLAYANI_NOOVERLAY, "S_FIRE_VICTIM") );

		pMsg->SetHighPriority(TRUE);
		this->GetEM()->OnMessage( pMsg, this );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fire", "Fire Animation Message sent", "" ); 
	}
#endif
	//
	//	STOLPERN	[STUMBLE/KNOCKBACK]
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Stumble", "", "" ); 

	int nDamage = (int) descDamage.fDamageReal;

	// läuft eine waffe-zieh oder waffe-wegsteck message, oder ein finishing move ?
	zBOOL noWeaponSelect = TRUE;

	oCMsgWeapon *pMsgWeaponCurrent	= NULL;
	oCMsgAttack *pMsgAttackCurrent	= NULL;
	int		 	 nMessages			= this->GetEM()->GetNumMessages();
	int		 	 nMessage			= 0;

	for ( ; nMessage < nMessages; nMessage ++ ) 
	{
		pMsgWeaponCurrent = zDYNAMIC_CAST< oCMsgWeapon > ( this->GetEM()->GetEventMessage( nMessage ) );
		pMsgAttackCurrent = zDYNAMIC_CAST< oCMsgAttack > ( this->GetEM()->GetEventMessage( nMessage ) );

		if ( pMsgWeaponCurrent )														
		{
			if ( pMsgWeaponCurrent->GetSubType() <= oCMsgWeapon::EV_FORCEREMOVEWEAPON)		
			{
				noWeaponSelect = FALSE;
				break;
			}
		}
		else if (pMsgAttackCurrent)
		{
			if ( pMsgAttackCurrent->GetSubType() == oCMsgAttack::EV_ATTACKFINISH)		
			{
				noWeaponSelect = FALSE;
				break;
			}
		};
	}
	
	zBOOL casting   = FALSE;

	if (GetWeaponMode()==NPC_WEAPON_MAG)
	{
		if ( GetSpellBook()						&& 
			 GetSpellBook()->GetSelectedSpell() && 
			 GetSpellBook()->GetSelectedSpell()->GetSpellStatus()==SPL_STATUS_CAST )
		{
			casting = TRUE;
		}
	};

	noWeaponSelect |= GetAnictrl()->wmode == WMODE_NONE;

	if (   nDamage > 1						&&			// [DESIGN LT. ALEX -> SIEHE COMMENT ZU DEFECT #2051]  
		   noWeaponSelect					&& 
		!  casting							&&
		!  inventory2.IsOpen()				&& 
		!  bFlyAway							&&
	    !  descDamage.bIsDead				&&
	    !  descDamage.bIsUnconscious		&&
	    !( IsAPlayer() && (pAniCtrl->IsInPreHit() || pAniCtrl->IsInCombo() ) ) )	// wenn spieler zuschlägt, auch gar nix machen
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Stumble", "Damage causes stumble", "" ); 

		oCMsgConversation*	pMsg	= NULL;

		//
		//	STUMBLE
		//
		zBOOL playerHitDuringAttack =  (IsAPlayer() && (((GetWeaponMode()>=NPC_WEAPON_FIST) && (GetWeaponMode()<=NPC_WEAPON_MAG)) )); 
		zBOOL monsterNoStumble		= (!IsAPlayer() && GetBodyStateInterruptableOverride());

		if ( !playerHitDuringAttack && this->IsBodyStateInterruptable() && !monsterNoStumble)
		{ 
			// [Ulf] - 25.01.01 - Beim Stumblen den Eventmanager clearen und damit alle 
			//                    laufenden Msg entfernen.
		
			// stumblen bedeutet hier das gleiche wie alle aktionen abzubrechen, da der EM geleert wird. Ausserdem 
			// werden hier hitanis und sprüche beendet, falls ein NSC das bodystateinterruptableOverride Flag nicht gesetzt hat
			this->ClearEM		();
			this->Interrupt		(FALSE, FALSE);
			this->SetBodyState	( BS_STUMBLE );

			zSTRING strAni	  ;
			zSTRING strPrefix = GetInterruptPrefix();

			if ( descDamage.pFXHit )	
			{
				zCPar_Symbol *pSymbol = ::parser.GetSymbol("spellFXAniLetters");

				if ( ! pSymbol ) {	zERR_MESSAGE( 5, 0, "R: NPC: OnDamage_Anim() -> NPC = \"" + this->GetName() + "\" : SpellAni not found!" ); }
				else				pSymbol->GetValue( strPrefix, descDamage.pFXHit->GetSpellType() );

				strAni = "T_"+ strPrefix + "STUMBLE";
				if ( ! pModel->GetAniFromAniName( strAni ) )  strPrefix = GetInterruptPrefix();
			}

			//
			//	COMPOSE ANI STRING
			//
			strAni = "T_"+ strPrefix + "STUMBLE";

			//
			//	ADD DIRECTION FLAG WHEN NECCESSARY
			//
			if ( ::fabs( descDamage.fAzimuth ) <= 90 )	strAni += "B";

			//
			//	CREATE APPROPRIATE MESSAGE
			//
			pMsg = zNEW( oCMsgConversation( oCMsgConversation::EV_PLAYANI_NOOVERLAY, strAni ) );
		}

		//
		//	ZUCKEN
		//
		else
		{
	  		pMsg = zNEW( oCMsgConversation( oCMsgConversation::EV_PLAYANI, "T_GOTHIT" ) );
		}

		pMsg->SetHighPriority( TRUE );
		this->GetEM()->OnMessage( pMsg, this );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Stumble", "Stumble Message sent", "" ); 
	}


	//
	//	WEGFLIEGEN
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "", "" ); 

	if ( bFlyAway ) 
	if ( pAniCtrl->GetWaterLevel() == 0 )
	if ( GetBodyState() != BS_LIE )
	{ 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "Damage causes fly", "" ); 

		zVEC3 vecDirection	;

		if ( bBarrier )
		{
			oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "Using direction", "" ); 

			vecDirection = descDamage.vecDirectionFly;
		}
		else
		{
			oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "Using location", "" ); 

			zVEC3 vecPosition	;

			if		( descDamage.pVobAttacker	)	vecPosition = descDamage.pVobAttacker	->GetPositionWorld();
			else if ( descDamage.pVobHit		)	vecPosition = descDamage.pVobHit		->GetPositionWorld();
			else									vecPosition =				this		->GetPositionWorld() + this->GetAtVectorWorld() * 100.0f;

			vecDirection  = this->GetPositionWorld();
			vecDirection -= vecPosition;
			vecDirection.NormalizeApprox();
		}

		//
		//	FALLHOEHE UEBERSCHREIBEN
		//
		this->overrideFallDownHeight = TRUE;

		//
		//	WEITERE AKTIONEN DELEGIEREN
		//
		pAIHuman->StartFlyDamage( float(descDamage.aryDamageEffective[ oEDamageIndex_Fly ] + descDamage.aryDamageEffective[ oEDamageIndex_Barrier ]), vecDirection );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "Starting Fly Animation", "" ); 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "Vector [X]", vecDirection[VX] ); 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "Vector [Y]", vecDirection[VY] ); 
		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Fly", "Vector [Z]", vecDirection[VZ] ); 
	}

	//
	//	FACE ANI
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Facial Animation", "", "" ); 

	if (	::zsound					) 
	if ( ! descDamage.bIsDead			)
	if ( ! descDamage.bIsUnconscious	)
	{
		this->StartFaceAni ( NPC_TALK_ANI );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Facial Animation", "Started", "" ); 
	}

	//
	//	STERBEN
	//
	oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Death", "", "" ); 

	if ( descDamage.bIsDead )
	{
		zBOOL	bSwimming   = ( pAniCtrl->GetActionMode() == ANI_ACTION_DIVE );
				bSwimming  |= ( pAniCtrl->GetActionMode() == ANI_ACTION_SWIM );
		zBOOL	bBack	    = ( descDamage.fAzimuth <= 90.0f );

		zSTRING strAni		= "T_";
		
		if	( bSwimming )	strAni += "DIVE_2_DROWNED"	;
		else				
		{
							strAni += "DEAD"			; 
			if  ( bBack )	strAni += "B"				;
		}

		pModel->StartAni( strAni );

		oNOTIFY_SPY_DAMAGE( "OnDamage_Anim()", "Death", "Started: ", strAni ); 
	}
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Sound()

    09-Oct-00       [Roman Keskenti]

					  Initial implementation
						Plays the corresponding sounds

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Sound ( oSDamageDescriptor& descDamage )
{
	//
	//	CHECK SOUND SYSTEM'S AVAILABILITY
	//
	if ( ::zsound ) 
	{
		//
		//	RANDOMIZE VOICE VARIATION
		//
		int		nVariationMax	= NPC_VOICE_VARIATION_MAX;	zCPar_Symbol* pSymbol = ::parser.GetSymbol( "NPC_VOICE_VARIATION_MAX" ); if ( pSymbol ) pSymbol->GetValue( nVariationMax );
		int		nVariation		= zRand		( nVariationMax );
		zSTRING strVariation	= zSTRING	( nVariation );

		//
		//	COMPOSE VOICE STRING
		//
		zSTRING strSound  = "SVM_";
				strSound += this->GetVoice();
				strSound += descDamage.bIsDead ? "_DEAD" : "_AARGH";

		if ( nVariation && ( ! descDamage.bIsDead ) )
		{
				strSound += "_";
				strSound += strVariation;
		}

		//
		//	LOAD SOUND FX
		//
		zCSoundFX*						pSoundFX	= ::zsound->LoadSoundFX( strSound );

		//
		//	SETUP SOUND PARAMETERS
		//
		zCSoundSystem::zTSound3DParams	paramsSound;
										paramsSound.SetDefaults();
										paramsSound.pitchOffset = (zREAL) this->GetVoicePitch();			

		//
		//	PLAY SOUND
		//
		zTSoundHandle hSound = zsound->PlaySound3D( pSoundFX, this, 2, &paramsSound );						

		//
		//	ADD SOUND TO VOICE HANDLES LIST
		//
		this->listOfVoiceHandles.InsertEnd( hSound );

		//
		//	RELEASE SOUND
		//
		zRELEASE( pSoundFX );
	}
}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_Events()

    09-Oct-00       [Roman Keskenti]

					  Initial implementation
						Triggers neccessary messages

	24-Oct-00		[Edenfeld]
						
						Tranform Spruch wird bei Tod oder Bewusstlosigkeit
						beendet

	09-Nov-00		[Edenfeld]
						
					    Control Spruch wird beendet, wenn der Caster getroffen wird 

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_Events ( oSDamageDescriptor& descDamage )
{
	//
	//	GET RELEVANT MEMBERS
	//
	zCModel	*pModel	= this->GetModel();	if ( ! pModel	)	{ 	oNOTIFY_SPY_DAMAGE( "OnDamage_Effects_End()", "", "", "No valid Model!" ); return; }

	//
	//	OHNMACHT
	//
	if ( descDamage.bIsUnconscious )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Events()", "Unconsciouseness", "Dropping unconscious", "" ); 

		this->DropUnconscious( descDamage.fAzimuth, descDamage.pNpcAttacker );
	}
	
	//
	//	TOD
	//
	if ( descDamage.bIsDead )
	{
		oNOTIFY_SPY_DAMAGE( "OnDamage_Events()", "Death", "Dieing", "" ); 

		if ( ! descDamage.pNpcAttacker )	
			oNOTIFY_SPY_DAMAGE( "OnDamage_Events()", "Death", "ATTENTION: Attacker is invalid! No XPs will be given!", "" ); 

		pModel->StopAni( pModel->GetAniFromAniName( "S_FIRE_VICTIM" ) );
		this->DoDie( descDamage.pNpcAttacker );
	}

	//
	//	STOP CURRENT SPELL
	//
	oCMag_Book* pBook = this->GetSpellBook();
	if ( pBook )
	if ( descDamage.fDamageReal >= 1.0f )
	if ( !IsAPlayer() && !GetBodyStateInterruptableOverride() )
	{
		pBook->StopSelectedSpell();
	}

	//
	//	KONTROLL-ZAUBER BEENDEN
	//
	/*oCSpell	*pSpellControl	= NULL;
	oCNpc	*pNpcTarget		= NULL;

	//
	//	Kontrollierter NSC ?
	//
	if ( descDamage.pNpcAttacker )
	{
		pSpellControl	= descDamage.pNpcAttacker->IsSpellActive( SPL_CONTROL );
		pNpcTarget		= pSpellControl ? pSpellControl->GetSpellTargetNpc() : NULL;
	}

	if ( pSpellControl	) 
	if ( pNpcTarget		)
	if ( this->IsDead() ) 
	{
		pSpellControl->EndTimedEffect();			
	}

	//
	//	Kontrollierender Caster ?
	//
	zBOOL	bControlling = this->HasBodyStateModifier( BS_MOD_CONTROLLING );

	if (bControlling)
	{
		// Caster wurde getroffen. Spell beenden!
		// Der aktive Player hat den Spell registriert -> dort beenden
		pSpellControl = oCNpc::player->IsSpellActive(SPL_CONTROL);
		zERR_ASSERTT_STRICT(pSpellControl," C: tried to end the control spell, but there is no control spell active on the main player. Perhaps a NPC tried to control another NPC ?");
		pSpellControl->EndTimedEffect();
	};*/

}

/*--------------------------------------------------------------------------

    oCNpc::OnDamage_State()

    26-Oct-00       [Roman Keskenti]

					  Initial implementation

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage_State ( oSDamageDescriptor& descDamage )
{
	//
	//	BODY STATES SETZEN
	//
	oCAniCtrl_Human *pAniCtrl	= this->GetAnictrl();
	zBOOL	bBurning			= this->HasFlag( descDamage.enuModeDamage, oEDamageType_Fire );
	zBOOL	bBurningAlready		= this->HasBodyStateModifier( BS_MOD_BURNING );
	int		nDamageBurn			= (int) descDamage.aryDamageEffective[ oEDamageIndex_Fire ];
	zBOOL	bInWater			= pAniCtrl ? ( pAniCtrl->GetWaterLevel() > 0 ) : FALSE;

	if (   nDamageBurn > 1	) 
	if (   bBurning			)
	if ( ! bBurningAlready	)
	if ( ! bInWater			)
	{
		this->ModifyBodyState( BS_MOD_BURNING, 0 );
	}
}


/*--------------------------------------------------------------------------

    oCNpc::OnDamage()

    04-Sep-00       [Roman Keskenti]

						Added support for guild-dependant (fist-)damage-types

    13-Sep-00       [Max Dennis Luesebrink]

						Bogen jetzt toetlich

    13-Sep-00       [Roman Keskenti]

						attacker == NULL wird jetzt abgefangen und sorgt fuer 
						toedlichen Schaden (wg. console-command "kill")

	20-Sep-00		[Edenfeld]

						Windrichtung wurde um 180 Grad falsch herum berechnet. Korrigiert.

	25-Sep-00		[Edenfeld]	

						Default Stumble Ani für Magie wird gespielt, falls keine spezielle Ani vorhanden

	09-Oct-00		[Roman Keskenti]

						Changed for usage with new version 

--------------------------------------------------------------------------*/ 
void oCNpc :: OnDamage ( zCVob* pVobHit, zCVob* pVobAttacker, zREAL damage, int damageType, const zVEC3& hitLocation )
{
	oSDamageDescriptor	descDamage	;
	zDWORD				dwFlags		= 0;

	//
	//	FILL DESCRIPTOR
	//
	descDamage.pVobAttacker			= pVobAttacker										;
	descDamage.pVobHit				= pVobHit											;
	descDamage.fDamageTotal			= damage											;
	descDamage.vecLocationHit		= hitLocation										;
	descDamage.vecDirectionFly		= hitLocation										;

	descDamage.pNpcAttacker			= zDYNAMIC_CAST< oCNpc		  > ( pVobAttacker	)	;
	descDamage.pItemWeapon 			= zDYNAMIC_CAST< oCItem		  > ( pVobHit		)	;
	descDamage.SetFXHit              (zDYNAMIC_CAST< oCVisualFX	  > ( pVobHit		))	;

	descDamage.nSpellID				= ( descDamage.pFXHit ) ? descDamage.pFXHit->GetSpellType	 () : -1;
	descDamage.nSpellCat			= ( descDamage.pFXHit ) ? descDamage.pFXHit->GetSpellCat	 () : -1;
	descDamage.nSpellLevel			= ( descDamage.pFXHit)  ? descDamage.pFXHit->GetLevel		 () : -1;

	descDamage.fDamageMultiplier	= 1.0f;

	//	---	INIT MODES
																				descDamage.enuModeWeapon	 = oETypeWeapon_Unknown				;
																				descDamage.enuModeDamage	 = oEDamageType_Unknown				;

	//	---	NPC WEAPON MODE
	if ( descDamage.pNpcAttacker )
	{
		if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_FIST	) {	descDamage.enuModeWeapon	 = oETypeWeapon_Fist				;	damageType	|= descDamage.pNpcAttacker->GetDamageMode(); }
		if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_DAG		)	descDamage.enuModeWeapon	|= oETypeWeapon_Melee				;
		if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_1HS		)	descDamage.enuModeWeapon	|= oETypeWeapon_Melee				;
		if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_2HS		)	descDamage.enuModeWeapon	|= oETypeWeapon_Melee				;
		if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_BOW		)	descDamage.enuModeWeapon	|= oETypeWeapon_Range				;
		if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_CBOW	)	descDamage.enuModeWeapon	|= oETypeWeapon_Range				;
		if ( descDamage.pNpcAttacker->GetWeaponMode() == NPC_WEAPON_MAG		)	descDamage.enuModeWeapon	|= oETypeWeapon_Magic				;

		if		( descDamage.pItemWeapon											)												
			if	( descDamage.pNpcAttacker->GetWeapon() != descDamage.pItemWeapon	)	{ zERR_MESSAGE( 5, 0 ,"R: NPC: OnDamage() - Weapon is NOT equal to NPC's weapon !!!" ); }
			else																		;	
		else	  descDamage.pItemWeapon = descDamage.pNpcAttacker->GetWeapon()			;
	}																			
																																	
	//	--- WEAPON TYPES														
	if ( descDamage.pItemWeapon	)												
	{																			
		if ( descDamage.pItemWeapon->HasFlag( ITM_CAT_NF	) )					descDamage.enuModeWeapon	|= oETypeWeapon_Melee				;	
		if ( descDamage.pItemWeapon->HasFlag( ITM_CAT_FF	) )					descDamage.enuModeWeapon	|= oETypeWeapon_Range				;	
		if ( descDamage.pItemWeapon->HasFlag( ITM_CAT_MUN	) )					descDamage.enuModeWeapon	|= oETypeWeapon_Range				;	
		if ( descDamage.pItemWeapon->HasFlag( ITM_CAT_RUNE	) )					descDamage.enuModeWeapon	|= oETypeWeapon_Magic				;	
	}																			

	//	--- DAMAGE TYPES																														
	/*
	if ( damageType == ITM_DAM_BARRIER	)										descDamage.enuModeDamage	|= oEDamageType_Barrier				;
	if ( damageType == ITM_DAM_BLUNT	)										descDamage.enuModeDamage	|= oEDamageType_Blunt				;
	if ( damageType == ITM_DAM_EDGE		)										descDamage.enuModeDamage	|= oEDamageType_Edge				;
	if ( damageType == ITM_DAM_FIRE		)										descDamage.enuModeDamage	|= oEDamageType_Fire				;
	if ( damageType == ITM_DAM_FLY		)										descDamage.enuModeDamage	|= oEDamageType_Fly					;
	if ( damageType == ITM_DAM_MAGIC	)										descDamage.enuModeDamage	|= oEDamageType_Magic				;
	if ( damageType == ITM_DAM_POINT	)										descDamage.enuModeDamage	|= oEDamageType_Point				;
	*/
																				descDamage.enuModeDamage	 = damageType						;
	
	//	--- DAMAGE TYPE STILL UNKNOWN ?  -> USE WEAPON TYPE
	if	(	( descDamage.enuModeDamage == oEDamageType_Unknown ) 
		&&	(	 ( descDamage.pItemWeapon  ) 
			  || ( descDamage.pNpcAttacker ) ) )
	{
		if( this->HasFlag( descDamage.enuModeWeapon, oETypeWeapon_Range ) )		descDamage.enuModeDamage	|= oEDamageType_Point				;
		if( this->HasFlag( descDamage.enuModeWeapon, oETypeWeapon_Magic ) )		descDamage.enuModeDamage	|= oEDamageType_Magic				;
	}

	//
	//	EVALUATE FLAGS
	//

																				dwFlags						|=	oEDamageDescFlag_Damage			;
																				dwFlags						|=	oEDamageDescFlag_DamageType		;
	if ( descDamage.pVobAttacker	)											dwFlags						|=	oEDamageDescFlag_Attacker		;
	if ( descDamage.pNpcAttacker	)											dwFlags						|=	oEDamageDescFlag_Npc			;
	if ( descDamage.pVobHit			)											dwFlags						|=	oEDamageDescFlag_Inflictor		;
	if ( descDamage.pItemWeapon		)											dwFlags						|=	oEDamageDescFlag_Weapon			;
	if ( descDamage.pFXHit			)																											
	{																																			
																				dwFlags						|=	oEDamageDescFlag_VisualFX		;
																				dwFlags						|=	oEDamageDescFlag_SpellID		;
																				dwFlags						|=	oEDamageDescFlag_SpellLevel		;
	}																										
	if ( this->HasFlag( descDamage.enuModeDamage, oEDamageType_Barrier ) )		dwFlags						|=	oEDamageDescFlag_FlyDirection	;


	this->OnDamage( descDamage );
}

/*--------------------------------------------------------------------------

    oCNpc::HasFlag()

    09-Oct-00       [Roman Keskenti]

					  Initial implementation
						Checks any DWORD bitfield 
						for presence of specified flags

--------------------------------------------------------------------------*/ 
zBOOL oCNpc::HasFlag( zDWORD dwValue, zDWORD dwFlag )
{
	return ( ( dwValue & dwFlag ) == dwFlag );
}

