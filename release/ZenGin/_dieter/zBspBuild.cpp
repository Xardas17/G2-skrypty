/******************************************************************************** 
 
     $Workfile:: zBSPBuild.cpp        $                $Date:: 27.01.01 19:42   $
     $Revision:: 23                   $             $Modtime:: 27.01.01 14:05   $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created:

 * $Log: /current_work/ZenGin/_Dieter/zBSPBuild.cpp $
 * 
 * 23    27.01.01 19:42 Moos
 * 
 * 22    25.01.01 17:01 Hildebrandt
 * 
 * 21    22.11.00 19:42 Speckels
 * 
 * 20    22.11.00 19:25 Speckels
 * 
 * 19    22.11.00 19:20 Speckels
 * 
 * 18    17.11.00 19:29 Moos
 * 
 * 17    10.11.00 1:43 Speckels
 * 
 * 16    22.09.00 15:58 Hoeller
 * 
 * 15    11.09.00 19:40 Speckels
 * 
 * 14    31.08.00 17:04 Hildebrandt
 * 
 * 13    21.08.00 17:18 Hildebrandt
 * 
 * 12    15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 11    21.07.00 14:28 Hildebrandt
 * 
 * 10    6.07.00 13:33 Hildebrandt
 * 
 * 6     6.05.00 17:56 Hildebrandt
 * zenGin 089f
 * 
 * 5     3.05.00 23:57 Hildebrandt
 * zenGin 089d
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 6     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 4     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 3     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 23 $ ($Modtime: 27.01.01 14:05 $)


#include <zCore.h>
#include <zBsp.h>
#include <zVisual.h>
//#include <zWorld.h>			// traceRayReport, tmp, debug

//#define zBSP_SAFE

#ifdef ZENGINE_DEBUG
//	#define zBSP_DONT_CREATE_LOD
//	#define zBSP_DEBUG_CREATE_LOD
#endif

#define zBSP_DONT_CREATE_LOD

#pragma warning( disable: 4244 ) 

//const zREAL	zBSP_OUTDOOR_MIN_CELL_AREA	= (500*500);
//const zREAL	zBSP_OUTDOOR_MIN_CELL_AREA			= (300*300);
const zREAL	zBSP_OUTDOOR_MIN_CELL_AREA			= (1000*1000);
const zREAL	zBSP_OCTREE_SOLID_MIN_CELL_VOLUME	= (500*500*500);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     CONSTRUCTION - BSP
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static zCCBspTree *actCBspTree;

zCCBspTree::zCCBspTree() {
	mesh			= zNEW(zCMesh);
	SetBspTreeMode	(zBSP_MODE_INDOOR);
};

void zCCBspTree::SetBspTreeMode (const zTBspTreeMode& bspMode) 
{
	bspTreeMode = bspMode; 
	// defaults, safety
	cfg_bspType			= zBSP_TYPE_OCTREE;
	cfg_spanningMode	= zSPANNING_PUSHBOTH;		
	cfg_useAllPolys		= TRUE;
	cfg_optimize		= 0.5F;
	cfg_wbalance		= 0.6F;
	cfg_wsplit			= 0.2F; 
	cfg_wplanar			= 0.2F;
	cfg_portalize		= FALSE;

	if (bspMode==zBSP_MODE_INDOOR) 
	{
/*
		// ALT: leafy-bsp
//		cfg_bspType			= zBSP_TYPE_OCTREE_SOLID;
		cfg_bspType			= zBSP_TYPE_LEAFY_BSP;
		cfg_spanningMode	= zSPANNING_PUSHBOTH;
//		cfg_spanningMode	= zSPANNING_SPLIT;
		cfg_portalize		= FALSE;
		cfg_useAllPolys		= TRUE;
		cfg_optimize		= 1.0F;
		cfg_wsplit			= 0.6F;
		cfg_wbalance		= 0.2F;
		cfg_wplanar			= 0.2F;
*/
		// NEU: 'octree' auch fuer indoor
		cfg_bspType			= zBSP_TYPE_OCTREE_SOLID;
		cfg_spanningMode	= zSPANNING_PUSHBOTH;
		cfg_portalize		= FALSE;
		cfg_useAllPolys		= TRUE;
		cfg_optimize		= 1.0F;
	} else 
	if (bspMode==zBSP_MODE_OUTDOOR) 
	{
		// octree
		cfg_bspType			= zBSP_TYPE_OCTREE;
		cfg_spanningMode	= zSPANNING_PUSHBOTH; 
//		cfg_spanningMode	= zSPANNING_CENTER;
//		cfg_spanningMode	= zSPANNING_SPLIT;

		cfg_useAllPolys		= TRUE;
		cfg_optimize		= 1.0F;
	};
};


zCCBspTree::~zCCBspTree() {
	zRELEASE (mesh);
	// Tree, polyLists werden autom. gelöscht
};

void zCCBspTree::DeleteTree	() {
	delete bspRoot.front;
	delete bspRoot.back;
	bspRoot.front = bspRoot.back  = 0;
	bspRoot.polyList.DeleteList(); 
};

void zCCBspTree::AddMesh (zCMesh* mesh) {
	AddMesh (mesh, Alg_Identity3D());
};

void zCCBspTree::AddMesh (zCMesh* inMesh, const zMATRIX4& trafoObjToWorld) { 
	if (!mesh) return;

	zERR_MESSAGE(3,zERR_BEGIN,"D: BSP: Adding Polys To Bsp-Mesh "+inMesh->GetMeshName()+" ("+zSTRING(inMesh->numPoly)+" polys) ...");
	mesh->MergeMesh (inMesh, trafoObjToWorld);
	zERR_MESSAGE(3,zERR_END,"");
};

// FIXME: temp, clean .. ??

static int splits;
static int numNodes;
static int statNumLeafs;
static int numPortals;

void zCCBspTree::BuildTree (const zREAL optimize) 
{
	zerr.Message ("D: BSP: Start BuildTree...");
	// alle Mesh-Polys in die Root.PolyList eintragen
	for (int i=0; i<mesh->numPoly; i++) {
		bspRoot.AddPoly (mesh->Poly(i)); 
	};
	//
	int num		= bspRoot.polyList.GetNumInList();
	splits		= 0;
	numNodes	= 0;
	actCBspTree	= this;

	// Params
	zerr.Message ("D: BSP: Optimize: "+zSTRING(optimize,4));
	cfg_optimize = optimize;
	if (cfg_optimize<=0) cfg_optimize=0.00001F;
	
	// doit
	bspRoot.BuildTree (); 
	
	int nnodes = CountNodes();
	int nleafs = CountLeafs();
	zerr.Message ("D: BSP: ... Finished BuildTree.");
	zerr.Message ("D: BSP: * Polys, before: "+zSTRING(num)+", after: "+zSTRING(num+splits));
	if (splits>0)
	zerr.Message ("D: BSP: * Splits: "+zSTRING(splits));
	zerr.Message ("D: BSP: * Num Nodes: "+zSTRING(nnodes)+", Leafs: "+zSTRING(nleafs)+ "("+
					zSTRING(int(nnodes*sizeof(zCBspNode)+nleafs*sizeof(zCBspLeaf)))+" bytes)"); 

	//
	if (actCBspTree->cfg_bspType==zBSP_TYPE_OCTREE_SOLID) 
	{
		bspRoot.CalcSubtreeBBox3DCell ();
	} else 
	{
		bspRoot.CalcSubtreeBBox3D ();
	};

	//
	{
		int numKilled = 0;
		if (GetBspTreeMode()==zBSP_MODE_OUTDOOR) 
		{
			numKilled = bspRoot.OutdoorKillRedundantLeafs();		// muss nach CalcBBox3D
		} else
		if (GetBspTreeMode()==zBSP_MODE_INDOOR) 
		{
//			numKilled = bspRoot.IndoorKillRedundantLeafs();		// muss nach CalcBBox3D
			numKilled = 0;
		};
		if (numKilled>0)
			zerr.Message ("D: BSP: Killed Nodes: "+zSTRING(numKilled));
	};

	//
	int max,min,avg;
	CountDepth (max,min,avg);
	zerr.Message ("D: BSP: * Depth, min: "+zSTRING(min)+", max: "+zSTRING(max)+", avg: "+zSTRING(avg));

	// Portalizing
	if (cfg_portalize)	bspRoot.Portalize	();

	//	bspRoot.DescribeTree ();
};

void zCCBspNode::RemovePoly	(zCPolygon *poly) {
	zTPolyNode *polyNode  = polyList.Get (0);
	while (polyNode) {
		if (polyNode->poly==poly) {
			polyList.Delete (polyNode);
			return;
		};
		polyNode = polyNode->next;
	};
};

// **************************************************************************************************
//  Generating LOD-Level pro zCCBspNode	(zBSP_MODE_OUTDOOR)
// **************************************************************************************************


