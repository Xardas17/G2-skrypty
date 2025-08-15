#include "zcore.h"

#include "zCCSPlayer.h"
#include "zCCSManager.h"

#include "zsession.h"
#include "z3d.h"
#include "zVob.h"
#include "zoption.h"
#include "zworld.h"

zCCSPlayer* dbplayer;

#define IGNORE_SAME_SVM_MODULES
// #define CS_ONE_BY_ONE

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Cutscene-Player
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


zCLASS_DEFINITION	(zCCSPlayer, zCObject,	0,1)

zCCSPlayer::zCCSPlayer()
		   :zCCSDebugger(), playList() //, breakList()	
{	
	debugInfoOnScreen	= FALSE;
	debugInfoScreen		= 0;
	ownerWorld			= 0;
	ownerManager		= 0;
	timerCtr			= 0;
	
	lastProcessDay = 0;
	lastProcessHour = 0;
	processingListItem= 0;
	processingCtr= 0;	
#ifdef DEBUG_SPECKELS
	ToggleDebugInfo();
#endif
}

zCCSPlayer::~zCCSPlayer()
{	
	StopAllCutscenes();

	for (int c=0; c<playList.GetNumInList(); c++)
	{
		//das Macro macht Probleme, also nicht das Macro

		if (playList[c]) 
		{
//			playList[c]->SetOwnerPlayer(0);
			playList[c]->Release();	
		}
	}
	playList.DeleteList();

	if (debugInfoScreen) delete debugInfoScreen;
	debugInfoScreen	= 0;
	ownerWorld = 0;
	ownerManager = 0;
}

// SetOwnerWorld:
// Der CSPlayer holt sich von der Welt ueber seine OwnerSession den CutsceneManager.
void zCCSPlayer::SetOwnerWorld(zCWorld* world)
{	
	ownerWorld		= world;		
};

void zCCSPlayer::SetOwnerManager(zCCSManager* manager)
{	
	ownerManager = manager;
};

//////////////////////////////////////////////////
// Start playing a cutscene
//////////////////////////////////////////////////


zCCSCutsceneContext* zCCSPlayer::StartCutscene(zCCutscene* cs, zCVob* vob, zSTRING scene)
// Der Spacer ruft diese Methode auf, um eine vorhandene Cutscene zu starten (testen)
{
	zERR_ASSERT(ownerManager);
	zERR_ASSERT(ownerWorld);
	zERR_ASSERTT(vob,"B: CS \""+scene+"\": Start new cutscene: called without a mainrole-vob");
	zERR_ASSERTT(vob->GetEventManager(),"B: CS \""+scene+"\": Start new cutscene: called without valid EventManager!");
	
	scene.Upper();
	
	//
	// Testen, ob die Cutscene schon im Gang ist.
	//

	zCCSCutsceneContext* cutscene = GetStartedCutscene(scene);
	if (cutscene)
	{
		zERR_MESSAGE(7,0,"B: CS \""+scene+"\": Start new cutscene: This Cutscene is still running");		
		return cutscene;
	}

	zCCSCutsceneContext* returnedCutscene=0;

	zERR_MESSAGE(7,zERR_BEGIN,"B: CS \""+scene+"\": Start new cutscene: Creating new Cutscene-Instance ...");

	cutscene = zNEW(zCCSCutsceneContext(cs,-1,false));		
	cutscene->SetRoleListForDebugging(cs->roleList);

	cutscene->SetProperties(dynamic_cast<zCCSProps*>(cs->properties->CreateCopy()));
	if (cutscene->GetProperties()) cutscene->GetProperties()->SetName(scene);

	// Hauptrolle hinzufügen
	if (!cutscene->AddMainRole(vob))
	{
		cutscene->Stop();						
	}
	else
	{		
		cutscene->SetStage(vob);				
			
		if (!scene.IsEmpty()) 	// Simulation	
		{				
			ownerManager->InitiateCSwithContext(cutscene);							
			cutscene->GetProperties()->SetIgnore(FALSE); // simulieren, deshalb checks nicht ignorieren
		}
		else  					// keine Simulation	
		{		
			scene = "temp";
			cutscene->GetProperties()->SetIgnore(TRUE);
		};
		
		InsertCutscene(cutscene);		
		returnedCutscene = cutscene;
	}
	
	zRELEASE(cutscene);

	zERR_MESSAGE(7,zERR_END,"");

	return returnedCutscene;
}


