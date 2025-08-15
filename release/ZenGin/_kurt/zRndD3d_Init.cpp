

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_Init.cpp 
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
				28.06.00	Added XD3D_TextureRescue() and XD3D_TextureRebuild()
				08.09.00	Integrated workaround for Voodoo cards (disable z-buffer write)
  
TODO:

*********************************************************************************/



#include "zcore.h"
#include "zRndD3D_Init.h"
#include "zWin32.h"
#include "zoption.h"

//#include "winable.h"


GUID						dxDeviceGUID;
unsigned long				dxDeviceNum;
unsigned long				dxDeviceNumber;
unsigned long				dxDeviceGUIDflag;
unsigned long				dxSelectDevice;
dxDEVICE					dxDevice[64];
DDDEVICEIDENTIFIER2			dddi;

typedef unsigned long		gxU32;

zD3DTEX						tex[zD3DTEXMAX];

typedef struct
{	gxU32						pixeltype;
	gxU32						pixelsize;
	gxU32						Rmask;	
	gxU32						Gmask;
	gxU32						Bmask;
	gxU32						Amask;

} xMAPTYPE;


dxDDMODE					dxDeviceMode[4][64];
static xMAPTYPE	maplist[] =
{	{ 0x0000,  8,0x0000,0x0000,0x0000,0x0000 },
	{ 0x4444, 16,0x0f00,0x00f0,0x000f,0xf000 },
	{ 0x5650, 16,0xf800,0x07e0,0x001f,0x0000 },
	{ 0x5551, 16,0x7c00,0x03e0,0x001f,0x8000 },
	{ 0x5550, 16,0x7c00,0x03e0,0x001f,0x0000 },
};
int							dxDeviceModeNum[4];


#define x4444 0
#define	x5650 1
#define	x5551 2
#define	x5550 3
#define	DDFLAG		(DDSCAPS_3DDEVICE)


DDPIXELFORMAT					pflist[32];
zBOOL							supportDXTC[5];


/*--------------------------------------------------------------------------

    XD3D_EnumTextureCallback( LPDDPIXELFORMAT ddpf, LPVOID context )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
static HRESULT CALLBACK XD3D_EnumTextureCallback( LPDDPIXELFORMAT ddpf, LPVOID context )
{	
	unsigned long mask[4];
	unsigned long pixelsize;
	if( ddpf->dwFlags&DDPF_PALETTEINDEXED8 )
	{	
		pixelsize = ddpf->dwRGBBitCount;
		pflist[0] = *ddpf;
		zerr.Message( "X: XD3D_EnumTextureCallback: Store Paletted Format" );
		((zCRnd_D3D*)zrenderer)->SetPalSupport( TRUE );
	}	
	else
	{	
		mask[0]		= ddpf->dwRBitMask;
		mask[1]		= ddpf->dwGBitMask;
		mask[2]		= ddpf->dwBBitMask;
		mask[3]		= ddpf->dwRGBAlphaBitMask;
		pixelsize	= ddpf->dwRGBBitCount;
		unsigned long t = 1;
		while( t<5 )
		{	
			if( maplist[t].pixelsize==pixelsize )
			{	
				if( (maplist[t].Rmask==mask[0])&&(maplist[t].Gmask==mask[1]) 
						&&(maplist[t].Bmask==mask[2])&&(maplist[t].Amask==mask[3]) )
				{	
					pflist[t] = *ddpf;
					zerr.Message( "X: XD3D_EnumTextureCallback: Store RGB Format" );
				}
			}
			t++;
		}
		switch( ddpf->dwFourCC )
		{
		case	MAKEFOURCC('D', 'X', 'T', '1'):
				supportDXTC[0] = TRUE;
				zerr.Message( "X: XD3D_EnumTextureCallback: Device supports DXT1" );
				break;
		case	MAKEFOURCC('D', 'X', 'T', '2'):
				supportDXTC[1] = TRUE;
				zerr.Message( "X: XD3D_EnumTextureCallback: Device supports DXT2" );
				break;
		case	MAKEFOURCC('D', 'X', 'T', '3'):
				supportDXTC[2] = TRUE;
				zerr.Message( "X: XD3D_EnumTextureCallback: Device supports DXT3" );
				break;
		case	MAKEFOURCC('D', 'X', 'T', '4'):
				supportDXTC[3] = TRUE;
				zerr.Message( "X: XD3D_EnumTextureCallback: Device supports DXT4" );
				break;
		case	MAKEFOURCC('D', 'X', 'T', '5'):
				supportDXTC[4] = TRUE;
				zerr.Message( "X: XD3D_EnumTextureCallback: Device supports DXT5" );
				break;
		}
	}
	*(static_cast<int*>( context )) += 1;

	return DDENUMRET_OK;
}



/*--------------------------------------------------------------------------

    XD3D_EnumModesCallback( LPDDSURFACEDESC2 DDSD, LPVOID lpContext )

 

    14-Aug-00       [PELZER]
    21-Sep-00       [HILDEBRANDT]
					prio Level des Spy Outputs runtergesetzt
--------------------------------------------------------------------------*/ 

static HRESULT WINAPI XD3D_EnumModesCallback( LPDDSURFACEDESC2 DDSD, LPVOID lpContext )
{	
	if( DDSD->ddpfPixelFormat.dwRGBBitCount>8 ) 
	{	
		dxDDMODE *dxDDM = &dxDeviceMode[dxDeviceNumber][dxDeviceModeNum[dxDeviceNumber]++];
		dxDDM->w		= DDSD->dwWidth;
		dxDDM->h		= DDSD->dwHeight;
		dxDDM->bpp		= DDSD->ddpfPixelFormat.dwRGBBitCount;
		zERR_MESSAGE (8,0,"X: Device supports mode -  (w*h*bpp) "+zSTRING(dxDDM->w)+"*"+zSTRING(dxDDM->h)+"*"+zSTRING(dxDDM->bpp) );
	}

	return DDENUMRET_OK;
}
 


