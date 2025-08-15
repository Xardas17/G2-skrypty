/******************************************************************************** 
 
     $Workfile:: zMorphMesh.cpp       $                $Date:: 31.01.01 6:02    $
     $Revision:: 23                   $             $Modtime:: 31.01.01 6:02    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zMorphMesh.cpp $
 * 
 * 23    31.01.01 6:02 Hildebrandt
 * 
 * 22    31.01.01 5:47 Hildebrandt
 * 
 * 21    27.01.01 19:42 Moos
 * 
 * 20    28.09.00 19:20 Hildebrandt
 * 
 * 19    22.09.00 2:37 Hildebrandt
 * 
 * 18    21.09.00 21:21 Hildebrandt
 * zenGin 0.94
 * 
 * 17    7.09.00 20:41 Hildebrandt
 * 
 * 16    24.08.00 14:26 Hildebrandt
 * 
 * 15    21.08.00 17:18 Hildebrandt
 * 
 * 14    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin 
 *  
 * 13    21.07.00 15:11 Hildebrandt
 * 
 * 12    21.07.00 14:28 Hildebrandt
 * 
 * 11    11.07.00 1:13 Hildebrandt
 * zenGin 0.92e
 * 
 * 10    6.07.00 13:45 Hildebrandt
 * 
 * 7     8.05.00 2:17 Hildebrandt
 * 
 * 6     4.05.00 20:17 Hildebrandt
 * zenGin 089e
 * 
 * 5     4.05.00 3:37 Hildebrandt
 * bugfix: flipping textures on faces
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 12    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 11    23.02.00 1:19 Hildebrandt
 * 
 * 10    17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 8     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
  * 
 * 7     16.11.99 19:49 Hildebrandt
 *  
 * 6     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 23 $ ($Modtime: 31.01.01 6:02 $)


#include <zCore.h>
#include <zMorphMesh.h>
#include <zWorld.h>
#include <zModel.h>
#include <zoption.h>
#include <zFile3D.h>
#include <zView.h>

#ifdef ZENGINE_DEBUG
//	#define zDEBUG_MORPH_DONT_LOAD_MMB
#endif

zCLASS_DEFINITION	(zCMorphMesh, zCVisualAnimate, 0,0)

/*

  .msh, .pwf, man, mdm, mmb

  SoftSkins:
	x .MDM laden/speichern
	- Texture-Comb
	- Mesh Kombinierbarkeit (rein/rauswerfen)

  MorphMesh:
	* Rendern/ani optimieren
	x Kopf in Model einfuegen
	x .MMB laden/speichern
	- Konzept / Rand-Ani Params ?

	- Shape-(Ref?)-Anis: kann man noch effizienter handhaben: einfach als Anis mit hoechstem Layer,
	  Samples sind absolut und nicht als Delta gespeichert und werden dann statt der RefMesh
	  Positions draufaddiert. (muessen immer die komplette RefMesh-Vert Zahl haben !)
	  => beim Starten einer solchen Ani werden einfach die RefMesh-Positions ausgetauscht !!!
	  ? Ref-Ani		: abrupter Austausch
	  ? Shape-Ani	: smoother Shape-Shift

		- verschiedene Koepfe ??
		- verschiedene Frisuren ? Helme ??

  beide:
	x ASC-Exporter: mit einfachen Switches versehen !
	- Tex Kombinierbarkeit (Konzept!)
	- Beleuchtung
	- ASC-Importer: vertNormals !

  Model-Engine:
	x .MDL einfuehren: Mesh&Tree
	- BBox fuer einzelne Anis
	x zCModelAniInst ganz aufloesen
	- Kleinkram:
		- rootNodeIndex rauswerfen
		- fpsRate float und *1000

*/

/*
  - Half-Life	:	60MB
  - Unreal		:	60MB	/ 68MB
  - Thief		:	47MB
  - Quake2		:	35MB

  - Quake		:	500k $
  - Unreal		:	250k $
  - LithTech	:	250k $
  - Drakan		:	100k $
  - NDL			:	100k $		(sie sagen: 250k - 50k)
  - Genesis3D	:	 50k $
*/

/*
  .MMS:	Script File
  .MMB: Binary File

	ani		("s_RunL"	1	"s_RunL"	0.0	0.1	M.	"Hum_RunLoop_A01.asc"		F	12	31)

MorphMesh ("Head1") 
{

	morphRef	("Hum_RunLoop_A01.asc")
	morphAni	("eyeBlink"	2	0.0	0.1	.	"Hum_RunLoop_A01.asc" 12	31)

}

  Flags:
	R = Random				(=> eye-blink)
	D = Discontinous Play	(=> talk)
	L = Loop				(explizites Stop noetig)

	AddRandAni	("EYE_BLINK", freq, mode);
	StartAni	("EYE_BLINK", mode, blendIn, blendOut, intensity);
	StopAni		();

  RND:1.0;0.25;0.5;0.25;0.1
  max, maxVar, maxPercent
  min, minVar

  Start	(ani, intensity, 

*/


///////////////////////////////////////////////////////////////////////////
//     Morph-Mesh Animation
///////////////////////////////////////////////////////////////////////////

zCMorphMeshAni::zCMorphMeshAni() {
	numVert			= 0;
	numFrames		= 0;
	vertIndexList	= 0;
	vertPosMatrix	= 0;

	blendInSpeed	= 0;
	blendOutSpeed	= 0;
	holdTime		= 0;
	layer			= 0;
	fpsRate			= 0;
	memset			(&flags, 0, sizeof(flags));
};

zCMorphMeshAni::~zCMorphMeshAni() {
	delete[] vertIndexList;		vertIndexList=0;
	delete[] vertPosMatrix;		vertPosMatrix=0;
};

