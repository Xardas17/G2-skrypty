/******************************************************************************** 
 
     $Workfile:: zViewPrint.cpp        $                $Date:: 13.02.01 11:26   $
     $Revision:: 14                   $             $Modtime:: 12.02.01 16:20   $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewPrint.cpp $
 * 
 * 14    13.02.01 11:26 Speckels
 * 
 * 13    25.01.01 20:11 Speckels
 * 
 * 12    16.01.01 23:21 Speckels
 * 
 * 11    9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 10    1.12.00 14:22 Keskenti
 * 
 * 9     28.11.00 12:37 Keskenti
 * 
 * 8     13.11.00 22:02 Hildebrandt
 * 
 * 7     19.10.00 17:15 Keskenti
 * 
 * 6     18.10.00 15:04 Keskenti
 * 
 * 5     18.10.00 0:45 Keskenti
 * 
 * 4     17.10.00 18:58 Keskenti
 * 
 * 3     17.10.00 17:58 Keskenti
 * 
 * 2     17.10.00 14:10 Keskenti
 * 
 * 1     17.10.00 13:24 Keskenti
 * 
 * 2     17.10.00 13:11 Keskenti
 * 
 * 1     17.10.00 13:09 Keskenti
 * 
 * 4     16.10.00 23:20 Keskenti
 * 
 * 3     16.10.00 21:45 Keskenti
 * 
 * 2     16.10.00 18:31 Keskenti
 * 
 * 1     16.10.00 18:30 Keskenti
 * 
 * 2     16.10.00 18:27 Keskenti
 * 
 * 1     16.10.00 13:09 Keskenti
 * 
 * 2     13.10.00 21:35 Keskenti
 * 
 *********************************************************************************/

#include <zCore.h>
#include <zTypes.h>
#include <z3d.h>
#include <zList.h>