/*--------------------------------------------------------------------------

    XD3D_EnumDeviceCallback( LPSTR DevDesc, LPSTR DevName, LPD3DDEVICEDESC7 D3DDevDesc, LPVOID userarg )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
static HRESULT CALLBACK XD3D_EnumDeviceCallback( LPSTR DevDesc, LPSTR DevName, LPD3DDEVICEDESC7 D3DDevDesc, LPVOID userarg )
{
	if( DevName ) 
		strcpy( dxDevice[dxDeviceNum].name,DevName );
	if( DevDesc ) 
		strcpy( dxDevice[dxDeviceNum].desc,DevDesc ); 
	else 
		return D3DENUMRET_OK;
	memcpy( &dxDevice[dxDeviceNum].guid, &D3DDevDesc->deviceGUID, sizeof( GUID ) );
	dxDevice[dxDeviceNum].dxguidflag = dxDeviceGUIDflag;
	if( dxDeviceGUIDflag )
		memcpy( &dxDevice[dxDeviceNum].dxguid, &dxDeviceGUID, sizeof( GUID ) );
	dxDevice[dxDeviceNum].number = dxDeviceNumber;
	if( D3DDevDesc->deviceGUID==IID_IDirect3DHALDevice )
	{	
		dxDevice[dxDeviceNum].hardware = 1;
		strcpy( dxDevice[dxDeviceNum].DeviceName, dddi.szDescription );
		zerr.Message( "X: Store Device: "+zSTRING(dddi.szDescription) );
		dxDeviceNum++;
		if( dxDeviceNum-1==dxSelectDevice ) 
			return D3DENUMRET_CANCEL;
	}
	
	return D3DENUMRET_OK;
}
 


/*--------------------------------------------------------------------------

    XD3D_AppIDDEnumCallback( GUID FAR* lpGUID, LPSTR lpDriverDesc, LPSTR lpDriverName, LPVOID lpContext )

 

    14-Aug-00       [PELZER]
	2002-05-28		[BENDLIN]
					- changed to EnumEx
					- added enum of attached secondary devices

--------------------------------------------------------------------------*/ 
BOOL FAR PASCAL XD3D_AppIDDEnumCallbackEx( GUID FAR* lpGUID, LPSTR lpDriverDesc,
                      LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm )
{
	IDirectDraw7 *testdd7	= NULL;
	IDirect3D7 *testd3d7	= NULL;
	int ggg;
	HRESULT err;
	err = DirectDrawCreateEx(lpGUID, reinterpret_cast<void**>( &testdd7 ), IID_IDirectDraw7, NULL); 
	if( err!=DD_OK ) 
		goto ende_;
	if( lpGUID!=NULL )
	{	
		dxDeviceGUIDflag = 1;
		memcpy( &dxDeviceGUID, lpGUID, sizeof( GUID ) );
	} 
	else
		dxDeviceGUIDflag = 0;
	testdd7->GetDeviceIdentifier( &dddi, 0L );
	ggg = 0;
	err = testdd7->QueryInterface( IID_IDirect3D7, (void**)&testd3d7);
	if( err!=DD_OK )
		goto ende1_;
	testd3d7->EnumDevices( &XD3D_EnumDeviceCallback,(LPVOID)&ggg );
	dxDeviceModeNum[dxDeviceNumber] = 0;
	testdd7->EnumDisplayModes( 0, NULL, NULL, &XD3D_EnumModesCallback );
	if( dxDeviceModeNum[dxDeviceNumber]>0 )
		dxDeviceNumber++;
ende1_:
	if( testd3d7!=NULL )
		RELEASE( testd3d7 );
ende_:
	if( testdd7!=NULL )
		RELEASE( testdd7 );
	if( dxDeviceNum-1==dxSelectDevice ) 
		return(D3DENUMRET_CANCEL);

	return DDENUMRET_OK;
}
 


/*--------------------------------------------------------------------------

    BOOL zCRnd_D3D :: XD3D_EnumerateModes( void )

 

    14-Aug-00       [PELZER]
	2002-05-28		[BENDLIN]
					- changed to EnumEx
					- added enum of attached secondary devices

--------------------------------------------------------------------------*/ 
//
BOOL zCRnd_D3D :: XD3D_EnumerateModes( void )
{
	dxDeviceNum		= 0;
	dxDeviceNumber	= 0;
	dxSelectDevice	= 0xFFFFFFFF;
	DirectDrawEnumerateEx( XD3D_AppIDDEnumCallbackEx, static_cast<void*>( 0L ),
		DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES );
	xd3d_actStatus.devmax = dxDeviceNum;
	
	return 0;
}
 


/*--------------------------------------------------------------------------

    BOOL zCRnd_D3D :: XD3D_InitPerDX( long flags, int x, int y, int bpp, int id )

	08-Sep-00       [PELZER]
	04-Oct-00       [HILDEBRANDT]
					Abfrage von zCRenderManager::GetUseRendererTNL() entfernt.
					Dieses Flag sollte nun nur noch "Hilevel" abefragt werden und
					dient oben dazu, zu entscheiden, ob die Trafo-Pipeline von der
					Engine oder dem Renderer erledigt werden soll.

--------------------------------------------------------------------------*/ 

BOOL zCRnd_D3D :: XD3D_InitPerDX( long flags, int x, int y, int bpp, int id )
{
	zerr.Message( "X: XD3D_InitPerDX: D3DXInitialize done" );
	unsigned long dwNumDevices = D3DXGetDeviceCount();

	D3DX_DEVICEDESC pDeviceList[100];
	if( !DXTryWarning( D3DXGetDeviceDescription( 0, &pDeviceList[0] ), 
		"X: [RND3D]XD3D_InitPerDX: Can't get device description !" ) )
		return FALSE;

	GUID guidLastUniqueDeviceId = pDeviceList[0].ddDeviceID;
    unsigned long cNumDDObjs = 1;
	unsigned long indexOfChosenD3DXDevices[100];
    indexOfChosenD3DXDevices[0] = 0; // start by picking the first device
    for( int i = 1; i<dwNumDevices; i++ )
    {
		if( !DXTryWarning( D3DXGetDeviceDescription( i, &pDeviceList[i] ), 
			"X: [RND3D]XD3D_InitPerDX: Can't get device description !" ) )
			return FALSE;
 
        if( pDeviceList[i].ddDeviceID!=guidLastUniqueDeviceId )
        {
            guidLastUniqueDeviceId = pDeviceList[i].ddDeviceID;
            cNumDDObjs++;
            indexOfChosenD3DXDevices[cNumDDObjs-1] = i;
        }
        else
		{
			if( (pDeviceList[i].hwLevel==D3DX_HWLEVEL_TL)||
					((pDeviceList[indexOfChosenD3DXDevices[cNumDDObjs-1]].hwLevel!=D3DX_HWLEVEL_TL)&&
					 (pDeviceList[i].hwLevel==D3DX_HWLEVEL_RASTER)) )
				indexOfChosenD3DXDevices[cNumDDObjs-1] = i;
		}
    }
	xd3d_actStatus.devmax = cNumDDObjs;
	for( i = 0; i<cNumDDObjs; i++ )
		zerr.Message( "X: XD3D_InitPerDX: Found "+zSTRING(pDeviceList[indexOfChosenD3DXDevices[i]].driverDesc) );

	// ACHTUNG: Hier wird die ID geändert !  
	// D3DX nummeriert die gefundenen Devices in umgekehrter Reihenfolge (im Vergleich zu D3D) !
	int dxdevnum = cNumDDObjs-1-id;
	zerr.Message( "X: XD3D_InitPerDX: Switching to "+zSTRING(pDeviceList[indexOfChosenD3DXDevices[dxdevnum]].driverDesc) );
	long deviceIndex = pDeviceList[indexOfChosenD3DXDevices[dxdevnum]].deviceIndex;
	
	ZeroMemory( &xd3d_Capabilities, sizeof( xd3d_Capabilities ) );
	if( pDeviceList[indexOfChosenD3DXDevices[dxdevnum]].hwLevel==D3DX_HWLEVEL_TL )
	{
		xd3d_Capabilities.tnl_hardware = TRUE;
		zerr.Message( "X: XD3D_InitPerDX: Hardware TnL supported." );
	}
	else
	{
		xd3d_Capabilities.tnl_hardware = FALSE;
		zerr.Message( "X: XD3D_InitPerDX: Hardware TnL not supported." );
	}

	//Hier geht's los ... Direct3D wird per DX Utility Library gestartet ...
	HRESULT hr;

	DWORD refreshRate = zoptions->ReadDWord("RENDERER_D3D", "zVidRefreshRate", 0);
	if (refreshRate == 0) refreshRate = D3DX_DEFAULT;

	// 32 bit z/w buffer antesten
	hr = D3DXCreateContextEx( deviceIndex, flags, xd3d_winHandle, NULL, bpp, D3DX_DEFAULT, 32 , 0, D3DX_DEFAULT, x, y, refreshRate, &xd3d_pd3dx );
	if( hr!=S_OK)
	{
		zERR_WARNING( "X: XD3D_InitPerDX: Can't initialize with 32 bit depth buffer, trying 24 bit ... " );
		hr = D3DXCreateContextEx( deviceIndex, flags, xd3d_winHandle, NULL, bpp, D3DX_DEFAULT, 24 , 0, D3DX_DEFAULT, x, y, refreshRate, &xd3d_pd3dx );
	}
	if(hr!=S_OK) 
	{
		zERR_WARNING( "X: XD3D_InitPerDX: Can't initialize with 24 bit depth buffer, trying default ... " );
		hr = D3DXCreateContextEx( deviceIndex, flags, xd3d_winHandle, NULL, bpp, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DX_DEFAULT, x, y, refreshRate, &xd3d_pd3dx );
	}
	
	if( (hr!=S_OK)&&(bpp!=16) )
	{
		zERR_WARNING( "X: XD3D_InitPerDX: Can't initialize with "+zSTRING(bpp)+" bpp - try 16 bpp ... " );
		hr = D3DXCreateContextEx( deviceIndex, flags, xd3d_winHandle, NULL, 16, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DX_DEFAULT, x, y, refreshRate, &xd3d_pd3dx );
		if( hr==S_OK )
			zerr.Message( "X: XD3D_InitPerDX: Initialized with 16 bpp !" );
	}

	if( hr!=S_OK ) 
	{	
		char error_str[128];
		char output_str[256];
		D3DXGetErrorString( hr, 128, error_str );
		sprintf( output_str, "X: XD3D_InitPerDX: Can't create D3DX context ! Error: %s", error_str );
		zerr.Fatal( output_str );
		return FALSE;
	}
	xd3d_pdd7 = xd3d_pd3dx->GetDD();
	if( xd3d_pdd7==NULL )
	{
		zERR_WARNING( "X: XD3D_InitPerDX: Can't get DirectDraw !" );
		RELEASE( xd3d_pd3dx );
		return FALSE;
	}
	xd3d_pd3d7 = xd3d_pd3dx->GetD3D();
	if( xd3d_pd3d7==NULL )
	{
		zERR_WARNING( "X: XD3D_InitPerDX: Can't get Direct3D !" );
		RELEASE( xd3d_pdd7 );
		RELEASE( xd3d_pd3dx );
		return FALSE;
	}
	xd3d_pd3dDevice7 = xd3d_pd3dx->GetD3DDevice();
	if( xd3d_pd3dDevice7==NULL )
	{
		zERR_WARNING( "X: XD3D_InitPerDX: Can't get Direct3DDevice !" );
		RELEASE( xd3d_pd3d7 );
		RELEASE( xd3d_pdd7 );
		RELEASE( xd3d_pd3dx );
		return FALSE;
	}
	xd3d_pfrontBuffer = xd3d_pd3dx->GetPrimary();
	if( xd3d_pfrontBuffer==NULL )
	{
		zERR_WARNING( "X: XD3D_InitPerDX: Can't get pointer to frontbuffer !" );
		RELEASE( xd3d_pd3dDevice7 );
		RELEASE( xd3d_pd3d7 );
		RELEASE( xd3d_pdd7 );
		RELEASE( xd3d_pd3dx );
		return FALSE;
	}
	xd3d_pbackBuffer = xd3d_pd3dx->GetBackBuffer( 0 );
	if( xd3d_pbackBuffer==NULL )
	{	
		zERR_WARNING( "X: XD3D_InitPerDX: Can't get pointer to backbuffer !" );
		RELEASE( xd3d_pfrontBuffer );
		RELEASE( xd3d_pd3dDevice7 );
		RELEASE( xd3d_pd3d7 );
		RELEASE( xd3d_pdd7 );
		RELEASE( xd3d_pd3dx );
		return FALSE;
	}
	xd3d_pzBuffer = xd3d_pd3dx->GetZBuffer();
	if( xd3d_pzBuffer==NULL )
	{	
		zERR_WARNING( "X: XD3D_InitPerDX: Can't get pointer to z-buffer !" );
		RELEASE( xd3d_pbackBuffer );
		RELEASE( xd3d_pfrontBuffer );
		RELEASE( xd3d_pd3dDevice7 );
		RELEASE( xd3d_pd3d7 );
		RELEASE( xd3d_pdd7 );
		RELEASE( xd3d_pd3dx );
		return FALSE;
	}

	if (zoptions->ReadInt("ENGINE","zVidEnableAntiAliasing",FALSE))
	{
		XD3D_SetRenderState(D3DRENDERSTATE_ANTIALIAS,D3DANTIALIAS_SORTINDEPENDENT);
	}

	return XD3D_TestCapabilities();
}
 


