/******************************************************************************** 
 
     $Workfile:: zCamera.cpp    $                $Date:: 1.02.01 22:49    $
     $Revision:: 25                   $             $Modtime:: 1.02.01 22:49    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Camera 
   created: 26.5.2000

 * $Log: /current_work/zengin_work/_Dieter/zCamera.cpp $
 * 
 * 25    1.02.01 22:49 Hildebrandt
 * 
 * 24    27.01.01 19:42 Moos
 * 
 * 23    11.01.01 21:09 Hildebrandt
 * 
 * 22    4.12.00 18:23 Moos
 * 
 * 21    24.11.00 22:49 Hildebrandt
 * 
 * 20    22.11.00 13:25 Moos
 * 
 * 19    20.11.00 15:38 Pelzer
 * 
 * 18    17.11.00 23:16 Hildebrandt
 * 
 * 17    17.11.00 19:29 Moos
 * 
 * 16    14.11.00 19:23 Hildebrandt
 * 
 * 15    13.11.00 21:56 Hildebrandt
 * 
 * 14    19.10.00 17:48 Keskenti
 * 
 * 13    17.10.00 17:07 Hildebrandt
 * 
 * 12    11.10.00 19:45 Hildebrandt
 * 
 * 11    5.10.00 20:19 Hildebrandt
 * 
 * 10    27.09.00 19:57 Hildebrandt
 * 
 * 9     21.09.00 21:20 Hildebrandt
 * zenGin 0.94
 * 
 * 8     20.09.00 1:47 Rueve
 * 
 * 7     19.09.00 13:07 Hildebrandt
 * 
 * 6     21.08.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 5     9.08.00 17:12 Admin
 * 
 * 3     21.07.00 14:28 Hildebrandt
 * 
 * 2     3.07.00 12:44 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 25 $ ($Modtime: 1.02.01 22:49 $)
 
// =======================================================================================================================

#include <zCore.h>
#include <z3d.h>
#include <zVob.h>
#include <zView.h>
#include <zMemPool.h>
#include <zVertexTransform.h>
#include <zoption.h>

// =======================================================================================================================

#ifdef ZENGINE_DEBUG
#endif


///////////////////////////////////////////////////////////////////////////////////////////////
//     CAMERA
///////////////////////////////////////////////////////////////////////////////////////////////

// static element definition
zCCamera*	zCCamera::activeCam		= 0;
zPOINT3		zCCamera::activeCamPos	= 0;

zCCamera::zCCamera () 
{
	// Falls die 3D-Hardware nur einen lowres ZBuffer zur Verfuegung stellt, muss die NearPlane weiter entfernt
	// gewaehlt werden. (also: nur bei 16bit zbuffer die nplane wegschieben).
	zERR_ASSERT			(zrenderer);

#ifdef COMPILING_SPACER
	zREAL nearZIni = -1;
#else
	zREAL nearZIni = zoptions->ReadReal("ENGINE", "ZNEARVALUE", -1);
#endif

	if (nearZIni == -1)
	{
		switch( zrenderer->HasCapability(zRND_CAP_DEPTH_BUFFER_PREC) )
		{
		case	-32:
		case	-24:
		case	-16:
				nearClipZ = 1;
				break;
		case	32:
				nearClipZ = 10;
				break;
		case	24:
				nearClipZ = 20;					// Muss auf 20: alles darunter ist zu niedrig (wasserpoly flimmern). besser die camera nicht so nah an wände heranlassen als diese werte zu tunen
				break;
		default:
				nearClipZ = 35;
		}
	}
	else 
	{
		zClamp(nearZIni, 0.1f, 100.0f);
		nearClipZ = nearZIni;
	};
		
		
	farClipZ			= 4000;

	targetView			= 0;
	connectedVob		= 0;
	camMatrix			= 
		camMatrixInv	= 
		trafoView		= 
		trafoViewInv	= 
		trafoProjection	= 
		trafoWorld		= Alg_Identity3D(); 
	tremorScale			= 0;
	memset				(&vpData, 0, sizeof (vpData));
						
	//					
	tremorToggle		= 0;
	tremorScale			= 0;
	tremorAmplitude		= 0;
	tremorOrigin		= 0;
	tremorVelo			= 0;
						
	//					
	viewDistanceX		= 0;
	viewDistanceY		= 0;
	viewDistanceXInv	= 0;
	viewDistanceYInv	= 0;
	vobFarClipZ			= 0;
						
	topBottomSin		= topBottomCos=0;
	leftRightSin		= leftRightCos=0;
						
	// not used			
	projection			= PERSPECTIVE; 
	drawMode			= zCAM_DRAW_NORMAL;
	shadeMode			= zSHADE_NORMAL;
	drawWire			= FALSE;

	//
	screenFadeEnabled			= FALSE;
	screenFadeColor				= zCOLOR (0,0,0,255);
	screenFadeTextureAniFPS		= 0.0f;
	screenFadeTextureBlendFunc	= zRND_ALPHA_FUNC_BLEND;

	cinemaScopeEnabled	= FALSE;
	cinemaScopeColor	= zCOLOR (0,0,0,255);

	InitDrawPolySimple	();

	// 
	SetFOV				(90.0F);
}

zCCamera::~zCCamera() {
	targetView		= 0;
	connectedVob	= 0;

	CleanupDrawPolySimple	();
	if (activeCam==this)	activeCam=0;
};

void zCCamera::PushTransform (const zTCamTrafoType trafoType) 
{
	switch (trafoType)
	{
		case zCAM_TRAFO_WORLD:		trafoWorldStack.Push	(trafoWorld);	break;
		case zCAM_TRAFO_VIEW:		trafoViewStack.Push		(trafoWorld);	break;
		case zCAM_TRAFO_WORLDVIEW:	trafoWorldViewStack.Push(trafoWorld);	break;
	};
};

void zCCamera::PopTransform (const zTCamTrafoType trafoType) 
{
	switch (trafoType)
	{
		case zCAM_TRAFO_WORLD:	
			SetTransform	(trafoType, trafoWorldStack.Pop());
			break;
		case zCAM_TRAFO_VIEW:	
			SetTransform	(trafoType, trafoViewStack.Pop());
			break;
		case zCAM_TRAFO_WORLDVIEW:	
			SetTransform	(trafoType, trafoWorldViewStack.Pop());
			break;
	};
};

void zCCamera::SetTransform (const zTCamTrafoType trafoType, const zMATRIX4& trafo) 
{
	switch (trafoType)
	{
		case zCAM_TRAFO_WORLD:	
			trafoWorld			= trafo;
			camMatrix			= trafoView * trafoWorld;		// trafoWorldView
			camMatrixInv		= camMatrix.InverseLinTrafo();	// trafoWorldViewInv
			break;
		case zCAM_TRAFO_VIEW:	
			trafoView			= trafo;
			trafoViewInv		= trafo.InverseLinTrafo();
			camMatrix			= trafoView * trafoWorld;		// trafoWorldView
			camMatrixInv		= camMatrix.InverseLinTrafo();	// trafoWorldViewInv
			break;
		case zCAM_TRAFO_WORLDVIEW:	
			camMatrix			= trafo;						// trafoWorldView
			camMatrixInv		= trafo.InverseLinTrafo();		// trafoWorldViewInv
			break;
		default:
			return;
			break;
	};

	// abhaengige setups
	zCCamera::activeCam->camMatrixInv.GetTranslation( zCCamera::activeCamPos );
	SetUpFrustum();
	
	// Mitteilung an den Renderer, fuer Renderer- und Hardware TnLC
	zrenderer->SetTransform (zRND_TRAFO_VIEW, camMatrix.Transpose());
};

const zMATRIX4& zCCamera::GetTransform (const zTCamTrafoType trafoType)
{
	switch (trafoType)
	{
		case zCAM_TRAFO_WORLD:			return trafoWorld;		break;
		case zCAM_TRAFO_VIEW:			return trafoView;		break;
		case zCAM_TRAFO_WORLDVIEW:		return camMatrix;		break;
		case zCAM_TRAFO_WORLDVIEW_INV:	return camMatrixInv;	break;
		case zCAM_TRAFO_VIEW_INV:		return trafoViewInv;	break;
		default:						return camMatrix;		break;
	};
};

void zCCamera::Activate () 
{
	// 
	if (!connectedVob)	return;
	zERR_ASSERT (connectedVob);

#ifndef COMPILING_SPACER
	zERR_ASSERT (targetView);
#endif

	activeCam	 = this;

	// Object-Space =>(trafoWorld)=> WorldSpace =>(trafoView)=> CamSpace
	// OS						=>(trafoWorldView)=>			CS

	// trafoView				: obj(=cam)Space	=> worldSpace
	// trafoView				: obj(=cam)Space	=> camSpace=ViewSpace
	// trafoWorld				: objSpace			=> worldSpace
	// trafoWorldView=camMatrix	: objSpace			=> camSpace=ViewSpace	( trafoWorldView = trafoView * trafoWorld; )

	// trafoView setzen (ergibt sich aus CamVob)
	// camMatrix ist hier gleich der trafoView, da die trafoWorld hier noch frisch auf Identity steht
	trafoViewInv			= camMatrixInv	= connectedVob->trafoObjToWorld;
	trafoView				= camMatrix		= trafoViewInv.InverseLinTrafo();				// trafo: worldSpace	 => obj(=cam)Space

	//
	trafoWorld.MakeIdentity	();

	// abhaengige setups
	zCCamera::activeCam->trafoViewInv.GetTranslation( zCCamera::activeCamPos );
	SetUpFrustum();

	// Die Updates des Renderers sind hier wichtig. Der Renderer ist eine globale Resource, die in der Zwischenzeit
	// auch von anderen Benutzern modifiziert sein koennte. Das Sicherstellen des korrekten Zustandes ist hier noetig.
	// Mitteilung an den Renderer, fuer Renderer- und Hardware TnLC
	zrenderer->SetTransform (zRND_TRAFO_VIEW			, this->camMatrix.Transpose());
	zrenderer->SetTransform	(zRND_TRAFO_PROJECTION		, this->trafoProjection);
	zrenderer->SetViewport	(vpData.xmin, vpData.ymin	, vpData.xdim, vpData.ydim);
};


void zCCamera::CreateProjectionMatrix (  zMAT4& matrix,
										 const zREAL near_plane,		// distance to near clipping plane
										 const zREAL far_plane,			// distance to far clipping plane
										 const zREAL fov_horiz,			// horizontal field of view angle, in radians
										 const zREAL fov_vert)			// vertical field of view angle, in radians
{
    zREAL    h, w, Q;
 
    w = zREAL(1) / (zREAL)tan(fov_horiz*0.5);
    h = zREAL(1) / (zREAL)tan(fov_vert*0.5);
    Q = far_plane/(far_plane - near_plane);
 

	matrix.MakeIdentity();
	matrix[0][0] = w;
	matrix[1][1] = h;
	matrix[2][2] = Q;
	matrix[3][2] = -Q*near_plane;
	matrix[2][3] = 1;
	matrix[3][3] = 0;
	/*D3DXMatrixPerspectiveFovLH(reinterpret_cast<D3DMATRIX *>(&matrix),  fov_horiz, zREAL(vpData.xdim) / zREAL(vpData.ydim), near_plane, far_plane);

    const float halfAngle = 45.0f;*/
