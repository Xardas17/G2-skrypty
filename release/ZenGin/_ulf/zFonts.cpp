/******************************************************************************** 
 
     $Workfile:: zFonts.cpp           $                $Date:: 14.02.01 21:20   $
     $Revision:: 32                   $             $Modtime:: 14.02.01 21:20   $
       $Author:: Hildebrandt                                                    $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zFonts.cpp $
 * 
 * 32    14.02.01 21:20 Hildebrandt
 * 
 * 31    8.02.01 19:09 Speckels
 * 
 * 30    8.02.01 19:08 Speckels
 * 
 * 29    7.02.01 18:00 Speckels
 * 
 * 28    1.02.01 19:16 Speckels
 * 
 * 27    30.01.01 19:18 Hildebrandt
 * 
 * 26    27.01.01 2:43 Hildebrandt
 * 
 * 25    27.01.01 2:21 Hildebrandt
 * 
 * 24    16.01.01 22:53 Speckels
 * 
 * 23    18.12.00 10:25 Keskenti
 * 
 * 22    15.12.00 19:06 Keskenti
 * 
 * 21    4.12.00 15:39 Keskenti
 * 
 * 20    1.12.00 19:16 Keskenti
 * 
 * 19    1.12.00 19:07 Keskenti
 * 
 * 18    23.11.00 17:10 Hildebrandt
 * 
 * 17    13.11.00 20:52 Hildebrandt
 * 
 * 16    13.11.00 20:34 Hildebrandt
 * 
 * 15    24.10.00 19:30 Hildebrandt
 * 
 * 14    4.10.00 18:34 Hildebrandt
 * 
 * 13    2.10.00 18:51 Keskenti
 * 
 * 12    21.09.00 2:06 Rueve
 * 
 * 11    19.09.00 20:57 Wohlers
 * 
 * 10    2.08.00 21:09 Wohlers
 * 
 * 9     21.07.00 15:35 Wohlers
 * 
 * 8     21.07.00 14:43 Wohlers
 * 
 * 7     20.07.00 21:35 Wohlers
 * 
 * 6     4.07.00 12:28 Wohlers
 * FontMan Bugfix
 * 
 * 5     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 3     8.05.00 23:10 Edenfeld
 * 
 * 4     3.05.00 12:25 Wohlers
 * zCView Umstellung Polyrendern
 * 
 * 3     26.04.00 11:27 Admin
 * 
 * 1     19.04.00 18:16 Edenfeld
 * 
 * 5     3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zFonts.h"
#include "zGrafix.h"
#include "zRenderer.h"
#include "zOption.h"
#include "zDisk.h"
#include "zTexture.h"
#include "zarchiver.h"

#include "zWin32.h"

const int zFONT_DATA_VERSION = 1;

// **********************************************************************************
// FontManager
// **********************************************************************************

zCFontMan *zfontman = NULL;

zCFontMan :: zCFontMan ()
{
}

zCFontMan :: ~zCFontMan()
{
	for (int i=0; i<fontlist.GetNumInList(); i++) {
		delete fontlist[i];
	}
}

int zCFontMan :: SearchFont(const zSTRING& s)
{
	zSTRING n = s;
	n.Upper();
	for (int i=0; i<fontlist.GetNumInList(); i++) {
		if (n == fontlist[i]->GetFontName()) return i;
	};
	return -1;
}

int zCFontMan :: Load (const zSTRING &s)
{
	int nr = SearchFont (s);
	if (nr<0) {
		zCFont* font	= zNEW( zCFont(s) );
		fontlist.Insert ( font );
		nr = fontlist.GetNumInList()-1;
	}
	return nr;
}

int zCFontMan :: GetNumber ()
{
	return fontlist.GetNumInList();
}

zCFont* zCFontMan :: GetFont (int nr)
{
	if (nr<fontlist.GetNumInList()) 
		return fontlist[nr];
	else
		return NULL;
}

// **********************************************************************************
// Textures
// **********************************************************************************

zCTextureConvert* zCFont :: texConv = NULL;

zBOOL zCFont :: CacheIn( void )
{ 
	if ( this->fontTex ) 
	{ 
		this->fontTex->CacheIn( -1 ); 
		return TRUE; 
	} 
	else 
		return FALSE; 
}

/*	------------------------------------------------------------------
	zBOOL zCFont :: LoadFontTexture(const zSTRING &texName)
	 4.10.00	[HILDEBRANDT]	
				Beim Laden wird nun der Umweg ueber das .TGA vermieden, das .TEX wird direkt 
				eingeladen.
				Unnoetiges zoptions->ChangeDir (DIR_TEX) entfernt.
	13.11.00	[HILDEBRANDT]	
				Um in AnalyseLetters() auf der Fonttextur arbeiten zu koennen darf diese kein ggfs. geslictes
				Tile sein und wird deshalb nocheinmal separat als eine zweite Renderer-unabhaengige nicht-Tile 
				Textur eingeladen.
	23.11.00	[HILDEBRANDT]	
				Bugfix: LoadFont failte, falls konvertiertes Format noch nicht vorlag => fontTex->CacheIn(-1)
	27.11.00	[HILDEBRANDT]	
				Workaround von Roman wieder entfernt. Nun wird wieder komplett ohne .TGA Laden ausgekommen.
				Damit das AnalyseLetters() nicht auf 'unsauberen' Texturen (aka DXTC) arbeitet, muessen die Fonts
				im internen Format .TEX in 16/32 Bit vorliegen.
	------------------------------------------------------------------ */