#include <zViewBase.h>
#include <zViewObject.h>
#include <zViewDraw.h>
#include <zViewFX.h>
#include <zFonts.h>
#include <zViewPrint_Font.h>
#include <zViewPrint.h>

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( zCViewPrint, zCViewFX, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewPrint::zCViewPrint()
{
	this->OffsetTextPixel	= zPOS( 0, 0 );
	this->PositionCursor	= zPOS( 0, 0 );
	this->SizeMargin	[0]	= zPOS( 0, 0 );
	this->SizeMargin	[1]	= zPOS( 0, 0 );
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewPrint::~zCViewPrint()
{
	this->RemoveAllTexts();
}

//
//---------------------------------------------------------------------------------
//********************************     GET/SET     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**															SizeHeightToContent
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::SizeHeightToContent( zBOOL bPreserveTop )
{
	if ( ! this->ViewFont.GetFont() ) return;

	int nLineHeight		 = this->ViewFont.GetFont()->GetFontY();
	int nLines			 = this->ListTextLines.GetNumInList();

	int nHeight			 = nLineHeight * nLines + 1;
		nHeight			+= this->SizeMargin[0].Y;
		nHeight			+= this->SizeMargin[1].Y;

	int nFormerTop		 = this->PixelPosition.Y;
	int nFormerBottom	 = this->PixelPosition.Y + nHeight;

	this->SetPixelSize		( zPOS( this->PixelSize.X, nHeight ) );

	if ( bPreserveTop )		this->SetPixelPosition	( zPOS( this->PixelPosition.X, nFormerTop ) );
	else					this->SetPixelPosition	( zPOS( this->PixelPosition.X, nFormerBottom - this->PixelSize.Y ) );
}

//
//---------------------------------------------------------------------------------
//********************************     RENDER     *********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																		   Blit
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::Blit( void )
{
	zCViewFX::Blit();

	if (	this->IsOpen	() )
	if ( !  this->IsOpening	() )
	if ( !  this->IsClosing () )

	this->BlitText();
}

//*********************************************************************************
//**																	   BlitText
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::BlitText( void )
{
	zCViewText2*	pViewText	= NULL;
	int				nTextLines	= this->ListTextLines.GetNumInList();

	while( nTextLines )
	{
		pViewText = this->ListTextLines[ --nTextLines ];
		if ( pViewText ) 
		{
			//
			//	CHECK TIMER
			//
			if ( pViewText->IsTimed() )
			{
				zREAL fTime	 = pViewText->GetTimer	 ();
				fTime		-= ::ztimer.GetFrameTimeF()/ztimer.GetMotionFactor();
				if	( fTime <= 0.0f )	{ this->RemoveText( pViewText ); continue; }
				else					pViewText->SetTimer( fTime );
			}

			//
			//	BLIT IT
			//
			this->BlitTextLine( pViewText );
		}
	}
}

//*********************************************************************************
//**																   BlitTextLine
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::BlitTextLine( zCViewText2* pViewText )
{
	//
	//	GET VIEW-FONT REFERNECES
	//
	zCViewFont& fontIntern	= this->ViewFont;
	zCViewFont& fontExtern	= pViewText->GetViewFont();

	//
	//	CHOOSE FONT
	//
	zCFont* pFont = NULL;

					pFont = fontExtern.GetFont();									// try text's font first
	if ( ! pFont )	pFont = fontIntern.GetFont();									// use view's font alternatively
	if ( ! pFont )	return;															

	//
	//	CHOOSE COLOR
	//
	zCOLOR	colorText;

	if		( pViewText->IsColored() )		colorText = fontExtern.GetColor();
	else									colorText = fontIntern.GetColor();

	//
	//	SETUP FONT BLENDING
	//
	if		( fontExtern.IsEnabledBlend() )	{ zrenderer->SetAlphaBlendFunc( fontExtern.GetAlphaBlendFunc()	); colorText.alpha = fontExtern.GetAlpha(); }
	else if ( fontIntern.IsEnabledBlend() )	{ zrenderer->SetAlphaBlendFunc( fontIntern.GetAlphaBlendFunc()	); colorText.alpha = fontIntern.GetAlpha(); }
	else									{ zrenderer->SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE			);											}

	//
	//	BLIT CHARACTERS
	//
	this->BlitTextCharacters( pViewText, pFont, colorText );
}

//*********************************************************************************
//**																 BlitCharacters
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::BlitTextCharacters( zCViewText2* pViewText, zCFont* pFont, zCOLOR& colorFont )
{
	zSTRING&	strText				= pViewText	->GetText				()	;
	zCTexture*	pTextureFont		= pFont		->GetFontTexture		()	;
	zPOS		ptPositionView		= this		->GetPixelPosition		()	;

	zPOS		ptPixel				= pViewText	->GetPosition			()	;	
				ptPixel			   += ptPositionView						;
				ptPixel			   += this->OffsetTextPixel					;

	zPOS		ptClipTopLeft		= ptPositionView						;
	zPOS		ptClipBottomRight	= this		->GetPixelSize			()	; ptClipBottomRight += ptClipTopLeft;

	int			nFontWidth			= 0;
	int			nFontHeight			= pFont->GetFontY();

	zVEC2		vecUV				[2];
	zVEC2		vecPixel			[2];

	//
	//	CALC WIDTH OF ONE SPACE 
	//
	int		nWidthSpace	= 0;
	zVEC2	vecRubbish	[2];

	pFont->GetFontData( 'i', nWidthSpace, vecUV[0], vecUV[1] );

	int letterDist = pFont->GetLetterDistance();
	int spaceWidth = pFont->GetWidth(' ');

	zREAL farZ;
	if (zCCamera::activeCam) farZ = zCCamera::activeCam->GetNearClipZ()+1;
	else					 farZ = 1;

	//
	//	PRINT CHARS
	//
	for ( int nChar = 0; nChar < strText.Length(); nChar++ )
	{
		//
		//	VISIBLE CHAR ?
		//
		if ( zBYTE( strText[ nChar ] ) > 32 )
		{
			pFont->GetFontData( strText[ nChar ], nFontWidth, vecUV[0], vecUV[1] );

			vecPixel[ 0 ][ VX ] = zREAL(ptPixel.X);
			vecPixel[ 0 ][ VY ] = zREAL(ptPixel.Y);

			vecPixel[ 1 ][ VX ] = vecPixel[ 0 ][ VX ] + nFontWidth  - 1;
			vecPixel[ 1 ][ VY ] = vecPixel[ 0 ][ VY ] + nFontHeight - 1;

			if ( vecPixel[ 0 ][ VX ] < ptClipTopLeft	.X	) break;
			if ( vecPixel[ 0 ][ VY ] < ptClipTopLeft	.Y	) break;
			if ( vecPixel[ 1 ][ VX ] > ptClipBottomRight.X	) break;
			if ( vecPixel[ 1 ][ VY ] > ptClipBottomRight.Y	) break;

			::zrenderer->DrawTile( pTextureFont, vecPixel[0], vecPixel[1], farZ, vecUV[0], vecUV[1], colorFont );

			ptPixel.X += nFontWidth + letterDist;
		}
		else	
			ptPixel.X += spaceWidth; // zFONT_SPACE;
	}
}

//
//---------------------------------------------------------------------------------
//*********************************     TEXT     **********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																 GetPixelBroder
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::GetPixelBorder( zPOS& ptTopLeft, zPOS& ptBottomRight )
{
	ptTopLeft		= this->GetPixelPosition();
	ptBottomRight	= this->GetPixelSize	();	

	ptBottomRight	+= ptTopLeft;

	ptTopLeft		+= this->SizeMargin[0];
	ptBottomRight	-= this->SizeMargin[1];
}

//*********************************************************************************
//**																	  ClearText
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::ClearText( void )
{
	this->RemoveAllTexts();
	this->PositionCursor = this->SizeMargin[0];
}

//*********************************************************************************
//**																		  Print
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::Print( zSTRING& strText )
{
	//
	//	CHECK FONT
	//
	if ( ! this->ViewFont.GetFont() ) return;

	//
	//	EVALUATE SIZE
	//

	//
	//	CREATE TEXT
	//
	zCViewText2* pViewText = zNEW( zCViewText2 )
								 ( zCViewText2 ( strText					, 
												 this->PositionCursor		,
												 this->ViewFont.GetColor()	,
												 this->ViewFont.GetFont ()	,
												 0xff						,
												 zRND_ALPHA_FUNC_NONE 
											   )
								 ); 

	//
	//	ADD TEXT TO TEXT ARRAY
	//
	this->AddText( pViewText );

	//
	//	ADVANCE CURSOR TO NEXT LINE
	//
	zPOS ptOffsetPixel	  = zPOS( this->ViewFont.GetFont()->GetFontX( strText ), 0 );
	this->PositionCursor += ptOffsetPixel;
}

//*********************************************************************************
//**																	  PrintLine
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::PrintLine( zSTRING& strText )
{
	//
	//	CHECK FONT
	//
	if ( ! this->ViewFont.GetFont() ) return;

	//
	//	CREATE TEXT
	//
	zCViewText2* pViewText = zNEW( zCViewText2 )
								 ( zCViewText2 ( strText					, 
												 this->PositionCursor		,
												 this->ViewFont.GetColor()	,
												 this->ViewFont.GetFont ()	,
												 0xff						,
												 zRND_ALPHA_FUNC_NONE 
											   )
								 ); 

	//
	//	ADD TEXT TO TEXT ARRAY
	//
	this->AddText( pViewText );

	//
	//	ADVANCE CURSOR TO NEXT LINE
	//
	this->PositionCursor.X  = this->SizeMargin[0].X;
	this->PositionCursor.Y += this->ViewFont.GetFont()->GetFontY();
}

//*********************************************************************************
//**																	 PrintLines
//*********************************************************************************
//**
//*********************************************************************************
void zCViewPrint::PrintLines( zSTRING& strText )
{
	//
	//	CHECK FONT
	//
	if ( ! this->ViewFont.GetFont() ) return;

	//
	//	CREATE LINES
	//
	zPOS	ptBorder	[2];	this->GetPixelBorder( ptBorder[0], ptBorder[1] );

	zSTRING	strMessage			= strText;
	zSTRING strWord				= "";
	zSTRING strLine				= "";
	zSTRING strDelimiters		= " -_#+*~`´=/&%$§\"{[]})\\\n";
	int		nWordWidth			= 0;
	int		nWord				= 1;
	int		nPosX				= ptBorder[0].X;

	//
	//	CALC WIDTH OF ONE SPACE 
	//
	zVEC2	vecRubbish	[2];
	int		nWidthSpace	= 0;

	this->ViewFont.GetFont()->GetFontData( 'i', nWidthSpace, vecRubbish[0], vecRubbish[1] );

	//
	//	PRINT WORD-BY-WORD
	//
	strMessage += "\n";

	do
	{
		strWord		= strMessage.PickWord( nWord, strDelimiters);
		nWordWidth	= this->ViewFont.GetFont()->GetFontX( strWord );

		if ( strWord == "\n" )
		{
			this->PrintLine( strLine );

			nPosX	= ptBorder[0].X;
			strLine = "";
		}
		else if ( strWord.Length() > 0 ) 
		{
			if ( ( nPosX + nWordWidth ) < ptBorder[1].X )
			{
				strLine += strWord		;
				strLine += " "			;
				nPosX   += nWordWidth + nWidthSpace;				
			}
			else
			{
				this->PrintLine( strLine );
				
				strLine  = strWord+" ";
				nPosX	 = ptBorder[0].X + nWordWidth + nWidthSpace;				
			}
		}

		nWord++;
	}
	while( strWord.Length() > 0 );
}

//*********************************************************************************
//**																		AddText
//*********************************************************************************
//**	Do !!! _NOT_ !!! delete the text. The view will do it for you
//*********************************************************************************
void zCViewPrint::AddText( zCViewText2* pText )
{
	if ( ! pText ) return;

	this->ListTextLines.InsertEnd( pText );
}

//*********************************************************************************
//**																	 RemoveText
//*********************************************************************************
//**	
//*********************************************************************************
void zCViewPrint::RemoveText( zCViewText2* pText )
{
	if ( ! pText ) return;

	this->ListTextLines.Remove( pText );
	delete pText;
}

//*********************************************************************************
//**																 RemoveAllTexts
//*********************************************************************************
//**	
//*********************************************************************************
void zCViewPrint::RemoveAllTexts( void )
{
	zCViewText2*	pViewText	= NULL;
	int				nTextLines	= this->ListTextLines.GetNumInList();

	while( nTextLines )
	{
		pViewText = this->ListTextLines[ --nTextLines ];
		if ( pViewText ) this->RemoveText( pViewText );
	}
}
