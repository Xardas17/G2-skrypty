/******************************************************************************** 
 
     $Workfile:: zViewDraw.h          $                $Date:: 16.02.01 14:01   $
     $Revision:: 14                   $             $Modtime:: 16.02.01 13:38   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewDraw.h $
 * 
 * 14    16.02.01 14:01 Moos
 * Noch mehr Runterfahr-Crashfixes
 * 
 * 13    28.11.00 12:37 Keskenti
 * 
 * 12    21.10.00 19:08 Moos
 * 
 * 11    21.10.00 1:14 Keskenti
 * 
 * 10    20.10.00 19:08 Keskenti
 * 
 * 9     20.10.00 16:18 Keskenti
 * 
 * 8     19.10.00 18:55 Keskenti
 * 
 * 7     19.10.00 18:27 Keskenti
 * 
 * 6     19.10.00 17:15 Keskenti
 * 
 * 5     17.10.00 14:10 Keskenti
 * 
 * 4     16.10.00 23:20 Keskenti
 * 
 * 3     16.10.00 21:45 Keskenti
 * 
 * 2     16.10.00 18:27 Keskenti
 * 
 * 1     16.10.00 11:34 Keskenti
 * 
 * 3     13.10.00 21:35 Keskenti
 * 
 *********************************************************************************/

#ifndef __ZVIEWDRAW_H__
#define __ZVIEWDRAW_H__

//
//	VIEW
//
class zCViewDraw : public zCViewObject
{
	zCLASS_DECLARATION	(zCViewDraw)
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zTRnd_AlphaBlendFunc	TextureFuncAlpha	;
	zCTexture*				Texture				;
	zCOLOR					TextureColor		;
	int						TextureAlpha		;
	zVEC2					TexturePosition	[2]	;
													
	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
    static zCViewDraw& GetScreen( void );
    static void        CleanupScreen();
public:
	//																														
	//	HIERARCHY																											
	//																														
	void					zCCFASTCALL	RemoveChild				( zSTRING& strTexture )										;

	//
	//	SET
	//
	void					zCCFASTCALL	SetTextureAlphaBlendFunc( const zTRnd_AlphaBlendFunc &funcAlphaBlend )				;
	void					zCCFASTCALL	SetTexture				( const zSTRING& strTexture )								;
	void					zCCFASTCALL	SetTexture				( zCTexture* pTexture )										;
	void					zCCFASTCALL	SetTextureColor			( const zCOLOR& colTexture )								;
	void					zCCFASTCALL	SetTextureAlpha			( int nAlpha )												;
	void					zCCFASTCALL	TextureCacheIn			( zREAL priority )											;
																																
	//																															
	//	GET																														
	//																															
	zTRnd_AlphaBlendFunc	zCCFASTCALL	GetTextureAlphaBlendFunc( void )													{ return this->TextureFuncAlpha	; }
	zCTexture*				zCCFASTCALL	GetTexture				( void )													{ return this->Texture			; }
	const zCOLOR&			zCCFASTCALL	GetTextureColor			( void )													{ return this->TextureColor		; }
	int						zCCFASTCALL	GetTextureAlpha			( void )													{ return this->TextureAlpha		; }
																																
	//									
	//	RENDER							
	//									
protected:
	virtual void			zCCFASTCALL	EvaluateTexturePosition	( void )													;
	virtual void			zCCFASTCALL	BlitTexture				( void )													;
	virtual void			zCCFASTCALL	Blit					( void )													;
																
	void					zCCFASTCALL	DrawChildren			( void )													;
	void					zCCFASTCALL	Draw					( void )													;
																
public:															
	void					zCCFASTCALL	Render					( void )													;
	
	//
	//	CON-/DESTRUCTION
	//
public:
			 zCViewDraw();
	virtual ~zCViewDraw();
};

typedef zCViewDraw	*LPCViewDraw,	*LPCVIEWDRAW;

#endif	//__ZVIEWDRAW_H__