zBOOL zCFont :: LoadFontTexture(const zSTRING &texName)
{
	zERR_MESSAGE (5, 0, "U: FNT: Loading Font: "+texName);

	// Und Fonts als brauchbare Textur fürn Renderer anlegen
	// Font Textur laden
	fontTex					= zCTexture::Load	((zSTRING)texName,zTEX_LOAD_FLAG_TILE);
//	fontTex->CacheIn		(-1);		// Font JETZT laden (damit falls noetig auch jetzt das konvertierte Format erstellt wird)

	zBOOL result = FALSE;

	if (LoadFontData())	
	// Font-Info-Datei (name.FNT) gefunden
	{
		result=TRUE;
	}
	else
	// Font-Info-Datei (name.FNT) nicht gefunden
	{
		// Convert Objekt erstellen und mit Texur fuellen
		texConv					= zrenderer->CreateTextureConvert	();	
	/*	{
			// Die Fonttextur wird hier nocheinmal eingeladen: diesesmal allerdings NICHT als Tile. Bei einem Einladen
			// als Tile koennte die Textur auf 3D-Hardware mit geringer moeglicher maximaler Texturdimension 'geslicet' 
			// werden, was ein spaeteres arbeiten auf der Textur (hier: AnalyseLetters) unmoeglich macht.
			// (Das einzige noch unschoene: das explizite "-C" im Filenamen unten..)
			zPATH path(texName);
			zCTextureFileFormatInternal* texFileInternal= zNEW(zCTextureFileFormatInternal);
			zBOOL res = texFileInternal->LoadTexture	(path.GetFilename()+"-C"+texFileInternal->GetFileExtension(), texConv);
			if (!res)
			{
				// ins interne Format konvertieren
				fontTex->CacheIn					(-1);
				// try again
				res = texFileInternal->LoadTexture	(path.GetFilename()+"-C"+texFileInternal->GetFileExtension(), texConv);
				zERR_ASSERT_STRICT					(res);
			};
			zRELEASE(texFileInternal);
		};*/

		// Analyse funktioniert nicht korrekt auf der Textur, da sie anti-aliased wird!
		// Deswegen hier wieder das .TGA laden
		// FIXME: Kann man nicht das TGA cachen ???
		zoptions->ChangeDir				(DIR_TEX);
		zCTextureFileFormatTGA*	texFile	= zNEW( zCTextureFileFormatTGA() );
		texFile -> LoadTexture			(texName,texConv);
		zRELEASE						(texFile);

		// Textur ins gewünschte Format konvertieren
		zCTextureInfo texInfo	= texConv ->GetTextureInfo();
		texInfo.texFormat		= zRND_TEX_FORMAT_RGBA_8888;
		result			= texConv->ConvertTextureFormat(texInfo);

		// Jetzt Fontdaten aus dieser Textur ermitteln.
		if (result) AnalyseLetters	();
		else		zERR_FAULT("U: FNT: Cannot convert Font "+texName);

		// TextureConvert Objekt wegschmeissen
		delete texConv; texConv = NULL;

		SaveFontData();
	}

/*	
ALT, mit dem Umweg ueber das .TGA..
	// Textur laden und ins Textureconvert Objekt packen
	zoptions->ChangeDir (DIR_TEX);
	texConv	= zrenderer->CreateTextureConvert();	
	zCTextureFileFormatTGA*	texFile		= zNEW( zCTextureFileFormatTGA() );
	texFile -> LoadTexture(texName,texConv);
	zRELEASE(texFile);
	// Textur ins gewünschte Format konvertieren
	zCTextureInfo texInfo	= texConv ->GetTextureInfo();
	texInfo.texFormat		= zRND_TEX_FORMAT_RGBA_8888;
	zBOOL result			= texConv->ConvertTextureFormat(texInfo);
	// Jetzt Fontdaten aus dieser Textur ermitteln.
	if (result) AnalyseLetters	();
	else		zERR_FAULT("U:FNT:Cannot convert Font "+texName);
	// TextureConvert Objekt wegschmeissen
	delete texConv; texConv = NULL;

	fontTex = zCTexture::Load ((zSTRING)texName,zTEX_LOAD_FLAG_TILE);
*/
	return result;
}

