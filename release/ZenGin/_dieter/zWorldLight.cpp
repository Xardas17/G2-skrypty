/******************************************************************************** 
 
     $Workfile:: zWorldLight.cpp      $                $Date:: 13.02.01 20:56   $
     $Revision:: 28                   $             $Modtime:: 13.02.01 20:47   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Lighting the static world mesh, vertexLight and lightmaps.
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zWorldLight.cpp $
 * 
 * 28    13.02.01 20:56 Hildebrandt
 * 
 * 27    8.02.01 6:54 Hildebrandt
 * 
 * 26    6.02.01 23:55 Hildebrandt
 * 
 * 25    27.01.01 19:42 Moos
 * 
 * 24    25.01.01 22:30 Hildebrandt
 * 
 * 23    25.01.01 17:01 Hildebrandt
 * 
 * 22    20.12.00 3:04 Hildebrandt
 * 
 * 21    6.12.00 16:49 Hildebrandt
 * 
 * 20    4.12.00 18:23 Moos
 * 
 * 19    25.11.00 2:14 Hildebrandt
 * 
 * 18    17.11.00 19:29 Moos
 * 
 * 17    26.10.00 17:45 Speckels
 * 
 * 16    22.09.00 15:58 Hoeller
 * 
 * 15    31.08.00 17:04 Hildebrandt
 * 
 * 14    21.08.00 17:18 Hildebrandt
 * 
 * 13    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 17    9.08.00 17:12 Admin
 * 
 * 12    21.07.00 14:28 Hildebrandt
 * 
 * 11    6.07.00 13:45 Hildebrandt
 * 
 * 6     10.05.00 23:27 Hildebrandt 
 * zenGin 089i
 * 
 * 5     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 4     2.05.00 21:48 Hildebrandt
 * zenGin 089c
 * 
 * 12    23.03.00 20:10 Hildebrandt
 * fixed potential lightmap-generation hangup
 * 
 * 11    15.03.00 16:43 Hildebrandt
 * zenGin 088
 * 
 * 10    23.02.00 3:29 Hildebrandt
 * 
 * 9     18.02.00 1:39 Hildebrandt
 * 
 * 6     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 5     16.11.99 19:49 Hildebrandt
 * 
 * 4     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 28 $ ($Modtime: 13.02.01 20:47 $)
 

#include <zCore.h>
#include <zWorld.h>
#include <z3d.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

#ifdef DEBUG_HILDEBRANDT
//	#define	zLIGHTMAP_COLOR_MARK 

//	Zeigt durch Farbkodierung, welche Polygone dieselbe Surface/Lightmap benutzen
//	#define zLIGHTMAP_MARK_SURFACES
#endif 


#define LIGHTMAP_SMOOTH_MATERIALS 1

//#undef	zLIGHTMAP_COLOR_MARK 

// Einheiten: cm

#ifdef DEBUG_HILDEBRANDT
	static const	zREAL	zLIGHTMAP_GRID_DEFAULT		= zREAL(50.0F);
#else													
	//static const	zREAL	zLIGHTMAP_GRID_DEFAULT		= zREAL(50.0F);		// 56 ~ Quake 1
	//static const	zREAL	zLIGHTMAP_GRID_DEFAULT		= zREAL(25.0F);		// 56 ~ Quake 1
//	static const	zREAL	zLIGHTMAP_GRID_DEFAULT		= zREAL(25.0F);		// 56 ~ Quake 1
	static const	zREAL	zLIGHTMAP_GRID_DEFAULT		= zREAL(25.0F);		// 56 ~ Quake 1
#endif													
//static const	zREAL	zLIGHTMAP_GRID_DEFAULT			= zREAL(16.0F);		
//static const	zREAL	zLIGHTMAP_GRID_DEFAULT			= zREAL(64.0F);
//static const	zREAL	zLIGHTMAP_GRID_DEFAULT			= zREAL(128.0F);
//static const	zREAL	zLIGHTMAP_FILTER_INTENS_THRESH	= zREAL( 20.0F);		// Intensity(0..255) Unterschied im 3x3 Grid, ab der das Sample gesmoothed wird (blur filter)
//static const	zREAL	zLIGHTMAP_NO_LM_INTENS_THRESH	= zREAL( 55.0F);		// Intensity(0..255) Unterschied innerhalb einer LM, ab der die LM weggeworfen und stattdessen VertLight benutzt wird

static const	zREAL	zLIGHTMAP_FILTER_INTENS_THRESH	= zREAL( 10.0F);		// Intensity(0..255) Unterschied im 3x3 Grid, ab der das Sample gesmoothed wird (blur filter)
static const	zREAL	zLIGHTMAP_NO_LM_INTENS_THRESH	= zREAL( 55.0F);		// Intensity(0..255) Unterschied innerhalb einer LM, ab der die LM weggeworfen und stattdessen VertLight benutzt wird


static zREAL			zLIGHTMAP_GRID					= zLIGHTMAP_GRID_DEFAULT;
static zREAL			zLIGHTMAP_GRID_HALF				= zLIGHTMAP_GRID * zREAL(0.5F);

// Schaltet das Blur-Filtering fuer die LMs ein/aus
#define zLIGHTMAP_SMOOTH



// **********************************************************************************************
//     Beleuchtung
// **********************************************************************************************

static zCList<zCVob> lightVobList;  

/* ----------------------------------------------------------------------
	
	zCPolygon::LightStatic()
    
	16.11.2000	[Moos]	
                Umstellung auf neue Vertexklasse:

                                   alt                       neu
Vertex wurde schon berechnet       vert->transformed == -2   vert->myIndex & 2
Vertex ist blockiert               BOOL(vert->vertScrX)      vert->myIndex & 1


   ---------------------------------------------------------------------- */

void zCPolygon::LightStatic (zCVobLight&	light, 
							 const zPOINT3& lightSourcePos, 
							 zMATRIX4&		polyTrafoObjToWorld,
							 zCWorld*		world) {
	// lightSourcePos	: im PolySpace (und nicht im vobLight-Space !!)
	// world			: fuer CheckRayPoly

	if (!feature) return; 
	
	// alle Portal Polys sind uniform hell
/*	if (IsPortal()) {
		zCOLOR col(100,100,100,255);
		for (int i=0; i<polyNumVert; i++) {
			feature[i]->lightStat = col;
		};
		return;
	};
*/
	zVALUE rangeInv	= light.GetRangeInv();
	zVALUE ka,kd;

	if (material==0) {
		ka  = 0.0f;
		kd  = 0.8f;
	} else {
		ka  = material->kambient;
		kd  = material->kdiffuse;
	};

	// Achtung: NICHT clipVert !!
	zVEC3	ray, rayOrg;
	zVEC3	view; 
	zBOOL	dirLight = (light.GetLightType()==zVOBLIGHT_TYPE_DIR);
	if (dirLight) {
		view	= light.GetAtVectorWorld();
//		view	= zVEC3(+0.5773F, -0.5773F, +0.5773F);
	};

	// fuer SpotLights
	zREAL	spotDotMax	= zCos((light.lightData.GetSpotConeAngle()/180.0F)*3.14159F);

	zBOOL specialSectorBorderLighting =
		(GetSectorFlag()) && 
		(GetMaterial()->GetBspSectorFront()) &&
		(GetMaterial()->GetBspSectorFront()->HasManyBigPortals());

	zBOOL smooth = FALSE;

	if (material) smooth = material->GetSmooth();

	for (int p=0; p<polyNumVert; p++) {
		zCVertex		*actVert = vertex[p]; 
		zCVertFeature	*actFeat = feature[p]; 

		zVALUE	dot;
		zVALUE	dist;
		zVALUE	i = 0;

		if (dirLight) {
			dist = 1;
		} else {
			////////////////////////
			// 3. Distance-Falloff /
			////////////////////////
			dist = (actVert->position-lightSourcePos).Length();
			if (dist>light.GetRange()) {
				dist = 0;
			} else {
				dist = 1-(dist * rangeInv);
			};
		};
		
		//
		// erreicht die Lichtquelle ueberhaupt den Vertex ?
		//

		if (dist>0) {
			zBOOL vertBlocked = FALSE;
			
			// Vert bereits gecheckt worden ?
//			if (actVert->transformed==-2) {
//				vertBlocked = zBOOL(actVert->vertScrX);

			if (actVert->myIndex & 2) {
				vertBlocked = zBOOL(actVert->myIndex & 1);
			} else
			if (world) {
				// alles im Worldspace
				const zPOINT3& vertWS= actVert->position * polyTrafoObjToWorld; 
				if (dirLight) {
					rayOrg			= vertWS - 10000*view;
					ray				= (vertWS - rayOrg);
					ray				= ray - 100*view;
				} else {
					rayOrg			= light.GetPositionWorld();
					ray				= (vertWS - rayOrg) * 0.96F;			// FIXME: korrekter Wert ?
				};
				
				world->TraceRayFirstHit (rayOrg, ray,(zCVob*)0,0);

				// result-caching
				vertBlocked			= world->traceRayReport.foundHit;
//				actVert->vertScrX	= float(vertBlocked);
//				actVert->transformed= -2;

				actVert->myIndex	= vertBlocked ? 3 : 2;
			};

			
			////////////////////////
			// 1. Diffuse         //
			////////////////////////
			// angle: face/light
			// dot<0 => poly ist lq abgewandt
			// (zu beleuchtender Punkt) - (Ort der Lichtquelle)
			if (dirLight) {
				if (smooth) dot = -(view * actFeat->vertNormal);
				else		dot = -(view * polyPlane.normal);
				//i += kd*dot;
				if (vertBlocked) dot *= 0.25F;
				i += dot;
			} else {
				if (vertBlocked) goto lightBlocked;
				view = actVert->position - lightSourcePos;
				view.Normalize(); 
				if (smooth) dot = -(view * actFeat->vertNormal);
				else		dot = -(view * polyPlane.normal);

				if (light.GetLightType()==zVOBLIGHT_TYPE_SPOT) 
				{
					zREAL spotDot	= (view * light.GetAtVectorWorld());
					if (spotDot<=spotDotMax) continue;
				};

				i += (kd*dot);

				////////////////////////
				// 3. Distance-Falloff /
				////////////////////////
				i *= (dist); 
			};
		};

lightBlocked:;

		////////////////////////
		// 4. Ambient		  //
		////////////////////////
		i += ka;

		// Sector-Polys sind dunkel
//		if (GetSectorFlag())	i *= 0.25F;		
//		if (GetSectorFlag())	i *= 0.08F;

		// LIGHTMAPS
//		if (GetSectorFlag())	i = 0;

		if (dirLight) {
			// ambient 
			if (i<0) {
				i = 0.25F*(1-(-i));
			}
			else if (material->GetMatGroup()!=zMAT_GROUP_WATER) i*=0.8f;
			i = i*0.85F + 0.15F;
//			i += 0.15F;
//			if (i<0.15F) i=0.15F;
		};

		// Spezielle Behandlung von Vertices innerhalb von Sektoren
		if (GetSectorFlag()) 
		{
			// Vertices in Sektoren mit vielen grossen Portalen (z.B. in Waldwaben) am Rand zum Nicht-Sektor
			// werden wie Vert ausserhalb des Sektors beleuchtet, um keinen harten Bruch in der Intensitaet zu haben
			zBOOL vertIsOnBorder=FALSE;
			if (specialSectorBorderLighting)
			{
				zTBBox3D		box;
				zCPolygon		**foundPolyList=0;
				int				foundPolyNum=0;
				box.Init		();
				box.AddPoint	(actVert->position+zVEC3(+1,+1,+1));
				box.AddPoint	(actVert->position+zVEC3(-1,-1,-1));
				world->GetBspTree()->CollectPolysInBBox3D(box, foundPolyList, foundPolyNum);
				for (int p=0; p<foundPolyNum; p++)
				{
					if ((!foundPolyList[p]->GetSectorFlag()) && (foundPolyList[p]->VertPartOfPoly(actVert)))
					{
						vertIsOnBorder=TRUE;
						break;
					};
				};
				if (!vertIsOnBorder)
				{
					i *= 0.60F;
					if (i<0.10F) i=0.10F;
				};
			} else
			{
				i *= 0.40F;
				if (i<0.10F) i=0.10F;
			};
		};

		if (i<=0.0F) continue;

		// combine
		if (i>zREAL(1.0F)) i=zREAL(1.0F);

		// Farbe des Lichtes durch die Intensitaet skalieren
		int intens		= int(i*255.0F);

		int r = (((int)light.GetColorR() * intens) >> 8) + int(actFeat->lightStat.r); if (r>255) r=255;
		int g = (((int)light.GetColorG() * intens) >> 8) + int(actFeat->lightStat.g); if (g>255) g=255;
		int b = (((int)light.GetColorB() * intens) >> 8) + int(actFeat->lightStat.b); if (b>255) b=255;

		// Die Effektive Farbe des Lichtes dem Vert-Feature hinzuaddieren (lightDyn)
		actFeat->lightStat.r = r;
		actFeat->lightStat.g = g;
		actFeat->lightStat.b = b;
//		if (dirLight)
//			actFeat->lightStat.alpha = actFeat->lightStat.g = actFeat->lightStat.r = 0;
	};
};