zCCSCutsceneContext* zCCSPlayer::StartCutscene(zSTRING & scene, zCVob* vob)
// Das Game ruft diese Methode auf, wenn eine neue Cutscene gestartet werden soll.
{		
	zERR_ASSERT(ownerManager);
	zERR_ASSERT(ownerWorld);
	zERR_ASSERTT(vob,"B: CS \""+scene+"\": Start new cutscene: called without a mainrole-vob");
	zERR_ASSERTT(vob->GetEventManager(),"B: CS \""+scene+"\": Start new cutscene: called without valid EventManager!");
	
	if (zCCSCutsceneContext::playDisabled) return 0;
	
	scene.Upper();
	
	zCCSCutsceneContext* sceneCS = GetStartedCutscene(scene);
	if (sceneCS) 
	{
		return 0;
	}
		
	//
	// CutsceneContext erstellen (laden)		
	//	
			
	zCCSCutsceneContext* cs = ownerManager->CreateNewCutscene(scene);					
	
	zCCSCutsceneContext* returnedCutscene=0;
	if (cs && cs->IsLoaded()) 
	{						
		if (cs->AddMainRole(vob)) 
		{
			zERR_MESSAGE(4,0,"B: CS \""+scene+"\": Start new cutscene");
			cs->SetStage(vob); 
			InsertCutscene(cs);			
			returnedCutscene=cs;
		}
		else 
		{						
			cs->Stop();						
		}		
	}
	
	zRELEASE(cs);

	zERR_MESSAGE(8,0,"B: CS: New Cutscene created and started");
	return returnedCutscene;
}

zCCSCutsceneContext* zCCSPlayer::CreateNewOutputUnit(int ref, zCVob* vob)
{
	zSTRING ouName(ref);

	zERR_ASSERT(ownerManager);
	zERR_ASSERT(ownerWorld);
	zERR_ASSERTT(vob,"B: CS \""+ouName+"\": Start new output-unit: called without a mainrole-vob");
	zERR_ASSERTT(vob->GetEventManager(),"B: CS \""+ouName+"\": Start new output-unit: called without valid EventManager!");
	
	//
	// Ist die OU-Referenz ok?
	//
	if (ownerManager->LibValidateOU(ref)==FALSE) 
	{ 
		zERR_WARNING("B: CS \""+ouName+"\": Get output-unit: reference not found");
		return 0;
	}		

	//
	// Cutscene erzeugen
	//
	zERR_MESSAGE(7,0,"B: CS \""+ouName+"\": Get new output-unit");

	zCCSCutsceneContext* cutscene = ownerManager->CreateNewOutputUnit(ref);
	
	if (cutscene) cutscene->GetProperties()->SetName(ouName);					
	
	zERR_MESSAGE(8,0,"B: CS: New Outputunit created from player");
	return cutscene;
};


