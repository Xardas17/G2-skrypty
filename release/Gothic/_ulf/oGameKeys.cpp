/******************************************************************************** 
 
     $Workfile:: oGameKeys.cpp        $                $Date:: 24.04.01 18:49   $
     $Revision:: 161                  $             $Modtime:: 24.04.01 18:44   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oGameKeys.cpp $
 * 
 * 161   24.04.01 18:49 Edenfeld
 * 1.08: Ausgabe des aktuell selektierten Spruches bei Benutzung eines
 * Shortkeys
 * 
 * 160   24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 159   16.02.01 23:08 Moos
 * 
 * 158   16.02.01 18:31 Wohlers
 * 
 * 157   16.02.01 12:28 Edenfeld
 * Crashfix Magie: Trvialer Nullpointer
 * 
 * 156   14.02.01 16:14 Wohlers
 * 
 * 155   14.02.01 4:13 Edenfeld
 * LookBack Cam
 * 
 * 154   13.02.01 21:33 Wohlers
 * 
 * 153   13.02.01 17:15 Wohlers
 * 
 * 152   13.02.01 11:26 Speckels
 * 
 * 151   11.02.01 20:24 Wohlers
 * 
 * 150   10.02.01 22:34 Wohlers
 * 
 * 149   10.02.01 20:48 Wohlers
 * 
 * 148   9.02.01 16:19 Pankratz
 * 
 * 147   8.02.01 19:39 Edenfeld
 * 
 * 146   8.02.01 17:30 Wohlers
 * 
 * 145   8.02.01 16:59 Edenfeld
 * 
 * 144   6.02.01 5:40 Edenfeld
 * 
 * 143   6.02.01 4:49 Wohlers
 * 
 * 142   6.02.01 4:33 Wohlers
 * 
 * 141   6.02.01 1:59 Wohlers
 * 
 * 140   6.02.01 1:06 Wohlers
 * 
 * 139   6.02.01 0:33 Wohlers
 * 
 * 138   31.01.01 21:49 Wohlers
 * 
 * 137   31.01.01 20:18 Wohlers
 * 
 * 136   31.01.01 2:07 Wohlers
 * 
 * 135   30.01.01 16:57 Wohlers
 * 
 * 134   29.01.01 16:35 Keskenti
 * 
 * 133   28.01.01 14:31 Wohlers
 * 
 * 132   25.01.01 20:09 Wohlers
 * 
 * 131   25.01.01 14:23 Wohlers
 * 
 * 130   18.01.01 19:31 Wohlers
 * 
 * 129   17.01.01 13:01 Keskenti
 * 
 * 128   16.01.01 10:56 Moos
 * 
 * 127   12.01.01 16:54 Edenfeld
 * 
 * 126   12.01.01 12:38 Moos
 * 
 * 125   11.01.01 0:39 Wohlers
 * 
 * 124   9.01.01 21:35 Wohlers
 * 
 * 123   9.01.01 20:22 Wohlers
 * 
 * 122   8.01.01 21:16 Wohlers
 * 
 * 121   8.01.01 14:55 Wohlers
 * 
 * 120   20.12.00 17:13 Moos
 * 
 * 119   19.12.00 13:40 Wohlers
 * 
 * 118   14.12.00 20:45 Wohlers
 * 
 * 117   8.12.00 17:32 Keskenti
 * 
 * 116   5.12.00 18:56 Speckels
 * 
 * 115   1.12.00 16:53 Wohlers
 * 
 * 114   30.11.00 12:53 Wohlers
 * 
 * 113   29.11.00 22:57 Wohlers
 * 
 * 112   29.11.00 21:57 Speckels
 * 
 * 111   29.11.00 18:16 Keskenti
 * 
 * 110   29.11.00 15:04 Keskenti
 * 
 * 109   29.11.00 14:45 Speckels
 * 
 * 108   29.11.00 12:52 Speckels
 * 
 * 107   24.11.00 15:41 Wohlers
 * 
 * 106   23.11.00 17:50 Wohlers
 * 
 * 105   21.11.00 14:12 Wohlers
 * 
 * 104   17/11/00 13:10 Luesebrink
 * 
 * 103   17/11/00 9:19 Luesebrink
 * 
 * 102   15.11.00 21:05 Speckels
 * 
 * 101   15.11.00 21:03 Speckels
 * 
 * 100   15/11/00 15:25 Luesebrink
 * 
 * 99    14.11.00 16:07 Wohlers
 * 
 * 98    14.11.00 14:31 Wohlers
 * 
 * 97    9.11.00 17:58 Wohlers
 * 
 * 96    9.11.00 17:10 Wohlers
 * 
 * 95    8.11.00 17:53 Wohlers
 * 
 * 94    7.11.00 18:53 Wohlers
 * 
 * 93    7/11/00 15:03 Luesebrink
 * 
 * 92    31.10.00 20:27 Keskenti
 * 
 * 91    27/10/00 16:53 Luesebrink
 * 
 * 90    26/10/00 18:27 Luesebrink
 * 
 * 89    26/10/00 15:52 Luesebrink
 * 
 * 88    25/10/00 15:48 Luesebrink
 * 
 * 87    21.10.00 19:51 Moos
 * 
 * 86    21/10/00 16:25 Luesebrink
 * 
 * 85    20/10/00 19:40 Luesebrink
 * 
 * 84    18.10.00 17:15 Keskenti
 * 
 * 83    16.10.00 21:28 Wohlers
 * 
 * 82    12.10.00 20:01 Wohlers
 * 
 * 81    10.10.00 13:39 Wohlers
 * 
 * 80    9/10/00 13:43 Luesebrink
 * 
 * 79    6.10.00 12:45 Wohlers
 * 
 * 78    4.10.00 18:04 Wohlers
 * 
 * 77    29.09.00 16:50 Wohlers
 * 
 * 76    28.09.00 21:20 Wohlers
 * 
 * 75    23.09.00 20:58 Herget
 * 
 * 74    22.09.00 20:07 Wohlers
 * 
 * 73    21.09.00 16:02 Wohlers
 * 
 * 72    20.09.00 22:22 Edenfeld
 * 
 * 71    20.09.00 21:19 Edenfeld
 * 
 * 70    20.09.00 16:51 Wohlers
 * 
 * 69    19.09.00 15:41 Keskenti
 * 
 * 68    14.09.00 18:30 Wohlers
 * 
 * 66    14.09.00 14:42 Wohlers
 * 
 * 65    13.09.00 19:50 Moos
 * 
 * 64    12.09.00 14:47 Wohlers
 * 
 * 63    7.09.00 21:05 Wohlers
 * 
 * 62    7.09.00 18:00 Wohlers
 * 
 * 61    7/09/00 16:57 Luesebrink
 * 
 * 60    6/09/00 18:21 Luesebrink
 * 
 * 59    5.09.00 21:09 Wohlers
 * 
 * 58    4.09.00 17:02 Rueve
 * 
 * 57    2.09.00 1:21 Keskenti
 * 
 * 56    1/09/00 17:35 Luesebrink
 * 
 * 55    31/08/00 14:29 Luesebrink
 * 
 * 54    30/08/00 12:33 Luesebrink
 * 
 * 53    29.08.00 21:24 Wohlers
 * 
 * 52    28.08.00 15:40 Rueve
 * zRndGlide.h ging nach Hause
 * 
 * 51    28.08.00 12:53 Edenfeld
 * 
 * 50    28.08.00 12:50 Keskenti
 * 
 * 49    25.08.00 0:33 Wohlers
 * 
 * 48    24.08.00 15:01 Moos
 * new durch zNEW ersetzt
 * 
 * 47    23.08.00 15:39 Wohlers
 * 
 * 46    23/08/00 14:46 Luesebrink
 * 
 * 45    22/08/00 14:01 Luesebrink
 * 
 * 44    21.08.00 18:56 Speckels
 * 
 * 43    17/08/00 17:03 Luesebrink
 * 
 * 42    15/08/00 13:15 Luesebrink
 * 
 * 41    14.08.00 18:10 Keskenti
 * 
 * 40    14.08.00 18:06 Keskenti
 * 
 * 39    14.08.00 18:05 Keskenti
 * 
 * 38    10.08.00 18:37 Wohlers
 * 
 * 37    9.08.00 12:53 Wohlers
 * 
 * 36    4/08/00 16:40 Luesebrink
 * 
 * 35    4.08.00 15:22 Wohlers
 * 
 * 34    3.08.00 20:51 Wohlers
 * 
 * 33    2.08.00 14:25 Wohlers
 * 
 * 32    1.08.00 15:14 Wohlers
 * 
 * 31    31.07.00 22:04 Wohlers
 * 
 * 30    27.07.00 19:50 Wohlers
 * 
 * 29    27.07.00 17:04 Wohlers
 * 
 * 28    27.07.00 15:29 Wohlers
 * 
 * 27    26/07/00 18:12 Luesebrink
 * 
 * 26    26.07.00 17:53 Wohlers
 * 
 * 25    26/07/00 13:22 Luesebrink
 * 
 * 24    26/07/00 12:41 Luesebrink
 * 
 * 23    26.07.00 12:06 Wohlers
 * 
 * 22    26.07.00 12:05 Wohlers
 * 
 * 21    21.07.00 14:43 Wohlers
 * 
 * 20    21/07/00 13:31 Luesebrink
 * 
 * 19    21.07.00 11:58 Wohlers
 * 
 * 18    20/07/00 15:20 Luesebrink
 * 
 * 15    5.07.00 12:20 Wohlers
 * 
 * 13    14.06.00 18:14 Wohlers
 * Gothic 0.85a
 * 
 * 12    13.06.00 22:24 Edenfeld
 * 
 * 11    9.06.00 18:18 Wohlers
 * 
 * 10    5.06.00 22:34 Wohlers
 * uSrc 05.06.00
 * 
 * 9     29.05.00 18:35 Wohlers
 * 
 * 8     24.05.00 20:29 Wohlers
 * Gothic 0.83
 * 
 * 7     22.05.00 22:13 Wohlers
 * 
 * 6     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 11    12.05.00 3:37 Wohlers
 * 
 * 10    11.05.00 12:48 Wohlers
 * 
 * 9     10.05.00 23:27 Wohlers
 * Gothic 0.81a
 * 
 * 8     10.05.00 4:00 Wohlers
 * 
 * 7     9.05.00 21:13 Wohlers
 * Gothic 0.81
 * 
 * 6     9.05.00 20:20 Wohlers
 * Gothic 0.81
 * 
 * 5     8.05.00 23:08 Edenfeld
 * 
 * 5     8.05.00 19:31 Wohlers
 * Gothic 0.80 - Inventory
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
 * 31    19.04.00 16:44 Wohlers
 * Bug-Fixes
 * 
 * 30    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 29    30.03.00 20:35 Wohlers
 * Bugfixes ( Wegnetz, TAs etc. )
 * 
 * 28    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 25    16.03.00 19:20 Wohlers
 * Anpassung Engine 0.88
 * 
 * 24    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 22    24.02.00 23:32 Wohlers
 * Fixes
 * 
 * 21    23.02.00 3:47 Wohlers
 * Fixes
 * 
 * 20    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 19    6.02.00 18:42 Wohlers
 * Various Fixes
 * 
 * 18    4.02.00 15:38 Wohlers
 * Bugfixes 
 * 
 * 17    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 15    11.01.00 22:59 Wohlers
 * CS-Fixes / NSC-Equip-Message
 * 
 * 14    10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 13    20.12.99 17:44 Wohlers
 * uSrc V0.70
 * AI_UseItem / AniComb TakeItem etc...
 * 
 * 11    7.12.99 22:08 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 10    6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 9     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 8     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zcore.h"

#include "oGame.h"
#include "oWorld.h"
#include "oNpc.h"
#include "oItem.h"
#include "oAIShoot.h"
#include "oAIHuman.h"
#include "oHelp.h"
#include "oMobInter.h"
#include "oInventory.h"
#include "oTrigger.h"
#include "oNpcMessages.h"
#include "ooCarsten.h"
#include "oMission.h"
#include "oMagic.h"
#include "oSpawn.h"

#include "oDoc.h"
#include "oVob.h"
#include "oGuilds.h"
#include "oPortals.h"

#include "zEventMan.h"
#include "zPhysics.h"
#include "zWaynet.h"
#include "zRenderer.h"
//#include "zRndGlide.h"
#include "zTexture.h"
#include "zAICamera.h"
#include "zCCSPlayer.h"
#include "zMorphMesh.h"
#include "zInput.h"
#include "zInput_Win32.h"
#include "zSky.h"

//changed[dennis]
#include "oFocus.h"

#include "oIncDialogs.h"
#include "oInfo.h"
#include "oInformationManager.h"

#ifdef DEBUG_MOOS
#include <memmanager.h>
#endif

#define E3_SKY_HACK

/*
void StartAIOutput(oCNpc* npc, oCNpc* target, zSTRING name)
{
	if (npc) {
		npc->voice = 11;
		if (target) {
			target->voice = 11;
			// Gucke ob "target" einen Eintrag mit "npc" als Ziel hat. 
			// Dann auf Beendigung dieser Msg warten
			zCEventMessage* evMsg = target->GetTalkingWithMessage(npc);
			if (evMsg) {
				oCMsgConversation* msg = zNEW( oCMsgConversation(oCMsgConversation::EV_WAITTILLEND,target);
				msg->watchMsg = evMsg;
				npc->GetEM()->OnMessage(msg,npc);
			}
		}
		oCMsgConversation* convMsg = zNEW( oCMsgConversation(oCMsgConversation::EV_OUTPUTSVM,name);
		convMsg->target = target;
		npc -> GetEM() -> OnMessage(convMsg,npc);
	}
}

void TestAIOutput(oCNpc* npc1, oCNpc* npc2)
{
	if (!npc1 || !npc2) return;

	StartAIOutput(npc1,npc2,"$CHEERFIGHT"); 
	StartAIOutput(npc2,npc1,"$HEYHEYHEY");
}
*/

