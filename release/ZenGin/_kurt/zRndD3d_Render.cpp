/******************************************************************************** 
 
     $Workfile:: zRndD3D_Render.cpp   $                $Date:: 17.03.01 3:19    $
     $Revision:: 136                  $             $Modtime:: 17.03.01 3:13    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   DirectX 7 - Implementation
   created       : 02.02.2000

 * $Log: /current_work/ZenGin/_Kurt/zRndD3D_Render.cpp $
 * 
 * 136   17.03.01 3:19 Hildebrandt
 * 
 * 135   15.03.01 2:18 Hildebrandt
 * 
 * 134   15.02.01 3:37 Hildebrandt
 * fix in SetLight(), incorrect handling of ambient lights
 * 
 * 133   14.02.01 23:16 Speckels
 * zerr.Message durch Makro ersetzt
 * 
 * 132   2.02.01 18:53 Hildebrandt
 * 
 * 131   31.01.01 1:47 Hildebrandt
 * added ini setting readout (zFogDisabled)
 * 1     8.12.00 21:29 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 136 $ ($Modtime: 17.03.01 3:13 $)

// ============================================================================================================

/**********************************************************************************
- comments:
				28.03.00	Changed DirectX-Error handling (DXTryWarning used)
				05.05.00	Added DrawPolySimple()
				06.05.00	Added alpha testing support
				08.09.00	Integrated workaround for Voodoo cards (disable z-buffer write)
				11.09.00	Support for Detonator3 (NVIDIA)
*********************************************************************************/



#include "zcore.h"
#include "zRndD3D_Render.h"
#include <zMemPool.h>
#include "zVertexTransform.h"
#include <zOption.h>
#include "zview.h"
#include "zworld.h"



#ifndef LocLerp
#define LocLerp(t, a, b) ( a + t * (b - a) ) 
#endif

//#define NVIDIA_FARZ_HACK

#define xSetD3D( d, x, y, z, w, c, u, v )	\
{ d.sx = x; d.sy = y; d.sz = z; d.rhw = w;  \
 d.color = c; \
  d.tu = u; d.tv = v; }
#define xSetD3D2( d, x, y, z, w, c, u1, v1, u2, v2 )	\
{ d.sx = x; d.sy = y; d.sz = z; d.rhw = w;  \
 d.color = c; \
  d.tu1 = u1; d.tv1 = v1; d.tu2 = u2; d.tv2 = v2; }

static scalingSetByMatrix = FALSE;


static unsigned short			pri[zMAX_POLY_CLIP_VERTS+1];
static D3DTLVERTEX				vertex[zMAX_POLY_CLIP_VERTS];
struct zD3DTLVERTEX2
{
	D3DVALUE sx;
	D3DVALUE sy;
	D3DVALUE sz;
	D3DVALUE rhw;
	D3DCOLOR color;
	D3DCOLOR specular; 
	D3DVALUE tu1; 
	D3DVALUE tv1; 
	D3DVALUE tu2; 
	D3DVALUE tv2; 
};
static zD3DTLVERTEX2				vertex2[zMAX_POLY_CLIP_VERTS];



zCSurfaceCache_D3D				global_surfaceCache;
zCDXTCCache_D3D					global_DXTCCache;

zTRnd_PolyDrawMode				global_PolyDrawMode;

ID3DXContext					*zCRnd_D3D::xd3d_pd3dx = NULL;
IDirectDraw7					*zCRnd_D3D::xd3d_pdd7 = NULL;
IDirect3D7						*zCRnd_D3D::xd3d_pd3d7 = NULL;
IDirect3DDevice7				*zCRnd_D3D::xd3d_pd3dDevice7 = NULL;
zBOOL							zCRnd_D3D::xd3d_dd7inuse = FALSE;
zBOOL							zCRnd_D3D::xd3d_palsupp = FALSE;
unsigned long					zCRnd_D3D::xd3d_actFrameNumber = 0;

zCVertexBufferDyn				*zD3D_alphaPoly::vertexbufferdyn = NULL;
zCVertexBuffer					*zD3D_alphaPoly::vertexbuffer = NULL;
zBOOL							zD3D_alphaPoly::locked = FALSE;
zDWORD							zD3D_alphaPoly::startvertex = 0;
zDWORD							zD3D_alphaPoly::actvertex = 0;
int								zD3D_alphaPoly::numberofvertices = 0;
int								zD3D_alphaPoly::actnov = 0;

zCSurfaceCache_D3D::zD3D_SlotHeader	
								*zCSurfaceCache_D3D::xsc_listofsurfaces[SURFACECACHECOUNTLIMIT];
int								zCSurfaceCache_D3D::xsc_listposition = 0;

static void Exc_ReleaseRenderer()
{
	if( zrenderer ) 
	{ 
		(( zCRnd_D3D* )zrenderer)->EmergencyExit();
	}
}

const int MAXALPHAPOLYS_WARNING = MAXALPHAPOLYS - 300;




/*--------------------------------------------------------------------------

    zCRnd_D3D :: zCRnd_D3D()

 

    25-Aug-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					Separates xd3d_polysRendered und xd3d_trisRendered entferent (=> nun komplett in xd3d_statistics)

--------------------------------------------------------------------------*/ 
zCRnd_D3D :: zCRnd_D3D() 
{
	zERR_MESSAGE (2, zERR_BEGIN, "X: RND_D3D: Initializing Direct3D ..." );

	DXTryWarning( D3DXInitialize(), "X: [RND3D-Constructor]: Can't initialize D3DX !" );
	zERR_MESSAGE(5,0, "X: [RND3D-Constructor]: D3DXInitialize done" );

	// Settings aus der .ini auslesen
	{
		const char* sectionName		= "RENDERER_D3D";
		xd3d_disableFog				= zoptions->ReadBool (sectionName, "zFogDisabled", FALSE);
		xd3d_enableRadialFog		= zoptions->ReadBool (sectionName, "zFogRadial",   TRUE);
		m_bMustFlushOnAmbientColor	= zoptions->ReadBool (sectionName, "zSyncAmbientCol",   FALSE);
		if (!xd3d_disableFog && xd3d_enableRadialFog) fogType = RADIAL; else
		if (xd3d_disableFog || !xd3d_enableRadialFog) fogType = LINEAR;

	};

	//Notwendige Initialisierungen
	//Disable task switching
	zexhnd.AddUnhandledExceptionReleaseCallback( Exc_ReleaseRenderer ); 
	xd3d_inScene				= FALSE;
	xd3d_pdd7					= NULL;
	xd3d_pd3d7					= NULL;
	xd3d_pd3dDevice7			= NULL;
	xd3d_pd3dx					= NULL;
	xd3d_backlocked				= FALSE;
	xd3d_pfrontBuffer			= NULL;
	xd3d_pbackBuffer			= NULL;
	xd3d_pzBuffer				= NULL;
	xd3d_pclipper				= NULL;
	xd3d_pgammacontrol			= NULL;
	xd3d_pactivematerial		= NULL;
	xd3d_actmaterial.diffuseRGBA = ( 1.0f, 1.0f, 1.0f, 1.0f);
	xd3d_actmaterial.ambientRGBA = ( 1.0f, 1.0f, 1.0f, 1.0f);
	xd3d_newWinHandle			= 0;
	xd3d_winHandle				= 0;
	xd3d_scrMode				= zRND_SCRMODE_FULLSCREEN;
	xd3d_scrWidth				= 0;
	xd3d_scrHeight				= 0;
	xd3d_scrBpp					= 0;	 
	xd3d_mode					= zRND_SCRMODE_FULLSCREEN;
	xd3d_x						= 0;
	xd3d_y						= 0;
	xd3d_bpp					= 0;
	xd3d_num					= -1;
	xd3d_scrStatus				= scrSTATUS_Free;
	xd3d_numAlphaPolys			= 0;
	xd3d_tryDevnum				= 0;

	XD3D_EnumerateModes();
	for( int t = 0; t<MAXTEXTURESTAGES; t++ )
	{
		xd3d_ptexture[t] = 0L;
		xd3d_pd3dtexture[t] = 0L;
	}
	polyDrawMode				= zRND_DRAW_MATERIAL;
	for( t = 0; t<MAXBUCKETS; t++ ) 
		xd3d_alphaSortBucket[t] = NULL;
	for( t = 0; t<MAXRENDERSTATES; t++ )
		xd3d_actRenderState[t] = 0xfafbfcfd;
	for( int s = 0; s<MAXTEXTURESTAGES; s++ )
		for( int t = 0 ; t<zRND_TSS_COUNT ; t++ )
			xd3d_actTexStageState[s][t] = 0xfafbfcfd;
	xd3d_bucketSize				= 1.0;
	xd3d_zMAX_from_Engine		= 2.0;
	xd3d_zMIN_from_Engine		= 0.25f;
	xd3d_scale_A				= 1.0f;
	xd3d_scale_B				= 0.0f;
	xd3d_scale_C				= 1.0f;
	xd3d_savedTexture			= NULL;
	xd3d_deviceChange			= FALSE;
	xd3d_numTexturesUsedThisFrame = 0;
	xd3d_numLightmapsUsedThisFrame = 0;
	xd3d_wBuffer				= FALSE;
	xd3d_alphaTest				= FALSE;
	xd3d_vbclipping				= FALSE;
	xd3d_zwBufferLevel			= zRND_UNKNOWN_BUFFER;
	
	alphaReference				= 0x000000b0;
	m_bAlphaLimitReached		= FALSE;
	m_bCacheAlphaPolys			= TRUE;
	immediateAlphaPolyRoot		= NULL;
	immediateAlphaPolyParent	= NULL;
	m_bAnisotropicFilter		= FALSE;
	ResetStatistics();
	SetSurfaceLost(FALSE);


	zERR_MESSAGE (2, zERR_END, "");
}



/*--------------------------------------------------------------------------

    zCRnd_D3D :: ~zCRnd_D3D() 

 

    25-Aug-00       [PELZER]

--------------------------------------------------------------------------*/ 
zCRnd_D3D :: ~zCRnd_D3D() 
{	
	//Zur Vermeidung einer Endlosschleife im Falle eines Crashs im Destruktor
	zexhnd.RemoveUnhandledExceptionReleaseCallback( Exc_ReleaseRenderer );
	//Sauberer Abriss des Renderer-Objekts
	//Enable task switching
	zERR_MESSAGE(5,0, "X: Shutdown D3D subsystem (Destructor)" );
	xd3d_deviceChange = FALSE;
	XD3D_ClearDevice();
	if( xd3d_scrStatus!=scrSTATUS_Free )
	{	
		XD3D_CloseWin();
	}

	DXTryWarning( D3DXUninitialize(), "X: [RND3D-Destructor]: Can't uninitialize D3DX Utility Library !" );
	zERR_MESSAGE(5,0, "X: [RND3D-Destructor]: D3DXUninitialize done" );
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: EmergencyExit() 

 

    12-Sep-00       [PELZER]

--------------------------------------------------------------------------*/ 
void zCRnd_D3D :: EmergencyExit() 
{	
	//Zur Vermeidung einer Endlosschleife im Falle eines Crashs im Destruktor
	zexhnd.RemoveUnhandledExceptionReleaseCallback( Exc_ReleaseRenderer );
	if( !xd3d_pd3dx )
		return;
 	zERR_MESSAGE(5,0, "X: EmergencyExit: Releasing all DirectX-Objects ..." );
	//Release der einzelnen DirectX-Pointer
	RELEASE( xd3d_pbackBuffer );
	RELEASE( xd3d_pfrontBuffer );
	RELEASE( xd3d_pzBuffer );
	if( xd3d_Capabilities.gamma ) 
		RELEASE( xd3d_pgammacontrol );
	RELEASE( xd3d_pd3dDevice7 );
	RELEASE( xd3d_pd3d7 );
	RELEASE( xd3d_pdd7 );
	RELEASE( xd3d_pd3dx );
	xd3d_pdd7			= NULL;
	xd3d_pd3d7			= NULL;
	xd3d_pd3dDevice7	= NULL;
	xd3d_pd3dx			= NULL;
	if( !DXTryWarning( D3DXUninitialize(), 
		"X: [RND3D]EmergencyExit: Can't uninitialize D3DX Utility Library !" ) )
		return;
	zERR_MESSAGE(5,0, "X: EmergencyExit: D3DXUninitialize done" );
	xd3d_num = -1;
	if( xd3d_scrStatus!=scrSTATUS_Free )
	{	
		XD3D_CloseWin();
	}

	DXTryWarning( D3DXUninitialize(), "X: [RND3D-Destructor]: Can't uninitialize D3DX Utility Library !" );
	zERR_MESSAGE(5,0, "X: [RND3D-Destructor]: D3DXUninitialize done" );
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: DrawPolySimple( zCTexture *texture, zTRndSimpleVertex *simplevertex, int numVert )  

 

    04-Oct-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: DrawPolySimple( zCTexture *texture, zTRndSimpleVertex *simplevertex, int numVert )
{
	//Darstellung eines Polys ausserhalb der Standard-3D-Welt (Titelbild, Inventory, Statusanzeige, etc.)
	//Untersuche, ob die Texture vorhanden ist
	if (!texture)	return;

	const zTResourceCacheState cacheState = texture->CacheIn();
	if (cacheState!=zRES_CACHED_IN)	return;

	if (GetSurfaceLost()) return;

	const zBOOL	fog = GetFog();
	SetFog(FALSE);

	const float zScaleA = 65534.0f/(65534.0f-1.0f);
	const float zScaleB = (-65534.0f*1.0f)/(65534.0f-1.0f);

	zREAL rhw = 1.0f/simplevertex[0].z;
	zREAL sz  = zScaleA + zScaleB *rhw;

	//Verwende die aktuell gesetzte Alpha-Blending-Funktion
	if( xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_MATERIAL ) 
		SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_MODULATE );
	else
		SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_SELECTARG2 );

	//Deaktiviere das Alphatesting
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, xd3d_actStatus.dither );
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
	if( xd3d_actStatus.texwrap )
	{
		SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_WRAP );
		SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_WRAP );
	}
	else
	{
		SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_CLAMP );
		SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_CLAMP );
	}
	SetTextureStageState( 0, zRND_TSS_ALPHAARG1, zRND_TA_TEXTURE );
	SetTextureStageState( 0, zRND_TSS_ALPHAARG2, zRND_TA_DIFFUSE );
	SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
	SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE );
	SetTextureStageState( 0, zRND_TSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
	SetTextureStageState( 0, zRND_TSS_TEXCOORDINDEX, 0 );
	SetTextureStageState( 1, zRND_TSS_COLOROP, zRND_TOP_DISABLE );
	SetZBufferCompare( xd3d_actStatus.zfunc );
	zBOOL alphaFuncBlendOrAdd = FALSE;
	switch( xd3d_actStatus.alphafunc )
	{
		case	zRND_ALPHA_FUNC_BLEND:
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
				XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
				XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
				alphaFuncBlendOrAdd = TRUE;
				break;
		case	zRND_ALPHA_FUNC_ADD:
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
				XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
				XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
				alphaFuncBlendOrAdd = TRUE;
				break;
		case	zRND_ALPHA_FUNC_MUL:
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG1 );
				XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR );
				XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO );
				break;
		case	zRND_ALPHA_FUNC_MUL2:
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG1 );
				XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR );
				XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCCOLOR );
				break;
		case	zRND_ALPHA_FUNC_SUB: //Wird nicht unterstützt
				zERR_WARNING( "X: DrawPolySimple: Not supported alpha blending function !" );
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
				XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
				XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
				alphaFuncBlendOrAdd = TRUE;
				break;
		default:
				if( texture->HasAlpha() )
				{
					XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
					SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
					SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_MODULATE );
					XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
					XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
					alphaFuncBlendOrAdd = TRUE;
				}
				else
				{
					XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
					SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
				}
	}

	//Übergebe die Vertexdaten
	unsigned long intalpha = 0;
	for( int i = 0; i<numVert; i++ )
	{
		if( alphaFuncBlendOrAdd )
		{
			if( xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_CONSTANT )
				intalpha = static_cast<unsigned long>( xd3d_actStatus.alphafactor*simplevertex[i].color.GetAlphaByte() );
			else
				intalpha = simplevertex[i].color.GetAlphaByte();
		}

		xSetD3D( vertex[i], 
				 simplevertex[i].pos[VX], 
				 simplevertex[i].pos[VY], 
				 sz,
				 rhw,
				 (intalpha<<24)
				 |((simplevertex[i].color.GetPackedDWord()<<8)>>8),
				 simplevertex[i].uv[VX], 
				 simplevertex[i].uv[VY] );
	}

	//Setze die Texture
	zCTex_D3D *tex = reinterpret_cast<zCTex_D3D *>( texture );
	tex->InsertTexture( xd3d_actStatus.palsupported );
	XD3D_ResetMultiTexturing();	

	//Deaktiviere das Clipping (Bessere Performance als mit eingeschaltetem DX-Clipping, da sonst eine von 
	//DirectX eine Back-Trafo in den Projektionsraum + Clipping + Projektion in den Screenraum ausgeführt wird!!!)
	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );

	//Zeichne das Polygon
	xd3d_pd3dDevice7->DrawPrimitive( D3DPT_TRIANGLEFAN, D3DFVF_TLVERTEX, (LPVOID) vertex, numVert, 0 );
	xd3d_pactivematerial = NULL;

	// Stats updaten
	xd3d_statistics.numTrisRendered += numVert-2;
	++xd3d_statistics.numPolysRendered;

	SetFog(fog);
}


