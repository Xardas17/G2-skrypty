/******************************************************************************** 
 
     $Workfile:: oMission.cpp         $                $Date:: 11.01.01 19:22   $
     $Revision:: 23                   $             $Modtime:: 11.01.01 19:21   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oMission.cpp $
 * 
 * 23    11.01.01 19:22 Speckels
 * 
 * 22    8.01.01 14:55 Wohlers
 * 
 * 21    1.12.00 3:07 Speckels
 * 
 * 20    26.10.00 16:18 Moos
 * 
 * 19    26.10.00 14:04 Moos
 * 
 * 18    25.10.00 10:01 Moos
 * 
 * 17    20.10.00 16:41 Wohlers
 * 
 * 16    11/10/00 16:04 Luesebrink
 * 
 * 15    5/10/00 13:22 Luesebrink
 * 
 * 14    5.10.00 13:16 Wohlers
 * 
 * 13    29/09/00 16:31 Luesebrink
 * 
 * 12    29.08.00 12:39 Wohlers
 * 
 * 11    28.08.00 12:50 Keskenti
 * 
 * 10    23.08.00 13:30 Keskenti
 * 
 * 9     18.08.00 15:44 Wohlers
 * 
 * 8     14.08.00 16:46 Herget
 * 
 * 7     2.08.00 14:25 Wohlers
 * 
 * 6     21.07.00 15:34 Wohlers
 * 
 * 5     19.07.00 20:05 Wohlers
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 10    29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 9     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 8     8.02.00 18:01 Wohlers
 * Debug-Methode CreateAllMissions
 * 
 * 7     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 5     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 4     20.12.99 17:44 Wohlers
 * uSrc V0.70
 * AI_UseItem / AniComb TakeItem etc...
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zDisk.h"
#include "zview.h"
#include "oMission.h"
#include "oInfo.h"
#include "oWorld.h"
#include "oNpc.h"
#include "oGame.h"

#include "zParser.h"

oCMissionManager misMan;

oCMissionManager :: oCMissionManager()
{
	missionList.SetCompare(SortMissions);
}

oCMissionManager :: ~oCMissionManager()
{
	ClearMissions();
}

void oCMissionManager :: ClearMissions()
{
	int i = 0, c = missionList.GetNumInList();
	while (i<c) {
		delete (missionList[i]);
		i++;
	}
	missionList.EmptyList();
};

int oCMissionManager :: SortMissions (const void* ele1,const void* ele2)
{
	oCMission* mis1 = *((oCMission**)ele1);
	oCMission* mis2 = *((oCMission**)ele2);

	if (mis1->GetInstance() < mis2->GetInstance()) 
		return -1;
	else
		return 1;
}

oCMission* oCMissionManager :: GetMission ( int instancenr )
{
	if (missionList.IsEmpty()) return NULL;

	// Binary Search	
	// return value = found index, -1=not found
	int index		= 0;
	int ind_low		= 0;
	int ind_high	= missionList.GetNumInList()-1;
	int foundInstance;

	do {

		index			= ind_low + (ind_high - ind_low) / 2;
		foundInstance	= missionList[index] -> GetInstance();
		
		if (foundInstance < instancenr) ind_low		= index + 1;	else
		if (foundInstance > instancenr) ind_high	= index - 1;	else
										return missionList[index];

	} while (ind_low <= ind_high);		
			
	return NULL;
}

void oCMissionManager :: CreateAllMissions()
{
	missionList.DeleteList();
	// Getting the class Index
	zSTRING misClass("C_MISSION");
	int cindex = parser.GetIndex(misClass);
	if (cindex<0) return;
	// Create all Infos
	int	pos	= 0;
	while (pos>=0) {
		pos	= parser.GetInstance(cindex,pos+1);
		if (pos>=0) {
			// Create Info
			oCMission* mission = zNEW( oCMission(pos) );
			mission->SetCurrentUser	(NULL,oCNpc::player);
			//if ((zRand() & 1) == 0) mission->SetStatus		(MIS_DONE);
			//else					
			mission->SetStatus			(MIS_RUNNING);
			missionList.InsertSort		(mission);
		}
	};
}

oCMission* oCMissionManager :: OfferThisMission(oCNpc* npc, oCNpc* pc, int missionNr)
{
	oCMission* mission = GetMission(missionNr);
	// Mission gibt's noch nicht -> Erzeugen
	if (!mission) {
		mission  = zNEW( oCMission(missionNr) );
		missionList.InsertSort(mission);
	}
	// Hier checken, ob Bedingungen laufen...
	mission->SetCurrentUser(npc,pc);
	int status = mission->GetStatus();
	if ((status==MIS_NOTINVOLVED) && mission->IsAvailable() && mission->OfferConditions()) {
		mission->Offer();

	} else if ((status==MIS_RUNNING) || (status==MIS_OFFERED)) {
		mission->CheckMission();		
	}
	return NULL;
}

oCMission* oCMissionManager :: GetAvailableMission (oCNpc* npc, oCNpc* pc, zBOOL important)
// Läuft eine Mission zwischen NSC und Spieler ?
// a) Spieler noch nicht involviert + Kriterien erfüllt
// b) Spieler involviert + Mission läuft
{
	oCMission* mission;
	// Checke Liste der anzubietenden Missionen
	for (int i=0; i<NPC_MIS_MAX; i++) {
		int nr	= npc -> GetMission(i);
		if (nr>0) {
			// Mission bereits in Liste ?
			mission	= NULL;
			mission	= GetMission(nr);
			// Mission gibt's noch nicht -> Erzeugen
			if (!mission) {
				mission  = zNEW( oCMission(nr) );
				missionList.InsertSort(mission);
			}
			
			// Nur wichtige Missionen berücksichtigen, fall wichtig-Flag gesetzt
			if (important && !mission->IsImportant()) continue; 
			
			// Hier checken, ob Bedingungen laufen...
			mission->SetCurrentUser(npc,pc);
			int status = mission->GetStatus();
			if ((status==MIS_NOTINVOLVED) && mission->IsAvailable() && mission->OfferConditions()) {
				return mission;
			} else if ((status==MIS_RUNNING) || (status==MIS_OFFERED)) {
				return mission;
			}
		}
	}
	return NULL;
}

int	oCMissionManager :: GetStatus (oCNpc* pc, int missionNr)
{
	oCMission* mission = GetMission(missionNr);
	if (!mission) return MIS_NOMISSION;

	// Safe old values -> safety
	oCNpc* old1, *old2;
	mission->GetCurrentUser(old1,old2);
	mission->SetCurrentUser(NULL,pc);
	int status = mission->GetStatus();
	mission->SetCurrentUser(old1,old2);
	return status;
}

void oCMissionManager :: SetStatus	(oCNpc* pc, int missionNr, int state)
{
	oCMission* mission = GetMission(missionNr);
	if (!mission) {
		zERR_WARNING("U: MIS: Mission SetStatus failed ");
		return;
	}
	// Safe old values -> safety
	oCNpc* old1, *old2;
	mission->GetCurrentUser	(old1,old2);
	mission->SetCurrentUser	(NULL,pc);
	mission->SetStatus		(state);
	mission->SetCurrentUser	(old1,old2);
}

zBOOL oCMissionManager :: CancelMission (oCNpc* pc, int missionNr)
{
	oCMission* mission = GetMission(missionNr);
	if (!mission) return FALSE;
	// Safe old values -> safety
	oCNpc* old1, *old2;
	mission->GetCurrentUser(old1,old2);
	mission->SetCurrentUser(NULL,pc);
	int status = mission->GetStatus();
	mission->SetCurrentUser(old1,old2);
	
	if ((status==MIS_RUNNING) || (status==MIS_OFFERED)) {
		mission->SetStatus(MIS_CANCELED);
		return TRUE;
	}
	return FALSE;
}

void oCMissionManager :: CreateMissionInfoList	(oCNpc* player, zCArray<oCMission*> &list)
{
	int					status;
	oCNpc*				old1,*old2;
	oCMission*			mission = NULL;	
	for (int i=0; i<missionList.GetNumInList(); i++) 
	{
		mission =  missionList[i];		
		mission -> GetCurrentUser		(old1,old2);
		mission -> SetCurrentUser		(NULL,player);
		status  =  mission -> GetStatus	();
		mission -> SetCurrentUser		(old1,old2);
		if (status != MIS_NOTINVOLVED) list.Insert(mission);		
	}
}

//
//	CODECHANGE [ROMAN]
//

zBOOL oCMissionManager :: TestNextMission( void )
{		
	return TRUE;

/*	oCMission* pMission;

	missionList.DeleteList();

	pMission = zNEW( oCMission( parser.GetIndex("Mis_1_OC_RyansKey") ) );
	missionList.InsertSort( pMission );

	pMission = zNEW( oCMission( parser.GetIndex("Mis_1_OC_BringSword") ) );
	missionList.InsertSort( pMission );
	
	pMission = NULL;
	pMission = GetMission(parser.GetIndex("Mis_1_OC_BringSword"));

	return FALSE;
	
	for (int i = 0; i<4; i++) {
		pMission = GetMission(parser.GetIndex("Mis_1_OC_RyansKey"));
		if (!pMission) {
			pMission = zNEW( oCMission( parser.GetIndex("Mis_1_OC_RyansKey") ) );
			missionList.InsertSort( pMission );
		}
	}
*/
//	return FALSE;

	//
	//	CLEAR ALL MISSIONS
	//
	this->missionList.DeleteList();

	//
	//	GET TEST MISSIONS
	//
	int nInstance[4];
	nInstance[0] = parser.GetIndex( "Mis_1_OC_RyansKey"		 );
	nInstance[1] = parser.GetIndex( "Mis_1_OC_BringSword"	 );
	nInstance[2] = parser.GetIndex( "Mis_1_OC_MiscreditRyan" );
	nInstance[3] = parser.GetIndex( "Mis_1_OC_BringList"	 );

	//
	//	INSERT MISSIONS WHILE TESTING INSERTION
	//
	zBOOL bResult = TRUE;
	for ( int nMission = 0; nMission < 4; nMission++ )
	{
		oCMission* pMission  = zNEW( oCMission( nInstance[ nMission ] ) );
		missionList.InsertSort( pMission );
		bResult = ( pMission == this->GetMission( nInstance[ nMission ] ) );
		if ( ! bResult ) zERR_MESSAGE( 5,0,"U: oCMissionManager: TestNextMission() - Mission #" +zSTRING(nMission)+ " not found !!!" );
	}
	zERR_MESSAGE( 5,0,"U: oCMissionManager: TestNextMission1() - All Missions OK!" );

	int found = 0;
	for ( nMission = 0; nMission < 4; nMission++ )
	{
//		oCMission* pMission  = zNEW( oCMission( nInstance[ nMission ] ) );
//		missionList.InsertSort( pMission );
		if (GetMission( nInstance[ nMission ] ) ) found++;
	}
	if (found==4) 
		zERR_MESSAGE( 5,0,"U: oCMissionManager: TestNextMission2() - All Missions OK!" );

	return bResult;
}