void zCMorphMeshAni::SetBlending (const zVALUE blendInSec, const zVALUE blendOutSec) {
	const zREAL ANI_BLEND_IN_ZERO	= zREAL_MAX;
	const zREAL ANI_BLEND_OUT_ZERO	=-zREAL_MAX;

	if (blendInSec==0)	blendInSpeed  = ANI_BLEND_IN_ZERO;
	else				blendInSpeed  = 1 / blendInSec;
	if (blendOutSec==0)	blendOutSpeed = ANI_BLEND_OUT_ZERO;
	else				blendOutSpeed =-1 / blendOutSec;
	blendInSpeed		/= zREAL(1000.0F);
	blendOutSpeed		/= zREAL(1000.0F);
};

void zCMorphMeshAni::Load (zCFileBIN& file) {
	file.BinReadString	(aniName);
	file.BinReadFloat	(blendInSpeed);
	file.BinReadFloat	(blendOutSpeed);
	file.BinReadFloat	(holdTime);
	file.BinReadInt		(layer);
	file.BinReadFloat	(fpsRate);
	file.BinRead		(&flags, sizeof(flags));
	file.BinReadInt		(numVert);
	file.BinReadInt		(numFrames);
	delete[] vertIndexList;
	delete[] vertPosMatrix;
	vertIndexList		= zNEW(int	  )	[numVert];
	vertPosMatrix		= zNEW(zPOINT3)	[numVert*numFrames];
	file.BinRead		(vertIndexList, sizeof(vertIndexList[0])*numVert);
	file.BinRead		(vertPosMatrix, sizeof(vertPosMatrix[0])*numVert*numFrames);

};

void zCMorphMeshAni::Save (zCFileBIN& file) {
	file.BinWriteString (aniName);
	file.BinWriteFloat	(blendInSpeed);
	file.BinWriteFloat	(blendOutSpeed);
	file.BinWriteFloat	(holdTime);
	file.BinWriteInt	(layer);
	file.BinWriteFloat	(fpsRate);
	file.BinWrite		(&flags, sizeof(flags));
	file.BinWriteInt	(numVert);
	file.BinWriteInt	(numFrames);
	file.BinWrite		(vertIndexList, sizeof(vertIndexList[0])*numVert);
	file.BinWrite		(vertPosMatrix, sizeof(vertPosMatrix[0])*numVert*numFrames);
};

///////////////////////////////////////////////////////////////////////////
//     Morph-Mesh Prototype
///////////////////////////////////////////////////////////////////////////
/*
static int CompareMorphProtoAniNames ( const void *arg1, const void *arg2 ) {
	zCMorphMeshAni* ani1 = *((zCMorphMeshAni**)arg1);
	zCMorphMeshAni* ani2 = *((zCMorphMeshAni**)arg2);
	return ani1->GetName().CompareTo (ani2->GetName());
};
*/

zCMorphMeshProto*	zCMorphMeshProto::morphRoot				= 0; 
zBOOL				zCMorphMeshProto::autoConvertBinaryFile	= FALSE;

zCMorphMeshProto::zCMorphMeshProto () {
//	aniList.SetCompare (CompareMorphProtoAniNames);
	morphRefMesh		= 0;
	morphRefMeshVertPos	= 0;
	//
	refCtr				= 1;

	// insert into list
	prev				= 0;
	next				= morphRoot;
	if (morphRoot)		
	morphRoot->prev		= this;
	morphRoot			= this;
	//
	morphProtoName		= zSTRING((int)this);		// safety

	m_bAlphaTestingEnabled = FALSE;
};

zCMorphMeshProto::~zCMorphMeshProto	() 
{
	// shared Object
	refCtr--;
	if (refCtr!=0) zERR_FATAL ("D:zCMorphMeshProto(zCMorphMeshProto::Destructor): Reference-Ctr not zero !");

	zERR_MESSAGE (7,0, "D: MORPH: Deleting MorphMeshProto..");

	//
	for (int i=0; i<aniList.GetNum(); i++)	delete aniList[i];
	aniList.EmptyList();

	// data
	zRELEASE (morphRefMesh);
	delete[] morphRefMeshVertPos; morphRefMeshVertPos=0;

	// delete from list
	if (this==morphRoot) morphRoot= next; else
	if (prev) prev->next	= next;
	if (next) next->prev	= prev;
	prev = next = 0;
};

// new	 : ref=1,
// delete: nur möglich wenn ref>=1; (macht selbst refCtr--);
int zCMorphMeshProto::Release () {
	refCtr--;								
	int c = refCtr;
	if (c<=0) { refCtr++; delete this; };
	return c;
};

zCMorphMeshProto* zCMorphMeshProto::SearchName (const zSTRING& name) {
	zCMorphMeshProto *model = morphRoot;
	while ((model) && (model->GetProtoName()!=name)) model = model->next;
	return model;
};

zCMorphMeshProto* zCMorphMeshProto::Load (const zSTRING& name) {
	// a) bereits im Speicher
	zPATH	morphPath (name);
	zSTRING morphName = morphPath.GetFilename();
	morphName.Upper();

	zCMorphMeshProto *morphProto = zCMorphMeshProto::SearchName (morphName);
	if (morphProto) {
//		zerr.Message ("D: MORPH: Sharing MorphProto: "+zSTRING(morphName));
		return morphProto->AddRef();
	};

	morphProto = zNEW(zCMorphMeshProto());

#ifndef zDEBUG_MORPH_DONT_LOAD_MMB
	// b) als .mmb auf HD (internes Bin-Format)
	zBOOL found = morphProto->LoadMMB	(morphName+".mmb"); 
	if (found) return morphProto;
#endif

	// c) als .mms auf HD (Script-Format + 3dsMax ASCII)
	morphProto->LoadMorphScript			(morphName+".mms"); 
	morphProto->SaveMMB					(morphName+".mmb");

	return morphProto;
};

zCMorphMeshAni* zCMorphMeshProto::SearchAni (const zSTRING& aniName) {
	// FIXME: binaere Suche
	for (int i=0; i<aniList.GetNum(); i++)
		if (aniList[i]->aniName==aniName) return aniList[i];
	return 0;
};

// ==================================================================================================================

const zDWORD zMMB_VERS = (03);

