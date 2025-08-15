/******************************************************************************** 
 
     $Workfile:: oAIHuman.cpp         $                $Date:: 24.04.01 17:33   $
     $Revision:: 256                  $             $Modtime:: 19.04.01 18:38   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oAIHuman.cpp $
 * 
 * 256   24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 254   14.03.01 18:01 Wohlers
 * 
 * 253   15.02.01 19:42 Wohlers
 * 
 * 252   15.02.01 16:48 Wohlers
 * 
 * 251   14.02.01 22:38 Edenfeld
 * LookBack Fix
 * 
 * 250   14.02.01 21:39 Edenfeld
 * 
 * 249   14.02.01 4:13 Edenfeld
 * LookBack Cam
 * 
 * 248   13.02.01 19:48 Wohlers
 * 
 * 247   13.02.01 11:24 Speckels
 * 
 * 246   13.02.01 1:02 Edenfeld
 * CamModDeath funzt wieder
 * 
 * 245   9.02.01 13:44 Speckels
 * 
 * 244   8.02.01 16:11 Moos
 * 
 * 243   7.02.01 21:15 Wohlers
 * 
 * 242   7.02.01 20:55 Wohlers
 * 
 * 241   6.02.01 4:49 Wohlers
 * 
 * 240   6.02.01 4:12 Speckels
 * 
 * 239   6.02.01 3:38 Speckels
 * 
 * 238   6.02.01 3:26 Wohlers
 * 
 * 237   6.02.01 3:25 Wohlers
 * 
 * 236   6.02.01 3:16 Speckels
 * 
 * 235   6.02.01 2:31 Wohlers
 * 
 * 234   6.02.01 1:06 Wohlers
 * 
 * 233   6.02.01 0:22 Speckels
 * 
 * 232   5.02.01 23:27 Wohlers
 * 
 * 231   5.02.01 20:19 Wohlers
 * 
 * 230   2.02.01 23:39 Edenfeld
 * 
 * 229   1.02.01 20:09 Wohlers
 * 
 * 228   1.02.01 15:26 Wohlers
 * 
 * 227   30.01.01 20:34 Edenfeld
 * 
 * 226   30.01.01 19:13 Speckels
 * 
 * 225   30.01.01 18:15 Wohlers
 * 
 * 224   30.01.01 16:48 Moos
 * 
 * 223   29.01.01 22:40 Wohlers
 * 
 * 222   29.01.01 22:40 Wohlers
 * 
 * 220   29.01.01 20:30 Wohlers
 * 
 * 219   29.01.01 17:42 Keskenti
 * 
 * 218   28.01.01 19:30 Moos
 * 
 * 217   26.01.01 15:48 Moos
 * 
 * 216   26.01.01 15:51 Edenfeld
 * 
 * 215   26.01.01 14:18 Wohlers
 * 
 * 214   24.01.01 16:45 Wohlers
 * 
 * 213   24.01.01 14:57 Moos
 * 
 * 212   23.01.01 19:02 Wohlers
 * 
 * 211   22.01.01 22:42 Edenfeld
 * 
 * 210   20.01.01 2:35 Edenfeld
 * 
 * 209   19.01.01 0:07 Speckels
 * 
 * 208   17.01.01 17:59 Wohlers
 * 
 * 207   16.01.01 20:05 Wohlers
 * 
 * 206   16.01.01 15:17 Wohlers
 * 
 * 205   16.01.01 14:18 Wohlers
 * 
 * 204   12.01.01 21:01 Edenfeld
 * 
 * 203   12.01.01 20:56 Keskenti
 * 
 * 202   12.01.01 18:20 Edenfeld
 * 
 * 201   12.01.01 16:54 Edenfeld
 * 
 * 200   12.01.01 15:05 Wohlers
 * 
 * 199   12.01.01 12:38 Moos
 * 
 * 198   12.01.01 11:04 Wohlers
 * 
 * 197   11.01.01 16:34 Wohlers
 * 
 * 195   10.01.01 17:47 Hildebrandt
 * removed ReportCollisionToAI()
 * 
 * 194   10.01.01 13:11 Moos
 * 
 * 193   9.01.01 22:31 Speckels
 * 
 * 192   9.01.01 22:08 Speckels
 * 
 * 191   9.01.01 22:07 Speckels
 * 
 * 190   8.01.01 14:55 Wohlers
 * 
 * 189   5.01.01 17:49 Keskenti
 * 
 * 188   21.12.00 16:07 Moos
 * 
 * 187   20.12.00 21:18 Wohlers
 * 
 * 186   20.12.00 18:36 Speckels
 * 
 * 185   20.12.00 17:13 Moos
 * 
 * 184   18.12.00 14:59 Keskenti
 * 
 * 183   18.12.00 10:02 Keskenti
 * 
 * 182   11.12.00 18:45 Hildebrandt
 * 
 * 181   1.12.00 17:06 Keskenti
 * 
 * 180   29.11.00 18:16 Keskenti
 * 
 * 179   28.11.00 18:58 Keskenti
 * 
 * 178   23.11.00 17:49 Wohlers
 * 
 * 177   22.11.00 20:45 Wohlers
 * 
 * 176   21.11.00 14:12 Wohlers
 * 
 * 175   17/11/00 9:19 Luesebrink
 * 
 * 174   10.11.00 15:02 Moos
 * 
 * 173   9.11.00 14:50 Moos
 * 
 * 172   7.11.00 15:34 Wohlers
 * 
 * 171   7.11.00 14:55 Speckels
 * 
 * 169   6/11/00 17:50 Luesebrink
 * 
 * 168   6/11/00 15:26 Luesebrink
 * 
 * 167   1.11.00 16:13 Wohlers
 * 
 * 166   31.10.00 20:27 Keskenti
 * 
 * 165   30.10.00 17:05 Speckels
 * 
 * 164   27/10/00 14:35 Luesebrink
 * 
 * 163   26.10.00 16:49 Edenfeld
 * 
 * 162   26/10/00 14:27 Luesebrink
 * 
 * 161   23/10/00 18:50 Luesebrink
 * 
 * 160   23.10.00 18:49 Moos
 * 
 * 159   23/10/00 17:15 Luesebrink
 * 
 * 158   23/10/00 13:05 Luesebrink
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 256 $ ($Modtime: 19.04.01 18:38 $)

#include "zCore.h"

#include <zModel.h>
#include <zPhysics.h> 
#include "zrenderer.h"
#include "zAICamera.h"
#include "zParticle.h"
#include "zMusic.h"
#include "zInput.h"
#include "zInput_Const.h"

#include "oAniCtrl.h"
#include "oAIHuman.h"
#include "oNpc.h"
#include "oWorld.h"
#include "oDialog.h"
#include "oGame.h"
#include "oMagic.h"
#include "oAIShoot.h"
#include "oFocus.h"
#include "oSpell.h"
#include "oRoutine.h"
#include "oCSPlayer.h"
#include "oNpcStates.h"
#include "oMobInter.h"
#include "oSpawn.h"
#include "ocsmanager.h"
#include "oMusicZone.h"
#include "oportals.h"
#include "zsky.h"

#include "zEventMan.h"
#include "oNpcMessages.h"

#include "zInput_Win32.h"
#include "windows.h"
#include "zmorphmesh.h"

#pragma warning ( disable:4244 )

// auch in oAniCtrl.cpp!!
//#define E3_NOWATERDIVE
//#define TEST_LEAKS


zBOOL CapsLock(void)
{
  BYTE keyState[256];

  GetKeyboardState((LPBYTE)&keyState);
  if( keyState[VK_CAPITAL] & 1 ) return TRUE;
  return FALSE;
}

void SetCapsLock( BOOL bState )
{
  BYTE keyState[256];

  GetKeyboardState((LPBYTE)&keyState);
  if( (bState && !(keyState[VK_CAPITAL] & 1)) ||
      (!bState && (keyState[VK_CAPITAL] & 1)) )
  {
  // Simulate a key press
     keybd_event( VK_CAPITAL,
                  0x45,
                  KEYEVENTF_EXTENDEDKEY | 0,
                  0 );

  // Simulate a key release
     keybd_event( VK_CAPITAL,
                  0x45,
                  KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                  0);
  }
}

void ToggleCapsLock(void)
{
	SetCapsLock( !CapsLock() );
}


// **************************************
// Statics for activation of Cameramodes
// **************************************

zSTRING oCAIHuman :: Cam_Normal	= CamModNormal;
zSTRING oCAIHuman :: Cam_Run	= CamModRun;
zSTRING oCAIHuman :: Cam_Fight	= CamModNormal;

zSTRING curCamMode;

// **************************************
// Static Overlay MDS
// **************************************
static zCModelPrototype* s_sprintOverlay	= NULL;
static zCModelPrototype* s_crawlOverlay	    = NULL;
static int               s_overlayRefCtr    = 0;

// **************************************
// Static generate passive timed Percs
// **************************************
static const	zREAL OBSERVESUSPECT_TIME		= 3.0 * 1000;
static			zREAL observeSuspect_Counter	= 0.0;
static const	zREAL ASSESSUSEMOB_TIME			= 3 * 1000;
static			zREAL assessUseMob_counter		= 0.0;



/* ----------------------------------------------------------------------
	
    oCAIHuman :: oCAIHuman()	

	10.11.2000	[Moos]	
                overlay-RefCtr dazu


   ---------------------------------------------------------------------- */


// Constructor
oCAIHuman :: oCAIHuman ()
{
	// FIXME : Wohin damit ?
	Cam_Normal			= CamModNormal;
	Cam_Run				= CamModRun;
	Cam_Fight			= CamModNormal;

	aiCam				= NULL;					// FIXME : reichts, wenn's ne static ist ?
	forcejump			= FALSE;
	lookedAround		= FALSE;
	thirdPersonFallback	= FALSE;
	sprintActive		= FALSE;
	crawlActive			= FALSE;
	showai				= FALSE;
	startObserveIntruder= FALSE;
	dontKnowAniPlayed	= FALSE;
	spellReleased		= TRUE;
	spellCastedLastFrame= FALSE;
	eyeBlinkActivated   = FALSE;

	SetAutoRollMaxAngle	(15);
	SetAutoRollSpeed	(0.006F);
	SetAutoRollPosDest	(0);
	SetAutoRollEnabled	(TRUE);
	
	SetShowAI			(FALSE);

    s_overlayRefCtr ++;
}

// Destructor

/* ----------------------------------------------------------------------
	
    ocAIHuman::~OcAIHuman()	

	3.10.2000	[Moos]	
                Leck beseitigt

    10.11.2000  [Moos]
                Nochmal komplett umgebastelt wegen LoadGame-Problematik

   ---------------------------------------------------------------------- */

oCAIHuman:: ~oCAIHuman ()
{
    if (--s_overlayRefCtr<=0){
        zRELEASE(s_sprintOverlay);
        zRELEASE(s_crawlOverlay);
    }

    SetSprintMode(FALSE);
    SetCrawlMode(FALSE);
    
// [Moos] Loch sollte wieder gefixt sein. die Overlays werden erst dann auf NULL gesetzt, wenn sie
// wirklich zerstört wurden; und dass passiert erst dann, wennn der letzte oCAIHuman weg ist.

	aiCam = NULL;
};


/* ----------------------------------------------------------------------
	
	ocAIHuman::Init()
    
	3.10.2000	[Moos]	
                Leck beseitigt
    10.11.2000  [Moos]
                Overlay-Kacke in den Konstruktor oCAIHuman() verlegt

   ---------------------------------------------------------------------- */

void oCAIHuman :: Init ( oCNpc *n )
{
	if (!n) return;
	
	oCAniCtrl_Human :: Init (n);
	
    // [Moos] es ist Chaos zu erwarten, wenn diese Funktion mehr als einmal pro Instanz aufgerufen wird...

	ResetAutoRoll	();
}


zBOOL oCAIHuman :: DoSimpleAI()
// Die Simple-AI befreit den NSC aus bestimmten Zustaenden, 
// aus denen es nur ein Ausweg gibt.
// - s_hang		:	hochklettern
// - s_fallen	:	aufstehen
// - s_fallenb	:	aufstehen
{
	// Only for NSCs "s_jump"
	CheckJump();
	
	if (GetModel()->IsStateActive(s_fallenb)) {
		StartAni	(t_fallenb_2_stand,_s_walk);
		SetCDStat(TRUE);
		return TRUE;
	} else if (GetModel()->IsStateActive(s_fallen)) {
		StartAni	(t_fallen_2_stand,_s_walk);
		SetCDStat(TRUE);
		return TRUE;
	} else if (GetModel()->IsStateActive(s_hang)) {
		StartAni(t_hang_2_stand,_s_walk);
		return TRUE;
	} else if (IsStanding()) {
		// Schwimmen/Tauchen BS beachten
		if (GetActionMode()==ANI_ACTION_SWIM)	npc->SetBodyState(BS_SWIM);	else
		if (GetActionMode()==ANI_ACTION_DIVE)	npc->SetBodyState(BS_DIVE);	else
												npc->SetBodyState(BS_STAND);
	};
	return FALSE;
}

zBOOL oCAIHuman :: Pressed(int key)
{
	return zinput->GetState(key);
}

zBOOL oCAIHuman :: Toggled(int key)
{
	return zinput->GetToggled(key);
}

void oCAIHuman :: SetCamModeMob(oCMobInter* mob)
{
	if (zCAICamera::GetCurrent()->IsModeActive(CamModDialog)) return;

	zSTRING mode("CAMMODMOB");
	if (mob) mode += mob->GetScemeName();
	if (zCAICamera::GetCurrent()->IsModeAvailable(mode)) 
		SetCamMode(mode);
	else 
		SetCamMode(zSTRING("CAMMODMOBDEFAULT"));
}

void oCAIHuman :: ChangeCamMode(const zSTRING &activateCamMode)
{
	SetCamMode(activateCamMode,TRUE);
}

void oCAIHuman :: InitCamModes (int val)
{
    npc->AvoidShrink();

	int w;
	// Force special Mode ?
	if (val==-1)	w = npc->GetWeaponMode();
	else			w = val;

	if (w==NPC_WEAPON_NONE) {
		Cam_Normal	= CamModNormal;
		Cam_Run		= CamModRun;
	
	} else if (w<=NPC_WEAPON_2HS) {
		// Nahkampf
		Cam_Normal	= CamModNormal;
		Cam_Run		= CamModRun;
		Cam_Fight	= CamModMelee;
	} else if ((w==NPC_WEAPON_BOW) || (w==NPC_WEAPON_CBOW)) {
		// Fernkampf
		Cam_Normal  = CamModNormal;
		Cam_Run		= CamModRun;
		Cam_Fight	= CamModMelee;
//		Cam_Fight	= CamModRanged;
	} else {
		// Magie
		Cam_Normal  = CamModMagic;
		Cam_Run		= CamModRun;
		Cam_Fight	= CamModMelee;	
//		Cam_Fight	= zSTRING("CamModMagic");	
	}
}

