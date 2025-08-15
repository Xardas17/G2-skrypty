

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_DXTCCache.cpp
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.97pre
* last modified : 20.10.00
* erstellt      : 20.10.00										
* Compiler OK   : 
*																
*********************************************************************************
- known bugs: 

*********************************************************************************
- possible optimizations: 

*********************************************************************************
- missing features:

*********************************************************************************
- comments:
  
TODO:

*********************************************************************************/



#include "zcore.h"
#include "zRndD3D_DXTCCache.h"






/*--------------------------------------------------------------------------
	
	zCDXTCCache_D3D :: zCDXTCCache_D3D()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCDXTCCache_D3D :: zCDXTCCache_D3D()
{
	//Notwendige Initialisierungen
	xdxtc_cacheentryCounter = 0;
	const zD3D_SlotHeader* stop = &xdxtc_slot[1][11][11];
	for( zD3D_SlotHeader* slot = &xdxtc_slot[0][0][0]; slot<=stop; )
	{
		slot->firstEntry	=  NULL;
		slot->lastEntry		= NULL;
		++slot;
	}
}



/*--------------------------------------------------------------------------
	
	zCDXTCCache_D3D :: ~zCDXTCCache_D3D()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCDXTCCache_D3D :: ~zCDXTCCache_D3D()
{
	//Bereinige das gesamte Slotsystem
	ClearCache();
}



/*--------------------------------------------------------------------------
	
	IDirectDrawSurface7 *zCDXTCCache_D3D :: Lock( int widthID, int heightID, int format )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
IDirectDrawSurface7 *zCDXTCCache_D3D :: Lock( int widthID, int heightID, int format )
{
	zD3D_Entry *entry;
	if( format==zRND_TEX_FORMAT_DXT1 )
		entry = xdxtc_slot[0][widthID][heightID].firstEntry;
	else
		entry = xdxtc_slot[1][widthID][heightID].firstEntry;
	if( entry!=NULL )
	{
		//Suche nach einem vorhandenen, nicht gelockten Eintrag
		while( entry->locked&&(entry->nextEntry!=NULL) )
			entry = entry->nextEntry;
		if( !entry->locked )
		{
			//Lock des gefundenen Eintrags und Rückgabe der DXTC-Surface
			entry->locked = TRUE;
			return entry->surface;
		}
		//Erzeuge einen neuen Eintrag für den Slot und zähle ihn mit
		entry->nextEntry	= zNEW( zD3D_Entry );
		++xdxtc_cacheentryCounter;
		entry				= entry->nextEntry;
		entry->nextEntry	= NULL;
		//Lock des Eintrags 
		entry->locked		= TRUE;
		return XDXTC_CreateSurface( widthID, heightID, format, entry );
	}
	//Erzeuge einen neuen Eintrag für den leeren Slot und zähle ihn mit
	entry = zNEW( zD3D_Entry );
	++xdxtc_cacheentryCounter;
	if( format==zRND_TEX_FORMAT_DXT1 )
		xdxtc_slot[0][widthID][heightID].firstEntry = entry;
	else
		xdxtc_slot[1][widthID][heightID].firstEntry = entry;
	entry->nextEntry	= NULL;
	//Lock des Eintrag und Rückgabe der DXTC-Surface
	entry->locked		= TRUE;

	return XDXTC_CreateSurface( widthID, heightID, format, entry );
}



/*--------------------------------------------------------------------------
	
	zBOOL zCDXTCCache_D3D :: Unlock( int widthID, int heightID, int format, IDirectDrawSurface7 *surface )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCDXTCCache_D3D :: Unlock( int widthID, int heightID, int format, IDirectDrawSurface7 *surface )
{
	zD3D_Entry *entry;
	if( format==zRND_TEX_FORMAT_DXT1 )
		entry = xdxtc_slot[0][widthID][heightID].firstEntry;
	else
		entry = xdxtc_slot[1][widthID][heightID].firstEntry;
	while( (entry!=NULL)&&(entry->surface!=surface) )
		entry = entry->nextEntry;
	//Falls der Eintrag nicht existiert, so melde einen Fehler
	if( entry==NULL )
	{
		zERR_WARNING( "X: zCDXTCCache_D3D :: Unlock: Can't unlock a missing entry !" );
		return FALSE;
	}
	//Unlock des Eintrags
	entry->locked = FALSE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	void zCDXTCCache_D3D :: ClearCache()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCDXTCCache_D3D :: ClearCache()
{
	zERR_MESSAGE(5,0, "X: zCDXTCCache_D3D :: ClearCache: Surfaces to clear - " + zSTRING( xdxtc_cacheentryCounter ) );
	const zD3D_SlotHeader* stop = &xdxtc_slot[1][11][11];
	zD3D_Entry *entry;
	//Durchlaufe sämtliche Slots
	for( zD3D_SlotHeader* slot = &xdxtc_slot[0][0][0]; slot<=stop; )
	{
		//Leere den Slot vollständig
		while( slot->firstEntry!=NULL )
		{
			entry = slot->firstEntry;
			if(	(entry->surface!=NULL)&&(entry->surface->Release()>0) )
				zERR_WARNING( "X: zCDXTCCache_D3D :: ClearCache: Release returned with RefCounter>0 !" );
			entry->surface = NULL;
			slot->firstEntry = entry->nextEntry;
			delete entry;
			--xdxtc_cacheentryCounter;
		}
		slot->firstEntry	= NULL;
		slot->lastEntry		= NULL;
		++slot;
	}
	//Überprüfe, ab die gezählten Neueinträge von der Anzahl der zerstörten Einträge abweicht
	if( xdxtc_cacheentryCounter!=0 )
		zERR_WARNING( "X: zCDXTCCache_D3D :: ClearCache: xdxtc_cacheentryCounter!=0 after cache clearing !" );
}



/*--------------------------------------------------------------------------
	
	IDirectDrawSurface7 *zCDXTCCache_D3D :: XDXTC_CreateSurface( int widthID, int heightID, int format, zD3D_Entry *entry )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
IDirectDrawSurface7 *zCDXTCCache_D3D :: XDXTC_CreateSurface( int widthID, int heightID, int format, zD3D_Entry *entry )
{
	DDSURFACEDESC2 ddsd2;
	ZeroMemory( &ddsd2, sizeof( ddsd2 ) );
	ddsd2.dwSize = sizeof( ddsd2 );
	ddsd2.ddpfPixelFormat.dwSize = sizeof( DDPIXELFORMAT );
	//Es werden nur DXT1 und DXT3 unterstützt, da intern mit RGB_565, ARGB_1555 und ARGB_4444 gearbeitet wird 
	if( format==zRND_TEX_FORMAT_DXT1 )
		ddsd2.ddpfPixelFormat.dwFourCC = MAKEFOURCC('D', 'X', 'T', '1');
	else
		ddsd2.ddpfPixelFormat.dwFourCC = MAKEFOURCC('D', 'X', 'T', '3');
	ddsd2.ddpfPixelFormat.dwFlags	= DDPF_FOURCC;
	ddsd2.dwFlags					= DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT; 
	ddsd2.ddsCaps.dwCaps			= DDSCAPS_TEXTURE;
	ddsd2.ddsCaps.dwCaps2			= DDSCAPS2_TEXTUREMANAGE|DDSCAPS2_HINTDYNAMIC;
	ddsd2.dwWidth					= 0x0001<<widthID;
	ddsd2.dwHeight					= 0x0001<<heightID;
	while( zCRnd_D3D::xd3d_dd7inuse )
	{
		zERR_MESSAGE(8,0, "X: DirectDraw out of sync !" );
		Sleep( 0 );
	}
	zCRnd_D3D::xd3d_dd7inuse = TRUE;
	if( !DXTryWarning( zCRnd_D3D::xd3d_pdd7->CreateSurface( &ddsd2, &(entry->surface), NULL ), 
			"X: [TXD3D]GetTextureBuffer: Can't create a new texture surface !" ) )
	{
		zCRnd_D3D::xd3d_dd7inuse = FALSE;
		return NULL;
	}
	zCRnd_D3D::xd3d_dd7inuse = FALSE;

	return entry->surface;
}

