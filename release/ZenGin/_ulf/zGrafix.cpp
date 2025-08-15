/******************************************************************************** 
 
     $Workfile:: Zgrafix.cpp          $                $Date:: 19.09.00 20:57   $
     $Revision:: 11                   $             $Modtime:: 19.09.00 19:52   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/Zgrafix.cpp $
 * 
 * 11    19.09.00 20:57 Wohlers
 * 
 * 10    11.09.00 20:52 Speckels
 * 
 * 9     24.08.00 17:06 Moos
 * 
 * 8     23.08.00 17:34 Moos
 * Auf zNEW umgestellt; Wird diese Datei eigentlich noch verwendet?
 * 
 * 7     31.07.00 23:39 Rueve
 * teufelswerk kommentiert
 * 
 * 6     21.07.00 15:35 Wohlers
 * 
 * 5     21.07.00 14:43 Wohlers
 * 
 * 4     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 6     29.03.00 15:32 Wohlers
 * Various Bugfixes ( Waynet, Klettern )
 * 
 * 5     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 3     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

/*****************************************************************
- Kommentare:
	- Die Koordinaten und Grö0en sind Pixel-Einheiten !  
	! Speicherallokation nach Grade - mempoolalloc !?
****************************************************************/

#include "zCore.h"

#include "zGrafix.h"
#include "zDisk.h"
#include "zOption.h"
#include "zRenderer.h"
#include "zVideo_Win32.h"

#include <direct.h>

//#pragma optimize( "", off )

zCGfx*	zCGfx :: Gfx_List = NULL;
int		zCGfx :: gfxcount = 0;