/*--------------------------------------------------------------------------

    void zCRnd_D3D :: DrawPoly( zCPolygon* poly )  

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
//#include "zsky.h"
void zCRnd_D3D :: DrawPoly( zCPolygon* poly ) 
{
	//Hiermit wird die Darstellung eines Polys in der bestehenden 3D-Welt veranlasst
	//Polys und Dreiecke mitzählen

	if (GetSurfaceLost()) return;

	++xd3d_statistics.numPolysRendered;
	xd3d_statistics.numTrisRendered += poly->numClipVert-2;

	// ACHTUNG: wenn radialer Nebel aktiviert ist, kann mit dieser Methode der Vertex Fog nicht benutzt werden,
	// da dieser nur funktioniert, wenn DX7 die Vertices selber transformiert
	// deswegen wird bei aktiviertem radial nebel hier auf table fog zurückgeschaltet
	// (diese lösung ist nicht perfekt, da teilweise farbdifferenzen zwischen per vertex oder per table eingefärbten
	// polys entstehen - dies kann man eventuell durch anziehen der near fog plane tunen)

	const zBOOL radial			 = xd3d_enableRadialFog && GetFog();
	if (radial)	
	{	
		// auf table fog umschalten
		SetFog(FALSE);
		xd3d_enableRadialFog = FALSE;
		SetFog(TRUE);
	}

//	SetFogColor(zCSkyControler::GetActiveSkyControler()->GetBackgroundColor());

	//SetFogType(LINEAR);

	XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
	//Deaktiviere das Clipping (Bessere Performance als mit eingeschaltetem DX-Clipping, da sonst eine von 
	//DirectX eine Back-Trafo in den Projektionsraum + Clipping + Projektion in den Screenraum ausgeführt wird!!!)
	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	switch( xd3d_renderMode )
	{
	case	zRND_MODE_1_PASS_VERT_LIGHT:
	case	zRND_MODE_DYN_POLYS_VERT_LIGHT:
			XD3D_PolyDrawOnePassVertLight( poly );
			break;
	case	zRND_MODE_1_PASS_MULTITEXTURE:
			XD3D_PolyDrawOnePassMultiTex( poly );
			break;
	case	zRND_MODE_2_PASS_TEXTURE:
			XD3D_PolyDrawTwoPassTexture( poly );
			break;
	case	zRND_MODE_2_PASS_LIGHTMAP:
			XD3D_PolyDrawTwoPassLightMap( poly );
			break;
	default:
			zERR_WARNING( "X: DrawPoly: Not supported render mode !" );
	}

	if (radial)
	{
		// auf vertex fog umschalten
		SetFog(FALSE);
		xd3d_enableRadialFog = TRUE;
		SetFog(TRUE);
	}

	//SetFogType(RADIAL);
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_PolyDrawOnePassVertLight( zCPolygon* poly )  

 

    14-Aug-00       [PELZER]
    16-Nov-00       [MOOS]   Auf neue Vertex-Klasse umgestellt

--------------------------------------------------------------------------*/
void zCRnd_D3D :: XD3D_PolyDrawOnePassVertLight( zCPolygon* poly )
{
	zCMaterial *mat = poly->GetMaterial();
	if( !XD3D_SetMaterial( mat ) )
		return;
	float sz;
	float rhw;
    zCVertexTransform *vert;
    zCVertFeature *feat;

	//Bei Non-Alpha-Blend-Polys erfolgt die Ausgabe sofort
	if( (xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_MATERIAL)
		&&(mat->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_NONE) )
	{
		if( !((xd3d_ptexture[0]!=0L)&&xd3d_ptexture[0]->HasAlpha()) ) 
		{ 
			if( xd3d_ptexture[0]!=0L ) //Verwende die Texture, falls vorhanden ...
			{	
				for( int i=0; i<poly->numClipVert; i++ )
				{					
                    vert = poly->clipVert[i]->VertexTransform();
					feat = poly->clipFeat[i];  
					//sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv)/xd3d_scale_C;
					sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv);
					rhw  = vert->vertCamSpaceZInv;

					xSetD3D( vertex[i], 
							 vert->vertScrX, 
							 vert->vertScrY, 
							 sz,
							 rhw,
							 feat->lightDyn.GetPackedDWord(),
							 feat->texu, 
							 feat->texv );
				}
			}
			else //Verwende Materialfarbe falls keine Textur vorhanden ...
			{
				for( int i=0; i<poly->numClipVert; i++ )
				{	
                    vert = poly->clipVert[i]->VertexTransform();
					feat = poly->clipFeat[i];  
					//sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv)/xd3d_scale_C;
					sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv);
					rhw  = vert->vertCamSpaceZInv;

					xSetD3D( vertex[i], 
							 vert->vertScrX, 
							 vert->vertScrY, 
							 sz,
							 rhw, //Mische dyn. Licht mit der Materialfarbe:
							 (((feat->lightDyn.GetRedByte()*mat->color.GetRedByte())>>8)<<16)
							 |(((feat->lightDyn.GetGreenByte()*mat->color.GetGreenByte())>>8)<<8)
							 |(((feat->lightDyn.GetBlueByte()*mat->color.GetBlueByte())>>8)),
							 0, 
							 0 );
				}
			}
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
			SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
			XD3D_ResetMultiTexturing();	
			if( polyDrawMode!=zRND_DRAW_WIRE ) //Filled-Modus
				xd3d_pd3dDevice7->DrawPrimitive( D3DPT_TRIANGLEFAN, D3DFVF_TLVERTEX, 
												(LPVOID) vertex, poly->numClipVert, 0 );
			else //Wire-Modus
			{	
				int q = 0;
				for( int t = 0; t<poly->numClipVert; t++ )
				{	
					pri[q++] = t;
					vertex[t].color = 0xFFFFFFFF;
				} 
				pri[q++] = 0;
				SetTexture( 0, 0L );
				xd3d_pd3dDevice7->DrawIndexedPrimitive( D3DPT_LINESTRIP, D3DFVF_TLVERTEX, 
												(LPVOID) vertex, poly->numClipVert, (LPWORD) pri, q, 0 );
			}
		}
		else
		{
			//Bei Alpha-Test-Unterstützung Alpha-Channel-Texturen sofort rendern
			if( ((xd3d_ptexture[0]!=0L)&&xd3d_ptexture[0]->HasAlpha()&&xd3d_alphaTest) )
			{
				XD3D_AlphaTestPoly( poly);
			}
		}
		return;
	}
	//Ausgabe bei Alpha-Polys erfolgt später [FlushPolys()]
	XD3D_AlphaBlendPoly( poly, mat );
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_PolyDrawOnePassMultiTex( zCPolygon *poly )  

 

    14-Aug-00       [PELZER]
    11-Nov-00       [MOOS]    Neue Lightmap-Kklasse

--------------------------------------------------------------------------*/
void zCRnd_D3D :: XD3D_PolyDrawOnePassMultiTex( zCPolygon *poly )
{
	zCMaterial *mat = poly->GetMaterial();
	XD3D_SetMaterial( mat );

	zCVertFeature     *feat;  
    zCVertexTransform *vert;

	if( polyDrawMode!=zRND_DRAW_MATERIAL ) 
		return;
    zCLightMap *lm = poly->GetLightmap();
	zCTex_D3D *tex = static_cast<zCTex_D3D*>( lm->Texture() );
	if( tex )
	{
		zTResourceCacheState cacheState = tex->CacheIn();
		if( cacheState!=zRES_CACHED_IN )
			tex=0;
	}
	if( !tex ) //Falls keine Lightmap-Texture vorhanden, verwende nur das Vertex-Light
	{
		XD3D_PolyDrawOnePassVertLight( poly );
		return;
	}
	tex->InsertTexture( xd3d_actStatus.palsupported, 1 );
	zREAL utex2;
	zREAL vtex2;
	float sz;
	float rhw;

	if( (mat->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_NONE)
		&&!((xd3d_ptexture[0]!=0L)&&xd3d_ptexture[0]->HasAlpha()) )
	{ 
		if( xd3d_ptexture[0]!=0L ) //Verwende die Texture, falls vorhanden ...
		{	
			for( int i=0; i<poly->numClipVert; i++ )
			{		
				lm->GetLightmapTexCoords( poly->clipVert[i]->position, utex2, vtex2 );
            
                vert = poly->clipVert[i]->VertexTransform();
				feat = poly->clipFeat[i];  
				//sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv)/xd3d_scale_C;
				sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv);
				rhw  = vert->vertCamSpaceZInv; 

				xSetD3D2( vertex2[i], 
						 vert->vertScrX, 
						 vert->vertScrY, 
						 sz,
						 rhw,
						 feat->lightDyn.GetPackedDWord(),
						 feat->texu, 
						 feat->texv,
						 utex2, 
						 vtex2 );
			}
		}
		else //Verwende Materialfarbe falls keine Textur vorhanden ...
		{
			for( int i=0; i<poly->numClipVert; i++ )
			{	
				lm->GetLightmapTexCoords( poly->clipVert[i]->position, utex2, vtex2 );

                vert = poly->clipVert[i]->VertexTransform();
				feat = poly->clipFeat[i];  
				//sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv)/xd3d_scale_C;
				sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv);
				rhw  = vert->vertCamSpaceZInv; 

				xSetD3D2( vertex2[i], 
						 vert->vertScrX, 
						 vert->vertScrY, 
						 sz,
						 rhw, //Mische dyn. Licht mit der Materialfarbe:
						 (((feat->lightDyn.GetRedByte()*mat->color.GetRedByte())>>8)<<16)
						 |(((feat->lightDyn.GetGreenByte()*mat->color.GetGreenByte())>>8)<<8)
						 |(((feat->lightDyn.GetBlueByte()*mat->color.GetBlueByte())>>8)),
						 0, 
						 0,
						 utex2, 
						 vtex2 );
			}
		}
		if( polyDrawMode!=zRND_DRAW_WIRE ) //Filled-Modus
		{
			SetTextureStageState( 1, zRND_TSS_COLOROP, zRND_TOP_ADD );
			SetTextureStageState( 1, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
			SetTextureStageState( 1, zRND_TSS_COLORARG2, zRND_TA_CURRENT );
			xd3d_pd3dDevice7->DrawPrimitive( D3DPT_TRIANGLEFAN, D3DFVF_TLVERTEX, 
											(LPVOID) vertex, poly->numClipVert, 0 );
		}
		else //Wire-Modus
		{	
			int q = 0;
			for( int t = 0; t<poly->numClipVert; t++ )
			{	
				pri[q++] = t;
				vertex[t].color = 0xFFFFFFFF;
			} 
			pri[q++] = 0;
			SetTexture( 0, 0L );
			xd3d_pd3dDevice7->DrawIndexedPrimitive( D3DPT_LINESTRIP, D3DFVF_TLVERTEX, 
											(LPVOID) vertex, poly->numClipVert, (LPWORD) pri, q, 0 );
		}
		return;
	}
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_PolyDrawTwoPassTexture( zCPolygon *poly )  

 

    14-Aug-00       [PELZER]
    16-Nov-00       [MOOS]   Auf neue Vertex-Klasse umgestellt

--------------------------------------------------------------------------*/
void zCRnd_D3D :: XD3D_PolyDrawTwoPassTexture( zCPolygon *poly )
{
	zCMaterial *mat = poly->GetMaterial();
	if( !XD3D_SetMaterial( mat ) )
		return;
	float sz;
	float rhw;
    zCVertFeature     *feat;  
    zCVertexTransform *vert;

	//Bei Non-Alpha-Polys erfolgt die Ausgabe sofort
	if( (xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_MATERIAL)
		&&(mat->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_NONE) )
	{	
		if(	!((xd3d_ptexture[0]!=0L)&&xd3d_ptexture[0]->HasAlpha()) ) 
		{ 
			if( poly->GetLightmap()==0 ) 
			{
				if( xd3d_ptexture[0]!=0L ) //Verwende die Texture, falls vorhanden ...
				{	
					for( int i=0; i<poly->numClipVert; i++ )
					{					
                        vert = poly->clipVert[i]->VertexTransform();
						feat = poly->clipFeat[i];  
						//sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv)/xd3d_scale_C;
						sz   = (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv);
						rhw  = vert->vertCamSpaceZInv; 

						xSetD3D( vertex[i], 
								 vert->vertScrX, 
								 vert->vertScrY, 
								 sz,
								 rhw,
								 feat->lightDyn.GetPackedDWord(),
								 feat->texu, 
								 feat->texv );
					}
				}
				else //Verwende Materialfarbe falls keine Textur vorhanden ...
				{
					for( int i=0; i<poly->numClipVert; i++ )
					{	
                        vert = poly->clipVert[i]->VertexTransform();
						feat = poly->clipFeat[i];  
						//sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv)/xd3d_scale_C;
						sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv);
						rhw  = vert->vertCamSpaceZInv; 

						xSetD3D( vertex[i], 
								 vert->vertScrX, 
								 vert->vertScrY, 
								 sz,
								 rhw, //Mische dyn. Licht mit der Materialfarbe:
								 (((feat->lightDyn.GetRedByte()*mat->color.GetRedByte())>>8)<<16)
								 |(((feat->lightDyn.GetGreenByte()*mat->color.GetGreenByte())>>8)<<8)
								 |(((feat->lightDyn.GetBlueByte()*mat->color.GetBlueByte())>>8)),
								 0, 
								 0 );
					}
				}
			}
			else
			{
				if( xd3d_ptexture[0]!=0L ) //Verwende die Texture, falls vorhanden ...
				{	
					for( int i=0; i<poly->numClipVert; i++ )
					{					
                        vert = poly->clipVert[i]->VertexTransform();
						feat = poly->clipFeat[i];  
						//sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv)/xd3d_scale_C;
						sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv);
						rhw  = vert->vertCamSpaceZInv; 

						xSetD3D( vertex[i], 
								 vert->vertScrX, 
								 vert->vertScrY, 
								 sz,
								 rhw,
								 0xffffffff,
								 feat->texu, 
								 feat->texv );
					}
				}
				else //Verwende Materialfarbe falls keine Textur vorhanden ...
				{
					for( int i=0; i<poly->numClipVert; i++ )
					{	
                        vert = poly->clipVert[i]->VertexTransform();						
						//sz = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv)/xd3d_scale_C;
						sz = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv);
						rhw = vert->vertCamSpaceZInv; 
						xSetD3D( vertex[i], 
								 vert->vertScrX, 
								 vert->vertScrY, 
								 sz,
								 rhw,
								 mat->color.GetPackedDWord(),
								 0, 
								 0 );
					}
				}
			}
			XD3D_ResetMultiTexturing();	
			if( polyDrawMode!=zRND_DRAW_WIRE ) //Filled-Modus
				xd3d_pd3dDevice7->DrawPrimitive( D3DPT_TRIANGLEFAN, D3DFVF_TLVERTEX, 
												(LPVOID) vertex, poly->numClipVert, 0 );
			else //Wire-Modus
			{	
				int q = 0;
				for( int t = 0; t<poly->numClipVert; t++ )
				{	
					pri[q++] = t;
					vertex[t].color = 0xFFFFFFFF;
				} 
				pri[q++] = 0;
				SetTexture( 0, 0L );
				xd3d_pd3dDevice7->DrawIndexedPrimitive( D3DPT_LINESTRIP, D3DFVF_TLVERTEX, 
												(LPVOID) vertex, poly->numClipVert, (LPWORD) pri, q, 0 );
			}
		}
		else
		{
			//Bei Alpha-Test-Unterstützung Alpha-Channel-Texturen sofort rendern
			if( ((xd3d_ptexture[0]!=0L)&&xd3d_ptexture[0]->HasAlpha()&&xd3d_alphaTest) )
				XD3D_AlphaTestPoly( poly);
		}
		return;
	}
	//Ausgabe bei Alpha-Polys erfolgt später [FlushPolys()]
	XD3D_AlphaBlendPoly( poly, mat );
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_AlphaTestPoly( zCPolygon* poly )  

 

    14-Aug-00       [PELZER]
    16-Nov-00       [MOOS]   Auf neue Vertex-Klasse umgestellt