/*    const float y = tanf(halfAngle) * near_plane;
    const float x = y * (zREAL(vpData.ydim) / zREAL(vpData.xdim));
    const float zNear2 = 2.0f * near_plane;

    const float w = 2.0f * x;
    const float h = 2.0f * y;

    matrix[0][0] = zNear2 / w;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;

    matrix[1][0] = 0.0f;
    matrix[1][1] = zNear2 / h;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;

    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = far_plane/(far_plane-near_plane);
    matrix[2][3] = (near_plane*far_plane)/(near_plane-far_plane);

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 1.0f;
    matrix[3][3] = 0.0f;*/

};

/*
UNREAL
		// Setup projection matrix.
		FLOAT wNear=1.f, wFar=32767.f;
		ProjectionMatrix._33 = wFar / (wFar - wNear);
		ProjectionMatrix._34 = 1.f;
		ProjectionMatrix._43 = -ProjectionMatrix._33 * wNear;
		ProjectionMatrix._44 = 0.f;
		Direct3DDevice7->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &ProjectionMatrix );
*/ 

void zCCamera::UpdateProjectionMatrix () 
{
	CreateProjectionMatrix (	this->trafoProjection,
								this->GetNearClipZ(),
								this->GetFarClipZ (),
								fovH,
								fovV);
	zrenderer->SetTransform	(zRND_TRAFO_PROJECTION, this->trafoProjection);
};

zREAL zCCamera::GetFOV () const {
	return Alg_Rad2Deg(fovH);
}

void zCCamera::GetFOV (zREAL& fovHori, zREAL& fovVert) const {
	fovHori	= Alg_Rad2Deg (fovH);
	fovVert	= Alg_Rad2Deg (fovV);
}

