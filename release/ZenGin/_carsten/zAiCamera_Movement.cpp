
#include "zcore.h"
#include "ztypes3d.h"
#include "zKBSplines.h"
#include "zvob.h"
#include "zinput.h"
#include "zworld.h"
#include "zCSCamera.h"
#include "zmodel.h"
#include "zAICamera.h"
#include "zAICamera_Movement.h"
#include "zAICamera_Core.h"


// assume this average Frametime for RingBuffer -> Relax conversion
const static zREAL averageFrameTime = .025F; // 40 fps


// *********************************************************************************
// **							static global constants
// *********************************************************************************
 
zCMovementTracker* zCMovementTracker::GetTracker()
{ 
	static zCMovementTracker theTracker; 
	return &theTracker;	
};


zCMovementTracker::zCMovementTracker() 
/*:
	pathSearch	(zCPathSearch::GetSearch ())*/
{	
	playerPos					= zVEC3(0,0,0);
	playerPosRing				= zVEC3(0,0,0);
//	ringPosPreSamplesPlayerPos	= 0; 
//	ringPosPlayerPos			= 0;
//	ringPosPlayerPosMov			= 0;
//	ringPosCam					= 0; 
	POI_Player					= zVEC3(0,0,0);
	camVob						= 0;
	target						= 0;
								
	oldCamPos					= zVEC3(0,0,0);
	oldPlayerPosMovement		= zVEC3(0,0,0);
	camPos						= zVEC3(0,0,0);
	camPosRing					= zVEC3(0,0,0);
	sampledPlayerPos			= zVEC3(0,0,0);
	sampledPlayerPosRing		= zVEC3(0,0,0);
	oldSampledPlayerPosRing		= zVEC3(0,0,0);
	oldSampledPlayerPos			= zVEC3(0,0,0);
								
	actAzi						= 0;
	actElev						= 0;
	distToPlayer				= 0;
	oldElev						= 0;
	oldAzi						= 0;
	oldDistToPlayer				= 0;
								
	inertiaHead					= 0;
	inertiaTrans				= 0.1F;
//	inertiaTrans				= 0;
	inertiaRotTargetFOR			= 0.1F;
	inertiaTargetTrans			= 0.2F;
	inertiaTargetRot			= 0.04F;
								
	standing					= FALSE;
	rotate						= TRUE;
	numPreSamplesPlayerPos		= 10;
	numSamplesCam				= 2;
	numSamplesPlayer			= 2;
	timeSamples					= 100000;
	movement					= 0;
	actWayPointHead				= 0;
	actWayPointHipLeft			= 0;
	actWayPointHipRight			= 0;
	actWayPointCam				= 0;
	wayTimeHead					= 0;
	wayTimeHipLeft				= 0;
	wayTimeHipRight				= 0;
	wayTimeCam					= 0;
								
	frameTime					= 0;
	playerVeloRange				= 0;
	standTimer					= 0;
	playerAziSideSign			= 0;
	playerElevSideSign			= 0;
	oldPlayerPos				= zVEC3(0,0,0);
	playerHead					= zVEC3(0,0,0);
	playerHipLeft				= zVEC3(0,0,0);
	playerHipRight				= zVEC3(0,0,0);


	playerPosMovement			= zVEC3(0,0,0);
	playerPosMovementRing		= zVEC3(0,0,0);
	playerPosMovementLocal		= zVEC3(0,0,0);
	playerPosMovementLocalCam	= zVEC3(0,0,0);
	playerPosMovement			= zVEC3(0,0,0);
	playerFuturePos				= zVEC3(0,0,0);

	playerFuturePosDT			= PLAYER_FUTURE_POS_ADVANCE_TIME_SEC;
	bMouseUsed					= FALSE;

	oldTrafoWStoTS		.MakeIdentity();
	oldTrafoWStoCS		.MakeIdentity();
	oldTrafoRotOffsetWStoCS.MakeIdentity();
	lastValidCamTrafo	.MakeIdentity();
	initialPoseRotFreeze.MakeIdentity();
	startRot			.Identity();
	endRot				.Identity();
	maxAziRot			.Identity();
	minAziRot			.Identity();
	idealRot			.Identity();
	idealRotTrans		.Identity();
	actRot				.Identity();
	idealRotLocal		.Identity();

	ResetWayPoints		( zPOINT3(0,0,0), zWAYPOINT_PLAYER );
	ResetWayPoints		( zPOINT3(0,0,0), zWAYPOINT_CAM );
	ClearMessages		();

//	for (int i=0; i<NUM_MOV_SAMPLES_FOCUS ; i++) movRingFocus[i] = zVEC3(0,0,0);
	pathSearch = zCPathSearch::GetSearch();

};

zCMovementTracker::~zCMovementTracker()
{
    while(targetKFList.GetNumInList() > 0)
	{
        zCPositionKey *delkey=targetKFList[0];
		targetKFList.RemoveOrder(delkey);
        delete delkey; 
    }
};


/********************************************************************************
 FUNCTION: GetAzimuth/Elevation 
 DESC    : Returns azimuth/elevation-angles between Cam-/ and target-heading
 RETURN  : -180.0 Deg to 180.0 Deg
*********************************************************************************/

float zCMovementTracker :: GetAzimuth(void)
{
	return GetAzimuth(GetCamPos());
}

float zCMovementTracker :: GetElevation(void) 
{
	return GetElevation(GetCamPos());
}

zREAL	zCMovementTracker :: GetAzimuth			(const zPOINT3 &testPos)
{
	const float	FAK = float(180/M_PI);

	zVEC3 atTarget = trafoTStoWS.GetAtVector();
	zVEC3 atCam	   = (playerPos - testPos).NormalizeSafe();
	
	zVEC3 up;
	// FIXME: The following code atCam == zVEC3(0,1,0) returns FALSE even if atCam is (0,1,0) ???
	up			= zPOINT3 (0,1,0);
	up			= (up + (-(up * atCam) * atCam)).NormalizeSafe(); // nötig ???
	zVEC3 right	= (up ^ atCam).NormalizeSafe();
	
	//							       ->  ->	  ->
	// Get YZ Plane through cam. E: 0=(X - P) dot n0
	zPOINT3	 planePt = testPos;
	// Get point to test plane with
	zPOINT3  testPt  = playerPos + trafoTStoWS.GetAtVector();
    // Determin on which side testPt lies
	float side = (testPt - planePt) * right;

	// project heading vecs onto world xz-plane

	zVEC2 aziTarget(atTarget[VX],atTarget[VZ]);
	zVEC2 aziCam   (atCam	[VX],atCam	 [VZ]);

	if (aziTarget.Length2()!=0) aziTarget.Normalize();
	if (aziCam	 .Length2()!=0) aziCam   .Normalize();

	float angle = aziTarget * aziCam;

	zClamp ( angle, zVALUE(-1), zVALUE(1) );

	// Get Azimuth Angle (- 180 Deg. to 180 Deg)
	float deg =  float( acos( double(angle) )*FAK );

	if (side<=0) return -deg;
	else		 return +deg;

};

zREAL	zCMovementTracker :: GetElevation		(const zPOINT3 &testPos)
{

	const float	FAK = float(180/M_PI);
	zPOINT3 planePt	= playerPos;

	//							       ->  ->	  ->
	// Get XZ Plane through cam. E: 0=(X - P) dot n0
    zPOINT3	 camP	= testPos;
	planePt[VY]		= camP[VY];  // Reset to 0 Deg.

	zVEC3    at		= (planePt - camP).NormalizeSafe();
	
	// Get orthogonal up vec from new at vec
	zVEC3 up = zPOINT3 (0,1,0);
	up = (up + (-(up * at) * at)).NormalizeSafe();

	// Get point to test plane with
	zPOINT3  testPt =  playerPos + trafoTStoWS.GetAtVector();
    
	// Determin on which side testPt lies
	float side		= (testPt - planePt) * up;
	float angle		= at * (playerPos - testPos).NormalizeSafe();

	zClamp ( angle , zVALUE(-1) , zVALUE(1) );	

	// Get Elevation Angle (-180 Deg. to 180 Deg)
	float deg =  float ( acos( (double) angle ))*FAK ;

	if (side <=0) return +deg;
 	else		  return -deg;

};

