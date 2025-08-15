

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  3DFX-Glide-Implementation
* File          : zRndGlide.h 
* Projekt       : Phoenix
* Autor         : Carsten Edenfeld
* Version       : 0.40
* last modified : 07.02.99
* erstellt      : 14.12.97										
* Compiler OK   : 
*																
*********************************************************************************
- known bugs: Spacer has problems with glide driver 2.60003
			  Voodoo Rush works best with Rush Driver 2.43
			  Game has problems with glide driver 2.48 (only lfb draw)?
*********************************************************************************
- possible optimizations: LfbPrimitives: No float to int conversion!
						  LfbColors: No int rgb_565 to float rgb_888 conversion !
						  glide is clamping RGBA Values automatically [0..255]

*********************************************************************************
- missing features: 
*********************************************************************************
- comments:
  tga files should be in DIR_TEX
  tex files should be in DIR_COMPILED_TEXTURES


(Alpha) Blend Modi:
	c1 = (c0 * a) + (c1 * (1-a))
	c1 = (a * c0 + c1)
	c1 = (c1 - c0)
	c1 = c0 * c1
	c1 = c0;

	Frage: Werden bei texeln mit alpha 0 die z-werte geschrieben ?
	grAlphaTestFunction

*********************************************************************************/

#ifndef __ZRENDERER_GLIDE_H__
#define __ZRENDERER_GLIDE_H__

#define FX_GLIDE_NO_FUNC_PROTO
#include <glide.h>
#include <glideutl.h>

#include "zCore.h"
#include "zRndGlide_Sym.h"
#include "zRenderer.h"
#include "zTexConvert.h"
#include "z3d.h"
#include "zTypes.h"

const int		GR_LOD_0		=	GR_LOD_1+1;
const float		SNAPCONST		=	(float) (3L << 18); // avoid lockups due to prec. problems
const float		NEAREST_OOW		=	1.0F;
const float		MAX_ALPHA		=	255.0F;
const float		MAX_FRAG		=	10.0F; // Defrag if fragmentation reaches 10%
const zDWORD	BACKGROUND_COL	=	0xff;  // assume RGBA Format

const int		GR_MAXBUCKETS	=	256;
const int		GR_MAXALPHAPOLYS=	5000;


class zCTex_RndGlide : public zCTexture {
public:
	// tmp static public !
	static zCList		<zCTex_RndGlide> texMem;// list to texture Memory slots
	static zDWORD		memAvail;				// actual memory available on hw
	static zDWORD		largestBlockAvail;		// largest Block actually available on hw

	zBOOL		 maxDetailTex;			// tmp E3 Hack
	float		 scaleX,scaleY;
	GrTexInfo	 infoCache;				// texture infos used in cache (actual mipmap level etc.)
	Gu3dfInfo    infoSrc;				// original tex-file info
    zDWORD		 sizeMipsCurrent;		// act size of all actual mipmaps needed in scene

	zCTex_RndGlide ();
	~zCTex_RndGlide ();

	static void		InitCache		();
	static void		ReleaseCache	();
	static float	GetFragmentation(); 
	static zBOOL	IsFragmentedTexMemHw();

	static void		ClearCache		();
	static void		Defrag			();
	static void		DefragPartial	(zDWORD maxTime,float maxFrag);

	static void		NewFrame		()									{ frameCounter ++;  };
	static int		GetFrame		()									{ return frameCounter; };
	static int		GetFreeTexMemHw	()									{ return memAvail; };
	static int		GetTotalTexMemHw()									{ return sizeTexMemHw; };

	static zBOOL	CheckCacheConsistency();
	static void		ShowTexCache	();
	static void		RecalcCacheMem	();

	static void		PrintCacheSlots	();

	inline void		SetAge			(); 
	inline int		GetAge			()									{ return age; };
	inline FxU32	GetHwMemPos		()									{ return addrTexHw; }
	inline void		RemoveFromCache	()									{ texMem.Remove(this); }


