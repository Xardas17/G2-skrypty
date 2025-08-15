/******************************************************************************** 
 
     $Workfile:: oNpc_Move.cpp        $                $Date:: 24.04.01 17:33   $
     $Revision:: 65                   $             $Modtime:: 22.04.01 20:46   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oNpc_Move.cpp $
 * 
 * 65    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 64    15.03.01 17:01 Wohlers
 * 
 * 63    15.03.01 17:00 Wohlers
 * 
 * 62    15.02.01 18:37 Wohlers
 * 
 * 61    15.02.01 2:21 Wohlers
 * 
 * 60    14.02.01 18:59 Wohlers
 * 
 * 59    14.02.01 18:13 Edenfeld
 * 
 * 58    13.02.01 20:26 Wohlers
 * 
 * 57    13.02.01 17:15 Wohlers
 * 
 * 56    12.02.01 19:23 Wohlers
 * Wegsuche : Bessere Reaktion auf Schraegen (Diego-Haenger bei
 * Spielstart)
 * 
 * 55    10.02.01 1:43 Wohlers
 * Wegfindung Kantenhaenger Fix
 * 
 * 54    9.02.01 16:33 Wohlers
 * EV_Strafe : Beim Strafen das Drehen bei gedrueckter ALT+Taste
 * verhindert.
 * 
 * 53    9.02.01 15:56 Edenfeld
 * 
 * 52    8.02.01 19:39 Edenfeld
 * 
 * 51    8.02.01 17:36 Wohlers
 * 
 * 50    7.02.01 18:33 Moos
 * 
 * 49    6.02.01 1:50 Wohlers
 * 
 * 48    6.02.01 0:33 Wohlers
 * 
 * 47    1.02.01 18:04 Wohlers
 * 
 * 46    30.01.01 21:28 Wohlers
 * 
 * 45    30.01.01 0:34 Wohlers
 * 
 * 44    29.01.01 17:08 Wohlers
 * 
 * 43    29.01.01 16:27 Keskenti
 * 
 * 42    25.01.01 21:59 Wohlers
 * 
 * 41    18.01.01 16:53 Keskenti
 * 
 * 40    17.01.01 18:00 Wohlers
 * 
 * 39    16.01.01 10:56 Moos
 * 
 * 38    15.01.01 16:32 Moos
 * 
 * 37    12.01.01 16:36 Wohlers
 * 
 * 36    12.01.01 12:38 Moos
 * 
 * 35    11.01.01 20:38 Wohlers
 * 
 * 34    11.01.01 15:55 Moos
 * 
 * 33    9.01.01 20:24 Wohlers
 * 
 * 32    8.01.01 14:59 Wohlers
 * 
 * 31    4.01.01 18:27 Keskenti
 * 
 * 30    20.12.00 17:13 Moos
 * 
 * 29    20.12.00 0:03 Wohlers
 * 
 * 28    19.12.00 17:36 Wohlers
 * 
 * 27    18.12.00 20:57 Wohlers
 * 
 * 26    18.12.00 16:41 Wohlers
 * 
 * 25    18.12.00 14:37 Wohlers
 * 
 * 24    14.12.00 20:46 Wohlers
 * 
 * 23    1.12.00 16:55 Wohlers
 * 
 * 22    30.11.00 15:57 Wohlers
 * 
 * 21    21.11.00 14:13 Wohlers
 * 
 * 20    17.11.00 16:53 Wohlers
 * 
 * 19    15.11.00 17:19 Wohlers
 * 
 * 18    15.11.00 13:15 Wohlers
 * 
 * 17    9.11.00 16:55 Wohlers
 * 
 * 16    9.11.00 16:54 Wohlers
 * 
 * 15    7.11.00 18:49 Wohlers
 * 
 * 14    7.11.00 15:15 Wohlers
 * 
 * 13    6.11.00 19:01 Wohlers
 * 
 * 12    6.11.00 18:18 Wohlers
 * 
 * 11    1.11.00 16:13 Wohlers
 * 
 * 10    31.10.00 20:27 Keskenti
 * 
 * 9     31.10.00 13:14 Wohlers
 * 
 * 8     30/10/00 13:13 Luesebrink
 * 
 * 7     27.10.00 17:06 Keskenti
 * 
 * 6     27.10.00 17:01 Wohlers
 * 
 * 5     26.10.00 18:30 Wohlers
 * 
 * 4     26.10.00 14:45 Wohlers
 * 
 * 3     12.10.00 20:01 Wohlers
 * 
 * 2     12.10.00 19:18 Keskenti
 * 
 * 1     12.10.00 16:20 Keskenti
 * 
 *********************************************************************************/

// ******************
// oCNPC - Move
// ******************

#include "zCore.h"

#include "zWaynet.h"
#include "zEventMan.h"
#include "zInput.h"
#include "zPhysics.h"
#include "zMorphMesh.h"

#include "oNpc.h"
#include "oNpcMessages.h"
#include "oAnictrl.h"
#include "oAIHuman.h"
#include "oMobInter.h"
#include "oWaynet.h"
#include "oGame.h"
#include "oFocus.h"

enum { NPC_OBST_NONE, NPC_OBST_FALL, NPC_OBST_WALL, NPC_OBST_WALL_CLIMB, NPC_OBST_CHASM, NPC_OBST_NPC, NPC_OBST_LADDER, NPC_OBST_STAIRS, NPC_OBST_MOBINTER, NPC_OBST_JUMP };

/*--------------------------------------------------------------------------

    oCNpc::CanDive()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: CanDive()
{
	// SwimTime > 0;
	return ((divetime > 0) || (divetime == ANI_TIME_INFINITE)); 
}

/*--------------------------------------------------------------------------

    oCNpc::CanSwim()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: CanSwim()
{	
	// SwimTime > 0;
	return ((swimtime > 0) || (swimtime == ANI_TIME_INFINITE)); 
}

/*--------------------------------------------------------------------------

    oCNpc::GetClimbRange()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: GetClimbRange()
{
	return 500.0f; // 5m
}

/*--------------------------------------------------------------------------

    oCNpc::GetTurnSpeed()

    29-Jan-01       [Roman Keskenti]

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: GetTurnSpeed()
{
	return this->IsAPlayer() ? 0.1f : this->speedTurn;
}

/*--------------------------------------------------------------------------

    oCNpc::GetJumpRange()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: GetJumpRange()
{
	return 300.0f; // 5m
}

int oCNpc :: RbtChooseChasmAction (const zVEC3& pos, const zVEC3& dir)
// Chasm wurde detected...
// Ergebnis kann sein :
// a) nicht zu ueberwinden	: NPC_OBST_CHASM
// b) ueberspringabr		: NPC_OBST_JUMP
// c) fallenlassen ok		: NPC_OBST_FALL
{
	zVEC3 cdNormal;
	zREAL floorDist = GetFallDownHeight() + 100;	
	
	// Chasm wurde breits detected, darum hier keine Abfrage mehr, 
	// dient nur zum Ermitteln der FloorDist
	zBOOL chasmDetected = anictrl->DetectChasm(pos, dir, floorDist, cdNormal);
	if (!chasmDetected) return NPC_OBST_NONE;

	// fallenlassen vorziehen, falls Hoehe gering -> kein Test mehr auf Jump ! 
	if (floorDist < GetFallDownHeight() * 0.5) {
		return NPC_OBST_FALL;
	}

	// Jumpable ?
	zREAL dist = GetJumpRange();
	
	// Freie Sicht zum Zielpunkt ?
	if (anictrl->CanJump() && (dist>0.0f)) {
		zVEC3 posDown;
//		zVEC3 pos		= GetPositionWorld();
//		zVEC3 dir		= GetAtVectorWorld() * dist;

		if (!GetHomeWorld()->TraceRayFirstHit(pos,dir, this, zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_NO_CD_DYN | zTRACERAY_VOB_IGNORE_CHARACTER)) {
			// Weg frei, Test nach unten.
			posDown		= pos + dir;
			zVEC3 dirDown (0,-GetFallDownHeight()*0.5f,0);
			if (GetHomeWorld()->TraceRayFirstHit(posDown,dirDown,this,zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_NO_CD_DYN | zTRACERAY_VOB_IGNORE_CHARACTER)) {
			

				return NPC_OBST_JUMP;
			}
		}
	}
	// Nicht jumpable - fallenlassen ok ? 
	if (floorDist > GetFallDownHeight()) {
		return NPC_OBST_CHASM;
	} else {
		return NPC_OBST_FALL;
	}
	return NPC_OBST_NONE;
};

/*--------------------------------------------------------------------------

    oCNpc::CanGo()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
int	oCNpc :: CanGo (zREAL len, zVEC3 &cdNormal)
{
	//if (rbt.obstVob) rbt.obstVob->SetDrawBBox3D(FALSE);
	
	rbt.obstVob			= NULL;
	rbt.isObstVobSmall	= FALSE;
	
	// ******************************
	// Irgendwas im Kollisionreport ?
	// ******************************
	oCAIHuman* ai = zDYNAMIC_CAST<oCAIHuman>(GetAI());
	if (!ai) return NPC_OBST_NONE;

	// Stairs sind kein Hindernis, Abfrage hier schon, weil sont am Ende der Treppe 
	// ein JumpUpMid erfolgt.
	if (zDYNAMIC_CAST<zCVobStair>(ai->GetInterferenceReport().spacingRayFrontVob)) return NPC_OBST_NONE;

	if ((ai->GetInterferenceReport().blocking.floorTooHigh) || (ai->GetInterferenceReport().blocking.floorTooSteepUp) || (ai->GetInterferenceReport().blocking.floorTooSteepDown)) {
		int height = ai->CanJumpLedge();
		
		if ((height>0) && (height<=2)) {
			
			// 0 - 2 JumpUpMid
			return NPC_OBST_WALL_CLIMB;
		
		} else if ((height==3) && (!state.IsInRoutine() || IsAPlayer())) {

			// 3 - JumpUp (High)
			return NPC_OBST_WALL_CLIMB;		
		
		} else {		
			
			if (ai->GetInterferenceReport().blocking.floorTooSteepDown) {
				// Schraege runter....
				int result = RbtChooseChasmAction(GetPositionWorld(),GetAtVectorWorld()*len);			
				if (result!=NPC_OBST_NONE) return result;
			
			} else {
				// Schraege rauf...
				// return NPC_OBST_WALL;
			}

			if (ai->GetInterferenceReport().spacingRayFrontPoly) cdNormal = ai->GetInterferenceReport().spacingRayFrontPoly->GetPlane().normal;	else
			if (anictrl->GetFloorPoly())	cdNormal = anictrl->GetFloorPoly()->GetPlane().normal; 			
			else					cdNormal = GetAtVectorWorld();
			return NPC_OBST_WALL;
		}
	}
	
	if (ai->GetInterferenceReport().blocking.lowCeiling) {
		
		// Welche normale Benutzen ?
		return NPC_OBST_WALL;
	
	} else if (ai->GetInterferenceReport().spacingRayFrontPoly) {
		
		cdNormal = ai->GetInterferenceReport().spacingRayFrontPoly->GetPlane().normal;
		
		if (ai->CanWalkOnPoly(cdNormal))	return NPC_OBST_NONE;
		
		return NPC_OBST_WALL;						
	}

	// Schon ein HindernisVob von der AI - gefunden ?
	if (!rbt.obstVob) {
		
		// ****************
		// Wand in Front ?
		// ****************
		
		// Mehr Power beim Tauchen.
		if (anictrl->GetActionMode()==ANI_ACTION_SWIM) {
			// FIXME : Das geht auch besser, oder ?
			// Beim Schwimmen muss Abstand geringer sein, in der er Hindernisse erkennt, 
			// da sonst ein DetectClimbUpLedge immer failed und NSC niemals aus dem Wasser steigt.
			len /= 2;
		}
		
		// **********************************************************************
		// HIndernis testen....
		// **********************************************************************

		// * Small Object... *
		// Optimize : small NSC dont need to test this.
		zBOOL hit			= RbtGetSmallObstacle(GetAtVectorWorld()*len,rbt.obstVob,cdNormal);
		rbt.isObstVobSmall	= hit;
		// Treppe als kleines Objekt gefunden -> hier raus, da sont beim Treppenende immer
		// ein ClimbLedge ausgefuehrt wird -> sieht panne aus.
		if (zDYNAMIC_CAST<zCVobStair>(rbt.obstVob)) return FALSE;

		// * Big Object... *
		// NSCs liefern keinen Hit, sehr wohl aber wird die "obstVob"-Var gefüllt, 
		// damit entsprechende Wahrnehmung aktiviert werden kann.
		if (!hit) hit		= RbtGetObstacle(GetPositionWorld(),GetAtVectorWorld()*len,rbt.obstVob,cdNormal);

		// **************************************************
		// Schon ein Hindernis von der zCAIPlayer ermittelt ?
		// **************************************************
		if (!hit && ai->GetInterferenceReport().spacingRayFrontVob) {
			
			// Kann nur kleines Objekt sein, da RbtGetObstacle bereits 
			if (!zDYNAMIC_CAST<oCNpc> (ai->GetInterferenceReport().spacingRayFrontVob)) { 
				
				cdNormal	= -GetAtVectorWorld();
				rbt.obstVob = ai->GetInterferenceReport().spacingRayFrontVob;
	
				//if (rbt.obstVob) rbt.obstVob->SetDrawBBox3D(TRUE);
				return NPC_OBST_WALL;					
			} 
		}

		if (hit) {
//			if ((anictrl->GetActionMode()==ANI_ACTION_SWIM) && anictrl->Swim_CanClimbLedge()) {
//				return NPC_OBST_WALL_CLIMB;
//			} else 
			
			if (!rbt.obstVob) {

				// Statischer Poly Hit - kein Vob gefunden.
				if ((rbt.frameCtr & 1) && ai->CanJump()) {
				
					// Nur jeden zweiten Frame checken.
					int height = ai->CanJumpLedge();

					if ((height>0) && (height<=2)) {
						return NPC_OBST_WALL_CLIMB;
					
					} else if ((height==3) && (!state.IsInRoutine() || IsAPlayer())) {
						// Climben nur, wenn TA nicht aktiv ist ?
						return NPC_OBST_WALL_CLIMB;		
					
					}
				}
				// Schraege, begehbar ?
				if (ai->CanWalkOnPoly(cdNormal))	return NPC_OBST_NONE;		
			}
			
			//if (rbt.obstVob) rbt.obstVob->SetDrawBBox3D(TRUE);
			return NPC_OBST_WALL;
		}
	} 

	// **************************
	// Abgrund in Front ?
	// Nur falls nicht im Wasser
	// **************************

	if (ai->GetInterferenceReport().blocking.floorTooLow)
	if ((ai->GetWaterLevel()==0) && !GetModel()->GetIsFlying() && ai->CanJump()) {

//		zERR_WARNING("U: RBT: Chasm detected.");
		cdNormal = -GetAtVectorWorld();
		if (RbtIsDirectionValid(cdNormal)) {
			// patch 1.08 : Abgrundhandling Fix 
			int result = RbtChooseChasmAction(GetPositionWorld(),GetAtVectorWorld()*len);
			if (result == NPC_OBST_NONE) return NPC_OBST_CHASM;
			else return result;
		} else {
			return NPC_OBST_CHASM;
		}
	};

	// To Do :
	// ****************
	// Water ?
	// ****************

	return NPC_OBST_NONE;
}

/*--------------------------------------------------------------------------

    oCNpc::GetAngle()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: GetAngle (zCVob *to)
{
	if (!to) return 0;
	zVEC3 v1	= GetAtVectorWorld();
	zVEC3 v2	= (to	-> GetPositionWorld() - GetPositionWorld());
	v1.n[1]		= 0;
	v2.n[1]		= 0;
	return Alg_Rad2Deg ( Alg_AngleRad (v1,v2) );
}

/*--------------------------------------------------------------------------

    oCNpc::GetAngles()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

    7 -Feb-01       [Moos]

                      Den Umdreh-Fix noch mehr spezialisiert

--------------------------------------------------------------------------*/ 
void oCNpc :: GetAngles(zVEC3& pos, zREAL& azi, zREAL& elev)
{
	zVEC3 atVec = GetAtVectorWorld();
	zREAL azi2,elev2;
	// Blickrichtung des aktuellen NSCs
	// Im Sitzen muss diese gedreht werden, da AtVector nicht korrekt
//	if (GetBodyState()==BS_SIT) atVec = -atVec; // [Moos] der Fehler scheint irgendwo anders korrigiert worden zu sein.

	if (GetBodyState()==BS_SIT && (GetModel()->IsAniActive("S_BENCH_S1") || GetModel()->IsAniActive("S_THRONE_S1"))) atVec = -atVec; // [Moos] OK, jetzt hab ichs kapiert: bei den angegebenen anis (aber NICHT bei allen anderen Sitz-Animationen) zeigt die Blickrichtung des NCSs in die andere Richtung. AAARRRGGH!

	Alg_CalcAziElevUnit	(atVec,azi2,elev2);
	// Position des Objektes -> Normalize, weil sonst Fehler in Alg_CalcAziElev auftreten könnte
	// yy > 1.0F -> Floating Point Error -> Wert in elev nicht vorherbestimmt.
	zVEC3	toVec  = pos;
			toVec -= GetPositionWorld();
			toVec	.NormalizeApprox();
	Alg_CalcAziElevUnit	(toVec, azi, elev);
	azi		-= azi2;
	elev	-= elev2;
	azi		=  Alg_Rad2Deg(azi);
	if (azi<-180)	azi  += 360; else
	if (azi> 180)	azi  -= 360;
	elev	=  Alg_Rad2Deg(elev);
	if (elev<-180)	elev += 360; else
	if (elev> 180)  elev -= 360;
}

