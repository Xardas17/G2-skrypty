/******************************************************************************** 
 
     $Workfile:: zRndD3D.h            $                $Date:: 15.03.01 2:18    $
     $Revision:: 75                   $             $Modtime:: 14.03.01 21:11   $
        Author:: Pelzer/Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   C++ Hardware Abstraction Layer (low/mid/hi-Level)
   DirectX 7 - Implementation
   created       : 02.02.2000

 * $Log: /current_work/ZenGin/_Kurt/zRndD3D.h $
 * 
 * 75    15.03.01 2:18 Hildebrandt
 * 
 * 74    14.02.01 7:28 Hildebrandt
 * 
 * 73    5.02.01 18:36 Hildebrandt
 * 
 * 72    31.01.01 1:47 Hildebrandt
 * added ini setting readout (zFogDisabled)
 * 1     8.12.00 21:29 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Pelzer/Hildebrandt
/// @version $Revision: 75 $ ($Modtime: 14.03.01 21:11 $)

// ============================================================================================================


#ifndef __ZRNDD3D_H__
#define __ZRNDD3D_H__

#pragma warning(1 : 4706)/* assignment in conditional expression */
#pragma warning(1 : 4189)/* local variable inited but not referenced */


// zengine includes
#ifndef __ZMATERIAL_H__
#include <zMaterial.h>
#endif

#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif

#ifndef __Z3D_H__
#include <z3d.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZWIN32_H__
#include <zWin32.h>
#endif

#ifndef __ZWIDEO_WIN32_H__
#include <zVideo_Win32.h>
#endif

#ifndef __ZTEXCONVERT_H__
#include <zTexConvert.h>
#endif

#ifndef __ZERROR_H__
#include <zError.h>
#endif

#ifndef __ZVERTEXBUFFER_H__
#include <zVertexBuffer.h>
#endif


// directx includes ( dx 7.0 sdk )
#ifndef __DDRAW_INCLUDED__
#include <ddraw.h>
#endif

#ifndef _D3D_H_
#include <d3d.h>
#endif

#ifndef __D3DX_H__
#include <d3dx.h>
#endif

#define scrSTATUS_Used			1
#define scrSTATUS_Free			0

#define MAXBUCKETS				256
#define MAXALPHAPOLYS			2048
#define ALPHAVERTEXBUFFERSIZE	1024
#define MAXTEXTURESTAGES		4
#define MAXRENDERSTATES			160

#define SURFACECACHECOUNTLIMIT	128
#define SURFACECACHETIMELIMIT	2000
#define RADIAL 1
#define LINEAR 2


#define d3dMIN(a,m)				(a>m ? a:m)
#define d3dMAX(a,m)				(a<m ? a:m)
#define d3dCLAMP(a, min,max)	(d3dMIN(d3dMAX(a,max),min))

class zCSurfaceCache_D3D;
extern zCSurfaceCache_D3D		global_surfaceCache;
class zCDXTCCache_D3D;
extern zCDXTCCache_D3D			global_DXTCCache;

inline zBOOL DXTryWarning( HRESULT hr, const char *info_str = NULL ) 
{ 
	if( FAILED( (HRESULT)hr ) ) 
	{ 
		char error_str[128]; 
		char output_str[256]; 
		D3DXGetErrorString( (HRESULT)hr, 128, error_str );
		if( info_str!=NULL )
			sprintf( output_str, "%s Error: %s", (char*)info_str, error_str );
		else
			sprintf( output_str, "(w/o info) Error: %s", error_str );
		zERR_WARNING( output_str );
		return FALSE;
	} 
	return TRUE;
}



enum zTRnd_DepthBufferLevel
{
	zRND_W32_BUFFER,
	zRND_W24_BUFFER,
	zRND_W16_BUFFER,
	zRND_Z32_BUFFER,
	zRND_Z24_BUFFER,
	zRND_Z16_BUFFER,
	zRND_UNKNOWN_BUFFER
};



class zCTex_D3D;
struct zD3D_savedTexture;
class zCVertexBuffer_D3D;



class zD3D_alphaPoly : public zCRndAlphaSortObject
{
	friend class zCRnd_D3D;

public:
	enum					{ zMAX_VERT	= 8 };

