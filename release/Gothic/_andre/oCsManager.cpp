#include "zcore.h"
#include "zccscontext.h"
#include "zcscamera.h"
#include "zvobmisc.h"
#include "zCCSProps.h"

#include "ocsmanager.h"
#include "ocsplayer.h"
#include "ocsprops.h"
#include "onpcmessages.h"

zCLASS_DEFINITION ( oCCSManager,zCCSManager, 0 ,0)

const zSTRING zMENU_SEPARATOR = "SEPARATOR";




///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Cutscene-Manager
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////




oCCSManager::oCCSManager()
{
	// *** ACHTUNG: Maximal 24mal AddCommand(...) einfuegen !!! ***

	zSTRING sepString = zMENU_SEPARATOR;

	// Core & FX
	zCEventMessage* msg=zNEW(zCEventCore(zCEventCore::zEVENT_TRIGGER,0));
	AddCommand(msg->MD_GetSubTypeString(zCEventCore::zEVENT_TRIGGER));

	AddCommand(sepString); // SEPARATOR

	// Movement
	zRELEASE(msg);msg=zNEW(oCMsgMovement(oCMsgMovement::EV_ROBUSTTRACE,0));
	AddCommand(msg->MD_GetSubTypeString(oCMsgMovement::EV_GOTOVOB));
	AddCommand(msg->MD_GetSubTypeString(oCMsgMovement::EV_GOROUTE));
	AddCommand(msg->MD_GetSubTypeString(oCMsgMovement::EV_GOTOFP));
	AddCommand(msg->MD_GetSubTypeString(oCMsgMovement::EV_TURNTOVOB));	
	AddCommand(msg->MD_GetSubTypeString(oCMsgMovement::EV_SETWALKMODE));

	AddCommand(sepString); // SEPARATOR

	// Conversation
	zRELEASE(msg); msg=zNEW(oCMsgConversation(oCMsgConversation::EV_PLAYANISOUND,zSTRING(),zSTRING()));
	AddCommand(msg->MD_GetSubTypeString(oCMsgConversation::EV_PLAYANISOUND));
	AddCommand(msg->MD_GetSubTypeString(oCMsgConversation::EV_PLAYANI));
	AddCommand(msg->MD_GetSubTypeString(oCMsgConversation::EV_PLAYSOUND));
	AddCommand(msg->MD_GetSubTypeString(oCMsgConversation::EV_LOOKAT));

	AddCommand(sepString);  // SEPARATOR
	
	// Manipulation
	zRELEASE(msg); msg = zNEW(oCMsgManipulate(oCMsgManipulate::EV_USEMOB,0));
	AddCommand(msg->MD_GetSubTypeString(oCMsgManipulate::EV_USEMOB));
	AddCommand(msg->MD_GetSubTypeString(oCMsgManipulate::EV_USEITEM));

	AddCommand(sepString); // SEPARATOR
	
	// ScreenFX
	zRELEASE(msg); msg = zNEW(zCEventScreenFX(zCEventScreenFX::zEVENT_BLEND_FADEIN,0,0,0));
	AddCommand(msg->MD_GetSubTypeString(zCEventScreenFX::zEVENT_BLEND_FADEIN));
	AddCommand(msg->MD_GetSubTypeString(zCEventScreenFX::zEVENT_BLEND_FADEOUT));

	AddCommand(sepString); // SEPARATOR

	// Camera-Init
	zRELEASE(msg); msg = zNEW(zCCSCamera_EventMsgActivate());
	AddCommand(msg->MD_GetSubTypeString(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE));
	AddCommand(msg->MD_GetSubTypeString(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE));
	
	AddCommand(sepString);  // SEPARATOR

	// Camera-Play
	zRELEASE(msg); msg = zNEW(zCCSCamera_EventMsg());
	AddCommand(msg->MD_GetSubTypeString(zCCSCamera_EventMsg::EV_PLAY));
	AddCommand(msg->MD_GetSubTypeString(zCCSCamera_EventMsg::EV_STOP));	
	zRELEASE(msg);
};

oCCSManager::~oCCSManager()
{
};

zCCSPlayer*	oCCSManager::CreateCutscenePlayer(zCWorld* ownerWorld)
{
	zCCSPlayer* player = zNEW( oCCSPlayer() );
	player->SetOwnerWorld	(ownerWorld);
	InsertPlayerInList		(player);	
	return player;
};

zCEventMessage* oCCSManager::CreateOuMessage()
{
	return CreateMessage(8); // PLAYANISOUND
};

