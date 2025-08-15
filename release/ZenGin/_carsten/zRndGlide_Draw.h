
#include "zRndGlide_State.h"
#include "zRndGlide_Cache.h"
#include "zRndGlide_Util.h"

#ifndef __zRNDGLIDE_DRAW_H__
#define __zRNDGLIDE_DRAW_H__

struct zSRndGlide_AlphaPoly {
	// several render states at DrawPoly-call
	int						alpha;
	zTRnd_AlphaBlendFunc	alpFunc;
	zTRnd_PolyDrawMode		dMode;

	// clipped vertices per transp. polygon - evtl. dyn. alloc
	int						numClipVert;	
	zVALUE					vertCamSpaceZInv[zMAX_POLY_CLIP_VERTS];
	zVALUE					vertScrX		[zMAX_POLY_CLIP_VERTS];
	zVALUE					vertScrY		[zMAX_POLY_CLIP_VERTS];
	zVALUE					texu			[zMAX_POLY_CLIP_VERTS];
	zVALUE					texv			[zMAX_POLY_CLIP_VERTS];
	float					avgZ;
	zCOLOR					lightDyn		[zMAX_POLY_CLIP_VERTS];	
	void					*poly;	// avoid material referencing with void * ptr.
	zCMaterial				*mat;
	zCTexture				*tex;
	zCTexture				*lightMap;
	// copy of chroma color
	int						cCol;   
	zBOOL					ccEnabled;
	zSRndGlide_AlphaPoly*	next;
};  

extern void SortAlphaPolys			(zCArray <zSRndGlide_AlphaPoly*> &polys, int items);
extern void PolyDrawOnePassMultiTex (zCPolygon *poly);
extern void PolyDrawOnePassVertLight(zCPolygon *poly);
extern void PolyDrawTwoPassTexture  (zCPolygon *poly);
extern void PolyDrawTwoPassLightMap (zCPolygon *poly);
extern void PolyDrawVobDynVertLight (zCPolygon *poly);

extern float grBucketSize; 
extern zSRndGlide_AlphaPoly*	alphaPolyBucket[GR_MAXBUCKETS]; 


inline void PolyDrawTwoPassLightMapInlined(zCPolygon *poly)
{
	// assumes poly has a lightmap !!!
	// lightmaps are rendered with little state-changes

	zCMaterial	*mat   = poly->GetMaterial();
	if (pDrawMode != zRND_DRAW_MATERIAL) return;

	actTexture=(zCTex_RndGlide *)poly->GetLightmap();

	if (!actTexture) return ;

	reqLargeLOD = actTexture->infoSrc.header.large_lod ;

	// texture changed, textured polygon
	if (!oldTexture) SetDrawMode(zCAM_DRAW_TEX);  // old state gouraud? -> yes -> set textured

	actTexture->Download();

	zREAL s,t;
	for (int i=0; i<poly->numClipVert; i++) {
		zCVertex* vt = poly->clipVert[i];
		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST; 
		v[i].oow = vt->vertCamSpaceZInv;

		zCVertFeature *feat=poly->clipFeat[i];
		v[i].r	 = (float)feat->lightDyn.GetRedByte();
		v[i].g	 = (float)feat->lightDyn.GetGreenByte();
		v[i].b	 = (float)feat->lightDyn.GetBlueByte();	

		actTexture->GetLightmapTexCoords (vt->position, s, t);

		v[i].tmuvtx[GR_TMU0].sow = s * actTexture->scaleX * v[i].oow;
		v[i].tmuvtx[GR_TMU0].tow = t * actTexture->scaleY * v[i].oow;
		v[i].a	 = 255;
	}
	
	grDrawPolygonVertexList(poly->numClipVert, v); 

	oldTexture = actTexture;
	
};


