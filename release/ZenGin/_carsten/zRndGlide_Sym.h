/********************************************************************************
*
* File          : zRndGlide_Sym.h 
* Projekt       : Phoenix
* Autor         : Carsten Edenfeld
* Version       : 0.0
* last modified : 20.02.98
* erstellt      : 19.02.98										
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
*********************************************************************************/

#ifndef __GLSYMBOLS_H__
#define __GLSYMBOLS_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef IMPORTS_C
#define DECL_TEMP
#define CALL_TEMP
#else
#define DECL_TEMP extern
#define CALL_TEMP __stdcall
#endif

typedef void   (CALL_TEMP *GrErrorCallbackFnc_t)( const char *string, FxBool fatal );

DECL_TEMP void (CALL_TEMP *grDrawLine) ( const GrVertex *v1, const GrVertex *v2 );
DECL_TEMP void (CALL_TEMP *grDrawPlanarPolygon)( int nverts, const int ilist[], const GrVertex vlist[] );
DECL_TEMP void (CALL_TEMP *grDrawPlanarPolygonVertexList)( int nverts, const GrVertex vlist[] );
DECL_TEMP void (CALL_TEMP *grDrawPoint)( const GrVertex *pt );
DECL_TEMP void (CALL_TEMP *grDrawPolygon)( int nverts, const int ilist[], const GrVertex vlist[] );
DECL_TEMP void (CALL_TEMP *grDrawPolygonVertexList)( int nverts, const GrVertex vlist[] );
DECL_TEMP void (CALL_TEMP *grDrawTriangle)( const GrVertex *a, const GrVertex *b, const GrVertex *c );
DECL_TEMP void (CALL_TEMP *grBufferClear)( GrColor_t color, GrAlpha_t alpha, FxU16 depth );
DECL_TEMP int  (CALL_TEMP *grBufferNumPending)( void );
DECL_TEMP void (CALL_TEMP *grBufferSwap)( int swap_interval );
DECL_TEMP void (CALL_TEMP *grRenderBuffer)( GrBuffer_t buffer );
DECL_TEMP void (CALL_TEMP *grErrorSetCallback)( GrErrorCallbackFnc_t fnc );
DECL_TEMP void (CALL_TEMP *grSstIdle)(void);
DECL_TEMP FxU32  (CALL_TEMP *grSstVideoLine)( void );
DECL_TEMP FxBool (CALL_TEMP *grSstVRetraceOn)( void );
DECL_TEMP FxBool (CALL_TEMP *grSstIsBusy)( void );
DECL_TEMP FxBool (CALL_TEMP *grSstWinOpen)(FxU32 hWnd,GrScreenResolution_t screen_resolution,GrScreenRefresh_t refresh_rate,
							GrColorFormat_t color_format, GrOriginLocation_t origin_location, int nColBuffers,
							int nAuxBuffers);
DECL_TEMP void		(CALL_TEMP *grSstWinClose)( void );
DECL_TEMP FxBool	(CALL_TEMP *grSstControl)( FxU32 code );
DECL_TEMP FxBool	(CALL_TEMP *grSstQueryHardware)( GrHwConfiguration *hwconfig );
DECL_TEMP FxBool	(CALL_TEMP *grSstQueryBoards)( GrHwConfiguration *hwconfig );
DECL_TEMP void		(CALL_TEMP *grSstOrigin)(GrOriginLocation_t  origin);
DECL_TEMP void		(CALL_TEMP *grSstSelect)( int which_sst );
DECL_TEMP FxU32		(CALL_TEMP *grSstScreenHeight)( void );
DECL_TEMP FxU32		(CALL_TEMP *grSstScreenWidth)( void );
DECL_TEMP FxU32		(CALL_TEMP *grSstStatus)( void );
DECL_TEMP void		(CALL_TEMP *grSstPerfStats)(GrSstPerfStats_t *pStats);
DECL_TEMP void		(CALL_TEMP *grSstResetPerfStats)(void);
DECL_TEMP void		(CALL_TEMP *grResetTriStats)();
DECL_TEMP void		(CALL_TEMP *grTriStats)(FxU32 *trisProcessed, FxU32 *trisDrawn);
DECL_TEMP void		(CALL_TEMP *grAlphaBlendFunction)(
                     GrAlphaBlendFnc_t rgb_sf,   GrAlphaBlendFnc_t rgb_df,
                     GrAlphaBlendFnc_t alpha_sf, GrAlphaBlendFnc_t alpha_df);
