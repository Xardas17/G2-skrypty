/******************************************************************************** 
 
     $Workfile:: zTexture.cpp        $                $Date:: 22.05.01 18:45   $
     $Revision:: 43                   $             $Modtime:: 24.04.01 0:34    $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zTexture.cpp $
 * 
 * 43    22.05.01 18:45 Edenfeld
 * 
 * 42    17.03.01 2:10 Hildebrandt
 * 
 * 41    14.02.01 7:28 Hildebrandt
 * 
 * 40    31.01.01 18:24 Speckels
 * 
 * 39    31.01.01 3:12 Speckels
 * 
 * 38    31.01.01 3:07 Speckels
 * 
 * 37    31.01.01 3:07 Speckels
 * 
 * 35    31.01.01 1:26 Speckels
 * 
 * 34    28.01.01 23:57 Hildebrandt
 * 
 * 33    27.01.01 2:21 Hildebrandt
 * 
 * 32    12.01.01 15:14 Hildebrandt
 * 
 * 31    22.12.00 1:38 Hildebrandt
 * 
 * 30    4.12.00 18:23 Moos
 * 
 * 29    17.11.00 1:21 Hildebrandt
 * 
 * 28    9.11.00 18:00 Pelzer
 * 
 * 27    2.11.00 16:04 Speckels
 * 
 * 26    17.10.00 21:31 Hildebrandt
 * 
 * 25    4.10.00 18:35 Hildebrandt
 * 
 * 24    27.09.00 19:59 Hildebrandt 
 * 
 * 23    25.09.00 23:12 Pelzer
 * 
 * 22    20.09.00 20:54 Hildebrandt
 * 
 * 21    31.08.00 17:04 Hildebrandt
 * 
 * 20    21.08.00 17:18 Hildebrandt
 * 
 * 19    10.08.00 21:45 Speckels
 * 
 * 20    10.08.00 21:43 Hildebrandt
 *  
 * 19    9.08.00 17:12 Admin
 * 
 * 18    8.08.00 22:38 Hildebrandt
 * 
 * 18    8.08.00 22:34 Hildebrandt
 * 
 * 17    8.08.00 0:50 Integrator
 * Gothic 0.89
 * 
 * 17    7.08.00 16:47 Pelzer
 * 
 * 16    7.08.00 16:45 Pelzer
 * 
 * 15    21.07.00 15:11 Hildebrandt
 * 
 * 14    21.07.00 14:28 Hildebrandt
 * 
 * 13    13.07.00 19:56 Hildebrandt
 * 
 * 12    6.07.00 13:45 Hildebrandt
 * 
 * 8     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 7     9.05.00 21:14 Hildebrandt
 * zenGin 089h
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
 * 16    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 15    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 14    23.02.00 3:29 Hildebrandt
 * 
 * 13    22.02.00 19:53 Hildebrandt
 * 
 * 12    18.02.00 3:05 Hildebrandt
 * zenGin 087b
 * 
 * 11    18.02.00 1:39 Hildebrandt
 * 
 * 10    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 8     17.01.00 21:23 Hildebrandt
 * 
 * 7     17.01.00 20:30 Hildebrandt
 * incremental fix: textures have reference size/bpp in Spacer
 * 
 * 6     14.01.00 21:09 Hildebrandt
 * zenGin 0.85c
 * 
 * 5     11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 4     10.01.00 21:34 Hildebrandt
 * 
 * 2     10.01.00 16:05 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 43 $ ($Modtime: 24.04.01 0:34 $)

// Holy shit

// fuer zBOOL zCTexture::ConvertRecursive()
#include <direct.h>

#include <zCore.h>
#include <zResource.h>
#include <zTexture.h>
#include <zOption.h>
#include <zVisual.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

zCLASS_DEFINITION_ABSTRACT	(zCTexture, zCResource, zCLASS_FLAG_RESOURCE | zCLASS_FLAG_SHARED_OBJECTS)

///////////////////////////////////////////////////////////////////////////
//     Texture
///////////////////////////////////////////////////////////////////////////

// static element defs
zSTRING							zCTexture::zTEX_DEFAULT_TEXTURE_FILE= "DEFAULT.TGA";
//zCTexture*						zCTexture::s_texRoot				= 0;
zBOOL8							zCTexture::s_useDefaultTex			= TRUE;
zBOOL8							zCTexture::s_globalLoadTextures		= TRUE;;
zTTexScaleSize					zCTexture::s_texScaleSize			= zTEX_SCALE_SIZE_REFERENCE;
zTTexScaleBPP					zCTexture::s_texScaleBPP			= zTEX_SCALE_BPP_REFERENCE;
zDWORD							zCTexture::s_texSupportedFormats	= 0;
zDWORD							zCTexture::s_texMaxPixelSize		= 0;

// reference setup
zREAL							zCTexture::s_texRefRAM				= 16;
zCTexture::zTTexFileDesiredBPP	zCTexture::s_texRefBPP				= zCTexture::zTTexFileDesiredBPP::zTEX_FILE_DESIRED_BPP_8;


zCTexture::zCTexture()
{	
	InitValues(); 
};

void zCTexture::InitValues() 
{
	//
	hasAlpha		= FALSE;
	isAnimated		= FALSE;
	changingRealtime= FALSE;
	isTextureTile	= FALSE;

	// Ani
	for (int i=0; i<zTEX_MAX_ANIS; i++) {
		nextAni		[i] = prevAni[i] = 0;
		actAniFrame [i] = 0;
		numAniFrames[i] = 0;
	};
};

zCTexture::~zCTexture() 
{
//	zERR_ASSERT_STRICT (GetCacheState()!=zRES_CACHED_IN);

	// bei einer animierten Textur werden hier alle angehaengten 'Frames' geloescht
	// FIXME: das ist hier rekursiv! eine iterative Loesunge waere schneller...
	for (int i=zTEX_MAX_ANIS-1; i>=0; i--) 
	{
		if (nextAni[i])
		{
			nextAni[i]->CacheOut();		// dem ResourceManager mitteilen, dass er Refs auf Resource und diese auscachen soll (noetig!)
			zRELEASE (nextAni[i]);		// diese Resource gibt die Referenz auf die in nextAni[i] gespeicherte frei 
			prevAni[i] = 0;
		};
	};
};

zCTexture* zCTexture::SearchName (zSTRING& name) {
	name.Upper();					// safe
	return (zCTexture*)GetStaticClassDef()->SearchObject (name);
};


zBOOL zCTexture::IsLightmap () const
{
	// FIXME: koennte man auch anders testen..
	int len = GetName().Length();
	if (len<4) return TRUE;
	return (GetName()[len-4] != '.');
};

zCTexture* zCTexture::GetAniTexture	() 
{
	if (!isAnimated) return this;
	// FIXME: koennte über fixe Zugriffs-Tabellen schneller sein ..
	zCTexture* tex = this;
	for (int i=0; i<zTEX_MAX_ANIS; i++) {
		if (numAniFrames[i]==0) continue;
		for (int j=0; j<actAniFrame[i]; j++) {
			if (!tex->nextAni[i]) break;
			tex = tex->nextAni[i];
		};
	};
	return tex;
};

void zCTexture::AddAniTex (int channel, zCTexture *tex) 
{
	// Fuegt die Textur in der angegeb. Channel Kette hinten an
	assert ((channel>=0) && (channel<zTEX_MAX_ANIS));
	zCTexture *insertTex = this;
	while (insertTex->nextAni[channel])
	{
		insertTex = insertTex->nextAni[channel];
	};
	insertTex->nextAni[channel] = tex;
	tex->prevAni[channel]		= insertTex;
	tex->nextAni[channel]		= 0;
};

void zCTexture::PrecacheTexAniFrames (zREAL priority)
{
	zCTexture* tex = this;
	while (tex)
	{
		tex->CacheIn (priority);
		tex = tex->nextAni[0];
	};
};

// ==============================================================================================

zCTexture* zCTexture::Load (zSTRING& texFile, int texLoadFlags) 
{
	// Wie der Name angeliefert wird ist egal: gross/klein, mit/ohne Pfad, welche Extension.
	// Allein der filename an sich ist wichtig.
	if (texFile.Length()<=0)		return 0; 
	if (!GetGlobalLoadTextures())	return 0;

	zPATH	texPath (texFile);
	zSTRING	texName (texPath.GetFilename()+".TGA");

	// 1. Texture bereits im Speicher ? => exit	(override)
	zCTexture *tex = zCTexture::SearchName (texName);
	if (tex) return static_cast<zCTexture*>(tex->AddRef());

	// über texFileName rausfinden: ist die Textur eine Ani-Textur ?
	enum { MAX_PREFIX=zTEX_MAX_ANIS+2 };
	int		numAnis = 0;
	zSTRING	aniPrefix[MAX_PREFIX];
	zSTRING	number;
	zSTRING baseName;

	int i=1;
	do {
		number		= texFile.PickWord (i, "_", "_");
		i++;
		if (number.Length()<=0) break;
		// mind 2 chars, erster keine Zahl, zweiter eine Zahl => Multitexture Kennung!
		if ((number.Length()>=2) && 
			((number[0]< '0') || (number[0]> '9')) &&
			((number[1]>='0') && (number[1]<='9'))) 
		{
			aniPrefix[numAnis] = zSTRING("_") + zSTRING(number[0]);
			numAnis++;
		} else {
			// falls ein nicht "X0" Segment bereits vorhanden "X0" Segmenten folgte, 
			// liegt keine MultiChannel Texture vor.
			// "MAUER_F08_256.TGA" ist keine MultiChannel Textur
			if (numAnis>0) {
				numAnis = 0;
				break;
			};
			baseName += number+"_";
		};
		if (numAnis>=MAX_PREFIX) break;
	} while (1);

	// Yep, eine Ani-Texur mit n Kanaelen
	if (numAnis>0) {

		if (numAnis>=zTEX_MAX_ANIS) {
			numAnis=zTEX_MAX_ANIS;
			zERR_WARNING ("D: TEX: numTextureChannels > "+zSTRING(zTEX_MAX_ANIS)+", file: "+texFile);
		};

		baseName.Delete (baseName.Length()-1, 1);
		zSTRING ext		(".tga");
		zSTRING name;
		int		i,j;
		int		actFrames [zTEX_MAX_ANIS]; 
		for (i=0; i<numAnis; i++) actFrames[i] = 0;

		// Jetzt nacheinander alle FileNamen generieren 'name_xx_yy.???'
		// wie ein digit-counter...
		zCTexture *tex		= 0;
		zCTexture *baseTex	= 0;
		zCTexture *firstTex	= 0;
		zCTexture *lastTex	= 0;
		actFrames[0]= -1;
		do {
			j =-1;
			do {
nextRun:
				if (j>numAnis-2) goto leave;
				if (j>=0)
				actFrames[j  ] =0;
				actFrames[j+1]++;
				j++;
				name = baseName;
				for (int k=numAnis-1; k>=0; k--) { 

// FIXME: scheinbar ein Compiler Bug! Bei Entfernen folgender sinnloser Zeilen gibt's im Release eine AV
int val=numAnis-k-1;
//zerr.Message ("D: val: "+texFile+","+zSTRING(val)+","+zSTRING(numAnis)+","+zSTRING(k));
if (val<0)
	zerr.Message ("D: ölkj");

					name += aniPrefix[numAnis-k-1] + zSTRING(actFrames[k]); 
				};

				// load 
				lastTex = tex;

				// Texture auf Platte vorhanden ?
				// a) das Texture-Verzeichnis durchkaemmen
				// Suche nach ".TGA" oder ".TEX" oder ".3DF" oder IRGENDWAS (TGA darf nich allein !!! => Release CD Version hat keine TGAs)
				// zuerst im Compiled-VZ, ist schneller
				// FIXME: Schneller ist hier ein file.Exists() auf dem Namen (=> ".3df" Extension vom Renderer erfragen..)
				zFILE* tfile = zfactory->CreateZFile(zoptions->GetDirString(DIR_COMPILED_TEXTURES) + name+"-C.TEX");
//zerr.Warning ("D: TEX: trying: "+name);
				if (tfile->Exists()) 
				{
					tex = LoadSingle (name+ext, texLoadFlags);
				} else {
					// .. sollte hier nicht mehr passieren => ueber CmdLineSwitch sollte alles konvertiert werden
					// nun im gesamten Tex-VZ
					// FIXME: aus Faulheit benutze ich hier einfach das Flag des Meshes..
					if (zCMesh::GetAutoConvertMeshes()) 
					{
						zPATH path;
						if (path.SearchFile(name+".*", zoptions->GetDirString(DIR_TEX))==zERR_NONE) {
							tex = LoadSingle (name+ext, texLoadFlags);
						} else tex=0;
					} 
					else tex=0;
				};  

				delete tfile; tfile=0;

				if (tex) {
					// Texture existiert
					if (!firstTex) firstTex=tex;
					if (!baseTex)  baseTex =tex;
					if (lastTex) {
						int channel = numAnis - j -1;
						(firstTex->numAniFrames[channel])++; 
						lastTex->AddAniTex (channel, tex);
					}
				} else {
					// 2x am Stueck nichts gefunden => exit
					if (baseTex==0) goto leave;
					lastTex = baseTex;
					tex		= baseTex;
					baseTex = 0;
					goto nextRun;
				};

			} while (tex==0);
		} while (1);

		goto leave;
leave:;
		// der erste Channel muss eins draufgezaehlt bekommen
		if (firstTex) {
			(firstTex->numAniFrames[0])++; 
			firstTex->isAnimated = TRUE; 
//			zerr.Message ("animated");
			return firstTex;
		} else {
			// Texture not found => weiterreichen an die nächste Schicht, diese muss es handeln
//			zerr.Message ("not animated");
			return LoadSingle (texFile, texLoadFlags); 
		};
	  
	} else {
		return LoadSingle (texFile, texLoadFlags);
	};
};

zCTexture* zCTexture::LoadSingle (zSTRING& texFile, int texLoadFlags) 
{
	// Wie der Name angeliefert wird ist egal: gross/klein, mit/ohne Pfad, welche Extension.
	// Allein der filename ist wichtig.

	if (texFile.Length()<=0) return 0;
	zPATH	texPath (texFile);
	zSTRING texName (texPath.GetFilename() + ".TGA");	// TGA fest eingesetzt, um kaputte Filenames autom. zu reparieren ("SCHORNSTEIN.TG")
	texName.Upper();

	// Texture-Name: "<name>.TGA", ohne Pfade, mit .TGA Extension
	// Texture erzeugen
	zCTexture *tex = zrenderer->CreateTexture ();
	if (!tex) return 0;

	// soll die Textur als TextureTile behandelt werden ?
	tex->isTextureTile	= (texLoadFlags & zTEX_LOAD_FLAG_TILE)!=0;

	//
	tex->SetName		(texName);

	//
/*#ifndef ZENGINE_DEBUG
	zBOOL res = tex->CacheIn	();
	if (!res) {
		// Texture konnte nicht geladen werden, Objekt zerstoeren
		zRELEASE (tex);
	};
#endif
*/
	return tex; 
};