void oCAIHuman :: SetCamMode(const zSTRING& activateCamMode, zBOOL checkSpecial)
{
	return;
	if (!npc->IsSelfPlayer()) return;
	// [EDENFELD] Hack: Falls Npc tot darf in keinen anderen Mode ausser CamModDeath
	// geschaltet werden
	// [EDENFELD] Noch ein Hack, der die Zurückschaukamera ermöglicht, 
	// bitte nicht schlagen. Morgen ist Goldmaster :)
	if (!zCAICamera::GetCurrent())														return;
	if (!zCAICamera::GetCurrent()->GetModeChangeEnabled() && activateCamMode == CamModLook)		return;
	
	if (curCamMode == CamModDeath && npc && npc->IsDead())								return;
	if ( (curCamMode == CamModLook || curCamMode == CamModLookBack) && lookedAround ) 	return;
	

	if (checkSpecial) 
	{
		if (zCAICamera::GetCurrent()->IsModeActive(CamModDialog)) return;
		if (zCAICamera::GetCurrent()->IsModeActive(CamModMelee)) 
		{
			// Wechsel der Kamera im CamModMelee
			// nach CamRun oder CamNormal nicht erlaubt
			if ((activateCamMode==CamModRun) || (activateCamMode==CamModNormal)) return;	
		}
	}
	if (curCamMode!=activateCamMode) 
	{
		zERR_MESSAGE(9,0,"U:AI: Camera-mode changed : "+activateCamMode);
	}
	curCamMode = activateCamMode;
}

void oCAIHuman :: WeaponChoose()
{
	// Waffenauswahl
	if (!Pressed(GAME_WEAPON)) {
		if (changeweapon) {
			
			if (npc->GetTrueGuild()<=NPC_GIL_MAX) {
				npc->GetEM()->OnMessage(zNEW(oCMsgWeapon(oCMsgWeapon::EV_DRAWWEAPON2)),npc);
			}				

			// Camera einstellen
			InitCamModes(wmode_selected);
			
			// Hier nicht über                          Override,da CamModMelee aktiv sein kann und
			// der Wechsel abgefangen wird.
			if( Cam_Normal != CamModMagic ) SetCamMode(Cam_Normal);
			
			// FocusMode einstellen
			if (wmode_selected<NPC_WEAPON_BOW)
				oCNpcFocus::SetFocusMode(FOCUS_MELEE);
			else
				oCNpcFocus::SetFocusMode(FOCUS_RANGED);
		
		} else {
			
			if ((npc->GetTrueGuild()<=NPC_GIL_MAX) && !IsStanding())
				npc->GetEM()->OnMessage(zNEW(oCMsgWeapon(oCMsgWeapon::EV_REMOVEWEAPON2)),npc);

			else 
				//wmode = WMODE_NONE;
				SetActionMode(ANI_ACTION_STAND);

			// Camera einstellen
			// Hier nicht über Override,da CamModMelee aktiv sein kann und
			// der Wechsel abgefangen wird.
			InitCamModes(NPC_WEAPON_NONE);

			SetCamMode	(Cam_Normal);
			// FocusMode einstellen
			oCNpcFocus::SetFocusMode(FOCUS_NORMAL);

		}
	} else {
		// Waffenauswahl hoch
		if (Toggled(GAME_UP)) {
		
			if (npc->GetTrueGuild()<=NPC_GIL_MAX) 
				npc->GetEM()->OnMessage(zNEW( oCMsgWeapon(oCMsgWeapon::EV_CHOOSEWEAPON,+1)),npc);

		}

		// Waffenauswahl runter
		if (Toggled(GAME_DOWN)) {
			if (npc->GetTrueGuild()<=NPC_GIL_MAX) 
				npc->GetEM()->OnMessage(zNEW( oCMsgWeapon(oCMsgWeapon::EV_CHOOSEWEAPON,-1)),npc);

		}

		// *********************************
		// Magiemodus - Zauberspruchauswahl
		// *********************************
		if (wmode_selected>=NPC_WEAPON_MAG) {
			npc->EndMovement();

			oCMag_Book* mb = npc->GetSpellBook();
			if (mb && !mb->IsInMovement()) {
				if (Pressed(GAME_LEFT) || Pressed(GAME_STRAFELEFT)) {
					changeweapon		= TRUE;
					oCMsgMagic* move	= zNEW( oCMsgMagic(oCMsgMagic::EV_MOVE,wmode_selected,-1));
					move-> level		= -1;
					move-> activeSpell	= mb->GetSelectedSpellNr();
					npc	-> GetEM() -> OnMessage (move,npc);
					// mb->Left();
				} else if (Pressed(GAME_RIGHT) || Pressed(GAME_STRAFERIGHT)) {
					changeweapon		= TRUE;
					oCMsgMagic* move	= zNEW( oCMsgMagic(oCMsgMagic::EV_MOVE,wmode_selected,-1));
					move-> level		= 1;
					move-> activeSpell	= mb->GetSelectedSpellNr();
					npc	-> GetEM() -> OnMessage (move,npc);
					// mb->Right();
				}								
			}
			
//			npc->BeginMovement();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//	
//	oCAIHuman::BowMode()
//
//	24.08.2000	[Moos]	
//
//				auf zNEW umgestellt
//
//	2002-06-18	[BENDLIN]
//	
//				back to old fight comtrols
//
//////////////////////////////////////////////////////////////////////////////

zBOOL oCAIHuman :: BowMode(zBOOL pressed)
{

	if (oCGame::GetUseOldControls())
	{
		zCModel  *model = npc->GetModel();

		if ( !npc->IsMunitionAvailable(npc->GetWeapon()) ) 
		{
			// Addon : BowMorphMesh zur Sicherheit zuruecksetzen

			oCVob*	  vob = zDYNAMIC_CAST<oCVob>(npc->GetEquippedRangedWeapon());
			if (!vob) vob = zDYNAMIC_CAST<oCVob>(npc->GetWeapon());

			if (vob)
			{
				zCMorphMesh* pMeshMorph = zDYNAMIC_CAST<zCMorphMesh>(vob->GetVisual());
				if ( pMeshMorph ) pMeshMorph->StartAni( "S_RELAX" );
			}

			npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), npc);
		}

		if ( model->IsAniActive(_s_aim) )
		{
			// Hat man für die Waffe keine Munition mehr, 
			// darf die Waffe mit CTRL nicht angehoben werden.
			// Wechseln zum WalkZustand
			if ( !npc->IsMunitionAvailable(npc->GetWeapon()) )
			{
				StartAni(_t_aim_2_walk, _s_walk);
				return FALSE;
			}

			// GetAngles
			zREAL azi = 0, elev = 0;


			// Autoaiming 
			if ( npc->GetFocusVob() )
			{
				// Hey, ziele nicht auf mich
				if ( npc->GetEnemy() )
					npc->GetEnemy()->AssessThreat_S(npc);
				npc->GetAngles(npc->GetFocusVob(), azi, elev);

				if (!oCNpcFocus::focus->IsInAngle(npc->GetFocusVob()->GetVobType(), azi,elev))
				{
					azi = 0; elev = 0;
				};
			} 

			zREAL xk = (azi / 90) + 0.5;
			zREAL yk = 1 - ((elev / 90) + 0.5);
			zClamp(xk, 0.0f, 1.0f);
			zClamp(yk, 0.0f, 1.0f);
			InterpolateCombineAni(xk, yk, _s_aim);

			if ( !pressed )
			{			
				if ( IsStateAniActive(_s_aim) )
					StartAni(_t_aim_2_walk, _s_walk);
			}
			else if ( Pressed(GAME_UP) )
			{
				// FIXME : Erst am Ende der AI abschiessen ?
				npc -> DoShootArrow (TRUE); 
				model->StartAni(_t_hitf);
			}
			PC_Turnings();
			return TRUE;
		}
		else if ( model->IsAniActive(_s_hitf) )
		{
			model->StartAni(_t_hitback);
			PC_Turnings();
			return TRUE;
		}
		else if ( model->IsAniActive(_t_hitback) )
		{
			npc->DoDoAniEvents();
			PC_Turnings();
			return TRUE;
		}
		else if ( pressed && IsStanding() )
		{
			model->StartAni(_t_walk_2_aim);
			return TRUE;
		} 
	}
	else
	{
		zCModel  *model = npc->GetModel();

		if ( !npc->IsMunitionAvailable(npc->GetWeapon()) || zinput->GetState(GAME_WEAPON) )
		{

			oCVob*	  vob = zDYNAMIC_CAST<oCVob>(npc->GetEquippedRangedWeapon());
			if (!vob) vob = zDYNAMIC_CAST<oCVob>(npc->GetWeapon());

			if (vob)
			{
				zCMorphMesh* pMeshMorph = zDYNAMIC_CAST<zCMorphMesh>(vob->GetVisual());
				if ( pMeshMorph ) pMeshMorph->StartAni( "S_RELAX" );
			}

			npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), npc);

		}
		if (model->IsAniActive(_s_aim)) 
		{
			// Hat man für die Waffe keine Munition mehr, 
			// darf die Waffe mit CTRL nicht angehoben werden.
			// Wechseln zum WalkZustand
			if ( !npc->IsMunitionAvailable(npc->GetWeapon()) )
			{
				StartAni(_t_aim_2_walk, _s_walk);
				return FALSE;
			}
			// GetAngles
			zREAL azi = 0, elev = 0;
			// Autoaiming 
			if ( npc->GetFocusVob() )
			{
				// Hey, ziele nicht auf mich
				if ( npc->GetEnemy() )
					npc->GetEnemy()->AssessThreat_S(npc);
				npc->GetAngles(npc->GetFocusVob(), azi, elev);
			} 

			zREAL xk = (azi / 90) + 0.5;
			zREAL yk = 1 - ((elev / 90) + 0.5);
			zClamp(xk, 0.0f, 1.0f);
			zClamp(yk, 0.0f, 1.0f);
			InterpolateCombineAni(xk, yk, _s_aim);

			if ((!npc->GetFocusVob() || Pressed(GAME_UP) || Pressed(GAME_DOWN)) && !Pressed(GAME_ACTION) ) 
			{			
				if ( IsStateAniActive(_s_aim) )
					StartAni(_t_aim_2_walk, _s_walk);
				PC_Turnings();
			} 
			else if ( Pressed(GAME_ACTION) ) 
			{
				npc->DoShootArrow(TRUE); 
				model->StartAni(_t_hitf);
			}
			PC_Turnings();
			
			PC_Strafe(Pressed(GAME_STRAFELEFT)||Pressed(GAME_STRAFERIGHT));

			return TRUE;
		} 
		else if ( model->IsAniActive(_s_hitf) ) 
		{
			model->StartAni(_t_hitback);
			PC_Turnings();
			return TRUE;
		} 
		else if ( model->IsAniActive(_t_hitback) ) 
		{
			npc -> DoDoAniEvents();
			PC_Turnings();
			return TRUE;
		}
		else if ( (npc->GetFocusVob() || Pressed(GAME_ACTION)) && IsStanding() ) 
		{
			PC_Turnings();
			model->StartAni(_t_walk_2_aim);
			return TRUE;
		} 
		return FALSE; 
	};
	return FALSE;
}

static zCArray<zCVob*>enemyList;

oHEROSTATUS oCAIHuman :: GetEnemyThreat()
// Ermittle neue Liste von Gegnern für die Kampfkamera
// und liefert auch gleich den BedrohungsLevel fürs Musiksystem zurück.
// wobei 0 = keine Bedrohung (Grundthema)
// wobei 1 = Bedrohung : Kampf NSC + NSC / Lebensenergie des Spielers <= 5
// wobei 2 = Kampf : Der Spieler ist in Kampf verwickelt.
{
    const  zREAL			THREATCHECKTIME	= 0.0f * 1000.0f;                           
    static zREAL			threatTimer		= 0.0f;
	static int				attackIndex		= -2;
	static int				attackIndex2	= -2;
	static oHEROSTATUS		threatLevel		= oHERO_STATUS_STD;

	// Homeworld sollte schon da sein....
	if (!npc || !npc->GetHomeWorld()) return oHERO_STATUS_STD;

	// ***************************************************************************
	// Nur jede Sekunde updaten
	// ***************************************************************************
    // Check nur alle 3 Sekunden machen, so verhindert man auch den schnellen 
    // Kameramoduswechsel
    threatTimer += ztimer.GetFrameTimeF();
    if (threatTimer < THREATCHECKTIME) return threatLevel;
	threatTimer -= THREATCHECKTIME;
	
	const float CHECK_RADIUS = 1000;
	zTBBox3D box;
	enemyList.DeleteList();
	threatLevel = oHERO_STATUS_STD;

	if (attackIndex ==-2) attackIndex	= parser.GetIndex("ZS_ATTACK");
	if (attackIndex2==-2) attackIndex2	= parser.GetIndex("ZS_MM_ATTACK");

	box.maxs = npc->GetPositionWorld() + (CHECK_RADIUS * zVEC3(1,1,1));
	box.mins = npc->GetPositionWorld() - (CHECK_RADIUS * zVEC3(1,1,1));

	oCNpc* other = NULL;

	zCArray<zCVob*>checkVobList;

	npc->GetHomeWorld()->CollectVobsInBBox3D(checkVobList, box);
	for (int i=0; i<checkVobList.GetNumInList(); i++) {

		other = zDYNAMIC_CAST<oCNpc>(checkVobList[i]);
		
		if (other) {

			if ((other!=npc) && other->IsConditionValid()) {
				float dist = (npc->GetPositionWorld() - other->GetPositionWorld()).LengthApprox();
				if ( (dist<CHECK_RADIUS) && (other->GetWeaponMode()!=NPC_WEAPON_NONE) ) {
					// Winkel ?
					enemyList.Insert(other);
					// Treatlevel ermitteln
					if (other->GetEnemy()==npc) {
						if (other->state.IsInState(attackIndex) || other->state.IsInState(attackIndex2)) {	
							if (npc->GetWeaponMode()==NPC_WEAPON_NONE)	return oHERO_STATUS_THR;
							else										return oHERO_STATUS_FGT;
						}
					}
				}
			}
		}
	}
	
	if (threatLevel==oHERO_STATUS_STD) {
		// Noch nichts ermittelt...
		if (npc->GetAttribute(NPC_ATR_HITPOINTS)<=5) {
			// a) Lebensenergie gering...
			threatLevel = oHERO_STATUS_THR;
		} else {
			// b) Waldportalraum ?
			zSTRING* curPortal = (zSTRING*)npc->GetSectorNameVobIsIn();
			if (curPortal && curPortal->Search("WALD")>=0) threatLevel = oHERO_STATUS_THR;
		}
	}
	return threatLevel;
}

