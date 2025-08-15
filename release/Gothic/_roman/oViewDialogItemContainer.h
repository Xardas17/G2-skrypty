/******************************************************************************** 
 
     $Workfile:: oViewDialogItemContainer.h  $                $Date:: 13.02.01 11:26   $
     $Revision:: 9                    $             $Modtime:: 12.02.01 16:47   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogItemContainer.h $
 * 
 * 9     13.02.01 11:26 Speckels
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

#ifndef __OVIEWDIALOGITEMCONTAINER_H__
#define __OVIEWDIALOGITEMCONTAINER_H__

//
//	VIEW
//
class oCViewDialogItemContainer : public zCViewDialog
{
	zCLASS_DECLARATION( oCViewDialogItemContainer )
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
public:
	enum oEItemContainerAlignment
	{
		oEItemContainerAlignment_Left	,
		oEItemContainerAlignment_Right	
	}
	oTItemContainerAlignment, oTAlignmentItemContainer;
	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	oCItemContainer*			ItemContainer	;
	oEItemContainerAlignment	Alignment		;
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
																												
	void						zCCFASTCALL	SetItemContainer	( oCItemContainer*			pItemContainer		)	;
	void						zCCFASTCALL	SetAlignment		( oEItemContainerAlignment	enuAlignment		)	;
	void						zCCFASTCALL	SetValueMultiplier	( zREAL						fValueMultiplier	)	{ this->ValueMultiplier = fValueMultiplier	; }
																												
	oCItemContainer*			zCCFASTCALL	GetItemContainer	( void )											{ return this->ItemContainer				; }	
	oEItemContainerAlignment	zCCFASTCALL	GetAlignment		( void )											{ return this->Alignment					; }	
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
			 oCViewDialogItemContainer();
	virtual ~oCViewDialogItemContainer();
};

typedef oCViewDialogItemContainer	*LPCViewDialogItemContainer,	*LPCVIEWDIALOGITEMCONTAINER;

#endif	//__OVIEWDIALOGITEMCONTAINER_H__