static const zWORD zFCHUNK_MMB_MORPHMESH			= 0xE000;
static const zWORD		zFCHUNK_MMB_SOURCE			= 0xE010;
static const zWORD		zFCHUNK_MMB_HEADER			= 0xE020;
static const zWORD		zFCHUNK_MMB_ANILIST			= 0xE030;

zBOOL zCMorphMeshProto::LoadMMB (const zSTRING& fileName) 
{
//	zoptions->ChangeDir (DIR_COMPILED_ANIMS); 
	// [BENDLIN] Addon Patch - MorphMeshes im Soundverzeichnis
	zCFileBIN file(zoptions->GetDirString(DIR_COMPILED_ANIMS) + fileName);
	// noch nicht ins interne Format konvertiert ?
	if (!file.BinExists()) {
		file.BinClose ();
		return FALSE;
	};

	file.BinOpen	();
	zERR_MESSAGE	(3, zERR_BEGIN, "D: MORPH: Loading MorphMesh: "+fileName);

	zWORD id;
	zLONG len;
	while (!file.BinEof()) { 
		file.BinOpenChunk (id, len);
		switch (id) { 
		case zFCHUNK_MMB_HEADER: {
			// Version
			zDWORD vers;
			file.BinReadDWord		(vers);
			if (vers!=zMMB_VERS) goto convertASC;

			file.BinReadString		(morphProtoName);

			// MorphRefMesh
			if (morphRefMesh)		morphRefMesh->Release();
			morphRefMesh			= zNEW(zCProgMeshProto());
			zBOOL ok				= morphRefMesh->Load (file);
			if (!ok) goto convertASC;
			
			this->m_bAlphaTestingEnabled = morphRefMesh->GetAlphaTestingEnabled();

//morphRefMesh->SetStaticLight (zCOLOR(255,255,255,255)); 
//morphRefMesh->ResetLightDynToLightStat();

			//
			delete[] morphRefMeshVertPos;
			morphRefMeshVertPos		= zNEW(zPOINT3) [morphRefMesh->GetNumVert()];
			file.BinRead			(morphRefMeshVertPos, sizeof(morphRefMeshVertPos[0])*morphRefMesh->GetNumVert());
			};
			break;
		case zFCHUNK_MMB_SOURCE: {
			if (!GetAutoConvertBinaryFiles()) {
				file.BinSkipChunk();
				break;
			};
			zWORD	numAni;
			zSTRING	ascName;
			file.BinReadWord	(numAni);
			zoptions->ChangeDir		(DIR_ANIMS);
			for (int i=0; i<numAni; i++) 
			{
				if (!file.BinReadCompareSrcFileStats ()) goto convertASC;
			}
			};
			break;
		case zFCHUNK_MMB_ANILIST: {
			zWORD numAni;
			file.BinReadWord	(numAni);
			aniList.EmptyList	();
			aniList.AllocAbs	(numAni);
			for (int i=0; i<numAni; i++) {
				zCMorphMeshAni *ani = zNEW(zCMorphMeshAni());
				ani->Load			(file);
				aniList.InsertEnd	(ani);
			};
			};
			break;
		default:
			file.BinSkipChunk();
		};
	}

	zERR_MESSAGE	(3, zERR_END, "");

	// cleanup
	file.BinClose ();
	return 1;

convertASC:;
	file.BinClose ();
	return 0;
};

void zCMorphMeshProto::SaveMMB (const zSTRING& fileName) {
	int i;

//	zSTRING fileName	= GetName ();
	zerr.Message		("D: MORPH: Saving MorphMesh: "+fileName);
	zoptions->ChangeDir		(DIR_COMPILED_ANIMS);
	
	zCFileBIN file;
	file.BinCreate		(fileName); 
	file.BinStartChunk	(zFCHUNK_MMB_MORPHMESH);

	// HEADER
	file.BinStartChunk	(zFCHUNK_MMB_HEADER);
	{
		file.BinWriteDWord		(zMMB_VERS);
		file.BinWriteString		(morphProtoName);
		morphRefMesh->Save		(file);
		file.BinWrite			(morphRefMeshVertPos, sizeof(morphRefMeshVertPos[0])*morphRefMesh->GetNumVert());
	};

	// SOURCE
	file.BinStartChunk	(zFCHUNK_MMB_SOURCE);
	{
		zoptions->ChangeDir		(DIR_ANIMS);
		file.BinWriteWord	(aniList.GetNum());
		for (i=0; i<aniList.GetNum(); i++) {
			file.BinWriteSrcFileStats (aniList[i]->ascName);
		};
	}

	// ANILIST
	file.BinStartChunk	(zFCHUNK_MMB_ANILIST);
	{
		file.BinWriteWord	(aniList.GetNum());
		for (i=0; i<aniList.GetNum(); i++) 
			aniList[i]->Save (file);
	};
};

// ===================================================================================================
// ===================================================================================================

// Load MorphScript
static const zSTRING	trenn	(" \t\r");
static const zSTRING	skip	(" \t\r");
static zFILE			*mfile;
static zSTRING			line;

static void CutMarks (zSTRING& arg) {
	arg.Delete ("\"", zSTR_TO);
	arg.Delete ("\"", zSTR_FROM);
};

