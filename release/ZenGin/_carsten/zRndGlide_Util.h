/********************************************************************************
 
 Project : Gothic
 Author  : Carsten Edenfeld
 File    : zRndGlide_Util.h
 Version : 0.00
 Created : 06.11.98
 Last Mod: 06.11.98
 
*********************************************************************************
 TODO : 
*********************************************************************************
 BUGS : 
*********************************************************************************
 NOTE : 
 *********************************************************************************

  $Log:: /current_work/Ze $
 * 
 * 3     7.05.00 20:41 Edenf
 * 
 * 2     26.04.00 11:27 Admi
 * 
 * 1     19.04.00 18:16 Eden
 * 
 * 5     1.03.00 15:56 Edenf
 * 
 * 4     10.01.00 15:22 Eden
 * Engine 0.85b Anpassungen
 * 
 * 3     2.12.99 17:11 Edenf

*********************************************************************************/

#ifndef __zRNDGLIDE_UTIL_H__
#define __zRNDGLIDE_UTIL_H__

#include <windows.h>
#include "glide.h"
#include "zRndGlide_Cache.h"
#include "zRndGlide_State.h"
#include "zDisk.h"

typedef struct {
    const char *id;
    int         res;
    float       width;
    float       height;
} ResToRes;

extern zWORD	maxTableRes ;
extern zWORD	actTableRes; 
extern ResToRes resTable[];
extern long		resTableSize;
extern int		mipAlgo;

extern HWND		winHandle;

extern void		tlGetDimsByConst		(const GrScreenResolution_t resConst, float *w, float *h);
extern int		tlGetTableSlotByConst	(const GrScreenResolution_t resConst);
extern void		tlGetConstByDims		(GrScreenResolution_t  *resConst, const int *w, const int *h);
extern int		tlGetResolutionConstant ( const char *identifier, float *width, float *height );
extern const	char *tlGetResolutionString	( int res ) ;
extern const	char *tlGetResolutionList	( void );

extern FxBool	ScreenDumpTGA			( char *filename, FxU16 width,  FxU16 height);

extern void		EnableTaskSwitch		();
extern void		DisableTaskSwitch		();


#ifndef Lerp
#define Lerp(t, a, b) ( a + t * (b - a) ) 
#endif


/*
inline void 	PolyTexCalcLargestLOD(zCPolygon *poly,const zCTex_RndGlide *tex)
{
	//zerr.Message("in PolyTexCalcLargestLOD");
	zREAL zMin      = zREAL_MAX;
	// pick nearest vertex
	for (int k=0; k < poly->numClipVert; k++) {
		zREAL z = poly->clipVert[k]->vertCamSpace[VZ];
		if ( z < zMin ) {
			if (z>0) {
				zMin = z;
			} 
			else {
				reqLargeLOD = tex->infoSrc.header.large_lod;
				return;
			}
		}
	};

	zClamp(zMin,zREAL(1),zREAL(mipRange)); // FIXME: upper bound nur für himmelspoly nötig
	reqLargeLOD = int ((tex->infoSrc.header.large_lod + (zMin*mipRangeInv) * float(tex->infoSrc.header.small_lod-tex->infoSrc.header.large_lod)));
	//zerr.Message("out PolyTexCalcLargestLOD");
}
*/

