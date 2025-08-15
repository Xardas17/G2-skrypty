/******************************************************************************** 
 
     $Workfile:: zQuadMark.cpp        $                $Date:: 27.01.01 19:42   $
     $Revision:: 20                   $             $Modtime:: 27.01.01 14:29   $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zQuadMark.cpp $
 * 
 * 20    27.01.01 19:42 Moos
 * 
 * 19    20.12.00 3:01 Hildebrandt
 * 
 * 18    12.10.00 16:04 Hildebrandt
 * 
 * 17    12.10.00 15:51 Moos
 * 
 * 16    12.10.00 9:30 Moos
 * 
 * 15    7.10.00 0:41 Hildebrandt
 * 
 * 14    4.10.00 17:20 Hildebrandt
 * 
 * 13    23.09.00 17:44 Hildebrandt
 * 
 * 12    23.09.00 17:08 Hildebrandt
 * 
 * 11    22.09.00 15:58 Hoeller
 * 
 * 10    7.09.00 20:41 Hildebrandt
 * 
 * 9     2.09.00 6:53 Hildebrandt
 * 
 * 8     31.08.00 17:04 Hildebrandt
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 16    9.08.00 17:12 Admin
 * 
 * 6     21.07.00 14:28 Hildebrandt
 * 
 * 5     8.05.00 2:17 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 5     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 4     16.11.99 19:49 Hildebrandt
 * 
 * 3     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 20 $ ($Modtime: 27.01.01 14:29 $)

#include <zCore.h>
#include <zPolystrip.h>
#include <zVob.h>
#include <zWorld.h>

zCLASS_DEFINITION (zCQuadMark,	zCVisual, zCLASS_FLAG_TRANSIENT,0) 

/*

  FIXME:

  - der Backface Test in GetNextWorldPoly() ist leider nicht wie sein soll, richtig waere es:
    Poly1Normal dot (Punkt auf Poly2/nicht auf shared edge) >= Poly1Distance

  IDEE:
  - statt einer überschrittenen Edge das Poly auf die neue Plane zu projezieren, koennte man es auch
    um die Edge auf die neue Ebene rotieren !? (damit 90° Ecken auch gut aussehen)

  x mit PFX koppeln 
	- 1 PFX <=> 1 QuadMark Visual
	- bei jeder PFX-Collision wird dort ein Quadmark erzeugt (PFX teilt dies über Callback mit)
  x texCoord-Ani: scale, scale-gravity (braucht texCoord Clamp)
  * welches Material/Texture (pro Objekt? pro Poly?)
  * Fußspuren ?
  - wegfaden (alpha), verschwinden
  - Triangle
  - SaveGame ?

  - moegliche Optimierung:
	x BBox verkleinern, mit denen die Polys aus dem BSP gezogen werden
	x nicht jedes einzelne Poly mit ZBIAS versehen, sondern erst alle Polys exakt clippen, und spaeter
	  alle geclippten Polys mit der avgNormal aller WorldPolys verschieben 
	  (=> (-) zbuffer-artefakte leichter moeglich, (+) shared verts/keine brueche)
	- wenn alle Fragmente des Quads auf Polys mit denselben Normalen liegen, 
	  muss das Poly nicht gesplittet werden ! (avgNorm=worldPolyNorm & ?)
	- Vertices sharen !

  - Einsatz:
	- Blut:
		- verwundet, Blut tropft herunter						1T,
		- von Pfeil getroffen: an Wand dahinter					1T
		- bei Schwert Treffer auf Boden							nT
		- beim Sterben/am Boden liegen: sich ausdehende Lache
	- fireball: ScorchMarks

  > Ein Quadmark hat 1 Default-Material, wird per default benutzt. Allerdings kann per Parameter auch eine
    "override-texture" angegeben werden, die einmal benutzt wird.
*/

//const zREAL ZQUADMARK_ZBIAS = 2.0F;
const zREAL ZQUADMARK_ZBIAS = 3.0F; 