	void					Draw( int currentIndex );
	zBOOL					IsAlphaPoly() { return TRUE; };

protected:
	struct zD3D_vertexFormat
	{
		D3DVALUE a_sx;
		D3DVALUE a_sy;
		D3DVALUE a_sz;
		D3DVALUE a_rhw;
		D3DCOLOR a_color;
		D3DVALUE a_tu;
		D3DVALUE a_tv;
	};

	zTRnd_AlphaBlendFunc	alphafunc;
	zCTex_D3D				*tex;
	zBOOL					wrap;
	unsigned long			zfunc;
	int						numVert;
	int						zBias;
	zD3D_vertexFormat		vertexList[zMAX_VERT];		// was: D3DTLVERTEX, and zMAX_POLY_CLIP_VERTS

	static zCVertexBufferDyn *vertexbufferdyn;
	static zCVertexBuffer	*vertexbuffer;
	static zBOOL			locked;
	static zDWORD			startvertex;
	static zDWORD			actvertex;
	static int				numberofvertices;
	static int				actnov;
};


class zCRnd_D3D : public zCRenderer 
{
	friend class zD3D_alphaPoly;
	friend class zCTex_D3D;
	friend class zCSurfaceCache_D3D;
	friend class zCDXTCCache_D3D;
	friend class zCVertexBuffer_D3D;

public:
	// Inits & Shutdowns
	zCRnd_D3D();
	~zCRnd_D3D();
	
	void					EmergencyExit();


	// management
	void					BeginFrame				();
	void					EndFrame				();
	void					FlushPolys				();
	

	// hi-level Rendering
	void					DrawPolySimple			( zCTexture *texture, zTRndSimpleVertex *vertex, int numVert );
	void					DrawPoly				( zCPolygon* poly );
	void					DrawLightmapList		( zCPolygon** polyList, int numPoly );
	void					DrawLine				( float x1, float y1, float x2, float y2, const zCOLOR col );
	void					DrawLineZ				( float x1Scr, float y1Scr, float z1CamSpaceInv, float x2Scr, float y2Scr, float z2CamSpaceInv, const zCOLOR col );
	void					SetPixel				( float x, float y, const zCOLOR col );

 
	// set/get Modes
	void					SetFog					( const zBOOL foggy );
	zBOOL					GetFog					() const;
	void					SetRadialFog			(const zBOOL foggy);
	zBOOL					GetRadialFog			() const									{ return xd3d_enableRadialFog && GetFog();	};
	void					SetFogColor				( const zCOLOR& col );
	zCOLOR					GetFogColor				() const;
	void					SetFogRange				( const float nearz, const float farz, const zTRnd_FogMode falloff=zRND_FOG_FALLOFF_LINEAR );
	void					GetFogRange				( float& nearz, float& farz, zTRnd_FogMode& falloff );
	int						GetFogType				() const									{ return fogType;	};
	void					SetFogType				(const int a_Type);
	void					SetPolyDrawMode			( const zTRnd_PolyDrawMode& drawMode );
	zTRnd_PolyDrawMode		GetPolyDrawMode			() const;
	void					SetTextureWrapEnabled	( const zBOOL b );
	zBOOL					GetTextureWrapEnabled	() const;
	void					SetBilerpFilterEnabled	( const zBOOL b );
	zBOOL					GetBilerpFilterEnabled	() const;
	void					SetDitherEnabled		( const zBOOL b );
	zBOOL					GetDitherEnabled		() const;


	// sorting, zbuffering
	void					SetPolySortMode			( const zTRnd_PolySortMode& smode );
	zTRnd_PolySortMode		GetPolySortMode			() const;
	void					SetZBufferWriteEnabled	( const zBOOL flag );
	zBOOL					GetZBufferWriteEnabled	() const;
	void					SetZBufferCompare		( const zTRnd_ZBufferCmp& zcmp );
	zTRnd_ZBufferCmp		GetZBufferCompare		();
	void					SetZBias				(const int a_zBias);
	int						GetZBias				() const;			
	void					SetPixelWriteEnabled	( const zBOOL flag );
	zBOOL					GetPixelWriteEnabled	() const;
	