inline void 	PolyTexCalcLargestLOD(zCPolygon *poly,const zCTex_RndGlide *tex)
{
	// return if size of tex in cache is already the max LOD
	if ( tex->infoCache.largeLod == tex->infoSrc.header.large_lod ) {
		reqLargeLOD = tex->infoCache.largeLod;
		return;
	}


	if (mipAlgo == 1) {
		
		const		int LOD_SCALE	= 30000;
		float		screenArea		= 0;
		float		texelArea		= 0;
		int			pLast			= poly->numClipVert-1; 	// indices into current/last vertex(-feature)
		int			pCurr;
		int			texelRatio;
		
		// Calculate the polygon and texture areas
		zCVertex			**clipVert = poly->clipVert;
		zCVertFeature		**clipFeat = poly->clipFeat;

		for(int i=0;i<poly->numClipVert;i++)
		{
			pCurr	    = i;
			screenArea += (clipVert[pCurr]->vertScrX + clipVert[pLast]->vertScrX)*(clipVert[pCurr]->vertScrY - clipVert[pLast]->vertScrY);
			texelArea  += (clipFeat[pCurr]->texu     + clipFeat[pLast]->texu    )*(clipFeat[pCurr]->texv     - clipFeat[pLast]->texv	);
			pLast		= pCurr;
		}

		if( screenArea==0 ) {
			reqLargeLOD = tex->infoSrc.header.small_lod;
			return;
		}

		// Get texture-to polgon ratio
		texelRatio=zAbs(int(texelArea*LOD_SCALE/screenArea));

		// Calculate the LOD
		for( reqLargeLOD=tex->infoSrc.header.large_lod; texelRatio>3; texelRatio>>=2 ) reqLargeLOD++;

		// conservative cache scheme: gereral subtract one LOD -> profile

		if( reqLargeLOD != tex->infoSrc.header.large_lod ) --reqLargeLOD;

		if( reqLargeLOD > tex->infoSrc.header.small_lod ) reqLargeLOD = tex->infoSrc.header.small_lod;
		if (reqLargeLOD > tex->infoCache.smallLod) reqLargeLOD = tex->infoCache.smallLod;

		//if ( !headTexFound && poly->GetMaterial()->GetAniTexture() && poly->GetMaterial()->GetAniTexture()->GetName() == zSTRING("HUM_HEAD_HAIR1_V0_C1.TGA") ) {
		//	zerr.Message("C: lod for head tex:" + zSTRING(reqLargeLOD));
		//	headTexFound = TRUE;
		//};
	}
	else {
		zREAL zMin      = zREAL_MAX;
		// pick nearest vertex
		for (int k=0; k < poly->numClipVert; k++) {
			zREAL z = poly->clipVert[k]->vertCamSpace[VZ];
			if ( z < zMin ) {
				if (z>0) {
					zMin = z;
				} 
				else {
					reqLargeLOD = tex->infoSrc.header.large_lod;
					return;
				}
			}
		};

		zClamp(zMin,zREAL(1),zREAL(mipRange)); // FIXME: upper bound nur für himmelspoly nötig
		reqLargeLOD = int ((tex->infoSrc.header.large_lod + (zMin*mipRangeInv) * float(tex->infoSrc.header.small_lod-tex->infoSrc.header.large_lod)));
		if (reqLargeLOD>tex->infoCache.smallLod) reqLargeLOD = tex->infoCache.smallLod;
	}
}

inline int GetPolyAvgZ(const zCPolygon* poly)
{
	float v=0;
	for (int k=0; k < poly->numClipVert; k++) v+= poly->clipVert[k]->vertCamSpace[VZ];
	v/=poly->numClipVert;
	return zFloat2Int(v);

}

/*inline float GetPolyAvgZ(const zCPolygon* poly)
{
	float zMAX=FLT_MIN;
	for (int k=0; k < poly->numClipVert; k++) {
		float zThis = poly->clipVert[k]->vertCamSpace[VZ];
		if (zThis > zMAX) zMAX = zThis;
	}
	return zMAX;
}*/


/*inline void GetPolyMinMaxZ(const zCPolygon* poly, float &zMin, float &zMax)
{
	zMax=FLT_MIN;
	zMin=FLT_MAX;
	for (int k=0; k < poly->numClipVert; k++) {
		float zThis = poly->clipVert[k]->vertCamSpace[VZ];
		if (zThis > zMax) zMax = zThis;
		if (zThis < zMin) zMin = zThis;
	}
}*/
/*inline void GetPolyMinMaxZ(const zCPolygon* poly, float &zMin, float &zMax)
{
	zMax=FLT_MIN;
	zMin=FLT_MAX;
	for (int k=0; k < poly->numClipVert; k++) {
		float zThis = poly->clipVert[k]->vertCamSpace[VZ];
		if (zThis > zMax) zMax = zThis;
		if (zThis < zMin) zMin = zThis;
	}
	//zMin = (zMax + zMin) * 0.5F;
}*/

#endif