/*--------------------------------------------------------------------------

    oCNpc::GetAngles()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: GetAngles(zCVob *to,zREAL &azi, zREAL &elev)
{
	GetAngles(to->GetPositionWorld(),azi,elev);
}

/*--------------------------------------------------------------------------

    oCNpc::GetDistanceToPos2()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: GetDistanceToPos2 (zVEC3& pos, zBOOL dim2)
{
	zVEC3 p1		= GetPositionWorld();
	zVEC3 p2		= pos;
	// Wenn Waypoint innerhalb der BBox-Höhe des NSCs, dann wird Y-Komponente angeglichen
	// 2 Dimensionen berücksichtigen !
	// FIXME : Besser -> Einmal Größe des Models ermitteln und damit rechnen !
	zTBBox3D bbox	= GetBBox3DWorld();
	if (dim2 || zInRange(pos[VY],bbox.mins[VY],bbox.maxs[VY])) {
		p2[VY] = p1[VY];
	}
	return (p1-p2).Length2();
}

/*--------------------------------------------------------------------------

    oCNpc::GetFalldownHeight()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: GetFallDownHeight()
{
	if ( this->overrideFallDownHeight ) return 0.0f;
	else								return fallDownHeight;
}

/*--------------------------------------------------------------------------

    oCNpc::GetRbtObstacleVob()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zCVob* oCNpc :: GetRbtObstacleVob ()
{
	return rbt.obstVob;
}

/*--------------------------------------------------------------------------

    oCNpc::GetVecNormalFromBBox()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zVEC3 oCNpc :: GetVecNormalFromBBox (zCVob* vob, zVEC3& pos)
// ToDo Optimze
{
	int nr			= 0;

	pos[VY]			= 1;
	zVEC3 cdNormal,fpos1,fpos2;
	zTBBox3D bbox	= vob->GetBBox3DWorld();
	zVEC3 point1	= bbox.mins;	point1[VY] = 1;				// rechts / unten / vorne
	zVEC3 point4	= bbox.maxs;	point4[VY] = 1;				// links  / oben  / hinten
	zVEC3 point2	= point1;		point2[VX] = point4[VX];	// links  / unten / vorne
	zVEC3 point3	= point4;		point3[VX] = point1[VX];

	// Geringste Entfernung holen
	zREAL dist		= 0.0f;
	zREAL maxDist	= zREAL_MAX;
	
	// Front
	dist = (point1 - pos).Length2() + (point2 - pos).Length2();		// front
	if (dist<maxDist) {
		fpos1	= point1; fpos2 = point2;
		maxDist = dist;
		nr		= 0;
	}
	
	// Back
	dist = (point3 - pos).Length2() + (point4 - pos).Length2();		// back
	if (dist<maxDist) {
		fpos1	= point3; fpos2 = point4;
		maxDist = dist;
		nr		= 1;
	}
	
	// Left
	dist = (point4 - pos).Length2() + (point2 - pos).Length2();		// left
	if (dist<maxDist) {
		fpos1	= point4; fpos2 = point2;
		maxDist = dist;
		nr		= 2;
	} 
	
	// Right
	dist = (point1 - pos).Length2() + (point3 - pos).Length2();		// right
	if (dist<maxDist) {
		fpos1	= point1; fpos2 = point3;
		maxDist = dist;
		nr		= 3;
	}
	
	switch (nr) {
	case 0 : zERR_WARNING("U:RBT: Front side"); break;
	case 1 : zERR_WARNING("U:RBT: Back side"); break;
	case 2 : zERR_WARNING("U:RBT: Left side"); break;
	case 3 : zERR_WARNING("U:RBT: Right side"); break;
	}

	// Calculate cdNormal
	cdNormal = zVEC3(0,1,0) ^ (fpos1 - fpos2);
//	if (nr==3) cdNormal = -cdNormal;
	cdNormal.NormalizeApprox();
//	zlineCache.Line3D (vob->GetPositionWorld(),vob->GetPositionWorld()+cdNormal*500,GFX_WHITE);
	return cdNormal;
}

/*--------------------------------------------------------------------------

    oCNpc::SetFalldownDamage()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: SetFallDownDamage	(int fd)
{
	fallDownDamage = fd;
}

/*--------------------------------------------------------------------------

    oCNpc::SetFalldownHeight()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: SetFallDownHeight	(zREAL fh)
{
	fallDownHeight = fh;
}

/*--------------------------------------------------------------------------

    oCNpc::SetRoute()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: SetRoute (zCRoute *rt)
{
	if (route) delete route;
	route = rt;
}

/*--------------------------------------------------------------------------

    oCNpc::CreateFallDamage()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: CreateFallDamage( zREAL dist )
{
	//
	//	FILL DAMAGE DESCRIPTOR
	//
	oCNpc::oSDamageDescriptor descDamage;

	descDamage.fDamageTotal	 = ((dist + 50.0f - GetFallDownHeight()) / 100) * fallDownDamage;
	descDamage.enuModeDamage = oEDamageType_Fall;
	descDamage.dwFieldsValid = oEDamageDescFlag_DamageType | oEDamageDescFlag_Damage;

	//
	//	SEND DAMAGE MESSAGE
	//
	oCMsgDamage* pMsg = zNEW( oCMsgDamage )( oCMsgDamage::EV_DAMAGE_ONCE, descDamage );
	this->GetEM()->OnMessage( pMsg, this );

	//
	//	OUTPUT DEBUG MESSAGE
	//
	zCView::PrintDebug("< Dist:"+zSTRING(int(dist))+"/ Dam:"+zSTRING( (int) descDamage.fDamageTotal )+">\n");
}

/* ----------------------------------------------------------------------
	
	oCNpc :: Fleeing()

	24.08.2000	[Moos]	

					auf zNEW umgestellt

    11-Oct-00	[Roman Keskenti]

					Moved for useage with oNpc_Move.h

   ---------------------------------------------------------------------- */
void oCNpc :: Fleeing( void )
{
	//
	//	ERSTMAL WAFFE WEGSTECKEN ... 
	//
/*	if ( GetWeaponMode() != NPC_WEAPON_NONE )
	{
		GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),this);
	}
*/

	//
	//	DANN BESTE RICHTUNG ERMITTELN
	//
	ThinkNextFleeAction();
}

/* ----------------------------------------------------------------------
	
	oCNpc :: ThinkNextFleeAction()

    11-Oct-00	[Roman Keskenti]

					Moved for useage with oNpc_Move.h

   ---------------------------------------------------------------------- */
int oCNpc :: ThinkNextFleeAction()
{
	//
	//	GEGNER ERMITTELN
	//
	oCNpc* pNpcFlee = this->GetEnemy();
	zCVob* pVobFlee = zDYNAMIC_CAST< zCVob > (pNpcFlee);

	//
	//	IST DER GEGNER AUSSERHALB DER SICHTWEITE (ODER KEIN GEGNER MEHR)?
	//
	if ( ( ! pVobFlee) || ( ! this->FreeLineOfSight( pVobFlee ) ) )
	{
		//
		//	STOP -> RAUS HIER
		//
		return 0;
	}

	//
	//	HATTE ICH SCHON EINEN PUNKT GEFUNDEN ... 
	//
	if ( this->foundFleePoint )
	{
		//
		//	SCHON DORT?
		//
		if ( this->reachedFleePoint )
		{
			//
			//	JA -> FLAGS LOESCHEN -> NEACHSTEN WEGPUNKT BESTIMMEN
			//
			this->foundFleePoint   = FALSE;
			this->reachedFleePoint = FALSE;

			return 0;
		}
		else
		{
			//
			//	JA -> DANN WEITER DORTHIN UND RAUS HIER
			//
			zVEC3 posSelf ;
			this->GetPositionWorld( posSelf );

			//
			//	ANGEKOMMEN?
			//
			if ( posSelf == posFlee ) 
			{
				//
				//	FERTIG
				//
				this->reachedFleePoint = TRUE;

				return 0;
			}

			//
			//	LAUF DORT HIN
			//
			rbt.stand				 = FALSE;
			rbt.standIfTargetReached = TRUE;
			rbt.targetReached		 = this->reachedFleePoint;
			rbt.maxTargetDist		 = 100 * 100;				// 1m
			RobustTrace				 ();

			return 0;

		}
		return 0;
	}

	//
	//	VECTOR ZUM GEGNER BESTIMMEN 
	//
	zVEC3 posEnemy;
	zVEC3 posSelf ;
	zVEC3 vecEnemy;

	pNpcFlee->GetPositionWorld	( posEnemy );
	this->GetPositionWorld		( posSelf  );

	vecEnemy  = posEnemy;
	vecEnemy -= posSelf ;

	//
	//	VERDOPPELE DIE ENTFERNUNG ZUM GEGNER UND KEHRE DIE RICHTUNG UM ( VEC *= -2 )
	//
	this->vecFlee  = vecEnemy;
	this->vecFlee *= -2;		// -> FLUCHT NACH HINTEN

	//
	//	LOOP: NEAHESTEN WEGPUNKT HOHLEN	(DER NICHT IN DER LISTE DER SCHON BEWERTETEN PUNKTE IST)
	//
	zCWaypoint* pWaypointNearestToDestination = NULL;
	int			nIterations					  = 1;

	while( ( pWaypointNearestToDestination == NULL ) && ( nIterations++ < 5) )
	{
		//
		//	HOHLE DEN NEAREST WAYPOINT RELATIV ZUM VECTOR
		//
		pWaypointNearestToDestination = this->GetHomeWorld()->GetWayNet()->GetNearestWaypoint( posSelf + vecFlee );

		//
		//	IST DER WAYPOINT SICHTBAR? ... UND LAUF NICHT WIEDER ZUM SELBEN WAYPOINT, AN DEM DU SCHON STEHST
		//
		if ( ( pWaypointNearestToDestination ) && ( pWaypointNearestToDestination != this->waypointFlee ) ) 
		{
			//
			//	JA -> DEN NEHMEN WIR!	-> END LOOP
			//
			this->waypointFlee = pWaypointNearestToDestination;
			this->GetEM() -> OnMessage( zNEW(oCMsgMovement)(oCMsgMovement::EV_GOROUTE, pWaypointNearestToDestination->GetName() ), this );
			
		//	this->anictrl			= this->GetAnictrl();
		//	this->posFlee			= pWaypointNearestToDestination->GetPositionWorld();
		//	this->foundFleePoint	= TRUE;
		//	this->reachedFleePoint	= FALSE;
		//	this->RbtUpdate			( posFlee, NULL );

			return 0;
		}
		else
		{
			//
			//	NEIN -> NOCHMAL DEN ZWEITBESTEN VERSUCHEN
			//
			pWaypointNearestToDestination = this->GetHomeWorld()->GetWayNet()->GetSecNearestWaypoint( vecFlee );

			//
			//	... UND LAUF NICHT WIEDER ZUM SELBEN WAYPOINT, AN DEM DU SCHON STEHST
			//
			if ( pWaypointNearestToDestination == this->waypointFlee ) continue;

			//
			//	IST DER WAYPOINT SICHTBAR?
			//
			if ( pWaypointNearestToDestination ) 
			{
				//
				//	JA -> DEN NEHMEN WIR!	-> END LOOP
				//
				this->waypointFlee = pWaypointNearestToDestination;
				this->GetEM() -> OnMessage( zNEW(oCMsgMovement)(oCMsgMovement::EV_GOROUTE, pWaypointNearestToDestination->GetName() ), this );
				
			//	this->anictrl			= this->GetAnictrl();
			//	this->posFlee			= pWaypointNearestToDestination->GetPositionWorld();
			//	this->foundFleePoint	= TRUE;
			//	this->reachedFleePoint	= FALSE;
			//	this->RbtUpdate			( posFlee, NULL );

				return 0;
			}
		}

		//
		//	KEINEN WAYPOINT GEFUNDEN 
		//

		vecFlee  *= -1;							// -> IN ANDERER RICHTUNG SUCHEN
		vecFlee  *= (1.0f/(float) nIterations); // -> ABSTAND VERRINGERN
	}

	//
	//	IMMER NOCH KEINEN WEGPUNKT GEFUNDEN ?
	//
	if ( (pWaypointNearestToDestination == NULL) && ( nIterations >= 5 ) )
	{
		//
		//	JA -> EINFACH NUR WEG VON HIER
		//
		this->vecFlee  = vecEnemy;
		this->vecFlee *= -2;					// -> FLUCHT NACH HINTEN

		this->anictrl			= this->GetAnictrl();
		this->waypointFlee		= NULL;
		this->foundFleePoint	= TRUE;
		this->reachedFleePoint	= FALSE;
		this->posFlee			= posSelf + vecFlee;
		this->RbtUpdate			( posFlee, NULL );
	}
	
	return 0;
}