void zCCamera::SetFOV (const zREAL fov) 
{
	// FIXME: so berechnen oder einen fixen Werte nehmen (z.B. 1.33) ?

	zREAL screenAspect;
	if (vpData.xdim==0) {
		screenAspect	= zREAL(1.0F) / zREAL(1.3333F);
	} else {
		screenAspect	= zREAL(vpData.ydim) / zREAL(vpData.xdim);
	};
	SetFOV (fov, fov * screenAspect);
};

/*--------------------------------------------------------------------------
    zCCamera::SetFOV()

    19-Sep-00       [Michael]
					  zSinCos eingeführt
--------------------------------------------------------------------------*/ 
void zCCamera::SetFOV (const zREAL fovHori, const zREAL fovVert) 
{
	// muss auch aufgerufen werden, wenn sich die Viewport-Dims ändern !

	fovH			= Alg_Deg2Rad (fovHori);
	fovV			= Alg_Deg2Rad (fovVert);

	// Vieport noch gar nicht gesetzt ?
	if (vpData.xdim==0) return;

	viewDistanceX	= (zREAL(vpData.xdim) * 0.5F) / zREAL(tan (fovH/2));
	viewDistanceY	= (zREAL(vpData.ydim) * 0.5F) / zREAL(tan (fovV/2));
	viewDistanceXInv= zREAL(1.0F) / viewDistanceX;
	viewDistanceYInv= zREAL(1.0F) / viewDistanceY;

	//
	zREAL angle;
	angle			= zREAL(atan((zVALUE(2.0) * viewDistanceX) / zREAL(vpData.xdim)));
	zSinCos			(angle, leftRightSin, leftRightCos);
	
	//
	angle			= zREAL(atan((zVALUE(2.0) * viewDistanceY) / zREAL(vpData.ydim)));
	zSinCos			(angle, topBottomSin, topBottomCos);
	
	// Renderer informieren
	UpdateProjectionMatrix();

/*	{
	// tan(FOV/2) = (screen_width/2)/d;    Horizontal FOV.
	// dist = (Xresolution / 2) / ( tan(FieldOfViewAngle / 2) )
	//	r_refdef.horizontalFieldOfView	= 2.0 * tan (scr_fov.value/360*M_PI);

	zREAL fov = 2.0F;
	zREAL fieldofview;
	zREAL viewDistance;
	zREAL viewDistanceInv;
	fieldofview		= fov;

	// for 3D-Clipping
	zVALUE maxscale,angle;
	zVALUE xscreenscale,yscreenscale;
	xscreenscale	= vpData.xdim / fieldofview;
	yscreenscale	= vpData.ydim / fieldofview;
	maxscale		= zMax(xscreenscale, yscreenscale);
	viewDistance	= maxscale;
	viewDistanceInv	= zVALUE(1.0) / viewDistance;

	//
	angle			= atan((zVALUE(2.0) * viewDistance) / (vpData.xdim));
	leftRightSin	= zSin(angle);
	leftRightCos	= zCos(angle);

	//
	angle			= atan((zVALUE(2.0) * viewDistance) / (vpData.ydim));
	topBottomSin	= zSin(angle); 
	topBottomCos	= zCos(angle);

	viewDistanceX	= viewDistance;
	viewDistanceY	= viewDistance;
	viewDistanceXInv= viewDistanceInv;
	viewDistanceYInv= viewDistanceInv;
	}
*/
}; 

void zCCamera::UpdateViewport() 
{
	if (targetView) 
	{
		const int	oldXMin	= vpData.xmin;
		const int	oldYMin	= vpData.ymin;
		const int	oldXDim	= vpData.xdim;
		const int	oldYDim	= vpData.ydim;
		targetView->GetViewport (vpData.xmin, vpData.ymin, 
								 vpData.xdim, vpData.ydim);
		// Nur aufwendige Updates durchfuehren, wenn sich Params wirklich geaendert haben
		if ((oldXMin!=vpData.xmin) ||
			(oldYMin!=vpData.ymin) || 
			(oldXDim!=vpData.xdim) || 
			(oldYDim!=vpData.xdim))
		{
			vpData.xcenter			= zVALUE(vpData.xdim) * zVALUE(0.5F) + zREAL(vpData.xmin);
			vpData.ycenter			= zVALUE(vpData.ydim) * zVALUE(0.5F) + zREAL(vpData.ymin);
			vpData.xminFloat		= zVALUE(vpData.xmin);
			vpData.yminFloat		= zVALUE(vpData.ymin);
			vpData.xmaxFloat		= zVALUE(vpData.xmin) + zVALUE(vpData.xdim) - 1;
			vpData.ymaxFloat		= zVALUE(vpData.ymin) + zVALUE(vpData.ydim) - 1;
			vpData.xdimFloat		= zVALUE(vpData.xdim);
			vpData.ydimFloat		= zVALUE(vpData.ydim);
			vpData.xdimFloatMinus1	= zVALUE(vpData.xdimFloat-1);
			vpData.ydimFloatMinus1	= zVALUE(vpData.ydimFloat-1);

			SetFOV					(Alg_Rad2Deg(fovH), Alg_Rad2Deg(fovV));
			SetUpFrustum			();
		};
	};
}; 

void zCCamera::SetRenderTarget (zCViewBase *target) {
	targetView				= target;
	UpdateViewport			();
};  

void zCCamera::SetRenderScreenFadeTex (const zSTRING texName)
{
	static zCTexture* screenFadeTexture = 0;
	if (!texName.IsEmpty())
	{
		screenFadeTexture = zCTexture::Load(zSTRING(texName));
	}
	else screenFadeTexture = NULL;

	polyMaterial->SetTexture(screenFadeTexture);
	zRELEASE(screenFadeTexture);
};


inline void zCCamera::SetWorldspaceClipPlane(const zPOINT3& normal, zTPlane *plane) 
{
	const zREAL CLIP_PLANE_EPSILON	= 0.0001F;
    // Rotate the plane normal from viewspace into worldspace
	// normal-trafo: camSpace => worldSpace
	// normalWorldSpace = (trafoCamToWorld^-1)^T * normalCamSpace = ...
	plane->normal   = normal * camMatrix;  
//	plane->normal   = camMatrixInv.Rotate (normal);
	plane->distance = (activeCamPos * plane->normal) - CLIP_PLANE_EPSILON; 
}


//////////////////////////////////////////////////////////////////////////////
// 3D-Frustum-Clipping
//////////////////////////



/////////////////////////////////////////////////////////////////////
// Set up the planes of the frustum, in worldspace coordinates.
/////////////////////////////////////////////////////////////////////