zCQuadMark::zCQuadMark() {
	connectedVob				= 0;
	alphaFadeSpeed				= 0;
	dontRepositionConnectedVob	= FALSE;
	quadMesh					= zNEW(zCMesh	 ());
	material					= zNEW(zCMaterial());
	actMaterial					= (zCMaterial *)material->AddRef(); // [Moos] Crashfix zu den beiden Leakfixes unten

	worldPolyList				= 0;
	numWorldPoly				= 0;
	firstWorldPoly				= 0;
	averageNormal				= 0;
};

zCQuadMark::~zCQuadMark() {
	zRELEASE (quadMesh);
	zRELEASE (material);		// FIXME: ?
    zRELEASE (actMaterial); // [Moos] Leakfix
	connectedVob				= 0;

	worldPolyList				= 0;
	numWorldPoly				= 0;
	firstWorldPoly				= 0;
	averageNormal				= 0;
};

void zCQuadMark::SetVisualUsedBy (zCVob* vob) { 
	connectedVob = vob; 
	vob->SetIgnoredByTraceRay	(TRUE);
	vob->SetCollDet				(FALSE);
};

zTBBox3D zCQuadMark::GetBBox3D () 
{
	return quadMesh->GetBBox3D();
};

/*
void zCQuadMark::DynLightVisual (const zCArray<zCVobLight*>& vobLightList, zMATRIX4 *trafoObjToWorld) 
{
	quadMesh->DynLightVisual (vobLightList, trafoObjToWorld);
};
*/

zBOOL zCQuadMark::Render (zTRenderContext& renderContext)
{
	// hier koennte man auch ZBuffer-Writes ausschalten
	// evtl. noch zbuffer: writeDisable, compare lessEqual

	zBOOL doRender	= TRUE;
	zBOOL visible	= FALSE;
	if (quadMesh->numPoly>0) 
	if (quadMesh->Poly(0)->GetMaterial()->GetTexture()) 
	{
		// Das Rendern wird solange unterdrueckt, bis die Textur tatsaechlich komplett eingeladen ist
		doRender = (quadMesh->Poly(0)->GetMaterial()->GetTexture()->CacheIn()==zRES_CACHED_IN);
	};

	if (doRender)
	{
		// Wenn die Polys mit AlphaTextur/AlphaTesting gerendert werden gibt es keine Probleme, und das
		// zrenderer->FlushPolys() ist nicht noetig. Was aber bei Karten, die kein Alphatesting beherrschen?
		// (FIXME: nicht als transp speichern !												)
		// (       aber: beim Ausschalten des AlphaPolyCachings gibt es zbuffer-Flimmern..	)
		const zBOOL needsClamp	= (quadMarkAniTracker.GetNum()>0);
		if (needsClamp)			  zrenderer->SetTextureWrapEnabled	(FALSE);
		//	const zBOOL cacheAlphas	= zrenderer->GetCacheAlphaPolys		();
		//	zrenderer->SetCacheAlphaPolys (FALSE);

		visible	= quadMesh->Render(renderContext);

		//	zrenderer->FlushPolys			();
		//	zrenderer->SetCacheAlphaPolys	(cacheAlphas);

		if (needsClamp)			zrenderer->SetTextureWrapEnabled (TRUE);
	};
 
	ProcessAniTracker		();
	return visible;
};

