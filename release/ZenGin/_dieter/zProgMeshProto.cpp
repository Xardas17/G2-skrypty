/******************************************************************************** 
  
     $Workfile:: zProgMeshProto.cpp   $                $Date:: 24.04.01 17:33   $
     $Revision:: 50                   $             $Modtime:: 23.04.01 23:26   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Progressive Meshes
   created: 9.11.99

 * $Log: /current_work/ZenGin/_Dieter/zProgMeshProto.cpp $
 * 
 * 50    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 49    16.02.01 15:58 Moos
 * F3-Fix
 * 
 * 48    15.02.01 18:50 Hildebrandt
 * 
 * 47    15.02.01 3:38 Hildebrandt
 * 
 * 46    15.02.01 1:49 Hildebrandt
 * 
 * 45    14.02.01 7:28 Hildebrandt
 * 
 * 44    8.02.01 12:05 Hildebrandt
 * 
 * 43    5.02.01 20:45 Hildebrandt
 * 
 * 42    5.02.01 19:13 Hildebrandt 
 * 
 * 41    31.01.01 6:02 Hildebrandt
 * 
 * 40    31.01.01 5:47 Hildebrandt
 * 
 * 39    30.01.01 23:59 Hildebrandt
 * 
 * 38    30.01.01 5:16 Hildebrandt
 * 
 * 37    15.01.01 3:54 Hildebrandt
 * 
 * 36    20.12.00 3:01 Hildebrandt
 * 
 * 35    4.12.00 17:29 Hildebrandt
 * 
 * 34    22.11.00 16:37 Hildebrandt
 * 
 * 33    17.11.00 1:29 Hildebrandt
 * 
 * 32    3.11.00 19:05 Hildebrandt
 * 
 * 31    25.10.00 15:06 Hildebrandt
 * 
 * 30    11.10.00 19:45 Hildebrandt
 * 
 * 29    28.09.00 19:20 Hildebrandt
 * 
 * 28    22.09.00 19:18 Hildebrandt
 * 
 * 27    21.09.00 22:07 Hildebrandt
 * 
 * 26    21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 23    7.09.00 20:41 Hildebrandt
 * 
 * 22    6.09.00 16:30 Hildebrandt
 * 
 * 21    2.09.00 7:51 Rueve
 * 
 * 20    2.09.00 6:53 Hildebrandt
 * 
 * 19    31.08.00 17:04 Hildebrandt
 * 
 * 18    22.08.00 21:49 Hildebrandt
 * 
 * 17    21.08.00 17:18 Hildebrandt
 * 
 * 16    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 15    21.07.00 15:11 Hildebrandt
 * 
 * 14    21.07.00 14:28 Hildebrandt
 * 
 * 13    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 12    6.07.00 13:45 Hildebrandt
 * 
 * 6     10.05.00 23:27 Hildebrandt
 * zenGin 089i
 * 
 * 5     8.05.00 2:17 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 12    22.03.00 21:07 Hildebrandt
 * 
 * 11    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 9     22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 8     20.02.00 18:08 Hildebrandt
 * zenGin 087c
 * 
 * 7     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 5     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     18.11.99 22:18 Hildebrandt
 * 
 * 3     16.11.99 19:49 Hildebrandt
 * 
 * 2     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 50 $ ($Modtime: 23.04.01 23:26 $)

// =======================================================================================================================

#include <zCore.h>
#include <zProgMesh.h>
#include <zoption.h>
#include <zWorld.h>
#include <zFile3d.h>
#include <zArchiver.h>
#include <zView.h>
#include <zVertexBuffer.h>
#include <zRenderLightContainer.h>
#include <zRenderManager.h>
#include <zSky.h>
#include <zModel.h>

//#define DEBUG_EFFECTS

#ifdef DEBUG_EFFECTS
#include "zinput.h"
#endif


// =======================================================================================================================

#ifdef DEBUG_HILDEBRANDT
//	#define zPM_SHOW_LOD_INFO
//	#define zPM_DRAW_NODE_HIERARCHY_OBB
//	#define zPM_DRAW_OBB
#endif

// LOD Groesse, ab der autom. von Exact auf Prelit gestellt wird 
#define zPM_PRELIT_EXACT_THRESH					zREAL(0.4F)
//#define zPM_PRELIT_EXACT_THRESH				zREAL(-99)

#define zPM_NUM_VBUFFER_VERT					4096
//#define zPM_NUM_VBUFFER_VERT					2048

//#define COUNT_MORPHED_VERTS
int	  s_morphedVerts = 0;
float zEFFECT_VERT_PERC = 0.5f;


// =======================================================================================================================

zCLASS_DEFINITION	(zCProgMeshProto	, zCVisual			,	zCLASS_FLAG_SHARED_OBJECTS,	1)
zCLASS_DEFINITION	(zCMeshSoftSkin		, zCProgMeshProto	,	0,	0)

zTFrameCtr			zCProgMeshProto::s_frameCtr			= -1;
zVEC3				zCProgMeshProto::s_posCacheList		[NUM_POS_CACHE];
zPMINDEX			zCProgMeshProto::s_wedgeRemap		[NUM_WEDGE_CACHE];
zVEC3				zCProgMeshProto::s_posNormalCSList	[NUM_POS_CACHE];
zCArray<zWORD>		zCProgMeshProto::s_workIndexList	(1024);
int					zCProgMeshProto::s_subMeshRenderDir	= +1;
zBOOL				zCProgMeshProto::s_autoSubdivEnabled= FALSE;
zDWORD				zCProgMeshProto::s_classCtorCtr		= 0;
int					zCProgMeshProto::s_posCacheCount	= 0;
int					zCProgMeshProto::s_posCacheCountLOD	= 0;
int					zCProgMeshProto::s_posCacheIndex	= 0;
zVEC3				zCProgMeshProto::s_posCacheListLOD		 [NUM_LOD_CACHE];
int					zCProgMeshProto::s_posCacheListLODIndices[NUM_LOD_CACHE*3];


static				zVEC3			s_morphVec					= zVEC3(0,0,0);
static				zREAL			s_morphWeight				= 0;	
static				zTAnimationMode	s_morphMode					= zVISUAL_ANIMODE_NONE;	


// tmp, debug
#define DO_MORPH TRUE

// =======================================================================================================================

static void CreateShadowMatrix(zMAT4& shadowMat, const zTPlane& groundPlane, zVEC4& lightpos)
{
#if 0

	lightpos.Normalize();
	lightpos[VW]=1;
	zREAL dot;
	/* Find dot product between light position vector and ground plane normal. */
	dot =		groundPlane.normal[VX]	* lightpos[VX] +
		groundPlane.normal[VY]	* lightpos[VY] +
		groundPlane.normal[VZ]	* lightpos[VZ] +
		groundPlane.distance	* lightpos[VW];
	shadowMat[0][0] = dot - lightpos[VX] * groundPlane.normal[VX];
	shadowMat[1][0] = 0.f - lightpos[VX] * groundPlane.normal[VY];
	shadowMat[2][0] = 0.f - lightpos[VX] * groundPlane.normal[VZ];
	shadowMat[3][0] = 0.f - lightpos[VX] * groundPlane.distance;
	
	shadowMat[0][1] = 0.f - lightpos[VY] * groundPlane.normal[VX];
	shadowMat[1][1] = dot - lightpos[VY] * groundPlane.normal[VY];
	shadowMat[2][1] = 0.f - lightpos[VY] * groundPlane.normal[VZ];
	shadowMat[3][1] = 0.f - lightpos[VY] * groundPlane.distance;
	
	shadowMat[0][2] = 0.f - lightpos[VZ] * groundPlane.normal[VX];
	shadowMat[1][2] = 0.f - lightpos[VZ] * groundPlane.normal[VY];
	shadowMat[2][2] = dot - lightpos[VZ] * groundPlane.normal[VZ];
	shadowMat[3][2] = 0.f - lightpos[VZ] * groundPlane.distance;
	
	shadowMat[0][3] = 0.f - lightpos[VW] * groundPlane.normal[VX];
	shadowMat[1][3] = 0.f - lightpos[VW] * groundPlane.normal[VY];
	shadowMat[2][3] = 0.f - lightpos[VW] * groundPlane.normal[VZ];
	shadowMat[3][3] = dot - lightpos[VW] * groundPlane.distance;
	shadowMat = shadowMat.Transpose();

#else
	zREAL k1 = (0-lightpos[VX]) / lightpos[VY];
	zREAL k2 = (0-lightpos[VZ]) / lightpos[VY];
	shadowMat.MakeIdentity();
	shadowMat[1][1]	= 0;
	shadowMat[0][1]	= k1;
	shadowMat[2][1]	= k2;
	shadowMat[1][3]	= 3;
#endif
}

static zBOOL RecreateLostVBCallback (zCVertexBuffer* vertexBuffer, void *pmProto)
{
	static_cast<zCProgMeshProto*>(pmProto)->PackStaticVertexBuffers();
	return TRUE;
};


// =======================================================================================================================

// zCProgMeshProto :: zCSubMesh

zCProgMeshProto::zCSubMesh::zCSubMesh() 
{
	material		= 0;
	vbStartIndex	= 0;
};

zCProgMeshProto::zCSubMesh::~zCSubMesh()
{
	zRELEASE (material);
};

// =======================================================================================================================

zREAL				zCProgMeshProto::s_lodParamStrengthOverride	=-1;
zREAL				zCProgMeshProto::s_lodParamStrengthModifier	= 1.0F;

zBOOL				zCProgMeshProto::s_markMeshMaterials		= FALSE;
zCVertexBufferDyn*	zCProgMeshProto::s_vertBufferColor			= 0;
zCVertexBufferDyn*	zCProgMeshProto::s_vertBufferNormal			= 0;

zCProgMeshProto::zCProgMeshProto()
{
	dataPool				= 0;
	dataSize				= 0;
	//shadowPMesh			= 0;
//	lightingMode			= zPM_LIGHTING_MODE_PRELIT;
	lightingMode			= zPM_LIGHTING_MODE_EXACT; 
	bbox3D.InitZero			();
	subMeshList				= 0;
	numSubMeshes			= 0;
	vertexBufferStatic		= 0;
	pmeshID					= s_classCtorCtr++;

	//
	lodParams.strength		= 1.0F;					// groesser ist aggressiver (0.5F)
	lodParams.zDisplace2	= (00.0F*00.0F);
	lodParams.morphPerc		= 0;					// % der aktiven Verts, die gemorphed werden
													// per Default 0! Nichts morphen!
//	lodParams.morphPerc		= 0.03F;				// % der aktiven Verts, die gemorphed werden
	lodParams.minVerts		= 0;

	//
	this->CalcRenderSortKey	();
	this->SetAlphaTestingEnabled(FALSE);
};

zCProgMeshProto::~zCProgMeshProto()
{
	// VertexBuffer
//	delete vertexBufferStatic;	vertexBufferStatic=0;
    if (vertexBufferStatic)
	    vertexBufferStatic->RemoveRecreateLostVBCallback (&RecreateLostVBCallback, this); // [Moos] Melde dich wieder richtig ab; F3-Crashfix, hoffentlich..

	zvertexBufferMan.ReleaseVertexBuffer	(vertexBufferStatic);
	vertexBufferStatic		= 0;


	//
	delete[] subMeshList;	subMeshList	= 0;

	// zuletzt !
	delete[] dataPool;		dataPool	= 0;
};

void zCProgMeshProto::CalcRenderSortKey ()
{
	if (this->vertexBufferStatic)
	{
		renderSortKey = 0xF0000000 |
						(vertexBufferStatic->GetVertexBufferID() << 16) | 
						this->pmeshID;
	} else
	{
		renderSortKey = 0xF0000000 |
						this->pmeshID;
	};
};

#define LOD_DYNAMIC_RANGE		zREAL(0.60F)
#define LOD_DYNAMIC_RANGE_HALF	zREAL(0.45F)

// 0.65, 0.50
void zCProgMeshProto::SetLODParamStrengthModifier (const zREAL strength)	
{ 
	s_lodParamStrengthModifier	= strength;	
	zClamp01					(s_lodParamStrengthModifier);

	// den Bereich von [0..1] auf den Bereich [1.1 .. 0.9] abbilden (Fix in v108)
	s_lodParamStrengthModifier	= zREAL(1.0F) - s_lodParamStrengthModifier;		// invertieren
	s_lodParamStrengthModifier	= ((s_lodParamStrengthModifier * LOD_DYNAMIC_RANGE) - LOD_DYNAMIC_RANGE_HALF) + zREAL(1.0F);
};

zREAL zCProgMeshProto::GetLODParamStrengthModifier () 
{ 
	return zREAL(1.0F) - (((s_lodParamStrengthModifier - zREAL(1.0F)) + LOD_DYNAMIC_RANGE_HALF) / zREAL(LOD_DYNAMIC_RANGE));	
};

/*void zCProgMeshProto::PackStaticVertexBuffers()
{
	// VB noch nicht vorhanden ? => initial erzeugen
	if (!vertexBufferStatic)
		vertexBufferStatic			= zrenderer->CreateVertexBuffer();

	// NumVerts zaehlen
	int numVertsRequired=0;
	for (int i=0; i<numSubMeshes; i++)
		numVertsRequired += subMeshList[i].wedgeList.GetNum();

	// Create Buffer
	vertexBufferStatic->Create		(zVBUFFER_VERTFORMAT_XYZ			|
									 zVBUFFER_VERTFORMAT_NORMAL			|
									 zVBUFFER_VERTFORMAT_TEXUV1,
									 numVertsRequired,
									 zVBUFFER_CREATE_FLAG_WRITEONLY);
	
	// Lock
	vertexBufferStatic->Lock		(zVBUFFER_LOCK_FLAG_WRITEONLY		|
									 zVBUFFER_LOCK_FLAG_DISCARDCONTENTS);

	// Fill Buffer
	int currentIndex=0;
	for (i=0; i<numSubMeshes; i++)
	{
		zCSubMesh		*subMesh	= &(subMeshList[i]);
		subMesh->vbStartIndex		= currentIndex;
		for (int j=0; j<subMesh->wedgeList.GetNum(); j++)
		{
			vertexBufferStatic->SetXYZ		(currentIndex, posList[subMesh->wedgeList[j].position]);
			vertexBufferStatic->SetNormal	(currentIndex, subMesh->wedgeList[j].normal);
			vertexBufferStatic->SetTexUV0	(currentIndex, subMesh->wedgeList[j].texUV);
			++currentIndex;
		};
	};

	// Unlock
	vertexBufferStatic->Unlock					();
	vertexBufferStatic->Optimize				();

	vertexBufferStatic->SetRecreateLostVBCallback (&RecreateLostVBCallback, this);
};*/

void zCProgMeshProto::PackStaticVertexBuffers()
{
	// NumVerts zaehlen
	int numVertsRequired=0;
	for (int i=0; i<numSubMeshes; i++)
		numVertsRequired += subMeshList[i].wedgeList.GetNum();

	enum {	LOCK_FLAGS				= zVBUFFER_LOCK_FLAG_WRITEONLY		|
									  zVBUFFER_LOCK_FLAG_DISCARDCONTENTS
	};

	// VB noch nicht vorhanden ? => initial vom VBMan organisieren
	int		currentIndex	= 0;
	zBOOL	firstBufferFill	= FALSE;
	if (!vertexBufferStatic)
	{
		enum {	VERTEX_FORMAT		= zVBUFFER_VERTFORMAT_XYZ			|
									  zVBUFFER_VERTFORMAT_NORMAL		|
									  zVBUFFER_VERTFORMAT_TEXUV1
									};
		vertexBufferStatic			= zvertexBufferMan.AcquireVertexBuffer (VERTEX_FORMAT, 
																			numVertsRequired, 
																			zVBUFFER_CREATE_FLAG_WRITEONLY,
																			LOCK_FLAGS,
																			currentIndex);
		firstBufferFill				= TRUE;
	};

	// Lock
	// Optimierung: Lock/Unlock wird hier nicht bei jedem einzelnen Fill/Benutzer gemacht, da dieses Zeit kostet und 
	// der VB idR von mehreren benutzt und nacheinaner gefuellt wird. Beim ersten Fill muss allerdings sichergestellt werden,
	// dass der Buffer wirklich gelockt ist.
	if (!vertexBufferStatic->IsLocked())
		if (!vertexBufferStatic->Lock	(LOCK_FLAGS))
		{
			zERR_WARNING("C: zCProgMeshProto::PackStaticVertexBuffers(): VB lock failed!");
			return;
		}


	// Fill Buffer
	{
		for (i=0; i<numSubMeshes; i++)
		{
			zCSubMesh		*subMesh	= &(subMeshList[i]);

			// Beim ersten Fill ist der index nocht unbekannt und ergibt sich aus dem laufenden Zaehlen.
			// Bei weiteren Fills (bei z.B. Windowed/Fullscreen Wechseln) ist der Ziel Index bereits bekannt und wird benutzt,
			if (firstBufferFill)	subMesh->vbStartIndex	= currentIndex;
			else					currentIndex			= subMesh->vbStartIndex;

			for (int j=0; j<subMesh->wedgeList.GetNum(); j++)
			{
				vertexBufferStatic->SetXYZ		(currentIndex, posList[subMesh->wedgeList[j].position]);
				vertexBufferStatic->SetNormal	(currentIndex, subMesh->wedgeList[j].normal);
				vertexBufferStatic->SetTexUV0	(currentIndex, subMesh->wedgeList[j].texUV);
				++currentIndex;
			};
		};
	};

	// Unlock
	// ..

	if (firstBufferFill)
		vertexBufferStatic->AddRecreateLostVBCallback (&RecreateLostVBCallback, this);

	//
	this->CalcRenderSortKey	();
};


static const zSTRING pmeshFileExt[1] = { ".3DS" };

const zSTRING* zCProgMeshProto::GetFileExtension (int i)
{
	if (i!=0) return 0;
	return &(pmeshFileExt[0]);
};

zCVisual* zCProgMeshProto::LoadVisualVirtual	(const zSTRING& visualName) const
{
	return Load (visualName);
};

zSTRING  zCProgMeshProto::GetVisualName ()
{
	return GetObjectName();
};