zCCSCutsceneContext* zCCSPlayer::StartOutputUnit(int ref, zCVob* vob)
{	
	zSTRING ouName(ref);

	zERR_ASSERT(ownerManager);
	zERR_ASSERT(ownerWorld);
	zERR_ASSERTT(vob,"B: CS \""+ouName+"\": Start new output-unit: called without a mainrole-vob");
	zERR_ASSERTT(vob->GetEventManager(),"B: CS \""+ouName+"\": Start new output-unit: called without valid EventManager!");
	
	//
	// Ist die OU-Referenz ok?
	//
	if (ownerManager->LibValidateOU(ref)==FALSE) 
	{ 
		zERR_WARNING("B: CS \""+ouName+"\": Start new output-unit: reference not found");
		return 0;
	}		
#ifdef IGNORE_SAME_SVM_MODULES
	if (ownerManager->LibIsSvmModuleRunning(ref))
	{
		zERR_MESSAGE(4,0,"B: CS \""+ouName+"\": *** SVM-Module ignored ***");
		return 0;
	};
#endif

	//
	// Laeuft die Outputunit schon irgendwo?
	//
	zCCSCutsceneContext* cutscene = GetStartedCutscene(ouName);
	if (cutscene) 
	{	
		zERR_MESSAGE(7,0,"B: CS \""+ouName+"\": Start new output-unit: is already running.");
		return 0;
	};
	
	//
	// Cutscene starten
	//
	zERR_MESSAGE(7,0,"B: CS \""+ouName+"\": Starting new output-unit now");

	zCCSCutsceneContext* returnedCutscene=0;	
	
	cutscene = ownerManager->CreateNewOutputUnit(ref);
	if (cutscene)
	{
		cutscene->GetProperties()->SetName(ouName);			

		InsertCutscene(cutscene);
		returnedCutscene = cutscene;

		cutscene->AddRoleOU(vob);
		cutscene->StartPlaying();
	}
	
	zRELEASE(cutscene);

	zERR_MESSAGE(8,0,"B: CS: New Outputunit created and started");
	return returnedCutscene;
}


void zCCSPlayer::ForgetCutscene	(zCCutscene* cs)
{
	// Processing ListItem auf Null setzen: Koennte von RemoveCutscene entfernt werden
	processingListItem=0; 

	RemoveCutscene(dynamic_cast<zCCSCutsceneContext*>(cs)); 
	cs=0; // Achtung, nach RemoveCutscene() ist cs vermutlich nicht mehr gueltig

	zERR_MESSAGE(8,0,"B: CS: Cutsceneplayer forgot cutscene.");
};















// Alle laufenden Cutscenes unterbrechen
void zCCSPlayer::Interrupt()
{
	zCCSCutsceneContext* _context =0;
	for (int z=0; z<playList.GetNumInList(); z++)
	{
		_context = playList[z];
		_context->ForcedInterrupt();
	}
}

// Alle laufenden Cutscenes fortführen
void zCCSPlayer::Resume()
{

	for (int z=0; z<playList.GetNumInList(); z++)
	{						
		if (!playList[z]->IsFinished())
		{
			playList[z]->ResumeActBlock();
		}

	}
}


//
//
// Entfernen und Einfuegen einer Cutscene in die Playlist
// Parameter by reference / Methoden sind protected, da sie nur intern verwendet werden.
//

void zCCSPlayer::InsertCutscene(zCCSCutsceneContext* csContext)
{
	if (!csContext) return;

	zERR_MESSAGE(8,0,"B: CS: Adding cutscene to playlist: \""+csContext->GetCSName()+"\" (refCtr:"+zSTRING(csContext->GetRefCtr())+")");	
	
#ifdef IGNORE_SAME_SVM_MODULES
	int nr = csContext->GetCSName().ToInt();
	if (nr>0) ownerManager->LibSvmModuleStart(nr);
#endif

	csContext->AddRef();	
	playList.Insert(csContext);	
	csContext->SetOwnerPlayer(this);
}

void zCCSPlayer::RemoveCutscene(zCCSCutsceneContext* csContext)
{
	if (!csContext) return;

	zERR_MESSAGE(8,0,"B: CS: Removing cutscene from playlist: \""+csContext->GetCSName()+"\" (refCtr:"+zSTRING(csContext->GetRefCtr())+")");
	
#ifdef IGNORE_SAME_SVM_MODULES
	int nr = csContext->GetCSName().ToInt();
	if (nr>0) ownerManager->LibSvmModuleStop(nr);
#endif

	csContext->SetOwnerPlayer(0);
	playList.Remove(csContext);				
	zRELEASE(csContext);
}