/*--------------------------------------------------------------------------

    oCNpc::Follow()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: Follow ()
{
//	oCNpc* leader = GetLeader();
//	if (leader) {
//		RbtUpdate(leader->GetPositionWorld(),leader);
//		if (RobustTrace()) anictrl->_Stand();
//	}
}

/*--------------------------------------------------------------------------

    oCNpc::ResetPos()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: ResetPos(zVEC3 &p)
{
	if (IsDead() && !IsMonster())	GetAnictrl() ->SetConfigDoSurfaceAlign(zCAIPlayer::zMV_SURFACE_ALIGN_NONE);
	Interrupt		    ();
	zVEC3 vec = GetAtVectorWorld();
	SetCollDet		    (FALSE);
	SetPositionWorld    (p);

	if (zinput->KeyPressed(KEY_LALT))
		ResetRotationsWorld();	

	attribute[NPC_ATR_HITPOINTS] = attribute[NPC_ATR_HITPOINTSMAX];
	// [BENDLIN] Addon
	attribute[NPC_ATR_MANA] = attribute[NPC_ATR_MANAMAX];
	if (IsSelfPlayer()) 
		StopFaceAni(NPC_TALK_ANI);
	
	GetModel		    ()->StopAnisLayerRange(1,1000);
	GetAnictrl		    ()->Reset();
	GetModel		    ()->StartAni( GetAnictrl()->_s_walk );
	GetAnictrl		    ()->SetActionMode(ANI_ACTION_WALK);
	ClearEM			    ();
//	GetAnictrl		    ()->SetDoOops(FALSE);
	SetBodyState	    (BS_STAND);
	SetCollDet		    (TRUE);
	SetSleeping		    (FALSE);
	GetRigidBody	    ()->ApplyImpulseCM(vec * 30000);      // [Moos] 11.1.01 Statt ApplyForce. Ist begriffsmässig besser.
	GetModel		    ()->SetAniTransScale(zVEC3(1,1,1));
	SetMovLock		    (FALSE);
	if (IsSelfPlayer()) 
	{
		oCNpcFocus :: focus -> SetFocusMode(FOCUS_NORMAL);
	};
	CheckModelOverlays();	
	state.curState.valid	= FALSE;
	state.curState.index	= -1;
	state.curState.name.Clear();
	state.curState.prgIndex	= -1;

	//
	//	CODECHANGE [ROMAN]
	//
	divectr = divetime;
	//
	//	CODECHANGE [ROMAN] END
	//
	
}

/*--------------------------------------------------------------------------

    oCNpc::EmergencyResetPos()

    08-Feb-01       [Edenfeld] erzeugt

--------------------------------------------------------------------------*/ 
void oCNpc :: EmergencyResetPos(zVEC3 &p)
{
	const zREAL MAX_DIST_TO_FLOOR_POS = 200.0f;
	const zREAL CHECK_RAY_DIST_DOWN	  = 1000000.0f;			// 10 km sollten reichen
	const zREAL CHECK_RAY_DIST_UP	  = 10000.0f;			
	const zREAL MAX_FORCED_PUSH_HEIGHT= 150.0f;
	const zREAL FORCED_IMPULSE		  = 3000.0f;

	zREAL pushHeight				  = MAX_FORCED_PUSH_HEIGHT;
	zBOOL groundCheckFailed			  = FALSE;
	zBOOL heightCheckFailed			  = FALSE;
	
	if (!GetHomeWorld()) return;	

	// diesen code nur ausführen, wenn der spieler in einem sinnvollen
	// Abstand zum Boden und zur Decke ist

	// distanz zum Boden checken
	if (GetHomeWorld()->TraceRayNearestHit( p, p+ (CHECK_RAY_DIST_DOWN * zVEC3(0,-1,0)), this, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_NO_CD_DYN ) ) 
	{
		zREAL distToFloorPos = (GetHomeWorld()->traceRayReport.foundIntersection - p).Length();
		if (distToFloorPos>MAX_DIST_TO_FLOOR_POS) groundCheckFailed = TRUE;
	}
	else
	{
		// kein punkt gefunden, mögliche Ursache ist: Spieler ist durchs Mesh gefallen
		// in diesem Fall wird der Spieler wieder an den Startpunkt teleportiert
		p = ogame->GetStartPos(); 
	};

	
	if		(GetHomeWorld()->TraceRayNearestHit( p, p+ (CHECK_RAY_DIST_UP * zVEC3(0,1,0)), this, zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_NO_CD_DYN ) ) 
	{
		// distanz zur Decke checken
		if (GetBBox3DWorld().maxs[VY] >= GetHomeWorld()->traceRayReport.foundIntersection[VY]) 
		{
			// Typ steckt vermutlich in der Decke
			heightCheckFailed = TRUE;
		}
		else if (GetBBox3DWorld().maxs[VY]+MAX_FORCED_PUSH_HEIGHT >= GetHomeWorld()->traceRayReport.foundIntersection[VY]) 
		{
			// nicht genügend platz, um die höhenveränderung durchzuführen
			pushHeight		  = 0;
			heightCheckFailed = TRUE;
			
		};
	}

	if (groundCheckFailed && !heightCheckFailed) return;
    
	if (IsDead() && !IsMonster())	GetAnictrl() ->SetConfigDoSurfaceAlign(zCAIPlayer::zMV_SURFACE_ALIGN_NONE);

	Interrupt		    ();
	zVEC3 vec = GetAtVectorWorld();
	SetCollDet		    (FALSE);
	SetPositionWorld    (p+zVEC3(0,pushHeight,0));
	ResetRotationsWorld	();	
	GetModel		    ()->StopAnisLayerRange(1,1000);
	GetAnictrl		    ()->Reset();
	GetModel		    ()->StartAni( GetAnictrl()->_s_walk );
	GetAnictrl		    ()->SetActionMode(ANI_ACTION_WALK);
	ClearEM			    ();
	SetBodyState	    (BS_STAND);
	SetCollDet		    (TRUE);
	SetSleeping		    (FALSE);
	GetRigidBody	    ()->ApplyImpulseCM(vec * FORCED_IMPULSE);      // [Moos] 11.1.01 Statt ApplyForce. Ist begriffsmässig besser.
	GetModel		    ()->SetAniTransScale(zVEC3(1,1,1));
	SetMovLock		    (FALSE);
	
	if (IsSelfPlayer()) 
	{
		oCNpcFocus :: focus -> SetFocusMode(FOCUS_NORMAL);
	};

	CheckModelOverlays();	
}


/*--------------------------------------------------------------------------

    oCNpc::StandUp()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: StandUp(zBOOL walkingallowed, zBOOL startAniTransition)
// Default : walkingallowed = FALSE;
{	
	anictrl = GetAnictrl();
	if (GetInteractMob() || GetInteractItem()) 
	{	
		Interrupt();

		// FIXME: folgende zeile ist wohl müll: das könnte bei allen mob interaktionen zu plöppen führen
		// [EDENFELD] in der Tat, das wird es, gehts nicht anders ??
		GetModel()->StartAni(anictrl->_s_walk);

	}
	else if (!anictrl->IsStanding())
	{
		if (anictrl->IsWalking() && walkingallowed) return;
		
		// Schwimmen tauchen berücksichtigen
		if (anictrl->GetActionMode()==ANI_ACTION_SWIM) {
			SetBodyState(BS_SWIM);
			GetModel()->StartAni("S_SWIM"); 
			return;
		}
		if (anictrl->GetActionMode()==ANI_ACTION_DIVE) {
			SetBodyState(BS_DIVE);
			GetModel()->StartAni("S_DIVE");
			return;
		}
	
		// Override des Körperzustandes
		SetBodyState(BS_STAND);
		anictrl->StopTurnAnis();

		if (startAniTransition) {
			// Animation suchen mit passendem Namen
			// Bsp : S_KNOCKEDOUT -> T_KNOCKEDOUT_2_STAND
			zSTRING				startAni;
			zTModelAniID		startAniID	= zMDL_ANI_ID_ILLEGAL;
			zCModelAniActive*	ani			= GetAnictrl()->GetLayerAni(1);
			if (ani) {
				zSTRING			aniName		= ani->GetAni()->GetAniName();
				if (aniName.Search("S_")==0) {
					// Zustand
					startAni	= "T_" + aniName.Copied(2) + "_2_STAND";
					startAniID	= GetModel()->GetAniIDFromAniName(startAni);
				}
			}
			if (startAniID==zMDL_ANI_ID_ILLEGAL) startAniID = GetAnictrl()->_s_walk;
			GetModel()->StartAni(startAniID);		
		} else {
			// Auf Standpos ploeppen (AI_StandUpQuick)
			anictrl->StartAni(anictrl->_s_walk);
		}
	}

	// Achtung: Ab 1.11j wird bei einem Standup() auch der RobustTrace angehalten
	RbtReset();

	// ab 1.15d: Anis auf Layer 2 bis 8 werden ausgefadet (turn/point/look ani overlays etc. bleiben weiterhin aktiv)
	// ACHTUNG: auch die RemoveWeapon Anis werden dann hier ausgeblendet -> dumm gelaufen 
	if (GetModel()) GetModel() -> FadeOutAnisLayerRange(2,8);


	// Patch 1.07 : BowMorphMesh zur Sicherheit zuruecksetzen
	zCMorphMesh* pMeshMorph = zDYNAMIC_CAST<zCMorphMesh> (GetEquippedRangedWeapon());
	if ( pMeshMorph ) pMeshMorph->StartAni( "S_RELAX" );
	pMeshMorph = zDYNAMIC_CAST<zCMorphMesh> (GetWeapon());
	if ( pMeshMorph ) pMeshMorph->StartAni( "S_RELAX" );
}

/*--------------------------------------------------------------------------

    oCNpc::Turn()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: Turn(zVEC3 &dir)
// Turn, ohne Beruecksichtigung der Bewegungssgeschwindigkeit
{
	zREAL winkel,elev,deg;
	// Winkel zwischen PlayerAtVector und anzusteuerndes Object
	GetAngles( dir, winkel, elev);
	// Winkelgeschwindigkeit 150 Grad/sec
	
	//
	//	CODECHANGE [ROMAN]
	//
	zREAL turn = this->GetTurnSpeed() * (ztimer.GetFrameTime()/ztimer.GetMotionFactor());
	//
	//	CODECHANGE [ROMAN] END
	//

	if (abs((int)winkel)>30) turn *= 2.0f;	else
	// [Ulf] : 06.01.01 - Drehung im Waffenmodus doppelt so schnell !
	if (IsSelfPlayer() && GetWeaponMode()!=NPC_WEAPON_NONE) turn *= 2.0f;

	if (winkel<0) {
//		zERR_WARNING("U:RBT:Turn Left");
		deg = zMax(winkel,-turn);
	} else { 
//		zERR_WARNING("U:RBT:Turn Right");
		deg = zMin(winkel, turn);
	}


	anictrl -> TurnDegrees (deg, abs((int)deg)>5);


	//	if (abs(deg)<3) anictrl->StopTurnAnis();
	return zAbs(winkel);
}

/*--------------------------------------------------------------------------

    oCNpc::Turning()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zREAL oCNpc :: Turning(zVEC3 &dir)
{
	zREAL winkel,elev;
	// Winkel zwischen PlayerAtVector und anzusteuerndes Object
	GetAngles( dir, winkel, elev);
	
	//
	//	CODECHANGE [ROMAN]
	//
	zREAL turn = /*NPC_TURNVELOCITY_MSEC*/ this->GetTurnSpeed() * ztimer.GetFrameTime();
	//
	//	CODECHANGE [ROMAN] END
	//

	// Winkelgeschwindigkeit 150 Grad/sec
	// zREAL turn	= NPC_TURNVELOCITY_MSEC * ztimer.GetFrameTime();
	
	// FIXME : Berechnung der Laenge nur 1x irgendwo im AniCtrl -> Dieter
	// zREAL len	= anictrl->velocity.LengthApprox();
	// Geschwindigkeiten fuer Human
	// Stehen	:   0.1 -   0.5
	// Gehen	:  90.0 - 160.0
	// Rennen	: 280.0 - 340.0		
	// zREAL w		= turn * len / NPC_TURNVELOCITY_MSEC; 

	if (winkel<0)	anictrl -> TurnDegrees( zMax(winkel,-turn) );
	else			anictrl -> TurnDegrees( zMin(winkel, turn) );
	
	if (abs((int)winkel)<5) anictrl->StopTurnAnis();		

	return winkel;
}

// ***************************************************************************************
// Externals
// ***************************************************************************************