	// alpha-blending related
	void					SetAlphaBlendSource		( const zTRnd_AlphaBlendSource &src );
	zTRnd_AlphaBlendSource	GetAlphaBlendSource		() const;
	void					SetAlphaBlendFunc		( const zTRnd_AlphaBlendFunc &mode );
	zTRnd_AlphaBlendFunc	GetAlphaBlendFunc		() const;
	void					SetAlphaBlendFactor		( const float &percentage );
	float					GetAlphaBlendFactor		() const;
	zBOOL					SupportAlphaTesting		();
	void					SetAlphaReference		(const DWORD a_alphaReference)					{ alphaReference = a_alphaReference;	};
	zDWORD					GetAlphaReference		()	const										{ return alphaReference;	};
	zBOOL					GetAlphaLimitReached	() const										{ return m_bAlphaLimitReached;	};
	zBOOL					GetCacheAlphaPolys		() const										{ return m_bCacheAlphaPolys; };	// TRUE: renderer caches alpha-polys and renders them z-sorted at FlushPolys(), FALSE: alpha-Polys are rendered immediatel
	void					SetCacheAlphaPolys		(const zBOOL b) 								{ m_bCacheAlphaPolys = b;	};	
	void					AddAlphaPoly			(const zCPolygon* poly);
	void					FlushAlphaPolys			();

	//
	void					SetRenderMode			( const zTRnd_RenderMode rmode );
	zTRnd_RenderMode		GetRenderMode			() const;
	int						HasCapability			( const zTRnd_Capability ) const;
	void					ResetZTest				();
	int						HasPassedZTest			();
	zWORD					GetTexturePortableBinaryVersion();
	void					GetGuardBandBorders		( float& guardBandLeft, float& guardBandTop, float& guardBandRight, float& guardBandBottom );


	// texture
	zCTexture				*CreateTexture			(); 
	void					GetStatistics			( zTRnd_Stats &stat );
	void					ResetStatistics			();
	int						GetTotalTextureMem		(); // returns bytes
	zBOOL					SupportsTextureFormat	( const zTRnd_TextureFormat texFormat);
	zBOOL					SupportsTextureFormatHardware( const zTRnd_TextureFormat texFormat);
	int						GetMaxTextureSize		();
	zCTextureConvert		*CreateTextureConvert	();

	// surface loss
	virtual zBOOL			GetSurfaceLost		() const								{ return m_bSurfaceLost;	};
	virtual void			SetSurfaceLost		(const zBOOL b)							{ m_bSurfaceLost = b;		};

	// alternate render options
	virtual zBOOL			GetSyncOnAmbientCol () const								{ return m_bMustFlushOnAmbientColor;};
	virtual void			SetSyncOnAmbientCol (const zBOOL b)							{ m_bMustFlushOnAmbientColor = b;   };
	
	// blit
	void					Vid_Blit				( zBOOL forceFlip, RECT *sourceRect, RECT *destRect );
	

	// lock							
	zBOOL					Vid_Lock				( zTRndSurfaceDesc &surfdesc );
	zBOOL					Vid_Unlock				();
	zBOOL					Vid_IsLocked			() { return xd3d_backlocked; };


	// copy frontbuffer
	zBOOL					Vid_GetFrontBufferCopy	( zCTextureConvert &frontcopy );


	// services
	void					Vid_Clear				( zCOLOR &col, int clearTarget = ( zRND_CLEAR_FRAMEBUFFER|zRND_CLEAR_ZBUFFER ) );
	int						Vid_GetNumDevices		();
	int						Vid_GetActiveDeviceNr	();
	zBOOL					Vid_SetDevice			( int deviceNr ); 
	zBOOL					Vid_GetDeviceInfo		( zTRnd_DeviceInfo& deviceInfo, int deviceNr );
	int						Vid_GetNumModes			() ;
	zBOOL					Vid_GetModeInfo			( zTRnd_VidModeInfo& modeInfo, int modeNr );
	int						Vid_GetActiveModeNr		();
	zBOOL					Vid_SetMode				( int modeNr, zTSystemContextHandle *winHandle = 0 );
	void					Vid_SetScreenMode		( zTRnd_ScreenMode scrmode );
	zTRnd_ScreenMode		Vid_GetScreenMode		();
	void					Vid_SetGammaCorrection	( float gamma = 0.5f, float contrast = 0.5f, float brightness = 0.5f ); // all [0.1;0.9]
	float					Vid_GetGammaCorrection	();

///////////////// ??? OBSOLETE ??? /////////////////
/**/	void					Vid_BeginLfbAccess		();
/**/	void					Vid_EndLfbAccess		() {};
/**/	void					Vid_SetLfbAlpha			( int opacity ) {}; // [0;255]
/**/	void					Vid_SetLfbAlphaFunc		( const zTRnd_AlphaBlendFunc &func ) {};
////////////////////////////////////////////////////
	
// ===================================================================================================================

