/******************************************************************************** 
 
     $Workfile:: oMission.h           $                $Date:: 8.01.01 14:55    $
     $Revision:: 12                   $             $Modtime:: 8.01.01 14:48    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oMission.h $
 * 
 * 12    8.01.01 14:55 Wohlers
 * 
 * 11    1.12.00 3:07 Speckels
 * 
 * 10    29/09/00 16:31 Luesebrink
 * 
 * 9     8.09.00 15:47 Herget
 * 
 * 8     29.08.00 12:39 Wohlers
 * 
 * 7     28.08.00 12:50 Keskenti
 * 
 * 6     23.08.00 13:30 Keskenti
 * 
 * 5     14.08.00 16:46 Herget
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

#ifndef __OMISSION_H__
#define __OMISSION_H__

#include "zVob.h"
#include "oMenu_Status.h"

class oCNpc;

// Constants for Mission-Status
const int MIS_NOMISSION				= -1;		// Keine Mission
const int MIS_NOTINVOLVED			= 0;		// Frei
const int MIS_OFFERED				= 1;		// angeboten
const int MIS_REFUSED				= 2;		// abgelehnt
const int MIS_RUNNING				= 3;		// laeuft
const int MIS_DONE					= 4;		// erledigt
const int MIS_DONELATE				= 5;		// Spaet erledigt
const int MIS_CANCELED				= 6;		// Abgebrochen
const int MIS_FAILED				= 7;		// Gescheitert

class oCMission;

class oCMissionManager {
public:
	oCMissionManager					();
	~oCMissionManager					();
	
	oCMission*	GetAvailableMission		(oCNpc* npc, oCNpc* pc, zBOOL important);
	int			GetStatus				(oCNpc* pc, int missionNr);
	void		SetStatus				(oCNpc* pc, int missionNr, int state);
	zBOOL		CancelMission			(oCNpc* pc, int missionNr);
	oCMission*	GetMission				(int instancenr);
	oCMission*	OfferThisMission		(oCNpc* npc, oCNpc* pc, int missionNr);

	void		CreateMissionInfoList	(oCNpc* player,zCArray<oCMission*> &list);
	void		CreateAllMissions		();

	int			GetNumMissions			() { return missionList.GetNumInList(); };

	void		ClearMissions			();

	//
	//	CODECHANGE [ROMAN]
	//
	BOOL		TestNextMission			();				
	//
	//	CODECHANGE [ROMAN] END
	//

	virtual void		Archive			(zCArchiver &arc);
	virtual void		Unarchive		(zCArchiver &arc);

private:
	
	zCArraySort <oCMission*>			missionList;

	static int	SortMissions			(const void* ele1,const void* ele2);
};

class oCMission {

public :
	oCMission							(int nr);
	oCMission	(){};
	~oCMission							();

	zSTRING		GetName					() { return name; };
	zSTRING		GetDesription			() { return description; };

	// CODECHANGE [STEFAN]
	void		AddEntry				(const zSTRING &text);
	void		SetDeleted				() { deleted = TRUE; };
	zBOOL		IsDeleted				() { return deleted; };
	// CODECHANGE [STEFAN] END

	void		SetCurrentUser			(oCNpc* npc, oCNpc* player);	// Who's working with this version ?
	void		GetCurrentUser			(oCNpc* &npc, oCNpc* &player);	// Who's working with this version ?
	zBOOL		IsAvailable				();
	int			GetStatus				();
	void		SetStatus				(int state);
	int			GetInstance				()	{ return instance;	};
	zBOOL		IsImportant				()  { return important; };

	zBOOL		IsRunning				() { return GetStatus()==MIS_RUNNING; };
	zBOOL		WasSolved				() { return (GetStatus()==MIS_DONELATE) || (GetStatus()==MIS_DONE); };
	zBOOL		WasFailed				() { return (GetStatus()==MIS_CANCELED) || (GetStatus()==MIS_FAILED); };	

	zBOOL		OfferConditions			();				// Criteria fulfilled ? 
	void		Offer					();				// Offer Mission

	zBOOL		SuccessConditions		();				// 
	void		Success					();				// 
	
	zBOOL		FailureConditions		();				// 
	void		Failure					();				// 
	
	zBOOL		ObsoleteConditions		();				// 
	void		Obsolete				();				// 

	void		Running					();				// 

	zBOOL		CheckMission			();				// Mission success / running etc.
	zBOOL		OnTime					();				// Mission still on time ?

	virtual void		Archive			(zCArchiver &arc);
	virtual oCMission*	Unarchive		(zCArchiver &arc);

private :
	
	typedef struct {
		zTVobID	vobID;		
		int		status;
		zREAL	startTime;
	} TMisStatus;

	zREAL		GetStartTime	();
	void		SetStartTime	(zREAL startTime);
	TMisStatus*	GetStatusInfo	();

	struct {
		zSTRING		name;
		zSTRING		description;
		int			duration;			// in Stunden
		zBOOL		important;			// Multiplayer-fähig

		// Functions
		int			offerConditions;	// Auftragsvergabebedingung
		int			offerFunc;			// Auftragsvergabeblock
		
		int			successConditions;	// Auftragslösungsbedingung
		int			successFunc;		// Auftragslösungsblock
		
		int			failureConditions;	// Auftragsabbruchbedingung
		int			failureFunc;		// Auftragsabbruchblock

		int			obsoleteConditions;	// Obseletebedingung
		int			obsoleteFunc;		// Obsoleteblock

		int			runningFunc;		// MissionRunning
	};
	
	int						instance;	// Instance-Number
	oCNpc*					npc;		// Mission-owner
	oCNpc*					player;		// Current Player
	zTVobID					curID;		// Who uses this mission ?
	zBOOL					available;	// Mission still available
	zCArray <TMisStatus*>	statusList;	// Mission used by which Players ?	
	TMisStatus*				status;		// Current status-pointer

	// CODECHANGE [STEFAN]
	zBOOL					deleted;
	// CODECHANGE [STEFAN] END
};

extern oCMissionManager misMan;

















/*
class oCMission {

public:

	oCMission		();
	~oCMission		();

	void			SetOther			(oCNpc* npc);
	zBOOL			CanBeOffered		();
	void			Offer				();
	void			Acknowledged		();
	void			Refused				();
	zBOOL			IsRunning			();
	void			CheckRunningMission	();
	int				GetStatus			();

private:
	
	struct {
		
		zSTRING	name;						// Name des Auftrages
		zBOOL	global;						// Globale (>0) oder persoenliche (==0) Mission
		int		id;							// Missionsnummer
		int		duration;					// Max. Dauer in Tageszeiten
		
		// Bedingung zur Vergabe
		int		condition;
		int		condition_var;

		// Auftrag erfüllt ?
		int		success;
		int		success_var;
		
		// Anbieten
		int		offer_string;

		// Auftrag angenommen.
		int		acknowledge;
		int		acknowledge_var;
		int		acknowledge_string;
		
		// Auftrag abgelehnt
		int		refuse;
		int		refuse_var;					// Nicht nötig
		int		refuse_string;

		// Running ontime
		int		running_ontime;
		int		running_ontime_var;
		int		running_ontime_string;

		// Running late
		int		running_late;
		int		running_late_var;
		int		running_late_string;

		// Auftrag erfüllt -> Konsequenzen
		int		done;
		int		done_var;
		int		done_string;

		int		done2;
		int		done2_var;
		int		done2_string;

		int		done3;
		int		done3_var;
		int		done3_string;	
	
		int		end;
	};

	// Status für jeden möglichen Spieler merken
//	zCList <TMisStatus> misStatus;

	oCNpc*		npc;				// The 
	oCNpc*		player;				// The Player
	zBOOL		available;			// Mission still available
	int			npcId;				// What Player ?
	int			status;				// How is the mission going ?
	int			startTime;			// Starttime of Mission

	zBOOL		ConditionSuccess	();
	zBOOL		Success				();
	zBOOL		IsOnTime			();
	void		StartOutput			(oCNpc* npc, const zSTRING& name);

/*	int instanz;
	oCMission *next;							// Pointer to next Mission in list

	oCNpc *player,*npc;							// Spieler und Auftragsgeber

	BOOL available;								// Kann Mission noch vergeben werden ?
	int status [16];							// Missionstatus der Player
	int npcid;									// Auftraggeber id
	__int64 starttime[16];							// Startzeit der Mission fuer jeden Player

	// Functions
	oCMission			(oCNpc *pl,oCNpc *np,int nr);

	BOOL Valid			(int npcnr);
	BOOL OnTime			();
	int  Status			();
	BOOL Conditions		();
	BOOL Criteria		();
	void Offer			();
	void Acknowledge	();
	void Refuse			();
	void Done			();
	void Abort			();
	void Running		();

	static zSTRING GetName			( int nr );
	static void CancelMission		( int nr );
	static BOOL HasCompletedMission	( int nr );
	static BOOL HasFailedMission	( int nr );

);

void Mis_Test		();

oCMission *Mis_Check(oCNpc *play, oCNpc *np);
*/
#endif