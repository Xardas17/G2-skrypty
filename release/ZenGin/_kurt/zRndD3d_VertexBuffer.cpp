

/********************************************************************************
*																
* C++ Hardware Abstraction Layer (low/mid/hi-Level)
*	  DirectX 7 - Implementation
* File          : zRndD3D_Vertexbuffer.cpp
* Projekt       : Phoenix
* Autor         : Kurt Pelzer
* Version       : 0.97pre
* last modified : 21.10.00
* erstellt      : 10.07.00										
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
#include "zRndD3D_Vertexbuffer.h"



zCArray<zCVertexBuffer_D3D*> zCVertexBuffer_D3D::xvb_vertexbufferList(512);






/*--------------------------------------------------------------------------
	
	zCVertexBuffer_D3D :: zCVertexBuffer_D3D() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCVertexBuffer_D3D :: zCVertexBuffer_D3D() 
{
	//Notwendige Initialisierungen
	xvb_vertexFormat		= 0;
	xvb_vertexType			= zVBUFFER_VERTTYPE_UT_UL; 
	xvb_locked				= FALSE;
	xvb_optimized			= FALSE;
	xvb_primitiveType		= zVBUFFER_PT_TRIANGLELIST;
	xvb_indexList.EmptyList();
	xvb_vertexBuffer		= 0;
	xvb_vertexbufferList.Insert( this );
}



/*--------------------------------------------------------------------------
	
	zCVertexBuffer_D3D :: ~zCVertexBuffer_D3D()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zCVertexBuffer_D3D :: ~zCVertexBuffer_D3D()
{
	//Zerstörung des DirectX-Vertexbuffers
	zRELEASE( xvb_vertexBuffer );
	xvb_vertexbufferList.Remove( this );
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: Create( zDWORD vtxFormat, zDWORD numVert, zDWORD createFlags )

    14-Aug-00       [PELZER]
    03-Oct-00       [HILDEBRANDT]
					Kriterium zur Bestimmung von zVBUFFER_VERTTYPE_UT_UL Verts geaendert.
--------------------------------------------------------------------------*/

