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
- neue Funktionalitaeten seit 
  
*****************************************************************
- noch fehlende Funktionalitaeten:

*****************************************************************
- Kommentare:
 
****************************************************************/

 
#ifndef _ZCCSPLAYER_H_
#define _ZCCSPLAYER_H_

#include "zObject.h"
#include "ZString.h"
#include "zContainer.h"

#include "zCCSCutscene.h"
#include "zCCSLib.h"

#include "zCCSContext.h"

class zCVob;
class zCCSPlayer;
class zCCSManager;
class zCWorld;

class zCCSPlayer : public zCObject, public zCCSDebugger
{
zCLASS_DECLARATION	(zCCSPlayer)
public:
	zCCSPlayer							();
	virtual ~zCCSPlayer					();		

	///
	// Play Cutscenes
	///	
	
	virtual zCCSCutsceneContext*	CreateNewOutputUnit	(int ref, zCVob* vob);	
	virtual zCCSCutsceneContext*	StartOutputUnit	(int ref, zCVob* vob);	
	virtual zCCSCutsceneContext*	StartCutscene	(zSTRING & scene, zCVob* vob);			
	virtual zCCSCutsceneContext*	StartCutscene	(zCCutscene* cs, zCVob* vob, zSTRING csName="");	
	virtual	void					ForgetCutscene	(zCCutscene* cs);	
	
	void							Interrupt		();
	void							Resume			();		

	virtual void	ResetCutscenePlayer	();
	virtual int		StopAllCutscenes	(zCVob* roleVob=0);
	virtual int		StopAllOutputUnits	(zCVob* roleVob=0);

	virtual void	InsertCutscene		(zCCSCutsceneContext* csContext);	// Neue Methode
	virtual void	RemoveCutscene		(zCCSCutsceneContext* csContext);	// Umbenannt	
	
	
	///
	// Handlers
	///

	virtual void	OnCSTrigger			(zSTRING & csname, zCVob* source);
	virtual void	OnCSUntrigger		(zSTRING & csname, zCVob* source);
		
	///
	// Set and Get Informations
	///

		
	zCCSCutsceneContext*	GetStartedCutscene		(zCVob* mainrole);
	zCCSCutsceneContext*	GetStartedCutscene		(const zSTRING& csname);
	zCCSCutsceneContext*	GetPlayingGlobalCutscene();	
	zBOOL					IsAssigned				(zSTRING& csname, zSTRING& vobname);
	
	//
	// Setting an getting Owner-Objects (Parent-Manager and -World)
	// Method SetOwnerWorld sets 'ownerManager', too.
	//

	virtual void			SetOwnerWorld			(zCWorld* world);
	virtual void			SetOwnerManager			(zCCSManager* manager);
	
	zCWorld*				GetOwnerWorld			()	{ return ownerWorld; };
	zCCSManager*			GetOwnerManager			()	{ return ownerManager; };
	
	//
	// handling cutscenes in playlist
	//
	virtual void	Process();

	///
	// Debug
	///

	void			PrintListOfCutscenes(const zSTRING& parm="");
	void			ToggleDebugInfo		();		

protected:	

	//
	// internal Cutscene-Handler with reference-position and  day/time-information
	//	
	virtual void	ProcessCutscene	(zCCSCutsceneContext* cs, const zPOINT3& pos);
	virtual void	ProcessList		(const zPOINT3& pos, int day, int hour, int minute);

	///
	// Archiver-Methoden
	///

	virtual void	Archive			(zCArchiver &arc);
	virtual void	Unarchive		(zCArchiver &arc);
		
	zBOOL			UpdateCutscenesNow();
		
	int lastProcessDay;
	int lastProcessHour;

	zCList<zCCSCutsceneContext>* processingListItem;
	int							 processingCtr;
	
	//
	// internal debug-methods [Speckels]
	// 

	void		DebugResetInfoscreen();
	void		DebugAddCutscene(int nr, zPOINT3 pos, zBOOL marked=FALSE);

	zBOOL		debugInfoOnScreen;
	zCView*		debugInfoScreen;	

private:
		
	zREAL							timerCtr;
	zCList<zCCSCutsceneContext>		playList;
//	zCArray<zCCSCutsceneContext*>	breakList;	
	zCCSManager*					ownerManager;
	zCWorld*						ownerWorld;

public:	

	// cutscene debugger
	virtual void CSDB_BeginSyncBlock	(zCCSSyncBlock* b);
	virtual void CSDB_BeginAtomBlock	(zCCSBlockBase* b);
	virtual void CSDB_EndAtomBlock		(zCCSBlockBase* b);
	virtual void CSDB_Error				(zCCSBlockBase* b, zSTRING & text);
	virtual void CSDB_Warning			(zCCSBlockBase* b, zSTRING & text);

	virtual void CSDB_StartPlaying		(zCCutscene* b);
	virtual void CSDB_Stop				(zCCutscene* b);	

};


extern zCCSPlayer* dbplayer;

#endif