DECL_TEMP void  (CALL_TEMP *grAlphaCombine)(
               GrCombineFunction_t function, GrCombineFactor_t factor,
               GrCombineLocal_t local, GrCombineOther_t other,
               FxBool invert);
DECL_TEMP void  (CALL_TEMP *grAlphaControlsITRGBLighting)( FxBool enable );
DECL_TEMP void  (CALL_TEMP *grAlphaTestFunction)( GrCmpFnc_t function );
DECL_TEMP void  (CALL_TEMP *grAlphaTestReferenceValue)( GrAlpha_t value );
DECL_TEMP void  (CALL_TEMP *grChromakeyMode)( GrChromakeyMode_t mode );
DECL_TEMP void  (CALL_TEMP *grChromakeyValue)( GrColor_t value );
DECL_TEMP void  (CALL_TEMP *grClipWindow)( FxU32 minx, FxU32 miny, FxU32 maxx, FxU32 maxy );
DECL_TEMP void  (CALL_TEMP *grColorCombine)(
               GrCombineFunction_t function, GrCombineFactor_t factor,
               GrCombineLocal_t local, GrCombineOther_t other,
               FxBool invert );
DECL_TEMP void  (CALL_TEMP *grColorMask)( FxBool rgb, FxBool a );
DECL_TEMP void  (CALL_TEMP *grCullMode)( GrCullMode_t mode );
DECL_TEMP void  (CALL_TEMP *grConstantColorValue)( GrColor_t value );
DECL_TEMP void  (CALL_TEMP *grConstantColorValue4)( float a, float r, float g, float b );
DECL_TEMP void  (CALL_TEMP *grDepthBiasLevel)( FxI16 level );
DECL_TEMP void  (CALL_TEMP *grDepthBufferFunction)( GrCmpFnc_t function );
DECL_TEMP void  (CALL_TEMP *grDepthBufferMode)( GrDepthBufferMode_t mode );
DECL_TEMP void  (CALL_TEMP *grDepthMask)( FxBool mask );
DECL_TEMP void  (CALL_TEMP *grDisableAllEffects)( void );
DECL_TEMP void  (CALL_TEMP *grDitherMode)( GrDitherMode_t mode );
DECL_TEMP void  (CALL_TEMP *grFogColorValue)( GrColor_t fogcolor );
DECL_TEMP void  (CALL_TEMP *grFogMode)( GrFogMode_t mode );
DECL_TEMP void  (CALL_TEMP *grFogTable)( const GrFog_t ft[GR_FOG_TABLE_SIZE] );
DECL_TEMP void  (CALL_TEMP *grGammaCorrectionValue)( float value );
DECL_TEMP void  (CALL_TEMP *grSplash)(float x, float y, float width, float height, FxU32 frame);
DECL_TEMP FxU32  (CALL_TEMP *grTexCalcMemRequired)(GrLOD_t lodmin, GrLOD_t lodmax,GrAspectRatio_t aspect, GrTextureFormat_t fmt);
DECL_TEMP FxU32  (CALL_TEMP *grTexTextureMemRequired)( FxU32     evenOdd,     GrTexInfo *info   );
DECL_TEMP FxU32  (CALL_TEMP *grTexMinAddress)( GrChipID_t tmu );
DECL_TEMP FxU32  (CALL_TEMP *grTexMaxAddress)( GrChipID_t tmu );
DECL_TEMP void  (CALL_TEMP *grTexNCCTable)( GrChipID_t tmu, GrNCCTable_t table );
DECL_TEMP void  (CALL_TEMP *grTexSource)( GrChipID_t tmu, FxU32      startAddress, FxU32      evenOdd, GrTexInfo  *info );
DECL_TEMP void  (CALL_TEMP *grTexClampMode)(GrChipID_t tmu, GrTextureClampMode_t s_clampmode, GrTextureClampMode_t t_clampmode);
DECL_TEMP void  (CALL_TEMP *grTexCombine)(GrChipID_t tmu,GrCombineFunction_t rgb_function,GrCombineFactor_t rgb_factor, 
					GrCombineFunction_t alpha_function,GrCombineFactor_t alpha_factor,FxBool rgb_invert,
					FxBool alpha_invert);
