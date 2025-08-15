/******************************************************************************** 
 
     $Workfile:: zTexture.h          $                $Date:: 17.03.01 2:10    $
     $Revision:: 20                   $             $Modtime:: 17.03.01 0:17    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Material and Texture classes, used by Polygons
   created       : 30.7.97

 * $Log: /current_work/ZenGin/_Dieter/zTexture.h $
 * 
 * 20    17.03.01 2:10 Hildebrandt
 * 
 * 19    14.02.01 7:28 Hildebrandt
 * 
 * 18    31.01.01 18:24 Speckels
 * 
 * 17    28.01.01 23:57 Hildebrandt
 * 
 * 16    11.01.01 1:27 Hildebrandt
 * 
 * 15    10.01.01 17:35 Hildebrandt
 * 
 * 14    5.12.00 15:35 Hildebrandt
 * 
 * 13    4.12.00 18:23 Moos
 * 
 * 12    24.10.00 19:48 Hildebrandt
 * 
 * 11    21.08.00 17:18 Hildebrandt
 * 
 * 10    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 9     6.07.00 13:45 Hildebrandt
 * 
 * 6     8.05.00 5:29 Hildebrandt
 * zenGin 089g
 * 
 * 5     4.05.00 20:17 Hildebrandt
 * zenGin 089e
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 6     15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 5     18.02.00 3:05 Hildebrandt
 * zenGin 087b
 * 
 * 4     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 2     10.01.00 16:05 Hildebrandt

 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 20 $ ($Modtime: 17.03.01 0:17 $)

#ifndef __ZTEXTURE_H__
#define __ZTEXTURE_H__

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __ZRESOURCE_H__
#include <zResource.h>
#endif

#ifndef __ZRENDERER_H__
#include <zRenderer.h>
#endif

#ifndef __ZSCANDIR_H__
#include <zScandir.h>
#endif

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4305 ) 

/*
  ClassTree

  PI: pure abstract interface
  I : abstract interface (but contains code/data)

	- zCObject (PI)
		- zCResource (PI)
			- zCTexture (I)
				- zCTex_RndGlide
				- zCTex_D3D
		- zCTextureFileFormat (PI)
			- zCTextureFileFormatInternal
			- zCTextureFileFormatTGA
	- zCTextureExchange (PI)
		- zCTextureConvert (I)
			- zCTexConGeneric
*/

// ==========================================================================================================

enum zTTexScaleSize {
	zTEX_SCALE_SIZE_XY_ONE_LOWER=0,					// / 4
	zTEX_SCALE_SIZE_X_ONE_LOWER,					// / 2
	zTEX_SCALE_SIZE_REFERENCE,						// * 1 <==
	zTEX_SCALE_SIZE_Y_ONE_HIGHER,					// * 2
	zTEX_SCALE_SIZE_XY_ONE_HIGHER_EVERY_SECOND,		// * 2
	zTEX_SCALE_SIZE_Y_XY_ONE_HIGHER_EVERY_SECOND,	// * 3
	zTEX_SCALE_SIZE_XY_ONE_HIGHER,					// * 4
	zTEX_SCALE_SIZE_XY_MAX,							// * ?

	zTEX_SCALE_SIZE_COUNT
};

enum zTTexScaleBPP {
	zTEX_SCALE_BPP_S3TC=0,							// / 2
	zTEX_SCALE_BPP_REFERENCE,						// * 1 <==
	zTEX_SCALE_BPP_ONE_HIGHER,						// * 2
	zTEX_SCALE_BPP_MAX								// * ?
};

// ==========================================================================================================

// Palette Format: 
// - 768 bytes total
// - 256 entries, 3 bytes per entry
// - mem byte-order			: RGB
// - dword byte-order(intel): B (bits0-7), G (bits8-15), R (bits16-23)
// - (direct compatible to DirectX, Glide for example has to do some conversions)

enum { zTEX_PAL_SIZE_BYTES	= 3*256 };

