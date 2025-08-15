/******************************************************************************** 
 
     $Workfile:: zFileQBSP.cpp        $                $Date:: 11.09.00 19:40   $
     $Revision:: 9                    $             $Modtime:: 11.09.00 18:58   $
       $Author:: Speckels                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zFileQBSP.cpp $
 * 
 * 9     11.09.00 19:40 Speckels
 * 
 * 8     21.08.00 17:18 Hildebrandt
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 6     21.07.00 15:11 Hildebrandt
 * 
 * 5     21.07.00 14:28 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 4     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Speckels $
/// @version $Revision: 9 $ ($Modtime: 11.09.00 18:58 $)


#include <zCore.h>
#include <zWorld.h>
#include <zFile3d.h>
#include <zoption.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 


#define VERBOSE

#ifdef VERBOSE
	inline static void Print (zSTRING s) { zerr.Message (s); };
#else
	inline static void Print (zSTRING s) { };
#endif

static const zREAL MAP_SCALE = zREAL(3.4F);

typedef struct                 // A Directory entry
{ long  offset;                // Offset to entry, in bytes, from start of file
  long  size;                  // Size of entry in file, in bytes
} dentry_t;

/*
Quake2:
#define	LUMP_ENTITIES		0
#define	LUMP_PLANES			1
#define	LUMP_VERTEXES		2
#define	LUMP_VISIBILITY		3
#define	LUMP_NODES			4
#define	LUMP_TEXINFO		5
#define	LUMP_FACES			6
#define	LUMP_LIGHTING		7
#define	LUMP_LEAFS			8
#define	LUMP_LEAFFACES		9
#define	LUMP_LEAFBRUSHES	10
#define	LUMP_EDGES			11
#define	LUMP_SURFEDGES		12
#define	LUMP_MODELS			13
#define	LUMP_BRUSHES		14
#define	LUMP_BRUSHSIDES		15
#define	LUMP_POP			16
#define	LUMP_AREAS			17
#define	LUMP_AREAPORTALS	18
#define	HEADER_LUMPS		19

*/

// Here is the BSP header itself, made of a version tag, and 15 entries: 

struct zTFileQBSPHeader		   // The BSP file header
{ long  version;               // Model version, must be 0x17 (23).
  dentry_t entities;           // List of Entities.
  dentry_t planes;             // Map Planes.
                               // numplanes = size/sizeof(plane_t)
  dentry_t miptex;             // Wall Textures.
  dentry_t vertices;           //*Map Vertices.
                               // numvertices = size/sizeof(vertex_t)
  dentry_t visilist;           // Leaves Visibility lists.
  dentry_t nodes;              // BSP Nodes.
                               // numnodes = size/sizeof(node_t)
  dentry_t texinfo;            //*Texture Info for faces.
                               // numtexinfo = size/sizeof(texinfo_t)
  dentry_t faces;              //*Faces of each surface.
                               // numfaces = size/sizeof(face_t)
  dentry_t lightmaps;          // Wall Light Maps.
  dentry_t clipnodes;          // clip nodes, for Models.
                               // numclips = size/sizeof(clipnode_t)
  dentry_t leaves;             // BSP Leaves.
                               // numlaves = size/sizeof(leaf_t)
  dentry_t lface;              //*List of Faces.
  dentry_t edges;              //*Edges of faces.
                               // numedges = Size/sizeof(edge_t)
  dentry_t ledges;             //*List of Edges.
  dentry_t models;             // List of Models.
                               // nummodels = Size/sizeof(model_t)
};

const int MAX_MAP_HULLS = 4;

typedef struct
{
	float		mins[3], maxs[3];
	float		origin[3];
	int			headnode[MAX_MAP_HULLS];
	int			visleafs;		// not including the solid leaf 0
	int			firstface, numfaces;
} dmodel_t;


