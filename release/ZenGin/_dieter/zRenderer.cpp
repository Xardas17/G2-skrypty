/******************************************************************************** 
 
     $Workfile:: zRenderer.cpp        $                $Date:: 12.02.01 17:51   $
     $Revision:: 17                   $             $Modtime:: 12.02.01 17:51   $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zRenderer.cpp $
 * 
 * 17    12.02.01 17:51 Hildebrandt
 * 
 * 16    13.11.00 23:00 Pelzer
 * 
 * 15    4.10.00 17:16 Hildebrandt
 * 
 * 14    28.09.00 19:18 Hildebrandt
 * 
 * 13    31.08.00 17:04 Hildebrandt
 * 
 * 12    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 11    6.07.00 13:45 Hildebrandt
 * 
 * 7     10.05.00 3:55 Hildebrandt
 * 
 * 6     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 5     8.05.00 2:17 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 *  
 * 6     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 5     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 17 $ ($Modtime: 12.02.01 17:51 $)


#include <zCore.h>
#include <zRenderer.h>
#include <zTexture.h>

#ifdef ZENGINE_DEBUG
//	#define zDEBUG_SHOW_TILE_QUADS 
#endif

zCRenderer *zrenderer=0; 

zTRnd_AlphaBlendFunc zCRenderer::AlphaBlendFuncStringToType	(const zSTRING& s) const 
{
	zTRnd_AlphaBlendFunc res = zRND_ALPHA_FUNC_NONE;
	if (s.Search("MAT_DEFAULT"	)!=-1) res = zRND_ALPHA_FUNC_MAT_DEFAULT;	else
	if (s.Search("NONE"			)!=-1) res = zRND_ALPHA_FUNC_NONE;			else
	if (s.Search("BLEND"		)!=-1) res = zRND_ALPHA_FUNC_BLEND;			else
	if (s.Search("ADD"			)!=-1) res = zRND_ALPHA_FUNC_ADD;			else
	if (s.Search("SUB"			)!=-1) res = zRND_ALPHA_FUNC_SUB;			else
	if (s.Search("MUL"			)!=-1) res = zRND_ALPHA_FUNC_MUL;			else
	if (s.Search("MUL2"			)!=-1) res = zRND_ALPHA_FUNC_MUL2;

	return res;
};

zSTRING zCRenderer::AlphaBlendFuncTypeToString	(const zTRnd_AlphaBlendFunc func) const 
{
	zSTRING res;
	switch (func) {
		case zRND_ALPHA_FUNC_MAT_DEFAULT: res = "MAT_DEFAULT";	break;
		case zRND_ALPHA_FUNC_NONE		: res = "NONE";			break;
		case zRND_ALPHA_FUNC_BLEND		: res = "BLEND";		break;
		case zRND_ALPHA_FUNC_ADD		: res = "ADD";			break;
		case zRND_ALPHA_FUNC_SUB		: res = "SUB";			break;
		case zRND_ALPHA_FUNC_MUL		: res = "MUL";			break;
		default							: res = "NONE";			break;
	};

	return res;
};

zBOOL zCRenderer::Vid_SetMode (int newXDim, int newYDim, int newBpp, zTSystemContextHandle* initContextHandle)
{
	// convience: searches modeList for best matching mode
	zTRnd_VidModeInfo	info;
	int					bestMode	= -1;
	int					bestError	= 99999999;
	for (int i=0; i<Vid_GetNumModes(); i++) 
	{
		Vid_GetModeInfo (info, i);
		if (info.bpp==newBpp)
		{
			int error = (info.xdim-newXDim)*(info.xdim-newXDim) + (info.ydim-newYDim)*(info.ydim-newYDim);
			if (error<bestError) 
			{
				bestMode	= i;
				bestError	= error;
			};
		};
	};
	if (bestMode<0) {
		return FALSE;
	} else {
		Vid_SetMode (bestMode, initContextHandle);
		return TRUE;
	};
}; 

/*		zRND_TEX_FORMAT_ARGB_8888,				// 32, alpha 8
		zRND_TEX_FORMAT_ABGR_8888,				// 32, alpha 8
		zRND_TEX_FORMAT_RGBA_8888,				// 32, alpha 8
		zRND_TEX_FORMAT_BGRA_8888,				// 32, alpha 8
		
		zRND_TEX_FORMAT_RGB_888,				// 24
		zRND_TEX_FORMAT_BGR_888,				// 24
		
		zRND_TEX_FORMAT_ARGB_4444,				// 16, alpha 4
		zRND_TEX_FORMAT_ABGR_4444,				// 16, alpha 4
		zRND_TEX_FORMAT_RGBA_4444,				// 16, alpha 4
		zRND_TEX_FORMAT_BGRA_4444,				// 16, alpha 4
		
		zRND_TEX_FORMAT_ARGB_1555,				//	 , alpha 1
		zRND_TEX_FORMAT_ABGR_1555,				//	 , alpha 1
		zRND_TEX_FORMAT_RGBA_5551,				//	 , alpha 1
		zRND_TEX_FORMAT_BGRA_5551,				//	 , alpha 1
		
		zRND_TEX_FORMAT_RGB_565,				
		zRND_TEX_FORMAT_BGR_565,				
		
		zRND_TEX_FORMAT_PAL_8,					// 8
		zRND_TEX_FORMAT_S3TC,					// 4
*/


