/******************************************************************************** 
 
     $Workfile:: zMesh.cpp            $                $Date:: 9.02.01 18:42    $
     $Revision:: 60                   $             $Modtime:: 9.02.01 16:58    $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zMesh.cpp $
 * 
 * 60    9.02.01 18:42 Moos
 * VertexFeature-Sharing beim Laden aktiviert
 * 
 * 59    9.02.01 15:15 Moos
 * 
 * 58    9.02.01 13:24 Moos
 * 
 * 57    6.02.01 22:24 Wohlers
 * 
 * 56    6.02.01 19:24 Moos
 * 
 * 55    6.02.01 18:49 Hildebrandt
 * 
 * 54    2.02.01 17:53 Moos
 * 
 * 53    2.02.01 0:20 Hildebrandt
 * 
 * 52    1.02.01 20:59 Hildebrandt
 * 
 * 51    1.02.01 20:59 Hildebrandt
 * 
 * 50    1.02.01 19:58 Moos
 * 
 * 49    28.01.01 12:30 Moos
 * 
 * 48    27.01.01 19:42 Moos
 * 
 * 47    27.01.01 13:02 Moos
 * 
 * 46    26.01.01 13:08 Moos
 * 
 * 45    25.01.01 18:08 Moos
 * 
 * 44    25.01.01 12:14 Moos
 * 
 * 43    24.01.01 14:57 Moos
 * 
 * 42    23.01.01 14:33 Moos
 * 
 * 41    9.01.01 14:54 Moos
 * 
 * 40    13.12.00 19:13 Moos
 * 
 * 39    6.12.00 23:34 Hildebrandt
 * 
 * 38    6.12.00 18:01 Moos
 * 
 * 37    5.12.00 17:15 Hildebrandt
 * 
 * 36    5.12.00 9:58 Moos
 * 
 * 35    4.12.00 20:26 Hildebrandt
 * 
 * 34    4.12.00 18:23 Moos
 * 
 * 33    22.11.00 19:59 Moos
 * 
 * 32    17.11.00 19:29 Moos
 * 
 * 31    3.11.00 19:02 Hildebrandt
 * 
 * 30    25.10.00 15:06 Hildebrandt
 * 
 * 29    18.10.00 13:52 Hoeller
 * 
 * 28    13.10.00 10:37 Moos
 * 
 * 27    12.10.00 13:41 Hoeller
 * 
 * 26    11.10.00 21:00 Hoeller
 * 
 * 25    11.10.00 19:39 Hildebrandt
 * 
 * 24    11.10.00 17:20 Hoeller
 * 
 * 23    11.10.00 13:17 Moos
 * 
 * 22    10.10.00 17:20 Hoeller
 * 
 * 21    10.10.00 13:23 Hoeller
 * 
 * 20    11.09.00 19:40 Speckels
 * 
 * 19    29.08.00 16:05 Hildebrandt
 * zengin 92j
 * 
 * 18    21.08.00 17:18 Hildebrandt
 * 
 * 17    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 18    9.08.00 17:12 Admin
 * 
 * 16    21.07.00 15:11 Hildebrandt
 * 
 * 15    21.07.00 14:28 Hildebrandt
 * 
 * 14    6.07.00 13:45 Hildebrandt
 * 
 * 8     9.05.00 21:14 Hildebrandt
 * zenGin 089h
 * 
 * 7     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 6     4.05.00 22:15 Hildebrandt
 * 
 * 5     4.05.00 20:17 Hildebrandt
 * zenGin 089e
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 16    22.03.00 22:59 Hildebrandt
 * 
 * 15    22.03.00 2:59 Hildebrandt
 * zenGin 088a
 * 
 * 14    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 13    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 12    20.02.00 18:08 Hildebrandt
 * zenGin 087c
 * 
 * 11    19.02.00 19:28 Hildebrandt
 * tmp hack: meshes are lit flat according to daytime
 * 
 * 10    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 8     11.01.00 20:59 Hildebrandt
 * zenGin 085b
 * 
 * 7     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     16.11.99 19:49 Hildebrandt
 * 
 * 4     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 60 $ ($Modtime: 9.02.01 16:58 $)


#include <zCore.h>
#include <zWorld.h>
#include <z3d.h>
#include "zoption.h"
#include <zFile3d.h>
#include <zArchiver.h>
#include <zSky.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zSparseArray.h>
#include <zContainer.h>

#pragma warning( disable: 4244 ) 


zCLASS_DEFINITION( zCMesh, zCVisual, 0,1)

// custom includings
#include <string.h>
#include <tchar.h>

#include "zArchive2container.h"
#include "zpolypool.h"

// foward declarations
static int Compare_Verts_Merge(const void *arg1, const void *arg2);
static int Compare_Features   (const void *arg1, const void *arg2);

///////////////////////////////////////////////////////////////////////////
//     Mesh
///////////////////////////////////////////////////////////////////////////
// =========================================================================================================

int		zCMesh::s_numMeshes			= 0;
zCMesh* zCMesh::s_meshRoot			= 0;
zBOOL	zCMesh::s_autoConvertMeshes	= FALSE;
zBOOL	zCMesh::s_usesVertexCache	= FALSE;
zBOOL   s_bAddVobsToMesh			= FALSE;

zCArraySort<zCVertex*>	zCMesh::s_vertexCache;

zCMesh::zCMesh() {
    numPoly	        = 0;
    numVert	        = 0;
    numFeat         = 0;
    vertList	    = 0;
    polyList        = 0;
    featList        = 0;
    vertArray       = 0;
    polyArray       = 0;
    featArray       = 0;
    masterFrameCtr  = 0;
    numVertAlloc    = 0;
    numPolyAlloc    = 0;
    hasLightmaps    = FALSE;
    //	refCtr			= 1;
    bbox3D.mins		= zVEC3(0,0,0);
    bbox3D.maxs		= zVEC3(0,0,0);
    s_numMeshes++;

#ifdef MEMPOOL_HOELLER
    if(GetMeshesPool().IsPoolActive()==FALSE)
      	poolIndex = -1;
    else
    	poolIndex		= GetMeshesPool().CreateAndAddMesh(this);
#endif

    // insert into list
    prev			= 0;
    next			= s_meshRoot;
    if (s_meshRoot!=0)
	s_meshRoot->prev= this;
    s_meshRoot		= this;
    //
    meshName = "#"+zSTRING((int)s_numMeshes);		// safety
	SetAlphaTestingEnabled(FALSE);
};

zCMesh::~zCMesh() 
{
	s_numMeshes--;
	DeleteAll();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		assert(poolIndex!=-1);  // must not be  -1 !
		if(GetMeshesPool().DeleteMesh(poolIndex)==FALSE)
		{
			zERR_FAULT("OH: couldn´t delete mesh with poolindex: " + zSTRING(poolIndex) + "from MeshPool");
		}
	}
#endif
//	refCtr--;
//	if (refCtr!=0)	zerr.Report (zERR_FATAL, 1000, "D:z3D(zCMesh::Destructor): Reference-Ctr not zero !");
	
	// delete contents

	// delete from list
	if (this==s_meshRoot) s_meshRoot = next; else
	if (prev) prev->next	= next;
	if (next) next->prev	= prev;
	next = prev = 0;
};

//static const zSTRING meshFileExt[2] = { ".3DS", ".BSP" };
static const zSTRING meshFileExt[1] = { ".BSP" };

const zSTRING* zCMesh::GetFileExtension (int i)
{
//	if ((i<0) || (i>1))	return 0;
//	return &(meshFileExt[i]);
	if (i!=0) return 0;
	return &(meshFileExt[0]);
};

zCVisual* zCMesh::LoadVisualVirtual (const zSTRING& visualName) const
{
	return zCMesh::Load (visualName);
};

void zCMesh::DeleteAll ()
{
    ClearLists();

#ifdef MEMPOOL_HOELLER
    if (GetMeshesPool().IsPoolActive()==FALSE){ // [Moos] nur bei aktiven Pools darf man das nicht machen
#endif
    int i;

	if (featList || featArray){
	    // shared features! Damit die Poly-Destruktoren keinen Müll bauen, müssen wir ihre Featurelisten von Hand abbauen.
	    if (polyList)
    		for (i=0; i<numPoly; i++){
    		    zCPolygon::S_DeletePointers(polyList[i]->polyNumVert, polyList[i]->feature);
    		    polyList[i]->feature = NULL;
    		}
	    else if (polyArray)
    		for (i=0; i<numPoly; i++){
    		    zCPolygon::S_DeletePointers(polyArray[i].polyNumVert, polyArray[i].feature);
		        polyArray[i].feature = NULL;
		    }
    	}
	
	if (vertList)
	    for (i=0; i<numVert; i++) delete vertList[i];
	if (featList)
	    for (i=0; i<numFeat; i++) delete featList[i];
	if (polyList)
	    for (i=0; i<numPoly; i++) delete polyList[i];

#ifdef MEMPOOL_HOELLER
    }
#endif

	delete[] vertList;	vertList = 0;
	delete[] polyList;	polyList = 0;
	delete[] featList;	featList = 0;

	delete[] vertArray;	vertArray = 0;
	delete[] polyArray;	polyArray = 0;
	delete[] featArray;	featArray = 0;

	numPoly	        = numVert       = numFeat = 0;
	numPolyAlloc    = numVertAlloc	= 0;

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		assert(poolIndex!=-1);
		GetMeshesPool().GetMesh(poolIndex)->ClearAll();
	}
#endif
	// like a virgin.. now
};

zCMesh*	zCMesh::SearchName (const zSTRING& name) {
	// FIXME: bin-Search
	zCMesh *mesh = s_meshRoot;
	while ((mesh) && (mesh->meshName!=name)) 
		mesh = mesh->next;
	return mesh;
};

zCMesh* zCMesh::Load (const zSTRING& meshFileName,const zBOOL a_bDontConvertToNPolys) 
{
	// lädt mesh von disk (3ds,bsp,...) falls nicht bereits im Speicher
	// Input-Filename: gross/klein egal, enthaltener Pfad wird zuerst benutzt, Ext wird benutzt
	// alt: meshName: Pfad (rel ab MESHES), filename, ext
	// meshName: filename, ext

	zSTRING fileName(meshFileName);
	fileName.Upper();
	zPATH meshPath	(fileName);
	zCMesh *mesh = SearchName (meshPath.GetFilename()+"."+meshPath.GetExt());

	if (mesh) {
		mesh->AddRef();
	} else {
		// create new mesh & load
		// mesh bereits im internen Format ?

		if (zCMaterial::GetUsageDefault	()!=zCMaterial::zMAT_USAGE_LEVEL) 
		{
			zoptions->ChangeDir	(DIR_COMPILED_MESHES);
			zFILE* file = zfactory->CreateZFile(meshPath.GetFilename()+".MSH");
			zBOOL ok	= FALSE;
			if (file->Exists()) {
				mesh		= zNEW(zCMesh);
				ok			= mesh->LoadMSH (meshPath.GetFilename()+".MSH", FALSE);
                mesh->SortPolysByMaterial();
			};
			delete file;
			if (ok) goto goOn;
		}

		// importieren und im internen Format speichern
		{
			zBOOL found = FALSE;
			zoptions->ChangeDir	(DIR_MESHES);
			{
				zFILE* file	= zfactory->CreateZFile(fileName);
				if (file->Exists()) found = TRUE;
				delete file; file=0;

				if (!found) 
				{
					// FIXME: spaeter evtl. erst im _COMPILED suchen
					zoptions->ChangeDir (DIR_MESHES);
					fileName = meshPath.GetFilename() + "." + meshPath.GetExt();
					zPATH path;
					if (path.SearchFile(fileName, zSTRING(zFILE::GetCurrentDir()))==zERR_NONE) {
						// Mesh gefunden !
						// relativen Pfad erzeugen
						const zSTRING& relDir	= path.GetDir().Deleted (zoptions->GetDirString (DIR_MESHES), zSTR_TO);						
						fileName				= relDir + fileName;
						found					= TRUE;
						// jetzt mit dem vollen-Pfad & Name nochmals im Speicher suchen..
						fileName.Upper();
						zCMesh *mesh2 = SearchName (fileName);
						if (mesh2) {
							zRELEASE(mesh);		// falls vorhanden
							mesh2->AddRef();
							mesh = mesh2;
							goto goOn;
						};
					};
				};
			}

			if (found) {
				if (!mesh) mesh = zNEW(zCMesh);
				if (meshPath.GetExt().Search("3DS")!=-1) {
					zCFile3DS meshFile;
					meshFile.Load3DS  (fileName, mesh);
				} else if (meshPath.GetExt().Search("BSP")!=-1) {
					zCFileQuakeBSP meshFile;
					meshFile.LoadQuakeBSP (fileName, mesh, 0);
				};
				if (mesh) {
					// Level-Mesh: nicht konvertieren !
					if (zCMaterial::GetUsageDefault	()!=zCMaterial::zMAT_USAGE_LEVEL) {
                        if (!a_bDontConvertToNPolys)  mesh->ConvertTrisToNPolys	();
						mesh->SaveMSH				(meshPath.GetFilename()+".MSH");
					};
				};
			};
		};
	};
goOn:;
	if (!mesh)	
		zERR_WARNING ("D: z3d(zCMesh::Load): Could not load Mesh: "+meshFileName);
	return mesh;
};


void zCMesh::S_InitVertexMergeCache(zCMesh* a_pMesh)
{
	zERR_MESSAGE(6,0, "C: Meshmagic: Initializing cache for vertex merging");
	s_vertexCache.DeleteList();
	
	s_vertexCache.SetCompare(Compare_Verts_Merge);
	// alle gespeicherten verts (falls vorhanden) 
	// in die neue sortierte liste kopieren
	for (int i=0; i<a_pMesh->numVert; i++) s_vertexCache.InsertSort(a_pMesh->vertList[i]);
	s_usesVertexCache = TRUE;
}

void zCMesh::S_DeleteVertexMergeCache()
{
	s_vertexCache.DeleteList();
	s_usesVertexCache = FALSE;
}


zCVertex* zCMesh::VertexInMesh (const zPOINT3& v) 
{
    ArraysToLists();

	if (s_usesVertexCache) 
	{
		static zCVertex s_compareVert;
		s_compareVert.position = v;
		int vertIndex = s_vertexCache.Search(&s_compareVert);
		if (vertIndex == -1) return FALSE;
		return s_vertexCache[vertIndex];
	}

	int i;
	for (i=0; i<numVert; i++) 
	{
		const zVALUE ALMOST_ZERO = 0.01F;		// = cm
		const zPOINT3& p1 = vertList[i]->position;
		if ((zAbs(p1.n[VX] - v.n[VX]) < ALMOST_ZERO) &&
			(zAbs(p1.n[VY] - v.n[VY]) < ALMOST_ZERO) &&
			(zAbs(p1.n[VZ] - v.n[VZ]) < ALMOST_ZERO)) return vertList[i];

	};
	return FALSE;
}

// Alloc-Num : plus-delta

void zCMesh::AllocVerts (int num) 
{
    ArraysToLists();

// old behavior for spacer
#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		if (num<=0) num=1;
		GetMeshesPool().GetMesh(poolIndex)->AllocateVertices(num);	
		zCVertex **newVertList;
		newVertList = zNEW(zCVertex*) [numVertAlloc+num];
		if (numVert!=0)		 memcpy (newVertList, vertList, sizeof( zCVertex* )*numVert );
		if (numVertAlloc!=0) delete[] vertList;
		vertList = newVertList;
		numVertAlloc += num;
	}
	else
#endif
	{
		if (num<=0) num=1;

        zCVertex::PreAlloc(num);  // [Moos] für die generische MemPool-Klasse

		zCVertex **newVertList;
		newVertList = zNEW(zCVertex*) [numVertAlloc+num];
		if (numVert!=0)		 memcpy (newVertList, vertList, sizeof( zCVertex* )*numVert );
		if (numVertAlloc!=0) delete[] vertList;
		vertList = newVertList;
		numVertAlloc += num;
	}
//	zerr.Message ("D: AllocVerts "+zSTRING(numVertAlloc));
}

void zCMesh::AllocPolys (int num) 
{
    CreateListsFromArrays();

    if (polyArray){
    	zCPolygon::PoolAdd(polyArray, numPoly); (zCPolygon *&)polyArray = NULL;
    }

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		if (num<=0) num=1;
		GetMeshesPool().GetMesh(poolIndex)->AllocatePolygons(num);	
		zCPolygon **newPolyList;
		newPolyList = zNEW(zCPolygon*) [numPolyAlloc+num];
		if (numPoly!=0)		 memcpy (newPolyList, polyList, sizeof( zCPolygon* )*numPoly);
		if (numPolyAlloc!=0) delete[] polyList;
		polyList = newPolyList;
		numPolyAlloc += num;
	}
	else
#endif
	{
		if (num<=0) num=1;

        zCPolygon::PreAlloc(num);  // [Moos] für die generische MemPool-Klasse

		zCPolygon **newPolyList;
		newPolyList = zNEW(zCPolygon*) [numPolyAlloc+num];
		if (numPoly!=0)		 memcpy (newPolyList, polyList, sizeof( zCPolygon* )*numPoly);
		if (numPolyAlloc!=0) delete[] polyList;
		polyList = newPolyList;
		numPolyAlloc += num;
	}
}

zCVertex* zCMesh::AddVertex	(zCVertex* vertex) 
{
    ArraysToLists();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		zCVertex **oldVPtrPtr = GetMeshesPool().GetMesh(poolIndex)->GetVertexPool()->GetVertexPtrPtrList();
		if (numVertAlloc<numVert+1) AllocVerts (zMax(1, numVert/2));

		//zCVertex **oldVPtrPtr = GetMeshesPool().GetMesh(poolIndex)->GetVertexPool()->GetVertexPtrPtrList();
		int numPool = GetMeshesPool().GetMesh(poolIndex)->AddVertex(vertex);
		// delete old vertex to avoid memleaks
		delete vertex;

		zCVertex* newVert = GetMeshesPool().GetMesh(poolIndex)->GetVertex(numPool);

		vertList[numVert] = newVert;
		numVert++;

		if(oldVPtrPtr!=GetMeshesPool().GetMesh(poolIndex)->GetVertexPool()->GetVertexPtrPtrList())
		{
			// recalc internal vertexaddresses
			int i = GetMeshesPool().GetMesh(poolIndex)->GetPolygonPool()->GetPolygonCount();
			if(i>0) while(i--)
			{
				zCPolygon *polygon = GetMeshesPool().GetMesh(poolIndex)->GetPolygonPool()->GetPolygonPtr(i);
				if(polygon->vertex!=NULL)
				{
					int ptrOffs = int(polygon->vertex) - int(oldVPtrPtr);
					ptrOffs = ptrOffs >> 2;
					polygon->vertex = GetMeshesPool().GetMesh(poolIndex)->GetVertexPool()->GetVertexPtrPtrList() + ptrOffs;
				}
			}
		}
	
		return newVert;
	}
	else
#endif
	{
		if (numVertAlloc<numVert+1) AllocVerts (zMax(1, numVert/2));
		vertList[numVert] = vertex;
		if (s_usesVertexCache) s_vertexCache.InsertSort(vertex);
		numVert++;
		return vertList[numVert-1];
	}
};


zCVertex* zCMesh::AddVertex (zPOINT3& a) 
{
    ArraysToLists();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		zCVertex **oldVPtrPtr = GetMeshesPool().GetMesh(poolIndex)->GetVertexPool()->GetVertexPtrPtrList();
		if (numVertAlloc<numVert+1) AllocVerts (zMax(1, numVert/2));

		zCVertex tempVert;
		tempVert.SetPosition(a); 
		int numPool = GetMeshesPool().GetMesh(poolIndex)->AddVertex(&tempVert);
	
		zCVertex* newVert = GetMeshesPool().GetMesh(poolIndex)->GetVertex(numPool);
		vertList[numVert] = newVert;
		numVert++;	

		if(oldVPtrPtr!=GetMeshesPool().GetMesh(poolIndex)->GetVertexPool()->GetVertexPtrPtrList())
		{
			// recalc internal vertexaddresses
			int i = GetMeshesPool().GetMesh(poolIndex)->GetPolygonPool()->GetPolygonCount();
			if(i>0) while(i--)
			{
				zCPolygon *polygon = GetMeshesPool().GetMesh(poolIndex)->GetPolygonPool()->GetPolygonPtr(i);
				if(polygon->vertex!=NULL)
				{	
					int ptrOffs = int(polygon->vertex) - int(oldVPtrPtr);
					ptrOffs = ptrOffs >> 2;
					polygon->vertex = GetMeshesPool().GetMesh(poolIndex)->GetVertexPool()->GetVertexPtrPtrList() + ptrOffs;
				}
			}
		}
	
		return newVert;
	}
	else
#endif
	{
		if (numVertAlloc<numVert+1) AllocVerts (zMax(1, numVert/2));

		vertList[numVert] = zNEW(zCVertex);
		vertList[numVert]->SetPosition (a);

		if (s_usesVertexCache) s_vertexCache.InsertSort(vertList[numVert]);

		numVert++;
		return vertList[numVert-1];
	}
}

zCVertex* zCMesh :: AddVertexSmart (zPOINT3& a) {
    ArraysToLists();

	zCVertex *vert = VertexInMesh (a);  
	if (vert) return vert;
	return AddVertex (a);
}

zCPolygon* zCMesh :: AddPoly	(zPOINT3& a, zPOINT3& b, zPOINT3& c, 
								 zPOINT2& texa, zPOINT2& texb, zPOINT2& texc ) 
{
    ArraysToLists();
    UnshareFeatures();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		zCVertex *pa,*pb,*pc;
		//	IsLegal();

		//
		// 1x: new zCPolygon
		//
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		// fill in
		zCPolygon poly(this);
		int np = GetMeshesPool().GetMesh(poolIndex)->AddPolygon(&poly);
		polyList[numPoly] = GetMeshesPool().GetMesh(poolIndex)->GetPolygon(np);

		// vertices already in vertList ?
		// 3x: new zCVertex, add Vertex
		//	pa = VertexInMesh (a); if (pa==0) pa = AddVertex (a);
		//	pb = VertexInMesh (b); if (pb==0) pb = AddVertex (b);
		//	pc = VertexInMesh (c); if (pc==0) pc = AddVertex (c);
		pa = AddVertexSmart (a);
		pb = AddVertexSmart (b);
		pc = AddVertexSmart (c);

		polyList[numPoly]->SetMapping (0, texa);
		polyList[numPoly]->SetMapping (1, texb);
		polyList[numPoly]->SetMapping (2, texc);

		polyList[numPoly]->SetVertices (pa,pb,pc);

		numPoly++;
		return polyList[numPoly-1];
	}
	else
#endif
	{
		zCVertex *pa,*pb,*pc;
		//	IsLegal();

		//
		// 1x: new zCPolygon
		//
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		// fill in
		polyList[numPoly] = zNEW(zCPolygon);

		// vertices already in vertList ?
		// 3x: new zCVertex, add Vertex
		//	pa = VertexInMesh (a); if (pa==0) pa = AddVertex (a);
		//	pb = VertexInMesh (b); if (pb==0) pb = AddVertex (b);
		//	pc = VertexInMesh (c); if (pc==0) pc = AddVertex (c);
		pa = AddVertexSmart (a);
		pb = AddVertexSmart (b);
		pc = AddVertexSmart (c);

		polyList[numPoly]->SetMapping (0, texa);
		polyList[numPoly]->SetMapping (1, texb);
		polyList[numPoly]->SetMapping (2, texc);

		polyList[numPoly]->SetVertices (pa,pb,pc);

		numPoly++;
		return polyList[numPoly-1];
	}
}

zCPolygon* zCMesh :: AddPoly (zCVertex* va, zCVertex* vb, zCVertex* vc) 
{
    ArraysToLists();
    UnshareFeatures();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		zCPolygon poly(this);
		int np = GetMeshesPool().GetMesh(poolIndex)->AddPolygon(&poly);
		polyList[numPoly] = GetMeshesPool().GetMesh(poolIndex)->GetPolygon(np);
		polyList[numPoly]->SetVertices (va,vb,vc);
		numPoly++;
		return polyList[numPoly-1];
	}
	else
#endif
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		polyList[numPoly] = zNEW(zCPolygon);
		polyList[numPoly]->SetVertices (va,vb,vc);
		numPoly++;
		return polyList[numPoly-1];
	}
};

zCPolygon* zCMesh :: AddPoly (zCVertex* va, zCVertex* vb, zCVertex* vc, zCVertex* vd) 
{
    ArraysToLists();
    UnshareFeatures();

#ifdef MEMPOOL_HOELLER
    if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		zCPolygon poly(this);
		int np = GetMeshesPool().GetMesh(poolIndex)->AddPolygon(&poly);
		polyList[numPoly] = GetMeshesPool().GetMesh(poolIndex)->GetPolygon(np);
		polyList[numPoly]->SetVertices (va,vb,vc,vd);
		numPoly++;
		return polyList[numPoly-1];
	}
	else
#endif
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		polyList[numPoly] = zNEW(zCPolygon);
		polyList[numPoly]->SetVertices (va,vb,vc,vd);
		numPoly++;
		return polyList[numPoly-1];
	}
};

zCPolygon* zCMesh :: AddPoly (zCPolygon* poly) 
{
    ArraysToLists();
    UnshareFeatures();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		int np = GetMeshesPool().GetMesh(poolIndex)->AddPolygon(poly);
		polyList[numPoly] = GetMeshesPool().GetMesh(poolIndex)->GetPolygon(np);
		//delete poly;
		// @DIRTY: removes memory from heap without initialization

		delete (void *)poly; // [Moos] so ist es etwas weniger Dirty (mein super-duper-spezial-leakfinder-speichermanager kam naturgemäss mit dem Unten nicht klar)
		/*
		#ifdef ZMEMORY_USE_ZMALLOC  
		zmalloc.Free((void*)poly);							 
		#else
		free((void*)poly);
		#endif
		*/
		numPoly++;
		return polyList[numPoly-1];
	}
	else
