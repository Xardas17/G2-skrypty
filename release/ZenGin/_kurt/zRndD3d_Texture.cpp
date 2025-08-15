

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_Texture.cpp
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
					- SupportsTextureFormat() ohne Hardware-Test

*********************************************************************************
- comments:
				28.03.00	Changed DirectX-Error handling (DXTryWarning used)
				14.04.00	Implemented a slotsystem for caching unused surfaces
							Added support for DXTC textures (see zRndD3D_SurfaceCache.h/.cpp)
				30.06.00	Added RescueTexture(..) and RebuildTexture(..)
  
TODO:

*********************************************************************************/



#include "zcore.h"
#include "zRndD3D_Texture.h"



enum zTDXTCSupport {	zRND_DXTC_ALWAYS_FALSE,				//Bewirkt die Dekomprimierung in der TextureConcert-Klasse
						zRND_DXTC_ALWAYS_TRUE,				//Bewirkt, dass der Renderer immer die komprimierten Texturen 
															//entgegen nimmt (und gegebenfalls SW-dekomrimiert)
						zRND_DXTC_ALWAYS_TRUE_DECOMPRESS,	//Bewirkt, dass der Renderer immer die komprimierten Texturen
															//entgegen nimmt und diese immer SW-dekomprimiert
						zRND_DXTC_ALWAYS_REAL				//Bewirkt, dass der Renderer komprimierte Texturen nur bei
															//Unterstützung durch die Hardware entgegen nimmt, ansonsten
															//erfolgt die Dekomprimierung in der TextureConvert-Klasse 
					}; 

//zTDXTCSupport DXTCSupportSwitch = zRND_DXTC_ALWAYS_REAL;
//zTDXTCSupport DXTCSupportSwitch = zRND_DXTC_ALWAYS_FALSE;
//zTDXTCSupport DXTCSupportSwitch = zRND_DXTC_ALWAYS_TRUE_DECOMPRESS;


zTDXTCSupport DXTCSupportSwitch = zRND_DXTC_ALWAYS_TRUE; //Dies wird die endgültige Einstellung sein ...






/*--------------------------------------------------------------------------
	
	zCTexture* zCRnd_D3D :: CreateTexture()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCTexture* zCRnd_D3D :: CreateTexture() 
{
	//Erzeugung eines 
	return zNEW( zCTex_D3D );
}


/*--------------------------------------------------------------------------
	
	int zCRnd_D3D :: GetTotalTextureMem()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int zCRnd_D3D :: GetTotalTextureMem()
{ 
	//Abfrage der Grösse des zur Verfügung stehenden Texturspeichers auf der Grafikkarte
	return xd3d_Capabilities.vidmemfree; 
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SupportsTextureFormat( const zTRnd_TextureFormat texFormat ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SupportsTextureFormat( const zTRnd_TextureFormat texFormat ) 
{ 
	//Abfrage der vom Renderer unterstützten Texturformate
	switch( texFormat )
	{
	case	zRND_TEX_FORMAT_RGB_565:
	case	zRND_TEX_FORMAT_ARGB_4444:	
	case	zRND_TEX_FORMAT_ARGB_1555:
			return TRUE;	
	case	zRND_TEX_FORMAT_DXT1:
			switch( DXTCSupportSwitch )
			{
			case	zRND_DXTC_ALWAYS_TRUE:
					return TRUE;
			case	zRND_DXTC_ALWAYS_FALSE:
					return FALSE;
			case	zRND_DXTC_ALWAYS_TRUE_DECOMPRESS:
					supportDXTC[0] = FALSE;
					return TRUE;
			default:
					return supportDXTC[0];
			}
	case	zRND_TEX_FORMAT_DXT3:
			switch( DXTCSupportSwitch )
			{
			case	zRND_DXTC_ALWAYS_TRUE:
					return TRUE;
			case	zRND_DXTC_ALWAYS_FALSE:
					return FALSE;
			case	zRND_DXTC_ALWAYS_TRUE_DECOMPRESS:
					supportDXTC[2] = FALSE;
					return TRUE;
			default:
					return supportDXTC[2];
			}
	default:
			return FALSE;
	}
}



/*--------------------------------------------------------------------------
	
	zBOOL zCRnd_D3D :: SupportsTextureFormat( const zTRnd_TextureFormat texFormat ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCRnd_D3D :: SupportsTextureFormatHardware( const zTRnd_TextureFormat texFormat ) 
{ 
	//Abfrage der vom Renderer unterstützten Texturformate
	switch( texFormat )
	{
	case	zRND_TEX_FORMAT_RGB_565:
	case	zRND_TEX_FORMAT_ARGB_4444:	
	case	zRND_TEX_FORMAT_ARGB_1555:
			return TRUE;	
	case	zRND_TEX_FORMAT_DXT1:
			return supportDXTC[0];
	case	zRND_TEX_FORMAT_DXT3:
			return supportDXTC[2];
	default:
			return FALSE;
	}
}



/*--------------------------------------------------------------------------
	
	int zCRnd_D3D :: GetMaxTextureSize()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
int zCRnd_D3D :: GetMaxTextureSize() 
{ 
	//Rückmeldung der maximalen Texturgrösse (Breite bzw. Höhe)
	return xd3d_Capabilities.maxtexsize;	
}



/*--------------------------------------------------------------------------
	
	zCTextureConvert* zCRnd_D3D :: CreateTextureConvert()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCTextureConvert* zCRnd_D3D :: CreateTextureConvert()
{
	//Erzeugung eines neuen Objekts der Texture-Convert-Klasse
	return zNEW( zCTexConGeneric );
}



/*--------------------------------------------------------------------------
	
	zCTex_D3D :: zCTex_D3D() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCTex_D3D :: zCTex_D3D() 
{	
	//Notwendige Initialisierungen
	xtex_textureflag			= 0xDEADFACE;
	xtex_lastFrameUsed			= 0;
	xtex_locked					= FALSE;
	xtex_internalnumber			= 0;
	xtex_pPalettePtr			= 0L;
	xtex_pddpal					= 0L; 
	xtex_palsupport				= zCRnd_D3D::xd3d_palsupp;
	xtex_texinfo.sizeX			= 0;
	xtex_texinfo.sizeY			= 0;
	xtex_texinfo.refSizeX		= 0;
	xtex_texinfo.refSizeY		= 0;
	xtex_texinfo.numMipMap		= 0;	
	xtex_miplocked				= 0;
	xtex_alphaTex				= FALSE;
	xtex_buffer					= NULL;
	xtex_decompress				= FALSE;
	for( int i = 0; i<12; i++ )
	{
		xtex_pddtex[i] = NULL;
		xtex_pddtemporarytex[i] = NULL;
	}
}



/*--------------------------------------------------------------------------
	
	zCTex_D3D :: ~zCTex_D3D() 

    14-Aug-00       [PELZER]
    17-Nov-00       [HILDEBRANDT]
					Aus einem 'zCResource::ReleaseData()' ein 'zCResource::CacheOut()' 
					gemacht. Ist wichtig, damit der ResourceManager seine Referenz auf die Res freigibt!
--------------------------------------------------------------------------*/

