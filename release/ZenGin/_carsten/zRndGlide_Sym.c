// zRndGlide_Sym.cpp

// Loads "glide2x.dll" and retrieves the function addresses of the symbols
// partly based upon wglide from Justin Frankel/Nullsoft, Inc. (http://www.nullsoft.com)


#include <windows.h>

#define FX_GLIDE_NO_FUNC_PROTO
#include <glide.h>
#include <glideutl.h>


#define IMPORTS_C
#include "zRndGlide_Sym.h"

static HINSTANCE hGlide;

// loads a function "name", that has a parameter list of "parmsize" bytes.
#define LOADFUNC(name,parmsize)	\
	( ##name ) = (void *) GetProcAddress(hGlide,"_" #name "@" #parmsize);	\
	if (!( ##name ))	\
	{	\
		FreeModule(hGlide);		\
		return 1;	\
	}

/********************************************************************************
 FUNCTION: LoadGlideSymbols
 DESC    : Fills Glide Function Pointers with symboladdresses in glide2x.dll
 RETURN  : 0 = success, 1 = error while symbol reading, -1 no glide2x.dll found
*********************************************************************************/
int LoadGlideSymbols(void)
{
	char str[512];
	GetWindowsDirectory(str,sizeof(str)-1);
	strcat(str,"\\glide2x.dll");
	hGlide = LoadLibraryEx(str,NULL,DONT_RESOLVE_DLL_REFERENCES);
	if (!hGlide) 
	{
		GetSystemDirectory(str,sizeof(str)-1);
		strcat(str,"\\glide2x.dll");
		hGlide = LoadLibrary(str);
		//hGlide = LoadLibraryEx(str,NULL,DONT_RESOLVE_DLL_REFERENCES);
		if (!hGlide) return -1;

	}
	LOADFUNC(grDrawLine,8);
	LOADFUNC(grDrawPlanarPolygon,12);
	LOADFUNC(grDrawPlanarPolygonVertexList,8);
	LOADFUNC(grDrawPoint,4);
	LOADFUNC(grDrawPolygon,12);
	LOADFUNC(grDrawPolygonVertexList,8);
	LOADFUNC(grDrawTriangle,12);
	LOADFUNC(grBufferClear,12);
	LOADFUNC(grBufferNumPending,0);
	LOADFUNC(grBufferSwap,4);
	LOADFUNC(grRenderBuffer,4);
	LOADFUNC(grErrorSetCallback,4);
	LOADFUNC(grSstIdle,0);
	LOADFUNC(grSstVideoLine,0);
	LOADFUNC(grSstVRetraceOn,0);
	LOADFUNC(grSstIsBusy,0);
	LOADFUNC(grSstWinOpen,28);
	LOADFUNC(grSstWinClose,0);
	LOADFUNC(grSstControl,4);
	LOADFUNC(grSstQueryHardware,4);
	LOADFUNC(grSstQueryBoards,4);
	LOADFUNC(grSstOrigin,4);
	LOADFUNC(grSstSelect,4);
	LOADFUNC(grSstScreenHeight,0);
	LOADFUNC(grSstScreenWidth,0);
	LOADFUNC(grSstStatus,0);
	LOADFUNC(grSstPerfStats,4);
	LOADFUNC(grSstResetPerfStats,0);
	LOADFUNC(grResetTriStats,0);
	LOADFUNC(grTriStats,8);
	LOADFUNC(grAlphaBlendFunction,16);
	LOADFUNC(grAlphaCombine,20);
	LOADFUNC(grAlphaControlsITRGBLighting,4);
	LOADFUNC(grAlphaTestFunction,4);
	LOADFUNC(grAlphaTestReferenceValue,4);
	LOADFUNC(grChromakeyMode,4);
	LOADFUNC(grChromakeyValue,4);
	LOADFUNC(grClipWindow,16);
	LOADFUNC(grColorCombine,20);
	LOADFUNC(grColorMask,8);
	LOADFUNC(grCullMode,4);
	LOADFUNC(grConstantColorValue,4);
	LOADFUNC(grConstantColorValue4,16);
	LOADFUNC(grDepthBiasLevel,4);
	LOADFUNC(grDepthBufferFunction,4);
	LOADFUNC(grDepthBufferMode,4);
	LOADFUNC(grDepthMask,4);
	LOADFUNC(grDisableAllEffects,0);
	LOADFUNC(grDitherMode,4);
	LOADFUNC(grFogColorValue,4);
	LOADFUNC(grFogMode,4);
	LOADFUNC(grFogTable,4);
	LOADFUNC(grGammaCorrectionValue,4);
	LOADFUNC(grSplash,20);
	LOADFUNC(grTexCalcMemRequired,16);
	LOADFUNC(grTexTextureMemRequired,8);
	LOADFUNC(grTexMinAddress,4);
	LOADFUNC(grTexMaxAddress,4);
	LOADFUNC(grTexNCCTable,8);
	LOADFUNC(grTexSource,16);
	LOADFUNC(grTexClampMode,12);
	LOADFUNC(grTexCombine,28);
	LOADFUNC(grTexCombineFunction,8);
	LOADFUNC(grTexDetailControl,16);
	LOADFUNC(grTexFilterMode,12);
	LOADFUNC(grTexLodBiasValue,8);
	LOADFUNC(grTexDownloadMipMap,16);
	LOADFUNC(grTexDownloadMipMapLevel,32);
	LOADFUNC(grTexDownloadMipMapLevelPartial,40);
	LOADFUNC(grCheckForRoom,4);
	LOADFUNC(grTexDownloadTable,12);
	LOADFUNC(grTexDownloadTablePartial,20);
	LOADFUNC(grTexMipMapMode,12);
	LOADFUNC(grTexMultibase,8);
	LOADFUNC(grTexMultibaseAddress,20);
	LOADFUNC(grLfbLock,24);
	LOADFUNC(grLfbUnlock,8);
	LOADFUNC(grLfbConstantAlpha,4);
	LOADFUNC(grLfbConstantDepth,4);
	LOADFUNC(grLfbWriteColorSwizzle,8);
	LOADFUNC(grLfbWriteColorFormat,4);
	LOADFUNC(grLfbWriteRegion,32);
	LOADFUNC(grLfbReadRegion,28);
	LOADFUNC(grAADrawLine,8);
	LOADFUNC(grAADrawPoint,4);
	LOADFUNC(grAADrawPolygon,12);
	LOADFUNC(grAADrawPolygonVertexList,8);
	LOADFUNC(grAADrawTriangle,24);
	LOADFUNC(grGlideInit,0);
	LOADFUNC(grGlideShutdown,0);
	LOADFUNC(grGlideGetVersion,4);
	LOADFUNC(grGlideGetState,4);
	LOADFUNC(grGlideSetState,4);
	LOADFUNC(grGlideShamelessPlug,4);
	LOADFUNC(grHints,8);
	LOADFUNC(guTexAllocateMemory,60);
	LOADFUNC(guTexChangeAttributes,48);
	LOADFUNC(guTexCombineFunction,8);
	LOADFUNC(guTexGetCurrentMipMap,4);
	LOADFUNC(guTexGetMipMapInfo,4);
	LOADFUNC(guTexMemQueryAvail,4);
	LOADFUNC(guTexMemReset,0);
	LOADFUNC(guTexDownloadMipMap,12);
	LOADFUNC(guTexDownloadMipMapLevel,12);
	LOADFUNC(guTexSource,4);
	LOADFUNC(ConvertAndDownloadRle,64);
	LOADFUNC(guAADrawTriangleWithClip,12);
	LOADFUNC(guDrawTriangleWithClip,12);
	LOADFUNC(guDrawPolygonVertexListWithClip,8);
	LOADFUNC(guAlphaSource,4);
	LOADFUNC(guColorCombineFunction,4);
	LOADFUNC(guEncodeRLE16,16);
	LOADFUNC(guTexCreateColorMipMap,0);
	LOADFUNC(guMovieStart,0);
	LOADFUNC(guMovieStop,0);
	LOADFUNC(guMovieSetName,4);
	LOADFUNC(guFogTableIndexToW,4);
	LOADFUNC(guFogGenerateExp,8);
	LOADFUNC(guFogGenerateExp2,8);
	LOADFUNC(guFogGenerateLinear,12);
	LOADFUNC(guEndianSwapWords,4);
	LOADFUNC(guEndianSwapBytes,4);
	LOADFUNC(gu3dfGetInfo,8);
	LOADFUNC(gu3dfLoad,8);
	return 0;
}


void FreeGlideSymbols(void)
{
  FreeLibrary(hGlide);
}