/*--------------------------------------------------------------------------

    BOOL zCRnd_D3D :: XD3D_InitPort( int x, int y, int bpp, int id, int mode )

 

    12-Sep-00       [PELZER]
	21-Jan-01		[PELZER]
					W-Buffer-Support für Matrox Grafikkarten gesperrt.

--------------------------------------------------------------------------*/ 
BOOL zCRnd_D3D :: XD3D_InitPort( int x, int y, int bpp, int id, int mode )
{
	global_surfaceCache.ClearCache();
	global_DXTCCache.ClearCache();
	xd3d_scrWidth	= x;
	xd3d_scrHeight	= y;
	zerr.Message( "X: XD3D_InitPort: "+zSTRING(x)+" x "+zSTRING(y)+" x "+zSTRING(bpp)+"(device:"+zSTRING(id)+" mode:"+zSTRING(mode)+")" );
	long flags;
	if( mode )
		flags = D3DX_CONTEXT_FULLSCREEN;
	else
		flags = 0;
	if( dxDevice[id].dxguidflag )
	{
		if( XD3D_InitPerDX( flags, x, y, bpp, id )==FALSE )
		{
			zERR_WARNING( "X: XD3D_InitPort: xInitPerID with ID failed !" );
			return FALSE;
		}
	}
	else
	{
		if( XD3D_InitPerDX( flags, x, y, bpp, 0 )==FALSE )
		{
			zERR_WARNING( "X: XD3D_InitPort: xInitPerDX without ID failed !" );
			return FALSE;
		}
	}
	DDPIXELFORMAT DDPFormat;
	memset( &DDPFormat, 0, sizeof( DDPFormat ) );
	DDPFormat.dwSize = sizeof( DDPFormat );
	if( !DXTryWarning( xd3d_pfrontBuffer->GetPixelFormat( &DDPFormat ), 
		"X: [RND3D]XD3D_InitPort: Can't get pixel format of the front buffer !" ) )
	{
		XD3D_ClearDevice();
		return FALSE;
	}
	xd3d_pixelformat = DDPFormat;
	D3DVIEWPORT7 viewData;
	viewData.dwX		= 0;
	viewData.dwY		= 0;
	viewData.dwWidth	= x;
	viewData.dwHeight	= y;
	viewData.dvMinZ		= 0.0f;
	viewData.dvMaxZ		= 1.0f;	
	DDPFormat.dwSize	= sizeof( DDPFormat );
	if( !DXTryWarning( xd3d_pd3dDevice7->SetViewport( &viewData ), 
		"X: [RND3D]XD3D_InitPort: Can't set viewport !" ) )
	{
		XD3D_ClearDevice();
		return FALSE;
	}
	//Beginne eine Scene
	if( xd3d_pd3dDevice7&&!xd3d_inScene )
	{
		xd3d_pd3dDevice7->BeginScene();
		xd3d_inScene = TRUE;
	}
	//Vermeide Garbage-Screen beim Start
	zCOLOR col;
	col.SetAlphaByte( 0 );
	col.SetBlueByte( 0 );
	col.SetRedByte( 0 );
	col.SetGreenByte( 0 );
	zrenderer->Vid_Clear( col, zRND_CLEAR_ALL );
	zrenderer->BeginFrame();
	zrenderer->EndFrame();
	zrenderer->Vid_Blit();
	zrenderer->Vid_Clear( col, zRND_CLEAR_ALL );
	for( int a = 0; a<MAXRENDERSTATES; a++ )
		xd3d_actRenderState[a] = 0xfafbfcfd;
	for( int b = 0; b<MAXTEXTURESTAGES; b++ )
		for( int a = 0 ; a<zRND_TSS_COUNT ; a++ )
			xd3d_actTexStageState[b][a] = 0xfafbfcfd;
	XD3D_SetRenderState( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );	
	XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_SPECULARENABLE, FALSE ); 
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
	XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );
	XD3D_SetRenderState( D3DRENDERSTATE_ZBIAS, 0);
	xd3d_actStatus.zd3dfunc = D3DCMP_LESSEQUAL;
	XD3D_SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE );
	XD3D_SetRenderState( D3DRENDERSTATE_AMBIENT, 0 );
	XD3D_SetRenderState( D3DRENDERSTATE_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL );
	xd3d_alphaBlendImmed	= FALSE;

	if( !DXTryWarning( xd3d_pdd7->GetDeviceIdentifier( &xd3d_deviceIdentifier, 0 ), 
		"X: [RND3D]XD3D_InitPort: Can't enumerate texture formats !" ) )
	{
		XD3D_ClearDevice();
		return FALSE;
	}
	zerr.Message( "X: D3D Device-Info: szDriver=" + zSTRING( xd3d_deviceIdentifier.szDriver ) ); 
	zerr.Message( "X: D3D Device-Info: szDescription=" + zSTRING( xd3d_deviceIdentifier.szDescription ) ); 
	zerr.Message( "X: D3D Device-Info: wProduct=" + zSTRING( HIWORD(xd3d_deviceIdentifier.liDriverVersion.HighPart) ) ); 
	zerr.Message( "X: D3D Device-Info: wVersion=" + zSTRING( LOWORD(xd3d_deviceIdentifier.liDriverVersion.HighPart) ) ); 
	zerr.Message( "X: D3D Device-Info: wSubVersion=" + zSTRING( HIWORD(xd3d_deviceIdentifier.liDriverVersion.LowPart) ) ); 
	zerr.Message( "X: D3D Device-Info: wBuild=" + zSTRING( LOWORD(xd3d_deviceIdentifier.liDriverVersion.LowPart) ) ); 
	zerr.Message( "X: D3D Device-Info: dwVendorId=" + zSTRING( xd3d_deviceIdentifier.dwVendorId ) ); 
	zerr.Message( "X: D3D Device-Info: dwDeviceId=" + zSTRING( xd3d_deviceIdentifier.dwDeviceId ) ); 
	zerr.Message( "X: D3D Device-Info: dwSubSysId=" + zSTRING( xd3d_deviceIdentifier.dwSubSysId ) ); 
	zerr.Message( "X: D3D Device-Info: dwRevision=" + zSTRING( xd3d_deviceIdentifier.dwRevision ) ); 

	XD3D_SetTexture( 0, 0 );
	for( int t = 0; t<zD3DTEXMAX; t++ )
	{
		tex[t].mode		= 0;
		tex[t].texture	= NULL;
	}

	// Default Material setzen
	{
		D3DMATERIAL7 d3dmat;
		ZeroMemory( &d3dmat, sizeof( D3DMATERIAL7 ) );
		d3dmat.diffuse.r = 1.0f;
		d3dmat.diffuse.g = 1.0f;
		d3dmat.diffuse.b = 1.0f;
		d3dmat.diffuse.a = 1.0f;
		d3dmat.ambient.r = 1.0f;
		d3dmat.ambient.g = 1.0f;
		d3dmat.ambient.b = 1.0f;
		d3dmat.ambient.a = 1.0f;
		xd3d_pd3dDevice7->SetMaterial( &d3dmat );
	};

	//
	xd3d_palsupp =  FALSE;
	supportDXTC[0] = FALSE;
	supportDXTC[1] = FALSE;
	supportDXTC[2] = FALSE;
	supportDXTC[3] = FALSE;
	supportDXTC[4] = FALSE;
	for( int i = 0; i<32; i++ )
		pflist[i].dwRGBBitCount = 0;
	int StartFormat;
	DDPFormat.dwSize = sizeof( DDPFormat );
	if( !DXTryWarning( xd3d_pd3dDevice7->EnumTextureFormats( XD3D_EnumTextureCallback, static_cast<LPVOID>( &StartFormat ) ), 
		"X: [RND3D]XD3D_InitPort: Can't enumerate texture formats !" ) )
	{
		XD3D_ClearDevice();
		return FALSE;
	}
	xd3d_actStatus.palsupported = xd3d_palsupp;
	if( xd3d_palsupp )
		zerr.Message( "X: XD3D_InitPort: Palette format supported" );

	// GetCaps
	D3DDEVICEDESC7 d3dd7;
	ZeroMemory( &d3dd7, sizeof( d3dd7 ) );
	if( !DXTryWarning( xd3d_pd3dDevice7->GetCaps( &d3dd7 ), 
		"X: [RND3D]XD3D_InitPort: Can't get the caps of the device !" ) )
	{
		XD3D_ClearDevice();
		return FALSE;
	}
	zerr.Message( "X: XD3D_InitPort: Maximal texture width  -> " + zSTRING( d3dd7.dwMaxTextureWidth ) );
	zerr.Message( "X: XD3D_InitPort: Maximal texture height -> " + zSTRING( d3dd7.dwMaxTextureHeight ) );

	// BlendDiffuseAlpha Support?
	if( d3dd7.dwTextureOpCaps & D3DTEXOPCAPS_BLENDDIFFUSEALPHA )
	{
		xd3d_Capabilities.blendDiffuseAlpha	= TRUE;
	} else
		xd3d_Capabilities.blendDiffuseAlpha	= FALSE;

	if (d3dd7.dwStencilCaps != 0)
		xd3d_Capabilities.hasStencil = TRUE;
	else 
		xd3d_Capabilities.hasStencil = FALSE;
		

	// Merke, ob alpha testing unterstützt wird
	if( d3dd7.dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
	{
		xd3d_alphaTest = TRUE;
		zerr.Message( "X: XD3D_InitPort: Alpha testing supported" );
	}
	else
	{
		xd3d_alphaTest = FALSE;
		zerr.Message( "X: XD3D_InitPort: Alpha testing not supported" );
	}

	// Teste, ob die Device range-based Fog unterstützt
	// Merke, ob Z- oder W-Buffer inkl. Auflösung
	// [EDENFELD] 
	// 1.08i Die Radeon Karte stellte manchmal Inventory Items nicht richtig dar
	zSTRING deviceDesc = zSTRING(xd3d_deviceIdentifier.szDescription).Upper();

	zBOOL buggyGeforceFound = (xd3d_deviceIdentifier.dwVendorId==4318) && 
							  ((deviceDesc.Search("GEFORCE3") != -1) ||(deviceDesc.Search("GEFORCE4") != -1) );

	buggyGeforceFound &= zoptions->ReadBool("RENDERER_D3D", "geforce3HackWBufferBug", TRUE);

	if (buggyGeforceFound) zERR_WARNING("C: geforce 3 or 4 found, setting to z buffer mode due to driver bug!");

	zSTRING vendor = zSTRING( xd3d_deviceIdentifier.szDescription ).Upper();
	zBOOL bRadeon	   = (vendor.Search("RADEON") != -1);
	zBOOL bRadeonFound = bRadeon && ( vendor.Search("9700") != -1 || vendor.Search("9000") != -1 || vendor.Search("9500") != -1 ) ;
	zBOOL bOldAtiFound = (xd3d_deviceIdentifier.dwVendorId==4098) && !bRadeonFound;						 

	if (bRadeonFound)
	{
		// [BENDLIN] 2.00 - Radeon-Hack default is now off
		if (!zoptions->ReadBool("RENDERER_D3D", "radeonHackAmbientColBug", FALSE))
		{
			m_bMustFlushOnAmbientColor = FALSE;
		}
		else 
		{
			m_bMustFlushOnAmbientColor = TRUE;
		}
	}
	else m_bMustFlushOnAmbientColor = FALSE;


	bOldAtiFound |= zoptions->ReadBool("RENDERER_D3D", "zForceZBuffer", FALSE);

	bOldAtiFound |= buggyGeforceFound;

	if( !bOldAtiFound && //[EDENFELD]; ATI Karten  nur Z-BUffer. Patch 1.08
		d3dd7.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_WBUFFER )
	{
		xd3d_wBuffer = TRUE;
		if( !XD3D_SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW ) )
		{
			xd3d_wBuffer = FALSE;
			zerr.Message( "X: XD3D_InitPort: no w-buffering" );
			if( !XD3D_SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_TRUE ) )
				zerr.Message( "X: XD3D_InitPort: no z-buffering" );
		}
	}
	else
	{
		xd3d_wBuffer = FALSE;
		zerr.Message( "X: XD3D_InitPort: no w-buffering" );
		if( !XD3D_SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_TRUE ) )
			zerr.Message( "X: XD3D_InitPort: no z-buffering" );
	}