/*
typedef struct  
{ short		plane_id;          // The plane in which the face lies
                               //           must be in [0,numplanes[ 
  short		side;              // 0 if in front of the plane, 1 if behind the plane
  long		ledge_id;          // first edge in the List of edges
                               //           must be in [0,numledges[
  short		ledge_num;         // number of edges in the List of edges
  short		texinfo_id;        // index of the Texture info the face is part of
                               //           must be in [0,numtexinfos[ 
  zBYTE		typelight;         // type of lighting, for the face
  zBYTE		baselight;         // from 0xFF (dark) to 0 (bright)
  zBYTE		light[2];          // two additional light models  
  long		lightmap;          // Pointer inside the general light map, or -1
                               // this define the start of the face light map
} face_t;
*/

typedef struct { 
	float X;                    // X,Y,Z coordinates of the vertex
	float Y;                    // usually some integer value
	float Z;                    // but coded in floating point
} vertex_t;

typedef struct {
	unsigned short	v[2];		// vertex numbers
} edge_t;

typedef struct
{ vertex_t normal;             // Vector orthogonal to plane (Nx,Ny,Nz)
                               // with Nx2+Ny2+Nz2 = 1
  float		dist;               // Offset to plane, along the normal vector.
                               // Distance from (0,0,0) to the plane
  long    type;                // Type of plane, depending on normal vector.
} plane_t;

// typedef unsigned short ledge_t;
typedef int ledge_t;

const int MAXLIGHTMAPS=4;

typedef struct {
	short		planenum;
	short		side;

	int			firstedge;		// we must support > 64k edges
	short		numedges;	
	short		texinfo;

	// lighting info
	zBYTE		styles[MAXLIGHTMAPS];
	int			lightofs;		// start of [numstyles*surfsize] samples
} face_t;

///////////////////////////////
// Constructors, Destructors
///////////////////////////////

zCFileQuakeBSP::zCFileQuakeBSP() { 
	file	= 0; 
};

zCFileQuakeBSP::~zCFileQuakeBSP() { 
	delete file; file=0;
};

/*
- vertices
- ledges
- edges
- lfaces
- faces
- texinfo
*/

