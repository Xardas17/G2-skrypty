/******************************************************************************** 
 
     $Workfile:: zPhysics.cpp         $                $Date:: 17.01.01 1:15    $
     $Revision:: 11                   $             $Modtime:: 17.01.01 1:15    $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zPhysics.cpp $
 * 
 * 11    17.01.01 1:15 Hildebrandt
 * 
 * 10    16.01.01 10:56 Moos
 * 
 * 9     14.01.01 16:36 Hildebrandt
 * 
 * 8     11.01.01 18:45 Moos
 * 
 * 7     20.09.00 1:39 Rueve
 * 
 * 6     31.08.00 17:04 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 6     15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 4     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 3     18.11.99 0:23 Hildebrandt
 * 
 * 2     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 11 $ ($Modtime: 17.01.01 1:15 $)


#include <zPhysics.h>
#include <zError.h>
#include <zArchiver.h>

#include <z3d.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 


// ACHTUNG: RDir wird von zCVob zur Zeit nicht intialisiert => angularEffects sind zur Zeit disabled

/*
	- Particel State: position & velocity
	- Problem: Vob-Origin = Center of Mass Location ! (bei Baraff)
*/

zCRigidBody::zCRigidBody() 
{
	memset (this, 0, sizeof(*this));
	RDir					= Alg_Identity2D();
	collisionHad			= FALSE;
	justSetSliding			= 0;
	SetMass					(10);				// kg
	SetInertiaTensorBlock	(50, 50, 50);
	SetGravityEnabled		(TRUE);
	SetGravityScale			(1.0);
	SetMode					(zPHY_RBMODE_FLY);
};

// *********************************************************************************************************
//	Simulation
// *********************************************************************************************************


void zCRigidBody::ComputeForceTorque(const zREAL t) 
{
//	force	= zVEC3(0);
//	torque	= zVEC3(0);

//	force	= zVEC3(0,10,0);
//	v = zVEC3(0,100,0);

	// Air-Friction
//	force	= force - 1.5*v;
//	force	= force - 0.05*(v);

//	LAngMom = LAngMom * 0.0F;
//	omega	= omega * 0.01F;
/*
	// Gravity
	if (xPos[VY]>-100000) {
//		force = force + zVEC3(0,-0.0001,0);
	} else {
		xPos[VY]=-100000;
		v[VY]	= 0;
	};*/
};

zMAT3 zCRigidBody::Star (const zVEC3& a)
 {				// richtiges Setup ???
/*	return zMAT3 (  zVEC3 (   0 , -a[2],  a[1]),
					zVEC3 ( a[2],    0 , -a[0]),
					zVEC3 (-a[1],  a[0],    0)); */
	return zMAT3 (  zVEC3 (   0 ,  a[2], -a[1]),
					zVEC3 (-a[2],    0 ,  a[0]),
					zVEC3 ( a[1], -a[0],    0)); 
};

zBOOL zCRigidBody::SetSliding (const zVEC3& normal) 
{
	zBOOL res = TRUE;

	// slide-Angle
//	zREAL oldSlideAngle = slideAngle;
	slideAngle			= Alg_Rad2Deg (Alg_AngleUnitRad (normal, zVEC3(0,1,0)));

	// bereits im SlideMode & wurde SlideMode gerade im letzten Frame mit derselben Normal gesetzt ?
	// Hier den Fall abfangen, wenn mehrmals hintereinander ein SetSlide derselben Normal
	// gemacht werden soll.
/*	if (justSetSliding>0)
	if (GetMode()==zPHY_RBMODE_SLIDE) {
		if (zAbs(slideAngle-oldSlideAngle)<0.01F) res = FALSE;
		justSetSliding = 2;
		return res;
	};
	justSetSliding = 2;*/
	// sim(0) - setSlide(2) - sim(2=>1) - [setSlide(1=>2)] | [nix(1)] - sim (1=>0)

	// v auf slide-plane projezieren
	zVEC3 v		= GetVelocity();
	v			=-((v^normal)^normal);
	v[VY] += 5.0F;										// FIXME: HACK, damit body nicht direkt wieder in Hinderniss bumpt..
	SetVelocity	(v);
	// slide-richtung bestimmen
	slideDir	= (zVEC3(0,1,0)^normal)^normal;
	if (slideDir[VY]>0) slideDir= -slideDir;
	// Mode setzen
	SetMode		(zPHY_RBMODE_SLIDE);

	return res;
};

/*--------------------------------------------------------------------------
    zCRigidBody::Integrate()
    19-Sep-00       [Michael]
                      Mikrooptimierung (günstigere Muls)
--------------------------------------------------------------------------*/ 