unsigned char GetCharFromDIK(int dik1, int dik2, int dik3 );

void ToggleShowStateDebug(oCNpc* target)
{
	if (target) {
		target->showaidebug=!target->showaidebug;
		if (target->showaidebug) 
			zerr.Message("U:NPC:"+target->GetName(TRUE)+" Log actions on.");
		else
			zerr.Message("U:NPC:"+target->GetName(TRUE)+" Log actions off.");
	}
}

void ToggleShowAI(oCNpc* target)
{
	// Alle Nscs ausschalten
	oCNpc* npc = NULL;
	zCListSort<oCNpc>* node = ogame->GetGameWorld()->GetVobListNpcs()->GetNextInList();
	while (node) {
		npc		= node->GetData();
		node	= node->GetNextInList();
		if ((npc!=target) && npc->GetHumanAI()) {
			npc -> GetHumanAI() -> SetShowAI(FALSE);
		};
	};

	// Nur das Target an
	if (target && target->GetHumanAI()) {
		target -> GetHumanAI() -> SetShowAI(!target -> GetHumanAI() -> GetShowAI());
	}
}

// FIXME : was machen die Statics hier : Unschoen !?!?!?!
static	oCNpc*	watchn	= NULL;
static  int		npcNr	= 0;

void oCGame :: SwitchCamToNextNpc ()
{
	zBOOL flag;

	if (watchn!=NULL) { 
		// Uebernimm Zustand 
		flag = ((oCAIHuman *)watchn->GetAICallback())->GetShowAI();
		((oCAIHuman *)watchn->GetAICallback())->SetShowAI(FALSE);
	
	} else flag = FALSE;

	do {
		watchn = ogame->GetGameWorld()->GetVobListNpcs()->Get(npcNr);
		if (watchn) {
			if (!watchn->GetHomeWorld()) {
				watchn = NULL;
			} else {
				((oCAIHuman *)watchn->GetAICallback())->SetShowAI(flag);
			}
		} else {
			npcNr = -1;
		}
		npcNr++;			
	} while (!watchn);

	GetCameraAI()->SetTarget(watchn);
	// [BENDLIN] Addon - Ghost Alpha
	if (watchn && (NPC_FLAG_GHOST == (watchn->variousFlags & NPC_FLAG_GHOST)))
		GetCameraAI()->SetTargetAlpha(zoptions->ReadReal("INTERNAL", "GhostAlpha", 0.3f));
	GetCameraAI()->ReceiveMsg(zPLAYER_BEAMED);
	if (oCNpc::player -> GetSleepingMode() == zVOB_SLEEPING) {
		oCNpc* save		= oCNpc::player;
		oCNpc::player	= NULL;
		HandleEvent(KEY_F4);
		oCNpc::player   = save;
	} else
		HandleEvent(KEY_F4);
};