struct zTTexPalette {
	zBYTE r,g,b;
};

// ATTENTION: bump archiver-version of 'zCTextureFileFormatInternal' every time this structure changes
class zENGINE_API zCTextureInfo {
public:
	zCTextureInfo()		{ memset (this, 0, sizeof(*this)); };

	zTRnd_TextureFormat	texFormat;
	int					sizeX;			// pixel
	int					sizeY;			// pixel
	int					numMipMap;

	//
	int					refSizeX;
	int					refSizeY;

	// alpha ? avgColor ?
	zCOLOR				averageColor;
//	int					alphaBitDepth;
//	void				*palette;		// nicht hier, oder ?
};

// ==========================================================================================================

class zCTextureExchange;

class zENGINE_API zCTextureFileFormat : public zCObject {
	zCLASS_DECLARATION (zCTextureFileFormat)
public:
	virtual	zBOOL				LoadTexture			(const zSTRING& fileName, zCTextureExchange* texFile)=0;
	virtual	zBOOL				SaveTexture			(const zSTRING& fileName, zCTextureExchange* texFile)=0;
	virtual	zBOOL				LoadTexture			(zFILE& inFile			, zCTextureExchange* texFile)=0;
	virtual	zBOOL				SaveTexture			(zFILE& inFile			, zCTextureExchange* texFile)=0;
	virtual const zSTRING&		GetFileExtension	() const=0;						// e.g. ".TGA"
	virtual zBOOL				CanSave				() const=0;
	virtual zBOOL				CanLoad				() const=0;

protected:
	virtual ~zCTextureFileFormat() {};		// use Release() instead !
};

// ==========================================================================================================

class zENGINE_API zCTextureFileFormatTGA : public zCTextureFileFormat {
	zCLASS_DECLARATION (zCTextureFileFormatTGA)
public:
	zCTextureFileFormatTGA();

	zBOOL				LoadTexture			(const zSTRING& fileName, zCTextureExchange* texFile); // expects fullPath: drive, path, filename, ext
	zBOOL				SaveTexture			(const zSTRING& fileName, zCTextureExchange* texFile) { return FALSE; };
	zBOOL				LoadTexture			(zFILE& inFile			, zCTextureExchange* texFile);
	zBOOL				SaveTexture			(zFILE& inFile			, zCTextureExchange* texFile) { return FALSE; };
	const zSTRING&		GetFileExtension	() const;
	zBOOL				CanSave				() const	{ return FALSE; };
	zBOOL				CanLoad				() const	{ return TRUE;	};

protected:
	~zCTextureFileFormatTGA();		// use Release() instead !
private:

#pragma pack (push, 1)							// Alignment ausschalten
	typedef struct {
		zBYTE	IDLength;		// length of Identifier String 
		zBYTE	CMapType;		// 0 = no map
		zBYTE	ImgType;		// image type (see below for values)
		zBYTE	CMapStartLo;
		zBYTE	CMapStartHi;
		zBYTE	CMapLengthLo;
		zBYTE	CMapLengthHi;
		zBYTE	CMapDepth;
		zWORD	XOffSet;
		zWORD	YOffSet;
		zBYTE	WidthLo;
		zBYTE	WidthHi;
		zBYTE	HeightLo;
		zBYTE	HeightHi;
		zBYTE	PixelDepth;
		zBYTE	ImageDescriptor;
	} zTTgaHeader;
#pragma pack (pop)								// Alignment ausschalten

    zTTgaHeader			tgaHeader;
	zTRnd_TextureFormat	texFormat;
	zCTextureInfo		texInfo;
	zBYTE				*palette;
	zBYTE				*data;					// walk
	zBYTE				*dataBase;				// base
	int					pitchXBytes;
	int					tgaRLE;
	int					tgaRLEflag;
	int					tgaRLEcount;
	int					tgaRLEsav[4]; 

