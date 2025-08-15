/******************************************************************************** 
 
     $Workfile:: oViewDocument.cpp   $                $Date:: 9.01.01 13:20    $
     $Revision:: 10                   $             $Modtime:: 9.01.01 13:05    $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oViewDocument.cpp $
 * 
 * 10    9.01.01 13:20 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 9     20.12.00 15:42 Speckels
 * 
 * 8     18.12.00 19:35 Speckels
 * 
 * 7     1.12.00 15:13 Keskenti
 * 
 * 6     17.11.00 17:44 Keskenti
 * 
 * 5     24.10.00 20:54 Keskenti
 * 
 * 4     23.10.00 23:27 Keskenti
 * 
 * 3     21.10.00 1:14 Keskenti
 * 
 * 2     20.10.00 17:54 Keskenti
 * 
 * 1     20.10.00 17:38 Keskenti
 * 
 * 1     20.10.00 16:27 Keskenti
 * 
 * 3     19.10.00 19:14 Keskenti
 * 
 * 2     19.10.00 17:15 Keskenti
 * 
 * 1     19.10.00 15:25 Keskenti
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
#include <oViewDocument.h>
#include <oViewDocumentMap.h>
#include <zInput_Win32.h>
#include <oGame.h>
#include <oNpc.h>
#include <zview.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocument::oCViewDocument( zSTRING& strName )
{
	//
	//	SETUP VIEW
	//
	// [BENDLIN] HACK: Karten sofort öffnen
	if (zDYNAMIC_CAST<oCViewDocumentMap>(this))
		this->Init( &zCViewDraw::GetScreen(), FALSE, VIEW_FX_NONE, VIEW_FX_NONE, 0.0f, 0.0f, strName );
	else
		this->Init( &zCViewDraw::GetScreen(), FALSE, VIEW_FX_FADE, VIEW_FX_ZOOM, 500.0f, 500.0f, strName );

	//[EDENFELD] 1.09 : Fonts in Constants.d enthalten
	zCPar_Symbol *sym = NULL;
	zSTRING fontName("font_default.tga");
	sym = parser.GetSymbol("TEXT_FONT_DEFAULT");
	if (sym) sym->GetValue(fontName);


	zCViewPrint::SetFont		( fontName );
	this->SetPixelMargins		( zPOS( 10, 10 ), zPOS( 20, 10 )	);
	this->SizeToContent			();
	this->Center				();
	// [BENDLIN] HACK: Karten sofort öffnen
	if (zDYNAMIC_CAST<oCViewDocumentMap>(this))
		this->OpenImmediately();
	else
		this->Open();

	//
	//	ENABLE EVENT HANDLING
	//
	this->SetEnableHandleEvent	( TRUE );
	this->SetHandleEventTop		();														// insert myself into the callback list

	//
	//	DISABLE PLAYER MOVEMENT
	//
	oCNpc* pPlayer = zDYNAMIC_CAST< oCNpc >  ( ::ogame->GetSelfPlayerVob() );
	if ( pPlayer ) 
	{
		pPlayer->SetMovLock( TRUE );

		//
		//	CLOSE INVENTORY
		//
		if ( pPlayer->inventory2.IsOpen() )	pPlayer->CloseInventory();
	}

	//
	//	SET PAGE COUNT
	//
	this->Pages = 0;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocument::oCViewDocument()
{
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocument::~oCViewDocument()
{
}

//
//---------------------------------------------------------------------------------
//********************************     GET/SET     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																		GetPage
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocument* oCViewDocument::GetPage( int nPage )
{
	zCViewObject*   pView			= const_cast  < zCViewObject  * > ( this->GetChild( nPage ) );	if ( ! pView		 ) return NULL;
	oCViewDocument* pViewDocument	= dynamic_cast< oCViewDocument* > ( pView );					if ( ! pViewDocument ) return NULL;

	return pViewDocument;
}

//*********************************************************************************
//**																	   SetPages
//*********************************************************************************
//** 
//*********************************************************************************
void oCViewDocument::SetPages( int nPages )
{
	//
	//	UPDATE PAGE COUNT 
	//
	this->Pages = nPages;

	//
	//	REMOVE FORMER PAGES - IF ANY
	//
	this->RemoveAllChildren();

	//
	//	ADD NEW PAGES
	//
	oCViewDocument* pViewDocument = NULL;

	while ( nPages-- > 0 )
	{
		pViewDocument = zNEW( oCViewDocument )( oCViewDocument() );

		pViewDocument->SetID( nPages );						
		pViewDocument->Init	( this, FALSE, VIEW_FX_FADE, VIEW_FX_FADE, 500.0f, 500.0f, zSTRING("") );
		pViewDocument->Open	();
	}
}

//*********************************************************************************
//**																	 SetMargins
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::SetMargins( int nPage, zPOS& ptTopLeft, zPOS& ptBottomRight, zBOOL bPixels )
{
	oCViewDocument* pViewDocument = NULL;

	if ( nPage >= 0 )
	{
						pViewDocument = this->GetPage( nPage );						if ( ! pViewDocument ) return;

		if	( bPixels )	pViewDocument->SetPixelMargins	( ptTopLeft, ptBottomRight );
	//	else			pViewDocument->SetVirtualMargins( ptTopLeft, ptBottomRight );
	}
	else
	{
		int nChildren = this->ListChildren.GetNumInList();
		while ( nChildren-- > 0 )
		{
			zCViewObject*   pView			= const_cast  < zCViewObject  * > ( this->ListChildren[ nChildren ] );
							pViewDocument	= dynamic_cast< oCViewDocument* > ( pView );

			if ( pViewDocument )
			{
				if	( bPixels )	pViewDocument->SetPixelMargins	( ptTopLeft, ptBottomRight );
			//	else			pViewDocument->SetVirtualMargins( ptTopLeft, ptBottomRight );
			}
		}
	}
}

//*********************************************************************************
//**																	    SetPage
//*********************************************************************************
//**
//*********************************************************************************
oCViewDocument* oCViewDocument::SetPage( int nPage, zSTRING& strTexture, zBOOL bScale )
{
	oCViewDocument* pViewDocument = NULL;

	if ( nPage >= 0 )
	{
		pViewDocument = this->GetPage( nPage );				if ( ! pViewDocument ) return NULL;
		pViewDocument->SetTexture( strTexture, bScale );
		// Force texture to immediately cache-in
		this->TextureCacheIn(-1);
	}
	else
	{
		int nChildren = this->ListChildren.GetNumInList();
		while ( nChildren-- > 0 )
		{
			zCViewObject*   pView			= const_cast  < zCViewObject  * > ( this->ListChildren[ nChildren ] );
							pViewDocument	= dynamic_cast< oCViewDocument* > ( pView );

			if ( pViewDocument )
			{
				pViewDocument->SetTexture( strTexture, bScale );	
			}
		}
	}	

	return pViewDocument;
}

//*********************************************************************************
//**																	    SetFont
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::SetFont( int nPage, zSTRING& strFont )
{
	oCViewDocument* pViewDocument = NULL;

	if ( nPage >= 0 )
	{
		pViewDocument = this->GetPage( nPage );				if ( ! pViewDocument ) return;
		((zCViewPrint*) pViewDocument)->SetFont( strFont );	
	}
	else
	{
		int nChildren = this->ListChildren.GetNumInList();
		while ( nChildren-- > 0 )
		{
			zCViewObject*   pView			= const_cast  < zCViewObject  * > ( this->ListChildren[ nChildren ] );
							pViewDocument	= dynamic_cast< oCViewDocument* > ( pView );

			if ( pViewDocument )
			{
				((zCViewPrint*) pViewDocument)->SetFont( strFont );	
			}
		}
	}
}

//*********************************************************************************
//**																	  PrintLine
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::PrintLine( int nPage, zSTRING& strText )
{
	oCViewDocument* pViewDocument = NULL;

	if ( nPage >= 0 )
	{
		pViewDocument = this->GetPage( nPage );				if ( ! pViewDocument ) return;
		((zCViewPrint*) pViewDocument)->PrintLine( strText );	
	}
	else
	{
		int nChildren = this->ListChildren.GetNumInList();
		while ( nChildren-- > 0 )
		{
			zCViewObject*   pView			= const_cast  < zCViewObject  * > ( this->ListChildren[ nChildren ] );
							pViewDocument	= dynamic_cast< oCViewDocument* > ( pView );

			if ( pViewDocument )
			{
				((zCViewPrint*) pViewDocument)->PrintLine( strText );	
			}
		}
	}
}

//*********************************************************************************
//**																	 PrintLines
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::PrintLines( int nPage, zSTRING& strText )
{
	oCViewDocument* pViewDocument = NULL;

	if ( nPage >= 0 )
	{
		pViewDocument = this->GetPage( nPage );				if ( ! pViewDocument ) return;
		((zCViewPrint*) pViewDocument)->PrintLines( strText );	
	}
	else
	{
		int nChildren = this->ListChildren.GetNumInList();
		while ( nChildren-- > 0 )
		{
			zCViewObject*   pView			= const_cast  < zCViewObject  * > ( this->ListChildren[ nChildren ] );
							pViewDocument	= dynamic_cast< oCViewDocument* > ( pView );

			if ( pViewDocument )
			{
				((zCViewPrint*) pViewDocument)->PrintLines( strText );	
			}
		}
	}
}

//*********************************************************************************
//**																	 SetTexture
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::SetTexture( zSTRING& strFont, zBOOL bScale )
{
	zCViewDraw::SetTexture( strFont );	

	if	( ! bScale )	this->SizeToContent();
	else				this->ScaleToParent();

	this->AlignPageToParent();
}

//
//---------------------------------------------------------------------------------
//******************************     POSITIONING     ******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**															  AlignPageToParent
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::AlignPageToParent( void )
{
	oCViewDocument* pParent = dynamic_cast< oCViewDocument* > ( this->ViewParent );	if ( ! pParent ) return;

	zPOS ptCenterParent		;
	zPOS ptCenterAllPages	;
	zPOS ptSizeAllPages		;
	zPOS ptSize				;
	zPOS ptStart			;
	zPOS ptOffset			;
	int	 nPage				= this	 ->GetID()	;	
	int	 nPages				= pParent->Pages	;	

	//
	//	SPECIAL PAGE COUNT ?
	//
	if ( nPages  < 1 )						return;
	if ( nPages == 1 )	{ this->Center();	return; }

	if ( pParent )
	{
		//
		//	CALCULATE PARENT'S CENTER POINT
		//
		ptCenterParent		 = pParent->GetPixelPosition();
		ptSize				 = pParent->GetPixelSize	 ();	ptCenterParent += ptSize;
		ptCenterParent.X	/= 2;
		ptCenterParent.Y	/= 2;

		//
		//	CALCULATE ALL PAGES' DIMENSIONS
		//
		ptSize				 = this->GetPixelSize();	
		ptSizeAllPages		 = zPOS( 0, 0 );				{	for ( int i = 0; i < nPages; i ++ ) ptSizeAllPages += ptSize; }

		//
		//	CALCULATE ALL PAGES' CENTER
		//
		ptCenterAllPages	 = ptSizeAllPages;
		ptCenterAllPages.X	/= 2;
		ptCenterAllPages.Y	/= 2;

		//
		//	CALCULATE THIS PAGES OFFSET FROM CENTER
		//
		ptStart				 = ptCenterParent  ;
		ptStart				-= ptCenterAllPages;

		ptOffset			 = ptStart		;
		ptOffset.Y			+= ptSize.Y / 2	;				{	for ( int i = 0; i < nPage; i ++ ) ptOffset.X += ptSize.X;	}

		//
		//	SET POSITION
		//
		this->SetPixelPosition( ptOffset );
	}
	else
		this->SetPosition( zPOS( 0, 0 ) );
}

//*********************************************************************************
//**																		 Center
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::Center( void )
{
	zPOS ptPosition	;
	zPOS ptSize		;

	if ( this->ViewParent )
	{
		ptPosition	= this->ViewParent->GetPixelPosition();
		ptSize		= this->ViewParent->GetPixelSize	();	ptPosition += ptSize;
		ptSize		= this->			GetPixelSize	();	ptPosition -= ptSize;

		ptPosition.X /= 2;
		ptPosition.Y /= 2;

		this->SetPixelPosition( ptPosition );
	//	this->SetPosition	  ( ptPosition );
	}
	else
		this->SetPosition( zPOS( 0, 0 ) );
}

//*********************************************************************************
//**																  SizeToContent
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::SizeToContent( void )
{
	zPOS ptSize;

	if ( this->Texture )
	{
		int nWidth  = this->Texture->GetTextureInfo().refSizeX;
		int nHeight = this->Texture->GetTextureInfo().refSizeY;

		if ( this->ViewParent )
		{
			ptSize = this->ViewParent->GetPixelSize();

			if ((nWidth > 0) && (nWidth < ptSize.X) && (nHeight > 0) && (nHeight < ptSize.Y))
			{
				this->SetPixelSize( zPOS( nWidth, nHeight ) );
				return;
			}
		}
	}	

	this->SizeToParent();
}

//*********************************************************************************
//**																   SizeToParent
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::SizeToParent( void )
{
	this->SetPosition( zPOS( 0, 0 ) );
	this->SetSize	 ( zPOS( zCViewBase::ViewVirtualWidth, zCViewBase::ViewVirtualHeight ) );
}

//*********************************************************************************
//**																  ScaleToParent
//*********************************************************************************
//**
//*********************************************************************************
void oCViewDocument::ScaleToParent( void )
{
	this->SizeToParent();
}