// **********************************************************************************
// Fonts
// **********************************************************************************

const int zFONT_DIST	= 1;		// Wieviele Pixel Abstand zwischen zwei Buchstaben
// const int zFONT_SPACE	= 3;		// wieviele Pixel hat ein Space ?

zCFont :: zCFont (const zSTRING &s)
{
	height	= 0;								// Height of Chars
	fontTex	= NULL;

	memset	(&width,	0,sizeof(width));
	memset	(&fontuv1,	0,sizeof(fontuv1));
	memset	(&fontuv2,	0,sizeof(fontuv2));

	LoadSource(s);
}

zCFont :: ~zCFont ()
{
	zRELEASE(fontTex); fontTex = NULL;
}

zBOOL zCFont :: LoadSource (const zSTRING &s)
{
	name = s;
	name.Upper();
	return LoadFontTexture(s);
}

zBOOL zCFont :: SaveFontData()
{		
	zSTRING saveName = name;		
	zFILE* file = zfactory->CreateZFile(saveName);
	if (file->GetExt()!="TGA")
	{
		zERR_FAULT("B: FONT: Name not correct: "+name);
		delete file;file=0;
		return FALSE;
	}	

	file->SetExt("FNT");
	file->SetDir(zoptions->GetDirString(DIR_COMPILED_TEXTURES));	

	zERR_MESSAGE(4,0,"B: FONT: Saving Font-Data: "+file->GetFullPath());

	file->Create();	

	int numLetters	= zFONT_MAX_LETTER;
	zSTRING version	= zSTRING(zFONT_DATA_VERSION);

	file->Write(version+"\n");
	file->Write(name+"\n");
	file->Write(&height,		sizeof(height));
	file->Write(&numLetters,	sizeof(numLetters));
	file->Write(width,sizeof(width));
	file->Write(fontuv1,sizeof(fontuv1));
	file->Write(fontuv2,sizeof(fontuv2));
	file->Close();
	delete file;file=0;
	return FALSE;
};

