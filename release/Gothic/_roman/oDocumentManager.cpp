/******************************************************************************** 
 
     $Workfile:: oDocumentManager.cpp $                $Date:: 14.03.01 21:46   $
     $Revision:: 15                   $             $Modtime:: 14.03.01 16:38   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oDocumentManager.cpp $
 * 
 * 15    14.03.01 21:46 Wohlers
 * 
 * 14    6.02.01 2:31 Wohlers
 * 
 * 13    6.02.01 1:58 Wohlers
 * 
 * 12    25.01.01 20:49 Keskenti
 * 
 * 11    24.01.01 16:21 Keskenti
 * 
 * 10    22.01.01 17:02 Keskenti
 * 
 * 9     16.01.01 17:22 Keskenti
 * 
 * 8     9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 7     1.12.00 15:13 Keskenti
 * 
 * 6     17.11.00 17:44 Keskenti
 * 
 * 5     25.10.00 17:45 Keskenti
 * 
 * 4     24.10.00 20:54 Keskenti
 * 
 * 3     23.10.00 23:27 Keskenti
 * 
 * 2     23.10.00 23:27 Keskenti
 * 
 * 1     23.10.00 18:05 Keskenti
 * 
 * 12    21.10.00 1:14 Keskenti
 * 
 * 11    20.10.00 22:57 Keskenti
 * 
 * 10    20.10.00 18:47 Keskenti
 * 
 * 9     20.10.00 17:53 Keskenti
 * 
 * 8     20.10.00 16:40 Keskenti
 * 
 * 7     20.10.00 15:35 Keskenti
 * 
 * 6     19.10.00 17:15 Keskenti
 * 
 * 5     19.10.00 15:56 Keskenti
 * 
 * 4     18.10.00 19:10 Keskenti
 * 
 * 3     18.10.00 18:33 Keskenti
 * 
 * 2     18.10.00 17:15 Keskenti
 * 
 *********************************************************************************/

#include <oIncDialogs.h>
#include <zInput_Win32.h>
#include <oDocumentManager.h>
#include <oInfo.h>
#include <oInformationManager.h>
#include <oGame.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**														  Singleton Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCDocumentManager& oCDocumentManager::GetDocumentManager()
{
	static oCDocumentManager mgrDocuments;
	return mgrDocuments;
}

//*********************************************************************************
//**																  Copy Operator
//*********************************************************************************
//**
//*********************************************************************************
oCDocumentManager& oCDocumentManager::operator = ( const oCDocumentManager& mgrDocuments )
{
	return (*this);
}

