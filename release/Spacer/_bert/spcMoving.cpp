#include "stdafx.h"

#include "zengine.h"

#include "spcMoving.h"

#include "zvob.h"
#include "zinput_win32.h"
#include "spacerview.h"

const		bool mov_lock = false;		// Stop Movement if CTRL is pressed
const		bool mov_stop = false;		// Stop complete Movement

// Grid Delta Values
static float dx = 0.0f;
static float dy = 0.0f;
static float dz = 0.0f;
static float step_save = 1.0f;

// Movement
static	float MOV_MASS		=  60.0f;	// Unser Player bringt 60kg auf die Waage
static	float MOV_FORCE_Z		= 240.0f;	// Kraft beim Vorwärts gehen	
static	float MOV_FORCE_X		= 200.0f;	// Kraft beim zur Seite gehen
static	float MOV_FORCE_Y		= 200.0f;	
static  float MOV_FRIC_MOV	= 0.45f;	// Reibungsfaktor

static	float MOV_FORCE_ROT	= 2.0f;  // Rotationsbeschleunigung
static  float MOV_FRIC_ROT	= 0.6f;	// Reibungsfaktor Drehen

// TIME CORRECTION VALUES
static const int MOV_TIME_CORR		= 64;	// Used in DIV

// Keys
#define MOV_KEY_RUN		KEY_LSHIFT
#define MOV_KEY_ACTION	KEY_LCTRL
#define MOV_KEY_SMOVE	GAME_SMOVE
#define MOV_KEY_INV		KEY_TAB
#define MOV_KEY_BOOK	KEY_ENTER
#define MOV_KEY_WEAPONS KEY_SPACE


static zCTimer movTimer;

// Constructor
spcCMovement::spcCMovement(zCVob *vob, tmov_mode mt)
{		
	/*bool*/	grid	= false;
	/*bool*/	gridrot = false;

	/*zCVob* */	movvob = vob;
	/*zCVob* */	camvob = vob;
	
	/*float*/	step = 12;
	/*float*/	rotangle = 0;
	/*float*/	rotup = 0;
	/*float*/	backup_rotup = 0;
	
	/*float*/	force_x		= 0.0;
	/*float*/	force_y		= 0.0;
	/*float*/	force_z		= 0.0;
	/*float*/	force_rot	= 0.0;
	/*float*/	xspeed		= 0.0;
	/*float*/	yspeed		= 0.0;
	/*float*/	zspeed		= 0.0;
	/*float*/	rotspeed	= 0.0;
		
	/*float*/	friction	= MOV_FRIC_MOV;
	/*float*/	friction_rot= MOV_FRIC_ROT;

	/*float*/	now = 0;
	/*float*/	time_corr = 0;

	if (movvob) movvob->AddRef();
	if (camvob) camvob->AddRef();
			
	SetMovement ( mt );
};

spcCMovement::~spcCMovement()
{
	zRELEASE(movvob);
	zRELEASE(camvob);	
};


void spcCMovement :: SetVob ( zCVob *vob, tmov_mode mt )
{
	zRELEASE(movvob);
	movvob	 = vob;
	if (movvob) movvob->AddRef();
	SetMovement ( mt );
}

void spcCMovement :: SetCamVob ( zCVob *cvob )
{
	zRELEASE(camvob);
	camvob	= cvob;
	if (camvob) camvob->AddRef();
}

void spcCMovement :: SetMovement ( tmov_mode mt )
{	
	switch (mt) 
	{
		case MOV_WALKING		:	MoveProc = &spcCMovement :: Walking;		break;
		case MOV_VOB			:	MoveProc = &spcCMovement :: VobMove;		break;
		case MOV_VOB_CAM		:	MoveProc = &spcCMovement :: VobMoveCam;		break;
		case MOV_VOB_PAR		:	MoveProc = &spcCMovement :: VobMovePar;		break;
	}
}

void spcCMovement :: IncreaseSpeed (float d) 
{
	MOV_FORCE_X = zMax (9.0f, (float)(MOV_FORCE_X+d));
	MOV_FORCE_Y = zMax (6.0f, (float)(MOV_FORCE_Y+d));
	MOV_FORCE_Z = zMax (12.0f, (float)(MOV_FORCE_Z+d));
};