zCVisual* zCProgMeshProto::Load (const zSTRING& inFileName) 
{
	// lädt mesh von disk (3ds,bsp,...) falls nicht bereits im Speicher
	// Input-Filename: gross/klein egal, enthaltener Pfad wird zuerst benutzt, Ext wird benutzt
	// alt: meshName: Pfad (rel ab MESHES), filename, ext
	// meshName: filename, ext

	zSTRING fileName		(inFileName);
	fileName.Upper			();
	zPATH meshPath			(fileName);
	const zSTRING objectName= meshPath.GetFilename()+"."+meshPath.GetExt();
	zCProgMeshProto *pmesh	= static_cast<zCProgMeshProto*>(zCProgMeshProto::GetStaticClassDef()->SearchObject(objectName));

	if (pmesh) {
		pmesh->AddRef();
	} else {
		// create new mesh & load
		// mesh bereits im internen Format ?

		if (zCMaterial::GetUsageDefault	()!=zCMaterial::zMAT_USAGE_LEVEL) 
		{
			// [BENDLIN] Addon Patch - Meshes im Soundverzeichnis
//			zoptions->ChangeDir	(DIR_COMPILED_MESHES);
			zCFileBIN file(zoptions->GetDirString(DIR_COMPILED_MESHES) + meshPath.GetFilename()+".MRM");
			zBOOL ok		= FALSE;
			if (file.BinExists()) 
			{
				file.BinOpen			();
				pmesh					= zNEW(zCProgMeshProto); 
				pmesh->SetObjectName	(objectName);
				ok						= pmesh->Load (file);
				if (ok)
				{
					pmesh->PackStaticVertexBuffers();		// FIXME
				} else 
				{
					// Mesh konnte nicht korrekt geladen werden, Objekt & "objectName" wieder freigeben
					pmesh->Release();
					pmesh=0;
				};
			};
			file.BinClose ();
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
					};
				};
			}

			if (found) {
				zCMesh *mesh = zNEW(zCMesh);
				if (meshPath.GetExt().Search("3DS")!=-1) {
					zCFile3DS meshFile;
					meshFile.Load3DS  (fileName, mesh);
				} else if (meshPath.GetExt().Search("BSP")!=-1) {
					zCFileQuakeBSP meshFile;
					meshFile.LoadQuakeBSP (fileName, mesh, 0);
				};
				if (mesh) {
					// Level-Mesh: nicht konvertieren !
					if (zCMaterial::GetUsageDefault	()==zCMaterial::zMAT_USAGE_LEVEL) {
						mesh->SetMeshName	(objectName);
						return mesh;
					} else 
					{
						pmesh				= zNEW(zCProgMeshProto);
						pmesh->SetObjectName(objectName);
//						BuildProgMeshProto	(mesh, pmesh, 0, zPM_BUILD_FLAG_NO_LOD | zPM_BUILD_FLAG_NO_POSNORMALS);
						if (fileName.Search("NOLOD")!=-1)
						{
							BuildProgMeshProto	(mesh, pmesh, 0, zPM_BUILD_FLAG_NO_POSNORMALS|zPM_BUILD_FLAG_NO_LOD);
						}
						else BuildProgMeshProto	(mesh, pmesh, 0, zPM_BUILD_FLAG_NO_POSNORMALS);
						pmesh->PackStaticVertexBuffers();		// FIXME

						// [BENDLIN] Addon Patch - Meshes im Soundverzeichnis
//						zoptions->ChangeDir	(DIR_COMPILED_MESHES);
						zCFileBIN file;
						file.BinCreate		(zoptions->GetDirString(DIR_COMPILED_MESHES) + meshPath.GetFilename()+".MRM"); 
						pmesh->Save			(file);
						file.BinClose		();
						mesh->Release		();
						mesh				=0;
					};
				};
			};
		};
	};
goOn:;
	if (!pmesh)	zERR_WARNING ("D: zProgMeshProto(::Load): Could not load Mesh: "+inFileName);
	return pmesh;
};

zBOOL zCProgMeshProto::BuildProgMeshProto (zCMesh *sourceMesh, zCProgMeshProto *destProgMesh, zCArray<int> *posListRemap, int buildFlags)
{
	zCProgMeshBuilder *pmBuilder	= zNEW(zCProgMeshBuilder);
	zBOOL res						= pmBuilder->BuildProgMeshProto (sourceMesh, destProgMesh, posListRemap, buildFlags);
	delete pmBuilder;
	return res;
};

zBOOL zCCFASTCALL zCProgMeshProto::CheckRayPolyIntersection (zCSubMesh		*subMesh, 
															 int			triIndex, 
															 const zPOINT3& rayOrigin, 
															 const zPOINT3& ray, 
															 zPOINT3&		inters, 
															 zVALUE&		alpha) const 
{
	// Quelle : news.raypoly.txt, web-page
	// output : intersection, alpha
	// Achtung: alles im WorldSpace !! (bzw. im Object-Space des Polygons)
	// - Backface-Culling: Schnittpunkte werden nur gemeldet, wenn der Ray das Poly von VORNE durchdringt
	// - nur Schnittpunkte im alpha-Bereich 0..1 sind valid.

	zERR_ASSERT (subMesh->triPlaneList.GetNum()>0);
	const zTPlane &triPlane = subMesh->triPlaneList[subMesh->triPlaneIndexList[triIndex]];

	// 1) Schnitt Ray/Plane finden, Backface-Culling
	zREAL dn;
 	dn		= ray * triPlane.normal;
	if (!zIsNegative (dn)) return FALSE;										// parallel, backface ?
	// ACHTUNG: dn ist negativ (<0 , s.o.!)
	alpha	= (triPlane.distance - (triPlane.normal * rayOrigin));
	if ((zIsGreaterZero(alpha)) || (alpha<dn)) return FALSE;									// vor/hinter Betrachter ?

	const zREAL	dnInv	= zREAL(1.0F) / dn;		// div ueberlappt mit folgendem Integer-Code..
	int		vx, vy, vz;
	zVEC2	a;
	a[VX]	= zAbsApprox(triPlane.normal[VX]);
	a[VY]	= zAbsApprox(triPlane.normal[VY]);
	vz		= (zIsSmallerPositive (a.n[VX], a.n[VY]))							? VY : VX;
	vz		= (zIsSmallerPositive (a.n[vz], zAbsApprox(triPlane.normal[VZ])))	? VZ : vz;
	vx		= vz+1; if (vx>2) vx=0;
	vy		= vx+1; if (vy>2) vy=0;

	alpha	= alpha * dnInv;
	inters	= rayOrigin + alpha*ray;

	const zVEC3& pos0		= posList[subMesh->wedgeList[subMesh->triList[triIndex].wedge[0]].position];
	const zVEC3& pos1		= posList[subMesh->wedgeList[subMesh->triList[triIndex].wedge[1]].position];
	const zVEC3& pos2		= posList[subMesh->wedgeList[subMesh->triList[triIndex].wedge[2]].position];

	const zVALUE a_c0		= (pos0  [vx] - pos2[vx]);
	const zVALUE a_c1		= (pos0  [vy] - pos2[vy]);
	const zVALUE b_c0		= (pos1  [vx] - pos2[vx]);
	const zVALUE b_c1		= (pos1  [vy] - pos2[vy]);
	const zVALUE p_c0		= (inters[vx] - pos2[vx]);
	const zVALUE p_c1		= (inters[vy] - pos2[vy]);


	const zVALUE denom		= (a_c0*b_c1 - a_c1*b_c0);			if (denom==0)	return FALSE;
	const zVALUE denomInv	= zREAL(1.0F) / denom;
	const zVALUE u			= (p_c0*b_c1 - p_c1*b_c0) * denomInv;
	const zVALUE v			= (a_c0*p_c1 - a_c1*p_c0) * denomInv;
	
	return /* inside = */ ((u + v < 1) && (u < 1) && (v < 1) && (!zIsNegative(u)) && (!zIsNegative(v)));
};

zBOOL zCCFASTCALL zCProgMeshProto::CheckRayPolyIntersection2Sided ( zCSubMesh		*subMesh, 
																	int				triIndex, 
																	const zPOINT3&	rayOrigin, 
																	const zPOINT3&	ray, 
																	zPOINT3&		inters, 
																	zVALUE&			alpha) const 
{
	// Quelle : news.raypoly.txt, web-page
	// output : intersection, alpha
	// Achtung: alles im WorldSpace !! (bzw. im Object-Space des Polygons)
	// - Backface-Culling: Schnittpunkte werden nur gemeldet, wenn der Ray das Poly von VORNE durchdringt
	// - nur Schnittpunkte im alpha-Bereich 0..1 sind valid.

	zERR_ASSERT (subMesh->triPlaneList.GetNum()>0);
	const zTPlane &triPlane = subMesh->triPlaneList[subMesh->triPlaneIndexList[triIndex]];

	// 1) Schnitt Ray/Plane finden, Backface-Culling
	zREAL dn;
 	dn		= ray * triPlane.normal;
	if (dn==0) return FALSE;													// parallel?
	// Achtung: dn ist hier NICHT negativ !
	alpha	= (triPlane.distance - (triPlane.normal * rayOrigin)) / dn;
	if (!zIsInRange01(alpha)) return FALSE;
	inters	= rayOrigin + alpha*ray;

	// 2) Closest Axis finden (src: solid) (Achse, mit groesstem Abs-Wert)
	int		vx, vy, vz;
	zVEC2	a;
	a[VX]	= zAbsApprox(triPlane.normal[VX]);
	a[VY]	= zAbsApprox(triPlane.normal[VY]);
	vz		= (zIsSmallerPositive (a.n[VX], a.n[VY]))							? VY : VX;
	vz		= (zIsSmallerPositive (a.n[vz], zAbsApprox(triPlane.normal[VZ])))	? VZ : vz;
	vx		= vz+1; if (vx>2) vx=0;
	vy		= vx+1; if (vy>2) vy=0;

	const zVEC3& pos0		= posList[subMesh->wedgeList[subMesh->triList[triIndex].wedge[0]].position];
	const zVEC3& pos1		= posList[subMesh->wedgeList[subMesh->triList[triIndex].wedge[1]].position];
	const zVEC3& pos2		= posList[subMesh->wedgeList[subMesh->triList[triIndex].wedge[2]].position];

	const zVALUE a_c0		= (pos0  [vx] - pos2[vx]);
	const zVALUE a_c1		= (pos0  [vy] - pos2[vy]);
	const zVALUE b_c0		= (pos1  [vx] - pos2[vx]);
	const zVALUE b_c1		= (pos1  [vy] - pos2[vy]);
	const zVALUE p_c0		= (inters[vx] - pos2[vx]);
	const zVALUE p_c1		= (inters[vy] - pos2[vy]);


	const zVALUE denom		= (a_c0*b_c1 - a_c1*b_c0);			if (denom==0)	return FALSE;
	const zVALUE denomInv	= zREAL(1.0F) / denom;
	const zVALUE u			= (p_c0*b_c1 - p_c1*b_c0) * denomInv;
	const zVALUE v			= (a_c0*p_c1 - a_c1*p_c0) * denomInv;
	
	return /* inside = */ ((u + v < 1) && (u < 1) && (v < 1) && (!zIsNegative(u)) && (!zIsNegative(v)));
};

/*
	zBOOL	b_inside = FALSE;
	zBOOL	b1 = (((B.x-A.x)*(inters[vy]-A.y) - (B.y-A.y)*(inters[vx]-A.x)) >= 0);
	zBOOL	b2 = (((C.x-B.x)*(inters[vy]-B.y) - (C.y-B.y)*(inters[vx]-B.x)) >= 0);

	if (b1==b2)
	{
	   b_inside = ( b1 == (((A.x-C.x)*(inters[vy]-C.y) - (A.y-C.y)*(inters[vx]-C.x)) >= 0)); 
	}
*/

zBOOL				zCProgMeshProto::TraceRay(	const zVEC3&		rayOrigin, 
												const zVEC3&		ray, 
												const int			traceFlags, 
												zTTraceRayReport	&report) 
{ 
	// Input-Ray		: objectSpace
	// Output-Location	: objectSpace

	//
	report.foundHit		= FALSE;
	report.foundPoly	= 0;

	// lineare Suche ueber die Tris hinweg
	zPOINT3	inters;
	zREAL	alpha;
	zBOOL	testTwoSided	= (traceFlags & zTRACERAY_POLY_2SIDED);
	zREAL	bestAlpha		= 999;
	int		bestTriIndex	= 0;
	zTPlane	*bestPlane		= 0;

	for (int s=0; s<numSubMeshes; s++)
	{
		zCSubMesh *subMesh = &(subMeshList[s]);

		// kein (effizienter) Test moeglich, wenn keine Triplanes vorliegen
		if (subMesh->triPlaneList.GetNum()<=0) continue;

		const zCMaterial *mat = subMesh->material;
		// Traceflags: zTRACERAY_POLY_TEST_WATER, zTRACERAY_POLY_IGNORE_TRANSP
		if (mat->GetMatGroup()==zMAT_GROUP_WATER) {
			if (!(traceFlags & zTRACERAY_POLY_TEST_WATER))			continue;
		} else {
			if ((traceFlags & zTRACERAY_POLY_IGNORE_TRANSP)) {
				if ((mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE) || ((mat->GetTexture()) && (mat->GetTexture()->HasAlphaChannel())))	
					continue;
			};
		};
		if (mat->GetNoCollDet()) continue;

		for (int i=0; i<subMesh->triList.GetNum(); i++)
		{
			zBOOL hit;
			if (testTwoSided)	hit	= CheckRayPolyIntersection2Sided(subMesh, i, rayOrigin, ray, inters, alpha);
			else				hit = CheckRayPolyIntersection		(subMesh, i, rayOrigin, ray, inters, alpha);
			if (hit)
			{
				// First Hit
				if ((traceFlags & zTRACERAY_FIRSTHIT)!=0)	
				{
					bestTriIndex			= i;
					bestPlane				= &(subMesh->triPlaneList[subMesh->triPlaneIndexList[bestTriIndex]]);
					report.foundIntersection= inters;
					report.foundHit			= TRUE;
					break;
				};
				// Nearest Hit
				if (alpha<bestAlpha) {
					bestAlpha				= alpha;
					bestTriIndex			= i;
					bestPlane				= &(subMesh->triPlaneList[subMesh->triPlaneIndexList[bestTriIndex]]);
					report.foundIntersection= inters;
					report.foundHit			= TRUE;
				};
			};
		};
	};

	// irgendein Poly getroffen ?
	if (report.foundHit) {
		// polyNormal erwuenscht ?
		if (traceFlags & zTRACERAY_POLY_NORMAL) {
//			report.foundPolyNormal	= triPlaneList[triList[bestTriIndex].triPlane].normal;
			report.foundPolyNormal	= (*bestPlane).normal;
		};
	};

	return report.foundHit;
};

int zCProgMeshProto::GetNumTri () const 
{
	int numTri=0;
	for (int i=0; i<numSubMeshes; i++)
		numTri += subMeshList[i].triList.GetNum();
	return numTri;
};

// GetPolygon(), for debugging purposes only (too slow)
zCPolygon* zCProgMeshProto::GetPolygon(const int a_iIndex)
{
	static zCPolygon* dummyPoly = 0;
	if (!dummyPoly)
	{
		dummyPoly = zNEW(zCPolygon);
		dummyPoly->polyNumVert = 3;
		dummyPoly->vertex	 = zNEW(zCVertex*[3]);
		for (int i=0; i<3; i++) dummyPoly->vertex[i] = zNEW(zCVertex);
	}

	int numTri			= 0;
	int subMeshIndex	= a_iIndex;
	int subMeshNumTris	= 0;

	for (int i=0; i<numSubMeshes; i++)
	{
		subMeshNumTris	 = subMeshList[i].triList.GetNum();
		numTri			+= subMeshNumTris;
		subMeshIndex	-= subMeshNumTris;
		if (numTri>=a_iIndex+1) break;
	}

	for (int j=0; j<3; j++)
	{
		dummyPoly->vertex[j]->position = posList[subMeshList[i].wedgeList[subMeshList[i].triList[subMeshIndex].wedge[j]].position];
	}
	dummyPoly->polyPlane = subMeshList[i].triPlaneList[subMeshList[i].triPlaneIndexList[subMeshIndex]];

	return dummyPoly;
};

// GetMesh(), for debugging purposes only (too slow)
zCMesh* zCProgMeshProto::GetMesh(const int a_iLODIndex)
{
	zCMesh *mesh = zNEW(zCMesh);
	int numPoly  = 0;

	for (int n=0; n<numSubMeshes; n++) numPoly += subMeshList[n].triList.GetNum(); 

	zCMesh::S_InitVertexMergeCache(mesh);

	mesh->AllocPolys(numPoly);
	mesh->AllocVerts(numPoly*3);

	for (int i=0; i<numSubMeshes; i++)
	{
		for (int p=0; p<subMeshList[i].triList.GetNum(); p++)
		{
			zPOINT3 a,b,c;
			zVEC2	f,g,h;
			a	= posList[subMeshList[i].wedgeList[subMeshList[i].triList[p].wedge[0]].position];
			b	= posList[subMeshList[i].wedgeList[subMeshList[i].triList[p].wedge[1]].position];
			c	= posList[subMeshList[i].wedgeList[subMeshList[i].triList[p].wedge[2]].position];
			f	= subMeshList[i].wedgeList[subMeshList[i].triList[p].wedge[0]].texUV;
			g	= subMeshList[i].wedgeList[subMeshList[i].triList[p].wedge[1]].texUV;
			h	= subMeshList[i].wedgeList[subMeshList[i].triList[p].wedge[2]].texUV;
			zCPolygon *newPoly	  = mesh->AddPoly();
			newPoly->AddVertex( mesh->AddVertexSmart(a) );
			newPoly->AddVertex( mesh->AddVertexSmart(b) );
			newPoly->AddVertex( mesh->AddVertexSmart(c) );
			zERR_ASSERT(newPoly);
			newPoly->SetMapping(0,f);
			newPoly->SetMapping(1,g);
			newPoly->SetMapping(2,h);
			newPoly->SetPlane		(subMeshList[i].triPlaneList[subMeshList[i].triPlaneIndexList[p]]);
			newPoly->SetMaterial	(subMeshList[i].material);

		};
	}

	mesh->SetMeshName(this->GetObjectName());
	zCMesh::S_DeleteVertexMergeCache();
	//mesh->CalcBBox3D			();
	//mesh->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_MAT); 

	return mesh;
};



int		zCProgMeshProto::GetLowestLODNumPolys()
{
	int numPoly  = 0;
	for (int n=0; n<numSubMeshes; n++) numPoly += subMeshList[n].triList.GetNum(); 
	return numPoly;
};

zVEC3*	zCProgMeshProto::GetLowestLODPoly(const int a_iPoly, zVEC3* &normal)
{
	static zVEC3 s_vecLodTri[3];
	static zVEC3 s_defaultNormal(0,1,0);
	
	int numPoly = 0;

	// finde das richtige submesh
	for (int n=0; n<numSubMeshes; n++) 
	{
		if (numPoly+subMeshList[n].triList.GetNum()<a_iPoly)
		{
			numPoly+=subMeshList[n].triList.GetNum();
			continue;
		}
		else break;
	}

	// finde das richtige poly. (yes, you will fail to understand, so do i)
	int foundIndex  = a_iPoly-numPoly-1;
	if (foundIndex<0) foundIndex = 0;
	s_vecLodTri[0]	= posList[subMeshList[n].wedgeList[subMeshList[n].triList[foundIndex].wedge[0]].position];
	s_vecLodTri[1]	= posList[subMeshList[n].wedgeList[subMeshList[n].triList[foundIndex].wedge[1]].position];
	s_vecLodTri[2]	= posList[subMeshList[n].wedgeList[subMeshList[n].triList[foundIndex].wedge[2]].position];
	if (subMeshList[n].triPlaneList.GetNum()==0) normal = &s_defaultNormal;
	else normal			= &subMeshList[n].triPlaneList[subMeshList[n].triPlaneIndexList[foundIndex]].normal;

	return s_vecLodTri;
};



