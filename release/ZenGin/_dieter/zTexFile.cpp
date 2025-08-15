/******************************************************************************** 
 
     $Workfile:: zTexFile.cpp         $                $Date:: 27.01.01 19:42   $
     $Revision:: 17                   $             $Modtime:: 27.01.01 18:30   $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zTexFile.cpp $
 * 
 * 17    27.01.01 19:42 Moos
 * 
 * 16    27.01.01 2:45 Hildebrandt
 * 
 * 15    27.01.01 2:28 Hildebrandt
 * 
 * 14    11.01.01 1:27 Hildebrandt
 * 
 * 13    24.10.00 19:36 Hildebrandt
 * 
 * 12    31.08.00 17:04 Hildebrandt
 * 
 * 11    21.08.00 17:18 Hildebrandt
 * 
 * 10    8.08.00 22:38 Hildebrandt
 * 
 * 15    8.08.00 22:37 Hildebrandt
 * 
 * 14    8.08.00 0:50 Integrator
 * Gothic 0.89
 * 
 * 8     7.08.00 16:45 Pelzer
 * 
 * 7     1.08.00 0:20 Rueve
 * 
 * 6     21.07.00 15:11 Hildebrandt
 * 
 * 5     4.05.00 20:17 Hildebrandt
 * zenGin 089e
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 13    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 12    23.02.00 3:29 Hildebrandt
 * 
 * 11    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 9     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 8     10.01.00 21:34 Hildebrandt
 * 
 * 6     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     18.11.99 22:18 Hildebrandt
 * 
 * 4     13.11.99 1:10 Hildebrandt
 * 
 * 3     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 17 $ ($Modtime: 27.01.01 18:30 $)


#include <zCore.h>
#include <zMaterial.h>
#include <zoption.h>

/*
		zRND_TEX_FORMAT_ABGR_8888,				// 32, alpha 8
		zRND_TEX_FORMAT_BGR_565,				

		zRND_TEX_FORMAT_ARGB_8888,				// 32, alpha 8
		zRND_TEX_FORMAT_RGB_888,				// 24
		zRND_TEX_FORMAT_ARGB_4444,				// 16, alpha 4
		zRND_TEX_FORMAT_ARGB_1555,				//	 , alpha 1
		zRND_TEX_FORMAT_RGB_565,				
		zRND_TEX_FORMAT_PAL_8,					// 8
		zRND_TEX_FORMAT_S3TC,					// 4

*/

 
// ===================

zCLASS_DEFINITION_ABSTRACT	(zCTextureFileFormat		, zCObject			 , 0)
zCLASS_DEFINITION			(zCTextureFileFormatTGA		, zCTextureFileFormat, 0, 0)
zCLASS_DEFINITION			(zCTextureFileFormatInternal, zCTextureFileFormat, 0, 1)

/*

	TODO:
	- Mono / MonoRLE unterstützen
	- ist das alpha-Channel-handling ok ?

*/

// definitions for tga image types
enum zTTgaImageTypes {
	zTGA_NULL		= 0,
	zTGA_CMAP		= 1,
	zTGA_TRUE		= 2,
	zTGA_MONO		= 3,
	zTGA_CMAP_RLE	= 9,
	zTGA_TRUE_RLE	= 10,
	zTGA_MONO_RLE	= 11
};

zCTextureFileFormatTGA::zCTextureFileFormatTGA()
{
	palette			= 0;
	data			= 0;
	dataBase		= 0;
	pitchXBytes		= 0;
};

zCTextureFileFormatTGA::~zCTextureFileFormatTGA()
{
	palette			= 0;
	data			= 0;
	dataBase		= 0;
};

const zSTRING& zCTextureFileFormatTGA::GetFileExtension	() const
{ 
	static const zSTRING s_ext(".TGA"); 
	return s_ext; 
};