void zCCSPlayer::OnCSTrigger(zSTRING & csname, zCVob* source)
{
	zERR_MESSAGE(8,0,"B: CS: Player::OnCSTrigger");
	int zEnd = playList.GetNumInList();
	int z = 0;
	zBOOL found = FALSE;
	if (zEnd==0) return;
	else 
	{
		while (z<zEnd && !found) 
		{
			if (playList[z]->GetCSName()==csname) found = TRUE;
			else z++;
		}
		if (found) 
		{
			zERR_MESSAGE(8,0,"B: CS: Player::OnCSTrigger found the cutscenes and calls HandleTrigger");
			playList[z]->HandleTrigger();
		}
	}
}

void zCCSPlayer::OnCSUntrigger(zSTRING & csname, zCVob* source)
{
	int zEnd = playList.GetNumInList();
	int z = 0;
	zBOOL found = FALSE;
	if (zEnd==0) return;
	else 
	{
		while (z<zEnd && !found) 
		{
			if (playList[z]->GetCSName()==csname) found = TRUE;
			else z++;
		}
		if (found) playList[z]->HandleUntrigger();
	}
}

void zCCSPlayer::Archive(zCArchiver &arc)
{
	zERR_MESSAGE(5,zERR_BEGIN,"B: CS: Archiving cutsceneplayer ...");

	zCObject::Archive(arc);

	if (arc.InSaveGame())
	{
		// Die letzte Uhrzeit und so
		arc.WriteInt("lastProcessDay",lastProcessDay);
		arc.WriteInt("lastProcessHour",lastProcessHour);

		// Playliste speichern
		arc.WriteInt("playListCount",playList.GetNumInList());
		zSTRING plChunkName("playContext");
		for (int z=0; z<playList.GetNumInList(); z++)
		{
			arc.WriteObject(zSTRING(plChunkName+zSTRING(z)).ToChar(),playList[z]);
		}
	}
	zERR_MESSAGE(5,zERR_END,"B: CS: Cutsceneplayer archived.");
}

void zCCSPlayer::Unarchive(zCArchiver &arc)
{	
	zERR_MESSAGE(5,zERR_BEGIN,"B: CS: Unarchiving cutsceneplayer ...");
	
	zCObject::Unarchive(arc);		

	// Playliste leeren
	for (int c=0; c<playList.GetNumInList(); c++)
	{			
		if (playList[c])
		{
			playList[c]->Stop();
			playList[c]->Release();			
		}
	}
	playList.DeleteList();	
	
	if (arc.InSaveGame()) 
	{
		// die letzte Uhrzeit und so
		arc.ReadInt("lastProcessDay",lastProcessDay);
		arc.ReadInt("lastProcessHour",lastProcessHour);		

		// Playlist laden		
		int csCount = 0;
		arc.ReadInt("playListCount",csCount);		
		zSTRING itemChunkName("playContext");
		int z = 0;
		zCCSCutsceneContext* newContext = 0;
		while (z<csCount)
		{		
			newContext = dynamic_cast<zCCSCutsceneContext*>(arc.ReadObject(zSTRING(itemChunkName+zSTRING(z)).ToChar(),newContext));
			
				if (newContext->IsCutscene())	ownerManager->InitiateCSwithContext(newContext);
				else							ownerManager->InitiateOUwithContext(newContext);
				InsertCutscene(newContext);
			
			zRELEASE(newContext);
			
			z++;
		}		
	}
	zERR_MESSAGE(5,zERR_END,"B: CS: Cutsceneplayer unarchived.");
}



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Cutscene-Debugger
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////





	// Cutscene Debugger
zCCSDebugger::~zCCSDebugger()
{		
	deb=0;
}

void zCCSPlayer::CSDB_BeginSyncBlock(zCCSSyncBlock* b)
{
	callstack.EmptyList();
	callframe = b;
	if (deb) deb->CSDB_BeginSyncBlock(b);
	else zERR_WARNING("A: CSBD: new syncblock"); 
}

