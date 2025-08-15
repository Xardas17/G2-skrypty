
/******************************************************************************** 
 
     $Workfile:: oWaynet.cpp          $                $Date:: 14.03.01 18:01   $
     $Revision:: 16                   $             $Modtime:: 14.03.01 17:25   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oWaynet.cpp $
 * 
 * 16    14.03.01 18:01 Wohlers
 * 
 * 15    13.03.01 18:36 Wohlers
 * Patches 1.07 1.Teil
 * 
 * 14    19.12.00 13:40 Wohlers
 * 
 * 13    18.12.00 14:36 Wohlers
 * 
 * 12    11.12.00 20:36 Wohlers
 * 
 * 11    10.10.00 19:13 Wohlers
 * 
 * 10    10.10.00 16:16 Wohlers
 * 
 * 9     20.09.00 22:51 Wohlers
 * 
 * 8     21.08.00 14:24 Wohlers
 * 
 * 7     17.08.00 23:09 Wohlers
 * 
 * 6     21.07.00 15:35 Wohlers
 * 
 * 5     22.05.00 18:44 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 4     8.05.00 19:32 Wohlers
 * Gothic 0.80 - Inventory
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 4     29.03.00 15:32 Wohlers
 * Various Bugfixes ( Waynet, Klettern )
 * 
 * 3     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 2     7.12.99 22:09 Wohlers
 * Trade Module
 * AssessGivenItem 
 * 
 * 1     6.12.99 15:14 Wohlers
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zWaynet.h"
#include "oWaynet.h"
#include "oNpc.h"
#include "oWorld.h"
#include "oMobInter.h"
#include "oGame.h"

// *******************************************************************************
// Waypoints
// *******************************************************************************

oCWaypoint :: oCWaypoint () : zCWaypoint()
{
};

oCWaypoint :: ~oCWaypoint ()
{
};

zBOOL oCWaypoint :: CanBeUsed (const zCVob* vob)
{
	// nur NPCs testen
	oCNpc* npc = dynamic_cast<oCNpc*>((zCVob*)vob);
	if (npc) {
		// a) Im Wasser ?
		if (waterDepth>0.0f) {
			// unter Wasser ? Tauchen ?
			if (underWater && npc->CanDive()) return TRUE;
			// Nein, aber Schwimmen sollte er schon können
			if (npc->CanSwim()) return TRUE;
			
			return FALSE;
		}		
	}
	return TRUE;
};

// *******************************************************************************
// Waypoints
// *******************************************************************************

oCWay :: oCWay () : zCWay()
{
	ladder	= NULL;
	door	= NULL;
};

oCWay :: ~oCWay ()
{
	zRELEASE(ladder);
	zRELEASE(door);
};

zBOOL oCWay :: CanBeUsed (const zCVob* vob)
{
	// nur NPCs testen

	oCNpc* npc = dynamic_cast<oCNpc*>((zCVob*)vob);
	if (npc) {
		// ***************************
		// Vielleicht eine Leiter da ?
		// ***************************
		if (GetLadder()) {
			if (npc->IsMonster())	return FALSE;
			else					return TRUE;
		}

		// **********************
		// b) Hindernis : Abgrund
		// **********************
		if (CanJump()) {
			// *****************
			// - überspringbar ?
			// *****************
			if (npc->GetJumpRange()	>= GetJumpDistance()) return TRUE;
			// ********************************
			// - fallenlassen und klettern ok ?
			// ********************************
			if ((npc->GetFallDownHeight() >= GetChasm()) && (npc->GetClimbRange() >= GetChasm())) return TRUE;
		
			return FALSE;
		
		} else if (GetChasm()>0.0) {
			// *******************
			// - fallenlassen ok ?
			// *******************
			if (npc->GetFallDownHeight() >= GetChasm()) return TRUE;
			return FALSE;
		}	
		// ************************************
		// c) Mobsi ? Hindernis ? Tür / Stein ?
		// ************************************
		
	}	
	
	return TRUE;
};

void oCWay :: Init (zCWaypoint *w1, zCWaypoint *w2)
// Objecte auf Weg einsammeln, sofern relevant -> Mobsis, in Liste packen
{
	zCWay :: Init (w1,w2);

	zTBBox3D bbox;
	zVEC3 mins	= zVEC3(zREAL_MAX,zREAL_MAX,zREAL_MAX);
	zVEC3 maxs	= zVEC3(zREAL_MIN,zREAL_MIN,zREAL_MIN);

	// Links
	zVEC3 pos	= GetLeftWaypoint()->GetPositionWorld();
	if (pos[VX]<mins[VX]) mins[VX] = pos[VX];
	if (pos[VX]>maxs[VX]) maxs[VX] = pos[VX];
	if (pos[VY]<mins[VY]) mins[VY] = pos[VY];
	if (pos[VY]>maxs[VY]) maxs[VY] = pos[VY];
	if (pos[VZ]<mins[VZ]) mins[VZ] = pos[VZ];
	if (pos[VZ]>maxs[VZ]) maxs[VZ] = pos[VZ];
	
	// Rechts
	pos	= GetRightWaypoint()->GetPositionWorld();
	if (pos[VX]<mins[VX]) mins[VX] = pos[VX];
	if (pos[VX]>maxs[VX]) maxs[VX] = pos[VX];
	if (pos[VY]<mins[VY]) mins[VY] = pos[VY];
	if (pos[VY]>maxs[VY]) maxs[VY] = pos[VY];
	if (pos[VZ]<mins[VZ]) mins[VZ] = pos[VZ];
	if (pos[VZ]>maxs[VZ]) maxs[VZ] = pos[VZ];
	
	// Sammeln
	zCArray <zCVob*> vobList;
	bbox.maxs = maxs; bbox.mins = mins;
	ogame->GetWorld()->CollectVobsInBBox3D (vobList, bbox);	
	
	oCMobLadder* foundLadder	= NULL;
	oCMobDoor*	 foundDoor		= NULL;

	for (int i=0; i<vobList.GetNumInList(); i++) {
				
		foundLadder = dynamic_cast<oCMobLadder*>(vobList[i]);
		if (foundLadder) {
			
			zVEC3 lowPos	= w1->GetPositionWorld();
			zVEC3 highPos	= w2->GetPositionWorld();
			if (lowPos[VY] > highPos[VY]) zSwap(lowPos,highPos);
			
			// Raytest, ob Leiter getroffen wird
			zTTraceRayReport report;
			if (foundLadder->TraceRay(lowPos,highPos-lowPos,zTRACERAY_VOB_BBOX,report)) {
			
				zVEC3 ladderMid	= foundLadder->GetBBox3DWorld().GetCenter();
				// a) HighPunkt muss ueber Haelfte der Leiter liegen....
				if ((lowPos[VY] < ladderMid[VY]) && ( highPos[VY] > ladderMid[VY])) {

/*					zVEC3 dir1	= foundLadder->GetPositionWorld() - w1->GetPositionWorld();
					zVEC3 dir2	= w2->GetPositionWorld() - w1->GetPositionWorld();
					dir1[VY]	= 1;
					dir2[VY]	= 1;
					zREAL angle = Alg_AngleRad(dir1,dir2);
					int	  result= abs(int(Alg_Rad2Deg(angle)));

					if (result<45) {	
*/						if (ladder) zERR_WARNING("U:WAY:Found multiple ladders on path "+w1->GetName()+"/"+w2->GetName());
						zRELEASE(ladder);		// Safety, da diese Sachen mehrfach durchlaufen werden können
						ladder = foundLadder;
						ladder -> AddRef();