// zCTexture::Exists: findet heraus, ob die gewünschte Textur im Speicher oder auf der HD (Format egal)
// liegt. Nicht besonders schnell.
zBOOL zCTexture::Exists(zSTRING &name)
{
	// im speicher ?
	if (zCTexture::SearchName (name)) 
	{
		return TRUE;
	}
	// auf HD bereits compiliert ?
	zFILE* tfile = zfactory->CreateZFile(zoptions->GetDirString(DIR_COMPILED_TEXTURES) + name+"-C.TEX");
	
	if (tfile->Exists()) 
	{ 
		delete tfile; tfile = 0;
		return TRUE;
	}

	// auf HD noch nicht kompiliert ?
	zPATH path;
	if (path.SearchFile(name+".*", zoptions->GetDirString(DIR_TEX))==zERR_NONE) 
	{
		return TRUE;
	}
	return FALSE;
}

// =================================================================================================

void zCTexture::AutoDetectRendererTexScale () 
{
	// FIXME: irgendwie virtual machen.. (zCRenderer?)
	//
/*	s_texSupportedFormats = 0;
	for (int i=0; i<zRND_TEX_FORMAT_COUNT; i++)
		if (zrenderer->SupportsTextureFormat (zTRnd_TextureFormat(i))) s_texSupportedFormats |= (1<<i);
*/

	// 
	const zREAL oneMB	= (1024.0F*1024.0F);
	zREAL defRAM		= s_texRefRAM;
	zREAL availRAM		= zFloor (zREAL(0.5F) + zREAL(zrenderer->GetTotalTextureMem()) / (oneMB));	// round nearest 1MB !
	zBOOL S3TC			= zrenderer->SupportsTextureFormat (zRND_TEX_FORMAT_DXT1);

	if (S3TC) 
	{ 
		// S3TC availabe
		if (availRAM>=2.0F*defRAM) {		// >= 32MB
			// size: 1 higher	* 4
			s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_S3TC;
		} else 
		if (availRAM>=1.5F*defRAM) {		// >= 6MB
			// size: n/2 0.5 higher	*2
			// size: n/2 1   higher	*4	=> *3
			s_texScaleSize	= zTEX_SCALE_SIZE_Y_XY_ONE_HIGHER_EVERY_SECOND;
			s_texScaleBPP	= zTEX_SCALE_BPP_S3TC;
		} else 
		if (availRAM>=1.0F*defRAM) {		// >= 4MB
			// size: 0.5 higher		*2
			s_texScaleSize	= zTEX_SCALE_SIZE_Y_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_S3TC;
		} else {
			// size: reference
			s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_S3TC;
		};
	} else 
	{
		// no texture compression available
		// was, wenn Karte das kein Format mit der RefBPP beherscht ? 
		// => Ausweich BPP ermitteln und Berechnungen darauf anpassen
		zTRnd_TextureFormat		texFormat		= CalcNextBestTexFormat			(s_texDesiredBPPDefault[s_texRefBPP]);
		zTRnd_TexFormatInfo		formatInfoRes	= zrenderer->GetTexFormatInfo	(texFormat);
		zTRnd_TexFormatInfo		formatInfoRef	= zrenderer->GetTexFormatInfo	(s_texDesiredBPPDefault[s_texRefBPP]);
		zREAL ratio		=  zREAL(formatInfoRef.bytesPerPixel) / zREAL(formatInfoRes.bytesPerPixel);
		availRAM		*= ratio;

		//
		if (availRAM>=4.0F*defRAM) {		// >= 16MB
			s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_ONE_HIGHER;
		} else 
		if (availRAM>=3.5F*defRAM) {		// >= 14MB
			s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE;
		} else 
		if (availRAM>=3.0F*defRAM) {		// >= 12MB
			s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE;
		} else 
		if (availRAM>=2.5F*defRAM) {		// >= 10MB
			s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE;
		} else 
		if (availRAM>=2.0F*defRAM) {		// >= 8MB
			s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE;
		} else 
		if (availRAM>=1.5F*defRAM) {		// >= 6MB
			s_texScaleSize	= zTEX_SCALE_SIZE_Y_ONE_HIGHER;
			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE;
		} else 
		if (availRAM>=1.0F*defRAM) {		// >= 4MB
			// reference
			s_texScaleSize	= zTEX_SCALE_SIZE_REFERENCE;
			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE;
		} else {
			s_texScaleSize	= zTEX_SCALE_SIZE_REFERENCE;
			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE;
//			s_texScaleSize	= zTEX_SCALE_SIZE_X_ONE_LOWER;
//			s_texScaleBPP	= zTEX_SCALE_BPP_REFERENCE; 
		};
	};

	// TexMaxSize setzen
	{
		// zunaechst den Wert aus der .ini holen und setzen
		RefreshTexMaxSize	();
		// dann ggfs. durch einen Wert aus der CmdLine ueberschreiben
		if (zoptions->Parm ("ZTEXMAXSIZE")) {
			s_texMaxPixelSize	= zMin (s_texMaxPixelSize, zAbs(zoptions->ParmValueInt("ZTEXMAXSIZE")));
		};
		zERR_BOUNDS			(s_texMaxPixelSize, 1, 65536);
	};

	zERR_MESSAGE(3,0, "D: TEX: texMaxSize: "+zSTRING(s_texMaxPixelSize)+", texScaleSize: "+zSTRING(s_texScaleSize-zTEX_SCALE_SIZE_REFERENCE)+", texScaleBPP: "+zSTRING(s_texScaleBPP-zTEX_SCALE_BPP_REFERENCE));

	if (s_texMaxPixelSize<32)
	{
		zERR_FATAL("C: maximum texture size is lower than 32. possible reasons: wrong gfx driver setup (install other driver), bad os state (try to reboot), or insufficient gfx hardware (buy better gfx card!) ");
	}

	// im Spacer wollen wir immer die Referenz Werte
	
#ifdef COMPILING_SPACER
	s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER;
	s_texScaleBPP	= zTEX_SCALE_BPP_S3TC;
#endif
	

#ifdef ZENGINE_DEBUG
// FIXME 
//s_texScaleBPP		= zTEX_SCALE_BPP_REFERENCE;
//s_texScaleBPP		= zTEX_SCALE_BPP_ONE_HIGHER;

//s_texScaleSize	= zTEX_SCALE_SIZE_REFERENCE;
//s_texScaleSize	= zTEX_SCALE_SIZE_X_ONE_LOWER;
//s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_LOWER;
//s_texScaleSize	= zTEX_SCALE_SIZE_XY_ONE_HIGHER_EVERY_SECOND;
//s_texMaxPixelSize	= 64;

#endif
/*
	zTEX_SCALE_SIZE_XY_ONE_LOWER=0,					// / 4
	zTEX_SCALE_SIZE_X_ONE_LOWER,					// / 2
	zTEX_SCALE_SIZE_REFERENCE,						// * 1 <==
	zTEX_SCALE_SIZE_Y_ONE_HIGHER,					// * 2
	zTEX_SCALE_SIZE_XY_ONE_HIGHER_EVERY_SECOND,		// * 2
	zTEX_SCALE_SIZE_Y_XY_ONE_HIGHER_EVERY_SECOND,	// * 3
	zTEX_SCALE_SIZE_XY_ONE_HIGHER,					// * 4
	zTEX_SCALE_SIZE_XY_MAX,							// * ?

	zTEX_SCALE_BPP_S3TC=0,							// / 2
	zTEX_SCALE_BPP_REFERENCE,						// * 1 <==
	zTEX_SCALE_BPP_ONE_HIGHER,						// * 2
	zTEX_SCALE_BPP_MAX								// * ?
*/
	// force: bpp, size
};

 
void zCTexture::RefreshTexMaxSize (int newTexMaxSize)
{
	// texMaxSize von aussen setzen?
	if (newTexMaxSize>0)
	{
		zoptions->WriteInt (zOPT_SEC_VIDEO, "zTexMaxSize", newTexMaxSize);
	};
	//
	s_texMaxPixelSize			= zrenderer->GetMaxTextureSize();
	const zDWORD texMaxSizeINI	= zDWORD(zAbs(zoptions->ReadInt (zOPT_SEC_VIDEO, "zTexMaxSize", 16384)));
	s_texMaxPixelSize			= zDWORD(zMin ( int(s_texMaxPixelSize), int(texMaxSizeINI)));
	zERR_BOUNDS					(s_texMaxPixelSize, zDWORD(1), zDWORD(65536));
	zClamp						(s_texMaxPixelSize, zDWORD(1), zDWORD(65536));
};