	// Transform and Lighting
	zBOOL					SetTransform			( zTRnd_TrafoType transformType, const zMAT4& matrix );
	zBOOL					SetViewport				( int x0, int y0, int xdim, int ydim );
	zBOOL					SetLight				( zDWORD lightIndex, zCRenderLight *light );
									
	// Material
	zBOOL					SetMaterial				( const zTMaterial &material );
	zBOOL					GetMaterial				( zTMaterial &material );

	// Multitexture Stages			
	zBOOL					SetTexture				( zDWORD stage, zCTexture *texture );
	zBOOL					SetTextureStageState	( zDWORD stage, zTRnd_TextureStageState state, zDWORD value );
	zBOOL					SetAlphaBlendFuncImmed	( const zTRnd_AlphaBlendFunc afunc );
				
	zBOOL					SetRenderState			( zTRnd_RenderStateType renderStateType, zDWORD renderState );
	zDWORD					GetRenderState			( zTRnd_RenderStateType renderStateType );

	// Alpha Object Sorting
	void					AddAlphaSortObject		( zCRndAlphaSortObject *alphaSortObject );
	void					RenderAlphaSortList		();

	// VertexBuffer
	zBOOL					DrawVertexBuffer		( zCVertexBuffer *vertexBuffer, int firstVert=0, int numVert=-1, zWORD *indexList=0, zDWORD numIndex=0 );
	zCVertexBuffer*			CreateVertexBuffer		();

	void					SetPalSupport			( zBOOL support ) { xd3d_palsupp = support; };
	zBOOL					GetPalSupport			() { return xd3d_palsupp; };

protected:	
	static ID3DXContext		*xd3d_pd3dx; // DirectX-Pointer
	static IDirectDraw7		*xd3d_pdd7;
	static IDirect3D7		*xd3d_pd3d7;
	static IDirect3DDevice7	*xd3d_pd3dDevice7;

	static unsigned long	xd3d_actFrameNumber;
	static zBOOL			xd3d_dd7inuse;	

	static zBOOL			xd3d_palsupp;

private:
	struct zD3D_Status // statusflags fuer die D3D-statevariablen
	{	
		int						modeNr;
		int						devnum;
		int						devmax;
		zBOOL					texwrap;
		zBOOL					filter;
		zBOOL					dither;
		zBOOL					fog;
		float					nearZ;
		float					farZ;
		zCOLOR					fogColor;
		zTRnd_FogMode			fogMode;
		zTRnd_AlphaBlendFunc	alphafunc;
		zTRnd_AlphaBlendSource	alphasrc;
		float					alphafactor;
		zBOOL					zenable;
		zBOOL					fenable;
		zTRnd_ZBufferCmp		zfunc;
		zBOOL					zwrite;
		int						zbias;
		unsigned long			zd3dfunc;
		DDPIXELFORMAT			ddpf;
		float					gammavalue;
		zBOOL					palsupported;
		zTRnd_RenderMode		renderMode;

		zD3D_Status()
		{
			modeNr			= 0;
			devnum			= 0;
			devmax			= 1;
			texwrap			= TRUE;
			filter			= TRUE;
			dither			= TRUE;
			fog				= FALSE;
			nearZ			= 0.0f;
			farZ			= 0.0f;
			fogColor.SetRedByte( 0x00 );
			fogColor.SetGreenByte( 0x00 );
			fogColor.SetBlueByte( 0x00 );
			fogMode			= zRND_FOG_FALLOFF_LINEAR;
			alphafunc		= zRND_ALPHA_FUNC_MAT_DEFAULT;
			alphasrc		= zRND_ALPHA_SOURCE_MATERIAL; 
			alphafactor		= 1.0f;
			fenable			= TRUE;
			zbias			= 0;
			zfunc			= zRND_ZBUFFER_CMP_LESS;
			zwrite			= TRUE;
			zd3dfunc		= D3DCMP_LESSEQUAL;
			gammavalue		= 0.45f;
			palsupported	= FALSE;
			renderMode		= zRND_MODE_1_PASS_VERT_LIGHT;
		}
	};

