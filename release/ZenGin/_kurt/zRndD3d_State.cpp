

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_State.cpp
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.99pre
* last modified : 13.11.00
* erstellt      : 02.02.00										
* Compiler OK   : 
*																
*********************************************************************************
- known bugs: 

*********************************************************************************
- possible optimizations: 

*********************************************************************************
- missing features:

*********************************************************************************
- comments:
				28.03.00	Changed DirectX-Error handling (DXTryWarning used)
							Fixed bug in SetFog() (no trafo in [0,1])
							Changed HasCapability() (zRND_CAP_MULTITEXTURE temporary on FALSE ) 
				08.09.00	Integrated workaround for Voodoo cards (disable z-buffer write)
  
TODO:

*********************************************************************************/



#include "zcore.h"
#include "zRndD3D_State.h"






/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetFog( const zBOOL foggy )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetFog( const zBOOL foggy )
{
	//Setze in DirectX die aktuelle Fog-Werte
	if (xd3d_actStatus.fog == foggy) return;

	xd3d_actStatus.fog = foggy;

	if (!this->xd3d_disableFog)
	{
		if( xd3d_actStatus.fog )
		{
			XD3D_SetRenderState( D3DRENDERSTATE_FOGENABLE, TRUE );			

			if (this->xd3d_enableRadialFog)
			{
				XD3D_SetRenderState( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_LINEAR );
			}
			else	
			{
				XD3D_SetRenderState( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_LINEAR );
			}
			
			XD3D_SetRenderState( D3DRENDERSTATE_FOGCOLOR,
				(xd3d_actStatus.fogColor.GetRedByte()<<16)|(xd3d_actStatus.fogColor.GetGreenByte()<<8)|(xd3d_actStatus.fogColor.GetBlueByte()) );

			XD3D_SetRenderState( D3DRENDERSTATE_FOGSTART, *((LPDWORD)( &xd3d_actStatus.nearZ )) );
			XD3D_SetRenderState( D3DRENDERSTATE_FOGEND, *((LPDWORD)( &xd3d_actStatus.farZ )) );

	        if (this->xd3d_enableRadialFog )
				XD3D_SetRenderState( D3DRENDERSTATE_RANGEFOGENABLE,  TRUE);
			else 
				XD3D_SetRenderState( D3DRENDERSTATE_RANGEFOGENABLE,  FALSE);
		}
		else
		{
		    if (this->xd3d_enableRadialFog) 
			{
				XD3D_SetRenderState( D3DRENDERSTATE_RANGEFOGENABLE,  FALSE);
				XD3D_SetRenderState( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_NONE );
			}
			else
				XD3D_SetRenderState( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_NONE );

			XD3D_SetRenderState( D3DRENDERSTATE_FOGENABLE, FALSE );
		}

	} else
	{
			XD3D_SetRenderState( D3DRENDERSTATE_FOGENABLE, FALSE );
	}

}


