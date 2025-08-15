// Cutscene Game Poperties
// Auswerter

#include "zcore.h"
#include "zArchiver.h"

#include "oCSProps.h"
#include "oCSManager.h"
#include "oCSPlayer.h"


zCLASS_DEFINITION(oCCSProps, zCCSProps, 0,1)

oCCSProps::oCCSProps()	
{
	/*
	scr_sight	= FALSE;	
	scr_hear	= FALSE;
	scr_steal	= TRUE;
	scr_talk	= TRUE;
	scr_sight_reaction	= SCR_RESULT_END;
	scr_hear_reaction	= SCR_RESULT_END;
	scr_steal_reaction	= SCR_RESULT_END;
	scr_talk_reaction	= SCR_RESULT_END;
	*/
};


void oCCSProps::Archive(zCArchiver &arc)
{
	zCCSProps::Archive(arc);
	/*
	zSTRING enumString("NOTHING;END;INTERRUPT");
	
	if (arc.InProperties())
	{
		arc.WriteGroupBegin("reactions");
	};

	arc.WriteBool("sight",scr_sight);		
	arc.WriteEnum("sight_reaction",enumString.ToChar(),scr_sight_reaction);

	arc.WriteBool("hear",scr_hear);
	arc.WriteEnum("hear_reaction",enumString.ToChar(),scr_hear_reaction);

	arc.WriteBool("talk",scr_talk);
	arc.WriteEnum("talk_reaction",enumString.ToChar(),scr_talk_reaction);

	arc.WriteBool("steal",scr_talk);
	arc.WriteEnum("steal_reaction",enumString.ToChar(),scr_steal_reaction);

	if (arc.InProperties())
	{
		arc.WriteGroupEnd("reactions");
	};
	*/
}
void oCCSProps::Unarchive(zCArchiver &arc)
{
	zCCSProps::Unarchive(arc);
	/*	
	int nr;
	
	nr=0;
	arc.ReadBool("sight",scr_sight);		
	arc.ReadEnum("sight_reaction",nr);scr_sight_reaction = zTCS_SCReaction(nr);

	nr=0;
	arc.ReadBool("hear",scr_hear);
	arc.ReadEnum("hear_reaction",nr);scr_hear_reaction = zTCS_SCReaction(nr);
		
	nr=0;
	arc.ReadBool("talk",scr_talk);
	arc.ReadEnum("talk_reaction",nr);scr_talk_reaction = zTCS_SCReaction(nr);
	
	nr=0;
	arc.ReadBool("steal",scr_steal);
	arc.ReadEnum("steal_reaction",nr);scr_steal_reaction = zTCS_SCReaction(nr);
	*/
}


//
// AcceptRole beim Sammeln der Rollen aufgerufen, um zu testen,
// ob der Vob als Rolle der Cutscene akzeptiert werden kann.
// Intern (in Basismethode) wird auch CheckRole aufgerufen!!!
//
zBOOL oCCSProps::AcceptRole(zCCSRole* role, zCVob* vob)
{
	return zCCSProps::AcceptRole(role,vob);
};


//
// CheckRole wird während einer Cutscene staendig aufgerufen, um zu testen,
// ob eine Rolle noch in einem gueltigen Zustand ist.
// Wird auch vopn AcceptRole aufgerufen.
//
zBOOL oCCSProps::CheckRole(zCCSRole* role, zCVob* vob)
{
	resultReaction = SCR_RESULT_NOTHING;
	
	if (!zCCSProps::CheckRole(role,vob)) return FALSE;	
	
	if (!vob) return TRUE;			

	return ((vob->GetCSStateFlags() & CS_NOT_ALLOWED_AS_ROLE) != CS_NOT_ALLOWED_AS_ROLE);
}


	/*
	if (!vob) return TRUE;

	int flag = vob->GetCSStateFlags();

	// basisklasse
	zBOOL start = TRUE;
	zSTRING s;
	if (!zCCSProps::CheckRole(role,vob))
	{
		s="rolecheck";
		start=FALSE;
	};
	
	// dann soll immer unterbrochen werden...	
	if ((SCR_AIM & flag)!=0) 
	{
		s = "scr_aim";
		start=FALSE;
	};
	if ((SCR_THREATEN & flag)!=0) 
	{
		s = "scr_threaten";
		start=FALSE;
	};
	if ((SCR_DAMAGE & flag)!=0) 
	{
		s = "scr_damage";
		start=FALSE;
	};
	
	if (!start) 
	{
		zERR_MESSAGE(8,0,"B: CS: CheckRole -> fatal action fired: "+s);	
		resultReaction = SCR_RESULT_END;
		goto finished;
	}
	
	// dann die (Filter) Flags (negativ) : 
	//       soll <scr_var> getestet werden
	//	     dann darf es in costumID nicht gesetzt sein
	
	if (scr_sight && ((SCR_SIGHT & flag)!=0))
	{ 
		resultReaction = scr_sight_reaction;
		zERR_MESSAGE(8,0,"B: CS: CheckRole -> scr_sight fired");
		if (resultReaction==SCR_RESULT_END) goto finished;
	}

	if (scr_hear && ((SCR_HEAR & flag)!=0)) 
	{
		resultReaction = scr_hear_reaction;
		zERR_MESSAGE(8,0,"B: CS: CheckRole -> scr_hear fired");
		if (resultReaction==SCR_RESULT_END) goto finished;
	}

	if (scr_talk && ((SCR_TALK & flag)!=0)) 
	{
		resultReaction = scr_talk_reaction;
		zERR_MESSAGE(8,0,"B: CS: CheckRole -> scr_talk fired");
		if (resultReaction==SCR_RESULT_END) goto finished;
	}

	if (scr_steal && ((SCR_STEAL & flag)!=0))
	{ 
		resultReaction = scr_steal_reaction;
		zERR_MESSAGE(8,0,"B: CS: CheckRole -> scr_steal fired");
		if (resultReaction==SCR_RESULT_END) goto finished;
	}	

finished:
	zBOOL result = (resultReaction==SCR_RESULT_NOTHING);
	// Loopende Cutscenes an dieser Stelle beenden
	if (!result)
	{
		csLoop = false;
	}
	return result;
}
	*/

int oCCSProps::CheckRoleResult()
{
	return resultReaction;
}