// =======================================================================================================================

void zCProgMeshProto::InitProgMeshProto()
{
	memset (&s_posCacheList		, 0, sizeof(s_posCacheList));
	memset (&s_wedgeRemap		, 0, sizeof(s_wedgeRemap));
	s_frameCtr=0;

	CreateDynamicVertexBuffer();

	// .ini auswerten
	const zBOOL	subdivEnabled				= zoptions->ReadBool ("ENGINE", "zSubdivSurfacesEnabled", FALSE);
	zCModel::S_SetSmoothRootNode( zoptions->ReadBool ("ENGINE", "zSmoothModelRootNode", zCModel::S_GetSmoothRootNode()) );

	zCProgMeshProto::SetAutoSubdivEnabled	(subdivEnabled);
};

zBOOL zCProgMeshProto::CreateDynamicVertexBuffer()
{
	// VertexBuffer
	{
/*		s_vertBufferColor 	= zrenderer->CreateVertexBuffer();
		s_vertBufferColor ->Create(	zVBUFFER_VERTFORMAT_XYZ		|
									zVBUFFER_VERTFORMAT_COLOR	|
									zVBUFFER_VERTFORMAT_TEXUV1,
									zPM_NUM_VBUFFER_VERT,
									0);
		s_vertBufferNormal	= zrenderer->CreateVertexBuffer();
		s_vertBufferNormal->Create(	zVBUFFER_VERTFORMAT_XYZ		|
									zVBUFFER_VERTFORMAT_NORMAL  |
									zVBUFFER_VERTFORMAT_TEXUV1,
									zPM_NUM_VBUFFER_VERT,
									0);
*/
		zDWORD vertFormat	= zVBUFFER_VERTFORMAT_XYZ		|
							  zVBUFFER_VERTFORMAT_NORMAL	|
							  zVBUFFER_VERTFORMAT_TEXUV1;

		s_vertBufferNormal= zNEW(zCVertexBufferDyn(vertFormat, zPM_NUM_VBUFFER_VERT));
		return TRUE;
	};
};

void zCProgMeshProto::CleanupProgMeshProto()
{
	s_frameCtr=0;

	if (zrenderer->HasCapability (zRND_CAP_TNL)) {
		{
			delete s_vertBufferColor;	s_vertBufferColor=0;
			delete s_vertBufferNormal;	s_vertBufferNormal=0;
		};
	};	
};

zREAL zCCFASTCALL zCProgMeshProto::CalcLODRenderVertPerc (const zTRenderContext& renderContext) 
{
	// berechnet prozentualen Anteil der zu rendernen Vertices anhand von Camera und Objekt Daten
	if (numSubMeshes<=0) return 0;

	// the projected radius of a sphere 
	// http://orca.cs.byu.edu/~cline/ideas/pradius.html

	zREAL fovx, fovy;
	zREAL sphereRadius	= bbox3D.GetMaxExtent();	// FIXME: precalc
	renderContext.cam->GetFOV (fovx, fovy);

	// lodStrength berechnen
	// 0.35 / 268 = 0.001306	(Referenzfall)
	zREAL lodStrength	= zREAL(lodParams.strength);
	if (s_lodParamStrengthOverride>=0)
		lodStrength		= s_lodParamStrengthOverride;
	// FIXME FIXME
	lodStrength			= zREAL(subMeshList[0].vertexUpdates.GetNum()) * zREAL(0.001306F) * lodStrength * s_lodParamStrengthModifier;
//	lodStrength			= zREAL(subMeshList[0].vertexUpdates.GetNum()) * zREAL(0.001306F) * lodStrength;	// * globaler LOD Slider
	// zREAL lodStrength= zREAL(vertexUpdates.GetNum()) * zREAL(0.001306F) * zREAL(lodParams.strength);		// * globaler LOD Slider

	if ((!renderContext.cam->GetVob()) || (!renderContext.vob)) return 1;
	zREAL distCam2		= (renderContext.cam->GetVob()->GetPositionWorld() - renderContext.vob->GetPositionWorld()).Length2();
	distCam2			-= lodParams.zDisplace2;
	zREAL dist			= (distCam2 - sphereRadius*sphereRadius);
	if ((dist<=0) || (lodStrength<=0))	return 4.0F;
	zREAL distInv		= Alg_SqrtInvApprox(dist);
	zREAL sphereProj	= (sphereRadius * zCCamera::activeCam->vpData.ydimFloat * distInv) / (lodStrength * fovy);

	// 4 = ausgefuellter Screen
	zREAL perc			= sphereProj / zREAL(4.0F);
//	if (perc>1.0F) return 1.0F;

	return perc;
};

zBOOL zCCFASTCALL zCProgMeshProto::CalcLODRenderArgs (const zTRenderContext& renderContext, zTLODRenderArgs &lodRenderArgs) 
{
	// berechnet: numPos, vertPerc

	zREAL actVertPerc		= CalcLODRenderVertPerc(renderContext);
	lodRenderArgs.vertPerc	= actVertPerc;
	if (actVertPerc>1.0F)	actVertPerc = 1.0F;

	// Wenn das Mesh ueberhaupt keine LOD-Repraesentation hat, muss hier natuerlich abgekuerzt werden
	// neu 1.15d: Lodding für Spieler deaktiviert
	if ((numSubMeshes<=0) || !HasLOD() || (renderContext.vob && renderContext.vob->GetCharacterClass() == zCVob::zVOB_CHAR_CLASS_PC)) 
	{
		lodRenderArgs.morphFrac				= 1.0F;
		if (numSubMeshes<=0) // ein leeres Mesh ? Robustheit..
		{
			lodRenderArgs.numPos				= 0;
			lodRenderArgs.numMinMorphPos		= 0;
			return FALSE;
		} else {
			lodRenderArgs.numPos				= posList.GetNum();	
			lodRenderArgs.numMinMorphPos		= lodRenderArgs.numPos;
			return TRUE;
		};
	};

	// numPos		: tatsaechliche Zahl Verts
	// maxVert		: morph, obere Grenze
	// minMorphVert	: morph, untere Grenze

	//
	const int numVertexUpdates	= subMeshList[0].vertexUpdates.GetNum();
	lodRenderArgs.numPos		= 0;										// wird hier bereits gesetzt, um auch bei early exits gueltig zu sein
	float	numPos				= actVertPerc * zREAL(numVertexUpdates-1);	// tatsaechliche Zahl Verts
	if (numPos<lodParams.minVerts) numPos=zREAL(lodParams.minVerts);
	if (numPos<3)				return FALSE;								// weniger als 3 Verts sind nicht mal ein Triangle => Objekt wird nicht mehr gerendert
	lodRenderArgs.numPos		= zFloat2Int(numPos);

	// Morph verts ?
	lodRenderArgs.morphFrac = 1.0F;
	if ((lodParams.morphPerc>0) && (DO_MORPH))
	{
		zREAL numMorphVert					= zREAL (numVertexUpdates) * lodParams.morphPerc;
		if (numMorphVert<1) {
			lodRenderArgs.numPos			= zFloat2Int(numPos);
			lodRenderArgs.numMinMorphPos	= lodRenderArgs.numPos;
		} else {
			zREAL numSection				= (zREAL (numVertexUpdates) / numMorphVert);
			lodRenderArgs.numPos			= zFloat2Int(numMorphVert * zCeil(numPos / zREAL (numVertexUpdates-1) * numSection));
			if (lodRenderArgs.numPos>=numVertexUpdates)	lodRenderArgs.numPos= numVertexUpdates-1;
			lodRenderArgs.numMinMorphPos	= zFloat2Int(lodRenderArgs.numPos - numMorphVert);
			lodRenderArgs.morphFrac			= ((numPos-lodRenderArgs.numMinMorphPos) / (lodRenderArgs.numPos-lodRenderArgs.numMinMorphPos));
			zClamp01						(lodRenderArgs.morphFrac);	// FIXME: .. lodRenderArgs.numPos ist leider manchmal kleiner als numPos => nicht kontinuierliche morphFracs
		};
	} else {
		lodRenderArgs.numPos			= zFloat2Int(numPos);
		lodRenderArgs.numMinMorphPos	= lodRenderArgs.numPos;
	};

	// Debug
	#ifdef zPM_SHOW_LOD_INFO
		screen->Print (0,1000, "%: "+zSTRING(float(lodRenderArgs.numPos) / float (subMeshList[0].vertexUpdates.GetNum()-1),2)+", v: "+zSTRING(lodRenderArgs.numPos));
	//	screen->Print (0,1250, "numMorphVert: "+zSTRING(numMorphVert,3)+", frac: "+zSTRING(minMorphVert)+", "+zSTRING(minMorphWedge)+"/"+zSTRING(maxVert)+"=>"+zSTRING((int)vertexUpdates.GetNum()));
	#endif

	return TRUE;
};



zBOOL zCCFASTCALL zCProgMeshProto::CalcLODRenderArgsMin(const zTRenderContext& renderContext, zTLODRenderArgs &lodRenderArgs) 
{
	// berechnet: numPos, vertPerc

#ifdef DEBUG_EFFECTS
	if (zinput)
	if (zinput->KeyPressed(KEY_LSHIFT) && zinput->KeyPressed(KEY_A))
	{
		zEFFECT_VERT_PERC-=0.1f;
		zERR_WARNING("C: effect perc: " + zSTRING(zEFFECT_VERT_PERC));
		zClamp01(zEFFECT_VERT_PERC);
	}
	else if (zinput->KeyPressed(KEY_LSHIFT) && zinput->KeyPressed(KEY_S))
	{
		zEFFECT_VERT_PERC+=0.1f;
		zERR_WARNING("C: effect perc: " + zSTRING(zEFFECT_VERT_PERC));
		zClamp01(zEFFECT_VERT_PERC);
	}
#endif

	zREAL actVertPerc		= zEFFECT_VERT_PERC;
	lodRenderArgs.vertPerc	= actVertPerc;
	

	// Wenn das Mesh ueberhaupt keine LOD-Repraesentation hat, muss hier natuerlich abgekuerzt werden
	// neu 1.15d: Lodding für Spieler deaktiviert
	if ((numSubMeshes<=0) || !HasLOD()) 
	{
		lodRenderArgs.morphFrac				= 1.0F;
		if (numSubMeshes<=0) // ein leeres Mesh ? Robustheit..
		{
			lodRenderArgs.numPos				= 0;
			lodRenderArgs.numMinMorphPos		= 0;
			return FALSE;
		} else {
			lodRenderArgs.numPos				= posList.GetNum();	
			lodRenderArgs.numMinMorphPos		= lodRenderArgs.numPos;
			return TRUE;
		};
	};

	// numPos		: tatsaechliche Zahl Verts
	// maxVert		: morph, obere Grenze
	// minMorphVert	: morph, untere Grenze

	//
	const int numVertexUpdates	= subMeshList[0].vertexUpdates.GetNum();
	lodRenderArgs.numPos		= 0;										// wird hier bereits gesetzt, um auch bei early exits gueltig zu sein
	float	numPos				= actVertPerc * zREAL(numVertexUpdates-1);	// tatsaechliche Zahl Verts
	if (numPos<lodParams.minVerts) numPos=zREAL(lodParams.minVerts);
	if (numPos<3)				return FALSE;								// weniger als 3 Verts sind nicht mal ein Triangle => Objekt wird nicht mehr gerendert
	lodRenderArgs.numPos		= zFloat2Int(numPos);

	// Morph verts ?
	lodRenderArgs.morphFrac = 1.0F;

	// FIXME: obsolete ???
	if ((lodParams.morphPerc>0) && (DO_MORPH))
	{
		zREAL numMorphVert					= zREAL (numVertexUpdates) * lodParams.morphPerc;
		if (numMorphVert<1) {
			lodRenderArgs.numPos			= zFloat2Int(numPos);
			lodRenderArgs.numMinMorphPos	= lodRenderArgs.numPos;
		} else {
			zREAL numSection				= (zREAL (numVertexUpdates) / numMorphVert);
			lodRenderArgs.numPos			= zFloat2Int(numMorphVert * zCeil(numPos / zREAL (numVertexUpdates-1) * numSection));
			if (lodRenderArgs.numPos>=numVertexUpdates)	lodRenderArgs.numPos= numVertexUpdates-1;
			lodRenderArgs.numMinMorphPos	= zFloat2Int(lodRenderArgs.numPos - numMorphVert);
			lodRenderArgs.morphFrac			= ((numPos-lodRenderArgs.numMinMorphPos) / (lodRenderArgs.numPos-lodRenderArgs.numMinMorphPos));
			zClamp01						(lodRenderArgs.morphFrac);	// FIXME: .. lodRenderArgs.numPos ist leider manchmal kleiner als numPos => nicht kontinuierliche morphFracs
		};
	} else {
		lodRenderArgs.numPos			= zFloat2Int(numPos);
		lodRenderArgs.numMinMorphPos	= lodRenderArgs.numPos;
	};

	return TRUE;
};


zBOOL zCCFASTCALL zCProgMeshProto::CalcLODRenderArgsSubMesh (
												 const zTRenderContext				&renderContext, 
												 const zTLODRenderArgs				&lodRenderArgs, 
												 const zCProgMeshProto::zCSubMesh	*subMesh,
												 zTLODRenderArgsSubMesh				&lodRenderArgsSub) 
{
	// berechnet Werte fuer das Geomorphing: groesster Vertex, kleinster Vertex, Gewichtung beider

	// Wenn das Mesh ueberhaupt keine LOD-Repraesentation hat, muss hier natuerlich abgekuerzt werden
	if (!HasLOD()) {
		if (subMesh->vertexUpdates.GetNum()<=0) // ein leeres Mesh ? Robustheit..
		{
			lodRenderArgsSub.numTri				= 0;
			lodRenderArgsSub.numWedge			= 0;
			return FALSE;
		} else {
			lodRenderArgsSub.numTri				= subMesh->vertexUpdates[0].numNewTri;
			lodRenderArgsSub.numWedge			= subMesh->vertexUpdates[0].numNewWedge;
			lodRenderArgsSub.numMinMorphWedge	= lodRenderArgsSub.numWedge;
			return TRUE;
		};
	};

	//
	lodRenderArgsSub.numTri				= subMesh->vertexUpdates[lodRenderArgs.numPos].numNewTri;
	lodRenderArgsSub.numWedge			= subMesh->vertexUpdates[lodRenderArgs.numPos].numNewWedge;
	lodRenderArgsSub.numMinMorphWedge	= subMesh->vertexUpdates[lodRenderArgs.numMinMorphPos].numNewWedge;

	// Debug
	#ifdef zPM_SHOW_LOD_INFO
//		screen->Print (0,1000, "%: "+zSTRING(float(lodRenderArgs.numPos) / float (subMesh->vertexUpdates.GetNum()-1),2)+", v: "+zSTRING(lodRenderArgs.numPos)+", t: "+zSTRING(lodRenderArgsSub.numTri));
	//	screen->Print (0,1250, "numMorphVert: "+zSTRING(numMorphVert,3)+", frac: "+zSTRING(minMorphVert)+", "+zSTRING(minMorphWedge)+"/"+zSTRING(maxVert)+"=>"+zSTRING((int)vertexUpdates.GetNum()));
	#endif

	return TRUE;
};

zBOOL zCProgMeshProto::Render (zTRenderContext& renderContext) 
{
	if (renderContext.m_AniMode == zVISUAL_ANIMODE_NONE) 
	{
		return RenderProgMesh (renderContext, 0);
	}
	else 
	{
		// soll wohl irgendwie animiert werden, mal schauen wie
		switch (renderContext.m_AniMode)
		{
			case zVISUAL_ANIMODE_WIND:
			case zVISUAL_ANIMODE_WIND2:
			// s'ist wind: weitere optimierungen:
			// T&L wenn zu weit weg (im Moment, wenn Vob weiter als die Hälfte der FarClipZ Plane
			// entfernt ist. Besser wäre es aber, noch die Grösse der BBox zu berücksichtigen (siehe
			// CalcRenderAlpha()
			// T&L wenn INDOOR
			    
				zCSkyControler_Outdoor* skyOut = zDYNAMIC_CAST<zCSkyControler_Outdoor>(zCSkyControler::GetActiveSkyControler());

				if ( ( skyOut																) && 
					 ( renderContext.m_aniModeStrength != 0									) &&
					 ( skyOut->GetGlobalWindVec(s_morphVec,renderContext.m_AniMode)			)
					)
				{
					// FIXME: precalc, optimieren & verlegen

					const zREAL fadeOutMorphMaxDist= zMin (lodFarDistance, zMin(renderContext.world->GetVobFarClipZ(), zCCamera::activeCam->GetFarClipZ()) )*0.65f;
					const zREAL fadeOutMorphMinDist= fadeOutMorphMaxDist * 0.6F;
					
					s_morphWeight = renderContext.m_aniModeStrength;
					if (s_morphWeight>5)	 s_morphWeight = 5;
					if (s_morphWeight>0  && s_morphWeight<0.1f)  s_morphWeight = 0.1f;

					if ( renderContext.distVobToCam<fadeOutMorphMinDist )  s_morphWeight = 1; else
					if ( renderContext.distVobToCam>fadeOutMorphMaxDist )  s_morphWeight = 0; 
					else
					{					
						float fac = 1-zSinusEase((renderContext.distVobToCam-fadeOutMorphMinDist)/(fadeOutMorphMaxDist-fadeOutMorphMinDist));
						zClamp01(fac);
						s_morphWeight *= fac;
					}


					if (s_morphWeight == 0) break;

					s_morphMode = renderContext.m_AniMode;
					return RenderProgMesh	(renderContext, zPM_RENDER_FLAG_PACK_DYNAMIC_VB | zPM_RENDER_FLAG_SW_TRAFO_VERTS | zPM_RENDER_FLAG_MORPH);
				}
			break;
		}
	}
	return RenderProgMesh (renderContext, 0);
	//
};

