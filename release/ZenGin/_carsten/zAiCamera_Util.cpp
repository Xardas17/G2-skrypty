#include "zcore.h"
#include "ztypes3d.h"
#include "zkbsplines.h"
#include "zvob.h"
#include "zworld.h"
#include "zsky.h"
#include "zAICamera.h"
#include "zAICamera_Movement.h"
#include "zAICamera_Core.h"
#include "zAIPlayer.h"
#include "zVob.h"
#include "zDbgTools.h"

#ifdef DEBUG_EDENFELD
#endif

static void Alg_ClipAtZ1(zPOINT3 &a,zPOINT3 &b)
{
	if ( a[VZ] < 1) 
	{
		if ( b[VZ] < 1) return;
		float t = (1-a[VZ]) / (b[VZ]-a[VZ]);
		a[VX] = a[VX] + t*(b[VX]-a[VX]);
		a[VY] = a[VY] + t*(b[VY]-a[VY]);
		a[VZ] = 1;
	}
	else if ( b[VZ] < 1) 
	{
		float t = (1-a[VZ]) / (b[VZ]-a[VZ]);
		b[VX] = a[VX] + t*(b[VX]-a[VX]);
		b[VY] = a[VY] + t*(b[VY]-a[VY]);
		b[VZ] = 1;
	}

}


void zCAICamera :: InitHelperVobs()
{
	if (!focusVob) focusVob = zNEW(zCVob());

	focusVob->SetSleeping			(FALSE);
	focusVob->SetVisual				("itfo_booze_01.3ds");
	focusVob->SetPhysicsEnabled		(FALSE);
	focusVob->SetCollDet			(FALSE);
	focusVob->SetIgnoredByTraceRay	(TRUE);
	focusVob->SetTrafo				(moveTracker->GetPlayerTrafo());
	camVob->GetHomeWorld()->AddVob		(focusVob);

	for (int i=0; i<MAX_CTRL_VOBS; i++) 
	{
		ctrlDot[i] = zNEW( zCVob );

		ctrlDot[i]->SetSleeping			(FALSE);
		ctrlDot[i]->SetVisual			("itfo_apple_01.3ds");
		ctrlDot[i]->SetPhysicsEnabled	(FALSE);
		ctrlDot[i]->SetCollDet			(FALSE);
		ctrlDot[i]->SetIgnoredByTraceRay(TRUE);
		ctrlDot[i]->SetDontWriteIntoArchive(TRUE);
		ctrlDot[i]->SetDrawBBox3D		(FALSE);
		ctrlDot[i]->SetShowVisual		(TRUE);
		ctrlDot[i]->SetTrafo			(moveTracker->GetPlayerTrafo());

		camVob->GetHomeWorld()->AddVob		(ctrlDot[i]);
	}
	
}