zBOOL zCQuadMark::ClipQuadPolyToPlane (zTQuadMarkPoly& inPoly, zTQuadMarkPoly& outPoly, const zTPlane& pplane) 
{
    int		i, nextvert;
	zBOOL	curin, nextin;
    zREAL	curdot, nextdot, scale;
	zBOOL	clipped = FALSE;

	curdot	= inPoly.vertex[0].position * pplane.normal; 
	curin	= (curdot >= pplane.distance);

	outPoly.vertex.EmptyList();

    for (i=0 ; i<inPoly.vertex.GetNum(); i++)  
    {
		nextvert = i+1; if (nextvert>=inPoly.vertex.GetNum()) nextvert=0;
		nextdot	= inPoly.vertex[nextvert].position * pplane.normal; 
		nextin	= (nextdot >= pplane.distance);
        
		// Keep the current vertex if it's inside the plane
		if (curin) {
			outPoly.vertex.Insert (inPoly.vertex[i]);
		};

		// clip
        if (curin != nextin)
		{
			scale = (pplane.distance - curdot) / (nextdot - curdot);
			zTQuadMarkVert	newVert;
			newVert.position	= inPoly.vertex[i].position + scale * (inPoly.vertex[nextvert].position - inPoly.vertex[i].position);
			newVert.texCoord	= inPoly.vertex[i].texCoord + scale * (inPoly.vertex[nextvert].texCoord - inPoly.vertex[i].texCoord);
			outPoly.vertex.Insert (newVert);
			clipped = TRUE;
        }
        curdot = nextdot;
        curin  = nextin;
    };
	return clipped;
};

void zCQuadMark::ClipQuadPolyToWorldPoly (zTQuadMarkPoly& inQuadPoly, zCPolygon* worldPoly, zCArray<int> &clipEdgeList) 
{
	int				nextvert;
	zTPlane			plane;

	zTQuadMarkPoly	quadPoly2;
	zTQuadMarkPoly	*quadPoly[2];
	quadPoly[0]		= &inQuadPoly;
	quadPoly[1]		= &quadPoly2;
	int actQuad		= 0;

	clipEdgeList.EmptyList();

	for (int i=0; i<worldPoly->polyNumVert; i++) 
	{
		nextvert = i+1; if (nextvert>=worldPoly->polyNumVert) nextvert=0;
		zVEC3	at		= worldPoly->GetVertexPtr(nextvert)->position - worldPoly->GetVertexPtr(i)->position;
		plane.normal	= at ^ worldPoly->GetNormal();
		plane.normal.NormalizeApprox();
//		plane.normal.Normalize();
		plane.distance	= plane.normal * worldPoly->GetVertexPtr(i)->position;
		
		zBOOL clipped = (ClipQuadPolyToPlane	(*quadPoly[actQuad], *quadPoly[actQuad^1], plane));

		// degen ?
		if ((*quadPoly[actQuad^1]).vertex.GetNum()<3) {
			inQuadPoly.vertex.EmptyList();
			clipEdgeList.EmptyList();
			return;
		};

		//
		if (clipped) {
			clipEdgeList.Insert (i);
	        actQuad ^= 1;
		};
	};

	if (actQuad==1) 
	if (clipEdgeList.GetNum()>0)
	{
		inQuadPoly	= quadPoly2;
	};
};

void zCQuadMark::CalcQuadAxis (zCPolygon* worldPoly, zVEC3& xvec, zVEC3& yvec)
{
	if (zAbs(worldPoly->GetNormal()[VY])<0.99F)	yvec	= zPOINT3 (0,1,0);	else
	if (zAbs(worldPoly->GetNormal()[VX])<0.99F)	yvec	= zPOINT3 (1,0,0);	else
												yvec	= zPOINT3 (0,0,1);

	yvec	= (yvec + (-(yvec * worldPoly->GetNormal()) * worldPoly->GetNormal())).NormalizeApprox();
	xvec	= (yvec ^ worldPoly->GetNormal());
};