zBOOL zCFont :: LoadFontData()
{
	zBOOL success=FALSE;
	zSTRING saveName = name;		
	zFILE* file = zfactory->CreateZFile(saveName);
	if (file->GetExt()!="TGA")
	{
		zERR_FAULT("B: FONT: Name not correct: "+name);
		delete file;file=0;
		return success;
	}	

	file->SetExt("FNT");
	file->SetDir(zoptions->GetDirString(DIR_COMPILED_TEXTURES));		
	
	if (file->Exists() && file->Open()==zERR_NONE)
	{
		zERR_MESSAGE(4,0,"B: FONT: Loading Font-Data: "+file->GetFullPath());

		int numLetters;
		zSTRING version;

		file->Read(version);

		if (version.ToInt() != zFONT_DATA_VERSION)
		{
			zERR_WARNING("B: FONT: Wrong version ("+zSTRING(version)+") of fontdata-file: version "+zSTRING(zFONT_DATA_VERSION));
		}
		else
		{			
			file->Read(name);
			file->Read(&height,		sizeof(height));
			file->Read(&numLetters,	sizeof(numLetters));

			if (numLetters!=zFONT_MAX_LETTER) 
			{
				zERR_WARNING("B: FONT: Wrong format of fontdata-file.");			
			}
			else
			{
				file->Read(width,sizeof(width));
				file->Read(fontuv1,sizeof(fontuv1));
				file->Read(fontuv2,sizeof(fontuv2));

				success = TRUE;
			}
		}
		file->Close();		
	}
	delete file;file=0;
	return success;	
};

zSTRING	zCFont :: GetFontName ()
{
	return name;
}

int zCFont :: GetFontY()
{
	return height;
}

int zCFont :: GetFontX(const zSTRING& s)
{
	int		w	= 0;
	char	*c	= s.ToChar();
	int		dist= GetLetterDistance();
	while (*c != 0) 
	{
		w += width [zBYTE(*c)] + dist;		
		c++;
	};
	// if (w>dist) w -= dist;  // [SPECKELS] Entfernt: Was sollte das, fuehrte zur falschen Berechnung von Wortlaengen! => letzte 'Buchstabenluecke' mitrechnen!
	return w;
}

int zCFont :: GetWidth(char c)
{
	return width[zBYTE(c)];
}

int	zCFont::GetLetterDistance()
{
	return zFONT_DIST;
};

char zCFont :: MapToAscii(char c)
{
	switch (c) {
	  case 252 : return char(129);
	  case 228 : return char(132); 
	  case 196 : return char(142); 
	  case 246 : return char(148); 
	  case 214 : return char(153); 
	  case 220 : return char(154); 
	  case 223 : return char(225); 
	}
	return c;
}

int zCFont :: GetSizex ()
{
	if (texConv) {
		return texConv->GetTextureInfo().sizeX;
	}
	return 0;
}

int zCFont :: GetSizey ()
{
	if (texConv) {
		return texConv->GetTextureInfo().sizeY;
	}
	return 0;
}

int zCFont :: GetPixel (int x, int y)
{
	int color = 0;
	if (texConv) {
		void*	texBuffer	= NULL;
//		int*	buffer		= NULL;
		int		pitchBytes;

		if (!texConv->Lock(zTEX_LOCK_READ))
		{
			zERR_WARNING("C: zCFont :: GetPixel(): could not lock texture");
			return 0;
		};
		texConv->GetTextureBuffer(0,texBuffer,pitchBytes);
		zBYTE	*ptr		= (zBYTE*)texBuffer + (y * pitchBytes) + x * 4;
		color				= *(int*)ptr;
		texConv->Unlock();
	}
	return (color & 0xFFFFFF00);
}

int zCFont :: GetPixelAlpha (int x, int y)
{
	int color = 0;
	if (texConv) {
		void*	texBuffer	= NULL;
//		int*	buffer		= NULL;
		int		pitchBytes;

		if (!texConv->Lock(zTEX_LOCK_READ))
		{
			zERR_WARNING("C: zCFont :: GetPixelAlpha(): could not lock texture");
			return 0;
		};
		texConv->GetTextureBuffer(0,texBuffer,pitchBytes);
		zBYTE	*ptr		= (zBYTE*)texBuffer + (y * pitchBytes) + x * 4;
		color				= *(int*)ptr;
		texConv->Unlock();
	}
	return (color & 0x000000FF);
}

int	zCFont :: NextPixelX	(int px, int py, int &col)
{
	while (px < GetSizex()) {
		col  = GetPixel(px,py);
		if (col != 0) return px;
		px ++;
	};
	// Not found.
	return -1;
}