void zCAICamera::DeleteHelperVobs()
{
	camVob->GetHomeWorld()->RemoveVob(focusVob);

	for (int i=0; i<MAX_CTRL_VOBS; i++) 
	{
		camVob->GetHomeWorld()->RemoveVob(ctrlDot[i]);
		zRELEASE(ctrlDot[i]);
	}

}
void zCAICamera::ShowDebug()
{
	focusVob->SetTrafo( moveTracker->GetPlayerTrafo() );

	ctrlDot[0]->SetPositionWorld(moveTracker->GetPlayerHipLeft());
	ctrlDot[1]->SetPositionWorld(moveTracker->GetPlayerHipRight());
	ctrlDot[2]->SetPositionWorld(moveTracker->GetPlayerHead());	
	ctrlDot[3]->SetPositionWorld(moveTracker->GetLastValidWayPoint(zCMovementTracker::zWAYPOINT_PLAYER));

	zSTRING s  = zSTRING("PlayerPos : ") + 
				 zSTRING(moveTracker->GetPlayerPos()[VX]) + zSTRING(" ") +
				 zSTRING(moveTracker->GetPlayerPos()[VY]) + zSTRING(" ") +
				 zSTRING(moveTracker->GetPlayerPos()[VZ]) + zSTRING("\n");

	zSTRING s2 =zSTRING("target velo     : ")+zSTRING(moveTracker->GetPlayerRangeVelo())	+ zSTRING("\n");
	zSTRING s5 =zSTRING("Range To Player : ")+zSTRING(moveTracker->GetRange())			+ zSTRING("\n");
	
	zSTRING s6,s7,s8,s9,s10,s11,s12,s13,s14 ;
	if (moveTracker->GetPlayerMovement() & zPLAYER_STAND) s6 = zSTRING("TARGET_STAND") + zSTRING("\n");
	else 
	{																	
		if		(moveTracker->GetPlayerMovement() & zPLAYER_MOVED_LEFT)		s6 = zSTRING("TARGET_MOVED_LEFT");
		else if (moveTracker->GetPlayerMovement() & zPLAYER_MOVED_RIGHT)	s6 = zSTRING("TARGET_MOVED_RIGHT");
		if		(moveTracker->GetPlayerMovement() & zPLAYER_MOVED_FORWARD)	
		{
			if (!s6.IsEmpty()) s6+= " | ";
			s6 += zSTRING("TARGET_MOVED_FORWARD");
		}
		else if (moveTracker->GetPlayerMovement() & zPLAYER_MOVED_BACKWARD)	
		{
			if (!s6.IsEmpty()) s6+= " | ";
			s6 += zSTRING("TARGET_MOVED_BACKWARD");
		}

		if (moveTracker->GetPlayerMovement() & zPLAYER_MOVED_UP)	
		{
			if (!s6.IsEmpty()) s6+= " | ";
			s6 += zSTRING("TARGET_MOVED_UP");
		}
		else if (moveTracker->GetPlayerMovement() & zPLAYER_MOVED_DOWN)	
		{
			if (!s6.IsEmpty()) s6+= " | ";
			s6 += zSTRING("TARGET_MOVED_DOWN");
		};
	}

	if		(moveTracker->GetPlayerMovement() & zPLAYER_ROT_NONE)		s7 = zSTRING("TARGET_ROT_NONE") + zSTRING("\n");
	else if (moveTracker->GetPlayerMovement() & zPLAYER_ROTATED_LEFT)  	s7 = zSTRING("TARGET_ROTATED_LEFT")  + zSTRING("\n");
	else if (moveTracker->GetPlayerMovement() & zPLAYER_ROTATED_RIGHT) 	s7 = zSTRING("TARGET_ROTATED_RIGHT")  + zSTRING("\n");

	s9  =zSTRING(" Azimuth   : ") + zSTRING( moveTracker->GetAzimuth() );
	s10 =zSTRING(" Elevation : ") + zSTRING( moveTracker->GetElevation() );

	if		(moveTracker->GetRange() > GetMaxRange()*100) s11 =  zSTRING("Player out of maxRange\n");
	else if (moveTracker->GetRange() < GetMinRange()*100) s11 =  zSTRING("Player out of minRange\n");
	else											 s11 =  zSTRING("Player in Range\n");


	if  (pathSearch->IsPointValid( camVob->GetPositionWorld(),zPATHSEARCH_INCLUDE_PLAYER_CHECK ))	
			s12 =  zSTRING("CamPos valid\n"); 
	else	s12 =  zSTRING("CamPos not valid\n");

	s13 = zSTRING("NPC/focus count:\n")+zSTRING(numTargets); 
	s14 = zSTRING("ModeName:"+GetMode());
	zSTRING s17 = zSTRING("Rays casted:") + zSTRING(raysCasted);

	screen->Print (0,3000,s);
	screen->Print (0,3300,s2);
	//screen->Print (0,3600,s3);
	//screen->Print (0,3900,s4);
	screen->Print (0,4200,s5);
	screen->Print (0,4500,s6);
	screen->Print (0,4800,s7);
	screen->Print (0,5100,s8);
	screen->Print (0,5400,s9);
	screen->Print (0,5700,s10);
	screen->Print (0,6000,s11);
	screen->Print (0,6300,s12);
	screen->Print (0,6600,s13);
	screen->Print (0,6900,s14);

	screen->Print (0,2700,s17);
}