void zCQuadMark::InitFirstQuadPoly (zCPolygon* worldPoly, const zPOINT3& hitLocation, const zVEC3& xvec, const zVEC3& yvec, zTEffectParams *aniEffects)
{
	firstQuadPoly.vertex.EmptyList();
	zTQuadMarkPoly	&quadPoly	= firstQuadPoly;
	zTQuadMarkVert	vert;
	const zPOINT3&	center		= hitLocation;

	quadPoly.vertex.AllocAbs			(4);
	quadPoly.vertex.MarkNumAllocUsed	();

	quadPoly.vertex[0].position	= center + xvec + yvec;
	quadPoly.vertex[1].position	= center - xvec + yvec;
	quadPoly.vertex[2].position	= center - xvec - yvec;
	quadPoly.vertex[3].position	= center + xvec - yvec;
	quadPoly.vertex[0].texCoord	= zVEC2(1.0,0.0);
	quadPoly.vertex[1].texCoord	= zVEC2(0.0,0.0);
	quadPoly.vertex[2].texCoord	= zVEC2(0.0,1.0);
	quadPoly.vertex[3].texCoord	= zVEC2(1.0,1.0);

	zTQuadMarkAniState *aniState=0;
	zBOOL animated = (alphaFadeSpeed>0) || ((aniEffects) && (aniEffects->texAniType!=zTEXANI_NONE));
	if (animated) {
		zTQuadMarkAniState newAniState;
		newAniState.alpha		= 255.0F;
		newAniState.texAniType	= zTEXANI_NONE;
		quadMarkAniTracker.Insert (newAniState);
		aniState = &(quadMarkAniTracker[quadMarkAniTracker.GetNum()-1]);
	};

	if (aniEffects)
	if (aniEffects->texAniType!=zTEXANI_NONE) 
	{
		if (aniEffects->texAniType==zTEXANI_SCALEUP_AUTO) {
			aniEffects->texAniType	= zTEXANI_SCALEUP;
			if (zAbs(worldPoly->GetNormal()[VY])<0.05F)	aniEffects->texAniType	= zTEXANI_SCALEUP_GRAV;
		};
		zVEC2 uvDelta;
		zVEC2 uvScale;

		if (aniEffects->texAniType==zTEXANI_SCALEUP) {
			uvDelta	= zVEC2(0.5F,0.5F);
			uvScale	= zVEC2(aniEffects->texAniScaleStart, aniEffects->texAniScaleStart);

			zREAL inv = 1.0F / aniEffects->texAniScaleStart;

//			zVEC2 inv(1.0F,1.0F);
//			if (uvScale[0]!=0)	inv[0]= 1.0F/uvScale[0];
//			if (uvScale[1]!=0)	inv[1]= 1.0F/uvScale[1];

			for (int i=0; i<4; i++) {
		//		quadPoly.vertex[i].texCoord	= quadPoly.vertex[i].texCoord * 2.0F - 0.5F;
//				quadPoly.vertex[i].texCoord[0]	= quadPoly.vertex[i].texCoord[0] * inv[0] - uvDelta[0];
//				quadPoly.vertex[i].texCoord[1]	= quadPoly.vertex[i].texCoord[1] * inv[1] - uvDelta[1];

				quadPoly.vertex[i].texCoord[0]	-= uvDelta[0];
				quadPoly.vertex[i].texCoord[0]	*= inv;
				quadPoly.vertex[i].texCoord[0]	+= uvDelta[0];
				quadPoly.vertex[i].texCoord[1]	-= uvDelta[1];
				quadPoly.vertex[i].texCoord[1]	*= inv;
				quadPoly.vertex[i].texCoord[1]	+= uvDelta[1];
			};
		} else
		if (aniEffects->texAniType==zTEXANI_SCALEUP_GRAV) {
			uvDelta	= zVEC2(0.0F,0.0F);
//			uvScale	= zVEC2(0.0F,0.8F);
			uvScale	= zVEC2(0.0F, aniEffects->texAniScaleStart);

			zREAL inv = 1.0F / aniEffects->texAniScaleStart;

			for (int i=0; i<4; i++) {
				quadPoly.vertex[i].texCoord[1]	*= inv;
			};
		};

		// aniState fuer dieses Poly bereits eingetragen, oder muss etwa noch ?
		if (!aniState)
		{
			zTQuadMarkAniState newAniState;
			newAniState.firstPolyIndex	= 0;		// SHUT UP, Compiler!
			quadMarkAniTracker.Insert	(newAniState);
			aniState = &(quadMarkAniTracker[quadMarkAniTracker.GetNum()-1]);
		};

		aniState->uvDelta		= uvDelta;
		aniState->uvScale		= uvScale;
		aniState->scaleStart	= 1.0F / uvScale[1];
		aniState->scaleCur		= aniState->scaleStart;
		aniState->scaleSpeedCur	= aniEffects->texAniSpeed;
		aniState->scaleSpeed	= aniEffects->texAniSpeed;
		aniState->texAniType	= aniEffects->texAniType;
	};
};