/* ----------------------------------------------------------------------
	
	oCGame :: HandleEvent()

	24.08.2000	[Moos]	

				auf zNEW umgestellt (ja, gut. Nicht sehr sinnvoll. Aber gründlichkeit muss sein :-)

	20.09.2000  [Edenfeld] SetFrontSpell() als Message verschickt.

   ---------------------------------------------------------------------- */

zBOOL oCGame :: HandleEvent (int key)
{
	// In globalen Cutscenes macht der hier gar nichts.
	if (GetWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene()) return FALSE;
	if (!oCNpc::player) return FALSE;

	zSTRING s;

	zWORD logicalKey = zinput->GetFirstBindedLogicalKey(key);	

	switch (logicalKey)
	{	
		// 
		// Offizielle Gamekeys (in Logicalkeys umwandeln?)
		//


		case GAME_LOCK_TARGET:	
								{
									if (!oCGame::GetUseOldControls()) oCNpc::SetTargetLocked(!oCNpc::GetTargetLocked());
									return TRUE;
								}
		case GAME_SCREEN_STATUS:	
								{ // Status - Screen
									if(oCNpc::player->inventory2.IsOpen()) oCNpc::player->inventory2.Close();
									oCNpc::player->OpenScreen_Status();
								};
								return TRUE;
								break;

		
		case GAME_SCREEN_LOG:
								{ // Mission/Log - Screen
									if(oCNpc::player->inventory2.IsOpen()) oCNpc::player->inventory2.Close();
									oCNpc::player->OpenScreen_Log();			
								};
								return TRUE;
								break;
		
		case GAME_SCREEN_MAP:	{ // Map
									zERR_MESSAGE(8, 0, "N: MAP: GAME_SCREEN_MAP");
									if (!oCNpc::player)										break;
									if (oCNpc::player->IsUnconscious())						break;
									if (oCNpc::player->GetInteractMob())					break;
									if (!oCNpc::player->GetEM()->IsEmpty(TRUE))				break;																		
//									if (!oCNpc::player->GetWeaponMode()!=NPC_WEAPON_NONE)	break; [Moos] Überflüssig (und ausserdem genau falschrum..); Die Waffe wird auch gerne weggesteckt.
									if (!oCNpc::player->GetAnictrl()->IsStanding())			break;
									if (oCNpc::player->GetBodyState() == BS_SWIM)			break;
									if (oCNpc::player->GetBodyState() == BS_DIVE)			break;

									// [BENDLIN] Addon - Skriptfunktion bei Karten-Hotkey
									int mapFunc = parser.GetIndex("PLAYER_HOTKEY_SCREEN_MAP");
									if (mapFunc <= 0)
										zERR_FAULT("N: MAP: Skript function PLAYER_HOTKEY_SCREEN_MAP not found!");
									else if (ogame && ogame->GetGameWorld())
									{
										// PLAYER_HOTKEY_SCREEN_MAP
										int mapInst = *(int*)parser.CallFunc(mapFunc);
										// OpenScreen_Map
										oCNpc::player->ClearEM();
										if (oCNpc::player->inventory2.IsOpen())
											oCNpc::player->inventory2.Close();
										oCNpc::player->OpenScreen_Map(mapInst);
									}
								};
								return TRUE;
								break;

		case GAME_INVENTORY:	// Öffnen
								if (ztimer.GetFrameTimeF()!=0.0f)				// nur wenn spiel nicht im pause modus
								if (oCNpc::player->IsUnconscious()) break; 
								if (oCNpc::player && oCNpc::player->GetEM()->IsEmpty(TRUE)) {
									// Keine aktive MobInteraction
									if (!oCNpc::player->GetInteractMob()) {
										oCNpc::player->OpenInventory(INV_MODE_DEFAULT);
										// Look Ani aus, weil diese das Benutzen der Inv-Items überlagern
										oCNpc::player->GetAnictrl()->StopLookAtTarget();
									}

								}
								return TRUE;
								break;
	}

	// [BENDLIN] man sollte keine lokalen Variablen ändern,
	// wenn sie später referenziert werden könnten... no comment
	int magkey = key;

	switch(key) 
	{
		/*case KEY_F1			:	{ // Help - Screen
									oCNpc::player->OpenScreen_Help();			
								};
								break;

		*/
		case KEY_F1			:
		case KEY_F2			:
		case KEY_F3			:
		case KEY_F4			:
								{
									if (game_testmode)
										return TestKeys(key);
									else
									{
										if (ogame->GetWorld()->GetActiveSkyControler())
										{
											zREAL gameSightFactor = 1.0f;
											switch (key) {
												case KEY_F1: gameSightFactor = zoptions->ReadReal("GAME", "SHORTKEY1FARPLANEDIST", 0.8f); break;
												case KEY_F2: gameSightFactor = zoptions->ReadReal("GAME", "SHORTKEY2FARPLANEDIST", 1.2f); break;
												case KEY_F3: gameSightFactor = zoptions->ReadReal("GAME", "SHORTKEY3FARPLANEDIST", 2.0f); break;
												case KEY_F4: gameSightFactor = zoptions->ReadReal("GAME", "SHORTKEY4FARPLANEDIST", 3.0f); break;
											}
											gameSightFactor = zMax(gameSightFactor, 0.2f);
											gameSightFactor = zMin(gameSightFactor, 3.0f);
											int gameSightSetting = zFloat2Int(gameSightFactor * 100) / 20 - 1;
											gameSightSetting = zMax(gameSightSetting, 0);
											gameSightSetting = zMin(gameSightSetting, 14);
											zoptions->WriteInt(zOPT_SEC_PERFORMANCE, "sightValue",	gameSightSetting, TRUE);
											ogame->GetWorld()->GetActiveSkyControler()->SetFarZScalability(gameSightFactor);
											return TRUE;
										}
									}
								};
								break;

		//
		// Quickslots
		//
		case KEY_1			:	{
									if (!oCNpc::player->CanDrawWeapon()) break;
									if (oCNpc::player->GetSpellBook()) {
										oCNpc::player->GetSpellBook()->Close(TRUE);
									}

									if((zinput)->KeyToggled(KEY_1))
									{
										// check toggle first! (closing inventory clears the keybuffer
										if(oCNpc::player->inventory2.IsOpen())oCNpc::player->inventory2.Close();
										if(dynamic_cast<oCMobContainer*>(oCNpc::player->GetInteractMob()))
										{
											((oCMobContainer*)oCNpc::player->GetInteractMob())->Close(oCNpc::player);
											((oCMobContainer*)oCNpc::player->GetInteractMob())->Reset();
											//oCNpc::player->GetAnictrl()->SearchStandAni(TRUE);
										}

										switch( oCNpc::player->GetWeaponMode() )
										{
											// PLAYER IS IN FIST MODE						-> UNDREADY WEAPON, READY A MELEE WEAPON IF THERE IS ONE AVAILABLE
											case NPC_WEAPON_FIST	:   oCNpc::player->GetEM()->OnMessage( zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), oCNpc::player ); 
																		goto DrawMeleeWeapon;
																		break;

											// PLAYER HAS ALREADY READIED A MELEE WEAPON	-> UNREADY IT
											case NPC_WEAPON_DAG		:  
											case NPC_WEAPON_1HS		:  
											case NPC_WEAPON_2HS		:	oCNpc::player->GetEM()->OnMessage( zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), oCNpc::player ); 
																		break;

											// PLAYER HAS ALREADY READIED A RANGE WEAPON	-> UNREADY IT, READY A MELEE WEAPON
											case NPC_WEAPON_BOW		:  
											case NPC_WEAPON_CBOW	:  
											case NPC_WEAPON_MAG		:	oCNpc::player->GetEM()->OnMessage( zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), oCNpc::player );

											// PLAYER HAS NOT READIED ANY WEAPON			-> READY A MELEE WEAPON
											case NPC_WEAPON_NONE	:  
																		DrawMeleeWeapon:
																		oCNpc::player->GetEM()->OnMessage( zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON, NPC_WEAPON_FIST), oCNpc::player );
																		break;
										}
									}
								}
								break;


		case KEY_2			:	{
									if (!oCNpc::player->CanDrawWeapon()) break;

									if((zinput)->KeyToggled(KEY_2))
									{
										if (oCNpc::player->GetSpellBook())
											oCNpc::player->GetSpellBook()->Close(TRUE);

										// check toggle first! (closing inventory clears the keybuffer
										if(oCNpc::player->inventory2.IsOpen())oCNpc::player->inventory2.Close();
										if(dynamic_cast<oCMobContainer*>(oCNpc::player->GetInteractMob()))
										{
											((oCMobContainer*)oCNpc::player->GetInteractMob())->Close(oCNpc::player);
											((oCMobContainer*)oCNpc::player->GetInteractMob())->Reset();
											//oCNpc::player->GetAnictrl()->SearchStandAni(TRUE);
										}

										if (oCNpc::player->GetWeaponMode()==NPC_WEAPON_NONE) {
											oCItem* weapon = oCNpc::player->GetEquippedRangedWeapon();
											if (weapon && oCNpc::player->IsMunitionAvailable(weapon)) {
												//oCNpcFocus::focus->SetFocusMode(FOCUS_RANGED);
												oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON, NPC_WEAPON_BOW),oCNpc::player); 
											}
										}
										else if( oCNpc::player->GetWeaponMode() == NPC_WEAPON_BOW || oCNpc::player->GetWeaponMode() == NPC_WEAPON_CBOW )
										{
											oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),oCNpc::player); 
										}
										else
										{
											oCItem* weapon = oCNpc::player->GetEquippedRangedWeapon();
											if (weapon && oCNpc::player->IsMunitionAvailable(weapon)) {
												oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),oCNpc::player); 
												oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON, NPC_WEAPON_BOW),oCNpc::player); 
											}
										}
									}
								}break;
		case KEY_3			:	// 3 Magie/Psi (letzter Spruch)
								// a) Magie available
								if (!oCNpc::player->CanDrawWeapon())	break;
								if (!oCNpc::player->HasMagic())			break;

								if ((zinput)->KeyToggled(KEY_3))
								{
									// check toggle first! (closing inventory clears the keybuffer
									if(oCNpc::player->inventory2.IsOpen())oCNpc::player->inventory2.Close();
									if(dynamic_cast<oCMobContainer*>(oCNpc::player->GetInteractMob()))
									{
										((oCMobContainer*)oCNpc::player->GetInteractMob())->Close(oCNpc::player);
										((oCMobContainer*)oCNpc::player->GetInteractMob())->Reset();
										//oCNpc::player->GetAnictrl()->SearchStandAni(TRUE);
									}
								
									if(dynamic_cast<oCMobContainer*>(oCNpc::player->GetInteractMob()))
									{
										((oCMobContainer*)oCNpc::player->GetInteractMob())->Close(oCNpc::player);
										((oCMobContainer*)oCNpc::player->GetInteractMob())->Reset();
									}
									int wm = oCNpc::player->GetWeaponMode();
									if (wm<NPC_WEAPON_MAG) {
										// Waffe wegstecken
										if (wm!=NPC_WEAPON_NONE) oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),oCNpc::player); 
										// Noch nicht im Magiemodus, Waffe ziehen (letzter Spruch wird automatisch genommen)
										oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON,NPC_WEAPON_MAG),oCNpc::player); 										
									}
									else oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),oCNpc::player);
								};
								break;
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
		case KEY_9:
		case KEY_0			:	if (!oCNpc::player->CanDrawWeapon()) break;
								// 3 Magie/Psi (letzter Spruch)
								// a) Magie available
								magkey = GetCharFromDIK(key, 0, 0);
								if ( magkey == 48 ) magkey = 58;
								if ( oCNpc::player->inventory2.IsOpen() ) break;
								if(dynamic_cast<oCMobContainer*>(oCNpc::player->GetInteractMob()))
								{
									((oCMobContainer*)oCNpc::player->GetInteractMob())->Close(oCNpc::player);
									((oCMobContainer*)oCNpc::player->GetInteractMob())->Reset();
								}

								if (oCNpc::player->HasMagic())
								{
									if(oCNpc::player->GetWeaponMode() == NPC_WEAPON_MAG)
									{
										if(oCNpc::player->GetSpellBook()->GetSelectedSpell())
										if(oCNpc::player->GetSpellBook()->GetSelectedSpell()->keyNo==magkey-51)
										{
											oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),oCNpc::player);break;
										}
									}
								}
								if (oCNpc::player->HasMagic()) 
								{	
									// Swim oder Dive ausklammern
									if ((oCNpc::player->GetAnictrl()->GetActionMode()==ANI_ACTION_SWIM) || 
										(oCNpc::player->GetAnictrl()->GetActionMode()==ANI_ACTION_SWIM)) break;
										
									// Ulf: Vorher waren die nächsten beiden if blöcke vertauscht. Statt der 
									// EV_SETFRONTSPELL MEssage wurde die Funktion direkt aufgerufen... (CE)
									int i = oCNpc::player->GetSpellBook()->GetNoOfSpellByKey(magkey-51);
									if (i) 
									{
										//oCMsgMagic *msg = zNEW(oCMsgMagic)(oCMsgMagic::EV_SETFRONTSPELL);
										//msg->activeSpell = i-1;
										oCNpc::player->GetSpellBook()->SetFrontSpell( i-1 );
										oCSpell *spell = 0;
										if (oCNpc::player->GetSpellBook()) spell = oCNpc::player->GetSpellBook()->GetSelectedSpell();

										// [EDENFELD] 1.09 Spellnamen scrollen nicht mehr nach oben
										if (spell) 
										{
											zCView::stdoutput->PrintCXY(spell->GetName());
											zCView::stdoutput->PrintTimedCXY(spell->GetName(), 1.0f * 1000);
										}
									} else break;
									
									if ( !(oCNpc::player->GetSpellBook()->IsOpen()))
									{
										int wm = oCNpc::player->GetWeaponMode();
										if (wm<NPC_WEAPON_MAG) 
										{
											// Waffe wegstecken
											if (wm!=NPC_WEAPON_NONE) oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),oCNpc::player); 
											// Noch nicht im Magiemodus, Waffe ziehen (letzter Spruch wird automatisch genommen)
											oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON,NPC_WEAPON_MAG),oCNpc::player); 
										}
									}
									/*
									int i = oCNpc::player->GetSpellBook()->GetNoOfSpellByKey(magkey-51);

									if( i ) 
									{
										oCMsgMagic *msg = zNEW(oCMsgMagic)(oCMsgMagic::EV_SETFRONTSPELL);
										msg->activeSpell = i-1;
										//oCNpc::player->GetSpellBook()->SetFrontSpell( i-1 );
										oCNpc::player->GetEM()->OnMessage(msg,oCNpc::player);
									}
									else break;*/

								};
								break;
		case KEY_F8:
								if (game_testmode) 
								{	
									return TestKeys(key);	
								}
								else
								{
									if (zinput->KeyPressed(KEY_LALT) && zinput->KeyPressed(KEY_LCTRL))
									if (oCNpc::player) 
									{
										oCNpc::player -> EmergencyResetPos(oCNpc::player->GetPositionWorld());
										return TRUE;
									}
								}
								return FALSE;
								break;
		//
		// Testkeys
		//

		default				:	if (game_testmode) 
									return TestKeys(key);	
								return FALSE;
								break;
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	oCGame :: TestKeys()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

