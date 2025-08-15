/******************************************************************************** 
 
     $Workfile:: zPolyStrip.cpp       $                $Date:: 4.12.00 18:23    $
     $Revision:: 10                   $             $Modtime:: 1.12.00 18:15    $
       $Author:: Moos                                                           $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_dieter/zPolyStrip.cpp $
 * 
 * 10    4.12.00 18:23 Moos
 * 
 * 9     23.11.00 12:18 Moos
 * 
 * 8     25.10.00 0:03 Hildebrandt
 * 
 * 7     31.08.00 17:04 Hildebrandt
 * 
 * 6     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 5     21.07.00 14:28 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 7     17.02.00 3:07 Hildebrandt
 * zenGin 087a
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
/// @author $Author: Moos $
/// @version $Revision: 10 $ ($Modtime: 1.12.00 18:15 $)


#include <zCore.h>
#include <zPolystrip.h>
#include <zVob.h>
#include <zWorld.h>			// poly/tri stats
#include <zMemPool.h>
#include <zVertexTransform.h>

zCLASS_DEFINITION (zCPolyStrip,	zCVisual, 0,0) 

// =======================================================================================================================

/*
	firstSeg, lastSeg	: erstes/letztes centerPoint/Poly INKLUSIVE
*/

/*

- Segmente:
	- allokierte		0..(numPoly-1)
	- generierte		firstSeg..lastSeg, numSeg
	- gerenderte		(subSegment genau über visFirstFrac, visLastFrac

*/

zCPolyStrip::zCPolyStrip() {
	vertList					= 0;
	polyList					= 0;
	numPoly						= 0;
	numVert						= 0;
	centerPointList				= 0;
	alphaList					= 0;
	firstSeg					= 0;
	lastSeg						= 0;
	numSeg						= 0;
	camAlign					= zCAM_ALIGN_NONE;

	visFirstFrac				= 1;
	visLastFrac					= 0;

	lastDirSeg					= -1;
	lastDirNormal				= 0;

	alphaFadeSpeed				= 0.0F;
	newAlpha					= 255.0F;
	newAlphaFadeSpeed			= 0.0F;
	connectedVob				= 0;
	bbox3D.Init					();
	SetWidth					(10.0F);
	SetIsLocalFOR				(FALSE);

	//
	material					= zNEW(zCMaterial());
	material->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
	material->SetAlpha			(255);
	
	material->texAniCtrl.SetAniFPS(10);
	heightCheck		= FALSE;
	heightBound		= FLT_MAX;
	everyFrameUpdate= FALSE;
};

zCPolyStrip::~zCPolyStrip() {
	FreeResources				();
	connectedVob				= 0;
	zRELEASE					(material);
};

zBOOL zCPolyStrip::IsBBox3DLocal () 
{
	return GetIsLocalFOR();
};

zTBBox3D zCPolyStrip::GetBBox3D () 
{ 
	if (numSeg<=0) 
	{
		if (connectedVob) {
			bbox3D.mins = connectedVob->GetPositionWorld();
			bbox3D.maxs = bbox3D.mins + zVEC3(1,1,1);
		} else {
			bbox3D.InitZero();
			bbox3D.maxs = zVEC3(1,1,1);
		};
	};
	/*if (GetEveryFrameUpdate())
	{
		zCVob *  cameraVob = zCCamera::activeCam->GetVob();
		if (cameraVob)
		{
			zPOINT3  everyTimeVisiblePos = cameraVob->GetPositionWorld() + 200 * cameraVob->GetAtVectorWorld();
			bbox3D.Init();
			bbox3D.AddPoint (everyTimeVisiblePos + zVEC3(10,10,10));
			bbox3D.AddPoint (everyTimeVisiblePos - zVEC3(10,10,10));
		}
	}*/
	return bbox3D;
};