/*--------------------------------------------------------------------------

    oCNpc::AI_Flee()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: AI_Flee(oCNpc *e)
{
//	if (!IsAIState(NPC_AISTATE_FLEE)) {
//		enemy_slot_deg		= e -> AI_GetFreePosAngle();
//		enemy_slot_holder	= e;
//		if (enemy_slot_deg==1000) return;
//		enemy_slot_dist		= 150;
//		GetNpcManager()->Clear();
	//		GetAIManager()->SetInsertMode(oCAIManager::INSERT_NORMAL);
//		SetAIState(NPC_AISTATE_FLEE);
	//		Reaction	(flee_start,e);
	//		GetAIManager()->AI_FleeMode();
//	}
}

/*--------------------------------------------------------------------------

    oCNpc::AI_Follow()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: AI_Follow(oCNpc *e)
{
//	if (!IsAIState(NPC_AISTATE_FOLLOW)) {
//		enemy_slot_deg		= e -> AI_GetFreePosAngle();
//		enemy_slot_holder	= e;
//		if (enemy_slot_deg==1000) return;
//		enemy_slot_dist		= 150;
//	}
}

// ***************************************************************************************
// Events
// ***************************************************************************************

/*--------------------------------------------------------------------------

    oCNpc::EV_AlignToFP()

 

    06-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_AlignToFP		(oCMsgMovement* csg)
{
	if ( ! csg->IsInUse() )
	{
		//
		//	FIND SPOT
		//
		zCVobSpot*	spot		= NULL;
		int i;

		zCArray <zCVob*> vobList;

		zTBBox3D bbox;
		bbox.maxs = bbox.mins = GetPositionWorld();		
		// Vorderer Punkt	
		bbox.maxs[0] += 100; bbox.maxs[1] += 100; bbox.maxs[2] += 100;
		// Hinterer Punkt
		bbox.mins[0] -= 100; bbox.mins[1] -= 100; bbox.mins[2] -= 100;
		this->GetHomeWorld() -> CollectVobsInBBox3D(vobList, bbox);
		
		int max = vobList.GetNumInList();

		// schmeisse alle nicht-Spots raus
		for (i=max-1;i>=0;i--)
			if (!zDYNAMIC_CAST<zCVobSpot>(vobList[i]))
				vobList.RemoveIndex(i);

		max = vobList.GetNumInList();

		zBOOL bFound = FALSE;
		for (i=0; i<max; i++) {	
			spot = zDYNAMIC_CAST<zCVobSpot>(vobList[i]);

			assert(spot);

 			if (spot->IsOnFP(this)) // Den erstbesten freien Benutzen.	
			{
				bFound = TRUE;
				break;
			}
		}

		if ( ! bFound )  return TRUE; 
		else			 
		{
			csg->SetInUse( TRUE );
			csg->targetVob = spot;
		}
	}

	//
	//	ALIGN TO SPOT
	//

	// Codechange [Ulf] 
	// return ( this->Turn( csg->targetVob->GetAtVectorWorld() ) == 0.0f );
	return ( this->Turn( GetPositionWorld() + csg->targetVob->GetAtVectorWorld()*200 ) <= 1.0f );
}


/*--------------------------------------------------------------------------

    oCNpc::EV_CanSeeNpc()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc ::  EV_CanSeeNpc (oCMsgMovement* csg)
{
	if ((csg->targetMode>=0) && CanSee(csg->targetVob)) {	
		int funcNr = csg->targetMode;
		ClearEM();
		state.StartAIState	(funcNr,FALSE,AITIME_NO);
		// Nicht als zu löschen markieren, weil ist schon passiert !
		return FALSE;
	}
	return TRUE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_GoRoute()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_GoRoute			(oCMsgMovement* csg)
// IN :
// a) - name		= Name des Zielwaypointes			ODER
// b) - target_vec	= Zielposition
{
	if (!anictrl->IsWalking() && !anictrl->IsStanding()) StandUp();

	// Route suchen
	if (!csg->IsInUse()) {
	
		RbtReset();		// Chasm detection goes off !
		csg->SetInUse	(TRUE);
			
		zCWayNet* wn = GetHomeWorld()->GetWayNet();
		if (csg->targetName.IsEmpty()) {
			// freie Position als Ziel
			SetRoute( wn->FindRoute(GetPositionWorld(),csg->targetPos,this) );

		} else
			// Waypoint als Ziel
			SetRoute( wn->FindRoute(GetPositionWorld(),csg->targetName,this) );

		// Der erste Waypoint sollte automatisch entfernt werden, wenn dieser besser plaziert ist
		// -> passiert jetzt also bereits in FindRoute

		// Keine Route gefunden, dann raus
		if (!route) {
			zSTRING msg = "U: NPC: No Route found :"+ GetName(TRUE) + " \\ " + GetInstanceName(); 
			if (!csg->targetName.IsEmpty()) msg += " ("+csg->targetName+")";
			zERR_WARNING(msg);
			return TRUE;
		}
		
		rbt.targetReached = TRUE;
	}

	zCWaypoint* wp = NULL;
	zCRoute*	rt = GetRoute();
	
	// Ziel erreicht, oder Route neu berechnen
	if (rbt.targetReached) {
		// Nächsten Wegpunkt holen und Subgoals erzeugen
		if (rt)	wp	= rt -> GetNextWP();
		if (wp) rbt.targetReached = FALSE;

	} else if (!rbt.waiting) {
		// Ziel nicht erreicht, Route bitte neu berechnen
		csg->SetInUse(FALSE);
		return FALSE;
	}

	if (wp) {
	
		// Wegproperties holen
		oCWay* way = static_cast<oCWay*>(rt -> GetCurrentWay());

		// *********
		// Leiter ?
		// *********
		oCMobLadder* ladder = NULL;
		if (way) ladder = way->GetLadder();
		if (ladder) {
			// auf jeden Fall stehenbleiben
			GetModel()->StartAni(anictrl->_s_walk);

			if (ladder->CanInteractWith(this)) {

				// Hoch oder Runter ?
				zCWaypoint*			current = way->GetLeftWaypoint();
				if (current==wp)	current = way->GetRightWaypoint();

				int targetState = 1;
				if (wp->GetPositionWorld()[VY] > current->GetPositionWorld()[VY]) targetState = 100;
					
				// Klettern
				oCMsgManipulate* evMsg = zNEW( oCMsgManipulate(oCMsgManipulate::EV_USEMOB, ladder, -1) );
				evMsg   -> SetHighPriority	(TRUE);
				GetEM() -> OnMessage (evMsg, this);
				
				evMsg = zNEW( oCMsgManipulate (oCMsgManipulate::EV_USEMOB, ladder, targetState) );
				evMsg   -> SetHighPriority	(TRUE);
				GetEM() -> OnMessage (evMsg, this);

				// Ausrichten
				oCMsgMovement* evMsgMove = zNEW( oCMsgMovement(oCMsgMovement::EV_TURNTOVOB, ladder) );
				evMsgMove   -> SetHighPriority	(TRUE);
				GetEM()		-> OnMessage		(evMsgMove, this);
				
				// Position oben / unten ?
				zVEC3 targetPos = ladder->GetPositionWorld();
				if (targetState>1) {
					// nach oben klettern / Position unten als Ziel benutzen
					targetPos[VY] = ladder->GetBBox3DWorld().mins[VY];
				} else {
					targetPos[VY] = ladder->GetBBox3DWorld().maxs[VY];
				}

				// Hingehen
				evMsgMove	=  zNEW( oCMsgMovement(oCMsgMovement::EV_GOTOPOS, targetPos) );
				evMsgMove   -> SetHighPriority	(TRUE);
				GetEM()		-> OnMessage		(evMsgMove, this);
				
				rbt.waiting			= FALSE;
				rbt.targetReached	= TRUE;
				return FALSE;
			};
			rbt.waiting = TRUE;
			return FALSE;
		}
		
		// ********
		// Abgrund
		// ********
		if (way && way->GetChasm() && way->CanJump()) {
			// FIXME : Stand - Befehl
			GetModel()->StartAni		(anictrl -> _s_walk);
			oCMsgMovement* evMsg = zNEW	( oCMsgMovement(oCMsgMovement::EV_JUMP, wp->GetPositionWorld()) );
			evMsg   -> SetHighPriority	(TRUE);
			GetEM() -> OnMessage		(evMsg, this);
			evMsg	=  zNEW				( oCMsgMovement(oCMsgMovement::EV_TURNTOPOS, wp->GetPositionWorld()) );
			evMsg   -> SetHighPriority	(TRUE);
			GetEM() -> OnMessage		(evMsg, this);
			rbt.targetReached = TRUE;

		} else {
			// FIXME : Properties des Weges und des WPs holen
			oCMsgMovement* evMsg = zNEW	( oCMsgMovement(oCMsgMovement::EV_ROBUSTTRACE, wp->GetPositionWorld()) );
			evMsg   -> SetHighPriority	(TRUE);
			GetEM() -> OnMessage		(evMsg, this);
		}

	} else {
		// Route beendet.
		SetRoute (NULL);
		anictrl -> StopTurnAnis		();
		anictrl	-> _Stand			();
		return (anictrl->IsStanding	());
	}
	
	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_Jump()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_Jump (oCMsgMovement* csg)
{
	if (!csg->IsInUse()) {
		anictrl -> JumpForward();
		csg		-> SetInUse(TRUE);
		return FALSE;
	}
	if (anictrl->IsStanding()) {
		SetCollDet(TRUE);
		return TRUE;
	}
	return FALSE;
}

//zREAL turnheadx = 0.5f, turnheady = 0.5f;

/*--------------------------------------------------------------------------

    oCNpc::EV_RobustTrace()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_RobustTrace	(oCMsgMovement* csg)
{
	if (!csg->IsInUse()) {
		RbtInit(csg->targetPos,csg->targetVob);
		rbt.standIfTargetReached	= (csg->targetMode!=0);
		rbt.exactPosition			= FALSE;
		csg->SetInUse(TRUE);
	}
	return RobustTrace();
}

/*--------------------------------------------------------------------------

    oCNpc::EV_StandUp()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_StandUp(oCMsgMovement* csg)
{
	if (!csg->IsInUse()) {
		// WalkingAllowed	= FALSE
		// StartTransAni	= csg->target != 0
		StandUp(FALSE,(csg->targetMode!=0));
		csg->SetInUse(TRUE);
	} 
	if (anictrl->GetActionMode()==ANI_ACTION_SWIM) return TRUE;
	if (anictrl->GetActionMode()==ANI_ACTION_DIVE) return TRUE;


	if (GetTrueGuild()==NPC_GIL_SKELETON_MAGE) return TRUE;

	return (GetModel()->IsAniActive(anictrl->_s_walk));
}

/*--------------------------------------------------------------------------

    oCNpc::EV_Strafe()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc ::  EV_Strafe (oCMsgMovement* csg)
{  
	zCModel* model = GetModel();

	// [BENDLIN] Beim Schlagen/Parieren abbrechen (auch strafe-aim-bug gefixt)
	// FIXME: Anderen Mechanismus? (Problem bei neuen Anpassungen)
	// FIXME: Was ist mit Fernwaffen/Magie?
	if (oCGame::GetUseOldControls())
	{
		if ( IsSelfPlayer() && (GetWeaponMode()!=NPC_WEAPON_NONE) && int(zinput->GetState(GAME_ACTION)) )
		{
			// Schlag nach links
			if ( int(zinput->GetState(GAME_LEFT) && (GetWeaponMode() < NPC_WEAPON_BOW) ) /* || int(zinput->GetState(GAME_STRAFELEFT)) */ )
			{
				if ( int(zinput->GetToggled(GAME_ACTION)) || int(zinput->GetToggled(GAME_LEFT)) /* || int(zinput->GetToggled(GAME_STRAFELEFT)) */ )
				{
					if ( model->IsAniActive(csg->ani) )
					{
						model->FadeOutAni	(csg->ani);
						model->StartAni		(anictrl->_s_walk);
					}
					GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT,anictrl->_t_hitl)),this);
					return TRUE;
				}
			}
			// Schlag nach rechts
			else if ( int(zinput->GetState(GAME_RIGHT) && (GetWeaponMode() < NPC_WEAPON_BOW) ) /* || int(zinput->GetState(GAME_STRAFERIGHT)) */ )
			{
				if ( int(zinput->GetToggled(GAME_ACTION)) || int(zinput->GetToggled(GAME_RIGHT)) /* || int(zinput->GetToggled(GAME_STRAFERIGHT)) */ )
				{
					if ( model->IsAniActive(csg->ani) )
					{
						model->FadeOutAni	(csg->ani);
						model->StartAni		(anictrl->_s_walk);
					}
					GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT,anictrl->_t_hitr)),this);
					return TRUE;
				}
			}
			// Schlag nach vorn
			else if ( int(zinput->GetState(GAME_UP)) )
			{				
				if ( int(zinput->GetToggled(GAME_ACTION)) || int(zinput->GetToggled(GAME_UP)) )
				{
					if ( model->IsAniActive(csg->ani) )
					{
						model->FadeOutAni	(csg->ani);
						model->StartAni		(anictrl->_s_walk);
					}
					
					// Siehe auch ThinkNextFightAction()
					switch (GetWeaponMode())
					{
					case NPC_WEAPON_FIST:
					case NPC_WEAPON_DAG:
					case NPC_WEAPON_1HS:
					case NPC_WEAPON_2HS:
						// Nahkampf
						GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, anictrl->_t_hitf)), this);
						break;
					case NPC_WEAPON_BOW:
					case NPC_WEAPON_CBOW:
						// Fernkampf
						FightAttackBow();
						break;
					case NPC_WEAPON_MAG:
						// Magie
						FightAttackMagic();
						break;
					default:
						// Ouch, this should never happen.
						break;
					}
					return TRUE;
				}
			}
			// Parade
			else if ( int(zinput->GetState(GAME_DOWN)) && (GetWeaponMode() < NPC_WEAPON_BOW) )
			{
				if ( int(zinput->GetToggled(GAME_ACTION)) || int(zinput->GetToggled(GAME_DOWN)) )
				{
					if ( model->IsAniActive(csg->ani) )
					{
						model->FadeOutAni	(csg->ani);
						model->StartAni		(anictrl->_s_walk);
					}
					GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,GetFocusNpc())),this);
					return TRUE;
				}
			}
		}
	}
	else
	{
		if ( IsSelfPlayer() && (GetWeaponMode()!=NPC_WEAPON_NONE) )
		{
			// Schlag nach links
			if ( int(zinput->GetState(GAME_ACTIONLEFT)) && (GetWeaponMode() < NPC_WEAPON_BOW) )  
			{
				if ( int(zinput->GetToggled(GAME_ACTIONLEFT)) )
				{
					if ( model->IsAniActive(csg->ani) )
					{
						model->FadeOutAni	(csg->ani);
						model->StartAni		(anictrl->_s_walk);
					}
					GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKLEFT,anictrl->_t_hitl)),this);
					return TRUE;
				}
			}
			// Schlag nach rechts
			else if ( int(zinput->GetState(GAME_ACTIONRIGHT) && (GetWeaponMode() < NPC_WEAPON_BOW) ) )
			{
				if ( int(zinput->GetToggled(GAME_ACTIONRIGHT)) )
				{
					if ( model->IsAniActive(csg->ani) )
					{
						model->FadeOutAni	(csg->ani);
						model->StartAni		(anictrl->_s_walk);
					}
					GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_ATTACKRIGHT,anictrl->_t_hitr)),this);
					return TRUE;
				}
			}
			// Schlag nach vorn
			else if ( int(zinput->GetToggled(GAME_ACTION)) )
			{				
				if ( model->IsAniActive(csg->ani) )
				{
					model->FadeOutAni	(csg->ani);
					model->StartAni		(anictrl->_s_walk);
				}
				
				// Siehe auch ThinkNextFightAction()
				switch (GetWeaponMode())
				{
				case NPC_WEAPON_FIST:
				case NPC_WEAPON_DAG:
				case NPC_WEAPON_1HS:
				case NPC_WEAPON_2HS:
					// Nahkampf
					GetEM()->OnMessage(zNEW(oCMsgAttack(oCMsgAttack::EV_ATTACKFORWARD, anictrl->_t_hitf)), this);
					break;
				case NPC_WEAPON_BOW:
				case NPC_WEAPON_CBOW:
					// Fernkampf
					FightAttackBow();
					break;
				case NPC_WEAPON_MAG:
					// Magie
					FightAttackMagic();
					break;
				default:
					// Ouch, this should never happen.
					break;
				}
				return TRUE;
			}
			// Parade
			else if ( int(zinput->GetState(GAME_PARADE)) && GetWeaponMode() < NPC_WEAPON_BOW )
			{

				if ( int(zinput->GetToggled(GAME_PARADE)) )
				{
					if ( model->IsAniActive(csg->ani) )
					{
						model->FadeOutAni	(csg->ani);
						model->StartAni		(anictrl->_s_walk);
					}
					GetEM()->OnMessage(zNEW( oCMsgAttack(oCMsgAttack::EV_PARADE,GetFocusNpc())),this);
					return TRUE;
				}
			}
		}
	};

	
	if (!csg->IsInUse()) 
	{
		if (csg->ani==zMDL_ANI_ID_ILLEGAL) return TRUE;
		if (GetAnictrl()) GetAnictrl()->StopTurnAnis();
		model	-> StartAni		(csg->ani);
		csg		-> SetInUse		(TRUE);
		csg		-> timer = model->GetProgressPercent(csg->ani);
	}

	if (csg->targetVob) 
	{
		// Nach Vob ausrichten
		Turn(csg->targetVob->GetPositionWorld());
	}
	else if (IsSelfPlayer() && human_ai) 
	{
		// Turnings erlauben, wenn kein Gegner im Focus
		if (!zinput->GetState(GAME_SMOVE)) human_ai->PC_Turnings();	
	}

	if (model->IsAniActive(csg->ani)) 
	{
		if (csg->timer > model->GetProgressPercent(csg->ani)) 
		{
			if (IsSelfPlayer()) 
			{
				zBOOL strafeL = (zinput->GetState(GAME_SMOVE) && zinput->GetState(GAME_LEFT))	|| zinput->GetState(GAME_STRAFELEFT);
				zBOOL strafeR = (zinput->GetState(GAME_SMOVE) && zinput->GetState(GAME_RIGHT))	|| zinput->GetState(GAME_STRAFERIGHT);
			
				if (model->GetAniFromAniID(csg->ani)->GetAniName().Search("STRAFEL")>=0) 
				{
					if (strafeL) 
					{
						csg  ->timer = 0.0f;	
					}
					else {
						model->StartAni	(anictrl->_s_walk);
					}
				} 
				else 
				{
					if (strafeR) 
					{
						csg	 ->timer = 0.0f;
					} else {
						model->StartAni	(anictrl->_s_walk);
					}
				}							
			
			} else {
				model->StartAni(anictrl->_s_walk);
			}

		} 
		else 
		{
			csg->timer = model->GetProgressPercent(csg->ani);
		}
	}

	// Strafe auch mittendrin abbrechbar machen....
	if (IsSelfPlayer()) 
	{

		int strafeDirNow = 1;
		if (model->GetAniFromAniID(csg->ani)->GetAniName().Search("STRAFEL")>=0) strafeDirNow = 0;

		zBOOL strafeL = (zinput->GetState(GAME_SMOVE) && zinput->GetState(GAME_LEFT))	|| zinput->GetState(GAME_STRAFELEFT);
		zBOOL strafeR = (zinput->GetState(GAME_SMOVE) && zinput->GetState(GAME_RIGHT))	|| zinput->GetState(GAME_STRAFERIGHT);

		if ((!strafeL && !strafeR) || (strafeL&&strafeDirNow==1) || (strafeR&&strafeDirNow==0) ) 
		{
			model->FadeOutAni	(csg->ani);
			model->StartAni		(anictrl->_s_walk);
		}
	}

	return (!model->IsAniActive(csg->ani));
}