void oCMissionManager::Archive( zCArchiver &arc )
{
	arc.WriteInt( "NumOfEntries", missionList.GetNum() );
	for( int i = 0; i < missionList.GetNum(); i++ )
	{
		missionList[i]->Archive( arc );
	}
}

void oCMissionManager::Unarchive( zCArchiver &arc )
{
	int tempNum = 0;
	arc.ReadInt( "NumOfEntries", tempNum );
	missionList.EmptyList();
//for masters
//	while( tempNum-- ) missionList.Insert( (zNEW(oCMission))->Unarchive(arc) );
//for beginners
	oCMission *tempObj = NULL;
	for( int i = 0; i < tempNum; i++ )
	{
		tempObj = zNEW( oCMission );
		tempObj->Unarchive(arc);
		missionList.Insert( tempObj );
	}
}

//
//	CODECHANGE [ROMAN] END
//

// **************************************************************************************
// Missionsklasse
// **************************************************************************************

oCMission :: oCMission (int nr)
{
	duration			= 0;		// in Stunden
	important			= FALSE;	// wichtiger Auftrag
	offerConditions		= -1;		// Auftragsvergabebedingung
	offerFunc			= -1;		// Auftragsvergabeblock
	successConditions	= -1;		// Auftragslösungsbedingung
	successFunc			= -1;		// Auftragslösungsblock
	failureConditions	= -1;		// Auftragsabbruchbedingung
	failureFunc			= -1;		// Auftragsabbruchblock
	obsoleteConditions	= -1;		// Obseletebedingung
	obsoleteFunc		= -1;		// Obsoleteblock
	runningFunc			= -1;		// MissionRunning
	
	instance			= nr;		// Instance-Number
	npc					= NULL;		// Mission-owner
	player				= NULL;		// Current Player
	curID				= 0;		// Who uses this mission ?
	available			= TRUE;		// Mission still available
	status				= NULL;		// Current status-pointer
	
	// CODECHANGE [STEFAN]
	deleted				= FALSE;
	// CODECHANGE [STEFAN] END

	parser.CreateInstance	(nr,&name);
	statusList.AllocAbs		(1);
}