zBOOL zCTextureFileFormatTGA::ReadTGAHeader (zFILE *file)
{
    // Fill up rest of the TGA header
	if (file->Read (&tgaHeader, sizeof(tgaHeader))!=sizeof(tgaHeader)) 
	{
		zerr.Fault ("D: TGA: unexpected end of file");
		return FALSE;
	};
	
    // skip the image id fields
	{
		zBYTE	buf[255];
		int		size = (tgaHeader.IDLength) & 0xFF;
		if (size>0)
		if ((size>255) || (file->Read (&buf, size)!=size)) {
			zerr.Fault ("D: TGA: unexpected end of file");
			return FALSE;
		};
	};

    // set texInfo
	texInfo.sizeX		= tgaHeader.WidthHi  << 8 | tgaHeader.WidthLo;
	texInfo.sizeY		= tgaHeader.HeightHi << 8 | tgaHeader.HeightLo;
	texInfo.numMipMap	= 1;
	
    if ((texInfo.sizeX <= 0) || (texInfo.sizeY <= 0)) {
		zerr.Fault ("D: TGA: image width or height is 0");
		return FALSE;
    }

	// alpha-Channel ?
//	info->size = info->width*info->height*GR_TEXFMT_SIZE(info->format);
//	txAttribs.alphaBits = 0;
	int alphaBits = 0;
	if (tgaHeader.PixelDepth != 8)	alphaBits = tgaHeader.ImageDescriptor & 0xf;

	if (alphaBits > 0 ) {
		zerr.Message ("D: TGA: has alpha channel, bits: "+zSTRING(alphaBits));
//		sprintf(sD,"Texture has alpha channel. Number of bits: %i", txAttribs.alphaBits);
	}
//	int bytesPerPixel = (tgaHeader.PixelDepth + 1) >> 3;

	// analyze image format
    switch(tgaHeader.ImgType) {
		
		// a) mono image
		case zTGA_MONO:
		case zTGA_MONO_RLE:			
			zerr.Fault ("D: TGA: mono image not yet supported !");
			return FALSE;
/*			// True color image
			if (tgaHeader.PixelDepth != 8) {
				zerr.Fault ("D: TGA: mono image is not 8 bits/pixel");
				return FALSE;
			}
			info->format = GR_TEXFMT_I_8;*/
			break;
			
		// b) rgb image
		case zTGA_TRUE:
		case zTGA_TRUE_RLE:
			switch (tgaHeader.PixelDepth) {
			case	15: 
			case	16: 
				texFormat = (alphaBits>0) ? zRND_TEX_FORMAT_ARGB_1555 : zRND_TEX_FORMAT_RGB_565; 
				break;
			case	24: 
				texFormat = zRND_TEX_FORMAT_BGR_888; 
				if (alphaBits>0) {
					zerr.Fault ("D: TGA: cant read true color image with 24bpp and alphaBits: "+zSTRING(alphaBits));
					return FALSE; 
				};
				break;
			case	32: 
				texFormat = zRND_TEX_FORMAT_BGRA_8888; 
				if (alphaBits!=8) {
					zerr.Warning ("D: TGA: cant read true color image with 32bpp and alphaBits: "+zSTRING(alphaBits));
					alphaBits	= 8;
//					return FALSE; 
				};
				break;
			default:	
				zERR_FAULT ("D: TGA: True color image is not 15/16/24/32 bits/pixel.");
				return FALSE; 
				break;
			}
			break;
			
		// c) paletted image
		case zTGA_CMAP:
		case zTGA_CMAP_RLE:			
			if ( tgaHeader.CMapType != 1 ) {
				zERR_FAULT ("D: TGA: Color-mapped TGA image has no palette");
				return FALSE;
			}
			if (((tgaHeader.CMapLengthLo + tgaHeader.CMapLengthHi * 256L)
				+(tgaHeader.CMapStartLo  + tgaHeader.CMapStartHi * 256L)) > 256){
				zerr.Fault ("D: TGA: Color-mapped image has more than 256 colors");
				return FALSE;
			}
			texFormat = zRND_TEX_FORMAT_PAL_8;
			break;
				
		// d) unknown format
		default:
			zerr.Fault ("D: TGA: unsupported format");
			return  FALSE;
    }

	texInfo.texFormat = texFormat;
	return TRUE;
}