// static zCTextureFileFormatInternal texFileFormatInternalDummy;

zBOOL zCTextureConvert::LoadFromFileFormat	(const zSTRING& fileName)
{
	zCClassDef* classDef;
	zCClassDef* classDefBase	= zCTextureFileFormat::GetStaticClassDef ();
	for (int i=0; i<zCClassDef::GetNum(); i++) 
	{
		classDef = zCClassDef::GetClassDefByIndex (i);
		if ((zCObject::CheckInheritance (classDefBase, classDef)) && (classDef!=classDefBase))
		{
			// FIXME: BESCHLEUNIGBAR.. extension des fileName am Anfang extrahieren
			// FIXME: unschoen: 'new' um an Infos ueber die Klasse zu kommen
			//        andere Moeglichkeit: als Startup von jeder Klasse ein Dummy-Objekt erzeugen, von dem dann runtime
			//        Infos geholt werden koennen
			zCTextureFileFormat *texFileFormat = (zCTextureFileFormat*)classDef->CreateNewInstance();
			if (texFileFormat->CanLoad())
			if (fileName.Search(texFileFormat->GetFileExtension())!=-1)
			{
				zBOOL res = texFileFormat->LoadTexture (fileName, this);
				texFileFormat->Release();
				return res;
			};
			texFileFormat->Release();
		};
	};
	return FALSE;
};

zBOOL zCTextureConvert::SaveToFileFormat	(const zSTRING& fileName) 
{
	zCClassDef* classDef;
	zCClassDef* classDefBase	= zCTextureFileFormat::GetStaticClassDef();
	for (int i=0; i<zCClassDef::GetNum(); i++) 
	{
		classDef = zCClassDef::GetClassDefByIndex (i);
		if ((zCObject::CheckInheritance (classDefBase, classDef))  && (classDef!=classDefBase))
		{
			// FIXME: extension des fileName am Anfang extrahieren
			zCTextureFileFormat *texFileFormat = (zCTextureFileFormat*)classDef->CreateNewInstance ();
			if (texFileFormat->CanSave())
			if (fileName.Search(texFileFormat->GetFileExtension())!=-1)
			{
				texFileFormat->SaveTexture (fileName, this);
				texFileFormat->Release();
				return TRUE;
			};
			texFileFormat->Release();
		};
	};
	return FALSE;
};
 
zBOOL zCTextureConvert::LoadFromFileFormat	(zFILE& file, zCTextureFileFormat* fileFormat) 
{
	if (!fileFormat->CanLoad())	return FALSE;
	return fileFormat->LoadTexture (file, this);
};

zBOOL zCTextureConvert::SaveToFileFormat	(zFILE& file, zCTextureFileFormat* fileFormat)
{
	if (!fileFormat->CanSave())	return FALSE;
	return fileFormat->SaveTexture (file, this);
};

zBOOL zCTextureConvert::SaveInternal (zFILE& file)
{
	zCTextureFileFormatInternal *texFile	= zNEW(zCTextureFileFormatInternal);
	zBOOL res = texFile->SaveTexture (file, this);
	texFile->Release();
	return res;
};

zBOOL zCTextureConvert::LoadInternal (zFILE& file)
{
	zCTextureFileFormatInternal *texFile	= zNEW(zCTextureFileFormatInternal);
	zBOOL res = texFile->LoadTexture (file, this);
	texFile->Release();
	return res;
};

// contents manipulation
void zCTextureConvert::ConvertToNewFormat(const zTRnd_TextureFormat& newTexFormat)
{
	zCTextureInfo& destTexInfo	= GetTextureInfo();
	destTexInfo.texFormat		= newTexFormat;
//	zBOOL res= ConvertTextureFormat (destTexInfo);
	ConvertTextureFormat (destTexInfo);
}

//
// Hier wird die Textur in eine neue groesse konvertiert.
// wobei keine besonderen smoothing-algorithmen verwendet
// werden sollen.
//

void zCTextureConvert::ConvertToNewSize(const int newTexSizeX, const int newTexSizeY)
{	
	// automatically corrects 1/8 aspect ratio faults
	zCTextureInfo& destTexInfo	= GetTextureInfo();
	destTexInfo.sizeX			= newTexSizeX;
	destTexInfo.sizeY			= newTexSizeY;
	CorrectPow2					(destTexInfo.sizeX, destTexInfo.sizeY);
	CorrectAspectRatio			(destTexInfo.sizeX, destTexInfo.sizeY);
	destTexInfo.numMipMap		= CalcNumMipMaps (destTexInfo.sizeX, destTexInfo.sizeY);
//	zBOOL res= ConvertTextureFormat (destTexInfo);
	ConvertTextureFormat (destTexInfo);
}	

void zCTextureConvert::GenerateMipMaps()
{
	zCTextureInfo& destTexInfo	= GetTextureInfo();
	destTexInfo.numMipMap		= CalcNumMipMaps (destTexInfo.sizeX, destTexInfo.sizeY);
//	zBOOL res= ConvertTextureFormat (destTexInfo);
	ConvertTextureFormat (destTexInfo);
}

int zCTextureConvert::CalcNumMipMaps (zDWORD xdim, zDWORD ydim)
{
	int numMipMaps	= 1;
	while (xdim>4 && ydim>4)
	{	
		numMipMaps++;	
		xdim>>=1;	
		ydim>>=1;
	}
	if (numMipMaps>0) numMipMaps--;		// FIXME: korrekt so ??? Adrians TexConvert Code scheint das so zu wollen
	return numMipMaps;
};

void zCTextureConvert::CorrectAspectRatio (int& xdim, int& ydim)
{
	// FIXME: den Wert aus den Renderer-Caps holen!
	// reference: 1/8 aspect ratio
//	zClamp (xdim, 0, 256);
//	zClamp (ydim, 0, 256);
	float maxAspectRatio = 8;
	if (xdim>ydim) {
		float ratio = float(xdim) / float(ydim);
		if (ratio>maxAspectRatio) ydim = ydim * (ratio / maxAspectRatio);
	} else {
		float ratio = float(ydim) / float(xdim);
		if (ratio>maxAspectRatio) xdim = xdim * (ratio / maxAspectRatio);
	};
};

void zCTextureConvert::CorrectPow2 (int& xdim, int& ydim)
{
	int xsize	= xdim;
	int ysize	= ydim;
	int b;
	b = xsize;	do	{ xsize= b;	b = b&(b-1); } while(b);
	b = ysize;	do	{ ysize= b;	b = b&(b-1); } while(b);
	
	xdim = xsize;
	ydim = ysize;
};

// ============================================================================================================

// zCResource Interface

zBOOL zCTexture::LoadResourceData ()
{
	// Lightmaps werden fuers erste weder ein- noch ausgecachet!
	if (IsLightmap())	return TRUE;
	zBOOL res = CacheInNamed (&GetName());
	return res;
};

zBOOL zCTexture::ReleaseResourceData ()
{
	// Lightmaps werden fuers erste weder ein- noch ausgecachet!
//	if (IsLightmap())	return;

	ReleaseData();

	// Bei einem TextureTile muessen auch die einzelnen Slices released werden
	if (this->IsTextureTileBaseSlice())
	{
		zCTexture *tex;
		for (int i=0; i<zTEX_MAX_ANIS; i++) 
		{
			tex = nextAni[i];
			while (tex) 
			{
				tex->ReleaseData();
				tex->SetCacheState (zRES_CACHED_IN);
				tex = tex->nextAni[i];
			};
		};
	};

	return TRUE;
};

zDWORD zCTexture::GetResSizeBytes ()
{
	if (this->IsTextureTile())
	{
		// TextureTile, aber nicht das erste? => hat offiziell keine Groesse
		if (this->IsTextureTileBaseSlice())
			return GetMemSizeBytes();			// FIXME: hier muesste eigentlich die Groesse alle Slices aufsummiert werden; da dieser Wert aber eh nur fuer 'statistische' Dinge benutzt wird, halten wir's hier einfacher
		else
			return 0;
	} else
		return GetMemSizeBytes();
};

/*
	- Texture-Tiles mit mehreren zCTexture in der Verkettung, so sollte das Verhalten sein:
		- CacheIn			: auf baseSlice laedt alle Slices ein, auf anderen Slices wirklungslos
		- CacheOut			: auf baseSlice cacht alle Slices aus, auf anderen Slices wirklungslos
		- GetMemSizeBytes	: auf baseSlice: Summe aller Slices; auf anderen Slices: 0
*/

/*--------------------------------------------------------------------------
	
	void zCTexture::GetCacheConfig (zDWORD &cacheOutTimeMSec, zDWORD &cacheSizeMaxBytes)

    25-Sep-00       [PELZER]
					cacheOutTimeMSec auf 3 Minuten gesetzt.
    27-Sep-00       [HILDEBRANDT]
					CacheSizeMaxBytes auf 22MB gesetzt (von verwendetem TexFormat unabh.)
    17-Oct-00       [HILDEBRANDT]
					CacheSizeMaxBytes bei nicht Unterstuetzung von HW-DXTC erhoeht
--------------------------------------------------------------------------*/