--------------------------------------------------------------------------*/
inline void zCRnd_D3D :: XD3D_AlphaTestPoly( zCPolygon* poly )
{
	//Darstellung eines Alphapolys mit aktiviertem Alphatesting
	float sz;
	float rhw;
    zCVertFeature     *feat;
    zCVertexTransform *vert;

	for( int i = 0; i<poly->numClipVert; i++ )
	{	
        vert = poly->clipVert[i]->VertexTransform();
		feat = poly->clipFeat[i];
		//sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv)/xd3d_scale_C;
		sz   = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv);
		rhw  = vert->vertCamSpaceZInv; 

		xSetD3D( vertex[i], 
				 vert->vertScrX, 
				 vert->vertScrY,  
				 sz,
				 rhw,
				 feat->lightDyn.GetPackedDWord(),
				 feat->texu, 
				 feat->texv );
	}
	XD3D_ResetMultiTexturing();
	if( polyDrawMode!=zRND_DRAW_WIRE ) //Filled-Modus
		xd3d_pd3dDevice7->DrawPrimitive( D3DPT_TRIANGLEFAN, D3DFVF_TLVERTEX, 
										(LPVOID) vertex, poly->numClipVert, 0 );
	else //Wire-Modus
	{	
		int q = 0;
		for( int t = 0; t<poly->numClipVert; t++ )
		{	
			pri[q++] = t;
			vertex[t].color = 0xFFFFFFFF;
		} 
		pri[q++] = 0;
		SetTexture( 0, 0L );
		xd3d_pd3dDevice7->DrawIndexedPrimitive( D3DPT_LINESTRIP, D3DFVF_TLVERTEX, 
										(LPVOID) vertex, poly->numClipVert, (LPWORD) pri, q, 0 );
	}
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_AlphaBlendPoly( zCPolygon* poly, zCMaterial *mat )  

 

    04-Sep-00       [PELZER]
    16-Nov-00       [MOOS]   
					Auf neue Vertex-Klasse umgestellt
    22-Nov-00       [HILDEBRANDT]
					numAlphaPolys werden nun auch in den Stastics mitgezaehlt
--------------------------------------------------------------------------*/

inline void zCRnd_D3D :: XD3D_AlphaBlendPoly( zCPolygon* poly, zCMaterial *mat )
{
	// Vorbereitung der späteren Darstellung eines normalen Alphapolys

	if (xd3d_numAlphaPolys>=MAXALPHAPOLYS_WARNING)
	{
		m_bAlphaLimitReached = TRUE;

		if( xd3d_numAlphaPolys>=MAXALPHAPOLYS )
		{
			// [BENDLIN] Addon Patch - Warning reicht - crasht sonst beim kleinen Feuersturm
#ifdef GOLDMASTER
			zERR_WARNING	( "X: XD3D_AlphaBlendPoly: xd3d_numAlphaPolys>=MAXALPHAPOLYS (Too many alphapolys)" );
#else
			zERR_FAULT_ONCE	( "X: XD3D_AlphaBlendPoly: xd3d_numAlphaPolys>=MAXALPHAPOLYS (Too many alphapolys)" );
#endif
			return;
		}
	}
	else m_bAlphaLimitReached = FALSE;

	zD3D_alphaPoly *AP		= &xd3d_alphaPolyPool[xd3d_numAlphaPolys];

	//Fülle den AlphaPoly-Listen-Eintrag mit allen später benötigten Daten
	AP->tex					= xd3d_ptexture[0];
	AP->wrap				= xd3d_actStatus.texwrap;
	zTRnd_AlphaBlendSource alphaSource = ((xd3d_ptexture[0]!=0L)&&xd3d_ptexture[0]->HasAlpha()) ? zRND_ALPHA_SOURCE_MATERIAL : xd3d_actStatus.alphasrc;
	AP->zfunc				= xd3d_actStatus.zfunc;
	AP->zBias				= xd3d_actStatus.zbias;

	if ((alphaSource==zRND_ALPHA_SOURCE_CONSTANT)&&(mat->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_NONE))
		AP->alphafunc		= xd3d_actStatus.alphafunc; //Verwende die global gesetzte Alphablendfunc, falls das Material keine eigene hat
	else
		AP->alphafunc		= mat->GetAlphaBlendFunc();

	//
	AP->numVert				= poly->numClipVert;
	if (AP->numVert>zD3D_alphaPoly::zMAX_VERT)		AP->numVert = zD3D_alphaPoly::zMAX_VERT;

	unsigned long	intalpha;
	float			sz;
	float			rhw;
	float			midz				= 0;
//	const float		xd3d_scale_C_INV	= 1.0F / xd3d_scale_C;
	const zDWORD	alphaFactorInt		= zDWORD(zFloat2Int(xd3d_actStatus.alphafactor*256));
	const zDWORD	matAlphaInt			= zDWORD(mat->GetAlpha());

	// Auf erwartetes Speicherlayout testen
	zERR_ASSERT ( (&(AP->vertexList[0].a_sx)+1) == &(AP->vertexList[0].a_sy));
	zERR_ASSERT ( (&(AP->vertexList[0].a_tu)+1) == &(AP->vertexList[0].a_tv));
	zERR_ASSERT ( (&(poly->clipFeat[0]->texu)+1) == &(poly->clipFeat[0]->texv));

	if (xd3d_ptexture[0]!=0L) 
	{
		// Verwende die Texture, falls vorhanden ...
		for (int i = 0; i<AP->numVert; i++)
		{	
			zCVertFeature *feat=poly->clipFeat[i];
			if ((alphaSource==zRND_ALPHA_SOURCE_CONSTANT))
			{
				intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte())) >> 8;
			} else
			{
				if( (xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_CONSTANT) )
					intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 16;
				else
					intalpha = (zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 8;
			};

			zCVertexTransform *vert				= poly->clipVert[i]->VertexTransform();
			rhw									= vert->vertCamSpaceZInv;
			//midz								+= 1.0f/rhw;
			midz								+= vert->vertCamSpace.n[VZ];

			// ScreenX/Y als ein Element kopieren
			*((zVEC2*)(&AP->vertexList[i].a_sx))= *((zVEC2*)(&vert->vertScrX));

			//AP->vertexList[i].a_sz				= (xd3d_scale_A + xd3d_scale_B * vert->vertCamSpaceZInv) * xd3d_scale_C_INV;
			AP->vertexList[i].a_sz				= (xd3d_scale_A + xd3d_scale_B * vert->vertCamSpaceZInv);
			AP->vertexList[i].a_rhw				= rhw;
			AP->vertexList[i].a_color			= (intalpha<<24) | ((feat->lightDyn.GetPackedDWord()<<8)>>8);

			// TexUV als ein Element kopieren
			*((zVEC2*)(&AP->vertexList[i].a_tu))= *((zVEC2*)(&feat->texu));
		}
	} else
	{
		// Verwende Materialfarbe falls keine Textur vorhanden ...
		for (int i = 0; i<AP->numVert; i++)
		{	
			zCVertFeature *feat=poly->clipFeat[i];
			if ((alphaSource==zRND_ALPHA_SOURCE_CONSTANT))
			{
				intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte())) >> 8;
			} else
			{
				if( (xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_CONSTANT) )
					intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 16;
				else
					intalpha = (zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 8;
			};

			zCVertexTransform *vert		= poly->clipVert[i]->VertexTransform();
			//sz							= (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv) * xd3d_scale_C_INV;
			sz							= (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv);
			rhw							= vert->vertCamSpaceZInv;
			midz						+= vert->vertCamSpace.n[VZ];
			//midz						+= 1.0f/rhw;
			AP->vertexList[i].a_sx		= vert->vertScrX;
			AP->vertexList[i].a_sy		= vert->vertScrY;
			AP->vertexList[i].a_sz		= sz;
			AP->vertexList[i].a_rhw		= rhw;
			AP->vertexList[i].a_color	= (intalpha<<24) //Mische dyn. Licht mit der Materialfarbe:
										  | (((feat->lightDyn.GetRedByte()*mat->color.GetRedByte())>>8)<<16)
										  | (((feat->lightDyn.GetGreenByte()*mat->color.GetGreenByte())>>8)<<8)
										  | (((feat->lightDyn.GetBlueByte()*mat->color.GetBlueByte())>>8));
		}
	};


	static int   lastNumVert	= -1;
	static float ooLastNumVert	= -1;

	if (lastNumVert!=AP->numVert)
	{
		lastNumVert		= AP->numVert;
		ooLastNumVert	= 1.0f/lastNumVert;
	}

	midz					*= ooLastNumVert;
	AP->SetZValue			( midz );
	AddAlphaSortObject		( AP );
	++xd3d_numAlphaPolys;
	++xd3d_statistics.numAlphaPolys;
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_AlphaBlendPoly( zCPolygon* poly, zCMaterial *mat )  

 

    04-Sep-00       [PELZER]
    16-Nov-00       [MOOS]   
					Auf neue Vertex-Klasse umgestellt
    22-Nov-00       [HILDEBRANDT]
					numAlphaPolys werden nun auch in den Stastics mitgezaehlt
--------------------------------------------------------------------------*/

inline void zCRnd_D3D :: AddAlphaPoly(const zCPolygon* poly)
{
	// Vorbereitung der späteren Darstellung eines normalen Alphapolys
	zCMaterial *mat = poly->GetMaterial();

	if( !XD3D_SetMaterial( mat ) ) return;

	++xd3d_statistics.numPolysRendered;
	xd3d_statistics.numTrisRendered += poly->numClipVert-2;


	zD3D_alphaPoly *AP		= &xd3d_alphaPolyPool[xd3d_numAlphaPolys];

	if (!immediateAlphaPolyRoot) immediateAlphaPolyRoot = AP;

	//Fülle den AlphaPoly-Listen-Eintrag mit allen später benötigten Daten
	AP->tex					= xd3d_ptexture[0];
	AP->wrap				= xd3d_actStatus.texwrap;
	zTRnd_AlphaBlendSource alphaSource = ((xd3d_ptexture[0]!=0L)&&xd3d_ptexture[0]->HasAlpha()) ? zRND_ALPHA_SOURCE_MATERIAL : xd3d_actStatus.alphasrc;
	AP->zfunc				= xd3d_actStatus.zfunc;
	AP->zBias				= xd3d_actStatus.zbias;

	if ((alphaSource==zRND_ALPHA_SOURCE_CONSTANT)&&(mat->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_NONE))
		AP->alphafunc		= xd3d_actStatus.alphafunc; //Verwende die global gesetzte Alphablendfunc, falls das Material keine eigene hat
	else
		AP->alphafunc		= mat->GetAlphaBlendFunc();

	//
	AP->numVert				= poly->numClipVert;
	if (AP->numVert>zD3D_alphaPoly::zMAX_VERT)		
		AP->numVert = zD3D_alphaPoly::zMAX_VERT;

	unsigned long	intalpha;
	float			sz;
	float			rhw;
	float			midz				= 0;
	const zDWORD	alphaFactorInt		= zDWORD(zFloat2Int(xd3d_actStatus.alphafactor*256));
	const zDWORD	matAlphaInt			= zDWORD(mat->GetAlpha());

	// Auf erwartetes Speicherlayout testen
	zERR_ASSERT ( (&(AP->vertexList[0].a_sx)+1) == &(AP->vertexList[0].a_sy));
	zERR_ASSERT ( (&(AP->vertexList[0].a_tu)+1) == &(AP->vertexList[0].a_tv));
	zERR_ASSERT ( (&(poly->clipFeat[0]->texu)+1) == &(poly->clipFeat[0]->texv));

	if (xd3d_ptexture[0]!=0L) 
	{
		// Verwende die Texture, falls vorhanden ...
		for (int i = 0; i<AP->numVert; i++)
		{	
			zCVertFeature *feat=poly->clipFeat[i];
			if ((alphaSource==zRND_ALPHA_SOURCE_CONSTANT))
			{
				intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte())) >> 8;
			} else
			{
				if( (xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_CONSTANT) )
					intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 16;
				else
					intalpha = (zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 8;
			};

			zCVertexTransform *vert				= poly->clipVert[i]->VertexTransform();
			rhw									= vert->vertCamSpaceZInv;
			//midz								+= 1.0f/rhw;
			midz								+= vert->vertCamSpace.n[VZ];

			// ScreenX/Y als ein Element kopieren
			*((zVEC2*)(&AP->vertexList[i].a_sx))= *((zVEC2*)(&vert->vertScrX));

			//AP->vertexList[i].a_sz				= (xd3d_scale_A + xd3d_scale_B * vert->vertCamSpaceZInv) * xd3d_scale_C_INV;
			AP->vertexList[i].a_sz				= (xd3d_scale_A + xd3d_scale_B * vert->vertCamSpaceZInv);
			AP->vertexList[i].a_rhw				= rhw;
			AP->vertexList[i].a_color			= (intalpha<<24) | ((feat->lightDyn.GetPackedDWord()<<8)>>8);

			// TexUV als ein Element kopieren
			*((zVEC2*)(&AP->vertexList[i].a_tu))= *((zVEC2*)(&feat->texu));
		}
	} else
	{
		// Verwende Materialfarbe falls keine Textur vorhanden ...
		for (int i = 0; i<AP->numVert; i++)
		{	
			zCVertFeature *feat=poly->clipFeat[i];
			if ((alphaSource==zRND_ALPHA_SOURCE_CONSTANT))
			{
				intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte())) >> 8;
			} else
			{
				if( (xd3d_actStatus.alphasrc==zRND_ALPHA_SOURCE_CONSTANT) )
					intalpha = (alphaFactorInt * zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 16;
				else
					intalpha = (zDWORD(feat->lightDyn.GetAlphaByte()) * matAlphaInt) >> 8;
			};

			zCVertexTransform *vert		= poly->clipVert[i]->VertexTransform();
			//sz							= (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv) * xd3d_scale_C_INV;
			sz							= (xd3d_scale_A+xd3d_scale_B*vert->vertCamSpaceZInv);
			rhw							= vert->vertCamSpaceZInv;
			midz						+= vert->vertCamSpace.n[VZ];
			//midz						+= 1.0f/rhw;
			AP->vertexList[i].a_sx		= vert->vertScrX;
			AP->vertexList[i].a_sy		= vert->vertScrY;
			AP->vertexList[i].a_sz		= sz;
			AP->vertexList[i].a_rhw		= rhw;
			AP->vertexList[i].a_color	= (intalpha<<24) //Mische dyn. Licht mit der Materialfarbe:
										  | (((feat->lightDyn.GetRedByte()*mat->color.GetRedByte())>>8)<<16)
										  | (((feat->lightDyn.GetGreenByte()*mat->color.GetGreenByte())>>8)<<8)
										  | (((feat->lightDyn.GetBlueByte()*mat->color.GetBlueByte())>>8));
		}
	};


	static int   lastNumVert	= -1;
	static float ooLastNumVert	= -1;

	if (lastNumVert!=AP->numVert)
	{
		lastNumVert		= AP->numVert;
		ooLastNumVert	= 1.0f/lastNumVert;
	}

	midz					*= ooLastNumVert;
	AP->SetZValue			( midz );
	AP->SetNext				( NULL );

	if (immediateAlphaPolyParent) immediateAlphaPolyParent->SetNext(AP);

	immediateAlphaPolyParent = AP;

	++xd3d_numAlphaPolys;
	++xd3d_statistics.numAlphaPolys;
}


