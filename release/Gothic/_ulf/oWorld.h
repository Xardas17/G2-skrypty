/******************************************************************************** 
 
     $Workfile:: oWorld.h             $                $Date:: 14.03.01 21:30   $
     $Revision:: 13                   $             $Modtime:: 14.03.01 21:20   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oWorld.h $
 * 
 * 13    14.03.01 21:30 Wohlers
 * 
 * 12    14.03.01 21:17 Wohlers
 * 
 * 11    19.10.00 21:49 Wohlers
 * 
 * 10    18.10.00 0:51 Wohlers
 * 
 * 9     8.08.00 18:27 Herget
 * 
 * 8     27.07.00 15:03 Wohlers
 * 
 * 7     7.07.00 12:42 Wohlers
 * Gothic 0.87
 * 
 * 6     5.07.00 12:22 Wohlers
 * 
 * 4     22.05.00 18:44 Wohlers
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
 * 10    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 9     29.03.00 15:37 Wohlers
 * Various Fixes ( Klettern, Wayneteigenschaften, GoRoute )
 * 
 * 8     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 7     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 6     11.11.99 13:58 Wohlers
 * EnableVob um "Parent" erweitert
 * 
 * 5     9.11.99 15:35 Wohlers
 * MOBSI Bugfixes / Firehandling V0.5
 * Externals V0.69
 * 
 * 4     22.10.99 13:36 Wohlers
 * 
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Wohlers $
/// @version $Revision: 13 $ ($Modtime: 14.03.01 21:20 $)





#ifndef __OWORLD_H__
#define __OWORLD_H__

#include "zSTRING.h"
#include "zTypes.h"
//#include "Grade.h"

#include "z3d.h"
#include "zWorld.h"
#include "oVob.h"

class oCVob;
class oCNpc;
class oCItem;


typedef zCListSort<zCVob>		oTVobList;
typedef zCListSort<oCNpc>		oTVobListNpcs;
typedef zCListSort<oCItem>		oTVobListItems;

class oCWorld : public zCWorld
{
	zCLASS_DECLARATION	(oCWorld)
public:	
	// path to the current Level
	zSTRING worldFilename;

	// name of the current Level
	zSTRING worldName;

public:
	
	oCWorld();
	virtual ~oCWorld();

	zSTRING GetWorldFilename()		{ return worldFilename; };
	zSTRING GetWorldName()			{ return worldName; };

	// ************************************************
	// Vobs einfügen / entfernen
	// ************************************************
			oCVob*	CreateVob		(const zTVobType type, const zSTRING& name);
	virtual oCVob*	CreateVob		(const zTVobType type, const int index);
	
	// ************************************************
	// Welt laden / speichern
	// ************************************************
	virtual void	Archive			(zCArchiver &arc);
	virtual void	Unarchive		(zCArchiver &arc);	
	
	virtual zBOOL	LoadWorld		(const zSTRING& fileName, const zTWorldLoadMode loadMode);
	virtual zBOOL	SaveWorld		(const zSTRING& fileName, const zTWorldSaveMode saveMode, 
									 const zBOOL	writeBinary=FALSE, const zBOOL _saveLevelMesh=FALSE);
	// ***************************************************************************************
	// zCWorld - Virtuals
	// ***************************************************************************************
	
	// logisches und physisches Ein- und Austragen
	virtual zCTree<zCVob>*	AddVobAsChild		(zCVob *childVob, zCTree<zCVob>* parentVob);	// vob/vobSubtree is inserted into world, vobSubtrees(torches etc) are handled correctly
	virtual void			RemoveVob			(zCVob *vob);									// childs get childs of vob's parent

	// logisches Eintragen
	virtual void			InsertVobInWorld	(zCVob *vob);	

	// physisches Ein- und Austragen (logisch muss der vob schon vorhanden sein)
	virtual void			EnableVob			(zCVob* vob, zCVob* papa = NULL);
	virtual void			DisableVob			(zCVob* vob);

	virtual zCVob*			SearchVob			(zCVob *vob				, zCTree<zCVob>* vobNode=0);
	virtual zCVob*			SearchVobByID		(const zTVobID	vobID	, zCTree<zCVob>* vobNode=0);
	virtual zCVob*			SearchVobByName		(const zSTRING& vobName);
	// CODECHANGE [STEFAN]
	virtual void			SearchVobListByName		(const zSTRING& vobName	, zCArray<zCVob*>& resultVobList);	// collects all vobs with the same name, list is not cleared!
	// virtual void			SearchVobListByClass	(zCClassDef* classDef	, zCArray<zCVob*>& resultVobList, zCTree<zCVob>* vobNode=0);
	// virtual void			SearchVobListByBaseClass(zCClassDef* baseClassDef, zCArray<zCVob*>& resultVobList, zCTree<zCVob>* vobNode=0);	// collects all vobs that are of or derived from 'baseClassDef'
	// CODECHANGE [STEFAN] END

	virtual void			TraverseVobList	(zCVobCallback &callback, void *callbackData=0);

	oTVobList*				GetVobList			()	{ return voblist; };
	oTVobListNpcs*			GetVobListNpcs		()	{ return voblist_npcs; };
	oTVobListItems*			GetVobListItems		()	{ return voblist_items; };			

	virtual void			DisposeWorld		();				// deletes (!) every vob in the world
	virtual void			DisposeVobs			();

	void					ClearNpcPerceptionVobLists	();
protected:
	void zCCFASTCALL		InsertInLists		(zCVob* v);
	void zCCFASTCALL		RemoveFromLists		(zCVob* v);

private:
	oTVobList*				voblist;
	oTVobListNpcs*			voblist_npcs;
	oTVobListItems*			voblist_items;	

};

// ***************************************************************************************
// WORLDTIMER
// ***************************************************************************************

// Zeitmasstab :
// 1 Sekunde (Echtzeit) = 1 Tick (tck)
// 1000 Ticks = 1 Tagesachtel (Spielzeit)
// 8 Tagesachtel = Tag (Spielzeit)

// 24 / 8			= 4 Std				= 1 Tagesachtel = 1000 Ticks
// 1 Std			= 1000 Ticks / 4	= 250 Ticks pro Spielstunde

const zREAL WLD_TICKSPERHOUR	=	250.0f * 1000.0f;		// 250 Ticks
const zREAL WLD_TICKSPERMIN		=	WLD_TICKSPERHOUR / 60.0f;	
const zREAL WLD_TICKSPERSEC		=	WLD_TICKSPERMIN  / 60.0f;
const zREAL WLD_TICKSPERDAY		=	WLD_TICKSPERHOUR * 24.0f;

class oCWorldTimer {
public:
	oCWorldTimer			();
	~oCWorldTimer			();
	
	void	Timer			();
	
	// Set & Get Time
	void	SetDay			(int dayNr);
	int		GetDay			();
	void	SetTime			(int  hour, int  min);
	void	GetTime			(int& hour, int& min);
	void	SetFullTime		(zREAL fullTime);
	zREAL	GetFullTime		();
	zSTRING GetTimeString	();
	
	// Special Time Functions
	zBOOL	IsTimeBetween	(int hour1, int min1, int hour2, int min2);
	zBOOL	IsDay			();
	zBOOL	IsNight			();
	zBOOL	IsLater			(int h1, int m1);
	zBOOL	IsLaterEqual	(int h1, int m1);
	int		GetPassedTime	(zREAL fullTime);
	zREAL	GetSkyTime		();
	
	// statics
	static  void AddTime	(int &h, int &m, int dh, int dm);

private:

	zREAL	worldTime;
	int		day;
};
	
#endif
