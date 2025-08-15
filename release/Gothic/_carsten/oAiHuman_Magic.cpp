#include "zcore.h"
#include "omagic.h"
#include "oaihuman.h"
#include "onpc.h"
#include "zinput.h"
#include "ovisfx.h"
#include "oNpcMessages.h"
#include "ogame.h"


// ************************************************************************
// Magie
// ************************************************************************

zBOOL oCAIHuman :: CheckActiveSpells()
{
	// ENTER wurde gedrückt, irgendwelche Spells ????????
	if (ztimer.GetFrameTimeF()>0)
	if (zinput->KeyToggled(KEY_ENTER)) 
	{
		oCSpell* spell;
		for (int spellID=SPL_TRFSHEEP; spellID<=SPL_TRFDRAGONSNAPPER; spellID++)
		{
			spell = npc->IsSpellActive(spellID);
			if (spell) 
			{
				spell->EndTimedEffect();
				return TRUE;
			}
		}
	}
	return FALSE;
}

zBOOL oCAIHuman :: MagicInvestSpell()
{
	oCMag_Book*	sbook	= npc	-> GetSpellBook		();
	oCSpell*	spell	= sbook	-> GetSelectedSpell	();
	if (!spell) return FALSE;

	sbook -> Spell_Setup	(npc,npc->GetFocusVob());
	int spellStatus	= spell->GetSpellStatus();

	if (spellStatus == SPL_STATUS_DONTINVEST && spell->GetInvestedMana()==0)
	{
		// Dontknow-Ani nur bei Player [Ulf]
		zERR_MESSAGE(10,0,"C: MAGAI: Action pressed, invest called & no mana invested");
		if (npc->IsAPlayer() && (!dontKnowAniPlayed))
		{
			npc->GetModel()->StartAni("T_CASTFAIL");
			dontKnowAniPlayed = TRUE;
		}
	}
	
	if (!IsWalking() && (spellStatus==SPL_STATUS_CANINVEST || spellStatus == SPL_STATUS_CANINVEST_NO_MANADEC)) 
	{
		zERR_MESSAGE(10,0,"C: MAGAI: Action pressed & caninvest");
		
		zCPar_Symbol *sym = parser.GetSymbol("spellFXAniLetters");
		assert(sym);
		zSTRING aniPrefix;
		if (sym) sym->GetValue(aniPrefix,spell->GetSpellID());
		else zERR_FAULT("C: MagicMode: SpellAni Prefix not found!");

		SetAnimations			(npc->GetWeaponMode(),aniPrefix);

		sbook -> Spell_Invest	();

		spellStatus = spell->GetSpellStatus();
//		action		= TRUE;

		if (spell->GetInvestedMana()==0) 
		{	
			// Dontknow-Ani nur bei Player [Ulf]
			zERR_MESSAGE(10,0,"C: MAGAI: Action pressed, invest called & no mana invested");
			if (npc->IsAPlayer() && (!dontKnowAniPlayed))
			{
				npc->GetModel()->StartAni("T_CASTFAIL");
				dontKnowAniPlayed = TRUE;
			}
		}
		else if (spell->GetSpellStatus()!=SPL_STATUS_DONTINVEST) 
		{
			zERR_MESSAGE(10,0,"C: MAGAI: Action pressed, invest called & invest allowed");

			TransitionToInvest	();		
			// Passive Wahrnehmung aussenden
			npc->AssessCaster_S (spell);
		}

		// skript funktion skript_processmana_release entscheidet über den entgültigen status
		// nachdem die action taste losgelassen wurde
		if ( (spellStatus != SPL_STATUS_STOP) && (spellStatus != SPL_STATUS_CAST) )	spellReleased = FALSE;
		else spellReleased = TRUE;
		
		return TRUE;
	}
	return FALSE;
};