void	zCRnd_D3D :: FlushAlphaPolys()
{
	if (immediateAlphaPolyRoot) 
	{
		SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
		//Deaktiviere das Clipping (Bessere Performance als mit eingeschaltetem DX-Clipping, da sonst eine von 
		//DirectX eine Back-Trafo in den Projektionsraum + Clipping + Projektion in den Screenraum ausgeführt wird!!!)
		XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
		XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );

		zCRndAlphaSortObject *nextObj	= immediateAlphaPolyRoot;
		zCRndAlphaSortObject *thisObj;
		immediateAlphaPolyRoot			= 0;
		immediateAlphaPolyParent		= 0;

		int totalNum = 0;
		while (nextObj)
		{
			thisObj = nextObj;
			nextObj->Draw(totalNum++);
			nextObj = nextObj->GetNext();
			thisObj->SetNext(NULL);
		}

		xd3d_numAlphaPolys -= totalNum;
	};
};





/*--------------------------------------------------------------------------

    void zCRnd_D3D :: XD3D_PolyDrawTwoPassLightMap( zCPolygon *poly )  

 

    06-Sep-00       [PELZER]
    16-Nov-00       [MOOS]   Auf neue Vertex-Klasse umgestellt

--------------------------------------------------------------------------*/
void zCRnd_D3D :: XD3D_PolyDrawTwoPassLightMap( zCPolygon *poly )
{
	//Ausgabe eines Lightmap-Polys
	zCLightMap *lm = poly->GetLightmap();
	zCTex_D3D *tex = static_cast<zCTex_D3D*>( lm->Texture() );
	if( tex )
	{
		zTResourceCacheState cacheState = tex->CacheIn();
		if( cacheState!=zRES_CACHED_IN )
			tex = 0;
	};
	if( !tex ) 
		return;
	tex->InsertTexture( xd3d_actStatus.palsupported );
	zREAL utex;
	zREAL vtex;
	float sz;
	float rhw;
	for( int i=0; i<poly->numClipVert; i++ )
	{	
		lm->GetLightmapTexCoords( poly->clipVert[i]->position, utex, vtex );

        zCVertexTransform *vert = poly->clipVert[i]->VertexTransform();
		zCVertFeature     *feat = poly->clipFeat[i];
		//sz  = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv)/xd3d_scale_C;
		sz  = (xd3d_scale_A+xd3d_scale_B * vert->vertCamSpaceZInv);
		rhw = vert->vertCamSpaceZInv; 

		xSetD3D( vertex[i], 
				 vert->vertScrX, 
				 vert->vertScrY, 
				 sz,
				 rhw,
				 feat->lightDyn.GetPackedDWord(),
				 utex, 
				 vtex );
	}
	XD3D_ResetMultiTexturing();
	xd3d_pd3dDevice7->DrawPrimitive( D3DPT_TRIANGLEFAN, D3DFVF_TLVERTEX, 
									(LPVOID) vertex, poly->numClipVert, 0 );
	xd3d_pactivematerial = NULL;
}


/*--------------------------------------------------------------------------

    void zCRnd_D3D :: DrawLightmapList( zCPolygon** polyList, int numPoly )  

 

    14-Aug-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					Separates xd3d_polysRendered und xd3d_trisRendered entferent (=> nun komplett in xd3d_statistics)

--------------------------------------------------------------------------*/

void zCRnd_D3D :: DrawLightmapList( zCPolygon** polyList, int numPoly )
{
	//Deaktiviere das Clipping (Bessere Performance als mit eingeschaltetem DX-Clipping, da sonst eine von 
	//DirectX eine Back-Trafo in den Projektionsraum + Clipping + Projektion in den Screenraum ausgeführt wird!!!)
	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	//Abarbeitung einer Liste von PolyDrawTwoPassLightMap-Befehlen
	//Polys mitzählen
	xd3d_statistics.numPolysRendered += numPoly;
	for( int i=0; i<numPoly; i++ ) 	
	{
		//Dreiecke mitzählen
		xd3d_statistics.numTrisRendered += polyList[i]->numClipVert-2;
		XD3D_PolyDrawTwoPassLightMap( polyList[i] );
	}
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: SetPixel( float x, float y, const zCOLOR c )  

 

    08-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: SetPixel( float x, float y, const zCOLOR c )
{	
	//Deaktiviere das Clipping (Bessere Performance als mit eingeschaltetem DX-Clipping, da sonst eine von 
	//DirectX eine Back-Trafo in den Projektionsraum + Clipping + Projektion in den Screenraum ausgeführt wird!!!)
	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	//Ein einzelnes Pixel darstellen
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
	XD3D_ResetMultiTexturing();
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE ); 
	SetZBufferCompare( xd3d_actStatus.zfunc );
	SetTexture( 0, 0L );
	DWORD dwValue;
	xd3d_pd3dDevice7->GetTextureStageState( 0, D3DTSS_COLOROP, &dwValue ); 
	xSetD3D( vertex[0], x, y, 0.0f, 1.0f, 0xff000000|c.GetPackedDWord(), 0, 0 );	
	xd3d_pd3dDevice7->DrawPrimitive( D3DPT_POINTLIST, D3DFVF_TLVERTEX, 
									(LPVOID) vertex, 1, 0 );
	SetTextureStageState( 0, zRND_TSS_COLOROP, dwValue ); 
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
	XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, xd3d_actStatus.zfunc );
	xd3d_pactivematerial = NULL;
}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: DrawLine( float x1, float y1, float x2, float y2, const zCOLOR col ) 

 

    08-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: DrawLine( float x1, float y1, float x2, float y2, const zCOLOR col )
{	
	//Deaktiviere das Clipping (Bessere Performance als mit eingeschaltetem DX-Clipping, da sonst eine von 
	//DirectX eine Back-Trafo in den Projektionsraum + Clipping + Projektion in den Screenraum ausgeführt wird!!!)

	const zBOOL	fog = GetFog();
	SetFog(FALSE);

	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	//Eine Linie darstellen
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	SetTextureStageState( 0, zRND_TSS_COLOROP, D3DTOP_MODULATE );
	XD3D_ResetMultiTexturing();
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE ); 
	SetZBufferCompare( xd3d_actStatus.zfunc );
	SetTexture( 0, 0L );
	DWORD dwValue;
	xd3d_pd3dDevice7->GetTextureStageState( 0, D3DTSS_COLOROP, &dwValue ); 
	xSetD3D( vertex[0], x1, y1, 0.0f, 1.0f, 0xff000000|col.GetPackedDWord(), 0, 0 );
	xSetD3D( vertex[1], x2, y2, 0.0f, 1.0f, 0xff000000|col.GetPackedDWord(), 0, 0 );
	xd3d_pd3dDevice7->DrawPrimitive( D3DPT_LINELIST, D3DFVF_TLVERTEX, 
									(LPVOID) vertex, 2, 0 );
	SetTextureStageState( 0, zRND_TSS_COLOROP, dwValue ); 
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
	XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, xd3d_actStatus.zd3dfunc );
	xd3d_pactivematerial = NULL;

	SetFog(fog);

}



/*--------------------------------------------------------------------------

    void zCRnd_D3D::DrawLineZ( float x1Scr,float y1Scr,float z1CamSpaceInv, float x2Scr,float y2Scr,float z2CamSpaceInv,const zCOLOR col )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D::DrawLineZ( float x1Scr,float y1Scr,float z1CamSpaceInv,
							float x2Scr,float y2Scr,float z2CamSpaceInv,const zCOLOR col )
{

	const zBOOL	fog = GetFog();
	SetFog(FALSE);

	//Deaktiviere das Clipping (Bessere Performance als mit eingeschaltetem DX-Clipping, da sonst eine von 
	//DirectX eine Back-Trafo in den Projektionsraum + Clipping + Projektion in den Screenraum ausgeführt wird!!!)
	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	//Eine Line mit Tiefeninformation darstellen
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
	XD3D_ResetMultiTexturing();
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE ); 
	SetZBufferCompare( xd3d_actStatus.zfunc );
	SetTexture( 0, 0L );
	DWORD dwValue;
	xd3d_pd3dDevice7->GetTextureStageState( 0, D3DTSS_COLOROP, &dwValue ); 

	//float sz = (xd3d_scale_A+xd3d_scale_B*z1CamSpaceInv)/xd3d_scale_C;
	float sz = (xd3d_scale_A+xd3d_scale_B*z1CamSpaceInv);
	float rhw	= z1CamSpaceInv; 
	xSetD3D( vertex[0], x1Scr, y1Scr, sz, rhw, 0xff000000|col.GetPackedDWord(), 0, 0 );
	rhw = z2CamSpaceInv; 
	//sz = (xd3d_scale_A+xd3d_scale_B*z2CamSpaceInv)/xd3d_scale_C;
	sz = (xd3d_scale_A+xd3d_scale_B*z2CamSpaceInv);
	xSetD3D( vertex[1], x2Scr, y2Scr, sz, rhw, 0xff000000|col.GetPackedDWord(), 0, 0 );
	xd3d_pd3dDevice7->DrawPrimitive( D3DPT_LINELIST, D3DFVF_TLVERTEX, 
									(LPVOID) vertex, 2, 0 );
	SetTextureStageState( 0, zRND_TSS_COLOROP, dwValue );
	xd3d_pactivematerial = NULL;

	SetFog(fog);

}



/*--------------------------------------------------------------------------

    void zCRnd_D3D :: FlushPolys()

 

    12-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: FlushPolys()
{
	RenderAlphaSortList();
}



/*--------------------------------------------------------------------------

    zBOOL zCRnd_D3D :: XD3D_SetMaterial( zCMaterial *material )

 

    12-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
inline zBOOL zCRnd_D3D :: XD3D_SetMaterial( zCMaterial *material )
{
	//Falls das Material bereits aktiv ist, ciao ...
	if( (material==xd3d_pactivematerial)&&(material->GetTexture()==xd3d_ptexture[0]) )
		return TRUE;

	//Falls das Material aktiviert werden muss ...
	xd3d_pactivematerial = material;
	//Setze die z-Buffer-Test-Eigenschaften
	switch( xd3d_actStatus.zfunc )
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

	//Setze die Blending-Funktion
	zTRnd_AlphaBlendFunc afunc;
	afunc = material->GetAlphaBlendFunc();
	xd3d_ptexture[0] = static_cast<zCTex_D3D*>( material->GetAniTexture() );
	if( (xd3d_ptexture[0]!=0L)&&(polyDrawMode==zRND_DRAW_MATERIAL) )
	{
		zTResourceCacheState cacheState = xd3d_ptexture[0]->CacheIn();
		if( cacheState!=zRES_CACHED_IN )
		{
			if( afunc!=zRND_ALPHA_FUNC_NONE )
				return FALSE;
			xd3d_ptexture[0] = 0L;
		}
	}

	if( xd3d_ptexture[0]!=0L )
	{	//Texture vorhanden
		if( (material->GetAlphaBlendFunc()==zRND_ALPHA_FUNC_NONE )&&xd3d_ptexture[0]->HasAlpha() )	
		{	//Texture mit Alpha-Channel (d.h. konstantes Alpha wird nicht benötigt)
			if( !xd3d_alphaTest )
				return TRUE;
			if( polyDrawMode==zRND_DRAW_MATERIAL )
			{
				SetTextureStageState( 0, zRND_TSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
				SetTextureStageState( 0, zRND_TSS_TEXCOORDINDEX, 0 );
				XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL );
				XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, FALSE );
				XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
				SetTextureStageState( 0, zRND_TSS_ALPHAARG1, zRND_TA_TEXTURE );
				SetTextureStageState( 0, zRND_TSS_ALPHAARG2, zRND_TA_DIFFUSE );
				SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
				SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE );
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_SELECTARG1 );
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
				XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
				XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO );
				XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, TRUE );
			}
			if( xd3d_actStatus.texwrap )
			{
				SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_WRAP );
				SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_WRAP );
			}
			else
			{
				SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_CLAMP );
				SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_CLAMP );
			}
			if( polyDrawMode==zRND_DRAW_MATERIAL )
				xd3d_ptexture[0]->InsertTexture( xd3d_actStatus.palsupported );
			else
				SetTexture( 0, 0L );
		} 
		else 
		{	//Texture ohne Alpha-Channel, jedoch evtl. mit Blendfunktion versehen
			if( afunc!=zRND_ALPHA_FUNC_NONE )
				return TRUE;
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );
			XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, xd3d_actStatus.dither );
			XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
			SetZBufferCompare( xd3d_actStatus.zfunc );
			//Texture wird direkt benötigt, da kein AlphaPoly ...
			//Die Texture wird nur im Material_Modus dazugeholt
			if( polyDrawMode==zRND_DRAW_MATERIAL )
				xd3d_ptexture[0]->InsertTexture( xd3d_actStatus.palsupported );
			else
				SetTexture( 0, 0L );
			XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
			XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, xd3d_actStatus.zd3dfunc );
			//Setze das Texture-Wrap/Clamp-Verhalten
			if( xd3d_actStatus.texwrap )
			{	
				SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_WRAP );
				SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_WRAP );
			}
			else
			{	
				SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_CLAMP );
				SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_CLAMP );
			}
		}
	}
	else
	{
		SetTexture( 0, 0L );
		XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
		XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );
		XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, xd3d_actStatus.dither );
		XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
		SetZBufferCompare( xd3d_actStatus.zfunc );
	}

	return TRUE ;
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: BeginFrame()

 

    14-Aug-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					Aufruf von ResetStatistics();
--------------------------------------------------------------------------*/
void zCRnd_D3D :: BeginFrame() 
{
	++xd3d_actFrameNumber;
	xd3d_numTexturesUsedThisFrame = 0;
	xd3d_numLightmapsUsedThisFrame = 0;

	this->ResetStatistics();

	for( int t = 0; t<MAXBUCKETS; t++ ) 
		xd3d_alphaSortBucket[t] = NULL; 
	if (!zCCamera::activeCam) 
		xd3d_zMAX_from_Engine = 65535;
	else 
		xd3d_zMAX_from_Engine = zCCamera::activeCam->GetFarClipZ();
	if( xd3d_zMAX_from_Engine<500.0f )
		xd3d_zMAX_from_Engine = 500.0f;
	xd3d_bucketSize = MAXBUCKETS/xd3d_zMAX_from_Engine;
	//Hier erfolgt die Berechnung der Parameter A und B für die Umwandlung der eye_z in
	//Z-Buffer-verträgliche Werte:
	// z = A + B/eye_z
	if( !scalingSetByMatrix )
	{
		if( xd3d_zMIN_from_Engine>=xd3d_zMAX_from_Engine )
		{
			zERR_WARNING( "X: BeginFrame: xd3d_zMIN>=xd3d_zMAX " );
		}
		xd3d_scale_A = xd3d_zMAX_from_Engine/(xd3d_zMAX_from_Engine-xd3d_zMIN_from_Engine);
		xd3d_scale_B = -xd3d_zMAX_from_Engine*xd3d_zMIN_from_Engine/(xd3d_zMAX_from_Engine-xd3d_zMIN_from_Engine);
	}
	vidSetFrameReady();
	if( xd3d_actStatus.fog )
		SetFog( xd3d_actStatus.fog );
	SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
	SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
	SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_CURRENT );
	SetTextureStageState( 1, zRND_TSS_COLOROP, zRND_TOP_DISABLE );

	// wichtig: zbias werte beim ersten rendern wieder auf normalwerte reseten
	// level polys werden auf zbias 7 gesetzt damit vobs auch einen negativen bias spielraum bekommen können
	SetZBias		(DEFAULT_LEVEL_ZBIAS);			
}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: EndFrame()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/