zREAL	zCMovementTracker :: GetRange			(const zPOINT3 &testPos)
{
	return (playerPos - testPos).Length();
};

/********************************************************************************
 FUNCTION: SetAzimuth/Elevation
 DESC    : Sets Elevation & Azimuth
 PARAM   : angle (-180 Deg. to 180 Deg)
*********************************************************************************/

void zCMovementTracker :: SetAzimuth(const float &angleDeg)
{
	camPos = ApplyAziToPoint(angleDeg,camPos);
}

void zCMovementTracker :: SetElevation(const float &angleDeg) 
{
	camPos = ApplyElevToPoint(angleDeg,camPos);
}

void zCMovementTracker :: SetRange(const float &dist)
{
	zVEC3 headVec = ( camPos - playerPos ).NormalizeSafe();
	camPos =  playerPos + (dist * headVec) ;
}


zREAL zCMovementTracker :: GetRange			()
{
	return (camPos-playerPos).Length();
};

/********************************************************************************
 FUNCTION: ApplyAziToPoint
 DESC    : Gets a new (world) position of a given point if rotated with given azi 
		   around target
*********************************************************************************/
/*--------------------------------------------------------------------------
    19-Sep-00       [Michael]
                      zSinCos eingeführt

  20-Sep-00       [Edenfeld]
                      zSinCos wieder durch sin/cos Calls ersetzt. Könnte durch Ungenauigkeiten
					  zu Camera Wackeln führen. Zur weiteren Beobachtung in Release 0.94 ist zSinCos drin...

--------------------------------------------------------------------------*/ 
zPOINT3 zCMovementTracker :: ApplyAziToPoint(const float &angleDeg,const zPOINT3 &camP)
{

	const zREAL	FAK = float(M_PI * ((1.0) / 180.0));
    const zREAL	angleRad= (180-angleDeg) * FAK;

	//						  ->  ->           ->            ->
	// Setup circle in Space. x = m + r*cos(b)*u0 + r*sin(b)*v0
	zVEC3 u0 = trafoTStoWS.GetAtVector();
	zVEC3 v0 = trafoTStoWS.GetRightVector();

	u0[VY]=0.0F; v0[VY]=0.0F;  // hier nicht mehr nötig ?
	u0.NormalizeSafe(); v0.NormalizeSafe();

	zPOINT2 camProj2d	(camP[VX],camP[VZ]);
	zPOINT2 targetProj2d(playerPos[VX],playerPos[VZ]);

    const float r = (camProj2d - targetProj2d).Length();

	zREAL anglesin, anglecos;
	zSinCos(angleRad, anglesin, anglecos);
	
	// get new azimuth position on circle
	zPOINT3 newPos =  playerPos +	(r * anglecos) * u0 + 
				 					(r * anglesin) * v0 ;

	return zPOINT3(newPos[VX],camP[VY],newPos[VZ]);

}
/*--------------------------------------------------------------------------
    19-Sep-00       [Michael]
                      zSinCos eingeführt

  20-Sep-00       [Edenfeld]
                      zSinCos wieder durch sin/cos Calls ersetzt. Könnte durch Ungenauigkeiten
					  zu Camera Wackeln führen. Zur weiteren Beobachtung in Release 0.94 ist zSinCos drin...

--------------------------------------------------------------------------*/ 
zPOINT3 zCMovementTracker :: ApplyElevToPoint(const float &angleDeg,const zPOINT3 &camPos)
{	

	zPOINT3 camP = camPos;
	const zREAL angleRad = (angleDeg+360.0f) * ((float) M_PI * ((1.0f) / 180.0f));
	//						  ->  ->           ->            ->
	// Setup circle in Space. x = m + r*cos(b)*u0 + r*sin(b)*v0
	const float r = (camP - playerPos).Length();

	zVEC3 u0,v0;

	// find u0 and v0. 
	u0 = (camP-playerPos).NormalizeSafe();

	if ( !u0.IsEqualEps(zVEC3(0,1,0)) && !u0.IsEqualEps(zVEC3(0,-1,0)))  
	{
		camP[VY] = playerPos[VY];
		u0 = (camP-playerPos).NormalizeSafe();
	}
	else 
	{
		zPOINT3 aziPos	= ApplyAziToPoint  ( GetAzimuth(), playerPos-trafoTStoWS.GetAtVector() );
		u0				= (playerPos-aziPos).NormalizeSafe();
	}

	// Get orthogonal up (=v0) vec. from new target at-vec.
	v0 = zPOINT3 (0,1,0);
	v0 = (v0 + (-(v0 * u0) * u0)).NormalizeSafe(); // nötig ???

	zREAL anglesin, anglecos;

	zSinCos(angleRad, anglesin, anglecos);

	// get new elevation position on circle
	return zPOINT3( playerPos + (r * anglecos) * u0 + 
					            (r * anglesin) * v0 );
}

zPOINT3 zCMovementTracker :: ApplyRangeToPoint(const float & dist,const zPOINT3 & p)
{
	const zVEC3 headVec= ( p-playerPos ).NormalizeSafe();
	return ( playerPos + (dist * headVec) );

}

zPOINT3 zCMovementTracker::GetRangePos(const float & dist)
{
	return ( playerPos + (( camPos-playerPos ).NormalizeSafe() * dist ));
}


zPOINT3 zCMovementTracker :: GetIdealRangePos()
{
	const zVEC3 headVec = ( camPos - playerPos ).NormalizeSafe();
	return ( playerPos + (camai->GetBestRange() * 100 * headVec) );
}

float zCMovementTracker :: GetDistToIdealRange()
{
	return ( (GetIdealRangePos() - camPos ).Length() );
}


zBOOL zCMovementTracker :: IsIdealOrientation()
{
	const float epsilonAngle = 1.5F;
	zBOOL flag = zAbs( GetAzimuth()  - camai->bestRotY   ) < epsilonAngle;
		  flag&= zAbs( GetElevation()- camai->bestRotX   ) < epsilonAngle;
	return ( flag ); 
}

zBOOL zCMovementTracker :: IsIdealRange()
{
	const float epsilonRange = 0.1F;
	return ( GetDistToIdealRange() < epsilonRange ) ;
}

void zCMovementTracker::UpdateCamPos(const zPOINT3 & newPos)
{
    zREAL dist2 = (newPos - camPosRing).Length2() / 100000;

    zREAL frac = frameTime / (numSamplesCam * averageFrameTime);
    frac      *= (1 + 4 * dist2) / (1 + dist2);

    camPosRing += newPos * frac;
    camPosRing /= (1 + frac);

	camPos     = newPos;
}

void zCMovementTracker::UpdatePlayerPos(const zPOINT3 & newPos)
{
    zVEC3 at = newPos - this->GetCamPos();
    at.NormalizeSafe();

    // die Basis-Schrittweite:
    zREAL parFrac  = frameTime / (numSamplesPlayer * averageFrameTime);
    zREAL perpFrac = parFrac;
    
    // Zerlege aktuelle und gesmoothte Position in Anteile paralell und Senkrecht zu at
    zVEC3 parNewPos  = at * (newPos * at);
    zVEC3 perpNewPos = newPos - parNewPos;

    zVEC3 parRelaxPos  = at * (playerPosRing * at);
    zVEC3 perpRelaxPos = playerPosRing - parRelaxPos;


    // extra-Faktoren für die Basis-Schrittweite, damit die Kamera nicht zu arg nachhängt
    zREAL dist2 = (newPos - playerPosRing).Length2() / 10000;
    if (at * (newPos - playerPosRing) < 0)
        dist2 -= at * (newPos - playerPosRing) * .1F;
  
    zREAL perpDist2 = (perpNewPos - perpRelaxPos).Length2() / 10000;

    parFrac   *= ((1   + 3*perpDist2) / (1 + perpDist2));
    perpFrac  *= ((.1F +       dist2) / (2 +     dist2));


    // und die eigentliche Anpassung
	parRelaxPos += parNewPos * parFrac;
    parRelaxPos /= (1 + parFrac);

	perpRelaxPos += perpNewPos * perpFrac;
    perpRelaxPos /= (1 + perpFrac);

    // füge die beiden Anteile wieder zusammen
	playerPosRing = parRelaxPos + perpRelaxPos;
	playerPos	  = newPos;	
}