void spcCMovement :: SetSpeed (int value)
// Set Speed to absolute Values
{
	float mult = (float)value;
	MOV_FORCE_Z	= 50*mult;
	MOV_FORCE_X	= 50*mult;
	MOV_FORCE_Y	= 50*mult;
	MOV_FORCE_ROT	=	(mult/15)+1;
}

void spcCMovement :: LookForward ()
{	
	// movvob->ResetRotations();		
	movvob->ResetXZRotationsWorld();
	rotup=0;
}

void spcCMovement :: RestoreLook ()
{
	rotup = backup_rotup;
	movvob -> RotateLocal(1,0,0,-rotup);
}

void spcCMovement :: BackupLook  ()
{
	backup_rotup = rotup;	
}

void spcCMovement :: Movement ()
// normale Fortbewegung
{
	(this->*MoveProc) ();
	movTimer.ResetTimer();
}

void spcCMovement :: Walking ()
{		
	if (dynamic_cast<zCDecal*>(movvob)) return;
	if (!movvob) return;

	force_x = force_y = force_z = force_rot = 0;

	if ((mov_stop) || ((mov_lock) && (zinput->KeyPressed(MOV_KEY_ACTION)))) goto timing;
		
	// Bewegung in Z-Richtung ( Vorwärts / Rückwärts )	
	if (zinput->KeyPressed(KEY_UP))  
	{
		force_z += MOV_FORCE_Z;	
	}
	
	if (zinput->KeyPressed(KEY_DOWN)) force_z -= MOV_FORCE_Z;
		
	// Bewegung in Y-Richtung ( Hoch / Runter )
	if (zinput->KeyPressed(KEY_A)) force_y += MOV_FORCE_Y;
	
	if (zinput->KeyPressed(KEY_Z)) force_y -= MOV_FORCE_Y;	// [BENDLIN] Addon - KeybFix
	
	// nur fuer nicht-trigger
	//if ( !dynamic_cast<zCTrigger*>(movvob) )
	{
		// Bewegung in X-Richtung ( (Turn) Links / ( Turn ) Rechts )
		zBOOL fullScreen = CSpacerView::view ? CSpacerView::view->modeFullscreen : FALSE;

		if (zinput->KeyPressed(KEY_LCTRL) || zinput->KeyPressed(KEY_RCTRL) || fullScreen)
		{
			if (zinput->KeyPressed(KEY_PAD_END)) force_x -= MOV_FORCE_X;		
			if (zinput->KeyPressed(KEY_PAD_PGDN)) force_x += MOV_FORCE_X;		
			if (zinput->KeyPressed(KEY_LEFT)) force_x -= MOV_FORCE_X;		
			if (zinput->KeyPressed(KEY_RIGHT)) force_x += MOV_FORCE_X;		
		}
		else
		{
			if (zinput->KeyPressed(KEY_PAD_END)) force_x -= MOV_FORCE_X;		
			if (zinput->KeyPressed(KEY_PAD_PGDN)) force_x += MOV_FORCE_X;		
			if (zinput->KeyPressed(KEY_LEFT)) force_rot -= MOV_FORCE_ROT;		
			if (zinput->KeyPressed(KEY_RIGHT)) force_rot += MOV_FORCE_ROT;
		}		
	}
	
	// **************************************************************************************

	if (zinput->KeyPressed(KEY_LSHIFT)) 
	{
		force_x *= 3;
		force_z *= 3;
		force_rot *= 3;
	}


timing:

	// TIME CORRECTION
	float fric_corr;
	
	now = movTimer.GetFrameTimeF();
	if (now<=0) now=100;

	time_corr = float(now) / MOV_TIME_CORR;	
	// zERR_MESSAGE(1,0,"B: "+zSTRING(now)+" -> "+zSTRING(time_corr));
	// time_corr=1;

	fric_corr = friction * time_corr;

	xspeed   += (force_x / MOV_MASS) * time_corr - fric_corr * xspeed; 
	yspeed   += (force_y / MOV_MASS) * time_corr - fric_corr * yspeed; 
	zspeed   += (force_z / MOV_MASS) * time_corr - fric_corr * zspeed; 
	rotspeed += force_rot * time_corr - friction_rot * rotspeed * time_corr;

	/*	
		// WITHOUT TIME CORRECTION
		time_corr = 1;
		xspeed   += (force_x / MOV_MASS) - friction * xspeed; 
		yspeed   += (force_y / MOV_MASS) - friction * yspeed; 
		zspeed   += (force_z / MOV_MASS) - friction * zspeed; 
		rotspeed += force_rot - (friction_rot * rotspeed);
	*/

	// nur fuer nicht-trigger
	//if ( !dynamic_cast<zCTrigger*>(movvob) )
	{
		// Hoch / Runter gucken
		if (zinput->KeyPressed(KEY_PGUP)) 
		{
			if (zinput->KeyPressed(KEY_LSHIFT)) 
			{
				movvob -> RotateLocal(1,0,0,-32);
				rotup -= 32;
			}
			else 
			{
				movvob -> RotateLocal(1,0,0,-4);
				rotup -= 4;
			}
		}
		if (zinput->KeyPressed(KEY_PGDN)) 
		{
			if (zinput->KeyPressed(KEY_LSHIFT)) 
			{
				movvob -> RotateLocal(1,0,0,32);
				rotup += 32;
			}
			else 
			{
				movvob -> RotateLocal(1,0,0,4);
				rotup += 4;
			}
		}

		if (zinput->KeyPressed(KEY_END)) 
		{
			movvob -> RotateLocal(1,0,0,-rotup);
			rotup=0;
		}

		if (rotup!=0) movvob -> RotateLocal(1,0,0,-rotup);
		
		movvob -> MoveLocal ((float)xspeed,(float)yspeed,(float)zspeed);
		
		if (rotup!=0) movvob -> RotateLocal(1,0,0,rotup);
		
		movvob -> RotateWorld (0,1,0,float(rotspeed));
	}
}

