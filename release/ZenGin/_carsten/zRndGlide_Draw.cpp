#include "zcore.h"
#include "zRndGlide.h"
#include "zRndGlide_State.h"
#include "zRndGlide_Util.h"
#include "zRndGlide_Draw.h"

zBOOL					cacheAlphaPolys	= TRUE;
int						numAlphaPolys	= 0;
float					grBucketSize	= 0; 

zSRndGlide_AlphaPoly*	alphaPolyBucket[GR_MAXBUCKETS]; 
zSRndGlide_AlphaPoly	alphaPolyPool  [GR_MAXALPHAPOLYS];

static void BucketInsert( int bucketnumber, zSRndGlide_AlphaPoly*alphaPoly )
{
	int index = bucketnumber;
	if( bucketnumber>=GR_MAXBUCKETS )
		index = GR_MAXBUCKETS-1;
	if( bucketnumber<0 )
		index = 0;
	//Falls Bucket noch leer ...
	if( alphaPolyBucket[index]==NULL )
	{
		alphaPoly->next			= NULL;
		alphaPolyBucket[index]	= alphaPoly;
		return;
	}

	//Falls erster Bucket-Eintrag bereits zu klein ...
	if( alphaPolyBucket[index]->avgZ<=alphaPoly->avgZ )
	{
		alphaPoly->next			= alphaPolyBucket[index];
		alphaPolyBucket[index]	= alphaPoly;
		return;
	}
	//Ansonsten durchlaufe die Bucket-Einträge bis zur richtigen Position ...
	zSRndGlide_AlphaPoly*entry		= alphaPolyBucket[index];
	zSRndGlide_AlphaPoly*nextentry	= entry->next;

	while( 1 )
	{
		if( nextentry==NULL )
			break;
		if( nextentry->avgZ<=alphaPoly->avgZ)
			break;

		entry		= nextentry;
		nextentry	= entry->next;
	}
	// ... und füge das neue Element in die verkettete Liste ein
	entry->next		= alphaPoly;
	alphaPoly->next = nextentry;

	return;
}


// FIXME: hier ?
zBOOL zCRnd_Glide::GetCacheAlphaPolys	() const						
{ 
	return cacheAlphaPolys;	
};
void  zCRnd_Glide::SetCacheAlphaPolys	(const zBOOL b)					
{ 
	cacheAlphaPolys	= b;	
};


/********************************************************************************
 FUNCTION: Drawpoly
*********************************************************************************/
void zCRnd_Glide ::	DrawPoly(zCPolygon* poly) 
{
	trisRendered+=poly->numClipVert-2;
	polysRendered++;

#ifdef CHASE_DEBUG
	/*
	if (poly->GetMaterial()) {
		if (poly->GetMaterial()->GetTexture()) {
			if (poly->GetMaterial()->GetTexture()->GetName().Search("BLA.TGA") != -1) {
				int brk = 0;
			}
		}
	}*/
#endif

    PolyDrawFunc(poly);
}	

void zCRnd_Glide ::	DrawPolyList(int numPoly, zCPolygon** polyList) 
{
	for (int i=0; i<numPoly; i++) {
		trisRendered+=polyList[i]->numClipVert-2;
		polysRendered++;
		PolyDrawFunc(polyList[i]);
	};
};