oCMission :: ~oCMission ()
{
	int i = 0, c = statusList.GetNumInList();
	while (i<c) {
		delete (statusList[i]);
		i++;
	}
	statusList.EmptyList();

	npc		= NULL;
	player	= NULL;
	status	= NULL;
}

void oCMission :: AddEntry(const zSTRING &text) 
{ 
	description += "<hr>" + text; 
};

void oCMission :: SetCurrentUser (oCNpc* npc, oCNpc* player)
{
	this -> npc			= npc;
	this -> player		= player;
	if (player) curID	= player->GetVobID();
	status				= GetStatusInfo();
};

void oCMission :: GetCurrentUser (oCNpc* &npc, oCNpc* &player)
{
	npc		= this->npc;
	player	= this->player;
};

oCMission::TMisStatus* oCMission :: GetStatusInfo ()
// Überprüfe den Missionstatus für diesen NSC
{
	int i = 0, c = statusList.GetNumInList();
	while (i<c) {
		if (statusList[i]->vobID == curID) return statusList[i];
		i++;
	}
	// Was, gibt's nicht ? Skandal, dann neuen machen
	TMisStatus*	stat = zNEW( TMisStatus );
	stat->vobID		 = curID;
	stat->status	 = MIS_NOTINVOLVED;
	stat->startTime	 = 0;

	statusList.Insert(stat);
	
	return stat;
}