void zCTexture::GetCacheConfig (zDWORD &cacheOutTimeMSec, zDWORD &cacheSizeMaxBytes)
{   

	static zBOOL	configRead = FALSE;
	static zDWORD	s_cacheOutTimeMSec;
	static zDWORD	s_cacheSizeMaxBytes;

	if (!configRead)
	{
		configRead = TRUE;
		// .ini auswerten
		s_cacheOutTimeMSec	= zoptions->ReadDWord ("ENGINE", "zTexCacheOutTimeMSec"	, 240000);		// 240 secs [PELZER]
		s_cacheSizeMaxBytes = zoptions->ReadDWord ("ENGINE", "zTexCacheSizeMaxBytes", 32000000);	// 32 MB, fuer 16bit Texturen
		// Die CacheSize wird unter bestimmten Bedingungen verdoppelt
		zBOOL doubleCacheSize		= FALSE;
		zBOOL tripleCacheSize		= FALSE;

		// a) bei mehr als 256MB Hauptspeicher 
		// FIXME FIXME: Windows-spezischischer Code: an einen Platform spezifischen Ort verlegen!!
		{
			enum {	ONEM			= (1024*1024)	};
			MEMORYSTATUS			memInfo;
			memInfo.dwLength		= sizeof(memInfo);
			GlobalMemoryStatus		(&memInfo);
			int memoryTotalMB		= (memInfo.dwTotalPhys + ONEM - 1) / ONEM;
			if (memoryTotalMB>512)
				tripleCacheSize		= TRUE;
			else if (memoryTotalMB>256)
				doubleCacheSize		= TRUE;
		};


		// b) falls die Hardware kein DXTC beherrscht
		// Werte beziehen sich auf default DXTC, cacheSize erhoehen, falls Renderer kein DXTC kann ..
		// (=> dann wird hoechstwahrscheinlich 16Bit benutzt, je nachdem was die HW kann)
		{
			if (!zrenderer->SupportsTextureFormatHardware(zRND_TEX_FORMAT_DXT1))
				doubleCacheSize		= TRUE;
		};

		if (tripleCacheSize)
		{
			s_cacheSizeMaxBytes	*= 3;
			s_cacheOutTimeMSec  *= 2;
		}
		else if (doubleCacheSize)
		{
			s_cacheOutTimeMSec  *= 1.5f;
			s_cacheSizeMaxBytes	*= 2;
		};
	};

	cacheOutTimeMSec = s_cacheOutTimeMSec;
	cacheSizeMaxBytes= s_cacheSizeMaxBytes;

};

// ============================================================================================================

zBOOL zCTexture::ConvertTexture (const zSTRING& texFileName)
{
	// 4 zCTextureConvert erzeugen:
	// - .TGA, .TEX (default), .TEX (hi-qual), .TEX (S3TC)
	// - .TGA in zCTextureConvert 
	// - die anderen 3 TexFiles aus dem TGA Texfile über einen Convert erzeugen
	// - " auf Platte sichern
	// - alle Texfiles loeschen

	if (texFileName.IsEmpty()) return TRUE;

	//
	zBOOL funcResult = TRUE;

	// Konvertier-Hints/Argumente aus dem Pfad des Source-Textures auswerten
	zBOOL	noMipMap			= FALSE;
	zBOOL	detailTextureMode	= FALSE;
	int		refSize				= -1;
	int		desiredBPP			= -1;		// -1 = default DXTC, sonst: 8,16,32
	zFILE	*srcTexPath			= zfactory->CreateZFile ("");
	zSTRING	srcFileName			(texFileName);

	// ACHTUNG: kann es sein, dass SearchFile()/_findnext nicht threadSafe sind ?
	// falls nicht: hier eine CriticalSection einfuehren, oder gleich in SeachrFile()??
	// => _findnext macht Probleme, allerdings derzeit auch der zCTextureConvert Code (statics...)

	// Zur Sicherheit (derzeit) die Texture Konvertierung serialisieren
	static zCCriticalSection s_convertTextureGuard;
	s_convertTextureGuard.Lock();

	zERR_ASSERT(srcTexPath);
	zERROR_ID searchFileRes = srcTexPath->SearchFile(srcFileName, zoptions->GetDirString(DIR_TEX));

	if (searchFileRes!=zERR_NONE) {
		delete srcTexPath; srcTexPath=0;
		funcResult	= FALSE;
	} else 
	{
		srcFileName = srcTexPath->GetDir();
		
		// noMip
		noMipMap			= (srcFileName.Search("NOMIP")!=-1);

		//
		detailTextureMode	= (srcFileName.Search("\\_DETAIL")!=-1);

		// minimum bpp
		if (srcFileName.Search("8BIT")!=-1)		desiredBPP = 8;  else
		if (srcFileName.Search("16BIT")!=-1)	desiredBPP = 16; else
		if (srcFileName.Search("32BIT")!=-1)	desiredBPP = 32;			// (seems broken)

		// refSize
		if (srcFileName.Search("\\4")!=-1)		refSize = 4  ; else
		if (srcFileName.Search("\\8")!=-1)		refSize = 8  ; else
		if (srcFileName.Search("\\16")!=-1)		refSize = 16 ; else
		if (srcFileName.Search("\\32")!=-1)		refSize = 32 ; else
		if (srcFileName.Search("\\64")!=-1)		refSize = 64 ; else
		if (srcFileName.Search("\\128")!=-1)	refSize = 128; else
		if (srcFileName.Search("\\256")!=-1)	refSize = 256; else
		if (srcFileName.Search("\\512")!=-1)	refSize = 512; else 
		if (srcFileName.Search("\\1024")!=-1)	refSize = 1024;else 
		if (srcFileName.Search("\\2048")!=-1)	refSize = 2048; 

		// Texture Source laden
		zCTextureConvert *texSource = zrenderer->CreateTextureConvert();
		if ((!texSource) || (!texSource->LoadFromFileFormat(srcTexPath->GetFullPath())))	
		{
			delete srcTexPath;
			delete texSource;
			funcResult = FALSE;
		} else {
			delete srcTexPath; srcTexPath=0;

			//
			zPATH	texPath		(texFileName);
			zSTRING resFileName	= texPath.GetFilename();

			// Ziel TextureInfo vorbereiten
			zCTextureConvert *texConWork		= 0;
			zCTextureInfo srcTexInfo			= texSource->GetTextureInfo();
			zCTextureInfo dstTexInfo			= srcTexInfo;
			zCTextureConvert::CorrectPow2		(dstTexInfo.sizeX, dstTexInfo.sizeY);
			zCTextureConvert::CorrectAspectRatio(dstTexInfo.sizeX, dstTexInfo.sizeY); 
			dstTexInfo.numMipMap				= noMipMap ? 1 : zCTextureConvert::CalcNumMipMaps (srcTexInfo.sizeX, srcTexInfo.sizeY); 
			dstTexInfo.refSizeX					= dstTexInfo.sizeX;
			dstTexInfo.refSizeY					= dstTexInfo.sizeY;

			// refSize X/Y berechnen
			if (refSize>0)
			while (dstTexInfo.refSizeX>4 && dstTexInfo.refSizeY>4)
			{
				int max = zMax (dstTexInfo.refSizeX, dstTexInfo.refSizeY);
				if (max<=refSize)	break;
				dstTexInfo.refSizeX >>=1;
				dstTexInfo.refSizeY >>=1;
			};

			// Sonderregeln:
			// - Texture mit Alpha muessen mind. 16Bit sein
			// - bei kleinen Texturen 16bit statt 8 verwenden, da PAL_8 bei weniger als 
			//   32x32 sogar mehr Mem (&1 StateChange mehr) braucht!
/*
			// 8 bit
			zTRnd_TextureFormat								destTexFormat8	= zRND_TEX_FORMAT_PAL_8;
			if (texSource->HasAlpha())						destTexFormat8	= zRND_TEX_FORMAT_ARGB_4444; else
			if ((dstTexInfo.sizeX*dstTexInfo.sizeY)<=1024)	destTexFormat8	= zRND_TEX_FORMAT_RGB_565;
			dstTexInfo.texFormat				= destTexFormat8;
			texConWork							= zrenderer->CreateTextureConvert();
			zCTextureExchange::CopyContents		(texSource, texConWork);
			texConWork->ConvertTextureFormat	(dstTexInfo);
			texConWork->SaveToFileFormat		(resFileName + "-C.TEX");
			delete texConWork;	texConWork=0;
			
			// 16 bit
			dstTexInfo.texFormat				= texSource->HasAlpha() ? zRND_TEX_FORMAT_ARGB_4444 : zRND_TEX_FORMAT_RGB_565;
			texConWork							= zrenderer->CreateTextureConvert();
			zCTextureExchange::CopyContents		(texSource, texConWork);
			texConWork->ConvertTextureFormat	(dstTexInfo);
			texConWork->SaveToFileFormat		(resFileName + "-C.TEX");
			delete texConWork;	texConWork=0;
*/
			// compressed
			if (desiredBPP==8)		dstTexInfo.texFormat = texSource->HasAlpha() ? zRND_TEX_FORMAT_ARGB_4444 : zRND_TEX_FORMAT_PAL_8;	else
			if (desiredBPP==16)		dstTexInfo.texFormat = texSource->HasAlpha() ? zRND_TEX_FORMAT_ARGB_4444 : zRND_TEX_FORMAT_RGB_565; else
			if (desiredBPP==32)		dstTexInfo.texFormat = texSource->HasAlpha() ? zRND_TEX_FORMAT_RGBA_8888 : zRND_TEX_FORMAT_RGB_888;
			else /*default=DXTC*/	dstTexInfo.texFormat = texSource->HasAlpha() ? zRND_TEX_FORMAT_DXT3		 : zRND_TEX_FORMAT_DXT1; 
			
			texConWork							= zrenderer->CreateTextureConvert();
			zCTextureExchange::CopyContents		(texSource, texConWork);
			texConWork->SetDetailTextureMode	(detailTextureMode);
			texConWork->ConvertTextureFormat	(dstTexInfo);
			texConWork->SaveToFileFormat		(resFileName + "-C.TEX");
			delete texConWork;	texConWork=0;
		
			//
			delete texSource;	texSource=0;
		};
	};
	s_convertTextureGuard.Unlock();

	return funcResult;
};

void zCTexture::ForceConvertAndReloadTexture()
{
	CacheOut		();
	ConvertTexture	(GetName());
	CacheIn			();
};

// ============================================================================================================

zSTRING zCTexture::s_texDesiredBPPSuffix [zTEX_FILE_DESIRED_BPP_COUNT]=
{
	zSTRING("-C"),
	zSTRING("-8"),
	zSTRING("-16"),
	zSTRING("-32")
};