/*--------------------------------------------------------------------------

    oCNpc::EV_WhirlAround()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_WhirlAround(oCMsgMovement* csg)
{
	// FIXME : AI_LookAt hier noch rein !!!

	// Wenn du liegst oder sitzt, spring auf 
	// sonst (alle anderen Ani-States) mach gar nichts
	// if (!EV_StandUp(csg)) return FALSE;

	// WhirlAround wird nur ausgeführt, wenn die Animation, 
	// in der der NSC ist unterbrechbar ist!
	// Das klappt also bei Sitzen und Liegen nicht, 
	// aber durch B_JumpUp (in B_WhirlAround enthalten) 
	// wird sichergestellt, daß ein NSC immer aufspringt, 
	// bevor er herumwirbelt. Somit ist es auch sitzenden/liegenden NSCs 
	// möglich den WhirlAround auszuführen.
	if (!IsBodyStateInterruptable()) return TRUE;

	// Bei TargetVob dieses auch verfolgen....
	if (csg->targetVob) csg->targetPos = csg->targetVob->GetPositionWorld();
	
	zREAL azi,elev;	
	GetAngles(csg->targetPos,azi,elev);
	zCModel* model = GetModel();

	if (!csg->IsInUse()) {
		
		StandUp();

		anictrl -> StopTurnAnis();

		csg->angle = azi;
		
		// Einmalige Pruefung auf das entsprechende Verhalten des NCSs
		if (abs((int)azi)<=90) {
			// Jawoll.
			csg->ani	= model->GetAniIDFromAniName("S_SURPRISE");
			// csg->angle	= 0.0f;
		} else {
			// Noe, schon mit Rumwirbeln
			if (azi<-90) {
				csg->ani	= model->GetAniIDFromAniName("T_SURPRISE_CCW");
				csg->angle  = azi;
			} else {
				csg->ani	= model->GetAniIDFromAniName("T_SURPRISE_CW");
				csg->angle  = azi;
			}
		}
		// Ani starten
		if (csg->ani!=zMDL_ANI_ID_ILLEGAL) {
			model	-> StartAni(csg->ani);
			csg		-> timer = 500;		// 1 Sekunde so verweilen
			csg		-> SetInUse(TRUE);
		} else {
			zERR_WARNING("U:NPC: "+GetInstanceName()+": WhirlAround Ani (T_SURPRISExxx) not found.");
			return TRUE;
		}
	}
	
	zREAL turnheadx = (azi  + 45) / ( 45 * 2);
	if (turnheadx<0) turnheadx = 0; else if (turnheadx>1.0) turnheadx=1.0;
	zREAL turnheady = (elev + 45) / ( 45 * 2);
	if (turnheady<0) turnheady = 0; else if (turnheady>1.0) turnheady=1.0;

/*
	if (zinput->GetState(GAME_UP)) {
		turnheady += 0.05f;	if (turnheady>1.0f) turnheady = 1.0f;
	} else if (zinput->GetState(GAME_DOWN)) {
		turnheady -= 0.05f;	if (turnheady<0.0f) turnheady = 0.0f;
	}
	if (zinput->GetState(GAME_RIGHT)) {
		turnheadx += 0.05f;	if (turnheadx>1.0f) turnheadx = 1.0f;
	} else if (zinput->GetState(GAME_LEFT)) {
		turnheadx -= 0.05f;	if (turnheadx<0.0f) turnheadx = 0.0f;
	}
*/
	// Model zusaetzlich drehen ?
//	if (csg->angle!=0.0) {
		// R-Flag bei den Anis muss raus, macht allein das Programm.	
		csg->angle = Turn(csg->targetPos);
//	} else {
//		anictrl->StopTurnAnis();
//	}

	// Ist das eine Ani-Comb, na dann anpassen, da !
	zCModelAni* cAni = model->GetAniFromAniID(csg->ani);
	if (cAni && cAni->GetAniType()==zMDL_ANI_TYPE_COMB) {
		model -> SetCombineAniXY(csg->ani,turnheadx,1-turnheady);
	}

	if (model->IsAniActive("S_SURPRISE")) {
		zTModelAniID	aniID	= model->GetAniIDFromAniName("S_SURPRISE");
		zCModelAni*		cAni	= model->GetAniFromAniID	(aniID);
		if (cAni && cAni->GetAniType()==zMDL_ANI_TYPE_COMB) {
			
			model -> SetCombineAniXY(aniID,turnheadx,1-turnheady);
		}
		// Eine halbe Skunde verweilen....
		csg->timer -= ztimer.GetFrameTimeF();
		if (csg->timer<=0) {		
			anictrl	-> StopTurnAnis	();
			model	-> StartAni		(anictrl->_s_walk);
			return TRUE;
		}
	} else if (!model->IsAniActive("T_SURPRISE_CCW") && !model->IsAniActive("T_SURPRISE_CW")) {
		// FIXME : Wie kann das passieren.
		// NSC mit hohem Kampftalent angreifen und mehrmals schalgen, bevor dieser im AttackModus ist ?!?!
		return TRUE;
	}
	
	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_Dodge()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_Dodge(oCMsgMovement* csg)
{
	// ai_Dodge <N-SC> (Ulf) machen!
	// In ZS_WatchFight aufgerufen, wenn jemand mit Waffe im Fluchtradius ist.
	// C_SpaceBehind (Ist hinter mir Platz), dann 
	// Springe zurück
	//			Sonst
	//				C_SpaceLeft (Wenn links von mir Platz ist), dann	
	//				Strafe nach links
	//			Oder (links/rechts zufällig?)
	//				C_SpaceRight (Wenn rechts von mir Platz ist), dann	
	//				Strafe nach rechts
	
	zCModel* model = GetModel();

	if (!csg->IsInUse()) {

		StandUp(TRUE);
		
		csg->SetInUse(TRUE);
		if (anictrl->CheckEnoughSpaceMoveBackward()) {
		
			csg->ani = model->GetAniIDFromAniName("T_JUMPB");
			if (csg->ani!=zMDL_ANI_ID_ILLEGAL) {
				anictrl->StartAni(csg->ani,anictrl->_s_walk);
				return FALSE;
			}

		} else if (anictrl->CheckEnoughSpaceMoveLeft()) {
			csg->ani = anictrl->_t_strafel;
			model->StartAni(anictrl->_t_strafel);

		} else if (anictrl->CheckEnoughSpaceMoveRight()) {
			csg->ani = anictrl->_t_strafer;
			model->StartAni(anictrl->_t_strafer);
		} else {
			// Nothing found
			return TRUE;
		}
	
	} else if (!model->IsAniActive(csg->ani)) {
		
		return TRUE;
	
	}

	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_GotoPos()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_GotoPos			(oCMsgMovement* csg)
{
	StandUp(TRUE);	// Walking allowed

	if (!csg->IsInUse()) {
		RbtInit	(csg->targetPos,NULL);
		rbt.standIfTargetReached	= 1;
		rbt.exactPosition			= FALSE;
		rbt.maxTargetDist			= 100 * 100;	// 1 Meter Varianz
		csg->SetInUse(TRUE);
	}
	csg->targetMode	= 1;			// Stehenbleiben
	return (EV_RobustTrace(csg));
};

/*--------------------------------------------------------------------------

    oCNpc::EV_GotoVob()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_GotoVob			(oCMsgMovement* csg)
{	
	if (!csg->targetVob) {
		zERR_WARNING("U: NPC: EV_GOTOVOB : targetVob not found.");
		return TRUE;
	}

	rbt.timer					= 500;
	rbt.targetVob				= csg->targetVob;
	rbt.targetPos				= csg->targetVob->GetPositionWorld();
	rbt.standIfTargetReached	= TRUE;

	rbt.maxTargetDist			= 200 * 200;
	return RbtGotoFollowPosition();

/*
	StandUp(TRUE);	// Walking allowed

	if (!csg->targetVob) {
		zERR_WARNING("U: NPC: EV_GOTOVOB : targetVob not found.");
		return TRUE;
	}
	
	csg->targetPos	= csg->targetVob->GetPositionWorld();
	csg->targetMode	= 1;			// Stehenbleiben
	return (EV_RobustTrace(csg));*/
}

/*--------------------------------------------------------------------------

    oCNpc::EV_GotoFP()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_GotoFP			(oCMsgMovement* csg)
{
	StandUp(TRUE);	// Walking allowed

	if (!csg->targetVob) {
		if (!csg->targetName.IsEmpty()) csg->targetVob = FindSpot(csg->targetName,(csg->targetMode!=0));
		if (!csg->targetVob) {
			zERR_WARNING("U: NPC " + GetInstanceName() +  ": EV_GOTOFP : Freepoint " + csg->targetName + " not found.");
			return TRUE;
		}
	}

	if (!csg->IsInUse()) {
		RbtInit	(csg->targetVob->GetPositionWorld(),csg->targetVob);
		rbt.standIfTargetReached	= 1;
		rbt.exactPosition			= FALSE;
		rbt.maxTargetDist			= 50 * 50;	// 1/2 Meter Varianz
		csg->SetInUse(TRUE);
		zCVobSpot* spot = zDYNAMIC_CAST<zCVobSpot>(csg->targetVob);
		if (spot) spot->MarkAsUsed(30 * 1000,this);
	}

	if (RobustTrace()) {
		// Ziel erreicht, jetzt noch ausrichten
		return (abs(int(Turn(GetPositionWorld()+csg->targetVob->GetAtVectorWorld()*200)))<3);
	}
	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_SetWalkMode()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_SetWalkMode(oCMsgMovement* csg)
{
	zCModel* model	= GetModel();
	anictrl			= GetAnictrl();

	// Im tiefen Wasser hat umschalten des Walkmodes keinen Erfolg !
	if (anictrl->GetWaterLevel() > 0) return TRUE;

	int fm = GetWeaponMode();
	if (!csg->IsInUse()) {
		if (anictrl->GetWalkMode()==csg->targetMode) return TRUE;
		// Falls nicht im StandMode, dann mal stehen....
		StandUp();
		csg->SetInUse(TRUE);
	}
	if (model->IsAniActive(csg->ani)) {
		return TRUE;
	} else
	// Wechsel in den angegebenen Walkmode
	if (anictrl->IsStateAniActive(anictrl->s_walk[fm])) {
		// *************************
		// von WALK nach
		// *************************
		if (csg->targetMode==ANI_WALKMODE_WALK) 
		{
			return TRUE;
		}
		else if (csg->targetMode==ANI_WALKMODE_RUN) {
			
			// nach RUN
			anictrl	-> SetWalkMode	(csg->targetMode);
			if		(anictrl->t_walk_2_run[fm]!=zMDL_ANI_ID_ILLEGAL)	model -> StartAni (anictrl->t_walk_2_run[fm]);
			else if	(anictrl->_s_walk!=zMDL_ANI_ID_ILLEGAL)				model -> StartAni (anictrl->_s_walk);
			else {
				anictrl	->SetWalkMode	(ANI_WALKMODE_RUN);
				model	->StartAni		(anictrl->_s_walk);
				return TRUE;
			}
			csg->ani = anictrl -> _s_walk;
		
		} else if (csg->targetMode==ANI_WALKMODE_SNEAK) {
			// nach SNEAK
			anictrl	-> SetWalkMode	(csg->targetMode);
			if		(anictrl->_s_walk!=zMDL_ANI_ID_ILLEGAL)				model -> StartAni (anictrl->_s_walk);
			else	{
				anictrl	->SetWalkMode	(ANI_WALKMODE_SNEAK);
				model	->StartAni		(anictrl->_s_walk);
				return TRUE;
			}
			csg->ani = anictrl -> _s_walk;
		}
	} else if (anictrl->IsStateAniActive(anictrl->s_run[fm])) {
		// *************************
		// von RUN nach
		// *************************
		if (csg->targetMode==ANI_WALKMODE_RUN) 
		{
			return TRUE;
		}
		else if (csg->targetMode==ANI_WALKMODE_WALK) {
			
			// nach WALK
			anictrl	-> SetWalkMode	(csg->targetMode);
			if		(anictrl->t_run_2_walk[fm]!=zMDL_ANI_ID_ILLEGAL)	model -> StartAni (anictrl->t_run_2_walk[fm]);
			else if (anictrl->_s_walk!=zMDL_ANI_ID_ILLEGAL)				model -> StartAni (anictrl->_s_walk);
			else {
				anictrl	->SetWalkMode	(ANI_WALKMODE_WALK);
				model	->StartAni		(anictrl->_s_walk);
				return TRUE;
			}
			csg->ani = anictrl -> _s_walk;

		} else if (csg->targetMode==ANI_WALKMODE_SNEAK) {
			
			// nach SNEAK
			anictrl	-> SetWalkMode	(csg->targetMode);
			if		(anictrl->t_run_2_sneak[fm]!=zMDL_ANI_ID_ILLEGAL)		model -> StartAni (anictrl->t_run_2_sneak[fm]);
			else if (anictrl->_s_walk!=zMDL_ANI_ID_ILLEGAL)					model -> StartAni (anictrl->_s_walk);
			else {
				anictrl	->SetWalkMode	(ANI_WALKMODE_WALK);
				model	->StartAni		(anictrl->_s_walk);
				return TRUE;			
			}
			csg->ani = anictrl -> _s_walk;
		
		}			
	} else if (anictrl->IsStateAniActive(anictrl->s_sneak[fm])) {
		// *************************
		// von SNEAK nach
		// *************************
		if (csg->targetMode==ANI_WALKMODE_SNEAK) 
		{
			return TRUE;
		}
		else if (csg->targetMode==ANI_WALKMODE_WALK) {
			
			// nach WALK
			anictrl	-> SetWalkMode	(csg->targetMode);
			if (anictrl->_s_walk!=zMDL_ANI_ID_ILLEGAL)						model -> StartAni (anictrl->_s_walk);
			else {
				anictrl	->SetWalkMode	(ANI_WALKMODE_SNEAK);
				model	->StartAni		(anictrl->_s_walk);
				return TRUE;				
			}
			csg->ani = anictrl->_s_walk;
		
		} else if (csg->targetMode==ANI_WALKMODE_RUN) {
			// nach RUN
			anictrl	-> SetWalkMode	(csg->targetMode);
			if		(anictrl->t_sneak_2_run[fm]!=zMDL_ANI_ID_ILLEGAL)		model -> StartAni (anictrl->t_sneak_2_run[fm]);
			else if (anictrl->_s_walk!=zMDL_ANI_ID_ILLEGAL)					model -> StartAni (anictrl->_s_walk);
			else {
				anictrl	->SetWalkMode	(ANI_WALKMODE_SNEAK);
				model	->StartAni		(anictrl->_s_walk);
				return TRUE;				
			}
			csg->ani = anictrl->_s_walk;
		}			
	}
	if (GetInteractMob() || GetInteractItem()) {
		Interrupt();
		model->StartAni(anictrl->_s_walk);
	}
	
	anictrl->_Stand();
	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::EV_Turn()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_Turn (oCMsgMovement* csg)
// Turn angles
{
	// Be sure : Nur im stehen....
/*	if (!csg	-> IsInUse() && !anictrl->IsStanding()) {
		anictrl	-> _Stand();
		csg		-> SetInUse( anictrl -> IsStanding() );
		return FALSE;
	}*/
	zREAL win;

	//
	//	CODECHANGE [ROMAN]
	//
	zREAL turn = /*NPC_TURNVELOCITY_MSEC*/ this->GetTurnSpeed() * ztimer.GetFrameTime();
	//
	//	CODECHANGE [ROMAN] END
	//

	if (csg->angle<0) {
		win			= zMax(csg->angle,-turn);
		csg->angle -= win;
	} else {
		win			= zMin(csg->angle, turn);
		csg->angle -= win;
	}
	
	anictrl -> TurnDegrees(win);
	if (csg->angle==0) {
		anictrl->StopTurnAnis();
		return TRUE;
	} else
		return FALSE;	
}

