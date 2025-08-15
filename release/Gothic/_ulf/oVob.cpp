/******************************************************************************** 
 
     $Workfile:: Ovob.cpp             $                $Date:: 14.03.01 21:17   $
     $Revision:: 31                   $             $Modtime:: 14.03.01 21:16   $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/Ovob.cpp $
 * 
 * 31    14.03.01 21:17 Wohlers
 * 
 * 30    14.03.01 18:01 Wohlers
 * 
 * 29    11.02.01 15:05 Wohlers
 * 
 * 28    10.02.01 20:48 Wohlers
 * 
 * 27    10.02.01 6:08 Hildebrandt
 * focus glow tuning
 * 
 * 26    10.02.01 1:12 Wohlers
 * Im Talkmode FokusNpc-Highlighting aus
 * 
 * 25    8.02.01 19:33 Wohlers
 * 
 * 24    8.02.01 15:44 Wohlers
 * 
 * 23    26.01.01 16:21 Moos
 * 
 * 22    19.01.01 1:05 Wohlers
 * 
 * 21    15.01.01 20:15 Moos
 * 
 * 20    8.01.01 22:43 Speckels
 * 
 * 19    8.01.01 20:09 Keskenti
 * 
 * 18    20.12.00 17:13 Moos
 * 
 * 17    15.11.00 13:12 Wohlers
 * 
 * 16    20.09.00 22:51 Wohlers
 * 
 * 15    12.09.00 19:11 Wohlers
 * 
 * 14    12.09.00 14:47 Wohlers
 * 
 * 13    11.09.00 19:24 Speckels
 * 
 * 12    7.09.00 21:05 Wohlers
 * 
 * 11    2.09.00 4:44 Wohlers
 * 
 * 10    22.08.00 15:18 Moos
 * 
 * 9     18.08.00 19:00 Moos
 * 
 * 8     16.08.00 21:18 Wohlers
 * 
 * 7     2.08.00 14:25 Wohlers
 * 
 * 6     21.07.00 15:35 Wohlers
 * 
 * 5     5.07.00 12:22 Wohlers
 * 
 * 4     22.05.00 18:43 Wohlers
 * Gothic 0.82
 * 
 * 5     9.05.00 20:20 Wohlers
 * Gothic 0.81
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 17    18.04.00 20:15 Wohlers
 * Kampfsystem Phase 1
 * Angepasst an ZenGin 0.89a
 * 
 * 16    9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 14    24.02.00 23:32 Wohlers
 * Fixes
 * 
 * 13    22.02.00 20:41 Wohlers
 * uSrc 0.73
 * 
 * 12    6.02.00 18:42 Wohlers
 * Various Fixes
 * 
 * 11    4.02.00 15:38 Wohlers
 * Bugfixes 
 * 
 * 10    3.02.00 18:18 Wohlers
 * Angepasst auf Engine 0.86
 * Neues AI-System
 * 
 * 9     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 8     9.12.99 22:33 Wohlers
 * 
 * 7     6.12.99 19:12 Wohlers
 * Waynet Erweiterungen I
 * 
 * 5     24.11.99 23:39 Wohlers
 * Release Phoenix 069b
 * Mobsi-Erweiterungen 
 * 
 * 4     23.11.99 18:50 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#include "zCore.h"

#include "zAlgebra.h"
#include "zview.h"
#include "zAICamera.h"
#include "zPhysics.h"
#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

#include "oVob.h"
#include "oNpc.h"
#include "oAniCtrl.h"
#include "oWorld.h"
#include "oAIShoot.h"
#include "ofocus.h"


#include "ogame.h"

#include "oMobInter.h"

#ifdef DEBUG_WOHLERS
#include "zMorphMesh.h"
#endif

const zSTRING SndMaterialName[6] = {
	"WOOD", "STONE", "METAL", "LEATHER", "CLAY", "GLAS"	
};

// Static
zCList <oCVob> debuglist;

oCVob::oCVob()
{
};

oCVob::~oCVob()
{
};

void oCVob::Init()
{
};

void oCVob :: ClearDebugList ()
{
	debuglist.DeleteList();
};

void oCVob :: ShowVobDebugInfo (zCCamera *camera)
{
	oCVob *vob;
	zCList <oCVob> *ele = debuglist.GetNextInList();
	while (ele) {
		vob =  ele->GetData();
		vob -> ShowDebugInfo (camera);
		ele =  ele -> GetNextInList();
	}
}

zBOOL oCVob :: GetShowDebug()
{
	return (debuglist.IsInList(this));
}

void oCVob :: ToggleShowDebug()
{
	if (debuglist.IsInList(this)) 
		debuglist.Remove(this);
	else
		debuglist.Insert(this);
}

void oCVob :: SetShowDebug(BOOL f)
{
	if (f) {
		if (!debuglist.IsInList(this)) debuglist.Insert(this);
	} else {
		debuglist.Remove(this);
	}
}

void oCVob :: ShowDebugInfo(zCCamera *cam)
{
	int			x,y;
	zSTRING		s;
	oCMobInter* mob = NULL;
	
	zVEC3 pos = GetPositionWorld();
	// Getting Y-Size of BBox
	zTBBox3D bbox = GetBBox3DWorld();
	pos[VY] += (bbox.maxs[VY] - bbox.mins[VY]) / 2;
	// Transform point to screen
	pos = cam->Transform (pos);
	if (pos[VZ]>=0) cam->Project (&pos, x, y);
	else return;

	if (pos[VZ]<1000) {
	
		zCModel*			model	= dynamic_cast<zCModel*>(GetVisual());
		zCModelAniActive*	ani		= NULL;
		
		x -= 30;
		x = screen -> anx(x); 
		y = screen -> any(y);
		// Show Debug Infos
		if (model) {
			for (int i=0; i<model->numActiveAnis; i++) {
				ani = model->aniChannels[i];
				if (ani->GetLayer()==1) {
					s = ani->GetAni()->GetAniName() + " (" + zSTRING(int(ani->GetActFrame())) +")";
					screen -> Print(x,y,s); y -= screen->FontY();
					break;
				}
			}

#ifdef DEBUG_WOHLERS
			// Search HeadNode
/*			zCModelNodeInst* head = model->SearchNode(zMDL_NODE_NAME_HEAD);
			if (head) {
				zCMorphMesh* vis = zDYNAMIC_CAST<zCMorphMesh> (head->GetNodeVisual());
				if (vis) {
					for (int i=0; i<vis->aniChannels.GetNum(); i++) {
						s = vis->aniChannels[i]->ani->GetName() + " (:" + zSTRING(int(vis->aniChannels[i]->ani->GetLayer())) +")";
						screen -> Print(x,y,s); y -= screen->FontY();
					};
				};		
			}*/