zCMorphMeshAni* zCMorphMeshProto::GenerateMorphAni (zCMesh *meshRoot, const zCArray<int> &posListRemap, zBOOL isRefShape) 
{
	if (!meshRoot) return 0;
	// morphRefMesh
	// meshRoot
	int i;

	zCMorphMeshAni* ani = zNEW(zCMorphMeshAni());
	ani->numFrames		= 0;
	ani->numVert		= 0;

// morphRefMesh: soll mehr verts haben koennen als ani-Meshes

	// Menge der animierten Vertices ermitteln
	// dazu alle Ani-Mesh-Frames durchlaufen
	zCArray<int>	vertIndexList(morphRefMesh->GetNumVert());
	zCMesh			*mesh = meshRoot;
	while (mesh) {
		if (isRefShape) {
			if ((mesh->numVert!=morphRefMesh->GetNumVert()) || (mesh->numPoly!=morphRefMesh->GetNumTri()))
				zERR_FATAL ("D: (zCMorphMeshProto::GenerateMorphAni): verts/polys of refShapeAni differ from morphRef-mesh");
		} else {
			if ((mesh->numVert>morphRefMesh->GetNumVert()) || (mesh->numPoly>morphRefMesh->GetNumTri()))
				zERR_FATAL ("D: (zCMorphMeshProto::GenerateMorphAni): animated mesh has more verts/polys than morphRef-mesh");
		};

		// Vertex Differenz ermitteln
		for (int i=0; i<mesh->numVert; i++) 
		{
			if (posListRemap[i]>=mesh->numVert)
				zERR_FATAL ("D: (zCMorphMeshProto::GenerateMorphAni): animated mesh and morphRef-mesh do not match");
			const zPOINT3& pos1 = mesh->Vertex(posListRemap[i])->position;
			const zPOINT3& pos2 = morphRefMesh->posList[i];
			if ((isRefShape) ||
				(!pos1.IsEqualEps (pos2)) && (!vertIndexList.IsInList (i)))
			{
				vertIndexList.Insert (i);
			};
		};
		ani->numFrames++;
		mesh = zDYNAMIC_CAST<zCMesh>(mesh->GetNextLODVisual());
//		zERR_ASSERT_STRICT (mesh);
	};

	// 
	if (vertIndexList.GetNum()<=0) {
//		zerr.Report (zERR_WARN, 1000, "D: zMorphMesh(zCMorphMeshProto::GenerateMorphAni): ani is equal to morphRef mesh");
		// Eine Ani, bei der kein einziger Vert bewegt wurde ist verdaechtig 
		// und wahrscheinlich eine 'neutral' ani => alle Verts als animiert kennzeichnen.
		// Allerdings nur, wenn die Ani nur einen Frame hat..
		if (ani->numFrames==1) {
			for (int i=0; i<meshRoot->numVert; i++) {
				vertIndexList.Insert (i);
			};
		} else {
			delete ani;
			return 0;
		};
	};

//	zerr.Message ("D: numVerts: "+zSTRING(vertIndexList.GetNum()));

	// 
	ani->numVert		= vertIndexList.GetNum();
	ani->vertIndexList	= zNEW(int	  )	[ani->numVert];
	ani->vertPosMatrix	= zNEW(zPOINT3)	[ani->numVert * ani->numFrames];
	for (i=0; i<ani->numVert; i++) {
		ani->vertIndexList[i] = vertIndexList[i];
	};
	mesh = meshRoot;
	int ctr=0;
	for (i=0; i<ani->numFrames; i++) {
		for (int j=0; j<ani->numVert; j++) 
		{
			// Differenzen zur Neutral-Pose speichern
			if (isRefShape) {
				ani->vertPosMatrix[ctr] = mesh->Vertex(posListRemap[ani->vertIndexList[j]])->position;
			} else {
	//			ani->vertPosMatrix[ctr] = mesh->vertList[ani->vertIndexList[j]]->position;
	//			ani->vertPosMatrix[ctr] = morphRefMesh->vertList[ani->vertIndexList[j]]->position - mesh->vertList[ani->vertIndexList[j]]->position;
				ani->vertPosMatrix[ctr] = mesh->Vertex(posListRemap[ani->vertIndexList[j]])->position - morphRefMesh->posList[ani->vertIndexList[j]];
			};
			ctr++;
		};
		mesh = (zCMesh*)mesh->GetNextLODVisual();
	};

	return ani;
};


zCMesh* zCMorphMeshProto::Load3DSMAXAsc (const zSTRING& ascName, zREAL &fpsRate, int firstFrame, int lastFrame) 
{
	zCModelAni *aniPtr		= 0;
	zSTRING		aniName		= 0;

	zERR_MESSAGE(5,0,"D: MORPH: Parsing ASC \""+ascName+"\"");

	zCModelPrototype *modelProto = zNEW(zCModelPrototype()); 
	modelProto->SetModelProtoName	(ascName);
	modelProto->Load3DSMAXAsc		(aniPtr, ascName, aniName, firstFrame, lastFrame, 
									 zMDL_MAX_IMPORT_MESH | 
									 zMDL_MAX_IMPORT_TREE | 
									 zMDL_MAX_IMPORT_PASS_ZCMESH);
	
	// Node mit mesh suchen
	zCMesh *mesh=0;
	for (int i=0; i<modelProto->GetNodeList().GetNum(); i++) {
		if (modelProto->GetNodeList()[i]->visual) { 
			mesh = (zCMesh*)modelProto->GetNodeList()[i]->visual->AddRef(); 
			break; 
		}; 
	};

	fpsRate = 1.0F;
	if (aniPtr)
	fpsRate = zREAL(aniPtr->GetFPSRate());

	modelProto->Release				();
	zRELEASE(aniPtr);

	return mesh;
};

void zCMorphMeshProto::ReadMorphRef (zCArray<int> &posListRemap) {
	line.Delete ("\"", zSTR_TO);
	line.Delete ("\"", zSTR_FROM);
	zSTRING ascName = line;

	// RefMesh laden
	zREAL	fpsRate;
	zCMesh	*sourceMesh	= Load3DSMAXAsc (ascName, fpsRate);

	// ProgMesh erzeugen
	zRELEASE			(morphRefMesh);							// safety
	morphRefMesh		= zNEW(zCProgMeshProto);
	morphRefMesh->BuildProgMeshProto	(	sourceMesh, 
											morphRefMesh, 
											&posListRemap, 
											zPM_BUILD_FLAG_NO_TRIPLANES				| 
											zPM_BUILD_FLAG_FORCE_SMOOTH_NORMALS		| 
											zPM_BUILD_FLAG_DONT_REMOVE_DEGEN_POLYS	|
											zPM_BUILD_FLAG_CREATE_SUBDIV_DATA
											);
	sourceMesh->Release	();

	// LOD Params setzen => FIXME: TEMP!
	zCProgMeshProto::zTLODParams lodParams;
	morphRefMesh->GetLODParams	(lodParams);
	lodParams.strength			= 0.35F;			// 0.08F; 
	lodParams.morphPerc			= 0.03F;
	morphRefMesh->SetLODParams	(lodParams);

	morphRefMeshVertPos = zNEW(zPOINT3) [morphRefMesh->GetNumVert()];
	for (int i=0; i<morphRefMesh->GetNumVert(); i++)
		morphRefMeshVertPos[i] = morphRefMesh->posList[i];
};