void zCPolyStrip::CalcBBox3D ()
{
	if (numSeg>0) 
	{
		bbox3D.Init();
		int i=firstSeg;
		for (int num=numSeg; num>1; num--) 
		{
			bbox3D.AddPoint (centerPointList[i]);
			i++; if (i>=numPoly) i=0;
		};
	} else {
		bbox3D.InitZero();
	};
	if (connectedVob) 
	{
		connectedVob->BeginMovement				();
		connectedVob->SetPositionWorld			(bbox3D.GetCenter());
		connectedVob->UpdateVisualDependencies	();
		connectedVob->EndMovement				();
	};
};

void zCPolyStrip::SetVisualUsedBy (zCVob* vob) { 
	vob->SetIgnoredByTraceRay (TRUE);
	connectedVob = vob;
};

void zCPolyStrip::EmptyEffect () {
	visFirstFrac				= 1;
	visLastFrac					= 0;
	numSeg						= 0;
	firstSeg					= 0;
	lastSeg						= 0;
	newAlpha					= 255.0F;
};

void zCPolyStrip::AllocateResources (int numMaxSeg) {
	numPoly			= numMaxSeg;
	numVert			= numPoly*2;
	polyList		= zNEW(zCPolygon) [numPoly];
	vertList		= zNEW(zCVertex	) [numVert];
	centerPointList	= zNEW(zPOINT3	) [numMaxSeg];
	alphaList		= zNEW(zREAL	) [numMaxSeg];
	
	// Polys mit Vertices/Material verbinden
	zCOLOR col(255,255,255,255);
	for (int i=0; i<numMaxSeg; i++) {
		zCPolygon* poly = &polyList[i];
		int j = i*2;
		poly->SetVertices	(&vertList[j], &vertList[j+1], &vertList[j+3], &vertList[j+2], FALSE);
		poly->SetMaterial	(material);
		poly->feature[0]->texu	= 1.0F;		poly->feature[0]->texv	= 0.0F;
		poly->feature[1]->texu	= 0.0F;		poly->feature[1]->texv	= 0.0F;
		poly->feature[2]->texu	= 0.0F;		poly->feature[2]->texv	= 1.0F;
		poly->feature[3]->texu	= 1.0F;		poly->feature[3]->texv	= 1.0F;
		for (int k=0; k<4; k++) {
			poly->feature[k]->lightStat = col; 
			poly->feature[k]->lightDyn	= col;
		};
		alphaList[i] = newAlpha;
	};

	// mache Ring!
	int j = (numMaxSeg-1)*2;
	polyList[numPoly-1].SetVertices	(&vertList[j], &vertList[j+1], &vertList[1], &vertList[0], FALSE);
};

void zCPolyStrip::FreeResources () {
	delete[] vertList;			vertList		= 0;
	delete[] polyList;			polyList		= 0;
	delete[] centerPointList;	centerPointList	= 0;
	delete[] alphaList;			alphaList		= 0;
	
	numPoly			= 0;
	numVert			= 0;
	EmptyEffect		();
};

void zCPolyStrip::SetVisibleSegments (zREAL visibleFirst, zREAL visibleLast) 
{
	const zREAL visFirstSeg	= visibleFirst	* zREAL(numPoly);
	const zREAL visLastSeg	= visibleLast	* zREAL(numPoly);
	const zREAL floorFirst	= zFloor(visFirstSeg);

	firstSeg		= zFloat2Int(floorFirst) % numPoly;
	lastSeg			= zFloat2Int(zCeil (visLastSeg) ) % numPoly;
	visFirstFrac	= visFirstSeg - floorFirst;
	visLastFrac		= 1.0F- (visLastSeg  - zFloor(visLastSeg));

	if (lastSeg>firstSeg)	numSeg = lastSeg-firstSeg+1;
	else					numSeg = lastSeg-(firstSeg-numPoly)+1;

	alphaList[lastSeg] = newAlpha;
};