void zCRnd_D3D :: EndFrame() 
{
	//DIES FUNKTIONIERT NUR IN DER DX7SDK-DEBUG-VERSION !!

	//	This method is intended to be used for performance tracking and debugging during product development 
	//	(on the debug version of DirectX). The method can succeed, returning S_FALSE, without retrieving device data. 
	//	This occurs when the retail version of the DirectX runtime is installed on the host system.
	//
	//	Ausgabe einiger Statistiken zur Textureanzahl und SetTexture-Switches pro Frame: 

	if (zCWorld::GetShowTextureStats())
	{
		if (!screen) return;

		D3DDEVINFO_TEXTUREMANAGER DevInfoStruct;
		D3DDEVINFO_TEXTURING	  DevInfoStruct2;

		xd3d_pd3dDevice7->GetInfo( D3DDEVINFOID_TEXTUREMANAGER, &DevInfoStruct, sizeof( D3DDEVINFO_TEXTUREMANAGER ) );
		xd3d_pd3dDevice7->GetInfo( D3DDEVINFOID_TEXTURING,	    &DevInfoStruct2,sizeof( D3DDEVINFO_TEXTURING)		);

		screen->Print (0, 1500,"bThrashing			: "	+zSTRING(DevInfoStruct.bThrashing));
		screen->Print (0, 1700,"total agp u/l  (kb)	: "	+zSTRING(DevInfoStruct.dwApproxBytesDownloaded/1024 ));
		screen->Print (0, 1900,"numEvicts			: "	+zSTRING(DevInfoStruct.dwNumEvicts) );
		screen->Print (0, 2100,"numVidCreates		: "	+zSTRING(DevInfoStruct.dwNumEvicts) );
		screen->Print (0, 2300,"numTexturesUsed		: "	+zSTRING(DevInfoStruct.dwNumTexturesUsed) );
		screen->Print (0, 2500,"numTexturesUsedInVid: "	+zSTRING(DevInfoStruct.dwNumUsedTexInVid) );
		screen->Print (0, 2700,"numTexturesInVid	: "	+zSTRING(DevInfoStruct.dwWorkingSet) );
		screen->Print (0, 2900,"totalInVid	   (kb)	: "	+zSTRING(DevInfoStruct.dwWorkingSet/1024) );
		screen->Print (0, 3100,"numManagedTotal		: "	+zSTRING(DevInfoStruct.dwTotalManaged ) );
		screen->Print (0, 3300,"managedTotal   (kb)	: "	+zSTRING(DevInfoStruct.dwTotalBytes/1024) );

		screen->Print (0, 3600,"dwNumLoads			: "	+zSTRING(DevInfoStruct2.dwNumLoads ) );
		screen->Print (0, 3800,"kb loaded via Load(): "	+zSTRING(DevInfoStruct2.dwApproxBytesLoaded/1024 ) );
		screen->Print (0, 4000,"dwNumCreates		: "	+zSTRING(DevInfoStruct2.dwNumCreates ) );
		screen->Print (0, 4200,"dwNumDestroys		: "	+zSTRING(DevInfoStruct2.dwNumDestroys) );
		screen->Print (0, 4400,"dwNumGetDCs			: "	+zSTRING(DevInfoStruct2.dwNumGetDCs) );
		screen->Print (0, 4600,"dwNumLoads			: "	+zSTRING(DevInfoStruct2.dwNumLoads) );
		screen->Print (0, 4800,"dwNumLocks			: "	+zSTRING(DevInfoStruct2.dwNumLocks) );
		screen->Print (0, 5000,"dwNumPreLoads		: "	+zSTRING(DevInfoStruct2.dwNumPreLoads) );
		screen->Print (0, 5200,"dwNumSet			: "	+zSTRING(DevInfoStruct2.dwNumSet) );
		screen->Print (0, 5400,"dwNumSetLODs		: "	+zSTRING(DevInfoStruct2.dwNumSetLODs) );
		screen->Print (0, 5800,"dwNumSetPriorities	: "	+zSTRING(DevInfoStruct2.dwNumSetPriorities) );
		
		screen->Print (0, 6100,"num Lightmaps		: "	+zSTRING(this->xd3d_statistics.numLightmapsUsed) );
		screen->Print (0, 6300,"num Alphapolys		: "	+zSTRING(this->xd3d_statistics.numAlphaPolys) );
		screen->Print (0, 6500,"dito, batched		: "	+zSTRING(this->xd3d_statistics.numAlphaPolyBatches) );

	}

}



/*--------------------------------------------------------------------------
	
	void zCRnd_D3D :: XD3D_ResetMultiTexturing()

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
inline void	zCRnd_D3D :: XD3D_ResetMultiTexturing()
{
	SetTextureStageState( 1, zRND_TSS_COLOROP, zRND_TOP_DISABLE );
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SetTransform( zTRnd_TrafoType transformType, const zMAT4& matrix )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/

zBOOL zCRnd_D3D :: SetTransform( zTRnd_TrafoType transformType, const zMAT4& matrix ) 
{ 

#ifdef _DEBUG

	// [BENDLIN] 2002-10-24
	// The Never Ending Story (or how-to-get-crazy-by-flickering-trees)
	{
		int i, j;
		unsigned int bits;

		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				bits = (*(unsigned int*)&(matrix[i][j]));
				if ((bits & 0x7F800000 == 0) &&	// exponent == 0
					(bits & 0x007FFFFF != 0))	// fraction != 0
				{
					bool brkDenormalFloat = true;
					//matrix[i][j] = 0.0f;
				}
			}
	}

#endif
	
	zBOOL ret=TRUE;

	switch( transformType )
	{
		case	zRND_TRAFO_VIEW:

				/*if (!matrix.IsUpper3x3Orthonormal())
				{
					zMAT4 newMatrix = matrix;
					newMatrix.MakeOrthonormal();
					if( !DXTryWarning( xd3d_pd3dDevice7->SetTransform( D3DTRANSFORMSTATE_WORLD, (D3DMATRIX *)(&newMatrix) ), 
							"X: [RND3D]SetTransform: Set world trafo matrix failed!" ) )
						ret = FALSE;
				}
				else */if( !DXTryWarning( xd3d_pd3dDevice7->SetTransform( D3DTRANSFORMSTATE_WORLD, (D3DMATRIX *)(&matrix) ), 
						"X: [RND3D]SetTransform: Set world trafo matrix failed!" ) )
						ret = FALSE;
				
#ifdef _DEBUG

				// [BENDLIN] 2002-10-24
				// The Never Ending Story (or how-to-get-crazy-by-flickering-trees)
				// Paranoid: check the device's trafo
				{
					int i, j;
					unsigned int bits;
					zMAT4 matrixDevice;

					xd3d_pd3dDevice7->GetTransform(D3DTRANSFORMSTATE_WORLD, (D3DMATRIX *)&matrixDevice);

					
					for (i = 0; i < 4; i++)
						for (j = 0; j < 4; j++)
						{
							bits = (*(unsigned int*)&(matrixDevice[i][j]));
							if ((bits & 0x7F800000 == 0) &&	// exponent == 0
								(bits & 0x007FFFFF != 0))	// fraction != 0
							{
								bool brkDenormalFloat = true;
								// matrix[i][j] = 0.0f;
							}
						}
				}

