/******************************************************************************** 
 
     $Workfile:: zRenderManager.h     $                $Date:: 24.04.01 17:34   $
     $Revision:: 14                   $             $Modtime:: 23.04.01 17:53   $
       $Author:: Edenfeld                                                       $
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Render Manager
   created: 29.5.2000

 * $Log: /current_work/ZenGin/_Dieter/zRenderManager.h $
 * 
 * 14    24.04.01 17:34 Edenfeld
 * Patch 1.08a
 * 
 * 13    15.02.01 1:49 Hildebrandt
 * 
 * 12    14.02.01 7:28 Hildebrandt
 * 
 * 11    12.02.01 17:51 Hildebrandt
 * 
 * 10    25.01.01 5:07 Hildebrandt
 * 
 * 9     8.01.01 17:56 Hildebrandt
 * 
 * 8     4.12.00 16:28 Hildebrandt
 * 
 * 7     22.11.00 1:36 Hildebrandt
 * 
 * 6     12.10.00 18:02 Hildebrandt
 * 
 * 5     11.10.00 19:45 Hildebrandt
 * 
 * 4     15.09.00 16:44 Hildebrandt
 * 
 * 3     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 4     9.08.00 17:12 Admin
 * 
 * 2     3.07.00 12:44 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revisio: 2 $ ($Modtime: 23.04.01 17:53 $)

// =======================================================================================================================

#ifndef __ZRENDERMANAGER_H__
#define __ZRENDERMANAGER_H__

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif


#ifndef __Z3D_H__
#include <z3d.h>
#endif


// forward declarations
class zCPolygon;
class zCMaterial;
class zCShader;
class zCVertexBuffer;
class zCVertexBufferDyn2;
class zCTexture;
class zCShaderStage;

// =======================================================================================================================

class zCRenderManager {
public:
	 zCRenderManager();
	~zCRenderManager();

	//
	void					InitRenderManager		();
	void					CleanupRenderManager	();

	static	void			SetUseRendererTNL		(const zBOOL b)		{ s_useRendererTNL=b;				};
	static	zBOOL			GetUseRendererTNL		()					{ return s_useRendererTNL;			};
	static	void			S_SetDetailTexturesEnabled(const zBOOL b)	{ s_detailTexturesEnabled=b;		};
	static	zBOOL			S_GetDetailTexturesEnabled()				{ return s_detailTexturesEnabled;	};

	//
	static zCShader*		GetFreeShader			();
	static zCShaderStage*	GetFreeShaderStage		();
	static void				ResetFreeShaderList		()	{ s_currentShader=0; s_currentShaderStage=0; };

	//
	zCVertexBufferDyn2* zCCFASTCALL GetFreeDynVertexBuffer	(zCShader *shader);

	//
	
	//void	zCCFASTCALL		AddPoly					(zCPolygon *poly);
	void	zCCFASTCALL		AddPolyAlphaSimple		(zCPolygon *poly);
	void					Flush					();
	void					FlushSimpleAlphaPolys	();



	//
	void					SetOverrideAlpha		(zREAL alpha, zTRnd_AlphaBlendFunc alphaBlendFunc) { overrideAlphaValue=zFloat2Int(alpha*255.0F); overrideAlphaBlendFunc=alphaBlendFunc; };	// alpha: 0..1
	zREAL					GetOverrideAlpha		() const { return zREAL(overrideAlphaValue) / zREAL(255.0F); };	// return value: 0..1

	//
	int						GetHintLightning		() const { return hintLightning;	};
	void					SetHintLightning		(const zBOOL b) { hintLightning = b;};

	//
	void	zCCFASTCALL		DrawVertexBuffer		(zCVertexBuffer *vertexBufferIn, 
													 int			firstVert, 
													 int			numVert, 
													 zWORD			*indexList,
													 zDWORD			numIndex,
													 zCMaterial		*material,
												     zBOOL			bSector);


	void	zCCFASTCALL		DrawVertexBuffer		(zCVertexBuffer *vertexBufferIn, 
													 int			firstVert, 
													 int			numVert, 
													 zWORD			*indexList,
													 zDWORD			numIndex,
													 zCShader		*shader);

	void	zCCFASTCALL		DrawVertexBufferSingleMaterial(const zCArray<zCPolygon*>&polyList, zCShader* shaderIn);

	inline void zCCFASTCALL AddPoly (zCPolygon *poly)
	{
		zERR_ASSERT (poly);
		zERR_ASSERT (poly->GetMaterial());

		zCMaterial *mat = poly->GetMaterial();

		if (mat->polyListTimeStamp!=frameCtr) 
		{
	//		mat->sceneMaterialIndex= sceneMaterialList.GetNum();
			mat->polyListTimeStamp = frameCtr;
			sceneMaterialList.Insert (mat);
		};
		mat->polyList.Insert	(poly);
		// [EDENFELD] Addon - FIXME: LightMap-Performance
		mat->polyListNeedsSort	|= zBOOL(poly->GetLightmap() > 0);
//		mat->polyListNeedsSort	|= zBOOL(poly->GetLightmap());		// ein klitzekleinwenig dirty (aber schneller)
	};


private:
	// MemPools of available, preallocated zCShader
	// (Spacer is granted some more resources)
	#ifdef COMPILING_SPACER
		// Spacer
		enum					{ zRENDERMAN_NUM_SHADER			= 192 }; 
		enum					{ zRENDERMAN_NUM_SHADER_STAGES	= zRENDERMAN_NUM_SHADER * 4 };
	#else
		// Game
		enum					{ zRENDERMAN_NUM_SHADER			= 64 }; 
		enum					{ zRENDERMAN_NUM_SHADER_STAGES	= zRENDERMAN_NUM_SHADER * 4 };
	#endif
	static zCShader				s_shaderList		[zRENDERMAN_NUM_SHADER];
	static zCShaderStage		s_shaderStageList	[zRENDERMAN_NUM_SHADER_STAGES];
	static int					s_currentShader;
	static int					s_currentShaderStage;

	//
	static zBOOL				s_useRendererTNL;
	static zBOOL				s_detailTexturesEnabled;
	static zCVertexBufferDyn2*	s_vertBufferDynTex1;
	static zCVertexBufferDyn2*	s_vertBufferDynTex2;
	static zCVertexBufferDyn2*	s_vertBufferDynTex2Normal;

	//
	zDWORD						frameCtr;
	zCArray<zCMaterial*>		sceneMaterialList;
	zCArray<zCPolygon*>		    sceneSimpleAlphaPolyList;	// for alpha vertex fading
	int							overrideAlphaValue;			// range: [0..255]
	zTRnd_AlphaBlendFunc		overrideAlphaBlendFunc;
	int							hintLightning;
								
	zBOOL						rendererMaterialModified;
								
	void	zCCFASTCALL			PackVB					(const zCArray<zCPolygon*> &polyList, zCShader	*shader);
								
	void	zCCFASTCALL			SortMaterialPolys		(zCMaterial *mat);
	void	zCCFASTCALL			BuildShader				(zCMaterial		*mat,				// IN
														 zCTexture		*lightmap, 
														 zDWORD			dlightmap,
														 zBOOL			useScratchPadShader,
														 zBOOL			bInSector,
														 zCShader*		&shader				// OUT
														);
	void	zCCFASTCALL			SetupBufferStates		(zCShader *shader, zCVertexBuffer *vertexBufferIn);
								
	void	zCCFASTCALL			SetTextureStage0		(zCShader *shader, zDWORD stageIndex, zCVertexBuffer *vertexBuffer);
	void	zCCFASTCALL			SetRGBA					(zCShaderStage *stage);
	void	zCCFASTCALL			SetStageColorOp			(const zDWORD stage, const zTRnd_AlphaBlendFunc alphaFunc);
	void	zCCFASTCALL			SetTextureTransform		(zCShader *shader, zDWORD stageIndex, zDWORD hardwareStageIndex);
	void	zCCFASTCALL			SetAlphaFunc			(zCShader *shader, zDWORD stageIndex, zDWORD hardwareStageIndex);

	friend class zCRndAlphaSortObject_WorldPoly;


};							



zENGINE_API extern zCRenderManager zrenderMan;

// =======================================================================================================================

// Transform functions
enum zTShaderWaveFunc {
    zSHD_FUNC_CONST,
	zSHD_FUNC_SIN,
    zSHD_FUNC_TRIANGLE,
    zSHD_FUNC_SQUARE,
    zSHD_FUNC_SAWTOOTH,
    zSHD_FUNC_INVERSESAWTOOTH,
	zSHD_FUNC_NOISE
};

// functions for generating and deforming vertexes.
enum zTShaderRGBGen {
	zSHD_RGBGEN_IDENTITY,
	zSHD_RGBGEN_VERTEX,		
	zSHD_RGBGEN_FACTOR,
	zSHD_RGBGEN_WAVE,	
};

enum zTShaderAlphaGen {
	zSHD_ALPHAGEN_IDENTITY,
	zSHD_ALPHAGEN_VERTEX,
	zSHD_ALPHAGEN_FACTOR,
	zSHD_ALPHAGEN_DETAILFADE,
	zSHD_ALPHAGEN_FARFADE,
	zSHD_ALPHAGEN_WATER
};

// texture coordinate generation
enum zTShaderTCGen {
	zSHD_TCGEN_BASE,
	zSHD_TCGEN_LIGHTMAP,	
	zSHD_TCGEN_ENVIRONMENT,	
	zSHD_TCGEN_ENVIRONMENT_FLAT,
};

// texture coordinate deformation
enum zTShaderTCMod {
	zSHD_TCMOD_NONE,
	zSHD_TCMOD_SCROLL,
	zSHD_TCMOD_ENVIRONMENT,
	zSHD_TCMOD_ROTATE,
	zSHD_TCMOD_SCALE,
	zSHD_TCMOD_STRETCH,
	zSHD_TCMOD_TRANSFORM,
	zSHD_TCMOD_TURB,
};

// vertes coordinates deformations
enum zTShaderDeformVertex {
	zSHD_DEFORMVERT_NONE,
	zSHD_DEFORMVERT_WAVE,
	zSHD_DEFORMVERT_NORMAL,
	zSHD_DEFORMVERT_BULGE,	
	zSHD_DEFORMVERT_MOVE,	
	zSHD_DEFORMVERT_AUTOSPRITE,
	zSHD_DEFORMVERT_AUTOSPRITE2,
};

// layer flags 
enum {
	LF_NOMIPMAP=0x01,		// do not create mipmaps
	LF_NOPICMIP=0x02,		// allways pick the highest mipmap
	LF_CLAMP=0x04,			// clamp, default is repeat
	LF_DETAIL=0x08,			// detail texture
	LF_LIGHTMAP=0x10,		// lightmap
	LF_HASTCMOD=0x20,
	LF_USENORMALS=0x40,
	LF_MULTITEX=0x80		// this layer and the next could be collapsed
};

// Shader flags:
enum {
	SF_NOMIPMAP=0x01,			// do not create mipmaps
	SF_NOPICMIP=0x02,			// allways pick the highest mipmap
	SF_POLYGONOFFSET=0x04,		// surface needs polygon offset
	SF_PORTAL=0x08,				// there is a portal layer
	SF_HASLIGHTMAP=0x10,		// there is a lightmap layer
	SF_HASCOLORS=0x20,			// there is a layer that needs colors
	SF_HASTCMOD=0x40,			// there is a layer that has lf_hastcmod
	SF_USENORMALS=0x80,			// there is a layer that has lf_usenormals
	SF_MULTITEX=0x0100			// this shader has two layers that can be collapsed
};

enum zTShaderFXMode {
	zSHD_FX_NONE=0,
	zSHD_FX_BASETEX,
	zSHD_FX_LIGHTMAP,
	zSHD_FX_LIGHTMAP_DYN,
	zSHD_FX_DETAIL,
	zSHD_FX_MACRO,
	zSHD_FX_ENV,
	zSHD_FX_SPECULAR,
};

class zCShaderStage {
public:
	zTShaderFXMode			shaderFXMode;
	zCTexture				*texture;
	zTRnd_AlphaBlendFunc	alphaFunc;
	zCOLOR					colorFactor;
	zCOLOR					avgTextureColor;		// needed, if texture is not yet cached in

	// params fuer colorGen, texUVGen
//	zTShaderWaveFunc		waveFunc;				// not currently used
	zTShaderAlphaGen		alphaGen;
	zTShaderRGBGen			rgbGen;
//	zREAL					rgbGenParams[5];		// not currently used
	zTShaderTCGen			tcGen;
	zTShaderTCMod			tcMod;
	zREAL					tcModParams[2];			// these should be really 5, but right now only 2 are in use!

	zBOOL					multiTextureNext;

	zCShaderStage();
	void Clear				()	{ 
		memset (this, 0, sizeof(*this));			// [BC] static memory overrun, false alert?
	};
};

class zCShader {
public:

	zCShader();
	~zCShader();
	int						GetNumStages		() const						{ return numStages;					};
	zCShaderStage*			GetStage			(int stageIndex) const			{ zERR_BOUNDS (stageIndex,0,MAX_STAGES); return stageList[stageIndex];		};
	void					AddStage			(zCShaderStage *stage)			{ zERR_ASSERT (numStages<MAX_STAGES);	 stageList[numStages++] = stage;	};
	void					InsertStage			(int pos, zCShaderStage *stage);
	void					Clear				()								{ numStages=0; hasLightmap = hasTcGenEnv = baseTexCachedIn = FALSE; };
	zBOOL					GetHasLightmap		() const						{ return hasLightmap;				};
	zBOOL					GetBaseTexCachedIn	() const						{ return baseTexCachedIn;			};

	enum { MAX_STAGES = 4 };
	int						numStages;
	zCShaderStage			*stageList[MAX_STAGES];
//	zTShaderDeformVertex	deformVert;					// not currently used
//	zREAL					defoormVertParams[8];		// not currently used

	zBOOL					hasLightmap;
	zBOOL					hasTcGenEnv;
	zBOOL					inSector;
	zBOOL					baseTexCachedIn;
};

// ======================================================================================

// maps object names to detailTexture names

class zCMapDetailTexture {
public:
	static	void			S_Init					();
	static	void			S_Cleanup				();

	struct zTMapDetailTextureEntry {
		zSTRING		detailTextureName;
		zREAL		detailTextureScale;
	};

	static	const zTMapDetailTextureEntry*	S_GetDetailTextureInfo (const zSTRING& objectName);	// return string of len==0 means not found
private:
};


// ======================================================================================

#endif