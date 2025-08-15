// Cutscene Standart Poperties
// Auswerter

#include "zcore.h"

#include "zCCSProps.h"
#include "zCCSContext.h"

zCLASS_DEFINITION	(zCCSProps,		zCObject,	0,3)

zCCSProps::zCCSProps()
{	
	hasToBeTriggerd		= FALSE;
	csLoop				= FALSE;		
	globalCutscene		= FALSE;	
	ignore				= FALSE;	
	runBehaviour		= RUN_ALWAYS;
	runBehaviourValue	= 0;
	numLockedBlocks		= 0;
	distance			= 500.0F;
	range				= 2000.0F;
	stageName.Clear();
	name.Clear();
}

zCCSProps::~zCCSProps()
{
};

void zCCSProps::Archive(zCArchiver &arc)
{
	zCObject::Archive (arc);
	if (arc.InSaveGame())
		arc.WriteString("name",name);
	
	arc.WriteBool	("globalCutscene",globalCutscene);
	arc.WriteBool	("csLoop", csLoop);		
	arc.WriteBool	("hasToBeTriggerd",hasToBeTriggerd);			
	arc.WriteFloat	("distance",distance);
	arc.WriteFloat	("range",range);				
	arc.WriteInt	("numLockedBlocks",numLockedBlocks);
	arc.WriteEnum	("runBehaviour","RUN_ALWAYS;RUN_TIMES;RUN_PERHOUR;RUN_PERDAY",runBehaviour);
	arc.WriteInt	("runBehaviourValue",runBehaviourValue);	
	arc.WriteString ("StageName",stageName);		
	arc.WriteString ("scriptFuncOnStop",scriptFuncOnStop);			
}
void zCCSProps::Unarchive(zCArchiver &arc)
{
	zCObject::Unarchive (arc);	

	if (arc.InSaveGame())
		arc.ReadString("name",name);
	int value;
	
	arc.ReadBool	("globalCutscene",globalCutscene);		
	arc.ReadBool	("csLoop", csLoop);	
	arc.ReadBool	("hasToBeTriggerd",hasToBeTriggerd);
	arc.ReadFloat	("distance",distance);		
	arc.ReadFloat	("range",range);	
	arc.ReadInt		("numLockedBlocks",numLockedBlocks);			
	arc.ReadEnum	("runBehaviour",value);runBehaviour = zTCSRunBehaviour(value);
	arc.ReadInt		("runBehaviourValue",runBehaviourValue);		
	arc.ReadString  ("StageName",stageName);		
	arc.ReadString	("scriptFuncOnStop",scriptFuncOnStop);			
}

zBOOL zCCSProps::CheckDistance(zREAL dist)
{	
	return (ignore) || (distance<0) || (dist<=distance);
}
zBOOL zCCSProps::CheckRange(zREAL r)
{
	return (range<0) || (r<=range);
}

int zCCSProps::GetCheckRoleResult()
{
	return SCR_RESULT_INTERRUPT;
}

void zCCSProps::PrintDebugInfo()
{
	zSTRING s;
	
	if (globalCutscene)		zERR_MESSAGE(1,0,"B: CS: - is a global cutscene."); else zERR_MESSAGE(5,0,"B: CS: - is an ambient cutscene.");
	if (csLoop)				zERR_MESSAGE(1,0,"B: CS: - loops."); else zERR_MESSAGE(5,0,"B: CS: - doesn't loop.");
	if (hasToBeTriggerd)	zERR_MESSAGE(1,0,"B: CS: - has to be triggered.");	
	
	zERR_MESSAGE(1,0,"B: CS: - distance: "+zSTRING(distance));
	zERR_MESSAGE(1,0,"B: CS: - range: "+zSTRING(range));		
	s.Clear();
	switch (runBehaviour)
	{
	case RUN_ALWAYS: s = "RUN_ALWAYS";break;
	case RUN_TIMES:  s = zSTRING(runBehaviourValue)+" times";break;
	case RUN_PERHOUR:s = zSTRING(runBehaviourValue)+" times per hour";break;
	case RUN_PERDAY: s = zSTRING(runBehaviourValue)+" times per day";break;
	default: s = "unknown";
	};
	zERR_MESSAGE(1,0,"B: CS: - runBehaviour: "+s);		
};

zBOOL zCCSProps::AcceptRole	(zCCSRole* role, zCVob* vob) 
{ 
	return CheckRole(role,vob); 
};

zBOOL zCCSProps::CheckRole	(zCCSRole* role, zCVob* vob) 
{ 
	return TRUE; 
};