void zCMorphMeshAni::SetFlagsByString (const zSTRING& flagString) {
	flags.discontinuity	= flagString.Search ("D")!=-1;
	flags.looping		= flagString.Search ("L")!=-1;
	flags.shape			= flagString.Search ("S")!=-1;		if (flags.shape)	layer = 999;
	flags.refShape		= flagString.Search ("R")!=-1;
};

void zCMorphMeshProto::ReadMorphAni (const zCArray<int> &posListRemap) 
{
	zSTRING arg		= line;
	arg.Delete		("(", zSTR_TO);
	arg.Delete		(")", zSTR_FROM);

	zCMorphMeshAni	*ani = 0;
	zREAL			fpsRate;
	zSTRING			ascName;
	int				firstFrame, lastFrame;
	zBOOL			isRefShape;
	ascName			= arg.PickWord ( 7, trenn, skip);	CutMarks (ascName);
	firstFrame		= arg.PickWord ( 8, trenn, skip).ToInt();
	lastFrame		= arg.PickWord ( 9, trenn, skip).ToInt();
	isRefShape		= arg.PickWord ( 6, trenn, skip).Search("R")!=-1;

	zCMesh *meshRoot= 0;
	meshRoot		= Load3DSMAXAsc		(ascName, fpsRate, firstFrame, lastFrame);
	ani				= GenerateMorphAni	(meshRoot, posListRemap, isRefShape);
	if (ani) {
		zERR_MESSAGE(8,0,"D: MORPH: ani...");
		zSTRING			flagString;
		zREAL			blendIn, blendOut;
		ani->aniName			= arg.PickWord ( 1, trenn, skip);	CutMarks (ani->aniName);
		ani->layer				= arg.PickWord ( 2, trenn, skip).ToInt();
		blendIn					= arg.PickWord ( 3, trenn, skip).ToFloat(); 
		ani->holdTime			= arg.PickWord ( 4, trenn, skip).ToFloat() * zREAL(1000.0F); 
		blendOut				= arg.PickWord ( 5, trenn, skip).ToFloat();
		flagString				= arg.PickWord ( 6, trenn, skip);
		ani->fpsRate			= fpsRate / zREAL(1000.0F);
		ani->SetBlending		(blendIn, blendOut);
		ani->SetFlagsByString	(flagString);
		ani->flags.looping		= (ani->holdTime<0); 
		ani->ascName			= ascName;
		aniList.Insert (ani);

		//
		int spos = arg.Search("SPD:");
		if (spos!=-1) {
			zSTRING tmp		(arg);
			tmp.Delete		("SPD:", zSTR_TO); 
			ani->fpsRate	= tmp.ToFloat() / zREAL(1000.0F);
		};
	};

	// Mesh-Ani wieder freigeben
	while (meshRoot) {
		zCMesh* mesh	= meshRoot;
		meshRoot		= (zCMesh*)meshRoot->GetNextLODVisual();
		mesh->Release();
	};
};

void zCMorphMeshProto::LoadMorphScript (const zSTRING& filename) 
{
	// Ort suchen, an dem sich das MDS befindet..

	zSTRING fname	= filename;
	fname.Upper		();
	zPATH mdsPath;
	zoptions->ChangeDir (DIR_ANIMS);
	if (mdsPath.SearchFile(fname, zSTRING(zFILE::GetCurrentDir()))!=zERR_NONE) {
		// MDS nicht gefunden
		zERR_FATAL ("D: zMorphMesh(zCMorphMeshProto::LoadmorphScript): MMS not found: "+fname);
	};

	// Hier wird implizit der aktuelle Pfad gesetzt, nachfolgende Routinen suchen ihre
	// Files in diesem aktuellem Pfad.
	zERR_MESSAGE	(3, zERR_BEGIN, "D: MORPH: Loading Morph-Script '"+filename+"' ...");
	zSTRING ascPath = mdsPath.GetDrive() + ":" + mdsPath.GetDir() + "\\"; 
	mfile			= zfactory->CreateZFile (mdsPath.GetPath());
	mfile->Open		();
	
	// morph-Name setzen
	SetProtoName	(mdsPath.GetFilename());
	zCArray<int>	posListRemap;

	while (!mfile->Eof()) { 
		mfile->Read (line);
		line.Upper();
			 if (line.Search ("//"			)!=-1) continue;
		else if (line.Search ("MORPHMESH"	)!=-1) {}
		else if (line.Search ("MORPHREF"	)!=-1) ReadMorphRef (posListRemap);
		else if (line.Search ("MORPHANI"	)!=-1) ReadMorphAni (posListRemap);
	};

	// Cleanup
	mfile->Close();
	delete mfile; mfile=0;

	zERR_MESSAGE (3, zERR_END, "");
};


///////////////////////////////////////////////////////////////////////////
//     Morph-Mesh 
///////////////////////////////////////////////////////////////////////////

// FIXME: nach alleinigem Default-Constr. ist die Klasse recht wackelig...

static int CompareMorphMeshAniLayer ( const void *arg1, const void *arg2 ) {
	zCMorphMeshAni* ani1 = (*((zCMorphMesh::zTMorphAniEntry**)arg1))->ani; 
	zCMorphMeshAni* ani2 = (*((zCMorphMesh::zTMorphAniEntry**)arg2))->ani;
	if (ani1->GetLayer()<ani2->GetLayer())	return -1;
	if (ani1->GetLayer()>ani2->GetLayer())	return +1;
	else									return  0;
};