zBOOL zCVertexBuffer_D3D :: Create( zDWORD vtxFormat, zDWORD numVert, zDWORD createFlags )
{
	if( xvb_vertexBuffer!=NULL )	return FALSE;

	// Aufbau des flexiblen Vertexformats
	zDWORD vertexFormatD3D = 0;
	if( vtxFormat & zVBUFFER_VERTFORMAT_XYZ )		vertexFormatD3D	|= D3DFVF_XYZ; 
	if( vtxFormat & zVBUFFER_VERTFORMAT_XYZRHW )	vertexFormatD3D	|= D3DFVF_XYZRHW;
	if( vtxFormat & zVBUFFER_VERTFORMAT_NORMAL )	vertexFormatD3D	|= D3DFVF_NORMAL; 
	if( vtxFormat & zVBUFFER_VERTFORMAT_COLOR )		vertexFormatD3D	|= D3DFVF_DIFFUSE; 
	if( vtxFormat & zVBUFFER_VERTFORMAT_TEXUV1 )	vertexFormatD3D	|= D3DFVF_TEX1; 
	if( vtxFormat & zVBUFFER_VERTFORMAT_TEXUV2 )	vertexFormatD3D	|= D3DFVF_TEX2;
	if( vtxFormat & zVBUFFER_VERTFORMAT_TEXUV3 )	vertexFormatD3D	|= D3DFVF_TEX3;
	if( vtxFormat & zVBUFFER_VERTFORMAT_TEXUV4 )	vertexFormatD3D	|= D3DFVF_TEX4;

	{
		D3DVERTEXBUFFERDESC		vbdesc;
		ZeroMemory				( &vbdesc, sizeof( D3DVERTEXBUFFERDESC ) );
		vbdesc.dwSize			= sizeof( D3DVERTEXBUFFERDESC );
		vbdesc.dwCaps			= 0L;
		vbdesc.dwFVF			= vertexFormatD3D;
		vbdesc.dwNumVertices	= numVert;
		if( createFlags & zVBUFFER_CREATE_FLAG_DONOTCLIP )			vbdesc.dwCaps |= D3DVBCAPS_DONOTCLIP;
		if( createFlags & zVBUFFER_CREATE_FLAG_SYSTEMMEMORY )		vbdesc.dwCaps |= D3DVBCAPS_SYSTEMMEMORY;
		if( createFlags & zVBUFFER_CREATE_FLAG_WRITEONLY )			vbdesc.dwCaps |= D3DVBCAPS_WRITEONLY;
		if( zrenderer->HasCapability( zRND_CAP_TNL_HARDWARE )==0 )	vbdesc.dwCaps |= D3DVBCAPS_SYSTEMMEMORY;
		// Erzeugung eines DirectX-Vertexbuffers
		if( !DXTryWarning( zCRnd_D3D::xd3d_pd3d7->CreateVertexBuffer( &vbdesc, &xvb_vertexBuffer, 0 ), "X: [VBD3D]Create: Create VB failed!" ) )
			return FALSE;
	};

	// Merke die Eigenschaften des Vertexbuffers
	this->xvb_vertexFormat	= vtxFormat;
	this->numVertex			= numVert;
	this->numVertsFilled	= 0;
	this->createFlags		= createFlags;

	if( vtxFormat & zVBUFFER_VERTFORMAT_XYZRHW )	
	{
		this->xvb_vertexType = zVBUFFER_VERTTYPE_T_L;	
	} 
	else 
	{
		if( (vtxFormat & zVBUFFER_VERTFORMAT_NORMAL)&&(!(vtxFormat & zVBUFFER_VERTFORMAT_COLOR)) )
			this->xvb_vertexType = zVBUFFER_VERTTYPE_UT_UL;
		else
			this->xvb_vertexType = zVBUFFER_VERTTYPE_UT_L; 
	};

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: Destroy()

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCVertexBuffer_D3D :: Destroy()
{
	//Zerstörung des Vertexbuffers
	//zRELEASE( xvb_vertexBuffer );
	if( xvb_vertexBuffer!=NULL )
	{
		if( xvb_vertexBuffer->Release()!=0 )
			zerr.Warning( "X: Ref-Counter != 0 after vertexbuffer release!" );
	}
	xvb_vertexBuffer	= NULL;
	xvb_locked			= FALSE;
	xvb_optimized		= FALSE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: Lock( zDWORD lockFlags ) 

    14-Aug-00       [PELZER]
    21-Sep-00       [HILDEBRANDT]
					zVBUFFER_LOCK_FLAG_NOSYSLOCK hinzugefuegt

--------------------------------------------------------------------------*/
zBOOL zCVertexBuffer_D3D :: Lock( zDWORD lockFlags ) 
{
	//Lock des DirectX-Vertexbuffers
	if( xvb_vertexBuffer==NULL )
		return FALSE;
	if( xvb_optimized )
		return FALSE;
	if( xvb_locked )
		return TRUE;
	zDWORD lockFlagsD3D = 0;
	if( lockFlags & zVBUFFER_LOCK_FLAG_READONLY )		
		lockFlagsD3D |= DDLOCK_READONLY;
	if( lockFlags & zVBUFFER_LOCK_FLAG_SURFACEMEMORYPTR )
		lockFlagsD3D |= DDLOCK_SURFACEMEMORYPTR;
	if( lockFlags & zVBUFFER_LOCK_FLAG_WAIT )			
		lockFlagsD3D |= DDLOCK_WAIT;
	if( lockFlags & zVBUFFER_LOCK_FLAG_WRITEONLY )		
		lockFlagsD3D |= DDLOCK_WRITEONLY;
	if( lockFlags & zVBUFFER_LOCK_FLAG_DISCARDCONTENTS )	
		lockFlagsD3D |= DDLOCK_DISCARDCONTENTS;
	if( lockFlags & zVBUFFER_LOCK_FLAG_NOOVERWRITE )		
		lockFlagsD3D |= DDLOCK_NOOVERWRITE;
	if( lockFlags & zVBUFFER_LOCK_FLAG_NOSYSLOCK)		
		lockFlagsD3D |= DDLOCK_NOSYSLOCK;

	memset( &array, 0, sizeof( array ) );
	HRESULT hr;
    if( !DXTryWarning( hr = xvb_vertexBuffer->Lock( lockFlagsD3D, (LPVOID*)(&array.basePtr), NULL ), 
			"X: [VBD3D]Lock: Lock VB failed!" ) )
	{
		while( hr==DDERR_SURFACEBUSY )
			hr = xvb_vertexBuffer->Lock( lockFlagsD3D, (LPVOID*)(&array.basePtr), NULL );

		if (hr==DDERR_SURFACELOST) zrenderer->SetSurfaceLost(TRUE);

		if( hr!=D3D_OK )
			return FALSE;
		zERR_MESSAGE( 10,0,"X: [VBD3D]Lock: Locked VB !" );
	}
	//Füllen der Array-Struktur
	zBYTE* ptr = array.basePtr;
	if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_XYZ )		
	{ 
		array.XYZPtr = (zPOINT3*)ptr; 
		ptr += sizeof( *array.XYZPtr );		
	}
	if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_XYZRHW )	
	{ 
		array.XYZRHWPtr	= (zVEC4*)ptr;	 
		ptr += sizeof( *array.XYZRHWPtr );	
	}
	if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_NORMAL )	
	{ 
		array.normalPtr	= (zVEC3*)ptr;	 
		ptr += sizeof( *array.normalPtr );	
	}
	if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_COLOR )	
	{ 
		array.colorPtr	= (zCOLOR*)ptr;	 
		ptr += sizeof( *array.colorPtr );	
	}
	int numTexUV = 0;
	if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_TEXUV1 )	
		numTexUV = 1; 
	else
		if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_TEXUV2 )	
			numTexUV = 2; 
		else
			if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_TEXUV3 )	
				numTexUV = 3; 
			else
				if( xvb_vertexFormat & zVBUFFER_VERTFORMAT_TEXUV4 )	
					numTexUV = 4;
	for( int i = 0; i<numTexUV; i++ )
	{
		array.texUVPtr[i] = (zVEC2*)ptr;	 
		ptr	+= sizeof( *array.texUV0Ptr );	
	}
	//Stride berechnen
	this->arrayStride = ptr - array.basePtr;
	xvb_locked = TRUE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: Unlock() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCVertexBuffer_D3D :: Unlock()
{
	//Unlock des DirectX-Vertexbuffers
	if( xvb_vertexBuffer==NULL )
		return FALSE;
	if( !xvb_locked )
		return TRUE;
	memset( &array, 0, sizeof( array ) );
    if( !DXTryWarning( xvb_vertexBuffer->Unlock(), "X: [VBD3D]Unlock: Unlock VB failed!" ) )
        return FALSE;
	xvb_locked = FALSE;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: Optimize() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCVertexBuffer_D3D :: Optimize()
{
	//Auslösung einer DirectX-internen Optimierung des Vertexbuffers
	if( xvb_vertexBuffer==NULL )	return FALSE;
	if( xvb_optimized )				return TRUE;
	if( !DXTryWarning( xvb_vertexBuffer->Optimize( zCRnd_D3D::xd3d_pd3dDevice7, 0 ), "X: [VBD3D]Optimize: Optimize VB failed!" ) )
        return FALSE;
	xvb_optimized			= TRUE;
	this->numVertsFilled	= this->numVertex;

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: SetPrimitiveType( zTVBufferPrimitiveType primType ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCVertexBuffer_D3D :: SetPrimitiveType( zTVBufferPrimitiveType primType )	
{ 
	//Festlegen des Primitive-Typ
	xvb_primitiveType = primType;
	
	return TRUE; 
}



/*--------------------------------------------------------------------------
	
	zTVBufferPrimitiveType zCVertexBuffer_D3D :: GetPrimitiveType() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTVBufferPrimitiveType zCVertexBuffer_D3D :: GetPrimitiveType()
{ 
	//Rückmeldung des gesetzten Primitive-Typ
	return xvb_primitiveType;		
}



/*--------------------------------------------------------------------------
	
	zDWORD zCVertexBuffer_D3D :: GetVertexFormat() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zDWORD zCVertexBuffer_D3D :: GetVertexFormat() 
{ 
	//Rückmeldung des Vertexformats des Vertexbuffers
	return xvb_vertexFormat; 
}



/*--------------------------------------------------------------------------
	
	zTVBufferVertexType zCVertexBuffer_D3D :: GetVertexType() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zTVBufferVertexType zCVertexBuffer_D3D :: GetVertexType() 
{ 
	//Rückgabe des Vertextyps des Vertexbuffers
	return xvb_vertexType;
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: SetIndexListSize( zDWORD num ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCVertexBuffer_D3D :: SetIndexListSize( zDWORD num )
{
	//Setze die Grösse der Indexliste
	xvb_indexList.AllocAbs( num );
	xvb_indexList.MarkNumAllocUsed();

	return TRUE;
}



/*--------------------------------------------------------------------------
	
	zDWORD zCVertexBuffer_D3D :: GetIndexListSize() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zDWORD zCVertexBuffer_D3D :: GetIndexListSize()
{
	//Rückmeldung der Grösse der Indexliste
	return xvb_indexList.GetNum(); 
}



/*--------------------------------------------------------------------------
	
	zWORD* zCVertexBuffer_D3D :: GetIndexListPtr() 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zWORD* zCVertexBuffer_D3D :: GetIndexListPtr()
{
	//Rückgabe des Pointers auf die Indexliste
	if( xvb_indexList.GetNum()<=0 )	
		return 0;
		
	return xvb_indexList.GetArray();
}



/*--------------------------------------------------------------------------
	
	zBOOL zCVertexBuffer_D3D :: SetIndexList( const zCArray<zWORD>& indexList ) 

 

    14-Aug-00       [PELZER]

--------------------------------------------------------------------------*/
zBOOL zCVertexBuffer_D3D :: SetIndexList( const zCArray<zWORD>& indexList )
{
	//Übergabe der Indexliste
	this->xvb_indexList	= indexList;

	return TRUE;
}