	struct zD3D_Caps
	{	
		unsigned long			vidmemsize;
		unsigned long			vidmemfree;
		unsigned long			mintexsize;
		unsigned long			maxtexsize;
		zBOOL					window;
		zBOOL					gamma;
		zBOOL					multitexture;
		zBOOL					ztest;
		zBOOL					guardband;
		float					guardbandleft;
		float					guardbandright;
		float					guardbandtop;
		float					guardbandbottom;
		
		zBOOL					alphatest;
		int						num_stages;
		int						num_texstages;	
		zBOOL					tnl;
		zBOOL					tnl_hardware;
		zBOOL					tnl_maxlights;
		zBOOL					blendDiffuseAlpha;
		zBOOL					hasStencil;

		zD3D_Caps()
		{
			vidmemsize			= 0;
			vidmemfree			= 0;
			mintexsize			= 0;
			maxtexsize			= 0;
			window				= FALSE;
			gamma				= FALSE;
			multitexture		= FALSE;
			ztest				= FALSE;
			guardband			= FALSE;
			guardbandleft		= 0.0f;
			guardbandright		= 0.0f;
			guardbandtop		= 0.0f;
			guardbandbottom		= 0.0f;
			alphatest			= FALSE;
			num_texstages		= 0;
			tnl					= FALSE;
			tnl_hardware		= FALSE;
			tnl_maxlights		= 0;
			hasStencil			= FALSE;
			blendDiffuseAlpha	= FALSE;
		}
	};

	int						fogType;

	zDWORD					xd3d_actRenderState[MAXRENDERSTATES];
	zDWORD					xd3d_actTexStageState[MAXTEXTURESTAGES][zRND_TSS_COUNT];
	zD3D_Status				xd3d_actStatus;
	zD3D_Caps				xd3d_Capabilities;
	DDDEVICEIDENTIFIER2		xd3d_deviceIdentifier;
	
	unsigned int			xd3d_numLightmapsUsedThisFrame;

	zBOOL					xd3d_wBuffer;
	zTRnd_DepthBufferLevel	xd3d_zwBufferLevel;
	zBOOL					xd3d_alphaTest;
	zBOOL					xd3d_alphaBlendImmed;

	zBOOL					xd3d_backlocked;

	IDirectDrawSurface7		*xd3d_pfrontBuffer;
	IDirectDrawSurface7		*xd3d_pbackBuffer;
	IDirectDrawSurface7		*xd3d_pzBuffer;
	IDirectDrawClipper		*xd3d_pclipper;
	IDirectDrawGammaControl	*xd3d_pgammacontrol;
	DDPIXELFORMAT			xd3d_pixelformat;

	zBOOL					xd3d_deviceChange;


	zTRnd_ScreenMode		xd3d_scrMode; // Screendaten
	int						xd3d_scrStatus;
	int						xd3d_scrWidth;
	int						xd3d_scrHeight;
	int						xd3d_scrBpp;

	int						xd3d_num;
	zTRnd_ScreenMode		xd3d_mode;
	int						xd3d_x; 
	int						xd3d_y;
	int						xd3d_bpp;
	
	float					xd3d_zMAX_from_Engine;
	float					xd3d_zMIN_from_Engine;
	float					xd3d_scale_A;
	float					xd3d_scale_B;
	float					xd3d_scale_C;

	zCMaterial				*xd3d_pactivematerial;
	zTMaterial				xd3d_actmaterial;

	zTRnd_Stats				xd3d_statistics;
	HWND					xd3d_newWinHandle;
	HWND					xd3d_winHandle;
	zTRnd_RenderMode		xd3d_renderMode;
	int						xd3d_tryDevnum;
	zBOOL					xd3d_inScene;

	// .ini settings
	zBOOL					xd3d_disableFog;
	zBOOL					xd3d_enableRadialFog;

