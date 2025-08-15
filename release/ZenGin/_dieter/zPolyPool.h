/******************************************************************************** 
 
     $Workfile:: zpolypool.h          $                $Date:: 2.02.01 17:53    $
     $Revision:: 9                    $             $Modtime:: 2.02.01 13:24    $
        Author:: Hoeller                                                    
    Subproject:: zenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created: ?.2000

 * $Log: /current_work/ZenGin/_Dieter/zpolypool.h $
 * 
 * 9     2.02.01 17:53 Moos
 * 
 * 8     27.01.01 19:42 Moos
 * 
 * 7     4.12.00 17:29 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hoeller
/// @version $Revisio: 2 $ ($Modtime: 2.02.01 13:24 $)

// =======================================================================================================================

#ifdef MEMPOOL_HOELLER

#ifndef __ZPOLYGONPOOL_H__
#define __ZPOLYGONPOOL_H__

#include <windows.h>

#ifndef __ZSTRING_H__
#include <zString.h>
#endif

#ifndef __ZTYPES_H__
#include <zTypes.h>
#endif

#ifndef __ZTYPES3D_H__
#include <zTypes3D.h>
#endif

#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

#ifndef __ZCONTAINER_H__
#include <zContainer.h>
#endif

#ifndef __ZARCHIVE2CONTAINER_H__
#include <tchar.h>
#include "zArchive2container.h"
#endif

#ifndef __Z3D_H__
#include "z3d.h"
#endif

#ifndef __ZVISUAL_H__
#include "zvisual.h"
#endif

// =======================================================================================================================


//zCVertFeature
///////////////////////////////////////////////////////////////////////////
//     Mesh
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//		Meshpool class
///////////////////////////////////////////////////////////////////////////


class zCVertexFeaturePool
{
protected:
	GETSmallArrayNative<zCVertFeature>	*Pool;
	GETSmallArrayNative<zCVertFeature*>	*PtrPool;
	int									NumOfAllocatedVertexFeatures;
public:
	zCVertexFeaturePool()
	{
		NumOfAllocatedVertexFeatures = 0;
		Pool = zNEW(GETSmallArrayNative<zCVertFeature>);
		PtrPool = zNEW(GETSmallArrayNative<zCVertFeature*>);
	}

	~zCVertexFeaturePool()
	{
		delete Pool;
		delete PtrPool;
	}

	int			AllocNewVertexFeatures(int numOfVertFeatures)
	{
		Pool->Reserve(Pool->Used + numOfVertFeatures);
		PtrPool->Reserve(Pool->Used + numOfVertFeatures);
		return int(Pool->Used);
	}

	int			AddVertexFeature(zCVertFeature &vertFeature)
	{
		int iPos = Pool->Add(vertFeature);
		zCVertFeature *ptrVFeat = &Pool->Entry[iPos];
		PtrPool->Add(ptrVFeat);
		return iPos;

	}

	void		DeleteVertexFeature(int index)
	{
		Pool->Remove(index);
		PtrPool->Remove(index);
	}
	
	void		ClearVertexFeatures()
	{
		Pool->Used = 0;
		PtrPool->Used = 0;
	}

	zCVertFeature&	GetVertexFeature(int index)
	{
		assert(index<Pool->Used);
		return Pool->Entry[index];
	}


	int			GetVertexFeatureCount()
	{
		return Pool->Used;
	}

	zCVertFeature*	GetVertexFeaturePtrList()
	{
		return Pool->Entry;
	}


	zCVertFeature**	GetVertexFeaturePtrPtrList()
	{
		return PtrPool->Entry;
	}

	void		AddNewVertFeature(int vertFeatureNum) {NumOfAllocatedVertexFeatures += vertFeatureNum;}
	void		SubtractNumVertFeatures(int vertFeatureNum) {NumOfAllocatedVertexFeatures -= vertFeatureNum;}
	int			GetNumberOfAllocatedVertexFeatures() {return NumOfAllocatedVertexFeatures;}
};


class zCPolygonPool
{
protected:
	GETSmallArrayNative<zCPolygon>	*Pool;
	int								NumOfAllocatedPolygon;
public:
	zCPolygonPool()
	{
		NumOfAllocatedPolygon = 0;
		Pool = zNEW(GETSmallArrayNative<zCPolygon>);
	}

	~zCPolygonPool()
	{
		int i = Pool->Used;
		if(i>0) while(i--)
		{
			Pool->Entry[i].~zCPolygon();
		}
		delete Pool;
	}

	int			AllocNewPolygons(int numOfPoly)
	{
		Pool->Reserve(Pool->Used + numOfPoly);
		return int(Pool->Used);
	}

	int			AddPolygon(zCPolygon &poly)
	{
		return Pool->Add(poly);
	}

	void		DeletePolygon(int index)
	{
		Pool->Entry[index].~zCPolygon();
		Pool->Remove(index);
	}

	zCPolygon*	GetPolygonPtr(int index)
	{
		if(index>=Pool->Used) return NULL;
		return &Pool->Entry[index];
	}
	
	int			GetPolygonCount()
	{
		return Pool->Used;
	}

	zCPolygon*	GetPolygonPtrList()
	{
		return Pool->Entry;
	}

	void		AddNewPolys(int polyNum) {NumOfAllocatedPolygon += polyNum;}
	void		SubtractNumPolys(int polyNum) {NumOfAllocatedPolygon -= polyNum;}
	int			GetNumberOfAllocatedPolys() {return NumOfAllocatedPolygon;}
};

class zCVertexPool
{
protected:
	GETSmallArrayNative<zCVertex>*	Pool;
	GETSmallArrayNative<zCVertex*>	*PtrPool;
	int								NumOfAllocatedVertex;
public:
	zCVertexPool()
	{
		NumOfAllocatedVertex = 0;
		Pool = zNEW(GETSmallArrayNative<zCVertex>);
		PtrPool = zNEW(GETSmallArrayNative<zCVertex*>);
	}

	~zCVertexPool()
	{
		delete Pool;
		delete PtrPool;
	}

	int			AllocNewVerticesPtr(int numOfVert)
	{
		PtrPool->Reserve(PtrPool->Used + numOfVert);
		return int(PtrPool->Used);
	}

	int			AllocNewVertices(int numOfVert)
	{
		Pool->Reserve(Pool->Used + numOfVert);
		//PtrPool->Reserve(PtrPool->Used + numOfVert);
		return int(Pool->Used);
	}

	int			AddVertex(zCVertex &vert)
	{
		int iPos = Pool->Add(vert);
		zCVertex *ptrVertex = &Pool->Entry[iPos];
		PtrPool->Add(ptrVertex);
		return iPos;
	}

	int			AddVertexPtr(zCVertex* ptrVertex)
	{
		return PtrPool->Add(ptrVertex);
	}


	zCVertex&	GetVertex(int index)
	{
		assert(index<Pool->Used);
		return Pool->Entry[index];
	}
	
	int			GetVertexCount()
	{
		return Pool->Used;
	}

	zCVertex*	GetVertexPtrList()
	{
		return Pool->Entry;
	}
	zCVertex**	GetVertexPtrPtrList()
	{
		return PtrPool->Entry;
	}

	void		AddNewVertex(int polyNum) {NumOfAllocatedVertex += polyNum;}
	void		SubtractNumVertex(int polyNum) {NumOfAllocatedVertex -= polyNum;}
	int			GetNumberOfAllocatedVertex() {return NumOfAllocatedVertex;}
};

class zCMeshPool
{
protected:
	zCVertexPool*			vertexPool;
	zCPolygonPool*			polygonPool;
	zCVertexFeaturePool*	vertexFeaturePool;
	int				meshIndex;
	zCMesh*			meshObject;
public:
	zCMeshPool(int index, zCMesh* mesh)
	{
		vertexPool = zNEW(zCVertexPool);
		polygonPool = zNEW(zCPolygonPool);
		vertexFeaturePool = zNEW(zCVertexFeaturePool);
		meshIndex = index;
		meshObject = mesh;
	}
	~zCMeshPool()
	{
		delete polygonPool;
		delete vertexPool;
		delete vertexFeaturePool;
	}

	int			GetMeshIndex() {return meshIndex;}
	zCMesh*		GetMeshObject() {return meshObject;}

	int			AddVertex(zCVertex* vertex) 
	{
		zCVertex *oldVPtr = vertexPool->GetVertexPtrList();
		zCVertex **oldVPtrPtr = vertexPool->GetVertexPtrPtrList();
		int result = vertexPool->AddVertex(*vertex);
		if(oldVPtr!=vertexPool->GetVertexPtrList())
		{
			int i = vertexPool->GetVertexCount();
			if(i>0) while(i--)
			{
				meshObject->VertexWritable(i) = &vertexPool->GetVertex(i);
				vertexPool->GetVertexPtrPtrList()[i] = &vertexPool->GetVertexPtrList()[i];
			}
		}
		if(oldVPtrPtr!=vertexPool->GetVertexPtrPtrList())
		{
			// recalc internal vertexaddresses
			int i = polygonPool->GetPolygonCount();
			if(i>0) while(i--)
			{
				zCPolygon *polygon = polygonPool->GetPolygonPtr(i);
				if(polygon->vertex!=NULL)
				{
					int ptrOffs = int(polygon->vertex) - int(oldVPtrPtr);
					ptrOffs = ptrOffs >> 2;
					polygon->vertex = vertexPool->GetVertexPtrPtrList() + ptrOffs;
				}
			}
		}
		return result;
	}
	zCVertex*	GetVertex(int index) {return &vertexPool->GetVertex(index);}
	void		AllocateVertices(int numVert)
	{
		//zERR_WARNING		("OH: MeshIndex(vertex)#" + zSTRING(meshObject->poolIndex) + " allocated bytes: " + zSTRING(numVert * int(sizeof(zCVertex))));
		zCVertex *oldVPtr = vertexPool->GetVertexPtrList();
		zCVertex **oldVPtrPtr = vertexPool->GetVertexPtrPtrList();

		vertexPool->AllocNewVertices(numVert);
		
		//if(meshObject->vertList!=NULL)
		if(oldVPtr!=vertexPool->GetVertexPtrList())
		{
			int i = vertexPool->GetVertexCount();
			if(i>0) while(i--)
			{
				meshObject->VertexWritable(i) = &vertexPool->GetVertex(i);
				vertexPool->GetVertexPtrPtrList()[i] = &vertexPool->GetVertexPtrList()[i];
			}
		}

		if(oldVPtrPtr!=vertexPool->GetVertexPtrPtrList())
		{
			// recalc internal vertexaddresses
			int i = polygonPool->GetPolygonCount();
			if(i>0) while(i--)
			{
				zCPolygon *polygon = polygonPool->GetPolygonPtr(i);
				if(polygon->vertex!=NULL)
				{
					int ptrOffs = int(polygon->vertex) - int(oldVPtrPtr);
					ptrOffs = ptrOffs >> 2;
					polygon->vertex = vertexPool->GetVertexPtrPtrList() + ptrOffs;
				}
			}
		}
	}
	
	int			GetVertexCount()
	{
		return vertexPool->GetVertexCount();
	}
	
	zCVertexPool*	GetVertexPool()
	{
		return vertexPool;
	}

	zCPolygonPool*	GetPolygonPool()
	{
		return polygonPool;
	}

	zCVertexFeaturePool* GetVertexFeaturePool()
	{
		return vertexFeaturePool;
	}
	
	int			AddPolygon(zCPolygon* polygon) 
	{
		zCPolygon *oldPPtr = polygonPool->GetPolygonPtrList();
		int result = polygonPool->AddPolygon(*polygon);
		if(meshObject->PolyList()!=NULL)
		{
			if(oldPPtr!=polygonPool->GetPolygonPtrList())
			{
				int i = polygonPool->GetPolygonCount();
				if(i>0) while(i--)
				{
					meshObject->PolyWritable(i) = polygonPool->GetPolygonPtr(i);
				}
			}
		}
		return result;
	}
	void		RemovePolygon(int index) {polygonPool->DeletePolygon(index);}
	zCPolygon*	GetPolygon(int index) {return polygonPool->GetPolygonPtr(index);}
	void		AllocatePolygons(int numPoly)
	{
		//zERR_WARNING		("OH: MeshIndex(polys)#" + zSTRING(meshObject->poolIndex) + " allocated bytes: " + zSTRING(numPoly * int(sizeof(zCPolygon))));
		zCPolygon *oldPPtr = polygonPool->GetPolygonPtrList();
		polygonPool->AllocNewPolygons(numPoly);
		if(meshObject->PolyList()!=NULL)
		{
			if(oldPPtr!=polygonPool->GetPolygonPtrList())
			{
				int i = polygonPool->GetPolygonCount();
				if(i>0) while(i--)
				{
					meshObject->PolyWritable(i) = polygonPool->GetPolygonPtr(i);
				}
			}
		}
	}
	int			GetPolygonCount()
	{
		return polygonPool->GetPolygonCount();
	}

	void		ClearAll()
	{
		delete vertexPool;
		delete polygonPool;
		delete vertexFeaturePool;
		vertexPool = zNEW(zCVertexPool);
		polygonPool = zNEW(zCPolygonPool);
		vertexFeaturePool = zNEW(zCVertexFeaturePool);

	}

	
	int					AddVertexFeature(zCVertFeature* vertexFeature) 
	{
		return vertexFeaturePool->AddVertexFeature(*vertexFeature);
	}
	
	zCVertFeature*		GetVertexFeature(int index) 
	{
		return &vertexFeaturePool->GetVertexFeature(index);
	}
	
	void		AllocateVertexFeatures(int numVert)
	{
		//zERR_WARNING		("OH: MeshIndex(vertexFeature)#" + zSTRING(meshObject->poolIndex) + " allocated bytes: " + zSTRING(numVert * int(sizeof(zCVertFeature))));
		zCVertFeature *oldVPtr = vertexFeaturePool->GetVertexFeaturePtrList();
		zCVertFeature **oldVPtrPtr = vertexFeaturePool->GetVertexFeaturePtrPtrList();

		// Realloc isn´t safe here?
		vertexFeaturePool->AllocNewVertexFeatures(numVert);
		if(oldVPtr!=vertexFeaturePool->GetVertexFeaturePtrList())
		{
			int i = vertexFeaturePool->GetVertexFeatureCount();
			if(i>0) while(i--)
			{
				vertexFeaturePool->GetVertexFeaturePtrPtrList()[i] = &vertexFeaturePool->GetVertexFeaturePtrList()[i];
			}
		}			

			
		if(oldVPtrPtr!=vertexFeaturePool->GetVertexFeaturePtrPtrList())
		{
			// recalc internal polygonaddresses
			int i = polygonPool->GetPolygonCount();
			if(i>0) while(i--)
			{
				zCPolygon *polygon = polygonPool->GetPolygonPtr(i);
				if(polygon->feature!=NULL)
				{
					int ptrOffs = int(polygon->feature) - int(oldVPtrPtr);
					ptrOffs = ptrOffs >> 2;
					polygon->feature = vertexFeaturePool->GetVertexFeaturePtrPtrList() + ptrOffs;
				}
			}
		}

	}

	int			GetVertexFeatureCount()
	{
		return vertexFeaturePool->GetVertexFeatureCount();
	}


};

class zCMeshesPool
{
protected:
	zBOOL								IsActive;
	GETSmallArrayNative<zCMeshPool*>	*pool;
public:
	zCMeshesPool()
	{
		pool = zNEW(GETSmallArrayNative<zCMeshPool*>);
		zSTRING str(GetCommandLine());
		str.Lower();
		if(str.Search("-zpolypool")!=-1)
			IsActive = TRUE;
		else
			IsActive = FALSE;
	}

	~zCMeshesPool()
	{
		ClearAllMeshes();
		delete pool;
	}

	zBOOL		IsPoolActive()
	{
		return IsActive;
	}

	zBOOL		DeleteMesh(int index)
	{
		if(index>=pool->Used)	
			return FALSE;

		delete pool->Entry[index];
		for(int i=index+1;i<pool->Used;i++)
			pool->Entry[i]->GetMeshObject()->poolIndex--;
		pool->Remove(index);
		return TRUE;
	}

	int			CreateAndAddMesh(zCMesh *meshObject)
	{
		zCMeshPool* meshPool = zNEW(zCMeshPool(pool->Used, meshObject));
		return pool->Add(meshPool);
	}

	zCMeshPool*	GetMesh(int index)
	{
		if(index>=pool->Used) 
			return NULL;
		return pool->Entry[index];
	}

	void		ClearAllMeshes()
	{
		int i = pool->Used;
		if(i>0) while(i--)
		{
			delete pool->Entry[i];
			pool->Entry[i] = NULL;
		}
		pool->Used = 0;
	}
};

zCMeshesPool& GetMeshesPool();

#endif

#endif