void zCCSPlayer::CSDB_BeginAtomBlock(zCCSBlockBase* b)
{
	callstack.Insert(b);
	if (deb) deb->CSDB_BeginAtomBlock(b);
	else {
		zSTRING mess ("A: CSBD: ");
		mess += b->GetCommand()->MD_GetSubTypeString(b->GetCommand()->GetSubType());
		mess += zSTRING(" ");
		mess += zSTRING(callstack.GetNumInList()-1);
		zERR_MESSAGE(6,0,mess);
	}
}

void zCCSPlayer::CSDB_EndAtomBlock(zCCSBlockBase* b)
{
	int p = callstack.Search(b);
	if (p!=-1)
	{
		callstack[p]=0;
		if (deb) deb->CSDB_EndAtomBlock(b);
		else {
			zSTRING mess ("A: CSBD: Finished ");
			mess += zSTRING(p);
			zERR_MESSAGE(6,0,mess);
		}
	}
}

void zCCSPlayer::CSDB_Error(zCCSBlockBase* b, zSTRING & text)
{
	if (deb) deb->CSDB_Error(b,text);
	else {
		zSTRING mess ("A: CSBD: ERROR  : ");
		if (b) mess += b->GetCommand()->MD_GetSubTypeString(b->GetCommand()->GetSubType());
		else mess += zSTRING("- ");
		mess += zSTRING(": ")+text;
		zERR_MESSAGE(6,0,mess);
	}
}

void zCCSPlayer::CSDB_Warning(zCCSBlockBase* b, zSTRING & text)
{
	if (deb) deb->CSDB_Warning(b,text);
	else {
		zSTRING mess ("A: CSBD: WARNING: ");
		if (b) mess += b->GetCommand()->MD_GetSubTypeString(b->GetCommand()->GetSubType());
		else mess += zSTRING("- ");
		mess += zSTRING(": ")+text;
		zERR_MESSAGE(6,0,mess);
	}
}

void zCCSPlayer::CSDB_StartPlaying(zCCutscene* b)
{
	if (deb) deb->CSDB_StartPlaying(b);
}

void zCCSPlayer::CSDB_Stop(zCCutscene* b)
{
	if (deb) deb->CSDB_Stop(b);
} 

void zCCSPlayer::ResetCutscenePlayer()
{
	StopAllCutscenes();
	ownerManager->RemoveCutscenePlayer(this);	
}

int zCCSPlayer::StopAllCutscenes(zCVob* roleVob)
{
	zSTRING s("B: CS: Stopping all Cutscene ");
	if (roleVob) s+="of "+roleVob->GetVobName();
	zERR_MESSAGE(8,zERR_BEGIN,s+" ... ");
	zCCSCutsceneContext* cs=0;
	int count=0;
	for (int i=playList.GetNumInList()-1;i>=0;i--)	
	{
		cs = dynamic_cast<zCCSCutsceneContext*>(playList[i]);
		if (!roleVob || cs->GetMainRole()==roleVob) 
		{
			zERR_MESSAGE(8,0,"B: CS: Stopping Cutscene: \""+cs->GetCSName()+"\"");
			playList[i]->Stop();

			count++;
		}
	}
	zERR_MESSAGE(8,zERR_END,"");
	return count;
};

int zCCSPlayer::StopAllOutputUnits(zCVob* roleVob)
{	
	zSTRING s("B: CS: Stopping all OutputUnits ...");
	if (roleVob) s+="of "+roleVob->GetVobName();
	zERR_MESSAGE(8,zERR_BEGIN,s+" ... ");	
	zCCSCutsceneContext* cs=0;
	int count=0;
	for (int i=playList.GetNumInList()-1;i>=0;i--)	
	{
		cs = dynamic_cast<zCCSCutsceneContext*>(playList[i]);
		if (cs->IsOutputUnit()) 
		{
			if (!roleVob || cs->GetMainRole()==roleVob) 
			{
				zERR_MESSAGE(8,0,"B: CS: Stopping OutputUnit: \""+cs->GetCSName()+"\"");
				cs->Stop();			
				count++;
			}
		}
	}
	zERR_MESSAGE(8,zERR_END,"");
	return count;
};

