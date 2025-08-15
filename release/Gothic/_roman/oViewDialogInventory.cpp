/******************************************************************************** 
 
     $Workfile:: oViewDialogInventory.cpp $         $Date:: 14.02.01 15:51   $
     $Revision:: 19                   $             $Modtime:: 14.02.01 14:48   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogInventory.cpp $
 * 
 * 19    14.02.01 15:51 Speckels
 * 
 * 18    13.02.01 18:15 Speckels
 * 
 * 17    13.02.01 13:52 Speckels
 * 
 * 16    13.02.01 13:50 Speckels
 * 
 * 15    13.02.01 13:39 Speckels
 * 
 * 14    13.02.01 11:26 Speckels
 * 
 * 13    8.02.01 17:53 Speckels
 * 
 * 12    8.02.01 16:26 Speckels
 * 
 * 11    6.02.01 2:31 Wohlers
 * 
 * 10    9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 9     19.12.00 20:01 Keskenti
 * 
 * 8     28.11.00 12:42 Keskenti
 * 
 * 7     14.11.00 20:21 Keskenti
 * 
 * 6     14.11.00 19:07 Keskenti
 * 
 * 5     10.11.00 17:34 Keskenti
 * 
 * 4     9.11.00 17:59 Keskenti
 * 
 * 3     8.11.00 12:45 Keskenti
 * 
 * 2     20.10.00 17:53 Keskenti
 * 
 * 1     20.10.00 16:27 Keskenti
 * 
 * 4     20.10.00 15:35 Keskenti
 * 
 * 3     19.10.00 18:27 Keskenti
 * 
 * 2     19.10.00 17:15 Keskenti
 * 
 * 1     19.10.00 16:10 Keskenti
 * 
 * 2     19.10.00 15:56 Keskenti
 * 
 * 1     19.10.00 15:20 Keskenti
 * 
 * 3     18.10.00 1:08 Keskenti
 * 
 * 2     18.10.00 0:49 Keskenti
 * 
 * 1     18.10.00 0:48 Keskenti
 * 
 *********************************************************************************/

#include <zIncDialogs.h>
#include <oItem.h>
#include <oViewDialogItem.h>
#include <oInventory.h>
#include <oViewDialogInventory.h>
#include <zWorld.h>
#include <oNpc.h>
#include <zoption.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( oCViewDialogInventory, zCViewDialog, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDialogInventory::oCViewDialogInventory()
{
	this->Alignment			= oEInventoryAlignment_Right;
	this->Inventory			= NULL;
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDialogInventory::~oCViewDialogInventory()
{
}

//
//---------------------------------------------------------------------------------
//********************************     GET/SET     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	   Activate
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogInventory::Activate( zBOOL bActivate )
{
//	zBOOL switchToFirstCategory = zoptions->ReadBool(zOPT_SEC_GAME,"invSwitchToFirstCategory",TRUE);	

	zCViewDialog::Activate( bActivate );

	if	( this->Inventory	)
		if	( this->IsActivated	)	 
		{
			this->Inventory->Activate	();
//			if (switchToFirstCategory) this->Inventory->SwitchToCategory(1);
		}
		else this->Inventory->Deactivate();
}

//*********************************************************************************
//**																   SetInventory
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogInventory::SetInventory( oCNpcInventory* pInventory )
{
	this->Inventory = pInventory;

	if (this->Inventory)
	{
		this->Inventory->DisableManipulateItems			(TRUE);
		this->Inventory->DisableTransferMoreThanOneItem	(FALSE);
	};
}

//*********************************************************************************
//**																   SetAlignment
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogInventory::SetAlignment( oEInventoryAlignment enuAlignment )
{
	this->Alignment = enuAlignment;
}

//*********************************************************************************
//**																GetSelectedItem
//*********************************************************************************
//**
//*********************************************************************************
oCItem*	oCViewDialogInventory::GetSelectedItem( void )
{
	if ( ! this->Inventory ) return NULL;

	return this->Inventory->GetSelectedItem();
}

int	oCViewDialogInventory::GetSelectedItemCount( void )
{
	if ( ! this->Inventory ) return 0;

	return this->Inventory->GetSelectedItemCount();
}


//*********************************************************************************
//**															 RemoveSelectedItem
//*********************************************************************************
//**
//*********************************************************************************
oCItem* oCViewDialogInventory::RemoveSelectedItem( void )
{
	if ( ! this->Inventory				) return NULL;
	if ( ! this->Inventory->GetOwner()	) return NULL;

	oCItem* selItem = (oCItem*) this->GetSelectedItem();
	int prevSelInstance = selItem?selItem->GetInstance():-1;

	oCItem* item = this->Inventory->RemoveByPtr( selItem, 1 );
	
	// [SPECKELS] Erstmal auskommentiert, mal schaun, ob ichs noch aktiviere ...
	selItem = (oCItem*) this->GetSelectedItem();

	//
	// "Dauerfeuer" resetten, wenn neues Item ausgewaehlt
	//	
	if (selItem && selItem->GetInstance() != prevSelInstance)
	{
		zinput->ResetRepeatKey(FALSE);
	}	
	
	return item;
}

void oCViewDialogInventory::InsertItem( oCItem* pItem )
{
	if ( ! this->Inventory ) return;

	this->Inventory->Insert( pItem );
}

////////////////////////////////////////////////////////////////////////////////
//
//	INTERACTION
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogInventory::CanHandleLeft(void)
{
	if ( !this->Inventory )
		return FALSE;

	//if ( this->Inventory->GetPrevCategory() == this->Inventory->GetCurrentCategory() )
	//	return FALSE;
	//
	//return TRUE;
	
	return FALSE;
}

zBOOL oCViewDialogInventory::CanHandleRight( void )
{
	if ( !this->Inventory )
		return FALSE;

	//if ( this->Inventory->GetNextCategory() == this->Inventory->GetCurrentCategory() )
	//	return FALSE;
	//
	//return TRUE; /DELAY:

	return FALSE;
}

zBOOL oCViewDialogInventory::HandleEvent( int nKey )
{
	if ( !this->IsActive() )
		return FALSE;

	zBOOL bMessageHandled = FALSE;

	switch( nKey )
	{
		case KEY_ENTER:
		case MOUSE_BUTTONRIGHT:
			this->CloseSafe();
			this->IsDone = TRUE;
			return TRUE;
	}

	return bMessageHandled; 
}

//*********************************************************************************
//**																 StartSelection
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogInventory::StartSelection( void )
{
	this->IsDone				= FALSE	;
	this->SetEnableHandleEvent	( TRUE );														

	if ( this->Inventory )
	{
		if ( this->Alignment == oEInventoryAlignment_Right )
		{
			// int nX, nY;
			// this->Inventory->GetSize(nX, nY);
			this->Inventory->Open(4096, 0, INV_MODE_SELL);
		}
		else
			this->Inventory->Open(0, 0, INV_MODE_BUY);
	}

	this->SetHandleEventTop		();														// put myself on top of the event list
}

//*********************************************************************************
//**																  StopSelection
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogInventory::StopSelection( void )
{
	this->IsDone				= FALSE	;
	this->SetEnableHandleEvent	( FALSE );												

	if ( this->Inventory )
	{
		this->Inventory->Close();
	}
}