#endif
		}

		s = "CDS:"+zSTRING(GetCollDetStat()) + "  CDD:"+zSTRING(GetCollDetDyn());
		screen -> Print(x,y,s); y -= screen->FontY();
		if (y<=0) goto _quit;
		s = "PH:"+zSTRING(GetPhysicsEnabled()) + "  GR:"+zSTRING(GetRigidBody()->GetGravityEnabled());	
		screen -> Print(x,y,s); y -= screen->FontY();
		if (y<=0) goto _quit;
		s = "SL:"+zSTRING(GetSleeping()) + "  AI:";
		if (GetAI())	s += GetAI()->GetClassName_();
		else			s += "-None-";
		screen -> Print(x,y,s); y -= screen->FontY();
		if (y<=0) goto _quit;
		s = "REF:"+zSTRING(GetRefCtr());	
		screen -> Print(x,y,s); y -= screen->FontY();
		
		mob = zDYNAMIC_CAST<oCMobInter>(this);
		if (mob) {
			s = "ST:"+zSTRING(mob->GetState())+" SC:"+mob->GetScemeName();
			screen -> Print(x,y,s); y -= screen->FontY();			
		}

_quit:
		; // ARGHHHH
	};
};

zBOOL oCVob :: HasNpcEnoughSpace (zVEC3 &vec)
{
	// TEST 2 - Für NSCs
	zVEC3 npos		= GetPositionWorld	();
	zTBBox3D bbox	= GetBBox3DWorld	();
	
	zCVob*				foundVob;
	zCArray<zCVob*>		ignoreVobList;
	zTTraceRayReport	traceReport;

	for (int i=0; i<3; i++) {
		zREAL d1		= npos[i] - bbox.mins[i];
		zREAL d2		= bbox.maxs[i] - npos[i];
		
		zVEC3 start		= vec;
		start[i]	   -= d1;
		zVEC3 dir		= zVEC3((i==0),(i==1),(i==2)) * (d1+d2);

		ignoreVobList.DeleteList();
		ignoreVobList.Insert	(this);

		do {

			foundVob = NULL;

			if (GetHomeWorld()->TraceRayNearestHit(start,dir,&ignoreVobList,zTRACERAY_VOB_BBOX | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {
				
				foundVob = GetHomeWorld()->traceRayReport.foundVob;

				if (foundVob) {
					if (zDYNAMIC_CAST<oCNpc>(foundVob)) {
						// NSC gefunden - auf keinen Fall Platz
						ignoreVobList.DeleteList();
						return FALSE;					

					} else if (foundVob->TraceRay(start,dir,zTRACERAY_POLY_NORMAL,traceReport)) {
						// Kolli gefunden, auf keinen Fall Platz
						ignoreVobList.DeleteList();
						return FALSE;
					}							
					ignoreVobList.Insert(foundVob);
				
				} else {
					// Static Poly hit
					return FALSE;
				} 
			}
		} while (foundVob);

	};
		
	// Es darf sich auch kein NSC drunter oder drüber befinden.... (sonst stapeln moeglich)
	if (GetHomeWorld()->TraceRayNearestHit(vec+zVEC3(0,200,0),zVEC3(0,-1000,0),this,zTRACERAY_VOB_BBOX | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {
			
		if (zDYNAMIC_CAST<oCNpc>(GetHomeWorld()->traceRayReport.foundVob)) return FALSE;
		
	}


	// Alles klar, kein Hindernis -> Platz ist da.
	return TRUE;	


/*			// Debug Info
			oCNpc*	thisNpc = (oCNpc*) this;
			if ((thisNpc->GetInstanceName()=="PC_ROCKEFELLER") || (thisNpc->GetInstanceName()=="GRD_201_FLETCHER01")) {
			
				zSTRING s		= "U:NPC:"+thisNpc->GetInstanceName()+"collides with ";

				// Hit occured, kein Platz.
				zCWorld*	world	= GetHomeWorld();
				zCVob*		vob		= world->traceRayReport.foundVob;
				if (vob) {
					oCNpc*	npc		= NULL;
					oCItem* item	= NULL;
					oCMOB*	mob		= NULL;
					if (npc		= dynamic_cast<oCNpc*>	(vob)) s+="NPC:"	+npc	-> GetInstanceName();
					if (item	= dynamic_cast<oCItem*>	(vob)) s+="ITEM:"	+item	-> GetInstanceName();
					if (mob		= dynamic_cast<oCMOB*>	(vob)) s+="MOB:"	+mob	-> GetName();			
					else s+="unknown:"+vob->GetVobName();
				} else {
					s += "static poly";
				};
			
				zERR_MESSAGE(5,0,s);
			};

*/							
/*			return FALSE;
		}
	};
	return TRUE;*/
}

zBOOL oCVob :: HasEnoughSpace (zVEC3 &vec)
// Prüfe, ob Vob an dieser Position in Welt eingefügt werden kann
// Muss in Welt eingefügt sein.
{
	if (!RegisteredInWorld()) {
 		zERR_WARNING("U: OVOB: Space-Test failed : Vob not in World.");
		return FALSE;
	}

	//zTVobCollType ct = GetCollType();
	//SetCollType		(zVOB_COLL_TYPE_BIG_OBJECT);

    zCCollisionObjectDef *cd = this->GetCollisionClass();
    SetCollisionClass (zCCollObjectComplex::S_GetCollObjClass());             // [Moos] 20.12.00 Anpassung an Vob-Änderung

	SetCollDet		(FALSE);
//	zVEC3 oldpos =	GetPositionWorld();
//	SetPositionWorld(vec);
//	SetCollDet		(TRUE);

    zMAT4 oldTrafo(GetOldTrafoObjToWorld());
    zMAT4 newTrafo(oldTrafo);
    newTrafo.SetTranslation(vec);

    zBOOL space =	!DetectCollision(&newTrafo);

	SetCollDet		(FALSE);                                            
    this->SetTrafoObjToWorld(oldTrafo);

//	SetPositionWorld(oldpos);

    SetCollisionClass(cd);                                   // [Moos] 20.12.00 Anpassung an Vob-Änderung
	//SetCollType		(ct);
	return space;
}

zBOOL oCVob :: SearchNpcPosition  (zVEC3& fit)
{
//	return TRUE;

	if (!GetHomeWorld()) {
		zERR_WARNING("U: OVOB: SearchNpcPos failed : HomeWorld == NULL.");
		return FALSE;
	}
	zVEC3 pos;
	zVEC3 center	= fit;	
	// center[VY] += 200;		// Test, 2m draufaddieren
	int	  ctr		= 0;
	int	  outerCtr	= 0;

	zREAL distx, distz;
	zTBBox3D	bbox	= GetBBox3DWorld();
	zREAL		add		= zMax(bbox.maxs[VX] - bbox.mins[VX],bbox.maxs[VZ] - bbox.mins[VZ]) * 1.5f;
	distx = distz = 100;
	do {
		do {
			switch (ctr) {
				case 0	:	pos = center;							break;
				
				case 1	:	pos	= center + zVEC3(     0, 0, distz);	break;
				case 2	:	pos	= center + zVEC3( distx, 0,    0);	break;
				case 3	:	pos	= center + zVEC3(     0, 0,-distz);	break;
				case 4	:	pos	= center + zVEC3(-distx, 0,    0);	break;
				
				case 5	:	pos	= center + zVEC3( distx, 0, distz);	break;
				case 6	:	pos	= center + zVEC3(-distx, 0, distz);	break;
				case 7	:	pos	= center + zVEC3(-distx, 0,-distz);	break;
				case 8	:	pos	= center + zVEC3( distx, 0,-distz);	break;
			}
			// FIXME : Check auf Positionshöhe -> innerhalb zB.2m Toleranz bleiben.
			if (zDYNAMIC_CAST<oCNpc>(this)) {
				if (GetFloorPosition(pos) && HasNpcEnoughSpace(pos)) {
					fit = pos;
					//zerr.Warning("U: OVOB: Npc chosen : "+zSTRING((outerCtr * 9)+ctr));
					return TRUE;
				}
			} else if (HasEnoughSpace(pos)) { 
				fit = pos;
				return TRUE;
			}
			
			ctr++;
		} while (ctr<9);
		
		ctr		= 0;
		distx  += add;
		distz  += add;
		outerCtr++;

	} while (outerCtr<6);	// 5x sollte reichen, oder ?

	zerr.Warning("U: OVOB: SearchNpcPos failed : Not enough space." + GetInstanceName());
	return FALSE;
}

zBOOL oCVob :: SearchFreePosition (zVEC3 &fit, zCVob* origin)
// zBOOL success : Found a Position
// Vob muss in Welt sein !
// Nur für Items und Mobs günstig, da diese nicht auf Boden gesetzt werden
// Für Npc : SearchFreeNpcPosition....
{
	if ((!origin) || (!origin->RegisteredInWorld())) {
		zERR_WARNING("U: OVOB: SearchPos failed : Origin or HomeWorld = NULL.");
		return FALSE;
	}
	zVEC3 best	= fit;
	zVEC3 dir	= origin->GetAtVectorWorld();
	// Get Size of Bounding Box
	zREAL stepsize[3];
	zTBBox3D box = GetBBox3DWorld();
	for (int i=0; i<3; i++) stepsize[i] = (box.maxs[i] - box.mins[i]) / 2;
	if (stepsize[VX]<10) stepsize[VX] = 10;
	if (stepsize[VZ]<10) stepsize[VZ] = 10;
	// Now Check Positions in front of Origin
	for (int x=0; x<=8; x++) {	
		switch (x) {
			case 0	:	/* Do nothing - original Pos */	break;
			case 1	:	fit[VX] -= stepsize[VX];		break;
			case 2	:	fit[VX] += stepsize[VX];		break;
			case 3	:	fit[VX] -= stepsize[VX] * 2;	break;
			case 4	:	fit[VX] += stepsize[VX] * 2;	break;
			case 5	:	fit[VX] -= stepsize[VX] * 3;	break;
			case 6	:	fit[VX] += stepsize[VX] * 3;	break;
			case 7	:	fit[VX] -= stepsize[VX] * 4;	break;
			case 8	:	fit[VX] += stepsize[VX] * 4;	break;
		}
		for (int z=0; z<=6; z++) {
			// a) Position vom Origin aus erreichbar ?
			// b) Platz genug da ?
			zCWorld* wld = origin->GetHomeWorld();
			zVEC3 org	 = origin->GetPositionWorld();
			if (!wld->TraceRayNearestHit (org, fit-org, origin, 0)) 
			if (HasEnoughSpace(fit)) {
				// Also, Platz ist da,
				return TRUE;
			}
			fit += dir * stepsize[VZ];
		}
	
		fit = best;
	}

	// Now Check Positions behind 
	for (x=0; x<=8; x++) {	
		switch (x) {
			case 1	:	fit[VX] -= stepsize[VX];		break;
			case 2	:	fit[VX] += stepsize[VX];		break;
			case 3	:	fit[VX] -= stepsize[VX] * 2;	break;
			case 4	:	fit[VX] += stepsize[VX] * 2;	break;
			case 5	:	fit[VX] -= stepsize[VX] * 3;	break;
			case 6	:	fit[VX] += stepsize[VX] * 3;	break;
		}		

		for (int z=0; z<7; z++) {
			// a) Position vom Origin aus erreichbar ?
			// b) Platz genug da ?
			zCWorld* wld = origin->GetHomeWorld();
			zVEC3 org	 = origin->GetPositionWorld();
			if (!wld->TraceRayNearestHit (org, fit-org, origin, zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE)) 
			if (HasEnoughSpace(fit)) {
				// Also, Platz ist da,
				return TRUE;
			}
			fit -= dir * stepsize[VZ];
		}
	
		fit = best;
	}
	return FALSE;
};

void oCVob :: SetOnFloor(zVEC3& centerPos)
// Setzt Objekt auf Bodenhoehe
// Bedingung : muss bereits in Welt eingefügt sein.
{
	zVEC3 newPos = centerPos;
	if (GetFloorPosition(newPos)) {
		SetPositionWorld(newPos);
	}
}

zBOOL oCVob :: GetFloorPosition(zVEC3& centerPos)
// Ermittelt die Position, die das Objekt haben muss, damit es auf den Boden steht.
// Ausgangspunkt pos
{
	if (!GetHomeWorld()) return FALSE;
	
	// Auf passende Höhe setzen
	zREAL diff		= GetPositionWorld()[VY] - GetBBox3DWorld().mins[VY];
	zCWorld* wld	= GetHomeWorld();

	if (wld->TraceRayNearestHit(centerPos,zVEC3(0,-1000,0),this,zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {
		// Poly gefunden
		if (wld->traceRayReport.foundPoly || wld->traceRayReport.foundVob) {
			// Schnittpunkt schnappen und Position neu setzen
			zVEC3 newpos = wld->traceRayReport.foundIntersection;
			// 4 cm bis zum Bodem, um Kollision zu vermeiden.
			newpos[VY] += diff + 4;
			centerPos = newpos;
			return TRUE;
		} 
	}	
	return FALSE;
}

zBOOL oCVob :: GetFloorPositionWithVob(zVEC3& centerPos, zCVob* &standingOnThisVob)
// Ermittelt die Position, die das Objekt haben muss, damit es auf den Boden steht.
// Ausgangspunkt pos
{
	standingOnThisVob = NULL;

	if (!GetHomeWorld()) return FALSE;
	
	// Auf passende Höhe setzen
	zREAL diff		= GetPositionWorld()[VY] - GetBBox3DWorld().mins[VY];
	zCWorld* wld	= GetHomeWorld();

	if (wld->TraceRayNearestHit(centerPos,zVEC3(0,-1000,0),this,zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {
		// Poly gefunden
		if (wld->traceRayReport.foundPoly || wld->traceRayReport.foundVob) {
			// Schnittpunkt schnappen und Position neu setzen
			zVEC3 newpos = wld->traceRayReport.foundIntersection;
			// 4 cm bis zum Bodem, um Kollision zu vermeiden.
			newpos[VY] += diff + 4;
			centerPos = newpos;
			standingOnThisVob = wld->traceRayReport.foundVob;
			return TRUE;
		} 
	}	
	return FALSE;
}

int oCVob :: GetInstance()
{
	return -1;
}

zSTRING oCVob :: GetInstanceName()
{
	return "";
}

void oCVob :: Archive (zCArchiver &arc)
{
	zCVob :: Archive (arc);
}

void oCVob :: Unarchive (zCArchiver &arc)
{
	zCVob :: Unarchive (arc);
}

void oCVob :: StartParticleEffects(zCTree<zCVob>* vobtree)
{
/* CODECHANGE Moos: This does not seem to have an effect any more.
                    the vob->ResetRotations() had a bad effect on the burning torch, deleting
                    the orientation of the visible part TORCH_BURNING relative to ITLSTORCHBURNING.

	if (!vobtree) return;

	zCVob* vob = vobtree->GetData();
	if (vob) {
		vob->ResetRotations();
		zCParticleFX* pfx	= dynamic_cast<zCParticleFX*>(vob->GetVisual());
		if (pfx) pfx->CreateParticles();
	}
			
	// recursive search
	zCTree<zCVob>* child = vobtree->GetFirstChild();
	while (child!=0) {
		StartParticleEffects(child);
		child	= child->GetNextChild();
	};

  END CODECHANGE Moos */
}

zBOOL zCCFASTCALL  oCVob::Render (zTRenderContext &renderContext)
{
	static int		talkIndex					= -2;
	static zCVob*	lastFocusVob				= NULL;
	static zREAL    currentFocusColorStrength   = 0.0f;    // 0..1

	renderContext.hintLightingHighlight			= FALSE;

	// Derzeitiges FocusVob ermitteln.
	zCVob* currentFocusVob = NULL;
	if (oCNpc::player && (!oCNpc::player->IsDead()) && (!oCNpc::player->IsUnconscious())) currentFocusVob = oCNpc::player->GetFocusVob();

	if (lastFocusVob != currentFocusVob) {
		// Neues Object im Fokus
        currentFocusColorStrength = 0.0f;
	}

	if (currentFocusVob == this) 
	{
		// Dieser Gegenstand im Focus....
		zBOOL doHighlighting = TRUE;

		// Nsc Im Talk-Modus ?
		oCNpc* currentFocusNpc = zDYNAMIC_CAST<oCNpc>(currentFocusVob);
		if (currentFocusNpc) {
			doHighlighting = ((oCNpcFocus::GetHighlightMeleeFocus()>=2) && oCNpcFocus::IsHighlightActive());
			//if (talkIndex==-2) talkIndex = parser.GetIndex("ZS_TALK");
			//doHighlighting = !currentFocusNpc->state.IsInState(talkIndex);
		}
		else if (oCMOB *mob = zDYNAMIC_CAST<oCMOB>(currentFocusVob))
		{
			if (oCMobInter *mobInter = zDYNAMIC_CAST<oCMobInter>(currentFocusVob))
			{
				if (mobInter->GetName().IsEmpty() || mobInter->IsInteractingWith(oCNpc::player)) 
					doHighlighting = FALSE;
			}
			else if (mob->GetName().IsEmpty()) doHighlighting = FALSE;
		}

		if (doHighlighting && (oCNpcFocus::GetHighlightInteractFocus() || ((oCNpcFocus::GetHighlightMeleeFocus()>=2) && oCNpcFocus::IsHighlightActive()))) 
		{
			// Swell aus - falls Item
			renderContext.hintLightingSwell = FALSE;

			// Einfade Geschwindigkeit
			currentFocusColorStrength		+= ztimer.GetFrameTimeF() * zREAL(0.003F);              
			zClamp01						(currentFocusColorStrength);

			renderContext.hintLightingHighlight				= TRUE;
			renderContext.hintLightingHighlightColor.SetRGBA(255,255,255,		// Focus-Farbe
															 zFloat2Int(currentFocusColorStrength*255));
		}
	} else if (!currentFocusVob) 
	{
		// Kein aktuelles FocusVob -> Werte wieder auf Null.
        currentFocusColorStrength = 0.0f;	
	}
    lastFocusVob = currentFocusVob;

	return zCVob::Render(renderContext);
};


oCAIVobMove* oCVob :: GetAIVobMove ()
{
	oCAIVobMove* ai = zDYNAMIC_CAST<oCAIVobMove>(GetAI());
	if (!ai) {
		// neue AI bauen
		// if (GetAI()) GetAI()->Release(); // CODECHANGE Moos: SetAI handles refcount
		SetAI (ai = zNEW( oCAIVobMove()) );
        ai->Release();
	}	
	return ai;
}

// ***********************************************************************************

const char* oCTouchDamage :: GetDamageTypeArcEnum (const zDWORD index)
{
	switch( index )
	{
		case oEDamageIndex_Barrier	:	return "Barrier"	;
		case oEDamageIndex_Blunt	:	return "Blunt"		;
		case oEDamageIndex_Edge		:	return "Edge"		;
		case oEDamageIndex_Fire		:	return "Fire"		;
		case oEDamageIndex_Fly		:	return "Fly"		;
		case oEDamageIndex_Magic	:	return "Magic"		;
		case oEDamageIndex_Point	:	return "Point"		;
		case oEDamageIndex_Fall		:	return "Fall"		;
	}

	// return "oCDamageType_Unknown";
	return 0;
}

zCLASS_DEFINITION_ABSTRACT	( oCVob,			zCVob, 0 )
zCLASS_DEFINITION			( oCTouchDamage,	zCTouchDamage, 0, 0 )