/*--------------------------------------------------------------------------

    oCNpc::EV_TurnAway()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_TurnAway (oCMsgMovement* csg)
{
	if (!csg->targetVob) {
		zERR_WARNING("U: NPC: EV_TURNAWAY : No targetVob found.");
		return TRUE;
	}
	// Nicht drehen, falls du nicht stehst !
	if (GetBodyState()!=BS_STAND) return TRUE;;
	
	if (!anictrl->IsStanding()) StandUp();

	csg->targetPos = GetPositionWorld() + (GetPositionWorld() - csg->targetVob->GetPositionWorld());
	return EV_TurnToPos(csg);
}

/*--------------------------------------------------------------------------

    oCNpc::EV_TurnToPos()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_TurnToPos	(oCMsgMovement* csg)
// Turn, ohne Beruecksichtigung der Bewegungssgeschwindigkeit
{
	zREAL elev;
	// Winkel zwischen PlayerAtVector und anzusteuerndes Object
	GetAngles(csg->targetPos, csg->angle, elev);
	return EV_Turn(csg);
}

/*--------------------------------------------------------------------------

    oCNpc::EV_TurnToVob()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: EV_TurnToVob (oCMsgMovement* csg)
{
	if (!csg->targetVob) {
		zERR_WARNING("U: NPC: EV_TURNTOVOB : No targetVob found.");
		return TRUE;
	}
	// Nicht drehen, falls du nicht stehst !
	if ((GetBodyState()!=BS_STAND) && (GetBodyState()!=BS_RUN)) return TRUE;;
	
	if (!anictrl->IsStanding()) StandUp();

	csg->targetPos = csg->targetVob->GetPositionWorld();
	if (EV_TurnToPos(csg)) {
		anictrl->StopTurnAnis();
		return TRUE;
	} else 
		return FALSE;
}

void oCNpc :: ForceRotation(zREAL deg)
{
	zBOOL inMove = GetInMovement();
	if (inMove) EndMovement();
	anictrl->TurnDegrees(deg);
	if (inMove) BeginMovement();
}


// ***************************************************************************************
// Robust Tracing
// ***************************************************************************************

zBOOL oCNpc :: RbtCheckForSolution(zVEC3 curPos, zVEC3 targetPos)
{
	// Nach zehn Sekunden sollte er es merken...
	const zREAL RBT_SOLUTION_DISTANCE	= 100.0f / 3000.0f;
	
	// Falls sich diese beiden Werte stark voneinander unterscheiden 
	// (kann nur durch die Y-Komponente ausgeloest werden), dann liegt der
	// Verdacht Nahe, dass sich der Zielpunkt direkt ueber den NSC befindet,
	// RobustTrace diesen aber nicht erreichen kann. Hier wird dann ein Flag 
	// gesetzt, dass dieses Problem nicht zu loesen ist, das von aussen
	// abgefragt und gesondert darauf reagiert werden kann (naemlich mit
	// Unterstuetzung des Wegnetzes.)
//	zREAL distNormal	= (targetPos - curPos).LengthApprox();
	curPos[VY]			= targetPos[VY];
	zREAL distIgnoreY	= (targetPos - curPos).LengthApprox();

	if (distIgnoreY*distIgnoreY <= rbt.maxTargetDist) {
		// Ohne beruecksichtigung der Y-Komponente wurde das Ziel erreicht.
//		if ( (distNormal - distIgnoreY) > 500 ) {

		zTBBox3D bbox = this->GetBBox3DWorld();

		if (!zInRange(targetPos[VY],bbox.mins[VY],bbox.maxs[VY])) {		
			rbt.failurePossibility += RBT_SOLUTION_DISTANCE * ztimer.GetFrameTimeF();
			//zERR_WARNING("U:RBT: Failure probability :"+zSTRING((int)rbt.failurePossibility));
			return FALSE;
		}
	}
	return TRUE;
}


/*--------------------------------------------------------------------------

    oCNpc::RbtReset()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: RbtReset()
{
	rbt.targetVob				= NULL;
	rbt.targetPos				= zVEC3(0,0,0);
	rbt.exactPosition			= FALSE;
	rbt.targetDist				= zREAL_MAX;
	rbt.lastTargetDist			= zREAL_MAX;
	rbt.targetReached			= FALSE;
	rbt.stand					= FALSE;
	rbt.dirChoosed				= FALSE;
	rbt.standIfTargetReached	= TRUE;
	rbt.dirTurn					= 0.0f;
	rbt.dirFirst				= zVEC3(0,1,0);
	rbt.dirLastAngle			= 0.0f;
	rbt.timer					= 0.0f; 
	rbt.waiting					= FALSE;
	rbt.frameCtr				= 0;
	rbt.lastDirections.DeleteList();
	rbt.obstVob					= NULL;
	// neu :
	rbt.targetVisible			= FALSE;
	rbt.targetPosIndex			= -1;
	rbt.targetPosCounter		= 0;
	rbt.checkVisibilityTime		= 0.0f;
	rbt.positionUpdateTime		= 0.0f;
	rbt.useChasmChecks			= TRUE;
	rbt.failurePossibility		= 0.0f;

	// FIXME : Abweichung pro Spezies
	rbt.maxTargetDist			= 150 * 150;	// 2 Meter
}

/*--------------------------------------------------------------------------

    oCNpc::RbtInit()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: RbtInit(zVEC3& tpos, zCVob* tvob)
{
	// Alten State clearen
	RbtReset();
	// Und neu initialisieren
	RbtUpdate(tpos,tvob);
};

/*--------------------------------------------------------------------------

    oCNpc::RbtUpdate()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
void oCNpc :: RbtUpdate(zVEC3& tpos, zCVob* tvob)
{	
	rbt.targetPos				= tpos;
	rbt.targetVob				= tvob;
	rbt.targetPosArray[0]		= tpos;

	zVEC3 pos1					= tpos;
	zVEC3 pos2					= GetPositionWorld();
	pos1[VY] = 0; pos2[VY] = 0;
	
	// Walkmodus berücksichtigen
	rbt.timer					= (pos2-pos1).LengthApprox();
	if (anictrl->GetWalkMode()==ANI_WALKMODE_RUN)	rbt.timer *= 10;
	else											rbt.timer *= 20;
		
	// Distanz errechnen
	rbt.lastTargetDist			= GetDistanceToPos2(rbt.targetPos);
	rbt.targetReached			= (rbt.lastTargetDist < rbt.maxTargetDist);
	if (!rbt.targetReached && rbt.standIfTargetReached) rbt.stand = FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::RbtMoveToExactPosition()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: RbtMoveToExactPosition ()
{
	// Stoppen, sobald Entfernung wieder zunimmt (aktuelle Entfernung groesser als letzte)
	if (rbt.targetDist > rbt.lastTargetDist) {
		// Jetzt dahinbeamen ( sofern Platz da ist )
		zVEC3 pos = rbt.targetPos;
		if (SearchNpcPosition(pos)) {
			// ok, Platz gefunden (in der Naehe)
			SetPositionWorld	(pos);
			GetModel()->StartAni(anictrl->_s_walk);
			rbt.stand			= FALSE;
			rbt.targetReached	= TRUE;
			rbt.dirChoosed		= FALSE;
			rbt.lastDirections.DeleteList();
			return TRUE;
		} else {
			// Keine punktgenaue Positionierung möglich
			rbt.exactPosition = FALSE;
		}
	} else {
		rbt.lastTargetDist = rbt.targetDist;
	}
	return FALSE;	
}

/*--------------------------------------------------------------------------

    oCNpc::RobustTrace()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: RobustTrace ()
// IN :
// csg->targetPos		-> zu suchende Position
// csg->targetMode!=0	-> Nach Erreichen des Zieles stehenbleiben
{
	// Setting Flags
	anictrl -> SetConfigDoWallSliding(FALSE);
	SetWalkStopChasm(rbt.useChasmChecks);

	// Entfernung zum Ziel
	// Im Tauchmodus sind alle 3 Dimensionen relevant
	// rbt.targetDist = GetDistanceToPos2(rbt.targetPos,anictrl->GetActionMode()!=ANI_ACTION_DIVE);
	rbt.targetDist = GetDistanceToPos2(rbt.targetPos);
	
	RbtCheckForSolution(GetPositionWorld(),rbt.targetPos);

	// Entfernung ok ?
	if (!rbt.stand) rbt.stand = (rbt.targetDist <= rbt.maxTargetDist);
	
	// Jetzt stehenbleiben ?
	if (rbt.standIfTargetReached) {
	
		if (rbt.exactPosition && rbt.stand) {
			// Punktgenau positionieren
			rbt.failurePossibility	= 0.0f;
			RbtMoveToExactPosition();		
		
		} else if (rbt.stand) {
			// Stehenbleiben
			anictrl -> StopTurnAnis();
			anictrl ->_Stand();
			if (anictrl->IsStanding()) {
				rbt.stand				= FALSE;
				rbt.targetReached		= TRUE;
				rbt.dirChoosed			= FALSE;
				rbt.failurePossibility	= 0.0f;
				rbt.lastDirections.DeleteList();
				return TRUE;
			}
			return FALSE;
		}
	
	} else if (rbt.stand) {
		// Nicht stehenbleiben, Ziel aber trotzdem erreicht
		rbt.targetReached		= TRUE;
		rbt.dirChoosed			= FALSE;
		rbt.failurePossibility	= 0.0f;
		rbt.lastDirections.DeleteList();
		return TRUE;	
	} 

	// Timing....
	rbt.timer -= ztimer.GetFrameTimeF();
	if (rbt.timer <= 0) {
		if (rbt.standIfTargetReached) {
			anictrl -> StopTurnAnis();
			anictrl ->_Stand();
			if (anictrl->IsStanding()) {
				rbt.stand				= FALSE;
				rbt.targetReached		= FALSE;
				rbt.dirChoosed			= FALSE;
				rbt.failurePossibility	= 0.0f;
				rbt.lastDirections.DeleteList();
				return TRUE;
			}
			return FALSE;
		}
		rbt.stand			= FALSE;
		rbt.targetReached	= FALSE;
		rbt.dirChoosed		= FALSE;
		rbt.lastDirections.DeleteList();
		return TRUE;
	};

	// Hindernisse abarbeiten
	if (anictrl->IsWalking() || anictrl->IsStanding() || anictrl->IsWalkingBackward() || (anictrl->GetActionMode()==ANI_ACTION_SWIM) || (anictrl->GetActionMode()==ANI_ACTION_DIVE)) {
		RbtCheckIfTargetVisible();
		RbtAvoidObstacles();
	} else {
		oCAIHuman* ai = zDYNAMIC_CAST<oCAIHuman>(GetAI());
		if (ai) ai->DoSimpleAI();
	}
	return FALSE;
};

zREAL oCNpc :: RbtCalcTurnDirection	( const zVEC3& cdNormal, zREAL dist, int lastObstacle )
{
	if (GetHomeWorld()) 
	{
		// test: hole nicht den nearest waypoint vom spieler, sondern vom ziel!
		zCWaypoint* wp = GetHomeWorld()->GetWayNet()->GetNearestWaypoint(rbt.targetPos);
		if (wp) 
		{ 
			zREAL dist = (wp->GetPositionWorld() - rbt.targetPos).Length2();
			if ((dist<600*600) && FreeLineOfSight_WP(wp->GetPositionWorld()) )
			{
				// WP frei, dann mal lieber da hingehen....
				zREAL azi,elev;
				GetAngles(wp->GetPositionWorld(),azi,elev);
				if (abs(int(azi))<=90) {
					if (azi>=0) return -1;
					else		return  1;
				}
			}
		}

		// hier hat man nun entweder keinen nearest wp gefunden, oder die distanz war zu gross, oder der wp war nicht
		// sichtbar
		// zweiter versuch mit Nearest WP des NSCs
		/*zCWaypoint**/ wp = GetHomeWorld()->GetWayNet()->GetNearestWaypoint(GetPositionWorld());
		if (wp) 
		{ 
			zREAL dist = (wp->GetPositionWorld() - GetPositionWorld()).Length2();
			if ((dist<400*400) && FreeLineOfSight_WP(wp->GetPositionWorld())) 
			{
				// WP frei, dann mal lieber da hingehen....
				zREAL azi,elev;
				GetAngles(wp->GetPositionWorld(),azi,elev);
				if (abs(int(azi))<=90) {
					if (azi>=0) return -1;
					else		return  1;
				}
			}
		};
	}
	// WPs alle ungültig, nun die turndirection richtung targetpos bewegen

	zVEC3	cdNormalRet;
	zREAL	turnDir		= (zVEC3(0,1,0) ^ cdNormal) * (rbt.targetPos - GetPositionWorld());
	
	//	In bevorzugter Richtung darf kein Abgrund liegen....
	zREAL floorDist = GetFallDownHeight() + 100;
	
	zVEC3			turnVec	= GetRightVectorWorld();
	if (turnDir>0)	turnVec	= -turnVec;

	if (GetAnictrl()->DetectChasm(GetPositionWorld(), turnVec * dist, floorDist, cdNormalRet)) {
		
		turnDir				= -turnDir;
		turnVec				= -turnVec;
		// Auch in annere Richtung ?
		if (GetAnictrl()->DetectChasm(GetPositionWorld(), turnVec * dist, floorDist, cdNormalRet)) {
			
			return turnDir;	// Keine guenstige Direction ermittelt....

		}
	}

	return turnDir;	
};