void zCPolygon::SmoothSectorBorder(zCWorld* world) 
{
	// Spezielle Behandlung von Vertices innerhalb von Sektoren
	if (GetSectorFlag() && GetMaterial()->GetBspSectorFront()) 
	{
		// Vertices in Sektoren mit vielen grossen Portalen (z.B. in Waldwaben) am Rand zum Nicht-Sektor
		// werden wie Vert ausserhalb des Sektors beleuchtet, um keinen harten Bruch in der Intensitaet zu haben
		for (int i=0; i<polyNumVert; i++)
		{
			zCVertex *actVert = vertex[i];
			zTBBox3D		box;
			zCPolygon		**foundPolyList=0;
			int				foundPolyNum=0;
			box.Init		();
			box.AddPoint	(actVert->position+zVEC3(+10,+10,+10));
			box.AddPoint	(actVert->position+zVEC3(-10,-10,-10));
			world->GetBspTree()->CollectPolysInBBox3D(box, foundPolyList, foundPolyNum);

			for (int p=0; p<foundPolyNum; p++)
			{
				if ( !foundPolyList[p]->IsOccluder()	)
				if ( !foundPolyList[p]->GetSectorFlag() )
				{
					int vertPartOfPoly = -1;
					for (int pf = 0; pf<foundPolyList[p]->polyNumVert; pf++)
					{
						if ((actVert->position-foundPolyList[p]->vertex[pf]->position).Length()<0.01f)
						{
							vertPartOfPoly = pf;
							break;
						}
					}
					if (vertPartOfPoly != -1)
					{
						// das entsprechende poly hat ein shared vertex mit einem outdoor poly
						// nun die statische vertex farbe so flaggen, das der renderer weiss das für dieses vertex feature
						// die outdoor farbe genommen werden muss
						// FIXME: das ist so natürlich nicht besonders schön, aber ein  zusätzliches Flag im zCVertexFeature wäre
						// zu teuer. Das stat Alpha wird eh nicht gebraucht
						/*for (int tt = 0; tt<polyNumVert; tt++)
						{
							feature[tt]->lightStat = zCOLOR(255,255,255,255);
							feature[tt]->lightStat.SetAlphaByte(99);	
						};
						return;*/
						feature[i]->lightStat = foundPolyList[p]->feature[pf]->lightStat;
						feature[i]->lightStat.SetAlphaByte(99);
						break;
					}
				};
			};
		}
	};
};




/* ----------------------------------------------------------------------
	
	zCPolygon::LightMesh()
    
	16.11.2000	[Moos]	
                Umstellung auf neue Vertexklasse:

                                   alt                       neu
Vertex wurde schon berechnet       vert->transformed == -2   vert->myIndex & 2
Vertex ist blockiert               BOOL(vert->vertScrX)      vert->myIndex & 1


   ---------------------------------------------------------------------- */

void zCMesh::LightMesh (zCVobLight& light, zMATRIX4& meshTrafoObjToWorld, zCWorld* world) {
	zMATRIX4	mtrafoWorldToObj = meshTrafoObjToWorld.InverseLinTrafo();
	zPOINT3		lightPosMeshSpace= mtrafoWorldToObj * light.GetPositionWorld();

	int i;
	for (i=0; i<numVert; i++) {
//		vertList[i]->transformed = -1;
		vertList[i]->myIndex = 0;
	};

	for (i=0; i<numPoly; i++) {
		polyList[i]->LightStatic (light, lightPosMeshSpace, meshTrafoObjToWorld, world);
	};


};

void zCWorld::LightWorldStaticUncompiled (zCTree<zCVob>* node) {

	// process node
	zCVob* vob = node->GetData();
	if (vob)
	if (vob->GetShowVisual())
	if (vob->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT)
	{
		zCVisual *vis = vob->GetVisual();
		if (vis)
		if (vis->GetClassDef()==zCMesh::GetStaticClassDef()) 
		{
			zCMesh *mesh = ((zCMesh*)vis);
			// jetzt alle Lights durchgehen und damit successive 
			// das eine Mesh beleuchten

			// vorher StaticLight reseten
			mesh->ResetStaticLight(); 
			// Smoothing 
			zerr.Message ("D: MESH: Calculating Vertex-Normals for Mesh (smoothing)...");
			mesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_MAT);
//			((zCMesh*)vis)->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_FACET);

			zCList<zCVob> *item = lightVobList.GetNextInList();
			while (item!=0) {
				// aktuelles Mesh mit jedem Licht aus Liste beleuchten
				zCVobLight *light = ((zCVobLight*)item->GetData ());
				assert (light);
				zerr.Message ("D: WORLD: Light, id:"+zSTRING((int)light->GetVobID())+", name: "+light->GetVobName()+
								", Range: "+zSTRING(light->GetRange())+
								", Col: "+light->GetColor().GetDescription());
				mesh->LightMesh (*light, vob->trafoObjToWorld, this);
				item = item->GetNextInList();
			};
//		mesh->LoadLightInfo(); // FIXME: TEMP
//		mesh->SaveLightInfo(); // FIXME: TEMP
		};
	};

	// recursive traversal
	zCTree<zCVob> *child = node->GetFirstChild(); 
	while (child!=0) {
		LightWorldStaticUncompiled (child);
		child = child->GetNextChild();
	};
};


static void TraverseCollectLights (zCTree<zCVob>* node) {
	// process node
	zCVob* vob = node->GetData();
	if (vob)
	if (vob->GetVobType()==zVOB_TYPE_LIGHT) {
		// nur statische Lichter beruecksichtigen
		if (((zCVobLight*)vob)->GetIsStatic()) 
			lightVobList.Insert (vob);
	};

	// recursive traversal
	zCTree<zCVob> *child = node->GetFirstChild(); 
	while (child) {
		TraverseCollectLights (child);
		child = child->GetNextChild();
	};
};

void zCWorld::LightWorldStaticCompiled () 
{
	zCVobLight *sunLight = zNEW(zCVobLight);

	if (GetBspTree()->GetBspTreeMode()==zBSP_MODE_OUTDOOR) { 
		sunLight->SetLightType		(zVOBLIGHT_TYPE_DIR);
		sunLight->SetRange			(100); 
		AddVob						(sunLight);
		sunLight->SetColor			(255,255,255);
	//	sunLight.Move				(30,180,200);
		zVEC3 dir					= zVEC3(+0.4495F, -0.8660F, -0.2181F);
//		zVEC3 dir					= zVEC3(+0.5773F, -0.7660F, +0.1395F);
//		zVEC3 dir					= zVEC3(-0.4880F, -0.5773F, +0.5773F);
//		zVEC3 dir					= zVEC3(2*zRandF()-1, -zRandF()*4, 2*zRandF()-1);
		dir.Normalize				();
		sunLight->SetHeadingAtWorld	(dir);
	//	sunLight->trafo.SetAtVector (zVEC3(+0.5773F, -0.5773F, +0.5773F));
	//	sunLight->trafoObjToWorld.SetAtVector (zVEC3(+0.5773F, -0.5773F, +0.5773F));
	lightVobList.DeleteList();
		lightVobList.Insert			(sunLight);
	};

	//
	zCMesh* mesh = GetBspTree()->mesh;

	// StaticLight reseten
	mesh->ResetStaticLight(); 

	// Smoothing 
	mesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_MAT, &bspTree); 
//	mesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_SMOOTH, &bspTree); 

	//
	zCList<zCVob> *item = lightVobList.GetNextInList();
	zMAT4 ident = Alg_Identity3D();
	while (item) {
		// aktuelles Mesh mit jedem Licht aus Liste beleuchten
		zCVobLight *light	= ((zCVobLight*)item->GetData ());
		assert				(light);
		zERR_MESSAGE		(9,0, "D: WORLD: Light, id:"+zSTRING((int)light->GetVobID())+", name: "+light->GetVobName()+", Range: "+zSTRING(light->GetRange())+", Col: "+light->GetColor().GetDescription());
		mesh->LightMesh		(*light, ident, this);
		item				= item->GetNextInList();
	};

	zERR_MESSAGE(5,0,"C: now smoothing sector border colors...");
	for (int i=0; i<mesh->numPoly; i++) {
		mesh->SharePoly(i)->SmoothSectorBorder(this);
	};
	zERR_MESSAGE(5,0,"C: ...done");


	RemoveVob	(sunLight);
	zRELEASE	(sunLight);
};

void zCWorld::GenerateStaticVertexLighting () 
{
	// Alle Lights des GlobalVobtrees durchgehen und mit diesen 
	// nacheinander alle Verts der Level-Komponenten Vobs beleuchten

	zerr.Message ("D: WORLD: Calculating static Vertex Light for world ...");

	// Mesh auf Zugriff vorbereiten
	GetBspTree()->mesh->CreateListsFromArrays();

	// Lights und Level aus dem GlobalVobtree in 2 Listen sortieren
	TraverseCollectLights	(&globalVobTree);
	zerr.Message ("D: WORLD: NumLights: "+zSTRING(lightVobList.GetNumInList()));
	if (IsCompiled())	LightWorldStaticCompiled	();
	else				LightWorldStaticUncompiled	(&globalVobTree);

	// cleanup
	lightVobList.DeleteList();
	zerr.Message ("D: WORLD: ... Finished.");
};




// **********************************************************************************************
//     LIGHTMAPS:	Raytracing	/ Radiosity
// **********************************************************************************************


#pragma pack (push, 1)							// Alignment ausschalten
	typedef zVEC3 zCRealColor;

	class zCPatch;

	class zCTransferConstr {
	public:
		zCPatch				*targetPatch;
		zREAL				formFactor;
	};

	class zCTransfer {
	public:
		zCPatch				*targetPatch;
		zWORD				formFactor;
	};

	class zCPatch {
	public:
		zCPatch() {
			radiosity	= radToShoot = 0;
		};
		void	DoTransfers();

		zPOINT3				center;
		zPOINT3				centerLight;
		zVEC3				normal;
		zREAL				area;
		zCRealColor			radiosity;
		zCRealColor			radToShoot;
		zSWORD				xpos, ypos;
		zCArray<zCTransfer>	transferList;
		zVEC3				reflectivity;
	};

	class zCPatchMap {
	public:
		zCPatchMap() {
			hit				= FALSE;
			xdim			= 0;
			ydim			= 0;
			lastRayHitPoly	= 0;
		};
		~zCPatchMap() {
			for (int i=0; i<patchList.GetNumInList(); i++) {
				delete patchList[i];
			};
			lastRayHitPoly=0;
		};
		zBOOL8				hit;
		zSWORD				xdim, ydim;
		zCArray<zCPatch*>	patchList;
		zCArray<zCPolygon*>	surface;
		zTPlane				lightRejectPlane0;		 // "sandwich" planes der surface
		zTPlane				lightRejectPlane1;
		zTBBox3D			bbox3D;

		zVEC3				lightmapOrigin;
		zVEC3				lightmapUp;
		zVEC3				lightmapRight;
		zCPolygon			*lastRayHitPoly;

		zBOOL CheckRaySurfaceIntersection (zPOINT3& rayOrg, zPOINT3& ray, zPOINT3& inters, zCPolygon* &hitPoly) {
			zREAL alpha;	// dummy
			if (lastRayHitPoly) {
				if (lastRayHitPoly->CheckRayPolyIntersection (rayOrg, ray, inters, alpha))	{
					hitPoly	= lastRayHitPoly;
					return TRUE;
				};
			};
			for (int i=0; i<surface.GetNumInList(); i++) {
				zCPolygon *poly = surface[i];
				if (poly->CheckRayPolyIntersection (rayOrg, ray, inters, alpha))	{
					hitPoly			= poly;
					lastRayHitPoly	= poly;
					return TRUE;
				};
			};
			hitPoly=0;
			return FALSE;
		};
	};

#pragma pack (pop)								// Alignment ausschalten

static zVEC3				COL_SCALE			= zVEC3((0.299F),(0.587F),(0.114F));

static int					numLightmapTexel;
static int					numLightmaps;
static int					numLightmapsRejected;

static zCPolygon			*traceRayLastPoly	= 0;
static zCArray<zCPatchMap*>	patchMapList;

static inline zREAL GetColorIntensity (const zCRealColor& col) {
	// result: 0..255
	return col * COL_SCALE;
/*	zREAL intens=0;
	for (int i=0; i<3; i++)
		intens += col[i]*COL_SCALE[i];
	return intens;*/
};

static zREAL ColorNormalize (const zCRealColor& in, zCRealColor& out) {
	// result normalisiert auf: 0..255
	zREAL max, scale;
	max = in[0];
	if (in[1] > max)	max = in[1];
	if (in[2] > max)	max = in[2];
	if (max == 0)		{ out=in; return 0; };
	scale	= 255.0 / max;
	out		= scale * in;
	return max;
}

static zREAL ColorClamp (const zCRealColor& in, zCRealColor& out) {
	// result normalisiert auf: 0..255
	zREAL max, scale;
	max = in[0];
	if (in[1] > max)	max = in[1];
	if (in[2] > max)	max = in[2];
	if (max <= 255)		{ out=in; return 0; };
 
	scale	= 255.0 / max;
	out		= scale * in;
	return max;
}

/*
	Create a "blocker list" for each light source consisting of all things which
	could possibly block that light source. (we group things and lights into
	"lighting systems" to shorten the blocker list, among other things)
	Every time you detect a blocked ray, move the blocking thing to the top of
	the list.
	Always search for blockers using the blocking list order.

	We got a speedup on the order of 100X with this approach.
*/

zBOOL zCWorld::LightingTestRay (const zPOINT3& start, const zPOINT3& end, zVEC3& inters, zCPolygon* &hitPoly) 
{
//	return bspTree.TraceRay (start, end, TRUE, TRUE, TRUE, inters, hitPoly, 0);
	if (traceRayLastPoly) 
	{
		zREAL alpha;
		if (traceRayLastPoly->CheckRayPolyIntersection (start, end-start, inters, alpha)) {
			hitPoly = traceRayLastPoly;
			return TRUE;
		};
		traceRayLastPoly=0;
//	if ((alpha<0) || (alpha>1))	zerr.Message ("löksdjgölksjdgöl");
	};
	
	if (bspTree.TraceRay (start, end, zTRACERAY_STAT_POLY | zTRACERAY_POLY_IGNORE_TRANSP, inters, hitPoly, 0)) {
		traceRayLastPoly = hitPoly;
		return TRUE;
	}; 
	return FALSE;
};