zBOOL zCTextureFileFormatTGA::ReadTGAColorMap (zFILE *file)
{
    if (tgaHeader.CMapType == 0)	return TRUE;		// no colormap
	if (!palette)					return FALSE;

    int	cmapStart;
    int	cmapLength;
    int	cmapDepth;
    int	i;
	
    cmapStart   = tgaHeader.CMapStartLo  + tgaHeader.CMapStartHi * 256L;
    cmapLength  = tgaHeader.CMapLengthLo + tgaHeader.CMapLengthHi * 256L;
    cmapDepth   = tgaHeader.CMapDepth;

    // Validate some parameters
    if (cmapStart < 0) {
		zerr.Fault ("D: TGA: Bad colorMap start value");
		return FALSE;
    }
	
    cmapDepth = (cmapDepth + 1) >> 3;		// convert bits to bytes
    if ((cmapDepth <= 0) || (cmapDepth > 4)) {
		zerr.Fault ("D: TGA: Bad colorMap depth");
		return FALSE;
    }
	
    // May have to skip the color map
    if ((tgaHeader.ImgType != zTGA_CMAP) && (tgaHeader.ImgType != zTGA_CMAP_RLE)) 
	{
		// True color, yet there is a palette, this is OK, just skip.
		file->Seek (file->Pos() + (cmapLength * cmapDepth));
		return TRUE;
    }
	
    // This is a real palette that's going to be used
	
    // Verify that it's not too large.
    if ((cmapStart + cmapLength) > 256) {
		zerr.Fault ("D: TGA: Color Map more than 256 entries");
		return FALSE;
    }
	
    // txPrint("cmapdepth = %d, start = %d, length = %d\n", cmapDepth,
    // 	cmapStart, cmapLength);
	int		r	= 0;
	int		g	= 0;
	int		b	= 0;
	int		a	= 0;
//	zBYTE	*pal= palette; ADRIAN: ausgeklammert, und stattdessen unsigend: signed speichert falsch ab!!!
	unsigned char	*pal= palette;
    for (i=0; i<256; i++) 
	{
		if ((i < cmapStart) || (i >= (cmapStart + cmapLength))) {
			*pal++	= 0;
			*pal++	= 0;
			*pal++	= 0;
			continue;
		}
		
		// Read this colormap entry.
		switch (cmapDepth) {
		case 1:	// 8 bpp
			file->Read (&r, 1);
			if (r == EOF) {
				zerr.Fault ("D: TGA: Unexpected End of File.");
				return FALSE;
			}
			r &= 0xFF;
//			palette[i] = (r << 24) | (r << 16) | (r << 8) | (r);
			*pal++	= r;
			*pal++	= r;
			*pal++	= r;
			break;
			
		case 2:	// 15, 16 bpp.
			
			file->Read (&b, 1);
			file->Read (&r, 1);
			if ((r == EOF) || (b == EOF)) {
				zerr.Fault ("D: TGA: Unexpected End of File.");
				return FALSE;
			}
			r &= 0xFF;
			b &= 0xFF;
			g = ((r & 0x3) << 6) + ((b & 0xE0) >> 2);
			r = (r & 0x7C) << 1;
			b = (b & 0x1F) << 3;
			
//			palette[i] = (r << 16) | (g << 8) | (b) | 0xFF000000L;
			*pal++	= b;
			*pal++	= g;
			*pal++	= r;
			break;
			
		case 3:
		case 4:
			// Alpha-Palette !
			// ABER: alpha wird ignoriert
			file->Read (&b, 1);
			file->Read (&g, 1);
			file->Read (&r, 1);
			if (cmapDepth == 4)	file->Read (&a, 1);
			else				a	= 0x0FF;
			
			if ((r == EOF) || (g == EOF) || (b == EOF) | (a == EOF)) {
				zerr.Fault ("D: TGA: Unexpected End of File.");
				return FALSE;
			}
//			palette[i] = (a << 24) | (r << 16) | (g << 8) | b;
			*pal++	= b;
			*pal++	= g;
			*pal++	= r;
			break;
			
		default:
				zerr.Fault ("D: TGA: Bad Color Map depth.");
			return FALSE;
		}
    }
    return TRUE;
}