zBOOL zCCSPlayer::IsAssigned(zSTRING & csname, zSTRING & vobname)
{    
	zBOOL found;
	int zEnd = playList.GetNumInList();
	int z = 0;
	if (zEnd==0) found = FALSE;
	else
	{
		found = FALSE;
		while (z<zEnd && !found) 
		{
			found=playList[z]->AreU(csname);
			z++;
		}
	}
	return found;
}






void zCCSPlayer::PrintListOfCutscenes(const zSTRING& parm)
{
	zerr.Separator();
	zERR_MESSAGE(1,zERR_BEGIN,"B: CS: LIST OF CUTSCENES ("+parm+")");
	zerr.Separator();

	zERR_MESSAGE(1,zERR_BEGIN,"B: CS: Number of running cutscenes: "+zSTRING(playList.GetNumInList()));
	// Liste der laufenden Cutscenes
	for (int i=0;i<playList.GetNumInList();i++)
	{
		playList[i]->PrintDebugInfo(parm);
	}	
	
	zERR_MESSAGE(1,zERR_END,"");	

/*	if (parm=="HISTORY")
	{
		zerr.Separator();

		zERR_MESSAGE(1,zERR_BEGIN,"B: CS: Number of cutscenes in history-pool: "+zSTRING(csPool.GetNumInList()));

		zSTRING s1;		
		for (int i=0; i<csPool.GetNumInList(); i++)
		{			
			csPool[i]->PrintDebugInfo();			
		}
		zERR_MESSAGE(1,zERR_END,"");	
	}
*/
	zERR_MESSAGE(1,zERR_END,"");	

	zerr.Separator();
		
};

zCCSCutsceneContext* zCCSPlayer::GetStartedCutscene(zCVob* mainrole)
{	
	for (int i=0;i<playList.GetNumInList();i++)	
	{
		if (playList[i]->GetMainRole()==mainrole) return playList[i];				
	}
	return 0;
}

zCCSCutsceneContext* zCCSPlayer::GetStartedCutscene(const zSTRING& csname)
{		
	zSTRING name=csname;name.Upper();
	for (int i=0;i<playList.GetNumInList();i++)	
	{
		if (playList[i]->AreU(name)) return playList[i];				
	}
	return 0;
}

zCCSCutsceneContext* zCCSPlayer::GetPlayingGlobalCutscene()
{
	for (int i=0;i<playList.GetNumInList();i++)	
	{
		if (playList[i]->IsGlobalCutscene() && playList[i]->IsPlaying()) return playList[i];				
	}
	return 0;
};

// Timer fuer Cutscene-Bearbeitung
zBOOL zCCSPlayer::UpdateCutscenesNow()
{	
	int numCutscenes = playList.GetNumInList();
	if (numCutscenes<=0) 
	{
		DebugResetInfoscreen();
		return FALSE;
	}

	#ifdef CS_ONE_BY_ONE
		if (timerCtr >= (250.0f / numCutscenes) ) // alle Cutscene viermal in der Sekunde
	#else
		if (timerCtr >= 250.0f) // alle Cutscene viermal in der Sekunde
	#endif
	{
		timerCtr=0;		
		return TRUE;
	}
	else 
	{
		timerCtr += ztimer.GetFrameTimeF();
		return FALSE;
	}	
};


//
// Debug-Methoden
//

void zCCSPlayer::DebugResetInfoscreen()
{
	return; 

	if (!debugInfoOnScreen || !debugInfoScreen) return;

	int yadd = debugInfoScreen->FontY();		

	debugInfoScreen->ClrPrintwin();
	debugInfoScreen->Print(10,int(yadd*0.5),"Running Cutscenes:");
	debugInfoScreen->Print(5000,int(yadd*0.5),"play(dist)");
	debugInfoScreen->Print(6500,int(yadd*0.5),"check");
	debugInfoScreen->Print(8100-debugInfoScreen->FontSize(zSTRING("bl/sec")),int(yadd*0.5),"bl/sec");	
};

