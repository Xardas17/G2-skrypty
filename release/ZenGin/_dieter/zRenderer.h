/******************************************************************************** 
 
     $Workfile:: zRenderer.h          $                $Date:: 14.02.01 7:28    $
     $Revision:: 34                   $             $Modtime:: 14.02.01 4:13    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Rendering Hardware Abstraction Layer (low/mid/hi-Level)
   created       : 3.12.97

 * $Log: /current_work/zengin_work/_Dieter/zRenderer.h $
 * 
 * 34    14.02.01 7:28 Hildebrandt
 * 
 * 33    27.01.01 19:04 Pelzer
 * 
 * 32    4.12.00 17:38 Hildebrandt
 * 
 * 31    22.11.00 4:06 Hildebrandt
 * 
 * 30    15.11.00 17:36 Hildebrandt
 * 
 * 29    13.11.00 21:56 Hildebrandt
 * 
 * 28    7.11.00 15:03 Hildebrandt
 * 
 * 27    19.10.00 20:06 Hildebrandt
 * 
 * 25    19.10.00 16:27 Pelzer
 * 
 * 24    17.10.00 21:21 Pelzer
 * 
 * 23    17.10.00 14:42 Pelzer
 * 
 * 22    16.10.00 22:27 Pelzer
 * 
 * 21    11.10.00 19:45 Hildebrandt
 * 
 * 20    5.10.00 18:44 Hildebrandt
 * 
 * 19    5.10.00 16:10 Hildebrandt
 * 
 * 18    4.10.00 22:48 Hildebrandt
 * 
 * 17    4.10.00 17:16 Hildebrandt
 * 
 * 16    29.09.00 16:19 Hildebrandt
 * 
 * 15    28.09.00 19:18 Hildebrandt
 * 
 * 14    22.09.00 20:14 Hildebrandt
 * 
 * 13    21.09.00 15:57 Hildebrandt
 * 
 * 12    21.09.00 15:48 Pelzer
 * 
 * 11    20.09.00 16:12 Hildebrandt
 * 
 * 10    1.09.00 19:53 Hildebrandt
 * 
 * 9     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 8     21.07.00 14:28 Hildebrandt
 * 
 * 7     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 6     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 4     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 34 $ ($Modtime: 14.02.01 4:13 $)


#ifndef __ZRENDERER_H__
#define __ZRENDERER_H__

// ======================================================================================================================

#ifndef __ZTYPES_H__
#include <ztypes.h>
#endif

#ifndef __ZSTRING_H__
#include <zstring.h>
#endif

#ifndef __ZTYPES3D_H__
#include <ztypes3d.h>
#endif



// ======================================================================================================================
// common definition
const int DEFAULT_LEVEL_ZBIAS	=	0;
const int DEFAULT_VOB_ZBIAS		=   1;

// ======================================================================================================================
// forward declarations 

class	zCPolygon;
class	zCTexture;
struct	zCOLOR;
class	zVEC3;
class	zCTextureConvert;
class	zCShader;
class	zCVertexBuffer;
class	zCRenderLight;

// ======================================================================================================================
// common enums

enum zTRnd_PolySortMode		{	zRND_SORT_NONE, 
								zRND_SORT_ZBUFFER
							};
enum zTRnd_ZBufferCmp		{	zRND_ZBUFFER_CMP_ALWAYS, 
								zRND_ZBUFFER_CMP_NEVER, 
								zRND_ZBUFFER_CMP_LESS,
								zRND_ZBUFFER_CMP_LESS_EQUAL,
							};
enum zTRnd_PolyDrawMode		{	zRND_DRAW_MATERIAL, 
								zRND_DRAW_MATERIAL_WIRE,
								zRND_DRAW_FLAT, 
								zRND_DRAW_WIRE,
							}; 
enum zTRnd_FogMode			{	zRND_FOG_FALLOFF_LINEAR };
enum zTRnd_AlphaBlendSource {	zRND_ALPHA_SOURCE_MATERIAL, 
								zRND_ALPHA_SOURCE_CONSTANT 
							}; 
enum zTRnd_AlphaBlendFunc	{	zRND_ALPHA_FUNC_MAT_DEFAULT,			// default
								zRND_ALPHA_FUNC_NONE,					// force/override (when set by rnd-interf)
								zRND_ALPHA_FUNC_BLEND,					// "
								zRND_ALPHA_FUNC_ADD,					
								zRND_ALPHA_FUNC_SUB,					
								zRND_ALPHA_FUNC_MUL,					
								zRND_ALPHA_FUNC_MUL2,					
								zRND_ALPHA_FUNC_TEST,					// Alphatesting [PELZER]
								zRND_ALPHA_FUNC_BLEND_TEST				// Alphatesting + Blending [PELZER]
							};	 										
enum zTRnd_Capability		{	zRND_CAP_GUARD_BAND,					// zBOOL
								zRND_CAP_ALPHATEST,						// zBOOL
								zRND_CAP_MAX_BLEND_STAGES,				// int,		how many stages are available
								zRND_CAP_MAX_BLEND_STAGE_TEXTURES,		// int,		how many textures are allowed in these stages
								zRND_CAP_DIFFUSE_LAST_BLEND_STAGE_ONLY,	// zBOOL,	limitations/defects of some 3Dhardware
								zRND_CAP_TNL,							// zBOOL
								zRND_CAP_TNL_HARDWARE,					// zBOOL
								zRND_CAP_TNL_MAXLIGHTS,					// int
								zRND_CAP_DEPTH_BUFFER_PREC,				// int,		(ZBuffer= 16,24,32, WBuffer= -16,-24,-32)
								zRND_CAP_BLENDDIFFUSEALPHA,				// zBOOL
							};
enum zTRnd_RenderMode		{	zRND_MODE_1_PASS_VERT_LIGHT,
								zRND_MODE_1_PASS_MULTITEXTURE,
								zRND_MODE_2_PASS_TEXTURE,				// polys: no rgb shading
								zRND_MODE_2_PASS_LIGHTMAP,				// polys: rgb shading
								zRND_MODE_DYN_POLYS_VERT_LIGHT
							};
enum zTRnd_ScreenMode		{	zRND_SCRMODE_FULLSCREEN,
								zRND_SCRMODE_WINDOWED,
								zRND_SCRMODE_HIDE 
							};
enum zTRnd_ClearTarget		{	zRND_CLEAR_FRAMEBUFFER	= 1,			// for: Vid_Clear()
								zRND_CLEAR_ZBUFFER		= 2,
								zRND_CLEAR_ALL			= (zRND_CLEAR_FRAMEBUFFER | zRND_CLEAR_ZBUFFER)
							};
enum zTRnd_RenderStateType	{
								zRND_RENDERSTATE_CLIPPING		=0,		// zBOOL
								zRND_RENDERSTATE_TEXTUREFACTOR	,		// zCOLOR

								zRND_RENDERSTATE_COUNT			,
							};	
enum zTRnd_TextureFormat	{	
								// this list has to be kept in sync with 'texFormatInfoList' in zRenderer.cpp
								// 24,32 bit [intel] bytes found in memory: ARGB=> A(0), R(1), G(2), B(2), left to right
								zRND_TEX_FORMAT_ARGB_8888,				// 32, alpha 8
								zRND_TEX_FORMAT_ABGR_8888,				// 32, alpha 8
								zRND_TEX_FORMAT_RGBA_8888,				// 32, alpha 8
								zRND_TEX_FORMAT_BGRA_8888,				// 32, alpha 8

								zRND_TEX_FORMAT_RGB_888,				// 24
								zRND_TEX_FORMAT_BGR_888,				// 24

								// 16 bit [intel] bits found in memory: ARGB=> B(0), G(4), R(8), A(12), right to left
								zRND_TEX_FORMAT_ARGB_4444,				// 16, alpha 4
								zRND_TEX_FORMAT_ARGB_1555,				//	 , alpha 1
								zRND_TEX_FORMAT_RGB_565,				

								// palettized
								zRND_TEX_FORMAT_PAL_8,					// 8

								// compressed
								zRND_TEX_FORMAT_DXT1,					// 4,	opaque or 1bit alpha 
								zRND_TEX_FORMAT_DXT2,					// 8,	explicit alpha,	alpha-premul: yes
								zRND_TEX_FORMAT_DXT3,					// 8,	explicit alpha,	alpha-premul: no
								zRND_TEX_FORMAT_DXT4,					// 8,	lerped   alpha,	alpha-premul: yes
								zRND_TEX_FORMAT_DXT5,					// 8,	lerped   alpha,	alpha-premul: no

								//
								zRND_TEX_FORMAT_COUNT
							};

// ======================================================================================================================
// Texture Stages

enum zTRnd_TextureStageState
{
    zRND_TSS_COLOROP					= 0,	// => zTRnd_TextureStageOp
    zRND_TSS_COLORARG1					,		// => zTRnd_TextureStageArg
    zRND_TSS_COLORARG2					,		// => zTRnd_TextureStageArg
    zRND_TSS_ALPHAOP					,		// => zTRnd_TextureStageOp
    zRND_TSS_ALPHAARG1					,		// => zTRnd_TextureStageArg
    zRND_TSS_ALPHAARG2					,		// => zTRnd_TextureStageArg
    zRND_TSS_BUMPENVMAT00				,		// not currently used
    zRND_TSS_BUMPENVMAT01				,		// not currently used
    zRND_TSS_BUMPENVMAT10				,		// not currently used
    zRND_TSS_BUMPENVMAT11				,		// not currently used
    zRND_TSS_TEXCOORDINDEX				,		// => zTRnd_TextureStageTexCoord
    zRND_TSS_ADDRESS					,		// not currently used
    zRND_TSS_ADDRESSU					,		// not currently used
    zRND_TSS_ADDRESSV					,		// not currently used
    zRND_TSS_BORDERCOLOR				,		// not currently used
    zRND_TSS_MAGFILTER					,		// not currently used
    zRND_TSS_MINFILTER					,		// not currently used
    zRND_TSS_MIPFILTER					,		// not currently used
    zRND_TSS_MIPMAPLODBIAS				,		// not currently used
    zRND_TSS_MAXMIPLEVEL				,		// not currently used
    zRND_TSS_MAXANISOTROPY				,		// not currently used
    zRND_TSS_BUMPENVLSCALE				,		// not currently used
    zRND_TSS_BUMPENVLOFFSET				,		// not currently used
    zRND_TSS_TEXTURETRANSFORMFLAGS		,		// => zTRnd_TextureStageTexTransformFlags

	zRND_TSS_COUNT						,
};

enum zTRnd_TextureStageOp
{
	zRND_TOP_DISABLE					= 0,  
	zRND_TOP_SELECTARG1					,  
	zRND_TOP_SELECTARG2					,  
	zRND_TOP_MODULATE					,  
	zRND_TOP_MODULATE2X					,  
	zRND_TOP_MODULATE4X					,		// not currently used  
	zRND_TOP_ADD						,  
	zRND_TOP_ADDSIGNED					,		// not currently used
	zRND_TOP_ADDSIGNED2X				,		// not currently used
	zRND_TOP_SUBTRACT					,		// not currently used
	zRND_TOP_ADDSMOOTH					,		// not currently used
	zRND_TOP_BLENDDIFFUSEALPHA			,	
	zRND_TOP_BLENDTEXTUREALPHA			,  
	zRND_TOP_BLENDFACTORALPHA			,  
	zRND_TOP_BLENDTEXTUREALPHAPM		,  
	zRND_TOP_BLENDCURRENTALPHA			,  
	zRND_TOP_PREMODULATE				,		// not currently used
	zRND_TOP_MODULATEALPHA_ADDCOLOR		,		// not currently used
	zRND_TOP_MODULATECOLOR_ADDALPHA		,		// not currently used
	zRND_TOP_MODULATEINVALPHA_ADDCOLOR	,		// not currently used
	zRND_TOP_MODULATEINVCOLOR_ADDALPHA  ,		// not currently used
    zRND_TOP_BUMPENVMAP					,		// not currently used
    zRND_TOP_BUMPENVMAPLUMINANCE		,		// not currently used
    zRND_TOP_DOTPRODUCT3				,		// not currently used

	zRND_TOP_COUNT						,
};

enum zTRnd_TextureStageArg
{
	zRND_TA_CURRENT						= 0,	// The texture argument is the result of the previous blending stage. In the first texture stage (stage 0), this argument is equivalent to D3DTA_DIFFUSE. If the previous blending stage uses a bump-map texture (the D3DTOP_BUMPENVMAP operation), the system chooses the texture from the stage before the bump-map texture. (If s represents the current texture stage and s - 1 contains a bump-map texture, this argument becomes the result output by texture stage s - 2.)
	zRND_TA_DIFFUSE						,		// The texture argument is the diffuse color interpolated from vertex components during Gouraud shading. If the vertex does not contain a diffuse color, the default color is 0xFFFFFFFF.
	zRND_TA_SELECTMASK					,		// Mask value for all arguments; not used when setting texture arguments.
	zRND_TA_TEXTURE						,		// The texture argument is the texture color for this texture stage. This is valid only for the first color and alpha arguments in a stage (the D3DTSS_COLORARG1 and D3DTSS_ALPHAARG1 members of D3DTEXTURESTAGESTATETYPE).
	zRND_TA_TFACTOR						,		// The texture argument is the texture factor set in a previous call to the IDirect3DDevice7::SetRenderState with the D3DRENDERSTATE_TEXTUREFACTOR render-state value.
	zRND_TA_SPECULAR							// The texture argument is the specular color interpolated from vertex components during Gouraud shading. If the vertex does not contain a diffuse color, the default color is 0xFFFFFFFF.
};

enum zTRnd_TextureStageTexCoord
{
	zRND_TSS_TCI_PASSTHRU						= 0x00000000,
	zRND_TSS_TCI_CAMERASPACENORMAL				= 0x00010000,
	zRND_TSS_TCI_CAMERASPACEPOSITION			= 0x00020000,
	zRND_TSS_TCI_CAMERASPACEREFLECTIONVECTOR	= 0x00030000,
};

enum zTRnd_TextureStageTexTransformFlags
{
	zRND_TTF_DISABLE					= 0,   
    zRND_TTF_COUNT1						= 1,   
    zRND_TTF_COUNT2						= 2,   
    zRND_TTF_COUNT3						= 3,   
    zRND_TTF_COUNT4						= 4,   
//	zRND_TTF_PROJECTED					= 256,
};

// ======================================================================================================================
// Transform and Lighting

enum zTRnd_TrafoType 
{
	zRND_TRAFO_VIEW,
	zRND_TRAFO_PROJECTION,
	zRND_TRAFO_TEXTURE0,
	zRND_TRAFO_TEXTURE1,
	zRND_TRAFO_TEXTURE2,
	zRND_TRAFO_TEXTURE3,
};

enum zTRenderLightType
{
	zLIGHT_TYPE_POINT	= 1,
	zLIGHT_TYPE_SPOT	= 2,
	zLIGHT_TYPE_DIR		= 3,
	zLIGHT_TYPE_AMBIENT	= 4
};

class zCRenderLight {
public:
	// Light definition
	zTRenderLightType	lightType;            
	zVEC3				colorDiffuse;				// diffuse color
//	zVEC3				colorSpecular;				
//	zVEC3				colorAmbient;				
	zVEC3				position;					// spot, point		[WS]
	zVEC3				direction;					// spot, dir		[WS]
	zREAL				range;						
//	zREAL				falloff;					// spot
//	zREAL				attenuation0;				// spot, point
//	zREAL				attenuation1;				
//	zREAL				attenuation2;				
//	zREAL				theta;						// spot
//	zREAL				phi;						// spot
						
	// aux
	zREAL				rangeInv;
	zVEC3				positionLS;					// spot, point		[LightingSpace]
	zVEC3				directionLS;				// spot, dir		[LightingSpace]
	zREAL				dir_approxFalloff;			// dir		
//	zVEC3				dir_approxLightToObjLS;		// dir				[LS]
};

// ======================================================================================================================

class zCRndAlphaSortObject {
public:
			 zCRndAlphaSortObject() {};
	virtual ~zCRndAlphaSortObject() {};

	virtual void			Draw				(int currentIndex)=0;
	virtual zBOOL			IsAlphaPoly			() { return FALSE; };	// FIXME: hmmm... oder eben ein "dynamic_cast"
	void					SetZValue			(const zREAL zin)					{ zvalue = zin;					};
	zREAL					GetZValue			() const							{ return zvalue;				};
	void					SetNext				(zCRndAlphaSortObject* sortObject)	{ nextSortObject = sortObject;	};
	zCRndAlphaSortObject*	GetNext				() const							{ return nextSortObject;		};

protected:
	zCRndAlphaSortObject	*nextSortObject;	// wirklich noetig? nimmt Details der Sort-Impl. vorweg..
	zREAL					zvalue;
};

// ======================================================================================================================

struct zTRnd_TexFormatInfo {
	float		bytesPerPixel;
	int			rPos, gPos, bPos, aPos;						// bit-position of each color element
	int			rSize,gSize,bSize,aSize;					// bit-size of each color elememt
	// FIXME: special flags for pal8/compressed ?
};

struct zTRnd_DeviceInfo {
	zSTRING		deviceName;
};

struct zTRnd_VidModeInfo {
	int			xdim;
	int			ydim;
	int			bpp;
	zBOOL		fullscreenOnly;
};

// this struct reports statistics that are gathered since the last call to zCRenderer::ResetStatistics()
struct zTRnd_Stats	{	
	int			texMemUsed;			// total texture memory used for rendering [bytes]
	int			texMemFetched;		// texture memory uploaded from system memory to 3D-hardware memory [bytes]
	int			numTexturesFetched;	// total number of textures uploaded to 3D-hardware memory
	int			numTexturesUsed;	// total number of textures used for rendering (all textures are counted, base-textures, lightmaps,..)
	int			numLightmapsUsed;	// total number of lightmap textures used for rendering
				
	int			numPolysRendered;	// total number of polys rendered
	int			numTrisRendered;	// (this number is 'polysRendererd' broken down to triangles)

	int			numAlphaPolys;		// polys that go through DrawPoly() with alphaBlendFunc!=NONE
	int			numAlphaPolyBatches;// in many VB-Batches have they been rendered?
};

struct zTRndSimpleVertex {
	zVEC2	pos;
	zREAL	z;
	zVEC2	uv;
	zCOLOR	color;
};

struct zTRndSurfaceDesc {
	void*	pSurface;
	zDWORD	bytePitch ;
	zDWORD	pixelWidth;
	zDWORD	pixelHeight;
	zDWORD	bitRGBCount;
	zDWORD	bitRMask;
	zDWORD	bitGMask;
	zDWORD	bitBMask;
};

// ======================================================================================================================
// abstract base-class 

class zENGINE_API zCRenderer {
protected:
	zTRnd_PolySortMode				polySortMode;
	zTRnd_PolyDrawMode				polyDrawMode;

public:
	// "static"
	zTRnd_AlphaBlendFunc			AlphaBlendFuncStringToType	(const zSTRING& s) const;
	zSTRING							AlphaBlendFuncTypeToString	(const zTRnd_AlphaBlendFunc func) const;
	zTRnd_TexFormatInfo				GetTexFormatInfo			(const zTRnd_TextureFormat texFormat) const;
public:
	// Inits & Shutdowns
									zCRenderer			() {};
	virtual							~zCRenderer			() {};						

	// management
	virtual void					BeginFrame			()=0;
	virtual void					EndFrame			()=0;				// incl. FlushPolys()
	virtual void					FlushPolys			()=0;					
	
	// hi-level Rendering
	virtual void					DrawPoly			(zCPolygon* poly)=0;
	virtual void					DrawLightmapList	(zCPolygon** polyList, int numPoly)		{};
	virtual void					DrawLine			(float x1, float y1, float x2, float y2, const zCOLOR col)=0;
	virtual void					DrawLineZ			(float x1Scr, float y1Scr, float z1CamSpaceInv, 
														 float x2Scr, float y2Scr, float z2CamSpaceInv, const zCOLOR col) {};
	virtual void					SetPixel			(float x, float y, const zCOLOR col)=0;
 
	// draw tile
	void							DrawTile			(zCTexture		*texture,	// handles screen clipping tile-poly and texture-slicing
														 const zVEC2&	posMin,
														 const zVEC2&	posMax,
														 const zREAL	zValue,
														 const zVEC2&	uvMin,
														 const zVEC2&	uvMax,
														 const zCOLOR	color);
//	static void						DrawTile			(zCTexture	*texture, zTRndSimpleVertex *vertex); // handles screen clipping tile-poly and texture-slicing
	virtual void					DrawPolySimple		(zCTexture	*texture, zTRndSimpleVertex *vertex, int numVert) {};

	// set/get States
	virtual void					SetFog				(const zBOOL foggy)=0;
	virtual zBOOL					GetFog				() const				{ return FALSE;				};
	virtual void					SetRadialFog		(const zBOOL foggy)=0;
	virtual zBOOL					GetRadialFog		() const				{ return FALSE;				};

	virtual void					SetFogColor			(const zCOLOR& col)=0;
	virtual zCOLOR					GetFogColor			() const				{ zCOLOR col; col.SetRGBA(0,0,0,255); return col;	};
	virtual void					SetFogRange			(const float nearz, const float farz, const zTRnd_FogMode falloff=zRND_FOG_FALLOFF_LINEAR)=0;
	virtual void					GetFogRange			(float& nearz, float& farz, zTRnd_FogMode& falloff) {};

	virtual zTRnd_PolyDrawMode		GetPolyDrawMode		() const								{ return polyDrawMode;		};
	virtual void					SetPolyDrawMode		(const zTRnd_PolyDrawMode& drawMode)	{ polyDrawMode = drawMode;	};

	// surface loss
	virtual zBOOL					GetSurfaceLost		() const								{ return FALSE;				};
	virtual void					SetSurfaceLost		(const zBOOL b)							{ };

	// alternate render options
	virtual zBOOL					GetSyncOnAmbientCol () const								{ return FALSE;				};
	virtual void					SetSyncOnAmbientCol (const zBOOL b)							{ };


	virtual void					SetTextureWrapEnabled(const zBOOL b)						{ };
	virtual zBOOL					GetTextureWrapEnabled() const								{ return TRUE; };

	virtual void					SetBilerpFilterEnabled(const zBOOL b)=0;
	virtual zBOOL					GetBilerpFilterEnabled() const=0;

	virtual void					SetDitherEnabled	(const zBOOL b)							{ };
	virtual zBOOL					GetDitherEnabled	() const								{ return TRUE; };

	// sorting, zbuffering
	virtual zTRnd_PolySortMode		GetPolySortMode		() const								{ return polySortMode;		};
	virtual void					SetPolySortMode		(const zTRnd_PolySortMode& smode)		{ polySortMode = smode;		};
	virtual	zBOOL					GetZBufferWriteEnabled() const								{ return TRUE; };
	virtual	void					SetZBufferWriteEnabled(const zBOOL)							{};
	virtual void					SetZBias			(const int zBias)						{};
	virtual int						GetZBias			() const								{ return 0;	};
	virtual	zTRnd_ZBufferCmp		GetZBufferCompare	()										{ return zRND_ZBUFFER_CMP_LESS; };
	virtual	void					SetZBufferCompare	(const zTRnd_ZBufferCmp& zcmp)			{};
	virtual	zBOOL					GetPixelWriteEnabled() const								{ return TRUE; };
	virtual	void					SetPixelWriteEnabled(const zBOOL)							{};

	// alpha-blending
	virtual	void					SetAlphaBlendSource	(const zTRnd_AlphaBlendSource &src)		{};
	virtual	zTRnd_AlphaBlendSource	GetAlphaBlendSource	() const								{ return zRND_ALPHA_SOURCE_MATERIAL; };
	virtual	void					SetAlphaBlendFunc	(const zTRnd_AlphaBlendFunc &mode)		{};
	virtual	zTRnd_AlphaBlendFunc	GetAlphaBlendFunc	() const								{ return zRND_ALPHA_FUNC_MAT_DEFAULT;};
	virtual	float					GetAlphaBlendFactor	() const								{ return 1.0F; };
	virtual	void					SetAlphaBlendFactor	(const float &percentage)				{};	// only for zRND_ALPHA_SOURCE_CONSTANT
	virtual void					SetAlphaReference		(const DWORD a_alphaReference)		{ };
	virtual zDWORD					GetAlphaReference		()	const							{ return 0;	};

	virtual	zBOOL					GetCacheAlphaPolys	() const								{ return TRUE; };	// TRUE: renderer caches alpha-polys and renders them z-sorted at FlushPolys(), FALSE: alpha-Polys are rendered immediatel
	virtual	void					SetCacheAlphaPolys	(const zBOOL)							{};	
	virtual	zBOOL					GetAlphaLimitReached() const								{ return FALSE;	};

	virtual	void					AddAlphaPoly		(const zCPolygon* poly)					{};
	virtual void					FlushAlphaPolys		()										{};

	//
	virtual void					SetRenderMode		(const zTRnd_RenderMode rmode)			{};
	virtual zTRnd_RenderMode		GetRenderMode		() const								{ return zRND_MODE_1_PASS_VERT_LIGHT; };
	virtual int						HasCapability		(const zTRnd_Capability) const			{ return FALSE; };
	virtual void					GetGuardBandBorders	(float& guardBandLeft, float& guardBandTop, float& guardBandRight, float& guardBandBottom) {};
	virtual void					ResetZTest			()										{};
	virtual int						HasPassedZTest		()										{ return TRUE;	};

	//
	// Factory
	//
	virtual zCTexture*				CreateTexture		()=0;
	virtual zCTextureConvert*		CreateTextureConvert() { return 0;		};

	//
	// Texture
	//
	virtual int						GetTotalTextureMem	()=0;					// returns bytes
	virtual zBOOL					SupportsTextureFormat(const zTRnd_TextureFormat texFormat) { return FALSE; };			//texture support by renderer 
	virtual zBOOL					SupportsTextureFormatHardware(const zTRnd_TextureFormat texFormat) { return FALSE; };	//texture support by hardware
	virtual int						GetMaxTextureSize	() { return 256;	};

	//
	virtual void					GetStatistics		(zTRnd_Stats &stat) =0;
	virtual void					ResetStatistics		()=0;

	//
	// Video (low-level)
	// 

// FIXME: hier statt dessen 'zTRnd_TextureFormat' verwenden ??
	int		vid_xdim ,vid_ydim	,vid_bpp ,vid_pitch;		// Vmode extensions
	int		vid_rpos ,vid_gpos	,vid_bpos;					// Bit-position of each color element
	int		vid_rsize,vid_gsize	,vid_bsize;					// Bit-size of each color elememt

	// frameBuffer 
	virtual void					Vid_Blit				(zBOOL forceFlip=TRUE,  RECT *sourceRect=NULL, RECT *destRect=NULL)=0;		// frontBuffer/backBuffer flipping
	virtual void					Vid_Clear				(zCOLOR &col, int clearTarget = zRND_CLEAR_ALL)=0;	// clears buffers (framebuffer, zbuffer,..)			
	virtual zBOOL					Vid_Lock				(zTRndSurfaceDesc &surfdesc)=0;		// locks backbuffer
	virtual zBOOL					Vid_Unlock				()=0;								// unlocks backbuffer
	virtual zBOOL					Vid_IsLocked			()=0;								// backbuffer locked?
	virtual zBOOL					Vid_GetFrontBufferCopy	(zCTextureConvert &frontcopy)=0;

	// modes, devices
	virtual int						Vid_GetNumDevices		()=0;												// <=0 failed
	virtual int						Vid_GetActiveDeviceNr	()=0;												// gets active device
	virtual zBOOL					Vid_SetDevice			(int deviceNr)=0;									// sets active device
	virtual zBOOL					Vid_GetDeviceInfo		(zTRnd_DeviceInfo& deviceInfo, int deviceNr)=0;
	virtual int						Vid_GetNumModes			()=0;												// <=0 failed
	virtual zBOOL					Vid_GetModeInfo			(zTRnd_VidModeInfo& modeInfo, int modeNr)=0;
	virtual int						Vid_GetActiveModeNr		()=0;
	// winHandle: you can specify the window that should be rendered in, '0' uses current/active window on mode changes
	virtual zBOOL					Vid_SetMode				(int modeNr, zTSystemContextHandle* initContextHandle=0)=0;
			zBOOL					Vid_SetMode				(int newXDim, int newYDim, int newBpp, zTSystemContextHandle* initContextHandle=0); // convenience: searches modeList for best matching mode

	// fullscreen/windowed
	virtual void					Vid_SetScreenMode		(zTRnd_ScreenMode scrmode)=0;
	virtual zTRnd_ScreenMode		Vid_GetScreenMode		()=0;
								
	virtual void					Vid_SetGammaCorrection	(float gamma = 0.5f, float contrast = 0.5f, float brightness = 0.5f)=0; // all [0.1;0.9]
	virtual float					Vid_GetGammaCorrection  ()=0;
									
// Ebenfalls obsolete ?	
									
	// LFB							
	virtual void					Vid_BeginLfbAccess		()=0;
	virtual void					Vid_EndLfbAccess		()=0;
	virtual	void					Vid_SetLfbAlpha			(int opacity)=0;						// [0;255]
	virtual void					Vid_SetLfbAlphaFunc		(const zTRnd_AlphaBlendFunc &func)=0;

	// ===================================================================================================================

	// Transform and Lighting
	struct zTMaterial {
		zVEC4		diffuseRGBA;
		zVEC4		ambientRGBA;
	};
	virtual zBOOL					SetTransform			(zTRnd_TrafoType transformType, const zMAT4& matrix){ return FALSE; };
	virtual zBOOL					SetViewport				(int x0, int y0, int xdim, int ydim)				{ return FALSE; };
	virtual zBOOL					SetLight				(zDWORD lightIndex, zCRenderLight *light)			{ return FALSE; };// setting a light enables it, 'light==0' disables that lightSlot
	virtual zBOOL					GetMaterial				(zTMaterial &material)								{ return FALSE; };
	virtual zBOOL					SetMaterial				(const zTMaterial &material)						{ return FALSE; };
									
	// Multitexture Stages			
	virtual zBOOL					SetTexture				(zDWORD stage, zCTexture *texture)					 { return FALSE; };
	virtual zBOOL					SetTextureStageState	(zDWORD stage, zTRnd_TextureStageState state, zDWORD value)  { return FALSE; };
	virtual	zBOOL					SetAlphaBlendFuncImmed	(const zTRnd_AlphaBlendFunc afunc)					{ return FALSE; };

	// RenderStates
	virtual zBOOL					SetRenderState			(zTRnd_RenderStateType renderStateType, zDWORD renderState) { return FALSE; };
	virtual zDWORD					GetRenderState			(zTRnd_RenderStateType renderStateType)						{ return FALSE; };
	
	// Alpha Object Sorting
	virtual void					AddAlphaSortObject		(zCRndAlphaSortObject *alphaSortObject) {};
	virtual void					RenderAlphaSortList		() {};

	// VertexBuffer
	virtual zBOOL					DrawVertexBuffer		(zCVertexBuffer *vertexBuffer, 
															 int			firstVert	= 0, 
															 int			numVert		=-1, 
															 zWORD			*indexList	= 0, 
															 zDWORD			numIndex	= 0)=0;	// if no firstVert and numVert specified the entire VB will be rendered; if no indexLists are specified, the internal one will be used

	virtual zCVertexBuffer*			CreateVertexBuffer		()=0;
};

zENGINE_API extern zCRenderer *zrenderer;

#endif