zBOOL oCGame :: TestKeys (int key)
{
	if (!oCNpc::player) return TRUE;	// [SPECKELS]

	if (game_editwaynet) return IA_TestWay(key);

	static	oCDummyVobGenerator* gen	= NULL;
	static	zCModel*	model			= NULL;
	static	oCItem*		item			= NULL;	
	static	oCItem*		lastitem		= NULL;
	static	oCNpc*		lastnpc			= NULL;
	static	int			npcnr			= 0;

#ifdef DEBUG_EDENFELD
	static	zCVob*		debugCam		= 0;
#endif

	float gamma;
	zSTRING s;
	static BOOL thirdview = FALSE;
	static oCNpc *targetnpc = NULL;

	zMATRIX4 trafo;

	zVEC3 vec;
	float x,y,z;
	oCVob* ovob;

	zVEC3 pos;
	
	zREAL dum1;
	zTRnd_FogMode dum2;
	
	switch (key) {

	case KEY_PAD_MUL :	gamma = zrenderer -> Vid_GetGammaCorrection();
						gamma += 0.1f; 
						if (gamma>2.0f) gamma = 2.0f;
						
						zoptions->WriteReal(zOPT_SEC_VIDEO,"zVidGamma",gamma);	

						zrenderer -> Vid_SetGammaCorrection(gamma);
						zCView::PrintDebug("< Gamma "+zSTRING(gamma)+">\n");
						break;
	case KEY_PAD_DIV :	gamma = zrenderer -> Vid_GetGammaCorrection();
						gamma -= 0.1f; 
						if (gamma<0.0f) gamma = 0.0f;

						zoptions->WriteReal(zOPT_SEC_VIDEO,"zVidGamma",gamma);	

						zrenderer -> Vid_SetGammaCorrection(gamma);
						zCView::PrintDebug("< Gamma "+zSTRING(gamma)+">\n");
						break;
	

	case KEY_F8			:	// Position
							if (zinput->KeyPressed(KEY_LSHIFT))
							{
								oCNpc::player->ResetPos(startpos);
								GetCameraAI()->ReceiveMsg(zPLAYER_BEAMED);
							}
							else
							{
								oCNpc::player->ResetPos(oCNpc::player->GetPositionWorld() + zVEC3(0,150,0));
							}
							// Info-Manager
							{
								oCInformationManager&	mgrInfos	= oCInformationManager::GetInformationManager();		
								mgrInfos.Exit();
							}

							break;
	case KEY_F2			:	
							Game_OpenConsole();	break;

	case KEY_5			:	cliprange = GetCamera()->GetFarClipZ() - 100;
							SetRanges();
							zCView::PrintDebug("< FarClip "+zSTRING((int)GetCamera()->GetFarClipZ())+" >\n");
							break;
	case KEY_6			:	cliprange = GetCamera()->GetFarClipZ() + 100;
							SetRanges();
							zCView::PrintDebug("< FarClip "+zSTRING((int)GetCamera()->GetFarClipZ())+" >\n");
							break;
	case KEY_7			:	zrenderer -> GetFogRange(fogrange,dum1,dum2);
							fogrange  -= 100;
							if (fogrange<0) fogrange = 0;
							SetRanges();
							zCView::PrintDebug("< Fog "+zSTRING(fogrange)+">\n");
							break;
	case KEY_8			:	zrenderer -> GetFogRange(fogrange,dum1,dum2);
							fogrange  += 100;
							SetRanges();
							zCView::PrintDebug("< Fog "+zSTRING(fogrange)+">\n");
							break;
	case KEY_9			:	if ((zinput->KeyPressed(KEY_LSHIFT)) || (zinput->KeyPressed(KEY_RSHIFT))) {
								// CAMLIGHT
								playerLightInt	-= 100; 
								if (playerLightInt<0) playerLightInt=0;
								if (zCSkyControler::GetActiveSkyControler())
								{
									zCSkyControler::GetActiveSkyControler()->SetLightDirty();
								}
								zCView::PrintDebug("< CamLight: "+zSTRING(playerLightInt)+">\n");
							} else {
								// PlayerLight
								pl_lightval	-= 100; 
								if (pl_lightval<0) pl_lightval=0;
								pl_light ->SetRange(pl_lightval);
								if (zCSkyControler::GetActiveSkyControler())
								{
									zCSkyControler::GetActiveSkyControler()->SetLightDirty();
								}
								zCView::PrintDebug("< PlayerLight: "+zSTRING(pl_lightval)+">\n");
							}
							break;
	case KEY_0			:	if ((zinput->KeyPressed(KEY_LSHIFT)) || (zinput->KeyPressed(KEY_RSHIFT))) {
								// CAMLIGHT
								playerLightInt += 100; 
								if (zCSkyControler::GetActiveSkyControler())
								{
									zCSkyControler::GetActiveSkyControler()->SetLightDirty();
								}
								zCView::PrintDebug("< CamLight: "+zSTRING(playerLightInt)+">\n");
							} else if (pl_light && game_text) {
								// PlayerLight
								pl_lightval	+= 100; 
								pl_light ->SetRange(pl_lightval);
								if (zCSkyControler::GetActiveSkyControler())
								{
									zCSkyControler::GetActiveSkyControler()->SetLightDirty();
								}
								zCView::PrintDebug("< PlayerLight: "+zSTRING(pl_lightval)+">\n");
							}
							break;
	case KEY_Y			:	// Freie Wegsuche Test
							oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_ROBUSTTRACE,oCNpc::player->GetPositionWorld()+oCNpc::player->GetAtVectorWorld()*1000),NULL);
							break;
							
	case KEY_C			:	// Attack....	
							if (oCNpc::player)
							{
								if (zinput->KeyPressed(KEY_LSHIFT)) {
									oCNpc* npc = oCNpc::player->GetFocusNpc();
									if (npc) {
										parser.SetInstance("SELF",npc);
										parser.SetInstance("OTHER",oCNpc::player);
										npc->state.StartAIState	("ZS_FOLLOW_PC",FALSE,0);
									};
								} else {
									oCNpc* npc = oCNpc::player->GetFocusNpc();
									if (npc) {
										npc->SetEnemy			(oCNpc::player);
										npc->state.StartAIState	("ZS_ATTACK",FALSE,0);
									};
								}
							}
							break;

