 

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_Init.h 
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.97pre
* last modified : 21.10.00
* erstellt      : 02.02.00										
* Compiler OK   : 
*																
*********************************************************************************
- known bugs: 

*********************************************************************************
- possible optimizations: 

*********************************************************************************
- missing features: 

*********************************************************************************
- comments:
  
TODO:

*********************************************************************************/



#ifndef __ZRNDD3D_INIT_H__
#define __ZRNDD3D_INIT_H__


#ifndef __ZRNDD3D_H__
#include "zRndD3D.h"
#endif

// [BENDLIN] Addon - Spacer: 'Compile NewWorld'
// max 16384 textures to buffer !!! (10000 before)
#define zD3DTEXMAX				(0x4000)

#define setpdfRGB(c,b,s)		c = ((c)>>(8-b)) << s;

#define RELEASE(x) if( x ) { x->Release(); x = NULL; }


typedef struct
{	
	char							name[256];
	char							desc[256];
	char							DeviceName[256];
	unsigned long					hardware;
	unsigned long					number;
	unsigned long					dxguidflag;
	GUID							guid;
	GUID							dxguid;
} dxDEVICE;

typedef struct
{	
	int	w;
	int h;
	int bpp;
} dxDDMODE;

typedef struct
{	
	int								mode;
	zCTex_D3D						*texture;
} zD3DTEX;


extern zD3DTEX						tex[zD3DTEXMAX];		// needed in _Texture and _Render
extern dxDEVICE						dxDevice[64];			// needed in _Render
extern dxDDMODE						dxDeviceMode[4][64];	// needed in _Render
extern int							dxDeviceModeNum[4];		// needed in _Render
extern DDPIXELFORMAT				pflist[32];				// needed in _Texture
extern zBOOL						supportDXTC[5];			// needed in _Texture

extern HINSTANCE					hInstApp;

 

#endif //#ifndef __zRndD3D_Init_H__