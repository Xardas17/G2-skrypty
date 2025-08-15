/********************************************************************************
 
 Project : Gothic
 Author  : Carsten Edenfeld
 File    : zRndGlide_Util.cpp
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
$Log:: $
 * 
 * 5     21
 * 
 * 4     21
 * 
 * 3     22
 * 
 * 2     26
 * 
 * 1     19
 * 
 * 8     10
 * Engine
 * 0.85b
 * Anpassun
 * gen
 * 
 * 7     7.
 * 
 * 6     7.
 * 
 * 5     2.
*********************************************************************************/

#include "zcore.h"
#include "zoption.h"
#include <windows.h>
#include <direct.h>
#include "zRndGlide.h"
#include "zRndGlide_Util.h"

int			mipAlgo		= 0;
zWORD		maxTableRes ;
zWORD		actTableRes = 5; 
ResToRes	resTable[] = {
    { "glide 512x384x16", GR_RESOLUTION_512x384, 512.0f, 384.0f },
    { "glide 640x400x16", GR_RESOLUTION_640x400, 640.0f, 400.0f },
    { "glide 640x480x16", GR_RESOLUTION_640x480, 640.0f, 480.0f },
    { "glide 800x600x16", GR_RESOLUTION_800x600, 800.0f, 600.0f },
    { "glide 1024x768x16", GR_RESOLUTION_1024x768, 1024.0f, 768.0f },
    { "glide 1280x1024x16", GR_RESOLUTION_1280x1024, 1280.0f, 1024.0f },
};

long resTableSize = sizeof( resTable ) / sizeof( ResToRes );

/* TLIB.C imported necessary funcs */

/*-------------------------------------------------------------------
  Function: tlGetResolution
  Date: 2/25
  Implementor(s): jdt
  Library: Test Library
  Description:
  Get the integer representing the provided resolution and return the
  necessary floats for screen scaling.
  Arguments:
  identifier - string identifying resolution of the form XRSxYRS
  width - pointer to float storage for width
  height - pointer to float storage for height
  Return:
  int
  -------------------------------------------------------------------*/


void tlGetDimsByConst(const GrScreenResolution_t resConst, float *w, float *h)
{
	int match;
  
	for( match = 0; match < resTableSize; match++ ) {
		if ( resTable[match].res == resConst ){
		  *w  = resTable[match].width;
		  *h  = resTable[match].height;
		  return;
		}
	}
} /* tlGetDimsByConst */

int tlGetTableSlotByConst(const GrScreenResolution_t resConst)
{
	int match;
  
	for( match = 0; match < resTableSize; match++ ) {
		if ( resTable[match].res == resConst ){
		  return match;
		}
	}
	return -1;
} /* tlGetDimsByConst */

void tlGetConstByDims(GrScreenResolution_t  *resConst, const int *w, const int *h)
{
	int match;

	for( match = 0; match < resTableSize; match++ ) {
		if ( resTable[match].width == (float)*w && resTable[match].height == (float)*h ){
		  *resConst  = resTable[match].res;
		  return;
		}
	}
//	*resConst = GR_RESOLUTION_NONE;
	
} 
/*-------------------------------------------------------------------
  Function: tlGetReslutionConstant
  Date: 2/28
  Implementor(s): jdt
  Library: Test Library
  Description:
  Returns the glide constant for a command line resolution argument
  Arguments:
  identifier - command line resolution arg.
  width - storage for floating point screen width
  height - storaget for floating piont screen height
  Return:
  GrResolution_t matching resolution argument
  -------------------------------------------------------------------*/

int tlGetResolutionConstant( const char *identifier, float *width, float *height ) 
{
	static int Res = GR_RESOLUTION_640x480;
	int match;

	for( match = 0; match < resTableSize; match++ ) {
		if ( !strcmp( identifier, resTable[match].id ) ) {
			Res = resTable[match].res;
			*width  = resTable[match].width;
			*height = resTable[match].height;
			return Res;
		}
	}
	return GR_RESOLUTION_NONE;

}

/*-------------------------------------------------------------------
  Function: tlGetResolutionString
  Date: 2/28
  Implementor(s): jdt
  Library: Test LIbrary
  Description:
  Returns a string value for a given resolution constant
  Arguments:
  res - resolution constant
  Return:
  string representing resolution
  -------------------------------------------------------------------*/
const char *tlGetResolutionString( int res ) 
{
    int match;
    const char *str = "unknown";

    for( match = 0; match < resTableSize; match++ ) {
        if ( resTable[match].res == res ) {
            str = resTable[match].id;
            break;
        }
    }
    return str;
}

/*-------------------------------------------------------------------
  Function: tlGetResolutionList
  Date: 2/28
  Implementor(s): jdt
  Library: TestLibrary
  Description:
  Return a list of all supported resolutions
  Arguments:
  none
  Return:
  const char * to resolution list
  -------------------------------------------------------------------*/