void zCRigidBody::Integrate (const zREAL deltaTime) 
{
	// Euler: y1 = y0 + h*ydot

	///////////////////////////////////
	// Linear
	///////////////////////////////////
//	xPos	+= deltaTime * v;
//	PLinMom	+= deltaTime * force;
//	v		= PLinMom * massInv;

	if (justSetSliding>0) justSetSliding--;

	// Fg = m * g
	if (!collisionHad) 
	{
		if (GetGravityEnabled()) 
		{
			if (GetMode()==zPHY_RBMODE_SLIDE) 
			{
				// Gleitreibung
				force	=  force - (mass)*(v);		// 2.5
	//			force	=  force - 2.5F*(1/massInv)*(v);		// 2.5
				// Gravity, auf die Slideplane projeziert
				zVEC3 g(0,-981.0F*gravityScale*mass,0);
				force	+= slideDir * (g*slideDir);
//				zlineCache.Line3D (xPos, xPos+slideDir*50, GFX_BROWN);
			} else 
			{
				force	+= zVEC3(0,-981.0F*gravityScale*mass,0);
			};
		};
	} else 
	{
		collisionHad = FALSE;
		force += zVEC3(0,1,0);
	};

	PLinMom	+= deltaTime * force;				// PLinMom	= m * v
	v		 = PLinMom	 * massInv;				// v		= PLinMom / m
	xPos	+= deltaTime * v;


//	zerr.Message ("D: xPos: "+zSTRING(xPos.Length()));

//	zVEC3 a;
//	a		 = force	* massInv;
//	v		+= deltaTime* a;
//	xPos	+= deltaTime* v;

	// Compute aux variables
	// v(t) = P(t) / M
//	v		= PLinMom * massInv;

	///////////////////////////////////
	// Angular
	///////////////////////////////////
/*	LAngMom	+= deltaTime * torque;
	// Ableitung von R(t) = omega(t)*R(t)
	// Compute Rdot(t) = omega(t)*R(t)
	zMAT3 Rdot = Star (omega) * RDir;
	for (int i=0; i<3; i++) for (int j=0; j<3; j++)
		RDir[i][j] += deltaTime * Rdot[i][j];
	RDir.MakeOrthonormal();*/
#if 0	
	// Compute aux variables
	// I^-1(t) = R(t) * iBody^-1 * R(t).Transpose
	iInv = RDir * iBodyInv * RDir.Transpose();
	// omega(t) = I^-1(t) * L(t)
	omega= iInv * LAngMom;
#endif 
	// Reset, damit sich im naechsten Frame die Forces aufsummieren koennen
	force	= zVEC3(0);
	torque	= zVEC3(0);
};

void zCRigidBody::RunSimulation () {
	zREAL deltaTime;

	// deltaTime in Sekunden umwandeln (1ms / 1000 = 0,001s)
	deltaTime = ztimer.GetFrameTimeF() / 1000;		

	if (deltaTime<=0) return;
	ComputeForceTorque	(deltaTime);
	Integrate			(deltaTime);
};

// *********************************************************************************************************
//	MISC
// *********************************************************************************************************

void zCRigidBody::SetInertiaTensorBlock	(zREAL xdim, zREAL ydim, zREAL zdim) 
{
	zMAT3 mat	= Alg_Identity2D();
	xdim		*= xdim;
	ydim		*= ydim;
	zdim		*= zdim;
	mat[0][0]	= ydim + zdim;
	mat[1][1]	= xdim + zdim;
	mat[2][2]	= xdim + ydim;
	iBody		= ((mass) / 12) * mat;
	iBodyInv	= iBody.Inverse();
};

void zCRigidBody::ApplyForceCM (const zVEC3& forceVec) 
{
	force += forceVec;
};

void zCRigidBody::ApplyForce (const zVEC3& forceVec, const zVEC3& pos) 
{
	force += forceVec;
};

zVEC3 zCRigidBody::GetPointVelocity (const zVEC3& point) const 
{
	// Geschwindigkeit in einem Punkt auf dem Koerper
	return v + (omega ^ (point - xPos));
};

void zCRigidBody::ApplyImpulseCM (const zVEC3& impulse) {
	PLinMom += impulse;
	v	 = PLinMom * massInv;
};

void zCRigidBody::ApplyImpulse (const zVEC3& impulse, const zVEC3& point) 
{ 
	// apply impulse
	// ??? addieren oder ersetzen ???
	PLinMom += impulse;						// collImpulseStatic
//	PLinMom = impulse;						// applyImpulse (set)

//	LAngMom += (point-xPos) ^ impulse;

	// recompute aux vars
	// v(t) = P(t) / M
	v	 = PLinMom * massInv;

	// omega(t) = I^-1(t) * L(t)
//	omega= iInv * LAngMom;
};