	zBOOL				ReadTGAHeader	(zFILE *file);
	zBOOL				ReadTGAColorMap (zFILE *file);
	zBOOL				ReadTGARLEPixel	(zFILE *file, zBYTE *data, int pixsize);
	zBOOL				ReadTGASpan		(zFILE *file, zBYTE *data, int w, int pixsize);
	zBOOL				ReadTGAData		(zFILE *file);
};

// ==========================================================================================================

class zENGINE_API zCTextureFileFormatInternal : public zCTextureFileFormat {
	zCLASS_DECLARATION (zCTextureFileFormatInternal)
public:
	zCTextureFileFormatInternal();
	// zCTextureFileFormat interface
	zBOOL				LoadTexture			(const zSTRING& fileName, zCTextureExchange* texFile);	// expects just: drive, path, filename, ext (maps into DIR_COMPILED_TEXTURES)
	zBOOL				SaveTexture			(const zSTRING& fileName, zCTextureExchange* texFile);
	zBOOL				LoadTexture			(zFILE& inFile			, zCTextureExchange* texFile);
	zBOOL				SaveTexture			(zFILE& inFile			, zCTextureExchange* texFile);
	const zSTRING&		GetFileExtension	() const;
	zBOOL				CanSave				() const	{ return TRUE;				};
	zBOOL				CanLoad				() const	{ return TRUE;				};

	//
	void				SetLoadMaxPixelSize	(const int numHigherThanRef, const int maxPixelDim)	{ this->numHigherThanRef=numHigherThanRef; this->maxPixelDim=maxPixelDim; };
	void				SetShowSpyMessages	(const zBOOL b) { showSpyMessages=b; };

private:
	zCTextureInfo		texInfo;
	int					numHigherThanRef;
	int					maxPixelDim;
	zBOOL				showSpyMessages;

	zBOOL				ReadHeader			(zFILE& file);
	zBOOL				ReadData			(zFILE& file, zCTextureExchange* texFile, zBOOL skipUnreadBytes=FALSE);
	zBOOL				WriteHeader			(zFILE& file, zCTextureExchange* texFile);
	zBOOL				WriteData			(zFILE& file, zCTextureExchange* texFile);

	friend class zCTexture;
};

// ==========================================================================================================

enum zTTexLockMode { 
	zTEX_LOCK_READ	= 1,		// these can be or'ed together
	zTEX_LOCK_WRITE	= 2			// 'read' without 'write' means 'readOnly' and vice versa
}; 

// Abstract interface for exchanging texture data in various formats.

class zENGINE_API zCTextureExchange {
public:
	static zBOOL				CopyContents		(zCTextureExchange *srcTex, zCTextureExchange *dstTex);

	// tool
	int							GetMemSizeBytes		();

	virtual ~zCTextureExchange					() {};

	// accessing contents (read, write, readOnly, writeOnly)
	virtual zBOOL				Lock				(int lockMode)=0;						// read/write, use 'zTTexLockMode' 
	virtual zBOOL				Unlock				()=0;									// read/write

	//
	virtual zBOOL				SetTextureInfo		(const zCTextureInfo& texInfo)=0;		// write
	virtual void*				GetPaletteBuffer	()=0;									// read/write
	virtual zBOOL				GetTextureBuffer	(int mipMapNr, void* &buffer, int &pitchXBytes)=0;						// read/write
	
	//
	virtual zCTextureInfo		GetTextureInfo		()=0;									// read/write
	virtual zBOOL				CopyPaletteDataTo	(void* destBuffer)=0;					// read
	virtual zBOOL				CopyTextureDataTo	(int mipMapNr, void* destBuffer, int destPitchXBytes)=0;		// read

	// query properties
//	virtual zCOLOR				GetAverageColor		()=0;
	virtual zBOOL				HasAlpha			()=0;
	virtual zVEC4				GetRGBAAtTexel		(zREAL xpos, zREAL ypos);
private:
	zVEC4						GetRGBAAtPtr		(zBYTE* ptr, zTTexPalette* palPtr, const zTRnd_TextureFormat texFormat);
}; 

