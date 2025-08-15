/******************************************************************************** 
 
     $Workfile:: zCCSContext.cpp      $                $Date:: 24.01.01 19:17   $
     $Revision:: 68                   $             $Modtime:: 24.01.01 19:12   $
        Author:: Schrieber
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   *
   created       : 20.12.98

 * $Log: /current_work/ZenGin/_Andre/zCCSContext.cpp $
 * 
 * 68    24.01.01 19:17 Speckels
 * 
 * 67    23.01.01 19:34 Speckels
 * 
 * 66    22.01.01 21:37 Speckels
 * 
 * 42    18.01.01 17:31 Speckels
 * 
 * 41    18.01.01 14:32 Speckels
 * 
 * 64    18.01.01 0:43 Speckels
 * 
 * 63    17.01.01 18:42 Speckels
 * 
 * 62    22.12.00 1:43 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Schrieber
/// @version $Revision: 68 $ ($Modtime: 24.01.01 19:12 $)

// ============================================================================================================

#include "zcore.h"
#include "zobject.h"
#include "zoption.h"
#include "z3d.h"
#include "zVob.h"
#include "zTools.h"
#include "zworld.h"
#include "zparser.h"
#include "zCCSProps.h"
#include "zCCSManager.h"
#include "zCCSContext.h"
#include "zCCSPlayer.h"
#include "zccspool.h"
#include "zparser.h"

// [HILDEBRANDT]: fixed wrong spelling on baseclass 'zCCutscene'
zCLASS_DEFINITION	(zCCSCutsceneContext,	zCCutscene,	0,1)


#define CSTS_NOTPLAYING -1.0F	// Cutscene spielt gerade nicht
#define CSTS_INTERUPTED -2.0F	// Cutscene wurde automatisch unterbrochen
#define CSTS_FORCEDSTOP -3.0F	// Cutscene wurde manuell unterbrochen




zBOOL zCCSCutsceneContext::playDisabled = FALSE;

zBOOL zCCSCutsceneContext::DisablePlayCutscenes(zBOOL disable)
{	
	zBOOL old_setting = playDisabled;
	playDisabled = disable;
	return old_setting;
};







/////////////////////////////////////////////////////////////////////////////////////
// Construct and destruct
/////////////////////////////////////////////////////////////////////////////////////


//
// Leere Cutscene, die dynamisch erzeugt wird
//
zCCSCutsceneContext::zCCSCutsceneContext()
	:	zCCutscene(), lastTimePoint(0.0)
{	
	lastTimeStamp	= CSTS_NOTPLAYING;
	reference		= -1;
	loaded			= TRUE;
	allowedToPlay	= TRUE;
	isCutscene		= TRUE;
	wasTriggered	= FALSE;
	poolItem		= 0;	
	stage			= 0;
	alternativeStageVob	= 0;	
}

// 
// Cutscene wird von der Festplatte geladen
//
zCCSCutsceneContext::zCCSCutsceneContext(zSTRING & csname)
	: zCCutscene(), lastTimePoint(0.0)
{
	lastTimeStamp	= CSTS_NOTPLAYING;	
	reference		= -1;		
	loaded			= FALSE;
	allowedToPlay	= TRUE;
	isCutscene		= TRUE;
	wasTriggered	= FALSE;	
	poolItem		= 0;	
	stage			= 0;	
	alternativeStageVob	= 0;

	if (csname.IsEmpty()) 
	{
		zERR_FAULT("B: CS \"\": Cutscene without name not allowed");
		return;
	};

	//
	// Cutscene laden
	//
	zFILE* f = zfactory->CreateZFile(zoptions->GetDirString(DIR_CUTSCENES) + csname);
	if (f->Exists())
	{
		zERR_MESSAGE(6,0,"B: CS \""+csname+"\": Loading "+f->GetFullPath());
		
		if (f->Open()==zERR_NONE)
		{
			zCArchiver* arch = zarcFactory.CreateArchiverRead(f);
				arch->ReadObject(this);
				arch->Close();
			zRELEASE(arch);
			
			f->Close();

			loaded = TRUE;		

			zERR_MESSAGE(6,0,"B: CS \""+csname+"\": "+zSTRING(GetNumOfRoles())+" roles in cutscene");
		}
	}	
	
	properties->SetName(csname);
	properties->PrintDebugInfo();

	if (!loaded)
	{		
		zERR_FAULT("B: CS \""+csname+"\": Cutscene not found ("+f->GetFullPath()+")");	
	}	
		
	delete f;f=0;

	SetObjectName(csname);

	zERR_MESSAGE(8,0,"B: CS: Cutscene-Context constructed: "+csname);
}

//
// Cutscene wird aus einem uebergebenen Cutscene-Block erzeugt
//
zCCSCutsceneContext::zCCSCutsceneContext(zCCSBlock* bl, int ref, zBOOL asUnit)
	:	
	zCCutscene(), 	
	lastTimePoint(0.0)

{	
	allowedToPlay	= TRUE;
	isCutscene		= TRUE;
	lastTimeStamp	= CSTS_NOTPLAYING;
	reference		= ref;
	stage			= 0;
	loaded			= TRUE;	
	wasTriggered	= FALSE;
	poolItem		= 0;
	alternativeStageVob = 0;

	if (asUnit) 
	// create an entry
	{
		blocks.Insert(zCCSBlockPosition());
		blocks[blocks.GetNumInList()-1].block = bl;
		isCutscene = FALSE;
	}
	else
	// copy pointer to Subblocks
	{	
		reference = 0; // bloss nicht -1
		blocks = bl->blocks;
		properties = NULL;	
	}		
	
	SetObjectName(zSTRING(reference));

	zERR_MESSAGE(8,0,"B: CS: Cutscene-Context constructed (*).");
}
void zCCSCutsceneContext::UseThisSubBlock(zCCSBlock* bl)
{
	if (isCutscene || !bl) return;

	blocks.EmptyList();
	blocks.Insert(zCCSBlockPosition());
	blocks[blocks.GetNumInList()-1].block = bl;
}


//
// Destructor
//
zCCSCutsceneContext::~zCCSCutsceneContext()
{ 
	// 
	// Wenn referenz>=0, dann duerfen die Bloecke nicht released werden
	//
	if (reference>=0)
	{
		for (int z=0; z<blocks.GetNumInList(); z++) blocks[z].block=0; // einfach dem destructor entziehen		
	}

	//
	// Cutscene sauber beenden
	//
	if (!IsFinished()) Stop();
	
	
	// Integrierte Vobs aus der Welt nehmen
	zCWorld* world = alternativeStageVob ? alternativeStageVob->GetHomeWorld() : 0;
	if (world)
	{
		for (int rc=0; rc<roleList.GetNumInList(); rc++)
		{
			if (
				roleList[rc]->GetRoleVob() &&				// Hat die Rolle (noch) einen Vob?
				roleList[rc]->GetRoleVob()->GetHomeWorld()	// Schon nicht mehr in der Welt?
				) 
			{
				world->RemoveVob(roleList[rc]->GetRoleVob());
			}
		}
	}	
	zRELEASE_OBJ(alternativeStageVob);
	//
	// Deinit
	//
	SetPoolItem(0);  //damit wird auch das poolitem-refCtr runtergezählt
	stage				= 0;
	alternativeStageVob = 0;		
	poolItem			= 0;	

	zERR_MESSAGE(8,0,"B: CS: Cutscene-Context destructed.");
}


//
// Archivierung
//

void zCCSCutsceneContext::Archive(zCArchiver &arc)
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: CS: Archiving cutscene ...");
	zERR_MESSAGE(6,0,"B: CS: -- Cutscenename: "+GetCSName());

	zCCutscene::Archive(arc);	

	if (arc.InSaveGame())
	{
		arc.WriteBool("isCutscene",isCutscene);
		if (!isCutscene)
		{
			//zCObject::Archive(arc);
			arc.WriteInt("reference",reference);			
			zERR_MESSAGE(6,0,"B: CS: -- Is Outputunit cutscene");
		} 
		else 
		{
			//zCCutscene::Archive(arc);
			arc.WriteBool("allowedToPlay",allowedToPlay);
			zERR_MESSAGE(6,0,"B: CS: -- Is full featured cutscene");
		}
		arc.WriteInt	("actualBlock",			GetActualBlockNum());
		arc.WriteObject	("alt_stage",			alternativeStageVob);
		arc.WriteObject	("stage",				stage);
		arc.WriteBool	("wasTriggered",		wasTriggered);		

		/*
		if (isCutscene) 
		{
			zCCutscene::Archive(arc);
		}		
		else // im anderen Fall werden die Daten nicht benötigt.
		{
			zCObject::Archive(arc);
		}
		*/		
	} 	
	/*
	else 
	{
		zCCutscene::Archive(arc);
	}
	*/
	
	zERR_MESSAGE(6,zERR_END,"B: CS: -> Cutscene archived");
}