// FIXME: optimale Reihenfolge (laut Performer): left-right-near-far-up-down

void zCCamera::SetUpFrustum(void)
{
	// Aufruf nur nötig, falls sich Parameter des View-Frustums geändert haben,
	// d.h. ein anderes FOV, oder eine ander Auflösung. NICHT jeden Frame !!
	// (oder andere camMatrix, camPos, ...)
    zPOINT3	normal;

    // Left clip plane
    normal.n[VX] = leftRightSin;
    normal.n[VY] = 0;
    normal.n[VZ] = leftRightCos;
    SetWorldspaceClipPlane(normal, &frustumplanes[0]);
	signbits[0]	 = frustumplanes[0].CalcSignbits ();
    
	// Right clip plane
    normal.n[VX] =-leftRightSin;
    SetWorldspaceClipPlane(normal, &frustumplanes[1]);
	signbits[1]	 = frustumplanes[1].CalcSignbits ();
 
    // Bottom clip plane
    normal.n[VX] = 0;
    normal.n[VY] = topBottomSin;
    normal.n[VZ] = topBottomCos;
    SetWorldspaceClipPlane(normal, &frustumplanes[2]);
	signbits[2]	 = frustumplanes[2].CalcSignbits ();
 
    // Top clip plane
    normal.n[VY] = -topBottomSin;
    SetWorldspaceClipPlane(normal, &frustumplanes[3]);
	signbits[3]	 = frustumplanes[3].CalcSignbits ();
 
	// Far clip plane
	normal.n[VX] = 0;
    normal.n[VY] = 0;
    normal.n[VZ] =-1;
	zPOINT3 p					= camMatrixInv * zPOINT3(0,0,farClipZ);			// FIXME: optimierbar !
	frustumplanes[4].normal		= normal * camMatrix;
	frustumplanes[4].distance	= ( p * frustumplanes[4].normal); 
	signbits     [4]			= frustumplanes[4].CalcSignbits ();

	// Near clip plane (nearZ=0)
	frustumplanes[5].normal		=- frustumplanes[4].normal;
	frustumplanes[5].distance	=-(frustumplanes[4].distance + farClipZ);
	signbits	 [5]			=  frustumplanes[5].CalcSignbits();
 }

/*
void zCCamera::SetNearClipZ (const zREAL z)
{
	nearClipZ = zMax (zVALUE(0),z); 
	// Renderer informieren
	UpdateProjectionMatrix		();
};*/

void zCCamera::SetFarClipZ (const zVALUE z) 
{
	farClipZ = zMax (zVALUE(0),z); 

	// Far clip plane aktualisieren
	zVEC3 normal (0,0,-1);
//	const zPOINT3& p			= farClipZ * camMatrixInv.GetAtVector();
	const zPOINT3& p			= camMatrixInv * zPOINT3(0,0,farClipZ);			// FIXME: optimierbar !
	frustumplanes[4].normal		= normal * camMatrix;
	frustumplanes[4].distance	= ( p * frustumplanes[4].normal); 
	signbits     [4]			= frustumplanes[4].CalcSignbits ();

	// Renderer informieren
	UpdateProjectionMatrix		();
};


/////////////////////////////////////////////////////////////////////
// Check if 3D-Bounding Box is trivIn/trivOut/intersect. frustum
/////////////////////////////////////////////////////////////////////


zTCam_ClipType zCCamera::BBox3DInFrustum (const zTBBox3D& bbox3D) {
	// Quelle: News, BVolumes.txt
	// FIXME : die hier gesammelten 'straddle'-Infos koennten später beim Clippen der Polys
	//         aus der BBox am Frustum benutzt werden => clipFlags
	// return zSign(normal[VX]) + zSign(normal[VY])<<1 + zSign(normal[VZ])<<1

    int	i= NUM_FRUSTUM_PLANES - 1;
    do {
		switch (bbox3D.ClassifyToPlane (frustumplanes[i], signbits[i])) {
		case zPLANE_BEHIND:
			return zCAM_CLIP_TRIV_OUT;
			break;
		case zPLANE_SPANNING:
			return zCAM_CLIP_CROSSING;
			break;
		};
    } while( i-- );
	
	return zCAM_CLIP_TRIV_IN;
}

zTCam_ClipType zCCamera::BBox3DInFrustum (const zTBBox3D& bbox3D, int& clipFlags) {
	// Quelle: News, BVolumes.txt
	// FIXME : die hier gesammelten 'straddle'-Infos koennten später beim Clippen der Polys
	//         aus der BBox am Frustum benutzt werden => clipFlags

	int	i= NUM_FRUSTUM_PLANES - 1;
//	int	i= NUM_FRUSTUM_PLANES - 1 - 2;
    do {
		if (!(clipFlags & (1<<i)) ) continue;	// don't need to clip against it
/*		switch (bbox3D.ClassifyToPlane (frustumplanes[i])) {
//		switch (bbox3D.ClassifyToPlane (frustumplanes[i], signbits[i])) {
		case zPLANE_BEHIND:
			return zCAM_CLIP_TRIV_OUT;
			break;
		case zPLANE_INFRONT:
			clipFlags &= ~(1<<i);		// node is entirely on screen
			break;
		}; */
		zREAL dist;
		const zTPlane& plane = frustumplanes[i];
		switch (signbits[i]) {
		case 0:	// 000, ZYX
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		case 1:	// 001
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		case 2:	// 010
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		case 3:	// 011
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		case 4:	// 100
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		case 5:	// 101
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		case 6:	// 110
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		case 7:	// 111
			dist = bbox3D.maxs.n[VX]*plane.normal.n[VX] + bbox3D.maxs.n[VY]*plane.normal.n[VY] + bbox3D.maxs.n[VZ]*plane.normal.n[VZ];	if (dist<plane.distance) return zCAM_CLIP_TRIV_OUT;
			dist = bbox3D.mins.n[VX]*plane.normal.n[VX] + bbox3D.mins.n[VY]*plane.normal.n[VY] + bbox3D.mins.n[VZ]*plane.normal.n[VZ];	if (dist>=plane.distance) clipFlags &= ~(1<<i);
			break;
		};
    } while( i-- ); 
	
    return ( clipFlags> 0 ) ? zCAM_CLIP_CROSSING : zCAM_CLIP_TRIV_IN;
}


/////////////////////////////////////////////////////////////////////
// zCCamera:	Tremor
/////////////////////////////////////////////////////////////////////

void zCCamera::StopTremor () {
	tremorScale = 0;
};

