// zRndD3D_TexConvert.cpp
//
//   texture-convertierungsutility
//   absolut systemunabhaenging, d.h. diese
//   routinen enthalten keinerlei DirectX-calls
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <s3_intrf.h>

#include "zcore.h"
#include "zMaterial.h"
#include "z3d.h"
#include "zArchiver.h"
#include "zTexConvert.h"

#define	zRND_TEX_FORMAT_REFERENCE	zRND_TEX_FORMAT_PAL8

//	 InitTexConvert
//   initialisiering der routinen (optional)
//   hier werden vorallem die tabellen fuer die umrechnung
//   angelegt.
//
#define	usergbtab			0			// nicht nutzen

#define	formatRGB555		0			// alpha ignorieren
#define	formatRGB1555		1			
#define	formatRGB565		2			
#define	formatRGB4444		3			
#define	formatRGB888		4
#define	formatBGR888		5
#define	formatRGBA8888		6
#define	formatBGRA8888		7
#define	formatRGB8			8			// eigentlich sollte es "graustufentextur" heissen.
#define	formatPAL8			9
#define	formatARGB8888		10
#define	formatABGR8888		11
#define formatDXT1			12
#define formatDXT2			13
#define formatDXT3			14
#define formatDXT4			15
#define formatDXT5			16

static	float	pixelsizes[]={ 2,2,2,2, 3,3, 4,4, 1,1,4,4, 1,1,1,1 }; //@TODO: 4-letzter Wert auf 0.5f ?
 
static	RGBPIXEL *rgbtab=NULL,*rgbbuff=NULL;
 

extern void tcCreatePalette(RGBPIXEL *src,zBYTE *pal,int size);
extern void tcConvertTexture(RGBPIXEL *src,zBYTE *dest,zBYTE *pal,int size);