inline void DrawPolyWire	(const zCPolygon *poly)
{
	GrState state; 

	grGlideGetState(&state);

	grColorCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE);

	grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE );

	grAlphaBlendFunction(GR_BLEND_SRC_ALPHA,GR_BLEND_ONE_MINUS_SRC_ALPHA,
						 GR_BLEND_ZERO,GR_BLEND_ZERO);            

	
	for (int i=0; i<poly->numClipVert; i++) {
		zCVertex* vt = poly->clipVert[i];

		v[i].oow = vt->vertCamSpaceZInv;
		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST;  

		v[i].tmuvtx[GR_TMU0].sow = 0;
		v[i].tmuvtx[GR_TMU0].tow = 0;

		v[i].r	 = 255.0F;
		v[i].g	 = 255.0F;
		v[i].b	 = 255.0F;
		v[i].a	 = 255;
	}

	for (i=0; i<poly->numClipVert-1; i++) grDrawLine(&v[i], &v[i+1]);
	grDrawLine(&v[poly->numClipVert-1],&v[0]);

	grGlideSetState(&state);
}


inline void DrawTransPolyWire(const zSRndGlide_AlphaPoly *tp)
{
	for (int i=0; i<tp->numClipVert; i++) {

		v[i].oow = tp->vertCamSpaceZInv[i];
		v[i].x	 = tp->vertScrX[i] + SNAPCONST; 
		v[i].y	 = tp->vertScrY[i] + SNAPCONST; 

		v[i].tmuvtx[GR_TMU0].sow = 0;
		v[i].tmuvtx[GR_TMU0].tow = 0;

		v[i].r	 = 255.0F;
		v[i].g	 = 255.0F;
		v[i].b	 = 255.0F;
		v[i].a	 = 255;

	}

	for (i=0; i<tp->numClipVert-1; i++) grDrawLine(&v[i], &v[i+1]);
	grDrawLine(&v[tp->numClipVert-1],&v[0]);

}

inline void DrawTransPolyGouraud(const zSRndGlide_AlphaPoly *tp)
{
	float mR,mG,mB;
	// precalc material color multiplicant
	mR = (float) tp->mat->GetColor().GetRedByte()   * (1.0F/255.0F);
	mG = (float) tp->mat->GetColor().GetGreenByte() * (1.0F/255.0F);
	mB = (float) tp->mat->GetColor().GetBlueByte()  * (1.0F/255.0F);


	for (int i=0; i<tp->numClipVert; i++) {
		v[i].oow = tp->vertCamSpaceZInv[i];
		v[i].x	 = tp->vertScrX[i] + SNAPCONST; 
		v[i].y	 = tp->vertScrY[i] + SNAPCONST; 

		v[i].tmuvtx[GR_TMU0].sow = 0;
		v[i].tmuvtx[GR_TMU0].tow = 0;

		v[i].r	 = (float)tp->lightDyn[i].GetRedByte()   * mR;
		v[i].g	 = (float)tp->lightDyn[i].GetGreenByte() * mG;
		v[i].b	 = (float)tp->lightDyn[i].GetBlueByte()  * mB;
		v[i].a	 = (float)tp->alpha;
	}

	grDrawPolygonVertexList(tp->numClipVert, v);


}