// *********************************************************************
// Grid - Routines for Spacer 
// *********************************************************************

void spcCMovement :: SetGrid (float s)
{
	step_save = s;
	// Grid Correction
	if (grid) {
		float x,y,z;
		step = s;
		movvob -> GetPositionWorld (x,y,z);
		x = ((int)x / step) * step;
		y = ((int)y / step) * step;
		z = ((int)z / step) * step;
		movvob -> SetPositionWorld (x,y,z);
		dx = 0; dy = 0; dz = 0;
	}
}

void spcCMovement :: Grid (bool on)
{
	grid = on;
	
	// Grid Correction
	if (grid) {
		float x,y,z;
		step = step_save;
		if (step<=0) step = 1;
		movvob -> GetPositionWorld (x,y,z);
		x = ((int)x / step) * step;
		y = ((int)y / step) * step;
		z = ((int)z / step) * step;
		movvob -> SetPositionWorld (x,y,z);
		dx = 0; dy = 0; dz = 0;
	} else {
		// Grid Off
		step_save	= step;
		step		= 1;
	}
}

void spcCMovement :: SetGridRot (float s)
{
	rotangle = s;
	if (rotangle<=0) rotangle = 1;
}

void spcCMovement :: GridRot (bool on)
{
	gridrot = on;
}

// *********************************************************************
// Special Movements for Spacer 
// *********************************************************************
// VOB_MOVE		: Normale Vobbewegung ohne Nachschwingen
// VOB_MOVE_CAM	: Vobbewegung relativ aus Sicht einer Camera
// *********************************************************************