void oCAIHuman :: CheckFightCamera()
// ********************************************************************************
// Kameramodus checken - Verzögerte Wechsel
// ********************************************************************************
{
    // Check nur alle 3 Sekunden machen, so verhindert man auch den schnellen 
    // Kameramoduswechsel
    if ((enemyList.GetNumInList()>0) || (npc->GetWeaponMode()!=NPC_WEAPON_NONE)) {
            
            // ChangeCamModeToMelee(enemyList);
    
    } else if (zCAICamera::GetCurrent()->IsModeActive(Cam_Fight)) {
    
            if (GetWalkMode() == ANI_WALKMODE_RUN) 
                    // Hier nicht über meine ChangeCamMode, da sonst die Overrides 
                    // greifen und der CamMode nie mehr zurückgeschaltet wird,
                    SetCamMode(Cam_Run);
            else
                    SetCamMode(Cam_Normal);     
    }
}

//////////////////////////////////////////////////////////////////////////////
//	
//	2002-06-18	[BENDLIN]
//	
//				back to old fight comtrols
//
//////////////////////////////////////////////////////////////////////////////

zBOOL oCAIHuman :: FightMelee()
{
	zBOOL attacked = FALSE;
	zCModel *model = npc->GetModel();

	CheckFightCamera();

	if (oCGame::GetUseOldControls())
	{
		if ( Pressed(GAME_ACTION) )
		{
			if ( !npc->GetFocusVob() )
				StopTurnAnis();

			npc->TurnToEnemy();

			if ( Pressed(GAME_UP) ) 
			{
				if ( IsWalking() ) 
				{
					// Schlag aus dem Rennen
					if ( _t_hitfrun != zMDL_ANI_ID_ILLEGAL )
						npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKRUN, _t_hitfrun)), npc);
					attacked = TRUE;
				} 
				else if ( Toggled(GAME_UP) )
				{
					attacked = TRUE;
					
					zBOOL	doFinish	= FALSE;
					oCNpc*	other		= npc->GetFocusNpc();
					if ( other && other->IsUnconscious() && (npc->GetWeaponMode() != NPC_WEAPON_FIST) )
					{
						doFinish = ((other->GetModel()->IsAniActive("S_WOUNDED") || other->GetModel()->IsAniActive("S_WOUNDEDB")) /*&& (! weapon->HasDamageType( oEDamageType_Blunt ) )*/ );
					}
					if ( doFinish )
					{
						zSTRING	s			= GetWeaponHitString(npc->GetWeaponMode());
						zTModelAniID ani	= model->GetAniIDFromAniName("T_" + s + "FINISH");
						oCMsgAttack* msg	= zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFINISH,ani));
						msg->target			= npc->GetFocusNpc();
						npc->GetEM()->OnMessage(msg, npc);
					}
					else
					{
						float dist = 0.0f;
						if( npc->IsInDoubleFightRange(other,dist) )
							((zCVob*)npc)->SetHeadingYWorld(other);
						
						zTModelAniID smoveAniID = zMDL_ANI_ID_ILLEGAL;
						if ( Pressed(GAME_SMOVE) && !model->GetIsFlying() )
						{
							zSTRING wps = GetWeaponString(npc->GetWeaponMode());
							smoveAniID = model->GetAniIDFromAniName("T_" + wps + "SPECIALATTACK");
						}
						if ( smoveAniID != zMDL_ANI_ID_ILLEGAL ) 
							// [BENDLIN] 2002-06-18, FIXME: wenn nicht funktional umsetzbar (oNpc/oNpcFight)... raus 
							npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, smoveAniID)), npc);
						else
							npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, _t_hitf)), npc);
					}
				}
				
			} 
			if ( Pressed(GAME_DOWN) && Toggled(GAME_DOWN) ) 
			{
				// Parade
				StopTurnAnis();
				npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_PARADE, npc->GetFocusNpc())), npc);
			} 
			else if ( Toggled(GAME_LEFT) || Toggled(GAME_STRAFELEFT) )  // [BENDLIN] Auch bei STRAFE Drehschlag
			{
				// Drehschlag links
				oCNpc* other = npc->GetFocusNpc();
				float dist = 0.0f;
				if( npc->IsInDoubleFightRange(other,dist) )
					((zCVob*)npc)->SetHeadingYWorld(other);
				npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT, _t_hitl)), npc);
			} 
			else if ( Toggled(GAME_RIGHT) || Toggled(GAME_STRAFERIGHT) )  // [BENDLIN] Auch bei STRAFE Drehschlag
			{
				// Drehschlag rechts
				oCNpc* other = npc->GetFocusNpc();
				float dist = 0.0f;
				if( npc->IsInDoubleFightRange(other,dist) )
					((zCVob*)npc)->SetHeadingYWorld(other);
				npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT, _t_hitr)), npc);
			}
			else if ( !Pressed(GAME_UP) && !Pressed(GAME_LEFT) && !Pressed(GAME_RIGHT) && !Pressed(GAME_DOWN) && !Pressed(GAME_STRAFELEFT) && !Pressed(GAME_STRAFERIGHT) ) // kein Stand durch Blocken+Schlagen
			{
				_Stand();
			}
			return TRUE;
		} 
		else if ( Pressed(GAME_SMOVE) && !model->GetIsFlying() ) 
		{
			// ALT gedrückt (special Moves)
			if ( Pressed(GAME_LEFT) )
			{
				// Strafen links
				oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, npc->GetFocusNpc()));
				msg->ani = _t_strafel;
				npc->GetEM()->OnMessage(msg, npc);					
				return TRUE;
			}
			else if ( Pressed(GAME_RIGHT) )
			{
				// Strafen rechts
				oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, npc->GetFocusNpc()));
				msg->ani = _t_strafer;
				npc->GetEM()->OnMessage(msg, npc);
				return TRUE;
			}
			else if ( Pressed(GAME_DOWN) ) 
			{
				// Jump zurueck
				oCMsgAttack * attack = zNEW(oCMsgAttack(oCMsgAttack::EV_PARADE, npc->GetFocusNpc()));
				attack->reachedTarget = TRUE;
				npc->GetEM()->OnMessage(attack, npc);		
				return TRUE;
			}
		}
		else if ( Pressed(GAME_DOWN) && !Pressed(GAME_LEFT) && !Pressed(GAME_RIGHT) && !Pressed(GAME_UP) ) 
		{
			// Jump zurueck
			oCMsgAttack * attack = zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE, npc->GetFocusNpc()));
			attack->reachedTarget = TRUE;
			npc->GetEM()->OnMessage(attack, npc);		
			return TRUE;
		}
	}
	else
	{
		zCModel *model = npc->GetModel();

		CheckFightCamera();
		
		// [Ulf] : 11.01.01 - entfernt, wird weiter unten eh abgefragt !
		//if(Pressed(key_smove)&&Pressed(key_down))npc->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,npc->GetFocusNpc())),npc);
		//if (!npc->GetFocusVob()) StopTurnAnis();
		npc->TurnToEnemy();

		zBOOL attacked = FALSE;
		
		if (Pressed(GAME_ACTION)) 
		{
			if (IsWalking()) 
			{
				// **********************
				// Schlag aus dem Rennen
				// **********************
				if (_t_hitfrun!=zMDL_ANI_ID_ILLEGAL)
					npc->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKRUN,_t_hitfrun)),npc);
				attacked = TRUE;
			
			} 
			else if (Toggled(GAME_ACTION)) 
			{
				attacked = TRUE;
				
				zBOOL	doFinish	= FALSE;
				oCNpc*	other		= npc->GetFocusNpc();
				if ( other && other->IsUnconscious() && (npc->GetWeaponMode() != NPC_WEAPON_FIST) )
				{
					doFinish = ((other->GetModel()->IsAniActive("S_WOUNDED") || other->GetModel()->IsAniActive("S_WOUNDEDB")) /*&& (! weapon->HasDamageType( oEDamageType_Blunt ) )*/ );
				}
				if ( doFinish )
				{
					zSTRING	s			= GetWeaponHitString(npc->GetWeaponMode());
					zTModelAniID ani	= model->GetAniIDFromAniName("T_" + s + "FINISH");
					oCMsgAttack* msg	= zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFINISH,ani));
					msg->target			= npc->GetFocusNpc();
					npc->GetEM()->OnMessage(msg, npc);
				}
				else
				{
					float dist = 0.0f;
					if( npc->IsInDoubleFightRange(other,dist) )
						((zCVob*)npc)->SetHeadingYWorld(other);
					
					zTModelAniID smoveAniID = zMDL_ANI_ID_ILLEGAL;
					if ( Pressed(GAME_SMOVE) && !model->GetIsFlying() )
					{
						zSTRING wps = GetWeaponString(npc->GetWeaponMode());
						smoveAniID = model->GetAniIDFromAniName("T_" + wps + "SPECIALATTACK");
					}
					if ( smoveAniID != zMDL_ANI_ID_ILLEGAL ) 
						// [BENDLIN] 2002-06-18, FIXME: wenn nicht funktional umsetzbar (oNpc/oNpcFight)... raus 
						npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, smoveAniID)), npc);
					else
						npc->GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, _t_hitf)), npc);
				}
			}
		} 
		
		if ( !attacked && Pressed(GAME_PARADE) && Toggled(GAME_PARADE) ) 
		{
			// **********************
			// Parade
			// **********************
			// Patch 1.07 : [Wohlers] : Drehnung sofort beenden, wenn geblocked werden soll.
			StopTurnAnis();
			npc->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,npc->GetFocusNpc())),npc);	
			return TRUE;
		} 
		else if (Toggled(GAME_ACTIONLEFT) 
			// && npc->GetAnictrl()->IsInCombo()
			) 
		{
			// **********************
			// Drehschlag links
			// **********************
			oCNpc*	other		= npc->GetFocusNpc();
			float dist = 0.0f;
			if(npc->IsInDoubleFightRange(other,dist))((zCVob*)npc)->SetHeadingYWorld(other); // [Moos] 20.12.00 Anpassung an Vob-Änderung
			npc->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT,_t_hitl)),npc);
			return TRUE;
		} 
		else if (Toggled(GAME_ACTIONRIGHT) 
			// && npc->GetAnictrl()->IsInCombo()
			) 
		{
			// **********************
			// Drehschlag rechts
			// **********************
			oCNpc*	other		= npc->GetFocusNpc();
			float dist = 0.0f;
			if(npc->IsInDoubleFightRange(other,dist))((zCVob*)npc)->SetHeadingYWorld(other); // [Moos] 20.12.00 Anpassung an Vob-Änderung
			npc->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT,_t_hitr)),npc);
			return TRUE;
		
		} 
		else if (!Pressed(GAME_ACTION)) 
		{
			//_Stand();
		} 
		
		if (Pressed(GAME_SMOVE) && !model->GetIsFlying() && !attacked) 
		{
			// ******************************
			// ALT gedrückt (special Moves)
			// ******************************
			if (Pressed(GAME_LEFT)) {
				// **********************
				// Strafen links
				// **********************
				oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,npc->GetFocusNpc()));
				msg -> ani			= _t_strafel;
				npc -> GetEM() -> OnMessage(msg,npc);					
				return TRUE;
			
			} else if (Pressed(GAME_RIGHT)) {
				// **********************
				// Strafen rechts
				// **********************
				oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,npc->GetFocusNpc()));
				msg -> ani			= _t_strafer;
				npc -> GetEM() -> OnMessage(msg,npc);					
				return TRUE;
			
	//		} else if (Pressed(key_up)) {
	//			// **********************
	//			// Alternative Hit
	//			// **********************
	//			zSTRING wps = GetWeaponString	(npc->GetWeaponMode());
	//			npc -> GetEM() -> OnMessage		(new oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD,model->GetAniIDFromAniName("T_"+wps+"SPECIALATTACK")),npc);	
			} 
			else if (Pressed(GAME_DOWN)) 
			{
				// **********************
				// Jump zurueck
				// **********************
				oCMsgAttack * attack = zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,npc->GetFocusNpc()));
				attack->reachedTarget = TRUE;
				npc->GetEM()->OnMessage(attack ,npc);		
				return TRUE;
			}
		}
		else if (Pressed(GAME_DOWN) && !attacked ) 
		{
			// **********************
			// Jump zurueck
			// **********************
			oCMsgAttack * attack = zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,npc->GetFocusNpc()));
			attack->reachedTarget = TRUE;
			npc->GetEM()->OnMessage(attack ,npc);		
			return TRUE;
		}

		return attacked;

	};
	return FALSE;
}


zBOOL oCAIHuman :: CheckMobInteraction()
{
	oCMobInter* mob_interact = npc->GetInteractMob();
	if (mob_interact) {

		// Space gedrückt -> Waffe ziehen !
		if (Pressed(GAME_WEAPON)) {
			// Mob Interrupt
			npc		-> Interrupt	();
			GetModel()	-> StartAni		(_s_walk);
			return FALSE;
		}

		zBOOL inMove = npc->GetInMovement();
		if (inMove) npc->EndMovement();

		// passive Wahrnehmung generieren
		CreateAssessUseMob();

		SetCamModeMob(mob_interact);
		if (mob_interact->IsTakeable() && mob_interact->IsInState(npc,0) && Pressed(GAME_ACTION) && Toggled(GAME_DOWN)) {
			// Aufnehmen - Mobinteraction beenden
			// mob_interact -> Interact (npc, TRUE, FALSE, TRUE, FALSE, FALSE);
			mob_interact->StopInteraction(npc);
			// TakeMob
			npc->GetEM()->OnMessage(zNEW( oCMsgManipulate(oCMsgManipulate::EV_TAKEVOB,mob_interact)),mob_interact);
			npc->SetInteractMob(NULL);
			
//			if (inMove) npc->BeginMovement();
			return TRUE;
		}

//		if( !(dynamic_cast<oCMobLadder*>(mob_interact)) )
//			mob_interact -> Interact (npc, Pressed(key_action), Toggled(key_up),Pressed(key_down),Pressed(key_left) || Pressed(GAME_STRAFELEFT),Pressed(key_right) || Pressed(GAME_STRAFERIGHT));
//		else
//			mob_interact -> Interact (npc, Pressed(key_action), Pressed(key_up),Pressed(key_down),Pressed(key_left) || Pressed(GAME_STRAFELEFT),Pressed(key_right) || Pressed(GAME_STRAFERIGHT));
		mob_interact->Interact(npc, Pressed(GAME_ACTION), Pressed(GAME_UP), Pressed(GAME_DOWN), Pressed(GAME_LEFT) || Pressed(GAME_STRAFELEFT), Pressed(GAME_RIGHT) || Pressed(GAME_STRAFERIGHT));
		if (mob_interact->IsInteractingWith(npc)) {			
			if (inMove) npc->BeginMovement();
			return TRUE;
		} else {
			npc->SetInteractMob(NULL);
		}
//		if (inMove) npc->BeginMovement();
	}
	return FALSE;
};		