//*********************************************************************************
//**															   Copy Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCDocumentManager::oCDocumentManager( const oCDocumentManager& mgrDocuments )
{
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCDocumentManager::oCDocumentManager()
{
	//
	//	CREATE MEMBERS
	//
	this->ListDocuments		= zNEW(zCListDocuments);
	this->DlgDocumentMain	= zNEW(zCViewDialog);

	//
	//	SETUP SCREEN
	//
	zCViewDraw& viewScreen = zCViewDraw::GetScreen();

	//
	//	SETUP CHOICE DIALOG
	//
	zUINT32 nSize = zCViewBase::ViewVirtualWidth;

	this->DlgDocumentMain	->Init			( &viewScreen							, 
												TRUE								, 
												zCViewFX::zEViewFX::VIEW_FX_NONE	, 
												zCViewFX::zEViewFX::VIEW_FX_NONE	, 
												1.0f								, 
												1.0f								, 
												zSTRING( "" )	
											);
	this->DlgDocumentMain	->SetPosition	( zPOS(		0,		0 ) );
	this->DlgDocumentMain	->SetSize		( zPOS( nSize,  nSize ) );
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCDocumentManager::~oCDocumentManager()
{
	delete	  this->ListDocuments	 ;
	zRELEASE( this->DlgDocumentMain	);
}

//
//---------------------------------------------------------------------------------
//*******************************     CREATION     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																 CreateDocument
//*********************************************************************************
//**
//*********************************************************************************
int oCDocumentManager::CreateDocument( void )
{
	//
	//	DELETE FORMER DOCUMENTS
	//
	this->ListDocuments->DeleteListDatas();

	//
	//	DONT DO ANYTHING WHILST INFO-MANAGER IS RUNNING
	//
	if ( ! oCInformationManager::GetInformationManager().HasFinished() ) return -1;

	int nDocID = this->GetNextAvailableID();

	oCViewDocument* pViewDoc = zNEW( oCViewDocument )( oCViewDocument() ); 

	if	( ! pViewDoc )	nDocID = -1;
	else
	{
		pViewDoc->Init( this->DlgDocumentMain, 
						TRUE, 
						zCViewFX::zEViewFX::VIEW_FX_FADE, 
						zCViewFX::zEViewFX::VIEW_FX_FADE, 
						500.0f, 
						500.0f, 
						zSTRING( "" ) 
					  );

		pViewDoc->SetPosition	( zPOS(							   0,							   0 ) );
		pViewDoc->SetSize		( zPOS( zCViewBase::ViewVirtualWidth,  zCViewBase::ViewVirtualHeight ) );

		this->ListDocuments->Insert( pViewDoc );
	}

	return nDocID;
}

//*********************************************************************************
//**																	  CreateMap
//*********************************************************************************
//**
//*********************************************************************************
int oCDocumentManager::CreateMap( void )
{
	//
	//	DELETE FORMER DOCUMENTS
	//
	this->ListDocuments->DeleteListDatas();

	//
	//	DONT DO ANYTHING WHILST INFO-MANAGER IS RUNNING
	//
	if ( ! oCInformationManager::GetInformationManager().HasFinished() ) return -1;

	int nDocID = this->GetNextAvailableID();

	oCViewDocumentMap* pViewDoc = zNEW( oCViewDocumentMap )( oCViewDocumentMap() ); 

	if	( ! pViewDoc )	nDocID = -1;
	else
	{
		pViewDoc->Init( this->DlgDocumentMain, 
						TRUE, 
						zCViewFX::zEViewFX::VIEW_FX_FADE, 
						zCViewFX::zEViewFX::VIEW_FX_FADE, 
						500.0f, 
						500.0f, 
						zSTRING( "" ) 
					  );

		pViewDoc->SetPosition	( zPOS(							   0,							   0 ) );
		pViewDoc->SetSize		( zPOS( zCViewBase::ViewVirtualWidth,  zCViewBase::ViewVirtualHeight ) );
//		pViewDoc->SetTexture	( strTexture, TRUE );

		this->ListDocuments->Insert( pViewDoc );
	}

	return nDocID;
}

//
//---------------------------------------------------------------------------------
//********************************     GET/SET     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	   SetPages
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::SetPages( int nDocID, int nPages )
{
	oCViewDocument* pViewDoc = this->GetDocumentView( nDocID );	if ( ! pViewDoc ) return;
	pViewDoc->SetPages( nPages );
}

//*********************************************************************************
//**																		SetPage
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::SetPage( int nDocID, int nPage, zSTRING& strTexture, zBOOL bScale )
{
	oCViewDocument* pViewDoc = this->GetDocumentView( nDocID );	if ( ! pViewDoc ) return;
	pViewDoc->SetPage( nPage, strTexture, bScale );
}

//*********************************************************************************
//**																		SetFont
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::SetFont( int nDocID, int nPage, zSTRING& strFont )
{
	oCViewDocument* pViewDoc = this->GetDocumentView( nDocID );	if ( ! pViewDoc ) return;
	pViewDoc->SetFont( nPage, strFont );
}

//*********************************************************************************
//**																	 SetMargins
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::SetMargins( int nDocID, int nPage, zPOS& ptTopLeft, zPOS& ptBottomRight, zBOOL bPixels )
{
	oCViewDocument* pViewDoc = this->GetDocumentView( nDocID );	if ( ! pViewDoc ) return;
	pViewDoc->SetMargins( nPage, ptTopLeft, ptBottomRight, bPixels );
}

//*********************************************************************************
//**																	   SetLevel
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::SetLevel( int nDocID, const zSTRING& strLevel )
{
	oCViewDocumentMap* pViewDocMap = dynamic_cast<oCViewDocumentMap*> (this->GetDocumentView( nDocID ));	if ( ! pViewDocMap ) return;
	pViewDocMap->SetLevel( strLevel );
}

//*********************************************************************************
//**																 SetLevelCoords
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::SetLevelCoords( int nDocID, int nLeft, int nTop, int nRight, int nBottom )
{
	oCViewDocumentMap* pViewDocMap = dynamic_cast<oCViewDocumentMap*> (this->GetDocumentView( nDocID ));
	if ( ! pViewDocMap )
		return;
	
	pViewDocMap->SetLevelCoords( nLeft, nTop, nRight, nBottom );
}

//*********************************************************************************
//**																	  PrintLine
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::PrintLine( int nDocID, int nPage, zSTRING& strText )
{
	oCViewDocument* pViewDoc = this->GetDocumentView( nDocID );	if ( ! pViewDoc ) return;
	pViewDoc->PrintLine( nPage, strText );
}

//*********************************************************************************
//**																	 PrintLines
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::PrintLines( int nDocID, int nPage, zSTRING& strText )
{
	oCViewDocument* pViewDoc = this->GetDocumentView( nDocID );	if ( ! pViewDoc ) return;
	pViewDoc->PrintLines( nPage, strText );
}

//*********************************************************************************
//**																		   Show
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::Show( int nDocID )
{
	//
	//	GET DOCUMENT VIEW
	//
	oCViewDocument	 * pViewDoc		= this->GetDocumentView( nDocID );					if ( ! pViewDoc ) return;
	oCViewDocumentMap* pViewDocMap	= dynamic_cast< oCViewDocumentMap* > ( pViewDoc );	if( pViewDocMap ) pViewDocMap->UpdatePosition();

	//
	//	DO NOT OPEN WHILST INFO-MANAGER IS RUNNING
	//
	if ( ! oCInformationManager::GetInformationManager().HasFinished() ) 
	{
		//
		//	REMOVE THE DOC FROM THE SCREEN
		//
	//	this->RemoveChild( pViewDoc );

		return;
	}

	//
	//	SET SELF ON TOP OF INPUT HANDLER
	//
	this->SetEnableHandleEvent	( TRUE );
	this->SetHandleEventTop		();														// insert myself into the callback list

	//
	//	CLOSE INVENTORY
	//
	oCNpc* pPlayer = ::ogame->GetSelfPlayerVob();

	if ( pPlayer )
	if ( pPlayer->inventory2.IsOpen() )
		 pPlayer->inventory2.Close ();

	//
	//	LOCK PLAYER MOVEMENT
	//
	if ( pPlayer )
		 pPlayer->SetMovLock( TRUE );

	//
	//	OPEN DOCUMENT VIEW
	//
	pViewDoc->Open();
}

//*********************************************************************************
//**															 GetNextAvailableID
//*********************************************************************************
//**
//*********************************************************************************
int oCDocumentManager::GetNextAvailableID( void )
{
	return this->ListDocuments->GetNumInList();
}

//*********************************************************************************
//**																GetDocumentView
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocument* oCDocumentManager::GetDocumentView( int nDocID )
{
	return (*this->ListDocuments)[ nDocID ];
}

//*********************************************************************************
//**																	  UpdateMap
//*********************************************************************************
//**
//*********************************************************************************
void oCDocumentManager::UpdateMap( int nDocID )
{
	oCViewDocument*		pViewDoc	= this->GetDocumentView( nDocID );					if ( ! pViewDoc ) return;
	oCViewDocumentMap* pViewDocMap	= dynamic_cast< oCViewDocumentMap* > ( pViewDoc );	if( pViewDocMap ) pViewDocMap->UpdatePosition();
}

//
//---------------------------------------------------------------------------------
//****************************     EVENT HANDLING     *****************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	HandleEvent
//*********************************************************************************
//**
//*********************************************************************************
zBOOL oCDocumentManager::HandleEvent( int nKey )
{
	// [Ulf] - 06.01.01 - Use logical Game-Constants !
	if (zinput->IsBinded(GAME_END,nKey) || zinput->IsBindedToggled(GAME_SCREEN_MAP,nKey) || zinput->IsBinded(GAME_INVENTORY,nKey) || (nKey==KEY_ENTER) || (nKey==MOUSE_BUTTONRIGHT)) {

//	switch ( nKey )
//	{
//	case KEY_TAB:
//	case KEY_ESC:
//	case KEY_ENTER:
		//
		//	REMOVE VIEWS
		//
		this->DlgDocumentMain->RemoveAllChildren();

		//
		//	REMOVE DOCUMENTS
		//
		this->ListDocuments->DeleteList();

		//
		//	UNLOCK PLAYER MOVEMENT
		//
		oCNpc* pPlayer = ::ogame->GetSelfPlayerVob();
		if ( pPlayer )
			 pPlayer->SetMovLock( FALSE );

		//
		//	DO NOT HANDLE FURTHER EVENTS
		//
		this->SetEnableHandleEvent( FALSE );
	}
	
	return TRUE; 
}
