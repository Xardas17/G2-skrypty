/******************************************************************************** 
 
     $Workfile:: oTrigger.cpp         $                $Date:: 3.04.01 15:20    $
     $Revision:: 20                   $             $Modtime:: 3.04.01 15:20    $
       $Author:: Integrator                                                     $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Bert/oTrigger.cpp $
 * 
 * 20    3.04.01 15:20 Integrator
 * 
 * 19    19.03.01 21:29 Edenfeld
 * Demo Kastration einfacher/rückgängig gemacht. 
 * 
 * 18    18.03.01 19:00 Edenfeld
 * Demo Geschichten
 * 
 * 17    22.01.01 22:42 Edenfeld
 * 
 * 16    30.11.00 15:03 Wohlers
 * 
 * 15    22.11.00 13:38 Wohlers
 * 
 * 14    9.11.00 16:54 Edenfeld
 * 
 * 13    25.10.00 21:07 Speckels
 * 

 * 
 *********************************************************************************/

#include "zcore.h"
#include "zPhysics.h"

#include "oSpell.h"
#include "oTrigger.h"
#include "oNpc.h"
#include "oGame.h"
#include "oWorld.h"
#include "oMagic.h"


zCLASS_DEFINITION	(oCTriggerChangeLevel,	zCTrigger,	0, 0)
zCLASS_DEFINITION	(oCTriggerScript,		zCTrigger,	0, 0)
/* zCLASS_DEFINITION	(oCObjectGenerator,		zCVob,		0, 0) */  // Deactivated in class-hierarchie:

oCTriggerChangeLevel::oCTriggerChangeLevel ()
{
	// No members that need to be initialised ( only zSTRINGs )
}

oCTriggerChangeLevel::~oCTriggerChangeLevel ()
{
}

/*--------------------------------------------------------------------------

    oCTriggerChangeLevel::TriggerTarget

	17-04-00		[Edenfeld]
						GOTHIC_DEMO Präprozessor Direktive verhindert Levelchange bei
						den Demos

	09-Nov-00		[Edenfeld]
					    Control Spruch/Transform Spruch wird beendet, falls versucht wird, in ein LevelChange Trigger
						zu gehen, und der Level Change wird nicht durchgeführt

	20-Nov-00		[Wohlers]
						Bei Levelwechsel Magiemodus aus und Effekt killen
--------------------------------------------------------------------------*/ 
void oCTriggerChangeLevel::TriggerTarget	(zCVob* vobInstigator)
{
#ifndef GOTHIC_DEMO
	zCTrigger::TriggerTarget(vobInstigator);

	if (vobInstigator && vobInstigator==oCNpc::player) 
	{
		// Zurückverwandeln, falls NPC transformiert wurde.
		oCSpell*    spell;
		for (int spellID=SPL_TRFSHEEP; spellID<=SPL_TRFDRAGONSNAPPER; spellID++)
		{
			spell = oCNpc::player->IsSpellActive(spellID);
			if (spell) break;
		};

		if (spell)
		{
			spell->EndTimedEffect();
			return;
		};

		zERR_MESSAGE(8,0,"B: TRIGGER: "+GetClassDef()->GetClassName_()+" "+zSTRING(GetVobName())+" triggered -> "+levelName);

		//	20-Nov-00		[Wohlers]
		//					Bei Levelwechsel Magiemodus aus und Effekt killen
		if (oCNpc::player->GetWeaponMode()==NPC_WEAPON_MAG) {
			
			oCMag_Book* mbook = oCNpc::player->GetSpellBook();
			if (mbook) mbook->KillSelectedSpell();
			oCNpc::player->EV_ForceRemoveWeapon(NULL);			
		}
		oCNpc::player->KillActiveSpells();

		// Levelwechsel aktivieren
		ogame->TriggerChangeLevel(levelName,startVob);
	}
#endif
};

void oCTriggerChangeLevel::UntriggerTarget	(zCVob* vobInstigator)
{
	zCTrigger::UntriggerTarget(vobInstigator);
};

void oCTriggerChangeLevel::SetLevelName(const zSTRING& level, const zSTRING& vobName)
{
	levelName	= level;
	startVob	= vobName;
}