#ifndef DEBUG_MOOS      // GRRRR. Im Debug-Modus gibt mir der Fullscreen-Wechsel einen Bluescreen.
	case KEY_F3			:	Game_ToggleScreenMode();
							break;
#else
#ifndef _DEBUG
	case KEY_F3			:	Game_ToggleScreenMode();
							break;
#endif
#endif
	case KEY_F4			:	// GameCamera
							if (zinput->KeyPressed(KEY_LSHIFT))
							{
								sysIdle(100);
								oCInformationManager::GetInformationManager().ToggleStatus();
							}
							else
							{
								GetCameraVob()	-> SetCollDet	(FALSE);
								GetWorld()		-> RemoveVob	(GetCameraVob());
								GetWorld()		-> AddVob		(GetCameraVob());
							}

// externer 3rd Person Debug Modus							
#ifdef DEBUG_EDENFELD
							if (debugCam)
							{
								debugCam->RemoveVobFromWorld();
								zRELEASE(debugCam);
							}
							GetCameraAI()   -> SetVob(GetCameraVob());
#endif

							zCView::PrintDebug	("< Game Camera.>\n");
							// Sleeping on / off
							GetCameraVob()	-> SetAICallback(GetCameraAI());
							GetCameraVob()	-> SetSleeping	(FALSE);
							
							freeLook = FALSE;

							if (oCNpc::player) oCNpc :: player -> SetSleeping(FALSE);							
							break;
							
	case KEY_F5			:	// Mov Player -> Model
							if ( !zinput->KeyPressed(KEY_LCTRL) )
							{
								oCNpc	:: player -> SetShowVisual	(TRUE);
								oCNpc	:: player -> SetSleeping	(FALSE);
								zCView::PrintDebug ("< Move Player - Model.>\n");
								GetCameraVob() -> SetSleeping(TRUE);
							}
							else return FALSE;
							break;
	case KEY_F6			:	// Mov Camera
							// Vom Spieler entkoppeln
							GetCameraVob()	-> SetCollDet	    (FALSE);
							GetWorld()		-> RemoveVob	    (GetCameraVob());
							GetWorld()		-> AddVob		    (GetCameraVob());
							GetCameraVob()	-> SetHeadingYWorld	(oCNpc :: player);
							GetCameraVob()	-> SetAICallback    (zNEW(oCAICamera)()); // [Moos] 20.12.00 Anpassung an Vob-Änderung
                            GetCameraVob()  ->GetAICallback()->Release();             // [Moos] Leakfix
							GetCameraVob()	-> SetSleeping	    (FALSE);

							oCNpc :: player -> SetShowVisual	(TRUE);
							oCNpc :: player -> SetSleeping	(TRUE);