zBOOL oCAIHuman :: MagicCheckSpellStates(zBOOL action)
{
	oCMag_Book*	sbook	= npc	-> GetSpellBook		();
	oCSpell*	spell	= sbook	-> GetSelectedSpell	();
	if (!spell) return FALSE;

	int spellStatus	= spell->GetSpellStatus();

	if ( spellStatus == SPL_STATUS_CAST ) 
	{
		if (spell->GetInvestedMana() == 0) 
		{
			zERR_MESSAGE(10,0,"C: MAGAI: status cast & invested mana == 0");
			spell->SetSpellStatus(SPL_STATUS_CANINVEST);
			spellStatus = SPL_STATUS_CANINVEST;
			TransitionToStand	();
		}
		else 
		{
			zERR_MESSAGE(10,0,"C: MAGAI: status cast & invested mana > 0");
			if (s_shoot!=zMDL_ANI_ID_ILLEGAL)
			{
				if ( npc->GetModel()->IsAniActive(s_shoot) )					
				{
					zERR_MESSAGE(10,0,"C: MAGAI: shoot ani active: s_shoot -> do cast...");
					//if (spell->GetSpellID()==SPL_INSTANTFIREBALL || spell->GetSpellID()==::SPL_CHARGEFIREBALL) sbook -> Spell_Setup(npc,npc->GetFocusVob());		

					/*if (spell->GetEffect() && spell->GetEffect()->GetLevel()==0) 
					{
						spell->GetEffect()->InvestNext();
					}*/

					if (spell->CanChangeTarget())
					if ( spell->GetEffect()->GetTarget()!=npc->GetFocusVob() ) 
					{
						if (spell->GetEffect()->GetIsProjectile())			  
						{
							sbook->Spell_Setup(npc,npc->GetFocusVob(),TRUE);		
						}
					}
					sbook -> Spell_Cast	();

					spellCastedLastFrame = TRUE;
					action				 = TRUE;
				}
				else if (IsStanding())
				{
					zERR_MESSAGE(10,0,"C: MAGAI: status cast and standing, reset to caninvest state");
					spellStatus		= SPL_STATUS_CANINVEST;
					spell->SetSpellStatus(SPL_STATUS_CANINVEST);
				}
				else
				{
					// solange die shoot ani noch nicht gestartet wurde, sollten 
					// die targets der spell effekte neu gesetzt werden, falls notwendig
					zERR_MESSAGE(10,0,"C: MAGAI: shoot ani not active, waiting...");

					/*if (spell->GetEffect() && spell->GetEffect()->GetLevel()==0) 
					{
						spell->GetEffect()->InvestNext();
					}*/

					/*
				    if (spell->GetEffect()->GetTarget()!=npc->GetFocusVob() )
					{
						if (spell->GetEffect()->GetIsProjectile())			  
						{
							sbook->Spell_Setup(npc,npc->GetFocusVob(),TRUE);		
						}
					}*/
				}
			}
			else 
			{
				zERR_MESSAGE(10,0,"C: MAGAI: shoot ani illegal: -> do cast...");
				//if (spell->GetSpellID()==SPL_INSTANTFIREBALL || spell->GetSpellID()==::SPL_CHARGEFIREBALL) sbook -> Spell_Setup(npc,npc->GetFocusVob());		
				sbook -> Spell_Cast	();
				action		= TRUE;
			}
			TransitionToCast	();
		}
	} 
	else if (spellStatus == SPL_STATUS_STOP) 
	{		
		TransitionToStand	();

		if (spell->GetInvestedMana()>0) 
		{
			zERR_MESSAGE(10,0,"C: MAGAI: spell status: stop, mana invested > 0");
			sbook->StopSelectedSpell();
			sbook->GetSelectedSpell()->Open(); //[Moos] 15.2.2001: wieder reingenommen, sonst: Rune ist einen Frame lang zu sehen (war vorher auskommentiert)
			action = TRUE;
		} 
		else 
		{
			zERR_MESSAGE(10,0,"C: MAGAI: spell status: stop, mana invested == 0");
			spell->SetSpellStatus(SPL_STATUS_CANINVEST);
		}

	} 
	else if (action && (spellStatus == SPL_STATUS_DONTINVEST) && (spell->GetInvestedMana()==0)) 
	{
		zERR_MESSAGE(10,0,"C: MAGAI: action pressed, spell status: dontinvest, mana invested == 0");

	} 
	else if (!action) 
	{
		//zERR_MESSAGE(10,0,"C: MAGAI: action NOT pressed, call release status");

		if (!spellReleased) 
		{
			spell->SetReleaseStatus();
			spellReleased = TRUE;
		}

		// Codechange : [Ulf] - 09.01.01
		// - Safety : Irgendwie kann es passieren, dass die ShootAni noch laeuft, 
		//            obwohl der SpellStatus nicht mehr CAST ist. Die Ani wird nie beendet.
		//            Hier also mal auf Nummer sicher gehen. Sollte nicht mehr auftreten
		//            nach Aenderung in TransitionToCast, aber Programmieren ist ja ne
		//            verdammt komplizierte Sache...
		if (npc->GetModel()->IsAniActive(s_shoot)) TransitionToStand();
	}
	return TRUE;
}

