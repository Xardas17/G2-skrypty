/******************************************************************************** 
 
     $Workfile:: oNpcInv.cpp          $                $Date:: 13.04.01 18:27   $
     $Revision:: 41                   $             $Modtime:: 5.04.01 21:18    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNpcInv.cpp $
 * 
 * 41    13.04.01 18:27 Edenfeld
 * 
 * 40    16.02.01 18:53 Moos
 * Klau-Fix
 * 
 * 39    14.02.01 15:51 Speckels
 * 
 * 38    7.02.01 18:21 Keskenti
 * 
 * 37    29.01.01 21:59 Wohlers
 * 
 * 36    22.01.01 21:36 Speckels
 * 
 * 35    19.01.01 0:05 Speckels
 * 
 * 34    18.01.01 23:36 Speckels
 * 
 * 33    17.01.01 17:43 Keskenti
 * 
 * 32    16.01.01 16:14 Keskenti
 * 
 * 31    16.01.01 15:24 Keskenti
 * 
 * 30    10.01.01 12:14 Keskenti
 * 
 * 29    9.01.01 23:31 Keskenti
 * 
 * 28    9.01.01 18:14 Keskenti
 * 
 * 27    7.12.00 18:06 Keskenti
 * 
 * 26    5.12.00 18:35 Speckels
 * 
 * 25    29.11.00 17:20 Wohlers
 * 
 * 24    29.11.00 12:59 Keskenti
 * 
 * 23    29.11.00 12:52 Speckels
 * 
 * 22    25/10/00 15:48 Luesebrink
 * 
 * 21    21/10/00 13:01 Luesebrink
 * 
 * 20    4.10.00 18:23 Edenfeld
 * 
 * 19    4.10.00 16:47 Wohlers
 * 
 * 18    23.09.00 18:10 Wohlers
 * 
 * 17    20.09.00 16:51 Wohlers
 * 
 * 16    7.09.00 18:30 Speckels
 * 
 * 15    1.09.00 23:20 Wohlers
 * 
 * 14    29.08.00 18:29 Keskenti
 * 
 * 13    29.08.00 18:28 Keskenti
 * 
 * 12    24.08.00 11:33 Moos
 * new durch zNEW ersetzt
 * 
 * 11    21.08.00 18:56 Speckels
 * 
 * 10    31.07.00 22:04 Wohlers
 * 
 * 9     27.07.00 15:03 Wohlers
 * 
 * 8     5.07.00 12:21 Wohlers
 * 
 * 6     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 5     8.05.00 23:08 Edenfeld
 * 
 * 5     6.05.00 18:08 Wohlers
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 7     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 6     4.02.00 15:38 Wohlers
 * Bugfixes 
 * 
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zcore.h"

#include "zAICamera.h"
#include "zSound.h"

#include "oNpc.h"
#include "oItem.h"
#include "oAniCtrl.h"
#include "oGame.h"
#include "oDialog.h"
#include "oFocus.h"
#include "oInventory.h"
#include "oMobInter.h"
#include "oMagic.h"

#include "zEventMan.h"
#include "oNpcMessages.h"
#include "oCSManager.h"

#include "oAiHuman.h"

int oCNpc::game_mode = NPC_GAME_NORMAL;

// ***************************************************************************************
// PerFrame - Check 
// ***************************************************************************************

oCNpc*		stealnpc			= NULL;
zREAL		stealcheck_timer	= 0.0f;
const zREAL STEALCHECK_TIME		= 3 * 1000.0f;


zBOOL oCNpc :: IsVictimAwareOfTheft()
{
	if ( ! stealnpc ) return FALSE;
		
	int		nBodyState			= stealnpc->GetBodyState();
	zBOOL	bVictimAware		= stealnpc->HasVobDetected( this );																									
			bVictimAware	   &= ! stealnpc->IsDead		()	  ;																				// not dead			or
																																									
	zBOOL	bVictimNotMoving	= ( stealnpc->IsUnconscious	()	 );																				// not unconscious	or
			bVictimNotMoving   |= ( stealnpc->IsDead		()	 );																				// not dead			or
			bVictimNotMoving   |= ( oCNpc::game_mode == NPC_GAME_STEAL ) ? (nBodyState == BS_STAND || nBodyState == BS_ITEMINTERACT ) : FALSE;	// not standing		-> not moving at all

	return ( bVictimAware || !(bVictimNotMoving) );
}

void oCNpc :: CheckSpecialSituations()
{
	// b) Klaut der SC gerade ? 
	if ( stealnpc ) 
	if ( oCNpc::game_mode == NPC_GAME_STEAL || oCNpc::game_mode == NPC_GAME_PLUNDER )
	{
		zBOOL	bLostFocus			= GetFocusNpc() != stealnpc;
		zBOOL	bVictimAware		= this->IsVictimAwareOfTheft();
		zBOOL	bVictimInvalid		= bLostFocus || bVictimAware;

		if ( bVictimInvalid )
		{
			this->StopTheft( this, bVictimAware );
		} 
		else 
		{
			stealcheck_timer -= ztimer.GetFrameTimeF();
			if (stealcheck_timer<=0) 
			{
				// b3) Wird es von einem dritten gesehen ?
				stealnpc -> AssessTheft_S(this);
				stealcheck_timer += STEALCHECK_TIME;
			}
		}
	}
}

void oCNpc :: StopTheft( oCNpc* pNpc, BOOL bVictimAware )
{
	if ( ! pNpc ) return;

	if ( bVictimAware ) 
	{
		zBOOL inMove = GetInMovement();
		if (inMove) EndMovement();
					stealnpc -> CatchThief_S(pNpc);
		if (inMove) BeginMovement();
	}

	pNpc->CloseInventory();

	if ( oCNpc::game_mode == NPC_GAME_STEAL ) pNpc->CloseSteal	();
	else									  pNpc->CloseDeadNpc	();		

	stealnpc = NULL;
}

// ***************************************************************************************
// Inventory darstellen
// ***************************************************************************************

/* ----------------------------------------------------------------------
	
	oCNpc :: OpenInventory()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */


zMATRIX4 oCNpc::s_playerPositionMatrix;

void oCNpc :: OpenInventory (int mode)
{		
	if (ztimer.GetFrameTimeF()==0) return;
	// BodyState unterbrechbar ?
	if (!IsBodyStateInterruptable()) return;
	// Set mode
	inventory2.SetMode(mode);
	// Inventory offen ?
	if (inventory2.IsOpen()) return;		
	// Auch kein Monster ?
	if (IsMonster()) return;
	// Auch nicht waehrend WeaponChoose
	if (GetAnictrl() && GetAnictrl()->IsInWeaponChoose()) return;

	// Spieler drehen
	/*
	aiCam->SetRotateEnabled(FALSE);
	s_playerPositionMatrix = GetOldTrafoObjToWorld();	
	oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::TMovementSubType::EV_TURNTOPOS,aiCam->GetVob()));
	GetEM()->OnMessage(msg,this);	
	*/
	
	// Waffe wegstecken
	if (GetWeaponMode()!=NPC_WEAPON_NONE) 
		GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),this);

	// TurnAnis aus
	if (GetAnictrl()) GetAnictrl()->StopTurnAnis();

	// und anzeigen ( rechts oben )
	// int sx, sy;
	// inventory2.GetSize	(sx,sy);
	inventory2.DisableManipulateItems(FALSE);
	inventory2.DisableTransferMoreThanOneItem(FALSE);
	inventory2.SetName	(this->GetName());
	inventory2.Open		(IsSelfPlayer() ? 4096 : 0, 0, mode);
}

void oCNpc :: CloseInventory ()
{
	// Self
	inventory2.Close();
	// Trade
	CloseTradeContainer();

	// SetTrafoObjToWorld(s_playerPositionMatrix);	
}


// ***************************************************************************************
// bestehlen
// ***************************************************************************************

/*static*/ oCStealContainer* oCNpc :: stealcontainer = NULL;


/* ----------------------------------------------------------------------
	
	oCNpc :: OpenSteal()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */


zBOOL oCNpc :: OpenSteal ()
{
	// Beklauen SC->NSC wird im Interface NICHT ermöglicht, 
	// wenn der NSC den SC wahrnimmt. 
	// -> "C_NPC.Steal()" wird durchlaufen, wenn der Spieler das 
	// Inventory des NSCs offen hat (wurde erst nicht wahrgenommen) 
	// und der NSC sich dann umdreht und den SC wahrnimmt, oder wenn 
	// er von einem anderen NSC "gewarnt" wird.
	// Monster kann man nicht beklauen,
	
	stealnpc = GetFocusNpc();
	if ((!stealnpc) || (stealnpc->IsDead())) return FALSE;

	if (stealnpc->IsMonster() || stealnpc->GetTrueGuild() == NPC_GIL_ORCS ) return FALSE;

	// a) Klauen nur mit Talent.
	// b) Täter darf das Opfer nicht wahrgenommen haben
	// c) Täter muss innerhalb der Dialogreichweite stehen
	// d) Opfer darf nicht friendly und nicht main sein	wird im Script gecheckt.
	::parser.SetInstance	( "SELF"	, this		);
	::parser.SetInstance	( "OTHER"	, stealnpc	);

    int gmb = oCNpc::game_mode;
	oCNpc::game_mode = NPC_GAME_STEAL;
	zBOOL bIsAware  = this->IsVictimAwareOfTheft();
    oCNpc::game_mode = gmb;

	zBOOL bCanSteal = * ((zBOOL*) ::parser.CallFunc( "G_CANSTEAL" ));
	if ((	bCanSteal ) &&
	    ( !	bIsAware  ) &&
		( GetDistanceToVob2(*stealnpc) <= oCNpcFocus :: focus -> GetRange2() ) )
	{
		// Open it
		if (stealcontainer) {
			delete (stealcontainer);
			stealcontainer = NULL;
		};
		stealcontainer  = zNEW(oCStealContainer)();
		stealcontainer -> SetOwner	(stealnpc);
		
		if (stealcontainer  -> IsEmpty()) {
			GetEM()->OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_PLAYANI,"T_DONTKNOW"),this);
		
		} else {
			stealcontainer->SetName(stealnpc->GetName());
			stealcontainer->Open(0, 0, INV_MODE_STEAL);
			OpenInventory(INV_MODE_DEFAULT);
			stealcontainer->Activate();
			oCNpc::game_mode = NPC_GAME_STEAL;
			return TRUE;
		}
	
	} else {
		// Gib Feedback, dass es nicht geklappt hat.
		GetEM()->OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_PLAYANI,"T_DONTKNOW"),this);
	}

	return FALSE;
	// Hilfe
	// game_help -> Redraw();
}

void oCNpc :: CloseSteal()
{
	if (stealcontainer) {
		stealcontainer -> Close();
		oCNpc::game_mode = NPC_GAME_NORMAL;
	}
}

// ***************************************************************************************
// Tote NSCs ausrauben
// ***************************************************************************************

static oCNpcContainer* npccontainer = NULL;

////////////////////////////////////////////////////////////////////////////////
//
//	oCNpc::OpenDeadNpc
//
//	24.08.2000	[Moos]
//
//				auf zNEW umgestellt
//
//	2002-05-12	[BENDLIN]
//
//				Bugfix: Inventory-Empty-Prüfung korrigiert
//				ScriptFunc for empty NPCs
//
////////////////////////////////////////////////////////////////////////////////

void oCNpc :: OpenDeadNpc()
// Toto und Ohnmächtige können geplündert werden
{	
	// NSC im Focus ?
	stealnpc = GetFocusNpc();
	if (stealnpc) 
	{
		zBOOL bIsVictimDead			= stealnpc->IsDead		 ();
		zBOOL bIsVictimUnconscious	= stealnpc->IsUnconscious();

		if ( bIsVictimDead || bIsVictimUnconscious )
		{
			// NSC ist okay....
			// Open it
			// [EDENFELD]: Leakfix 1.09
			if (npccontainer)
			{
				delete npccontainer;
				npccontainer = 0;
			}

			npccontainer  = zNEW(oCNpcContainer)();
			npccontainer -> SetOwner(stealnpc);

			if ( !npccontainer->IsEmpty() )
			{
				npccontainer-> SetName(stealnpc->GetName());
				npccontainer->Open(0, 0, INV_MODE_PLUNDER);
				OpenInventory(INV_MODE_DEFAULT);
				npccontainer->Activate();
				oCNpc::game_mode = NPC_GAME_PLUNDER;
				return;	
			}
		} 
	}

	// Gib Feedback, dass es nicht geklappt hat.
//	GetEM()->OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_PLAYANI,"T_DONTKNOW"),this);
	//[KARK] Hier Meldung ausspucken: "Die Leiche ist schon leergeräumt."
	GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, PLAYER_PLUNDER_IS_EMPTY,-1),this);
}

void oCNpc :: CloseDeadNpc()
{
	if (npccontainer) {
		CloseInventory();
//		oCNpc* other = npccontainer->GetOwner();
		npccontainer -> Close();
		delete (npccontainer);
		npccontainer = NULL;
		oCNpc::game_mode = NPC_GAME_NORMAL;
	}
}