void zCRnd_Glide ::	DrawPolySimple		(zCTexture	*texture, zTRndSimpleVertex *vertex, int numVert)
{
	if (!texture) return;

	SetDrawMode (zCAM_DRAW_TEX		);
	SetAlphaFunc(GetAlphaBlendFunc());
	
	if (texture->HasAlpha()) 
	{
		if ( GetAlphaBlendFunc() == zRND_ALPHA_FUNC_NONE || GetAlphaBlendFunc() == zRND_ALPHA_FUNC_MAT_DEFAULT ) 
		{
			SetAlphaFunc(zRND_ALPHA_FUNC_BLEND);
		}

		SetAlphaSource(TRUE);
	}

	actTexture = static_cast<zCTex_RndGlide*>(texture);

	actTexture->Download();


	for (int i=0; i<numVert; i++) 
	{
		assert(vertex[i].pos[VX] < vid_xdim && vertex[i].pos[VX]>=0);
		assert(vertex[i].pos[VY] < vid_ydim && vertex[i].pos[VY]>=0);

		v[i].x	 = vertex[i].pos[VX] + SNAPCONST;
		v[i].y	 = vertex[i].pos[VY] + SNAPCONST; 

		v[i].x	 -= SNAPCONST;
		v[i].y	 -= SNAPCONST;

		v[i].oow = 1/vertex[i].z;

		v[i].r	 = (float)vertex[i].color.GetRedByte();
		v[i].g	 = (float)vertex[i].color.GetGreenByte();
		v[i].b	 = (float)vertex[i].color.GetBlueByte();

		v[i].tmuvtx[GR_TMU0].sow = vertex[i].uv[VX] * actTexture->scaleX * v[i].oow ;
		v[i].tmuvtx[GR_TMU0].tow = vertex[i].uv[VY] * actTexture->scaleY * v[i].oow ;

		v[i].a	 = (float)vertex[i].color.GetAlphaByte();

	}
	guDrawPolygonVertexListWithClip(numVert, v); 

	oldTexture = actTexture;

};


void zCRnd_Glide::DrawLightmapList	(zCPolygon** polyList, int numPoly)
{
	for (int i=0; i<numPoly; i++) 	PolyDrawTwoPassLightMapInlined(polyList[i]);
	lightMapsRendered = numPoly;
}


void zCRnd_Glide :: SetPixel (float x,float y,const zCOLOR col)
{
	p[0].r = (float) col.GetRedByte();
	p[0].g = (float) col.GetGreenByte();
	p[0].b = (float) col.GetBlueByte();
	p[0].x = (float) x;  
	p[0].y = (float) y;
	grConstantColorValue(255); 

	// check render state & decide how to draw the pixel
    if (lfbLoop) grDrawPoint(&p[0]);
	else {
		zTRnd_PolyDrawMode mode = GetPolyDrawMode();
		SetPolyDrawMode ( zRND_DRAW_FLAT );
		grDrawPoint(&p[0]);
		SetPolyDrawMode ( mode );
	}

};

void zCRnd_Glide :: DrawLine ( float a, float b, float c, float d, const zCOLOR col)
{	
	GrState state; 

	grGlideGetState(&state);

	grColorCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE);

	grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE );

	grAlphaBlendFunction(GR_BLEND_SRC_ALPHA,GR_BLEND_ONE_MINUS_SRC_ALPHA,
						 GR_BLEND_ZERO,GR_BLEND_ZERO);            

	p[0].r = (float) col.GetRedByte();
	p[0].g = (float) col.GetGreenByte();
	p[0].b = (float) col.GetBlueByte();
	p[1].r = (float) col.GetRedByte();
	p[1].g = (float) col.GetGreenByte();
	p[1].b = (float) col.GetBlueByte();
	p[0].x = (float) a;
	p[0].y = (float) b;
	p[1].x = (float) c;
	p[1].y = (float) d;

	grDrawLine(&p[0],&p[1]);

	grGlideSetState(&state); // tmp
	
}

// DrawLineZ: Draws a z-buffered line from a to b. a and b should be in screen space
void zCRnd_Glide::DrawLineZ(float x1Scr,float y1Scr,float z1CamSpaceInv,
							float x2Scr,float y2Scr,float z2CamSpaceInv,const zCOLOR col)
{
	
	GrState state; 

	grGlideGetState(&state);

	grColorCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE);

	grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE );

	grAlphaBlendFunction(GR_BLEND_SRC_ALPHA,GR_BLEND_ONE_MINUS_SRC_ALPHA,
						 GR_BLEND_ZERO,GR_BLEND_ZERO);            

	v[0].oow = z1CamSpaceInv;
	v[0].x	 = x1Scr + SNAPCONST; 
	v[0].y	 = y1Scr + SNAPCONST; 
	v[0].x	 -= SNAPCONST; 
	v[0].y	 -= SNAPCONST; 
	v[0].tmuvtx[GR_TMU0].sow = 0;

	v[0].r = (float) col.GetRedByte();
	v[0].g = (float) col.GetGreenByte();
	v[0].b = (float) col.GetBlueByte();
	v[0].a = 255;
	
	v[1].oow = z2CamSpaceInv;
	v[1].x	 = x2Scr + SNAPCONST; 
	v[1].y	 = y2Scr + SNAPCONST; 
	v[1].x	 -= SNAPCONST; 
	v[1].y	 -= SNAPCONST; 
	v[1].tmuvtx[GR_TMU0].sow = 0;
	

	v[1].r = (float) col.GetRedByte();
	v[1].g = (float) col.GetGreenByte();
	v[1].b = (float) col.GetBlueByte();
	v[1].a = 255;

	grDrawLine(&v[0],&v[1]);
	grGlideSetState(&state);

}



