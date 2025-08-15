/******************************************************************************** 
 
     $Workfile:: zViewFX.cpp          $                $Date:: 9.01.01 13:21    $
     $Revision:: 14                   $             $Modtime:: 9.01.01 13:18    $
       $Author:: Keskenti                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewFX.cpp $
 * 
 * 14    9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 13    15.12.00 16:12 Keskenti
 * 
 * 12    28.11.00 12:37 Keskenti
 * 
 * 11    26.10.00 18:14 Hildebrandt
 * 
 * 10    25.10.00 17:45 Keskenti
 * 
 * 9     23.10.00 23:27 Keskenti
 * 
 * 8     19.10.00 17:15 Keskenti
 * 
 * 7     18.10.00 18:33 Keskenti
 * 
 * 6     17.10.00 14:10 Keskenti
 * 
 * 5     17.10.00 13:24 Keskenti
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

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( zCViewFX, zCViewDraw, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewFX::zCViewFX()
{
	this->HasOpened			= TRUE					;
	this->HasClosed			= FALSE					;
	this->TimeOpen			= 0.0f					;
	this->TimeClose			= 0.0f					;
	this->DurationOpen		= 500.0f				;
	this->DurationClose		= 500.0f				;
	this->ModeOpen			= VIEW_FX_FADE			;
	this->ModeClose			= VIEW_FX_FADE			;
	this->TextureOffset[0]	= zVEC2( 0.0f, 0.0f )	;
	this->TextureOffset[1]	= zVEC2( 0.0f, 0.0f )	;
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewFX::~zCViewFX()
{
}

//
//---------------------------------------------------------------------------------
//*******************************     CREATION     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																		   Init
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::Init(	zCViewObject*	pParent			,
						zBOOL			bOpened			,
						zDWORD			enuFXOpen		,
						zDWORD			enuFXClose		,
						zREAL			fDurationOpen	,
						zREAL			fDurationClose	,
						zSTRING&		strTexture		)
{	
	if	( pParent )					pParent->AddChild( this );
	if	( bOpened )					this->OpenImmediately	();
	else							this->CloseImmediately	();
									this->SetFXOpen			( enuFXOpen		 );
									this->SetFXClose		( enuFXClose	 );
									this->SetDurationOpen	( fDurationOpen	 );
									this->SetDurationClose	( fDurationClose );
	if ( !strTexture.IsEmpty() )	this->SetTexture		( strTexture	 );
}

//
//---------------------------------------------------------------------------------
//******************************     OPEN/CLOSE     *******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																		   Open
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::Open( void )
{	
	this->HasOpened	= FALSE;																		
	this->TimeOpen	= ::ztimer.GetFrameTimeF()/ztimer.GetMotionFactor();													

	this->HasClosed	= TRUE;															// view is closed until it has finished opening process
	this->TimeClose	= 0.0f;
}																							

//*********************************************************************************
//**																	   OpenSafe
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::OpenSafe( void )
{	
	zREAL fTimeOffset = 0.0f;

	if ( ! this->IsClosing()  )	
	{
		if ( this->IsOpen	()  )	return;
		if ( this->IsOpening()	)	return;
	}
	else
	{
		fTimeOffset = 1.0f - TimeClose;
	}

		this->Open		()	;

	if ( fTimeOffset != 0.0f ) this->TimeOpen = fTimeOffset;
}																							
																							
//*********************************************************************************
//**																OpenImmediately
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::OpenImmediately( void )
{	
	this->HasOpened	= TRUE;																		
	this->TimeOpen	= 0.0f;													

	this->HasClosed	= FALSE;															// view is closed until it has finished opening process
	this->TimeClose	= 0.0f;
}

//*********************************************************************************
//**																		  Close
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::Close( void )
{			
	if ( this->IsClosed	() )	return;
	if ( this->IsClosing() )	return;

	this->HasClosed	= FALSE;																		
	this->TimeClose	= ::ztimer.GetFrameTimeF()/ztimer.GetMotionFactor();													

	this->HasOpened	= TRUE;															// view is open until it has finished closing process
	this->TimeOpen  = 0.0f;
}																							

//*********************************************************************************
//**																	  CloseSafe
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::CloseSafe( void )
{			
	if ( this->IsOpening() )	this->CloseImmediately();

	if ( this->IsClosed	() )	return;
	if ( this->IsClosing() )	return;

		 this->Close	()	;
}																							

//*********************************************************************************
//**															   CloseImmediately
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::CloseImmediately( void )
{	
	this->HasOpened	= FALSE;																		
	this->TimeOpen	= 0.0f;													

	this->HasClosed	= TRUE;															// view is closed until it has finished opening process
	this->TimeClose	= 0.0f;
}

//*********************************************************************************
//**															   ApplyOpenCloseFX
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::ApplyOpenCloseFX( void )
{			
	if		( this->IsOpening() ) ApplyOpenFX	();
	else if ( this->IsClosing() ) ApplyCloseFX	();
}

//*********************************************************************************
//**																	ApplyOpenFX
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::ApplyOpenFX( void )
{
	//
	//	FINISHED OPENING ?
	//
	if ( this->TimeOpen >= this->DurationOpen ) 
	{
		this->TimeOpen	= 0.0f	;
		this->HasOpened	= TRUE	;
		this->HasClosed = FALSE	;

		return;
	}

	//
	//	APPLY OPEN FX
	//
	if ( ( this->ModeOpen & VIEW_FX_FADE ) == VIEW_FX_FADE ) ApplyOpenFade();
	if ( ( this->ModeOpen & VIEW_FX_ZOOM ) == VIEW_FX_ZOOM ) ApplyOpenZoom();

	//
	//	ADVANCE TIMER
	//
	this->TimeOpen += ::ztimer.GetFrameTimeF()/ztimer.GetMotionFactor();
}

//*********************************************************************************
//**																   ApplyCloseFX
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::ApplyCloseFX( void )
{
	//
	//	FINISHED OPENING ?
	//
	if ( this->TimeClose >= this->DurationClose ) 
	{
		this->TimeClose = 0.0f	;
		this->HasClosed = TRUE	;
		this->HasOpened	= FALSE	;

		return;
	}

	//
	//	APPLY CLOSE FX
	//
	if ( ( this->ModeClose & VIEW_FX_FADE ) == VIEW_FX_FADE ) ApplyCloseFade();
	if ( ( this->ModeClose & VIEW_FX_ZOOM ) == VIEW_FX_ZOOM ) ApplyCloseZoom();

	//
	//	ADVANCE TIMER
	//
	this->TimeClose += ::ztimer.GetFrameTimeF()/ztimer.GetMotionFactor();
}

//*********************************************************************************
//**																  ApplyOpenFade
//*********************************************************************************
//**
//*********************************************************************************

/*	------------------------------------------------------------------
	void zCViewFX::ApplyOpenFade( void )
	26.10.00	[HILDEBRANDT]	
				zFloat2Int eingesetzt, um Compiler Warning (float=>int) auszuschalten
	------------------------------------------------------------------ */