/*

Noch zu klaerendes:

- zCArraySort Default Compare ? 

- Ist die borderVertList nun ueberfluessig ? (wird doch schon alles ueber Edge::CalcIsBorderVert() geregelt, oder?)
- Inkonsistenzen: wie koennen sich die BorderVert-Eigenschaften einer Edge bei einem Recalc aendern ??
- degen Polys ? wodurch ?
- Ein RecalcEdge, dass sein Polys nicht findet ? kann das sein ?
- Ein und dasselbe Poly kann in beiden vertNeighbour-Lists sein..
*/

static int ComparePolyPtr (const void* poly1, const void* poly2) {
	zCPolygon	*p1		= (*((zCPolygon**)poly1));
	zCPolygon	*p2		= (*((zCPolygon**)poly2));
	zDWORD		ptr1	= zDWORD(p1);
	zDWORD		ptr2	= zDWORD(p2);
	if (ptr1< ptr2)		return -1;
	if (ptr1==ptr2)		return  0;
	else				return +1;
};

#ifdef zBSP_DEBUG_CREATE_LOD

#include <zInput_Win32.h>
#include <zWin32.h>
#include <zMoving.h>

static zBOOL					dbg_LOD_camPosSet	= FALSE;
static zBOOL					dbg_LOD_show		= TRUE;
static zCMaterial				*dbg_LOD_matA		= 0;
static zCMaterial				*dbg_LOD_matB		= 0;
static zCMaterial				*dbg_LOD_mat1		= 0;
static zCMaterial				*dbg_LOD_mat2		= 0;
static zCArraySort<zCPolygon*>	dbg_LOD_borderPolyList;
static zCCBspNode				*dbg_LOD_node		= 0;

static void Dbg_LOD_RenderNodeSubtree	(zCCBspNode *node=0) 
{
	if (!node)	node=dbg_LOD_node;

	if (node->IsLeaf() || node->HasLOD()) {
		const zTBBox3D& bbox3DCell= node->bbox3DCell;
		bbox3DCell.Draw		(GFX_YELLOW);
/*		zlineCache.Line3D (zVEC3(bbox3DCell.mins[VX], bbox3DCell.mins[VY], bbox3DCell.mins[VZ]), zVEC3(bbox3DCell.mins[VX], bbox3DCell.maxs[VY], bbox3DCell.mins[VZ]), GFX_YELLOW, TRUE);
		zlineCache.Line3D (zVEC3(bbox3DCell.mins[VX], bbox3DCell.mins[VY], bbox3DCell.maxs[VZ]), zVEC3(bbox3DCell.mins[VX], bbox3DCell.maxs[VY], bbox3DCell.maxs[VZ]), GFX_YELLOW, TRUE);
		zlineCache.Line3D (zVEC3(bbox3DCell.maxs[VX], bbox3DCell.mins[VY], bbox3DCell.mins[VZ]), zVEC3(bbox3DCell.maxs[VX], bbox3DCell.maxs[VY], bbox3DCell.mins[VZ]), GFX_YELLOW, TRUE);
		zlineCache.Line3D (zVEC3(bbox3DCell.maxs[VX], bbox3DCell.mins[VY], bbox3DCell.maxs[VZ]), zVEC3(bbox3DCell.maxs[VX], bbox3DCell.maxs[VY], bbox3DCell.maxs[VZ]), GFX_YELLOW, TRUE);
*/
	};

	if (node->front) Dbg_LOD_RenderNodeSubtree (node->front);
	if (node->back ) Dbg_LOD_RenderNodeSubtree (node->back);
};

static void Dbg_LOD_PrepareRemovePolys	(zCPolygon* poly1, zCPolygon* poly2) 
{
	if (!dbg_LOD_matA) { dbg_LOD_matA=zNEW(zCMaterial()); dbg_LOD_matA->SetColor (255,50 ,50); };
	if (!dbg_LOD_matB) { dbg_LOD_matB=zNEW(zCMaterial()); dbg_LOD_matB->SetColor ( 50,255,50); };
	dbg_LOD_mat1 = poly1->GetMaterial();	poly1->material = dbg_LOD_matA;
	dbg_LOD_mat2 = poly2->GetMaterial();	poly2->material = dbg_LOD_matB;
};

static void Dbg_LOD_DePrepareRemovePolys	(zCPolygon* poly1, zCPolygon* poly2) 
{
	poly1->material = dbg_LOD_mat1;
	poly2->material = dbg_LOD_mat2;
};

static void Dbg_LOD_SetCamPos (zCArraySort<zCPolygon*> &polyList) 
{
	zCCamera *cam = zCCamera::activeCam;
	if (!cam) return;

	zTBBox3D box;
	box.Init();
	for (int i=0; i<polyList.GetNum(); i++) {
		for (int j=0; j<polyList[i]->polyNumVert; j++) {
			box.AddPoint (polyList[i]->vertex[j]->position);
		};
	};

	zPOINT3 pos			= box.GetCenter();
						
	zCVob *vob			= cam->GetVob();
	zMAT4 mat			= vob->trafo;
//pos					= mat.GetTranslation();
//	pos[VY]				= mat.GetTranslation()[VY];
//	pos[VY]				= 8400.0F;
	pos[VY]				= box.maxs[VY] + 1.0F*(box.maxs[VY]-box.mins[VY]);
	mat.SetAtVector		(zVEC3(0,-1,0));
	mat.SetUpVector		(zVEC3(0, 0,1));
	mat.SetRightVector	(zVEC3(1, 0,0));
	mat.SetTranslation	(pos);
	vob->SetTrafo		(mat);

	cam->Activate();
	dbg_LOD_camPosSet	= TRUE;
};


/* ----------------------------------------------------------------------
	
    Dbg_LOD_Render()

	16.11.2000	[Moos]	
                Auf neue Vertices umgestellt

   ---------------------------------------------------------------------- */


static void Dbg_LOD_Render (zCArraySort<zCPolygon*> &polyList, int wireCol=GFX_GREEN, zBOOL drawWireOnly=FALSE) 
{
	if (!dbg_LOD_show) return;

	if (!dbg_LOD_camPosSet)		Dbg_LOD_SetCamPos (polyList);

	int polyCtr;
	static int masterFrameCtr=0;

    zCVertex::ResetVertexTransforms();
	masterFrameCtr++;
	// alle polys abgehen
	for (polyCtr=0; polyCtr<polyList.GetNum(); polyCtr++) {
		zCPolygon *actPoly = polyList [polyCtr]; 
		
		// backface culling (in world(obj)Space) 
//		if (((actPoly->vertex [0]->position - camPos)*actPoly->polyPlane.normal) > 0) continue;
		if ((zCCamera::activeCamPos*actPoly->polyPlane.normal) <= actPoly->polyPlane.distance) continue;

		// 3D-Clipping am Frustum, in Weltkoordinaten
		if (!actPoly->ClipToFrustum(zCCamera::CLIP_FLAGS_FULL)) continue;

		// alle verts abgehen
		int	vertCtr = actPoly->numClipVert-1;
		do {
			zCVertex *actVert = (actPoly->clipVert[vertCtr]); 
			if (actVert->transformed!=masterFrameCtr) {
				// Transform 
				actVert->vertCamSpace= (zCCamera :: activeCam->camMatrix) * (actVert->position);
				actVert->transformed = masterFrameCtr;
				// Project
				zCCamera:: activeCam->ProjectClamp (actVert);
				zCWorld :: s_vertsTransformed++;
			};
		} while (vertCtr--);
		
		actPoly->LightDynCamSpace	(zCCamera::activeCamPos, 50000); 
		if (!drawWireOnly)
			zrenderer->DrawPoly		(actPoly);
		actPoly->DrawWire			(wireCol);
	}

};

static void Dbg_LOD_Render (zCArray<zCPolygon*> &polyList, int wireCol=GFX_GREEN, zBOOL drawWireOnly=FALSE) 
{
	zCArraySort<zCPolygon*> list(polyList.GetNum());
	for (int i=0; i<polyList.GetNum(); i++)
		list.Insert (polyList[i]);
	Dbg_LOD_Render (list, wireCol, drawWireOnly);
};

static void Dbg_LOD_Clear () {
	dbg_LOD_camPosSet	= FALSE;
};

static zBOOL Dbg_LOD_DoFrame ()
{
	zCCamera *cam = zCCamera::activeCam;	if (!cam) return FALSE;
	Dbg_LOD_RenderNodeSubtree();
	zlineCache.Flush		(cam->targetDtpItem);
	zrenderer->FlushPolys	();
	zrenderer->Vid_Blit		();
	zCOLOR col (50,50,50,255);
	zrenderer->Vid_Clear	(col);
	zCPolygon::PrepareRendering	();
	sysEvent();
	if (zinput->KeyPressed (KEY_ESC)) { 
		if (zinput->KeyPressed (KEY_LSHIFT))		zerr.Fatal ("D: bye");
		dbg_LOD_show = FALSE; 
		return FALSE;
	};
	if (zinput->KeyPressed (KEY_I)) { 
		dbg_LOD_node->DescribeTree();
	};
	if (zinput->KeyPressed (KEY_R)) { 
		dbg_LOD_node->polyList.DeleteList();

		zCArraySort<zCPolygon*> innerPolyList;
		innerPolyList.SetCompare (ComparePolyPtr);

//		if (dbg_LOD_node->front) dbg_LOD_node->front->LODCollectLeafPolys(dbg_LOD_node, innerPolyList, );
//		if (dbg_LOD_node->back)  dbg_LOD_node->back ->LODCollectLeafPolys(dbg_LOD_node, innerPolyList, );
	};

	static CMov_Movement *mov=0;
	if (!mov)	mov = zNEW(CMov_Movement(cam->GetVob()));
	mov->vob = cam->GetVob();
	mov->Movement();
	cam->Activate();

	return !zinput->KeyPressed(KEY_SPACE);
};
#endif

