/******************************************************************************** 
 
     $Workfile:: zPhysics.h           $                $Date:: 5.12.00 17:46    $
     $Revision:: 9                    $             $Modtime:: 5.12.00 17:46    $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ Physics / Rigid-Body Dynamics
   created       : 15.3.98

 * $Log: /current_work/zengin_work/_Dieter/zPhysics.h $
 * 
 * 9     5.12.00 17:46 Hildebrandt
 * 
 * 8     5.12.00 17:39 Hildebrandt
 * 
 * 7     4.12.00 17:46 Hildebrandt
 * 
 * 6     21.08.00 17:18 Hildebrandt
 * 
 * 5     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 14    9.08.00 17:12 Admin
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 4     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 2     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 9 $ ($Modtime: 5.12.00 17:46 $)

// =======================================================================================================================

#ifndef __ZPHYSICS_H__
#define __ZPHYSICS_H__


#ifndef __ZALGEBRA_H__
#include <zAlgebra.h>
#endif

class zCArchiver;

// =======================================================================================================================

enum zTRigidBodyMode 
{
	zPHY_RBMODE_FLY		= 0, 
	zPHY_RBMODE_SLIDE	= 1,
}; // ATT: keep in sync with bitfield

class zENGINE_API zCRigidBody {
public:
	// methods
	 zCRigidBody();
	~zCRigidBody() {};

	// Run Simulation
	void			ComputeForceTorque				(const zREAL t);
	zMAT3			Star							(const zVEC3& a);
	void			Integrate						(const zREAL deltaTime);
	void			RunSimulation					();

	// Misc
	void			SetMass							(const zREAL m) { mass=m; if (m==0)     massInv =0.00001F; else massInv = zREAL(1)/m; };
	zREAL			GetMass							() const		{ return mass; /*if (massInv==0.00001F) return 0; else return zREAL(1)/massInv;*/ };
	void			SetInertiaTensorBlock			(zREAL xdim, zREAL ydim, zREAL zdim);
	void			ApplyForce						(const zVEC3& forceVec, const zVEC3& pos);
	void			ApplyForceCM  					(const zVEC3& forceVec);
	void			ApplyImpulse					(const zVEC3& impulse, const zVEC3& point);
	void			ApplyImpulseCM					(const zVEC3& impulse);
	zVEC3			GetPointVelocity				(const zVEC3& point) const;
	void			CollisionImpulseStatic			(const zVEC3& collNormal, const zVEC3& applyPoint, const zREAL epsilon);
	void			CollisionImpulseCenterStatic	(const zVEC3& collNormal, const zREAL epsilon);
	void			CollisionImpulse				(const zVEC3& collNormal, const zVEC3& applyPoint, const zREAL epsilon,
													  zCRigidBody *body2); 
	void			StopRotation					();
	void			StopTranslation					();
	void			StopTransRot					();
	void			SetVelocity						(const zVEC3& vel);
	const zVEC3&	GetVelocity						() const					{ return v;				};
	void			SetPositionCM					(const zVEC3& pos)			{ xPos = pos;			};
	const zVEC3&	GetPositionCM					() const					{ return xPos;			};
	void			SetGravityEnabled				(const zBOOL b)				{ gravityOn = b;		};
	zBOOL			GetGravityEnabled				() const					{ return gravityOn;		};
	void			SetGravityScale					(const zREAL s)				{ gravityScale = s;		};
	zREAL			GetGravityScale					() const					{ return gravityScale;	};
	const zVEC3&	GetImpulse						() const					{ return PLinMom;		};

	void			SetMode							(const zTRigidBodyMode& m);
	zTRigidBodyMode	GetMode							() const					{ return zTRigidBodyMode(mode); };
	zBOOL			SetSliding						(const zVEC3& normal);
	zREAL			GetSlideAngle					() const					{ return slideAngle;	};
	const zVEC3&	GetSlideDir						() const					{ return slideDir;		};
	zBOOL			ShouldSlide						(const zVEC3& collNormal) const;
	// Units:
	// mass		:	kg
	// impulse	:	cm*kg/sec
	// force	:	cm*kg/sec^2	= cN
	// velocity	:	cm/sec				(intern, aber extern laeuft auch alles mit: cm/sec !)
	// position	:	cm

	// persistance
	void			Archive				(zCArchiver &arc);
	void			Unarchive			(zCArchiver &arc);
private:
	// Constant quantities
	zREAL			mass;			// mass M
	zREAL			massInv;		// mass M
	zMAT3			iBody;			// Inertia-Tensor for body
	zMAT3			iBodyInv;		// " Inverse

	// State variables
	zVEC3			xPos;			// x(t)	Position
	zMAT3			RDir;			// R(t)	Orientation
	zVEC3			PLinMom;		// P(t)	total linear momentum
	zVEC3			LAngMom;		// L(t)	total angular momentum

	// Derived quantities (auxiliary vars)
	zMAT3			iInv;			// I^-1(t) Inertia-Tensor Inverse
	zVEC3			v;				// v(t)
	zVEC3			omega;			// omega(t)

	// Computed quantities
	zVEC3			force;			// F(t)
	zVEC3			torque;			// tau(t)

	// misc
//	zVEC3			gravityForce;
	zREAL			gravityScale;
	zVEC3			slideDir;
	zREAL			slideAngle;
	struct 
	{
		zUINT8		gravityOn		: 1;
		zUINT8		collisionHad	: 1;
		zUINT8		mode			: 1;		// zTRigidBodyMode
		zUINT8		justSetSliding	: 4;		// 0,1,2
	};
};

#endif