void zCQuadMark::InitQuadPoly (zTQuadMarkPoly &quadPoly, zCPolygon* worldPoly)
{
	if (worldPoly!=firstWorldPoly) {
		ProjectQuadPolyToPlane	(firstQuadPoly, quadPoly, worldPoly->GetPlane());
	} else {
		quadPoly = firstQuadPoly;
	};
};

void zCQuadMark::ProjectQuadPolyToPlane (const zTQuadMarkPoly &inQuadPoly, zTQuadMarkPoly &outQuadPoly, const zTPlane& plane)
{
	outQuadPoly.vertex.AllocAbs			(inQuadPoly.vertex.GetNum());
	outQuadPoly.vertex.MarkNumAllocUsed	();
	for (int i=0; i<inQuadPoly.vertex.GetNum(); i++) 
	{
		zREAL dist						= plane.normal * inQuadPoly.vertex[i].position - plane.distance;
		outQuadPoly.vertex[i].position	= inQuadPoly.vertex[i].position - plane.normal * dist;
//		outQuadPoly.vertex[i].position	= inQuadPoly.vertex[i].position - plane.normal * (dist-ZQUADMARK_ZBIAS);
		outQuadPoly.vertex[i].texCoord	= inQuadPoly.vertex[i].texCoord;
	};
};

void zCQuadMark::AddQuadPolyToQuadMesh (zTQuadMarkPoly& quadPoly, zCPolygon *worldPoly)
{
	// Verts werden auch gleich in das KS des Vobs verlegt (nur Translation!)
	zCPolygon *poly = quadMesh->AddPoly();
	poly->AllocVerts (quadPoly.vertex.GetNum());
	poly->SetMaterial(actMaterial);

	for (int i=0; i<quadPoly.vertex.GetNum(); i++) {
		zPOINT3		pos		= quadPoly.vertex[i].position - connectedVob->GetPositionWorld();
		zCVertex*	vert	= quadMesh->AddVertex		(pos);
//		zCVertex*	vert	= quadMesh->AddVertexSmart	(pos);
		
		poly->SetVertex (i, vert);
	};

	for (i=0; i<quadPoly.vertex.GetNum(); i++) {
		poly->SetMapping				(i, quadPoly.vertex[i].texCoord);
		poly->feature[i]->vertNormal	= worldPoly->polyPlane.normal;
	};

	// Poly Normale berechnen
	poly->polyPlane.normal	= worldPoly->polyPlane.normal;
	poly->polyPlane.distance= poly->polyPlane.normal*poly->GetVertexPtr(0)->position;

//poly->CalcNormal();

	// FIXME: optimize!
	quadMesh->CalcBBox3D		(TRUE);
//	quadMesh->CalcVertexNormals	(zCMesh::zMSH_VERTNORMAL_FACET); 
};

zCPolygon* zCQuadMark::GetNextWorldPoly (zCVertex* vert1, zCVertex* vert2)
{
	for (int i=0; i<numWorldPoly; i++) {
		if (worldPolyList[i]->EdgePartOfPoly (vert2, vert1)) {
			zCPolygon *poly = worldPolyList[i];
			if (numWorldPoly>1)
				worldPolyList[i] = worldPolyList[numWorldPoly-1];
			numWorldPoly--;

			// backface culling
			if ((firstWorldPoly->GetNormal()*poly->GetNormal())<=0) {
				i--;
				continue;
			};
			return poly;
		};
	};
	return 0;
};

