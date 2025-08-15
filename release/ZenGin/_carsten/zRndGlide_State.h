#ifndef __zRNDGLIDE_STATE_H__
#define __zRNDGLIDE_STATE_H__

typedef enum zTRnd_BilerpFilterMode	{	zRND_BILERP_FILTER_MAT_DEFAULT,	
										zRND_BILERP_FILTER_ON,	
										zRND_BILERP_FILTER_OFF	
									};


typedef enum zTRnd_DitherMode		{	zRND_DITHER_MAT_DEFAULT,	
										zRND_DITHER_ON,	
										zRND_DITHER_OFF 
									};


extern zCTex_RndGlide			*actTexture;
extern zCTex_RndGlide			*oldTexture;

extern zTRnd_RenderMode			renderMode;
extern zTRnd_PolyDrawMode		pDrawMode;
extern float					alphaF;   // percentage 
extern GrColor_t				actAlpha; // 0..255
extern zTRnd_AlphaBlendFunc		alphaBlendFunc;
extern zTRnd_AlphaBlendSource	alphaSrc;

extern zBOOL					mipMapDithering;
extern zBOOL					cc;			// tmp workaround for chromakeying

// global render state variables
extern zBOOL					alphaSort			;  // perhaps different sort modes ?
extern zBOOL					usingTextureAlpha	;
extern zTRnd_AlphaBlendFunc		alphaFunc			;
extern zBOOL					alphaFuncMul		;
extern zTCam_DrawMode			drMode				;
extern zTRnd_BilerpFilterMode	filtMode;
extern zTRnd_DitherMode			dithMode;

extern GrColor_t				chromaColor;
extern GrVertex					v[zMAX_POLY_CLIP_VERTS];   // temporary vertex-struct req. by glide
extern zBOOL					renderCameraActive ;
extern float					zMAX;
extern float					mipRange	;
extern float					mipRangeInv	;
extern int						memPerTMU;
extern zBOOL					lfbLoop;

extern zBOOL					headTexFound;

extern int						numTexDrawn;

inline void SetDrawMode	(zTCam_DrawMode mode, const zBOOL &force=FALSE) 
{
	if (drMode == mode && !force) return;
	switch (mode) {
	case zCAM_DRAW_WIRE:
	case zCAM_DRAW_FLAT:
		grColorCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
					   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE);
		grTexCombine( GR_TMU0,GR_COMBINE_FUNCTION_ZERO,GR_COMBINE_FACTOR_NONE,
					  GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
					  FXFALSE,FXFALSE );
		break;
	case zCAM_DRAW_TEX:
		if (renderMode != zRND_MODE_2_PASS_LIGHTMAP) {
			grColorCombine(	GR_COMBINE_FUNCTION_SCALE_OTHER,		// func
							GR_COMBINE_FACTOR_LOCAL,				// factor
 							GR_COMBINE_LOCAL_ITERATED,				// local
							GR_COMBINE_OTHER_TEXTURE,				// other
							FXFALSE);
		}
		else {
			grColorCombine ( GR_COMBINE_FUNCTION_SCALE_OTHER_ADD_LOCAL,
						GR_COMBINE_FACTOR_ONE,
                        GR_COMBINE_LOCAL_ITERATED, GR_COMBINE_OTHER_TEXTURE, FXFALSE );
		}

		grTexCombine( GR_TMU0,GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
					  GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
					  FXFALSE,FXFALSE );

		break;
	}
	drMode = mode;
};

inline zTCam_DrawMode GetDrawMode()
{
	return drMode;
}


inline void SetAlphaSource(const zBOOL txAlpha, const zBOOL force = FALSE)
{

	if ( txAlpha == usingTextureAlpha && !force ) return;

	if ( txAlpha == TRUE ) {
		// a = iterated vertex alpha * texture alpha ( * constant alpha, manually mult. w/each vertex)
		grAlphaCombine(GR_COMBINE_FUNCTION_SCALE_OTHER,	GR_COMBINE_FACTOR_LOCAL,
					   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_TEXTURE, FXFALSE	);
	}
	else {
		// a = iterated vertex alpha * constant alpha - default
		grAlphaCombine(GR_COMBINE_FUNCTION_SCALE_OTHER,	GR_COMBINE_FACTOR_LOCAL,
					   GR_COMBINE_LOCAL_CONSTANT,GR_COMBINE_OTHER_ITERATED, FXFALSE	);//	    grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,	GR_COMBINE_FACTOR_ONE,
	}

	usingTextureAlpha = txAlpha;

}

inline zBOOL GetAlphaSource() 
{
	return usingTextureAlpha;
}


