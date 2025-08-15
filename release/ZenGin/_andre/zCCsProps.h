
#ifndef _ZCCSPROPS_H_
#define _ZCCSPROPS_H_

#include "zObject.h"

enum zTCS_SCReaction { SCR_RESULT_NOTHING, SCR_RESULT_END, SCR_RESULT_INTERRUPT };



 
class zCCSRole;

class zCCSProps : public zCObject
{
zCLASS_DECLARATION	(zCCSProps)

public:

	enum zTCSRunBehaviour { RUN_ALWAYS, RUN_TIMES, RUN_PERHOUR, RUN_PERDAY };

	zCCSProps();
	virtual ~zCCSProps();	

	zSTRING&			GetStageName() { return stageName; };

	// Check, if vob is acceptable as a role of the cutscene (will call CheckRole, too)
	virtual zBOOL		AcceptRole	(zCCSRole* role, zCVob* vob);

	// Check, if role is valid while cutscene is playing
	virtual zBOOL		CheckRole	(zCCSRole* role, zCVob* vob);

	virtual int			GetCheckRoleResult();

	virtual zBOOL		CheckDistance(zREAL distance);
	virtual zBOOL		CheckRange(zREAL distance);		
	
	zBOOL				Loop() { return csLoop; };
	zBOOL				HasToBeTriggered() { return !ignore && hasToBeTriggerd; };

	zBOOL				IsGlobalCutscene() { return globalCutscene; };
	void				SetGlobalCutscene(zBOOL value) { globalCutscene = value; };

	zTCSRunBehaviour	GetRunBehaviour(int& value) { value = runBehaviourValue;return runBehaviour; };
	void				SetRunBehaviour(zTCSRunBehaviour beh, int& value) { runBehaviour = beh;runBehaviourValue=value; };

	virtual void		PrintDebugInfo();

	virtual void		Archive		(zCArchiver &arc);
	virtual void		Unarchive	(zCArchiver &arc);

	void				SetName(zSTRING _name) { name = _name;name.Upper(); };
	zSTRING				GetName() { return name; };

	void				SetIgnore(zBOOL _ignore = TRUE) { ignore = _ignore; };	
	zBOOL				Ignore() { return ignore; };	

	zSTRING				GetScriptFuncOnStop() { return scriptFuncOnStop; };

	zINT				GetNumLockedBlocks() { return numLockedBlocks; };

protected:

	zSTRING	name;

	zBOOL	csLoop;
	zBOOL	globalCutscene;
	
	zREAL	distance;
	zBOOL	hasToBeTriggerd;
	zREAL	range;	

	zBOOL	ignore;	

	int		numLockedBlocks;

	zSTRING	stageName;
	zSTRING	scriptFuncOnStop; // Script will be called if Cutscene stops (not "end")

	// for external use:
	zTCSRunBehaviour	runBehaviour;
	int					runBehaviourValue;
};

#endif