/* ----------------------------------------------------------------------
	
	InitTexConvert()

	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static void InitTexConvert(void)
{	
	int t;
	RGBPIXEL *tex;
	// erstmal nur 2 tabellen anlegen
	// fuer 1555 und 565
	// mit je 65536 eintraegen a 32 bit fuer jeden eingelesenen wert
	// rgbtab = (RGBPIXEL*) malloc(65536*2*4);
    
    delete[] rgbtab;
    rgbtab = zNEW_ARRAY(RGBPIXEL,65536*2);
	// 1555
	tex = (RGBPIXEL*)rgbtab;
	for(t=0;t<65535;t++){	
		tex->r = ((t>>10)&31)<<3;
		tex->g = ((t>>5)&31)<<3;
		tex->b = (t&31)<<3;
		tex->a = ((t>>15)&1)*0xFF;		// alle 1-bits werden dadurch zu einer 255
		tex++;
	}
	// 565
	for(t=0;t<65535;t++){
		tex->r = ((t>>11)&31)<<3;
		tex->g = ((t>>5)&63)<<2;
		tex->b = (t&31)<<3;
		tex->a = 0xFF;
		tex++;
	}
}



/* ----------------------------------------------------------------------
	
	FreeTexConvert() : Buffer wieder freigeben

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void FreeTexConvert(void)
{
	//free(rgbtab); rgbtab=0;
    delete[] rgbtab;
    rgbtab=NULL;
}

//
// schnelle routinen zum skalierten
// kopieren. aus performancegruenden
// gibts hier fuer jede pixelbitgroesse
// eine eigene routine. 
// die routinen koennten in C kuerzer geschrieben
// werden. aber nicht schneller.
//
_inline void rcopy8(void *src,void *dest,int dstx,int dsty,int srcoff,float srcdx,float srcdy)
{
	int t,r;
	float srcx,srcy;
	zBYTE  *src8,*dest8,*SRCX;

	dest8 = (zBYTE*) dest;
	src8 = (zBYTE*) src;
	srcy = 0;
	for(t=0;t<dsty;t++)	{	
		srcx = 0;														// erstes zeichen...
		SRCX = &src8[(int)(srcy) * srcoff];	// anfangsadresse der zeile
		for(r=0;r<dstx;r++){	
			dest8[r]=SRCX[(int)(srcx)];
			srcx +=srcdx;
		}
		dest8+=dstx;
		srcy += srcdy;	// offset weiterzaehlen...
	}
}

_inline void rcopy16(void *src,void *dest,int dstx,int dsty,int srcoff,float srcdx,float srcdy)
{
	int t,r;
	float srcx,srcy;
	unsigned short  *src16,*dest16,*SRCX;

	dest16 = (unsigned short*) dest;
	src16 = (unsigned short*) src;
	srcy = 0;
	for(t=0;t<dsty;t++)	{	
		srcx = 0;														// erstes zeichen...
		SRCX = &src16[(int)(srcy) * srcoff];	// anfangsadresse der zeile
		for(r=0;r<dstx;r++)	{	
			dest16[r]=SRCX[(int)(srcx)];
			srcx +=srcdx;
		}
		dest16+=dstx;
		srcy += srcdy;	// offset weiterzaehlen...
	}
}

_inline void rcopy24(void *src,void *dest,int dstx,int dsty,int srcoff,float srcdx,float srcdy)
{
	int t,r;
	float srcx,srcy;
	zBYTE  *src24,*dest24,*SRCX;

	dest24 = (zBYTE*) dest;
	src24 = (zBYTE*) src;
	srcy = 0;
	for(t=0;t<dsty;t++){	
		srcx = 0;														// erstes zeichen...
		SRCX = &src24[((int)srcy) * (srcoff*3)];	// anfangsadresse der zeile
		for(r=0;r<dstx;r++)	{	
			dest24[(r*3)]=SRCX[((int)srcx)*3];
			dest24[(r*3)+1]=SRCX[(((int)srcx)*3)+1];
			dest24[(r*3)+2]=SRCX[(((int)srcx)*3)+2];
			srcx +=srcdx;
		}
		dest24+=dstx*3;
		srcy += srcdy;	// offset weiterzaehlen...
	}
}


_inline void rcopy32(void *src,void *dest,int dstx,int dsty,int srcoff,float srcdx,float srcdy)
{
	int t,r;
	float srcx,srcy;
	unsigned long  *src32,*dest32,*SRCX;

	dest32 = (unsigned long*) dest;
	src32 = (unsigned long*) src;
	srcy = 0;
	for(t=0;t<dsty;t++)	{	
		srcx = 0;														// erstes zeichen...
		SRCX = &src32[(int)(srcy) * srcoff];	// anfangsadresse der zeile
		for(r=0;r<dstx;r++)	{	
			dest32[r]=SRCX[(int)(srcx)];
			srcx +=srcdx;
		}
		dest32+=dstx;
		srcy += srcdy;	// offset weiterzaehlen...
	}
}


//
// ResizeTexture
//  hier wird die textur umskaliert.
//  die automatische skalierung ist nicht besonders
//  schoen, das sie nur die Nearest-methode verwendet.
//  (d.h. bei verkleinerungen wird nicht runtergesampelt)
//  mit dieser funktio
//
char *ResizeTexture(int *srcsize,int dstx,int dsty, void *src, void *dest,unsigned long fmt)
{	
	float	srcx,srcy,srcdx,srcdy;
	srcx = (float) srcsize[0];
	srcy = (float) srcsize[1];

	// offsets fuer die umrechnung berechnen...
	srcdx = srcx/dstx;			
	srcdy = srcy/dsty;
	//
	srcy = 0;
	if (pixelsizes[fmt]==1)	rcopy8(src,dest,dstx,dsty,srcsize[0],srcdx,srcdy);	else
	if (pixelsizes[fmt]==2)	rcopy16(src,dest,dstx,dsty,srcsize[0],srcdx,srcdy);	else
	if (pixelsizes[fmt]==3) rcopy24(src,dest,dstx,dsty,srcsize[0],srcdx,srcdy);	else
	if (pixelsizes[fmt]==4)	rcopy32(src,dest,dstx,dsty,srcsize[0],srcdx,srcdy);	

	return (char*)dest;
}

//
// custom -> RGB
//
//
// Hier kommt jetzt ein ganzer set von konvertierungroutinen
// aus geschwindigkeitsgruenden, gibts fuer jeden typ
// eine eigene routine.
//
_inline void getRGB555(int size,unsigned short *src,RGBPIXEL *dest)
{
	
	if(rgbtab)	{	// wenn speicher da ist...
		while(size>0){	
			*dest = rgbtab[(*src++)|0x8000];		// bit 15 immer setzen (damit die konvertierung korrekte alphawerte hat)
			size--;	dest++;
		}
	} 
	else {	// alte methode
		unsigned short a;
		while(size>0){	
			a=*src;
			dest->r = ((a>>10)&31)<<3;
			dest->g = ((a>>5)&31)<<3;
			dest->b = (a&31)<<3;
			dest->a = 0;
			dest++;	size--;	src++;
		}
	}
}

_inline void getRGB1555(int size,unsigned short *src,RGBPIXEL *dest){
	
	if(rgbtab)	{	// wenn speicher da ist...
		while(size>0){	
			*dest = rgbtab[*src++];
			size--;	dest++;
		}
	} 
	else{	// alte methode (vieeeeel langsamer...)
		unsigned short a;
		while(size>0){	
			a = *src;
			dest->r = ((a>>10)&31)<<3;
			dest->g = ((a>>5)&31)<<3;
			dest->b = (a&31)<<3;
			dest->a = (a>>15)*0xFF;	// sicher ist sicher...(ein interger-mul ist schneller, als ein if...)
			dest++;	size--;	src++;
		}
	}
}

_inline void getRGB565(int size,unsigned short *src,RGBPIXEL *dest)
{	
	if(rgbtab){	// wenn speicher da ist...
		while(size>0){	
			*dest = rgbtab[65536+(*src++)];
			size--; dest++;
		}
	} 
	else{	
		unsigned short a;
		while(size>0){	
			a = *src;
			dest->r = ((a>>11)&31)<<3;
			dest->g = ((a>>5)&63)<<2;
			dest->b = (a&31)<<3;
			dest->a = 0xFF;
			dest++;	size--; src++;
		}
	}
}

_inline void getRGB4444(int size,unsigned short *src,RGBPIXEL *dest)
{	
	unsigned short a;
	while(size>0){	
		a = *src;
		dest->r = ((a>>8)&15)<<4;
		dest->g = ((a>>4)&15)<<4;
		dest->b = (a&15)<<4;
		dest->a = ((a>>12)&15)<<4;;
		dest++;	size--; src++;
	}
}

_inline void getBGR888(int size,zBYTE *src,RGBPIXEL *dest)
{	
	while(size>0){	
		dest->r = src[2];
		dest->g = src[1];
		dest->b = src[0];
		dest->a = 0xFF;
		dest++;	size--; src+=3;
	}
}

_inline void getABGR8888(int size,zBYTE *src,RGBPIXEL *dest)
{	
	while(size>0){	
		dest->r = src[3];
		dest->g = src[2];
		dest->b = src[1];
		dest->a = src[0];
		dest++;	size--; src+=4;
	}
}

_inline void getBGRA8888(int size,zBYTE *src,RGBPIXEL *dest)
{	
	while(size>0){	
		dest->r = src[2];
		dest->g = src[1];
		dest->b = src[0];
		dest->a = src[3];
		dest++;	size--; src+=4;
	}
}


_inline void getRGB888(int size,zBYTE *src,RGBPIXEL *dest)
{	
	while(size>0){	
		dest->r = src[0];
		dest->g = src[1];
		dest->b = src[2];
		dest->a = 0xFF;
		dest++;	size--; src+=3;
	}
}

_inline void getRGBA8888(int size,zBYTE *src,RGBPIXEL *dest)
{	
	while(size>0){	
		dest->r = src[0];
		dest->g = src[1];
		dest->b = src[2];
		dest->a = src[3];
		dest++;	size--; src+=4;
	}
}

_inline void getARGB8888(int size,zBYTE *src,RGBPIXEL *dest)
{	
	while(size>0){	
		dest->r = src[1];
		dest->g = src[2];
		dest->b = src[3];
		dest->a = src[0];
		dest++;	size--; src+=4;
	}
}

_inline void getRGB8(int size,zBYTE *src,RGBPIXEL *dest)
{	
	while(size>0){	
		dest->r = src[0];
		dest->g = src[0];
		dest->b = src[0];
		dest->a = 0xFF;
		dest++;	size--; src++;
	}
}

_inline void getPAL8(int size,zBYTE *src,RGBPIXEL *dest,zBYTE *pal)
{	
	unsigned long a;
	while(size>0){	
		a = (*src++) * 3;
		dest->r = pal[a+2];
		dest->g = pal[a+1];
		dest->b = pal[a+0];
		dest->a = 0xFF;
		dest++;	size--;
	}
}

_inline void getDXT1(int size,zBYTE *src,RGBPIXEL *dest,int nWidth,int nHeight)
{	
	//Specify a width and height that are a multiple of 4 pixels
	if(nWidth<4)
		return;
	if(nHeight<4)
		return;

//	unsigned int	*blockcolor = (unsigned int*)src;

	DDSURFACEDESC descIn;
	DDSURFACEDESC descOut;

	descIn.dwSize							= sizeof(descIn);
	descIn.dwFlags							= DDSD_WIDTH|DDSD_HEIGHT|DDSD_LPSURFACE|DDSD_PIXELFORMAT;
	descIn.dwWidth							= nWidth;
	descIn.dwHeight							= nHeight;
	descIn.dwLinearSize						= nWidth/2;
	descIn.lpSurface						= src;
	descIn.ddpfPixelFormat.dwFlags			= DDPF_FOURCC;
	descIn.ddpfPixelFormat.dwFourCC			= MAKEFOURCC('D','X','T','1');
	descIn.ddpfPixelFormat.dwRGBBitCount	= S3TC_ENCODE_RGB_FULL|S3TC_ENCODE_ALPHA_NONE;

	descOut.dwSize = sizeof(descOut);

	S3TCdecode(&descIn,&descOut,dest);
}

_inline void getDXT2(int size,zBYTE *src,RGBPIXEL *dest,int nWidth,int nHeight)
{
	zerr.Warning( "Texture-Convert: getDXT2 is not supported yet ! " );
}

_inline void getDXT3(int size,zBYTE *src,RGBPIXEL *dest,int nWidth,int nHeight)
{
	//Specify a width and height that are a multiple of 4 pixels
	if(nWidth<4)
		return;
	if(nHeight<4)
		return;

	DDSURFACEDESC descIn;
	DDSURFACEDESC descOut;

	descIn.dwSize							= sizeof(descIn);
	descIn.dwFlags							= DDSD_WIDTH|DDSD_HEIGHT|DDSD_LPSURFACE|DDSD_PIXELFORMAT;
	descIn.dwWidth							= nWidth;
	descIn.dwHeight							= nHeight;
	descIn.dwLinearSize						= nWidth;
	descIn.lpSurface						= src;
	descIn.ddpfPixelFormat.dwFlags			= DDPF_FOURCC;
	descIn.ddpfPixelFormat.dwFourCC			= MAKEFOURCC('D','X','T','3');
	descIn.ddpfPixelFormat.dwRGBBitCount	= S3TC_ENCODE_ALPHA_EXPLICIT;

	descOut.dwSize = sizeof(descOut);

	S3TCdecode(&descIn,&descOut,dest);
}

_inline void getDXT4(int size,zBYTE *src,RGBPIXEL *dest,int nWidth,int nHeight)
{
	zerr.Warning( "Texture-Convert: getDXT4 is not supported yet ! " );
}

_inline void getDXT5(int size,zBYTE *src,RGBPIXEL *dest,int nWidth,int nHeight)
{
	zerr.Warning( "Texture-Convert: getDXT5 is not supported yet ! " );
}


//
// RGB -> custom
//
//
// Hier kommt jetzt ein ganzer set von konvertierungroutinen
// aus geschwindigkeitsgruenden, gibts fuer jeden typ
// eine eigene routine.
//
_inline void setRGB555(int size,RGBPIXEL *src,unsigned short *dest)
{	
	while(size>0){	
		*dest++ = ((src->r>>3)<<10)|((src->g>>3)<<5)|(src->b>>3);
		src++; size--;
	}
}

_inline void setRGB1555(int size,RGBPIXEL *src,unsigned short *dest)
{	
	while(size>0){	
		*dest++ = ((src->a>>7)<<15)|((src->r>>3)<<10)|((src->g>>3)<<5)|(src->b>>3);
		src++; size--;
	}
}

_inline void setRGB565(int size,RGBPIXEL *src,unsigned short *dest)
{	
	while(size>0)	{	
		*dest++ = ((src->r>>3)<<11)|((src->g>>2)<<5)|(src->b>>3);
		src++; size--;
	}
}

_inline void setRGB4444(int size,RGBPIXEL *src,unsigned short *dest)
{	
	//unsigned short d;
	while(size>0){	
		*dest++ = ((src->a>>4)<<12)|((src->r>>4)<<8)|(src->g & 0xF0)|(src->b>>4);
		src++; size--;
	}
}

_inline void setRGB888(int size,RGBPIXEL *src,zBYTE *dest)
{	
	while(size>0){	
		dest[0] = src->r;
		dest[1] = src->g;
		dest[2] = src->b;
		dest+=3;
		src++; size--;
	}
}

_inline void setRGB8888(int size,RGBPIXEL *src,unsigned long *dest)
{	
	unsigned long *S = (unsigned long*) src;
	while(size>0){	
		*dest++ = *S++;
		size--; 
	}
}

_inline void setRGB8(int size,RGBPIXEL *src,zBYTE *dest)
{	
	while(size>0){	
		*dest++ = ((src->r)+(src->g)+(src->b))/3;
		src++; size--;
	}
}

_inline void setPAL8(int size,RGBPIXEL *src,zBYTE *dest,zBYTE *pal)
{	
	tcConvertTexture(src,dest,pal,size);
}

_inline void setDXT1(int size,RGBPIXEL *src,zBYTE *dest,int nWidth,int nHeight,zBOOL alpha)
{	
	//Specify a width and height that are a multiple of 4 pixels
	if(nWidth<4)
		return;
	if(nHeight<4)
		return;

	DDSURFACEDESC descIn;
	DDSURFACEDESC descOut;
	float weight[3]		= {0.3086f,0.6094f,0.0820f}; //r_g_b_weights
	DWORD dwEncodeType;
	if( !alpha )
		dwEncodeType	= S3TC_ENCODE_RGB_FULL|S3TC_ENCODE_ALPHA_NONE;
	else
		dwEncodeType	= S3TC_ENCODE_RGB_ALPHA_COMPARE|S3TC_ENCODE_ALPHA_NONE; //Bei 1-Bit Alpha

	descIn.dwSize								= sizeof(descIn);
	descIn.dwFlags								= DDSD_WIDTH|DDSD_HEIGHT|DDSD_LPSURFACE|DDSD_PITCH|DDSD_PIXELFORMAT;
	descIn.dwWidth								= nWidth;
	descIn.dwHeight								= nHeight;
	descIn.lPitch								= nWidth*4;
	descIn.lpSurface							= src;
	descIn.ddpfPixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	descIn.ddpfPixelFormat.dwFlags				= DDPF_RGB|DDPF_ALPHAPIXELS;
	descIn.ddpfPixelFormat.dwRGBBitCount		= 32;
	descIn.ddpfPixelFormat.dwRGBAlphaBitMask	= 0xff000000;
	descIn.ddpfPixelFormat.dwRBitMask			= 0x00ff0000;
	descIn.ddpfPixelFormat.dwGBitMask			= 0x0000ff00;
	descIn.ddpfPixelFormat.dwBBitMask			= 0x000000ff;

	descOut.dwSize = sizeof(descOut);

	S3TCencode(&descIn,NULL,&descOut,dest,dwEncodeType,weight);
}

_inline void setDXT2(int size,RGBPIXEL *src,zBYTE *dest,int nWidth,int nHeight)
{
	zerr.Warning( "Texture-Convert: setDXT2 is not supported yet ! " );
}

_inline void setDXT3(int size,RGBPIXEL *src,zBYTE *dest,int nWidth,int nHeight)
{	
	//Specify a width and height that are a multiple of 4 pixels
	if(nWidth<4)
		return;
	if(nHeight<4)
		return;

	DDSURFACEDESC descIn;
	DDSURFACEDESC descOut;
	float weight[3]		= {0.3086f,0.6094f,0.0820f}; //r_g_b_weights
	DWORD dwEncodeType	= S3TC_ENCODE_RGB_FULL|S3TC_ENCODE_ALPHA_EXPLICIT;

	descIn.dwSize								= sizeof(descIn);
	descIn.dwFlags								= DDSD_WIDTH|DDSD_HEIGHT|DDSD_LPSURFACE|DDSD_PITCH|DDSD_PIXELFORMAT;
	descIn.dwWidth								= nWidth;
	descIn.dwHeight								= nHeight;
	descIn.lPitch								= nWidth*4;
	descIn.lpSurface							= src;
	descIn.ddpfPixelFormat.dwSize				= sizeof(DDPIXELFORMAT);
	descIn.ddpfPixelFormat.dwFlags				= DDPF_RGB|DDPF_ALPHAPIXELS;
	descIn.ddpfPixelFormat.dwRGBBitCount		= 32;
	descIn.ddpfPixelFormat.dwRGBAlphaBitMask	= 0xff000000;
	descIn.ddpfPixelFormat.dwRBitMask			= 0x00ff0000;
	descIn.ddpfPixelFormat.dwGBitMask			= 0x0000ff00;
	descIn.ddpfPixelFormat.dwBBitMask			= 0x000000ff;

	descOut.dwSize = sizeof(descOut);

	S3TCencode(&descIn,NULL,&descOut,dest,dwEncodeType,weight);
}

_inline void setDXT4(int size,RGBPIXEL *src,zBYTE *dest,int nWidth,int nHeight)
{
	zerr.Warning( "Texture-Convert: setDXT4 is not supported yet ! " );
}

_inline void setDXT5(int size,RGBPIXEL *src,zBYTE *dest,int nWidth,int nHeight)
{
	zerr.Warning( "Texture-Convert: setDXT5 is not supported yet ! " );
}

//
// ConvertTexture (2-er texturen werden auch verwendet...)
//  srcsize   - zeiger auf 2 ints: breite und hoehe der quelltexture (diese werte koennen sich auch aendern...)
//  src,dest  - zeiger auf die quelle und den zielspeicher
//  srcfmt,dstfmt - sourceformat, und das zielformat
//  mipmaps   - ist dieser wert > 1, dann werden auch mipmaplevel
//              fuer die textur erstellt (wenn man's sowieso in rgb hat...)
//
typedef struct {	
	zBYTE c[3];
} PALPIXEL;


/* ----------------------------------------------------------------------
	
	allocTextureBuffer() : einen texture-buffer reservieren...

	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static char *allocTextureBuffer(int x,int y,float bpp,int mipMapNr)
{	//
	int size = 0;
//	int d = x*y*zFloat2Int(bpp);
	int d = zFloat2Int(x*y*bpp);
	while(mipMapNr && d){	
		size+=d;	d>>=2; mipMapNr--;
	}
	return(zNEW_ARRAY(char,size));
}

//
// einen texture-buffer aus den zengine-daten setzen
//
static char *AllocTextureBuffer(zCTextureInfo *ti)
{	//
	zTRnd_TexFormatInfo tfi= zrenderer->GetTexFormatInfo(ti->texFormat);
	return(allocTextureBuffer(ti->sizeX,ti->sizeY,tfi.bytesPerPixel,ti->numMipMap));
}

/* ----------------------------------------------------------------------
	
	FreeTextureBuffer():    egal welchen texture-buffer freigeben.


	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static char *FreeTextureBuffer(char *src)
{	
	// free(src);
	delete[] src;
    return(0L);
}

/* ----------------------------------------------------------------------
	
	ConvertTexture2()

	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static char *ConvertTexture2	(int			*srcsize,
								 int			*dstsize, 
								 void			*src,
								 int			offset,
								 void			*pal,
								 unsigned long	srcfmt,
								 unsigned long	dstfmt,
								 int			mipmaps,
								 zCOLOR			*averageColor,
								 const zBOOL	detailTextureMode)
{	
	int dstx,dsty,oldoff,off;
	int t,r,size;
	void *newptr;
	char *ssrc = ((char*)src) + offset;
	RGBPIXEL *srcrgb,*srcrgb2,*dstrgb;

	dstx = dstsize[0];
	dsty = dstsize[1];

	// minimal-texturgroesse ueberpruefen
	if(dstx<2) dstx = 2;
	if(dsty<2) dsty = 2;

#if TWO_N_SIZE
	int b;
	// die zielgroesse auf  2^n - groessen bringen...
	b = dstx;	do	{	dstx = b;		b = b&(b-1);	} while(b);
	b = dsty;	do	{	dsty = b;		b = b&(b-1);	} while(b);
#endif
	//
	// testen, obj die groesse sich jetzt
	// geaendert hat, wenn ja, dann wird
	// die groesse umgerechnet, da dabei
	// auch vergroessert werden kann, wird
	// ein pointer zurueckgegeben, der einen
	// zeiger auf den neuen zwischenbuffer
	// enthalet.
	if(dstx!=srcsize[0] || dsty!=srcsize[1]) {	// also: speicher fuer die textur neu anlegen, 
		// textur in den neuen buffer umkopieren, und
		//
		newptr = allocTextureBuffer(dstx,dsty,float(pixelsizes[srcfmt]),mipmaps);
		if(newptr){	
			ResizeTexture(srcsize,dstx,dsty,ssrc,newptr,srcfmt);		// neu berechnen...
			FreeTextureBuffer((char*)src);	// alten buffer koennen wir wegschmeissen....
			src = (char*)newptr;	// wird einfach aus dem neuen rausgelesen...
			ssrc = (char*)newptr;	// wird einfach aus dem neuen rausgelesen...

		} 
		else {	
			zERR_FATAL("C: ConvertTexture: Error...converttexture");
			return(0L);
		}
		// groesse auf den neuen wert umstellen,
		// und an den aufrufer zurueckgeben...
		srcsize[0] = dstx;
		srcsize[1] = dsty;
	}

	// funktionsweise: 
	//   wenn die formate nicht gleich sind,
	//   werden die texturen zuerst in ein RGB32bit-zwischenbuffer
	//   kopiert, und dann in das zielformat konvertiert. 
	//   um richtig schnell zu sein,
	//   werden dabei tabellen verwendet
	//
	size = dstx*dsty;	// groesse der textur....
	//

	//rgbbuff = (RGBPIXEL*)malloc(size*4);
	rgbbuff = zNEW_ARRAY(RGBPIXEL,size);

	if(rgbbuff==0) 	{	
		//gxdb(1,"No memory for conversion buffer...");
		zERR_FATAL("C: No memory for conversion buffer...");
		return(0);		// fehler...
	}

	zBOOL alpha = FALSE;
	switch(srcfmt)	{	
		case formatRGB555:		getRGB555(size,(unsigned short*)ssrc,rgbbuff);					break;
		case formatRGB1555:		getRGB1555(size,(unsigned short*)ssrc,rgbbuff); alpha = TRUE;	break;
		case formatRGB565:		getRGB565(size,(unsigned short*)ssrc,rgbbuff);					break;
		case formatRGB4444:		getRGB4444(size,(unsigned short*)ssrc,rgbbuff);	alpha = TRUE;	break;
		case formatBGR888:		getBGR888(size,(zBYTE*)ssrc,rgbbuff);							break;
		case formatRGB888:		getRGB888(size,(zBYTE*)ssrc,rgbbuff);							break;
		case formatRGBA8888:	getRGBA8888(size,(zBYTE*)ssrc,rgbbuff);			alpha = TRUE;	break;
		case formatBGRA8888:	getBGRA8888(size,(zBYTE*)ssrc,rgbbuff);			alpha = TRUE;	break;
		case formatARGB8888:	getARGB8888(size,(zBYTE*)ssrc,rgbbuff);			alpha = TRUE;	break;
		case formatABGR8888:	getABGR8888(size,(zBYTE*)ssrc,rgbbuff);			alpha = TRUE;	break;
		case formatRGB8:		getRGB8(size,(zBYTE*)ssrc,rgbbuff);								break;
		case formatPAL8:		getPAL8(size,(zBYTE*)ssrc,rgbbuff,(zBYTE*)pal);					break;
		case formatDXT1:		getDXT1(size,(zBYTE*)ssrc,rgbbuff,dstx,dsty);					break;
		case formatDXT2:		getDXT2(size,(zBYTE*)ssrc,rgbbuff,dstx,dsty);	alpha = TRUE;	break;
		case formatDXT3:		getDXT3(size,(zBYTE*)ssrc,rgbbuff,dstx,dsty);	alpha = TRUE;	break;
		case formatDXT4:		getDXT4(size,(zBYTE*)ssrc,rgbbuff,dstx,dsty);	alpha = TRUE;	break;
		case formatDXT5:		getDXT5(size,(zBYTE*)ssrc,rgbbuff,dstx,dsty);	alpha = TRUE;	break;
		default: zERR_WARNING("C: ConvertTexture: !!!!!!UNSUPPORTED BITMAPFORMAT"); return(0);
	}

	// ok, jetzt wird der zielbuffer angelegt. 
	// dabei wird der alte quellbuffer vorher
	// entfernt, und der neue in der neuen groesse, im neuen
	// format angelegt.
	//
	src = FreeTextureBuffer((char*)src);			// wieder freigeben....

	char *dest = allocTextureBuffer(dstx,dsty,pixelsizes[dstfmt],mipmaps);

	if(dest==0L){	
		zERR_FATAL("C:ConvertTexture: can't alloc destination buffer");
		return FALSE;
	}


	if( (dstfmt==formatDXT1)||(dstfmt==formatDXT3) )
	{	// average color berechnen auf Basis des ARGB8888 Zwischenformats //NEU !!!
		zVEC4 avgColor(0,0,0,0);
		zREAL counter = 0;
		zBYTE* ptr = (zBYTE*)rgbbuff;

		while (counter<size) 
		{
//			avgColor += zVEC4(ptr[0], ptr[1], ptr[2], ptr[3]);	// ARGB
			avgColor += zVEC4(ptr[3], ptr[2], ptr[1], ptr[0]);	// BGRA
			ptr += 4;
			counter++;
		}

		avgColor /= zREAL(size);
		averageColor->SetAlphaByte( zFloat2Int(avgColor[VX]) ); // A
		averageColor->SetRedByte( zFloat2Int(avgColor[VY]) );	// R
		averageColor->SetGreenByte( zFloat2Int(avgColor[VZ]) );	// G
		averageColor->SetBlueByte( zFloat2Int(avgColor[VW]) );	// B
	}

	//
	// jetzt wird in das neue format in den buffer zurueckkopiert
	// das geschieht in einer scheife, weil dabei auch gleich die
	// mipmaps berechnet werden koennen
	//
	// wenn eine palette benoetigt, aber keine vorhanden
	// dann wird erst eine palette neu berechnet....

	if(dstfmt==formatPAL8)	{
		if(srcfmt!=formatPAL8)	{	
			#if dd
			zerr.Message("C: ConvertTexture: need palette");
			#endif
			tcCreatePalette(rgbbuff,(zBYTE*)pal,size);		// die palette wird erstellt...
		}
		else{	
			#if dd
			zerr.Message("C: ConvertTexture: reuse stored palette");
			#endif
		}
	}

	char *destbuff = dest;
	do{
		// alle mipmaps einzelnen konvertieren
		switch(dstfmt){
			case formatRGB555:		setRGB555(size,rgbbuff,(unsigned short*)dest);		dest = (char*)((unsigned long)dest + size*2);	break;
			case formatRGB1555:		setRGB1555(size,rgbbuff,(unsigned short*)dest);		dest = (char*)((unsigned long)dest + size*2);	break;
			case formatRGB565:		setRGB565(size,rgbbuff,(unsigned short*)dest);		dest = (char*)((unsigned long)dest + size*2); 	break;
			case formatRGB4444:		setRGB4444(size,rgbbuff,(unsigned short*)dest);		dest = (char*)((unsigned long)dest + size*2);	break;
			case formatRGB888:		setRGB888(size,rgbbuff,(zBYTE*)dest);				dest = (char*)((unsigned long)dest + size);		break;
			case formatRGBA8888:	setRGB8888(size,rgbbuff,(unsigned long*)dest);		dest = (char*)((unsigned long)dest + size*4); 	break;
			case formatRGB8:		setRGB8(size,rgbbuff,(zBYTE*)dest);					dest = (char*)((unsigned long)dest + size);		break;
			case formatPAL8:		setPAL8(size,rgbbuff,(zBYTE*)dest,(zBYTE*)pal);		dest = (char*)((unsigned long)dest + size/2);	break;
			case formatDXT1:		setDXT1(size,rgbbuff,(zBYTE*)dest,dstx,dsty,alpha);	dest = (char*)((unsigned long)dest + size/2);	break;
			case formatDXT2:		setDXT2(size,rgbbuff,(zBYTE*)dest,dstx,dsty);		dest = (char*)((unsigned long)dest + size);		break;
			case formatDXT3:		setDXT3(size,rgbbuff,(zBYTE*)dest,dstx,dsty);		dest = (char*)((unsigned long)dest + size);		break;
			case formatDXT4:		setDXT4(size,rgbbuff,(zBYTE*)dest,dstx,dsty);		dest = (char*)((unsigned long)dest + size);		break;
			case formatDXT5:		setDXT5(size,rgbbuff,(zBYTE*)dest,dstx,dsty);		dest = (char*)((unsigned long)dest + size);		break;
		}

		// jetzt werden hier die mipmaps
		// generiert, weil wir uns in der hoechsten
		// aufloesung befinden, und so im normalen modus
		// arbeiten koennen
		//
		dstx>>=1;
		dsty>>=1;
		mipmaps--;	// runterzaehlen...
		size>>=2;	// kleiner machen...
		if((mipmaps>0) && (size>4))	{	// wenn downsampeln angesagt ist...

			oldoff = dstx+dstx;
			srcrgb  = (RGBPIXEL*) rgbbuff;						// 1 zeile
			srcrgb2 = (RGBPIXEL*) (rgbbuff+oldoff);			// 2 zeile
			//oldoff<<=1;																// offset verdoppeln, damit 2 zeilen uebersprungen werden
			off = 0;
			dstrgb=rgbbuff;		// buffer...(ziel = quelle, da ziel kleiner als ide quelle ist...

			for(t=0;t<dsty;t++)	{	
				off = 0;
				for(r=0;r<dstx;r++)	{	
					dstrgb->r = ((srcrgb[off].r + srcrgb[off+1].r + srcrgb2[off].r + srcrgb2[off+1].r))>>2;
					dstrgb->g = ((srcrgb[off].g + srcrgb[off+1].g + srcrgb2[off].g + srcrgb2[off+1].g))>>2;
					dstrgb->b = ((srcrgb[off].b + srcrgb[off+1].b + srcrgb2[off].b + srcrgb2[off+1].b))>>2;
					dstrgb->a = ((srcrgb[off].a + srcrgb[off+1].a + srcrgb2[off].a + srcrgb2[off+1].a))>>2;
					if (detailTextureMode)
					{
						const zVEC3 F = (127.0F, 127.0F, 127.0F);		// fadeColor
						const zREAL B = 0.3F;		// fadeWeight
						dstrgb->r = zFloat2Int((1.0F-B)*zREAL(dstrgb->r) + B*F[0]);
						dstrgb->g = zFloat2Int((1.0F-B)*zREAL(dstrgb->g) + B*F[1]);
						dstrgb->b = zFloat2Int((1.0F-B)*zREAL(dstrgb->b) + B*F[2]);

					};
					dstrgb++;
					off+=2;
				}
				srcrgb+=oldoff*2;	
				srcrgb2+=oldoff*2;
			}
		} 

	} while((mipmaps>0) && (size>0));	// solange irgendwelche mipmaps berechnet werden sollen...(at least one)
	// und der hauptbuffer...

	delete[] rgbbuff;
    rgbbuff = NULL;

	return((char*)destbuff);
}


/*--------------------------------------------------------------------------
	
	zBOOL zCTexConGeneric :: ConvertTextureFormat( const zCTextureInfo& dsttexinfo )

 

    27-Oct-00       [PELZER] Einfügender berechneten Average-Color in die Texture-Info

--------------------------------------------------------------------------*/
zBOOL zCTexConGeneric::ConvertTextureFormat (const zCTextureInfo& dsttexinfo)
{	
	if ( (dsttexinfo.texFormat == texinfo.texFormat) &&
		 (dsttexinfo.numMipMap == texinfo.numMipMap) &&
		 (dsttexinfo.sizeX	   == texinfo.sizeX	   ) &&
		 (dsttexinfo.sizeY	   == texinfo.sizeY	   ) ) return TRUE;

	int					destformat;
	zTRnd_TextureFormat	dfm;
	int					srcptr;

	#if dd
	zerr.Message("C: ConverTextureForamt.");
	#endif

	if ( tempptr==NULL ){	
		zerr.Message("C: ConverTextureForamt: NO TEXTURE BUFFER, did you called SetTextureInfo first?.");
		return FALSE;
	}

	dfm = dsttexinfo.texFormat;

	switch(dfm){	
		case	zRND_TEX_FORMAT_PAL_8:		destformat = formatPAL8;		break;
		case	zRND_TEX_FORMAT_RGB_565:	destformat = formatRGB565;		break;
		case	zRND_TEX_FORMAT_BGR_888:	destformat = formatBGR888;		break;
		case	zRND_TEX_FORMAT_RGB_888:	destformat = formatRGB888;		break;
		case	zRND_TEX_FORMAT_BGRA_8888:	destformat = formatBGRA8888;	break;
		case	zRND_TEX_FORMAT_ABGR_8888:	destformat = formatABGR8888;	break;
		case	zRND_TEX_FORMAT_ARGB_8888:	destformat = formatARGB8888;	break;
		case	zRND_TEX_FORMAT_RGBA_8888:	destformat = formatRGBA8888;	break;
		case	zRND_TEX_FORMAT_ARGB_4444:	destformat = formatRGB4444;		break;
		case	zRND_TEX_FORMAT_ARGB_1555:	destformat = formatRGB1555;		break;
		case	zRND_TEX_FORMAT_DXT1:		destformat = formatDXT1;		break;
		case	zRND_TEX_FORMAT_DXT2:		destformat = formatDXT2;		break;
		case	zRND_TEX_FORMAT_DXT3:		destformat = formatDXT3;		break;
		case	zRND_TEX_FORMAT_DXT4:		destformat = formatDXT4;		break;
		case	zRND_TEX_FORMAT_DXT5:		destformat = formatDXT5;		break;
	}

	// wenn eine datei geladen wurde, dann wird sie
	// jetzt konvertiert....
	int srcsize[2],dstsize[2];
	srcsize[0] = texinfo.sizeX;
	srcsize[1] = texinfo.sizeY;
	dstsize[0] = dsttexinfo.sizeX;
	dstsize[1] = dsttexinfo.sizeY;
	srcptr = 0L;//tempptr;

	// hier eine kleiner "bonus": 
	//   bevor die textur wirklich umgeaendert wird, werden
	//   die vorhandenen mipmaps abgesucht. damit die bestmoegliche
	//   qualitaet fuer die skalierung verwendet werden kann.

	int wx=texinfo.sizeX, wy=texinfo.sizeY, wm=texinfo.numMipMap;
	zTRnd_TexFormatInfo tfi= zrenderer->GetTexFormatInfo(texinfo.texFormat);

	while((dstsize[0]<wx-(wx>>2)) && (dstsize[1]<wy-(wy>>2)) && wm>1){	
//		srcptr+=(wx*wy)*zFloat2Int(tfi.bytesPerPixel);
		srcptr+=zFloat2Int((wx*wy)*tfi.bytesPerPixel);
		wx>>=1;
		wy>>=1;
		wm-=1;
	}

	srcsize[0]=wx;
	srcsize[1]=wy;

	int mipmaps = 1;
	int ww = dstsize[0];
	int hh = dstsize[1];
	while(ww>1 && hh>1)	{	mipmaps++;	ww>>=1;	hh>>=1;	}

	if(dsttexinfo.numMipMap < 1)	
	{	// wenn keine angegeben, dann neurechnen
		mipmaps = 1;
	} 
	else 
	{	
		// zuerst pruefen, ob ueberhaupt ein gueltiger wert
		// gespeichert wurde...
		if (dsttexinfo.numMipMap<=mipmaps) {	
			mipmaps = dsttexinfo.numMipMap;
		} else {	
			zerr.Message("C: ConvertTextureFormat: WRONG mipmapcount want:"+zSTRING(dsttexinfo.numMipMap)+" can:"+zSTRING(mipmaps));
			return(FALSE);
			//dsttexinfo.numMipMap = mipmaps;
		}
	}

	zCOLOR avgCol; //[PELZER] NEU - Um die berechnete Average-Color in die Texture-Info einfügen zu können
	alpha = FALSE;
	switch(texinfo.texFormat){	
		case	zRND_TEX_FORMAT_PAL_8:			tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatPAL8,destformat,mipmaps,&avgCol, this->detailTextureMode); 						break;
		case	zRND_TEX_FORMAT_RGB_565:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatRGB565,destformat,mipmaps,&avgCol, this->detailTextureMode); 					break;
		case	zRND_TEX_FORMAT_BGR_888:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatBGR888,destformat,mipmaps,&avgCol, this->detailTextureMode); 					break;
		case	zRND_TEX_FORMAT_RGB_888:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatRGB888,destformat,mipmaps,&avgCol, this->detailTextureMode); 					break;
		case	zRND_TEX_FORMAT_BGRA_8888:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatBGRA8888,destformat,mipmaps,&avgCol, this->detailTextureMode); 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_ABGR_8888:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatABGR8888,destformat,mipmaps,&avgCol, this->detailTextureMode); 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_ARGB_8888:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatARGB8888,destformat,mipmaps,&avgCol, this->detailTextureMode); 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_RGBA_8888:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatRGBA8888,destformat,mipmaps,&avgCol, this->detailTextureMode); 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_ARGB_4444:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatRGB4444,destformat,mipmaps,&avgCol, this->detailTextureMode); 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_ARGB_1555:		tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatRGB1555,destformat,mipmaps,&avgCol, this->detailTextureMode); 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_DXT1:			tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatDXT1,destformat,mipmaps,&avgCol, this->detailTextureMode);						break;
		case	zRND_TEX_FORMAT_DXT2:			tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatDXT2,destformat,mipmaps,&avgCol, this->detailTextureMode);	 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_DXT3:			tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatDXT3,destformat,mipmaps,&avgCol, this->detailTextureMode);	 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_DXT4:			tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatDXT4,destformat,mipmaps,&avgCol, this->detailTextureMode);	 	alpha = TRUE;	break;
		case	zRND_TEX_FORMAT_DXT5:			tempptr = ConvertTexture2(srcsize,dstsize,tempptr,srcptr,pal,formatDXT5,destformat,mipmaps,&avgCol, this->detailTextureMode);	 	alpha = TRUE;	break;
	}
	texinfo					= dsttexinfo;
	texinfo.averageColor	= avgCol; //[PELZER] NEU - Einfügen der berechneten Average-Color in die Texture-Info
	texinfo.texFormat		= dfm;
	texinfo.sizeX			= dstsize[0];
	texinfo.sizeY			= dstsize[1];
	texinfo.numMipMap		= mipmaps;

	#if usergbtab
	FreeTexConvert();
	#endif

	return TRUE;
};