inline void DrawTransPolyTex(const zSRndGlide_AlphaPoly *tp)
{
	if (tp->lightMap == 0) { // tmp
		if (!actTexture->HasAlpha()) {
			// draw textured poly
			if (!alphaFuncMul)
			for (int i=0; i<tp->numClipVert; i++) {

				v[i].x	 = tp->vertScrX[i] + SNAPCONST; 
				v[i].y	 = tp->vertScrY[i] + SNAPCONST; 

				v[i].oow = tp->vertCamSpaceZInv[i];

				v[i].r	 = (float)tp->lightDyn[i].GetRedByte();
				v[i].g	 = (float)tp->lightDyn[i].GetGreenByte();
				v[i].b	 = (float)tp->lightDyn[i].GetBlueByte();

				v[i].tmuvtx[GR_TMU0].sow = tp->texu[i] * actTexture->scaleX * v[i].oow;
				v[i].tmuvtx[GR_TMU0].tow = tp->texv[i] * actTexture->scaleY * v[i].oow;

				v[i].a	 = (float)tp->lightDyn[i].GetAlphaByte();
			}
			else 
			for (int i=0; i<tp->numClipVert; i++) {

				v[i].x	 = tp->vertScrX[i] + SNAPCONST; 
				v[i].y	 = tp->vertScrY[i] + SNAPCONST; 

				v[i].oow = tp->vertCamSpaceZInv[i];

				v[i].r	 = (float)tp->lightDyn[i].GetRedByte();
				v[i].g	 = (float)tp->lightDyn[i].GetGreenByte();
				v[i].b	 = (float)tp->lightDyn[i].GetBlueByte();

				v[i].tmuvtx[GR_TMU0].sow = tp->texu[i] * actTexture->scaleX * v[i].oow;
				v[i].tmuvtx[GR_TMU0].tow = tp->texv[i] * actTexture->scaleY * v[i].oow;

				v[i].a	 = float(tp->alpha)/255 * (float)tp->lightDyn[i].GetAlphaByte();
			}
		}
		else {
			// draw textured poly
			for (int i=0; i<tp->numClipVert; i++) {

				v[i].x	 = tp->vertScrX[i] + SNAPCONST; 
				v[i].y	 = tp->vertScrY[i] + SNAPCONST; 

				v[i].oow = tp->vertCamSpaceZInv[i];

				v[i].r	 = (float)tp->lightDyn[i].GetRedByte();
				v[i].g	 = (float)tp->lightDyn[i].GetGreenByte();
				v[i].b	 = (float)tp->lightDyn[i].GetBlueByte();

				v[i].tmuvtx[GR_TMU0].sow = tp->texu[i] * actTexture->scaleX * v[i].oow;
				v[i].tmuvtx[GR_TMU0].tow = tp->texv[i] * actTexture->scaleY * v[i].oow;

				v[i].a	 = float(tp->alpha)/255 * tp->lightDyn[i].GetAlphaByte();
			}
		}
	}
	else {
		if (!actTexture->HasAlpha()) {
			// draw textured poly
			for (int i=0; i<tp->numClipVert; i++) {

				v[i].x	 = tp->vertScrX[i] + SNAPCONST; 
				v[i].y	 = tp->vertScrY[i] + SNAPCONST; 

				v[i].oow = tp->vertCamSpaceZInv[i];

				v[i].r	 = v[i].g = v[i].b = 255;

				v[i].tmuvtx[GR_TMU0].sow = tp->texu[i] * actTexture->scaleX * v[i].oow;
				v[i].tmuvtx[GR_TMU0].tow = tp->texv[i] * actTexture->scaleY * v[i].oow;

				v[i].a	 = (float)tp->lightDyn[i].GetAlphaByte();

			}
		}
		else {
			// draw textured poly
			for (int i=0; i<tp->numClipVert; i++) {

				v[i].x	 = tp->vertScrX[i] + SNAPCONST; 
				v[i].y	 = tp->vertScrY[i] + SNAPCONST; 

				v[i].oow = tp->vertCamSpaceZInv[i];

				v[i].r	 = v[i].g = v[i].b = 255;

				v[i].tmuvtx[GR_TMU0].sow = tp->texu[i] * actTexture->scaleX * v[i].oow;
				v[i].tmuvtx[GR_TMU0].tow = tp->texv[i] * actTexture->scaleY * v[i].oow;

				v[i].a	 = float(tp->alpha)/255 * tp->lightDyn[i].GetAlphaByte();
			}
		}

	}

	grDrawPolygonVertexList(tp->numClipVert, v);
}


