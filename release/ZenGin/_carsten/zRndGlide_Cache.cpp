// zRndGlide_Cache.cpp
// Carsten Edenfeld

#include "zcore.h"
#include "zRndGlide.h"
#include "zRndGlide_Cache.h"
#include "zRndGlide_State.h"
#include "zWin32.h"

int	reqLargeLOD;

#ifdef CHASE_DEBUG
	#define TEX_DEBUG
#endif

// statistical
static int texMemFetched		= 0;
static int texMemUsed			= 0;
static int numTexDL				= 0;
static int numTexDLBruteForce	= 0;
static int numTexDLBlockFree	= 0;
static int numTexDLBestFit		= 0;
static int numTexPartialDeleted = 0;
static int numTexStateChange	= 0;

zCList				<zCTex_RndGlide> zCTex_RndGlide :: texMem;

FxU32		zCTex_RndGlide :: root					= 0;					
zDWORD		zCTex_RndGlide :: frameCounter			= 0;
zDWORD		zCTex_RndGlide :: sizeTexMemHw			= 0;			
zDWORD		zCTex_RndGlide :: memAvail				= 0;				
zDWORD		zCTex_RndGlide :: largestBlockAvail		= 0;		
zBOOL		zCTex_RndGlide :: fragmented			= FALSE;

zCTex_RndGlide	 *zCTex_RndGlide :: tmpTexture		= 0;

void zCTex_RndGlide::InitCache() 
{
		
	tmpTexture = zNEW( zCTex_RndGlide );
	tmpTexture -> SetName ("CacheTex 2000");
	tmpTexture -> infoCache.smallLod = GR_LOD_0;

	root = grTexMinAddress(GR_TMU0) ;
	sizeTexMemHw = largestBlockAvail = memAvail	= grTexMaxAddress(GR_TMU0) - root;
	fragmented	 = FALSE;

	// fill first cache-slot with dummy to avoid one if-case in zCTex_RndGlide::Download
	texMem.Insert(tmpTexture);  
}

void zCTex_RndGlide::ReleaseCache()
{
	tmpTexture -> Release();
}

float zCTex_RndGlide::GetFragmentation() 
{ 
	return ( (100.0F- ((largestBlockAvail*100.0F) / memAvail)))  ;
}

zBOOL zCTex_RndGlide::IsFragmentedTexMemHw () 
{ 
	return ( GetFragmentation() > MAX_FRAG );
}

void zCTex_RndGlide :: ReleaseData() 
{
	if (infoSrc.data) {
		free(infoSrc.data);
		infoSrc.data = 0;
	}

	if (palette) {
		free(palette);
		palette = 0;
	}

	if (infoCache.largeLod != GR_LOD_0) {
		texMem.Remove(this); // GetNextinList nötig ?
		memAvail += sizeMipsCurrent;
		largestBlockAvail = GetLargestBlock();
		infoCache.largeLod = GR_LOD_0;
	}

};

