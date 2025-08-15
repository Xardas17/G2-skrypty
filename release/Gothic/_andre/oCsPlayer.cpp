#include "zcore.h"
#include "zccsmanager.h"
#include "zvobmisc.h"

#include "oCSPlayer.h"
#include "ocsProps.h"
#include "onpcmessages.h"
#include "ogame.h"
#include "onpc.h"
#include "oworld.h"

zCLASS_DEFINITION ( oCCSPlayer,	zCCSPlayer, 0 ,0)

oCCSPlayer::oCCSPlayer() : zCCSPlayer()
{
	
}

oCCSPlayer::~oCCSPlayer()
{
};

/*zCCSProps* oCCSPlayer::CreateProperties()
{
	return zNEW(oCCSProps);
};
*/

void oCCSPlayer::ProcessCutscene(zCCSCutsceneContext* cs, const zPOINT3& pos)
{
	zCCSPlayer::ProcessCutscene(cs, pos);
	
	// Analyse der Cutscene nach dem Spielen

	switch (cs->lastPlayResult)
	{
		case zCCSCutsceneContext::CS_PLAY_STARTEDPLAYING:     
		{
			zERR_MESSAGE(7,0,"B: CS: Cutscene started playing");
			if (cs->IsGlobalCutscene()) dynamic_cast<oCWorld*>(GetOwnerWorld())->ClearNpcPerceptionVobLists();
		}	break;

		case zCCSCutsceneContext::CS_PLAY_STOPPED:     
		{
			zERR_MESSAGE(7,0,"B: CS: Cutscene stopped");
		}	break;			

		case zCCSCutsceneContext::CS_PLAY_INTERRUPTED: 
		{
			zERR_MESSAGE(7,0,"B: CS: Cutscene interrupted");
		}	break;

		case zCCSCutsceneContext::CS_PLAY_RESUMED:
		{
			zERR_MESSAGE(7,0,"B: CS: Cutscene resumed");
		}	break;		
	};									
};