void zCCSCutsceneContext::Unarchive(zCArchiver &arc)
{
	zERR_MESSAGE(6,zERR_BEGIN,"B: CS: Unarchiving cutscene ... ");

	zCCutscene::Unarchive(arc);

	zERR_MESSAGE(6,0,"B: CS: -- Cutscenename: "+GetCSName());

	if (arc.InSaveGame())
	{
		arc.ReadBool("isCutscene",isCutscene);
		if (!isCutscene) 
		{
			// stattdessen werden die Daten aus der Lib geholt (der destruktor ignoriert diese auch) 
			//blocks.Insert(zCCSBlockPosition());
			//das Holen der OUDaten aus Lib übernimmt der CSPlayer
			//zCObject::Unarchive(arc);
			//roleVobList.Insert(0); // da kommt die eine Rolle rein; Cutscenes machen das auch
			//roleEvMList.Insert(0);
			arc.ReadInt("reference",reference);
			zERR_MESSAGE(6,0,"B: CS: -- Is outputunit cutscene");
		}
		else 
		{
			reference=-1;
			// zCCutscene::Unarchive(arc);
			arc.ReadBool("allowedToPlay",allowedToPlay);
			//das PoolItem wird nur vom CSPlayer restauriert oder gar nicht
			zERR_MESSAGE(6,0,"B: CS: -- Is full featured cutscene");
		}
		
		int blNum = 0;
		blNum = arc.ReadInt("actualBlock");				
		ResumeAtBlock(blNum);
	
		zRELEASE_OBJ(alternativeStageVob);
		zRELEASE_OBJ(stage);
		alternativeStageVob	= dynamic_cast<zCVob*>(arc.ReadObject("alt_stage"));
		stage				= dynamic_cast<zCVob*>(arc.ReadObject("stage"));
		
		arc.ReadBool("wasTriggered",wasTriggered);

/*
		// bisher an der CS teilnehmende Vobs lesen
		int anzroleVobList = arc.ReadInt("numOfroleVobList");
		for (int i=roleVobList.GetNumInList();i<anzroleVobList;i++)
		{
			roleVobList.Insert(0);
		};
		assert(roleVobList.GetNumInList()==anzroleVobList);
		zCVob* vob;
		for (int z=0; z<anzroleVobList; z++)
		{
			vob = dynamic_cast<zCVob*>(arc.ReadObject());
			roleVobList[z] = vob;
			// das muß leider später erfolgen:	roles.Insert(vob->GetEventManager());
		}
		// Hauptrolle nochmal extra
		mainRoleVob = dynamic_cast<zCVob*>(arc.ReadObject("mainRoleVob"));
*/
		lastTimeStamp = CSTS_INTERUPTED;
	}	
	/*
	else 
	{
		zCCutscene::Unarchive(arc);
	}
	*/
	
	zERR_MESSAGE(6,zERR_END,"B: CS: -> Cutscene unarchived.");
}








