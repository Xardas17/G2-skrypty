/******************************************************************************** 
 
     $Workfile:: zFonts.h             $                $Date:: 1.02.01 19:16    $
     $Revision:: 11                   $             $Modtime:: 1.02.01 19:08    $
       $Author:: Speckels                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/ZenGin/_Ulf/zFonts.h $
 * 
 * 11    1.02.01 19:16 Speckels
 * 
 * 10    16.01.01 22:53 Speckels
 * 
 * 9     15.12.00 19:27 Keskenti
 * 
 * 8     4.12.00 18:23 Moos
 * 
 * 7     2.10.00 18:51 Keskenti
 * 
 * 6     2.10.00 18:47 Keskenti
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
 * 5     22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ZFONTS_H__
#define __ZFONTS_H__

#ifndef __ZTYPES_H__
#include "zTypes.h"
#endif

#ifndef __ZALGEBRA_H__
#include "zAlgebra.h"
#endif

#ifndef __ZSTRING_H__
#include "zString.h"
#endif

#ifndef __ZCONTAINER_H__
#include "zContainer.h"
#endif


class zCGfx;
class zCTexture;
class zCTextureConvert;
class zVEC2;

const int zFONT_MAX_LETTER	= 256;

class zCFont
{
public: // Statics
	
public:	
	zCFont							(const zSTRING &s);
	~zCFont							();

	zBOOL		GetFontData			(const unsigned char letter, int& fontWidth, zVEC2& texuv1, zVEC2& texuv2);
	zCTexture*	GetFontTexture		();

	int			GetFontY			();
	int			GetFontX			(const zSTRING &s);
	int			GetWidth			(char c);
	int			GetLetterDistance	();
	zSTRING		GetFontName			();

	//
	//	CODECHANGE [ROMAN]
	//
	zBOOL		CacheIn				( void );
	//
	//	CODECHANGE [ROMAN] END
	//

	zBOOL		SaveFontData		();
	zBOOL		LoadFontData		();

private:
	zCFont							()  { memset(this,0,sizeof(*this)); };

	// *****
	zBOOL		LoadSource			(const zSTRING &s);
	char		MapToAscii			(char c);
	zBOOL		LoadFontTexture		(const zSTRING& s);
	zBOOL		AnalyseLetters		();

	int			GetSizex			();
	int			GetSizey			();
	int			GetPixel			(int x, int y);
	int			GetPixelAlpha		(int x, int y);
	
	int			NextPixelX			(int px, int py, int &col);
	int			NextPixelY			(int px, int py, int &col);

	int			NextPixelXCol		(int px, int py, int col_match);
	int			NextPixelYCol		(int px, int py, int col_match);
	
	int			NextPixelXAlpha		(int px, int py, int &alpha);
	int			NextPixelYAlpha		(int px, int py, int &alpha);

	// *****

	zSTRING		name;								// name of Font
	int			height;								// Height of Chars

	zCTexture*	fontTex;

	zBYTE		width	[zFONT_MAX_LETTER];			// Width of Chars
	zVEC2		fontuv1	[zFONT_MAX_LETTER];
	zVEC2		fontuv2	[zFONT_MAX_LETTER];

	// Statics 
	static		zCTextureConvert*	texConv;

};

class zCFontMan 
{
public :
	zCFontMan				();
	~zCFontMan				();

	int		Load			(const zSTRING &s);
	int		GetNumber		();
	zCFont*	GetFont			(int nr);

private:
	zBOOL	LoadTexure		(const zSTRING& s);
	int		SearchFont		(const zSTRING& s);
	zCArray <zCFont*>		fontlist;
};

extern zCFontMan* zfontman;

#endif