inline void SetAlphaFunc(const zTRnd_AlphaBlendFunc & func,const zBOOL &force=FALSE)
{
	if (func == alphaFunc && !force) return;

	switch (func) {
	case zRND_ALPHA_FUNC_BLEND:
	//	c1 = (c0 * a) + (c1 * (1-a))
		if (alphaFuncMul) {
			SetDrawMode(drMode,TRUE);
			alphaFuncMul = FALSE;
		}
		grAlphaBlendFunction(GR_BLEND_SRC_ALPHA, GR_BLEND_ONE_MINUS_SRC_ALPHA,  
							 GR_BLEND_ZERO,GR_BLEND_ZERO);            
		break;
	case zRND_ALPHA_FUNC_ADD:
	//		c1 = a * (c0 + c1)
		if (alphaFuncMul) {
			SetDrawMode(drMode,TRUE);
			alphaFuncMul = FALSE;
		}
	    grAlphaBlendFunction(GR_BLEND_SRC_ALPHA, GR_BLEND_ONE,  
							 GR_BLEND_ZERO,GR_BLEND_ZERO);  
		break;
	case zRND_ALPHA_FUNC_SUB:   // not possible on act. 3dfx-hw
#ifdef CHASE_DEBUG
#else
		zERR_FATAL("C: zCRndGlide_State.h(SetAlphaFunc): Subtractive Blending not supported");
#endif
		break;
	case zRND_ALPHA_FUNC_MUL:
	//		c1 = c0 * c1, restrictions: no iterated vertex color, alpha only one of vertex or texture alpha (automatic use of texture alpha if texture has alpha channel)
		if (drMode == zCAM_DRAW_TEX) {
			alphaFuncMul = TRUE;
			grColorCombine(	GR_COMBINE_FUNCTION_SCALE_OTHER,		// func
							GR_COMBINE_FACTOR_OTHER_ALPHA,			// factor
 							GR_COMBINE_LOCAL_NONE,					// local
							GR_COMBINE_OTHER_TEXTURE,				// other
							FXFALSE);
		}
	    grAlphaBlendFunction(GR_BLEND_DST_COLOR, GR_BLEND_ZERO,  
							 GR_BLEND_ZERO,GR_BLEND_ZERO);  
		break;
	case zRND_ALPHA_FUNC_MUL2:
		//	c1 = 2 * c0 * c1, restrictions: no iterated vertex color, alpha only one of vertex or texture alpha (automatic use of texture alpha if texture has alpha channel)

		if (drMode == zCAM_DRAW_TEX) {
			alphaFuncMul = TRUE;
			grColorCombine(	GR_COMBINE_FUNCTION_SCALE_OTHER,		// func
							GR_COMBINE_FACTOR_OTHER_ALPHA,			// factor
 							GR_COMBINE_LOCAL_NONE,					// local
							GR_COMBINE_OTHER_TEXTURE,				// other
							FXFALSE);
		}
		
	    grAlphaBlendFunction(GR_BLEND_DST_COLOR, GR_BLEND_SRC_COLOR,  
							 GR_BLEND_ZERO,GR_BLEND_ZERO);  
		break;
	default:
		// c1 = c0;
		if (alphaFuncMul) {
			SetDrawMode(drMode,TRUE);
			alphaFuncMul = FALSE;
		}
	    grAlphaBlendFunction(GR_BLEND_ONE, GR_BLEND_ZERO,  
							 GR_BLEND_ZERO,GR_BLEND_ZERO);  

	}

	alphaFunc = func;

}

inline zTRnd_AlphaBlendFunc GetAlphaFunc() 
{
	return alphaFunc;
};

inline void SetBilerpFiltering(const zTRnd_BilerpFilterMode mode,const zBOOL &force=FALSE)	
{ 
	if (mode == filtMode && !force) return;
	switch (mode) {
	case zRND_BILERP_FILTER_ON:
	case zRND_BILERP_FILTER_MAT_DEFAULT:
		grTexFilterMode(GR_TMU0,GR_TEXTUREFILTER_BILINEAR,GR_TEXTUREFILTER_BILINEAR);
		break;
	case zRND_BILERP_FILTER_OFF:
		grTexFilterMode(GR_TMU0,GR_TEXTUREFILTER_POINT_SAMPLED,GR_TEXTUREFILTER_POINT_SAMPLED);
		break;
	}
	filtMode = mode;
};

inline zTRnd_BilerpFilterMode GetBilerpFiltering()
{
	return filtMode; 
}

inline void	SetDithering (const zTRnd_DitherMode mode,const zBOOL &force=FALSE)		
{ 
	if (mode == dithMode && !force) return;
	switch (mode) {
	case zRND_DITHER_ON:
	case zRND_DITHER_MAT_DEFAULT:
		grDitherMode( GR_DITHER_4x4 );
		break;
	case zRND_DITHER_OFF:
		grDitherMode( GR_DITHER_DISABLE );
		break;
	}
	dithMode = mode;
}

inline zTRnd_DitherMode GetDithering()
{
	return dithMode;
}




inline void SetMipMapDitheringEnabled ( const zBOOL &flag , const zBOOL &force ) 
{
	if (mipMapDithering == flag && !force) return;
	if (flag) {
		grHints(GR_HINT_ALLOW_MIPMAP_DITHER,1);
		grTexMipMapMode(GR_TMU0,GR_MIPMAP_NEAREST_DITHER,FXTRUE);
		grTexLodBiasValue(GR_TMU0,GR_LODBIAS_TRILINEAR);
	} else {
		grHints(GR_HINT_ALLOW_MIPMAP_DITHER,0);
		grTexMipMapMode(GR_TMU0,GR_MIPMAP_NEAREST,FXFALSE);
		grTexLodBiasValue(GR_TMU0,GR_LODBIAS_BILINEAR);
	}
};



#endif