/////////////////////////////////////////////////////////////////////////////////////
// Play and Stop
/////////////////////////////////////////////////////////////////////////////////////


//
// StartPlaying
//
// Wenn das Cutscene-System entschieden hat, dass die Cutscene gespielt werden kann
// so wird diese Methode aufgerufen. Sie ist die letzte Instanz, die darueber entscheidet,
// ob sie nun wirklich spielen darf.
//
zBOOL zCCSCutsceneContext::StartPlaying()
{			
	//
	// Globale Cutscene abchecken
	//
		if (IsGlobalCutscene())
		{
			zCCSCutsceneContext* globalCS = ownerPlayer->GetPlayingGlobalCutscene();
			if  (globalCS && this!=globalCS)
		{	
			zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Global Cutscene delayed: Another is running!");
			return FALSE;	// dann nicht starten!!! Warten bis die andere fertig ist.
		}
	}
	
	//
	// Start-Versuch (Basismethode entscheidet nun)
	//
	if (zCCutscene::StartPlaying())
	{
		zERR_MESSAGE(5,0,"B: CS "+CS_NAME_QUOTED(properties)+": Start playing ...");

		// Waehrend des Spielens, die grundlegenden Checks nicht durchfuehren.
		// Es sei denn, die CS darf eh immer wieder neu gestartet werden.
		properties->SetIgnore(!ReplayCutscene());		
		
		return TRUE;
	}
	//
	// Startversuch schlug fehl
	//
	else
	{
		zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Start failed (in zCCSCutscene)");
		return FALSE;
	};	
}

