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

 
#ifndef _ZCCSMANAGER_H_
#define _ZCCSMANAGER_H_

const int zLIB_STORE_ASCII	= 1;
const int zLIB_STORE_BIN	= 2;

const int zLIB_LOAD_ASCII	= 1;
const int zLIB_LOAD_BIN		= 2;

#include "zobject.h"
#include "zCCSProps.h"

class zCEventMessage;
class zCCSPlayer;
class zCCSBlock;
class zCCSBlockBase;
class zCCSPoolItem;
class zCCutscene;
class zCCSLib;
class zCCSCutsceneContext;
class zCCSPoolItem;






///
// Cutscene-Manager
///
class zCCSManager : public zCObject
{
zCLASS_DECLARATION	(zCCSManager)
public:	

	zCCSManager							();
	virtual ~zCCSManager				();		

	///
	//History
	///

	zCCSCutsceneContext*	InitiateCSwithContext(zCCSCutsceneContext* context);
	zCCSCutsceneContext*	InitiateOUwithContext(zCCSCutsceneContext* context);
	zCCSCutsceneContext*	CreateNewOutputUnit	(int ref);
	zCCSCutsceneContext*	CreateNewCutscene	(zSTRING & csname);
	
	zBOOL	IsDeactivated				(zSTRING & csname);
	void	PoolCountStart				(zSTRING & csname);
	void	PoolCountStop				(zSTRING & csname);
	
	void	PoolResetAll				();  //setzt Run-Zähler zurück
	void	PoolResetByHour				();
	void	PoolResetByDay				();

	int		PoolAllowedToStart			(zSTRING & csname); // 1==ja, 0==nein und -1==cs giebs nicht
	int		PoolNumPlayed				(zSTRING & csname);	
	zBOOL	PoolHasFlags				(zSTRING & csname, int flags);
	void	PoolClrFlags				(zSTRING & csname, int flags);
	void	PoolSetFlags				(zSTRING & csname, int flags);

	///
	// Editor Short-Cuts
	///

	int			GetNumOfShortCom		();
	zSTRING		GetShortCom				(int z);
	
	///
	// Create-Methods
	///
	virtual		zCEventMessage* CreateMessage	(int z)	{ return 0; };
	virtual		zCEventMessage* CreateOuMessage	()		{ return 0; };	
	virtual		zCCSPlayer*		CreateCutscenePlayer(zCWorld* ownerWorld); // Creating a cutscenes player with given ownerWorld
	virtual		zCCSProps*		CreateProperties();
	
	virtual		void			RemoveCutscenePlayer(zCCSPlayer* csplayer);
	///
	// Output-Library
	///
	void				LibCompact				();
	void				LibForceToLoad			();
	virtual zBOOL		LibIsLoaded				();
	virtual zCCSBlock*	LibGet					(int n);
	virtual zCCSBlock*	LibGetFirst				();
	virtual zCCSBlock*	LibGetNext				();
	virtual zCCSBlock*	LibGetFirst				(int & n);
	virtual zCCSBlock*	LibGetNext				(int & n);
	virtual int			LibAddOU				(zCCSBlock* bl);
	virtual void		LibDelOU				(int n);
	virtual void		LibNullOU				(int n);	
	virtual void		LibLoad					(int flags = zLIB_LOAD_ASCII | zLIB_LOAD_BIN);	
	virtual void		LibStore				(int flags = zLIB_STORE_ASCII | zLIB_STORE_BIN);	
	virtual zBOOL		LibValidateOU			(int ref=0);
	virtual int			LibValidateOU			(zSTRING & token);

	virtual zSTRING		LibGetSvmModuleName		(int n);
	virtual zBOOL		LibIsSvmModuleRunning	(int n);
	virtual zBOOL		LibSvmModuleStart		(int n);
	virtual zBOOL		LibSvmModuleStop 		(int n);

	zCArray<zSTRING>	libSvmModuleList;

#ifdef COMPILING_SPACER
	virtual void			OpenCSForIteration	(zSTRING& scene);
	virtual void			SaveCSForIteration	(zSTRING& scene);
	virtual void			CloseIteration		();
	virtual zBOOL			Next				(zSTRING& Token, zSTRING& Text);
	virtual zBOOL			Localize			(zSTRING& Token, zSTRING& Text);
	virtual	zCCSBlockBase*	BlockLocalize		(zCCSBlockBase* block, zSTRING& Text);	
#endif

protected:

	virtual void		InsertPlayerInList(zCCSPlayer* csplayer);
	virtual void		RemovePlayerFromList(zCCSPlayer* csplayer);
	

	void				AddCommand		(zSTRING & comm);

	virtual void		LibCheckLoaded	(int flags = zLIB_LOAD_ASCII | zLIB_LOAD_BIN);	

	///
	// Archiver
	///

	virtual void		Archive			(zCArchiver &arc);
	virtual void		Unarchive		(zCArchiver &arc);

	zCCutscene*			iteration;
	zCCSBlockBase*		iter;
	int					iterA;
	int					iterB;

	///
	// internal PoolItem-Methods
	///

	zCArray<zCCSPoolItem*>	csPool;

	virtual zCCSPoolItem*	PoolFindItem	(zSTRING & csname);
	virtual void			PoolInsertItem	(zCCSPoolItem* item);	

private:

	zCArray<zSTRING>	commandStrings;

	zCArray<zCCSPlayer*>csPlayerList;
	
	zCCSLib*			src_lib;
	zCCSLib*			library;
	int					iterator;		
};

#endif