// ===========================================

static zCArray<zCPolygon*>	triangulatedPortals;

static int triPortNumIn=0;
static int triPortNumOut=0;


zBOOL zCCBspNode::DoesNodeContainPoly (zCPolygon* poly) {
	// Poly ist dann in Node, wenn ...
	// Nur Verts durchlassen, die bis in den Parent reichen.
	// Diese Verts werden dann gegen die akt. Node-Plane klassifiziert.
	int numcand = 0;
	zCCBspNode *node;

	for (int i=0; i<poly->polyNumVert; i++) {
		const zPOINT3& vert = poly->GetVertexPtr(i)->position;
		node   = this;

		while (node) {
			if (node->parent==0) goto yep;
			if ((node->parent->back )==node) {
				if (node->parent->plane.ClassifyPoint (vert)==zPLANE_INFRONT)	goto nextVert;
			} else 
			if ((node->parent->front)==node) 
				if (node->parent->plane.ClassifyPoint (vert)==zPLANE_BEHIND)	goto nextVert;
			node = node->parent;
		};
		// ok, Vert liegt im Parent-Subspace
yep:
		numcand++;
nextVert:;
	};
	// Vert-Test: Poly komplett im Parent-Subspace 
	return (numcand==poly->polyNumVert);
};

// ==================================================================================================================

// **************************************************************************************************
//  Leafy BSP Portals
// **************************************************************************************************

int zCCBspNode::CheckPortalConsistency() 
{
	int sum = 0;
	int numPortals, numPolys;
	numPortals = numPolys = 0;
	if (polyList.GetNumInList()>0) {
		if (!IsLeaf()) zERR_WARNING("D: BSP:PORTAL: Polys in Nodes !");

		zTPolyNode *polyNode  = polyList.Get (0);
		while (polyNode!=0) {
			zCPortal *poly = (zCPortal*)polyNode->poly;
			if (poly)
			if (poly->IsPortal()) {
				numPortals++;
				sum++;
				zERR_ASSERT_STRICT (poly->polyNumVert>zMAX_POLY_VERTS);
				zCCBspNode *frontNode, *backNode;
				frontNode = poly->GetFrontCBspNode(); 
				backNode  = poly->GetBackCBspNode ();
				if ((frontNode!=this) && (backNode!=this))	
					zERR_WARNING("D: BSP:PORTAL: Portal in Node is not connected to Node !");
				if ((frontNode==0) && (backNode==0))
					zERR_WARNING("D: BSP:PORTAL: Portal not connected at all !");
				if ((frontNode==this) && (backNode==this))
					zERR_WARNING("D: BSP:PORTAL: Portal connected to the same Node 2 times !");

				if (frontNode) {
					if (!frontNode->IsLeaf())
						zERR_WARNING("D: BSP:PORTAL: Portal connected to inner Node !");
					zBOOL		found = FALSE;
					zTPolyNode *pNode  = frontNode->polyList.Get (0);
					while (pNode!=0) {
						if (pNode->poly==poly) { found = TRUE; break; };
						pNode = pNode->next;
					};
					if (!found) zERR_WARNING("D: BSP:PORTAL: Portal not found in connected Front-Node !");
				};
				if (backNode) {
					if (!backNode->IsLeaf())
						zERR_WARNING("D: BSP:PORTAL: Portal connected to inner Node !");
					zBOOL		found = FALSE;
					zTPolyNode *pNode = backNode->polyList.Get (0);
					while (pNode!=0) {
						if (pNode->poly==poly) { found = TRUE; break; };
						pNode = pNode->next;
					};
					if (!found) zERR_WARNING("D: BSP:PORTAL: Portal not found in connected Back-Node !");
				};
				
			};
			polyNode= polyNode->next;
		};
	};

	if (IsLeaf()) {
		if (numPortals==0) zERR_WARNING("D: BSP:PORTAL: Leaf without Portals !");
//		if (numPolys  ==0) zERR_WARNING("D: BSP:PORTAL: Leaf without Polys !");
	};

	// recurse
	if (front) sum += front->CheckPortalConsistency();
	if (back ) sum += back ->CheckPortalConsistency();
	return sum;
};

void zCCBspNode::SplitPortals () {
	// Alle Portale der Node werden durch die Plane der aktuellen BSP-Node gesplittet.
	// Die Portal-Fragmente werden front bzw. back gepushed.
	// Das Ursprungs-Portal wird gelöscht und aus dessen BSP-Nodes entfernt.

	// WICHTIG: Hier ist nur die Ausrichtung der BSP-Node-Plane wichtig.
/*
	               |
	       ____!___|______!__
	      / !      |   !    |
         /         |        |
		/          |        |
		|        <=|        |
		|          | _______|
		\          |/
		 \         / 
		  \       /|  
		   \_____/ |
		   front   |  back
*/
	zTPolyNode *polyNode  = polyList.Get (0);
	zTPolyNode *nextNode;
	while (polyNode!=0) {
		nextNode = polyNode->next;
		zCPortal *poly = (zCPortal*)polyNode->poly;
		if (poly)
		if (poly->IsPortal()) {
			switch (poly->ClassifyPlane (plane)) {
			case zPLANE_INFRONT:
				if (front) {
					PushPolyFront (polyNode);
					// connected Leafs anpassen
					if (poly->GetFrontCBspNode()==this) poly->SetFrontCBspNode (front);
					else								poly->SetBackCBspNode  (front);
				} else {
					poly->RemoveFromBsp();
//				zerr.Report (zERR_WARN, 1000, "D: zBSP(zCPortal::SplitPortals): NOPE FRONT ");
				};
				break;
			case zPLANE_BEHIND:
				if (back) {
					PushPolyBack (polyNode);
					// connected Leafs anpassen
					if (poly->GetFrontCBspNode()==this) poly->SetFrontCBspNode (back);
					else								poly->SetBackCBspNode  (back);
				} else {
					poly->RemoveFromBsp();
//				zerr.Report (zERR_WARN, 1000, "D: zBSP(zCPortal::SplitPortals): NOPE BACK");
				};
				break;
			case zPLANE_ONPLANE: 
				// ???? erlaubt ??????
//				zerr.Report (zERR_WARN, 1000, "D: zBSP(zCPortal::SplitPortals): Portal onplane !!");
				RemovePoly (poly); 
				poly->RemoveFromBsp();
				if (front) front->AddPoly (poly); 
				if (back ) back ->AddPoly (poly);
				poly->SetFrontCBspNode (front);
				poly->SetBackCBspNode  (back);
/*				if (front) {
					PushPolyFront (polyNode);
					// connected Leafs anpassen
					if (poly->GetFrontCBspNode()==this) poly->SetFrontCBspNode (back);
					else								poly->SetBackCBspNode  (back);
				};*/
				break;
			case zPLANE_SPANNING:
				// Portal Splitten !! 
				zCPortal *frontPortal= zNEW(zCPortal);
				zCPortal *backPortal = zNEW(zCPortal);
//				poly->SplitPoly (plane, frontPortal, backPortal, actCBspTree->mesh);
				poly->SplitPoly (plane, frontPortal, backPortal, 0);

				if (frontPortal->polyNumVert>=3)
				{
					if (!front) delete frontPortal; else
					{
						// neues Portal in mesh-container eintragen !
	//					actCBspTree->mesh->AddPoly (frontPortal);
						// eintragen welche Leafs das Portal verbindet
						if (poly->GetFrontCBspNode()==this) {
							// front zeigt nach innen
							frontPortal->SetFrontCBspNode (front);
							frontPortal->SetBackCBspNode  (poly->GetBackCBspNode());
						} else {
							// back zeigt nach innen
							frontPortal->SetBackCBspNode  (front);
							frontPortal->SetFrontCBspNode (poly->GetFrontCBspNode());
						};
						// Neues Portal in seine beiden Nodes eintragen
						zCCBspNode *node;
						node = frontPortal->GetFrontCBspNode(); if(node) node->AddPoly (frontPortal);
						node = frontPortal->GetBackCBspNode (); if(node) node->AddPoly (frontPortal);
					};
				}
				else {
					zERR_WARNING("D: zBSP(zCPortal::SplitPortals): Front-Portal degenerate !!");
					delete frontPortal;
				};

				if (backPortal->polyNumVert>=3)
				{
					if (!back) delete backPortal; else
					{
						// neues Portal in mesh-container eintragen !
	//					actCBspTree->mesh->AddPoly (backPortal);
						// eintragen welche Leafs das Portal verbindet
						if (poly->GetFrontCBspNode()==this) {
							// front zeigt nach innen, front ändert sich
							backPortal->SetFrontCBspNode (back);
							backPortal->SetBackCBspNode  (poly->GetBackCBspNode());
						} else {
							// back zeigt nach innen, back ändert sich
							backPortal->SetBackCBspNode  (back);
							backPortal->SetFrontCBspNode (poly->GetFrontCBspNode());
						};
						// Neues Portal in seine beiden Nodes eintragen
						zCCBspNode *node;
						node = backPortal->GetFrontCBspNode(); if(node) node->AddPoly (backPortal);
						node = backPortal->GetBackCBspNode (); if(node) node->AddPoly (backPortal);
					};
				}
				else {
					zERR_WARNING("D: zBSP(zCPortal::SplitPortals): Back-Portal degenerate !!");
					delete backPortal;
				};

				// altes Portal aus seinen beiden Nodes austragen
				poly->RemoveFromBsp();
				// das Quell-Poly muss noch aus dem Container gelöscht werden !!!
				// aber nur das Poly, nicht dessen Vertices !!
//				poly->SubRefCtr();
//				poly->SubRefCtr();
//				if (poly->GetRefCtr()<=0) 
				delete poly;
//					actCBspTree->mesh->DeletePoly (poly);		// FIXME: löscht poly, aber nicht PORTAL !!
	
			};
		};
		polyNode = nextNode;
	};
};