zBOOL zCCFASTCALL zCProgMeshProto::RenderProgMesh (	
										zTRenderContext&				renderContext, 
										int								renderFlags, 
										zTLODRenderArgs					*lodRenderArgs, 
										zCRenderLightContainer			*renderLightCont,
										zREAL							fatness,
										zREAL							scale) 
{ 
	//
//	zERR_ASSERT (wedgeList.GetNum()	<NUM_WEDGE_CACHE);
	zERR_ASSERT (posList.GetNum()	<NUM_POS_CACHE);
	if (posList.GetNum()>=NUM_POS_CACHE) return FALSE;

	//
	s_frameCtr++;

	// LOD Argumente 
	zTLODRenderArgs		localLodRenderArgs;
	if (!lodRenderArgs) 
	{
		lodRenderArgs		= &localLodRenderArgs;
		CalcLODRenderArgs	(renderContext, *lodRenderArgs);
	};
	if (lodRenderArgs->numPos<3) return FALSE;

	// Beleuchtung vorbereiten
	// ScalePrelit oder Exact ?
	zCRenderLightContainer	localRenderLightCont; 

	if (!renderLightCont)
	{
		const zBOOL	doPrelight		= (lightingMode==zPM_LIGHTING_MODE_PRELIT) || 
									  (lodRenderArgs->vertPerc<zPM_PRELIT_EXACT_THRESH);

		localRenderLightCont.SetDoPrelight		(doPrelight);

		{
			localRenderLightCont.CollectLights	(renderContext);
			localRenderLightCont.Activate		(renderContext.cam->GetTransform(zCAM_TRAFO_VIEW));
		};
		renderLightCont		= &localRenderLightCont;
	};

/*	if (!renderLightCont)
	{
		// Prelight einschalten?		(=> falls weit weg, oder generell Beleuchtung auf 'cheap' gesetzt)
		// 3500.0F (distance CM) / 380435.0F (Volumen cm^3) = 0.00394285F
		const zREAL maxExtend		= zMax(120.0f, bbox3D.GetMaxExtent());
		const zREAL factor			= zREAL(0.0014f) * maxExtend * maxExtend * maxExtend;
		const zBOOL	doPrelight		= (lightingMode==zPM_LIGHTING_MODE_PRELIT) || 									  
									  ((renderContext.distVobToCam>factor));// && (lodRenderArgs->vertPerc<zPM_PRELIT_EXACT_THRESH));

//		const zBOOL	doPrelight		= (lightingMode==zPM_LIGHTING_MODE_PRELIT) || (lodRenderArgs->vertPerc<zPM_PRELIT_EXACT_THRESH);


		localRenderLightCont.SetDoPrelight	(doPrelight);
		localRenderLightCont.SetPreLightDist(factor);

		{
			localRenderLightCont.CollectLights	(renderContext);
			localRenderLightCont.Activate		(renderContext.cam->GetTransform(zCAM_TRAFO_VIEW));
		};
		renderLightCont		= &localRenderLightCont;
	};*/

	/*
	Pipeline:
	- fa pos: trafo (OS => CS)		(shared)
	- fa tris:
		- fa verts:	morph, pack		(share?)
		- clip
		- fa pos: proj				(shared)
		- cull2D
		- fa vert: light			(share!)	(pack into vertBuffer)
		- render tri
	*/

	#ifdef zPM_DRAW_OBB
		if (renderContext.distVobToCam<2000.0F)
			obbox3D.Draw (10);  
	#endif

	// Debug Einstellung Materialien durch Farbcodes ersetzen?
	static zCArray<zCTexture*> texColorList;
	if (GetMarkMeshMaterials())
	{
		if (texColorList.GetNum()<=0)
		{
			zCTexture *tex;
			tex	= zCTexture::Load (zSTRING("RED.TGA"));		texColorList.Insert (tex);
			tex	= zCTexture::Load (zSTRING("BLUE.TGA"));	texColorList.Insert (tex);
			tex	= zCTexture::Load (zSTRING("GREEN.TGA"));	texColorList.Insert (tex);
			tex	= zCTexture::Load (zSTRING("YELLOW.TGA"));	texColorList.Insert (tex);
			tex	= zCTexture::Load (zSTRING("WHITE.TGA"));	texColorList.Insert (tex);
			tex	= zCTexture::Load (zSTRING("BROWN.TGA"));	texColorList.Insert (tex);
			tex	= zCTexture::Load (zSTRING("BLACK.TGA"));	texColorList.Insert (tex);
			// FIXME: debug leaks..
		};
		for (int i=0; i<numSubMeshes; i++)
		{
			if (i>=texColorList.GetNum())	break;
			zSwap (subMeshList[i].material->texture, texColorList[i]);
		};
	};

	// Falls dieses Mesh gerade komplett Alpha-gefadet ist, werden die SubMeshes immer in
	// derselben Reihenfolge (0..n) gerendert, um ein 'Flackern' zu verhindern.
	if (zrenderMan.GetOverrideAlpha()<zREAL(1.0F))
	{
		s_subMeshRenderDir	= +1;
	};
	//
	zBOOL res;
	if (renderFlags & zPM_RENDER_FLAG_PACK_DYNAMIC_VB)
	{
		if ((GetAutoSubdivEnabled()) && (lodRenderArgs->vertPerc>=1) && (HasSubdivData()))
		{
			res	= RenderDynamicSubdiv	(renderContext, renderFlags, lodRenderArgs, renderLightCont, fatness, scale);
		} else 
		{
			res	= RenderDynamicLOD		(renderContext, renderFlags, lodRenderArgs, renderLightCont, fatness, scale);
		};
	} else if (HasLOD())
	{
		res	= RenderStaticLOD			(renderContext, renderFlags, lodRenderArgs, renderLightCont);
	} else 
	{
		res	= RenderStatic				(renderContext, renderFlags, lodRenderArgs, renderLightCont);
	};

	//
	//RenderStaticLODShadow (renderContext, renderFlags, lodRenderArgs, renderLightCont);


	// Debug Einstellung Materialien durch Farbcodes ersetzen?
	if (GetMarkMeshMaterials())
	{
		for (int i=0; i<numSubMeshes; i++)
		{
			if (i>=texColorList.GetNum())	break;
			zSwap (subMeshList[i].material->texture, texColorList[i]);
		};
	};
	return res;
}; 

// =======================================================================================================================

zBOOL zCCFASTCALL zCProgMeshProto::RenderStatic		(	
											zTRenderContext&		renderContext, 
											int						renderFlags, 
											zTLODRenderArgs			*lodRenderArgs, 
											zCRenderLightContainer	*renderLightCont
										)
{
	// Fall A):		TLC, static mesh, static VB

	if (!(renderFlags & zPM_RENDER_FLAG_DONT_SET_TRANSFROM))
	{
		zCCamera::activeCam->PushTransform	(zCAM_TRAFO_WORLDVIEW);
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, renderContext.vob->trafoObjToWorld);
	};

	// Lights aktivieren
	renderLightCont->SetupRendererLights();

	// TEMP
	if (this->vertexBufferStatic==0)			PackStaticVertexBuffers					();
	if (this->vertexBufferStatic->IsLocked())	zvertexBufferMan.UnlockOpenVertexBuffers();


	// hat kein LOD
	s_subMeshRenderDir	= -s_subMeshRenderDir;
	int subMeshIndex	= (s_subMeshRenderDir==1) ? 0 : numSubMeshes-1;
	int count			= numSubMeshes;

	zBOOL sectorVob		= renderContext.vob->GetGroundPoly() ? renderContext.vob->GetGroundPoly()->GetSectorFlag() : FALSE;

	if (count>0)
	do
	{
		zCSubMesh *subMesh					= &(subMeshList[subMeshIndex]);
		subMeshIndex						+= s_subMeshRenderDir;


		if (!subMesh->material->GetEnvMapEnabled())
		{
			zrenderMan.DrawVertexBuffer			(vertexBufferStatic, 
												 subMesh->vbStartIndex, 
												 subMesh->wedgeList.GetNum(),
												 (zWORD*)subMesh->triList.GetArray(),
												 subMesh->triList.GetNum()*3,
												 subMesh->material, sectorVob);
		}
		else
		{
			const zREAL envMapStrengthBak = subMesh->material->GetEnvMapStrength();
			const float ONE_OVER_255	  = 1.0f/255.0f;
			if (envMapStrengthBak>0)
			subMesh->material->SetEnvMapStrength( envMapStrengthBak * renderContext.vob->CalcLightSampleAtOrigin().GetIntensityFloat()*ONE_OVER_255 );

			zrenderMan.DrawVertexBuffer			(vertexBufferStatic, 
												 subMesh->vbStartIndex, 
												 subMesh->wedgeList.GetNum(),
												 (zWORD*)subMesh->triList.GetArray(),
												 subMesh->triList.GetNum()*3,
												 subMesh->material, sectorVob	);
			subMesh->material->SetEnvMapStrength( envMapStrengthBak );

		}
	} while(--count);

	if (!(renderFlags & zPM_RENDER_FLAG_DONT_SET_TRANSFROM))
		zCCamera::activeCam->PopTransform	(zCAM_TRAFO_WORLDVIEW);
	return TRUE;
};

// =======================================================================================================================

zBOOL zCCFASTCALL zCProgMeshProto::RenderStaticLOD	(	
											zTRenderContext&		renderContext, 
											int						renderFlags, 
											zTLODRenderArgs			*lodRenderArgs, 
											zCRenderLightContainer	*renderLightCont
										)
{
	// Fall B):		TLC, prog mesh, static VB

	// Findet keine Reduktion statt, weil Objekt zu nahe => schnelleren Pfad benutzen
	if (lodRenderArgs->vertPerc>=1)
		return RenderStatic(renderContext, renderFlags, lodRenderArgs, renderLightCont);

	if (!(renderFlags & zPM_RENDER_FLAG_DONT_SET_TRANSFROM))
	{
		zCCamera::activeCam->PushTransform	(zCAM_TRAFO_WORLDVIEW);
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, renderContext.vob->trafoObjToWorld);
	};	

	// Lights aktivieren
	renderLightCont->SetupRendererLights();

	// TEMP
	if (this->vertexBufferStatic==0)			PackStaticVertexBuffers					();
	if (this->vertexBufferStatic->IsLocked())	zvertexBufferMan.UnlockOpenVertexBuffers();

	// hat LOD
	zTLODRenderArgsSubMesh	lodRenderArgsSub;
	s_subMeshRenderDir	= -s_subMeshRenderDir;
	int subMeshIndex	= (s_subMeshRenderDir==1) ? 0 : numSubMeshes-1;
	int count			= numSubMeshes;
	
	zBOOL sectorVob		= renderContext.vob->GetGroundPoly() ? renderContext.vob->GetGroundPoly()->GetSectorFlag() : FALSE;

	if (count>0)
	do
	{
		zCSubMesh *subMesh				= &(subMeshList[subMeshIndex]);
		subMeshIndex					+= s_subMeshRenderDir;
		CalcLODRenderArgsSubMesh		(renderContext, *lodRenderArgs, subMesh, lodRenderArgsSub);
		if (lodRenderArgsSub.numTri<=0)	continue;

		// wedgeRemap Liste erstellen (damit sie spaeter geshared werden kann)
		{
			// a) der unmodifizierte Teil
			for (int j=0; j<lodRenderArgsSub.numWedge; j++) {
				s_wedgeRemap[j]	= j;
			};
			// b) der modifizierte Teil
			for (j=lodRenderArgsSub.numWedge; j<subMesh->wedgeList.GetNum(); j++) {
				int wedgeIndex = j;
				while (wedgeIndex>=lodRenderArgsSub.numWedge) {
					zERR_ASSERT (subMesh->wedgeMap[wedgeIndex]!=zPMINDEX_NONE);
					wedgeIndex = subMesh->wedgeMap[wedgeIndex];
				};
				s_wedgeRemap[j]	= wedgeIndex;
			};
		};
		int numIndizes=0;
		{
			// remaped IndexList erstellen
			s_workIndexList.EmptyList();
			s_workIndexList.AllocAbs (lodRenderArgsSub.numTri*3);	s_workIndexList.MarkNumAllocUsed();
			for (int j=0; j<lodRenderArgsSub.numTri; j++)
			{
				s_workIndexList[numIndizes++]	= s_wedgeRemap[subMesh->triList[j].wedge[0]];
				s_workIndexList[numIndizes++]	= s_wedgeRemap[subMesh->triList[j].wedge[1]];
				s_workIndexList[numIndizes++]	= s_wedgeRemap[subMesh->triList[j].wedge[2]];
			};
		};

		if (!subMesh->material->GetEnvMapEnabled())
		{
			zrenderMan.DrawVertexBuffer			(vertexBufferStatic, 
												 subMesh->vbStartIndex, 
												 lodRenderArgsSub.numWedge,
												 s_workIndexList.GetArray(),
												 numIndizes,
												 subMesh->material, sectorVob);
		}
		else
		{
			const zREAL envMapStrengthBak = subMesh->material->GetEnvMapStrength();
			const float ONE_OVER_255	  = 1.0f/255.0f;
			if (envMapStrengthBak>0)
			subMesh->material->SetEnvMapStrength( envMapStrengthBak * renderContext.vob->CalcLightSampleAtOrigin().GetIntensityFloat()*ONE_OVER_255 );
			zrenderMan.DrawVertexBuffer			(vertexBufferStatic, 
												 subMesh->vbStartIndex, 
												 lodRenderArgsSub.numWedge,
												 s_workIndexList.GetArray(),
												 numIndizes,
												 subMesh->material, sectorVob);
			subMesh->material->SetEnvMapStrength( envMapStrengthBak );
		}

	} while(--count);

	if (!(renderFlags & zPM_RENDER_FLAG_DONT_SET_TRANSFROM))
		zCCamera::activeCam->PopTransform	(zCAM_TRAFO_WORLDVIEW);
	return TRUE;
};

// =======================================================================================================================

void zCProgMeshProto::SoftwareTransformVerts (int renderFlags, zTLODRenderArgs *lodRenderArgs, zREAL fatness, zREAL scale)
{
	// alle positions transformieren 
	int i;
	zERR_ASSERT (lodRenderArgs->numPos>=0);

	zBOOL morph = (renderFlags & zPM_RENDER_FLAG_MORPH);
	if (!morph)
	{
		i=0;
		if (fatness!=0) {
			// Fatness
			// (andere Moeglichkeit: Wedge-Normals benutzen..)
			if (scale!=1) {
				do {
					s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (scale * (posList[i] + (fatness * posNormalList[i])));
					i++;
				} while (i<lodRenderArgs->numPos);
			} else {
				do {
					s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (posList[i] + (fatness * posNormalList[i]));
					i++;
				} while (i<lodRenderArgs->numPos);
			};
		} else {
			// keine Fatness
			if (scale!=1) {
				do {
					s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (scale * posList[i]);
					i++;
				} while (i<lodRenderArgs->numPos);
			} else {
				do {
					s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (posList[i]);
					i++;
				} while (i<lodRenderArgs->numPos);
			};
		};
	}
	else
	{
		if (s_morphMode == zVISUAL_ANIMODE_WIND)
		{
			#ifdef COUNT_MORPHED_VERTS
			s_morphedVerts+=lodRenderArgs->numPos;
			#endif

			const zREAL dy		= this->GetBBox3D().maxs[VY]-this->GetBBox3D().mins[VY];
			const zREAL yrangeInv = 1.0f/dy;
			const zVEC3 morphVec	= s_morphVec * s_morphWeight;

			i=0;
			zVEC3 newPos; 
			if (fatness!=0) {
				// Fatness
				// (andere Moeglichkeit: Wedge-Normals benutzen..)
				if (scale!=1) {
					do {
						newPos = posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * morphVec;
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (scale * (newPos + (fatness * posNormalList[i])));
						i++;
					} while (i<lodRenderArgs->numPos);
				} else {
					do {
						newPos = posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * (morphVec);
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (newPos + (fatness * posNormalList[i]));
						i++;
					} while (i<lodRenderArgs->numPos);
				};
			} else {
				// keine Fatness
				if (scale!=1) {
					do {
						newPos = posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * (morphVec);
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (scale * newPos);
						i++;
					} while (i<lodRenderArgs->numPos);
				} else {
					do {
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * (morphVec));
						i++;
					} while (i<lodRenderArgs->numPos);
				};
			};
		}
		else if (s_morphMode == zVISUAL_ANIMODE_WIND2)
		{

			#ifdef COUNT_MORPHED_VERTS
			s_morphedVerts+=lodRenderArgs->numPos;
			#endif

			zREAL xrangeInv = 1.0f/(this->GetBBox3D().maxs[VX]-this->GetBBox3D().mins[VX]);
			zREAL yrangeInv = 1.0f/(this->GetBBox3D().maxs[VY]-this->GetBBox3D().mins[VY]);
			zREAL zrangeInv = 1.0f/(this->GetBBox3D().maxs[VZ]-this->GetBBox3D().mins[VZ]);
			
			//s_morphWeight  *= 0.2f;
			zVEC3 morphVec	= s_morphVec * s_morphWeight;

			morphVec[VY]	= (morphVec[VX] + morphVec[VY]) * 0.4F;
			morphVec[VX]	*= 0.5f;
			morphVec[VZ]	*= 0.5f;

			i=0;
			zVEC3 newPos; 
			do {
				zREAL weight			= zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv))*(((posList[i][VX]-GetBBox3D().mins[VX]) * xrangeInv))*zSinusSlowStart(((posList[i][VZ]-GetBBox3D().mins[VZ]) * zrangeInv));
				s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (posList[i] + (weight * morphVec));
				i++;
			} while (i<lodRenderArgs->numPos);
			return;


			if (fatness!=0) {
				// Fatness
				// (andere Moeglichkeit: Wedge-Normals benutzen..)
				if (scale!=1) {
					do {
						newPos = posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * morphVec;
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (scale * (newPos + (fatness * posNormalList[i])));
						i++;
					} while (i<lodRenderArgs->numPos);
				} else {
					do {
						newPos = posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * (morphVec);
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (newPos + (fatness * posNormalList[i]));
						i++;
					} while (i<lodRenderArgs->numPos);
				};
			} else {
				// keine Fatness
				if (scale!=1) {
					do {
						newPos = posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * (morphVec);
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (scale * newPos);
						i++;
					} while (i<lodRenderArgs->numPos);
				} else {
					do {
						s_posCacheList[i]		= (zCCamera::activeCam->camMatrix) * (posList[i] + zSinusSlowStart(((posList[i][VY]-GetBBox3D().mins[VY]) * yrangeInv)) * (morphVec));
						i++;
					} while (i<lodRenderArgs->numPos);
				};
			};
		}
	}
	
};

zBOOL zCCFASTCALL zCProgMeshProto::RenderDynamicLOD	(	
											zTRenderContext&		renderContext, 
											int						renderFlags, 
											zTLODRenderArgs			*lodRenderArgs, 
											zCRenderLightContainer	*renderLightCont,
											zREAL					fatness, 
											zREAL					scale
										)
{

	#define PACK_VERTEX( pos3, normal, texUV ) \
		*((zPOINT3*)(vbBasePtr + vbOffsetXYZ))		= pos3; \
		*((zVEC3 * )(vbBasePtr + vbOffsetNormal))	= normal; \
		*((zVEC2*  )(vbBasePtr + vbOffsetTexUV0))	= texUV;	vbBasePtr += vbStride;

	// Fall C):		 LC, prog mesh, softSkin, dyn VB

	// ASSERT: Transforms sind bereits vorher gesetzt worden
	if (renderFlags & zPM_RENDER_FLAG_SW_TRAFO_VERTS)
		SoftwareTransformVerts (renderFlags, lodRenderArgs, fatness, scale);

	//
	zCCamera::activeCam->PushTransform	(zCAM_TRAFO_WORLDVIEW);
	zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLDVIEW, zMAT4::GetIdentity());

	// Lights aktivieren
	renderLightCont->SetupRendererLights();

	// Pro Material wird ein VB gefuellt
	// Die Art der VB haengt davon ab, ob korrekte oder schnelle Prelight Beleuchtung gemacht werden soll
	zCVertexBuffer		*vertexBuffer		= 0;
	zCVertexBufferDyn	*vertexBufferDyn	= 0;
	zBYTE				*vbBasePtr			= 0;
	zDWORD				vbOffsetXYZ			= 0;
	zDWORD				vbOffsetNormal		= 0;
	zDWORD				vbOffsetTexUV0		= 0;
	zDWORD				vbStride			= 0;