void	zCRnd_D3D :: SetRadialFog(const zBOOL foggy)
{
	xd3d_enableRadialFog = foggy;
	if (!xd3d_disableFog && xd3d_enableRadialFog) fogType = RADIAL; else
	if (xd3d_disableFog || !xd3d_enableRadialFog) fogType = LINEAR;
	SetFog(FALSE);
	if (!xd3d_disableFog) SetFog(TRUE);
};



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: GetFog() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: GetFog() const 
{
	//Melde zurück, ob der Fog momentan an- oder abgeschaltet ist
	return xd3d_actStatus.fog; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D::SetFogColor( const zCOLOR& col ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D::SetFogColor( const zCOLOR& col )		
{
	//Setze in DirectX die gewünschte Fog-Farbe
	xd3d_actStatus.fogColor = col;
	XD3D_SetRenderState( D3DRENDERSTATE_FOGCOLOR,
		(col.GetRedByte()<<16)|(col.GetGreenByte()<<8)|(col.GetBlueByte()) );
}

void	zCRnd_D3D::SetFogType(const int a_Type)							
{ 
	
	//if (fogType == a_Type) return;

	//if ( (!xd3d_enableRadialFog) || (xd3d_disableFog) ) return;

	if (a_Type == RADIAL)
	{
		XD3D_SetRenderState( D3DRENDERSTATE_FOGTABLEMODE,  D3DFOG_NONE   );
		XD3D_SetRenderState( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_LINEAR );
		XD3D_SetRenderState( D3DRENDERSTATE_RANGEFOGENABLE,  TRUE);
	}
	else if (a_Type == LINEAR)
	{
		// eventuell hier noch die fog near plane anziehen
		XD3D_SetRenderState( D3DRENDERSTATE_RANGEFOGENABLE,  FALSE);
		XD3D_SetRenderState( D3DRENDERSTATE_FOGVERTEXMODE,D3DFOG_NONE   );
		XD3D_SetRenderState( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_LINEAR );
	}


};

/*--------------------------------------------------------------------------
	
	zCOLOR zCRnd_D3D :: GetFogColor() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCOLOR zCRnd_D3D :: GetFogColor() const
{
	//Melde die aktuelle Fog-Farbe zurück
	return xd3d_actStatus.fogColor; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetFogRange( const float nearz, const float farz, const zTRnd_FogMode falloff )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetFogRange( const float nearz, const float farz, const zTRnd_FogMode falloff ) 
{
	//Setze in DirectX die gewüschten Fogstart- und Fogend-Werte
	xd3d_actStatus.nearZ	= nearz;
	xd3d_actStatus.farZ		= farz;
	xd3d_actStatus.fogMode	= falloff;
	XD3D_SetRenderState( D3DRENDERSTATE_FOGSTART, *((LPDWORD)( &xd3d_actStatus.nearZ )) );
	XD3D_SetRenderState( D3DRENDERSTATE_FOGEND, *((LPDWORD)( &xd3d_actStatus.farZ )) );

	if (this->xd3d_enableRadialFog) 
	{
		XD3D_SetRenderState( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_LINEAR );
		XD3D_SetRenderState( D3DRENDERSTATE_RANGEFOGENABLE,  TRUE);
	}
	else XD3D_SetRenderState( D3DRENDERSTATE_FOGTABLEMODE,  D3DFOG_LINEAR );
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: GetFogRange( float& nearz, float& farz, zTRnd_FogMode& falloff )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: GetFogRange( float& nearz, float& farz, zTRnd_FogMode& falloff )
{
	//Melde die aktuellen Fogstart- und Fogend-Werte zurück
	nearz	= xd3d_actStatus.nearZ;
	farz	= xd3d_actStatus.farZ;
	falloff = xd3d_actStatus.fogMode;
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetPolyDrawMode( const zTRnd_PolyDrawMode& drawMode )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetPolyDrawMode( const zTRnd_PolyDrawMode& drawMode ) 
{
	//Setze den gewünschten Darstellungs-Modus (Material, Flat oder Wire)
	polyDrawMode = drawMode; 
}



/*--------------------------------------------------------------------------
	
	zTRnd_PolyDrawMode zCRnd_D3D :: GetPolyDrawMode() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTRnd_PolyDrawMode zCRnd_D3D :: GetPolyDrawMode() const 
{ 
	//Melde den momentan aktiven Darstellungs-Modus zurück (Material, Flat oder Wire)
	return polyDrawMode; 
}



/*--------------------------------------------------------------------------
	
	zvoid zCRnd_D3D :: SetTextureWrapEnabled( const zBOOL b )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetTextureWrapEnabled( const zBOOL b ) 
{ 
	//Aktiviere/Deaktiviere den Texture-Wrap-Modus
	xd3d_actStatus.texwrap = b; 
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: GetTextureWrapEnabled() const 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: GetTextureWrapEnabled() const 
{ 
	//Melde den momentanen Texture-Wrap-Status zurück
	return xd3d_actStatus.texwrap; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetBilerpFilterEnabled( const zBOOL b )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetBilerpFilterEnabled( const zBOOL b ) 
{ 
	//Wechsel zwischen trilinearer (bzw. bilinearer) Filterung und harter Point-Filterung der Textur in DirectX
	xd3d_actStatus.filter = b;
	if( b )
	{		
		if (m_bAnisotropicFilter)
		{
			SetTextureStageState( 0, zRND_TSS_MAGFILTER, D3DTFG_ANISOTROPIC);
			SetTextureStageState( 0, zRND_TSS_MINFILTER, D3DTFN_ANISOTROPIC);
		}
		else
		{
			SetTextureStageState( 0, zRND_TSS_MAGFILTER, D3DTFG_LINEAR );
			SetTextureStageState( 0, zRND_TSS_MINFILTER, D3DTFN_LINEAR );
		}
		SetTextureStageState( 0, zRND_TSS_MIPFILTER, D3DTFP_LINEAR );
		return;
	}
	SetTextureStageState( 0, zRND_TSS_MAGFILTER, D3DTFG_POINT );
	SetTextureStageState( 0, zRND_TSS_MINFILTER, D3DTFN_POINT );
	SetTextureStageState( 0, zRND_TSS_MIPFILTER, D3DTFP_POINT );
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: GetBilerpFilterEnabled() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: GetBilerpFilterEnabled() const 
{ 
	//Meldet den momentan aktiven Textur-Filterungs-Status
	return xd3d_actStatus.filter; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetDitherEnabled( const zBOOL b ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetDitherEnabled( const zBOOL b ) 
{ 
	//Aktiviere/Deaktiviere das Dithering
	xd3d_actStatus.dither = b;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: GetDitherEnabled() const  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: GetDitherEnabled() const 
{ 
	//Meldet den momentan aktiven Dithering-Status
	return xd3d_actStatus.dither; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetPolySortMode( const zTRnd_PolySortMode& smode ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetPolySortMode( const zTRnd_PolySortMode& smode )
{
	//Aktiviere/Deaktiviere den z/w-Buffer in DirectX
	if( smode==zRND_SORT_ZBUFFER ) 
	{
		if( xd3d_wBuffer )
			XD3D_SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );
		else
			XD3D_SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_TRUE );
	}
	else
		XD3D_SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_FALSE );
	polySortMode = smode;
}



/*--------------------------------------------------------------------------
	
	zTRnd_PolySortMode zCRnd_D3D :: GetPolySortMode() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTRnd_PolySortMode zCRnd_D3D :: GetPolySortMode() const
{
	//Melde den aktuellen z/w-Buffer-Status
	return polySortMode;
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetZBufferWriteEnabled( const zBOOL flag ) 

 

    08-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetZBufferWriteEnabled( const zBOOL flag )	
{ 
	//Aktiviere/Deaktiviere den schreibenden Zugriff auf den z/w-Buffer in DirectX
	xd3d_actStatus.zwrite = flag;
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, flag );
}



/*--------------------------------------------------------------------------
	
	zBOOL	zCRnd_D3D :: GetZBufferWriteEnabled() const

 

    08-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL	zCRnd_D3D :: GetZBufferWriteEnabled() const
{ 
	//Melde den aktuellen Schreibzugriff-Status des z/w-Buffer
	return xd3d_actStatus.zwrite; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetZBufferCompare( const zTRnd_ZBufferCmp& zcmp )

 

    08-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetZBufferCompare( const zTRnd_ZBufferCmp& zcmp ) 
{
	//Setze die z/w-Buffer-Vergleichsfunktion in DirectX
	xd3d_actStatus.zfunc = zcmp;
	switch( zcmp ) 
	{
	case	zRND_ZBUFFER_CMP_LESS:
			xd3d_actStatus.zd3dfunc = D3DCMP_LESS;
			break;
	case	zRND_ZBUFFER_CMP_ALWAYS:
			xd3d_actStatus.zd3dfunc = D3DCMP_ALWAYS;
			break;
	case	zRND_ZBUFFER_CMP_NEVER:
			xd3d_actStatus.zd3dfunc = D3DCMP_NEVER;
			break;
	case	zRND_ZBUFFER_CMP_LESS_EQUAL:
	default:
			xd3d_actStatus.zd3dfunc = D3DCMP_LESSEQUAL;
	}
	XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, xd3d_actStatus.zd3dfunc );
}



/*--------------------------------------------------------------------------
	
	zTRnd_ZBufferCmp zCRnd_D3D :: GetZBufferCompare()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTRnd_ZBufferCmp zCRnd_D3D :: GetZBufferCompare() 
{ 
	//Melde die aktuelle z/w-Buffer-Vergleichsfunktion zurück
	return xd3d_actStatus.zfunc; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetPixelWriteEnabled(const zBOOL flag )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetPixelWriteEnabled(const zBOOL flag ) 
{
	//PixelWriteEnable steht im D3D-Renderer immer auf TRUE
	xd3d_actStatus.fenable = TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL	zCRnd_D3D :: GetPixelWriteEnabled() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL	zCRnd_D3D :: GetPixelWriteEnabled() const
{
	//Melde PixelWriteEnable immer als TRUE zurück
	return xd3d_actStatus.fenable; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetAlphaBlendSource( const zTRnd_AlphaBlendSource &src )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetAlphaBlendSource( const zTRnd_AlphaBlendSource &src )		
{
	//Setze die global im D3D-Renderer aktive Alpha-Source (Material oder Constant)
	xd3d_actStatus.alphasrc = src;
}



/*--------------------------------------------------------------------------
	
	zTRnd_AlphaBlendSource zCRnd_D3D :: GetAlphaBlendSource() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTRnd_AlphaBlendSource zCRnd_D3D :: GetAlphaBlendSource() const 
{
	//Melde die aktuell als global aktive gesetzte Alpha-Source
	return xd3d_actStatus.alphasrc;
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetAlphaBlendFunc( const zTRnd_AlphaBlendFunc &mode )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetAlphaBlendFunc( const zTRnd_AlphaBlendFunc &mode )		
{
	xd3d_actStatus.alphafunc = mode;
}



/*--------------------------------------------------------------------------
	
	zTRnd_AlphaBlendFunc zCRnd_D3D :: GetAlphaBlendFunc() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTRnd_AlphaBlendFunc zCRnd_D3D :: GetAlphaBlendFunc() const
{
	return xd3d_actStatus.alphafunc; 
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetAlphaBlendFactor( const float &percentage )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetAlphaBlendFactor( const float &percentage )		
{
	xd3d_actStatus.alphafactor = percentage;
}



/*--------------------------------------------------------------------------
	
	float zCRnd_D3D :: GetAlphaBlendFactor() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
float zCRnd_D3D :: GetAlphaBlendFactor() const
{
	return xd3d_actStatus.alphafactor; 
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SupportAlphaTesting()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SupportAlphaTesting()
{
	return xd3d_alphaTest;
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: SetRenderMode( const zTRnd_RenderMode rmode )

 

    08-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetRenderMode( const zTRnd_RenderMode rmode )
{
	xd3d_renderMode = rmode;
	switch( xd3d_renderMode )
	{
	case	zRND_MODE_2_PASS_LIGHTMAP:
			if( xd3d_actStatus.renderMode!=zRND_MODE_2_PASS_LIGHTMAP )
			{
				SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_CLAMP );
				SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_CLAMP );
				xd3d_actStatus.zwrite = FALSE;
				XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
				SetZBufferCompare(zRND_ZBUFFER_CMP_LESS_EQUAL );
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR );
				XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO );
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_ADD );
				SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
				SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE );
				xd3d_actStatus.renderMode = zRND_MODE_2_PASS_LIGHTMAP;
			}
			break;
	default:
			SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_WRAP );
			SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_WRAP );
			xd3d_actStatus.zwrite = TRUE;
			XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
			SetZBufferCompare( zRND_ZBUFFER_CMP_LESS );
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
			SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
			SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
			SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE ); 
			xd3d_actStatus.renderMode = zRND_MODE_1_PASS_VERT_LIGHT;
	}
}



/*--------------------------------------------------------------------------
	
	zTRnd_RenderMode zCRnd_D3D :: GetRenderMode() const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTRnd_RenderMode zCRnd_D3D :: GetRenderMode() const
{
	return xd3d_renderMode; 
}



/*--------------------------------------------------------------------------
	
	int zCRnd_D3D :: HasCapability( const zTRnd_Capability c ) const

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int zCRnd_D3D :: HasCapability( const zTRnd_Capability c ) const
{
	switch( c ) 
	{
	case	zRND_CAP_GUARD_BAND:	
			if( xd3d_Capabilities.guardband )
				return 1;
			return 0;
	case	zRND_CAP_ALPHATEST:
			if( xd3d_Capabilities.alphatest )
				return 1;
			return 0;
	case	zRND_CAP_MAX_BLEND_STAGES:
			return xd3d_Capabilities.num_stages;
	case	zRND_CAP_MAX_BLEND_STAGE_TEXTURES:
			if( ((xd3d_deviceIdentifier.dwVendorId==4098)&&(xd3d_deviceIdentifier.dwDeviceId==18242))||	//RAGE-PRO
				((xd3d_deviceIdentifier.dwVendorId==4139)&&(xd3d_deviceIdentifier.dwDeviceId==1313)) )	//G200
				return 1;
			return xd3d_Capabilities.num_texstages;
	case	zRND_CAP_TNL:
			if( xd3d_Capabilities.tnl )
				return 1;
			return 0;
	case	zRND_CAP_TNL_HARDWARE:
			if( xd3d_Capabilities.tnl_hardware )
				return 1;
			return 0;
	case	zRND_CAP_TNL_MAXLIGHTS:
			if( xd3d_Capabilities.tnl_maxlights>0 )
				return xd3d_Capabilities.tnl_maxlights;
			return 8;
	case	zRND_CAP_DEPTH_BUFFER_PREC:
			switch( xd3d_zwBufferLevel )
			{
			case	zRND_W32_BUFFER:
					return -32;
			case	zRND_W24_BUFFER:
					return -24;
			case	zRND_W16_BUFFER:
					return -16;
			case	zRND_Z32_BUFFER:
					return 32;
			case	zRND_Z24_BUFFER:
					return 24;
			case	zRND_Z16_BUFFER:
			default:
					return 16;
			}
			return 16;
	case	zRND_CAP_DIFFUSE_LAST_BLEND_STAGE_ONLY:
			if( (xd3d_deviceIdentifier.dwVendorId==4634)&&(xd3d_deviceIdentifier.dwDeviceId==5) ) //VOODOO-3
				return 1;
			return 0;
	case	zRND_CAP_BLENDDIFFUSEALPHA:
			return xd3d_Capabilities.blendDiffuseAlpha;
			break;
	}

	return FALSE;
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: ResetZTest()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: ResetZTest()										
{
	return;
}



/*--------------------------------------------------------------------------
	
	int zCRnd_D3D :: HasPassedZTest()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int zCRnd_D3D :: HasPassedZTest()										
{
	return 0;	
}

int zCRnd_D3D :: GetZBias()	const									
{
	return xd3d_actStatus.zbias;	
}


void zCRnd_D3D :: SetZBias(const int a_z)										
{
	if (a_z == xd3d_actStatus.zbias) return;
	XD3D_SetRenderState(D3DRENDERSTATE_ZBIAS, a_z);
	xd3d_actStatus.zbias = a_z;	
}


/*--------------------------------------------------------------------------
	
	zWORD zCRnd_D3D :: GetTexturePortableBinaryVersion()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zWORD zCRnd_D3D :: GetTexturePortableBinaryVersion()
{
	return 0;		
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: GetGuardBandBorders( float& guardBandLeft, float& guardBandTop, float& guardBandRight, float& guardBandBottom )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: GetGuardBandBorders( float& guardBandLeft, float& guardBandTop, float& guardBandRight, float& guardBandBottom )
{
	if( xd3d_Capabilities.guardband )
	{
		guardBandLeft	= xd3d_Capabilities.guardbandleft;
		guardBandRight	= xd3d_Capabilities.guardbandright;
		guardBandTop	= xd3d_Capabilities.guardbandtop;
		guardBandBottom = xd3d_Capabilities.guardbandbottom;
	} 
	else
	{	guardBandLeft	= 0.0f;
		guardBandRight	= 0.0f;
		guardBandTop	= 0.0f;
		guardBandBottom = 0.0f;
	}
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: GetStatistics( zTRnd_Stats &stat )

 

    14-Aug-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					Obsolete Felder entfernt

--------------------------------------------------------------------------*/
void zCRnd_D3D :: GetStatistics( zTRnd_Stats &stat ) 
{
	xd3d_statistics.texMemUsed			= -1;
	xd3d_statistics.texMemFetched		= -1;
	xd3d_statistics.numTexturesFetched	= -1;
	xd3d_statistics.numTexturesUsed		= xd3d_numTexturesUsedThisFrame;
	xd3d_statistics.numLightmapsUsed	= xd3d_numLightmapsUsedThisFrame;
	stat = xd3d_statistics;
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D::ResetStatistics()

 

    14-Aug-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					Feld wird nun korrekt ueber memset geloescht
--------------------------------------------------------------------------*/

void zCRnd_D3D::ResetStatistics() 
{ 
	memset (&xd3d_statistics, 0, sizeof(xd3d_statistics));
}