#endif
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		polyList[numPoly] = poly;
		numPoly++;
		return polyList[numPoly-1];
	}
};

zCPolygon* zCMesh::AddPoly () 
{
    ArraysToLists();
    UnshareFeatures();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		zCPolygon poly(this);
		int np = GetMeshesPool().GetMesh(poolIndex)->AddPolygon(&poly);
		polyList[numPoly] = GetMeshesPool().GetMesh(poolIndex)->GetPolygon(np);
		numPoly++;
		return polyList[numPoly-1];
	}
	else
#endif
	{
		if (numPolyAlloc<numPoly+1) AllocPolys (numPoly/2);
		polyList[numPoly] = zNEW(zCPolygon);
		numPoly++;
		return polyList[numPoly-1];
	}
};

void zCMesh :: DeletePoly	(zCPolygon* poly) 
{
    ArraysToLists();
    UnshareFeatures();

#ifdef MEMPOOL_HOELLER
	if(GetMeshesPool().IsPoolActive()==TRUE)
	{
		for (int i=0; i<numPoly; i++) 
		{
			if (polyList[i]==poly) 
			{
				GetMeshesPool().GetMesh(poolIndex)->RemovePolygon(i);
				//delete polyList[i];
				for (int j=i; j<numPoly-1; j++)
					polyList[j]= polyList[j+1];
//				polyList[j] -= sizeof(zCPolygon);  <- warum das denn ? Irgendein unbekanntes Feature ? [oh]
				numPoly--;
				// numVertAlloc bleibt wie es ist!
				return;
			};
		};
	}
	else
#endif
	{
		for (int i=0; i<numPoly; i++) 
		{
			if (polyList[i]==poly) 
			{
				delete polyList[i];
				for (int j=i; j<numPoly-1; j++)
					polyList[j]= polyList[j+1];
				numPoly--;
				// numVertAlloc bleibt wie es ist!
				return;
			};
		}
	};
};

// =========================================================================================================

void zCMesh::DynLightVisual (const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld) {
	return;
	// FIXME: alles temporaer
	
//	zCPolygon::LightPolyList (vobLightList, polyList, numPoly, trafoWorldToObj);
	if (vobLightList.GetNumInList()==0) {
//		ResetLightDynToLightStat ();  
		zCOLOR col;
		col.Reset	();
		SetLightDyn (col);  
	} else {
		zPOINT3 posWS;
		if (trafoObjToWorld)	posWS = trafoObjToWorld->GetTranslation();
		else					posWS = 0;
		zCOLOR col = zCVobLight::SumLightsAtPositionWS (vobLightList, posWS);
		DynLightScalePrelit (col); 
	};
};

void zCMesh::DynLightScalePrelit (const zCOLOR scaleColor) {
	return;
	int sr = int (scaleColor.GetRedByte());
	int sg = int (scaleColor.GetGreenByte());
	int sb = int (scaleColor.GetBlueByte());
//	for (int i=0; i<numPoly; i++) {
	zCOLOR col;
	col.alpha=255;
	int i=numPoly-1;
	do {
		zCPolygon *poly = Poly(i);
		int j=poly->polyNumVert-1; 
		do {
//		for (int j=0; j<poly->polyNumVert; j++) {
			// assert: prelit = nur weisses Licht, kein ALPHA
			int intens	= int(poly->feature[j]->lightStat.r);
//			col.alpha	= poly->feature[j]->lightStat.alpha;
			col.r		= (intens * sr) >> 8;
			col.g		= (intens * sg) >> 8;
			col.b		= (intens * sb) >> 8; 
/*			col.r		= (intens * int (scaleColor.GetRedByte())) >> 8;
			col.g		= (intens * int (scaleColor.GetGreenByte())) >> 8;
			col.b		= (intens * int (scaleColor.GetBlueByte())) >> 8;*/
			poly->feature[j]->lightDyn = col;
//			poly->feature[j]->lightDyn = poly->feature[j]->lightStat;
		} while (j--);
	} while (i--);
};

void zCMesh::PrelightMesh (zMATRIX4 *trafoObjToWorld) {
    ArraysToLists();
    //    UnshareFeatures();

	zCArray<zCVobLight*> vobLightList;

//	if (GetDynLightMode()==zMDL_DYNLIGHT_SCALEPRELIT) 
/*		zCVobLight light1, light2, light3;
		light1.SetRange		(500);
		light1.SetColor		(255,255,255);
		light1.Move			(30,180,200);
		vobLightList.Insert (&light1);

		light2.SetRange		(500);
		light2.SetColor		(255,255,255);
		light2.Move			(0,50,-100);
		vobLightList.Insert (&light2);

		light3.SetRange		(400);
		light3.SetColor		(205,205,205);
		light3.Move			(0,300,0);
		vobLightList.Insert (&light3);
*/
		zCVobLight	*light1	= zNEW(zCVobLight); 
		zCVobLight	*light2	= zNEW(zCVobLight);
		zCVobLight	*light3	= zNEW(zCVobLight);
		zCVobLight	*light4	= zNEW(zCVobLight);
		zVEC3		pos;
		pos					= zVEC3(-1*400, 100, +1*400);
		light1->SetRange	(1100);
		light1->SetColor	(255,255,255);
		light1->Move		(pos);
		vobLightList.Insert (light1);

		pos					= zVEC3(+1*400, 50, +1*400);
		light2->SetRange	(1100);
		light2->SetColor	(255,255,255);
		light2->Move		(pos);
		vobLightList.Insert (light2);

		pos					= zVEC3(+1*400, 300, -1*400);
		light3->SetRange	(1000);
		light3->SetColor	(205,205,205);
		light3->Move		(pos);
		vobLightList.Insert (light3);

		pos					= zVEC3(-1*400, -50, -1*400);
		light4->SetRange	(1100);
		light4->SetColor	(205,205,205);
		light4->Move		(pos);
		vobLightList.Insert (light4);

	ResetStaticLight			();		// ... um lightDyn auf 0 zu setzen.. 
	ResetLightDynToLightStat	();

	if (trafoObjToWorld)	zCPolygon::LightPolyList (vobLightList, polyList, numPoly, &(trafoObjToWorld->InverseLinTrafo()));
	else					zCPolygon::LightPolyList (vobLightList, polyList, numPoly, 0);

	for (int i=0; i<numPoly; i++) {
		zCPolygon *poly = polyList[i];
		for (int j=0; j<poly->polyNumVert; j++) {
			poly->feature[j]->lightStat = poly->feature[j]->lightDyn;
		};
	};
	zRELEASE (light1);
	zRELEASE (light2);
	zRELEASE (light3);
	zRELEASE (light4);

//	l_vobLightList = &vobLightList;
//	l_lightingMode = zMDL_LIGHT_PRELIGHT;
//	DynLightVisual (Alg_Identity3D(), &meshTree);
};

// =========================================================================================================

/*
Es sind ja im Grunde 2 checks möglich:
- 1. Negativ-Test: Mit der Suche aufhören, sobald ein Poly getroffen wurde			=> Trace Light-Beam, line-of-sight
- 2. aus Satz von Polys das Poly heraussuchen, das den Strahl am nächsten trifft	=> Select Poly with mouse
*/

// 1.
zCPolygon* zCMesh::CheckRayPolyIntersection (const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& intersection) {
	// Alle Polys des Meshes abgehen, stoppen, sobald Strahl behindert wurde
	zVALUE alpha;		// dummy
	for (int polyCtr=0; polyCtr<numPoly; polyCtr++) {
	    zCPolygon *poly = Poly(polyCtr);
		if (poly->CheckRayPolyIntersection (rayOrigin, ray, intersection, alpha)) {
			if (alpha<=1.0F) return poly;
		};
	};
	return FALSE;
};

static const zVALUE RAY_DIST = 60000.0F;

// 1.
zCPolygon* zCMesh::CheckRayPolyIntersection (zCCamera& cam, int xscr, int yscr, zPOINT3& intersection) {
	zPOINT3 ray00, ray, p;
	
	// create ray00, ray by backprojection
	// ray00, ray sind im world(obj)Space
	// 'ray00	= cam.camMatrixInv * zPOINT3(0,0,0);'  =
	cam.camMatrixInv.GetTranslation( ray00 );
	p.n[VZ] = RAY_DIST;
	cam.BackProject	(xscr, yscr, p);		// p im camSpace
	p		= cam.camMatrixInv * p;			// p im worldSpace  
	ray		= p - ray00;

	// doit
	// ACHTUNG: intersection befindet sich auch im world(obj)Space
	return CheckRayPolyIntersection (ray00, ray, intersection);
};

// 2.
zCPolygon* zCMesh::PickPolygon (const zPOINT3& rayOrigin, const zPOINT3& ray, zPOINT3& intersection) {
	zVALUE		alpha, minAlpha = zVALUE_MAX;
	zCPolygon	*bestPoly;
	zPOINT3		bestIntersect;

	// Alle Polys des Meshes abgehen, und das heraussuchen, das Strahl am nächsten trifft 
	for (int polyCtr=0; polyCtr<numPoly; polyCtr++) {
	    zCPolygon *poly = Poly(polyCtr);

		if (poly->IsPortal()) continue;
		if (poly->CheckRayPolyIntersection (rayOrigin, ray, intersection, alpha)) {
			// besser als alle getroffenen Polys zuvor ?
			if (alpha<minAlpha) {
				minAlpha		= alpha;
				bestPoly		= poly;
				bestIntersect	= intersection;
			};
		};
	};
	if (minAlpha!=zVALUE_MAX) {
		intersection = bestIntersect;
		return bestPoly;
	};
	return FALSE;
};

// 2.
zCPolygon* zCMesh::PickPolygon (zCCamera& cam, int xscr, int yscr, zPOINT3& intersection) {
	zPOINT3 ray00, ray, p;

	// create ray00, ray by backprojection
	// ray00, ray sind im world(obj)Space
	// 'ray00	= cam.camMatrixInv * zPOINT3(0,0,0);'  =
	cam.camMatrixInv.GetTranslation( ray00 );
	p.n[VZ] = RAY_DIST;
	cam.BackProject	(xscr, yscr, p);		// p im camSpace
	p		= cam.camMatrixInv * p;			// p im world(obj)Space  
	ray		= p - ray00;

	// doit
	return PickPolygon (ray00, ray, intersection); 
};

zBOOL zCMesh::TraceRay	(	const zVEC3&		rayOrigin, 
							const zVEC3&		ray, 
							const int			traceFlags, 
							zTTraceRayReport	&report)
{
	// Input-Ray		: objectSpace
	// Output-Location	: objectSpace

	// FIXME: traceFlag 'zTRACERAY_POLY_2SIDED' ist hier noch nicht beruecksichtigt!

	zCPolygon *poly;
	if ((traceFlags & zTRACERAY_FIRSTHIT)!=0) 
	{
		// First Hit
		poly	= CheckRayPolyIntersection	(rayOrigin, ray, report.foundIntersection);

	} else
	{
		// Nearest Hit
		poly	= PickPolygon				(rayOrigin, ray, report.foundIntersection);
	}

	// irgendein Poly getroffen ?
	report.foundHit			= FALSE;
	if (poly) {
		// flags filtern
		// transp polys ignorieren ?
		if (traceFlags & zTRACERAY_POLY_IGNORE_TRANSP) {
			zCMaterial *mat = poly->GetMaterial();
			if ((mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE) ||
				((mat->GetTexture()) && (mat->GetTexture()->HasAlphaChannel())))
				poly = 0;
		};
		
		if (poly) {
			// polyNormal erwuenscht ?
			if (traceFlags & zTRACERAY_POLY_NORMAL) {
				report.foundPolyNormal	= poly->GetNormal();
			};
			report.foundHit				= TRUE;
			report.foundPoly			= poly;
		};

	};

	return report.foundHit;
};

// =========================================================================================================


void zCMesh::CalcVertexNormals (zTCalcVertNormalMode mode, zCBspTree* bspTree) {
    ArraysToLists();
    UnshareFeatures();

	// FORCE_SMOOTH
	// FIXME/TODO:
	// - Poly-Normals beim addieren durch Flaeche des Polys gewichten
	// - Keine identischen Polys mehrfach beruecksichtigen
	// - Bessere Iteration: : 
	//	should init all normals to 0
	//	:
	//	: for(int j=0; j<num_polys; j++)
	//	:       for(i=0; i<faces[j].num_verts; i++)
	//	:               faces[j].verts[i].normal+=faces[j].normal;
	//	:
	//	: for(i=0; i<num_verts; i++)
	//	:       verts[i].normal.normalize();
	//
	// Winkel:  arccos( v dot w / || v || * || w || ),

//	zerr.Message ("D: MESH: Calculating Vertex-Normals for Mesh ...");

/*	zCArray<zCPolygon*> **vertBucket = new zCArray<zCPolygon*>* [numVert];
	for (int i=0; i<numPoly; i++) {
		zCPolygon *poly = polyList[i];
		for (int j=0; j<poly->polyNumVert; j++) {
			poly->vertex[j]
		};
	};
	delete vertBucket[];*/

//mode = zMSH_VERTNORMAL_SMOOTH;
	zTBBox3D	polyBBox;
	zCPolygon**	foundPolyList;
	int			foundPolyNum;

	if (mode==zMSH_VERTNORMAL_MAT) 
	{
		for (int i=0; i<numPoly; i++) {
			zCPolygon *poly = polyList[i];
			if (bspTree) {
				polyBBox = poly->GetBBox3D();
				polyBBox.Scale (1.5F);
				const zREAL INC = zREAL(1.0F);
				if (polyBBox.mins[VX]==polyBBox.maxs[VX])	{ polyBBox.mins[VX] -= INC; polyBBox.maxs[VX] += INC; };
				if (polyBBox.mins[VZ]==polyBBox.maxs[VZ])	{ polyBBox.mins[VZ] -= INC; polyBBox.maxs[VZ] += INC; };
			};
			for (int j=0; j<poly->polyNumVert; j++) 
			{
				zCVertex		*vert = poly->vertex[j];
				zCVertFeature	*feat = poly->feature[j];

				feat->vertNormal = poly->GetNormal();

				if (poly->material)
				if (poly->material->GetSmooth() || poly->GetSectorFlag()) 
				{
 					if (bspTree) 
					{
						bspTree->GetRoot()->CollectPolysInBBox3D (polyBBox, foundPolyList, foundPolyNum);
						// welches Poly teilt noch dieses aktuelle Vert ?
						for (int k=0; k<foundPolyNum; k++) 
						{
							zCPolygon *poly2 = foundPolyList[k];

							if (poly2->material->GetSmooth() || poly2->GetSectorFlag()) 
							{
								if (poly2->VertPartOfPoly(vert)) 
								{
									if (poly2==poly) continue;
									zREAL angle1, angle2;
									angle1 = poly->GetSectorFlag() ? 60:poly->GetMaterial()->smoothAngle;
									angle2 = poly2->GetSectorFlag()? 60:poly2->GetMaterial()->smoothAngle;
									zREAL smoothRel = zMax			(angle1, angle2);
									zREAL polyRel	= Alg_Rad2Deg	(Alg_AngleUnitRad(poly->GetNormal() , poly2->GetNormal()));
									if (smoothRel>polyRel)
										feat->vertNormal += poly2->GetNormal();
								};
							};
						};
					} 
					else 
					{
						// welches Poly teilt noch dieses aktuelle Vert ?
						for (int k=0; k<numPoly; k++) 
						{
							zCPolygon *poly2 = polyList[k];

							if (poly2->material==poly->material)
							{
								if (poly2->VertPartOfPoly(vert))
								{ 
									if (i==k) continue;
									// 2. Poly gefunden: ist dieses
									// a) auch ein Smooth-Material b) ist der Winkel < alpha° ?
									zREAL smoothRel = zMax			(poly->GetMaterial()->smoothAngle, poly2->GetMaterial()->smoothAngle);
									zREAL polyRel	= Alg_Rad2Deg	(Alg_AngleUnitRad(poly->GetNormal() , poly2->GetNormal()));
									if (smoothRel>polyRel)
										feat->vertNormal += poly2->GetNormal();
								};
							};
						};
					};
					// hier kann theoret. eine Normale aus obiger Berechnung mit Laenge 0 ankommen
					// sollte man das anders behandeln .. ?
					zREAL normalLen	= feat->vertNormal.Length();
					if (normalLen==0)	feat->vertNormal  = poly->GetNormal();
					else				feat->vertNormal /= normalLen;
				};
			};
		};
	} else
	if (mode==zMSH_VERTNORMAL_SMOOTH) 
	{
		for (int i=0; i<numPoly; i++) {
			zCPolygon	*poly = polyList[i];

			if (bspTree) 
			{
				polyBBox = poly->GetBBox3D();
				polyBBox.Scale (1.5F);
				const zREAL INC = zREAL(1.0F);
				if (polyBBox.mins[VX]==polyBBox.maxs[VX])	{ polyBBox.mins[VX] -= INC; polyBBox.maxs[VX] += INC; };
				if (polyBBox.mins[VY]==polyBBox.maxs[VY])	{ polyBBox.mins[VY] -= INC; polyBBox.maxs[VY] += INC; };
				if (polyBBox.mins[VZ]==polyBBox.maxs[VZ])	{ polyBBox.mins[VZ] -= INC; polyBBox.maxs[VZ] += INC; };
			};
			for (int j=0; j<poly->polyNumVert; j++) 
			{
				zCVertex		*vert = poly->vertex[j];
				zCVertFeature	*feat = poly->feature[j];

				feat->vertNormal = poly->GetNormal();
				if (bspTree) 
				{
					bspTree->GetRoot()->CollectPolysInBBox3D (polyBBox, foundPolyList, foundPolyNum);
					// welches Poly teilt noch dieses aktuelle Vert ?
					for (int k=0; k<foundPolyNum; k++) 
					{
						zCPolygon *poly2 = foundPolyList[k];
						if (poly2->VertPartOfPoly(vert)) 
						{
							if (poly2!=poly) 
							feat->vertNormal += poly2->GetNormal();
						};
					};
				}
				else 
				{
					// welches Poly teilt noch dieses aktuelle Vert ?
					for (int k=0; k<numPoly; k++) 
					{
						zCPolygon *poly2 = polyList[k];
						if ((poly2->VertPartOfPoly(vert) && (i!=k))) {
							feat->vertNormal += poly2->GetNormal();
						};
					};
				};
				feat->vertNormal.NormalizeSafe();
			};
		};
	} else
	if (mode==zMSH_VERTNORMAL_FACET) 
	{
		for (int i=0; i<numPoly; i++) 
		{
			zCPolygon *poly = polyList[i];
			for (int j=0; j<poly->polyNumVert; j++)
				poly->feature[j]->vertNormal = poly->GetNormal();
		};
	}; /* END FACET */
};