zCPortal* zCCBspNode::SplitPortalByAllPortals (zCPortal* portal) 
{
	// Splittet 'portal' durch die Planes aller Portale dieser BSP-Node
	// WICHTIG: Hier muessen die alten Portale richtig ausgerichtet sein, 
	//			die Ausrichtung des neuen '*portal' ist unwichtig.

	zTPolyNode *polyNode  = polyList.Get (0);
	while (polyNode!=0) {
		zCPortal *poly = (zCPortal*)polyNode->poly;
		if (poly)
		if (poly->IsPortal()) {
			zTPlane splitPlane;
			poly->GetPlane (splitPlane);

			switch (portal->ClassifyPlane (splitPlane)) {
			case zPLANE_INFRONT:
				break;
			case zPLANE_BEHIND:
				break;
			case zPLANE_ONPLANE:
				break;
			case zPLANE_SPANNING:
				// Portal Splitten !!
				zCPortal *frontPortal= zNEW(zCPortal);
				zCPortal *backPortal = zNEW(zCPortal);
				zCPortal *newPortal;
//				poly->SplitPoly (plane, frontPortal, backPortal, actCBspTree->mesh);
				portal->SplitPoly (splitPlane, frontPortal, backPortal, 0);
				
				// Auswahl
				if (poly->GetFrontCBspNode()==this) {
					// front behalten
					newPortal = frontPortal;
					delete backPortal;					// FIXME: manche vertices muessten mitgelöscht werden, manche nicht !!!
				} else {
					// back  behalten
					newPortal = backPortal;
					delete frontPortal;					// FIXME: manche vertices muessten mitgelöscht werden, manche nicht !!!
				};

				if (newPortal->polyNumVert>=3) 
				{
					// neues Portal in mesh-container eintragen !
//					actCBspTree->mesh->AddPoly (newPortal);
					// eintragen welche Leafs das Portal verbindet
//					newPortal->SetFrontCBspNode (portal->GetFrontCBspNode());
//					newPortal->SetBackCBspNode  (portal->GetBackCBspNode ());
//					actCBspTree->mesh->DeletePoly (portal);		// FIXME: löscht poly, aber nicht PORTAL !!
					delete portal;		// FIXME: manche vertices muessten mitgelöscht werden, manche nicht !!!
					portal = newPortal;
				} 
				else {
					zERR_WARNING("D: zBSP(zCPortal::SplitPortal): Degenerate New Portal !");
				};
				break;
			};
		};
		polyNode = polyNode->next;
	};
	return portal;
};

/*

// ORIENTIERUNG: FRONT/BACK

- Der 'normale' Fall ist:
	- alle Portale zeigen nach innen, in die Node hinein
	- ein neues Portal hat die Front-Side in Richtung des Front-Sohnes

- a) am Anfang jeder Node alle Portals neu ausrichten (Speed ?)
- b) bei jeder Entscheidung neu (=>wie Carmack)

*/

void zCCBspNode::EnumeratePortals() {
/*
1)	- Erzeuge ein neues Portal-Poly (_sehr groß_) und splitte es durch alle bereits vorhandenen Portal-Poly Planes im
	  aktuellen BSP-Node.
	- Die beiden Söhne werden erzeugt und in dem Portal-Poly eingetragen (front/back-connection).
	- Der _Ptr_ auf das Portal-Poly wird front & back gepushed. => das neue Portal-Poly ist fertig ! Nun zu den alten...
	- Splitte nun alle bereits vorhandenen Portal-Polys durch die Split-Plane des neuen Portal-Polys.
		- Muss ein altes Portal-Poly gesplittet werden dann:
			- erzeuge zwei neue Portal-Polys, die aus dem Split resultieren
			- deren back-side-ptr auf eine bsp-node ist bei beiden gleich, nämlich die des urspr. Portal-Polys
			- deren front-side-ptr sind unterschiedlich: linker bsp-sohn im linken Portal-Poly und umgekehrt.
		- Alle Portal-Polys des BSP-Nodes werden den Tree hinunter gepushed
*/
	// Abbruch-Bedingungen
	if (IsLeaf()) {
//	CalcBBox3D();		// BBox3D des wirklichen Sub-Spaces
		statNumLeafs++;
//		if ((numLeafs&511)==0) zerr.Message ("D: BSP: ... still working ("+zSTRING(numLeafs)+" leafs)");
		return;
	};

	// Erzeuge neues Portal-Poly
	zCPortal* portal = zNEW(zCPortal(plane, actCBspTree->mesh));
//	actCBspTree->mesh->AddPoly (portal);

	// splitte Portal-Poly durch die Planes aller anderen Portale der BSP-Node
	portal = SplitPortalByAllPortals (portal);

	// alle alten Portals durch Plane des neuen Portals/der Bsp-Node splitten
	// die Portals dann weiter den Baum hinunter pushen
	SplitPortals();

	// trage Leafs ein, die dieses Portal verbindet
	portal->SetFrontCBspNode (front);
	portal->SetBackCBspNode  (back);
	
	// pushe das neue Portal-Poly front & back
	if (front) front->AddPoly (portal);
	if (back ) back ->AddPoly (portal);

	// recurse
	if (front) front->EnumeratePortals();
	if (back ) back ->EnumeratePortals();
};

void zCCBspNode::ClassifyPortals() 
{
	if (IsLeaf()) {
		zTPolyNode *polyNode  = polyList.Get (0);
		zTPolyNode *nextNode;
		while (polyNode!=0) {
			nextNode = polyNode->next;
			zCPortal *poly = (zCPortal*)polyNode->poly;
			if (poly->IsPortal()) {
				if ((poly->GetFrontCBspNode()==0) || (poly->GetBackCBspNode()==0)) {
					poly->RemoveFromBsp();
					delete poly;			// FIXME: verts..
				};
			};
			polyNode = nextNode;
		};
		return;
	};
	// recurse
	if (front) front->ClassifyPortals();
	if (back ) back ->ClassifyPortals();
};

void zCCBspNode::Portalize() 
{
	zerr.Message ("D: BSP: Portalizing BSP-Leafs...");
	statNumLeafs   = 0;
	numPortals = 0;

	// find portals
	EnumeratePortals();
	zerr.Message ("D: BSP: * Num Portals: "+zSTRING(CheckPortalConsistency()));
	// classify Portals => delete solid portals
	ClassifyPortals();
	zerr.Message ("D: BSP: * Num Portals: "+zSTRING(CheckPortalConsistency()));
	// shared vertices  => delete double vertices
	// ...

	zerr.Message ("D: BSP: * Num Nodes: "+zSTRING(CountNodes())+", Leafs: "+zSTRING(CountLeafs()));
	zerr.Message ("D: BSP: ... Finished Portalizing.");
};

/*
- Portale, die nur in einem Leaf vorhanden sind ?
*/

//
// *** ENDE PORTALS ****
// *** ENDE PORTALS ****
// *** ENDE PORTALS ***********************************************************************************
// 

