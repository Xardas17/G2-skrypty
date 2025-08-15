/******************************************************************************** 
 
     $Workfile:: oViewDialogInventory.h  $                $Date:: 13.02.01 11:26   $
     $Revision:: 7                    $             $Modtime:: 12.02.01 16:47   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogInventory.h $
 * 
 * 7     13.02.01 11:26 Speckels
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
 * 1     20.10.00 16:27 Keskenti
 * 
 * 3     20.10.00 15:35 Keskenti
 * 
 * 2     19.10.00 17:15 Keskenti
 * 
 * 1     19.10.00 15:58 Keskenti
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

#ifndef __OVIEWDIALOGINVENTORY_H__
#define __OVIEWDIALOGINVENTORY_H__

//
//	VIEW
//
class oCViewDialogInventory : public zCViewDialog
{
	zCLASS_DECLARATION( oCViewDialogInventory )
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
public:
	enum oEInventoryAlignment
	{
		oEInventoryAlignment_Left	,
		oEInventoryAlignment_Right	
	}
	oTInventoryAlignment, oTAlignmentInventory;
	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	oCNpcInventory*			Inventory			;
	oEInventoryAlignment	Alignment			;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************

	//
	//	GET/SET
	//
public:	
	virtual void 			zCCFASTCALL	Activate			( zBOOL bActive  )						;
															
	void					zCCFASTCALL	SetInventory		( oCNpcInventory* pInventory		)	;
	void					zCCFASTCALL	SetAlignment		( oEInventoryAlignment enuAlignment )	;
															
	oCNpcInventory*			zCCFASTCALL	GetInventory		( void )								{ return this->Inventory; }	
	oEInventoryAlignment	zCCFASTCALL	GetAlignment		( void )								{ return this->Alignment; }	

	oCItem*					zCCFASTCALL	GetSelectedItem		( void )								;
	int						zCCFASTCALL	GetSelectedItemCount( void )											;
	oCItem*					zCCFASTCALL	RemoveSelectedItem	( void )								;
	void					zCCFASTCALL	InsertItem			( oCItem* pItem	)						;
																									
	//														
	//	INTERACTION											
	//														
public:														
	virtual void 			zCCFASTCALL	StartSelection		( void )								;
	virtual void 			zCCFASTCALL	StopSelection		( void )								;

	//																							
	//	EVENTS																					
	//																							
public:																							
	virtual zBOOL			HandleEvent						( int nKey )							;		
																								
	zBOOL					zCCFASTCALL	CanHandleLeft		( void )								;
	zBOOL					zCCFASTCALL	CanHandleRight		( void )								;
															
	//
	//	CON-/DESTRUCTION
	//
public:
			 oCViewDialogInventory();
	virtual ~oCViewDialogInventory();
};

typedef oCViewDialogInventory	*LPCViewDialogInventory,	*LPCVIEWDIALOGINVENTORY;

#endif	//__OVIEWDIALOGINVENTORY_H__