void zCAICamera::DrawClipLine(const zPOINT3 &a,const zPOINT3 &b,const zCOLOR col)
{
	if (!showDebug) return;
	zPOINT3 csPoint1, csPoint2;	// world/camera-space
	zPOINT2 ssPoint1, ssPoint2;						// screen-space X,Y
	
	csPoint1 = zCCamera::activeCam->Transform (a);
	csPoint2 = zCCamera::activeCam->Transform (b);

	Alg_ClipAtZ1(csPoint1,csPoint2);

	if ( csPoint1[VZ] < 1 || csPoint1[VZ] < 1 ) return;

	zCCamera::activeCam->Project (&csPoint1, ssPoint1[VX], ssPoint1[VY]);
	zCCamera::activeCam->Project (&csPoint2, ssPoint2[VX], ssPoint2[VY]);

	int x1 = (int)ssPoint1[VX];
	int y1 = (int)ssPoint1[VY];
	int x2 = (int)ssPoint2[VX];
	int y2 = (int)ssPoint2[VY];	
	
	if (!screen->ClipLine(x1,y1,x2,y2)) return;
	
	zrenderer -> DrawLineZ	((float)x1,(float)y1,(float)1/csPoint1[VZ],(float)x2,(float)y2,(float)1/csPoint2[VZ],col);
}



/* --------------------------------------------------------------------------------
 FUNCTION: CalcMinimumBSphere
 DESCR: calculates bounding sphere out of a arbitary points set
        see Graphic Gems 1
 PARAM: pointer to step, num_steps
 ORIG:  Jack Ritter and Lyle Rains.
 --------------------------------------------------------------------------------  */