#ifdef COMPILING_SPACER
	xd3d_wBuffer = FALSE;
#endif

	unsigned long colorBits		= 0;
	unsigned long depthBits		= 0;
	unsigned long alphaBits		= 0;
	unsigned long stencilBits	= 0;
	xd3d_pd3dx->GetNumBits( &colorBits, &depthBits, &alphaBits, &stencilBits );
	zerr.Message( "X: XD3D_InitPort: Color-Buffer depth:"+zSTRING(colorBits) );
	if( (xd3d_wBuffer)&&
		!((xd3d_deviceIdentifier.dwVendorId==4139/*Matrox*/)/*&&*/
		  /*((xd3d_deviceIdentifier.dwDeviceId==1313)||(xd3d_deviceIdentifier.dwDeviceId==1317))*/) ) //G400 und G200
	{
		switch( depthBits )
		{
		case	32:
				xd3d_zwBufferLevel = zRND_W32_BUFFER;
				break;
		case	24:
				xd3d_zwBufferLevel = zRND_W24_BUFFER;
				break;
		case	16:
				xd3d_zwBufferLevel = zRND_W16_BUFFER;
				break;
		default:
				xd3d_zwBufferLevel = zRND_UNKNOWN_BUFFER;
		}
		zerr.Message( "X: XD3D_InitPort: W-Buffer depth:"+zSTRING(depthBits) );
	}
	else
	{
		switch( depthBits )
		{
		case	32:
				xd3d_zwBufferLevel = zRND_Z32_BUFFER;
				break;
		case	24:
				xd3d_zwBufferLevel = zRND_Z24_BUFFER;
				break;
		case	16:
				xd3d_zwBufferLevel = zRND_Z16_BUFFER;
				break;
		default:
				xd3d_zwBufferLevel = zRND_UNKNOWN_BUFFER;
		}
		zerr.Message( "X: XD3D_InitPort: Z-Buffer depth:"+zSTRING(depthBits) );
	}

	// Guardband Caps
	{
		xd3d_Capabilities.guardbandleft		= ( float )d3dd7.dvGuardBandLeft;	
		xd3d_Capabilities.guardbandright	= ( float )d3dd7.dvGuardBandRight;
		xd3d_Capabilities.guardbandtop		= d3dd7.dvGuardBandTop;		
		xd3d_Capabilities.guardbandbottom	= d3dd7.dvGuardBandBottom;
		xd3d_Capabilities.guardband			= FALSE;
		if( (d3dd7.dvGuardBandLeft<0)&&(d3dd7.dvGuardBandTop<0)&&
				(d3dd7.dvGuardBandRight>xd3d_scrWidth)&&(d3dd7.dvGuardBandBottom>xd3d_scrHeight) )
			xd3d_Capabilities.guardband		= TRUE;
	};

	// Min/Max Texture Dimensionen
	{
		xd3d_Capabilities.maxtexsize	= (unsigned long)zMin (int(d3dd7.dwMaxTextureHeight), int(d3dd7.dwMaxTextureWidth));
		xd3d_Capabilities.mintexsize	= (unsigned long)zMax (int(d3dd7.dwMinTextureHeight), int(d3dd7.dwMinTextureWidth));

		// sanity: Laut Kundenreports wurden oefter Fehler gemeldet, die auf ein 'maxTexSize==0' zurueckzufuehren sind, aber: wie kann soetwas passieren?
		if (xd3d_Capabilities.maxtexsize<=0)
		{
			zERR_FATAL ("D: Direct3D Device reports maximum texture dimension to be 0! Direct3D or the VideoDriver fails.");
		};
	};

	// misc Caps
	{
		xd3d_Capabilities.multitexture	= FALSE;
		if( d3dd7.wMaxSimultaneousTextures>1 )							xd3d_Capabilities.multitexture = TRUE;
		xd3d_Capabilities.ztest			= TRUE;
		xd3d_Capabilities.alphatest		= FALSE;
		if( d3dd7.dpcTriCaps.dwAlphaCmpCaps | D3DCMP_GREATEREQUAL )		xd3d_Capabilities.alphatest = TRUE;
		xd3d_Capabilities.num_stages	= d3dd7.wMaxTextureBlendStages;
		xd3d_Capabilities.num_texstages = d3dd7.wMaxSimultaneousTextures;
		
		// Bugfix Kyro/andere Karten mit mehr als 4 verschiedenen simultan verwendeten Texturen
		zClamp(xd3d_Capabilities.num_texstages, 0, MAXTEXTURESTAGES);

		xd3d_Capabilities.tnl_maxlights = d3dd7.dwMaxActiveLights;
		xd3d_Capabilities.tnl = TRUE;
	}

	// DirectDraw Caps
	DDCAPS	ddcaps;
	ZeroMemory( &ddcaps, sizeof( ddcaps ) );
	ddcaps.dwSize = sizeof( ddcaps );
	if( !DXTryWarning( xd3d_pdd7->GetCaps( &ddcaps, NULL ), 
		"X: [RND3D]XD3D_InitPort: Can't get caps of DirectDraw !" ) )
	{
		XD3D_ClearDevice();
		return FALSE;
	}
	if (ddcaps.dwCaps2&DDCAPS2_CANRENDERWINDOWED)					xd3d_Capabilities.window = TRUE;
	xd3d_Capabilities.vidmemsize	= ddcaps.dwVidMemTotal;
	xd3d_Capabilities.vidmemfree	= ddcaps.dwVidMemFree;
	if( xd3d_Capabilities.window ) 
		zerr.Message( "X: XD3D_InitPort: caps - windowed mode possible" );

	// GammaControl vorhanden?
	if (ddcaps.dwCaps2 & DDCAPS2_PRIMARYGAMMA)	
	{
		if (!DXTryWarning (xd3d_pfrontBuffer->QueryInterface( IID_IDirectDrawGammaControl, reinterpret_cast<void**>( &xd3d_pgammacontrol)), 
				"X: [RND3D]XD3D_InitPort: caps - gamma correction not activated !" ) )
		{
			xd3d_Capabilities.gamma = FALSE;
			RELEASE					(xd3d_pgammacontrol);	// safety
			xd3d_pgammacontrol		= 0;
		}
		else 
		{
			xd3d_Capabilities.gamma = TRUE;
			zERR_ASSERT				(xd3d_pgammacontrol!=0);
			zERR_MESSAGE			(5, 0, "X: XD3D_InitPort: caps - gamma correction enabled");
		};
	} else
	{
		xd3d_Capabilities.gamma		= FALSE;
		RELEASE						(xd3d_pgammacontrol);	// safety
		xd3d_pgammacontrol			= 0;
	};

	// Auf Matrox Karten wird aufgrund von Crashes die maximale FPS Anzahl auf 20
	// FPS gesetzt (FIXME: eventuell nicht mehr nötig, wegen besserer Treiber -> QA Check)
	if (xd3d_deviceIdentifier.dwVendorId==4139)
	{
		zoptions->WriteDWord("ENGINE", "zMaxFPS", 400 );
	}