inline void RenderPoly1PassVertLightTex(const zCPolygon * poly)
{
	for (int i=0; i<poly->numClipVert; i++) {
		v[i].x	 = poly->clipVert[i]->vertScrX + SNAPCONST; 
		v[i].y	 = poly->clipVert[i]->vertScrY + SNAPCONST; 
		v[i].oow = poly->clipVert[i]->vertCamSpaceZInv;

		zCVertFeature *feat=poly->clipFeat[i];
		v[i].r	 = (float)feat->lightDyn.GetRedByte();
		v[i].g	 = (float)feat->lightDyn.GetGreenByte();
		v[i].b	 = (float)feat->lightDyn.GetBlueByte();
		v[i].tmuvtx[GR_TMU0].sow = feat->texu * actTexture->scaleX * v[i].oow ;
		v[i].tmuvtx[GR_TMU0].tow = feat->texv * actTexture->scaleY * v[i].oow ;
		v[i].a	 = 255;

	}
	grDrawPolygonVertexList(poly->numClipVert, v); 
}

inline void RenderPoly1PassVertLightGouraud(const zCPolygon *poly)
{
	float mR,mG,mB;

	// precalc material color multiplicant
	mR = (float) poly->GetMaterial()->GetColor().GetRedByte()   * (1.0F/255.0F);
	mG = (float) poly->GetMaterial()->GetColor().GetGreenByte() * (1.0F/255.0F);
	mB = (float) poly->GetMaterial()->GetColor().GetBlueByte()  * (1.0F/255.0F);
	
	for (int i=0; i<poly->numClipVert; i++) {
		zCVertex* vt = poly->clipVert[i];

		v[i].oow = vt->vertCamSpaceZInv;
		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST; 

		v[i].tmuvtx[GR_TMU0].sow = 0;
		v[i].tmuvtx[GR_TMU0].tow = 0;

		zCVertFeature *feat=poly->clipFeat[i];
		v[i].r	 = (float)feat->lightDyn.GetRedByte()   * mR;
		v[i].g	 = (float)feat->lightDyn.GetGreenByte() * mG;
		v[i].b	 = (float)feat->lightDyn.GetBlueByte()  * mB;
		v[i].a	 = 255;
	}

	grDrawPolygonVertexList(poly->numClipVert, v);
}


inline void RenderPoly2PassTextureTex(const zCPolygon * poly)
{
	if (poly->GetLightmap() == 0) {
		for (int i=0; i<poly->numClipVert; i++) {
			zCVertex* vt = poly->clipVert[i];

			v[i].x	 = vt->vertScrX + SNAPCONST; 
			v[i].y	 = vt->vertScrY + SNAPCONST; 
			v[i].oow = vt->vertCamSpaceZInv;

			zCVertFeature *feat=poly->clipFeat[i];
			v[i].r	 = (float)feat->lightDyn.GetRedByte();
			v[i].g	 = (float)feat->lightDyn.GetGreenByte();
			v[i].b	 = (float)feat->lightDyn.GetBlueByte();

			v[i].tmuvtx[GR_TMU0].sow = feat->texu * actTexture->scaleX * v[i].oow;
			v[i].tmuvtx[GR_TMU0].tow = feat->texv * actTexture->scaleY * v[i].oow;

			v[i].a	 = (float)feat->lightDyn.GetAlphaByte();
		}
	} else {
		for (int i=0; i<poly->numClipVert; i++) {
			zCVertex* vt = poly->clipVert[i];
			v[i].x	 = vt->vertScrX + SNAPCONST; 
			v[i].y	 = vt->vertScrY + SNAPCONST; 
			v[i].oow = vt->vertCamSpaceZInv;

			zCVertFeature *feat=poly->clipFeat[i];
			v[i].r	 = v[i].g = v[i].b = 255;
			v[i].tmuvtx[GR_TMU0].sow = feat->texu * actTexture->scaleX * v[i].oow;
			v[i].tmuvtx[GR_TMU0].tow = feat->texv * actTexture->scaleY * v[i].oow;
			v[i].a	 = 255;
		}
	}

	
	grDrawPolygonVertexList(poly->numClipVert, v); 

}