//
// Stop()
//
// Eine Cutscene wird beendet. Diese Methode wird immer aufgerufen, auch wenn die Cutscene nie gespielt wurde,
// sondern nur schlummert.
//
void zCCSCutsceneContext::Stop()
{
	if (!ownerPlayer) 
	{
		zERR_WARNING("B: CS: Cutscene \""+GetCSName()+"\" has no player");
		return; // Cutscene wurde vermutlich bereits beendet
	}
	
	zERR_MESSAGE(7,zERR_BEGIN,"B: CS "+CS_NAME_QUOTED(properties)+": Stopping cutscene-context ...");

	// Einige Eigenschaften merken bevor die Cutscene beendet wird
	zSTRING scriptFuncName					= properties ? properties->GetScriptFuncOnStop() : "";
	zSTRING scriptFuncParm					= properties ? properties->GetName() : "";
	zBOOL	isCutscene						= IsCutscene();
	zBOOL	mainroleHasPlayedThisCutscene	= FALSE;
	zCVob*	mainrole						= GetMainRole();
	if (mainrole) 
	{
		zADDREF_OBJ(mainrole);
		mainroleHasPlayedThisCutscene = (mainrole->GetEM()->GetCutscene()==this);
	}
	

	//
	// Nun die Cutscene beenden
	//		

	zCCutscene::Stop();	// Basismethode
	
	stage			= 0;				// Die Stage wurde entfernt. :TODO: Dort auf NULL setzen, wo sie auch entfernt wird!!!	
	wasTriggered	= FALSE;	
	lastPlayResult	= CS_PLAY_STOPPED;	
	
	if (properties)		properties	->SetIgnore		(FALSE);
	if (poolItem)		poolItem	->ClrFlags		(CS_PLAYING);	// Cutscene spielt nicht mehr, also Flag zuruecksetzen	
	if (ownerPlayer)	ownerPlayer	->ForgetCutscene(this);			// ownerPlayer wird hier auf 0 gesetzt

	//
	// Scriptfunktion aufrufen
	//
	if (isCutscene && mainroleHasPlayedThisCutscene) 
	{					
		if (!scriptFuncName.IsEmpty())
		{
			int	scriptFuncIndex = parser.GetIndex(scriptFuncName);
			if (scriptFuncIndex>=0)
			{
				zERR_MESSAGE(8,0,"B: CS: Calling onStop-ScriptFunction "+scriptFuncName);		
				parser.SetInstance("SELF",mainrole);
				parser.SetInstance("OTHER",0);
				parser.SetInstance("VICTIM",0);
				parser.CallFunc(scriptFuncIndex,scriptFuncParm);		
			}
			else zERR_WARNING("B: CS: onStop-ScriptFunction not found: \""+scriptFuncName+"\"");
		}
	}	

	// Hauptrolle wieder freigeben
	zRELEASE_OBJ(mainrole);

	zERR_MESSAGE(7,zERR_END,"B: CS: Cutscene-Context stopped.");
}