zREAL oCMission :: GetStartTime()
{
	if (status) return status->startTime;
	else		return -1;	
}

void oCMission :: SetStartTime	(zREAL startTime)
{
	if (status) status->startTime = startTime;
}

zBOOL oCMission :: CheckMission()
// State == MIS_RUNNING
{
	if (SuccessConditions()) {
		// *************
		// He did it !!
		// *************
		Success();
		return TRUE;
	}
	if (FailureConditions()) {
		// **********************
		// Mission abgebrochen ?
		// **********************
		Failure();
		return TRUE;
	}
	if (ObsoleteConditions()) {
		// **********************
		// Mission abgebrochen ?
		// **********************
		Obsolete();
		return TRUE;
	} 
	if (GetStatus()==MIS_RUNNING) {
		// **********************
		// Mission läuft ?
		// **********************
		Running();
		return TRUE;
	}
	return FALSE;
}

int oCMission :: IsAvailable()
// Kann die Mission grundsätzlich noch vergeben werden ?
{
	return available;
}

// ***************************************************************************************
// Skriptfunktionen aufrufen
// ***************************************************************************************

zBOOL oCMission :: OfferConditions()
// Liefert TRUE, wenn die Kriterien zur Auftragsvergabe erfuellt worden sind.
{	
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	return( *(BOOL *)parser.CallFunc(offerConditions) );
}

void oCMission :: Offer()
{
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	parser.CallFunc		(offerFunc);
}

zBOOL oCMission :: SuccessConditions()
// Liefert TRUE, wenn die Kriterien zur Auftragsvergabe erfuellt worden sind.
{	
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	return( *(BOOL *)parser.CallFunc(successConditions) );
}

void oCMission :: Success()
{
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	parser.CallFunc		(successFunc);
}

zBOOL oCMission :: FailureConditions()
// Liefert TRUE, wenn die Kriterien zum Auftragsabbruch erfuellt worden sind.
{	
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	return( *(BOOL *)parser.CallFunc(failureConditions) );
}

void oCMission :: Failure()
{
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	parser.CallFunc		(failureFunc);
}

zBOOL oCMission :: ObsoleteConditions()
// Liefert TRUE, wenn die Kriterien zur Auftragsabbruch erfuellt worden sind.
{	
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	return( *(BOOL *)parser.CallFunc(obsoleteConditions) );
}