/*	if (xd3d_Capabilities.gamma)	 
	{	
		if( !DXTryWarning( xd3d_pfrontBuffer->QueryInterface( IID_IDirectDrawGammaControl, reinterpret_cast<void**>( &xd3d_pgammacontrol ) ), 
				"X: [RND3D]XD3D_InitPort: caps - gamma correction not activated !" ) )
			xd3d_Capabilities.gamma = FALSE;
		else 
			zerr.Message( "X: XD3D_InitPort: caps - gamma correction enabled" );
	}*/

	//
	zERR_MESSAGE (5,0, "X: XD3D_InitPort: caps - total videomem:"+zSTRING(xd3d_Capabilities.vidmemsize) );
	zERR_MESSAGE (5,0, "X: XD3D_InitPort: caps - free videomem:"+zSTRING(xd3d_Capabilities.vidmemfree) );

	if( d3dd7.dpcTriCaps.dwRasterCaps&D3DPRASTERCAPS_WFOG )
		zerr.Message( "X: XD3D_InitPort: caps - w-based fog supported" );

	// Default bzw. letzten Stand erzeugen
	for( i = 0; i<xd3d_Capabilities.num_texstages; i++ )
	{
		SetTextureStageState( i, zRND_TSS_ADDRESSU, D3DTADDRESS_WRAP );
		SetTextureStageState( i, zRND_TSS_ADDRESSV, D3DTADDRESS_WRAP );
		
		if (!zoptions->ReadBool("ENGINE", "zTexAnisotropicFiltering", FALSE))
		{
			SetTextureStageState( i, zRND_TSS_MAGFILTER, D3DTFG_LINEAR );
			SetTextureStageState( i, zRND_TSS_MINFILTER, D3DTFN_LINEAR );
			m_bAnisotropicFilter = FALSE;

		}
		else
		{
			SetTextureStageState( i, zRND_TSS_MAGFILTER, D3DTFG_ANISOTROPIC);
			SetTextureStageState( i, zRND_TSS_MINFILTER, D3DTFN_ANISOTROPIC);
			m_bAnisotropicFilter = TRUE;
		}

		SetTextureStageState( i, zRND_TSS_MIPFILTER, D3DTFP_LINEAR );
		SetTextureStageState( i, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
		SetTextureStageState( i, zRND_TSS_COLORARG2, zRND_TA_CURRENT );
		SetTextureStageState( i, zRND_TSS_ALPHAARG1, zRND_TA_TEXTURE );
		SetTextureStageState( i, zRND_TSS_ALPHAARG2, zRND_TA_CURRENT );
	}
	Vid_SetGammaCorrection	( xd3d_actStatus.gammavalue );
	SetFogRange				( xd3d_actStatus.nearZ, xd3d_actStatus.farZ, xd3d_actStatus.fogMode );
	SetFogColor				( xd3d_actStatus.fogColor );
	SetFog					( xd3d_actStatus.fog );
	SetMaterial				( xd3d_actmaterial );

	zCSurfaceCache_D3D::ResetSurfaceList();

	if( xd3d_deviceChange )
	{
		//Rebuild der einzelnen Vertexbuffer
		zerr.Message( "X: XD3D_InitPort: Start to rebuild vertexbuffers ..." );
		for( i = 0; i<zCVertexBuffer_D3D::xvb_vertexbufferList.GetNum(); i++ )
		{
			if( !zCVertexBuffer_D3D::xvb_vertexbufferList[i]->CallRecreateLostVBCallbacks() )
				zERR_WARNING( "X: XD3D_InitPort: Can't recreate vertexbuffer at list position "+zSTRING(i)+" !" );
		}
		zerr.Message( "X: XD3D_InitPort: Vertexbuffers rebuild done." );
		//Rebuild der geretteten Texturen
		XD3D_TextureRebuild(); 
		xd3d_deviceChange = FALSE;
	}
	for( t = 0; t<MAXTEXTURESTAGES; t++ )
	{
		xd3d_ptexture[t] = 0L;
		xd3d_pd3dtexture[t] = 0L;
	}
	for( int s = 0; s<MAXTEXTURESTAGES; s++ ) 
		for( int t = 0 ; t<zRND_TSS_COUNT ; t++ )
			xd3d_actTexStageState[s][t] = 0xffffffff;

	//Vertexbuffer für den Alphapoly-Flush anlegen
	D3DVERTEXBUFFERDESC vbdesc;
	ZeroMemory( &vbdesc, sizeof( D3DVERTEXBUFFERDESC ) );
	vbdesc.dwSize			= sizeof( D3DVERTEXBUFFERDESC );
	vbdesc.dwCaps			= D3DVBCAPS_WRITEONLY;
	vbdesc.dwFVF			= D3DFVF_TLVERTEX;
	vbdesc.dwNumVertices	= ALPHAVERTEXBUFFERSIZE;
    //Erzeugung eines DirectX-Vertexbuffers
	zD3D_alphaPoly::vertexbufferdyn = zNEW( zCVertexBufferDyn( zVBUFFER_VERTFORMAT_XYZRHW|zVBUFFER_VERTFORMAT_COLOR|zVBUFFER_VERTFORMAT_TEXUV1, ALPHAVERTEXBUFFERSIZE ) );
	zD3D_alphaPoly::vertexbuffer = zD3D_alphaPoly::vertexbufferdyn->GetVertexBuffer();
	zD3D_alphaPoly::vertexbuffer->SetPrimitiveType( zVBUFFER_PT_TRIANGLELIST );
	zD3D_alphaPoly::locked = FALSE;
	zD3D_alphaPoly::startvertex = 0;
	zD3D_alphaPoly::numberofvertices = 0;
	zD3D_alphaPoly::actnov = 0;

	xd3d_backlocked = FALSE;

	return TRUE;
}
 


