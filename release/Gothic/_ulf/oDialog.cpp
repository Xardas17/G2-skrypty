/******************************************************************************** 
 
     $Workfile:: oDialog.cpp          $                $Date:: 24.04.01 17:33   $
     $Revision:: 38                   $             $Modtime:: 19.04.01 13:06   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oDialog.cpp $
 * 
 * 38    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 36    14.03.01 18:01 Wohlers
 * 
 * 35    13.02.01 11:26 Speckels
 * 
 * 34    12.01.01 12:38 Moos
 * 
 * 33    11.12.00 20:36 Wohlers
 * 
 * 32    27.10.00 16:35 Wohlers
 * 
 * 31    26.10.00 18:29 Wohlers
 * 
 * 30    26.10.00 18:11 Wohlers
 * 
 * 29    26.10.00 17:33 Wohlers
 * 
 * 28    26.09.00 22:31 Keskenti
 * 
 * 27    24/09/00 22:51 Luesebrink
 * 
 * 26    20.09.00 20:07 Rueve
 * 
 * 25    12.09.00 14:47 Wohlers
 * 
 * 24    11.09.00 17:05 Wohlers
 * 
 * 23    8.09.00 1:10 Keskenti
 * 
 * 22    1.09.00 17:34 Keskenti
 * 
 * 21    29.08.00 12:39 Wohlers
 * 
 * 20    16.08.00 15:10 Wohlers
 * 
 * 19    15.08.00 14:48 Wohlers
 * 
 * 18    11.08.00 15:42 Wohlers
 * 
 * 17    11.08.00 13:42 Keskenti
 * 
 * 17   11.08.00 13:41 Keskenti
 * Fix fuer AI_Ask und AI_WaitForQuestion
 * 
 * 16    9.08.00 16:25 Wohlers
 * 
 * 15    2.08.00 14:25 Wohlers
 * 
 * 14    28.07.00 17:03 Keskenti
 * 
 * 13    28.07.00 16:54 Wohlers
 * 
 * 12    27.07.00 22:46 Keskenti
 * 
 * 11    27.07.00 22:46 Wohlers
 * 
 * 10    27.07.00 22:19 Wohlers
 * 
 * 9     27.07.00 16:09 Wohlers
 * 
 * 8     21.07.00 15:34 Wohlers
 * 
 * 7     21.07.00 14:43 Wohlers
 * 
 * 6     19.07.00 20:05 Wohlers
 * 
 * 5     7.07.00 12:41 Wohlers
 * Gothic 0.87
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 5     11.05.00 12:48 Wohlers
 * 
 * 4     8.05.00 23:07 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:09 Wohlers
 * 
 * 13    18.04.00 20:14 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 12    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 11    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 10    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 9     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 8     20.12.99 17:44 Wohlers
 * uSrc V0.70
 * AI_UseItem / AniComb TakeItem etc...
 * 
 * 7     7.12.99 22:08 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 6     6.12.99 19:13 Wohlers
 * Dialog-Bug gefixed
 * 
 * 5     6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 4     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include <io.h>

#include "zCore.h"

#include "zInput_Win32.h"
#include "zModel.h"
#include "zview.h"
#include "zParser.h"
#include "zOption.h"
#include "zAICamera.h"
#include "zEventMan.h"
#include "zGrafix.h"

#include "oDialog.h"
#include "oMission.h"
#include "oNPC.h"
#include "oInfo.h"
#include "oItem.h"
#include "oWorld.h"
#include "oText.h"
#include "oGame.h"
#include "oNpcMessages.h"
#include "oItemReact.h"


extern zBOOL g_bDontKillOUSound;

// **********************************
// Happy Ask Box
// **********************************
zCOLOR COLOR_YES	(255,255,0,255);
zCOLOR COLOR_NO		(192,192,192,255);

// **********************************
// Ask Box
// **********************************

oCItem* offer = NULL;

const zREAL ASKBOX_SIZEX = 3.0f;
const zREAL ASKBOX_SIZEY = 3.0f;

oCAskBox :: oCAskBox()
{
	npc1	= NULL;
	npc2	= NULL;
	askvob	= NULL;
	fadeout	= FALSE;
	alpha	= 0;
	answer  = 0;

	for (int i=0; i<3; i++) thumb[i] = NULL;
}

oCAskBox :: ~oCAskBox()
{
	npc1	= NULL;
	npc2	= NULL;
	zRELEASE(askvob);
	for		(int i=0; i<3; i++) thumb[i]	= NULL;
}

void oCAskBox :: Init (oCNpc* ask, oCNpc* answer)
{
	npc1	= answer;
	npc2	= ask;
	askvob	= zNEW( zCVob );
	askvob -> SetDontWriteIntoArchive(TRUE);
	askvob -> SetCollDet		(FALSE);
	askvob -> SetPhysicsEnabled (FALSE);
	askvob -> SetVisualCamAlign	(zVISUAL_CAMALIGN_FULL);
	askvob -> SetSleeping		(FALSE);
	askvob -> SetAICallback		(this);
	fadeout = FALSE;
	alpha	= 0;
	SetNeutral();

	// Place into world
	if (!askvob->GetHomeWorld()) npc1->GetHomeWorld()->AddVob(askvob);
	SetPosition();
}

void oCAskBox :: Delete ()
{
	fadeout = TRUE;
}

void oCAskBox :: DoAI	(zCVob* inVob, zBOOL& vobDeleted)
{
	SetPosition();

	if (!fadeout) {

		if (alpha<255) {
			alpha+=20;
			if (alpha>255) alpha=255;
			zCDecal *masterDecal = (zCDecal *)askvob->GetVisual	();	
			masterDecal->decalMaterial->SetAlpha	(alpha);	
		}
	} else {
		// FadeOut
		if (alpha>0) alpha-=20;
		if (alpha<0) alpha = 0;
		zCDecal *masterDecal = (zCDecal *)askvob->GetVisual	();	
		masterDecal->decalMaterial->SetAlpha	(alpha);	
		if (alpha==0) {
			askvob -> SetAICallback(NULL);
			vobDeleted	= TRUE;
			askvob		= NULL;
			this->Release();
		}
	}
}

void oCAskBox :: SetNeutral()
{
	if (answer==2) return; 
	askvob -> SetVisual("Ask_Neutral.tga");
	zCDecal *masterDecal = (zCDecal *)askvob->GetVisual	();
	masterDecal->decalMaterial->SetAlphaBlendFunc		(zRND_ALPHA_FUNC_ADD);
	masterDecal->decalMaterial->SetMatGroup				(zMAT_GROUP_WATER);
	masterDecal->decalMaterial->SetAlpha					(alpha);	
	masterDecal->SetDecalDim(ASKBOX_SIZEX,ASKBOX_SIZEY);
	answer = 2;
}

void oCAskBox :: SetYes()
{
	if (answer==1) return;
	askvob -> SetVisual("Ask_Yes.tga");
	zCDecal *masterDecal = (zCDecal *)askvob->GetVisual	();
	masterDecal->decalMaterial->SetAlphaBlendFunc		(zRND_ALPHA_FUNC_ADD);
	masterDecal->decalMaterial->SetMatGroup				(zMAT_GROUP_WATER);
	masterDecal->decalMaterial->SetAlpha					(alpha);	
	masterDecal->SetDecalDim(ASKBOX_SIZEX,ASKBOX_SIZEY);
	answer = 1;	
}

void oCAskBox :: SetNo()
{
	if (answer==0) return;
	askvob -> SetVisual("Ask_No.tga");
	zCDecal *masterDecal = (zCDecal *)askvob->GetVisual	();
	masterDecal->decalMaterial->SetAlphaBlendFunc		(zRND_ALPHA_FUNC_ADD);
	masterDecal->decalMaterial->SetMatGroup				(zMAT_GROUP_WATER);
	masterDecal->decalMaterial->SetAlpha					(alpha);	
	masterDecal->SetDecalDim(ASKBOX_SIZEX,ASKBOX_SIZEY);
	answer = 0;
}

void oCAskBox :: SetPosition()
{
	if (!askvob) return;
/*	zCModelNodeInst *playerHead	= npc1->GetModel()->SearchNode(zMDL_NODE_NAME_HEAD);
	zCModelNodeInst *npcHead	= npc2->GetModel()->SearchNode(zMDL_NODE_NAME_HEAD);

	zMATRIX4	trafoHandToWorld;
	zVEC3		pos1,pos2;
	pos1 = (npc1->trafoObjToWorld * npc1->GetModel()->GetTrafoNodeToModel(playerHead)).GetTranslation();
	pos2 = (npc2->trafoObjToWorld * npc2->GetModel()->GetTrafoNodeToModel(npcHead)).GetTranslation();
	pos1 = (pos1+pos2)*0.5;
	pos1[VY] -= 20;*/

	zCCamera* cam	= ogame	-> GetCamera		();
	zCVob* camVob	= ogame	-> GetCameraVob		();
	zVEC3 dir		= camVob-> GetAtVectorWorld	();
	zVEC3 pos;
	pos[VZ]  = 10;
	cam		-> BackProject		(zrenderer->vid_xdim/2,zrenderer->vid_ydim - zrenderer->vid_ydim/5,pos);
	pos		 = camVob->trafoObjToWorld * pos;	// p im worldSpace  
	askvob	-> SetPositionWorld	(pos);

