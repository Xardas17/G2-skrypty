/****************************************************************
* CutscenePlayer (Header)              							*
* Datei         : zCCSPool.h									*
* Projekt       : Engine										*
* Autor         : Andre Schrieber								*
* Version       : 0.31											*
* last modified : 12.08.99										*
* erstellt      : 20.12.98										*
*****************************************************************
- bekannte Bugs:
*****************************************************************
- moegliche Optimierungen:
*****************************************************************
- neue Funktionalitaeten seit 
- neue Funktionalitaeten seit 
  
*****************************************************************
- noch fehlende Funktionalitaeten:

*****************************************************************
- Kommentare:
 
****************************************************************/

 
#ifndef _ZCCSPOOL_H_
#define _ZCCSPOOL_H_

#include "zstring.h"
#include "zobject.h"
#include "zccsprops.h"

class zCCSCutsceneContext;

// Flags

const int CS_PLAYING	= 1<<0;	// is it playing now?
const int CS_PLAYED		= 1<<1;	// has it ever been played

///
// Class of Items for Cutscene-Historypool
///

class zCCSPoolItem : public zSTRING, public zCObject
{
	zCLASS_DECLARATION(zCCSPoolItem)
public:	
	zCCSPoolItem				(zCCSCutsceneContext* csContext);
	zCCSPoolItem				(zSTRING & n, int i);
		
	void	ClrFlags			(long _flags);
	void	SetFlags			(long _flags);
	zBOOL	HasFlags			(long _flags);

	int		GetPlayCounter		()			{ return playCounter; }
	int		GetNumPlayed		()			{ return numPlayed; };

	void	IncNumPlayed		()			{ numPlayed++;playCounter++; };	
	void	ResetNumPlayed		()			{ numPlayed = 0; };		
	
	zBOOL	IsAllowedToPlay		();
	void	TestedDeactivation	();
	void	Deactivate			()	{ deactivated=TRUE; };
	zBOOL	IsDeactivated		()	{ return deactivated; };	

	virtual void Archive	(zCArchiver &arc);
	virtual void Unarchive	(zCArchiver &arc);
	
	zCCSProps::zTCSRunBehaviour	GetRunBehaviour(int& value);
	zCCSProps::zTCSRunBehaviour	GetRunBehaviour();
	void						SetRunBehaviour(zCCSProps::zTCSRunBehaviour beh, int& value);
	
	virtual void PrintDebugInfo();

protected:

	zCCSPoolItem();
	void Init();

	virtual ~zCCSPoolItem();

private:
	zBOOL							deactivated;

	int								runBehaviourValue;
	zCCSProps::zTCSRunBehaviour		runBehaviour;
	int								numPlayed;	
	int								playCounter;

	int								flags;
};



#endif
