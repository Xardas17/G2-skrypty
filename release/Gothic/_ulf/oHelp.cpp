/******************************************************************************** 
 
     $Workfile:: oHelp.cpp            $                $Date:: 1.12.00 16:53    $
     $Revision:: 10                   $             $Modtime:: 1.12.00 13:19    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oHelp.cpp $
 * 
 * 10    1.12.00 16:53 Wohlers
 * 
 * 9     11.09.00 13:26 Rueve
 * cleanup
 * 
 * 8     24.08.00 11:33 Moos
 * new durch zNEW ersetzt
 * 
 * 7     21.07.00 15:34 Wohlers
 * 
 * 6     21.07.00 14:43 Wohlers
 * 
 * 5     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 3     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

// oHelp.cpp

#include "zCore.h"

#include "oHelp.h"

#include "oGame.h"
#include "oNpc.h"
#include "oItem.h"
#include "oDialog.h"
#include "oAniCtrl.h"
#include "oFocus.h"
#include "oText.h"

#include "zSound.h"
#include "zOption.h"
#include "zInput_Win32.h"

static const int K_LEFT		= 0;
static const int K_RIGHT	= 1;
static const int K_UP		= 2;
static const int K_DOWN		= 3;

static const int LED_CTRL	= 0;
static const int LED_ALT	= 1;

enum {	HLP_TURN_LEFT	=  0,
		HLP_TURN_RIGHT	=  1,
		HLP_FORWARD		=  2,
		HLP_BACKWARD	=  3,
		HLP_LEFT		=  4,
		HLP_RIGHT		=  5,
		HLP_JUMP		=  6,

		HLP_CATLEFT		=  7,
		HLP_CATRIGHT	=  8,
		HLP_UP			=  9,
		HLP_DOWN		= 10,

		HLP_USE_SWITCH	= 11,

		HLP_EXAMINE		= 12,
		HLP_OPEN		= 13,
		HLP_THROW		= 14,
		HLP_DROP		= 15,
		HLP_PUSH		= 16,
		HLP_PULL		= 17,
		HLP_ASK			= 18,
		HLP_STEAL		= 19,
		HLP_TAKE		= 20,
		HLP_READY		= 21,

		HLP_MOVETOCONT	= 22,
		HLP_MOVETOINV	= 23,

		HLP_GUILD		= 24,
		HLP_TRADE		= 25,
		HLP_LEARN		= 26,

		HLP_EXCHANGE	= 27,
		HLP_BUY			= 28,
		HLP_SELL		= 29,

		HLP_INHAND		= 30,
		HLP_WEAPON		= 31,
		HLP_EAT			= 32,
		HLP_READ		= 33,
		HLP_YES			= 34,
		HLP_NO			= 35,

		HLP_GIVE		= 36,
		HLP_HIT			= 37,
		HLP_HITL		= 38,
		HLP_HITR		= 39,
		HLP_DEFEND		= 40,
		HLP_SHOOT		= 41,

		HLP_SWIM_FOR	= 42,
		HLP_SWIM_BACK	= 43,
		HLP_DIVE		= 44,
		HLP_DIVE_UP		= 45,
		HLP_DIVE_DOWN	= 46,

		HLP_CLIMB		= 47,
		HLP_CALL		= 48
};

static zCGfx *k_alt,		*k_alth,	*k_altp,
				*k_ctrl,	*k_ctrlh,	*k_ctrlp,
				*k_cup,		*k_cdown,	*k_cleft,
				*k_cright,	*k_cnone,	*k_both;

static oCItem *a_item;
static oCNpc	 *a_npc;


/* ----------------------------------------------------------------------
	
	oCHelp :: oCHelp()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

oCHelp :: oCHelp ( )
{	
	zoptions->ChangeDir(DIR_TEX_DESKTOP);
	
	int	x	= 8192 - screen->anx(159);
	int y	= 8192 - screen->any(59);
	
	win		=  zNEW(zCView)	(x,y,x + screen->anx(158),y + screen->any(58));
	screen	-> InsertItem	(win);
	//win		-> InsertBack	("desktop\\gfx_help.pcx");
//	win		-> SetChromaKey	(GFX_BLACK);
//	win		-> SetTransparency (254);
	
	// Load Grafix
	k_alt	= zNEW(zCGfx)("k-alt.pcx");
	k_alth	= zNEW(zCGfx)("k-alth.pcx");
	k_altp	= zNEW(zCGfx)("k-altp.pcx");
	k_ctrl	= zNEW(zCGfx)("k-ctrl.pcx");
	k_ctrlh = zNEW(zCGfx)("k-ctrlh.pcx");
	k_ctrlp = zNEW(zCGfx)("k-ctrlp.pcx");
	k_cup	= zNEW(zCGfx)("k-cup.pcx");
	k_cdown	= zNEW(zCGfx)("k-cdown.pcx");
	k_cleft	= zNEW(zCGfx)("k-cleft.pcx");
	k_cright= zNEW(zCGfx)("k-cright.pcx");
	k_cnone = zNEW(zCGfx)("k-cnone.pcx");;
	k_both	= zNEW(zCGfx)("k-both.pcx");

	//win		-> FontCol ( GFX_BLUE );
	
	memset (&index,-1,sizeof(index));

	led[0] = 0;
	led[1] = 0;

	CalcPos();

	Redraw( NULL );
};

oCHelp :: ~oCHelp()
{
	if (win->IsVisible()) screen -> RemoveItem(win);
	delete(win);
};

void oCHelp :: CalcPos()
{
	// unused: 	int ly = win -> FontY();
	sx = 8192 / 4;
	sy = 8192 / 4;
	dx = sx / 4;
	dy = sy / 4;
	
	// links drehen
	x[0] = win->anx(15  + 52);	y[0] = win->any(40); 
	// rechts drehen
	x[1] = win->anx(93  + 52);	y[1] = win->any(40);
	// vor
	x[2] = win->anx(49  + 52);	y[2] = win->any(1);
	// zurück
	x[3] = win->anx(49  + 52);	y[3] = win->any(22);
		
	// Ctrl
	ledx[0] = dx;			
	ledy[0] = dy;
	// Alt
	ledx[1] = dx*3+sx*2+sx/2;
	ledy[1] = dy;
}

void oCHelp :: Toggle ()
{
	if (win->IsVisible()>0) {
		screen -> RemoveItem (win);
		// Sound on
		zCSoundFX * newSnd = zsound->LoadSoundFXScript("HELP_OFF");
		zsound->PlaySound(newSnd);	
		zRELEASE(newSnd);
	} else {
		screen -> InsertItem (win);
		Redraw();
		// Sound on
		zCSoundFX * newSnd = zsound->LoadSoundFXScript("HELP_ON");
		zsound->PlaySound(newSnd);	
		zRELEASE(newSnd);
	}
}

void oCHelp :: Update()
{
/*	if (!oCNpc::player) return;

	for (int i=0; i<4; i++) index[i] = -1;
	led[LED_ALT]	= FALSE;
	led[LED_CTRL]	= FALSE;

	// Frage aktiv ?
	if (View_YesNo()) {
		led[LED_CTRL] = TRUE;
		if (kbPressed(KEY_LCTRL)) {
			index[K_UP]		= HLP_YES;
			index[K_DOWN]	= HLP_NO;
		}
	} else if ((oCNpc :: game_mode == NPC_GAME_NORMAL) && (oCNpc :: player -> GetWeaponMode()==NPC_WEAPON_NONE)) {
		
		int walkmode;
		oCAniCtrl_Human *ai = oCNpc :: player -> GetAnictrl();
		if (ai) 
			walkmode = ai  -> GetWalkMode();
		else
			walkmode = ANI_WALKMODE_RUN;

		// ***********************************
		// Schwimmen ?
		// ***********************************
		if (walkmode==ANI_WALKMODE_SWIM) {
			if (!kbPressed(KEY_LALT)) {
				led	 [LED_ALT]	= TRUE;
				index[K_UP]		= HLP_SWIM_FOR;
				index[K_DOWN]	= HLP_SWIM_BACK;
				index[K_LEFT]	= HLP_TURN_LEFT;
				index[K_RIGHT]	= HLP_TURN_RIGHT;
			} else if (ai->Swim_CanClimbLedge()) {
				index[K_UP] = HLP_CLIMB;
			}
			return;
		} else if (walkmode==ANI_WALKMODE_DIVE) {
			led	 [LED_ALT]	= TRUE;
			index[K_UP]		= HLP_DIVE_UP;
			index[K_DOWN]	= HLP_DIVE_DOWN;
			index[K_LEFT]	= HLP_TURN_LEFT;
			index[K_RIGHT]	= HLP_TURN_RIGHT;			
			return;
		}

		// ***********************************
		// Normale Bewegung
		// ***********************************
		led[LED_ALT] = TRUE;
		if ((a_mob!=NULL) || (a_item!=NULL) || (a_npc!=NULL)) led[LED_CTRL] = TRUE;

		if (!kbPressed(KEY_LCTRL)) {
			index[K_DOWN]	= HLP_BACKWARD;
			if (kbPressed(KEY_LALT)) {
				index[K_UP]		= HLP_JUMP;
				if (walkmode!=ANI_WALKMODE_WATER) {
					index[K_LEFT]	= HLP_LEFT;
					index[K_RIGHT]	= HLP_RIGHT;
				}
			} else {
				index[K_UP]		= HLP_FORWARD;
				index[K_LEFT]	= HLP_TURN_LEFT;
				index[K_RIGHT]	= HLP_TURN_RIGHT;
			}
		}	
		
		if (kbPressed(KEY_LCTRL)) {
			if (a_mob != NULL) {
				// Mob im Focus !
				if (a_mob->HasFlag(OBJ_FLAG_SWITCH)) 
					index[K_UP]	= HLP_USE_SWITCH;
				else if (a_mob->HasFlag(OBJ_FLAG_CONTAINER)) 
					index[K_UP]	= HLP_OPEN;
				// Verschiebbar
				if ((kbPressed(KEY_LCTRL)) && (a_mob -> HasFlag(OBJ_FLAG_MOVEABLE))) {
					index[K_UP]		= HLP_PUSH;
					index[K_DOWN]	= HLP_PULL;
				}
			} else if (a_npc != NULL) {
				// NSC im Focus
				if (a_npc->IsDead()) {
					index[K_UP] = HLP_EXAMINE;
				} else {
					zREAL dist = oCNpc :: player->GetDistanceToVob2(*a_npc);
					if (dist > oCNpcFocus :: focus -> GetRange2()) {
						index[K_UP] = HLP_CALL;
					} else {
						index[K_UP]	= HLP_ASK;
					}
					if ((kbPressed(KEY_LCTRL)) && (dist < oCNpcFocus :: focus -> GetRange2())) {
						if (oCNpc::player -> HasTalent(NPC_TAL_STEAL)) 
							index[K_RIGHT] = HLP_STEAL;
					}
				}
			} else if (a_item != NULL) {
				// Item im Focus
				if (kbPressed(KEY_LCTRL)) {
					index[K_UP]	= HLP_TAKE;
				}
			} else if ((oCNpc :: player->GetRightHand())!=NULL) {
				index[K_UP]		= HLP_THROW;
				//index[K_RIGHT]	= HLP_TAKE;
			}
		}// else {
			//index[K_CTRL]	= HLP_EXAMINE;
			//if (kbPressed(KEY_LALT)) {
			//	index[K_UP]		= HLP_THROW;
			//index[K_LEFT]	= HLP_DROP;
			//}
		//}
	} else if (oCNpc :: player -> GetWeaponMode()!=NPC_WEAPON_NONE) {
		// ********************************************************
		// Kampmodus
		// ********************************************************
		led[LED_CTRL]	= TRUE;
		led[LED_ALT]	= TRUE;

		if (!kbPressed(KEY_LCTRL)) {
			index[K_DOWN]	= HLP_BACKWARD;
			if (kbPressed(KEY_LALT)) {
				index[K_UP]		= HLP_JUMP;
				index[K_LEFT]	= HLP_LEFT;
				index[K_RIGHT]	= HLP_RIGHT;
			} else {
				index[K_UP]		= HLP_FORWARD;
				index[K_LEFT]	= HLP_TURN_LEFT;
				index[K_RIGHT]	= HLP_TURN_RIGHT;
			}
		} else {
			if (1) {
				//worldhandler.GetHostPlayer()->GetWeaponMode()<=NPC_WEAPON_2HA) {
				index[K_UP]		= HLP_HIT;
				index[K_LEFT]	= HLP_HITL;
				index[K_RIGHT]	= HLP_HITR;
				index[K_DOWN]	= HLP_DEFEND;
			} else if (oCNpc::player->GetWeaponMode()<=NPC_WEAPON_CBOW) {
//				if (worldhandler.GetHostPlayer()->HasArrowInHand()) index[K_UP] = HLP_SHOOT;
			}
		}
	} else if (oCNpc :: game_mode == NPC_GAME_INVENTORY) {
		// ***********************************
		// Inventory - Mode
		// ***********************************
		oCNpcInventory *inv_cont= NULL;
		oCItemContainer *cont	= oCNpcInventory :: GetContainer(); 
		if (cont->GetType()==ITM_INVENTORY) inv_cont = (oCNpcInventory *)cont;

		if (inv_cont!=NULL) {
			// *********************
			// Inventory
			// *********************
			if (kbPressed(KEY_LCTRL)) {
				if (a_item!=NULL) {
					if ((a_item->HasFlag(ITM_FLAG_NF)) || (a_item->HasFlag(ITM_FLAG_FF)) || (a_item->HasFlag(ITM_FLAG_RU))) {
						if (oCNpc :: player->CanUse(a_item)) index[K_UP]	= HLP_WEAPON;
					} else if (a_item->HasFlag(ITM_FLAG_VZ)) {
						index[K_UP] = HLP_EAT;
					} else if (a_item->HasFlag(ITM_FLAG_LB)) {
						index[K_UP] = HLP_READ;
					} 
					if (oCNpcInventory :: GetNumOfContainer() > 1) {
						// Noch ein Container im Bild -> dann dareinpacken moeglich !
						index[K_LEFT] = HLP_MOVETOCONT;
					}
				}
				index[K_DOWN] = HLP_DROP;
			} else {
				led	[LED_CTRL] = TRUE;
				if (cont->HasPrevItem()) index[K_UP]	= HLP_UP;
				if (cont->HasNextItem()) index[K_DOWN]	= HLP_DOWN;
				if (inv_cont->GetPrevCategory() != inv_cont->GetCategory()) index[K_LEFT] = HLP_CATLEFT;
				if (inv_cont->GetNextCategory() != inv_cont->GetCategory()) index[K_RIGHT]= HLP_CATRIGHT;
			}
		} else {
			// *********************
			// Container
			// *********************
			if (kbPressed(KEY_LCTRL)) {
				index[K_RIGHT] = HLP_MOVETOINV;
			} else {
				led	[LED_CTRL] = TRUE;
				if (cont->HasPrevItem()) index[K_UP]	= HLP_UP;
				if (cont->HasNextItem()) index[K_DOWN]	= HLP_DOWN;
			}			
		}
	} else if (oCNpc :: game_mode == NPC_GAME_DIALOG) {
		led[LED_CTRL]	= TRUE;
		led[LED_ALT]	= TRUE;
		if (!kbPressed(KEY_LCTRL)) {
			index[K_DOWN]	= HLP_BACKWARD;
			index[K_UP]		= HLP_FORWARD;
			index[K_LEFT]	= HLP_TURN_LEFT;
			index[K_RIGHT]	= HLP_TURN_RIGHT;
		} else {
			index[K_UP]		= HLP_ASK;
			index[K_LEFT]	= HLP_LEARN;
			index[K_RIGHT]	= HLP_TRADE;
		}
	} else if (oCNpc :: game_mode == NPC_GAME_STEAL) {
		oCItemContainer *cont	= oCNpcInventory :: GetContainer(); 
		led[LED_CTRL]	= TRUE;
		if (cont->HasPrevItem()) index[K_UP]	= HLP_UP;
		if (cont->HasNextItem()) index[K_DOWN]	= HLP_DOWN;
		if (kbPressed(KEY_LCTRL)) {
			index[K_RIGHT] = HLP_STEAL;
		}
	} else if (oCNpc :: game_mode == NPC_GAME_TRADE) {
		led[LED_CTRL]	= TRUE;
		index[K_UP]		= HLP_UP;
		index[K_DOWN]	= HLP_DOWN;
		index[K_LEFT]	= HLP_CATLEFT;
		index[K_RIGHT]	= HLP_CATRIGHT;
		
/*		if (kbPressed(KEY_LCTRL)) {
			if (oCNpcInventory :: GetContainer() == game_inv_Player) {
				index[K_LEFT]	= HLP_GIVE;
				index[K_UP]		= HLP_SELL;
			} else if (oCNpcInventory :: GetContainer() == game_inv_NSCs) {
				index[K_RIGHT]	= HLP_STEAL;
				index[K_UP]		= HLP_BUY;
			} else if ((oCNpcInventory :: GetContainer() == game_inv_Demand) && (game_trader->IsOffer())) {
				index[K_RIGHT]	= HLP_EXCHANGE;
			} else if ((oCNpcInventory :: GetContainer() == game_inv_Offer) && (game_trader->IsOffer())) {
				index[K_RIGHT]	= HLP_EXCHANGE;
			}
		}*/