//
// Interrupt()
//
// Die Cutscene wird unterbrochen. Die schlummert danach und wird automatisch wieder aufgenommen
//
void zCCSCutsceneContext::Interrupt()
{	
	zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Interrupt");
	
	lastTimeStamp	= CSTS_INTERUPTED;
	lastPlayResult	= CS_PLAY_INTERRUPTED;
	
	zCCutscene::Interrupt();		
  
	properties->SetIgnore(FALSE); // Checks wieder durchfuehren!
}

//
// ForcedInterrupt()
//
// Die Cutscene wird manuell unterbrochen. Externes Resume noetig
//
void zCCSCutsceneContext::ForcedInterrupt()
{
	zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Forced Interrupt");
	
	lastTimeStamp	= CSTS_FORCEDSTOP;
	lastPlayResult	= CS_PLAY_INTERRUPTED;
	
	zCCutscene::Interrupt();	

	// properties->SetIgnore(TRUE); // Checks weiterhin nicht durchfuehren
}



//
// Play(position)
//
// Versucht eine Cutscene zu spielen. Zahlreiche Test laufen ab, bevor es tatsaehlich
// zum Abspielen der Cutscene kommt: Die Cutscene schlummert hier, bis zum endgueltigen ok, dieser Methode.
// Sie liegert TRUE, wenn die Cutscene tatsaechlich spielt und in lastPlayResult findet sich 
// der eventuelle Grund fuer eine Verweigerung zum Spielen der Cutscene.
//
zBOOL zCCSCutsceneContext::Play(zPOINT3 position)
{						
	lastPlayResult			= CS_PLAY_CONTINUED;

	//
	// Kritische Checks
	//
	
	// :TODO: [Speckels] Ein nicht erfolgreiches Laden (s.o.) sollte schon vorher abgefangen werden (Cutscene endgueltig deaktivieren) -> FAULT-Ausgabe			
	if (!properties)					{ zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": Cutscene has no properties-object");return FALSE; };				
	if (!IsLoaded())					{ zERR_MESSAGE(8,0,"B: CS "+CS_NAME_QUOTED(properties)+": Cutscene was not correctly loaded");return TRUE; };
	if (lastTimeStamp==CSTS_FORCEDSTOP) { return FALSE;	}		


	//
	// (1) Einfache Checks
	//	

	// 1.a) Darf die Cutscene ueberhaupt noch gespielt werden?
	zBOOL play = allowedToPlay;		
	
	if (play && IsCutscene())		
	{	
		// 1.b) Cutscene ohne MainRole -> nicht erlaubt.
		play = play && GetMainRole();
	}

	//
	// (2) Komplexere Check (meist nur vor dem Spielen einer Cutscene notwendig)
	//
	
	if (play && IsCutscene() && !properties->Ignore())
	{					
		// 2.a) Distance-Check : Ist die Hauptrolle auch in passender Entfernung zur übergebenen Position?			
		zPOINT3 mainRolePosition	= GetMainRole()->GetPositionWorld();
		zVEC3	distanceVec			= position - mainRolePosition;				
		play = play && CheckDistance(distanceVec.LengthApprox());
		if (!play && lastPlayResult==CS_PLAY_CONTINUED) lastPlayResult = CS_PLAY_TOOFAR;		
		
		// 2.b) Muss die Cutscene getriggered werden?
		play = play && (wasTriggered || !HasToBeTriggered());
		if (!play && lastPlayResult==CS_PLAY_CONTINUED) lastPlayResult = CS_PLAY_NOTTRIGGERED;						
	}

	//
	// (3) Cutscene-Check: Rollen testen (scr_result speichert die gewuenschte Aktion)
	// 
	int	scr_result = 0;	
	if (play && IsCutscene())
	{				
		play = play && CSCheck(scr_result);
		if (!play && lastPlayResult==CS_PLAY_CONTINUED)	lastPlayResult = CS_PLAY_CHECKFAILED;
	}		
	
	//
	// (4) Wenn bis hierin alles glatt gelaufen ist ...
	//
	if (play)
	{						
		// 4.a) Versuch, die Cutscene zu starten (start playing)
		if (lastTimeStamp == CSTS_NOTPLAYING )
		{
			if (StartPlaying())
			{
				zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Start playing ...");
				lastPlayResult = CS_PLAY_STARTEDPLAYING;
				if (poolItem) poolItem->SetFlags(CS_PLAYED);
			} 
			else 
			{
				zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Start playing ... failed");
				lastPlayResult = CS_PLAY_STARTFAILED;
				goto csplay_done;
			}
		}

		// 4.b) Versuch, die Cutscene weiterspielen zu lassen (resume)
		else if (lastTimeStamp == CSTS_INTERUPTED) 
		{
			if (ResumeActBlock())
			{
				zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": Resume playing ...");			
				lastPlayResult = CS_PLAY_RESUMED;			
			} 
			else 
			{
				lastPlayResult = CS_PLAY_RESUMEFAILED;
				goto csplay_done;
			}
		}		

		// 4c) Cutscene wird hier gespielt: Nächsten Zyklus spielen!

		if (poolItem) poolItem->SetFlags(CS_PLAYING);		

		zREAL	timerTime		= ztimer.GetTotalTimeF() / 1000.0F;
		zCSTIME	newTimePoint	= timerTime-lastTimeStamp;
		if (lastTimePoint<newTimePoint)
		{			
			if (PlaySub(lastTimePoint,newTimePoint)==0) lastTimePoint = newTimePoint;			
		}
	}
	else
	//
	// 5. ... und wenn das Spielen nicht erlaubt ist ...
	//
	{
		// 5.a) Eine spielende Cutscene beenden
		if (lastTimeStamp>=0.0F)
		{			
			if (scr_result==SCR_RESULT_INTERRUPT) 
			{
				Interrupt();
				lastPlayResult = CS_PLAY_INTERRUPTED;
			} 
			else // ansonsten immer Stoppen
			{  
				Stop();
				lastPlayResult = CS_PLAY_STOPPED;
			};
		};
	}	

	//
	// 6. Hier ist nun Schluss mit lustig: Fehler analysieren
	//