zBOOL zCPolyStrip::Render (zTRenderContext& renderContext) 
{
	if (numSeg<=0) return FALSE;
	AlignToCamera();

	//
	if (!GetIsLocalFOR())
		zCCamera::activeCam->Activate();

	//
#if 0
	zrenderer->Vid_BeginLfbAccess();
	screen->Print (0,3000, zSTRING(firstSeg)+"/"+zSTRING(lastSeg)+"/"+zSTRING(numSeg));
	zrenderer->Vid_EndLfbAccess();
#endif

	//
	newAlpha -= newAlphaFadeSpeed * ztimer.GetFrameTimeF();
	if (newAlpha<0) newAlpha=0;

	// Sub-Segment genauer Render-Bereich
	int		num				= numSeg;
	int		firstPoly		= firstSeg;
	int		lastPoly		= lastSeg;
	zBOOL	subSegment		= !((visFirstFrac==1) && (visLastFrac==0));

	//
	int		j0, jnext0;
	int		j1, jnext1;
	zPOINT3	vertPosBak[4];
	if (subSegment) {
		j0						= firstPoly*2;
		jnext0					= (j0+2) % numVert;
		vertPosBak[0]			= vertList[j0+0].position; 
		vertPosBak[1]			= vertList[j0+1].position;
		vertList[j0+0].position	= vertList[j0+0].position + visFirstFrac * (vertList[jnext0+0].position - vertList[j0+0].position);
		vertList[j0+1].position	= vertList[j0+1].position + visFirstFrac * (vertList[jnext0+1].position - vertList[j0+1].position);

		j1						= lastPoly*2;
		jnext1					= (j1-2);	if (jnext1<0) jnext1 += numVert;
		vertPosBak[2]			= vertList[j1+0].position;
		vertPosBak[3]			= vertList[j1+1].position;
		vertList[j1+0].position	= vertList[j1+0].position + visLastFrac  * (vertList[jnext1+0].position - vertList[j1+0].position);
		vertList[j1+1].position	= vertList[j1+1].position + visLastFrac  * (vertList[jnext1+1].position - vertList[j1+1].position);
	};

	// Alpha-Fade
	zREAL alphaSpeed		= ztimer.GetFrameTimeF() * alphaFadeSpeed;
	alphaList[firstPoly]	-= alphaSpeed;
	zREAL matAlpha			= material->GetColor().GetAlphaFloat();

	int lastZero	= -1;
	int lastAlpha	= zFloat2Int(alphaList[firstPoly]) ;
	if (lastAlpha<0) {
		lastAlpha=0;
		lastZero= firstPoly;
	};

	int j=-1;
	for (int i=firstPoly; num>1; num--,i++) 
	{
		if (i>=numPoly) i=0;
		zCPolygon *poly = &polyList[i];

		if (heightCheck && poly->vertex[0]->position[VY]<heightBound) continue;

		poly->feature[0]->lightStat.alpha	= zFloat2Int(lastAlpha * matAlpha) ;
		poly->feature[1]->lightStat.alpha	= zFloat2Int(lastAlpha * matAlpha);

		int	alpha;
		j = i+1; if (j>=numPoly) j=0;
		alphaList[j]	-= alphaSpeed;
		alpha			= zFloat2Int(alphaList[j]);
		if (alpha<0) {
			alpha	= 0;
			lastZero= j;
		};
		poly->feature[2]->lightStat.alpha	= zFloat2Int(alpha * matAlpha);
		poly->feature[3]->lightStat.alpha	= zFloat2Int(alpha * matAlpha);
		
		lastAlpha = alpha;


		if (poly->ClipToFrustum (renderContext.clipFlags)) 
		{ 
			if (poly->TransformProjectLight()) 
			{
				// FIXME !
				for (int k=0; k<poly->numClipVert; k++) 
				{
					poly->clipFeat[k]->lightDyn=poly->clipFeat[k]->lightStat;
				};

				zrenderer->DrawPoly (poly); 
			};
		};
	};

	// ausgefadete Segmente entfernen ?
	if (lastZero>=0) 
	{
		if ((lastZero==j) || (lastZero==lastSeg)) {
			lastSeg=firstSeg=numSeg=0;
		} else {
			firstSeg	= lastZero;
			if (lastSeg >firstSeg)	numSeg = lastSeg-firstSeg+1; else
			if (lastSeg <firstSeg)	numSeg = lastSeg-(firstSeg-numPoly)+1;
			else					numSeg = 0;
		};
	};

	//
	if (subSegment) {
		vertList[j0+0].position = vertPosBak[0];
		vertList[j0+1].position = vertPosBak[1];
		vertList[j1+0].position = vertPosBak[2];
		vertList[j1+1].position = vertPosBak[3];
	};

// 	zlineCache.Line3D (centerPointList[firstSeg], centerPointList[lastSeg]);

	return TRUE;
};