void zCCamera::AddTremor (const zPOINT3& posWorldSpace, const zREAL radiusSquare, const zREAL timeMsec, const zVEC3& amplitude) {
	// tremor zu weit entfernt ?
	zREAL dist = (GetVob()->GetPositionWorld() - posWorldSpace).Length2();
	if (dist>=radiusSquare) return;

	dist = zREAL(1.0F) - (dist / radiusSquare);

	if (tremorScale<=0) 
	{
		tremorAmplitude		= dist * amplitude; 
		tremorScale			= 1.0F;
		tremorVelo			= zREAL(1.0F) / timeMsec;
	} else {
		// mix
		zVEC3 amp = dist * amplitude;
		for (int i=0; i<3; i++)
		tremorAmplitude[i]	= zMax (amp[i], tremorAmplitude[i]);
		tremorScale			= zREAL(0.5F) * (tremorScale + 1.0F);
		tremorVelo			= zMax (tremorVelo, zREAL(1.0F) / timeMsec);
	}; 
};

void zCCamera::PreRenderProcessing () {
	if (tremorScale>0) {
		tremorToggle = !tremorToggle;

		zVEC3 rand, offset;
//		if (tremorToggle)	rand = zVEC3(zRandF(), zRandF(), zRandF());
//		else				rand = zVEC3(zRandF()-1, zRandF()-1, zRandF()-1);
		if (tremorToggle)	rand[VY] = zRandF();
		else				rand[VY] = zRandF()-1;
		rand[VX] = zRandF()*2-1;
		rand[VZ] = zRandF()*2-1;
//		rand = zVEC3(zRandF()*2-1, zRandF()*2-1, zRandF()*2-1);
		
		tremorScale -= ztimer.GetFrameTimeF() * tremorVelo;
		if (zIsNegative(tremorScale)) tremorScale=0;
		offset		= tremorScale * Alg_Prod (tremorAmplitude, rand);

		tremorOrigin = GetVob()->GetPositionWorld();
		GetVob()->Move (offset);
	};
};

void zCCamera::PostRenderProcessing () 
{
	// Tremor
	if (tremorScale>0) {
		GetVob()->SetPositionWorld (tremorOrigin);
	};

	// ScreenFX
	RenderCinemaScope	();
	RenderScreenFade	();
};

void zCCamera::GetCamPos (zPOINT3& camPos) const { 
	connectedVob->GetPositionWorld (camPos);	
};

// ===========================================================================================================

void zCCamera::InitDrawPolySimple () 
{
	polyMesh			= zCMesh::CreateQuadMesh	(FALSE);
	poly				= polyMesh->Poly(0); 
	polyMaterial		= zNEW(zCMaterial);

	polyMesh->SetStaticLight				(zCOLOR(255,255,255,255));
	polyMesh->ResetLightDynToLightStat		();
};

void zCCamera::CleanupDrawPolySimple () 
{
	zRELEASE (polyMesh);
	zRELEASE (polyMaterial);
};

/* ----------------------------------------------------------------------
	
    zCamera::DrawPolySimple()	

	16.11.2000	[Moos]	
                auf neue Vertices umgestellt

    22.11.2000  [Moos]
                FlushPolys() ganz nach vorne verlegt, weil es
                die VertexTransforms manchmal resetted

   ---------------------------------------------------------------------- */

void zCCamera::DrawPolySimple (zTCamVertSimple *vertList, int numVert, zCMaterial *material, int drawFlags) 
{
	zrenderer->FlushPolys				();

	assert ((numVert>=3) && (numVert<=4));
	for (int i=0; i<numVert; i++)
	{
		zCVertexTransform* polyVert	= poly->vertex[i]->GetVertexTransform();
		polyVert->vertScrX			= vertList[i].x;
		polyVert->vertScrY			= vertList[i].y;
		polyVert->vertCamSpaceZInv	= vertList[i].z;
	};

	poly->polyNumVert					= numVert;
	poly->material						= material;
	poly->Unclip						(); 

	zrenderer->SetPolySortMode			(zRND_SORT_NONE);
	zrenderer->SetZBufferWriteEnabled	(FALSE);
	
	zrenderer->DrawPoly					(poly);
	zrenderer->FlushPolys				();

	zrenderer->SetPolySortMode			(zRND_SORT_ZBUFFER);
	zrenderer->SetZBufferWriteEnabled	(TRUE);
	poly->polyNumVert					= zTCAM_POLY_NUM_VERT;
	poly->material						= 0;
};

void zCCamera::SetRenderScreenFade (const zCOLOR color)
{
	screenFadeEnabled			= TRUE;
	screenFadeColor				= color;
};

void zCCamera::SetRenderScreenFadeTexAniFPS	(const zREAL a_aniFPS)
{
	this->screenFadeTextureAniFPS = a_aniFPS;
	if (polyMaterial) polyMaterial->texAniCtrl.SetAniFPS(this->screenFadeTextureAniFPS);
}

void zCCamera::SetRenderScreenFadeTexBlendFunc	(const zTRnd_AlphaBlendFunc a_blendFunc)
{
	this->screenFadeTextureBlendFunc = a_blendFunc;
}


void zCCamera::SetRenderCinemaScope	(const zCOLOR color)
{
	cinemaScopeEnabled	= TRUE;
	cinemaScopeColor	= color;
};

void zCCamera::RenderScreenFade ()
{
	if (!screenFadeEnabled) return;
	screenFadeEnabled				= FALSE;
	const zREAL VERT_Z				= zREAL(1.0F) / 0.0001F;
	polyCamVerts[3].x				= vpData.xminFloat;
	polyCamVerts[3].y				= vpData.yminFloat;
	polyCamVerts[3].z				= VERT_Z;
	polyCamVerts[2].x				= vpData.xmaxFloat;
	polyCamVerts[2].y				= vpData.yminFloat;
	polyCamVerts[2].z				= VERT_Z;
	polyCamVerts[1].x				= vpData.xmaxFloat;
	polyCamVerts[1].y				= vpData.ymaxFloat;
	polyCamVerts[1].z				= VERT_Z;
	polyCamVerts[0].x				= vpData.xminFloat;
	polyCamVerts[0].y				= vpData.ydimFloat;
	polyCamVerts[0].z				= VERT_Z;

	polyMaterial->GetAniTexture		();			// macht ein implizites AdvanceAnis() auf den AniCtrl und erlaubt damit animierte Texturen
	polyMaterial->SetColor			(screenFadeColor);
	polyMaterial->SetAlphaBlendFunc	(screenFadeTextureBlendFunc);
	DrawPolySimple					(polyCamVerts, 4, polyMaterial);
};