zBOOL zCWorld::GetSurfaceLightmapBBox2D (zCArray<zCPolygon*>& surface, zTBBox2D& lmBox, int realDim[2]) 
{
	// origin, up, right des Polys ermitteln
	int				i;
	zBOOL			validBox	= TRUE;
	zCPolygon		*poly		= surface[0];
	zVEC3			origin, up, right;
	const zTPlane&	surfacePlane= surface[0]->GetPlane();
	poly->GetPlane().GetOriginUpRight (origin, up, right);

	// bbox2D der Lightmap ermitteln
	lmBox.Init();
	zVALUE			s,t;
	zPOINT3			q;
	const zPOINT3&	a			= right;				// assert: right*up=0 
	const zPOINT3&	b			= up;
	zREAL			bb			= (b*b);
	zREAL			div			= zREAL(1) / ((a*a)*(bb));
	zVEC3			axisRight	= (bb*div)*a;
	zVEC3			axisUp		= b / bb;

	for (int p=0; p<surface.GetNumInList(); p++) {
		poly = surface[p];
		for (int i=0; i<poly->polyNumVert; i++) {
			zPOINT3 pos = poly->GetVertexPtr(i)->position;
			pos -= surfacePlane.normal * ((pos * surfacePlane.normal) - surfacePlane.distance);		// Vertex auf die Ebene der Lightmap Surface projezieren
			q	= pos - origin;
			s	= q * axisRight;
			t	= q * axisUp;

			lmBox.mins[0] = zMin (lmBox.mins[0], s);
			lmBox.maxs[0] = zMax (lmBox.maxs[0], s);
			lmBox.mins[1] = zMin (lmBox.mins[1], t);
			lmBox.maxs[1] = zMax (lmBox.maxs[1], t);
		};
	};

	// Grid Snap
	for (i=0; i<2; i++) {
		lmBox.mins[i] = zFloor(lmBox.mins[i] / zLIGHTMAP_GRID) * zLIGHTMAP_GRID;
		lmBox.maxs[i] = zCeil (lmBox.maxs[i] / zLIGHTMAP_GRID) * zLIGHTMAP_GRID;
	};

	// Lightmap-Groessen auf naechst groessere 2er Potenzen bringen
	int lmDim  [2];									// Einheiten: lm-texel
//	int realDim[2];
	for (i=0; i<2; i++) {
		lmDim[i]		= int((lmBox.maxs[i] - lmBox.mins[i]) / zLIGHTMAP_GRID);
		if (lmDim[i]<=0)	lmDim[i] = 1;
		realDim[i]		= lmDim[i];
		lmDim[i]		= zMakePowerOf2Higher (lmDim[i]);
		lmBox.maxs[i]	= lmBox.mins[i] + zREAL(lmDim[i]) * zLIGHTMAP_GRID;
	};

	assert (realDim[0]!=0);
	
	// ist die aspect-ratio ok ?
	// FIXME: Abfrage: Was wenn lmDims zu gross ??
	if ((lmDim[0]>256) || (lmDim[1]>256)) 
		validBox = FALSE;
	zClamp (lmDim[0], 0, 256);
	zClamp (lmDim[1], 0, 256);
	zClamp (realDim[0], 0, 256);
	zClamp (realDim[1], 0, 256);

	assert (realDim[0]!=0);

//	lmDim[0] = zMax (lmDim[0], lmDim[1]);
//	lmDim[1] = lmDim[0];
	if (lmDim[0]>lmDim[1]) {
		float ratio = float(lmDim[0]) / float(lmDim[1]);
		if (ratio>8) lmDim[1] = lmDim[1] * (ratio / 8.0F);
	} else {
		float ratio = float(lmDim[1]) / float(lmDim[0]);
		if (ratio>8) lmDim[0] = lmDim[0] * (ratio / 8.0F);
	};

	for (i=0; i<2; i++) {
		lmBox.maxs[i]	= lmBox.mins[i] + zREAL(lmDim[i]) * zLIGHTMAP_GRID;
	}; 

	return validBox;
};

zVEC3 zCWorld::GetPhongNormal (zCPolygon *poly, const zPOINT3 &pos)
{
	// smoothing
	int ifirst=0, inext1=1, inext2=2;
#ifdef LIGHTMAP_SMOOTH_MATERIALS
#else
	if (poly->GetMaterial()->GetSmooth()) 
#endif
	{
		if (poly->polyNumVert>3)
		for (ifirst=0; ifirst<poly->polyNumVert; ifirst++) {
			inext1=ifirst+1; if (inext1>=poly->polyNumVert) inext1=0;
			inext2=inext1+1; if (inext2>=poly->polyNumVert) inext2=0;
			if (!Alg_IsColinear (poly->GetVertexPtr(ifirst)->position,poly->GetVertexPtr(inext1)->position,poly->GetVertexPtr(inext2)->position)) {
				break;
			};
		};
	};
	const zPOINT3&	a	= poly->GetVertexPtr(inext2)->position - poly->GetVertexPtr(inext1)->position;
	const zPOINT3&	b	= poly->GetVertexPtr(ifirst)->position - poly->GetVertexPtr(inext1)->position;
	const zREAL		ab	= (a*b); 
	const zREAL		bb	= (b*b);
	const zPOINT3&	normalDelta1 = poly->feature[inext2]->vertNormal - poly->feature[inext1]->vertNormal;
	const zPOINT3&	normalDelta2 = poly->feature[ifirst]->vertNormal - poly->feature[inext1]->vertNormal;

	zVEC3	q	= pos - poly->GetVertexPtr(inext1)->position;
	zREAL	qb	= (q*b);

	zREAL	s	= ((bb) * (q*a) - (ab) * (qb)) / ((a*a)*(bb) - ((ab)*(ab)));
	zREAL	t	= ((qb) - s*(ab)) / (bb);

	zVEC3 normal= poly->feature[inext1]->vertNormal + s*normalDelta1 + t*normalDelta2;
	normal.Normalize();
	return normal;
};

zCPatchMap* zCWorld::GeneratePatchMapFromSurface (zCArray<zCPolygon*>& surface) 
{
	zVEC3		origin, up, right;
	zTBBox2D	lmBox;
	int			lmDim  [2];									// Einheiten: lm-texel
	int			realDim[2];

	GetSurfaceLightmapBBox2D (surface, lmBox, realDim);
	lmDim[0]= (lmBox.maxs[0] - lmBox.mins[0]) / zLIGHTMAP_GRID;
	lmDim[1]= (lmBox.maxs[1] - lmBox.mins[1]) / zLIGHTMAP_GRID;
	
	// origin, up, right des Polys ermitteln
	zCPolygon* poly = surface[0];
	poly->GetPlane().GetOriginUpRight (origin, up, right);

	// jetzt ist origin der lokale Origin (links unten) der Lightmap, in WS-cm
	zVALUE mids,midt;
	origin	= origin + right*lmBox.mins[0] + up*lmBox.mins[1];
	mids	= (lmBox.mins[0] + lmBox.maxs[0]) * 0.5F;
	midt	= (lmBox.mins[1] + lmBox.maxs[1]) * 0.5F;

	// BBox2D in Patches rastern
	zCPatchMap *patchMap	= zNEW(zCPatchMap);
	patchMap->surface		= surface;
	patchMap->lightmapOrigin= origin;
	patchMap->lightmapRight	= right * zLIGHTMAP_GRID * zREAL(lmDim[0]);
	patchMap->lightmapUp	= up	* zLIGHTMAP_GRID * zREAL(lmDim[1]);
	patchMap->xdim			= lmDim[0]; 
	patchMap->ydim			= lmDim[1];

	// 'lightRejectPlane' und 'bbox3D' der Patchmap berechnen. Werden spaeter fuer die trivRej von Lights benutzt
	// FIXME: der 'lightRejectPlane' Test ist derzeit noch buggy und disabled (bringt aber auch nicht soo viel..)
	zREAL planeMinDist			= zREAL_MAX;
	zREAL planeMaxDist			= zREAL_MIN;
	patchMap->bbox3D.Init		();
	patchMap->lightRejectPlane0	= patchMap->surface[0]->GetPlane();
	patchMap->lightRejectPlane1	= patchMap->surface[0]->GetPlane();
	patchMap->lightRejectPlane0.normal *= zREAL(-1.0F);		// Normale umdrehen
	for (int i=0; i<patchMap->surface.GetNum(); i++)
	{
		zCPolygon *poly = surface[i];
		for (int j=0; j<poly->polyNumVert; j++)
		{
			patchMap->bbox3D.AddPoint		(poly->GetVertexPtr(j)->position);
			zREAL planeDist					= patchMap->lightRejectPlane1.GetDistanceToPlane (poly->GetVertexPtr(j)->position);
			if (planeDist<0)	planeMinDist= zMin (planeMinDist, planeDist);
			else				planeMaxDist= zMax (planeMaxDist, planeDist);
		};
	};
	if (planeMinDist<0)	patchMap->lightRejectPlane0.distance += planeMinDist;
	if (planeMaxDist>0)	patchMap->lightRejectPlane1.distance += planeMaxDist;

	// FIXME: pro poly, nicht pro surface !
	zBOOL matLight = FALSE;

	//
	zPOINT3 texelPos;
	zPOINT3 lmOrigin =	origin + 
						right  * zLIGHTMAP_GRID_HALF +
						up     * zLIGHTMAP_GRID_HALF;
	const zREAL		RAY_SCALE	= patchMap->bbox3D.GetMaxExtent()*zREAL(2.0F);
	      zVEC3		testRay		= -2*RAY_SCALE*poly->GetNormal(); 
	const zVEC3&	startOfs	=    RAY_SCALE*poly->GetNormal();

	for (int x=0; x<realDim[VX]; x++) 
	{
		for (int y=0; y<realDim[VY]; y++) 
		{
			texelPos =	lmOrigin + 
						right *	zREAL(x) * zLIGHTMAP_GRID + 
						up	  * zREAL(y) * zLIGHTMAP_GRID;

			// Test: liegt der Lightmap-Texel noch auf der Flaeche eines Polygons der Surface ?
			zVEC3		rayInters;
			zCPolygon	*hitPoly= 0;
			zBOOL		ok		= FALSE;
			if (patchMap->CheckRaySurfaceIntersection (texelPos+startOfs, testRay, rayInters, hitPoly))	ok = TRUE;
			else 
			{
				const int	SUBDIV		= 1;
				const zREAL	DELTA		= zLIGHTMAP_GRID / zREAL(SUBDIV);
				zVEC3		startPos	= texelPos - right*zLIGHTMAP_GRID_HALF - up*zLIGHTMAP_GRID_HALF;

				// 6, subdiv, <=
				for (int i=0; i<=SUBDIV; i++) 
					for (int j=0; j<=SUBDIV; j++) {
						const zVEC3& point = startPos + right*zREAL(i)*DELTA + up*zREAL(j)*DELTA;
						if (patchMap->CheckRaySurfaceIntersection (point+startOfs, testRay, rayInters, hitPoly)) {
							ok		= TRUE;
							goto exitLoop;
						};
					};
exitLoop:;
			};

			if (ok)
			{			
				zCPatch	*patch		= zNEW(zCPatch);
				patch->center		= rayInters;							// TraceRay Ziel fuer Ray-Casts
				patch->centerLight	= rayInters;							// wirklicher Mittelpunkt des Lighmap-Texels (zur Beleuchtung)
				patch->area			= (zLIGHTMAP_GRID*zLIGHTMAP_GRID);		// approx
				patch->xpos			= x;
				patch->ypos			= y;
#ifdef zLIGHTMAP_COLOR_MARK
	patch->radiosity = zVEC3(0,0,255);
#endif
				// Patch-Reflectivity berechnen
				if (hitPoly->GetMaterial()->GetTexture()) {
					patch->reflectivity	= zVEC3(1,1,1);
				} else {
					zCOLOR col;
					col = hitPoly->GetMaterial()->GetColor();
					patch->reflectivity	= zVEC3(zREAL(col.r)/255, zREAL(col.g)/255, zREAL(col.b)/255);
				};
				// Selbstleuchtendes Material ?
				if (matLight) {
					patch->radToShoot	+= patch->reflectivity * 255;
					patch->radiosity	 = zVEC3(200,200,200);
				};
				patchMap->hit		= FALSE;
				patchMap->patchList.Insert (patch);

#ifndef LIGHTMAP_SMOOTH_MATERIALS
				if (!hitPoly->GetMaterial()->GetSmooth()) 
//				if (1)
//				if (0)
				{
					patch->normal		= hitPoly->GetNormal();
				} else {
					patch->normal		= GetPhongNormal	(hitPoly, patch->center);
				};
#else 
				patch->normal		= GetPhongNormal	(hitPoly, patch->center);
#endif
			};
		};
	};
//	poly->GetMaterial()->SetSmooth(TRUE);

	return patchMap;
};

static int inline Clip (int a, int max) {
	if (a<0)	return 0;		else
	if (a>=max)	return max-1;
	else		return a;
};



/* ----------------------------------------------------------------------
	
    zCWorld::GenerateLightmapFromPatchMap()	

	29.11.2000	[Moos]	
                auf neue Lightmap-Klasse umgestellt

   ---------------------------------------------------------------------- */