void spcCMovement :: VobMoveCam()
{
	float rotx,roty,rotz;
	float x1,y1,z1,x2,y2,z2;
	if (grid) movvob->GetPositionWorld(x1,y1,z1);	

	if (camvob == NULL) {
		zerr.Report(zERR_FAULT,-1,"A: keine Camera bei VobMoveCam !"); 
		return;
	}

	xspeed = yspeed = zspeed = rotx = roty = rotz = rotspeed = 0.0;

	/*
	if (zinput->KeyPressed(MOV_KEY_SMOVE))
	{
		if (zinput->KeyPressed(KEY_END))		movvob->ResetRotationsWorld();
		else if (zinput->KeyPressed(KEY_DEL))	movvob->ResetXZRotationsWorld();
	}
	*/

	if (zinput->KeyPressed(KEY_DEL))	{ rotspeed = 1;roty = -1; }
	if (zinput->KeyPressed(KEY_PGDN))	{ rotspeed = 1;roty = +1; }

	if (zinput->KeyPressed(KEY_INS))	{ rotspeed = 1;rotz = +1; }
	if (zinput->KeyPressed(KEY_PGUP))	{ rotspeed = 1;rotz = -1; }

	if (zinput->KeyPressed(KEY_HOME))	{ rotspeed = 1;rotx = -1; }
	if (zinput->KeyPressed(KEY_END))	{ rotspeed = 1;rotx = +1; }


	if (zinput->KeyPressed(KEY_LEFT))	xspeed = -step;
	if (zinput->KeyPressed(KEY_RIGHT))	xspeed = +step;	
	
	if (zinput->KeyPressed(KEY_UP))		zspeed = +step; 	
	if (zinput->KeyPressed(KEY_DOWN))	zspeed = -step;

	if (zinput->KeyPressed(KEY_A))		yspeed = +step; 	
	if (zinput->KeyPressed(KEY_Z))		yspeed = -step;	// [BENDLIN] Addon - KeybFix
	
	
	if ((zinput->KeyPressed(KEY_LSHIFT)) && (!grid)) 
	{
		xspeed *= 10;
		yspeed *= 10;
		zspeed *= 10;
		rotspeed *= 10;
	}

	if (rotspeed != 0) {
		if (!gridrot) 
			movvob -> RotateLocal((float)rotx,(float)roty,(float)rotz,(float)rotspeed);
//			vob -> Rotate((float)rotx,(float)roty,(float)rotz,(float)rotspeed);
		else
			movvob -> RotateLocal((float)rotx,(float)roty,(float)rotz,(float)rotangle);
//			vob -> Rotate((float)rotx,(float)roty,(float)rotz,(float)rotangle);
	}

	zMATRIX4 trafo		= camvob -> GetTrafoLocal();

	
	zPOINT3 right	(trafo[0][0], 0, trafo[2][0]);
	zPOINT3 up		(0, trafo[1][1], 0);
	zPOINT3 at		(trafo[0][2], 0 , trafo[2][2]);
	
	movvob -> GetPositionWorld (x2,y2,z2);
	
	x2 += (xspeed * right.n[VX]) + (yspeed * up.n[VX]) + (zspeed * at.n[VX]);
	y2 += (xspeed * right.n[VY]) + (yspeed * up.n[VY]) + (zspeed * at.n[VY]);	
	z2 += (xspeed * right.n[VZ]) + (yspeed * up.n[VZ]) + (zspeed * at.n[VZ]);
	
	movvob -> SetPositionWorld (x2,y2,z2);

	if (grid) 
	{
		movvob -> GetPositionWorld(x2,y2,z2);

		dx += (x2-x1);
		dy += (y2-y1);
		dz += (z2-z1);

		if (dx<-step) { x1 -= step; dx+=step; } else
		if (dx> step) { x1 += step; dx-=step; }
		if (dy<-step) { y1 -= step; dy+=step; } else
		if (dy> step) { y1 += step; dy-=step; }
		if (dz<-step) { z1 -= step; dz+=step; } else
		if (dz> step) { z1 += step; dz-=step; }

		movvob -> SetPositionWorld(x1,y1,z1);
	}
}

void spcCMovement :: VobMove()
{
	float x1,y1,z1,x2,y2,z2;

	if (grid) movvob->GetPositionWorld(x1,y1,z1);
	
	xspeed = yspeed = zspeed = rotspeed = 0;
	// Vorwärts
	if (zinput->KeyPressed(KEY_UP)) 
	{
		zspeed = step;
	} 
	else 
	if (zinput->KeyPressed(KEY_DOWN)) 
	{
		zspeed = -step;
	};

	// Nach links gehen / drehen
	if (zinput->KeyPressed(KEY_LEFT)) 
	{
		if (zinput->KeyPressed(MOV_KEY_SMOVE)) 
			xspeed = -step;
		else
			rotspeed = -step;
	}
	
	if (zinput->KeyPressed(KEY_RIGHT)) 
	{
		if (zinput->KeyPressed(MOV_KEY_SMOVE)) 
			xspeed = step;
		else	
			rotspeed = step;
	};
	
	if (zinput->KeyPressed(KEY_A)) 
	{
		yspeed = step;
	}
	else
	if (zinput->KeyPressed(KEY_Z))	// [BENDLIN] Addon - KeybFix
	{
		yspeed = -step;
	};

	if ((zinput->KeyPressed(KEY_LSHIFT)) && (!grid)) 
	{
		xspeed *= 3;
		yspeed *= 3;
		zspeed *= 3;
		rotspeed *= 3;
	}

	if (rotspeed!=0) 
	{
		if (!gridrot) 
			movvob -> RotateLocal (0,1,0,float(rotspeed));
		else
			// !!! BERTS SCHMUH aendern !!!
			movvob -> RotateLocal (0,1,0,rotangle);
	}


	zVEC3 moveVec((float)xspeed,(float)yspeed,(float)zspeed);
	moveVec.Normalize();
	moveVec *= (movTimer.GetFrameTimeF()/1000)*10.0F;

	movvob -> MoveLocal  (xspeed,yspeed,zspeed);
	
	// Deltas ermittlen
	
	if (grid) 
	{
		movvob -> GetPositionWorld(x2,y2,z2);

		dx += (x2-x1);
		dy += (y2-y1);
		dz += (z2-z1);

		if (dx<-step) { x1 -= step; dx+=step; } else
		if (dx> step) { x1 += step; dx-=step; }
		if (dy<-step) { y1 -= step; dy+=step; } else
		if (dy> step) { y1 += step; dy-=step; }
		if (dz<-step) { z1 -= step; dz+=step; } else
		if (dz> step) { z1 += step; dz-=step; }

		movvob -> SetPositionWorld(x1,y1,z1);
	}
}