/* ----------------------------------------------------------------------
	
	zCGfx::zCGfx(zSTRING &)

	23.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

// Constructor 1 - Load File
zCGfx :: zCGfx(const zSTRING& f)
{
	data	= NULL;
	next	= NULL;
	
	// Check if file is in list
	zCGfx *ele = Gfx_List;

	zSTRING file = f;
	file.Upper();
	while (ele!=NULL) {
		if (*ele->data->id == file) {
			// It is already in list
			data = ele->data;			
			data -> count ++;
			// Put in list
			next	 = Gfx_List;
			Gfx_List = this;
			return;
		}
		ele = ele->next;
	}
	// Not in list
	data = LoadGfx(file);
	if (data == NULL) {
//		TRACE("zGRAFIX : Loading %s failed",file.ToChar());
		return;
	};
	data -> count = 1;
	data -> id    = zNEW(zSTRING(file));
	data -> bpp	  = VideoRSize + VideoGSize + VideoBSize;
	if (zrenderer->vid_bpp == 32) data->bpp += 8;
	// Put in list
	next	 = Gfx_List;
	Gfx_List = this;
}

/* ----------------------------------------------------------------------
	
	zCGfx::zCGfx(int,int)

	23.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

// Constructor 2 - Init Empty Gfx
zCGfx :: zCGfx(int x,int y)
{
	data	= NULL;
	next	= NULL;

	int size;
	// Will not be in list
	gfxcount++;
	data		= zNEW(TGfx_Gfx);
//	if (data == NULL) TRACE("zGRAFIX : Init Empty Gfx %d %d failed",x,y);
	data -> id	  = zNEW(zSTRING(gfxcount));
	*data -> id	 += zSTRING("..");
	data -> bpp	  = VideoRSize + VideoGSize + VideoBSize;
	if (zrenderer->vid_bpp == 32) data->bpp += 8;
	data -> sx	  = x;
	data -> sy	  = y;
	data -> count = 1;
	size		  = x * y * (zrenderer->vid_bpp>>3);
	data -> scr   = zNEW_ARRAY(BYTE,size);
	memset (data->scr,0,size);
}

// Destructor
zCGfx :: ~zCGfx()
{
	zCGfx *ele;
	if (data) {
		// First check reference counter
		data->count--;
		if (data->count <= 0) {
			// remove file
			delete(data->id);
			delete[] data->scr;
			delete(data);
		}
	};

	// Remove from list
	ele = Gfx_List;
	if (ele != NULL) {
		if (ele == this) Gfx_List = next;
		else while (ele->next!=NULL) {
			if (ele->next == this) {
				ele->next = next;
				return;
			}
			ele = ele->next;
		}
	}

	data = NULL;
	next = NULL;
}

// Reload Files in List
void zCGfx :: Reload()
{

	TGfx_Gfx *newgfx;
	zCGfx *ele;
	zSTRING s;
	int a_bpp = VideoRSize + VideoGSize + VideoBSize;
	if (zrenderer->vid_bpp == 32) a_bpp += 8;

	ele = Gfx_List;
	while(ele!=NULL) {
		if (ele->data->bpp != a_bpp) {
			s	= *ele->data->id;
			// Free old Gfx - Data
			delete[] ele->data->scr;
			// Create new Gfx
			newgfx = ele->LoadGfx(s);
//			if (newgfx==NULL) TRACE("zGRAFIX : Failed to reload %s.",s.ToChar());
			// Copy Interior 
			ele->data->bpp   = a_bpp;
			ele->data->sx    = newgfx->sx;
			ele->data->sy	 = newgfx->sy;
			ele->data->scr   = newgfx->scr;
			delete(newgfx);
		}
		ele = ele->next;
	}
}

////////////////////////////////////////////////
//			Color - Definitions
////////////////////////////////////////////////

#define COLREF(r,g,b) r<<16+g<<8+b

// Color correcting in 8bpp (Pal Entries : 0..9 + 246..255)
//#define _COL8CORRECT_

// Lustige Farbens
zCOLOR	GFX_WHITE		(255,255,255,255),
		// Yellows
		GFX_YELLOW		(255,255,0,255),
		GFX_LYELLOW		(255,255,224,255),
		GFX_GOLD		(255,215,0,255),
		// Orange
		GFX_ORANGE		(255,128,0,255),
		GFX_DORANGE		(255,140,0,255),
		GFX_CARROT		(237,145,33,255),
		// Reds
		GFX_RED			(255,0,0,255),
		GFX_DRED		(255,99,71,255),
		GFX_PINK		(255,192,203,255),
		GFX_LPINK		(255,182,193,255),
		GFX_DPINK		(255,20,147,255),
		// Magentas
		GFX_MAGENTA		(255,0,255,255),
		GFX_ORCHID		(218,112,214,255),
		GFX_PURPLE		(160,32,240,255),
		GFX_VIOLET		(143,94,153,255),
		// Cyans
		GFX_CYAN		(0,255,255,255),
		GFX_AQUA		(127,255,212,255),
		// Greens
		GFX_GREEN		(0,255,0,255),
		GFX_DGREEN		(0,100,0,255),
		GFX_PALEGREEN	(152,251,152,255),
		GFX_OLIVE		(59,94,43,255),
		// Blues
		GFX_BLUE		(0,0,255,255),
		GFX_LBLUE		(173,216,230,255),
		GFX_MBLUE		(0,0,205,255),
		GFX_INDIGO		(8,46,84,255),
		GFX_DBLUE		(0,0,128,255),
		GFX_SKY			(135,206,235,255),
		GFX_STEEL		(70,130,180,255),
		// Browns
		GFX_BROWN		(128,42,42,255),
		GFX_OCHRE		(135,66,31,255),
		GFX_DOCHRE		(115,61,26,255),
		GFX_BEIGE		(163,148,128,255),
		GFX_FLESH		(255,125,64,255),
		GFX_KHAKI		(240,230,140,255),
		// Greys
		GFX_GREY		(192,192,192,255),
		GFX_LGREY		(211,211,211,255),
		GFX_COLDGREY	(128,138,135,255),
		GFX_WARMGREY	(128,128,105,255),
		// Blacks
		GFX_BLACK		(0,0,0,255),
		GFX_IVORY		(41,36,33,255);

TGfx_Gfx *Gfx_List = NULL;

// Palette

BYTE *Gfx_pal = NULL;

WORD Gfx_Pal8to16[256]; 
int  Pal8to24[256];

// Reloading Flag
BOOL Gfx_reloading = FALSE;

int rnd(float x)
{
	if (x>0) return (int) (x+0.5);
        else return (int) (x-0.5);
}


////////////////////////////////////////////////
// Load Gfx Functions
////////////////////////////////////////////////

/* ----------------------------------------------------------------------
	
	zCGfx::LoadRaw()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void Gfx_ChangeBPP (TGfx_Gfx *gfx)
{
	if (gfx->bpp==zrenderer->vid_bpp) return;
}
	
TGfx_Gfx *zCGfx :: LoadRaw(const zSTRING &s,int w, int h,int bpp)
{ 
	FILE *f;
	TGfx_Gfx *Gfx=NULL;

	zFILE::DirectFileAccess(true);
	if ((f=fopen(s.ToChar(),"rb"))!=NULL) {
		// Alloc Size for Grx Descritpors
		Gfx = zNEW(TGfx_Gfx);//(TGfx_Gfx *) malloc(sizeof(TGfx_Gfx));
	  	memset(Gfx,0,sizeof(Gfx));
		// Alloc Size for Grx Data
		Gfx->scr = zNEW_ARRAY(BYTE,w*h);
		fread(Gfx->scr,w*h*(bpp>>3),1,f);
		fclose(f);
		Gfx->sx = w; Gfx->sy = h; Gfx->bpp = zrenderer->vid_bpp;
		#ifdef _COL8CORRECT_
			if (bpp==8) {	
				ptr = Gfx->scr;
				for (i=0; i<w*h; i++) {				
					if ((*ptr<10) || (*ptr>245)) {
						i=zrenderer->vid_bpp; zrenderer->vid_bpp = zrenderer->vid_bpp;
						palptr = Gfx_pal + *ptr*4;
						r = *palptr++;
						g = *palptr++;
						b = *palptr++;
						*ptr=Gfx_Col(r,g,b);
						zrenderer->vid_bpp=i;
					}
					ptr++;
				}
			}
		#endif
	}	
	zFILE::DirectFileAccess(false);
	return(Gfx);
}

const int CACHESIZE = 5000;
BYTE *Cache,*CacheC;
int   count = -1;

BYTE zCGfx :: Readbyte(zFILE *fp)
{
	int len;
	if ((count<0) || (count>=CACHESIZE)) {
	len = fp->Size() - fp->Pos();
		if (len>CACHESIZE) len=CACHESIZE;
		fp->Read(Cache,CACHESIZE);
		count = 0; CacheC = Cache;
	} 
	count++; 
	return(*CacheC++);
}


/* ----------------------------------------------------------------------
	
	TGfx_Gfx :: LoadPcx()

	23.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */


TGfx_Gfx *zCGfx :: LoadPcx(const zSTRING &s)
{	
	zFILE *fp = zfactory->CreateZFile(s);
	int   step,RLE_byte;
    long size,W,H,i;
    unsigned short r,g,b,h;
    unsigned char VGA_pal[768];
    BYTE PCX_byte;
    unsigned char *buf_ptr;
    unsigned char *end_of_buf;
	unsigned char *pall,*palptr;
	TGfx_Gfx *Gfx = NULL;
	char buf[1024];

	_getcwd((char *)&buf,sizeof(buf));
	if (fp->Exists() == FALSE) {

        zERR_FAULT ("U: GFX: File "+s+" not found.");
		
		delete (fp);
		return zNEW(TGfx_Gfx);

    } else {
		
		// Using Cache
		Cache = zNEW_ARRAY(BYTE,CACHESIZE);
		//free(Cache);
		count = -1;
		
		step  = zrenderer->vid_bpp >> 3;
		
		fp->Open();
		fp->Seek(8);
		fp->Read(&b,sizeof(unsigned short));
		fp->Read(&h,sizeof(unsigned short));
		
        W=(long) b+1;
        H=(long) h+1;

        size = (long) (W * H * step);

        // Alloc Gfx
		Gfx        = zNEW(TGfx_Gfx);
		Gfx->sx    = W; Gfx->sy = H; Gfx->bpp = zrenderer->vid_bpp;
		Gfx->scr   = buf_ptr = zNEW_ARRAY(BYTE,size);
        end_of_buf = buf_ptr + size;
		
        // Load 256 color PCX palette
        fp->Seek(fp->Size()-768);
        fp->Read(VGA_pal,768);
		pall = palptr = zNEW_ARRAY(BYTE,1024);
		memset(pall,0,1024);
		for (i=0; i<256; i++) {
			*(palptr)   = VGA_pal[i*3];		// reading unitialised Memory
			*(palptr+1) = VGA_pal[i*3+1]; 
			*(palptr+2) = VGA_pal[i*3+2];	// reading unitialised Memory
			palptr+=4;
		}
		Gfx_Setpal(pall);

        fp->Seek(128);

        while (buf_ptr < end_of_buf) {

            // Read next packet
			PCX_byte = Readbyte(fp);

            if (PCX_byte < 192) {
                // Raw Pixel
				if (zrenderer->vid_bpp>8) {
					// Get matching Color
					if (PCX_byte!=0) {
						palptr = pall + PCX_byte * 4;
						r = *palptr++;	// reading un
						g = *palptr++;
						b = *palptr++;	// reading un
						RLE_byte = Gfx_Col(r,g,b);
					} else
						RLE_byte = 0;
					memcpy(buf_ptr,&RLE_byte,step);
					buf_ptr+=step;
				} else
					*buf_ptr++ = PCX_byte;
            } else {
                // RLE Pixels
                PCX_byte = PCX_byte & 0x3F;
				RLE_byte = Readbyte(fp);
				// Get matching Color
				if (zrenderer->vid_bpp>8) {
					if (RLE_byte!=0) {
						palptr = pall + RLE_byte * 4;
						r = *palptr++;	// reading un
						g = *palptr++;
						b = *palptr++;	// reading un
						RLE_byte = Gfx_Col(r,g,b);
					} else
						RLE_byte = 0;
				};	
				for (i=0; i<PCX_byte; i++) {
					memcpy(buf_ptr,&RLE_byte,step);
					buf_ptr+=step;
				}
                //memset(buf_ptr, RLE_byte, PCX_byte);
                //buf_ptr += PCX_byte;
            }
        }

		delete[] Cache;
	    fp->Close();
		delete(fp);
    }
	return (Gfx);
}