void zCWorld::GenerateLightmapFromPatchMap (zCPatchMap *patchMap) {
	// darf nur bei raytracing !
	if (!patchMap->hit) return;

	// Colormap erzeugen
	//	zerr.Message ("D: LM: "+zSTRING(patchMap->xdim)+", "+zSTRING(patchMap->ydim));
	const int XDIM = patchMap->xdim;
	const int YDIM = patchMap->ydim;
	const int size = XDIM*YDIM;
	zCRealColor	*colorMap		= zNEW(zCRealColor) [size];
	zCRealColor	*colorMap2		= zNEW(zCRealColor) [size];
	zCRealColor	*colorMapSrc	= colorMap;
	zCRealColor	*colorMapDest	= colorMap2;
	zCTexture	*lightmapTex		= 0;
	zCLightMap	*lightmapMap		= 0;
	assert (size>0);

	for (int j=0; j<size; j++)
		colorMapSrc[j] = zVEC3(-1,0,0);

	// Patches in die Colormap eintragen
	zVEC3 avgCol=zVEC3(0); 
	#ifdef zLIGHTMAP_MARK_SURFACES
		zVEC3 randCol = zVEC3(zRandF()*255, zRandF()*255, zRandF()*255);
	#endif
	for (int i=0; i<patchMap->patchList.GetNumInList(); i++) {
		zCPatch *patch		= patchMap->patchList[i];
//		ColorNormalize		(patch->radiosity, patch->radiosity);
		ColorClamp			(patch->radiosity, patch->radiosity);
		#ifdef zLIGHTMAP_MARK_SURFACES
			patch->radiosity= randCol;
		#endif
		colorMapSrc			[patch->xpos + patch->ypos*XDIM] = patch->radiosity;
		avgCol				+= patch->radiosity;
	}; 
	avgCol /= patchMap->patchList.GetNumInList();

	// eine einfache 'hit' Abfrage reicht bei Radiosity nicht aus
//	zREAL intens = GetColorIntensity (avgCol);;
//	if (intens<10) goto leave;

	// Colormap: smoothen
#ifdef zLIGHTMAP_SMOOTH
	if (1)
	{
		zREAL	minTotal = zREAL_MAX;
		zREAL	maxTotal = zREAL_MIN;
		zVEC3	v;
		for (int x=0; x<XDIM; x++) {
			for (int y=0; y<YDIM; y++) {
				zVEC3 sum	= zVEC3(0);
				zREAL num	= 0;
				zREAL min	= zREAL_MAX;
				zREAL max	= zREAL_MIN;
				int xminus1	= Clip(x-1,XDIM);
				int xplus1  = Clip(x+1,XDIM);
				int yminus1	= Clip(y-1,YDIM); 
				int yplus1  = Clip(y+1,YDIM);
				v = colorMapSrc[xminus1	+ yminus1*XDIM];	if (v[VX]>=0) { num +=1; sum += zREAL(1.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };
				v = colorMapSrc[xminus1	+ (y+0)  *XDIM];	if (v[VX]>=0) { num +=2; sum += zREAL(2.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };
				v = colorMapSrc[xminus1	+ yplus1 *XDIM];	if (v[VX]>=0) { num +=1; sum += zREAL(1.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };

				v = colorMapSrc[x		+ yminus1*XDIM];	if (v[VX]>=0) { num +=2; sum += zREAL(2.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };
				v = colorMapSrc[x		+ (y+0)  *XDIM];	if (v[VX]>=0) { num +=4; sum += zREAL(4.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };
				v = colorMapSrc[x		+ yplus1 *XDIM];	if (v[VX]>=0) { num +=2; sum += zREAL(2.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };

				v = colorMapSrc[xplus1	+ yminus1*XDIM];	if (v[VX]>=0) { num +=1; sum += zREAL(1.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };
				v = colorMapSrc[xplus1	+ (y+0)  *XDIM];	if (v[VX]>=0) { num +=2; sum += zREAL(2.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };
				v = colorMapSrc[xplus1	+ yplus1 *XDIM];	if (v[VX]>=0) { num +=1; sum += zREAL(1.0F)*v; zREAL intens = GetColorIntensity(v); min=zMin(min, intens); max=zMax(max, intens); };

				if (num>0) {
					minTotal	= zMin (minTotal, min);
					maxTotal	= zMax (maxTotal, max);
				};

				// nur filtern, wenn fuer mind 2 Positionen valide Samples vorliegen
				if ((num<2) || ((max-min)<zLIGHTMAP_FILTER_INTENS_THRESH))
				{
					colorMapDest [x +y*XDIM] = colorMapSrc[x +y*XDIM]; 
				} else {
					// filtern
					colorMapDest[x + y*XDIM] = sum / num;
				};
			};
		};
		zSwap (colorMapSrc, colorMapDest);

		// Wenn die Lightmap nur geringe Intensitaets-Unterschiede hat, bekommen die Polys keine Lightmap,
		// sondern nur VertLight. Also: Abbruch hier.
		// Im Outdoor wird dies nicht zugelassen, da hier die tageszeitliche Beleuchtung "dazwischenfunkt"
// ATT: erst einmal disabled, um auffaelige Mismatches zwischen LM-Polys und gouraud-Polys zu vermeiden
/*		if (GetBspTree()->GetBspTreeMode()==zBSP_MODE_INDOOR)
		if ((maxTotal-minTotal)<zLIGHTMAP_NO_LM_INTENS_THRESH) 
		{
			numLightmapsRejected++;
			#ifndef zLIGHTMAP_MARK_SURFACES
				goto leave;
			#endif
		};
*/
	};
#endif

	// 'leere' Felder in der LM mit avgCol der Umgebung ausfuellen
	// und: -1 entfernen
	// => damit das Bilerp keine falschen Farben in die LM hineinzieht
	// erst nach dem smoothen, oder ? 
	if (1) {
		zVEC3	v;
		for (int x=0; x<XDIM; x++) {
			for (int y=0; y<YDIM; y++) {
				if (colorMapSrc[x + y*XDIM][0]==-1) {
					zVEC3 sum=zVEC3(0);
					zREAL num=0;
					int xminus1	= Clip(x-1,XDIM);
					int xplus1  = Clip(x+1,XDIM);
					int yminus1	= Clip(y-1,YDIM); 
					int yplus1  = Clip(y+1,YDIM);
					v = colorMapSrc[xminus1	+ yminus1*XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };
					v = colorMapSrc[xminus1	+ (y+0)  *XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };
					v = colorMapSrc[xminus1	+ yplus1 *XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };

					v = colorMapSrc[x		+ yminus1*XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };
					v = colorMapSrc[x		+ (y+0)  *XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };
					v = colorMapSrc[x		+ yplus1 *XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };

					v = colorMapSrc[xplus1	+ yminus1*XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };
					v = colorMapSrc[xplus1	+ (y+0)  *XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };
					v = colorMapSrc[xplus1	+ yplus1 *XDIM] * zREAL(1.0F);		if (v[VX]>=0) { num +=1; sum += v; };

					if (num>0)	colorMapDest[x + y*XDIM] = sum / num;
					else		colorMapDest[x + y*XDIM] = zVEC3(0,0,0);
				} else
					colorMapDest[x + y*XDIM] = colorMapSrc[x +y*XDIM];
			};
		};
		zSwap (colorMapSrc, colorMapDest);
	};

	// Colormap: error-diffusion
	// ...

	// Lightmap aus Colormap erzeugen
	lightmapTex	=		zrenderer->CreateTexture ();
    lightmapMap =       zNEW(zCLightMap);

    lightmapMap->SetTexture         (lightmapTex);
	lightmapTex->SetCacheOutLock	(TRUE);
//	lightmap->SetName			(zSTRING("lm")+zSTRING(int(patchMap->surface[0]))); 

#ifdef ZENGINE_DEBUG
//	zrenderer->SetBilerpFilterEnabled (FALSE);
#endif
	{
		int numTexel			= patchMap->xdim * patchMap->ydim;
		zCTextureConvert *texCon= zrenderer->CreateTextureConvert();
 
		// 1) TexCon aus RawData erzeugen
		{
			// TextureFormat
			zCTextureInfo texInfo;
			texInfo.texFormat	= zRND_TEX_FORMAT_RGB_888;
			texInfo.sizeX		= patchMap->xdim;
			texInfo.sizeY		= patchMap->ydim;
			texInfo.numMipMap	= 1;
			texInfo.refSizeX	= patchMap->xdim;
			texInfo.refSizeY	= patchMap->ydim;

			// TexConvert anwerfen..
			if (!texCon->Lock			(zTEX_LOCK_WRITE))
			{
				zERR_FATAL("C: zCWorld::GenerateLightmapFromPatchMap() could not lock texConvert for write");
			}
			texCon->SetTextureInfo	(texInfo);

			//
			void	*texBuffer;
			int		texPitch;
			texCon->GetTextureBuffer(0, texBuffer, texPitch);
			if (texBuffer)
			{
				// Real colorMap in integer RGB888 ColorMap konvertieren
				// FIXME: error-diffusion ? 
				// (bei ziel-pal 8bit z.B. schon hier moeglich, auch wenn pal woanders generiert wird?)
				zBYTE	*ptrLineStart		= (zBYTE*)texBuffer;
				int		sourceIndex			= 0;
				for (int yrun=0; yrun<texInfo.sizeY; yrun++) {
					zBYTE	*ptr			= ptrLineStart;
					for (int xrun=0; xrun<texInfo.sizeX; xrun++) {
						*ptr= zFloat2Int(colorMapSrc[sourceIndex][0]); if (*ptr>255) *ptr=255;	ptr++;
						*ptr= zFloat2Int(colorMapSrc[sourceIndex][1]); if (*ptr>255) *ptr=255;	ptr++;
						*ptr= zFloat2Int(colorMapSrc[sourceIndex][2]); if (*ptr>255) *ptr=255;	ptr++;
						sourceIndex++;
					};
					ptrLineStart += texPitch;
				};
			};
			texCon->Unlock	();
		};

		// 2) TexCon in Zielformat konvertieren
		zCTextureInfo	texInfo	= texCon->GetTextureInfo();
		texInfo.numMipMap		= 1;
		texInfo.texFormat		= (numTexel<=1024) ? zRND_TEX_FORMAT_RGB_565 : zRND_TEX_FORMAT_PAL_8;
// FIXME: hier gibt es noch ein Problem:
//        wenn die aktive Hardware kein PAL_8 unterstuetzt kann die LM auch gar nicht als solche abgelegt werden.
//        spaeter moechte man sie allerdings als solche im .ZEN haben..
		texInfo.texFormat		= zCTexture::CalcNextBestTexFormat (texInfo.texFormat);
 		texCon->ConvertTextureFormat(texInfo);


		// 3) Texcon in Target Texture kopieren
		zCTextureConvert::CopyContents	(texCon, lightmapTex);
		delete texCon; texCon=0;

		lightmapTex->SetCacheOutLock	(TRUE);
	};
	
/*
int xdim,ydim;
lightmap->GetPixelSize	(xdim,ydim);
zerr.Message ("D: size: "+zSTRING(xdim)+","+zSTRING(ydim));
*/

	lightmapMap->CalcLightmapOriginUpRight	(patchMap->lightmapOrigin, patchMap->lightmapUp, patchMap->lightmapRight); 
	for (i=0; i<patchMap->surface.GetNumInList(); i++) {
		patchMap->surface[i]->SetLightmap (lightmapMap);		
	};

	lightmapMap->Release();
	assert (lightmapMap->GetRefCtr()>0);

	lightmapTex->Release();
	assert (lightmapTex->GetRefCtr()>0);

	numLightmapTexel += lightmapTex->GetMemSizeBytes();
	numLightmaps++;

	// cleanup
	goto leave;
leave:;
	delete[] colorMap;
	delete[] colorMap2;
};

void zCWorld::LightPatchMap (zCPatchMap *patchMap) 
{
	zCList<zCVob>	*item	= lightVobList.GetNextInList();
	zCPolygon		*poly	= patchMap->surface[0]; 

	while (item) 
	{
		// aktuelles Mesh mit jedem Licht aus Liste beleuchten
		zCVobLight *light = ((zCVobLight*)item->GetData ());

		// Trivial rejection:
		// Nur Lichter beruecksichtigen, die die minSurfacPlane schneiden und die BBox der Surface beruehren
		zPOINT3 lightPos	= light->GetPositionWorld();
//		zREAL	dist0		= zAbsApprox(patchMap->lightRejectPlane0.GetDistanceToPlane (lightPos));
//		zREAL	dist1		= zAbsApprox(patchMap->lightRejectPlane1.GetDistanceToPlane (lightPos));
		zTBSphere3D lightSphere;
		lightSphere.center	= lightPos;
		lightSphere.radius	= light->GetRange();
		if (
//			((dist0<=light->GetRange()) ||
//			 (dist1<=light->GetRange())) && 
			(patchMap->bbox3D.IsIntersecting (lightSphere))
			)
		{ 
			//
			zCOLOR	col			= light->GetColor();
			zVEC3	lightColor	= col.GetVEC3();
			zREAL	range2		= light->GetRange()*light->GetRange();
			zVALUE	rangeInv	= light->GetRangeInv();
			zREAL	spotDotMax	= zCos((light->lightData.GetSpotConeAngle()/180.0F)*3.14159F);
			
			for (int i=0; i<patchMap->patchList.GetNumInList(); i++) 
			{
				zCPatch *patch	= patchMap->patchList[i];
				zVEC3	view	= (patch->centerLight  - lightPos);
				zREAL	dist	= (view).Length2();
				if (dist<=range2)
				{
					zREAL dot, i=0;
					dist  = sqrt(dist);
					view /= dist;
					dot   = -(view * patch->normal);
					if (dot<0) continue; 

					if (light->GetLightType()==zVOBLIGHT_TYPE_SPOT) 
					{
						zREAL spotDot	= (view * light->GetAtVectorWorld());
						if (spotDot<=spotDotMax) continue;
					};

/*					// linear falloff
					dist  = 1-(dist * rangeInv);
					zClamp01 (dist);
					i	  = dot; 
					i	 *= dist;
*/
					// quadratic falloff
					// (fuer einen helleren Gesamteindruck)
					dist	= (dist * rangeInv);
					dist	*= dist;
					dist	= 1-dist;
					zClamp01 (dist);
					i		= dot; 
					i		*= dist;

					// Raytrace Occlusion Test
					zVEC3		patchColor=lightColor;
					zVEC3		inters;
					zCPolygon	*hitPoly=0;
//					bspTree.TraceRay (lightPos, patch->center-patchMap->poly->polyPlane.normal, TRUE, FALSE, TRUE, inters, hitPoly, 0); 
					// ignoreTranspPoly ? Farbaenderung bei Wasserdurchdringung ??
//					bspTree.TraceRay	(lightPos, patch->center, TRUE, TRUE, TRUE, inters, hitPoly, 0); 
/*					if ((bspTree.TraceRay (lightPos, patch->center, TRUE, FALSE, TRUE, inters, hitPoly, 0) &&
						(hitPoly) &&
						(hitPoly->GetMaterial()->GetAlpha()!=255)))
					{
						patchColor	= 0.5F*patchColor + 0.5F*zVEC3(0,0,GetColorIntensity(patchColor));
						bspTree.TraceRay (lightPos, patch->center, TRUE, TRUE, TRUE, inters, hitPoly, 0);
					};*/
//					if (LightingTestRay (lightPos, patch->center, inters, hitPoly)) 
					// FIXME !!!   SURFACE !!!
					// nichts getroffen => ok, der Licht Strahl kommt durch !
					// etwas  getroffen => Strahl kommt nur durch, wenn das getroffene Poly eines der Surfae ist !
/*
					zVEC3 ray = (patch->center-lightPos)*0.5F; 
					zBOOL res = LightingTestRay (lightPos, patch->center + ray, inters, hitPoly);
//					zBOOL res = LightingTestRay (lightPos, patch->center, inters, hitPoly);
					if (res) {
						for (int i=0; i<patchMap->surface.GetNumInList(); i++)
							if (patchMap->surface[i]==hitPoly) { res = FALSE; break; }; 
						if ((inters-patch->center).Length2()<80.0F)	res = FALSE;						
					};
					if (!res)
*/
					// Vobs werfen Schatten
					const zVEC3& rayLightToPatch = patch->centerLight-lightPos;
					if (TraceRayNearestHit (lightPos, rayLightToPatch , light, zTRACERAY_STAT_IGNORE)) {
						if (traceRayReport.foundVob) 
						if (traceRayReport.foundVob->GetStaticVob()) 
							goto leaveThis;
					};

					{
					
						// Der ZielOrt ist ein wenig von dem Poly weggerueckt.
						// Beachte: Die BSP-TraceRay Routine verlaengt den Ray minimal (ca. 1.001), wodurch ein hier
						// weggerueckter EndPunkt trotzdem 'merkwuerdigerweise' das Ziel treffen wuerde.
						// (=> zCBspTree::CheckRayAgainstPolys..())
						zBOOL rayOccluded	= bspTree.TraceRay (lightPos, 
																patch->center + 11*poly->GetNormal(),	// war: 9
																zTRACERAY_STAT_POLY | zTRACERAY_POLY_IGNORE_TRANSP, 
																inters, 
																hitPoly,
																0);

						if (!rayOccluded)
						{ 
	//						if ((hitPoly==poly) || ((inters-patch->center).Length2()<80.0F))	// 9cm
							{
								#ifdef zLIGHTMAP_COLOR_MARK
									patch->radiosity= zVEC3(0,255,0);
								#else
									patch->radiosity+= patchColor * i;
	//								patch->radiosity= zVEC3(255,0,0);
								#endif
								patch->radToShoot	+= patchColor * i;
								patchMap->hit		 = TRUE;
							};
						};
					};

goto leaveThis;
leaveThis:;
				};
			};
		};
		item = item->GetNextInList();
	};
};

void zCWorld::GenerateSurfaces (const zBOOL doRaytracing, zTBBox3D *updateBBox3D)
{
	int						numSurfaces=0;
	int						i;
	zCMesh					*mesh	= bspTree.mesh;
	zCArray<zCPolygon*>		polyList(mesh->numPoly);
	zCArray<zCPolygon*>		surface;

	// Polyliste kopieren
	for (i=0; i<mesh->numPoly; i++) {
		zCPolygon *poly = mesh->Poly(i);
		poly->flags.mustRelight = TRUE;						// dient als Markierung fuer Polys, die bereits mit einer LM versehen sind (=TRUE)..
		// Polys rausfiltern, die keine Lightmaps bekommen sollen
		if (poly->GetMaterial()->GetDontUseLightmaps()) continue;
		if (poly->GetMaterial()->GetTexture()) 
		{
			poly->GetMaterial()->GetTexture()->CacheIn(-1);				// Muss!!!
			if (poly->GetMaterial()->GetTexture()->HasAlpha())			// Alpha-Texturen bekommen keine LMs!
				continue;
		}
		if (GetBspTree()->GetBspTreeMode()==zBSP_MODE_OUTDOOR)	{
			if (!poly->GetSectorFlag()) continue;
			if ( poly->IsPortal())		continue;
		};
		// Update Bereich durch eine BBox eingeschraenkt ?
		if (updateBBox3D) {
			if (!poly->GetBBox3D().IsIntersecting (*updateBBox3D)) continue;
		};
		poly->flags.mustRelight = FALSE;					// dient als Markierung fuer Polys, die bereits mit einer LM versehen sind (=TRUE)..
		polyList.Insert		(poly);
	};

	zREAL numPolyTotal = polyList.GetNum();
	while (polyList.GetNum()>0) 
	{
		// eine Surface wird eingesammelt
		surface.EmptyList		();
		surface.Insert			(polyList[0]);
		polyList.RemoveIndex	(0);

		{
			for (int l=0; l<surface.GetNumInList(); l++) {
				zCPolygon *poly = surface[l]; 

				// alle Nachbarn des aktuellen Polys aus dem BSP ziehen
				zCPolygon	**foundPolyList=0;
				int			foundPolyNum=0;
				zTBBox3D	bbox3D;
				bbox3D		= poly->GetBBox3D();
				bbox3D.Scale (zREAL(1.01F));
				GetBspTree()->CollectPolysInBBox3D (bbox3D, foundPolyList, foundPolyNum);

				for (int j=0; j<foundPolyNum; j++) {
					zCPolygon *poly2 = foundPolyList[j];

					if (poly2->flags.mustRelight)	continue;
					if (poly==poly2) 			continue;

					// FIXME: eigentlich duerften hier auch nur Polys betrachtet werden, die zu dem aktuellen "smooth" 
					//        geshadet werden sollen. Ein Aufnahme von Polys in dieselbe LM-Surface macht die Uebergaenge
					//        immer "glatt".

					const zREAL		EPSILON_PLANE_NORMAL	=  0.70F;		// 0.95 / 0.7	0.707 = 45°
					const zTPlane&	p1						= surface[0]->GetPlane();
					const zTPlane&	p2						= poly2->GetPlane(); 
					if (
						(    (((p1.normal) *(p2.normal)))	>= EPSILON_PLANE_NORMAL)
						)
					{
						// teilen die 2 Polys ein Vertex ?
						for (int k=0; k<poly->polyNumVert; k++) 
						{
							if (poly2->VertPartOfPoly (poly->GetVertexPtr(k))) 
							{
								// Ist Poly bereits Teil einer Surface und hat bereits eine LM ?
								int polyListIndex = polyList.Search (poly2);
								if (polyListIndex>=0)
								{
									// Falls das neue Polygon in der Projektion auf die Lightmap/Surface Ebene ein
									// Polygon schneidet, das bereits Teil der Surface ist, dann darf dieses neue Poly
									// nicht in die Surface aufgenommen werden. Wuerde Fehler ergeben, da die LM planar
									// projeziert wird und fuer 1 Lighray mehrere Polygon-Orte existieren wuerden.
									zBOOL intersectingProjection = FALSE;
									for (int m=0; m<surface.GetNum(); m++) 
									{
										if (poly2->IsIntersectingProjection (surface[m], surface[0]->GetNormal())) 
										{
											intersectingProjection = TRUE;
											break;
										};
									};
									if (!intersectingProjection)
									{
										zTBBox2D	lmBox;
										int			realDim[2]; 
										surface.InsertEnd (poly2);
										if (!GetSurfaceLightmapBBox2D (surface, lmBox, realDim)) {
											surface.RemoveIndex		(surface.GetNumInList()-1);
										} else {
											poly2->flags.mustRelight = TRUE;
											polyList.RemoveIndex	(polyListIndex);
											foundPolyList[j]		= foundPolyList[foundPolyNum-1];
											foundPolyNum--;
											j--;
											break;
										};
									};
								};
							};
						};
					};
				};
			};
		};

		// ok, die Surface ist gefunden
		// generate
		zCPatchMap *patchMap=0;
		int currentPatchDim[2];
		if (doRaytracing) 
		{
			// Raytracing
			patchMap = GeneratePatchMapFromSurface	(surface);
			LightPatchMap							(patchMap);
			GenerateLightmapFromPatchMap			(patchMap);
			currentPatchDim[0]						= patchMap->xdim;
			currentPatchDim[1]						= patchMap->ydim;
			delete patchMap;
		} else 
		{
			// Radiosity
			patchMap = GeneratePatchMapFromSurface		(surface);
			patchMapList.Insert							(patchMap);
			LightPatchMap								(patchMap);
		};
		numSurfaces++;
		if ((numSurfaces&7)==0) 
		{
			zREAL perc = (zREAL(1) - (zREAL(polyList.GetNum()) / numPolyTotal)) * zREAL(100);
			zERR_MESSAGE (3, 0, "D: ... working, numSurfaces: "+zSTRING(numSurfaces)+", numPolys: "+zSTRING(surface.GetNum())+", dim: "+zSTRING(currentPatchDim[0])+"x"+zSTRING(currentPatchDim[1])+" ("+zSTRING(perc,3)+"%) ...");
		};
	};

	// Lightmaps in zCTexture Pages sammeln
    mesh->CombineLightmaps();

	zerr.Message ("D: WORLD: LM: numPolys: "+zSTRING(mesh->numPoly)+", numSurfaces: "+zSTRING(numSurfaces));
};

// Radiosity

void zCWorld::MakeTransfers () 
{
	zerr.Message ("D: WORLD: LM: Making transfers...");
	const zREAL MAX_DIST = 800.0F;
	zREAL		totalTrans;
	int			numTrans = 0;
	zCArray<zCTransferConstr>	transferList(1024);

	for (int i=0; i<patchMapList.GetNumInList(); i++) {
		for (int j=0; j<patchMapList[i]->patchList.GetNumInList(); j++) 
		{
			zCPatch				*patch = patchMapList[i]->patchList[j];
			zCTransferConstr	transfer;
			transferList.EmptyList();
			totalTrans=0;

			// aktuellen Patch gegen alle anderen Patches testen

			for (int k=0; k<patchMapList.GetNumInList(); k++) {

				// kann man die gesamte Patchmap discarden ?

				// backface-culling
				// don't bother with surfaces behind the surface
				// don't bother with surfaces too far away
				zCPolygon	*poly	= patchMapList[k]->surface[0];
				zREAL		dist	= patch->center * poly->GetNormal() - poly->polyPlane.distance;
				if ((dist<=0) || (dist>(MAX_DIST*MAX_DIST))) continue;

				for (int l=0; l<patchMapList[k]->patchList.GetNumInList(); l++) 
				{
					zCPatch	*patch2 = patchMapList[k]->patchList[l];
					if (patch2==patch) continue;

					// - pvs
					// - plane/sphere Test
					// - dot/backface Test
					// - TraceRay

					zREAL	trans;
					zVEC3	ray		= patch2->center - patch->center;
					zREAL	length	= ray.Length2(); 
					if (length>(MAX_DIST*MAX_DIST)) continue;
							length	= sqrt(length);
							ray	   /= length;
					zREAL	scale	= (ray * patch->normal) * (-(ray*patch2->normal));

					// backface culling
					if (scale<=0) continue;

					// traceRay
					zVEC3		inters;
					zCPolygon	*hitPoly;
					// FIXME !!!!!!!!
					if (LightingTestRay (patch->center, patch2->center, inters, hitPoly)) {
						if ((inters-patch2->center).Length2()>50.0F) continue;
					};

					//
					trans = scale * patch2->area / ((length*length) * M_PI);
					if (trans<=0.001F) continue;

					// Ok, einen korrekten Transfer entdeckt
					totalTrans			+= trans;
					transfer.targetPatch = patch2;
					transfer.formFactor	 = trans;
					transferList.Insert	(transfer);
					numTrans++;
				};
			};

			// Transfers eines Patches normalisieren
			patch->transferList.AllocAbs (transferList.GetNumInList());
			for (int m=0; m<transferList.GetNumInList(); m++) {
				zCTransfer trans;
				trans.targetPatch = transferList[m].targetPatch;
				trans.formFactor  = zWORD((transferList[m].formFactor * 0x10000) / totalTrans);
				patch->transferList.Insert	(trans);
			};
		};
		static int lastPerc;
		int perc = int(float(i)/float(patchMapList.GetNumInList())*100.0F);
		if (((perc%10)==0) && (perc!=lastPerc)) {
			zerr.Message ("D: WORLD: LM: .. "+zSTRING(perc)+" % ..");
			lastPerc = perc;
		};
	};
	zerr.Message ("D: WORLD: LM: NumTransfers: "+zSTRING(numTrans)+", mem: "+zSTRING(float((sizeof(zCTransfer)+4)*numTrans)/(1024*1024),2)+" megs"); 
};

static zCPatch* FindMaxPowerPatch (zREAL& resultInt) {
	zVEC3	bestRad;
	zREAL	bestPower	= -1;
	zCPatch	*bestPatch;

	for (int i=0; i<patchMapList.GetNumInList(); i++) {
		for (int j=0; j<patchMapList[i]->patchList.GetNumInList(); j++) {
			zCPatch *patch	= patchMapList[i]->patchList[j];
			zVEC3	rad		= patch->radToShoot;
			zREAL	power	= GetColorIntensity (rad);
			if (power>bestPower) 
			if (patch->transferList.GetNumInList()>0)
			{
				bestPower = power;
				bestPatch = patch;
				resultInt = power;
				if (power>=254.0F) return patch;
			};
		}
	}
	return bestPatch;
};

static zREAL	bestPower;
static zCPatch *nextPatch;

void zCPatch::DoTransfers() {
	for (int c=0; c<3; c++)
		radToShoot[c] = radToShoot[c] * reflectivity[c]; 

	bestPower=-1;
	for (int i=0; i<transferList.GetNumInList(); i++) {
		const zCTransfer&	transfer	= transferList[i];
		zVEC3				targetRad	= radToShoot * (zREAL(transfer.formFactor) / zREAL(0x10000)) * 0.45F; 
//			targetRad[1] = 255;
		transfer.targetPatch->radiosity	+= targetRad;
		transfer.targetPatch->radToShoot+= targetRad;

		zREAL thisPower = GetColorIntensity (transfer.targetPatch->radToShoot);
		if (thisPower>bestPower) 
		if (transfer.targetPatch->transferList.GetNumInList()>0)
		{
			bestPower	= thisPower;
			nextPatch	= transfer.targetPatch;
		};
	};

	// alles verschossen
	radToShoot	= 0;
};

void zCWorld::GenerateLightmapsRadiosity (zTBBox3D *updateBBox3D) 
{
	int i=0;

	// Die PatchMaps aller Surfaces werden erstellt
	// und durch VobLights beleuchtet
	GenerateSurfaces	(FALSE, updateBBox3D);

	// 
	MakeTransfers		();

	// Iterate shooting steps
	zerr.Message ("D: WORLD: LM: Iterating...");
//	zREAL		patchInt;
	int			numIterations	= 0;
//	zCPatch		*patch			= FindMaxPowerPatch(patchInt);
//	zREAL		firstPower		= (patchInt * patch->area);;

#if 0
	if ((firstPower>0) && (patch))
	do {
		patch->DoTransfers();

		// Konvergiert ?
		if (patchInt * patch->area < firstPower * 0.7F) break;

		// und weiter..
		if (bestPower!=-1) {
			patch		= nextPatch;
			patchInt	= bestPower;
		} else
			patch		= FindMaxPowerPatch(patchInt);
	} while (patch);
	zerr.Message ("D: WORLD: LM: Last fraction: "+zSTRING(((patchInt*patch->area) /firstPower),3));
#else

	numIterations = 6;
	do { 
		for (i=0; i<patchMapList.GetNumInList(); i++) {
			for (int j=0; j<patchMapList[i]->patchList.GetNumInList(); j++) {
				zCPatch *patch = patchMapList[i]->patchList[j];
/*				if (((i&2)!=0) && ((j&64)!=0)) {
					patch->radToShoot	= zVEC3(128,128,128);
					patch->radiosity	= patch->radToShoot;
					patchMapList[i]->hit = TRUE;
				};*/
				patch->DoTransfers();
			};
		};
	} while (numIterations--);

#endif

	zerr.Message ("D: WORLD: LM: Finished.");

	// Build lightmaps from patchmaps & cleanUp
	while (patchMapList.GetNumInList()>0) {
		GenerateLightmapFromPatchMap	(patchMapList[0]);
		delete patchMapList[0];
		patchMapList.RemoveIndex		(0);
	};

	// Cleanup
	patchMapList.DeleteList();
};

void zCWorld::GenerateLightmaps (const zTStaticWorldLightMode& lightMode, zTBBox3D *updateBBox3D)
{
	if (!IsCompiled()) return;

	// Mesh auf Zugriff vorbereiten
	GetBspTree()->mesh->CreateListsFromArrays();

	// hohe FPU Precision sicherstellen
	const zDWORD fpuControlWord	= zfpuControler.GetCurrentControlWord();
	zfpuControler.SetPrecision_53();

	//
	zERR_MESSAGE			(3, zERR_BEGIN, "D: WORLD: LM: Generating Lightmaps.. ("+zSTRING(lightMode)+")");
	lightVobList.DeleteList	();
	TraverseCollectLights	(&globalVobTree);
	numLightmaps			= 0;
	numLightmapTexel		= 0;
	numLightmapsRejected	= 0;
	traceRayLastPoly		= 0;
	zLIGHTMAP_GRID 			= zLIGHTMAP_GRID_DEFAULT;
	if (lightMode <zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL)	zLIGHTMAP_GRID	*= zREAL(2.5F);	else
	if (lightMode==zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL)	zLIGHTMAP_GRID	*= zREAL(2.0F);	else
	if (lightMode >zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL)	zLIGHTMAP_GRID	*= zREAL(1.0F);
	zLIGHTMAP_GRID_HALF		= zLIGHTMAP_GRID * zREAL(0.5F);

	// Die alten LM's killen
	// Wird bei partiellen Updates/Berechnungen (=> udpateBBox3D) unterbunden
	if (!updateBBox3D)
	{
		zCMesh *mesh = bspTree.mesh;
		for (int i=0; i<mesh->numPoly; i++) {
			mesh->Poly(i)->SetLightmap(0);
		};
		bspTree.mesh->SetHasLightmaps (FALSE);
	};

//	if (lightMode<=zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL) 
	if (1)
	{
	//	GenerateLightmapsRaytracing();
		GenerateSurfaces			(TRUE, updateBBox3D);
	} else {
		GenerateLightmapsRadiosity	(updateBBox3D);
	};

	bspTree.mesh->SetHasLightmaps	((numLightmaps>0));

	// cleanup
	lightVobList.DeleteList			();
	SetWorldRenderMode				(zWLD_RENDER_MODE_LIGHTMAPS);
	zERR_MESSAGE					(3, zERR_END, "D: WORLD: LM: ok. numLightmaps: "+zSTRING(numLightmaps)+", numLMReject: "+zSTRING(numLightmapsRejected)+", numTexel: "+zSTRING(numLightmapTexel)+", mem: "+zSTRING(int(numLightmapTexel/1024))+"k");

	//
	zfpuControler.SetControlWord	(fpuControlWord);
};

/* ----------------------------------------------------------------------------
	zCWorld::GenerateStaticWorldLighting

	26.10.2000	[SPECKELS]	Aufruf von ResetVobLighting
   ----------------------------------------------------------------------------*/

// FIXME: [EDENFELD] 1.09 external scheisse muss noch raus
extern zBOOL g_bIsInCompileLightMode;

void zCWorld::GenerateStaticWorldLighting	(const zTStaticWorldLightMode& lightMode, zTBBox3D *updateBBox3D) 
{

	zCMesh *mesh = GetBspTree()->mesh;

	if (mesh)
	{
		mesh->ResetStaticLight(); 
		// Smoothing 
		zERR_MESSAGE(5,0,"C: WORLD: smoothing vertex normals for lightmap generation");
		mesh->CalcVertexNormals(zCMesh::zMSH_VERTNORMAL_SMOOTH, &bspTree); 
	}

	g_bIsInCompileLightMode = TRUE;
	// Die Reihenfolge ist wichtig
	// Lightmaps
	if (lightMode!=zWLD_LIGHT_VERTLIGHT_ONLY) {
		GenerateLightmaps		(lightMode, updateBBox3D);
	};

	// Vertex-Light 
	GenerateStaticVertexLighting	();

	// statische LichtInfos in BSP-Leafs refreshen
	GetBspTree()->CalcStaticLeafLightData();

	// statische Licht Caches im Vob ungueltig machen
	MakeVobLightingDirty();

	g_bIsInCompileLightMode = FALSE;
};

/* ----------------------------------------------------------------------------
	zCWorld::ResetVobLighting / static TraverseResetVobLighting

	26.10.2000	[SPECKELS]	Methode eingeführt
   ----------------------------------------------------------------------------*/

static void TraverseMakeVobLightingDirty (zCTree<zCVob>* node) 
{
	// process node	
	zCVob* vob = node->GetData();
	if (vob)
	{
		vob->SetLightColorDynDirty();
		vob->SetLightColorStatDirty();
	}	
	// recursive traversal
	zCTree<zCVob> *child = node->GetFirstChild(); 
	while (child) {
		TraverseMakeVobLightingDirty(child);
		child = child->GetNextChild();
	};
};

void zCWorld::MakeVobLightingDirty		()
{
	zERR_MESSAGE(7,0,"D: WLD: Make Vob-Lighting dirty");
	TraverseMakeVobLightingDirty(&globalVobTree);	
	zERR_MESSAGE(7,0,"D: WLD: ... finished");
};

/*
	// Initialise meshing, unshot radiosity and radiosity vectors
	
	patches = CreateMesh(polygons, edge_len);
	S = EmittedRadiosity(patches); // unshot radiosity: vector of length n
	B = S; // vector of length n

	// Iterate shooting steps

	while (true) {
		i			= FindMaxPowerIndex(patches);		// unshot radiosity * area
		radToShoot	= S[i];
		S[i]		= 0;

		for (j in patches)		// Shoot from patch i to patch j
			B[j] += radToShoot * FormFactor(i, j) * Vis1(i, j) * Reflectance[j];
			S[j] += radToShoot * FormFactor(i, j) * Vis1(i, j) * Reflectance[j];

		if (firstIteration)		
			firstPower = area(i) * radToShoot;
		else if (area(i) * radToShoot < firstPower * t_ratio)
			return;
	};
*/


/*
SPOTLIGHT:
-------------------------------------------------------------------
			dl->type = emit_spotlight;
			dl->stopdot = FloatForKey (e, "_cone");
			if (!dl->stopdot)
				dl->stopdot = 10;
			dl->stopdot = cos(dl->stopdot/180*3.14159);
-------------------------------------------------------------------
			case emit_spotlight:
				// linear falloff
				dot2 = -DotProduct (delta, l->normal);
				if (dot2 <= l->stopdot)
					goto skipadd;	// outside light cone
				scale = (l->intensity - dist) * dot;
				break;
-------------------------------------------------------------------
*/


/*
	TODO:
	x bei wenig intensity Varianz auf lightmap: keine generieren, sondern vert-Light
	x Schmutzraender vs. smooth-Filter
	x surfaces: 1 LM fuer mehrere coplanare polys
	* Phong (lerp normals)
	- lighting: anderer falloff
	- error-diffusion filter
	- Volume-Fog

	- Radiosity

	Radiosity-Probleme:
	- zu langsam
	- braucht zuviel Speicher (GIGA-BYTE !!)
	- Strategien:
		- nicht jedes LM-Texel als Patch nehmen, sondern evtl. Gruppen von Texeln
		  hierarchisch ? 
		  (Quake2 laesst z.B. nur maximal 65000 Patches zu, waehrend es weit mehr Texel gibt!)
		- anderes Radiosity-Verfahren ? Hierarchisch/Substructuring ?

	- Idee:
		- einfach & stumpf 2 Passes 
		- 1) Radiosity Pass mit halber (weniger?) Texel-Dichte. Hierbei wird allerdings als Radiosity
		     in den Patches nur das ambiente Licht akkumuliert.
			 (hierzu muss ja das Licht der Voblights ueber Raytracing in die Patches gelangen)
		- 2) Raytracing Pass mit normaler Texel-Dichte. Die Texel bekommen als ambientes Start-Licht
		     ueber Bilerp Licht aus den Patches des ersten Passes. Dann gelangt 

  - Idee: 
    Polys koennten Flag haben (castShadows), falls nicht castShadows=durchsichtig, wird der Ray mit der Farbe 
	des getroffenen Pixels eingefaerbt. (flipcode-shot)
	  Here you can really experiment. Try out other algos. Perhaps you come up with something new. For example I have added stained
	  windows. If you have an intersection with a polygon, check if the polygon is a window. If so, calculate the texel (the coord of the
	  texture) of the face and use it's color. If you have a red window, it just let's through the red components of the light (do you
	  remember the physics lessons, spectral components of the light, prisma and so on). So, set the color of the light to that color and
	  go on tracing the ray until you hit the light or some other polygon. That's simple. However calculating the texel is not that easy,
	  because you will need to deal with different uv-values, perhaps texture wrapping and so on. Check out some raytracing sites,
	  perhaps you find something. I can't give you any help here, because my algo is top secret again, just one hint : Draw a polygon on
	  a sheet of paper and set an intersection point into it. Then play around a bit and think of an algo you learned at school : "shortest
	  distance from a point to a line". You got it ???? Basically it's the other way round then calculating the 3D Point of a pixel in the
	  lightmap, edges and so on. I really hope you got that here, but that's all I can say at the moment.
*/

/*
	Aus POVRAY-Source ('93):

* DESCRIPTION
*
*   Calculate the Phong-interpolated vector within the triangle
*   at the given intersection point. The math for this is a bit
*   bizarre:
*
*      -         P1
*      |        /|\ \
*      |       / |Perp\
*      |      /  V  \   \
*      |     /   |    \   \
*    u |    /____|_____PI___\
*      |   /     |       \    \
*      -  P2-----|--------|----P3
*                Pbase    PIntersect
*          |-------------------|
*                         v
*
*   Triangle->Perp is a unit vector from P1 to Pbase. We calculate
*
*   u = (PI - P1) DOT Perp / ((P3 - P1) DOT Perp).
*
*   We then calculate where the line from P1 to PI intersects the line P2 to P3:
*   PIntersect = (PI - P1)/u.
*
*   We really only need one coordinate of PIntersect.  We then calculate v as:
*
*        v = PIntersect[X] / (P3[X] - P2[X])
*   or   v = PIntersect[Y] / (P3[Y] - P2[Y])
*   or   v = PIntersect[Z] / (P3[Z] - P2[Z])
*
*   depending on which calculation will give us the best answers.
*
*   Once we have u and v, we can perform the normal interpolation as:
*
*     NTemp1 = N1 + u(N2 - N1);
*     NTemp2 = N1 + u(N3 - N1);
*     Result = normalize (NTemp1 + v(NTemp2 - NTemp1))
*
*   As always, any values which are constant for the triangle are cached
*   in the triangle.
*
* CHANGES
*
*   -
*
*****************************************************************************

static void Smooth_Triangle_Normal(VECTOR Result, OBJECT *Object, INTERSECTION *Inter)
{
  int Axis;
  DBL u, v;
  VECTOR PIMinusP1;
  SMOOTH_TRIANGLE *Triangle = (SMOOTH_TRIANGLE *)Object;

  VSub(PIMinusP1, Inter->IPoint, Triangle->P1);

  VDot(u, PIMinusP1, Triangle->Perp);

  if (u < EPSILON)
  {
    Assign_Vector(Result, Triangle->N1);

    return;
  }

  Axis = Triangle->vAxis;

  v = (PIMinusP1[Axis] / u + Triangle->P1[Axis] - Triangle->P2[Axis]) / (Triangle->P3[Axis] - Triangle->P2[Axis]);

  // This is faster. [DB 8/94] 

  Result[X] = Triangle->N1[X] + u * (Triangle->N2[X] - Triangle->N1[X] + v * (Triangle->N3[X] - Triangle->N2[X]));
  Result[Y] = Triangle->N1[Y] + u * (Triangle->N2[Y] - Triangle->N1[Y] + v * (Triangle->N3[Y] - Triangle->N2[Y]));
  Result[Z] = Triangle->N1[Z] + u * (Triangle->N2[Z] - Triangle->N1[Z] + v * (Triangle->N3[Z] - Triangle->N2[Z]));

  VNormalize(Result, Result);
}

*/

/*
Consider a sharp shadow that cuts diagonally through your light map...

With [single-sample] ray tracing to a [point] light source, either a light map
texel is visible to the light source (lit) or it is not visible to the light
source (in shadow.)  You have a digital value here, on or off.

But with most global illumination techniques (MLT, Radiosity, etc.) the light
source is an area, not a point.  So the each texel along the edge of the
shadow boundary can see a portion of the light source and is lit according to
how much of the light source it can see.

So... If your shadow is the shape of a triangle when projected onto a light
map, then it would be the same as drawing that triangle into the light map
with anti-aliasing.  Automatic smooth edges.  Adding bilinear filtering to
this when you render softens the aliasing effect even more.

I've tried ray tracing and radiosity for light map generation.  If you've got
a good radiosity solution, you should try to avoid filtering if at all
possible (IMHO.)  Consider something sitting on the floor; the surface of the
floor under that object is in shadow.  If you blur the map, then the shadow
lingers around the edges of that object more than it normally would.

If you must use a filter, try this (we use this to clean up the 2-minute
quick-pass radiosity solutions):

It works like a 3x3 low-pass filter (blur) but it's just a little smarter.		!!!
Rather than performing the blur on every pixel, take the min/max intensity of
the 3x3 area, and if the difference between min/max is beyond a given
threshold, the blur is performed for that pixel.  Otherwise the result is left
unchanged. This way, you only blur the really harsh stuff, and leave
everything else alone.  The threshold lets you play with the results a bit.
It still has some of side-effects of normal filtering, but not quite as bad.

*/

/*

      The concept of light mapping is pretty simple. The illumination across a surface is rendered (usually
      pre-rendered) into a texture. When that texture is then applied to a given surface in the appropriate way, you get
      the illusion of illumination. This results in a more aesthetically pleasing scene without the performance cost of
      the actual lighting calculations, but with the cost of static pre-calculated lighting. 

      The first steps 

      We'll start with a few assumptions. First, that you're targeting a platform with 3D acceleration, and second, that
      you've already got your scene loaded up and ready to play with. 

      We'll need some extra data to manage our light maps. We'll need an ID to each surface (i.e. polygon) in the
      scene. We'll need this because there will be just as many textures as we have polygons since they each may be
      illuminated uniquely. Along with this ID, we'll need to store a new set of texture coordinates for each polygon. This
      way, the polygon can have a texture applied to it, and a light-map applied to it. By storing unique UV values for
      textures and light-maps, we allow each to be mapped independently. If you're planning to support software
      rendering, this might not be such a great idea, but this is beyond the scope of this document (don't you just hate
      it when people write stuff like that?) 


      The light-map UVs 

      We'll need to pick the light-map UVs for each surface. This is a pretty simple process, but before I get into this,
      let's discuss a few small details. 

      Texel density is very important. This refers to how tightly packed the texels are applied to the surface. For
      example, a one-square-foot surface with a 256x256 texture applied to it will have a much higher texel density than
      a the same surface with only a 32x32 applied to it. 

      Ideally, we would like to have a uniform texel density across the entire scene (at least, to start with…) 

      Aside from texel density, we need to consider polygon seams (where two adjoining polygons meet along a shared
      edge.) These shared-edged polygons should have similarly mapped light maps so that the seam is not
      noticeable. This usually applies to the standard texture maps, but it is more important for light maps. Even
      non-planar polygons should have a shared mapping across the bend where they meet to keep the light
      continuous. 

      The only way to accomplish this is to maintain the same texel density as well as the same mapping scheme. 

      Another thing we want to try to accomplish is to have an even resolution across a surface. Ideally, we want to
      minimize the "stretch" of a light-map across any surface, giving us as close to an equal resolution in U as in V. 


      The mapping scheme 

      To accomplish this seamless mapping across planar as well as non-planar surfaces, we'll need a shared frame of
      reference (a frame of reference that all polygons fit into) for all mapping. I'll use world-space coordinate system
      as a frame of reference for this example, but feel free to find your own. 

      World-space mapping is done by using two of the three world-space components (X&Y, Y&Z or Z&X) and
      applying them directly to the UV coordinates. By using these world-space coordinates we effectively apply a
      planar mapping to everything in the scene using the plane defined by the coordinates chosen. And magically, any
      polygons that share a common edge (and hence, vertices that define those edges) will end up with the same UV
      values at those edges. 

      To properly map a 3D scene, we can't use just one planar mapping, we need to use all three (X/Y/Z). To
      accomplish this, we simply consider each surface normal. For the surfaces whose normal is primarily in the X/Y
      plane (i.e. Z is the largest value in the normal) we'll use the X&Y world-space coordinates… 


       if (surface.normal.z > surface.normal.y && surface.normal.y > surface.normal.x)
       {
               for (each vertex i)
               {
                       surface.lightmap[i].u = surface.vertex[i].x;
                       surface.lightmap[i].v = surface.vertex[i].y;
               }
       }

       if (surface.normal.y > surface.normal.x && surface.normal.x > surface.normal.z)
       {
               for (each vertex i)
               {
                       surface.lightmap[i].u = surface.vertex[i].z;
                       surface.lightmap[i].v = surface.vertex[i].x;
               }
       }

       if (surface.normal.x > surface.normal.z && surface.normal.z > surface.normal.y)
       {
               for (each vertex i)
               {
                       surface.lightmap[i].u = surface.vertex[i].y;
                       surface.lightmap[i].v = surface.vertex[i].z;
               }
       }



      In the above example code, you'll see that the planar mapping is applied specific to the surface direction to get
      the most resolution out of each surface. Since world-space is a 3-space, we'll get seamless edges across
      non-planar polygons as well as planar polygons. 

      You may find that world-space coordinates will give you a mapping that is not ideal in terms of resolution or texel
      density. You can adjust this by applying a scalar to each vertex before applying it to the UV value. For example,
      if your world space coordinate system is mapped to a 1:1 correlation of units to feet, and you want two texels per
      feet, simply multiply your light-map UV values by 2. 

      The resolution of the light maps is completely up to you. I will suggest that you use as high of a resolution as you
      can get away with. Play with it and see what you find works best. 


      Light-map sizes 

      Many 3D accelerators have limitations on their texture dimensions (power of two sizes only, etc.) and maximum
      resolutions (2048x2048, etc.) 

      If a surface requires a light-map that exceeds your 3D accelerator's maximum resolution, that surface will need to
      be split. Surfaces require an odd sized light-map (65x75) on an accelerator that requires power-of-two texture
      dimensions will end up wasting some space. This waste can be reduced, however (see "Optimizations"). 


      Caching the textures 

      Caching these textures should work pretty much the same as caching the standard textures. I'm only including
      this section to point out one important aspect. Each surface will have its own unique light-map, which means a
      LOT of light maps. 

      Fortunately, these maps are usually much smaller than the standard textures used to give the scene its detail.
      This reduces the amount of memory required, but your combined light maps will probably be much larger than
      your combined detail texture library. 


      Optimizations 

      There really are a lot of potential optimizations. For example, if you have many small surfaces that map to the
      same planar mapping and share edges, these surfaces can be combined into a single light-map. This improves
      your ratio of light-maps to surfaces as well as reduces potential wasted light-map texture space. 

      You could take this a step further and place smaller textures into the wasted areas of larger textures, though this
      can prove to be quite tricky. 

      Using n-gons rather than triangles for your data can effectively help accomplish these tasks by combining small
      planar polygons. 

      This list goes on… */

// ========================================================================================================================

/*
Now that's all well and good, but the most common question I've heard about generating lightmaps has got to
 be: How do I get from 2D texture (lightmap) coordinates to world space (so that I can calculate the value for
 that lumel)? You DO have access to the 3D points at the vertices, so its not entirely 2D texture coordinates to
 world space (that would be impossible; many surfaces have the same texture coordinates). So then, how do
 you do it? This bothered me for a while because I wanted an "exact" solution (using the exact orthogonal uv
 vectors) for arbitrary surfaces, but as it turns out an "exact" solution in many cases wouldn't look right because
 the textures don't line up. So I resorted to planar mapping. I honestly have no idea if this is the method that
 most engines use, but I'm guessing it is. The method I use to do this is nothing new or special but it works very
 nicely. If you would like to know more about planar mapping, check out the archives on The Fountain Of
 Knowledge. Paul Nettle explains (in more than one response) how planar texture mapping works and why it is
 good. This would be nice to read if you don't know what I'm talking about right now. To generate my lightmaps,
 I basically do the following for each surface (minor clarifications added 08/18/99 by request): 

    * Determine the primary axis plane based on the absolute value of the normal for this surface. 
    * Assign the UV vectors based on this plane. This axis plane, the one that the surface is nearest to in
      orientation, is the one we will use for the planar mapping, so we assign the surface the U and V
      vectors of the plane (ie, the normalized vectors pointing 'right' and 'down' respectively along that
      plane. You don't have to use 'right' and 'down', but it makes more sense to trace in those
      directions as you'll see in the loop below). 
    * Get the min and max (2D vertices) along that plane. This means to use only the 2 relevant
      coordinate components for this particular plane. For example if you're using the XY plane, only x and
      y at the vertices count for this step. 
    * Determine the texture plane origin (p) from the min 
    * Determine the u and v lengths (max-min (on the plane)) 
    * Determine lightmap coordinates:
      (for each vertex) ltu=((pu - minu) / ulen) and ltv=((pv - minv) / vlen)
      where pu and pv are the x and y in PLANE space (not world space). 
      pu and pv are nothing new, they are the 2 relevant components at the vertices for this particular
      plane. The 'x' and 'y' in relation to the plane. 

 Now you have the UV vectors and lightmap coordinates to do whatever you need. The actual sample point
 determination for each uv when generating the lightmap can look like the following in psuedo-code, unoptimized
 for clarity: 

      usteps = ulen / [lightmap_w];
      vsteps = vlen / [lightmap_h];

      for(int ly=0; ly < [lightmap_h]; ly++)
      {
              for(int lx=0;  lx < [lightmap_w]; lx++)
              {
                     xs = uvec * (lx * usteps)
                     ys = vvec * (ly * vsteps)

                     sample= xs + ys + p

                     ... actual lighting calculation at this sample point
                     ... store the result at position (lx, ly) in the lightmap;
              }
      }


 The sample point is in world space and that's what I use for lighting or whatever else. There are many obvious
 optimizations that you can make to the above, but the idea remains the same. 

 I hope I didn't make any mistakes in the above explanation. If I did, its likely something I typed wrong or forgot
 to type because the algorithm works (as far as I know ;). This approach is very easy and the results look nice.
 Obviously my worst case would be when a polygon is slanted at 45 degrees to some plane, but it still doesn't
 look too bad. I was talking to a fellow coder, Luke Hodorowicz, about an approach like this that he's working on
 as well and he agrees that the skewing isn't really that noticeable even in those worst case situations;
 especially in conjunction with techniques like bilinear filtering. 

*/

// ========================================================================================================================

/*
Caluclating UV's
You have to calculate seperate UV's for the lightmaps, you can't just use the textures UV coordinates. 
The technique used to do this is called planar mapping, and is very useful and pretty simple. 
First you have to decide which plane to map on, this is done by check which component of the polygons normal 
that is largest. If X is largest the you map on the YZ(or ZY) plane, if Y is largest the map on the XZ, then naturally 
if Z is the largest you map to the XY plane. Remember to check the absolute value of the normal component, fabs(). 
Now let's say that Y was largest, and you want to map to the XZ plane, then you just assign your lightmaps U values 
as X, and you V values as Z. Like this: 

for(i = 0; i < NumVerts; i++)
{
   Poly.LightmapUV[ i ].U = Vertices[ Poly.Verts[ i ] ].X;
   Poly.LightmapUV[ i ].V = Vertices[ Poly.Verts[ i ] ].Z;
}

You could now say you have your UV's in 3D worldspace, but you want them in the 2D texture space. 
To do that, you have to calculate the 2D bounding box of the polygon. That's easy, just set your 
min and max UV's to the UV's of the first lightmap UV, and then loop though the others and see if they're 
smaller of greater than that value, something like this: 

   uvMin.U = Poly.LightmapUV[ 0 ].U;
   uvMin.V = Poly.LightmapUV[ 0 ].V;
   uvMax.U = Poly.LightmapUV[ 0 ].U;
   uvMax.V = Poly.LightmapUV[ 0 ].V;

   for(i = 0; i < NumVerts; i++)
   {
         if( Poly.LightmapUV[ i ].U < uvMin.U )
           uvMin.U = Poly.LightmapUV[ i ].U;
         if( Poly.LightmapUV[ i ].V < uvMin.V )
           uvMin.V = Poly.LightmapUV[ i ].V;

         if( Poly.LightmapUV[ i ].U > uvMax.m_fU )
           uvMax.U = Poly.LightmapUV[ i ].U;
         if( Poly.LightmapUV[ i ].V > uvMax.m_fV )
           uvMax.V = Poly.LightmapUV[ i ].V;
   }

Now get the Delta between these two, then you subtract the Min UV value from all lightmap UVs to 
make all lightmap UVs relative to that point. But your lightmap coords must range from 0.0 to 1.0, 
so you divide you lightmap UVs by the Delta value. That's it. 

   uvDelta.U = uvMax.U - uvMin.U;
   uvDelta.V = uvMax.V - uvMin.V;

   for(i = 0; i < NumVerts; i++)
   {
         Poly.LightmapUV[ i ].U -= uvMin.U;
         Poly.LightmapUV[ i ].V -= uvMin.V;
         Poly.LightmapUV[ i ].U /= uvDelta.fU;
         Poly.LightmapUV[ i ].V /= uvDelta.V;
   }


Lumel worldspace calculation
Now what? Well, now you have to calculate the world space position for each lumel, lumel is a pixel 
in the lightmap, the equivalent of texel in a texturemap. 
Getting the lumels into world space is pretty tricky, and pretty hard to explain, so I can understand 
if you don't understand this right away. 

Like I said before you've calculated the 2D bounding box of the polygon, so it's really no problem getting 
lumels, but then you would have to have only orthogonal polygons for it too work. 
The first thing you have to do is the get the vertex with the lightmap coord 0;0, then get the position of 
that vertex, that value will be the value that all your lumels have to be displaced by. 

Then you have to calculate the two edge vector (the blue arrows in the picture), one vector from 0;0 to 1;0 
and one from 0;0 to 0;1. This is no problem you say, just use the uvMin and uvMax you calculated. Yes, but 
these are just in one plane, lets say they are in the XZ plane as we used before. So you will have to calculate 
Y to get it right. To do this you have to used the Plane equation of your polygon. 
The plane equation is:
Ax + By + Cz + D = 0 
But you want to calculate Y:
y = - ( Ax + Cz + D ) / B 
Not too hard to understand, huh?
Now you can calculate the two edge vectors: 

    Y = - ( norm.X * uvMin.U + norm.Z * uvMin.V + Polygons[ i ].Plane.m_fDistance ) / norm.Y;
   UVVector = CVector( uvMin.U, Y, uvMin.V );
    Y = - ( norm.X * uvMax.U + norm.Z * uvMin.V + Polygons[ i ].Plane.m_fDistance ) / norm.Y;
   Vect1    = CVector( uvMax.U, Y, uvMin.V );
    Y = - ( norm.X * uvMin.U + norm.Z * uvMax.V + Polygons[ i ].Plane.m_fDistance ) / norm.Y;
   Vect2    = CVector( uvMin.U, Y, uvMax.V );      

 Edge1 = Vect1 - UVVector;
 Edge2 = Vect2 - UVVector;

When you have the two edge vector, it's just to interpolate them. 
To get your lumel for a pixel in your 16x16 lightmap, do like this: 


 U = pixelX / 16;
 V = pixelY / 16;
 NewEdge1 = Edge1 * U;
 NewEdge2 = Edge2 * V;
 LumelPosition = ZeroVector + NewEdge1 + NewEdge2;

ZeroVector is the vector you calculated in the beginning. That's it, now you have your lumel in world space. 
*/
// ========================================================================================================================

/*April 14, 1999 

radiosity - 09:00 EST 
     radiosity is the rate at which (light) energy leaves a surface. for an environment consisting of diffuse surfaces, the radiosity equation is 

                              |\
                              |
        B(x)  =  Be(x) + p(x) |  G(x, x')B(x') dx'
                              |
                             \|

              =  Be(x) + p(x)E(x)
              =  Be(x) + Br(x)

     where B(x), the radiosity at point x measured in energy per unit time per unit area, is the sum of emitted radiosity Be(x) and the reflected
     radiosity Br(x). reflectivity, a function of wavelength, is denoted p(x). the integral is taken over the hemisphere about x. G(x, x') accounts for the
     relative orientation, distance and visibility of the surfaces. 

                        cos(tx) cos(tx')
        G(x, x')  =   --------------------  V(x, x')
                         pi |x - x'|2


     V(x, x') is equal to one if point x' is visible from point x, zero otherwise. E(x) is irradiance, the amount of energy per unit area received from
     other surfaces. 

     the approach of hierarchical radiosity subdivides, recursively, each input surface into a set of subpatches until the measure of interaction is
     constant across a given subpatch. each node in the hierarchy represents an area of the original surface. two nodes are linked if the interaction
     between them can be computed to within some predefined accuracy. 

     the following code fragment establishes all linkages between initial patches p and q. FormFactor( ) computes the percentage of light interaction
     as the integral of G(x, x'), defined eariler, with respect to the area of the receiver patch, taking into account, also, the degree of occlusion. if
     either form factor is larger than the estimate Fe, the patch is subdivided into four new quadrilaterials. the subdivision is stored in a quadtree data
     structure. Subdivide( ) returns false if the patch cannot be subdivided further, in that its area is less than Ae. 

        void Refine(Patch *p, Patch *q, double Fe, double Ae)
        {
           double   Fpq, Fqp;

           Fpq = FormFactor(p, q);
           Fqp = FormFactor(q, p);

           if (Fpq < Fe && Fqp < Fe)
               Link(p, q);
           else {
               if (Fpq > Fqp) {
                   if (Subdivide(q, Ae)) {
                     Refine(p, q->ne, Fe, Ae);
                     Refine(p, q->nw, Fe, Ae);
                     Refine(p, q->se, Fe, Ae);
                     Refine(p, q->sw, Fe, Ae);
                   } else Link(p, q);
               } else {
                   if (Subdivide(p, Ae)) {
                     Refine(q, p->ne, Fe, Ae);
                     Refine(q, p->nw, Fe, Ae);
                     Refine(q, p->se, Fe, Ae);
                     Refine(q, p->sw, Fe, Ae);
                   } else Link(p, q);
               }
           }
        }

     once all form factors have been determined, the radiosity for each patch is calculated. Gather( ) accumlates the total amount of energy received
     by a patch directly and from its parent subpatches. the average brightness of each patch is stored in B and its diffuse colour is stored in Cd. the
     brightness, gathered from the list of all interactions in q, is stored in Bg. 

        void Gather(Patch *p)
        {
           Patch    *q;
           double   Fpq;

           if (p != NULL) {
              p->Bg = 0.0;
              for (q=p->interactions; q != NULL; q=q->next) {
                 Fpq = FormFactor(p, q)
                 p->Bg += Fpq * p->Cd * q->B;
              }
              Gather(p->ne);
              Gather(p->nw);
              Gather(p->se);
              Gather(p->sw);
           }
        }


     the disadvantage of hierarchical radiosity is that shadow boundaries tend to be jagged because subdivision occurs regularly and, therefore, does
     not follow the contour of the shadow. 
     —
     Hanrahan, P., D. Salzman, and L. Aupperle, "A Rapid Hierarchical Radiosity Algorithm," Computer Graphics, SIGGRAPH 1991
     Proceedings, 25(4):197-206

     Kajiya, J.T., "The Rendering Equation," Computer Graphics, SIGGRAPH 1986 Proceedings, 20(4):143-149

     Lischinski, D., F. Tampieri, and D.P. Greenberg, "Combining Hierarchical Radiosity and Discontinuity Meshing," Computer Graphics,
     SIGGRAPH 1993 Proceedings, 27(4):199-208 
*/

/*
DYNAMIC TEXTURE LIGHTS

http://www.flipcode.com/tutorials/tut_omnilights.htm

Projecting a lightmap for an omnidirectional light is different than projecting a lightmap for a directional light. With
omnidirectional lights, there is no need to worry about perspective corrections beyond what is required for normal texturing. 

When a light projects the lightmap onto a face, the center of the lightmap texture is located at the point that is closest to the
light. This point need not actually lie on the face. However, it will lie on the plane of the face. 


Texture Coordinates 


To compute the texture coordinates of the lightmap for each of the face’s vertices is a relatively easy thing. First, two vectors
must be generated, the vS and vT vectors. 

   vS = Normalize (vFaceVertex - vClosestPointOnPlane)
   vT = vLightNormal cross vS

   Where:
        vFaceVertex is any vertex of the face
        vClosestPointOnPlane is the closest point on the plane to the light source
        vLightNormal is the normal vector between the light source and the closest point on the plane.



The final part required to compute the texture coordinates from the vertex is the scale of the lightmap. As the plane gets farther
away from the light source, the size of the circle generated by the light gets smaller also. The scale of the lightmap is defined
as: 

   Scale = (1 / (sqrt (LightIntensity2- DistanceFromPlane2)) / LightIntensity) / LightIntensity * 2



To compute the texture coordinates for a given vertex, use the following equations 

   s = ((vFaceVertex - vClosestPointOnPlane) dot vS) * Scale + .5
   t = ((vFaceVertex - vClosestPointOnPlane) dot vT) * Scale + .5




Lightmap Intensity and Color 


Since the intensity of a pixel is defined by the previous equation, the intensity of the lightmap at the center of the lightmap must
be adjusted to match the required intensity. With OpenGL, the color and intensity of a texture can be adjusted by invoking
glColor. If the plane actually traveled through the center of the light, then the intensity of the light would be 100%, thus glColor
would be invoked as glColor4f (1, 1, 1, 1) for a white light. As the plane is moved farther away from the light source, the RGB
values for glColor would be reduced as specified by the equation. 

   LightMapIntensity = 1 - (DistanceFromPlane2 / LightIntensity2)
   LightMapColor = LightColor * LightMapIntensity

   Where:
        LightColor is the color of the light in RGB form.



Once LightMapColor has been computed, use that value in conjunction with glColor4f to scale the intensity and set the color of
the lightmap. 

*/

/*

LM-Generierung => 
- Crystal-Space
- Genesis3D

*/
/*
Radiosity: FlipCode Tutorial
*/
/*
	if (kbPressed(KEY_F6)) {
		lightMapBilerpFilter = !lightMapBilerpFilter;
		if (lightMapBilerpFilter)	SetBilerpFiltering(zRND_BILERP_FILTER_ON);
		else						SetBilerpFiltering(zRND_BILERP_FILTER_OFF);
	};
*/

/*
Monolith update 19:02 PST server time / 3:02 AM your time Billy 'Wicked' Wilson
And speaking of .plan updates, Monolith's Mike Dussault (LithTech2 engine code p1mp) updated his .plan with the
following (once again, quite a few fairly tasty bits in this one):

   The coolest thing that got in lately is lightmap animations. Basically, we can now get shadowed effects for
   a bunch of things in the environment: 

   - When doors open, light floods out. 
   - Flickering lights in the environment cast shadows. 
   - Keyframed objects and lights cast shadows on things. 
   - As the sun rotates over the world, the shadows on everything move. 

   I'll be working on Certain Cool Enhancements to this next week! 

   I must say again how impressed I am by Third Law. They never cease to amaze me. In addition to building
   their game, they've added a ton of awesome features to their version of the engine. I can't believe how
   fast these guys work! 

   DX7 is in now. There are a lot of things that I like about it and a few things I dislike about it (but I had my
   chance to complain so I won't complain now!) Overall, the API is a lot cleaner and easier to use (especially
   to initialize). 
   It was really easy to convert everything over. 

   It remains to be seen whether or not there will be any performance gain with skeletal animation using the
   multimatrix blending (ie: hardware T&L for skeletal animation).*/


/*

  16*16 + 1024	= 1280		PAL8
  16*16 * 2		= 512		16BIT

  32*32 + 1024	= 2048		PAL8
  32*32 * 2		= 2048		16BIT

  64*64 + 1024	= 5120		PAL8
  64*64 * 2		= 8192		16BIT

  <= 32x32 (=1024) 16BIT benutzen !!

*/

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