void oCTriggerChangeLevel::Archive (zCArchiver& arc)
{
	zCTrigger::Archive(arc);

	arc.WriteString("levelName"		,levelName);
	arc.WriteString("startVobName"	,startVob);
}

void oCTriggerChangeLevel::Unarchive (zCArchiver& arc)
{
	zCTrigger::Unarchive(arc);

	arc.ReadString("levelName"		,levelName);
	arc.ReadString("startVobName"	,startVob);
}

// ***********************************************************************************
// Scriptfunction - Trigger
// ***********************************************************************************

oCTriggerScript::oCTriggerScript ()
{
}

oCTriggerScript::~oCTriggerScript ()
{
}

void oCTriggerScript::TriggerTarget			(zCVob* vobInstigator)
{	
	zCTrigger::TriggerTarget(vobInstigator);

	zERR_MESSAGE(8,0,"B: TRIGGER: "+GetClassDef()->GetClassName_()+" "+zSTRING(GetVobName())+" triggered -> "+scriptFunc);
	parser.SetInstance	("SELF" ,dynamic_cast<oCNpc *>(vobInstigator));
	parser.SetInstance	("OTHER",0);
	parser.SetInstance	("ITEM"	,0);
	parser.CallFunc		(scriptFunc);	
};

void oCTriggerScript::UntriggerTarget			(zCVob* vobInstigator)
{
	zERR_MESSAGE(8,0,"B: TRIGGER: "+GetClassDef()->GetClassName_()+" "+zSTRING(GetVobName())+" untriggered -> "+scriptFunc);
	zCTrigger::UntriggerTarget(vobInstigator);
};

void oCTriggerScript::SetScriptFunc (const zSTRING& name, int calls)
{
	scriptFunc	= name;
	ResetNumCanBeActivated(calls);	
}


void oCTriggerScript::Archive (zCArchiver& arc)
{
	zCTrigger::Archive(arc);

	arc.WriteString	("scriptFunc"	,scriptFunc);
}

void oCTriggerScript::Unarchive (zCArchiver& arc)
{
	zCTrigger::Unarchive(arc);

	arc.ReadString	("scriptFunc"	,scriptFunc);
}

// ***************************************************************************************
// ObjectGenerator
// ***************************************************************************************

oCObjectGenerator::oCObjectGenerator ()
{
	speed = 0.0f;
};

oCObjectGenerator::~oCObjectGenerator ()
{
};

void oCObjectGenerator::SetObjectName (const zSTRING& objName)
{
	objectName = objName;
}

void oCObjectGenerator::SetObjectSpeed (zREAL sp)
{
	speed = sp;
}

void oCObjectGenerator::OnTrigger	(zCVob* otherVob, zCVob* vobInstigator)
{
	if (!GetHomeWorld() || objectName.IsEmpty()) return;
	
	zCVob* vob = NULL;
	int index;
	
	zERR_MESSAGE(8,0,"B: TRIGGER: "+GetClassDef()->GetClassName_()+" "+zSTRING(GetVobName())+" triggered");

	// Zen - File ?
	if (objectName.Search(".ZEN")>0) {
		
	
	} else if ((index = parser.GetIndex(objectName))>0) {
		// Item ?
		vob  = ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,index);
		
	} else {
		// another Visual ?
		vob	 = zNEW(zCVob ());
		vob -> SetVisual (objectName);
	}

	if (vob) {
		// verschicken....
		vob->SetPhysicsEnabled	(TRUE);
		vob->SetTrafoObjToWorld	(trafoObjToWorld);
		GetHomeWorld	()->AddVob(vob);
		//vob->GetRigidBody	()->SetVelocity(trafoObjToWorld.GetAtVector() * speed);
		//vob->GetRigidBody	()->SetGravityEnabled(FALSE);
	};
};

void oCObjectGenerator::Archive (zCArchiver& arc)
{
	zCVob::Archive(arc);

	arc.WriteString	("objectName"	,objectName);
	arc.WriteFloat	("objectSpeed"	,speed);
}

void oCObjectGenerator::Unarchive (zCArchiver& arc)
{
	zCVob::Unarchive(arc);

	arc.ReadString	("objectName"	,objectName);
	arc.ReadFloat	("objectSpeed"	,speed);
}