void zCMesh :: UnSmoothMesh() {
    ArraysToLists();
    UnshareFeatures();

	for (int polyCtr=0; polyCtr<numPoly; polyCtr++) {
		if (polyList[polyCtr]->GetMaterial())
		polyList[polyCtr]->GetMaterial()->SetSmooth (FALSE);
//		polyList[polyCtr]->SetSmoothing (FALSE);				// setzt beteiligtes poly auf SMOOTH
	};
};

void zCMesh :: SetDefaultPlanarMapping (const zVALUE scaleu, const zVALUE scalev) {
    ArraysToLists();
    UnshareFeatures();

	int polyCtr;
	// alle verts abgehen
	for (polyCtr=0; polyCtr<numPoly; polyCtr++) {
		zCPolygon *poly = polyList[polyCtr]; 
		poly->TexApplyPlanarMapping (scaleu, scalev);
	};
};

void zCMesh::CalcBBox3D (const zBOOL fastApprox) {
    ArraysToLists();
    UnshareFeatures();

	if (fastApprox)
	{
		bbox3D.Init(); 
		for (int vertCtr=0; vertCtr<numVert; vertCtr++) {
			zCVertex *vert = vertList [vertCtr];
			for (int j=0; j<3; j++) {
				bbox3D.mins[j] = zMin (bbox3D.mins[j], vert->position.n[j]);
				bbox3D.maxs[j] = zMax (bbox3D.maxs[j], vert->position.n[j]);
			};
		};
	}
	else {
		// temp ?
		obbox3D.BuildOBBTree (this, 3);
		bbox3D = obbox3D.GetBBox3D();
	};
	//
	if ((numVert==0) || (numPoly==0)) {
		zREAL D = 0.1F;
		bbox3D.mins = -zVEC3(D,D,D);
		bbox3D.maxs =  zVEC3(D,D,D);
	};
};

void zCMesh::Center () {
	zVEC3 center = 0;
	for (int vertCtr=0; vertCtr<numVert; vertCtr++) 
		center += Vertex(vertCtr)->position;
	center = center / zREAL(numVert);
	TransformAllVerts (Alg_Translation3D(-center), TRUE);
};

void zCMesh::TransformAllVerts (const zMATRIX4& trafo, const zBOOL autoUpdateInternals) {
	for (int i=0; i<numVert; i++) 
		Vertex(i)->position = trafo*Vertex(i)->position;
	if (autoUpdateInternals) {
		CalcNormals	();
		CalcBBox3D	();
	};
};

void zCMesh::MergeMesh (zCMesh *mesh, const zMATRIX4& trafo) 
{
    ArraysToLists();
    UnshareFeatures();


	int i;
	AllocVerts (mesh->numVert);		// Ueberschaetzung
	AllocPolys (mesh->numPoly);

	// da die camera nicht performance kritisch ist, und höchste präzision vonnöten ist, 
	// wird die fpu auf 64 bit precision gesetzt
	zfpuControler.SaveCurrentControlWord();
	zfpuControler.SetPrecision_64();

	if (!s_bAddVobsToMesh) S_InitVertexMergeCache(this);

	zCVertex **newVert = zNEW(zCVertex*) [mesh->numVert];

	// Verts kopieren & einfügen
	for (i=0; i<mesh->numVert; i++) {
		// Vert falls moeglich sharen
		const zPOINT3& newPos= trafo * mesh->vertList[i]->position;
		zCVertex *vert		= s_bAddVobsToMesh ? 0 : this->VertexInMesh (newPos);
		if (vert) newVert[i]=vert;
		else {
			vert			= zNEW(zCVertex);
			// Vert transformieren & kopieren 
			*vert			= (*(mesh->vertList[i]));
			vert->position	= newPos;
			newVert[i]		= this->AddVertex (vert);
		};
	};


	// Polys kopieren & einfügen
	for (i=0; i<mesh->numPoly; i++) {

		zCPolygon *poly		= AddPoly();
		(*poly)				= *(mesh->polyList[i]);

		poly->vertex		= 0;
		poly->polyNumVert	= 0;

		poly->AllocVerts (mesh->polyList[i]->polyNumVert);
		mesh->polyList[i]->CopyValuesInto (poly);				// ACHTUNG, Material.AddRef impl. 

		// Alle Poly-Verts abgehen
		for (int j=0; j<poly->polyNumVert; j++) {
			zCVertex* vert	= mesh->polyList[i]->vertex[j];
			poly->vertex[j] = vert;
//			poly->vertex[j] = mesh->polyList[i]->vertex[j];
//			zCVertex* vert	= poly->vertex[j];

			// Für jedes Poly-Vert passendes Vert aus Mesh-Liste finden
			for (int k=0; k<mesh->numVert; k++) {
				if (vert==mesh->vertList[k]) {
					poly->vertex[j] = newVert[k];
					break;
				};
			};
		};

		// MUSS hier gemacht werden !!!!!!
		// Eine Normale ist definitiv eine *absolute* Angabe im jeweiligen Raum !
		poly->CalcNormal();
	};
	delete[] newVert;

	if (!s_bAddVobsToMesh) S_DeleteVertexMergeCache();
	zfpuControler.RestoreSavedControlWord();


};

void zCMesh::CalcNormals () {
	for (int i=0; i<numPoly; i++) Poly(i)->CalcNormal();
};

void zCMesh::SetMaterial (zCMaterial *mat) {
	for (int i=0; i<numPoly; i++) Poly(i)->SetMaterial (mat);		// AddRef implizit
};

void zCMesh::ScaleXZ (const zVALUE xs, const zVALUE zs) {
	for (int i=0; i<numVert; i++) {
		Vertex(i)->position[VX] *= xs;
		Vertex(i)->position[VZ] *= zs;
	};
	bbox3D.mins[VX] *= xs;
	bbox3D.maxs[VX] *= xs;
	bbox3D.mins[VZ] *= zs;
	bbox3D.maxs[VZ] *= zs;
};

void zCMesh::Scale (const zVALUE xs, const zVALUE ys, const zVALUE zs) {
	zVEC3 s = zVEC3(xs,ys,zs);
	for (int i=0; i<numVert; i++) {
		Vertex(i)->position = Alg_Prod (Vertex(i)->position, s);;
	};
	bbox3D.mins = Alg_Prod (bbox3D.mins, s);
	bbox3D.maxs = Alg_Prod (bbox3D.maxs, s);
}; 

void zCMesh::CheckForMaterials () const {
	for (int i=0; i<numPoly; i++) {
		if (!Poly(i)->IsPortal())
			if (!Poly(i)->GetMaterial())
				zERR_FATAL ("D: z3d(zCMesh::CheckForMaterials): poly without material ! ("+GetMeshName()+")");
	};

};

/*
void zCMesh::ShareVerts () {
	for (int polyCtr=0; polyCtr<numPoly; polyCtr++) {
		zCPolygon	*poly = polyList[polyCtr];
		for (int vertCtr=0; vertCtr<numVert-1; vertCtr++) {
			zCVertex *vert = poly->vertList[vertCtr];

			for (int i=vertCtr+1; i<numVert; i++) {
				if (poly->material==0)
				if (vert->position==poly->vertList[i]->position) {
					poly->vertList[i] = vert;
				};
			};
		};
	};
};
*/

//
//  MRENDERN
//

/*
***************************************************************************
* Ist:
- (large-scale culling)
- fa Polys
	- backface culling (o)
	- fa Verts
		- Trafo
		- far Clipping plane (o)
		- Project
		- Lighting
	- (2D-Clipping)
	- (3D-Clipping (perfekt=>2D-Clipping unnötig!))
- Sort Polys (Z,BSP)
- Draw Polys 
	- fa Kanten
		- Clip3D (+evtl. Project)
		- Scan
	- 2D-Clipping (o)
	- (lighting)
	- Process Table
***************************************************************************
* Soll:
x (large-scale culling) (o)
- fa Polys
	x backface culling (o)
	x 3D-Clipping (perfekt=>2D-Clipping unnötig!) (o)
	- fa Verts
		x Trafo 
		x far Clipping plane (o)
		x Project
x Sort Polys (Z,BSP,Edge-Sorting)
- Draw Polys 
	x evtl. "on-the-fly" triangulieren
	x fa Kanten
		- Scan
	- (lighting)
	- Process Table
***************************************************************************
Zusammengefasst macht diese Routine:
- culling
- 3D-Clipping
- Trafo
- Projection
*/ 

/*
{
	// Wellen-Sinus
	int vertCtr = actPoly->polyNumVert-1; 
	do {
		zCVertex *actVert = (actPoly->vertex[vertCtr]);
		if (actPoly->material->GetMatGroup()==zMAT_GROUP_WATER)   
		{
			zPOINT3 pos = actVert->position;
			zREAL	t	= ( (pos[VX]+pos[VZ]) + ztimer.GetTotalTimeF()/700);
//			zREAL	t	= ( (pos[VX]+pos[VZ]) + ztimer.GetFrameTimeF()/500);
			pos[VY] -= 0.6F*(zSin(t));
			actVert->position = pos;
		};
	} while (vertCtr--);
		}
*/

/*
The most efficient method to perform back face culling it perform it in
object space before any transforms. What you do is just with inverse
object transform matrix transform viewpoint to object space and apply dot
product between view vector and surface normal. When this value is
negative, the face is front facing. The calculations you'll need for whole
procedure is 3 muls and 5 adds.

If you're only using perspective projection, a faster way to do backface culling is to check
which side of the poly's plane the viewpoint is on, i.e. let vp=(x,y,z), and let plane be
(A,B,C,D); then you can see poly iff Ax+By+Cz+D >0, otherwise you're behind it.
*/

zBOOL zCMesh::Render (zTRenderContext& renderContext) 
{
	// Das Mesh wird beleuchtet (derzeit nur ambient & entsprechend der Tageszeit)
	zCOLOR vertColor(200,200,200,255);
	if (renderContext.world) {
		if ((renderContext.vob) &&
		    (renderContext.vob->GetGroundPoly()) &&
		    (renderContext.vob->GetGroundPoly()->GetSectorFlag()))
		{
			vertColor	= renderContext.world->GetActiveSkyControler()->GetDaylightColorFromIntensity (120);
		} else {
			vertColor	= renderContext.world->GetActiveSkyControler()->GetDaylightColorFromIntensity (200);
		};
	};
	return Render (renderContext, &vertColor);
};

/* ----------------------------------------------------------------------
	
    zCMesh::Render()	

	16.11.2000	[Moos]	
                Auf neue Vertex-Klasse umgestellt
    22.11.2000  [Moos]
                Nur die explizit verwendeten Vertices werden zurückgesetzt
     4.12.2000  [Moos]
                Und das wird jetzt effizient über die MemPool-Klassen gemacht

   ---------------------------------------------------------------------- */

zBOOL zCMesh::Render (zTRenderContext& renderContext, zCOLOR *vertexColor) 
{
	// Das Mesh wird in erster Linie nicht weiter beleuchtet, existierende vertex-rgba's bleiben unangetastet
	// Es kann allerdings eine vertexColor angegeben werden, die bei Angabe fuer alle Verts als color eingesetzt wird

	int polyCtr;
    size_t markedPos;
	// im Sinne von: alle verts: "transformed/projected" - flags auf FALSE setzen
	//masterFrameCtr++;

	// setup
	const zPOINT3& camPos	= zCCamera :: activeCamPos; 

	// Texture-CacheIn Prio
	zREAL texCacheInPrio	= ((renderContext.distVobToCam / renderContext.cam->GetFarClipZ())) * 0.5F + 0.25F;
//	if (texCacheInPrio>0.5F) texCacheInPrio=0.5F;

	// Lage der Mesh-BBox zum Camera-Viewport
	if (renderContext.clipFlags==-1) {
		renderContext.clipFlags = zCCamera::CLIP_FLAGS_FULL;
		zTCam_ClipType meshClip = zCCamera::activeCam->BBox3DInFrustum (bbox3D, renderContext.clipFlags);
		if (meshClip==zCAM_CLIP_TRIV_OUT) goto renderExitOutside;
	};

    markedPos = zCVertexTransform::PoolMark(); // [Moos] Alle Allocationen von TransformedVertices sollen nur lokal gelten

	// alle polys abgehen
	for (polyCtr=0; polyCtr<numPoly; polyCtr++) 
	{
		zCPolygon *actPoly = Poly(polyCtr); 
		
		// backface culling (in world(obj)Space) 
#ifdef COMPILING_SPACER
		if (zrenderer->GetPolyDrawMode() != zRND_DRAW_WIRE)
		if (zrenderer->GetPolyDrawMode() != zRND_DRAW_FLAT)
#endif
		if ((camPos*actPoly->polyPlane.normal) <= actPoly->polyPlane.distance) continue;


		// 3D-Clipping am Frustum, in Weltkoordinaten
		if (renderContext.clipFlags>0) {
			if (!actPoly->ClipToFrustum(renderContext.clipFlags)) continue;
		} else actPoly->Unclip();

		// animated Texture-Mapping (muss das _vor_ dem Clippen ?)
		// [EDENFELD] 1.10: Textur Anis nach dem Clippen
		if (actPoly->GetMaterial()) {
			actPoly->GetMaterial()->ApplyTexAniMapping (actPoly);
			if (actPoly->GetMaterial()->GetTexture())
				actPoly->GetMaterial()->GetTexture()->CacheIn (texCacheInPrio);
		};


		// alle verts abgehen
		int	vertCtr = actPoly->numClipVert-1;
		do {
			zCVertex          *actVert = (actPoly->clipVert[vertCtr]); 
			zCVertexTransform *trans;
			if (!actVert->IsTransformed()) {
				// Transform 
                trans = actVert->CreateVertexTransform();
				trans->vertCamSpace= (zCCamera :: activeCam->camMatrix) * (actVert->position);
//				actVert->transformed = masterFrameCtr;

                // Project
				zCCamera:: activeCam->ProjectClamp (trans);
			};

			// 
			if (vertexColor)
				actPoly->clipFeat[vertCtr]->lightDyn = *vertexColor;
		} while (vertCtr--);
		
		// put triangle in to-draw-list
//		if (outside!=actPoly->numClipVert) 
		{
actPoly->LightDynCamSpace (camPos, playerLightInt); 
			zrenderer->DrawPoly (actPoly);
		}
	}

    /*
    for (i = numVert-1; i>=0; i--)  // [Moos] lösche die transformierten Daten.
        vertList[i]->ResetVertexTransform();
    */


	goto renderExitInside;
renderExitInside:;
    zCVertexTransform::PoolRestore(markedPos); // [Moos] So löscht man die Vertices jetzt
	return TRUE;

renderExitOutside:;
	return FALSE;
}


zBOOL zCMesh::RenderHorizon(zTRenderContext& renderContext, zREAL farClipZ) 
{
	// Das Mesh wird in erster Linie nicht weiter beleuchtet, existierende vertex-rgba's bleiben unangetastet
	// Es kann allerdings eine vertexColor angegeben werden, die bei Angabe fuer alle Verts als color eingesetzt wird

	int polyCtr;
    size_t markedPos;
	// im Sinne von: alle verts: "transformed/projected" - flags auf FALSE setzen
	//masterFrameCtr++;

	// setup
	const zPOINT3& camPos	= zCCamera :: activeCamPos; 
	const zREAL ooz			= 1.0f/farClipZ;

	// Texture-CacheIn Prio
	zREAL texCacheInPrio	= ((renderContext.distVobToCam / renderContext.cam->GetFarClipZ())) * 0.5F + 0.25F;
//	if (texCacheInPrio>0.5F) texCacheInPrio=0.5F;

    markedPos = zCVertexTransform::PoolMark(); // [Moos] Alle Allocationen von TransformedVertices sollen nur lokal gelten

	// alle polys abgehen
	for (polyCtr=0; polyCtr<numPoly; polyCtr++) 
	{
		zCPolygon *actPoly = Poly(polyCtr); 
		
		// backface culling (in world(obj)Space) 
#ifdef COMPILING_SPACER
		if (zrenderer->GetPolyDrawMode() != zRND_DRAW_WIRE)
		if (zrenderer->GetPolyDrawMode() != zRND_DRAW_FLAT)
#endif
		if ((camPos*actPoly->polyPlane.normal) <= actPoly->polyPlane.distance) continue;


		// 3D-Clipping am Frustum, in Weltkoordinaten
		if (renderContext.clipFlags>0) {
			if (!actPoly->ClipToFrustum(renderContext.clipFlags)) continue;
		} else actPoly->Unclip();

		// animated Texture-Mapping (muss das _vor_ dem Clippen ?)
		// [EDENFELD] 1.10: Textur Anis nach dem Clippen
		if (actPoly->GetMaterial()) {
			actPoly->GetMaterial()->ApplyTexAniMapping (actPoly);
			if (actPoly->GetMaterial()->GetTexture())
				actPoly->GetMaterial()->GetTexture()->CacheIn (texCacheInPrio);
		};


		// alle verts abgehen
		int	vertCtr = actPoly->numClipVert-1;
		do {
			zCVertex          *actVert = (actPoly->clipVert[vertCtr]); 
			zCVertexTransform *trans;
			if (!actVert->IsTransformed()) {
				// Transform 
                trans = actVert->CreateVertexTransform();
				trans->vertCamSpace= (zCCamera :: activeCam->camMatrix) * (actVert->position);
//				actVert->transformed = masterFrameCtr;

                // Project
				zCCamera:: activeCam->ProjectClamp (trans);
				trans->vertCamSpace.n[VZ] = farClipZ;
				trans->vertCamSpaceZInv   = ooz;
			};

		} while (vertCtr--);
		
		// put triangle in to-draw-list
		zrenderer->AddAlphaPoly(actPoly);
	}

	zrenderer->FlushAlphaPolys();

    zCVertexTransform::PoolRestore(markedPos); // [Moos] So löscht man die Vertices jetzt
	return TRUE;
}



void zCMesh::RenderDecal (const zVALUE xscr, const zVALUE yscr, const zVALUE z, const zBOOL onTop) {
	// z => Screen-Groesse

	zPOINT3 pos;
	pos[VZ]	= z;
	zCCamera::activeCam->BackProject					(xscr, yscr, pos);

	zCCamera::activeCam->camMatrix   .ResetRotation		();
	zCCamera::activeCam->camMatrix   .SetTranslation	(pos);
	zCCamera::activeCam->camMatrixInv.ResetRotation		();
	zCCamera::activeCam->camMatrixInv.SetTranslation	(-pos);

	zCCamera::activeCam->camMatrixInv.GetTranslation	( zCCamera::activeCamPos );
	zCCamera::activeCam->SetUpFrustum(); 

	zTRenderContext renderContext;
	renderContext.Clear();

	RenderDecal (renderContext, onTop);
};