#ifdef DEBUG_EDENFELD
							if (!debugCam) 
							{
								debugCam = zNEW(zCVob);
								debugCam ->SetSleeping			(FALSE);
								debugCam ->SetVisual			("invisible_zCCSCamera.3ds");
								debugCam ->SetPhysicsEnabled	(FALSE);
								debugCam ->SetCollDet			(FALSE);
								debugCam ->SetIgnoredByTraceRay	(TRUE);
								debugCam ->SetTrafo				(GetCameraVob()->trafoObjToWorld);
								GetCameraVob()->GetHomeWorld()->AddVob(debugCam);
								debugCam ->SetAICallback		(GetCameraAI());
								GetCameraAI()->SetVob(debugCam);
							}
#endif

							freeLook = TRUE;
							break;

	case KEY_F7			:	// 3. person View
							GetCameraVob()	-> SetCollDet		    (FALSE);
							oCNpc::player	-> SetShowVisual	    (TRUE);
							GetWorld()		-> RemoveVob		    (GetCameraVob());
							GetCameraVob()	-> ResetRotationsWorld	();               // [Moos] 20.12.00 Anpassung an Vob-Änderung
							GetWorld()		-> zCWorld::AddVobAsChild(GetCameraVob(),oCNpc :: player);
							//GetCameraVob()	-> SetPositionWorld     (0,70,-300);
							zCView::PrintDebug("< Third Person.>\n");
							// Sleeping on / off
							GetCameraVob()	-> SetSleeping		(TRUE);
							oCNpc::player	-> SetSleeping		(FALSE);							
							break;
/*	case KEY_F8			:   // 1. person view
							oCNpc	::	player -> SetShowVisual(FALSE);
							camera		->  SetVob( oCNpc :: player );
							zCView	::	StdPrintwin(zSTRING("< First person.>\n"));
							// Sleeping on / off
							camVob		->	SetSleeping(TRUE);
							oCNpc	::	player -> SetSleeping(FALSE);							
							break;
*/
	case KEY_F9			:	
							if (zinput->KeyPressed(KEY_LALT))
							{
								zresMan->PurgeCaches();
								return TRUE;
							}
		
							if ( !zinput->KeyPressed(KEY_LCTRL) )
							{
								singleStep = !singleStep;
								if (singleStep) {
									timeStep = 0.0f;
									zCView::PrintDebug	("< Single-step an >\n");
								} else {
									timeStep = -1.0f;
									zCView::PrintDebug	("< Single-step aus >\n");
								}
							}
							else return FALSE;

							break;
	case KEY_F10		:	if (singleStep) {
								timeStep = (1.0F / 25.0F);
								zerr.Message ("step");
							}
							break;