	zD3D_alphaPoly			xd3d_alphaPolyPool[MAXALPHAPOLYS];
	int						xd3d_numAlphaPolys;
	zCRndAlphaSortObject	*xd3d_alphaSortBucket[MAXBUCKETS]; 
	float					xd3d_bucketSize;
	zDWORD					alphaReference;
	
	zBOOL					xd3d_vbclipping;
	zDWORD					xd3d_texturefactor;
	zBOOL					m_bAlphaLimitReached;
	zBOOL					m_bSurfaceLost;

	zCTex_D3D				*xd3d_ptexture[MAXTEXTURESTAGES]; // Aktueller Texture- und Material-Stand
	IDirectDrawSurface7		*xd3d_pd3dtexture[MAXTEXTURESTAGES];
	unsigned int			xd3d_numTexturesUsedThisFrame;

	zD3D_savedTexture		*xd3d_savedTexture;

	zBOOL					m_bCacheAlphaPolys;
	zBOOL					m_bAnisotropicFilter;
	zBOOL					m_bMustFlushOnAmbientColor;
	zD3D_alphaPoly			*immediateAlphaPolyRoot;
	zD3D_alphaPoly			*immediateAlphaPolyParent;

	zBOOL					XD3D_InitPort			( int x, int y, int bpp, int id, int mode );
	zBOOL					XD3D_InitPerDX			( long flags, int x, int y, int bpp, int id );
	int						XD3D_EnumerateModes		( void );
	zBOOL					XD3D_SetMode			( int x,int y,int bpp );
	BOOL					XD3D_SetDevice			( int num, int x, int y, int bpp, zTRnd_ScreenMode mode );
	void					XD3D_ClearDevice		();
	inline zBOOL			XD3D_SetMaterial		( zCMaterial *material );
	zBOOL					XD3D_CreateWin			( const int x, const int y, const int bpp );
	void					XD3D_CloseWin			();
	static void				XD3D_SortAlphaPolys		( zCArray<zD3D_alphaPoly*> &polys, int items );
	void					XD3D_PolyDrawOnePassVertLight( zCPolygon *poly );
	void					XD3D_PolyDrawOnePassMultiTex( zCPolygon *poly );
	void					XD3D_PolyDrawTwoPassTexture( zCPolygon *poly );
	void					XD3D_PolyDrawTwoPassLightMap( zCPolygon *poly );
	inline void				XD3D_AlphaBlendPoly		( zCPolygon* poly, zCMaterial *mat );
	inline void				XD3D_AlphaTestPoly		( zCPolygon* poly );
	zBOOL					XD3D_TestCapabilities	();
	zBOOL					XD3D_SetTexture			( zDWORD stage, IDirectDrawSurface7 *texture );


	zBOOL					XD3D_TextureRescue		( zCTex_D3D *texture );
	zBOOL					XD3D_TextureRebuild		();

	zBOOL					XD3D_DrawVertexBufferWire( zCVertexBuffer *vertexBuffer, const int firstVert, const int numVert, zWORD *indexList, const zDWORD numIndex );
	zBOOL					XD3D_DrawVertexBufferFlat( zCVertexBuffer *vertexBuffer, const int firstVert, const int numVert, zWORD *indexList, const zDWORD numIndex );