void zCFileQuakeBSP :: LoadQuakeBSP (const zSTRING& fileName, zCMesh *mesh, zCWorld* world) {
	Print ("D: QBSP: Loading QuakeBSP: \""+fileName+"\"");

	// Open File
	zoptions->ChangeDir	(DIR_MESHES);
	int i;
	file = zfactory->CreateZFile(fileName);
	file->Open();
	
	/////////////////////
	// Read Header
	/////////////////////

	zTFileQBSPHeader header;
	file->Read(&header, sizeof(header));
//	Print ("D: File-Version: "+zSTRING(header.version));

	/////////////////////
	// Read Vertices
	/////////////////////

	file->Seek (header.vertices.offset);
	int numVerts = header.vertices.size / sizeof(vertex_t);
//	Print ("D: Num Verts: "+zSTRING(numVerts));
	mesh->AllocVerts (numVerts);
	zCVertex **vertList = zNEW(zCVertex*) [numVerts];
	zPOINT3 p;
	zPOINT2 tex;				// hier noch dummy
	for (i=0; i<numVerts; i++) {
		file->Read (&p, sizeof(p));
		zVALUE tmp;
		tmp		= p.n[VY];
		p.n[VY] = p.n[VZ];
		p.n[VZ] = tmp;
//		zSwap (p.n[VZ],p.n[VY]);
//		vertList[i]= mesh->AddVertex(p, tex);
		p = MAP_SCALE * p;
		vertList[i]= mesh->AddVertex(p);
	};

	/////////////////////
	// Read Planes
	/////////////////////

	file->Seek (header.planes.offset);
	int numPlanes= header.planes.size / sizeof(plane_t);
	plane_t *planes = zNEW(plane_t) [numPlanes];
	file->Read (planes, sizeof(plane_t)*numPlanes);
	
	/////////////////////
	// Read Edges
	/////////////////////
	
	file->Seek (header.edges.offset);
	int numEdges = header.edges.size / sizeof(edge_t);
//	Print ("D: Num Edges: "+zSTRING(numEdges));
	edge_t *edges = zNEW(edge_t) [numEdges];
	file->Read (edges, sizeof(edge_t)*numEdges);

	/////////////////////
	// Read Edge-List
	/////////////////////
	
	file->Seek (header.ledges.offset);
	int numEdgeList = header.ledges.size / sizeof(ledge_t);
//	Print ("D: Num EdgeList: "+zSTRING(numEdgeList));
	ledge_t *edgeList = zNEW(ledge_t) [numEdgeList];
	file->Read (edgeList, sizeof(ledge_t)*numEdgeList);

	/////////////////////
	// Read Texinfo
	/////////////////////

	file->Seek (header.texinfo.offset);

	/////////////////////
	// Read ModelInfo
	/////////////////////

	dmodel_t modelInfo;
	file->Seek (header.models.offset);
	file->Read (&modelInfo, sizeof(dmodel_t));

	///////////////////////////
	// Read Entities / Lights
	///////////////////////////

	if (world) {
		zerr.Message ("D: QBSP: Reading light entities ..");
		int numLights=0;
		file->Seek (header.entities.offset);
		zSTRING		line, arg;
		int			numRead	= 0;
		int			pos		= file->Pos();
		int			end		= pos + header.entities.size;
		zCVobLight	*light=0;
		while (pos<end) {
			file->Read (line);
			if ((line.Search("\"light")!=-1) && (line.Search("\"classname\"")!=-1)) {
				if (light) {
					light->SetRange (260 * MAP_SCALE);		// default
					world->AddVob	(light); 
					numLights++;
				};
				light = zNEW(zCVobLight);
				light->SetIsStatic (TRUE);
//				zerr.Message (line);
			} else
			if (light) {
				arg = line.PickWord (3, "\"", "\"");
				if (line.Search("\"origin\"")!=-1) {
					zVEC3 org;
					org[0] = arg.PickWord_Old (1,"").ToFloat();
					org[1] = arg.PickWord_Old (2,"").ToFloat();
					org[2] = arg.PickWord_Old (3,"").ToFloat();
					zSwap (org[1], org[2]);
					org = org * MAP_SCALE;
					light->SetPositionWorld (org);
				} else
				if (line.Search("\"light\"")!=-1) {
					zREAL range;
					range = arg.ToFloat() * MAP_SCALE;
					light->SetRange (range);
					world->AddVob	(light);
					numLights++;
					light=0;
				};
			};
			numRead++;
			pos = file->Pos();
		};
		zerr.Message ("D: QBSP: numLights: "+zSTRING(numLights));
	};

//	file->Read (&modelInfo, header.entities.size);


	/////////////////////
	// Read Faces
	/////////////////////

	// Create Material
	zCMaterial *mat1 = zNEW(zCMaterial(".BSPMat1"));
	mat1->color.r = mat1->color.g = mat1->color.b = 200;
	//mat1->SetTexture (zSTRING("TUTENDTL.TGA"));
	zCMaterial *mat2 = zNEW(zCMaterial(".BSPMat2"));
	mat2->color.r = 128;
	mat2->color.g = 42;
	mat2->color.b = 42;
	//mat2->SetTexture (zSTRING("TUTENDTL.TGA"));
	zCMaterial *mat3 = zNEW(zCMaterial(".BSPMat3"));
	mat3->color.b = 170;
	mat3->color.r = mat3->color.g = 150;
	//mat3->SetTexture (zSTRING("TUTENDTL.TGA"));
//	mat1->SubRef();
//	mat2->SubRef();
//	mat3->SubRef();

	// Read Faces
	int maxNum, avgNum;
	maxNum = avgNum = 0;

	file->Seek (header.faces.offset);

	int firstFace	= modelInfo.firstface;
	int numFaces	= modelInfo.numfaces;
//	int firstFace	= 0;
//	int numFaces	= header.faces.size / sizeof(face_t);

	//	Print ("D: Num Faces: "+zSTRING(numFaces));
	mesh->AllocPolys (numFaces);
	face_t face;
	int v1;
	int j;
	zCVertex	*faceVert[zMAX_POLY_VERTS];
	zCPolygon	*poly = 0;;

	for (i=0; i<numFaces;i++) {
		file->Read (&face, sizeof(face));
		
		if (i<firstFace) continue;
 
		avgNum += face.numedges;
		maxNum = zMax (maxNum, face.numedges);
		if (face.numedges<=zMAX_POLY_VERTS) {
			//
			int vertNr = 0;
			for (int n=face.firstedge; n<face.numedges+face.firstedge; n++) {
				j  = edgeList[n];
				if (zAbs(j)>numEdges) { 
					zERR_WARNING("D: QBSP: Error: Illegal edgeList index :"+zSTRING(j));
					continue;
				};
				if (j<0) { v1 = edges[-j].v[0]; /* v2 = edges[-j].v[1]; */ }
				    else { v1 = edges[ j].v[1]; /* v2 = edges[ j].v[0]; */ };
				if (j==0) zERR_WARNING("D: QBSP: Error: Illegal edgeList index: _0_");
				// Add Vertex #1
				faceVert[vertNr] = vertList[v1];
				vertNr++;
			};
			// Create Poly
/*			poly = mesh->AddPoly (faceVert[0], faceVert[1], faceVert[2]);
			for (int m=3; m<vertNr; m++) poly->AddVertex(faceVert[m]); };*/
/*			poly = mesh->AddPoly (faceVert[vertNr],
								  faceVert[vertNr-1],
								  faceVert[vertNr-2]);
			vertNr -= 3;
			for (; vertNr>=0; vertNr--) {
				poly->AddVertex(faceVert[vertNr]);
			};
*/
			poly = mesh->AddPoly ();
			poly->AllocVerts (vertNr);

			vertNr--;
			int max = vertNr;
//			for (int i=0; i<vertNr; i++) {
			for (; vertNr>=0; vertNr--) {
//				poly->SetVertex (i, faceVert[i]);
				poly->SetVertex (max-vertNr, faceVert[vertNr]);
			};

			// Set Normal
			zTPlane tmpPlane;
			if (face.side==0) {
				tmpPlane.normal.n[VX]	= planes[face.planenum].normal.X;
				tmpPlane.normal.n[VY]	= planes[face.planenum].normal.Z;
				tmpPlane.normal.n[VZ]	= planes[face.planenum].normal.Y;
				tmpPlane.distance		= planes[face.planenum].dist;
			} else {
				tmpPlane.normal.n[VX]	=-planes[face.planenum].normal.X;
				tmpPlane.normal.n[VY]	=-planes[face.planenum].normal.Z;
				tmpPlane.normal.n[VZ]	=-planes[face.planenum].normal.Y;
				tmpPlane.distance		=-planes[face.planenum].dist;
			};
			tmpPlane.distance *= MAP_SCALE;
			
			poly->polyPlane = tmpPlane;
//		poly->CalcNormal  ();

			// Set Material
//			poly->SetMaterial (mat1);
			zPOINT3 floorNormal(0,1,0);
			zVALUE  value = floorNormal*poly->polyPlane.normal;
			if (zAbs(value)<0.5) { 
				value = zPOINT3(0,0,1)*poly->polyPlane.normal;
				if (zAbs(value)<0.5) poly->SetMaterial (mat3);
				else				 poly->SetMaterial (mat1);
			} else poly->SetMaterial (mat2);
		};
	};
	zerr.Message ("D: QBSP: Verts per Poly. Max: "+zSTRING(maxNum)+", Avg: "+zSTRING(float(avgNum) /float(numFaces)));

	/////////////////////
	// Close File
	/////////////////////

	file->Close();

	// Cleanup
	delete[] planes;
	delete[] edgeList;
	delete[] edges;
	delete[] vertList;
	delete	 file;
	
	//
	mesh->CalcBBox3D();
	//
	zPATH path (fileName);
	mesh->SetMeshName (path.GetFilename()+"."+path.GetExt());
//	mesh->SetDefaultPlanarMapping (1.0F, 1.0F);
	//
	zerr.Message ("D: QBSP: ... Finished. Verts: "+zSTRING(mesh->numVert) +
		" Polys: "+zSTRING(mesh->numPoly)
	);
};

#pragma warning( default : 4244 ) 
