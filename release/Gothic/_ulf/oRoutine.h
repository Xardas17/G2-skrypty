/******************************************************************************** 
 
     $Workfile:: oRoutine.h           $                $Date:: 16.01.01 18:04   $
     $Revision:: 9                    $             $Modtime:: 16.01.01 15:29   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oRoutine.h $
 * 
 * 9     16.01.01 18:04 Wohlers
 * 
 * 8     18.10.00 0:51 Wohlers
 * 
 * 7     16.10.00 21:28 Wohlers
 * 
 * 6     4.08.00 13:53 Wohlers
 * 
 * 5     12.07.00 14:52 Wohlers
 * Overlay-TA Bugfix
 * 
 * 4     22.05.00 18:43 Wohlers
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
 * 7     18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 6     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __OROUTINE__
#define __OROUTINE__

#include "zString.h"
#include "zList.h"
#include "zVob.h"

class zCVob;
class zCWorld;
class oCNpc;


class oCRtnCutscene {
public:
				oCRtnCutscene	();
	virtual		~oCRtnCutscene	();

	void		ResetPlayState	();

public:
	// Cutscene during a Routine
	oCNpc*		npc;
	zSTRING		csName;
	zSTRING		roleName;
	zBOOL		ignorePlayState;
	zBOOL		active;
};

class oCRtnEntry {
public:
	oCRtnEntry					();
	oCRtnEntry					(int hour1,int min1,int hour2,int min2,int func, const zSTRING& wp, int i=-1); 
	~oCRtnEntry					();

	void			SetTime		(int  h1, int  m1, int  h2, int  m2);
	void			GetTime		(int &h1, int &m1, int &h2, int &m2);
	int				GetState	();
	zSTRING			GetWaypoint	();
	oCNpc*			GetNpc		()			{ return npc; };
	void			SetNpc		(oCNpc* n)	{ npc = n; };

public:
	int				hour1,min1;
	int				hour2,min2;
	int				f_script;
	zSTRING			wpname;
	int				instance;
	zCVob*			poi;
	oCNpc*			npc;
	// Cutscene dran gekoppelt ?
	oCRtnCutscene*	cutscene;
	zBOOL			overlay;		// Overlayed Daily Routine
};

class oCRtnManager {
public :
	oCRtnManager					();
	~oCRtnManager					();

	// Init 
	void		SetWorld			(zCWorld* w);
	
	// Routine List Management
	void		Insert				(oCNpc* npc, oCRtnEntry* rtn);
	void		RemoveEntry			(oCRtnEntry* entry);
	void		RemoveRoutine		(oCNpc* npc);
	void		RemoveOverlay		(oCNpc* npc);
	void		CheckConsistency	(oCNpc* npc);

	void		RestartRoutines		();					// Restart all Routines.
	void		UpdateSingleRoutine	(oCNpc* npc);		// Update a single Routine (Overlay-TA)
	void		UpdateGlobalRoutineEntry();
	
	void		CheckRoutines		();					
	zBOOL		FindRoutine			(oCNpc* npc, oCRtnEntry* &rtnNow, oCRtnEntry* &rtnBefore);
	
	// WayBox Berechnung
	void		InitWayBoxes		();
	void		CreateWayBoxes		(oCNpc* npc);
	zBOOL		CollidesWithWayBox	(zTBBox3D& bbox, zCList<oCNpc>& foundNpcList);
	void		RemoveWayBoxes		(oCNpc* npc);
	
	// Interpolation
	void		SetDailyRoutinePos	(zBOOL onlyRoutineDriven = FALSE);
	zVEC3		GetRoutinePos		(oCNpc* npc);

	// Debug
	void		DrawWayBoxes		();
	int			GetNumOfWayBoxes	();
	void		ShowRoutine			(int x, int y, oCNpc* npc);
	zSTRING		GetRoutineString	(oCRtnEntry* entry);
	
	// Archive / Unarchive
	void		WriteRoutine		(zCArchiver& arc, oCNpc* npc, zBOOL onlyOverlays);
	void		ReadRoutine			(zCArchiver& arc, oCNpc* npc);

private:	

	typedef struct {
		zBOOL		begin;
		zTBBox3D	bbox;
		zREAL		value;
		oCNpc*		npc;
		
	} TRtn_WayBoxLimit;

	int										indexStart	[3];
	int										indexEnd	[3];

	typedef struct {

		// FIXME : Argh, zCListSort
		void		Release()				{ delete(this); };

		zTBBox3D	bbox;
		oCNpc*		npc;
		int			found;
	} TRtn_WayBox;
	
	zCWorld*								world;
	zCListSort  <oCRtnEntry>*				nextEntryNode;		// Check this Entry next

	zCListSort	<oCRtnEntry>				rtnList;
	zCListSort	<TRtn_WayBox>				wayboxListX;
	zCListSort	<TRtn_WayBox>				wayboxListY;
	zCListSort	<TRtn_WayBox>				wayboxListZ;

	zCList		<oCNpc>						activeList;
	zCArraySort	<TRtn_WayBoxLimit*>			wayboxList[3];

	void		InsertWaybox				(oCNpc* npc, zVEC3& mins, zVEC3& maxs);
	void		CreateActiveList			(oCNpc* npc, zTBBox3D& bbox);

	static int	Sort_Routine				(oCRtnEntry *entry1, oCRtnEntry *entry2);
	static int	Sort_WayBoxX				(TRtn_WayBox *entry1, TRtn_WayBox *entry2);
	static int	Sort_WayBoxY				(TRtn_WayBox *entry1, TRtn_WayBox *entry2);
	static int	Sort_WayBoxZ				(TRtn_WayBox *entry1, TRtn_WayBox *entry2);

	static int	Sort_WayBoxLimit			(TRtn_WayBoxLimit *entry1, TRtn_WayBoxLimit *entry2);
};

extern oCRtnManager rtnMan;

#endif