void zCMesh::RenderDecalHorizon (const zVALUE xscr, const zVALUE yscr, const zVALUE z, const zVALUE depth) 
{
	// z => Screen-Groesse

	zPOINT3 pos;
	pos[VZ]	= z;
	zCCamera::activeCam->BackProject					(xscr, yscr, pos);

	zCCamera::activeCam->camMatrix   .ResetRotation		();
	zCCamera::activeCam->camMatrix   .SetTranslation	(pos);
	zCCamera::activeCam->camMatrixInv.ResetRotation		();
	zCCamera::activeCam->camMatrixInv.SetTranslation	(-pos);

	zCCamera::activeCam->camMatrixInv.GetTranslation	( zCCamera::activeCamPos );
	zCCamera::activeCam->SetUpFrustum(); 

	zTRenderContext renderContext;
	renderContext.Clear();

	if (numPoly<=0) return;

	if (renderContext.vob && renderContext.vob->GetIsInWater()) return;

	int polyCtr;
	// im Sinne von: alle verts: "transformed/projected" - flags auf FALSE setzen
	//masterFrameCtr++;

	// setup
	zPOINT3 camPos	= zCCamera :: activeCamPos;
	zVALUE  ooz		= 1.0f/depth;

	// Lage der Mesh-BBox zum Camera-Viewport
	if (renderContext.clipFlags==-1) { 
		renderContext.clipFlags = zCCamera::CLIP_FLAGS_FULL;
		zTCam_ClipType meshClip = zCCamera::activeCam->BBox3DInFrustum (bbox3D, renderContext.clipFlags);
		if (meshClip==zCAM_CLIP_TRIV_OUT) return; 
	};

    size_t markedPos = zCVertexTransform::PoolMark(); // [Moos] Alle Allocationen von TransformedVertices sollen nur lokal gelten

	zVALUE zinv;
	zinv = zVALUE (1) / -camPos[VZ]; 

	// alle polys abgehen
	polyCtr = numPoly-1;
	do {
		zCPolygon *actPoly = Poly(polyCtr); 
		
		// animated Texture-Mapping
		if (actPoly->material) actPoly->material->ApplyTexAniMapping (actPoly);

		// 3D-Clipping am Frustum, in Weltkoordinaten
		if (renderContext.clipFlags>0) {
			if (!actPoly->ClipToFrustum(renderContext.clipFlags)) continue;
		} else actPoly->Unclip();

		// alle verts abgehen
		zCVertex          *actVert	= NULL;
        zCVertexTransform *trans	= NULL;

		int	vertCtr = actPoly->numClipVert-1;
		do {
			actVert = (actPoly->clipVert[vertCtr]); 
			
			if (!actVert->IsTransformed()) {
				// Transform 
                trans = actVert->CreateVertexTransform();

				trans->vertCamSpace= actVert->position - camPos;

				// Project
				zCCamera :: activeCam->ProjectClamp (actVert, zinv);
				trans->vertCamSpaceZInv		= ooz; 
				trans->vertCamSpace.n[VZ]	= depth;
			};
		} while (vertCtr--);
		
        if (!trans)
            trans = actVert->GetVertexTransform();

		// put triangle in to-draw-list
		// nur wenn vor der farClipPlane
		if (trans->vertCamSpace.n[VZ]<zCCamera::activeCam->GetFarClipZ()) 
		{
			// anders wie hier gehts leider nicht, das poly wandert sonst in die sort liste wo es nicht
			// hin darf
			zrenderer->AddAlphaPoly		(actPoly);
			zrenderer->FlushAlphaPolys	();				
		}
	} while (polyCtr--);

    zCVertexTransform::PoolRestore(markedPos); // [Moos] So löscht man die Vertices jetzt


};


/* ----------------------------------------------------------------------
	
    zCMesh::RenderDecal()	

	16.11.2000	[Moos]	
                auf neue Vertex-Klasse umgestellt
    22.11.2000  [Moos]
                Nur die explizit verwendeten Vertices werden zurückgesetzt
     4.12.2000  [Moos]
                Und das wird jetzt effizient über die MemPool-Klassen gemacht
     6.01.2001  [Wohlers]
                CrashFix - "zCVertexTransform *trans" mit NULL initialisiert

   ---------------------------------------------------------------------- */

void zCMesh::RenderDecal (zTRenderContext& renderContext, const zBOOL onTop) {
	// assert:
	// - alle Polys der Cam zugewandt		(=> kein backFace Culling) 
	// - alle Vertices haben dasselbe 'z'	(=> alle Polys planar, schnelleres Project)


	// was hier schneller ist:
	// - nur 0x backface culling
	// - nur 1x GetAniTexture		(weil nur 1 Texture pro Decal erlaubt)
	// bei camAlignFull Decals:
	// - schnellere trafo/Projektion 

	if (numPoly<=0) return;

	if (renderContext.vob && renderContext.vob->GetIsInWater()) return;

	int polyCtr;
	// im Sinne von: alle verts: "transformed/projected" - flags auf FALSE setzen
	//masterFrameCtr++;

	// setup
	zPOINT3 camPos = zCCamera :: activeCamPos;

	// Lage der Mesh-BBox zum Camera-Viewport
	if (renderContext.clipFlags==-1) { 
		renderContext.clipFlags = zCCamera::CLIP_FLAGS_FULL;
		zTCam_ClipType meshClip = zCCamera::activeCam->BBox3DInFrustum (bbox3D, renderContext.clipFlags);
		if (meshClip==zCAM_CLIP_TRIV_OUT) return; 
	};

    size_t markedPos = zCVertexTransform::PoolMark(); // [Moos] Alle Allocationen von TransformedVertices sollen nur lokal gelten

	zVALUE zinv;
	zinv = zVALUE (1) / -camPos[VZ]; 

	// alle polys abgehen
	polyCtr = numPoly-1;
	do {
		zCPolygon *actPoly = Poly(polyCtr); 
		
		// animated Texture-Mapping
		if (actPoly->material) actPoly->material->ApplyTexAniMapping (actPoly);

		// 3D-Clipping am Frustum, in Weltkoordinaten
		if (renderContext.clipFlags>0) {
			if (!actPoly->ClipToFrustum(renderContext.clipFlags)) continue;
		} else actPoly->Unclip();

		// alle verts abgehen
		zCVertex          *actVert	= NULL;
		// [Ulf] : 06.01.01 Codechange : trans wurde nicht initialisiert, spaeterer Zugriff 
		//                  bei trans->vertCamSpace crasht u.U. 
        zCVertexTransform *trans	= NULL;

		int	vertCtr = actPoly->numClipVert-1;
		do {
			actVert = (actPoly->clipVert[vertCtr]); 
			
			if (!actVert->IsTransformed()) {
				// Transform 
                trans = actVert->CreateVertexTransform();

				trans->vertCamSpace= actVert->position - camPos;
//				trans->transformed = masterFrameCtr;

				// Project
				zCCamera :: activeCam->ProjectClamp (actVert, zinv);
				if (onTop)	trans->vertCamSpaceZInv = zVALUE(1) / (zCCamera::activeCam->GetNearClipZ()+1); 
//				if (onTop)	actVert->vertCamSpaceZInv = 1;
				else		trans->vertCamSpaceZInv = zinv; 
			};
		} while (vertCtr--);
		
        if (!trans)
            trans = actVert->GetVertexTransform();

		// put triangle in to-draw-list
		// nur wenn vor der farClipPlane

		if (trans->vertCamSpace.n[VZ]<zCCamera::activeCam->GetFarClipZ()) {
			actPoly->LightDynCamSpace (camPos, playerLightInt); 
			zrenderer->DrawPoly (actPoly);
		}
	} while (polyCtr--);

    zCVertexTransform::PoolRestore(markedPos); // [Moos] So löscht man die Vertices jetzt
}; 

// =========================================================================================================

// FIXME: noch Buggy !??
/*void zCMesh::GetPolysOnPlane (zCPolygon* rootPoly, 
							  zCList<zCPolygon>& outList, 
							  const zBOOL  onlySameMaterial, 
							  const zVALUE tolerance) const {

	zTPlane plane = rootPoly->GetPlane();

	for (int i=0; i<numPoly; i++) {
		zCPolygon *poly = polyList[i];
		if (poly->material==rootPoly->material)
//		if (plane.EqualTo (poly->polyPlane, 0.001F)) {
		if (plane.EqualTo (poly->polyPlane, tolerance)) {
			outList.Insert (poly);
		};
	};
};
*/

// FIXME: noch Buggy !!
/*void zCMesh::GetAdjacentPolysOnPlane (zCPolygon* rootPoly, 
									  zCList<zCPolygon>& outList, 
									  const zBOOL  onlySameMaterial, 
									  const zVALUE tolerance) const {
	zCList<zCPolygon> planePolys;
	GetPolysOnPlane (rootPoly, planePolys, onlySameMaterial, tolerance);

	outList.Insert (rootPoly);

	// Alle OnPlane Polys werden durchgegangen
	zBOOL addedPoly = FALSE;
	do {
		addedPoly = FALSE;
		zCList<zCPolygon> *npoly = &planePolys;
		for (; npoly!=0 ; npoly = npoly->GetNextInList()) {

			zCPolygon *poly = npoly->GetData();

			// benachbartes Poly suchen
			// mit Polys aus der outListe vergleichen
			zCList<zCPolygon> *npoly2 = &outList;
			if (poly)
			for (; npoly2!=0 ; npoly2 = npoly2->GetNextInList()) {
				
				// Test-Poly bereits in der OutList ? => naechstes TestPoly
				zCPolygon *poly2 = npoly2->GetData();
				if (poly==poly2) break;

				// Alle Kanten des Test-Polys mit allen Kanten 
				// des zweiten Polys vergleichen (Ptr oder Positions ??)
				// beachte: zweites Poly muesste invertierte Vert-Reihenfolge haben
				if (poly2)
				for (int v=0; v<poly->polyNumVert; v++) {
					int v2= v+1; 
					if (v2>=poly->polyNumVert) v2=0;
					
					// Test-Poly Kante: vertex[v] vertex[v2]
					for (int k=0; k<poly2->polyNumVert; k++) {
						int k2= k+1; 
						if (k2>=poly2->polyNumVert) k2=0;
						if (((poly->vertex[v ]->position==poly2->vertex[k ]->position)  &&
							 (poly->vertex[v2]->position==poly2->vertex[k2]->position)) ||
							((poly->vertex[v ]->position==poly2->vertex[k2]->position)  &&
							 (poly->vertex[v2]->position==poly2->vertex[k ]->position))) 
						{
							// yep ! shared Edge gefunden !
							addedPoly = TRUE;
							outList.Insert (poly);
							goto loopExit;
						};
					};
				};
			};
	loopExit:;
		};
	} while (addedPoly);
};
*/

/*
>from O'rourke :
>Area2 (tpoint a,b,c) {
>  return a[0]*b[1]-a[1]*b[0] + a[1]c[0]-[0]*c[1] + b[0]*c[1]-c[0]*b[1];
>}
>
>boolean is_on_left ( tpoint a,b,c) {
>  return Area2 (a,b,c) > 0;
>}
>
>and something like this :
>
>is_convex := true;
>for i:=0 to Poly.length-1 do
>  is_convex := is_convex AND is_on_left (Poly[i],Poly[i+1],Poly[i+2]);

This has a minor problem in that it assumes polygons are defined in
anticlockwise order.  If you don't know the order, you have to check
that is_on_left() returns either all-true or all-false values.  (Also,
the i+1 and i+2 indices have to wrap around, modulo Poly.length.)

A more subtle problem is that it works only if you know for sure that
the polygon is simple, i.e. not self-intersecting.  O'Rourke uses this
definition of a polygon.
*/

/*
	- Mesh optimize
		- alle planaren Polys sammeln (gleiche Materialien)
		- ein Poly raussuchen & gegen alle anderen testen
			- Score: neues poly/Vertlist bewerten:
				- stimmen die tex-UV an den Kanten ?
				- convex ?
				- Groesse ?
				- Seitenverhaeltnisse
		- 
*/

// =========================================================================================================

void zCMesh::ResetStaticLight () {
	for (int i=0; i<numPoly; i++) SharePoly(i)->ResetStaticLight();
};

void zCMesh::SetStaticLight (const zCOLOR lightStat) {
	for (int i=0; i<numPoly; i++) SharePoly(i)->SetStaticLight(lightStat);
};

void zCMesh::SetLightDyn (const zCOLOR lightDyn) {
	for (int i=0; i<numPoly; i++) SharePoly(i)->SetLightDyn (lightDyn);
};

void zCMesh::SetLightStatAlpha (const zBYTE alpha) {
	for (int i=0; i<numPoly; i++) SharePoly(i)->SetLightStatAlpha (alpha);
};

void zCMesh::ResetLightDynToLightStat () {
	for (int i=0; i<numPoly; i++) SharePoly(i)->ResetLightDynToLightStat();
};

void zCMesh::AddToLightDyn (const zCOLOR lightDelta) {
	for (int i=0; i<numPoly; i++) SharePoly(i)->AddToLightDyn (lightDelta);
};

// =========================================================================================================

zCMesh* zCMesh::CreateQuadMesh (const zBOOL twoSided) 
{
//	decalMesh = zCMesh::Load ("_intern\\decalMesh.3ds");
	zCMesh* decalMesh = zNEW(zCMesh);
	decalMesh ->AllocVerts	(4);
	zCVertex*	vert4	= decalMesh ->AddVertex	(zPOINT3(-50, +50, 0));
	zCVertex*	vert3	= decalMesh ->AddVertex	(zPOINT3( 50,  50, 0));
	zCVertex*	vert2	= decalMesh ->AddVertex	(zPOINT3(+50, -50, 0));
	zCVertex*	vert1	= decalMesh ->AddVertex	(zPOINT3(-50, -50, 0));
 
	if (!twoSided) {
		// one-sided
		decalMesh ->AllocPolys	(1);
		zCPolygon*	poly	= decalMesh ->AddPoly	(vert1,vert2,vert3,vert4);

		// Tex-Coords setzen
		poly->SetMapping (3, zVEC2(0.0,0.0));
		poly->SetMapping (2, zVEC2(1.0,0.0));
		poly->SetMapping (1, zVEC2(1.0,0.99f));
		poly->SetMapping (0, zVEC2(0.0,0.99f));

		poly->material = 0;
	} else {
		// two-sided
		decalMesh ->AllocPolys	(2);

		zCPolygon*	poly1	= decalMesh ->AddPoly	(vert1,vert2,vert3,vert4);
		zCPolygon*	poly2	= decalMesh ->AddPoly	(vert2,vert1,vert4,vert3);

		// Tex-Coords setzen
		poly1->SetMapping (3, zVEC2(0.0,0.0));
		poly1->SetMapping (2, zVEC2(1.0,0.0));
		poly1->SetMapping (1, zVEC2(1.0,0.99f));
		poly1->SetMapping (0, zVEC2(0.0,0.99f));

		poly2->SetMapping (2, zVEC2(0.0,0.0));
		poly2->SetMapping (3, zVEC2(1.0,0.0));
		poly2->SetMapping (0, zVEC2(1.0,0.99f));
		poly2->SetMapping (1, zVEC2(0.0,0.99f));

		poly1->material = poly2->material = 0;
	};

	decalMesh ->CalcBBox3D			();
	decalMesh ->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_FACET); 
	return decalMesh;
};

zCMesh* zCMesh::CreateTriMesh () {
//	decalMesh = zCMesh::Load ("_intern\\decalMesh.3ds");
	zCMesh* decalMesh = zNEW(zCMesh);
	decalMesh ->AllocVerts	(3);
	zCVertex*	vert3	= decalMesh ->AddVertex	(zPOINT3(-50, +50, 0));
	zCVertex*	vert2	= decalMesh ->AddVertex	(zPOINT3( 50,  50, 0));
	zCVertex*	vert1	= decalMesh ->AddVertex	(zPOINT3(-50, -50, 0));
 
	// one-sided
	decalMesh ->AllocPolys	(1);
	zCPolygon*	poly	= decalMesh ->AddPoly	(vert1,vert2,vert3);

	// Tex-Coords setzen
	poly->SetMapping (2, zVEC2(0.0,0.0));
	poly->SetMapping (1, zVEC2(1.0,0.0));
	poly->SetMapping (0, zVEC2(0.0,1.0));

	poly->material = 0;

	decalMesh ->CalcBBox3D			();
	decalMesh ->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_FACET); 
	return decalMesh;
};

// =========================================================================================================

//static inline zREAL TexCoordFrac (const zREAL c) { 
//	return c -zFloor (c);
//};

zBOOL zCMesh::CheckTexUVOnPlane (const zCArray<zCVertex*> &vertList, const zCArray<zCVertFeature> &featList)
{
	// zunaechst 3 nicht-kolineare Verts suchen
	zBOOL	result = TRUE;
	int		n=2;
	do {
		zVEC3 u		= (vertList[1]->position-vertList[0]->position);
		zVEC3 v		= (vertList[n]->position-vertList[1]->position);
		zREAL lenu	= u.Length();
		zREAL lenv	= v.Length();
		if ((u!=0) && (v!=0))
		{
			u		/= lenu;
			v		/= lenv;
			zBOOL	colinear= u.IsEqualEps(v) || u.IsEqualEps(-v);
			if (!colinear) 
			{
				break;
			};
		};
		n++;
	} while (n<vertList.GetNum());

	if (n>=vertList.GetNum())
	{
		// Falls keine 3 nicht-kolinearen Verts gefunden werden, gelten die TexUVS trotzdem als "OnPlane"
		result = TRUE;
	} else 
	{
		// jetzt fuer anhand 3er Referenz-Verts (innerhalb des NPolys) die uebrigen Verts
		// ueberpruefen 
		for (int i=2; i<vertList.GetNum(); i++)
		{
			if (i==n) continue;
			zVEC3	q		= vertList[i]->position - vertList[0]->position;

			zPOINT3 a		= vertList[1]->position - vertList[0]->position;
			zPOINT3 b		= vertList[n]->position - vertList[0]->position;
			zREAL ab		= (a*b);
			zREAL bb		= (b*b);
			zREAL qb		= (q*b);
			zREAL x			= ((bb) * (q*a) - (ab) * (qb)) / ((a*a)*(bb) - ((ab)*(ab)));
			zREAL y			= ((qb) - x*(ab)) / (bb);

			zVEC2 texUVBase	= zVEC2(featList[0].texu, featList[0].texv);
			zVEC2 delta0	= zVEC2(featList[1].texu, featList[1].texv) - texUVBase;
			zVEC2 delta1	= zVEC2(featList[n].texu, featList[n].texv) - texUVBase;

			zVEC2 texUV		= texUVBase + x*delta0 + y*delta1;
			if ((zAbs(featList[i].texu-texUV[0])>zREAL(0.05F)) ||
				(zAbs(featList[i].texv-texUV[1])>zREAL(0.05F))) 
			{
				result= FALSE;
				break;
			};
		};
	};
	return result;
};