void zCCBspNode::SelectPlane (zTPlane& outplane, zTPolyNode* &splitPolyNode, zBOOL& convexSet) 
{ 
	int			front, back, planar, split;
	float		score			= 0.0F;
	zVALUE		bestScore		= zVALUE_MAX;
	zTPlane		bestPlane;
	zTPolyNode	*bestPolyNode;
	convexSet		= TRUE;
	splitPolyNode	= 0;

	// Erstmal ein temporaere Liste mit allen Polys erzeugen, die
	// noch _nicht_ markiert sind..
	// wurde Poly-Plane schon mal als Split-Plane gewählt => auf zum nächsten Poly
	// Polylist-Kandidaten heraussuchen
	int			numCandy	= 0;
	zTPolyNode	**candyList = zNEW(zTPolyNode*) [polyList.GetNumInList()];
	zTPolyNode	*pnode		= polyList.Get (0);
	while (pnode) {
		if (!pnode->marked) 
		{
			candyList[numCandy]= pnode;
			numCandy++;
		};
		pnode = pnode->next;
	};

	// Alle Polys durchgehen
	int step;
	if (numCandy!=0) {
		step = int(float(numCandy) / (float(numCandy) * actCBspTree->cfg_optimize));
		if (step<1) step=1;
	} else
		step = 1;

	for (int i=0; i<numCandy; i += step) {
		front = back = planar = split = 0;

		splitPolyNode = candyList[i];
		splitPolyNode->poly->GetPlane (outplane); 
		for (int j=0; j<numCandy; j++)
		{
			if (i==j) continue;
			zCPolygon *poly	= candyList[j]->poly;
			switch (poly->ClassifyPlane (outplane)) { 
			case zPLANE_INFRONT:
				front++;
				break;
			case zPLANE_BEHIND:
				back++;
				break;
			case zPLANE_SPANNING:
				split++;
				break;
			case zPLANE_ONPLANE:
				planar++;
				break;
			};
			// evtl. ist mittendrin schon ein Abbruch möglich, wenn die aktuelle Score unter der bisher 
			// Besten liegt und auch nicht mehr über diese steigen kann ....
		};
		
		if (split!=0) convexSet = FALSE;

		// Beim ersten gefundenen Kandidaten stoppen 
//		if (actCBspTree->cfg_optimize<1.0F) {
//			return;
//		};

		// FIXME:  __falsche__ Berechnung oder ?????? (Aepfel mit Nuessen vergleichen ...)
		// kleinere Werte => besser
		float numInv		= 1.0F / float(numCandy); 
		float balanceScore	= zAbs(float(front - back)) * numInv;
		float splitScore	= float(split)				* numInv;
		float planarScore	= float(planar)				* numInv;
        score = actCBspTree->cfg_wbalance * balanceScore + 
				actCBspTree->cfg_wsplit   * splitScore   +
				actCBspTree->cfg_wplanar  * planarScore;
//score = split;
	
		// Nur frühzeitiger Abbruch erlaubt, wenn nicht alle Polys benutzt
		// werden müssen, da hier das "convexSet"-Flag bedeutend ist.
		// Zur Bestimmung dieses Flags muessen alle Kombinationen getestet werden !!
//		if (!actCBspTree->cfg_useAllPolys) 
		if (score == 0.0) goto leave;		// FIXME !!

        if (score < bestScore) {
			bestScore	= score; 
			bestPlane	= outplane;
			bestPolyNode= splitPolyNode; 
		};
	};

	if (bestScore==zVALUE_MAX) splitPolyNode=0;
	else {
		splitPolyNode = bestPolyNode;	
		outplane	  = bestPlane;
	};

	// cleanup
leave:;
	delete[] candyList;
};

void zCCBspNode::SelectPlaneOctree (zCCBspTree *cbspTree, zTPlane& plane, int recDepth)
{
//	CalcBBox3D();
//	const zTBBox3D& box = bbox3D;
	if (parent) 
	{
		bbox3DCell = parent->bbox3DCell;
		if (parent->plane.normal[VX]>0)	{
			if (this!=parent->front)	bbox3DCell.maxs[VX] = (bbox3DCell.maxs[VX]+bbox3DCell.mins[VX]) * 0.5F;
			else						bbox3DCell.mins[VX] = (bbox3DCell.maxs[VX]+bbox3DCell.mins[VX]) * 0.5F;
		} else 
		if (parent->plane.normal[VY]>0)	{
			if (this!=parent->front)	bbox3DCell.maxs[VY] = (bbox3DCell.maxs[VY]+bbox3DCell.mins[VY]) * 0.5F;
			else						bbox3DCell.mins[VY] = (bbox3DCell.maxs[VY]+bbox3DCell.mins[VY]) * 0.5F;
		} else 
		if (parent->plane.normal[VZ]>0)	{
			if (this!=parent->front)	bbox3DCell.maxs[VZ] = (bbox3DCell.maxs[VZ]+bbox3DCell.mins[VZ]) * 0.5F;
			else						bbox3DCell.mins[VZ] = (bbox3DCell.maxs[VZ]+bbox3DCell.mins[VZ]) * 0.5F;
		}; 
	};
	const zTBBox3D& box = bbox3DCell;

	zREAL xdim = box.maxs[VX] - box.mins[VX];
	zREAL ydim = box.maxs[VY] - box.mins[VY];
	zREAL zdim = box.maxs[VZ] - box.mins[VZ];
	int nr;

	if (cbspTree->cfg_bspType==zBSP_TYPE_OCTREE)
	{
		if (xdim>zdim)		nr = 0;
		else				nr = 2;
	} else 
	if (cbspTree->cfg_bspType==zBSP_TYPE_OCTREE_SOLID)
	{
		if (xdim>ydim) {
			if (xdim>zdim)	nr = 0;
			else			nr = 2;
		} else {
			if (ydim>zdim)	nr = 1;
			else			nr = 2;
		};
	};
//	nr = recDepth % 3;

	zPOINT3 p;
	switch (nr) {
	case 0:
		// X-Plane
		plane.normal.n[VX] = 1;
		plane.normal.n[VY] = 0;
		plane.normal.n[VZ] = 0;
		p = zPOINT3 ((box.mins[VX] + box.maxs[VX]) * 0.5F, box.mins[VY], box.mins[VZ]);
		break;
	case 1:
		// Y-Plane
		plane.normal.n[VX] = 0;
		plane.normal.n[VY] = 1;
		plane.normal.n[VZ] = 0;
		p = zPOINT3 (box.mins[VX], (box.mins[VY] + box.maxs[VY]) * 0.5F, box.mins[VZ]);
		break;
	case 2:
		// Z-Plane
		plane.normal.n[VX] = 0;
		plane.normal.n[VY] = 0;
		plane.normal.n[VZ] = 1;
		p = zPOINT3 (box.mins[VX], box.mins[VY], (box.mins[VZ] + box.maxs[VZ]) * 0.5F);
		break;
	};
	plane.distance = plane.normal * p;
};
/*
		// oder: zTPlane::ClassifyPoint
		zVALUE dist1 = node->plane.normal * start - node->plane.distance;
		zVALUE dist2 = node->plane.normal * end   - node->plane.distance;

		// both in front of plane 
		if ((dist1>=0) && (dist2>=0)) {
			node = (zCBspNode*)node->front;
			if (node==0) { return TRUE; }		// inters = end
		} else

		// both behind plane
		if ((dist1<0) && (dist2<0)) {
			node = (zCBspNode*)node->back;  
			if (node==0) { return TRUE; }		// inters = end
		} else {
			// Ray is cut by split-Plane
			zPOINT3 offs, mid, split1, split2;

			// FIXME: schneller ist es hier per Hand...
			node->plane.Intersection(start, end-start, mid);
			offs	= DIST_EPSILON * node->plane.normal;
			split1	= mid + offs;
			split2	= mid - offs;
*/

int zCCBspNode::ClassifyRayToNode (const zVEC3& startRay, const zVEC3& endRay) 
{
	// Der Ray wird nacheinander gegen alle Planes geclippt, die den Node-Subspace definieren
	// Out:	-1		=   Ray liegt ausserhalb der Node (genauer: ausserhalb der beiden Soehne der Node)
	//		sonst:		zPLANE_INFRONT, zPLANE_BEHIND, zPLANE_SPANNING 

	zCCBspNode	*node   = this;
	zVEC3		start	= startRay;
	zVEC3		end		= endRay;

	while (node) {
		zCCBspNode *workNode= node->parent;
		if (workNode==0) break;

		// Ray klassifizieren 
		zVALUE dist1 = workNode->plane.normal * start - workNode->plane.distance;
		zVALUE dist2 = workNode->plane.normal * end   - workNode->plane.distance;

		if ((dist1>=0) && (dist2>=0)) {
			// both in front of plane 
			if ((workNode->back )==node) {
				// Back behalten, Front wegwerfen
				return -1;
			} else 
			if ((workNode->front)==node) {
				// Front behalten, Back wegwerfen
				// ok, weiter..
			};
		} else
		if ((dist1<0) && (dist2<0)) {
			// both behind plane
			if ((workNode->back )==node) {
				// Back behalten, Front wegwerfen
				// ok, weiter..
			} else 
			if ((workNode->front)==node) {
				// Front behalten, Back wegwerfen
				return -1;
			};
		} else {
			// Ray is cut by split-Plane
			zVEC3 inters;
			workNode->plane.Intersection(start, end-start, inters);
			if ((workNode->back )==node) {
				// Back behalten, Front wegwerfen
				if (dist1>=0)	start	= inters;		// start in front
				else			end		= inters;		// end   in front
			} else 
			if ((workNode->front)==node) {
				// Front behalten, Back wegwerfen	
				if (dist1>=0)	end		= inters;		// start in front
				else			start	= inters;		// end   in front
			};
		};
		node = node->parent;
	};

	// Ok, Ray ist nun in den Parent-Subspace geclippt. 
	// Wie liegt der Ray relativ zur aktuellen Node-Splitplane ?
	// Ray klassifizieren 
	zVALUE dist1 = this->plane.normal * start - this->plane.distance;
	zVALUE dist2 = this->plane.normal * end   - this->plane.distance;
	if ((dist1>=0) && (dist2>=0)) {
		// both in front of plane 
		return zPLANE_INFRONT;
	} else
	if ((dist1<0) && (dist2<0)) {
		// both behind plane
		return zPLANE_BEHIND;
	};

	// split
	return zPLANE_SPANNING;
};