void zCPolyStrip::AddSegment (const zPOINT3& posUp, const zPOINT3& posDown) 
{
	if (numSeg>=numPoly) return;
	int next = (firstSeg + numSeg) % numPoly;

	const zPOINT3& centerPoint = (posUp+posDown)*zREAL(0.5F);
	UpdateSegment (next, posUp, posDown, centerPoint);

	if (!GetEveryFrameUpdate()) bbox3D.AddPoint (centerPoint);
//	CalcBBox3D();		// FIXME
	lastSeg = next;
	numSeg++;
};

void zCPolyStrip::AddSegment (const zPOINT3& centerPoint) 
{
	if (numSeg>=numPoly) return;
	int next = (firstSeg + numSeg) % numPoly;

	centerPointList[next]	= centerPoint;
	bbox3D.AddPoint (centerPoint);

	lastSeg = next;
	numSeg++;
};

void zCPolyStrip::AddSegmentSmart (const zPOINT3& pos1, const zPOINT3& pos2)
{
	if (numSeg>=2)
	{
		const zPOINT3& center = (pos1 + pos2) * zREAL(0.5F);

		if (lastDirSeg!=lastSeg) {
			int prevSeg		= lastSeg-1; if (prevSeg<0) prevSeg = numPoly-1;
			lastDirNormal	= (centerPointList[lastSeg] - centerPointList[prevSeg]).NormalizeApprox();
			lastDirSeg		= lastSeg;
		};

		const zVEC3&	dir	= (centerPointList[lastSeg] - center).NormalizeApprox();
		zREAL			dot	= lastDirNormal*dir;

		if (zAbsApprox(dot)>0.995F) 
		{
			// kein neues Segment, das letzte updaten
			UpdateSegment (lastSeg, pos1, pos2, center);
			return;
		};
		lastDirNormal	= dir;
	};

	// neues Segment
	AddSegment (pos1, pos2);
};

void zCPolyStrip::UpdateSegment (int segNr, const zPOINT3& posUp, const zPOINT3& posDown, const zPOINT3& center) 
{
	if (segNr==-1) segNr = lastSeg;
	assert (segNr>=0);
	assert (segNr<numPoly);
	int j = segNr*2;
	vertList[j+0].position	= posUp;
	vertList[j+1].position	= posDown;
	centerPointList [segNr]	= center;
	alphaList		[segNr]	= newAlpha;
};

void zCPolyStrip::UpdateSegmentAlpha (int segNr, const zREAL inNewAlpha)
{
	if (segNr==-1) segNr= lastSeg;
	assert (segNr>=0);
	assert (segNr<numPoly);
	alphaList [segNr]	= inNewAlpha;
};