void zCMesh::ConvertTrisToNPolys (zCPolygon **inPolyList, int inPolyNum, zCMesh* homeMesh, 
								  const zBOOL onlySectorPolys) {
	// TODO:	- viele Polys enthalten mehr Verts als noetig
	//			- bei einem Poly alle moeglichen Verschmelzungen pruefen & mit Score bewerten

	zerr.Message ("D: MSH: Converting tris to n-Polys...");

	// hohe FPU Precision sicherstellen
	const zDWORD fpuControlWord	= zfpuControler.GetCurrentControlWord();
	zfpuControler.SetPrecision_53();

	const int EPS_SETS=3;
	enum {
		EPS_DEFAULT		=0,
		EPS_AGGRESSIVE	=1,
		EPS_PORTAL		=2,
	};
	//											0=default,		1=aggresiv,		2=portale
	zREAL EPSILON_PLANE_DISTANCE[EPS_SETS]	= { zREAL(0.1F),	zREAL(0.1F),	zREAL(50.0F)	};
	zREAL EPSILON_PLANE_NORMAL	[EPS_SETS]	= { zREAL(0.95F),	zREAL(0.95F),	zREAL( 0.80F)	};
	zREAL EPSILON_UV			[EPS_SETS]	= { zREAL(0.01F),	zREAL(0.01F),	zREAL( 0.10F)	};
	zREAL EPSILON_CONVEX		[EPS_SETS]	= { zREAL(0.00F),	zREAL(0.00F),	zREAL( 0.80F)	};
	zBOOL CHECK_TEXUV_PLANE		[EPS_SETS]	= { TRUE,			TRUE,			FALSE			};
	int USE_EPS=EPS_DEFAULT;

	//
/*	zREAL EPSILON_PLANE_DISTANCE	= zREAL(0.1F);		// 0.1
	zREAL EPSILON_PLANE_NORMAL		= zREAL(0.95F);		// 0.95
	zREAL EPSILON_UV				= zREAL(0.01F);
	zREAL EPSILON_CONVEX			= zREAL(0.0F);
	zBOOL CHECK_TEXUV_PLANE			= TRUE;
	if (onlySectorPolys) {
		// Im Outdoor (speziell fuer Portale wichtig) werden aggressive Epsilons verwendet..
		EPSILON_PLANE_DISTANCE		= zREAL(50.0F);		// 20
		EPSILON_PLANE_NORMAL		= zREAL(0.8F);		// 0.8
		EPSILON_UV					= zREAL(0.10F);		// 0.05
		EPSILON_CONVEX				= zREAL(0.8F);		// 0.1
		CHECK_TEXUV_PLANE			= FALSE;
	};
*/
	//
	int maxVert=0;

	zCArray<zCPolygon*>		polyList(inPolyNum);
	zCArray<zCPolygon*>		onPlanePolyList;
	zCArray<zCVertex*>		vertList(32);
	zCArray<zCVertFeature>	featList(32);
	int i;
	int polysRemoved=0;

	// Polyliste kopieren
	for (i=0; i<inPolyNum; i++) {
		if (onlySectorPolys) {
			if (!inPolyList[i]->GetSectorFlag()) continue;
		};
//doit:;
		polyList.Insert (inPolyList[i]);
	};

	while (polyList.GetNumInList()>0) {

		// alle Polys in derselben Ebene & mit demselben Material einsammeln
		onPlanePolyList.EmptyList();
		zTPlane		plane		= polyList[0]->GetPlane();
		zCPolygon	*testPoly	= polyList[0];

		// welchen Epsilon-Satz benutzen ?
		if (testPoly->GetMaterial()->IsPortalMaterial())	USE_EPS = EPS_PORTAL;		else
		if (onlySectorPolys)								USE_EPS = EPS_AGGRESSIVE;	
		else												USE_EPS = EPS_DEFAULT;

		for (i=0; i<polyList.GetNumInList(); i++) 
		{
			zCPolygon	*poly	= polyList[i];
			if (testPoly->GetMaterial()==poly->GetMaterial()) 
			if ((zAbs((plane.distance)-(poly->GetPlane().distance))	<= EPSILON_PLANE_DISTANCE	[USE_EPS]) && 
				(    (((plane.normal) *(poly->GetPlane().normal)))	>= EPSILON_PLANE_NORMAL		[USE_EPS]))

			{
				onPlanePolyList	.Insert			(poly);
				polyList		.RemoveIndex	(i);
				i--;
			};
		};
//		zerr.Message ("numOnPlane: "+zSTRING(onPlanePolyList.GetNumInList())+", plane: "+plane.Print());
		if (onPlanePolyList.GetNumInList()<=1) continue;

		// 2) Closest Axis finden (solid) (Achse, mit groesstem Abs-Wert)
		int		vx, vy, vz;
		zVEC2	a;
		a[VX]	= zAbs(plane.normal[VX]);
		a[VY]	= zAbs(plane.normal[VY]);
		vz		= a[VX]	< a[VY]					 ? VY : VX;
		vz		= a[vz]	< zAbs(plane.normal[VZ]) ? VZ : vz;
		vx		= vz+1; if (vx>2) vx=0;
		vy		= vx+1; if (vy>2) vy=0;

		//
testNextPair:;
		for (i=0; i<onPlanePolyList.GetNumInList(); i++) {
			zCPolygon *poly = onPlanePolyList[i];

			for (int j=0; j<onPlanePolyList.GetNumInList(); j++) {
				zCPolygon *poly2 = onPlanePolyList[j];
				if (poly==poly2) continue;

				// teilen die 2 Polys eine Kante mit denselben Features ?
				for (int k=0; k<poly->polyNumVert; k++) {
					int knext=k+1;	if (knext>=poly->polyNumVert) knext=0;
					zCVertex *vert1	= poly->vertex[k];
					zCVertex *vert2	= poly->vertex[knext];

//					int l, lnext;
//					for (lnext=0, l= poly2->polyNumVert-1; lnext<poly2->polyNumVert; l=lnext++) {
					for (int l=0; l<poly2->polyNumVert; l++) 
					{
						int lnext=l+1;	if (lnext>=poly2->polyNumVert) lnext=0;
						if ((poly2->vertex[l]==vert2) && (poly2->vertex[lnext]==vert1)) 
						{
/*							if ((zAbs(TexCoordFrac(poly2->feature[l    ]->texu) - TexCoordFrac(poly->feature[knext]->texu))) > THRESH) continue;
							if ((zAbs(TexCoordFrac(poly2->feature[l    ]->texv) - TexCoordFrac(poly->feature[knext]->texv))) > THRESH) continue;
							if ((zAbs(TexCoordFrac(poly2->feature[lnext]->texu) - TexCoordFrac(poly->feature[k	  ]->texu))) > THRESH) continue;
							if ((zAbs(TexCoordFrac(poly2->feature[lnext]->texv) - TexCoordFrac(poly->feature[k	  ]->texv))) > THRESH) continue;*/

							if ((zAbs(poly2->feature[l    ]->texu - poly->feature[knext]->texu)) > EPSILON_UV[USE_EPS]) continue;
							if ((zAbs(poly2->feature[l    ]->texv - poly->feature[knext]->texv)) > EPSILON_UV[USE_EPS]) continue;
							if ((zAbs(poly2->feature[lnext]->texu - poly->feature[k	   ]->texu)) > EPSILON_UV[USE_EPS]) continue;
							if ((zAbs(poly2->feature[lnext]->texv - poly->feature[k	   ]->texv)) > EPSILON_UV[USE_EPS]) continue;

							// ja, die Polys teilen diese Kante
							// vert/feat List des resutlierenden Polys erzeugen
							vertList.EmptyList();
							featList.EmptyList();
							for (int m=0; m<poly->polyNumVert; m++) {
								if (m==k) {
									// hier nun die Verts des zweiten Polys einfuegen
									int p2vert =lnext;
									for (int n=0; n<poly2->polyNumVert; n++) {
										vertList.Insert (  poly2->vertex [p2vert]);
										featList.Insert (*(poly2->feature[p2vert]));
										p2vert++; if (p2vert>=poly2->polyNumVert) p2vert=0;
									};
								} else 
								if (m!=knext) {
									vertList.Insert (  poly->vertex [m]);
									featList.Insert (*(poly->feature[m]));
								};
							};
							// alle Schlaufen/doppelten Verts herausnehmen
							// FIXME: wraparound
							// FIXME: Verts auch aus dem Mesh entfernen ??????????????

							// FIXME: scheint buggy zu sein (stuerzt nur im Release ab ??)
							if (0)
							for (int r=0; r<vertList.GetNumInList()-1; r++) {
								zCVertex *v1 = vertList[r];
								for (int s=r+1; s<vertList.GetNumInList(); s++) {
									zCVertex *v2 = vertList[s];
									if (v1==v2) {
										for (int t=r+1; t<=s; t++) {
											vertList.RemoveOrderIndex (r+1);
											featList.RemoveOrderIndex (r+1);
										};
										break;
									};
								};
							};

							// maximale Vert-Zahl erreicht ??
							if (vertList.GetNumInList()<3) {
//								zerr.Report (zERR_WARN, 1000, " < 3 Verts !");
								continue;
							};
							if (vertList.GetNumInList()>zMAX_POLY_VERTS) continue;

							// waere die Verschmelzung der Polys noch konvex ?
							// (quelle: paul bourke, geometry)
							zBOOL	isConvex= TRUE;
							int		o, onext1, onext2;
							int		flag	= 0;
							zREAL	z;
							for (o=0; o<vertList.GetNumInList(); o++) {
								onext1			= o     +1; if (onext1>=vertList.GetNumInList()) onext1 = 0;
								onext2			= onext1+1; if (onext2>=vertList.GetNumInList()) onext2 = 0;
								const zPOINT3& a= vertList[o	 ]->position;	// i
								const zPOINT3& b= vertList[onext1]->position;	// j
								const zPOINT3& c= vertList[onext2]->position;	// k
								z  = (b[vx]-a[vx]) * (c[vy]-b[vy]);
								z -= (b[vy]-a[vy]) * (c[vx]-b[vx]);
								if (z<-EPSILON_CONVEX[USE_EPS])		flag |= 1; else
								if (z>+EPSILON_CONVEX[USE_EPS])		flag |= 2;
								if (flag==3)		{ isConvex=FALSE; break; };
								if (a==c)			{ isConvex=FALSE; break; };
							};

							// Das potentielle NPoly ist nur korrekt, wenn die TexUV Koords aller verts in ein und
							// derselben Ebene liegen. Darauf wird hier geprueft. Wuerden Polys, die diesen Test nicht
							// bestehen, trotzdem gerendert werden waeren Textur-Verzerrungen die Folge
							if (isConvex)
							if (CHECK_TEXUV_PLANE[USE_EPS])
							{
								isConvex = CheckTexUVOnPlane (vertList ,featList);
							};

							if (isConvex) {
/*								zCMaterial *mat = zNEW(zCMaterial());
								mat->SetColor (zRand(), zRand(), zRand());  
								poly ->SetMaterial (mat);
								poly2->SetMaterial (mat);

*/								// Polys verschmelzen
								poly->RemoveVerticesAndFeatures ();
								poly->AllocVerts				(vertList.GetNumInList());
//								for (int p=0; p<vertList.GetNumInList(); p++) {
								for (int p=vertList.GetNumInList()-1; p>=0; p--) {
									poly->SetVertex		(p,   vertList[p]);
									poly->SetFeature	(p, &(featList[p]));
								};
								
								maxVert = zMax (maxVert, poly->polyNumVert);
								onPlanePolyList	.Remove (poly2);
								if (homeMesh) {
									homeMesh->DeletePoly (poly2);
								};
								polysRemoved++;
								goto testNextPair;
							};
						};
					};
				};
			};
		};
	};
	zerr.Message ("D: MSH: ..polys removed: "+zSTRING(polysRemoved)+", maxVert: "+zSTRING(maxVert));

	//
	zfpuControler.SetControlWord	(fpuControlWord);
};


// =========================================================================================================

static const zWORD zMESH_FILE_VERS					= 9;

static const zWORD zFCHUNK_MESH						= 0xB000;
static const zWORD		zFCHUNK_BBOX3D				= 0xB010;
static const zWORD		zFCHUNK_MATLIST				= 0xB020;
static const zWORD		zFCHUNK_LIGHTMAPLIST		= 0xB025;
static const zWORD		zFCHUNK_LIGHTMAPLIST_SHARED = 0xB026;
static const zWORD		zFCHUNK_VERTLIST			= 0xB030;
static const zWORD		zFCHUNK_FEATLIST			= 0xB040;
static const zWORD		zFCHUNK_POLYLIST			= 0xB050;
static const zWORD		zFCHUNK_MESH_END			= 0xB060;

static const zDWORD zMSH_FILE_MAX_VERT = 65535;
static const zDWORD zMSH_FILE_MAX_FEAT = zDWORD(65535)*zDWORD(65535);

zWORD zCMesh::GetFileVersion ()			// gesamt: 16 Bit!!
{ 
	zWORD vers = zWORD(zCTextureFileFormatInternal::GetStaticClassDef()->GetArchiveVersion()) << 8;
	vers += zMESH_FILE_VERS; 
	return vers; 
};

#pragma pack (push, 1)							// Alignment ausschalten
	typedef int		zTVertIndex;
	typedef zDWORD	zTFeatIndex;

	struct zTMSH_LightmapChunk {
    	zVEC3 lmVectors[3];
        int   texIndex;
	};

	struct zTMSH_FeatureChunk {
		zREAL		texu;
		zREAL		texv;
		zCOLOR		lightStat;
		zVEC3		vertNormal;
	};

	class zTMSH_PolyChunk {
	public:
		zSWORD				matIndex;
		zSWORD				lightmapIndex;
		zTPlane				polyPlane;
		zCPolygon::TFlags	flags;
		zBYTE				polyNumVert;
	};

	class zTMSH_PolyReadChunk : public zTMSH_PolyChunk {
	public:
		struct zTIndex {
			zTVertIndex		vertIndex;
			zTFeatIndex		featIndex;
		};
		zTIndex				indexList[255];
	};
#pragma pack (pop)								// Alignment ausschalten

void zCMesh::SaveMSH (zCFileBIN& file) {
	SaveMSH (file, polyList, numPoly, this);
};

void zCMesh::SaveMSH (const zSTRING& fileName) {
	zerr.Message		("D: MSH: Saving Mesh: "+fileName);

	// [BENDLIN] Addon Patch - Meshes im Soundverzeichnis
//	zoptions->ChangeDir		(DIR_COMPILED_MESHES);
	zCFileBIN file;
	file.BinCreate		(zoptions->GetDirString(DIR_COMPILED_MESHES) + fileName); 
	SaveMSH				(file);
	file.BinClose		();
};


/* ----------------------------------------------------------------------
	
    zCMesh::SaveMSH()

	16.11.2000	[Moos]	
                auf neue Vertex-Klasse umgestellt
    29.11.2000  [Moos]
                Lightmap-Zusammenfassung hinzugefügt
     6.11.2000  [Moos]
                Zerkronkelung der VertexTransform-Daten verhindert

   ---------------------------------------------------------------------- */

void zCMesh::SaveMSH (zCFileBIN& file, zCPolygon** polyList, int numPoly, zCMesh* mesh) {

	// vorsichtshalber alle gemorphten vertices reseten, man weiss ja nie
	zCPolygon::S_ResetMorphedVerts();

#ifdef DEBUG_MOOS_X
    if (mesh)
    {
        mesh->ShareFeatures();
        mesh->CreateListsFromArrays();
    }
#endif
    

    zCVertex::ResetVertexTransforms();

    if (mesh)
	{
        mesh->CreateListsFromArrays();
	}


	// assert:
	// < 255   Verts pro Poly
	int i;

	file.BinStartChunk			 		(zFCHUNK_MESH);
	{
		file.BinWriteWord				(zCMesh::GetFileVersion());
//		if (mesh)	file.BinWriteString	(mesh->GetMeshName());
//		else		file.BinWriteString	(zSTRING(""));

		// Date & Name des Source-.3DS schreiben
		zSTRING		meshName;
		zFILE_STATS	sourceStats;
		if (mesh) 
		if (mesh->GetMeshName().Length()>0)
		if (mesh->GetMeshName()[0]!='#')
		{
			meshName = mesh->GetMeshName(); 
			zoptions->ChangeDir		(DIR_MESHES);
			zPATH meshPath		(meshName);
			if (meshPath.SearchFile(meshPath.GetFilename()+"."+meshPath.GetExt(), zSTRING(zFILE::GetCurrentDir()))!=zERR_NONE) {
				zERR_WARNING("D: MSH: z3d(zCMesh::SaveMSH): source-file not found: "+mesh->GetMeshName());
				meshName.Clear	();
			};
			// 3DS gefunden
			zFILE* meshFile	= zfactory->CreateZFile(meshPath.GetPath());
			meshFile->GetStats	(sourceStats); 
			delete meshFile;
		} else {
			meshName.Clear();
			//sourceStats;
		};

		file.BinWrite		(&(sourceStats.modifyDate), sizeof(sourceStats.modifyDate));
		file.BinWriteString	(meshName);
	};

	zCArray	   <zCVertex*>		vertList(numPoly / 2);
	zCArray	   <zCVertFeature*>	featList;
	//featList.SetCompare(Compare_Features);

	if (mesh) {
		polyList= mesh->polyList;
		numPoly	= mesh->numPoly;
	};

	// TexCorrectUV() => safety
	for (i=0; i<numPoly; i++) 
	{
		// Workaround: das Wasser besteht aus sehr vielen Polys mit einer einzigen Textur. 
		// TexCorrectUV() darf auf diesen Polys nicht ausgeführt werden, da ansonsten
		// die Texturkoords geschrottet werden. Workaround: Alles was sich dynamisch bewegt
		// bekommt keine TexUV Korrektur
		if (polyList[i]->GetMaterial()->GetWaveAniMode()==zWAVEANI_NONE)	
			polyList[i]->TexCorrectUV();
	};


	//return;

	// Vertices einsammeln
	if (mesh) 
	{
		zERR_MESSAGE(5,0,"C: mesh given, counting vertex & features...");
		zERR_MESSAGE(5,0,"C: number of verts before merging them: " + zSTRING(mesh->numVert));
		zERR_MESSAGE(5,0,"C: number of feats before merging them: " + zSTRING(mesh->numFeat));

		if (!zoptions->Parm("ZENSAVEOLDMETHOD"))
		{
			if (mesh->numFeat==0 || mesh->FeatList()==0)
			{
				mesh->ClearLists();
				mesh->ShareFeatures();
				mesh->CreateListsFromArrays();
			}

			vertList.AllocAbs(mesh->numVert);
			featList.AllocAbs(mesh->numFeat);

			for (int i=0; i<mesh->numVert; i++) {
				vertList.InsertEnd (mesh->vertList[i]);
			};
			
			// geshared ?
			if ( mesh->numFeat>0 && mesh->FeatList()!=0 )
			{
				// ja, speichere alle gesharten Features 
				for (i=0; i<mesh->numFeat; i++) {
					featList.InsertEnd (mesh->featList[i]);
				};
			}
			else
			{
				for (i=0; i<numPoly; i++) 
				{
					zCPolygon *poly = polyList[i];
					for (int j=0; j<poly->polyNumVert; j++) 
					{
						featList.InsertEnd(poly->feature[j]);			// SHARED
					};
					if  ((i!=0) && ((i&4095)==0)) zERR_MESSAGE (3, 0, "D: ... still working ("+zSTRING(i)+" polys)");
				};
				zERR_MESSAGE(5,0,"C: number of verts after merging them: " + zSTRING(vertList.GetNum()));
				zERR_MESSAGE(5,0,"C: number of feats after merging them: " + zSTRING(featList.GetNum()));
			}
		}
		else
		{
			vertList.AllocAbs(mesh->numVert);
			for (int i=0; i<mesh->numVert; i++) 
			{
				vertList.Insert (mesh->vertList[i]);
			};
			for (i=0; i<numPoly; i++) 
			{
				zCPolygon *poly = polyList[i];
				for (int j=0; j<poly->polyNumVert; j++) 
				{
					if (!featList.IsInList (poly->feature[j])) featList.InsertEnd(poly->feature[j]);			// SHARED
				};
				if  ((i!=0) && ((i&4095)==0)) zERR_MESSAGE (3, 0, "D: ... still working ("+zSTRING(i)+" polys)");
			};

			zERR_MESSAGE(5,0,"C: number of verts after merging them: " + zSTRING(vertList.GetNum()));
			zERR_MESSAGE(5,0,"C: number of feats after merging them: " + zSTRING(featList.GetNum()));
		}
	} 
	else 
	{
		zERR_MESSAGE(5,0,"C: no mesh given, counting vertex & features of polylist...");
		zERR_MESSAGE(5,0,"C: number of verts before merging them: " + zSTRING(mesh->numVert));
		zERR_MESSAGE(5,0,"C: number of feats before merging them: " + zSTRING(mesh->numFeat));

		for (i=0; i<numPoly; i++) 
		{
			zCPolygon *poly = polyList[i];
			for (int j=0; j<poly->polyNumVert; j++)
			{
				if (!vertList.IsInList (poly->vertex [j]))	vertList.InsertEnd  (poly->vertex[j]);
				if (!featList.IsInList (poly->feature[j]))	featList.InsertEnd	(poly->feature[j]);		// SHARED
			};
			if  ((i!=0) && ((i&4095)==0)) zERR_MESSAGE (3, 0, "D: ... still working ("+zSTRING(i)+" polys)");
		};

		zERR_MESSAGE(5,0,"C: number of verts after merging them: " + zSTRING(vertList.GetNum()));
		zERR_MESSAGE(5,0,"C: number of feats after merging them: " + zSTRING(featList.GetNum()));
	};

#if 0
	if (vertList.GetNumInList()>zMSH_FILE_MAX_VERT) {
		zerr.Fatal ("D: z3d(zCMesh::SaveMSH): too many verts in Mesh...");
	};
	if (featList.GetNumInList()>zMSH_FILE_MAX_FEAT) {
		zerr.Fatal ("D: z3d(zCMesh::SaveMSH): too many feats in Mesh...");
	};
#endif

	// BBox
	if (mesh) {
		file.BinStartChunk		(zFCHUNK_BBOX3D);
		{
			mesh->bbox3D .SaveBIN (file);
			mesh->obbox3D.SaveBIN (file);
		}
	};

	// Material-List
	zCArray<zCMaterial*> matList;
	zBOOL alphaTesting = FALSE;
	for (i=0; i<numPoly; i++) {
		zCMaterial *mat = polyList[i]->GetMaterial();
		if (!matList.IsInList(mat)) 
		{
			matList.Insert (mat);
			if ( mat->GetTexture() )
			{
				mat->GetTexture()->CacheIn(-1); // muss, ansonsten ist hier der alpha state noch unbekannt
				if ( mat->GetTexture()->HasAlpha() ||
					 mat->GetAlphaBlendFunc() == zRND_ALPHA_FUNC_TEST   ) 
				{
					alphaTesting = TRUE;
				}
			}
		}
	};
	if (matList.GetNumInList()>0) {
		file.BinStartChunk		(zFCHUNK_MATLIST);
		{
			{
				zCArchiver *arc = zarcFactory.CreateArchiverWrite (file.file, zARC_MODE_BINARY, FALSE, zARC_FLAG_WRITE_BRIEF_HEADER); // noSaveGame, briefHeader
				zERR_ASSERT_STRICT (arc);

				arc->WriteInt		("",matList.GetNum());
				for (i=0; i<matList.GetNumInList(); i++) 
				{
					arc->WriteString	("",matList[i]->GetName());
					arc->WriteObject	(matList[i]);
				};
				arc->WriteBool("",alphaTesting);
				arc->Close			();
				zRELEASE (arc);
			};
		};
	};

	// Lightmap-List

   	zCArraySort<zCLightMap*>	lmList;

	{
       	zCArraySort<zCTexture*>	lmTexList;
	
        for (i=0; i<numPoly; i++) {
			zCLightMap *lm = polyList[i]->GetLightmap();
			if (lm)	
            {
    			if (!lmList.IsInList(lm))
                    lmList.InsertSort (lm);

            
                zCTexture *lmTex = lm->Texture();
                zERR_ASSERT_STRICT(lmTex);

                if (!lmTexList.IsInList(lmTex))
                    lmTexList.InsertSort(lmTex);
	        }
    	};

		if (lmList.GetNumInList()>0) {
			file.BinStartChunk		(zFCHUNK_LIGHTMAPLIST_SHARED);
			{
                file.BinWriteInt    (lmTexList.GetNumInList());  // Schreibe zuerst die rohen Texturen

				for (i=0; i<lmTexList.GetNumInList(); i++)
					lmTexList[i]->SaveAndConvertInternal	(*file.file);

                zTMSH_LightmapChunk chunk;

				file.BinWriteInt	(lmList.GetNumInList());    // Dann die Lightmap-Koordinaten mit index auf die Texturen

				for (i=0; i<lmList.GetNumInList(); i++) {
        			chunk.texIndex	= lmTexList.Search  (lmList[i]->Texture());
					lmList[i]->GetLightmapOriginUpRight (chunk.lmVectors[0], chunk.lmVectors[1], chunk.lmVectors[2]);
					file.BinWrite						(&chunk, sizeof(chunk));
				};
			};
			lmList.QuickSort();
		};
	};

    /* [Moos] Alte version:

	zCArraySort<zCTexture*>	lmList;
	{
		for (i=0; i<numPoly; i++) {
			zCTexture *lm = polyList[i]->GetLightmap();
			if (lm)	
			if (!lmList.IsInList(lm)) lmList.InsertSort (lm);
		};
		if (lmList.GetNumInList()>0) {
			file.BinStartChunk		(zFCHUNK_LIGHTMAPLIST);
			{
				file.BinWriteInt	(lmList.GetNumInList());
				zVEC3 lmVectors[3];
				for (i=0; i<lmList.GetNumInList(); i++) {
					lmList[i]->GetLightmapOriginUpRight (lmVectors[0], lmVectors[1], lmVectors[2]);
					file.BinWrite						(&lmVectors, sizeof(lmVectors));
					lmList[i]->SaveAndConvertInternal	(*file.file);
				};
			};
			lmList.QuickSort();
		};
	};
    */

//    zERR_ASSERT_STRICT(vertList.GetNumInList() < 65000); // [Moos] Damits noch in ein UWORD passt; doch nicht mehr nötig

	// Vertex-List
	// ACHTUNG: zCVertex::vertScrX wird als Index-Speicher "misbraucht" !
	file.BinStartChunk		(zFCHUNK_VERTLIST);
	{
		file.BinWriteInt	(vertList.GetNumInList());
		for (i=0; i<vertList.GetNumInList(); i++) {
			zCVertex *vert		= vertList[i];

            zERR_ASSERT           (vert->transformedIndex == 0);

			vert->hackData		= i;  // [Moos] so, das geht jetzt richtig.
			// Vertex Data
			file.BinWrite		(&vert->position, sizeof(vert->position));
		};
	}

	// Feature-List
	// ACHTUNG: zCVertFeature::lightDyn wird als Index-Speicher "misbraucht" !
	file.BinStartChunk		(zFCHUNK_FEATLIST);
	{
		file.BinWriteInt	(featList.GetNumInList());
		zCOLOR tmpColor;
		for (i=0; i<featList.GetNumInList(); i++) {
			zCVertFeature *feat	= featList[i];
			tmpColor.dword		= i;
			feat->lightDyn		= tmpColor;
			// Feature Data
			zTMSH_FeatureChunk	chunk;
			chunk.texu			= feat->texu;
			chunk.texv			= feat->texv;
			chunk.lightStat		= feat->lightStat;
			chunk.vertNormal	= feat->vertNormal;
			file.BinWrite		(&chunk, sizeof(chunk));
		};
	}

	// Poly-List 

	// FIXME: hier evtl. 2 versch. alternative Chunks: indoor/lightmap, outdoor/%

// FIXME: ueber das BinFile/zFILE wird fuer diesen Chunk eine falsche, zu grosse Groesse ermittelt
//        (z.B. beim Groundshadow sind es 47 bytes Daten und die Disk-Routinen melden 51 bytes)
//        dies macht a) beim Lesen ein SkipOpenChunk und b) ein SeekBack noetig
	file.BinStartChunk		(zFCHUNK_POLYLIST);
	{
		file.BinWriteInt	(numPoly);
		for (i=0; i<numPoly; i++) 
		{
			zTMSH_PolyChunk	chunk;
			zCPolygon *poly		= polyList[i];
			chunk.polyPlane		= poly->polyPlane;
			chunk.flags			= poly->flags;
			chunk.polyNumVert	= poly->polyNumVert;
			chunk.matIndex		= matList.Search	(poly->GetMaterial());		// -1 = nix
			chunk.lightmapIndex	= lmList.Search		(poly->GetLightmap());
			file.BinWrite		(&chunk, sizeof(chunk));
			for (int j=0; j<poly->polyNumVert; j++) 
			{
				zTVertIndex vi = zTVertIndex(poly->vertex [j]->hackData);
				zTFeatIndex fi = zTFeatIndex(poly->feature[j]->lightDyn.GetPackedDWord());
				file.BinWrite (&vi, sizeof(vi));
				file.BinWrite (&fi, sizeof(fi));
			};
		};
	}

	file.BinStartChunk		(zFCHUNK_MESH_END);
//	file.BinWriteByte		(zBYTE(66));	

	// cleanup
	file.BinEndChunk	();			// kein BinClose() !
//	file.file = 0;					// wg Destruktor noetig !

    for (i=0; i<vertList.GetNumInList(); i++) {
	    zCVertex *vert		= vertList[i];
		vert->hackData		= 0;  // [Moos] Lösche unsere Daten wieder.
	};

    if (mesh){
        mesh->UnshareFeatures();
        mesh->ClearLists();
    }
};


