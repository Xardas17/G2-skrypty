

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_Vid.cpp
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.97pre
* last modified : 20.10.00
* erstellt      : 20.10.00										
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
		  
TODO:

*********************************************************************************/



#include "zcore.h"
#include "zoption.h"
#include "zRndD3D_Vid.h"
#include "zWin32.h"



#ifndef LocLerp
#define LocLerp(t, a, b) ( a + t * (b - a) ) 
#endif




// #define _NOVSYNC

/*--------------------------------------------------------------------------

    void zCRnd_D3D :: Vid_Blit( int x,int y ) 

 

    14-Sep-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					Separates xd3d_polysRendered und xd3d_trisRendered entferent (=> nun komplett in xd3d_statistics)
--------------------------------------------------------------------------*/ 

void zCRnd_D3D :: Vid_Blit( zBOOL forceFlip, RECT *sourceRect, RECT *destRect )
{
	//Beende die aktuelle Scene
	if( xd3d_pd3dDevice7&&xd3d_inScene )
	{
		xd3d_pd3dDevice7->EndScene();
		xd3d_inScene = FALSE;
	}
//	xd3d_statistics.numPolysRendered	= xd3d_polysRendered; 
//	xd3d_statistics.numTrisRendered		= xd3d_trisRendered;

	//Falls nur Simple-Polys gerendert wurden, so warte auf das Vertical-Blank-Signal (um Queuestaus zu vermeiden)
	if( xd3d_statistics.numPolysRendered==0 )
		xd3d_pdd7->WaitForVerticalBlank( DDWAITVB_BLOCKBEGIN, NULL );

	// Blit wird ab hier eingeleitet
	if( xd3d_pd3dx )
	{
		while( zCRnd_D3D::xd3d_dd7inuse )
		{
			zERR_MESSAGE(5,0, "X: DirectDraw Vid_Blit out of sync !" );
			Sleep( 0 );
		}
		zCRnd_D3D::xd3d_dd7inuse = FALSE;zCRnd_D3D::xd3d_dd7inuse = TRUE;
		if( forceFlip||(xd3d_mode==zRND_SCRMODE_WINDOWED) )
		{
			#ifdef _NOVSYNC
			xd3d_pd3dx->UpdateFrame( D3DX_UPDATE_NOVSYNC );		// kein Warten auf Sync		
			#else	 	
			xd3d_pd3dx->UpdateFrame( 0 );		// Default je nach Karte (meist: auf Sync warten)		
			#endif
		}
		else
		{
			xd3d_pfrontBuffer->Blt( destRect, xd3d_pbackBuffer, sourceRect, DDBLT_WAIT, NULL );
		}
		zCRnd_D3D::xd3d_dd7inuse = FALSE;
	}
	else zERR_WARNING( "X: Vid_Blit: Don't use Vid_Blit after releasing D3DX !" );

	//Beginne eine neue Scene
	if( xd3d_pd3dDevice7&&!xd3d_inScene )
	{
		xd3d_pd3dDevice7->BeginScene();
		xd3d_inScene = TRUE;
	}
//	xd3d_polysRendered = 0;
//	xd3d_trisRendered = 0;
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D::Vid_Lock( zTRndSurfaceDesc &surfdesc ) 

    16-Sep-00       [PELZER]
	19-Oct-00		[HILDEBRANDT]
					hwnd aus zTRndSurfaceDesc entfernt
--------------------------------------------------------------------------*/

zBOOL zCRnd_D3D::Vid_Lock( zTRndSurfaceDesc &surfdesc ) 
{
	if( !xd3d_backlocked )
	{
		DDSURFACEDESC2 ddsd;
		ZeroMemory( &ddsd, sizeof( ddsd ) );
		ddsd.dwSize = sizeof( DDSURFACEDESC2 );
		if( !DXTryWarning( xd3d_pbackBuffer->Lock( NULL, &ddsd, DDLOCK_NOSYSLOCK|DDLOCK_WAIT|DDLOCK_WRITEONLY, NULL ), 
				"X: Vid_Lock: Can't lock the back buffer surface !" ) )
			return FALSE;
		surfdesc.pSurface = ddsd.lpSurface;
		surfdesc.bytePitch = ddsd.lPitch;
		surfdesc.pixelWidth = ddsd.dwWidth;
		surfdesc.pixelHeight = ddsd.dwHeight;
		surfdesc.bitRGBCount = ddsd.ddpfPixelFormat.dwRGBBitCount;
		surfdesc.bitRMask = ddsd.ddpfPixelFormat.dwRBitMask;
		surfdesc.bitGMask = ddsd.ddpfPixelFormat.dwGBitMask;
		surfdesc.bitBMask = ddsd.ddpfPixelFormat.dwBBitMask;
		xd3d_backlocked = TRUE;
		return TRUE;
	}

	return FALSE;
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D::Vid_Unlock() 

 

    16-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D::Vid_Unlock() 
{
	if( xd3d_backlocked ) 
	{
		xd3d_pbackBuffer->Unlock( NULL );
		xd3d_backlocked = FALSE;
		return TRUE;
	}

	return FALSE;
}



/*--------------------------------------------------------------------------

    zBOOL Vid_GetFrontBufferCopy( zCTextureConvert &frontcopy ) 

 

    16-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D::Vid_GetFrontBufferCopy( zCTextureConvert &frontcopy ) 
{
	DDSURFACEDESC2 ddsd;
	ZeroMemory( &ddsd, sizeof( ddsd ) );
	ddsd.dwSize = sizeof( DDSURFACEDESC2 );
	if( !DXTryWarning( xd3d_pbackBuffer->Lock( NULL, &ddsd, DDLOCK_NOSYSLOCK|DDLOCK_WAIT|DDLOCK_READONLY, NULL ), 
			"X: Vid_GetFrontBufferCopy: Can't lock the back buffer surface !" ) )
		return FALSE;
	zCTextureInfo texInfo;
	texInfo.averageColor = 0x00000000;
	texInfo.numMipMap = 1;
	texInfo.refSizeX = ddsd.dwWidth;
	texInfo.refSizeY = ddsd.dwHeight;
	texInfo.sizeX = ddsd.dwWidth;
	texInfo.sizeY = ddsd.dwHeight;
	texInfo.texFormat = zRND_TEX_FORMAT_COUNT;
	switch( ddsd.ddpfPixelFormat.dwRGBBitCount )
	{
	case	32:	
			switch( ddsd.ddpfPixelFormat.dwRBitMask )
			{
			case	0x000000ff:
					texInfo.texFormat = zRND_TEX_FORMAT_RGBA_8888;
					break;
			case	0x0000ff00:
					texInfo.texFormat = zRND_TEX_FORMAT_ARGB_8888;
					break;
			case	0x00ff0000:
					texInfo.texFormat = zRND_TEX_FORMAT_BGRA_8888;
					break;
			case	0xff000000:
					texInfo.texFormat = zRND_TEX_FORMAT_ABGR_8888;
					break;
			}
			break;
	case	24:
			switch( ddsd.ddpfPixelFormat.dwRBitMask )
			{
			case	0x0000ff:
					texInfo.texFormat = zRND_TEX_FORMAT_RGB_888;
					break;
			case	0xff0000:
					texInfo.texFormat = zRND_TEX_FORMAT_BGR_888;
					break;
			}
			break;
	case	16:	
			switch( ddsd.ddpfPixelFormat.dwRBitMask )
			{
			case	0x0f00:
					texInfo.texFormat = zRND_TEX_FORMAT_ARGB_4444;
					break;
			case	0xec00:
					texInfo.texFormat = zRND_TEX_FORMAT_ARGB_1555;
					break;
			case	0xf800:
					texInfo.texFormat = zRND_TEX_FORMAT_RGB_565;
					break;
			}
			break;
	}
	if( texInfo.texFormat==zRND_TEX_FORMAT_COUNT )
	{
		xd3d_pbackBuffer->Unlock( NULL );
		zERR_WARNING( "X: Vid_GetFrontBufferCopy: Illegal pixel format." );
		return FALSE;
	}
	frontcopy.SetTextureInfo( texInfo );
	void *dbuffer = NULL;
	int destPitchXBytes = 0;
	if( !frontcopy.GetTextureBuffer( 0, dbuffer, destPitchXBytes ) ) //erste MipMap
	{
		xd3d_pbackBuffer->Unlock( NULL );
		return FALSE;
	}
	for( int h = 0; h<ddsd.dwHeight; h++ )
	{
		switch (ddsd.ddpfPixelFormat.dwRGBBitCount)
		{
			case 32: memcpy( (unsigned char*)dbuffer+h*destPitchXBytes, (unsigned char*)ddsd.lpSurface+h*ddsd.lPitch, ddsd.dwWidth * 4);break;
			case 24: memcpy( (unsigned char*)dbuffer+h*destPitchXBytes, (unsigned char*)ddsd.lpSurface+h*ddsd.lPitch, ddsd.dwWidth * 3);break;
			case 16: memcpy( (unsigned char*)dbuffer+h*destPitchXBytes, (unsigned char*)ddsd.lpSurface+h*ddsd.lPitch, ddsd.dwWidth * 2);break;
		}
	}
	xd3d_pbackBuffer->Unlock( NULL );

	return TRUE; 
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D::Vid_Clear( zCOLOR &col, int clearTarget ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D::Vid_Clear( zCOLOR &col, int clearTarget )
{
	//Bereinigung des RGB- und/oder des z-Buffers
	long clearFlags;
	switch( clearTarget )
	{
	case	zRND_CLEAR_FRAMEBUFFER:
			clearFlags = D3DCLEAR_TARGET;
			break;
	case	zRND_CLEAR_ZBUFFER:
			clearFlags = D3DCLEAR_ZBUFFER;
			// ab 1.12d: Stencil wird beim Löschen des FBs auch gecleart
			// soll angeblich auch NVIDIA Karten schneller sein.
			// TODO: Auf anderen Karten testen & schauen ob der Stencil Clear auch
			// beim Löschen des FBs Performance bringt
			//if (xd3d_Capabilities.hasStencil) clearFlags |= D3DCLEAR_STENCIL;
			break;
	default:
			clearFlags = D3DCLEAR_ZBUFFER|D3DCLEAR_TARGET;
	}

	if( xd3d_pd3dx )
	{
		DXTryWarning( xd3d_pd3dx->SetClearDepth( 1.0f ), 
			"X: [RND3D]Vid_Clear: Can't set clear depth !" );
		DXTryWarning( xd3d_pd3dx->SetClearColor( col.GetPackedDWord() ), 
			"X: [RND3D]Vid_Clear: Can't set clear color !" );
		DXTryWarning( xd3d_pd3dx->Clear( clearFlags ), 
			"X: [RND3D]Vid_Clear: Can't clear render target !" );
	}
}



/*--------------------------------------------------------------------------

    int zCRnd_D3D :: Vid_GetNumDevices()  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int zCRnd_D3D :: Vid_GetNumDevices() 
{	
	//Rückgabe der Anzahl der zur Verfügung stehenden Devices
	return xd3d_actStatus.devmax; 
}



/*--------------------------------------------------------------------------

    int	zCRnd_D3D :: Vid_GetActiveDeviceNr()  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int	zCRnd_D3D :: Vid_GetActiveDeviceNr() 
{ 
	//Rückgabe der Nummer der derzeit aktiven Device
	return xd3d_actStatus.devnum; 
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D :: Vid_SetDevice( int deviceNr )  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: Vid_SetDevice( int deviceNr ) 
{		
	//Wechsel zu einer anderen Device
	if( xd3d_tryDevnum==deviceNr ) 
	{
		zERR_MESSAGE(5,0, "X: Vid_SetDevice: No changes ..." );
		return TRUE;
	}
	if( (deviceNr>=0)&&(deviceNr<xd3d_actStatus.devmax) )
	{
		zERR_MESSAGE(5,0, "X: Vid_SetDevice: Change device to:"+zSTRING(dxDevice[deviceNr].DeviceName) );
		xd3d_tryDevnum = deviceNr;
		return TRUE; 
	}
	zERR_MESSAGE(5,0, "X: Vid_SetDevice: Illegal devicenumber" );

	return FALSE; 
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D::Vid_GetDeviceInfo( zTRnd_DeviceInfo& deviceInfo, int deviceNr )  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D::Vid_GetDeviceInfo( zTRnd_DeviceInfo& deviceInfo, int deviceNr )
{
	//Rückgabe der Namens-Textmeldung zur gewünschten Device
	if( deviceNr>=xd3d_actStatus.devmax )
	{	
		zERR_MESSAGE(5,0, "X: Vid_GetDeviceInfo: Wrong devicenumber: " + zSTRING(deviceNr) );
		return FALSE;
	}
	deviceInfo.deviceName = zSTRING( dxDevice[deviceNr].DeviceName );

	return TRUE;
}



/*--------------------------------------------------------------------------

    int zCRnd_D3D ::Vid_GetNumModes()  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int zCRnd_D3D ::Vid_GetNumModes() 
{	
	//Rückgabe der Modes-Anzahl zur momentan aktiven Device 
	return dxDeviceModeNum[xd3d_actStatus.devnum];
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D ::Vid_GetModeInfo( zTRnd_VidModeInfo& modeInfo, int modeNr )  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D ::Vid_GetModeInfo( zTRnd_VidModeInfo& modeInfo, int modeNr ) 
{	
	//Rückgabe der Informationen zur angegebenen Mode-Nummer der momentan aktiven Device
	if( modeNr>=dxDeviceModeNum[xd3d_actStatus.devnum] )
	{	
		zERR_WARNING( "X: "+zSTRING(modeNr)+"illegal modenumber, correct to highest possible" );
		return FALSE;
	}
	modeInfo.xdim			= dxDeviceMode[xd3d_actStatus.devnum][modeNr].w; 
	modeInfo.ydim			= dxDeviceMode[xd3d_actStatus.devnum][modeNr].h; 
	modeInfo.bpp			= dxDeviceMode[xd3d_actStatus.devnum][modeNr].bpp;
	modeInfo.fullscreenOnly = !xd3d_Capabilities.window;
 
	return TRUE; 
}



/*--------------------------------------------------------------------------

    int	zCRnd_D3D ::Vid_GetActiveModeNr()  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int	zCRnd_D3D ::Vid_GetActiveModeNr() 
{
	//Rückmeldung der Nummer des momentan aktiven Modes
	return xd3d_actStatus.modeNr; 
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D ::Vid_SetMode( int modeNr, zTSystemContextHandle *winHandle )  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D ::Vid_SetMode( int modeNr, zTSystemContextHandle *winHandle ) 
{
	if( winHandle!=0 )
		xd3d_newWinHandle = *((HWND*)winHandle);
	//Wechsel zu einem neuen Mode per Mode-Nummer
	if( modeNr>=dxDeviceModeNum[xd3d_actStatus.devnum] )
	{	
		zERR_WARNING( "X: "+zSTRING(modeNr)+"illegal modenumber, correct to highest possible" );
		modeNr = dxDeviceModeNum[xd3d_actStatus.devnum];
	}

	if( XD3D_SetMode( dxDeviceMode[xd3d_actStatus.devnum][modeNr].w, 
						dxDeviceMode[xd3d_actStatus.devnum][modeNr].h, 
						dxDeviceMode[xd3d_actStatus.devnum][modeNr].bpp ) )
	{
		xd3d_actStatus.modeNr = modeNr;
		return TRUE;
	}

	return FALSE;
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D :: XD3D_SetMode( int x, int y, int bpp )  

 

    24-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: XD3D_SetMode( int x, int y, int bpp )
{	
	zERR_MESSAGE (4, zERR_BEGIN, "X: RND_D3D: SetMode ..");

	//Wechsel zu einem neuen Mode per Auflösung und Bittiefe
	zBOOL	result = TRUE;
	vid_xdim = x;
	vid_ydim = y;
	if( (xd3d_scrWidth==x)&&(xd3d_scrHeight==y)&&(xd3d_scrBpp==bpp) ) 
	{
		zERR_MESSAGE(5,0, "X: Vid_SetMode: No changes ..." );
		result = TRUE;
	} else
	{
		xd3d_scrWidth	= x;
		xd3d_scrHeight	= y;
		xd3d_scrBpp		= bpp;
		XD3D_CreateWin( x, y, bpp );
		if( XD3D_SetDevice( xd3d_tryDevnum, x, y, bpp, xd3d_scrMode )==FALSE )
		{	
			zERR_WARNING( "X: Vid_SetMode: SetD3Ddevice failed !" );
			result = FALSE;
		} else
		{
			xd3d_scrStatus = scrSTATUS_Used;
		};
	};


	if (xd3d_scrMode == zRND_SCRMODE_WINDOWED) sysKillWindowsKeys(false);
	else									   sysKillWindowsKeys(true);

	zERR_MESSAGE (4, zERR_END, "");
	return result;
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: Vid_SetScreenMode( zTRnd_ScreenMode mode )  

 

    24-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: Vid_SetScreenMode( zTRnd_ScreenMode mode ) 
{
	//Wechsel zwischen Fullscreen und Windowed
	if( mode==zRND_SCRMODE_HIDE )
		mode = zRND_SCRMODE_WINDOWED;
	if( mode==xd3d_scrMode )  
	{
		zERR_MESSAGE(5,0, "X: Vid_SetScreenMode: No changes ..." );
		return;
	}
	if( xd3d_pdd7&&( xd3d_scrStatus==scrSTATUS_Used ) )
	{	
		if( XD3D_SetDevice( xd3d_tryDevnum, xd3d_scrWidth, xd3d_scrHeight, xd3d_scrBpp, mode )==FALSE )
		{	
			zERR_WARNING( "X: Vid_SetScreenMode: SetD3Ddevice failed !" );
			XD3D_SetDevice( xd3d_actStatus.devnum, xd3d_scrWidth, xd3d_scrHeight, xd3d_scrBpp, xd3d_scrMode );
		}
		else
		{
			switch( mode )
			{	
			case	zRND_SCRMODE_FULLSCREEN:		
					zERR_MESSAGE(5,0, "X: Vid_SetScreenMode: Switched to fullscreen mode ..." );
					ShowCursor( FALSE );
					sysKillWindowsKeys(true);
					break;
			case	zRND_SCRMODE_WINDOWED:
			default:
					zERR_MESSAGE(5,0, "X: Vid_SetScreenMode: Switched to windowed mode   ..." );

					ShowCursor( TRUE );
					sysKillWindowsKeys(false);
					break;
			}
			xd3d_scrMode = mode;
		}
	} 
	else
	{	
		zERR_MESSAGE(5,0, "X: Vid_SetScreenMode: Setting New Mode..." );
		xd3d_scrMode = mode;	
	} 			
	SetSurfaceLost(FALSE);
}



/*--------------------------------------------------------------------------

    zTRnd_ScreenMode zCRnd_D3D :: Vid_GetScreenMode()  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTRnd_ScreenMode zCRnd_D3D :: Vid_GetScreenMode() 
{ 
	//Rückmeldung des aktuellen Screenmode (Fullscreen oder Windowed)
	return xd3d_scrMode; 
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: Vid_SetGammaCorrection( float value )  

    14-Aug-00       [PELZER]
    29-Jan-01       [HILDEBRANDT]
					Umrechnung der Eingabe Parameter in guenstige Bereiche.
					Contrast invertiert (c=1-c)
--------------------------------------------------------------------------*/

void zCRnd_D3D :: Vid_SetGammaCorrection( float gamma, float contrast, float brightness ) 
{
	// Contrast, gamma correction and brightness
	if ((xd3d_Capabilities.gamma) && (xd3d_pgammacontrol))
	{
		float			x;
		DDGAMMARAMP		ramp;
		xd3d_actStatus.gammavalue = gamma;

		zClamp		(gamma		, 0.1F, 0.9F);
		zClamp		(contrast	, 0.1F, 0.9F);
		zClamp		(brightness	, 0.1F, 0.9F);

		// contrast invertieren
		contrast	= zREAL(1.0F) - contrast;

		brightness	= brightness* 0.4f + 0.3f;
		contrast	= contrast	* 0.4f + 0.3f;
		gamma		= gamma		* 0.8f + 0.1f;

		for( int t=0; t<256; t++ )
		{	
			x			= ((float)t)/255.0f; //[0.0f;1.0f]

			// Berechne den Kontrast
			x			= contrast/(1.0f-contrast)*x + 0.5f - contrast/(1.0f-contrast)*0.5f;
			zClamp01	(x);

			// Berechen die Gamma-Korrektur
			x			= (float)pow( x, 1/LocLerp( gamma*gamma, 0.25f, 3.25f ) );
	
			// Berechen die Helligkeit
			x			+= 2.0f*brightness-1.0f;
			zClamp01	(x);

			// Übertrage die skalierten Werte in die Gamma-Map
			x			*= 65535.0f;
			ramp.red[t] = ramp.green[t]	= ramp.blue[t] = (WORD)(x);
		}

		DXTryWarning (xd3d_pgammacontrol->SetGammaRamp( 0L, &ramp ), 
						"X: [RND3D]Vid_SetGammaCorrection: Can't set gamma ramp !" );
		zERR_MESSAGE (8, 0, "X: Vid_SetGammaCorrection:" );
		zERR_MESSAGE (8, 0, "X:     Contrast    -> " + zSTRING(contrast) );
		zERR_MESSAGE (8, 0, "X:     Gamma       -> " + zSTRING(gamma) );
		zERR_MESSAGE (8, 0, "X:     Brightness  -> " + zSTRING(brightness) );
	};
}



/*--------------------------------------------------------------------------

    float zCRnd_D3D :: Vid_GetGammaCorrection()  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
float zCRnd_D3D :: Vid_GetGammaCorrection() 
{ 
	//Rückmeldung der aktuellen Einstellung der Gamma-Korrektur
	return xd3d_actStatus.gammavalue; 
}
