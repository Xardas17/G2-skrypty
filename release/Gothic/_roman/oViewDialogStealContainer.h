/******************************************************************************** 
 
     $Workfile:: oViewDialogStealContainer.h $                $Date:: 13.02.01 11:26   $
     $Revision:: 3                    $             $Modtime:: 12.02.01 16:47   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogStealContainer.h $
 * 
 * 3     13.02.01 11:26 Speckels
 * 
 * 2     7.12.00 18:05 Keskenti
 * 
 * 1     7.12.00 17:03 Keskenti
 * 
 * 8     5.12.00 18:51 Keskenti
 * 
 * 7     28.11.00 12:46 Keskenti
 * 
 * 6     28.11.00 12:42 Keskenti
 * 
 * 5     14.11.00 20:21 Keskenti
 * 
 * 4     14.11.00 19:07 Keskenti
 * 
 * 3     10.11.00 17:34 Keskenti
 * 
 * 2     8.11.00 12:45 Keskenti
 * 
 * 1     8.11.00 12:33 Keskenti
 * 
 *********************************************************************************/

#ifndef __OVIEWDIALOGSTEALCONTAINER_H__
#define __OVIEWDIALOGSTEALCONTAINER_H__

//
//	VIEW
//
class oCViewDialogStealContainer : public zCViewDialog
{
	zCLASS_DECLARATION( oCViewDialogStealContainer )
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
public:
	enum oEStealContainerAlignment
	{
		oEStealContainerAlignment_Left	,
		oEStealContainerAlignment_Right	
	}
	oTStealContainerAlignment, oTAlignmentStealContainer;
	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	oCStealContainer*			StealContainer	;
	oEStealContainerAlignment	Alignment		;
	zUINT32						Value			;
	zREAL						ValueMultiplier	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************

	//
	//	GET/SET
	//
public:	
	virtual void 				zCCFASTCALL	Activate			( zBOOL bActive  )									;
																												
	void						zCCFASTCALL	SetStealContainer	( oCStealContainer*			pStealContainer		)	;
	void						zCCFASTCALL	SetAlignment		( oEStealContainerAlignment	enuAlignment		)	;
	void						zCCFASTCALL	SetValueMultiplier	( zREAL						fValueMultiplier	)	{ this->ValueMultiplier = fValueMultiplier	; }
																												
	oCStealContainer*			zCCFASTCALL	GetStealContainer	( void )											{ return this->StealContainer				; }	
	oEStealContainerAlignment	zCCFASTCALL	GetAlignment		( void )											{ return this->Alignment					; }	
	zUINT32						zCCFASTCALL	GetValue			( void )											{ return this->Value						; }	
	zREAL						zCCFASTCALL	GetValueMultiplier	( void )											{ return this->ValueMultiplier				; }	
																												
	oCItem*						zCCFASTCALL	GetSelectedItem		( void )											;
	int							zCCFASTCALL	GetSelectedItemCount( void )											;
	oCItem*						zCCFASTCALL	RemoveSelectedItem	( void )											;
	void						zCCFASTCALL	InsertItem			( oCItem*					pItem				)	;
	void						zCCFASTCALL	TransferAllItemsTo	( oCNpcInventory*			pInventory			)	;
																												
protected:																										
	void						zCCFASTCALL	RemoveItem			( oCItem*					pItem				)	;
	void						zCCFASTCALL UpdateValue			( void )											;
																												
	//																											
	//	INTERACTION																								
	//																											
public:																											
	virtual void 				zCCFASTCALL	StartSelection		( void )											;
	virtual void 				zCCFASTCALL	StopSelection		( void )											;
																													
	//																												
	//	EVENTS																										
	//																												
public:																												
	virtual zBOOL				HandleEvent						( int nKey )										;		
																													
	zBOOL						zCCFASTCALL	CanHandleLeft		( void )											;
	zBOOL						zCCFASTCALL	CanHandleRight		( void )											;
																												
	//
	//	CON-/DESTRUCTION
	//
public:
			 oCViewDialogStealContainer();
	virtual ~oCViewDialogStealContainer();
};

typedef oCViewDialogStealContainer	*LPCViewDialogStealContainer,	*LPCVIEWDIALOGSTEALCONTAINER;

#endif	//__OVIEWDIALOGSTEALCONTAINER_H__