void zCPolyStrip::AlignToCamera () 
{
	if (GetCamAlign()==zCAM_ALIGN_NONE)	return;
	zCCamera *cam = zCCamera::activeCam;
	if (!cam) return;

	if (numSeg<=0) return;

	if (GetCamAlign()==zCAM_ALIGN_STRIP)
	{
		zVEC3 stripUp	= centerPointList[lastSeg] - centerPointList[firstSeg];
		zVEC3 stripRight= cam->camMatrixInv.GetAtVector() ^ stripUp;
		stripRight.NormalizeApprox();

		stripRight *= GetWidth();

		int j = firstSeg;
		int k;
		for (int i=0; i<numSeg; i++) {
			k = 2*j;
			vertList[k+0].position	= centerPointList[j] - stripRight;
			vertList[k+1].position	= centerPointList[j] + stripRight;

			j++;
			if (j>=numPoly) j=0;
		}; 
	} else {
		zVEC3	stripUp, stripRight;
		int		j		= firstSeg;
		int		jprev;
		for (int i=0; i<(numSeg-1); i++) {
			jprev = j;
			j++;
			if (j>=numPoly) j=0;

			stripUp		= centerPointList[jprev] - centerPointList[j];
			stripRight	= cam->camMatrixInv.GetAtVector() ^ stripUp;
			stripRight.NormalizeApprox();

			stripRight *= GetWidth();
			int k = 2*jprev;
			vertList[k+0].position	= centerPointList[jprev] - stripRight;
			vertList[k+1].position	= centerPointList[jprev] + stripRight;
		};
		int k = 2*j;
		vertList[k+0].position	= centerPointList[j] - stripRight;
		vertList[k+1].position	= centerPointList[j] + stripRight;
	};
};

void zCPolyStrip::ProjectToSphere (const zTBSphere3D& sphere)
{
	int j = firstSeg;
	for (int i=0; i<numSeg; i++) 
	{
		//
		zVEC3 delta = centerPointList[j] - sphere.center;
		delta.NormalizeApprox();
		centerPointList[j] = sphere.center + sphere.radius*delta;
		//
		j++;
		if (j>numPoly) j=0;
	};
};

// ************************************
//		GenerateCP:		Lightning0
// ************************************

static int LogBase2 (int n) 
{
	int i=0;
	assert (n!=0);
	while (!(n&1)) {
		n=n>>1;
		i++;
	};
	assert ((n&~1)==0);
	return i;
};

static zREAL GaussRand() {
	int r=0;
	for (int i=0; i<6; i++)
		r += zRand() - zRand();

	return zREAL(r) / (zREAL(zRAND_MAX) * 6.0F);
};

static zVEC3* currentCenterPoint=0;

void zCPolyStrip::Lightning0Subdivide (const zPOINT3& startPos, const zPOINT3& endPos, zREAL s, int n) 
{
	if (n==0) {
		currentCenterPoint++;
		*currentCenterPoint = endPos;
		return;
	};

	zVEC3 mid;
	mid[VX]	= (endPos[VX] + startPos[VX]) * 0.5F + s * GaussRand();
	mid[VY]	= (endPos[VY] + startPos[VY]) * 0.5F + s * GaussRand();
	mid[VZ]	= (endPos[VZ] + startPos[VZ]) * 0.5F + s * GaussRand();

	Lightning0Subdivide	(startPos	, mid	, s * 0.5F, n-1);
	Lightning0Subdivide	(mid		, endPos, s * 0.5F, n-1);
};

void zCPolyStrip::GenerateCPLightning0 (const zPOINT3& startPos, const zPOINT3& endPos, zREAL wildness)
{
	// Zahl der vorhandenen Polys/CenterPoints muss "2er-Potenz+1" sein

	EmptyEffect();

	firstSeg= 0;
	lastSeg	= numPoly-1;
	numSeg	= numPoly;

	zREAL	length		= (endPos-startPos).LengthApprox();
	int		lowIndex	= firstSeg;
	int		highIndex	= lastSeg;

	centerPointList[lowIndex]	= startPos;
	currentCenterPoint			= &centerPointList[lowIndex];

	Lightning0Subdivide (startPos, endPos, length * wildness, LogBase2(highIndex - lowIndex));
	
//	SetVisibleSegments	(0,1.0F);
	CalcBBox3D			();

	for (int i=0; i<numPoly; i++)
		alphaList[i]	= 255;
};