// ==========================================================================================================

// Abstract interface for converting texture data, data con be accessed from outside
// via the zCTextureExchange interface.
// Instances are created by the renderer.

class zENGINE_API zCTextureConvert : public zCTextureExchange {
public:
	// tools
	static int			CalcNumMipMaps			(zDWORD xdim, zDWORD ydim);
	static void			CorrectAspectRatio		(int& xdim, int& ydim);
	static void			CorrectPow2				(int& xdim, int& ydim);


	// all fileNames must be UPPER
	virtual ~zCTextureConvert					() {};
												
	// manual low-level access
	zBOOL				LoadInternal			(zFILE& file);
	zBOOL				SaveInternal			(zFILE& file);
	zBOOL				LoadFromFileFormat		(const zSTRING& fileName);						// looks at the fileName extension and then chooses the fileformat 
	zBOOL				SaveToFileFormat		(const zSTRING& fileName);
	zBOOL				LoadFromFileFormat		(zFILE& file, zCTextureFileFormat* fileFormat);	// uses specified texture file format
	zBOOL				SaveToFileFormat		(zFILE& file, zCTextureFileFormat* fileFormat);
												
	// contents manipulation					
	void				ConvertToNewFormat		(const zTRnd_TextureFormat& newTexFormat);
	void				ConvertToNewSize		(const int newTexSizeX, const int newTexSizeY);		// automatically corrects 1/8 aspect ratio faults
	void				GenerateMipMaps			();

	// main texture converting method (implement this !)
	virtual zBOOL		ConvertTextureFormat	(const zCTextureInfo& destTexInfo)=0;
	virtual void		SetDetailTextureMode	(const zBOOL b) { };	// in this mode, successive mipmaps fade to grey (0.5,0.5,0.5), FIXME: move this out of here
};

///////////////////////////////////////////////////////////////////////////
//     Texture
///////////////////////////////////////////////////////////////////////////

enum zTTexLoadFlags {
	zTEX_LOAD_FLAG_TILE		= 1			// treats the the texture as a 'texture-tile', these textures are sliced into separate textures if they are bigger than the maxSize the renderer permits
};

class zENGINE_API zCTexture : public zCResource, public zCTextureExchange {
	zCLASS_DECLARATION (zCTexture)

	zCTexture(const zCTexture&);				// disable
	zCTexture& operator=(const zCTexture&);		// disable
public:						
	static zSTRING			zTEX_DEFAULT_TEXTURE_FILE;
	static void				SetGlobalLoadTextures		(const zBOOL b)		{ s_globalLoadTextures = b;		};
	static zBOOL			GetGlobalLoadTextures		()					{ return s_globalLoadTextures;	};
	static void				AutoDetectRendererTexScale	();
	static void				RefreshTexMaxSize			(int newTexMaxSize=-1);	// refreshes the maximum side length, that a texture can have; -1 reads the value from the .INI settings, other values directly set the new size and are written to the .INI settings
	static zCTexture*		Load						(zSTRING& texFile, int texLoadFlags=0);				// creates new Texture-Object in List, loads tex from hd, use 'zTTexLoadFlags' for flags
	static zCTexture*		LoadSingle					(zSTRING& texFile, int texLoadFlags=0);				// creates new Texture-Object in List, loads tex from hd, use 'zTTexLoadFlags' for flags
	static zBOOL			Exists						(zSTRING &name);
	static void				ScanConvertTextures			(const zSTRING a_strSubDir);
	static zTRnd_TextureFormat	CalcNextBestTexFormat	(zTRnd_TextureFormat texFormat);
	enum					{ zTEX_MAX_ANIS = 3 };

	// methods				
			 zCTexture		();
	void					InitValues					();
														
	const zSTRING&			GetName						() const				{ return GetObjectName ();		};
	zBOOL					SetName						(const zSTRING& name)	{ return SetObjectName (name);	};