void zCQuadMark::ProcessWorldPoly (zCPolygon *worldPoly)
{
	zCArray<int>	clipEdgeList;

	zTQuadMarkPoly	quadPoly;
	InitQuadPoly				(quadPoly, worldPoly);
	ClipQuadPolyToWorldPoly		(quadPoly, worldPoly, clipEdgeList);
	if (quadPoly.vertex.GetNum()<3) return;
	AddQuadPolyToQuadMesh		(quadPoly, worldPoly);
	averageNormal += worldPoly->GetNormal();

	// Alle clipped Edges abgehen
	for(int i=0; i<clipEdgeList.GetNum(); i++) {
		int vert			= clipEdgeList[i];
		int nextVert		= vert+1;			if (nextVert>=worldPoly->polyNumVert) nextVert=0;
		zCPolygon* nextPoly = GetNextWorldPoly	(worldPoly->GetVertexPtr(vert), worldPoly->GetVertexPtr(nextVert));
		if (!nextPoly)	continue;
		if (visitedPolyList.IsInList(nextPoly)) continue;
		visitedPolyList.Insert	(nextPoly);
		
		// recurse
		ProcessWorldPoly	(nextPoly);	
	};
};

void zCQuadMark::CreateQuadMark	(const zPOINT3& rayOrg, 
								 const zVEC3&	ray, 
								 const zVEC2&	quadMarkDim, 
								 zSTRING&		texName,
								 zTEffectParams	*aniEffects)
{
	if ((!actMaterial->GetTexture()) ||
	   (actMaterial->GetTexture()->GetName()!=texName))
	{
		// FIXME: hier evtl. erst die Materialien des QuadMeshes durchsuchen..
/*		for (int i=0; i<quadMesh->numPoly; i++)
		{
			zCPolygon* poly = quadMesh->polyList[i];
			if (poly->GetMaterial()->GetTexture())
			if (poly->GetMaterial()->GetTexture()->GetName()==texName) {
				actMaterial = poly->GetMaterial();
			}
		};*/
		//
        zRELEASE(actMaterial); // [Moos] Leakfix
		actMaterial = zNEW(zCMaterial);
		actMaterial->SetTexture (texName);
	};
	CreateQuadMark (rayOrg, ray, quadMarkDim, aniEffects);
};

void zCQuadMark::CreateQuadMark			(const zPOINT3& rayOrg, 
										 const zVEC3&	ray, 
										 const zVEC2&	quadMarkDim, 
										 zCMaterial		*newMaterial,
										 zTEffectParams	*aniEffects)
{
	if ((!actMaterial->GetTexture()) ||	(actMaterial==newMaterial))
	{
        zRELEASE (actMaterial); // [Moos] Leakfix
		actMaterial = static_cast<zCMaterial*>(newMaterial->AddRef());
	};
	CreateQuadMark (rayOrg, ray, quadMarkDim, aniEffects);
};

void zCQuadMark::CreateQuadMark	(const zPOINT3& rayOrg, 
								 const zVEC3&	ray, 
								 const zVEC2&	quadMarkDim, 
								 zTEffectParams	*aniEffects)
{
	if (!connectedVob)					return;
	if (!connectedVob->GetHomeWorld())	return;

	// Hit Poly ermitteln
	if (!connectedVob->GetHomeWorld()->TraceRayNearestHit	(rayOrg, ray, (zCVob*)0, zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE)) return;
	zCPolygon* worldPoly = connectedVob->GetHomeWorld()->traceRayReport.foundPoly;

	//
	CreateQuadMark (worldPoly, connectedVob->GetHomeWorld()->traceRayReport.foundIntersection, quadMarkDim, aniEffects);
};