/* ----------------------------------------------------------------------
	
	zCGfx::LoadTga()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

TGfx_Gfx *zCGfx :: LoadTga(const zSTRING &s)
// Load a Targa-Bitmap
{
	#pragma pack (push,1)
	typedef struct TTGA_Head {
		BYTE idlen;
		BYTE colortable;
		BYTE type;
		WORD colIndex1;
		WORD colCount;		// In Doku this should be a word ?! 
		BYTE colBits;
		WORD xpos,ypos;
		WORD sx,sy;
		BYTE bpp;
		BYTE descr;
	} TTGA_Head;
	#pragma pack (pop)

	BOOL format = FALSE;
	TTGA_Head TGA_Head;
	zFILE *fp = zfactory->CreateZFile(s);
	TGfx_Gfx *Gfx = NULL;
	BYTE a,r,g,b;
	BYTE *ptr,*data,*cmap;
	WORD rgb;
	int col,size,step;
	int x,y,rep,i;

	if (fp->Exists() == FALSE) {
        zERR_FAULT ("U: (zGrafix) File "+s+" not found.");
		delete (fp);
		return (Gfx);
	}

	//if (fp->Exists()==FALSE) return(Gfx);
	// Using Cache
	Cache = zNEW_ARRAY(BYTE,CACHESIZE);
	count = -1;
	// Read TGA_Head;
	fp->Open();
	fp->Read(&TGA_Head,sizeof(TGA_Head));
	if (TGA_Head.idlen>0) fp->Seek(fp->Pos()+TGA_Head.idlen);
	// Check Data
	/*zSTRING s1("TGA-Dimensions :");
	s1 += TGA_Head.sx;
	s1 += ":";
	s1 += TGA_Head.sy;
	s1 += ":";
	s1 += TGA_Head.bpp;
	TRACE(s1.ToChar());*/
	// Init Gfx
	Gfx      = zNEW(TGfx_Gfx);
	Gfx->sx  = TGA_Head.sx; Gfx->sy = TGA_Head.sy; 
	Gfx->bpp = zrenderer->vid_bpp;
	size	 = TGA_Head.sx * TGA_Head.sy * (zrenderer->vid_bpp>>3);
	Gfx->scr = ptr = zNEW_ARRAY(BYTE,size);
	step	 = zrenderer->vid_bpp>>3;
	ptr		+= (size-step);

	// TYPE 1 : UNCOMPRESSED COLORMAPPED PICTURES
	if (TGA_Head.type == 1) {
		// Read ColorTable
		rep  = TGA_Head.colBits / 8;
		size = rep * TGA_Head.colCount;
		cmap = zNEW_ARRAY(BYTE, size);
		fp->Read(cmap,size);
		// OK, dann ma los
		if ((TGA_Head.bpp == 8) && (TGA_Head.colBits == 24)) {
			format = TRUE;
			for (y=TGA_Head.sy-1; y>=0; y--) {
				ptr = (BYTE *)Gfx->scr + TGA_Head.sx * y * step;
				for (x=0; x<TGA_Head.sx; x++) {
					rgb  = Readbyte(fp);
					data = cmap + rgb * rep;
					b	 = *data++;
					g	 = *data++;
					r	 = *data;
					col  = Gfx_Col(r,g,b);
					memcpy(ptr,&col,step);
					ptr += step;
				}
	
			}
		} 
		delete[] cmap;
	}
	
	// UNMAPPED TYPES 2 + 10

	// Check for Colormap
	if ((TGA_Head.colortable) && (TGA_Head.type!=1)) {
		for (i=0; i<TGA_Head.colCount * (TGA_Head.colBits / 8); i++) Readbyte(fp);
	}

	// Switch for Correct Color Conversion
	if (TGA_Head.type == 2) {
		// Unkomprimiert
		if (TGA_Head.bpp == 16) {
			format = TRUE;
			for (y=TGA_Head.sy-1; y>=0; y--) {
				ptr = (BYTE *)Gfx->scr + TGA_Head.sx * y * step;
				for (x=0; x<TGA_Head.sx; x++) {
					rgb  = Readbyte(fp);
					rgb += Readbyte(fp) << 8;
					// Wide to 8 bpp
					r	= ((rgb >> 10) & 31) * 256 / 32;		// Mask Out A
					g	= ((rgb >>  5) & 31) * 256 / 32;
					b	= ((rgb		 ) & 31) * 256 / 32;
					// TMP
					if (rgb==1023) {
						r=r;
						//g=0;
						//b=255;
					}
					col = Gfx_Col(r,g,b);
					memcpy(ptr,&col,step);
					// Intensity Byte 
					//r = Readbyte(&fp);
					ptr += step;
				}
			}
		} else 

		if (TGA_Head.bpp == 24) {
			format = TRUE;
			for (y=TGA_Head.sy-1; y>=0; y--) {
				ptr = (BYTE *)Gfx->scr + TGA_Head.sx * y * step;
				for (x=0; x<TGA_Head.sx; x++) {
					b = Readbyte(fp);
					g = Readbyte(fp);
					r = Readbyte(fp);
					col = Gfx_Col(r,g,b);
					memcpy(ptr,&col,step);
					ptr += step;
				}
	
			}
		} else

		if (TGA_Head.bpp == 32) {
			format = TRUE;
			for (y=TGA_Head.sy-1; y>=0; y--) {
				ptr = (BYTE *)Gfx->scr + TGA_Head.sx * y * step;
				for (x=0; x<TGA_Head.sx; x++) {
					b = Readbyte(fp);
					g = Readbyte(fp);
					r = Readbyte(fp);
					a = Readbyte(fp);
					col = Gfx_Col(r,g,b);
					memcpy(ptr,&col,step);
					ptr += step;
				}
	
			}
		}

	} else if (TGA_Head.type == 10) {
		// RLE encoded
		x   = TGA_Head.sx * TGA_Head.sy;
		ptr = data = zNEW_ARRAY(BYTE, size );
		
		if (TGA_Head.bpp == 16) {	
			format = TRUE;
			while (x>0) {
				
				y = Readbyte (fp);
			
				if (y > 127) {
					// RLE Packet
					rep = (y & 127) + 1;

					rgb  = Readbyte(fp);
					rgb += Readbyte(fp) << 8;
					// Wide to 8 bpp
					r	= ((rgb >> 10) & 31) * 256 / 32;		// Mask Out A
					g	= ((rgb >>  5) & 31) * 256 / 32;
					b	= ((rgb		 ) & 31) * 256 / 32;

					col = Gfx_Col(r,g,b);
					for (i=0; i<rep; i++) {
						memcpy(ptr,&col,step);
						ptr += step;
					}
					x -= rep;
				} else {
					// Raw Packet
					for (i=0; i<y+1; i++) {	
						rgb  = Readbyte(fp);
						rgb += Readbyte(fp) << 8;
						// Wide to 8 bpp
						r	= ((rgb >> 10) & 31) * 256 / 32;		// Mask Out A
						g	= ((rgb >>  5) & 31) * 256 / 32;
						b	= ((rgb		 ) & 31) * 256 / 32;
						col = Gfx_Col(r,g,b);
						memcpy (ptr,&col,step);
						ptr += step;
					}
					x -= y+1;
				}
			}
		} else

		if ((TGA_Head.bpp == 24) || (TGA_Head.bpp == 32)) {	
			format = TRUE;
			while (x>0) {
				
				y = Readbyte (fp);
			
				if (y > 127) {
					// RLE Packet
					rep = (y & 127) + 1;
					b = Readbyte(fp);
					g = Readbyte(fp);
					r = Readbyte(fp);
					if (TGA_Head.bpp == 32) a = Readbyte(fp);
					col = Gfx_Col(r,g,b);
					for (i=0; i<rep; i++) {
						memcpy(ptr,&col,step);
						ptr += step;
					}
					x -= rep;
				} else {
					// Raw Packet
					for (i=0; i<y+1; i++) {	
						b = Readbyte(fp);
						g = Readbyte(fp);
						r = Readbyte(fp);
						if (TGA_Head.bpp == 32) a = Readbyte(fp);
						col = Gfx_Col(r,g,b);
						memcpy (ptr,&col,step);
						ptr += step;
					}
					x -= y+1;
				}
			}
		}

		if (format) {
			// Now Flip it
			BYTE *scr	= data + (TGA_Head.sy-1) * TGA_Head.sx * step;
			ptr			= Gfx->scr;
			step		= TGA_Head.sx * step;
			for (i=0; i<TGA_Head.sy; i++) {
				memcpy (ptr,scr,step);
				ptr += step;
				scr -= step;
			}
		}
		delete[] data;

	} 
	if (!format) {
		// Error		
		zERR_FATAL(s + "\nTGA-format not supported !");
	}

	fp->Close();
	delete(fp);
	return(Gfx);	
}