inline void RenderPoly2PassTextureGouraud(const zCPolygon *poly)
{
	float mR,mG,mB;
	// precalc material color multiplicant
	mR = (float) poly->GetMaterial()->GetColor().GetRedByte()   * (1.0F/255.0F);
	mG = (float) poly->GetMaterial()->GetColor().GetGreenByte() * (1.0F/255.0F);
	mB = (float) poly->GetMaterial()->GetColor().GetBlueByte()  * (1.0F/255.0F);

	for (int i=0; i<poly->numClipVert; i++) {
		zCVertex* vt = poly->clipVert[i];
		v[i].oow = vt->vertCamSpaceZInv;
		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST; 

		v[i].tmuvtx[GR_TMU0].sow = 0;
		v[i].tmuvtx[GR_TMU0].tow = 0;

		zCVertFeature *feat=poly->clipFeat[i];
		v[i].r	 = (float)feat->lightDyn.GetRedByte()   * mR;
		v[i].g	 = (float)feat->lightDyn.GetGreenByte() * mG;
		v[i].b	 = (float)feat->lightDyn.GetBlueByte()  * mB;
		v[i].a	 = 255;
	}

	grDrawPolygonVertexList(poly->numClipVert, v);
}


inline void RenderPolyVobDynVertLightTex(const zCPolygon * poly)
{
	
	float alpha = (alphaSrc == zRND_ALPHA_SOURCE_CONSTANT) ? alpha = (float)actAlpha : alpha = (float)poly->GetMaterial()->GetAlpha();

	for (int i=0; i<poly->numClipVert; i++) {
		zCVertex* vt = poly->clipVert[i];
		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST; 
		v[i].oow = vt->vertCamSpaceZInv;

		zCVertFeature *feat=poly->clipFeat[i];
		v[i].r	 = (float)feat->lightDyn.GetRedByte();
		v[i].g	 = (float)feat->lightDyn.GetGreenByte();
		v[i].b	 = (float)feat->lightDyn.GetBlueByte();
		v[i].tmuvtx[GR_TMU0].sow = feat->texu * actTexture->scaleX * v[i].oow;
		v[i].tmuvtx[GR_TMU0].tow = feat->texv * actTexture->scaleY * v[i].oow;

		v[i].a	 = alpha/255 * (float)feat->lightDyn.GetAlphaByte();;
	}
	
	grDrawPolygonVertexList(poly->numClipVert, v); 

}

inline void RenderPolyVobDynVertLightGouraud(zCPolygon *poly)
{
	RenderPoly1PassVertLightGouraud(poly);
};


inline void RenderPolyAlphaWire(const zCPolygon *poly)
{

	float alpha = (alphaSrc == zRND_ALPHA_SOURCE_CONSTANT) ? alpha = (float)actAlpha : alpha = (float)poly->GetMaterial()->GetAlpha();

	for (int i=0; i<poly->numClipVert; i++) {

		zCVertex* vt = poly->clipVert[i];
		v[i].oow = vt->vertCamSpaceZInv;
		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST; 

		v[i].tmuvtx[GR_TMU0].sow = 0;
		v[i].tmuvtx[GR_TMU0].tow = 0;

		v[i].r	 = 255.0F;
		v[i].g	 = 255.0F;
		v[i].b	 = 255.0F;
		v[i].a	 = alpha/255 * (float)poly->clipFeat[i]->lightDyn.GetAlphaByte();

	}

	for (i=0; i<poly->numClipVert-1; i++) grDrawLine(&v[i], &v[i+1]);
	grDrawLine(&v[poly->numClipVert-1],&v[0]);

}