	void  Download() ;  
	void  Download_BruteForce();

	//
	// "virtuals"

	// for secure access to map-data (disk/mem)
	void			ReleaseData				();

	zBOOL			GetChromaKeyingEnabled	() const					{ return chromaTex; };
	void			SetChromaKeyingEnabled	(const zBOOL b)				{ chromaTex = b; };

     // accessing contents (read, write, readOnly, writeOnly)
    zBOOL			Lock                    (int lockMode);
    zBOOL			Unlock                  ();                                                                      
    //
    zBOOL			SetTextureInfo			(const zCTextureInfo& texInfo);
    void*			GetPaletteBuffer        ();
	zBOOL			GetTextureBuffer		(int mipMapNr, void* &buffer, int &pitchXBytes);
    // 
    zCTextureInfo   GetTextureInfo			();
    zBOOL           CopyPaletteDataTo		(void* destBuffer);
	zBOOL			CopyTextureDataTo		(int mipMapNr, void* destBuffer, int destPitchXBytes);		

private:
	// 3dfx texture mem list related
	static zDWORD				frameCounter;    
	static FxU32				root;					// First available hw-tex-mem-pos
	static zDWORD				sizeTexMemHw;			// max texture memory available on 3d-hw
	static zBOOL				fragmented;
	static zCTex_RndGlide*		tmpTexture;

	zFILE*			file;
	FxU32			addrTexHw;  // texaddr. on 3d-hw
    zCTex_RndGlide* next;       // ptr. to next pos if in hw-mem
	zDWORD			age;
	zDWORD			importance;
	zBOOL			locked;
	int				lockedMode;
	zCTextureInfo	infoTex;
	
	// additional texture information 
	zBOOL			alphaTex;
	zBOOL			chromaTex;
	void*			palette;					// engine internal palette buffer

	static inline zDWORD GetLargestBlock() ;
	static inline zDWORD GetFreeBlock	(zCList <zCTex_RndGlide> *help);

	void	Load3df						(zSTRING &fileName);
	int		GetMipSize					(int mipMapNr);
	void	ConvertPaletteToGlideFormat	();

	inline zCList <zCTex_RndGlide> *GetBestFitInCache();


};
 

class zCRnd_Glide : public zCRenderer {
public:

	// Inits & Shutdowns
	zCRnd_Glide();
	virtual ~zCRnd_Glide();

	// management

	void					BeginFrame			();
	void					EndFrame			();
	void					FlushPolys			() ;
	
	// hi-level Rendering
	void					DrawPolySimple		(zCTexture	*texture, zTRndSimpleVertex *vertex, int numVert);
	void					DrawPoly			(zCPolygon* poly) ;
	void					DrawPolyList		(int numPoly, zCPolygon** polyList);

	// set/get Modes
	void					SetPolySortMode		(const zTRnd_PolySortMode &smode);
	zTRnd_PolySortMode		GetPolySortMode     () const							{ return polySortMode; };

	void					SetPolyDrawMode		(const zTRnd_PolyDrawMode& drawMode);
	zTRnd_PolyDrawMode		GetPolyDrawMode		();

	zBOOL					GetZBufferWriteEnabled() const							{ return writeZBuffer; };
	void					SetZBufferWriteEnabled(const zBOOL b )					{ if (b) grDepthMask(FXTRUE); else grDepthMask(FXFALSE); writeZBuffer = b ;	};
	zREAL					GetZBias			() const							{ return zBias; };
	void					SetZBias			(const zREAL& zvalue)				{ grDepthBiasLevel((FxI16) zvalue);	zBias = zvalue;	};
	zTRnd_ZBufferCmp		GetZBufferCompare	()									{ return zBufCompareFunc; };
	void					SetZBufferCompare	(const zTRnd_ZBufferCmp& zcmp);

	zBOOL					GetCacheAlphaPolys	() const;		
	void					SetCacheAlphaPolys	(const zBOOL b);

