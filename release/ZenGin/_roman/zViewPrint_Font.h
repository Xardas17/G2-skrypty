/******************************************************************************** 
 
     $Workfile:: zViewPrint_Font.h    $                $Date:: 20.10.00 16:18   $
     $Revision:: 6                    $             $Modtime:: 20.10.00 16:18   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewPrint_Font.h $
 * 
 * 6     20.10.00 16:18 Keskenti
 * 
 * 5     18.10.00 2:15 Keskenti
 * 
 * 4     17.10.00 22:46 Keskenti
 * 
 * 3     17.10.00 17:58 Keskenti
 * 
 * 2     17.10.00 14:10 Keskenti
 * 
 * 1     17.10.00 14:06 Keskenti
 * 
 * 1     17.10.00 13:24 Keskenti
 * 
 * 1     17.10.00 13:07 Keskenti
 * 
 * 3     16.10.00 23:20 Keskenti
 * 
 * 2     16.10.00 21:45 Keskenti
 * 
 * 1     16.10.00 18:30 Keskenti
 * 
 * 2     16.10.00 18:27 Keskenti
 * 
 * 1     16.10.00 11:34 Keskenti
 * 
 * 3     13.10.00 21:35 Keskenti
 * 
 *********************************************************************************/

#ifndef __ZVIEWPRINT_FONT_H__
#define __ZVIEWPRINT_FONT_H__

//
//	FONT
//
class zCViewFont
{
	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zTRnd_AlphaBlendFunc	FuncAlphaBlend	;
	zCFont*					Font			;
	zCOLOR					Color			;
	int						Alpha			;
	zBOOL					EnabledBlend	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	void					zCCFASTCALL	EnableBlend			( zBOOL bEnable = TRUE					)	{ this->EnabledBlend	= bEnable		; }
	void					zCCFASTCALL	SetFont				( zSTRING& strFont						)	;
	void					zCCFASTCALL	SetFont				( zCFont* pFont							)	{ this->Font			= pFont			; }
	void					zCCFASTCALL	SetColor			( zCOLOR& color							)	{ this->Color			= color			; }
	void					zCCFASTCALL	SetAlpha			( int nAlpha							)	{ this->Alpha			= nAlpha		; }
	void					zCCFASTCALL	SetAlphaBlendFunc	( zTRnd_AlphaBlendFunc funcAlphaBlend	)	{ this->FuncAlphaBlend	= funcAlphaBlend; }

	zBOOL					zCCFASTCALL	IsEnabledBlend		( void )									{ return this->EnabledBlend		; }
	zCFont*					zCCFASTCALL	GetFont				( void )									{ return this->Font				; }
	zCOLOR&					zCCFASTCALL	GetColor			( void )									{ return this->Color			; }
	int						zCCFASTCALL	GetAlpha			( void )									{ return this->Alpha			; }
	zTRnd_AlphaBlendFunc	zCCFASTCALL	GetAlphaBlendFunc	( void )									{ return this->FuncAlphaBlend	; }

	//
	//	CON-/DESTRUCTION
	//
	 zCViewFont( zCFont* pFont, zCOLOR& color, int nAlpha, zTRnd_AlphaBlendFunc funcAlphaBlend );
	 zCViewFont( zCFont* pFont, zCOLOR& color );
	 zCViewFont( zCFont* pFont );
	 zCViewFont();
	~zCViewFont();
};

//
//	TEXT
//
class zCViewText2
{
	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zBOOL		EnabledColor	;
	zBOOL		EnabledTimer	;

	zPOS		PixelPosition	;
	zREAL		Timer			;
	zSTRING		Text			;
	zCViewFont	ViewFont		;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	zBOOL		zCCFASTCALL	IsColored	( void )			{ return this->EnabledColor										; }
	zBOOL		zCCFASTCALL	IsTimed		( void )			{ return this->EnabledTimer										; }
	zPOS&		zCCFASTCALL	GetPosition	( void )			{ return this->PixelPosition									; }
	zCViewFont&	zCCFASTCALL	GetViewFont	( void )			{ return this->ViewFont											; }
	zSTRING&	zCCFASTCALL	GetText		( void )			{ return this->Text												; }
	zREAL		zCCFASTCALL	GetTimer	( void )			{ return this->Timer											; }

	void		zCCFASTCALL	SetColor	( zCOLOR& color )	{ this->ViewFont.SetColor( color )	; this->EnabledColor = TRUE	; }
	void		zCCFASTCALL	SetTimer	( zREAL& fTime	)	{ this->Timer = fTime											; }

	//
	//	CON-/DESTRUCTION
	//
	 zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color, zREAL fTime, zCFont* pFont, int nAlpha, zTRnd_AlphaBlendFunc funcAlphaBlend	);
	 zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color,			  zCFont* pFont, int nAlpha, zTRnd_AlphaBlendFunc funcAlphaBlend	);
	 zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color, zREAL fTime, zCFont* pFont														);	
	 zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color,			  zCFont* pFont														);	
	 zCViewText2( zSTRING& strText, zPOS& ptPosition, zCOLOR& color																					);	
	 zCViewText2( zSTRING& strText, zPOS& ptPosition,				 zREAL fTime, zCFont* pFont														);	
	 zCViewText2( zSTRING& strText, zPOS& ptPosition,							  zCFont* pFont														);	
	 zCViewText2( zSTRING& strText, zPOS& ptPosition,				 zREAL fTime																	);	
	 zCViewText2( zSTRING& strText, zPOS& ptPosition );	
	~zCViewText2();
};

#endif	//__ZVIEWPRINT_FONT_H__