void zCMovementTracker::SetCamPos(const zPOINT3 & newPos)
{
	// ring coord = absolute coord
    camPosRing = camPos = newPos;
	if (movement & zPLAYER_BEAMED) ResetWayPoints(newPos , zWAYPOINT_CAM );
}

void zCMovementTracker::CalcPlayerPose()
{
	float HIP_OFFSETX			   = 15;
	float HIP_OFFSETY			   = 0;

	static zVEC3 v=zVEC3(0,0,0);

	if (!target) return;
	/* Build target pose we are interested in */

	if (!target->trafoObjToWorld.IsUpper3x3Orthonormal())
	{
		zERR_WARNING("C: zCMovementTracker::CalcFocusPose(): Player trafoObjToWorld is not orthonormal, orthonormalizing...");
		target->trafoObjToWorld.MakeOrthonormal();
	}
	// [HILDEBRANDT] Zugriff auf zCVob::trafo zwecks Kapselung entfernt, sollte hier sowieso nicht noetig sein.
/*	if (!target->trafo.IsUpper3x3Orthonormal())
	{
		zERR_WARNING("C: zCMovementTracker::CalcFocusPose(): Player trafo			is not orthonormal, orthonormalizing...");
		target->trafo.MakeOrthonormal();
	}*/

	zVEC3 meatBugOffsetVec	= zVEC3(0,0,0);
	zCModel *targetModel	= dynamic_cast<zCModel*>(target->GetVisual());

	if (targetModel)
	{
		const zTBBox3D	bbox			= targetModel->GetBBox3DLocalFixed();
		const float		yXT				= bbox.maxs[VY]-bbox.mins[VY];
		if (yXT<40)		meatBugOffsetVec= zVEC3(0,20,0);
		HIP_OFFSETX						= bbox.maxs[VX] * 0.8f;
	}

	zVEC3	at		= target->GetAtVectorWorld();
	zVEC3	up		= zVEC3(0,1,0);
	zVEC3	right	= target->GetRightVectorWorld();

	// project at vec onto world-xz-plane if necessary
	at[VY] = 0;
	at.NormalizeSafe();

	right[VY] = 0;
	right.NormalizeSafe();

	// get and smooth out players position
	UpdateSampledPlayerPos ( target->GetPositionWorld	()							+ meatBugOffsetVec );

/*	@@@
	timeSamples += frameTime;

	if ( timeSamples >= secToSample ) 
	{
		zVEC3 newV = (GetSampledPlayerPosRing() - GetPlayerPos()) / timeSamples;
		// Only update velocity if last & actual velocities are not nearly equal
		if (!NearlyEqual(v,newV,0.5F)) v = newV;
		timeSamples=0;
	}

	zPOINT3 newFocusPos = GetPlayerPos() + ( frameTime * v );*/

	UpdatePlayerPos ( GetSampledPlayerPosRing() +
							 right						   * camai->focusOffsetX	+
							 up							   * camai->focusOffsetY	+
							 at							   * camai->focusOffsetZ );

	playerPos = playerPosRing;

	pathSearch->AdjustCenterSphere(playerPos,	 target->GetPositionWorld()  );

	// calculate target head and hip points for player waypoint calculations
	zREAL	yOffset;

	zCModel *model = dynamic_cast<zCModel*>(target->GetVisual());

	if (model && model->SearchNode(zMDL_NODE_NAME_HEAD))
	{
		zMAT4 trafoHead = target->GetTrafoModelNodeToWorld(zMDL_NODE_NAME_HEAD);
		yOffset = trafoHead.GetTranslation()[VY]-playerPos[VY]+10;
	}
	else yOffset = target->GetBBox3DWorld().maxs[VY] - playerPos[VY] + 10;

	// FIXME: yOffset in einen ringbuffer
	
	playerHead			=  zPOINT3( playerPos[VX], playerPos[VY]+yOffset, playerPos[VZ] );
	playerHipLeft		=  playerPos - (up * HIP_OFFSETY) - (right * HIP_OFFSETX);
	playerHipRight		=  playerPos - (up * HIP_OFFSETY) + (right * HIP_OFFSETX);

	if (rotate)		   trafoTStoWS = GetPoseOfHeading( GetPlayerPos(), at );
	else			   trafoTStoWS = initialPoseRotFreeze;

	if ((movement & zPLAYER_BEAMED) || bMouseUsed)  sampledPlayerPose.SetRot(trafoTStoWS);
	else											sampledPlayerPose.UpdateRot(trafoTStoWS);

	trafoTStoWS = sampledPlayerPose.GetRotMat();
	trafoTStoWS.SetTranslation(playerPos);

	initialPoseRotFreeze.SetTranslation(playerPos);

	trafoWStoTS = zInverseMatD(trafoTStoWS,zSTRING("CalcPlayerPose"));

	// dafür sorgen, das alle gewählten spieler referenz positionen auch wirklich in der welt sind, d.h.
	// die target root pos muss gesehen werden. assert: die target root node ist _immer_ gültig.
	// FIXME: AdjustCenterSphere ist zu langsam !

	pathSearch->AdjustCenterSphere(playerHead,	 playerPos);
	pathSearch->AdjustCenterSphere(playerHipLeft, playerPos);
	pathSearch->AdjustCenterSphere(playerHipRight,playerPos);

	playerFuturePos = GetPlayerFuturePos(playerFuturePosDT);

	UpdateWayPoint( zWAYPOINT_PLAYER );

	// determin on which side of the camera at vec the target lies
	zPOINT3 playerLocalCam = GetCamTrafoInv() * GetPlayerPos();
	if		(playerLocalCam[VX]<0) playerAziSideSign = -1.0F;
	else if (playerLocalCam[VX]>0) playerAziSideSign = +1.0F;
	else						   playerAziSideSign =  0.0F;

	if		(playerLocalCam[VY]<0) playerElevSideSign = -1.0F;
	else if (playerLocalCam[VY]>0) playerElevSideSign = +1.0F;
	else						   playerElevSideSign =  0.0F;

}

void zCMovementTracker::CalcPlayerMovements()
{
    // [Moos] FIXME: Wieso wird hier mit frameTime multipliziert? und wieso später nochmal (war avg *= frameTime)??
	zPOINT3 newMov = ((trafoWStoCS * playerPos)-(trafoWStoCS *oldPlayerPos)) * frameTime;

    zREAL frac = frameTime / (NUM_MOV_SAMPLES_FOCUS * averageFrameTime);

    playerPosMovementRing += frameTime * frac * newMov;
    playerPosMovementRing /= (1 + frac);

	playerPosMovement			= (trafoWStoCS    * playerPos) - (trafoWStoCS    * oldPlayerPos);
	playerPosMovementLocal		= (oldTrafoWStoTS * playerPos) - (oldTrafoWStoTS * oldPlayerPos);
	playerPosMovementLocalCam	= (oldTrafoWStoCS * playerPos) - (oldTrafoWStoCS * oldPlayerPos);
}

void zCMovementTracker::SetPlayerPos(const zPOINT3 &newTarget)
{
    playerPos = playerPosRing = newTarget;

	ResetWayPoints		( newTarget, zWAYPOINT_PLAYER );
	SetSampledPlayerPos	( newTarget );
}

void zCMovementTracker::ReceiveMsg	(const zTAICamMsg &msg)
{
	movement |= msg;
}

void zCMovementTracker::ClearMessages()
{
	movement = zPLAYER_ROT_NONE | zPLAYER_STAND  ;
}