int zCCBspNode::ClassifyPolyToNode2 (zCPolygon* poly) {
	
	// Alle Kanten des Polys durchlaufen
	zBOOL frontHit		= FALSE;
	zBOOL backHit		= FALSE;
	zVEC3 normalOffset	= poly->polyPlane.normal * zREAL(0.5F);
	for (int i=0; i<poly->polyNumVert; i++) 
	{
		int j=i+1; if (j>=poly->polyNumVert) j = 0;
		zPOINT3 p1 = poly->GetVertexPtr(i)->position + normalOffset;		// FIXME: HACK !
		zPOINT3 p2 = poly->GetVertexPtr(j)->position + normalOffset;
		int mode = ClassifyRayToNode (p1, p2);
		switch (mode) {
		case zPLANE_INFRONT:
			frontHit= TRUE;  
			break;
		case zPLANE_BEHIND:
			backHit	= TRUE;
			break;
		case zPLANE_SPANNING:
			frontHit= TRUE;
			backHit	= TRUE;
			break;
		case -1:
			break;
		};
		if (frontHit && backHit) return zPLANE_SPANNING;
	};

	// An diesem Punkt:
	// Poly-Kanten schneiden entweder einen oder keinen der beiden Volumes
	// Achtung: Folgende Tests liefern nur Ergebnisse mit _begrenzter_ Genauigkeit.. hoffentlich reicht es..
	const zREAL	STEP	= (1.0F / 16.0F);	  
	zPOINT3 center = poly->GetCenter() + poly->polyPlane.normal;		// FIXME: HACK !
	int mode;
	for (i=0; i<poly->polyNumVert; i++) {
		int j=i+1; if (j>=poly->polyNumVert) j = 0;
		zVEC3 delta = (poly->GetVertexPtr(j)->position - poly->GetVertexPtr(i)->position);
		for (zREAL t=zREAL(0.0F); t<zREAL(1.0F); t += STEP) {
			zPOINT3 p2 = poly->GetVertexPtr(i)->position + t*delta; // + poly->polyPlane.normal;
			mode = ClassifyRayToNode (p2, center);
			if (mode==zPLANE_SPANNING)	return zPLANE_SPANNING; else
			if (mode==zPLANE_INFRONT)	frontHit= TRUE;			else
			if (mode==zPLANE_BEHIND)	backHit	= TRUE;
			if (frontHit && backHit)	return zPLANE_SPANNING;
		};
	};

	if (frontHit && backHit)	return zPLANE_SPANNING;
	if (frontHit)				return zPLANE_INFRONT;
	if (backHit)				return zPLANE_BEHIND;

	// FIXME: Darf eigentlich nicht auftreten, oder ??
	// ....
	return zPLANE_INFRONT;

//	return -1;
};
/*
int zCCBspNode::ClassifyPolyToNode (zCPolygon* poly) {
	// Poly ist dann in Node, wenn ...
	// Nur Verts durchlassen, die bis in den Parent reichen.
	// Diese Verts werden dann gegen die akt. Node-Plane klassifiziert.

	int numback, numfront, numonplane, numcand;
	numback = numfront = numonplane = numcand = 0;
	zCCBspNode *node;

	for (int i=0; i<poly->polyNumVert; i++) {
		const zPOINT3& vert = poly->vertex[i]->position;
		node   = this;

		while (node!=0) {
			if (node->parent==0) goto yep;
			if ((node->parent->back )==node) {
				if (node->parent->plane.ClassifyPoint (vert)==zPLANE_INFRONT)  goto nextVert;
			} else 
			if ((node->parent->front)==node) 
				if (node->parent->plane.ClassifyPoint (vert)==zPLANE_BEHIND) goto nextVert;
			node = node->parent;
		};
		// ok, Vert liegt im Parent-Subspace, jetzt kann geprüft werden, ob der Vert in der 
		// aktuellen Node Front oder Back ist...
yep:
		numcand++;
		switch (plane.ClassifyPoint (vert)) {
		case zPLANE_INFRONT:
			numfront++;
			break;
		case zPLANE_BEHIND:
			numback++;
			break;
		case zPLANE_ONPLANE:
			numfront++;
			numonplane++;
			break;
		};
		// Vert liegt nicht in Node, nächste Node ...
nextVert:;
	};

	// Vert-Test: Poly komplett im Parent-Subspace 
	if (numcand==poly->polyNumVert) {
		if ((numfront!=0) && (numback!=0))	return zPLANE_SPANNING;
		if (numonplane==numcand)			return zPLANE_INFRONT;
		if (numfront  !=0)					return zPLANE_INFRONT;
		return zPLANE_BEHIND;
	};

	// Vert-Test: Poly teilweise im Parent-Subspace (mind. 1 Vertex)
	if (numcand>0) {
		if ((numfront!=0) && (numback!=0))	return zPLANE_SPANNING;		// darf hier so entschieden werden, weiters noch nicht..
		if (numfront  !=0) {
			// Poly auf jeden Fall im Front-Teil, auch im Back-Teil ?
			zerr.Report (zERR_WARN, 1000, "warn1");
		} else {
			// Poly auf jeden Fall im Back-Teil , auch im Front-Teil ?
			zerr.Report (zERR_WARN, 1000, "warn2");
		};
	};

	// Vert-Test: Kein Vert liegt im Parent-Subspace
	zerr.Report (zERR_WARN, 1000, "warn3");

//	if ((numfront==0) && (numback==0)) return -1;
	if ((numfront!=0) && (numback!=0))	return zPLANE_SPANNING;
	if (numonplane==numcand)			return zPLANE_INFRONT;
	if (numfront  !=0)					return zPLANE_INFRONT;
//	if (numback   !=0) 
	return zPLANE_BEHIND;
};
*/
 
static int ClassifyOctreePlaneBSPBuild (const zTPlane& plane, zCPolygon *poly) 
{
	const zDOUBLE ON_EPSILON = zDOUBLE(0.005F);
	int front	= 0;
	int back	= 0;
	int onplane = 0;
	
	if (plane.normal[VX]!=0) {
		for(int n=0; n<poly->polyNumVert; n++) {
			zREAL dist = poly->GetVertexPtr(n)->position[VX] - plane.distance;
			if(dist > ON_EPSILON)	front++; else  
			if(dist <-ON_EPSILON)	back++ ; else 
									{ front++; back++; onplane++; };
		};
	} else
	if (plane.normal[VZ]!=0) {
		for(int n=0; n<poly->polyNumVert; n++) {
			zREAL dist = poly->GetVertexPtr(n)->position[VZ] - plane.distance;
			if(dist > ON_EPSILON)	front++; else  
			if(dist <-ON_EPSILON)	back++ ; else 
									{ front++; back++; onplane++; };
		};
	} else {
		for(int n=0; n<poly->polyNumVert; n++) {
			zREAL dist = poly->GetVertexPtr(n)->position[VY] - plane.distance;
			if(dist > ON_EPSILON)	front++; else  
			if(dist <-ON_EPSILON)	back++ ; else 
									{ front++; back++; onplane++; };
		};
	};
	if (onplane== poly->polyNumVert)	return zPLANE_ONPLANE ; else	// FIRST !!!!
	if (front  == poly->polyNumVert)	return zPLANE_INFRONT ; else 
	if (back   == poly->polyNumVert)	return zPLANE_BEHIND  ; else
										return zPLANE_SPANNING;
}

int zCCBspNode::OutdoorKillRedundantLeafs () 
{
	int sum=0;
	if (IsLeaf()) return sum;

	if (front && back)
	if (front->IsLeaf())
	if (back->IsLeaf())
	{
		if (front->polyList.GetNumInList()==back->polyList.GetNumInList()) 
		if (front->bbox3D==back->bbox3D)
		{
			bbox3D = front->bbox3D;
			// Alle Polys durchgehen
			zTPolyNode *polyNode = front->polyList.Get (0);
			zTPolyNode *nextNode;
			while (polyNode) {
				nextNode = polyNode->next;
				AddPoly				(polyNode->poly);
				front->RemovePoly	(polyNode->poly);
				back ->RemovePoly	(polyNode->poly);
				polyNode = nextNode;
			};
			delete front;
			delete back;
			front = back = 0;
			sum=1;
		};
	};
	if (front)	sum += front->OutdoorKillRedundantLeafs();
	if (back)	sum += back ->OutdoorKillRedundantLeafs();
	return sum;
};

