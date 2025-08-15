/******************************************************************************** 
 
     $Workfile:: oViewDialogStealContainer.cp $         $Date:: 14.02.01 15:51   $
     $Revision:: 11                   $             $Modtime:: 14.02.01 14:50   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogStealContainer.cpp $
 * 
 * 11    14.02.01 15:51 Speckels
 * 
 * 10    13.02.01 18:15 Speckels
 * 
 * 9     13.02.01 11:26 Speckels
 * 
 * 8     8.02.01 17:53 Speckels
 * 
 * 7     8.02.01 16:26 Speckels
 * 
 * 6     6.02.01 2:31 Wohlers
 * 
 * 5     22.01.01 17:05 Keskenti
 * 
 * 4     9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 3     15.12.00 14:57 Keskenti
 * 
 * 2     7.12.00 18:05 Keskenti
 * 
 * 1     7.12.00 17:03 Keskenti
 * 
 * 12    5.12.00 18:51 Keskenti
 * 
 * 11    28.11.00 12:42 Keskenti
 * 
 * 10    22.11.00 15:12 Keskenti
 * 
 * 9     16.11.00 19:26 Keskenti
 * 
 * 8     15.11.00 17:05 Keskenti
 * 
 * 7     14.11.00 20:21 Keskenti
 * 
 * 6     14.11.00 19:07 Keskenti
 * 
 * 5     10.11.00 17:34 Keskenti
 * 
 * 4     9.11.00 17:59 Keskenti
 * 
 * 3     8.11.00 13:45 Keskenti
 * 
 * 2     8.11.00 12:45 Keskenti
 * 
 * 1     8.11.00 12:36 Keskenti
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
#include <oViewDialogStealContainer.h>
#include <zWorld.h>
#include <oNpc.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( oCViewDialogStealContainer, zCViewDialog, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDialogStealContainer::oCViewDialogStealContainer()
{
	this->Alignment			= oEStealContainerAlignment_Right;
	this->StealContainer	= NULL;
	this->Value				= 0;
	this->ValueMultiplier	= 1.0f;
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDialogStealContainer::~oCViewDialogStealContainer()
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
void oCViewDialogStealContainer::Activate( zBOOL bActivate )
{
	zCViewDialog::Activate( bActivate );

	if ( this->StealContainer )
	if ( this->IsActivated	 )
		 this->StealContainer->Activate	();
	else
		 this->StealContainer->Deactivate();

}

//*********************************************************************************
//**															   SetStealContainer
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::SetStealContainer( oCStealContainer* pStealContainer )
{
	this->StealContainer = pStealContainer;

	if ( this->StealContainer )	
	{
		this->StealContainer->DisableManipulateItems			(TRUE);
		this->StealContainer->DisableTransferMoreThanOneItem	(FALSE);
		this->UpdateValue();
	}
}

//*********************************************************************************
//**																   SetAlignment
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::SetAlignment( oEStealContainerAlignment enuAlignment )
{
	this->Alignment		= enuAlignment;
}

//*********************************************************************************
//**																GetSelectedItem
//*********************************************************************************
//**
//*********************************************************************************
oCItem*	oCViewDialogStealContainer::GetSelectedItem( void )
{
	if ( ! this->StealContainer ) return NULL;

	return this->StealContainer->GetSelectedItem();
}


int	oCViewDialogStealContainer::GetSelectedItemCount( void )
{
	if ( ! this->StealContainer ) return 0;

	return this->StealContainer->GetSelectedItemCount();
}

//*********************************************************************************
//**															 RemoveSelectedItem
//*********************************************************************************
//**
//*********************************************************************************
oCItem* oCViewDialogStealContainer::RemoveSelectedItem( void )
{
	if ( ! this->StealContainer ) return NULL;

	oCNpc*			pOwner		= this->StealContainer->GetOwner();	if ( ! pOwner ) return NULL;
	oCNpcInventory* pInventory	= &pOwner->inventory2;

	oCItem* selItem = (oCItem*) this->GetSelectedItem();
	int prevSelInstance = selItem?selItem->GetInstance():-1;

	oCItem*			pItem		= pInventory->RemoveByPtr( (oCItem*) this->GetSelectedItem(), 1 );
	this->StealContainer->SetOwner( pOwner );

	// [SPECKELS] Erstmal auskommentiert, mal schaun, ob ichs noch aktiviere ...
	selItem = (oCItem*) this->GetSelectedItem();

	//
	// "Dauerfeuer" resetten, wenn neues Item ausgewaehlt
	//	
	if (selItem && selItem->GetInstance() != prevSelInstance)
	{
		zinput->ResetRepeatKey(FALSE);		
	}
	
	//
	
	//oCItem*	pItem = this->StealContainer->Remove( (oCItem*) this->GetSelectedItem(), 1 );

	if ( pItem )
	{
		// zUINT32	lValueRemoved = zUINT32(pItem->GetAmount() * ( ( pItem->GetValue() * this->ValueMultiplier ) + 0.5f )); 
			
		// if	( lValueRemoved > this->Value )	this->Value  = 0;							// ERROR !!!
		// else								this->Value -= lValueRemoved;

		this->UpdateValue();
	}

	return pItem;
}

//*********************************************************************************
//**																	 InsertItem
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::InsertItem( oCItem* pItem )
{
	if ( ! this->StealContainer	) return;
	if ( ! pItem				) return;

	// this->Value += zUINT32(pItem->GetAmount() * ( ( pItem->GetValue() * this->ValueMultiplier ) + 0.5f )); 
	
	oCNpc*			pOwner		= this->StealContainer->GetOwner();	if ( ! pOwner ) return;
	oCNpcInventory* pInventory	= &pOwner->inventory2;
	pInventory->Insert( pItem );
	this->StealContainer->SetOwner( pOwner );

//	this->StealContainer->Insert		( pItem );
	this->				 UpdateValue();
}

//*********************************************************************************
//**																	 RemoveItem
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::RemoveItem( oCItem* pItem )
{
	if ( ! this->StealContainer	) return;
	if ( ! pItem				) return;

	// zUINT32	lValueRemoved = zUINT32(pItem->GetAmount() * ( ( pItem->GetValue() * this->ValueMultiplier ) + 0.5f )); 
		
	// if	( lValueRemoved > this->Value )	this->Value  = 0;							// ERROR !!!
	// else								this->Value -= lValueRemoved;

	oCNpc*			pOwner		= this->StealContainer->GetOwner();	if ( ! pOwner ) return;
	oCNpcInventory* pInventory	= &pOwner->inventory2;
					pItem		= pInventory->Remove( pItem, 1 );
	this->StealContainer->SetOwner( pOwner );

//	this->StealContainer->Remove		( pItem );
	this->				 UpdateValue();
}

//*********************************************************************************
//**															 TransferAllItemsTo
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::TransferAllItemsTo( oCNpcInventory*	pInventory )
{
																			if ( ! this->StealContainer	) return;	// no container at all
																			if ( ! pInventory			) return;	// no intentory to place the items in
	zCListSort<oCItem>* pListItems	= this->StealContainer->GetContents();	if ( ! pListItems			) return;	// no item list available
	zUINT32				nItems		= pListItems->GetNumInList()		;	if ( ! nItems				) return;	// item list is empty
	zUINT32				nItem		= nItems							;
	oCItem*				pItem		= NULL								;

	//
	//	PUT ALL ITEMS INTO TARGET INVENTORY
	//
	while( nItem-- )
	{
		pItem = (*pListItems)[ nItem ];

		if ( pItem ) 
		{
			pInventory->Insert( pItem );
		}
	}

	//
	//	REMOVE ALL ITEMS
	//
	nItem = nItems;

	while( nItem-- )
	{
		pItem = (*pListItems)[ nItem ];

		if ( pItem ) 
		{
			this->RemoveItem( pItem );
		}
	}
}

//*********************************************************************************
//**																	UpdateValue
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::UpdateValue( void )
{
	oCNpc*	pOwner	= this->StealContainer->GetOwner();	if ( ! pOwner ) return;

	this->StealContainer->SetName( pOwner->GetName() );
}

//
//---------------------------------------------------------------------------------
//*****************************     INTERACTION     *******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																  CanHandleLeft
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCViewDialogStealContainer::CanHandleLeft( void )
{
	return FALSE;
}

//*********************************************************************************
//**																 CanHandleRight
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCViewDialogStealContainer::CanHandleRight( void )
{
	return FALSE;
}

//*********************************************************************************
//**																	HandleEvent
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCViewDialogStealContainer::HandleEvent( int nKey )
{
	if ( ! this->IsActive() ) return FALSE;

	switch( nKey )
	{
		case KEY_ENTER	:	case MOUSE_BUTTONRIGHT	:
							this->CloseSafe		()		;
							this->IsDone = TRUE			; return TRUE;
	}

	return FALSE; 
}

//*********************************************************************************
//**																 StartSelection
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::StartSelection( void )
{
	this->IsDone				= FALSE	;
	this->SetHandleEventTop		()		;														// put myself on top of the event list
	this->SetEnableHandleEvent	( TRUE );														

	if ( this->StealContainer )
	{
		if ( this->Alignment == oEStealContainerAlignment_Right )
		{
			// int nX, nY;
			// this->StealContainer->GetSize	( nX, nY );
			this->StealContainer->Open		( 4096, 0, INV_MODE_SELL );
		}
		else
			this->StealContainer->Open		( 0, 0, INV_MODE_BUY );
	}
}

//*********************************************************************************
//**																  StopSelection
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogStealContainer::StopSelection( void )
{
	this->IsDone				= FALSE	;
	this->SetEnableHandleEvent	( FALSE );	
	
	if ( this->StealContainer )
	{
		this->StealContainer->Close();
	}
}