	inline zBOOL			XD3D_SetRenderState		( D3DRENDERSTATETYPE renderStateType, zDWORD renderState )
	{
		if( xd3d_actRenderState[renderStateType]==renderState )
			return TRUE;
		if( !DXTryWarning( xd3d_pd3dDevice7->SetRenderState( renderStateType, renderState ), "X: [RND3D]XD3D_SetRenderState: Set render state failed!" ) )	
			return FALSE;

		xd3d_actRenderState[renderStateType] = renderState;

		if (m_bMustFlushOnAmbientColor && renderStateType==D3DRENDERSTATE_AMBIENT) 
		{
			xd3d_pd3dDevice7->EndScene();
			xd3d_pd3dDevice7->BeginScene();
		}

		//Sonderfall Alphatesting
		if( (renderStateType==D3DRENDERSTATE_ALPHATESTENABLE)&&(renderState==TRUE) )
		{
			xd3d_pd3dDevice7->SetRenderState( D3DRENDERSTATE_ALPHAREF, alphaReference );
			xd3d_pd3dDevice7->SetRenderState( D3DRENDERSTATE_ALPHAFUNC, D3DCMP_GREATEREQUAL );
			return TRUE;
		}

		if( (renderStateType==D3DRENDERSTATE_FOGENABLE)&&(renderState==FALSE) )
		{
			if (xd3d_enableRadialFog)	
			{
				xd3d_actRenderState[D3DRENDERSTATE_FOGVERTEXMODE]  = 0x1f1f1f1f;
				xd3d_actRenderState[D3DRENDERSTATE_RANGEFOGENABLE] = 0x1f1f1f1f;
			}
			else xd3d_actRenderState[D3DRENDERSTATE_FOGTABLEMODE]  = 0x1f1f1f1f;


			xd3d_actRenderState[D3DRENDERSTATE_FOGCOLOR] = 0x1f1f1f1f;
			xd3d_actRenderState[D3DRENDERSTATE_FOGSTART] = 0x1f1f1f1f;
			xd3d_actRenderState[D3DRENDERSTATE_FOGEND] = 0x1f1f1f1f;
			return TRUE;
		}

		return TRUE;
	}

	inline void				XD3D_ResetMultiTexturing();
};


class zCSurfaceCache_D3D
{
	friend class zCRnd_D3D;
	friend class zCTex_D3D;

protected:
	struct zCSlotIndex
	{
		int						dynamic;
		int						pixelformat;
		int						mipmaps;
		int						width;
		int						height;
	};

	struct zD3D_Entry
	{
		IDirectDrawSurface7		*surface;
		unsigned long			frameNumber;
		zD3D_Entry				*nextEntry;
	};

	struct zD3D_SlotHeader
	{
		zD3D_Entry				*firstEntry;
		zD3D_Entry				*lastEntry;
	};

public:
	zCSurfaceCache_D3D();
	~zCSurfaceCache_D3D();

	zBOOL					CacheInSurface			( IDirectDrawSurface7 *surface, zCSlotIndex *slotindex );
	IDirectDrawSurface7		*CacheOutSurface		( zCSlotIndex *slotindex );
	void					ClearCache				();

	static void				ResetSurfaceList		() { for( int t = 0; t<SURFACECACHECOUNTLIMIT; t++ ) xsc_listofsurfaces[t] = NULL; xsc_listposition = 0; };

private:
	int						xsc_cacheentryCounter;
	zD3D_SlotHeader			xsc_slot[2][6][12][12][12];

	static zD3D_SlotHeader	*xsc_listofsurfaces[SURFACECACHECOUNTLIMIT];
	static int				xsc_listposition;

	void					XSC_ClearSlot				( zD3D_SlotHeader *slot );
	void					XSC_KillLastSurfaceInSlot	( zD3D_SlotHeader *slot );
};


class zCDXTCCache_D3D
{
public:
	zCDXTCCache_D3D();
	~zCDXTCCache_D3D();

	IDirectDrawSurface7		*Lock( int width, int height, int format );
	zBOOL					Unlock( int width, int height, int format, IDirectDrawSurface7 *surface );
	void					ClearCache();

private:
	struct zD3D_Entry
	{
		IDirectDrawSurface7		*surface;
		zBOOL					locked;
		zD3D_Entry				*nextEntry;
	};
	struct zD3D_SlotHeader
	{
		zD3D_Entry				*firstEntry;
		zD3D_Entry				*lastEntry;
	};

	int						xdxtc_cacheentryCounter;
	zD3D_SlotHeader			xdxtc_slot[2][12][12];

	IDirectDrawSurface7		*XDXTC_CreateSurface( int width, int height, int format, zD3D_Entry *entry );
};


struct zD3D_savedTexture
{
	zCTex_D3D				*texture;
	zCTextureConvert*		texCon;
	zD3D_savedTexture		*next; 
}; 


class zCTex_D3D : public zCTexture 
{
public:
	zCTex_D3D();
	~zCTex_D3D();

	zBOOL					Lock					( int m=0 );
	zBOOL					Unlock					();
	void					InsertTexture			( zBOOL palsupp, int stage = 0 );
	zBOOL					RemoveTexture			();
	void					ReleaseData				();
	void					GetPixelSize			( int& xdim, int &ydim );
	zBOOL					SetTextureInfo			( const zCTextureInfo& texInfo );
	zBOOL					GetTextureBuffer		( int mipMapNr, void* &buffer, int &pitchXBytes );