void zCTex_RndGlide :: ShowTexCache()
{

	GrVertex	tmp[4];
	GrState state; 
	float offsetX = 0; 
	float offsetY = 0;
	float wSlot = 0;
	const float SLOT_HEIGHT= 10;
	const float SLOT_WIDTH = 10;

	grGlideGetState(&state);

	grColorCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE);

	grAlphaCombine(GR_COMBINE_FUNCTION_LOCAL,GR_COMBINE_FACTOR_NONE,
				   GR_COMBINE_LOCAL_ITERATED,GR_COMBINE_OTHER_NONE,FXFALSE );

	grAlphaBlendFunction(GR_BLEND_SRC_ALPHA,GR_BLEND_ONE_MINUS_SRC_ALPHA,
						 GR_BLEND_ZERO,GR_BLEND_ZERO);            
	
	
	zCList <zCTex_RndGlide> *help=texMem.GetNextInList();

	while (help->GetNextInList()) {

		float size = float(help->GetData()->sizeMipsCurrent);
		wSlot = MAX(1,size/200);

		if (offsetX + wSlot > zrenderer->vid_xdim) {
			offsetX = 0;
			offsetY += SLOT_HEIGHT+1;
		}
		tmp[0].x	 = offsetX; 
		tmp[0].y	 = offsetY; 
		tmp[1].x	 = offsetX; 
		tmp[1].y	 = offsetY+SLOT_HEIGHT; 
		tmp[2].x	 = offsetX+wSlot; 
		tmp[2].y	 = offsetY+SLOT_HEIGHT; 
		tmp[3].x	 = offsetX+wSlot; 
		tmp[3].y	 = offsetY; 
		offsetX += wSlot+1;

		for (int i=0; i<4; i++) {  
			tmp[i].r  = tmp[i].g = tmp[i].b = 255.0F;
			tmp[i].a  = 100.0F;
			tmp[i].oow= NEAREST_OOW;
		}

		// display in backbuffer, thus converting to rgb 565
		grDrawPolygonVertexList(4, tmp);

		size = float(GetFreeBlock(help));
		wSlot = MAX(1,size/200);

		if (offsetX + wSlot > zrenderer->vid_xdim) {
			offsetX = 0;
			offsetY += SLOT_HEIGHT+1;
		}
		if (offsetY > zrenderer->vid_ydim) return;
		tmp[0].x	 = offsetX; 
		tmp[0].y	 = offsetY; 
		tmp[1].x	 = offsetX; 
		tmp[1].y	 = offsetY+SLOT_HEIGHT; 
		tmp[2].x	 = offsetX+wSlot; 
		tmp[2].y	 = offsetY+SLOT_HEIGHT; 
		tmp[3].x	 = offsetX+wSlot; 
		tmp[3].y	 = offsetY; 
		offsetX += wSlot+1;

		for (i=0; i<4; i++) {  
			tmp[i].r  = tmp[i].g = tmp[i].b = 0;
			if (size) tmp[i].r  = 255;
			tmp[i].a  = 100.0F;
			tmp[i].oow= NEAREST_OOW;
		}

		// display in backbuffer, thus converting to rgb 565
		grDrawPolygonVertexList(4, tmp);

		help = help->GetNextInList();
	}
	
	float size = float((root+sizeTexMemHw) - (help->GetData()->addrTexHw+help->GetData()->sizeMipsCurrent));
	wSlot = float(size/200);
	if (size) {
		tmp[0].x	 = offsetX; 
		tmp[0].y	 = offsetY; 
		tmp[1].x	 = offsetX; 
		tmp[1].y	 = offsetY+SLOT_HEIGHT; 
		tmp[2].x	 = offsetX+wSlot; 
		tmp[2].y	 = offsetY+SLOT_HEIGHT; 
		tmp[3].x	 = offsetX+wSlot; 
		tmp[3].y	 = offsetY; 
		for (int i=0; i<4; i++)  tmp[i].r  = 255; 
		// display in backbuffer, thus converting to rgb 565
		guDrawPolygonVertexListWithClip(4, tmp);
	}

	grGlideSetState(&state);

}


inline zCList <zCTex_RndGlide> *zCTex_RndGlide :: GetBestFitInCache()
{	// Prioritys for a best Fit:
	// 1. same size, old age
	// 2. size greater (maximum double size), old age
	// 3. same size, age unimportant
	// 4. size greater (maximum double size), age unimportant

	zCList <zCTex_RndGlide> *help=texMem.GetNextInList();
	zCList <zCTex_RndGlide> *nearestFit = 0;
	zCList <zCTex_RndGlide> *sameSizeFit = 0;
	zSDWORD actAge,maxAge=-1;

	// 1. same size, old age
	while (help->GetNextInList()) {
		// Check for same feature
		if ( help->GetData()->sizeMipsCurrent == sizeMipsCurrent) {
			// Yes. Check if tex is old enough to be returned immediately
			actAge = frameCounter - help->GetData()->age;
			if ( actAge > AGE_TO_CACHE_OUT) return help;
			// No, so remember age
			if (actAge > maxAge) {
				maxAge  = actAge;
				nearestFit = help;  
			}
		}

		help = help->GetNextInList();
	}

	// 
	if (maxAge > MIN_AGE_TO_CACHE_OUT) return nearestFit;
	else sameSizeFit = nearestFit;
	
	help	   =texMem.GetNextInList();
	maxAge	   =-1;
	nearestFit = 0;

	// 2. size greater (maximum double size), old age
	while (help->GetNextInList()) {
		zDWORD thisSize = help->GetData()->sizeMipsCurrent;

		// Check for greater size (maximum double size)
		if ( thisSize > sizeMipsCurrent && thisSize>>1 <= sizeMipsCurrent ) {
			// Yes. Check if tex is old enough to be returned immediately
			actAge = frameCounter - help->GetData()->age;
			if ( actAge > AGE_TO_CACHE_OUT) return help;
			// No, so remember age
			if (actAge > maxAge) {
				maxAge  = actAge;
				nearestFit = help;  
			}
		}

		help = help->GetNextInList();
	}

	if (maxAge > MIN_AGE_TO_CACHE_OUT) return nearestFit;
	else if (sameSizeFit)			   return sameSizeFit;

	return nearestFit;
};  

	
inline zDWORD zCTex_RndGlide :: GetFreeBlock(zCList <zCTex_RndGlide> *help) 
{
	zCTex_RndGlide *act  = help->GetData();
	zCTex_RndGlide *next = help->GetNextInList()->GetData();

	for (int i=2; i<memPerTMU; i+=2) {
		int bound = i * 1024 * 1024;
		if ( (act->addrTexHw <= bound )  &&  ( next->addrTexHw >= bound ) ) return 0;
	}

	return	 next->addrTexHw -  ( act->addrTexHw + act->sizeMipsCurrent ) ;
}