void zCCSPlayer::DebugAddCutscene(int nr, zPOINT3 pos, zBOOL marked)
{	
	return; 

	zCCSCutsceneContext* cs = playList[nr];

	if (!cs || cs->IsFinished() || !debugInfoOnScreen || !debugInfoScreen) return;

	int yadd = debugInfoScreen->FontY();
	
	zSTRING rolename = "N/A";			
	zSTRING csname	 = cs->GetCSName();
	zSTRING result;	

	if (marked) debugInfoScreen->Print(10,yadd*(nr+2),"x");
		
	if (cs->GetMainRole()) rolename = cs->GetMainRole()->GetVobName();
	rolename.Lower();
	csname.Lower();
	csname.Delete(".cs");

	debugInfoScreen->Print(200,yadd*(nr+2),csname+"("+rolename+")");
	
	int distance=-1;
	if (cs->GetMainRole())
	{
		zPOINT3 mainRolePos = cs->GetMainRole()->GetPositionWorld();
		distance = int((pos - mainRolePos).LengthApprox() / 100);
	}
	
	cs->GetLastPlayResult(result);
	debugInfoScreen->Print(5000,yadd*(nr+2),result+" "+zSTRING(distance));

	cs->GetLastCheckResult(result);			
	debugInfoScreen->Print(6500,yadd*(nr+2),result);

	result = zSTRING(cs->GetActualBlockNum()) + "/" + zSTRING(int(cs->GetLastTimePoint()));
	debugInfoScreen->Print(8100-debugInfoScreen->FontSize(result),yadd*(nr+2),result);							
};


//
// Cutscenes bearbeiten ... 
//
	
void zCCSPlayer::Process()
{			
	if (!UpdateCutscenesNow()) return;

	zERR_ASSERTT(GetOwnerWorld(),"B: CS: No world set.");
	zERR_ASSERTT(GetOwnerWorld()->GetOwnerSession(),"B: CS: World has no session.");
	zERR_ASSERTT(GetOwnerWorld()->GetOwnerSession()->GetCameraVob(),"B: CS: Session knows no cameravob.");

	// Uhrzeit von der Session ermitteln
	int day, hour, minute;
	GetOwnerWorld()->GetOwnerSession()->GetTime(day,hour,minute);

	// Position der Kamera ermitteln
	zPOINT3 position = GetOwnerWorld()->GetOwnerSession()->GetCameraVob()->GetPositionWorld();
	
	ProcessList(position,day,hour,minute);
}
	