zBOOL oCAIHuman :: CheckItemInteraction()
{
	// ***************************************
	// Item Interaktion am Laufen tun ??????
	// ***************************************
	if (npc->GetInteractItemCurrentState() != -1) {
		oCItem* item = npc->GetInteractItem();
		if (zinput->GetState(GAME_ACTION)) {
			if (zinput->GetState(GAME_UP)) {
				// Nächster State, wenn möglich
				if (item && npc->InteractItemGetAni(item->GetSchemeName(),npc->GetInteractItemCurrentState(),npc->GetInteractItemCurrentState()+1)) {
					oCMsgManipulate* msg = zNEW( oCMsgManipulate(oCMsgManipulate::EV_USEITEMTOSTATE,item,npc->GetInteractItemCurrentState()+1));
					npc->GetEM()->OnMessage(msg,npc);
					return TRUE;
				}
			} else if (zinput->GetState(GAME_DOWN)) {
				// vorheriger State, wenn möglich
				if (item && npc->InteractItemGetAni(item->GetSchemeName(),npc->GetInteractItemCurrentState(),npc->GetInteractItemCurrentState()-1)) {
					oCMsgManipulate* msg = zNEW( oCMsgManipulate(oCMsgManipulate::EV_USEITEMTOSTATE,item,npc->GetInteractItemCurrentState()-1));
					npc->GetEM()->OnMessage(msg,npc);
					return TRUE;
				}

			} else if (zinput->GetState(GAME_LEFT)) {
				// Was fürn Zustand ? LoopAni Starten, falls vorhanden
				zSTRING aniName = "T_"+item->GetSchemeName()+"_S"+npc->GetInteractItemCurrentState()+"_LOOPL";
				if (GetModel()->GetAniIDFromAniName(aniName)!=zMDL_ANI_ID_ILLEGAL) {
					oCMsgConversation* msg = zNEW( oCMsgConversation(oCMsgConversation::EV_PLAYANI,aniName));
					npc->GetEM()->OnMessage(msg,npc);
					return TRUE;
				};

			} else if (zinput->GetState(GAME_RIGHT)) {
				// Was fürn Zustand ? LoopAni Starten, falls vorhanden
				zSTRING aniName = "T_"+item->GetSchemeName()+"_S"+npc->GetInteractItemCurrentState()+"_LOOPR";
				if (GetModel()->GetAniIDFromAniName(aniName)!=zMDL_ANI_ID_ILLEGAL) {
					oCMsgConversation* msg = zNEW ( oCMsgConversation(oCMsgConversation::EV_PLAYANI,aniName));
					npc->GetEM()->OnMessage(msg,npc);
					return TRUE;
				};
			}
		} 
		// Im Zustand "0" und es gibt keine "1" mehr, dann automatische zurueck
		// [Ulf] : 01.02.01
		if (npc->GetInteractItemCurrentState()==0) {
			if (!npc->InteractItemGetAni(item->GetSchemeName(),npc->GetInteractItemCurrentState(),1)) 
			if (npc->InteractItemGetAni(item->GetSchemeName(),npc->GetInteractItemCurrentState(),-1)) {
				oCMsgManipulate* msg = zNEW( oCMsgManipulate(oCMsgManipulate::EV_USEITEMTOSTATE,item,-1) );
				npc->GetEM()->OnMessage(msg,npc);
				return TRUE;
			}
		}

		// Zurückwandern lassen
		// Auf Normalbetrieb schalten, wenn möglich
		if (!zinput->GetState(GAME_ACTION) && item) {
			int target = -2;
			if (npc->InteractItemGetAni(item->GetSchemeName(),npc->GetInteractItemCurrentState(),-1)) {
				target = -1;
			} else if (npc->InteractItemGetAni(item->GetSchemeName(),npc->GetInteractItemCurrentState(),npc->GetInteractItemCurrentState()-1)) {
				target = npc->GetInteractItemCurrentState() - 1;
			} else {
				// Keine Nachricht verschicken, hat ja eh keinen Sinn
				return TRUE;
			}
			oCMsgManipulate* msg = zNEW( oCMsgManipulate(oCMsgManipulate::EV_USEITEMTOSTATE,item,target) );
			npc->GetEM()->OnMessage(msg,npc);
		}
		return TRUE;		
	}
	return FALSE;
}


zBOOL oCAIHuman :: StandActions()
// a) In stand-mode
// b) GAME_ACTION is pressed
// returns TRUE if an action started -> suppress following TURNS 
{
	oCNpc*		other	= npc->GetFocusNpc();
	oCMobInter*	mobint	= zDYNAMIC_CAST<oCMobInter>(npc->GetFocusVob());
	oCMOB*		mob		= zDYNAMIC_CAST<oCMOB>(npc->GetFocusVob());
	oCItem*		item	= zDYNAMIC_CAST<oCItem>(npc->GetFocusVob());

	// NPCs (focused)
	if ( other )
	{
		// plunder
		if ( other->IsDead() || other->IsUnconscious() )
		{
			npc->OpenDeadNpc();
			return TRUE;
		}
		// steal
		else if ( GetWalkMode() == ANI_WALKMODE_SNEAK )
		{
			//return npc->OpenSteal();
		}
		// talk
		else if ( other->HasPerception(NPC_PERC_ASSESSTALK) && oCNpc::IsInPerceptionRange(NPC_PERC_ASSESSTALK, npc, other) )
		{
			if ( other->CanBeTalkedTo() )
			{
				other->AssessTalk_S(npc);
				return TRUE;
			}
		}
		// call
		else if ( other->HasPerception(NPC_PERC_ASSESSCALL) && oCNpc::IsInPerceptionRange(NPC_PERC_ASSESSCALL, npc, other) )
		{
			return other->AssessCall_S(npc);
		}
	}
	// Interact-mobs (focused)
	else if ( mobint )
	{
		if ( IsStanding() && !zinput->GetState(GAME_WEAPON) && !mobint->IsInteractingWith(npc) && mobint->CanInteractWith(npc) )
		{
			ResetAssessUseMobCounter();
			mobint->GetEM()->OnMessage(zNEW(oCMobMsg)(oCMobMsg::EV_STARTINTERACTION, npc), npc);
			return TRUE;
		}
	}
	// Mobs (focused)
	else if ( mob )
	{
		if ( mob->IsTakeable() )
		{
			npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_TAKEVOB, mob), mob);
			startObserveIntruder = TRUE;
			return TRUE;
		}
	}
	// Items (focused)
	else if ( item ) 
	{
		if ( npc->CanCarry(item) )
		{
			// Check for ItemSlot...
			if (item->GetHomeWorld())
			{
				const zREAL FPBOX_DIMENSION = 50;

				// BBox checken
				zCArray<zCVob*> foundVob;
				zTBBox3D		foundbox;
				foundbox.maxs = foundbox.mins = item->GetPositionWorld();
				foundbox.maxs[0] += FPBOX_DIMENSION;
				foundbox.maxs[1] += FPBOX_DIMENSION * 2;
				foundbox.maxs[2] += FPBOX_DIMENSION;
				foundbox.mins[0] -= FPBOX_DIMENSION;
				foundbox.mins[1] -= FPBOX_DIMENSION * 2;
				foundbox.mins[2] -= FPBOX_DIMENSION;
				item->GetHomeWorld()->CollectVobsInBBox3D(foundVob, foundbox);
				for (int n = 0; n < foundVob.GetNumInList(); n++)
				{
					oCMobItemSlot* slotmob = zDYNAMIC_CAST<oCMobItemSlot>(foundVob[n]);
					if (slotmob)
					{
						if (slotmob->GetInsertedItem() == item)
						{
							// ItemSlot hat das Item!
							if ( IsStanding() && !zinput->GetState(GAME_WEAPON) && !slotmob->IsInteractingWith(npc) && slotmob->CanInteractWith(npc) )
							{
								ResetAssessUseMobCounter();
								slotmob->GetEM()->OnMessage(zNEW(oCMobMsg)(oCMobMsg::EV_STARTINTERACTION, npc), npc);
							}
							return TRUE;
						}
					}
				}
			}
			
			npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_TAKEVOB, item), npc);
			startObserveIntruder = TRUE;
			zCAICamera::GetCurrent()->SubTarget(item);
			return TRUE;
		}
	}
	// Throw ???
	else if ( npc->GetRightHand() )
	{
		zCModel* model = npc->GetModel();
		model->StartAni(t_stand_2_iaim);
		startObserveIntruder = TRUE;
		return FALSE;
	}

	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCAIHuman::PC_CheckSpecialStates
//
//	2002-05-11	[BENDLIN]
//				Aus dem Hängen automatisch in den Stand
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCAIHuman :: PC_CheckSpecialStates()
// Beim PC muss in besonderen Zuständen noch auf Tastendrücke reagiert werden.
// TRUE : Keine weiteren Aktionen erlauben
{
	// ****************************
	// S_JUMP - Landen nach Sprung
	// ****************************
	if (GetModel()->IsAniActive(_s_jump)) {
		// Sprung nach vorne (letzter Loop-Frame)		// Landung einleiten ?
		if ((GetWaterLevel()==2) && (GetFeetY()<=GetWaterY())) {
			// Landung auf Wasser
			StartPhysicsWithVel		();
			GetModel()->StartAni			("T_JUMP_2_FALLDN");
		} else if (GetAboveFloor()<=0) {
			// Landung auf Boden
			if ((Pressed(GAME_UP)) && (!Pressed(GAME_SMOVE)) && (walkmode==ANI_WALKMODE_RUN) && (t_jump_2_runl)) 
				LandAndStartAni (GetModel()->GetAniFromAniID(_t_jump_2_runl));
			else
				LandAndStartAni (GetModel()->GetAniFromAniID(t_jump_2_stand));
		} else {
			// wird gerade losgesprungen ? => Physik anschmeissen
			if (!npc->GetPhysicsEnabled()) {
				npc->SetPhysicsEnabled			(TRUE);
				npc->GetRigidBody()->SetVelocity(GetVelocity()*1.0);  
			};
		};
		return FALSE;
	}
	else if ( GetModel()->IsAniActive(s_hang) )
	{
		// Camera einstellen
		ChangeCamMode(CamModClimb);
		
		// Hängen-bleiben mit DOWN
		// (nur um überhaupt die Möglichkeit zu haben, hängen zu bleiben -- nicht wirklich notwendig)
		if ( Pressed(GAME_DOWN) )
		{
			// Fallen lassen (SMOVE losgelassen beim Hängen)
			if ( !Pressed(GAME_SMOVE) )
			{
				// Kollision vermeiden
				zVEC3 at = npc->GetAtVectorWorld();
				npc->SetPhysicsEnabled(TRUE);
				npc->Move(-at * 10);
				GetModel()->StartAni("T_HANG_2_FALLDN");
				ClearFoundLedge();
				GetVob()->ResetXZRotationsWorld();   // [Moos] 10.1.01 Das an der Kante baumeln ändert jetzt manchmal die Orientierung; mache es hier rückgängig.
			}
		}
		else
		{
			// Hochklettern
			StartAni(t_hang_2_stand, _s_walk);
		}

		return TRUE;
	}
	else if (GetModel()->IsStateActive(s_fallen)) {
		// ***********************
		// s_Fallen
		// ***********************
		// npc->SetPhysicsEnabled	(FALSE);  // [Moos] 21.12.00 Das macht die zCAIPlayer bei gegebenem Anlass schon.
		npc->SetTorchAni		(FALSE);
		if (Pressed(GAME_UP)) {
			GetModel()->StartAni		("T_FALLEN_2_STAND");
			npc->SetCollDet		(TRUE );
		}
		return TRUE;
			
	} else if (GetModel()->IsStateActive(s_fallenb)) {
		// ***********************
		// s_Fallenb
		// ***********************
		// npc->SetPhysicsEnabled	(FALSE);  // [Moos] 21.12.00 Das macht die zCAIPlayer bei gegebenem Anlass schon.
		npc->SetTorchAni		(FALSE);
		if (Pressed(GAME_UP)) {
			GetModel()->StartAni		("T_FALLENB_2_STAND");
			npc->SetCollDet		(TRUE );
		}
		return TRUE;
	
	} else if (GetModel()->IsAniActive("S_WOUNDEDB")) {

		if (Pressed(GAME_UP)) GetModel()->StartAni ("T_WOUNDEDB_2_STAND");
			
	} else if (GetModel()->IsAniActive("S_WOUNDEDB")) {

		if (Pressed(GAME_UP)) GetModel()->StartAni ("T_WOUNDED_2_STAND");
	
	} else
		CheckSpecialStates();

	return FALSE;
}

void oCAIHuman :: PC_Diving()
{
	const zREAL MOUSECLAMP			= 10.0f;
	const zREAL SWIM_TURNVELOCITY	= 0.100f;

	SetCamMode(CamModDive);

	if (Pressed(GAME_SMOVE) || Pressed(GAME_ACTION)) {
		this->SetConfigDoWallSliding(TRUE);
		_Forward();
	} else {
		_Stand();
	}

	zREAL xPos,yPos,zPos;
	zinput->GetMousePos(xPos,yPos,zPos);

	if (Pressed(GAME_UP)) {
		DiveRotateX(SWIM_TURNVELOCITY * (ztimer.GetFrameTimeF()/ztimer.GetMotionFactor()));
	
	} else if (Pressed(GAME_DOWN))	{
		DiveRotateX(SWIM_TURNVELOCITY * (-ztimer.GetFrameTimeF()/ztimer.GetMotionFactor()));
	
	} else if (yPos!=0.0f) {
		zClamp(yPos,-MOUSECLAMP,+MOUSECLAMP); 
		yPos = -yPos / MOUSECLAMP;
		DiveRotateX(SWIM_TURNVELOCITY * (ztimer.GetFrameTimeF()/ztimer.GetMotionFactor()) * yPos * 1.5f);
	}

	PC_Turnings(TRUE);
}