void zCGfx :: SaveRaw ( const zSTRING &s )
{
	zFILE *f = zfactory->CreateZFile(s);
	
	int xdx = data->sx;
	int xdy = data->sy;
	int xanz = xdx * xdy * 2;
	f->Create();
	// Now write Data
	f->Write(data->scr,xanz);
	f->Close();
	delete(f);
}

void zCGfx :: Save(const zSTRING &s)
// Save Gfx as TGA-File
{
	#pragma pack (push,1)
	typedef struct TTGA_Head {
		BYTE idlen;
		BYTE colortable;
		BYTE type;
		WORD colIndex1;
		WORD colCount;		// In Doku this should be a word ?! 
		BYTE colBits;
		WORD xpos,ypos;
		WORD sx,sy;
		BYTE bpp;
		BYTE descr;
	} TTGA_Head;
	#pragma pack (pop)
	
	int y;
	TTGA_Head THead;

	if (data->bpp!=32) {
		zERR_FAULT("U:zGrafix: Save TGA only in 32bpp mode !");
		return;
	}
	memset(&THead,0,sizeof(TTGA_Head));
	// Init TGA_Head
	THead.sx	= data->sx;
	THead.sy	= data->sy;
	THead.type	= 2;			// Unmapped Uncompressed
	THead.bpp	= 32;
	// Save Head
	zFILE *f = zfactory->CreateZFile(s);
	f->Create();
	f->Write(&THead,sizeof(TTGA_Head));
	// Now write Data
	for (y=(data->sy-1); y>=0; y--) {
		BYTE *scr = data->scr + y * 4 * data->sx;
		f->Write(scr,data->sx*4);		
	}
	f->Close();
	delete(f);
}