void zCMovementTracker::AutoSetMessages()
{
	// nun die Bewegungen des Spielers in Messages umwandeln
	const float EPS_REC_MOVE_RIGHT		=	1.5F;	const float EPS_REC_MOVE_LEFT		=	1.5F;
	const float EPS_REC_MOVE_UP			=	0.5F;	const float EPS_REC_MOVE_DOWN		=	0.5F;
	const float EPS_REC_MOVE_FORWARD	=	3.5F;	const float EPS_REC_MOVE_BACKWARD	=	3.5F;
	const float EPS_REC_ROT_LEFT		=	0.02F;  const float EPS_REC_ROT_RIGHT		=	0.02F;


	// translations messages aus der bewegung des spielers im camera koordinaten system ermitteln
	if		( playerPosMovementLocalCam[VX] > +EPS_REC_MOVE_RIGHT   ) movement |= zPLAYER_MOVED_RIGHT;
	else if	( playerPosMovementLocalCam[VX] < -EPS_REC_MOVE_LEFT    ) movement |= zPLAYER_MOVED_LEFT;
	if		( playerPosMovementLocalCam[VY] > +EPS_REC_MOVE_UP		) movement |= zPLAYER_MOVED_UP;
	else if	( playerPosMovementLocalCam[VY] < -EPS_REC_MOVE_DOWN	) movement |= zPLAYER_MOVED_DOWN;
	if		( playerPosMovementLocalCam[VZ] > +EPS_REC_MOVE_FORWARD ) movement |= zPLAYER_MOVED_FORWARD;
	else if	( playerPosMovementLocalCam[VZ] < -EPS_REC_MOVE_BACKWARD) movement |= zPLAYER_MOVED_BACKWARD;

	//zERR_MESSAGE(5,0,"C: vr[VX]: " + zSTRING(playerPosMovementLocalCam[VX]) + ", vr[VY]: " + zSTRING(playerPosMovementLocalCam[VY]) + ", vr[VZ]: " + zSTRING(playerPosMovementLocalCam[VZ]));

	// rotations messages aus der differenz rotation des spielers ermitteln
	zMAT4	t1		 =  oldTrafoWStoTS.InverseLinTrafo();
	zMAT4	t2		 =  trafoTStoWS; 
	zVEC3	v0		 =	t1.GetAtVector();
	zVEC3	v1		 =  t2.GetAtVector();

	zVEC3	vr		 =  v0^v1;
	
	if	    (vr[VY]>+EPS_REC_ROT_RIGHT) movement |= zPLAYER_ROTATED_RIGHT;
	else if (vr[VY]<-EPS_REC_ROT_LEFT ) movement |= zPLAYER_ROTATED_LEFT;
	// rotation um die x und z achsen wird nicht benutzt

}

void zCMovementTracker::UpdateMessages()
{
	if ( (movement & zPLAYER_MOVED_FORWARD) || (movement & zPLAYER_MOVED_BACKWARD) ||
		 (movement & zPLAYER_MOVED_UP)	    || (movement & zPLAYER_MOVED_DOWN)	   ||
		 (movement & zPLAYER_MOVED_LEFT)	|| (movement & zPLAYER_MOVED_RIGHT) )
	{
		movement |= zPLAYER_MOVED;
		movement &= ~zPLAYER_STAND;
	};

	if ((movement & zPLAYER_ROTATED_LEFT)  || (movement & zPLAYER_ROTATED_RIGHT) )
	{
		movement |= zPLAYER_ROTATED;
		movement &= ~zPLAYER_ROT_NONE;
	};

/*	if (translated || rotated)
	{
	if (standing) 
		{
			standTimer += frameTime;
			if (standTimer > 1) 
			{
				standTimer = 0;
				standing   = FALSE;
			}
		}
	}*/

};

void zCMovementTracker::Update()
{
	const  float RANGE_TO_RECOGNIZE_BEAMING	= 5 * 1000;

	if (!camVob) return;
	if (!target) return;
	
	CheckKeys		 ();

	frameTime						= ztimer.GetFrameTimeFSecs()/ztimer.GetMotionFactor();
	if (frameTime == 0)	return;

	UpdateCamPos  ( camVob->GetPositionWorld() );
	UpdateWayPoint( zWAYPOINT_CAM );

	trafoCStoWS = camVob->trafoObjToWorld;
	trafoWStoCS = zInverseMatD(trafoCStoWS,zSTRING("Update")); 

	CalcPlayerPose			();
	CalcPlayerMovements		();
	
	// Get range - velocity in m/sec
	playerVeloRange		= 1000.0F * zAbs( distToPlayer - oldDistToPlayer ) / frameTime;	

	actAzi				= GetAzimuth();
	actElev				= GetElevation();
	distToPlayer		= GetRange();

	if ( (target->GetPositionWorld()-oldSampledPlayerPos).Length() > RANGE_TO_RECOGNIZE_BEAMING ) movement |= zPLAYER_BEAMED;

	if ( movement & zPLAYER_STAND ) standing	= TRUE;
	else							standTimer  = 0;

	zREAL	farZ	= zCCamera::activeCam ? zCCamera::activeCam->GetFarClipZ() : 5000;
	zPOINT3 hPos	= playerHead + (farZ * trafoTStoWS.GetAtVector());

	camai->raysCasted++;
	if (camVob->GetHomeWorld()->TraceRayNearestHit(playerHead, hPos-playerHead, target, zTRACERAY_VOB_BBOX|standardTraceFlags)) 
	{
		POI_Player = camVob->GetHomeWorld()->traceRayReport.foundIntersection + (playerHead - camVob->GetHomeWorld()->traceRayReport.foundIntersection).NormalizeSafe();
	}
	else POI_Player = hPos;

	CalcPlayerSpline	();
	CheckSpecialMoves	();
	AutoSetMessages		();
	UpdateMessages		();

}

void zCMovementTracker::CheckKeys()
{
}

zBOOL zCMovementTracker:: CheckSpecialMoves()
{
	if ( !camVob || camVob->GetSleeping() ) return FALSE;
	if ( zCCSCamera::GetIsPlaying()		  ) return FALSE;

	if ( zCCamera::activeCam == 0 || zCCamera::activeCam->GetVob() == 0 ) return FALSE;

	if (movement & zPLAYER_BEAMED) 
	{
		SetPlayerPos		( target->GetPositionWorld() );
		CalcPlayerPose		();
		CalcPlayerMovements	();
		camai->CalcFirstPosition();

		zPOINT3 resetPos = camai->GetCamSysFirstPos();

		if ( !pathSearch->IsPointValid(resetPos,zPATHSEARCH_INCLUDE_PLAYER_CHECK ) ) 
		{
			zCPathSearch::zSPathSearchOptions searchOpts;
			searchOpts.SetDefaults();
			searchOpts.quality							= 1;
			searchOpts.poseFailReason					= zFAILREASON_PLAYER_BEAMED;
			pathSearch->FindBestEvasion(searchOpts);
			
			if (camai->evasionSearchReport->bestLerpMode == zPATH_LERP_CUSTOM)
				camai->evasionSearchReport->bestLerpMode = zPATH_LERP_CUSTOM_JUMP;
			else camai->evasionSearchReport->bestLerpMode = zPATH_LERP_JUMP;

			InterpolateTo(*camai->evasionSearchReport);
		}
		else 
		{
			zSPathSearchResult evasion;
			evasion.p1				= camVob->GetPositionWorld();
			evasion.p2				= resetPos;
			evasion.bestLerpMode	= zPATH_LERP_JUMP;
			evasion.veloTrans		= camai->veloTrans;
			evasion.veloRot			= camai->veloRot;
			evasion.r1.Matrix4ToQuat(camVob->trafoObjToWorld);

			InterpolateTo(evasion);
		}

		camai->underWater = FALSE;
		camai->CheckUnderWaterFX();
		return TRUE;
	}

	return FALSE;
}


zCQuat zCMovementTracker::GetLocalRot(const float & azi, const float & elev)
{

	zCQuat newPose;
	zPOINT3 behind = playerPos - trafoTStoWS.GetAtVector();

	zPOINT3 newPoint = ApplyAziToPoint	(azi , behind);
			newPoint = ApplyElevToPoint	(elev, newPoint );

	zMATRIX4 newTrafo = GetPoseOfHeading( newPoint, (playerPos - newPoint).NormalizeSafe());
	newPose.Matrix4ToQuat( trafoWStoTS * newTrafo );

	return newPose;
}