csplay_done:;

	// Ausgabe von Fehlern (zur Optimierung den Error-Filterlevel checken)
	if (zerr.GetFilterLevel()>=9)
	{
		zSTRING reason;
		switch (lastPlayResult)
		{
			case CS_PLAY_TOOFAR:		reason = "distance-check failed";break;
			case CS_PLAY_MAXREACHED:	reason = "maximum number of runs in specified period";break;
			case CS_PLAY_NOTTRIGGERED:	reason = "missing trigger-event";break;
			case CS_PLAY_CHECKFAILED:	reason = "failed cutscene-check";break;				
			case CS_PLAY_STOPPED:		reason = "stop";break;		
			case CS_PLAY_INTERRUPTED:	reason = "interruptiion";break;		
			default:					reason = "playing cutscene: "+zSTRING(play);
		};
		zERR_MESSAGE(zerr.GetFilterLevel(),0,"B: CS "+CS_NAME_QUOTED(properties)+": "+reason);
	};

	return play;
}


//
// Auf ein Un/Trigger reagieren
//
void zCCSCutsceneContext::HandleTrigger()
{
	zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": HandleTrigger");
	wasTriggered = true;
};

void zCCSCutsceneContext::HandleUntrigger()
{
	// Untrigger soll ueberhaupt nicht mehr bearbeitet werden (ist sicherer).

	// zERR_MESSAGE(7,0,"B: CS "+CS_NAME_QUOTED(properties)+": HandleUntrigger");
	// wasTriggered = false;
};