zTBSphere3D zCAICamera::CalcMinimumBSphere(zCArray<zPOINT3>&pointList)
{
	zTBSphere3D res;
	#define BIGNUMBER 100000000.0  		// hundred million

	// These are used as input and output parameters.
	int i;
	zPOINT3 caller_p,cen;
	zPOINT3 xmin,xmax,ymin,ymax,zmin,zmax,dia1,dia2;
	float rad;
	float dx,dy,dz;
	float rad_sq,xspan,yspan,zspan,maxspan;
	float old_to_p,old_to_p_sq,old_to_new;

	// FIRST PASS: find 6 minima/maxima points 
	// initialize for min/max compare 
	xmin[VX] = ymin[VY] = zmin[VZ] = BIGNUMBER; 
	xmax[VX] = ymax[VY] = zmax[VZ] = -BIGNUMBER;

	for (i=0;i<pointList.GetNumInList();i++) 
	{
		caller_p=pointList[i]; /* load global struct caller_p with */
         				/* his ith point. */
		if ( caller_p[VX] < xmin[VX] ) xmin = caller_p; /* New xminimum point */
		if ( caller_p[VX] > xmax[VX] ) xmax = caller_p;
		if ( caller_p[VY] < ymin[VY] ) ymin = caller_p;
		if ( caller_p[VY] > ymax[VY] ) ymax = caller_p;
		if ( caller_p[VZ] < zmin[VZ] ) zmin = caller_p;
		if ( caller_p[VZ] > zmax[VZ] ) zmax = caller_p;
	}

	// Set xspan = distance between the 2 points xmin & xmax (squared) 
	dx = xmax[VX] - xmin[VX];
	dy = xmax[VY] - xmin[VY];
	dz = xmax[VZ] - xmin[VZ];
	xspan = dx*dx + dy*dy + dz*dz;

	// Same for y & z spans 
	dx = ymax[VX] - ymin[VX];
	dy = ymax[VY] - ymin[VY];
	dz = ymax[VZ] - ymin[VZ];

	yspan = dx*dx + dy*dy + dz*dz;

	dx = zmax[VX] - zmin[VX];
	dy = zmax[VY] - zmin[VY];
	dz = zmax[VZ] - zmin[VZ];
	zspan = dx*dx + dy*dy + dz*dz;

	// Set points dia1 & dia2 to the maximally seperated pair 
	dia1 = xmin; dia2 = xmax; // assume xspan biggest 
	maxspan = xspan;

	if ( yspan>maxspan ) 
	{
		maxspan = yspan;
		dia1	= ymin; 
		dia2	= ymax;
	}
	if ( zspan>maxspan ) 
	{
		dia1	= zmin; 
		dia2	= zmax;
	}

	// dia1,dia2 is a diameter of initial sphere 
	// calc initial center 
	cen = 0.5F*(dia1+dia2);

	// calculate initial radius² and radius 
	dx = dia2[VX]-cen[VX]; // x componant of radius vector 
	dy = dia2[VY]-cen[VY]; // y componant of radius vector 
	dz = dia2[VZ]-cen[VZ]; // z componant of radius vector 

	rad_sq = dx*dx + dy*dy + dz*dz;
	rad = (float)sqrt(rad_sq);

	// SECOND PASS: increment current sphere 

	for ( i=0; i < pointList.GetNumInList(); i++ ) 
	{
		caller_p = pointList[i]; // load global struct caller_p with 
   												   // with his ith point.
		dx = caller_p[VX]-cen[VX];
		dy = caller_p[VY]-cen[VY];
		dz = caller_p[VZ]-cen[VZ];
		old_to_p_sq = dx*dx + dy*dy + dz*dz;

		if (old_to_p_sq > rad_sq) 
		{	
			// do r² test first 
			// this point is outside of current sphere 
			old_to_p = (float)sqrt(old_to_p_sq);
			// calc radius of new sphere 
			rad = (rad + old_to_p) * 0.5F;
			rad_sq = rad*rad; 	// for next r² compare 
			old_to_new = old_to_p - rad;
			// calc center of new sphere 
			cen = (rad * cen + old_to_new * caller_p) / old_to_p;
		}
	}

	res.center=cen;
	res.radius=rad;
	return res;
} 			 
	