/*--------------------------------------------------------------------------

    BOOL zCRnd_D3D :: XD3D_TestCapabilities()

    07-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 

BOOL zCRnd_D3D :: XD3D_TestCapabilities()
{
	D3DDEVICEDESC7 d3dd7;
	ZeroMemory( &d3dd7, sizeof( d3dd7 ) );
	if( !DXTryWarning( xd3d_pd3dDevice7->GetCaps( &d3dd7 ), 
		"X: [RND3D]XD3D_InitPort: Can't get the caps of the device !" ) )
	{
		return FALSE;
	};

	zBOOL	failed	= FALSE;
	zSTRING	errorString;

	// Min/Max TexSize
	{
		int maxtexsize	= zMin (int(d3dd7.dwMaxTextureHeight), int(d3dd7.dwMaxTextureWidth));

		// sanity: Laut Kundenreports wurden oefter Fehler gemeldet, die auf ein 'maxTexSize==0' zurueckzufuehren sind, aber: wie kann soetwas passieren?
		if ((maxtexsize<=0) || (maxtexsize<256))
		{
			zSTRING		s("X: XD3D_TestCapabilities: failure, texture dimensions of at least 256 are not supported! \n");
			errorString	+= s;
			zERR_WARNING(s);
			failed		= TRUE;
		};
	};

	if( !(d3dd7.dwTextureOpCaps&D3DTEXOPCAPS_ADD) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DTEXOPCAPS_ADD not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if( !(d3dd7.dwTextureOpCaps&D3DTEXOPCAPS_MODULATE) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DTEXOPCAPS_MODULATE not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if( !(d3dd7.dwTextureOpCaps&D3DTEXOPCAPS_SELECTARG1) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DTEXOPCAPS_SELECTARG1 not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if( !(d3dd7.dwTextureOpCaps&D3DTEXOPCAPS_SELECTARG2) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DTEXOPCAPS_SELECTARG2 not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if( !(d3dd7.dpcTriCaps.dwTextureAddressCaps&D3DPTADDRESSCAPS_CLAMP) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DPTADDRESSCAPS_CLAMP not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if ((!(d3dd7.dpcTriCaps.dwTextureCaps&D3DPTEXTURECAPS_NONPOW2CONDITIONAL)) && (d3dd7.dpcTriCaps.dwTextureCaps&D3DPTEXTURECAPS_POW2))
	{
		zerr.Message( "X: XD3D_TestCapabilities: All textures must have widths and heights specified as powers of 2 !" );
	};
	if( !(d3dd7.dpcTriCaps.dwTextureAddressCaps&D3DPTADDRESSCAPS_WRAP) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DPTADDRESSCAPS_WRAP not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if( !(d3dd7.dpcTriCaps.dwZCmpCaps&D3DPCMPCAPS_LESSEQUAL) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DPCMPCAPS_LESSEQUAL not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if( !(d3dd7.dwDevCaps&D3DDEVCAPS_DRAWPRIMTLVERTEX) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DDEVCAPS_DRAWPRIMTLVERTEX not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if( !(d3dd7.dwDevCaps&D3DDEVCAPS_FLOATTLVERTEX) )
	{
		const zSTRING	s("X: XD3D_TestCapabilities: D3DDEVCAPS_FLOATTLVERTEX not supported \n");
		errorString		+= s;
		zERR_WARNING	(s);
		failed			= TRUE;
	}
	if (!failed)
		zerr.Message( "X: XD3D_TestCapabilities: Device has passed capability tests." );

	if (failed)		
	{
		zERR_FATAL ("D: Direct3D Renderer: Direct3D Device does not support all required features. Terminating now. Log: "+errorString);
	};

	return (!failed);
}
 


/*--------------------------------------------------------------------------

    BOOL zCRnd_D3D :: XD3D_SetDevice( int num, int x, int y, int bpp, zTRnd_ScreenMode mode )

 

    24-Aug-00       [PELZER]
	2002-05-28		[BENDLIN]
					- changed to EnumEx
					- added enum of attached secondary devices

--------------------------------------------------------------------------*/ 
BOOL zCRnd_D3D :: XD3D_SetDevice( int num, int x, int y, int bpp, zTRnd_ScreenMode mode )
{
	dxDeviceNum			= 0;
	dxDeviceNumber		= 0;
	dxSelectDevice		= num;
	xd3d_scrMode		= mode;
	DirectDrawEnumerateEx( XD3D_AppIDDEnumCallbackEx, static_cast<void*>( NULL ),
		DDENUM_ATTACHEDSECONDARYDEVICES | DDENUM_NONDISPLAYDEVICES );
	if( mode==zRND_SCRMODE_FULLSCREEN )
		ShowCursor( FALSE );
	else
		ShowCursor( TRUE );
	if( xd3d_scrMode==zRND_SCRMODE_HIDE )
		xd3d_scrMode = zRND_SCRMODE_WINDOWED;
	if( mode==zRND_SCRMODE_FULLSCREEN )
	{
		if( (num==xd3d_num)&&(x==xd3d_x)&&(y==xd3d_y)&&(bpp==xd3d_bpp) )
		{
			if( xd3d_mode==zRND_SCRMODE_WINDOWED )
			{
				xd3d_mode			= zRND_SCRMODE_FULLSCREEN;
				xd3d_deviceChange	= TRUE;
				zerr.Message		( "X: XD3D_SetDevice: Switching to fullscreen on same device ..." );
				XD3D_ClearDevice();
				if( XD3D_InitPort( x, y, bpp, num, 1 ) ) //fullscreen initialisieren
				{
					xd3d_actStatus.devnum = num;
					return TRUE;
				} else
				{
					zERR_FATAL ("D: Direct3D Renderer: Cannot initialize Direct3D Device. Unsupported Video-Hardware or Video-Drivers? Terminating now.");
				};

				return FALSE;
			}
			return TRUE;
		}
		xd3d_num			= num;
		xd3d_x				= x;
		xd3d_y				= y;
		xd3d_bpp			= bpp;
		xd3d_mode			= zRND_SCRMODE_FULLSCREEN;
		xd3d_deviceChange	= TRUE;
		XD3D_ClearDevice();
		if( XD3D_InitPort( x, y, bpp, num, 1 ) ) //fullscreen initialisieren
		{
			xd3d_actStatus.devnum = num;
			return TRUE;
		} else
		{
			zERR_FATAL ("D: Direct3D Renderer: Cannot initialize Direct3D Device. Unsupported Video-Hardware or Video-Drivers? Terminating now.");
		};
		return FALSE;
	}

	//Windowed Modus soll aktiviert werden ...
	if( (xd3d_num==0)&&(x==xd3d_x)&&(y==xd3d_y)&&(bpp==xd3d_bpp) )
	{
		if( xd3d_mode==zRND_SCRMODE_FULLSCREEN )
		{
			xd3d_mode			= zRND_SCRMODE_WINDOWED;
			xd3d_deviceChange	= TRUE;
			zerr.Message		( "X: XD3D_SetDevice: Switching to windowed on same device ..." );
			XD3D_ClearDevice();
			if( XD3D_InitPort( x, y, bpp, 0, 0 ) ) //windowed initialisieren....
			{
				xd3d_actStatus.devnum = 0;
				return TRUE;
			} else
			{
				zERR_FATAL ("D: Direct3D Renderer: Cannot initialize Direct3D Device. Unsupported Video-Hardware or Video-Drivers? Terminating now.");
			};
			return FALSE;
		}
		return TRUE;
	}
	xd3d_num			= 0;
	xd3d_x				= x;
	xd3d_y				= y;
	xd3d_bpp			= bpp;
	xd3d_mode			= zRND_SCRMODE_WINDOWED;
	xd3d_deviceChange	= TRUE;
	XD3D_ClearDevice();
	if( XD3D_InitPort( x, y, bpp, 0, 0 ) ) //windowed initialisieren....
	{
		xd3d_actStatus.devnum = 0;
		return TRUE;
	} else
	{
		zERR_FATAL ("D: Direct3D Renderer: Cannot initialize Direct3D Device. Unsupported Video-Hardware or Video-Drivers? Terminating now.");
	};
	return FALSE;
}
 