const char *tlGetResolutionList( void ) {
    char *list = (char *) calloc( sizeof( char ), 256 );
    int member;
    strcat( list, resTable[0].id );
    for( member = 1; member < resTableSize; member++ ) {
        strcat( list, " \n" );
        strcat( list, resTable[member].id );
    }
    return list;
}



FxBool ScreenDumpTGA( char *filename, FxU16 width,  FxU16 height)
{

	zFILE::DirectFileAccess(TRUE);
	 FxU8  *S,*D,*B;
	 FILE  *fp;
	 FxU8  *region;
	 int   bitsize;
	 int   h;
	 int   wsize;
	 unsigned short tga_header[0x12]={0,2,0,0,0,0,width,height,0x10 };

	 /*
	  * dump frontbuffer
	  */
	 bitsize=width * height * sizeof(FxU16);
	 region = (unsigned char *)malloc(bitsize);
	 if(region==0)return FXFALSE;
	 grLfbReadRegion( GR_BUFFER_FRONTBUFFER,0, 0, width, height, width*2,(unsigned short*)region );

	 /*
	  * flip vertical
	  */
	 h=height>>1;
	 wsize = width<<1;
	 B = (FxU8*) malloc( wsize);
	 if(!B)
	 {
	  free(B);
	  free(region);
	  zFILE::DirectFileAccess(FALSE);
	  return FXFALSE;
	 }

	 S = (FxU8*) region;
	 D = S;
	 S += bitsize;

	 while(h--)
	 {
	  S -= wsize;

	  memcpy(B,S,wsize);
	  memcpy(S,D,wsize);
	  memcpy(D,B,wsize);

	  D += wsize;
	 }

	 free(B);


	 /*
	  * write the tgaheader
	  */
	 fp = fopen(filename,"wb");
	 if(fp==NULL)
	 {
	  free(B);
	  free(region);
	  zFILE::DirectFileAccess(FALSE);
	  return FXFALSE;
	 }

	 fwrite((void*)tga_header,1,sizeof(tga_header),fp);

	 /*
	  * write pixels
	  */
	 D=region;
	 for( int i=0;i<bitsize/2;i++)
	 {
	  unsigned short rbits;
	  unsigned short gbits;
	  unsigned short bbits;
	  unsigned short abits;

	  rbits = gbits = bbits = * (unsigned short *)D;
	  rbits&=0xf100;
	  gbits&=0x07c0;
	  bbits&=0x001f;

	  abits=bbits;
	  abits|= (gbits>>1);
	  abits|= (rbits>>1);

	  fwrite((void *)&abits,1,2,fp);
	  D+=2;
	 }

	 fclose(fp);

	 free(region);
	 zFILE::DirectFileAccess(FALSE);
	 return FXTRUE;
}



static void DeletePath (zSTRING& res) {
	while (res.Search (zSTRING("\\")) != -1) {
		res.Delete (zSTRING("\\"), zSTR_TO);
	};
}



/* -------------------------------------------------------------------------------------
   From here: modified version of 3df.c included in the texus library 
   ------------------------------------------------------------------------------------- */

#define TEXFMT_SIZE(x)  ((x < GR_TEXFMT_16BIT) ? 1: ((x < GR_TEXFMT_32BIT) ? 2: 4))
// Read NCC table 


//******************************************** OTHER

static HHOOK mouseHook;
static int   nOldVal= 0;
HWND		 winHandle;    // FIXME: In zRndVid.h Vid_GetActiveWinHandle() ?

/*
typedef LRESULT (CALLBACK* HOOKPROC)(int code, WPARAM wParam, LPARAM lParam);
*/

#ifndef _MFC
static LRESULT CALLBACK AppMouseHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	return 1;
}
#endif

void DisableTaskSwitch()
{
	#ifndef _MFC
	if (0)
	if (!zoptions->Parm("ENABLETASKSWITCH")) 
	{
		// disable Win95 Keys
		SystemParametersInfo (SPI_SCREENSAVERRUNNING, 1, (void*)&nOldVal, 0);

		// setup mouse hook thus disabling mouse events
		mouseHook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)AppMouseHook, NULL, GetCurrentThreadId());
		assert(mouseHook!=0);
		RECT wRect;
		GetWindowRect(winHandle,&wRect);
		ClipCursor(&wRect);
	}
	#endif
};


void EnableTaskSwitch()
{
	#ifndef _MFC
	if (0)
	if (!zoptions->Parm("ENABLETASKSWITCH")) 
	{
		ClipCursor(0);
		SystemParametersInfo (SPI_SCREENSAVERRUNNING, 0, (void*)&nOldVal, 0);
		UnhookWindowsHookEx	 (mouseHook);						// Remove keyboard handler
	}
	#endif
}