// zCMovementTracker::GetLocalRotEnd()
// liefert die lokale Rotation aus den günstigsten sphärischen Koordinaten in Form einer 4x4 Matrix

zMAT4 zCMovementTracker::GetLocalRotEnd()
{
	zMAT4 localRotEnd;
	if ( movement & zPLAYER_BEAMED ) 
	{
		return camVob->trafoObjToWorld;
	}
	if (GetCamPos() == GetPlayerPos())	
	{
		return GetPlayerTrafo();
	}
	else								localRotEnd = GetPoseOfHeading( GetCamPos(), (GetPlayerPos()-GetCamPos()).NormalizeSafe() );
	
	float thisRotX, thisRotY;

	// im mode normal oder run verändert ein elev offset auch die lokale rotation um die x achse
	if ( !bMouseUsed		  && 
		 camai->bestRotX != 0 && 
		(camai->GetMode() == CamModNormal || camai->GetMode() == CamModRun) )	
	{  
		thisRotX = GetElevation()/camai->bestRotX * camai->rotOffsetX; 
		thisRotX = zSign(thisRotX) * MIN( zAbs(thisRotX), zAbs(camai->rotOffsetX) );
	}	
	else
		thisRotX = camai->rotOffsetX;

	// ein azi winkel ungleich null verändert auch die lokale rotation um die Y achse
	if (camai->bestRotY != 0) 
	{
		thisRotY = GetAzimuth  ()/camai->bestRotY * camai->rotOffsetY; 
		thisRotY = zSign(thisRotY) * MIN( zAbs(thisRotY), zAbs(camai->rotOffsetY) );
	}
	else thisRotY = camai->rotOffsetY;
	
	localRotEnd = localRotEnd * Alg_Rotation3DN( zVEC3(1,0,0), -thisRotX ) ;
	localRotEnd = Alg_Rotation3DN( zVEC3(0,1,0), -thisRotY )  * localRotEnd; 
	localRotEnd = localRotEnd * Alg_Rotation3DN( zVEC3(0,0,1), -camai->rotOffsetZ) ;

	return localRotEnd;
}


void zCMovementTracker::RecalcRingPositions()
{
	numSamplesCam = (int)Lerp(inertiaTrans, 1, MAX_POS_SAMPLES_CAM);

    sampledPlayerPosRing = playerPosRing = playerPos;

//	for (int i=0; i<numPreSamplesPlayerPos; i++) posRingPreSamplesPlayerPos[i]  = playerPos;
//	for (	 i=0; i<numSamplesPlayer;		i++) posRingPlayerPos[i]			= playerPos;
//	for (    i=0; i<numSamplesCam;			i++) posRingCam	   [i]				= GetCamPosRing();
//	ringPosPreSamplesPlayerPos	=	0;
//	ringPosPlayerPos			=	0;
//	ringPosCam					=	0;
	rotPoseTargetFOR .SetInertiaRot	  (inertiaRotTargetFOR);
	headPose		 .SetInertiaRot	  (inertiaHead);
	sampledPlayerPose.SetInertiaPos	  (inertiaTargetTrans);
	sampledPlayerPose.SetInertiaRot	  (inertiaTargetRot);

}

zPOINT3& zCMovementTracker::GetLastValidWayPoint(const zTWayPoint &type)
{
	switch (type) 
	{
	case zWAYPOINT_PLAYER:
	case zWAYPOINT_HEAD:
		// gibt waypoint der mindestens zWAYPOINT_SAMPLE_TIME/2 secs. zurückliegt zurück
		if (wayTimeHead>zWAYPOINT_SAMPLE_TIME/2) 
		{
			if (actWayPointHead == 0) return wayPointHead[NUM_WAYPOINTS-1]; 
			else					  return wayPointHead[actWayPointHead-1];
		} 
		else 
		{
			if (actWayPointHead > 1)  return wayPointHead[actWayPointHead-2  ]; else
			if (actWayPointHead == 1) return wayPointHead[NUM_WAYPOINTS-1]; 
			else		  			  return wayPointHead[NUM_WAYPOINTS-2];
		}
		break;
	case zWAYPOINT_HIP_LEFT:
		// gibt waypoint der mindestens zWAYPOINT_SAMPLE_TIME/2 secs. zurückliegt zurück
		if (wayTimeHipLeft>zWAYPOINT_SAMPLE_TIME/2) 
		{
			if (actWayPointHipLeft == 0) return wayPointHipLeft[NUM_WAYPOINTS-1]; 
			else						 return wayPointHipLeft[actWayPointHipLeft-1];
		} 
		else 
		{
			if (actWayPointHipLeft > 1)  return wayPointHipLeft[actWayPointHipLeft-2  ]; else
			if (actWayPointHipLeft == 1) return wayPointHipLeft[NUM_WAYPOINTS-1]; 
			else						 return wayPointHipLeft[NUM_WAYPOINTS-2];
		}
		break;
	case zWAYPOINT_HIP_RIGHT:
		// gibt waypoint der mindestens zWAYPOINT_SAMPLE_TIME/2 secs. zurückliegt zurück
		if (wayTimeHipRight>zWAYPOINT_SAMPLE_TIME/2) 
		{
			if (actWayPointHipRight == 0) return wayPointHipRight[NUM_WAYPOINTS-1]; 
			else						  return wayPointHipRight[actWayPointHipRight-1];
		} 
		else 
		{
			if (actWayPointHipRight > 1)  return wayPointHipRight[actWayPointHipRight-2  ]; else
			if (actWayPointHipRight == 1) return wayPointHipRight[NUM_WAYPOINTS-1]; 
			else						  return wayPointHipRight[NUM_WAYPOINTS-2];
		}
		break;
	case zWAYPOINT_CAM:
		// gibt waypoint der mindestens zWAYPOINT_SAMPLE_TIME/2 secs. zurückliegt zurück
		if (wayTimeCam>zWAYPOINT_SAMPLE_TIME/2) 
		{
			if (actWayPointCam == 0) return wayPointCam[NUM_WAYPOINTS-1]; 
			else	 			     return wayPointCam[actWayPointCam-1];
		} 
		else 
		{
			if (actWayPointCam > 1)  return wayPointCam[actWayPointCam-2  ]; else
			if (actWayPointCam == 1) return wayPointCam[NUM_WAYPOINTS-1];	 
			else				     return wayPointCam[NUM_WAYPOINTS-2];
		}
		break;
	}
	zERR_ASSERT(1!=1);
	// compiler safety
	static zPOINT3 res(0,0,0); 
	return res;
}

void zCMovementTracker::UpdateWayPoint(const zTWayPoint &type)
{
	switch (type) 
	{
	case zWAYPOINT_HEAD:
	case zWAYPOINT_PLAYER:
		camai->raysCasted++;
		if (!camVob->GetHomeWorld()->TraceRayFirstHit( camPos, playerHead - camPos, target,standardTraceFlags )) 
		{
			wayTimeHead += frameTime;
			if (wayTimeHead > zWAYPOINT_SAMPLE_TIME) 
			{
				wayTimeHead = 0;
				wayPointHead[actWayPointHead++] = playerHead;
				if (actWayPointHead == NUM_WAYPOINTS) actWayPointHead = 0;
			}
		}
		camai->raysCasted++;
		if (!camVob->GetHomeWorld()->TraceRayFirstHit( camPos, playerHipLeft - camPos, target, standardTraceFlags)) 
		{
			wayTimeHipLeft += frameTime;
			if (wayTimeHipLeft > zWAYPOINT_SAMPLE_TIME) 
			{
				wayTimeHipLeft = 0;
				wayPointHipLeft[actWayPointHipLeft++] = playerHipLeft;
				if (actWayPointHipLeft == NUM_WAYPOINTS) actWayPointHipLeft = 0;
			}
		}
		camai->raysCasted++;
		if (!camVob->GetHomeWorld()->TraceRayFirstHit( camPos, playerHipRight - camPos, target, standardTraceFlags)) 
		{
			wayTimeHipRight += frameTime;
			if (wayTimeHipRight > zWAYPOINT_SAMPLE_TIME) 
			{
				wayTimeHipRight = 0;
				wayPointHipRight[actWayPointHipRight++] = playerHipRight;
				if (actWayPointHipRight == NUM_WAYPOINTS) actWayPointHipRight = 0;
			}
		}
		break;
	case zWAYPOINT_CAM:
		// @@@ Wann tritt diese Bedingung ein ? Wann ist der Punkt ungültig ?
		if ( pathSearch->IsPointValid(camPos, zPATHSEARCH_INCLUDE_PLAYER_CHECK|zPATHSEARCH_INCLUDE_NEARWALL_CHECK) )
		{
			wayTimeCam += frameTime;
			if (wayTimeCam > zWAYPOINT_SAMPLE_TIME) 
			{
				wayTimeCam = 0;
				wayPointCam [actWayPointCam++] = camPos;
				if (actWayPointCam == NUM_WAYPOINTS) actWayPointCam = 0;
			}
		}
		break;
	}


}