void zCMorphMesh::Init() {
	morphProto	= 0;
	morphMesh	= 0;
	refShapeAni	= 0;
	SetAlphaTestingEnabled(FALSE);
};

zCMorphMesh::zCMorphMesh(zCMorphMeshProto* morphMeshProto) {
	Init();

	aniChannels.SetCompare (CompareMorphMeshAniLayer);
	morphProto	= morphMeshProto->AddRef();
	morphMesh	= (zCProgMeshProto*)morphProto->morphRefMesh->AddRef();
	texAniState.BuildTexListFromProgMesh (morphMesh);
};

zCMorphMesh::~zCMorphMesh() 
{
	zRELEASE (morphProto);
	zRELEASE (morphMesh);

	//
	for (int i=0; i<aniChannels.GetNum(); i++)	delete aniChannels[i];
	aniChannels.EmptyList();
};

zCMorphMesh* zCMorphMesh::Load (const zSTRING& name) 
{
	zCMorphMeshProto *proto = zCMorphMeshProto::Load (name);		// AddRef
	if (!proto) return 0;
	zCMorphMesh* res		= zNEW(zCMorphMesh(proto));				// AddRef
	res->SetAlphaTestingEnabled(proto->m_bAlphaTestingEnabled);
	proto->Release			();										// Release
	return res;
};

const zSTRING* zCMorphMesh::GetFileExtension (int i)
{
	if (i!=0) return 0;
	static const zSTRING ext(".MMS");
	return &ext;
};

zCVisual* zCMorphMesh::LoadVisualVirtual (const zSTRING& visualName) const
{
	return zCMorphMesh::Load (visualName);
};

// =====================================================================================

zTBBox3D zCMorphMesh::GetBBox3D () {
	if (!morphMesh) { 
		zTBBox3D bbox;
		bbox.InitZero();
		return bbox;
	};
	assert (morphMesh);
	return morphMesh->GetBBox3D();
};

zSTRING zCMorphMesh::GetVisualName () {
	return morphProto->GetProtoName() + ".MMS";
};

zCMorphMeshAni* zCMorphMesh::SearchAni (const zSTRING& aniName) {
	return morphProto->SearchAni (aniName);
};

zBOOL zCMorphMesh::Render (zTRenderContext& renderContext) {
	return Render (renderContext, 0);
};

zBOOL zCMorphMesh::Render (zTRenderContext&					renderContext, 
						   zCRenderLightContainer*			renderLightCont,
						   zREAL							fatness,
						   zREAL							scale) 
{
	if (!morphMesh) return FALSE;
	zCProgMeshProto::zTLODRenderArgs	lodRenderArgs;
	if (!morphMesh->CalcLODRenderArgs(renderContext, lodRenderArgs)) return FALSE;

	// LOD: bei geringer Bildschirmgroesse werden die Animationen nicht abgespielt
	// (Prozent-Anteil der Vertices)
	if (lodRenderArgs.vertPerc>0.5F) {
		AdvanceAnis					();
		CalcVertPositions			();
	};
	texAniState.UpdateTexList		();

	return morphMesh->RenderProgMesh	(renderContext, 
										 zPM_RENDER_FLAG_PACK_DYNAMIC_VB | zPM_RENDER_FLAG_SW_TRAFO_VERTS, 
										 &lodRenderArgs, 
										 renderLightCont, 
										 fatness, 
										 scale);
};

void zCMorphMesh::CalcVertPositions () {
	int i;

	for (i=0; i<morphMesh->GetNumVert(); i++) 
		morphMesh->posList[i] = zVEC3(0);

	for (i=0; i<aniChannels.GetNum(); i++) 
	{
		zTMorphAniEntry	*entry			= aniChannels[i];
		zCMorphMeshAni	*ani			= entry->ani;
//		zREAL			weight			= entry->weight;
		zREAL			weight			= zSinusEase (entry->weight);
						weight			= zSinusEase (weight);
		zREAL			weight1M		= zREAL(1.0F) - weight;
		zPOINT3			*vertPosAni		= ani->vertPosMatrix + (entry->actFrameInt * ani->numVert);

		if (ani->flags.shape)	weight1M = 1.0F;

		zVEC3 delta;
		if (ani->numFrames<=1) 
		{
			for (int j=0; j<ani->numVert; j++) {
/*				zCVertex	*vert		= morphMesh->vertList[ani->vertIndexList[j]];
				if (vert->transformed!=-2) {
					vert->position		= vertPosAni[j] * weight;
					vert->transformed	= -2;
				} else {
					vert->position		= (weight1M * vert->position) + (weight * vertPosAni[j]);
				};*/
				zPOINT3& vertPos	= morphMesh->posList[ani->vertIndexList[j]];
				delta				= vertPosAni[j] * weight;
				vertPos				= weight1M * vertPos + delta;
			};
		} else 
		{
			// zwischen den Frames lerpen
			zREAL		frac			= entry->frac;
			zPOINT3		*vertPosAniNext	= ani->vertPosMatrix + (entry->nextFrameInt* ani->numVert);

			for (int j=0; j<ani->numVert; j++) {
/*				zCVertex	*vert		= morphMesh->vertList[ani->vertIndexList[j]];
				delta					= vertPosAni[j] + frac*(vertPosAniNext[j] - vertPosAni[j]);
				delta					= delta * weight;
				if (vert->transformed!=-2) {
					vert->position		= delta;
					vert->transformed	= -2;
				} else {
					vert->position		= (weight1M * vert->position) + (delta);
				};*/
				zPOINT3& vertPos	= morphMesh->posList[ani->vertIndexList[j]];
				delta				= vertPosAni[j] + frac*(vertPosAniNext[j] - vertPosAni[j]);
				delta				= delta * weight;
				vertPos				= weight1M * vertPos + delta;
			};
		};
	};

	if (refShapeAni) {
		for (i=0; i<refShapeAni->numVert; i++) {
			morphMesh->posList[i]	+= refShapeAni->vertPosMatrix[i];
		};
	} else {
		for (i=0; i<morphMesh->GetNumVert(); i++) 
			morphMesh->posList[i]	+= morphProto->morphRefMeshVertPos[i];
	};

/*	for (i=0; i<morphMesh->numVert; i++) {
		zCVertex *vert = morphMesh->vertList[i];
		if (vert->transformed==-2)	vert->position += morphProto->morphRefMeshVertPos[i];
		else						vert->position  = morphProto->morphRefMeshVertPos[i];
	};*/
};