zCTex_D3D :: ~zCTex_D3D() 
{	
	// Bereinigung des Objekts
	this->CacheOut();
} 



/*--------------------------------------------------------------------------
	
	void zCTex_D3D :: ReleaseData() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCTex_D3D :: ReleaseData() 
{	
	//Entfernung bzw. Einlagerung der Surface in das Slotsystem und Austragung aus der Registrierungsliste
	if( xtex_textureflag!=0xDEADFACE )
	{
		zERR_WARNING("X: zCTex_D3D::ReleaseData: uninitialized pointer called" );
		return;
	}
	RemoveTexture();
	tex[xtex_internalnumber].mode	= 0;
	xtex_internalnumber				= -1;
}


/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: Lock( int m )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: Lock( int m )
{
	//Lock des Texture-Objekts
	if( GetCacheState()==zRES_CACHED_OUT )
		CacheIn(-1);
	xtex_locked = TRUE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: Unlock()

 

    06-Sep-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: Unlock()
{
	//Unlock des Texture-Objekts inklusive Sonderbehandlung komprimierter Texturen bei 
	//fehlender Unterstützung durch die Hardware
	for( int i = 0; i<12; i++ )
	{
		if( xtex_miplocked&(0x0001<<i) )
		{
			if( xtex_decompress )
				xtex_pddtemporarytex[i]->Unlock( NULL );
			else
				xtex_pddtex[i]->Unlock( NULL );
			xtex_miplocked &= 0xffff-(0x0001<<i); //Hier wird auf FALSE gesetzt
		}
		else
			break;
	}
	if( xtex_decompress )
	{
		//Erzeuge die Surfaces für die dekomprimierten Texturen
		XTEX_BuildSurfaces( TRUE );

		//Führe die Dekompressionsblits für die einzelnen Surfaces durch
		for( int j = 0; j<i; j++ )
		{
			xtex_pddtex[j]->Blt( NULL, xtex_pddtemporarytex[j], NULL, DDBLT_WAIT, NULL );
			if( !global_DXTCCache.Unlock( xtex_slotindex.width-j, xtex_slotindex.height-j, 
					xtex_texinfo.texFormat, xtex_pddtemporarytex[j] ) )
				zERR_MESSAGE(5,0, "X: Illegal unlock in DXTCCache ..." );
			xtex_pddtemporarytex[j] = NULL;
		}

		//Ändere in der Texture-Info das Pixelformat
		switch( xtex_texinfo.texFormat )
		{	
		case	zRND_TEX_FORMAT_DXT1:
				if( xtex_alphaTex )
					xtex_texinfo.texFormat = zRND_TEX_FORMAT_ARGB_1555;
				else
					xtex_texinfo.texFormat = zRND_TEX_FORMAT_RGB_565;
				break;
		case	zRND_TEX_FORMAT_DXT3:
				xtex_texinfo.texFormat = zRND_TEX_FORMAT_ARGB_4444;
				break;
		}
	}
	//Vermerke, dass die Textur nun eingecacht ist
	xtex_locked = FALSE;
	SetCacheState( zRES_CACHED_IN );
	xtex_decompress = FALSE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zCTextureInfo zCTex_D3D :: GetTextureInfo()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCTextureInfo zCTex_D3D :: GetTextureInfo()	
{ 
	//Rückgabe des Texture-Info-Objekts
	if( GetCacheState()==zRES_CACHED_OUT )
		CacheIn(-1);
	return xtex_texinfo; 
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: SetTextureInfo( const zCTextureInfo& texInfo )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: SetTextureInfo( const zCTextureInfo& texInfo ) 	
{	
	//Setzen des Texture-Info-Objekts
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::SetTextureInfo: uninitialized pointer called" );
		return FALSE;
	}
	xtex_texinfo = texInfo;	
	if( xtex_texinfo.sizeX==0||xtex_texinfo.sizeY==0 )
	{	
		zERR_WARNING("X: CacheIn: WARNING: texture has no size....abort action!!!" );
		return FALSE;
	}

	return TRUE; 
}



/*--------------------------------------------------------------------------
	
	void zCTex_D3D :: GetPixelSize( int& xdim, int &ydim )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCTex_D3D :: GetPixelSize( int& xdim, int &ydim )	
{	
	//Rückgabe der Texturgrösse (Breite und Höhe)
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::GetPixelSize: uninitialized pointer called" );
		return;
	}
	xdim = xtex_texinfo.sizeX;		
	ydim = xtex_texinfo.sizeY;	
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: CopyTextureDataTo( int mipMapNr, void* destBuffer, int destPitchXBytes )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: CopyTextureDataTo( int mipMapNr, void* destBuffer, int destPitchXBytes )
{		
	//Kopieren des Texturinhalts (Mipmap-Surface) in einen vorgegebenen Buffer
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::CopyTextureDataTo: uninitialized pointer called" );
		return FALSE;
	}
	if( !xtex_locked )
	{
		zERR_WARNING( "X: CopyTextureDataTo: Texture is not locked ---> No buffer pointer returned !" );
		return FALSE;
	}
	if( !xtex_pddtex[0] )
	{
		zERR_WARNING( "X: CopyTextureDataTo: No DirectX Surfaces are connected with this texture !" );
		return FALSE;
	}
	DDSURFACEDESC2 ddsd;
	ZeroMemory( &ddsd, sizeof( ddsd ) );
	ddsd.dwSize = sizeof( DDSURFACEDESC2 );
	while( zCRnd_D3D::xd3d_dd7inuse )
	{
		zERR_MESSAGE(5,0, "X: DirectDraw out of sync !" );
		Sleep( 0 );
	}
	zCRnd_D3D::xd3d_dd7inuse = TRUE;
	HRESULT hr;
	if( !DXTryWarning( hr = xtex_pddtex[mipMapNr]->Lock( NULL, &ddsd, DDLOCK_READONLY, NULL ), 
		"X: [TXD3D]CopyTextureDataTo: Can't lock the texture surface !" ) )
	{
		while( hr==DDERR_SURFACEBUSY )
			hr = xtex_pddtex[mipMapNr]->Lock( NULL, &ddsd, DDLOCK_READONLY, NULL );
		if( hr!=D3D_OK )
		{
			zCRnd_D3D::xd3d_dd7inuse = FALSE;
			return FALSE;
		}
		zERR_MESSAGE(5,0, "X: [TXD3D]CopyTextureDataTo: Locked the texture surface !" );
	}
	zCRnd_D3D::xd3d_dd7inuse = FALSE;
	unsigned char *sbuffer = (unsigned char*)ddsd.lpSurface;
	unsigned char *dbuffer = (unsigned char*)destBuffer;
	switch( xtex_texinfo.texFormat )
	{
	case	zRND_TEX_FORMAT_DXT1:
	case	zRND_TEX_FORMAT_DXT3:
			memcpy( dbuffer, sbuffer, ddsd.dwLinearSize );
			break;
	default:
			if( xtex_texinfo.texFormat!=zRND_TEX_FORMAT_PAL_8 )
				for( int h = 0; h<ddsd.dwHeight; h++ )
					memcpy( dbuffer+h*destPitchXBytes, sbuffer+h*ddsd.lPitch, ddsd.dwWidth*2 );
			else
				for( int h = 0; h<ddsd.dwHeight; h++ )
					memcpy( dbuffer+h*destPitchXBytes, sbuffer+h*ddsd.lPitch, ddsd.dwWidth );
	}
	xtex_miplocked |= 0x0001<<mipMapNr; //TRUE

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: CopyPaletteDataTo( void* destBuffer )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: CopyPaletteDataTo( void* destBuffer ) //the source data can be filled in directly from hard disk (if no convers. necessary)
{	
	//Kopieren des Paletteninhalts in einen vorgegebenen Buffer
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::CopyPaletteDataTo: uninitialized pointer called" );
		return FALSE;
	}
	if( (destBuffer==0L)||(xtex_pPalettePtr==0L) ) 
		return FALSE;
	memcpy( destBuffer, xtex_pPalettePtr, 256*3 );

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	void* zCTex_D3D :: GetPaletteBuffer()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void* zCTex_D3D :: GetPaletteBuffer()	
{	
	//Rückgabe des Pointers auf die Palette (8-Bit palettierten Texturen)
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::GetPaletteBuffer: uninitialized pointer called" );
		return 0L;
	}
	if( xtex_texinfo.texFormat==zRND_TEX_FORMAT_PAL_8 )
	{
		xtex_pPalettePtr = zNEW_ARRAY( unsigned char, 256*3 );
		return xtex_pPalettePtr;
	}

	return 0L;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: GetTextureBuffer( int mipMapNr, void* &buffer, int &pitchXBytes )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: GetTextureBuffer( int mipMapNr, void* &buffer, int &pitchXBytes )
{
    buffer      = NULL;
    pitchXBytes = 0;     // [Moos] Sicherheitshalber resetten wir das Ding mal
    	
	//Rückgabe eines Pointers auf die gewünschte Mipmap-Surface
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::GetTextureBuffer: uninitialized pointer called" );
		return FALSE;
	}
	if( !xtex_locked )
	{
		zERR_WARNING( "X: GetTextureBuffer: Texture is not locked ---> No buffer pointer returned !" );
		return FALSE;
	}
	//Bei DXT1 oder DXT3 muss die Breite und Höhe durch 4 teilbar sein
	if( (xtex_texinfo.texFormat==zRND_TEX_FORMAT_DXT1)||(xtex_texinfo.texFormat==zRND_TEX_FORMAT_DXT3) )
		if( ((xtex_texinfo.sizeX>>mipMapNr)<4)||((xtex_texinfo.sizeY>>mipMapNr)<4) )
		{
			zERR_WARNING( "X: GetTextureBuffer: DXT1- or DXT3-Mipmap with width or height < 4 pixels !" );
			return FALSE;
		}
	//Falls die Surface noch nicht vorhanden ist, so erstelle eine neue bzw. besorge eine aus dem Slotsystem
	if( !xtex_pddtex[0] )
	{
		xtex_slotindex.mipmaps = xtex_texinfo.numMipMap-1;
		switch( xtex_texinfo.sizeX )
		{
		case	1:
				xtex_slotindex.width = 0;
				break;
		case	2:
				xtex_slotindex.width = 1;
				break;
		case	4:
				xtex_slotindex.width = 2;
				break;
		case	8:
				xtex_slotindex.width = 3;
				break;
		case	16:
				xtex_slotindex.width = 4;
				break;
		case	32:
				xtex_slotindex.width = 5;
				break;
		case	64:
				xtex_slotindex.width = 6;
				break;
		case	128:
				xtex_slotindex.width = 7;
				break;
		case	256:
				xtex_slotindex.width = 8;
				break;
		case	512:
				xtex_slotindex.width = 9;
				break;
		case	1024:
				xtex_slotindex.width = 10;
				break;
		case	2048:
				xtex_slotindex.width = 11;
				break;
		default:
				xtex_slotindex.width = 999;
		}
		switch( xtex_texinfo.sizeY )
		{
		case	1:
				xtex_slotindex.height = 0;
				break;
		case	2:
				xtex_slotindex.height = 1;
				break;
		case	4:
				xtex_slotindex.height = 2;
				break;
		case	8:
				xtex_slotindex.height = 3;
				break;
		case	16:
				xtex_slotindex.height = 4;
				break;
		case	32:
				xtex_slotindex.height = 5;
				break;
		case	64:
				xtex_slotindex.height = 6;
				break;
		case	128:
				xtex_slotindex.height = 7;
				break;
		case	256:
				xtex_slotindex.height = 8;
				break;
		case	512:
				xtex_slotindex.height = 9;
				break;
		case	1024:
				xtex_slotindex.height = 10;
				break;
		case	2048:
				xtex_slotindex.height = 11;
				break;
		default:
				xtex_slotindex.height = 999;
		}
		if( !XTEX_BuildSurfaces( FALSE ) )
			return FALSE;
	}
	DDSURFACEDESC2 ddsd;
	ZeroMemory( &ddsd, sizeof( ddsd ) );
	ddsd.dwSize = sizeof( DDSURFACEDESC2 );
	//Falls eine Online-Dekompression durch DirectX vorgesehen ist, so breite diese nun vor
	if( xtex_decompress )
	{
		//DXTC-Surface vom gewünschten S3TC-Format und mit der aktuellen Höhe und Breite bereitstellen
		//lassen sowie in xtex_pddtemporarytex[mipMapNr] merken !
		xtex_pddtemporarytex[mipMapNr] = global_DXTCCache.Lock( xtex_slotindex.width-mipMapNr, 
			xtex_slotindex.height-mipMapNr, xtex_texinfo.texFormat );
		if( xtex_pddtemporarytex[mipMapNr]==NULL )
			return FALSE;
		while( zCRnd_D3D::xd3d_dd7inuse )
		{
			zERR_MESSAGE(5,0, "X: DirectDraw out of sync !" );
			Sleep( 0 );
		}
		zCRnd_D3D::xd3d_dd7inuse = TRUE;
		HRESULT hr;
		if( !DXTryWarning( hr = xtex_pddtemporarytex[mipMapNr]->Lock( NULL, &ddsd, DDLOCK_WRITEONLY, NULL ), 
			"X: [TXD3D]GetTextureBuffer: Can't lock the texture surface !" ) )
		{
			while( hr==DDERR_SURFACEBUSY )
				hr = xtex_pddtemporarytex[mipMapNr]->Lock( NULL, &ddsd, DDLOCK_WRITEONLY, NULL );
			if( hr!=D3D_OK )
			{
				zCRnd_D3D::xd3d_dd7inuse = FALSE;
				return FALSE;
			}
			zERR_MESSAGE(5,0, "X: [TXD3D]GetTextureBuffer: Locked the texture surface !" );
		}
		zCRnd_D3D::xd3d_dd7inuse = FALSE;
	}
	else
	{
		while( zCRnd_D3D::xd3d_dd7inuse )
		{
			zERR_MESSAGE(5,0, "X: DirectDraw out of sync !" );
			Sleep( 0 );
		}
		zCRnd_D3D::xd3d_dd7inuse = TRUE;
		HRESULT hr;
		if( !DXTryWarning( hr = xtex_pddtex[mipMapNr]->Lock( NULL, &ddsd, DDLOCK_WRITEONLY, NULL ), 
			"X: [TXD3D]GetTextureBuffer: Can't lock the texture surface !" ) )
		{
			while( hr==DDERR_SURFACEBUSY )
				hr = xtex_pddtex[mipMapNr]->Lock( NULL, &ddsd, DDLOCK_WRITEONLY, NULL );
			if( hr!=D3D_OK )
			{
				zCRnd_D3D::xd3d_dd7inuse = FALSE;
				return FALSE;
			}
			zERR_MESSAGE(5,0, "X: [TXD3D]GetTextureBuffer: Locked the texture surface !" );
		}
		zCRnd_D3D::xd3d_dd7inuse = FALSE;
	}
	
	//Bei nachfolgender Online-Dekompression durch DirectX wird der Pointer auf die temporäre, komprimierte Surface
	//zurückgegeben, ansonsten ein Pointer auf die gewünschte Surface
	buffer = (void*) ddsd.lpSurface;
	xtex_buffer = buffer;
	switch( xtex_texinfo.texFormat )
	{
	case	zRND_TEX_FORMAT_DXT1:
			pitchXBytes = xtex_texinfo.sizeX>>(mipMapNr+1);
			break;
	case	zRND_TEX_FORMAT_DXT3:
			pitchXBytes = xtex_texinfo.sizeX>>mipMapNr;
			break;
	default:
			pitchXBytes = ddsd.lPitch;
	}
	xtex_miplocked |= 0x0001<<mipMapNr; //TRUE

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: XTEX_BuildSurfaces( zBOOL decompressBuild )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: XTEX_BuildSurfaces( zBOOL decompressBuild )
{
	// Erzeuge neue Surfaces bzw. hole die passenden aus dem Slot-System
	DDSURFACEDESC2 ddsd2;
	ZeroMemory( &ddsd2, sizeof( ddsd2 ) );
	ddsd2.dwSize = sizeof( ddsd2 );
	switch( xtex_texinfo.texFormat )
	{	
	case	zRND_TEX_FORMAT_ARGB_4444:			
			ddsd2.ddpfPixelFormat				= pflist[1];
			xtex_alphaTex						= TRUE;
			xtex_slotindex.pixelformat			= 0;
			break;
	case	zRND_TEX_FORMAT_ARGB_1555:			
			ddsd2.ddpfPixelFormat				= pflist[3];
			xtex_alphaTex						= TRUE;
			xtex_slotindex.pixelformat			= 1;
			break;	
	case	zRND_TEX_FORMAT_DXT1:
			if( supportDXTC[0]==FALSE )
			{
				xtex_decompress					= TRUE;
				//Ausnahmefall berücksichtigen
				if( !decompressBuild )
					return TRUE;
				//Werte den zuvor ermittelten Alphagehalt der Textur aus
				if( xtex_alphaTex ) 
				{								
					ddsd2.ddpfPixelFormat		= pflist[3];
					xtex_alphaTex				= TRUE;
					xtex_slotindex.pixelformat	= 1;
				}
				else
				{	
					ddsd2.ddpfPixelFormat		= pflist[2];
					xtex_alphaTex				= FALSE;
					xtex_slotindex.pixelformat	= 2;
				}
				break;
			}
			ddsd2.ddpfPixelFormat.dwFourCC		= MAKEFOURCC('D', 'X', 'T', '1');
			ddsd2.ddpfPixelFormat.dwFlags		= DDPF_FOURCC;
			xtex_slotindex.pixelformat			= 4;
			break;
	case	zRND_TEX_FORMAT_DXT2:
			zERR_WARNING( "X: GetTextureBuffer: zRND_TEX_FORMAT_DXT2 not supported !" );
			return FALSE;
	case	zRND_TEX_FORMAT_DXT3:
			if( supportDXTC[2]==FALSE )
			{
				xtex_decompress					= TRUE;
				//Ausnahmefall berücksichtigen
				if( !decompressBuild )
					return TRUE;
				ddsd2.ddpfPixelFormat			= pflist[1];
				xtex_alphaTex					= TRUE;
				xtex_slotindex.pixelformat		= 0;
				break;
			}
			ddsd2.ddpfPixelFormat.dwFourCC		= MAKEFOURCC('D', 'X', 'T', '3');
			ddsd2.ddpfPixelFormat.dwFlags		= DDPF_FOURCC;
			xtex_alphaTex						= TRUE;
			xtex_slotindex.pixelformat			= 5;
			break;
	case	zRND_TEX_FORMAT_DXT4:
			zERR_WARNING( "X: GetTextureBuffer: zRND_TEX_FORMAT_DXT4 not supported !" );
			return FALSE;
	case	zRND_TEX_FORMAT_DXT5:
			zERR_WARNING( "X: GetTextureBuffer: zRND_TEX_FORMAT_DXT5 not supported !" );
			return FALSE;
	default:			
			ddsd2.ddpfPixelFormat				= pflist[2];
			xtex_alphaTex						= FALSE;
			xtex_slotindex.pixelformat			= 2;
	}

	//Bei 8-Bit palettierten Texturen ist eine zusätzliche Palette notwendig
	unsigned char *pal = (unsigned char*)GetPaletteBuffer();		 
	if( pal )
	{
		if( xtex_palsupport )
		{	
			ddsd2.ddpfPixelFormat		= pflist[0];
			xtex_slotindex.pixelformat	= 3;
		}
		else
		{
			zERR_WARNING( "X: GetTextureBuffer: Can't use palettized texture !" );
			return FALSE;
		}
	}
	ddsd2.dwFlags = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_MIPMAPCOUNT; 
	ddsd2.ddsCaps.dwCaps = DDSCAPS_TEXTURE|DDSCAPS_MIPMAP|DDSCAPS_COMPLEX;
	if( GetChangingRealtime() )
	{
		ddsd2.ddsCaps.dwCaps2	= DDSCAPS2_TEXTUREMANAGE|DDSCAPS2_HINTDYNAMIC;
		xtex_slotindex.dynamic	= 0;
	}
	else
	{
		ddsd2.ddsCaps.dwCaps2	= DDSCAPS2_TEXTUREMANAGE;
		xtex_slotindex.dynamic	= 1;
	}
	ddsd2.dwMipMapCount = xtex_texinfo.numMipMap;
	ddsd2.dwWidth		= xtex_texinfo.sizeX;
	ddsd2.dwHeight		= xtex_texinfo.sizeY;

	//Bei DXT1 oder DXT3 muss die Breite und Höhe aller MipMaps durch 4 teilbar sein
	if( (xtex_texinfo.texFormat==zRND_TEX_FORMAT_DXT1)||(xtex_texinfo.texFormat==zRND_TEX_FORMAT_DXT3) )
	{
		int numOfRealMipMaps = 0;
		if( ddsd2.dwMipMapCount>0 )
			numOfRealMipMaps = ddsd2.dwMipMapCount-1;
		if( ((ddsd2.dwWidth>>numOfRealMipMaps)<4)||((ddsd2.dwHeight>>numOfRealMipMaps)<4) )
		{
			zERR_WARNING( "X: GetTextureBuffer: DXT1- or DXT3-MipMap with width or height < 4 pixels !" );
			return FALSE;
		}
	}

	//Zuerst wird im Slotsystem eine passende Surface gesucht
	xtex_pddtex[0]		= global_surfaceCache.CacheOutSurface( &xtex_slotindex );

	//Ist dort keine vorhanden, so muss eine neue erzeugt werden
	if( xtex_pddtex[0]==NULL )
	{
		while( zCRnd_D3D::xd3d_dd7inuse )
		{
			zERR_MESSAGE(5,0, "X: DirectDraw out of sync !" );
			Sleep( 0 );
		}
		zCRnd_D3D::xd3d_dd7inuse = TRUE;
		if( !DXTryWarning( zCRnd_D3D::xd3d_pdd7->CreateSurface( &ddsd2, &(xtex_pddtex[0]), NULL ), 
				"X: [TXD3D]GetTextureBuffer: Can't create a new texture surface !" ) )
		{
			zCRnd_D3D::xd3d_dd7inuse = FALSE;
			return FALSE;
		}
		zCRnd_D3D::xd3d_dd7inuse = FALSE;
	}

	//Setze bei 8-Bit palettierten Texturen die Palette
	if( pal&&xtex_palsupport )
	{	
		PALETTEENTRY palentry[256];
		// palette kopieren...
		for( int t=0; t<256; t++ )
		{	
			palentry[t].peRed	= pal[(t*3)+2];
			palentry[t].peGreen	= pal[(t*3)+1];
			palentry[t].peBlue	= pal[(t*3)+0];
		}
		// palette anmelden...
		while( zCRnd_D3D::xd3d_dd7inuse )
		{
			zERR_MESSAGE(5,0, "X: DirectDraw out of sync !" );
			Sleep( 0 );
		}
		zCRnd_D3D::xd3d_dd7inuse = TRUE;
		if( !DXTryWarning( zCRnd_D3D::xd3d_pdd7->CreatePalette( DDPCAPS_8BIT, palentry, &xtex_pddpal, NULL ), 
			"X: [TXD3D]GetTextureBuffer: Can't create a new texture palette !" ) )
		{
			zCRnd_D3D::xd3d_dd7inuse = FALSE;
			return FALSE;
		}
		if( !DXTryWarning( xtex_pddtex[0]->SetPalette( xtex_pddpal ), 
			"X: [TXD3D]GetTextureBuffer: Can't set the new texture palette !" ) )
		{
			zCRnd_D3D::xd3d_dd7inuse = FALSE;
			return FALSE;
		}
		zCRnd_D3D::xd3d_dd7inuse = FALSE;
	}

	// Merke die Pointer auf die einzelnen Mipmaps
	if( xtex_texinfo.numMipMap>1 )
	{	
		int next = 1;
		IDirectDrawSurface7 *MipMap		= 0;
		IDirectDrawSurface7 *NextMipMap	= 0;
		DDSCAPS2 ddcaps;
		xtex_pddtex[0]->AddRef();
		MipMap			= xtex_pddtex[0];
		ddcaps.dwCaps	= DDSCAPS_TEXTURE | DDSCAPS_MIPMAP;
		ddcaps.dwCaps2	= 0;
		ddcaps.dwCaps3	= 0;
		ddcaps.dwCaps4	= 0;
		while (next<xtex_texinfo.numMipMap)
		{
			if (!DXTryWarning (MipMap->GetAttachedSurface (&ddcaps, &NextMipMap), "X: [TXD3D]GetTextureBuffer: Can't get the attached surface !"))
			{
				break;
			}
			else
			{
				xtex_pddtex[next]	= NextMipMap;

				if (!NextMipMap)	break;			// => kam laut CrashLog bei einem Kunden mal vor... wie kann das passieren ,wie fixt man soetwas?

				NextMipMap->Release	();
				MipMap				= NextMipMap;
				++next;
			}
		}
		// Sollte eine Reduktion des Referenzzählers zur 0 führen, so melde einen Fehler
		if( xtex_pddtex[0]->Release()==0 )
		{
			if( xtex_pddpal )
				RELEASE( xtex_pddpal );
			if( xtex_pPalettePtr ) 
				delete[] xtex_pPalettePtr;
			xtex_pPalettePtr	= NULL;	
			xtex_pddtex[0]		= NULL;	
			xtex_pddpal			= NULL;
			zERR_WARNING( "X: GetTextureBuffer: Mipmap-Loop -> Release returned 0 !" );
			return FALSE;
		}
	}

	//Registriere die neue Textur
	while( 1 )
	{	
		int t = 0; 
		while( tex[t].mode!=0&&t<zD3DTEXMAX ) 
			t++;
		if( t<zD3DTEXMAX )
		{	
			tex[t].texture		= this;
			tex[t].mode			= 1;
			xtex_internalnumber = t;
			break;
		} 
		//Falls maximale Anzahl der Texturen erreicht, so entferne alle aus dem Speicher
		zERR_MESSAGE(5, 0, "X: Reached maximum texture count (zD3DTEXMAX = " + zSTRING(zD3DTEXMAX) + "). All textures are removed now!");
		for( t = 0; t<zD3DTEXMAX; t++ )	
			if( tex[t].mode )
			{	
				tex[t].texture->RemoveTexture(); 
				tex[t].mode			= 0;
				xtex_internalnumber = -1;
			}
	}

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	void zCTex_D3D :: InsertTexture( zBOOL palsupp, int stage )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCTex_D3D :: InsertTexture( zBOOL palsupp, int stage )
{	
	//Aktivierung der gewünschten Textur
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::InsertTexture: uninitialized pointer called" );
		return;
	}

	//Keine Textur wird aktiviert, falls die Grösse oder der Pointer nicht vorhanden ist
	if( xtex_texinfo.sizeX==0||xtex_texinfo.sizeY==0 )
	{	
		((zCRnd_D3D*)zrenderer)->XD3D_SetTexture( stage, 0L );
		((zCRnd_D3D*)zrenderer)->xd3d_ptexture[stage] = 0L;
		return;
	}
	if( !xtex_pddtex[0] )
	{	
		((zCRnd_D3D*)zrenderer)->XD3D_SetTexture( stage, 0L );
		((zCRnd_D3D*)zrenderer)->xd3d_ptexture[stage] = 0L;
		return;
	}

	//Teste, ob die Texture-Surface restauriert werden muss (z.B. nach Alt+Tab)
	if( xtex_pddtex[0]->IsLost()==DDERR_SURFACELOST )
	{
		zERR_WARNING( "X: TXD3D]InsertTexture: Texture surface has been lost - restoring ... !" );
		xtex_pddtex[0]->Restore();

		if (this->GetCacheState()!=zRES_CACHED_IN)
		{
			CacheOut();
			CacheIn (-1);
		}
	}

	//Aktivieren der gewünschten Textur in DirectX
	if( ((zCRnd_D3D*)zrenderer)->XD3D_SetTexture( stage, xtex_pddtex[0] ) )
		((zCRnd_D3D*)zrenderer)->xd3d_ptexture[stage] = this;
	if( GetLastFrameUsed()!=((zCRnd_D3D*)zrenderer)->xd3d_actFrameNumber )
	{
		((zCRnd_D3D*)zrenderer)->xd3d_numTexturesUsedThisFrame++;
		SetLastFrameUsed();
	}
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: PreloadTexture()

 

    4-Oct-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: PreloadTexture()
{

	//Preload der gewünschten Textur in DirectX
	if( xtex_pddtex[0]==NULL )
		return FALSE;
	if( !DXTryWarning( zCRnd_D3D::xd3d_pd3dDevice7->PreLoad( xtex_pddtex[0] ), "X: [TXD3D]PreloadTexture: Preload texture failed!" ) ) 
		return FALSE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: SetTexture( int stage )

    14-Aug-00       [PELZER]
    14-Jan-01       [HILDEBRANDT]
					Mikrooptimierung
--------------------------------------------------------------------------*/