inline zDWORD zCTex_RndGlide :: GetLargestBlock() 
{  
	zDWORD actSize,maxSize=0;
	zCList <zCTex_RndGlide> *help=texMem.GetNextInList();

	while (help->GetNextInList()) {
		actSize=GetFreeBlock(help);
		if (actSize > maxSize) maxSize=actSize;
		help = help->GetNextInList();
	}
	zDWORD lastPosFree = (root+sizeTexMemHw) - (help->GetData()->addrTexHw+help->GetData()->sizeMipsCurrent);
	if ( lastPosFree > maxSize ) return lastPosFree; else return maxSize;
}

/*****************************************************************************
FUNCTION: DefragPartial
DESC    : Defrags Texture Memory according to given time limit 
*****************************************************************************/
void	zCTex_RndGlide :: DefragPartial(zDWORD maxTime,float maxFrag)
{
	zCList <zCTex_RndGlide> *help=texMem.GetNextInList()->GetNextInList();// ptr. to first texture slot
	zCTex_RndGlide *tmpTex;
	zDWORD size;

	zDWORD startTime = sysGetTime();

	while (help->GetNextInList()) {
		
		if (size=GetFreeBlock(help)) { // Is there a mem hole ?
			// Yes.
			// Texture has to be in main mem to be moved, as there is no
			// direct access to hw-texture mem
			tmpTex=help->GetNextInList()->GetData(); 
			tmpTex -> CacheIn(); // probably not necessary?
			// Calc new addr directly after prev. Texture
			tmpTex -> addrTexHw = help->GetData()->addrTexHw + help->GetData()->sizeMipsCurrent;
			// Download again at correct position
			grTexDownloadMipMap( GR_TMU0 , tmpTex -> addrTexHw ,GR_MIPMAPLEVELMASK_BOTH, &tmpTex->infoCache);
			// Recalc largestBlock if necessary
			if (size == largestBlockAvail) largestBlockAvail = GetLargestBlock();
		}

		if ( (sysGetTime() - startTime >= maxTime) || GetFragmentation() <= maxFrag ) break;

		help = help->GetNextInList();

	}
	largestBlockAvail = GetLargestBlock();

}

void zCTex_RndGlide :: Defrag()
{
	DefragPartial(100000,0);
}



inline zBOOL zCTex_RndGlide :: CheckCacheConsistency(){

	zCList <zCTex_RndGlide> *help=texMem.GetNextInList()->GetNextInList();

	if (!help) return TRUE;
	zDWORD lastAddr = help->GetData()->addrTexHw;
	zDWORD lastSize = help->GetData()->sizeMipsCurrent;
	zCList <zCTex_RndGlide> *lastEle=texMem.GetNextInList()->GetNextInList();

	if (help = help->GetNextInList())
	while (help->GetNextInList()) {
		zDWORD thisAddr = help->GetData()->addrTexHw;
		if (lastAddr >= thisAddr || lastAddr+lastSize > thisAddr ) return FALSE;
		lastAddr = thisAddr;
		lastEle  = help;
		lastSize = help->GetData()->sizeMipsCurrent;
		help = help->GetNextInList();
	}
	return TRUE;
}