zBOOL zCTextureFileFormatTGA::ReadTGARLEPixel( zFILE *file, zBYTE *data, int pixsize)
{
    int c=0;
	int i;
	
    // Run length encoded data Only
    if (tgaRLEcount == 0) 
	{
		// Need to restart the run.
		file->Read (&c, 1);
		tgaRLEcount = c;
		if (c==EOF) {
			zerr.Fault ("D: TGA: Unexpected End of File.");
			return FALSE;
		}
		tgaRLEflag	= tgaRLEcount & 0x80;
		tgaRLEcount = (tgaRLEcount & 0x7F) + 1;
		
		if (tgaRLEflag) {
			// Replicated color, read the color to be replicated 
			for (i=0; i<pixsize; i++) {
				file->Read (&c, 1);
				if (c == EOF) {
					zerr.Fault ("D: TGA: Unexpected End of File");
					return FALSE;
				}
				tgaRLEsav[i] = (zBYTE) c;
			}
		}
    }
	
    // Now deliver the data either from input or from saved values.
    tgaRLEcount--;
    if (tgaRLEflag) {
		// deliver from saved data.
		for (i=0; i<pixsize; i++) *data++ = (zBYTE) tgaRLEsav[i];
    } else {
		for (i=0; i<pixsize; i++) {
			file->Read (&c, 1);
			if (c == EOF) {
				zerr.Fault ("D: TGA: Unexpected End of File");
				return FALSE;
			}
			*data++ = (zBYTE) c;
		}
    }
    return TRUE;
}

zBOOL zCTextureFileFormatTGA::ReadTGASpan ( zFILE *file, zBYTE *data, int w, int pixsize)
{
    if (tgaRLE == 0) {
		if (file->Read (data, w*pixsize) != (zDWORD)(w*pixsize)) 
		{
			zerr.Fault ("D: TGA: Unexpected End of File");
			return FALSE;
		}
		return TRUE;
    }
	
    // Otherwise, RLE data.
    while (w--) {
		if (!ReadTGARLEPixel( file, data, pixsize)) {
			return FALSE;
		}
		data += pixsize;
    }
    return TRUE;
}