zBOOL zCTex_D3D :: SetTexture( int stage )
{
	// Gewünschte Textur wird direkt gesetzt (bei der Verwendung von Vertexbuffern)  
	if( (xtex_texinfo.sizeX==0) || (xtex_texinfo.sizeY==0) || (!xtex_pddtex[0]) )
	{	
		if( !((zCRnd_D3D*)zrenderer)->XD3D_SetTexture( stage, 0 ) ) return FALSE;
		((zCRnd_D3D*)zrenderer)->xd3d_ptexture[stage] = 0L;
		return TRUE;
	}

	// Teste, ob die Texture-Surface restauriert werden muss (z.B. nach Alt+Tab)
	if( xtex_pddtex[0]->IsLost()==DDERR_SURFACELOST )
	{
		zERR_WARNING( "X: TXD3D]SetTexture: Texture surface has been lost - restoring ... !" );
		xtex_pddtex[0]->Restore();
		if (this->GetCacheState()!=zRES_CACHED_IN)
		{
			CacheOut();
			CacheIn (-1);
		}
	}

	// Aktivieren der gewünschten Textur in DirectX
	if( !((zCRnd_D3D*)zrenderer)->XD3D_SetTexture( stage, xtex_pddtex[0] ) )	
		return FALSE;

 	((zCRnd_D3D*)zrenderer)->xd3d_ptexture[stage] = this;
/*	if( GetLastFrameUsed()!=((zCRnd_D3D*)zrenderer)->xd3d_actFrameNumber )
	{
		((zCRnd_D3D*)zrenderer)->xd3d_numTexturesUsedThisFrame++;
		SetLastFrameUsed();
	}*/

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: RemoveTexture()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: RemoveTexture()
{	
	//Komplettes Entfernen bzw. Einlagern (in das Slotsystem) einer Textur
	if( xtex_textureflag!=0xDEADFACE )
	{	
		zERR_WARNING("X: zCTex_D3D::RemoveTexture: uninitialized pointer called" );
		return FALSE;
	}
	if( xtex_internalnumber>=0 )
		tex[xtex_internalnumber].mode = 0;
	if( xtex_pddtex[0]==NULL )
		return FALSE;
	if( !global_surfaceCache.CacheInSurface( xtex_pddtex[0], &xtex_slotindex ) )
		xtex_pddtex[0]->Release();
	//Die Palettendaten (sofern vorhanden) werden entfernt
	if( xtex_pddpal )
		RELEASE( xtex_pddpal );
	if( xtex_pPalettePtr ) 
		delete[] xtex_pPalettePtr;
	xtex_pPalettePtr	= NULL;	
	xtex_pddtex[0]		= NULL;	
	xtex_pddpal			= NULL;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: RescueTexture( zD3D_savedTexture *savedTex )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: RescueTexture( zD3D_savedTexture *savedTex ) 
{
	//Texturen die über einen Device-Wechsel hinweg gerettet werden müssen werden hier behandelt
	this->SetCacheOutLock( FALSE );
	savedTex->texCon = zrenderer->CreateTextureConvert();
	//Rettung der Textur in einem Texture-Convert-Objekt
	if( !zCTextureExchange::CopyContents( this, savedTex->texCon ) )
		return FALSE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCTex_D3D :: RebuildTexture( zD3D_savedTexture *savedTex ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCTex_D3D :: RebuildTexture( zD3D_savedTexture *savedTex ) 
{
	//Restauration der über einen Device-Wechsel hinweg geretteten Texturen
	zCTextureInfo texInfo = savedTex->texCon->GetTextureInfo();	
	zBOOL calcNextBest = FALSE;
	switch( texInfo.texFormat )
	{
	case	zRND_TEX_FORMAT_ARGB_4444:			
			if( pflist[1].dwRGBBitCount==0 )
				calcNextBest = TRUE;
			break;
	case	zRND_TEX_FORMAT_ARGB_1555:			
			if( pflist[3].dwRGBBitCount==0 )
				calcNextBest = TRUE;
			break;	
	case	zRND_TEX_FORMAT_DXT1:
			if( supportDXTC[0]==FALSE )
			{
				zERR_WARNING( "X: RebuildTexture: Can't use DXT1 texture !" );
				calcNextBest = TRUE;
			}
			break;
	case	zRND_TEX_FORMAT_DXT2:
			if( supportDXTC[1]==FALSE )
			{
				zERR_WARNING( "X: RebuildTexture: Can't use DXT2 texture !" );
				calcNextBest = TRUE;
			}
			break;
	case	zRND_TEX_FORMAT_DXT3:
			if( supportDXTC[2]==FALSE )
			{
				zERR_WARNING( "X: RebuildTexture: Can't use DXT3 texture !" );
				calcNextBest = TRUE;
			}
			break;
	case	zRND_TEX_FORMAT_DXT4:
			if( supportDXTC[3]==FALSE )
			{
				zERR_WARNING( "X: RebuildTexture: Can't use DXT4 texture !" );
				calcNextBest = TRUE;
			}
			break;
	case	zRND_TEX_FORMAT_DXT5:
			if( supportDXTC[4]==FALSE )
			{
				zERR_WARNING( "X: RebuildTexture: Can't use DXT5 texture !" );
				calcNextBest = TRUE;
			}
			break;
	default:
			if( pflist[2].dwRGBBitCount==0 )
				calcNextBest = TRUE;
	}
	//Falls notwendig erfolgt einen Konvertierung des geretteten Texturformats in ein durch die neue Device unterstütztes
	if( calcNextBest )
	{
		texInfo.texFormat = zCTexture::CalcNextBestTexFormat( texInfo.texFormat );
		savedTex->texCon->ConvertTextureFormat( texInfo );
	}
	//Übertragung der geretteten Textur
	if( !zCTextureExchange::CopyContents( savedTex->texCon, this ) )
	{
		delete savedTex->texCon;
		return FALSE;
	}
	this->SetCacheOutLock( TRUE );
	
	return TRUE;
}