zBOOL zCAICamera::CheckUnderWaterFX()
{
	const int checkWaterTraceFlags = zTRACERAY_STAT_POLY|zTRACERAY_VOB_IGNORE_NO_CD_DYN|zTRACERAY_POLY_TEST_WATER;

	// assert: Camera must be over water at startup and no beaming into water is allowed!

#ifdef COMPILING_SPACER
	// im spacer ist die in Game Camera AI nicht eingeschaltet, und wir
	// müssen die letzte Camera Position manuell updaten
/*
	frameTime = ztimer.GetFrameTimeF()/1000;
	if (!zCCamera::activeCam) return FALSE;
	if (!zCCamera::activecamVob->GetVob()) return FALSE;
	
	aiCamPos = zCCamera::activecamVob->GetVob()->GetPositionWorld();
	UpdateWayPoint(WAYPOINT_CAM);
	*/
	// [EDENFELD] Addon Spacer: gab wohl manchnmal probleme, daher
	// springen wir hier lustig raus.

	return FALSE;
#endif

	if (!camVob || !camVob->GetHomeWorld()) return FALSE;

	// safe check jeden frame. Ist die Unterwasser Camera aktiv, befindet sich der Spieler nicht im Wasser,
	// und ist die Camera höher als der Spieler, schalten wir die Unterwasser Camera aus
	if (underWater)
	{
		zCAIPlayer* aiPlayer = dynamic_cast<zCAIPlayer*>(target->GetAICallback());

		if ( target														&& 
			 aiPlayer													&& 
			 target->GetCharacterClass() == zCVob::zVOB_CHAR_CLASS_PC	&&
			 aiPlayer->GetWaterLevel()== 0								&&
			 target->GetPositionWorld()[VY] < camVob->GetPositionWorld()[VY]
		   )
		{
			underWater = FALSE;
			camVob->GetHomeWorld()->GetActiveSkyControler()->SetUnderwaterFX (underWater);
			return FALSE;
		};
	}
	else
	{
		zCAIPlayer* aiPlayer = dynamic_cast<zCAIPlayer*>(target->GetAICallback());

		if ( target														&& 
			 aiPlayer													&& 
			 target->GetCharacterClass() == zCVob::zVOB_CHAR_CLASS_PC	&&
			 aiPlayer->GetWaterLevel()== 2								&&
			 target->GetPositionWorld()[VY] > camVob->GetPositionWorld()[VY]
		   )
		{
			underWater = TRUE;
			camVob->GetHomeWorld()->GetActiveSkyControler()->SetUnderwaterFX (underWater);
			return FALSE;
		};

		camVob->GetHomeWorld()->GetActiveSkyControler()->SetUnderwaterFX (FALSE);
	}
	
	zPOINT3 lastCamPoint = moveTracker->GetLastValidWayPoint(zCMovementTracker::zWAYPOINT_CAM);

	if (lastCamPoint[VY]>camVob->GetPositionWorld()[VY])
	{
		// bewegung nach unten
		if (lastCamPoint[VY]-camVob->GetPositionWorld()[VY]<10) 
		{
			// unterschied kleiner als 10cm, lastCamPoint um 5cm nach oben verschieben
			lastCamPoint[VY]+=5;
		}
	}
	else 
	{
		// bewegung nach oben/keine bewegung
		if (camVob->GetPositionWorld()[VY]-lastCamPoint[VY]<10) 
		{
			// unterschied kleiner als 10cm, lastCamPoint um 5cm nach oben verschieben
			lastCamPoint[VY]-=5;
		}
	}

	raysCasted++;
	if (!camVob->GetHomeWorld()->TraceRayNearestHit(lastCamPoint,camVob->GetPositionWorld()-lastCamPoint,(zCVob*)0,checkWaterTraceFlags)) return FALSE;
	if (!camVob->GetHomeWorld()->traceRayReport.foundPoly) return FALSE;
	if (camVob->GetHomeWorld()->traceRayReport.foundPoly->GetMaterial()->GetMatGroup() != zMAT_GROUP_WATER) return FALSE;
	// must be 2-sided water poly, check reverse ray also
	raysCasted++;
	if (!camVob->GetHomeWorld()->TraceRayNearestHit(camVob->GetPositionWorld(),lastCamPoint-camVob->GetPositionWorld(),(zCVob*)0,checkWaterTraceFlags )) return FALSE;
	if (!camVob->GetHomeWorld()->traceRayReport.foundPoly) return FALSE;
	if (camVob->GetHomeWorld()->traceRayReport.foundPoly->GetMaterial()->GetMatGroup() != zMAT_GROUP_WATER) return FALSE;

	// nun haben wir ein wasser poly durchdrungen

	moveTracker->ResetWayPoints(camVob->GetPositionWorld(),zCMovementTracker::zWAYPOINT_CAM);

	zBOOL isWater = !underWater;

	// nun einen zweiten safe check durchführen
	if (isWater)
	{
		// wenn wir unter wasser sind, muss über der aktuellen camera position ein wasser poly existieren
		raysCasted++;
		if (!camVob->GetHomeWorld()->TraceRayNearestHit(camVob->GetPositionWorld(),200 * zVEC3(0,1,0),(zCVob*)0,checkWaterTraceFlags )) return FALSE;
		
		if (camVob->GetHomeWorld()->traceRayReport.foundPoly)
		{
			if (camVob->GetHomeWorld()->traceRayReport.foundPoly->GetMaterial()->GetMatGroup() != zMAT_GROUP_WATER) return FALSE;		// es wurde ein nicht wasser poly gefunden -> raus hier
		};
	}
	else
	{
		// wenn wir über wasser sind, muss unter der aktuellen camera position ein wasser poly existieren
		raysCasted++;
		if (!camVob->GetHomeWorld()->TraceRayNearestHit(camVob->GetPositionWorld(),200 * zVEC3(0,-1,0),(zCVob*)0,checkWaterTraceFlags )) return FALSE;
		
		if (camVob->GetHomeWorld()->traceRayReport.foundPoly)
		{
			if (camVob->GetHomeWorld()->traceRayReport.foundPoly->GetMaterial()->GetMatGroup() != zMAT_GROUP_WATER) return FALSE;		// es wurde ein nicht wasser poly gefunden -> raus hier
		};
	};

	underWater = !underWater;
	camVob->GetHomeWorld()->GetActiveSkyControler()->SetUnderwaterFX (underWater);

	return underWater;
};