void PolyDrawAlphaImmediate(zCPolygon *poly)
{
	zTRnd_AlphaBlendFunc	func;
	GrColor_t				alpha;

	zCMaterial *mat = poly->GetMaterial();

	if ( alphaSrc == zRND_ALPHA_SOURCE_CONSTANT ) {
 		alpha = actAlpha; 
		grConstantColorValue( alpha );
	}
	else {
		alpha = mat->GetAlpha();
	}

	if ( alphaBlendFunc == zRND_ALPHA_FUNC_MAT_DEFAULT ) func = mat->GetAlphaBlendFunc(); 
	else func = alphaBlendFunc;

	zCTex_RndGlide *tex = (zCTex_RndGlide *) mat->GetAniTexture();


	if (tex) SetAlphaSource(tex->HasAlpha()); else SetAlphaSource(FALSE);

	SetAlphaFunc		( zRND_ALPHA_FUNC_BLEND ); 
	if ( tex && tex-> HasAlpha() && ( func == zRND_ALPHA_FUNC_NONE  ) ){
			 SetAlphaFunc		( zRND_ALPHA_FUNC_BLEND ); 
	}
	else SetAlphaFunc		( func );

	zTRnd_PolyDrawMode thisMode = pDrawMode;
	
	if ( actTexture && (actTexture->zCResource::CacheIn() != zRES_CACHED_IN) ) thisMode = zRND_DRAW_FLAT;

	switch (thisMode)	{

	case (zRND_DRAW_MATERIAL):
		actTexture = tex;

		if (actTexture) {  // no tex-change
			PolyTexCalcLargestLOD(poly,actTexture);

			// texture changed, textured polygon
			if(!oldTexture) SetDrawMode(zCAM_DRAW_TEX);  // old state gouraud? -> yes -> set textured

			actTexture->Download();  // Hmm, only needed once per frame & texture
 
			RenderPolyAlphaTex(poly);
		} 
		else {	
			// no texture, draw gouraud
			SetDrawMode(zCAM_DRAW_FLAT);
			RenderPolyAlphaGouraud(poly);
		}

		oldTexture = actTexture;
		break;

	case zRND_DRAW_FLAT:
		SetDrawMode(zCAM_DRAW_FLAT); 
		RenderPolyAlphaGouraud(poly);
		oldTexture = 0;
		break;
	case zRND_DRAW_WIRE:
		SetDrawMode(zCAM_DRAW_WIRE); 
		RenderPolyAlphaWire(poly);
		oldTexture = 0;
		break;
	}

}

