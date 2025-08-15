/******************************************************************************** 
 
     $Workfile:: zViewDraw.cpp        $                $Date:: 16.02.01 14:01   $
     $Revision:: 14                   $             $Modtime:: 16.02.01 13:55   $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Roman/zViewDraw.cpp $
 * 
 * 14    16.02.01 14:01 Moos
 * Noch mehr Runterfahr-Crashfixes
 * 
 * 13    9.01.01 13:21 Keskenti
 * Replaced #include "" with #include <>
 * 
 * 12    13.12.00 19:52 Hildebrandt
 * fixed bad zCLASS_DEFINITION,  zCViewDraw is derived from zCViewObject,
 * not zCViewBase
 * 
 * 11    28.11.00 12:37 Keskenti
 * 
 * 10    21.10.00 19:08 Moos
 * 
 * 9     20.10.00 19:08 Keskenti
 * 
 * 8     19.10.00 18:54 Keskenti
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

//
//---------------------------------------------------------------------------------
//****************************     CON/DESTRUCTION     ****************************
//---------------------------------------------------------------------------------
//

zCLASS_DEFINITION ( zCViewDraw, zCViewObject, 0 ,0 )

//*********************************************************************************
//**																	Constructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewDraw::zCViewDraw()
{
	this->TextureFuncAlpha		= zRND_ALPHA_FUNC_NONE;
	this->Texture				= NULL;
	this->TextureColor			= zCOLOR( 0xff, 0xff, 0xff, 0xff );
	this->TextureAlpha			= 255;
	this->TexturePosition[0]	= zVEC2( 0.0f, 0.0f );
	this->TexturePosition[1]	= zVEC2( 0.0f, 0.0f );
}

//*********************************************************************************
//**																	 Destructor
//*********************************************************************************
//**
//*********************************************************************************
zCViewDraw::~zCViewDraw()
{
	zRELEASE( this->Texture );
}

//
//---------------------------------------------------------------------------------
//*******************************     HIERARCHY     *******************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																	RemoveChild
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::RemoveChild( zSTRING& strTexture )
{
	//
	//	RELEASE CHILDREN
	//
	zCViewObject*	pView		= NULL;
	zCViewDraw*		pViewDraw	= NULL;
	int				nViews		= this->ListChildren.GetNumInList();

	while( nViews )
	{
		pView = this->ListChildren[ --nViews ];
		if ( pView )
		{
			pViewDraw = dynamic_cast< zCViewDraw* > ( pView );
			if ( pViewDraw->GetTexture()->GetName() == strTexture )
			{
				zCViewObject::RemoveChild( pView );
//				this->RemoveChild( pView );
			}
		}
	}
}

//
//---------------------------------------------------------------------------------
//********************************     GET/SET     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**													   SetTextureAlphaBlendFunc
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::SetTextureAlphaBlendFunc( const zTRnd_AlphaBlendFunc &funcAlphaBlend )
{
	this->TextureFuncAlpha = funcAlphaBlend;
}

//*********************************************************************************
//**																	 SetTexture
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::SetTexture( const zSTRING& strTexture )				
{
	if ( strTexture.IsEmpty() ) return;
	
	zRELEASE( this->Texture );
	this->Texture = zCTexture::Load( (zSTRING) strTexture, zTEX_LOAD_FLAG_TILE );
}

//*********************************************************************************
//**																	 SetTexture
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::SetTexture( zCTexture* pTexture )						
{
	if ( pTexture )
	{
		//
		//	RELEASE CURRENT TEXTURE
		//
		zRELEASE( this->Texture );

		//
		//	SET NEW TEXTURE
		//
		this->Texture = pTexture;

		//
		//	PROTECT TEXTURE FROM DELETION
		//
		this->Texture->AddRef();
	}
}

//*********************************************************************************
//**															    SetTextureColor
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::SetTextureColor( const zCOLOR& colTexture )				
{
	this->TextureColor = colTexture;
}

//*********************************************************************************
//**															    SetTextureAlpha
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::SetTextureAlpha( int nAlpha )								
{
	this->TextureAlpha = nAlpha;
}

////////////////////////////////////////////////////////////////////////////////
//
// Cache in texture
//
////////////////////////////////////////////////////////////////////////////////

void zCViewDraw::TextureCacheIn( zREAL priority )								
{
	if (this->Texture)
		this->Texture->CacheIn(priority);
}

//
//---------------------------------------------------------------------------------
//********************************     DRAWING     ********************************
//---------------------------------------------------------------------------------
//

//*********************************************************************************
//**																		 Render
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::Render( void )
{
	this->Draw();
}

//*********************************************************************************
//**																		   Draw
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::Draw( void )
{
	//
	//	STORE RENDERER SETTINGS
	//
	zBOOL					bWasEnabledFilter		= zrenderer	->GetBilerpFilterEnabled();
	zBOOL					bWasEnabledDepthBuffer	= zrenderer	->GetZBufferWriteEnabled();
	zTRnd_ZBufferCmp		funcDepthBufferCompare	= zrenderer	->GetZBufferCompare		();
	zTRnd_AlphaBlendFunc	funcAlphaBlend			= zrenderer	->GetAlphaBlendFunc		();
	int						nAlpha					= this		->GetTextureAlpha		();

	//
	//	BLIT SELF
	//
	this->Blit							();

	//
	//	RESTORE RENDERER SETTINGS
	//
	zrenderer->SetAlphaBlendFunc		( funcAlphaBlend			);
	zrenderer->SetZBufferCompare		( funcDepthBufferCompare	);
	zrenderer->SetZBufferWriteEnabled	( bWasEnabledDepthBuffer	);
	zrenderer->SetBilerpFilterEnabled	( bWasEnabledFilter			);
	this	 ->SetTextureAlpha			( nAlpha					);

	//
	//	DRAW CHILDREN
	//
	this->DrawChildren	();
}

//*********************************************************************************
//**																   DrawChildren
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::DrawChildren( void )
{
	zCViewBase* pView		= NULL;
	zCViewDraw* pViewDraw	= NULL;
	int			nViews		= this->ListChildren.GetNumInList();

	while( nViews )
	{
		pView		= this->ListChildren[ --nViews ];
		pViewDraw	= dynamic_cast< zCViewDraw* > ( pView );

		if ( pViewDraw ) 
			 pViewDraw->Draw();
	}
}

//*********************************************************************************
//**																		   Blit
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::Blit( void )
{
	//
	//	SETUP RENDER SETTINGS
	//
	zrenderer->SetAlphaBlendFunc		( this->TextureFuncAlpha	);
	zrenderer->SetZBufferCompare		( zRND_ZBUFFER_CMP_ALWAYS	);
	zrenderer->SetZBufferWriteEnabled	( FALSE						);
	zrenderer->SetBilerpFilterEnabled	( TRUE						);

	//
	//	BLIT TEXTURE
	//
	if ( this->Texture )				this->BlitTexture();
}

//*********************************************************************************
//**																	BlitTexture
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::BlitTexture( void )
{
	//
	//	GET TEXTURE COORDINATES
	//
	zVEC2	vecUV	[2];
			vecUV	[0] = zVEC2( 0.0f, 0.0f );
			vecUV	[1] = zVEC2( 1.0f, 1.0f );

	//
	//	EVALUATE EFFECTIVE TEXTURE PIXEL COORIDNATES
	//
	this->EvaluateTexturePosition	();

	//
	//	MODIFY TEXTURE COLOR
	//
	this->TextureColor.SetAlphaByte	( this->TextureAlpha );

	//
	//	DRAW TEXTURE
	//

	zREAL farZ;
	if (zCCamera::activeCam) farZ = zCCamera::activeCam->GetNearClipZ()+1;
	else					 farZ = 1;

	zrenderer -> DrawTile			(	this->Texture			, 
										this->TexturePosition[0], 
										this->TexturePosition[1],	
										farZ					, 
										vecUV[0]				, 
										vecUV[1]				, 
										this->TextureColor 
									);		
}

//*********************************************************************************
//**														EvaluateTexturePosition
//*********************************************************************************
//**
//*********************************************************************************
void zCViewDraw::EvaluateTexturePosition( void )
{
	//
	//	GET PIXEL POSITION
	//
	zPOS	ptPos	[2];
			ptPos   [0] = this->GetPixelPosition();
			ptPos	[1] = this->GetPixelSize	();	ptPos[1] += ptPos[0];

	//
	//	CONVERT TO 2D FLOAT VECTOR
	//
	this->TexturePosition[0] = zVEC2( (float) ptPos[0].X, (float) ptPos[0].Y );
	this->TexturePosition[1] = zVEC2( (float) ptPos[1].X, (float) ptPos[1].Y );
}

//*********************************************************************************
//**														              GetScreen
//*********************************************************************************
//**
//*********************************************************************************
static zCViewDraw *theScreen=NULL;

zCViewDraw& zCViewDraw::GetScreen( void )
{
	if ( ! theScreen && zrenderer) 
	{ 
        theScreen = zNEW(zCViewDraw);
		theScreen->SetVirtualSize( zPOS( zCViewBase::ViewVirtualWidth, zCViewBase::ViewVirtualHeight ) ); 
	}

	return *theScreen;
}

// [Moos] theScreen muss irgendwann auch abgebaut werden.
void zCViewDraw::CleanupScreen()
{
    zRELEASE(theScreen);
}