#if 0
int zCCBspNode::IndoorKillRedundantLeafs () 
{
	// Forciert folgende Bedingung:
	// Es darf keine Node geben, die zwei Childs hat, von denen mindestens eine KEINE Polys hat.
	// Das heisst NICHT, dass es keine Childs ohne Polys geben darf (dann halt hoeher im Tree!).
	int sum=0;
	if (IsLeaf()) return sum;

	if (front && back)
	if (front->IsLeaf())
	if (back->IsLeaf())
	{
		int numPolyFront	= front->polyList.GetNumInList();
		int numPolyBack		= front->polyList.GetNumInList();
		if ((numPolyFront==0) || (numPolyBack==0))
		{
			// Alle Polys durchgehen, aus front und back einsammeln und in THIS verstauen
			zTPolyNode *polyNode;
			zTPolyNode *nextNode;

			//  FrontPolys => this
			polyNode				= front->polyList.Get (0);
			while (polyNode) 
			{
				nextNode			= polyNode->next;
				AddPoly				(polyNode->poly);
				front->RemovePoly	(polyNode->poly);
				back ->RemovePoly	(polyNode->poly);
				polyNode = nextNode;
			};

			//  BackPolys => this
			polyNode				= back->polyList.Get (0);
			while (polyNode) 
			{
				nextNode			= polyNode->next;
				AddPoly				(polyNode->poly);
				front->RemovePoly	(polyNode->poly);
				back ->RemovePoly	(polyNode->poly);
				polyNode = nextNode;
			};

			// die beiden Leaf-Childs 
			delete front;
			delete back;
			front = back = 0;
			sum=1;
		};
	};
	if (front)	sum += front->IndoorKillRedundantLeafs();
	if (back)	sum += back ->IndoorKillRedundantLeafs();
	return sum;
};
#endif

void zCCBspNode::BuildTree (int recDepth) 
{
	// Modes:
	// 1) Octree1-uniform
	// 2) Octree2-adaptiv
	// 3) BSP-leafy-jedes Poly benutzen
	// 4) BSP-leafy-stoppen wenn PolyMenge konvex
	
	// Split plane wählen
	// Heuristiken:
	// - least Split
	// - space balanced
	// - poly-num balanced
	
	// Erstmal die BBox3D berechnen, alles weitere beeinflusst diese nicht.

	//
	int cfront,cback,csplit;
	cfront = cback = csplit = 0;
	
	// Test, ob Leaf schon erreicht ist 
	zTPlane		splitPlane; 
	zTPolyNode	*splitPolyNode;
	zBOOL		convexSet;

	if (actCBspTree->cfg_bspType==zBSP_TYPE_OCTREE) 
	{
		// OCTREE
		if (polyList.GetNumInList()<=0) return;			// noetig ??
		if (recDepth==0) 
		{
			CalcBBox3D();
			bbox3DCell = bbox3D;
			for (zTPolyNode *node = polyList.Get(0); node; node =node->next) {
				node->marked			= TRUE;
//				node->isCompleteInside	= TRUE;
			};
			SelectPlaneOctree (actCBspTree, splitPlane, recDepth);
		} else 
		{
			// keine Sector-Polys: 
			// noetig, damit bbox3DCell berechnet wird!
			SelectPlaneOctree (actCBspTree, splitPlane, recDepth);

			// Grundflaeche der Cell berechnen (20m Minimum)
			zREAL area = bbox3DCell.GetFloorArea();
			if (area<zBSP_OUTDOOR_MIN_CELL_AREA) return;

			// polys zaehlen, die isCompleteInside sind (Sektor-Polys)
			int		num				= 0;
			int		numInside		= 0;
			zBOOL	sectorOccured	= FALSE;
			for (zTPolyNode *node = polyList.Get(0); node; node =node->next) {
				if (node->poly->GetSectorFlag()) { sectorOccured = TRUE; continue; };

				num++;
				// FIXNE: hat 'isCompleteInside' wirklich einen korrekten Wert ????
				if (node->isCompleteInside) numInside++;
			};

			// sind zu wenige Polys completeInside ?
			// weniger als 5% aller ??
			if (numInside<=0) return;
			float ratio = float(numInside) / float(num);
			if (ratio<0.20F) return;
//			if (ratio<0.50F) return;
		};

	} else 
	if (actCBspTree->cfg_bspType==zBSP_TYPE_OCTREE_SOLID) 
	{
		// OCTREE SOLID
		// - node/leaf bboxen sind immer die CellBoxen 
		//   (WICHTIG, da diese sonst beim Rendern gecullt werden koennten, obwohl sie Vobs enthalten koennten, 
		//	  die gerendert werden muessen!)
		//	 => CalcSubtreeBBox3DCell()
		// - eine Node hat entweder KEINE childs (== leaf), oder BEIDE childs
		//   (wichtig: falls eine Node nur EIN Child hat, koennte Raum im Level bestehen, der nicht durch eine Node
		//    oder ein Leaf abgedeckt ist. TraceRay() und AddVobToTree() wuessten dann nicht weiter..)

		if (polyList.GetNumInList()<=0) return;			// noetig ??
		if (recDepth==0) 
		{
			CalcBBox3D();
			bbox3DCell = bbox3D;
			for (zTPolyNode *node = polyList.Get(0); node; node =node->next) {
				node->marked			= TRUE;
			};
			SelectPlaneOctree (actCBspTree, splitPlane, recDepth);
		} else 
		{
			// keine Sector-Polys: 
			// noetig, damit bbox3DCell berechnet wird!
			SelectPlaneOctree	(actCBspTree, splitPlane, recDepth);
			this->bbox3D		= this->bbox3DCell;

			// Terminierungskriterien: Volumen der Cell, min Zahl Polys
			if (polyList.GetNumInList()<=4)									return;
			if (bbox3DCell.GetVolume()<zBSP_OCTREE_SOLID_MIN_CELL_VOLUME)	return;

			// childs erzeugen
			// (WICHTIG, um zu gewaehrleisten, dass keine Node mit nur 1 Child existiert!)
			zERR_ASSERT (!front);
			zERR_ASSERT (!back);
			front		= zNEW(zCCBspNode(this));
			back		= zNEW(zCCBspNode(this));
		};
	} else 
	if (actCBspTree->cfg_bspType==zBSP_TYPE_LEAFY_BSP) 
	{
		// BSP
//		CalcBBox3D();
		SelectPlane (splitPlane, splitPolyNode, convexSet);
		// Abbruch-Bedingungen
		if (splitPolyNode==0) {
		#ifdef zBSP_SAFE 
			for (int i=0; i<polyList.GetNumInList(); i++) if (!polyList.Get (i)->marked) zerr.Message ("D: warn");
		#endif
			return;
		};
//		if (!actCBspTree->cfg_useAllPolys) if (convexSet) return;
		// ok, weiter. Node ist noch kein Leaf
		splitPolyNode->marked = TRUE;
		PushPolyFront (splitPolyNode);
		cfront++;
	};

	// Splitplane in node eintragen
	plane = splitPlane;

	// Alle Polys durchgehen
	zTPolyNode *polyNode = polyList.Get (0);
	zTPolyNode *nextNode;
	while (polyNode) 
	{
		nextNode		= polyNode->next;
		zCPolygon *poly = polyNode->poly;
	
		int classification;
		if (actCBspTree->cfg_bspType!=zBSP_TYPE_LEAFY_BSP)	classification = ClassifyOctreePlaneBSPBuild (splitPlane, poly);
		else												classification = poly->ClassifyPlaneBSPBuild (splitPlane);

		switch (classification) {  
		case zPLANE_INFRONT:
			goto polyIsInfront;
polyIsInfront:;
			PushPolyFront (polyNode); 
			cfront++;
			break;
		case zPLANE_BEHIND:
			goto polyIsBehind;
polyIsBehind:;
			PushPolyBack (polyNode);
			cback++;
			break;
		case zPLANE_ONPLANE:
			// FIXME: evtl. das "onPlane" anders testen, mit einem gewissem grosszuegigem Tolerance-Epsilon
			/*
			- pushback
			- pushfront, mark
			*/
			if (splitPlane.Opposite (poly->polyPlane)) {
				// Poly liegt SplitPoly gegenüber
				polyNode->marked = TRUE;
				PushPolyBack (polyNode);
				cback++;
			} else {
				// Poly zeigt in dieselbe Richtung wie SplitPoly
				// marken, damit plane nicht wieder gewählt wird !
				polyNode->marked = TRUE;
				PushPolyFront (polyNode);
				cfront++;
			};
			break;

		case zPLANE_SPANNING:
			switch (actCBspTree->cfg_spanningMode) {
			case zCCBspTree::zSPANNING_CENTER:
				// Zuordnung je nach Center des Polys
				polyNode->isCompleteInside=FALSE;
				if (splitPlane.ClassifyPoint (poly->GetCenter())==zPLANE_INFRONT) 
					PushPolyFront (polyNode); else
					PushPolyBack  (polyNode);
				break;
			case zCCBspTree::zSPANNING_PUSHBOTH:
				// Poly Back & Front pushen
				// ACHTUNG: Ein Poly, das von allen Split-Planes einer Node geschnitten wird kann dennoch ausserhalb
				//			des Node-Subspaces liegen !! Deshalb darf ein Poly nur dann in eine Child-Node gepushed 
				//			werden, wenn mindestens ein Poly-Vertex innerhalb des Child-Subspaces liegt !
				// FIXME: was wenn kein Vertex, dafuer aber Kanten des Polys sich im Leaf befinden ????
				{
//					int mode = ClassifyPolyToNode  (polyNode->poly);
					int mode = ClassifyPolyToNode2 (polyNode->poly);
					switch (mode) {
					case zPLANE_INFRONT:
						goto polyIsInfront;
						break;
					case zPLANE_BEHIND:
						goto polyIsBehind;
						break;
					case zPLANE_SPANNING:
						PushPolyBoth (polyNode);
						polyNode->isCompleteInside=FALSE;
						break;
					case -1: 
						// Poly liegt in keinem der beiden Childs..			
	// FIXME:   darf das ?????
	//						RemovePoly (polyNode->poly);
						break;
					default:
						zERR_WARNING("D: BSP, ß873087");
						break;
					};
				}
				break;

			case zCCBspTree::zSPANNING_SPLIT:
				// Splitten 
				polyNode->isCompleteInside=FALSE;

				// Entscheiden, wo das Container-Mesh liegt
				zCMesh *containerMesh;

				containerMesh = actCBspTree->mesh;
				// doit
				zCPolygon *frontPoly = zNEW(zCPolygon);
				zCPolygon *backPoly	 = zNEW(zCPolygon);
				poly     ->SplitPoly (splitPlane, frontPoly, backPoly, containerMesh);  

				if (frontPoly->polyNumVert>=3) {
					zTPolyNode *frontNode = zNEW(zTPolyNode (frontPoly, polyNode->marked)); 
					PushPolyFront (frontNode);
					// neues Poly in mesh-container eintragen !
					containerMesh->AddPoly (frontPoly);
				} else {
//					zerr.Report (zERR_WARN, 1000, "D: zBSP(zCCBspNode::BuildTree): Degenerate FrontPoly after Split !");
					delete frontPoly;										// FIXME: (shared) verts !!!!!!
				};
				if (backPoly->polyNumVert>=3) {
					zTPolyNode *backNode  = zNEW(zTPolyNode (backPoly , polyNode->marked));
					PushPolyBack  (backNode);
					// neues Poly in mesh-container eintragen !
					containerMesh->AddPoly (backPoly);
				} else {
//					zerr.Report (zERR_WARN, 1000, "D: zBSP(zCCBspNode::BuildTree): Degenerate BackPoly after Split !");
					delete backPoly;											// FIXME: (shared) verts !!!!!!
				};
				if (actCBspTree->cfg_spanningMode==zCCBspTree::zSPANNING_PUSHBOTH) {
					polyList.Delete (polyNode);
				} else {
					polyList.Delete (polyNode);
					// das Quell-Poly muss noch aus dem Container gelöscht werden !!!
					// aber nur das Poly, nicht dessen Vertices !!
					containerMesh->DeletePoly (poly);		// FIXME: denke an den material->Release !!!!!!!!
				};
				csplit++;
				splits++;
				break;
			};
			break;

		};
		polyNode = nextNode;
	};

	numNodes++;
	if ((numNodes&255)==0) zerr.Message ("D: BSP: ... still working on building bsp-tree ("+zSTRING(numNodes)+" nodes)");

	// Rekursion
	if (front) front->BuildTree (recDepth+1);
	if (back ) back ->BuildTree (recDepth+1);
};

