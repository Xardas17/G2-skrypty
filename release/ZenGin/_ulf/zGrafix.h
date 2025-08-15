/******************************************************************************** 
 
     $Workfile:: Zgrafix.h            $                $Date:: 4.12.00 18:23    $
     $Revision:: 5                    $             $Modtime:: 4.12.00 17:22    $
       $Author:: Moos                                                           $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/Zgrafix.h $
 * 
 * 5     4.12.00 18:23 Moos
 * 
 * 4     22.05.00 18:45 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 5     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 3     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZGRAFIX_H__
#define __ZGRAFIX_H__

#ifndef __ZTYPES3D_H__
#include "zTypes3d.h"
#endif

#ifndef __ZSTRING_H__
#include "zSTRING.h"
#endif

#ifndef __ZDISK_H__
#include "zDisk.h"
#endif


// Lustige Farbens
extern zCOLOR	GFX_WHITE,GFX_YELLOW,GFX_LYELLOW,GFX_GOLD,
				GFX_ORANGE,GFX_DORANGE,GFX_CARROT,
				GFX_RED,GFX_DRED,GFX_PINK,GFX_LPINK,GFX_DPINK,
				GFX_MAGENTA,GFX_ORCHID,GFX_PURPLE,GFX_VIOLET,
				GFX_CYAN,GFX_AQUA,GFX_GREEN,GFX_DGREEN,GFX_PALEGREEN,
				GFX_OLIVE,GFX_BLUE,GFX_LBLUE,GFX_MBLUE,GFX_INDIGO,
				GFX_DBLUE,GFX_SKY,GFX_STEEL,GFX_BROWN,GFX_OCHRE,
				GFX_DOCHRE,GFX_BEIGE,GFX_FLESH,GFX_KHAKI,GFX_GREY,
				GFX_LGREY,GFX_COLDGREY,GFX_WARMGREY,GFX_BLACK,GFX_IVORY;

extern zWORD Gfx_Pal8to16[256];

// Palette
int  Gfx_Col		(int r,int g,int b); 
int  Gfx_Col		(zCOLOR col);
void Gfx_Loadpal	(const char *s); 
void Gfx_Setpal		(zBYTE *scr); 

////////////////////////////////////////////////
//			Class - Definitions
////////////////////////////////////////////////

typedef struct TGfx_Gfx {
		zSTRING *id;						// Name of Grafix
		int bpp;							// Bits per Pixel = actual Bitdepth : 8,15,16,24,32
		int sx,sy;							// Original Size in Pixel
		int count;							// Reference-Counter
		zBYTE *scr;							// Pointer to Data
} TGfx_Gfx;

class zCGfx {
public:	
	zCGfx								(const zSTRING &file);				// Load a Grafik
	zCGfx								(int  x,int y);						// Init an empty Gfx
	~zCGfx								();
	
	void			Save				(const zSTRING &s);
	void			SaveRaw				(const zSTRING &s);

	// Info
	int				GetSizex			();
	int				GetSizey			();
	zBYTE*			GetDataPtr			();
	int				GetPixel			(int x, int y);

	TGfx_Gfx*		data;													// Pointer to Gfx-Data
	zCGfx*			next;													// Pointer to next class in list
	
	static void		Reload				();									// Reload Gfx-List

private:

	zBYTE			Readbyte			(zFILE *fp);
	TGfx_Gfx*		LoadGfx				(const zSTRING &file);
	TGfx_Gfx*		LoadTga				(const zSTRING &s);
	TGfx_Gfx*		LoadPcx				(const zSTRING &s);
	TGfx_Gfx*		LoadRaw				(const zSTRING &s,int w, int h,int bpp);
	
	static zCGfx*	Gfx_List;												// List of all loaded Gfx
	static int		gfxcount;												// Counter of all not loaded Gfx
};

#endif
