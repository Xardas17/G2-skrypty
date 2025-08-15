/******************************************************************************** 
 
     $Workfile:: zVertexBuffer.cpp    $                $Date:: 16.02.01 5:56    $
     $Revision:: 11                   $             $Modtime:: 16.02.01 5:56    $
       $Author:: Hildebrandt                                                    $
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Vertex Buffer
   created: 25.5.2000

 * $Log: /current_work/ZenGin/_Dieter/zVertexBuffer.cpp $
 * 
 * 11    16.02.01 5:56 Hildebrandt
 * 
 * 10    12.02.01 17:48 Hildebrandt
 * 
 * 9     5.02.01 20:45 Hildebrandt
 * 
 * 8     5.02.01 19:13 Hildebrandt
 * 
 * 7     26.01.01 0:43 Hildebrandt
 * 
 * 6     11.10.00 19:45 Hildebrandt
 * 
 * 5     22.09.00 19:18 Hildebrandt
 * 
 * 4     21.09.00 18:03 Hildebrandt
 * 
 * 3     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 4     9.08.00 17:12 Admin
 * 
 * 2     3.07.00 12:44 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revisio: 2 $ ($Modtime: 16.02.01 5:56 $)

// =======================================================================================================================

#include <zRenderer.h>
#include <zVertexBuffer.h>

zCLASS_DEFINITION_ABSTRACT (zCVertexBuffer	,	zCObject	,	0)

// =======================================================================================================================

zDWORD	zCVertexBuffer::s_classCtorCtr	= 0;

zCVertexBuffer::zCVertexBuffer() 
{
	numVertex					= 0;
	arrayStride					= 0;
	numVertsFilled				= 0;
	vertexBufferID				= s_classCtorCtr++;
	createFlags					= 0;
	memset						(&array, 0, sizeof(array));
};

zCVertexBuffer::~zCVertexBuffer() 
{
	numVertex					= 0;
	arrayStride					= 0;
	memset						(&array, 0, sizeof(array));
};

void zCVertexBuffer::AddRecreateLostVBCallback (zTRecreateLostVBCallback callbackFunc, void *data)
{
	// Nur hinzufuegen, falls nicht bereits vorhanden
	zBOOL alreadThere = FALSE;
	for (int i=0; i<callbackList.GetNum(); i++)
	{
		if ((callbackList[i].recreateLostVBCallback==callbackFunc) &&
			(callbackList[i].recreateLostVBCallbackData==data))
		{	
			alreadThere = TRUE;
			break;
		};
	};
	if (!alreadThere)
	{
		zTCallbackData callbackData;
		callbackData.recreateLostVBCallback		= callbackFunc;
		callbackData.recreateLostVBCallbackData	= data;
		callbackList.Insert						(callbackData);
	};
};

void zCVertexBuffer::RemoveRecreateLostVBCallback (zTRecreateLostVBCallback callbackFunc, void *data)
{
	zERR_ASSERT (callbackFunc);
	for (int i=0; i<callbackList.GetNum(); i++)
	{
		if ((callbackList[i].recreateLostVBCallback==callbackFunc) &&
			(callbackList[i].recreateLostVBCallbackData==data))
		{	
			callbackList.RemoveIndex (i);
			break;
		};
	};
};

zBOOL zCVertexBuffer::CallRecreateLostVBCallbacks()
{
	// VB sollte schon einmal etwas enthalten haben
	zERR_ASSERT_STRICT	(this->GetNumVert()>0);

	// VB erzeugen
	this->Unlock		();
	this->Destroy		();
	this->Create		(this->GetVertexFormat(), this->GetNumVert(), this->createFlags);

	// Liste der Callbacks durchlaufen und aufrufen
	zBOOL result = TRUE;
	for (int i=0; i<callbackList.GetNum(); i++)
	{
		if (callbackList[i].recreateLostVBCallback)
		{
			// VB vom Benutzer-Callback fuellen lassen
			// (ist selber fuer lock/unlock zustaendig)
			result = (callbackList[i].recreateLostVBCallback) (this, callbackList[i].recreateLostVBCallbackData)
						&& result;
		};
	};
	return result;
};

// =======================================================================================================================

zCVertexBufferDyn::zCVertexBufferDyn(const zDWORD _vertexFormat, const zDWORD _numVert)
{
	currentPos					= 0;
	this->flush					= TRUE;
	locked						= FALSE;
	vertexSizeBytes				= 0;
	vertexFormat				= _vertexFormat;
	numVert						= _numVert;

	vertexBuffer				= zrenderer->CreateVertexBuffer ();
	zERR_ASSERT					(vertexBuffer);
	vertexBuffer->Create		(vertexFormat,
								 numVert,
								 zVBUFFER_CREATE_FLAG_WRITEONLY);
};

zCVertexBufferDyn::~zCVertexBufferDyn()
{
	Unlock();
	zRELEASE(vertexBuffer);
}


void* zCVertexBufferDyn::Lock (const zDWORD numVertLocked, zDWORD &startVertIndex)
{
	zERR_ASSERT(vertexBuffer);
	
	startVertIndex		= 0;
	void* pLockedData	= 0;
	
	// Ensure there is enough space in the VB for this data
	if (numVertLocked>vertexBuffer->numVertex) { return 0; }
	
	zDWORD lockFlags = LOCKFLAGS_APPEND;
	
	// If either user forced us to this->flush,
	//  or there is not enough space for the vertex data,
	//  then this->flush the buffer contents
	//
	if (this->flush || ((numVertLocked + currentPos) >= vertexBuffer->numVertex))
	{
		this->flush			= FALSE;
		currentPos		= 0;
		lockFlags		= LOCKFLAGS_FLUSH;
	}
	
	zBOOL res	= vertexBuffer->Lock (lockFlags);
	pLockedData	= vertexBuffer->array.basePtr;
	
	if (res)
	{
		locked			= TRUE;
		startVertIndex	= currentPos;
		currentPos		+= numVertLocked;
		vertexSizeBytes	= vertexBuffer->arrayStride;
	}
	
	return ((void*)(( char*)pLockedData + (startVertIndex) * vertexSizeBytes));
}

void zCVertexBufferDyn::Unlock()
{
	zERR_ASSERT (vertexBuffer);
	if (locked)
	{
		vertexBuffer->Unlock();				
		locked	= FALSE;
	}
}

// =======================================================================================================================

zCVertexBufferDyn2::zCVertexBufferDyn2(const zDWORD _vertexFormat, const zDWORD _numVert)
{
	currentPos					= 0;
	this->flush					= TRUE;
	locked						= FALSE;
	vertexSizeBytes				= 0;
	vertexFormat				= _vertexFormat;
	numVert						= _numVert;

	vertexBuffer				= zrenderer->CreateVertexBuffer ();
	zERR_ASSERT					(vertexBuffer);
	vertexBuffer->Create		(vertexFormat,
								 numVert,
								 zVBUFFER_CREATE_FLAG_WRITEONLY);
};

zCVertexBufferDyn2::~zCVertexBufferDyn2()
{
	Unlock(0);
	zRELEASE(vertexBuffer);
}

void zCVertexBufferDyn2::ReserveVerts (const zDWORD numVertsMax)
{
	if (currentPos + numVertsMax>numVert)	this->flush = TRUE;
};

void* zCVertexBufferDyn2::Lock (zDWORD &startVertIndex)
{
	zERR_ASSERT(vertexBuffer);
	
	startVertIndex		= 0;
	zDWORD lockFlags	= LOCKFLAGS_APPEND;
	
	// If either user forced us to this->flush,
	//  or there is not enough space for the vertex data,
	//  then this->flush the buffer contents
	//
	if (this->flush)
	{
		this->flush		= FALSE;
		currentPos		= 0;
		lockFlags		= LOCKFLAGS_FLUSH;
	}
	
	zBOOL	res			= vertexBuffer->Lock (lockFlags);
	void*	pLockedData	= vertexBuffer->array.basePtr;
	
	if (res)
	{
		locked			= TRUE;
		startVertIndex	= currentPos;
		vertexSizeBytes	= vertexBuffer->arrayStride;
	}
	
	return ((void*)(( char*)pLockedData + (startVertIndex) * vertexSizeBytes));
};

void zCVertexBufferDyn2::Unlock (const zDWORD numVertsUsed)
{
	zERR_ASSERT(vertexBuffer);
	if (locked)
	{
		vertexBuffer->Unlock();				

		locked		= FALSE;
		currentPos	+= numVertsUsed;
		if (currentPos>=numVert)
			this->flush	= TRUE;
	}
};

// =======================================================================================================================

//enum { zVBMAN_STATIC_VB_NUM_VERT	= 4096};
enum { zVBMAN_STATIC_VB_NUM_VERT	= 2048 };
//enum { zVBMAN_STATIC_VB_NUM_VERT	= 0 };

zCVertexBufferManager zvertexBufferMan;

zCVertexBufferManager::~zCVertexBufferManager() 
{
	// Listen sollten hier bereits Leer sein!
	// Falls nicht lief irgendetwas vorher schief!
/*
	zERR_ASSERT (openVBList.GetNum()<=0);
	zERR_ASSERT (closedVBList.GetNum()<=0);
	for (int i=0; i<this->openVBList.GetNum(); i++)		openVBList[i]->Release();
	for (int j=0; j<this->closedVBList.GetNum(); j++)	closedVBList[j]->Release();
*/
};
 