zCEventMessage* oCCSManager::CreateMessage(int z)
{
	// *** ACHTUNG: Maximal bis Nr 23 !!! ***

	switch (z)
	{
	// Core:
	case 0: return zNEW(zCEventCore(zCEventCore::zTEventCoreSubType(zCEventCore::zEVENT_TRIGGER)));
	// Movement
	case 2: return zNEW(oCMsgMovement(oCMsgMovement::EV_GOTOVOB,0));
	case 3: return zNEW(oCMsgMovement(oCMsgMovement::EV_GOROUTE,0));
	case 4: return zNEW(oCMsgMovement(oCMsgMovement::EV_GOTOFP,0));
	case 5: return zNEW(oCMsgMovement(oCMsgMovement::EV_TURNTOVOB,0));	
	case 6: return zNEW(oCMsgMovement(oCMsgMovement::EV_SETWALKMODE,0));
	// Conversation
	case 8:	return zNEW(oCMsgConversation(oCMsgConversation::TConversationSubType(oCMsgConversation::EV_PLAYANISOUND)));
	case 9:	return zNEW(oCMsgConversation(oCMsgConversation::TConversationSubType(oCMsgConversation::EV_PLAYANI)));
	case 10:return zNEW(oCMsgConversation(oCMsgConversation::TConversationSubType(oCMsgConversation::EV_PLAYSOUND)));
	case 11:return zNEW(oCMsgConversation(oCMsgConversation::TConversationSubType(oCMsgConversation::EV_LOOKAT)));
	// Manipulation
	case 13:return zNEW(oCMsgManipulate(oCMsgManipulate::EV_USEMOB));	
	case 14:return zNEW(oCMsgManipulate(oCMsgManipulate::EV_USEITEM));		
	// ScreenFX
	case 16:return zNEW(zCEventScreenFX(zCEventScreenFX::zEVENT_BLEND_FADEIN,0,0,0));	
	case 17:return zNEW(zCEventScreenFX(zCEventScreenFX::zEVENT_BLEND_FADEOUT,0,0,0));			
	// Camera-Init
	case 19:return zNEW(zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE));	
	case 20:return zNEW(zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE));
	// Camera
	case 22:return zNEW(zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_PLAY));	
	case 23:return zNEW(zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_STOP));	

	// *** ACHTUNG: Maximal bis Nr 23 !!! ***
	default:	return NULL;
	}
}
zCCSProps* oCCSManager::CreateProperties()
{
	return zNEW(oCCSProps);
};

#ifdef COMPILING_SPACER

	zBOOL oCCSManager::Next(zSTRING & Token, zSTRING & Text)
	{
		zBOOL retVal = FALSE;
		while (!retVal) {
			retVal = zCCSManager::Next(Token,Text);
			if (!retVal) return retVal;

			retVal = FALSE;
			zCCSAtomicBlock* aBlock = dynamic_cast<zCCSAtomicBlock*>(iter);
			if (aBlock)
			{
				oCMsgConversation* msg = dynamic_cast<oCMsgConversation*>(aBlock->GetCommand());
				if (	msg &&
					(msg->GetSubType()==oCMsgConversation::EV_PLAYANISOUND || msg->GetSubType()==oCMsgConversation::EV_PLAYSOUND)
					)
				{
					Token = msg->name;
					Text = msg->text;
					retVal = TRUE;
				}    
			}
		}

		return TRUE;
	}
	zCCSBlockBase* oCCSManager::BlockLocalize(zCCSBlockBase* block, zSTRING & Text)
	{
		zCCSAtomicBlock* aBlock = dynamic_cast<zCCSAtomicBlock*>(block);
		if (aBlock)
		{
			oCMsgConversation* msg = dynamic_cast<oCMsgConversation*>(aBlock->GetCommand());
			if (	msg &&
					(msg->GetSubType()==oCMsgConversation::EV_PLAYANISOUND || msg->GetSubType()==oCMsgConversation::EV_PLAYSOUND)
					)
			{
				msg->text = Text;
			}  
			return block;
		} else return 0;
	}
	zBOOL oCCSManager::Localize(zSTRING & Token, zSTRING & Text)
	{
		if (!iteration) return zCCSManager::Localize(Token,Text);

		iterA = 0;
		iterB = 0;
		iter = 0;
		zSTRING searchToken;
		zSTRING txt;
		while (Next(searchToken,txt))
		{
			if (searchToken==Token)
			{
				BlockLocalize(iter,Text);
				return TRUE;
			}
		}
		return FALSE;
	}

#endif