int	zCFont :: NextPixelY	(int px, int py, int &col)
{
	while (py < GetSizey()) {
		col  = GetPixel(px,py);
		if (col != 0) return py;
		py ++;
	};
	// Not found.
	return -1;
}

int	zCFont :: NextPixelXAlpha(int px, int py, int &alpha)
{
	while (px < GetSizex()) {
		alpha = GetPixelAlpha(px,py);
		if (alpha != 0) return px;
		px ++;
	};
	// Not found.
	return -1;
}

int	zCFont :: NextPixelYAlpha(int px, int py, int &alpha)
{
	while (py < GetSizey()) {
		alpha = GetPixelAlpha(px,py);
		if (alpha != 0) return py;
		py ++;
	};
	// Not found.
	return -1;
}

int zCFont :: NextPixelXCol (int px, int py, int col_match)
{
	int col = 0;
	while (px > -1) {
		px = NextPixelX (px,py,col);
		if (col==col_match) return px;
		else if (px!=-1) px++;
	};
	return -1;
}

int zCFont :: NextPixelYCol (int px, int py, int col_match)
{
	int col = 0;
	while (py > -1) {
		py = NextPixelY (px,py,col);
		if (col==col_match) return py;
		else if (py!=-1) py++;
	};
	return -1;
}