#endif

				break;
		case	zRND_TRAFO_PROJECTION:
				if( matrix[3][3]!=0.0f )
					zERR_WARNING( "X: SetTransform: matrix[3][3]!=0.0f !!!" );
				if( !DXTryWarning( xd3d_pd3dDevice7->SetTransform( D3DTRANSFORMSTATE_PROJECTION, (D3DMATRIX *)(&matrix) ), 
						"X: [RND3D]SetTransform: Set projection matrix failed!" ) )	
					ret = FALSE;
				xd3d_scale_A = matrix[2][2];
				xd3d_scale_B = matrix[3][2];
				xd3d_scale_C = matrix[2][3];
				scalingSetByMatrix = TRUE;
				break;
		case	zRND_TRAFO_TEXTURE0:
				if( !DXTryWarning( xd3d_pd3dDevice7->SetTransform( D3DTRANSFORMSTATE_TEXTURE0, (D3DMATRIX *)(&matrix) ), 
						"X: [RND3D]SetTransform: Set world trafo matrix failed!" ) )
					ret = FALSE;
				break;
		case	zRND_TRAFO_TEXTURE1:
				if( !DXTryWarning( xd3d_pd3dDevice7->SetTransform( D3DTRANSFORMSTATE_TEXTURE1, (D3DMATRIX *)(&matrix) ), 
						"X: [RND3D]SetTransform: Set texture stage 1 trafo matrix failed!" ) )
					ret = FALSE;
				break;
		case	zRND_TRAFO_TEXTURE2:
				if( !DXTryWarning( xd3d_pd3dDevice7->SetTransform( D3DTRANSFORMSTATE_TEXTURE2, (D3DMATRIX *)(&matrix) ), 
						"X: [RND3D]SetTransform: Set texture stage 2 trafo matrix failed!" ) )
					ret = FALSE;
				break;
		case	zRND_TRAFO_TEXTURE3:
				if( !DXTryWarning( xd3d_pd3dDevice7->SetTransform( D3DTRANSFORMSTATE_TEXTURE3, (D3DMATRIX *)(&matrix) ), 
						"X: [RND3D]SetTransform: Set texture stage 3 trafo matrix failed!" ) )
					ret = FALSE;
				break;
	}

	/*if (!ret) 
	{
		int brk = 0;
	};*/



	return ret;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SetViewport( int x0, int y0, int xdim, int ydim )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SetViewport( int x0, int y0, int xdim, int ydim ) 
{ 
	// initialize view port
	if( (xdim<=0)||(ydim<=0) )
		return FALSE;
    D3DVIEWPORT7 vp;
    vp.dwX		= x0;
    vp.dwY		= y0;
    vp.dwWidth  = xdim;
    vp.dwHeight = ydim;
    vp.dvMinZ	= 0.0f;
    vp.dvMaxZ	= 1.0f;

	if( !DXTryWarning( xd3d_pd3dDevice7->SetViewport( &vp ), "X: [RND3D]SetViewport: Set viewport failed!" ) )	
	{
		// [EDENFELD]: Addon: Safety Warning Messages. Sonst weiss man nicht welcher Param dafür verantwortlich war
		// bestes Beispiel: jemand gibt als zres Batchkommando einen Zahlendreher ein (1024x786, statt 1024x768), dann 
		// passieren die wildesten Dinge (Portalfehler, Himmel wird schwarz dargestellt, etc...)
		zERR_WARNING("C: d3dviewport values: dwX: "  + zSTRING(vp.dwX) + ", dwY: " + zSTRING(vp.dwY) + ", dwWidth: " + zSTRING(vp.dwWidth) + ", dwHeight: " + zSTRING(vp.dwHeight) + ", dvMinZ: " + zSTRING(vp.dvMinZ) + ", dvMaxZ: " + zSTRING(vp.dvMaxZ));
		return FALSE;
	}

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SetLight( zDWORD lightIndex, zCRenderLight *light )


    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/

static void DumpLightInfo(int index, const D3DLIGHT7& light)
{
	zERR_WARNING ("X: LightIndex: "+zSTRING(index));
	zERR_WARNING ("X: dltType: "+zSTRING((int)light.dltType));
//	zERR_WARNING ("X: dcvDiffuse: "+zSTRING((int)light.dcvDiffuse)));
//	zERR_WARNING ("X: dcvSpecular: "+zSTRING((int)light.dcvSpecular));
//	zERR_WARNING ("X: dcvAmbient: "+zSTRING((int)light.dcvAmbient));
	zERR_WARNING ("X: dvRange: "+zSTRING(light.dvRange));
	zERR_WARNING ("X: dvPosition: "+ zSTRING(light.dvPosition.x,1)+","+zSTRING(light.dvPosition.y,1)+","+zSTRING(light.dvPosition.z,1));
	zERR_WARNING ("X: dvDirection: "+zSTRING(light.dvDirection.x,1)+","+zSTRING(light.dvDirection.y,1)+","+zSTRING(light.dvDirection.z,1));
//	zERR_WARNING ("X: dvFalloff: "+zSTRING(light.dvFalloff));
	zERR_WARNING ("X: dvAttenuation0: "+zSTRING(light.dvAttenuation0));
	zERR_WARNING ("X: dvAttenuation1: "+zSTRING(light.dvAttenuation1));
	zERR_WARNING ("X: dvAttenuation2: "+zSTRING(light.dvAttenuation2));
//	zERR_WARNING ("X: dvTheta: "+zSTRING(light.dvTheta));
//	zERR_WARNING ("X: dvPhi: "+zSTRING(light.dvPhi));
};

/*
    D3DLIGHTTYPE    dltType;            
    D3DCOLORVALUE   dcvDiffuse;         
    D3DCOLORVALUE   dcvSpecular;        
    D3DCOLORVALUE   dcvAmbient;         
    D3DVECTOR       dvPosition;         
    D3DVECTOR       dvDirection;        
    D3DVALUE        dvRange;            
    D3DVALUE        dvFalloff;          
    D3DVALUE        dvAttenuation0;     
    D3DVALUE        dvAttenuation1;     
    D3DVALUE        dvAttenuation2;     
    D3DVALUE        dvTheta;            
    D3DVALUE        dvPhi;              
*/


zBOOL zCRnd_D3D :: SetLight( zDWORD lightIndex, zCRenderLight *light ) 
{ 
	// setting a light enables it, 'light==0' disables that lightSlot
	static zDWORD ambientLightIndex = 0xffff;

	if( lightIndex>=this->HasCapability( zRND_CAP_TNL_MAXLIGHTS ) ) 
		return FALSE;

    if( light ) 
	{
        D3DLIGHT7 dlight;
        memset					(&dlight, 0, sizeof(dlight));
		const zVEC3 diffColor	= zVEC4( light->colorDiffuse[0], light->colorDiffuse[1], light->colorDiffuse[2], 255 );
		memcpy					(&(dlight.dcvDiffuse) , &diffColor, sizeof(dlight.dcvDiffuse));
        switch (light->lightType) 
		{
			case	zLIGHT_TYPE_POINT:
					dlight.dltType			= D3DLIGHT_POINT;
					dlight.dvRange			= light->range;
					dlight.dvAttenuation0	= 0;
					dlight.dvAttenuation1	= 0.009F;
					dlight.dvAttenuation2	= 0;
					memcpy( &(dlight.dvPosition), &light->positionLS, sizeof( dlight.dvPosition ) );
					break;
			case	zLIGHT_TYPE_SPOT:
					dlight.dltType			= D3DLIGHT_SPOT;
					dlight.dvRange			= light->range;
					dlight.dvAttenuation0	= 0;
					dlight.dvAttenuation1	= 1;
					dlight.dvAttenuation2	= 0;
					dlight.dvFalloff		= 1.0F;
					dlight.dvTheta			= 0;
					dlight.dvPhi			= Alg_Deg2Rad(40.0F);	// light->spotConeAngle;
					memcpy( &(dlight.dvPosition), &light->positionLS, sizeof( dlight.dvPosition ) );
					break;
			case	zLIGHT_TYPE_DIR:
					dlight.dltType			= D3DLIGHT_DIRECTIONAL;
					// FIXME: irgendwie kommen hier gelegentlich Lichter mit Null-Vektoren an... ?! Lieber auf einen
					// definierten Wert setzen, wer weiss, was sonst unten bei D3D damit schief laufen koennte..
					if ((light->directionLS[VX]==0) && (light->directionLS[VY]==0) && (light->directionLS[VZ]==0))
						light->directionLS	= zVEC3(1,0,0);
					memcpy( &(dlight.dvDirection), &light->directionLS, sizeof( dlight.dvDirection ) );
					break;
			case	zLIGHT_TYPE_AMBIENT:
					break;
        }
		if( light->lightType!=zLIGHT_TYPE_AMBIENT )
		{
	        if( !DXTryWarning( xd3d_pd3dDevice7->SetLight( lightIndex, &dlight ), "X: [RND3D]SetLight: Set light data failed!" ) )		
			{
				DumpLightInfo (lightIndex, dlight);
				return FALSE;
			};
		    if( !DXTryWarning( xd3d_pd3dDevice7->LightEnable( lightIndex, TRUE ), "X: [RND3D]SetLight: Light enable failed!" ) )	
			{
				DumpLightInfo (lightIndex, dlight);
				return FALSE;
			};
			// Falls bisher ein ambientes Licht auf diesem Kanal aktiv war, so muss es nun disabled werden
			if( ambientLightIndex==lightIndex )
			{
				ambientLightIndex = 0xffff;
				if( !XD3D_SetRenderState( D3DRENDERSTATE_AMBIENT, 0 ) )	
					return FALSE;
			};
		}
		else
		{
			ambientLightIndex = lightIndex;
			if( !XD3D_SetRenderState( D3DRENDERSTATE_AMBIENT, 
								 (((zFloat2IntFloor(light->colorDiffuse[0])&0x00ff)<<16) //r,g,b
								 |((zFloat2IntFloor(light->colorDiffuse[1])&0x00ff)<< 8)
								 |((zFloat2IntFloor(light->colorDiffuse[2])&0x00ff)<< 0)) ) )	
			{
				DumpLightInfo (lightIndex, dlight);
				return FALSE;
			}
			if( !DXTryWarning( xd3d_pd3dDevice7->LightEnable( lightIndex, FALSE ), "X: [RND3D]SetLight: Light disable failed!" ) )	
			{
				DumpLightInfo (lightIndex, dlight);
				return FALSE;
			};
		}
    } 
	else 
	{
		// Falls bisher ein ambientes Licht auf diesem Kanal aktiv war, so muss es nun disabled werden
		if( ambientLightIndex==lightIndex )
		{
			ambientLightIndex = 0xffff;
			if( !XD3D_SetRenderState( D3DRENDERSTATE_AMBIENT, 0 ) )	
				return FALSE;
		};
        if( !DXTryWarning( xd3d_pd3dDevice7->LightEnable( lightIndex, FALSE ), "X: [RND3D]SetLight: Light disable failed!" ) )
		{
			return FALSE;
		};
    }

    return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SetMaterial( const zTMaterial &material ) 

 

    29-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SetMaterial( const zTMaterial &material ) 
{ 
	D3DMATERIAL7 mat;
	mat.dcvDiffuse.r	= material.diffuseRGBA[0]; 
    mat.dcvDiffuse.g	= material.diffuseRGBA[1]; 
    mat.dcvDiffuse.b	= material.diffuseRGBA[2]; 
    mat.dcvDiffuse.a	= material.diffuseRGBA[3]; 
	mat.dcvAmbient.r	= material.ambientRGBA[0]; 
    mat.dcvAmbient.g	= material.ambientRGBA[1]; 
    mat.dcvAmbient.b	= material.ambientRGBA[2]; 
    mat.dcvAmbient.a	= material.ambientRGBA[3]; 

    mat.dcvSpecular.r	= 0.0f; 
    mat.dcvSpecular.g	= 0.0f; 
    mat.dcvSpecular.b	= 0.0f; 
    mat.dcvSpecular.a	= 0.0f; 

    mat.dcvEmissive.r	= 0.0f; 
    mat.dcvEmissive.g	= 0.0f; 
    mat.dcvEmissive.b	= 0.0f; 
    mat.dcvEmissive.a	= 0.0f;

    mat.dvPower = 0.0f;
	if( !DXTryWarning( xd3d_pd3dDevice7->SetMaterial(&mat), "X: [RND3D]SetMaterial: Set material failed !" ) )	
			return FALSE;
	xd3d_actmaterial.diffuseRGBA = material.diffuseRGBA;
	xd3d_actmaterial.ambientRGBA = material.ambientRGBA;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: GetMaterial( zTMaterial &material ) 

 

    29-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: GetMaterial( zTMaterial &material ) 
{ 
	material.diffuseRGBA = xd3d_actmaterial.diffuseRGBA;
	material.ambientRGBA = xd3d_actmaterial.ambientRGBA;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: XD3D_SetTexture( zDWORD stage, IDirectDrawSurface7 *texture )

 

    07-Oct-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: XD3D_SetTexture( zDWORD stage, IDirectDrawSurface7 *texture )
{
	if (this->GetPolyDrawMode()>zRND_DRAW_MATERIAL_WIRE) return TRUE;

	if( xd3d_pd3dtexture[stage]==texture )
		return TRUE;
	if( !DXTryWarning( xd3d_pd3dDevice7->SetTexture( stage, texture ), "X: [RND3D]SetTexture: Set texture failed!" ) )	
			return FALSE;
	xd3d_pd3dtexture[stage] = texture;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SetTexture( zDWORD stage, zCTexture *texture )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SetTexture( zDWORD stage, zCTexture *texture ) 
{ 
	if (this->GetPolyDrawMode()>zRND_DRAW_MATERIAL_WIRE) return TRUE;

	zCTex_D3D *tex = static_cast<zCTex_D3D*>( texture );
	if( tex )
	{
		if( tex->CacheIn()!=zRES_CACHED_IN ) 
			tex = 0;
	}
	if( !tex )
	{
		//Immer aufrufen (auch wenn xd3d_ptexture[stage] bereits gleich 0L)
		if( !XD3D_SetTexture( stage, 0 ) )	
			return FALSE;
		xd3d_ptexture[stage] = 0L;
	} 
	else 
	{
		if( !tex->SetTexture( stage ) )
			return FALSE;
		xd3d_ptexture[stage] = tex;
	}

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SetTextureStageState( zDWORD stage, zTRnd_TextureStageState state, zDWORD value )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
const static D3DTEXTURESTAGESTATETYPE s_textureStageStateArray [] =
{
	D3DTSS_COLOROP,							// zRND_TSS_COLOROP					= 1,  
	D3DTSS_COLORARG1,						// zRND_TSS_COLORARG1				,
	D3DTSS_COLORARG2,						// zRND_TSS_COLORARG2				,  
	D3DTSS_ALPHAOP,							// zRND_TSS_ALPHAOP					,  
	D3DTSS_ALPHAARG1,						// zRND_TSS_ALPHAARG1				,  
	D3DTSS_ALPHAARG2,						// zRND_TSS_ALPHAARG2				,  
	D3DTSS_BUMPENVMAT00,					// zRND_TSS_BUMPENVMAT00			,		// not currently used
	D3DTSS_BUMPENVMAT01,					// zRND_TSS_BUMPENVMAT01			,		// not currently used
	D3DTSS_BUMPENVMAT10,					// zRND_TSS_BUMPENVMAT10			,		// not currently used
	D3DTSS_BUMPENVMAT11,					// zRND_TSS_BUMPENVMAT11			,		// not currently used
	D3DTSS_TEXCOORDINDEX,					// zRND_TSS_TEXCOORDINDEX			,
	D3DTSS_ADDRESS,							// zRND_TSS_ADDRESS					,
	D3DTSS_ADDRESSU,						// zRND_TSS_ADDRESSU				,
	D3DTSS_ADDRESSV,						// zRND_TSS_ADDRESSV				,
	D3DTSS_BORDERCOLOR,						// zRND_TSS_BORDERCOLOR				,		// not currently used
	D3DTSS_MAGFILTER,						// zRND_TSS_MAGFILTER				,
	D3DTSS_MINFILTER,						// zRND_TSS_MINFILTER				,
	D3DTSS_MIPFILTER,						// zRND_TSS_MIPFILTER				,
	D3DTSS_MIPMAPLODBIAS,					// zRND_TSS_MIPMAPLODBIAS			,
	D3DTSS_MAXMIPLEVEL,						// zRND_TSS_MAXMIPLEVEL				,
	D3DTSS_MAXANISOTROPY,					// zRND_TSS_MAXANISOTROPY			,		// not currently used
	D3DTSS_BUMPENVLSCALE,					// zRND_TSS_BUMPENVLSCALE			,		// not currently used
	D3DTSS_BUMPENVLOFFSET,					// zRND_TSS_BUMPENVLOFFSET			,		// not currently used
	D3DTSS_TEXTURETRANSFORMFLAGS 			// zRND_TSS_TEXTURETRANSFORMFLAGS			// not currently used
};

const static D3DTEXTUREOP s_textureStageOpArray [] =
{
	D3DTOP_DISABLE,							// zRND_TOP_DISABLE
	D3DTOP_SELECTARG1,						// zRND_TOP_SELECTARG1
	D3DTOP_SELECTARG2,						// zRND_TOP_SELECTARG2
	D3DTOP_MODULATE,						// zRND_TOP_MODULATE
	D3DTOP_MODULATE2X,						// zRND_TOP_MODULATE2X
	D3DTOP_MODULATE4X,						// zRND_TOP_MODULATE4X
	D3DTOP_ADD,								// zRND_TOP_ADD
	D3DTOP_ADDSIGNED,						// zRND_TOP_ADDSIGNED
	D3DTOP_ADDSIGNED2X,						// zRND_TOP_ADDSIGNED2X
	D3DTOP_SUBTRACT,						// zRND_TOP_SUBTRACT
	D3DTOP_ADDSMOOTH,						// zRND_TOP_ADDSMOOTH
	D3DTOP_BLENDDIFFUSEALPHA,				// zRND_TOP_BLENDDIFFUSEALPHA
	D3DTOP_BLENDTEXTUREALPHA,				// zRND_TOP_BLENDTEXTUREALPHA
	D3DTOP_BLENDFACTORALPHA,				// zRND_TOP_BLENDFACTORALPHA
	D3DTOP_BLENDTEXTUREALPHAPM,				// zRND_TOP_BLENDTEXTUREALPHAPM
	D3DTOP_BLENDCURRENTALPHA,				// zRND_TOP_BLENDCURRENTALPHA
	D3DTOP_PREMODULATE,						// zRND_TOP_PREMODULATE
	D3DTOP_MODULATEALPHA_ADDCOLOR,			// zRND_TOP_MODULATEALPHA_ADDCOLOR
	D3DTOP_MODULATECOLOR_ADDALPHA,			// zRND_TOP_MODULATECOLOR_ADDALPHA
	D3DTOP_MODULATEINVALPHA_ADDCOLOR,		// zRND_TOP_MODULATEINVALPHA_ADDCOL
	D3DTOP_MODULATEINVCOLOR_ADDALPHA,		// zRND_TOP_MODULATEINVCOLOR_ADDALP
	D3DTOP_BUMPENVMAP,						// zRND_TOP_BUMPENVMAP
	D3DTOP_BUMPENVMAPLUMINANCE,				// zRND_TOP_BUMPENVMAPLUMINANCE
	D3DTOP_DOTPRODUCT3          			// zRND_TOP_DOTPRODUCT3
};

const static int s_textureStageTAArray [] =
{
	D3DTA_CURRENT,							// zRND_TA_CURRENT
	D3DTA_DIFFUSE,							// zRND_TA_DIFFUSE
	D3DTA_SELECTMASK,						// zRND_TA_SELECTMASK
	D3DTA_TEXTURE,							// zRND_TA_TEXTURE
	D3DTA_TFACTOR,							// zRND_TA_TFACTOR
	D3DTA_SPECULAR							// zRND_TA_SPECULAR
};

const static int s_textureStageTexCoordArray [] =
{
	D3DTSS_TCI_PASSTHRU,					// zRND_TSS_TCI_PASSTHRU
	D3DTSS_TCI_CAMERASPACENORMAL,			// zRND_TSS_TCI_CAMERASPACENORMAL
	D3DTSS_TCI_CAMERASPACEPOSITION,			// zRND_TSS_TCI_CAMERASPACEPOSITION
	D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR	// zRND_TSS_TCI_CAMERASPACEREFLECTIONVECTOR
};

const static int s_textureStageTexTransformFlagsArray [] =
{
	D3DTTFF_DISABLE,  						// zRND_TTF_DISABLE
    D3DTTFF_COUNT1, 						// zRND_TTF_COUNT1  
    D3DTTFF_COUNT2,  						// zRND_TTF_COUNT2 
    D3DTTFF_COUNT3,  						// zRND_TTF_COUNT3 
    D3DTTFF_COUNT4,   						// zRND_TTF_COUNT4
    D3DTTFF_PROJECTED						// zRND_TTF_PROJECTED
};


zBOOL zCRnd_D3D :: SetTextureStageState( zDWORD stage, zTRnd_TextureStageState state, zDWORD value )
{
	if( xd3d_actTexStageState[stage][state]==value )
		return TRUE;
	zDWORD						valueD3D = value;
	D3DTEXTURESTAGESTATETYPE	stateD3D = s_textureStageStateArray[state];
	switch( stateD3D )
	{
	case	D3DTSS_COLOROP:
	case	D3DTSS_ALPHAOP:
			valueD3D = s_textureStageOpArray[value];
			break;
	case	D3DTSS_COLORARG1:
	case	D3DTSS_COLORARG2:
	case	D3DTSS_ALPHAARG1:
	case	D3DTSS_ALPHAARG2:
			valueD3D = s_textureStageTAArray[value];
			break;
	case	D3DTSS_TEXCOORDINDEX:
//			valueD3D = s_textureStageTexCoordArray[value];
			break;
	case	D3DTSS_TEXTURETRANSFORMFLAGS:
//			valueD3D = s_textureStageTexTransformFlagsArray[value];
			break;
	}
	if( !DXTryWarning( xd3d_pd3dDevice7->SetTextureStageState( stage, stateD3D, valueD3D ), "X: [RND3D]SetTextureStageState: Set texture stage state failed!" ) )	
		return FALSE;
	xd3d_actTexStageState[stage][state] = value;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SetAlphaBlendFuncImmed( const zTRnd_AlphaBlendFunc afunc )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SetAlphaBlendFuncImmed( const zTRnd_AlphaBlendFunc afunc )
{
	zBOOL alphaTest = FALSE;
	zBOOL alphaNone = FALSE;
	switch( afunc )
	{
	case	zRND_ALPHA_FUNC_TEST:	
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
			XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
			XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO );
			alphaTest = TRUE;
			break;
	case	zRND_ALPHA_FUNC_BLEND:
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
			XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
			XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );

			break;
	case	zRND_ALPHA_FUNC_BLEND_TEST:
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
			XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
			XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
			alphaTest = TRUE;
			break;
	case	zRND_ALPHA_FUNC_ADD:
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
			XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
			XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
			break;
	case	zRND_ALPHA_FUNC_MUL:
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
			XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR );
			XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO );
			break;
	case	zRND_ALPHA_FUNC_MUL2:
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
			XD3D_SetRenderState( D3DRENDERSTATE_SRCBLEND, D3DBLEND_DESTCOLOR );
			XD3D_SetRenderState( D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCCOLOR );
			break;
	case	zRND_ALPHA_FUNC_NONE:
	default:
			XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
			alphaNone = TRUE;
	}
	if( alphaTest )
	{
		XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, FALSE );
		XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
		XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, TRUE );
		XD3D_SetRenderState( D3DRENDERSTATE_ALPHAREF, alphaReference );
	}
	else
	{
		XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );
		if( alphaNone )
		{
			XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, xd3d_actStatus.dither );
			XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
		}
		else
		{
			XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, FALSE );
			XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
		}
		SetZBufferCompare( xd3d_actStatus.zfunc );
	}

	return TRUE;
}	



