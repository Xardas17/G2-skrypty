#include "zcore.h"

#include "zCCSPool.h"
#include "zCCSContext.h"

zCLASS_DEFINITION (zCCSPoolItem, zCObject,	0,0)


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Cutscene-Poolitems
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

zCCSPoolItem::zCCSPoolItem()
{
	Init();
}

zCCSPoolItem::zCCSPoolItem(zCCSCutsceneContext* csContext)	
{
	if (csContext) assign(csContext->GetCSName().ToChar());
	Init();	
	Upper();	
};
		
void zCCSPoolItem::Init()
{	
	deactivated=FALSE;
	numPlayed=0;
	playCounter = 0;
	flags = 0;
};

zCCSPoolItem::~zCCSPoolItem()
{
};

zCCSProps::zTCSRunBehaviour	zCCSPoolItem::GetRunBehaviour(int& value) 
{ 
	value = runBehaviourValue;return runBehaviour; 
};

zCCSProps::zTCSRunBehaviour	zCCSPoolItem::GetRunBehaviour() 
{ 
	return runBehaviour; 
};

void zCCSPoolItem::SetRunBehaviour(zCCSProps::zTCSRunBehaviour beh, int& value)
{ 
	runBehaviour = beh;runBehaviourValue=value; 
};
	

void zCCSPoolItem::Archive(zCArchiver &arc)
{
	arc.WriteString	("itemName",*this);
	arc.WriteEnum	("runBehaviour","RUN_ALWAYS;RUN_TIMES;RUN_PERHOUR;RUN_PERDAY",runBehaviour);
	arc.WriteInt	("runBehaviourValue",runBehaviourValue);
	arc.WriteInt	("numPlayed", numPlayed);
	arc.WriteInt	("deactivated", deactivated);
	arc.WriteInt	("flags",flags);
}
void zCCSPoolItem::Unarchive(zCArchiver &arc)
{
	zSTRING str;
	int value;

	arc.ReadString	("itemName", str);str.Upper();assign(str);	
	arc.ReadEnum	("runBehaviour",value);runBehaviour = zCCSProps::zTCSRunBehaviour(value);
	arc.ReadInt		("runBehaviourValue",runBehaviourValue);
	arc.ReadInt		("numPlayed", numPlayed);
	arc.ReadInt		("deactivated", deactivated);
	arc.ReadInt		("flags",flags);
}

void zCCSPoolItem::TestedDeactivation()
{
	if (GetRunBehaviour()== zCCSProps::RUN_TIMES && runBehaviourValue>=numPlayed) 
	{
		Deactivate();
	}
}
zBOOL zCCSPoolItem::IsAllowedToPlay()
{
	return (	(GetRunBehaviour()!=zCCSProps::RUN_ALWAYS && runBehaviourValue>numPlayed) ||
				(GetRunBehaviour()==zCCSProps::RUN_ALWAYS)
				);
}

void zCCSPoolItem::PrintDebugInfo()
{
	zERR_MESSAGE(1,zERR_BEGIN,"B: CS: Cutscene \""+zSTRING(this)+"\" in history-pool");	
	
	if (deactivated) zERR_MESSAGE(1,0,"B: CS: *** deactivated ***");	
	
	zERR_MESSAGE(1,0,"B: CS: num of runs: "+zSTRING(GetNumPlayed()));
	
/*	if (GetNumPlayed()>0) 
	{
		zERR_MESSAGE(1,0,"B: CS: last run: "+zSTRING(GetRunDay())+".day, "+zSTRING(GetRunHour())+". hour");	
	}
*/  //[Andre]	eine solche Debuginfo ist nicht mehr möglich
	zERR_MESSAGE(1,zERR_END,"");
};


void zCCSPoolItem::ClrFlags(long _flags)
{
	flags &= ~_flags;
};

void zCCSPoolItem::SetFlags(long _flags)
{
	flags |= _flags;
};

zBOOL zCCSPoolItem::HasFlags(long _flags)
{
	return (flags & _flags) == _flags;
};