/*--------------------------------------------------------------------------
    19-Sep-00       [Michael]
                      zSinCos eingeführt

    20-Sep-00       [Edenfeld]
                      zSinCos wieder durch sin/cos Calls ersetzt. Könnte durch Ungenauigkeiten
					  zu Camera Wackeln führen. Zur weiteren Beobachtung in Release 0.94 ist zSinCos drin...

--------------------------------------------------------------------------*/ 
zPOINT3& zCAICamera::CalcAziElevRange(const float &aziDeg,const float &elevDeg,const float &range, const zMAT4 &trafoObjToWorld)
{
	const zREAL	FAK = float(M_PI * ((1.0) / 180.0));
    const zREAL azi = (180-aziDeg)  * FAK;
    const zREAL elev= (elevDeg+360) * FAK;
	static zPOINT3 resultPoint;

	zPOINT3 mid		= trafoObjToWorld.GetTranslation();
	zVEC3	at		= trafoObjToWorld.GetAtVector();
	zVEC3	right   = trafoObjToWorld.GetRightVector();
	//						  ->  ->           ->            ->
	// Setup circle in Space. x = m + r*cos(b)*u0 + r*sin(b)*v0
	zVEC3 u0 = at;
	zVEC3 v0 = right;

	u0[VY]=0.0F; v0[VY]=0.0F;  // hier nicht mehr nötig ?
	u0.NormalizeSafe(); v0.NormalizeSafe();

	// get new azimuth position on circle
	zREAL fsin, fcos;
	zSinCos(azi, fsin, fcos);

	resultPoint	=  mid +   (range * fcos) * u0 + 
						   (range * fsin) * v0 ;

	// find u0 and v0 for elevation circle 
	resultPoint[VY] = mid[VY];
	u0 = (resultPoint-mid);
	u0.NormalizeSafe();

	// Get orthogonal up (=v0) vec. from new target at-vec.
	v0 = zPOINT3 (0,1,0);
	v0 = (v0 - ((v0 * u0) * u0));
	v0.NormalizeSafe(); // nötig ???

	zSinCos(elev, fsin, fcos);
	// get new elevation position on circle
	resultPoint =   zPOINT3( mid + (range * fcos) * u0 + (range * fsin) * v0 );
	return resultPoint;
}



/*

zBOOL zCAICamera::PointInFrustum(const zMATRIX4 &trafoCamToWorld, const zPOINT3 &pos)
{
	const zMAT4 trafoWorldToCam = trafoCamToWorld.InverseLinTrafo();
	
	// erster Check: Ist der gesuchte Punkt hinter der Near Clipping Plane ?
	zPOINT3 transformed = trafoWorldToCam * pos;
	if (transformed[VZ]<0) return FALSE;

	// Punkt ist vor der Near Clipping Plane. Ist der Punkt im Viewport ?
	float zrecip	= (float(1)) / pos[VZ];
	float xscr		= (vpData.xcenter) + float((pos[VX] * float(viewDistanceX)) * zrecip);
	float yscr		= (vpData.ycenter) - float((pos[VY] * float(viewDistanceY)) * zrecip);

};






};
*/


