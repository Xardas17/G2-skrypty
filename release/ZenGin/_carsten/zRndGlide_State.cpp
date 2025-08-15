#include "zcore.h"
#include "zRndGlide.h"
#include "zRndGlide_State.h"
#include "zRndGlide_Draw.h"

zCTex_RndGlide	*actTexture=0;
zCTex_RndGlide	*oldTexture=(zCTex_RndGlide	*)0xffffffff;

int						memPerTMU;
zTRnd_RenderMode		renderMode;
zTRnd_PolyDrawMode		pDrawMode;
float					alphaF;   // percentage 
GrColor_t				actAlpha; // 0..255
zTRnd_AlphaBlendFunc	alphaBlendFunc;
zBOOL					alphaFuncMul;
zTRnd_AlphaBlendSource	alphaSrc;
zTRnd_BilerpFilterMode	filterMode;
zTRnd_DitherMode		ditherMode;
zBOOL					mipMapDithering;

GrColor_t				chromaColor;
GrVertex				v[zMAX_POLY_CLIP_VERTS];   // temporary vertex-struct req. by glide

// global render state variables
zBOOL					cc					= FALSE; // tmp workaround for chromakeying
zBOOL					lfbLoop				= FALSE;
zBOOL					alphaSort			= TRUE;  // perhaps different sort modes ?
zBOOL					usingTextureAlpha	= FALSE;
zTRnd_AlphaBlendFunc	alphaFunc			= zRND_ALPHA_FUNC_BLEND;
zTRnd_BilerpFilterMode	filtMode			= zRND_BILERP_FILTER_ON;
zTRnd_DitherMode		dithMode			= zRND_DITHER_ON;
zTCam_DrawMode			drMode				= zCAM_DRAW_NOTHING;
zBOOL					renderCameraActive  = FALSE;
float					mipRange			= 10000;
float					mipRangeInv			= 1/10000.0F;
int						numTexDrawn			= 0;


void zCRnd_Glide::SetRenderMode (const zTRnd_RenderMode rmode)
{
	zTRnd_BilerpFilterMode fmode = filtMode;
	renderMode = rmode;
	switch (rmode) {
	case zRND_MODE_1_PASS_VERT_LIGHT:
		PolyDrawFunc = PolyDrawOnePassVertLight;
		grTexClampMode			(GR_TMU0,GR_TEXTURECLAMP_WRAP,GR_TEXTURECLAMP_WRAP);
		SetAlphaFunc			(zRND_ALPHA_FUNC_MAT_DEFAULT);
		SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS);
		SetZBufferWriteEnabled	(TRUE);
		if (pDrawMode == zRND_DRAW_MATERIAL)
		grColorCombine			( GR_COMBINE_FUNCTION_SCALE_OTHER,
								  GR_COMBINE_FACTOR_LOCAL, 
								  GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_TEXTURE, FXFALSE);

		break;
	case zRND_MODE_1_PASS_MULTITEXTURE:
		if (cap.numTexPerPass<2) {
			zerr.Report(zERR_FATAL,8000,"C: zRndGlide.cpp(zCRnd_Glide::SetRenderMode): Single Pass Multi-Texture Rendering not supported with this board!");
		}else {
			PolyDrawFunc = PolyDrawOnePassMultiTex;
		};
		break;
	case zRND_MODE_2_PASS_TEXTURE:
		PolyDrawFunc = PolyDrawTwoPassTexture;
		grTexClampMode			(GR_TMU0,GR_TEXTURECLAMP_WRAP,GR_TEXTURECLAMP_WRAP);
		SetAlphaBlendFunc		(zRND_ALPHA_FUNC_MAT_DEFAULT);
		SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS);
		SetZBufferWriteEnabled	(TRUE);
		if (pDrawMode == zRND_DRAW_MATERIAL)
		grColorCombine			( GR_COMBINE_FUNCTION_SCALE_OTHER,
								  GR_COMBINE_FACTOR_LOCAL, 
								  GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_TEXTURE, FXFALSE);

		break;
	case zRND_MODE_2_PASS_LIGHTMAP:
		PolyDrawFunc = PolyDrawTwoPassLightMap;

		if (!lightMapBilerpFilter) SetBilerpFiltering(zRND_BILERP_FILTER_OFF);
		grTexClampMode		  (GR_TMU0,GR_TEXTURECLAMP_CLAMP,GR_TEXTURECLAMP_CLAMP);
		SetAlphaFunc		  (zRND_ALPHA_FUNC_MUL);
		SetZBufferWriteEnabled(FALSE);
		SetZBufferCompare     (zRND_ZBUFFER_CMP_LESS_EQUAL);
		grColorCombine        ( GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL,
								GR_COMBINE_FACTOR_ONE,
                                GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_TEXTURE, FXFALSE );

		SetBilerpFiltering(filtMode);
		return;
		
		break;
	case zRND_MODE_DYN_POLYS_VERT_LIGHT:
		PolyDrawFunc = PolyDrawVobDynVertLight;
		grTexClampMode			(GR_TMU0,GR_TEXTURECLAMP_WRAP,GR_TEXTURECLAMP_WRAP);
		SetAlphaFunc			(zRND_ALPHA_FUNC_BLEND);
		SetZBufferCompare		(zRND_ZBUFFER_CMP_LESS);
		SetZBufferWriteEnabled	(TRUE);
		if (pDrawMode == zRND_DRAW_MATERIAL)
		grColorCombine			( GR_COMBINE_FUNCTION_SCALE_OTHER,
								  GR_COMBINE_FACTOR_LOCAL, 
								  GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_TEXTURE, FXFALSE);
 
		break;
	}

	switch (pDrawMode) {
	case zRND_DRAW_MATERIAL:
		SetDrawMode(zCAM_DRAW_TEX,TRUE);
		break;
	case zRND_DRAW_FLAT:
		SetDrawMode(zCAM_DRAW_FLAT,TRUE);
		break;
	case zRND_DRAW_WIRE:
		SetDrawMode(zCAM_DRAW_WIRE,TRUE);
		break;
	}

}