/*--------------------------------------------------------------------------

    oCNpc::RbtIsObjectObstacle()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: RbtIsObjectObstacle(zCVob* obstacle, const zVEC3& pos, const zVEC3& dir, zVEC3& cdNormal)
{
	//
	//	CODECHANGE [ROMAN]
	//
	if (!obstacle) zERR_FAULT( "U:RBT: oCNpc::RbtIsObjectObstacle() - Obstacle is INVALID !!!" );
	//
	//	CODECHANGE [ROMAN]
	//

	if (obstacle->GetCollDetDyn()) {
		
		// Safety : IgnoredByTraceRays ausschliessen....
		zBOOL ignoreRays = obstacle->GetIgnoredByTraceRay();
		if (ignoreRays) {
			zERR_WARNING("U:RBT: Obstacle ignore TraceRays");
			obstacle->SetIgnoredByTraceRay(FALSE);
		}

		// Ein NSC ist kein Hindernis (da vorher auf VobBox getestet)
		if (zDYNAMIC_CAST<oCNpc>(obstacle)) return FALSE;
		
		zTTraceRayReport traceReport;
		// Test auf Polyebene ! Huuuaaaaaaaaarrrrrr ! Wir haben ja Zeit.......
		if (obstacle->TraceRay(pos,dir,zTRACERAY_POLY_NORMAL,traceReport)) {
			cdNormal = traceReport.foundPolyNormal;
			// Winkel mit angeben
			zVEC3 dir1 = cdNormal;	dir1[VY] = 1;	// TEMP	
			zVEC3 dir2 = dir;		dir2[VY] = 1;	// TEMP
			int angle = (int)Alg_Rad2Deg(Alg_AngleRad(dir1,dir2));
			if (abs(angle)<90) cdNormal = -cdNormal;
			
			//zERR_WARNING("U:RBT:Normal-Angle : "+zSTRING(int(angle)));
			//zlineCache.Line3D (obstacle->GetPositionWorld(),obstacle->GetPositionWorld() + cdNormal*500,GFX_WHITE);
			obstacle->SetIgnoredByTraceRay(ignoreRays);
			return TRUE;
		}	
		obstacle->SetIgnoredByTraceRay(ignoreRays);
	}
	return FALSE;
};

/*--------------------------------------------------------------------------

    oCNpc::RbtGetObstacle()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 

/* Old Implmentation */
/*zBOOL oCNpc :: RbtGetObstacle(const zVEC3& pos, const zVEC3& dir, zCVob* &obstacle, zVEC3& cdNormal)
{
	zCWorld* world	= GetHomeWorld();
	obstacle		= NULL;

	if (world->TraceRayNearestHit(pos,dir,this,zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL | zTRACERAY_VOB_BBOX | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {
		// Anderes Objekt ?
		obstacle = world->traceRayReport.foundVob;
		if (obstacle) {

			// NSCs sind keine Hindernisse.
			if (dynamic_cast<oCNpc*>(obstacle))			return FALSE;
			// Treppen auch nicht.
			if (dynamic_cast<zCVobStair*>(obstacle))	return FALSE;

			return RbtIsObjectObstacle(obstacle,pos,dir,cdNormal);

		} else if (world->traceRayReport.foundPoly) {

			// Static Poly Hit.
			cdNormal	= world->traceRayReport.foundPoly->GetPlane().normal; 			
			// zVEC3 inter	= world->traceRayReport.foundIntersection;
			return TRUE;				
		
		} else {
		
//			zERR_WARNING("U:RBT: what the heck.... shitty obstacle found, but no further information. Great... ("+GetInstanceName()+")");
		}
	}	
	return FALSE;
};*/

zBOOL oCNpc :: RbtGetObstacle(const zVEC3& pos, const zVEC3& dir, zCVob* &obstacle, zVEC3& cdNormal)
{
	zCWorld*	world		= GetHomeWorld();
	zBOOL		contLoop	= FALSE;
	zBOOL		hit			= FALSE;

	zCArray<zCVob*> ignoreVobs;
	
	ignoreVobs.Insert(this);
	do {

		obstacle	= NULL;
		contLoop	= FALSE;

		// TODO : Hier eignet sich ein Trace-Ray-Cache !
		hit			= world->TraceRayNearestHit(pos,dir,&ignoreVobs,zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL | zTRACERAY_VOB_BBOX | zTRACERAY_VOB_IGNORE_NO_CD_DYN);

		if (hit) {
			// Anderes Objekt ?
			obstacle = world->traceRayReport.foundVob;
			if (obstacle) {

				// NSCs sind keine Hindernisse.
				if (zDYNAMIC_CAST<oCNpc>(obstacle))			return FALSE;

				// Muss sein, da es sonst Stellen gibt, wo Vob gefunden wird, 
				// nicht als Hindernis eingestuft wird und die Wand dahinter nicht (nie!) 
				// detected wird. Auch nicht von der zCAIPlayer...
				// -> Treppen sind keine Hindernisse.
				if (zDYNAMIC_CAST<zCVobStair>(obstacle) || !RbtIsObjectObstacle(obstacle,pos,dir,cdNormal)) {
					// kein logischer Treffer
					ignoreVobs.Insert(obstacle);
					contLoop = TRUE;
				} else {
					return TRUE;
				}

			} else if (world->traceRayReport.foundPoly) {

				// Static Poly Hit.
				cdNormal	= world->traceRayReport.foundPoly->GetPlane().normal; 			
				// zVEC3 inter	= world->traceRayReport.foundIntersection;
				return TRUE;				
			
			} else {
		
		//			zERR_WARNING("U:RBT: what the heck.... shitty obstacle found, but no further information. Great... ("+GetInstanceName()+")");
			}
		}
	} while (contLoop);

	return FALSE;
};