DECL_TEMP void  (CALL_TEMP *grTexCombineFunction)(GrChipID_t tmu,GrTextureCombineFnc_t fnc);
DECL_TEMP void  (CALL_TEMP *grTexDetailControl)(GrChipID_t tmu,int lod_bias,FxU8 detail_scale,float detail_max);
DECL_TEMP void  (CALL_TEMP *grTexFilterMode)(GrChipID_t tmu,GrTextureFilterMode_t minfilter_mode,GrTextureFilterMode_t magfilter_mode);
DECL_TEMP void  (CALL_TEMP *grTexLodBiasValue)(GrChipID_t tmu, float bias );
DECL_TEMP void  (CALL_TEMP *grTexDownloadMipMap)( GrChipID_t tmu,FxU32      startAddress,FxU32      evenOdd,GrTexInfo  *info );
DECL_TEMP void  (CALL_TEMP *grTexDownloadMipMapLevel)( GrChipID_t        tmu,
                          FxU32             startAddress,
                          GrLOD_t           thisLod,
                          GrLOD_t           largeLod,
                          GrAspectRatio_t   aspectRatio,
                          GrTextureFormat_t format,
                          FxU32             evenOdd,
                          void              *data );
DECL_TEMP void  (CALL_TEMP *grTexDownloadMipMapLevelPartial)( GrChipID_t        tmu,
                                 FxU32             startAddress,
                                 GrLOD_t           thisLod,
                                 GrLOD_t           largeLod,
                                 GrAspectRatio_t   aspectRatio,
                                 GrTextureFormat_t format,
                                 FxU32             evenOdd,
                                 void              *data,
                                 int               start,
                                 int               end );

DECL_TEMP void  (CALL_TEMP *ConvertAndDownloadRle)( GrChipID_t        tmu,
                        FxU32             startAddress,
                        GrLOD_t           thisLod,
                        GrLOD_t           largeLod,
                        GrAspectRatio_t   aspectRatio,
                        GrTextureFormat_t format,
                        FxU32             evenOdd,
                        FxU8              *bm_data,
                        long              bm_h,
                        FxU32             u0,
                        FxU32             v0,
                        FxU32             width,
                        FxU32             height,
                        FxU32             dest_width,
                        FxU32             dest_height,
                        FxU16             *tlut);

DECL_TEMP void  (CALL_TEMP *grCheckForRoom)(FxI32 n);

DECL_TEMP void  (CALL_TEMP *grTexDownloadTable)( GrChipID_t   tmu,
                    GrTexTable_t type, 
                    void         *data );

DECL_TEMP void  (CALL_TEMP *grTexDownloadTablePartial)( GrChipID_t   tmu,
                           GrTexTable_t type, 
                           void         *data,
                           int          start,
                           int          end );

DECL_TEMP void  (CALL_TEMP *grTexMipMapMode)( GrChipID_t     tmu, 
                 GrMipMapMode_t mode,
                 FxBool         lodBlend );

DECL_TEMP void  (CALL_TEMP *grTexMultibase)( GrChipID_t tmu,
                FxBool     enable );