void PolyDrawOnePassVertLight(zCPolygon *poly)
{
	zTRnd_AlphaBlendFunc	func;
	GrColor_t				alpha;

	zCMaterial	   *mat = poly->GetMaterial();
	zCTex_RndGlide *tex = (zCTex_RndGlide *) mat->GetAniTexture();

	func  = mat->GetAlphaBlendFunc(); 
	alpha = mat->GetAlpha();
	// Check if we can immediately render the polygon (no blending / no alpha)
	if ( (func == zRND_ALPHA_FUNC_NONE) && !(tex && tex->HasAlpha()) ) {
		grConstantColorValue(255);
		SetAlphaFunc( func );
		actTexture=tex;

		zTRnd_PolyDrawMode thisMode = pDrawMode;
	
		if ( actTexture && (actTexture->zCResource::CacheIn() != zRES_CACHED_IN) ) thisMode = zRND_DRAW_FLAT;

		switch (thisMode)	{

		case (zRND_DRAW_MATERIAL):
		

			if (actTexture) {
				PolyTexCalcLargestLOD(poly,actTexture);
				// texture changed, textured polygon
				if (!oldTexture) SetDrawMode(zCAM_DRAW_TEX);  // old state gouraud? -> yes -> set textured

				actTexture->Download();
				RenderPoly1PassVertLightTex(poly);
			}
			else // no texture, state change gouraud
			{	
				SetDrawMode(zCAM_DRAW_FLAT);
				RenderPoly1PassVertLightGouraud(poly);
			}
			oldTexture = actTexture;
			break;
		case zRND_DRAW_FLAT:
			SetDrawMode(zCAM_DRAW_FLAT);
			RenderPoly1PassVertLightGouraud(poly);
			oldTexture = 0;
			break;
		case zRND_DRAW_WIRE:
			SetDrawMode(zCAM_DRAW_WIRE);
			DrawPolyWire(poly);
			oldTexture = 0;
			break;
		}
		return;
	}

	if (!cacheAlphaPolys) { 
		PolyDrawAlphaImmediate(poly);
		return;
	}
	
	// nope : So put the polys to be blended in an array and flush'em later

	if( numAlphaPolys>=GR_MAXALPHAPOLYS ) return;

	zSRndGlide_AlphaPoly *TP = &alphaPolyPool[numAlphaPolys];

	TP->alpha		= alpha;
	TP->alpFunc		= func;
	TP->dMode		= pDrawMode;
	TP->ccEnabled	= cc;
	TP->cCol		= chromaColor;
	TP->poly		= (void *)poly;
	TP->mat			= mat;
	TP->tex			= tex;
	TP->lightMap	= 0;
	TP->avgZ		= 0;

	// copy vertices which can change several times per frame and transp. poly
	TP->numClipVert	= poly->numClipVert;
	
	for (int i=0; i< poly->numClipVert; i++) {
		float zInv = poly->clipVert[i]->vertCamSpaceZInv;
		TP->vertCamSpaceZInv[i]= zInv;
		TP->vertScrX[i]		   = poly->clipVert[i]->vertScrX;
		TP->vertScrY[i]	       = poly->clipVert[i]->vertScrY;
		TP->texu[i]			   = poly->clipFeat[i]->texu;
		TP->texv[i]			   = poly->clipFeat[i]->texv;
		TP->lightDyn[i]	       = poly->clipFeat[i]->lightDyn;
		TP->avgZ			  += zInv;
	}

	TP->avgZ		= TP->numClipVert/TP->avgZ;

	BucketInsert( zFloat2IntFloor( TP->avgZ/grBucketSize ), TP ); 

	numAlphaPolys++;
}

void PolyDrawOnePassMultiTex(zCPolygon *poly)
{
	PolyDrawOnePassVertLight(poly);
}