void zCMorphMesh::AdvanceAnis () {
	for (int i=0; i<aniChannels.GetNum(); i++) 
	{
		zTMorphAniEntry *entry	= aniChannels[i];
		zCMorphMeshAni	*ani	= entry->ani;
		
		// weight
		if (entry->blendState==zMORPH_BLEND_STATE_FADEIN) {
			entry->weight			+= entry->blendInSpeed * ztimer.GetFrameTimeF();
			if (entry->weight>=entry->weightDest) {
				entry->weight		= entry->weightDest;
				entry->blendState	= zMORPH_BLEND_STATE_CONST;
			};
		} else
		if (entry->blendState==zMORPH_BLEND_STATE_CONST) {
			if (!ani->flags.looping) {
				if (entry->holdTime>0) {
					entry->holdTime		-= ztimer.GetFrameTimeF();
				} else { 
					entry->blendState	= zMORPH_BLEND_STATE_FADEOUT;
				};
			};
		} else {
			entry->weight			+= entry->blendOutSpeed * ztimer.GetFrameTimeF();
			if (entry->weight<=0) {
				delete aniChannels[i];
				aniChannels.RemoveOrderIndex (i);
				i--;
				continue;
			};
		};

		// frame
		if (ani->numFrames>1) {
			entry->actFrame += ani->fpsRate * ztimer.GetFrameTimeF();
			// wrap
			while (entry->actFrame>=ani->numFrames)
				entry->actFrame -= ani->numFrames;
			
			// actFrameInt und nextFrameInt bestimmen
			zREAL actFrameFloor	= zFloor		(entry->actFrame);
			int	  actFrameInt	= zFloat2Int	(actFrameFloor);
			entry->frac			= entry->actFrame - actFrameFloor;

			// Discontinuity Play: soll der naechste Frame zufaellig gewaehlt werden ?
			if (ani->flags.discontinuity) {
				if (actFrameInt!=entry->actFrameInt) {
					// der alte NextFrame wird der neue ActFrame
					actFrameInt		= entry->nextFrameInt;
					entry->actFrame = zREAL(actFrameInt) + entry->frac;
					do {
						entry->nextFrameInt = zFloat2Int( zFloor(zRandF() * zREAL(ani->numFrames)) );
					} while (entry->nextFrameInt==actFrameInt);
				};
			} else {
				entry->nextFrameInt = actFrameInt+1;
				if (entry->nextFrameInt>=ani->numFrames) entry->nextFrameInt=0;
			};
			entry->actFrameInt = actFrameInt;
		};
	};

	// RandAnis
	ProcessRandAnis();
};

zBOOL zCMorphMesh::IsAniActive (const zSTRING& aniName) {
	return IsAniActive (SearchAni(aniName));
};

zBOOL zCMorphMesh::IsAniActive (zCMorphMeshAni	*ani) {
	if (!ani) return FALSE;
	for (int i=0; i<aniChannels.GetNum(); i++) {
		if (aniChannels[i]->ani==ani) return TRUE;
	};
	return FALSE;
};

void zCMorphMesh::StopAni (const zSTRING& aniName) {
	StopAni (SearchAni (aniName));
};

void zCMorphMesh::StopAni (zCMorphMeshAni *ani) {
	if (!ani) return;
	for (int i=0; i<aniChannels.GetNum(); i++) {
		if (aniChannels[i]->ani==ani) {
			delete aniChannels[i];
			aniChannels.RemoveOrderIndex (i);
			break;
		};
	};
};

void zCMorphMesh::FadeOutAni (const zSTRING& aniName) {
	FadeOutAni (SearchAni(aniName));
};

void zCMorphMesh::FadeOutAni (zCMorphMeshAni *ani) {
	if (!ani) return;
	for (int i=0; i<aniChannels.GetNum(); i++) {
		if (aniChannels[i]->ani==ani) {
			aniChannels[i]->blendState	= zMORPH_BLEND_STATE_FADEOUT;
			break;
		};
	};
};

const zSTRING* zCMorphMesh::GetAnyAnimation ()
{
	if (!morphProto)						return 0;
	if (morphProto->aniList.GetNum()<=0)	return 0;
	return &(morphProto->aniList[0]->GetName());
};

void zCMorphMesh::StartAni (const zSTRING& aniName, zREAL intensity, zREAL holdTime) {
	StartAni (SearchAni (aniName), intensity, holdTime);
};

void zCMorphMesh::StartAni (zCMorphMeshAni	*ani, zREAL intensity, zREAL holdTime) {
	if (!ani) return;

	// refShapeAni ?
	if (ani->flags.refShape) {
		refShapeAni = ani;
		return;
	};

	// Channel suchen
	zBOOL leave = FALSE;
	for (int i=0; i<aniChannels.GetNum(); i++) {
		// laeuft Ani bereits ? => direkt rausspringen, oder falls ani ausfadet, diese wieder einfaden
		if (aniChannels[i]->ani==ani) {
			if (aniChannels[i]->blendState==zMORPH_BLEND_STATE_FADEOUT)
				aniChannels[i]->blendState	= zMORPH_BLEND_STATE_FADEIN;
			leave = TRUE;
			continue;
		};
		// Anis im selben Layer werden ausgefadet
		if (aniChannels[i]->ani->GetLayer()==ani->GetLayer()) 
		{
			aniChannels[i]->blendState	= zMORPH_BLEND_STATE_FADEOUT;
		} else
		// Eine neue Ani wird hinter allen bereits laufenden Anis desselben Layers gelegt
		if (aniChannels[i]->ani->GetLayer()>ani->GetLayer()) {
			break;
		};
	};
	if (leave) return;

	zTMorphAniEntry *aniEntry= zNEW(zTMorphAniEntry);
	aniEntry->ani			= ani;
	aniEntry->actFrame		= 0.0F;
	aniEntry->actFrameInt	= 0;
	aniEntry->nextFrameInt	= 1;
	aniEntry->frac			= 0;
	aniEntry->weight		= 0.0F;
	aniEntry->weightDest	= intensity;
	aniEntry->holdTime		= (holdTime==zREAL(-2)) ? ani->holdTime : holdTime;
	aniEntry->blendInSpeed	= ani->blendInSpeed;
	aniEntry->blendOutSpeed	= ani->blendOutSpeed;
	aniEntry->blendState	= zMORPH_BLEND_STATE_FADEIN;

	aniChannels.InsertAtPos (aniEntry, i);
};

