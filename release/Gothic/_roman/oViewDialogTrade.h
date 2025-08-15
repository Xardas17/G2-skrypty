/******************************************************************************** 
 
     $Workfile:: oViewDialogTrade.h   $                $Date:: 13.02.01 11:26   $
     $Revision:: 14                   $             $Modtime:: 12.02.01 16:44   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogTrade.h $
 * 
 * 14    13.02.01 11:26 Speckels
 * 
 * 13    1.02.01 21:48 Speckels
 * 
 * 12    24.01.01 17:56 Keskenti
 * 
 * 11    22.01.01 15:13 Keskenti
 * 
 * 10    12.01.01 13:19 Keskenti
 * 
 * 9     7.12.00 18:05 Keskenti
 * 
 * 8     7.12.00 15:30 Keskenti
 * 
 * 7     28.11.00 12:42 Keskenti
 * 
 * 6     14.11.00 19:07 Keskenti
 * 
 * 5     10.11.00 17:34 Keskenti
 * 
 * 4     8.11.00 13:45 Keskenti
 * 
 * 3     8.11.00 12:45 Keskenti
 * 
 * 2     20.10.00 16:40 Keskenti
 * 
 * 1     20.10.00 16:27 Keskenti
 * 
 * 2     20.10.00 15:35 Keskenti
 * 
 * 1     19.10.00 15:19 Keskenti
 * 
 * 4     18.10.00 1:08 Keskenti
 * 
 * 3     18.10.00 0:58 Keskenti
 * 
 * 2     18.10.00 0:48 Keskenti
 * 
 * 1     18.10.00 0:47 Keskenti
 * 
 *********************************************************************************/

#ifndef __OVIEWDIALOGTRADE_H__
#define __OVIEWDIALOGTRADE_H__

//
//	VIEW
//
class oCViewDialogTrade : public zCViewDialog
{
	zCLASS_DECLARATION( oCViewDialogTrade );
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
protected:
	typedef 
	enum zETradeDialogSection
	{
		TRADE_SECTION_LEFT_INVENTORY	,
		TRADE_SECTION_RIGHT_INVENTORY	//,
//		TRADE_SECTION_CHOICE			
	}
	zTTradeSection;

/*	typedef 
	enum zETradeDialogChoice
	{
		TRADE_CHOICE_TRANSFER	,	
		TRADE_CHOICE_RESET		,
		TRADE_CHOICE_EXIT		
	}
	zTTradeChoice; */
/*	typedef 
	enum zETradeCharacter
	{
		TRADE_CHARACTER_NPC		,
		TRADE_CHARACTER_PLAYER		
	}
	zTTradeNPC; */

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	oCViewDialogStealContainer*	DlgInventoryNpc		;
//	zCViewDialogChoice*			DlgChoice			;
	oCViewDialogInventory*		DlgInventoryPlayer	;
	zTTradeSection				SectionTrade		;
	oCNpc*						NpcLeft				;
	oCNpc*						NpcRight			;

	zINT						TransferCount		;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
																				
	//																		
	//	HELPERS
	//																		
protected:
	void			zCCFASTCALL	AllDialogsDisable	( void						)	;
	void			zCCFASTCALL	AllDialogsStop		( void						)	;

//	void			zCCFASTCALL	TransferAccept		( void						)	;
//	void			zCCFASTCALL	TransferReset		( void						)	;

	//																			
	//	GET/SET																	
	//																			
public:
	void			zCCFASTCALL	SetNpcLeft			( oCNpc*	pNpc			)	;
	void			zCCFASTCALL	SetNpcRight			( oCNpc*	pNpc			)	;
																				
	//																			
	//	SELECTION																
	//																			
	virtual void	zCCFASTCALL	StartSelection		( void						)	;
																				
	//
	//  GET/ SET
	//
	virtual zINT	GetTransferCount				()						{ return TransferCount; }	;
	virtual void	SetTransferCount				(const zINT count)		{ TransferCount = count; }	;
	virtual void	IncTransferCount				(const zINT count)		{ TransferCount += count; }	;

	//																			
	//	EVENTS																	
	//																			
public:
	virtual zBOOL				HandleEvent			( int nKey					)	;		
	void			zCCFASTCALL	Update				( void						)	;
																					
protected:																			
	zBOOL			zCCFASTCALL	OnKeyLeft			( zBOOL altKey );
	zBOOL			zCCFASTCALL	OnKeyRight			( zBOOL altKey );
	zBOOL			zCCFASTCALL	OnKeyEnter			( void						)	;
	zBOOL			zCCFASTCALL	OnKeyEsc			( void						)	;
																					
	zBOOL			zCCFASTCALL	OnMoveLeft			( void						)	;
	zBOOL			zCCFASTCALL	OnMoveRight			( void						)	;
																					
	zBOOL			zCCFASTCALL	OnTransferLeft		( zINT	amount );
	zBOOL			zCCFASTCALL	OnTransferRight		( zINT	amount );
																					
	zBOOL			zCCFASTCALL	OnSectionPrevious	( void						)	;
	zBOOL			zCCFASTCALL	OnSectionNext		( void						)	;
	void			zCCFASTCALL	OnSection			( zTTradeSection enuSection )	;
																					
//	void			zCCFASTCALL	OnChoice			( zTTradeChoice	 enuChoice	)	;
//	void			zCCFASTCALL	OnAccept			( void						)	;
//	void			zCCFASTCALL	OnRecline			( void						)	;
//	void			zCCFASTCALL	OnBack				( void						)	;
//	void			zCCFASTCALL	OnReset				( void						)	;
																					
	void			zCCFASTCALL	OnExit				( void						)	;

	//
	//	CON-/DESTRUCTION
	//
public:
			 oCViewDialogTrade	();
	virtual ~oCViewDialogTrade	();

	void UpdateViewSettings		();

};

typedef oCViewDialogTrade	*LPCViewDialogTrade,	*LPCVIEWDIALOGTRADE;

#endif	//__OVIEWDIALOGTRADE_H__