void oCAIHuman :: PC_Turn(zREAL dir, zBOOL playAnis)
{
	Turn(dir,playAnis);
}

zBOOL oCAIHuman :: PC_SpecialMove(zBOOL pressed)
{

	// [BENDLIN] 1.27
	// Keine Spezial-Moves beim Fallen
	if (npc->IsSelfPlayer() && GetModel()->GetIsFlying())
		return FALSE;
	
	static zBOOL oldpressed = FALSE;

	if (!pressed)
	{
		oldpressed = FALSE;
		return FALSE;
	};

#ifndef E3_NOWATERDIVE
	if ( GetActionMode() == ANI_ACTION_SWIM )
	{
		if (!oldpressed )
		{
			GetModel()->StartAni	(t_swim_2_dive);
			SetWalkMode				(ANI_WALKMODE_DIVE);
			SetActionMode			(ANI_ACTION_DIVE);				
		}
		oldpressed = TRUE;
		return TRUE;	
	}
#endif
	oldpressed = TRUE;

	if ( pressed )
	{
		// Springen aus dem Stehen
		do_jump = ( GetModel()->IsAniActive(_s_walkl) || GetModel()->IsAniActive(_s_walk) );
		return do_jump;
	} 

	return FALSE;
}


zBOOL oCAIHuman :: PC_ActionMove(zBOOL pressed)
{
	// [BENDLIN] 1.27
	// Keine Aktionen beim Fallen
	if (npc->IsSelfPlayer() && GetModel()->GetIsFlying())
		return FALSE;

	// NO weapon
	if ( npc->GetWeaponMode() == NPC_WEAPON_NONE )
	{
		// Standing
		if ( IsStanding() )
		{
			oCNpc* other = npc->GetFocusNpc();
			// NPC is waiting for answer?
			if ( other ) if ( other->IsWaitingForAnswer() )
			{
				// talk
				if ( oCNpc::IsInPerceptionRange(NPC_PERC_ASSESSTALK,npc,other) )
				{
					if ( !other->CanBeTalkedTo() ) return TRUE;

					int status = 0;
					if		(pressed)			status = 1;		// JA
					else if (Pressed(GAME_END))	status = -1;	// NEIN
					return other->SetCurrentAnswer(status, pressed, npc);
				}
				// NO talk
				else
				{
					other->SetCurrentAnswer(0, FALSE, npc);
					return other->SetCurrentAnswer(0, TRUE, npc);
				}
			}
			// Standard-actions
			if ( pressed && Toggled(GAME_ACTION) )
			{
				return StandActions();
			}
		}
	}
	// Weapon - Melee
	else if ( npc->GetWeaponMode() <= NPC_WEAPON_2HS )
	{
		return FightMelee();
	}
	// Weapon - Bow
	else if ( npc->GetWeaponMode() <= NPC_WEAPON_CBOW )
	{
		return BowMode(pressed);
	}
	// Weapon - Magic/User
	else
	{
		return MagicMode();
	}

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	oCAIHuman::PC_WeaponMove()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

zBOOL oCAIHuman :: PC_WeaponMove(zBOOL pressed)
{
	if (!pressed)			return FALSE;
	if (npc->GetCarryVob())	return FALSE;
	if ((GetActionMode()==ANI_ACTION_SWIM) || (GetActionMode()==ANI_ACTION_DIVE)) return FALSE;


	// [BENDLIN] 1.27
	// Keine Waffenaktion beim Fallen
	if (npc->IsSelfPlayer() && GetModel()->GetIsFlying())
		return FALSE;

	//changed[dennis]
	if( !npc->IsMonster() )//kein monster
	{
		if (IsStanding()) {
			if (npc->GetWeaponMode()==NPC_WEAPON_NONE) {
				// ****************************
				// Waffe ziehen + auswählen
				// ****************************
				npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON1,wmode_last),npc);
				return TRUE;
			} else {
				// ****************************
				// Waffe wegstecken + auswählen
				// ****************************
				npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON1,wmode_last),npc);
				return TRUE;
			}

		} else if (IsWalking()) {
			if (npc->GetWeaponMode()==NPC_WEAPON_NONE) {
				// ****************************
				// Waffe ziehen aus dem Rennen
				// ****************************
				int fm = npc->GetNextWeaponMode(wmode_last-1,+1);
				if (fm>NPC_WEAPON_NONE) {
					npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON,fm),npc);
					return TRUE;
				}
			} else {
				// ********************************
				// Waffe wegstecken aus dem Rennen
				// ********************************
 				npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON,NPC_WEAPON_NONE),npc);
				return TRUE;
			}
		}
	}
	else//monster
	{
		if( IsStanding() )
		{
			GetModel()->StartAni(t_warn);
			return TRUE;
		}
		else return FALSE;
	}
	return FALSE;
}

zBOOL oCAIHuman :: PC_SlowMove(zBOOL pressed)
{

	// [BENDLIN] 1.27
	// Keine SlowMove-Aktion beim Fallen
	if (npc->IsSelfPlayer() && GetModel()->GetIsFlying())
		return FALSE;
	
//changed [dennis]
	if( CapsLock() )
	{
		if(pressed)ToggleCapsLock();
		else pressed = TRUE;
	}
	if( pressed )
	{
		if( (GetActionMode()==ANI_ACTION_SWIM) && !crawlActive ) 
		{
			if (GetModel()->IsStateActive(s_swim) || GetModel()->IsAniActive(s_swimf)) {
				SetCrawlMode(TRUE);
				return FALSE;
			}
		}
		else if( IsWalking() && (GetWalkMode()==ANI_WALKMODE_RUN) && CanToggleWalkModeTo(ANI_WALKMODE_WALK) )
		{
			ToggleWalkMode();
			return FALSE;
		
		}
		else if( IsWalking() && (GetWalkMode()==ANI_WALKMODE_SNEAK) && CanToggleWalkModeTo(ANI_WALKMODE_RUN) )
		{
			ToggleWalkMode();
			return FALSE;
		
		}
		else if( IsStanding() && (GetWalkMode()==ANI_WALKMODE_SNEAK) && CanToggleWalkModeTo(ANI_WALKMODE_WALK) )
		{
			ToggleWalkMode();
			return FALSE;
		
		}
		else if( IsStanding() )
		{
			// Wenn der Spieler sprintet und eine kleine Anhöhe runterfällt, 
			// kommt er danach bei gedrückter SHIFT-Taste in den Sneak-Mode, 
			// obwohl Shift zwischenzeitlich nicht losgelassen wurde. 
			// Hier sollte sich das Programm besser merken, 
			// was SHIFT vor dem Sturz bewirkt hat.	
			if( sprintActive ) return FALSE;

			if( (GetWalkMode() == ANI_WALKMODE_RUN) && CanToggleWalkModeTo(ANI_WALKMODE_WALK) )
			{
				ToggleWalkMode();
				return TRUE;
			}
		}

	}
	else 
	{
		if( (GetActionMode()==ANI_ACTION_SWIM) && crawlActive) 
		{
			if (GetModel()->IsAniActive(s_swim) || GetModel()->IsAniActive(s_swimf)) { 
				SetCrawlMode(FALSE);
				return FALSE;
			}
		}
		else if( IsWalking() && (GetWalkMode()==ANI_WALKMODE_WALK) && CanToggleWalkModeTo(ANI_WALKMODE_RUN) )
		{
			ToggleWalkMode();
			return FALSE;
		
		}
		else if( IsStanding() && (GetWalkMode() == ANI_WALKMODE_WALK) && CanToggleWalkModeTo(ANI_WALKMODE_RUN) )
		{
			ToggleWalkMode();
			return TRUE;
		}
		else if( !Pressed( GAME_UP ) )
		{
			if (crawlActive) {
				if (GetModel()->IsAniActive(s_swim) || GetModel()->IsAniActive(s_swimf)) {
					SetCrawlMode(FALSE);
					return FALSE;			
				}
			}
		}
	}
	return FALSE;
}

zBOOL oCAIHuman :: PC_Sneak(zBOOL pressed)
{

	// [BENDLIN] 1.27
	// Kein Schleichen beim Fallen
	if (npc->IsSelfPlayer() && GetModel()->GetIsFlying())
		return FALSE;

	if( pressed )
	{
		SetCapsLock(false);
		if( IsWalking() )
		{
			if( (GetWalkMode()==ANI_WALKMODE_SNEAK) && CanToggleWalkModeTo(ANI_WALKMODE_RUN) )
			{
				ToggleWalkMode();
				return TRUE;
			}
			else if( GetWalkMode()==ANI_WALKMODE_RUN && CanToggleWalkModeTo(ANI_WALKMODE_SNEAK) )
			{
				ResetObserveSuspectCounter();
				ToggleWalkMode();
				return TRUE;
			}
			else if( GetWalkMode()==ANI_WALKMODE_WALK && CanToggleWalkModeTo(ANI_WALKMODE_SNEAK) )
			{
				ResetObserveSuspectCounter();
				ToggleWalkMode();
				return TRUE;
			}
		}
		else if( IsStanding() )
		{
			if( (GetWalkMode()==ANI_WALKMODE_SNEAK) && CanToggleWalkModeTo(ANI_WALKMODE_RUN) )
			{
				ToggleWalkMode();
				return TRUE;
			}
			else if( GetWalkMode()==ANI_WALKMODE_RUN && CanToggleWalkModeTo(ANI_WALKMODE_SNEAK) )
			{
				ResetObserveSuspectCounter();
				ToggleWalkMode();
				return TRUE;
			}
			else if (GetWalkMode()==ANI_WALKMODE_WALK && CanToggleWalkModeTo(ANI_WALKMODE_SNEAK) )
			{
				ResetObserveSuspectCounter();
				ToggleWalkMode();
				return TRUE;
			}
		}
	}
	else
	{
	}
	return FALSE;
}

void oCAIHuman :: PC_Turnings( zBOOL forceRotation )
{	
	static zBOOL mouseScaleInitialized = FALSE;
	static zREAL globalMouseScale	   = 2.0f;

	const zREAL MOUSECLAMP = 100.0f;
	const zREAL MOUSESCALE = 10.0f;

	if (ztimer.GetFrameTimeF()==0.0F) return;

	if (!mouseScaleInitialized)
	{
		mouseScaleInitialized = TRUE;
		globalMouseScale      = zoptions->ReadReal("ENGINE","zMouseRotationScale" , globalMouseScale );
	}

    npc->AvoidShrink();

//changed [dennis]
	if( !Pressed(GAME_ACTION) || forceRotation )
	{
		zREAL xPos,yPos,zPos;
		zinput->GetMousePos(xPos,yPos,zPos);
		xPos *= globalMouseScale;

		if( npc->GetWeaponMode()==NPC_WEAPON_NONE )
		{
			zClamp(xPos,-MOUSECLAMP,+MOUSECLAMP);

			if (Pressed(GAME_LEFT))	PC_Turn			(-1,TRUE);					else
 			if (Pressed(GAME_RIGHT))PC_Turn			(+1,TRUE);					else
			if (xPos<0)				PC_Turn			((xPos / MOUSECLAMP) * MOUSESCALE, -xPos > MOUSECLAMP/MOUSESCALE);	else
			if (xPos>0)				PC_Turn			((xPos / MOUSECLAMP) * MOUSESCALE,  xPos > MOUSECLAMP/MOUSESCALE);
			else
			{
				StopTurnAnis();
			}
		}
		else
		{
			zClamp(xPos,-MOUSECLAMP,+MOUSECLAMP);
			
			if (Pressed(GAME_LEFT))	PC_Turn			(-2,TRUE);		else
 			if (Pressed(GAME_RIGHT))PC_Turn			(+2,TRUE);		else
			if (xPos<0)				PC_Turn			((xPos / MOUSECLAMP) * MOUSESCALE, -xPos > MOUSECLAMP/MOUSESCALE);	else
			if (xPos>0)				PC_Turn			((xPos / MOUSECLAMP) * MOUSESCALE,  xPos > MOUSECLAMP/MOUSESCALE);
			else
			{
				StopTurnAnis();
			}
		}
	}
	else StopTurnAnis();
};

zBOOL oCAIHuman::PC_Strafe(zBOOL pressed)
{
	if(GetActionMode()==ANI_ACTION_SWIM) return FALSE;

	// [BENDLIN] 1.27
	if (npc->IsSelfPlayer())
	{
		// Kein Strafen beim Fallen
		if (GetModel()->GetIsFlying())
			return FALSE;
	
		// Kein Strafen beim Kampf wenn GAME_ACTION
		if (Pressed(GAME_ACTION) && (npc->GetWeaponMode() != NPC_WEAPON_NONE))
			return FALSE;
	}

	if (Pressed(GAME_STRAFELEFT)) {
		// **********************
		// Strafen links
		// **********************
		oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,npc->GetFocusNpc()));
		msg -> ani			= _t_strafel;
		npc -> GetEM() -> OnMessage(msg,npc);					
		return TRUE;

	} else if (Pressed(GAME_STRAFERIGHT)) {
		// **********************
		// Strafen rechts
		// **********************
		oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,npc->GetFocusNpc()));
		msg -> ani			= _t_strafer;
		npc -> GetEM() -> OnMessage(msg,npc);					
		return TRUE;
	}
	return FALSE;
}