zBOOL zCTextureFileFormatTGA::ReadTGAData( zFILE *file)
{
    int			i, stride;
    int 		bpp;			// bytes per pixel
//	long		BigEndian	= 0xff000000;
	
    tgaRLEcount = 0;
    bpp			= (tgaHeader.PixelDepth + 1) >> 3;
	
    switch (tgaHeader.ImgType) {
		case zTGA_MONO		:	
		case zTGA_CMAP		:	
		case zTGA_TRUE		:	tgaRLE = 0; break;
		case zTGA_MONO_RLE	:
		case zTGA_TRUE_RLE	:
		case zTGA_CMAP_RLE	:	tgaRLE = 1; break;
    }
	
    // txPrint("bpp = %d, rle = %d\n", bpp, tgaRLE);

//	stride	= texInfo.sizeX * bpp;
	stride	= pitchXBytes;
	data	= dataBase;
    if ((tgaHeader.ImageDescriptor & 0x20) == 0) {
		// Origin is lower left
		data   = data + (texInfo.sizeY-1) * stride;
		stride = -stride;
    }
	
    // read palette if available
    if (!ReadTGAColorMap(file))	return FALSE;
	
    // Read in all the data
    for ( i = 0; i < texInfo.sizeY; i++) {
		if (!ReadTGASpan( file, data, texInfo.sizeX, bpp)) {
			zERR_FAULT ("D: TGA: Unexpected end of file.");
			return FALSE;
		}
		data += stride;
    }

    /*
		- BPP == 1 -> P8 or I8 formatted data.
		- BPP == 2 -> ARGB1555 formatted data.
		- BPP == 4 -> ARGB8888 formatted data.
		- BPP == 3  should be translated to ARGB8888 from RGB888.
	*/
	{
/*		if (bpp == 3) {
			int		npixels = texInfo.sizeX * texInfo.sizeY;
			zBYTE	*src = ((zBYTE *) dataBase) + (npixels - 1) * 3;
			zBYTE	*dst = ((zBYTE *) dataBase) + (npixels - 1) * 4;
			
			while (npixels--) {
				dst[0] = src[0];
				dst[1] = src[1];
				dst[2] = src[2];
				dst[3] = 0xFF;
				dst -= 4;
				src -= 3;
			}
		}
*/
/*		if (*(zBYTE *)&BigEndian) {
			// Repack 16bpp and 32bpp cases 
			if (bpp == 2) {
				int		npixels = texInfo.sizeX * texInfo.sizeY;
				zWORD	*src	= (zWORD*) dataBase;
				
				while (npixels--) {
					*src = (*src << 8) | ((*src >> 8) & 0xff);
					src++;
				}
			} else
			if ((bpp == 3) || (bpp == 4)) {
				int		npixels = texInfo.sizeX * texInfo.sizeY;
				zDWORD	*src	= (zDWORD *) dataBase;
				
				while (npixels--) {
					*src = (((*src      ) & 0xff)  << 24)|
            			   (((*src >>  8) & 0xff)  << 16)|
						   (((*src >> 16) & 0xff)  <<  8)|
						   (((*src >> 24) & 0xff)       );
					src++;
				}
			}
		}
*/
	};
    return TRUE;
}

// ==================================================================================================================

zBOOL zCTextureFileFormatTGA::LoadTexture (zFILE& inFile, zCTextureExchange* texFile)
{
	if (!texFile)	return FALSE;

	zerr.Message ("D: Loading Texture (.TGA): "+inFile.GetFile());

	if (!texFile->Lock				(zTEX_LOCK_WRITE))			return FALSE;
	if (!ReadTGAHeader				(&inFile))			return FALSE;

	if (!texFile->SetTextureInfo	(texInfo))			return FALSE;

	palette	= (zBYTE*)texFile->GetPaletteBuffer();

	void *dataTmp;
	texFile->GetTextureBuffer		(0, dataTmp, pitchXBytes);
	data		= (zBYTE*)dataTmp;
	if (!data)	return FALSE;
	dataBase	= data;

	if (!ReadTGAData				(&inFile))		return FALSE;
	if (!texFile->Unlock			())				return FALSE;

	return TRUE;
};

zBOOL zCTextureFileFormatTGA::LoadTexture (const zSTRING& fileName, zCTextureExchange* texFile)
{
	// erwartet kompletten fileName, mit Laufwerk, Pfad, Filename, ext
//	const zSTRING& fileNameComplete = zoptions->GetDirString(DIR_TEX) + fileName;
	const zSTRING& fileNameComplete = fileName;

	zFILE *file = zfactory->CreateZFile(fileNameComplete);
	if (!file)	return FALSE;

	// ist der Pfad bereits im Namen ?
	zBOOL ok	= file->Exists ();	
	if (ok) ok	= (file->Open(fileNameComplete)==zERR_NONE);
	
	if (!ok)
	{
		// Nein, also erst nach dem File suchen
		zSTRING fname (fileName);
		if (file->SearchFile (fname, zoptions->GetDirString(DIR_TEX))!=zERR_NONE) {
			delete file;
			return FALSE;
		};
		if (file->Open(file->GetFullPath())!=zERR_NONE) {
			delete file;
			return FALSE;
		};
	};

	zBOOL res = LoadTexture (*file, texFile);
	file->Close	();
	delete file;

	return res;
};

// ==================================================================================================================

// 'zCTextureFileFormatInternal' speichert die MipMaps einer Textur in der Reihenfolge kleiner=>groesser, damit
// beim Einladen ohne langsame Seeks hohe MipMapLevel geskippt werden koennen.
// Die zCTexture und zCTextureExchange Klassen nummerieren die MipMapLevel genau anders herum: 0 hoechste Aufloesung,
// 1 eine pow2 kleiner etc.