// ************************************
//		GenerateCP:		Circle
// ************************************

void zCPolyStrip::GenerateCircle (const zTBSphere3D& sphere, const zPOINT3& startPos, const zVEC3& dirNormal)
{
	EmptyEffect();

	zVEC3	right		= (startPos - sphere.center).NormalizeApprox();
	zVEC3	rotVec		= right ^ dirNormal;
	zMAT4	rotMat		= Alg_Rotation3D (rotVec, 360.0F / zREAL(numPoly));
	zPOINT3	point		= startPos;

	rotVec	*= GetWidth();

	newAlpha = 0;

	for (int i=0; i<numPoly; i++)
	{
		AddSegment (point-rotVec, point+rotVec);

		point	-= sphere.center;
		point	= rotMat.Rotate (point);
		point	+= sphere.center;
	};

	newAlpha = 255;
	CalcBBox3D	();
};

// =======================================================================================================================

zBOOL zCLightning::Render (zTRenderContext& renderContext) {
//	if (rootBolt.numSeg>0)
//		zlineCache.Line3D (rootBolt.centerPointList[rootbolt.firstSeg], rootBolt.centerPointList[rootbolt.lastSeg]);
	return rootBolt.Render (renderContext);
};

void zCLightning::SetVisualUsedBy (zCVob* vob) { 
	vob->SetIgnoredByTraceRay	(TRUE);
	vob->SetCollDet				(FALSE);
};

static zPOINT3		boltGlobalEndPos; 
static zTBSphere3D	boltGlobalSphere; 

void zCLightning::SetProjectionSphere (const zTBSphere3D& sphere) 
{
	boltGlobalSphere = sphere;
};

void zCLightning::Generate (const zPOINT3& startPos, const zPOINT3& endPos) 
{
//	boltGlobalSphere.center = endPos+zVEC3(100,-100,100);
//	boltGlobalSphere.radius	= (endPos-startPos).Length();

	boltGlobalEndPos = endPos;
	rootBolt.FreeResources	();
	rootBolt.SetWidth		(30.0F);
	rootBolt.SetGlobalAlpha	(200);
	rootBolt.Generate_R		(startPos, endPos);
};

void zCLightning::zCBolt::Generate_R (const zPOINT3& startPos, const zPOINT3& endPos, zREAL depth) {
	if (depth>zRandF()*3.0F+3.0F) return;
	zREAL len		= (endPos-startPos).LengthApprox();

	int numPoints	= int(len / (1000.0F) * 16.0F);
	numPoints		= zMakePowerOf2Lower(numPoints)+1;

	AllocateResources	(numPoints);
	GenerateCPLightning0(startPos, endPos);
//	ProjectToSphere		(boltGlobalSphere);

	int numChilds = int(zRand(5));
	if (numChilds<=0) return;
	childList.AllocAbs (numChilds);

	for (int i=0; i<numChilds; i++) 
	{
		int		stitchIndex;
		zVEC3	childStartPos;
		zVEC3	childEndPos;

		zCBolt *bolt	= zNEW(zCBolt);
		stitchIndex		= (firstSeg + zRand(numSeg / 2)) % numSeg;
//		stitchIndex		= (firstSeg + zAbs(int(GaussRand()*zREAL(numSeg)))) % numSeg;
		childStartPos	= centerPointList[stitchIndex];
		childEndPos		= zVEC3(zRandF2(), -(zRandF()*0.5F +0.5F), zRandF2());
		childEndPos.NormalizeApprox();

		childEndPos		= childStartPos + childEndPos * (zRandF()*0.3F + 0.3F) * (len);
		childEndPos[VY]	= zMax (boltGlobalEndPos[VY], childEndPos[VY]);

		bolt->SetGlobalAlpha( int(zREAL(GetGlobalAlpha())*0.4F));
		bolt->SetWidth		(GetWidth()*0.6F);
		bolt->Generate_R	(childStartPos, childEndPos, depth+1);
		childList.Insert	(bolt);
	};

}; 