void oCAIHuman :: _WalkCycle()
{
	zBOOL actionStarted = FALSE;

	if (GetWalkMode()==ANI_WALKMODE_RUN) npc->SetWalkStopChasm(FALSE);

	actionStarted							= PC_ActionMove		(Pressed(GAME_ACTION));
	if (!actionStarted) actionStarted		= PC_SpecialMove	(Pressed(GAME_SMOVE) || ( GetActionMode() == ANI_ACTION_SWIM ? Pressed(GAME_ACTION) : FALSE) );
	// FIXME : Das ist krass ? Geht das besser / anders ?
	// if ( actionStarted && (oCNpc::game_mode!=NPC_GAME_STEAL))	startObserveIntruder= TRUE;
	// PC_SlowMove ist keine relevante Bewegung mehr für den ObserveIntruder -> enthält nur Walkmodi - Wechsel
	// Waffe ziehen, Waffe wegstekcne -> keine relevante Aktion fuer ObserverIntruder
	if (!actionStarted) actionStarted		= PC_WeaponMove		(Pressed(GAME_WEAPON));
	if (!actionStarted) actionStarted		= PC_SlowMove		(Pressed(GAME_SLOW));
	if (!actionStarted) actionStarted		= PC_Sneak			(Toggled(GAME_SNEAK));
	if (!actionStarted) actionStarted		= PC_Strafe			(Pressed(GAME_STRAFELEFT)||Pressed(GAME_STRAFERIGHT));

	if (!actionStarted) {

		// Drehungen 
		PC_Turnings();

		// Bewegung
		if (Pressed(GAME_UP))	{
			// Vorwaerts gehen
			startObserveIntruder = TRUE;
			PC_GoForward ();		
			if( !Pressed(GAME_SMOVE) ) ChangeCamMode(CamModRun);

		} else if (Pressed(GAME_DOWN)) {
			// Rückwaerts gehen
			startObserveIntruder = TRUE;			
			PC_GoBackward ();		
		
		} else {
			// Stehenbleiben
			if (startObserveIntruder && IsStanding()) {
				startObserveIntruder = FALSE;
				if (GetWalkMode()!=ANI_WALKMODE_SNEAK) npc->ObserveIntruder_S ();
			};				

			SetCrawlMode	(FALSE);
			SetSprintMode	(FALSE);
			_Stand();
			ChangeCamMode(CamModNormal);

			// wenn nichts zu tun und nichts im fokus
			// und Kante zum Hochklettern entdeckt -> ANGLOTZEN
			
			// [EDENFELD] Aus Performancegründen auskommentiert
			
			/*if ( !do_jump && !npc->GetFocusNpc() && !npc->GetFocusVob() )
			{
				zPOINT3 ledgePoint;
				if ( npc->IsAPlayer() )
				// [BENDLIN] Addon - nur wenn der Spieler steht neue Kante suchen
				// (sonst fliegt er beim Klettern nach oben)
				if ( IsStanding() )
				if ( DetectClimbUpLedge(ledgePoint, TRUE) && (CanJumpLedge() >= 3) )
				{
					SetLookAtTarget(ledgePoint);
					LookAtTarget();
				}
			}*/
		}
	
	}

	// *** Activate Actions ***
	if (do_jump) {
		PC_JumpForward();
		startObserveIntruder = TRUE;
	}

	// passive Wahrnehmungen erzeugen
	CreateObserveSuspect();
	CreateFootStepSound	();
}

void oCAIHuman :: ResetObserveSuspectCounter()
{
	observeSuspect_Counter = OBSERVESUSPECT_TIME;
};

void oCAIHuman :: CreateObserveSuspect(BOOL first)
{
	// logischen Sound erzeugen
	if ((walkmode == ANI_WALKMODE_SNEAK) && !IsStanding()) {

		observeSuspect_Counter += ztimer.GetFrameTimeF();
		if (observeSuspect_Counter >= OBSERVESUSPECT_TIME) {
			observeSuspect_Counter -= OBSERVESUSPECT_TIME;
			zBOOL inMove = npc->GetInMovement();
			if (inMove) npc->EndMovement();
			npc->CreatePassivePerception(NPC_PERC_OBSERVESUSPECT,npc);
			if (inMove) npc->BeginMovement();
		}
	}
}

void oCAIHuman :: CreateFootStepSound(zBOOL first)
{
	static const	zREAL STEPSOUND_TIME	= 1 * 1000;		// Alle halbe Sekunde erzeugen
	static			zREAL stepsound_counter	= 0.0;
	// logischen Sound erzeugen
	if ((walkmode!=ANI_WALKMODE_SNEAK) && IsWalking()) {
		if (first) {
			// First = auf jeden Fall Sound starten
			stepsound_counter = 0;
		
		} else {
			stepsound_counter += ztimer.GetFrameTimeF();
			if (stepsound_counter >= STEPSOUND_TIME) {
				stepsound_counter -= STEPSOUND_TIME;
				zBOOL inMove = npc->GetInMovement();
				if (inMove) npc->EndMovement();
				npc->AssessQuietSound_S(npc,npc->GetPositionWorld());
				if (inMove) npc->BeginMovement();
			}
		}
	}
}

void oCAIHuman :: ResetAssessUseMobCounter()
{
	assessUseMob_counter = ASSESSUSEMOB_TIME; 
};

void oCAIHuman :: CreateAssessUseMob()
{
	oCMobInter* mob = npc->GetInteractMob();
	if (mob) {
		assessUseMob_counter += ztimer.GetFrameTimeF();
		if (assessUseMob_counter >= ASSESSUSEMOB_TIME) {
			assessUseMob_counter -= ASSESSUSEMOB_TIME;
			zBOOL inMove = npc->GetInMovement();
			if (inMove) npc->EndMovement();
			npc->AssessUseMob_S(mob);
			if (inMove) npc->BeginMovement();
		}
	}
}

/* ----------------------------------------------------------------------
	
    oCAIHuman :: SetCrawlMode()	

	10.11.2000	[Moos]	
                Overlay laden hierher verlegt


   ---------------------------------------------------------------------- */

void oCAIHuman :: SetCrawlMode(zBOOL on)
{
	if (!npc) return;
	if (npc->GetTrueGuild()>NPC_GIL_HUMANS || on == crawlActive) return;

	if (!s_crawlOverlay)
        s_crawlOverlay = zCModelPrototype::Load ("HUMANS_SWIM.MDS",GetModel()->GetModelProto());

	if (!s_crawlOverlay) return;

	if (on && !crawlActive) {
		zBOOL walking = GetModel()->IsAniActive(s_swimf);
		npc->GetModel()->ApplyModelProtoOverlay(s_crawlOverlay);	
		crawlActive = TRUE;
		InitAnimations();
		if (walking)	GetModel()->StartAni(s_swimf);
		else			GetModel()->StartAni(s_swim);
		SetWalkMode		(ANI_WALKMODE_SWIM);
		SetActionMode	(ANI_ACTION_SWIM);

	} else if (!on && crawlActive) {
		zBOOL state	  = GetActionMode();
		zBOOL walking = GetModel()->IsAniActive(s_swimf);
		npc->GetModel()->RemoveModelProtoOverlay(s_crawlOverlay);
		crawlActive = FALSE;
		InitAnimations();
		if (state==ANI_ACTION_SWIM) {
			SetWalkMode		(ANI_WALKMODE_SWIM);
			SetActionMode	(ANI_ACTION_SWIM);
			if (walking)	GetModel()->StartAni(s_swimf);
			else			GetModel()->StartAni(s_swim);
		}
	}
}

/* ----------------------------------------------------------------------
	
    oCAIHuman :: SetSprintMode()	

	10.11.2000	[Moos]	
                Overlay laden hierher verlegt


   ---------------------------------------------------------------------- */

void oCAIHuman :: SetSprintMode(zBOOL on)
{
	if (!npc) return;
	if (npc->GetTrueGuild()>NPC_GIL_HUMANS || on == sprintActive) return;

	if (!s_sprintOverlay)
	    s_sprintOverlay = zCModelPrototype::Load ("HUMANS_SPRINT.MDS",GetModel()->GetModelProto());	

	if (!s_sprintOverlay) return;

	if (on && !sprintActive) {
		zBOOL walking = IsWalking();
		npc->GetModel()->ApplyModelProtoOverlay(s_sprintOverlay);	
		sprintActive = TRUE;
		InitAnimations();
		if (walking) GetModel()->StartAni(_s_walkl);
		SetNextAni (_t_walk_2_walkl, _s_walkl);

	} else if (!on && sprintActive) {
		zBOOL walking = IsWalking();
		npc->GetModel()->RemoveModelProtoOverlay(s_sprintOverlay);
		sprintActive = FALSE;
		InitAnimations();
		if (GetWaterLevel()==2)	{
			GetModel()->StartAni(s_swim);
		} else {
			if (walking)	GetModel()->StartAni(_s_walkl);
			else			GetModel()->StartAni(_s_walk);
			SetNextAni (_t_walkl_2_walk, _s_walk);
		}
	}
}

// [EDENFELD] Für die Firstperson Camera noch die KEY_PAD_DEL Taste hinzugefügt
// [EDENFELD] Für die Zurückschau Camera Code hinzugefügt
zBOOL oCAIHuman :: MoveCamera()
{	
	return FALSE;
}

void oCAIHuman :: CamMessages()
{

	return; 
}

//*********************************************************************************
//**																  CheckFocusVob
//*********************************************************************************
//**	18.12.00	(RK)	Simplified
//********************************************************************************* 

void oCAIHuman :: CheckFocusVob(const zBOOL a_bForce)
{
	//
	//	DO NOT CHANGE TO FOCUS AS LONG AS WE ARE IN STEAL OR PLUNDER MODE
	//
	if ( oCNpc::game_mode == NPC_GAME_PLUNDER || oCNpc::game_mode == NPC_GAME_STEAL ) return;

	// FIXME : wirklich jeden Frame nötig 
	if (!Pressed(GAME_LOOK)) npc->GetAnictrl()->StopLookAtTarget();

	//
	//	ACTION
	//
	zBOOL		bAction		= ::zinput->GetState	( GAME_ACTION );
	zBOOL		bLeft		= ::zinput->GetState	( GAME_LEFT	  ) || ::zinput->GetState	( GAME_STRAFELEFT	);
	zBOOL		bRight		= ::zinput->GetState	( GAME_RIGHT  ) || ::zinput->GetState	( GAME_STRAFERIGHT  );// ? ::zinput->GetToggled	( GAME_RIGHT  ) : FALSE;

	if (!oCGame::GetUseOldControls())
	{
		bLeft  |= (zBOOL)::zinput->GetState	( GAME_ACTIONLEFT  );
		bRight |= (zBOOL)::zinput->GetState	( GAME_ACTIONRIGHT );
	};

	zCVob*		pVobFocus	= this->npc->GetFocusVob();
	oCNpc*		pNpcFocus	= this->npc->GetFocusNpc();

	zBOOL		bFocusDead	= ( pNpcFocus ) ? pNpcFocus->IsDead	() || pNpcFocus->IsUnconscious() : FALSE;

	if ( bAction )
	{
		switch( npc->GetWeaponMode() )
		{
			//
			//	MELEE WEAPON 
			//
			case NPC_WEAPON_FIST	:  
			case NPC_WEAPON_DAG		:  
			case NPC_WEAPON_1HS		:  
			case NPC_WEAPON_2HS		:	break;

			//
			//	ENABLE FOCUS TOGGLE <CTRL>+<LEFT/RIGHT>
			//
			case NPC_WEAPON_BOW		:  
			case NPC_WEAPON_CBOW	:  
			case NPC_WEAPON_MAG		:  
			case NPC_WEAPON_NONE	:  {
											//	GET NEXT FOCUS VOB
											if		( bLeft  )	npc->ToggleFocusVob( TRUE  ); 
											else if ( bRight )	npc->ToggleFocusVob( FALSE ); 
											else	break;

											//	UPDATE FOCUS VOB
											pVobFocus = this->npc->GetFocusVob();
											pVobFocus = this->npc->GetFocusNpc();

											bFocusDead	= ( pNpcFocus ) ? pNpcFocus->IsDead() : FALSE;
											
											//	LOOK AT NEW FOCUS VOB
											this->SetLookAtTarget( pVobFocus );

											return;
										}
										break;
		}

		//
		//	FOCUS ALREADY VALID?
		//
		if ( pVobFocus )
		{
			//
			//	FOCUSING A LIVING(!) NPC OR NO NPC AT ALL?
			//
			if ( (!pNpcFocus) || ( pNpcFocus && (!bFocusDead) ) )
			{
				//
				//	NO NEED TO RECOLLECT THE FOCUS
				//
				return;
			}
		}
	}

	//
	//	UPDATE FOCUS VOB 
	//
	npc->CollectFocusVob(a_bForce);

	//
	//	CHECK ENEMY FOR VALIDITY
	//
	if ( npc && npc->GetEnemy()	 )
	{
		if ( npc->GetEnemy()->IsDead() )
		{		
			 npc->SetEnemy( NULL );
		}
	}

}


void oCAIHuman :: Moving ()
{	
	// Dennis : Hier alles fürn Fokus-Vob rein (Ermittlung + Steuerung)

	CheckFocusVob();
	
	// *****************
	// Item Interaktion
	// *****************
	// Muss vor MovLock, weil ItemInteraktion auch passiert, waehrend Inv offen ist.
	CheckItemInteraction();

    // MoveLock
    zBOOL moveAllowed				= zCAICamera::GetCurrent() ? zCAICamera::GetCurrent()->GetPlayerIsMovable() : TRUE;
	zBOOL globalCutsceneRunnning	= npc->GetHomeWorld() && (npc->GetHomeWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene()!=0);

    if (npc->IsMovLock()				 || 
		globalCutsceneRunnning			 || 
		npc->state.CanPlayerUseAIState() || 
		!moveAllowed ) 
	{		
		// zERR_MESSAGE(8,0,"B: NPC: Player Locked: "+zSTRING(npc->IsMovLock())+" "+zSTRING(npc->state.CanPlayerUseAIState())+" "+zSTRING(!moveAllowed));
        _Stand();
        return;
    }

	// Sliding ? Dann raus
	if (IsSliding()) return;
	
	// ****************
	// Camera 
	// ****************
	if (!aiCam) aiCam = ogame -> GetCameraAI();
	//CamMessages();
	if (lookedAround) return;

	// **********************************
	// Mob Interaction
	// **********************************
	if (CheckMobInteraction()) return;
	
	// ****************
	// Special States 
	// ****************
	if (PC_CheckSpecialStates()) return;

	// ****************
	// Moving
	// ****************
	
	switch (GetActionMode()) {
		case ANI_ACTION_DIVE			:	PC_Diving	();			break;
		case ANI_ACTION_CHOOSEWEAPON	:	WeaponChoose();			break;
		default							:	_WalkCycle	();			break;
	}
}