// *******************************
//		LOADING
// *******************************

	  char		zTEX_FILE_INTERNAL_COOKIE[]	= "ZTEX";
const zDWORD	zTEX_FILE_INTERNAL_VERS		= 0;

struct zTTFFHeader {
	char			cookie[4];
	zDWORD			vers;
	zCTextureInfo	texInfo;
};

zCTextureFileFormatInternal::zCTextureFileFormatInternal()
{
	numHigherThanRef= 0;
	maxPixelDim		= 65536;		// irgendeine unerreichbare Zahl
	showSpyMessages	= TRUE;
};

const zSTRING& zCTextureFileFormatInternal::GetFileExtension () const
{ 
	static const zSTRING s_ext(".TEX"); 
	return s_ext; 
};

zBOOL zCTextureFileFormatInternal::ReadHeader (zFILE& file)
{
	// FIXME: hieraus einen ENZIGEN file.Read machen!
	zTTFFHeader	header;
	file.Read	(&header,	sizeof(zTTFFHeader));
	if (header.vers!=zTEX_FILE_INTERNAL_VERS)	return FALSE;
	texInfo		= header.texInfo;

	// SetTextureInfo erst beim ReadData() !
	return TRUE;
}; 

zBOOL zCTextureFileFormatInternal::ReadData (zFILE& file, zCTextureExchange* texFile, zBOOL skipUnreadBytes)
{
	//
	const zTRnd_TexFormatInfo texFormatInfo = zrenderer->GetTexFormatInfo(texInfo.texFormat);

	// Sollen hoehere MipMap-Stufen weggelassen werden ?
	// Hier dann die neue Anzahl MipMap-Stufen und zu skippende Bytes berechnen
	int maxDimX		= zMin (maxPixelDim, (numHigherThanRef>=0) ? texInfo.refSizeX << numHigherThanRef : texInfo.refSizeX >> -numHigherThanRef);
	int maxDimY		= zMin (maxPixelDim, (numHigherThanRef>=0) ? texInfo.refSizeY << numHigherThanRef : texInfo.refSizeY >> -numHigherThanRef);
	int numMipMaps	= texInfo.numMipMap;
	int dimX		= texInfo.sizeX;
	int dimY		= texInfo.sizeY;
	int skipBytes	= 0;
	if (maxDimX<0)	maxDimX=1;
	if (maxDimY<0)	maxDimY=1;
	// beachte: es koennten hier auch Texturen mit numMipMaps==1 vorliegen..
	while (((dimX>maxDimX) || (dimY>maxDimY)) && (numMipMaps>1))
	{
		numMipMaps--;		
		// FIXME: was bei S3TC ??
//		skipBytes	+= (dimX*dimY) * zFloat2Int(zrenderer->GetTexFormatInfo (texInfo.texFormat).bytesPerPixel); //nochmal nachsehen
		skipBytes	+= zFloat2Int((dimX*dimY) * (zrenderer->GetTexFormatInfo (texInfo.texFormat).bytesPerPixel));
		dimX		>>= 1;
		dimY		>>= 1;
		if (numMipMaps<=1)	break;	// falls das File nicht alle Mipmaps runter bis 1x1 hat..
		assert(numMipMaps>=0);
	};
	assert (numMipMaps!=0);
	texInfo.sizeX		= dimX;
	texInfo.sizeY		= dimY;

/* [Pelzer] Eingefuegt und wieder auskommentiert

	//Bei DXT1 und DXT3 nur Mipmaps bis maximal 4*4 herunter erlaubt.
	//Also muss die Mipmap-Anzahl gegebenenfalls begrenzt werden.
	if( (texInfo.texFormat==zRND_TEX_FORMAT_DXT1)||(texInfo.texFormat==zRND_TEX_FORMAT_DXT3) )
	{
		switch( dimX>>numMipMaps )
		{
		case 1:
			numMipMaps -= 2;
		case 2:
			--numMipMaps;
		}
		switch(	dimY>>numMipMaps )
		{
		case 1:
			numMipMaps -= 2;
		case 2:
			--numMipMaps;
		}
		if( numMipMaps<=0 )
			zerr.Fault ("X/D: ReadData: numMipMaps <= 0.");
		//assert(numMipMaps>0);
	}
*/
	texInfo.numMipMap	= numMipMaps;

	// Wird jetzt erst gemacht (da jetzt erst wahre dimX/Y bekannt)
	if (!texFile->Lock(zTEX_LOCK_WRITE))	return FALSE;
	texFile->SetTextureInfo	(texInfo);

	// palette
	zBYTE *palette	= (zBYTE*)texFile->GetPaletteBuffer();
	if (palette) {
		if (file.Read (palette, zTEX_PAL_SIZE_BYTES	) != zTEX_PAL_SIZE_BYTES)	return FALSE;
	};

	// data
	void	*data;
	int		destPitchXBytes;
	int		sizeX;
	int		sizeY;
	for (int i=texInfo.numMipMap-1; i>=0; i--) 
	{
		if (!texFile->GetTextureBuffer(i, data, destPitchXBytes)) return FALSE;	
		if (!data) return FALSE;
		
		sizeX = texInfo.sizeX >> i;		if (sizeX<1) sizeX=1;
		sizeY = texInfo.sizeY >> i;		if (sizeY<1) sizeY=1;

		// Zeilenweise einlesen ?
		int srcPitchXBytes = zFloat2Int(texFormatInfo.bytesPerPixel * sizeX);
		if (destPitchXBytes!=srcPitchXBytes) 
		{
			// Zeilenweise
			// FIXME:  Das ist langsam - aber es kommt nicht oft vor (MR 310700)
			
			for (int yrun=0; yrun<sizeY; yrun++) 
			{
				if (file.Read (data, srcPitchXBytes) != srcPitchXBytes) return FALSE;
				data = (zBYTE*)data + destPitchXBytes;
			};
		} else {
			// gesamtes Texture in 1 Rutsch
//			int dataSize = zFloat2Int(texFormatInfo.bytesPerPixel) * (sizeX*sizeY); //@TODO: nochmal nachsehen
			int dataSize = zFloat2Int(texFormatInfo.bytesPerPixel * (sizeX*sizeY));
			if (file.Read (data, dataSize) != dataSize) return FALSE;
		};
	};

	// ungelesenes Ende skippen ?
	if (skipUnreadBytes) 
	{
		file.Seek	(file.Pos()+skipBytes);
	};

	if (!texFile->Unlock())	return FALSE;

	return TRUE;
};