	// Chroma Keying 
	void					EnableChromaKeying	();
	void					DisableChromaKeying	(); 
	void					SetChromaKeyColor	(const zCOLOR &col);
	int						GetChromaKeyColor	();

	void					SetBilerpFilterEnabled(const zBOOL b);		
	zBOOL					GetBilerpFilterEnabled() const;

	void					SetFog              (const zBOOL foggy) ;
	zBOOL					GetFog				() const							{ return fogEnabled; } ; 

	void					SetFogColor         (const zCOLOR& col) ;
	zCOLOR					GetFogColor			()	const							{ return fogColor; } ;

	void					SetFogRange			(const float nearz, const float farz, const zTRnd_FogMode type);
	void					GetFogRange			(float& nearz, float& farz, zTRnd_FogMode& falloff) 
																					{ nearz = nearZ; farz=farZ; falloff=fogType; };
	
	// alpha related
	void					SetAlphaBlendSource	( const zTRnd_AlphaBlendSource &src );
	void					SetAlphaBlendFunc	( const zTRnd_AlphaBlendFunc &mode ) ;
	zTRnd_AlphaBlendSource	GetAlphaBlendSource	();
	zTRnd_AlphaBlendFunc	GetAlphaBlendFunc	();
	float					GetAlphaBlendFactor	();
	void					SetAlphaBlendFactor	( const float &scale );// only for zRND_ALPHA_SRC_CONSTANT, obsolete for zRND_ALPHA_FUNC_NONE:
	void					SetSortAlphaPolys	( const zBOOL &sort );
	zBOOL					GetSortAlphaPolys	();
	void					SetTextureWrapEnabled(const zBOOL b)						{ wrapEnabled = b; 	int wrMode = wrapEnabled ? GR_TEXTURECLAMP_WRAP : GR_TEXTURECLAMP_CLAMP; grTexClampMode (GR_TMU0,wrMode,wrMode); };
	zBOOL					GetTextureWrapEnabled() const								{ return wrapEnabled; };


	// Vid/Primitive related

	int						Vid_GetNumDevices	();
	zBOOL					Vid_SetDevice		(int deviceNr);
	zBOOL					Vid_GetDeviceInfo	(zTRnd_DeviceInfo& deviceInfo, int deviceNr);
	int						Vid_GetNumModes		();
	zBOOL					Vid_GetModeInfo		(zTRnd_VidModeInfo& modeInfo, int modeNr) ;
	int						Vid_GetActiveModeNr	();
	int						Vid_GetActiveDeviceNr()													{ return 0;};
	zBOOL					Vid_SetMode			(int modeNr, HWND *winHandle=0);

	void					Vid_SetScreenMode	(zTRnd_ScreenMode screenMode);
	zTRnd_ScreenMode		Vid_GetScreenMode	()													{ return scrMode; }

	void					Vid_Lock			();
	void					Vid_Unlock			();
	zBOOL					Vid_IsLocked		()													{ return lfbLocked; };


	void					Vid_BeginLfbAccess	();
	void					Vid_EndLfbAccess	();

	void					Vid_Clear			(zCOLOR &col, int clearTarget = (zRND_CLEAR_FRAMEBUFFER | zRND_CLEAR_ZBUFFER));
	void					Vid_Blit			(int xofs=0, int yofs=0);		// frontBuffer/backBuffer flipping

	void					Vid_BlitRect		(zBYTE *src, int width, int height, int xd, int yd,int alpha);
	void					Vid_SetLfbAlpha		(int opacity)										{ grLfbConstantAlpha(opacity); }
	void					Vid_SetLfbAlphaFunc	(const zTRnd_AlphaBlendFunc &func);
	void					Vid_SetGammaCorrection(float value) ; // input [0..20] - default 1
	float					Vid_GetGammaCorrection()												{ return gamma; }

	zBOOL					Vid_ScreenDump		(const zSTRING &fileName);

	// Draw Primitives
	void					SetPixel			(float x,float y,const zCOLOR col);