//						zERR_WARNING("U:WAY: Ladder found ("+GetLeftWaypoint()->GetName()+"/"+GetRightWaypoint()->GetName());
/*					} else {
						zERR_WARNING("U:WAY: Ladder suspicious (Angle:"+zSTRING(result)+") ("+GetLeftWaypoint()->GetName()+"/"+GetRightWaypoint()->GetName());			
					}
*/
				} else {
					zERR_WARNING("U:WAY: Ladder highpoint error ("+GetLeftWaypoint()->GetName()+"/"+GetRightWaypoint()->GetName());				
				}
			}

		} else {
			
			foundDoor = dynamic_cast<oCMobDoor*>(vobList[i]);
			if (foundDoor) {				

				zVEC3 dir1	= foundDoor->GetPositionWorld() - w1->GetPositionWorld();
				zVEC3 dir2	= w2->GetPositionWorld() - w1->GetPositionWorld();
				dir1[VY]	= 1;
				dir2[VY]	= 1;
				zREAL angle = Alg_AngleRad(dir1,dir2);
				int	  result= abs(int(Alg_Rad2Deg(angle)));
				if (result<10) {					
					//if (door) zERR_WARNING("U:WAY:Found multiple doors on path "+w1->GetName()+"/"+w2->GetName());
					zRELEASE(door);		// Safety, da diese Sachen mehrfach durchlaufen werden können
					door = foundDoor;
					door -> AddRef();
					//zERR_WARNING("U:WAY: Door found ("+GetLeftWaypoint()->GetName()+"/"+GetRightWaypoint()->GetName());
				}
			}
		}
	}
};

zBOOL oCWay :: IsObjectOnWay (const zCVob* object)
{
	return ( (ladder == object) || (door == object) );
};

oCMobLadder* oCWay :: GetLadder ()
{
	return ladder;
};

oCMobDoor* oCWay :: GetDoor ()
{
	return door;
};