//	} 
}

void oCHelp :: Redraw ( zCVob *v )
{
	if (win->IsVisible()==0) return;
	
	// what vob
	a_item	= NULL;
	a_npc	= NULL;
	if (v) {
		switch (v->GetVobType() ) {
			case zVOB_TYPE_NSC	:	a_npc	= (oCNpc *)v;
									break;
			case zVOB_TYPE_ITEM	:	a_item	= (oCItem *)v;
									break;
		}
	}
	Update();

	int l,xp;
	//,col;

	//win -> DrawBackground();
	
	// Alt-Key
/*	if (kbPressed(KEY_LCTRL)) 
		win -> Draw(0,0,k_ctrlp->data);
	else if (kbPressed(KEY_LALT))
		win -> Draw(0,0,k_altp->data);
	else if (led[LED_CTRL] && led[LED_ALT]) 
		win -> Draw(0,0,k_both->data);
	else if (led[LED_CTRL]) 
		win -> Draw(0,0,k_ctrlh->data);
	else if (led[LED_ALT]) 
		win -> Draw(0,0,k_alth->data);
	else {
		win -> Draw(0,0,k_ctrl->data);
		win -> Draw(0,win->any(20),k_alt->data);
	}
*/	
	// Pfeiltasten
/*	if (kbPressed(KEY_UP)) 
		win -> Draw(win->anx(51),0,k_cup->data);
	else if (kbPressed(KEY_DOWN)) 
		win -> Draw(win->anx(51),0,k_cdown->data);
	else if (kbPressed(KEY_LEFT))
		win -> Draw(win->anx(51),0,k_cleft->data);
	else if (kbPressed(KEY_RIGHT))
		win -> Draw(win->anx(51),0,k_cright->data);
	else 
		win -> Draw(win->anx(51),0,k_cnone->data);


//	win -> InsertBack	(GFX_OLIVE);

/*
	for (int i=0; i<2; i++) {
		if (led[i]) 
			col = GFX_GREEN;
		else
			col = GFX_GREY;
		win -> Bar	(ledx[i],ledy[i],ledx[i]+sx/2,ledy[i]+sy/2,col);
	}
*/
	zSTRING s;

	for (int i=0; i<4; i++) {
		
		if (index[i]>=0) {
			
			s = parser.GetText ( oCText :: TXT_HELP, index[i] );

			l = win -> FontSize ( s );

			xp = x[i] - l / 2;
			
			if ((i==1) && (xp+l>8192)) 
				xp = 8192-l;

			win -> Print(xp,y[i], s );
		}
	}
};

//#pragma optimize( "", on )
