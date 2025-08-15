/******************************************************************************** 
 
     $Workfile:: zViewPrint.h         $                $Date:: 1.12.00 14:22    $
     $Revision:: 11                   $             $Modtime:: 1.12.00 13:35    $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewPrint.h $
 * 
 * 11    1.12.00 14:22 Keskenti
 * 
 * 10    28.11.00 12:37 Keskenti
 * 
 * 9     20.10.00 16:18 Keskenti
 * 
 * 8     18.10.00 15:04 Keskenti
 * 
 * 7     18.10.00 0:45 Keskenti
 * 
 * 6     17.10.00 22:07 Keskenti
 * 
 * 5     17.10.00 22:06 Keskenti
 * 
 * 4     17.10.00 18:58 Keskenti
 * 
 * 3     17.10.00 17:58 Keskenti
 * 
 * 2     17.10.00 14:10 Keskenti
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

#ifndef __ZVIEWPRINT_H__
#define __ZVIEWPRINT_H__

//
//	VIEW
//
class zCViewPrint : public zCViewFX
{
	zCLASS_DECLARATION	(zCViewPrint)
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
protected:
	typedef zCArray< zCViewText2* > zCListViewText;

	typedef
	enum zEViewAlignment
	{
		VIEW_ALIGN_NONE		,
		VIEW_ALIGN_MAX		,
		VIEW_ALIGN_MIN		,
		VIEW_ALIGN_CENTER	
	}
	zTViewAlign;

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zCListViewText	ListTextLines	;
	zCViewFont		ViewFont		;
	zPOS			PositionCursor	;
	zPOS			OffsetTextPixel	;
	zPOS			SizeMargin	[2]	;

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	void			zCCFASTCALL	SetFont					( zSTRING& strFont											)	{ this->ViewFont.SetFont			( strFont			); }
	void			zCCFASTCALL	SetFont					( zCFont* pFont												)	{ this->ViewFont.SetFont			( pFont				); }
	void			zCCFASTCALL	SetTextColor			( zCOLOR& color												)	{ this->ViewFont.SetColor			( color				); }
 	void			zCCFASTCALL	SetTextAlpha			( int nAlpha												)	{ this->ViewFont.SetAlpha			( nAlpha			); }
	void			zCCFASTCALL	SetTextAlphaBlendFunc	( zTRnd_AlphaBlendFunc& funcAlphaBlend						)	{ this->ViewFont.SetAlphaBlendFunc	( funcAlphaBlend	); }
	void			zCCFASTCALL	SetPixelMargins			( zPOS& ptTopLeft, zPOS& ptBottomRight						)	{ this->SizeMargin[0]	 = ptTopLeft	 ; 
																														  this->SizeMargin[1]	 = ptBottomRight ; 
																														  if ( this->PositionCursor.X < this->SizeMargin[0].X )	this->PositionCursor.X = this->SizeMargin[0].X;
																														  if ( this->PositionCursor.Y < this->SizeMargin[0].Y )	this->PositionCursor.Y = this->SizeMargin[0].Y;
																														}
	void			zCCFASTCALL	SizeHeightToContent		( zBOOL bPreserveTop = FALSE								);

protected:
	void			zCCFASTCALL	GetPixelBorder			( zPOS& ptTopLeft, zPOS& ptBottomRight						);

	//																												
	//	TEXT																										
	//																												
public:																												
	void			zCCFASTCALL	ClearText				( void														);
																													
	//																												
	//	PRINT																										
	//																												
	void			zCCFASTCALL	Print					( zSTRING& strText											);
	void			zCCFASTCALL	PrintLine				( zSTRING& strText											);
	void			zCCFASTCALL	PrintLines				( zSTRING& strText											);
	void			zCCFASTCALL	PrintAligned			( zSTRING& strText, zPOS& ptPosition, 
														  zTViewAlign enuAlignX = VIEW_ALIGN_NONE, 
														  zTViewAlign enuAlignY = VIEW_ALIGN_NONE					);

protected:
	void			zCCFASTCALL	AddText					( zCViewText2* pText										);
	void			zCCFASTCALL	RemoveText				( zCViewText2* pText										);
	void			zCCFASTCALL	RemoveAllTexts			( void														);
																													
	//																												
	//	RENDER																										
	//																												
protected:																											
	virtual void	zCCFASTCALL	Blit					( void														);
	virtual void	zCCFASTCALL	BlitText				( void														);
	virtual void	zCCFASTCALL	BlitTextLine			( zCViewText2* pViewText									);
	virtual void	zCCFASTCALL	BlitTextCharacters		( zCViewText2* pViewText, zCFont* pFont, zCOLOR& colorFont	);

	//
	//	CON-/DESTRUCTION
	//
public:
			 zCViewPrint();
	virtual ~zCViewPrint();
};

typedef zCViewPrint	*LPCViewPrint,	*LPCVIEWPRINT;

#endif	//__ZVIEWPRINT_H__