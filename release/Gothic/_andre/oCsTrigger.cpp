
#include "zcore.h"
#include "zCCSPlayer.h"
#include "zCCSContext.h"
#include "zArchiver.h"
#include "zworld.h"


#include "oCSTrigger.h"

/////////////////////////////////////////////////


zCLASS_DEFINITION ( oCCSTrigger,	zCTrigger, 0 ,0)

void oCCSTrigger::TriggerTarget(zCVob* vobInstigator)
{	
	zERR_MESSAGE(8,0,"B: CS: CSTrigger/Trigger "+GetObjectName()+" by "+(vobInstigator?vobInstigator->GetObjectName():""));
	zSTRING name = GetTriggerTarget();
	if (GetHomeWorld() && GetHomeWorld()->GetCutscenePlayer())
		GetHomeWorld()->GetCutscenePlayer()->OnCSTrigger(name,vobInstigator);
};

void oCCSTrigger::UntriggerTarget(zCVob* vobInstigator)
{
	zERR_MESSAGE(8,0,"B: CS: CSTrigger/Untrigger "+GetObjectName()+" by "+(vobInstigator?vobInstigator->GetObjectName():""));
	zSTRING name = GetTriggerTarget();
	if (GetHomeWorld() && GetHomeWorld()->GetCutscenePlayer())
		GetHomeWorld()->GetCutscenePlayer()->OnCSUntrigger(name,vobInstigator);
};

void oCCSTrigger::Archive(zCArchiver &arc)
{
	zCTrigger::Archive(arc);
}
void oCCSTrigger::Unarchive(zCArchiver &arc)
{
	zCTrigger::Unarchive(arc);
}