/* ----------------------------------------------------------------------
	
    zCMesh::LoadMSH()	

	29.11.2000	[Moos]	
                Neuer Lightmap-Lader

   ---------------------------------------------------------------------- */


zBOOL zCMesh::LoadMSH (zCFileBIN& file, zBOOL tryToLoadShared) 
{
	int i=0;

//#ifndef DEBUG_MOOS_X
//    tryToLoadShared = FALSE;
//#endif

#ifdef COMPILING_SPACER
    tryToLoadShared = FALSE;
#endif

    if (tryToLoadShared && zoptions->Parm("ZNOSHAREDFEATURES"))
        tryToLoadShared = FALSE;

//	zCMaterial *defMat = zNEW(zCMaterial ("MSH_DEF_MAT"));
//	defMat->SetColor (200,100,80);

//	zCFileBIN file;
//	file.file = &inFile;
	int num;

    DeleteAll();

	zCVertFeature   *featArray		= 0;
	zCMaterial		**matList		= 0;
	int				numFeatList		= 0;
	zCLightMap		**lightmapList	= 0;  // [Moos]
	int				numlightMap		= 0;
	int				numMaterials	= 0;
	zBOOL			bboxChunkRead	= FALSE;
    int             maxNumFeat      = 0;

	zWORD id;
	zLONG len;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
	
		case zFCHUNK_MESH:
			{
				zWORD		vers;
				zSTRING		s;
				zDATE		date;
				file.BinReadWord	(vers);
				file.BinRead		(&(date), sizeof(date));
				file.BinReadString	(s); 
				SetMeshName			(s);

				// alte Version, oder neueres ASC-File ?
				if (vers!=zCMesh::GetFileVersion()) {
					zERR_WARNING("D: z3d(zCMesh::LoadMSH): wrong mesh-file version, engine: "
						+zSTRING(zCMesh::GetFileVersion())+", file: "+zSTRING(vers));
					return FALSE;
				};
				
				if (s.Length()>0) 
				if (zCMesh::GetAutoConvertMeshes()) {
					// Source-Mesh aufspueren 
					zPATH meshPath;
					zoptions->ChangeDir (DIR_MESHES);
					if (meshPath.SearchFile(meshName, zSTRING(zFILE::GetCurrentDir()))!=zERR_NONE) {
						zERR_WARNING("D: MSH: z3d(zCMesh::LoadMSH): ASC not found: "+s);
					} else {
						// ASC gefunden
						zFILE_STATS meshStats;
						zFILE* meshFile	= zfactory->CreateZFile(meshPath.GetPath());
						meshFile->GetStats		(meshStats);
						delete meshFile;

		//				zerr.Message ("D: MDL: .. out of date, MAN: "+date.ToString(zDATE_ALL)+", ASC: "+ascStats.modifyDate.ToString(zDATE_ALL));
						// yep, ASC muss neu konvertiert werden !
						if (meshStats.modifyDate>date) return FALSE;
					};
				};
			};
			break;
		case zFCHUNK_BBOX3D:
			bbox3D .LoadBIN	(file);
			obbox3D.LoadBIN	(file);
			bboxChunkRead = TRUE;
			break;
		case zFCHUNK_MATLIST:
			{
				{
					zCArchiver			*arc = zarcFactory.CreateArchiverRead (file.file);
					zERR_ASSERT_STRICT	(arc);
					numMaterials		= arc->ReadInt	("");
					matList				= zNEW(zCMaterial*) [numMaterials];
					zSTRING				matName;
					zCMaterial*			mat=0;
					// Die MatList haelt offizielle Referenzen auf die enthaltenen Materialien
					for (int i=0; i<numMaterials; i++) 
					{
						matName		= arc->ReadString				("");
						mat			= zCMaterial::SearchName		(matName);
						if (mat) {
							mat->AddRef			();		// damit sich das Release() am Ende zu "0" aufloest..
							zWORD vers;
							arc->ReadChunkStart	(matName, vers);
							arc->SkipOpenChunk	();
						} else {
							mat		= (zCMaterial*)arc->ReadObject	();	// erzeugte Objekte ("new") kommen hier mit ref=1 heraus
						};
						matList[i]	= mat;
						// Fehler ? (z.B. Objekt im alten Format im File)
						// =>	Abbruch / Neu-Konvertierung
						if (mat==0) return FALSE;
					};
					SetAlphaTestingEnabled(arc->ReadBool(""));
					arc->Close();
					zRELEASE (arc);
				};
			};
			break;

		case zFCHUNK_LIGHTMAPLIST: // [Moos] alter ladecode; zwecks Kompatibilität noch drin. Angepasst an Mapping/Textur-Trennung
			{
//file.BinSkipChunk();
//break;
				file.BinReadInt (numlightMap);
				lightmapList	= zNEW(zCLightMap*) [numlightMap];
				zVEC3 lmVectors[3];
				for (int i=0; i<numlightMap; i++) {
                    zCLightMap *lm                  = zNEW(zCLightMap);                         // [Moos]
					zCTexture *lmTex				= zrenderer->CreateTexture();
//					lm->SetName		        		(zSTRING("lm")+zSTRING(i));
					file.BinRead					(&lmVectors, sizeof(lmVectors));
					lm->SetLightmapOriginUpRight	(lmVectors[0], lmVectors[1], lmVectors[2]); 
					lmTex->LoadAndConvertInternal	(*file.file);
                    lm->SetTexture                  (lmTex);                                    // [Moos]
					lightmapList[i]					= lm;

                    lmTex->SetCacheOutLock(TRUE); // Lightmaps sollen im Speicher bleiben

                    zRELEASE(lmTex);
				};
				SetHasLightmaps (TRUE);
			};

    	break;

		case zFCHUNK_LIGHTMAPLIST_SHARED: // [Moos] Neuer Ladecode
            {
                // Lege die Pointer für die Texturen an
                int numTextures = 0, i;    
                file.BinReadInt(numTextures);
                zCTexture **lmTexList = zNEW_ARRAY(zCTexture *, numTextures);
                
                // und lade sie
                for (i = 0; i < numTextures; i++)
                {
                    zCTexture *tex = zrenderer->CreateTexture();
                    tex->LoadAndConvertInternal(*file.file);
                    tex->SetCacheOutLock(TRUE); // Lightmaps sollen im Speicher bleiben
                    lmTexList[i] = tex;
                }
    
                // Jetzt die Mappings. Speicher anlegen
                file.BinReadInt (numlightMap);
                lightmapList  = zNEW_ARRAY(zCLightMap*, numlightMap);

                // und laden.
                struct zTMSH_LightmapChunk chunk;
                for (i = 0; i < numlightMap; i++)
                {
                    file.BinRead(&chunk, sizeof(chunk));
                    zCLightMap *lm = zNEW(zCLightMap);

                    lm->SetTexture                  (lmTexList[chunk.texIndex]);
					lm->SetLightmapOriginUpRight	(chunk.lmVectors[0], chunk.lmVectors[1], chunk.lmVectors[2]); 
                    lightmapList[i] = lm;
                }

                // Texturen releasen. Die Lightmaps kümmern sich nun darum
                for (i = 0; i < numTextures; i++)
                    zRELEASE(lmTexList[i]);

                delete[] lmTexList;

				//
				SetHasLightmaps (TRUE);
            }
            break;

		case zFCHUNK_VERTLIST: 
			{
				file.BinReadInt (num);
				// Verts im Mesh komplett allokieren
				// FIXME: hier alle Verts in EINEM Block allokieren !! -> gefixed !

               if (tryToLoadShared)
               {
                    vertArray   = zNEW(zCVertex  )[num];      // enfach ein Vertex-Array
                    vertList    = zNEW(zCVertex *)[num];      // diese Pointer können nachher wieder gelöscht werden
				    for (int i=0; i<num; i++)
                        vertList[i] = vertArray + i;
                    numVert = num;
                }
                else
                {
				    AllocVerts		(num);                    // doch lieber jeden Vertex einzeln allocieren; die Pointer werden dann immer Gebraucht.
				    for (int i=0; i<num; i++) {
					    zCVertex	*vert = zNEW(zCVertex);
					    AddVertex	(vert);
    				};
                }

				// Verts vom File einlesen & eintragen
				zPOINT3 *block = zNEW(zPOINT3) [num];
				file.BinRead	(block, num*sizeof(zPOINT3));
				for (i=0; i<num; i++) {
					vertList[i]->SetPosition (block[i]);
				};
				delete[] block; block=0;
			};
			break;
		case zFCHUNK_FEATLIST: 
			{
#ifdef MEMPOOL_HOELLER
				if(GetMeshesPool().IsPoolActive()==TRUE)
				{
					file.BinReadInt (num);
					numFeatList	= num;
					// Feats vom File einlesen
					featArray					= zNEW(zCVertFeature)		[num];
					//	featArray					= (zCVertFeature*)zAlignPtr(malloc(sizeof(zCVertFeature)*num+32), 32);
				
					zTMSH_FeatureChunk *block	= zNEW(zTMSH_FeatureChunk)	[num];
					file.BinRead				(block, num*sizeof(zTMSH_FeatureChunk));
		
					GetMeshesPool().GetMesh(poolIndex)->AllocateVertexFeatures(num);

					for (i=0; i<num; i++) 
					{
						featArray[i].texu		= block[i].texu;
						featArray[i].texv		= block[i].texv;
						featArray[i].vertNormal	= block[i].vertNormal;
						featArray[i].lightStat	= block[i].lightStat;
					};
 					delete[] block; block=0;
				}
				else
#endif
				{
					file.BinReadInt (num);
					numFeatList	= num;
					// Feats vom File einlesen
					featArray					= zNEW(zCVertFeature)		[num];
                    numFeat                     = num;
					// featArray					= (zCVertFeature*)zAlignPtr(malloc(sizeof(zCVertFeature)*num+32), 32);
				
					zTMSH_FeatureChunk *block	= zNEW(zTMSH_FeatureChunk)	[num];
					file.BinRead				(block, num*sizeof(zTMSH_FeatureChunk));
					for (i=0; i<num; i++) 
					{
						featArray[i].texu		= block[i].texu;
						featArray[i].texv		= block[i].texv;
						featArray[i].vertNormal	= block[i].vertNormal;
						featArray[i].lightStat	= block[i].lightStat;
					};
 					delete[] block; block=0;
				}
			};
			break;
		case zFCHUNK_POLYLIST: 
			{
				file.BinReadInt (num);

                if (tryToLoadShared)
                {
                    polyArray       = zNEW(zCPolygon)[num];
                    zERR_ASSERT     (polyArray);
                }
                else
    				AllocPolys		(num);

				zBYTE *block	= zNEW(zBYTE) [len];
				file.BinRead	(block, len);

				zBYTE *blockPtr = block;
				for (int i=0; i<num; i++) {

                    zCPolygon *poly = NULL;
                    if (tryToLoadShared)
					    poly				        = polyArray + i;
                    else
					    poly				        = zNEW(zCPolygon());

					zTMSH_PolyReadChunk *chunk	= (zTMSH_PolyReadChunk*)blockPtr;
					poly->flags					= chunk->flags;
					// safety: all polys must be lit at first apperance
					poly->flags.mustRelight		= TRUE;
					poly->polyPlane				= chunk->polyPlane;
					
//					poly->CalcNormalMainAxis();

                    if (tryToLoadShared)					
                    {
                        poly->vertex      = (zCVertex **)     zCPolygon::S_AllocPointers       (chunk->polyNumVert);
    		            poly->feature     = (zCVertFeature **)zCPolygon::S_AllocPointers       (chunk->polyNumVert);
                        poly->polyNumVert =                                                     chunk->polyNumVert;
                    }
                    else
					    poly->AllocVerts			(chunk->polyNumVert);

                    maxNumFeat                 +=chunk->polyNumVert;

					for (int j=0; j<chunk->polyNumVert; j++) 
					{
						int featIndex = chunk->indexList[j].featIndex;
						// FIXME: dies ist temporaerer Code zum korrekten Einladen von 'defekten' Files...
						//        (kann spaeter wieder entfernt werden..)
						if (featIndex>=numFeatList) featIndex = featIndex >> 16;
						poly->SetVertex		(j,  vertList[chunk->indexList[j].vertIndex]);

                        if (tryToLoadShared)
                            poly->feature[j] = featArray + featIndex;
                        else
						    poly->SetFeature	(j, &featArray[featIndex]);

//						poly->SetFeature	(j, &featArray[chunk->indexList[j].featIndex]);

//						poly->AddVertexAndFeature (	vertList[chunk->indexList[j].vertIndex], 
//												   &featArray[chunk->indexList[j].featIndex]);
					};

 					poly->SetMaterial	(matList[chunk->matIndex]);
					
					if (chunk->lightmapIndex>=0) 
					if (lightmapList)
					{
						poly->SetLightmap (lightmapList[chunk->lightmapIndex]);
					};

                    if(tryToLoadShared)
                        numPoly++;
                    else
					    AddPoly				(poly);

//poly->TexCorrectUV();
					blockPtr += sizeof(zTMSH_PolyChunk) + sizeof(zTMSH_PolyReadChunk::zTIndex)*chunk->polyNumVert;
				};
				delete[] block; block=0;
			};
			file.BinSkipChunk();		// FIXME: Warum ist das noetig ???? ist len falsch ????
			break;
		case zFCHUNK_MESH_END: 
//			file.BinSkipChunk();
			goto fileEnd;
			break;
		default:
			file.BinSkipChunk();
		};
	}
fileEnd:;

	// Lightmaps releasen 
	for (i=0; i<numlightMap; i++)	lightmapList[i]->Release();

	// Materials releasen 
	for (i=0; i<numMaterials; i++)	matList[i]->Release();

	//
	if (!bboxChunkRead) CalcBBox3D	();

	// FIXME: temp ?
	ResetLightDynToLightStat();

	// cleanup

    if (tryToLoadShared)
    {
        delete[] this->featArray;  this->featArray = featArray;
        delete[] this->featList;   this->featList  = NULL;


        ClearLists();               // [Moos] die werden nicht mehr gebraucht.


        if (numFeat == maxNumFeat)  // wenn die Features noch nicht geshared werden, tue es jetzt
           ShareFeatures();

    }
    else
    {
        delete[] featArray;
        featArray = NULL;
        numFeat   = 0;
    }

	delete[] matList;
	delete[] lightmapList;
