 
#ifndef _OCSPROPS_H_
#define _OCSPROPS_H_

#include "zCCSProps.h"

class oCCSProps : public zCCSProps
{
zCLASS_DECLARATION	(oCCSProps)
private:	

	/*
	zBOOL			scr_sight;	
	zTCS_SCReaction	scr_sight_reaction;
	zBOOL			scr_hear;
	zTCS_SCReaction	scr_hear_reaction;
	zBOOL			scr_talk;
	zTCS_SCReaction	scr_talk_reaction;
	zBOOL			scr_steal;
	zTCS_SCReaction	scr_steal_reaction;
	*/

	int resultReaction;

public:
	oCCSProps();
	
	virtual zBOOL	AcceptRole	(zCCSRole* role, zCVob* vob);	
	virtual zBOOL	CheckRole	(zCCSRole* role, zCVob* vob);	
	virtual int		CheckRoleResult();


	virtual void	Archive		(zCArchiver &arc);
	virtual void	Unarchive	(zCArchiver &arc);

};

#endif