DECL_TEMP void  (CALL_TEMP *grTexMultibaseAddress)( GrChipID_t       tmu,
                       GrTexBaseRange_t range,
                       FxU32            startAddress,
                       FxU32            evenOdd,
                       GrTexInfo        *info );

DECL_TEMP GrMipMapId_t  (CALL_TEMP *guTexAllocateMemory)(
                    GrChipID_t tmu,
                    FxU8 odd_even_mask,
                    int width, int height,
                    GrTextureFormat_t fmt,
                    GrMipMapMode_t mm_mode,
                    GrLOD_t smallest_lod, GrLOD_t largest_lod,
                    GrAspectRatio_t aspect,
                    GrTextureClampMode_t s_clamp_mode,
                    GrTextureClampMode_t t_clamp_mode,
                    GrTextureFilterMode_t minfilter_mode,
                    GrTextureFilterMode_t magfilter_mode,
                    float lod_bias,
                    FxBool trilinear
                    );

DECL_TEMP FxBool  (CALL_TEMP *guTexChangeAttributes)(
                      GrMipMapId_t mmid,
                      int width, int height,
                      GrTextureFormat_t fmt,
                      GrMipMapMode_t mm_mode,
                      GrLOD_t smallest_lod, GrLOD_t largest_lod,
                      GrAspectRatio_t aspect,
                      GrTextureClampMode_t s_clamp_mode,
                      GrTextureClampMode_t t_clamp_mode,
                      GrTextureFilterMode_t minFilterMode,
                      GrTextureFilterMode_t magFilterMode
                      );

DECL_TEMP void  (CALL_TEMP *guTexCombineFunction)(
                     GrChipID_t tmu,
                     GrTextureCombineFnc_t fnc
                     );

DECL_TEMP GrMipMapId_t  (CALL_TEMP *guTexGetCurrentMipMap)( GrChipID_t tmu );

DECL_TEMP GrMipMapInfo  * (CALL_TEMP *guTexGetMipMapInfo)( GrMipMapId_t mmid );

DECL_TEMP FxU32  (CALL_TEMP *guTexMemQueryAvail)( GrChipID_t tmu );

DECL_TEMP void  (CALL_TEMP *guTexMemReset)( void );

DECL_TEMP void  (CALL_TEMP *guTexDownloadMipMap)(
                    GrMipMapId_t mmid,
                    const void *src,
                    const GuNccTable *table
                    );

DECL_TEMP void  (CALL_TEMP *guTexDownloadMipMapLevel)(
                         GrMipMapId_t mmid,
                         GrLOD_t lod,
                         const void **src
                         );
DECL_TEMP void  (CALL_TEMP *guTexSource)( GrMipMapId_t id );

DECL_TEMP FxBool  (CALL_TEMP *grLfbLock)( GrLock_t type, GrBuffer_t buffer, GrLfbWriteMode_t writeMode,
           GrOriginLocation_t origin, FxBool pixelPipeline, 
           GrLfbInfo_t *info );
DECL_TEMP FxBool  (CALL_TEMP *grLfbUnlock)( GrLock_t type, GrBuffer_t buffer );
DECL_TEMP void  (CALL_TEMP *grLfbConstantAlpha)( GrAlpha_t alpha );
DECL_TEMP void  (CALL_TEMP *grLfbConstantDepth)( FxU16 depth );
DECL_TEMP void  (CALL_TEMP *grLfbWriteColorSwizzle)(FxBool swizzleBytes, FxBool swapWords);
DECL_TEMP void  (CALL_TEMP *grLfbWriteColorFormat)(GrColorFormat_t colorFormat);
DECL_TEMP FxBool  (CALL_TEMP *grLfbWriteRegion)( GrBuffer_t dst_buffer, 
                  FxU32 dst_x, FxU32 dst_y, 
                  GrLfbSrcFmt_t src_format, 
                  FxU32 src_width, FxU32 src_height, 
                  FxI32 src_stride, void *src_data );