//
// Cutscenes bearbeiten ...
// Liefert true, wenn die Cutscene gestartet/fortgesetzt oder beendet/unterbrochen wurde
// Es wird immer nur maximal eine Cutscene bearbeitet. Beim nächsten Aufruf ist dann 
// die nächste dran u.s.w (Lastverteilung über alle Frames)
//
void zCCSPlayer::ProcessList(const zPOINT3& pos, int day, int hour, int minute)
{			
	zBOOL reset_occured = FALSE;
	if (lastProcessDay!=day)
	{
		ownerManager->PoolResetByDay();
		lastProcessDay = day;
		reset_occured = TRUE;
	}
	if (lastProcessHour!=hour)
	{
		ownerManager->PoolResetByHour();
		lastProcessHour = hour;
		reset_occured = TRUE;
	}

	if (reset_occured) 
	{
		// alle Cutscenes, die jetzt nicht spielen dürfen, 
		// (weil sie in ihrer Zeitspanne of genug liefen; deaktivierte sind nicht in dieser Liste)
		// könnten jetzt doch die Möglichkeit dazu haben
		zCList<zCCSCutsceneContext>* localContextItem = playList.GetNextInList();
		while (localContextItem)
		{
			zCCSCutsceneContext* localContext = localContextItem->GetData();
			if (
					!(localContext->allowedToPlay) && 
					ownerManager->PoolAllowedToStart(localContext->GetCSName())==1
				) 
			{
				localContext->allowedToPlay = TRUE;
			}
					
			localContextItem = localContextItem->GetNextInList();
		}
	}

	//
	// Die Variante, bei der immer nur eine Cutscene abgearbeitet wird
	//
	#ifdef CS_ONE_BY_ONE

		if (!processingListItem)
		{
			processingListItem = playList.GetNextInList();	// Erstes Daten-Element der Liste		
			if (!processingListItem) return; // Liste ist leer
			processingCtr = 0;		
		};		
			
		processingCtr++;

		// Cutscene ermitteln 
		zCCSCutsceneContext* cutscene = processingListItem->GetData();

		// ListItem für nächsten Aufruf ermitteln
		// Wichtig: Direkt nach dem Ermitteln der Cutscene, da das aktuelle listItem
		// beim Beenden der Cutscene ungueltig werden koennte!
		processingListItem = processingListItem->GetNextInList();	
		
		cutscene->AddRef();

			// Cutscene bearbeiten
			if (
				cutscene && 
				cutscene->allowedToPlay &&
				!cutscene->IsFinished()
				)
			{							
				ProcessCutscene(cutscene, pos);												
			}

			// Debugg-Output aller laufenden Cutscenes
			if (debugInfoOnScreen) 
			{
				DebugResetInfoscreen();			
				for (int i=0;i<playList.GetNumInList();i++)
				{				
					DebugAddCutscene(i, pos, playList[i]==cutscene);
				}
			}

		zRELEASE(cutscene);		

	//
	// Die Variante, bei der immer alle Cutscenes abgearbeitet werden
	//
	
	#else

		processingListItem = playList.GetNextInList();	// Erstes Daten-Element der Liste		
		processingCtr = 0;				

		while (processingListItem)
		{
			processingCtr++;

			// Cutscene ermitteln 
			zCCSCutsceneContext* cutscene = processingListItem->GetData();

			// ListItem für nächsten Aufruf ermitteln
			// Wichtig: Direkt nach dem Ermitteln der Cutscene, da das aktuelle listItem
			// beim Beenden der Cutscene ungueltig werden koennte!
			processingListItem = processingListItem->GetNextInList();	
			
			cutscene->AddRef();

				// Cutscene bearbeiten
				if (
					cutscene && 
					cutscene->allowedToPlay &&
					!cutscene->IsFinished()
					)
				{							
					ProcessCutscene(cutscene, pos);												
				}

				// Debugg-Output aller laufenden Cutscenes
				if (debugInfoOnScreen) 
				{
					DebugResetInfoscreen();			
					for (int i=0;i<playList.GetNumInList();i++)
					{				
						DebugAddCutscene(i, pos, playList[i]==cutscene);
					}
				}

			zRELEASE(cutscene);		
		}
	#endif
}

void zCCSPlayer::ProcessCutscene(zCCSCutsceneContext* cs, const zPOINT3& pos)
{
	cs->Play(pos);
	
	zCCSCutsceneContext::zTCSPlayResult playResult = cs->lastPlayResult;
	
	switch (playResult)
	{
	case zCCSCutsceneContext::CS_PLAY_STARTEDPLAYING:
		{
			ownerManager->PoolCountStart(cs->GetCSName());
			break;
		} 
	case zCCSCutsceneContext::CS_PLAY_STOPPED:
		{
			ownerManager->PoolCountStop(cs->GetCSName());
			break;
		} 
	};
};

void zCCSPlayer::ToggleDebugInfo() 
{ 
	debugInfoOnScreen = !debugInfoOnScreen; 
	if (!debugInfoScreen)
	{
		debugInfoScreen = zNEW(zCView(0,500,8192,8000));
	};
	if (debugInfoOnScreen) 
	{
		screen->InsertItem(debugInfoScreen);	
		DebugResetInfoscreen();
	}
	else
	{
		screen->RemoveItem(debugInfoScreen);
	};
};