//	if (renderLightCont->GetDoPrelight())	vertexBuffer= s_vertBufferColor;
//	else									vertexBuffer= s_vertBufferNormal;
	vertexBufferDyn					= s_vertBufferNormal;
	vertexBuffer					= vertexBufferDyn->GetVertexBuffer();;
	vertexBuffer->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);

	//
	zTLODRenderArgsSubMesh	lodRenderArgsSub;
	zVEC3					normalCS;
	s_subMeshRenderDir	= -s_subMeshRenderDir;
	int subMeshIndex	= (s_subMeshRenderDir==1) ? 0 : numSubMeshes-1;
	int count			= numSubMeshes;
	zBOOL sectorVob		= renderContext.vob->GetGroundPoly() ? renderContext.vob->GetGroundPoly()->GetSectorFlag() : FALSE;
	if (count>0)
	do
	{
		const zCSubMesh* const subMesh	= &(subMeshList[subMeshIndex]);
		subMeshIndex					+= s_subMeshRenderDir;
		CalcLODRenderArgsSubMesh		(renderContext, *lodRenderArgs, subMesh, lodRenderArgsSub);
		if (lodRenderArgsSub.numTri<=0)	continue;

		// wedgeRemap Liste erstellen (damit sie spaeter geshared werden kann)
		{
			// a) der unmodifizierte Teil
			for (int j=0; j<lodRenderArgsSub.numWedge; j++) {
				s_wedgeRemap[j]	= j;
			};
			// b) der modifizierte Teil
			for (j=lodRenderArgsSub.numWedge; j<subMesh->wedgeList.GetNum(); j++) {
				int wedgeIndex = j;
				while (wedgeIndex>=lodRenderArgsSub.numWedge) {
					zERR_ASSERT (subMesh->wedgeMap[wedgeIndex]!=zPMINDEX_NONE);
					wedgeIndex = subMesh->wedgeMap[wedgeIndex];
				};
				s_wedgeRemap[j]	= wedgeIndex;
			};
		};

		// IndexList erstellen
		s_workIndexList.EmptyList		();		
		s_workIndexList.AllocAbs		(lodRenderArgsSub.numTri*3);
		s_workIndexList.MarkNumAllocUsed();
		int numIndizes=0;
		for (int j=0; j<lodRenderArgsSub.numTri; j++)
		{
			s_workIndexList[numIndizes++] = (s_wedgeRemap[subMesh->triList[j].wedge[0]]);
			s_workIndexList[numIndizes++] = (s_wedgeRemap[subMesh->triList[j].wedge[1]]);
			s_workIndexList[numIndizes++] = (s_wedgeRemap[subMesh->triList[j].wedge[2]]);
		};

		// VB klarmachen: lock
		zDWORD startVertexIndex;
		if (!vertexBufferDyn->Lock		(lodRenderArgsSub.numWedge, startVertexIndex))
		{
			zERR_WARNING ( "C: zCProgMeshProto::RenderDynamicLOD()	- vertex buffer lock failed." );
			zCCamera::activeCam->PopTransform	(zCAM_TRAFO_WORLDVIEW);
			return FALSE;
		};
		zDWORD currentVertIndex		= startVertexIndex; 

		// Verts in den Buffer packen
		// der fixe Anteil

		vbStride			= vertexBuffer->arrayStride;
		vbBasePtr			= vertexBuffer->array.basePtr + (vertexBuffer->arrayStride * startVertexIndex);
		vbOffsetXYZ			= zDWORD((zBYTE*)vertexBuffer->array.XYZPtr		- (zBYTE*)vertexBuffer->array.basePtr);
		vbOffsetNormal		= zDWORD((zBYTE*)vertexBuffer->array.normalPtr  - (zBYTE*)vertexBuffer->array.basePtr);
		vbOffsetTexUV0		= zDWORD((zBYTE*)vertexBuffer->array.texUV0Ptr	- (zBYTE*)vertexBuffer->array.basePtr);

		for (j=0; j<lodRenderArgsSub.numMinMorphWedge; j++, currentVertIndex++)
		{
			// CRASH in folgender Zeile, DEFECT 3422
			PACK_VERTEX( s_posCacheList[subMesh->wedgeList[j].position], renderLightCont->GetTrafoObjToCam().Rotate (subMesh->wedgeList[j].normal), subMesh->wedgeList[j].texUV)
		};

		// der gemorphte Anteil
		for (; j<lodRenderArgsSub.numWedge; j++, currentVertIndex++)
		{
			int destIndex = j;
			while (destIndex>=lodRenderArgsSub.numMinMorphWedge) {
				if (subMesh->wedgeMap[destIndex]==zPMINDEX_NONE)		break;
				destIndex = subMesh->wedgeMap[destIndex];
			};
 			
			// Das lerpen macht man hier fuer jede Wedge (nicht mehr pro Wedge, pro Tri). Optimaler Fall.
			const zTPMWedge&	wedge1		= subMesh->wedgeList[j];
			const zTPMWedge&	wedge0		= subMesh->wedgeList[destIndex];
			PACK_VERTEX( zLerp (lodRenderArgs->morphFrac, s_posCacheList[wedge0.position], s_posCacheList[wedge1.position]), 
						renderLightCont->GetTrafoObjToCam().Rotate (zLerp (lodRenderArgs->morphFrac, wedge0.normal  , wedge1.normal)),
						zLerp (lodRenderArgs->morphFrac, wedge0.texUV	, wedge1.texUV)
					   )
		};

		// VB unlocken und rendern
		vertexBufferDyn->Unlock			();

		if (!subMesh->material->GetEnvMapEnabled())
		{
			zrenderMan.DrawVertexBuffer		(vertexBuffer, 
											 startVertexIndex, 
											 lodRenderArgsSub.numWedge,
											 s_workIndexList.GetArray(),
											 numIndizes,
											 subMesh->material, sectorVob);
		}
		else
		{
			const zREAL envMapStrengthBak = subMesh->material->GetEnvMapStrength();
			const float ONE_OVER_255	  = 1.0f/255.0f;
			if (envMapStrengthBak>0)
			subMesh->material->SetEnvMapStrength( envMapStrengthBak * renderContext.vob->CalcLightSampleAtOrigin().GetIntensityFloat()*ONE_OVER_255 );
			
			zrenderMan.DrawVertexBuffer		(vertexBuffer, 
											 startVertexIndex, 
											 lodRenderArgsSub.numWedge,
											 s_workIndexList.GetArray(),
											 numIndizes,
											 subMesh->material, sectorVob);

			subMesh->material->SetEnvMapStrength( envMapStrengthBak );
		}

	} while(--count);

	zCCamera::activeCam->PopTransform	(zCAM_TRAFO_WORLDVIEW);
	return TRUE;
};

// =======================================================================================================================

void zCCFASTCALL zCProgMeshProto::CalcSubdiv (int renderFlags, const zTLODRenderArgs *lodRenderArgs)
{
	int i=0;
	do {
		s_posNormalCSList[i] = (zCCamera::activeCam->camMatrix).Rotate (posNormalList[i]);
		i++;
	} while (i<lodRenderArgs->numPos);
};

void zCCFASTCALL zCProgMeshProto::CalcNumSubdivEdges(
										 zCSubMesh				*subMesh,			// in
										 const zTLODRenderArgs	*lodRenderArgs, 
										 zTLODRenderArgsSubMesh &lodRenderArgsSub)	// out
{
//	lodRenderArgsSub.numSubdivEdges	= subMesh->edgeList.GetNum();
//	lodRenderArgsSub.numSubdivEdges	= subMesh->edgeList.GetNum() / 2;
	zREAL fac						= lodRenderArgs->vertPerc * 0.25F;
	zClamp01						(fac);
	lodRenderArgsSub.numSubdivEdges	= zFloat2Int(zREAL(subMesh->edgeList.GetNum()) * fac);
};

void zCCFASTCALL zCProgMeshProto::CalcSubdivSubMesh (
										 zCSubMesh				*subMesh,			// in
										 zCVertexBuffer			*vertexBuffer,
										 const zTLODRenderArgs	*lodRenderArgs, 
										 zCRenderLightContainer	*renderLightCont,
										 zTLODRenderArgsSubMesh &lodRenderArgsSub)	// out
{
	// Neue Verts auf den SubDiv Edges berechnen und in den VB packen
	int currentVertIndex			= lodRenderArgsSub.numWedge;

	for (int i=0; i<lodRenderArgsSub.numSubdivEdges; i++)
	{
		// FIXME: das Packen geht noch schneller.. (VB Ptr direkt benutzen)
		const int wedgeIndex0		= subMesh->edgeList[i].wedge[0];
		const int wedgeIndex1		= subMesh->edgeList[i].wedge[1];
		const int posIndex0			= subMesh->wedgeList[wedgeIndex0].position;
		const int posIndex1			= subMesh->wedgeList[wedgeIndex1].position;

		zVEC3 pos					= zLerp (0.5F, s_posCacheList[posIndex0]		 , s_posCacheList[posIndex1]);
		zVEC2 texUV					= zLerp (0.5F, subMesh->wedgeList[wedgeIndex0].texUV , subMesh->wedgeList[wedgeIndex1].texUV);
		zVEC3 normal				= zLerp (0.5F, subMesh->wedgeList[wedgeIndex0].normal, subMesh->wedgeList[wedgeIndex1].normal);
		zVEC3 normalMove			= zLerp (0.5F, s_posNormalCSList[posIndex0]			 , s_posNormalCSList[posIndex1]);
//		normal.Normalize			();
		pos							+= subMesh->edgeScoreList[i] * normalMove;

		vertexBuffer->SetXYZ		(currentVertIndex, pos);
		normal						= renderLightCont->GetTrafoObjToCam().Rotate (normal);	// normalCS
		vertexBuffer->SetNormal		(currentVertIndex, normal);
		vertexBuffer->SetTexUV0		(currentVertIndex, texUV);
		currentVertIndex++;
	};
};

zBOOL zCCFASTCALL zCProgMeshProto::RenderDynamicSubdiv(	
											zTRenderContext&		renderContext, 
											int						renderFlags, 
											zTLODRenderArgs			*lodRenderArgs, 
											zCRenderLightContainer	*renderLightCont,
											zREAL					fatness, 
											zREAL					scale
										)
{
	// Fall D):		 LC, prog mesh, softSkin, dyn VB

	// ASSERT: Transforms sind bereits vorher gesetzt worden
	if (renderFlags & zPM_RENDER_FLAG_SW_TRAFO_VERTS)
	{
		SoftwareTransformVerts (renderFlags, lodRenderArgs, fatness, scale);

		// SubDiv Params berechnen, NACH den Vert-Trafos !
		CalcSubdiv (renderFlags, lodRenderArgs);
	};

	//
	zCCamera::activeCam->PushTransform	(zCAM_TRAFO_WORLDVIEW);
	zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLDVIEW, zMAT4::GetIdentity());

	// Lights aktivieren
	renderLightCont->SetupRendererLights();

	// Pro Material wird ein VB gefuellt
	// Die Art der VB haengt davon ab, ob korrekte oder schnelle Prelight Beleuchtung gemacht werden soll
	zCVertexBuffer		*vertexBuffer	= 0;
	zCVertexBufferDyn	*vertexBufferDyn= 0;
//	if (renderLightCont->GetDoPrelight())	vertexBuffer= s_vertBufferColor;
//	else									vertexBuffer= s_vertBufferNormal;
	vertexBufferDyn					= s_vertBufferNormal;
	vertexBuffer					= vertexBufferDyn->GetVertexBuffer();;
	vertexBuffer->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);

	//
	zTLODRenderArgsSubMesh	lodRenderArgsSub;
	zVEC3					normalCS;

	zBOOL sectorVob		= renderContext.vob->GetGroundPoly() ? renderContext.vob->GetGroundPoly()->GetSectorFlag() : FALSE;

	s_subMeshRenderDir	= -s_subMeshRenderDir;
	int subMeshIndex	= (s_subMeshRenderDir==1) ? 0 : numSubMeshes-1;
	int count			= numSubMeshes;
	if (count>0)
	do
	{
		zCSubMesh	*subMesh			= &(subMeshList[subMeshIndex]);
		subMeshIndex					+= s_subMeshRenderDir;
		CalcLODRenderArgsSubMesh		(renderContext, *lodRenderArgs, subMesh, lodRenderArgsSub);
		if (lodRenderArgsSub.numTri<=0)	continue;

		//
		CalcNumSubdivEdges				(subMesh, lodRenderArgs, lodRenderArgsSub);

		// VB klarmachen: lock
		zDWORD	startVertexIndex;
vertexBufferDyn->FlushAtFrameStart();		// OUCH
		zDWORD	numVBVerts				= lodRenderArgsSub.numWedge + lodRenderArgsSub.numSubdivEdges;
		if (!vertexBufferDyn->Lock			(numVBVerts, startVertexIndex))
		{
			zERR_WARNING ( "C: zCProgMeshProto::RenderDynamicSubdiv()	- vertex buffer lock failed." );
			zCCamera::activeCam->PopTransform	(zCAM_TRAFO_WORLDVIEW);
			return FALSE;
		};
		zDWORD	currentVertIndex		= startVertexIndex; 

		// Verts in den Buffer packen
		// der fixe Anteil
		for (int j=0; j<lodRenderArgsSub.numWedge; j++, currentVertIndex++)
		{
			// FIXME: das Packen geht noch schneller.. (VB Ptr direkt benutzen)
			const int posIndex				= subMesh->wedgeList[j].position;
			vertexBuffer->SetXYZ			(currentVertIndex, s_posCacheList[posIndex]);
			normalCS						= renderLightCont->GetTrafoObjToCam().Rotate (subMesh->wedgeList[j].normal);
			vertexBuffer->SetNormal			(currentVertIndex, normalCS);
			vertexBuffer->SetTexUV0			(currentVertIndex, subMesh->wedgeList[j].texUV);
		};

		// SubdivVerts in den Buffer packen
		CalcSubdivSubMesh				(subMesh, vertexBuffer, lodRenderArgs, renderLightCont, lodRenderArgsSub);

		// IndexList erstellen
		s_workIndexList.EmptyList		();		
		s_workIndexList.AllocAbs		(lodRenderArgsSub.numTri*3*4);
		s_workIndexList.MarkNumAllocUsed();
		int numIndizes=0;

		// die neuen Verts
		for (j=0; j<lodRenderArgsSub.numTri; j++)
		{

			struct zTSplitTable {
				int		numTri;
				struct {
					int	index[3];
				} triList[4];
			};

			#define A 3
			#define B 4
			#define C 5
			static const zTSplitTable splitTable[] = 
			{
				{ 1, 0,1,2, 0,0,0, 0,0,0, 0,0,0 },
				{ 2, 0,1,C, 1,2,C, 0,0,0, 0,0,0 },
				{ 2, 0,1,B, B,2,0, 0,0,0, 0,0,0 },
				{ 3, 0,1,B, B,2,C, 0,B,C, 0,0,0 },
				{ 2, 0,A,2, 1,2,A, 0,0,0, 0,0,0 },
				{ 3, 0,A,C, 1,C,A, 1,2,C, 0,0,0 },
				{ 3, 0,B,2, 0,A,B, A,1,B, 0,0,0 },
				{ 4, A,B,C, 0,A,C, 1,B,A, 2,C,B },
			};
			#undef A
			#undef B
			#undef C

			int indexList[6];
			indexList[0]	= subMesh->triList[j].wedge[0];
			indexList[1]	= subMesh->triList[j].wedge[1];
			indexList[2]	= subMesh->triList[j].wedge[2];
			indexList[3]	= subMesh->triEdgeList[j].edge[0] + lodRenderArgsSub.numWedge;
			indexList[4]	= subMesh->triEdgeList[j].edge[1] + lodRenderArgsSub.numWedge;
			indexList[5]	= subMesh->triEdgeList[j].edge[2] + lodRenderArgsSub.numWedge;

			// numSubdivEdge
			int splitCode	=	int(subMesh->triEdgeList[j].edge[2]<lodRenderArgsSub.numSubdivEdges)		|
								int(subMesh->triEdgeList[j].edge[1]<lodRenderArgsSub.numSubdivEdges) << 1	|
								int(subMesh->triEdgeList[j].edge[0]<lodRenderArgsSub.numSubdivEdges) << 2;
			int numTri		= splitTable[splitCode].numTri;
			for (int k=0; k<numTri; k++)
			{
				s_workIndexList[numIndizes++]		= indexList[splitTable[splitCode].triList[k].index[0]];
				s_workIndexList[numIndizes++]		= indexList[splitTable[splitCode].triList[k].index[1]];
				s_workIndexList[numIndizes++]		= indexList[splitTable[splitCode].triList[k].index[2]];
			};

		};

		// VB unlocken und rendern
		vertexBufferDyn->Unlock			();
		

		if (!subMesh->material->GetEnvMapEnabled())
		{
			zrenderMan.DrawVertexBuffer		(vertexBuffer, 
											 startVertexIndex, 
											 numVBVerts,
											 s_workIndexList.GetArray(),
											 numIndizes,
											 subMesh->material, sectorVob);
		}
		else
		{
			const zREAL envMapStrengthBak = subMesh->material->GetEnvMapStrength();
			const float ONE_OVER_255	  = 1.0f/255.0f;

			if (envMapStrengthBak>0)
			subMesh->material->SetEnvMapStrength( envMapStrengthBak * renderContext.vob->CalcLightSampleAtOrigin().GetIntensityFloat()*ONE_OVER_255 );
			zrenderMan.DrawVertexBuffer		(vertexBuffer, 
											 startVertexIndex, 
											 numVBVerts,
											 s_workIndexList.GetArray(),
											 numIndizes,
											 subMesh->material, sectorVob);
			subMesh->material->SetEnvMapStrength( envMapStrengthBak );
		};

	} while(--count);

	zCCamera::activeCam->PopTransform	(zCAM_TRAFO_WORLDVIEW);
	return TRUE;
};

// =======================================================================================================================