zBOOL oCAIHuman :: MagicMode()
{
	zBOOL action = FALSE;
	oCMag_Book*	sbook = npc->GetSpellBook();

	if (ztimer.GetFrameTimeF()==0) return FALSE;

	if (oCGame::GetUseOldControls())
	{
		npc -> EndMovement();
		
		oCSpell* spell = sbook->GetSelectedSpell();

		if (!spell) return FALSE;

		if( npc->GetSpellBook()->GetNoOfSpells() == 0 ) npc->SetWeaponMode(NPC_WEAPON_NONE);

		// einmalig den Effekt initialisieren, wenn er auf der Hand ist
		// (für den FX INIT STATE)
		if (spell->GetEffect() && spell->GetEffect()->GetState() <= zVFXSTATE_OPEN)
		{	
			sbook->SetOwner			(npc);
			sbook->SetShowHandSymbol(TRUE);
		};

		zBOOL bKeyReleased = FALSE;


		if ( zinput->GetState(GAME_ACTION) )
		{
			if (spell->CanTurnDuringInvest()) 
			{
				npc->TurnToEnemy();
			}

			if ( zinput->GetState(GAME_UP) )
			{
				if (!spellCastedLastFrame)
				{
					action = TRUE;
				
					MagicInvestSpell();
				
					if ( spell->GetSpellStatus() == SPL_STATUS_CAST ||
						 spell->GetSpellStatus() == SPL_STATUS_STOP ||
						 spell->GetSpellStatus() == SPL_STATUS_DONTINVEST )
						 bKeyReleased = TRUE;
				}
			}
			else 
			{
				bKeyReleased			= TRUE ;
				dontKnowAniPlayed		= FALSE;
				spellCastedLastFrame	= FALSE; 
			}
		}
		else 
		{
			bKeyReleased			= TRUE ;
			dontKnowAniPlayed		= FALSE;
			spellCastedLastFrame	= FALSE; 
		}


		//
		//	KEY RELEASED
		//
		if ( bKeyReleased )
		{
			//
			//	HANDELT ES SICH UM EINEN INVESTIER-ZAUBER (OHNE CAST-PHASE)
			//
			if ( spell )							// Spell gueltig ?
			if ( spell->GetInvestedMana() > 0 )		// Wurde schon investiert?
			if ( spell->IsInvestSpell() )			// Ist das ein Investier-Zaueber ?
			{
				//
				//	DAS SPELL-ITEM HOLEN
				//
				oCItem* pItemSpell = sbook->GetSpellItem( spell );
				zERR_ASSERT( pItemSpell );

				if (pItemSpell->MultiSlot()){ // [Moos] nur weitermachen, wenn es keine Scroll ist
					//
					//	DAS ITEM AUS DEM INVENTORY ENTFERNEN (DE-REGISTER PASSIERT DANN AUTOMATISCH)
					//

					//	DIESEN BLOCK NUR 1-MAL AUSFUEHREN
					//
					spell->SetInvestedMana( 0 );
					spell->Setup		  (npc,0);			// damit z.B. beim gerade aktiven telekinesis spell die target effects gelöscht werden
					
					#ifdef _DEBUG
						oCItem* pItemRemoved = this->npc->RemoveFromInv( pItemSpell, 1 );
						zERR_ASSERT( pItemRemoved );
					#else
						npc->RemoveFromInv( pItemSpell, 1 );
					#endif


					//	"WAFFE" SPELL "WEGSTECKEN"
					//
					this->npc->GetEM()->OnMessage( zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), this->npc ); 

				}
			}
		}

		MagicCheckSpellStates(action);

		npc -> BeginMovement();
	}
	else
	{
		npc -> EndMovement();
		
		oCSpell* spell = sbook->GetSelectedSpell();

		if (!spell) return FALSE;

		if( npc->GetSpellBook()->GetNoOfSpells() == 0 ) npc->SetWeaponMode(NPC_WEAPON_NONE);

		// einmalig den Effekt initialisieren, wenn er auf der Hand ist
		// (für den FX INIT STATE)
		if (spell->GetEffect() && spell->GetEffect()->GetState() <= zVFXSTATE_OPEN)
		{	
			sbook->SetOwner			(npc);
			sbook->SetShowHandSymbol(TRUE);
		};

		zBOOL bKeyReleased = FALSE;
		

		if (spell->CanTurnDuringInvest()) 
		{
			npc->TurnToEnemy();
		}

		if ( zinput->GetState(GAME_ACTION) )
		{
			if (!spellCastedLastFrame)
			{
				action = TRUE;
			
				MagicInvestSpell();
			
				if ( spell->GetSpellStatus() == SPL_STATUS_CAST ||
					 spell->GetSpellStatus() == SPL_STATUS_STOP ||
					 spell->GetSpellStatus() == SPL_STATUS_DONTINVEST )
					 bKeyReleased = TRUE;
			}
		}
		else 
		{
			bKeyReleased			= TRUE ;
			dontKnowAniPlayed		= FALSE;
			spellCastedLastFrame	= FALSE; 
		}

		//
		//	KEY RELEASED
		//
		if ( bKeyReleased )
		{
			//
			//	HANDELT ES SICH UM EINEN INVESTIER-ZAUBER (OHNE CAST-PHASE)
			//
			if ( spell )							// Spell gueltig ?
			if ( spell->GetInvestedMana() > 0 )		// Wurde schon investiert?
			if ( spell->IsInvestSpell() )			// Ist das ein Investier-Zaueber ?
			{
				//
				//	DAS SPELL-ITEM HOLEN
				//
				oCItem* pItemSpell = sbook->GetSpellItem( spell );
				zERR_ASSERT( pItemSpell );

				if (pItemSpell->MultiSlot()){ // [Moos] nur weitermachen, wenn es keine Scroll ist
					//
					//	DAS ITEM AUS DEM INVENTORY ENTFERNEN (DE-REGISTER PASSIERT DANN AUTOMATISCH)
					//

					//	DIESEN BLOCK NUR 1-MAL AUSFUEHREN
					//
					spell->SetInvestedMana( 0 );
					spell->Setup		  (npc,0);			// damit z.B. beim gerade aktiven telekinesis spell die target effects gelöscht werden
					
					#ifdef _DEBUG
						oCItem* pItemRemoved = this->npc->RemoveFromInv( pItemSpell, 1 );
						zERR_ASSERT( pItemRemoved );
					#else
						npc->RemoveFromInv( pItemSpell, 1 );
					#endif


					//	"WAFFE" SPELL "WEGSTECKEN"
					//
					this->npc->GetEM()->OnMessage( zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), this->npc ); 

				}
			}

			//	Zurueck zur normalen Kamera
			ChangeCamMode(Cam_Normal);
		}

		MagicCheckSpellStates(action);

		npc -> BeginMovement();

	};
	return action;
}

