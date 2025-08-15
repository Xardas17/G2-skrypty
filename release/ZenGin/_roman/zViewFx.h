/******************************************************************************** 
 
     $Workfile:: zViewFX.h          $                $Date:: 28.11.00 12:37   $
     $Revision:: 6                    $             $Modtime:: 28.11.00 12:33   $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewFX.h $
 * 
 * 6     28.11.00 12:37 Keskenti
 * 
 * 5     23.10.00 23:27 Keskenti
 * 
 * 4     20.10.00 16:18 Keskenti
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

#ifndef __ZVIEWFX_H__
#define __ZVIEWFX_H__

//
//	VIEW
//
class zCViewFX : public zCViewDraw
{
	zCLASS_DECLARATION	(zCViewFX)
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************
public:
	typedef
	enum zEViewFX
	{
		VIEW_FX_NONE		= 0,
		VIEW_FX_ZOOM		= 1,
		VIEW_FX_FADE		= VIEW_FX_ZOOM << 1,
		VIEW_FX_BOUNCE		= VIEW_FX_FADE << 1,

		VIEW_FX_FORCE_DWORD	= 0xffffffff
	}
	zTViewFX;

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
protected:
	zBOOL		HasOpened		;																			//  indicates completed opening process
	zBOOL		HasClosed		;																			//  indicates completed closing process
	zREAL		TimeOpen		;																			//	elapsed time during opening process
	zREAL		TimeClose		;																			//	elapsed time during closing process
	zREAL		DurationOpen	;																			//	time opening process will take to finish
	zREAL		DurationClose	;																			//	time closing process will take to finish
	zDWORD		ModeOpen		;																			//	fx that will be applied during opening process
	zDWORD		ModeClose		;																			//	fx that will be applied during closing process
	zVEC2		TextureOffset[2];																			//	offset to be added to texture coordinates

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
public:
	//
	//	CREATION
	//
	void			zCCFASTCALL	Init					(	zCViewObject*	pParent			= NULL			,
															zBOOL			bOpened			= TRUE			,
															zDWORD			enuFXOpen		= VIEW_FX_NONE	,
															zDWORD			enuFXClose		= VIEW_FX_NONE	,
															zREAL			fDurationOpen	= 500.0f		,
															zREAL			fDurationClose	= 500.0f		,
															zSTRING&		strTexture		= zSTRING( "" )	
														);

	//
	//	GET/SET
	//
	void			zCCFASTCALL	SetDurationOpen			( zREAL  fDuration			)	{ this->DurationOpen	= fDuration	; }
	void			zCCFASTCALL	SetDurationClose		( zREAL	 fDuration			)	{ this->DurationClose	= fDuration	; }
	void			zCCFASTCALL	SetFXOpen				( zDWORD enuFX				)	{ this->ModeOpen		= enuFX		; }
	void			zCCFASTCALL	SetFXClose				( zDWORD enuFX				)	{ this->ModeClose		= enuFX		; }
	void			zCCFASTCALL	SetClosed				( zBOOL	 bClosed	= TRUE	)	{ this->HasClosed		= bClosed	; this->HasOpened	= !bClosed; }
	void			zCCFASTCALL	SetOpened				( zBOOL	 bOpened	= TRUE	)	{ this->HasOpened		= bOpened	; this->HasClosed	= !bOpened; }
														
	zBOOL			zCCFASTCALL	IsOpen					( void )						{ return this->HasOpened		; }
	zBOOL			zCCFASTCALL	IsClosed				( void )						{ return this->HasClosed		; }
	zBOOL			zCCFASTCALL	IsOpening				( void )						{ return this->TimeOpen  != 0.0f; }
	zBOOL			zCCFASTCALL	IsClosing				( void )						{ return this->TimeClose != 0.0f; }

	//																					
	//	OPEN/CLOSE																		
	//																					
public:
	void			zCCFASTCALL	Open					( void )						;
	void			zCCFASTCALL	OpenSafe				( void )						;											// will not restart open if already opening
	void			zCCFASTCALL	Close					( void )						;											
	void			zCCFASTCALL	CloseSafe				( void )						;											// will not restart close if already closing
																						
protected:																				
	void			zCCFASTCALL	OpenImmediately			( void )						;
	void			zCCFASTCALL	CloseImmediately		( void )						;

	void			zCCFASTCALL	ApplyOpenCloseFX		( void )						;
	void			zCCFASTCALL	ApplyOpenFX				( void )						;
	void			zCCFASTCALL	ApplyCloseFX			( void )						;
																						
	void			zCCFASTCALL	ApplyOpenFade			( void )						;
	void			zCCFASTCALL	ApplyOpenZoom			( void )						;
																						
	void			zCCFASTCALL	ApplyCloseFade			( void )						;
	void			zCCFASTCALL	ApplyCloseZoom			( void )						;
																						
	//																					
	//	RENDER																			
	//																					
protected:																				
	virtual void	zCCFASTCALL	EvaluateTexturePosition	( void )						;
	virtual void	zCCFASTCALL	Blit					( void )						;
	
	//
	//	CON-/DESTRUCTION
	//
public:
			 zCViewFX();
	virtual ~zCViewFX();
};

typedef zCViewFX	*LPCViewFX,	*LPCVIEWFX;

#endif	//__ZVIEWFX_H__