//	case KEY_F11		:	watchnpc = oCNpc :: player -> GetFocusNpc();
//							break;

	case KEY_F12		:	// Test InfoManager
							if ( zinput->KeyPressed( KEY_LALT ) ) 
							{
								oCNpc* pPlayer	= dynamic_cast< oCNpc* >  ( ::ogame->GetSelfPlayerVob() );
								oCNpc* pSelf	= pPlayer->GetFocusNpc();

								if ( pSelf )
								{
									oCMsgConversation* pMsg = zNEW( oCMsgConversation ) ( oCMsgConversation::EV_PROCESSINFOS, pSelf );
									pPlayer->GetEM()->OnMessage( pMsg, pPlayer );
								}
							}
							else
							// Making a ScreenDump
							{
								static int count = 0;
								//zrenderer -> Vid_ScreenDump ( zSTRING("GOTHIC"+zSTRING(count))+".TGA" );
								count++;
							}
							break;
	case KEY_G			:	// Toggle Show AI - Function ( Player )
							if (zinput->KeyPressed(KEY_LCTRL)) {
								ToggleShowStateDebug(oCNpc::player->GetFocusNpc());
							} else if (zinput->KeyPressed(KEY_LSHIFT)) {
								ToggleShowAI(oCNpc :: player -> GetFocusNpc());
							} else {		
								ToggleShowAI(oCNpc::player);
							}
							break;
	case KEY_F11			:	// Set Player to Watchn
							if (watchn) {
								zTVobSleepingMode aimode = watchn -> GetSleepingMode();
								watchn -> SetAsPlayer();
								watchn -> SetVobName("ABCD");
								((oCAIHuman *)watchn->GetAICallback())->SetShowAI(FALSE);
								HandleEvent(KEY_F4);
								watchn -> SetSleepingMode (aimode);
								watchn = NULL;							
							}
							break;
	case KEY_HOME		:	SwitchCamToNextNpc ();	
							break;
	
	
	case KEY_BACKSPACE		:	
							{
								if( oCNpc::player->GetHumanAI()->IsSprintActive() )
								{
									oCNpc::player->GetHumanAI()->SetSprintMode(FALSE);
									return TRUE;
										}
								else
								{
									if( oCNpc::player->GetWeaponMode() >= NPC_WEAPON_FIST ) oCNpc::player->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),oCNpc::player);
									oCNpcFocus::focus->SetFocusMode(FOCUS_NORMAL);
									oCNpc::player->GetHumanAI()->SetCamMode(CamModNormal);
									oCNpc::player->GetHumanAI()->SetSprintMode(TRUE);
									return TRUE;
								
								}
							}break;

	case KEY_T			:	if (zinput->KeyPressed(KEY_LALT)) {
								GetWorld()->PrintStatus();
							} else {
								if (zinput->KeyPressed(KEY_LSHIFT))	
									ovob = (oCVob*) oCNpc::player;
								else 
									ovob = (oCVob*) oCNpc::player -> GetFocusVob();
								if (ovob) ovob -> ToggleShowDebug();
							}
							break;	

	case KEY_GREYPLUS	:	playerLightInt	+= 100; 
							fogrange		+= 100;
							cliprange		+= 100;
							SetRanges();
							zCView::PrintDebug("< Light: "+zSTRING(playerLightInt)+" Fog: "+zSTRING((int)fogrange)+">\n");
							break;
	case KEY_GREYMINUS	:	playerLightInt	-= 100; 
							fogrange		-= 100;
							cliprange		-= 100;
							SetRanges();
							zCView::PrintDebug("< Light: "+zSTRING(playerLightInt)+" Fog: "+zSTRING((int)fogrange)+">\n");
							break;

	case KEY_P			:	if (zinput->KeyPressed(KEY_LALT)) {
#ifdef DEBUG_MOOS  // Speicher-Kram
                                mem_man::profile();
#endif
								oCNpc :: player -> GetPositionWorld(x,y,z);
								s = "Position :" + zSTRING(x) + "/" + zSTRING(y) + "/" + zSTRING(z) + "\n";
								game_text -> Printwin(s);
								break;
							} else {
								
							
							}
							break;
	// !!!! TEMP !!!!

	case KEY_O		:		if (zinput->KeyPressed(KEY_LALT)) {
								ogame->SetShowDebug(!ogame->GetShowDebug());
								if (ogame->GetShowDebug()) 				
									game_text -> Printwin("Debug Infos an.\n");
								else
									game_text -> Printwin("Debug Infos aus.\n");
							} else {
								
								if (oCNpc::player->GetFocusNpc()) oCNpc::player->GetFocusNpc()->SetAsPlayer();

							}
							break;	

	case KEY_U			:	if (zinput->KeyPressed(KEY_LALT)) {
								game_showwaynet = !game_showwaynet;
							} else if (zinput->KeyPressed(KEY_LCTRL)) {
								ogame->SetShowDebug(TRUE);
								zCView::PrintDebug("< Waynet - Mode an >\n");
								game_showwaynet = TRUE;
								game_editwaynet	= TRUE;
							} else if (zinput->KeyPressed(KEY_LSHIFT)) {
								GetWorld()->GetWayNet() -> CorrectHeight();
								zCView::PrintDebug("< Waynet - Correction.>\n");
							}
							break;

	case KEY_K			:	if (zinput->KeyPressed(KEY_LALT)) {
								Game_OpenFightConsole();		
						
							} else {
								// Beamer
								oCNpc::player->SetCollDet		(FALSE);
								oCNpc::player->SetPositionWorld ( oCNpc::player->GetPositionWorld()+oCNpc::player->GetAtVectorWorld()*300 );
								oCNpc::player->SetCollDet		(TRUE);
								ogame->GetCameraAI()->ReceiveMsg(zPLAYER_BEAMED);
							}

							break;
							
					
	case KEY_E			:	// Open Species Console / DescribeTree
							if (zinput->KeyPressed(KEY_LALT)) 
								Game_OpenSpeciesConsole();		
							else
								GetSelfPlayerVob()->GetModel()->GetModelProto()->DescribeTree();
							break;

	case KEY_PAD_LEFT	:	// Talent Schleichen an / aus
							if (oCNpc::player->GetTalentSkill(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_SNEAK)==1)
							{
								oCNpc::player->SetTalentSkill(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_SNEAK,0);
								zCView::PrintDebug("< Schleichen aus. >\n");
							} else {
								oCNpc::player->SetTalentSkill(oCNpcTalent::oTEnumNpcTalent::NPC_TAL_SNEAK,1);
								zCView::PrintDebug("< Schleichen an. >\n");
							}
							break;

	case KEY_LHOOK		:	// "?"
							// Toggle automatic Camera - System
							GetCameraAI()->SetModeChangeEnabled(!GetCameraAI()->GetModeChangeEnabled());
							if (GetCameraAI()->GetModeChangeEnabled()) 
								zCView::PrintDebug("< Camera-Changes an. >\n");
							else
								zCView::PrintDebug("< Camera-Changes aus. >\n");
							break;

	case KEY_H			:	// Hit him 
							if (zinput->KeyPressed(KEY_LSHIFT)) {
 								if (oCNpc::player->GetFocusVob()) oCNpc::player->GetFocusVob()->OnDamage(oCNpc::player,oCNpc::player,5,oEDamageType_Fire,oCNpc::player->GetFocusVob()->GetPositionWorld());
								oCNpc::player->SetFocusVob(NULL);
							
							} else if (zinput->KeyPressed(KEY_LCTRL)) {
								oCNpc::player->GetEM()->OnDamage(NULL,NULL,10,oEDamageType_Fire | oEDamageType_Magic, oCNpc::player->GetAtVectorWorld() );
							} else {
								oCNpc::player->GetEM()->OnDamage(oCNpc::player,oCNpc::player,10,oEDamageType_Edge,oCNpc::player->GetPositionWorld());
							}
							break;

	case KEY_J			:	{
								// Show Routine Info
								if (oCNpc::player) showRoutineNpc = oCNpc::player->GetFocusNpc();
							}
							break;
	case KEY_V			:	// various Krams je nach Bedarf