//	zVEC3 pos		= camVob->GetPositionWorld();
//	zVEC3 dir		= camVob->GetAtVectorWorld();
//	askvob -> SetPositionWorld(pos + dir * 10);
}

// ***************************************************************************************
// ****************************** BRANDNEU - BRANDHEISS **********************************
// ************************************** MASTERAI ***************************************
// ***************************************************************************************
// ***************************************************************************************

// ***************************************************************************************
// Dialogbezogene Funktionen des NSCs
// ***************************************************************************************
/*
zBOOL oCNpc :: EV_WaitForPcQuestion (oCMsgConversation* csg)
// IMPORTANT : Darf nicht Netzwerkrelevant sein.
{
	if (ogame->GetSelfPlayerVob()->GetFocusVob()==this) {
		if (zinput->Toggled(GAME_UP) && zinput->Pressed(GAME_ACTION)) {
			
			parser.CallFunc(csg->f_yes);
			return TRUE;
		} 
	}
	csg->timer -= ztimer.GetFrameTimeF();
	if (csg->timer<=0) {
		parser.CallFunc(csg->number);	
		return TRUE;
	}
	return FALSE;
}
*/
/*
zBOOL oCNpc :: WaitsForAnswer(zBOOL answerYes, oCNpc* other)
{
	oCMsgConversation* msg = dynamic_cast<oCMsgConversation*>(GetEM()->GetActiveMessage());
	if (msg) {
		
		// Falls other InMovement, diesen Ausschalten
		zBOOL inMove = other->GetInMovement();
		if (inMove) other->EndMovement();

		if (msg->GetSubType() == oCMsgConversation::EV_ASK) {		
			// msg kann hier aus den Skripten gelöscht werden (zB.ClearAIQueue),
			// darum wird hier zusaetzliche Referenz drauf behalten
			msg->AddRef();
			if (answerYes) {
				ogame->GetChoiceBox()->SetAnswerYes();
				// if (askbox) askbox->SetYes();
				parser.CallFunc(msg->f_yes);
			} else {
				ogame->GetChoiceBox()->SetAnswerNo();
				// if (askbox) askbox->SetNo();
				parser.CallFunc(msg->f_no);
			}
			if (askbox) askbox -> Delete();
			askbox  = NULL;		
			msg	   -> Delete();
			zRELEASE(msg);
			state.SetStateTime(0);		// StateLoop Counter wieder auf "0" -> weil sonst zeitabhaengige Reaktionen sofort gestartet werden,

			if (inMove) other->BeginMovement();
			return TRUE;
		
		} else if (answerYes && (msg->GetSubType() == oCMsgConversation::EV_WAITFORQUESTION)) {
			
			// msg kann hier aus den Skripten gelöscht werden (zB.ClearAIQueue),
			// darum wird hier zusaetzliche Referenz drauf behalten
			msg->AddRef();
			parser.CallFunc		(msg->f_yes);
			state.SetStateTime	(0);	// StateLoop Counter wieder auf "0" -> weil sonst zeitabhaengige Reaktionen sofort gestartet werden,
			msg	-> Delete();
			zRELEASE(msg);
			if (inMove) other->BeginMovement();
			return TRUE;

		}
		if (inMove) other->BeginMovement();
	}
	return FALSE;
}
*/
zBOOL oCNpc :: IsWaitingForAnswer()
{
	oCMsgConversation* msg = dynamic_cast<oCMsgConversation*>(GetEM()->GetActiveMessage());
	if (msg) {
		if (msg->GetSubType() == oCMsgConversation::EV_ASK)				return TRUE;
		if (msg->GetSubType() == oCMsgConversation::EV_WAITFORQUESTION) return TRUE;
	}
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	zBOOL oCNpc :: SetCurrentAnswer(int status, zBOOL selectStatus, oCNpc* other)

	24.09.2000	[dennis]	

				antwort auswaehlen ohne die strg taste loszulassen

   ---------------------------------------------------------------------- */
zBOOL oCNpc :: SetCurrentAnswer(int status, zBOOL selectStatus, oCNpc* other)
// this		= NPC
// other	= Spieler
{
	static int		oldStatus		= -2;
	static zBOOL	oldSelectStatus	= FALSE;

	zCView* view = ogame->GetView(oCGame::oEGameDialogView::GAME_VIEW_CHOICE);
	zERR_ASSERT	(view);

	// Select Status ermitteln
	zBOOL selected	= (oldSelectStatus && !selectStatus);	// Wechsel von 1 nach 0 -> losgelassen.
	oldSelectStatus = selectStatus;

	oCMsgConversation* msg = dynamic_cast<oCMsgConversation*>(GetEM()->GetActiveMessage());
	if (msg) {
		
		if (msg->GetSubType() == oCMsgConversation::EV_ASK) {	
				
			if (!selected) {
				if (zinput->GetToggled(GAME_ACTION)) {
					view->Open();
					view->DialogSelection	(msg->text,msg->name, (status > 0) ? COLOR_YES : COLOR_NO , (status < 0) ? COLOR_YES : COLOR_NO, -2.0f );
				} else if (!zinput->GetState(GAME_ACTION)) {
					view->Close();
					return FALSE;
				}
			}

			if (status!=oldStatus) {
				// View-Update
				view->DialogSelection	(msg->text,msg->name, (status > 0) ? COLOR_YES : COLOR_NO , (status < 0) ? COLOR_YES : COLOR_NO, -2.0f);
				oldStatus = status;
			}

			//changed[dennis]
			if (msg->IsInUse() && ( (status==1) || (status==-1) ) ) {

				// Falls other InMovement, diesen Ausschalten
				zBOOL inMove = other->GetInMovement();
				if (inMove) other->EndMovement();
				// msg kann hier aus den Skripten gelöscht werden (zB.ClearAIQueue),
				// darum wird hier zusaetzliche Referenz drauf behalten
				msg->AddRef();

				//
				//	CODECHANGE [ROMAN]
				//
				parser.SetInstance( "SELF" , this );
				parser.SetInstance( "OTHER", other );
				//
				//	CODECHANGE [ROMAN] END
				//

				// Auswahl ausführen
				state.CloseCutscenes();
				if (status > 0) {
					parser.CallFunc(msg->f_yes);	
				} else if (status < 0) {
					parser.CallFunc(msg->f_no);
				}

				state.SetStateTime(0);		// StateLoop Counter wieder auf "0" -> weil sonst zeitabhaengige Reaktionen sofort gestartet werden,
				
				view->Close();

				msg->Delete();
				zRELEASE(msg);

				oldStatus		= -2;
				oldSelectStatus = FALSE;
				if (inMove) other->BeginMovement();
			}

			return TRUE;
		
		} else if (msg->GetSubType() == oCMsgConversation::EV_WAITFORQUESTION) {
			
			if (status>0) {
				// Falls other InMovement, diesen Ausschalten
				zBOOL inMove =	other->GetInMovement();
				if (inMove)		other->EndMovement	();
				// msg kann hier aus den Skripten gelöscht werden (zB.ClearAIQueue),
				// darum wird hier zusaetzliche Referenz drauf behalten
				msg->AddRef			();
				
				//
				//	CODECHANGE [ROMAN]
				//
				parser.SetInstance( "SELF" , this  );
				parser.SetInstance( "OTHER", other );
				//
				//	CODECHANGE [ROMAN] END
				//

				state.CloseCutscenes();
				parser.CallFunc		(msg->f_yes);
				state.SetStateTime	(0);	// StateLoop Counter wieder auf "0" -> weil sonst zeitabhaengige Reaktionen sofort gestartet werden,
				msg	-> Delete		();
				zRELEASE			(msg);
				if (inMove) other->BeginMovement();
				
				oldStatus		= -2;
				oldSelectStatus = FALSE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

zBOOL oCNpc :: EV_Ask (oCMsgConversation* csg)
// Der NSC stellt Spieler eine Frage - und wartet auf die Antwort
// IMPORTANT : Darf nicht Netzwerkrelevant sein.
{	
	static int status = -2;
	
	oCNpc* selfPlayer = ogame->GetSelfPlayerVob();
	if ((selfPlayer->GetFocusNpc()==this) && oCNpc::IsInPerceptionRange(NPC_PERC_ASSESSTALK,this,selfPlayer)) {
		
		// nix machen, warten....
		csg->SetInUse(TRUE);

		// View nicht aufmachen, passiert erst bei gedrückter ACTION in SetCurrentAnswer
/*		if (!csg->IsInUse()) {
			zCView* view = ogame->GetView(oCGame::oEGameDialogView::VIEW_DIALOG_CHOICE);
			zERR_ASSERT	(view);
			view->DialogSelection	(csg->text,csg->name, (status > 0) ? COLOR_YES : COLOR_NO , (status < 0) ? COLOR_YES : COLOR_NO ,-2.0f);
			csg->SetInUse(TRUE);
		};*/
		
	} else if (csg->IsInUse() && !zinput->GetState(GAME_ACTION)) {

		zCView* view = ogame->GetView(oCGame::oEGameDialogView::GAME_VIEW_CHOICE);
		zERR_ASSERT	(view);
		view->Close	();
		return TRUE;
		
	}		
	return FALSE;
};
		
/*	
		if (zinput->GetState(GAME_ACTION)) {

			// Do the shitty View
			int oldStatus = status;
			status = 0;
			if (zinput->GetState(GAME_UP))		status = 1;		else
			if (zinput->GetState(GAME_DOWN))	status = -1;	
			
			if (oldStatus!=status) {
				view->DialogSelection	(csg->text,csg->name, (status > 0) ? COLOR_YES : COLOR_NO , (status < 0) ? COLOR_YES : COLOR_NO ,-2.0f);
				csg->SetInUse			(TRUE);
			}

		} else {
			
			// Close the shitty View
			status = -2;
			if (csg->IsInUse()) {
				view->Close();
				// Und Answer raushauen.
					
			
			}
		}

				
		
		
		// Askbox an !
		if (!askbox) {
			askbox  = new oCAskBox();
			askbox -> Init(ogame->GetSelfPlayerVob(),this);
		}		
		askbox->SetNeutral();

	} else if (askbox) {
		// AskBox aus
		askbox -> Delete();
		askbox  = NULL;
	}

	csg->timer -= ztimer.GetFrameTimeF();
	if (csg->timer<=0) {
		if (askbox) {
			askbox -> Delete();
			askbox  = NULL;
		}
		parser.SetInstance	("SELF;",this);
		parser.CallFunc		(zSTRING("B_NPCBye"));	
		return TRUE;
	}
	return FALSE;
}
/*
zBOOL oCNpc :: EV_Ask (oCMsgConversation* csg)
// Der NSC stellt Spieler eine Frage - und wartet auf die Antwort
// IMPORTANT : Darf nicht Netzwerkrelevant sein.
{	
	oCNpc* selfPlayer = ogame->GetSelfPlayerVob();
	if ((selfPlayer->GetFocusNpc()==this) && oCNpc::IsInPerceptionRange(NPC_PERC_ASSESSTALK,this,selfPlayer)) {
		// Askbox an !
		if (!askbox) {
			askbox  = new oCAskBox();
			askbox -> Init(ogame->GetSelfPlayerVob(),this);
		}		
		askbox->SetNeutral();

	} else if (askbox) {
		// AskBox aus
		askbox -> Delete();
		askbox  = NULL;
	}

	csg->timer -= ztimer.GetFrameTimeF();
	if (csg->timer<=0) {
		if (askbox) {
			askbox -> Delete();
			askbox  = NULL;
		}
		parser.SetInstance	("SELF;",this);
		parser.CallFunc		(zSTRING("B_NPCBye"));	
		return TRUE;
	}
	return FALSE;
}
*/
zBOOL oCNpc :: EV_WaitForQuestion (oCMsgConversation* csg)
// IMPORTANT : Darf nicht Netzwerkrelevant sein.
{	
	csg->timer -= ztimer.GetFrameTimeF();
	if (csg->timer<=0) {
		parser.SetInstance	("SELF",this);
		parser.CallFunc		(zSTRING("B_NPCBye"));	
		return TRUE;
	}
	return FALSE;
}

// ***********************************************************************************
// Dialog - Methoden.
// ***********************************************************************************

zBOOL oCNpc :: CanTalk ()
{
	return (canTalk<=0.0f);
};

void oCNpc :: SetCanTalk(int timeSec)
{
	canTalk = (zREAL)(timeSec) * 1000;
}

void oCNpc :: SetTalkingWith(oCNpc* other, zBOOL talking)
// Dieser Typ spricht gerade mit "this" (talking = TRUE)
// ansonsten Gespräch beendet
{
	if (!other)	{
		talkOther = NULL;
		return;
	}
	if (talking)			talkOther = other;		else 
	if (talkOther == other)	talkOther = NULL;
}

oCNpc* oCNpc :: GetTalkingWith()
// Dieser Typ spricht gerade mit "this" (talking = TRUE)
// ansonsten Gespräch beendet
{
	return talkOther;
}

void oCNpc :: StartTalkingWith(oCNpc* other)
{
	if (!other) return;

	SetTalkingWith			(other,TRUE);
	other->SetTalkingWith	(this ,TRUE);	
}

void oCNpc :: StopTalkingWith()
{
	if (talkOther) talkOther->SetTalkingWith (NULL,FALSE);	
	SetTalkingWith (NULL,FALSE);
}

zCEventMessage* oCNpc :: GetTalkingWithMessage(oCNpc* other)
// Hat NSC eine Msg mit NSC "other" als Ziel ?
// dann diese Msg liefern.
{
	int nr = GetEM()->GetNumMessages();
	zCEventMessage*		watch	= NULL;
	oCMsgConversation*	convMsg = NULL;
	zBOOL hasTalkMsg			= FALSE;
	for (int i=nr-1; i>=0; i--) {
		// Letzte Message merken, die kein Overlay ist.
		if (!watch) {
			watch = GetEM()->GetEventMessage(i);
			if (watch->IsOverlay()) watch = NULL;
		}		
		// Nach entsprechender TalkMessage suchen.
		convMsg = dynamic_cast<oCMsgConversation*>(GetEM()->GetEventMessage(i));
		if (convMsg) {
			if ((convMsg->GetSubType()==oCMsgConversation::EV_OUTPUT) || (convMsg->GetSubType()==oCMsgConversation::EV_OUTPUTSVM)) {
				if (convMsg->target==other) {
					hasTalkMsg = TRUE;
					if (watch) break;
				}
			}
		}
	}	
	if (hasTalkMsg) return watch;
	else			return NULL;
}

zBOOL oCNpc :: CanBeTalkedTo()
// Wenn ich einen NSC anlabere, soll alles Ambient-Gefasel (kann Amb-CS oder ZS_Smalltalk sein), 
// was er von sich gibt, beendet werden, und der ZS_Talk (bzw. B_RefuseTalk) geht los.
// TRUE : NSC kann angesprochen werden (CSs / OUs wurden gestoppt)
{
	if (IsWaitingForAnswer()) return TRUE;

	// Bereits im ZS_Talk, dann nichts machen
	if (state.IsInState(parser.GetIndex("ZS_TALK"))) {
		return GetEM()->IsEmpty(TRUE) && !GetEM()->GetCutsceneMode();
	}

	// Nicht im ZS_Talk -> OU oder CS abbrechen.
	zCCSCutsceneContext* context = dynamic_cast<zCCSCutsceneContext*>(GetEM()->GetCutscene());
	if (context) {
		if (context->IsCutscene() && !context->IsGlobalCutscene()) {
			// Ambient-Cutscene
			StopRunningOU();		// Safety, falls da gerade was laeuft....
			context->Stop();
		} else {
			StopRunningOU();
		}
	}
	return TRUE;
}

void oCNpc :: StopRunningOU()
// Beende laufende OU.
{
	// OU raussuchen und Sound stoppen....
	if (g_bDontKillOUSound) return;

	oCMsgConversation* msg = NULL;
	for (int i=0; i < GetEM()->GetNumMessages(); i++) {
		msg = dynamic_cast<oCMsgConversation*>(GetEM()->GetEventMessage(i));
		if (msg && msg->GetCutsceneMode() && (msg->GetSubType()==oCMsgConversation::EV_PLAYANISOUND)) {
			// Dies ist die OU, die gestoppt werden soll....
			zsound->StopSound((zTSoundHandle)msg->handle);
			msg->Delete();
			// evt. offene Views schliessen
			zCView* view = ogame->GetView(oCGame::oEGameDialogView::GAME_VIEW_NOISE);
			if (view) view->Close();
			view = ogame->GetView(oCGame::oEGameDialogView::GAME_VIEW_CONVERSATION);
			if (view) view->Close();
			view = ogame->GetView(oCGame::oEGameDialogView::GAME_VIEW_CINEMA);
			if (view) view->Close();
			// TEMP : Patch 1.08 : Test : CS-Modus auch beenden
			GetEM()->SetCutscene(NULL);
		}
	}	
	// Patch 1.07 : [Wohlers] : Dialoggesten auch beenden.
	zCModel* model = GetModel();
	if (model) {
		for (int i=0; i<model->numActiveAnis; i++) {
			zCModelAniActive* ani = GetModel()->aniChannels[i];
			if (ani && ani->GetAni() && (ani->GetAni()->GetAniName().Search("DIALOGGESTURE_")>=0)) {
				// Stop Ani
				model->FadeOutAni(ani->GetAni());
			}
		}
		StopFaceAni(NPC_TALK_ANI);
	}
}

// ***********************************************************************************
// Item-React-Module checking / Darstellung etc.
// ***********************************************************************************

zBOOL oCNpc :: AssessGivenItem (oCItem* item, oCNpc* other)
{	
	int func = GetPerceptionFunc (NPC_PERC_ASSESSGIVENITEM);
	if (func<0) return FALSE;

	if (item) item->AddRef();
	// Missionsitem ?
	{
		if (item && item->HasFlag(ITM_FLAG_MI)) {
			// a) Item Lösungsbedingung für einen Auftrag
			oCMission* mission = misMan.GetAvailableMission(this,other,FALSE);
			if (mission) {

				zBOOL success	= mission->SuccessConditions();
				
				if (success) {				
					// Austausch durchführen
					ExchangeTradeModules		(other);
					// Success - Methode aktivieren.
					parser.SetInstance			("ITEM",item);
					mission -> Success			();
					item->Release();
					return TRUE;
				}
			}
		}
	}
	// b) SkriptMethode ZS_AssessGivenItem ausführen
	AssessGivenItem_S (other,item);
	if (item) item->Release();
	return TRUE;
}

oCNpc* oCNpc :: GetTradeNpc(void)
{
	return tradeNpc;
}
void oCNpc :: SetTradeNpc(oCNpc* tradingWithNpc)
{
	tradeNpc = tradingWithNpc;
}

oCItem* oCNpc :: GetTradeItem()
{
	if (trader) {
		zCListSort <oCItem>* node = trader->GetContents()->GetNextInList();
		if (node) return node->GetData();
	}
	return NULL;
}

void oCNpc :: OpenTradeContainer(oCItem* item, oCNpc* tradingWithNpc, int amount)
{
	if (!item) return;
	if (!trader) {
		// Init Container
		trader  = zNEW( oCItemContainer() );
	}
	if (!trader->IsOpen()) {
		if (IsSelfPlayer())
		{
			trader -> SetName		(tradingWithNpc->GetName());
			trader -> OpenPassive	(4096, 0, INV_MODE_BUY);
		}
		else
		{
			trader -> SetName		(tradingWithNpc->GetName());
			// int x,y;
			// trader -> GetSize		(x, y);
			// x = ::screen->anx(x);
			trader -> OpenPassive	(0, 0, INV_MODE_SELL);
		}
	}

	SetTradeNpc(tradingWithNpc);
	oCItem* transferItem		= RemoveFromInv(item->GetInstance(), amount );
	oCItem* oldItem				= NULL;
	zCListSort<oCItem>* node	= trader->GetContents()->GetNextInList();
	while (node) {
		oldItem = node->GetData();
		node	= node->GetNextInList();
		if (oldItem && oldItem->MultiSlot() && (oldItem->GetInstance()==transferItem->GetInstance())) {
			oldItem			-> SetAmount( oldItem->GetAmount()+1 );
			transferItem	-> SetAmount( transferItem->GetAmount()-1 );
			if (transferItem-> GetAmount()<=0) {
				// Remove and delete it
				ogame->GetGameWorld()->RemoveVob(transferItem);
				transferItem = NULL;
			}
			break;

		} else {
			trader->Remove	(oldItem);
			PutInInv		(oldItem);
			break;
		}
	}

	if (transferItem) trader->Insert	(transferItem);
}

void oCNpc :: CloseTradeContainer()
{
	// Los Trados aussos
	if (trader) {
		// Back to inventory
		oCItem*	item = GetTradeItem();
		if (item) {
			trader->Remove(item);
			PutInInv(item);
		}
		trader->Close();
	}
	if (tradeNpc && ogame->GetGameWorld()->GetVobListNpcs()->IsInList(tradeNpc)) {
		tradeNpc->SetTradeNpc(NULL);
		tradeNpc->CloseTradeContainer();
	}
	tradeNpc = NULL;
	offer	 = NULL;
}

void oCNpc :: OpenTradeOffer (oCNpc* player)
// this		= npc
// player	= player
{
	oCItem* item = player->GetTradeItem();
	if (!item) return;

	// Containerinhalt verwerfen
	if (trader) {
		oCItem* oldItem = GetTradeItem();
		if (oldItem) {
			trader->Remove(oldItem);
			PutInInv(oldItem);
		}
	}

	oCItemReactModule* module = ogame->GetTradeManager()->GetModule(player,this,item);
	if (module) {
		// passendes Modul gefunden....
		// a) Gegenstand erzeugen, sofern nicht im Inventory vorhanden.
		//oCItem* offer = NULL;
		int instance, amount;
		module->GetOfferedInstance	(instance,amount);

		//
		//	CODECHANGE [ROMAN]
		//
		if ( !offer )
        {
            offer = IsInInv(instance,amount);
    		if (!offer) {
	    		offer = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,instance);
    			offer -> SetAmount(amount);
			    PutInInv (offer);
		    }
        }
		//
		//	CODECHANGE [ROMAN] END
		//
		OpenTradeContainer(offer,player, this->IsAPlayer() ? 1 : amount);
	}
}

zBOOL oCNpc :: CheckItemReactModule (oCNpc* npc, oCItem* item)
// this		= Player
// other	= NSC
{
	zBOOL success = FALSE;
	oCItemReactModule* module = ogame->GetTradeManager()->GetModule(this,npc,item);
	if (module) {
        success = module->StartReaction(item->GetAmount());
		if (success) {
			ExchangeTradeModules(npc);
		};
	}
	// and now closen, which implies : Back to inventory !
	npc -> CloseTradeContainer();
	CloseTradeContainer();
	return (module!=NULL);
};

void oCNpc :: ExchangeTradeModules(oCNpc* npc)
{
	// ....Do Exchange....
	// Just exchange the Pointers ?
	oCItemContainer* traderNpc = npc->trader;			
	npc -> trader	= trader;
	trader			= traderNpc;

	// Anis starten
	if (GetBodyState()		==BS_STAND)		GetModel()		-> StartAni("T_TRADEITEM");
	if (npc->GetBodyState	()==BS_STAND)	npc->GetModel()	-> StartAni("T_TRADEITEM");

	// and now closen, which implies : Back to inventory !
	npc -> CloseTradeContainer();
	CloseTradeContainer			();
}