void zCLightning::zCBolt::FreeResources () {
	zCPolyStrip::FreeResources();
	for (int i=0; i<childList.GetNum(); i++) {
		childList[i]->FreeResources ();
// delete childList[i];
	};
	childList.DeleteList();
};

zBOOL zCLightning::zCBolt::Render (zTRenderContext& renderContext) {
//	boltGlobalSphere.Draw();

	zCPolyStrip::Render (renderContext);
	for (int i=0; i<childList.GetNum(); i++) 
	{
		zCBolt *strip = childList[i];
//if (strip->numSeg>0)
//	strip->GenerateCP (strip->centerPointList[strip->firstSeg], strip->centerPointList[strip->lastSeg]);
		strip->Render (renderContext);
	}
	return TRUE;
};

// =======================================================================================================================

/*
/*	for (int i=firstSeg; num>1; num--,i++) 
	{
		if (i>=numPoly) i=0;
		zCPolygon *poly = &polyList[i];
		if (poly->ClipToFrustum (clipFlags)) { 
			if (poly->TransformProjectLight ()) 
			{
				// FIXME !
				for (int k=0; k<poly->numClipVert; k++) {
					poly->clipFeat[k]->lightDyn=poly->clipFeat[k]->lightStat;
				};

				zrenderer->DrawPoly (poly); 
			};
		};
	};
*/
/*	if (0)
	{
		static zCMaterial *mat = 0;
		if (!mat) {
			mat = zNEW(zCMaterial());
			mat->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_ADD);
			mat->SetAlpha			(100);
			mat->SetTexture			(zSTRING("zplasma0.TGA"));
		//	material.SetTexture			(zSTRING("zplasma1.TGA"));
		//	material.SetTexture			(zSTRING("zbeam3.TGA"));
		//	material.SetTexture			(zSTRING("plasma01.TGA"));
//			material.SetTexture			(zSTRING("LIGHTNING_A0.TGA"));
		};

		zrenderer->FlushPolys();

		zREAL oldW = GetWidth();
		SetWidth (oldW*5);
		AlignToCamera();
		SetWidth (oldW);

		int num = numSeg;
		for (int i=firstSeg; num>1; num--,i++) 
		{
			if (i>=numPoly) i=0;
			zCPolygon *poly = &polyList[i];
			zCMaterial *oldMat = poly->GetMaterial();
			poly->material		= mat;
			
			poly->lastTimeDrawn	= 0;
			for (int i=0; i<poly->polyNumVert; i++)
				poly->vertex[i]->transformed = 0;

			if (poly->ClipToFrustum (clipFlags)) { 
				if (poly->TransformProjectLight ()) 
				{
					// FIXME !
					for (int k=0; k<poly->numClipVert; k++) {
						poly->clipFeat[k]->lightDyn=poly->clipFeat[k]->lightStat;
					};

					zrenderer->DrawPoly (poly); 
				};
			};
			poly->material = oldMat;
		};
	};
*/