TGfx_Gfx *zCGfx :: LoadGfx(const zSTRING &s)
{
	TGfx_Gfx *gfx = NULL;
	zSTRING s2;

	s2 = "U:(zGrafix) Loading Gfx : " + s;
	zERR_MESSAGE(8,0,s2);
	// Load it.
	if (s.Search(zSTRING(".PCX"))>=0) { 
		// PCX Load
		gfx = LoadPcx(s);
	} else if (s.Search(zSTRING(".TEX"))>=0) {
		// Raw Load
		gfx = LoadRaw(s,64,64,8);
	} else if (s.Search(zSTRING(".TGA"))>=0) {
		// Load Targa-File
		gfx = LoadTga(s);
	}
	if (gfx==NULL) zerr.Message("U:(zGrafix) Failed.");
	return(gfx);
}
	
////////////////////////////////////////////////
// Color + Palette Functions
////////////////////////////////////////////////

int Gfx_Col(const zCOLOR col)
{
	return Gfx_Col(col.r,col.g,col.b);
}

int Gfx_Col(int r,int g,int b)
// Seek a fitting color in current mode
{
	int i,dif,min,col;
	BYTE *pal;

	// Von 256C to 16Bit
	if ((zrenderer->vid_bpp==8) && (Gfx_pal!=NULL)) {
		pal = Gfx_pal + 10*4; dif = 0;
		i=0; col = 0; min = 65535;
		for (i=10; i<246; i++) {
			dif  = abs(r-*pal); pal++;
			dif += abs(g-*pal); pal++;
			dif += abs(b-*pal); pal+=2;
			if (dif<min) {
				min = dif; col = i;
			}
		}
	} else {
		r	= (r << VideoRSize) / 256;
		g	= (g << VideoGSize) / 256;
		b	= (b << VideoBSize) / 256;
		col = (r << VideoRPos) + (g << VideoGPos) + (b << VideoBPos);
		//col = (r << 10) + (g << 5) + (b << 0);
		/*
		
		if (zrenderer->vid_bpp==16) {
		r = r * 32 / 256;
		g = g * 64 / 256;
		b = b * 32 / 256;
		col = (r<<11)+(g<<5)+b;
	} else 
        col = (r<<16)+(g<<8)+b;*/
	}
	return(col);
}