zBOOL oCNpc :: RbtGetSmallObstacle(const zVEC3& dir, zCVob* &obstacle, zVEC3& cdNormal)
{
	zCWorld*	world	= GetHomeWorld();
	obstacle			= NULL;
	
	// Position 10cm ueber den Boden ermitteln
	zVEC3		pos		= GetPositionWorld();
	pos[VY]				= anictrl->GetFeetY() + 10;
 	
	// NSCs werden von diesen Tests nicht erfasst (alle Morphmeshes ???) Hier egal.

	if (world->TraceRayNearestHit(pos,dir,this,zTRACERAY_STAT_POLY | zTRACERAY_POLY_NORMAL | /*zTRACERAY_VOB_BBOX | */zTRACERAY_VOB_IGNORE_NO_CD_DYN | zTRACERAY_VOB_IGNORE_CHARACTER)) {
		// Anderes Objekt ?
		obstacle = world->traceRayReport.foundVob;
		if (obstacle) {

			// NSCs sind keine Hindernisse.
			if (zDYNAMIC_CAST<oCNpc>(obstacle))		return FALSE;			
			// Treppen auch nicht.
			if (zDYNAMIC_CAST<zCVobStair>(obstacle))	return FALSE;

			// Ausser, wenn es das anvisierte Vob ist.....
			if (rbt.targetVob == obstacle)			return FALSE;
			
			if (world->traceRayReport.foundPoly)	cdNormal = world->traceRayReport.foundPolyNormal;
			else									cdNormal = -GetAtVectorWorld();
			
			// Mobs immer ausweichen, da Test auf Polyebene nicht immer Treffer bringt (zB. Tisch)
			if (zDYNAMIC_CAST<oCMOB>(obstacle))		return TRUE;

			return FALSE;
			
			if (RbtIsObjectObstacle(obstacle,pos,dir,cdNormal)) {
				if (!anictrl->CanWalkOnPoly(cdNormal)) return TRUE;
			}

//			return TRUE;
/*
			zTBBox3D bbox	= obstacle->GetBBox3DWorld();
			zREAL objHeight = bbox.maxs[VY] - bbox.mins[VY];
			
			zREAL selfHeight= GetPositionWorld() - GetAnictrl()->GetFeetY();

			// FIXME : Make it better !
			return (objHeight < selfHeight);*/
		} else {
			// Static hit....
			//cdNormal = world->traceRayReport.foundPolyNormal;
			//if (!anictrl->CanWalkOnPoly(cdNormal)) return TRUE;
		}
	}	
	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::RbtAvoidObstacle()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: RbtAvoidObstacles ()
{
	zVEC3 cdNormal;

	// Hindernis ermitteln
	// TEST : Distanz 100cm + Halbe Z-BBox-Ausmasse mit berücksichtigen.
	zTBBox3D bbox	= GetModel()->GetBBox3D();
	zREAL dist		= 100 + (bbox.maxs[VZ] - bbox.mins[VZ]) / 2;	
	int obst		= CanGo(dist,cdNormal);

	rbt.frameCtr++;

	// Debug : Detection Info 
	/*zSTRING s;
	switch (obst) {
		case NPC_OBST_NONE			:	s+=" nothing.";				break;
		case NPC_OBST_FALL			:	s+=" fall down.";			break;
		case NPC_OBST_WALL			:	s+=" wall.";				break;
		case NPC_OBST_WALL_CLIMB	:	s+=" wall (climbable)";		break;
		case NPC_OBST_CHASM			:	s+=" chasm.";				break;
		case NPC_OBST_NPC			:	s+=" npc.";					break;
		case NPC_OBST_LADDER		:	s+=" ladder.";				break;
		case NPC_OBST_STAIRS		:	s+=" stairs.";				break;
		case NPC_OBST_MOBINTER		:	s+=" mobsi.";				break;
		case NPC_OBST_JUMP			:	s+=" chasm (jumpable).";	break;	
	};
	zERR_WARNING("U: RBT: Obstacle :"+s);*/

	// Falls er sich einen Abhang runterfallen lassen soll, hier kurzzeitig das
	// DetectWalkStopChasm aus	
	if (obst==NPC_OBST_FALL) SetWalkStopChasm(FALSE);

	if (obst == NPC_OBST_WALL_CLIMB) {

		// Nur ausfuehren, wenn Hindernis zwischen NPC und Target liegt.
		if (RbtIsDirectionValid(cdNormal)) {
			//if (anictrl->GetActionMode()==ANI_ACTION_SWIM) 
			//	anictrl->Swim_ClimbLedge();
			//else
				anictrl->JumpForward();

		} else {
			obst = NPC_OBST_WALL;
		}
	}

	if (obst == NPC_OBST_WALL) {
		// ***********************
		// Wand
		// ausweichen vorbereiten
		// ***********************
		
		// Choose TurnDirection
		if (!rbt.dirChoosed) {
			rbt.dirTurn		= RbtCalcTurnDirection(cdNormal,dist,obst);
			rbt.dirChoosed	= TRUE;
		}
		
		// Muss das Model nach links oder rechts ausweichen ?

		//
		//	CODECHANGE [ROMAN]
		//
		zVALUE rotValue = this->GetTurnSpeed() * ztimer.GetFrameTimeF();
		//
		//	CODECHANGE [ROMAN] END
		//

		// FIXME :
		// Rotation muss ausgefuehrt werden, es darf kein Movement Block an sein, da
		// Sonst Rotation zurueckgesetzt wird, falls noch weitere Moves stattfinden, die
		// die Position ungueltig machen -> NSCs haengen an Waenden....
		if (rbt.dirTurn<0) {
			ForceRotation(+rotValue);
		} else {
			ForceRotation(-rotValue);		
		}
		
/*		if (rbt.dirTurn<0) {
			anictrl->TurnDegrees(+rotValue);
		} else {
			anictrl->TurnDegrees(-rotValue);		
		}
*/		
		if (RbtIsDirectionValid(cdNormal)) {
			
			oTDirectionInfo*	dirInfo							= RbtInsertDirection ( -cdNormal );
			if (dirInfo)		dirInfo->checkForSmallObject	= rbt.isObstVobSmall;
		}	

	} else if (obst == NPC_OBST_CHASM) {

		cdNormal = GetAtVectorWorld();

		// Choose Turn Direction
		if (!rbt.dirChoosed) {		
			rbt.dirTurn		= RbtCalcTurnDirection(-cdNormal,dist,obst);
			rbt.dirChoosed	= TRUE;
		}
		
		// * Turn *
		zVALUE rotValue = this->GetTurnSpeed() * ztimer.GetFrameTimeF(); //* 4;	// Fastturn, moeglichst schnell drehen...
		if (rbt.dirTurn<0) {
			ForceRotation(+rotValue);
		} else {
			ForceRotation(-rotValue);		
		}
		
		if (RbtIsDirectionValid(-cdNormal)) {
			oTDirectionInfo*	dirInfo	=  RbtInsertDirection ( cdNormal );
			if (dirInfo)		dirInfo -> checkForChasm = TRUE;
		}
		  
	} else if (obst == NPC_OBST_JUMP) {
		
		if (RbtIsDirectionValid(cdNormal)) anictrl->JumpForward();


	} else if (rbt.lastDirections.GetNumInList()>0) {
		// ***************************
		// Kein Hindernis
		// Direction-Liste abarbeiten
		// ***************************
		RbtCheckLastDirection(dist);
		
	} else {
		// ***************************
		// Kein Hindernis,
		// Keine optimalen Richtungen
		// Go straight ahead
		// ***************************
		rbt.dirChoosed = FALSE;
		Turn(rbt.targetPos);
	}

	if (anictrl->GetActionMode() == ANI_ACTION_DIVE) {
		
		// Auftauchen, as fast as possible....
		zREAL win = -this->GetTurnSpeed() * ztimer.GetFrameTime();

/*
		zREAL azi,elev,win;
		GetAngles(rbt.targetPos,azi,elev);
		// Winkelgeschwindigkeit 150 Grad/sec

		//
		//	CODECHANGE [ROMAN]
		//
		zREAL turn	= this->GetTurnSpeed() * ztimer.GetFrameTime();
		//
		//	CODECHANGE [ROMAN] END
		//

		if		(abs((int)elev)<turn)	win = -elev;
		else if (elev<0)				win	= zMax(-elev,turn);
		else							win	= zMin(elev,-turn);
*/
		anictrl -> DiveRotateX(win);		
	
	} else {
		
		// Tauchen nötig ?
		zCWaypoint* wp	= NULL;
		zCRoute* route	= GetRoute();			
		if (route) wp	= route->GetTargetWP();
		if (wp && wp->IsUnderwater() && (anictrl->GetActionMode()==ANI_ACTION_SWIM)) {
			// Tauchen an
			GetModel()	-> StartAni		(anictrl->t_swim_2_dive);
			anictrl		-> SetWalkMode	(ANI_WALKMODE_DIVE);
			anictrl		-> SetActionMode(ANI_ACTION_DIVE);				
		}
	}
	
	anictrl->_Forward();

	// ****************************************************************
	// Sachen die eine Wahrnehmung triggern, erst hinterher ! Prüfen !
	// ****************************************************************

	if (zDYNAMIC_CAST<oCNpc>(rbt.obstVob)) {

		// MoveMob Wahrnehmung
		MoveNpc_S(static_cast<oCNpc*>(rbt.obstVob));

	} else {
		
		oCMobDoor* door = zDYNAMIC_CAST<oCMobDoor>(rbt.obstVob);

		if (door && (door->GetScemeName().Search("DOOR")>=0) ) {
			// FIXME :  Erstmal nur Türen durchlassen, weil sonst Wahrnehmung oft getriggert wird ?
			MoveMob_S(static_cast<oCMobDoor*>(rbt.obstVob));
		}
	} 

	return FALSE;
}

/*--------------------------------------------------------------------------

    oCNpc::RbtIsDirectionValid()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: RbtIsDirectionValid (const zVEC3& direction)
// Is Obstacledirection betwenn NPC and TargetPos ?
{
	if (rbt.lastDirections.GetNumInList()<=0) {
		// Between NPC and Target.
		zVEC3 vecA = rbt.targetPos - GetPositionWorld();
		if ((vecA * direction)>0) {
			// Hindernis nicht zwischen NSC und Ziel...
			// Nicht eintragen...
			// zERR_WARNING("U:RBT: Obstacle not between NSC and Target.");
			return FALSE;
		}
	}
	return TRUE;
}

/*--------------------------------------------------------------------------

    oCNpc::RbtInsertDirection()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 

oCNpc::oTDirectionInfo* oCNpc :: RbtInsertDirection (zVEC3 direction)
{
	static zREAL ANGLERANGE = Alg_Deg2Rad(3.0f);
	
	// Direction als naechste anzustrebende Richtung eintragen
	direction[VY] = 0;
	// Alles Null, dann Safety....
	if ((direction[VX]==0) && (direction[VZ]==0)) return NULL;

	zBOOL				putEntryInList	= TRUE;
	oTDirectionInfo*	newDirInfo		= NULL;

	if (rbt.lastDirections.GetNumInList() > 0) {
		// Letzten Eintrag holen
		oTDirectionInfo* dirInfo		= rbt.lastDirections[rbt.lastDirections.GetNumInList()-1];
		zREAL angle						= Alg_AngleRad	(dirInfo->checkDirection,direction);
		putEntryInList					= zNotInRange	(angle,-ANGLERANGE,+ANGLERANGE);
	}
	if (putEntryInList) {
		// Und in Liste eintragen....
		newDirInfo						= zNEW(oTDirectionInfo);
		newDirInfo->checkDirection		= direction;
		newDirInfo->checkForChasm		= FALSE;
		newDirInfo->checkForSmallObject	= FALSE;
		newDirInfo->checkIfClimbable	= FALSE;
		rbt.lastDirections.Insert(newDirInfo);
	} 
	return newDirInfo;
}

/*--------------------------------------------------------------------------

    oCNpc::RbtCheckLastDirection()

    11-Oct-00       [Roman Keskenti]

					  Moved for useage with oNpc_Move.h

--------------------------------------------------------------------------*/ 
zBOOL oCNpc :: RbtCheckLastDirection (zREAL dist)
{
	if (!GetHomeWorld())	return FALSE;
	
	int numDirs				= rbt.lastDirections.GetNumInList();
	if (numDirs<= 0)		return FALSE;

	oTDirectionInfo* dirInfo = rbt.lastDirections[numDirs-1];

	// Kann Liste geloescht werden ?
	// a) wenn Target Visible und erster (Pruefe : oder einer der ?) Eintrag kein CHASM ist
	if (rbt.targetVisible && !dirInfo->checkForChasm) {
		rbt.dirChoosed = FALSE;
		rbt.lastDirections.DeleteList();
		return FALSE;
	}
	
	if (dirInfo) {
		zBOOL	turnAllowed	= TRUE;
		zCVob*	obstacle	= NULL;
		zVEC3	dir			= dirInfo->checkDirection;
		zVEC3	cdNormal;

		// ************************************************************
		// Step 1 : auf kleines Object testen ?
		// ************************************************************
		
		if (dirInfo->checkForSmallObject) {
			
			// 10 cm uebern Boden....
			zVEC3 startPos	= GetPositionWorld();
			startPos[VY]	= GetAnictrl()->GetFeetY() + 10;

			turnAllowed		= !RbtGetSmallObstacle(dir*dist,obstacle,cdNormal);
		}

		// ************************************************************
		// Step 2 : auf Abgrund testen ?
		// ************************************************************
		if (dirInfo->checkForChasm && turnAllowed) {
						
			int obstacleType = RbtChooseChasmAction(GetPositionWorld(), dir*dist);
			turnAllowed		 = (obstacleType==NPC_OBST_NONE) || (obstacleType==NPC_OBST_FALL) || (obstacleType==NPC_OBST_JUMP); 

		}
/*			if (GetAnictrl()->DetectChasm(GetPositionWorld(),dir*dist, floorDist, cdNormal)) {
				
//				turnAllowed = FALSE;
				turnAllowed = (floorDist < GetFallDownHeight());
			}
		}*/

		// ************************************************************
		// Step 3 : erkletterbar ? (Macht das Sinn, braucht das wer ?)
		// ************************************************************
		if (dirInfo->checkIfClimbable) {
			


		}

		// ************************************************************
		// Step 4 : Normales Hindernis auf Huefthoehe
		// ************************************************************
		if (turnAllowed) {
			
			turnAllowed = !RbtGetObstacle(GetPositionWorld(),dir*dist,obstacle,cdNormal);
		}

		// ************************************************************
		// Step 5 : Drehung ausfuehren
		// ************************************************************
		if (turnAllowed) {
			
			// Temp : ForceTurn
			zBOOL inMove = GetInMovement();
			if (inMove) EndMovement();

			zREAL w = Turn(GetPositionWorld() + dir * dist);

			if (inMove) BeginMovement();

			if (abs((int)w)<1) {
				// Alte Richtung erreicht, Vector entfernen.
				rbt.lastDirections.Remove(dirInfo);
				delete(dirInfo);
				return TRUE;
			}
		} 
	}

	return FALSE;
}

// 
// Follow - Erweiterungen
// 

zBOOL oCNpc :: RbtCheckIfTargetVisible()
// Results in rbt-Structure....
{
	const zREAL	RBT_CHECK_VISIBILITY_TIME	=  500.0f;	// 1 Sekunde
	const zREAL RBT_POSITION_UPDATE_TIME	=  500.0f;	// 3 Sekunden
	const zREAL RBT_POSITION_DISTANCE		=  150.0f;	// 3 Meter

	if (rbt.targetVob) {	
		rbt.checkVisibilityTime += ztimer.GetFrameTimeF();
		if (rbt.checkVisibilityTime >= RBT_CHECK_VISIBILITY_TIME) {
			// Neuer Check nur jede Sekunde...
			rbt.checkVisibilityTime -= RBT_CHECK_VISIBILITY_TIME;
			rbt.targetVisible = FreeLineOfSight(rbt.targetVob);			
		
			if (rbt.targetVisible) {
				// 
				// Sichtbar, nur aktuelle Target-Position interessiert....
				//
				rbt.targetPosArray[0]		= rbt.targetVob->GetPositionWorld();
				rbt.targetPos				= rbt.targetPosArray[0];
				rbt.targetPosCounter		= 0;
				rbt.targetPosIndex			= 0;
				rbt.positionUpdateTime		= RBT_POSITION_UPDATE_TIME;

				//zERR_WARNING("U: RBT: Cleared PosArray. Updating Position 0");
			}

		} 
		
		if (!rbt.targetVisible) {

			rbt.positionUpdateTime += ztimer.GetFrameTimeF();

			if (rbt.positionUpdateTime >= RBT_POSITION_UPDATE_TIME) {
				// Nicht sichtbares Ziel. Neue Position speichern....
				// Vorher sind die anderen Positionen in der Liste noch relevant
				rbt.positionUpdateTime -= RBT_POSITION_UPDATE_TIME;
				// Nur, wenn Entfernung sich mehr als 3m geaendert hat
				zVEC3 newPos = rbt.targetVob->GetPositionWorld();
				assert (rbt.targetPosCounter>=0);
				if ( (newPos - rbt.targetPosArray[rbt.targetPosCounter]).Length2() > RBT_POSITION_DISTANCE * RBT_POSITION_DISTANCE) {				
					if (rbt.targetPosCounter+1 < RBT_POSITION_INDEX_MAX) rbt.targetPosCounter++;
					rbt.targetPosArray[rbt.targetPosCounter] = rbt.targetVob->GetPositionWorld();
					//zERR_WARNING("U: RBT: Adding Position "+zSTRING(rbt.targetPosCounter));
				}
			}
		}
		
	} else {
	
		// Kein Vob vorhanden, also nur Position benutzen

		rbt.checkVisibilityTime += ztimer.GetFrameTimeF();
		if (rbt.checkVisibilityTime >= RBT_CHECK_VISIBILITY_TIME) {
			// Neuer Check nur jede Sekunde...
			rbt.checkVisibilityTime -= RBT_CHECK_VISIBILITY_TIME;
			rbt.targetVisible = FreeLineOfSight(rbt.targetPos);			
		}		
	}
	return rbt.targetVisible;
};

zBOOL oCNpc :: RbtGotoFollowPosition()
// Fuelle Rbt.targetPos mit aktuellem Ziel.
// berücksichtige dabei auch die TargetPosList....
// TRUE, wenn erreicht...
// max Reichweiten sind vorher vom Caller zu fuellen...
{	
	if (!rbt.targetVob) return TRUE;

	if (zInRange(rbt.targetPosIndex,0,RBT_POSITION_INDEX_MAX-1)) {
		rbt.targetPos = rbt.targetPosArray[rbt.targetPosIndex];
	} else {
		rbt.targetPos = rbt.targetVob->GetPositionWorld();
		//zERR_WARNING("U: RBT: NPC: Using direct !!!");
	}

	rbt.targetReached			= FALSE;
	rbt.standIfTargetReached	= (rbt.targetPosIndex<0) || (rbt.targetPosIndex==rbt.targetPosCounter);
	rbt.exactPosition			= FALSE;

	if (rbt.targetPosIndex>0) {
		// Entfernung korrigieren, darf bei Anlaufen der Punkte nicht Kampfentfernung sein....
		rbt.maxTargetDist		= 80 * 80;
	}

	zBOOL reached				= RobustTrace();
	if (reached) {
		if (rbt.targetPosIndex>=0) {

			//zERR_WARNING("U: RBT: Reached Position "+zSTRING(rbt.targetPosIndex));
			rbt.targetPosIndex++;
			rbt.dirChoosed = FALSE;
			rbt.lastDirections.DeleteList();
			
			if (rbt.targetPosIndex > rbt.targetPosCounter) {
				// All done
				rbt.targetPosIndex		= 0;
				rbt.targetPosCounter	= 0;
				rbt.targetPosArray[0]	= rbt.targetVob->GetPositionWorld();
			}
		}
	} else {
		//
		// Das Wegnetz zurate ziehen.... ?
		// 
		if (rbt.failurePossibility>=100) {
			
			oCMsgMovement* msg = zNEW(oCMsgMovement)(oCMsgMovement::EV_GOROUTE,rbt.targetPos);
			msg->SetHighPriority(TRUE);
			GetEM()->OnMessage	(msg, this);
			RbtReset();
		}
	}

	return reached;
}

zBOOL oCNpc :: CanStrafe(zBOOL dirLeft, zTModelAniID aniID)
{
	anictrl = GetAnictrl();
	if (!anictrl) return FALSE;

	zVEC3 cdNormal;
	zREAL floorDist			= GetFallDownHeight()+100.0f;	// High !
	zBOOL result			= TRUE;
	zBOOL oldDetectChasm	= anictrl->GetConfigDoDetectWalkStopChasm(); // GetConfigDoDetectWalkStopChasm();
	zREAL detectLength		= 150.0f;

	zCModelAni* ani			= GetModel()->GetAniFromAniID(aniID);
	if (ani) detectLength	= ani->GetAniTranslation().Length() + 20.0f;

	//zERR_WARNING("U: NPC: Strafe : Abgrund check : "+zSTRING(detectLength));

	// Abgruende mit beruecksichtigen....
	anictrl->SetConfigDoDetectWalkStopChasm(TRUE);

	if (dirLeft)	result	= (anictrl->CheckEnoughSpaceMoveLeft()  && !anictrl->DetectChasm(GetPositionWorld(),-GetRightVectorWorld()*detectLength,floorDist,cdNormal));						
	else			result	= (anictrl->CheckEnoughSpaceMoveRight() && !anictrl->DetectChasm(GetPositionWorld(), GetRightVectorWorld()*detectLength,floorDist,cdNormal));

	anictrl->SetConfigDoDetectWalkStopChasm(oldDetectChasm);

	return result;
};

zBOOL oCNpc :: CanJumpBack(zTModelAniID aniID)
{
	anictrl = GetAnictrl();
	if (!anictrl) return FALSE;

	zVEC3 cdNormal;
	zREAL floorDist			= GetFallDownHeight()+100.0f;	// High !
	zBOOL result			= TRUE;
	zBOOL oldDetectChasm	= anictrl->GetConfigDoDetectWalkStopChasm();
	zREAL detectLength		= 150.0f;

	zCModelAni* ani			= GetModel()->GetAniFromAniID(aniID);
	if (ani) detectLength	= ani->GetAniTranslation().Length() + 20.0f;

	//zERR_WARNING("U: NPC: Strafe : Abgrund check : "+zSTRING(detectLength));

	// Abgruende mit beruecksichtigen....
	anictrl -> SetConfigDoDetectWalkStopChasm(TRUE);

	result = (anictrl->CheckEnoughSpaceMoveBackward() && !anictrl->DetectChasm(GetPositionWorld(), -GetAtVectorWorld()*detectLength,floorDist,cdNormal));

	anictrl -> SetConfigDoDetectWalkStopChasm(oldDetectChasm);

	return result;
};

void oCNpc :: SetWalkStopChasm (zBOOL stop)
{
	if (GetAnictrl()) GetAnictrl()->SetConfigDoDetectWalkStopChasm(stop);
};

zBOOL oCNpc :: GetWalkStopChasm ()
{
	return (GetAnictrl() && GetAnictrl()->GetConfigDoDetectWalkStopChasm());
};