void zCTex_RndGlide :: RecalcCacheMem() {
	zCList <zCTex_RndGlide> *help=texMem.GetNextInList()->GetNextInList();
	zDWORD	avail = 0, maxSize = 0;

	while (help->GetNextInList()) {
		zDWORD slotFree = GetFreeBlock(help);
		avail+= slotFree; 
		if (slotFree > maxSize) maxSize=slotFree;
		help = help->GetNextInList();

	}
	zDWORD lastPosFree = (root+sizeTexMemHw) - (help->GetData()->addrTexHw+help->GetData()->sizeMipsCurrent);
	if ( lastPosFree > maxSize ) largestBlockAvail = lastPosFree; else largestBlockAvail = maxSize;
	memAvail = avail + lastPosFree;
}

void  zCTex_RndGlide :: SetAge() 
{ 
	if (age != frameCounter) {
		texMemUsed += sizeMipsCurrent;
		age = frameCounter; 
		numTexDrawn ++;
	}
};

/********************************************************************************
 FUNCTION: zCTex_RndGlide::Download
 DESC    : Loads a texture onto the 3dfx-card texture memory
*********************************************************************************/

void zCTex_RndGlide :: Download() 
{

	if ( zCResource::CacheIn() != zRES_CACHED_IN ) return;
	
	if (oldTexture == this && infoCache.largeLod <= reqLargeLOD) {
		SetAge();
		return;// no tex-change
	}

	if (infoSrc.mem_required <= largestBlockAvail || maxDetailTex ) reqLargeLOD = infoSrc.header.large_lod;

	if (infoCache.largeLod <= reqLargeLOD) { // requested mipmaps are on 3dfx-mem
		// set as active texture

		SetAge();
		numTexStateChange++;

		grTexSource(GR_TMU0, GetHwMemPos() ,GR_MIPMAPLEVELMASK_BOTH, &infoCache );

		// see if we got tables to download, too
		if (infoCache.format == GR_TEXFMT_YIQ_422 || infoCache.format == GR_TEXFMT_AYIQ_8422 ) {
			grTexDownloadTable(GR_TMU0,GR_TEXTABLE_NCC0,&infoSrc.table.nccTable);
		} 
		else if (infoCache.format == GR_TEXFMT_P_8 || infoCache.format == GR_TEXFMT_AP_88 ) {
			grTexDownloadTable(GR_TMU0,GR_TEXTABLE_PALETTE,&infoSrc.table.palette);
		} 
		return;

	}
	else if (infoCache.largeLod != GR_LOD_0) { // partial mipmaps are already in list, they have to be removed

		numTexPartialDeleted ++;

		texMem.Remove(this); 
		memAvail += sizeMipsCurrent;
		largestBlockAvail = GetLargestBlock();
	}

	CacheIn();

	zBOOL	found=FALSE;
	zCList <zCTex_RndGlide> *help=texMem.GetNextInList();// ptr. to first texture slot
	zDWORD	sizeFreeBlock=0;

	infoCache.largeLod = reqLargeLOD;

	if (infoCache.largeLod>infoCache.smallLod) infoCache.largeLod = infoCache.smallLod;
	
	sizeMipsCurrent = grTexCalcMemRequired(infoCache.smallLod,infoCache.largeLod,infoCache.aspectRatio,infoCache.format);

	SetAge();  // Hmm, only needed once per frame & texture

	// find calculated mip chain in original 3df data
	infoCache.data = (zBYTE*)infoSrc.data + (infoSrc.mem_required - sizeMipsCurrent);

	addrTexHw = 0;
	if (largestBlockAvail >= sizeMipsCurrent) {  // check if we have to deal w/ full texture mem
		// no, so we can simply Insert it at the correct position 
		// find a free block in list 
		while (help->GetNextInList() ) {   // As long as we have a next member
			if (GetFreeBlock(help) >= sizeMipsCurrent) {
				found = TRUE;
				break;
			}
			help = help->GetNextInList();
		}

		// Calculate free address on hw-mem
		addrTexHw = help->GetData()->addrTexHw + help->GetData()->sizeMipsCurrent;
		if (!found) {
			// letzte Position auf 2MB Boundary Problem checken, grrr (nicht nötig für alles über voodoo2)
			for (int i=2; i<memPerTMU; i+=2) {
				int bound = i * 1024 * 1024;
				if ( (addrTexHw <= bound )  &&  ( addrTexHw+sizeMipsCurrent >= bound ) ) {
					addrTexHw = bound;
				}
			}
		}


		help->Insert(this);
		memAvail		 -= sizeMipsCurrent;
		// FIXME: teuer!
		largestBlockAvail = GetLargestBlock();
		numTexDLBlockFree++;

	}
	else if (memAvail <= sizeMipsCurrent) { // full mem, less fragmentation

		// Now search in list for the best fit (same features, old age)
		help = GetBestFitInCache();  
		if (help) {  // See if we got a best fit
			numTexDLBestFit	++;
			addrTexHw  = help->GetData()->addrTexHw;// + help->GetData()->size;
			help->GetData()->infoCache.largeLod = GR_LOD_0;
			if (help->GetData()->sizeMipsCurrent > sizeMipsCurrent) {
				memAvail += help->GetData()->sizeMipsCurrent-sizeMipsCurrent;
				largestBlockAvail = GetLargestBlock();
			}

			help->Replace(this);
		}
		else Download_BruteForce();
	}
	else { 
		
		// fragmentation very possible, defragmentation is expensive. 
		   // DefragPartial() called in BeginFrame if necessary
		help = GetBestFitInCache();  
		if (help) {  // See if we got a best fit
			numTexDLBestFit	++;
			addrTexHw = help->GetData()->addrTexHw;//+ help->GetData()->size;
			help->GetData()->infoCache.largeLod = GR_LOD_0;
			if (help->GetData()->sizeMipsCurrent > sizeMipsCurrent) {
				memAvail += help->GetData()->sizeMipsCurrent-sizeMipsCurrent;
				largestBlockAvail = GetLargestBlock();
			}
			help->Replace(this);
			// Note: Although BestFit might be always possible here, fragmentation
			//   may affect performance nevertheless -> defrag/multi-base 
		}
		else Download_BruteForce(); // fragmentation worst case!
	}


	
    #ifdef _CHECK_TEXCACHE_
	assert(memAvail>=largestBlockAvail);
	assert(addrTexHw+sizeMipsCurrent<=sizeTexMemHw);
	assert(memAvail<=sizeTexMemHw);
	assert(largestBlockAvail<=sizeTexMemHw);
	#endif
	//}

	grTexDownloadMipMap( GR_TMU0 , addrTexHw ,GR_MIPMAPLEVELMASK_BOTH, &infoCache);

	// set as active texture
	numTexStateChange++;
	grTexSource(GR_TMU0, GetHwMemPos() ,GR_MIPMAPLEVELMASK_BOTH, &infoCache );

	// see if we got tables to download, too
	if (infoCache.format == GR_TEXFMT_YIQ_422 || infoCache.format == GR_TEXFMT_AYIQ_8422 ) {
		grTexDownloadTable(GR_TMU0,GR_TEXTABLE_NCC0,&infoSrc.table.nccTable);
	}
	else if (infoCache.format == GR_TEXFMT_P_8 || infoCache.format == GR_TEXFMT_AP_88 ) {
		grTexDownloadTable(GR_TMU0,GR_TEXTABLE_PALETTE,&infoSrc.table.palette);
	} 

	assert(sizeMipsCurrent>0);
	texMemFetched += sizeMipsCurrent;
	numTexDL ++;
}