void spcCMovement :: VobMovePar()
{
	float x1,y1,z1,x2,y2,z2;

	if (grid) movvob->GetPositionWorld(x1,y1,z1);
	
	xspeed = yspeed = zspeed = rotspeed = 0;
	// Vorwärts
	if (zinput->KeyPressed(KEY_UP)) 
	{
		zspeed = step;
	}
	else
	if (zinput->KeyPressed(KEY_DOWN)) 
	{
		zspeed = -step;
	};

	// Nach links gehen / drehen
	if (zinput->KeyPressed(KEY_LEFT))	xspeed = -step;	
	
	if (zinput->KeyPressed(KEY_RIGHT))	xspeed = step;
	
	if (zinput->KeyPressed(KEY_A)) 
	{
		yspeed = step;
	} 
	else
	if (zinput->KeyPressed(KEY_Z))	// [BENDLIN] Addon - KeybFix
	{
		yspeed = -step;
	};

	if ((zinput->KeyPressed(KEY_LSHIFT)) && (!grid)) 
	{
		xspeed *= 10;
		yspeed *= 10;
		zspeed *= 10;
		rotspeed *= 10;
	}

	if (rotspeed!=0) 
	{
		if (!gridrot) 
			movvob -> RotateLocal (0,1,0,float(rotspeed));
		else
			// !!! BERTS SCHMUH aendern !!!
			movvob -> RotateLocal (0,1,0,rotangle);
	}


	if (xspeed!=0 || zspeed!=0 || yspeed!=0) 
	{
		zVEC3 moveVec((float)xspeed,(float)yspeed,(float)zspeed);
		moveVec.Normalize();
		// moveVec *= (movTimer.GetFrameTimeF()/1000)*10.0F;
		moveVec = moveVec*10;
		//	movvob -> MoveLocal  (xspeed,yspeed,zspeed);
		movvob -> MoveLocal  (moveVec);
	}
	
	// Deltas ermittlen
	
	if (grid) 
	{
		movvob -> GetPositionWorld(x2,y2,z2);

		dx += (x2-x1);
		dy += (y2-y1);
		dz += (z2-z1);

		if (dx<-step) { x1 -= step; dx+=step; } else
		if (dx> step) { x1 += step; dx-=step; }
	
		if (dy<-step) { y1 -= step; dy+=step; } else
		if (dy> step) { y1 += step; dy-=step; }
		
		if (dz<-step) { z1 -= step; dz+=step; } else
		if (dz> step) { z1 += step; dz-=step; }

		movvob -> SetPositionWorld(x1,y1,z1);
	}
}
//#pragma optimize( "", on )

void spcCMovement::SetFriction		(float _friction, float _friction_rot)
{
	if (friction!=-1.0) friction		= _friction;
	if (friction!=-1.0) friction_rot	= _friction_rot;
};

void spcCMovement::GetFriction	(float& _friction, float& _friction_rot)
{
	_friction = friction;
	_friction_rot = friction_rot;
};

#pragma warning (default : 4244)