//zCRigidBody::ClassifyContact();

void zCRigidBody::CollisionImpulseStatic (const zVEC3& collNormal, const zVEC3& applyPoint, const zREAL epsilon) 
{
	 
	//////////////////////////////////////////
	// - Variante A:	Impulse				//
	//////////////////////////////////////////

//	const zREAL THRESHOLD	= zREAL(1.0F);

/*	// Variant A1:  hit auf Oberflaeche
	// ACHTUNG: ist xPos hier WIRKLICH trafoObjToWorld.GetPositionWorld() ????
	zVEC3		padot		= GetPointVelocity(applyPoint);
	zREAL		vrel		= collNormal * padot;
	// contact oder von anderem Object wegbewegend ?
	if (vrel >= 0) return;		

	zVEC3	ra			= applyPoint - xPos;
	zREAL	numerator	= -(1 + epsilon) * vrel;
	zREAL	denum		= ( massInv + (collNormal * ((iInv * (ra ^ collNormal)) ^ ra)));
	zREAL	j			= numerator / denum;
	zVEC3	impulse		= j*collNormal;
*/
	// Variant A2:  hit center
	zVEC3	padot		= GetVelocity();
	zREAL	vrel		= collNormal * padot;
	// contact oder von anderem Object wegbewegend ?
	if (vrel >= -0.001F) return;

	zREAL	numerator	= -(1 + epsilon) * vrel;
	zREAL	denum		= massInv;
	if (denum==0) denum = 0.00001F;
	zREAL	j			= numerator / denum;
	zVEC3	impulse		= j*collNormal;

//	zREAL vOld = v[VY];
	ApplyImpulse (impulse, applyPoint);
//	zerr.Message ("Impulse: "+impulse.GetString()+", vy-: "+zSTRING(vOld)+", vy+"+zSTRING(v[VY])); 
//	zerr.Message ("vy-: "+zSTRING(vOld)+", vy+"+zSTRING(v[VY])); 
	collisionHad = TRUE;


	//////////////////////////////////////////
	// - Variante B:  Reflection Vector		//
	//////////////////////////////////////////
/*
	zVEC3 reflect = -v;
	reflect.Normalize();
	reflect = reflect.Reflect (collNormal);
	zlineCache.Line3D (applyPoint, applyPoint+reflect*50, GFX_YELLOW);			// reflection vector

	reflect *= v.Length()*1.0F;
	ApplyImpulse (reflect, applyPoint);
//	SetVelocity  (reflect);
	*/
};

void zCRigidBody::CollisionImpulseCenterStatic (const zVEC3& collNormal, const zREAL epsilon) 
{
	 
	//////////////////////////////////////////
	// - Variante A:	Impulse				//
	//////////////////////////////////////////

	// Variant A2:  hit center
/*	zVEC3	padot		= GetVelocity();
	zREAL	vrel		= collNormal * padot;
	// contact oder von anderem Object wegbewegend ?
	if (vrel >= -0.001F) return; 

	zREAL	numerator	= -(1 + epsilon) * vrel;
	zREAL	denum		= massInv;
	zREAL	j			= numerator / denum;
	zVEC3	impulse		= j*collNormal;

//	zREAL vOld = v[VY];
	ApplyImpulse (impulse, xPos);*/
//	zerr.Message ("Impulse: "+impulse.GetString()+", vy-: "+zSTRING(vOld)+", vy+"+zSTRING(v[VY])); 
//	zerr.Message ("vy-: "+zSTRING(vOld)+", vy+"+zSTRING(v[VY])); 

/*	zVEC3 vv = v;
	vv.Normalize();
	zVALUE angle = Alg_Rad2Deg(Alg_AngleUnitRad(vv,collNormal));
	if (angle>80) zerr.Message ("diff-angle: "+zSTRING(angle));*/

	//////////////////////////////////////////
	// - Variante B:  Reflection Vector		//
	//////////////////////////////////////////

	zVEC3		reflect		= -v;
	const zREAL	reflectLen	= reflect.Length();
	if (reflectLen>0) 
	{
		reflect		= reflect / reflectLen;		// Normalize()
		reflect		= reflect.Reflect (collNormal);
	//	zlineCache.Line3D (applyPoint, applyPoint+reflect*50, GFX_YELLOW);			// reflection vector
		reflect		*= v.Length()*0.3F;
		SetVelocity (reflect);
	}

	collisionHad = TRUE;
};