void zCTex_RndGlide::Download_BruteForce()
{
	numTexDLBruteForce++;

	/* tmp - Brute Force */
	zCList <zCTex_RndGlide> *t=texMem.GetNextInList()->GetNextInList();
	zDWORD memAlloced=0;

	while (t->GetNextInList()) {
		zCList <zCTex_RndGlide> *tmp;
		memAlloced += t->GetData()->sizeMipsCurrent+GetFreeBlock(t);
		t->GetData()->infoCache.largeLod = GR_LOD_0;
		tmp = t->GetNextInList();
		texMem.Remove(t->GetData());
		if (memAlloced >= sizeMipsCurrent) break;
		t = tmp;
	}

	addrTexHw = root;
	texMem.GetNextInList()->Insert(this);
	RecalcCacheMem();
}

void zCTex_RndGlide::PrintCacheSlots() 
{
	int num = 0;
	zDWORD totalSize = 0;
	zCList <zCTex_RndGlide> *help=texMem.GetNextInList();

	zerr.Message("C: *** Texture Cache filled with the following active textures:");

	while (help->GetNextInList()) {
		if (help->GetData()->GetAge() == zCTex_RndGlide::GetFrame() ) {
			zerr.Message("C: slot " + zSTRING(num++) +zSTRING(": ") + help->GetData()->GetName() + " size: " + zSTRING(help->GetData()->sizeMipsCurrent));
			totalSize += help->GetData()->sizeMipsCurrent;
		}
		help = help->GetNextInList();
	}
	
	zerr.Message("C: total scene size: " + zSTRING(totalSize));
}