	// hint for procedural textures
	void					SetChangingRealtime			(const zBOOL b)			{ changingRealtime=b;		};
	zBOOL					GetChangingRealtime			() const				{ return changingRealtime;	};

	//
	zBOOL					IsTextureTile				() const				{ return isTextureTile;		};
	zBOOL					IsTextureTileBaseSlice		() const;

	// List Iterators => zCClassDef (zCMaterial::GetStaticClassDef())
	static zCTexture*		SearchName					(zSTRING& name);		// Tex mit Name suchen
							
	// Texture-Animation
	zBOOL					IsAnimated					() const				 { return isAnimated;				};
	int						GetNumAniFrames				(int aniNr) const		 { return numAniFrames[aniNr];		};
	int						GetActAniFrame				(int aniNr) const		 { return actAniFrame [aniNr];		};
	void					SetActAniFrame				(int aniNr, int frameNr) { actAniFrame[aniNr] = frameNr;	};
	zCTexture*				GetAniTexture				();
	void					AddAniTex					(int channel, zCTexture *tex);
	void					PrecacheTexAniFrames		(zREAL priority=zREAL(0.5F));	// range: [0;1]
			 										
	// the following 2 methods are used for lightmap persistance in world-files
	zBOOL					LoadAndConvertInternal		(zFILE &texFile);		// loads & autoConverts to a format that can be used by the renderer (eg lightmaps)
	zBOOL					SaveAndConvertInternal		(zFILE &texFile);


	// for secure access to map-data (disk/mem)
	void					ForceConvertAndReloadTexture();								// used for tools, if source file has changed
	void					GetPixelSize				(int& xdim, int &ydim);				// for mipmap level 0

	//
	zBOOL					HasAlphaChannel				()			{ return hasAlpha;		};

	// zCTextureExchange Interface
//	zCOLOR					GetAverageColor				()			{ return averageColor;	};
	zBOOL					HasAlpha					()			{ return hasAlpha;		};

	// zCResource Interface
	virtual zBOOL			LoadResourceData			();
	virtual zBOOL			ReleaseResourceData			();
	virtual zDWORD			GetResSizeBytes				();
	virtual void			GetCacheConfig				(zDWORD &cacheOutTimeMSec, zDWORD &cacheSizeMaxBytes);

	// zCTexture interface (public)
	// [empty]

	// OBSOLETE:										
	//virtual zCOLOR		GetAverageColor				()	{ zCOLOR col; col.SetRGBA (128,128,128,255); return col; };
	//		zBOOL			HasAlphaChannel				()	const { return FALSE; };
	virtual zBOOL			GetChromaKeyingEnabled		() const			{ return FALSE; };
	virtual void			SetChromaKeyingEnabled		(const zBOOL b)		{ };

protected:
//	static zCTexture		*s_texRoot;						// texture-list
	static zTTexScaleSize	s_texScaleSize;					// texture-mem scalability
	static zTTexScaleBPP	s_texScaleBPP;
	static zDWORD			s_texSupportedFormats;
	static zBOOL8			s_useDefaultTex;
	static zBOOL8			s_globalLoadTextures;
	static zDWORD			s_texMaxPixelSize;

//	zCTexture				*next;
//	zCTexture				*prev;
//	zCOLOR					averageColor;
							
	// Animation			
	zCTexture				*nextAni	[zTEX_MAX_ANIS];
	zCTexture				*prevAni	[zTEX_MAX_ANIS];
	int						actAniFrame	[zTEX_MAX_ANIS];
	int						numAniFrames[zTEX_MAX_ANIS];

	zBOOL					IsLightmap					() const;				// impl. is missing..

	// flags
	struct {
//		zUINT8				inMemory			: 1;				// .. or on hard-disk 
		zUINT8				hasAlpha			: 1;
		zUINT8				isAnimated			: 1;				// texture ani => frame Animation
		zUINT8				changingRealtime	: 1;				// is changing realtime ? (procedural texture)
		zUINT8				isTextureTile		: 1;				// a 'texture-tile', these textures are sliced into separate textures if they are bigger than the maxSize the renderer permits
	};