// Dies sind die BPP Formate, wie sie in den .TEX Files abgelegt sind.
zTRnd_TextureFormat zCTexture::s_texDesiredBPPDefault [zTEX_FILE_DESIRED_BPP_COUNT]=
{
	zRND_TEX_FORMAT_DXT1,
	zRND_TEX_FORMAT_PAL_8,
	zRND_TEX_FORMAT_RGB_565,
	zRND_TEX_FORMAT_RGB_888
};

// this list has to be kept in sync with 'texFormatInfoList' in zRenderer.cpp
// gerichteter Graph (zyklisch)
static int texNextBestTexFormat [zRND_TEX_FORMAT_COUNT]=
{
/**/int(zRND_TEX_FORMAT_ABGR_8888),		// zRND_TEX_FORMAT_ARGB_8888,				// 32, alpha 8
	int(zRND_TEX_FORMAT_RGBA_8888),		// zRND_TEX_FORMAT_ABGR_8888,				// 32, alpha 8
	int(zRND_TEX_FORMAT_BGRA_8888),		// zRND_TEX_FORMAT_RGBA_8888,				// 32, alpha 8
	int(zRND_TEX_FORMAT_ARGB_1555),		// zRND_TEX_FORMAT_BGRA_8888,				// 32, alpha 8

/**/int(zRND_TEX_FORMAT_BGR_888),		// zRND_TEX_FORMAT_RGB_888,					// 24
	int(zRND_TEX_FORMAT_PAL_8),			// zRND_TEX_FORMAT_BGR_888,					// 24

/**/int(zRND_TEX_FORMAT_ARGB_1555),		// zRND_TEX_FORMAT_ARGB_4444,				// 16, alpha 4
	int(zRND_TEX_FORMAT_ARGB_8888),		// zRND_TEX_FORMAT_ARGB_1555,				//	 , alpha 1
	int(zRND_TEX_FORMAT_RGB_888),		// zRND_TEX_FORMAT_RGB_565,				

	int(zRND_TEX_FORMAT_RGB_565),		// zRND_TEX_FORMAT_PAL_8,					// 8
	int(-1),							// zRND_TEX_FORMAT_S3TC,					// 4
};

zTRnd_TextureFormat zCTexture::CalcNextBestTexFormat (zTRnd_TextureFormat texFormat) 
{
	// unterstuetzt die Karte das gewuenschte Format ?
	// nicht ? naechstbestes, alternatives Format finden (8=>16, 16=>8, 32=>16, alpha!)
	zBOOL	found			= FALSE;
	int		startFormat		= (int)texFormat;
	int		currentFormat	= startFormat;
	do 
	{
		if (zrenderer->SupportsTextureFormat (zTRnd_TextureFormat(currentFormat)))
		{
			found = TRUE;
			break;
		};
		currentFormat	= texNextBestTexFormat[currentFormat];
	} while ((currentFormat>=0) && (currentFormat!=startFormat));

	// darf niemals passieren !
	if (!found)	zERR_FATAL ("D: no texture format found!");

	return zTRnd_TextureFormat(currentFormat);
};

void zCTexture::CalcDesiredBPP (const zSTRING		*texFileName, 
								zTTexFileDesiredBPP &desiredBPP, 
								zTRnd_TextureFormat &desiredTexFormat, 
								zBOOL				&needsConversion) 
{
	desiredBPP			= s_texRefBPP;		// reference
	desiredTexFormat	= s_texDesiredBPPDefault[s_texRefBPP];
	needsConversion		= FALSE;

	if (s_texScaleBPP==zTEX_SCALE_BPP_S3TC)
	{
		desiredBPP		= zTEX_FILE_DESIRED_BPP_S3TC;
		desiredTexFormat= zRND_TEX_FORMAT_DXT1;
	} else 
	{
		// Hint aus TexName
		if (texFileName)
		{
			if (texFileName->Search ("8BIT" )!=-1)	desiredBPP= zTEX_FILE_DESIRED_BPP_8;	else
			if (texFileName->Search ("16BIT")!=-1)	desiredBPP= zTEX_FILE_DESIRED_BPP_16;	else
			if (texFileName->Search ("32BIT")!=-1)	desiredBPP= zTEX_FILE_DESIRED_BPP_32;
		};

		// 
		if (s_texScaleBPP==zTEX_SCALE_BPP_ONE_HIGHER)	desiredBPP = zTTexFileDesiredBPP(int(desiredBPP)+1);

		// clamp
		if (desiredBPP>=zTEX_FILE_DESIRED_BPP_COUNT)	desiredBPP = zTTexFileDesiredBPP(int(zTEX_FILE_DESIRED_BPP_COUNT)-1);

		// ist das RefFormat vom Renderer bereitgestellt ? nein => naechstbestes Format suchen
		desiredTexFormat	= CalcNextBestTexFormat (s_texDesiredBPPDefault[int(desiredBPP)]);

		// aus einem TexFormat eine 'desiredBPP' und das 'needConversion' Flag ermitteln
		zTRnd_TexFormatInfo texFormatInfo	= zrenderer->GetTexFormatInfo (desiredTexFormat);
		if (texFormatInfo.bytesPerPixel==1)			desiredBPP = zTEX_FILE_DESIRED_BPP_8;	else
		if (texFormatInfo.bytesPerPixel==2)			desiredBPP = zTEX_FILE_DESIRED_BPP_16;	else
		if (texFormatInfo.bytesPerPixel>=3)			desiredBPP = zTEX_FILE_DESIRED_BPP_32;	else
		if (desiredTexFormat==zRND_TEX_FORMAT_DXT1)	desiredBPP = zTEX_FILE_DESIRED_BPP_S3TC;

		// needConversion ?
		needsConversion = TRUE;
		for (int i=0; i<zTEX_FILE_DESIRED_BPP_COUNT; i++)
		{
			if (desiredTexFormat==s_texDesiredBPPDefault[i]) {
				needsConversion = FALSE;
				break;
			};
		};
	};
};

struct zTTexScaleSizeTable {
	int		numHigherThanRef;
	zBOOL	everySecond;
	zBOOL	affectJustOneDim;
};

static zTTexScaleSizeTable s_texScaleSizeTable[zTEX_SCALE_SIZE_COUNT]=
{
	// numHigherThanRef, everySecond, affectJustOneDim
/*	{	-1,	FALSE,	FALSE	},		// FIXME: richtig so ! aber: affectJustOneDim ist leider noch zu langsam!
	{	 0,	FALSE,	TRUE	},
	{	 0,	FALSE,	FALSE	},
	{	+1,	FALSE,	TRUE	},
	{	+1,	FALSE,	FALSE	},
	{	+1,	TRUE,	TRUE	},
	{	+1,	TRUE,	FALSE	},
	{   +8,	FALSE,	FALSE	}
*/
	{	-1,	FALSE,	FALSE	},
	{	 0,	FALSE,	FALSE	},
	{	 0,	FALSE,	FALSE	},
	{	+1,	FALSE,	FALSE	},
	{	+1,	FALSE,	FALSE	},
	{	+1,	TRUE,	FALSE	},
	{	+1,	TRUE,	FALSE	},
	{   +8,	FALSE,	FALSE	}
};

zBOOL zCTexture::LoadAndConvertInternal (zFILE &texFile)
{
	// FIXME: hier muss diese Textur noch markiert werden als eine, bei 'CacheOut' nicht geht!!

	// nur fuer Lightmaps  (nicht fuer Disk-Textures)
	// A) Header Einlesen
	zBOOL res = TRUE;
	zCTextureFileFormatInternal *ffi = zNEW(zCTextureFileFormatInternal);
	if (!ffi->ReadHeader (texFile)) {
		zRELEASE (ffi);
		return FALSE;
	};

	// braucht Lightmap eine Format-Konvertierung ?
	zBOOL				needsConversion = FALSE;
	zTRnd_TextureFormat	desiredTexFormat= CalcNextBestTexFormat (ffi->texInfo.texFormat);
	if (desiredTexFormat!=ffi->texInfo.texFormat)
		needsConversion = TRUE;

	// hier wird berechnet, welche PixelSize die Textur haben soll

	// 's_texScaleSize'
	// - n higher (oder lower)
	// - every second
	// - only Y dim higher
	const	zTTexScaleSizeTable& texScaleParams = s_texScaleSizeTable[s_texScaleSize];
	int		numHigherThanRef					= texScaleParams.numHigherThanRef;
	if (texScaleParams.everySecond)
	{
		static int everySecondCtr=0;
		if (everySecondCtr&1)	numHigherThanRef=0;
		everySecondCtr++;
	};
	if (texScaleParams.affectJustOneDim)	needsConversion	= TRUE;

	// runtime Konvertierung vorbereiten, falls noetig
	zCTextureConvert	*texCon		= 0;
	zCTextureExchange	*texExchange= this;
	if (needsConversion)
	{
		texCon		= zrenderer->CreateTextureConvert();
		texExchange	= texCon;
	};

	// B) Data Einlesen
	// hier dem ffi mitteilen, welche MipMaps oben gecuttet werden sollen!
	ffi->SetLoadMaxPixelSize		(numHigherThanRef, s_texMaxPixelSize);
//	texExchange->Lock				(zTEX_LOCK_WRITE);
	res = ffi->ReadData				(texFile, texExchange, TRUE);		// TRUE = ungelesene Bytes am Ende skippen!
//	texExchange->Unlock				();
	zRELEASE (ffi);
	if (!res)	return FALSE;

	// Konvertierung, falls noetig
	if (needsConversion)
	{
		// hier evtl. die Size Anpassungen
		zerr.Message ("D: converting texture...");
		zCTextureInfo texInfo	= texExchange->GetTextureInfo();
		texInfo.texFormat		= desiredTexFormat;
		if (texScaleParams.affectJustOneDim) 
		{
			texInfo.sizeY>>=1;	if (texInfo.sizeY<1) texInfo.sizeY=1;
			zCTextureConvert::CorrectAspectRatio (texInfo.sizeX, texInfo.sizeY);
			texInfo.numMipMap	= zCTextureConvert::CalcNumMipMaps (texInfo.sizeX, texInfo.sizeY);
		};
		res = res && texCon->ConvertTextureFormat(texInfo);
		res = res && zCTextureExchange::CopyContents(texCon, this);
		delete texCon; texCon=0;
		if (!res)	return FALSE;
	};

	// 
	SetCacheState			(zRES_CACHED_IN);
	this->SetCacheOutLock	(TRUE);

	zRELEASE (ffi);
	return res;
};