// writing contents
zBOOL	zCTexConGeneric::SetTextureInfo		(const zCTextureInfo& texInfo)	
{	
	//gxdb(1,"SetTextureInfo");	
	texinfo = texInfo;
	if((texinfo.sizeX * texinfo.sizeY)>0)	{
		// nur wenn schon was eingetragen ist...
		if(!tempptr){
			// wenn kein zeiger initialisiert ist
			tempptr = AllocTextureBuffer(&texinfo);		// zeigerreservieren
			#if dd
			zerr.Message("C: ConvertTexture: SetTextureInfo ALLOC BUFFER");
			#endif
			if(!tempptr) return(FALSE);
		}
		#if dd
		zerr.Message("C: ConvertTexture: SetTextureInfo");
		#endif
	}
	return TRUE;	
}

zCTextureInfo	zCTexConGeneric::GetTextureInfo()	
{	
	/*gxdb(1,"GetTextureInfo");*/		
	#if dd
	zerr.Message("C: ConvertTexture: GetTextureInfo");
	#endif
	return texinfo;	
}

void*	zCTexConGeneric::GetPaletteBuffer()							
{	
	if (lockMode & zTEX_LOCK_WRITE) modified = TRUE;
	if (texinfo.texFormat == zRND_TEX_FORMAT_PAL_8)	return(pal);
	else return 0;
}