void oCAIHuman :: DoAI (zCVob *vob, zBOOL &vobDeleted)
{
	vobDeleted = FALSE;

#ifdef GOLDMASTER
	if (ztimer.GetFrameTimeF() == 0.0f) return;
#endif

#ifdef TEST_LEAKS
	if (ztimer.GetFrameTimeF() == 0.0f) return;
#endif

    npc->AvoidShrink();   //        Verhindere, dass sich das Model abbaut (bzw. erzeuge ein neues)

    zERR_ASSERT_STRICT(GetRefCtr() > 0);

	zCModel  *model  = npc->GetModel();


	if (showai) {
		npc			-> ShowState			(0,1600);
		npc->GetEM()-> ShowList				(0,2100);
		model		-> PrintStatus			(0,6000);
		model		-> ShowAniList			(6200);
	}


	if (npc == oCNpc::player) ChangeCamModeBySituation();

	// Tot ? 
	if (IsDead()) 
	{
        // [Moos] Tote surfacealign kronkelei...
        zTSurfaceAlignMode sa=GetConfigDoSurfaceAlign();
        SetConfigDoSurfaceAlign(zMV_SURFACE_ALIGN_NORMAL);

        Begin(npc);
        End();

        SetConfigDoSurfaceAlign(sa);

		// mach mal Inv zu
		if ( npc->IsSelfPlayer() ) 
		{
			if (npc->inventory2.IsActive()) npc->inventory2.Deactivate();
		}


		// Auch tote bei Verlassen entfernen
		ogame->GetSpawnManager()->CheckRemoveNpc(npc);
		return;
	}


	// standard face anis für npcs (publisher demo)
	if (npc && npc->IsConditionValid() && npc->GetBodyState()!=BS_LIE)
	{
		// Search HeadNode
		if (npc->GetModel() && !eyeBlinkActivated) 
		{
			zCModelNodeInst* head = npc->GetModel()->SearchNode(zMDL_NODE_NAME_HEAD);
			if (head) 
			{
				// Getting the Visual
				zCMorphMesh* vis = zDYNAMIC_CAST<zCMorphMesh> (head->GetNodeVisual());
				if (vis) 
				{
					vis->AddRandAni (vis->SearchAni("R_EYESBLINK"), 0.15F, 0.1F, 3.8F, 1.0F, 0.2F);
					eyeBlinkActivated = TRUE;
				}
			}
		}
	}
	else 
	{
		// Search HeadNode
		if (npc->GetModel() && eyeBlinkActivated) 
		{
			zCModelNodeInst* head = npc->GetModel()->SearchNode(zMDL_NODE_NAME_HEAD);
			if (head) {
				// Getting the Visual
				zCMorphMesh* vis = zDYNAMIC_CAST<zCMorphMesh> (head->GetNodeVisual());
				if (vis) 
				{
					zCMorphMeshAni *ani = vis->SearchAni("R_EYESBLINK");
					vis->RemoveRandAni(ani);
					eyeBlinkActivated = FALSE;
				}
			}
		}
	}
	// [EDENFELD] 1.17 Standard Faci Anis enabled
	/*if (npc->GetFocusNpc())
	{
		npc->StartStdFaceAni(npc->GetAttitude(npc->GetFocusNpc()));
	}
	else
	{
		npc->StartStdFaceAni(NPC_ATT_NEUTRAL);
	}*/

	// Erstmal kein AutoRoll annehmen....
	autoRollDirection = 0.0f;

	// ***********************************************************
	// Abregen :: Normal / Angry / Furious
	// ***********************************************************
	npc->CheckAngryTime();

	// ***********************************************************
	// MAIN - AI
	// ***********************************************************

 	// FIXME : Ist das noch nötig
	CorrectAniStates();

	
	if (oCNpc::GetBaseAIEnabled()){
        StartUp(npc);
    }


	if (npc && npc->IsSelfPlayer() && npc->inventory2.IsOpen() )
	{
		// BUGFIX: manchmal turnte der SC bei offenem INV rum
		this->StopTurnAnis();
		// wenn das inventory auf ist, aber kein movlock an ist, ist irgendwas schief gelaufen, und wird korrigiert
		if (!npc->inventory2.IsPassive() && !npc->IsMovLock())
		{
			npc->SetMovLock(TRUE);
			npc->inventory2.SetHandleEventTop();
		}
	}


	// *********************************************************************
	// Wasserstandsprüfung
	// *********************************************************************
	if (GetActionMode()!=ANI_ACTION_CHOOSEWEAPON) CheckWaterLevel();

	// **** Besondere States checken ***
	CheckSpecialStates	();
	
	npc->state.DoAIState();

	if (npc == oCNpc::player) 
	{
		// highlight fx hier starten/beenden
		if ((npc->GetWeaponMode() < NPC_WEAPON_DAG) || (npc->GetWeaponMode() > NPC_WEAPON_MAG) || (npc->IsUnconscious()) || (npc->IsDead()))
		{
			oCNpcFocus::StopHighlightningFX();
		}
		else
		{
			// focus highlighting aktivieren, falls gewünscht (hallo jowood)
			if ( Pressed(GAME_ACTION) || (!oCGame::GetUseOldControls()) )
			{
				if (npc->GetFocusNpc() && (oCNpcFocus::GetHighlightMeleeFocus()))
				{
					oCNpcFocus::StartHighlightningFX(npc->GetFocusNpc());
				}
				else
				{
					oCNpcFocus::StopHighlightningFX();
				};
			}
			else
			{
				oCNpcFocus::StopHighlightningFX();
			};
		}
	}

	if (!npc->IsDead() && !npc->GetNpcAIDisabled()) 
	{
		DoHackSpecials();
		// Player Actions
		if (npc == oCNpc::player) 
		{
			npc -> CheckSpecialSituations();
			// Bewegung / Tastenabfragen
			if (npc->GetEM()->IsEmpty(TRUE)) 
			{
				// keine animation läuft
				Moving();
			}
			else
			{
				// im nahkampf zusätzliche checks für den spieler, auch wenn animationen gespielt werden
				// eine animation oder ein anderes event ist aktiv
				// checken, ob hitani-kombofenster aktiv, und wenn ja, dann
				// zum aktuellen enemy rotieren
				if ((npc->GetWeaponMode() >= NPC_WEAPON_DAG) && (npc->GetWeaponMode() <= NPC_WEAPON_2HS))
				{
					if ( npc->GetEnemy() && (npc->GetEnemy()->IsUnconscious() || (npc->GetEnemy()->IsDead())) )
					{
						CheckFocusVob(TRUE);
						SetComboHitTarget(npc->GetEnemy());
					}
					else if (!npc->GetEnemy())
					{
						CheckFocusVob(TRUE);
						SetComboHitTarget(npc->GetEnemy());
					};
					
					if (npc->GetAnictrl())
					{
						if (!oCGame::GetUseOldControls() && 
							!zinput->GetMouseIdle()		 && 
							(npc->GetAnictrl()->IsInCombo() || npc->GetAnictrl()->IsInPostHit() || npc->GetAnictrl()->IsInPreHit()) )
						{
							CheckFocusVob	();
							npc->TurnToEnemy();
						};

						if (npc->GetAnictrl()->IsDefending())
						{
							CheckFocusVob	();
							npc->TurnToEnemy();
						}
						else if (npc->GetAnictrl()->IsInCombo())
						{
							// im zeitfenster, rotiere
							// ab 1.20 soll in den Combo-Zeitfenstern nicht mehr zum nächsten Target rotiert werden -> wieder das alte Gothic 1 Kampfsystem
							if (!oCGame::GetUseOldControls() && !zinput->GetMouseIdle())
							{
								CheckFocusVob();							
								SetComboHitTarget(npc->GetEnemy());
							}
							npc->TurnToEnemy();
						}
					}
				}
			}
		} 
		else 
		{
			// NSC - Special
			DoSimpleAI				();
			// Keine Wahrnehmungen bei einer Cutscene
			if (!npc->GetEM()->GetCutsceneMode()) npc -> PerceptionCheck	();
			// Safety : Falls EM leer und noch am gehen, stoppen !!!
			// FIXME : Kampf, Verfolgung....
			// if (npc->GetEM()->IsEmpty(TRUE) && IsWalking()) _Stand();
		
		}
		// Add Offset to Fight-Anis
		DoAniWithOffset		();
	}

	if (oCNpc::GetBaseAIEnabled()) End();

	// *********************************************************************
	// Hingucken
	// *********************************************************************
	
	LookAtTarget();
	DoAutoRoll	();

	// *********************************************************************
	// Effekte
	// *********************************************************************

	// Zauberkranzauswahl
	npc -> DoSpellBook();
	// Am NSCs haengende Objecte positionieren
	npc -> UpdateSlots();

	// Specialeffekte von Monster abhaengig abspielen
	DoMonsterSpecial();

	// *********************************************************************
	// Blutomat anschmeissen
	// *********************************************************************
	
	if ( oCNpc::GetBloodMode() >= oCNpc::oEBloodMode_Trails )
	{
		zREAL bleedValue = 1 - (npc->GetAttribute(NPC_ATR_HITPOINTS) / (npc->GetAttribute(NPC_ATR_HITPOINTSMAX)*0.50));
		if (bleedValue<0.0f) bleedValue = 0.0f;
		SetBleeding(bleedValue);
	}
	else		 
	{		
		SetBleeding(0);	
	}

	// *********************************************************************
	// Regeneration
	// *********************************************************************
	npc -> ProcessNpc();

	// ***********************************************************
	// Laufende Spells updaten
	// ***********************************************************	
	if (npc->IsSelfPlayer()) CheckActiveSpells();
	zBOOL vobDel = npc -> DoActiveSpells ();

	// ***********************************************************
	// Entfernungs - Check zum Player  
	// FIXME : auch nur jede Sekunde ?
	// ***********************************************************	
	if (ogame->GetSpawnManager()->CheckRemoveNpc(npc)) return;

    if (npc->GetInMovement()) npc->TouchMovement(); // [Moos] wir haben uns zumindest logisch IMMER bewegt. Garantiert, dass die Kollisionserkennung ausgeführt wird.

	// Delete-Status
	vobDeleted	= vobDel;
}

void oCAIHuman::DoHackSpecials()
{
	if (npc == oCNpc::player) 
	{

		// hier mal einige seltene bugs abfangen
		// 1. Pfeil klebt machmal am NSC - Versuch
		// 2. Fackel hängt blöd am Spieler
		// 3. was noch ?

		if (!npc->globalVobTreeNode) return;

		zCTree<zCVob> *child = npc->globalVobTreeNode->GetFirstChild(); 
		while (child) 
		{
			zCVob *vob = zDYNAMIC_CAST<zCVob>(child->GetData());

			if (vob)
			{
				zBOOL removeIt	   = FALSE;
				removeIt |= zDYNAMIC_CAST<oCAIArrowBase>(vob->GetAI()) != NULL;							// pfeil entfernen, ungetestet
				removeIt |= (vob->GetObjectName() == "TORCH_BURN") && (npc) && (!npc->HasTorch());		// fackel tree entfernen, funzt!

				if (removeIt)
				{
					vob->SetDontWriteIntoArchive	(TRUE);				// damit die leaks sich nicht in savegames ausbreiten
					vob->RemoveVobSubtreeFromWorld	();
					//vob->ReleaseVobSubtree		(child);			// Hier Crash!!!
				}
			}
			child = child->GetNextChild();
		};

		// ani freezer für den spieler entfernen, jeden frame (ist schnell genug)
		//if ((npc->GetHomeWorld()->GetMasterFrameCtr())==0)
		{
			zCModel *model = npc->GetModel();
			if (model)
			{
				if (model->CorrectAniFreezer())
				{
					zERR_WARNING("C: corrected ani freezer for player! pos: X: " + zSTRING(npc->GetPositionWorld()[VX]) + zSTRING(", Y: ") + zSTRING(npc->GetPositionWorld()[VY]) + zSTRING(", Z:") + zSTRING(npc->GetPositionWorld()[VZ]));
				};
			};
		};

		// [EDENFELD] [ADDON] Wieder drin: Hack, der Sprungfreezer durch Ausschalten der Physik im Collisionmodul
		// unterbindet
		if (npc->GetModel()->IsStateActive(s_falldn) && !npc->GetPhysicsEnabled()) 
		{
			npc->SetPhysicsEnabled(TRUE);
		};

	}
	else
	{
		// ani freezer für nscs entfernen (weniger häufig)
		// evtl. auch jeden frame ausführen -> analyze
		if ((npc->GetHomeWorld()->GetMasterFrameCtr()%5)==0)
		{
			zCModel *model = npc->GetModel();
			if (model)
			{
				if (model->CorrectAniFreezer())
				{
					zERR_WARNING("C: corrected ani freezer for npc: " + npc->GetName() + ", pos: X: " + zSTRING(npc->GetPositionWorld()[VX]) + zSTRING(", Y: ") + zSTRING(npc->GetPositionWorld()[VY]) + zSTRING(", Z:") + zSTRING(npc->GetPositionWorld()[VZ]));
				};
			};
		};
	};

};