void zCQuadMark::CreateQuadMark			(zCPolygon		*worldPoly,
										 const zPOINT3&	hitLocation,
										 const zVEC2&	quadMarkDim, 
										 zTEffectParams	*aniEffects)
{
	int		oldNumPoly = quadMesh->numPoly;
	int		i;
	zVEC3	xaxis, yaxis;
	if (!connectedVob)					goto leave;
	if (!connectedVob->GetHomeWorld())	goto leave;
	if (!worldPoly)						goto leave;
	if (worldPoly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER) goto leave;

	// die Textur wird hier precached (tunen..!)
	if (actMaterial->GetTexture())
		actMaterial->GetTexture()->CacheIn(0.2F);

	// Quad Axen bestimmen
	CalcQuadAxis (worldPoly, xaxis, yaxis);
	xaxis		 *= quadMarkDim[0];
	yaxis		 *= quadMarkDim[1];

	// Nachbar-Polys ermitteln
	// Box aus den exakten Ausmassen des ersten QuadPolys ermitteln
	{
		const zVEC3&	center = hitLocation;
		zTBBox3D		box;
		box.Init		();
		box.AddPoint	(center + xaxis + yaxis + worldPoly->GetNormal());
		box.AddPoint	(center - xaxis - yaxis - worldPoly->GetNormal());
		connectedVob->GetHomeWorld()->GetBspTree()->GetRoot()->CollectPolysInBBox3D (box, worldPolyList, numWorldPoly);
		for (i=0; i<numWorldPoly; i++) {
			if ((worldPolyList[i]->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER) 
	//			|| (!worldPolyList[i]->CheckBBoxPolyIntersection (testBBox3D))
				)
			{
				numWorldPoly--;
				worldPolyList[i] = worldPolyList[numWorldPoly];
				i--;
			};
		};
		if (numWorldPoly<=0) goto leave;
	};

	{
		//
		visitedPolyList.EmptyList	();
		visitedPolyList.AllocAbs	(numWorldPoly);
		visitedPolyList.Insert		(worldPoly);

		// Beim ersten QuadMark den Vob-Ursprung auf diesen QuadMark setzen
		if (!dontRepositionConnectedVob)
		if (quadMesh->numPoly<=0) 
		{
			connectedVob->SetCollDet			(FALSE);
			connectedVob->BeginMovement			();
			connectedVob->TouchMovement			();
			connectedVob->SetPositionWorld		(hitLocation);
			connectedVob->ResetRotationsWorld	();
			connectedVob->EndMovement			();
		};

		//
		averageNormal		= zVEC3(0,0,0);
		firstWorldPoly		= worldPoly;
		InitFirstQuadPoly	(worldPoly, hitLocation, xaxis, yaxis, aniEffects);
		ProcessWorldPoly	(worldPoly);

		// Die neuen Polys ein wenig anheben, um ZBuffer Artefakten aus dem Weg zu gehen
		averageNormal.NormalizeApprox();
		averageNormal *= ZQUADMARK_ZBIAS;
		for (int i=oldNumPoly; i<quadMesh->numPoly; i++) {
			zCPolygon *poly = quadMesh->Poly(i);
			for (int j=0; j<poly->polyNumVert; j++) 
				poly->GetVertexPtr(j)->position += averageNormal;
		};

		// nur den Vob updaten, wenn dieser QuadMark direktes Visual des Vobs 
		// (ansonsten muesste das direkte Visual fuer das Update sorgen..)
		if (connectedVob->GetVisual()==this)
		{
			connectedVob->BeginMovement				();
			connectedVob->TouchMovement				();		// FIXME
			connectedVob->UpdateVisualDependencies	();
			connectedVob->EndMovement				();
		};

		// TexAni: indizes nachtragen
		if (((aniEffects) && (aniEffects->texAniType!=zTEXANI_NONE)) || (alphaFadeSpeed>0))
		{
			quadMarkAniTracker[quadMarkAniTracker.GetNum()-1].firstPolyIndex	= oldNumPoly;
			quadMarkAniTracker[quadMarkAniTracker.GetNum()-1].lastPolyIndex		= quadMesh->numPoly-1;
		};
	};

leave:;
	// wurde ein neues Material gar nicht benutzt ? => loeschen
	if (oldNumPoly>=quadMesh->numPoly) {
		if (actMaterial!=material)
			zRELEASE(actMaterial);
	};

	// wieder aufs Default-Material zuruecksetzen
    if (actMaterial != material){
        zRELEASE(actMaterial); // [Moos] noch ein Leakfix
	    actMaterial = (zCMaterial *)material->AddRef();
    }
};