void zCViewFX::ApplyOpenFade( void )
{
	zREAL fPercentage = this->TimeOpen / this->DurationOpen;

	this->SetTextureAlphaBlendFunc	( zRND_ALPHA_FUNC_BLEND				);
	this->SetTextureAlpha			( zFloat2Int(fPercentage * this->TextureAlpha)	);					// DON'T PANIC: Former alpha value will be restored by zCViewDraw::Draw() !!!  
}

//*********************************************************************************
//**																  ApplyOpenZoom
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::ApplyOpenZoom( void )
{	
	//
	//	CALCULATE PERCENTUAL FX "STRENGTH"
	//
	zREAL	fPercentage		 = this->TimeOpen / this->DurationOpen			;

	//
	//	CALCUALTE TEXTURE MODIFICATION
	//
	zPOS	ptSize			 = this->GetPixelSize();
	zVEC2	vecOffset		 = zVEC2( (float) ptSize.X, (float) ptSize.Y )	;
			vecOffset		*= ( 1.0f - fPercentage	)						;
			vecOffset		*= 0.5											;

	this->TextureOffset[0]	+= vecOffset									;
	this->TextureOffset[1]	-= vecOffset									;
}

//*********************************************************************************
//**																 ApplyCloseFade
//*********************************************************************************
//**
//*********************************************************************************

/*	------------------------------------------------------------------
	void zCViewFX::ApplyCloseFade( void )
	26.10.00	[HILDEBRANDT]	
				zFloat2Int eingesetzt, um Compiler Warning (float=>int) auszuschalten
	------------------------------------------------------------------ */

void zCViewFX::ApplyCloseFade( void )
{
	zREAL fPercentage = this->TimeClose / this->DurationClose;

	this->SetTextureAlphaBlendFunc	( zRND_ALPHA_FUNC_BLEND						  );
	this->SetTextureAlpha			( zFloat2Int(( 1.0f - fPercentage ) * this->TextureAlpha) );		// DON'T PANIC: Former alpha value will be restored by zCViewDraw::Draw() !!! 
}

//*********************************************************************************
//**																 ApplyCloseZoom
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::ApplyCloseZoom( void )
{
	//
	//	CALCULATE PERCENTUAL FX "STRENGTH"
	//
	zREAL	fPercentage		= this->TimeClose / this->DurationClose			;

	//
	//	CALCUALTE TEXTURE MODIFICATION
	//
	zPOS	ptSize			 = this->GetPixelSize();
	zVEC2	vecOffset		 = zVEC2( (float) ptSize.X, (float) ptSize.Y )	;
			vecOffset		*= fPercentage									;
			vecOffset		*= 0.5											;

	this->TextureOffset[0]	+= vecOffset									;
	this->TextureOffset[1]	-= vecOffset									;
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
void zCViewFX::Blit( void )
{
	//
	//	RESET TEXTURE MODIFICATIONS
	//
	this->TextureOffset[0]	= zVEC2( 0.0f, 0.0f );
	this->TextureOffset[1]	= zVEC2( 0.0f, 0.0f );

	//
	//	APPLY ACTIVE FX
	//
	this->ApplyOpenCloseFX();

	//
	//	SHOW IT
	//
	if ( this->IsOpen() || this->IsOpening() || this->IsClosing() )
		zCViewDraw::Blit();
}

//*********************************************************************************
//**														EvaluateTexturePosition
//*********************************************************************************
//**
//*********************************************************************************
void zCViewFX::EvaluateTexturePosition( void )
{
	//
	//	CALL BASE CLASS
	//
	zCViewDraw::EvaluateTexturePosition();

	//
	//	MODIFY VALUES ACCORDING TO CURRENT FX
	//
	this->TexturePosition[0] += this->TextureOffset[0];
	this->TexturePosition[1] += this->TextureOffset[1];
}