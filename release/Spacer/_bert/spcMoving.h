
#ifndef __SPCMOVING_H__
#define __SPCMOVING_H__

class zCVob;

// #include "z3D.h"
// #include "zInput_Win32.h"

//extern BOOL mov_lock;
//extern BOOL mov_stop;

typedef enum tmov_mode { MOV_WALKING_MODEL, MOV_WALKING, MOV_VOB, MOV_VOB_CAM, MOV_VOB_PAR };



class spcCMovement 
{

public:

			spcCMovement	( zCVob *vob, tmov_mode mt = MOV_WALKING );
	virtual ~spcCMovement	();

	void Movement		();

	void SetVob			( zCVob *vob, tmov_mode mt = MOV_WALKING );
	void SetCamVob		( zCVob *camvob );
	void SetMovement	( tmov_mode mt );

	void LookForward ();
	void RestoreLook ();
	void BackupLook  ();
			
	void SetGrid		(float step);
	void SetGridRot		(float step);
	void GridRot		(bool on);
	void Grid			(bool on);

	void SetFriction	(float _friction = -1.0, float _friction_rot = -1.0);
	void GetFriction	(float& _friction, float& _friction_rot);
	
	void SetSpeed		(int value);	
	void IncreaseSpeed	(float d);	

protected:

	void (spcCMovement::*MoveProc)();
	
	void Walking		();
	
	// Bewegen von Objekten
	void VobMove		();
	void VobMoveCam		();
	void VobMovePar		();

protected:

	// Time Correction
	float		now;
	float		time_corr;

	// !!! For Spacer !!!
	zCVob*	movvob;
	zCVob*	camvob;
	float	step;
	float	rotangle;
	float	rotup;
	float	backup_rotup;
	bool	grid,gridrot;

	float force_x,force_y,force_z,force_rot;
	float xspeed,yspeed,zspeed,rotspeed;
	
	float friction;
	float friction_rot;

	float dummy[10];	// 2nd-last float-value causes memory-overrun
};

#endif