DECL_TEMP FxBool  (CALL_TEMP *grLfbReadRegion)( GrBuffer_t src_buffer,
                 FxU32 src_x, FxU32 src_y,
                 FxU32 src_width, FxU32 src_height,
                 FxU32 dst_stride, void *dst_data );
DECL_TEMP void  (CALL_TEMP *grAADrawLine)(const GrVertex *v1, const GrVertex *v2);
DECL_TEMP void  (CALL_TEMP *grAADrawPoint)(const GrVertex *pt );
DECL_TEMP void  (CALL_TEMP *grAADrawPolygon)(const int nverts, const int ilist[], const GrVertex vlist[]);
DECL_TEMP void  (CALL_TEMP *grAADrawPolygonVertexList)(const int nverts, const GrVertex vlist[]);
DECL_TEMP void  (CALL_TEMP *grAADrawTriangle)(
                 const GrVertex *a, const GrVertex *b, const GrVertex *c,
                 FxBool ab_antialias, FxBool bc_antialias, FxBool ca_antialias
                 );
DECL_TEMP void  (CALL_TEMP *grGlideInit)( void );
DECL_TEMP void  (CALL_TEMP *grGlideShutdown)( void );
DECL_TEMP void  (CALL_TEMP *grGlideGetVersion)( char version[80] );
DECL_TEMP void  (CALL_TEMP *grGlideGetState)( GrState *state );
DECL_TEMP void  (CALL_TEMP *grGlideSetState)( const GrState *state );
DECL_TEMP void  (CALL_TEMP *grGlideShamelessPlug)(const FxBool on);
DECL_TEMP void  (CALL_TEMP *grHints)(GrHint_t hintType, FxU32 hintMask);
DECL_TEMP void  (CALL_TEMP *guAADrawTriangleWithClip)( const GrVertex *a, const GrVertex *b, const GrVertex *c);
DECL_TEMP void  (CALL_TEMP *guDrawTriangleWithClip)(const GrVertex *a,const GrVertex *b,const GrVertex *c);
DECL_TEMP void  (CALL_TEMP *guDrawPolygonVertexListWithClip)( int nverts, const GrVertex vlist[] );
DECL_TEMP void  (CALL_TEMP *guAlphaSource)( GrAlphaSource_t mode );
DECL_TEMP void  (CALL_TEMP *guColorCombineFunction)( GrColorCombineFnc_t fnc );
DECL_TEMP int  (CALL_TEMP *guEncodeRLE16)( void *dst, void *src, FxU32 width, FxU32 height );
DECL_TEMP FxU16  *(CALL_TEMP *guTexCreateColorMipMap)( void );
DECL_TEMP void  (CALL_TEMP *guMovieStart)( void );
DECL_TEMP void  (CALL_TEMP *guMovieStop)( void );
DECL_TEMP void  (CALL_TEMP *guMovieSetName)( const char *name );
DECL_TEMP float  (CALL_TEMP *guFogTableIndexToW)( int i );
DECL_TEMP void  (CALL_TEMP *guFogGenerateExp)( GrFog_t fogtable[GR_FOG_TABLE_SIZE], float density );
DECL_TEMP void  (CALL_TEMP *guFogGenerateExp2)( GrFog_t fogtable[GR_FOG_TABLE_SIZE], float density );
DECL_TEMP void  (CALL_TEMP *guFogGenerateLinear)(GrFog_t fogtable[GR_FOG_TABLE_SIZE],float nearZ, float farZ );
DECL_TEMP FxU32  (CALL_TEMP *guEndianSwapWords)( FxU32 value );
DECL_TEMP FxU16  (CALL_TEMP *guEndianSwapBytes)( FxU16 value );
DECL_TEMP FxBool  (CALL_TEMP *gu3dfGetInfo)( const char *filename, Gu3dfInfo *info );
DECL_TEMP FxBool  (CALL_TEMP *gu3dfLoad)( const char *filename, Gu3dfInfo *data );



#undef DECL_TEMP
#undef CALL_TEMP 

#ifdef __cplusplus
};
#endif
#endif