/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_ClearDevice()

 

    26-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCRnd_D3D :: XD3D_ClearDevice()
{
	if( !xd3d_pd3dx )
		return;
	zerr.Message( "X: XD3D_ClearDevice: Releasing old mode ..." );
	for( int i = 0; i<xd3d_Capabilities.num_texstages; i++ )
		XD3D_SetTexture( i, 0L );

	int textureSaved = 0;
	if( xd3d_deviceChange )
		zerr.Message( "X: Start to save textures (lightmaps) ..." );
	//WICHTIG: Kopiere die Liste der auszucachenden Texturen in eine eigene statische Liste
	//da die vorgegebene Liste sich während dem CacheOut der Einträge verändern kann !!!
	zCTexture **tex = zNEW_ARRAY( zCTexture*, zCTexture::GetStaticClassDef()->GetNumObjects() );
	for( int t=0; t<zCTexture::GetStaticClassDef()->GetNumObjects(); t++) 
	{
		(*(tex+t)) = static_cast<zCTexture*>(zCTexture::GetStaticClassDef()->GetObjectByIndex(t));
	}
	//Ab hier wird nur mit der eigenen statischen Kopie der Liste gearbeitet !!!
	for( t = 0; t<zCTexture::GetStaticClassDef()->GetNumObjects(); t++) 
	{
		if( (xd3d_deviceChange)&&(tex[t]->GetCacheOutLock()) )
		{
			if( XD3D_TextureRescue( (zCTex_D3D*)(*(tex+t)) ) )
				++textureSaved;
		}
		(*(tex+t))->CacheOut();
	}
	delete[] tex;
	if( xd3d_deviceChange )
		zerr.Message( "X: Number of saved textures:"+zSTRING(textureSaved) );
	xd3d_pd3d7->EvictManagedTextures();
	global_surfaceCache.ClearCache();
	global_DXTCCache.ClearCache();
	//Beende die aktuelle Scene
	if( xd3d_pd3dDevice7&&xd3d_inScene )
	{
		xd3d_pd3dDevice7->EndScene();
		xd3d_inScene = FALSE;
	}
	//Release der einzelnen DX-Vertexbuffer
	if( xd3d_deviceChange )
	{
		zerr.Message( "X: Destroy all vertexbuffers." );
		for( i = 0; i<zCVertexBuffer_D3D::xvb_vertexbufferList.GetNum(); i++ )
		{
			zCVertexBuffer_D3D::xvb_vertexbufferList[i]->Destroy();
		}
	}
	if( zD3D_alphaPoly::vertexbufferdyn!=NULL )
		delete zD3D_alphaPoly::vertexbufferdyn;

	// Release der einzelnen DirectX-Pointer
	RELEASE				( xd3d_pbackBuffer );
	RELEASE				( xd3d_pfrontBuffer );
	RELEASE				( xd3d_pzBuffer );
	if (xd3d_Capabilities.gamma) 
		RELEASE (xd3d_pgammacontrol);
	xd3d_pgammacontrol	= 0;			// sicher ist sicher..
	RELEASE				( xd3d_pd3dDevice7 );
	RELEASE				( xd3d_pd3d7 );
	RELEASE				( xd3d_pdd7 );
	RELEASE				( xd3d_pd3dx );
	xd3d_pdd7			= NULL;
	xd3d_pd3d7			= NULL;
	xd3d_pd3dDevice7	= NULL;
	xd3d_pd3dx			= NULL;
	xd3d_num = -1;
}
 


