/******************************************************************************** 
 
     $Workfile:: oInformationManager. $                $Date:: 1.02.01 21:48    $
     $Revision:: 21                   $             $Modtime:: 1.02.01 21:14    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oInformationManager.h $
 * 
 * 21    1.02.01 21:48 Speckels
 * 
 * 20    18.01.01 0:07 Keskenti
 * 
 * 19    17.01.01 16:17 Keskenti
 * 
 * 18    17.01.01 13:01 Keskenti
 * 
 * 17    15.01.01 21:20 Keskenti
 * 
 * 16    11.01.01 1:08 Keskenti
 * 
 * 15    11.01.01 0:45 Keskenti
 * 
 * 14    10.01.01 14:29 Keskenti
 * 
 * 13    6.12.00 15:53 Keskenti
 * 
 * 12    14.11.00 13:07 Keskenti
 * 
 * 11    26.10.00 21:07 Keskenti
 * 
 * 10    25.10.00 17:45 Keskenti
 * 
 * 9     23.10.00 23:27 Keskenti
 * 
 * 8     21.10.00 1:14 Keskenti
 * 
 * 7     20.10.00 22:57 Keskenti
 * 
 * 6     20.10.00 18:47 Keskenti
 * 
 * 5     20.10.00 16:40 Keskenti
 * 
 * 4     19.10.00 15:56 Keskenti
 * 
 * 3     18.10.00 18:33 Keskenti
 * 
 * 2     18.10.00 17:15 Keskenti
 * 
 *********************************************************************************/

#ifndef __ZINFORMATIONMANAGER_H__
#define __ZINFORMATIONMANAGER_H__

class oCInformationManager 
{
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
protected:
	typedef
	enum zEInformationManagerMode
	{
		INFO_MGR_MODE_IMPORTANT	,
		INFO_MGR_MODE_INFO		,
		INFO_MGR_MODE_CHOICE	,
		INFO_MGR_MODE_TRADE
	}
	zTInfoMgrMode;

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zSTRING					LastMethod				;
	zCViewDialogChoice*		DlgStatus				;
	oCViewDialogTrade*		DlgTrade				;
	zCViewDialogChoice*		DlgChoice				;
	oCNpc*					Npc						;
	oCNpc*					Player					;
	oCInfo*					Info					;
	zBOOL					IsDone					;
	zBOOL					IsWaitingForEnd			;
	zBOOL					IsWaitingForScript		;
	zBOOL					IsWaitingForOpen		;
	zBOOL					IsWaitingForClose		;
	zBOOL					IsWaitingForSelection	;
	zBOOL					MustOpen				;
	int						IndexBye				;
	int						ImportantCurrent		;
	int						ImportantMax			;
	zTInfoMgrMode			Mode					;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	void	zCCFASTCALL	SetNpc				( oCNpc* pNpc			)	;
	zBOOL	zCCFASTCALL	HasFinished			( void					)	;
	zBOOL	zCCFASTCALL	WaitingForEnd		( void					)	;
	void	zCCFASTCALL	Update				( void					)	;
	void	zCCFASTCALL	Exit				( void					)	;
	void	zCCFASTCALL	ToggleStatus		( void					)	;

	void	UpdateViewSettings				( void					)	;
																			
protected:																	
	void	zCCFASTCALL	CollectInfos		( void					)	;
	zBOOL	zCCFASTCALL	CollectChoices		( oCInfo* pInfo			)	;
	void	zCCFASTCALL	ProcessImportant	( void					)	;
	void	zCCFASTCALL	ProcessNextImportant( void					)	;
	void	zCCFASTCALL	InfoWaitForEnd		( void					)	;

	void	zCCFASTCALL	CameraStart			( void					)	;
	void	zCCFASTCALL	CameraStop			( void					)	;
	void	zCCFASTCALL	CameraRefresh		( void					)	;

	void	zCCFASTCALL	PrintStatus			( void					)	;

	//
	//	EVENTS
	//
	void	zCCFASTCALL	OnImportantBegin	( void					)	;
	void	zCCFASTCALL	OnImportantEnd		( void					)	;
	void	zCCFASTCALL	OnInfoBegin			( void					)	;
	void	zCCFASTCALL	OnInfo				( int			nInfo	)	;
	void	zCCFASTCALL	OnInfo				( oCInfo*		pInfo	)	;
	void	zCCFASTCALL	OnChoiceBegin		( void					)	;
	void	zCCFASTCALL	OnChoice			( int nChoice			)	;
	void	zCCFASTCALL	OnChoice			( oCInfoChoice*	pChoice	)	;
	void	zCCFASTCALL	OnChoiceEnd			( void					)	;
	void	zCCFASTCALL	OnInfoEnd			( void					)	;
																			
	void	zCCFASTCALL	OnTradeBegin		( void					)	;
	void	zCCFASTCALL	OnTradeEnd			( void					)	;
																			
	void	zCCFASTCALL	OnExit				( void					)	;
	void	zCCFASTCALL	OnTermination		( void					)	;

	//
	//	CON-/DESTRUCTION
	//
public:
	static oCInformationManager& GetInformationManager( void );

protected:	 
			 oCInformationManager();
			 oCInformationManager( const oCInformationManager& );
			 oCInformationManager& operator = ( const oCInformationManager& );
public:		~oCInformationManager(); 
};

#endif	//__ZINFORMATIONMANAGER_H__