zBOOL zCCFASTCALL zCProgMeshProto::RenderStaticLODShadow	(	
													zTRenderContext&		renderContext, 
													int						renderFlags, 
													zTLODRenderArgs			*lodRenderArgs, 
													zCRenderLightContainer	*renderLightCont
												)
{
	// Fall E):		TLC, prog mesh, static VB



	/*if (!(renderFlags & zPM_RENDER_FLAG_DONT_SET_TRANSFROM))
	{
		zCCamera::activeCam->PushTransform	(zCAM_TRAFO_WORLDVIEW);
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, renderContext.vob->trafoObjToWorld);
	};*/	

	//
	zCCamera::activeCam->PushTransform	(zCAM_TRAFO_WORLDVIEW);
	zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLDVIEW, zMAT4::GetIdentity());

	//if (renderFlags & zPM_RENDER_FLAG_SW_TRAFO_VERTS)



	// 
	zMAT4	shadowMat;
	zTPlane groundPlane = renderContext.vob->GetGroundPoly()->GetPlane();
	zVEC4	lightPos;
	lightPos				= zVEC4(0.5,1,0,1);
	CreateShadowMatrix		(shadowMat, groundPlane, lightPos);
	shadowMat[1][3]	= renderContext.vob->GetBBox3DWorld().mins[VY]+3;
	//shadowMat=shadowMat.Transpose();
	zMAT4 vobTrafo = Alg_Identity3D();
	vobTrafo.SetTranslation(renderContext.vob->trafoObjToWorld.GetTranslation());
	zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, shadowMat*vobTrafo);
	//zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, shadowMat*zCCamera::activeCam->GetTransform(zCAM_TRAFO_WORLD));

	SoftwareTransformVerts (renderFlags, lodRenderArgs, 0, 1);


	//
	zTRnd_ZBufferCmp zbufferCmp	= zrenderer->GetZBufferCompare	();
	zrenderer->SetZBufferCompare	(zRND_ZBUFFER_CMP_LESS);

	//
	static zCShader			shadowShader;
	static zCShaderStage	shadowStage;
	shadowStage.Clear		();
	shadowStage.alphaFunc	= zRND_ALPHA_FUNC_MUL;
	shadowShader.Clear		();
	shadowShader.AddStage	(&shadowStage);

	// Lights aktivieren
	renderLightCont->SetupRendererLights();

/*	// TEMP
	if (this->vertexBufferStatic==0)			PackStaticVertexBuffers					();
	if (this->vertexBufferStatic->IsLocked())	zvertexBufferMan.UnlockOpenVertexBuffers();

	// hat LOD
	zTLODRenderArgsSubMesh	lodRenderArgsSub;
	s_subMeshRenderDir	= -s_subMeshRenderDir;
	int subMeshIndex	= (s_subMeshRenderDir==1) ? 0 : numSubMeshes-1;
	int count			= numSubMeshes;
	if (count>0)
	do
	{
		zCSubMesh *subMesh				= &(subMeshList[subMeshIndex]);
		subMeshIndex					+= s_subMeshRenderDir;
		CalcLODRenderArgsSubMesh		(renderContext, *lodRenderArgs, subMesh, lodRenderArgsSub);
		if (lodRenderArgsSub.numTri<=0)	continue;

		// wedgeRemap Liste erstellen (damit sie spaeter geshared werden kann)
		{
			// a) der unmodifizierte Teil
			for (int j=0; j<lodRenderArgsSub.numWedge; j++) {
				s_wedgeRemap[j]	= j;
			};
			// b) der modifizierte Teil
			for (j=lodRenderArgsSub.numWedge; j<subMesh->wedgeList.GetNum(); j++) {
				int wedgeIndex = j;
				while (wedgeIndex>=lodRenderArgsSub.numWedge) {
					zERR_ASSERT (subMesh->wedgeMap[wedgeIndex]!=zPMINDEX_NONE);
					wedgeIndex = subMesh->wedgeMap[wedgeIndex];
				};
				s_wedgeRemap[j]	= wedgeIndex;
			};
		};
		int numIndizes=0;
		{
			// remaped IndexList erstellen
			s_workIndexList.EmptyList();
			s_workIndexList.AllocAbs (lodRenderArgsSub.numTri*3);	s_workIndexList.MarkNumAllocUsed();
			for (int j=0; j<lodRenderArgsSub.numTri; j++)
			{
				s_workIndexList[numIndizes++]	= s_wedgeRemap[subMesh->triList[j].wedge[0]];
				s_workIndexList[numIndizes++]	= s_wedgeRemap[subMesh->triList[j].wedge[1]];
				s_workIndexList[numIndizes++]	= s_wedgeRemap[subMesh->triList[j].wedge[2]];
			};
		};
		zrenderMan.DrawVertexBuffer			(vertexBufferStatic, 
											 subMesh->vbStartIndex, 
											 lodRenderArgsSub.numWedge,
											 s_workIndexList.GetArray(),
											 numIndizes,
											 &shadowShader);
	} while(--count);*/


	// Lights aktivieren
	renderLightCont->SetupRendererLights();

	// Pro Material wird ein VB gefuellt
	// Die Art der VB haengt davon ab, ob korrekte oder schnelle Prelight Beleuchtung gemacht werden soll
	zCVertexBuffer		*vertexBuffer	= 0;
	zCVertexBufferDyn	*vertexBufferDyn= 0;
//	if (renderLightCont->GetDoPrelight())	vertexBuffer= s_vertBufferColor;
//	else									vertexBuffer= s_vertBufferNormal;
	vertexBufferDyn					= s_vertBufferNormal;
	vertexBuffer					= vertexBufferDyn->GetVertexBuffer();;
	vertexBuffer->SetPrimitiveType	(zVBUFFER_PT_TRIANGLELIST);

	//
	zTLODRenderArgsSubMesh	lodRenderArgsSub;
	zVEC3					normalCS;
	s_subMeshRenderDir	= -s_subMeshRenderDir;
	int subMeshIndex	= (s_subMeshRenderDir==1) ? 0 : numSubMeshes-1;
	int count			= numSubMeshes;
	if (count>0)
	do
	{
		const zCSubMesh* const subMesh	= &(subMeshList[subMeshIndex]);
		subMeshIndex					+= s_subMeshRenderDir;
		CalcLODRenderArgsSubMesh		(renderContext, *lodRenderArgs, subMesh, lodRenderArgsSub);
		if (lodRenderArgsSub.numTri<=0)	continue;

		// wedgeRemap Liste erstellen (damit sie spaeter geshared werden kann)
		{
			// a) der unmodifizierte Teil
			for (int j=0; j<lodRenderArgsSub.numWedge; j++) {
				s_wedgeRemap[j]	= j;
			};
			// b) der modifizierte Teil
			for (j=lodRenderArgsSub.numWedge; j<subMesh->wedgeList.GetNum(); j++) {
				int wedgeIndex = j;
				while (wedgeIndex>=lodRenderArgsSub.numWedge) {
					zERR_ASSERT (subMesh->wedgeMap[wedgeIndex]!=zPMINDEX_NONE);
					wedgeIndex = subMesh->wedgeMap[wedgeIndex];
				};
				s_wedgeRemap[j]	= wedgeIndex;
			};
		};

		// IndexList erstellen
		s_workIndexList.EmptyList		();		
		s_workIndexList.AllocAbs		(lodRenderArgsSub.numTri*3);
		s_workIndexList.MarkNumAllocUsed();
		int numIndizes=0;
		for (int j=0; j<lodRenderArgsSub.numTri; j++)
		{
			s_workIndexList[numIndizes++] = (s_wedgeRemap[subMesh->triList[j].wedge[0]]);
			s_workIndexList[numIndizes++] = (s_wedgeRemap[subMesh->triList[j].wedge[1]]);
			s_workIndexList[numIndizes++] = (s_wedgeRemap[subMesh->triList[j].wedge[2]]);
		};

		// VB klarmachen: lock
		zDWORD startVertexIndex;
		vertexBufferDyn->Lock		(lodRenderArgsSub.numWedge, startVertexIndex);
		zDWORD currentVertIndex		= startVertexIndex; 

		// Verts in den Buffer packen
		// der fixe Anteil
		for (j=0; j<lodRenderArgsSub.numMinMorphWedge; j++, currentVertIndex++)
		{
			// FIXME: das Packen geht noch schneller.. (VB Ptr direkt benutzen)
			const int posIndex				= subMesh->wedgeList[j].position;
// CRASH in folgender Zeile, DEFECT 3422
			vertexBuffer->SetXYZ			(currentVertIndex, s_posCacheList[posIndex]);
			//normalCS						= renderLightCont->GetTrafoObjToCam().Rotate (subMesh->wedgeList[j].normal);
			//vertexBuffer->SetNormal			(currentVertIndex, normalCS);
			//vertexBuffer->SetTexUV0			(currentVertIndex, subMesh->wedgeList[j].texUV);
		};

		// der gemorphte Anteil
		for (; j<lodRenderArgsSub.numWedge; j++, currentVertIndex++)
		{
			int destIndex = j;
			while (destIndex>=lodRenderArgsSub.numMinMorphWedge) {
				if (subMesh->wedgeMap[destIndex]==zPMINDEX_NONE)		break;
				destIndex = subMesh->wedgeMap[destIndex];
			};
 			
			// Das lerpen macht man hier fuer jede Wedge (nicht mehr pro Wedge, pro Tri). Optimaler Fall.
			// FIXME: das Packen geht noch schneller.. (VB Ptr direkt benutzen)
			const zTPMWedge&	wedge1		= subMesh->wedgeList[j];
			const zTPMWedge&	wedge0		= subMesh->wedgeList[destIndex];
			vertexBuffer->SetXYZ			(currentVertIndex, zLerp (lodRenderArgs->morphFrac, s_posCacheList[wedge0.position], s_posCacheList[wedge1.position]));
			//normalCS						= renderLightCont->GetTrafoObjToCam().Rotate (zLerp (lodRenderArgs->morphFrac, wedge0.normal  , wedge1.normal));
			//vertexBuffer->SetNormal			(currentVertIndex, normalCS);
			//vertexBuffer->SetTexUV0			(currentVertIndex, zLerp (lodRenderArgs->morphFrac, wedge0.texUV	, wedge1.texUV));
		};

		// VB unlocken und rendern
		vertexBufferDyn->Unlock			();
		zrenderMan.DrawVertexBuffer		(vertexBuffer, 
										 startVertexIndex, 
										 lodRenderArgsSub.numWedge,
										 s_workIndexList.GetArray(),
										 numIndizes,
										 &shadowShader);

	} while(--count);


	//
	zrenderer->SetZBufferCompare	(zbufferCmp);

	//if (!(renderFlags & zPM_RENDER_FLAG_DONT_SET_TRANSFROM))
		zCCamera::activeCam->PopTransform	(zCAM_TRAFO_WORLDVIEW);
	return TRUE;
};

// =======================================================================================================================

#if 0
			for (int k=0; k<3; k++)
			{
				int l=k+1; if (l==3) l=0;
				const int wedgeIndex0		= subMesh->triList[j].wedge[k];
				const int wedgeIndex1		= subMesh->triList[j].wedge[l];
				const int posIndex0			= subMesh->wedgeList[wedgeIndex0].position;
				const int posIndex1			= subMesh->wedgeList[wedgeIndex1].position;

				zVEC3 newPos				= zLerp (0.5F, s_posCacheList[posIndex0]		 , s_posCacheList[posIndex1]);
				zVEC2 texUV					= zLerp (0.5F, subMesh->wedgeList[wedgeIndex0].texUV , subMesh->wedgeList[wedgeIndex1].texUV);

				zVEC3 avgPosNormal			= zLerp (0.5F, s_posNormalCSList[posIndex0], s_posNormalCSList[posIndex1]);
				zREAL edgeLen				= (s_posCacheList[posIndex0]-s_posCacheList[posIndex1]).LengthApprox();
				zREAL dot					= s_posNormalCSList[posIndex0] * s_posNormalCSList[posIndex1];
				if (dot<-0.2F) dot=1;
				zClamp01					(dot);
				dot = 1.0F - dot;
				newPos						+= (0.2F * edgeLen * dot) * avgPosNormal;

				vertexBuffer->SetXYZ		(currentVertIndex, newPos);
				normalCS					= renderLightCont->GetTrafObjToCam().Rotate (normal);
				vertexBuffer->SetNormal		(currentVertIndex, normalCS);
				vertexBuffer->SetTexUV0		(currentVertIndex, texUV);
				currentVertIndex++;
			};
			int ind_a = currentVertIndex-3;
			int ind_b = currentVertIndex-2;
			int ind_c = currentVertIndex-1; 

			s_workIndexList[numIndizes++]		= subMesh->triList[j].wedge[0];
			s_workIndexList[numIndizes++]		= ind_a;
			s_workIndexList[numIndizes++]		= ind_c;
												
			s_workIndexList[numIndizes++]		= subMesh->triList[j].wedge[1];
			s_workIndexList[numIndizes++]		= ind_b;
			s_workIndexList[numIndizes++]		= ind_a;
												
			s_workIndexList[numIndizes++]		= subMesh->triList[j].wedge[2];
			s_workIndexList[numIndizes++]		= ind_c;
			s_workIndexList[numIndizes++]		= ind_b;
												
			s_workIndexList[numIndizes++]		= ind_a;
			s_workIndexList[numIndizes++]		= ind_b;
			s_workIndexList[numIndizes++]		= ind_c;
#endif

#if 0
zBOOL zCProgMeshProto::RenderSoftwareTLC(	zTRenderContext&		renderContext, 
											int						renderFlags, 
											zTLODRenderArgs			*lodRenderArgs, 
											zCRenderLightContainer	*renderLightCont
										)
{
	// fuer's 3D clipping in CS setzen
	zCCamera::activeCam->camMatrix.MakeIdentity();
	zCCamera::activeCam->camMatrixInv = zCCamera::activeCam->camMatrix;				// fuer frustum-planes
	zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );		// fuer backfaceCulling
	zCCamera::activeCam->SetUpFrustum(); 

	// render Triangles
	zCOLOR	prelightColor(0,0,0,255);
	for (int i=0; i<lodRenderArgs->numTri; i++)
	{
		zTPMTriangle	*tri = &triList[i];
		int				curWedge[3];

		// Triangle in pmPoly verpacken
		for (int j=0; j<3; j++)
		{
			// result-WedgeIndex sharen !!
			int wedgeIndex = s_wedgeRemap[tri->wedge[j]];

			// fuer spaeter cachen
			curWedge[j] = wedgeIndex;

			//
			int	posIndex = wedgeList[wedgeIndex].position;

			if ((wedgeIndex>=lodRenderArgs->numMinMorphWedge) && (DO_MORPH))
			{
				int destIndex = wedgeIndex;
				while (destIndex>=lodRenderArgs->numMinMorphWedge) {
					if (wedgeMap[destIndex]==zPMINDEX_NONE)		break;
					destIndex = wedgeMap[destIndex];
				};
 				
				// FIXME: das lerpen macht man hier fuer jedes Triangle, in dem der Vertex vorkommt... (5% aller verts?)
				//        gibt's einen besseren Weg ?
				const zTPMWedge&	wedge1		= wedgeList[wedgeIndex];
				const zTPMWedge&	wedge0		= wedgeList[destIndex];
				pmPoly->vertex[j]->position		= zLerp (lodRenderArgs->morphFrac, s_posCacheList[wedge0.position].posCS, s_posCacheList[wedge1.position].posCS);
				pmPoly->feature[j]->texu		= zLerp (lodRenderArgs->morphFrac, wedge0.texUV[0], wedge1.texUV[0]);
				pmPoly->feature[j]->texv		= zLerp (lodRenderArgs->morphFrac, wedge0.texUV[1], wedge1.texUV[1]);
				pmPoly->feature[j]->vertNormal	= zLerp (lodRenderArgs->morphFrac, wedge0.normal  , wedge1.normal);
			} else 
			{
				pmPoly->vertex[j]->position		= s_posCacheList[posIndex].posCS;
				pmPoly->feature[j]->texu		= wedgeList[wedgeIndex].texUV[0];
				pmPoly->feature[j]->texv		= wedgeList[wedgeIndex].texUV[1];
				pmPoly->feature[j]->vertNormal	= wedgeList[wedgeIndex].normal;
			};
//			zCOLOR color (s_wedgeCacheList[wedgeIndex].color[0], s_wedgeCacheList[wedgeIndex].color[1], s_wedgeCacheList[wedgeIndex].color[2],255);
//			zCOLOR color = col;
			if (renderLightCont->GetDoPrelight()) {
				prelightColor.SetRGB			(colorList[wedgeIndex] * renderLightCont->GetPrelightColor());
				pmPoly->feature[j]->lightStat	= prelightColor;
				pmPoly->feature[j]->lightDyn	= prelightColor;
			};
			pmPoly->material				= materialList[tri->matIndex];
		};

		// clipping 3D (camSpace)
		zBOOL modified	 = FALSE;
		if (renderContext.clipFlags>0) {
			int numClipVert	= zCPolygon::GetNumClipVertScene();
			if (!pmPoly->ClipToFrustum(renderContext.clipFlags)) continue;
			modified = (pmPoly->numClipVert!=3) || (numClipVert!=zCPolygon::GetNumClipVertScene());
			if (!modified)
				pmPoly->Unclip();	// Vertex-Order wieder herstellen
		} else {
			pmPoly->Unclip();
		};

		// pos projezieren
		if (modified) 
		{
			// stumpf alles projezieren, nichts sharen
			for (j=0; j<pmPoly->numClipVert; j++) {
				pmPoly->clipVert[j]->vertCamSpace	= pmPoly->clipVert[j]->position;
				zCCamera::activeCam->ProjectClamp	(pmPoly->clipVert[j]);
			};
		} else {
			for (j=0; j<3; j++)
			{
				// position noch nicht projeziert ?
				int	posIndex = wedgeList[curWedge[j]].position;
				if (s_posCacheList[posIndex].transformed!=s_frameCtr) 
				{
					s_posCacheList[posIndex].transformed= s_frameCtr;
					zREAL zrecip						= zREAL(1.0F) / pmPoly->clipVert[j]->position[VZ];
					s_posCacheList[posIndex].posCSZInv	= zrecip;
					zCCamera::activeCam->Project (pmPoly->clipVert[j]->position, zrecip, s_posCacheList[posIndex].posScr);
				};
				pmPoly->clipVert[j]->vertCamSpaceZInv	= s_posCacheList[posIndex].posCSZInv;
				pmPoly->clipVert[j]->vertScrX			= s_posCacheList[posIndex].posScr.n[VX];
				pmPoly->clipVert[j]->vertScrY			= s_posCacheList[posIndex].posScr.n[VY];
//				zClamp (pmPoly->clipVert[j]->vertScrX, zVALUE(0), zVALUE(zCCamera::activeCam->vpData.xdimFloat));
//				zClamp (pmPoly->clipVert[j]->vertScrY, zVALUE(0), zVALUE(zCCamera::activeCam->vpData.ydimFloat));
			};
		};

		// backface culling 2D
		zREAL x1 = pmPoly->clipVert[0]->vertScrX - pmPoly->clipVert[1]->vertScrX;
		zREAL y1 = pmPoly->clipVert[0]->vertScrY - pmPoly->clipVert[1]->vertScrY;
		zREAL x2 = pmPoly->clipVert[2]->vertScrX - pmPoly->clipVert[1]->vertScrX;
		zREAL y2 = pmPoly->clipVert[2]->vertScrY - pmPoly->clipVert[1]->vertScrY;
		if ((x1*y2 - x2*y1)<=0) continue;

		// 6) light
		if (!renderLightCont->GetDoPrelight()) 
		{
			if (modified)
			{
				// stumpf alles lighten, nichts sharen
				zVEC3 color;
				zVEC3 normalCS;
				for (j=0; j<pmPoly->numClipVert; j++) {
					normalCS= renderLightCont->GetTrafObjToCam().Rotate (pmPoly->clipFeat[j]->vertNormal);
					color	= renderLightCont->LightVertex				(pmPoly->clipVert[j]->position, normalCS);
//					color	= renderLightCont->LightVertex				(pmPoly->clipVert[j]->position, pmPoly->clipFeat[j]->vertNormal);
					pmPoly->clipFeat[j]->lightDyn.SetRGB				(color);
				};
			} else {
				zVEC3 normalCS;
				for (j=0; j<3; j++) {
					int wedgeIndex = curWedge[j];
					if (s_wedgeCacheList[wedgeIndex].processed!=s_frameCtr) {
						s_wedgeCacheList[wedgeIndex].processed	= s_frameCtr;
						normalCS								= renderLightCont->GetTrafObjToCam().Rotate (wedgeList[wedgeIndex].normal);
						s_wedgeCacheList[wedgeIndex].color		= renderLightCont->LightVertex				(pmPoly->clipVert[j]->position, normalCS);
//						s_wedgeCacheList[wedgeIndex].color		= renderLightCont->LightVertex				(pmPoly->clipVert[j]->position, wedgeList[wedgeIndex].normal);
					};
					pmPoly->clipFeat[j]->lightDyn.SetRGB (s_wedgeCacheList[wedgeIndex].color);
				};
			};
		};

		// 7) RENDER !
		{
			zrenderer->DrawPoly (pmPoly);
			zCWorld::s_polysRendered++;
			zCWorld::s_trisRendered += (pmPoly->numClipVert-2);
		}
	};

	// cleanup
	pmPoly->material = 0;

	return TRUE; 
};		
#endif 