zBOOL zCTextureFileFormatInternal::LoadTexture (zFILE& inFile, zCTextureExchange* texFile)
{
	if (!texFile)	return FALSE;

//	if (showSpyMessages)
//		zERR_MESSAGE (8,0, "D: Loading Texture (internal): "+inFile.GetFile());

	if (!ReadHeader				(inFile))			return FALSE;
	if (!ReadData				(inFile, texFile))	return FALSE;

	return TRUE;
};

zBOOL zCTextureFileFormatInternal::LoadTexture (const zSTRING& fileName, zCTextureExchange* texFile)
{
	// erwartet alleinig Filename, ext (NICHT aber: Laufwerk, Pfad)
	const zSTRING& fileNameComplete = zoptions->GetDirString(DIR_COMPILED_TEXTURES) + fileName;
	zFILE *file = zfactory->CreateZFile(fileNameComplete);
	if (!file)	return FALSE;

	zBOOL res;
	file->Open	(fileNameComplete);
//	if (file->IsOpened())
	{
		res	= LoadTexture (*file, texFile);
		file->Close	();
	} 
/*	else
	{
		res = FALSE;
	};*/
	delete file;

	return res;
};

// *******************************
//		SAVING
// *******************************

zBOOL zCTextureFileFormatInternal::WriteHeader (zFILE& file, zCTextureExchange* texFile)
{
	texInfo = texFile->GetTextureInfo();

	zTTFFHeader	header;
	memcpy			(header.cookie, zTEX_FILE_INTERNAL_COOKIE, sizeof(header.cookie));
	header.vers		= zTEX_FILE_INTERNAL_VERS;
	header.texInfo	= texInfo;
	file.Write		(&header,	sizeof(zTTFFHeader));
	return TRUE;
};