void zCRigidBody::CollisionImpulse    (const zVEC3& collNormal, const zVEC3& applyPoint, const zREAL epsilon,
									   zCRigidBody *body2) 
{ 
	// Variant A1:  hit auf Center
	zVEC3		padot		= GetVelocity();
	zVEC3		pbdot		= body2->GetVelocity(); 
//pbdot =0;
	zREAL		vrel		= collNormal * (padot - pbdot);

	// contact oder von anderem Object wegbewegend ? => raus
//	zerr.Message ("vrel: "+zSTRING(vrel));
//	zerr.Message ("- va: "+(padot.GetString())+", vb: "+zSTRING(pbdot.GetString()));
	if (vrel >= -0.001F) return;

	zREAL	numerator	= -(1 + epsilon) * vrel;
	zREAL	denum		= ( massInv + body2->massInv );
//	zREAL	denum		= ( massInv + 0);
	zREAL	j			= numerator / denum;
	zVEC3	impulse		= j*collNormal; 
//	zerr.Message ("imp: "+impulse.GetString());
	
	       ApplyImpulse ( impulse, applyPoint);
	body2->ApplyImpulse (-impulse, applyPoint);
//		   collisionHad = TRUE;
//	body2->collisionHad = TRUE;
};


void zCRigidBody::StopRotation () 
{
	torque	= 0;
	LAngMom	= 0;
	omega	= 0;
};

void zCRigidBody::StopTranslation () 
{
	force	= 0;
	PLinMom	= 0;
	v		= 0;
};

void zCRigidBody::StopTransRot () 
{
	StopRotation	();
	StopTranslation	();
	SetMode			(zPHY_RBMODE_FLY);
};

void zCRigidBody::SetVelocity (const zVEC3& vel) 
{
	force	= 0;
	v		= vel;
	PLinMom	= v / massInv;
};

void zCRigidBody::SetMode (const zTRigidBodyMode& m)	
{ 
/*	if (m   ==zPHY_RBMODE_FLY)
	if (mode==zPHY_RBMODE_SLIDE)
	{
		zerr.Message ("slide => flying");
	};*/
	mode = m; 
};

zBOOL zCRigidBody::ShouldSlide (const zVEC3& collNormal) const 
{
	// Übergang zum sliden ?
	// Bedingungen:
	// - Geschwindigkeit < THRESH
	// - Winkel des Bodens absolut		 < 70° (am Hang)
	// - Winkel Bewegung gegenüber Boden > 45°
	zBOOL doSliding = FALSE;
//	zREAL angle		= Alg_Rad2Deg (Alg_AngleUnitRad (-collPlane.normal, RigidBody()->GetVelocity().Normalize()));
	zREAL angleAbs	= Alg_Rad2Deg (Alg_AngleUnitRad (collNormal, zVEC3(0,1,0)));
	zVEC3 vv		=-GetVelocity(); 
	zREAL vvLen		= vv.Length();
	if (vvLen>0)
	{
		vv				= vv / vvLen;		// vv.Normalize();
		zREAL angleRel	= Alg_Rad2Deg (Alg_AngleUnitRad (collNormal, vv));
		//	zerr.Message ("angleRel: "+zSTRING(angleRel));
		if ((angleAbs<70) && (angleRel>40) && (angleRel<110) && (GetVelocity().Length2()<(700*700))) doSliding = TRUE;
	};
	return doSliding;
};

void zCRigidBody::Archive (zCArchiver &arc) 
{
	arc.WriteVec3	("vel"		,	GetVelocity());
	arc.WriteByte	("mode"		,	GetMode());
	arc.WriteBool	("gravOn"	,	gravityOn);
	arc.WriteFloat	("gravScale",	gravityScale);
	arc.WriteVec3	("slideDir"	,	slideDir);
};

void zCRigidBody::Unarchive (zCArchiver &arc) 
{
	SetVelocity		(arc.ReadVec3	("vel"));
	SetMode			(zTRigidBodyMode(arc.ReadByte	("mode")));
	gravityOn	= 	 arc.ReadBool	("gravOn");
	arc.ReadFloat	("gravScale",	gravityScale);
	arc.ReadVec3	("slideDir"	,	slideDir);
};

/*
void RIGID_BODY::move( const SCALAR dt )
{
		 VECTOR F, T;
         this->Translate( this->V * dt );
         this->Rotate( this->W * dt );
         ComputeForceAndTorque( F, T );
         this->V += (1/this->M)* F * dt;
         this->W += this->I_inv * (T - W.cross(I*W)) *
         dt;
}
*/


// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 

