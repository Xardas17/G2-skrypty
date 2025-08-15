

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_SurfaceCache.cpp
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.97pre
* last modified : 21.10.00
* erstellt      : 11.07.00										
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
#include "zRndD3D_SurfaceCache.h"






/*--------------------------------------------------------------------------
	
	zCSurfaceCache_D3D :: zCSurfaceCache_D3D() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCSurfaceCache_D3D :: zCSurfaceCache_D3D()
{
	//Notwendige Initialisierungen
	xsc_cacheentryCounter		= 0;
	const zD3D_SlotHeader* stop = &xsc_slot[1][5][11][11][11];
	for( zD3D_SlotHeader* ptr = &xsc_slot[0][0][0][0][0]; ptr<=stop; )
	{
		ptr->firstEntry =  NULL;
		ptr->lastEntry	= NULL;
		++ptr;
	}
}



/*--------------------------------------------------------------------------
	
	zCSurfaceCache_D3D :: ~zCSurfaceCache_D3D() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCSurfaceCache_D3D :: ~zCSurfaceCache_D3D()
{
	//Bereinigung des gesamten Slotsystems
	ClearCache();
}



/*--------------------------------------------------------------------------
	
	zBOOL zCSurfaceCache_D3D :: CacheInSurface( IDirectDrawSurface7 *surface, zCSlotIndex *slotindex )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCSurfaceCache_D3D :: CacheInSurface( IDirectDrawSurface7 *surface, zCSlotIndex *slotindex )
{
	//Teste die Slot-Indizies auf Gültigkeit
	if( xsc_cacheentryCounter>=SURFACECACHECOUNTLIMIT )
	{
		while( xsc_listofsurfaces[xsc_listposition]->firstEntry==NULL )
		{
			++xsc_listposition;
			if( xsc_listposition==SURFACECACHECOUNTLIMIT )
				xsc_listposition = 0;
		}
		XSC_KillLastSurfaceInSlot( xsc_listofsurfaces[xsc_listposition] );
	}
	if( (slotindex->dynamic<0)||(slotindex->dynamic>1) )
	{
 		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheInSurface: slotindex->dynamic out of range !" );
		return FALSE;
	}
	if( (slotindex->pixelformat<0)||(slotindex->pixelformat>5) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheInSurface: slotindex->pixelformat out of range !" );
		return FALSE;
	}
	if( (slotindex->width<0)||(slotindex->width>11) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheInSurface: slotindex->width out of range !" );
		return FALSE;
	}
	if( (slotindex->height<0)||(slotindex->height>11) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheInSurface: slotindex->height out of range !" );
		return FALSE;
	}
	if( (slotindex->mipmaps<0)||(slotindex->mipmaps>11) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheInSurface: slotindex->mipmaps out of range !" );
		return FALSE;
	}
	//Füge die Surface als neuen Eintrag am Ende des Slots ein (dort sind die jüngsten Einträge zu finden)
	zD3D_Entry *entry						= NULL;
	entry									= zNEW( zD3D_Entry );
	if( entry==NULL )
		return FALSE;
	entry->surface							= surface;
	entry->frameNumber						= zCRnd_D3D::xd3d_actFrameNumber;
	entry->nextEntry						= NULL;
	zD3D_SlotHeader *slotHeader				= &xsc_slot[slotindex->dynamic][slotindex->pixelformat][slotindex->width][slotindex->height][slotindex->mipmaps];
	if( slotHeader->lastEntry==NULL )
	{
		slotHeader->lastEntry				= entry;
		slotHeader->firstEntry				= entry;
	}
	else
	{
		slotHeader->lastEntry->nextEntry	= entry;
		slotHeader->lastEntry				= entry;
	}
	++xsc_cacheentryCounter;
	xsc_listofsurfaces[xsc_listposition] = slotHeader;
	++xsc_listposition;
	if( xsc_listposition==SURFACECACHECOUNTLIMIT )
		xsc_listposition = 0;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	IDirectDrawSurface7 *zCSurfaceCache_D3D :: CacheOutSurface( zCSlotIndex *slotindex )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
IDirectDrawSurface7 *zCSurfaceCache_D3D :: CacheOutSurface( zCSlotIndex *slotindex )
{
	//Teste die Slot-Indizies auf Gültigkeit
	if( (slotindex->dynamic<0)||(slotindex->dynamic>1) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheOutSurface: slotindex->dynamic out of range !" );
		return NULL;
	}
	if( (slotindex->pixelformat<0)||(slotindex->pixelformat>5) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheOutSurface: slotindex->pixelformat out of range !" );
		return NULL;
	}
	if( (slotindex->width<0)||(slotindex->width>11) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheOutSurface: slotindex->width out of range !" );
		return NULL;
	}
	if( (slotindex->height<0)||(slotindex->height>11) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheOutSurface: slotindex->height out of range !" );
		return NULL;
	}
	if( (slotindex->mipmaps<0)||(slotindex->mipmaps>11) )
	{
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheOutSurface: slotindex->mipmaps out of range !" );
		return NULL;
	}
	//Hole aus dem zugehörigen Slot die älteste (oberste) Surface, sofern diese vorhanden ist
	zD3D_SlotHeader *slotHeader = &xsc_slot[slotindex->dynamic][slotindex->pixelformat][slotindex->width][slotindex->height][slotindex->mipmaps];
	if( slotHeader->firstEntry==NULL )
		return NULL;
	IDirectDrawSurface7 *surface;
	zD3D_Entry *entry		= slotHeader->firstEntry;
	surface					= entry->surface;
	slotHeader->firstEntry	= entry->nextEntry;
	if( entry->nextEntry==NULL )
		slotHeader->lastEntry = NULL;
	delete entry;
	--xsc_cacheentryCounter;
	if( xsc_cacheentryCounter<0 )
		zERR_WARNING( "X: zCSurfaceCache_D3D :: CacheOutSurface: xsc_cacheentryCounter < 0 !" );

	return surface;
}



/*--------------------------------------------------------------------------
	
	void zCSurfaceCache_D3D :: ClearCache()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCSurfaceCache_D3D :: ClearCache()
{
	//Entferne alle Einträge aus allen Slots
	const zD3D_SlotHeader* stop = &xsc_slot[1][5][11][11][11];
	for( zD3D_SlotHeader* ptr = &xsc_slot[0][0][0][0][0]; ptr<=stop; )
	{
		XSC_ClearSlot( ptr );
		++ptr;
	}
	if( xsc_cacheentryCounter!=0 )
		zERR_WARNING( "X: zCSurfaceCache_D3D :: ClearCache: xsc_cacheentryCounter!=0 after cache clearing !" );
}



/*--------------------------------------------------------------------------
	
	void zCSurfaceCache_D3D :: XSC_ClearSlot( zD3D_SlotHeader *slot )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCSurfaceCache_D3D :: XSC_ClearSlot( zD3D_SlotHeader *slot )
{
	zD3D_Entry *entry;
	//Entferne alle Einträge aus dem Slot
	while( slot->firstEntry!=NULL )
	{
		entry = slot->firstEntry;
		if(	(entry->surface!=NULL)&&(entry->surface->Release()>0) )
			zERR_WARNING( "X: zCSurfaceCache_D3D :: XSC_ClearSlot: Release returned with RefCounter>0 !" );
		entry->surface = NULL;
		slot->firstEntry = entry->nextEntry;
		delete entry;
		--xsc_cacheentryCounter;
	}
	slot->firstEntry	= NULL;
	slot->lastEntry		= NULL;
}



/*--------------------------------------------------------------------------
	
	void zCSurfaceCache_D3D :: XSC_KillLastSurfacesInSlot( zD3D_SlotHeader *slot )

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
void zCSurfaceCache_D3D :: XSC_KillLastSurfaceInSlot( zD3D_SlotHeader *slot )
{
	zD3D_Entry *entry = slot->firstEntry;
	if(	(entry->surface!=NULL)&&(entry->surface->Release()>0) )
		zERR_MESSAGE(8,0, "X: Kill last surface in slot with RefCounter>0 !" );
	entry->surface = NULL;
	slot->firstEntry = entry->nextEntry;
	delete entry;
	--xsc_cacheentryCounter;
	//Falls der Slot komplett bereinigt wurde, so vermerke dies im Pointer auf den letzten Eintrag
	if( slot->firstEntry==NULL )
		slot->lastEntry = NULL;
}