/*--------------------------------------------------------------------------

	zBOOL zCRnd_D3D :: SetRenderState( zTRnd_RenderStateType renderStateType, zDWORD renderState )

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SetRenderState( zTRnd_RenderStateType renderStateType, zDWORD renderState )
{
	switch( renderStateType )
	{
	case	zRND_RENDERSTATE_CLIPPING:
			xd3d_vbclipping = (zBOOL)renderState;
			break;
	case	zRND_RENDERSTATE_TEXTUREFACTOR:
			XD3D_SetRenderState( D3DRENDERSTATE_TEXTUREFACTOR, renderState ); 
			xd3d_texturefactor = renderState;
			break;
	default:
			return FALSE;
	}

	return TRUE;
}	






/*--------------------------------------------------------------------------

	zDWORD zCRnd_D3D :: GetRenderState( zTRnd_RenderStateType renderStateType )

 

    22-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zDWORD zCRnd_D3D :: GetRenderState( zTRnd_RenderStateType renderStateType )
{
	switch( renderStateType )
	{
	case	zRND_RENDERSTATE_CLIPPING:
			return (zDWORD)xd3d_vbclipping;
	case	zRND_RENDERSTATE_TEXTUREFACTOR:
			return xd3d_texturefactor;
	}

	return 0;
}



/*--------------------------------------------------------------------------

	void zCRnd_D3D :: AddAlphaSortObject( zCRndAlphaSortObject *alphaSortObject )

 

    05-Oct-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: AddAlphaSortObject( zCRndAlphaSortObject *alphaSortObject )
{
	float zvalue = alphaSortObject->GetZValue();
	if( zvalue==0.0f )
		return;

	int index = zFloat2IntFloor( xd3d_bucketSize*zvalue );
	if( index>=MAXBUCKETS )
		index = MAXBUCKETS-1;
	if( index<0 )
		index = 0;
	//Falls Bucket noch leer ...
	if( xd3d_alphaSortBucket[index]==NULL )
	{
		alphaSortObject->SetNext( NULL );
		xd3d_alphaSortBucket[index] = alphaSortObject;
		return;
	}
	//Falls erster Bucket-Eintrag bereits zu klein ...
	if( xd3d_alphaSortBucket[index]->GetZValue()<=zvalue )
	{
		alphaSortObject->SetNext( xd3d_alphaSortBucket[index] );
		xd3d_alphaSortBucket[index] = alphaSortObject;
		return;
	}
	//Ansonsten durchlaufe die Bucket-Einträge bis zur richtigen Position ...
	zCRndAlphaSortObject *entry		= xd3d_alphaSortBucket[index];
	zCRndAlphaSortObject *nextentry	= entry->GetNext();
	while( 1 )
	{
		if( nextentry==NULL )
			break;
		if( nextentry->GetZValue()<=zvalue )
			break;
		entry		= nextentry;
		nextentry	= entry->GetNext();
	}
	// ... und füge das neue Element in die verkettete Liste ein
	entry->SetNext( alphaSortObject );
	alphaSortObject->SetNext( nextentry );
}



/*--------------------------------------------------------------------------

	void zCRnd_D3D :: RenderAlphaSortList()

 

    05-Oct-00       [PELZER]

--------------------------------------------------------------------------*/
void zCRnd_D3D :: RenderAlphaSortList()
{
	global_PolyDrawMode = polyDrawMode;
	SetTexture( 0, 0L );

	int index = 0;
	zCRndAlphaSortObject *alphaObject;
    for( int i = MAXBUCKETS-1; i>=0; i-- )
	{
		while( xd3d_alphaSortBucket[i]!=NULL )
		{
			alphaObject = xd3d_alphaSortBucket[i];
			alphaObject->Draw( index );
			xd3d_alphaSortBucket[i] = alphaObject->GetNext(); 
			index++;
		}
	}
	xd3d_numAlphaPolys = 0;


	//Restauriere den alten Status für die Darstellung von Non-Alpha-Polys
	XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, xd3d_actStatus.zwrite );
	switch( xd3d_actStatus.zfunc )
	{
	case	zRND_ZBUFFER_CMP_LESS:
			xd3d_actStatus.zd3dfunc = D3DCMP_LESS;
			break;
	case	zRND_ZBUFFER_CMP_LESS_EQUAL:
			xd3d_actStatus.zd3dfunc = D3DCMP_LESSEQUAL;
			break;
	case	zRND_ZBUFFER_CMP_ALWAYS:
			xd3d_actStatus.zd3dfunc = D3DCMP_ALWAYS;
			break;
	case	zRND_ZBUFFER_CMP_NEVER:
			xd3d_actStatus.zd3dfunc = D3DCMP_NEVER;
			break;
	default:
			zERR_WARNING( "X: FlushPolys: Not supported z function !" );
	}
	XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, xd3d_actStatus.zd3dfunc );
	XD3D_SetRenderState( D3DRENDERSTATE_DITHERENABLE, xd3d_actStatus.dither );
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
	SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
	SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_CURRENT );
	if( xd3d_actStatus.texwrap )
	{
		SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_WRAP );
		SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_WRAP );
	}
	else
	{
		SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_CLAMP );
		SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_CLAMP );
	}
	
	XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );

	SetTexture( 0, 0L );
	xd3d_pactivematerial = NULL;
}



/*--------------------------------------------------------------------------

	void zCRnd_D3D ::zD3D_alphaPoly ::Draw()

 

    05-Oct-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					FIXME/Performance Kommentar hinzugefuegt..
					AlphaPolyBatches werden gezaehlt (Renderer-Statistics).
					Fog disabled bei additiv geblendeten Polys.
    25-Jan-01       [HILDEBRANDT]
					Fog bei MUL-AlphaBlend Polys ausgeschaltet.
					Das Packen der Verts aus dem zD3D_alphaPoly in den VB wesentlich optimiert (memcpy).
					zD3D_alphaPoly: unnoetige Member entfernt => sparte ca. 1.5MB Speicher ein!
--------------------------------------------------------------------------*/

void zD3D_alphaPoly :: Draw( int currentIndex )
{
	zCRnd_D3D *d3drenderer = (zCRnd_D3D*)zrenderer;
	d3drenderer->XD3D_ResetMultiTexturing();
	d3drenderer->XD3D_SetRenderState( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );
	d3drenderer->SetTextureStageState( 0, zRND_TSS_ALPHAARG1, zRND_TA_TEXTURE );
	d3drenderer->SetTextureStageState( 0, zRND_TSS_ALPHAARG2, zRND_TA_DIFFUSE );
	d3drenderer->SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TEXTURE );
	d3drenderer->SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE );
	d3drenderer->SetTextureStageState( 0, zRND_TSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
	d3drenderer->SetTextureStageState( 0, zRND_TSS_TEXCOORDINDEX, 0 );
	d3drenderer->XD3D_SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE );

	//Bearbeite das aktuell vorliegende Poly
	switch( zfunc )
	{
	case	zRND_ZBUFFER_CMP_LESS:
			d3drenderer->XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_LESS );
			break;
	case	zRND_ZBUFFER_CMP_LESS_EQUAL:
			d3drenderer->XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL );
			break;
	case	zRND_ZBUFFER_CMP_ALWAYS:
			d3drenderer->XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );
			break;
	case	zRND_ZBUFFER_CMP_NEVER:
			d3drenderer->XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_NEVER );
			break;
	default:
			zERR_WARNING( "X: FlushPolys: Not supported z function !" );
	}

	d3drenderer->SetZBias(this->zBias);

	//
	const zBOOL fogEnabledBackup = d3drenderer->GetFog();

	const zBOOL radial			 = d3drenderer->xd3d_enableRadialFog && fogEnabledBackup;
	if (radial)	
	{	
		// auf table fog umschalten: FIXME: eventuell nur nötig, wenn auch wirklich unten das DrawVertexBuffer ausgeführt wird
		d3drenderer->SetFog(FALSE);
		d3drenderer->xd3d_enableRadialFog = FALSE;
		d3drenderer->SetFog(TRUE);
	}

	//
	if( tex ) //Verwende die Texture, falls vorhanden ...
	{
		if( wrap )
		{
			d3drenderer->SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_WRAP );
			d3drenderer->SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_WRAP );
		}
		else
		{
			d3drenderer->SetTextureStageState( 0, zRND_TSS_ADDRESSU, D3DTADDRESS_CLAMP );
			d3drenderer->SetTextureStageState( 0, zRND_TSS_ADDRESSV, D3DTADDRESS_CLAMP );
		}
		if( global_PolyDrawMode==zRND_DRAW_MATERIAL )
			tex->InsertTexture( FALSE );
		else
			d3drenderer->SetTexture( 0, 0L );
		switch( alphafunc )
		{
		case	zRND_ALPHA_FUNC_ADD: 
				if( !tex->HasAlpha() ) //Z.B. Lichtpfeil, Lensflares
					d3drenderer->SetTextureStageState	( 0, zRND_TSS_ALPHAOP, zRND_TOP_SELECTARG2 );
				else
					d3drenderer->SetTextureStageState	( 0, zRND_TSS_ALPHAOP, zRND_TOP_MODULATE );
				d3drenderer->SetTextureStageState		( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
				d3drenderer->SetAlphaBlendFuncImmed		( zRND_ALPHA_FUNC_ADD );
				d3drenderer->SetFog						( FALSE );
				break;
		case	zRND_ALPHA_FUNC_MUL: //Schatten
				d3drenderer->SetTextureStageState		( 0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG1 );
				d3drenderer->SetFog						( FALSE );
				d3drenderer->SetAlphaBlendFuncImmed		( zRND_ALPHA_FUNC_MUL );
				break;
		case	zRND_ALPHA_FUNC_MUL2:
				d3drenderer->SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG1 );
				d3drenderer->SetAlphaBlendFuncImmed( zRND_ALPHA_FUNC_MUL2 );
				break;
		case	zRND_ALPHA_FUNC_SUB: //Wird nicht unterstützt
				zERR_WARNING( "X: FlushPolys: Alpha function zRND_ALPHA_FUNC_SUB is not supported" );
		case	zRND_ALPHA_FUNC_BLEND: 
		default:
				if( !tex->HasAlpha() ) //Z.B. Wasser
					d3drenderer->SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_SELECTARG2 );
				else
					d3drenderer->SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_MODULATE );
				d3drenderer->SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
			
				d3drenderer->SetAlphaBlendFuncImmed( zRND_ALPHA_FUNC_BLEND );

				break;
		}
	} 
	else //Falls keine Texture vorhanden, so greife auf die Diffuse-Werte zurück ...
	{
		d3drenderer->SetTextureStageState( 0, zRND_TSS_ALPHAOP, zRND_TOP_SELECTARG2 );
		d3drenderer->SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG2 );
		switch( alphafunc )
		{
		case	zRND_ALPHA_FUNC_ADD:
				d3drenderer->SetAlphaBlendFuncImmed	( zRND_ALPHA_FUNC_ADD );
				d3drenderer->SetFog					( FALSE );
				break;
		case	zRND_ALPHA_FUNC_MUL:
				d3drenderer->SetAlphaBlendFuncImmed	( zRND_ALPHA_FUNC_MUL );
				break;
		case	zRND_ALPHA_FUNC_MUL2:
				d3drenderer->SetAlphaBlendFuncImmed	( zRND_ALPHA_FUNC_MUL2 );
				break;
		case	zRND_ALPHA_FUNC_SUB:
				zERR_WARNING( "X: FlushPolys: Alpha function zRND_ALPHA_FUNC_SUB is not supported" );
		case	zRND_ALPHA_FUNC_BLEND: //Z.B. Fensterausblendungen
		default:
				d3drenderer->SetAlphaBlendFuncImmed( zRND_ALPHA_FUNC_BLEND );
				break;
		}
	}

	//
	if( global_PolyDrawMode!=zRND_DRAW_WIRE ) //Filled-Modus
	{
		zCRndAlphaSortObject *nextalpha = GetNext();

// FIXME:
// kann es sein, dass mit dieser Methode nur AlphaPolys mit gleicher Textur in einem VB-Batch zusammengefasst werden,
// wenn sie sich im selben Sort-Bucket befinden?? ("GetNext()") => unnoetig kleine Batches?

		//Falls der dyn. Vertexbuffer noch nicht gelockt, so bereite ein Schreibfenster der benötigten Grösse vor
		if( !locked )
		{
			numberofvertices				= (numVert-2)*3;
			zCRndAlphaSortObject *nextentry = nextalpha;
			while( !((nextentry==NULL)||(!nextentry->IsAlphaPoly())||(((zD3D_alphaPoly*)nextentry)->tex!=tex)) )
			{
				numberofvertices += (((zD3D_alphaPoly*)nextentry)->numVert-2)*3;
				if( numberofvertices<=ALPHAVERTEXBUFFERSIZE )
					nextentry = nextentry->GetNext();
				else
				{
					numberofvertices	-= (((zD3D_alphaPoly*)nextentry)->numVert-2)*3;
					nextentry			= NULL;
				}
			}
			if( !vertexbufferdyn->Lock( numberofvertices, startvertex ) )
			{
				zERR_WARNING ( "X: zD3D_alphaPoly::Draw() - vertex buffer lock failed." );
				startvertex			= 0;
				actvertex			= 0;
				numberofvertices	= 0;
				actnov				= 0;
				return;
			}
			actvertex	= startvertex;
			locked		= TRUE;
		}

		//Fülle Vertexbuffer
		if( actnov<numberofvertices )
		{
			zERR_ASSERT		(vertexbufferdyn->GetVertexSizeBytes()==sizeof(zD3D_alphaPoly::zD3D_vertexFormat));
			zERR_CASSERT	(sizeof(zD3D_alphaPoly::zD3D_vertexFormat)==28);

			// emergency, lock failure/surface loss	
			if (vertexbufferdyn->GetVertexBuffer()->array.basePtr==0) return;

			// Die ersten 3 Verts per memcpy kopieren
			zD3D_vertexFormat*	destPtr	=	(zD3D_vertexFormat*) (((zBYTE*)(vertexbufferdyn->GetVertexBuffer()->array.basePtr)) +
											(actvertex*int(vertexbufferdyn->GetVertexBuffer()->arrayStride)));
			memcpy			(destPtr, &this->vertexList[0], sizeof(zD3D_alphaPoly::zD3D_vertexFormat)*3);
			actvertex		+= 3;
			actnov			+= 3;
			destPtr			+= 3;

			if (numberofvertices>3)
			{
				// Die reslichen Verts kopieren (triangulieren)
				for( int t = 3; t<numVert; t++ )
				{
					memcpy			(destPtr, &this->vertexList[0]	, sizeof(zD3D_alphaPoly::zD3D_vertexFormat));
					++destPtr;
					memcpy			(destPtr, &this->vertexList[t-1], sizeof(zD3D_alphaPoly::zD3D_vertexFormat));
					++destPtr;
					memcpy			(destPtr, &this->vertexList[t]	, sizeof(zD3D_alphaPoly::zD3D_vertexFormat));
					++destPtr;
					actvertex		+= 3;
					actnov			+= 3;
				};

			}; 
		}
		//Unlock des Schreibfensters und Draw des Vertexbuffers falls keine weiteren passenden Alphapolys mehr vorhanden
		if( (nextalpha==NULL)||(!nextalpha->IsAlphaPoly())||(((zD3D_alphaPoly*)nextalpha)->tex!=tex)||(actnov>=numberofvertices) )
		{
			vertexbufferdyn->Unlock			();
			locked							= FALSE;
			d3drenderer->DrawVertexBuffer	( vertexbuffer, startvertex, numberofvertices, NULL, 0 );
			startvertex						= 0;
			actvertex						= 0;
			numberofvertices				= 0;
			actnov							= 0;
			d3drenderer->xd3d_statistics.numAlphaPolyBatches++;
		}
	}
	else //Wire-Modus
	{	
		int q = 0;
		for( int t = 0; t<numVert; t++ )
		{	
			pri[q++]					= t;
			this->vertexList[t].a_color	= 0xFFFFFFFF;
		} 
		pri[q++] = 0;
		d3drenderer->SetTexture( 0, 0L );

		enum { VERTEX_FORMAT = 	D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 };

		d3drenderer->xd3d_pd3dDevice7->DrawIndexedPrimitive(	D3DPT_LINESTRIP, 
																VERTEX_FORMAT, 
																(LPVOID) this->vertexList,
																numVert, 
																(LPWORD) pri, 
																q, 
																0 );
	}

	if (radial)
	{
		// auf vertex fog zurückschalten
		d3drenderer->SetFog(FALSE);
		d3drenderer->xd3d_enableRadialFog = TRUE;
		d3drenderer->SetFog(TRUE);
	}
	// Fogging zuruecksetzen
	d3drenderer->SetFog					 ( fogEnabledBackup );
	//if (d3drenderer->xd3d_enableRadialFog)	d3drenderer->SetFogType			 ( fogType );
}