zBOOL zCFont :: AnalyseLetters()
{
	int	cornerx		= 0;
	int cornery		= 0;					// Begin of first cell
	int	cellx		= 0;
	int celly		= 0;					// Dims of a cell
	int	dimx		= 0;
	int	dimy		= 0;					// Number of cells

//	int	col_back	= GFX_BLACK;			// Color of background
	int	col_border	= GFX_BLACK;			// Color of cellborder
	int	col_letter	= GFX_BLACK;			// Color of letter

	int	deltax1		= 0;
	int	deltax2		= 0;					// Max. Letterdim x
	int	deltay1		= 0;
	int deltay2		= 0;					// Max. Letterdim y

	// **********************************
	// **********************************
	// ************************************
	// Find first Cell
	// **********************************
	// **********************************
	// ************************************
	int col		= 0;
	// Start der ersten Zelle ermitteln
	cornerx		= NextPixelX	(0,50,col) + 1;
	col_border	= col;
	cornery		= NextPixelYCol	(50,0,col_border) + 1;
	// Ende der ersten Zelle ermitteln
	int endx	= NextPixelXCol	(cornerx,cornery,col_border) - 1;
	int endy	= NextPixelYCol	(cornerx,cornery,col_border) - 1;
	// Größe einer Zelle
	cellx		= endx - cornerx + 1;
	celly		= endy - cornery + 1;
	if ((cellx<=0) || (celly<=0)) zERR_FAULT("U:FONT:Cannot convert Font (cell-size error)");
	
	// Wieviele Zellen pro Reihe ?
	dimx		= 1;
	int	found	= 0;
	int startx	= cornerx + cellx + 1;
	int starty	= cornery + celly + 1;
	while (found >= 0) {
		found	= NextPixelXCol (startx,starty,col_border);
		if (found >= 0) {
			dimx++;
			startx += cellx + 1;
		}
	}
	
	// Wieviele Zellen pro Spalte ?
	dimy		= 1;
	found		= 0;
	startx		= cornerx + cellx + 1;
	starty		= cornery + celly + 1;
	while (found >= 0) {
		found = NextPixelYCol (startx,starty,col_border);
		if (found >= 0) {
			dimy++;	
			starty += celly + 1;
		}
	}

	if ((dimx<=0) || (dimy<=0)) zERR_FAULT("U:FONT:Cannot convert Font (cell-count error)");
	
	// **********************************
	// **********************************
	// **********************************
	// AnalyseLetters()
	// **********************************
	// **********************************
	// **********************************
	int x1[256]; memset(&x1,0,sizeof(x1));
	int x2[256]; memset(&x2,0,sizeof(x1));
	
	int px		= cornerx;
	int py		= cornery;
	int cellpx	= 0;
	int	count	= 0;
	int ascii	= 32;
	// Starthöhe und Endhöhe berechnen
	deltay1		= celly + 1;	// oben 
	deltay2		= 0;			// unten
	do {
		// ***************************************
		// auf ersten Pixel vom Buchstaben checken
		// ***************************************
		deltax1	= cellx + 1;	// links
		deltax2	= 0;			// rechts
		int	sx	= px;
		int sy	= py;
		// Max. X-Dimensionen ermitteln pro Letter
		for (int dx = 0; dx < cellx; dx++) {	
			py	= NextPixelY/*Alpha*/ (sx + dx, sy, col_letter);
			if (py>=0) {	// Pixel gefunden, innerhalb der Range ?
				if (py < sy + celly) {
					// Ja ! Das ist ein Buchstabenpixel
					if (dx < deltax1) deltax1 = dx;
					if (dx > deltax2) deltax2 = dx;
				}
			}
		}
		// Und Breite speichern
		if (deltax2 < deltax1) {
			// keine Breite
			x1[ascii] = -1;
		} else {
			x1[ascii] = sx + deltax1;// + 1;
			x2[ascii] = sx + deltax2;// + 2;
		};

		// Max. Y-Dimensionen ermitteln für alle Letter
		for (int dy = 0; dy < celly; dy++) {	
			px	= NextPixelX/*Alpha*/ (sx,sy+dy,col_letter);
			if (px>=0) {	// Pixel gefunden, innerhalb der Range ?
				if (px < sx + cellx) {
					// Ja ! Das ist ein Buchstabenpixel
					if (dy < deltay1) deltay1 = dy;
					if (dy > deltay2) deltay2 = dy;
				}
			}
		}
		// ***************************************
		// Nächster Buchstabe
		// ***************************************
		count++;
		cellpx ++;
		if (cellpx >= dimx) {
			// Nächste Reihe
			cellpx	= 0;
			px		= cornerx;
			py		= sy + celly + 1;
		} else {
			// Nächste Spalte
			px		= sx + cellx + 1;
			py		= sy;
		}
		ascii++;
	} while (count < dimx*dimy);

	// *********************************
	// **********************************
	// **********************************
	// Calculate UV
	// *********************************
	// **********************************
	// **********************************

	height = deltay2 - deltay1 + 1;
	
	// Anzahl
	int number = dimx * dimy;
	if (32+number > 256) {
		zERR_FAULT("U:FONT:Cannot convert Font (char-count error)");
		zERR_FAULT("U:FONT:Is' mir scheiss egal - ich konvertier's trotzdem !!!");
		number = 256 - 32;
	//	return FALSE;
	}
	
	// Breiten ermitteln
	memset(width,0,sizeof(width));
	for (int i = 32; i < 32 + number; i++) {
		if (x1[i]>=0) width[i] = x2[i] - x1[i] + 1;
	}
	width[32] = width[97]; // Leerzeichen-Breite = Breite von 'a'

	// Buchstabendaten schreiben
	int sy  = cornery;
	int nrx = 0;
	for (i=32; i<32+number; i++) {
		
		// links oben
		fontuv1[i].n[0] = (float)x1[i] / (float)GetSizex();		// x1-Coord = U1 Coord
		fontuv1[i].n[1] = (float)sy    / (float)GetSizey();		// y1-Coord = V1 Coord
		// rechts unten
		fontuv2[i].n[0] = (float)(x1[i] + width[i] - 1)	/ (float)GetSizex();
		fontuv2[i].n[1] = (float)(sy	+ celly - 1)	/ (float)GetSizey();

		nrx ++;
		if (nrx>=dimx) {
			sy += celly + 1;
			nrx = 0;
		}
	}
	
	return TRUE;
}

zBOOL zCFont :: GetFontData	(const unsigned char letter, int& _fontWidth, zVEC2& _texuv1, zVEC2& _texuv2)
{
	if (letter<=zFONT_MAX_LETTER) {		
		_fontWidth	= width		[letter];
		_texuv1		= fontuv1	[letter];
		_texuv2		= fontuv2	[letter];
		return TRUE;
	}
	return FALSE;
}

zCTexture* zCFont :: GetFontTexture()
{
	return fontTex;
}