zBOOL	zCTexConGeneric::GetTextureBuffer(int mipMapNr, void* &buffer, int &pitchXBytes)	// read/write
{
	buffer=0;
	pitchXBytes=0;
	int s=0;

	if (lockMode & zTEX_LOCK_WRITE) modified = TRUE;
	
	if((texinfo.sizeX * texinfo.sizeY)>0) {
		// nur wenn schon was eingetragen ist...
		//Bei DXT1 oder DXT3 muss die Breite und Höhe durch 4 teilbar sein
		if( (texinfo.texFormat==zRND_TEX_FORMAT_DXT1)||(texinfo.texFormat==zRND_TEX_FORMAT_DXT3) )
			if( ((texinfo.sizeX>>mipMapNr)<4)||((texinfo.sizeY>>mipMapNr)<4) )
			{
				zerr.Warning( "X: zCTexConGeneric::GetTextureBuffer: DXT1 or DXT3 with width or height not a multiple of 4 pixels !" );
				return FALSE;
			}
		zTRnd_TexFormatInfo tfi= zrenderer->GetTexFormatInfo(texinfo.texFormat);
//		int d = texinfo.sizeX * texinfo.sizeY* zFloat2Int(tfi.bytesPerPixel); //@TODO: nochmal nachsehen
		int d = zFloat2Int(texinfo.sizeX * texinfo.sizeY*tfi.bytesPerPixel);

		if(tempptr && (mipMapNr<=texinfo.numMipMap)){
			// wenn zu hoher wert ?
			//gxdb(1,"GetTextureBuffer buffer allowed...");	
			// anfangsadresse des mipmaps 
			int num = mipMapNr;
			while (num && d) {	
				s+=d;	d>>=2; num--;
			}
			s = s + (int)tempptr;
			buffer		= (void*)s;
//			pitchXBytes = (texinfo.sizeX >> mipMapNr) * zFloat2Int(tfi.bytesPerPixel); //@TODO: nochmal nachsehen
			pitchXBytes = zFloat2Int((texinfo.sizeX >> mipMapNr) * tfi.bytesPerPixel);
			return TRUE;
		}
	}
	//gxdb(1,"GetTextureBuffer: buffer not initialized");	
	return FALSE;

}