zBOOL zCTexture::SaveAndConvertInternal (zFILE &texFile)
{
	// nur fuer Lightmaps  (nicht fuer Disk-Textures)
	// 'offline' code
	zCTextureInfo	texInfo = this->GetTextureInfo();
	zBOOL			res		= TRUE;
	
	// Lightmap ist hier eine 'Renderer-Texture', ist sie in einem gaengigem Format vorhanden ?
	// ja, dann gleich saven, ansonsten erst in dieses konvertieren
	if ((texInfo.texFormat==zRND_TEX_FORMAT_PAL_8	) ||
		(texInfo.texFormat==zRND_TEX_FORMAT_RGB_565	))
	{
		zCTextureFileFormatInternal *ffi = zNEW(zCTextureFileFormatInternal);
		res = ffi->SaveTexture (texFile, this);
		zRELEASE (ffi);
	} else
	{
		// Lightmap auf gaengiges 'default' Format konvertieren: PAL_8 oder RGB_565
		zCTextureInfo	destTexInfo		= texInfo;
		destTexInfo.texFormat			= ((texInfo.sizeX*texInfo.sizeY)<=1024) ? zRND_TEX_FORMAT_RGB_565 : zRND_TEX_FORMAT_PAL_8;
		zCTextureConvert	*texCon		= zrenderer->CreateTextureConvert();
		assert (texCon);
		res = res && zCTextureConvert::CopyContents	(this, texCon);
		res = res && texCon->ConvertTextureFormat	(destTexInfo);
		res = res && texCon->SaveInternal			(texFile);
		delete texCon; texCon=0;
	};
	return res;
};

/*--------------------------------------------------------------------------
	
	zBOOL zCTexture :: CacheInNamed (const zSTRING *texFileName)

 

    09-Nov-00       [PELZER] Bei DXTC-Texturen erfolgt nun im Falle eines Slicings eine Konvertierung ins unkomprimierte Format

--------------------------------------------------------------------------*/

zBOOL zCTexture::CacheInNamed (const zSTRING *texFileName)  
{
	// nur fuer Disk-Textures (nicht fuer Lightmaps)
	// - texFileName!=0	: texture-File im Level wird 'runtime' geladen, evtl .TEX-Files erzeugen
	// - texFile!=0		: LightMap wird aus WorldFile geladen

	zERR_ASSERT (texFileName);

	// Format Konvertierung noetig ? 
	// (von dem Format aus dem File in ein Format, das der Renderer kennt)
	zBOOL				needsConversion = FALSE;
	zTTexFileDesiredBPP	desiredBPP;
	zTRnd_TextureFormat desiredTexFormat;
	CalcDesiredBPP		(texFileName, desiredBPP, desiredTexFormat, needsConversion);

	// Texture 'offline' konvertieren, falls noetig
	zSTRING fileName;
	if (texFileName)
	{
		zPATH path		(texFileName);
		fileName		= path.GetFilename() + s_texDesiredBPPSuffix[desiredBPP] + ".TEX";
		zFILE *file		= zfactory->CreateZFile(zoptions->GetDirString (DIR_COMPILED_TEXTURES) + fileName);
		if (!file->Exists())
		{
			// Nein => Konvertierung
			delete file; file=0;
			if (!ConvertTexture (texFileName))
			{
				// Konvertierung schlug fehl
				if (zTEX_DEFAULT_TEXTURE_FILE!=texFileName)
				{
					if (!s_useDefaultTex) {
						return FALSE;
					} else {
						zERR_WARNING ("D: Texture not found '"+*texFileName+"', using default-texture");
						return CacheInNamed (&zTEX_DEFAULT_TEXTURE_FILE);
					};
				};
				zERR_FATAL ("D: Default Texture '"+zTEX_DEFAULT_TEXTURE_FILE+"' not found!");
				return FALSE;
			} else {
				// Konvertierung gelang
				return CacheInNamed (texFileName);
			};
		};
		delete file; file=0;
	};

	// hier wird berechnet, welche PixelSize die Textur haben soll

	// 's_texScaleSize'
	// - n higher (oder lower)
	// - every second
	// - only Y dim higher
//isTextureTile = FALSE;
//needsConversion=TRUE;

	zTTexScaleSize	texScaleSize = s_texScaleSize; 
	int				texPixelSize = s_texMaxPixelSize;
	if (isTextureTile) {
		// Wenn die Texture als Tile benutzt werden soll, muss sie auf jeden Fall erst einmal
		// in ein TextureConvert Objekt geladen werden. Eine Begrenzung der Texture-Dims auf 
		// Renderer-Caps hin ist an dieser Stelle nicht erwuenscht, die Textur wird spaeter noch
		// 'geslicet'.
		needsConversion			= TRUE;
		texScaleSize			= zTTexScaleSize(int(zTEX_SCALE_SIZE_COUNT)-1);
//FIXME
		texPixelSize			= 2048;		// beliebig..
	};

	const	zTTexScaleSizeTable& texScaleParams = s_texScaleSizeTable[texScaleSize];
	int		numHigherThanRef					= texScaleParams.numHigherThanRef;
	if (texScaleParams.everySecond)
	{
		static int everySecondCtr=0;
		if (everySecondCtr&1)	numHigherThanRef=0;
		everySecondCtr++;
	};
	if (texScaleParams.affectJustOneDim)	needsConversion	= TRUE;

	// runtime Konvertierung vorbereiten, falls noetig
	zCTextureConvert	*texCon		= 0;
	zCTextureExchange	*texExchange= this;
	if (needsConversion)
	{
		texCon		= zrenderer->CreateTextureConvert();
		texExchange	= texCon;
	};

	// Laden
	// hier dem ffi mitteilen, welche MipMaps oben gecuttet werden sollen!
	{
		zBOOL showSpyMessages			= FALSE;
		zCTextureFileFormatInternal *ffi= zNEW(zCTextureFileFormatInternal);
		ffi->SetLoadMaxPixelSize		(numHigherThanRef, texPixelSize);
		ffi->SetShowSpyMessages			(showSpyMessages);
		zBOOL res = ffi->LoadTexture	(fileName, texExchange);
		ffi->Release(); ffi=0;
		if (!res) return FALSE;		// FIXME: hier ein potent. MemLeak durch fruehes return

		// das desiredTexFormat exakt korrigieren (auch wg. alpha)
		desiredTexFormat				= CalcNextBestTexFormat (texExchange->GetTextureInfo().texFormat);
	};

	// Konvertierung, falls noetig
	if (needsConversion)
	{
		zBOOL res				= TRUE;
		zCTextureInfo texInfo	= texExchange->GetTextureInfo();
		texInfo.texFormat		= desiredTexFormat;
		if (texScaleParams.affectJustOneDim) 
		{
			texInfo.sizeY>>=1;	if (texInfo.sizeY<1) texInfo.sizeY=1;
			zCTextureConvert::CorrectAspectRatio (texInfo.sizeX, texInfo.sizeY);
			texInfo.numMipMap	= zCTextureConvert::CalcNumMipMaps (texInfo.sizeX, texInfo.sizeY);
		};

		//
		if (isTextureTile)
		{
			zCTextureConvert::CorrectPow2		 (texInfo.sizeX, texInfo.sizeY);
			zCTextureConvert::CorrectAspectRatio (texInfo.sizeX, texInfo.sizeY);
			if( (texInfo.sizeX>zrenderer->GetMaxTextureSize())|| //Bei DXTC-Texturen muss im Falle eines Slicings
				(texInfo.sizeY>zrenderer->GetMaxTextureSize()) ) //zusätzlich das Format gewechselt werden [PELZER]
			{
				switch( texInfo.texFormat )
				{
				case	zRND_TEX_FORMAT_DXT1:
						texInfo.texFormat = zRND_TEX_FORMAT_RGB_565;
						break;
				case	zRND_TEX_FORMAT_DXT3:
						texInfo.texFormat = zRND_TEX_FORMAT_ARGB_4444;
						break;
				case	zRND_TEX_FORMAT_DXT2:
				case	zRND_TEX_FORMAT_DXT4:
				case	zRND_TEX_FORMAT_DXT5:
						zerr.Warning( "X: CreateTextureTile: Unsupported DXTC format." );
				}
			}
			res = res && texCon->ConvertTextureFormat	(texInfo);
			res = res && CreateTextureTile				(texCon);
//			res = res && zCTextureExchange::CopyContents(texCon, this);
		} else {
			// hier evtl. die Size Anpassungen
			zerr.Message ("D: converting texture...");
			res = res && texCon->ConvertTextureFormat	(texInfo);
			res = res && zCTextureExchange::CopyContents(texCon, this);
		};
		delete texCon; texCon=0;
		if (!res)	return FALSE;
	};

	// hasAlpha Flag setzen
	hasAlpha = zrenderer->GetTexFormatInfo(GetTextureInfo().texFormat).aSize>0;

	// 
	return TRUE;
};

zBOOL zCTexture::IsTextureTileBaseSlice () const
{
	if (IsTextureTile())
	{
		for (int i=0; i<zTEX_MAX_ANIS; i++)
		{
			if (this->prevAni[i]!=0)	return FALSE;
		};
		return TRUE;
	};
	return FALSE;
};