int zCQuadMark::GetNumActive ()
{
	if (alphaFadeSpeed<=0)	return quadMesh->numPoly;
	return quadMarkAniTracker.GetNum();
};

void zCQuadMark::ProcessAniTracker ()
{
	zREAL alphaFade = alphaFadeSpeed * ztimer.GetFrameTimeF();
	for (int i=0; i<quadMarkAniTracker.GetNum(); i++) 
	{
		//
		zTQuadMarkAniState& aniState = quadMarkAniTracker[i];

		if (aniState.texAniType!=zTEXANI_NONE) {
			// Texture Coord Animation
			zREAL t					= ( (aniState.scaleCur-0.9F) / (aniState.scaleStart-0.9F) );
			aniState.scaleSpeedCur	= aniState.scaleSpeed	 * t;
			zREAL scale				= aniState.scaleSpeedCur * ztimer.GetFrameTimeF() / 1000.0F;
			scale					= 1.0F - scale;
			aniState.scaleCur		*= scale;

			if ((aniState.scaleCur<1)) {
				if (alphaFade>0) {
					// texAni ausschalten, wenn parallel noch ein alphaFade laeuft
					aniState.texAniType = zTEXANI_NONE;
				} else {
					// kein AlphaFade parallel => entfernen
					quadMarkAniTracker.RemoveIndex (i);
					i--;
					continue;
				};
			};

			//
			const zVEC2& uvDelta	= aniState.uvDelta;
			const zVEC2& uvScale	= aniState.uvScale;

			// FIXME: optimieren !
			for (int j=aniState.firstPolyIndex; j<=aniState.lastPolyIndex; j++)
			{
				zCPolygon *poly = quadMesh->Poly(j);
				for (int k=0; k<poly->polyNumVert; k++)
				{
					zCVertFeature *feat = poly->feature[k];
					if (uvScale[0]!=0) {
						feat->texu -= uvDelta[0];
						feat->texu *= scale;
						feat->texu += uvDelta[0];
					};

					if (uvScale[1]!=0) {
						feat->texv -= uvDelta[1];
						feat->texv *= scale;
						feat->texv += uvDelta[1];
					};
				};
			};
		};

		// Alpha setzen
		{
			aniState.alpha		-= alphaFade;
			zBYTE	newAlpha	= 0;
			if (aniState.alpha>0)	newAlpha = zBYTE(aniState.alpha);
			for (int j=aniState.firstPolyIndex; j<=aniState.lastPolyIndex; j++)
			{
				zCPolygon *poly = quadMesh->Poly(j);
				for (int k=0; k<poly->polyNumVert; k++)
				{
					zCVertFeature *feat		= poly->feature[k];
					feat->lightDyn.alpha	= newAlpha;		// FIXME
					feat->lightStat.alpha	= newAlpha;
				};
			};
			if (aniState.alpha<=0) {
				// QuadMark ist ausgefadet, aus aniListe entfernen..
				// FIXME: evtl. auch als zu renderendes Poly aus Mesh entfernen !!
				quadMarkAniTracker.RemoveIndex (i);
				i--;
				continue;
			};
		};
	};

	// alphaFade im Gange & alle Polys ausgefadet ? 
	if (alphaFadeSpeed>0) 
	if (quadMarkAniTracker.GetNum()<=0)
	{
		// alle ausgefadeten Polys aus dem Mesh loeschen
		quadMesh->DeleteAll ();
	};
};