void zCMovementTracker::ResetWayPoints(const zPOINT3 &fillPos, const zTWayPoint &type)
{
	int i;
	switch (type) 
	{
	case zWAYPOINT_PLAYER: 
		wayTimeHead			= 0;
		wayTimeHipLeft		= 0;
		wayTimeHipRight		= 0;
		actWayPointHead		= 0;
		actWayPointHipLeft	= 0;
		actWayPointHipRight = 0;
		for (i=0; i<NUM_WAYPOINTS; i++) wayPointHead	[i]=fillPos;
		for (i=0; i<NUM_WAYPOINTS; i++) wayPointHipLeft [i]=fillPos;
		for (i=0; i<NUM_WAYPOINTS; i++) wayPointHipRight[i]=fillPos;
		break;
	case zWAYPOINT_CAM: 
		wayTimeCam		= 0;
		actWayPointCam	= 0;
		for (i=0; i<NUM_WAYPOINTS; i++) wayPointCam		[i]=fillPos;
		break;

	}
}

void zCMovementTracker :: InterpolateTo(const zSPathSearchResult &lerpDesc)
{
	const float MAX_DIST_MAX_INERTIA = 5;

	zSPathSearchResult moveDesc = lerpDesc;

	if (moveDesc.p1 != moveDesc.p2)
	if (moveDesc.bestLerpMode == zPATH_LERP_LINE)
	{
		if (!pathSearch->LineOfSight(moveDesc.p1,moveDesc.p2))
		{
			//zERR_WARNING("C: no LOS p1 to p2");
			zPOINT3 twp = GetLastValidWayPoint(zCMovementTracker::zWAYPOINT_PLAYER);

			if (pathSearch->LineOfSight(GetPlayerHead(),moveDesc.p1) && 
				pathSearch->LineOfSight(GetPlayerHead(),moveDesc.p2)
				)
			{
				//zERR_WARNING("C: easing to head");
				moveDesc.p2 = GetPlayerHead();
			}
			else if (pathSearch->LineOfSight(GetPlayerPos(),moveDesc.p1) && 
				     pathSearch->LineOfSight(GetPlayerPos(),moveDesc.p2))
			{
				//zERR_WARNING("C: easíng to player");
				moveDesc.p2 = GetPlayerPos();
			}
			else if (pathSearch->LineOfSight(twp,moveDesc.p1) && 
				     pathSearch->LineOfSight(twp,moveDesc.p2))
			{
				//zERR_WARNING("C: easíng to wp player");
				moveDesc.p2 = twp;
			}
			else 
			{
				moveDesc.bestLerpMode = zPATH_LERP_JUMP;
				//zERR_WARNING("C: switch to p2");
			}
		}
		else if (!pathSearch->LineOfSight(GetPlayerPos(),moveDesc.p2))		// FIXME: darf eigentlich nicht eintreten
		{
			//zERR_WARNING("C: no LOS player to p2");
			zPOINT3 twp = GetLastValidWayPoint(zCMovementTracker::zWAYPOINT_PLAYER);
			if (pathSearch->LineOfSight(moveDesc.p1,twp) && 
				pathSearch->LineOfSight(twp,moveDesc.p2))
			{
				//zERR_WARNING("C: easíng to wp head");
				moveDesc.p2 = twp;
			}
			else if (pathSearch->LineOfSight(moveDesc.p1,GetPlayerPos()) && 
					 pathSearch->LineOfSight(GetPlayerPos(),moveDesc.p2))
			{
				//zERR_WARNING("C: easíng to player");
				moveDesc.p2 = GetPlayerPos();
			}
			else 
			{
				//zERR_WARNING("C: jump to head");
				moveDesc.p2			  = GetPlayerHead();
				moveDesc.bestLerpMode = zPATH_LERP_JUMP;
			};
		}
	}

	zPOINT3 newPosition;
	zMAT4   newTrafo		= Alg_Identity3D();

	zBOOL switchMode = ( moveDesc.bestLerpMode == zPATH_LERP_JUMP || moveDesc.bestLerpMode == zPATH_LERP_CUSTOM_JUMP ) ? TRUE : FALSE;
	//if (switchMode) zERR_WARNING("C: switchMode");
	//zERR_WARNING("C: length of evasion: " + zSTRING((moveDesc.p2-moveDesc.p1).Length()));

	// obergrenze für die distanz zum kopf festsetzen
	if (!switchMode)
	if (bMouseUsed)
	if ( (moveDesc.p2-moveDesc.p1).Length()>250 )
	{
		moveDesc.p2 = moveDesc.p1 + (250 * (moveDesc.p2-moveDesc.p1).Normalize());
	}
	//
	// Translation
	// 
	// TODO: distanz abhängiger easeTime scale faktor
	zBOOL playerVisible = pathSearch->LineOfSight(moveDesc.p1,playerPos);
	//zBOOL bestPosValid	= pathSearch->LineOfSight(playerPos, camai->GetCamSysFirstPos());

	float distScale;

	zREAL actDistance = (moveDesc.p1 - moveDesc.p2).Length()/100;
	zClamp(actDistance,0.0F, MAX_DIST_MAX_INERTIA);		// FIXME: dirty
	zREAL inertiaScale= actDistance/MAX_DIST_MAX_INERTIA;
	zREAL distScale2  = zLerp(inertiaScale,0.3f ,1.0f);
	zClamp01(inertiaScale);

	/*if (!bestPosValid) {
		zREAL distToIdealRangeNow, distToIdealRange;
		zVEC3 camPosBak = camPos;
		camPos = moveDesc.p2;
		distToIdealRangeNow = GetDistToIdealRange();
		camPos = camPosBak;
		if (distToIdealRangeNow>0.1f) 
		{
			zREAL distScale3 = (GetDistToIdealRange()/distToIdealRangeNow)+0.1f;
			zClamp01(distScale3);
			
			distScale2 *= zSinusEase(distScale3);
		}
	}*/

	if (playerVisible) 
	{
		if (bMouseUsed || camai->GetMode()==CamModFirstPerson)	
		{
			zREAL sensX, sensY;
			zinput->GetMouseSensitivity(sensX, sensY);

			distScale = moveDesc.veloTrans * sensX * distScale2;
		}
		else if ( (camai->GetMode()==CamModMelee) ||  (camai->GetMode()==CamModMagic) )	
		{
			distScale = Lerp( inertiaScale,moveDesc.veloTrans,MAX(10,moveDesc.veloTrans+20));
			if (!bMouseUsed) distScale *=2;
		}
		else 
		{
			distScale = Lerp( inertiaScale,moveDesc.veloTrans,MAX(10,moveDesc.veloTrans));
			if (!bMouseUsed) distScale *=2;
		}
	}
	else
	{
		if (bMouseUsed || camai->GetMode()==CamModFirstPerson)	
		{
			zREAL sensX, sensY;
			zinput->GetMouseSensitivity(sensX, sensY);
			distScale = moveDesc.veloTrans * sensX * distScale2;
		}
		else
		{
			distScale = Lerp( inertiaScale,moveDesc.veloTrans,MIN(30,moveDesc.veloTrans+10));
			if (!bMouseUsed) distScale *=3;
		}
	}

	float easeTime =  distScale * frameTime;
	if (switchMode) easeTime = 1; else zClamp01(easeTime);

	if (switchMode)		 SetCamPos	 ( moveDesc.p2 );
	else if (bMouseUsed || camai->GetMode()==CamModFirstPerson) 
	{
		//zVEC3 moveVec = easeTime * (moveDesc.p2-moveDesc.p1);
		//SetCamPos(GetCamPos()+moveVec);
		SetCamPos	 ( Lerp( easeTime, moveDesc.p1, moveDesc.p2 ) );
	}
	else	
	{
		zPOINT3 newPos = Lerp( easeTime, moveDesc.p1, moveDesc.p2 );
		UpdateCamPos( newPos );
		zPOINT3 camRing = GetCamPosRing();
		pathSearch->AdjustCenterSphere(camRing, newPos);
		SetCamPos(camRing);
	}

	//zERR_WARNING("C: distScale: " + zSTRING(distScale));

	if (!camVob) return;

	zMATRIX4 localCStoTS = camVob->trafoObjToWorld;
	localCStoTS.SetTranslation(GetCamPosRing());
	localCStoTS = GetPlayerTrafoInv() * localCStoTS;
	zPOINT3 localCoords = localCStoTS.GetTranslation();

	rotPoseTargetFOR.UpdateRot(localCStoTS);
	rotPoseTargetFOR.GetPose(localCStoTS);
	localCStoTS.SetTranslation(localCoords);
	localCStoTS = trafoTStoWS * localCStoTS;

	// ACHTUNG: hier wird die absolute Position auf die Ringbuffer Position gesetzt
	camPos		= GetCamPosRing();	
	
	pathSearch->CorrectPosForNearClip(camPos);

	// @@@if (!AI_PointIsValid(newPos)) pathSearch->AdjustCenterSphere(newPos,movePos);
	//
	// Rotation 
	// 
	easeTime = moveDesc.veloRot * frameTime;
	if (switchMode) easeTime = 1;
	else			zClamp01(easeTime);

	// rotation aus der moveDescription nehmen ?
	if (moveDesc.bestLerpMode == zPATH_LERP_CUSTOM	|| moveDesc.bestLerpMode == zPATH_LERP_CUSTOM_JUMP) 
	{
		zCQuat startRot,endRot,actRot;

		startRot				.Matrix4ToQuat	(camVob->trafoObjToWorld);
		actRot					.Slerp			(easeTime,startRot,moveDesc.r2);
		headPose				.UpdateRot		(actRot);
		zMAT4 newMatrix	= Alg_Identity3D();
		headPose				.GetPose		(newMatrix);
		newMatrix.SetTranslation(GetCamPos());

		zVEC3 right = newMatrix.GetRightVector();	right[VY]   = 0; right.NormalizeSafe();
		newMatrix.SetRightVector	(right);
		newMatrix.SetUpVector		(newMatrix.GetAtVector()^right);
		if (newMatrix.GetUpVector()[VY] < 0) newMatrix.SetUpVector(-newMatrix.GetUpVector());

		newMatrix.MakeOrthonormal	();
		camVob->SetTrafo			(newMatrix);
	}
	else 
	{
		// default rotation zum playerPos mit gegebenen lokalen offset winkeln
		zCQuat startHeadRot;

		if (GetCamPos() == GetPlayerPos()) startHeadRot.Matrix4ToQuat(GetPlayerTrafo());			
		else startHeadRot.Matrix4ToQuat( GetPoseOfHeading( GetCamPos(), (GetPlayerPos()-GetCamPos()).Normalize()) * oldTrafoRotOffsetWStoCS );

		// FIXME: mir obiger zeile rotiert man immer von der lokalen camera rotation ohne offsetwinkel zur 
		// idealen rotation mit offset winkeln. allerdings scheint es nicht zu funzen, wenn easeTime recht klein
		// gewählt ist: ruckeln
		// untere Zeile funzt, ist aber visuell "schwammig", da - wenn einmal die ideal rotation inkl offsetwinkel
		// erreicht wurde, trotzdem permanent zu dieser idealrotation gestrebt wird. 

		//zMAT4 oldTrafoCStoWS = oldTrafoWStoCS.InverseLinTrafo();
		//startHeadRot.Matrix4ToQuat(trafoTStoWS * oldTrafoWStoTS * oldTrafoCStoWS);

		zCQuat endHeadRot;
		endHeadRot.Matrix4ToQuat(GetLocalRotEnd());

		// FIXME: Wieso ist das nötig ?
		startHeadRot.Unit();
		endHeadRot	.Unit();

		actRot.Slerp( easeTime, startHeadRot, endHeadRot );
		actRot.Unit	();

		// trägheitsdämpfer aktivieren
		zMAT4 actRotTrafo = Alg_Identity3D();
		headPose.UpdateRot	( actRot );
		headPose.GetPose	( actRotTrafo );

		//actRotTrafo = trafoTStoWS * actRotTrafo;
		if (camai->GetMode()==CamModFirstPerson)
		{
			actRotTrafo = target->trafoObjToWorld;
		}

		actRotTrafo.SetTranslation(GetCamPos());
		zVEC3 right = actRotTrafo.GetRightVector(); 	right[VY]   = 0; right.NormalizeSafe();

		actRotTrafo.SetRightVector(right);
		actRotTrafo.SetUpVector(actRotTrafo.GetAtVector()^right);
		if (actRotTrafo.GetUpVector()[VY] < 0) actRotTrafo.SetUpVector(-actRotTrafo.GetUpVector());

		actRotTrafo.MakeOrthonormal();
		camVob->SetTrafo			( actRotTrafo );
	}

	if (camai->GetMode()==CamModFirstPerson) 
	{
		camVob->RotateLocalX(camai->rotOffsetX);
	}
}