/////////////////////////////////////////////////////////////////////////////////////
// Get, Set and Misc
/////////////////////////////////////////////////////////////////////////////////////



///
// Einige Informationen abgreifen.
///

zCSTIME	zCCSCutsceneContext::GetLastTimePoint()
{
	return lastTimePoint;
};

zCSTIME	zCCSCutsceneContext::GetLastTimeStamp()
{
	return lastTimeStamp; 
};


zCCSCutsceneContext::zTCSPlayResult zCCSCutsceneContext::GetLastPlayResult(zSTRING& result)
{
	switch (lastPlayResult)
	{
		case CS_PLAY_STARTEDPLAYING:	result="startplay";break;
		case CS_PLAY_STOPPED:			result="stop";break;		
		case CS_PLAY_INTERRUPTED:		result="interpt";break;
		case CS_PLAY_RESUMED:			result="resumed";break;
		case CS_PLAY_CONTINUED:			result="cont.";break;
		case CS_PLAY_DISABLED:			result="xxx";break;

		case CS_PLAY_STARTFAILED:		result="startfail";break;		
		case CS_PLAY_RESUMEFAILED:		result="res.fail";break;		
		case CS_PLAY_TOOFAR:			result="TooFar";break;
		case CS_PLAY_MAXREACHED:		result="Max";break;
		case CS_PLAY_NOTTRIGGERED:		result="NoTrigger";break;
		case CS_PLAY_CHECKFAILED:		result="CheckFail";break;
		default:						result="N/A";
	}
	return lastPlayResult;
}



///
// AreU(csname)
//
// Achtung: Die Methode ist Case-Sensitiv !
// Falls anderes erwuenscht, muss eine Konvertierung in Grossbuchstaben weiter oben passieren
///

zBOOL zCCSCutsceneContext::AreU(const zSTRING & csname)
{
	return (csname==properties->GetName());
}

zBOOL zCCSCutsceneContext::AreU(int ref)
{
	return (ref==reference);
}



///
// Methoden, mit denen man den Zustand der Cutscene erfragen kann
///

zBOOL zCCSCutsceneContext::IsForcedInterrupted()
{
	return lastTimeStamp==CSTS_FORCEDSTOP;
}


zBOOL zCCSCutsceneContext::IsPlaying()
{
	return (lastTimeStamp>=0) && !IsFinished();
};

zBOOL zCCSCutsceneContext::IsFinished()
{	
	// Wenn nicht geladen, und keine globale Cutscene dann FALSE 
	// Damit die Cutscene nicht staendig neu geladen wird. 
	
	// :TODO: Das Laden einer nicht vorhandenen Cutscene muss schon beim Ladeversuch
	// unterbunden werden -> Nicht vorhandene Cutscene muessen im Pool deaktiviert werden!
	if (!loaded && !IsGlobalCutscene()) return FALSE;
	
	return zCCutscene::IsFinished();
};



///
// Soll die Cutscene jederzeit erneut gestartet werden?
// Zeigt an, dass die Cutscene jederzeit wieder unterbrochen werden kann.
// Andere laufen durch. 
///
zBOOL zCCSCutsceneContext::ReplayCutscene()
{
	return properties->Loop(); // nur, wenn es eine loopende Cutscene ist
};