	// zCTexture interface (protected)
	virtual ~zCTexture		();							// use Release() instead !
	virtual void			ReleaseData				()=0;									// dispose main-memory data

private:
	static zBOOL			ConvertRecursive		();


	enum zTTexFileDesiredBPP {
		zTEX_FILE_DESIRED_BPP_S3TC,
		zTEX_FILE_DESIRED_BPP_8,
		zTEX_FILE_DESIRED_BPP_16,
		zTEX_FILE_DESIRED_BPP_32,
		zTEX_FILE_DESIRED_BPP_COUNT,
	};
	static zSTRING				s_texDesiredBPPSuffix	[zTEX_FILE_DESIRED_BPP_COUNT];
	static zTRnd_TextureFormat	s_texDesiredBPPDefault	[zTEX_FILE_DESIRED_BPP_COUNT];
	static zREAL				s_texRefRAM;
	static zTTexFileDesiredBPP	s_texRefBPP;
	static void					CalcDesiredBPP			(const zSTRING *texFileName, zTTexFileDesiredBPP &desiredBPP, zTRnd_TextureFormat &desiredTexFormat, zBOOL &needsConversion);
	static zBOOL				ConvertTexture			(const zSTRING &texFileName);
	zBOOL						CacheInNamed			(const zSTRING *texFileName);
	zBOOL						CreateTextureTile		(zCTextureExchange *texExchange);

	friend class zCTextureFileHandler;
};	


// for the lightmaps; was part of zCTexture once

class zCLightMap: public zCObject{ 
	zCLASS_DECLARATION (zCLightMap)

	// lightmap				
	zVEC3					lightmapOrigin;
	zVEC3					lightmapUVUp;
	zVEC3					lightmapUVRight;

    zCTexture              *tex;
public:
    zCLightMap();
    ~zCLightMap();

    void                    SetTexture(zCTexture *t);
    zCTexture*              Texture(){return tex;}


	// lightmaps			
	void					SetLightmapOriginUpRight	(const zVEC3& origin, const zVEC3& up, const zVEC3& right)  { lightmapOrigin=origin; lightmapUVUp=up; lightmapUVRight=right;  };
	void					GetLightmapOriginUpRight	(zVEC3& origin, zVEC3& up, zVEC3& right) const				{ origin= lightmapOrigin; up=lightmapUVUp; right=lightmapUVRight; };
	void					CalcLightmapOriginUpRight	(const zVEC3& origin, const zVEC3& up, const zVEC3& right);
	inline void				GetLightmapTexCoords		(const zPOINT3& posWorldSpace, float& u, float& v) const;
	inline const zVEC2		GetLightmapTexCoords		(const zPOINT3& posWorldSpace) const;
};

class zCTextureFileHandler : public zCScanDirFileHandler
{
public:
	zCTextureFileHandler() 
	{
		RegisterFileType("tga");
	};
	virtual ~zCTextureFileHandler() 
	{		
	};		

	virtual zBOOL HandleFile(const zSTRING& filename, const char* directory, _finddata_t fileinfo);	
};


// inlines


void zCLightMap::GetLightmapTexCoords (const zPOINT3& posWorldSpace, float& u, float& v) const {
	const zVEC3& q	= posWorldSpace - lightmapOrigin;
	u				= q				* lightmapUVRight;
	v				= q				* lightmapUVUp;
};

const zVEC2 zCLightMap::GetLightmapTexCoords (const zPOINT3& posWorldSpace) const {
	const zVEC3& q	= posWorldSpace - lightmapOrigin;
	return zVEC2 (q*lightmapUVRight, q*lightmapUVUp);
};




// enable VC++ Warning: double to float conversion
#pragma warning( default: 4305 ) 

#endif