void PolyDrawTwoPassTexture(zCPolygon *poly)
{
	zTRnd_AlphaBlendFunc	func;
	GrColor_t				alpha;

	zCMaterial	   *mat = poly->GetMaterial();
	zCTex_RndGlide *tex = (zCTex_RndGlide *) mat->GetAniTexture();

	func  = mat->GetAlphaBlendFunc(); 
	alpha = mat->GetAlpha();
	
	// Check if we can immediately render the polygon (no blending / no alpha)
	if ( (func == zRND_ALPHA_FUNC_NONE)  && !(tex && tex->HasAlpha()) ) {
		grConstantColorValue(255);
		SetAlphaFunc( func );
		actTexture=tex;

		zTRnd_PolyDrawMode thisMode = pDrawMode;
	
		if ( actTexture && (actTexture->zCResource::CacheIn() != zRES_CACHED_IN) ) thisMode = zRND_DRAW_FLAT;

		switch (thisMode)	{
		case (zRND_DRAW_MATERIAL):
			if (actTexture) {  // no tex-change
				PolyTexCalcLargestLOD(poly,actTexture);
				// texture changed, textured polygon
				if (!oldTexture) SetDrawMode(zCAM_DRAW_TEX);  // old state gouraud? -> yes -> set textured
				actTexture->Download();  // Hmm, only needed once per frame & texture
				RenderPoly2PassTextureTex(poly);
			} 
			else {	
				// no texture, state change gouraud
				SetDrawMode(zCAM_DRAW_FLAT);
				RenderPoly2PassTextureGouraud(poly);
			}
			oldTexture = actTexture;
			break;
		case zRND_DRAW_FLAT:
			SetDrawMode(zCAM_DRAW_FLAT);
			RenderPoly2PassTextureGouraud(poly);
			oldTexture = 0;
			break;
		case zRND_DRAW_WIRE:
			SetDrawMode(zCAM_DRAW_WIRE);
			DrawPolyWire(poly);
			oldTexture = 0;
			break;
		}

		return;
	}

	if ( actTexture && actTexture->CacheIn()!=zRES_CACHED_IN ) return;

	if (!cacheAlphaPolys) { 
		PolyDrawAlphaImmediate(poly);
		return;
	}

	// nope : So put the polys to be blended in an array and flush'em later
	if( numAlphaPolys>=GR_MAXALPHAPOLYS ) return;

	zSRndGlide_AlphaPoly *TP = &alphaPolyPool[numAlphaPolys];

	TP->alpha		= alpha;
	TP->alpFunc		= func;
	TP->dMode		= pDrawMode;
	TP->ccEnabled	= cc;
	TP->cCol		= chromaColor;
	TP->poly		= (void *)poly;
	TP->mat			= mat;
	TP->tex			= tex;
	TP->lightMap	= 0;
	TP->avgZ		= 0;

	// copy vertices which can change several times per frame and transp. poly
	TP->numClipVert	= poly->numClipVert;
	
	for (int i=0; i< poly->numClipVert; i++) {
		float zInv = poly->clipVert[i]->vertCamSpaceZInv;
		TP->vertCamSpaceZInv[i]= zInv;
		TP->vertScrX[i]		   = poly->clipVert[i]->vertScrX;
		TP->vertScrY[i]	       = poly->clipVert[i]->vertScrY;
		TP->texu[i]			   = poly->clipFeat[i]->texu;
		TP->texv[i]			   = poly->clipFeat[i]->texv;
		TP->lightDyn[i]	       = poly->clipFeat[i]->lightDyn;
		TP->avgZ			  += zInv;
	}

	TP->avgZ		= TP->numClipVert/TP->avgZ;

	BucketInsert( zFloat2IntFloor( TP->avgZ/grBucketSize ), TP ); 

	numAlphaPolys++;

}
void PolyDrawTwoPassLightMap(zCPolygon *poly) 
{
	PolyDrawTwoPassLightMapInlined(poly);
}