/*--------------------------------------------------------------------------

	zBOOL zCRnd_D3D :: XD3D_DrawVertexBufferWire( zCVertexBuffer *vertexBuffer, const int firstVert, const int numVert, zWORD *indexList, const zDWORD numIndex )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/

static const D3DPRIMITIVETYPE s_primitiveArray[] =
{   
	D3DPT_TRIANGLELIST			,	// zVBUFFER_PT_TRIANGLELIST
	D3DPT_TRIANGLESTRIP			,	// zVBUFFER_PT_TRIANGLESTRIP
	D3DPT_TRIANGLEFAN			,	// zVBUFFER_PT_TRIANGLEFAN
	D3DPT_POINTLIST				,	// zVBUFFER_PT_POINTLIST
	D3DPT_LINELIST				,	// zVBUFFER_PT_LINELIST
	D3DPT_LINESTRIP					// zVBUFFER_PT_LINESTRIP
};

zBOOL zCRnd_D3D :: XD3D_DrawVertexBufferWire( zCVertexBuffer *vertexBuffer, const int firstVert, const int numVert, zWORD *indexList, const zDWORD numIndex )
{
	// Primitive Type uebersetzen
	D3DPRIMITIVETYPE	primTypeD3D	= s_primitiveArray[vertexBuffer->GetPrimitiveType()];
	zCVertexBuffer_D3D	*vbD3D		= static_cast<zCVertexBuffer_D3D*>( vertexBuffer );

	// FLAT
	SetTexture( 0, 0 );
	zDWORD drawFlags=0;

	zDWORD indexListSize;
	zWORD *indexListPtr;
	if( numIndex>0 )
	{
		indexListSize = numIndex;
		indexListPtr = indexList;
	}
	else
	{
		indexListSize = vbD3D->GetIndexListSize();
		indexListPtr = vbD3D->GetIndexListPtr();
	}

	XD3D_SetRenderState( D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME );
	SetRenderState( zRND_RENDERSTATE_TEXTUREFACTOR, 0xffffffff );
	if( xd3d_actRenderState[D3DRENDERSTATE_LIGHTING]==TRUE )
	{
		if( FAILED( SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE4X ) ) )
			if( FAILED( SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE2X ) ) )
				SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_MODULATE );
	}
	else
		SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG1 );
	SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_TFACTOR );
	SetTextureStageState( 0, zRND_TSS_COLORARG2, zRND_TA_DIFFUSE );
	SetTextureStageState( 1, zRND_TSS_COLOROP, zRND_TOP_DISABLE );

	if( indexListSize>0 )
	{
		// indexed
		if( !DXTryWarning( xd3d_pd3dDevice7->DrawIndexedPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer, firstVert, numVert,
				indexListPtr, indexListSize, drawFlags ), "X: [RND3D]XD3D_DrawVertexBufferFlat: Draw VB (indexed) failed" ) )
			return FALSE;
	}
	else
	{
		// not-indexed
		if( !DXTryWarning( xd3d_pd3dDevice7->DrawPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer, firstVert, numVert,
				drawFlags ), "X: [RND3D]XD3D_DrawVertexBufferFlat: Draw VB (non-indexed) failed" ) )
			return FALSE;
	}
	XD3D_SetRenderState( D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID );

	return TRUE;
}



/*--------------------------------------------------------------------------

	zBOOL zCRnd_D3D :: XD3D_DrawVertexBufferFlat( zCVertexBuffer *vertexBuffer, const int firstVert, const int numVert, zWORD *indexList, const zDWORD numIndex )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: XD3D_DrawVertexBufferFlat( zCVertexBuffer *vertexBuffer, const int firstVert, const int numVert, zWORD *indexList, const zDWORD numIndex )
{
	// Primitive Type uebersetzen
	D3DPRIMITIVETYPE	primTypeD3D	= s_primitiveArray[vertexBuffer->GetPrimitiveType()];
	zCVertexBuffer_D3D	*vbD3D		= static_cast<zCVertexBuffer_D3D*>( vertexBuffer );

	// FLAT
	SetTexture( 0, 0 );
	zDWORD drawFlags=0;

	zDWORD indexListSize;
	zWORD *indexListPtr;
	if( numIndex>0 )
	{
		indexListSize = numIndex;
		indexListPtr = indexList;
	}
	else
	{
		indexListSize = vbD3D->GetIndexListSize();
		indexListPtr = vbD3D->GetIndexListPtr();
	}

	XD3D_SetRenderState( D3DRENDERSTATE_TEXTUREFACTOR, 0xffffffff );
	SetTextureStageState( 0, zRND_TSS_COLOROP, zRND_TOP_SELECTARG1 );
	SetTextureStageState( 0, zRND_TSS_COLORARG1, zRND_TA_DIFFUSE );
	SetTextureStageState( 1, zRND_TSS_COLOROP, zRND_TOP_DISABLE );

	if( indexListSize>0 )
	{
		// indexed
		if( !DXTryWarning( xd3d_pd3dDevice7->DrawIndexedPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer, firstVert, numVert,
				indexListPtr, indexListSize, drawFlags ), "X: [RND3D]XD3D_DrawVertexBufferFlat: Draw VB (indexed) failed" ) )
			return FALSE;
	}
	else
	{
		// not-indexed
		if( !DXTryWarning( xd3d_pd3dDevice7->DrawPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer, firstVert, numVert,
				drawFlags ), "X: [RND3D]XD3D_DrawVertexBufferFlat: Draw VB (non-indexed) failed" ) )
			return FALSE;
	}

	return TRUE;
}



/*--------------------------------------------------------------------------

	zBOOL zCRnd_D3D :: DrawVertexBuffer( zCVertexBuffer *vertexBuffer, int firstVert, int numVert )

 

    14-Aug-00       [PELZER]
    22-Nov-00       [HILDEBRANDT]
					Separates xd3d_polysRendered und xd3d_trisRendered entferent (=> nun komplett in xd3d_statistics)
--------------------------------------------------------------------------*/

zBOOL zCRnd_D3D :: DrawVertexBuffer( zCVertexBuffer *vertexBuffer, int firstVert, int numVert, zWORD *indexList, zDWORD numIndex )
{ 
	// if no firstVert and numVert specified the entire VB will be rendered
	zERR_ASSERT( vertexBuffer );

	if( numVert==0 )
		return TRUE;

	if( numVert<0 )
		numVert = vertexBuffer->numVertex;

	// Primitive Type uebersetzen
	D3DPRIMITIVETYPE	primTypeD3D	= s_primitiveArray[vertexBuffer->GetPrimitiveType()];
	zCVertexBuffer_D3D	*vbD3D		= static_cast<zCVertexBuffer_D3D*>( vertexBuffer );

	// stats updaten
	zDWORD indexListSize;
	zWORD *indexListPtr;
	if( numIndex>0 )
	{
		indexListSize = numIndex;
		indexListPtr = indexList;
	}
	else
	{
		indexListSize = vbD3D->GetIndexListSize();
		indexListPtr = vbD3D->GetIndexListPtr();
	}

	int numVertStats = ( indexListSize>0 ) ? indexListSize : numVert;
	switch( vertexBuffer->GetPrimitiveType() )
	{
		case	zVBUFFER_PT_TRIANGLELIST:
				numVertStats /= 3;
				xd3d_statistics.numTrisRendered += numVertStats;
				xd3d_statistics.numPolysRendered+= numVertStats;
				break;
		case	zVBUFFER_PT_TRIANGLEFAN:
				xd3d_statistics.numTrisRendered += numVertStats-2;
				++xd3d_statistics.numPolysRendered;
				break;
		case	zVBUFFER_PT_TRIANGLESTRIP:
				xd3d_statistics.numTrisRendered	+= numVertStats-2;
				xd3d_statistics.numPolysRendered+= numVertStats-2;
				break;
	}

	// Draw Flags
	zDWORD drawFlags = 0;
	zBOOL lightingOn;
	zBOOL clippingOn;
	zBOOL culling;
	switch( vbD3D->GetVertexType() ) 
	{
		case	zVBUFFER_VERTTYPE_UT_UL:
				lightingOn = TRUE;
				xd3d_vbclipping = TRUE;
				clippingOn = xd3d_vbclipping; //Gesetzten Hint berücksichtigen
				culling = D3DCULL_CW;
				break;
		case	zVBUFFER_VERTTYPE_UT_L:
				lightingOn = FALSE; 
				xd3d_vbclipping = TRUE;
				clippingOn = xd3d_vbclipping; //Gesetzten Hint berücksichtigen
				culling = D3DCULL_CW;
				break;
		case	zVBUFFER_VERTTYPE_T_L:
		default:
				lightingOn = FALSE; 
				clippingOn = FALSE;
				culling = D3DCULL_NONE;
	};

	DXTryWarning( XD3D_SetRenderState( D3DRENDERSTATE_LIGHTING, lightingOn ), "X: [RND3D]DrawVertexBuffer: Set lighting failed" );
	XD3D_SetRenderState( D3DRENDERSTATE_CLIPPING, clippingOn );
	XD3D_SetRenderState( D3DRENDERSTATE_CULLMODE, culling );

	zBOOL returnValue = TRUE;
	// handle Flat und Wire Modes

	switch( polyDrawMode )
	{
		case	zRND_DRAW_WIRE:	
				if( !XD3D_DrawVertexBufferWire( vertexBuffer, firstVert, numVert, indexList, numIndex ) )
					returnValue = FALSE;
				break;
		case	zRND_DRAW_FLAT:	
				if( !XD3D_DrawVertexBufferFlat( vertexBuffer, firstVert, numVert, indexList, numIndex ) )
					returnValue = FALSE;
				break;
		case	zRND_DRAW_MATERIAL_WIRE:
				if( indexListSize>0 ) 
				{
					// indexed
					if( !DXTryWarning( xd3d_pd3dDevice7->DrawIndexedPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer, firstVert, numVert, 
							indexListPtr, indexListSize, drawFlags ), "X: [RND3D]DrawVertexBuffer: Draw VB (indexed) failed" ) )
						returnValue = FALSE;
				} 
				else 
				{
					// not-indexed
					if( !DXTryWarning( xd3d_pd3dDevice7->DrawPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer,	firstVert, numVert,	drawFlags ), 
							"X: [RND3D]DrawVertexBuffer: Draw VB (non-indexed) failed" ) )
						returnValue = FALSE;
				}	
				XD3D_SetRenderState( D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL );
				if( !XD3D_DrawVertexBufferWire( vertexBuffer, firstVert, numVert, indexList, numIndex ) )
					returnValue = FALSE;
				break;
		default:
				if( indexListSize>0 ) 
				{
					// indexed
					if( !DXTryWarning( xd3d_pd3dDevice7->DrawIndexedPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer, firstVert, numVert, 
							indexListPtr, indexListSize, drawFlags ), "X: [RND3D]DrawVertexBuffer: Draw VB (indexed) failed" ) )
						returnValue = FALSE;
				} 
				else 
				{
					// not-indexed
					if( !DXTryWarning( xd3d_pd3dDevice7->DrawPrimitiveVB( primTypeD3D, vbD3D->xvb_vertexBuffer,	firstVert, numVert,	drawFlags ), 
							"X: [RND3D]DrawVertexBuffer: Draw VB (non-indexed) failed" ) )
						returnValue = FALSE;
				}
	}

	DXTryWarning( XD3D_SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE ), "X: [RND3D]DrawVertexBuffer: Disable lighting failed" );

	return returnValue;
}


void zCRnd_D3D::Vid_BeginLfbAccess()
{
	xd3d_scale_A = xd3d_zMAX_from_Engine/(xd3d_zMAX_from_Engine-xd3d_zMIN_from_Engine);
	xd3d_scale_B = -xd3d_zMAX_from_Engine*xd3d_zMIN_from_Engine/(xd3d_zMAX_from_Engine-xd3d_zMIN_from_Engine);
};





/*--------------------------------------------------------------------------

	zCVertexBuffer* zCRnd_D3D :: CreateVertexBuffer()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCVertexBuffer* zCRnd_D3D :: CreateVertexBuffer() 
{ 
	return zNEW( zCVertexBuffer_D3D );
}