	void					DrawLine			(float x1,float y1,float x2,float y2,const zCOLOR col);
	void					DrawLineZ			(float x1Scr, float y1Scr, float z1CamSpaceInv, 
												float x2Scr, float y2Scr, float z2CamSpaceInv, const zCOLOR col) ;

	// texture related
	zCTexture*				CreateTexture		();
	zCTextureConvert*		CreateTextureConvert()													{ return(zNEW( zCTexConGeneric ));}

	int						GetTotalTextureMem  ()													{ return zCTex_RndGlide :: GetTotalTexMemHw() ;}; 

	void					SetRenderMode		(const zTRnd_RenderMode rmode);
	zTRnd_RenderMode		GetRenderMode		() const;
	int						HasCapability		(const zTRnd_Capability) const;
	void					DrawLightmapList	(zCPolygon** polyList, int numPoly);

	// misc

	void					GetStatistics		(zTRnd_Stats &stat);
	void					ResetStatistics		();

	void					ResetZTest			();
	int						HasPassedZTest		();
	zBOOL					GetPixelWriteEnabled() const											{ return pixelWriteEn; };
	void					SetPixelWriteEnabled(const zBOOL b)										{ pixelWriteEn = b; grColorMask(pixelWriteEn,FXFALSE); };// Enable Colors w/o alpha

	zBOOL					SupportsTextureFormat(const zTRnd_TextureFormat texFormat); 
	int						GetMaxTextureSize	 ()													{ return 256;  };

	// spacer / internal use in Vid_Blit
	void					GetRect				(zBYTE *dest, int width, int height, int pitch, int xd, int yd);


private:

	typedef struct SCapability
	{
		int	  numTexPerPass;
		int	  totalFrameBufferMem;
		int	  totalTextureMem;
		zBOOL alphaBlendMulAvail;
		zBOOL alphaBlendAddAvail;
		zBOOL chromaAvail;
		zBOOL lfbAlphaBlendAvail;
		zBOOL lfbChromaAvail;
	} TCapability;
	
	TCapability			 cap;
    GrHwConfiguration	 hwconfig;
	GrScreenResolution_t fullRes;
	GrScreenResolution_t actRes;
	float				 gamma;
	zBOOL				 rushBased;
	zBOOL				 fullScreenOnly;
	GrFog_t				 fog[GR_FOG_TABLE_SIZE];
	GrState				 lfbState;
	GrVertex			 p[4];					   // temporary primitive 2d-vertex struct
	GrVertex			 v[zMAX_POLY_CLIP_VERTS];  // temporary vertex-struct req. by glide
	GrLfbInfo_t			 frameBuf;
	zBYTE*				 colorBuf;
	zBOOL				 lfbLocked;
	float				 nearZ;
	float				 farZ;
	zTRnd_FogMode		 fogType;
	zTRnd_ScreenMode	 scrMode;
	zBOOL				 fogEnabled;
	zCOLOR				 fogColor;
	zBOOL				 waitRetrace;
	zBOOL				 writeZBuffer;
	zDWORD				 maxTimeDefragPartial;
	zREAL				 zBias;
	zTRnd_ZBufferCmp	 zBufCompareFunc;
	zBOOL				 lightMapBilerpFilter;
	zBOOL				 bilerpFilter;
	zBOOL				 wrapEnabled;
	zTRnd_Stats			 zTestStat;
	zBOOL				 pixelWriteEn;
	int					 polysRendered;
	int					 trisRendered;
	int					 lightMapsRendered;
	zTRnd_DeviceInfo	 deviceInfo;

	void					GetFrameProfileValues	(void)												{	maxTimeDefragPartial = 1000; }	// evaluated ~ 2fps 
	zBOOL					CreateWin				(const int x, const int y, const int bpp);
	void					CloseWin				();
	void					(*PolyDrawFunc)			(zCPolygon *poly);

	zBOOL					SetMode				(int x,int y,int bpp);

};


extern "C" {

extern int  LoadGlideSymbols(void);
extern void FreeGlideSymbols(void);

};

#endif