void PolyDrawVobDynVertLight(zCPolygon *poly)
{
	zTRnd_AlphaBlendFunc	func;
	GrColor_t				alpha;

	zCMaterial *mat = poly->GetMaterial();
	zBOOL	texOpaque = TRUE;

	if ( alphaSrc == zRND_ALPHA_SOURCE_CONSTANT ) {
 		alpha = actAlpha; 
	}
	else alpha = mat->GetAlpha();

	if ( alphaBlendFunc == zRND_ALPHA_FUNC_MAT_DEFAULT ) func = mat->GetAlphaBlendFunc(); 
	else func = alphaBlendFunc;

	zCTex_RndGlide *tex = (zCTex_RndGlide *) mat->GetAniTexture();
	// FIXME: Wenn das atr File noch nicht geladen ist, ist der tex-alpha-state
	// hier unbekannt
	if (tex && tex->HasAlpha()) texOpaque = FALSE;

	// Check if we can immediately render the polygon (no blending / no alpha)
	if ( (func == zRND_ALPHA_FUNC_NONE)  && texOpaque ) {
		grConstantColorValue(255);
		SetAlphaFunc( func );

		actTexture=tex;

		zTRnd_PolyDrawMode thisMode = pDrawMode;

		if ( actTexture && (actTexture->zCResource::CacheIn() != zRES_CACHED_IN) ) thisMode = zRND_DRAW_FLAT;

		switch (thisMode)	{

		case (zRND_DRAW_MATERIAL):

			if (actTexture) {  // no tex-change
				PolyTexCalcLargestLOD(poly,actTexture);

				// texture changed, textured polygon
				if(!oldTexture) SetDrawMode(zCAM_DRAW_TEX);  // old state gouraud? -> yes -> set textured
				actTexture->Download();  // Hmm, only needed once per frame & texture
				RenderPolyVobDynVertLightTex(poly);
			} 
			else // no texture, draw gouraud
			{	
				SetDrawMode(zCAM_DRAW_FLAT);
				RenderPolyVobDynVertLightGouraud(poly);
			}

			oldTexture = actTexture;
			break;

		case zRND_DRAW_FLAT:
			SetDrawMode(zCAM_DRAW_FLAT); 
			RenderPolyVobDynVertLightGouraud(poly);
			oldTexture = 0;
			break;
		case zRND_DRAW_WIRE:
			SetDrawMode(zCAM_DRAW_WIRE); 
			DrawPolyWire(poly);
			oldTexture = 0;
			break;
		}

		return;
	}
	
	if ( actTexture && actTexture->CacheIn()!=zRES_CACHED_IN ) return;

	if (!cacheAlphaPolys) { 
		PolyDrawAlphaImmediate(poly);
		return;
	}
	// nope : So put the polys to be blended in an array and flush'em later
	if( numAlphaPolys>=GR_MAXALPHAPOLYS ) return;

	zSRndGlide_AlphaPoly *TP = &alphaPolyPool[numAlphaPolys];

	TP->alpha		= alpha;
	TP->alpFunc		= func;
	TP->dMode		= pDrawMode;
	TP->ccEnabled	= cc;
	TP->cCol		= chromaColor;
	TP->poly		= (void *)poly;
	TP->mat			= mat;
	TP->tex			= tex;
	TP->lightMap	= 0;
	TP->avgZ		= 0;

	// copy vertices which can change several times per frame and transp. poly
	TP->numClipVert	= poly->numClipVert;
	
	for (int i=0; i< poly->numClipVert; i++) {
		float zInv = poly->clipVert[i]->vertCamSpaceZInv;
		TP->vertCamSpaceZInv[i]= zInv;
		TP->vertScrX[i]		   = poly->clipVert[i]->vertScrX;
		TP->vertScrY[i]	       = poly->clipVert[i]->vertScrY;
		TP->texu[i]			   = poly->clipFeat[i]->texu;
		TP->texv[i]			   = poly->clipFeat[i]->texv;
		TP->lightDyn[i]	       = poly->clipFeat[i]->lightDyn;
		TP->avgZ			  += zInv;
	}

	TP->avgZ		= TP->numClipVert/TP->avgZ;

	BucketInsert( zFloat2IntFloor( TP->avgZ/grBucketSize ), TP ); 

	numAlphaPolys++;
}

void zCRnd_Glide :: FlushPolys()
{		
	
	zTCam_DrawMode			dMode			= GetDrawMode		();
	zTRnd_AlphaBlendFunc	aFunc			= GetAlphaFunc		();
	zTRnd_BilerpFilterMode	filtMode		= GetBilerpFiltering();
	zTRnd_DitherMode		dithMode		= GetDithering		();
	zBOOL					abSource		= GetAlphaSource	();
	
	grDepthMask(FXFALSE);
	
	SetBilerpFiltering	( zRND_BILERP_FILTER_ON );
	SetDithering		( zRND_DITHER_OFF ); 

	zSRndGlide_AlphaPoly *TP;
	zCTex_RndGlide *tex;

    for( int i = GR_MAXBUCKETS-1; i>=0; i-- )
	while( alphaPolyBucket[i]!=NULL )
	{
		TP = alphaPolyBucket[i];
		tex = (zCTex_RndGlide *)TP->tex;
		if (tex) SetAlphaSource(tex->HasAlpha()); else SetAlphaSource(FALSE);

		if ( tex && tex->HasAlpha() && (TP->alpFunc == zRND_ALPHA_FUNC_NONE  ) ){
			 SetAlphaFunc		( zRND_ALPHA_FUNC_BLEND ); 
		}
		else SetAlphaFunc		( TP->alpFunc );

		grConstantColorValue( (GrColor_t) TP->alpha );

		DrawTransPoly( TP ); 

		alphaPolyBucket[i] = TP->next; 
	}

	grDepthMask(FXTRUE);
	grConstantColorValue(255);
	SetDrawMode			(dMode);
	SetAlphaFunc		(aFunc);
	SetBilerpFiltering	(filtMode);
	SetDithering		(dithMode);
	SetAlphaSource		(abSource);

	numAlphaPolys = 0;

}