//	file.file = 0;


    
#ifdef DEBUG_MOOS_X
    CombineLightmaps();
#endif

	return TRUE;
};

zBOOL zCMesh::LoadMSH (const zSTRING& fileName, zBOOL tryToLoadShared) {
	zERR_MESSAGE		(3, zERR_BEGIN, "D: MSH: Loading Mesh: "+fileName);

	// [BENDLIN] Addon Patch - Meshes im Soundverzeichnis
//	zoptions->ChangeDir		(DIR_COMPILED_MESHES);
	zCFileBIN file;
	file.BinOpen		(zoptions->GetDirString(DIR_COMPILED_MESHES) + fileName);  
	zBOOL res = LoadMSH	(file, tryToLoadShared);
	file.BinClose		();
	zERR_MESSAGE		(3, zERR_END, "");
	return res;
};

// =========================================================================================================


// initializes the pointer lists from the arrays
void zCMesh::CreateListsFromArrays() const{ 
#ifdef MEMPOOL_HOELLER
    if (GetMeshesPool().IsPoolActive())
    	return;
#endif

    int i;

    if (!vertList && vertArray){
    	(zCVertex **&)vertList = zNEW(zCVertex *)[numVert];
    	for (i=numVert-1; i>=0; i--) vertList[i] = vertArray + i;
    }

    if (!polyList && polyArray){
    	(zCPolygon **&)polyList = zNEW(zCPolygon *)[numPoly];
    	for (i=numPoly-1; i>=0; i--) polyList[i] = polyArray + i;
    }

    if (!featList && featArray){
    	(zCVertFeature **&)featList = zNEW(zCVertFeature *)[numFeat];
    	for (i=numFeat-1; i>=0; i--) featList[i] = featArray + i;
    }
}; 

// clears the lists if there are arrays, too
void zCMesh::ClearLists() const{
#ifdef MEMPOOL_HOELLER
    if (GetMeshesPool().IsPoolActive())
    	return;
#endif

    if (vertList && vertArray){
    	delete[] vertList; (zCVertex **&)vertList = NULL;
    }

    if (polyList && polyArray){
    	delete[] polyList; (zCPolygon **&)polyList = NULL;
    }

    if (featList && featArray){
    	delete[] featList; (zCVertFeature **&)featList = NULL; 
    }
};
    

// converts the arrays back to lists and deletes the arrays

void zCMesh :: ArraysToLists() const{
#ifdef MEMPOOL_HOELLER
    if (GetMeshesPool().IsPoolActive())
    	return;
#endif

    CreateListsFromArrays();

    if (vertArray){
    	zCVertex::PoolAdd(vertArray, numVert); (zCVertex *&)vertArray = NULL;
    }

    if (polyArray){
    	zCPolygon::PoolAdd(polyArray, numPoly); (zCPolygon *&)polyArray = NULL;
    }

    if (featArray){
    	zCVertFeature::PoolAdd(featArray, numFeat); (zCVertFeature *&)featArray = NULL;
    }
};            


/* ----------------------------------------------------------------------
	
    zCMesh::ShareFeatures()

	 27.1.2001	[Moos]	
                Testimplementierung; mal sehen, wieviel es bringen könnte.
	 2.2.2001	[HILDEBRANDT]	
                in S_FeaturesAreEqual() ist 0.1 als Unterscheidungsgrenze bei
				UVs zu gering. Habs in der World getestet: gab unschoene Verzerrungen.
				Habe nun 0.03 eingesetzt, in der Hoffnung, dass dieser Werte besser
				passt. Habe es allerdings nicht nochmal in der World getestet.
				Wert so ok?
   ---------------------------------------------------------------------- */

zBOOL S_FeaturesAreEqual(const zCVertFeature &a, const zCVertFeature &b)
{
	// FIXME: das ist leider noch nicht ausreichend. Es gibt Fälle wo Features nicht
	// geshared werden dürfen, auch wenn die Werte gleich sind: Sectorpoly Features
	// dürfen nicht mit Outdoorpoly Features verschmolzen werden, sonst gibt es beleuchtungprobs
  if (a.vertNormal * b.vertNormal < .7)
    return FALSE;
  //  if (a.lightStat != b.lightStat)
  //    return FALSE;
  if (fabs(a.texu - b.texu) > .03)	return FALSE;
  if (fabs(a.texv - b.texv) > .03)	return FALSE;

#ifdef COMPILING_SPACER
  if (a.hintSectorFeature != b.hintSectorFeature) return FALSE;
#endif

  return TRUE;
}

void zCMesh::ShareFeatures(){
    //    if (numVert < 1000)
    //        return;

    zBOOL wasSharedBefore = featArray || featList;

#ifdef MEMPOOL_HOELLER
    if (GetMeshesPool().IsPoolActive())
        return;
#endif

    CreateListsFromArrays();

    zCVertFeature *oldFeatures = featArray;

    delete[] featList; featList = NULL; // wir brauchen sie nicht; wir bauen sie sowieso neu auf.

    int i, j, k;

    int shared=0;
    int total =0;
    
    //	  if (featList)
    //  Un	shareFeatures();
    
    zERR_MESSAGE(4, zERR_BEGIN, "M: Beginning to share vertex features...        ");
    
    zCVertex::ResetVertexTransforms();
    
    zERR_MESSAGE(5, 0,          "M: Enumerating Vertices...                      ");
    
    for (i = numVert-1; i>=0; i--)
    {
	    zERR_ASSERT(vertList[i]->transformedIndex == 0);
	    vertList[i]->hackData = i;
    }
    
    zERR_MESSAGE(5, 0,          "M: Counting Features...                         ");
    
    numFeat = 0;
    for (i = numPoly-1; i>=0; i--)
	numFeat += polyList[i]->polyNumVert;
    
    featArray = zNEW(zCVertFeature)[numFeat]; // Dimensionierte das Array grosszügig. Wir räumen es später auf.
    
//    int numFeat_before = numFeat;
    numFeat = 0;
    
    zERR_MESSAGE(5, 0,          "M: Building Mapping from Vertices to Features...");
    
    //	 für jeden Vertex: die liste seiner bisher neu angelegten Features.
    zCArray<zCVertFeature *> *vertex_To_VertFeature = zNEW(zCArray<zCVertFeature *>)[numVert];
    
    for (i = numPoly-1; i>=0; i--)
    {
	    zCPolygon               *p  = polyList[i];
	    zCVertFeature **newFeatures = (zCVertFeature**)zCPolygon::S_AllocPointers(p->polyNumVert);  // So ists besser.
	    
	    for (j = p->polyNumVert-1; j>=0; j--)
        {
	        zCVertex      *v  = p->vertex[j];
	        zCVertFeature *f  = p->feature[j];

#ifdef COMPILING_SPACER
			if (p->GetSectorFlag()) f->hintSectorFeature = TRUE;
			else					f->hintSectorFeature = FALSE;
#endif
	        
	        total ++;
	        
	        zCArray<zCVertFeature*> &features = vertex_To_VertFeature[v->hackData];
	        
	        //	 SO. <v> ist ein Vertex, <f> eines seiner Features und <features> eine Liste seiner bisher geshareten features.
	        // suc	he diese Liste nach features ab, die mit <f> geshared werden koennen.
	        zCVertFeature *newFeature = NULL;
	        for (k = features.GetNumInList()-1; !newFeature && k>=0; k--)
			{
                zCVertFeature *oldFeature = features[k];
		        if (S_FeaturesAreEqual(*oldFeature, *f))
				{ // sharebar!
    		        shared ++;
		            newFeature = oldFeature;
		        }
            }

	        if (!newFeature)
            { // nichts gefunden. Lege ein neues Feature an.
		        newFeature  = &featArray[numFeat++];
		        *newFeature = *f;
#ifdef COMPILING_SPACER
				if (p->GetSectorFlag()) newFeature ->hintSectorFeature = TRUE;
				else					newFeature ->hintSectorFeature = FALSE;
#endif
		        features.Insert(newFeature);
            }

	        newFeatures[j] = newFeature;
	    }	  
	
        if (!wasSharedBefore)	
	        zCPolygon::S_DeleteVertFeatures(p->polyNumVert, *p->feature);

	    zCPolygon::S_DeletePointers    (p->polyNumVert,  p->feature);
	    
	    p->feature = newFeatures;
    }
    
    zERR_MESSAGE(5, 0,          "M: Cleaning up...                                    ");
    
    for (i = numVert-1; i>=0; i--)
    {
	    zERR_ASSERT(vertList[i]->hackData == i);
	    vertList[i]->hackData = 0;
    }


#ifdef PSYCHO
    zCVertFeature *fl = featArray;
    
    featArray = zNEW(zCVertFeature)[numFeat];
    zERR_ASSERT(featArray);

    memcpy(featArray, fl, numFeat * sizeof(zCVertFeature));


    // update alle pointer in den Polygonen auf das neu angelegte Array mit pointer-Magie
    int offset = featArray - fl;

    for (i = numPoly-1; i>=0; i--)
    {
	    zCPolygon               *p  = polyList[i];
	    
	    for (j = p->polyNumVert-1; j>=0; j--)
            p->feature[j] += offset;
    }

    delete[] fl;
#else

    zCVertFeature *fl = featArray;

    featArray = zNEW(zCVertFeature)[numFeat];
    zERR_ASSERT(featArray);

    memcpy(featArray, fl, numFeat * sizeof(zCVertFeature));

    // update alle pointer in den Polygonen auf das neu angelegte Array mit pointer-Magie
   for (i = numPoly-1; i>=0; i--)
    {
	    zCPolygon               *p  = polyList[i];
	    
	    for (j = p->polyNumVert-1; j>=0; j--)
            p->feature[j] = featArray + (p->feature[j] - fl);
    }

    delete[] fl;
#endif


    delete[] oldFeatures;

    delete[] vertex_To_VertFeature;
    
    

    zERR_MESSAGE(4, zERR_END,    "M: Shared " + zSTRING(shared) + " of a total of " + zSTRING(total) + " vertex features. Memory conservation: " + zSTRING((int )((shared) * (sizeof(zCVertFeature) + sizeof (void *))) )+ " bytes.");
    
    zERR_MESSAGE(4, 0,    "M: Conservation from avoiding pointer boards: " + zSTRING(int((numVert + numPoly + numFeat) * sizeof(void *)))+ " bytes.");

    ClearLists();

}


void zCMesh::UnshareFeatures()
{
//    return;

    ArraysToLists();

    if (!featList)
        return;

  // gehe einfach alle Polygone durch, lege ihre VertexFeature-Listen neu an und lösche später die geshareten.

    for (int i = numPoly-1; i>=0; i--){
    	zCPolygon     *p       = polyList[i];

    	zCVertFeature *newFeat =                   zCPolygon::S_AllocVertFeatures(p->polyNumVert);
    	zCVertFeature **newFP  = (zCVertFeature **)zCPolygon::S_AllocPointers    (p->polyNumVert);
	
    	for (int j = p->polyNumVert-1; j>=0; j--){
	        newFeat[j] = *p->feature[j];
	        newFP[j]   = &newFeat[j];
	    }
	
        zCPolygon::S_DeletePointers(p->polyNumVert, p->feature);
    	p->feature = newFP;
    }

    delete[] featList;  featList  = NULL;
    delete[] featArray; featArray = NULL;
}



/*

// alter dummy-code
void zCMesh::ShareFeatures () {
};

void zCMesh::UnshareFeatures () {
};

// initializes the pointer lists from the arrays
void zCMesh::CreateListsFromArrays() const{}; 

// clears the lists if there are arrays, too
void zCMesh::ClearLists() const{};
    

// converts the arrays back to lists and deletes the arrays

void zCMesh::ArraysToLists() const{};            

*/



// =========================================================================================================

void zCMesh::FlipPolys () { 
	for (int i=0; i<numPoly; i++) Poly(i)->Flip(); 
};

// =========================================================================================================


static int Compare_Verts_Merge(const void *arg1, const void *arg2) 
{
	const zVALUE	ALMOST_ZERO				= 0.01F;		// = cm
	const zVEC3		p1						= (*((zCVertex**)arg1))->position;
	const zVEC3		p2						= (*((zCVertex**)arg2))->position;	
	const zREAL		p1x						= p1.n[VX];
	const zREAL		p1y						= p1.n[VY];
	const zREAL		p1z						= p1.n[VZ];
	const zREAL		p2x						= p2.n[VX];
	const zREAL		p2y						= p2.n[VY];
	const zREAL		p2z						= p2.n[VZ];

	// erster test auf gleichheit
	if ((zAbs(p1x - p2x) < ALMOST_ZERO) &&
		(zAbs(p1y - p2y) < ALMOST_ZERO) &&
		(zAbs(p1z - p2z) < ALMOST_ZERO)) return 0;			// equal	

	if		( (p1x-p2x) < 0 ) return -1;
	else if ( (p1x-p2x) > 0 ) return +1;
	else 
	{
		// die x koords sind gleich, dann die y coords vergleichen
		if		( (p1y-p2y) < 0 ) return -1;
		else if ( (p1y-p2y) > 0 ) return +1;
		else
		{
			// die x und die y coords sind gleich, kann dann nur noch z unterschiedlich sein
			if		( (p1z-p2z) < 0 ) return -1;
			else if ( (p1z-p2z) > 0 ) return +1;
		}
	}

	zERR_FAULT("C: Compare_Verts_Merge: Bug!!! should be never here!");
	// hier darf man niemals hinkommen
	return 0;

}

static int Compare_Features(const void *arg1, const void *arg2) 
{
	const zCVertFeature *f1						= (*((zCVertFeature**)arg1));
	const zCVertFeature *f2						= (*((zCVertFeature**)arg2));
	if (f1<f2) return -1; else
	if (f1>f2) return +1; else
	return 0;
}


static int ComparePolysByMaterial (const void *arg1, const void *arg2) {
	zCMaterial* m1 = (*((zCPolygon**)arg1))->GetMaterial();
	zCMaterial* m2 = (*((zCPolygon**)arg2))->GetMaterial();
	if (m1<m2)	return -1; else
	if (m1>m2)	return +1; else
				return  0;
};

void zCMesh::SortPolysByMaterial() { 
    ArraysToLists();
	qsort ((polyList), this->numPoly, sizeof(polyList[0]), ComparePolysByMaterial);
};


// =========================================================================================================

// =========================================================================================================

/* ----------------------------------------------------------------------
	
    zCMesh::SortPolysByList()

    Sortiert die Polygone nach ihrem Auftauchen in der übergebenen Liste, ebenso
    die Vertices dieser Polygone

	 24.1.2001	[Moos]	
                Erzeugt

   ---------------------------------------------------------------------- */

static zCSparseArray<const void *, int> s_polyVertIndex;

static int S_ComparePolyVerts(const void *A, const void *B){
  void *a = *((void **)A);
  void *b = *((void **)B);

  int *AI = s_polyVertIndex[a];
  int *BI = s_polyVertIndex[b];

  if (!AI || !BI)
    return 0;

  int ai = *AI;
  int bi = *BI;

  if (ai < bi)
    return -1;
  if (ai > bi)
    return 1;

  return 0;
}


void zCMesh::SortPolysByList(zCPolygon **list, int listLength){
#ifdef DEBUG_MOOS_X
    return;
#endif

    int i;

    ArraysToLists();

    zERR_MESSAGE (3,zERR_BEGIN, "M: Sorting " + zSTRING(numPoly) + " polygons by their appearence in a list of length " + zSTRING(listLength) + " for better spacial mesh coherence.");



#ifdef DEBUG_MOOS_X
    zCSparseArray<const void *, int> s_polyIndex;
 
    // weise jedem Polygon seine Nummer zu
    for (i = numPoly-1; i>=0; i--)
        *(s_polyIndex.Insert(polyList[i])) = i;

    for (i = numPoly-1; i>=0; i--)
        zERR_ASSERT_STRICT (*(s_polyIndex[polyList[i]]) == i);
#endif



    zERR_MESSAGE (5,0,          "M: Assigning indices to polygons...    ");

    // losche die Arrays
    s_polyVertIndex.Clear();

    // zuerst Ordnen wir jedem Polygon sein erstes Vorkommen in der Liste zu
    for (i = listLength-1; i>=0; i--)
        *(s_polyVertIndex.Insert(list[i])) = i;


#ifdef DEBUG_MOOS_X
    // prüfe sie
    for (i = listLength-1; i>=0; i--)
        zERR_ASSERT_STRICT ( s_polyVertIndex[list[i]] &&  *(s_polyVertIndex[list[i]]) <= i );
#endif



    zERR_MESSAGE (5,0,          "M: Sorting polygons...                 ");

    // sortiere sie nach diesem Kriterium
    insertionsort(polyList, numPoly, sizeof(void *), &S_ComparePolyVerts, TRUE);

    zERR_MESSAGE (5,0,          "M: Assigning indices to vertices...    ");

    // gib den Vertices dann die Nummer des Polygons, in dem sie zuerst auftauchen
    for (i= numPoly-1; i>=0; i--)
    {
        zCPolygon *p = polyList[i];
        for (int j = p->polyNumVert-1; j>=0; j--)
            *(s_polyVertIndex.Insert(p->vertex[j])) = i;
    }



#ifdef DEBUG_MOOS_X
    // prüfe sie
    for (i= numPoly-1; i>=0; i--)
    {
        zCPolygon *p = polyList[i];
        for (int j = p->polyNumVert-1; j>=0; j--)
            zERR_ASSERT_STRICT ( s_polyVertIndex[p->vertex[j]] &&  *(s_polyVertIndex[p->vertex[j]]) <= i );
    }
#endif



    zERR_MESSAGE (5,0,          "M: sorting vertices...                 ");

    // sortiere auch sie nach diesem Kriterium
    insertionsort(vertList, numVert, sizeof(void *), &S_ComparePolyVerts, TRUE);


    if (featList)
      {
	zERR_MESSAGE (5,0,          "M: Assigning indices to features...    ");
	
	//		 gib den Vertices dann die Nummer des Polygons, in dem sie zuerst auftauchen
	for (i= numPoly-1; i>=0; i--)
	  {
	    zCPolygon *p = polyList[i];
	    for (int j = p->polyNumVert-1; j>=0; j--)
	      *(s_polyVertIndex.Insert(p->feature[j])) = i;
	  }
	
	
	
#ifdef DEBUG_MOOS_X
	// prüfe sie	
	for (i= numPoly-1; i>=0; i--)
	  {
	    zCPolygon *p = polyList[i];
	    for (int j = p->polyNumVert-1; j>=0; j--)
	      zERR_ASSERT_STRICT ( s_polyVertIndex[p->feature[j]] &&  *(s_polyVertIndex[p->feature[j]]) <= i );
	  }
#endif	
	
	zERR_MESSAGE (5,0,          "M: sorting features...                 ");

	// sortiere auch sie nach diesem Kriterium
	insertionsort(featList, numFeat, sizeof(void *), &S_ComparePolyVerts, TRUE);
      }
	
    // losche die Arrays wieder
    s_polyVertIndex.Clear();

    zERR_MESSAGE (3,zERR_END,   "M: Done sorting mesh polygons.         ");
}


// =========================================================================================================

// =========================================================================================================

void zCMesh::DeletePolyAndVerts	(zCPolygon* poly) 
{
    ArraysToLists();

	for (int i=0; i<numPoly; i++) 
	{
		if (polyList[i]==poly) 
		{
			DeletePolyAndVerts (i);
			return;
		};
	};
};

void zCMesh::DeletePolyAndVerts	(const zDWORD polyListIndex) 
{
    ArraysToLists();

	zERR_ASSERT (polyListIndex<numPoly);
	if (polyListIndex>=numPoly) return;

	zCPolygon *poly = polyList[polyListIndex];

	// Verts des Polys loeschen, falls sie nicht weiter referenziert werden
	// (langsam bei grossen Meshes...)
	// Verts des Polys durchlaufen
	zBOOL found = FALSE;
	for (int j=0; j<poly->polyNumVert; j++)
	{
		// dieses Vert in einem anderen Poly enthalten?
		zCVertex *vert = poly->vertex[j];
		for (int k=0; k<numPoly; k++)
		{
			if (polyList[k]==poly) continue;
			if (polyList[k]->VertPartOfPoly(vert))
			{
				found = TRUE; 
				break;
			};
		};
		// nicht gefunden => entfernen
		if (!found)
		{
			// Ort in der VertexList suchen
			for (int l=0; l<numVert; l++)
			{
				if (vert==vertList[l])
				{
					// Ort in VertexListe gefunden, aus der Liste austragen
					if (l!=numVert-1) 
						vertList[l]	= vertList[numVert-1];
//								for (int k=l; k<numVert-1; k++) vertList[k] = vertList[k+1];
					numVert--;
					break;
				};
			};
			// Vert wird nun nicht mehr referenziert und kann geloescht werden
			delete vert;
		};
	};

	// Poly loeschen
	delete polyList[polyListIndex];
	for (j=polyListIndex; j<numPoly-1; j++)
		polyList[j]= polyList[j+1];
	numPoly--;

	// numVertAlloc bleibt wie es ist!
};