zBOOL	zCTexConGeneric::CopyTextureDataTo	(int mipMapNr, void* destBuffer, int destPitchXBytes)
{	
	#if dd
	zerr.Message("C: ConvertTexture: CopyTextureDataTo");
	#endif

	//Bei DXT1 oder DXT3 muss die Breite und Höhe durch 4 teilbar sein
	if( (texinfo.texFormat==zRND_TEX_FORMAT_DXT1)||(texinfo.texFormat==zRND_TEX_FORMAT_DXT3) )
		if( ((texinfo.sizeX>>mipMapNr)<4)||((texinfo.sizeY>>mipMapNr)<4) )
		{
			zerr.Warning( "X: zCTexConGeneric::CopyTextureDataTo: DXT1 or DXT3 with width or height not a multiple of 4 pixels !" );
			return FALSE;
		}

	zBYTE *data = (zBYTE*) tempptr;

	if (data == NULL || destBuffer == NULL) {
		zERR_WARNING("C:CopyTextureDataTo//mipmap failed");
		return FALSE;
	}
		
	// wenn zeiger vorhanden ist...

	zTRnd_TexFormatInfo tfi	=	zrenderer->GetTexFormatInfo(texinfo.texFormat);
	int srcOffset			=	0;
//	int d					=	texinfo.sizeX * texinfo.sizeY * zFloat2Int(tfi.bytesPerPixel); //@TODO: nochmal nachsehen
	int d					=	zFloat2Int(texinfo.sizeX * texinfo.sizeY * tfi.bytesPerPixel);
	int mip					=   mipMapNr;

	while(mip && d) {	
		srcOffset+=d; 
		d		>>=2; 
		mip--; 
	}

	// hmm, hier weiss man leider nicht, ob die textur, aus die der destBuffer stammt auch gelockt ist...
	zBYTE *src = &data[srcOffset];
//	int thisPitch = (texinfo.sizeX >> mipMapNr) * zFloat2Int(tfi.bytesPerPixel); //@TODO: nochmal nachsehen
	int thisPitch = zFloat2Int((texinfo.sizeX >> mipMapNr) * tfi.bytesPerPixel);

	if (destPitchXBytes == thisPitch) {
		memcpy(destBuffer,(void*)src,d); 
	}
	else {
		// Copy a texture from src to dst, dst has a pitch != dstWidth
		zBYTE *dst = (zBYTE *)destBuffer;

		int height = texinfo.sizeY;

		while (height--) {
			memcpy((void*)dst,(void*)src,thisPitch);
			dst += destPitchXBytes;
			src += thisPitch;
		}
	}

	return TRUE;

}