void zCTex_RndGlide::ClearCache() 
{
	zCList <zCTex_RndGlide> *help=texMem.GetNextInList();

	while (help->GetNextInList()) {
		help->GetData()->infoCache.largeLod = GR_LOD_0;
		help = help->GetNextInList();
	}
	texMem.DeleteList();
	texMem.Insert(tmpTexture);  
}


void zCRnd_Glide::GetStatistics(zTRnd_Stats &stat)
{
	GrSstPerfStats_t grStats;
	grSstPerfStats(&grStats);
	memset(&stat,0,sizeof(stat));
	stat.pixelsIn		= grStats.pixelsIn  + zTestStat.pixelsIn;
	stat.pixelsOut		= grStats.pixelsOut + zTestStat.pixelsOut;
	stat.chromaFail		= grStats.chromaFail+ zTestStat.chromaFail;
	stat.aFuncFail		= grStats.aFuncFail	+ zTestStat.aFuncFail;
	stat.zFuncFail		= grStats.zFuncFail + zTestStat.zFuncFail;
	stat.numPolysRendered	= polysRendered;
	stat.numTrisRendered    = trisRendered;
	stat.numTexturesFetched = numTexDL;
	stat.numLightmapsUsed	= lightMapsRendered;
	stat.numTexturesUsed	= numTexDrawn;

	zCList <zCTex_RndGlide> *help=zCTex_RndGlide::texMem.GetNextInList();
	zDWORD cacheUsed = 0;


	zSDWORD actAge,maxAge=-1;

	while (help->GetNextInList()) {
		// Check for same feature
		cacheUsed += help->GetData()->sizeMipsCurrent;
		actAge = zCTex_RndGlide::GetFrame() - help->GetData()->GetAge();
		// No, so remember age
		if (actAge > maxAge) maxAge  = actAge;

		help = help->GetNextInList();
	}

	stat.texMemFetched	= texMemFetched;
	stat.texMemUsed		= texMemUsed;

	#ifdef TEX_DEBUG
	zerr.Message("C: total tex mem avail : " + zSTRING(zCTex_RndGlide::GetTotalTexMemHw()));
	zerr.Message("C: total cache mem used: " + zSTRING(cacheUsed));
	zerr.Message("C: total texture count downloaded:" + zSTRING(numTexDL));
	zerr.Message("C: total texture count downloaded brute force:" + zSTRING(numTexDLBruteForce));
	zerr.Message("C: total texture count downloaded in free block:" + zSTRING(numTexDLBlockFree));
	zerr.Message("C: total texture count downloaded with best fit:" + zSTRING(numTexDLBestFit));
	zerr.Message("C: total texture count deleted due to uncomplete mipmap data :" + zSTRING(numTexPartialDeleted));
	zerr.Message("C: total texture state changes:" + zSTRING(numTexStateChange));
	zerr.Message("C: oldest texture in cache :" + zSTRING(maxAge));
	zerr.Message("C: num tex drawn :" + zSTRING(numTexDrawn));
	#endif
};

void zCRnd_Glide::ResetStatistics()
{
	grSstResetPerfStats();
	texMemFetched		= 0;
	texMemUsed			= 0;
	numTexDL			= 0;
	numTexDLBruteForce	= 0;
	numTexDLBlockFree	= 0;
	numTexDLBestFit		= 0;
	numTexPartialDeleted= 0;
	numTexStateChange	= 0;
	numTexDrawn			= 0;
	memset(&zTestStat,0,sizeof(zTestStat));
};