/*							{
								oCNpc* npc = oCNpc::player->GetFocusNpc();
								if (npc) {
									zCModelNodeInst*	head	= npc->GetModel()->SearchNode(zMDL_NODE_NAME_HEAD);
									if (head) {
										zCMorphMesh*	vis		= zDYNAMIC_CAST<zCMorphMesh> (head->GetNodeVisual());
										if (vis) {
											if (zinput->KeyPressed(KEY_LSHIFT)) {
												npc -> StartDialogAni ();
											} else {											
												if (vis->IsAniActive("VISEME")) {
													npc->StopFaceAni("VISEME");
												} else if (vis->IsAniActive	("S_FRIENDLY")) {
													npc->StartFaceAni	("S_NEUTRAL",1,-1);
												} else {
													npc->StartFaceAni	("S_FRIENDLY",1,-1);										
												}
											}
										}
									}
								}
							}*/
							// DeleteTorches();
							// if (oCNpc::player->GetFocusNpc()) oCNpc::player->GetFocusNpc()->DropUnconscious(0,oCNpc::player);
/*							{
							srand(0);
							oCNpc* npc1, *npc2;
							int npcNum = GetGameWorld()->GetVobListNpcs()->GetNumInList();
							for (int i=0; i<100000; i++) {
								
								npc1 = GetGameWorld()->GetVobListNpcs()->Get(zRand(npcNum));
								npc2 = GetGameWorld()->GetVobListNpcs()->Get(zRand(npcNum));
								
								if (zRand() & 1) {
									GetNewsManager()->CreateNews(185,FALSE,npc1,oCNpc::player,npc2,FALSE);
								} else {
									GetNewsManager()->CreateNews(185,FALSE,npc1,npc2,oCNpc::player,FALSE);								
								}
							}
							}*/
							break;

	default				:	return FALSE;
							break;
	}
	return TRUE;
}

zBOOL oCGame :: IA_TestWay(int key)
{
	static int wpnr = 0;
	static zSTRING vobname = "A";
	static zCWaypoint *mwp1, *mwp2;
	
//	int x,y;
	zCVobWaypoint	*vobwp;
	zCWaypoint		*wp;
	zCView		*in;
	zSTRING			s;

	switch (key) {

		case KEY_N			:	// Create New Waypoint at this Position
								vobwp = zNEW(zCVobWaypoint)	();
								vobwp -> SetVobName			(vobname);
								GetWorld()->AddVob(vobwp);
								vobwp -> SetCollDet			(FALSE);
								vobwp -> SetPositionWorld	(oCNpc::player -> GetPositionWorld());
								vobwp -> SetHeadingAtWorld	(oCNpc::player->GetAtVectorWorld());   // [Moos] 20.12.00 Anpassung an Vob-Änderung

								mwp1 = wp = zfactory->CreateWaypoint();
								wp -> Init		(vobwp);
								wp -> SetName	(vobname);
								vobname[0]++;
								GetWorld()->GetWayNet()->InsertWaypoint(wp);
								break;
		case KEY_1			:	wp	 = GetWorld()->GetWayNet()->GetNearestWaypoint(oCNpc::player->GetPositionWorld());
								if (wp) {
									zCView::PrintDebug("< Select WP1 "+wp->GetName()+">\n");
								}
								mwp1 = wp;
								break;
		case KEY_2			:	wp	 = GetWorld()->GetWayNet()->GetNearestWaypoint(oCNpc::player->GetPositionWorld());
								if (wp) {
									zCView::PrintDebug("< Select WP2 "+wp->GetName()+">\n");
								}
								mwp2 = wp;
								break;
		case KEY_C			:	// Create WP + Way
								if (mwp1) {
									vobwp = zNEW(zCVobWaypoint)	();
									vobwp -> SetVobName			(vobname);
									GetWorld()->AddVob(vobwp);
									vobwp -> SetCollDet			(FALSE);
									vobwp -> SetPositionWorld	(oCNpc::player -> GetPositionWorld());
									vobwp -> SetHeadingAtWorld	(oCNpc::player->GetAtVectorWorld());   // [Moos] 20.12.00 Anpassung an Vob-Änderung
									
									mwp2 = wp = zfactory->CreateWaypoint();
									wp -> Init		(vobwp);
									wp -> SetName	(vobname);
									vobname[0]++;
									GetWorld()->GetWayNet()->InsertWaypoint(wp);
									GetWorld()->GetWayNet() -> CreateWay (mwp1,mwp2);								
									mwp1 = mwp2;
								}
								break;
		case KEY_W			:	if (zinput->KeyPressed(KEY_LCTRL)) {
									zCView::PrintDebug("< Waynet - Mode aus >\n");
									game_editwaynet = FALSE;
								} else {
									if ((mwp1) && (mwp2)) {
										GetWorld()->GetWayNet() -> CreateWay (mwp1,mwp2);
									}
								}
								break;
		case KEY_B			:	if (mwp1) {
									in = zNEW(zCView)(0,0,2048,screen->FontY());
									screen->InsertItem(in);
									s = mwp1-> GetName();
									s = in  -> Input(30,s);
									mwp1 -> SetName (s);
									vobwp = mwp1->GetVob();
									if (vobwp) vobwp->SetVobName(s);
									screen->RemoveItem(in);
									delete(in);
								}							
								break;
		case KEY_E			:	if (mwp1) {
									in = zNEW(zCView)(0,0,2048,screen->FontY());
									screen->InsertItem(in);
									//s = mwp1 -> GetSpecialString();
									s = in -> Input(8,s);
									//mwp1 -> SetSpecialString(s);
									screen->RemoveItem(in);
									delete(in);
								}							
								break;
		case KEY_D			:	if (zinput->KeyPressed(KEY_LCTRL)) {
									GetWorld()->GetWayNet()->DeleteWaypoint(mwp1);	
								} else if (zinput->KeyPressed(KEY_LSHIFT)) {
									GetWorld()->GetWayNet()->DeleteWay(mwp1,mwp2);	
								}
								break;
		case KEY_A			:	GetWorld()->GetWayNet() -> CorrectHeight();
								break;
		default				:	return FALSE;

	}
	return TRUE;
}