void zCCamera::RenderCinemaScope ()
{
	if (!cinemaScopeEnabled) return;
	cinemaScopeEnabled				= FALSE;
									
	const zREAL VERT_Z				= zREAL(1.0F) / 0.0001F;
	zREAL borderYDim				= vpData.ydimFloat * zREAL(0.12F) * cinemaScopeColor.GetAlphaFloat();
	
	// oben							
	polyCamVerts[3].x				= vpData.xminFloat;
	polyCamVerts[3].y				= vpData.yminFloat;
	polyCamVerts[3].z				= VERT_Z;
	polyCamVerts[2].x				= vpData.xmaxFloat+1;						// FIXME: warum +1 noetig ?
	polyCamVerts[2].y				= vpData.yminFloat;
	polyCamVerts[2].z				= VERT_Z;
	polyCamVerts[1].x				= vpData.xmaxFloat+1;
	polyCamVerts[1].y				= vpData.yminFloat + borderYDim;
	polyCamVerts[1].z				= VERT_Z;
	polyCamVerts[0].x				= vpData.xminFloat;
	polyCamVerts[0].y				= vpData.yminFloat + borderYDim;
	polyCamVerts[0].z				= VERT_Z;
	polyMaterial->SetColor			(cinemaScopeColor);
	polyMaterial->SetAlphaBlendFunc	(zRND_ALPHA_FUNC_BLEND);
	DrawPolySimple					(polyCamVerts, 4, polyMaterial);

	// unten
	polyCamVerts[3].y				= vpData.ymaxFloat - borderYDim;
	polyCamVerts[3].z				= VERT_Z;
	polyCamVerts[2].y				= vpData.ymaxFloat - borderYDim;
	polyCamVerts[2].z				= VERT_Z;
	polyCamVerts[1].y				= vpData.ymaxFloat+1;						// FIXME: warum +1 noetig ?
	polyCamVerts[1].z				= VERT_Z;
	polyCamVerts[0].y				= vpData.ymaxFloat+1;
	polyCamVerts[0].z				= VERT_Z;
	polyMaterial->SetColor			(cinemaScopeColor);
	DrawPolySimple					(polyCamVerts, 4, polyMaterial);
};

// =======================================================================================================================

zBOOL zCCFASTCALL zCCamera::ScreenProjectionTouchesPortalRough (const zTBBox3D& bbox3D, const zTBBox2D& portal2D)
{
	zTBSphere3D		sphere;
	sphere.center	= this->Transform (bbox3D.GetCenter());

	// 
	if (sphere.center[VZ]<=2)
	{
		// Objekte sehr nahe an Camera? => als sichtbar melden
		return TRUE;
	} else 
	{
		zVALUE	zrecip	= (zVALUE(1)) / sphere.center[VZ];
		zREAL	xc;
		zREAL	yc;
		this->Project( &(sphere.center), zrecip, xc, yc );
		// Teste zunächst den Kugel-Mittelpunkt auf seine Lage zum Portal
		if( (sphere.center[VX]<=portal2D.maxs[VX])&&
			(sphere.center[VX]>=portal2D.mins[VX])&&
			(sphere.center[VY]<=portal2D.maxs[VY])&&
			(sphere.center[VY]>=portal2D.mins[VY]) )
			return TRUE; //TRUE -> Berührung liegt vor (triviales IN)

		// Berechne die 2D-Bounding-Box des BSP-Leafs
		sphere.radius	= zREAL(0.5F) * (bbox3D.maxs - bbox3D.mins).LengthApprox();
		zPOINT3 p2		= sphere.center + zVEC3(-sphere.radius, sphere.radius,0);

		// impliziert sphere.center[VZ]>0 und somit brauchbare xc, yc
		zREAL xr,yr;
		this->Project( &(p2), zrecip, xr, yr );
		zTBBox2D		box2D;
		box2D.mins[VX]	= xr;
		box2D.mins[VY]	= yr;
		box2D.maxs[VX]	= xc+(xc-xr);
		box2D.maxs[VY]	= yc+(yc-yr);

		// Teste nun die grosszügig gehaltene 2D-Bounding-Box auf ihre Lage zum Portal
 		if ((box2D.maxs[VX]<portal2D.mins[VX])|| 
			(box2D.mins[VX]>portal2D.maxs[VX])|| 
			(box2D.maxs[VY]<portal2D.mins[VY])|| 
			(box2D.mins[VY]>portal2D.maxs[VY])) 
			return FALSE; //FALSE -> keine Berührung (triviales OUT)

		// Den 3. Test nicht bei BSP-Leafs einsetzen, da sonst 
		// hinundwieder Polys fehlen (3D-Bounding-Box zu klein?) 
		return TRUE;
	};
};