void zCCSCutsceneContext::SetPoolItem(zCCSPoolItem* _poolItem)
{
	zRELEASE(poolItem);
	poolItem = _poolItem;
	if (poolItem) 
	{
		poolItem->AddRef();
		// poolItem->SetFlags(CS_PLAYING);
		if (!loaded) poolItem->Deactivate();
	}
};

void zCCSCutsceneContext::PrepareBlock()
{
	zCCutscene::PrepareBlock();
	lastTimeStamp = (ztimer.GetTotalTimeF()/1000);
	lastTimePoint = 0;

	if (!ReplayCutscene()) properties->SetIgnore(TRUE);
}



zCVob* zCCSCutsceneContext::GetStage()
{
	if (stage) return stage;
	else return  alternativeStageVob;
}


void zCCSCutsceneContext::SetStage(zCVob* vob)
{   
	zADDREF_OBJ(vob);
	zRELEASE_OBJ(alternativeStageVob);	
	alternativeStageVob = vob;  // erster angemeldeter vob	
	stage = LoadStage();
};


// :TODO: [Speckels] Verstehe ich nicht: Warum wird initVob ignoriert? Ist alternativeStageVob ueberhaupt noch sinnvoll. Was ist das?
zCVob* zCCSCutsceneContext::CatchPlayer(zCVob* initVob)
{
	return zCCutscene::CatchPlayer(alternativeStageVob);
}


// :TODO: [Speckels] Aeh, was macht diese Methode?
void zCCSCutsceneContext::ForcedResume()
{
	if (IsForcedInterrupted())
	{
		lastTimeStamp=CSTS_INTERUPTED;
	}
}


///
// :TODO: [Speckels] Diese Methode wird nirgends mehr aufgerufen. Dafuer aber CSCheck direkt. Weg damit.
///
zBOOL zCCSCutsceneContext::CheckRoleReactions()
{
	int scr_result;
	zBOOL start = CSCheck(scr_result);	
	if (!start)
	{		
		if (lastTimeStamp>=0.0F) // Spielt er gerade?
		{		
			if (scr_result==SCR_RESULT_INTERRUPT) 
			{
				Interrupt();
				lastPlayResult = CS_PLAY_INTERRUPTED;			
			} 
			else 
			{
				Stop();
				lastPlayResult = CS_PLAY_STOPPED;
			}
		}	
	}		
	return start;
};


////////////////////////////////////////////////////////////////////////////////
// Diverse Debugausgaben
////////////////////////////////////////////////////////////////////////////////



void zCCSCutsceneContext::PrintDebugInfo(const zSTRING& parm)
{
	zERR_MESSAGE(1,zERR_BEGIN,"B: CS: Cutscene \""+GetCSName()+"\"");

	zCCutscene::PrintDebugInfo(parm);		

	if (parm=="PROPS" || parm=="STATES")
	{
		if (lastTimeStamp==CSTS_NOTPLAYING) zERR_MESSAGE(1,0,"B: CS: not playing");
		else if (lastTimeStamp==CSTS_INTERUPTED) zERR_MESSAGE(1,0,"B: CS: interrupted");
		else if (lastTimeStamp==CSTS_FORCEDSTOP) zERR_MESSAGE(1,0,"B: CS: forced stop");
		else if (lastTimeStamp>0) zERR_MESSAGE(1,0,"B: CS: running ...");
		else zERR_MESSAGE(1,0,"B: CS: unknown state "+zSTRING(lastTimeStamp)+"...");		

		if (parm=="PROPS")
		{		
			properties->PrintDebugInfo();
		};

	};	
	zERR_MESSAGE(1,zERR_END,"");
};


zBOOL zCCSCutsceneContext::AddMainRole(zCVob* roleVob)
{
	zBOOL result = zCCutscene::AddMainRole(roleVob);
	// Wenn das Hinzufuegen fehlgeschlagen ist, dann
	// die Cutscene fuers komplette Spiel sperren (Datenfehler!!!)
	if (!result && poolItem)
	{
		poolItem->Deactivate();
	};
	return result;
};