/*
  Effekte:
	* Laser-Beam	(endlos, begrenzt [expendable,heavyGear])
	- Spell-Blitz			(einfach/gespalten)
	- Wetter-Blitz
	- Kuppel-Blitz
	- Dark-Reign-Effekt
	- Sword-Trail, Arrow-Trail
	- Fahrzeug-Spuren
	- Messiah-FX	(screenshot, E3)
	- Spotlights	(HalfLife, Messiah)
	- Shadow-Man: Flammen !
	- Expendable-Effekt
	- Schatten ?
	* Scorch ?
	* Fusspuren ?

  Blitz-Effekt:
	- HalfLife
	* Genesis3D
	- Pics
	- Requiem
	- Ultima9-Video

  Properties: (fix/animiert)
	- Texture, UV
	- Vert-Color
	- Vert-Alpha
	- Vert-Pos
		- fixed/CamAlign
		- Breite des Strips

	- a) feste Vert-Positionen
	- b) Vert-Positionen zur Camera ausrichten 

- Primitiv: PolyStrip
	x Container fuer polyList
	x shared verts & shared features
	x 2 Modi:
		- a) camAlign 	(jeden Frame Verts neu berechnen)
		- b) fixed		(verts nur 1x berechnen)
	x Resourcen 1x holen ? 1x holen & cyclen ? dyn. erweitern ? 
	- Multipass mit variierenden Params ? (=> Requiem)
	- dynamische Effekte
		- den Strip verlaengern/verkuerzen
		- Breite des Strips variieren 	(beliebiege shape?, auf ganzer Laenger ? nur einen Teil ? Enden 'abrunden' (Turok2-Pfeil,Trail) ? dyn auf 0 faden?)
		x Alpha-Fade 					(alles gleichmaessig ? ..)
		- Color-Lerp					(")
- Flares/PFX? 
	- Start/Ende eines PolyStrips, mittendrin ?

- Vielleicht ein Visual, das n Polystrips mit demselben start/end beherbergt und einer gew. Wildness-Varianz ??

- Requiem-Blitz
	- Blitz-Generierung scheint recht einfach zu sein 
	  (alle n Einheiten ein zufaelliger Ausschlag mit Bias zur Mitte hin = wildness, sieht wohl nur
	  gut aus bei kleiner bis mittlerer Wildness, also eher gut fuer 'gerade' Blitze)
	- die centerPoints koennen auch 'morphen', bewegen sich also nicht schlagartig von Pos zu Pos, 
	  sondern morphen dazwischen...
	- Blitze haben als einen fixen Ort bestimmte Limbs des Koerpers
	- Ziel-Punkte wechseln nicht drastisch, sondern bewegen sich langsam, leicht zufaellig fort

- Ultima9 Blitz (Spell)
	- erleuchtet Umgebung (sogar mit OVERBRIGHT!)
	- Effekt hat ca. 5 Polystrips mit maessiger Wildness (vielleicht alle ein wenig versch, 1 auf 0.05?)
	- Effekt haelt ca. 2 Sekunden an, in dieser Zeit wird aber jeder Polystrip veraendert
	- die Polystrips haben leicht variierende Intensitaet/Dicke, aber keine spezielle Aura
	- Effekt erscheinen/verschwinden ist ohne Verzoegerung

=============

- Corona/Poly am Origin
- 'Aura' durch andere Textur ? oder 2 Passes ? während Haupt-Blitz oder erst danach ?
- dynamische Effekte:
	- Blitz waechst vorne (evtl. 'schwindet' hinten) (subSegment-genau, anspitzen an den Enden ?)
	- Blitz als ganzes fadet aus (alpha) (und hat wachsende width)
	- Breite variieren
	- 'flackern': alpha/Aura animieren 

- Blitz-Enden anspitzen ?

- echter Blitz: Intensitaet/Helligkeit zuckt in fertiger Form mehrmals 

=======================================================================================================

- Spell-Blitz
- Wetter-Blitz
- Kuppel-Blitz

- Sword-Trail
	- alpha-Fade
	- width-Fade
- Arrow-Trail

- Psi-Magie 'Bahnen'

=======================================================================================================

  TODO:
  - Decals/PFX an Start/Ende
  - Breite animieren/manipulieren
  - Multipass / Aura ? 
  - Morphen ? (ShadowMan Blitz,..)

  - Interface 'final' machen
  - noch fehlendee Effekte: Blitz (Wetter, Kuppel)

  - alphaListe/centerPointList vereinigen ?
  - widthList einfuehren ?

*/