/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D :: XD3D_TextureRescue( zCTex_D3D *texture )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL zCRnd_D3D :: XD3D_TextureRescue( zCTex_D3D *texture )
{
	zD3D_savedTexture	*lastSavedTexture = xd3d_savedTexture;
	xd3d_savedTexture = zNEW( zD3D_savedTexture );
	if( xd3d_savedTexture==NULL )
	{
		zerr.Message( "X: XD3D_TextureRescue: RescueTexture failed (no memory for zD3D_savedTexture)" );
		xd3d_savedTexture = lastSavedTexture;
		return FALSE;
	}
	xd3d_savedTexture->next		= lastSavedTexture;
	xd3d_savedTexture->texture	= texture;
	if( !texture->RescueTexture( xd3d_savedTexture ) )
	{
		zerr.Message( "X: XD3D_TextureRescue: RescueTexture failed" );
		delete xd3d_savedTexture;
		xd3d_savedTexture = lastSavedTexture;
		return FALSE;
	}

	return TRUE;
}
 


/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D :: XD3D_TextureRebuild()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL zCRnd_D3D :: XD3D_TextureRebuild()
{
	zerr.Message( "X: Start to rebuild saved textures (lightmaps) ..." );
	zD3D_savedTexture	*doneSavedTexture = NULL;
	int textureRebuild = 0;
	while( xd3d_savedTexture!=NULL )
	{
		if( !xd3d_savedTexture->texture->RebuildTexture( xd3d_savedTexture ) )
			zerr.Message( "X: XD3D_TextureRebuild: RebuildTexture failed" );
		doneSavedTexture	= xd3d_savedTexture;
		xd3d_savedTexture	= xd3d_savedTexture->next;
		delete doneSavedTexture;
		++textureRebuild;
	}
	zerr.Message( "X: Number of rebuild textures:"+zSTRING(textureRebuild) );

	return TRUE;
}
 


/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D :: XD3D_CreateWin( const int x, const int y, const int bpp )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zBOOL zCRnd_D3D :: XD3D_CreateWin( const int x, const int y, const int bpp )
{
	zBOOL res;
    VIDMODE NewMode;
	vid_xdim					= x;
	vid_ydim					= y;
	vid_bpp						= bpp;
    memcpy( &NewMode, &VideoModeCur, sizeof( VIDMODE ) );
    NewMode.si.Width			= x;
    NewMode.si.Height			= y;
    NewMode.si.BPP				= bpp;
    NewMode.hwModeType			= VIDMODE_DIB;
    if ( !vidSetMode( &NewMode ) ) 
	{
		res = FALSE; 
		zERR_WARNING("X: Failed to open window with x: " + zSTRING(x) + " y: "+ zSTRING(y) );
	} 
	else 
	{
		res = TRUE;
		zERR_MESSAGE(6,0,"X: Opened window with x: " + zSTRING(x) + " y: "+ zSTRING(y) );
	}
	VIDEO_INFO vidInfo;
	memZero( &vidInfo, sizeof( vidInfo ) ); //Wipe out structure
	vidInfo.bHideMenu			= TRUE;
	vidInfo.bDisableMenuKeys	= TRUE; //Disable menu keys
	vidInfo.bOnlyFullScreen		= FALSE; //Only operate on fullscreen
	vidInfo.bDisableAltEnter	= TRUE;	
	vidInfo.bDisableCtrlAltDel	= TRUE;
	vidInfo.dwShowBitDepths		= 2 | 8; //Show 16 and 32 bit color depths
	vidInfo.dwEnableBitDepths	= 2 | 8; //Enable 16 and 32 bit color depths
	vidInfo.dwStretch			= VIDSTRETCH_USER; //Variable size
	vidInfo.fnCheckVMode		= 0; //->Callback to Check modes to add
	vidInfo.fnSetVideoMode		= 0; //->Callback for Video mode	
	vidSetModeEx( &vidInfo ); //Set video mode caps
	sysSetFocus();
	if( xd3d_newWinHandle==0 )
	{
		xd3d_winHandle			= GetActiveWindow();
		zERR_WARNING( "X: XD3D_CreateWin: Using active window (please set win handle) !!!" );
	}
	else
		xd3d_winHandle			= xd3d_newWinHandle;
//	BlockInput( TRUE );

	return res;

}
 


/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_CloseWin()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCRnd_D3D :: XD3D_CloseWin()
{
    VIDMODE NewMode;
    memcpy( &NewMode, &VideoModeCur, sizeof( VIDMODE ) );
    NewMode.si.Width			= 0;
    NewMode.si.Height			= 0;
    NewMode.si.BPP				= 16;
    NewMode.hwModeType			= VIDMODE_ANYWINDOWED;
    vidSetMode( &NewMode );
	VIDEO_INFO vidInfo;
	memZero( &vidInfo, sizeof( vidInfo ) ); //Wipe out structure
	vidInfo.bHideMenu			= TRUE;
	vidInfo.bDisableMenuKeys	= TRUE; //Disable menu keys
	vidInfo.bOnlyFullScreen		= FALSE; //Only operate on fullscreen
	vidInfo.bDisableAltEnter	= TRUE;	
	vidInfo.bDisableCtrlAltDel	= TRUE;
	vidInfo.dwShowBitDepths		= 1 | 2 | 8; //Show 8, 16 and 32 bit color depths
	vidInfo.dwEnableBitDepths	= 1 | 2 | 8; //Enable 8 and 32 bit color depths
	vidInfo.dwStretch			= VIDSTRETCH_USER; //Variable size
	vidInfo.fnCheckVMode		= 0; //->Callback to Check modes to add
	vidInfo.fnSetVideoMode		= 0; //->Callback for Video mode
	vidSetModeEx( &vidInfo ); //Set video mode caps
	xd3d_winHandle				= GetActiveWindow();
	SetFocus( xd3d_winHandle );
}