inline void RenderPolyAlphaGouraud(const zCPolygon *poly)
{
	float mR,mG,mB;
	// precalc material color multiplicant
	
	mR = (float) poly->GetMaterial()->GetColor().GetRedByte()   * (1.0F/255.0F);
	mG = (float) poly->GetMaterial()->GetColor().GetGreenByte() * (1.0F/255.0F);
	mB = (float) poly->GetMaterial()->GetColor().GetBlueByte()  * (1.0F/255.0F);

	float alpha = (alphaSrc == zRND_ALPHA_SOURCE_CONSTANT) ? alpha = (float)actAlpha : alpha = (float)poly->GetMaterial()->GetAlpha();

	for (int i=0; i<poly->numClipVert; i++) {
		zCVertex* vt = poly->clipVert[i];
		v[i].oow = vt->vertCamSpaceZInv;
		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST; 

		v[i].tmuvtx[GR_TMU0].sow = 0;
		v[i].tmuvtx[GR_TMU0].tow = 0;

		zCVertFeature *feat=poly->clipFeat[i];

		v[i].r	 = (float)feat->lightDyn.GetRedByte()   * mR;
		v[i].g	 = (float)feat->lightDyn.GetGreenByte() * mG;
		v[i].b	 = (float)feat->lightDyn.GetBlueByte()  * mB;
		v[i].a	 = alpha/255 * (float)feat->lightDyn.GetAlphaByte();
	}

	grDrawPolygonVertexList(poly->numClipVert, v);


}

inline void RenderPolyAlphaTex(const zCPolygon *poly)
{
	// draw textured poly
	float alpha = (alphaSrc == zRND_ALPHA_SOURCE_CONSTANT) ? alpha = (float)actAlpha : alpha = (float)poly->GetMaterial()->GetAlpha();

	for (int i=0; i<poly->numClipVert; i++) {

		zCVertex* vt = poly->clipVert[i];

		v[i].x	 = vt->vertScrX + SNAPCONST; 
		v[i].y	 = vt->vertScrY + SNAPCONST; 
		v[i].oow = vt->vertCamSpaceZInv;

		zCVertFeature *feat=poly->clipFeat[i];

		v[i].r	 = (float)feat->lightDyn.GetRedByte();
		v[i].g	 = (float)feat->lightDyn.GetGreenByte();
		v[i].b	 = (float)feat->lightDyn.GetBlueByte();

		v[i].tmuvtx[GR_TMU0].sow = feat->texu * actTexture->scaleX * v[i].oow;
		v[i].tmuvtx[GR_TMU0].tow = feat->texv * actTexture->scaleY * v[i].oow;

		v[i].a	 = alpha/255 * (float)feat->lightDyn.GetAlphaByte();
	}

	grDrawPolygonVertexList(poly->numClipVert, v);
}


inline void DrawTransPoly(const zSRndGlide_AlphaPoly *tp)
{

	if (tp->tex) actTexture=(zCTex_RndGlide *)tp->tex; 
	else actTexture = 0;

	zTRnd_PolyDrawMode thisMode = tp->dMode;

	if ( actTexture  && (actTexture->zCResource::CacheIn() != zRES_CACHED_IN) ) thisMode = zRND_DRAW_FLAT;

	switch (thisMode)	{

	case (zRND_DRAW_MATERIAL):
	

		if (actTexture) {
			PolyTexCalcLargestLOD((zCPolygon*)tp->poly,actTexture);
			// texture changed, textured polygon
			if (!oldTexture) SetDrawMode(zCAM_DRAW_TEX);  // old state gouraud? -> yes -> set textured

			actTexture->Download();
			DrawTransPolyTex(tp);
		}
		else // no texture, state change gouraud
		{	
			SetDrawMode(zCAM_DRAW_FLAT);
			DrawTransPolyGouraud(tp);
		}

		oldTexture = actTexture;
		break;

	case zRND_DRAW_FLAT:
		SetDrawMode(zCAM_DRAW_FLAT); 
		DrawTransPolyGouraud(tp);
		oldTexture = 0;
		break;
	case zRND_DRAW_WIRE:
		SetDrawMode(zCAM_DRAW_WIRE); 
		DrawTransPolyWire(tp);
		oldTexture = 0;
		break;
	}

}


#endif