zBOOL zCTextureFileFormatInternal::WriteData (zFILE& file, zCTextureExchange* texFile)
{
	// palette
	zBYTE* palette	= (zBYTE*)texFile->GetPaletteBuffer();
	if (palette) {
		file.Write (palette, zTEX_PAL_SIZE_BYTES);
	};

	const zTRnd_TexFormatInfo texFormatInfo = zrenderer->GetTexFormatInfo(texInfo.texFormat);

	// data
	void	*data;
	int		srcPitchXBytes;
	int		sizeX;
	int		sizeY;
	for (int i=texInfo.numMipMap-1; i>=0; i--) 
	{
		texFile->GetTextureBuffer(i, data, srcPitchXBytes);	
		if (!data) return FALSE;

		sizeX = texInfo.sizeX >> i;		if (sizeX<1) sizeX=1;
		sizeY = texInfo.sizeY >> i;		if (sizeY<1) sizeY=1;

		// Zeilenweise schreiben ?
		int destPitchXBytes = zFloat2Int(texFormatInfo.bytesPerPixel * sizeX);	// pitch im File auf Disk (Dest)
		if (destPitchXBytes!=srcPitchXBytes) 
		{
			// Zeilenweise
			for (int yrun=0; yrun<sizeY; yrun++) 
			{
				if (file.Write(data, destPitchXBytes) != destPitchXBytes) return FALSE;
				data = (zBYTE*)data + srcPitchXBytes;
			};
		} else {
			// gesamtes Texture in 1 Rutsch
//			int dataSize = zFloat2Int(texFormatInfo.bytesPerPixel) * (sizeX*sizeY); //@TODO: nochmal nachsehen
			int dataSize = zFloat2Int(texFormatInfo.bytesPerPixel * (sizeX*sizeY));
			if (file.Write (data, dataSize) != dataSize) return FALSE;
		};
	};

	return TRUE;
};

zBOOL zCTextureFileFormatInternal::SaveTexture (zFILE& inFile, zCTextureExchange* texFile)
{
	if (!texFile)	return FALSE;
//	zerr.Message ("D: Saving Texture (internal): "+inFile.GetFile());

	if (!texFile->Lock		(zTEX_LOCK_READ))	return FALSE;
	if (!WriteHeader		(inFile, texFile))	return FALSE;
	if (!WriteData			(inFile, texFile))	return FALSE;
	if (!texFile->Unlock	())					return FALSE;

	return TRUE;
};

zBOOL zCTextureFileFormatInternal::SaveTexture (const zSTRING& fileName, zCTextureExchange* texFile)
{
	const zSTRING& fileNameComplete = zoptions->GetDirString(DIR_COMPILED_TEXTURES) + fileName;
	zFILE *file = zfactory->CreateZFile(fileNameComplete);
	if (!file)	return FALSE;

	if (showSpyMessages)
	{
		const zCTextureInfo&	texInfo			= texFile->GetTextureInfo();
		zTRnd_TexFormatInfo		texFormatInfo	= zrenderer->GetTexFormatInfo (texInfo.texFormat);
		zerr.Message			("D: Saving Texture (internal): "+fileName+" ("+
								 zSTRING(texInfo.sizeX)+"x"+zSTRING(texInfo.sizeX)+"x"+
								 zSTRING(int(texFormatInfo.bytesPerPixel*8))+
								 ", mips: "+zSTRING(texInfo.numMipMap)+")");
	};

	file->Create	(fileNameComplete);
	zBOOL res		= SaveTexture (*file, texFile);
	file->Close		();
	delete file;

	return res;
};

