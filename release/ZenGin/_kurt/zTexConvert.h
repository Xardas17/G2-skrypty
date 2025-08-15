
/****************************************************************
*																
*
* File          : zTexConvert.h ()									
* Project       : Engine										
* Author        : Adrian Dalecki
* created		: 1999/07/15
*																
****************************************************************/

#ifndef __ZTEXCONVERT_H__
#define __ZTEXCONVERT_H__

#ifndef __ZRENDERER_H__
#include "zRenderer.h"
#endif

#ifndef __Z3D_H__
#include "z3d.h"
#endif

#ifndef __ZTYPES_H__
#include "Ztypes.h"
#endif

// instances are created by the renderer
typedef struct {	
	unsigned char b,g,r,a;
} RGBPIXEL;

class zCTexConGeneric : public zCTextureConvert
{
public:
	// all fileNames must be UPPER
	zCTexConGeneric();	// constructor....
	~zCTexConGeneric();	// destructor...

	// accessing contents (read, write, readOnly, writeOnly)
	zBOOL				Lock				(int lockMode);	// read/write, use 'zTTexLockMode' 
	zBOOL				Unlock				();				// read/write

	//
	zBOOL				SetTextureInfo		(const zCTextureInfo& texInfo);		// write
	void*				GetPaletteBuffer	();									// read/write
	zBOOL				GetTextureBuffer	(int mipMapNr, void* &buffer, int &pitchXBytes);	// read/write
	
	//
	zCTextureInfo		GetTextureInfo		();									// read/write
	zBOOL				CopyPaletteDataTo	(void* destBuffer);					// read
	zBOOL				CopyTextureDataTo	(int mipMapNr, void* destBuffer, int destPitchXBytes);		// read

	// query properties
	zCOLOR				GetAverageColor		();
	zBOOL				HasAlpha			();

	virtual zBOOL		ConvertTextureFormat (const zCTextureInfo& dsttexifo);
	virtual void		SetDetailTextureMode (const zBOOL b) { detailTextureMode = b; };	// in this mode, successive mipmaps fade to grey (0.5,0.5,0.5), FIXME: move this out of here

private:

	zCTextureInfo				texinfo;
	char						*tempptr;		// zeiger sperren
	char						pal[256*3];	// palettenbuffer (si
	zCTextureFileFormatInternal *ffi;
	zBOOL						alpha;
	zCOLOR						average;

	zTTexLockMode				lockMode;
	zBOOL						modified;
	zBOOL						detailTextureMode;
};

#endif