zCVertexBuffer* zCVertexBufferManager::AcquireVertexBuffer (zDWORD	vertexFormat, 
															zDWORD	numVertRequired, 
															zDWORD	createFlags,
															zDWORD	lockFlags,
															int		&indexVertexStart)
{
	// Gibt es in der openVBList einen VB mit dem gewuenschtem Format und ausreichend Platz?
	for (int i=0; i<openVBList.GetNum(); i++)
	{
		zERR_ASSERT			(openVBList[i]->numVertsFilled>=0);
		zERR_ASSERT			(openVBList[i]->numVertsFilled<=openVBList[i]->numVertex);
		zERR_ASSERT_STRICT	(openVBList[i]->IsLocked());

		int vertsAvailable	= (openVBList[i]->GetNumVert() - openVBList[i]->GetNumVertsFilled());
		if ((openVBList[i]->GetVertexFormat()==vertexFormat) &&
			(vertsAvailable>=numVertRequired))
		{
			indexVertexStart				= openVBList[i]->numVertsFilled;
			openVBList[i]->numVertsFilled	+= numVertRequired;
			openVBList[i]->AddRef			();		// refCtr++, diese Ref ist dem Benutzer zugeordnet undwird durch ein zCVertexBufferManager::Release..() aufgeloest
			return openVBList[i];
		};
	};

	// Nein, es wurde kein geeigneter gefunden, also einen neuen erzeugen & locken
	{
		zCVertexBuffer *vertexBuffer	= zrenderer->CreateVertexBuffer ();
//		#ifdef _DEBUG
//			vertexBuffer->SetObjectName (zSTRING("ACQUIRE: ")+zSTRING(vertexBuffer->GetVertexBufferID()));
//		#endif
		int numVert						= (changeWorldHintSet) ? 
										   zMax (numVertRequired, zVBMAN_STATIC_VB_NUM_VERT)
										   :
										   numVertRequired;
		vertexBuffer->Create			(vertexFormat, numVert, createFlags);	// refCtr==1

		if (!vertexBuffer->Lock				(lockFlags))
		{
			zERR_WARNING("C: zCVertexBufferManager::AcquireVertexBuffer(): VB Lock failed!");
		};

		vertexBuffer->numVertsFilled	+= numVertRequired;
		openVBList.Insert				(vertexBuffer);
		indexVertexStart				= 0;
		return vertexBuffer;			// refCtr==1, diese Ref ist dem Benutzer zugeordnet undwird durch ein zCVertexBufferManager::Release..() aufgeloest
	};
};

