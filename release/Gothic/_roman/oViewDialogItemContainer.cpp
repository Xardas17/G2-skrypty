/******************************************************************************** 
 
     $Workfile:: oViewDialogItemContainer.cpp $         $Date:: 14.02.01 15:51   $
     $Revision:: 19                   $             $Modtime:: 14.02.01 14:49   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDialogItemContainer.cpp $
 * 
 * 19    14.02.01 15:51 Speckels
 * 
 * 18    13.02.01 18:15 Speckels
 * 
 * 17    13.02.01 11:26 Speckels
 * 
 * 16    8.02.01 17:53 Speckels
 * 
 * 15    8.02.01 16:26 Speckels
 * 
 * 14    6.02.01 2:31 Wohlers
 * 
 * 13    9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
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
#include <oViewDialogItemContainer.h>
#include <zWorld.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( oCViewDialogItemContainer, zCViewDialog, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDialogItemContainer::oCViewDialogItemContainer()
{
	this->Alignment			= oEItemContainerAlignment_Right;
	this->ItemContainer		= NULL;
	this->Value				= 0;
	this->ValueMultiplier	= 1.0f;	
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDialogItemContainer::~oCViewDialogItemContainer()
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
void oCViewDialogItemContainer::Activate( zBOOL bActivate )
{
	zCViewDialog::Activate( bActivate );

	if ( this->ItemContainer )
	if ( this->IsActivated	 )
		 this->ItemContainer->Activate	();
	else
		 this->ItemContainer->Deactivate();

}

//*********************************************************************************
//**															   SetItemContainer
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogItemContainer::SetItemContainer( oCItemContainer* pItemContainer )
{
	this->ItemContainer = pItemContainer;

	if ( this->ItemContainer )	
	{		
		this->ItemContainer->DisableManipulateItems			(TRUE);
		this->ItemContainer->DisableTransferMoreThanOneItem	(FALSE);
		this->UpdateValue();
	}
}

//*********************************************************************************
//**																   SetAlignment
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogItemContainer::SetAlignment( oEItemContainerAlignment enuAlignment )
{
	this->Alignment		= enuAlignment;
}

//*********************************************************************************
//**																GetSelectedItem
//*********************************************************************************
//**
//*********************************************************************************
oCItem*	oCViewDialogItemContainer::GetSelectedItem( void )
{
	if ( ! this->ItemContainer ) return NULL;

	return this->ItemContainer->GetSelectedItem();
}

int	oCViewDialogItemContainer::GetSelectedItemCount( void )
{
	if ( ! this->ItemContainer ) return 0;

	return this->ItemContainer->GetSelectedItemCount();
}

//*********************************************************************************
//**															 RemoveSelectedItem
//*********************************************************************************
//**
//*********************************************************************************
oCItem* oCViewDialogItemContainer::RemoveSelectedItem( void )
{
	if ( ! this->ItemContainer ) return NULL;


	oCItem* selItem = (oCItem*) this->GetSelectedItem();
	int prevSelInstance = selItem?selItem->GetInstance():-1;

	oCItem* item = this->ItemContainer->RemoveByPtr( selItem, 1 );

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
	if ( item )
	{
		// zUINT32	lValueRemoved = zUINT32(item->GetAmount() * ( ( item->GetValue() * this->ValueMultiplier ) + 0.5f )); 
			
		// if	( lValueRemoved > this->Value )	this->Value  = 0;							// ERROR !!!
		// else								this->Value -= lValueRemoved;

		this->UpdateValue();
	}

	return item;
}

//*********************************************************************************
//**																	 InsertItem
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogItemContainer::InsertItem( oCItem* pItem )
{
	if ( ! this->ItemContainer	) return;
	if ( ! pItem				) return;

	// this->Value += zUINT32(pItem->GetAmount() * ( ( pItem->GetValue() * this->ValueMultiplier ) + 0.5f )); 
	
	this->ItemContainer->Insert		( pItem );
	this->				 UpdateValue();
}

//*********************************************************************************
//**																	 RemoveItem
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogItemContainer::RemoveItem( oCItem* pItem )
{
	if ( ! this->ItemContainer	) return;
	if ( ! pItem				) return;

	// zUINT32	lValueRemoved = zUINT32(pItem->GetAmount() * ( ( pItem->GetValue() * this->ValueMultiplier ) + 0.5f )); 
		
	// if	( lValueRemoved > this->Value )	this->Value  = 0;							// ERROR !!!
	// else								this->Value -= lValueRemoved;

	this->ItemContainer->Remove		( pItem );
	this->				 UpdateValue();
}

//*********************************************************************************
//**															 TransferAllItemsTo
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogItemContainer::TransferAllItemsTo( oCNpcInventory*	pInventory )
{
																			if ( ! this->ItemContainer	) return;	// no container at all
																			if ( ! pInventory			) return;	// no intentory to place the items in
	zCListSort<oCItem>* pListItems	= this->ItemContainer->GetContents();	if ( ! pListItems			) return;	// no item list available
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
void oCViewDialogItemContainer::UpdateValue( void )
{
	// this->ItemContainer->SetStaticCategoryText( zSTRING( this->Value ) );
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
zBOOL oCViewDialogItemContainer::CanHandleLeft( void )
{
	return FALSE;
}

//*********************************************************************************
//**																 CanHandleRight
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCViewDialogItemContainer::CanHandleRight( void )
{
	return FALSE;
}

//*********************************************************************************
//**																	HandleEvent
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCViewDialogItemContainer::HandleEvent( int nKey )
{
	if ( ! this->IsActive() ) return FALSE;

	// [Ulf] - 06.01.01 - Mousebutton
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
void oCViewDialogItemContainer::StartSelection( void )
{
	this->IsDone				= FALSE	;
	this->SetHandleEventTop		()		;														// put myself on top of the event list
	this->SetEnableHandleEvent	( TRUE );														

	if ( this->ItemContainer )
	{
		// int nX = 0, nY = 0;

		if ( this->Alignment == oEItemContainerAlignment_Left )	
		{
			// this->ItemContainer->GetSize(nX, nY);
			// nX = ::screen->anx( nX );
			this->ItemContainer->Open(0, 0, INV_MODE_BUY);
		}
		else
			this->ItemContainer->Open(4096, 0, INV_MODE_SELL);
	}
}

//*********************************************************************************
//**																  StopSelection
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDialogItemContainer::StopSelection( void )
{
	this->IsDone				= FALSE	;
	this->SetEnableHandleEvent	( FALSE );	
	
	if ( this->ItemContainer )
	{
		this->ItemContainer->Close();
	}
}