zBOOL zCCFASTCALL zCCamera::ScreenProjectionTouchesPortal (const zTBBox3D& bbox3D, const zTBBox2D& portal2D)
{
	zTBSphere3D		sphere;
	sphere.center	= this->Transform (bbox3D.GetCenter());

	// 
	if (sphere.center[VZ]<=2)
	{
		// Objekte sehr nahe an Camera? => als sichtbar melden
		return TRUE;
	} else 
	{
		zVALUE	zrecip	= (zVALUE(1)) / sphere.center[VZ];
		zREAL	xc;
		zREAL	yc;
		this->Project( &(sphere.center), zrecip, xc, yc );
		// Teste zunächst den Kugel-Mittelpunkt auf seine Lage zum Portal
		if( (sphere.center[VX]<=portal2D.maxs[VX])&&
			(sphere.center[VX]>=portal2D.mins[VX])&&
			(sphere.center[VY]<=portal2D.maxs[VY])&&
			(sphere.center[VY]>=portal2D.mins[VY]) )
			return TRUE; //TRUE -> Berührung liegt vor (triviales IN)

		// Berechne die 2D-Bounding-Box des BSP-Leafs
		sphere.radius	= zREAL(0.5F) * (bbox3D.maxs - bbox3D.mins).LengthApprox();
		zPOINT3 p2		= sphere.center + zVEC3(-sphere.radius, sphere.radius,0);

		// impliziert sphere.center[VZ]>0 und somit brauchbare xc, yc
		zREAL xr,yr;
		this->Project( &(p2), zrecip, xr, yr );
		zTBBox2D		box2D;
		box2D.mins[VX]	= xr;
		box2D.mins[VY]	= yr;
		box2D.maxs[VX]	= xc+(xc-xr);
		box2D.maxs[VY]	= yc+(yc-yr);

 		if ((box2D.maxs[VX]<portal2D.mins[VX])|| 
			(box2D.mins[VX]>portal2D.maxs[VX])|| 
			(box2D.maxs[VY]<portal2D.mins[VY])|| 
			(box2D.mins[VY]>portal2D.maxs[VY])) 
		{
			return FALSE; //FALSE -> keine Berührung (triviales OUT)
		};

		// Den 3. Test nicht bei BSP-Leafs einsetzen, da sonst 
		// hinundwieder Polys fehlen (3D-Bounding-Box zu klein?) 

		// Zum Schluss ein genauerer Test, da der Mittelpunkt ausserhalb des Portals liegt
		// und die grosszügig gehaltene 2D-Bounding-Box Kontakt mit dem Portal hat (also keiner
		// der beiden trivialen Fälle (IN oder OUT) vorliegt).
		{
			zPOINT3 pointOfBox3D[8];
			bbox3D.GetCornerPoints (pointOfBox3D);
			box2D.mins[VX] = xc;
			box2D.mins[VY] = yc;
			box2D.maxs[VX] = xc;
			box2D.maxs[VY] = yc;
			for( int t = 0; t<8; t++ )
			{
				pointOfBox3D[t] = this->Transform( pointOfBox3D[t] );
				
				// zu nahe an Camera? => als sichtbar markieren
				if (pointOfBox3D[t].n[VZ]<=2)	return TRUE;

				zCCamera::activeCam->Project( &(pointOfBox3D[t]), xc, yc );
				box2D.AddPoint (zVEC2(xc, yc));
			}
			// Teste die eng anliegende 2D-Bounding-Box auf ihre Lage zum Portal
			if( (box2D.maxs[VX]<portal2D.mins[VX])|| 
				(box2D.mins[VX]>portal2D.maxs[VX])|| 
				(box2D.maxs[VY]<portal2D.mins[VY])|| 
				(box2D.mins[VY]>portal2D.maxs[VY]) )
				return FALSE; //FALSE -> keine Berührung
		};

		return TRUE;
	};
};

// =======================================================================================================================

/*
void R_ViewChanged (vrect_t *pvrect, int lineadj, float aspect)
{
	int		i;
	float	res_scale;

	r_viewchanged = true;

	R_SetVrect (pvrect, &r_refdef.vrect, lineadj);

	r_refdef.horizontalFieldOfView	= 2.0 * tan (scr_fov.value/360*M_PI);
	r_refdef.fvrectx				= (float)r_refdef.vrect.x;
	r_refdef.fvrectx_adj			= (float)r_refdef.vrect.x - 0.5;
	r_refdef.vrect_x_adj_shift20	= (r_refdef.vrect.x<<20) + (1<<19) - 1;
	r_refdef.fvrecty				= (float)r_refdef.vrect.y;
	r_refdef.fvrecty_adj			= (float)r_refdef.vrect.y - 0.5;
	r_refdef.vrectright				= r_refdef.vrect.x + r_refdef.vrect.width;
	r_refdef.vrectright_adj_shift20 = (r_refdef.vrectright<<20) + (1<<19) - 1;
	r_refdef.fvrectright			= (float)r_refdef.vrectright;
	r_refdef.fvrectright_adj		= (float)r_refdef.vrectright - 0.5;
	r_refdef.vrectrightedge			= (float)r_refdef.vrectright - 0.99;
	r_refdef.vrectbottom			= r_refdef.vrect.y + r_refdef.vrect.height;
	r_refdef.fvrectbottom			= (float)r_refdef.vrectbottom;
	r_refdef.fvrectbottom_adj		= (float)r_refdef.vrectbottom - 0.5;

	r_refdef.aliasvrect.x			= (int)(r_refdef.vrect.x * r_aliasuvscale);
	r_refdef.aliasvrect.y			= (int)(r_refdef.vrect.y * r_aliasuvscale);
	r_refdef.aliasvrect.width		= (int)(r_refdef.vrect.width * r_aliasuvscale);
	r_refdef.aliasvrect.height		= (int)(r_refdef.vrect.height * r_aliasuvscale);
	r_refdef.aliasvrectright		= r_refdef.aliasvrect.x + r_refdef.aliasvrect.width;
	r_refdef.aliasvrectbottom		= r_refdef.aliasvrect.y + r_refdef.aliasvrect.height;

	pixelAspect						= aspect;
	xOrigin							= r_refdef.xOrigin;
	yOrigin							= r_refdef.yOrigin;
	
	screenAspect					= r_refdef.vrect.width*pixelAspect / r_refdef.vrect.height;

// 320*200 1.0 pixelAspect = 1.6 screenAspect
// 320*240 1.0 pixelAspect = 1.3333 screenAspect
// proper 320*200 pixelAspect = 0.8333333

	verticalFieldOfView = r_refdef.horizontalFieldOfView / screenAspect;

// values for perspective projection
// if math were exact, the values would range from 0.5 to to range+0.5
// hopefully they wll be in the 0.000001 to range+.999999 and truncate
// the polygon rasterization will never render in the first row or column
// but will definately render in the [range] row and column, so adjust the
// buffer origin to get an exact edge to edge fill
	xcenter			= ((float)r_refdef.vrect.width * XCENTERING) + 		r_refdef.vrect.x - 0.5;
	aliasxcenter	= xcenter * r_aliasuvscale;
	ycenter			= ((float)r_refdef.vrect.height * YCENTERING) +		r_refdef.vrect.y - 0.5;
	aliasycenter	= ycenter * r_aliasuvscale;

	xscale			= r_refdef.vrect.width / r_refdef.horizontalFieldOfView;
	aliasxscale		= xscale * r_aliasuvscale;
	xscaleinv		= 1.0 / xscale;
	yscale			= xscale * pixelAspect;
	aliasyscale		= yscale * r_aliasuvscale;
	yscaleinv		= 1.0 / yscale;
	xscaleshrink	= (r_refdef.vrect.width-6)/r_refdef.horizontalFieldOfView;
	yscaleshrink	= xscaleshrink*pixelAspect;

// left side clip
	screenedge[0].normal[0] = -1.0 / (xOrigin*r_refdef.horizontalFieldOfView);
	screenedge[0].normal[1] = 0;
	screenedge[0].normal[2] = 1;
	screenedge[0].type = PLANE_ANYZ;
	
// right side clip
	screenedge[1].normal[0] =
			1.0 / ((1.0-xOrigin)*r_refdef.horizontalFieldOfView);
	screenedge[1].normal[1] = 0;
	screenedge[1].normal[2] = 1;
	screenedge[1].type = PLANE_ANYZ;
	
// top side clip
	screenedge[2].normal[0] = 0;
	screenedge[2].normal[1] = -1.0 / (yOrigin*verticalFieldOfView);
	screenedge[2].normal[2] = 1;
	screenedge[2].type = PLANE_ANYZ;
	
// bottom side clip
	screenedge[3].normal[0] = 0;
	screenedge[3].normal[1] = 1.0 / ((1.0-yOrigin)*verticalFieldOfView);
	screenedge[3].normal[2] = 1;	
	screenedge[3].type = PLANE_ANYZ;
	
	for (i=0 ; i<4 ; i++)
		VectorNormalize (screenedge[i].normal);

	res_scale = sqrt ((double)(r_refdef.vrect.width * r_refdef.vrect.height) /
			          (320.0 * 152.0)) *
			(2.0 / r_refdef.horizontalFieldOfView);
	r_aliastransition = r_aliastransbase.value * res_scale;
	r_resfudge = r_aliastransadj.value * res_scale;

	if (scr_fov.value <= 90.0)	r_fov_greater_than_90 = false;
	else						r_fov_greater_than_90 = true;
	D_ViewChanged ();
}
*/

