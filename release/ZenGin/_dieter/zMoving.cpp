/******************************************************************************** 
 
     $Workfile:: zMoving.cpp          $                $Date:: 20.12.00 3:04    $
     $Revision:: 14                   $             $Modtime:: 11.12.00 22:35   $
       $Author:: Hildebrandt                                                    $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin_work/_Dieter/zMoving.cpp $
 * 
 * 14    20.12.00 3:04 Hildebrandt
 * 
 * 13    24.11.00 2:09 Hildebrandt
 * 
 * 12    23.11.00 0:47 Hildebrandt
 * 
 * 11    16.11.00 21:43 Hildebrandt
 * 
 * 10    20.09.00 22:31 Rueve
 * intel compilerwarn
 * 
 * 9     21.08.00 17:18 Hildebrandt
 * 
 * 8     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 7     6.07.00 13:45 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 6     15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 5     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 3     10.01.00 15:12 Hildebrandt
 * zenGin 0.85a
 * 
 * 2     12.11.99 1:04 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Hildebrandt $
/// @version $Revision: 14 $ ($Modtime: 11.12.00 22:35 $)


// 

#include <zCore.h>
#include "zMoving.h"
#include <zModel.h >
#include <zVob.h>

#include <zWin32.h>
#include <zInput_Win32.h>

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

static const int D = 190; 
static const mov_typ MOV_MASS		=  60;	// Unser Player bringt 60kg auf die Waage
static		 mov_typ MOV_FORCE_Z	=  60+D;	// Kraft beim Vorwärts gehen	
static		 mov_typ MOV_FORCE_X	=  30+D;	// Kraft beim zur Seite gehen
static		 mov_typ MOV_FORCE_Y	=  30+D;	
static const mov_typ MOV_FRIC_MOV	= 0.2;	// Reibungsfaktor

static const mov_typ MOV_FORCE_ROT	=	2;  // Rotationsbeschleunigung
static const mov_typ MOV_FRIC_ROT	= 0.3;	// Reibungsfaktor Drehen

// TIME CORRECTION VALUES
#define _TIME_CORR_
// Based on ca.16 FPS -> 1 / 16 = 0,0625 ms 
static const int MOV_TIME_CORR		= 64;	// Used in DIV

// Constructor
CMov_Movement :: CMov_Movement ( zCVob *v )
{
	vob		 = v;
	xspeed   = 0; 
	yspeed   = 0;
	zspeed   = 0;
	rotspeed = 0;

	oldtime  = sysGetTime();
};

void CMov_Movement :: IncreaseSpeed (mov_typ d) {
	MOV_FORCE_X = zMax (20, MOV_FORCE_X+d);
	MOV_FORCE_Y = zMax (20, MOV_FORCE_Y+d);
	MOV_FORCE_Z = zMax (20, MOV_FORCE_Z+d);
};

void CMov_Movement :: Movement ()
// normale Fortbewegung
{
	if (!vob) return;

	vob->BeginMovement();

	// Bewegung in Z-Richtung ( Vorwärts / Rückwärts )
	force_z = 0;
	if ((zinput->KeyPressed(KEY_PAD_UP)) || (zinput->KeyPressed(KEY_UP))) {
		force_z += MOV_FORCE_Z;
	} 
	if ((zinput->KeyPressed(KEY_PAD_DOWN)) || (zinput->KeyPressed(KEY_DOWN))) {
		force_z -= MOV_FORCE_Z;
	} 
	
	// Bewegung in X-Richtung ( Links / Rechts )
	force_x = 0;
	if (zinput->KeyPressed(KEY_PAD_PGDN)) {
		force_x += MOV_FORCE_X;
	} 
	if (zinput->KeyPressed(KEY_PAD_END)) {
		force_x -= MOV_FORCE_X;
	} 

	// !!! Nur zwecks Demo !!!
	// Bewegung in Y-Richtung ( Hoch / Runter )
	force_y = 0;
	if (zinput->KeyPressed(KEY_A)) {
		force_y += MOV_FORCE_Y;
	} 
	if (zinput->KeyPressed(KEY_Z)) {
		force_y -= MOV_FORCE_Y; 
	} 

	// Rotation úm eigene Achse ( Links / Rechts drehen )
	force_rot = 0;
	if ((zinput->KeyPressed(KEY_PAD_LEFT)) || (zinput->KeyPressed(KEY_LEFT))) {
		force_rot -= MOV_FORCE_ROT;
	} 
	if ((zinput->KeyPressed(KEY_PAD_RIGHT)) || (zinput->KeyPressed(KEY_RIGHT))) {
		force_rot += MOV_FORCE_ROT;
	} 

	zREAL rotDegree= 0.1F * ztimer.GetFrameTimeF();

	if (zinput->KeyPressed(KEY_LSHIFT))	
	{
/*		if (zinput->KeyPressed(KEY_INS))	vob->RotateWorld (0,1,0, -rotDegree);
		if (zinput->KeyPressed(KEY_DEL))	vob->RotateWorld (0,1,0, rotDegree);
		if (zinput->KeyPressed(KEY_HOME))	vob->RotateWorld (1,0,0, -rotDegree);
		if (zinput->KeyPressed(KEY_END))	vob->RotateWorld (1,0,0, rotDegree);
		if (zinput->KeyPressed(KEY_PGUP))	vob->RotateWorld (0,0,1, -rotDegree);
		if (zinput->KeyPressed(KEY_PGDN))	vob->RotateWorld (0,0,1, rotDegree);
*/
		if (zinput->KeyPressed(KEY_INS))	vob->RotateWorldY (-rotDegree);
		if (zinput->KeyPressed(KEY_DEL))	vob->RotateWorldY (rotDegree);
		if (zinput->KeyPressed(KEY_HOME))	vob->RotateWorldX (-rotDegree);
		if (zinput->KeyPressed(KEY_END))	vob->RotateWorldX (rotDegree);
		if (zinput->KeyPressed(KEY_PGUP))	vob->RotateWorldZ (-rotDegree);
		if (zinput->KeyPressed(KEY_PGDN))	vob->RotateWorldZ (rotDegree);
	} else
	{
		if (zinput->KeyPressed(KEY_INS))	vob->RotateLocal (0,1,0, -rotDegree);
		if (zinput->KeyPressed(KEY_DEL))	vob->RotateLocal (0,1,0, rotDegree);
		if (zinput->KeyPressed(KEY_HOME))	vob->RotateLocal (1,0,0, -rotDegree);
		if (zinput->KeyPressed(KEY_END))	vob->RotateLocal (1,0,0, rotDegree);
		if (zinput->KeyPressed(KEY_PGUP))	vob->RotateLocal (0,0,1, -rotDegree);
		if (zinput->KeyPressed(KEY_PGDN))	vob->RotateLocal (0,0,1, rotDegree);
	};
	
	if (!zinput->KeyPressed(KEY_RSHIFT)) 
	{ 
		if (zinput->KeyPressed(KEY_PLUS))	IncreaseSpeed (+50);
		if (zinput->KeyPressed(KEY_MINUS))	IncreaseSpeed (-50);
	};
	
	zBOOL modelMode		= FALSE; 
	zCVisual *vis		= vob->GetVisual();
//	if (vis) modelMode	= (vis->GetClassDef()==zCModel::GetStaticClassDef());
	if (vis) modelMode	= vob->GetCharacterClass()>=zCVob::zVOB_CHAR_CLASS_PC;

	mov_typ fric_corr;
	now       = sysGetTime();
	time_corr = double(now - oldtime) / MOV_TIME_CORR;
	oldtime   = now;

	fric_corr = MOV_FRIC_MOV * time_corr;
//	if (!modelMode) {
		xspeed   += (force_x / MOV_MASS) * time_corr - fric_corr * xspeed; 
		yspeed   += (force_y / MOV_MASS) * time_corr - fric_corr * yspeed; 
		zspeed   += (force_z / MOV_MASS) * time_corr - fric_corr * zspeed; 
//	};
	rotspeed += force_rot * time_corr - MOV_FRIC_ROT * rotspeed * time_corr;
	
	if (!modelMode) 
	{
		// Move Vob
		vob->MoveLocal		(xspeed,yspeed,zspeed);
		vob->RotateWorld	(0,1,0,(rotspeed * time_corr));
	};
	vob->EndMovement();
}

// disable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 
