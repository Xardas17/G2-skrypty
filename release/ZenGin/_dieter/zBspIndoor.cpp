 /******************************************************************************** 
 
     $Workfile:: zBSPIndoor.cpp       $                $Date:: 27.01.01 19:42   $
     $Revision:: 9                    $             $Modtime:: 27.01.01 14:05   $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   created: 

 * $Log: /current_work/ZenGin/_Dieter/zBSPIndoor.cpp $
 * 
 * 9     27.01.01 19:42 Moos
 * 
 * 8     25.01.01 17:01 Hildebrandt
 * 
 * 7     22.09.00 15:57 Hoeller
 * 
 * 6     21.08.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 4     9.08.00 17:12 Admin
 * 
 * 4     21.07.00 14:28 Hildebrandt
 * 
 * 3     3.07.00 12:44 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author $Author: Moos $
/// @version $Revision: 9 $ ($Modtime: 27.01.01 14:05 $)

#include <zCore.h>
#include <zBsp.h>
#include <zVisual.h>
#include <zWorld.h>

#ifdef ZENGINE_DEBUG
//	#define zBSP_DONT_CREATE_SECTORS_INDOOR
#endif

zCBuildPortal::zCBuildPortal()
{
	portalPoly=portalPolyBack=0;
	sector[0]=sector[1]=0;
};

zCBuildPortal::~zCBuildPortal()
{
	portalPoly=portalPolyBack=0;
	sector[0]=sector[1]=0;
};

void zCBspTree::PreprocessIndoorPortals	(zCMesh *mesh, zCArray<zCBuildPortal*> &portalList)
{
	#ifdef zBSP_DONT_CREATE_SECTORS_INDOOR
		return;
	#endif

	// *****************************
	//	1. Portale sammeln
	// *****************************

	zERR_ASSERT (this->portalList.GetNum()==0);
	this->portalList.EmptyList();
	this->portalList.AllocAbs (portalList.GetNum()*2);

	int oldNumPoly = mesh->numPoly;		// damit die neu dazugefuegten Polys nicht mit hineingeraten
	for (int i=0; i<oldNumPoly; i++) 
	{
		zCPolygon	*poly	= mesh->Poly(i);
		zCMaterial	*mat	= poly->GetMaterial();
		poly->SetSectorFlag		(FALSE);
		poly->SetPortalType		(zCPolygon::zPORTAL_TYPE_NONE);
		poly->SetSectorIndex	(zSECTOR_INDEX_UNDEF);

		if (mat->IsPortalMaterial())
		{
			// Flags im Poly setzen
			poly->SetPortalType		(zCPolygon::zPORTAL_TYPE_BIG);
			poly->SetSectorIndex	(portalList.GetNum() | zSECTOR_INDEX_PORTAL);
			mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND); 

			// BuildPortal erzeugen
			zCBuildPortal *portal	= zNEW(zCBuildPortal);
			portalList.Insert		(portal);
			portal->SetPortalPoly	(poly);

			// Portal double-sided machen => Copy
			zCPolygon *poly2		= zNEW(zCPolygon);
			poly2->SetMaterial		(poly->GetMaterial());
			poly2->SetPortalType	(poly->GetPortalType());
			poly2->AllocVerts		(poly->polyNumVert);
			for (int j=0; j<poly->polyNumVert; j++)
			{
				poly2->SetVertex	(j, poly->GetVertexPtr(poly->polyNumVert-j-1));
				poly2->SetFeature	(j, poly->feature[poly->polyNumVert-j-1]);
			};
			poly2->CalcNormal();
			mesh->AddPoly	(poly2);
			zERR_ASSERT (poly->GetNormal()*poly2->GetNormal()<0);
			portal->SetPortalPolyBack	(poly2);

			//
			this->portalList.Insert (poly);
			this->portalList.Insert (poly2);
		};
	};
	zerr.Message ("D: BSP: numIndoorPortals: "+zSTRING(portalList.GetNum()));
};

void zCBspTree::GetPolyNeighbours (zCPolygon *sourcePoly, zCPolygon**& foundPolyList, int& foundPolyNum) 
{
	zTBBox3D	searchBox = sourcePoly->GetBBox3D();
	searchBox.Scale (1.1F);
	CollectPolysInBBox3D (searchBox, foundPolyList, foundPolyNum);

	// Aussortieren: doppelte Polys, Sector-Polys 
	// (Portale werden entfernt!!!)
	for (int k=0; k<foundPolyNum; k++) {
		zCPolygon *poly = foundPolyList[k];
		if ((poly==sourcePoly) ||
			(poly->IsPortal()))
		{
			foundPolyList[k] = foundPolyList[--foundPolyNum];
			k--;
			continue;
		};
		for (int j=k+1; j<foundPolyNum; j++) { 
			zCPolygon *poly2 = foundPolyList[j];
			if (poly2==poly) {
				foundPolyList[j] = foundPolyList[--foundPolyNum];
				j--;
				continue;
			};
		};
	};
};

void zCBspTree::PostprocessIndoorPortals(zCArray<zCBuildPortal*> &portalList)
{
	#ifdef zBSP_DONT_CREATE_SECTORS_INDOOR
		return;
	#endif

	//
	if (portalList.GetNum()<=0) return;

	zERR_MESSAGE (3, zERR_BEGIN, "D: BSP: Autoportalizing indoor BSP..");
	zCPolygon	**foundPolyList;
	int			foundPolyNum;

	// *****************************
	//	1. Border-Polys einsammeln
	// *****************************

	for (int i=0; i<portalList.GetNum(); i++)
	{
		// grob potentielle BorderPolys aus BSP ziehen 
		zCBuildPortal	*portal		= portalList[i];
		zCPolygon		*portalPoly = portal->GetPortalPoly();
		GetPolyNeighbours (portalPoly, foundPolyList, foundPolyNum);

		for (int j=0; j<foundPolyNum; j++)
		{
			// BorderPoly: a) schneidet portalPoly, b) hat Vertex mit portalPoly gemeinsam
			zCPolygon *poly2	= foundPolyList[j];
			if (portalPoly->IsIntersecting(poly2))
			{
				poly2->SetSectorIndex			(i | zSECTOR_INDEX_PORTAL);
				portal->borderPolyList.Insert	(poly2);
//for (int k=0; k<poly2->polyNumVert; k++)
//	poly2->feature[k]->texu=poly2->feature[k]->texv=0;
				continue;
			};

			// Vertex geshared ?
			for (int k=0; k<portalPoly->polyNumVert; k++)
			{
				if (poly2->VertPartOfPoly (portalPoly->GetVertexPtr(k)))
				{
					poly2->SetSectorIndex			(i | zSECTOR_INDEX_PORTAL);
					portal->borderPolyList.Insert	(poly2);
//for (int k=0; k<poly2->polyNumVert; k++)
//	poly2->feature[k]->texu=poly2->feature[k]->texv=0;
					continue;
				};
			};
		};
	};

	// ********************************************
	//	2. Connectivity Walk
	// ********************************************

	zCArray<zCPolygon*>	activePolys;			// keine Portale, Polys bei denen noch nicht alle Edges gescannt wurden
	zCArray<int>		activePolysFrontBack;	// merkt sich fuer jedes noch aktive Poly, auf welcher Seite es gefunden wurde

	for (i=0; i<portalList.GetNum(); i++)
	{
		//
		zCBuildPortal	*portal		= portalList[i];
		zCPolygon		*portalPoly = portal->GetPortalPoly();

		// Startpolys eintragen
		activePolys = portal->borderPolyList;
		activePolysFrontBack.DeleteList			();	// kein EmptyList!
		activePolysFrontBack.AllocAbs			(activePolys.GetNum());
		activePolysFrontBack.MarkNumAllocUsed	();
		for (int j=0; j<activePolysFrontBack.GetNum(); j++)
			activePolysFrontBack[j]=-1;

		// ConWalk
		while (activePolys.GetNum()>0) 
		{
			zCPolygon	*poly				= activePolys[0];
			int			polyFrontBack		= activePolysFrontBack[0];
			activePolys.RemoveIndex			(0);
			activePolysFrontBack.RemoveIndex(0);

			GetPolyNeighbours (poly, foundPolyList, foundPolyNum);

			// Edges des aktiven Polys scannen
			for (int j=0; j<poly->polyNumVert; j++) 
			{
				int jnext		= (j+1) % poly->polyNumVert;
				zCVertex *vert1	= poly->GetVertexPtr(j);
				zCVertex *vert2	= poly->GetVertexPtr(jnext);

				// Ist die aktuelle Edge in einem anderen Poly enthalten ?
				for (int k=0; k<foundPolyNum; k++) 
				{
					zCPolygon *poly2 = foundPolyList[k];
					if (poly2==poly)				continue;
					if (poly2->GetSectorIndex()==0) continue;

					if (poly2->EdgePartOfPoly(vert2, vert1)) 
					{
						// Befinden wir uns vor oder hinter dem Portal ?
						int bucketNr= polyFrontBack;
						if (polyFrontBack<0)
						{
							if (portalPoly->GetPlane().GetDistanceToPlane(vert2->position)>=0)	bucketNr=0;	// front
							else																bucketNr=1;	// back
						};

						// BorderPoly ? 
						if ((poly2->GetSectorIndex()!=zSECTOR_INDEX_UNDEF) &&
						   ((poly2->GetSectorIndex() & zSECTOR_INDEX_PORTAL)!=0))
						{
							// Beides BorderPolys des gleichen Sektors ?
							if (poly2->GetSectorIndex()!=poly->GetSectorIndex())
							{
								// Verbindung zu anderem Portal herstellen
								int				portalIndex	= poly2->GetSectorIndex() & (zSECTOR_INDEX_PORTAL-1);
								zCBuildPortal	*portal2	= portalList[portalIndex];
								if (portal!=portal2)
								{
									int				bucketNr2;
									if (portal2->GetPortalPoly()->GetPlane().GetDistanceToPlane(vert2->position)>=0)	bucketNr2=0;	// front
									else																				bucketNr2=1;	// back
									if (!portal->portalBucket[bucketNr].IsInList (portal2))
										portal->portalBucket[bucketNr].Insert (portal2);
									if (!portal2->portalBucket[bucketNr2].IsInList (portal))
										portal2->portalBucket[bucketNr2].Insert (portal);
									zERR_ASSERT (portal2->borderPolyList.IsInList (poly2));
								};
							}; 
						} else
						{
							//
							portal->polyBucket[bucketNr].Insert (poly2);
							poly2->SetSectorIndex		(0);				// als registriert markieren

							//
							zERR_ASSERT					(!activePolys.IsInList(poly2));
							activePolys.Insert			(poly2);
							activePolysFrontBack.Insert (bucketNr);
						};

						foundPolyList[k]			= foundPolyList[--foundPolyNum];
						k--;
						break;
					};
				};
			};
		};
		zerr.Message ("D: BSP: portal#"+zSTRING(i)+
			", numVert: "+zSTRING(portal->GetPortalPoly()->polyNumVert)+
			", borderPolys: "	+zSTRING(portal->borderPolyList.GetNum())+
			", polyBucket: "	+zSTRING(portal->polyBucket[0].GetNum())+"/"+zSTRING(portal->polyBucket[1].GetNum())+
			", portalBucket: "	+zSTRING(portal->portalBucket[0].GetNum())+"/"+zSTRING(portal->portalBucket[1].GetNum())+
			", "+portal->GetPortalPoly()->GetCenter().GetString());
	};

	// ********************************************
	//	3. Create Sectors
	// ********************************************

	zERR_ASSERT_STRICT (sectorList.GetNum()==0);
	for (i=0; i<portalList.GetNum(); i++)
	{
		//
		zCBuildPortal	*portal		= portalList[i];
		for (int j=0; j<2; j++)
		{
			// Falls noch kein Sektor auf der Seite vorhanden ist, wird nun einer erzeugt
			if (portal->sector[j]==0)
			{
				zCBspSector *sector		= zNEW(zCBspSector);
				portal->sector[j]		= sector;
				sectorList.Insert		(sector);
				int sectorIndex			= sectorList.GetNum()-1;
				sector->sectorIndex		= sectorIndex;
				if (j==0)	sector->sectorPortals.Insert	(portal->GetPortalPoly());
				else		sector->sectorPortals.Insert	(portal->GetPortalPolyBack());

				// alle Polys auf der Seite mit der richtigen Sektor-Nummer markieren
				for (int k=0; k<portal->polyBucket[j].GetNum(); k++)
				{
					portal->polyBucket[j][k]->SetSectorIndex(sectorIndex);
				};
				
				// alle weiteren Portale auf der Seite durchgehen, dort die richtige Seite finden & den Sektor eintragen
				for (k=0; k<portal->portalBucket[j].GetNum(); k++)
				{
					zCBuildPortal	*portal2 = portal->portalBucket[j].GetSafe(k);
					// richtige Seite finden
					for (int l=0; l<2; l++)
					{
						if (portal2->portalBucket[l].IsInList(portal))
							break;
					};
					zERR_ASSERT_STRICT	(l<2);
//					zERR_ASSERT_STRICT	(portal2->sector[l]==0);
					// Der Sektor kann allerdings in dem Portal schein eingetragen sein, falls mehr als 2 Portale
					// in denselben Sektor fuehren
					portal2->sector[l]	= sector;
					zCPolygon *portalPoly = (l==0) ? portal2->GetPortalPoly() : portal2->GetPortalPolyBack();
					if (!sector->sectorPortals.IsInList(portalPoly))
						sector->sectorPortals.Insert (portalPoly);
				};
			};
		};

		// Nun sind die beiden Sektoren auf den beiden Seiten des Portals bekannt.
		// Die Portal-Polys bekommen nun die Info, in welchen Sektor sie hineinfuehren.
		portal->GetPortalPoly	 ()->SetSectorIndex(zWORD(portal->sector[1]->GetSectorIndex()));
		portal->GetPortalPolyBack()->SetSectorIndex(zWORD(portal->sector[0]->GetSectorIndex()));

		// Fuer jeden Sector dessen BspNodes suchen
		for (j=0; j<2; j++)
		{
			zCBspSector		*sector	= portal->sector[j];

			// Nur nach Nodes fuer den Sector suchen, falls dies noch nicht geschehen ist
			// if ((sector->sectorNodes.GetNum()==0) && (portal->polyBucket[j].GetNum()>0))
			if (sector->sectorNodes.GetNum()==0) 
			{
				// Markierung im Leaf reseten
				for (int leafNr=0; leafNr<numLeafs; leafNr++) 
				{
					zCBspLeaf *leaf		= &(leafList[leafNr]);
					leaf->sectorIndex	= 0;
				};

				//
				zCArray<zCPolygon*> testList = portal->polyBucket[j];
				// Die BorderPolys aller angrenzenden Portale gehoeren ebenfalls zu diesem
				// Sektor und werden hier explizit eingesammelt.
				for (int q=0; q<2; q++)
				{
					for (int r=0; r<portal->portalBucket[q].GetNum(); r++)
					{
						if ((portal->portalBucket[q][r]->sector[0]==sector) ||
							(portal->portalBucket[q][r]->sector[1]==sector))
						{
							testList.InsertArray	(portal->portalBucket[q][r]->borderPolyList);
						};
					};
				};
				testList.InsertArray	(portal->borderPolyList);
				testList.Insert			(portal->GetPortalPoly());
				testList.Insert			(portal->GetPortalPolyBack());

				// Die Poly-Testliste ist nun komplett. Alle Leafs des BSP werden darauf getestet, ob
				// sie ein Poly der Testliste enthalten. Falls ja, wird das Leaf dem Sektor zugeordnet.
				for (int k=0; k<testList.GetNum(); k++)
				{
					zCPolygon *poly = testList[k];
					
					for (int leafNr=0; leafNr<numLeafs; leafNr++) 
					{
						zCBspLeaf *leaf = &(leafList[leafNr]);
						if (leaf->sectorIndex==0)		// "0" => noch nicht zugeordnet
						{
							for (int i=0; i<leaf->numPolys; i++) 
							{
								zCPolygon *poly2 = leaf->polyList[i];
								if (poly==poly2)
								{
									sector->sectorNodes.Insert (leaf);
									leaf->sectorIndex	= 1;			// mark 
									break;
								};
							};
						};
					};
				};
			};
		};
	};

	// Leafs ohne Polys den Sektoren zuordnen

	// Ray-Tests
	{
		zERR_MESSAGE (5, 0, "D: BSP: INDOOR: associating emptyLeafs to sectors");
		int numAssocs=0;
		for (int leafNr=0; leafNr<numLeafs; leafNr++) 
		{
			zCBspLeaf	*leaf		= &(leafList[leafNr]);

			// Fuer dieses Leaf sollen Sektor-Zuordnungen festgestellt werden, 
			zBOOL		testLeaf	= (leaf->numPolys<=0);		// testen wenn kein Polys, oder nur Portale
			if (!testLeaf)
			{
				testLeaf			= TRUE;
				for (int i=0; i<leaf->numPolys; i++)
				{
					if (!leaf->polyList[i]->IsPortal()) 
					{
						testLeaf	= FALSE;
						break;
					};
				}
			};
			if (testLeaf)
			{
				const zPOINT3&	testPos		= leaf->bbox3D.GetCenter();
				const int		traceFlags	=	zTRACERAY_STAT_POLY		| 
												zTRACERAY_STAT_PORTALS	|
												zTRACERAY_POLY_2SIDED	| 
												zTRACERAY_VOB_IGNORE;
				zCPolygon		*hitPoly	= 0;
				zPOINT3			inters;
				zVEC3			ray			= zVEC3(0,-500000.0F,0);

				this->TraceRay (testPos, testPos + ray, traceFlags, inters, hitPoly, 0);
				if ((hitPoly) && (hitPoly->IsPortal()))
				{
					ray	= -ray;
					this->TraceRay (testPos, testPos + ray, traceFlags, inters, hitPoly, 0);
				};
				if (hitPoly)
				{
					// Poly backface getroffen?
					zERR_ASSERT (hitPoly);
					zREAL	dot			= hitPoly->GetNormal() * ray;
					if (dot<=0)
					{
						// frontface	=> zuordnen
						int sectorIndex = hitPoly->GetSectorIndex();
						if (sectorIndex!=zSECTOR_INDEX_UNDEF)
						{
							// Portal getroffen ?
							if (hitPoly->IsPortal())
							{
								// duerfte hier nicht mehr auftreten
								zERR_FAULT ("D: BSP: INDOOR: downRay hits Portal !");
								continue;
							} else
							// BorderPoly getroffen ?
							if (sectorIndex>=zSECTOR_INDEX_PORTAL)
							{
								// BorderPoly: ueber das Portal den Sektor ermitteln
								int portalIndex = (sectorIndex & (zSECTOR_INDEX_PORTAL-1)) << 1;
								if (this->portalList[portalIndex]->GetPlane().GetDistanceToPlane(testPos)<0)	sectorIndex	= this->portalList[portalIndex]->GetSectorIndex();
								else																			sectorIndex	= this->portalList[portalIndex+1]->GetSectorIndex();
							};
							zCBspSector *foundSector		= sectorList[sectorIndex];
							// zERR_ASSERT					(!foundSector->sectorNodes.IsInList (leaf));
							if (!foundSector->sectorNodes.IsInList (leaf))
								foundSector->sectorNodes.Insert (leaf);
							++numAssocs;
						};
					} else
					{
						// backface		=> leaf befindet sich NICHT im Level und wird auch nicht zugeordnet
						continue;
					};
				};
			};
		};
		zERR_MESSAGE (5, 0, "D: BSP: INDOOR: emptyLeafs, numAssocs; "+zSTRING(numAssocs));
	}

	zERR_MESSAGE (3, zERR_END,"D: BSP: numIndoorSectors: "+zSTRING(sectorList.GetNum()));
};