// <=> zTexture.cpp 'texNextBestTexFormat'
zTRnd_TexFormatInfo texFormatInfoList[zRND_TEX_FORMAT_COUNT]=
{
	//	bpp,	rpos,	gpos,	bpos,	apos,	rsize,	gsize,	bsize,	aSize
	{	4.0F,		8,		16,		24,		0,		8,		8,		8,		8},		// argb_8888
	{	4.0F,		24,		16,		8,		0,		8,		8,		8,		8},		// abgr_8888
	{	4.0F,		0,		8,		16,		24,		8,		8,		8,		8},		// rgba_8888
	{	4.0F,		16,		8,		0,		24,		8,		8,		8,		8},		// bgra_8888

	{	3.0F,		0,		8,		16,		0,		8,		8,		8,		0},		// rgb_888
	{	3.0F,		16,		8,		0,		0,		8,		8,		8,		0},		// bgr_888

	{	2.0F,		8,		4,		0,		12,		4,		4,		4,		4},		// argb_4444
	{	2.0F,		10,		5,		0,		15,		5,		5,		5,		1},		// argb_1555
	{	2.0F,		11,		5,		0,		0,		5,		6,		5,		0},		// rgb_565

	{	1.0F,		0,		0,		0,		0,		0,		0,		0,		0},		// PAL_8

	{	0.5F,		0,		0,		0,		0,		0,		0,		0,		0},		// DXT1
	{	1.0F,		0,		0,		0,		0,		0,		0,		0,		0},		// DXT2
	{	1.0F,		0,		0,		0,		0,		0,		0,		0,		1},		// DXT3
	{	1.0F,		0,		0,		0,		0,		0,		0,		0,		0},		// DXT4
	{	1.0F,		0,		0,		0,		0,		0,		0,		0,		0}		// DXT5
};

zTRnd_TexFormatInfo zCRenderer::GetTexFormatInfo (const zTRnd_TextureFormat texFormat) const
{
	return texFormatInfoList[texFormat];
};

static inline void GetSliceXY (int &sliceX, int &sliceY, const zVEC2& uv, int numSlicesX, int numSlicesY)
{
	sliceX = zMin (numSlicesX-1, zFloat2Int(zFloor(uv[0] * zREAL(numSlicesX))));
	sliceY = zMin (numSlicesY-1, zFloat2Int(zFloor(uv[1] * zREAL(numSlicesY))));
};

static inline zBOOL ClipTileVertList (zTRndSimpleVertex *tileVert)
{
	// Hier werden nur die Verts 0 und 2 der tileVert List betrachtet (Rest sind abhaengige Verts)

	// triv out
	if ((tileVert[0].pos[VX]>=zrenderer->vid_xdim) ||
		(tileVert[0].pos[VY]>=zrenderer->vid_ydim) ||
		(tileVert[2].pos[VX]< 0) ||
		(tileVert[2].pos[VY]< 0))
		return FALSE;		// ausserhalb des Screens

	// clip
	const zVEC2 screenDim	= zVEC2(zREAL(zrenderer->vid_xdim-1),zREAL(zrenderer->vid_ydim-1));	// -1 !
	for (int i=0; i<2; i++)
	{
		if (tileVert[0].pos[i]<0)	{
			zREAL a				= tileVert[0].pos[i];
			zREAL b				= tileVert[2].pos[i];
			zREAL clipFrac		= (0-a) / (b-a);
			tileVert[0].pos[i]	= 0;
			tileVert[0].uv [i]	= zLerp (clipFrac, tileVert[0].uv[i], tileVert[2].uv[i]);
		};

		if (tileVert[2].pos[i]>screenDim[i])	{
			zREAL a				= tileVert[0].pos[i];
			zREAL b				= tileVert[2].pos[i];
			zREAL clipFrac		= (screenDim[i]-a) / (b-a);
			tileVert[2].pos[i]	= screenDim[i];
			tileVert[2].uv [i]	= zLerp (clipFrac, tileVert[0].uv[i], tileVert[2].uv[i]);
		};
	};
	return TRUE;
};