/* ----------------------------------------------------------------------
	
    zCMovementTracker::CalcPlayerSpline()	

	26.08.2000	[Moos]	

                fixed leak

   ---------------------------------------------------------------------- */


void zCMovementTracker::CalcPlayerSpline() 
{
	const int MAX_zPLAYER_KEYFRAMES = 50;
	
	static int frame = 0;
	if (frame++%2) return;

	if (targetKFList.GetNumInList() > MAX_zPLAYER_KEYFRAMES ) 
	{
        zCPositionKey *delkey=targetKFList[0];
		targetKFList.RemoveOrder(delkey);
        delete delkey;            // [Moos] get rid of it
		for (int i=0; i<targetKFList.GetNumInList(); i++) targetKFList[i]->SetTime(float(i));
	}
	zCPositionKey *key = zNEW( zCPositionKey );
	key->SetPosition	(GetShoulderCamMat().GetTranslation());
	key->SetTime		(float(targetKFList.GetNumInList()));
	targetKFList.Insert(key);

/*	if (targetKFList.GetNumInList()>=4) {
		zCKBSpline spl(targetKFList);
		spl.Draw(GFX_RED);
	}*/
};


zMAT4& zCMovementTracker:: GetFirstPersonCamMat() 
{
	zCModel *model = dynamic_cast<zCModel*>(target->GetVisual());
	
	if (model) 
	{
		// erst mal sehen, obs nen first person node in dem model gibt
		zCModelNodeInst* camFP = model->SearchNode("ZS_FPCAM");
		if (camFP) 
		{
			static zMAT4 trafoFP = Alg_Identity3D();
				
			trafoFP = target->GetTrafoModelNodeToWorld(camFP);			
			trafoFP.PostRotateZ(-90);
			zPOINT3 p(playerHead[VX],trafoFP.GetTranslation()[VY],playerHead[VZ]);
			pathSearch->AdjustCenterSphere(p,playerPos);
			trafoFP.SetTranslation(p);
			return trafoFP;
		}
	}

	// nope, kein FP Node, also manuell ermitteln
	// (FIXME: BBox Grösse berücksichtigen)
	zPOINT3 p(playerHead[VX],playerHead[VY],playerHead[VZ]);
	return GetPoseOfHeading(p, trafoTStoWS.GetAtVector());
};

zMAT4& zCMovementTracker::GetPanicCamMat()
{
	static zMAT4 resMat = Alg_Identity3D();
	resMat = GetLocalRotEnd();
	return GetPoseOfHeading(GetCamPosRing(), (trafoTStoWS.GetAtVector()+zVEC3(0,resMat.GetAtVector()[VY],0)).NormalizeApprox()); 
};

