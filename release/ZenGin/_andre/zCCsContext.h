/****************************************************************
* CutscenePlayer (Header)              							*
* Datei         : zCCSPlayer.h									*
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
	Startbedingungen				12.08.99  
	Sperrzeiten						19.08.99
- neue Funktionalitaeten seit 
  
*****************************************************************
- noch fehlende Funktionalitaeten:

*****************************************************************
- Kommentare:
 
********************************************************************/

 
#ifndef _ZCCSCONTEXT_H_
#define _ZCCSCONTEXT_H_

#include "zObject.h"
#include "ZString.h"
#include "zContainer.h"

#include "zCCSCutscene.h"
#include "zCCSLib.h"
class zCVob;


///////////////
#define SCR_RANGE_OFF	  100000000.0F
#define SCR_FORCE		  0.0F


class zCCSPoolItem;

class zCCSCutsceneContext : public zCCutscene
{
	zCLASS_DECLARATION	(zCCSCutsceneContext)	

public:
	
	enum zTCSPlayResult 
	{ 
		CS_PLAY_STARTEDPLAYING,
		CS_PLAY_STOPPED,
		CS_PLAY_INTERRUPTED,
		CS_PLAY_RESUMED,
		CS_PLAY_CONTINUED,
		CS_PLAY_DISABLED,

		CS_PLAY_STARTFAILED,
		CS_PLAY_RESUMEFAILED,		
		CS_PLAY_TOOFAR,
		CS_PLAY_MAXREACHED,		
		CS_PLAY_NOTTRIGGERED,
		CS_PLAY_CHECKFAILED,
		CS_PLAY_MAX
	} lastPlayResult;

	static zBOOL playDisabled;
	static zBOOL DisablePlayCutscenes(zBOOL disable=TRUE);	
	
	zCCSCutsceneContext	();
	zCCSCutsceneContext	(zSTRING & csname);
	zCCSCutsceneContext	(zCCSBlock* bl, int ref, zBOOL asUnit=FALSE);

	virtual ~zCCSCutsceneContext();

	void	UseThisSubBlock(zCCSBlock* bl);

	virtual void	SetPoolItem			(zCCSPoolItem* _poolItem);	
	virtual void	SetStage			(zCVob* vob);	

	zTCSPlayResult	GetLastPlayResult	(zSTRING& result);
	zCSTIME			GetLastTimeStamp	();
	zCSTIME			GetLastTimePoint	();	
	zSTRING			GetCSName			() const			{ return (properties?properties->GetName():zSTR_EMPTY); };	
	int				GetOUReference		() const			{ return reference; };

	virtual zBOOL	AddMainRole			(zCVob* roleVob);

	virtual zBOOL	StartPlaying		();
	virtual zBOOL	Play				(zPOINT3 position);
	virtual void	Stop				();
	virtual void	Interrupt			();
	virtual void	ForcedInterrupt		();	
	
	virtual zBOOL	CheckRoleReactions	();
	
	virtual zBOOL	IsPlaying			();			
	virtual zBOOL	IsFinished			();	
	virtual zBOOL	IsCutscene			()	{ return isCutscene; };	
	virtual zBOOL	IsOutputUnit		()	{ return !isCutscene; };
	zBOOL			IsLoaded			()  { return loaded; };				

	zBOOL			ReplayCutscene		();	

	zBOOL			AreU				(const zSTRING & csname);
	zBOOL			AreU				(int ref);		

	void			HandleTrigger		();
	void			HandleUntrigger		();	

	virtual void	PrintDebugInfo		(const zSTRING& parm="");
	
public:

	zBOOL allowedToPlay;

protected:
	virtual void	PrepareBlock	();

	// Archiver-Methoden
	virtual void	Archive			(zCArchiver &arc);
	virtual void	Unarchive		(zCArchiver &arc);

	virtual zCVob*	GetStage		();


private:

	virtual zCVob*	CatchPlayer	(zCVob* initVob=0); // überschreibungstrick!! liefert alternative vob für die CS
	
	void			ForcedResume		();
	zBOOL			IsForcedInterrupted	();

	zCVob*			alternativeStageVob;		

	zBOOL			wasTriggered;
	zBOOL			isCutscene;	
	zBOOL			loaded;		
	int				reference;
	
	zCVob*			stage;	

	zCCSPoolItem*	poolItem;

	zCSTIME			lastTimeStamp;  // StartTime of the last block
	zCSTIME			lastTimePoint;	// last TimePoint of call(play)	
};

// **************** Cutscen Debugging interface

class zCCSDebugger 
{
public:
	zCArray<zCCSBlockBase*>		callstack;
	zCCSSyncBlock*				callframe;	
	zCCSDebugger*				deb;

	zCCSDebugger() : callframe(0), callstack(), deb(0) {};
	virtual ~zCCSDebugger();

	virtual void CSDB_BeginSyncBlock(zCCSSyncBlock* b)=0;
	virtual void CSDB_BeginAtomBlock(zCCSBlockBase* b)=0;
	virtual void CSDB_EndAtomBlock	(zCCSBlockBase* b)=0;
	virtual void CSDB_Error			(zCCSBlockBase* b, zSTRING & text)=0;
	virtual void CSDB_Warning		(zCCSBlockBase* b, zSTRING & text)=0;

	virtual void CSDB_StartPlaying	(zCCutscene* b)=0;
	virtual void CSDB_Stop			(zCCutscene* b)=0;
};


extern zCCSCutsceneContext* dContext;

#endif