zBOOL zCTexture::CreateTextureTile (zCTextureExchange *texSource)
{
	// Das Input Texture hat bereits korrekte pow2 und aspectRatio
//	texExchange
	if (zrenderer->GetMaxTextureSize()<=0) return FALSE;

	int numSlicesX, numSlicesY;
	
	numSlicesX	= zMax (1, texSource->GetTextureInfo().sizeX / zrenderer->GetMaxTextureSize());
	numSlicesY	= zMax (1, texSource->GetTextureInfo().sizeY / zrenderer->GetMaxTextureSize());
	if ((numSlicesX==1) && (numSlicesY==1))
	{
		// !NEIN: darf NICHT zurueckgesetzt werden, damit beim erneuten/naechsten CacheIn die Reduzierung auf eine TextureSize Obergrenze NICHT auf Tiles ausgefuehrt wird! kann zurueckgesetzt werden.. kein slicing noetig!
//		this->isTextureTile	= FALSE;								
		return zCTextureExchange::CopyContents(texSource, this);
	};

	const zCTextureInfo& texInfoSource	= texSource->GetTextureInfo();
	int					sliceSizeX		= (numSlicesX>1) ? zrenderer->GetMaxTextureSize() : texInfoSource.sizeX;
	int					sliceSizeY		= (numSlicesY>1) ? zrenderer->GetMaxTextureSize() : texInfoSource.sizeY;
	zREAL				bytesPerPixel	= zrenderer->GetTexFormatInfo(texInfoSource.texFormat).bytesPerPixel;

	zBOOL		result	= TRUE;
	zCTexture	*texSlot= this;
	for (int sliceX=0; sliceX<numSlicesX; sliceX++)
	{
		zCTexture *texDest;
		for (int sliceY=0; sliceY<numSlicesY; sliceY++)
		{
			zBOOL textureAlreadyExisted		= FALSE;
			if ((sliceY==0) && (sliceX==0))
			{
				texDest						= this;
			} else 
			{
				zSTRING newName				= this->GetObjectName()+zSTRING(sliceX)+zSTRING(sliceY); 
				texDest						= zCTexture::SearchName	(newName);
				if (!texDest)
				{
					// Texture-Tile wird das erste mal eingecacht, die einzelnen Texturen der Kette muessen noch erzeugt werden
					texDest					= zrenderer->CreateTexture();
					texDest->SetObjectName	(newName);
				} else
				{
					// Texture-Tile wurde bereits eingecacht, die einzelnen Texturen existieren bereits
					textureAlreadyExisted	= TRUE;
					texDest->CacheIn		(-1);		// safety
				};
			};
			texDest->isTextureTile			= TRUE;		// Kettenmitglied als ein Tile kennzeichnen

			//
			result = result && texDest  ->Lock	(zTEX_LOCK_WRITE);
			result = result && texSource->Lock	(zTEX_LOCK_READ);

			zCTextureInfo texInfoDest	= texInfoSource;
			texInfoDest.numMipMap		= 1;
			texInfoDest.sizeX			= sliceSizeX;
			texInfoDest.sizeY			= sliceSizeY;
			texInfoDest.refSizeX		= texInfoSource.sizeX;
			texInfoDest.refSizeY		= texInfoSource.sizeY;
			texInfoDest.texFormat		= texInfoSource.texFormat;

			// hasAlpha Flag setzen
			texDest->hasAlpha			= zrenderer->GetTexFormatInfo(texInfoDest.texFormat).aSize>0;

			//
			void*	sourcePtr;
			int		sourcePitchXBytes;
			void*	destPtr;
			int		destPitchXBytes;
			result = result && texDest	->SetTextureInfo	(texInfoDest);
			result = result && texDest  ->GetTextureBuffer	(0, destPtr  , destPitchXBytes);
			result = result && texSource->GetTextureBuffer	(0, sourcePtr, sourcePitchXBytes);

			// ggfs. Palette kopieren
			if (texSource->GetPaletteBuffer())
				result = result && texSource->CopyPaletteDataTo(texDest->GetPaletteBuffer());

			//
			if (!result) break;

			//
			int numBytesLine= zFloat2Int (zREAL(texInfoDest.sizeX) * bytesPerPixel);

			// SourcePtr in das Texture hinein 'offseten'
			sourcePtr		= ((zBYTE*)sourcePtr) +
				zFloat2Int(zREAL(sliceX * sliceSizeX) * bytesPerPixel)
				+         (     (sliceY * sliceSizeY) * sourcePitchXBytes);

			for (int y=0; y<sliceSizeY; y++)
			{
				memcpy		(destPtr, sourcePtr, numBytesLine);
				sourcePtr	= ((zBYTE*)sourcePtr) + sourcePitchXBytes;
				destPtr		= ((zBYTE*)destPtr  ) + destPitchXBytes;
			};

			//
			result = result && texSource->Unlock			();
			result = result && texDest  ->Unlock			();		// sorgt selbst fuer das 'cacheIn'
			texDest->SetCacheState (zRES_CACHED_IN);

			// Neu erzeugte Textur mit den anderen Verketten (nur beim ersten CacheIn muss diese Verkettung erzeugt werden)
			if (!textureAlreadyExisted)
			{
				if (sliceY==0) {
					if (this!=texDest) 
						this->AddAniTex (0, texDest);
					texSlot = texDest;
				} else {
					texSlot->AddAniTex (1, texDest);
				};
			};
		};
		texSlot = texDest;
		if (!result) break;
	};
	this->numAniFrames[0]	= numSlicesX;
	this->numAniFrames[1]	= numSlicesY;
	this->isAnimated		= TRUE;

	if (!result)
		zERR_FAULT ("D: zCTexture(::CreateTextureTile): failed!");
	return result;
};

void zCTexture::GetPixelSize (int& xdim, int &ydim)
{
	zCTextureInfo texInfo = GetTextureInfo();
	xdim = texInfo.sizeX;
	ydim = texInfo.sizeY;
};

// ====================================================================================================================

// Textures konvertieren

zBOOL zCTextureFileHandler::HandleFile(const zSTRING& fname, const char* directory, _finddata_t fileinfo)
{		
	zBOOL touched = FALSE;

	if (fname.Search(".TGA")>=0) 
	{				
		// Kompletten Dateinamen bauen
		zSTRING filename = zSTRING(directory) + DIR_SEPARATOR + fname;
		filename.Lower();		

		time_t tga_last_access = fileinfo.time_write;		
	
		// Konvertierte Datei
		_finddata_t	fileinfo3df;
		zSTRING		file3df = filename.PickWord(1,".",".") + "-C.TEX"; 
		
		// Nach konvertierter Datei suchen und ggf. Datum vergleichen
		zoptions->ChangeDir(DIR_COMPILED_TEXTURES);
		
		zFILE::DirectFileAccess(TRUE);
		long handle3df = _findfirst(file3df.ToChar(), &fileinfo3df); 
		zFILE::DirectFileAccess(FALSE); //[EDENFELD] 1.09 : Fehlte (uebel!)

		if (handle3df==-1L || fileinfo3df.time_write < tga_last_access ) 
		{
			// Konvertierung notwendig
			touched = TRUE;
			zCTexture::ConvertTexture (filename);			
		}						
	}
	else if (fname.Search(".PCX")>=0) 
	{
		AddMessage("Attention: PCX-Files must be converted to TGA");
	}
	else 
	{
		zERR_WARNING("B: SDIR: Unknown filetype. Can't handle file "+fname);
	}

	return touched;
};

void zCTexture::ScanConvertTextures(const zSTRING a_strSubDir)
{
	zerr.Message				("D: TEX: Searching texture directory for unconverted textures...");
	zCScanDir dirScanner;

	// Instance des FileHandlers fuer Texturen erzeugen
	zCTextureFileHandler* texFileHandler = zNEW(zCTextureFileHandler);

	// FileHandler registrieren
	dirScanner.RegisterFileHandler(texFileHandler,"TextureConvert");

	// Texturverzeichnis scannen
	if (a_strSubDir.IsEmpty())
		dirScanner.Scan(zoptions->GetDirString(DIR_TEX));
	else  
		dirScanner.Scan(zoptions->GetDirString(DIR_TEX) + a_strSubDir + "\\");

	// Fertig:
	delete texFileHandler;
	texFileHandler = 0;
}

// ============================================================================================================

zBOOL zCTextureExchange::CopyContents (zCTextureExchange *srcTex, zCTextureExchange *dstTex)
{
	// 
	zBOOL result = TRUE;
	result	= dstTex->Lock	(zTEX_LOCK_WRITE)	&& result;
	result	= srcTex->Lock	(zTEX_LOCK_READ)	&& result;

	//
	result				= dstTex->SetTextureInfo	(srcTex->GetTextureInfo())		&& result;
//	dstTex->averageColor= srcTex->GetAverageColor	();
//	dstTex->hasAlpha	= srcTex->HasAlpha			();

	srcTex->CopyPaletteDataTo	(dstTex->GetPaletteBuffer());		// falls vorhanden
	for (int i=0; i<srcTex->GetTextureInfo().numMipMap; i++) 
	{
		void*	srcBuffer;
		int		srcPitch;
		result	= dstTex->GetTextureBuffer	(i, srcBuffer, srcPitch) && result;
		if (!result)	break;
		result	= srcTex->CopyTextureDataTo	(i, srcBuffer, srcPitch) && result;
	};

	//
	result = srcTex->Unlock () && result;
	result = dstTex->Unlock () && result;

	//
	return result;
};

int zCTextureExchange::GetMemSizeBytes ()
{
//	assert(zrenderer);
	if (!zrenderer) return 0;

	zCTextureInfo texInfo = GetTextureInfo();
	float size		= 0;
	int dimX		= texInfo.sizeX;
	int dimY		= texInfo.sizeY;
	int numMipMap	= texInfo.numMipMap;
	while (numMipMap>0)
	{
		size += zREAL(dimX*dimY) * zrenderer->GetTexFormatInfo(texInfo.texFormat).bytesPerPixel;
		dimX>>=1;	if (dimX<1)	dimX=1;
		dimY>>=1;	if (dimY<1)	dimY=1;
		numMipMap--;
	};
	if (texInfo.texFormat==zRND_TEX_FORMAT_PAL_8)
		size += zTEX_PAL_SIZE_BYTES;
	return zFloat2Int(size);
};

zVEC4 zCTextureExchange::GetRGBAAtTexel (zREAL xpos, zREAL ypos) 
{
	const zCTextureInfo &texInfo = this->GetTextureInfo();
	zClamp (xpos, 0.0F, zREAL(texInfo.sizeX-1));
	zClamp (ypos, 0.0F, zREAL(texInfo.sizeY-1));
	int		bytesPerPixel	= zFloat2Int(zrenderer->GetTexFormatInfo (texInfo.texFormat).bytesPerPixel);

	//
	int		x0	= zFloat2IntFloor (xpos);
	int		y0	= zFloat2IntFloor (ypos);
	zREAL	dx	= xpos-x0;
	zREAL	dy	= ypos-y0;
	zREAL	omdx= 1-dx;
	zREAL	omdy= 1-dy;

	//
	if (!this->Lock		(zTEX_LOCK_READ))
	{
		zERR_WARNING("C: zCTextureExchange::GetRGBAAtTexel(): Texture could not be locked");
		return zVEC4(0,0,0,255);
	};

	void*			texBuffer;
	int				texPitchXBytes;
	zBOOL result = this->GetTextureBuffer(0, texBuffer, texPitchXBytes);
	zVEC4 resCol;
	if (result && texBuffer) {
		zBYTE			*ptr		= (zBYTE*)texBuffer + (y0*texPitchXBytes) + x0*bytesPerPixel;
		zTTexPalette	*palPtr		= (zTTexPalette*)this->GetPaletteBuffer();
		
		//
		zBYTE *deltaXPlus1	= (zBYTE*) ((x0+1<texInfo.sizeX) ? bytesPerPixel	: 0);
		zBYTE *deltaYPlus1	= (zBYTE*) ((y0+1<texInfo.sizeY) ? texPitchXBytes	: 0);

		resCol	=	omdx*omdy	* GetRGBAAtPtr (ptr				 , palPtr, texInfo.texFormat) + 
					omdx*dy		* GetRGBAAtPtr ((zBYTE*)((zDWORD)ptr + (zDWORD)deltaYPlus1), palPtr, texInfo.texFormat) +
					dx*omdy		* GetRGBAAtPtr ((zBYTE*)((zDWORD)ptr + (zDWORD)deltaXPlus1), palPtr, texInfo.texFormat) + 
					dx*dy		* GetRGBAAtPtr ((zBYTE*)((zDWORD)ptr + (zDWORD)deltaXPlus1 + (zDWORD)deltaYPlus1), palPtr, texInfo.texFormat);   
	} else {
		resCol	= zVEC4(255,0,0,255);
	};
	//
	this->Unlock	();

	return resCol;
};