zTRnd_RenderMode zCRnd_Glide::GetRenderMode () const
{ 
	return renderMode; 
};


void zCRnd_Glide::SetBilerpFilterEnabled(const zBOOL b)
{ 
	SetBilerpFiltering(b?zRND_BILERP_FILTER_ON:zRND_BILERP_FILTER_OFF); 
	bilerpFilter = b; 
};

zBOOL zCRnd_Glide::GetBilerpFilterEnabled() const
{
	return bilerpFilter;
};

void  zCRnd_Glide::SetZBufferCompare	(const zTRnd_ZBufferCmp& zcmp)		
{
	switch (zcmp) {
	case zRND_ZBUFFER_CMP_LESS:
		grDepthBufferFunction(GR_CMP_LESS);
		break;
	case zRND_ZBUFFER_CMP_LESS_EQUAL:
		grDepthBufferFunction(GR_CMP_LEQUAL);
		break;
	case zRND_ZBUFFER_CMP_ALWAYS:
		grDepthBufferFunction(GR_CMP_ALWAYS);
		break;
	case zRND_ZBUFFER_CMP_NEVER:
		grDepthBufferFunction(GR_CMP_NEVER);
		break;
	}
	zBufCompareFunc = zcmp;
};


void zCRnd_Glide::SetFogColor         (const zCOLOR& col) 
{
	GrColor_t grColor=
		(GrColor_t) col.GetRedByte() << 24 | (GrColor_t) col.GetGreenByte() << 16 | 
		(GrColor_t) col.GetBlueByte() << 8;

	grFogColorValue(grColor);
	fogColor = col;
}


void zCRnd_Glide ::	SetAlphaBlendSource	( const zTRnd_AlphaBlendSource &src ) 
{ 
	alphaSrc = src; 
};
void zCRnd_Glide ::	SetAlphaBlendFunc( const zTRnd_AlphaBlendFunc &mode ) 
{ 
	alphaBlendFunc = mode; 
};

zTRnd_AlphaBlendSource zCRnd_Glide :: GetAlphaBlendSource()
{	
	return alphaSrc; 
};
zTRnd_AlphaBlendFunc zCRnd_Glide ::	GetAlphaBlendFunc()
{	
	return alphaBlendFunc;
};
float zCRnd_Glide :: GetAlphaBlendFactor()
{ 
	return alphaF;	 
};

void  zCRnd_Glide :: SetSortAlphaPolys	( const zBOOL &sort ) 
{	
	alphaSort = sort; 
}

zBOOL zCRnd_Glide :: GetSortAlphaPolys	()					  
{	
	return alphaSort; 
}

		
void zCRnd_Glide :: SetPolySortMode	(const zTRnd_PolySortMode &smode)
{
	if (smode == zRND_SORT_ZBUFFER) grDepthBufferMode(GR_DEPTHBUFFER_WBUFFER); else
	grDepthBufferMode(GR_DEPTHBUFFER_DISABLE);

	polySortMode = smode;

};		

/********************************************************************************
 FUNCTION: SetPolyDrawMode
 DESC    : Sets the drawmode of following polys
*********************************************************************************/
void zCRnd_Glide ::	SetPolyDrawMode		(const zTRnd_PolyDrawMode& drawMode)
{

	if (pDrawMode == drawMode) return;
	switch (drawMode) {
	case zRND_DRAW_MATERIAL:
		SetDrawMode(zCAM_DRAW_TEX,TRUE);
		break;
	case zRND_DRAW_FLAT:
		SetDrawMode(zCAM_DRAW_FLAT,TRUE);
		break;
	case zRND_DRAW_WIRE:
		SetDrawMode(zCAM_DRAW_FLAT,TRUE);
		break;
	}
	polyDrawMode = drawMode;
	pDrawMode = drawMode;

}

zTRnd_PolyDrawMode	zCRnd_Glide :: GetPolyDrawMode		() 
{ 
	return polyDrawMode; 
};

void zCRnd_Glide::ResetZTest () 
{
	grSstResetPerfStats     ();
};

int zCRnd_Glide::HasPassedZTest () 
{
	GrSstPerfStats_t        grStats;
	grSstIdle               ();                             
	grSstPerfStats          (&grStats);

	zTestStat.pixelsIn  += grStats.pixelsIn;
	zTestStat.pixelsOut += grStats.pixelsOut;
	zTestStat.zFuncFail += grStats.zFuncFail;
	zTestStat.aFuncFail += grStats.aFuncFail;
	zTestStat.chromaFail+= grStats.chromaFail;

	return ((grStats.pixelsIn - grStats.zFuncFail)>0);
};