// =======================================================================================================================

// =======================================================================================================================

struct zTPMProtoDirEntry {
	zDWORD		offset;
	zDWORD		size;
	void Set (zDWORD _offset, zDWORD _size) { offset=_offset; size=_size; };
};

struct zTPMProtoDirectoryMain {
	zTPMProtoDirEntry	posList;
	zTPMProtoDirEntry	posNormalList;

	void TransferFromProto (zCProgMeshProto *pmProto) {
		#define SetDirEntry(FIELD) FIELD.Set ((zBYTE*)pmProto->FIELD.GetArray()- pmProto->dataPool, pmProto->FIELD.GetNum());
		SetDirEntry		(posList);
		SetDirEntry		(posNormalList);
		#undef SetDirEntry
	};
	void TransferToProto (zCProgMeshProto *pmProto) {
		#define GetFromEntry(FIELD) pmProto->FIELD.SetArray ((zBYTE*)zDWORD(pmProto->dataPool) + zDWORD(FIELD.offset), FIELD.size);
		GetFromEntry	(posList);
		GetFromEntry	(posNormalList);
		#undef GetFromEntry
	};
};

struct zTPMProtoDirectorySubMesh {
	zTPMProtoDirEntry	triList;
	zTPMProtoDirEntry	wedgeList;
	zTPMProtoDirEntry	colorList;
	zTPMProtoDirEntry	triPlaneIndexList;
	zTPMProtoDirEntry	triPlaneList;
	zTPMProtoDirEntry	wedgeMap;
	zTPMProtoDirEntry	vertexUpdates;
	zTPMProtoDirEntry	triEdgeList;
	zTPMProtoDirEntry	edgeList;
	zTPMProtoDirEntry	edgeScoreList;

	void TransferFromProto (zCProgMeshProto *pmProto, zCProgMeshProto::zCSubMesh *subMesh) {
		#define SetDirEntry(FIELD) FIELD.Set ((zBYTE*)subMesh->FIELD.GetArray()- pmProto->dataPool, subMesh->FIELD.GetNum());
		SetDirEntry		(triList);
		SetDirEntry		(wedgeList);
		SetDirEntry		(colorList);
		SetDirEntry		(triPlaneIndexList);
		SetDirEntry		(triPlaneList);
		SetDirEntry		(wedgeMap);
		SetDirEntry		(vertexUpdates);
		SetDirEntry		(triEdgeList);
		SetDirEntry		(edgeList);
		SetDirEntry		(edgeScoreList);
		#undef SetDirEntry
	};
	void TransferToProto (zCProgMeshProto *pmProto, zCProgMeshProto::zCSubMesh *subMesh) {
		#define GetFromEntry(FIELD) subMesh->FIELD.SetArray ((zBYTE*)zDWORD(pmProto->dataPool) + zDWORD(FIELD.offset), FIELD.size);
		GetFromEntry	(triList);
		GetFromEntry	(wedgeList);
		GetFromEntry	(colorList);
		GetFromEntry	(triPlaneIndexList);
		GetFromEntry	(triPlaneList);
		GetFromEntry	(wedgeMap);
		GetFromEntry	(vertexUpdates);
		GetFromEntry	(triEdgeList);
		GetFromEntry	(edgeList);
		GetFromEntry	(edgeScoreList);
		#undef GetFromEntry
	};
};

static const zWORD zPROGMESH_FILE_VERS				= (05);		// 8 bit

static const zWORD zFCHUNK_PROGMESH					= 0xB100;
static const zWORD		zFCHUNK_PROGMESH_END		= 0xB1FF;

zWORD zCProgMeshProto::GetFileVersion ()			// gesamt: 16 Bit!!
{ 
	zWORD vers	= zWORD(zCMaterial::GetStaticClassDef()->GetArchiveVersion()) << 8;
	vers		+= zPROGMESH_FILE_VERS; 
	return vers; 
};

zBOOL zCProgMeshProto::Save (zCFileBIN& file) 
{
	//
	file.BinStartChunk			 		(zFCHUNK_PROGMESH);
	{
		// ==============
		//	HEADER
		// ==============

		file.BinWriteWord				(zCProgMeshProto::GetFileVersion());
#if 0
		// Date & Name des Source-.3DS schreiben
		zSTRING		meshName;
		// [BENDLIN] 2002-06-26, zero memory (garbage in bin files because of alignment)
		zFILE_STATS	sourceStats;
		memset(&sourceStats, 0, sizeof(sourceStats));

		if (mesh->GetMeshName().Length()>0)
		if (mesh->GetMeshName()[0]!='#')
		{
			meshName = mesh->GetMeshName(); 
			zoptions->ChangeDir		(DIR_MESHES);
			zPATH meshPath		(meshName);
			if (meshPath.SearchFile(meshPath.GetFilename()+"."+meshPath.GetExt())!=zERR_NONE) {
				zerr.Report		(zERR_WARN, 1000, "D: (::Save): source-file not found: "+mesh->GetMeshName());
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
#endif
		// ==============
		//	DATA
		// ==============

		// dataPool
		{
			file.BinWriteDWord				(dataSize);
			file.BinWrite					(dataPool	, dataSize);
		};

		// dataPool - Directorys
		{
			file.BinWriteByte				(numSubMeshes);
			zTPMProtoDirectoryMain			protoDir;
			protoDir.TransferFromProto		(this);
			file.BinWrite					(&protoDir	, sizeof(protoDir));
			
			zTPMProtoDirectorySubMesh subMeshDir;
			for (int i=0; i<numSubMeshes; i++)
			{
				subMeshDir.TransferFromProto(this, &(subMeshList[i]));
				file.BinWrite				(&subMeshDir, sizeof(subMeshDir));
			};
		};

		// materialList
		{
			zCArchiver *arc = zarcFactory.CreateArchiverWrite (file.file, zARC_MODE_BINARY, FALSE, zARC_FLAG_WRITE_BRIEF_HEADER | zARC_FLAG_NO_SPY_MESSAGES); // noSaveGame, briefHeader
			zERR_ASSERT_STRICT (arc);
			for (int i=0; i<numSubMeshes; i++) 
			{
				arc->WriteString	("",subMeshList[i].material->GetName());
				arc->WriteObject	(subMeshList[i].material);
			};
			arc->WriteBool		("",GetAlphaTestingEnabled());
			arc->Close			();
			zRELEASE			(arc);
		};

		// misc
		{
			file.BinWrite					(&bbox3D	, sizeof(bbox3D));
			obbox3D.SaveBIN					(file);
			file.BinWrite					(&lodParams	, sizeof(lodParams));
		};
	};

	// ==============
	//	End-Kennung
	// ==============

	file.BinStartChunk		(zFCHUNK_PROGMESH_END);

	// cleanup
	file.BinEndChunk		();			// kein BinClose() !

	return TRUE;
};

zBOOL zCProgMeshProto::Load	(zCFileBIN& file)
{
	// Wird diesem Mesh als ganzes eine DetailTextur zugeordnet?
	zCMapDetailTexture::zTMapDetailTextureEntry *objectDetailTexEntry = 0;
	if (!this->GetObjectName().IsEmpty())
	{
		objectDetailTexEntry = const_cast<zCMapDetailTexture::zTMapDetailTextureEntry *>(zCMapDetailTexture::S_GetDetailTextureInfo (this->GetObjectName()));
	};

	zWORD id;
	zLONG len;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
		case zFCHUNK_PROGMESH:
			{
				// ==============
				//	HEADER
				// ==============
				zWORD		vers;
				file.BinReadWord	(vers);
				if (vers!=zCProgMeshProto::GetFileVersion()) {
					zERR_WARNING ("D: (zCProgMeshProto::Load): wrong mesh-file version, engine: "+zSTRING(zCProgMeshProto::GetFileVersion())+", file: "+zSTRING(vers));
					return FALSE;
				};
#if 0
				zDATE		date;
				zSTRING		s;
				file.BinRead		(&(date), sizeof(date));
				file.BinReadString	(s); 
				SetMeshName			(s);

				// alte Version, oder neueres ASC-File ?
				if (vers!=zCMesh::GetFileVersion()) {
					zERR_WARNING ("D: (zCProgMeshProto::Load): wrong mesh-file version, engine: "+zSTRING(zCProgMeshProto::GetFileVersion())+", file: "+zSTRING(vers));
					return FALSE;
				};
				
				if (s.Length()>0) 
				if (zCMesh::GetAutoConvertMeshes()) {
					// Source-Mesh aufspueren 
					zPATH meshPath;
					zoptions->ChangeDir (DIR_MESHES);
					if (meshPath.SearchFile(meshName)!=zERR_NONE) {
						zerr.Report (zERR_WARN, 1000, "D: MSH: z3d(zCMesh::LoadMSH): ASC not found: "+s);
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
#endif
				// ==============
				//	DATA
				// ==============

				// dataPool
				{
					delete[] dataPool; dataPool=0;
					file.BinReadDWord				(dataSize);
					dataPool						= zNEW(zBYTE) [dataSize];
					file.BinRead					(dataPool	, dataSize);
				}

				// dataPool - Directorys
				{
					zBYTE b;
					file.BinReadByte				(b);
					numSubMeshes					= b;
					zTPMProtoDirectoryMain			protoDir;
					file.BinRead					(&protoDir	, sizeof(protoDir));
					protoDir.TransferToProto		(this);

					//
					delete[] subMeshList; subMeshList=0;
					subMeshList						= zNEW(zCSubMesh) [numSubMeshes];
					
					zERR_ASSERT_STRICT				(numSubMeshes<32);
					zTPMProtoDirectorySubMesh		subMeshDir[32];
					file.BinRead					(&subMeshDir, sizeof(zTPMProtoDirectorySubMesh)*numSubMeshes);
					for (int i=0; i<numSubMeshes; i++)
					{
						subMeshDir[i].TransferToProto(this, &(subMeshList[i]));
					};
				}

				// materialList
				{
					zCArchiver			*arc = zarcFactory.CreateArchiverRead (file.file, zARC_FLAG_NO_SPY_MESSAGES);
					zERR_ASSERT_STRICT	(arc);
					zSTRING				matName;
					zCMaterial*			mat=0;
					// Die MatList haelt offizielle Referenzen auf die enthaltenen Materialien
					for (int i=0; i<numSubMeshes; i++) 
					{
						matName		= arc->ReadString				("");
						mat			= zCMaterial::SearchName		(matName);
						if (mat) {
							mat->AddRef			();						// das ProgMeshProto Objekt referenziert dieses Material ab nun..
							zWORD vers;
							arc->ReadChunkStart	(matName, vers);
							arc->SkipOpenChunk	();
						} else {
							mat		= (zCMaterial*)arc->ReadObject	();	// erzeugte Objekte ("new") kommen hier mit ref=1 heraus

							// ggfs. eine Detail-Tex assoziieren
							if ((mat) && (mat->GetTexture()))
							{
								if (objectDetailTexEntry)
								{
									mat->SetDetailTexture		(objectDetailTexEntry->detailTextureName);
									mat->SetDetailTextureScale	(objectDetailTexEntry->detailTextureScale);
								}
							};
						};
						subMeshList[i].material	= mat;
						// Fehler ? (z.B. Objekt im alten Format im File)	=>	Abbruch / Neu-Konvertierung
						if (mat==0) {
							// vor dem Raussprung aufraeumen..
							for (int j=0; j<i; j++)
								subMeshList[i].material->Release();
							return FALSE;
						};
					};
					SetAlphaTestingEnabled(arc->ReadBool(""));
					arc->Close	();
					zRELEASE	(arc);
				};

				// misc
				{
					file.BinRead					(&bbox3D	, sizeof(bbox3D));
					obbox3D.LoadBIN					(file);
					file.BinRead					(&lodParams	, sizeof(lodParams));
				};
			};
			break;
		case zFCHUNK_PROGMESH_END: 
			goto fileEnd;
			break;
		default:
			file.BinSkipChunk();
		};
	}
fileEnd:;

	return TRUE;
};

// =======================================================================================================================

///////////////////////////////////////////////////////////////////////////
//      Deformable SoftSkin Mesh
///////////////////////////////////////////////////////////////////////////

zCMeshSoftSkin::zCMeshSoftSkin() {
	vertWeightStream= 0;
	iterator		= 0;
};

zCMeshSoftSkin::~zCMeshSoftSkin() {
	DeleteVertWeightStream	();
	DeleteNodeOBBList		();
};

void zCMeshSoftSkin::AllocVertWeightStream(int numSVerts, int numWeightEntrys) {
	DeleteVertWeightStream();
	int size		= numSVerts * sizeof(zTNumWeightEntry) + numWeightEntrys * sizeof(zTWeightEntry);
	vertWeightStream= zNEW(zBYTE) [size];
	iterator		= vertWeightStream;
};

void zCMeshSoftSkin::DeleteVertWeightStream() {
	delete vertWeightStream;
	vertWeightStream= 0;
	iterator		= 0;
};
 
void zCMeshSoftSkin::AddNumWeightEntry (const zTNumWeightEntry& numSVert) {
	*((zTNumWeightEntry*)iterator)	= numSVert;
	iterator += sizeof (zTNumWeightEntry);
};

void zCMeshSoftSkin::AddWeightEntry	(const zTWeightEntry& weightEntry) {
	*((zTWeightEntry*)iterator)	= weightEntry;
	iterator += sizeof (zTWeightEntry);
};


void zCMeshSoftSkin::ResetVertWeightIterator () {
	iterator=vertWeightStream;
};

int zCMeshSoftSkin::GetVertWeightStreamSize () {
	ResetVertWeightIterator();
	int size=0;

	for (int i=0; i<posList.GetNum(); i++) {
		int _numNodes = GetIterNumWeightEntry();
		size += sizeof (zTNumWeightEntry) + _numNodes * sizeof (zTWeightEntry);
		SkipIterNumWeightEntry (_numNodes);
	};
	return size;
};

void zCMeshSoftSkin::BuildNodeIndexList () {
	// Aus dem vertWeightStream alle enthaltenen NodeIndizes scannen & in 'nodeIndexList' eintragen (Menge)
	nodeIndexList.EmptyList();
	ResetVertWeightIterator();
	for (int i=0; i<posList.GetNum(); i++) {
		int numW = GetIterNumWeightEntry();
		for (int j=0; j<numW; j++) {
			int index = GetIterWeightEntry()->nodeIndex;
			if (!nodeIndexList.IsInList	(index))
				nodeIndexList.Insert	(index);
		};
	};
};

void zCMeshSoftSkin::DeleteNodeOBBList () {
	for (int i=0; i<nodeOBBList.GetNum(); i++) 
		delete nodeOBBList[i];
	nodeOBBList.DeleteList();
};

void zCMeshSoftSkin::BuildNodeOBBList () 
{
	// Vertices, die mit der Node gelinkt sind werden in dessen KS gebracht
	// Polys, die solche Verts enthalten werden in einer Liste gesammelt
	zTBBox3D nodeBox;

	for (int n=0; n<nodeIndexList.GetNum(); n++) 
	{
		int		i;
		int		nodeIndex	= nodeIndexList[n];
		zBOOL	found		= FALSE;
		ResetVertWeightIterator	();

		nodeBox.Init();
		for (i=0; i<posList.GetNum(); i++) 
		{
			int numW = GetIterNumWeightEntry();
//			for (int j=0; j<numW; j++) 
			// nur Polys registrieren, die ein Vert benutzen, dass mit einem rel. hohen Weight an Node gelinkt ist
			// => ergibt sonst zu grosse/ungenaue Boxen
//			int j=0;
			{
				zTWeightEntry	*weightEntry= GetIterWeightEntry();
				if (nodeIndex==weightEntry->nodeIndex) 
				{
					for (int w=0; w<numSubMeshes; w++)
					{
						zCSubMesh *subMesh = &(subMeshList[w]);
						for (int k=0; k<subMesh->triList.GetNum(); k++) 
						{
							if ((subMesh->wedgeList[subMesh->triList[k].wedge[0]].position == i) ||
								(subMesh->wedgeList[subMesh->triList[k].wedge[1]].position == i) ||
								(subMesh->wedgeList[subMesh->triList[k].wedge[2]].position == i))
							{
								nodeBox.AddPoint (posList[subMesh->wedgeList[subMesh->triList[k].wedge[0]].position]);
								nodeBox.AddPoint (posList[subMesh->wedgeList[subMesh->triList[k].wedge[1]].position]);
								nodeBox.AddPoint (posList[subMesh->wedgeList[subMesh->triList[k].wedge[2]].position]);
								found = TRUE;
							};
						};
					};
				};
			};
			SkipIterNumWeightEntry (numW-1);
		};

		// obbox fuer Node erzeugen
		zCOBBox3D *obb			= zNEW(zCOBBox3D	());
		obb->SetByBBox3D		(nodeBox);
		obb->Scale				(zVEC3(0.8F,0.8F,0.8F));
		nodeOBBList.InsertEnd	(obb);
		if (!found) {
			// hmm, darf soetwas sein ?
//			zERR_WARNING ("D: MSH_SS: node without obb: "+zSTRING(n));
			obb->center = 0;
			obb->extent	= zVEC3(0.0001F, 0.0001F, 0.0001F);
			obb->axis[0]= zVEC3(1,0,0);
			obb->axis[1]= zVEC3(0,1,0);
			obb->axis[2]= zVEC3(0,0,1);
		};
	};
};


// ==================================================================================================================

const zDWORD zMESHSOFTSKIN_FILE_VERS = (04);		// 8 BIT !!

static const zWORD zFCHUNK_MESHSOFTSKIN				= 0xE100;
static const zWORD		zFCHUNK_MESHSOFTSKIN_END	= 0xE110;

zWORD zCMeshSoftSkin::GetFileVersion () {
	return zWORD(zMESHSOFTSKIN_FILE_VERS);
};
	
zBOOL zCMeshSoftSkin::Load (zCFileBIN& file) {
	zWORD						id;
	zLONG						len;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
		case zFCHUNK_MESHSOFTSKIN: {
			zDWORD	vers;
			file.BinReadDWord	(vers); 
			if (vers!=zMESHSOFTSKIN_FILE_VERS) return FALSE; 

			//
			zBOOL ok = zCProgMeshProto::Load (file);
			if (!ok) return FALSE;

//			zerr.Message ("D: Load SoftSkin: v: "+zSTRING(numVert)+", p: "+zSTRING(numPoly));
			
			//
			zDWORD size;
			file.BinReadDWord	(size);
			delete[] vertWeightStream;
			vertWeightStream	= zNEW(zBYTE) [size];
			file.BinRead		(vertWeightStream, size);

			//
			zDWORD numNodeWedgeNormals;
			file.BinReadDWord				(numNodeWedgeNormals);
			nodeWedgeNormalList.EmptyList	();
			nodeWedgeNormalList.AllocAbs	(numNodeWedgeNormals);
			nodeWedgeNormalList.MarkNumAllocUsed();
			if (numNodeWedgeNormals>0)
				file.BinRead				(nodeWedgeNormalList.GetArray(), sizeof(nodeWedgeNormalList[0])*numNodeWedgeNormals);

			//
			zWORD numNodes;
			file.BinReadWord				(numNodes);
			nodeIndexList.EmptyList			();
			nodeIndexList.AllocAbs			(numNodes);
			nodeIndexList.MarkNumAllocUsed	();
			file.BinRead					(nodeIndexList.GetArray(), sizeof(nodeIndexList[0]) * numNodes);

			//
			nodeOBBList.EmptyList			();
			nodeOBBList.AllocAbs			(numNodes);
			nodeOBBList.MarkNumAllocUsed	();
			for (int i=0; i<numNodes; i++) {
				zCOBBox3D *obb	= zNEW(zCOBBox3D());
				obb->LoadBIN	(file);
				nodeOBBList[i]	= obb;
			};

			};
			break;
		case zFCHUNK_MESHSOFTSKIN_END:
			goto leave;
		default:
			file.BinSkipChunk();
		};
	};

leave:;
	return TRUE;
};