zMAT4& zCMovementTracker::GetShoulderCamMat()
{
	zPOINT3 shoulderPos	= camai->CalcAziElevRange(SHOULDERCAM_AZI,SHOULDERCAM_ELEV,SHOULDERCAM_RANGE+camai->GetNpcDistOffset(),GetPlayerTrafo());
	zPOINT3 lookPos		= GetPlayerPos() + 
						  SHOULDERCAM_FOCUS_OFFSET_AT * GetPlayerAtVector() + 
						  SHOULDERCAM_FOCUS_OFFSET_UP * zVEC3(0,1,0);

	return GetPoseOfHeading(shoulderPos, (lookPos-shoulderPos).NormalizeSafe());
};

zPOINT3& zCMovementTracker::CalcAziElevRangeApprox(const float &aziDeg,const float &elevDeg,const float &range)
{
	const zREAL	FAK = float(M_PI * ((1.0) / 180.0));
    const zREAL azi = (180-aziDeg)  * FAK;
    const zREAL elev= (elevDeg+360) * FAK;
	static zPOINT3 resultPoint;
	zREAL fsin, fcos;

	//						  ->  ->           ->            ->
	// Setup circle in Space. x = m + r*cos(b)*u0 + r*sin(b)*v0
	zVEC3 u0 = trafoTStoWS.GetAtVector();;
	zVEC3 v0 = trafoTStoWS.GetRightVector();

	u0[VY]=0.0F; v0[VY]=0.0F;  // hier nicht mehr nötig ?
	u0.NormalizeSafe(); v0.NormalizeSafe();

	// get new azimuth position on circle
	zSinCosApprox(azi, fsin, fcos);

	resultPoint	=  playerPos +  (range * fcos) * u0 + 
								(range * fsin) * v0 ;

	// find u0 and v0 for elevation circle 
	resultPoint[VY] = playerPos[VY];
	u0 = (resultPoint-playerPos).NormalizeSafe();

	// Get orthogonal up (=v0) vec. from new target at-vec.
	v0 = zPOINT3 (0,1,0);
	v0 = (v0 - ((v0 * u0) * u0)).NormalizeSafe(); // nötig ???

	zSinCosApprox(elev, fsin, fcos);
	// get new elevation position on circle
	resultPoint =   playerPos + (range * fcos) * u0 + 
								(range * fsin) * v0 ;

	return resultPoint;
}


void zCMovementTracker::SetRotateEnabled(zBOOL r)
{
	if (rotate == r) return;
	zERR_MESSAGE(10,0,"C: zCMovementTracker::SetRotateEnabled() rotateflag changed: " + zSTRING(r));
	initialPoseRotFreeze	= trafoTStoWS;
	rotate					= r;
};


void zCMovementTracker::SaveFrameStates()
{
	oldPlayerPosMovement		= playerPosMovement;
	oldSampledPlayerPosRing		= GetSampledPlayerPosRing();
	oldPlayerPos				= playerPos;
	oldSampledPlayerPos			= sampledPlayerPos;
	oldTrafoWStoTS				= trafoWStoTS;
	oldCamPos					= camPos; 
	oldDistToPlayer				= GetRange();		// äh, distToPlayer ?
	oldElev						= GetElevation();   // wie jetzt ? Vor oder nach dem cam-trafo?
	oldAzi						= GetAzimuth();
	camPos						= camVob->GetPositionWorld();
	if ((playerPos-camVob->GetPositionWorld()).Length() == 0 || camai->GetMode()==CamModFirstPerson || (movement&zPLAYER_BEAMED) ) oldTrafoRotOffsetWStoCS=Alg_Identity3D(); else
	oldTrafoRotOffsetWStoCS		= GetPoseOfHeading( camVob->GetPositionWorld(), (playerPos-camVob->GetPositionWorld()).NormalizeSafe() ).Inverse() * camVob->trafoObjToWorld;
	oldTrafoWStoCS				= camVob->trafoObjToWorld.Inverse();

	// safety: falls irgendwo die Matrix zerhauen wurde, wird hier die letzte gültige genommen
	if (!CheckMatrixConsistency( camVob->trafoObjToWorld ) ) 
	{ 
		zERR_WARNING("C: zAICamera.cpp(zCAICamera::DoAI):Matrix-inconsistency!");
		camVob->SetTrafo			( lastValidCamTrafo );
	} 
	else lastValidCamTrafo = camVob->trafoObjToWorld;

	ClearMessages		();
}


void zCMovementTracker::TargetChanged()
{
	target = camai->target;

	playerPosMovement			= zVEC3(0,0,0);
	playerPosMovementRing		= zVEC3(0,0,0);
	playerPosMovementLocal		= zVEC3(0,0,0);
	playerPosMovementLocalCam	= zVEC3(0,0,0);

	if (!target) return;
	
	SetPlayerPos			( target->GetPositionWorld() );
	Update					();
};

void zCMovementTracker::CamVobChanged()
{
	camVob = camai->camVob;
	if (!camVob) return;
	SetCamPos( camVob->GetPositionWorld() );
	Update	 ();
}

// zCMovementTracker::UpdateSampledPlayerPos
// sampled die absolute Spieler Positionen alle n msec, damit Geschwindigkeitsschwankungen innerhalb
// von Animationen weniger auf die Camera übertragen werden
void zCMovementTracker::UpdateSampledPlayerPos(const zPOINT3 &p)
{
    zREAL dist2 = (p - sampledPlayerPosRing).Length2() / 100000;

    zREAL frac = frameTime / (numPreSamplesPlayerPos * averageFrameTime);
    frac      *= (1 + 4 * dist2) / (1 + dist2);

	if (movement & zPLAYER_BEAMED || camai->GetMode() == CamModFirstPerson ) 
	{
		sampledPlayerPosRing = p;	
	} 
    else
    {
        sampledPlayerPosRing += p * frac;
        sampledPlayerPosRing /= (1 + frac);
    }

//	zPOINT3 avg = posRingPreSamplesPlayerPos[0];

	sampledPlayerPos								  = p;  // absolute coord
//	sampledPlayerPosRing							  = avg;

}

/*
void zCMovementTracker::UpdateSampledPlayerPos(const zPOINT3 &p)
{
	const  float sampleTime = 0.1F;
	static float time		= 0 ;
	zPOINT3 newPos;

	time += frameTime;
	if ( (time >= sampleTime) || (movement & zPLAYER_BEAMED) ) 
	{
		time   = 0;
		newPos = p;	
	} 
	else newPos = oldSampledPlayerPos;

	zPOINT3 avg = zPOINT3(0,0,0);

	posRingPreSamplesPlayerPos[ringPosPreSamplesPlayerPos++] = newPos;
	if ( ringPosPreSamplesPlayerPos == numPreSamplesPlayerPos ) ringPosPreSamplesPlayerPos = 0;

	for (int i=0; i<numPreSamplesPlayerPos; i++) avg += posRingPreSamplesPlayerPos[i];
	avg												 /= (float)numPreSamplesPlayerPos;
	sampledPlayerPos								  = newPos;  // absolute coord
	sampledPlayerPosRing							  = avg;

}
*/

void zCMovementTracker::SetSampledPlayerPos(const zPOINT3 &newTarget)
{
    sampledPlayerPos = sampledPlayerPos = newTarget;
//	for (int i=0; i<numPreSamplesPlayerPos; i++) posRingPreSamplesPlayerPos[i]=newTarget;
//	UpdateSampledPlayerPos(newTarget);
}

zPOINT3& zCMovementTracker::GetPlayerFuturePos(const float advanceTimeSec) 			
{ 
	static zPOINT3 newPos;
	newPos = sampledPlayerPos + ((playerPosMovementRing/frameTime) * advanceTimeSec);
	// FIXME: LineofSight benutzt TraceRayFirstHit!!!
	if ( pathSearch->LineOfSight( newPos, GetPlayerPos() ) ) return newPos;
	else													 return (camVob->GetHomeWorld()->traceRayReport.foundIntersection);
};