void zCMesh::RemoveDegeneratePolys ()
{
    ArraysToLists();

	int removedCtr=0;
	for (int i=0; i<numPoly; i++)
	{
		zCPolygon *poly = polyList[i];
		if (!poly->CalcNormal())
		{
			// degeneriert => loeschen!
			DeletePolyAndVerts (i);
			i--;
			removedCtr++;
		};
	};
	if (removedCtr>0)
		zERR_MESSAGE (5,0, "D: MSH: removed degenerated polys: "+zSTRING(removedCtr));
};





/* ----------------------------------------------------------------------
    	
    zCCombine

    Hilfsklasse für CombineLightMaps

	29.11.2000	[Moos]	
                Implementiert

   ---------------------------------------------------------------------- */

#define RAND 1

#define ADDX_BEFORE RAND
#define ADDX_AFTER  RAND
#define ADDY_BEFORE RAND
#define ADDY_AFTER  RAND

#ifdef DEBUG_MOOS_X
// zeige den Zusammenhang der Lightmaps an
// #define SHOW_LIGHTMAP_COHERENCE
#endif

#define COMBX_SIZE_RAW 256
#define COMBY_SIZE_RAW 256
#define COMBX_SIZE (COMBX_SIZE_RAW + ADDX_BEFORE + ADDX_AFTER)
#define COMBY_SIZE (COMBY_SIZE_RAW + ADDY_BEFORE + ADDY_AFTER)

class zCCombine{
    char occupied[COMBX_SIZE][COMBY_SIZE];

    class zCCItem{
        zCLightMap *map;

    public:
        int        x,y;

        zCCItem():map(0), x(-1), y(-1){}
        zCCItem(const zCCItem &i):map(0),x(i.x),y(i.y){SetMap(i.map);}
        ~zCCItem(){ map = 0; } //zRELEASE(map);}
        zCCItem &operator=(const zCCItem &i){
            SetMap(i.map);
            x = i.x;
            y = i.y;

            return *this;
        }

        zCLightMap *Map(){return map;}

        void        SetMap(zCLightMap *m){
            map = m;
            return;

/*            if (map == m)
                return;

            zRELEASE(map);
            map = m;
            if (map)
                map->AddRef(); */
        } 
    };

    zCArray<zCCItem*> items;

    zBOOL      CombineWith(zCLightMap *m, int x, int y);  // wie CombineWith() ohne x und y; versucht, die Lightmap m an der Position x,y einzufygen.
public:
    zCCombine();

    // Versucht, die Lightmap m noch hinzuzufügen. Rückgabewert: ist es gelungen?
    zBOOL      CombineWith(zCLightMap *m);

    // hier wird die Kombination wirklich ausgeführt
    ~zCCombine();  
};



/* ----------------------------------------------------------------------
    	
	zCMesh::CombineLightmaps()

    Fasst Lightmap-Texturen zusammen

	29.11.2000	[Moos]	
                Implementiert

   ---------------------------------------------------------------------- */


void zCMesh::CombineLightmaps()
{
    this->CreateListsFromArrays();

    int i,j;
    zREAL distance=0, avgDistance=0, nearDistance = -1;

    
    // Sammle erst einmal alle verwendenten Lightmaps und Texturen in diesen Arrays
    zCArraySort<zCLightMap*> maps;

    {
        zCArraySort<zCTexture*>  textures;
    
        for (i=numPoly-1; i>=0; i--)
        {
            zCLightMap *map = polyList[i]->GetLightmap();
            if (map)
            {
                if (!maps.IsInList(map))
                    maps.InsertSort(map);

                zCTexture *tex  = map->Texture();

                if (!textures.IsInList(tex))
                    textures.InsertSort(tex);
            }
        }

        if (maps.GetNumInList() > textures.GetNumInList() || maps.GetNumInList() == 0){
            ClearLists();
            return;  // in diesem Fall war jemand schon fleissig und hat die Lightmaps zusammengefasst.
        }
    }

    int numLightmaps = maps.GetNumInList();

    /*
    // referenziere die gesammelten Maps, keine ungültigen Pointer runhängen (wir geben die dinger im Mesh frei)
    for (i = numLightmaps-1; i>=0; i--)
        maps[i]->AddRef();
    */
 


    zCArray<zCCombine*> collected;   // zusammengefügte Lightmap-Texturen
    zCArray<zVEC3>      position;    // position einer Lightmap in dieser Textur

    // jetzt kommt das eigentliche Zusammenfügen
    zERR_MESSAGE (3,zERR_BEGIN, zSTRING("M: Combining ") + zSTRING(numLightmaps) + zSTRING(" lightmaps."));
    
    for (i = numLightmaps-1; i>=0 ; i--)  // gehe alle alten Lightmaps durch
    {
        zCLightMap *map = maps[i];
        if (!map)
            break;

        zVEC3       map_origin, dummy1, dummy2;

        map->GetLightmapOriginUpRight(map_origin, dummy1, dummy2);

        // suche eine passende, schon zusammengefasste Textur dafür
        zBOOL success = FALSE;

        // Tuning-Konstanten; zREALS sind im Metern.
        static const int   COLLECT_NEAREST=100;
        static const zREAL INNER_RADIUS   =20;
        static const zREAL OUTER_RADIUS   =50;
        static const zBOOL DESPERATE      =FALSE;

        /*

        Strategie: suche zuerst unter den maximal COLLECT_NEAREST der neuen Map am nächsten gelegenen, schon zusammengestelltem maps
                   die nächste, in die die neue Map noch passen würde.
                   Wenn das versagt, probiere alle schon zusammengestellten maps, die näher als OUTER_RADIUS sind.
                   Wenn das versagt und DESPERATE gesetzt ist, nimm irgendeine.
                   Sonst: mache eine neue zusammengestellte map auf.
        */


        // Sammle erstmal die ersten COLLECT_NEAREST nächsten
        int     nearest[COLLECT_NEAREST+1];
        zREAL ndistance[COLLECT_NEAREST+1];

        for (j=COLLECT_NEAREST-1; j>=0; j--)
        {
            nearest  [j] = -1;
            ndistance[j] = -1;
        }

        nearDistance = -1;

        for (j=collected.GetNumInList()-1; j>=0; j--)
        {
            distance = (position[j] - map_origin).Length2();
            
            if(distance < INNER_RADIUS*INNER_RADIUS*10000)
                for(int k=COLLECT_NEAREST-1; k >= 0; k--)
                {
                    nearest  [k+1] = nearest  [k];
                    ndistance[k+1] = ndistance[k];

                    if ( nearest[k] < 0 ||  distance < ndistance[k] )
                    {
                        nearest[k]   = j; // der neue ist besser als der alte
                        ndistance[k] = distance;
                        if (distance > nearDistance)
                            nearDistance = distance;
                    }
                    else
                        k = -1;         // abbrechen
                }                   
        }

        // probiere die nächsten dinger aus
        for (j=0; !success && j<COLLECT_NEAREST && nearest[j] >= 0; j++)
        {
            distance = ndistance[j];
            success = collected[nearest[j]]->CombineWith(map);
        }
        // wenn das nicht geklappt hat, nimm die aus einer festen Umgebung
        // sie sollte näher als 30 m sein

        for (j=collected.GetNumInList()-1; !success && j>=0; j--)
        {
            distance = (position[j] - map_origin).Length2();

            if (distance >= nearDistance && distance < OUTER_RADIUS*OUTER_RADIUS*10000)
                success = collected[j]->CombineWith(map);
        }

        // Na gut, dann nimm alle anderen 
        for (j=collected.GetNumInList()-1;DESPERATE && !success && j>=0; j--)
        {
            distance = (position[j] - map_origin).Length2();
            // sie sollte weiter weg als 30 m sein
            if (distance > OUTER_RADIUS*OUTER_RADIUS*10000)
                success = collected[j]->CombineWith(map);
        }

        if (!success)
        {   // Immer noch kein Erfolg. Mache eine neue Sammlung auf
            collected.InsertEnd(zNEW(zCCombine)());
            position.InsertEnd(zVEC3());

            if (collected.GetNumInList() % 13 == 0)
                zERR_MESSAGE ((collected.GetNumInList() % 3 == 0) ? 5 : 6,0 , zSTRING("M: Adding new lightmap nr. ") + zSTRING(collected.GetNumInList()) + zSTRING("."));

            success = collected[collected.GetNumInList()-1]->CombineWith(map);
            position[position.GetNumInList()-1] = map_origin;

            zERR_ASSERT_STRICT(success);         
        }
        else
            avgDistance += distance;
    }


    // Diverse Releases
    
    for (i = collected.GetNumInList()-1; i>=0; i--)
        delete collected[i];

    zERR_MESSAGE (3,zERR_END, zSTRING("M: Done combining ") + zSTRING(numLightmaps) + zSTRING(" old to ") + zSTRING(collected.GetNumInList()) + zSTRING(" new lightmaps") +
    zSTRING(", Average distance: ") + zSTRING(sqrt(avgDistance/numLightmaps)/100) + zSTRING(" m."));

    ClearLists();
}



zCCombine::zCCombine(){
    for (int i=COMBX_SIZE-1; i>=0; i--)
        for (int j=COMBY_SIZE-1; j>=0; j--)
            occupied[i][j] = 0;
}


#define EXTRASPACE 0

    // Versucht, die Lightmap m noch hinzuzufügen. Rückgabewert: ist es gelungen?
zBOOL zCCombine::CombineWith(zCLightMap *m){
    zERR_ASSERT(m);
    zCTexture *tex = m->Texture();
    zERR_ASSERT(tex);

    // bestimme die groesse der Textur
    int w,h;
    tex->GetPixelSize(w,h);

    w+=ADDX_BEFORE+ADDX_AFTER;
    h+=ADDY_BEFORE+ADDY_AFTER;

    // suche ganz dumm und dystematisch einen freien Platz im occupied-Array.
    // sum soll x+y sein und hat daher die folgenden Grenzen:

    // neu: Quadratsuche
    int minwh = h;
    if (w < minwh) minwh = w;

    int maxsize = ( COMBX_SIZE > COMBY_SIZE ? COMBX_SIZE : COMBY_SIZE);
    
    for (int max = minwh; max <= maxsize; max ++)
    {
        for (int x = 0; x + w <= max ; x++)
            if (CombineWith(m, x, max - h))
                return TRUE;

        for (int y = 0; y + h < max ; y++)
            if (CombineWith(m, max - w, y))
                return TRUE;
    }

#ifdef DEBUG_MOOS_X  // alte Methode: Dreieckssuche
    for (int sum = 0; sum <= COMBX_SIZE + COMBY_SIZE - w - h; sum ++)
    {
        int maxx = COMBX_SIZE - w;
        if (maxx > sum - EXTRASPACE)
            maxx = sum - EXTRASPACE;

        int maxy = COMBY_SIZE - h;
        int minx = sum - maxy;
        if (minx < EXTRASPACE)
            minx = EXTRASPACE;

        for (int x = minx; x <= maxx ; x++)
        {
            int y = sum-x;
    
            zERR_ASSERT_STRICT(!CombineWith(m, x, y));  // darf nichts finden
        }
    }
#endif

    return FALSE;
}


zBOOL zCCombine::CombineWith(zCLightMap *m, int x, int y){
    if (x<0 || y<0)
        return FALSE;

    zERR_ASSERT(m);
    zCTexture *tex = m->Texture();
    zERR_ASSERT(tex);

    // bestimme die groesse der Textur
    int w,h;
    tex->GetPixelSize(w,h);

    w+=ADDX_BEFORE+ADDX_AFTER;
    h+=ADDY_BEFORE+ADDY_AFTER;

    if (x+w > COMBX_SIZE || y+h> COMBY_SIZE)
        return FALSE;

    // so. Jetzt versuchen wir, das Ding an (x,y) einzufügen. Mal sehen, ob Brute Force reicht:
    zBOOL fits = TRUE;

    for (int a = 0; fits && a < w; a++)
        for(int b = 0; fits && b < h; b++)
        {
            zERR_ASSERT(x+a < COMBX_SIZE && y+b < COMBY_SIZE);
            if (occupied[x+a][y+b])
                fits = FALSE;
        }
    if (fits)
    {   // Hurra! wir haben einen Platz. 
        // reserviere ihn
        for (int a = 0; a < w; a++)
            for(int b = 0; b < h; b++)
            {
                zERR_ASSERT(x+a < COMBX_SIZE && y+b < COMBY_SIZE);
                occupied[x+a][y+b] = 1;
            }
        // Trage die Lightmap ein
        items.InsertEnd(zNEW(zCCItem)());
        zCCItem &it = *items[items.GetNumInList()-1];

        it.SetMap(m);
        it.x = x + ADDX_BEFORE;
        it.y = y + ADDX_AFTER;

        return TRUE;
    }

    return FALSE;
}


// hier wird die Kombination wirklich ausgeführt
zCCombine::~zCCombine(){
    if (items.GetNumInList())
    {
        zCTexture *new_tex = zrenderer->CreateTexture();
    
        // finde die minimale grösse der neuen Textur 

        int comb_w=0, comb_h=0, i,j;
        for (i = COMBX_SIZE - 1; i>=0; i--)
            for (j = COMBY_SIZE - 1; j>=0; j--)
                if (occupied[i][j])
                {
                    if (i >= comb_w)
                        comb_w = i;
                    if (j >= comb_h)
                        comb_h = j;
                }

        // den Rand dürfen wir einmal wieder Abziehen
        comb_w -= ADDX_AFTER + ADDX_BEFORE;
        comb_h -= ADDY_AFTER + ADDY_BEFORE;


        // und runde auf die nächste Zweierpotenz
        for (i = 1; i < COMBX_SIZE_RAW; i*=2)
        {
            if (i < comb_w && i*2 >= comb_w)
                comb_w = i*2;
        }

        for (i = 1; i < COMBY_SIZE_RAW; i*=2)
        {
            if (i < comb_h && i*2 >= comb_h)
                comb_h = i*2;
        }


        // lege die neue Textur an und besorge ihre Rohdaten
        zCTextureConvert *texCon= zrenderer->CreateTextureConvert();

		zCTextureInfo texInfo;
    	texInfo.texFormat	= zRND_TEX_FORMAT_RGB_565;
		texInfo.sizeX		= comb_w;
		texInfo.sizeY		= comb_h;
		texInfo.numMipMap	= 1;
		texInfo.refSizeX	= comb_w;
		texInfo.refSizeY	= comb_h;

        texCon->Lock			(zTEX_LOCK_WRITE);
        texCon->SetTextureInfo	(texInfo);

        zWORD *data;
        int    pitch;

        zERR_ASSERT(sizeof(zBYTE) * 2 == sizeof(zWORD));

        zBOOL success = texCon->GetTextureBuffer(0, (void *&)data, pitch);
        pitch >>= 1; // wir arbeiten mit Wörtern, also ist der pitch zu halbieren.
        zERR_ASSERT_STRICT(success && data);


        // lösche die Textur
        int fillValue=0;
#ifdef _DEBUG
        fillValue=0xf0f0;
#endif
#ifdef SHOW_LIGHTMAP_COHERENCE
        fillValue=zRand() && 0xffff;
#endif

        for (i = pitch*comb_h-1; i>=0; i--)
            data[i] = fillValue;
//        memset(data, fillValue, pitch*comb_h*sizeof(zWORD));
        // So. Gehe alle unsere gesammelten Lightmaps durch
        for (i = items.GetNumInList()-1; i>=0; i--)
		{
            zCLightMap *map = items[i]->Map(); 
            zERR_ASSERT(map);

            zCTextureExchange	*tex				= map->Texture();
            zBOOL				deleteTexWhenDone	= FALSE;
            zERR_ASSERT(tex);

            int xoffs = items[i]->x-ADDX_BEFORE;
            int yoffs = items[i]->y-ADDY_BEFORE;

            zERR_ASSERT(xoffs >= 0 && yoffs >= 0);

            if (tex->GetTextureInfo().texFormat != texInfo.texFormat)
            {
				zCTextureConvert *texConv		= zrenderer->CreateTextureConvert();
				zCTextureExchange::CopyContents (tex, texConv);
				texConv->ConvertTextureFormat	(texInfo);
				tex								= texConv;
				deleteTexWhenDone				= TRUE;
            }

            zWORD *src_data;
            int    src_pitch;

			const zCTextureInfo texInfoSource = tex->GetTextureInfo();
            int src_w	= texInfoSource.sizeX;
			int src_h	= texInfoSource.sizeY;


#ifdef _DEBUG
                for (int a = 0; a < src_w; a++)
                    for(int b = 0; b < src_h; b++)
                    {
                        zERR_ASSERT(xoffs + ADDX_BEFORE + a < COMBX_SIZE && yoffs + ADDY_BEFORE + b < COMBY_SIZE);
                        zERR_ASSERT(occupied[xoffs+ ADDX_BEFORE + a][yoffs + ADDX_BEFORE + b]);
                    }
#endif

            zERR_ASSERT(xoffs + src_w <= comb_w && yoffs + src_h <= comb_h);

            tex->Lock(zTEX_LOCK_READ);
            success = tex->GetTextureBuffer(0, (void *&)src_data, src_pitch);
            zERR_ASSERT_STRICT(success && src_data);

            src_pitch >>= 1; // wir arbeiten mit Wörtern, also ist der pitch zu halbieren.

            int x,y;


            // vorbereitungen für den Rand
            int addxbefore = ADDX_BEFORE;
            int addybefore = ADDY_BEFORE;
            int addxafter  = ADDX_AFTER;
            int addyafter  = ADDY_AFTER;

          //  addxbefore = 0;
          //  addybefore = 0;
          //  addxafter  = 0;
          //  addyafter  = 0;

            if (xoffs < addxbefore)
                addxbefore = xoffs;
            if (yoffs < addybefore)
                addybefore = yoffs;
            if (comb_w - xoffs - src_w < addxafter)
                addxafter = comb_w - xoffs - src_w;
            if (comb_h - yoffs - src_h < addyafter)
                addyafter = comb_h - yoffs - src_h;


            zWORD *src_ptr   = src_data;
            zWORD *dest_ptr  = data + (pitch * (yoffs - addybefore) + xoffs);

#ifdef _DEBUG            
            zWORD *max_dest_ptr = data    +      pitch * comb_h;
            zWORD *max_src_ptr  = src_ptr +  src_pitch * src_h;
#endif

#ifndef SHOW_LIGHTMAP_COHERENCE
            // Kopiere endlich die Binärdaten
            for (y = src_h-1+addybefore; y>=-addyafter; y--)
            {
                // linker Rand
                for (x = addxbefore; x>0; x--)
                    dest_ptr[-x] = *src_ptr;

                for (x = src_w-1; x>=0; x--)
                {
#ifdef _DEBUG
                    zERR_ASSERT((int) dest_ptr < (int)  max_dest_ptr - addxafter);
                    zERR_ASSERT((int)  src_ptr < (int)  max_src_ptr);
                    zERR_ASSERT((int) dest_ptr >= (int) data + addxbefore);
                    zERR_ASSERT((int)  src_ptr >= (int) src_data);
#endif
                    *(dest_ptr++) = *(src_ptr++);
                }

                // rechter Rand
                for (x = addxafter; x>0; x--)
                    dest_ptr[x-1] = src_ptr[-1];

                if (y < src_h && y > 0)
                {
                    src_ptr  += src_pitch - src_w;
                    dest_ptr += pitch     - src_w;
                }
                else
                { // Rand; gehe wieder eine Zeile zurück
                    src_ptr  +=           - src_w;
                    dest_ptr += pitch     - src_w;
                }
            }
#endif

            tex->Unlock();

            // trage die meue Textur ein
            map->SetTexture(new_tex);

            // und verschiebe die Mapping so, dass die zu den neuen offsets passt.
            zVEC3 origin, up, right;
            map->GetLightmapOriginUpRight(origin, up, right);
            
            // zuerst lassen wir up und right sich auf pixel beziehen
            up    *= src_h;
            right *= src_w;

            // verschiebe den Ursprung, so daß der alte origin jetzt auf (xoffs,yoffs) gemappt wird
            zREAL uls = up*up;
            zREAL rls = right*right;
            origin -= up * ((yoffs)/uls) + right * ((xoffs)/rls);

            // und wieder zurück in normale u/v koordinaten in der normalen Textur
            up    /= comb_h;
            right /= comb_w;

            // zurück damit und fertig!
            map->SetLightmapOriginUpRight(origin, up, right);

			//
			if (deleteTexWhenDone)
			{
				// tex zeigt hier garantiert auf ein zCTextureExchange Objekt, also: kein Release()!
				delete tex; tex=0;				
			};
        }

        zCTextureConvert::CopyContents	(texCon, new_tex);

        texCon->Unlock();
        delete texCon; texCon = 0;

        new_tex->SetCacheOutLock(TRUE); // Lightmaps sollen im Speicher bleiben

        zRELEASE(new_tex);    
    }

    for(int i = items.GetNumInList()-1; i>=0; i--)
        delete items[i];
}

// =========================================================================================================


#pragma warning( default: 4244 ) 