// **********************************************************************
//					Info Functions for zCGfx
// **********************************************************************

int zCGfx :: GetSizex ( )
{
	return data ? data->sx : 0;
}

int zCGfx :: GetSizey ( )
{
	return data ? data->sy : 0;
}

zBYTE *zCGfx :: GetDataPtr ( )
{
	return data ? data->scr : NULL;
}

int	zCGfx :: GetPixel (int x, int y)
{
	if (!data) return 0;
	// FIXME : Derzeit nur 16 Bit
	zWORD* ptr = (zWORD*)data->scr;
	ptr += y * data->sx + x;
	return (int)*ptr;
}

void Gfx_Setpal(BYTE *pal)
{
	int i,r,g,b;
	BYTE *ptr;

	ptr = pal;
	// Make Table 16 Bit
	for (i=0; i<256; i++) {
		r = (*ptr++) * 32 / 256;	// reading Mem
		g = (*ptr++) * 32 / 256;
		b = (*ptr++) * 32 / 256;	// reading Mem
		ptr++;
		Gfx_Pal8to16[i] = (r<<10)+(g<<5)+b;			
	}
	ptr = pal;
	// Make Table 24 Bit
	for (i=0; i<256; i++) {
		r = (*ptr++);				// reading Mem
		g = (*ptr++);
		b = (*ptr++);				// reading Mem
		ptr++;
		Pal8to24[i] = (r<<16)+(g<<8)+b;			
	}
	ptr = pal;
	Gfx_pal = pal;
}

/* ----------------------------------------------------------------------
	
	Gfx_Loadpal

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

void Gfx_Loadpal(const char *s)
// Init this 256-Color-Palette
// KLUDGE:    Teufelswerk!  Direct File Access
// FIXME:	  Potentielles Speicherloch (malloc?!)
{
	FILE *f;
	BYTE *pal;
	int len,i;

	if (Gfx_pal==NULL) Gfx_pal=zNEW_ARRAY(BYTE,1024);

	zFILE::DirectFileAccess(true);
	if ((f = fopen(s,"rb")) != NULL) {
		fseek(f,0,SEEK_END);
		len = ftell(f);
		fseek(f,0,SEEK_SET);
		// Typ 1 : 768 Byte
		memset(Gfx_pal,0,1024);
		pal = Gfx_pal;
		if (len==768) {
			for (i=0; i<256; i++) {
				fread(pal,1,3,f);
				*pal = *pal * 256 / 64; pal++;
				*pal = *pal * 256 / 64; pal++;
				*pal = *pal * 256 / 64; pal+=2;
			}
		}
		fclose(f);
		// Activate Pal
		Gfx_Setpal(Gfx_pal);
	}
	zFILE::DirectFileAccess(false);
}