zVEC4 zCTextureExchange::GetRGBAAtPtr (zBYTE* ptr, zTTexPalette* palPtr, const zTRnd_TextureFormat texFormat) 
{
	//
	switch (texFormat) {
	case zRND_TEX_FORMAT_ARGB_8888	:	return zVEC4(ptr[1], ptr[2], ptr[3], ptr[0]);		break;
	case zRND_TEX_FORMAT_ABGR_8888	:	return zVEC4(ptr[1], ptr[2], ptr[3], ptr[0]);		break;
	case zRND_TEX_FORMAT_RGBA_8888	:	return zVEC4(ptr[0], ptr[1], ptr[2], ptr[3]);		break;
	case zRND_TEX_FORMAT_BGRA_8888	:	return zVEC4(ptr[2], ptr[1], ptr[0], ptr[3]);		break;
	case zRND_TEX_FORMAT_RGB_888	:	return zVEC4(ptr[0], ptr[1], ptr[2], 255);		break;
	case zRND_TEX_FORMAT_BGR_888	:	return zVEC4(ptr[2], ptr[1], ptr[0], 255);		break;

	case zRND_TEX_FORMAT_ARGB_4444	:{	zWORD a = *(zWORD*)ptr;
										return zVEC4(	((a>>8 )&15)<<4	,
														((a>>4 )&15)<<4	, 
														((a>>0 )&15)<<4,		
														((a>>12)&15)<<4);				break; };
	case zRND_TEX_FORMAT_ARGB_1555	:{	zWORD a = *(zWORD*)ptr;
										return zVEC4(	((a>>10)&31)<<3	,
														((a>>5 )&31)<<3	, 
														((a>>0 )&31)<<3,		
														((a>>15)&31)*0xFF);				break; };
	case zRND_TEX_FORMAT_RGB_565	:{	zWORD a = *(zWORD*)ptr;
										return zVEC4(	((a>>11)&31)<<3	,
														((a>>5 )&63)<<2	, 
														((a>>0 )&31)<<3,		
														 255);							break; };
	case zRND_TEX_FORMAT_PAL_8		:{	return zVEC4(	palPtr[*ptr].r,
														palPtr[*ptr].g,
														palPtr[*ptr].b,		
														 255);							break; };
//	default: //DXTC-Texturen können hier nicht (so schnell) ausgewertet werden
//		zERR_WARNING ("D: (zCTextureEchange::GetRGBAAtTexel) cannot read pixel from this format..");
	};
	return zVEC4(0,0,0,255);
};

// ============================================================================================================

//                    zCLightMap

// ============================================================================================================

/* ----------------------------------------------------------------------
    zCLASS_DEFINITION (zCLightMap,..)

	22.12.2000	[HILDEBRANDT]	
                Flag zCLASS_FLAG_SHARED_OBJECTS entfernt, war nicht noetig.
   ---------------------------------------------------------------------- */

zCLASS_DEFINITION	(zCLightMap, zCObject, 0, 0)

/* ----------------------------------------------------------------------
    zCLightMap::zCLightMap() und ~zCLightMap()	

	29.11.2000	[Moos]	
                Erzeugt
   ---------------------------------------------------------------------- */

zCLightMap::zCLightMap():tex(NULL){}

zCLightMap::~zCLightMap(){
    zRELEASE(tex);
}

/* ----------------------------------------------------------------------
	
    zCLightMap::SetTexture()	

	29.11.2000	[Moos]	
                erzeugt

   ---------------------------------------------------------------------- */

void zCLightMap::SetTexture(zCTexture *t){
    if (t==tex) return;

    zRELEASE(tex);
    tex = t;
    if (tex) tex->AddRef();
}

/* ----------------------------------------------------------------------
	
    zCLightMap::CalcLightmapOriginUpRight()	

	29.11.2000	[Moos]	
                von zCTexture hierher verlegt

   ---------------------------------------------------------------------- */


void zCLightMap::CalcLightmapOriginUpRight (const zVEC3& origin, const zVEC3& up, const zVEC3& right) {
	const zPOINT3&	a				= right;
	const zPOINT3&	b				= up;
	zREAL			bb				= (b*b);
	zREAL			div				= zREAL(1) / ((a*a)*(bb));
					lightmapUVRight	= (bb*div)*a;
					lightmapUVUp	= b / bb;

	lightmapOrigin = origin;
/*	q		= poly->clipVert[i]->position - actTexture->lightmapOrigin;
	s		= tc1*q;
	t		= tc4*q;	*/
};


// ============================================================================================================
// ============================================================================================================

/*

	"REFERENCE" = Voodoo2
	- 4MB Texture Speicher
	- 256x256 max. Texture-Groesse
	- aspect-Ratio max. 1:8
	- BPP, Size fuer diese Plattform legen die Grafiker mit ihren Zuweisungen zu Texture-Directories fest
	  (idR PAL8, manchmal 16bit)

	Minimum Capabilities:
	- mind. 2 Texture Formate aus zTRnd_TextureFormats (mit/ohna alpha)
	- 

	zCTextureFileFormat kann:
	- Texture Files im bestimmten Format lesen/schreiben und ein zCTextureConvert mit Daten fuellen, in einem Format, 
	  dass das zCTextureConvert kennt

	zCTextureConvert kann:
	- Color Conversion
	- Size Conversion		(auf voellig beliebige Dimensionen, nicht nur pow2)
	- MipMap Generierung
	- Palette Generierung

    - wird vom Renderer erzeugt
	- zCTextureFileFormat benutzen, um Source-Daten zu lesen/schreiben
	- ein optimiertes internes Format laden und speichern (auch ueber zCTextureFileFormat)
	- per Flag kann man das autom. Speichern des internen Formates verbieten 
	  => es werden nur Source-Files gelesen und on-the-fly kovnertiert
	- kann intern alle zTRnd_TextureFormat Formate ineinander konvertieren
	- bekommt Daten von:
		- zCTextureFileFormat
		- zCTextureFileFormat: aus internem Format 
		- ein Benutzer kann Daten im vorher angekuendigtem Format drirekt hineingeschrieben

	- die 'Reference-Konfiguration' einer Textur setzt sich zusammen aus zCTextureConvert bekannten Werten
	  (interne Konstanten fuer Tex-Mem Groesse, BPP, etc.) und Abweichungen davon, die aus dem Pfad-Namen
	  der Textur ableitbar sind. Beim Konvertieren in das interne FileFormat wird diese Information in das
	  interne Fileformat abglegt und ist somit beim Laden auch wieder verfuegbar.

    zCTextureFileFormatInternal kann:
	- eigenes optimiertes internes Format laden und speichern (alle Formate, das zCTextureConvert auch kennt)
	- Paletten so verwalten, dass verschiedene Texturen dieselben Paletten benutzen (derselbe Ptr auf Speicher)
	  (macht Renderer/Hardware schneller)
	- Versions-Kontrolle:
		- konvertiert ein File im internen Format neu, falls dessen Versions-Nummer nicht mehr aktuell ist
		- konvertiert ein File im internen Format neu, falls das dazugehoerige Source-File vorhanden ist & neuer ist
		  (Verhalten per Flag ausschaltbar, da langsam)

	- im internen Format sind gespeichert:
		- "reference"-Werte: size, bpp, Paletten-Name (kann von TexInfo abweichen, ergibt sich aus den Directory-Namen)
		- TexInfo
		- alle mipmaps

	Renderer-Textur
	- Die zCTextureConvert Klasse und der Renderer sind im gewissen Bereich aufeinander abgestimmt
	  (will heissen: Die Renderer Textur muss mind. 1 Format des zCTextureConvert kennen und umgekehrt).
    - Renderer-Tex Formate sind ein Subset der zCTextureConvert-Formate (i.d.R.)
	- falls eine Renderer-Textur intern ein nicht-zCTTextureFile-Format benutzt, so muss es das interne Format in ein
	  zCTTextureFile-Format konvertieren koennen

  Texturen geben durch die Namen der Verzeichnisse, in denen sie sich befinden Hints:
  ("NOMIP" im VZ-Namen koennte die MipMap-Generierung verhindern => Fonts, Desktop-Grafiken)
  - Beispiele:
	- DATA
		- TEXTURES
			- LEVEL
				- OLDCAMP
					- 064
						- 8BPP
							- PAL_OC_WALL
						- 16BPP
					- 128
						- 8BPP
						- 16BPP
					- 256
						- 8BPP
							- PAL_OC_WALL
						- 16BPP
*/

// Header einlesen
// (size, numMipMap, format, interne File-Vers, Source-File-Name/Date(.TGA))
// - falls gewuenschtes BPP-Format nicht unterstuetzt wird, dann entweder Daten aus diesem File umkonvertieren, 
//   oder ein anderes passenderes File laden (das entweder die gewuenschte BPP hat, oder leichter konvertiert werden kann)
// - falls gewuenschte texSize > texMaxSize ist, dann texSize anpassen

// texInfo setzen

// Body
// Falls die Daten im File nicht im gewuenschten Format (size/bpp) vorliegen:
// - a) Daten laden, konvertieren
// sonst:
// - b) Daten nicht lokal laden & zwischenbuffern

// LoadPaletteData() / LoadTextureData(): 
// bringt die Body-Daten an die angegeb. Speicher-Positionen (entweder a) aus internem Buffer oder b) direkt von der Platte)


/*	// liegt Textur in einem BPP Format vor, das der Renderer unterstützt ?
if (!zrenderer->SupportsTextureFormat (texConvert->GetTextureFormat()) 
{
	// Nein => on-the-fly Konvertierung
	int texBPP	= zRND_TEX_FORMAT_COUNT;
	int numTry	= 0;
	do
	{
		texBPP	= (texBPP + 1) % zRND_TEX_FORMAT_COUNT;
		if (zrenderer->SupportsTextureFormat (zTRnd_TextureFormat(texBPP)))	break;
		numTry++;
	} while (numTry<zRND_TEX_FORMAT_COUNT);
	if (numTry>=zRND_TEX_FORMAT_COUNT)	goto leave;

	// alternatives Format gefunden
	texConvert->ForceTextureFormat (texBPP);
};
*/

/*

  Potentielle Probleme:
  - Lightmaps:
	- Liegen auf Disk nur in 1 MipMap vor. Falls diese groesser als die durch den Renderer erlaubte Groesser,
	  wird diese bisher nicht runterkonvertiert. I.A. wird halt eine kleiner MipMap genommen, ist hier aber nicht
	  moeglich.
	- Bei geladenem Level und Device-Wechsel werden derzeit alle Texturen ausge-cacht, danach wieder CacheIn().
	  Problem: Lightmaps koennen weder ein- noch ausgecacht werden. Allerdings koennen die Surfaces der Texturen aber
	  nicht ueber den Device-Wechsel hinweg gerettet werden ... uuuhh.

*/

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 