#ifdef zDEBUG_SHOW_TILE_QUADS
	#include <z3d.h>
#endif

void zCRenderer::DrawTile		(   zCTexture		*texture,
									const zVEC2&	posMin,
									const zVEC2&	posMax,
									const zREAL		zValue,
									const zVEC2&	uvMin,
									const zVEC2&	uvMax,
									const zCOLOR	color)
{
	//
	static zTRndSimpleVertex tileVert[4];

	//
	int numSlicesX = 0;
	int numSlicesY = 0;
	if (texture)	{
		texture->CacheIn(-1);
		numSlicesX = texture->GetNumAniFrames (0);
		numSlicesY = texture->GetNumAniFrames (1);
	};

	//
	for (int i=0; i<4; i++) {
		tileVert[i].z		= zValue;
		tileVert[i].color	= color;
	};

	// shortcut, falls die Texture keine Slicing braucht.
	if ((!texture) || (!texture->IsTextureTile()) || ((numSlicesX==0) && (numSlicesY==0))) {
		tileVert[0].pos		= posMin;
		tileVert[0].uv		= uvMin;
		tileVert[2].pos		= posMax;
		tileVert[2].uv		= uvMax;

		if (ClipTileVertList(tileVert)) {
			// abhaengige Verts erzeugen
			tileVert[3].pos[0]	= tileVert[2].pos[0];
			tileVert[3].pos[1]	= tileVert[0].pos[1];
			tileVert[3].uv[0]	= tileVert[2].uv [0];
			tileVert[3].uv[1]	= tileVert[0].uv [1];

			tileVert[1].pos[0]	= tileVert[0].pos[0];
			tileVert[1].pos[1]	= tileVert[2].pos[1];
			tileVert[1].uv[0]	= tileVert[0].uv [0];
			tileVert[1].uv[1]	= tileVert[2].uv [1];
			DrawPolySimple		(texture, &tileVert[0], 4);
		};
		return;
	};

	//
	// clipping, slicing
	//

	int startSliceX, startSliceY;
	int numWalkSlicesX, numWalkSlicesY;
	GetSliceXY				(startSliceX		, startSliceY	, uvMin, numSlicesX, numSlicesY);
	GetSliceXY				(numWalkSlicesX	, numWalkSlicesY, uvMax, numSlicesX, numSlicesY);
	numWalkSlicesX			= (numWalkSlicesX - startSliceX) + 1;
	numWalkSlicesY			= (numWalkSlicesY - startSliceY) + 1;

	//
	const zVEC2 sliceUVMin	= Alg_Prod (uvMin, zVEC2(zREAL(numSlicesX), zREAL(numSlicesY)));
	const zVEC2 sliceUVMax	= Alg_Prod (uvMax, zVEC2(zREAL(numSlicesX), zREAL(numSlicesY)));

	// Texture Wrap ausschalten
	const zBOOL texWrapEnabled = zrenderer->GetTextureWrapEnabled();
	zrenderer->SetTextureWrapEnabled (FALSE);

	//
	zVEC2 fullSliceDim;
	for (i=0; i<2; i++)
		fullSliceDim[i]	= (posMax[i]-posMin[i]) / (sliceUVMax[i]-sliceUVMin[i]);

	//
	zCTexture	*actTexture;
	zVEC2		uvMinAct;
	zVEC2		uvMaxAct;
	zVEC2		posMinAct;
	zVEC2		posMaxAct;
	posMinAct[VY]	= posMin[VY];

	for (int y=0; y<numWalkSlicesY; y++)
	{
		//
		if (y==0) {
			uvMinAct[VY]	= sliceUVMin[VY] - zFloor(sliceUVMin[VY]);
			zREAL ceil		= zCeil(sliceUVMin[VY]);	if (ceil==sliceUVMin[VY]) ceil +=1;
			zREAL frac		= (ceil - sliceUVMin[VY]) / (sliceUVMax[VY]-sliceUVMin[VY]);
			if (frac==0)	frac=1;
			posMaxAct[VY]	= zLerp (frac, posMin[VY], posMax[VY]);
		} else {
			uvMinAct[VY]	= 0;
			posMaxAct[VY]	+= fullSliceDim[VY];
		};

		//
		if (y==(numWalkSlicesY-1))	{
			uvMaxAct[VY]	= sliceUVMax[VY];
			while (uvMaxAct[VY]>1)	uvMaxAct[VY] -= 1;
			posMaxAct[VY]	= posMax[VY];
		} else									
			uvMaxAct[VY]	= 1;

		posMinAct[VX]	= posMin[VX];
		for (int x=0; x<numWalkSlicesX; x++)
		{
			//
			if (x==0) {
				uvMinAct[VX]	= sliceUVMin[VX] - zFloor(sliceUVMin[VX]);
				zREAL ceil		= zCeil(sliceUVMin[VX]);	if (ceil==sliceUVMin[VX]) ceil +=1;
				zREAL frac		= (ceil - sliceUVMin[VX]) / (sliceUVMax[VX]-sliceUVMin[VX]);
				if (frac==0)	frac=1;
				posMaxAct[VX]	= zLerp (frac, posMin[VX], posMax[VX]);
			} else {
				uvMinAct[VX]	= 0;
				posMaxAct[VX]	+= fullSliceDim[VX];
			};

			//
			if (x==(numWalkSlicesX-1))	{
				uvMaxAct[VX]	= sliceUVMax[VX];
				while (uvMaxAct[VX]>1)	uvMaxAct[VX] -= 1;
				posMaxAct[VX]	= posMax[VX];
			} else									
				uvMaxAct[VX]	= 1;

			//
			tileVert[0].pos		= posMinAct;
			tileVert[0].uv		= uvMinAct;
			tileVert[2].pos		= posMaxAct;
			tileVert[2].uv		= uvMaxAct;

			//
			posMinAct[VX]		= posMaxAct[VX];

			if (!ClipTileVertList (tileVert)) continue;

			// abhaengige Verts erzeugen
			tileVert[3].pos[0]	= tileVert[2].pos[0];
			tileVert[3].pos[1]	= tileVert[0].pos[1];
			tileVert[3].uv[0]	= tileVert[2].uv [0];
			tileVert[3].uv[1]	= tileVert[0].uv [1];

			tileVert[1].pos[0]	= tileVert[0].pos[0];
			tileVert[1].pos[1]	= tileVert[2].pos[1];
			tileVert[1].uv[0]	= tileVert[0].uv [0];
			tileVert[1].uv[1]	= tileVert[2].uv [1];

			//
			texture->SetActAniFrame (0, x+startSliceX);
			texture->SetActAniFrame (1, y+startSliceY);
			actTexture			= texture->GetAniTexture ();

			// rendern
			DrawPolySimple		(actTexture, &tileVert[0], 4);

#ifdef zDEBUG_SHOW_TILE_QUADS
			zCOLOR col(0,0,255,255);
/*			zrenderer->DrawLine (tileVert[0].pos[VX],tileVert[0].pos[VY],
								 tileVert[2].pos[VX],tileVert[2].pos[VY], col);
			zrenderer->DrawLine (tileVert[1].pos[VX],tileVert[1].pos[VY],
								 tileVert[3].pos[VX],tileVert[3].pos[VY], col);*/
			zlineCache.Line		((int)tileVert[0].pos[VX],(int)tileVert[0].pos[VY],
								 (int)tileVert[2].pos[VX],(int)tileVert[2].pos[VY], col);
			zlineCache.Line		((int)tileVert[1].pos[VX],(int)tileVert[1].pos[VY],
								 (int)tileVert[3].pos[VX],(int)tileVert[3].pos[VY], col);
#endif
		};
		//
		posMinAct[VY]= posMaxAct[VY];
	};
	zrenderer->SetTextureWrapEnabled (texWrapEnabled);
};

/*
- eigentlich muss auf folgender Renderer-Caps eingegangen werden:
	dwMinTextureWidth	1
	dwMinTextureHeight	1
	dwMaxTextureWidth	2048
	dwMaxTextureHeight	2048
	dwMaxTextureAspectRatio	0
*/