// *****************
//	Rand Anis
// *****************


void zCMorphMesh::RemoveRandAni		(zCMorphMeshAni *ani) {
	if (!ani) return;
	for (int i=0; i<randAniList.GetNum(); i++) {
		if (randAniList[i].randAni==ani) {
			randAniList.RemoveIndex (i);
			break;
		};
	};
};

void zCMorphMesh::AddRandAni(zCMorphMeshAni *ani, 
							 const zREAL timeMin, 
							 const zREAL timeMinVar, 
							 const zREAL timeMax, 
							 const zREAL timeMaxVar, 
							 const zREAL probMin) 
{
	if (!ani) return;
	zTRandAni randAni;
	randAni.randAni				= ani;
	randAni.randAniTimeMin		= timeMin;
	randAni.randAniTimeMinVar	= timeMinVar;
	randAni.randAniTimeMax		= timeMax;
	randAni.randAniTimeMaxVar	= timeMaxVar;
	randAni.randAniProbMin		= probMin;
	randAni.randAniTimer		= timeMax * zREAL(2.0F) * zREAL(1000.0F);
	randAniList.Insert (randAni);
};

void zCMorphMesh::ProcessRandAnis () {
	for (int i=0; i<randAniList.GetNum(); i++) 
	{
		randAniList[i].randAniTimer -= ztimer.GetFrameTimeF();
		if (randAniList[i].randAniTimer<0) {
			// RandAni starten
			StartAni (randAniList[i].randAni, zRandF()*0.4F + 0.6F);

			// naechsten Zeitpunkt bestimmen
			zREAL t;
			if (zRandF()<randAniList[i].randAniProbMin)	t = randAniList[i].randAniTimeMin + zRandF2()*randAniList[i].randAniTimeMinVar;
			else										t = randAniList[i].randAniTimeMax + zRandF2()*randAniList[i].randAniTimeMaxVar;
			randAniList[i].randAniTimer = t * zREAL(1000.0F);
			break;
		};
	};
};

void zCMorphMesh::SetTextureVar (const int channel, const int varNr, zSTRING* texNamePart)
{
	texAniState.SetChannelVariation	(channel, varNr, texNamePart);
};

zBOOL zCMorphMesh::TraceRay			(	const zVEC3&		rayOrigin, 
										const zVEC3&		ray, 
										const int			traceFlags, 
										zTTraceRayReport	&report)
{
	// traceRay, ray and report defined in objectSpace
	if (!GetMorphMesh()) return FALSE;
	return GetMorphMesh()->TraceRay (rayOrigin, ray, traceFlags, report);
};

// ==================================================================================================================

void zCMorphMesh::PrintStatus (int xpos, int ypos) {
	const int ADD = 250;
	const int TAB = 300;
	screen->Print (xpos + 0*TAB, ypos, "AniName");
	screen->Print (xpos + 6*TAB, ypos, "weight/dest");
	screen->Print (xpos +11*TAB, ypos, "Layer");
	screen->Print (xpos +13*TAB, ypos, "Frame");
	screen->Print (xpos +15*TAB, ypos, ".");
	screen->Print (xpos +16*TAB, ypos, "fps");
	screen->Print (xpos +17*TAB, ypos, "(#anis: "+zSTRING(morphProto->aniList.GetNumInList())+")");
	ypos += ADD;
	zSTRING ascName;
	for (int i=0; i<aniChannels.GetNum(); i++) {
		screen->Print (xpos + 0*TAB, ypos+i*ADD, aniChannels[i]->ani->aniName);
		screen->Print (xpos + 6*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->weight,2)+"/"+zSTRING(aniChannels[i]->weightDest,2));
		screen->Print (xpos +12*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->ani->GetLayer()));
		screen->Print (xpos +13*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->actFrame,2));
		screen->Print (xpos +14*TAB, ypos+i*ADD, ", "+zSTRING(aniChannels[i]->ani->numFrames));
//		screen->Print (xpos +15*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->advanceDir));  
		screen->Print (xpos +16*TAB, ypos+i*ADD, zSTRING(aniChannels[i]->ani->fpsRate*zREAL(1000.0F),2));  
	};
};

// =======================================================================================================================

zCMorphMeshConvertFileHandler::zCMorphMeshConvertFileHandler() 
{
	RegisterFileType("mms");
};

zBOOL zCMorphMeshConvertFileHandler::HandleFile (const zSTRING& fname, const char* directory, _finddata_t fileinfo)
{
	zBOOL touched = FALSE;

	// Kompletten Dateinamen bauen
	zSTRING filename = zSTRING(directory) + DIR_SEPARATOR + fname;
	filename.Upper();		

	//
	if (fname.Search(".MMS")>=0) 
	{				
		zCMorphMesh *morphMesh	= zCMorphMesh::Load (fname);
		if (morphMesh)
		{
			morphMesh->Release		();
			touched					= TRUE;
		};
	} 
	else
	{
		zERR_FAULT ("D: MORPH: Convert: Unknown filetype: "+fname);
	}

	return touched;
};

// =======================================================================================================================