zBOOL	zCTexConGeneric::CopyPaletteDataTo	(void* destBuffer)// the source data can be filled in directly from hard disk (if no convers. necessary)
{	
	int t;
	zBYTE *b = (zBYTE *) destBuffer;
	if( b==0 ) return FALSE;
	for(t=0;t<256*3;t++) b[t]=pal[t];
	#if dd
	zerr.Message("C: ConvertTexture: CopyPaletteDataTo");
	#endif
	return(TRUE);
}

// query properties
zCOLOR	zCTexConGeneric::GetAverageColor()
{	
	return(texinfo.averageColor);
}

zBOOL	zCTexConGeneric::HasAlpha()
{
	switch(texinfo.texFormat)
	{
		case	zRND_TEX_FORMAT_ARGB_8888:
		case	zRND_TEX_FORMAT_RGBA_8888:
		case	zRND_TEX_FORMAT_BGRA_8888:
		case	zRND_TEX_FORMAT_ABGR_8888:
		case	zRND_TEX_FORMAT_ARGB_4444:
		case	zRND_TEX_FORMAT_ARGB_1555:
		case	zRND_TEX_FORMAT_DXT3:
				alpha = TRUE;
				break;
		default:
//				if( zRND_TEX_FORMAT_DXT1 )
//					; //@TODO: Sonderbehandlung !
//				else
					alpha = FALSE;
	}

	return(alpha);
}