void zCCBspNode::CalcBBox3D() 
{
	bbox3D.Init();

	// Sind die Portale bereits in der Poly-Liste ?
	// (zur Zeit: ja, d.h. die BBox3D umfasst das GESAMTE Volumen, des leafs, nicht
	//  nur die zu malenden Polys).
	zTPolyNode *node;
	for (node = polyList.Get (0); node!=0; node=node->next) 
	{
		// Ghostoccluder werden bei der BBox Bildung ausgenommen, damit sie diese moeglichst nicht unnoetig vergroessern
		// Dafuer koennen beim Rendern leider nicht die laufenden clipFlags genutzt werden..
		if (!node->poly->GetGhostOccluder())
		{
			for (int vertCtr=0; vertCtr<node->poly->polyNumVert; vertCtr++) {
				zCVertex *vert = node->poly->GetVertexPtr(vertCtr);
				bbox3D.AddPoint (vert->position);
			};
		};
	};
};

void zCCBspNode::CalcSubtreeBBox3D () 
{
	if (front) front->CalcSubtreeBBox3D();
	if (back ) back ->CalcSubtreeBBox3D();
	if (IsLeaf()) 
	{
		// leaf ? => BBox3d von den vertices berechnen
		CalcBBox3D();
	} else 
	{
		// node ? => BBox3d von den childs berechnen
		zTBBox3D box1,box2;
		CalcBBox3D();
		if (front) box1 = front->GetBBox3D(); else box1.Init(); 
		if (back ) box2 = back ->GetBBox3D(); else box2.Init();
		bbox3D.CalcGreaterBBox3D (box1);
		bbox3D.CalcGreaterBBox3D (box2);
	};
};

void zCCBspNode::CalcSubtreeBBox3DCell () 
{
	// Geht davon aus, dass die erste bzw. parent Node bereits die korrekte CellBox hat, die childs werden davon 
	// abgeleitet berechnet.
	// Geht weiterhin davon aus, dass die splitPlanes AXIS-ALIGNED, und die Normalen immer >=0 sind!
	if (this->parent) 
	{
		this->bbox3DCell = parent->bbox3DCell;
		if (parent->plane.normal[VX]>0)	{
			if (this!=parent->front)	this->bbox3DCell.maxs[VX] = (bbox3DCell.maxs[VX]+bbox3DCell.mins[VX]) * 0.5F;
			else						this->bbox3DCell.mins[VX] = (bbox3DCell.maxs[VX]+bbox3DCell.mins[VX]) * 0.5F;
		} else 
		if (parent->plane.normal[VY]>0)	{
			if (this!=parent->front)	this->bbox3DCell.maxs[VY] = (bbox3DCell.maxs[VY]+bbox3DCell.mins[VY]) * 0.5F;
			else						this->bbox3DCell.mins[VY] = (bbox3DCell.maxs[VY]+bbox3DCell.mins[VY]) * 0.5F;
		} else 
		if (parent->plane.normal[VZ]>0)	{
			if (this!=parent->front)	this->bbox3DCell.maxs[VZ] = (bbox3DCell.maxs[VZ]+bbox3DCell.mins[VZ]) * 0.5F;
			else						this->bbox3DCell.mins[VZ] = (bbox3DCell.maxs[VZ]+bbox3DCell.mins[VZ]) * 0.5F;
		}; 
		this->bbox3D	= this->bbox3DCell;
	};
	if (front)	front->CalcSubtreeBBox3DCell();
	if (back)	back ->CalcSubtreeBBox3DCell();
};

int zCCBspNode::CountNodes () {
	int a=0;
	if (front) a = front->CountNodes();
	if (back ) a+= back ->CountNodes();
	return a+1;
};

int zCCBspNode::CountLeafs () {
	int a=0;
	if (front) a = front->CountLeafs();
	if (back ) a+= back ->CountLeafs();
	if ((front==0) && (back==0)) a++;
	return a;
};

int zCCBspNode::CountPolys () {
	int a=0;
	if (front) a = front->CountPolys();
	if (back ) a+= back ->CountPolys();
	return a+polyList.GetNumInList();
};

void zCCBspNode::CountDepthRec (int depth, int& maxDepth, int& minDepth, int& sumDepth) {
	if (front) front->CountDepthRec(depth+1, maxDepth, minDepth, sumDepth);
	if (back ) back ->CountDepthRec(depth+1, maxDepth, minDepth, sumDepth);
	if (IsLeaf()) {
		if (depth>maxDepth) maxDepth = depth;
		if (depth<minDepth) minDepth = depth;
		sumDepth+= depth;
	};
};

void zCCBspNode::CountDepth (int& maxDepth, int& minDepth, int& avgDepth) {
	int sum;
	maxDepth = -1;
	minDepth = 999999;
	sum		 = 0;
	CountDepthRec (0, maxDepth, minDepth, sum);
	avgDepth = sum / CountLeafs();
};

void zCCBspNode::DescribeTree (int indent) 
{
	zSTRING s = "D: CBSP: ";
	s += Spaces (indent*2);
	if (IsLeaf()) s = s + "- Leaf, ";
	else		  s = s + "- Node, ";
	s = s + zSTRING(polyList.GetNumInList())+" Polys";
	if (front) s=s+ ", [front]";
	if (back ) s=s+ " [back]";
	s	+=  " ("+
			zSTRING(this->plane.normal[VX],1) + ", "+
			zSTRING(this->plane.normal[VY],1) + ", "+
			zSTRING(this->plane.normal[VZ],1) + ", "+
			zSTRING(this->plane.distance,1)
			+")";
	zerr.Message (s);

	if (front) front->DescribeTree (indent+1);
	if (back ) back ->DescribeTree (indent+1);
};

#pragma warning( default: 4244 ) 