/*
QUAKE:
******
		for (i=0 ; i<4 ; i++)
		{
			if (! (clipflags & (1<<i)) )
				continue;	// don't need to clip against it

		// generate accept and reject points
		// FIXME: do with fast look-ups or integer tests based on the sign bit
		// of the floating point values

			pindex = pfrustum_indexes[i];

			rejectpt[0] = (float)node->minmaxs[pindex[0]];
			rejectpt[1] = (float)node->minmaxs[pindex[1]];
			rejectpt[2] = (float)node->minmaxs[pindex[2]];
			
			d = DotProduct (rejectpt, view_clipplanes[i].normal);
			d -= view_clipplanes[i].dist;

			if (d <= 0)
				return;

			acceptpt[0] = (float)node->minmaxs[pindex[3+0]];
			acceptpt[1] = (float)node->minmaxs[pindex[3+1]];
			acceptpt[2] = (float)node->minmaxs[pindex[3+2]];

			d = DotProduct (acceptpt, view_clipplanes[i].normal);
			d -= view_clipplanes[i].dist;

			if (d >= 0)
				clipflags &= ~(1<<i);	// node is entirely on screen
		}
*/

/*
zTCam_ClipType zCCamera::BBox3DInFrustum (const zTBBox3D& bbox3D) {
	// Quelle: News, BVolumes.txt
	// FIXME : die hier gesammelten 'straddle'-Infos koennten später beim Clippen der Polys
	//         aus der BBox am Frustum benutzt werden => clipFlags

    const zPOINT3* const minMax[ 2 ] = { &(bbox3D.mins), &(bbox3D.maxs) };
	
	int	straddle	= 0;					//number of planes the box straddles
    int	i			= NUM_FRUSTUM_PLANES - 1;
	
    do {
        int	ix = ( frustumplanes[ i ].normal[VX] > 0 ) ?  1 : 0;
        int	iy = ( frustumplanes[ i ].normal[VY] > 0 ) ?  1 : 0;
        int	iz = ( frustumplanes[ i ].normal[VZ] > 0 ) ?  1 : 0;
		
        zVALUE decision;
		decision  = minMax[ ix ]->n[VX] * frustumplanes[ i ].normal.n[VX];	// dot
        decision += minMax[ iy ]->n[VY] * frustumplanes[ i ].normal.n[VY];
        decision += minMax[ iz ]->n[VZ] * frustumplanes[ i ].normal.n[VZ];
		
        if( decision < frustumplanes[ i ].distance) return zCAM_CLIP_TRIV_OUT;
		
        decision  = minMax[ 1 - ix ]->n[VX] * frustumplanes[ i ].normal.n[VX];
        decision += minMax[ 1 - iy ]->n[VY] * frustumplanes[ i ].normal.n[VY];
        decision += minMax[ 1 - iz ]->n[VZ] * frustumplanes[ i ].normal.n[VZ];
		
		if( decision < frustumplanes[ i ].distance) ++straddle;
//		if( decision < frustumplanes[ i ].distance) return zCAM_CLIP_CROSSING;
    } while( i-- );
	
//	return zCAM_CLIP_TRIV_IN;
	return ( straddle > 0 ) ? zCAM_CLIP_CROSSING : zCAM_CLIP_TRIV_IN;
}
*/

	
/*
zTCam_ClipType zCCamera::BBox3DInFrustum (const zTBBox3D& bbox3D, int& clipFlags) {
	// Quelle: News, BVolumes.txt
	// FIXME : die hier gesammelten 'straddle'-Infos koennten später beim Clippen der Polys
	//         aus der BBox am Frustum benutzt werden => clipFlags

    const zPOINT3* const minMax[ 2 ] = { &(bbox3D.mins), &(bbox3D.maxs) };
	
    int	i		= NUM_FRUSTUM_PLANES - 1;
//	clipFlags	= 0;					//number of planes the box straddles
	
    do {
		if (!(clipFlags & (1<<i)) ) continue;	// don't need to clip against it

        int	ix = ( frustumplanes[ i ].normal[VX] > 0 ) ?  1 : 0;
        int	iy = ( frustumplanes[ i ].normal[VY] > 0 ) ?  1 : 0;
        int	iz = ( frustumplanes[ i ].normal[VZ] > 0 ) ?  1 : 0;
		
        zVALUE decision;
		decision  = minMax[ ix ]->n[VX] * frustumplanes[ i ].normal.n[VX];	// dot
        decision += minMax[ iy ]->n[VY] * frustumplanes[ i ].normal.n[VY];
        decision += minMax[ iz ]->n[VZ] * frustumplanes[ i ].normal.n[VZ];

		// backside
        if( decision < frustumplanes[ i ].distance) return zCAM_CLIP_TRIV_OUT;
		
        decision  = minMax[ 1 - ix ]->n[VX] * frustumplanes[ i ].normal.n[VX];
        decision += minMax[ 1 - iy ]->n[VY] * frustumplanes[ i ].normal.n[VY];
        decision += minMax[ 1 - iz ]->n[VZ] * frustumplanes[ i ].normal.n[VZ];
		
		// straddle
//		if( decision < frustumplanes[ i ].distance) clipFlags |=  (1<<i);
		// no straddle
		if( decision >=frustumplanes[ i ].distance) clipFlags &= ~(1<<i);	// node is entirely on screen
    } while( i-- );
	
    return ( clipFlags> 0 ) ? zCAM_CLIP_CROSSING : zCAM_CLIP_TRIV_IN;
}
*/

// =======================================================================================================================