// zeiger erstmal deinitialisieren
// so dass ein sauberes abfangen unitialisierter objekte
// moeglich ist...
//
zCTexConGeneric::zCTexConGeneric()
{
	tempptr				= 0L;
	memset				(&texinfo,0,sizeof(texinfo));
	alpha				= FALSE;
	average.SetRGBA		(255,255,255,255);
	lockMode			= (zTTexLockMode)0;
	modified			= FALSE;
	detailTextureMode	= FALSE;

	#if dd
		zerr.Message("C: ConvertTexture: CREATE");
	#endif
}

// hinterher aufraeumen, und zeiger loeschen, damit
// kein scheiss mehr passiert...
zCTexConGeneric::~zCTexConGeneric()
{	
	if(tempptr) tempptr = FreeTextureBuffer(tempptr);
	memset(&texinfo,0,sizeof(texinfo));
	#if dd
	zerr.Message("C: ConvertTexture: DESTROY");
	#endif
}

// read/write, use 'zTTexLockMode' 
zBOOL zCTexConGeneric::Lock	(int lockMode) 
{ 
	this->lockMode = (zTTexLockMode)lockMode;
	return TRUE; 
};	

// read/write
zBOOL zCTexConGeneric::Unlock	() 
{ 

// FIXME: Das ist unschön, so werden im Spacer keine Durchschnittsfarben berechnet
// (aber erstmal die Texturen im Spacer gehackt auch hinreichend schnell dargestellt)
#ifndef FINAL_RELEASE
#ifndef CHASE_DEBUG
#ifndef COMPILING_SPACER
	if (lockMode & zTEX_LOCK_WRITE && modified && (texinfo.texFormat!=formatDXT1) && (texinfo.texFormat!=formatDXT3) ) {
		// average color ermitteln.
		// FIXME: das könnte noch schneller gehen, da die Durchschnittsfarbe aus
		// der grössten MipMap zu berechnen unnötig ist.
		zVEC4 avgColor(0,0,0,0);
		zREAL x = 0, y = 0;

		while (y<texinfo.sizeY) 
		{
			while (x<texinfo.sizeX) 
			{
				avgColor += GetRGBAAtTexel(x,y);
				x ++;
			}
			y ++; x = 0;
		}

		avgColor /= zREAL(texinfo.sizeX*texinfo.sizeY);

		texinfo.averageColor = zCOLOR( zFloat2Int(avgColor[VX]),
									   zFloat2Int(avgColor[VY]),
									   zFloat2Int(avgColor[VZ]),
									   zFloat2Int(avgColor[VW]) );
	}
#endif
#endif
#endif

	modified = FALSE;

	return TRUE; 
};				