zBOOL zCVertexBufferManager::ReleaseVertexBuffer (zCVertexBuffer* vertexBuffer)
{
	// Der Benutzer gibt einen benutzten VB und dessen Ref wieder zurueck
	// Rausfinden, in welcher Liste sich der VB befindet, falls gefunden dort entfernen & Release()
	int index	= closedVBList.Search	(vertexBuffer);
	if (index>=0)
	{
		// nur aus Liste loeschen, falls hiermit die letzte Ref aufgeloest wird!
		if (vertexBuffer->GetRefCtr()==1)			
			closedVBList.RemoveIndex	(index);
		zRELEASE						(vertexBuffer);
	} else
	{
		index = openVBList.Search		(vertexBuffer);
		if (index>=0)
		{
			// nur aus Liste loeschen, falls hiermit die letzte Ref aufgeloest wird!
			if (vertexBuffer->GetRefCtr()==1)
				openVBList.RemoveIndex	(index);
			zRELEASE					(vertexBuffer);
		};
	};

	return TRUE;
};

void zCVertexBufferManager::UnlockOpenVertexBuffers()
{
	for (int i=0; i<closedVBList.GetNum(); i++)
	{
		// hmmm... so ganz schoen ist das hier nicht. In der ClosedList koennten nach einem Renderer Abriss
		// und den daraus folgenden VB-Destroys noch unlocked VBs befinden, die im ReCreateCallback neu erzeugt
		// und gelockt wurden, aber nirgends sonst unlocked. Das geschieht hier dann. 
		// (eher ein workaround, siehe Anmerkung am Ende der zCVertexBufferManager Implementation)
		if (closedVBList[i]->IsLocked())
		{
			closedVBList[i]->Unlock			();
			closedVBList[i]->Optimize		();		// FIXME: was bei DynVBs ?
		};
	};
	while (openVBList.GetNum()>0)
	{
		// Unlock
		zERR_ASSERT_STRICT				(openVBList[0]->IsLocked());
		openVBList[0]->Unlock			();
		openVBList[0]->Optimize			();		// FIXME: was bei DynVBs ?
		closedVBList.Insert				(openVBList[0]);
		openVBList.RemoveIndex			(0);
	};
};

void zCVertexBufferManager::StartChangeWorld		()
{
	changeWorldHintSet		= TRUE;
};

void zCVertexBufferManager::EndChangeWorld			()
{
	changeWorldHintSet		= FALSE;
	UnlockOpenVertexBuffers	();
};

// =======================================================================================================================

/*
	- VB Benutzung ueber den VBManager ist noch nicht sicher genug, es gibt zu viele Moeglichkeiten etwas falsch zu
	  machen. Besser:
		- alles TopDown machen, alle wichtigen organisatorischen Methoden *muessen* ueber den VBMan laufen, und sind
		  dann im VB selbst private
*/