/******************************************************************************** 
 
     $Workfile:: oNPC.cpp             $                $Date:: 24.04.01 17:33   $
     $Revision:: 644                  $             $Modtime:: 21.04.01 15:31   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNPC.cpp $
 * 
 * 644   24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 642   16.03.01 16:24 Wohlers
 * 
 * 641   15.03.01 20:18 Wohlers
 * 
 * 640   14.03.01 20:16 Wohlers
 * 
 * 639   14.03.01 18:01 Wohlers
 * 
 * 638   14.03.01 15:47 Speckels
 * 
 * 637   14.03.01 15:42 Wohlers
 * 
 * 636   14.03.01 15:41 Wohlers
 * 
 * 635   13.03.01 18:36 Wohlers
 * Patches 1.07 1.Teil
 * 
 * 634   16.02.01 19:16 Wohlers
 * Waffe aus dem Laufen ziehen/wegstecken reagiert jetzt auf Loslassen der
 * "nach vorne" Taste
 * 
 * 633   16.02.01 16:07 Moos
 * Map-Hotkey-Fix
 * 
 * 632   16.02.01 14:08 Moos
 * 
 * 631   16.02.01 2:21 Edenfeld
 * Im ZS_Dead werden alle Perceptions des NPCs gel�scht. Behebt ZS_Zapped
 * H�nger beim Blitz Spruch
 * 
 * 630   15.02.01 22:13 Moos
 * SurfaceAlign-Aktivierungsfix
 * 
 * 629   15.02.01 19:42 Wohlers
 * 
 * 628   15.02.01 13:21 Moos
 * Durch Fixes in oCMagic unn�tig gewordenen Hack entfernt
 * 
 * 627   15.02.01 1:43 Wohlers
 * Kampftuning Versuch 1
 * 
 * 626   14.02.01 23:12 Speckels
 * zerr-Warnings in Makros verwandelt
 * 
 * 625   14.02.01 21:01 Wohlers
 * 
 * 624   13.02.01 19:11 Wohlers
 * 
 * 623   13.02.01 17:05 Moos
 * Diego-Bewegt-Sich-Im-OC-keinen-Millimeter-wegen-H�henangst-Fix
 * 
 * 622   13.02.01 11:38 Moos
 * vobList- Leakfix
 * 
 * 621   12.02.01 19:04 Wohlers
 * Von Manuel: Seltsamer Compilierungsfehler behoben
 * 
 * 620   12.02.01 17:54 Moos
 * Leakfix
 * 
 * 619   12.02.01 16:28 Moos
 * 
 * 618   11.02.01 15:58 Wohlers
 * 
 * 617   10.02.01 23:15 Speckels
 * 
 * 616   10.02.01 20:48 Wohlers
 * 
 * 615   9.02.01 22:02 Moos
 * Lakfix in der Wahrnehmung
 * 
 * 614   9.02.01 20:49 Wohlers
 * 
 * 613   9.02.01 18:12 Moos
 * 
 * 612   9.02.01 17:56 Wohlers
 * Finishing Move Ani Bug gefixed.
 * 
 * 611   8.02.01 21:48 Wohlers
 * 
 * 610   8.02.01 21:26 Wohlers
 * 
 * 609   8.02.01 19:38 Keskenti
 * 
 * 608   8.02.01 19:06 Wohlers
 * 
 * 607   8.02.01 18:53 Wohlers
 * 
 * 606   8.02.01 18:23 Moos
 * 
 * 600   7.02.01 20:15 Keskenti
 * 
 * 599   7.02.01 19:37 Keskenti
 * 
 * 598   7.02.01 12:53 Moos
 * 
 * 597   6.02.01 19:24 Moos
 * 
 * 596   6.02.01 19:09 Keskenti
 * 
 * 595   6.02.01 15:20 Keskenti
 * 
 * 594   6.02.01 14:48 Speckels
 * 
 * 593   6.02.01 11:43 Moos
 * 
 * 592   6.02.01 4:40 Speckels
 * 
 * 591   6.02.01 4:12 Speckels
 * 
 * 590   6.02.01 3:39 Speckels
 * 
 * 589   6.02.01 0:23 Speckels
 * 
 * 588   5.02.01 20:19 Wohlers
 * 
 * 587   5.02.01 16:03 Keskenti
 * 
 * 586   5.02.01 15:02 Moos
 * 
 * 585   2.02.01 23:57 Edenfeld
 * 
 * 584   2.02.01 18:57 Moos
 * 
 * 583   2.02.01 13:04 Moos
 * 
 * 582   1.02.01 19:01 Wohlers
 * 
 * 581   1.02.01 18:14 Keskenti
 * 
 * 580   1.02.01 15:26 Wohlers
 * 
 * 579   31.01.01 21:50 Wohlers
 * 
 * 578   31.01.01 20:46 Wohlers
 * 
 * 577   31.01.01 20:18 Wohlers
 * 
 * 576   31.01.01 20:00 Moos
 * 
 * 575   31.01.01 12:13 Moos
 * 
 * 574   30.01.01 19:15 Wohlers
 * 
 * 573   30.01.01 19:11 Wohlers
 * 
 * 572   30.01.01 18:57 Keskenti
 * 
 * 571   30.01.01 16:56 Wohlers
 * 
 * 570   30.01.01 15:01 Moos
 * 
 * 569   30.01.01 13:48 Moos
 * 
 * 568   29.01.01 20:29 Wohlers
 * 
 * 567   29.01.01 20:19 Moos
 * 
 * 566   29.01.01 19:09 Moos
 * 
 * 565   29.01.01 18:47 Moos
 * 
 * 564   29.01.01 17:06 Keskenti
 * 
 * 563   29.01.01 14:09 Moos
 * 
 * 562   29.01.01 13:28 Keskenti
 * 
 * 561   29.01.01 13:28 Keskenti
 * 
 * 560   29.01.01 13:20 Keskenti
 * 
 * 559   29.01.01 13:16 Moos
 * 
 * 558   29.01.01 11:57 Keskenti
 * 
 * 557   28.01.01 21:12 Moos
 * 
 * 556   28.01.01 20:17 Moos
 * 
 * 555   28.01.01 17:50 Wohlers
 * 
 * 554   28.01.01 14:31 Wohlers
 * 
 * 553   27.01.01 23:09 Wohlers
 * 
 * 552   27.01.01 23:00 Wohlers
 * 
 * 551   27.01.01 20:55 Wohlers
 * 
 * 550   27.01.01 20:21 Wohlers
 * 
 * 549   27.01.01 16:39 Wohlers
 * 
 * 548   26.01.01 18:26 Wohlers
 * 
 * 547   26.01.01 18:04 Wohlers
 * 
 * 546   26.01.01 16:05 Moos
 * 
 * 545   26.01.01 15:02 Moos
 * 
 * 544   26.01.01 13:08 Moos
 * 
 * 543   25.01.01 23:33 Speckels
 * 
 * 542   25.01.01 19:53 Keskenti
 * 
 * 541   25.01.01 19:02 Moos
 * 
 * 540   25.01.01 18:20 Wohlers
 * 
 * 539   25.01.01 17:53 Moos
 * 
 * 538   25.01.01 17:27 Wohlers
 * 
 * 537   25.01.01 17:24 Keskenti
 * 
 * 536   25.01.01 16:04 Moos
 * 
 * 535   25.01.01 14:48 Moos
 * 
 * 534   25.01.01 14:23 Wohlers
 * 
 * 533   24.01.01 22:14 Wohlers
 * 
 * 532   24.01.01 16:45 Wohlers
 * 
 * 531   24.01.01 14:57 Moos
 * 
 * 530   23.01.01 21:55 Wohlers
 * 
 * 529   23.01.01 21:02 Wohlers
 * 
 * 528   23.01.01 19:12 Keskenti
 * 
 * 527   23.01.01 19:02 Wohlers
 * 
 * 526   23.01.01 16:22 Moos
 * 
 * 525   23.01.01 15:46 Moos
 * 
 * 524   23.01.01 15:20 Moos
 * 
 * 523   23.01.01 12:04 Moos
 * 
 * 522   22.01.01 23:08 Wohlers
 * 
 * 521   22.01.01 22:38 Wohlers
 * 
 * 520   22.01.01 20:01 Moos
 * 
 * 519   22.01.01 13:09 Moos
 * 
 * 518   19.01.01 15:48 Wohlers
 * 
 * 517   18.01.01 23:36 Speckels
 * 
 * 516   18.01.01 23:36 Wohlers
 * 
 * 515   18.01.01 23:19 Speckels
 * 
 * 514   18.01.01 16:53 Keskenti
 * 
 * 513   18.01.01 14:49 Moos
 * 
 * 512   18.01.01 2:00 Wohlers
 * 
 * 511   18.01.01 0:06 Edenfeld
 * 
 * 510   17.01.01 21:51 Wohlers
 * 
 * 509   17.01.01 17:59 Wohlers
 * 
 * 508   17.01.01 16:57 Keskenti
 * 
 * 507   17.01.01 16:41 Keskenti
 * 
 * 505   17.01.01 16:33 Wohlers
 * 
 * 504   17.01.01 14:06 Keskenti
 * 
 * 503   16.01.01 19:23 Moos
 * 
 * 502   16.01.01 18:04 Wohlers
 * 
 * 501   16.01.01 15:24 Keskenti
 * 
 * 500   16.01.01 14:18 Wohlers
 * 
 * 499   15.01.01 18:39 Keskenti
 * 
 * 498   15.01.01 17:12 Wohlers
 * 
 * 497   12.01.01 22:45 Hildebrandt
 * oCCollObjectCharacter durch zCCollObjectCharacter ersetzt (fuers
 * erste..)
 * 
 * 496   12.01.01 21:01 Edenfeld
 * 
 * 495   12.01.01 16:54 Edenfeld
 * 
 * 494   12.01.01 15:04 Moos
 * 
 * 493   12.01.01 12:38 Moos
 * 
 * 492   12.01.01 10:23 Keskenti
 * 
 * 491   11.01.01 17:37 Wohlers
 * 
 * 490   11.01.01 16:10 Keskenti
 * 
 * 489   11.01.01 0:45 Keskenti
 * 
 * 488   10.01.01 17:34 Wohlers
 * 
 * 487   10.01.01 16:56 Wohlers
 * 
 * 486   10.01.01 15:01 Speckels
 * 
 * 484   9.01.01 22:09 Speckels
 * 
 * 483   9.01.01 20:22 Wohlers
 * 
 * 482   9.01.01 17:59 Speckels
 * 
 * 481   8.01.01 21:16 Wohlers
 * 
 * 480   8.01.01 18:48 Speckels
 * 
 * 479   8.01.01 16:37 Wohlers
 * 
 * 478   8.01.01 15:37 Wohlers
 * 
 * 477   8.01.01 14:55 Wohlers
 * 
 * 476   20.12.00 17:52 Wohlers
 * 
 * 475   20.12.00 17:40 Speckels
 * 
 * 474   20.12.00 17:18 Speckels
 * 
 * 473   20.12.00 17:13 Moos
 * 
 * 472   20.12.00 14:45 Speckels
 * 
 * 471   20.12.00 14:30 Speckels
 * 
 * 470   20.12.00 14:33 Keskenti
 * 
 * 469   20.12.00 14:18 Keskenti
 * 
 * 468   20.12.00 14:08 Speckels
 * 
 * 467   20.12.00 0:03 Wohlers
 * 
 * 466   19.12.00 20:46 Speckels
 * 
 * 465   19.12.00 18:57 Keskenti
 * 
 * 464   19.12.00 18:22 Keskenti
 * 
 * 463   19.12.00 18:14 Keskenti
 * 
 * 462   19.12.00 17:38 Wohlers
 * 
 * 461   19.12.00 17:15 Keskenti
 * 
 * 460   19.12.00 13:40 Wohlers
 * 
 * 459   19.12.00 12:06 Keskenti
 * 
 * 458   18.12.00 17:38 Speckels
 * 
 * 457   18.12.00 14:59 Keskenti
 * 
 * 456   15.12.00 17:50 Keskenti
 * 
 * 455   15.12.00 16:00 Keskenti
 * 
 * 454   14.12.00 20:45 Wohlers
 * 
 * 453   11.12.00 20:36 Wohlers
 * 
 * 452   8.12.00 17:32 Keskenti
 * 
 * 451   8.12.00 13:57 Keskenti
 * 
 * 450   7.12.00 22:14 Keskenti
 * 
 * 449   7.12.00 20:11 Moos
 * 
 * 448   6.12.00 15:53 Keskenti
 * 
 * 447   6.12.00 12:27 Speckels
 * 
 * 446   5.12.00 21:57 Speckels
 * 
 * 445   5.12.00 19:49 Keskenti
 * 
 * 444   5.12.00 18:35 Speckels
 * 
 * 443   1.12.00 19:21 Keskenti
 * 
 * 442   1.12.00 17:08 Keskenti
 * 
 * 441   1.12.00 13:00 Keskenti
 * 
 * 440   1.12.00 3:07 Speckels
 * 
 * 439   30.11.00 19:32 Speckels
 * 
 * 435   29.11.00 21:57 Speckels
 * 
 * 434   29.11.00 17:20 Wohlers
 * 
 * 433   29.11.00 12:52 Speckels
 * 
 * 432   28.11.00 16:57 Keskenti
 * 
 * 431   27.11.00 18:32 Keskenti
 * 
 * 430   27.11.00 14:05 Moos
 * 
 * 429   24.11.00 15:41 Wohlers
 *********************************************************************************/

#include "zCore.h"

#include "zParser.h"
#include "zview.h"
#include "z3D.h"
#include "zVob.h"
#include "zFile3D.h"
#include "zOption.h"
#include "zRenderer.h"
#include "zAlgebra.h"
#include "zModel.h"
#include "zMorphMesh.h"
#include "zParticle.h"
#include "zSound.h"
#include "zPhysics.h"
#include "zSoundMan.h"
#include "zMusic.h"
#include "zBuffer.h"
#include "zArchiver.h"
#include "zAICamera.h"
#include "zCCSPlayer.h"
#include "zInput_Win32.h"
#include "zEventMan.h"
#include "zWayNet.h"
#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>
#include <oCollisionObjectMiscChar.h>
#include <zSparseArray.h>

#include "oNPC.h"
#include "oItem.h"
#include "oText.h"
#include "oWorld.h"
#include "oMagic.h"
#include "oMission.h"
#include "oAIShoot.h"
#include "oMobInter.h"
#include "oInfo.h"
#include "oAIHuman.h"
#include "oAniCtrl.h"
#include "oAIShoot.h"
#include "oFocus.h"
#include "oDialog.h"
#include "oGame.h"
#include "oGuilds.h"
#include "oNpcStates.h"
#include "oInventory.h"
#include "oNpcMessages.h"
#include "oSvm.h"
#include "oCSPlayer.h"
#include "oMenu_Status.h"
//#include "oMenu_Help.h"
#include "oPlayerInfo.h"
//#include "oViewStatusBar.h"
#include "oPortals.h"
#include "oSpawn.h"
#include "oCSManager.h"
#include "oMagFrontier.h"
#include "oVisFX.h"
//#include "zAIPlayer.h"

//
/*
#include "zViewBase.h"
#include "zViewObject.h"
#include "zViewDraw.h"
#include "zViewFX.h"
#include "zFonts.h"
#include "zViewPrint_Font.h"
#include "zViewPrint.h"
#include "zView.h"
#include "zViewDialog.h"
#include "zViewDialogChoice.h"
#include "oViewDialogItem.h"
#include "oViewDialogInventory.h"
#include "oViewDialogTrade.h"
*/
#include "oIncDialogs.h"
#include "oInformationManager.h"
//

#include "zAccount.h"

// diverse Konstanten

const zSTRING NPC_TALK_ANI				= "VISEME";

const zSTRING BS_NAMES[BS_MAX] = {
	"BS_STAND",						"BS_WALK",			"BS_SNEAK",			"BS_RUN",				"BS_SPRINT",			"BS_SWIM",
	"BS_CRAWL",						"BS_DIVE",			"BS_JUMP",			"BS_CLIMB",				"BS_FALL",
	"BS_SIT",						"BS_LIE",			"BS_INVENTORY",		"BS_ITEMINTERACT",		"BS_MOBINTERACT",
	"BS_MOBINTERACT_INTERRUPT",		"BS_TAKEITEM",		"BS_DROPITEM",		"BS_THROWITEM",			"BS_PICKPOCKET"	,				
	"BS_STUMBLE",					"BS_UNCONSCIOUS",	"BS_DEAD",			"BS_AIMNEAR",			"BS_AIMFAR",
	"BS_HIT",						"BS_PARADE",
	"BS_CASTING",					"BS_PETRIFIED",		"BS_CONTROLLING" };

const zSTRING BS_MOD_NAMES[6] = {
	"BS_MOD_HIDDEN",
	"BS_MOD_DRUNK",
	"BS_MOD_NUTS",
	"BS_MOD_BURNING",
	"BS_MOD_CONTROLLED",
	"BS_MOD_TRANSFORMED"
};

const zSTRING NPC_NODE_RIGHTHAND	= "ZS_RIGHTHAND";
const zSTRING NPC_NODE_LEFTHAND		= "ZS_LEFTHAND";
const zSTRING NPC_NODE_SWORD		= "ZS_SWORD";
const zSTRING NPC_NODE_LONGSWORD	= "ZS_LONGSWORD";
const zSTRING NPC_NODE_BOW			= "ZS_BOW";
const zSTRING NPC_NODE_CROSSBOW		= "ZS_CROSSBOW";
const zSTRING NPC_NODE_SHIELD		= "ZS_SHIELD";
const zSTRING NPC_NODE_HELMET		= "ZS_HELMET";
const zSTRING NPC_NODE_JAWS			= "ZS_JAWS";
const zSTRING NPC_NODE_TORSO		= "ZS_TORSO";						// Torso, kein wirkliches Slot

const zSTRING	npcStatesPrg	[NPC_AISTATE_PRG_MAX] = 
		{	"ZS_NONE"	,"ZS_NONE", 
			"ZS_ANSWER", "ZS_DEAD", "ZS_UNCONSCIOUS", "ZS_FADEAWAY","ZS_FOLLOW"	};

extern void NotifyInfoToSpy( char* pszMethod, char* pszOutput, char* pszStatus );

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

const int	NPC_VOB_CHECK			=	 3 * 1000;							// alle 3 Sekunden
const int	NPC_VOB_CHECK_RANGE		= 4000 * 4000;							// 40m Entfernung vom Spieler, 
const zREAL	NPC_FADEAWAY_TIME		=	 5 * 1000;							
const float ASSESS_THREAT_TIME		=  1.0 * 1000;
																			
//																			
//	CODECHANGE [ROMAN]														
//																			
const zREAL	NPC_MESSAGE_WIN_TIME	=		-1.0f;							//
																			//	fTime Values :	>=  0.0f	close after specified time
																			//					== -1.0f	close after char-count * VIEW_CHAR_TIME
																			//					== -2.0f	will be closed manually
																			//
static zREAL  NPC_TALK_TIME_MIN		= 1000.0f;
static zREAL  NPC_TALK_TIME_MAX		= 8000.0f;
static zCOLOR NPC_COLOR_TALK_PC		= zCOLOR( 0xff, 0xff, 0xff, 0xff );
static zCOLOR NPC_COLOR_TALK_NPC	= zCOLOR( 0xff, 0xff, 0x00, 0xff );
static zCOLOR NPC_COLOR_AMBIENT		= zCOLOR( 0xff, 0xff, 0xff, 0xff );
static zCOLOR NPC_COLOR_CINEMA		= zCOLOR( 0xff, 0xff, 0xff, 0xff );
static zCOLOR NPC_COLOR_NOISE		= zCOLOR( 0xff, 0x3f, 0x00, 0xff );
static zCOLOR NPC_COLOR_CHOICE_YES	= zCOLOR( 0xff, 0xff, 0x00, 0xff );
static zCOLOR NPC_COLOR_CHOICE_NO	= zCOLOR( 0x7f, 0x7f, 0x7f, 0xff );
//
//	CODECHANGE [ROMAN] END
//

zBOOL oCNpc :: godmode					= FALSE;
zBOOL oCNpc :: ai_disabled				= FALSE;
zREAL oCNpc :: ai_messagesSkip			= 0.0f;		// on - no timer
zREAL oCNpc :: ai_messagesSkipTimer		= 0.0f;		// on - no timer
zREAL oCNpc :: ai_scriptStateSkip		= 0.0f;		// on - no timer
zREAL oCNpc :: ai_scriptStateSkipTimer	= 0.0f;		// on - no timer
zBOOL oCNpc :: ai_baseEnabled			= TRUE;		// on
zBOOL oCNpc :: isEnabledTalkBox			= TRUE;
zBOOL oCNpc :: isEnabledTalkBoxPlayer	= TRUE;
zBOOL oCNpc :: isEnabledTalkBoxAmbient	= FALSE;
zBOOL oCNpc :: isEnabledTalkBoxNoise	= FALSE;
zBOOL oCNpc :: s_bTargetLocked			= FALSE;

//zBOOL oCNpc :: ai_extendedRays			= TRUE;

zREAL percRange	[NPC_PERC_MAX];

// Der Spieler
oCNpc*	oCNpc :: player						= NULL;
zBOOL	oCNpc :: s_bEnabledDialogCamStop	= FALSE;
oCNpc*	oCNpc :: dontArchiveThisNpc			= NULL;

// H�ufig gebrauchte String-Konstanten
static zSTRING S_ITLSTORCHBURNING("ITLSTORCHBURNING");

// ****************************
// Parser - Vars
// ****************************
zREAL NPC_ANGRY_TIME		=	30 * 1000;

static zSTRING percNames[NPC_PERC_MAX] = 
					{
						// * active perception *				
						"NONE",								"ASSESSPLAYER"			/*=	  1*/,
						"ASSESSENEMY"			/*=   2*/,	"ASSESSFIGHTER"			/*=   3*/,		
						"ASSESSBODY"			/*=   4*/,	"ASSESSITEM	"			/*=   5*/,		
						"ASSESSMURDER"			/*=	  6*/,	
						// * passive perception *				
															"ASSESSDEFEAT"			/*=	  7*/,
						"ASSESSDAMAGE"			/*=	  8*/,	"ASSESSOTHERSDAMAGE"	/*=	  9*/,		
						"ASSESSTHREAT"			/*=  10*/,	"ASSESSREMOVEWEAPON"	/*=  11*/,		
						"OBSERVEINTRUDER"		/*=  12*/,	"ASSESSFIGHTSOUND"		/*=  13*/,		
						"ASSESSQUIETSOUND"		/*=  14*/,	"ASSESSWARN"			/*=  15*/,		
						"CATCHTHIEF"			/*=  16*/,	"ASSESSTHEFT"			/*=  17*/,		
						"ASSESSCALL"			/*=  18*/,	"ASSESSTALK"			/*=  19*/,		
						"ASSESSGIVENITEM"		/*=  20*/,	"ASSESSFAKEGUILD"		/*=  21*/,		
						"MOVEMOB"				/*=  22*/,	"MOVENPC"				/*=  23*/,			
						"DRAWWEAPON"			/*=  24*/,	"OBSERVESUSPECT"		/*=  25*/,			
						"NPCCOMMAND"			/*=  26*/,	"ASSESSMAGIC"			/*=  27*/,			
						"ASSESSSTOPMAGIC"		/*=  28*/,	"ASSESSCASTER"			/*=  29*/,		  
						"ASSESSSURPRISE"		/*=  30*/,	"ASSESSENTERROOM"		/*=  31*/,			
						"ASSESSUSEMOB"			/*=  32*/,			
					};

// ****************************
// Statics for Fighting-system
// ****************************
int oCNpc :: angle_near		= 40;		// Winkel fuer Auto-Heading im Nahkampf (+-)
int oCNpc :: angle_far_up	= 45;		// Hoehenwinkel fuer Auto-Heading Fernkampf (+-)
int oCNpc :: angle_far_side	= 30;		// Seitenwinkel fuer Auto-Heading Fernkampf (+-)

// *******************************
// Statics for Player-Perceptions
// *******************************
int playerPercAssessMagic		= -1;
int playerPercAssessStopMagic	= -1;

static zBOOL		parserNpcRefsDone = FALSE;
static zCArray<int> gParserNpcReferenceList(1200);
static float		s_assessThreatCounter		= ASSESS_THREAT_TIME;
static oCNpc*		s_assessThreatLastEnemy	= NULL;


zBOOL g_bDontKillOUSound	= FALSE;


// [EDENFELD] 1.09b Talent Archive Version hochgesetzt
zCLASS_DEFINITION	( oCNpcTalent, zCObject	, 0, 1 )

oCNpcTalent::oCNpcTalent()
{
	m_talent	= NPC_TAL_UNKNOWN;
	m_value		= -1;
	m_skill		= 0;
};

oCNpcTalent::~oCNpcTalent()
{	
};

void oCNpcTalent::CreateTalentList(zCArray<oCNpcTalent*>* talentList)
{
	talentList->DeleteList();
	talentList->AllocAbs(oTEnumNpcTalent::NPC_TAL_MAX);
	for (int i=0;i<oTEnumNpcTalent::NPC_TAL_MAX;i++) talentList->Insert(0);	
};

// Archiver

void oCNpcTalent::Archive(zCArchiver &arc)
{
	zCObject::Archive(arc);
	arc.WriteInt("talent"	,m_talent);
	arc.WriteInt("value"	,m_value);	
	arc.WriteInt("skill"	,m_skill);	
};	

void oCNpcTalent::Unarchive	(zCArchiver &arc)
{
	zCObject::Unarchive(arc);
	int talent;
	arc.ReadInt("talent"	,talent);		m_talent = oTEnumNpcTalent(talent);
	arc.ReadInt("value"		,m_value);	
	arc.ReadInt("skill"		,m_skill);	
};


int BitToNumber ( int value )
{
	if (value==0) return(0);
	for (int i=0; i<64; i++) {
		if (value & 1) return i;
		value = value >> 1;
	}
	return(0);
}


/* ----------------------------------------------------------------------
	
    SafeAddRef()	

    Macht ein AddRef auf den angegebenen Vob und achtet dabei auf
    die Vobtree-Problematik. R�ckgabawert muss f�r SafeRelease aufgehoben werden.

	27.11.2000	[Moos]	
                Erzeugt, damit Fackeln und Runen gleichzeitig funktionnieren


   ---------------------------------------------------------------------- */

static zBOOL SafeAddRef(zCVob *vob){
    int refbefore = vob->GetRefCtr();
    vob->AddRefVobSubtree();

    zBOOL wasVobTree = (vob->GetRefCtr() != refbefore);

    if (!wasVobTree) // [Moos] Dann hat das Vob keinen Subtree. Mache normales AddRef
        vob->AddRef();
    
    return wasVobTree;
}

/* ----------------------------------------------------------------------
	
    SafeRelease()	

    Macht ein Release auf den angegebenen Vob und achtet dabei auf
    die Vobtree-Problematik. Zweites Argument muss der R�ckgabewert
    von SafeAddRef() sein.

	27.11.2000	[Moos]	
                Erzeugt, damit Fackeln und Runen gleichzeitig funktionnieren


   ---------------------------------------------------------------------- */

static void SafeRelease(zCVob *vob, zBOOL wasVobTree){
    if (vob){
        int refbefore = vob->GetRefCtr();

        if (wasVobTree)
            vob->ReleaseVobSubtree();

        if (vob->GetRefCtr() == refbefore) // [Moos] Dann hat das Vob keinen Subtree. Mache normales Release
            vob->Release();
    }
}

/*--------------------------------------------------------------------------

    TNpcSlot::SetVob() und ClearVob()

 

    20.10.2000       [Moos]

                       Erzeugt, um RefCtr-�rger zu vermeiden

--------------------------------------------------------------------------*/

void TNpcSlot::SetVob(oCVob *v){
    if (vob == v)
        return;

    ClearVob();

    vob = v;

/*
    if (!vob)
        return;

    int refbefore = vob->GetRefCtr();
    vob->AddRefVobSubtree();

    wasVobTreeWhenInserted = (vob->GetRefCtr() != refbefore);

    if (!wasVobTreeWhenInserted) // [Moos] Dann hat das Vob keinen Subtree. Mache normales AddRef
        vob->AddRef();
*/
    wasVobTreeWhenInserted = SafeAddRef(vob);

    ogame->GetGameWorld()->InsertVobInWorld(vob);
}


void   TNpcSlot::ClearVob(){
    if (vob){
        /*
        int refbefore = vob->GetRefCtr();

        if (wasVobTreeWhenInserted)
            vob->ReleaseVobSubtree();

        if (vob->GetRefCtr() == refbefore) // [Moos] Dann hat das Vob keinen Subtree. Mache normales Release
            vob->Release();
        */

        SafeRelease(vob, wasVobTreeWhenInserted);

        vob = NULL;
    }
}



/*--------------------------------------------------------------------------

    TActiveInfo::TActiveInfo()

    18.1.2001       [Moos]

                       Erzeugt

--------------------------------------------------------------------------*/

oCNpc::TActiveInfo::TActiveInfo(const oCNpc *n)
:modified(FALSE), putTorchBackInHand(FALSE) , changeTorchAni(FALSE), changeTorchAniTo(FALSE)//, npc ((oCNpc *)n)
{
//    if (npc)
//    {
//        npc->SetVisual(NULL);
//        npc->UnShrink();
//    }
}

oCNpc::TActiveInfo::~TActiveInfo()
{
//    if (npc)
//        npc->Shrink();
}



/*--------------------------------------------------------------------------

    oCNpc::GetActiveInfo() und GetActiveInfoWritable()

    Besorgen die Daten des NPC, die nur dann vorhanden sein sollen, wenn der NPC aktiv ist

    18.1.2001       [Moos]

                     Erzeugt

--------------------------------------------------------------------------*/

static zCCacheAsk<const oCNpc *, oCNpc::TActiveInfo> s_activeInfoCache(13, 100);


const oCNpc::TActiveInfo * oCNpc::GetActiveInfo()          const {
    return s_activeInfoCache[this];
}


oCNpc::TActiveInfo * oCNpc::GetActiveInfoWritable()        const {
    TActiveInfo *info = s_activeInfoCache[this];
    info->modified    = TRUE;

    return info;
}



// ************************************************************
//  oCShrinkHelper: Class to help shrink/unshrink a NPC
// ************************************************************

class oCShrinkHelper{
public:
    oCNpc *npc;

    oCShrinkHelper(const oCNpc *n): npc((oCNpc *)n){
        if (npc)
        {
            npc->SetVisual(NULL);
            npc->UnShrink();
        }
    }

    ~oCShrinkHelper()
    {
        if (npc)
            npc->Shrink();
    }


	zBOOL DontDelete(){
        // L�sche ihn nicht, wenn er noch in der Welt oder der letzte seiner Art (ModelPrototype) ist.

		return  npc && ( npc->GetHomeWorld() ||
                         ( npc->GetModel() && npc->GetModel()->GetModelProto() && npc->GetModel()->GetModelProto()->GetRefCtr() > 1 ) );
	}
};


static zCCacheAsk<const oCNpc *, oCShrinkHelper> s_shrinkCache(101, 2000);


/*--------------------------------------------------------------------------

    oCNpc::(Un)Shrink()

    Beseitigt oder restauriert alle Informationen, die bei inaktiven NSCs nicht
    ben�tigt werden. 

    22.01.2001       [Moos]

                    erzeugt


--------------------------------------------------------------------------*/

void oCNpc::Shrink(){
    if (!ogame)  // [Moos] whoops. Das sieht gef�hrich aus. Wahrscheinlich sind wir schon beim Abr�umen der statischen Objekte.
        return;

    SetVisual(NULL);

    activeOverlays.ShrinkToFit();

    if (GetHumanAI())
        GetHumanAI()->SetVob(this);
    DeleteHumanAI();


    SetCollisionObject(NULL);
	RemoveEffect(effect);
}

void oCNpc::UnShrink(){
    if (GetVisual() && GetHumanAI())
        return;

    static zBOOL recursion = FALSE;
    zERR_ASSERT_STRICT(!recursion);
    recursion = TRUE;

    // reinitiiere das Model:
	zCVob::SetVisual(GetMdsName());

	if (!GetVisual())
	{
		zERR_FAULT("NPC " + GetObjectName() + " [ " + GetName() + " ] has invalid visual name [ " + GetMdsName() + " ]."); 
		zCVob::SetVisual("Meatbug.mds");
        model_scale = zVEC3(1,1,1);
        if (!GetVisual())
            zERR_FATAL("Whoops. Default Visual not found.");
    }
    else{
    	InitModel();
        SetHead();
    }
    zCModel *model = GetModel();

	// [Wohlers] : Npc-Fading....
	model->SetLODFarDistance		(oCSpawnManager::GetInsertRange());
	model->SetLODNearFadeOutDistance(oCSpawnManager::GetInsertRange()-500);

    // overlays restaurieren
    int i;
    for (i=activeOverlays.GetNum()-1; i>=0; i--)
    {
        zSTRING ov = activeOverlays[i];
        if (!model->ApplyModelProtoOverlay(ov))
            activeOverlays.RemoveIndex(i);
    }

    model->SetModelScale(model_scale);
    model->SetFatness   (model_fatness);

    // Faustkampfmodus reaktivieren
    if (GetWeaponMode() == NPC_WEAPON_FIST)
    {
    	// evt. Waffe graphisch aus den Handslot loeschen
    	zCModelNodeInst *node = model -> SearchNode("ZS_RIGHTHAND");
    	if (node) model -> SetNodeVisual(node,NULL);
    }

	for (i=0; i<invSlot.GetNumInList(); i++) 
	{
        TNpcSlot *slot = invSlot[i];

        if (slot->name!=NPC_NODE_TORSO)
        {
			zCModelNodeInst* node	= model -> SearchNode( slot->name );
            if (node && slot->Vob()) 
			{
				oCItem* item = zDYNAMIC_CAST<oCItem>(slot->Vob());
				if (item) item->CreateVisual();

				// [EDENFELD] An dieser Stelle wird das Item nur noch vom Modelanimationssystem
				// als zCProgMesh-Visual am Ziel-Node gerendert.
				model -> SetNodeVisual( node, slot->Vob()->GetVisual() );

				SetItemEffectControledByModel(item, node, TRUE);
			}
        }
		else
		{
			oCItem* item = zDYNAMIC_CAST<oCItem>(slot->Vob());
			if (item) SetItemEffectControledByModel(item, 0, TRUE);
		}
    }

    if (!GetHumanAI())
        InitHumanAI();
    else
    {
        GetHumanAI()->SetVob(this);
        GetHumanAI()->SetWorld (ogame->GetWorld());  // setvob setzt diese auf NULL, wenn this noch nicht in der Welt ist
        GetHumanAI()->InitAnimations();              // ohne model wurden die falsch initialisiert
    }

    GetHumanAI()->SearchStandAni();

       
    // und das Kollisionsobjekt wieder beseitigen, damit es neu erzeugt werden muss und garantiert die Datan aus dem echten Model nimmt
    if (!GetInMovement())
    {
        SetCollisionObject(NULL);
        CreateCollisionObject();
    }

	if (GetHomeWorld()) AddEffect(effect);

    recursion = FALSE;

    zERR_ASSERT(GetModel() && GetHumanAI() && GetHumanAI()->GetModel() == GetModel());

    /*
    // Skill-Overlays kommen dazu:
    for (int i=talents.GetNum()-1; i>=0; i--)
    if (talents[i])
    {
		int setFightMode=-1;
		switch (talents[i]->GetTalent()) 
		{
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_1H		:	setFightMode = NPC_WEAPON_1HS;	break;
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_2H		:	setFightMode = NPC_WEAPON_2HS;	break;
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_BOW		:	setFightMode = NPC_WEAPON_BOW;	break;		
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_CROSSBOW	:	setFightMode = NPC_WEAPON_CBOW;	break;
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_ACROBAT	:	
						if (GetModel())		GetModel()   -> ApplyModelProtoOverlay("HUMANS_ACROBATIC.MDS");
						if (GetAnictrl())	    GetAnictrl() -> InitAnimations();
						break;
		}

        int skill = talents[i]->GetTalentSkill();
		if (skill > 0 && setFightMode>=0 && GetModel()) 
		{
			zSTRING ws = oCAniCtrl_Human::GetWeaponHitString(setFightMode);
			GetModel()->ApplyModelProtoOverlay("HUMANS_"+ws+"T"+zSTRING(skill)+".MDS");

			oCAniCtrl_Human *ac = GetAnictrl();
			if (ac) 
			{
				ac -> InitFightAnis(setFightMode);
				if (setFightMode == GetWeaponMode()) ac->SetFightAnis(setFightMode);		
			}
			
		} 
    }
    */
}



void oCNpc::AvoidShrink(int timeout){
    static zBOOL recursion=FALSE;
    if (recursion)
        return;

    if (mds_name.Length() <= 0)
        return;

    recursion = TRUE;
    s_shrinkCache[this];
    recursion = FALSE;
}


/*--------------------------------------------------------------------------

    oCNpc::Apply/RemoveOverlay()
 
    Setzt/entfernt Overlays und merkt sie sich, da das Model ja verlorengehen kann.

    22.01.2001       [Moos]

                    erzeugt


--------------------------------------------------------------------------*/

static int Hash(const zSTRING &s){
      int ret=0;
      int fak=1;
      for (int i = s.Length()-1; i>=0; i--)
    {
      ret += fak*s[i];
      fak *= 29;
    }

  return ret;
}

class zTOverlayIndex{
public:
  zSTRING overlayName;
  
  zTOverlayIndex(const zSTRING &s): overlayName(s){}
  zTOverlayIndex(const zTOverlayIndex &s): overlayName(s.overlayName){}

  int operator == (const zTOverlayIndex &b) const { return (overlayName == b.overlayName); }
};

// [EDENFELD] 1.09 �bertrag aus der Sequel Codebase
// k�nnte einen Bug fixen, der sich darin ��sserte, das Overlays teilweise einfach 
// entfernt wurden
//	[Bendlin] 2001-10-23
//
//	Hier wurde das Hash-Template f�r zSTRING mit zTOverlayIndex als Parameter �berschrieben
//	(mal davon abgesehen, das dies von VC eigentlich nicht kompiliert werden d�rfte...),
//	gehe ich davon aus, das hier beabsichtigt war, das Hash-Template f�r zTOverlayIndex
//	zu �berschreiben, welches im zCSparseArray von zTOverlayIndex benutzt werden soll.
//	Zur Sicherheit sind hier beide Hash-Templates definiert.
//
//inline void Hash<zSTRING>(const zTOverlayIndex *s, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb){
//	int h = Hash(s->overlayName);
//	Hash(&h, p, hasha, hashb);
//};
//
inline void Hash<zTOverlayIndex>(const zTOverlayIndex *s, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb){
    int h = Hash(s->overlayName);
    Hash(&h, p, hasha, hashb);
};

inline void Hash<zSTRING>(const zSTRING *s, zUINT32 p, zUINT32 &hasha, zUINT32 &hashb){
    int h = Hash(s);
    Hash(&h, p, hasha, hashb);
};


static zCSparseArray<zTOverlayIndex, zCModelPrototype*> s_overlayArray(13);



zBOOL oCNpc::ApplyOverlay  (const zSTRING &onParam)
{
	// Patch 1.07 : [Wohlers] : 13.03.01 : Codechange
	// Safety : Always uppern, da sonst doppelte Eintraege moeglich waeren.
	zSTRING on = onParam;
	on.Upper();
	// Codechange END

	// schaue nach, ob es vielleicht schon aktiv ist
    for (int i = activeOverlays.GetNum()-1; i>=0; i--)
        if (on == activeOverlays[i])
            return TRUE;

    if (!GetVisual()){
        activeOverlays.Insert(on);
        return TRUE;
    }

    zCModelPrototype **overlay = s_overlayArray[on];
    if (!overlay)
    {
        overlay = s_overlayArray.Insert(on);
        *overlay = zCModelPrototype::Load (on ,GetModel()->GetModelProto());	
        zERR_ASSERT(overlay && *overlay);
    }   

    if (!GetVisual() || GetModel()->ApplyModelProtoOverlay(*overlay)){
        activeOverlays.Insert(on);
        return TRUE;
    }

    return FALSE;
}


void oCNpc::RemoveOverlay (const zSTRING &onParam){

   	// Patch 1.07 : [Wohlers] : 13.03.01 : Codechange
	// Safety : Always uppern, da sonst doppelte Eintraege moeglich waeren.
	zSTRING on = onParam;
	on.Upper();
	// Codechange END

	int found = -1;

    for (int i = activeOverlays.GetNum()-1; i>=0; i--)
        if (on == activeOverlays[i])
            found = i;

    if (found >= 0)
    {
        activeOverlays.RemoveIndex(found);
        if (GetVisual())
            GetModel()->RemoveModelProtoOverlay(on);
    }
}


/*--------------------------------------------------------------------------

    oCNpc::SetModelScale/SetFatness()
 
    setzt die gleichnamigen Eigenschaften des Models

    22.01.2001       [Moos]

                    erzeugt


--------------------------------------------------------------------------*/

void oCNpc::SetModelScale (const zVEC3 &scale){
    model_scale = scale;
    if (GetVisual())
        GetModel()->SetModelScale(scale);
}

void oCNpc::SetFatness    (zREAL fat){
    model_fatness = fat;
    if (GetVisual())
        GetModel()->SetFatness(fat);

}

/*--------------------------------------------------------------------------

    oCNpc::oCNpc()

 

    28-Aug-00       [Roman Keskenti]

                      Added initialization for aiming variables


--------------------------------------------------------------------------*/

oCNpc :: oCNpc ()
{
	// Delete Parser Vars
	memset(&idx,0,(int)&parserEnd-(int)&idx);
	// InvSlots
	CreateInvSlot(NPC_NODE_RIGHTHAND);
	CreateInvSlot(NPC_NODE_LEFTHAND);
	CreateInvSlot(NPC_NODE_SWORD);
	CreateInvSlot(NPC_NODE_LONGSWORD);	
	CreateInvSlot(NPC_NODE_BOW);
	CreateInvSlot(NPC_NODE_CROSSBOW);
	CreateInvSlot(NPC_NODE_HELMET);		
	CreateInvSlot(NPC_NODE_TORSO);

	// Magic
	mag_book					= NULL;
	this->spellMana				= 0;
								
	// News / Info				
	news						= NULL;
	info						= NULL;
	askroutine					= FALSE;
	askbox						= NULL;
	askYes						= 0;
	askNo						= 0;
	curMission					= NULL;
								
	// Vobs						
	focus_vob					= NULL;
	enemy						= NULL;
	carry_vob					= NULL;
	bodyState					= 0;
	talkOther					= NULL;
								
	// Others					
	anictrl						= NULL;
	human_ai					= NULL;
	route						= NULL;
	fmode						= NPC_WEAPON_NONE;
	instanz						= -1;								
	guild = guildTrue			= NPC_GIL_NONE;
	fighttactic					= 0;
	spells						= 0;
	overlay_wounded				= FALSE;
	mad							= FALSE;
	drunk						= FALSE;
	drunk_heal					= 0;
	mad_heal					= 0;
	namenr						= 0;
	attitude					= NPC_ATT_NEUTRAL;
	tmp_attitude				= NPC_ATT_NEUTRAL;
	knowsPlayer					= 0;
	attTimer					= 0;
	selfDist					= 0.0f;
	voice						= 0;
	voicePitch					= 0;
	respawnOn					= FALSE;
	
	// timers					
	vobcheck_time				= 0;
	pickvobdelay				= 0;
	// Cutscenes
	// Sehr wichtig, dass hier nicht "rangeToPlayer" mit "0" initialisiert wird,
	// weil sonst beim ersten mal bei der CS die Range falsch sein kann und diese
	// gestartet wird.
	rangeToPlayer				= zREAL_MAX;	
	csAllowedAsRole				= TRUE;			// Codechange [Speckels]
	// Debug
	showaidebug					= FALSE;

	// Fire
	fireDamageTimer				= 0;		// Schaden sofort wirken lassen.
	fireDamage					= 0;
	fireVob						= NULL;
	inOnDamage					= FALSE;

	// Item Interaction
	interactMob					= NULL;
	interactItem				= NULL;
	interactItemCurrentState	= -1;
	interactItemTargetState		= 0;;

	swimtime					= 0.0f;
	divetime					= 0.0f;
	divectr						= 0.0f;
	
	// Trading
	trader						= NULL;
	tradeNpc					= NULL;
	
	// Messages
	csg							= NULL;
	lastLookMsg					= NULL;
	lastPointMsg				= NULL;

	parserEnd					= 0;
								
	// R�stungssystem			
	body_TexVarNr				= 0;
	body_TexColorNr				= 0;
	head_TexVarNr				= 0;
	teeth_TexVarNr				= 0;
								
	// Falldown					
	overrideFallDownHeight		= FALSE;
	fallDownHeight				= 500;
	fallDownDamage				= 0;
	canTalk						= TRUE;

    // model properties
    model_fatness               = 0;
    model_scale                 = zVEC3(1,1,1);

	//
	//	CODECHANGE [ROMAN]
	//
	this->InitDamage();
	//
	//	CODECHANGE [ROMAN] END
	//

	// FIXME : Brauche ich die noch ?
	script_aiprio				= 0;
	old_script_state			= 0;
	ai_disabled					= FALSE;
	showNews					= FALSE;
	autoremoveweapon			= FALSE;
	openinventory				= FALSE;
								
	// Kampf					
	fightRangeBase				= 0;
	fightRangeFist				= 0;
	fightRangeG					= 0;

	fight_waitTime				= 0.0f;
	fight_waitForAniEnd			= zMDL_ANI_ID_ILLEGAL;
	fight_lastStrafeFrame		= 0.0f;
	
	damageMul					= 1.0f;	// changed [dennis]
	voiceIndex					= NULL;	// changed [SPECKELS]
	
	// logical Sound
	soundType					= 0;
	soundVob					= NULL;

	// PerceptionInit
	for (int i=0; i<NPC_PERC_MAX; i++) { 
		percList[i].percID		= 0; 
		percList[i].percFunc	= -1; 
	}; 
	percActive					= 0;
	percActiveTime				= 0.0f;
	percActiveDelta				= 0.0f;	

	SetSpawnInRangeAllowed	(TRUE);
	
	// Regeneration defaults
	SetAttribute			(NPC_ATR_REGENERATEHP,	 600*1000);
	SetAttribute			(NPC_ATR_REGENERATEMANA, 600*1000);

	SetBodyState			(BS_STAND);

	// AI + Perception
	SetPerceptionTime		(5000);
	
	// Init Objects
	inventory2.		SetOwner(this);
	state.			SetOwner(this);

	RbtReset				();

	// Set Properties
	SetVobType				(zVOB_TYPE_NSC);

	// [HILDEBRANDT] erstmal wieder die zCCollObjectCharacter aktiviert!
    SetCollisionClass		(oCCollObjectCharacter::S_GetCollObjClass());           // [Moos] 20.12.00 Anpassung an Vob-�nderung
	SetCollDet				(TRUE);
/*
	// [HILDEBRANDT] Manuels alter Code
    SetCollisionClass		(oCCollObjectCharacter::S_GetCollObjClass());           // [Moos] 20.12.00 Anpassung an Vob-�nderung
    oCCollObjectCharacter::S_RegisterHandler();
*/
	SetMovLock				(FALSE);

	//
	//	CODECHANGE [CARSTEN]
	//

	magFrontier.SetNPC(this);

	//
	//	CODECHANGE [CARSTEN] END
	//

	oCNpcTalent::CreateTalentList(&talents);

	this->isSummoned = FALSE;
	lastHitSpellID	= -1;
	lastHitSpellCat = -1;

}

void oCNpc :: SetVisual(zCVisual* v)
{
	oCVob :: SetVisual(v);
    SetCollisionClass		(oCCollObjectCharacter::S_GetCollObjClass());           // [Moos] 20.12.00 Anpassung an Vob-�nderung
};

void oCNpc :: CleanUp()
{
	state.SetRoutine		(NULL,NULL);	// Alte rtn-route wird geloescht -> wichtig falls NSCs liegenbleiben -> Route haette Verweise auf Objekte, die es nicht mehr gibt.
	
	StopAllVoices			();
	ClearPerceptionLists	();
    SetInteractItem			(NULL);
	SetInteractMob			(NULL);

	if (GetNewsMemory()) GetNewsMemory()->ClearNews();

	rtnMan.	RemoveWayBoxes	(this);
	rtnMan.	RemoveRoutine	(this);

	rbt.lastDirections.DeleteList();

	// Falls Nachrichten noch Referenzen auf Objekte haben ( zB. EV_DAM_PER_FRAME )
	GetEM()->KillMessages();

	DeleteHumanAI();
	SetEnemy	(NULL);
    SetFocusVob (NULL);
	zRELEASE	(fireVob);
	
	// Release ist hier mit drin !
	SetAI		(NULL);
	SetRoute	(NULL);		 // [Moos] Leakfix

    magFrontier.DisposeFX();
    KillActiveSpells();

	talkOther					= NULL;
	s_assessThreatCounter		= ASSESS_THREAT_TIME;
	s_assessThreatLastEnemy		= NULL;
	bodyStateInterruptableOverride = FALSE;
	m_bAniMessageRunning		= FALSE;
	lastAction					= NPC_FIGHTMOVE_NOTINITIALISED;

    state       .ClearParserReferences();  // melde uns beim Parser ab

	// auf jeden fall alle laufenden effekte beenden
	for (int i=0; i<effectList.GetNum(); i++)
	{
		oCVisualFX* newFX = effectList[i];
		effectList.Remove(newFX);
		newFX->Kill();
		zRELEASE_ACCT(newFX);
		--i;
	}
};

oCNpc :: ~oCNpc()
// Destuctor
{
	zERR_MESSAGE(5,0,"U: NPC: Deleting NPC "+GetInstanceName());

	CleanUp();

    int i;

    // delete invslots (COCECHANGE Moos)
	TNpcSlot* slot		= NULL;
	for (i=invSlot.GetNumInList()-1; i>=0; i--) {
		slot = invSlot[i];
		invSlot.Remove(slot);
		delete	(slot);
  	}


    // [Moos] 7.12.00 Leakfix; beseitige die Talente
    for (i=talents.GetNumInList()-1;i>=0; i--)
	{
        zRELEASE(talents[i]);
	}

    // [Moos] Mache die ActiveInfo unsch�dlich
//    TActiveInfo *activeInfo =s_activeInfoCache.GetDataDangerous(this);
//    if (activeInfo)
//    activeInfo->npc = NULL;
    s_activeInfoCache.Delete(this);
    s_shrinkCache    .Delete(this);

	// Delete MagBooks
	delete mag_book;	mag_book = NULL;
	delete trader;		trader	 = NULL;

	mag_book			= NULL;
	// News / Info
	news				= NULL;
	info				= NULL;
	askbox				= NULL;
	curMission			= NULL;
	// Vobs
	focus_vob			= NULL;
	carry_vob			= NULL;
	talkOther			= NULL;
	// Others
	anictrl				= NULL;
	fireVob				= NULL;
	trader				= NULL;
	tradeNpc			= NULL;
	talkOther			= NULL;
	// SoundVob
	soundVob			= NULL;
	voiceIndex			= NULL;

    if (player == this)
        player = NULL;   // [Moos] oCNpc::player darf nicht auf eine ung�ltige Adresse zeigen

	// Moegliche Parser-Referenzen auf dieses Objekt aufloesen.
	parser.ResetWithVarReferenceList(gParserNpcReferenceList,this);

    if (GetClassDef()->GetNumLivingObjects() <= 1) // [Moos] unload all overlays at the end
    {
        for (zCSparseArrayIterator i(s_overlayArray); i; i.Next()){
			zCModelPrototype *overlay = *s_overlayArray[i];
            zRELEASE(overlay);
            s_overlayArray.Delete(i);
        }
    }

	// auf jeden fall alle laufenden effekte beenden
	for (i=0; i<effectList.GetNum(); i++)
	{
		oCVisualFX* newFX = effectList[i];
		effectList.Remove(newFX);
		newFX->Kill();
		zRELEASE_ACCT(newFX);
		--i;
	}

	// Delete Timed-Overlays...
	timedOverlays.DeleteListDatas();
}

void oCNpc :: InitByScript(int nr, zBOOL inSaveGame)
// Set Values 
{
	// Check Class Size
	static int classindex = -1;
	if (classindex<0) {
		classindex = parser.GetIndex("C_NPC");
		parser.CheckClassSize (classindex,(int)&parserEnd - (int)&idx);
	}
	
	zERR_MESSAGE(9,0,"U: NPC: Loading Script-NPC ");
	int typ,ele;
	zSTRING instanceName = parser.GetSymbolInfo(nr,typ,ele);
	zERR_MESSAGE(7,0,"U: NPC: NPC - Instance : "+instanceName);
	
	// Check auf NSC
	if (!parser.MatchClass(nr,"C_NPC")) 
		zERR_FATAL("U: NPC: Instance is not a npc. Dat/Tre-Files are not compatible !");

	memset(&idx,0,(int)&parserEnd - (int)&idx);

	// Idx ist hier wichtig, weil in den Sktipten drauf verwiesen wird.
	instanz	= idx = nr;

//	if (instanceName=="BAU_902_POCK01") parser.ShowCode(nr);
	parser.SetInstance		("SELF",this);
	parser.CreateInstance	(nr,this);

	if (mass==0) mass = 10;

	// Spellbook
	if (GetAttribute(NPC_ATR_MANAMAX)>0) MakeSpellBook();
		
	if (!inSaveGame) {
		
		// Items aktivieren, die im Skript aktiviert (angelegt wurden)	
		// ignore angelegte Armor -> weil bei SetAdditionalParam schon angelegt.
		inventory2.CheckForEquippedItems	(TRUE);	
	
		// *** Guild ***
		SetTrueGuild(guild);

		// *** Attitude ***
		// Aus Gildentabelle initialisieren...
		if (ogame && ogame->GetGuilds() && oCNpc::player) {
			attitude = ogame->GetGuilds()->GetAttitude(GetTrueGuild(),oCNpc::player->GetTrueGuild());
		}

		tmp_attitude = attitude;
		SetAttitude (attitude);			// Attitude nochmal setzen, wegen StdFaceAni

		// Create needed Objects (wird jetzt lazy erzeugt...) Enable / Disable / SetAsPlayer
		// InitHumanAI		();

		if (GetWeaponMode()==NPC_WEAPON_FIST) {
			// sofort in Faustkampfmodus schalten
			SetToFistMode();
		} else if (GetRightHand()) {
			// Sofort in Kampfmodus schalten
			oCItem* item = (oCItem*) GetRightHand();
			SetRightHand	(NULL);
			SetToFightMode	(item);
		}
	}

	//
	//	ASURE VALID DAMAGE TYPE
	//
	if ( this->damagetype == 0 ) this->damagetype = oEDamageType_Blunt;

	//
	//	SET DAMAGES ACCORDING TO TYPES
	//
	//::ApplyDamages( this->defaultDamage, this->damage, this->GetAttribute( NPC_ATR_STRENGTH );

	// *** Tagesablauf ***
	state.InitRoutine	();
	
	SetVobName(instanceName);

	// TEMP : FIXME : Disable Me !!!!!!!!!!!!!
	/*zSTRING _name = GetName(TRUE);
	_name.Upper();
	SetVobName(_name);
	*/
	vobcheck_time = rand() % NPC_VOB_CHECK;

	ogame->GetGameWorld()->InsertVobInWorld(this);

	zERR_MESSAGE(9,0,"U: NPC: Finished Script-NPC.");

	// [EDENFELD] Addon: Tolle gehackte Scheisse:
	// f�r den Fall das NpcType NPC_FLAG_GHOST enh�lt
	// wird das Visual auf Transparent gestellt
	zREAL _alpha = 1.0f;
	if ((this->variousFlags & NPC_FLAG_GHOST) == NPC_FLAG_GHOST) 
	{
		static zREAL ghostAlpha = 0.0f;
		if (ghostAlpha < 0.01f)
		{
			ghostAlpha = zoptions->ReadReal("INTERNAL", "GhostAlpha", 0.3f);
			if ((ghostAlpha < 0.01f) || (ghostAlpha > 1.01f))
			{
				ghostAlpha = 0.3f;
				zoptions->WriteReal("INTERNAL", "GhostAlpha", ghostAlpha);
			}
		}
		_alpha = ghostAlpha;
	}
	this->SetVisualAlpha(_alpha);
	this->SetVisualAlphaEnabled(_alpha < 0.99f);

	if (!effect.IsEmpty()) effect.Upper();

}

void oCNpc :: InitHumanAI()
{
	if (!human_ai) {
		ai_disabled =  FALSE;
		human_ai	=  zNEW( oCAIHuman() );
		human_ai	-> Init(this);
		anictrl		=  human_ai;
		SetAICallback  (human_ai);
	}
}

void oCNpc :: DeleteHumanAI()
{
	zRELEASE(human_ai); 
	SetAI	(NULL);	
	anictrl = NULL;
}

/*
void oCNpc :: ResetPos(zVEC3 &p)
{
	if (IsDead() && !IsMonster())	GetAnictrl() -> zMV_DO_SURFACE_ALIGN = FALSE;
	Interrupt		();
	zVEC3 vec = GetAtVectorWorld();
	SetCollDet		(FALSE);
	SetPositionWorld(p);
	ResetRotations	();	
	attribute		[NPC_ATR_HITPOINTS] = attribute	[NPC_ATR_HITPOINTSMAX];
	
	GetModel		()->StopAnisLayerRange(1,1000);
	GetAnictrl		()->Reset();
	GetModel		()->StartAni( GetAnictrl()->_s_walk );
	GetAnictrl		()->SetActionMode(ANI_ACTION_WALK);
	GetEM			()->Clear();
	GetAnictrl		()->SetDoOops(FALSE);
	SetBodyState	(BS_STAND);
	SetCollDet		(TRUE);
	SetSleeping		(FALSE);
	GetRigidBody	()->ApplyForceCM(vec * 30000);
	GetModel		()->SetAniTransScale(zVEC3(1,1,1));
	SetMovLock		(FALSE);
	if (IsSelfPlayer()) {
		ogame -> GetCameraAI() -> SetCamMode(CamModNormal);
		oCNpcFocus :: focus -> SetFocusMode(FOCUS_NORMAL);
	};
	CheckModelOverlays();	
	state.curState.valid = FALSE;

	//
	//	CODECHANGE [ROMAN]
	//
	divectr = divetime;
	//
	//	CODECHANGE [ROMAN] END
	//
};
*/

/*
zREAL oCNpc :: GetAngle (zCVob *to)
{
	if (!to) return 0;
	zVEC3 v1	= GetAtVectorWorld();
	zVEC3 v2	= (to	-> GetPositionWorld() - GetPositionWorld());
	v1.n[1]		= 0;
	v2.n[1]		= 0;
	return Alg_Rad2Deg ( Alg_AngleRad (v1,v2) );
}

void oCNpc :: GetAngles(zVEC3& pos, zREAL& azi, zREAL& elev)
{
	zVEC3 atVec = GetAtVectorWorld();
	zREAL azi2,elev2;
	// Blickrichtung des aktuellen NSCs
	// Im Sitzen muss diese gedreht werden, da AtVector nicht korrekt
	if (GetBodyState()==BS_SIT) atVec = -atVec;
	Alg_CalcAziElevUnit	(atVec,azi2,elev2);
	// Position des Objektes -> Normalize, weil sonst Fehler in Alg_CalcAziElev auftreten k�nnte
	// yy > 1.0F -> Floating Point Error -> Wert in elev nicht vorherbestimmt.
	zVEC3	toVec  = pos;
			toVec -= GetPositionWorld();
			toVec	.NormalizeApprox();
	Alg_CalcAziElevUnit	(toVec, azi, elev);
	azi		-= azi2;
	elev	-= elev2;
	azi		=  Alg_Rad2Deg(azi);
	if (azi<-180)	azi  += 360; else
	if (azi> 180)	azi  -= 360;
	elev	=  Alg_Rad2Deg(elev);
	if (elev<-180)	elev += 360; else
	if (elev> 180)  elev -= 360;
}

void oCNpc :: GetAngles(zCVob *to,zREAL &azi, zREAL &elev)
{
	GetAngles(to->GetPositionWorld(),azi,elev);
}
*/

zSTRING oCNpc :: GetGuildName()
{
	zCPar_Symbol* sym = parser.GetSymbol("TXT_GUILDS");
	if (sym) {
		zSTRING npcName;
		sym->GetValue(npcName,GetGuild());
		return npcName;
	}
	return zSTRING("Error : Missing guild-names !");
};

zSTRING oCNpc :: GetName(zBOOL known)
{
	// FIXME : Param kann raus
	// Immer bekannt, Absprache mit Mike (15.08.00)
	return name[0];
}

zBOOL oCNpc :: IsHostile( oCNpc* other )
// Ist other ein Feind von "this"
{
	return (GetAttitude(other)==NPC_ATT_HOSTILE);
}

zBOOL oCNpc :: IsFriendly( oCNpc* other )
// Ist other ein Feind von "this"
{
	return (GetAttitude(other)==NPC_ATT_FRIENDLY);
}

zBOOL oCNpc :: IsNeutral( oCNpc* other )
// Ist other ein Feind von "this"
{
	return (GetAttitude(other)==NPC_ATT_NEUTRAL);
}

zBOOL oCNpc :: IsAngry( oCNpc* other )
// Ist other ein Feind von "this"
{
	return (GetAttitude(other)==NPC_ATT_ANGRY);
}

int oCNpc :: GetAttitude(oCNpc* other)
{
	if (!other) return NPC_ATT_NEUTRAL;

	if ((other->IsAPlayer()) && (tmp_attitude!=attitude)) {
		return tmp_attitude;
	} else {
		return GetPermAttitude(other);
	};
}

int oCNpc :: GetPermAttitude(oCNpc* other)
{
	if (other->IsAPlayer()) return attitude;

	oCGuilds* guilds = ogame -> GetGuilds();
	return guilds -> GetAttitude (GetTrueGuild(),other->GetGuild());
}

void oCNpc :: SetAttitude(int wert)
{
	// Immer Attitude zum Spieler gemeint...
	SetCSEnabled(wert!=NPC_ATT_HOSTILE);

	attitude = wert;
	if (attitude > NPC_ATT_MAX)	attitude = NPC_ATT_MAX;
	if (attitude < 0)			attitude = 0;

	// FIX ab 1.13a: tempor�re Attitude muss beim Setzen auch ber�cksichtigt werden
	// doch wieder raus...
	//SetTmpAttitude(wert);
}

void oCNpc :: SetTmpAttitude(int wert)
{
	// Immer Attitude zum Spieler gemeint...
	SetCSEnabled(wert!=NPC_ATT_HOSTILE);

	tmp_attitude = wert;
	if (tmp_attitude > NPC_ATT_MAX)	tmp_attitude = NPC_ATT_MAX;
	if (tmp_attitude < 0)			tmp_attitude = 0;
}

int oCNpc :: GetProtectionByIndex( oEDamageIndex nIndex )
{
	return protection[ nIndex ];
}

int oCNpc :: GetProtectionByType( oEDamageType dwProtectionType )
{
	if ( ( dwProtectionType & oEDamageType_Barrier	) == oEDamageType_Barrier	) return this->GetProtectionByIndex( oEDamageIndex_Barrier	);
	if ( ( dwProtectionType & oEDamageType_Blunt	) == oEDamageType_Blunt		) return this->GetProtectionByIndex( oEDamageIndex_Blunt	);
	if ( ( dwProtectionType & oEDamageType_Edge		) == oEDamageType_Edge		) return this->GetProtectionByIndex( oEDamageIndex_Edge		);
	if ( ( dwProtectionType & oEDamageType_Fire		) == oEDamageType_Fire		) return this->GetProtectionByIndex( oEDamageIndex_Fire		);
	if ( ( dwProtectionType & oEDamageType_Fly		) == oEDamageType_Fly		) return this->GetProtectionByIndex( oEDamageIndex_Fly		);
	if ( ( dwProtectionType & oEDamageType_Magic	) == oEDamageType_Magic		) return this->GetProtectionByIndex( oEDamageIndex_Magic	);
	if ( ( dwProtectionType & oEDamageType_Point	) == oEDamageType_Point		) return this->GetProtectionByIndex( oEDamageIndex_Point	);
	if ( ( dwProtectionType & oEDamageType_Fall		) == oEDamageType_Fall		) return this->GetProtectionByIndex( oEDamageIndex_Fall		);

	return 0;
}

int oCNpc :: GetProtectionByMode( oTDamageMode dwProtectionMode )
{
	int nProtectionTotal = 0;

	if ( ( dwProtectionMode & oEDamageType_Barrier	) == oEDamageType_Barrier	) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Barrier	);
	if ( ( dwProtectionMode & oEDamageType_Blunt	) == oEDamageType_Blunt		) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Blunt		);
	if ( ( dwProtectionMode & oEDamageType_Edge		) == oEDamageType_Edge		) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Edge		);
	if ( ( dwProtectionMode & oEDamageType_Fire		) == oEDamageType_Fire		) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Fire		);
	if ( ( dwProtectionMode & oEDamageType_Fly		) == oEDamageType_Fly		) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Fly		);
	if ( ( dwProtectionMode & oEDamageType_Magic	) == oEDamageType_Magic		) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Magic		);
	if ( ( dwProtectionMode & oEDamageType_Point	) == oEDamageType_Point		) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Point		);
	if ( ( dwProtectionMode & oEDamageType_Fall		) == oEDamageType_Fall		) nProtectionTotal += this->GetProtectionByIndex( oEDamageIndex_Fall		);

	return nProtectionTotal;
}

int oCNpc :: GetFullProtection()
{
	int nProtectionTotal = 0;

	for ( zDWORD nIndex = 0; nIndex < oEDamageIndex_MAX; nIndex ++ ) 
		nProtectionTotal += this->GetProtectionByIndex( (oEDamageIndex) nIndex );

	return nProtectionTotal;
}

void oCNpc :: SetProtectionByIndex( oEDamageIndex nIndex, int nValue )
{
	this->protection[ nIndex ] = nValue;
}

int oCNpc :: GetDamageByIndex( oEDamageIndex nIndex )
{
	return damage[ nIndex ];
}

int oCNpc :: GetDamageByType( oEDamageType dwDamageType )
{
	if ( ( dwDamageType & oEDamageType_Barrier	) == oEDamageType_Barrier	) return this->GetDamageByIndex( oEDamageIndex_Barrier	);
	if ( ( dwDamageType & oEDamageType_Blunt	) == oEDamageType_Blunt		) return this->GetDamageByIndex( oEDamageIndex_Blunt	);
	if ( ( dwDamageType & oEDamageType_Edge		) == oEDamageType_Edge		) return this->GetDamageByIndex( oEDamageIndex_Edge		);
	if ( ( dwDamageType & oEDamageType_Fire		) == oEDamageType_Fire		) return this->GetDamageByIndex( oEDamageIndex_Fire		);
	if ( ( dwDamageType & oEDamageType_Fly		) == oEDamageType_Fly		) return this->GetDamageByIndex( oEDamageIndex_Fly		);
	if ( ( dwDamageType & oEDamageType_Magic	) == oEDamageType_Magic		) return this->GetDamageByIndex( oEDamageIndex_Magic	);
	if ( ( dwDamageType & oEDamageType_Point	) == oEDamageType_Point		) return this->GetDamageByIndex( oEDamageIndex_Point	);
	if ( ( dwDamageType & oEDamageType_Fall		) == oEDamageType_Fall		) return this->GetDamageByIndex( oEDamageIndex_Fall		);

	return 0;
}

int oCNpc :: GetDamageByMode( oTDamageMode dwDamageMode )
{
	int nDamageTotal = 0;

	if ( ( dwDamageMode & oEDamageType_Barrier	) == oEDamageType_Barrier	) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Barrier	);
	if ( ( dwDamageMode & oEDamageType_Blunt	) == oEDamageType_Blunt		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Blunt	);
	if ( ( dwDamageMode & oEDamageType_Edge		) == oEDamageType_Edge		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Edge	);
	if ( ( dwDamageMode & oEDamageType_Fire		) == oEDamageType_Fire		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Fire	);
	if ( ( dwDamageMode & oEDamageType_Fly		) == oEDamageType_Fly		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Fly		);
	if ( ( dwDamageMode & oEDamageType_Magic	) == oEDamageType_Magic		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Magic	);
	if ( ( dwDamageMode & oEDamageType_Point	) == oEDamageType_Point		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Point	);
	if ( ( dwDamageMode & oEDamageType_Fall		) == oEDamageType_Fall		) nDamageTotal += this->GetDamageByIndex( oEDamageIndex_Fall	);

	return nDamageTotal; 
}

int oCNpc :: GetFullDamage()
{
	int nDamageTotal = 0;

	for ( zDWORD nIndex = 0; nIndex < oEDamageIndex_MAX; nIndex ++ ) 
		nDamageTotal += this->GetDamageByIndex( (oEDamageIndex) nIndex );

	return	nDamageTotal;
}

void oCNpc::SetDamages( int* aryDamages )
{
	if ( ! aryDamages ) return;

	::memcpy( this->damage, aryDamages, sizeof( this->damage ) );
}

int oCNpc :: GetAttribute (int nr)
{
	return attribute[nr];
}

int	oCNpc :: GetHitChance(int nr)
{
	zERR_ASSERT(nr>=0 && nr<NPC_HITCHANCE_MAX);
	return this->hitChance[nr];
};

void oCNpc :: SetHitChance(int nr, int value)
{
	zERR_ASSERT(nr>=0 && nr<NPC_HITCHANCE_MAX);
	this->hitChance[nr] = value;
};

	
void oCNpc :: ChangeAttribute(int nr, int change)
{
	if ((change<0) && (player==this) && (godmode)) return; 
	if (change == 0) return;
	// Immortal
	if ( (nr==NPC_ATR_HITPOINTS) && HasFlag(NPC_FLAG_IMMORTAL) && change != -999 ) return;
	
	attribute[nr] += change;
	if (attribute[nr]<0) attribute[nr] = 0;

	// Higher than Max ?
	if ((nr==NPC_ATR_MANA) && (attribute[NPC_ATR_MANA]>attribute[NPC_ATR_MANAMAX]))
		attribute[NPC_ATR_MANA] = attribute[NPC_ATR_MANAMAX];
	if ((nr==NPC_ATR_HITPOINTS) && (attribute[NPC_ATR_HITPOINTS]>attribute[NPC_ATR_HITPOINTSMAX]))
		attribute[NPC_ATR_HITPOINTS] = attribute[NPC_ATR_HITPOINTSMAX];
	
	CheckModelOverlays();
}

void oCNpc :: SetAttribute(int nr, int value)
{
	attribute[nr] = value;
	CheckModelOverlays();
}

zBOOL oCNpc :: GetOverlay (zSTRING &name)
{
	name = mds_name.PickWord(1,".") + name + ".mds";
	// Check For File
	zoptions->ChangeDir(DIR_ANIMS);
	zFILE *f = zfactory->CreateZFile(name);
	zBOOL jau = f->Exists();
	delete(f);
	return jau;
}

void oCNpc :: CheckModelOverlays()
{
	// Damit die Overlays nicht geladen werden, wenn NSC schon tot ist ( wounded )
	if (GetAttribute(NPC_ATR_HITPOINTS)<=0) return;
	// Wounded
	zSTRING name;
	// Automatic Overlay active ?
	if (IsAPlayer() && (attribute[NPC_ATR_HITPOINTS]<=2) && (GetHumanAI()->GetWaterLevel()<=1)) {
		if (!overlay_wounded) {
			name = "_wounded";
			if (!GetOverlay(name)) return;
//			GetModel()	 -> StopAnisLayerRange(1,1000);	
                			ApplyOverlay(name);
			GetAnictrl() -> InitAnimations();
			overlay_wounded = TRUE;
		}
	} else if (overlay_wounded) {		
		name = "_wounded";
		if (!GetOverlay(name)) return;
//		GetModel()	 -> StopAnisLayerRange(1,1000);	
		                RemoveOverlay(name);
		GetAnictrl() -> InitAnimations();
		overlay_wounded = FALSE;
	}
}

void oCNpc :: SetToMad(zREAL ms)
{
	mad_heal	= ms;
	
	// Wechsel nur wirklich vollf�hren, wenn NSC 
	if (!GetAnictrl()->IsStanding()) return;
	if (mad) return;
	
	zSTRING name = "_mad";
	if (!GetOverlay(name)) return;
//	GetModel()	 -> StopAnisLayerRange(1,1000);	
	                ApplyOverlay(name);
	GetAnictrl() -> InitAnimations();
	mad		= TRUE;
}

void oCNpc :: HealFromMad()
{
	if (!mad) return;
	zSTRING name = "_mad";
	if (!GetOverlay(name)) return;
//	GetModel()	 -> StopAnisLayerRange(1,1000);	
	                RemoveOverlay(name);
	GetAnictrl() -> InitAnimations();
	mad			= FALSE;
	mad_heal	= 0;
}

void oCNpc :: SetToDrunk(zREAL ms)
{
/*	drunk_heal	= ms;
	
	// Wechsel nur wirklich vollf�hren, wenn NSC 
	if (!GetAnictrl()->IsStanding()) return;
	if (drunk) return;
	
	zSTRING name = "_drunken";
	if (!GetOverlay(name)) return;
	GetModel()	 -> StopAnisLayerRange(1,1000);	
	GetModel()   -> ApplyModelProtoOverlay(name);
	GetAnictrl() -> InitAnimations();
	drunk		= TRUE;*/
}

void oCNpc :: HealFromDrunk()
{
/*	if (!drunk) return;
	zSTRING name = "_drunken";
	if (!GetOverlay(name)) return;
	GetModel()	 -> StopAnisLayerRange(1,1000);	
	GetModel()   -> RemoveModelProtoOverlay(name);
	GetAnictrl() -> InitAnimations();
	drunk		= FALSE;
	drunk_heal	= 0;*/
}

// ********************************************************************
// Used in oDialog / oAuftrag
// ********************************************************************

void oCNpc :: CheckAngryTime()
{
	if (tmp_attitude != attitude) {
		if (attTimer==0) attTimer = NPC_ANGRY_TIME;
		// Tempor�re Attit�de aktiv, runterz�hlen
		attTimer -= ztimer.GetFrameTimeF();
		if (attTimer<=0) {
			// Attitude verbessert sich...
			tmp_attitude	= attitude;
			// Nochmal aufrufen, damit wieder richtige Std-FaceAni l�uft
			SetAttitude		(attitude);	
			attTimer		= 0;
		}	
	}
}

zBOOL oCNpc :: CanRecruitSC()
// Check, ob der NSC dem Spieler die Mitgliedschaft in seiner Gilde anbieten kann
// Sonderflag in NSC.memory
{
	//return ((memoryflag & NPC_MEM_RECRUIT)>0);
	return FALSE;
}

zBOOL oCNpc :: IsDisguised()
{
	return (GetGuild()!=GetTrueGuild());
}

int  oCNpc :: GetGuild()
{
	return guild;
}

void oCNpc :: SetGuild(int guildID)
{
	guild = guildID;
}

int oCNpc :: GetTrueGuild()
{
	return guildTrue;
}

void oCNpc :: SetTrueGuild(int guildID)
{
	guildTrue = guildID;
}

int oCNpc :: GetCamp()
{
	return 0;
}

zBOOL oCNpc :: IsGuildFriendly(int g2)
{
	return (ogame->GetGuilds()->GetAttitude(GetTrueGuild(),g2) == NPC_ATT_FRIENDLY);
}

int oCNpc :: GetGuildAttitude (int g)
{
	return ogame->GetGuilds()->GetAttitude(GetTrueGuild(),g);
}

// ************************************************************************************
// Abilities
// ************************************************************************************

/*
zBOOL oCNpc :: CanSwim()
{	
	// SwimTime > 0;
	return ((swimtime > 0) || (swimtime == ANI_TIME_INFINITE)); 
}

zBOOL oCNpc :: CanDive()
{
	// SwimTime > 0;
	return ((divetime > 0) || (divetime == ANI_TIME_INFINITE)); 
}

zREAL oCNpc :: GetJumpRange()
{
	return 300.0f; // 5m
}

zREAL oCNpc :: GetClimbRange()
{
	return 500.0f; // 5m
}
*/

// ************************************************************************************
// Inventory
// ************************************************************************************

void oCNpc :: CreateItems (int instanz, int anz)
// Add multiple Items to Npc - Inventory
{
	oCItem *ele = (oCItem*) ogame->GetGameWorld() -> CreateVob(zVOB_TYPE_ITEM,instanz);
	oCItem *item= NULL;

	// Sammelgegenstand
	if (ele->MultiSlot()) {
		ele->SetAmount(anz);
		item = PutInInv(ele);
		zRELEASE(ele);
	} else {
		item = PutInInv(ele);
		zRELEASE(ele);
		for (int i=1; i<anz; i++) {
			ele = (oCItem*)ogame->GetGameWorld() -> CreateVob(zVOB_TYPE_ITEM,instanz);
			item = PutInInv(ele);
			zRELEASE(ele);
		}
	}
	parser.SetInstance("ITEM", item);
}

// ************************************************************************************
// Talents & Memory
// ************************************************************************************

void oCNpc :: SetFlag(int nr)
{
	variousFlags &= nr;
}

zBOOL oCNpc :: HasFlag(int nr)
{
	return ((variousFlags & nr)>0);
}

/*
void oCNpc :: SetFightTalentLevel ( int nr )
// TEMP f�r Alex zum schnellen Aktivieren von Kampftalenten !!!
{
	int tal;
	oCItem *item = GetWeapon();
	if (item==NULL) return;
	if (item->HasFlag(ITM_FLAG_SWD))		tal = NPC_TAL_1H_1;			else
	if (item->HasFlag(ITM_FLAG_AXE))		tal = NPC_TAL_1H_1;			else
	if (item->HasFlag(ITM_FLAG_2HD_SWD))	tal = NPC_TAL_2H_1;			else
	if (item->HasFlag(ITM_FLAG_2HD_AXE))	tal = NPC_TAL_2H_1;			else
	if (item->HasFlag(ITM_FLAG_BOW))		tal = NPC_TAL_BOW_1;		else
	if (item->HasFlag(ITM_FLAG_CROSSBOW))	tal = NPC_TAL_CROSSBOW_1;		
	else return;

	zCView :: StdPrintwin("< FightTalent Level : "+zSTRING(nr)+">\n");

	DestroyFightTalent(tal);
	DestroyFightTalent(tal<<1);
	DestroyFightTalent(tal<<2);

	for (int i=1; i<=nr; i++) LearnFightTalent(tal<<(i-1));
	
	oCAniCtrl_Human *ac = GetAnictrl();
	ac -> InitFightAnis(GetWeaponMode());
	ac -> SetFightAnis (GetWeaponMode());
	
	GetModel() -> StartAni(ac->_s_walk);
}
*/


oCNpcTalent* oCNpc :: GetTalent(int talentNr, zBOOL createIfNull)
{
	if (talentNr<0 || talentNr>oCNpcTalent::oTEnumNpcTalent::NPC_TAL_MAX) 
		{ zERR_FAULT("U: NPC: TalentIndex invalid");return 0; }
	else if (talentNr>=talents.GetNumInList())
		{ zERR_FAULT("U: NPC: TalentList overrun");return 0; };
	
	if (!talents[talentNr]) 
	{
		if (!createIfNull) return NULL;
		talents[talentNr]=zNEW(oCNpcTalent);
		talents[talentNr]->SetTalent( oCNpcTalent::oTEnumNpcTalent(talentNr) );
	};

	return talents[talentNr];	
};

void oCNpc::SetTalentValue(int talentNr, int value)
{
	if (talentNr<0 || talentNr>oCNpcTalent::oTEnumNpcTalent::NPC_TAL_MAX) 
		{ zERR_FAULT("U: NPC: TalentIndex invalid");return; }
	else if (talentNr>=talents.GetNumInList())
		{ zERR_FAULT("U: NPC: TalentList overrun");return; };	
	
	if (!talents[talentNr]) 
	{
		talents[talentNr]=zNEW(oCNpcTalent);
		talents[talentNr]->SetTalent( oCNpcTalent::oTEnumNpcTalent(talentNr));
	}	
	talents[talentNr]->SetTalentValue( value );
};

int oCNpc::GetTalentValue(int talentNr)
{
	if (talentNr<0 || talentNr>oCNpcTalent::oTEnumNpcTalent::NPC_TAL_MAX) 
		{ zERR_FAULT("U: NPC: TalentIndex invalid");return -1; }
	else if (talentNr>=talents.GetNumInList())
		{ zERR_FAULT("U: NPC: TalentList overrun");return -1; };	
	
	if (!talents[talentNr]) return 0;
	
	return talents[talentNr]->GetTalentValue();
};

void oCNpc::SetTalentSkill(int talentNr, int skill)
{
	if (talentNr<0 || talentNr>oCNpcTalent::oTEnumNpcTalent::NPC_TAL_MAX) 
		{ zERR_FAULT("U: NPC: TalentIndex invalid");return; }
	else if (talentNr>=talents.GetNumInList())
		{ zERR_FAULT("U: NPC: TalentList overrun");return;	};	
	
	if (!talents[talentNr]) 
	{
		talents[talentNr]=zNEW(oCNpcTalent);
		talents[talentNr]->SetTalent( oCNpcTalent::oTEnumNpcTalent(talentNr));
	}	

	zBOOL forgetSkills	= skill<talents[talentNr]->GetTalentSkill();
	zBOOL learnSkills	= skill>talents[talentNr]->GetTalentSkill();	
	talents[talentNr]->SetTalentSkill( skill );

	if (learnSkills)
	{
		// Neues Flag auswerten (evtl. Overlay-MDS setzen)
		int setFightMode=-1;
		switch (talents[talentNr]->GetTalent()) 
		{
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_1H		:	setFightMode = NPC_WEAPON_1HS;	break;
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_2H		:	setFightMode = NPC_WEAPON_2HS;	break;
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_BOW		:	setFightMode = NPC_WEAPON_BOW;	break;		
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_CROSSBOW	:	setFightMode = NPC_WEAPON_CBOW;	break;
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_ACROBAT	:	
						ApplyOverlay("HUMANS_ACROBATIC.MDS");
						if (GetAnictrl())	GetAnictrl() -> InitAnimations();
						SetFallDownHeight (GetFallDownHeight()*2);			
						break;
		}

		// Entsprechendes Overlay-MDS fuer FightMode-Talente laden
		if (setFightMode>=0)   // [Moos] ApplyOverlay k�mmert sich nun um die Details // && GetModel()) 
		{
			zSTRING ws = oCAniCtrl_Human::GetWeaponHitString(setFightMode);
			// [Wohlers] : Patch 1.07 : Codechange : 13.03.01
			// Vorherige Talent-MDS wieder entfernen

			//[EDENFELD] 1.09: Fehler, HUMANS war hardcodiert, darf nicht, da wir auch Babes haben ;)
			zSTRING modelBase;

			zBOOL convertModelsAtNewGame = zoptions->ReadBool("ENGINE", "zCacheInAllNSCAtNewGame", FALSE) && ogame->IsInScriptStartup();

			if ( convertModelsAtNewGame || !ogame->IsInScriptStartup() )
			{
				if (!GetModel()) modelBase = "HUMANS";
				else   		     modelBase = GetModel()->GetModelProto()->GetModelProtoName();

				if (skill >= 2) {
					RemoveOverlay(modelBase+"_"+ws+"T"+zSTRING(skill-1)+".MDS");
				}

				ApplyOverlay(modelBase+"_"+ws+"T"+zSTRING(skill)+".MDS");

				oCAniCtrl_Human *ac = GetAnictrl();
				if (ac) 
				{
					ac -> InitFightAnis(setFightMode);
					if (setFightMode == GetWeaponMode()) ac->SetFightAnis(setFightMode);		
				}
			}
		} 
		
		// Und Jingle starten
		if (IsAPlayer()) zmusic->PlayJingleByScript("JINGLELEARNTALENT");		
	}
	else if (forgetSkills)
	{
		switch (oCNpcTalent::oTEnumNpcTalent(talentNr)) 
		{
			case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_ACROBAT:
						RemoveOverlay("HUMANS_ACROBATIC.MDS");
						if (GetAnictrl())	GetAnictrl() -> InitAnimations();
						SetFallDownHeight (GetFallDownHeight()/2);			
						break;
		}
	};
};

int oCNpc::GetTalentSkill(int talentNr)
{
	if (talentNr<0 || talentNr>oCNpcTalent::oTEnumNpcTalent::NPC_TAL_MAX) 
		{ zERR_FAULT("U: NPC: TalentIndex invalid");return -1; }
	else if (talentNr>=talents.GetNumInList())
		{ zERR_FAULT("U: NPC: TalentList overrun");return -1; };	
	
	if (!talents[talentNr]) return 0;
	
	return talents[talentNr]->GetTalentSkill();
};

zBOOL oCNpc::HasTalent(int nr, int value)
{
	return GetTalentSkill(nr)>=value;
};

zBOOL oCNpc :: CanUse	(oCItem *item)
// Kann der NSC dieses Item benutzen ?
// Check bei Waffen und r�stbaren Teilen
{
	if ( ! item ) return FALSE; 

	//
	//	CHECK MAGIC CIRCLE
	//
	int nMagicCircle = this->GetTalentSkill( oCNpcTalent::oTEnumNpcTalent::NPC_TAL_MAGE );

	if (  nMagicCircle < item->mag_circle ) 
	{
		//
		//	SET INSTANCES
		//
		::parser.SetInstance( "SELF", this );
		::parser.SetInstance( "ITEM", item );

		//
		//	CALL SCRIPT
		//
		int nIndex = ::parser.GetIndex( "G_CANNOTCAST" );
		::parser.CallFunc( nIndex, this->IsAPlayer() ? 1 : 0, item->mag_circle, nMagicCircle ); 

		//
		//	RETURN FAILURE
		//
		return FALSE; 
	}

	//
	//	CHECK ATTRIBUTE CONDITIONS
	//
	for (int i=0; i<ITM_COND_MAX; i++) {
		if (item->cond_atr[i]>0) {
			if (attribute[item->cond_atr[i]] < item->cond_value[i]) 
			{
				//
				//	SET INSTANCES
				//
				::parser.SetInstance( "SELF", this );
				::parser.SetInstance( "ITEM", item );

				//
				//	CALL SCRIPT
				//
				int nIndex = ::parser.GetIndex( "G_CANNOTUSE" );
				::parser.CallFunc( nIndex, this->IsAPlayer() ? 1 : 0, item->cond_atr[i], item->cond_value[i] ); 

				//
				//	RETURN FAILURE
				//
				return FALSE;
			}
		}
	}
	return TRUE;
}


/* ----------------------------------------------------------------------
	
	oCNpc::DisplayCannotUse()

    Stellt das Nicht-Benutzen-K�nnen eines Items dar

	8.11.2000	[Moos]	
                Erzeugt           


   ---------------------------------------------------------------------- */

void  oCNpc :: DisplayCannotUse ()
{
	//
	//	PLAY SVM
	//
	oCMsgConversation* convMsg = zNEW(oCMsgConversation)(oCMsgConversation::EV_OUTPUTSVM,"$SC_CANTUSEITEM");
	GetEM() -> OnMessage(convMsg,this);

    if (!IsAPlayer())
    {
/*
        static zBOOL reported = FALSE;

        if (reported)
            zERR_WARNING("Npc " + GetName() + " kann ein Item wegen fehlender Veraussetzungen nicht benutzen!");
        else
            zERR_FAULT("Npc " + GetName() + " kann ein Item wegen fehlender Veraussetzungen nicht benutzen!");
        
        reported = TRUE;  */

        return; // [Moos] nur der Spieler soll die Warnung bekommen
    }

//	int index = parser.GetIndex("S_DISPLAYCANNOTUSE");
//	parser.CallFunc(index, name, item->name, ...);
	
/*	zCSoundFX* sfx = zsound->LoadSoundFX( zSTRING("CANT_USE_ITEM.WAV") );
	if (sfx) {
		zCSoundSystem::zTSound3DParams params;
		params.SetDefaults();
//		params.pitchOffset = GetVoicePitch();
		zsound->PlaySound3D(sfx,this,2,&params);
	}
	zRELEASE(sfx);
*/
  
//	zCView :: StdPrintwin (zSTRING("< Die Voraussetzungen zum Benutzen dieses Items sind nicht erf�llt. >\n"));
//	GetEM()->OnMessage(zNEW( oCMsgConversation(oCMsgConversation::EV_PLAYANI,"S_DONTKNOW")),this);
}


/* ----------------------------------------------------------------------
	
	oCNpc :: CheckAllCanUse()
    
    �berpr�ft alle equippten Items, ob die Voraussetzungen noch
    erf�llt sind.

	13.11.2000	[Moos]	
                Erzeugt


   ---------------------------------------------------------------------- */

void  oCNpc :: CheckAllCanUse (){
    static bool recursion = false;
    static bool finished = false;

    finished = false;

    if (recursion)
        return;

    recursion = true;

    while (!finished)
    {
        finished = true;
        int i;

    	for (i=invSlot.GetNumInList()-1; i>=0; i--)
        {
	    	oCItem *item = zDYNAMIC_CAST<oCItem> (invSlot[i]->Vob());
			if (item && !CanUse(item) && item->HasFlag( ITM_FLAG_ACTIVE ))
            {
		    	UnequipItem(item);
                DisplayCannotUse();
                finished = false; // Teste alles nochmal; vielleicht gibt es Kettenabh�ngigkeiten?
		    }
	    }

        zCListSort<oCItem>* invrun = inventory2.GetContents();

        while (invrun){
	    	oCItem *item = invrun->GetData();
		    if (item && item->HasFlag(ITM_FLAG_ACTIVE) && !CanUse(item))
            {
		    	UnequipItem(item);
                DisplayCannotUse();
                finished = false; // Teste alles nochmal; vielleicht gibt es Kettenabh�ngigkeiten?
		    }
            invrun = invrun->GetNextInList();
	    }
    }

    recursion = false;
}


oCVob* oCNpc :: GetSlotVob (const zSTRING& name)
{
	TNpcSlot* slot = GetInvSlot(name);
	if (!slot) return NULL;
	return zDYNAMIC_CAST<oCVob>(slot->Vob());
}

oCItem* oCNpc :: GetSlotItem (const zSTRING& name)
{
	TNpcSlot* slot = GetInvSlot(name);
	if (!slot) return NULL;
	return zDYNAMIC_CAST<oCItem>(slot->Vob());
}

//
//	CODECHANGE [ROMAN]
//
oCItem*	oCNpc :: GetItem( int nCategory, int nSlot )
{
//	return inventory2.GetItem( nCategory, nSlot );
	return inventory2.GetItem( nSlot );
}
//
//	CODECHANGE [ROMAN] END
//

oCNpc* oCNpc :: GetSlotNpc (const zSTRING& name)
{
	TNpcSlot* slot = GetInvSlot(name);
	if (!slot) return NULL;
	return zDYNAMIC_CAST<oCNpc>(slot->Vob());
}


/* ----------------------------------------------------------------------
    	
	oCNpc :: AddItemEffects()

	13.11.2000	[Moos]	
                Dazu: �berpr�fe die Benutzbarkeit aller anderen Items


   ---------------------------------------------------------------------- */

void oCNpc :: AddItemEffects (oCItem* item)
{
	if (!item) return;
	
	// a) Change Attribute
	for (int i=0; i<ITM_COND_MAX; i++) {
		if (item->change_atr[i]>0) ChangeAttribute(item->change_atr[i],item->change_value[i]);
	}
	// b) Change Protection
	for (i=0; i< oEDamageIndex_MAX; i++) {
		protection[i] += item->GetProtectionByIndex( (oEDamageIndex) i );
	}
	// c) Verkleidung ?
	if (item->GetDisguiseGuild()!=NPC_GIL_NONE) {
		// irgendjemand gesehen ?
		if (item->GetDisguiseGuild()!=GetTrueGuild()) {
			SetGuild			(item->GetDisguiseGuild());
			AssessFakeGuild_S	();
		}
	}
	// d) Skript ?
	// [EDENFELD] 1.09 NPCs k�nnen nun auch Items per Skript equippen (z.B. Ringe etc.)
	if (/*this->IsSelfPlayer() &&*/ (item->on_equip>0)) {
		parser.SetInstance	("SELF",this);
		parser.CallFunc		(item->on_equip);
	}

    CheckAllCanUse();	//  [Moos] �berpr�fe alle Items, ob sie noch getragen werden d�rfen
}



/* ----------------------------------------------------------------------
    	
	oCNpc :: RemoveItemEffects()

	13.11.2000	[Moos]	
                Dazu: �berpr�fe die Benutzbarkeit aller anderen Items


   ---------------------------------------------------------------------- */

void oCNpc :: RemoveItemEffects (oCItem* item)
{
	if (!item) return;
	
	// a) Change Attribute ?
	for (int i=0; i<ITM_COND_MAX; i++) {
		if (item->change_atr[i]>0) ChangeAttribute(item->change_atr[i],-item->change_value[i]);
	}
	
	// b) Change Protection
	for (i=0; i< oEDamageIndex_MAX; i++) {
		protection[i] -= item->GetProtectionByIndex( (oEDamageIndex) i );
	}

	// c) Verkleidung ?
	if (item->GetDisguiseGuild()!=NPC_GIL_NONE) SetGuild ( GetTrueGuild() );
	
	// d) Skript ?
	// [EDENFELD] 1.09 NPCs k�nnen nun auch Items per Skript equippen (z.B. Ringe etc.)
	if (/*this->IsSelfPlayer() && */(item->on_unequip>0)) {
		parser.SetInstance	("SELF",this);
		parser.CallFunc		(item->on_unequip);
	}


    CheckAllCanUse();	//  [Moos] �berpr�fe alle Items, ob sie noch getragen werden d�rfen
}

void oCNpc :: EquipItem (oCItem *item)
// Aendere die Attribute, die durch aktivieren eines Item geaendert werden
{
	if (!item || item->HasFlag(ITM_FLAG_ACTIVE))
		return;

	//
	// [BENDLIN] Addon - SplitSlot
	//
	// Hier wird geprueft, ob ein Split-Item getrennt werden muss.
	// Dazu wird der Rest abgetrennt und in das Inventar eingefuegt.
	//
	// Vorher MUSS aber das Item bereits als 'ACTIVE' markiert sein,
	// damit nicht wieder das gleiche Item hochgesetzt wird...
	//
	if (item->SplitSlot() && (item->GetAmount() > 1))
	{
		oCItem *split = item->SplitItem(item->GetAmount() - 1);
		if (split)
		{
			item->SetFlag(ITM_FLAG_ACTIVE);
			item->SetAmount(1);
			inventory2.Insert(split);
			// [BENDLIN] Addon - SplitItem-Leak
			zRELEASE(split);
			item->ClearFlag(ITM_FLAG_ACTIVE);
		}
	}
	
	AddItemEffects(item);

	// Set active-Flag
	item->SetFlag(ITM_FLAG_ACTIVE);

	// Check if Parserproc has to be called
	// In "AddItemEffects"
	//if ((item->on_equip > 0) && (this==player))
    //    parser.CallFunc(item->on_equip,this);
	
	// Packe ins Ani-Slot
	zSTRING node = "";
	if (item->HasFlag(ITM_FLAG_SWD) || item->HasFlag(ITM_FLAG_DAG)|| item->HasFlag(ITM_FLAG_AXE))
		node = NPC_NODE_SWORD;
	else if (item->HasFlag(ITM_FLAG_2HD_SWD) || item->HasFlag(ITM_FLAG_2HD_AXE))
		node = NPC_NODE_LONGSWORD;
	else if (item->HasFlag(ITM_FLAG_SHIELD))
		node = NPC_NODE_SHIELD;
	else if (item->HasFlag(ITM_FLAG_BOW))
		node = NPC_NODE_BOW;
	else if (item->HasFlag(ITM_FLAG_CROSSBOW))
		node = NPC_NODE_CROSSBOW;
	else if (item->wear & ITM_WEAR_HEAD) 
		node = NPC_NODE_HELMET;
	else if (item->wear & ITM_WEAR_TORSO) {
		node = NPC_NODE_TORSO;
	}

	if (node!="") PutInSlot(node,item,TRUE);
}

void oCNpc :: UnequipItem (oCItem *item)
// Aendere die Attribute, die durch aktivieren eines Item geaendert werden
{
	if (!item || !item->HasFlag(ITM_FLAG_ACTIVE))
		return;

	RemoveItemEffects(item);

	// active Flag wech
	item -> ClearFlag (ITM_FLAG_ACTIVE);

	// Entferne aus Ani-Slot
	zSTRING node;
	if (item->HasFlag(ITM_FLAG_SWD) || item->HasFlag(ITM_FLAG_DAG)|| item->HasFlag(ITM_FLAG_AXE))
		node = NPC_NODE_SWORD;
	else if (item->HasFlag(ITM_FLAG_2HD_SWD) || item->HasFlag(ITM_FLAG_2HD_AXE))
		node = NPC_NODE_LONGSWORD;
	else if (item->HasFlag(ITM_FLAG_SHIELD))
		node = NPC_NODE_SHIELD;
	else if (item->HasFlag(ITM_FLAG_BOW))
		node = NPC_NODE_BOW;
	else if (item->HasFlag(ITM_FLAG_CROSSBOW))
		node = NPC_NODE_CROSSBOW;
	else if (item->wear & ITM_WEAR_HEAD) 
		node = NPC_NODE_HELMET;
	else if (item->wear & ITM_WEAR_TORSO)
		node = NPC_NODE_TORSO;
	
	oCVob* removedVob = NULL;
	if (node!="")
		removedVob = RemoveFromSlot(node);

	//
	// [BENDLIN] Addon - SplitSlot
	//
	// Hier wird nach einem Stapel vorhandener Slit-Items gesucht,
	// wo das nicht mehr equipte Item dazugepackt werden kann.
	// (falls zutreffend, wird es dann auch komplett weggeworfen)
	//
	// Bedingungen:
	//  - Stapel nicht 'ACTIVE'
	//  - nicht das gleiche Item
	//  - aber gleiche Intanz
	//
	if (removedVob)		// Nur, wenn es aus einem Slot entfernt wurde (kein Drop)
	if (item->SplitSlot())
	{
		zCListSort<oCItem>* ele = inventory2.GetContents();
		while (ele)
		{
			oCItem *i = ele->GetData();
			if (i && i->SplitSlot() && !i->HasFlag(ITM_FLAG_ACTIVE) &&
				(i != item) && (i->GetInstance() == item->GetInstance()))
			{
		    	i->ChangeAmount(item->GetAmount());
				inventory2.Remove(item);

				// [BENDLIN] Addon - FIXME: Item-Leak
				if (item->GetRefCtr() >= 2)  // InteractItem am Mobsi aber GetInteractItem() == NULL
					ogame->GetGameWorld()->RemoveVob(item);
				
				break;
			}
			ele = ele->GetNextInList();
		}
	}
}

// ********************************************************************
// Enemy and Vob - Recognition
// ********************************************************************

static zCView *game_focus = NULL;

int	oCNpc :: GetCutsceneDistance ()
// Umrechnung der aktuellen Entfernung des Spielers auf Wahrnehmungsdistanz / x 
// Konstanten aus Andres zCCSPlayer
{
//	if (ogame->GetSelfPlayerVob()) 
//		return (int)GetDistanceToVobApprox(*ogame->GetSelfPlayerVob());	
//	else

	zCVob* camVob	= NULL;
    zCAICamera* ai	= zCAICamera::GetCurrent();
	if (ai) camVob	= ai->GetVob();
	if (camVob)							return (int)GetDistanceToVobApprox(*camVob); else 
	if (ogame->GetSelfPlayerVob()) 		return (int)GetDistanceToVobApprox(*ogame->GetSelfPlayerVob());
	return 0;
}


/*--------------------------------------------------------------------------

    oCNpc::GetCSStateFlags()

    06-Sep-00       [Speckels]

					Bedeutung des CSStateFlags geaendert. Wird vorerst aus
					IsDead() und neuem Flag csAllowedAsRole generiert.
					Einziges moegliches Flag: CS_NOT_ALLOWED_AS_ROLE

--------------------------------------------------------------------------*/


void oCNpc :: SetCSEnabled(zBOOL enabled)
{
	csAllowedAsRole = enabled;	
}

int oCNpc :: GetCSStateFlags()
{
	int flag=0;
	if (!IsConditionValid())flag |= CS_NOT_ALLOWED_AS_ROLE;
	if (!csAllowedAsRole)	flag |= CS_NOT_ALLOWED_AS_ROLE;	
	return flag;
}

void oCNpc :: SetFocusVob(zCVob* vob)
{
	if (focus_vob != vob){
		zRELEASE_ACCT(focus_vob);
		focus_vob = vob;
		if (focus_vob) zADDREF_ACCT(focus_vob);
	}
}

zCVob* oCNpc :: GetFocusVob()
{
	return focus_vob;
}

void oCNpc :: ClearFocusVob()
{
	zRELEASE_ACCT(focus_vob);
}

oCNpc* oCNpc :: GetFocusNpc()
{
	return zDYNAMIC_CAST<oCNpc>(focus_vob);
}

oCNpc* oCNpc :: GetNearestFightNpcLeft()
{
	const zREAL maxangle = -360.0f;
	
	zREAL azi,elev;
	zREAL lowazi			= maxangle;
	
	zCVob *select			= NULL;
	
	zCArray<zCVob*> found;
	CreateVobList	(found, GetFightRange()*2);
	
	int max = found.GetNumInList();
	for (int i=0; i<max; i++) {	
		zCVob *v = found[i];
		// a) Es muss ein NSC sein
		// b) Es darf nicht der eigene NSC sein
		// c) Es darf nicht der aktuelle FocusNSC sein
		if (zDYNAMIC_CAST<oCNpc>(v) && (v!=GetFocusNpc()) && (v!=this)) {
			// Getting the angle
			GetAngles (v,azi,elev);
			if (azi>0.0f) azi = -180.0f - azi;
			if (!zInRange(azi,maxangle,0)) continue;
			// Getting the Distance 
			//zREAL dist;
			//zBOOL inRange = IsInFightRange(v,dist);
			//zBOOL inRange = GetDistanceToVobApprox(*v) < (GetFightRange()*2);
			// FIXME : H�he ????
			//if (inRange && (azi>lowazi)) {
			if (azi>lowazi) {
				// In Kampfdistanz
				select = v;		
				lowazi = azi;			
			}
		}
	}
//	if (select) select->SetDrawBBox3D(TRUE);
	found.EmptyList();
	return static_cast<oCNpc*>(select);
}

oCNpc* oCNpc :: GetNearestFightNpcRight()
// Check bei Drehschl�gen auf "best"-plaziertesten Angreifer
// Basiert auf CollectFocusVob und benutzt die dort aufgebaute vobList
// Direction > 0 = Schlag nach rechts
// Direction < 0 = Schlag nach links
// a) in Kampfdistanz und k�rzester Winkel
// b) k�rzester Winkel
{
	const zREAL maxangle = 360.0f;
	
	zREAL azi,elev;
	zREAL lowazi		= maxangle;
	
	zCVob *select		= NULL;

	zCArray<zCVob*> found;
	CreateVobList	(found, GetFightRange()*2);
	int max = found.GetNumInList();

	for (int i=0; i<max; i++) {	
		zCVob *v = found[i];
		// a) Es muss ein NSC sein
		// b) Es darf nicht der eigene NSC sein
		// c) Es darf nicht der aktuelle FocusNSC sein
		if (zDYNAMIC_CAST<oCNpc>(v) && (v!=GetFocusNpc()) && (v!=this)) {
			// Getting the angle
			GetAngles (v,azi,elev);
			if (azi < 0.0f) azi = 180.0f + (-azi);
			if (!zInRange(azi,0,maxangle)) continue;
			
			//if (abs(azi)>maxangle) continue;
			// Getting the Distance 
//			zREAL dist;
//			zBOOL inRange = IsInFightRange(v,dist);
//			zBOOL inRange = GetDistanceToVobApprox(*v) < (GetFightRange()*2);
			// FIXME : H�he ????
//			if (inRange && (azi<lowazi)) {
			if (azi<lowazi) {
				// In Kampfdistanz
				select = v;
				lowazi = azi;
			}
		}
	}
//	if (select) select->SetDrawBBox3D(TRUE);
	found.EmptyList();
	return static_cast<oCNpc*>(select);
}

zBOOL oCNpc :: FocusCheckBBox(const zCVob* vob, const int type, const int last_type, const zREAL low_azi, zREAL& azi)
{
	zREAL elev;
	// Player
	zVEC3 pos1		= GetPositionWorld();
	// Nur einmal -> Distanz auf 2 Dimensionen gebracht.
	zTBBox3D box3d	= vob->GetBBox3DWorld();
	zVEC3 pos2		= box3d.GetCenter();
	pos2[VY]		= pos1[VY];
	zREAL dist		= (pos1 - pos2).Length2();
	// Subtrahiere BBox3d - Ausmasse
	zREAL zdist		= (box3d.maxs[2] - box3d.mins[2]) / 2;
	zREAL xdist		= (box3d.maxs[0] - box3d.mins[0]) / 2;
	zdist			= zMax(zdist,xdist);
	dist		   -= zdist * zdist;
	// Und Test
	if (dist<0) dist = 0;
	if (!oCNpcFocus::focus->IsInRange(type,dist)) return FALSE;
	
	zVEC3 tpos[2];
	// 1. Position -> unten
	tpos[0]			= box3d.GetCenter();
	tpos[0][VY]		= box3d.mins[VY] + 180;
	// 2. Position -> oben
	tpos[1]			= box3d.GetCenter();
	tpos[1][VY]		= box3d.maxs[VY] - 10;
	
	int ctr = 0;
	do {
		GetAngles(tpos[ctr],azi,elev);
		if (oCNpcFocus::focus->IsInAngle(type,azi,elev)) {
			// f) Winkeltest = nur bei gleicher Priorit�t
			if (oCNpcFocus::focus->GetPriority(type)==oCNpcFocus::focus->GetPriority(last_type)) {
				if (abs(azi) >= abs(low_azi)) goto _skip;
			}
			if (FreeLineOfSight(tpos[ctr])) return TRUE;
		}
_skip:		
		ctr++;
	} while (ctr<2);

	// passed
	return FALSE;
}

zBOOL oCNpc :: FocusCheck(const zCVob* vob, const int type, const int last_type, const zREAL low_azi, zREAL& azi)
{
	zREAL elev;
	zVEC3 pos1,pos2;

	// d) Distanz
	pos1	= GetPositionWorld();
	pos2	= vob->GetPositionWorld();
	// Down 2 2 Dims
	pos1[VY]		= pos2[VY];
	zREAL dist		= (pos1-pos2).Length2();
	// Subtrahiere BBox3d - Ausmasse
	zTBBox3D box3d	= vob -> GetBBox3DWorld();
	zREAL zdist		= (box3d.maxs[2] - box3d.mins[2]) / 2;
	zREAL xdist		= (box3d.maxs[0] - box3d.mins[0]) / 2;
	zdist = zMax(zdist,xdist);
	dist -= zdist * zdist;

	if (dist<0) dist = 0;
	if (!oCNpcFocus::focus->IsInRange(type,dist)) return FALSE;

	// e) In Winkel
	
	zVEC3 vobPos	= vob->GetBBox3DWorld().GetCenter();
	zVEC3 thisPos	= this->GetBBox3DWorld().GetCenter();

	// ab 1.16 neu: vob position liegt im oberen viertel der bbox
	// ab 1.20:     aber nicht f�r NSCs mit sehr grosser BBOX (derzeit nur Drachen und Trolle)
	zBOOL bigNSC = FALSE;
	if (type == zVOB_TYPE_NSC)
	{
		oCNpc* npc = zDYNAMIC_CAST<oCNpc>(vob);

		if (npc && npc->GetGuild()==NPC_GIL_TROLL || npc->GetGuild()==NPC_GIL_DRAGON)
		{
			bigNSC = TRUE;
		}
	}
	zREAL ydist     = vob->GetBBox3DWorld().maxs[VY] - vob->GetBBox3DWorld().mins[VY];

	if (!bigNSC) vobPos[VY]	   += 0.25f * ydist;			


	GetAngles(vobPos,azi,elev);
	if (!oCNpcFocus::focus->IsInAngle(type,azi,elev)) return FALSE;

	// f) Winkeltest = nur bei gleicher Priorit�t
	if (oCNpcFocus::focus->GetPriority(type)==oCNpcFocus::focus->GetPriority(last_type)) {
		if (abs(azi) >= abs(low_azi)) return FALSE;
	}

	// g) Sichtbar ?
	// if (!FreeLineOfSight((zCVob*)vob)) return FALSE;

	// Patch 1.08 : Mittelpunkt der BBox des anvisierten Objektes nehmen,
	// da es sonst Probleme gibt manche Objekte in den Fokus zu bekommen (zB. sitzende NSCs)
	zCArray <zCVob*> ignore;
	ignore.Insert(this);
	ignore.Insert((zCVob*)vob);

	if ( GetGuild()!=NPC_GIL_TROLL && GetGuild()!=NPC_GIL_DRAGON)
	{
		ydist			= this->GetBBox3DWorld().maxs[VY] - this->GetBBox3DWorld().mins[VY];
		thisPos[VY]	   += 0.25f * ydist;			
	}
	
	// GetDirection ( Ziel - Start )
	zVEC3 dir = (vobPos - thisPos) * 0.95F;
	// Can See ?
	zBOOL hit = ogame->GetGameWorld()->TraceRayFirstHit(thisPos,dir,&ignore, zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_CHARACTER );
	// passed
	return !hit;
}

//changed [dennis]
void oCNpc :: ToggleFocusVob ( zBOOL left )
{
	zCVob*		vob;
	zVALUE		max_range		= oCNpcFocus::focus->GetMaxRange();
	zREAL		azi				= 0;
	zVALUE		low_azi			= 181.0f;
	int			type			= 0, last_type = 0;
	if( focus_vob ) type		= focus_vob->GetVobType();
	zBOOL		inFocus			= FALSE;
	if( type )  inFocus			= FocusCheckBBox(focus_vob,type,last_type,low_azi,azi);
	zVALUE		angle			= 0;
	zVALUE		tempangle		= 0;
	zVALUE		lastangle		= 360;
	zVALUE		dummy			= 0;
	zBOOL		overrideFocus	= FALSE;;

	if( inFocus )
	{
		GetAngles(focus_vob, angle, dummy );
		inFocus = FALSE;
	}

//	vobList.DeleteList	();
    ClearVobList        ();
	CreateVobList		(max_range);

	int noofobj = vobList.GetNumInList();
	for( int i = 0; i < noofobj; i++ )
	{
		overrideFocus = FALSE;
		
		vob = vobList[i];
		if((vob == this)||(HasInHand(vob))) continue;

		//
		//	Nur sichtbare vobs in den focus lassen
		//
		if ( ! this->FreeLineOfSight( vob ) ) continue;

		type = vob -> GetVobType();
		if( (type==zVOB_TYPE_NSC) || (type==zVOB_TYPE_ITEM) || (type==zVOB_TYPE_MOB) )
		{
			if(type==zVOB_TYPE_ITEM)
			{
				if (((oCItem*)vob)->HasFlag(ITM_FLAG_NFOCUS)) continue;
			}
			if(HasInHand(vob)) continue;

			// Sonderfall B : [Ulf] 
			// Mobsis koennen Fokus-Override-Flag haben und 
			// ueberschreiben damit Fokussystem
			// **** Ist aber nur im Fernkampfmodus aktiv. ****
			if ((GetWeaponMode()==NPC_WEAPON_BOW) || (GetWeaponMode()==NPC_WEAPON_CBOW)) {
				if (zDYNAMIC_CAST<oCMOB>(vob)) {
					oCMOB* mob		= static_cast<oCMOB*>(vob);
					overrideFocus	= mob->HasFocusOverride();
				}
			}
						
			// Sonderfall A : tote NSCs
			// Fokussystem: get�tete NSCs/SCs sollten im Melee- und Normalmodus wie MOBs behandelt werden. 
			// Im Fernkampf sollten sie komplett ignoriert werden, da sie nicht die Eigenschaft AIMABLE haben sollen.
			// Sonderfall fuers Enemy - setzen -> NSC schon tot ?
			if ((type==zVOB_TYPE_NSC) && (((oCNpc *)vob)->IsDead())) type=zVOB_TYPE_MOB;			

			if (!overrideFocus) {		
				// a) Type accepted in this Focus mode ?
				if (!oCNpcFocus::focus->IsValid(type)) continue;
		
				// b) Priority
				if (oCNpcFocus::focus->HasLowerPriority(type,last_type)) continue;
			}
//			if (!overrideFocus && !oCNpcFocus::focus->IsValid(type) ) continue;

			if( (type==zVOB_TYPE_NSC) && (((oCNpc *)vob)->IsDead()) ) type=zVOB_TYPE_MOB;
			
			if (((oCVob*)vob)->DoFocusCheckBBox()) inFocus = FocusCheckBBox(vob,type,last_type,low_azi,azi);
			else inFocus = FocusCheck(vob,type,type,low_azi,azi);
			if (inFocus) 
			{
				if( left )
				{
					GetAngles(vob, tempangle, dummy );
					tempangle = tempangle - angle;
					if( (tempangle < 0) && (fabs(tempangle) < lastangle ) )
					{
						last_type	= type;
						low_azi		= azi;
						SetFocusVob(vob);
						lastangle	= fabs(tempangle);
				
						// [Ulf] : (AtHome2) Bei Enemy setzen immer SetEnemy benutzen !
						if (type==zVOB_TYPE_NSC) SetEnemy((oCNpc *)vob);
					}
				}
				else
				{
					GetAngles(vob, tempangle, dummy );
					tempangle = tempangle - angle;
					if( (tempangle > 0) && (fabs(tempangle) < lastangle ) )
					{
						last_type	= type;
						low_azi		= azi;
						SetFocusVob (vob);
						lastangle	= fabs(tempangle);
				
						// [Ulf] : (AtHome2) Bei Enemy setzen immer SetEnemy benutzen !
						if (type==zVOB_TYPE_NSC) SetEnemy((oCNpc *)vob);
					}
				}
			}
		}
	}
}

//*********************************************************************************
//**																CollectFocusVob
//*********************************************************************************
//**	22.09.00	(DL)	Schnelleres update
//**	18.12.00	(RK)	Simplified
//**    17.01.01    (UW)    Leiter wird wieder als FokusVob erkannt
//**	25.01.01	(RK)	Sotred/restored current enemy after focus correction
//********************************************************************************* 


void oCNpc :: CollectFocusVob ( const zBOOL a_bForce )
{	
	//
	//	TIMER
	//
	int PICKVOBTIME = 250;				// alle viertel Sekunde

	if ((GetWeaponMode() >= NPC_WEAPON_DAG) && (GetWeaponMode() <= NPC_WEAPON_2HS))
	{
		PICKVOBTIME = 100;
	}

	
	if (oCNpc::GetTargetLocked())
	{
		// der target lock wird aufgehoben, sobald:
		// A) das target weiter als eine bestimmte distanz weg ist
		// B) das target tot ist
		// C) kein target exisitiert
		
		oCNpc* targetNpc = zDYNAMIC_CAST<oCNpc>(GetFocusVob());
		if ( !GetFocusVob()						|| 
			(targetNpc && targetNpc->IsDead())	|| 
			(GetFocusVob() && (GetPositionWorld()-GetFocusVob()->GetPositionWorld()).Length2()>2000*2000) )
		{
			oCNpc::SetTargetLocked(FALSE);
		}
		else return;
	}

	if (!a_bForce)
	{
		if ( pickvobdelay < PICKVOBTIME ) 
		{
			pickvobdelay += ztimer.GetFrameTimeF();
			return;
		}
		pickvobdelay -= PICKVOBTIME;
	}

	//
	//	CLEAR FORMER FOCUS/ENEMY
	//
	this->ClearFocusVob();
	SetEnemy(NULL);								

	//
	//	CREATE FOCUS LIST
	//
//	this->vobList.DeleteList();
    this->ClearVobList      ();
	this->CreateVobList		( oCNpcFocus::focus->GetMaxRange() );

	zCArray<oCNpc*>unconsciousNpcList;

	//
	//	CHECK ALL COLLECTED VOB FOR VALIDITY
	//
	int		nWeaponMode		 = this->GetWeaponMode()	;
	zBOOL	bIsRangedWeapon	 = ( nWeaponMode == NPC_WEAPON_BOW  )
							|| ( nWeaponMode == NPC_WEAPON_CBOW )
							|| ( nWeaponMode == NPC_WEAPON_MAG  );

	int		nVobType		= 0						;
	int		nVobTypeLeast	= 0						;

	zCVob*	pVob			= NULL					;
	oCVob*	pVobGame		= NULL					;
	oCMOB*	pMob			= NULL					;
	oCItem*	pItem			= NULL					;
	oCNpc*	pNpc			= NULL					;

	zBOOL	bCheckBBox		= FALSE					;
	zBOOL	bIsVobInFocus	= FALSE					;
	zBOOL	bOverrideFocus	= FALSE					;

	zREAL	fAzimuthMin		= 181.0f				;
	zREAL	fAzimuthActual	= 0.0f					;

	//
	//	LOOP VOBs
	//
	for ( int nVob = 0; nVob < vobList.GetNumInList(); nVob++ )
	{
		//
		//	(P)RE-SET VARS
		//
		bIsVobInFocus	= FALSE;

		//
		//	GET CURRENT VOB
		//
		pVob			= vobList[ nVob ]	;	if ( ! pVob )												continue;
		pNpc			= zDYNAMIC_CAST< oCNpc >	( pVob );
		nVobType		= pVob->GetVobType();

		//
		//	PERFORM VISIBILITY DETERMINATION 
		//
		
		// CodeChange : [Ulf]  - 17-01-01
		//              Bugfix - Leiter (von oben runterklettern) konnte niemals FokusVob werden...
		pVobGame		= zDYNAMIC_CAST< oCVob > ( pVob );	
		if ( !pVobGame ) continue;
		bCheckBBox		= pVobGame->DoFocusCheckBBox();
		
		if (!bCheckBBox) {
			// && !this->FreeLineOfSight( pVob ) )	continue;

			// Patch 1.08 : Mittelpunkt der BBox des anvisierten Objektes nehmen,
			// da es sonst Probleme gibt manche Objekte in den Fokus zu bekommen (zB. sitzende NSCs)
			zVEC3 vobPos	= pVob->GetBBox3DWorld().GetCenter();
			zVEC3 thisPos	= this->GetBBox3DWorld().GetCenter();
			zREAL ydist     = pVob->GetBBox3DWorld().maxs[VY] - pVob->GetBBox3DWorld().mins[VY];
			vobPos[VY]	   += 0.25f * ydist;			
			ydist			= this->GetBBox3DWorld().maxs[VY] - this->GetBBox3DWorld().mins[VY];
			thisPos[VY]	   += 0.25f * ydist;
			zVEC3 dir		= (vobPos - thisPos) * 0.95F;
			// Can See ?
			if (ogame->GetGameWorld()->TraceRayFirstHit(thisPos,dir, pVob, zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_CHARACTER ))
				continue;

		}

		// CodeChange End : [Ulf]  

		//
		//	CHECK DIFFERENT VOB TYPES		[TYPE EVALUATION/QUICK CHECKS]
		//
		
		switch( nVobType )
		{
			case		zVOB_TYPE_NSC	:	//
											//	CHECK NPCS ...
											//
											if ( ! pNpc )	continue;		//	NPC IS NOT VALID

											if ( (nWeaponMode >= NPC_WEAPON_DAG) && (nWeaponMode <= NPC_WEAPON_2HS) )
											{
												if ( pNpc->IsUnconscious() )
												{
													//zERR_WARNING("C: unconscious NPC found!!!!!!!!!!!!!");
													unconsciousNpcList.InsertEnd(pNpc);
													continue;
												}
												else if ( pNpc->IsDead() ) continue;
											}
											else if ( pNpc->IsDead() ) {nVobType = zVOB_TYPE_MOB; }								// CONSIDER DEAD NPCs AS MOBs

											break;

			case		zVOB_TYPE_ITEM	:	//
											//	CHECK ITEMS ...
											//
											pItem	= zDYNAMIC_CAST< oCItem >	( pVob );	if ( ! pItem )	continue;		//	ITEM IS NOT VALID
											
											if ( this ->HasInHand	( pItem )			)					continue;		//	DO NOT COLLECT ITEMS IN MY HAND
											if ( pItem->HasFlag		( ITM_FLAG_NFOCUS ) )					continue;		//	DO NOT COLLECT ITEMS MARKED FOR FOCUS DISABLE

											break;

			case		zVOB_TYPE_MOB	:	//
											//	CHECK MOBS ...
											//
											pMob	= zDYNAMIC_CAST< oCMOB >	( pVob );	if ( ! pMob )	continue;		// MOB IS NOT VALID

											if ( pMob->IsDestroyed() )										continue;		// DO NOT COLLECT DESTROYED MOBs
											
											if ( bIsRangedWeapon )															// CHECK OVERRIDE FLAG WHEN IN RANGED WEAPON MODE
												 bOverrideFocus = pMob->HasFocusOverride();
											
											break;

			default:																						continue;
		}

		//
		//	CHECK FOCUS VALIDITY BY TYPE	[SCRIPT CHECK]
		//
		if ( ! bOverrideFocus )
		{
			if ( !	oCNpcFocus::focus->IsValid			( nVobType				  ) )						continue;
			if (	oCNpcFocus::focus->HasLowerPriority	( nVobType, nVobTypeLeast ) )						continue;
		}

		//
		//	PERFORM VISIBILITY DETERMINATION [BASED ON WEAPON MODE]
		//
		switch( nWeaponMode )
		{
			//
			//	NO WEAPON AT ALL
			//
			case NPC_WEAPON_NONE	:  

			//
			//	MELEE WEAPON 
			//
			case NPC_WEAPON_FIST	:  
			case NPC_WEAPON_DAG		:  
			case NPC_WEAPON_1HS		:  
			case NPC_WEAPON_2HS		:	

			//
			//	RANGED WEAPON
			//
			case NPC_WEAPON_BOW		:  
			case NPC_WEAPON_CBOW	:	break;  

			//
			//	MAGIC SPELL
			//
			case NPC_WEAPON_MAG		:  	oCMag_Book* pBook  = this ->GetSpellBook	()	;	zERR_ASSERT( pBook );
										oCSpell*	pSpell = pBook->GetSelectedSpell()	;	
										
										if ( ! pSpell )														continue;
										if ( ! pSpell->IsValidTarget( pVob ) )								continue;
										break;

		}	

		if	( bCheckBBox )	bIsVobInFocus = this->FocusCheckBBox( pVob, nVobType, nVobTypeLeast, fAzimuthMin, fAzimuthActual );
		else				bIsVobInFocus = this->FocusCheck	( pVob, nVobType, nVobTypeLeast, fAzimuthMin, fAzimuthActual );

		//
		//	UPDATE FOCUS					[IN CASE A "BETTER" VOB WAS FOUND]
		//
		if	( ! bIsVobInFocus )																				continue;
		else					
		{
			//
			//	SET NEW FOCUS
			//
			nVobTypeLeast	= nVobType		;
			fAzimuthMin		= fAzimuthActual;

			this->SetFocusVob( pVob );

			//
			//	SET NEW ENEMY
			//
			SetEnemy(pNpc);
		}
	}

	// so, wenn es hier keinen focus vob gibt, dann nimm als letzten ausweg einen bewusstlosen npc, falls es einen gibt
	if ( !GetFocusVob() )
	{
		if (unconsciousNpcList.GetNum()>0)
		{
			zREAL	fAzimuth, fElevation, fDistance;
			zREAL   fAngle;
			zREAL   actScore;
			zREAL   minScore		=   FLT_MAX;
			oCNpc*	nearestNpc		=	NULL;
			zREAL	fDistanceMax	= 1.0f;

			if	( pItem )	fDistanceMax = pItem->range			 ;
			else			fDistanceMax = this ->GetFightRange();

			if ( fDistanceMax <= 0.0f ) fDistanceMax = 1.0f;

			//
			//	GET FIGHT ANGLE
			//
			zREAL fAngleMax		= oCNpcFocus::focus->GetAzi();


			for (int i=0; i<unconsciousNpcList.GetNum(); i++)
			{
				fDistance = (GetPositionWorld()-unconsciousNpcList[i]->GetPositionWorld()).Length();
				GetAngles	(unconsciousNpcList[i] , fAzimuth, fElevation);				
				//
				//	GET RELATIVE ANGLES
				//
				
				fAngle = fAzimuth ? ( fAzimuth / fAngleMax ) : 1.0f;

				// calc score
				actScore = 2.0f * fAngle + 8.0f * ( fDistance / fDistanceMax );

				if (actScore<minScore)
				{
					minScore    = actScore;
					nearestNpc	= unconsciousNpcList[i];
				}
			}
			if (nearestNpc) 
			{
				SetFocusVob(nearestNpc);
				SetEnemy   (nearestNpc);
			}
		}
	}

	//
	//	CORRECT FOCUS ?!?
	//
	switch( nWeaponMode )
	{
		//
		//	MELEE WEAPON 
		//
		case NPC_WEAPON_FIST	:	
		case NPC_WEAPON_DAG		:  
		case NPC_WEAPON_1HS		:  
		case NPC_WEAPON_2HS		:  	{
										//
										//	SETUP VARS
										//
										zCVob* pVobNearestDistance	= NULL;
										zCVob* pVobNearestAngle		= NULL;

										//
										//	ASSURE A VALID FOCUS
										//
										pVobNearestAngle	= this->GetFocusVob	();	
										if ( ! pVobNearestAngle ) return;
										pItem				= this->GetWeapon	();

										//
										//	TRY TO FIND NEARER VOB
										//
										if ( pItem )	
										{
											//
											//	STORE CURRENT ENEMY
											//
											pNpc = this->GetEnemy();

											//
											//	SEARCH FOR A NEARER VOB
											//
											this->GetNearestValidVob( oCNpcFocus::focus->GetMaxRange() );

											//
											//	RESTORE CURRENT ENEMY (IF ANY)
											//
											if (   pNpc ) 
											if ( ! this->GetEnemy() ) 
												this->SetEnemy( pNpc );
										}

										//
										//	NO VOB INSIDE FOCUS RANGE -> USE FORMER FOCUS
										//
										pVobNearestDistance	= this->GetFocusVob();

										if ( ! pVobNearestDistance )					
										{
											pNpc = dynamic_cast< oCNpc* > ( pVobNearestAngle );
											if ( pNpc ) this->SetEnemy( pNpc );

											this->SetFocusVob( pVobNearestAngle );

											return;
										}

										//
										//	GET FIGHT DISTANCE
										//
										zREAL fDistanceMax	= 1.0f;

										if	( pItem )	fDistanceMax = pItem->range			 ;
										else			fDistanceMax = this ->GetFightRange();

										if ( fDistanceMax <= 0.0f ) fDistanceMax = 1.0f;

										//
										//	GET FIGHT ANGLE
										//
										zREAL fAngleMax		= oCNpcFocus::focus->GetAzi();

										//
										//	GET VOBS' ANGLES AND DISTANCES
										//
										zREAL	fAzimuth[2], fElevation[2], fDistance[2];

														this->GetAngles		  (  pVobNearestAngle   , fAzimuth[0], fElevation[0]	);
										fDistance[0] =	this->GetDistanceToVob(	*pVobNearestAngle									);

														this->GetAngles		  (  pVobNearestDistance, fAzimuth[1], fElevation[1]	);
										fDistance[1] =	this->GetDistanceToVob(	*pVobNearestDistance								);

										//
										//	GET RELATIVE ANGLES
										//
										zREAL fAngle[2];

										fAngle[0] = fAzimuth[0] ? ( fAzimuth[0] / fAngleMax ) : 1.0f;
										fAngle[1] = fAzimuth[1] ? ( fAzimuth[1] / fAngleMax ) : 1.0f;

										//
										//	RATE DISTANCES
										//
										zREAL fPriority[2];

										fPriority[0] = 2.0f * fAngle[0] + 8.0f * ( fDistance[0] / fDistanceMax );
										fPriority[1] = 2.0f * fAngle[1] + 8.0f * ( fDistance[1] / fDistanceMax );

										//
										//	UPDATE FOCUS
										//
										if ( fPriority[0] < fPriority[1] )
										{
											oCNpc* pNpc1 = dynamic_cast< oCNpc* > ( pVobNearestAngle );

											if ( pNpc1 ) this->SetEnemy( pNpc );

											this->SetFocusVob( pVobNearestAngle );
										}

									}
									break;	

		//
		//	RANGED WEAPON
		//
		case NPC_WEAPON_BOW		:  
		case NPC_WEAPON_CBOW	:

		//
		//	MAGIC SPELL
		//
		case NPC_WEAPON_MAG		:

		//
		//	NO WEAPON AT ALL
		//
		case NPC_WEAPON_NONE	:  	break;
	}	



}

void oCNpc :: GetNearestValidVob (zREAL max_dist)
// Only Valid, if its the player
{
	static const int PICKVOBTIME = 0;				// alle halbe Sekunde

	zPOINT2 a_vobpos;
	if (pickvobdelay > PICKVOBTIME) {
		pickvobdelay -= PICKVOBTIME;
		// delete old List
/*
		if (vobList.GetNumInList()!=0) 		
			// Folgende Zeile ist unbedingt noetig, damit keine Mem-Leaks entstehen !!
			vobList.DeleteList();
*/
        ClearVobList();

		zVEC3 pos1,pos2;
		// Create BBox
		zTBBox3D bbox;
		pos1 = bbox.maxs = bbox.mins = GetPositionWorld();	
		// Vorderer Punkt	
		bbox.maxs[0] += max_dist; bbox.maxs[1] += max_dist; bbox.maxs[2] += max_dist;
		// Hinterer Punkt
		bbox.mins[0] -= max_dist; bbox.mins[1] -= max_dist; bbox.mins[2] -= max_dist;
		ogame->GetGameWorld() -> CollectVobsInBBox3D	(vobList, bbox);
		// Jetzt das naechste Vob ermitteln
//		zREAL lowazi = 181.0;
//		zREAL azi,elev;
		zCVob *vob;

		SetEnemy(NULL);
		ClearFocusVob();

		max_dist *= max_dist;			// Zum Quadrat

		int i, max = vobList.GetNumInList();
		for (i=0; i<max; i++) {	
			vob = vobList[i];

			if (vob!=this) {
				int type = vob -> GetVobType();
				if ((type==zVOB_TYPE_ITEM) && (((oCItem *)vob)->HasFlag(ITM_FLAG_NFOCUS))) continue;
				if ((type==zVOB_TYPE_NSC) && (((oCNpc *)vob)->IsDead())) type=zVOB_TYPE_MOB;			
				if (!oCNpcFocus::focus->IsValid(type)) continue;
				
				if (zDYNAMIC_CAST<oCVob>(vob)) {
				    // Entfernung okay ?
					if (GetDistanceToVob2(*vob)<=max_dist) {
						// FreeLineOfSight ?
						zREAL angle		 = GetAngle( vob );
						oCNpc* npc		 = zDYNAMIC_CAST<oCNpc>(vob);
						zBOOL inValidNpc = FALSE;
						
						if (npc && ( GetWeaponMode()>=NPC_WEAPON_DAG && GetWeaponMode()<=NPC_WEAPON_2HS ) && (npc->IsUnconscious()||npc->IsDead()) )
							inValidNpc = TRUE;

						if ( !inValidNpc && FreeLineOfSight(vob) && angle <= oCNpcFocus::focus->GetAzi() ) 
						{
							
							max_dist = GetDistanceToVob2(*vob);
							SetFocusVob(vob);
							// [Ulf] : (AtHome2)
							if ((type==zVOB_TYPE_NSC) && (!((oCNpc *)vob)->IsDead())) SetEnemy((oCNpc *)vob);
						}
					}
				}
			}
		}

        vobList.Remove(this);

        for (i = vobList.GetNumInList()-1; i>=0; i--)
            zADDREF_ACCT(vobList[i]);

	} else 
		pickvobdelay += ztimer.GetFrameTimeF();
}

void oCNpc :: GetNearestVob (zREAL max_dist)
// Only Valid, if its the player
{
	static const int PICKVOBTIME = 0;				// alle halbe Sekunde

	zPOINT2 a_vobpos;
	if (pickvobdelay > PICKVOBTIME) {
		pickvobdelay -= PICKVOBTIME;
		// delete old List
/*		if (vobList.GetNumInList()!=0) 		
			// Folgende Zeile ist unbedingt noetig, damit keine Mem-Leaks entstehen !!
			vobList.DeleteList();
*/
        ClearVobList();

		zVEC3 pos1,pos2;
		// Create BBox
		zTBBox3D bbox;
		pos1 = bbox.maxs = bbox.mins = GetPositionWorld();	
		// Vorderer Punkt	
		bbox.maxs[0] += max_dist; bbox.maxs[1] += max_dist; bbox.maxs[2] += max_dist;
		// Hinterer Punkt
		bbox.mins[0] -= max_dist; bbox.mins[1] -= max_dist; bbox.mins[2] -= max_dist;
		ogame->GetGameWorld() -> CollectVobsInBBox3D	(vobList, bbox);
		// Jetzt das naechste Vob ermitteln
//		zREAL lowazi = 181.0;
//		zREAL azi,elev;
		zCVob *vob;
		
		// [Ulf] : (AtHome2)
		SetEnemy(NULL);
		ClearFocusVob();

		max_dist *= max_dist;			// Zum Quadrat

		int i, max = vobList.GetNumInList();
		for (i=0; i<max; i++) {	
			vob = vobList[i];

			if (vob!=this) {
				int type = vob -> GetVobType();
				if ((type==zVOB_TYPE_ITEM) && (((oCItem *)vob)->HasFlag(ITM_FLAG_NFOCUS))) continue;
				
				if (zDYNAMIC_CAST<oCVob>(vob)) {
				    // Entfernung okay ?
					if (GetDistanceToVob2(*vob)<=max_dist) {
						// FreeLineOfSight ?
						zREAL angle = GetAngle( vob );
						if (FreeLineOfSight(vob) && angle <= oCNpcFocus::focus->GetAzi() ) {
							max_dist = GetDistanceToVob2(*vob);
							SetFocusVob(vob);
							// [Ulf] : (AtHome2)
							if ((type==zVOB_TYPE_NSC) && (!((oCNpc *)vob)->IsDead())) SetEnemy((oCNpc *)vob);
						}
					}
				}
			}
		}

        vobList.Remove(this);

        for (i = vobList.GetNumInList()-1; i>=0; i--)
            zADDREF_ACCT(vobList[i]);

	} else 
		pickvobdelay += ztimer.GetFrameTimeF();

}

oCAniCtrl_Human *oCNpc :: GetAnictrl()
{	
	return human_ai; 
}

void oCNpc :: ResetToHumanAI()
{	
	if (GetAICallback()!=human_ai) {
		zRELEASE(human_ai);
		human_ai = zDYNAMIC_CAST<oCAIHuman>(GetAICallback());
	}
}


// ********************************************************************
// Kampfauswirkungen
// ********************************************************************

void oCNpc :: SetEnemy ( oCNpc *e )
{

    if (e == enemy && e && e->IsConditionValid())
        return;

	// [Ulf] : (AtHome2)
	zRELEASE_ACCT(enemy);

	if (this==e) {
		zERR_MESSAGE(5,0,"U: NPC: NPC attacks himself !");
		return;
	}

	if (e && e->IsConditionValid()) {
		enemy = e;
		zADDREF_ACCT(enemy);
	}
}

oCNpc* oCNpc :: GetNextEnemy()
// Suche dir naechsten enemy raus
{
	if (enemy && enemy->IsConditionValid()) return enemy;

	// Was in Wahrnehmungsliste ?
	// den nearest verwenden.
	oCNpc*	other	= NULL;
	oCNpc*	found	= NULL;
	zREAL	thisDist= 0.0f;
	zREAL	minDist	= zREAL_MAX;

	int max = vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		other = zDYNAMIC_CAST<oCNpc>(vobList[i]);
		// a) Es muss ein NSC sein
		// b) Es darf nicht der eigene NSC sein
		if (other && (other!=this)) {

			if (other->IsInGlobalCutscene()) continue;
			
			if ((this->GetAttitude(other)==NPC_ATT_HOSTILE) && other->IsConditionValid()) {
				thisDist = GetDistanceToVob2(*other);
				if (thisDist<minDist) {
					minDist = thisDist;
					found	= other;
				}
			}
		}
	}

	SetEnemy(found);
	return found;
}

zBOOL oCNpc :: IsConditionValid()
// Ist NSC einsatzf�hig ? Nein, wenn
// a) bewusstlos
// b) tot
// c) versteinert (Magie)
{
	return (
		!IsDead() &&
		!IsUnconscious() &&
		!IsFadingAway() &&
		!IsSpellActive(SPL_ICECUBE) &&
		!IsSpellActive(SPL_WHIRLWIND) &&
		!IsSpellActive(SPL_GREENTENTACLE) &&
		!IsSpellActive(SPL_ICEWAVE) &&
		!IsSpellActive(SPL_PYROKINESIS)	&&
		!IsSpellActive(SPL_SUCKENERGY)
		);
}

zBOOL oCNpc :: IsInFightFocus(zCVob* target)
{
	if (!target) return FALSE;
	// a) In Winkel
	// b) In Distance (30m FernkampfDistanz)
	zREAL azi,elev;
	GetAngles(target,azi,elev);
	return ((abs(azi)<30) && (abs(elev)<50) && (GetDistanceToVob2(*target)<3000*3000));
}

// ************* Kampfsystem Hilfe ************

/*
void oCNpc :: SetFallDownHeight	(zREAL fh)
{
	fallDownHeight = fh;
}

zREAL oCNpc :: GetFallDownHeight()
{
	return fallDownHeight;
}

void oCNpc :: SetFallDownDamage	(int fd)
{
	fallDownDamage = fd;
}

void oCNpc :: CreateFallDamage( zREAL dist )
{
	//
	//	FILL DAMAGE DESCRIPTOR
	//
	oCNpc::oSDamageDescriptor descDamage;

	descDamage.fDamage		 = ((dist + 50.0f - GetFallDownHeight()) / 100) * fallDownDamage;
	descDamage.enuTypeDamage = oCNpc::oETypeDamage::oEDamageType_Fall;
	descDamage.dwFieldsValid = oEDamageDescFlag_DamageType | oEDamageDescFlag_Damage;

	//
	//	SEND DAMAGE MESSAGE
	//
	oCMsgDamage* pMsg = zNEW( oCMsgDamage )( oCMsgDamage::EV_DAMAGE_ONCE, descDamage );
	this->GetEM()->OnMessage( pMsg, this );

	//
	//	OUTPUT DEBUG MESSAGE
	//
	zCView::PrintDebug("< Dist:"+zSTRING(int(dist))+"/ Dam:"+zSTRING( (int)descDamage.fDamage)+">\n");

//	ChangeAttribute	(NPC_ATR_HITPOINTS,-dam);
//	if (GetAttribute(NPC_ATR_HITPOINTS)<=0) DoDie();
}
*/

oCItem* oCNpc :: HasEquippedStolenItem (oCNpc* npc)
// Hat dieser NSC ein Item an, was "npc" geh�rt
{
	oCItem *item;
	// Waffe testen
	item = GetWeapon();
	if (item && item->IsOwned(npc->GetInstance(),0)) {
		return item;
	}
	// Alles andere testen
	for (int i=0; i<invSlot.GetNumInList(); i++) {
		oCItem *item = GetSlotItem(i);
		if (item && item->IsOwned(npc->GetInstance(),0)) {
			return item;
		}
	}
	return NULL;
}

// ************************************************************************
// Monster - Specials
// ************************************************************************
/*�
zBOOL oCNpc :: CanTrollCallGobbo()
{
	if (GetTrueGuild()!=NPC_GIL_TROLL) return FALSE;
	// Nur wenn der Troll gerde nichts zu tun hat.
	if (GetEM()->IsEmpty()) {
		// Gobbos im letzten Zyklus wargenommen ?
		zCVob *vob;
		int max = vobList.GetNumInList();
		for (int i=0; i<max; i++) {	
			vob = vobList[i];
			if (vob->GetVobType()==zVOB_TYPE_NSC) {
				oCNpc* gobbo = (oCNpc*)vob;
				if (!gobbo->IsDead())
				if ((gobbo->GetTrueGuild()==NPC_GIL_GOBBO) && (!gobbo->already_thrown)) {
					// gefundenen Gobbo in "leader" speichern
					SetAsLeader (gobbo);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void oCNpc :: AI_TrollCallsGobbo()
{
	// Gefundenen Gobbo wurde in Leader gespeichert
	oCNpc* gobbo = GetLeader();
	if ((!gobbo) || (gobbo->IsDead())) return;
	// safety
	if (gobbo->GetTrueGuild()!=NPC_GIL_GOBBO) return;
	SetAsLeader(NULL);

	gobbo->GetEM()->Clear();
	// FIXME : Player !!!!
	gobbo->enemy = enemy = oCNpc :: player;
//	gobbo->GetNpcManager()->AI_GotoTroll(this);
	gobbo->already_thrown = TRUE;
}

zBOOL oCNpc :: HasHead()
// Fuers Zombie : Kopf noch dran ?
{
	zCModelNodeInst* headNode = GetModel()->SearchNode (zMDL_NODE_NAME_HEAD);
	if (!headNode) return FALSE;
	zCVisual* headMesh = headNode->GetNodeVisual();
	if (!headMesh) return FALSE;
	return TRUE;
}

zBOOL oCNpc :: HasDeadGobbo()
// Fuer Snapper : Gobbo im Maul ?
{
/*	oCNpcNodelist* node = nodelist.wurzel;
	while (node!=NULL) {
		if (node->vob->GetVobType()==zVOB_TYPE_NSC) {
			oCNpc *n = (oCNpc*)node->vob;
			if (n->guild==NPC_GIL_GOBBO) return TRUE;
		}
		node = node -> next;
	}*/
//	return FALSE;
//}

// **************************************************************************
// Hit - Funktionen
// **************************************************************************

void oCNpc :: Burn ( int damage, zREAL timems )
{
	/// FIXME : In den Zustand brennen setzen !
	if ((damage>0) && !fireVob) {	
		zCParticleFX* partFX	= zNEW( zCParticleFX() );
		zCVob* pfxVob			= zNEW( zCVob() ); 
		pfxVob -> SetVobName			("Particle_Test_Vob");
		pfxVob -> SetVisual				(partFX);
		partFX -> SetAndStartEmitter	("FIRE");
		partFX -> SetDontKillPFXWhenDone(TRUE);
		pfxVob -> SetCollDet			(FALSE);
		pfxVob -> SetPositionWorld		(GetPositionWorld());
		GetHomeWorld()->AddVobAsChild	(pfxVob,this);	
		pfxVob -> SetPositionWorld		(GetPositionWorld());	
		fireVob	= pfxVob;
		zRELEASE(partFX);
	}
	if (damage>fireDamage) {
		fireDamageTimer = 0;		// Schaden sofort wirken lassen.
		fireDamage		= damage;
	}

	this->ModifyBodyState( BS_MOD_BURNING, 0 );
}

void oCNpc :: StopBurn ()
{
	if (fireVob && GetHomeWorld()) {
		
		// Rauch starten
		zCParticleFX* partFX	= zNEW( zCParticleFX() );
		zCVob* pfxVob			= zNEW( zCVob() ); 
		pfxVob -> SetVobName			("Particle_Test_Vob");
		pfxVob -> SetVisual				(partFX);
		partFX -> SetAndStartEmitter	("FIRE_SMOKE_ONCE");
		pfxVob -> SetCollDet			(FALSE);
		pfxVob -> SetPositionWorld		(GetPositionWorld());
		GetHomeWorld()->AddVobAsChild	(pfxVob,this);	
		pfxVob -> SetPositionWorld		(GetPositionWorld());	

		fireDamageTimer = 0;
		fireDamage		= 0;

		zRELEASE(fireVob);
		zRELEASE(partFX);
		zRELEASE(pfxVob);
	}

	this->ModifyBodyState( 0, BS_MOD_BURNING );
}

zVEC3 RotateVec(zVEC3& pos, zVEC3& rotAxis, zREAL rotAngle, zREAL length)
{
	zMATRIX4 trafo	= Alg_Rotation3DN ( rotAxis, rotAngle );
	zVEC3 newPos	= pos + trafo.GetAtVector() * length;
	return newPos;
}

void oCNpc :: Interrupt(zBOOL checkBodyState, zBOOL stopWeaponChoose)
// Jede NSC-Aktion abbrechen !
{
	// ************************************
	// In den logischen Standmode schalten
	// ************************************
	// FIXME : Was ist mit Schwimmen/Tauchen ????
	oCAniCtrl_Human	*ac = GetAnictrl();	
	if (!ac) return;
	
	if ((ac->GetActionMode()!=ANI_ACTION_SWIM) && (ac->GetActionMode()!=ANI_ACTION_DIVE))
		ac -> SetActionMode(ANI_ACTION_STAND);

	// ************************************
	// Moeglicher Schlag wird abgebrochen
	// ************************************
	if (!GetBodyStateInterruptableOverride()) ac -> HitInterrupt();
	
	// ************************************
	// Magiekranz einfahren
	// ************************************
	oCMag_Book* mag = GetSpellBook();

	//
	//	CODECHANGE [CARSTEN]
	//
	if (mag) 
	{
		// Der Spieler oder NSCs mit gesetztem override-Flag d�rfen nicht den aktuellen Spell abbrechen, wenn sie getroffen werden
		if (stopWeaponChoose || (!IsAPlayer() && !GetBodyStateInterruptableOverride()))
		{
			if (mag->GetSelectedSpell()) {

				zTVFXState state = mag->GetSelectedSpell()->GetEffect()->GetState();
				// einen spell nur stoppen, wenn der caster am investieren ist
				if ( state == zVFXSTATE_INVESTNEXT ) mag->StopSelectedSpell();

			}			
				if (GetWeaponMode()!=NPC_WEAPON_MAG) 
				{
					mag->Close(TRUE);				
				}
		}
			
	} 
	//
	//	CODECHANGE [CARSTEN] END
	//
	
	// Patch 1.08 : MobInteraction vor ItemInteraction setzen....

	// *************************************
	// MobInteraction aus
	// *************************************
	if (GetInteractMob()) {
		
		// Falls Bodystate nicht interruptable ist, darf MobInteraktion nicht abgebrochen werden.
		// [Ulf]
		zBOOL endMobInteract = (!checkBodyState || this->IsBodyStateInterruptable());
		if (endMobInteract) 
		{
			// folgender Code spult die Ani zur�ck, anstatt sie hart zu pl�ppen
			// States zur�ck
			/*oCMobMsg* msg = zNEW(oCMobMsg(oCMobMsg::EV_STARTSTATECHANGE, this));
			msg->from = GetInteractMob()->GetState();
			msg->to = msg->from - 1;
			GetInteractMob()->GetEM()->OnMessage(msg, this);								
			SetInteractMob(NULL);*/
			GetInteractMob()->InterruptInteraction(this);
			SetInteractMob(NULL);
			
			// Safety :
			this->GetAnictrl()->SearchStandAni();
		}
	};

	// *******************************************************
	// ItemInteraction aus 
	// *******************************************************
	if (GetInteractItem()) {
		SetInteractItem (NULL);
		// Safety : ab 1.15c: etwaige Item Interaktions Anis werden gestoppt
		this->GetAnictrl()->SearchStandAni();
		interactItemCurrentState = -1;
	}

	// *************************************
	// Alle Anis auf h�heren Layer stoppen
	// *************************************
    if (GetVisual())
    {
    	GetModel() -> StopAnisLayerRange(2,1000);
    	GetModel() -> SetAniTransScale	(zVEC3(1,1,1));
    }

	// *************************************
	// Schluss mit Gerede !
	// *************************************	
	StopFaceAni		(NPC_TALK_ANI);
	StopTalkingWith	();

	//
	//	CODECHANGE [ROMAN]
	//
	StopAllVoices	();
	//
	//	CODECHANGE [ROMAN] END
	//
	
	// *************************************
	// Traden aus !
	// *************************************	
	if ( state.nextState.name != "ZS_ASSESSGIVENITEM" )
		CloseTradeContainer();

	// *************************************
	// Movement aus
	// *************************************	
	//zCVob* pVobObstacle = rbt.obstVob;
	RbtReset();
	//rbt.obstVob = pVobObstacle;

	// *************************************
	// Und weitere Vars zur�ck 
	// *************************************	
	ac->ResetAutoRoll();

	// FIXME: folgende zeilen machen bei mobsi benutzung probleme: liegt jemand im Bett und wird getroffen, so pl�ppt er _immer_ aus dem
	// bett. Seiteneffekte noch unklar
	// Update 1.21: Nun sind die Seiteneffekte klar:
	// Es kann hier Anih�nger geben. Da dieses Fragement nur auskommentiert wurde, weil Typen aus dem Bett pl�ppen, wird
	// der Code nicht aufgerufen, wenn der Bodystate BS_LIE ist
	// zum kotzen, das Standup w�hrend des Waffeziehens muss an dieser Stelle _IMMER_ drinbleiben
	// gibt zu viele Probleme ansonsten. Einzige M�glichkeit, die Waffe garantiert ziehen zu k�nnen, ist den Aufruf dieser Interrupt()
	// Methode zu vermeiden. Das ist allerdings nicht so einfach :)

	if ( ac->wmode!=WMODE_NONE )
	{
		// Gerade beim Waffe ziehen, abgebrochen !
		ac->wmode=WMODE_NONE;
		//
		this->StandUp( TRUE );
	}
}

int oCNpc :: GetWeaponDamage(oCItem* weapon)
// Kalkuliere Schaden dieser Waffe und ber�cksichtige die Resistenzen
{
	if (!weapon) return 0;
	int hp	= 0;
	int dam	= 0;

	// Resistenz einfliessen lassen.
	for (int i=0; i< oEDamageIndex_MAX; i++ ) {
		dam = weapon->GetDamageByIndex( (oEDamageIndex) i ) - GetProtectionByIndex( (oEDamageIndex) i );
		if (dam>0) hp += dam;
	}
	return hp;
}

int oCNpc :: GetBluntDamage(oCItem* weapon)
{
	if (!weapon) return 0;
	return weapon->GetDamageByIndex( oEDamageIndex_Blunt ) - GetProtectionByIndex( oEDamageIndex_Blunt );
}

/*--------------------------------------------------------------------------

   void oCNpc :: DropUnconscious(zREAL azi, oCNpc* attacker)


    13-Sep-00       [Max Dennis Luesebrink]

					wenn der character ohnmaechtig wird dann muss der focusmodus zurueck gesetzt werden
					weil er sonst keine gegenstaende in den focud nehmen kann wenn er wieder aufgestanden ist

	05-Oct-00		[Roman Keskenti]

						resets camera to normal mode in case the player was fighting
						thus avoiding "awaking" with activated fight-cam

--------------------------------------------------------------------------*/ 
void oCNpc :: DropUnconscious		(zREAL azi, oCNpc* attacker)
{
	if (IsUnconscious()) return;

	// [BENDLIN] Inventory
	if ( IsSelfPlayer() )
	{
		if (oCNpc::game_mode == NPC_GAME_STEAL || oCNpc::game_mode == NPC_GAME_PLUNDER)
			StopTheft(this, FALSE);
		
		oCMobContainer* mobContainer = dynamic_cast<oCMobContainer*>(GetInteractMob());
		if (mobContainer)
			mobContainer->Close(this);

		CloseInventory();

		SetMovLock(FALSE);
	}

	StopFaceAni		(NPC_TALK_ANI);
	DropAllInHand	();
	// Kein Waffenmodus mehr
	SetWeaponMode	(NPC_WEAPON_NONE);

	// Zustand ZS_UNCONSCIOUS starten
	SetAttribute					(NPC_ATR_HITPOINTS,1);
	SetBodyState					(BS_UNCONSCIOUS);
	parser.SetInstance				("OTHER",attacker);
	state.StartAIState				(NPC_AISTATE_UNCONSCIOUS,FALSE,AITIME_NO);
	
	// Animation starten
	oCMsgConversation*	msg		= NULL;
	if (abs(azi)<=90)	msg		= zNEW( oCMsgConversation(oCMsgConversation::EV_PLAYANI_NOOVERLAY,"T_STAND_2_WOUNDEDB"));
	else				msg		= zNEW( oCMsgConversation(oCMsgConversation::EV_PLAYANI_NOOVERLAY,"T_STAND_2_WOUNDED"));
	msg->SetHighPriority(TRUE);
	GetEM()->OnMessage	(msg,this);

	// passive Wahrnehmung senden
	if (attacker) AssessDefeat_S	(attacker);

	//
	//	CODECHANE [ROMAN]
	//
	if ( this->IsSelfPlayer() )
	{
		if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModNormal);
		//changed[dennis]
		oCNpcFocus::SetFocusMode(FOCUS_NORMAL);
		oCNpc::player->CloseInventory();
	}
	//
	//	CODECHANE [ROMAN]
	//
}

void oCNpc :: CheckUnconscious()
{
	zCModel* model = GetModel();

	if (!model) return;
	if (!model->IsAniActive("T_STAND_2_WOUNDEDB") && !model->IsAniActive("T_STAND_2_WOUNDED") && !model->IsAniActive("S_WOUNDEDB") && !model->IsAniActive("S_WOUNDED") && !model->IsAniActive("T_WOUNDEDB_2_DEADB") && !model->IsAniActive("T_WOUNDED_2_DEAD") && !model->IsAniActive("T_WOUNDED_TRY") && !model->IsAniActive("T_WOUNDEDB_TRY")) {
		oCMsgConversation*	msg		= zNEW( oCMsgConversation(oCMsgConversation::EV_PLAYANI_NOOVERLAY,"T_STAND_2_WOUNDEDB"));
		msg->SetHighPriority(TRUE);
		GetEM()->OnMessage	(msg,this);			
	}
}

zSTRING oCNpc :: GetInterruptPrefix()
{
	if (GetInteractMob()) {
		return GetInteractMob()->GetScemeName();
	}
	return "";
}

void oCNpc :: CompleteHeal()
{
	attribute[NPC_ATR_HITPOINTS]= attribute[NPC_ATR_HITPOINTSMAX];
	attribute[NPC_ATR_MANA]		= attribute[NPC_ATR_MANAMAX];
}

zBOOL oCNpc :: IsDead()
{
	return (attribute[NPC_ATR_HITPOINTS]<=0);		
}

zBOOL oCNpc :: IsUnconscious()
{
	return (state.IsInState(NPC_AISTATE_UNCONSCIOUS));
}

void oCNpc :: DoDie (oCNpc* attacker)
// NSC stirbt
{
	// [BENDLIN] Inventory
	if ( IsSelfPlayer() )
	{
		if (oCNpc::game_mode == NPC_GAME_STEAL || oCNpc::game_mode == NPC_GAME_PLUNDER)
			StopTheft(this, FALSE);
		
		oCMobContainer* mobContainer = dynamic_cast<oCMobContainer*>(GetInteractMob());
		if (mobContainer)
			mobContainer->Close(this);

		CloseInventory();

		SetMovLock(FALSE);
	}

	Interrupt();

	StopFaceAni		(NPC_TALK_ANI);

	GetAnictrl()->SetConfigDoSurfaceAlign(zCAIPlayer::zMV_SURFACE_ALIGN_NORMAL);
	if (IsSelfPlayer()) {
		// Camera einstellen
		if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModDeath);
		SetFocusVob(NULL);
	} 
	// Und Jingle starten
	// if (enemy && enemy->IsAPlayer()) zmusic->PlayJingleByScript("JINGLEKILLEDFOE");
	// Todesschrei / Ani ?
	// Reaction(dies,NULL);
	// Alles fallen lassen
	//GetAIManager()->SetInsertMode(oCAIManager::INSERT_BEFORE);
	DropAllInHand();
	// Kein Waffenmodus mehr
	if (!IsMonster()) SetWeaponMode(NPC_WEAPON_NONE);
	
	// Jetzt mal mit Brennen aufh�ren
	StopBurn();
	GetAnictrl()->StopTurnAnis();

	//BodyState setzten
	this->SetBodyState( BS_DEAD );

	// Death-State aktivieren
	this->ClearPerception();
	
	// Patch 1.08 : Manchmal werden beim Tod keine XPs vergeben.
	//              Lag daran, dass 2x DoDie aufgerufen wurde (DoAI::IsDead())...
	//              einmal mit Attacker und einmal ohne.
	//			    Darum hier Abfrage ob sicher der NSC nicht schon in ZS_Dead befindet, 
	//				damit Logik nicht ein 2x aktiviert wird
	if (!state.IsInState(NPC_AISTATE_DEAD)) {
		// Save & restore current other
		void*			oldOther	= NULL;
		zCPar_Symbol*	sym			= parser.GetSymbol("OTHER");
		if (sym)		oldOther	= sym->GetInstanceAdr();
		parser.SetInstance	("OTHER",attacker);
		state.StartAIState	(NPC_AISTATE_DEAD,FALSE,AITIME_NO);
		parser.SetInstance	("OTHER",oldOther);
	}

	SetPhysicsEnabled	(TRUE);

	// Hat irgendjemand diesen feigen Mord gesehen ?
	if (attacker) AssessMurder_S (attacker);			

	// Respawning aktivieren ?
	if (CanRespawn()) {
		// SpawnDelay ist hier SpielStunden
		zERR_MESSAGE(5,0,"U: NPC: Respawning NPC "+GetInstanceName()+" in "+zSTRING(int(spawnDelay))+" gamehours.");		
		oCNpc* newNpc = ogame->GetSpawnManager()->SpawnNpc(GetInstance(),spawnPoint,spawnDelay * WLD_TICKSPERHOUR);
		if (newNpc) {
			newNpc->SetCanRespawn(TRUE);
			newNpc->spawnDelay = spawnDelay;	
			newNpc->SetSpawnInRangeAllowed(FALSE);	//  Nicht sofort respawnen....
		}
		// Nur einmal respawnen, dann reichts (alles weitere macht die neue Instanz);
		this->SetCanRespawn(FALSE);

	}
	
	// Tote haben letztendlich immer 0 Lebenspunkte
	this->SetAttribute(NPC_ATR_HITPOINTS, 0);
};

void oCNpc :: StartFadeAway()
{
	SetCollDetDyn		(FALSE);
	SetSleeping			(FALSE);
	ClearPerception		();
	ClearPerceptionLists();
	DropInventory		();
	// FadeAway-State aktivieren.
	state.StartAIState	(NPC_AISTATE_FADEAWAY,FALSE,AITIME_NO);
	fadeAwayTime		= NPC_FADEAWAY_TIME;			// 5 Sekunden
	respawnTime			= (zREAL)spawnDelay * 1000;
}

zBOOL oCNpc :: IsFadingAway()
{
	return state.IsInState(NPC_AISTATE_FADEAWAY);
};

zBOOL oCNpc :: FadeAway()
{
	fadeAwayTime -= ztimer.GetFrameTimeF();
	if (fadeAwayTime>0) {
		// inventory2.EmptyInventoryToWorld();
		SetVisualAlphaEnabled	(TRUE);
		SetVisualAlpha			(fadeAwayTime / NPC_FADEAWAY_TIME);	
	} else {
		SetVisualAlphaEnabled	(TRUE);
		SetVisualAlpha			(0.0f);
		ogame->GetGameWorld()->DisableVob(this);
		ogame->GetSpawnManager()->DeleteNpc(this);
		return TRUE;
	}
	return FALSE;
};

/*--------------------------------------------------------------------------

    zBOOL oCNpc :: BeamTo

    26-Sept-00	[SPECKELS]
				Ausrichtung (AtVector) auch fuer Nicht-Waypoints  beruecksichtigt.

--------------------------------------------------------------------------*/

zBOOL oCNpc :: BeamTo	(const zSTRING& targetVob)
// Target kann sein :
// a) Waypoint
// b) Freepoint
// c) anderer Vob
{
	zMAT4 startMatrix	= Alg_Identity3D();
	zVEC3 startPos		= zVEC3(0,0,0);
	zVEC3 startAt		= zVEC3(1,0,0);

	zCVob* vob		= NULL;
	zCWaypoint* wp	= ogame->GetWorld()->GetWayNet()->GetWaypoint(targetVob);
	if (wp) {
		/*
		startMatrix.SetTranslation	( wp->GetPositionWorld() );
		startMatrix.SetAtVector		( wp->GetAtVectorWorld() );	
		startMatrix.MakeOrthonormal	();
		*/
		startPos	= wp->GetPositionWorld();		
		startAt		= wp->GetAtVectorWorld();

	} else {
		vob = ogame->GetWorld()->SearchVobByName(targetVob);
		if (vob) {
			// startMatrix = vob->trafoObjToWorld; [SPECKELS] Matrix auch fuer Beam zum Freepoint, damit Ausrichtung uebernommen wird.
			/*
			startMatrix.SetTranslation	( vob->GetPositionWorld() );
			startMatrix.SetAtVector		( vob->GetAtVectorWorld() );	
			startMatrix.MakeOrthonormal	();
			*/
			startPos	= vob->GetPositionWorld();						
			startAt		= vob->GetAtVectorWorld();
		}
	}
	if (!wp && !vob) {
		zERR_WARNING("U: NPC: Way- or Freepoint not found :"+targetVob);
		return FALSE;
	};

	// [BENDLIN] Addon Patch2 - bei AI_Teleport wurde SELF �berschrieben
	oCNpc* oldSelfNpc = NULL;
	zCPar_Symbol* sym = parser.GetSymbol("SELF");
	if (sym)
		oldSelfNpc = dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());

	// Und hier wieder aktivieren
	SetCollDet			(FALSE);
	// SetTrafoObjToWorld	(startMatrix);

	startAt.n[VY]=0;
	SetPositionWorld	(startPos);	
	SetHeadingAtWorld	(startAt);
	SetCollDet			(TRUE);
	Enable				(GetPositionWorld());
		
	// Kamera entsprechende Meldungen schicken
	if (IsSelfPlayer()) {
		zCAICamera* aiCam = zCAICamera::GetCurrent();
		if (aiCam) {
			aiCam->ClearTargetList	();
			aiCam->SetTarget		(oCNpc::player);
			// [BENDLIN] Addon - Ghost Alpha
			if (NPC_FLAG_GHOST == (oCNpc::player->variousFlags & NPC_FLAG_GHOST))
				aiCam->SetTargetAlpha(zoptions->ReadReal("INTERNAL", "GhostAlpha", 0.3f));
			aiCam->ReceiveMsg		(zPLAYER_BEAMED);
			aiCam->SetMode			(CamModNormal);			
		};
	}

	// sofortiges Spawning aktivieren
	ogame->GetSpawnManager()->SpawnImmediately();

	// [BENDLIN] Addon Patch2 - bei AI_Teleport wurde SELF �berschrieben
	parser.SetInstance("SELF", oldSelfNpc);
	
	return TRUE;
};

void oCNpc :: DropInventory()
{
/*	if (!GetHomeWorld()) return;
	
	zBOOL inMove = GetInMovement();
	if (inMove) EndMovement();
	
	zVEC3 fit;
	oCItem* item = NULL;
	for (int i=0; i<INV_MAX; i++) {
		// Komplette Listen l�schen
		zCListSort<oCItem> *node = inventory2.GetFirstNode(i);
		while (node) {
			// aus globalen Listen entfernen
			item = node->GetData();
			node = node->GetNextInList();
		
			item = inventory2.Remove(item,item->GetAmount());
			item->SetCollDetDyn(TRUE);
			item->ResetRotationsLocal();
			GetHomeWorld()->AddVob(item);
			fit = GetPositionWorld() + zVEC3(0,50,0);
			if (!item->SearchNpcPosition(fit)) {
				zERR_WARNING("U: NPC: Not enough Space to drop item "+item->GetInstanceName());
			};
			item->SetPositionWorld	(fit);
			item->SetPhysicsEnabled	(TRUE);
			item->GetRigidBody()->SetGravityEnabled(TRUE);
			item->GetRigidBody()->SetVelocity(zVEC3((zRand()%200)-100,zRand()%100,(zRand()%200)-100));
			item->SetCollDetStat (TRUE);
			item->SetCollDetDyn	 (TRUE);
			item->SetSleeping	 (FALSE);
		}
	}
	
	if (inMove) BeginMovement();*/
};

zBOOL oCNpc :: HasInHand(int instance)
{
	oCVob* pVobRight = this->GetRightHand();
	oCVob* pVobLeft  = this->GetLeftHand ();

	if ( pVobRight )
	if ( pVobRight->GetInstance() == instance ) return TRUE;

	if ( pVobLeft )
	if ( pVobLeft ->GetInstance() == instance ) return TRUE;

	return FALSE;
}

zBOOL oCNpc :: HasInHand(zCVob* what)
{
	zCVob* vob = GetSlotVob(NPC_NODE_RIGHTHAND);
	if (vob==what) return TRUE;

	return (GetSlotVob(NPC_NODE_LEFTHAND) == what);
}


void oCNpc :: DropAllInHand()
// Alles in den Haenden fallenlassen
{
	DropFromSlot (NPC_NODE_RIGHTHAND);
	DropFromSlot (NPC_NODE_LEFTHAND);
	
	if (!IsDead()) {
		oCAniCtrl_Human*	anictrl = GetAnictrl();
		zCModel*			model	= GetModel();
		int wl = anictrl->GetWaterLevel(); 
		if (wl==0)	{
			anictrl->SetWalkMode(ANI_WALKMODE_RUN);		
			model->StartAni(anictrl->_s_walk);
		} else if (wl==1) {
			anictrl->SetWalkMode(ANI_WALKMODE_WALK);
			model->StartAni(anictrl->_s_walk);
		} else if (wl==2) {
			anictrl->SetWalkMode(ANI_WALKMODE_SWIM);
			anictrl->SetState(oCAniCtrl_Human::zMV_STATE_SWIM);
			model->StartAni(anictrl->s_swim);
		}
	};
    
    /* [Moos] dieser Hack wird nun nicht mehr gebraucht
    if (mag_book)
    {
        OpenSpellBook();          // [Moos] werde Runen los
        CloseSpellBook(TRUE);
    }
    */
}

oCItem *oCNpc :: GetWeapon()
{
	if (fmode<=NPC_WEAPON_FIST)	return NULL; else
	if (fmode<=NPC_WEAPON_2HS)	return GetSlotItem(NPC_NODE_RIGHTHAND); else
	if (fmode==NPC_WEAPON_CBOW) return GetSlotItem(NPC_NODE_RIGHTHAND);	else
								return GetSlotItem(NPC_NODE_LEFTHAND);
}

oCItem* oCNpc :: GetEquippedMeleeWeapon()
{
//	return inventory.FindItem(NPC_INV_NEARWEAPON,ITM_FLAG_ACTIVE);	
	oCItem*		item = GetSlotItem(NPC_NODE_SWORD);
	if (!item)	item = GetSlotItem(NPC_NODE_LONGSWORD);
	return item;
}

oCItem* oCNpc :: GetEquippedRangedWeapon()
{
	oCItem*		item = GetSlotItem(NPC_NODE_BOW);
	if (!item)	item = GetSlotItem(NPC_NODE_CROSSBOW);
	return item;
}

oCItem* oCNpc :: GetEquippedArmor()
{	
	return GetSlotItem(NPC_NODE_TORSO);
}

/*
oCItem* oCNpc :: GetEquippedHelm()
{
	zCList<oCItem>* node = inventory2.GetFirstNode(NPC_INV_ARMOR);
	return NULL;
	//GetSlotItem(NPC_SLOT_TORSO);
}
*/

/*
int  oCNpc :: GetDistanceArea(zREAL &d)
// in welchem Bereich befindet sich der aktuelle Gegner ?
{
	return GetDistanceArea(enemy,d);																	return 5;
}

int  oCNpc :: GetDistanceArea( zCVob *vob, zREAL &d )
// in welchem Bereich befindet sich der aktuelle Gegner ?
// 0 - Nahkampf
// 1 - Waffenreichweite
// 2 - Waffenreichweite + 1m ( Angriff mit Ausfallschritt )
// 3 - "Lauer"-Reichweite	 ( Kampfsteps zwecks Reizen des Spielers )
// 4 - Ausser Reichweite
{
	if (!vob) return 2;

	zVEC3 posz	= vob->GetPositionWorld();
	zVEC3 poss	= GetPositionWorld();
	// Down 2 2 Dims
	posz[VY]	= poss[VY];
	d			= (posz - poss).Length();

	if (d < fight_range)											return 0; else
	if (d < fight_range +     fight_step_len)						return 1; else
	if (d < fight_range + 2 * fight_step_len)						return 2; else
	if (d < fight_range + 4 * fight_step_len)						return 3; else
	if (d < fight_range + 4 * fight_step_len + fight_run2walk_len)	return 4; else
																	return 5;
}
*/
zBOOL oCNpc :: IsSameHeight(zCVob* other)
{
	if (!other) return FALSE;
	// H�he der Boundingboxes ermitteln
	zTBBox3D	box1	= GetBBox3DWorld();
	zTBBox3D	box2	= other -> GetBBox3DWorld();
	zREAL		y1		= GetPositionWorld()[VY];
	zREAL		y2		= other -> GetPositionWorld()[VY];
	// h�her oder tiefer gelegen ?
	zREAL maxdiff		= (box2.maxs[VY] - box2.mins[VY]) / 4;
	if (y2<y1) {
		// Other steht tiefer als this
		return (box2.maxs[VY] - maxdiff >= box1.mins[VY] );
	} else {
		return (box1.maxs[VY] - maxdiff >= box2.mins[VY] );
	}
}

/* ----------------------------------------------------------------------

	void oCNpc :: TurnToEnemy()
	
	 22.09.2000	[Dennis]	

				Azimuth holen
	 23.09.2000	[Dennis]	

				GetFocuVob statt enemy

   ---------------------------------------------------------------------- */

// wird nur f�r den spieler aufgerufen, f�r WeaponMode>NONE und wenn pariert wird
void oCNpc :: TurnToEnemy()
{

	if (IsSelfPlayer())
	{
		if (!enemy) return;
	
		if ( zCAICamera::GetCurrent()							    && 
			 zCAICamera::GetCurrent()->GetMode()==CamModFirstPerson ) 
			 return;

		if (!oCGame::GetUseOldControls() && !zinput->GetMouseIdle() && !oCNpc::GetTargetLocked()) return;
	}
	if (enemy) 
	{
		// Get Angle
		float azi,elev;
		GetAngles(enemy,azi,elev);

		//if ( zAbs(azi) <= oCNpcFocus::focus->GetAzi() ) 
		{
			if (zAbs(azi)<=1) return;

			//
			//	CODECHANGE [ROMAN]
			//
			zVALUE winkel = this->GetTurnSpeed() * ztimer.GetFrameTimeF() * 4;	
			//
			//	CODECHANGE [ROMAN] END
			//

			if (azi<0) 
				azi = zMax(azi,-winkel);
			else
				azi = zMin(azi,winkel);
				
			RotateLocalY(azi);
		}
	}
}


zBOOL oCNpc :: ShieldEquipped ()
{
	return !IsSlotFree(NPC_NODE_SHIELD);
}

int oCNpc :: GetWeaponDamage ()
// Liefere Gesamtschaden der aktuellen Waffe
{
	oCItem *item = GetWeapon();
	if (item) {
		return item->GetFullDamage();
	} else
		return 0;
};

// ********************************************************************
// Animationen
// ********************************************************************

void oCNpc :: SetMovLock ( zBOOL f )
{
	if (f==movlock) return;
	movlock = f;	
/*
	if (f)	zERR_MESSAGE(4,0,"B: NPC: MovLock ON");
	else	zERR_MESSAGE(4,0,"B: NPC: MovLock OFF");	
	*/
}

zBOOL oCNpc :: IsMovLock()
{
	return movlock;
}

void oCNpc :: SetHead()
// Resets the current Head of model
{
	zCModel *model = GetModel();
	if (model) {
		// Head
		if (!head_visualName.IsEmpty()) {
			zCModelNodeInst* head = model -> SearchNode(zMDL_NODE_NAME_HEAD);
			if (head) {
				// Kopf ein MorphMesh ?
				zSTRING v = GetVisualHead();
				if (!v.IsEmpty()) {
					// Jawoll, Morphmesh laden
					zCMorphMesh* mms = zCMorphMesh :: Load (v);
					model -> SetNodeVisual (head,mms);
					
					// .. load mms, in model in richtige Node einfuegen..
					// ASSERT: Texturen fuer den 'Kopf' enthalten den String "HEAD", alle anderen nicht (analog fuer Zaehne/TEETH)
					mms->SetTextureVar	(0, head_TexVarNr  , &zSTRING("HEAD"));
					mms->SetTextureVar	(1, body_TexColorNr, &zSTRING("HEAD"));
					mms->SetTextureVar	(0, teeth_TexVarNr , &zSTRING("TEETH"));
//					mms->AddRandAni		(mms->SearchAni(ANI_EYEBLINK), 0.15F, 0.1F, 3.8F, 1.0F, 0.2F);


					zRELEASE(mms);
						
/*						
					model->SetNodeMeshTexture (zMDL_NODE_NAME_HEAD, 0, head_TexVarNr	,&zSTRING("HEAD"));                // head texture
					model->SetNodeMeshTexture (zMDL_NODE_NAME_HEAD, 1, body_TexColorNr	,&zSTRING("HEAD"));                // head skin color
//					model->SetNodeMeshTexture (zMDL_NODE_NAME_HEAD, 1, body_TexVarNr	,&zSTRING("HEAD"));                // head skin color
					model->SetNodeMeshTexture (zMDL_NODE_NAME_HEAD, 0, teeth_TexVarNr	,&zSTRING("TEETH"));               // teeth texture
*/
				} 
			}
		}
		// und standard Face-Ani
		// ->AddRandAni(face->SearchAni("R_EYESBLINK"), 0.15F, 0.1F, 3.8F,1.0F, 0.2F);
	}
}

void oCNpc :: SetAdditionalVisuals (zSTRING &vBody, int bodyTexNr, int bodyColor, zSTRING &vHead, int headTexNr, int teethTexNr, int armorInstance)
{
	// The Body
	body_visualName	= vBody;
	body_TexVarNr	= bodyTexNr;
	body_TexColorNr	= bodyColor;
	// The Head
	head_visualName	= vHead;		head_visualName.Upper();
	head_TexVarNr	= headTexNr;
	// The Teeth
	teeth_TexVarNr	= teethTexNr;

	if (ogame && !ogame->IsInLoadSaveGame()) {
		// Armor erzeugen ?
		if (armorInstance>0) {
			// Item erschaffen
			oCItem* item = (oCItem*) ogame -> GetGameWorld() -> CreateVob(zVOB_TYPE_ITEM,armorInstance);
			// aktivieren
			if (item && (item->wear&ITM_WEAR_TORSO)) {
				// Als erstes ins Inventory packen
				PutInInv	(item);
				// Dann anlegen -> dadurch wird InitModel() von PutInSlot aufgerufen.
				EquipArmor	(item);
				zRELEASE	(item);
				return;
			}
			zRELEASE (item);
		} 
	}

    if (GetVisual())
	    InitModel();
}

/*
void oCNpc :: SetAdditionalVisuals (zSTRING &body_asc, int body_var, int body_col, zSTRING& head_mms, int head_tex, zSTRING& head_form)
{
	// Body
	body_mesh_ASC_Name	= body_asc;
	body_Tex_Var_Nr		= body_var;
	body_Tex_Color_Nr	= body_col;
	// Head
	head_MMS_Name		= head_mms;
	head_Tex_Nr			= head_tex;
	head_Form_Name		= head_form;
	// Do It !
	InitModel();
}

void oCNpc :: InitModel()
{
	zCModel* model = GetModel();
	if (model) {
		// K�rper 
		// a) Body 
		model->SetModelMesh		(body_mesh_ASC_Name, TRUE);
		// mesh
		model->SetModelTexture	(0, body_Tex_Var_Nr, "", "", "");
		// skin variation 
		// skin color
		model->SetModelTexture  (1, body_Tex_Color_Nr   , "", "", "");          
		// Kopf / Helm setzen
		SetHead			();
		SetShowVisual	(TRUE);
	}
};

void oCNpc :: SetHead()
// Resets the current Head of model
{
	zCModel *model = GetModel();
	if (model) {
		// ******
		// Head
		// ******
		zCModelNodeInst* head = ani_model -> SearchNode(zMDL_NODE_NAME_HEAD);
		if (head && !visual_head.IsEmpty()) {
			// Kopf ein MorphMesh ?
			zSTRING v = GetVisualHead();
			if (v.Search("MMS")>0) {
				// Jawoll, Morphmesh laden
				zCMorphMesh* mms = zCMorphMesh :: Load (v);
				ani_model -> SetNodeVisual (head,mms);
				// Kopfform setzen ?
				if (!visual_headform.IsEmpty()) {
					StartFaceAni(visual_headform);
				}
				// .. load mms, in model in richtige Node einfuegen..
				model->SetModelTexture(0, head_Tex_Nr, "HEAD", "", "");
				// head texture 
				// head skin color
				model->SetModelTexture(1, body_Tex_Color_Nr, "HEAD", "", "");
			}
		}
		
		// Hair or Helm ?
		zCModelNodeInst *node = ani_model -> SearchNode("ZS_HELMET");
		zCVisual  *vis;
		zCMesh	  *mesh;
		if (node!=NULL) {
			if (invslot[NPC_SLOT_HEAD]!=NULL) {
				// Helm
				vis	= invslot[NPC_SLOT_HEAD] -> GetVisual();
				mesh= (zCMesh *) vis;
				//node -> SetNodeVisual( mesh );
				ani_model -> SetNodeVisual( node, mesh );
				ani_model -> SetModelTexture (0, 0, "HELMET", "", "");				
			} /*else if (hair!=NULL) {
				vis	= hair -> GetVisual();
				mesh= (zCMesh *) vis;
				//node -> SetNodeVisual( mesh );
				ani_model -> SetNodeVisual( node, mesh );
				ani_model -> SetModelTexture (0, visual_hair, "HELMET", "", "");
			}
		}
		ani_model->SetModelTexture (0, visual_face, "KOPF", "", "");
	}
}
*/
/*
void oCNpc :: InitModel()
{
//	GetModel()->SetModelMesh( GetVisualBody() );
	zCModel *model;
	if (model = GetModel()) {
		// Koerper setzen
//		body_TexColorNr = 3;
		if (!body_visualName.IsEmpty()) {
			// ASSERT: Texturen fuer den 'Body' enthalten den String "BODY", 
			// alle anderen nicht (analog fuer Ruestung/Armor)
			model->RemoveMeshLibAll                 ();                                                                          
			model->ApplyMeshLib                     (body_visualName);														// mesh
			model->SetMeshLibTexture                (body_visualName, 0, body_TexVarNr  ,&zSTRING("BODY"));					// skin tex variation
			model->SetMeshLibTexture                (body_visualName, 1, body_TexColorNr,&zSTRING("BODY"));					// skin tex color
			model->SetMeshLibTexture                (body_visualName, 0, 0				,&zSTRING("ARMOR"));				// armor tex variation
		}
		// Kopf setzen
		SetHead			();
		SetShowVisual	(TRUE);
		// Und SelfDistance errechnen f�r exakte Kampfentfernung
		zCModelPrototype* proto = model->GetModelProto();
		selfDist = proto->GetBBox3D().maxs[VZ] - proto->GetRootNodeTrans()[VZ];
	}
}
*/
void oCNpc :: InitModel()
{
	zCModel *model = GetModel();
	if (model) {
		zSTRING meshLib		= body_visualName;
		int		armorSkinNr	= 0;
		
		// R�stung angezogen, dann diese Meshlib benutzen
		oCItem* armor		= GetEquippedArmor();
		if (armor) {
			meshLib			= armor->GetVisualChange();
			armorSkinNr		= armor->visual_skin;
		}

		// Koerper setzen
		if (!meshLib.IsEmpty()) {
			// ASSERT: Texturen fuer den 'Body' enthalten den String "BODY", 
			// alle anderen nicht (analog fuer Ruestung/Armor)
			model->RemoveMeshLibAll                 ();                                                                          
			model->ApplyMeshLib                     (meshLib);														// mesh
			model->SetMeshLibTexture                (meshLib, 0, body_TexVarNr  ,&zSTRING("BODY"));					// skin tex variation
			model->SetMeshLibTexture                (meshLib, 1, body_TexColorNr,&zSTRING("BODY"));					// skin tex color
			model->SetMeshLibTexture                (meshLib, 0, armorSkinNr	,&zSTRING("ARMOR"));				// armor tex variation
		}
		// Kopf setzen
		SetHead			();
		SetShowVisual	(TRUE);
		// Und SelfDistance errechnen f�r exakte Kampfentfernung
		zCModelPrototype* proto = model->GetModelProto();
		// vorher : ????? selfDist = proto->GetBBox3D().maxs[VZ]; 
		selfDist = proto->GetBBox3D().maxs[VZ] - proto->GetRootNodeTrans()[VZ];

		// FIXME: Hier gab es ein IrrLicht NSC Problem. selfDist war -4. Vermutlich PFX BBox Problem
		// Durch Workaround hier behoben
		if (selfDist<=0) selfDist = 150;

//		zERR_ASSERT(selfDist>0);
	
		//zERR_WARNING("U:TEST: 1."+GetInstanceName()+" SelfDist :"+zSTRING(int(selfDist)));
	}

    // fackeloverlay?
	// [EDENFELD] ab 1.25 interessieren wir uns nicht mehr f�r die Fackeloverlay Anis
    //oCItem *torch = GetSlotItem(NPC_NODE_LEFTHAND);
    //SetTorchAni(torch && torch->GetObjectName() == S_ITLSTORCHBURNING, FALSE);
}


zCModel *oCNpc :: GetModel ()
{
    zCModel *ret = zDYNAMIC_CAST<zCModel>(GetVisual());
    if (ret) return ret;

    AvoidShrink();

	return zDYNAMIC_CAST<zCModel>(GetVisual());
}

zSTRING oCNpc :: GetVisualBody()
{
	return body_visualName;
}

zSTRING oCNpc :: GetVisualHead()
{
	return head_visualName;
}

zBOOL oCNpc :: StartFaceAni	(const zSTRING& name, zREAL intensity, zREAL holdtime)
{
	zCModel* model = GetModel();
	if (!model) return FALSE;
	// Search HeadNode
	zCModelNodeInst* head = model->SearchNode(zMDL_NODE_NAME_HEAD);
	if (!head) return FALSE;
	// Getting the Visual
	zCMorphMesh* vis = zDYNAMIC_CAST<zCMorphMesh> (head->GetNodeVisual());
	if (vis) {
		vis -> StartAni(name,intensity,holdtime);
		return TRUE;
	}	
	return FALSE;
}

zBOOL oCNpc :: StartStdFaceAni	(int attitude)
{
	// Starte Gesichtsanimation in Abh�ngigkeit von der Attitude zum NSC
	zSTRING s;
	switch (attitude) {
		case NPC_ATT_HOSTILE	:	s = "S_HOSTILE";	break;
		case NPC_ATT_ANGRY		:	s = "S_ANGRY";		break;
		case NPC_ATT_NEUTRAL	:	s = "S_NEUTRAL";	break;
		case NPC_ATT_FRIENDLY	:	s = "S_FRIENDLY";	break;
	}
	return StartFaceAni(s);
}

zBOOL oCNpc :: StopFaceAni	(const zSTRING& name)
{
    if (!GetVisual())
        return TRUE;

	// Search HeadNode
	zCModelNodeInst* head = GetModel()->SearchNode(zMDL_NODE_NAME_HEAD);
	if (!head) return FALSE;
	// Getting the Visual
	zCMorphMesh* vis = zDYNAMIC_CAST<zCMorphMesh> (head->GetNodeVisual());
	if (vis) {
		vis -> StopAni		(name);
//		vis -> StartAni		("S_NEUTRAL");
//		vis -> AdvanceAnis	();
/*		vis -> StartAni		("S_ANGRY");
		vis -> AdvanceAnis	();
		vis -> StartAni		("S_HOSTILE");
		vis -> AdvanceAnis	();
		vis -> StartAni		("S_NEUTRAL");
		vis -> AdvanceAnis	();*/
		return TRUE;
	}	
	return FALSE;
}

int oCNpc :: GetWeaponMode()
{
	// Patch 1.08 : Safety....
	if ((fmode<0) || (fmode>=NPC_WEAPON_MAX)) fmode = NPC_WEAPON_NONE;
	return fmode;
};

void oCNpc :: SetWeaponMode2(const zSTRING& mode)
// Ermittle aus dem String den Waffenmodus
{
	int fm = NPC_WEAPON_NONE;

	if (mode=="FIST") {
		fm = NPC_WEAPON_FIST;
	} else if ((mode=="1H") || (mode=="1HS")) {
		// 1H kann sein : NPC_WEAPON_1HS, NPC_WEAPON_1HA
		fm = NPC_WEAPON_1HS;
	} else if ((mode=="2H") || (mode=="2HS")) {
		fm = NPC_WEAPON_2HS;
	} else if (mode=="BOW") {
		fm = NPC_WEAPON_BOW;
	} else if (mode=="CBOW") {
		fm = NPC_WEAPON_CBOW;
	} else if (mode=="MAG") {
		fm = NPC_WEAPON_MAG;
	}
	SetWeaponMode2(fm);
}

void oCNpc :: SetWeaponMode2(int fm)
{
    AvoidShrink();

	// Toggle den Waffenmodus - dazu geh�rt :
	// a) Animationen f�r Waffenmodus initialisieren 
	// b) SlotWechsel der Waffen durchf�hren
	// c) aktuellen Walkmodus beibehalten
	
	if (fm==fmode) return;

	// 1. Fall : NONE to WEAPON
	// *************************
	// Waffe equippen
	// *************************

	if (fmode==NPC_WEAPON_NONE) {

		if( human_ai->IsSprintActive() ) human_ai->SetSprintMode( FALSE );

		zSTRING from;
		zSTRING to;
		
		// Waffe ziehen im Rennen erm�glichen
		oCAniCtrl_Human* ac		= GetAnictrl();
		zCModel* model			= GetModel();

		zBOOL walking			= FALSE;
		if (ac) walking			= ac->IsWalking() || model->IsAniActive(ac->_t_walkl_2_walk) || model->IsAniActive(ac->_t_walkr_2_walk);
		zBOOL standing			= model->IsAniActive(ac->_s_walk);

		// Stand-Ani als Follow Ani ? muss beruecksichtigt werden, sonst gibt's Ani-Haenger
		zCModelAniActive* cAni	= NULL;
		if (model) {
			cAni			= model->GetActiveAni(ac->_t_walkl_2_walk);
			if (!cAni) cAni = model->GetActiveAni(ac->_t_walkr_2_walk);
		}

		// Startslot
		switch (fm) {
			case NPC_WEAPON_DAG : case NPC_WEAPON_1HS : from = NPC_NODE_SWORD;		break;
			case NPC_WEAPON_2HS :						from = NPC_NODE_LONGSWORD;	break;
			case NPC_WEAPON_BOW :						from = NPC_NODE_BOW;		break;
			case NPC_WEAPON_CBOW:						from = NPC_NODE_CROSSBOW;	break;
		}
		// ZielSlot
		switch (fm) {
			case NPC_WEAPON_DAG : case NPC_WEAPON_1HS : case NPC_WEAPON_2HS : case NPC_WEAPON_CBOW :
								  to = NPC_NODE_RIGHTHAND;		
								  break;
			case NPC_WEAPON_BOW : to = NPC_NODE_LEFTHAND;	
								  break;
			case NPC_WEAPON_MAG :	{
										oCMag_Book* sb = GetSpellBook();
										if (walking) {
											// Falls im Gehen Waffe ziehen, Magiekranz nicht mit ausfahren, 
											// sondern nur den letzten Spell wieder aktivieren.
											if (sb) {
												sb->Open				(FALSE);
												sb->SetShowHandSymbol	(TRUE);
											}

										} else if (sb && sb->IsOpen()) {
											// Bereits aktiv, dann wurde Auswahl getroffen
								   			GetEM()->OnMessage(zNEW( oCMsgMagic(oCMsgMagic::EV_CLOSE,fm,FALSE)),this);
											//CloseSpellBook(fm,FALSE);
										} //else {
										//	GetEM()->OnMessage(zNEW( oCMsgMagic(oCMsgMagic::EV_OPEN,fm,TRUE)),this);
											//OpenSpellBook(fm);
									//	}
									}
									break;
		}

		// Und graphischen Wechsel durchf�hren
		if (!from.IsEmpty() && !to.IsEmpty()) {
			// Slot Wechseln
			TNpcSlot* slot1	= GetInvSlot(from);
			TNpcSlot* slot2 = GetInvSlot(to);
			zBOOL inInv1	= slot1->inInventory;
			zBOOL inInv2	= slot2->inInventory;
			oCVob* vob1		= RemoveFromSlot(slot1, TRUE, FALSE);
			oCVob* vob2		= RemoveFromSlot(slot2, TRUE, FALSE);
			PutInSlot (slot1,vob2,inInv2);
			PutInSlot (slot2,vob1,inInv1);
		}
		
		// Und Logik setzen
		this->SetWeaponMode( fm );
		ac -> SetFightAnis(fm);
		ac -> SetWalkMode (ac->GetWalkMode());

		// Und beim gehen jetzt entsprechende Ani des neuen Waffenmodus starten
		if (walking) model->StartAni(ac->_s_walkl);

		// Und Follow-Ani wieder entsprechend dem Waffenmodus setzen.
		if (cAni) {
			cAni->SetNextAni(model->GetAniFromAniID(ac->_s_walk));
		}

		// Stand-Ani korrigieren
		if (standing) model->StartAni(ac->_s_walk);

	} else if (fm == NPC_WEAPON_NONE) {
		// 1. Fall : WEAPON to NONE
		// *************************
		// Waffe deequippen
		// *************************

		// Waffe wegstecken im Rennen erm�glichen
		oCAniCtrl_Human* ac = GetAnictrl();
		zCModel* model		= GetModel();
		zBOOL walking		= FALSE;
		if (ac) walking		= ac->IsWalking() || model->IsAniActive(ac->_t_walkl_2_walk) || model->IsAniActive(ac->_t_walkr_2_walk);
		
		// Stand-Ani als Follow Ani ? muss beruecksichtigt werden, sonst gibt's Ani-Haenger
		zCModelAniActive* cAni	= NULL;
		if (model) {
			cAni			= model->GetActiveAni(ac->_t_walkl_2_walk);
			if (!cAni) cAni = model->GetActiveAni(ac->_t_walkr_2_walk);
		}

		zSTRING from;
		zSTRING to;  
		// Startslot
		switch (fmode) {
			case NPC_WEAPON_DAG : case NPC_WEAPON_1HS : from = NPC_NODE_SWORD;		break;
			case NPC_WEAPON_2HS :						from = NPC_NODE_LONGSWORD;	break;
			case NPC_WEAPON_CBOW:						from = NPC_NODE_CROSSBOW;	break;
			case NPC_WEAPON_BOW :	{
										from = NPC_NODE_BOW;		
										// BowMorphMesh zur Sicherheit zuruecksetzen
										oCVob *vob = zDYNAMIC_CAST<oCVob>(this->GetWeapon());
										if (vob)
										{
											zCMorphMesh* pMeshMorph = zDYNAMIC_CAST<zCMorphMesh>(vob->GetVisual());
											if ( pMeshMorph ) pMeshMorph->StartAni( "S_RELAX" );
										}
										break;
									}
		}

		// ZielSlot
		switch (fmode) {
			case NPC_WEAPON_DAG : case NPC_WEAPON_1HS : case NPC_WEAPON_2HS : case NPC_WEAPON_CBOW :
								  to = NPC_NODE_RIGHTHAND;		
								  break;
			case NPC_WEAPON_BOW : to = NPC_NODE_LEFTHAND;	
								  break;
			case NPC_WEAPON_MAG : {
										oCMag_Book* sb = GetSpellBook();
										if (walking) {
											// Am Laufen, dann Handsymbol weg...
											sb->Close(TRUE);
										} else if (!sb->IsOpen()) {
											sb->Close(TRUE);	
										} else {
											GetEM()->OnMessage(zNEW( oCMsgMagic(oCMsgMagic::EV_OPEN,fmode,TRUE) ),this);
											// CloseSpellBook(fmode,TRUE);
										}
								  }
								  break;
		}

		// Und graphischen Wechsel durchf�hren
		if (!from.IsEmpty() && !to.IsEmpty()) {
			// Slot Wechseln
			TNpcSlot* slot1	= GetInvSlot(from);
			TNpcSlot* slot2 = GetInvSlot(to);
			zBOOL inInv1	= slot1->inInventory;
			zBOOL inInv2	= slot2->inInventory;
			oCVob* vob1		= RemoveFromSlot(slot1, TRUE, FALSE);
			oCVob* vob2		= RemoveFromSlot(slot2, TRUE, FALSE);
			PutInSlot (slot1,vob2,inInv2);
			PutInSlot (slot2,vob1,inInv1);
		}

		// Und Logik setzen
		this->SetWeaponMode( fm );
		ac -> SetFightAnis(fm);
		ac -> SetWalkMode (ac->GetWalkMode());

		// Und beim gehen jetzt entsprechende Ani des neuen Waffenmodus starten
		if (walking) model->StartAni(ac->_s_walkl);

		// Und Follow-Ani wieder entsprechend dem Waffenmodus setzen.
		if (cAni) cAni->SetNextAni(model->GetAniFromAniID(ac->_s_walk));

		// Stand-Ani korrigieren
		if (ac->IsStanding()) model->StartAni(ac->_s_walk);
	}
}

void oCNpc :: SetWeaponMode( int fm )
{       
	fmode = fm;
	// Patch 1.08 : Safety....
	if ((fmode<0) || (fmode>=NPC_WEAPON_MAX)) fmode = NPC_WEAPON_NONE;

	// sicher ist sicher
	if (IsAPlayer())
	{
		if( GetWeaponMode() < NPC_WEAPON_BOW )
		{
			if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModMelee);
			oCNpcFocus::SetFocusMode(FOCUS_MELEE);
		}
		else if( GetWeaponMode() == NPC_WEAPON_MAG )
		{
			if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModMelee);
			oCNpcFocus::SetFocusMode(FOCUS_MAGIC);
		}
		else if( GetWeaponMode() >= NPC_WEAPON_BOW )
		{
			if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModNormal);
			oCNpcFocus::SetFocusMode(FOCUS_RANGED);
		}
	}
}

int oCNpc :: GetNextWeaponMode ( int from, int dir, zBOOL ignoreFistCondition )
{
  	oCItem* wnear	= GetEquippedMeleeWeapon();
	oCItem* wfar	= GetEquippedRangedWeapon();

	int check = from;
	do {
		check+=dir;
		if (check>NPC_WEAPON_MAG)	check = NPC_WEAPON_FIST;
		if (check<=NPC_WEAPON_NONE)	check = NPC_WEAPON_MAG;

		switch (check) {

			case NPC_WEAPON_FIST	:	if (ignoreFistCondition) {
											return (check);
										} else if (!wnear) {
											return(check);
										}; break;
			case NPC_WEAPON_DAG		:	if (wnear && wnear->HasFlag(ITM_FLAG_DAG)) {
											return(check);
										}; break;
			case NPC_WEAPON_1HS		:	if (wnear) {
											if (wnear->HasFlag(ITM_FLAG_AXE) || wnear->HasFlag(ITM_FLAG_SWD)) {
												return(check);
											}
										}; break;
			case NPC_WEAPON_2HS		:	if (wnear && (wnear->HasFlag(ITM_FLAG_2HD_SWD) || wnear->HasFlag(ITM_FLAG_2HD_AXE))) {
											return(check);
										}; break;
			case NPC_WEAPON_BOW		:	if ((wfar && wfar->HasFlag(ITM_FLAG_BOW)) && (IsMunitionAvailable(wfar))) {
											return(check);
										}; break;
			case NPC_WEAPON_CBOW	:	if ((wfar && wfar->HasFlag(ITM_FLAG_CROSSBOW)) && (IsMunitionAvailable(wfar))) {
											return(check);
										}; break;
			case NPC_WEAPON_MAG		:	if (GetNumberOfSpells()>0) return check;
										break;
			default					:	//check+=dir:
										//zerr.Message("U: (oNPC:GetNextWeaponMode) No valid Weaponmode found.");
										//return (-1);
										break;
		}
	} while (TRUE);
	
	return -1;
}

void oCNpc :: Equip ( oCItem* item )
{
	if (item)
	{	
		int cat = inventory2.GetCategory(item);
		
		if (cat == INV_COMBAT)
		{
			if (item->HasFlag(ITM_CAT_NF))
				EquipWeapon(item);
			else if (item->HasFlag(ITM_CAT_FF))
				EquipFarWeapon(item);
		}
		else if (cat == INV_ARMOR)
		{			
			EquipArmor(item); 
		}
		else if (cat == INV_RUNE && item->HasFlag(ITM_FLAG_ACTIVE))
		{
			if (GetSpellBook())
				GetSpellBook()->DeRegister(item);
			item->ClearFlag(ITM_FLAG_ACTIVE);
		}
		else if (cat == INV_RUNE && !item->HasFlag(ITM_FLAG_ACTIVE))
		{
			if (GetSpellBook())
			{
				if (GetSpellBook()->GetNoOfSpells() > 6)
					return;
				GetSpellBook()->Register(item);
			}
			item->SetFlag(ITM_FLAG_ACTIVE);
		}
		else if (cat == INV_MAGIC && item->HasFlag(ITM_FLAG_ACTIVE))
		{ 
			RemoveItemEffects(item);
			item->ClearFlag(ITM_FLAG_ACTIVE);
		}
		else if (cat == INV_MAGIC && !item->HasFlag(ITM_FLAG_ACTIVE))
		{
			if (item->HasFlag(ITM_FLAG_AMULET))
			{
				// Nur 1 Amulett equippen.
				oCItem* amulet = NULL;
				inventory2.UnpackCategory();
				int numItems = inventory2.GetNumItemsInCategory();
				for (int i = 0; i < numItems; i++)
				{					
					amulet = inventory2.GetItem(i);
					if (amulet && amulet->HasFlag(ITM_FLAG_AMULET) && amulet->HasFlag(ITM_FLAG_ACTIVE))
						return;
				}
			}
			if (item->HasFlag(ITM_FLAG_RING))
			{
				// Nur 2 Ringe gleichzeitig equippen.
				oCItem* ring = NULL;
				inventory2.UnpackCategory();
				int numItems = inventory2.GetNumItemsInCategory();
				int usedRings = 0;
				for (int i = 0; i < numItems; i++)
				{
					ring = inventory2.GetItem(i);
					if (ring && ring->HasFlag(ITM_FLAG_RING) && ring->HasFlag(ITM_FLAG_ACTIVE))
					{
						usedRings++;
						if (usedRings >= 2)
							return;
					}
				}
			}			
			if(item->HasFlag(ITM_FLAG_BELT))
			{
				// Nur 1en Guertel equippen.
				oCItem* belt = NULL;
				inventory2.UnpackCategory();
				int numItems = inventory2.GetNumItemsInCategory();
				for (int i = 0; i < numItems; i++)
				{					
					belt = inventory2.GetItem(i);
					if (belt && belt->HasFlag(ITM_FLAG_BELT) && belt->HasFlag(ITM_FLAG_ACTIVE))
						return;
				}
			}
			AddItemEffects(item);
			item->SetFlag(ITM_FLAG_ACTIVE);
		}
		else
		{
			UseItem(item);
		}
	}
}


/* ----------------------------------------------------------------------
	
    oCNpc :: EquipWeapon()	

	13.11.2000	[Moos]	
                M�ll (?) beim unequippen beseitigt 


   ---------------------------------------------------------------------- */


void oCNpc :: EquipWeapon ( oCItem *item )
{
	// Equippen nur moeglich, wenn nicht im Kampfmodus
//	if (fmode!=NPC_WEAPON_NONE) return;

//	int slot = -1;
	// Bereits equipped ?
	if (item->HasFlag(ITM_FLAG_ACTIVE))
	{
        UnequipItem(item);
		return;
	}

	// Voraussetzungen erf�llt ?
    if (!CanUse(item) && this==player){
        DisplayCannotUse();
        return;
    }


	if ((item->HasFlag(ITM_FLAG_2HD_SWD)) || (item->HasFlag(ITM_FLAG_2HD_AXE))) {
		// Zweih�nder, beide Slots leeren
		UnequipItem( GetSlotItem(NPC_NODE_SWORD) );
		UnequipItem( GetSlotItem(NPC_NODE_LONGSWORD) );
		UnequipItem( GetSlotItem(NPC_NODE_SHIELD) );
//		slot = NPC_NODE_LONGSWORD;

	} else if ((item->HasFlag(ITM_CAT_NF)) && (!item->HasFlag(ITM_FLAG_SHIELD))) {
		// Einh�nder, nur Waffenslot r�umen
		UnequipItem( GetSlotItem(NPC_NODE_SWORD) );
		UnequipItem( GetSlotItem(NPC_NODE_LONGSWORD) );		
//		slot = NPC_NODE_SWORD;
	
	} else if (item->HasFlag(ITM_FLAG_SHIELD)) {
		// Schild slot r�umen
		UnequipItem( GetSlotItem(NPC_NODE_SHIELD) );
//		slot = NPC_NODE_SHIELD;
	}
	// Und in Slot reinpacken
	EquipItem	( item );
}

void oCNpc :: EquipFarWeapon ( oCItem *item )
{
	// Equippen nur moeglich, wenn nicht im Kampfmodus
	if (!item) return;
	if (!item->HasFlag(ITM_CAT_FF)) return;

	zBOOL equipped = item -> HasFlag(ITM_FLAG_ACTIVE);
//  if (!equipped) && (fmode!=NPC_WEAPON_NONE)) return;

	// Altes Slot r�umen
	UnequipItem ( GetSlotItem(NPC_NODE_BOW) );
	UnequipItem ( GetSlotItem(NPC_NODE_CROSSBOW) );

	// Nur equippen, wenn noch nicht equipped
	if (!equipped) {

    	if (!CanUse(item) && this==player){
            DisplayCannotUse();
            return;
        }

		EquipItem ( item );
	}
}

void oCNpc :: EquipArmor ( oCItem *item )
{
	// R�stbar ?
	if (!item->HasFlag(ITM_CAT_ARMOR)) return;

	
	// **********************************
	// UnEquip
	// **********************************

	if (item->HasFlag(ITM_FLAG_ACTIVE)) {
		UnequipItem(item);
		return;
	}

	// **********************************
	// Equip
	// **********************************
   	if (!CanUse(item) && this==player){
        DisplayCannotUse();
        return;
    }

	// Slot ermitteln
	zSTRING slot;
	/*
	switch (item->wear) {
		case ITM_WEAR_HEAD		:	slot = NPC_NODE_HELMET;	
									break;
		case ITM_WEAR_TORSO		:   slot = NPC_NODE_TORSO;
									break;
		default					:	zERR_FAULT("U: NPC: (WearItem) Ungueltiger 'wear'-Wert von " + item->GetName());	
	}*/

	if (item->wear & ITM_WEAR_HEAD) slot = NPC_NODE_HELMET;	 else
	if (item->wear & ITM_WEAR_TORSO)slot = NPC_NODE_TORSO;	 else
		zERR_FAULT("U: NPC: (WearItem) Ungueltiger 'wear'-Wert von " + item->GetName());	


	if (!slot.IsEmpty()) {
		// Altes Item im Slot unequippen
		UnequipItem	(GetSlotItem(slot));
		EquipItem	(item);
	}
}

void oCNpc :: SetToFightMode ( oCItem *item, zBOOL startStandAni )
// Schalte NSC ohne Anims in den Kampfmodus
{
	int cat = inventory2.GetCategory ( item );
//	if (cat==NPC_INV_CLOSECOMBAT) {
	if ((cat==INV_COMBAT) && item->HasFlag(ITM_CAT_NF)) {
	
		//
		// [BENDLIN] Addon - SplitSlot FIXME
		//
		// UnequipItem(w) statt Equip(w)
		//
		// Alte Waffe vorhanden ? -> dann de-equippen
		oCItem *w = GetWeapon();
		if (w) // Equip(w);
			UnequipItem(w);
		
		// Waffe regeltechnisch in den rechten Handslot packen
		EquipWeapon		( item );
		// [Ulf] - 18.01.01 - AddItemEffects macht EquipWeapon bereits....
		//		AddItemEffects	( item );
		//
		// [BENDLIN] Addon - SplitSlot FIXME
		//
		// passiert bereits in EquipWaepon
		//
//		item -> SetFlag ( ITM_FLAG_ACTIVE );
		SetWeaponMode	( NPC_WEAPON_FIST );
		SetWeaponMode	( GetNextWeaponMode( GetWeaponMode(), +1 ) );
				
		// Animationen des Kampfmodus initialisieren
		oCAniCtrl_Human *ac = GetAnictrl();
		if (ac) {
			// CameraModis initialisieren
			human_ai -> InitCamModes ( );

			ac -> SetFightAnis	( GetWeaponMode() );
			ac -> SetWalkMode	( ANI_WALKMODE_RUN );
			
			// Wird ben�tigt -> CheckActiveSpells
			ac -> wmode_selected = GetWeaponMode();

			if (startStandAni && GetVisual()) GetModel() -> StartAni ( ac->_s_walk );
		}
	}
}

void oCNpc :: SetToFistMode ( )
// Schalte NSC ohne Anims in den Kampfmodus
{
	SetWeaponMode	( NPC_WEAPON_FIST );
	// evt. Waffe graphisch aus den Handslot loeschen
	oCAniCtrl_Human *ac = GetAnictrl();

    if (GetVisual())
    {
    	zCModel *model = GetModel();
    	zCModelNodeInst *node = model -> SearchNode("ZS_RIGHTHAND");
    	if (node) model -> SetNodeVisual(node,NULL);

        if (ac)
    		model -> StartAni	( ac->_s_walk );
    }

	// Animationen des Kampfmodus initialisieren
	if (ac) {
		ac -> SetFightAnis	( GetWeaponMode() );
		ac -> SetWalkMode	( ANI_WALKMODE_RUN );
		// Wird ben�tigt -> CheckActiveSpells
		ac -> wmode_selected = NPC_WEAPON_FIST;
		// CameraModis initialisieren
		human_ai -> InitCamModes	( );
	}
}

void oCNpc :: Activate ( int cat, int nr )
{
	// Item ermitteln
	//oCItem *item = inventory[cat].Get(nr);
	//if (item==NULL) return;
	//DoActivate(item);
}

oCVob* oCNpc :: GetRightHand ( )
// Liefere aktuelles handnitem
{
	return GetSlotVob(NPC_NODE_RIGHTHAND);
}

oCVob* oCNpc :: GetLeftHand ( )
// Liefere aktuelles handnitem
{
	return GetSlotVob(NPC_NODE_LEFTHAND);
}

void oCNpc :: DropVob(oCVob* vob, zVEC3 &pos)
{
	// Position ermitteln
	if (!vob -> RegisteredInWorld()) ogame->GetGameWorld()->EnableVob(vob);
	if (!vob -> SearchFreePosition(pos,this)) {
		zERR_MESSAGE(3,0,"U: NPC: DropItem:Not enough space.");
	};
	vob	-> SetPositionWorld(pos);
	if (!vob->RegisteredInWorld()) ogame->GetGameWorld()->EnableVob(vob);
}

void oCNpc :: SetCarryVob ( zCVob *m )
{
	// Overlay aus !
	zSTRING suffix;
	oCMOB* mob		= zDYNAMIC_CAST<oCMOB>(m);
	if (mob) suffix = mob->GetScemeName();

	// Altes CarryVob-Overlay entfernen
	if (GetCarryVob()) {
		// Overlay aus !
		oCMOB* oldMob = zDYNAMIC_CAST<oCMOB>(GetCarryVob());
		if (oldMob) {
			zSTRING suffix = oldMob->GetScemeName();
			RemoveOverlay("HUMANS_CARRY"+suffix+".MDS");
		}
		RemoveFromSlot(NPC_NODE_RIGHTHAND,FALSE);		
	}

	if (m) {
		// AI dranh�ngen
		oCAIVobMove* vobai = zNEW( oCAIVobMove() );
		vobai->Init(m,this,m->GetPositionWorld());
		
		PutInSlot(NPC_NODE_RIGHTHAND,(oCVob*)m,FALSE);
		
		ApplyOverlay("HUMANS_CARRY"+suffix+".MDS");
    
        zRELEASE(vobai);	//  [Moos] Leakfix	
	}

	carry_vob = m;
}

zCVob* oCNpc :: GetCarryVob ()
{
	return carry_vob;
}

void oCNpc :: SetLeftHand ( oCVob *vob )
{
	if (!vob) return;
	zBOOL inInv = ((vob->GetVobType()==zVOB_TYPE_ITEM) && (IsInInv((oCItem*)vob)));
	PutInSlot(NPC_NODE_LEFTHAND,vob,inInv);

		
/*	
	oCItem *item;

	if (invslot[NPC_SLOT_HANDL]) 
		invslot[NPC_SLOT_HANDL]->SetIgnoredByTraceRay(FALSE);

	if (vob) {
		vob -> SetIgnoredByTraceRay	(TRUE);
		vob -> SetPhysicsEnabled	(FALSE);
		vob -> RigidBody() -> SetGravityEnabled (FALSE);
		if (!vob->RegisteredInWorld()) {
			// Kollision aus
			switch (vob->GetVobType()) {
  				case zVOB_TYPE_ITEM	:	item =  (oCItem *)vob;
										item -> PutIn3D(GetPositionWorld());	
										//worldhandler.DoVob_Insert(item,GetPositionWorld());
										break;
				case zVOB_TYPE_NSC	:	((oCNpc  *)vob)->PutIn3D(GetPositionWorld());	
										//worldhandler.DoVob_Insert((oCNpc*)vob,GetPositionWorld());
										break;
			}
			vob -> SetCollDet	(FALSE);
		} 
		if (vob->GetVobType()==zVOB_TYPE_ITEM) {
			item =  (oCItem *)vob;
			item -> SetFlag(ITM_FLAG_NFOCUS);
		}
	}
	invslot[NPC_SLOT_HANDL] = vob;*/
}

void oCNpc :: SetRightHand ( oCVob *vob )
//oCItem *item )
{
	if (!vob) return;
	zBOOL inInv = ((vob->GetVobType()==zVOB_TYPE_ITEM) && (IsInInv((oCItem*)vob)));
	PutInSlot(NPC_NODE_RIGHTHAND,vob,inInv);

/*	oCItem *item;

	if (invslot[NPC_SLOT_HANDR]) 
		invslot[NPC_SLOT_HANDR]->SetIgnoredByTraceRay(FALSE);

	if (vob) {
		vob -> SetIgnoredByTraceRay	(TRUE);
		vob -> SetPhysicsEnabled	(FALSE);
		vob -> RigidBody() -> SetGravityEnabled (FALSE);
		if (!vob->RegisteredInWorld()) {
			// Kollision aus
			switch (vob->GetVobType()) {
				case zVOB_TYPE_ITEM	:	// FIXME : Solange der Worldhandler das nicht macht
										((oCItem*) vob) -> PutIn3D(GetPositionWorld());	
										break;
				case zVOB_TYPE_NSC	:	// FIXME : Solange der Worldhandler das nicht macht
										((oCNpc *) vob) -> PutIn3D(GetPositionWorld());	
										//worldhandler.DoVob_Insert((oCNpc*)vob,GetPositionWorld());
										break;
			}
			vob -> SetCollDet	(FALSE);
		} 
		if (vob->GetVobType()==zVOB_TYPE_ITEM) {
			item =  (oCItem *)vob;
			item -> SetFlag(ITM_FLAG_NFOCUS);
		}
	}
	invslot[NPC_SLOT_HANDR] = vob;*/
}

zBOOL oCNpc :: HasTorch()
{
	oCItem *item1 = GetSlotItem(NPC_NODE_LEFTHAND);
	oCItem *item2 = GetSlotItem(NPC_NODE_RIGHTHAND);
	if( item1 ) return item1->HasFlag(ITM_FLAG_TORCH);
	if( item2 ) return item2->HasFlag(ITM_FLAG_TORCH);
	return FALSE;
}

void oCNpc :: ExchangeTorch()
// Fackel tauschen, wenn diese aktiv und rechte Hand frei
{
//	if ((HasTorch()) && (GetRightHand()==NULL)) 
//		GetAICommand() -> AI_ExchangeTorch();
}

void oCNpc :: SetTorchAni(zBOOL f, zBOOL now)
// Spezielle TorchAni anzeigen
{
/*	oCAniCtrl_Human *ac = GetAnictrl();
	if ((HasTorch()) && (f)) {
		GetModel()->StartAni(ac->_s_torch);
		GetModel()->SetRandAnisEnabled(FALSE);
	} else {
		GetModel()->StopAni (ac->_s_torch);
		GetModel()->SetRandAnisEnabled(TRUE);
	}*/
   TActiveInfo *activeInfo = GetActiveInfoWritablePrivate();

    if (now)
    {
        activeInfo->changeTorchAni   = FALSE;
        activeInfo->changeTorchAniTo = f;

	    if( GetTrueGuild() >= NPC_GIL_ORCS )
	    {
		    if( f ) ApplyOverlay("ORC_TORCH.MDS");
		    else    RemoveOverlay("ORC_TORCH.MDS");
	    }
	    if( GetTrueGuild() <= NPC_GIL_HUMANS )
	    {
		    if( f ) ApplyOverlay("HUMANS_TORCH.MDS");
		    else    RemoveOverlay("HUMANS_TORCH.MDS");
	    }
    }
    else
    {
//        if (activeInfo->changeTorchAniTo != f)
//       {
            activeInfo->changeTorchAni   = TRUE;
            activeInfo->changeTorchAniTo = f;
    
            CheckSetTorchAni();
//        }
    }
}

/* ----------------------------------------------------------------------
	
    oCNpc::CheckSetTorchAni()

    Setzt eine vorher mit SetTorchAni(f, FALSE) vorgemerkte Fackelanimation,
    wenn es der aktuelle Zustand erlaubt.

	 18.1.2001	[Moos]	
                erzeugt


   ---------------------------------------------------------------------- */

void oCNpc::CheckSetTorchAni(){
    TActiveInfo *activeInfo = GetActiveInfoWritablePrivate();

    if (!GetVisual() || !GetAnictrl())
        return;

    zCModel *model = GetModel();

    if (activeInfo->changeTorchAni &&
       (model->IsStateActive(GetAnictrl()->_s_walk) || model->IsStateActive(GetAnictrl()->s_run[GetWeaponMode()])) &&
       !model->IsAniActive("T_FOODHUGE_STAND_2_S0"))
    {
        SetTorchAni(activeInfo->changeTorchAniTo);
    }
}




/* ----------------------------------------------------------------------
	
    oCNpc::CheckPutbackTorch()

    wenn das putBackTorchInHand-Flag gesetzt ist, wird eine Fackel
    aus der rechten Hand oder dem Inventory genommen, angez�ndet und
    in die Linke genommen.

	 18.1.2001	[Moos]	
                erzeugt


   ---------------------------------------------------------------------- */


static zBOOL s_isInPutInSlot = FALSE;


void oCNpc::CheckPutbackTorch (){
    if (s_isInPutInSlot)
        return;

    s_isInPutInSlot = TRUE;

    TNpcSlot *slotLeft = GetInvSlot(NPC_NODE_LEFTHAND);
	// Patch 1.08 : Auf Nullpointerzugriffe pruefen
	zCVob*			vob	= NULL;
	if (slotLeft)	vob	= slotLeft->Vob();

    if (!vob && s_activeInfoCache.GetDataDangerous(this) && GetActiveInfo()->putTorchBackInHand){     // Linke Hand ist frei und wir sollen eine Fackel reintun. Probieren wir mal...
        GetActiveInfoWritablePrivate()->putTorchBackInHand = FALSE;

        // schaue in der rechten Hand nach
        TNpcSlot *slotRight		= GetInvSlot(NPC_NODE_RIGHTHAND);
        // Patch 1.08 : Auf Nullpointer pruefen
		oCItem *torch			= NULL;
		if (slotRight) torch	= zDYNAMIC_CAST<oCItem>(slotRight->Vob()); 

        if (!torch || !(torch->GetObjectName() == S_ITLSTORCHBURNING))
        { // was auch immer in der rechten Hand ist, ist keine Fackel. Schaue im Inventar nach.
            torch = IsInInv("ITLSTORCH");
        }

        if (torch)
            UseItem(torch);     // verwende sie!
    }

    s_isInPutInSlot = FALSE;
    
    // Sicherheit : Wenn keine Fackel in der Hand, dann weg mit der Ani
    // Patch 1.08 : Auf Nullpointer pruefen.
	oCItem *newTorch = NULL;
	if (slotLeft) newTorch = zDYNAMIC_CAST<oCItem>(slotLeft->Vob());
    SetTorchAni(newTorch && newTorch->GetObjectName() == S_ITLSTORCHBURNING, FALSE);
//    return;
}



zBOOL oCNpc :: UseItem ( oCItem *item )
// Wear this item
{
	zBOOL available = TRUE;

	if (!CanUse(item) && this==player) {
        DisplayCannotUse();
		return FALSE;
	}	

	if (item->HasFlag(ITM_CAT_FOOD)) {
		// *********************************
		// Verzehrbar
		// *********************************
		// !!! TO DO !!! Chrunch Sound.
		// m�gl �nderungen der Attribute 
		ChangeAttribute(NPC_ATR_HITPOINTS,item->nutrition);

		AddItemEffects(item);

		if (item->GetAmount()>1) {
			item->ChangeAmount(-1);
			available = TRUE;
		} else {
			available = FALSE;
		}
	} else if (item->HasFlag(ITM_CAT_DOCS)) {
		// ****************************
		// a) Lesbar -> lesen !
		// ****************************
		available = TRUE;

//changed[dennis]
	} else if (item->HasFlag(ITM_FLAG_TORCH) && (item->GetName() != S_ITLSTORCHBURNING)) {
		// **************************************
		// a) Fackel anz�nden und in Player-Hand
		// **************************************
		// Nur, wenn keine Fackel bereits an
		if (!HasTorch()) {
			item	= RemoveFromInv (item);

			// [EDENFELD] 1.25: Brennende Fackeln nicht mit ins Archiv schreiben
			oCItem* torch = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCHBURNING");
			torch->SetDontWriteIntoArchive(TRUE);

			zCTree<zCVob> *child = torch->globalVobTreeNode->GetFirstChild(); 
			while (child) 
			{
				zCVob *vob = zDYNAMIC_CAST<zCVob>(child->GetData());

				if (vob) vob->SetDontWriteIntoArchive(TRUE);
				child = child->GetNextChild();
			};

			
//changed[dennis]
//			if (torch) SetRightHand(torch);
			if (torch)
			{
				SetLeftHand(torch);
				//this->anictrl->model->StartAni("t_torch");
				SetTorchAni( TRUE );
			}

		
			// Und AI aktivieren
			oCAIVobMove* ai = torch -> GetAIVobMove();
			if (ai) ai->Init(torch,this,torch->GetPositionWorld());
		    torch->ReleaseVobSubtree();	//  CODECHANGE Moos: get rid of that thing properly later
            //zRELEASE(torch);              // ok. the line above causes crashes. FIXME later.
		}
		else
		{
            // l�sche eine Fackel in der linken hand
            TNpcSlot *slotLeft = GetInvSlot(NPC_NODE_LEFTHAND);
            oCItem *torch = zDYNAMIC_CAST<oCItem>(slotLeft->Vob()); 

            if (torch && torch->GetObjectName() == S_ITLSTORCHBURNING)
            {
                PutInInv(zDYNAMIC_CAST<oCItem> (RemoveFromSlot(NPC_NODE_LEFTHAND, FALSE)));
                SetTorchAni(FALSE, FALSE);
            }
            else  // Fackel in der rechten Hand?
            {
                TNpcSlot *slot = GetInvSlot(NPC_NODE_RIGHTHAND);
                zCVob *vob = slot->Vob();

                if (vob)                     // [Moos] Crashfix
                {
                    vob->AddRefVobSubtree();	//  [Moos] Sonst werden Teile der Fackel gel�scht

    			    SetLeftHand(RemoveFromSlot(NPC_NODE_RIGHTHAND,FALSE));
    			    SetTorchAni( TRUE );

                    vob->ReleaseVobSubtree();
                }
	        }
    	}
		available = TRUE;
	} 

	// Item entfernen
	if (!available) {
		// Aus Slots entfernen
		// FIXME : Sonderfall -> wird durch AI-befehl entfernt
		if (item->HasFlag(ITM_FLAG_DRINK)) return TRUE;
		
		if (GetRightHand()==item)	item = (oCItem*)RemoveFromSlot(NPC_NODE_RIGHTHAND);	else
		if (GetLeftHand ()==item)	item = (oCItem*)RemoveFromSlot(NPC_NODE_LEFTHAND);	else
		if (IsInInv(item))			item = RemoveFromInv(item);
		if (item) {
			// if (item->GetHomeWorld()) item->GetHomeWorld()->RemoveVob(item);
			// zRELEASE(item);
            // Codechange [Wohlers] - GetHomeWorld() kann beim Laden Null sein ! 
			// und beim laden von Models ist er hier reingekommen (-> Levelchange OrcTempel)
			if (ogame && ogame->GetWorld()) {
				ogame->GetWorld()->RemoveVob(item);	//  CODECHANGE Moos (FIXME: ist das korrekt so?)
				// FIXME: fehlt hier nicht noch ein zRELEASE(item)? evtl. memleak beim essen/trinken (auch npc's-> checken)
			}
		}
	
	} else {
		
	}


	return TRUE;
};

// ********************************************************************
// Werfen
// ********************************************************************

// Bahngleichung des schraegen Wurfes
// y = x * tan(a) - (g/(2v^2 * cos^2(a)) * x^2
//
// wobei
// x = Entfernung 
// y = Hohenunterschied StartPos / EndPos
// g = Fallbeschleunigung (981 cm/s^2)
// a = Winkel der Abwurfrichtung zur Waagerechten
// v = Abwurfgeschwindigkeit in horizontaler Richtung
//
// Gesucht : v
// Nach Umstellung :
// 
// -------------------- Verworfen ---------------------
// Neue Formel :
//		v = sqrt( g * x / sin(2*ar) );
// 
//	x  = Entfernung			(cm)
//	ar = Wurfwinkel			
//	g  = 981.0f;// Gravity	(cm/sec^2)

zREAL oCNpc :: GetThrowSpeed(const zREAL dist, const zREAL angle)
{
	return sqrt( 981.0f * dist / zSin(2 * Alg_Deg2Rad(angle)) ) * 0.9f;
}

// ********************************************************************
// Starte Bogen - Pfeil
// ********************************************************************

zBOOL oCNpc :: HasArrowInHand()
{
	oCItem* bolt = GetSlotItem(NPC_NODE_RIGHTHAND);
	if ((bolt) && (bolt->GetInstanceName()=="ARROW")) return TRUE;
	return FALSE;
}

zBOOL oCNpc :: HasArrowInInv()
{
	// Pfeil noch im Inventory vorhanden ?
	return (IsInInv("ARROW")!=NULL);
}

zBOOL oCNpc :: HasBoltInInv()
{
	// Pfeil noch im Inventory vorhanden ?
	return (IsInInv("BOLT")!=NULL);
}

zBOOL oCNpc :: HasBoltInHand()
{
	oCItem* bolt = GetSlotItem(NPC_NODE_LEFTHAND);
	if ((bolt) && (bolt->GetInstanceName()=="BOLT")) return TRUE;
	return FALSE;
}

zBOOL oCNpc :: IsMunitionAvailable(oCItem* weapon)
{
	if (!weapon) return FALSE;
	
	// **************
	// Magische Waffe
	// **************	
	if (weapon->HasFlag(ITM_FLAG_CREATEAMMO)) return TRUE;

	// **********************
	// Muni noch inner Hand ?
	// **********************
	if (HasInHand(weapon->GetMunitionInstance())) return TRUE;

	// *************
	// Normale Waffe
	// *************

	// [EDENFELD] 1.09 wenn muni alle, dann skript aufrufen
	zBOOL bAmmoAvail = IsInInv(weapon->GetMunitionInstance())!=NULL;
	if (!bAmmoAvail && (this==oCNpc::player) )
	{
		GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, PLAYER_RANGED_NO_AMMO,-1),this);
	}

	return (bAmmoAvail);	
/*
	if (GetWeaponMode()==NPC_WEAPON_BOW) {
		return (HasArrowInHand() || HasArrowInInv());
	} else if (GetWeaponMode()==NPC_WEAPON_CBOW) {
		return (HasBoltInHand() || HasBoltInInv());
	} else
		return TRUE;
		*/
}

// ****************************************
// Spells
// ****************************************

void oCNpc :: GetTalentInfo(int nr, zSTRING& name, zSTRING& desc, zSTRING& skills)
{
	name.Clear();
	desc.Clear();
	skills.Clear();
	zCPar_Symbol* sym = NULL;
	sym = parser.GetSymbol("TXT_TALENTS");
	if (sym) sym->GetValue(name,nr);
	sym = parser.GetSymbol("TXT_TALENTS_DESC");
	if (sym) sym->GetValue(desc,nr);	
	sym = parser.GetSymbol("TXT_TALENTS_SKILLS");
	if (sym) sym->GetValue(skills,nr);	
}

void oCNpc :: GetSpellInfo(int nr,zSTRING& name, zSTRING& desc)
{
	name.Clear();
	desc.Clear();
	zCPar_Symbol* sym = NULL;
	sym = parser.GetSymbol("TXT_SPELLS");
	if (sym) sym->GetValue(name,nr);
	sym = parser.GetSymbol("TXT_SPELLS_DESC");
	if (sym) sym->GetValue(desc,nr);	
}

void oCNpc :: GetAttribInfo(int nr, zSTRING& name, zSTRING& desc)
{
	name.Clear();
	desc.Clear();
	zCPar_Symbol* sym = NULL;
//	sym = parser.GetSymbol("TXT_SPELLS");
//	if (sym) sym->GetValue(name,nr);
	sym = parser.GetSymbol("TXT_ATTRIBUTE_DESC");
	if (sym) sym->GetValue(desc,nr);	
}

void oCNpc :: CreateSpell (int nr)
{
	// Magie oder Psi-Spruch ?
	if (!mag_book) mag_book = zNEW( oCMag_Book() );
	// In Buch eintragen
/*	if (!mag_book->IsIn(nr)) {
		mag_book -> SetOwner(this);
		mag_book -> Register(nr);
	}*/
}

void oCNpc :: LearnSpell (int nr)
{
	// Gibt's den schon ?
	if (HasSpell(nr)) return;
	// Pacj in Zauberkranz
	CreateSpell(nr);
	// Spell lernen
	spells |= (1 << nr);	
}

zBOOL oCNpc :: HasSpell (int nr)
{
	return ( (spells & (1 << nr) )>0 );
}

void oCNpc :: DestroySpell (int nr)
{
	if (HasSpell(nr)) spells -= (1 << nr );
}

void oCNpc :: SetActiveSpellInfo(int value)
{
	if (GetWeaponMode()==NPC_WEAPON_MAG) {
		oCMag_Book* book = GetSpellBook();
		if (book) {
			oCSpell* spell = book -> GetSelectedSpell();
			if (spell) spell -> SetSpellInfo(value);
		};
	};
}

int oCNpc :: GetActiveSpellNr()
{
	if (GetWeaponMode()==NPC_WEAPON_MAG) {
		oCMag_Book* book = GetSpellBook();
		if (book) {
			oCSpell* spell = book -> GetSelectedSpell();
			if (spell) return spell -> GetSpellID();
		};
	};
	return -1;
}

int oCNpc :: GetActiveSpellCategory()
{
	if (GetWeaponMode()==NPC_WEAPON_MAG) {
		oCMag_Book* book = GetSpellBook();
		if (book) {
			oCSpell* spell = book -> GetSelectedSpell();
			if (spell) return spell -> GetCategory();
		};
	};
	return -1;
}

int oCNpc :: GetActiveSpellLevel()
{
	if (GetWeaponMode()==NPC_WEAPON_MAG) {
		oCMag_Book* book = GetSpellBook();
		if (book) {
			oCSpell* spell = book -> GetSelectedSpell();
			if (spell) return spell -> GetLevel();
		};
	};
	return -1;
}

int oCNpc :: GetActiveSpellIsScroll()
{
	if (GetWeaponMode()==NPC_WEAPON_MAG) {
		oCMag_Book* book = GetSpellBook();
		if (book) {
			oCItem* item = book->GetSpellItem(book -> GetSelectedSpellNr());
			if (item) return item->MultiSlot();
		};
	};
	return 0;
}



// NEW
//[EDENFELD] AddRefs auf die spells durchgef�hrt
void oCNpc :: InsertActiveSpell(oCSpell* spell)
{
	if (!spell) return;
	spell->AddRef();
	activeSpells.Insert(spell);
}

void oCNpc :: RemoveActiveSpell(oCSpell* spell)
{
	if (!spell) return;
	activeSpells.Remove(spell);
	zRELEASE(spell);
}

void oCNpc :: RemoveActiveSpell(int nr)
{
	oCSpell* spell				= NULL;
	zCList<oCSpell>* spellNode	= activeSpells.GetNextInList();
	while (spellNode) {
		spell		= spellNode->GetData();
		spellNode	= spellNode->GetNextInList();
		if (spell->GetSpellID() == nr) {
			activeSpells.Remove(spell);
			zRELEASE(spell);
		}
	}
}

zBOOL oCNpc :: DoActiveSpells()
{
	// Effekte durchgehen
	zBOOL		deleteCaster	= FALSE;
	oCSpell*	spell			= NULL;
	zCList<oCSpell>* spellNode	= activeSpells.GetNextInList();
	while (spellNode) {
		spell		= spellNode->GetData();
		spellNode	= spellNode->GetNextInList();
		spell -> DoTimedEffect();
		if (spell -> CanBeDeleted()) {
			if (spell -> DeleteCaster()) deleteCaster = TRUE;
			activeSpells.Remove(spell);
			zRELEASE(spell);
			if (deleteCaster) return TRUE;
		}
	}
	return FALSE;
}

void oCNpc :: KillActiveSpells()
{
	// Effekte durchgehen
	oCSpell*	spell			= NULL;
	zCList<oCSpell>* spellNode	= activeSpells.GetNextInList();
	while (spellNode) 
	{
		spell		= spellNode->GetData();
		spellNode	= spellNode->GetNextInList();
		activeSpells.Remove(spell);
		zRELEASE(spell);
	}
}


oCSpell* oCNpc :: IsSpellActive(int nr)
{
	// Effekte durchgehen
	oCSpell* spell				= NULL;
	zCList<oCSpell>* spellNode	= activeSpells.GetNextInList();
	while (spellNode) {
		spell		= spellNode->GetData();
		spellNode	= spellNode->GetNextInList();
		if (spell->GetSpellID()==nr) return spell;
	}
	return FALSE;
}

zBOOL oCNpc :: HasMagic ()
{
	return (GetNumberOfSpells()>0);
}

int  oCNpc :: GetNumberOfSpells ()
// Ermittelt Anzahl der Alchemie Spr�che
{
	//changed[dennis]
	if( mag_book ) return mag_book->GetNoOfSpells();
	else return 0;
}

void oCNpc :: CopyTransformSpellInvariantValuesTo( oCNpc* pNpcOther )
{
	if ( ! pNpcOther ) return;

	pNpcOther->level						= this->level						;
	pNpcOther->learn_points					= this->learn_points				;
	pNpcOther->experience_points			= this->experience_points			;
	pNpcOther->experience_points_next_level = this->experience_points_next_level;

	zREAL hpScale   = zREAL(GetAttribute(NPC_ATR_HITPOINTS))/zREAL(GetAttribute(NPC_ATR_HITPOINTSMAX));

	pNpcOther->SetAttribute( NPC_ATR_MANA,		 pNpcOther->GetAttribute(NPC_ATR_MANA)					   );
	pNpcOther->SetAttribute( NPC_ATR_HITPOINTS,  hpScale   * pNpcOther->GetAttribute(NPC_ATR_HITPOINTSMAX) );

	pNpcOther->GetModel()->SetTimeScale( this->GetModel()->GetTimeScale() );
}

void oCNpc :: OpenScreen_Help()
{
/*
	oCHelpScreen* menu = zNEW( oCHelpScreen() );

	zCArray<oSMenuKey>	keys;
	oSMenuKey* key = NULL;
	
	key	= zNEW( oSMenuKey() );
	key->internalName = "keyUp";
	keys.Insert(*key);
	key->internalName = "keyDown";
	keys.Insert(*key);
	key->internalName = "keyLeft";
	keys.Insert(*key);
	key->internalName = "keyRight";
	keys.Insert(*key);
	key->internalName = "keyAction";
	keys.Insert(*key);
	key->internalName = "keySlow";
	keys.Insert(*key);
	key->internalName = "keySMove";
	keys.Insert(*key);
	key->internalName = "keyWeapon";
	keys.Insert(*key);
	key->internalName = "keyInventory";
	keys.Insert(*key);
	key->internalName = "keyCharScreen";
	keys.Insert(*key);
	key->internalName = "keySneak";
	keys.Insert(*key);
	key->internalName = "keyLook";
	keys.Insert(*key);


	void*buffer=0;
	zDWORD bindSize;
	zSTRING s1,s2;
	for (int i=0; i<keys.GetNumInList(); i++) {
		bindSize = zoptions->ReadRaw(zOPT_SEC_KEYS,keys[i].internalName.ToChar(),buffer);

		s1 = "";
		s2 = "";

		if (bindSize > 0) {
			s1 = zinput->GetNameByControlValue(((zWORD*)buffer)[0]);
			if (bindSize > 2)
				s2 = zinput->GetNameByControlValue(((zWORD*)buffer)[1]);
		}

		keys[i].name = (s2.IsEmpty() ? s1 : s1 + " or " + s2);

		delete[] buffer;
	}

	menu->SetKeys(keys);

	zBOOL oldShow = ogame->GetShowPlayerStatus();
	ogame->SetShowPlayerStatus(FALSE);
	menu->Show();
	ogame->SetShowPlayerStatus(oldShow);
*/
}

//static zCList<oCLogTopic> list2;

void oCNpc :: OpenScreen_Log()	// @HOME
{
	oCLogScreen* logScreen = zNEW( oCLogScreen() );	
	
	//
	// Werte setzen
	//
	oCMenu_Log*			menu	= logScreen->GetLogMenu			();
	oCLogManager&		mgrLogs = oCLogManager::GetLogManager	();	

	/*
	mgrLogs.AddTopic("ExampleTopic", oCLogTopic::zELogSection::zELogSection_Notes);
	mgrLogs.AddEntry("ExampleTopic","Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 Entry 1 ");
	mgrLogs.AddEntry("ExampleTopic","Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 Entry 2 ");
	mgrLogs.AddEntry("ExampleTopic","Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 Entry 3 ");
	mgrLogs.AddEntry("ExampleTopic","Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 Entry 4 ");
	mgrLogs.AddEntry("ExampleTopic","Entry 5 Entry 5 Entry 5 Entry 5 Entry 5 Entry 5 Entry 5 Entry 5 Entry 5 ");
	*/

	// old
//	list2						= mgrLogs.GetTopicList			();			
//	menu->SetLogTopics(list2);

	// patch 1.07 - verhindert Absturz beim runterfahren, wenn Logscreen offen war.
	menu->SetLogTopics(mgrLogs.GetTopicList());

	int day,hour,min;
	ogame->GetTime(day,hour,min);	

	zSTRING dayStr(day+1);
	dayStr+=".";

	zSTRING timeStr = zSTRING(hour) + ":";
	if (min<10) timeStr += "0";
	timeStr += zSTRING(min);

	menu->SetDayTime(dayStr,timeStr);

	//
	// Anzeigen
	//
	zBOOL oldShow = ogame->GetShowPlayerStatus();
	ogame->SetShowPlayerStatus(FALSE);
	logScreen->Show();
	ogame->SetShowPlayerStatus(oldShow);
		
	delete menu;menu=0;
};


void oCNpc :: OpenScreen_Map(int mapInst)
{
    SetWeaponMode2(NPC_WEAPON_NONE);	// [Moos] Waffe wegstecken, sonst �rger (equippte Waffe, aber nicht im Slot).
    GetHumanAI()->StartStandAni();

	oCMapScreen* menu = zNEW( oCMapScreen() );

	zBOOL oldShow = ogame->GetShowPlayerStatus();
	ogame->SetShowPlayerStatus(FALSE);
	menu->Show(mapInst);
	ogame->SetShowPlayerStatus(oldShow);
		
	delete menu;menu=0;
};


void oCNpc :: OpenScreen_Status() // @HOME
{
	oCStatusScreen* statusScreen = zNEW( oCStatusScreen() );
	oCMenu_Status*	menu = statusScreen->GetStatusMenu();
	oSMenuInfoAttribute* atr;

	// ***************************
	// Attributes (muss Reihenfolge im Menuescript entsprechen!!!!!!)
	// ***************************
	zSTRING unused;
	// * Strength *
	atr				= zNEW( oSMenuInfoAttribute() );
	atr -> actValue = GetAttribute(NPC_ATR_STRENGTH);
	atr -> maxValue = GetAttribute(NPC_ATR_STRENGTH);
	atr -> type		= oSMenuInfoAttribute::ATTRIB_STR;
	GetAttribInfo(NPC_ATR_STRENGTH,unused,atr->descr);
	menu->AddAttribute(*atr);
	// * Dexterity *
	atr				= zNEW(  oSMenuInfoAttribute() );
	atr -> actValue = GetAttribute(NPC_ATR_DEXTERITY);
	atr -> maxValue = GetAttribute(NPC_ATR_DEXTERITY);
	atr -> type		= oSMenuInfoAttribute::ATTRIB_DEX;
	GetAttribInfo(NPC_ATR_DEXTERITY,unused,atr->descr);
	menu->AddAttribute(*atr);	
	// * Mana / Psi ? *
	int energy		= NPC_ATR_MANA;
	atr				= zNEW( oSMenuInfoAttribute() );
	atr -> actValue = GetAttribute(energy);
	atr -> maxValue = GetAttribute(energy+1);
	atr	-> type		= oSMenuInfoAttribute::ATTRIB_MANA;
	GetAttribInfo(NPC_ATR_MANA,unused,atr->descr);
	menu->AddAttribute(*atr);
	// * Hitpoints *
	atr = zNEW(  oSMenuInfoAttribute() );
	atr -> actValue = GetAttribute(NPC_ATR_HITPOINTS);
	atr -> maxValue = GetAttribute(NPC_ATR_HITPOINTSMAX);
	atr -> type		= oSMenuInfoAttribute::ATTRIB_HP;
	GetAttribInfo(NPC_ATR_HITPOINTS,unused,atr->descr);
	menu->AddAttribute(*atr);
	
	//
	// Einzelwerte (Erfahrung etc.)
	//

	menu->SetExperience(GetLevel(),experience_points,experience_points_next_level);
	menu->SetLearnPoints(learn_points);
	
	//
	// Schutzwerte (muss Reihenfolge im Menuescript entsprechen!!!!!!)
	//

	oSMenuInfoArmor armor;
	armor.actValue = GetProtectionByType(oEDamageType_Blunt);	menu->AddArmor(armor);	// Waffen
	armor.actValue = GetProtectionByType(oEDamageType_Point);	menu->AddArmor(armor);	// Geschosse
	armor.actValue = GetProtectionByType(oEDamageType_Fire);	menu->AddArmor(armor);	// Feuer
	armor.actValue = GetProtectionByType(oEDamageType_Magic);	menu->AddArmor(armor);	// Magie
	
	// ***********************
	// Talents
	// ***********************
	oSMenuInfoTalent* tal;
	for (int i=0; i<oCNpcTalent::oTEnumNpcTalent::NPC_TAL_MAX; i++) 
	{		
		tal = zNEW(oSMenuInfoTalent);
		if (i == oCNpcTalent::oTEnumNpcTalent::NPC_TAL_UNKNOWN) continue;				
		
		GetTalentInfo(i,tal->name,tal->desc,tal->skillEnum);	// Informationen aus den Scripten auslesen
		oCNpcTalent* talent	= talents[i];						// Informationen des Talents auslesen
		if (talent) 
		{
			tal->skill		= talent->GetTalentSkill();

			switch (talent->GetTalent())
			{
				case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_1H:
					tal->value = this->GetHitChance(NPC_HITCHANCE_1H);
					break;
				case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_2H:
					tal->value = this->GetHitChance(NPC_HITCHANCE_2H);
					break;
				case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_BOW:
					tal->value = this->GetHitChance(NPC_HITCHANCE_BOW);;
					break;
				case oCNpcTalent::oTEnumNpcTalent::NPC_TAL_CROSSBOW:
					tal->value = this->GetHitChance(NPC_HITCHANCE_CROSSBOW);;
					break;
				default:
					tal->value		= talent->GetTalentValue();			
			break;
			}
		
		}
		else { tal->value = 0; tal->skill = 0; }

		// Talent in die Liste einfuegen
		menu->AddTalent(*tal);

		delete tal;tal=0;
	}
	
	//
	// Werte setzen
	//	
	menu->SetPlayerName	(GetName(TRUE));
	menu->SetGuild		(GetGuildName());
	// menu->SetGuildLevel	(GetLevel());
	// menu->SetTime		(ogame->GetWorldTimer()->GetTimeString());
	// menu->SetDay			(zSTRING(ogame->GetWorldTimer()->GetDay() + 1));			
	
	//
	// Anzeigen
	//
	zBOOL oldShow = ogame->GetShowPlayerStatus();
	ogame->SetShowPlayerStatus(FALSE);
	statusScreen->Show();
	ogame->SetShowPlayerStatus(oldShow);
		
	delete statusScreen;statusScreen=0;
}

// *********************************************************************
//							3D - Functions
// *********************************************************************

/* ----------------------------------------------------------------------
	
	oCNpc::THisVobAddedToWorld()

	27.11.2000	[Moos]	
                Fackelfix vereinheitlicht

   ---------------------------------------------------------------------- */

void oCNpc :: ThisVobAddedToWorld		(zCWorld *homeWorld)
{
	oCVob::ThisVobAddedToWorld	(homeWorld);
	
	// * called AFTER the actual addition *
	SetSleeping			(FALSE);
	SetCollDetDyn		(TRUE);
	SetCollDetStat		(TRUE);
	SetPhysicsEnabled	(TRUE);
	
	// Die Slot-Items auch einf�gen
	oCWorld* oWld = zDYNAMIC_CAST<oCWorld>(homeWorld);
	for (int i=0; i<invSlot.GetNumInList(); i++) {
        zCVob *vob = invSlot[i]->Vob();
		if (!invSlot[i]->inInventory && vob) {
			// Insert it.
			vob -> SetGroundPoly(NULL);
			if (oWld){
                if (!oWld->GetVobList()->IsInList(vob))
                    oWld->InsertVobInWorld(vob);  // [Moos] ist nach Levelwechsel manchmal n�tig

                oCItem *item = zDYNAMIC_CAST<oCItem>(vob);
                if (item){
                    zBOOL wasTree = SafeAddRef(item);	//  [Moos] 27.11. Crashfix

                    RemoveFromSlot(invSlot[i],false);
                    PutInSlot(invSlot[i],item);  // [Moos] ohne diese Zeilen sind manche Objekte unsichtbar (Pfeile in der Hand...)

                    SafeRelease(item, wasTree);
                }

            	oWld		-> EnableVob	(vob);
            }

			else		homeWorld	-> AddVob		(vob);

		}
	}

	AddEffect(effect);
}

void oCNpc :: ThisVobRemovedFromWorld	(zCWorld *homeWorld)
{
	// called BEFFORE the actual removal
	oCVob::ThisVobRemovedFromWorld	(homeWorld);

	// Clear Parser References....
//	state.ClearParserReferences();

	// Die Verweise auf temp. Objekte l�schen
	ClearFocusVob	();
	ClearVobList	();
	
	// [Ulf] : (AtHome2)
	SetEnemy		(NULL);	

	// Und Pointer auf Cutscenes l�schen
	state.CloseCutscenes();

	// InteractItem l�schen
	SetInteractItem	(NULL);

	// Die Slot-Items auch entfernen
	oCWorld* oWld = zDYNAMIC_CAST<oCWorld>(homeWorld);
	for (int i=0; i<invSlot.GetNumInList(); i++) {
        oCVob *vob = invSlot[i]->Vob();

		if (vob && vob->GetHomeWorld() && !invSlot[i]->inInventory) 
		{
			// Remove it.
			if (oWld)	oWld		-> DisableVob		(vob);
			else		homeWorld	-> RemoveVobSubtree	(vob);
		}
	}
	RemoveEffect(effect);
}

/*--------------------------------------------------------------------------

    void oCNpc::StopAllVoices()

    26-Sept-00	[SPECKELS]
				Neue Funktion: Stoppt alle laufenden Voice-Sounds des NSCs				

--------------------------------------------------------------------------*/

zBOOL oCNpc :: IsVoiceActive()
{
	return (listOfVoiceHandles.GetNumInList()>0);
};

void oCNpc :: StopAllVoices()
{	
	// Sounds stoppen
	int i=0;
	zTSoundHandle sndHandle;
	while (i<listOfVoiceHandles.GetNumInList())
	{
		sndHandle = listOfVoiceHandles.GetSafe(i);
		zsound->StopSound(sndHandle);
		i++;
	};
	// Alle Sounds aktualisieren (entfernt handles der gestoppten Sounds aus der Liste)
	voiceIndex=0;
	while (!UpdateNextVoice());
};

/*--------------------------------------------------------------------------

    zBOOL oCNpc::StopAllVoices()

    26-Sept-00	[SPECKELS]
				Neue Funktion: Updated oder entfernt einen VoiceSound des NSCs
				Iteriert bei mehrmaligen Aufrufen durch alle Sounds und 
				liefert TRUE, wenn Ende erreicht. Beginnt dann beim naechsten
				Aufruf wieder von vorne.				

--------------------------------------------------------------------------*/

zBOOL oCNpc :: UpdateNextVoice()
{	
	// voiceIndex ueberpruefen
	if (listOfVoiceHandles.GetNumInList()==0) return TRUE;
	if (voiceIndex>=listOfVoiceHandles.GetNumInList()) voiceIndex=0;

	// Handle holen und entweder entfernen oder Sound updaten
	zTSoundHandle sndHandle = listOfVoiceHandles.GetSafe(voiceIndex);	
	if (!zsound->IsSoundActive(sndHandle)) 
	{
		listOfVoiceHandles.RemoveIndex(voiceIndex);
	}
	else 
	{
		zsound->UpdateSound3D(sndHandle);		
		voiceIndex++;
	}

	// Ende der Liste erreicht?
	if (voiceIndex>=listOfVoiceHandles.GetNumInList()) voiceIndex=0;
	
	return (voiceIndex==0);	// TRUE, wenn n�chster Aufruf werder am Anfang beginnt
};

/*--------------------------------------------------------------------------

    void oCNpc :: ProcessNpc()

    26-Sept-00	[SPECKELS]
				Aufruf von UpdateNextVoice eingebaut: Pro Frame die Voicesounds
				aktualisieren!

--------------------------------------------------------------------------*/

void oCNpc :: ProcessNpc()
{
	// Sounds Updaten [SPECKELS]	
	
	if (listOfVoiceHandles.GetNumInList()>0)
	{
		if ( GetHomeWorld() )
		if ( GetHomeWorld()->GetMasterFrameCtr() % 4 ) 
			UpdateNextVoice();	//  jeden Frame ein Voice updaten

		/* alle Sounds auf einmal updaten (gibt meist sowieso nur max.1)
		{		
			voiceIndex=0;
			while (!UpdateNextVoice());	// alle Aktualisieren
		}
		*/	
	}
	
	// Nat�rliche Regeneration
	Regenerate	 ();
	// News Verbreitung 
	GetNewsMemory() -> CheckSpreadNews ();
	// Anti ZS_Talk Counter
	if (!CanTalk()) canTalk -= ztimer.GetFrameTimeF(); 
	// Portal gewechselt -> Wahrnehmung senden ?
	if (IsSelfPlayer()) {
		oCPortalRoomManager* man = ogame->GetPortalRoomManager();
		if (man && man->HasPlayerChangedPortalRoom()) AssessEnterRoom_S();	
	}

	//
	//	CODECHANGE [ROMAN]
	//
	if (fabs(divetime - ANI_TIME_INFINITE) > 0.0001)
		// Tauchzeit ist beschr�nkt
		if ( ANI_ACTION_DIVE == this->GetAnictrl()->GetActionMode() )
		{
			int npc_DAM_DIVE_TIME;
			zCPar_Symbol* symbol = parser.GetSymbol("NPC_DAM_DIVE_TIME");
			symbol->GetValue(npc_DAM_DIVE_TIME);
			
			divectr -= ztimer.GetFrameTimeF();
			if ( divectr < -npc_DAM_DIVE_TIME )
			{
				divectr = 0.0f;
				ChangeAttribute (NPC_ATR_HITPOINTS,-1);
				if (IsDead()) {
					GetModel()->StartAni("T_DIVE_2_DROWNED");
					DoDie();
				}
			}
		}
		else if ( divectr < divetime )
		{
			divectr += 2.0f * ztimer.GetFrameTimeF();
			if ( divectr > divetime ) divectr = divetime;
		}
	//
	//	CODECHANGE [ROMAN] END
	//

	//  CODECHANGE [MICHAEL]
	//  Brennt der Typ - kriegt er schaden
	//  tscha... nur wie brennt ein Typ?   1/3HP /sec soll er jedenfalls kriegen

	//  CODECHANGE [MICHAEL] END

	//
	//	CODECHANGE [CARSTEN] 
	//
	magFrontier.DoCheck();

	//
	//	CODECHANGE [CARSTEN] END
	//

	if (showNews) GetNewsMemory()->ShowDebugInfos();

    // [Moos] K�mmere dich um geplante Fackelanimationen
    CheckSetTorchAni();

	// [Wohlers] Timed Overlay Mds
	oCNpcTimedOverlay			*nodeData	= NULL;
	zCList	<oCNpcTimedOverlay>	*node		= timedOverlays.GetNextInList();
	while (node) {
		nodeData = node->GetData();
		if (nodeData && nodeData->Process()) {
			// Done. Remove it.
			timedOverlays.Remove(nodeData);
			if (GetModel())		GetModel()	->RemoveModelProtoOverlay( nodeData->GetMdsName() );
			if (GetAnictrl())	GetAnictrl()->InitAnimations();
			delete nodeData; nodeData = NULL;
			break;
		}
		node = node->GetNextInList();
	}
}

//int oCNpc :: GetSwimDivePoeppels()
// kann weg
//{
//	if (divetime!=ANI_TIME_INFINITE)
//		return swimdivectr/(10*1000);
//	else
//		return 0;
//}


// *********************************
//		Magic Book Functions
// *********************************

void oCNpc :: DoSpellBook()
{
	if (mag_book) mag_book->DoPerFrame();
}

void oCNpc :: OpenSpellBook (zBOOL showMagicCircle)
{
   	oCMag_Book* book = GetSpellBook();
	if (!book) return;
	// Und aufmachen
	zBOOL move = GetInMovement();
	if (move) EndMovement();
	book -> SetOwner(this);
	book -> Open(showMagicCircle);
	if (move) BeginMovement();
}

void oCNpc :: CloseSpellBook(zBOOL removeall)
{
	// Welches denn ?
	if (mag_book) mag_book->Close( removeall );
}

oCMag_Book *oCNpc :: GetSpellBook()
{
	return mag_book; 
}

// *********************************
//		Sound Materials
// *********************************

void oCNpc :: GetSoundMaterial_MA (zCSoundManager::zTSndManMedium &med1, oTSndMaterial &mat1, zSTRING s)
{
	oCItem *w = GetWeapon();
	if (w) {
		// Waffe gefunden -> "IA" Item attacks
		med1 = zCSoundManager :: zSND_MAN_MEDIUM_ITEM;
		mat1 = w->GetSoundMaterial();
	} 
	else 
	{
		// Nat�rliche Waffenart "MA"
		med1 = zCSoundManager :: zSND_MAN_MEDIUM_MODEL;
		if (this->IsMonster())		mat1 = oTSndMaterial(1);	else	// Jaw
		if (s.Search("FIST")>=0)	mat1 = oTSndMaterial(0);	else	// Fist
		if (s.Search("JAW" )>=0)	mat1 = oTSndMaterial(1);	else	// Jaw
		if (s.Search("TAIL")>=0)	mat1 = oTSndMaterial(2);	else	// Tail
									mat1 = oTSndMaterial(0);			// Fist
	}
}

void oCNpc :: GetSoundMaterial_AM (zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2, int damage)
{
	med2 = zCSoundManager :: zSND_MAN_MEDIUM_MODEL;
	//if (damage > 0) mat2 = SND_MAT_LEATHER;	
	//else {
		oCItem* armor = GetEquippedArmor();
		if (armor)	mat2 = armor -> GetSoundMaterial();
		else		mat2 = SND_MAT_LEATHER;
	//}
}

void oCNpc :: GetSoundMaterial_MH_HM (zCSoundManager::zTSndManMedium &med2, oTSndMaterial &mat2)
{
	med2 = zCSoundManager :: zSND_MAN_MEDIUM_MODEL;
	oCItem* armor = GetEquippedArmor();
	if (armor)	mat2 = armor -> GetSoundMaterial();
	else		mat2 = SND_MAT_LEATHER;
}

// *********************************
//		World Detection
// *********************************

zBOOL oCNpc :: HasSenseHear()
{
	return ((senses & NPC_SENSE_HEAR)>0);
}

zBOOL oCNpc :: HasSenseSee()
{
	return ((senses & NPC_SENSE_SEE)>0);
}

zBOOL oCNpc :: HasSenseSmell()
{
	return ((senses & NPC_SENSE_SMELL)>0);
}

void oCNpc :: SetSenses(int s)
{
	senses = s;
}

void oCNpc :: PrintStateCallDebug(const zSTRING &name, int callfunc, int callperc)
{
	if (!showaidebug) return;

	zSTRING s = "U: NPC: "+GetName(TRUE)+":Call "+name+"...";
	// Callfunc = -99 -> Keine Skriptfunktion n�tig
	if (callfunc!=-99) {
		zCPar_Symbol* sym = NULL;
		if (callfunc>0) sym = parser.GetSymbol(callfunc);
		if (!sym) {
			s += "failure : Script function not found.";
			zERR_MESSAGE(3,0,s);
			return;
		}
//		s += "("+sym->name+"/"+zSTRING(state.GetPriority(callperc))+") ";
	} //else
//		s += "("+zSTRING(state.GetPriority(callperc))+") ";

	// Funktion gibt es, kann Aufruf erfolgen ?
/*	if (!state.IsHigher(callperc)) {
		s += "failure : Current perception higher ("+state.GetStateInfo()+")";
		zerr.Message(s);
		return;
	}*/

	s += "success.";
	zERR_MESSAGE(3,0,s);
}

int oCNpc :: GetOldScriptState()
{
	return old_script_state;
}

int oCNpc :: GetAIState()
{
	return state.GetState();
}

int oCNpc :: GetAIStateTime()
// Liefert Anzahl Sekunden, wielange sich der NSC bereits in diesem Zustand befindet.
{
	return state.GetStateTime();
}

zBOOL oCNpc :: IsAIState(int nr)
{
	return (state.IsInState(nr));
}

void oCNpc :: ShowState(int x, int y)
{
	int origy = y;

	oCAniCtrl_Human* anictrl = GetAnictrl();
	zSTRING s = "Walk : ";
	switch (anictrl->GetWalkMode()) {
		case ANI_WALKMODE_WALK			:	s+="Walk";		break;
		case ANI_WALKMODE_RUN			:	s+="Run";		break;
		case ANI_WALKMODE_SNEAK			:	s+="Sneak";		break;
		case ANI_WALKMODE_WATER			:	s+="Water";		break;
		case ANI_WALKMODE_SWIM			:	s+="Swim";		break;
		case ANI_WALKMODE_DIVE			:	s+="Dive";		break;
	}

	s += "   State : "+state.GetStateInfo();

	screen -> Print(x,y,s);
	y += screen -> FontY();

	s = "P.detect : ";
	if (HasVobDetected(oCNpc::player))	s+="yes";
	else s+="no";

	s += "    BS:" + GetBodyStateName() + "(";
	if (IsBodyStateInterruptable()) s += "I";
	if (HasBodyStateFreeHands())	s += "F";
	if (HasBodyStateModifier(BS_MOD_HIDDEN))	s += "H";
	if (HasBodyStateModifier(BS_MOD_DRUNK))	s += "D";
	if (HasBodyStateModifier(BS_MOD_NUTS))	s += "N";
	if (HasBodyStateModifier(BS_MOD_BURNING))	s += "B";
	if (HasBodyStateModifier(BS_MOD_CONTROLLED))	s += "C";
	if (HasBodyStateModifier(BS_MOD_TRANSFORMED))	s += "T";
	s += ")";

	zREAL dist = 0.0f;
	if (oCNpc::player) dist = GetDistanceToVob(*oCNpc::player);
	s += "   D:"+zSTRING(int(dist))+" cm";

	screen -> Print(x,y,s);
	
	y+= screen->FontY();

	// CODECHANGE [STEFAN]
	y = origy;

	s = "NpcName : ";
	s+= this->GetName();
	screen -> Print(5800,y,s);
	y += screen -> FontY();

	s = "TempAttitude : ";

	int att	= GetAttitude(oCNpc::player);
	zSTRING ats;
	if (att==NPC_ATT_FRIENDLY) 
		ats = "friendly";
	else if (att==NPC_ATT_NEUTRAL) 
		ats = "neutral";
	else if (att==NPC_ATT_ANGRY) 
		ats = "angry";
	else if (att==NPC_ATT_HOSTILE) 
		ats = "hostile";
	else ats = zSTRING(att);
	
	s += ats;

	screen -> Print(5800,y,s);

	y += screen -> FontY();

	s = "PermAttitude : ";

	att	= GetPermAttitude(oCNpc::player);
	if (att==NPC_ATT_FRIENDLY) 
		ats = "friendly";
	else if (att==NPC_ATT_NEUTRAL) 
		ats = "neutral";
	else if (att==NPC_ATT_ANGRY) 
		ats = "angry";
	else if (att==NPC_ATT_HOSTILE) 
		ats = "hostile";
	else ats = zSTRING(att);
	
	s += ats;

	screen -> Print(5800,y,s);

	y += screen -> FontY();
	s = "Guild : ";
	
	s += GetGuildName();

	screen -> Print(5800,y,s);

	y += screen -> FontY();
	s = "TrueGuild : ";
	
	zCPar_Symbol* sym = parser.GetSymbol("TXT_GUILDS");
	if (sym) {
		zSTRING guildName;
		sym->GetValue(guildName,GetTrueGuild());
		s += guildName;
	} else {
		s += zSTRING("Error : Missing guild-names !");
	}

	screen -> Print(5800,y,s);
	// CODECHANGE [STEFAN] END
}

zBOOL oCNpc :: IsNear(oCNpc* other)
{
	const zREAL NEAR_DISTANCE = 500 * 500;		// 5m
	zREAL dist = (GetPositionWorld() - other->GetPositionWorld()).Length2();
	return (dist < NEAR_DISTANCE);
};

oCItem* oCNpc :: DetectItem (int w, zBOOL best)
{
	if (IsSelfPlayer()) return NULL;

	zREAL	curDist	= 0.0f;
	oCItem* found	= NULL;
	oCItem* item	= NULL;
	zREAL	dist	= zREAL_MAX;
	int		max		= vobList.GetNumInList();
	for (int i = 0; i < max; i++)
	{	
		// [BENDLIN] Addon - mehrere Kategorien/Flags (Wld_DetectItem)
		item = zDYNAMIC_CAST<oCItem>( vobList[i] );
		if (item && !item->HasFlag(ITM_FLAG_NFOCUS))
		if (((item->GetMainFlag() | item->GetFlags()) & w) != 0)
		{
			curDist = GetDistanceToVob2(*item);
			if (curDist < dist)
			{
				found	= item;
				dist	= curDist;
			}
		}
	};
	return found;
}

oCNpc* oCNpc :: DetectPlayer ()
{
	if (IsSelfPlayer()) return NULL;

	oCNpc* npc = NULL;
	int max = vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		npc = zDYNAMIC_CAST<oCNpc>(vobList[i]);
		if (npc) {
			if (npc->IsAPlayer()) return npc;
		}
	}
	return NULL;
}

oCMobInter* oCNpc :: FindMobInter(const zSTRING& name)
{
	oCMobInter*	mob			= NULL;
	oCMobInter*	nearestMob	= NULL;
	
	zREAL		dist	= 500;
	zREAL		minDist	= FLT_MAX;

	zCArray <zCVob*> vobList;

	zTBBox3D bbox;
	bbox.maxs = bbox.mins = GetPositionWorld();		
	// Vorderer Punkt	
	bbox.maxs[0] += dist; bbox.maxs[1] += dist; bbox.maxs[2] += dist;
	// Hinterer Punkt
	bbox.mins[0] -= dist; bbox.mins[1] -= dist; bbox.mins[2] -= dist;
	ogame->GetGameWorld() -> CollectVobsInBBox3D	(vobList, bbox);
	
	int max = vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		mob = zDYNAMIC_CAST<oCMobInter>(vobList[i]);
		if (mob) 
		{
			if (mob->GetScemeName().Search(name)>=0)
			if (mob->CanInteractWith(this))
			if (FreeLineOfSight(mob))
			{
				zREAL thisDist = (mob->GetPositionWorld()-this->GetPositionWorld()).Length2();
				if (thisDist<minDist)
				{
					nearestMob = mob;
					minDist	   = thisDist;
				}
			}
		}
	}	
	return nearestMob;
}

/* ----------------------------------------------------------------------
	
    oCNpc::FindSpot

	22.09.2000	[Moos]	
                Optimiert (==komplett umgestellt) und Distanzparameter eingef�gt

   ---------------------------------------------------------------------- */

zCVobSpot* oCNpc :: FindSpot(const zSTRING& name, zBOOL checkDistance, zREAL dist)
{
	zCVobSpot*	spot		= NULL;
	//zREAL		dist		= 2000;
	//zREAL		maxDist		= zREAL_MAX;
	//zREAL		curDist		= zREAL_MAX;
    int i,j;

	zCArray <zCVob*> vobList;

	zTBBox3D bbox;
	bbox.maxs = bbox.mins = GetPositionWorld();		
	// Vorderer Punkt	
	bbox.maxs[0] += dist; bbox.maxs[1] += dist; bbox.maxs[2] += dist;
	// Hinterer Punkt
	bbox.mins[0] -= dist; bbox.mins[1] -= dist; bbox.mins[2] -= dist;
	ogame->GetGameWorld() -> CollectVobsInBBox3D	(vobList, bbox);
	
	int max = vobList.GetNumInList();

    // schmeisse alle nicht-Spots raus
    for (i=max-1;i>=0;i--)
        if (!zDYNAMIC_CAST<zCVobSpot>(vobList[i]))
            vobList.RemoveIndex(i);

	max = vobList.GetNumInList();

    if (checkDistance){ // sortiere die Vobs, bevor die Rays gecastet werden
        zCArray <zREAL> distances;
    
	    for(i=0; i<max; i++)  // berechne die Entfernungen
            distances.InsertEnd(GetDistanceToVob2(*(vobList[i])));

        // benutze quicksort, sollten nicht allzuviele Vobs sein
        for (i=1; i<max ; i++)
            for (j=i-1; j>=0; j--){
                if (distances[j] > distances[j+1]){
                    zREAL  d_swap;
                    zCVob *v_swap;
                    d_swap         = distances[j];
                    distances[j]   = distances[j+1];
                    distances[j+1] = d_swap;

                    v_swap       = vobList[j];
                    vobList[j]   = vobList[j+1];
                    vobList[j+1] = v_swap;
                }
                else
                    j=-1;
            }
    }

	for (i=0; i<max; i++) {	
		spot = zDYNAMIC_CAST<zCVobSpot>(vobList[i]);

        assert(spot);

		if (spot->GetVobName().Search(name)>=0 && // hat das Ding den richtigen Namen?
			spot->IsAvailable(this)            &&  // ist es frei?
			FreeLineOfSight(spot))                 // kann ich es sehen?
        {
            if (checkDistance)
                return spot;
 				else if (!spot->IsOnFP(this)) // Den erstbesten freien Benutzen.	
				    return spot;
        }

    }
    return NULL; // failure

/* Old (22.9.00) implementation:

	zCVobSpot*	spot		= NULL;
	zCVobSpot*	foundSpot	= NULL;
	//zREAL		dist		= 2000;
	zREAL		maxDist		= zREAL_MAX;
	zREAL		curDist		= zREAL_MAX;

	zCArray <zCVob*> vobList;

	zTBBox3D bbox;
	bbox.maxs = bbox.mins = GetPositionWorld();		
	// Vorderer Punkt	
	bbox.maxs[0] += dist; bbox.maxs[1] += dist; bbox.maxs[2] += dist;
	// Hinterer Punkt
	bbox.mins[0] -= dist; bbox.mins[1] -= dist; bbox.mins[2] -= dist;
	ogame->GetGameWorld() -> CollectVobsInBBox3D	(vobList, bbox);
	
	int max = vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		spot = zDYNAMIC_CAST<zCVobSpot*>(vobList[i]);
		if (spot) {
			if (spot->GetVobName().Search(name)>=0)
			if (FreeLineOfSight(spot)) {
				// Auch noch Platz da, kein anderer NSC ?
				if (spot->IsAvailable(this)) {
					// Distanz wichtig ?
					if (checkDistance) {
						
						curDist = GetDistanceToVob2(*spot);
						if (curDist<maxDist) {
							foundSpot	= spot;
							maxDist		= curDist;
						}
					
					} else if (!spot->IsOnFP(this)) {						
						// Den erstbesten freien Benutzen.	
						return spot;
					
					}
				}
			}
		}
	}	
	return foundSpot;
*/
}

void oCNpc :: ForceVobDetection(zCVob *v)
{
	if (IsSelfPlayer()) return;

    InsertInVobList(v);
}

zBOOL oCNpc :: HasVobDetected(zCVob *v)
{
	if (IsSelfPlayer()) return FALSE;

	zCVob *vob;
	int max = vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		vob = vobList[i];
		if (vob == v) return TRUE;
	}	
	return FALSE;
}

zBOOL oCNpc :: CheckForOwner(zCVob *v)
// testet, ob der uebergebene Vob jemand gehoert, der den SC (this) gesehen hat
// und liefert TRUE, falls die SC - Aktion abgebrochen werden soll
{
	oCItem *item = zDYNAMIC_CAST<oCItem>(v);
	zCArray <zCVob*> vobs;

	if (item) {
		// Wahrnehmung ?
		parser.SetInstance		("ITEM",item);
		CreatePassivePerception	(NPC_PERC_ASSESSTHEFT,this);		
	} 
	return FALSE;
}

void oCNpc :: AI_ForceDetection()
{
	vobcheck_time = 100000;
}

zBOOL oCNpc :: CanSense(zCVob *vob)
// Kann der NSC den uebergebenen Vob sehen / riechen / hoeren
// unter Beruecksichtigung seiner Sinne ?
{
	if (vob==this) return FALSE;
		
	oCItem* item = zDYNAMIC_CAST<oCItem>(vob);
	if (item && item->HasFlag(ITM_FLAG_NFOCUS)) return FALSE;

	zTVobType vt = vob->GetVobType();
	if (HasSenseSmell()) {
		// **********************
		// Riechen 
		// **********************
		// Innerhalb der Smell - Range ?
		if (GetDistanceToVobApprox(*vob)<=senses_range) return TRUE;
	}

	if ((vt==zVOB_TYPE_NSC) && (HasSenseHear())) {
		// **********************
		// Hoeren 
		// **********************
	} 

	// Vob nur auf Sicht testen, wenn nur sehen aktiviert ist
	if (HasSenseSee()) {
		// **********************
		// Sehen 
		// **********************
		if (CanSee(vob)) {
			return TRUE;
		}
	}

	return FALSE;
}

void oCNpc :: DetectWitnesses(oCNpc *victim, int type)
// this		= player	(T�ter)
// victim	= Opfer
// TYPES = Attack / Steal / Aims
{
	zREAL dist = 2000;	// Radius = 20m

	// Benutze lokale Liste
	zCArray<zCVob*> vobList;

	// Create BBox
	zTBBox3D bbox;
	bbox.maxs = bbox.mins = GetPositionWorld();
	// Vorderer Punkt	
	bbox.maxs[0] += dist; bbox.maxs[1] += dist; bbox.maxs[2] += dist;
	// Hinterer Punkt
	bbox.mins[0] -= dist; bbox.mins[1] -= dist; bbox.mins[2] -= dist;
	ogame->GetGameWorld() -> CollectVobsInBBox3D	(vobList, bbox);
	
	if (showaidebug) {
		zSTRING s = "U: NPC: "+GetName()+"did sth. : check for witnesses...";
	}

	// Suche gefundene NSCs
	zCVob *v;
	int max = vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		v = vobList[i];
		if ((v->GetVobType()==zVOB_TYPE_NSC) && (v!=victim) && (v!=this)) {
			// NSC, der die Sitution beobachtet haben k�nnte, gefunden
			oCNpc *n = (oCNpc *)v;
			
			// *** old ***
			// Nicht gut, da nicht immer alle NSCs reagieren, 
			// auch wenn sie Nahe genug sind
			// if (!n->IsDead() && n->HasVobDetected(this)) {
			// ***********

			// *** New ***
			// Nur LOS-Check, so k�nnen alle Beteiligten NSC in der N�he darauf reagieren
			// ***********
			if (!n->IsDead() && n->FreeLineOfSight(this)) {
				// Er hat's gesehen und wird auch drauf reagieren....
				
				int callfunc = 0;
//				if (type==NPC_PERC_WITNESS_ATTACK)	callfunc = n->assessFriendsDamage;
//				if (type==NPC_PERC_WITNESS_THEFT)	callfunc = n->assessTheft;
//				if (type==NPC_PERC_MURDER)			callfunc = n->assessMurder;
				n->PrintStateCallDebug("Witness",callfunc,type);

/*				if (n->state.IsHigher(type)) {
					// Zeugenfunktion aktivierem -> nur bei befreundeten NSCs ????
					if ((type==NPC_PERC_WITNESS_ATTACK) && (n->IsFriendly(victim)))  {
						n->ReactionWitness(n->assessFriendsDamage,this,victim);	
				
					} else if (type==NPC_PERC_WITNESS_THEFT) {
						n->ReactionWitness(n->assessTheft,this,victim);

					} else if (type==NPC_PERC_MURDER) {
						n->ReactionWitness(n->assessMurder,this,victim);
					
					}
					n -> state.SetPriority(type);
				}*/
			}
		}
	};
	vobList.DeleteList();
}

oCNpc* oCNpc :: FindNpc (int instance, int guild, int aiState, zBOOL nearest)
// Basierend auf letzen Warnehmungscheck 
{
	if (IsSelfPlayer()) return NULL;

	oCNpc* found	= NULL;
	oCNpc* npc		= NULL;
	zREAL dist		= 0.0f;
	zREAL lowDist	= zREAL_MAX;
	int max			= vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		npc = zDYNAMIC_CAST<oCNpc>(vobList[i]);
		if (npc) {
			if ((instance>=0) && (npc->GetInstance	()!=instance))		continue;
			if ((guild>=0)    && (npc->GetTrueGuild	()!=guild))			continue;
			if ((aiState>=0)  &&  !npc->state.IsInState(aiState))		continue;
			
			if (nearest) {
				dist = GetDistanceToVob2(*npc);
				if (dist < lowDist) {
					found	= npc;
					lowDist = dist;
				}
			} else {
				return npc;
			}
		}
	}
	return found;
}

oCNpc* oCNpc :: FindNpcEx (int instance, int guild, int aiState, zBOOL nearest, zBOOL ignorePlayer, zBOOL ignoreDead)
// Basierend auf letzen Warnehmungscheck 
{
	if (IsSelfPlayer()) return NULL;

	oCNpc* found	= NULL;
	oCNpc* npc		= NULL;
	zREAL dist		= 0.0f;
	zREAL lowDist	= zREAL_MAX;
	int max			= vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		npc = zDYNAMIC_CAST<oCNpc>(vobList[i]);
		if (npc) {
			if ((instance>=0)	&& (npc->GetInstance	()!=instance))	continue;
			if ((guild>=0)		&& (npc->GetTrueGuild	()!=guild))		continue;
			if ((aiState>=0)	&&  !npc->state.IsInState(aiState))		continue;
			if ((ignorePlayer)	&&  npc->IsSelfPlayer())				continue;				
			if ((ignoreDead)	&&  !npc->IsConditionValid())			continue;				
			
			if (nearest) {
				dist = GetDistanceToVob2(*npc);
				if (dist < lowDist) {
					found	= npc;
					lowDist = dist;
				}
			} else {
				return npc;
			}
		}
	}
	return found;
}

oCNpc* oCNpc :: FindNpcExAtt (int instance, int guild, int aiState, zBOOL nearest, zBOOL ignorePlayer, zBOOL ignoreDead, int att)
// Basierend auf letzen Warnehmungscheck 
{
	if (IsSelfPlayer()) return NULL;

	oCNpc* found	= NULL;
	oCNpc* npc		= NULL;
	zREAL dist		= 0.0f;
	zREAL lowDist	= zREAL_MAX;
	int max			= vobList.GetNumInList();
	for (int i=0; i<max; i++) {	
		npc = zDYNAMIC_CAST<oCNpc>(vobList[i]);
		if (npc) {
			if ((instance>=0)	&& (npc->GetInstance	()!=instance))	continue;
			if ((guild>=0)		&& (npc->GetTrueGuild	()!=guild))		continue;
			if ((aiState>=0)	&&  !npc->state.IsInState(aiState))		continue;
			if ((ignorePlayer)	&&  npc->IsSelfPlayer())				continue;				
			if ((ignoreDead)	&&  !npc->IsConditionValid())			continue;				
			// [BENDLIN] 2002-05-12, nur die OTHER, die in einem bestimmten Verh�ltnis zu SELF stehen (nicht umgekehrt)
			if ((npc->GetAttitude(this)!=att))							continue;
			
			if (nearest) {
				dist = GetDistanceToVob2(*npc);
				if (dist < lowDist) {
					found	= npc;
					lowDist = dist;
				}
			} else {
				return npc;
			}
		}
	}
	return found;
}


int oCNpc :: GetComrades()
{
	zCArray<zCVob*>		found;
	oCNpc*	npc			= NULL;
	int		count		= 0;

	zTBBox3D bbox;
	zREAL distance	 = percRange[NPC_PERC_ASSESSENEMY];
	bbox.maxs		 = bbox.mins = GetPositionWorld();	
	bbox.maxs[0]	+= distance; bbox.maxs[1]	+= distance; bbox.maxs[2]	+= distance;
	bbox.mins[0]	-= distance; bbox.mins[1]	-= distance; bbox.mins[2]	-= distance;
	GetHomeWorld()->CollectVobsInBBox3D (found, bbox);	
	
	for (int i=0; i<found.GetNumInList(); i++) {
		
		npc = zDYNAMIC_CAST<oCNpc>(found[i]);
		if (npc && npc->IsConditionValid() && (npc!=this)) {
			
			if (GetTrueGuild() == npc->GetGuild()) count++;

		}
	}
	
	return (count);
}

zBOOL oCNpc::AreWeStronger(oCNpc* enemy)
// SELF		= this
// OTHER	= enemy
{
	if (!enemy)				return TRUE;
	if (!GetHomeWorld())	return TRUE;

	// b) NPC_AreWeStonger (self, other):
	// Wenn die Summe der Level aller NPCs (human, Monster), die zu mir
	// feindlich sind und die zu <other> freundlich sind
	// MEHR ALS DOPPELT SO HOCH ist
	// (x  > 2*y),
	// wie die Summe der Level aller Leute, die zu mir freundlich sind, und die
	// zu <other> feindlich sind,
	// dann NEIN,
	// sonst JA (= wir SIND st�rker, nicht echt, aber ab doppelter Gegnerst�rke
	// zu fliehen ist fr�h genug, sonst kommen die Jungs aus dem Rennen nicht
	// mehr raus :) )
	// Beachten:
	// 1) Monster k�nnen feindlich zu beiden Menschen sein --> egal, z�hlen auf
	// beiden Seiten
	// 2) Jemand, der z.B. zu mir freundlich und zu <other> feindlich ist, wird
	// demnach doppelt gewertet --> ok so	
	
	int levelFriends	= 0;
	int levelEnemies	= 0;
	
	zCArray<zCVob*>		found;
	oCNpc* npc			= NULL;

	zTBBox3D bbox;
	zREAL distance	 = 1000;
	bbox.maxs		 = bbox.mins = GetPositionWorld();	
	bbox.maxs[0]	+= distance; bbox.maxs[1]	+= distance; bbox.maxs[2]	+= distance;
	bbox.mins[0]	-= distance; bbox.mins[1]	-= distance; bbox.mins[2]	-= distance;
	GetHomeWorld()->CollectVobsInBBox3D (found, bbox);	
	
	for (int i=0; i<found.GetNumInList(); i++) {
		
		npc  = zDYNAMIC_CAST<oCNpc>(found[i]);
		if (npc) {
			
			if ((GetAttitude(npc)==NPC_ATT_HOSTILE)  && (enemy->GetAttitude(npc)==NPC_ATT_FRIENDLY)) levelEnemies += npc->GetLevel();
			if ((GetAttitude(npc)==NPC_ATT_FRIENDLY) && (enemy->GetAttitude(npc)==NPC_ATT_HOSTILE))  levelFriends += npc->GetLevel();

		}
	}
	
	return (levelEnemies >= 2*levelFriends);
};

oCNpc* oCNpc :: IsEnemyBehindFriend(oCNpc* friend1)
{
	// Gibt JA/NEIN und ggf. FREUND-SC/NSC aus.
	// Nehme innerhalb von Fluchtradius um <Feind> alle Personen
	// Pr�fe f�r jede Person:
	// Wenn Att zu Person = freundlich, dann
	// Wenn Feind NICHT im Sichtfeld dieser Person, dann
	//		Gib JA und <Person> aus
	//		Sonst gib NEIN aus
	// -------------
	// this		= Feind
	// friend1	= Betrachter - Freund
	if (!GetHomeWorld()) return NULL;
	
	zCArray<zCVob*>	found;
	oCNpc* npc		= NULL;

	zTBBox3D bbox;
	zREAL distance	 = percRange[NPC_PERC_ASSESSTALK];
	bbox.maxs		 = bbox.mins = GetPositionWorld();	
	bbox.maxs[0]	+= distance; bbox.maxs[1]	+= distance; bbox.maxs[2]	+= distance;
	bbox.mins[0]	-= distance; bbox.mins[1]	-= distance; bbox.mins[2]	-= distance;
	GetHomeWorld()->CollectVobsInBBox3D (found, bbox);	
	
	for (int i=0; i<found.GetNumInList(); i++) {
		
		npc  = zDYNAMIC_CAST<oCNpc>(found[i]);
		if (npc)												// a) NPC ?
		if (friend1->IsFriendly(npc))							// b) ein Freund vom Betrachter ?
		if (!npc -> HasVobDetected(this)) {						// c) NPC hat Feind noch nicht wahrgenommen.
			
			return npc;

		}
	}
	return NULL;
};

zBOOL oCNpc :: InMobInteraction(const zSTRING& keyWord, int keyState)
{
	oCMobInter* mob = GetInteractMob();
	if (mob) {
		zSTRING name = mob->GetScemeName();
		return ((name.Search(keyWord)>=0) && (mob->GetState()==keyState));
	}
	return FALSE;
}

zBOOL oCNpc :: FreeLineOfSight(zCVob *vob)
{
	return FreeLineOfSight(vob->GetBBox3DWorld().GetCenter(),vob);
//	return FreeLineOfSight(vob->GetPositionWorld(),vob);
}

zBOOL oCNpc :: FreeLineOfSight(zVEC3& pos, zCVob *vob)
{
	zCArray <zCVob*> ignore;
	ignore.Insert(this);
	if (vob) ignore.Insert(vob);
	// GetDirection ( Ziel - Start )
	zVEC3 dir = (pos - GetPositionWorld()) * 0.95F;
	// Can See ?
	zBOOL free = !(ogame->GetGameWorld()->TraceRayFirstHit(GetPositionWorld(),dir,&ignore, zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_CHARACTER ));

	return free;
}

zBOOL oCNpc :: FreeLineOfSight_WP(zVEC3& pos, zCVob *vob)
{
	zCArray <zCVob*> ignore;
	ignore.Insert(this);
	if (vob) ignore.Insert(vob);
	// GetDirection ( Ziel - Start )
	zVEC3 org = GetPositionWorld()+zVEC3(0,100,0);
	zVEC3 dir = (pos - org) * 0.95F;
	// Can See ?
	zBOOL free = !(ogame->GetGameWorld()->TraceRayFirstHit(org,dir,&ignore, zTRACERAY_VOB_IGNORE_NO_CD_DYN | zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_CHARACTER ));

	return free;
}


zBOOL oCNpc :: CanSee (zCVob *vob, zBOOL ignoreAngles)
{
	oCNpc* target = zDYNAMIC_CAST<oCNpc>(vob);
	// Unsichtbarkeit einbeziehen
	if (target) {
		if (target->InMobInteraction("BARREL",1)) {
			// Im Fass versteckt, nicht sehen
			return FALSE;
		}
	}

	const int NPC_SEE_MAXANGLE = 90;
	zREAL azi,elev;
	zCArray <zCVob*> ignore;
	ignore.Insert(this);
	ignore.Insert(vob);
	// Get Distance
	zVEC3 dir = (vob->GetPositionWorld() - GetPositionWorld());
	zREAL len = dir.LengthApprox();
	// Ausserhalb der Senses Reichweite ?
	if (len>senses_range)	return FALSE;

	// Can See ?
	zVEC3 pos	= GetPositionWorld();
	pos[VY]		= GetBBox3DWorld().maxs[VY];
	zBOOL flag = (ogame->GetGameWorld()->TraceRayFirstHit(pos,dir,&ignore,zTRACERAY_STAT_POLY | zTRACERAY_POLY_IGNORE_TRANSP));
	// Delete List
	ignore.DeleteList();
	
	if (!flag) {
		if (ignoreAngles) return TRUE;
		// Auch in Sichtradius ?
		// FIXME : Hier noch Regeltechnischer Check, ob Ziel aureichend beleuchtet.
		GetAngles(vob,azi,elev);
		return ((abs(azi)<=NPC_SEE_MAXANGLE) && (abs(elev)<=NPC_SEE_MAXANGLE));
	}
	return FALSE;
}

// *********************************************************************
// Regeneration
// *********************************************************************

void oCNpc :: SetSwimDiveTime (zREAL swimTimeSec, zREAL diveTimeSec)
// Parameter in Sekunden
{
	swimtime	= swimTimeSec * 1000.0f;	// nach ms
	divetime	= diveTimeSec * 1000.0f;	// nach ms
	divectr		= divetime;
}

void oCNpc :: GetSwimDiveTime (zREAL &_swimTime, zREAL& _diveTime, zREAL& _diveCtr)
// Parameter in milliSekunden
{
	_swimTime = swimtime;
	_diveTime = divetime;
	_diveCtr  = divectr;
}

//void oCNpc :: SetRegenerationTime (int atr, zREAL time)
//{
//	switch (atr) {
//		case NPC_ATR_HITPOINTS		:	 hpHeal		= hpHealTime	= time;		break;
//		case NPC_ATR_MANA			:	 manaHeal	= manaHealTime	= time;		break;
//	}
//}

void oCNpc :: Regenerate()
{
	zREAL delay = ztimer.GetFrameTimeF();
	if (!IsDead()) {
		hpHeal		-= delay;
		manaHeal	-= delay;
		// Nat�rliche Heilung
		if ((GetAttribute(NPC_ATR_REGENERATEHP) > 0) && (hpHeal <= 0) && (GetAttribute(NPC_ATR_HITPOINTS)<GetAttribute(NPC_ATR_HITPOINTSMAX))) {
			ChangeAttribute(NPC_ATR_HITPOINTS,+1);		
			hpHeal = GetAttribute(NPC_ATR_REGENERATEHP) * 1000.0f;
		}
		// Nat�rliche Mana - Regeneration 
		if ((GetAttribute(NPC_ATR_REGENERATEHP) > 0) && (manaHeal <= 0) && (GetAttribute(NPC_ATR_MANA)<GetAttribute(NPC_ATR_MANAMAX))) {
			ChangeAttribute(NPC_ATR_MANA,+1);		
			manaHeal = GetAttribute(NPC_ATR_REGENERATEMANA) * 1000.0f;
		}
	}

	// Noch voll am abbrennen ?
	if (fireDamage>0) {
		// im Wasser, Feuer gel�scht ?
		if (GetAnictrl()->GetWaterLevel()>=1) {
			StopBurn();
		} else {
			fireDamageTimer -= delay;
			if (fireDamageTimer<0) {

				//DoHit(1.0f,zRand(360),GetPositionWorld());

				fireDamage--;
				if (fireDamage == 0) {
					StopBurn();
					fireDamageTimer = 0;
				} else {
					fireDamageTimer = 2000;
				}
			}
		}
	}
}

void oCNpc :: RefreshNpc()
// Bei jedem SCLevelwechsel und um 24 h:
// Keine R�stung  generiere R�stung nach Tabelle
// Bogen  aber keine Pfeile  generiere 50 Pfeile
// LE, Mana und PSI auf Max
{
	// Tote und Monster machens nicht !
	if (IsDead() || IsMonster()) return;
	
	// *********
	//  R�stung
	// *********
	oCItem* item = GetEquippedArmor();
	if (!item) EquipBestArmor();
	item = GetEquippedArmor();
	if (!item) {
		// generiere R�stung aus Tabelle.... ne, besser aus Skript
		parser.SetInstance	("SELF",this);
		parser.CallFunc		(zSTRING("B_REFRESHARMOR"));
	}
	// *********
	//  Bows
	// *********
	oCItem* weapon				= NULL;
/*	zCListSort<oCItem>* node	= inventory2.GetFirstNode(INV_COMBAT);
	while (node) {
		weapon = node->GetData();
		// Kann Item benutzt werden
		if (CanUse(weapon) && weapon->HasFlag(ITM_CAT_FF)) {
			if (!IsMunitionAvailable(weapon)) CreateItems(weapon->GetMunitionInstance(),50);
			break;
		}
		node = node -> GetNextInList();
	}*/

//	inventory2.UnpackCategory(INV_MAGIC);
	inventory2.UnpackCategory();
//	int numItems = inventory2.GetNumItemsInCategory(INV_COMBAT);
	int numItems = inventory2.GetNumItemsInCategory();
	for (int i=0; i<numItems; i++) {
//		inventory2.UnpackItemsInCategory(INV_COMBAT);
//		weapon = GetItem(INV_COMBAT, i);
		weapon = GetItem(0, i);
		if (weapon && weapon->HasFlag(ITM_CAT_FF) && CanUse(weapon)) {
			if (!IsMunitionAvailable(weapon)) CreateItems(weapon->GetMunitionInstance(),50);
			break;
		}
	}

	// ********
	//  Stats
	// ********
	SetAttribute(NPC_ATR_HITPOINTS,	GetAttribute(NPC_ATR_HITPOINTSMAX));
	SetAttribute(NPC_ATR_MANA,		GetAttribute(NPC_ATR_MANAMAX));
};

// Render
void oCNpc :: RenderNpc ( zCView *viewitem )
{
	zCCamera	i_cam;
	zCWorld*	i_wld = zNEW( zCWorld() );
	zCVob*		i_vob = zNEW( zCVob() );

	SetPositionWorld	( 0,0,0 );
	i_wld->AddVob		( this  );

	zTBBox3D box3d	= GetBBox3DWorld();

	float x,y,z;

	x = (box3d.maxs[0] + box3d.mins[0]) / 2;
	y = (box3d.maxs[1] + box3d.mins[1]) / 2;
	z = (box3d.maxs[2] + box3d.mins[2]) / 2;

	// Groesste Distanz ermitteln
	float dx,dy,dz;
	dx = box3d.maxs[0] - box3d.mins[0];
	dy = box3d.maxs[1] - box3d.mins[1];
	dz = box3d.maxs[2] - box3d.mins[2];
	if (dx<dy) dx = dy;
	if (dz<dy) dx = dz;

	i_cam.SetRenderTarget(viewitem);
	i_vob->SetPositionWorld (x,y,-dx);			
	i_cam.SetVob(i_vob);

	i_cam.SetFarClipZ (zVALUE_MAX);

//	i_wld.usingBspPortals = 0;
	i_wld->SetDrawVobBBox3D(FALSE);
//	i_cam.drawMode	= zCAM_DRAW_TEX_PER;
//	i_cam.shadeMode = zSHADE_GOURAUD;

	// Insert it in 3D
	i_wld->Render(i_cam);

	// Rewove from 3D
	i_wld->RemoveVob( this );

	zRELEASE(i_vob);
	zRELEASE(i_wld);
}

zBOOL oCNpc :: IsAPlayer()
{
	return (this==oCNpc::player);
}

zBOOL oCNpc :: IsSelfPlayer()
{
	return (this==oCNpc::player);
}

int oCNpc :: GetPlayerNumber()
// basiert auf oPlayerInfo ( Bert )
// liefert 0 - ung�ltig
// 1 - 4 f�r PlayerInstanzen identifiziet �ber deren Instanzname !
{
//	for (int i=1; i<=MAX_PLAYER_INSTANCES; i++) {
//		if (GetInstanceName()==PLAYER_INSTANCE[i]) return i;
//	}
	return 0;
}

void oCNpc :: SetKnowsPlayer(int playerNumber)
{
//	if (playerNumber<=0) return;
	knowsPlayer = TRUE;
};

zBOOL oCNpc :: KnowsPlayer (oCNpc* player)
{
	return (knowsPlayer>0);
}

zBOOL oCNpc :: KnowsPlayer(int playerNumber)
{
	return (knowsPlayer>0);
}

zBOOL oCNpc :: IsMonster()  
// Monster haben kein Inventory  
// Monster sind immer in einem Waffenmodus  
{     
	return ((!this->IsHuman()) && (!this->IsOrc()) && (this->GetTrueGuild()!=NPC_GIL_DRAGON) && (this->GetTrueGuild()!=NPC_GIL_FIREGOLEM) && (this->GetTrueGuild()!=NPC_GIL_ICEGOLEM)) ;   
}    

zBOOL oCNpc :: IsHuman()  
{         
	return (GetTrueGuild()<=NPC_GIL_HUMANS);  
}    

zBOOL oCNpc :: IsGoblin()  
{   
	return (GetTrueGuild()==NPC_GIL_GOBBO				||
			GetTrueGuild()==NPC_GIL_GOBBO_SKELETON		||
			GetTrueGuild()==NPC_GIL_SUMMONED_GOBBO_SKELETON	);  
}

zBOOL oCNpc :: IsOrc()  
{   
	return (GetTrueGuild()>=NPC_GIL_ORCS);  
}

zBOOL oCNpc :: IsSkeleton()  
{   
	return ( GetTrueGuild()==NPC_GIL_SKELETON				||
			 GetTrueGuild()==NPC_GIL_SUMMONED_SKELETON );

}

void oCNpc :: SetAsPlayer()
{
	if (!oCNpcFocus :: focus) oCNpcFocus :: InitFocusModes();

	if (player) {
		// Der alte Player l�scht RefenceVerweise
		player->ClearVobList	();
		player->ClearFocusVob	();
//		player->CleanUp();
	};

	ClearVobList();
	ClearFocusVob();
//	CleanUp();

	// Patch 1.08 : Ref-Leak bei Spielerwechsel...
	oCPlayerInfo* playerInfo = dynamic_cast<oCPlayerInfo*>(zCPlayerInfo::GetActivePlayer());
	if (playerInfo) playerInfo->SetPlayerVob(this);

	// Diesen als neuen Player einrichten
	player = this;
	parser.SetInstance("HERO",player);
	
	// Focus-Mode ein.
	int fm = GetWeaponMode();
	if (fm==NPC_WEAPON_NONE) {
		oCNpcFocus :: focus -> SetFocusMode(FOCUS_NORMAL);
	} else if (fm<NPC_WEAPON_BOW) {
		oCNpcFocus :: focus -> SetFocusMode(FOCUS_MELEE);
	} else {
		oCNpcFocus :: focus -> SetFocusMode(FOCUS_RANGED);
	}

	// HumanAI erzeugen
	if (!GetHumanAI()) InitHumanAI();
	
	// Kamera-modus ein
	if (human_ai) human_ai -> InitCamModes	();

	zCAICamera* aiCam	= ogame -> GetCameraAI	();
	zCVob*		camVob	= ogame -> GetCameraVob	();
	if (aiCam && camVob && camVob->RegisteredInWorld()) {
		aiCam->ClearTargetList	();
		aiCam->SetTarget		(oCNpc::player);
		// [BENDLIN] Addon - Ghost Alpha
		if (NPC_FLAG_GHOST == (oCNpc::player->variousFlags & NPC_FLAG_GHOST))
			aiCam->SetTargetAlpha(zoptions->ReadReal("INTERNAL", "GhostAlpha", 0.3f));
		aiCam->SetMode			(CamModNormal);
		aiCam->ReceiveMsg		(zPLAYER_BEAMED);
		// kamera 2 m hinter Target setzen.... (Test)
		camVob->SetPositionWorld (GetPositionWorld() - GetAtVectorWorld()*200);
		camVob->SetHeadingAtWorld(GetAtVectorWorld());
	}
	SetWalkStopChasm(FALSE);
}

// ***************************************************************
// Ehemals in zCAIManager
// ***************************************************************

/*--------------------------------------------------------------------------

    oCNpc::DoDoAniEvents()

 

    13-Sep-00       [Max Dennis Luesebrink]
					Def_DRAWSOUND eingefuegt


--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: DoDoAniEvents()
{
	// Warum werden manche Events immer wieder aktiviert - z.B. DEF_INSERT_ITEM bis zu 3x
	zSTRING n1,n2;
	zCArray<zCModelAniEvent*> events;
	
	GetModel()->GetOccuredAniEventList (events);
	int c = events.GetNumInList();
	for (int i=0; i<c; i++) {
		zCModelAniEvent *ev = events[i];
		if (ev->aniEventType==zMDL_EVENT_TAG) {			
			if (ev->tagString=="DEF_FIGHTMODE") {
				// **************************************
				// Waffenwechsel 
				// **************************************
				n1 = ev->string[0];
				SetWeaponMode2(n1);

			} else if (ev->tagString=="DEF_SWAPMESH") {
				// **************************************
				// Waffenwechsel 
				// **************************************
				n1 = ev->string[0];
				n2 = ev->string[1];
				DoModelSwapMesh(n1,n2);

			} else if (ev->tagString=="DEF_PLACE_MUNITION") {
				// **************************************
				// Pfeil einf�gen / entfernen
				// **************************************
				DoInsertMunition(ev->string[0]);

			} else if (ev->tagString=="DEF_REMOVE_MUNITION") {
				// **************************************
				// Pfeil einf�gen 
				// **************************************
				DoRemoveMunition();
			
			} else if (ev->tagString=="DEF_INSERT_ITEM") {
				// **************************************
				// Item Interaktion - Item einf�gen
				// **************************************
//				zCView::StdPrintwin(zSTRING("Send Insert\n"));
				oCMsgManipulate* msg = zNEW( oCMsgManipulate(oCMsgManipulate::EV_INSERTINTERACTITEM,"",ev->string[0]));
				msg->SetHighPriority(TRUE);
				GetEM()->OnMessage(msg,this);

			} else if (ev->tagString=="DEF_REMOVE_ITEM") {
				// **************************************
				// Item Interaktion - Item entfernen
				// **************************************
				oCMsgManipulate* msg = zNEW(oCMsgManipulate(oCMsgManipulate::EV_REMOVEINTERACTITEM,"",ev->string[0]));
				msg->SetHighPriority(TRUE);
				GetEM()->OnMessage(msg,this);

			} else if (ev->tagString=="DEF_CREATE_ITEM") {
				// ************************************************
				// Item Interaktion - Item komplett neu erschaffen
				// ************************************************
				 
				oCMsgManipulate* msg = zNEW(oCMsgManipulate(oCMsgManipulate::EV_CREATEINTERACTITEM,ev->string[1],ev->string[0]));
				msg->SetHighPriority(TRUE);
				GetEM()->OnMessage(msg,this);
			
			} else if (ev->tagString=="DEF_DESTROY_ITEM") {
				// **************************************
				// Item Interaktion - Item zerst�ren
				// **************************************
				oCMsgManipulate* msg = zNEW(oCMsgManipulate(oCMsgManipulate::EV_DESTROYINTERACTITEM,"",ev->string[0]));
				msg->SetHighPriority(TRUE);
				GetEM()->OnMessage(msg,this);

			} else if (ev->tagString=="DEF_PLACE_ITEM") {
				// **************************************
				// Item Interaktion - Item zerst�ren
				// **************************************
				oCMsgManipulate* msg = zNEW(oCMsgManipulate(oCMsgManipulate::EV_PLACEINTERACTITEM,"",""));
				msg->SetHighPriority(TRUE);
				GetEM()->OnMessage(msg,this);

			} else if (ev->tagString=="DEF_EXCHANGE_ITEM") {
				// **************************************
				// Item Interaktion - Item austauschen
				// **************************************
//				zCView::StdPrintwin(zSTRING("Send Insert\n"));
				oCMsgManipulate* msg = zNEW(oCMsgManipulate(oCMsgManipulate::EV_EXCHANGEINTERACTITEM,ev->string[1],ev->string[0]));
				msg->SetHighPriority(TRUE);
				GetEM()->OnMessage(msg,this);

			} else if (ev->tagString=="DEF_DROP_TORCH") {
				// **************************************
				// Item Interaktion - Torch weg schmeissen
				// **************************************
				oCItem *item = NULL;
				item = GetSlotItem(NPC_NODE_LEFTHAND);
				if( item && (item->GetInstanceName().Search("ITLSTORCH")==0) )
				{
					RemoveFromSlot(NPC_NODE_LEFTHAND,TRUE);
					SetTorchAni( FALSE, FALSE);
				}

			} else if (ev->tagString=="DEF_INV_TORCH") {
				// **************************************
				// Item Interaktion - Torch ins inv packen
				// **************************************
				oCItem *item = NULL;
				item = GetSlotItem(NPC_NODE_LEFTHAND);
				if( item && (item->GetInstanceName().Search("ITLSTORCH")==0) )
				{
					oCItem* torch = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCH");
					RemoveFromSlot(NPC_NODE_LEFTHAND,FALSE);
					PutInInv(torch);
					zRELEASE( torch );

					SetTorchAni( FALSE, FALSE);

                    // [Moos] 18.1.2001: lasse die Fackel bei n�chster Gelegenheit wieder holen:
                    GetActiveInfoWritablePrivate()->putTorchBackInHand = TRUE;

				}
			} else if (ev->tagString=="DEF_DRAWSOUND") {
				// **************************************
				// Sound beim ziehen der waffe abspielen!!!
				// **************************************
				oCItem*		item = GetSlotItem(NPC_NODE_RIGHTHAND);
				if (!item)	item = GetSlotItem(NPC_NODE_SWORD);
				if (!item)	item = GetSlotItem(NPC_NODE_LONGSWORD);
				if (!item)	item = GetSlotItem(NPC_NODE_LEFTHAND);
				
				if( item ) 
				{
					switch( item->GetSoundMaterial() )
					{
							case SND_MAT_WOOD:  
								{
									zCSoundFX* sfx = zsound->LoadSoundFX( zSTRING("DrawSound") + "_WO" + ".wav" );
									if (sfx) {
										zCSoundSystem::zTSound3DParams params;
										params.SetDefaults();
										params.pitchOffset = GetVoicePitch();
										zsound->PlaySound3D(sfx,this,2,&params);
									}
									zRELEASE(sfx);		// [EDENFELD] Leakfix
								}break;
							case SND_MAT_METAL:
								{
									zCSoundFX* sfx = zsound->LoadSoundFX( zSTRING("DrawSound") + "_ME" + ".wav" );
									if (sfx) {
										zCSoundSystem::zTSound3DParams params;
										params.SetDefaults();
										params.pitchOffset = GetVoicePitch();
										zsound->PlaySound3D(sfx,this,2,&params);
									}
                                    zRELEASE(sfx);	//  [Moos] Leakfix
								}break;
							default :	zERR_WARNING("U: NPC: DEF_DRAWSOUND : No soundmaterial found.");
										break;
					}
				} else {
					zERR_WARNING("U: NPC: DEF_DRAWSOUND : No weapon found.");
				}
			} else if (ev->tagString=="DEF_UNDRAWSOUND") {
				// **************************************
				// Sound beim ziehen der waffe abspielen!!!
				// **************************************
				oCItem*		item = GetSlotItem(NPC_NODE_RIGHTHAND);
				if (!item)	item = GetSlotItem(NPC_NODE_SWORD);
				if (!item)	item = GetSlotItem(NPC_NODE_LONGSWORD);
				if (!item)	item = GetSlotItem(NPC_NODE_LEFTHAND);
				if( item ) 
				{
					switch( item->GetSoundMaterial() )
					{
							case SND_MAT_WOOD:  
								{
									zCSoundFX* sfx = zsound->LoadSoundFX( zSTRING("UnDrawSound") + "_WO" + ".wav" );
									if (sfx) {
										zCSoundSystem::zTSound3DParams params;
										params.SetDefaults();
										params.pitchOffset = GetVoicePitch();
										zsound->PlaySound3D(sfx,this,2,&params);
									} 
									zRELEASE(sfx);
								}break;
							case SND_MAT_METAL:
								{
									zCSoundFX* sfx = zsound->LoadSoundFX( zSTRING("UnDrawSound") + "_ME" + ".wav" );
									if (sfx) {
										zCSoundSystem::zTSound3DParams params;
										params.SetDefaults();
										params.pitchOffset = GetVoicePitch();
										zsound->PlaySound3D(sfx,this,2,&params);
									} 
									zRELEASE(sfx);
								}break;
							default :	zERR_WARNING("U: NPC: DEF_UNDRAWSOUND : No soundmaterial found.");
										break;
					}
				} else {
					zERR_WARNING("U: NPC: DEF_UNDRAWSOUND : No weapon found.");				
				}

			} else if (ev->tagString=="DEF_DRAWTORCH") {
			
			}
		} 
	}
	return TRUE;
}

zBOOL oCNpc :: DoModelSwapMesh(const zSTRING &node1, const zSTRING &node2)
{
	// G�ltiger Slot-Wechsel ?
	if (node1.IsEmpty() || node2.IsEmpty()) return FALSE;
	
	// Hier passiert jetzt auch die logische Abfrage 
	// -> logischer Wechsel in den Waffen/Normalmodus
	if ((node1==NPC_NODE_LEFTHAND) || (node1==NPC_NODE_RIGHTHAND) ||
		(node2==NPC_NODE_LEFTHAND) || (node2==NPC_NODE_RIGHTHAND)) {
		// Auch wirklich wechsel in Waffenmode
        oCAniCtrl_Human* ac = GetAnictrl();
		int nr = ac->wmode_selected;
		if (GetWeaponMode()!=nr) {
			if (nr != NPC_WEAPON_NONE) {
				// Waffe ziehen
				SetWeaponMode		(nr);
				ac -> SetFightAnis	(nr);
				ac -> SetWalkMode	(ac->GetWalkMode());
			} else {
				// Waffe wegstecken
				SetWeaponMode		(NPC_WEAPON_NONE);					
				ac -> SetFightAnis	(NPC_WEAPON_NONE);
				ac -> SetWalkMode	(ac->GetWalkMode());								
			}
		}
	} 

	// Slot Wechseln
	TNpcSlot* slot1	= GetInvSlot(node1);
	TNpcSlot* slot2 = GetInvSlot(node2);
	zBOOL inInv1	= slot1->inInventory;
	zBOOL inInv2	= slot2->inInventory;
	oCVob* vob1		= RemoveFromSlot(slot1, TRUE, FALSE);
	oCVob* vob2		= RemoveFromSlot(slot2, TRUE, FALSE);
	PutInSlot (slot1,vob2,inInv2);
	PutInSlot (slot2,vob1,inInv1);
	return TRUE;
}

zBOOL oCNpc :: HasMunitionInHand(oCItem* weapon)
{
	int index = weapon->GetMunitionInstance();
	// Rechts ?
	oCItem* item = GetSlotItem(NPC_NODE_RIGHTHAND);
	if (item && (item->GetInstance()==index)) return TRUE;
	// Links
	item = GetSlotItem(NPC_NODE_LEFTHAND);
	return (item && (item->GetInstance()==index));
}

oCItem* oCNpc :: DoInsertMunition(const zSTRING& hand)
{
	oCItem* arrow	= NULL;
	oCItem* weapon	= GetWeapon();
	if (!weapon) return NULL;

	if (!HasMunitionInHand(weapon)) {
		zBOOL inmove = GetInMovement();
		if (inmove)	EndMovement();
		zSTRING node = hand;

		// Nur Hand erlaubt
		if ((node!=NPC_NODE_LEFTHAND) && (node!=NPC_NODE_RIGHTHAND)) return NULL;
		if (IsSlotFree(node)) {
			// Gegenstand erzeugen oder aus Inventory nehmen ?
			if (weapon->HasFlag(ITM_FLAG_CREATEAMMO)) 
				arrow = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,weapon->GetMunitionInstance());
			else
				arrow = RemoveFromInv(weapon->GetMunitionInstance());

			if (weapon && arrow) 
			{
				if (arrow && arrow->GetEffect()) arrow->GetEffect()->SetLevel(1,TRUE);

				// Damage dem arrow �bergeben
				weapon-> CopyDamage( arrow );
//				arrow -> damage			= weapon -> Get
//				arrow -> damageTotal	= weapon -> GetFullDamage ();
//				arrow -> damageTypes	= weapon -> GetDamageTypes();
				PutInSlot(node,arrow);								
			}
		}
		if (inmove)	BeginMovement();
	}		
	return arrow;
}

void oCNpc :: DoRemoveMunition()
{
	oCItem* weapon = GetWeapon();
	if (!weapon) return;

	int index = weapon->GetMunitionInstance();
	// Rechts ?
	oCItem* item = GetSlotItem(NPC_NODE_RIGHTHAND);
	if (item && (item->GetInstance()==index)) {
		item = (oCItem*) RemoveFromSlot (NPC_NODE_RIGHTHAND);
		if (weapon->HasFlag(ITM_FLAG_CREATEAMMO))	item->Release();
		else										PutInInv (item);
	}
	// Links
	item = GetSlotItem(NPC_NODE_LEFTHAND);
	if (item && (item->GetInstance()==index)) {
		item = (oCItem*) RemoveFromSlot (NPC_NODE_LEFTHAND);
		if (weapon->HasFlag(ITM_FLAG_CREATEAMMO))	item->Release();
		else										PutInInv (item);
	}
}

zBOOL oCNpc :: DoShootArrow(zBOOL autoaim)
{
	if ((GetWeaponMode()==NPC_WEAPON_BOW)  && !HasMunitionInHand(GetWeapon()))	return FALSE; else
	if ((GetWeaponMode()==NPC_WEAPON_CBOW) && !HasMunitionInHand(GetWeapon()))	return FALSE;

	// Bolzen holen
	oCItem* bolt = NULL;
	if (GetWeaponMode()==NPC_WEAPON_BOW) {
		bolt = (oCItem*) RemoveFromSlot(NPC_NODE_RIGHTHAND,FALSE, FALSE);
	} else if (GetWeaponMode()==NPC_WEAPON_CBOW) {
		bolt = (oCItem*) RemoveFromSlot(NPC_NODE_LEFTHAND,FALSE, FALSE);
	}
	if (!bolt) return FALSE;
	
	// Bolt einf�gen
	bolt -> SetSleeping			(TRUE);
	if (!bolt->RegisteredInWorld()) GetHomeWorld() -> AddVob(bolt);

	// AI dranh�ngen
	oCAIArrow *aiArrow = zNEW	(oCAIArrow);
	bolt -> SetAICallback		(aiArrow);
	bolt -> SetVobName			("Pfeil von NSC" + GetName());
	
	// AI init
	if (autoaim) {
		if (enemy)				aiArrow -> SetupAIVob	(bolt, this, enemy);			else
		if (GetFocusVob())		aiArrow -> SetupAIVob	(bolt, this, GetFocusVob());	else
								aiArrow -> SetupAIVob	(bolt, this);
	} else {
		aiArrow	-> SetupAIVob	(bolt, this);
	}
	
	bolt -> SetSleeping			(FALSE);
	zRELEASE					(aiArrow);
	return TRUE;
}


/* ----------------------------------------------------------------------
	
	oCNpc::THisVobAddedToWorld()

	27.11.2000	[Moos]	
                Fackelfix vereinheitlicht

   ---------------------------------------------------------------------- */

zBOOL oCNpc :: DoTakeVob (zCVob *vob)
// F�ge Vob ins Inventory / Slot ein 
{
	if (!vob) return FALSE;

	oCItem* item = zDYNAMIC_CAST<oCItem>(vob);
	if (item) {
		if (!item -> RegisteredInWorld()) return FALSE;

		// Reset 'dropped by player' flag
		// (e.g. NPC takes dropped weapon)
		if (!this->IsSelfPlayer())
			item->ClearFlag(ITM_FLAG_DROPPED);

		// Falls Item - FokusVob ist, dieses clearen... (sonst bleibt Schrift noch kurz da)
		if (item==GetFocusVob()) SetFocusVob(NULL);

        zBOOL wasTree = SafeAddRef(item);	//  [Moos] Brennende-Fackel-Aufheb-Verschwind-Fix

		ogame->GetGameWorld()->DisableVob(item);
		//if (item -> HasFlag(ITM_FLAG_THROW))	SetRightHand	( item );
		
        // Argh! Fackel!
        if( item->GetObjectName() == S_ITLSTORCHBURNING && !GetLeftHand() )
        {
        	SetLeftHand(item);
		    SetTorchAni( TRUE );
		}
		else
		{
    		oCItem *newitem = PutInInv	( item );
			CheckForOwner(newitem);
		}

        SafeRelease(item, wasTree);	//  [Moos] Leakfix zum Verschwindfix

		return TRUE;
	} 
	
	oCNpc* npc = zDYNAMIC_CAST<oCNpc>(vob);
	if (npc) {		
		// MEATBUG : In rechte Hand
		if (npc -> GetTrueGuild()==NPC_GIL_MEATBUG) {
			npc	-> SetSleeping		(TRUE);
			npc	-> SetPhysicsEnabled(FALSE);
			npc	-> SetCollDetDyn	(FALSE);
			SetRightHand (npc);

		} else if (npc -> GetTrueGuild()==NPC_GIL_GOBBO) {
			npc	-> SetSleeping		(TRUE);
			npc	-> SetPhysicsEnabled(FALSE);
			npc	-> SetCollDetDyn	(FALSE);
			SetCarryVob	(npc);
			npc	-> SetAICallback	(NULL);
			npc	-> SetSleeping		(FALSE);
			npc	-> GetModel() -> StartAni("S_GOBGOT");
		}
		return TRUE;
	
	} 
	
	oCMOB* mob = zDYNAMIC_CAST<oCMOB>(vob);
	if (mob) {
		SetCarryVob	(vob);
		GetAnictrl() -> StopLookAtTarget();
		return TRUE;	
	}

	return FALSE;
}


/* ----------------------------------------------------------------------
	
	oCNpc::DoDropVob()

	27.11.2000	[Moos]	
                Fackelfix vereinheitlicht

   ---------------------------------------------------------------------- */

zBOOL oCNpc :: DoDropVob	(zCVob *vob)
// Entferne Vob aus Inventory und lasse es fallen
{
	if (!vob) return FALSE;

	// Schon in Welt, dann Position schnappen
	zVEC3 startPos;
	if (vob->GetHomeWorld()) {
		startPos = vob->GetPositionWorld();
	} else {
		startPos = GetTrafoModelNodeToWorld(NPC_NODE_RIGHTHAND).GetTranslation();
	}

    zBOOL wasTree = SafeAddRef(vob);	//  [Moos] Crashfix analog zu DoThrowVob

	if (vob->GetVobType()==zVOB_TYPE_ITEM) 
	{
		// Remove From Inventory + automatisches Unequippen ?
		oCItem* item = (oCItem*)vob;
		RemoveFromInv (item,item->GetAmount());
		// In der Hand ? dann diese L�schen ?
		if (GetLeftHand() ==vob) RemoveFromSlot	(NPC_NODE_LEFTHAND,FALSE, FALSE); else
		if (GetRightHand()==vob) RemoveFromSlot	(NPC_NODE_RIGHTHAND,FALSE, FALSE);

		SetItemEffectControledByModel(item, 0, FALSE);

		if(item->HasFlag(ITM_FLAG_ACTIVE)) 
		{
			//[EDENFELD] 1.09
			// Item Effects entfernen WENN Item aktiv war und nich nur so 
			// fixt einen Bug der sich darin �usserte, da� versehntlich zweimal die Itemboni beim 
			// Fallenlassen eines Item abgezogen werden konnten
			RemoveItemEffects(item);

			item->ClearFlag(ITM_FLAG_ACTIVE);
		}
		// Sign items dropped by player
		if (this->IsSelfPlayer())
			item->SetFlag(ITM_FLAG_DROPPED);
	}
	
	if (vob == GetCarryVob()) {
		SetCarryVob(NULL);
	}
	
	// immer die oCAIVobMove anschmeissen
	oCAIVobMove* ai = zDYNAMIC_CAST<oCAIVobMove>(vob->GetAI());
	if (!ai) {
		// neue AI bauen
		if (vob->GetAI()) vob->GetAI()->Release();
		vob->SetAI(ai = zNEW( oCAIVobMove() ));
		vob->GetAI()->Release();
	}

	// Und fallen lassen
	if (ai) ai->Init(vob,this,startPos,0,100,&trafoObjToWorld);

    SafeRelease(vob, wasTree);	//  [Moos] Crashfix analog zu DoThrowVob

	return TRUE;
}

/* ----------------------------------------------------------------------
	
	oCNpc::DoThrowVob()

	27.11.2000	[Moos]	
                Fackelfix vereinheitlicht

   ---------------------------------------------------------------------- */

zBOOL oCNpc :: DoThrowVob (zCVob *vob, zREAL dist)
{		
	oCVob* ovob = zDYNAMIC_CAST<oCVob>(vob);
	if (!ovob) return FALSE;
	
	// Wurfwinkel
	zREAL angle = 35.0f;

	// Schon in Welt, dann Position schnappen
	zVEC3 startPos;
	if (vob->GetHomeWorld()) {
		startPos = vob->GetPositionWorld();
	} else {
		startPos = GetTrafoModelNodeToWorld(NPC_NODE_RIGHTHAND).GetTranslation();
	}

    zBOOL wasTree = SafeAddRef(vob);	//  [Moos] Crashfix; beim werfen der Fackel wird sonst beim Entfernen aus der zCWorld der VobTree gel�scht

	if (zDYNAMIC_CAST<oCItem>(vob)) {
		// Remove From Inventory + automatisches Unequippen ?
		oCItem* item =	(oCItem*)vob;
		// In der Hand ? dann diese L�schen ?
		if (GetLeftHand() ==vob) RemoveFromSlot	(NPC_NODE_LEFTHAND,FALSE, FALSE);
		if (GetRightHand()==vob) RemoveFromSlot	(NPC_NODE_RIGHTHAND,FALSE, FALSE);
		else					 RemoveFromInv	(item,item->GetAmount());
	} 

	// Mobsis werden flacher geworfen
	if (zDYNAMIC_CAST<oCMOB>(vob)) angle = 20;
	
	if (vob == GetCarryVob()) {
		SetCarryVob(NULL);
	}
	
	// immer die oCAIVobMove anschmeissen
	oCAIVobMove* ai = ovob->GetAIVobMove();
	
	// Und los werfos 
	if (ai) ai->Init(vob,this,startPos,angle,dist,&trafoObjToWorld);

    SafeRelease(vob, wasTree);	//  [Moos] Leakfix zum Crashfix. Inzwischen ist die Fackel wieder in der Welt.

	return TRUE;
}

zBOOL oCNpc :: DoPutInInventory (oCItem* item)
{
	if (!item) return FALSE;
	PutInInv (item);
	return TRUE;
}

zBOOL oCNpc :: DoRemoveFromInventory (oCItem* item)
{
	if (!item) return FALSE;
	RemoveFromInv (item);
	return TRUE;
}

zBOOL oCNpc :: DoSetToFightMode (oCItem* weapon)
{
	if (!weapon) return FALSE;
	// Waffe wechseln, ohne Anis dazwischen 
	SetToFightMode	( weapon, FALSE );
	return TRUE;
}

zBOOL oCNpc :: DoExchangeTorch ()
{
	oCVob *right	= GetRightHand();
	oCVob *left		= GetLeftHand();	
	if (left)  RemoveFromSlot(NPC_NODE_LEFTHAND);
	if (right) RemoveFromSlot(NPC_NODE_RIGHTHAND);
	SetRightHand(left);
	SetLeftHand	(right);
	return TRUE;
}

void oCNpc :: Pack (zCBuffer& buffer)
{
	// numActiveAnis als Header eintragen
//	buffer.Write(&ai_state,sizeof(ai_state));
	buffer.Write(&fmode,sizeof(fmode));
	buffer.Write(&attribute,sizeof(attribute));
	buffer.Write(&script_aiprio,sizeof(script_aiprio));
	int walkmode = GetAnictrl() -> GetWalkMode();
	buffer.Write(&walkmode,sizeof(walkmode));
	// Enemy �bertragen
	zTVobID enemyid = 0;
	if (enemy) enemyid = enemy -> GetVobID();
	buffer.Write(&enemyid,sizeof(enemyid));
}

void oCNpc :: Unpack    (zCBuffer& buffer)
{
	int walkmode;
//	buffer.Read(&ai_state,sizeof(ai_state));
	buffer.Read(&fmode,sizeof(fmode));
	buffer.Read(&attribute,sizeof(attribute));      
	buffer.Read(&script_aiprio,sizeof(script_aiprio));
	buffer.Read(&walkmode,sizeof(walkmode));
	if (walkmode!=GetAnictrl()->GetWalkMode()) GetAnictrl()->SetWalkMode(walkmode);	
	// Enemy
	zTVobID enemyid;
	buffer.Read(&enemyid,sizeof(enemyid));
    if (enemyid>0) enemy = (oCNpc*) ogame->GetGameWorld()->SearchVobByID(enemyid);
}

// ********************************************
// Spezielle Skript-Funktionen
// ********************************************

zBOOL oCNpc :: IsInFightMode_S	( int id )
{
	int wm = GetWeaponMode();
	if (id==NPC_WEAPON_DAG)		return ((wm>=NPC_WEAPON_DAG) && (wm< NPC_WEAPON_BOW));
	if (id==NPC_WEAPON_NONE)	return ( wm==NPC_WEAPON_NONE);
	if (id==NPC_WEAPON_FIST)	return ( wm==NPC_WEAPON_FIST);
	if (id==NPC_WEAPON_BOW)		return ((wm==NPC_WEAPON_BOW) || (wm==NPC_WEAPON_CBOW));
	if (id==NPC_WEAPON_MAG)		return (wm==NPC_WEAPON_MAG);

	return FALSE;
};

zBOOL oCNpc :: IsAiming_S ( oCNpc* target )
// Zielt this auf target ?
// 
{
	// Im Magiemodus - b�ser Zauberspruch und am aimen
	if (GetFocusNpc()!=target) return FALSE;
	
	if (GetWeaponMode()>=NPC_WEAPON_MAG) {
		oCSpell* spell		= NULL;
		oCMag_Book* book		= GetSpellBook();
		if (book) spell		= book -> GetSelectedSpell();
		if (spell && /*spell->InCast() &&*/ (spell->GetCategory()==SPL_CAT_BAD)) {
			// Spruch ist b�se, und es wird geaimt.
			return TRUE;
		}
	}

	return (GetAnictrl()->IsAiming());
};

// *************************************
// Statics / Helpers
// *************************************

const int PLAYER_NAME_MAX = 6;
const zSTRING player_name[PLAYER_NAME_MAX] = {	
		"",
		"PC_HERO",
		"PC_FIGHTER",
		"PC_THIEF",
		"PC_MAGE",
		"PC_PSIONIC"
};

zSTRING oCNpc :: GetInstanceName ()
{
	int typ,ele;
	return parser.GetSymbolInfo(instanz,typ,ele);
}

zBOOL oCNpc :: GetScriptInstance	(zSTRING* &scriptInstanceName, int &scriptInstanceIndex)
{
	// returns name/index, as available
	// Achtung : dynamisches Objekt !
	zCPar_Symbol* sym = parser.GetSymbol(instanz);
	if (sym) scriptInstanceName = &sym->name;
	else	 scriptInstanceName = NULL;
	scriptInstanceIndex			= instanz;
	return TRUE;
}
	
zBOOL oCNpc ::	SetByScriptInstance	(const zSTRING* scriptInstanceName, const int scriptInstanceIndex)
{
	// use 'name' or 'index' exclusively, but not both
	if (scriptInstanceName) {
		InitByScript(parser.GetIndex(*scriptInstanceName));
	} else {
		InitByScript(scriptInstanceIndex);
	}
	return TRUE;
}

zSTRING	oCNpc :: GetInstanceByID (int nr)
// Empty - not found
{
	if ((nr<0) || (nr>=PLAYER_NAME_MAX)) nr = 0;
	return player_name[nr];
}

int	oCNpc :: GetIDByInstance (const zSTRING &name)
// 0 - not found
{
	for (int i=0; i<PLAYER_NAME_MAX; i++) {
		if (player_name[i] == name) return i;
	};
	return 0;
}

// *************************************
// Enable / Disable
// *************************************

void oCNpc :: Disable()
{
    ClearVobList();

 	if (GetHomeWorld())
        AvoidShrink();      // [Moos] sorge daf�r, dass er ein Visual hat.

	if (GetNpcAIDisabled()) return;

	if (!IsAPlayer()) {

		// auf jeden fall alle laufenden effekte beenden
		for (int i=0; i<effectList.GetNum(); i++)
		{
			oCVisualFX* newFX = effectList[i];
			effectList.Remove(newFX);
			newFX->Kill();
			zRELEASE_ACCT_NONULL(newFX);
			--i;
		}

		Interrupt			();	// Hier Abmelden von Item und Mobsikram

		if (GetHomeWorld())
            ogame->GetGameWorld()->DisableVob(this);

		ClearPerceptionLists();
		SetSleeping			(TRUE);
		state.CloseCutscenes();		
	//	DeleteHumanAI		();
		zERR_MESSAGE		(2,0,"U: NPC: AI:Removed NPC "+GetName()+" / "+GetInstanceName());
	}
}


/*--------------------------------------------------------------------------

    void oCNpc :: Enable(zVEC3& pos)

    26-Sept-00	[SPECKELS]
				Standardmaessiges Equipppen von Waffen deaktiviert
				(kann laut Mike auch auf Scriptebene erledigt werden)

--------------------------------------------------------------------------*/


void oCNpc :: Enable(zVEC3& pos)
{

    GetModel();  // [Moos] sorge daf�r, dass das Model VOR der Positionssuche da ist.

	// Logisch einf�gen
	if (!GetHomeWorld()) {
		ogame->GetGameWorld()->EnableVob(this);
	}


	// NSC schaltet auf Tagesablauf
	if (!GetNpcAIDisabled()) Interrupt();

	// Position setzen
	SetCollDet			(FALSE);
	SearchNpcPosition	(pos);				// Setzt H�he und checkt auf Platz.
	SetPositionWorld	(pos);
	SetCollDet			(TRUE);
	SetSleeping			(FALSE);

    // [Moos] Besorge einen neuen SpatialState
    ((zCCollObjectCharacter *)GetCollisionObject())->MarkSpatialStateAsUninited(TRUE);

	if (GetNpcAIDisabled()) return;

	if (!GetHumanAI()) InitHumanAI();

	// Standardmaessig Waffen equippen	
	if (!IsAPlayer() && !IsDead() && !GetCarryVob()) 
	{
		// Immer im Normalmodus inserten, ausser bei Monstern
		if (!IsMonster()) 
		{
			// Slots leeren
			SetWeaponMode	(NPC_WEAPON_NONE);
			oCItem* item	= zDYNAMIC_CAST<oCItem>(RemoveFromSlot (NPC_NODE_RIGHTHAND,FALSE));
			if (item) {
				if (item->HasFlag(ITM_FLAG_ACTIVE)) 
				{
					UnequipItem	(item);
					Equip		(item);
				}
				else 
				{
					PutInInv(item);
				}
			}
			item			= zDYNAMIC_CAST<oCItem>(RemoveFromSlot (NPC_NODE_LEFTHAND,FALSE));
			if (item) {
				if (item->HasFlag(ITM_FLAG_ACTIVE)) {
					UnequipItem	(item);
					Equip		(item);
				} else {
					PutInInv(item);
				}
			}
		}	
		// Nur wenn beide Haende frei sind.
		if (!GetSlotVob(NPC_NODE_RIGHTHAND) && !GetSlotVob(NPC_NODE_LEFTHAND))
		{
			EquipBestWeapon		(ITM_CAT_NF);
			EquipBestWeapon		(ITM_CAT_FF);
		}
	}	

	// StartAni starten.
	if (GetModel()) {
		// Alles wech....
		GetModel()->StopAnisLayerRange(1,256);

		if (IsDead()) {

			GetModel()->StartAni("S_DEAD");
		
		} else {
			// Waffenmodus setzen
			if (GetWeaponMode()!=NPC_WEAPON_NONE) GetHumanAI()->SetFightAnis(GetWeaponMode());
			// Walkmode setzen...
			GetHumanAI() -> SetWalkMode		(ANI_WALKMODE_RUN);
			// StandAni starten
			GetHumanAI() -> SearchStandAni	(TRUE);
		}		
	}

	// Derzeitigen AI-Zustand aktivieren.
	Interrupt();
	ClearEM();
	state.StartRtnState	(TRUE);	

	zERR_MESSAGE(2,0,"U: AI: Inserted NPC : "+GetName()+" / "+GetInstanceName());
	AddEffect(effect);

	// [BENDLIN] _nach_ EquipBestWeapon verschoben
	parser.SetInstance	("SELF",this);
	parser.CallFunc(zSTRING("B_REFRESHATINSERT"));
}

void oCNpc :: ClearEM()
// Kapselung : Clear-EventManager....
// um auf Befehle zu reagieren, die sonst fehlerhaft beendet wuerden
{
	GetEM()->Clear();
	// EV_ROBUSTTRACE....
	if (GetAnictrl()) {
		if (GetAnictrl()->IsWalking() || (GetAnictrl()->GetActionMode()==ANI_ACTION_SWIM) || (GetAnictrl()->GetActionMode()==ANI_ACTION_DIVE)) {
			GetAnictrl()->_Stand();
		}
		GetAnictrl()->StopTurnAnis();
	}
	lastLookMsg		= NULL;
	lastPointMsg	= NULL;
}

// *************************************
// Archive / Unarchive
// *************************************

void oCNpc :: Archive (zCArchiver &arc)
{
    int i;

	// TMP : For debugging
	// Saving a reference of a player during levelchange is not allowed !
	if (dontArchiveThisNpc==this) {
	
		zERR_FAULT("U: NPC: Object tries to save reference of player during levelchange. This is not allowed.");
	
	}
    
	// [MOOS] speichere das Visual zwischen und l�sche es aus der Datenstruktur. Es muss nicht gespeichert werden.
    zCVisual *vis = GetVisual();
    if (vis) vis->AddRef();
    SetVisual(NULL);

	oCVob :: Archive(arc);

    SetVisual(vis);	//  restauriere das alte Visual
    zRELEASE(vis);

	// Write Instance Name
	zCPar_Symbol* sym = parser.GetSymbol(GetInstance());
	zSTRING s;
	if (!sym) {
		zERR_WARNING("U: NPC:Save:Instance not found : "+GetInstanceName());
		// Patch 1.08 : Hier nicht mehr "(Error)" speichern, sondern den Vobnamen,
		// der kann noch den richtigen Instanznamen beinhalten.
		s = GetVobName();
	} else
		s = sym->name;
	
	arc.WriteString	("npcInstance",s);

	// Nur beim SaveGame ????
	if (!arc.InSaveGame()) return;
		
	// *********************************************
	// Aus den Skripten heraus wird initialisiert :
	// Die AI-Funktionen
	// Visual-Vars
	// Fighting Ranges
	// *********************************************


	////////////////////////////////////////////////////////////////////////////

    // model properties
    arc.WriteVec3    ("modelScale"   ,model_scale);
    arc.WriteFloat   ("modelFatness" ,model_fatness);

    arc.WriteInt     ("numOverlays"  ,activeOverlays.GetNum());
    for (i=activeOverlays.GetNum()-1; i>=0; i--)
        arc.WriteString("overlay", activeOverlays[i]);

	if (arc.InProperties()) 
	{
		arc.WriteGroupBegin("scripted");
	};

	// alles ver�nderliche jetzt dr�berlegen
	arc.WriteInt	("flags"		,variousFlags);
	arc.WriteInt	("guild"		,guild);
	arc.WriteInt	("guildTrue"	,guildTrue);
	arc.WriteInt	("level"		,level);
	arc.WriteInt	("xp"			,experience_points);
	arc.WriteInt	("xpnl"			,experience_points_next_level);
	arc.WriteInt	("lp"			,learn_points);

	arc.WriteInt	("numTalents"	,talents.GetNumInList());
	for (i=0;i<talents.GetNumInList();i++)
	{
		arc.WriteObject(talents[i]);
	}


	arc.WriteInt	("fightTactic"	,fighttactic);
	arc.WriteInt	("fightMode"	,fmode);

	// Overlays
	arc.WriteBool	("wounded"			,overlay_wounded);
	arc.WriteBool	("mad"				,mad);
	arc.WriteInt	("madTime"			,mad_heal);

	if (arc.InProperties()) 
	{
		arc.WriteGroupEnd("scripted");
		return;
	}

	////////////////////////////////////////////////////////////////////////////

	// Player-Flag
	zBOOL isPlayer = (this==oCNpc::player);
	arc.WriteBool ("player"	,isPlayer);

	// Attribute
	for (i=0; i<NPC_ATR_MAX; i++) 
	{
		s = "atr"+zSTRING(i);
		arc.WriteInt(s.ToChar(),attribute[i]);
	}

	// Hitchance
	for (i=1; i<NPC_HITCHANCE_MAX; i++) 
	{
		s = "hc"+zSTRING(i);
		arc.WriteInt(s.ToChar(),hitChance[i]);
	}

	// Missions
	for (i=0; i<NPC_MIS_MAX; i++) {
		s = "mission"+zSTRING(i);
		arc.WriteInt(s.ToChar()		,mission[i]);
	}
	// Scriptvars
	zSTRING scriptName;
	if (startAIState>0) {
		zCPar_Symbol* sym = parser.GetSymbol(startAIState);
		if (sym) scriptName = sym->name;
	}
	arc.WriteString	("startAIState" ,scriptName);
	arc.WriteRaw	("scriptVars"	,&aiscriptvars	,sizeof(aiscriptvars));
	arc.WriteString	("scriptWp"		,wpname);
			
	// Attitude
	arc.WriteInt	("attitude"		,attitude);
	arc.WriteInt	("tmpAttitude"	,tmp_attitude);
	// Internals
	arc.WriteInt	("nameNr"		,namenr);
	// Spells
    int tmp = spells;
	arc.WriteRaw	("spells"		,&tmp		,sizeof(tmp));

	//News
	knownNews.Archive(arc);

	// Vobs
	arc.WriteObject	("carryVob"		,carry_vob);	

	// Enemy speichern - ausser wenn's der Player ist (nicht noetig).
	if (IsSelfPlayer()) SetEnemy(NULL);
	oCNpc* writeEnemy = NULL;
	if (enemy != dontArchiveThisNpc)	writeEnemy = enemy;
	// Referenz freigeben, wird nicht mehr gebraucht.
	else								SetEnemy(NULL);
	arc.WriteObject ("enemy"			,writeEnemy);

	// Others
	arc.WriteBool	("moveLock"			,movlock);

	// *********
	// Weiteres
	// *********
	// b) Inventory
	inventory2.Archive (arc);
	
	// a) Inventory - Slots
	int numInv	= invSlot.GetNumInList();	
	arc.WriteInt	("numInvSlots"		,numInv);
	for (i=0; i<numInv; i++) {

		zCVob*	tmpVob	= invSlot[i]->Vob();
		zBOOL	used	= (tmpVob!=NULL);
		if (used) {
			// [Ulf] : InteractItems werden nicht mit abgespeichert, da beim Laden diese Aktion eh verpufft.
			// [EDENFELD] 1.25: und fackeln werden auch nicht mit abgespeichtert -> zu viele Probleme
			used = !((GetInteractItem()==tmpVob) || (invSlot[i]->tmpLevel>0));
			if (tmpVob->GetObjectName()==S_ITLSTORCHBURNING) used = FALSE;

			if (!used) zERR_WARNING("U: NPC: InteractItem "+tmpVob->GetObjectName()+" not saved.");
		}

		arc.WriteBool	("used"			,used);
		arc.WriteString	("name"			,invSlot[i]->name);
		if (used) {
			arc.WriteObject	("vob",		invSlot[i]->Vob());
			arc.WriteBool	("inInv",	invSlot[i]->inInventory);
			// arc.WriteBool	("tmpLevel",invSlot[i]->tmpLevel);	//  TmpLevel ist eh immer "0"
		}

	}

	// c) Perception
	state.Archive(arc);

	// d) Daily Routine - Kann durch ExchangeRoutine veraendert werden.
	zSTRING rtnName;
	sym	= parser.GetSymbol(daily_routine);
	if (sym) rtnName = sym->name;
	arc.WriteString	("curRoutine",rtnName);

	// e) Spawning
	arc.WriteBool	("respawn"		,respawnOn);
	arc.WriteInt	("respawnTime"	,spawnDelay);

	// f) Protection Values
	arc.WriteRaw	("protection"	,protection,sizeof(protection));

	// bodystate override
	arc.WriteInt	("bsInterruptableOverride"		,this->bodyStateInterruptableOverride);

	// neu: npcType auch mit abspeichern
	arc.WriteInt	("npcType",		 npcType);

	// [BENDLIN] damit er sich merkt, wieviel Mana f�r den Spruch auf der Hand investiert werden soll
	arc.WriteInt	("spellMana",	spellMana);
};

void oCNpc :: Unarchive	(zCArchiver &arc)
{
	static int npcCount = 0;
	
	oCVob :: Unarchive(arc);

	// Get Instance Name
	zSTRING name;
	arc.ReadString	("npcInstance",name);
	int		index	= parser.GetIndex	(name);

	if (index >= 0) {
		// Inventory darf nicht bei SaveGame aus Skript erstellt werden.
		InitByScript	(index,arc.InSaveGame());
	} else {
		SetAICallback(NULL);
		instanz = -1;
		zERR_FAULT("U: NPC:Load:Instance not found : Vobname :" + GetVobName() + "/ Scriptinstance:" + name +". Correct instancename or remove Npc !");
	};

	if (!arc.InSaveGame()) return;

/*	if (GetVobName()=="SFB_1040_SCHUERFER") {
		zERR_WARNING("U: NPC: NpcCOunt :"+zSTRING(npcCount));
	}
*/
	////////////////////////////////////////////////////////////////////////////

    // model properties
    arc.ReadVec3    ("modelScale"   ,model_scale);
    arc.ReadFloat   ("modelFatness" ,model_fatness);

    int num_overlays=0;
    zSTRING overlayName;
	arc.ReadInt     ("numOverlays"  ,num_overlays);
    for (;num_overlays>0; num_overlays--) {
		
		// Patch 1.07 : [Wohlers] : 13.03.01 : Codechange
		// Safety : Always uppern, da sonst doppelte Eintraege moeglich waeren.
		// Alte Savegames kompatibel halten -> Eintraege in Uppercase und nicht doppelt !
		overlayName = arc.ReadString("overlay");
		overlayName.Upper();

		// [EDENFELD] FIXME HACK: Torchanis werden ignoriert
		const zBOOL torchOverlay = (overlayName.Length()>6) && (overlayName[7]=='T') && (overlayName.Search("HUMANS_TORCH")!=-1);

		if (!activeOverlays.IsInList(overlayName) && !torchOverlay) activeOverlays.Insert(overlayName);
		// [Wohlers] : CodeChange End
	}

    if (GetAI())
        AvoidShrink();  //[Moos] Das hier ist der fr�hestm�gliche Zeitpunkt, das Model zu restaurieren.

	int nTemp;
	// alles ver�nderliche jetzt dr�berlegen
	arc.ReadInt		("flags"		,variousFlags);
	arc.ReadInt		("guild"		,guild);
//	arc.ReadInt		("guildTrue"	,guildTrue);
	arc.ReadInt		("guildTrue"	,nTemp);    guildTrue                       = nTemp;
	arc.ReadInt		("level"		,level);
	arc.ReadInt		("xp"			,nTemp);	experience_points				= nTemp;
	arc.ReadInt		("xpnl"			,nTemp);	experience_points_next_level	= nTemp;
	arc.ReadInt		("lp"			,nTemp);	learn_points					= nTemp;
	
	// Talents
	int numTalents=0;	
	arc.ReadInt		("numTalents"	,numTalents);
	if (numTalents>talents.GetNumInList()) zERR_WARNING("U: NPC: Found more talents in archive than used in game!");
	if (numTalents<talents.GetNumInList()) zERR_WARNING("U: NPC: Found less talents in archive than used in game!");
	numTalents = zMin(numTalents,talents.GetNumInList());

	oCNpcTalent* talent;
	for (int i=0;i<numTalents;i++)
	{
		zRELEASE(talents[i]);

		talent = zDYNAMIC_CAST<oCNpcTalent>(arc.ReadObject0());				
		if (talent)
		{
			// [EDENFELD] 1.27a Workaround f�r korrupte Savegames 
			if (talent->GetTalentSkill()>100) 
			{	
				zERR_WARNING("C: corrupt archive found: npc " + GetName() + " has an illegal talent skill for index: " + zSTRING(i));
				talent->SetTalentSkill(1);
			}
			SetTalentSkill(i,talent->GetTalentSkill());
			SetTalentValue(i,talent->GetTalentValue());		
		}
		zRELEASE(talent);
	}

	arc.ReadInt		("fightTactic"	,fighttactic);
	arc.ReadInt		("fightMode"	,fmode);

	// Overlays
//	arc.ReadBool	("wounded"			,overlay_wounded);
//	arc.ReadBool	("mad"				,mad);
//	arc.ReadInt		("madTime"			,mad_heal);

	arc.ReadBool	("wounded"			,nTemp);   overlay_wounded              = nTemp;
	arc.ReadBool	("mad"				,nTemp);   mad                          = nTemp;
	arc.ReadInt		("madTime"			,nTemp);   mad_heal                     = nTemp;

	//arc.ReadFloat	("healTime"			,hpHealTime);
	//arc.ReadFloat	("manaTime"			,manaHealTime);

	if (arc.InProperties()) return;

	////////////////////////////////////////////////////////////////////////////

	// Player-Flag
	zBOOL isPlayer;
	arc.ReadBool	("player"	,isPlayer);

	// Attribute
	zSTRING s;
	for (i=0; i<NPC_ATR_MAX; i++) 
	{
		s = "atr"+zSTRING(i);
		arc.ReadInt	(s.ToChar()		,attribute[i]);
	}

	// Hitchance
	for (i=1; i<NPC_HITCHANCE_MAX; i++) 
	{
		s = "hc"+zSTRING(i);
		arc.ReadInt(s.ToChar(),hitChance[i]);
	}
	
	// Missions
	for (i=0; i<NPC_MIS_MAX; i++) 
	{
		s = "mission"+zSTRING(i);
		arc.ReadInt	(s.ToChar()		,mission[i]);
	}

	// Scriptvars
	zSTRING scriptName;
	arc.ReadString	("startAIState" ,scriptName);
	if (!scriptName.IsEmpty()) {
		startAIState = parser.GetIndex(scriptName);
		if (startAIState<0) zERR_FAULT("U: NPC: Cannot reinitialize AI-State :"+scriptName+" / "+GetInstanceName());	
	}		

	arc.ReadRaw		("scriptVars"	,&aiscriptvars	,sizeof(aiscriptvars));
	arc.ReadString	("scriptWp"		,wpname);

	// Attitude
	arc.ReadInt		("attitude"		,attitude);
	arc.ReadInt		("tmpAttitude"	,tmp_attitude);
	// Internals
	arc.ReadInt		("nameNr"		,namenr);
	// Spells
	arc.ReadRaw		("spells"		,&nTemp		,sizeof(nTemp));  spells = nTemp;

	//News
	knownNews.Unarchive(arc);

	// Vobs
	carry_vob	= (zCVob*) arc.ReadObject1	("carryVob");
	
	// Restore Enemy
	oCNpc* tmpEnemy = (oCNpc*)arc.ReadObject2	("enemy",enemy);
	SetEnemy (tmpEnemy); 
	zRELEASE (tmpEnemy);

	// Others
//	arc.ReadBool	("moveLock"			,movlock);
	arc.ReadBool	("moveLock"			,nTemp);     movlock = nTemp;

	// Weiteres
	// b) Inventory
	inventory2.ClearInventory	();
	inventory2.Unarchive		(arc);

	// a) Inventory - Slots leeren
	for  (int n=0; n<invSlot.GetNumInList(); n++){
//        zRELEASE(invSlot[n]->vob);	//  [Moos] Leakfix; eigentlich sollte man das Ding noch aus der Welt entfernen, aber unten wird es sowieso wieder geladen ; [Moos] das macht jetzt der Slot-Destruktor
        delete (invSlot[n]);
     }

	invSlot.DeleteList();

	// und wieder auff�llen
	zSTRING invName;
	zBOOL	used;
	int		numInv;
	
	arc.ReadInt ("numInvSlots" ,numInv);
	for (i=0; i<numInv; i++) {		
		arc.ReadBool		("used"		,used);
		arc.ReadString		("name"		,invName);
		CreateInvSlot		(invName);
		if (used) 
		{
            oCVob *vob=NULL;
			vob = (oCVob*)arc.ReadObject2 ("vob"	,vob);  // [Moos] Neue SlotVob-Logik
            invSlot[i]->SetVob(vob);

			// [EDENFELD] 1.25 Fackeln gibt es nicht mehr im Archiv
			//if (vob && vob->GetObjectName() == S_ITLSTORCHBURNING && GetSlotVob(NPC_NODE_LEFTHAND) == vob)
			//	SetTorchAni(TRUE,FALSE);

            zRELEASE(vob);  

			arc.ReadBool	("inInv"	,invSlot[i]->inInventory);
            
	        if (invSlot[i]->inInventory) 
			{	
				oCItem* item = zDYNAMIC_CAST<oCItem>(invSlot[i]->Vob());
				if (item)
				{
					if (!item->HasFlag(ITM_FLAG_ACTIVE)) 
					{
						item->SetFlag(ITM_FLAG_ACTIVE);
						item->CreateVisual();
						// graphisch einfuegen.
						if (GetVisual())
						{
	    					zCModelNodeInst* node	= GetModel() -> SearchNode( invName );
							// [EDENFELD] An dieser Stelle wird das Item nur noch vom Modelanimationssystem
							// gerendert
							if (node) GetModel() -> SetNodeVisual( node, item->GetVisual() );
			
							if (invSlot[i]->Vob()) 
							{
								this->SetItemEffectControledByModel(item, node, TRUE);
							}
						}
					}
				}
			}							
//			if (item) {
//				PutInInv(zDYNAMIC_CAST<oCItem>(invSlot[i]->vob));	//  [Moos] das ist auch noch zu erledigen
//			}
		}
	}

    if (carry_vob) carry_vob->Release();	//  [Moos] Leakfix; beim Laden des carry_vobs wurde ein addref gemacht, das normalerweise nicht gemacht wird.

	// c) Perception ( fehlt )
	state.Unarchive(arc);
	
	// d) Human_AI
	oCAIHuman *ai = zDYNAMIC_CAST<oCAIHuman>(GetAICallback());
	if (ai) 
	{
        AvoidShrink();    // [Moos] sorge daf�r, dass die AI ein Model zum Spielen hat
        zERR_ASSERT(GetModel() == human_ai->GetModel());

		// Init AI
        if (ai && !human_ai){
    		ai -> AddRef			();
            human_ai = ai;
        }

		human_ai -> SetActionMode	(human_ai->GetActionMode());
		human_ai -> SetFightAnis	(this    ->GetWeaponMode());
		human_ai -> SetWalkMode		(human_ai->GetWalkMode  ());
		human_ai -> SearchStandAni	(TRUE);
	}

	if (isPlayer && !oCNpc::player) {
		// Gibt's den Spieler nocht nicht, diesen �bernehmen
		oCNpc::player = this;
	}
	
	// d) Daily Routine - Kann durch ExchangeRoutine veraendert werden.
	zSTRING rtnName;
	arc.ReadString	("curRoutine",rtnName);
	int rtnIndex	= parser.GetIndex (rtnName);
	if ((rtnIndex>=0) && (rtnIndex!=daily_routine)) {
		state.ChangeRoutine(rtnIndex);
	}

	// e) Spawning
//	arc.ReadBool	("respawn"		,respawnOn);
	arc.ReadBool	("respawn"		,nTemp);          respawnOn  = nTemp;
	arc.ReadInt		("respawnTime"	,spawnDelay);

	// f) Protection Values
	arc.ReadRaw		("protection"	,protection		,sizeof(protection));

	arc.ReadInt		("bsInterruptableOverride"		,this->bodyStateInterruptableOverride);

	// neu: npcType auch mit laden
	arc.ReadInt		("npcType",		 npcType);

	// [BENDLIN] damit er sich merkt, wieviel Mana f�r den Spruch auf der Hand investiert werden soll
	arc.ReadInt		("spellMana",	spellMana);

    if (GetVisual())   InitModel();	               // [Moos] damit eine R�stung GAAANZ sicher angezogen wird.
    if (GetHumanAI())  GetHumanAI()->Init(this);   // [Moos] erst hier sind alle Werte (gilde und so) bekannt, die die AI braucht.
	AddEffect(effect);
};

void oCNpc :: PreSaveGameProcessing()
// [Ulf] : InteractItems werden nicht mit abgespeichert, da beim Laden diese Aktion eh verpufft.
{
	oCWorld* world = NULL;

	int numInv = invSlot.GetNumInList();	
	for (int i=0; i<numInv; i++) {

		oCVob*	tmpVob	= invSlot[i]->Vob();
		zBOOL	used	= (tmpVob!=NULL);
		if (used) {
			used = !((GetInteractItem()==tmpVob) || (invSlot[i]->tmpLevel>0));
			if (!used && tmpVob && tmpVob->GetHomeWorld()) {
				
				zERR_WARNING("U: NPC: InteractItem "+tmpVob->GetObjectName()+" not saved.");

				// Aus Welt entfernen und ins Inv packen....
				tmpVob->AddRef();
				world = zDYNAMIC_CAST<oCWorld>(tmpVob->GetHomeWorld());
				if (world) world->DisableVob(tmpVob);
				else zERR_WARNING("U: NPC: Problem with removing Interact-Item !!!");

				// SlotInfo kopieren...
				TNpcSlot* tmpSlot		= zNEW(TNpcSlot());
				tmpSlot->inInventory	= invSlot[i]->inInventory;
				tmpSlot->name			= invSlot[i]->name;
				tmpSlot->tmpLevel		= invSlot[i]->tmpLevel;
				tmpSlot->SetVob			 (tmpVob);
				tmpSlot->Vob()			->AddRef();

				// Ins Inventory packen, damits mitgespeichert wird...
				if (invSlot[i]->tmpLevel==0) PutInInv(zDYNAMIC_CAST<oCItem>(tmpVob));
				
				// Und in TmpSlotData - Liste speichern
				tmpSlotList.Insert(tmpSlot);
		
				// wieder releasen....
				tmpVob->Release();
			}
		}
	}
};

void oCNpc :: PostSaveGameProcessing()
{
	TNpcSlot*	tmpSlot	= NULL;
	oCItem*		item	= NULL;
	int			numInv	= tmpSlotList.GetNumInList();	
	
	for (int i=0; i<numInv; i++) {

		tmpSlot = tmpSlotList[i];

		// 1) Ins Inventory gepackte Item wieder rausholen und wegwerfen, 
		//    falls Pointer'n anderer als gepspeichert ist. -> MultiSlotItem
		item = RemoveFromInv(tmpSlot->Vob()->GetInstanceName(),1);
		if (item != tmpSlot->Vob()) 
		{
			// komplett entfernen... Wird nicht gebraucht...
			ogame->GetWorld()->RemoveVob(item);
		};

		// In Slot packen....
		item = zDYNAMIC_CAST<oCItem>(RemoveFromSlot(tmpSlot->name,FALSE, FALSE));
		if (item!=tmpSlot->Vob()) {
			zERR_WARNING("U:NPC: SaveGameProcess : Interact-Item changed !");
		}
		PutInSlot(tmpSlot->name,tmpSlot->Vob(),tmpSlot->inInventory);
		
		// TmpLevel setzen...
		TNpcSlot* slot = GetInvSlot(tmpSlot->name);
		if (slot) slot->tmpLevel = tmpSlot->tmpLevel;
		
		// und Object wieder releasen...
		tmpSlot->Vob()->Release();
		tmpSlot->ClearVob();
	};
	
	tmpSlotList.DeleteList();
};

zBOOL oCNpc::AllowDiscardingOfSubtree(){
    return TRUE;
}

/*
void oCNpc :: SetRoute (zCRoute *rt)
{
	if (route) delete route;
	route = rt;
};
*/

// ********************************************
// Neues Inventory
// ********************************************

oCItem* oCNpc:: IdentifyMushroom(oCItem* item)
{
	int index;
	zRELEASE(item);

	if (zRand(2)==0) {
		index = parser.GetIndex("ITFOHONEYMUSHROOM");
	} else {
		index = parser.GetIndex("ITFOSTINKMUSHROOM");
	};
	
	oCItem* pilz = NULL;
	if (index>=0) pilz = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,index);
	return pilz;
}

void oCNpc :: IdentifyAllMushrooms()
{
	oCItem* pilz	= NULL;
	int index		= parser.GetIndex("ITFOMUSHROOM");
	if (index<0) return;
	do {	
		pilz = RemoveFromInv(index,1);
		if (pilz) PutInInv( IdentifyMushroom(pilz) );

	} while (pilz);
};

zBOOL oCNpc :: HasMissionItem()
// Inventory 
{
/*	oCItem* item = NULL;
	for (int i=0; i<INV_MAX; i++) {
		// Komplette Listen l�schen
		zCListSort<oCItem> *node = inventory2.GetFirstNode(i);
		while (node) {
			// aus globalen Listen entfernen
			item = node->GetData();
			node = node->GetNextInList();
		
			if (item->HasFlag(ITM_FLAG_MI)) return TRUE;
		}
	}
	return FALSE;
*/
	oCItem* item = NULL;
//	for (int cat=0; cat<INV_MAX; cat++) {
//		inventory2.UnpackCategory(cat);
		inventory2.UnpackCategory();
//		int numItems = inventory2.GetNumItemsInCategory(cat);
		int numItems = inventory2.GetNumItemsInCategory();
		for (int i=0; i<numItems; i++) {
//			item = GetItem(cat, i);
			item = GetItem(0, i);
			if (item && item->HasFlag(ITM_FLAG_MI)) return TRUE;
		}
//	}
	return FALSE;
};

// *** Checks ***
oCItem* oCNpc :: IsInInv (oCItem* item, int anz)
{
	return inventory2.IsIn(item,anz);
}

//
//	CODECHANGE [ROMAN]
//
oCItem* oCNpc :: GetFromInv (int instance, int anz)
{
	oCItem* pItem = inventory2.IsIn(instance,anz);

	if ( ! pItem ) return NULL;
	if ( pItem->GetAmount() == anz )	return pItem;

	oCItem* pItemClone = (oCItem*) pItem->CreateCopy();
	pItemClone->SetAmount( anz );
	pItem->SetAmount( pItem->GetAmount() - anz );

	return pItemClone;
}
//
//	CODECHANGE [ROMAN] END
//

oCItem* oCNpc :: IsInInv (int instance, int anz)
{
	return inventory2.IsIn(instance,anz);
}

oCItem* oCNpc :: IsInInv (const zSTRING& name, int anz)
{
	return inventory2.IsIn(name,anz);
}

zBOOL oCNpc :: CanCarry (oCItem* item)
{
	if (inventory2.CanCarry(item) ||
		(item->MultiSlot() && inventory2.IsIn(item->GetInstance(), 1)))
		return TRUE;

	this->GetAnictrl()->GetModel()->StartAni("T_CANNOTTAKE");
	return FALSE;
}

// *** Checks ***
/*--------------------------------------------------------------------------

    zCNpc::PutInInv()

 

    23-Aug-00       [Roman Keskenti]

                      Chaught oCInventory::Insert() 's return value


--------------------------------------------------------------------------*/ 
oCItem* oCNpc :: PutInInv (oCItem* item)
{
	if (!item) return NULL;

    if( item->GetObjectName() == S_ITLSTORCHBURNING)    // [Moos] es ist eine brennende Fackel. Igitt. Mache daraus eine nicht brennende.
    	item = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCH");	//  die brennende fackel sollte dann eigentlich durch das fehlende AddRef unten beseitigt werden.
    else
        zADDREF_ACCT(item);                                                               // jetzt haben wir jedenfalls eine lokale Referenz auf das item.

	// Physikalisch aus Welt entfernen ( RefCtr ! )
	oCWorld* oworld = zDYNAMIC_CAST<oCWorld>(item->GetHomeWorld());
	if (oworld) oworld->DisableVob(item);

	// etwaige item effekte auch aus der welt entfernen
	if (item->GetEffect()) item->GetEffect()->RemoveVobFromWorld();
	
//	zERR_ASSERTT(item->GetRefCtr()==2,"U: INV: Item-Reference-Counter != 2");

	// Check : Talent Pilzkunde, gleich identifizieren

	//
	//	CODECHANGE [ROMAN]
	//
	oCItem *item2 = inventory2.Insert(item);
	//
	//	CODECHANGE [ROMAN]
	//

	/*
	if (HasTalent(NPC_TAL_IDENTIFY) && (item->GetInstanceName()=="ITFOMUSHROOM")) {
		// NOTE : OriginalItem wird gel�scht !!!!	
		IdentifyAllMushrooms();
	}
	*/

    zRELEASE(item);  // [Moos] gegenst�ck zum AddRef ganz oben

	return item2;
}

oCItem* oCNpc :: PutInInv (int instance, int anz)
{
	if (instance<0) return NULL;

	oCItem* item = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,instance);
	if (item) {
		if (item->MultiSlot()) {
			item -> SetAmount ( anz );
			return PutInInv(item);
		} else {
			// No Multislot -> einzeln erzeugen
			for (int i=0; i<anz-1; i++) {
				item  = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,instance);
				item -> SetAmount( 1 );
				PutInInv(item);
			}
			return item;
		}
	}
	return NULL;
}

oCItem* oCNpc :: PutInInv (const zSTRING& name, int anz)
{
	return PutInInv(parser.GetIndex(name),anz);
}

oCItem*	oCNpc :: RemoveFromInv (oCItem* item, int anz)
{
	if (item) {
		item = inventory2.Remove(item,anz);
		if (item && item->HasFlag(ITM_FLAG_ACTIVE)) Equip(item);
	}
	return item;
}

oCItem*	oCNpc :: RemoveFromInv	(int instance, int num)
{
	oCItem* item = inventory2.Remove(instance,num);
	if (item && item->HasFlag(ITM_FLAG_ACTIVE)) Equip(item);		
	return item;
}

oCItem* oCNpc :: RemoveFromInv	(const zSTRING& instance, int num)
{
	return RemoveFromInv(parser.GetIndex(instance),num);
}

// ********************************************
// Inventory Slots
// ********************************************

zBOOL oCNpc :: IsSlotFree (const zSTRING& name)
{
	return IsSlotFree(GetInvSlot(name));
}
	
zBOOL oCNpc :: IsSlotFree (TNpcSlot* slot)
{
	return (slot && !slot->Vob());
}

void oCNpc :: SetToSlotPosition(zCVob* vob, const zSTRING& slotName)
{
	if (!vob) return;
	zMAT4 trafo = GetTrafoModelNodeToWorld(slotName);
	vob -> SetCollDet (FALSE);
	vob -> SetTrafoObjToWorld(trafo);
	oCItem* item = zDYNAMIC_CAST<oCItem>(vob);
	if (item && item->GetEffect()) item->GetEffect()->SetTrafoObjToWorld(trafo);
}

void oCNpc :: CreateInvSlot (const zSTRING& name) 
// Ein neues Slot anmelden
{
	TNpcSlot* slot		= zNEW( TNpcSlot );
//	slot -> vob			= NULL; // [Moos] macht der Konstruktor schon brav
	slot -> inInventory	= FALSE;
	slot -> tmpLevel	= 0;
	slot -> name		= name;
	invSlot.Insert ( slot );
}

void oCNpc :: DeleteInvSlot (const zSTRING& name)
{
	TNpcSlot* slot		= NULL;
	for (int i=0; i<invSlot.GetNumInList(); i++) {
		slot = invSlot[i];
		if (slot->name==name) {
			invSlot.Remove(slot);
//            zRELEASE(slot->vob);  // CODECHANGE Moos: Leakfix ; [Moos, viel sp�ter] macht jetzt der Destruktor
			delete(slot);
			return;
		}
	}
}

TNpcSlot* oCNpc :: GetInvSlot(const zSTRING& name)
{
	for (int i=0; i<invSlot.GetNumInList(); i++) {
		if (invSlot[i]->name == name) return invSlot[i];
	}
	return NULL;
}

TNpcSlot* oCNpc :: GetInvSlot(zCVob* vob)
{
	for (int i=0; i<invSlot.GetNumInList(); i++) {
		if (invSlot[i]->Vob() == vob) return invSlot[i];
	}
	return NULL;
}

zBOOL oCNpc :: IsInvSlotAvailable (const zSTRING& name)
{
	return (GetInvSlot(name)!=NULL);
}

void oCNpc :: PutInSlot (const zSTRING& name, oCVob* vob, zBOOL inInv)
{
	PutInSlot(GetInvSlot(name),vob,inInv);
}


void oCNpc :: PutInSlot (TNpcSlot* slot, oCVob* vob, zBOOL inInv)
{
	if (!slot)	return;
	if (!vob)	return;

	// Benutztes Slot vorher freimachen
	if (!IsSlotFree(slot))
    {
        // [Moos] wenn es eine Fackel ist und der slot die linke Hand ist, versuche sie in die rechte zu nehmen.
        if (slot->Vob()->GetObjectName() == S_ITLSTORCHBURNING && slot == GetInvSlot(NPC_NODE_LEFTHAND) &&
            IsSlotFree(NPC_NODE_RIGHTHAND)){
            zCVob *torch = slot->Vob();
            torch->AddRefVobSubtree();
            PutInSlot(NPC_NODE_RIGHTHAND, RemoveFromSlot(slot));
            torch->ReleaseVobSubtree();

            GetActiveInfoWritablePrivate()->putTorchBackInHand = TRUE;  // r�ume sie bei Gelegenheit wieder weg.
        }
        else  // Normalfall. schmeisse das Ding einfach weg.
        {
            s_isInPutInSlot = TRUE;
            RemoveFromSlot(slot);
            s_isInPutInSlot = FALSE;
        }
    }

	// Okay, jetzt belegen
	slot->SetVob(vob);	//  [Moos] neue Logik
	slot->inInventory	= inInv;

    // Sicherheit: Wenn Fackel in der Hand, dann her mit der Ani
    oCItem *torch = GetSlotItem(NPC_NODE_LEFTHAND);
    SetTorchAni(torch && torch->GetObjectName() == S_ITLSTORCHBURNING, FALSE);
	
	// Nicht in Fokus kriegen.
	oCItem* item = zDYNAMIC_CAST<oCItem>(vob);
	if (item) item->SetFlag(ITM_FLAG_NFOCUS);

	if (inInv) 
	{
		oCItem* item	= zDYNAMIC_CAST<oCItem>(vob);
		if (item) item->CreateVisual();
		
		//		zCModel* model	= GetModel();
		// Falls nur im Inv, einfach Mesh uebernehmen
		if (slot->name==NPC_NODE_TORSO) 
		{						
			if (!item) return;
			zSTRING visName = item -> GetVisualChange();
			if (!visName.IsEmpty()) 
			{
				// *****************
				// Ruestung anziehen
				// *****************
				item -> SetFlag(ITM_FLAG_ACTIVE);
                if (GetHomeWorld())
    				InitModel();                         // [Moos] nicht, bevor der NPC in der Welt ist.
					
			 }
			 this  -> SetItemEffectControledByModel(item, 0, TRUE);
		} 
		else 
		{
			// ***********************
			// Helm/Waffe/Fackel/Pfeil
			// ***********************
            if (GetVisual())
			{
                zCModel* model	= GetModel();
			    zCModelNodeInst* node	= model -> SearchNode( slot->name );
				if (node) 
				{
					oCItem* item = zDYNAMIC_CAST<oCItem>(vob);
					if (item) item->CreateVisual();
					model -> SetNodeVisual( node, vob->GetVisual() );

					// [EDENFELD] An dieser Stelle wird das Item nur noch vom Modelanimationssystem
					// gerendert
					this  -> SetItemEffectControledByModel(item, node, TRUE);
				}
            }
		}

	} 
	else 
	{
		// Falls nicht in Welt, das Teil einf�gen
		vob -> SetCollDet (FALSE);	
		if (!vob	-> GetHomeWorld()) {
			vob		-> SetPositionWorld(0,0,0);			// Safety
//			ogame	-> GetWorld() -> zCWorld::AddVobAsChild (vob,this);
			ogame	-> GetGameWorld() -> EnableVob(vob,this);
			SetToSlotPosition (vob,slot->name);
		}
		// Vob einrichten
		vob -> SetIgnoredByTraceRay	(TRUE);
		vob -> SetPhysicsEnabled	(FALSE);
		vob -> GetRigidBody ()->SetGravityEnabled (FALSE);
	};
};

/* ----------------------------------------------------------------------
	
    oCNpc :: RemoveFromAllSlots()	

	20.10.2000	[Moos]	
                Erzeugt, um das Fackelleck zu stopfen (so kann oCWorld die npc-Slots aufr�umen)


   ---------------------------------------------------------------------- */

void oCNpc :: RemoveFromAllSlots(zBOOL dropIt){
	for (int i=0; i<invSlot.GetNumInList(); i++)
        RemoveFromSlot(invSlot[i], dropIt);
}

oCVob* oCNpc :: RemoveFromSlot(const zSTRING& slot, zBOOL dropIt, zBOOL killEffect)
{
	return RemoveFromSlot(GetInvSlot(slot),dropIt, killEffect);
}

oCVob* oCNpc :: RemoveFromSlot(TNpcSlot* slot, zBOOL dropIt, zBOOL killEffect)
{
	if (!slot) return NULL;

	// In Fokus kriegen.
	oCItem* item = zDYNAMIC_CAST<oCItem>(slot->Vob());
	if (item) item->ClearFlag(ITM_FLAG_NFOCUS);

	if (slot->inInventory) 
	{		
		// Noch im Inventory, dann einfach nur Mesh entfernen
		if (slot->name == NPC_NODE_TORSO) 
		{
			// ******************
			// Ruestung ausziehen
			// ******************
			oCItem* item = GetEquippedArmor();
			if (item) 
			{
				// Save Vob temporarily
				oCVob* saveVob	= slot->Vob();
                if (saveVob) saveVob->AddRef();
				slot->ClearVob();	//  [Moos] neue Logik
				// Remove Armor
				item -> ClearFlag(ITM_FLAG_ACTIVE);
				if (GetVisual()) InitModel();
				// Restore Vob
				slot->SetVob(saveVob);
                zRELEASE(saveVob);

				// an dieser stelle muss ein etwaiger item effekt aus
				// der welt entfernt werden, da das item auch nicht mehr da ist
				this->SetItemEffectControledByModel(item, 0, FALSE, TRUE, killEffect);				
			}


		} 
		else 
		{
			// *********************************
			// Helm/Fackel/Pfeil/Waffe ausziehen
			// *********************************
            if (GetVisual())
            {
        		zCModel* model = GetModel();
    			zCModelNodeInst* node	= model -> SearchNode( slot->name );
    			
				// kontrolle dem modelanimationssystem entziehen
				if (node) model -> SetNodeVisual( node, NULL );

				// an dieser stelle muss ein etwaiger item effekt aus
				// der welt entfernt werden, da das item auch nicht mehr da ist
				this->SetItemEffectControledByModel(item, 0, FALSE, TRUE, killEffect);				
            };
		};

	} else if (dropIt) {
		// Object fallenlassen 
		return DropFromSlot(slot);
	}
	
	oCVob* removedVob = slot->Vob();
	if (slot->Vob()) 
	{
		zCWorld* zwld	= slot->Vob()->GetHomeWorld();
		if (zwld) 
		{
			oCWorld*	wld = zDYNAMIC_CAST<oCWorld>(zwld);
			if (wld)	wld -> DisableVob(slot->Vob());
			else		zwld-> RemoveVobSubtree(slot->Vob());
		}
		slot  -> Vob() -> SetIgnoredByTraceRay(FALSE);
        slot->ClearVob();	//  [Moos] Neue Logik
	}
	
    CheckPutbackTorch();
	return removedVob;
};

oCVob* oCNpc :: DropFromSlot(const zSTRING& name)
{
	return DropFromSlot(GetInvSlot(name));
}

oCVob* oCNpc :: DropFromSlot(TNpcSlot* slot)
{
	if (!slot || !slot->Vob()) return NULL;

	zBOOL inMove = GetInMovement();
	if (inMove) EndMovement();

	if (slot->inInventory) 
	{
		// Noch im Inventory, dann einfach nur Mesh entfernen
		zCModel* model			= GetModel();
		zCModelNodeInst* node	= model -> SearchNode( slot->name );
		if (node) model -> SetNodeVisual( node, NULL );

		oCItem *item = zDYNAMIC_CAST<oCItem>(slot->Vob());
		
		if ( (NULL!=item) && (NULL!=item->GetEffect()))
		{
			// ok, gib dem vob wieder die kontrolle �ber sich selbst
			GetModel()->RemoveChildVobFromNode	   (item->GetEffect());
			item->GetEffect()->SetAllowMovement (TRUE);
			this->GetHomeWorld()->MoveVobSubtreeToWorldSpace(item->GetEffect());
			item->GetEffect()->SetSleeping	   (FALSE);
			item->GetEffect()->SetPFXShapeVisual(item->GetVisual());

		}

		// und Objekt aus Inventory entfernen
		DoRemoveFromInventory(item);
	} 

	// Object fallenlassen 


	zMATRIX4	trafo	= GetTrafoModelNodeToWorld( slot->name );
    zCVob          *v   = slot->Vob();

    // [Moos] Fallenlass-Code aus DoDropVob geklaut, der alte hat�s nicht getan.

	// immer die oCAIVobMove anschmeissen
	oCAIVobMove* ai = zDYNAMIC_CAST<oCAIVobMove>(v->GetAI());
	if (!ai) {
		// neue AI bauen
		if (v->GetAI()) v->GetAI()->Release();
		v->SetAI(ai = zNEW( oCAIVobMove() ));
		v->GetAI()->Release();
	}

	// Und fallen lassen
	if (ai) ai->Init(v,this,trafo.GetTranslation(),0,100,&trafoObjToWorld);

    /* Alter Code; kann mit anpassungen an der oCAIDrop reaktiviert werden. [Moos]
	zMATRIX4	trafo	= GetTrafoModelNodeToWorld( slot->name );
	zVEC3		pos		= trafo.GetTranslation();
	zCVob*		v		= slot->Vob();
	oCAIDrop*	drop	= zNEW( oCAIDrop() );

	drop	-> SetupAIVob			(v,this);
	v 		-> SetAICallback		(drop);
	v		-> SetIgnoredByTraceRay	(FALSE);
	zRELEASE	(drop);

    */

	// Activate bei den Items raus
	// FIXME : Ist das hier wirklich n�tig ? 
	if (zDYNAMIC_CAST<oCItem>(v)) {
		oCItem* item = (oCItem*)v;
		if (item->HasFlag(ITM_FLAG_ACTIVE)) item->ClearFlag(ITM_FLAG_ACTIVE);
		if (item->HasFlag(ITM_FLAG_NFOCUS)) item->ClearFlag(ITM_FLAG_NFOCUS);
		// Sign items dropped by player
		if (this->IsSelfPlayer())
			item->SetFlag(ITM_FLAG_DROPPED);
	}

	slot -> Vob() -> SetIgnoredByTraceRay(FALSE);
	oCVob* removedVob = slot->Vob();
	
	zERR_ASSERT	(slot->Vob()->GetRefCtr()>1);
    slot->ClearVob();	//  [Moos] neue Logik

	if (inMove) BeginMovement();
	
    CheckPutbackTorch();
	return removedVob;
};

void oCNpc :: UpdateSlots()
{
	TNpcSlot* slot;
	for (int i=0; i<invSlot.GetNumInList(); i++) 
	{
		slot = invSlot[i];
		if (slot && slot->Vob()) 
		{			
			oCItem *item = zDYNAMIC_CAST<oCItem>(slot->Vob());

			// beim laden eines savegames kann ein item-effekt nocht nicht als child an den npc geh�ngt werden
			// dies passiert dann hier einmalig (siehe SetItemEffectControledByModel())
			if ( item && item->GetEffect() && !item->GetEffect()->HasParentVob() )
			{
				if (!item->GetEffect()->GetHomeWorld()) GetHomeWorld()->AddVob(item->GetEffect());
				GetHomeWorld()->MoveVobSubtreeTo(item->GetEffect(), this);
			}

			if (!slot->inInventory)
			{				
				slot->Vob()->SetCollDet(FALSE);
				SetToSlotPosition(slot->Vob(),slot->name);				
			}
		}
	}
}

// ****************************************
// Mob Manipulation (Logic)
// ****************************************

void oCNpc :: SetInteractMob		( oCMobInter *mob )
{
	// FIXME : Safety, nicht unbedingt n�tig
	oCAIHuman* ai = zDYNAMIC_CAST<oCAIHuman>(GetAI());
	if (ai) {
		if (interactMob)	ai -> SubIgnoreCD (interactMob);
		if (mob)			ai -> AddIgnoreCD (mob);
	}
	interactMob = mob;
	if (interactMob) GetModel()->SetIsInMobinteraction(TRUE);
	else			 GetModel()->SetIsInMobinteraction(FALSE);
};

oCMobInter*	oCNpc :: GetInteractMob	( )
{
	return interactMob;
};

zCVob::zTVobCharClass oCNpc :: GetCharacterClass	()					
{
	if (IsAPlayer())	return zVOB_CHAR_CLASS_PC;
	else				return zVOB_CHAR_CLASS_NPC;
};

void oCNpc :: SetInteractItem	(oCItem* item)
// Das InteractItem wird aus dem Slot entfernt ( nicht deleted ! )
// Das InteractItem wird ins Inventory gepackt
// Alle Additional InteractItems werden deleted !!!
// Alle Additional Slots werden deleted !!!
{
/*	zERR_MESSAGE(4,0,"U: NPC: Set InteractItem NSC "+GetInstanceName());
	zSTRING debugStr;
	if (item)	debugStr = item->GetInstanceName() + "Amount:" + zSTRING(item->GetAmount()) + " RefCtr:" + zSTRING(item->GetRefCtr());
	else		debugStr = "None";
	zERR_MESSAGE(4,0,"U: NPC: New InteractItem : "+debugStr);

	if (interactItem)	debugStr = interactItem->GetInstanceName() + "Amount:" + zSTRING(interactItem->GetAmount()) + " RefCtr:" + zSTRING(interactItem->GetRefCtr());
	else				debugStr = "None";
	zERR_MESSAGE(4,0,"U: NPC: Old InteractItem : "+debugStr);
*/
	if (interactItem) {

		//assert(interactItem->GetRefCtr()>=3);
		if (item!=interactItem) {
			// Remove all Interact-Items and Destroy Additionals
			TNpcSlot*	slot		= NULL;
			oCItem*		slotItem	= NULL;
			
			for (int i=0; i<invSlot.GetNumInList(); i++) {
				slot		= invSlot[i];
				slotItem	= GetSlotItem(slot->name);
				if (slotItem) {
					
					if ((slot->tmpLevel==0) && (slotItem->GetInstance()==interactItem->GetInstance())) {
						//zERR_WARNING	("U: ITEMI:Removed Item:"+interactItem->GetInstanceName());

						// [EDENFELD] 1.27 das hier ist die zentrale stelle an der alle interact items verschwinden
						// das problem war, das hier von mehreren stellen ein neues item erzeugt wurde und somit das alte
						// verschwand.
						// Man k�nnte hier auch das neue Item wieder in den Slot stecken, aber aus Sicherheitsgr�nden
						// gibts hier keinen globalen Fix, sondern der seperate Call wird vorher abgefangen
						oCItem* tmpItem = zDYNAMIC_CAST<oCItem>(RemoveFromSlot(slot,FALSE));
						// Noch in Welt registriert ? Dann darf's auch ins Inventory, 
						// ansonsten wird Welt gerade abger�umt
						// if (tmpItem && (tmpItem->GetRefCtr()>2)) 
						PutInInv(tmpItem);
					
					} else if (slot->tmpLevel>0) {
						// Created for ItemInteraction 
						// a) Destroy Object
						zCVob* vob = RemoveFromSlot	(slot,FALSE);
						if (vob) vob->AddRef();
						GetHomeWorld() -> RemoveVob(vob);
						// Release it
//						assert(vob->GetRefCtr()==1);
//						assert( vob != interactItem );
						if (slot->tmpLevel==2) {
							// b) Destroy complete Slot
							//zERR_WARNING ("U: ITEMI: Destroyed Slot:"+slot->name);
							DeleteInvSlot(slot->name);
						}
						slot->tmpLevel = 0;
						if (vob) vob->Release();
					}
				}
			}
		}

	}
	if (interactItem!=item) {
		// Altes InteractItem releasen
		zRELEASE(interactItem);
		// Neues Interactitem setzen
		interactItem = item;	
		// und ein AddRef drauf
		if (interactItem) interactItem->AddRef();
	}
}

// ****************************
// Basic Event-Messages
// ****************************

void oCNpc :: OnTouch (zCVob* otherVob)
{
	oCMOB* mob = zDYNAMIC_CAST<oCMOB>(otherVob);
	if (mob) {
		if (mob->GetRigidBody()->GetVelocity().Length2()>10000) {
			// Jap, das Teil ist in Bewegung
			oCAIVobMove* ai = zDYNAMIC_CAST<oCAIVobMove>(mob->GetAI());
			if (ai) {
				// Darf Kollision stattfinden ?	
				OnDamage(mob,ai->GetOwner(),mob->GetDamage(), oEDamageType_Edge, GetPositionWorld());
				ai -> AddIgnoreCDVob(this);
			}
		}
	}
}

// ****************************************
// AI - Kommandos
// ****************************************

/*--------------------------------------------------------------------------

    oCNpc::OnMessage()

 

    17-Aug-00       [Roman Keskenti]

						Added EV_AimAt and EV_ShootAt

	24-Aug-00		[Roman Keskenti]	

						Added EV_EquipArmor					

    28-Aug-00       [Roman Keskenti]

						Added EV_StopAim

    07-Sep-00       [Roman Keskenti]

						Added EV_Defend

--------------------------------------------------------------------------*/ 
void oCNpc :: OnMessage	(zCEventMessage *eventMessage, zCVob* sourceVob)
{
	if (!IsMessageAIEnabled()) {
		eventMessage->Delete();
		return;
	}

    if (!GetVisual() || !GetAnictrl())
        AvoidShrink();	//  [Moos] GRRR. Falls mal ein nicht in der Welt eingef�gter NSC eine Nachricht erh�lt...

	if (!GetAnictrl()) InitHumanAI();
	anictrl = GetAnictrl();

    zERR_ASSERT_STRICT(anictrl && anictrl->GetRefCtr() > 0);

	// Hier Addref drauf, damit message nicht Irgendwo gel�scht wird (zB. Cutscene-Clear)
	eventMessage->AddRef();

	zBOOL del = TRUE;

	if (zDYNAMIC_CAST<zCEvMsgCutscene>(eventMessage))
	{
		zCEvMsgCutscene* csg = static_cast<zCEvMsgCutscene*>(eventMessage);

		zERR_MESSAGE(8,0,"U: NPC: \""+GetName(TRUE)+"\" received message "+csg->MD_GetSubTypeString(csg->GetSubType())+" from Cutscene \""+csg->GetCutsceneName()+"\"");

		switch (csg->GetSubType())
		{
			//
			// Start playing a cutscene
			//	
			case zCEvMsgCutscene::EV_CS_RESUME:			
			case zCEvMsgCutscene::EV_CS_STARTPLAY:				
				if (csg->IsMainRole())
				{
					if ( oCNpc::player && csg->IsGlobalCutscene())
					{
						if ( IsConditionValid() )
						{
							oCNpc::player->CloseInventory();
							oCNpc::player->GetAnictrl()->StopTurnAnis();
							oCNpc::player->StandUp(FALSE);				
						}
					}
				}
				if (!GetHomeWorld())
				{
					// NSC (die Rolle) in die Welt einfuegen					
					zVEC3 pos;
					if (state.HasRoutine()) pos = rtnMan.GetRoutinePos(this);
					else					pos = state.GetAIStatePosition();					
					Enable(pos);
					zERR_MESSAGE(7,0,"U: NPC: "+GetName(TRUE)+" inserted into world for cutscene \""+csg->GetCutsceneName()+"\"");
				};

				if (!csg->IsOutputUnit()) 
				{
					//
					//	AKTUELLEN ZUSTEND SICHERN
					//
					this->old_script_state = this->state.GetState();

					//
					//	WAHRNEHMUNGEN LOESCHEN
					//
					this->ClearPerception		();
					this->ClearPerceptionLists	();

					//
					//	STANDARD-WAHRNEHMUNGEN FUER CUTSCENES PER SKRIPT AKTIVIEREN
					//
					if ( !csg->IsGlobalCutscene() )
					{
						int nIndex = :: parser .GetIndex( "B_SETCUTSCENEPERCEPTIONS" );
						parser.SetInstance("SELF",this);
						parser.CallFunc( nIndex );
					}
				}

				del = TRUE;
				break;

			//
			// Stopping a cutscene
			//
			case zCEvMsgCutscene::EV_CS_STOP:	
			case zCEvMsgCutscene::EV_CS_INTERRUPT:					
			/*
				//
				//	SCREEN LOESCHEN
				//
                if (ogame && ogame->GetView(oCGame::GAME_VIEW_SCREEN)) // [Moos] Crashfix; im Destruktor von oCGame sind die Views schon gel�scht...
				    ::ogame->GetView( oCGame::GAME_VIEW_SCREEN )->ClrPrintwin();
			*/
				if (!csg->IsOutputUnit()) 
				{
					//
					//	AUFSTEHEN
					//
					if ( IsConditionValid() )
						StandUp();

					//
					//	ALTEN ZUSTAND WIEDERHERSTELLEN
					//

					// Noetig bei normalem Ende der Cutscene
					// state.StartAIState( this->old_script_state, FALSE, 0 ); 
				
				} else {
					
					// OU wurde gestoppt.
					// WatchMsg zur Sicherheit rauswerfen (CTRL + C)
					StopRunningOU();			
				
				}
				del = TRUE;
				break;			
		};
		if (del) csg->Delete();
	} 
	else

	if (zDYNAMIC_CAST<oCMsgDamage>(eventMessage)) {
		
		oCMsgDamage* csg = (oCMsgDamage*) eventMessage;
		switch( csg->GetSubType() ) {
			case oCMsgDamage::EV_DAMAGE_ONCE		:	del = EV_DamageOnce		(csg);		break;
			case oCMsgDamage::EV_DAMAGE_PER_FRAME	:	del = EV_DamagePerFrame	(csg);		break;
		};
		if (del) csg->Delete();
	} else

	if (zDYNAMIC_CAST<oCMsgMovement>(eventMessage)) {
		
		oCMsgMovement* csg = (oCMsgMovement*)eventMessage;
		switch	(csg->GetSubType()) {
			case oCMsgMovement::EV_ROBUSTTRACE	:	del = EV_RobustTrace	(csg);		break;
			case oCMsgMovement::EV_GOTOPOS		:	del = EV_GotoPos		(csg);		break;
			case oCMsgMovement::EV_GOTOVOB		:	del = EV_GotoVob		(csg);		break;
			case oCMsgMovement::EV_GOROUTE		:	del = EV_GoRoute		(csg);		break;
			case oCMsgMovement::EV_TURN			:	del = EV_Turn			(csg);		break;
			case oCMsgMovement::EV_TURNTOPOS	:	del = EV_TurnToPos		(csg);		break;
			case oCMsgMovement::EV_TURNTOVOB	:	del = EV_TurnToVob		(csg);		break;
			case oCMsgMovement::EV_TURNAWAY		:	del = EV_TurnAway		(csg);		break;
			case oCMsgMovement::EV_JUMP			:	del = EV_Jump			(csg);		break;
			case oCMsgMovement::EV_WHIRLAROUND	:	del = EV_WhirlAround	(csg);		break;
			case oCMsgMovement::EV_SETWALKMODE	:	del = EV_SetWalkMode	(csg);		break;
			case oCMsgMovement::EV_STANDUP		:	del = EV_StandUp		(csg);		break;
			case oCMsgMovement::EV_CANSEENPC	:	del = EV_CanSeeNpc		(csg);		break;
			case oCMsgMovement::EV_STRAFE		:	del = EV_Strafe			(csg);		break;
			case oCMsgMovement::EV_GOTOFP		:	del = EV_GotoFP			(csg);		break;
			case oCMsgMovement::EV_DODGE		:	del = EV_Dodge			(csg);		break;
			case oCMsgMovement::EV_BEAMTO		:	BeamTo(csg->targetName);del = TRUE;	break;
			case oCMsgMovement::EV_ALIGNTOFP	:	del = EV_AlignToFP		(csg);		break;
		};
		if (del) csg->Delete();
	} else
	
	if (zDYNAMIC_CAST<oCMsgAttack>(eventMessage)) {
		
		oCMsgAttack* csg = (oCMsgAttack*)eventMessage;
		switch	(csg->GetSubType()) {
			case oCMsgAttack::EV_ATTACKFORWARD	:	del = EV_AttackForward	(csg);		break;
			case oCMsgAttack::EV_ATTACKLEFT		:	del = EV_AttackLeft		(csg);		break;
			case oCMsgAttack::EV_ATTACKRIGHT	:	del = EV_AttackRight	(csg);		break;
			case oCMsgAttack::EV_ATTACKRUN		:	del = EV_AttackRun		(csg);		break;
			case oCMsgAttack::EV_ATTACKFINISH	:	del = EV_AttackFinish	(csg);		break;
			case oCMsgAttack::EV_PARADE			:	del = EV_Parade			(csg);		break;
			case oCMsgAttack::EV_AIMAT			:	del = EV_AimAt			(csg);		break;
			case oCMsgAttack::EV_SHOOTAT		:	del = EV_ShootAt		(csg);		break;
			case oCMsgAttack::EV_STOPAIM		:	del = EV_StopAim		(csg);		break;
			case oCMsgAttack::EV_DEFEND			:	del = EV_Defend			(csg);		break;
			case oCMsgAttack::EV_ATTACKBOW		:	del = EV_AttackBow		(csg);		break;
			case oCMsgAttack::EV_ATTACKMAGIC	:	del = EV_AttackMagic	(csg);		break;
		};
		if (del) csg->Delete();
	} else

	if (zDYNAMIC_CAST<oCMsgConversation>(eventMessage)) {

		oCMsgConversation* csg = (oCMsgConversation*)eventMessage;
		switch	(csg->GetSubType()) {
			case oCMsgConversation::EV_PLAYANISOUND		:	del = EV_PlayAniSound		(csg);	break;
			case oCMsgConversation::EV_PLAYANI			:	del = EV_PlayAni			(csg);	break;
			case oCMsgConversation::EV_PLAYSOUND		:	del = EV_PlaySound			(csg);	break;
			case oCMsgConversation::EV_SNDPLAY			:
			case oCMsgConversation::EV_SNDPLAY3D		:	del = EV_SndPlay			(csg);	break;
			case oCMsgConversation::EV_LOOKAT			:	del = EV_LookAt				(csg);	break;
			case oCMsgConversation::EV_POINTAT			:	del = EV_PointAt			(csg);	break;
			case oCMsgConversation::EV_STOPLOOKAT		:	del = EV_StopLookAt			(csg);	break;
			case oCMsgConversation::EV_STOPPOINTAT		:	del = EV_StopPointAt		(csg);	break;
			case oCMsgConversation::EV_QUICKLOOK		:	del = EV_QuickLook			(csg);	break;
			case oCMsgConversation::EV_OUTPUT			:	del = EV_Output				(csg);	break;
			case oCMsgConversation::EV_OUTPUTSVM		:	del = EV_OutputSVM			(csg);	break;
			case oCMsgConversation::EV_CUTSCENE			:	del = EV_Cutscene			(csg);	break;
			case oCMsgConversation::EV_WAITTILLEND		:	del = EV_WaitTillEnd		(csg);	break;
			case oCMsgConversation::EV_ASK				:	del = EV_Ask				(csg);	break;
			case oCMsgConversation::EV_WAITFORQUESTION	:	del = EV_WaitForQuestion	(csg);	break;
			case oCMsgConversation::EV_PLAYANI_NOOVERLAY:	del = EV_PlayAni			(csg);	break;
			case oCMsgConversation::EV_PLAYANI_FACE		:	del = EV_PlayAniFace		(csg);	break;
			case oCMsgConversation::EV_PROCESSINFOS		:	del = EV_ProcessInfos		(csg);	break;
			case oCMsgConversation::EV_STOPPROCESSINFOS	:	del = EV_StopProcessInfos	(csg);	break;
			case oCMsgConversation::EV_OUTPUTSVM_OVERLAY:	del = EV_OutputSVM_Overlay	(csg);	break;
			case oCMsgConversation::EV_PRINTSCREEN		:	del = EV_PrintScreen		(csg);	break;
			case oCMsgConversation::EV_STARTFX			:	del = EV_StartFX			(csg);	break;
			case oCMsgConversation::EV_STOPFX			:	del = EV_StopFX				(csg);	break;
		}
		if (del) 
		{
			zERR_MESSAGE(9,0,"U: Mark Conversationmessage for deletion");
			csg->Delete();
		}
		
	} else

	if (zDYNAMIC_CAST<oCMsgWeapon>(eventMessage)) {
		
		oCMsgWeapon* csg = (oCMsgWeapon*)eventMessage;
		switch	(csg->GetSubType()) 
		{
			case oCMsgWeapon::EV_DRAWWEAPON				:	del = EV_DrawWeapon			(csg);		break;
			case oCMsgWeapon::EV_DRAWWEAPON1			:	del = EV_DrawWeapon1		(csg);		break;
			case oCMsgWeapon::EV_DRAWWEAPON2			:	del = EV_DrawWeapon2		(csg);		break;
			case oCMsgWeapon::EV_REMOVEWEAPON			:	del = EV_RemoveWeapon		(csg);		break;
			case oCMsgWeapon::EV_REMOVEWEAPON1			:	del = EV_RemoveWeapon1		(csg);		break;
			case oCMsgWeapon::EV_REMOVEWEAPON2			:	del = EV_RemoveWeapon2		(csg);		break;
			case oCMsgWeapon::EV_CHOOSEWEAPON			:	del = EV_ChooseWeapon		(csg);		break;
			case oCMsgWeapon::EV_FORCEREMOVEWEAPON		:	del = EV_ForceRemoveWeapon	(csg);		break;
			case oCMsgWeapon::EV_ATTACK					:	Fighting();	del=TRUE;					break;
			case oCMsgWeapon::EV_EQUIPBESTWEAPON		:	del = EV_EquipBestWeapon	(csg);		break;
			case oCMsgWeapon::EV_EQUIPBESTARMOR			:	del = EV_EquipBestArmor		(csg);		break;
			case oCMsgWeapon::EV_UNEQUIPWEAPONS			:	del = EV_UnequipWeapons		(csg);		break;
			case oCMsgWeapon::EV_UNEQUIPARMOR			:	del = EV_UnequipArmor		(csg);		break;
			case oCMsgWeapon::EV_EQUIPARMOR				:	del = EV_EquipArmor			(csg);		break;
		};

		if (del) csg->Delete();
	}
	else

	if (zDYNAMIC_CAST<oCMsgManipulate>(eventMessage)) {
		
		oCMsgManipulate* csg = (oCMsgManipulate*)eventMessage;
		switch	(csg->GetSubType()) {
			case oCMsgManipulate::EV_TAKEVOB				:	del = EV_TakeVob		(csg);		break;
			case oCMsgManipulate::EV_DROPVOB				:	del = EV_DropVob		(csg);		break;
			case oCMsgManipulate::EV_THROWVOB				:	del = EV_ThrowVob		(csg);		break;
			case oCMsgManipulate::EV_EXCHANGE				:	del = EV_Exchange		(csg);		break;
			case oCMsgManipulate::EV_USEITEMTOSTATE			:	del = EV_UseItemToState	(csg);		break;
			case oCMsgManipulate::EV_USEITEM				:	del = EV_UseItem		(csg);		break;
			case oCMsgManipulate::EV_USEMOB					:	del = EV_UseMob			(csg);		break;
			case oCMsgManipulate::EV_TAKEMOB				:	del = EV_TakeMob		(csg);		break;
			case oCMsgManipulate::EV_EQUIPITEM				:	del = EV_EquipItem		(csg);		break;
			case oCMsgManipulate::EV_DROPMOB				:	del = EV_DropMob		(csg);		break;

			case oCMsgManipulate::EV_INSERTINTERACTITEM		:	del = EV_InsertInteractItem	(csg);		break;
			case oCMsgManipulate::EV_REMOVEINTERACTITEM		:	del = EV_RemoveInteractItem (csg);		break;
			case oCMsgManipulate::EV_CREATEINTERACTITEM		:	del = EV_CreateInteractItem	(csg);		break;
			case oCMsgManipulate::EV_DESTROYINTERACTITEM	:	del = EV_DestroyInteractItem(csg);		break;
			case oCMsgManipulate::EV_PLACEINTERACTITEM		:	del = EV_PlaceInteractItem	(csg);		break;
			case oCMsgManipulate::EV_EXCHANGEINTERACTITEM	:	del = EV_ExchangeInteractItem(csg);		break;
			case oCMsgManipulate::EV_USEMOBWITHITEM			:	del = EV_UseMobWithItem		(csg);		break;

			case oCMsgManipulate::EV_CALLSCRIPT				:	del = EV_CallScript			(csg);		break;

//			case oCMsgManipulate::EV_PUTINSLOT		:	del = EV_PutInSlot		(csg);		break;
//			case oCMsgManipulate::EV_REMOVEFROMSLOT	:	del = EV_RemoveFromSlot	(csg);		break;
		}
		if (del) csg->Delete();

	} else 
		
	if (zDYNAMIC_CAST<oCMsgUseItem>(eventMessage)) {
		
		oCMsgUseItem* csg = (oCMsgUseItem*)eventMessage;
		switch	(csg->GetSubType()) {
			case oCMsgUseItem::EV_DRINK			:	del = EV_Drink			(csg);		break;
		}
		if (del) csg->Delete();
	} else

	if (zDYNAMIC_CAST<oCMsgState>(eventMessage)) {
		
		oCMsgState* csg = (oCMsgState*)eventMessage;
		switch	(csg->GetSubType()) {
			case oCMsgState::EV_STARTSTATE		:	// Hier wird eh immer der EM gel�scht,
													// darum immer FALSE -> kein Delete mehr
													EV_DoState	(csg);
													del = FALSE;
													break;
			case oCMsgState::EV_WAIT			:	del = EV_Wait   (csg);		break;
			case oCMsgState::EV_SETNPCSTOSTATE	:	SetNpcsToState	(csg->function,csg->minutes);
													del = TRUE;		
													break;
			case oCMsgState::EV_SETTIME			:	{	int day,hour,min;
														ogame->GetTime(day,hour,min);
														ogame->SetTime(day,csg->function,csg->minutes);
													};
													del = TRUE;
													break;
		}
		if (del) csg->Delete();
	} else 
		
	if (zDYNAMIC_CAST<oCMsgMagic>(eventMessage)) {
		
		oCMsgMagic* csg = (oCMsgMagic*)eventMessage;
		switch	(csg->GetSubType()) {
			case oCMsgMagic::EV_OPEN			:	OpenSpellBook	(csg->removeSymbol);	break;
			case oCMsgMagic::EV_CLOSE			:	CloseSpellBook	(csg->removeSymbol);	break;
			case oCMsgMagic::EV_MOVE			:{	oCMag_Book* mb = GetSpellBook();
													if (mb) {
														mb -> SetFrontSpell	(csg->activeSpell);
														if (csg->level<0)	mb->Left();
														else				mb->Right();
													}
													break;	}			
			case oCMsgMagic::EV_INVEST			:{	oCMag_Book* mb = GetSpellBook	();
													if (mb) mb->StartInvestEffect	(csg->target,csg->level,csg->manaInvested,csg->energyLeft);
													break;	}			
			case oCMsgMagic::EV_CAST			:{	oCMag_Book* mb = GetSpellBook	();
													if (mb) mb->StartCastEffect		(csg->target,csg->targetPos);
													break;	}			
			case oCMsgMagic::EV_SETLEVEL		:	//del = EV_RemoveWeapon2	(csg);		break;
			case oCMsgMagic::EV_SHOWSYMBOL		:	//del = EV_ChooseWeapon	(csg);		
													break;
			case oCMsgMagic::EV_SETFRONTSPELL   :	{
														oCMag_Book* mb = GetSpellBook	();
														if (mb) mb->SetFrontSpell(csg->activeSpell);	
													}
													break;
			case oCMsgMagic::EV_CASTSPELL		:	if (EV_CastSpell(csg)) csg->Delete();
													break;
			case oCMsgMagic::EV_READY			:	if (this->ReadySpell( csg->activeSpell, csg->manaInvested )) csg->Delete();
													break;
			case oCMsgMagic::EV_UNREADY			:	if (this->UnreadySpell()) csg->Delete();
													break;
		};
	}

#if defined(SECUROM) && !defined(COMPILING_SPACER)
	else if (zDYNAMIC_CAST<oCMsgRequest>(eventMessage))
	{
		oCMsgRequest* csg = (oCMsgRequest*)eventMessage;
		del = EV_Request(csg);
		if (del) csg->Delete();
	}
#endif

	eventMessage->Release();
}

// *****************************
// *** Events : Waffe ziehen ***
// *****************************

zBOOL oCNpc :: EV_DrawWeapon(oCMsgWeapon* csg)
{
	// Keine Waffe ziehen beim Schwimmen
	if (anictrl->GetWaterLevel()==2) return TRUE;

	// Bereits im Waffenmodus ?
	// FIXME : Nicht besonders sch�n
	if (csg->firstTime) 
	{
		oCItem *weapon = zDYNAMIC_CAST<oCItem>(GetRightHand());
		if (weapon && weapon->GetEffect()) weapon->GetEffect()->SetLevel(2,TRUE);


		if ( /*IsMonster() ||*/ (GetWeaponMode()!=NPC_WEAPON_NONE)) return TRUE;
		StandUp(TRUE);				// Walking allowed
		csg->showMagicCircle	= FALSE;		// Hier niemals Magiekranz anzeigen.
		csg->firstTime			= FALSE;
	}

	zCModel* model = GetModel();
	DoDoAniEvents();
	if (!csg->initDone) {
		
		if (model->IsAniActive(anictrl->_s_walkl)) {
			// **********************************
			// Waffe waehrend des Laufens ziehen
			// **********************************
			int wm			= GetNextWeaponMode					(csg->targetMode-1,+1,csg->useFist);
			zSTRING w		= anictrl	-> GetWeaponString		(wm);
			csg->ani		= model		-> GetAniIDFromAniName	("T_MOVE_2_"+w+"MOVE");
			if (GetLeftHand())	DoDropVob(GetLeftHand());
			if (GetRightHand()) DoDropVob(GetRightHand());
			if (csg->ani!=zMDL_ANI_ID_ILLEGAL) {
				csg->duringRun = TRUE;
				// NachfolgeAni NULL, weil Teilk�rper Ani auf Layer 2
				anictrl		-> StartAni	(csg->ani);
				// Safety, walk-Loop muss weiterlaufen, weil sonst ein kurz vorher
				// getstartetes "T_RUNL_2_RUN" zum Freezer fuehrt....
				/*if (model->IsAniActive	(anictrl->_t_walkl_2_walk)) {
					model->StopAni		(anictrl->_t_walkl_2_walk);
					model->StartAni		(anictrl->_s_walkl);
				}*/
				
				//,anictrl->s_walkl[wm]);
				csg			-> initDone = TRUE;
				if (IsAPlayer())
				{
					if( GetWeaponMode() < NPC_WEAPON_BOW )
					{
						if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModMelee);
						oCNpcFocus::SetFocusMode(FOCUS_MELEE);
					}
					else if( GetWeaponMode() >= NPC_WEAPON_BOW )
					{
						if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModNormal);
						oCNpcFocus::SetFocusMode(FOCUS_RANGED);
					}
				}
				return FALSE;
			}
			// no success...
			return TRUE;
			
		} else {
			// **********************************
			// Waffe aus dem Stand ziehen
			// **********************************
			anictrl -> StopTurnAnis();
			csg		-> duringRun = FALSE;
			csg		-> initDone	 = EV_DrawWeapon1(csg);
			if (csg->initDone) csg->SetInUse(FALSE);
		}
	
	} else {

		// This has happended... Msg from Ani not send ????
		if (GetWeaponMode()==NPC_WEAPON_NONE) {
			for (int i=NPC_WEAPON_NONE+1; i<NPC_WEAPON_MAX; i++) {
				if (GetModel()->IsAniActive(anictrl->s_walk[i]) || GetModel()->IsAniActive(anictrl->s_run[i]) || GetModel()->IsAniActive(anictrl->s_sneak[i])) {
					model->StartAni(anictrl->_s_walk);
					return TRUE;
				}
			}
		}
		// **********************************
		// Turnings f�r den Spieler erlauben
		// **********************************
		if (IsSelfPlayer()) human_ai -> PC_Turnings();	

		if (csg->duringRun) {

			if (IsSelfPlayer()) {
				if (!zinput->GetState(GAME_UP)) anictrl->_Stand();
			}
			
			return (!model->IsAniActive(csg->ani));
		
		} else {	
			return (EV_DrawWeapon2(csg));
		}

	}

	return FALSE;
}

zBOOL oCNpc :: EV_DrawWeapon1(oCMsgWeapon* csg)
{
	if (!csg->IsInUse()) {
		oCItem *item  = (oCItem*)GetLeftHand();
		if (GetLeftHand())	DoDropVob(GetLeftHand());
		if (GetRightHand()) DoDropVob(GetRightHand());
		if( item )if(item->HasFlag(ITM_FLAG_TORCH))
		{
			SetTorchAni( FALSE);
		}
		csg->SetInUse	(TRUE);
		anictrl->StopTurnAnis();
	}

  	DoDoAniEvents();
	if (anictrl -> DrawWeapon1(csg->targetMode,csg->useFist,csg->showMagicCircle))
		return TRUE;
	else
		return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_DrawWeapon2()

 

    28-Aug-00       [Roman Keskenti]

                      Weapon may now be drawn whilst in aim-overlay-mode


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_DrawWeapon2(oCMsgWeapon* csg)
{
	if (IsAPlayer())
	{
		if( GetWeaponMode() < NPC_WEAPON_BOW )
		{
			if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModMelee);
			oCNpcFocus::SetFocusMode(FOCUS_MELEE);
		}
		else if( GetWeaponMode() == NPC_WEAPON_MAG )
		{
			if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModMelee);
			oCNpcFocus::SetFocusMode(FOCUS_MAGIC);
		}
		else if( GetWeaponMode() >= NPC_WEAPON_BOW )
		{
			if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModNormal);
			oCNpcFocus::SetFocusMode(FOCUS_RANGED);
		}
	}

	DoDoAniEvents();
	if (!csg->IsInUse()) {
		zCModel* model	= GetModel();
		zSTRING w		= anictrl->GetWeaponString (anictrl->wmode_selected);
		w				= "T_"+w+"_2_"+w+"RUN";
		csg->ani		= model->GetAniIDFromAniName(w);
		
		if (csg->ani!=zMDL_ANI_ID_ILLEGAL) {
			zTModelAniID ani2 = zMDL_ANI_ID_ILLEGAL;
			if (anictrl->GetWalkMode()==ANI_WALKMODE_WATER)		ani2 = model	-> GetAniIDFromAniName("S_" + anictrl->GetWeaponString (anictrl->wmode_selected) + "WALK");
			else												ani2 = model	-> GetAniIDFromAniName("S_" + anictrl->GetWeaponString (anictrl->wmode_selected) + anictrl->GetWalkModeString());
			
			anictrl->StartAni(csg->ani,ani2);
			//model	-> StartAni		(csg->ani);
			//anictrl -> SetNextAni	(csg->ani,ani2);
		} else {
			zERR_WARNING("U: NPC: Ani "+w+" not found. Cannot draw weapon !");
			return TRUE;
		}
		csg	-> SetInUse	(TRUE);
	
	}
	//
	//	CODECHANGE [ROMAN]
	//
	else if (GetModel()->IsAniActive(anictrl->_s_walk) || GetModel()->IsAniActive(anictrl->_s_aim)) {
	//
	//	CODECHANGE [ROMAN] END
	//
		anictrl		-> SetActionMode (ANI_ACTION_STAND);			// =  WMODE_STAND;
		anictrl		-> wmode_last	=  anictrl -> wmode_selected;
		// Skriptreaktion / Waffe ziehen
		if (IsAPlayer()) {			
			CreatePassivePerception	(NPC_PERC_DRAWWEAPON,this);
			// Cutscene State triggern			
		}

		return TRUE;
	}
	return FALSE;
}

zBOOL oCNpc :: EV_RemoveWeapon(oCMsgWeapon* csg)
{
	// Bereits im Normalmodus ?
	// FIXME : Nicht besonders sch�n
	if (csg->firstTime) 
	{
		if (IsMonster() || (GetWeaponMode()==NPC_WEAPON_NONE)) return TRUE;

		oCItem *weapon = zDYNAMIC_CAST<oCItem>(GetRightHand());
		if (weapon && weapon->GetEffect()) weapon->GetEffect()->SetLevel(1,TRUE);

		StandUp(TRUE);
		csg		-> firstTime = FALSE;
		anictrl	-> SetLookAtTarget(NULL);
		anictrl -> StopTurnAnis();
	}
	
	// Fokusmode einstellen
	if (IsSelfPlayer()) {
		oCNpcFocus::focus->SetFocusMode(FOCUS_NORMAL);
		if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModNormal);
	}

	zCModel* model = GetModel();
	DoDoAniEvents();

	if (!csg->initDone) {

		model->StopAnisLayerRange (20, 20);		// turn anis und dialoggesten anis hart stoppen

		int _wmode = GetWeaponMode();

		// Im Laufen ????
//		if ( model->IsAniActive(anictrl->_s_walkl) )

		// FIXME: vorherige version hat S_MAGRUN... nicht gefunde, wieso?
		// (gibt es keine Funktion fuer das hier?) 
		if (// laufen mit waffe
			model->IsAniActive(anictrl->s_run[_wmode])			|| model->IsAniActive(anictrl->t_run_2_runl[_wmode])		|| model->IsAniActive(anictrl->t_runl_2_run[_wmode])		||
			model->IsAniActive(anictrl->s_runl[_wmode])			|| model->IsAniActive(anictrl->t_runl_2_runr[_wmode])		|| model->IsAniActive(anictrl->t_runr_2_runl[_wmode])		||
			model->IsAniActive(anictrl->s_runr[_wmode])			|| model->IsAniActive(anictrl->t_runr_2_run[_wmode])		|| 
			model->IsAniActive(anictrl->t_runturnl[_wmode])		|| model->IsAniActive(anictrl->t_runturnr[_wmode])			|| // ...runstrafe?
			// gehen mit waffe
			model->IsAniActive(anictrl->s_walk[_wmode])			|| model->IsAniActive(anictrl->t_walk_2_walkl[_wmode])		|| model->IsAniActive(anictrl->t_walkl_2_walk[_wmode])		||
			model->IsAniActive(anictrl->s_walkl[_wmode])		|| model->IsAniActive(anictrl->t_walkl_2_walkr[_wmode])		|| model->IsAniActive(anictrl->t_walkr_2_walkl[_wmode])		||
			model->IsAniActive(anictrl->s_walkr[_wmode])		|| model->IsAniActive(anictrl->t_walkr_2_walk[_wmode])		|| 
			model->IsAniActive(anictrl->t_walkturnl[_wmode])	|| model->IsAniActive(anictrl->t_walkturnr[_wmode])			|| // ...walkstrafe?
			// schleichen mit waffe
			model->IsAniActive(anictrl->s_sneak[_wmode])		|| model->IsAniActive(anictrl->t_sneak_2_sneakl[_wmode])	|| model->IsAniActive(anictrl->t_sneakl_2_sneak[_wmode])	||
			model->IsAniActive(anictrl->s_sneakl[_wmode])		|| model->IsAniActive(anictrl->t_sneakl_2_sneakr[_wmode])	|| model->IsAniActive(anictrl->t_sneakr_2_sneakl[_wmode])	||
			model->IsAniActive(anictrl->s_sneakr[_wmode])		|| model->IsAniActive(anictrl->t_sneakr_2_sneak[_wmode])	|| 
			model->IsAniActive(anictrl->t_sneakturnl[_wmode])	|| model->IsAniActive(anictrl->t_sneakturnr[_wmode])		)  // ...sneakstrafe? */
		{
			// **********************************
			// Waffe im Rennen wegstecken 
			// **********************************
			zSTRING w		= anictrl	-> GetWeaponString		(_wmode);
			w				= "T_"+w+"MOVE_2_MOVE";
			csg->ani		= model		-> GetAniIDFromAniName	(w);
			
			if (csg->ani != zMDL_ANI_ID_ILLEGAL) {
				// NachfolgeAni NULL, weil Teilk�rper Ani auf Layer 2
				// csg->ani -> SetNextAni	(NULL);
				model	 -> StartAni	(csg->ani);
				csg		 -> duringRun	= TRUE;
				csg		 -> initDone	= TRUE;
				return FALSE;
			} else {
				// no success....
				zERR_WARNING("U: NPC: Ani "+w+" not found. Cannot remove weapon !");
				return TRUE;
			}

		} else {
			// **********************************
			// Waffe aus dem Stand wegstecken
			// **********************************
			anictrl -> StopTurnAnis();
			csg		-> duringRun = FALSE;
			csg		-> initDone	 = EV_RemoveWeapon1(csg);
		}
	
	} else {
		
		// **********************************
		// Turnings f�r den Spieler erlauben
		// **********************************
		if (IsSelfPlayer()) human_ai -> PC_Turnings();

		if (csg->duringRun) {

			if (IsSelfPlayer()) {
				if (!zinput->GetState(GAME_UP)) anictrl->_Stand();
			}
			
			return (!model->IsAniActive(csg->ani));		
		} else {
			return (EV_RemoveWeapon2(csg));			
		}

	}
	return FALSE;
}

zBOOL oCNpc :: EV_RemoveWeapon1(oCMsgWeapon* csg)
{
	if (IsMonster()) return TRUE;


	DoDoAniEvents();

	anictrl->StopTurnAnis();

	if (anictrl->RemoveWeapon1()) {	
		if (IsAPlayer()) {		
			// Leertaste noch gedr�ckt, dann Magiekranz starten
			if (zinput->KeyPressed(KEY_SPACE) && (anictrl->wmode_selected>=NPC_WEAPON_MAG)) {
				oCMsgMagic* magMsg		= zNEW( oCMsgMagic(oCMsgMagic::EV_OPEN,anictrl->wmode_selected));
				magMsg->removeSymbol	= TRUE;	// show Circle
				GetEM()->OnMessage(magMsg,this);
				// OpenSpellBook(anictrl->wmode_selected);
			}
		}
		return TRUE;
	} else {
		// Safety first....
		if ((GetWeaponMode()==NPC_WEAPON_NONE) && (anictrl->IsStanding())) return TRUE;
		return FALSE;
	}
}

zBOOL oCNpc :: EV_RemoveWeapon2(oCMsgWeapon* csg)
{
	if (IsMonster()) return TRUE;
	

	if (!csg	-> IsInUse()) 
	{
		anictrl -> wmode_selected = csg->targetMode;
		csg		-> SetInUse(TRUE);
		// Schliesse Magiekr�nze
		GetEM()->OnMessage(zNEW( oCMsgMagic(oCMsgMagic::EV_CLOSE,NPC_WEAPON_MAG,TRUE)),this);
		// GetEM()->OnMessage(new oCMsgMagic(oCMsgMagic::EV_CLOSE,NPC_WEAPON_PSI,TRUE),this);
		//CloseSpellBook(NPC_WEAPON_MAG,TRUE);
		//CloseSpellBook(NPC_WEAPON_PSI,TRUE);
		anictrl -> StopTurnAnis();
	}
	DoDoAniEvents();

	// This has happended... Msg from Ani not send ????
	if (GetWeaponMode()!=NPC_WEAPON_NONE)
	{
		if (GetModel()->IsAniActive(anictrl->s_walk[NPC_WEAPON_NONE]) || GetModel()->IsAniActive(anictrl->s_run[NPC_WEAPON_NONE]) || GetModel()->IsAniActive(anictrl->s_sneak[NPC_WEAPON_NONE])) {
			GetModel()->StartAni(anictrl->_s_walk);
			return TRUE;
		}
	}

	if (anictrl -> RemoveWeapon2() || (anictrl->IsStanding() && (GetWeaponMode()==NPC_WEAPON_NONE)) ) 
	{
		// beendet
		if (IsSelfPlayer()) {
			// Skriptreaktion des anvisierten NSCs
			AssessRemoveWeapon_S(this);
		}
		return TRUE;
	}
	return FALSE;
}

zBOOL oCNpc :: EV_ChooseWeapon(oCMsgWeapon* csg)
{
	DoDoAniEvents();
	if (!csg->IsInUse()) {
		anictrl -> ChooseNextWeapon2( csg->targetMode );
		csg		-> SetInUse(TRUE);
	} else if (anictrl->IsStateAniActive(anictrl->s_weapon[GetWeaponMode()])) {
		zSTRING w = "T_" + anictrl->GetWeaponString(GetWeaponMode())+ "_2_" + anictrl->GetWeaponString(anictrl->wmode_selected);
		GetModel()->StartAni (w);
	}
	// Safety....
	if (anictrl->IsStanding()) return TRUE;
	if (anictrl->wmode_selected==0) {
		anictrl->SearchStandAni();
		return TRUE;
	}

	return (anictrl->IsStateAniActive( anictrl->s_weapon[anictrl->wmode_selected]) );
}

zBOOL oCNpc :: EV_ForceRemoveWeapon(oCMsgWeapon* csg)
{
	if (!IsMonster()) {
		if( HasTorch() )
		{
			oCItem *item = GetSlotItem(NPC_NODE_LEFTHAND);
			if( item )
			{
				if( item->HasFlag(ITM_FLAG_TORCH ) )
				{
					SetTorchAni( FALSE );
					oCItem* torch = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,"ITLSTORCH");
					RemoveFromSlot(NPC_NODE_LEFTHAND,FALSE);
					PutInInv(torch);
					zRELEASE( torch );
				}
			}
		}
		oCMag_Book* sb = GetSpellBook();
		
		// Walkmodus kurzeitig auf Standard (RUN) setzen, damit Anis auf jeden Fall intialisiert werden (auch beim Schwimmen / tauchen)
		int oldWalkMode = GetAnictrl()->GetWalkMode();
		if ((oldWalkMode==ANI_WALKMODE_SWIM) || (oldWalkMode==ANI_WALKMODE_DIVE)) GetAnictrl()->SetWalkMode(ANI_WALKMODE_RUN);
		// Sofortiger Wechsel in den Normalmodus ( Waffe poppt weg ) 
		SetWeaponMode2(NPC_WEAPON_NONE);	
		// Walkmode wieder zurueck in alten Mode
		if ((oldWalkMode==ANI_WALKMODE_SWIM) || (oldWalkMode==ANI_WALKMODE_DIVE)) GetAnictrl()->SetWalkMode(oldWalkMode);
		// Falls Magie an, Handsymbol ausschalten
		if (sb) {
			//oCVisualFX* effect	= NULL;
			//oCSpell*	spell	= sb	->GetSelectedSpell();
			// if (spell)	spell  -> Kill();
			// Dichtmachen den Scheiss.
			sb->Close(TRUE);
			sb->SetShowHandSymbol(FALSE);
			
		}
		// FIXME : Autogenerierende Munition ?!?!?!
		// H�nde leeren
		oCItem* item	= GetSlotItem(NPC_NODE_RIGHTHAND);
		if (item) PutInInv((oCItem*)RemoveFromSlot(NPC_NODE_RIGHTHAND));
		item			= GetSlotItem(NPC_NODE_LEFTHAND);
		if (item) PutInInv((oCItem*)RemoveFromSlot(NPC_NODE_LEFTHAND));
		// Fokusmode setzen
		if (IsAPlayer())
		{
			oCNpcFocus::SetFocusMode(FOCUS_NORMAL);

			//
			//	CODECHANGE [ROMAN]
			//
			if (GetHumanAI()) GetHumanAI()->SetCamMode(CamModNormal);
			//
			//	CODECHANGE [ROMAN] END
			//
		}
	}
	return TRUE;
}

zBOOL oCNpc :: EV_EquipBestWeapon(oCMsgWeapon* csg)
{
	EquipBestWeapon(csg->targetMode);
	return TRUE;
}

void oCNpc :: EquipBestWeapon(int targetMode)
{
	oCItem* item		= NULL;
	int		numItems	= 0;
	
	if (targetMode==ITM_CAT_NF) {

//		inventory2.UnpackCategory(INV_COMBAT);
		inventory2.UnpackCategory();
//		numItems = inventory2.GetNumItemsInCategory(INV_COMBAT);
		numItems = inventory2.GetNumItemsInCategory();
		for (int i=0; i<numItems; i++) {
//			item = inventory2.GetItem(INV_COMBAT, i);
			item = inventory2.GetItem(i);
			// Kann Item benutzt werden
			if (CanUse(item) && item->HasFlag(ITM_CAT_NF)) {
				if (!item->HasFlag(ITM_FLAG_ACTIVE)) EquipWeapon(item);
				return;
			}
		}

	} else if (targetMode==ITM_CAT_FF) {

//		inventory2.UnpackCategory(INV_COMBAT);
		inventory2.UnpackCategory();
//		numItems = inventory2.GetNumItemsInCategory(INV_COMBAT);
		numItems = inventory2.GetNumItemsInCategory();
		for (int i=0; i<numItems; i++) {
//			item = inventory2.GetItem(INV_COMBAT, i);
			item = inventory2.GetItem(i);
			// Kann Item benutzt werden
			if (CanUse(item) && item->HasFlag(ITM_CAT_FF) && IsMunitionAvailable(item)) {
				if (!item->HasFlag(ITM_FLAG_ACTIVE)) EquipWeapon(item);
				return;
			}
		}
	}
}

zBOOL oCNpc :: EV_EquipBestArmor(oCMsgWeapon* csg)
{
	EquipBestArmor();
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	oCNpc::EquipBestArmor()

	25-Aug-2000		[Keskenti]	

						Do not equip an armor that is equipped already,
						since this would actually result in unequipping.

   ---------------------------------------------------------------------- */

void oCNpc :: EquipBestArmor()
{
	oCItem* item = NULL;

//	inventory2.UnpackCategory(INV_ARMOR);
	inventory2.UnpackCategory();
//	int numItems = inventory2.GetNumItemsInCategory(INV_ARMOR);
	int numItems = inventory2.GetNumItemsInCategory();
	// Bei Kategorien durchsuchen muss jetzt vorher die Kategory angemeldet werden
	for (int i=0; i<numItems; i++) {
//		item = GetItem(INV_ARMOR, i);
		item = GetItem(0, i);
		// Kann Item benutzt werden
		if (item && CanUse(item) && item->HasFlag(ITM_CAT_ARMOR)) {
			// Trage ich das Teil schon ?
			if ( ! item->HasFlag(ITM_FLAG_ACTIVE) )	EquipArmor(item);
			return;
		}
	}

/* old imp.	
	oCItem* item = NULL;
	zCListSort<oCItem>* node = inventory2.GetFirstNode(INV_ARMOR);
	while (node) {
		item = node->GetData();
		// Kann Item benutzt werden
		if (CanUse(item) && item->HasFlag(ITM_CAT_ARMOR)) {
			// Trage ich das Teil schon ?
			if ( ! item->HasFlag(ITM_FLAG_ACTIVE) )	EquipArmor(item);
			return;
		}
		node = node -> GetNextInList();
	}*/
}

zBOOL oCNpc :: EV_UnequipWeapons(oCMsgWeapon* csg)
{
	oCItem *item = GetEquippedMeleeWeapon();
	if (item)
		UnequipItem(item);
	
	item = GetEquippedRangedWeapon(); 
	if (item)
		UnequipItem(item);
	
	return TRUE;	
}

zBOOL oCNpc :: EV_UnequipArmor(oCMsgWeapon* csg)
{
	oCItem *item = GetEquippedArmor();
	// Item gefuenden, dann removen
	if (item) EquipArmor(item);
	return TRUE;	
}

/* ----------------------------------------------------------------------
	
	EV_EquipArmor()

	25.08.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

zBOOL oCNpc :: EV_EquipArmor(oCMsgWeapon* csg)
{
	oCItem*	item = IsInInv( csg->GetObjectName() );		if ( ! item ) return TRUE;

	if (CanUse(item) && item->HasFlag(ITM_CAT_ARMOR))
		EquipArmor(item);

	return TRUE;	
}


// *************************
// Attacks 
// *************************

/*--------------------------------------------------------------------------

    oCNpc::EV_AttackForward()

 

    07-Sep-00       [Roman Keskenti]

                      Added enemy's defense-handling


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_AttackForward		(oCMsgAttack* csg)
{

//changed[dennis]
	zCModel* model = GetModel();
	if (!csg -> IsInUse () && (csg->hitAni!=zMDL_ANI_ID_ILLEGAL)) 
	{
		csg			 -> SetInUse	(TRUE);
		anictrl		 -> StopTurnAnis();

		//
		//	CODECHANGE [ROMAN]
		//
		oCNpc* pEnemy = GetEnemy();

		if (IsSelfPlayer()) anictrl -> StartHitCombo (csg->hitAni,GetFocusVob());
		else				anictrl -> StartHitCombo (csg->hitAni,pEnemy);

		if ( pEnemy )
		if ( pEnemy->isDefending )
		{
			pEnemy->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,anictrl->_t_hitr)),pEnemy);
			pEnemy->didParade = TRUE;
		}
		//
		//	CODECHANGE [ROMAN]
		//
	}
	else 
	{
		// Check Hit

		if( IsSelfPlayer() )
		{

			if (!oCGame::GetUseOldControls())
			{
				// [BENDLIN] 2002-06-18, back to old fight controls
				zBOOL keyAttackRight	= zinput->GetToggled(GAME_ACTIONRIGHT);
				zBOOL keyAttackLeft		= zinput->GetToggled(GAME_ACTIONLEFT);
				zBOOL actionToggled     = zinput->GetToggled(GAME_ACTION);

				human_ai -> PC_Turnings();	

				// wurde w�hrend des Combo Fensters die Up Taste gedr�ckt, so kann man weitergehen
				if( zinput->GetState(GAME_UP) && zinput->GetToggled(GAME_UP) && (anictrl->IsInCombo() || anictrl->IsInPostHit()) )
				{
					model->StartAni(anictrl->_s_walk);	
					return TRUE;
				}
				// wurde w�hrend des Combo Fensters die Down Taste gedr�ckt, so kann man weitergehen
				if( zinput->GetState(GAME_DOWN) && zinput->GetToggled(GAME_DOWN) && (anictrl->IsInCombo() || anictrl->IsInPostHit()) )
				{
					model->StartAni(anictrl->_s_walk);	
					return TRUE;
				}
				if (actionToggled)
				{
					anictrl -> HitCombo(TRUE);
				}
				if( zinput->GetState(GAME_STRAFERIGHT) && zinput->GetToggled(GAME_STRAFERIGHT) && (anictrl->IsInCombo() || anictrl->IsInPostHit())  )
				{
					oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,oCNpc::player->GetFocusNpc()));
					msg -> ani			= anictrl->_t_strafer;
					oCNpc::player -> GetEM() -> OnMessage(msg,oCNpc::player);					
					return TRUE;
				} 
				else if (zinput->GetState(GAME_STRAFELEFT) && zinput->GetToggled(GAME_STRAFELEFT) && (anictrl->IsInCombo() || anictrl->IsInPostHit())  )
				{
					oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,oCNpc::player->GetFocusNpc()));
					msg -> ani			= anictrl->_t_strafel;
					oCNpc::player -> GetEM() -> OnMessage(msg,oCNpc::player);					
					return TRUE;
				}
				if (keyAttackRight && anictrl->comboNr == 0)
				{
					if (anictrl->IsInCombo())
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT,anictrl->_t_hitr)),this);
						return TRUE;
					}
				}
				// [BENDLIN] 2002-06-18, nach dem ersten Schlag ist die Hand oben links
				if ( keyAttackRight && (anictrl->comboNr == 0) )
				{
					if ( anictrl->IsInCombo() )
					{
						GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT, anictrl->_t_hitr)), this);
						return TRUE;
					}
				}
				// [BENDLIN] 2002-06-18, nach dem zweiten/dritten Schlag ist die Hand oben rechts
				else if ( keyAttackLeft && (anictrl->comboNr == 1 || anictrl->comboNr == 2) ) 
				{
					if ( anictrl->IsInCombo() )
					{
						GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT, anictrl->_t_hitl)), this);
						return TRUE;
					}
				}
				else if (keyAttackLeft && anictrl->comboNr == 0)
				{
					if (anictrl->IsInCombo())
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT,anictrl->_t_hitl)),this);
						return TRUE;
					}
				}
				if (zinput->GetState(GAME_PARADE))
				{
					if (anictrl->IsInCombo() || anictrl->IsInPostHit())
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,GetFocusNpc())),this);
						return TRUE;
					}
				}
				/*else if (attackEnd)
				{
					if (anictrl->IsInCombo() || anictrl->IsInPostHit()) 
					{	
						model->StartAni(anictrl->_s_walk);	
						return TRUE;
					}
				}*/
			}
			else
			{

				zBOOL keyAttackRight	= zinput->GetToggled(GAME_RIGHT) || zinput->GetToggled(GAME_STRAFERIGHT);  // [BENDLIN] Auch bei STRAFE Drehschlag
				zBOOL keyAttackLeft		= zinput->GetToggled(GAME_LEFT) || zinput->GetToggled(GAME_STRAFELEFT);  // [BENDLIN] Auch bei STRAFE Drehschlag
				zBOOL attackEnd			= zinput->GetState(GAME_UP)	&& !zinput->GetState(GAME_ACTION) && !keyAttackRight && !keyAttackLeft;
				
				if ( !attackEnd )
				{
					human_ai->PC_Turnings();	

					if ( zinput->GetToggled(GAME_UP) )
					{
				 		anictrl->HitCombo(TRUE);
					}

				}
				
				if ( !attackEnd && (anictrl->IsInCombo() || anictrl->IsInPostHit()) )  // [BENDLIN] Auch bei STRAFE Drehschlag
				{
					// [BENDLIN] 2002-06-18, FIXME: Strafe aus Kombo-Fenster -> sauber aus der Kombo raus ohne Schlag!
					if ( zinput->GetState(GAME_STRAFERIGHT) )
					{
						model->StartAni(anictrl->_s_walk);	
						// strafe right
						oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, oCNpc::player->GetFocusNpc()));
						msg->ani = anictrl->_t_strafer;
						oCNpc::player->GetEM()->OnMessage(msg, oCNpc::player);
						return TRUE;
					} 
					else if ( zinput->GetState(GAME_STRAFELEFT) )
					{
						model->StartAni(anictrl->_s_walk);	
						// strafe right
						oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, oCNpc::player->GetFocusNpc()));
						msg->ani = anictrl->_t_strafel;
						oCNpc::player->GetEM()->OnMessage(msg, oCNpc::player);					
						return TRUE;
					}
				}

				// [BENDLIN] 2002-06-18, nach dem ersten Schlag ist die Hand oben links
				if ( keyAttackRight && (anictrl->comboNr == 0) )
				{
					if ( anictrl->IsInCombo() )
					{
						GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT, anictrl->_t_hitr)), this);
						return TRUE;
					}
				}
				// [BENDLIN] 2002-06-18, nach dem zweiten/dritten Schlag ist die Hand oben rechts
				else if ( keyAttackLeft && (anictrl->comboNr == 1 || anictrl->comboNr == 2) ) 
				{
					if ( anictrl->IsInCombo() )
					{
						GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT, anictrl->_t_hitl)), this);
						return TRUE;
					}
				}

				if ( zinput->GetState(GAME_DOWN) )
				{
					if ( anictrl->IsInCombo() || anictrl->IsInPostHit() )
					{
						GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_PARADE, GetFocusNpc())), this);
						return TRUE;
					}
				}
				else if ( attackEnd )
				{
					if ( anictrl->IsInCombo() || anictrl->IsInPostHit() ) 
					{	
						model->StartAni(anictrl->_s_walk);	
						return TRUE;
					}
				} 
			}
		} 
		else 
		{
			// ********
			//  NSC AI
			// ********
			if (csg->combo == -1) 
			{
				// ComboVerhalten : -1  = Bis zum Erreichen des Zeitfensters und dann Messagea aus, 
				// weil dann naechtse aktiv werden soll (Kombo)
				if (anictrl->IsInCombo()) 
				{
					model->StartAni(anictrl->_s_walk);	
					return TRUE;
				}
				anictrl->HitCombo(FALSE);

			} else if ((csg->combo-1) < anictrl -> comboNr) 
			{
				// Ansonsten gibt Combo Anzahl der combos an, die gespielt werden d�rfen...
				anictrl->HitCombo(TRUE);

			} else 
			{
				anictrl->HitCombo(FALSE);
			}
			
			if (GetEnemy()) 
			{
				zVEC3 pos = GetEnemy()->GetPositionWorld();
				Turn(pos);
			}
		}
	}

	oCItem *weapon = 0;
	if (fmode<=NPC_WEAPON_2HS)	weapon = GetSlotItem(NPC_NODE_RIGHTHAND);		
	if (anictrl->CheckMeleeWeaponHitsLevel(weapon))
	{
		//zERR_WARNING("C: weapon hits level");
	}

	anictrl->HitCombo(FALSE);

	SetBodyState(BS_HIT);
	if (!model->IsAniActive(csg->hitAni)) 
	{
		return TRUE;	
	}
	else return FALSE;

}

/*--------------------------------------------------------------------------

    oCNpc::EV_AttackLeft()

 

    07-Sep-00       [Roman Keskenti]

                      Added enemy's defense-handling


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_AttackLeft		(oCMsgAttack* csg)
{
	//changed[dennis]
	zCModel* model = GetModel();
	if (!csg -> IsInUse () && csg->hitAni) {
		csg			 -> SetInUse	(TRUE);
		anictrl		 -> StopTurnAnis();
	
		//
		//	CODECHANGE [ROMAN]
		//
		oCNpc* pEnemy = GetEnemy();

		if (IsSelfPlayer()) anictrl -> StartHitCombo (csg->hitAni,GetFocusVob());
		else				anictrl -> StartHitCombo (csg->hitAni,pEnemy);

		if ( pEnemy )
		if ( pEnemy->isDefending )
		{
			pEnemy->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,anictrl->_t_hitr)),pEnemy);
			pEnemy->didParade = TRUE;
		}
		//
		//	CODECHANGE [ROMAN]
		//

	} else {
		// Check Hit
		if( IsSelfPlayer() )
		{

			if (!oCGame::GetUseOldControls())
			{			
				zBOOL keyAttackRight	= zinput->GetToggled(GAME_ACTIONRIGHT);
				zBOOL keyAttackLeft		= zinput->GetToggled(GAME_ACTIONLEFT);

				if (zinput->GetState(GAME_ACTION))
				{
					if( anictrl ->IsInCombo() && anictrl->canEnableNextCombo )
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD,anictrl->_t_hitf)),this);
						return TRUE;
					}
					else anictrl->canEnableNextCombo = FALSE;
				}
				else if (keyAttackRight)
				{
					if( anictrl ->IsInCombo() && anictrl->canEnableNextCombo )
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT,anictrl->_t_hitr)),this);
						return TRUE;
					}
					else anictrl->canEnableNextCombo = FALSE;
				}
				else if (keyAttackLeft)
				{
					if( GetEM()->GetActiveMessage()->GetSubType() != oCMsgAttack::EV_ATTACKLEFT ) 
						anictrl->HitCombo(TRUE);
				}
				else if (zinput->GetState(GAME_PARADE))
				{
					if (anictrl ->IsInCombo() || anictrl->IsInPostHit())
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,GetFocusNpc())),this);
						return TRUE;
					}
					else anictrl->canEnableNextCombo = FALSE;
				}
				else anictrl->HitCombo(FALSE);
				
				if(  zinput->GetState(GAME_SMOVE) )
				{
					zBOOL keyAttackRight	= zinput->GetToggled(GAME_RIGHT)  || zinput->GetToggled(GAME_STRAFERIGHT);
					zBOOL keyAttackLeft		= zinput->GetToggled(GAME_LEFT)	  || zinput->GetToggled(GAME_STRAFELEFT);
				
					if (keyAttackLeft)
					{
						if( anictrl->IsInCombo() || anictrl->IsInPostHit())
						{
							oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,oCNpc::player->GetFocusNpc()));
							msg -> ani			= anictrl->_t_strafel;
							oCNpc::player -> GetEM() -> OnMessage(msg,oCNpc::player);					
							return TRUE;
						}
					}
					else if (keyAttackRight)
					{
						if( anictrl->IsInCombo() || anictrl->IsInPostHit())
						{
							oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,oCNpc::player->GetFocusNpc()));
							msg -> ani			= anictrl->_t_strafer;
							oCNpc::player -> GetEM() -> OnMessage(msg,oCNpc::player);					
							return TRUE;
						}
					}
				
				} 
				/*else {
					if (anictrl->IsInCombo() || anictrl->IsInPostHit()) {
						
						model->StartAni(anictrl->_s_walk);	
						return TRUE;
					
					}
				}	*/
			}
			else
			{
				zBOOL keyAttackRight	= zinput->GetToggled(GAME_RIGHT) || zinput->GetToggled(GAME_STRAFERIGHT);  // [BENDLIN] Auch bei STRAFE Drehschlag
				zBOOL keyAttackLeft		= zinput->GetToggled(GAME_LEFT) || zinput->GetToggled(GAME_STRAFELEFT);  // [BENDLIN] Auch bei STRAFE Drehschlag

				if ( zinput->GetState(GAME_ACTION) )
				{				
					if ( zinput->GetState(GAME_UP) )
					{
						if ( anictrl->IsInCombo() && anictrl->canEnableNextCombo )
						{
							zinput->GetToggled(GAME_UP);
							GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, anictrl->_t_hitf)), this);
							//anictrl->StartAni(anictrl->_t_hitf);
							return TRUE;
						}
						else anictrl->canEnableNextCombo = FALSE;
					}
					else if ( keyAttackRight )
					{
						if ( anictrl->IsInCombo() && anictrl->canEnableNextCombo )
						{
							GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT, anictrl->_t_hitr)), this);
							//anictrl->StartAni(anictrl->_t_hitr);
							return TRUE;
						}
						else anictrl->canEnableNextCombo = FALSE;
					}
					else if ( zinput->GetState(GAME_DOWN) )
					{
						if ( anictrl ->IsInCombo() || anictrl->IsInPostHit() )
						{
							GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_PARADE, GetFocusNpc())), this);
							return TRUE;
						}
						else anictrl->canEnableNextCombo = FALSE;
					}
					else if ( keyAttackLeft )
					{
						if ( GetEM()->GetActiveMessage()->GetSubType() != oCMsgAttack::EV_ATTACKLEFT ) 
							anictrl->HitCombo(TRUE);
					}
					else anictrl->HitCombo(FALSE);
				}
				else if (  zinput->GetState(GAME_SMOVE) )
				{
					zBOOL keyAttackRight	= zinput->GetToggled(GAME_RIGHT)  || zinput->GetToggled(GAME_STRAFERIGHT);
					zBOOL keyAttackLeft		= zinput->GetToggled(GAME_LEFT)	  || zinput->GetToggled(GAME_STRAFELEFT);
				
					if ( keyAttackLeft )
					{
						if ( anictrl->IsInCombo() || anictrl->IsInPostHit() )
						{
							oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, oCNpc::player->GetFocusNpc()));
							msg->ani = anictrl->_t_strafel;
							oCNpc::player->GetEM()->OnMessage(msg, oCNpc::player);					
							return TRUE;
						}
					}
					else if ( keyAttackRight )
					{
						if ( anictrl->IsInCombo() || anictrl->IsInPostHit() )
						{
							oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, oCNpc::player->GetFocusNpc()));
							msg->ani = anictrl->_t_strafer;
							oCNpc::player->GetEM()->OnMessage(msg, oCNpc::player);					
							return TRUE;
						}
					}
				}
				else
				{
					if ( anictrl->IsInCombo() || anictrl->IsInPostHit() )
					{
						model->StartAni(anictrl->_s_walk);	
						return TRUE;
					}
				}
			}
		}
		else
		{
			// ********
			//  NSC AI
			// ********
			
			if ((csg->combo == -1) && anictrl->IsInCombo()) return TRUE;
			// ComboVerhalten : -1  = Bis zum Erreichen des Zeitfensters und dann Messagea aus, 
			// weil dann naechtse aktiv werden soll (Kombo)
			anictrl->HitCombo(FALSE);
		}
	}

	oCItem *weapon = 0;
	if (fmode<=NPC_WEAPON_2HS)	weapon = GetSlotItem(NPC_NODE_RIGHTHAND);		
	if (anictrl->CheckMeleeWeaponHitsLevel(weapon))
	{
		//zERR_WARNING("C: weapon hits level");
	}


	SetBodyState(BS_HIT);
	return (!model->IsAniActive(csg->hitAni));
}

/*--------------------------------------------------------------------------

    oCNpc::EV_AttackRight()

 

    07-Sep-00       [Roman Keskenti]

                      Added enemy's defense-handling


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_AttackRight		(oCMsgAttack* csg)
{
	//changed[dennis]
	zCModel* model = GetModel();
	if (!csg -> IsInUse () && csg->hitAni) {
		csg			 -> SetInUse	(TRUE);
		anictrl		 -> StopTurnAnis();

		//
		//	CODECHANGE [ROMAN]
		//
		oCNpc* pEnemy = GetEnemy();

		if (IsSelfPlayer()) anictrl -> StartHitCombo (csg->hitAni,GetFocusVob());
		else				anictrl -> StartHitCombo (csg->hitAni,pEnemy);

		if ( pEnemy )
		if ( pEnemy->isDefending )
		{
			pEnemy->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,anictrl->_t_hitr)),pEnemy);
			pEnemy->didParade = TRUE;
		}
		//
		//	CODECHANGE [ROMAN]
		//
	
	} else 
	{
		// Check Hit
		if( IsSelfPlayer() )
		{
			if (!oCGame::GetUseOldControls())
			{
				zBOOL keyAttackRight	= zinput->GetToggled(GAME_ACTIONRIGHT);
				zBOOL keyAttackLeft		= zinput->GetToggled(GAME_ACTIONLEFT);

				if (zinput->GetState(GAME_ACTION))
				{
					if( anictrl ->IsInCombo() && anictrl->canEnableNextCombo )
					{	
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD,anictrl->_t_hitf)),this);
						//anictrl->StartAni(anictrl->_t_hitf);
						return TRUE;
					}
					else anictrl->canEnableNextCombo = FALSE;
				}
				else if (keyAttackLeft)
				{
					if( anictrl ->IsInCombo() && anictrl->canEnableNextCombo )
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT,anictrl->_t_hitl)),this);
						return TRUE;
					}
					else anictrl->canEnableNextCombo = FALSE;
				}
				else if (zinput->GetState(GAME_PARADE))
				{
					if( anictrl ->IsInCombo() || anictrl->IsInPostHit())
					{
						GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,GetFocusNpc())),this);
						return TRUE;
					}
					else anictrl->canEnableNextCombo = FALSE;
				}
				else if (keyAttackRight)
				{
					if( GetEM()->GetActiveMessage()->GetSubType() != oCMsgAttack::EV_ATTACKRIGHT ) 
						anictrl->HitCombo(TRUE);
				}
				else anictrl->HitCombo(FALSE);
				
				
				if(  zinput->GetState(GAME_SMOVE) )
				{
					if (keyAttackLeft)
					{
						if( anictrl->IsInCombo() || anictrl->IsInPostHit())
						{
							oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,oCNpc::player->GetFocusNpc()));
							msg -> ani			= anictrl->_t_strafel;
							oCNpc::player -> GetEM() -> OnMessage(msg,oCNpc::player);					
							return TRUE;
						}
					}
					else if (keyAttackRight)
					{
						if( anictrl->IsInCombo() || anictrl->IsInPostHit())
						{
							oCMsgMovement* msg	= zNEW( oCMsgMovement(oCMsgMovement::EV_STRAFE,oCNpc::player->GetFocusNpc()));
							msg -> ani			= anictrl->_t_strafer;
							oCNpc::player -> GetEM() -> OnMessage(msg,oCNpc::player);					
							return TRUE;
						}
					}
				}
				/*else if (anictrl->IsInCombo() || anictrl->IsInPostHit()) {
					
					model->StartAni(anictrl->_s_walk);	
					return TRUE;
				};*/
			}
			else
			{
				zBOOL keyAttackRight	= zinput->GetToggled(GAME_RIGHT) || zinput->GetToggled(GAME_STRAFERIGHT);  // [BENDLIN] Auch bei STRAFE Drehschlag
				zBOOL keyAttackLeft		= zinput->GetToggled(GAME_LEFT) || zinput->GetToggled(GAME_STRAFELEFT);  // [BENDLIN] Auch bei STRAFE Drehschlag

				if ( zinput->GetState(GAME_ACTION) )
				{
					if ( zinput->GetState(GAME_UP) )
					{
						if ( anictrl->IsInCombo() && anictrl->canEnableNextCombo )
						{
							zinput->GetToggled(GAME_UP);
							GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, anictrl->_t_hitf)), this);
							//anictrl->StartAni(anictrl->_t_hitf);
							return TRUE;
						}
						else anictrl->canEnableNextCombo = FALSE;
					}
					else if ( keyAttackLeft )
					{
						if ( anictrl->IsInCombo() && anictrl->canEnableNextCombo )
						{
							GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT, anictrl->_t_hitl)), this);
							//anictrl->StartAni(anictrl->_t_hitl);
							return TRUE;
						}
						else anictrl->canEnableNextCombo = FALSE;
					}
					else if ( zinput->GetState(GAME_DOWN) )
					{
						if ( anictrl ->IsInCombo() || anictrl->IsInPostHit() )
						{
							GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_PARADE,GetFocusNpc())), this);
							return TRUE;
						}
						else anictrl->canEnableNextCombo = FALSE;
					}
					else if ( keyAttackRight )
					{
						if ( GetEM()->GetActiveMessage()->GetSubType() != oCMsgAttack::EV_ATTACKRIGHT ) 
							anictrl->HitCombo(TRUE);
					}
					else anictrl->HitCombo(FALSE);
				}
				else if ( zinput->GetState(GAME_SMOVE) )
				{
					if ( keyAttackLeft )
					{
						if ( anictrl->IsInCombo() || anictrl->IsInPostHit() )
						{
							oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, oCNpc::player->GetFocusNpc()));
							msg->ani = anictrl->_t_strafel;
							oCNpc::player->GetEM()->OnMessage(msg, oCNpc::player);					
							return TRUE;
						}
					}
					else if ( keyAttackRight )
					{
						if ( anictrl->IsInCombo() || anictrl->IsInPostHit() )
						{
							oCMsgMovement* msg = zNEW(oCMsgMovement(oCMsgMovement::EV_STRAFE, oCNpc::player->GetFocusNpc()));
							msg->ani = anictrl->_t_strafer;
							oCNpc::player->GetEM()->OnMessage(msg, oCNpc::player);					
							return TRUE;
						}
					}
				}
				else if ( anictrl->IsInCombo() || anictrl->IsInPostHit() )
				{
					model->StartAni(anictrl->_s_walk);	
					return TRUE;
				};
			}
		}
		else
		{
			// ********
			//  NSC AI
			// ********			
			if ((csg->combo == -1) && anictrl->IsInCombo()) return TRUE;
			// ComboVerhalten : -1  = Bis zum Erreichen des Zeitfensters und dann Messagea aus, 
			// weil dann naechtse aktiv werden soll (Kombo)
			anictrl->HitCombo(FALSE);
		}
	}

	oCItem *weapon = 0;
	if (fmode<=NPC_WEAPON_2HS)	weapon = GetSlotItem(NPC_NODE_RIGHTHAND);		
	if (anictrl->CheckMeleeWeaponHitsLevel(weapon))
	{
		//zERR_WARNING("C: weapon hits level");
	}


	SetBodyState(BS_HIT);
	return (!model->IsAniActive(csg->hitAni));

}

/*--------------------------------------------------------------------------

    oCNpc::EV_AttackRun()

 

    07-Sep-00       [Roman Keskenti]

                      Added enemy's defense-handling


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_AttackRun			(oCMsgAttack* csg)
{
	zCModel* model = GetModel();

	if (!csg  -> IsInUse () && csg->hitAni) {
		csg			 -> SetInUse	(TRUE);
		anictrl		 -> StopTurnAnis();

		//
		//	CODECHANGE [ROMAN]
		//
		oCNpc* pEnemy = GetEnemy();

		if (IsSelfPlayer()) anictrl -> StartHitCombo (csg->hitAni,GetFocusVob());
		else				anictrl -> StartHitCombo (csg->hitAni,pEnemy);

		if ( pEnemy )
		if ( pEnemy->isDefending )
		{
			pEnemy->GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,anictrl->_t_hitr)),pEnemy);
			pEnemy->didParade = TRUE;
		}
		//
		//	CODECHANGE [ROMAN]
		//
	
	} else {
		

		human_ai -> PC_Turnings();	

		anictrl -> HitCombo(FALSE);		

		if (IsSelfPlayer()) {
			if (!zinput->GetState(GAME_UP)) {
				model->StartAni(anictrl->_s_walk);
			}		
		}

	}

	oCItem *weapon = 0;
	if (fmode<=NPC_WEAPON_2HS)	weapon = GetSlotItem(NPC_NODE_RIGHTHAND);		
	if (anictrl->CheckMeleeWeaponHitsLevel(weapon))
	{
		//zERR_WARNING("C: weapon hits level");
	}
	
	SetBodyState(BS_HIT);
	return (!model->IsAniActive(csg->hitAni));
}

zBOOL oCNpc :: EV_AttackFinish	(oCMsgAttack* csg)
{
	//
	//	EVALUATE TARGET POSITION
	//
	int nFinishDistance = 180;

	zCPar_Symbol* pSymbol = ::parser.GetSymbol( "NPC_ATTACK_FINISH_DISTANCE" );
	if ( pSymbol ) pSymbol->GetValue( nFinishDistance );

	// NOTE finish direction calculation
	zVEC3 posTarget = csg->target->GetPositionWorld();
	zVEC3 posSelf	= this		 ->GetPositionWorld();
	zVEC3 vecDir	= posTarget - posSelf;
		  vecDir	.NormalizeApprox();
		  vecDir   *= zREAL( nFinishDistance );
	zVEC3 posDest	= posTarget - vecDir;

	//
	//	1ST PASS [MOVEMENT]
	//
	if ( ! csg->IsInUse() )
	{
		oCNpc* pTargetNpc = zDYNAMIC_CAST< oCNpc > (csg->target);	if ( ! pTargetNpc ) return TRUE;


		//
		//	IF TARGETS TIME IS RUN UP -> DO NOT TRY TO FINISH HIM OR ELSE HE WILL STAND UP IN BETWEEN
		//
		int nSecondsUnconscious = 20;
		zCPar_Symbol* pSymbol = ::parser.GetSymbol( "HAI_TIME_UNCONSCIOUS" );
		if ( pSymbol ) pSymbol->GetValue( nSecondsUnconscious );

		if ( pTargetNpc->GetAIStateTime() > ( nSecondsUnconscious - 1 ) ) return TRUE;

		//
		//	KEEP TARGET LOCKED	[AIStateTime for ZS_UNCONSCIOUS]
		//
		pTargetNpc->state.SetStateTime( 0 );

		if (IsAPlayer())
		{
			SetFocusVob(pTargetNpc);	
		};

		//
		//	GOTO TARGET
		//
		oCMsgMovement* msg = zNEW( oCMsgMovement(oCMsgMovement::EV_GOTOPOS, posDest ) );
		msg -> SetHighPriority(TRUE);
		GetEM()->OnMessage(msg,NULL);
		csg->SetInUse(TRUE);
		csg->reachedTarget = FALSE;

		return FALSE;
	}

	//
	//	2ND PASS [ORIENTATION]
	//
	if (!csg->reachedTarget) 
	{
		//
		//	CORRECT POSITION
		//
		this->SetPositionWorld( posDest );

		//
		//	START VICTIM's ANIMATION
		//
		zCModel* model = GetModel();
		if ( csg->hitAni )
		{
			this->GetAnictrl()->StopTurnAnis();
			model	-> StartAni	(csg->hitAni);
			// Victim Anis starten !
			oCNpc* enemy = zDYNAMIC_CAST<oCNpc>(csg->target);
			if (enemy && enemy->IsUnconscious()) 
			{
				// Und noch eine lustige TodesAni anschmeissen
				zCModel* enemyModel = enemy->GetModel();
				if (enemyModel) {
					if (enemyModel->IsAniActive("S_WOUNDED"))	enemyModel->StartAni("T_WOUNDED_2_DEAD");	else
					if (enemyModel->IsAniActive("S_WOUNDEDB"))	enemyModel->StartAni("T_WOUNDEDB_2_DEADB"); 
				}
			}	
		}

		if (IsAPlayer())
		{
			oCNpc* pTargetNpc = zDYNAMIC_CAST< oCNpc > (csg->target);
			if (pTargetNpc) SetFocusVob(pTargetNpc);	
		};

		csg->reachedTarget = TRUE;
		SetBodyState(BS_HIT);
	}

	zCModel* model = GetModel();

	//
	//	nTH PASS [KILL]
	//
	if ( model->IsAniActive(csg->hitAni) ) 
	{	
		//
		//	CORRECT HEADING
		//
		this->SetHeadingYWorld( csg->target->GetPositionWorld() );

		//
		//	VICTIMs DEATH
		//

		if (IsAPlayer())
		{
			oCNpc* pTargetNpc = zDYNAMIC_CAST< oCNpc > (csg->target);
			if (pTargetNpc) SetFocusVob(pTargetNpc);	
		};

		zREAL fr = model->GetProgressPercent(csg->hitAni);
		if (fr>=0.5) 
		{
			// Gegner tot !
			oCNpc* enemy = zDYNAMIC_CAST<oCNpc>(csg->target);
			if (enemy && enemy->IsUnconscious()) 
			{
				//
				//	HITPOINTS AUF "0"
				//
				enemy->SetAttribute(NPC_ATR_HITPOINTS,0);

				//
				//	STERBEN
				//
				enemy->DoDie(this);

				// Partikeleffekt erzeugen 
				// FIXME : Blutfarbe
				// FIXME : Blut abstellen
				enemy->GetAnictrl()->AddBlood(enemy->GetPositionWorld(),zVEC3(0,-1000,0),100.0f,TRUE, &this->bloodTexture /*&zSTRING("ZBLOODSPLAT2.TGA")*/);

				//
				//	SCHADENSBESCHREIBUNG ERSTELLEN
				//
				oCNpc::oSDamageDescriptor descDamage;
				::memset( &descDamage, 0, sizeof ( oCNpc::oSDamageDescriptor ) );
				descDamage.bIsDead = TRUE;

				//
				//	ENTSPRECHENDEN SOUND SPIELEN
				//
				enemy->OnDamage_Sound( descDamage );
			}
		}
	}
	return (!model->IsAniActive(csg->hitAni));
}

zBOOL oCNpc :: EV_Parade(oCMsgAttack* csg)
// csg->targetVob = zu parierender Gegner
{
	zCArray<zCModelAniEvent*> events;

	zCModel* model = GetModel();

	if (!csg -> IsInUse()) {

		zREAL dist;
		zSTRING attackDir;
		oCNpc* enemy = GetEnemy();
		if (enemy && enemy->IsInFightRange(this,dist) && enemy->IsInFightFocus(this)) {
			// In einem Angriff -> wenn ja, welcher Angriff, welche ComboNr
			// aus welcher Richtung geht der Schlag ein
			attackDir = enemy->GetAnictrl()->GetHitDirection();
			//zERR_MESSAGE(5,0, "C: Parade: calc attackdir from enemy");
		}
		if (attackDir.IsEmpty()) attackDir = "0";
		
		// Ani suchen
		zSTRING s		= anictrl->GetWeaponString		(GetWeaponMode());

		if ( !csg->reachedTarget )
		{
			int randomParadeNum = zRand(3)+1;

			if ( randomParadeNum>1 )
			{
				csg	-> hitAni	= model->GetAniIDFromAniName	("T_"+s+"PARADE_"+attackDir+"_A"+zSTRING(randomParadeNum));
				
				if (csg->hitAni == zMDL_ANI_ID_ILLEGAL) 
				{
					csg	-> hitAni	= model->GetAniIDFromAniName	("T_"+s+"PARADE_"+attackDir);
				}
			}
			else csg	-> hitAni	= model->GetAniIDFromAniName	("T_"+s+"PARADE_"+attackDir);
		}
		else
		{
			csg	-> hitAni	= model->GetAniIDFromAniName	("T_"+s+"PARADEJUMPB");
		}

		if ( csg->hitAni == zMDL_ANI_ID_ILLEGAL ) return TRUE;

		csg		-> SetInUse			(TRUE);
		anictrl -> StartHitCombo	(csg->hitAni, NULL);
		GetAnictrl()->StopTurnAnis();

		// perc_assess_damage ausloesen
		this->AssessDamage_S( enemy, 0 );
	}
	else if (IsSelfPlayer()) 
	{
		// [Ulf] - 30.01.01 - Waehrend einer Parade Ausrichtung zum Gegener beibehalten
		human_ai -> PC_Turnings();	
		// [BENDLIN] 2002-06-18, back to old fight controls
		if ( oCGame::GetUseOldControls() )
		{
			if ( zinput->GetState(GAME_ACTION) )
			{
				TurnToEnemy();
			}
			else
			{

			};
		}
	}

	SetBodyState(BS_PARADE);
	zBOOL res = !model->IsAniActive(csg->hitAni);
	
	if (!res) 
	{
		// ani noch aktiv, falls sich der frame im combo fenster befindet, darf die ani noch nicht
		// abgebrochen werden
		if ( !GetAnictrl()->IsInCombo() ) return TRUE;
	}
	return ( res );
}

//
//	CODECHANGE [ROMAN]
//

/*--------------------------------------------------------------------------

    oCNpc::InitAim()

 

    24-Aug-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/
zBOOL oCNpc :: InitAim( oCMsgAttack* csg, oCNpc** pEnemy, zBOOL *pDrawn, zBOOL *pAmmo, zBOOL bKillFormerMsg )
{
	//
	//	NOCH EIN GEGNER DA?
	//
	if ( pEnemy ) 
	{
		(*pEnemy) = zDYNAMIC_CAST<oCNpc> (csg->target);
		if ( !(*pEnemy) ) (*pEnemy) = this->GetEnemy();		// try to get target from message. if there's no target attached to the message, use the current enemy as target.

		if ( (*pEnemy) )
			if ((*pEnemy)->IsDead()) (*pEnemy) = NULL;
	}

	//
	//	RANGE WAFFEN GEZOGEN?
	//
	if ( pDrawn )
	{
		(*pDrawn) =  ( ( this->GetWeaponMode() == NPC_WEAPON_BOW  ) 
					|| ( this->GetWeaponMode() == NPC_WEAPON_CBOW ) );
	}

	//
	//	AMMO FUER DIE WAFFE VERFUEGBAR?
	//
	if ( pAmmo )
	{
		(*pAmmo) = this->IsMunitionAvailable( this->GetWeapon() );
	}

	//
	//	GLEICHE ATTACK MESSAGE SCHON IN DER QUEUE?
	//
	if ( bKillFormerMsg )
	{
		oCMsgAttack*	pMsgAttack	= NULL;

		for ( int nMessage = 0; nMessage < GetEM()->GetNumMessages(); nMessage++ ) 
		{
			pMsgAttack = zDYNAMIC_CAST<oCMsgAttack> (GetEM()->GetEventMessage( nMessage ));
			if ( pMsgAttack ) 
			{
				if		( pMsgAttack == csg ) continue;													// donot delete self
				else if ( pMsgAttack->GetSubType() == csg->GetSubType() ) 
				{
					//
					//	JA -> ALTE ATTACK MESSAGE VOM GLEICHEN SUBTYPE LOESCHEN
					//
					pMsgAttack->Delete(); 
				}
			}
		}
	}

	return TRUE;
}

/*--------------------------------------------------------------------------

    oCNpc::TransitionAim()

 

    28-Aug-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/
zBOOL oCNpc :: TransitionAim( zTModelAniID idCurrentAni, zTModelAniID idTargetAni )
{
	oCAniCtrl_Human* pAniCtrl	= this->GetAnictrl	();
	zCModel*		 pModel		= this->GetModel	();

	//
	//	GEWUENSCHTER ZUSTAND ERREICHT?
	//
	if ( pModel->IsAniActive( idTargetAni ) ) return TRUE;

	//
	//	WECHSEL IN DEN GEWUENSCHTEN ZUSTAND EINLEITEN
	//
	if		( ( idCurrentAni == pAniCtrl->_s_walk ) && ( idTargetAni == pAniCtrl->_s_aim  ) ) pModel->StartAni( pAniCtrl->_t_walk_2_aim );
	else if	( ( idCurrentAni == pAniCtrl->_s_aim  ) && ( idTargetAni == pAniCtrl->_s_hitf ) ) pModel->StartAni( pAniCtrl->_t_hitf		);
	else if	( ( idCurrentAni == pAniCtrl->_s_hitf ) && ( idTargetAni == pAniCtrl->_s_aim  ) ) pModel->StartAni( pAniCtrl->_t_hitback	);

	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::InterpolateAim()

 

    28-Aug-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/
zBOOL oCNpc :: InterpolateAim( oCNpc* pEnemy )
{
	oCAniCtrl_Human* pAniCtrl	= this->GetAnictrl	();

	//
	//	BEWEGUNG ANHALTEN
	//
	zBOOL inMove =	this->GetInMovement();
	if (inMove)		this->EndMovement();
	
	//
	//	GEGNER "BESCHEID SAGEN", DASS ICH AUF IHN ZIELE
	//
	pEnemy->AssessThreat_S( this );

	//
	//	WINKEL BESTIMMEN	
	//
	zREAL	fAzimuth	= 0.0f,
			fElevation	= 0.0f;

	this->GetAngles( pEnemy, fAzimuth, fElevation );

	zREAL	fX = ( fAzimuth / 90.0f ) + 0.5f;
	zREAL	fY = 1.0f - ( ( fElevation / 90.0f ) + 0.5f );

	//
	//	REICHT HUEFE-DREHEN NICHT MEHR AUS ?
	//
	if	( 
		   ((fX < 0.0f) || (fX > 1.0f))
		|| ((fY < 0.0f) || (fY > 1.0f))
		) 
	{
		//
		//	GEGNER NOCH NICHT ERFASST
		//
		this->hasLockedEnemy = FALSE;

		//
		//	JA -> ZUM GEGNER DREHEN ...
		//
		this->Turn( pEnemy->GetPositionWorld() );

		//
		//	... UND WARTEN
		//
		return FALSE;
	}
	else 
		//
		//	GEGNER ERFASST
		//
		this->hasLockedEnemy = TRUE;

	//
	//	BEWEGUNG STARTEN
	//
	if (inMove) this->BeginMovement();

	//
	//	UND DAS ZIELEN INTERPOLIEREN
	//
	pAniCtrl->InterpolateCombineAni( fX, fY, pAniCtrl->_s_aim );

	return TRUE;
}

/*--------------------------------------------------------------------------

    oCNpc::FinalizeAim()

 

    28-Aug-00       [Roman Keskenti]

                      Initial implementation

						
--------------------------------------------------------------------------*/
zBOOL oCNpc :: FinalizeAim( zBOOL bStartMelee, zBOOL bStandUp )
{
	zBOOL bResult = FALSE;		// was in aim-overlay mode before

	//
	//	OVERLAY-AIM-MESAGES LOESCHEN
	//
	oCMsgAttack*	pMsgAttack	= NULL;

	for ( int nMessage = 0; nMessage < GetEM()->GetNumMessages(); nMessage++ ) 
	{
		pMsgAttack = zDYNAMIC_CAST<oCMsgAttack> (GetEM()->GetEventMessage( nMessage ));
		if ( pMsgAttack ) 
		{
			if ( pMsgAttack->GetSubType() == oCMsgAttack::EV_AIMAT ) 
			{
				pMsgAttack->Delete(); 
				bResult = TRUE;
			}
		}
	}

	//
	//	SOLL ICH IN DEN NAHKAMPFMODUS WECHSELN?
	//
	if ( bStartMelee )
	{
		//
		//	JA -> WAFFE WEGSTECKEN ...
		//
		oCMsgWeapon* pMsgWeaponRemove = zNEW( oCMsgWeapon(oCMsgWeapon::EV_REMOVEWEAPON) );
		pMsgWeaponRemove->SetHighPriority( TRUE );
		this->GetEM()->OnMessage( pMsgWeaponRemove, this );
	}

	//
	//	SOLL ICH AUFSTEHEN (AUFHOEREN ZU ZIELEN)?
	//
	if ( bStandUp ) 
		this->StandUp();

	return bResult;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_StopAim()

 

    28-Aug-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_StopAim(oCMsgAttack* csg )
{
	this->FinalizeAim( FALSE, TRUE );
	return TRUE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_AimAt()

 

    24-Aug-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_AimAt(oCMsgAttack* csg )
{
	//
	//	
	//
	oCNpc*	pEnemy			= NULL ;
	zBOOL	bDrawnWeapon	= FALSE;
	zBOOL	bAmmoAvailable	= FALSE;
	zBOOL	bKillFormerMsg	= TRUE ;

	oCAniCtrl_Human* pAniCtrl	= this->GetAnictrl	();

	//
	//	SITUATION ERMITTELN
	//
	this->InitAim( csg, &pEnemy, &bDrawnWeapon, &bAmmoAvailable, bKillFormerMsg );

	//
	//	SITUATION AUSWETEN
	//
	if ( ! pEnemy			)	{ this->FinalizeAim( FALSE, TRUE ); return TRUE ; }		// KEIN GEGNER MEHR DA	-> STOP AIM
	if ( ! bDrawnWeapon		)	{									return FALSE; }		// KEINE RANGE WAFFE	-> AUF ENTSPRECHENDEN SKRIP-BEFEHL WARTEN
	if ( ! bAmmoAvailable	)	{ this->FinalizeAim( TRUE, TRUE  ); return TRUE ; }		// KEINE MUNI MEHR		-> NAHKAMPF 

	//
	//	TRANSITION VOM WALK- ZU AIM-ANI EINLEITEN
	//
	if ( this->TransitionAim( pAniCtrl->_s_walk, pAniCtrl->_s_aim ) )
	{
		// [Ulf] : TurnAnis beenden vorm Zielen
		if (GetAnictrl()) GetAnictrl()->StopTurnAnis();

		//
		//	TRANSITION ABGESCHLOSSEN -> ZIEL ERFASSEN 
		//
		this->InterpolateAim( pEnemy );
	}

	//
	//	WEITER WARTEN
	//
	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_ShootAt()

 

    24-Aug-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_ShootAt(oCMsgAttack* csg)
{
	//
	//	MODEL UND ANI CONTROLLER HOHLEN
	//
	oCAniCtrl_Human* pAniCtrl	= this->GetAnictrl	();

	//
	//	SCHIESSEN
	//
	if ( ! this->didShoot ) 
	{
		//
		//	ZIELEN BEENDEN
		//
		this->wasAiming = this->FinalizeAim( FALSE, FALSE );

		//
		//	NOTFALLS SELBST ZIELEN
		//
		if ( ! this->hasLockedEnemy )
		{
			this->EV_AimAt( csg );
			return FALSE;
		}

		//
		//	PFEIL LOSSCHICKEN
		//
		this->DoShootArrow( TRUE ); 
		this->didShoot = TRUE;
	}

	//
	//	TREFFEN
	//
	if ( ! this->didHit )	
		this->didHit = this->TransitionAim( pAniCtrl->_s_aim , pAniCtrl->_s_hitf );

	if ( this->didShoot && this->didHit ) 
	{
		this->DoDoAniEvents();

		//
		//	NACHLADEN
		//
		if ( this->TransitionAim( pAniCtrl->_s_hitf, pAniCtrl->_s_aim  ) )
		{
			this->didShoot = FALSE;
			this->didHit   = FALSE;

			//
			//	NEU ZIELEN?
			//
			if ( wasAiming ) 
			{
				oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_AIMAT, csg->target );
				this->GetEM()->OnMessage( pMsg, csg->target );
				this->wasAiming = FALSE;
			}
			else
				this->StandUp();

			return TRUE;
		}
	}

	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_Defend()

 

    07-Sep-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_Defend(oCMsgAttack* csg )
{
	//
	//	VERTEIDIGEN EINSCHALTEN -> WIRD IM EV_ATTACK ABGEFANGEN
	//
	this->isDefending = TRUE;

	//
	//	HABE ICH PARIERT?
	//
	if ( this->didParade )
	{
		//
		//	DANN AUFHOEREN -> AB HIER KOMMT DER SKRIPT-ZS
		//
		this->isDefending	= FALSE;
		this->didParade		= FALSE;

		return TRUE;
	}

	//
	//	WEITER WARTEN
	//
	return FALSE;
}
//
//	CODECHANGE [ROMAN] END
//

// ****************************************
// Events - Use Item
// ****************************************
	
zBOOL oCNpc :: EV_Drink (oCMsgUseItem* csg)
{
	zCModel* model	= GetModel();
	
	if (anictrl->IsStanding()) {
		if (!csg->IsInUse()) {
			csg		-> ani  = model->GetAniIDFromAniName("T_DRINKPOTION");
			anictrl -> SetNextAni(csg->ani,anictrl->_s_walk);
			model	-> StartAni(csg->ani);
			csg		-> SetInUse(TRUE);
			csg		-> state = 0;
		} else {
			if (csg->state==2) {	// Safety, duerfte eigentlich nicht passieren
//				EndMovement();
				SetLeftHand(NULL);
				oCItem*	 item	= zDYNAMIC_CAST<oCItem>(csg->vob);
				if (item && (csg->state==2)) {
					// Passiert nach Laden eines OverlayMDS !
					oCVob* what = (oCVob*)RemoveFromSlot (NPC_NODE_LEFTHAND, FALSE);
					zRELEASE(what);
				}
//				BeginMovement();
			}
			return TRUE;
		}

	} else if (model->IsAniActive(csg->ani)) {
		zREAL fr = model->GetProgressPercent(csg -> ani);
		if ((csg->state==0) && (fr>=0.15)) {
//			EndMovement();
			// Mesh in das Slot einf�gen
			oCItem*	 item	= zDYNAMIC_CAST<oCItem>(csg->vob);
			item				= RemoveFromInv( item );
			if (!item)			return TRUE;
			PutInSlot			(NPC_NODE_LEFTHAND,item);
//			BeginMovement		();
			csg->state = 1;
		} else if ((csg->state==1) && (fr>=0.65)) {
//			EndMovement		();
			oCItem*	 item	= zDYNAMIC_CAST<oCItem>(csg->vob);
			UseItem			(item);
//			BeginMovement	();
			csg->state = 2;
		} else if ((csg->state==2) && (fr>=0.85)) {
//			EndMovement	();
			oCVob* what = (oCVob*) RemoveFromSlot (NPC_NODE_LEFTHAND, FALSE);
			if (what && (csg->state==2)) zRELEASE(what);
//			BeginMovement();
			csg->state = 3;
		}
	} 
	return FALSE;
};

zBOOL oCNpc :: EV_TakeVob (oCMsgManipulate* csg)
{
	zCModel* model = GetModel();
	
	// Patch 1.07
	// Gegenstaende aufnehmen beim Schwimmen enablen
	if (anictrl->GetWaterLevel()==2) {
		if (csg->targetVob && csg->targetVob->GetHomeWorld() == GetHomeWorld()) {
			DoTakeVob(csg->targetVob);
			csg->targetVob = NULL;
		}		
		return TRUE;
	}

	// Gegenstand aufheben
	if (anictrl -> IsStateAniActive(anictrl->_s_walk)) {

		// [BENDLIN] Addon Patch2 - TakeVob Crash-Hack
		try
		{
			if (zDYNAMIC_CAST<oCItem>(csg->targetVob))	csg->aniID = model->GetAniIDFromAniName("T_STAND_2_IGET");
			else										csg->aniID = model->GetAniIDFromAniName("T_STAND_2_OGET");
		}
		catch(...)  // catch all exceptions
		{
			csg->targetVob = NULL;
			return TRUE;
		}

		SetBodyState(BS_TAKEITEM);
		if (csg->IsInUse()) {
			return TRUE;
		}

		model->StartAni(csg->aniID);

		// Positioning - YKoordinate berechnen
		if (csg->targetVob) {
			
			csg->aniCombY = csg->targetVob->GetPositionWorld()[VY] - GetPositionWorld()[VY];
			// Now Scale
			csg->aniCombY = (csg->aniCombY + 100) / 200;
			if (csg->aniCombY < 0.0f) csg->aniCombY = 0.0f;
			if (csg->aniCombY > 1.0f) csg->aniCombY = 1.0f;	
		}

	} else if (model->IsAniActive(anictrl->s_iget) || model->IsAniActive(anictrl->s_oget)) {
		
		if (csg->targetVob && csg->targetVob->GetHomeWorld() == GetHomeWorld()) {
			DoTakeVob(csg->targetVob);
			csg->targetVob = NULL;
		}
				
		model	-> StartAni		(anictrl -> t_iget_2_stand);
		anictrl -> SetNextAni	(anictrl -> t_iget_2_stand, anictrl->_s_walk);
		csg		-> SetInUse		(TRUE);
		csg		-> aniID = anictrl -> t_iget_2_stand;
	}

	zCModelAni*	ani	= model	-> GetAniFromAniID	(csg->aniID);
	
	if (ani && (ani->GetAniType()==zMDL_ANI_TYPE_COMB)) {
		model->SetCombineAniXY(csg->aniID,0.5,csg->aniCombY);
	}	

	return FALSE;
}

zBOOL oCNpc :: EV_DropVob (oCMsgManipulate* csg)
{
	zCModel* model = GetModel();
	SetBodyState (BS_INVENTORY);
	// Gegenstand ablegen
	if (anictrl -> IsStateAniActive	(anictrl -> _s_walk)) {
		if (csg->IsInUse()) return TRUE;
//		model -> StartAni (anictrl -> t_stand_2_iaim);
		model -> StartAni ("T_STAND_2_IDROP");

//	} else if (anictrl -> IsStateAniActive(anictrl -> s_iaim)) {
//		model -> StartAni(anictrl -> t_iaim_2_idrop);
	
	} else if (anictrl -> IsStateAniActive(anictrl -> s_idrop)) {

		if (csg->targetVob) {
			DoDropVob		(csg->targetVob);
		
		} else if (!slot.IsEmpty()) {
			RemoveFromSlot	(csg->npcSlot);
		
		} else if (!csg->name.IsEmpty()) {
			
			oCItem* item = RemoveFromInv(csg->name);
			if (item) DoDropVob(item);
		
		}
		
		if (anictrl->t_idrop_2_stand) {
			anictrl -> SetNextAni	(anictrl->t_idrop_2_stand,anictrl->_s_walk);
			model	-> StartAni		(anictrl->t_idrop_2_stand);
		} else {
			model	-> StartAni		(anictrl->_s_walk);
		}			

		csg   -> SetInUse	(TRUE);
	}
	return FALSE;
}

zBOOL oCNpc :: EV_ThrowVob(oCMsgManipulate* csg)
{
	zCModel* model = GetModel();
	if (anictrl->IsStateAniActive(anictrl->_s_walk)) {
		if (csg->IsInUse()) return TRUE;
		model->StartAni(anictrl->t_stand_2_iaim);
		csg->SetInUse(TRUE);

	} else if (anictrl->IsStateAniActive(anictrl->s_iaim)) {
		model->StartAni(anictrl->t_iaim_2_ithrow);

	} else if (anictrl->IsStateAniActive(anictrl->s_ithrow)) {
		
		zCVob *vob = GetSlotVob(NPC_NODE_RIGHTHAND);
		if (vob) {
			zREAL dist;
			if (zDYNAMIC_CAST<oCMOB>(vob))	{
				oCNpcFocus::SetFocusMode(FOCUS_THROW_MOB);
				dist = oCNpcFocus::focus->GetMobThrowRange();
				dist = GetThrowSpeed(sqrt(dist),20);
			} else {
				oCNpcFocus::SetFocusMode(FOCUS_THROW_ITEM);
				dist = oCNpcFocus::focus->GetItemThrowRange();
				dist = GetThrowSpeed(sqrt(dist),35);
			}
			DoThrowVob	(vob,dist);
			oCNpcFocus::SetFocusMode(FOCUS_NORMAL);
		}

		if (anictrl -> t_ithrow_2_stand) {
			anictrl -> SetNextAni	(anictrl -> t_ithrow_2_stand, anictrl->_s_walk);
			model	-> StartAni		(anictrl -> t_ithrow_2_stand);
		} else {
			model	-> StartAni		(anictrl->_s_walk);
		}			
		// Safety
		csg->SetInUse(TRUE);
	} 
	return FALSE;
}

zBOOL oCNpc :: EV_Exchange(oCMsgManipulate* csg)
{
	zCModel* model = GetModel();
	// anders aufgebaut, da Torchgeschichten Anis des 2ten Layers sind
	if (model->IsAniActive(anictrl->_t_stand_2_torch)) {
		// FIXME : Muss spaeter durch Event aus MDS ausgeloest werden, nicht
		// durch Frameabfrage !
		if (!csg->IsInUse()) {
			zCModelAniActive* ani = model->GetActiveAni(anictrl->_t_stand_2_torch);
			if (ani && (ani->GetActFrame()>=4)) {
				// Items austauschen
				DoExchangeTorch();
				csg->SetInUse(TRUE);
			}
		}
	
	} else if (model->IsAniActive(anictrl->_s_walk)) {
		if (!csg->IsInUse()) 
			model->StartAni(anictrl->_t_stand_2_torch);
		else {
			SetTorchAni(GetLeftHand()!=NULL);
			return TRUE;
		}

	} else if (model->IsAniActive(anictrl->s_iaim)) {
		if (!csg->IsInUse()) 
			model->StartAni(anictrl->_t_stand_2_torch);
		else
			model->StartAni(anictrl->_s_walk);
	}
	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_DropMob()

 

    20-Sep-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_DropMob(oCMsgManipulate* csg)
{
	oCMobInter* mob = zDYNAMIC_CAST< oCMobInter > (this->GetCarryVob());
	if ( ! mob ) return TRUE;

	oCMsgManipulate* pMsg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_DROPVOB,mob);
	pMsg->SetHighPriority( TRUE );

	this->GetEM()->OnMessage( pMsg ,this);
	return TRUE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_TakeMob()

 

    20-Sep-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_TakeMob(oCMsgManipulate* csg)
{
	oCMobInter* mob = this->FindMobInter( csg->name );
	if ( ! mob ) return TRUE;

	oCMsgManipulate* pMsg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_TAKEVOB,mob);
	pMsg->SetHighPriority( TRUE );

	this->GetEM()->OnMessage( pMsg ,this);
	return TRUE;
}

zBOOL oCNpc :: EV_UseMob(oCMsgManipulate* csg)
{
	if (!csg->targetVob) {
		csg->targetVob = GetInteractMob();
		if (!csg->targetVob) {
			// Mob erstmal suchen
			csg->name.Upper();
			oCMobInter* mob = FindMobInter(csg->name);
			csg->targetVob	= mob;
			if (!csg->targetVob) {
				zERR_WARNING("U: NPC: EV_USEMOB : No Mobsi with specified schemeName ("+csg->name+") found.");
				return TRUE;
			}
			// aber vorher hingehen !
			zVEC3 targetPos;
			mob->GetFreePosition(this,targetPos);
			oCMsgMovement* msg = zNEW( oCMsgMovement(oCMsgMovement::EV_GOTOPOS,targetPos) );
			msg -> SetHighPriority(TRUE);
			GetEM()->OnMessage(msg,NULL);
			// Objekt schon mal als anvisiert markern !
			mob->MarkAsUsed(20 * 1000,this);
			return FALSE;
		}
	}

	oCMobInter* mob = zDYNAMIC_CAST<oCMobInter>(csg->targetVob);
	if (mob) {
		if (!mob->IsInteractingWith(this) && !mob->CanInteractWith(this)) return TRUE;
		return (mob->AI_UseMobToState(this,csg->targetState));
	}
	return FALSE;
}

zBOOL oCNpc :: EV_UseMobWithItem (oCMsgManipulate* csg)
{
	SetInteractItem(zDYNAMIC_CAST<oCItem>(csg->targetVob));
	return TRUE;
}

zBOOL oCNpc :: EV_InsertInteractItem	(oCMsgManipulate* csg)
{		
	if (interactItem) {
		if (csg->slot.IsEmpty()) {
			zERR_WARNING("U: ITEMI: No slot found :"+csg->slot);
			return TRUE;
		}
		if (GetSlotItem(csg->slot)!=interactItem) {
			// oCItem* isIn	= IsInInv(interactItem,1);
            if (IsInInv(interactItem))
			    SetInteractItem	(RemoveFromInv(interactItem,1));	//  [Moos] 2.2.2001: Das InteractItem ist aber doch gar nie im Inventory! Das gibt �rger....

			PutInSlot		(csg->slot,interactItem);
			//zERR_WARNING	("U: ITEMI: Inserted Item:"+interactItem->GetInstanceName());
		}
	}
	return TRUE;
}

zBOOL oCNpc :: EV_ExchangeInteractItem	(oCMsgManipulate* csg)
{		
	// a) Altes InteractItem destroyen
	if (interactItem) {
		TNpcSlot* slot = NULL;
		for (int i=0; i<invSlot.GetNumInList(); i++) {
			slot = invSlot[i];
			if (GetSlotItem(slot->name)==interactItem) {
				//zERR_WARNING	("U: ITEMI: Removed Item:"+interactItem->GetInstanceName());
				RemoveFromSlot	(slot,FALSE);
				GetHomeWorld()->RemoveVob(interactItem);
                zRELEASE(interactItem);
				break;
			}		
		}
	}
	
	// b) Neues InteractItem einsetzen
	oCItem* tmpItem = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,csg->name) ;
	if (tmpItem) {
		// Sicherung fuer Multi-Items.... Argh !
		PutInInv				(tmpItem);		
		oCItem* curItem = RemoveFromInv(tmpItem->GetInstance(),1);
		SetInteractItem			(curItem);
		EV_InsertInteractItem	(csg);
   	}
	zRELEASE(tmpItem);
	return TRUE;
}

zBOOL oCNpc :: EV_RemoveInteractItem	(oCMsgManipulate* csg)
{
	SetInteractItem	(NULL);
	return TRUE;
}

zBOOL oCNpc :: EV_CreateInteractItem	(oCMsgManipulate* csg)
{
	
	zBOOL interactitemcreated = TRUE;

	if (!GetInteractItem()) 
	{
		zERR_WARNING(       "C: oCNpc :: EV_CreateInteractItem: DEF_CREATE_ITEM w/o previously called DEF_INSERT_ITEM, " +
					zSTRING("did you forget to set a valid mobsi useOnItem string ?") );

		interactitemcreated = FALSE;
		//ItMw_1h_Vlk_Sword
	}
		
	// wenn diese Zeile drinsteht, werden sporadisch keine
	// items aus dem MDS erzeugt (H�mmer, etc.)
	// FIXME: ich weiss hier nicht was ich tue, so werden zwar die h�mmer korrekt dargestellt,
	// (und ich mach auch mal ein interact item daraus)
	// aber eventuell gibt es item verdoppler crashes, fehlende H�mmer beim Laden, etc...
	// muss genauer beobachtet werden
	if (1)
	{
		if (csg->slot.IsEmpty()) return TRUE;
		// Item erzeugen
		oCItem* item = (oCItem*) ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,csg->name);
		if (item && !csg->slot.IsEmpty()) {
			int tmplevel = 0;

			// Slot erzeugen....
			if (!IsInvSlotAvailable(csg->slot)) {
				CreateInvSlot(csg->slot);
				tmplevel++;
			}

			TNpcSlot* slot = GetInvSlot(csg->slot);
			if (slot) {
				tmplevel++;
				slot -> tmpLevel = tmplevel;				// Only used for ItemInteraction
				zBOOL inMove = GetInMovement();
				if (inMove) EndMovement		();
				PutInSlot		(slot,item);
				if (inMove)	BeginMovement	();
				//zERR_WARNING	("U: ITEMI: Created Item:"+item->GetInstanceName());
			}
		}
		if (!interactitemcreated) SetInteractItem(item);
		zRELEASE(item);
	}
	return TRUE;
}

zBOOL oCNpc :: EV_DestroyInteractItem	(oCMsgManipulate* csg)
{
	int instance = -1;
	oCItem* item = GetInteractItem();
	if (item) instance = item->GetInstance();	
	SetInteractItem(NULL);
	if (instance>=0) {
		item = RemoveFromInv(instance,1);
		if (item) {
//			zERR_WARNING("U: ITEMI: Destroyed Item:"+item->GetInstanceName());	
			if (item->GetEM()->GetCutsceneMode()) {
				zERR_FAULT("U: ITEMI: Item ("+item->GetInstanceName()+") used in cutscene cannot be destroyed. This is evil, please correct the cutscene using the AI_USEITEM-command !");
				ogame->GetWorld()->RemoveVob(item);	
				item = NULL;
			} else {
				// Muss noch in den Listen stehen.
				// zERR_ASSERT	(item->GetRefCtr()>=2);
				// zRELEASE	(item);
				ogame->GetWorld()->RemoveVob(item);
				item = NULL;
			}
		}
	}
	return TRUE;
}

zCModelAni* oCNpc::InteractItemGetAni(const zSTRING& sceme, int from, int to)
{
	zSTRING name = "T_"+sceme+"_";

	if (from == -1) name += "STAND";
	else			name += "S"+zSTRING(from);
	name += "_2_";

	if (to == -1)	name += "STAND";
	else			name += "S"+zSTRING(to);

	return GetModel()->GetAniFromAniName(name);
}

zBOOL oCNpc::EV_PlaceInteractItem(oCMsgManipulate* csg)
{
	oCMobItemSlot* mob		= zDYNAMIC_CAST<oCMobItemSlot>(GetInteractMob());
	if (mob) {
		oCItem* item = GetInteractItem();
		if (item) {
			// Gegenstand aus Inventoryx entfernen ( sofern vorhanden )
			SetInteractItem(NULL);
			if (IsInInv(item)) item = RemoveFromInv(item,1);
			mob -> PlaceItem(item);
		} else {
			// Gegenstand nehmen
			oCItem* item = mob -> RemoveItem();
			PutInInv(item);
		}
	} else {
		// Patch 1.08
		// DEF_PLACE_ITEM wird auch bei Mobsis benutzt, bei denen es keinen Effekt hat....
		// dh. kein Object der Klasse oCMobItemSlot
		// Hier zu Sicherung InteractItem loeschen und aus Inventory entfernen.
		
		oCItem*		item	= GetInteractItem();

		// Auch das hilft nichts, da die Slots in den Daten nicht vorhanden sind,
		// schade, sieht alles ziemlich panne aus, so.
		/*oCMobInter* mob		= zDYNAMIC_CAST<oCMobItemSlot>(GetInteractMob());
		if (mob) {
			// Durchsuche nach Item-Slot : ZS_SLOT
			zCModelPrototype* m = GetModel()->GetModelProto();
			for (int i=0; i<m->GetNodeList().GetNumInList(); i++) {
				zCModelNode*	node		= m->GetNodeList()[i];
				zSTRING			nodeName	= node->GetName();
				// Found ?
				if (node && (nodeName.Search("ZS_SLOT")>=0)) {				
					
					item -> AddRef();
					SetInteractItem(NULL);	
					item -> SetCollDet(FALSE);

					if (item->GetHomeWorld()) item->GetHomeWorld()->RemoveVob(item);
					item -> SetPositionWorld	(0,0,0);
					GetHomeWorld()->AddVob		(item);
					
					zMATRIX4 trafo	= GetTrafoModelNodeToWorld(nodeName);
					item -> SetCollDet			(FALSE);
					item -> SetTrafoObjToWorld	(trafo);
					item -> SetPhysicsEnabled	(FALSE);
					item -> SetIgnoredByTraceRay(TRUE);
					item -> SetSleeping			(TRUE);
					zRELEASE(item);

					return TRUE;
				}
			}

		} else */ if (item) {
			int instance = item->GetInstance();
			SetInteractItem(NULL); // wandert hier zurueck ins Inv
			item		= RemoveFromInv(instance,1);
			if (item && GetHomeWorld()) GetHomeWorld()->RemoveVob(item);
		}
	}
	return TRUE;
}

int oCNpc::GetInteractItemMaxState(const zSTRING& sceme)
{
	int num = -1;
	while ( GetModel()->GetAniIDFromAniName("S_"+sceme+"_S"+zSTRING(num+1)) != zMDL_ANI_ID_ILLEGAL) {
		num++;
	}
	return num;
}

zBOOL oCNpc::InteractItemIsInState(const zSTRING& sceme, int state)
{
	if (state == -1)	return anictrl		-> IsStanding	();
	else				return GetModel()	-> IsAniActive	("S_"+sceme+"_S"+zSTRING(state));
}

zBOOL oCNpc :: EV_EquipItem(oCMsgManipulate* csg)
{	
	// TargetVob suchen
	if (!csg->targetVob) csg->targetVob = IsInInv(csg->name,1);

    oCItem *item = zDYNAMIC_CAST<oCItem>(csg->targetVob);
	if (!item->HasFlag(ITM_FLAG_ACTIVE) && !CanUse(item) && this==player) {
        DisplayCannotUse();
		return TRUE;
	}	

	Equip(item);	
	return TRUE;
}

zBOOL oCNpc :: EV_UseItem(oCMsgManipulate* csg)
{
	if (!csg->targetVob) {
		oCItem* item				= IsInInv(csg->name,1);
		csg->targetVob				= item;
		// Nicht gefunden, Befehl beenden.
		if (!csg->targetVob) {
			zERR_WARNING("U: NPC: EV_USEITEM : No targetVob "+csg->name+"found.");
			return TRUE;
		}
		// Initialisieren
		interactItemCurrentState	= -1;
		csg->targetState			= GetInteractItemMaxState(item->GetSchemeName());
	}

	if (EV_UseItemToState(csg)) {
		// Zustand erreicht, jetzt wieder runter ?
		if (csg->targetState>= 0) {
			csg->targetState = -1; 
			// [EDENFELD] 1.27 
			// Eine EV_UseItemToState() Message ist beendet, wenn die Transition zuende gespielt wurde,
			// und der gew�nschte loop ani state erreicht ist.
			// z.B. ist EV_UseItemToState() beendet, wenn T_POTION_STAND_2_S0 beendet ist, und S_POTION_S0 angespielt wird
			// ob das von der Implementation so gew�nscht ist, kann ich nicht sagen.
			// das SetInUse(FALSE) war hier daf�r gedacht, das bei einem n�chsten Call von EV_UseItemToState() der neue targetState (=zur�ckspulen)
			// �bernommen wird. 
			// das ist jetzt nicht mehr n�tig, da der state nun jeden Frame mit �bernommen wird.
			// der eigentliche "Item verschwindet Fehler" kam zustande, da bei einem erneuten Initialisieren der Message (=SetInUse(FALSE))
			// ein neues InteractItem gesetzt wird. (siehe SetInteractItem())
			//csg->SetInUse(FALSE);
		} else if (csg->targetState<=-1) {
			return TRUE;
		}
	}
	return FALSE;
}

zBOOL oCNpc :: EV_UseItemToState(oCMsgManipulate* csg)
{
	if (!csg->IsInUse()) {
		// Ist der Vob �berhaupt ein Item ?
		oCItem* item = zDYNAMIC_CAST<oCItem>(csg->targetVob);
		if (!item) {
			// Kein TargetVob angegeben, also im Inventory nach dem SchemaNamen->Instanzname gucken
			item = IsInInv(csg->name,1);
			// Dann Vielleicht aktuelles Interact Item
			// Beachte : Befindet sich nicht mehr im Inv, 
			// wenn bereits in Welt per "DEF_INSERTITEM" eingef�gt
			if (!item && GetInteractItem() && (GetInteractItem()->GetInstanceName()==csg->name)) {
				item = GetInteractItem();
			}
			
			csg->targetVob	= (zCVob*)item;
		}

		if (!csg->targetVob) {
			zERR_WARNING("U: NPC: EV_USEITEMTOSTATE : No targetVob "+csg->name+" found.");
			return TRUE;
		}

		// Hat er einen SchemaNamen ?
		csg->name = item->GetSchemeName();
		if (csg->name.IsEmpty()) {
			zERR_WARNING("U: NPC: EV_USEITEMTOSTATE : Item "+item->GetName()+" has no schemename.");
			return TRUE;
		}		

		// Safety : Stehenbleiben, falls ItemInteraktion beginnt und nicht in MobInteraktion
//		if ((interactItemCurrentState==-1) && !GetInteractMob()) {
//			StandUp();
//		}

		// Alles ok, dann mal los
		csg->SetInUse(TRUE);
		csg->flag = FALSE;
		SetInteractItem(item);
		//interactItemCurrentState	= -1;
		//interactItemTargetState	= csg ->targetState;
	}
	
	// [EDENFELD] 1.27
	interactItemTargetState		= csg ->targetState;

	SetBodyState(BS_ITEMINTERACT);

	// Check MDS-EventTags
	DoDoAniEvents();

	// Safety....
	if (!GetInteractItem() && (interactItemTargetState>=0)) {
		SetInteractItem(zDYNAMIC_CAST<oCItem>(csg->targetVob));
		if (!GetInteractItem()) {
			interactItemCurrentState = -1;
			if (GetAnictrl()) GetAnictrl()->SearchStandAni(TRUE);
			return TRUE;
		}
	};

	// Schon im Zielzustand, dann ist's ja gut.
	if (interactItemCurrentState!=interactItemTargetState) 
	if (InteractItemIsInState(csg->name, interactItemCurrentState)) {		

		// Aktiviere Zustandseffekt
		if (interactItem && !csg->flag) {
			parser.SetInstance	("SELF",this);
			parser.SetInstance	("ITEM",interactItem);			
			//interactItem -> DoStateEffect	(interactItemCurrentState);
			CallScript			(interactItem->GetStateEffectFunc(interactItemCurrentState));
			csg->flag = TRUE;
		}

		// Direkter Wechsel zum Zielzustand m�glich ?
		zCModel* model	= GetModel();
		zCModelAni* ani = InteractItemGetAni(csg->name,interactItemCurrentState,interactItemTargetState);
		if (ani) {
			model -> StartAni ( ani );
			interactItemCurrentState = interactItemTargetState;
			csg -> flag = FALSE;
		} else {
			// Kein Direkter Wechsel m�glich, also gehen wir Schrittweise
			int dir = 0;
			if (interactItemCurrentState < interactItemTargetState) dir = +1;
			else													dir = -1;
			// Wechsel zum angestrebten n�chsten Zustand m�glich ?
			ani = InteractItemGetAni(csg->name,interactItemCurrentState,interactItemCurrentState + dir);
			if (!ani) {
				zERR_WARNING("U: ITEMI: No Transition found : "+csg->name+"/"+zSTRING(interactItemCurrentState)+"/"+zSTRING(interactItemTargetState));
				interactItemTargetState = interactItemCurrentState;
			} else {		
				model -> StartAni ( ani );
				// interactItemCurrentState = interactItemTargetState + dir;
				interactItemCurrentState += dir;
				csg -> flag = FALSE;
			}
		}
	}
	// Safety, weil sonst Haenger in EV_UseItemToState passieren kann ( durch random-Anis ? )
	if ((interactItemCurrentState > -1) && (interactItemCurrentState==interactItemTargetState)) {
		if (anictrl->IsStateAniActive(anictrl->_s_walk)) return TRUE; 
	}
	return (InteractItemIsInState(csg->name,interactItemTargetState));
}

void oCNpc :: CallScript(const zSTRING& funcName)
{
	CallScript(parser.GetIndex(funcName));
}

void oCNpc :: CallScript(int funcIndex)
{
	if (funcIndex>=0) parser.CallFunc(funcIndex);
}

zBOOL oCNpc :: EV_CallScript(oCMsgManipulate* csg)
{
	parser.SetInstance("SELF",this);
	parser.SetInstance("OTHER",oCNpc::player);
	if (csg->targetState>=0)	parser.CallFunc(csg->targetState);	else
	if (!csg->name.IsEmpty())	parser.CallFunc(csg->name);
	return TRUE;
}

// *****************************
// *** Events : StateChanges ***
// *****************************

zBOOL oCNpc :: EV_Unconscious(oCMsgState* csg)
{	
	zCModel* model = GetModel();
	if (model->IsAniActive("S_KNOCKEDOUT")) {
		csg->timer -= ztimer.GetFrameTimeF();
		if (csg->timer<=0) {
			model->StartAni("T_KNOCKEDOUT_2_STAND");
			return TRUE;
		}	
	} else if (!model->IsAniActive("T_KNOCKEDOUT")) {
		model->StartAni	("T_KNOCKEDOUT");
		SetAttribute	(NPC_ATR_HITPOINTS,1);
	}
	return FALSE;
}

zBOOL oCNpc :: EV_DoState(oCMsgState* csg)
{
	if (!csg->wp.IsEmpty()) wpname = csg->wp;
	int		function	= csg->function;
	zBOOL	endOld		= csg->endOldState;

	// Note : SELF wird bei AI_StartState gesetzt.
	parser.SetInstance("OTHER"	,csg->other);
	parser.SetInstance("VICTIM"	,csg->victim);

	// Vorher Queue l�schen !
	ClearEM();

	if (function==0) {
		// Tagesablauf starten.
		state.curState.valid	= FALSE;
		state.nextState.valid	= FALSE;
		state.StartRtnState ();
	} else {
		// [Wohlers] Neuen Zustand starten (aus den Skripten)
		// Nicht per Wahrnehmung getriggert...(AtHome).
		state.StartAIState(function,endOld,AITIME_NO,0.0f,csg->inRoutine);
	}

	return TRUE;
}

zBOOL oCNpc :: EV_Wait(oCMsgState* csg)
// BuildIn-State-Warten
{	
	if (GetAnictrl()) {
		if (GetAnictrl()->IsWalking() || (GetAnictrl()->GetActionMode()==ANI_ACTION_SWIM) || (GetAnictrl()->GetActionMode()==ANI_ACTION_DIVE)) {
			GetAnictrl()->_Stand();
		}
		GetAnictrl()->StopTurnAnis();
	}
	
	csg->timer -= ztimer.GetFrameTimeF();
	return (csg->timer<0.0f);
};

/*--------------------------------------------------------------------------

    oCNpc :: EV_ApplyTimedOverlayMds()

 

    03-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: ApplyTimedOverlayMds( const zSTRING& mdsName, zREAL timer )
{
    if (!GetVisual()) // [Moos] ohne visual macht diese Funktion keinen Sinn
        return FALSE;

	oCAniCtrl_Human*	pAniCtrl	= this->GetAnictrl	();	if ( ! pAniCtrl ) return FALSE;		// no Anis  -> DELETE ME !
	zCModel*			pModel		= this->GetModel	(); if ( ! pModel	) return FALSE;		// mo Model -> DELETE ME !

	//
	//	START MDS
	//
	pModel	->ApplyModelProtoOverlay	(mdsName);												// [Moos] dass hier nicht ApplyOverlay() aufgerufen wird, ist OK; es ist ja nur ein tempor�res Overlay.
	pAniCtrl->InitAnimations			();

	// Create Entry
	oCNpcTimedOverlay* entry = zNEW(oCNpcTimedOverlay)(mdsName,timer);
	timedOverlays.Insert(entry);
	
	return TRUE;
}

// *****************************
// *** Events : Conversation ***
// *****************************

zBOOL oCNpc :: EV_OutputSVM_Overlay (oCMsgConversation* csg)
{
	if (csg->number==-1) {
	
		oCNpc* other = zDYNAMIC_CAST<oCNpc>(csg->target);
		// Darf ich was zu dem anderen sagen ?
		if (csg->target && other) {
			// Sagt schon ein anderer was zu "other"
			if ((other->GetTalkingWith()!=NULL) && (other->GetTalkingWith()!=this)) {
				// Ist einer von uns bereits im dialog (ZS_TALK) ?
				int index = parser.GetIndex("ZS_TALK");
				if ( GetTalkingWith()!=NULL )
				if ( state.IsInState(index) || GetTalkingWith()->state.IsInState(index)) {
					// ... dann mal nichts sagen
					zERR_MESSAGE(5,0,"U: NPC: Output-Unit "+csg->name+" not started. Another NSC is having a conversation with targetNpc :"+other->GetInstanceName());
					return TRUE;
				}
			}
		}

		oCSVMManager* svm = ogame -> GetSVMManager();
		csg->number = svm -> GetOU (csg->name,GetVoice());
		if (csg->number>=0) {
			// AI - Output - checken
			if (!ogame->GetCutsceneManager()->LibValidateOU(csg->number)) {				
				zERR_WARNING("U: AI: Output-unit-number "+csg->name+"/"+zSTRING(csg->number)+" not found !");
				return TRUE;
			}
			
			if (ogame->GetCutsceneManager()->LibIsSvmModuleRunning(csg->number))
			{
				zERR_MESSAGE(4,0,"B: AI: SVM-Module is still running. Ignoring ...");
				return TRUE;
			};
			
			// Daten aus entsprechender OU uebers CutsceneSystem besorgen.
			zCCSCutsceneContext* cs = ogame->GetWorld()->GetCutscenePlayer()->CreateNewOutputUnit(csg->number,this);
			if (cs) 
			{
				zTCSBlockPosition	pos		= cs->GetFirstBlockPosition();
				oCMsgConversation*	convMsg	= NULL;
				zCEventMessage*		msg		= cs->GetNextMessage(pos);
				while (msg) {				
					convMsg = zDYNAMIC_CAST<oCMsgConversation>(msg);				
					if (convMsg && (convMsg->GetSubType()==oCMsgConversation::EV_PLAYANISOUND)) {
						// Getting the data
						csg->name	= convMsg->name;		// Sound....
						csg->text	= convMsg->text;		// text...
					}
                    msg		= cs->GetNextMessage(pos);
				}

				// I'm talking to you
				StartTalkingWith(other);
				ogame->GetCutsceneManager()->LibSvmModuleStart(csg->number);			
			}
			else
			{
				csg->number=-1;
				return TRUE;
			}			
			zRELEASE(cs);
			

		} else {
			zERR_WARNING("U: AI: No Output-unit number found:"+zSTRING(name));
			return TRUE;
		}
	} 	

	zBOOL finished = TRUE;
	if (csg->number>=0) {
	
		// Still running this shitty Message ???????
		finished = EV_PlaySound(csg);
		if (finished)
		{
			ogame->GetCutsceneManager()->LibSvmModuleStop(csg->number);
		}
			
	}
	return finished;
};

zBOOL oCNpc :: EV_OutputSVM (oCMsgConversation* csg)
{
	
	oCNpc* other = zDYNAMIC_CAST<oCNpc>(csg->target);
	// Darf ich was zu dem anderen sagen ?
	if (csg->target && other) {
		// Sagt schon ein anderer was zu "other"
		if ((other->GetTalkingWith()!=NULL) && (other->GetTalkingWith()!=this)) {
			// Ist einer von uns bereits im dialog (ZS_TALK) ?
			int index = parser.GetIndex("ZS_TALK");
			if ( GetTalkingWith()!=NULL )
			if ( state.IsInState(index) || GetTalkingWith()->state.IsInState(index)) {
				// ... dann mal nichts sagen
				zERR_MESSAGE(5,0,"U: NPC: Output-Unit "+csg->name+" not started. Another NSC is having a conversation with targetNpc :"+other->GetInstanceName());
				return TRUE;
			}
		}
	}

	oCSVMManager* svm = ogame -> GetSVMManager();
	csg->number = svm -> GetOU (csg->name,GetVoice());
	if (csg->number>=0) {
		// AI - Output - checken
		if (!ogame->GetCutsceneManager()->LibValidateOU(csg->number)) {
			zERR_WARNING("U: AI: Output-unit-number "+csg->name+"/"+zSTRING(csg->number)+" not found !");
			return TRUE;
		}
		// I'm talking to you
		StartTalkingWith(other);
		state.StartOutputUnit(csg->number);

		return TRUE;

	
	} else {
		zERR_WARNING("U: AI: No Output-unit number found:"+zSTRING(name));
	}
	return TRUE;
};

zBOOL oCNpc :: EV_Output (oCMsgConversation* csg)
{	
	oCNpc* other = zDYNAMIC_CAST<oCNpc>(csg->target);
	// Darf ich was zu dem anderen sagen ?
	if (csg->target && other) {
		// Sagt schon ein anderer was zu "other"
		if ((other->GetTalkingWith()!=NULL) && (other->GetTalkingWith()!=this)) {
			// Ist einer von uns bereits im dialog (ZS_TALK) ?
			int index = parser.GetIndex("ZS_TALK");
			if ( GetTalkingWith()!=NULL )
			if ( state.IsInState(index) || GetTalkingWith()->state.IsInState(index)) {
				// ... dann mal nichts sagen
				zERR_MESSAGE(5,0,"U: NPC: Output-Unit "+csg->name+" not started. Another NSC is having a conversation with targetNpc :"+other->GetInstanceName());
				return TRUE;
			}
		}
	}

	// �ber Namen die Nummer ermitteln
	// AI - Output - checken
	csg->number = ogame->GetCutsceneManager()->LibValidateOU(csg->name);
	if (csg->number<0) {
		zERR_WARNING("U: AI: Output-unit "+zSTRING(csg->name)+" not found !");
		return TRUE;
	}
	// I'm talking to you
	StartTalkingWith		(other);
	state.StartOutputUnit	(csg->number);
	return TRUE;
}

zBOOL oCNpc :: EV_PlayAni(oCMsgConversation* csg)
{
	zCModel* model = GetModel();
	if (!csg->IsInUse()) {
		// PATCH : Falls es eine 2_STAND - Ani ist, nur dann starten, 
		// wenn Stand-Ani noch nicht laeuft
		if (model->IsAniActive(anictrl->_s_walk))
		{
			if (csg->name.Search("_2_STAND")>0) 
			{
				// Safety :Stand Ani nochmal starten
				model->StartAni(anictrl->_s_walk);
				return TRUE;
			}
		}

		if (!csg->name.IsEmpty())
		{
			if (csg->name[0]=='R' && csg->name[1]=='_')
			{
				// roam anis nicht smoothen
				model->SetSmoothRootNode(FALSE);
			}
			else
			{
				model->SetSmoothRootNode(TRUE);
			}
		}

		csg->cAni = model->GetAniFromAniName(csg->name);
		if (csg->cAni) {
			csg->ani = csg->cAni->GetAniID();
		}		
		if (csg->ani!=zMDL_ANI_ID_ILLEGAL)	model -> StartAni(csg->ani);
		// Damit auch AniBlend davon erfasst werden.
		else								model -> StartAni(csg->name);
		// Falls in MobINteraktion, Bodystate nicht verlieren.
		if (GetInteractMob()) {
			GetInteractMob()->SetMobBodyState(this);
		} else {
			SetBodyState(csg->number & BS_ONLY_STATE);
		}
		csg		-> SetInUse (TRUE);
	};
	zBOOL result = !model->IsAniActive( csg->ani );
	m_bAniMessageRunning = !result;
	return result;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_PlayAniFace()

 

    29-Aug-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/
zBOOL oCNpc :: EV_PlayAniFace(oCMsgConversation* csg)
{
	this->StartFaceAni( csg->name );
	return TRUE;
}
 
zTModelAniID oCNpc :: StartDialogAni ()
{
	if (!HasBodyStateFreeHands() || (GetWeaponMode()!=NPC_WEAPON_NONE) || HasBodyStateModifier(BS_SIT)) return zMDL_ANI_ID_ILLEGAL;

	zTModelAniID aniID	= zMDL_ANI_ID_ILLEGAL;
	zCModel* model		= GetModel();
	if (model) {
		int numDialogAnis	= 20;
		int x				= (zRand() % numDialogAnis) + 1;
		zSTRING num			= zSTRING(x);
		if (x<10) num = "0" + num;

		aniID				= model->GetAniIDFromAniName("T_DIALOGGESTURE_"+num);
		model -> StartAni (aniID);
	};
	return aniID;
};

zBOOL oCNpc :: EV_PlayAniSound(oCMsgConversation* csg)
// Immer Default Ani Mechanismus benutzen
{
	
	zCModel* model	= GetModel();
	zBOOL firstTime = !csg->IsInUse();
	// Ani starten. Nur einen Versuch !!!
	if (firstTime) 
	{
		csg->ani = StartDialogAni();							
	}
	// Sound starten -> Dort wird SetInUse auf TRUE gesetzt.
	
	if (EV_PlaySound(csg))			
	{		
		// Sound abgearbeitet, Ani stoppen
		model->FadeOutAni(csg->ani);
		return TRUE;
	}
	
	if (firstTime) csg->SetInUse(TRUE);

	return FALSE;
}


zBOOL oCNpc :: ActivateDialogCam(zREAL timems)
{	
//	return FALSE;

	if (GetTalkingWith()) {
		// Einer der beiden muss in ZS_Talk sein.
		int index = parser.GetIndex("ZS_TALK");
		if (state.IsInState(index) || GetTalkingWith()->state.IsInState(index)) {
			// Zielgerichtet und im ZS_Talk -> DislogCamera an.
			zCArray<zCVob*> targetList;
			targetList.Insert(this);
			targetList.Insert(GetTalkingWith());
			if (timems>0.0f) ogame->GetCameraAI()->SetDialogCamDuration(timems);
			ogame->GetCameraAI()->SetMode(CamModDialog,targetList);
			return TRUE;
		}
	}
	return FALSE;
}		

zBOOL oCNpc :: DeactivateDialogCam()
{
	//
	//	CHECK STATIC DIALOG CAMERA STOP DISABLING OVERRIDE
	//
	if ( ! oCNpc::s_bEnabledDialogCamStop )
		return FALSE;
	
	static zREAL dialogCamTreshold = 0.0f;

	oCNpc*	other			= GetTalkingWith();
	zBOOL	stopDialogCam	= (other==NULL);
	if (!stopDialogCam) {
		int index = parser.GetIndex("ZS_TALK");
		stopDialogCam = (!other->state.IsInState(index));
	}
	if (stopDialogCam) {
		// Treshold einbauen
		dialogCamTreshold += ztimer.GetFrameTimeF();
		if (dialogCamTreshold > 1000) {
			ogame->GetCameraAI()->SetMode(CamModNormal);
			dialogCamTreshold = 0.0f;
		}
	} else {
		dialogCamTreshold = 0.0f;
	}
	return stopDialogCam;
}		

zBOOL oCNpc :: EV_PlaySound(oCMsgConversation* csg)
{
	zBOOL	stop	= FALSE;
	csg -> f_yes	= oCGame::oEGameDialogView::GAME_VIEW_AMBIENT;
	
	if (!csg->IsInUse()) 
	{	
		csg->handle = 0;
		zCSoundFX* sfx = zsound->LoadSoundFX(csg->name);
		if (sfx) {
			// Pitchvarianz ?
			zCSoundSystem::zTSound3DParams params;
			params.SetDefaults();
			params.pitchOffset = GetVoicePitch();
			zREAL revLevel = oCGame::GetUseSpeechReverbLevel();
			if (revLevel==0) params.reverbLevel = 0.0f; else
			if (revLevel==1) params.reverbLevel = 0.5f; else
			if (revLevel==2) params.reverbLevel = 1; 

			csg -> handle = (zTSoundHandle) zsound->PlaySound3D(sfx,this,2,&params);			
			csg -> f_no = 0;			
			
			// CODECHANGE [SPECKELS]						
			listOfVoiceHandles.InsertEnd(csg->handle);
		} 
		StartFaceAni (NPC_TALK_ANI);

		zREAL sfxTime	= 0.0f;
		if (sfx) {
			sfxTime		= sfx->GetPlayingTimeMSEC();
			csg->f_no	= sfxTime;
			// zERR_MESSAGE(3,0,"B: SND: Sound lasts "+zSTRING(csg->f_no)+" ms (sfx)");
		} 
		if (!sfx || (sfxTime <= 50.0f) ) {
			// Sound nicht gefunden - 3 Sekunden warten...
			csg->f_no	= csg->text.Length() * zCView::GetViewTimePerChar();
			csg->f_no	= zMax( NPC_TALK_TIME_MIN, zMin( NPC_TALK_TIME_MAX, (zREAL)csg->f_no) );	//  1000.0f...3000.0f  3000.0f;
			sfxTime		= csg->f_no;
			// zERR_MESSAGE(3,0,"B: SND: Sound lasts "+zSTRING(csg->f_no)+" ms (!sfx)");
		}
		zRELEASE(sfx);

		// Text nur anzeigen, wenn Entfernung nicht gr��er als 5m
		// Dirty Hack : Schuld ist Stefan !
        if ((!oCNpc::player) || 
		   (GetDistanceToVob2(*oCNpc::player)<=1000*1000) || 
		   (GetEM()->GetCutscene() && GetEM()->GetCutscene()->IsGlobalCutscene())) 
		{
			zBOOL	textOut	= FALSE;
			oCNpc*	other	= GetTalkingWith();			
			zCView* view	= NULL;

			zSTRING msg = "U: NPC \""+GetName(TRUE)+"\": PlaySound";
			if (other) msg+=" to \""+other->GetName(TRUE)+"\"";
			msg+=": "+csg->text;
			zERR_MESSAGE(6,0,msg);

			if (! csg->text.IsEmpty() )
			{
				if (other) {
					// Zielgerichtet... Player involved ?
					int   dialogIndex		= parser.GetIndex("ZS_TALK");
					zBOOL playerInvolved	= (IsSelfPlayer() || other->IsSelfPlayer());
					zBOOL inDialog			= (state.IsInState(dialogIndex) || other->state.IsInState(dialogIndex));
					// Dialog
					if (playerInvolved && inDialog) {
						// *** Dialog ***

						//
						//	CODECHANGE [ROMAN]
						//
						csg -> f_yes = oCGame::oEGameDialogView::GAME_VIEW_CONVERSATION;
						view = ::ogame->GetView( (oCGame::oEGameDialogView) csg -> f_yes );
						if ( view ) 
						{
							if (IsSelfPlayer())
							{
								if (oCNpc::IsEnabledTalkBoxPlayer())
									view->DialogMessageCXY("", csg->text+"\n", sfxTime, NPC_COLOR_TALK_PC);
							}
							else
							{
								if (oCNpc::IsEnabledTalkBox())
									view->DialogMessageCXY(GetName(), csg->text+"\n", sfxTime, NPC_COLOR_TALK_NPC);
							}
						}
						//
						//	CODECHANGE [ROMAN] END
						//

						textOut = TRUE;
					} else if (playerInvolved) {
						// *** NSC sagt etwas zum Spieler - kein Dialog - ***
						// ogame->GetTextView()->Printwin( GetName()+":"+csg->text+"\n" )

						//
						//	CODECHANGE [ROMAN]
						//
						csg -> f_yes = oCGame::oEGameDialogView::GAME_VIEW_NOISE;
						view = ::ogame->GetView( (oCGame::oEGameDialogView) csg -> f_yes );
						if ( view ) 
						{							
							if (oCNpc::IsEnabledTalkBoxNoise())
								view->DialogMessageCXY( GetName(), csg->text+"\n", sfxTime, NPC_COLOR_NOISE );
						}
						//
						//	CODECHANGE [ROMAN] END
						//
						textOut = TRUE;
					}
				} 
				if (!textOut) {
					//
					//	CODECHANGE [ROMAN]
					//

					//
					//	GLOBAL CUTSCENE?
					//
					zBOOL bGlobalCutscene = GetHomeWorld() && (GetHomeWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene()!=0);

					if ( (!bGlobalCutscene) && (!other) )
					{
						csg -> f_yes = oCGame::oEGameDialogView::GAME_VIEW_NOISE;
						zCView* view = ogame->GetView((oCGame::oEGameDialogView) csg -> f_yes);
						if (oCNpc::IsEnabledTalkBoxNoise())
							view->DialogMessageCXY(GetName(), csg->text+"\n", sfxTime, NPC_COLOR_NOISE);
					}
					else if ( bGlobalCutscene )
					{
						csg -> f_yes = oCGame::oEGameDialogView::GAME_VIEW_CINEMA;
						zCView* view = ogame->GetView((oCGame::oEGameDialogView) csg -> f_yes );
						if (oCNpc::IsEnabledTalkBox())
							view->DialogMessageCXY(GetName(), csg->text+"\n", sfxTime, NPC_COLOR_CINEMA);
					}
					else
					{
						csg -> f_yes = oCGame::oEGameDialogView::GAME_VIEW_AMBIENT;
						zCView* view = ogame->GetView((oCGame::oEGameDialogView) csg -> f_yes );
						if (oCNpc::IsEnabledTalkBoxAmbient())
							view->PrintMessageCXY(GetName(), csg->text+"\n", -1.0f, NPC_COLOR_AMBIENT);
					}
					//
					//	CODECHANGE [ROMAN] END
					//
				}
			}
		}
//		else
//			zERR_MESSAGE( 1, 0, "U: NPC: EV_PLAYANISOUND - Player is out of perception range !!!" );

		ActivateDialogCam(sfxTime);

		csg -> SetInUse	(TRUE);
		return FALSE;
	}
	else
	{
		csg->f_no -= ztimer.GetFrameTime();
		stop = (csg->f_no <= 0);

		// [BENDLIN] Addon - FIXME: Fuchteln endet halbe Sekunden vorher...
		if (csg->f_no <= 500)
		{
			zCModel* model = GetModel();
			if (model) {
				for (int i=0; i<model->numActiveAnis; i++) {
					zCModelAniActive* ani = GetModel()->aniChannels[i];
					if (ani && ani->GetAni() && (ani->GetAni()->GetAniName().Search("DIALOGGESTURE_")>=0))
						model->FadeOutAni(ani->GetAni());
				}
				StopFaceAni(NPC_TALK_ANI);
			}
		}
		// patch 1.07 : Falls Sound aktiv, besser das Soundsystem fragen.
		if (!stop && csg->handle!=0) {
			// stop = !zsound->IsSoundActive((zTSoundHandle)csg->handle);
			// Argh ! Diese Abfrage liefert manchmal FALSE, obwohl Sound noch aktiv.!!!!
			// if (stop) zERR_MESSAGE( 5, 0, "U: NPC: EV_PLAYANISOUND stopped. Sound no longer active.");
		}

/*		if (csg->f_no <= 0) {
			if (!zsound->IsSoundActive((zTSoundHandle)csg->handle)) {
//				zERR_MESSAGE( 1, 0, "U: NPC: EV_PLAYANISOUND exceeds expected playing time !!!" );
				if ()
				stop = TRUE;
			};
		} else*/ {
//			zSTRING strTimer = "U: NPC: EV_PLAYANISOUND - Timer : ";	strTimer += csg->f_no;	zERR_MESSAGE( 1, 0, strTimer );
		}
	}

	if (stop) 
	{
		StopFaceAni	(NPC_TALK_ANI);
		StopTalkingWith	();
//		if ( ( (oCGame::oEGameDialogView) csg -> f_yes ) != oCGame::oEGameDialogView::GAME_VIEW_AMBIENT )
//			::ogame->GetView( (oCGame::oEGameDialogView) csg -> f_yes )->Close();
//		zERR_MESSAGE( 1, 0, "U: NPC: EV_PLAYANISOUND was STOPPED !!!" );
	}


	return stop;
}

// [EDENFELD] neu 1.09
zBOOL oCNpc::EV_SndPlay(oCMsgConversation *csg)
{
//	zBOOL bSoundOff = FALSE;
	if (!csg->IsInUse() )
	{
		csg->SetInUse(TRUE);
		zCSoundFX* sfx = zsound->LoadSoundFX(csg->name);

		if (!sfx) return TRUE;
		csg->timer  = sfx->GetPlayingTimeMSEC();
		csg->f_no	= 0;
		

		if (csg->f_yes && csg->target)
		{
			csg->handle = (zTSoundHandle) zsound->PlaySound3D(sfx,csg->target);			
			zREAL sfxTime		= sfx->GetPlayingTimeMSEC();
			csg->f_no	= sfxTime;
			listOfVoiceHandles.InsertEnd(csg->handle);
		}
		else
		{
			zsound->PlaySound(sfx);
		}
		zRELEASE(sfx);
	}

	return (TRUE);
}


// [EDENFELD] neu 1.14d
zBOOL oCNpc::EV_PrintScreen(oCMsgConversation *csg)
{
	int nPosX			= csg->f_no;
	int nPosY			= csg->f_yes;
	int nTimeSeconds	= (int)csg->timer;

	zSTRING strFont		= csg->name;
	zSTRING strMessage	= csg->text; 
																											
	if ( ! strFont.IsEmpty() )																				
	{																										
			 ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->SetFont( strFont );
		if ( ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->GetFont()->GetFontName() != strFont )	//	check for success
		{
			zERR_FAULT("C: oCNpc::EV_PrintScreen: could not load font:" +  strFont);
			return TRUE;
		}
	}

	//															
	//	CALCULATE EFFECTIVE PLACEMENT							
	//															
																
	int		nWidth	,																						//	view's with as specified in virtual coords 
			nHeight		;																					//	view's height as specified in virtual coords 
	float	fWidth	,																						//	percentage-applied view's width 
			fHeight		;																					//	percentage-applied view's height 
	
	nWidth	= VIEW_VXMAX		;
	nHeight = VIEW_VYMAX		;

	fWidth	= (float) nWidth	;									
	fHeight	= (float) nHeight	;
							
	fWidth	*= 0.01f			;										
	fHeight *= 0.01f			;										
							
	fWidth	*= (float) nPosX	;										
	fHeight *= (float) nPosY	;										
							
	nWidth	= (int) fWidth		;
	nHeight	= (int) fHeight		;

	//
	//	ACTUALLY OUTPUT THE MESSAGE
	//

	if		( ( nPosX == - 1 ) && ( nPosY == - 1 ) )	::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimedCXY(				    strMessage, nTimeSeconds * 1000, NULL );
	else if   ( nPosY == - 1 )							::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimedCY ( nWidth,		    strMessage, nTimeSeconds * 1000, NULL );
	else if   ( nPosX == - 1 )							::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimedCX (	       nHeight, strMessage, nTimeSeconds * 1000, NULL );
	else												::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimed	 ( nWidth, nHeight, strMessage, nTimeSeconds * 1000, NULL );

	return TRUE;
}

void oCNpc::AddEffect	(const zSTRING& a_strNewFX, const zCVob* a_pTarget)
{
	if (!oCItem::GetItemEffectsEnabled()) return;

	if (a_strNewFX.IsEmpty()) return;
	// checken, ob bereits so ein effekt l�uft
	for (int i=0; i<effectList.GetNum(); i++)
	{
		oCVisualFX* newFX = effectList[i];
		if (newFX ->GetName()==a_strNewFX) 
		{
			if (newFX->IsFinished())
			{
				effectList.Remove(newFX);
				newFX->Stop();
				zRELEASE(newFX);
				--i;
				break;
			}
			// gibst schon, raus hier. TODO: alten FX updaten
			return;
		}
	}
	// nein, also neuen starten
	oCVisualFX* newFX = oCVisualFX::CreateAndPlay(a_strNewFX, this, a_pTarget);
			
	if (!newFX) 
	{
		zERR_WARNING("C: effect " + a_strNewFX + " could not be started for npc " + this->GetName());
		return;
	}
	
	if (GetVisual()) newFX->SetPFXShapeVisual(GetVisual());

	effectList.Insert(newFX);
}

void oCNpc::RemoveEffect(const zSTRING& a_strFX)
{
	if (a_strFX.IsEmpty()) return;
	// checken, ob �berhaupt so ein effekt l�uft
	for (int i=0; i<effectList.GetNum(); i++)
	{
		oCVisualFX* newFX = effectList[i];
		if (newFX->GetName()==a_strFX) 
		{
			effectList.Remove(newFX);
			newFX->Kill();
			zRELEASE_ACCT_NONULL(newFX);
			return;
		}
	}
};


zBOOL oCNpc::EV_StartFX(oCMsgConversation *csg)
{	
	AddEffect(csg->name, csg->target);
	return TRUE;
}


zBOOL oCNpc::EV_StopFX(oCMsgConversation *csg)
{	
	RemoveEffect(csg->name);
	return TRUE;
}



zBOOL oCNpc :: EV_LookAt(oCMsgConversation* csg)
{

	// B_LookAt beinhaltet das Drehen des K�rpers, 
	// aber nur in K�rperhaltungen, deren Animationen 
	// das FreeHands-Flag haben 
	// (also im Sitzen oder Stehen ohne Waffe). 
	// In allen anderen Haltungen (z.B. Leiterklettern) 
	// dreht sich bei LookAt nur der Kopf!

	if (!csg->IsInUse()) {
		// Gibt's schon eine andere LookAt - Message ?
		// diese dann rauswerfen....
		zBOOL				deletionAllowed	= FALSE;
		oCMsgConversation*	convMsg			= NULL;
		for (int i=0; i<GetEM()->GetNumMessages(); i++) {
			// Nach entsprechender TalkMessage suchen.
			convMsg = zDYNAMIC_CAST<oCMsgConversation>(GetEM()->GetEventMessage(i));
			if (convMsg) {
				if (convMsg == csg) {
					// Nur Sachen l�schen, die schon hinter mir liegen...
					deletionAllowed = TRUE;
				} else if (deletionAllowed && (convMsg->GetSubType()==oCMsgConversation::EV_LOOKAT)) {
					convMsg->Delete(); 
				}
			}
		}
		if (!csg->target) {
			// Kein Target angegeben, �ber Vobnamen ermitteln
			zCWaypoint* wp			= GetHomeWorld()->GetWayNet()->GetWaypoint(csg->name);
			if (wp) csg->targetPos	= wp->GetPositionWorld();
			else csg->target		= GetHomeWorld()->SearchVobByName(csg->name);
		}

		// StoplookAt aufrufen, falls n�tig
		if (  ( csg->target != NULL ) 						&&
			  ( GetAnictrl()->targetVob != csg->target ) )
		{
			// Kopf zur�ck
			GetAnictrl() -> StopLookAtTarget	();
			GetAnictrl() -> StopCombineAni	(GetModel() -> GetAniIDFromAniName("T_QLOOK"));
			GetAnictrl() -> StopCombineAni	(GetModel() -> GetAniIDFromAniName("S_TLOOK"));
		}

		csg->SetInUse(TRUE);
	}

	lastLookMsg = csg;
	if (HasBodyStateFreeHands()) {
		if (csg->target)	anictrl -> SetLookAtTarget(csg->target);
		else				anictrl -> SetLookAtTarget(csg->targetPos);
	} else {
		// Nur Kopf bewegem
		if (csg->ani == zMDL_ANI_ID_ILLEGAL) csg->ani = GetModel() -> GetAniIDFromAniName("S_TLOOK");
		if (csg->target)	anictrl -> StartCombineAni(csg->target,csg->ani,60.0f,45.0f);
		else				anictrl -> StartCombineAni(csg->targetPos,csg->ani,60.0f,45.0f);	
	}

	return FALSE;
}

zBOOL oCNpc :: EV_StopLookAt(oCMsgConversation* csg)
{
	// Letzte LookAtMessage rauswerfen
	if (GetEM()->IsRunning(lastLookMsg)) {
		lastLookMsg->Delete();
		lastLookMsg = NULL;
	}
	// alle weiteren lookat messages rauswerfen
	oCMsgConversation*	convMsg			= NULL;
	for (int i=0; i<GetEM()->GetNumMessages(); i++) 
	{
		// Nach entsprechender TalkMessage suchen.
		convMsg = zDYNAMIC_CAST<oCMsgConversation>(GetEM()->GetEventMessage(i));
		if (convMsg && (convMsg->GetSubType()==oCMsgConversation::EV_LOOKAT)) { 
				convMsg->Delete(); 
		}
	}

	// Kopf zur�ck
	anictrl -> StopLookAtTarget	();


	return TRUE;
}

zBOOL oCNpc :: EV_PointAt(oCMsgConversation* csg)
{
	const zREAL ANGLE_MAX_AZI	= 90.0f;
	const zREAL ANGLE_MAX_ELEV	= 45.0f;

	// Wie beim Ansehen ist es auch m�glich, 
	// NSCs situationsbezogen auf etwas zeigen zu lassen. 
	// Dies funktioniert aber nur f�r humanoide Wesen (Menschen, Orcs, evtl. Gobbos). 
	// Wie bei Quicklook zeigt der NSC nur kurz!
	// Nur bei Anis mit FreeHands-Flag m�glich!
	if (!HasBodyStateFreeHands()) return TRUE;
	
	if (!csg->target && !csg->IsInUse()) {
		// Kein Target angegeben, �ber Vobnamen ermitteln
		zCWaypoint* wp			= GetHomeWorld()->GetWayNet()->GetWaypoint(csg->name);
		if (wp) csg->targetPos	= wp->GetPositionWorld();
		else csg->target		= GetHomeWorld()->SearchVobByName(csg->name);
		csg->SetInUse(TRUE);
	}
	if (csg->target) csg->targetPos = csg->target->GetPositionWorld();

	lastPointMsg = csg;
	
	zREAL azi,elev;
	GetAngles(csg->targetPos,azi,elev);
	if ((abs(azi) > ANGLE_MAX_AZI) || (abs(elev) > ANGLE_MAX_ELEV)) {
		// Point-At Target out of Range	
		anictrl->StopCombineAni(anictrl->s_point);
	
	} else {	
		if (csg->target)	anictrl -> StartCombineAni (csg->target		,anictrl -> s_point, ANGLE_MAX_ELEV, ANGLE_MAX_AZI);
		else				anictrl -> StartCombineAni (csg->targetPos	,anictrl -> s_point, ANGLE_MAX_ELEV, ANGLE_MAX_AZI);
	}
	return FALSE;
}

zBOOL oCNpc :: EV_StopPointAt(oCMsgConversation* csg)
{
	// Letzte LookAtMessage rauswerfen
	if (GetEM()->IsRunning(lastPointMsg)) {
		lastPointMsg ->Delete();
		lastPointMsg = NULL;
	}
	// Kopf zur�ck
	anictrl->StopCombineAni(anictrl->s_point);
	return TRUE;
}
 
zBOOL oCNpc :: EV_QuickLook(oCMsgConversation* csg)
{
	if (!csg->IsInUse()) {
		csg->number = 2000;		// 2 Sekunden lang
		csg->ani	= GetModel()->GetAniIDFromAniName("T_QLOOK");
		csg->SetInUse(TRUE);
	}
	if (csg->target) {
		zVEC3 pos = csg->target->GetBBox3DWorld().maxs;
		
		// Zielausrichtung ermitteln
		zREAL azi,elev;
		zREAL targetx = 0.5f, targety = 0.5f;
	
		GetAngles (pos,azi,elev);
		if (abs(int(azi))<=90)	targetx = (azi  / 120) + 0.5;
		if (abs(int(elev))<=90)	targety = 1 - ((elev / 120) + 0.5);

		zClamp (targetx,0.0f,1.0f);
		zClamp (targety,0.0f,1.0f);
		anictrl->InterpolateCombineAni (targetx, targety, csg->ani );
	}

	csg->number -= ztimer.GetFrameTime();
	if (csg->number<=0) {	
		anictrl->StopCombineAni(csg->ani);
		return TRUE;
	}
	return FALSE;
}

zBOOL oCNpc :: EV_Cutscene (oCMsgConversation* csg)
{
	if (csg->name.IsEmpty()) {
		zERR_WARNING("U: NPC: Tried to play Cutscene (or Output-Unit) with no name. That is evil !");
		return TRUE;
	}

	if (csg->name.Search(".")<=0) csg->name += ".CS";
	
	state.StartCutscene (csg->name,csg->text);

	return TRUE;
}

zBOOL oCNpc ::  EV_WaitTillEnd (oCMsgConversation* csg)
{
	oCNpc* other = zDYNAMIC_CAST<oCNpc>(csg->target);
	if (!other)	return TRUE;
	
	if (GetAnictrl()) {
		GetAnictrl()->StopTurnAnis();
		// Patch 1.08 : Waehrend des Dialoges stehenbleiben....
		if (IsSelfPlayer()) StandUp(FALSE,TRUE);
	}

	if (!other->GetEM()->IsRunning(csg->watchMsg)) {
		// Cutscene-Mode darf nicht mehr aktiv sein....
		// Weil eine AI_Output-Message beim Start aus der Liste genommen wird.
		if (!other->GetEM()->GetCutsceneMode()) {
			return TRUE;
		}
	}
	return FALSE;
}

extern void NotifyInfoToSpy( char* pszMethod, char* pszOutput, char* pszStatus );

zBOOL oCNpc :: EV_StopProcessInfos( oCMsgConversation* csg )
{
	oCInformationManager& mgrInfos = oCInformationManager::GetInformationManager();								
	mgrInfos.Exit();

	// [EDENFELD] 1.09: der npc sollte auch wissen das das gespr�ch beendet ist.
	this->StopTalkingWith();

	return TRUE;																				
}

zBOOL oCNpc :: EV_ProcessInfos( oCMsgConversation* csg )
{
	zBOOL					bFinished	= FALSE;
	oCInformationManager&	mgrInfos	= oCInformationManager::GetInformationManager();		

	//
	//	FIRST RUN
	//
	if ( ! csg->IsInUse() )
	{

		oCNpc* other = zDYNAMIC_CAST< oCNpc > (csg->target);
//		if (!CanBeTalkedTo() || !other->CanBeTalkedTo()) return TRUE;

		if (GetEM()->GetCutsceneMode()) return TRUE;
		if (other && other->GetEM()->GetCutsceneMode()) return TRUE;
		
		mgrInfos.SetNpc(other);								
		csg->SetInUse( TRUE );																	
		return bFinished;
	}

	//
	//	SUBSEQUENT RUNS
	//
	mgrInfos.Update	  ();																		
	bFinished	= mgrInfos.HasFinished();														

	return bFinished;
}

// ****************************************
// Skriptreaktionen - Aktive Wahrnehmungen
// ****************************************

zBOOL oCNpc :: AssessPlayer_S (oCNpc* player)
{
	int func = GetPerceptionFunc (NPC_PERC_ASSESSPLAYER);
	if (func>=0) {
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("SELF" ,this);
		parser.SetInstance		("OTHER",player);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);
	}	
	return (func>=0);
}

zBOOL oCNpc :: AssessEnemy_S (oCNpc* enemy)
{
	// this: der den Feind Wahrnehmende
	int func = GetPerceptionFunc (NPC_PERC_ASSESSENEMY);
	if (func>=0) {
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("SELF" ,this);
		parser.SetInstance		("OTHER",enemy);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);
	}	
	return (func>=0);
}

zBOOL oCNpc :: AssessFighter_S (oCNpc* fighter)
{
	int func = GetPerceptionFunc (NPC_PERC_ASSESSFIGHTER);
	if (func>=0) {
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("SELF" ,this);
		parser.SetInstance		("OTHER",fighter);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);
	}	
	return (func>=0);
}

zBOOL oCNpc :: AssessBody_S (oCNpc* body)
{
	int func = GetPerceptionFunc(NPC_PERC_ASSESSBODY);
	if (func>=0) {
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("SELF" ,this);
		parser.SetInstance		("OTHER",body);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);
	}	
	return (func>=0);
}

zBOOL oCNpc :: AssessItem_S (oCItem* item)
{
	int func = GetPerceptionFunc(NPC_PERC_ASSESSITEM);
	if (func>=0) {
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("SELF" ,this);
		parser.SetInstance		("ITEM" ,item);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);
	}	
	return (func>=0);
}

// ****************************************
// Skriptreaktionen - passive Wahrnehmungen
// ****************************************

void oCNpc :: SetNpcsToState(int stateFunc, int radius)
{
	zCArray<zCVob*>	found;
	oCNpc* npc		= NULL;

	CreateVobList(found, radius);
	
	for (int i=0; i<found.GetNumInList(); i++) {

		npc  = zDYNAMIC_CAST<oCNpc>(found[i]);
		if (npc)												// a) NPC ?
		if (!npc -> IsDead())									// c) sollte schon noch leben
		if (npc  != this) {										// d) nicht sich selber die Wahrnehmung schicken
			npc -> state .StartAIState	(stateFunc,FALSE,AITIME_NO,0.0f);	
		}
	}
};

/*--------------------------------------------------------------------------

    oCNpc::StopCutscene()

    10-Okt-00		[Speckels]
                    SetCutsceneReaction hier eingebaut (THREATEN bei DRAWWEAPON)	

--------------------------------------------------------------------------*/ 

void oCNpc::StopCutscenes()
{
	//
	//	EVTL. CUTSCENE ABBRECHEN
	//
	zCCSCutsceneContext* pCutSceneContext = zDYNAMIC_CAST<zCCSCutsceneContext> (this->GetEM()->GetCutscene());
	if ( pCutSceneContext && !pCutSceneContext->IsOutputUnit() && !pCutSceneContext->IsGlobalCutscene() )
		pCutSceneContext->Stop();
	
};

/*--------------------------------------------------------------------------

    oCNpc::CreatePassivePerception()

    13-Sep-00		[HILDEBRANDT]
					unnoetiges zerr.Separator() im if(sendDebug) Zweig entfernt
	10-Okt-00		[SPECKELS]
					StopCutscene aufgerufen

--------------------------------------------------------------------------*/ 

void oCNpc :: CreatePassivePerception (int percType,zCVob* other, zCVob* victim)
{
	zCArray<zCVob*>	found;
	oCNpc*			npc			= NULL;
	int				func		= -1;
	zBOOL			inMovement	= FALSE;

	CreateVobList(found, percRange[percType]);
	
	// Muss aber deaktiviert werden, wegen zCVobTouchDamage-OnDamage Ringschluss.
	if (percType!=NPC_PERC_ASSESSOTHERSDAMAGE) {
		
		inMovement = GetInMovement();	
		if (inMovement)	{
			SetCollDet	(FALSE);
			EndMovement	();
			SetCollDet	(TRUE);
		}
	}
	
	zSTRING s;
	zBOOL success	= FALSE;
	zBOOL sendDebug = ((percType == NPC_PERC_ASSESSMURDER) || (percType == NPC_PERC_ASSESSDEFEAT));

	sendDebug=TRUE;
	if (sendDebug) {
		zERR_MESSAGE (7,0,"U: NPC: Npc "+GetInstanceName()+" creates "+percNames[percType]);
	}

	for (int i=0; i<found.GetNumInList(); i++) {
		
		npc  = zDYNAMIC_CAST<oCNpc>(found[i]);
		if (npc) {														// a) NPC ?

			success = FALSE;
			s = "Try to send perc to "+npc->GetInstanceName()+" :";

			if ((func = npc -> GetPerceptionFunc(percType)) >= 0) 		// b) Wahrnehmung relevant ?
			if (npc != this)											// b) nicht sich selber die Wahrnehmung schicken
			if (!npc -> IsDead())										// c) sollte schon noch leben
			if (!npc -> IsAPlayer()) {									// e) darf auch nicht ein Spieler sein
				
				npc->StopCutscenes();	// cutscenes stoppen
				
				// Npc hat diesen "Npc" wahrgenommen
				npc -> ForceVobDetection(this);			
				// Alles klar, passive Wahrnehmung starten
				// "SELF" wird im StartAIState gesetzt
				parser.SetInstance			("VICTIM"	,victim);
				parser.SetInstance			("OTHER"	,other);
				success = npc -> state .StartAIState (func,FALSE,AITIME_NO,0.0f);				
			}

			if (!success) {
				if (npc -> GetPerceptionFunc(percType) <= 0)	s+="failed. Perception is not activated.";	// b) Wahrnehmung relevant ?
				else if (npc == this)							s+="failed. Npc is sender.";				// b) nicht sich selber die Wahrnehmung schicken
				else if (npc -> IsDead())						s+="failed. Npc is dead.";					// c) sollte schon noch leben
				else if (npc -> IsAPlayer())					s+="failed.	Npc is player.";				// e) darf auch nicht ein Spieler sein
				else s+="failed. StartAIState failed. Why the heck does this happen ?";
				
				s+= "/ Current State : "+npc->state.GetStateInfo();
				
				if (sendDebug) zERR_MESSAGE(7,0,"U: _PERC: "+s);
			} else {
				s+="success.";
				if (sendDebug) zERR_MESSAGE(7,0,"U: _PERC: "+s);			
			}

		}
	}

	if (sendDebug) {
		zERR_MESSAGE	(7,0,"U: NPC: Npc "+GetInstanceName()+" passive perc creation stops.");
	};

	if (inMovement)	 BeginMovement();
};

void oCNpc :: CreateSoundPerception	(int percType, zCVob* source, const zVEC3& position, zCVob* victimVob, zBOOL setVictim)
{
	zCArray<zCVob*>	found;
	oCNpc* npc		= NULL;
	int    func		= -1;

	zTBBox3D bbox;
	zREAL distance	 = percRange[percType];
	bbox.maxs		 = bbox.mins = position;	
	bbox.maxs[0]	+= distance; bbox.maxs[1]	+= distance; bbox.maxs[2]	+= distance;
	bbox.mins[0]	-= distance; bbox.mins[1]	-= distance; bbox.mins[2]	-= distance;
	ogame->GetGameWorld()->CollectVobsInBBox3D (found, bbox);	
	
	zBOOL inMovement = FALSE;
	oCNpc* npcSource = zDYNAMIC_CAST<oCNpc>(source);
	if (npcSource) {
		inMovement = npcSource->GetInMovement	();
		if (inMovement)	npcSource->EndMovement	();
	}

	for (int i=0; i<found.GetNumInList(); i++) {
		
		// FIXME : Sehen ??????
		npc  = zDYNAMIC_CAST<oCNpc>(found[i]);
		if (npc)												// a) NPC ?
		if ((func = npc -> GetPerceptionFunc(percType)) >= 0)	// b) Wahrnehmung relevant ?
		if (!npc -> IsDead())									// c) sollte schon noch leben
		if (npc  != source)										// d) nicht sich selber die Wahrnehmung schicken
		if (!npc -> IsAPlayer()) {								// e) darf auch nicht ein Spieler sein

			// StopCutscenes();	// cutscenes stoppen

			// Parser variablen aktualisieren				
			if ( setVictim ) parser.SetInstance("VICTIM"	,zDYNAMIC_CAST<oCNpc>(victimVob));
			parser.SetInstance("OTHER"	,zDYNAMIC_CAST<oCNpc> (source)); 
			parser.SetInstance("ITEM"	,zDYNAMIC_CAST<oCItem>(source));

			// Npc hat diesen "Npc" wahrgenommen
			npc -> ForceVobDetection	(source);			
			// Alles klar, passive Wahrnehmung starten
			// "SELF" wird im StartAIState gesetzt
			npc -> SetSoundSource		(0,source,(zVEC3)position);
			npc -> state .StartAIState	(func,FALSE,AITIME_NO,0.0f);	
		}
	}

	if (npcSource && inMovement)	 npcSource->BeginMovement();
}

zBOOL oCNpc :: AssessMurder_S	(oCNpc* comitter)
// this : gemordeter NSC
// Sende Wahrnehmung MURDER an alle NSC in Umgebung aus
{
	CreatePassivePerception	(NPC_PERC_ASSESSMURDER,comitter,this);
	return TRUE;
};

#if 1
zBOOL oCNpc :: AssessThreat_S	(oCNpc* other)
// this : bedrohter NSC
{
	if (s_assessThreatLastEnemy != this)
	{
		s_assessThreatCounter		= ::ASSESS_THREAT_TIME;
		s_assessThreatLastEnemy	= other;
	}
	else
	{
		s_assessThreatCounter += ztimer.GetFrameTimeF();
	}

	if (s_assessThreatCounter >= ASSESS_THREAT_TIME) 
	{
		s_assessThreatCounter -= ASSESS_THREAT_TIME;
		// aktive Wahrnehmung beim anvisierten NSC
		int func = GetPerceptionFunc(NPC_PERC_ASSESSTHREAT);
		if (func>=0) {	
			StopCutscenes();	// cutscenes stoppen

			parser.SetInstance		("OTHER",other);
			state .StartAIState		(func,FALSE,AITIME_NO,0.0f);	
			return TRUE;
		};
		return FALSE;
	}
	return TRUE;
};
#else

zBOOL oCNpc :: AssessThreat_S	(oCNpc* other)
// this : bedrohter NSC
{
	// aktive Wahrnehmung beim anvisierten NSC
	int func = GetPerceptionFunc(NPC_PERC_ASSESSTHREAT);
	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("OTHER",other);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);	
		return TRUE;
	};
	return FALSE;
};
#endif


zBOOL oCNpc :: AssessDefeat_S	(oCNpc* comitter)
// this : geschlagener NSC
{
	CreatePassivePerception (NPC_PERC_ASSESSDEFEAT,comitter,this);
	return TRUE;
};

zBOOL oCNpc :: AssessDamage_S	(oCNpc* comitter, int damage)
// this : getroffener NSC
{		
	// aktive Wahrnehmung beim getroffenen NSC
	int func = GetPerceptionFunc(NPC_PERC_ASSESSDAMAGE);
	// [Ulf] : (AtHome2)
	if (func>=0) 
	{	
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("OTHER"  ,comitter);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);	
	};
	// Passive Wahrnehmung bei anderen NSCs (other = comitter, this = victim)
	AssessOthersDamage_S		(comitter, this, damage);
	return TRUE;
};

zBOOL oCNpc :: AssessOthersDamage_S	(oCNpc* comitter, oCNpc* victim, int damage)
// this : getroffener NSC
{
	CreatePassivePerception (NPC_PERC_ASSESSOTHERSDAMAGE,comitter,victim);
	return TRUE;
};

zBOOL oCNpc :: AssessRemoveWeapon_S ( oCNpc* other )
// this		: SC hat Waffe weggesteckt
// FIXME	: Other wird so nicht mehr ben�tigt
{
	CreatePassivePerception (NPC_PERC_ASSESSREMOVEWEAPON,this);
	return TRUE;
/*	int func = GetPerceptionFunc(NPC_PERC_ASSESSREMOVEWEAPON);
	if (func) {	
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance		("OTHER", other);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);	
	};
	return TRUE;*/
}


zBOOL oCNpc :: ObserveIntruder_S ( )
// this : stehengebliebener (N)SC
{
	zBOOL inMove = GetInMovement();
	if (inMove) EndMovement();
	CreatePassivePerception (NPC_PERC_OBSERVEINTRUDER,this);
	if (inMove) BeginMovement();
	return TRUE;
};

zBOOL oCNpc :: AssessFightSound_S (zCVob* soundVob, const zVEC3& soundPosition, zCVob* victimVob)
{
	CreateSoundPerception	(NPC_PERC_ASSESSFIGHTSOUND,soundVob,soundPosition,victimVob,TRUE);
	return TRUE;
};

zBOOL oCNpc :: AssessQuietSound_S (zCVob* soundVob, const zVEC3& soundPosition)
{
	g_bDontKillOUSound = TRUE;
	CreateSoundPerception	(NPC_PERC_ASSESSQUIETSOUND,soundVob,soundPosition,NULL,FALSE);
	g_bDontKillOUSound = FALSE;
	return TRUE;
};

zBOOL oCNpc :: AssessWarn_S ( oCNpc* comitter )
// this = NSC der alle anderen warnt.
{
	CreatePassivePerception (NPC_PERC_ASSESSWARN,comitter);
	return TRUE;
}

zBOOL oCNpc :: CatchThief_S ( oCNpc* thief )
// this : bestohlener NSC, aktive Wahrnehmung
{
	// aktive Wahrnehmung beim bestohlenen NSC
	int func = GetPerceptionFunc(NPC_PERC_CATCHTHIEF);
	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance	("OTHER",thief );
		state .StartAIState	(func,FALSE,AITIME_NO,0.0f);	
		return TRUE;
	};
	return FALSE;
}

zBOOL oCNpc :: AssessTheft_S ( oCNpc* thief )
// this -> Bestohlener NSC, der aber noch nichts mitgekriegt hat, sendet Wahrnehmung aus
{
	CreatePassivePerception (NPC_PERC_ASSESSTHEFT,thief,this);
	return TRUE;
}

zBOOL oCNpc :: AssessCall_S ( oCNpc* pc )
{
	// aktive Wahrnehmung beim angesprochenen NSC
	int func = GetPerceptionFunc (NPC_PERC_ASSESSCALL);
	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance	("OTHER",pc );
		state .StartAIState	(func,FALSE,AITIME_NO,0.0f);	
		return TRUE;
	};	
	return FALSE;
}

zBOOL oCNpc :: AssessTalk_S ( oCNpc* pc )
{
	// aktive Wahrnehmung beim angesprochenen NSC
	int func = GetPerceptionFunc (NPC_PERC_ASSESSTALK);
	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance	("OTHER",pc );
		state .StartAIState	(func,FALSE,AITIME_NO,0.0f);	
		return TRUE;
	};	
	return FALSE;
}

zBOOL oCNpc :: AssessGivenItem_S ( oCNpc* pc, oCItem* item )
{
	// aktive Wahrnehmung beim angesprochenen NSC
	int func = GetPerceptionFunc (NPC_PERC_ASSESSGIVENITEM);
	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen

		parser.SetInstance	("OTHER",pc );
		parser.SetInstance	("ITEM" ,item);
		state .StartAIState	(func,FALSE,AITIME_NO,0.0f);	
		return TRUE;
	};
	return FALSE;
};

zBOOL oCNpc :: AssessMagic_S ( oCNpc* other, int spellType )
// Magie wird auf "self" von "other" ausge�bt
{
	// Player wird besonders behandelt.
	int func = -1;
	if (IsSelfPlayer() && !state.IsScriptStateActive()) {
		// Player-Default Wahrnehmung nur benutzen, wenn Player in keinem Zustand ist.
		func = playerPercAssessMagic;
	} else {
		func = GetPerceptionFunc	(NPC_PERC_ASSESSMAGIC);
	}

	if (func>=0) {			
		zERR_MESSAGE			(9,0,"U:NPC: oCNpc :: AssessMagic_S() activated.");
		StopCutscenes			();	// cutscenes stoppen

		parser.SetInstance		("OTHER"  ,other);
		state .StartAIState		(func,FALSE,AITIME_NO,0.0f);		
		return TRUE;
	}
	else zERR_WARNING("U:NPC: Could not send PERC AssessMagic to npc " + this->GetName() + ". Current State is " + state.curState.name + " (ignore warning if npc is in a magic state (e.g. ZS_MagicSleep)" );

	return FALSE;
}

zBOOL oCNpc :: AssessStopMagic_S ( oCNpc* other, int spellType )
// Magie wird auf "self" von "other" ausge�bt
{
	// Player wird besonders behandelt.
	int func = -1;
	if (IsSelfPlayer() && !state.IsScriptStateActive()) {
		// Player-Default Wahrnehmung nur benutzen, wenn Player in keinem Zustand ist.
		func = playerPercAssessStopMagic;
	} else {
		func = GetPerceptionFunc	(NPC_PERC_ASSESSSTOPMAGIC);
	}

	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen

		zERR_WARNING("U:NPC:       AssessStopMagic activated.");
		parser.SetInstance		("OTHER"  ,other);
		state .StartAIState(func,FALSE,AITIME_NO,0.0f);
		return TRUE;
	}
	else zERR_WARNING("U:NPC: Could not send PERC AssessStopMagic to npc " + this->GetName() + ". Current State is " + state.curState.name );

	return FALSE;
}

zBOOL oCNpc :: AssessCaster_S ( oCSpell* spell )
{
	CreatePassivePerception	(NPC_PERC_ASSESSCASTER,this);
	return TRUE;
}

zBOOL oCNpc :: AssessFakeGuild_S ()
// this = Spieler, der sich umzieht
{
	if (!IsSelfPlayer()) return FALSE;
	// Passives Sehen. Wird ausgesendet, sobald ein SC seine R�stung wechselt 
	// oder sich verwandelt (nicht bei R�ckwandlung oder ausziehen!)
	CreatePassivePerception (NPC_PERC_ASSESSFAKEGUILD,this);
	return TRUE;
};

zBOOL oCNpc :: MoveMob_S ( oCMOB* mob )
{
	// aktive Wahrnehmung beim getroffenen MOB
	int func = GetPerceptionFunc (NPC_PERC_MOVEMOB);
	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen

		state .StartAIState	(func,FALSE,AITIME_NO,0.0f);	
		return TRUE;
	};	
	return FALSE;
};

zBOOL oCNpc :: AssessUseMob_S (oCMobInter* mob)
// eigene passive assessUseMob-Wn bei Sc fummelt anT�r/Truhe/Schlo�, 
// rum aber auch sitzt auf Stuhl etc.
{
	if (!mob)				return FALSE;
	if (!IsSelfPlayer())	return FALSE;
	// aktives Mob in rbt-Struktur setzen und so den Zugriff �ber Build-Ins damit aktivieren.
	rbt.obstVob = mob;
	CreatePassivePerception(NPC_PERC_ASSESSUSEMOB,this);
	return TRUE;
};

zBOOL oCNpc :: MoveNpc_S ( oCNpc* other )
{
	// aktive Wahrnehmung beim getroffenen NSC
	int func = GetPerceptionFunc (NPC_PERC_MOVENPC);
	if (func>=0) {	
		StopCutscenes();	// cutscenes stoppen
		parser.SetInstance	("OTHER",other);
		state .StartAIState	(func,FALSE,AITIME_NO,0.0f);	
		return TRUE;
	};
	return FALSE;
}

zBOOL oCNpc :: AssessEnterRoom_S ( )
{
	CreatePassivePerception	(NPC_PERC_ASSESSENTERROOM,this);
	return TRUE;
}

// ****************************************
// Logische Sounds
// ****************************************

zREAL oCNpc :: GetDistToSound ()
{
	return (soundPosition - GetPositionWorld()).LengthApprox();
};

zCVob* oCNpc :: GetSoundSource ()
{
	return soundVob;
};

void oCNpc :: SetSoundSource (int sndType, zCVob* sndVob, zVEC3& sndPos)
{
	soundType		= sndType;
	soundVob		= sndVob;
	if (soundVob)	soundPosition	= soundVob->GetPositionWorld();
	else			soundPosition	= sndPos;
}

// ****************************************
// Wahrnehmungen
// ****************************************

void oCNpc :: ClearPerceptionLists()
{
	ClearFocusVob	();
	ClearVobList	();
};

zBOOL oCNpc :: IsMoreImportant	( zCVob* vob1, zCVob* vob2 )
{	
	// Ist Npc1 wichtiger als Npc2
	if (!vob1) return FALSE;
	if (!vob2) return TRUE;

	// Entfernungen ber�cksichtigen
	return (GetDistanceToVob2(*vob1) < GetDistanceToVob2(*vob2));	
	// OLD : return (!npc2 || npc2->IsAPlayer());
}

void oCNpc :: CreateVobList	(zCArray<zCVob*>& found, zREAL distance)
// Erstelle Liste umgebender NSCs - f�r passive Wahrnehmung
{
	if (!GetHomeWorld()) return;

	zTBBox3D bbox;
	bbox.maxs		 = bbox.mins = GetPositionWorld();	
	bbox.maxs[0]	+= distance; bbox.maxs[1]	+= distance; bbox.maxs[2]	+= distance;
	bbox.mins[0]	-= distance; bbox.mins[1]	-= distance; bbox.mins[2]	-= distance;
	GetHomeWorld()  -> CollectVobsInBBox3D (found, bbox);	
};

void oCNpc :: ClearVobList ()
{
//	if (!IsSelfPlayer() || force)
    for (int i=0; i<vobList.GetNumInList(); i++) zRELEASE_ACCT(vobList[i]);
    vobList.DeleteList();
//    }
}


void oCNpc :: InsertInVobList(zCVob *v){
	if (v && !vobList.IsInList(v)) {
		vobList.Insert(v);
		zADDREF_ACCT(v);
	};
}


void oCNpc :: RemoveFromVobList(zCVob *v){
	if (v && vobList.IsInList(v)) {
		vobList.Remove(v);
		zRELEASE_ACCT(v);
	};
}

void oCNpc :: CreateVobList (zREAL max_dist)
{
	if (!GetHomeWorld()) return;

    ClearVobList(); // [Moos] Leakfix

	zTBBox3D bbox;
	
	bbox.maxs		 = bbox.mins = GetPositionWorld();	
	// Vorderer Punkt
	bbox.maxs[0]	+= max_dist; 
	bbox.maxs[1]	+= max_dist; 
	bbox.maxs[2]	+= max_dist;
	// Hinterer Punkt
	bbox.mins[0]	-= max_dist; 
	bbox.mins[1]	-= max_dist; 
	bbox.mins[2]	-= max_dist;
	// sammeln
	GetHomeWorld() -> CollectVobsInBBox3D	(vobList, bbox);	
	// selber fliegt raus.
	// vobList.Remove (this);

	// Patch 1.07 - selfIndex und eigenes Object aus Liste damit entfernen
	int selfIndex = -1;
    for (int i = vobList.GetNumInList()-1; i>=0; i--) {
    	zADDREF_ACCT(vobList[i]);
		// selber fliegt raus.
		if (vobList[i] == this) selfIndex = i;
	}
	if (selfIndex>=0) {
    	zRELEASE_ACCT(vobList[selfIndex]);
		vobList.RemoveIndex(selfIndex);
	};
}

void oCNpc :: SetPerceptionTime (zREAL time)
{
	percActiveDelta = time;
	while (percActiveTime>percActiveDelta) percActiveTime -= percActiveDelta;
}

void oCNpc :: PerceiveAll()
{
	if (IsSelfPlayer()) return;

	// Alle Objekte einsammeln ( ITEMS + NPCS )
	zBOOL	remove	= FALSE;
	oCItem* item	= NULL;
	zCVob*	vob		= NULL;

	ClearVobList	();
	CreateVobList	(senses_range);	

	zBOOL globalCutsceneRunning = GetHomeWorld() && (GetHomeWorld()->GetCutscenePlayer()->GetPlayingGlobalCutscene()!=0);

	int	max	= vobList.GetNumInList();	
	for (int i=max-1; i>=0; i--) {	
		remove	= TRUE;
		vob		= vobList[i];
		item	= zDYNAMIC_CAST<oCItem>(vob);
		if (item && !item->HasFlag(ITM_FLAG_NFOCUS)) remove = FALSE;

		// In "Globale"-Cutscenes-Npcs werden nicht wahrgenommen
		if (zDYNAMIC_CAST<oCNpc>(vob) && (!globalCutsceneRunning))	remove = FALSE;
		
		if (remove) {
			//RemoveFromVobList(vob);
			// Patch 1.07 : Faster....			
			vobList.RemoveIndex(i);
			zRELEASE_ACCT(vob);
		}
	}
}

void oCNpc :: PerceptionCheck ()
// F�hre aktive Checks durch
// - assessFighter
// - assessEnemy
// - assessBody
// - assessItem
{
	// Zeit
	percActiveTime += ztimer.GetFrameTimeF();
	if (percActiveTime < percActiveDelta) return;
	percActiveTime -= percActiveDelta;

	ClearVobList	();

	if (GetEM()->GetCutsceneMode()) return;

	// Wahrnehmung n�tig ?
	zBOOL checkNpc	= HasPerception(NPC_PERC_ASSESSPLAYER) || HasPerception(NPC_PERC_ASSESSENEMY) || HasPerception(NPC_PERC_ASSESSFIGHTER) || HasPerception(NPC_PERC_ASSESSBODY);
	zBOOL checkItem	= HasPerception(NPC_PERC_ASSESSITEM);

	if (!checkNpc && !checkItem) return;
	
	CreateVobList	(senses_range);		// 40m

	// ***********
	//  auswerten
	// ***********

	oCNpc*  playerFound		= NULL;
	oCNpc*	enemyFound		= NULL;
	oCNpc*	fighterFound	= NULL;
	oCNpc*	bodyFound		= NULL;
	oCNpc*	npc				= NULL;
	oCItem*	itemFound		= NULL;
	oCItem*	item			= NULL;
	zCVob*	vob				= NULL;
	int		max				= vobList.GetNumInList();
	
	for (int i=max-1; i>=0; i--) {	
		vob = vobList[i];

		if (checkNpc && zDYNAMIC_CAST<oCNpc>(vob)) {
			
			zBOOL removeFromList = TRUE;
			npc = static_cast<oCNpc*>(vob);

			if (npc->IsDead() || npc->IsUnconscious()) {
				
				if (IsMoreImportant(npc,bodyFound) && CanSense(npc)) {

					bodyFound		= npc;
					removeFromList	= FALSE;
				}

			} else if (PercFilterNpc(npc)) {			
				
				if (npc->IsAPlayer() && CanSense(npc)) {
					// Spieler wahrgenommen
					playerFound		= npc;
					removeFromList	= FALSE;
				}
				
				if (IsHostile(npc)) {				
					// *** assessEnemy ***
					if (IsMoreImportant(npc,enemyFound) && CanSense(npc)) {
						enemyFound		= npc;
						removeFromList	= FALSE;
					}
				
				} else if ((npc->GetWeaponMode()!=NPC_WEAPON_NONE) && IsMoreImportant(npc,fighterFound) && CanSense(npc)) {
					// *** assessFighter ***
					fighterFound	= npc;
					removeFromList	= FALSE;
				}
			
			} 

			if (removeFromList) {
				// Zwar NSC, aber uninteressant
//				RemoveFromVobList(vob);
				// Patch 1.07 : Faster....			
				vobList.RemoveIndex(i);
				zRELEASE_ACCT(vob);
				continue;
			}
				

		} else if (checkItem && zDYNAMIC_CAST<oCItem>(vob) && PercFilterItem(item) && IsMoreImportant(item,itemFound) && CanSense(item)) {
		
			// Item gefunden.
			itemFound = item = static_cast<oCItem*>(vob);

		} else {

			// uninteressant.
			//RemoveFromVobList(vob);

			// Patch 1.07 : Faster....			
			vobList.RemoveIndex(i);
			zRELEASE_ACCT(vob);
			continue;
		}
		
		// Interessantes Vob, verweilt in Liste...
//		vob -> AddRef();
	}

	// Jetzt aktive Wahrnehmungen checken.
	for (i=0; i<percActive; i++) {

		// [ALT] Nur die hoechst priorisierte aktive Wahrnehmung wird getriggert
		// [NEU ab 1.13]
		// Alle aktiven Warhnehmungen werden priorisiert abgearbeitet
		// Falls eine Wahrnehmung keine weitere mehr zul�sst, m�ssen diese
		// auf Skriptebene in den entsprechenden B_Funktionen ausgeschaltet werden
		switch (percList[i].percID) {
			
			case NPC_PERC_ASSESSPLAYER	:	if (playerFound) {
												AssessPlayer_S	(playerFound);
												//return;
											}; break;
			case NPC_PERC_ASSESSENEMY	:	if (enemyFound) {
												AssessEnemy_S	(enemyFound);
												//return;
											}; break;
			case NPC_PERC_ASSESSFIGHTER	:	if (fighterFound) {
												AssessFighter_S	(fighterFound);
												//return;
											}; break;

			case NPC_PERC_ASSESSBODY	:	if (bodyFound) {
												AssessBody_S	(bodyFound);
												//return;
											}; break;
			case NPC_PERC_ASSESSITEM	:	if (itemFound) {
												AssessItem_S	(itemFound);
												//return;
											}; break;
		}
	}
}

zBOOL oCNpc :: PercFilterNpc (oCNpc* other)
{
	return TRUE;
}

zBOOL oCNpc :: PercFilterItem (oCItem* item)
{
	if (item->HasFlag(ITM_FLAG_NFOCUS)) return FALSE;
	return TRUE;
}

void oCNpc :: ClearPerception ()
{
	// Gesamte Liste l�schen
	memset(&percList,0,sizeof(percList));
	percActive = 0;		// Number of active Perceptions
}

void oCNpc :: EnablePerception (int percType, int scriptFunc)
{
	for (int i=0; i<percActive; i++) {				
		if (percList[i].percID  == percType) {
			percList[i].percFunc = scriptFunc;
			return;
		} else if (percList[i].percID == 0) {
			// Platz ist frei, diesen benutzen
			percList[i].percID   = percType;
			percList[i].percFunc = scriptFunc;
			return;
		}
	}
	if (percActive >= NPC_PERC_MAX) {
		zERR_WARNING("U: NPC: Tried to enable too many perceptions :"+GetInstanceName());
		return;
	};
	percList[percActive].percID		= percType;
	percList[percActive].percFunc	= scriptFunc;
	percActive++;
}

void oCNpc :: DisablePerception (int percType)
{
	for (int i=0; i<percActive; i++) {		
		if (percList[i].percID == percType) {
			percList[i].percID		= 0;
			percList[i].percFunc	= -1;
			if (i==percActive-1) {
				percActive--;
				break;
			}
		}
	}
}

zBOOL oCNpc :: HasPerception (int percType)
{
	for (int i=0; i<percActive; i++) {		
		if (percList[i].percID == percType) return TRUE;
	}
	return FALSE;
}

int oCNpc :: GetPerceptionFunc (int percType)
{
	for (int i=0; i<percActive; i++) {		
		if (percList[i].percID == percType) return percList[i].percFunc;
	}
	return -1;
}

// Static
void oCNpc :: SetPerceptionRange(int percID, zREAL percDist)
{
	if (percID < NPC_PERC_MAX) percRange[percID] = percDist;
}

zBOOL oCNpc :: IsInPerceptionRange(int percID, zREAL percDist)
{
	if (percID < NPC_PERC_MAX)	return (percDist<=percRange[percID]);
	else						return FALSE;
}

zBOOL oCNpc :: IsInPerceptionRange(int percID, zCVob* vob1, zCVob* vob2)
{
	if (vob1 && vob2)	return IsInPerceptionRange(percID, vob1->GetDistanceToVob(*vob2));
	else				return FALSE;
}

// ****************************************
// InitStatics
// ****************************************

void oCNpc :: InitStatics ()
{	
	int val;
	zCPar_Symbol *sym;
	
	// ******************************************************
	// a) Werte f�r Dauer der temp-Attituden ANGRY / ANNOYED 
	// in Sekunden angegeben.
	// ******************************************************
	sym = parser.GetSymbol("NPC_ANGRY_TIME");
	if (sym) {
		sym->GetValue(val);
		NPC_ANGRY_TIME = val * 1000;
	}
	
	// ******************************************************
	// b) Default Einstellungen der Wahrnehmungsreichweiten
	// ******************************************************
	for (int i=0; i<NPC_PERC_MAX; i++) percRange[i] = 500;
	
	val = parser.GetIndex("INITPERCEPTIONS");
	if (val>=0) parser.CallFunc(val);
	else		zERR_WARNING("U: AI: Script-func InitPerceptions not found.");
	
	// ******************************************************
	// c) Kampf - AI - Init
	// ******************************************************
	InitFightAI();

	// ******************************************************
	// g) BodyStates einlesen
	// ******************************************************
	InitBodyStates();

	// ******************************************************
	// h) Standard-Wahrnehmungen fuern Player
	// ******************************************************
	sym = parser.GetSymbol	("PLAYER_PERC_ASSESSMAGIC");
	if (sym) sym->GetValue	(playerPercAssessMagic);
	sym = parser.GetSymbol	("PLAYER_PERC_ASSESSSTOPMAGIC");
	if (sym) sym->GetValue	(playerPercAssessStopMagic);
	
	if (playerPercAssessMagic	 >=0) zERR_MESSAGE(5,0,"U: NPC: Found player-perception AssessMagic.");
	if (playerPercAssessStopMagic>=0) zERR_MESSAGE(5,0,"U: NPC: Found player-perception AssessStopMagic.");

	// ******************************************************
	// i) ReferenzListe vom Parser fuer NSC-Sckript-DeInit
	// ******************************************************
	if (!parserNpcRefsDone) {
		parser.CreateVarReferenceList("C_NPC",gParserNpcReferenceList);
//		zERR_FAULT("U: NPC: Parser found "+zSTRING(gParserNpcReferenceList.GetNumInList())+" C_NPC Vars.");
		parserNpcRefsDone = TRUE;
	}
}

/* ----------------------------------------------------------------------
	
    oCNpc:: ReleaseStatistics()	

	26.08.2000	[Moos]	
                ExitFightAI() hinzugef�gt


   ---------------------------------------------------------------------- */

void oCNpc :: ReleaseStatics()
{
    ExitFightAI(); 
};

// ****************************************
// Body Status
// ****************************************

int oCNpc :: bodyStateList[BS_MAX];

void oCNpc :: InitBodyStates()
{
	zCPar_Symbol* sym = NULL;
	memset(&bodyStateList,0,sizeof(bodyStateList));
	for (int i=0; i<BS_MAX; i++) {
		sym = parser.GetSymbol(BS_NAMES[i]);
		if (sym && (sym->type==zPAR_TYPE_INT)) {
			sym->GetValue(bodyStateList[i]);
		}
	}
}

void oCNpc :: SetBodyState(int bs)
{
	if ((bs<0) || (bs>=BS_MAX)) {
		zERR_WARNING("U:NPC: Unknown BodyState :"+zSTRING(bs));
	} else {
		// Overlays nicht ver�ndern !!!!
		int nextbsflags	= bodyStateList[bs] & (BS_FLAG_INTERRUPTABLE | BS_FLAG_FREEHANDS);
		int mods		= bodyState & BS_MOD_ACTIVE;
		bodyState		= bs | mods | nextbsflags;
	}
}

int oCNpc :: GetBodyState()
{	
	return (bodyState & BS_ONLY_STATE);
};

int oCNpc :: GetFullBodyState()
// BodyState + Interrupt und Gestenflag
{	
	return (bodyState & (~BS_MOD_ACTIVE));
};

zSTRING oCNpc :: GetBodyStateName()
{
	int bs = GetBodyState();
	if ((bs>=0) && (bs<BS_MAX)) return BS_NAMES[bs];
	else						return "unknown";
};

zBOOL oCNpc :: HasBodyStateModifier(int nr)
{
	return ((bodyState & nr)>0);
};

void oCNpc :: SetBodyStateModifier(int nr)
{
	bodyState |= nr;
};

void oCNpc :: ClrBodyStateModifier(int nr)
{
	bodyState &= (~nr);
}

zSTRING	oCNpc :: GetBodyStateModifierNames()
{
	zSTRING strResult = "";

	if ( this->HasBodyStateModifier( BS_MOD_BURNING		) ) strResult += "BS_MOD_BURNING\n";
	if ( this->HasBodyStateModifier( BS_MOD_CONTROLLED  ) ) strResult += "BS_MOD_CONTROLLED\n";
	if ( this->HasBodyStateModifier( BS_MOD_DRUNK		) ) strResult += "BS_MOD_DRUNK\n";
	if ( this->HasBodyStateModifier( BS_MOD_HIDDEN		) ) strResult += "BS_MOD_HIDDEN\n";
	if ( this->HasBodyStateModifier( BS_MOD_NUTS		) ) strResult += "BS_MOD_NUTS\n";
	if ( this->HasBodyStateModifier( BS_MOD_TRANSFORMED ) ) strResult += "BS_MOD_TRANSFORMED\n";

	return strResult;
}

int	oCNpc :: ModifyBodyState( int add, int remove )
{
	this->SetBodyStateModifier( add );
	this->ClrBodyStateModifier( remove );

	return this->GetBodyState();
}

zBOOL oCNpc :: IsBodyStateInterruptable()
{
	// Overlays - nicht interruptable, keine Gesten...
	if ((bodyState & BS_MOD_ACTIVE)>0)	return FALSE;
	// Sonst Flags benutzen
	return ((bodyState & BS_FLAG_INTERRUPTABLE)>0);
}

zBOOL oCNpc :: HasBodyStateFreeHands()
{
	// Overlays - nicht interruptable, keine Gesten...
	if ((bodyState & BS_MOD_ACTIVE)>0)	return FALSE;
	// Sonst Flags benutzen
	return ((bodyState & BS_FLAG_FREEHANDS)>0);
}

zBOOL oCNpc :: IsInGlobalCutscene()
{
	return (GetEM()->GetCutscene() && GetEM()->GetCutscene()->IsGlobalCutscene());
}

//changed[dennis]
void oCNpc :: MakeSpellBook( void )
{ 
	if (!mag_book) mag_book = zNEW( oCMag_Book() );
	mag_book -> SetOwner(this);
	spells = 1;	// TEMP : Hack !
}

void oCNpc :: DestroySpellBook( void )
{ 
    delete mag_book;
    mag_book=NULL;
}

// ****************************************
// Debug
// ****************************************

void oCNpc :: ShowDebugInfo	(zCCamera *camera)
{
	oCVob :: ShowDebugInfo (camera);

	oCAIHuman* ai = zDYNAMIC_CAST<oCAIHuman>(GetAI());
	if (ai) {
		zSTRING s;

/*		s = "Dirs :"+zSTRING(rbt.lastDirs.GetNumInList()) + "     Angle :" + zSTRING(int(rbt.dirLastAngle));
		s += "    Timer :"+zSTRING(int(rbt.timer));
		screen->Print(0,6000,s);

		s = "Front:"+zSTRING(ai->ir.correction.spacingRayFront);
		screen->Print(0,7000,s);
		s = "Back:"+zSTRING(ai->ir.correction.spacingRayBack);
		screen->Print(2048,7000,s);
		s = "Left:"+zSTRING(ai->ir.correction.spacingRayLeft);
		screen->Print(4096,7000,s);	
		s = "Right:"+zSTRING(ai->ir.correction.spacingRayRight);
		screen->Print(6192,7000,s);
			
		s = "FrontP:"+zSTRING(ai->ir.spacingRayFrontPoly!=NULL);
		screen->Print(0,7250,s);
		s = "BackP:"+zSTRING(ai->ir.spacingRayBackPoly!=NULL);
		screen->Print(2048,7250,s);
		s = "LeftP:"+zSTRING(ai->ir.spacingRayLeftPoly!=NULL);
		screen->Print(4096,7250,s);	
		s = "RightP:"+zSTRING(ai->ir.spacingRayRightPoly!=NULL);
		screen->Print(6192,7250,s);

		s = "LowCeil:"+zSTRING(ai->ir.blocking.lowCeiling);
		screen->Print(0,7500,s);
		s = "Chasm:"+zSTRING(ai->ir.blocking.walkStopChasm);
		screen->Print(2048,7500,s);
		s = "FloorSteep:"+zSTRING(ai->ir.blocking.floorTooSteep);
		screen->Print(4096,7500,s);
		s = "FloorHigh:"+zSTRING(ai->ir.blocking.floorTooHigh);
		screen->Print(6192,7500,s);*/

//		screen->Print(0,5000,"StopChasm :"+zSTRING(GetAnictrl()->zMV_DO_DETECT_WALK_STOP_CHASM));
//		screen->Print(0,5300,"ChasmDetected :"+zSTRING(GetHumanAI()->ir.blocking.walkStopChasm));

		screen->Print(0,5000,"Perc: "+GetInstanceName());

		int x = 0; int y = 5000 + screen->FontY();
		for (int i=0; i<NPC_PERC_MAX; i++) {
			if (HasPerception(i)) {
				if (x>=8192-(8192/3)) 
				{
					y+=screen->FontY();
					x = 0;
				}
				screen->Print(x,y,percNames[i]);
				x += 8192/3;
			}
		}
	}

/*	if (GetEnemy()) {
		zREAL dist;
		zBOOL inRange = npc->IsInFightRange(npc->GetEnemy(),dist);
		s = "Range: " + zSTRING(int(dist)) + "(" + zSTRING(inRange) + ")";
		screen -> Print(x,y,s); 
		y -= screen->FontY();
		if (y<=0) goto _quit;
	}*/
}

zREAL oCNpc::GetDamageMultiplier()
{
	return damageMul;
}

void oCNpc::SetDamageMultiplier( zREAL dm )
{
	damageMul = dm;
}

void oCNpc :: SetNpcAIDisabled	(zBOOL off)		
{
	ai_disabled = off;			
	if (!off) {
		// AI an
		SetMessagesSkip		(  0.0f	);		// on  -> no timer
		SetScriptStateSkip	(  0.0f );		// on  -> no timer
		SetBaseAIEnabled	(  TRUE  );		// on  
	} else {
		// AI aus
		SetMessagesSkip		(  0.0f	);		// on  -> no timer
		SetScriptStateSkip	( -1.0f );		// off -> np script-ai
		SetBaseAIEnabled	(  TRUE );		// on
	}
};

void oCNpc :: ProcessAITimer ()		
{
	if (ai_messagesSkip>0.0f) {
		if (ai_messagesSkipTimer  > ai_messagesSkip) {
			ai_messagesSkipTimer -= ai_messagesSkip;	
		}
		ai_messagesSkipTimer  += ztimer.GetFrameTimeF();
	}

	if (ai_scriptStateSkip >0.0f) {
		if (ai_scriptStateSkipTimer  > ai_scriptStateSkip) {
			ai_scriptStateSkipTimer -= ai_scriptStateSkip;	
		}
		ai_scriptStateSkipTimer	+= ztimer.GetFrameTimeF();
	}
}

zBOOL oCNpc :: IsScriptStateAIEnabled	()
{
	if (ai_scriptStateSkip	== 0.0f) return TRUE;		// immer an
	if (ai_scriptStateSkip	 < 0.0f) return FALSE;		// immer aus
	// Timed
	if (ai_scriptStateSkipTimer  > ai_scriptStateSkip)	return TRUE;
	return FALSE;
}

zBOOL oCNpc :: IsMessageAIEnabled	()
{
	if (ai_messagesSkip	== 0.0f) return TRUE;		// immer an
	if (ai_messagesSkip  < 0.0f) return FALSE;		// immer aus
	// Timed
	if (ai_messagesSkipTimer  > ai_messagesSkip)	return TRUE;
	return FALSE;
}

void oCNpc :: SetShowNews (zBOOL on)
// Temp -> Debug
{
	showNews = on;
};

// ********************************************
// Timed Overlay
// ********************************************

zBOOL oCNpc :: oCNpcTimedOverlay :: Process()
{
	timer -= ztimer.GetFrameTimeF();
	return (timer<=0.0f);
}

// ********************************************
// Bert Special Spacer NSC -.AI
// ********************************************

void oCNpc :: UseStandAI()
{
	SetAI(zNEW( oCAIHuman_Stand(this)) );
	GetAI()->Release();
}


void oCNpc::SetItemEffectControledByModel(oCItem* a_pItem, zCModelNodeInst* a_pNode, const zBOOL a_bModelControl, const zBOOL a_bForceStop, const zBOOL a_bEffectCleanUp)
{
	// das item h�ngt entweder: a) als tree im worldspace
	// b) als child am npc
	// c) nirgendwo

	if ( NULL!=a_pItem ) 
	{
		if ( !a_pItem->effectName.IsEmpty() ) 
		{			
			if (!a_bForceStop) a_pItem->InsertEffect();	// safety

			if ( (NULL!=a_pItem->GetEffect()))
			{

				zCWorld* homeWorld = GetHomeWorld();
				if (!homeWorld) homeWorld = ogame->GetWorld();

				//a_pItem->GetEffect()->SetInflictor(this);// verursacht npc mem leaks bei savegames, ist aber unwichtig

				if (a_bForceStop)
				{
					// hier: maximaler refcounter 3 (oCWorld, oCItem, zCModel), alles entfernen
					GetModel()->RemoveChildVobFromNode(a_pItem->GetEffect());
					a_pItem->GetEffect()->RemoveVobSubtreeFromWorld(); 
					// nur bei clean up
					if (a_bEffectCleanUp) 
					{
						a_pItem->RemoveEffect();
					}
				}
				else if (a_bModelControl)
				{
					// Ein etwaiger parallel laufender oCVisualFX Effekt des a_pItems muss nun manuell 
					// vom Modelsystem geupdated werden, da das a_pItem nun nicht mehr in der Welt ist (zCModel weiss nichts von
					// den a_pItems)
					GetModel()-> RemoveChildVobFromNode		 (a_pItem->GetEffect() ); 
					a_pItem->GetEffect()->SetAllowMovement	 (FALSE);
										
					if (!a_pNode) 
					{
						// sonderfall r�stungen: im gegensatz zu slot-items wzb. waffen 
						// repr�sentiert die (angezogene) r�stung das komplette softskin und wird nicht als node-visual gerendert
						// daher m�ssen wir dem effekt nun sagen, das das pfx-visual nun das model ist
						a_pItem->GetEffect()->SetPFXShapeVisual(this->GetVisual());
						a_pItem->GetEffect()->SetTrafoObjToWorld(this->trafoObjToWorld);						
					}
					else
					{
						a_pItem->GetEffect()->SetPFXShapeVisual(a_pItem->GetVisual());
						GetModel()-> AttachChildVobToNode (a_pItem->GetEffect(), a_pNode);// problem: beim laden eines savegames ist hier noch nicht der vobtree bekannt, also wird dies in updateslots erledigt
						// ab hier RefCtr:2  (zCModel+oCItem)
					}

					if (!a_pItem->GetEffect()->GetHomeWorld()) 
					{
						homeWorld->AddVob(a_pItem->GetEffect());
					}

					// FIXME: w�hrend des ladens eines save-games ist hier der vobtree noch nicht bekannt
					// l�sung: effekt aus der welt entfernen und in updateslots sp�ter an den parent
					// linken
					if (!this->globalVobTreeNode) 
					{
						a_pItem->GetEffect()->RemoveVobSubtreeFromWorld(); 
					}

					homeWorld->MoveVobSubtreeTo	 (a_pItem->GetEffect(), this);
					// ab hier RefCtr: 2 (zCWorld+oCItem) oder 3 (zCWorld+zCModel+oCItem)

					a_pItem->GetEffect()->SetSleeping		 (FALSE);

				}
				else
				{
					// ok, gib dem vob wieder die kontrolle �ber sich selbst
					GetModel()->RemoveChildVobFromNode	   (a_pItem->GetEffect());
					a_pItem->GetEffect()->SetAllowMovement (TRUE);
					homeWorld->MoveVobSubtreeToWorldSpace(a_pItem->GetEffect());
					a_pItem->GetEffect()->SetSleeping	   (FALSE);
					a_pItem->GetEffect()->SetPFXShapeVisual(a_pItem->GetVisual());
				};
			}
		}
	}
};




/*
int	oCNpc :: Release()
{
	int i = 0;
	return zCObject::Release();	
};

zCObject* oCNpc :: AddRef()
{
	int i = 0;
	return zCObject::AddRef();	
};
*/

#if defined(SECUROM) && !defined(COMPILING_SPACER)

#include <tchar.h>
#include "special.h"

zBOOL oCNpc :: EV_Request(oCMsgRequest* csg)
{
	zBOOL bFinished = FALSE;

	if (!csg->IsInUse())
	{
		// First Run
		csg->SetInUse(TRUE);
	}
	else
	{
		csg->delay -= ztimer.GetFrameTimeF();
	}

	// Check delay-time (milliseconds)
	if (csg->delay <= 0)
	{
		bFinished = TRUE;
		switch (csg->subType)
		{
		case oCMsgRequest::EV_REQUEST_0:
		case oCMsgRequest::EV_REQUEST_1:
		case oCMsgRequest::EV_REQUEST_2:
		case oCMsgRequest::EV_REQUEST_3:
		case oCMsgRequest::EV_REQUEST_4:
		case oCMsgRequest::EV_REQUEST_5:
		case oCMsgRequest::EV_REQUEST_6:
		case oCMsgRequest::EV_REQUEST_7:
		case oCMsgRequest::EV_REQUEST_8:
		case oCMsgRequest::EV_REQUEST_9:
			{
			#include "evt_1.inl"
				::ogame->GetSpawnManager()->SetSpawnFlags(NPC_FLAG_IMMORTAL | NPC_FLAG_PROTECTED);
			#include "evt_2.inl"
			}
			break;
		}
	}

	return bFinished;
}
#endif

zCLASS_DEFINITION_SCRIPTED( oCNpc , oCVob	, 0, 7, C_NPC)

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