// 1.20: new main trigger class for all game camera modes which should 
// be a lot safer and more tuneable
/*

// key driven
CamModLook;
CamModLookBack;
CamModFirstPerson;

// state driven
CamModMobXXX
CamModDeath;
CamModSwim;
CamModDive;
CamModJumpUp;
CamModClimb;
CamModInventory;
CamModMelee;
CamModMagic;
CamModRanged;


// special case modes
CamModDialog;
CamModNormal;
CamModThrow;


// neue modes (ideen!)
CamModFall
CamModFocus		(sc steht und starrt länger auf ein objekt. welche objekte ?
CamModLookDown	(sc steht und hat einen abgrund vor sich)

  TODO:
  - kein camera mode change während waffenwechsel
  - FOV Morph bei DMT Effect

*/
void oCAIHuman ::ChangeCamModeBySituation()
{
	zCAICamera* cam = zCAICamera::GetCurrent();

	if (!cam) 
	{
		zERR_WARNING("C: no camera ai present");
		return;
	}

	if (ztimer.GetFrameTimeF()==0) return;		// keine Wechsel wenn das game pausiert

	// **** erst mal die sonderfälle abarbeiten ****
	
	// keine camera wechsel während eines dialoges
	if (cam->GetMode()==CamModDialog) 
	{
		if (cam->GetPreviousMode()==CamModFirstPerson) thirdPersonFallback = TRUE;

		return;

		// TODO: Dialog Cam bleibt stecken Bug hier umgehen.
		// funzt so noch nicht!

		/*if (cam->GetTargetList().GetNum()>0) 
		{
			oCNpc *npc = zDYNAMIC_CAST<oCNpc>(cam->GetTargetList()[0]);

			if (npc->GetTalkingWith()) 
			{
				// Einer der beiden muss im ZS_Talk sein.
				int index = parser.GetIndex("ZS_TALK");
				if (npc->state.IsInState(index) || npc->GetTalkingWith()->state.IsInState(index))
				{
					// alles ok, camera darf nicht wechseln.
					return;
				}
			}
			
		};*/
	};

	// portal hint an die camera
	
	zCSkyControler_Outdoor *sky = zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler());
	zBOOL camIsInSector			= sky && sky->GetCameraInsideSector();
	oCPortalRoomManager* rooms	= ogame->GetPortalRoomManager();
	cam->SetHintTargetInPortalRoom( rooms && rooms->IsPlayerInRoom() || camIsInSector );

	// kein camera wechsel während waffe ziehen
	// kein camera wechsel während magiekranz rotation

	// ermitteln, ob firstperson erlaubt ist
	zBOOL firstPersonAllowed = TRUE;

	{
		// cache ini reading
		static zBOOL zDontSwitchToThirdPerson = zBOOL(-2);
		if (zDontSwitchToThirdPerson == zBOOL(-2))
			zDontSwitchToThirdPerson = zoptions->ReadBool("ENGINE", "zDontSwitchToThirdPerson", FALSE);

		if (!zDontSwitchToThirdPerson) 
		if ((npc->GetWeaponMode()!=NPC_WEAPON_NONE && !npc->IsMonster())	||					// 1. kampf ? 
			 npc->GetInteractMob()											||					// 2. mobinteraktion ?
			 npc->HasTorch()												||					// 3. Fackel in Hand ?
			 this->IsDead()													||					// 4. tot
			 npc->IsUnconscious()											||					// 5. bewusstlos
			 (Pressed(GAME_LOOK) && Pressed(GAME_UP))						||					// 6. Rückspiegel   					
			 npc->GetBodyState()==BS_SWIM || npc->GetBodyState()==BS_DIVE)						// 7. tauchen & schwimmen (probs wegen fft polys)
		{
			firstPersonAllowed = FALSE;
		}
	}

	// firstperson aktiv ?
	if (cam->GetMode()==CamModFirstPerson)
	{
		thirdPersonFallback = FALSE;
		// hier darf nur reagiert werden, wenn die 1st person camera nicht sowieso abgeschaltet werden soll
		if ( !(Toggled(GAME_LOOK_FP) && Pressed(GAME_LOOK_FP)) )	
		{
			// illegaler pc state -> 3rd person erzwingen
			thirdPersonFallback	 = !firstPersonAllowed;

			if (!thirdPersonFallback) return;
		}
	}
	else if (thirdPersonFallback)
	{
		// nein, aber:
		// bisher war die thirdperson camera erzwungen
		// nun testen wir, ob wir wieder zur 1st person cam zurückschalten müssen
		if ( firstPersonAllowed )
		{
			thirdPersonFallback = FALSE;
			lookedAround		= FALSE;			// muss, sonst kann es vorkommen, das der sc noch weiterläuft
			cam->SetMode(CamModFirstPerson);
			return;
		}
	}

	// *** key driven modes ***
	// 1. umschau kamera / rückspiegel
	if ( Pressed(GAME_LOOK) ) 
	{
		if (this->IsStanding())			
		{
			// umschaukamera im stehen
			this->StopTurnAnis();

			cam->SetMode(CamModLook);

			zREAL cx = 0.5f ,cy = 0.5f;

			GetModel() -> SetRandAnisEnabled (FALSE);	

			if (Pressed(GAME_LEFT))		cx = 0.0f;
			if (Pressed(GAME_RIGHT))	cx = 1.0f;
			if (Pressed(GAME_DOWN))		cy = 1.0f;
			if (Pressed(GAME_UP))		cy = 0.0f;
			
			SetLookAtTarget (cx,cy);
			
			lookedAround = TRUE;
		}
		else if (!lookedAround)
		{
			// rückspiegel während des laufens
			cam->SetMode(CamModLookBack);
			lookedAround = TRUE;
		}
		return;
	}
	else if (lookedAround) 
	{
		StopLookAtTarget();
		lookedAround = FALSE;		
	}

	// 2. first person
	if (ogame && !ogame->IsPaused() && !ogame->IsInLoadSaveGame() && !ogame->IsInScriptStartup()) // game running?
	if (zinput->GetToggled(GAME_LOOK_FP) && firstPersonAllowed)
	{
		// firstperson einschalten, wenn noch nicht aktiv
		if (cam->GetMode()!=CamModFirstPerson)
		{
			cam->SetMode(CamModFirstPerson);
			// muss nix mehr getan werden -> raus hier
			return;
		}				
	}

	// *** state driven camera modes

	// 1. tot / bewusstlos
	if (this->IsDead() || npc->IsUnconscious())
	{
		cam->SetMode(CamModDeath);
		return;
	}


	// 2. mob interaction cam
	oCMobInter* mob_interact = npc->GetInteractMob();

	if (mob_interact && !Pressed(GAME_WEAPON)) 
	{
		zSTRING mode = zSTRING("CAMMODMOB") + mob_interact->GetScemeName();

		// gibt es einen mode mit einem passenden scheme namen, so wird dieser genommen, ansonsten der default mob mode
		if (cam->IsModeAvailable(mode)) cam->SetMode(mode);
		else							cam->SetMode(zSTRING("CAMMODMOBDEFAULT"));

		return;
	}

	// 3. am tauchen 
	if (npc->GetBodyState()==BS_DIVE)
	{
		cam->SetMode(CamModDive);
		return;
	};

	
	// 4. am schwimmen ?
	if (GetWaterLevel()>1)
	{
		cam->SetMode(CamModSwim);
		return;
	}

	// 5. cammodjumpup noch drin ? welches interface ?
	/*
	*/

	// 6. CamModClimb (noch drin ?)
	if (GetModel()->IsAniActive(s_hang))
	{
		cam->SetMode(CamModClimb);
		return;
	}

	// 7. CamModFall (noch drin ?)
	if (GetModel()->IsAniActive(s_fall) || GetModel()->IsAniActive(s_fallb))
	{
		cam->SetMode(CamModFall);
		return;
	}


	// 8. inventory/tradescreen offen ? dann mal die inventory kamera an
	if (npc->inventory2.IsOpen())
	{
		cam->SetMode(CamModInventory);
		return;
	}

	// 9. magie gezogen ?
	if (npc->GetWeaponMode() == NPC_WEAPON_MAG)
	{
		cam->SetMode(CamModMagic);
		return;
	}

	// 10. fernkampfwaffe gezogen ?
	if (npc->GetWeaponMode() == NPC_WEAPON_BOW || npc->GetWeaponMode() == NPC_WEAPON_CBOW)
	{
		cam->SetMode(CamModRanged);
		return;
	}

	// 11. nahkampfwaffe gezogen
	if (npc->GetWeaponMode() >= NPC_WEAPON_FIST && npc->GetWeaponMode() <= NPC_WEAPON_2HS)
	{
		cam->SetMode(CamModMelee);
		return;
	}

	// *** sonderfälle ***
	// CamModDialog
	// *** CamModThrow;

	// noch nix gefunden ? dann schmeiss die normale camera an!
	cam->SetMode(CamModNormal);

}

void oCAIHuman :: DoMonsterSpecial()
{
}


void oCAIHuman :: SetShowAI(BOOL f)
{
	showai = f;
}

BOOL oCAIHuman :: GetShowAI()
{
	return showai;
}

zBOOL oCAIHuman :: CanThisCollideWith (zCVob* vob)	
{
	return !ignoreVobList.InList(vob);
}

void oCAIHuman :: AddIgnoreCD (zCVob *vob)
{
	ignoreVobList.Insert(vob);
}

void oCAIHuman :: SubIgnoreCD (zCVob *vob)
{
	ignoreVobList.Remove(vob);
}

// [HILDEBRANDT] removed ReportCollisionToAI()

void oCAIHuman :: StartFlyDamage(zREAL damage, zVEC3& flyDir)
{
	int	  fMax	= 0.0f
		, fMin	= 0.0f
		, fStep	= 0.0f;

	zCPar_Symbol* pSymbol = NULL;

	pSymbol = ::parser.GetSymbol( "DAMAGE_FLY_CM_MAX"		);	pSymbol->GetValue( fMax		);
	pSymbol = ::parser.GetSymbol( "DAMAGE_FLY_CM_MIN"		);	pSymbol->GetValue( fMin		);
	pSymbol = ::parser.GetSymbol( "DAMAGE_FLY_CM_PER_POINT" );	pSymbol->GetValue( fStep	);

	 if ( damage <= 0.0f ) damage = 1.0f;

	zREAL fDamage	= damage * fStep;
	fDamage			= zMax( fDamage, (zREAL) fMin );
	fDamage			= zMin( fDamage, (zREAL) fMax );

	fDamage   *= 100;
	flyDir    *= fDamage;
	flyDir[VY] = config.zMV_FORCE_JUMP_UP * 0.8;

	//
	//	WINKEL ZUM ZIEL-ORT BESTIMMEN
	//
	zREAL azi, elev;
	zVEC3 posTarget;
	posTarget  = npc->GetAtVectorWorld();
	posTarget += flyDir;
	npc->GetAngles( posTarget, azi, elev );

	//
	//	ENSTRECHENDE FALL-ANI STARTEN
	//
	if ( abs( azi ) > 90 )		GetModel() -> StartAni ("S_FALLB");
	else						GetModel() -> StartAni ("S_FALL");

	// Etwas über den Boden setzen
	zVEC3 pos = npc->GetPositionWorld();
	pos[VY]  += 30;
	npc -> SetPositionWorld						(pos);
	npc -> SetPhysicsEnabled					(TRUE);
	npc -> GetRigidBody() -> SetGravityEnabled	(TRUE);
	npc -> GetRigidBody() -> ApplyImpulseCM		(flyDir);

	createFlyDamage = damage;
}

// ********************************************
// Archiver
// ********************************************

void oCAIHuman :: Archive (zCArchiver &arc)
{
	oCAniCtrl_Human::Archive(arc);
	
	if (!arc.InSaveGame())	return;
}

void oCAIHuman :: Unarchive	(zCArchiver &arc)
{
	oCAniCtrl_Human::Unarchive(arc);

	if (!arc.InSaveGame())	return;
}

// **********************************************************************************
// Camera 
// **********************************************************************************

// Camera 1 AI

// Constructor
oCAICamera:: oCAICamera ( )
{
};

/*	------------------------------------------------------------------
	void oCAICamera :: DoAI (zCVob *vob,BOOL &vobDeleted)
	11.12.00	[Hildebrandt]	
				RotateLocal() durch RotateWorld() ersetzt, wenn man sich
				mit CURSOR_LEFT/RIGHT um die eigene (Welt-) Achse drehen moechte.
				TODO: statt ztimer.GetFrameTimeF() einen lokalen zCTimer-Member
				benutzen!
	------------------------------------------------------------------ */


void oCAICamera :: DoAI (zCVob *vob,BOOL &vobDeleted)
{
	vobDeleted = FALSE;
	zREAL frameTime = ztimer.GetFrameTimeF()/1000;
	if (frameTime == 0) frameTime = 0.02F;
	
	//if (frameTime == 0) frameTime = 0.02F;

	float step = 350 * frameTime, rotxstep = 150 *frameTime;
	float xspeed,yspeed,zspeed,rotspeed,rotx;

	xspeed = yspeed = zspeed = rotspeed = rotx = 0;

	if (zinput->KeyPressed(KEY_LSHIFT) || zinput->KeyPressed(KEY_RSHIFT)) {
		step		*= 4;
		rotxstep	*= 2;
	}

	// Vorwärts
	if (zinput->KeyPressed(KEY_UP)) {
		zspeed = step;
	} else if (zinput->KeyPressed(KEY_DOWN)) {
		zspeed = -step;
	};
	// Nach links gehen / drehen
	if (zinput->KeyPressed(KEY_LEFT)) {
		if (zinput->KeyPressed(KEY_LALT)) 
			xspeed = -step;
		else
			rotspeed = -rotxstep;
	}
	
	if (zinput->KeyPressed(KEY_RIGHT)) {
		if (zinput->KeyPressed(KEY_LALT)) 
			xspeed = step;
		else	
			rotspeed = rotxstep;
	};
	
	if (zinput->KeyPressed(KEY_A)) {
		yspeed = step;
	} else if (zinput->KeyPressed(KEY_Z)) {	// [BENDLIN] Addon, KeybFix
		yspeed = -step;
	};

	if (zinput->KeyPressed(KEY_PGUP)) {
		rotx = -rotxstep;
	} else if (zinput->KeyPressed(KEY_PGDN)) {
		rotx = rotxstep;
	}

	vob -> RotateWorld	(0,1,0,rotspeed);	// [HILDEBRANDT]
	vob -> RotateLocal	(1,0,0,rotx);		

	vob -> MoveLocal	(zVEC3(xspeed,yspeed,zspeed));
}



// ********************************************
// Bert Special Spacer NSC -.AI
// ********************************************

oCAIHuman_Stand :: oCAIHuman_Stand( zCVob *v )
{
}

oCAIHuman_Stand :: ~oCAIHuman_Stand( )
{
}

void oCAIHuman_Stand :: DoAI (zCVob* inVob, zBOOL& vobDeleted)
{
	zREAL feetY;
	vobDeleted = FALSE;

//	if (inVob->GetVisualType()==zVISUAL_MODEL) {
//		zCModel *GetModel()	= (zCModel *)inVob->GetVisual();
//		feetY			= GetModel()->GetBBox3DWorld().mins[VY];  
//	} else {
		feetY			= inVob->GetBBox3DWorld().mins[VY];  
//	}
	
	zVEC3 centerPos	= inVob->GetPositionWorld();
	zREAL diff		= centerPos[VY] - feetY;
	zCWorld* wld	= inVob->GetHomeWorld();

	if (wld->TraceRayNearestHit(inVob->GetPositionWorld(),zVEC3(0,-1000,0),inVob,zTRACERAY_STAT_POLY)) {
		// Poly gefunden
		if (wld->traceRayReport.foundPoly) {
			// Schnittpunkt schnappen und Position neu setzen
			zVEC3 newpos = wld->traceRayReport.foundIntersection;
			// 4 cm bis zum Bodem, um Kollision zu vermeiden.
			newpos[VY] += diff + 4;
//			zCView :: stdoutput -> Printwin("Pos Y : "+zSTRING(newpos[VY],4)+"\n");
			inVob->SetPositionWorld	(newpos);
			inVob->SetPhysicsEnabled(FALSE);
		}
	}
	// inVob -> SetAICallback(NULL);
}

zCLASS_DEFINITION (oCAIHuman,		oCAniCtrl_Human, 0,0 )

zCLASS_DEFINITION (oCAICamera,		zCAIBase, 0,0 )
zCLASS_DEFINITION (oCAIHuman_Stand, zCAIBase, 0,0 )

#pragma warning ( default:4244 )