zBOOL zCMeshSoftSkin::Save (zCFileBIN& file) {
	zDWORD size;
	file.BinStartChunk	(zFCHUNK_MESHSOFTSKIN);
	{
		file.BinWriteDWord	(zMESHSOFTSKIN_FILE_VERS);
		zCProgMeshProto::Save(file);
		size				= GetVertWeightStreamSize();
		file.BinWriteDWord	(size);
		file.BinWrite		(vertWeightStream	, size);

		//
		file.BinWriteDWord	(nodeWedgeNormalList.GetNum());
		file.BinWrite		(nodeWedgeNormalList.GetArray(), sizeof(nodeWedgeNormalList[0])*nodeWedgeNormalList.GetNum());

		//
		file.BinWriteWord	(nodeIndexList.GetNum());
		file.BinWrite		(nodeIndexList.GetArray(), sizeof(nodeIndexList[0])*nodeIndexList.GetNum());
		for (int i=0; i<nodeOBBList.GetNum(); i++)
			nodeOBBList[i]->SaveBIN (file);
	};

	file.BinStartChunk	(zFCHUNK_MESHSOFTSKIN_END);
	
	zERR_MESSAGE (3, 0, "D: MDL: Saving SoftSkin, polys: "+zSTRING(GetNumTri())+", verts: "+zSTRING(posList.GetNum())+", mem: "+zSTRING(int(size)));
	return TRUE;
};

// =======================================================================================================================

zBOOL zCCFASTCALL zCMeshSoftSkin::RenderSoftSkin (zTRenderContext&			renderContext, 
												  const zCArray<zMAT4*>		&nodeTrafoList, 
												  zCRenderLightContainer	*renderLightCont,
												  zREAL						fatness) 
{
	zERR_ASSERT (renderLightCont);
	int i;

	//
	zTLODRenderArgs		lodRenderArgs;
	if (!CalcLODRenderArgs	(renderContext, lodRenderArgs)) return FALSE;

	// 1) trafo
	// Optimierung: in groesserer Entfernung werden N-Links als 1-Links behandelt
	zCMeshSoftSkin::zTWeightEntry* weightEntry;
	ResetVertWeightIterator();

	if (lodRenderArgs.vertPerc<0.6F) 
	{
		// 1 - Link
		if (fatness!=0) {
			// Fatness
			i=0;
			do {
				int			_numNodes	= GetIterNumWeightEntry();
				weightEntry				= GetIterWeightEntry ();
				int index				= weightEntry->nodeIndex;
				s_posCacheList[i]		= (*nodeTrafoList[index]) * (weightEntry->vertPosOS + posNormalList[i]*fatness);
				SkipIterNumWeightEntry	(_numNodes-1);
				i++;
			} while (i<lodRenderArgs.numPos);
		} else {
			// keine Fatness
			i=0;
			do {
				int			_numNodes	= GetIterNumWeightEntry();
				weightEntry				= GetIterWeightEntry ();
				int index				= weightEntry->nodeIndex;
				s_posCacheList[i]		= (*nodeTrafoList[index]) * (weightEntry->vertPosOS);
				SkipIterNumWeightEntry	(_numNodes-1);
				++i;
			} while (i<lodRenderArgs.numPos);
		};
	} else {
		// N - Link
		zPOINT3 resultPos;
		if (fatness!=0) {
			// Fatness
			i=0;
			do {
				int			_numNodes	= GetIterNumWeightEntry();
							resultPos	= zVEC3(0);
				for (int j=0; j<_numNodes; j++) 
				{
					weightEntry			= GetIterWeightEntry ();
					int index			= weightEntry->nodeIndex;
					resultPos			+= weightEntry->weight * ((*nodeTrafoList[index]) * (weightEntry->vertPosOS + posNormalList[i]*fatness));
				};
				s_posCacheList[i]		= resultPos;
				i++;
			} while (i<lodRenderArgs.numPos);
		} else {
			// keine Fatness
			i=0;
			do {
				int			_numNodes	= GetIterNumWeightEntry();
							resultPos	= zVEC3(0);
				for (int j=0; j<_numNodes; j++) 
				{
					weightEntry			= GetIterWeightEntry ();
					int index			= weightEntry->nodeIndex;
					resultPos			+= weightEntry->weight * ((*nodeTrafoList[index]) * weightEntry->vertPosOS);
				};
				s_posCacheList[i]		= resultPos;
				i++;
			} while (i<lodRenderArgs.numPos);
		};
	};

	// Subdiv
	// 1-Link
	if ((GetAutoSubdivEnabled()) && (lodRenderArgs.vertPerc>=1) && (HasSubdivData()))
	{
		ResetVertWeightIterator();
		i=0;
		do {
			int			_numNodes	= GetIterNumWeightEntry();
			weightEntry				= GetIterWeightEntry ();
			int index				= weightEntry->nodeIndex;
			s_posNormalCSList[i]	= (*nodeTrafoList[index]).Rotate (posNormalList[i]);
			SkipIterNumWeightEntry	(_numNodes-1);
			i++;
		} while (i<lodRenderArgs.numPos);
	};

	const zBOOL vis = RenderProgMesh (renderContext, zPM_RENDER_FLAG_PACK_DYNAMIC_VB | zPM_RENDER_FLAG_DONT_SET_TRANSFROM, &lodRenderArgs, renderLightCont);

	#ifdef zPM_DRAW_NODE_HIERARCHY_OBB
	{
		int color = GFX_BLUE;
		for (int i=0; i<nodeIndexList.GetNum(); i++) {
			zCCamera::activeCam->camMatrix    = *nodeTrafoList[nodeIndexList[i]];
			
			zCCamera::activeCam->camMatrixInv = zCCamera::activeCam->camMatrix.Inverse();
			nodeOBBList[i]->Draw(0, color); 
			color += (1 + 32 + 512);
		};
	};
	#endif

	return vis;
};



static int s_iTotalSoftSkinPolys = 0;
static int s_iTotalPMPolys		 = 0;





void zCProgMeshProto::InitSetupLowestLOD()
{
	s_posCacheIndex		= 0;
	s_posCacheCount		= 0;
	s_posCacheCountLOD	= 0;
	s_iTotalSoftSkinPolys=0;
	s_iTotalPMPolys		= 0;
};


void zCCFASTCALL zCMeshSoftSkin::SetupLowestLOD(zTRenderContext&			renderContext, 
												  const zCArray<zMAT4*>		&nodeTrafoList, 
												  zREAL						fatness, int &a_iTotalNumTri) 
{
	//
	int i;
	int s_posCacheIndexStart	= s_posCacheCountLOD;

	zTLODRenderArgs		lodRenderArgs;
	if (!CalcLODRenderArgsMin(renderContext, lodRenderArgs)) return;

	if (lodRenderArgs.numPos<3) 
	{
		a_iTotalNumTri=0;
		return;
	}

	if (!zCCamera::activeCam) return;

	zMAT4 trafoCamToWorld = zCCamera::activeCam->camMatrixInv;

	a_iTotalNumTri = 0;

	// 1) trafo
	// Optimierung: in groesserer Entfernung werden N-Links als 1-Links behandelt
	zCMeshSoftSkin::zTWeightEntry* weightEntry;
	ResetVertWeightIterator();

	if (lodRenderArgs.vertPerc<0.6F) 
	{
		// 1 - Link
		if (fatness!=0) 
		{
			// Fatness
			i=0;
			do 
			{
				int			_numNodes			= GetIterNumWeightEntry();
				weightEntry						= GetIterWeightEntry ();
				int index						= weightEntry->nodeIndex;
				s_posCacheList[s_posCacheCount++]= trafoCamToWorld * ((*nodeTrafoList[index]) * (weightEntry->vertPosOS + posNormalList[i]*fatness));
				SkipIterNumWeightEntry	(_numNodes-1);
				i++;
			} 
			while (i<lodRenderArgs.numPos);
		} 
		else 
		{
			// keine Fatness
			i=0;
			do 
			{
				int			_numNodes				= GetIterNumWeightEntry();
				weightEntry							= GetIterWeightEntry ();
				int index							= weightEntry->nodeIndex;
				s_posCacheList[s_posCacheCount++]	= trafoCamToWorld * ((*nodeTrafoList[index]) * weightEntry->vertPosOS);
				SkipIterNumWeightEntry	(_numNodes-1);
				i++;	
			} 
			while (i<lodRenderArgs.numPos);
		};
	} 
	else 
	{
		// N - Link
		zPOINT3 resultPos;
		if (fatness!=0) 
		{
			// Fatness
			i=0;
			do 
			{
				int			_numNodes			= GetIterNumWeightEntry();
							resultPos			= zVEC3(0);
				for (int j=0; j<_numNodes; j++) 
				{
					weightEntry	= GetIterWeightEntry ();
					int index	= weightEntry->nodeIndex;
					resultPos	+= weightEntry->weight * ((*nodeTrafoList[index]) * (weightEntry->vertPosOS + posNormalList[i]*fatness));
				};
				s_posCacheList[s_posCacheCount++]	= trafoCamToWorld * resultPos;
				i++;
			} 
			while (i<lodRenderArgs.numPos);
		} 
		else 
		{
			// keine Fatness
			i=0;
			do 
			{
				int			_numNodes	= GetIterNumWeightEntry();
							resultPos	= zVEC3(0);
				for (int j=0; j<_numNodes; j++) 
				{
					weightEntry	=  GetIterWeightEntry ();
					int index	=  weightEntry->nodeIndex;
					resultPos	+= weightEntry->weight * ((*nodeTrafoList[index]) * weightEntry->vertPosOS);
				};
				s_posCacheList[s_posCacheCount++]	= trafoCamToWorld * resultPos;
				i++;
			} while (i<lodRenderArgs.numPos);
		};
	};

	// nun die trianglelisten aufbauen
	int subMeshIndex		= numSubMeshes-1;
	int count				= numSubMeshes;	
	zTLODRenderArgsSubMesh	lodRenderArgsSub;
	

	if (count>0)
	do
	{
		const zCSubMesh* const subMesh	= &(subMeshList[subMeshIndex]);
		CalcLODRenderArgsSubMesh(renderContext, lodRenderArgs, subMesh, lodRenderArgsSub);
		if (lodRenderArgsSub.numTri<=0)	continue;
		a_iTotalNumTri			+= lodRenderArgsSub.numTri;
		s_iTotalSoftSkinPolys	+= lodRenderArgsSub.numTri;

		// wedgeRemap Liste erstellen (damit sie spaeter geshared werden kann)
		// a) der unmodifizierte Teil
		for (int j=0; j<lodRenderArgsSub.numWedge; j++) {
			s_wedgeRemap[j]	= j;
		};
		// b) der modifizierte Teil
		for (j=lodRenderArgsSub.numWedge; j<subMesh->wedgeList.GetNum(); j++) {
			int wedgeIndex = j;
			while (wedgeIndex>=lodRenderArgsSub.numWedge) {
				zERR_ASSERT (subMesh->wedgeMap[wedgeIndex]!=zPMINDEX_NONE);
				wedgeIndex = subMesh->wedgeMap[wedgeIndex];
			};
			s_wedgeRemap[j]	= wedgeIndex;
		};

		// IndexList erstellen

		for (j=0; j<lodRenderArgsSub.numTri; j++)
		{
			s_posCacheListLODIndices[s_posCacheIndex++] = (s_wedgeRemap[subMesh->triList[j].wedge[0]])+s_posCacheIndexStart;
			s_posCacheListLODIndices[s_posCacheIndex++] = (s_wedgeRemap[subMesh->triList[j].wedge[1]])+s_posCacheIndexStart;
			s_posCacheListLODIndices[s_posCacheIndex++] = (s_wedgeRemap[subMesh->triList[j].wedge[2]])+s_posCacheIndexStart;
		};

		// den fixen teil holen
		
		for (j=0; j<lodRenderArgsSub.numMinMorphWedge; j++)
		{
			s_posCacheListLOD[s_posCacheCountLOD++] = s_posCacheList[subMesh->wedgeList[j].position];
		};

		// der gemorphte Anteil
		for (; j<lodRenderArgsSub.numWedge; j++)
		{
			int destIndex = j;
			while (destIndex>=lodRenderArgsSub.numMinMorphWedge) 
			{
				if (subMesh->wedgeMap[destIndex]==zPMINDEX_NONE)		break;
				destIndex = subMesh->wedgeMap[destIndex];
			};
 			
			// Das lerpen macht man hier fuer jede Wedge (nicht mehr pro Wedge, pro Tri). Optimaler Fall.
			const zTPMWedge&	wedge1			= subMesh->wedgeList[j];
			const zTPMWedge&	wedge0			= subMesh->wedgeList[destIndex];
			s_posCacheListLOD[s_posCacheCountLOD++]	= zLerp (lodRenderArgs.morphFrac, s_posCacheList[wedge0.position], s_posCacheList[wedge1.position]);
		};
		subMeshIndex--;
	} 
	while(--count);
};


int		zCMeshSoftSkin::GetLowestLODNumPolys()
{
	return s_iTotalSoftSkinPolys;
};

zVEC3*	zCMeshSoftSkin::GetLowestLODPoly(const int a_iPoly, zVEC3* &normal)
{
	static zVEC3 defNormal(0,1,0);
	static zVEC3 resPoly[3];

	normal = &defNormal;

	int index = a_iPoly*3;

	if (a_iPoly>=0)
	{
		resPoly[0]=s_posCacheListLOD[s_posCacheListLODIndices[index+0]];
		resPoly[1]=s_posCacheListLOD[s_posCacheListLODIndices[index+1]];
		resPoly[2]=s_posCacheListLOD[s_posCacheListLODIndices[index+2]];
	}

	return resPoly;
};



// =======================================================================================================================

zCProgMeshConvertFileHandler::zCProgMeshConvertFileHandler() 
{
	RegisterFileType("3ds");
};

zBOOL zCProgMeshConvertFileHandler::HandleFile (const zSTRING& fname, const char* directory, _finddata_t fileinfo)
{
	zBOOL touched = FALSE;

	// Kompletten Dateinamen bauen
	zSTRING filename = zSTRING(directory) + DIR_SEPARATOR + fname;
	filename.Upper();		

	//
	if (fname.Search(".3DS")>=0) 
	{				
		// keine LevelMeshes konvertieren
		if ((filename.Search ("\\LEVEL\\")==-1) &&
			(filename.Search ("\\_DIETER\\")==-1))		// hihi..
		{
			zCVisual *pmesh			= zCProgMeshProto::LoadVisual (fname);
			if (pmesh)
			{
				pmesh->Release			();
				touched					= TRUE;
			};
		} 
	} 
	else
	{
		zERR_FAULT ("D: PMESH: Convert: Unknown filetype: "+fname);
	}

	return touched;
};

// =======================================================================================================================

/*
	Zu den zCCamera::SetTransforms():
	Alter Stand: camMatrizen werden in zCBspTree::RenderVobList() und zCVob::Render() gesetzt, ein zCVisual::Render()
	geht von gesetzten Matrizen aus. Problem: auf diesem alten Pfad wurden nur die camMatrix/camMatrixInv gesetzt, nicht 
	aber die anderen Matrizen bzw. wichtiger die zCRenderer Matrizen.
	Deshalb sind so in diesem Code folgenden beiden Zeilen aquivalent:
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLD, renderContext.vob->trafoObjToWorld);
			und
		zCCamera::activeCam->SetTransform	(zCAM_TRAFO_WORLDVIEW, renderContext.cam->camMatrix);
	Hier muss eine einheitliche/Render-weite Regeleung her. Wer setzt die Matrizen? Muessen sie aufgeraeumt werden? Setzt
	ein Visual::Render() sie selber? CAM_ALIGN_YAW/...

*/

// =======================================================================================================================

