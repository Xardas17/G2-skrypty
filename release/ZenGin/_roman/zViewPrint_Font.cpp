/******************************************************************************** 
 
     $Workfile:: zViewPrint_Font.cpp   $                $Date:: 9.01.01 13:21    $
     $Revision:: 6                    $             $Modtime:: 9.01.01 13:17    $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewPrint_Font.cpp $
 * 
 * 6     9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 5     19.10.00 17:15 Keskenti
 * 
 * 4     17.10.00 22:46 Keskenti
 * 
 * 3     17.10.00 17:58 Keskenti
 * 
 * 2     17.10.00 14:11 Keskenti
 * 
 * 1     17.10.00 14:10 Keskenti
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
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color, zREAL fTime, zCFont* pFont, int nAlpha, zTRnd_AlphaBlendFunc funcAlphaBlend )
{
	this->EnabledColor				= TRUE						;
	this->EnabledTimer				= TRUE						;
	this->Text						= strText					;
	this->Timer						= fTime						;
	this->PixelPosition				= ptPosition				;
	this->ViewFont.SetColor			( color					)	;
	this->ViewFont.SetFont			( pFont					)	;
	this->ViewFont.SetAlpha			( nAlpha				)	;
	this->ViewFont.SetAlphaBlendFunc( funcAlphaBlend		)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color, zCFont* pFont, int nAlpha, zTRnd_AlphaBlendFunc funcAlphaBlend )
{
	this->EnabledColor				= TRUE						;
	this->EnabledTimer				= FALSE						;
	this->Text						= strText					;
	this->Timer						= 0.0f						;
	this->PixelPosition				= ptPosition				;
	this->ViewFont.SetColor			( color					)	;
	this->ViewFont.SetFont			( pFont					)	;
	this->ViewFont.SetAlpha			( nAlpha				)	;
	this->ViewFont.SetAlphaBlendFunc( funcAlphaBlend		)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color, zREAL fTime, zCFont* pFont	)
{
	this->EnabledColor				= TRUE						;
	this->EnabledTimer				= TRUE						;
	this->Text						= strText					;
	this->Timer						= fTime						;
	this->PixelPosition				= ptPosition				;
	this->ViewFont.SetColor			( color					)	;
	this->ViewFont.SetFont			( pFont					)	;
	this->ViewFont.SetAlpha			( 0xff					)	;
	this->ViewFont.SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE	)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color, zCFont* pFont )
{
	this->EnabledColor				= TRUE						;
	this->EnabledTimer				= FALSE						;
	this->Text						= strText					;
	this->Timer						= 0.0f						;
	this->PixelPosition				= ptPosition				;
	this->ViewFont.SetColor			( color					)	;
	this->ViewFont.SetFont			( pFont					)	;
	this->ViewFont.SetAlpha			( 0xff					)	;
	this->ViewFont.SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE	)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color )
{
	this->EnabledColor				= FALSE						;
	this->EnabledTimer				= FALSE						;
	this->Text						= strText					;
	this->Timer						= 0.0f						;
	this->PixelPosition				= ptPosition				;
	this->ViewFont.SetColor			( color					)	;
	this->ViewFont.SetFont			( NULL					)	;
	this->ViewFont.SetAlpha			( 0xff					)	;
	this->ViewFont.SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE	)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zREAL fTime, zCFont* pFont )
{
	this->EnabledColor				= FALSE									;
	this->EnabledTimer				= TRUE									;
	this->Text						= strText								;
	this->Timer						= fTime									;
	this->PixelPosition				= ptPosition							;
	this->ViewFont.SetColor			( zCOLOR( 0xff, 0xff, 0xff, 0xff )	)	;
	this->ViewFont.SetFont			( pFont								)	;
	this->ViewFont.SetAlpha			( 0xff								)	;
	this->ViewFont.SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE				)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zCFont* pFont	)
{
	this->EnabledColor				= FALSE									;
	this->EnabledTimer				= FALSE									;
	this->Text						= strText								;
	this->Timer						= 0.0f									;
	this->PixelPosition				= ptPosition							;
	this->ViewFont.SetColor			( zCOLOR( 0xff, 0xff, 0xff, 0xff )	)	;
	this->ViewFont.SetFont			( pFont								)	;
	this->ViewFont.SetAlpha			( 0xff								)	;
	this->ViewFont.SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE				)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition, zREAL fTime )
{
	this->EnabledColor				= FALSE									;
	this->EnabledTimer				= TRUE									;
	this->Text						= strText								;
	this->Timer						= fTime									;
	this->PixelPosition				= ptPosition							;
	this->ViewFont.SetColor			( zCOLOR( 0xff, 0xff, 0xff, 0xff )	)	;
	this->ViewFont.SetFont			( NULL								)	;
	this->ViewFont.SetAlpha			( 0xff								)	;
	this->ViewFont.SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE				)	;
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::zCViewText2( zSTRING& strText, zPOS& ptPosition )
{
	this->EnabledColor				= FALSE									;
	this->EnabledTimer				= FALSE									;
	this->Text						= strText								;
	this->Timer						= 0.0f									;
	this->PixelPosition				= ptPosition							;
	this->ViewFont.SetColor			( zCOLOR( 0xff, 0xff, 0xff, 0xff )	)	;
	this->ViewFont.SetFont			( NULL								)	;
	this->ViewFont.SetAlpha			( 0xff								)	;
	this->ViewFont.SetAlphaBlendFunc( zRND_ALPHA_FUNC_NONE				)	;
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewText2::~zCViewText2()
{
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewFont::zCViewFont( zCFont* pFont, zCOLOR& color, int nAlpha, zTRnd_AlphaBlendFunc funcAlphaBlend )
{
	this->SetFont			( pFont				);
	this->SetColor			( color				);
	this->SetAlpha			( nAlpha			);
	this->SetAlphaBlendFunc	( funcAlphaBlend	);
	this->EnableBlend		( TRUE				);
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewFont::zCViewFont( zCFont* pFont, zCOLOR& color )
{
	this->SetFont			( pFont					);
	this->SetColor			( color					);
	this->SetAlpha			( 0xff					);
	this->SetAlphaBlendFunc	( zRND_ALPHA_FUNC_NONE	);
	this->EnableBlend		( FALSE					);
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewFont::zCViewFont( zCFont* pFont )
{
	this->SetFont			( pFont								);
	this->SetColor			( zCOLOR( 0xff, 0xff, 0xff, 0xff )	);
	this->SetAlpha			( 0xff								);
	this->SetAlphaBlendFunc	( zRND_ALPHA_FUNC_NONE				);
	this->EnableBlend		( FALSE								);
}

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewFont::zCViewFont()
{
	this->SetFont			( NULL								);
	this->SetColor			( zCOLOR( 0xff, 0xff, 0xff, 0xff )	);
	this->SetAlpha			( 0xff								);
	this->SetAlphaBlendFunc	( zRND_ALPHA_FUNC_NONE				);
	this->EnableBlend		( FALSE								);
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewFont::~zCViewFont()
{
}

//*********************************************************************************
//**																		SetFont
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFont::SetFont( zSTRING& strFont )
{
	int		nFont = ::zfontman->Load	( strFont	);
	zCFont* pFont = ::zfontman->GetFont	( nFont		);

	this->SetFont( pFont );
}