void oCMission :: Obsolete()
{
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	parser.CallFunc		(obsoleteFunc);
}

void oCMission :: Running()
{
	parser.SetInstance	(zSTRING("SELF")	,npc);
	parser.SetInstance	(zSTRING("OTHER")	,player);	
	parser.CallFunc		(runningFunc);
}

// *****************************************************************************************
// Status-Änderungen
// *****************************************************************************************

int oCMission :: GetStatus()
// Überprüfe den Missionstatus für diesen NSC
{
	if (status) return status->status;
	else		return MIS_NOMISSION;
}

void oCMission :: SetStatus (int state)
{
	if (!status) {
		zerr.Fault("U:MISSION:Used Mis_SetState without active Mission.");
		return;
	}

	status->status = state;
	
	if (state == MIS_RUNNING) {
		// Zeit ab jetzt
		SetStartTime(ogame->GetWorldTimer()->GetFullTime());		
	}
}

zBOOL oCMission :: OnTime()
// Liegt Mission noch in der Zeit
{
	// unendliche Missionen haben die Duration von Null
	if (duration>0) {
		zREAL fulltime = GetStartTime() + duration * WLD_TICKSPERHOUR;
		return (ogame->GetWorldTimer()->GetFullTime() <= fulltime); 
	} 
	return TRUE;
}

void oCMission::Archive( zCArchiver &arc )
{
    int i;

	if( !arc.InSaveGame() ) return;

	zCPar_Symbol *symbol = parser.GetSymbol( instance );
	arc.WriteString	("name"		,symbol->name );
	arc.WriteInt	("ID"		,curID );
	arc.WriteBool	("Av"		,available );
	
	arc.WriteInt	("NumInList",statusList.GetNum() );

    int current_status=-1;

	for(i = 0; i < statusList.GetNum(); i ++ )
	{
		arc.WriteInt	( "VobIDL"		, statusList[i]->vobID );
		arc.WriteInt	( "StatusL"		, statusList[i]->status );
		arc.WriteFloat	( "startTimeL"	, statusList[i]->startTime );

        if (statusList[i] == status)
            current_status = i;
	}

    zERR_ASSERT(current_status >= 0 || !status);
    arc.WriteInt("StatusIndex", current_status);     // [Moos] Spart Speicherplatz und ist sicherer

  /*  arc.WriteObject("Player", player);
    arc.WriteObject("npc"   , npc);
    */

//	arc.WriteFloat	( "VobID"		, status->startTime );
//	arc.WriteInt	( "Status"		, status->status );
//	arc.WriteInt	( "startTime"	, status->vobID  );
}

oCMission* oCMission::Unarchive( zCArchiver &arc )
{
    player = npc = NULL;

	if( !arc.InSaveGame() ) return NULL;

	statusList.EmptyList();

	arc.ReadString( "name", name );
	instance = parser.GetIndex(name);
	parser.CreateInstance	(instance,&name);

	arc.ReadInt	( "ID", (int&)curID );
	arc.ReadBool( "Av", available );

	int tempNum;
	arc.ReadInt	( "NumInList", tempNum );
	TMisStatus *tempMis;
	for( int i = 0; i < tempNum; i ++ )
	{
		tempMis = zNEW(TMisStatus);

		arc.ReadInt		("VobIDL"		, (int&)tempMis->vobID );
		arc.ReadInt		("StatusL"		, tempMis->status );
		arc.ReadFloat	("startTimeL"	, tempMis->startTime );

		statusList.Insert( tempMis );
	}

//	tempMis = zNEW(TMisStatus);

    int current_status;
    arc.ReadInt("StatusIndex", current_status);        // [Moos] analogon zu Änderungen oben.
    if (current_status >= 0)
        status = statusList[current_status];
    else
        status = NULL;


/*
    player = dynamic_cast<oCNpc *>(arc.ReadObject("Player", player));
    npc    = dynamic_cast<oCNpc *>(arc.ReadObject("npc"   , npc));

    if (npc)    npc   ->Release();
    if (player) player->Release();
*/
//	arc.ReadFloat( "VobID", tempMis->startTime );
//	arc.ReadInt ( "Status", tempMis->status );
//	arc.ReadInt ( "startTime", (int&)tempMis->vobID  );


	return this;
}