	void*					GetPaletteBuffer		();
	zCTextureInfo			GetTextureInfo			();
	zBOOL					CopyPaletteDataTo		( void* destBuffer );
	zBOOL					CopyTextureDataTo		( int mipMapNr, void* destBuffer, int destPitchXBytes );
	zBOOL					HasAlpha				() const	{ return xtex_alphaTex; };			//Rückgabe der Information, ob dies Textur einen Alpha-Channel besitzt

	zBOOL					PreloadTexture			();
	zBOOL					SetTexture				( int stage );

	inline unsigned long	GetLastFrameUsed		() const	{ return xtex_lastFrameUsed;							};	//Rückgabe der Frame-Nummer, bei der diese Textur das letztemal aktiv war
	void					SetLastFrameUsed		()			{ xtex_lastFrameUsed = zCRnd_D3D::xd3d_actFrameNumber;	};	//Merken der aktuellen Frame-Nummer 

	zBOOL					RescueTexture			( zD3D_savedTexture *slm );
	zBOOL					RebuildTexture			( zD3D_savedTexture *slm );

private:
	unsigned int			xtex_textureflag;
	struct
	{
		int											: 17; // unused
		zBOOL			xtex_decompress				: 1;
		zBOOL			xtex_locked					: 1;
		zBOOL			xtex_palsupport				: 1;
		unsigned int	xtex_miplocked				: 12;
	};
	zCTextureInfo			xtex_texinfo;
	zCSurfaceCache_D3D::zCSlotIndex	
							xtex_slotindex;
	unsigned char			*xtex_pPalettePtr;
	IDirectDrawPalette		*xtex_pddpal;
	int						xtex_internalnumber;
	zBOOL					xtex_alphaTex;
	IDirectDrawSurface7		*xtex_pddtex[12];
	IDirectDrawSurface7		*xtex_pddtemporarytex[12]; //@TODO: Unnötigen Speicherverbrauch vermeiden !!!
	unsigned long			xtex_lastFrameUsed;
	void					*xtex_buffer;

	zBOOL					XTEX_BuildSurfaces( zBOOL decompressBuild );
};


class zCVertexBuffer_D3D : public zCVertexBuffer 
{
	friend class zCRnd_D3D;

public:	
	zCVertexBuffer_D3D();
	~zCVertexBuffer_D3D();

	zBOOL					Create					( zDWORD vertexFormat, zDWORD numVert, zDWORD createFlags );
	zBOOL					Destroy					();
										
	zBOOL					Lock					( zDWORD lockFlags );
	zBOOL					Unlock					();
	zBOOL					Optimize				();	// no Lock possible afterwards
	zBOOL					IsLocked				()	{ return xvb_locked; };
								
	zBOOL					SetPrimitiveType		( zTVBufferPrimitiveType primType );
	zTVBufferPrimitiveType	GetPrimitiveType		();
																			
	zDWORD					GetVertexFormat			();	
	zTVBufferVertexType		GetVertexType			();

	// Index List (array of zWORDs), no Lock/Unlock needed for access
	// Only if Index List Size is >0, the vertices are treated/rendered as indexed primitives. 
	// But the Buffer can still be rendered without any indices.
	zBOOL					SetIndexListSize		( zDWORD num );
	zDWORD					GetIndexListSize		();
	zWORD*					GetIndexListPtr			();
	zBOOL					SetIndexList			( const zCArray<zWORD>& indexList );

protected:
	static zCArray<zCVertexBuffer_D3D*>		xvb_vertexbufferList;

private:
	struct
	{
		int											: 23;	// unused
		zUINT8					xvb_optimized		: 1;	// bool
		zUINT8					xvb_locked			: 1;	// bool
		zTVBufferVertexType		xvb_vertexType		: 3;
		zTVBufferPrimitiveType	xvb_primitiveType	: 4;
	};

	zDWORD					xvb_vertexFormat;
	IDirect3DVertexBuffer7	*xvb_vertexBuffer;
	zCArray<zWORD>			xvb_indexList;
};



#endif //#ifndef __zRndD3D_H__
