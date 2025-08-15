/******************************************************************************** 
 
     $Workfile:: zVobMove.cpp         $                $Date:: 17.03.01 2:10    $
     $Revision:: 12                   $             $Modtime:: 17.03.01 1:30    $
        Author:: Hildebrandt                                                    
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/ZenGin/_Dieter/zVobMove.cpp $
 * 
 * 12    17.03.01 2:10 Hildebrandt
 * 
 * 11    8.02.01 14:53 Moos
 * 
 * 10    5.02.01 18:01 Moos
 * 
 * 9     2.02.01 17:53 Moos
 * 
 * 8     23.01.01 21:01 Hildebrandt
 * 
 * 7     23.01.01 18:11 Hildebrandt
 * 
 * 6     14.01.01 16:36 Hildebrandt
 * 
 * 5     11.01.01 18:46 Hildebrandt
 * 
 * 4     10.01.01 17:11 Hildebrandt
 * 
 * 3     8.01.01 17:56 Hildebrandt
 * 
 * 2     21.12.00 18:27 Hildebrandt
 * 
 * 1     20.12.00 3:04 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt
/// @version $Revision: 12 $ ($Modtime: 17.03.01 1:30 $)

// ==================================================================================================================

#include <zCore.h>
#include <zVob.h>
#include <zWorld.h>
#include <zPhysics.h>
#include <zVisual.h>
#include <zGrafix.h>
#include <zAI.h>
#include <zEventMan.h> 

#include <zModel.h>
#include <zMorphMesh.h>

// ==================================================================================================================

#include <zCollisionDetector.h>
#include <zCollisionObject.h>
#include <zCollisionObjectMisc.h>

// FIXME TMPE
#include <zVobMisc.h>

#include <zAccount.h>

// ==================================================================================================================

#ifdef DEBUG_HILDEBRANDT
//	#define zVOB_DEBUG_CD
//	#define zDEBUG_EVENT_MESSAGES
	#define zDEBUG_COLLECT_STATS
#endif

 
#ifdef zVOB_DEBUG_CD 
	static inline void db_Print				(const zSTRING& s)											{ zerr.Message ("D: VOB_CD: "+s); };
	static inline void db_PrintBlockBegin	()															{ zERR_MESSAGE (1, zERR_BEGIN, ""); };
	static inline void db_PrintBlockEnd		()															{ zERR_MESSAGE (1, zERR_END, "");	};
	static inline void db_Line3D			(const zPOINT3& a, const zPOINT3& b, int color= GFX_YELLOW) { zlineCache.Line3D (a,b, color);	};
	static inline void db_DrawBBox3D		(const zTBBox3D bbox, int color= GFX_YELLOW)				{ bbox.Draw (color); };
	static inline void db_DrawBSphere3D		(const zTBSphere3D bbox, int color= GFX_YELLOW)				{ bbox.Draw (color); };
	static inline void db_DrawWire			(zCPolygon *poly, int color= GFX_YELLOW)					{ poly->DrawWire (color); }; 
#else										
	static inline void db_Print				(const zSTRING& s)											{ };
	static inline void db_PrintBlockBegin	()															{ };
	static inline void db_PrintBlockEnd		()															{ };
	static inline void db_Line3D			(const zPOINT3& a, const zPOINT3& b, int color= GFX_YELLOW) { };
	static inline void db_DrawBBox3D		(const zTBBox3D bbox, int color= GFX_YELLOW)				{ };
	static inline void db_DrawBSphere3D		(const zTBSphere3D bbox, int color= GFX_YELLOW)				{ };
	static inline void db_DrawWire			(zCPolygon *poly, int color= GFX_YELLOW)					{ }; 
#endif

// ==================================================================================================================


/*
 Evtl. moechte man hier die Abhaengigkeiten zum zCMover aufloesen (waere schoener).
 Alternativen:
 a) "AutoLink" ist ein Feature, dass alle Vob-Klassen haben koennen und somit in der zCVob Basisklasse integriert ist. 
    Diese melden dann per Virtual, ob sie es nutzen wollen.
 b) Nur die zCMover verfuegt ueber 'autoLink'. Code dafuer liegt komplett in der zCMover Klasse.

*/

zCVob* zCVob::GetAutoLinkParent (zCVob *childVob) 
{
	if (
		(childVob->globalVobTreeNode)							&&
		(childVob->globalVobTreeNode->GetParent())				&&
		(childVob->globalVobTreeNode->GetParent()->GetData())) 
	{
		zCMover *mover = dynamic_cast<zCMover*>(childVob->globalVobTreeNode->GetParent()->GetData());
		if ((mover) && (mover->GetAutoLinkEnabled()))	return mover;
		else											return 0;
	}
	else
		return 0;
};

zBOOL zCVob::CanAutoLinkWith (zCVob *childVob, zCVob *parentVob)
{
	assert (childVob);
	zBOOL doit	= ((childVob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NONE) && (!childVob->GetPhysicsEnabled())) ||
				  ((childVob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_NONE) && ( childVob->GetPhysicsEnabled()));
	zBOOL hasParent		=  childVob->HasParentVob();

	if (doit)														// child im richtigen Class/Physik Zustand
	if (!hasParent)													// child selber noch nicht gelinkt
	if (!childVob->GetStaticVob())									// kein statisches Objekt
	if ( childVob->GetCollDetDyn())									// dynamische Kollision
	{
		zPOINT3 startPos	= childVob->GetPositionWorld();
		startPos[VY]		= childVob->GetBBox3DWorld().maxs[VY];
//		zREAL scanLen		= zAbsApprox(startPos[VY] - childVob->GetBBox3DWorld().mins[VY]) * zREAL(100.0F);
		zREAL scanLen		= 100000.0F;
		if (parentVob) {
			zTTraceRayReport report;
			zBOOL res		= parentVob->TraceRay (startPos, zVEC3(0,-scanLen,0), 0, report);
			parentVob		= res ? report.foundVob : 0;
			if (!parentVob) return FALSE;
		} else {
							  childVob->GetHomeWorld()->TraceRayNearestHit (startPos, zVEC3(0,-scanLen,0), childVob,	zTRACERAY_STAT_IGNORE | zTRACERAY_VOB_IGNORE_NO_CD_DYN);
			parentVob		= childVob->GetHomeWorld()->traceRayReport.foundVob;
			if (parentVob) {
				zCMover *mover = dynamic_cast<zCMover*>(parentVob);
				if ((!mover) || (!mover->GetAutoLinkEnabled())) {
					return FALSE;
				};
			};
		};
//		zerr.Message ("D: Can Link!"); 
		return TRUE;
	};
	return FALSE;
};

void zCVob::CheckAutoLink (zCVob *childVob, zCVob *parentVob)
{
	// unter welchen einfachen Grundbedingungen wird ein ChildVob an ein ParentVob gelinkt ?
	// - kein Static-Flag
	// - dyn. Collision ein
	// - kein Parent-Vob

	static int guard = TRUE;
	if (!guard) return;
	assert (childVob);

	zBOOL doit			= ((childVob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NONE) && (!childVob->GetPhysicsEnabled())) ||
						  ((childVob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_NONE) && ( childVob->GetPhysicsEnabled()));
	zBOOL hasParent		=  childVob->HasParentVob();

	if (doit)
	if (!hasParent)
	if (!childVob->GetStaticVob())									// kein statisches Objekt
	if ( childVob->GetCollDetDyn())									// dynamische Kollision
	{
		zPOINT3 startPos	= childVob->GetPositionWorld();
		startPos[VY]		= childVob->GetBBox3DWorld().maxs[VY];
		zREAL scanLen		= zAbsApprox(startPos[VY] - childVob->GetBBox3DWorld().mins[VY]) * zREAL(3.0F);
		zBOOL res;
		if (parentVob) {
			zTTraceRayReport report;
			res				= parentVob->TraceRay (startPos, zVEC3(0,-scanLen,0), 0, report);
			parentVob		= res ? report.foundVob : 0;
		} else {
			res				= childVob->GetHomeWorld()->TraceRayNearestHit (startPos, zVEC3(0,-scanLen,0), childVob,	zTRACERAY_STAT_IGNORE | zTRACERAY_VOB_IGNORE_NO_CD_DYN);
			parentVob		= childVob->GetHomeWorld()->traceRayReport.foundVob;
		};
		
		if (parentVob) 
		{
			zCMover *mover = dynamic_cast<zCMover*>(parentVob);
			if (mover)
			if (mover->GetAutoLinkEnabled())
			{
				guard = FALSE;
				zBOOL cdDyn	= childVob->GetCollDetDyn		();
				zBOOL cdStat= childVob->GetCollDetStat		();
				zMAT4 trafoWorld							= childVob->trafoObjToWorld;
				childVob->SetCollDet						(FALSE);
				childVob->GetHomeWorld()->MoveVobSubtreeTo	(childVob, parentVob);
				childVob->SetTrafoObjToWorld				(trafoWorld);
				childVob->SetPhysicsEnabled					(FALSE);
				childVob->SetCollDetDyn						(cdDyn);
				childVob->SetCollDetStat					(cdStat);
//				zerr.Message								("D: link");
				guard = TRUE;
			};
		}
	};
};

void zCVob::CheckAutoUnlink (zCVob *childVob)
{
	static int guard = TRUE;
	if (!guard) return;

	zERR_ASSERT (childVob);

	zBOOL doit			= ((childVob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NONE) && (!childVob->GetPhysicsEnabled())) ||
						  ((childVob->GetCharacterClass()==zCVob::zVOB_CHAR_CLASS_NONE) && ( childVob->GetPhysicsEnabled()));
	zCVob* linkParent	=  zCVob::GetAutoLinkParent (childVob);

	if (doit)
	if (linkParent)
	if (!childVob->GetStaticVob())									// kein statisches Objekt
	if ( childVob->GetCollDetDyn())									// dynamische Kollision
	{
		zPOINT3 startPos	= childVob->GetPositionWorld();
		startPos[VY]		= childVob->GetBBox3DWorld().maxs[VY];
		zREAL scanLen		= zAbsApprox(startPos[VY] - childVob->GetBBox3DWorld().mins[VY]) * zREAL(1.5F);
		zTTraceRayReport report;
		zBOOL res			= linkParent->TraceRay (startPos, zVEC3(0,-scanLen,0), 0, report);
		
		if (!res) 
		{
			guard = FALSE;
			zBOOL cdDyn	= childVob->GetCollDetDyn				();
			zBOOL cdStat= childVob->GetCollDetStat				();
			zMAT4 trafoWorld									= childVob->trafoObjToWorld;
			childVob->SetCollDet								(FALSE);
			childVob->GetHomeWorld()->MoveVobSubtreeToWorldSpace(childVob);
			childVob->SetTrafoObjToWorld						(trafoWorld);
			childVob->SetCollDetDyn								(cdDyn);
			childVob->SetCollDetStat							(cdStat);
//			zerr.Message										("D: unlink");
			guard = TRUE;
		};
	};
};

// ==================================================================================================================

void zCVob::CalcGroundPoly() 
{
	//
	zERR_ASSERT (homeWorld);
	const zPOINT3& startPos = GetBBox3DWorld().GetCenter();
	
	// Effekt Vobs brauchen keine groundpolys
	// [EDENFELD] Nachtrag: 1.23: Doch und zwar wird in zCBspTree::AddVobsToRenderListOutDoor(zCBspSector, zTBBox2D)
	// über das Groundpoly abgefragt, in welchem Sektor sich der Vob befindet.
	// ist kein Groundpoly dort vorhanden, wird der Vob dann nicht gerendert -> Crap
	// Ergo: Nicht mit Groundpolys rumspielen, auch an anderen Stellen wird das Ding sicher gebraucht
	//if (GetDontWriteIntoArchive())	return;			

	// FIXME: ACHTUNG bei Level/World wechseln !
	// FIXME: ist 'etwas' ungenau, wenn ein WasserPoly(z.B.Teich) den statischen Level durchdringt
	if ((GetGroundPoly()) &&
		(GetGroundPoly()->GetMaterial()->GetMatGroup()!=zMAT_GROUP_WATER))
	{
		// ist das alte GroundPoly immer noch aktuell ?
		// ACHTUNG: dies Methode kann unter Umständen fehlerhaft sein: ein zweites Poly koennte sich dazwischenschieben
		// const zREAL testRayLen	= (GetBBox3DWorld().maxs[VY] - GetBBox3DWorld().mins[VY]);		// FixVersuch fuer: Char verschwindet oberhalb von Portalraeumen (OC/NC); erstmal nicht benutzt: wuerde einiges mehr an Rays bedeuten, korrekter Fix waere: die Infos der CollDetChar hier wiederverwenden
		zVEC3		inters;
		zREAL		alpha;
		if (GetGroundPoly()->CheckRayPolyIntersection (startPos, zVEC3(0,-20000,0), inters, alpha)) return;
	};

	GetHomeWorld	()->TraceRayNearestHit (startPos, zVEC3(0,-20000,0), (zCVob*)0,	zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE | zTRACERAY_POLY_2SIDED);

	// Falls der erste Ray ab Box-Center kein GroundPoly gefunden hat, oder ein Poly backface getroffen wurde 
	// (=> StartPunktbefand sich aler Wahrscheinlichkeit nach ausserhalb des Levels) wird ein weiterer Versuch
	// ab oberem Center der BBox gestartet (=> z.B. fuer manche Objekte in Sektoren, die tiefer im Boden stecken).
	if ((!GetHomeWorld()->traceRayReport.foundPoly) ||						// kein Poly gefunden?
	    (GetHomeWorld()->traceRayReport.foundPoly->GetNormal()[VY]<=0))		// oder backfacing?
	{
		zVEC3 topStartPos	= startPos;
		topStartPos[VY]		= GetBBox3DWorld().maxs[VY];
		GetHomeWorld	()->TraceRayNearestHit (topStartPos, zVEC3(0,-20000,0), (zCVob*)0,	zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE);
	};
	SetGroundPoly	(GetHomeWorld()->traceRayReport.foundPoly);
};

// ==================================================================================================================

void zCVob::CalcWaterVob() 
{
	if (this->GetCharacterClass()!=zVOB_CHAR_CLASS_NONE) return;			// nur normale vobs die sich bewegen können was mit der underwater info anfangen
	if (GetDontWriteIntoArchive())						 return;			// Effekt Vobs brauchen keine Wasserinfos (FIXME: Ausnahme: Firegolems)

	//
	zERR_ASSERT (homeWorld);
	zPOINT3& startPos		= GetBBox3DWorld().GetCenter();
	startPos[VY]			= GetBBox3DWorld().maxs[VY];

	GetHomeWorld()->TraceRayNearestHit (startPos, zVEC3(0,20000,0), (zCVob*)0,	zTRACERAY_STAT_POLY | zTRACERAY_VOB_IGNORE | zTRACERAY_POLY_TEST_WATER);

	if (!GetHomeWorld()->traceRayReport.foundPoly)	this->bIsInWater = FALSE;
	else											this->bIsInWater = GetHomeWorld()->traceRayReport.foundPoly->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER;
};

// ==================================================================================================================


void zCVob::SetCollTypeDefaultFromVisual () 
{
	// Collision-Type festlegen
//	if (GetCollType()==zVOB_COLL_TYPE_UNDEF) 
	{
		if ((GetCharacterClass()==zVOB_CHAR_CLASS_PC) || (GetCharacterClass()==zVOB_CHAR_CLASS_NPC))
		{
//			SetCollisionClass (zCCollObjectCharacter::S_GetCollObjClass());
		} else
		if ((GetVisualClass()==zCMesh::GetStaticClassDef()) || 
			(GetVisualClass()==zCModel::GetStaticClassDef()) ||
			(GetVisualClass()==zCMorphMesh::GetStaticClassDef()) ||
		    (GetVisualClass()==zCProgMeshProto::GetStaticClassDef()))
		{ 
			const zREAL vol = visual->GetBBox3D().GetVolume();
			if (vol<200000)	
			{
				SetCollisionClass (zCCollObjectPoint::S_GetCollObjClass());
			} else 
			{
				SetCollisionClass (zCCollObjectComplex::S_GetCollObjClass());
			};
		} else
			SetCollisionClass (zCCollObjectUndef::S_GetCollObjClass());
	};
};

// ==================================================================================================================

// Methoden, die innerhalb eines Begin/EndMovement Blockes Zustaende veraendern

//#define MOVE_BLOCK_UPDATE_VOB_TRAFOS

void zCVob::TouchMovement () 
{ 
	zERR_ASSERT (GetInMovement()); 
	zERR_ASSERT (GetCollisionObject()); 
	if (GetInMovement())
		GetCollisionObject()->SetTrafoHintTranslation(); 
};

const zMATRIX4& zCVob::GetNewTrafoObjToWorld () const
{ 
	return (GetInMovement()) ? GetCollisionObject()->GetTrafoNew() : trafoObjToWorld; 
};

zMATRIX4& zCVob::GetNewTrafoObjToWorld () 
{ 
	return (GetInMovement()) ? GetCollisionObject()->GetTrafoNew() : trafoObjToWorld; 
};

void zCVob::SetNewTrafoObjToWorld (const zMATRIX4& newTrafo) 
{ 
	if (GetInMovement()) GetCollisionObject()->SetTrafoNew(newTrafo);		
};

/*
	2 Zugaenge:
	a) API, also von aussen	: Set/GetBBox3DWorld/Local()..
	b) internas				: ..
*/

void zCVob::SetBBox3DWorld (const zTBBox3D& b)	
{ 
	// bbox auf einem Vob mit Visual setzen macht keinen Sinn
	if (GetVisual()) return;

	const zBOOL local = !GetInMovement();
	if (local) BeginMovement();
	bbox3D			= b; 

	GetCollisionObject()->SetTrafoHintTranslation	();

	if (local) EndMovement(FALSE);
};

void zCVob::SetBBox3DLocal (const zTBBox3D& b)	
{
	// bbox auf einem Vob mit Visual setzen macht keinen Sinn
	if (GetVisual()) return;

	const zBOOL local	= !GetInMovement();
	if (local) BeginMovement();
	bbox3D				= b;
	bbox3D.Translate	(trafoObjToWorld.GetTranslation());

	this->GetCollisionObject()->SetTrafoHintTranslation	();

	if (local) EndMovement(FALSE);
};

zTBBox3D zCVob::GetBBox3DLocal() const 
{ 
	if ((GetVisual() && (GetVisual()->IsBBox3DLocal())))
	{
		return GetVisual()->GetBBox3D();
	} else 
	{
		zTBBox3D bbox3DLocal	= bbox3D;
		bbox3DLocal.Translate	(-trafoObjToWorld.GetTranslation());
		return bbox3DLocal;	
	};
};

void zCVob::Move (zVALUE x, zVALUE y, zVALUE z) 
{
	MoveWorld (x,y,z);
}

void zCVob::MoveWorld (zVALUE x, zVALUE y, zVALUE z) 
{
	const zBOOL local	= !GetInMovement();
	if (local)			BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafoObjToWorld.Translate	(zPOINT3 (x,y,z));
		CorrectTrafo				();
	#endif

	GetCollisionObject()->GetTrafoNew().Translate	(zPOINT3 (x,y,z));
	GetCollisionObject()->SetTrafoHintTranslation	();

	if (local)		EndMovement();
}

void zCVob::MoveLocal (zVALUE x, zVALUE y, zVALUE z) 
{
	const zBOOL local	= !GetInMovement();
	if (local)			BeginMovement();
	MoveWorld			(GetCollisionObject()->GetTrafoNew().Rotate(zVEC3(x,y,z)));		// move im Local-Space
//	MoveWorld			(trafoObjToWorld.Rotate(zVEC3(x,y,z)));							// move im Local-Space
//	MoveWorld			(trafo.Rotate(zVEC3(x,y,z)));									// move im Parent-Space
	if (local)			EndMovement();
};

void zCVob::SetRotationWorld (const zCQuat& quat)
{
	const zBOOL local		= !GetInMovement();
	if (local)				BeginMovement();

	quat.QuatToMatrix4							(GetCollisionObject()->GetTrafoNew());
	GetCollisionObject()->SetTrafoHintRotation	();

	if (local)				EndMovement();
};

void zCVob::RotateWorld (const zVEC3 &rotAxis, const zVALUE angle) 
{
	if (angle==0) return;
	const zBOOL local		= !GetInMovement();
	if (local)				BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
	//	// Axis ins lokale Koordinaten-System bringen
	//	RotateLocal				(GetCollisionObject()->GetTrafoNew().Inverse().Rotate (rotAxis), angle);
		trafoObjToWorld			= trafoObjToWorld * Alg_Rotation3D (rotAxis, angle);
		CorrectTrafo			();
	#endif

	const zVEC3& oldTrans						= GetCollisionObject()->GetTrafoNew().GetTranslation();
	GetCollisionObject()->GetTrafoNew			().SetTranslation(0);
	GetCollisionObject()->SetTrafoNew			(Alg_Rotation3D (rotAxis, angle) * GetCollisionObject()->GetTrafoNew());	// FIXME: optmierbar (nur der 3x3 Rot-Teil wird modifiziert...
	GetCollisionObject()->GetTrafoNew			().SetTranslation(oldTrans);
	GetCollisionObject()->SetTrafoHintRotation	();

	if (local)				EndMovement();
};

void zCVob::RotateLocal (const zVEC3 &rotAxisLocal, const zVALUE angle) 
{
	if (angle==0) return;
	zBOOL local = !GetInMovement();
	if (local)	BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafo					= trafo * Alg_Rotation3D (rotAxisLocal, angle);
		CorrectTrafoObjToWorld	();
	#endif

	GetCollisionObject()->SetTrafoNew			(GetCollisionObject()->GetTrafoNew() * Alg_Rotation3D (rotAxisLocal, angle));
	GetCollisionObject()->SetTrafoHintRotation	();

	if (local) EndMovement();
};

void zCVob::RotateLocalX (const zVALUE angle) 
{
	if (angle==0)			return;
	const zBOOL local		= !GetInMovement();
	if   (local)			BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafo.PostRotateX		(angle);
		CorrectTrafoObjToWorld	();
	#endif

//	GetCollisionObject()->SetTrafoNew			(GetCollisionObject()->GetTrafoNew() * Alg_Rotation3D (zVEC3(1,0,0), angle));
	GetCollisionObject()->GetTrafoNew			().PostRotateX(angle);
	GetCollisionObject()->SetTrafoHintRotation	();

	if (local) EndMovement	();
};

void zCVob::RotateLocalY (const zVALUE angle) 
{
	if (angle==0) return;
	const zBOOL local		= !GetInMovement();
	if   (local)			BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafo.PostRotateY		(angle);
		CorrectTrafoObjToWorld	();
	#endif

//	GetCollisionObject()->SetTrafoNew			(GetCollisionObject()->GetTrafoNew() * Alg_Rotation3D (zVEC3(0,1,0), angle));
	GetCollisionObject()->GetTrafoNew			().PostRotateY(angle);
	GetCollisionObject()->SetTrafoHintRotation	();

	if (local) EndMovement	();
};

void zCVob::RotateLocalZ (const zVALUE angle) 
{
	if (angle==0) return;
	zBOOL local = !GetInMovement();
	if   (local)   BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafo.PostRotateZ		(angle);
		CorrectTrafoObjToWorld	();
	#endif

//	GetCollisionObject()->SetTrafoNew			(GetCollisionObject()->GetTrafoNew() * Alg_Rotation3D (zVEC3(0,0,1), angle));
	GetCollisionObject()->GetTrafoNew			().PostRotateZ(angle);
	GetCollisionObject()->SetTrafoHintRotation	();

	if (local) EndMovement();
};

void zCVob::RotateWorldX (const zVALUE angle) 
{
	// FIXME: optimize
	RotateWorld (zVEC3(1,0,0), angle);
};

void zCVob::RotateWorldY (const zVALUE angle) 
{
	// FIXME: optimize
	RotateWorld (zVEC3(0,1,0), angle);
};

void zCVob::RotateWorldZ (const zVALUE angle)
{
	// FIXME: optimize
	RotateWorld (zVEC3(0,0,1), angle);
};

void zCVob::GetPositionWorld (zVALUE& x, zVALUE& y, zVALUE& z) const 
{ 
	zPOINT3 tmp;
	trafoObjToWorld.GetTranslation (tmp); 
	x = tmp.n[VX]; y = tmp.n[VY]; z = tmp.n[VZ];
};

void zCVob::GetPositionLocal (zVALUE& x, zVALUE& y, zVALUE& z) const 
{ 
	zPOINT3 tmp;
	GetTrafoLocal().GetTranslation (tmp); 
	x = tmp.n[VX]; y = tmp.n[VY]; z = tmp.n[VZ];
};

zVALUE zCVob::GetDistanceToVob (zCVob& v) 
{
	return (GetPositionWorld()-v.GetPositionWorld()).Length();
};

zVALUE zCVob::GetDistanceToVobApprox (zCVob& v) 
{
	return (GetPositionWorld()-v.GetPositionWorld()).LengthApprox();
};

zVALUE zCVob::GetDistanceToVob2 (zCVob& v) 
{	// res = squared distance
	return (GetPositionWorld()-v.GetPositionWorld()).Length2();
};

void zCVob::SetPositionLocal	(const zPOINT3& pos) 
{
	zBOOL local					= !GetInMovement();
	if (local) BeginMovement	();
								
	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafo.SetTranslation		(pos);
		CorrectTrafoObjToWorld		();
	#endif
								
	const zPOINT3&				posWorld		= GetCollisionObject()->GetTrafoNew().Inverse() * pos;
	GetCollisionObject()->GetTrafoNew			().SetTranslation (posWorld);
	GetCollisionObject()->SetTrafoHintTranslation();

	if (local) EndMovement		();
};

void zCVob::SetPositionWorld (const zPOINT3& posWorld) 
{
	zBOOL local						= !GetInMovement();
	if (local) BeginMovement		();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafoObjToWorld.SetTranslation	(posWorld);
		CorrectTrafo					();
	#endif

	GetCollisionObject()->GetTrafoNew			().SetTranslation (posWorld);
	GetCollisionObject()->SetTrafoHintTranslation();

	if (local) EndMovement			();
/*	// FIXME: ist 'n bisschen teuer das ganze mit einer MatInv zu machen, oder ??
	if ((globalVobTreeNode) && (globalVobTreeNode->GetParent()))
	{
		zCVob *parent = globalVobTreeNode->GetParent()->GetData();
		if (parent) {
			SetPositionLocal (parent->trafoObjToWorld.InverseLinTrafo() * pos);		// die WS-Pos im OS des Parents berechnen 
		} else SetPositionLocal(pos);
	} else SetPositionLocal(pos);
*/
};

void zCVob::SetTrafo (const zMATRIX4& inTrafoLocal) 
{
	#ifdef _DEBUG
		int warnMega;
		//zERR_ASSERT (inTrafoLocal.IsUpper3x3Orthonormal());
	#endif

	zBOOL local = !GetInMovement();
	if (local) BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafo				= inTrafoLocal;						// der Rest wird in EndMovement korrigiert
		CorrectTrafoObjToWorld	();
	#endif

	if (HasParentVob())
	{
		zCVob *parentVob					= globalVobTreeNode->GetParent()->GetData();
		GetCollisionObject()->SetTrafoNew	(parentVob->trafoObjToWorld * inTrafoLocal);
	} else 
	{
		GetCollisionObject()->SetTrafoNew	(inTrafoLocal);
	};
	GetCollisionObject()->SetTrafoHintTranslation();
	GetCollisionObject()->SetTrafoHintRotation	 ();

	if (local) EndMovement();
};

void zCVob::SetTrafoObjToWorld (const zMATRIX4& intrafo) 
{
	#ifdef _DEBUG
//		zERR_ASSERT (intrafo.IsUpper3x3Orthonormal());
	#endif

	zBOOL local = !GetInMovement();
	if (local) BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		trafoObjToWorld = intrafo;
		CorrectTrafo	();
	#endif

	GetCollisionObject()->SetTrafoNew			 (intrafo);
	GetCollisionObject()->SetTrafoHintTranslation();
	GetCollisionObject()->SetTrafoHintRotation	 ();

	if (local) EndMovement();
};

void zCVob::ResetRotationsLocal () 
{
	const zBOOL local = !GetInMovement();
	if (local) BeginMovement();

	if (HasParentVob())
	{
		zCVob *parentVob							= globalVobTreeNode->GetParent()->GetData();
		const zPOINT3& oldPos						= GetCollisionObject()->GetTrafoNew().GetTranslation();
		GetCollisionObject()->SetTrafoNew			(parentVob->trafoObjToWorld);
		GetCollisionObject()->GetTrafoNew			().SetTranslation (oldPos);
		GetCollisionObject()->SetTrafoHintRotation	();
	} else 
	{
		ResetRotationsWorld			();
	};

	if (local) EndMovement();
};

void zCVob::ResetXZRotationsLocal () 
{
	const zBOOL local = !GetInMovement();
	if (local) BeginMovement();

	if (HasParentVob())
	{
// FIXME: noch buggy!!
		zCVob *parentVob	= globalVobTreeNode->GetParent()->GetData();
		zMAT4 trafoLocal	= parentVob->trafoObjToWorld.Inverse() * GetCollisionObject()->GetTrafoNew();
		const zPOINT3&	at  = trafoLocal.GetAtVector();
		zPOINT3			pos	= trafoLocal.GetTranslation();
		pos [VX]			+= at [VX]*1000.0F;
		pos [VZ]			+= at [VZ]*1000.0F;
		pos					= parentVob->trafoObjToWorld * pos;		// pos nun im WS
		SetHeadingWorld		(pos);
	} else 
	{
		ResetXZRotationsWorld();
	};

	if (local) EndMovement();
};

void zCVob::ResetRotationsWorld () 
{
	const zBOOL local = !GetInMovement();
	if (local) BeginMovement();

	#ifdef MOVE_BLOCK_UPDATE_VOB_TRAFOS
		const zVEC3& currentPosWorld	= trafoObjToWorld.GetTranslation();
		trafoObjToWorld.MakeIdentity	();
		trafoObjToWorld.SetTranslation	(currentPosWorld);
		CorrectTrafo					();
	#endif

	const zPOINT3& currentPosWS			= GetCollisionObject()->GetTrafoNew().GetTranslation();
	GetCollisionObject()->GetTrafoNew().MakeIdentity	();
	GetCollisionObject()->GetTrafoNew().SetTranslation	(currentPosWS);
	GetCollisionObject()->SetTrafoHintRotation			();

/*
	// FIXME: ist 'n bisschen teuer das ganze mit einer MatInv zu machen, oder ??
	if (HasParentVob())
	{
		zCVob *parent = globalVobTreeNode->GetParent()->GetData();
		zMAT4 newTrafoObjToWorld;
		newTrafoObjToWorld.MakeIdentity		();
		newTrafoObjToWorld.SetTranslation	(GetPositionWorld());
		SetTrafo							(parent->trafoObjToWorld.Inverse() * newTrafoObjToWorld);
	} else 
	{
		ResetRotations();
	};*/

	if (local) EndMovement();
};

void zCVob::ResetXZRotationsWorld () 
{
	const zBOOL local = !GetInMovement();
	if (local) BeginMovement();

	const zPOINT3&	at  = GetCollisionObject()->GetTrafoNew().GetAtVector();
	zPOINT3			pos	= GetCollisionObject()->GetTrafoNew().GetTranslation();
	pos [VX]			+= at [VX]*1000.0F;
	pos [VZ]			+= at [VZ]*1000.0F;
	SetHeadingWorld		(pos);

	if (local) EndMovement();

/*	// FIXME: ist 'n bisschen teuer das ganze mit einer MatInv zu machen, oder ??
	if (HasParentVob())
	{
		zCVob	*parent = globalVobTreeNode->GetParent()->GetData();
		zMAT4	newTrafoObjToWorld;
		zVEC3	newAtVector	= GetAtVectorWorld();	newAtVector[VY]=0;
		if ((newAtVector[VX]==0) && (newAtVector[VZ]==0)) newAtVector[VX]=1;
		else newAtVector.Normalize();

		zVEC3	up			= zPOINT3 (0,1,0);
		up					= (up + (-(up * newAtVector) * newAtVector)).Normalize();
		zVEC3 right			= (up ^ newAtVector).Normalize();

		newTrafoObjToWorld.MakeIdentity		();						// FIXME: nur die unterste Zeile muesste inited werden..
		newTrafoObjToWorld.SetAtVector		(newAtVector);
		newTrafoObjToWorld.SetUpVector		(up);
		newTrafoObjToWorld.SetRightVector	(right);
		newTrafoObjToWorld.SetTranslation	(GetPositionWorld());
		SetTrafo							(parent->trafoObjToWorld.Inverse() * newTrafoObjToWorld);
	} else 
		ResetXZRotationsLocal();*/
};

void zCVob::SetHeadingYLocal (const zPOINT3& targetPos) 
{
// FIXME: noch ungetestet!!
	// FIXME: optimierbar !
	SetHeadingLocal			(targetPos);
	ResetXZRotationsLocal	();
};

void zCVob::SetHeadingYWorld (const zPOINT3& targetPos) 
{
	// FIXME: optimierbar !
	SetHeadingWorld			(targetPos);
	ResetXZRotationsWorld	();
};

void zCVob::SetHeadingYWorld (zCVob *targetVob) 
{
	SetHeadingYWorld		(targetVob->GetPositionWorld());
};

void zCVob::SetHeadingLocal (const zPOINT3& targetPos) 
{
// FIXME: noch ungetestet!!
	const zBOOL local = !GetInMovement();
	if (local) BeginMovement	();

	zVEC3	newAt				= (targetPos - this->GetCollisionObject()->GetTrafoNew().GetTranslation());
	zREAL	newAtLen			= newAt.Length();
	if (newAtLen<=0)			return;		// SetHeading nicht moeglich
	newAt						/= newAtLen;
	SetHeadingAtLocal			(newAt);

	if (local) EndMovement		();
};

void zCVob::SetHeadingWorld (const zPOINT3& targetPos) 
{
	const zBOOL local = !GetInMovement();
	if (local) BeginMovement	();

	zVEC3	newAt				= (targetPos - this->GetCollisionObject()->GetTrafoNew().GetTranslation());
	zREAL	newAtLen			= newAt.Length();
	if (newAtLen<=0)			return;		// SetHeading nicht moeglich
	newAt						/= newAtLen;
	SetHeadingAtWorld			(newAt);

	if (local) EndMovement		();
};

void zCVob::SetHeadingWorld (zCVob *targetVob) {
	SetHeadingWorld (targetVob->GetPositionWorld());
};

void zCVob::SetHeadingAtLocal (const zVEC3& newAtVector) 
{
	// ASSERT: 'newAtVector' must be normalized
	zBOOL local = !GetInMovement();
	if (local) BeginMovement();  

	zVEC3	up, right;
	zREAL	upLen;

	up		= zVEC3(0,1,0);					// 'default' UpVector
	up		= up - (((up * newAtVector)) * newAtVector);
	upLen	= up.Length();

	// Test, ob die Wahl des UpVectors(0,1,0) unguenstig war, d.h. up==newAtVector
	// (falls ja: alternatives up waehlen)
    // If this vector has near-zero length because the input specified a
    // bogus up vector, let's try a default up vector
    if (1e-6f>upLen)
    {
		up		= zVEC3(1,0,0) - newAtVector[VX] * newAtVector;
		upLen	= up.Length();
		
		// If we still have near-zero length, resort to a different axis.
		if (1e-6f>upLen)
		{
			up		= zVEC3(0,0,1) - newAtVector[VZ] * newAtVector;
			upLen	= up.Length();
		}
    }

	// kein SetHeading() moeglich?
	if (1e-6f<=upLen)
	{
		up		/= upLen;
		right	 = (up ^ newAtVector).Normalize();

		// Neue Trafo wird im OS des Vobs konstruiert..
		zMAT4 tmpTrafoLocal				= Alg_Identity3D();
		tmpTrafoLocal.SetAtVector		(newAtVector);
		tmpTrafoLocal.SetUpVector		(up);
		tmpTrafoLocal.SetRightVector	(right);

		// .. und hier schliesslich in den WS transformiert und gesetzt!
		const zPOINT3& oldPosWorld							= GetCollisionObject()->GetTrafoNew().GetTranslation();
		GetCollisionObject()->GetTrafoNew().SetTranslation	(0);
		if (HasParentVob())
		{
			zCVob *parentVob								= globalVobTreeNode->GetParent()->GetData();
			GetCollisionObject()->SetTrafoNew				(parentVob->trafoObjToWorld * tmpTrafoLocal);
		} else 
		{
			GetCollisionObject()->SetTrafoNew				(tmpTrafoLocal);
		};
		GetCollisionObject()->GetTrafoNew().SetTranslation	(oldPosWorld);

	};
	if (local) EndMovement();
};

void zCVob::SetHeadingAtWorld (const zVEC3& newAtVector) 
{
	// ASSERT: 'newAtVector' must be normalized
	zBOOL local = !GetInMovement();
	if (local) BeginMovement();  

	zVEC3	up, right;
	zREAL	upLen;

	up		= zVEC3(0,1,0);					// 'default' UpVector
	up		= up - (((up * newAtVector)) * newAtVector);
	upLen	= up.Length();

	// Test, ob die Wahl des UpVectors(0,1,0) unguenstig war, d.h. up==newAtVector
	// (falls ja: alternatives up waehlen)
    // If this vector has near-zero length because the input specified a
    // bogus up vector, let's try a default up vector
    if (1e-6f>upLen)
    {
		up		= zVEC3(1,0,0) - newAtVector[VX] * newAtVector;
		upLen	= up.Length();
		
		// If we still have near-zero length, resort to a different axis.
		if (1e-6f>upLen)
		{
			up		= zVEC3(0,0,1) - newAtVector[VZ] * newAtVector;
			upLen	= up.Length();
		}
    }

	// kein SetHeading() moeglich?
	if (1e-6f<=upLen)
	{
		up		/= upLen;
		right	 = (up ^ newAtVector).Normalize();

		// Neue Trafo direkt im WS setzen
		GetCollisionObject()->GetTrafoNew().SetAtVector		(newAtVector);
		GetCollisionObject()->GetTrafoNew().SetUpVector		(up);
		GetCollisionObject()->GetTrafoNew().SetRightVector	(right);
		GetCollisionObject()->SetTrafoHintRotation			();

	};
	if (local) EndMovement();
};

/*
	>The bottom row of your matrix represents the z-axis of the coordinate
	>space.  We shall assume that this is right.  The middle row represents
	>the UP direction (or y-axis).
	>
	>To find how much of the middle row vector (V) lies along the bottom
	>row vector (N):
	up		= y = V = middle
	at		= z = N = bottom
	right	= x     = top
	t		= up * at;
	up		= up - (t  * at);
	right	= up x at;
	In here don't forget to make sure V and N are of unit length.
	>t = V dot N            (maginitude of V along N)
	>T = t * N              (the part vector of V along N)
	>Therefore if we subtract this from V, no part of it will not lie at 90
	>degrees to N:
	>V = V - T
	>To get the x -axis (top row of the matrix), just do a cross-product of
	>V and N.
	>You now have an orthogonalised matrix.
	>This technique can also be used to create a camera orientation from a
	>look point and arbitrary up point.
*/

// ==================================================================================================================

void zCCFASTCALL zCVob::SetCollDetStat (const zBOOL b) 
{ 
	// Falls ein Vob ohne cdFlags in den MovementBlock gelang, und innnerhalb dieses Blocks die cd eingeschaltet wird,
	// so liegt ein Fehler vor!
	if ((b) && (GetInMovementMode()==zVOB_MOVE_MODE_INBLOCK_NOCD))
	{
		zERR_FAULT ("D: zVob(zCVob::SetCollDetStat): cannot modify collision-flags while in movement-phase");
	};
	collDetectionStatic = b; 
};

void zCCFASTCALL zCVob::SetCollDetDyn (const zBOOL b)  
{
	// Falls ein Vob ohne cdFlags in den MovementBlock gelang, und innnerhalb dieses Blocks die cd eingeschaltet wird,
	// so liegt ein Fehler vor!
	if ((b) && (GetInMovementMode()==zVOB_MOVE_MODE_INBLOCK_NOCD))
	{
		zERR_FAULT ("D: zVob(zCVob::SetCollDetDyn): cannot modify collision-flags while in movement-phase");
	};
	collDetectionDynamic= b; 
};

// ==================================================================================================================

/*void zCVob::CorrectTrafoObjToWorld () 
{
	// correct 'trafoObjToWorld' if 'trafo' has changed 
	// and 'trafoObjToWorld' is dirty
	if (HasParentVob())
	{
		zCVob *parentVob= globalVobTreeNode->GetParent()->GetData();
		trafoObjToWorld	= parentVob->trafoObjToWorld * trafo;				// konkateniere Matrizen
	} else
		trafoObjToWorld = trafo;
};*/

void zCVob::CorrectTrafo () 
{
    if (!trafo)
        return;

	// correct 'trafo' if 'trafoObjToWorld' has changed 
	// and 'trafo' is dirty
	if (HasParentVob())
	{
		zCVob *parentVob= globalVobTreeNode->GetParent()->GetData();
		*trafo			= parentVob->trafoObjToWorld.InverseLinTrafo() * trafoObjToWorld;
	} else
		*trafo			= trafoObjToWorld;
};

// destroy the local matrix again if the vob has no parent after transfering the position change into trafoObjToWorld
void zCVob::DoneWithTrafoLocal(){
    if (!trafo || HasParentVob())
        return;

    trafoObjToWorld = *trafo;
    delete             trafo;
    trafo           = NULL;
}

// allocates the local transformation matrix
void zCVob::CreateTrafoLocal () const{
    if (!trafo)
        (zMAT4 *&)trafo = zNEW(zMAT4);
    
    zERR_ASSERT(trafo);

    ((zCVob *)this)->CorrectTrafo();
}


// ==================================================================================================================

void zCVob::SetPhysicsEnabled (const zBOOL enable) 
{
	if (GetStaticVob()) return;
	physicsEnabled = enable; 
//	if (!enable) 
	if (rigidBody) rigidBody->StopTransRot(); 
};

zVEC3 zCVob::GetVelocity () 
{
	// FIXME: im Visual den Wert pro Frame cachen (billiger)
	// FIXME: auch ein schnelleres GetVelocityLength() bereitstellen !

	// Achtung: etwas unsauber ist es, dass zCVob::GetVelocity() im Fall 
	//			Physik: WorldSpace, ModelAni: localSpace zurueckliefert..

	zVEC3 vel;
	if (GetPhysicsEnabled()) {
		vel = GetRigidBody()->GetVelocity();
//		vel = vel * 1000;
	} else
	if (GetVisualClass()==zCModel::GetStaticClassDef())
	{
		// v	= s/t
		// [vel]= cm/ms
//		vel = ((zCModel*)GetVisual())->GetLastPosDelta();
		vel = ((zCModel*)GetVisual())->GetVelocityRing();
		vel = trafoObjToWorld.Rotate(vel);					// trafo: objectSpace => worldSpace
	} else
		vel = 0;
	return vel;
};


// ==================================================================================================================

void zCVob::UpdatePhysics()
{
	if (GetPhysicsEnabled())
	if (rigidBody) 
	{
		if (GetRigidBody()->GetMode()==zPHY_RBMODE_SLIDE)	db_Line3D (GetPositionWorld(), GetPositionWorld()+GetRigidBody()->GetVelocity(), GFX_ORANGE);
		else												db_Line3D (GetPositionWorld(), GetPositionWorld()+GetRigidBody()->GetVelocity(), GFX_YELLOW);

		// FIXME: muss auf trafoObjToWorld arbeiten !!
		// FIXME: UGLY

//		rigidBody->RDir	= trafoObjToWorld * Alg_Identity2D();		// angularEffects disabled
//		rigidBody->SetPositionCM	(GetPositionWorld());
		rigidBody->SetPositionCM	(GetCollisionObject()->GetTrafoNew().GetTranslation());

		rigidBody->RunSimulation	();

//		zMATRIX4 tmpMat;											// angularEffects disabled
//		tmpMat = rigidBody->RDir; 
//		SetTrafoObjToWorld		(tmpMat);
		SetPositionWorld		(rigidBody->GetPositionCM());  

		// RigidBody Mode-Wechsel ?
		// Sliding
if (GetCollisionClass()!=zCCollObjectCharacter::S_GetCollObjClass())	// model-sliding wird von der AI kontrolliert.. ARGH!
		if (GetRigidBody()->GetMode()==zPHY_RBMODE_SLIDE) 
		{
			// Sliding beenden ?

			// a) wieder ins Fallen übergehen ?
			//    hierzu 4 Rays der OBB nach unten casten
			// wie auswerten ?? (=> sehr steiler Hang..)

			// FIXME: 'FirstHit' statt 'NearestHit' verwenden !!!!

			const zVALUE	Y_CAST		= bbox3D.GetCenter()[VY];
			const zVALUE	Y_DELTA		= 15+(Y_CAST-bbox3D.mins[VY]);

			zPOINT3 rayOrg;
			rayOrg	= zPOINT3(bbox3D.mins[VX], Y_CAST, bbox3D.mins[VZ]);
			if (GetHomeWorld()->TraceRayNearestHit (rayOrg, zVEC3(0,-100000,0), this, 0)) {
				db_Line3D (GetHomeWorld()->traceRayReport.foundIntersection, GetHomeWorld()->traceRayReport.foundIntersection+zVEC3(0,15,0), GFX_RED);
				if (zAbs(GetHomeWorld()->traceRayReport.foundIntersection[VY] -rayOrg[VY])<Y_DELTA) goto onGround;
			};
			rayOrg	= zPOINT3(bbox3D.mins[VX], Y_CAST, bbox3D.maxs[VZ]);
			if (GetHomeWorld()->TraceRayNearestHit (rayOrg, zVEC3(0,-100000,0), this, 0)) {
				db_Line3D (GetHomeWorld()->traceRayReport.foundIntersection, GetHomeWorld()->traceRayReport.foundIntersection+zVEC3(0,15,0), GFX_RED);
				if (zAbs(GetHomeWorld()->traceRayReport.foundIntersection[VY] -rayOrg[VY])<Y_DELTA) goto onGround;
			};
			rayOrg	= zPOINT3(bbox3D.maxs[VX], Y_CAST, bbox3D.mins[VZ]);
			if (GetHomeWorld()->TraceRayNearestHit (rayOrg, zVEC3(0,-100000,0), this, 0)) {
				db_Line3D (GetHomeWorld()->traceRayReport.foundIntersection, GetHomeWorld()->traceRayReport.foundIntersection+zVEC3(0,15,0), GFX_RED);
				if (zAbs(GetHomeWorld()->traceRayReport.foundIntersection[VY] -rayOrg[VY])<Y_DELTA) goto onGround;
			};
			rayOrg	= zPOINT3(bbox3D.maxs[VX], Y_CAST, bbox3D.maxs[VZ]); 
			if (GetHomeWorld()->TraceRayNearestHit (rayOrg, zVEC3(0,-100000,0), this, 0)) { 
				db_Line3D (GetHomeWorld()->traceRayReport.foundIntersection, GetHomeWorld()->traceRayReport.foundIntersection+zVEC3(0,15,0), GFX_RED);
				if (zAbs(GetHomeWorld()->traceRayReport.foundIntersection[VY] -rayOrg[VY])<Y_DELTA) goto onGround;
			};
//				zerr.Message ("flying again...");
			GetRigidBody()->SetMode (zPHY_RBMODE_FLY);
			goto leave;
onGround:;
			// b) zum Stillstand gekommen auf relativ ebenen Grund ?
			if ((GetRigidBody()->GetSlideAngle()<=30) &&
				// FIXME: TIME_CORRECT
				(GetRigidBody()->GetVelocity().Length2()<(50*50))) {
				SetPhysicsEnabled	(FALSE);
				// FIXME: Nur wenn keine AI aktiv ??
				db_Print ("going to sleep.. slideVelo");
				if (callback_ai)	SetSleepingMode		(zVOB_AWAKE_DOAI_ONLY);
				else				SetSleeping			(TRUE);
			};
			goto leave;
leave:; 
		};
	};
};

// ==================================================================================================================

/*

Sweep-Tests von Sphere,AABB,OBB,..:
http://gamasutra.com/features/19991018/Gomez_1.htm


  Collision-Detection-Strategie:

    - Wie es eigentlich '100%' korrekt sein sollte:
	  Alle Vobs bewegen sich gleichzeitig von t=0 auf t=1. Falls Kollisionen auftraten, wird bis zum Zeitpunkt tc
	  der fruehesten Kollision zurueckgegangen. D.h. die gesamte Physik-Simulation fuer _alle_ Vobs wird auf den
	  Zustand des Zeitpunktes tc gesetzt. Dann werden die C.R.s fuer alle beteiligten, kollidierenden Vobs errechnet
	  (=> Impulse). Dann schreitet die Zeit und die Physik-Simulation von tc weiter in Richtung t=1. 
	  Dieser ganze Vorgang wiederholt sich solange bis nach&nach alle Kollisionen im Intervall 0..1 aufgeloest sind und
	  die Simulation t=1 erreicht hat.

+++
	- Grund-Annahme:
	  Nachdem & bevor alle Vobs ihre Bewegungen abgeschlossen haben, ist die gesamte Welt _kollisionsfrei_.
	- Es wird immer nur ein Vob zur Zeit bewegt. Dabei wird angenommen, dass alle uebrigen Vobs fuer diesen
	  Augenblick stillstehen.
	- Falls eine Kollision bei t=1 auftritt wird der exakte Kollisionspunkt tc im Zeitintervall 0..1 durch
	  binaere Suche ermittelt. Zur Vereinfachung wird hier _nur_ die Translation des Vobs, nicht aber dessen
	  Rotation im Intervall 0..1 interpoliert (=> Rot waere auch moeglich(Quats), allerdings gibt so keine/weniger
	  Probs mit Eberlys OBB-Code).
	  Der Zeitpunkt tc ist Kollisionsfrei, sollte aber moeglichst nahe an dem realen Zeitpunkt des 'Kontaktes' sein.
	  Die Objekte mit den der Vob zum letzten Zeitpunkt _vor_ tc kollidiert ist, sind die Objekte mit denen zum
	  Zeitpunkt tc die C.R. durchgefuehrt wird (Liste von Vobs, Liste von static-Polys).

	  Im Zustand tc werden die Closest features ermittelt und aus diesen dann die C.R. fuer _alle_ beteiligten
	  Objekte errechnet.
	- Es werden leider n^2 Checks auf allen Vobs eines BSP-Volumens gemacht.

	- Zunaechst wird ein SpeedBBox3D Check gemacht. Ist dieser Collision-frei, dann early exit.
	- Falls nicht, hat mann nun eine maximale Menge statische Polys und dyn. Vobs, mit denen ueberhaupt im Zeitraum
	  t=0..1 ein Collision stattgefunden haben kann. Der Zeitraum wird nun linear von t=0 bis t=1 durchgegangen, mit 
	  einem gewissen Objekt-abhängigem dt. dt muss so gewaehlt werden, dass in Folge des Durchschreitens des gesamten
	  Intervalls kein Punkt auf der Bewegungs-Geraden des Objektes 'unbedeckt' geblieben ist.
	  Pro diskretem Zeitpunkt wird nun ein Check mit der Speedbox-Menge gegen den OBB-Tree des Objekts gemacht. Falls 
	  eine Collision festgestellt wurde, wird zum vorherigen t backupt, dt wird halbiert und die Suche fortgesetzt, 
	  solange bis dt<epsilon ist.

	- SPEEDBOX: nur im SpeedBox3D Volume sammeln
	  EXACT   : bestehende Listen gegen exakteres Volume testen (=>OBB)
	  ALL	  : SpeedBox (=BBox) Test + exact-Test

	- SleepMode/Physik/AI/..
		- 

	- Probleme
		- Die einzelnen OBB des Meshes koennen zur Zeit noch aus der Speedbox hervorragen. Das kann Probleme bereiten.
		  Z.B: Speedbox meldet irrtuemlich eine CD, aber: eine Collision der einzelnen BBoxen zu jedem Zeitpunkt haette
		  keine Coll. ergeben. Ein OBB des Meshes ragt allerdings bereits bei t=0 in ein Poly hinein:
		  => laut bbox keine 'loesbare' collision (am Hang..), laut obb eine 'illegale' collision
		  (=> bbox wird nun aus obb gewonnen..)

		- Bei statische Impulse-Collision gibt es oft den Effekt, dass trotz dem angewandten Impuls das Objekt sich 
		  nicht _vollstaendig_ vom Hindernis wegbewegt. Oder: beim Aufprallen auf den Boden zeigt zwar die veloc nach
		  dem Impuls minimal vom Boden weg, wird aber sofort danach von der Gravity wieder Richtung Hinderniss gezerrt...
		- EVIL: Nach der Response (bzw. dem Reset davor) gibt es noch COLLISION STATES.
		- Sliding: Falls ein Objekt auf eine Kante geworfen wird und ins Sliden geganngen wird, haengt dieses. Problem:
		  der berechnete Slide-Weg fuehrt durch das Hindernis hindurch..

		- CD Vob/Vob:
			- Vobs bleiben in der Luft haengen 
			  (=> oft, falls 1 Vob 'eingeklemmt' ist. Impulse scheint nicht wie noetig zu wirken...warum ???)
			- Vob slided auf Vob
			- Vobs, die auf anderen Vobs einschlafen, muessen deren Childs werden. Beim aufwecken: wieder loesen.
			- Models/Meshes: Models bleiben haengen !!!!!!

		* illegale Collision States nach Response
		x Intervall-Suche mit Rotationen !!
		x Intervall-Suche mit adaptiver Schrittweite !!
		- Vobs, die auf Kanten geworfen werden (blocked slideDir)
		- Model/Level: CD-Konzept (Spheres..)

    - Collision: Vob <=> Level
		- 1) Polys aus dem BSP-Tree ziehen, die die Speedbox ueberlagern = SET, keine? => fertig
		     Falls es nun Polys in der Speedbox gibt, muss auf jeden Fall eine binaere Suche auf t gemacht werden,
			 auch wenn weitere Checks auf der BBox oder dem OBB-Tree zur Zeit t=1 keine Collision ergeben.
		- 2) Polys ermitteln, die die BBox ueberlagern		(BBox/Poly-Check)		=> SET verkleinern.
		- 3) Polys ermitteln, die den OBB-Tree uerberlagern (OBB-Tree/Poly-Check)	=> SET verkleinern.
		- 4) => SET enthaehlt nun alle Polys mit denen das Vob zur akt. Zeit kollidiert.
		
    - Collision: Model <=> Waffe (eines Models)
		- 

	- Collision: VOB  <=> VOB
		- Collision: Mesh  <=> Mesh
	    - Collision: Mesh  <=> Model
			- BVolumes:
				- Mesh (speedbox, bbox, obb)
				- Model:
					- falls Mesh statisch : dasselbe volume wie beim model/level test, bis kniehoehe reduziert
					- falls Mesh dynamisch: bbox3dLocalFixed
			- 
	    - Collision: Model <=> Model 


	- Vob-Zustaende
		- slide:
			- 

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  - DoAI()
	- BeginMovement
	- Physik
	- Model-Movement
	- AI-Callback
	- EndMovement

  - EndMovement
	- if (model) DoStaticModelCollision()
	- loop:
		- DetectCollisionDyn()
AI			- AI->CanThisCollideWith()
		- DetectCollisionStat()
AI		- AI->HasAIDetectedCollision()						// flag, Boden/Decke-Rays

		- if (collision)
			- CollisionResponse()
				- if (static)
// AI					- AI->AICollisionResponse()				// wallEdgePopping, wallSlide, emergency
AI					- AI->ReportCollisionToAI()
				- if (dyn)
AI						- AI->ReportCollisionToAI()
AI			- AI->AICollisionResponseSelfDetected()

	- AI-Callback:
		- Begin()
			- berechnet/cacht/resettet: 
				vobVelocity, centerPos=vobPosWorld, headY, feetY, waterLevel/oldWaterLevel, state/oldState, aiDetectedCollision
			- ruft auf: 
				CalcModelAnisInPlace	();
				DoAutoRoll				();

		- FindFloorCeiling()
			- castet Rays nach oben/unten (start= old vobWorldPos, damit garantiert IM Level)
			- berechnet/cacht:
				floorY, floorPoly, ceilingY, ceilingPoly, lastFloorY, floorIsStair, waterY, waterPoly, waterDepth, 
				aboveFloor
				newCenter (auf Grundlage von centerPos)
				forceModelHalt, aiDetectedCollision, interferenceReport
				Gravity unterwasser daempfen
				Stroemungs-Bewegung

		- CorrectFloorHeight()
			- wenn nicht im Flug
				- wenn mehr als StepHeight ueber Boden und keine Treppe (+ WasserCheck)
					- fallen lassen (Ani+Physik)
				- sonst:
					- auf Sliding testen
					- HoehenKorrektur: SetWorldPos(newCenter)

		- if (CollisionHandling()) goto leave;
			- reagiert nur bei Flags: collisionOccured, selfDetectedCollision
			- zMV_STATE_SWIM, zMV_STATE_DIVE 
				- => exit
			- zMV_STATE_FLY
				- Test auf Kante greifen
				- Test auf Starten der OOOops Ani
				- CheckFloorSliding()
			- zMV_STATE_STAND
				- CheckFloorSliding()
				- Test auf Starten der OOOops Ani
				- ggfs. forceModelHalt

		- BeginStateSwitch()
			- if (DetectWalkStopChasm()) forceModelHalt = TRUE; 
			- im Flug fallDownStartY setzen
			- (vob->GetPhysicsEnabled()) oder (model->GetIsFlying())	=>	state = zMV_STATE_FLY;


		.. StateSwitch ..

			- aktuelle Animationen (= Zustaende) abfragen
			- neue Animationen starten (Transitionen einleiten)
			- interne Zustandsvariablen benutzen (z.B. floorY, waterY, waterLevel, oldState, aboveFloor,..)
			- Model bewegen (z.B. Kante greifen), ResetRotations(), AlignModelToLedge()
			- CheckEnoughSpaceXX(), CheckForceModelHalt()
			- Physik ein/aus
			- CollDet ein/aus
			- Umgebung/Level auswerten

		- prozedurale Bewegung (Moves/Rots..())


		- End()
			- forceModelHalt = FALSE;
			- CollisionDetectionAndResponse();
			- UpdateEffects();

		- CollisionDetectionAndResponse();
			- CollDet, CollResp, wallSide, wallEdgePopping, Fallen auf Kante, nicht durchLevelFallen, 
			- Surface-Align

============================

	* Variablen: Zeitpunkte der Gueltigkeit
		* direkt am Anfang der AIPlayer koennte die GetWorldPos bereits ausserhalb des Levels sein..
	* Rays minimieren
	* welche Features/Eigenschaften muss das gesamte Teil haben?

*/

// ==================================================================================================================

zBOOL zCVob::DetectCollision (zMATRIX4 *trafoObjToWorldNew) 
{
	zBOOL							physicsEnabled;
	zTVobSleepingMode				sleepMode;
	if (trafoObjToWorldNew) 
	{
		physicsEnabled				= GetPhysicsEnabled	();
		sleepMode					= GetSleepingMode	();
		SetPhysicsEnabled			(TRUE);
		SetSleepingMode				(zVOB_AWAKE);
	};								
									
	// Test ausfuehren
	this->BeginMovement				();							// Begin/EndMove benutzen, damit hier ein korrekter CollObject Kontext vorliegt
	if (trafoObjToWorldNew)										// Bei einem dyn. Test das Ziel setzen
		this->SetTrafoObjToWorld	(*trafoObjToWorldNew);
	zBOOL isColliding				= this->IsColliding();
	if (trafoObjToWorldNew)										// Bei einem dyn. Test das Ziel setzen
		this->ResetToOldMovementState();						// alles wieder zuruecknehmen, war ja nur ein Test!
	this->EndMovement				();							// sollte ein no-op sein
									
	//								
	if (trafoObjToWorldNew)			
	{								
		SetPhysicsEnabled			(physicsEnabled);
		SetSleepingMode				(sleepMode);
	};								
									
	return isColliding;
};

// ==================================================================================================================

void zCCFASTCALL zCVob::SetInMovement (zBOOL b) 
{
	SetInMovementMode ( b ? zVOB_MOVE_MODE_INBLOCK : zVOB_MOVE_MODE_NOTINBLOCK);
};

void zCCFASTCALL zCVob::SetInMovementMode (zTMovementMode moveMode) 
{ 
	if ((isInMovementMode	==zVOB_MOVE_MODE_INBLOCK_NOCD) || 
		(moveMode			==zVOB_MOVE_MODE_INBLOCK_NOCD)) 
	{
		// dieser Mode beeinflusst 's_vobAlreadyInMovement' nicht
		isInMovementMode		= moveMode;
	} else 
	{
		isInMovementMode		= moveMode;
		s_vobAlreadyInMovement	= (moveMode==zVOB_MOVE_MODE_INBLOCK); 
	};
};

// ==================================================================================================================

void zCVob::BeginMovement () 
{
	if (GetInMovement()) return;

	// Befindet sich dieser Vob gerade bei der Aufloesung der Transaktion, in der EndMovement() Methode?
	// Ein Notification Callback koennte fehlerhafterweise erneut BeginMovement() aufrufen. Das wird hier abgefangen.
	if (GetInsideEndMovementMethod())
	{
		#ifdef _DEBUG
			zERR_FAULT	("D: VOB: illegal call of vob::BeginMovement() from a collision notification callback");
		#else
			zERR_WARNING("D: VOB: illegal call of vob::BeginMovement() from a collision notification callback");
		#endif
		return;
	};

	// CollisionObject erzeugen (akkumuliert im Block die Pos/Rot Veraenderungen)
	this->CreateCollisionObject			();
	this->ResetCollisionObjectState		();

	//
	this->SetMovementHintTrafoLocalConst(FALSE);
	
	#if 1
		// Beliebig viele Vobs gleichzeitig in Bewegung
		SetInMovement		(TRUE);
	#else
		// Nur 1 Vob gleichzeitig in Bewegung
		// ACHTUNG: koennte Probs machen, wenn CollTests NICHT reflexiv sind! (weils dann naemlich davon abhaengt,
		//          in welcher Reihenfolge sich Objekte bewegen)
		// Regel:
		// Es darf sich nur 1 Vob zu Zeit im Movement-Block befinden, der eingeschaltete Coll-Flags
		// hat. Nur Vobs, die KEINE Coll-Flags gesetzt haben, duerfen auch zeitgleich bewegt werden.
		const zBOOL doDetection = (GetCollDetStat() || GetCollDetDyn());
		if ((s_vobAlreadyInMovement) && (doDetection))
		{
			zERR_FAULT ("D: zVob(zCVob::BeginMovement): only one moving vob without cd allowed at a time, vobName: "+GetVobName());
			return;
		};
		if (!doDetection) 
		{
			SetInMovementMode	(zVOB_MOVE_MODE_INBLOCK_NOCD);
		} else
		{
			SetInMovement		(TRUE);
		};
	#endif
};	

void zCVob::ResetToOldMovementState () 
{
	if (GetInMovement()) 
	{
		this->SetNewTrafoObjToWorld					(this->GetOldTrafoObjToWorld());
		this->GetCollisionObject()->ResetTrafoHints	();
	};
};

void zCCFASTCALL zCVob::UpdateTouchList(const zCArray<zCVob*> &newTouchVobList) 
{
	// OnTouch, OnUntouch: EMs benachrichtigen
	// newTouchVobList ist die Liste der Vobs, die diesen Frame beruehrt werden.
	// Vobs benachrichtigen, die sich beruehrten, aber ohne Collision-Response: zVOB_COLL_TYPE_NO_COLLRESP
	// FIXME: Performance Optimierung: die temp. Listen onTouchVobList und onUntouchVobList erzeugen jedesmal heap-Objekte..

	if ((touchVobList.GetNum()!=0) || (newTouchVobList.GetNum()!=0))			// optimized
	{
		// 'touch' Messages
		zCArray<zCVob*> onTouchVobList;	
		for (int i=0; i<newTouchVobList.GetNum(); i++) 
		{
			zCVob* vob	= newTouchVobList[i];
			int index	= touchVobList.Search (vob);
			if (index!=-1) 
				touchVobList.RemoveIndex (index);
			else {
				// Vob wird in diesem Frame zum ersten mal beruehrt
				//				    GetEM()->OnTouch			(vob);
				//			   vob->GetEM()->OnTouch			(this); 
				//			   if (!vob->touchVobList.IsInList	(this))	// FIXME: WORKAROUND
				zERR_ASSERTT (!vob->touchVobList.IsInList(this), "D: bereits in Liste!");
				vob->touchVobList.Insert	(this);				// touchVobList von "other" updaten (insert)
				onTouchVobList.Insert		(vob);
			};
		};

		// 'untouch' Messages
		// Vobs, die jetzt noch in der touchVobList sind, werden im neuen Frame nicht mehr beruehrt
		zCArray<zCVob*> onUntouchVobList	= touchVobList;
		for (i=0; i<touchVobList.GetNum(); i++) 
		{
			zCVob* vob = touchVobList[i];
			zERR_ASSERTT (vob->touchVobList.IsInList(this), "D: gar nicht in Liste!");
//				 GetEM()->OnUntouch		(vob);
//			vob->GetEM()->OnUntouch		(this);
			vob->touchVobList.Remove	(this);					// touchVobList von "other" updaten (remove)
		};
		touchVobList = newTouchVobList;							// touchVobList von "this" updaten (insert/remove)
		
		// Jetzt sind die TouchListen sowohl im this-vob als auch in allen other-Vobs aktuallisiert und das 
		// Benachrichtigen der betroffenen Vobs darf ausgefuehrt werden.
		for (i=0; i<onTouchVobList.GetNum(); i++)
		{
			zCVob* vob	= onTouchVobList[i];
			GetEM()->OnTouch			(vob);
			vob->GetEM()->OnTouch		(this); 
		};
		for (i=0; i<onUntouchVobList.GetNum(); i++)
		{
			zCVob* vob	= onUntouchVobList[i];
			GetEM()->OnUntouch			(vob);
			vob->GetEM()->OnUntouch		(this); 
		};
	};
};

void zCCFASTCALL zCVob::CalcDestinationBBox3DWorld (zTBBox3D &resultBBox3D) 
{
	/*

	BBox-Handling:
	Bei Vobs mit Visual diktiert das Visual die BBox des Vobs. Das Visual liefert je nach Typ entweder eine
	BBox im WS oder im OS, wobei im Vob die zweite abhaengige BBox errechnet wird.
	Bei Vobs ohne Visual ist die World-BBox die dominierende und die ObjSpace-BBox ist die abhaengige. Bei solchen
	Vobs macht eine OS-BBox auch keinen Sinn, da sich in dessen OS gar nichts befindet.. Ausserdem ist es nur so
	im Spacer vernuenftig moeglich, die BBox zu editieren, naemlich im World-Space.
	Achtung: Trafos von BBoxen (z.B. WS<=>OS) sind i.A. LOSSY!! D.h.: Eine Trafo Kette einer BBox WS=>OS=>WS
	liefert am Ende nicht wieder die Eingabe BBox.
	*/ 

	zERR_ASSERT ((&resultBBox3D) != (&bbox3D));
	// bbox3d nach worldSpace transformieren
	if (GetVisual()) 
	{
		// FIXME: das macht so eigentlich nur Sinn, wenn die BBox im OS ist...
		if (visual->IsBBox3DLocal())
		{
			GetVisual()->GetBBox3D().Transform (GetCollisionObject()->GetTrafoNew(), resultBBox3D);
		}
		else							
		{ 
			// FIXME: todo.txt, @1
			// Ein Vob hat zu jedem Zeitpunkt eine gueltige BBoxWS und BBoxOS...
			// Bei Bewegungen koennen diese leicht ueber die Trafos geupdated werden.
			// Wenn allerdings das Visual seine BBox aendert muss das Vob auch seine Eintraege updaten...
			const zVEC3	distWS		= GetCollisionObject()->GetTrafoNew().GetTranslation() - GetCollisionObject()->GetTrafoOld().GetTranslation();
			resultBBox3D			= bbox3D;
			resultBBox3D.Translate	(distWS);
		};
	} else 
	{
		// auch Vobs ohne Visual brauchen eine korrekte WorldSpace BBox3D
		const zVEC3	distWS			= GetCollisionObject()->GetTrafoNew().GetTranslation() - GetCollisionObject()->GetTrafoOld().GetTranslation();
		resultBBox3D				= bbox3D;
		resultBBox3D.Translate		(distWS);
	};
};

void zCVob::AdoptCollObjResults () 
{
	zERR_ASSERT (GetInMovement());

	if (GetCollisionObject()->HasMoved())
	{
		trafoObjToWorld				= GetCollisionObject()->GetTrafoNew();
		// trafoLocal nur updaten, falls nicht der entsprechende Hint sagt, dass sie konstant ist (subTree Update)
		if (!this->GetMovementHintTrafoLocalConst())
		{
			this->CorrectTrafo		();
		};
	};
	this->DestroyCollisionObject	();
};


void zCVob::EndMovement(const zBOOL a_bHintTrafoChanged) 
{
	// Beendet eine Bewegungs Transaktion. Prueft ggfs. auf Kollisionen und haelt abhaengige Variablen
	// und Objekte konsistent.
	// (berechnet rekursiv im globalVobTree: trafoObjToWorld, bbox3d (WS), collision Detection)
	// In dieser Methode ist nur EIN EINZIGES return am Ende der Methode erlaubt.


	/*	ALT, behoben:
		(F_ME: hier gibt es noch einen Bug mit der zCModel::UpdateBBox3DTree(), dieser wird naemlich das erste mal
	     *nach* der Physik berechnet; nachfolgende Resets aufgrund von Collisions setzen dann auf diesen, zurueck..)*/

	if (GetInMovementMode()==zVOB_MOVE_MODE_NOTINBLOCK) return;

	// Befindet sich dieser Vob gerade bei der Aufloesung der Transaktion, in der EndMovement() Methode?
	// Ein Notification Callback koennte fehlerhafterweise erneut EndMovement() aufrufen. Das wird hier abgefangen.
	if (GetInsideEndMovementMethod())
	{
		#ifdef _DEBUG
			zERR_FAULT	("D: VOB: illegal call of vob::EndMovement() from a collision notification callback");
		#else
			zERR_WARNING("D: VOB: illegal call of vob::EndMovement() from a collision notification callback");
		#endif
		return;
	};

	// re-enter guard setzen
	SetInsideEndMovementMethod (TRUE);

	// nicht in der Welt registriert ? 
	if (!GetHomeWorld()) 
	{
		// bbox3d nach worldSpace transformieren
		{
			zTBBox3D newBBox3D;
			CalcDestinationBBox3DWorld	(newBBox3D);
			this->bbox3D				= newBBox3D;
		};

		//
		AdoptCollObjResults();

		// Die Moving-Phase ist hiermit beendet
		SetInMovement (FALSE);

		// recursive traversal, childs anpassen falls es sich um einen ausser-weltlichen mini VobSubtree handelt (Fackel etc..)
		// (subtree trafoObjToWorld und bboxWS muessten angepasst werden.. (reku.))
		if (globalVobTreeNode)
		{
			zCTree<zCVob> *child = globalVobTreeNode->GetFirstChild(); 
			while (child) 
			{
				zCVob *vob = child->GetData			();
				vob->BeginMovement					();
				vob->SetMovementHintTrafoLocalConst	(TRUE);
				vob->SetTrafoObjToWorld				(this->trafoObjToWorld * vob->GetTrafoLocal());	
				vob->EndMovement					(a_bHintTrafoChanged);
				child = child->GetNextChild			();
			};
		};
	} else 
	if (!GetCollisionObject()->HasMoved()) 
	{
		// Keine Bewegung stattgefunden ?
		// FIXME: hier kann aber trotzdem eine Veränderung der BBox passiert sein (=> PFX)
		AdoptCollObjResults();

		// Die Moving-Phase ist hiermit beendet
		SetInMovement (FALSE); 
	} else 
	{
		#ifdef zDEBUG_COLLECT_STATS	
			zengineStats.numVob_EndMovement++;
		#endif

		// den neuen, sich im CollObj befindlichen Zustand testen & ggfs. durch Responses in einen gueltigen Zustand bringen
		
		CheckAndResolveCollisions();

		// bbox3d nach worldSpace transformieren
		// FIXME: Perf! falls keine Kollision vorlag, wurde diese Bereits zum Bauen der SpeedBox verwendet und kann reused werden
		{
			zTBBox3D newBBox3D;
			CalcDestinationBBox3DWorld	(newBBox3D);
			this->bbox3D				= newBBox3D;
		};

		// den nun getesten Zustand im CollObject in den Vob uebernehmen
		AdoptCollObjResults();

		// Die Moving-Phase ist hiermit beendet
		SetInMovement (FALSE); 

		// AdjustVob
		// Zone ?
		if (GetHomeWorld()->ShouldAddThisVobToBsp(this))
			GetHomeWorld()->GetBspTree()->AdjustVob (this);

		// recursive traversal
		// FIXME/ACHTUNG: Dies ist 'brute-force'/ineffizient, falls Vobs der Hierarchie ausserdem noch
		// bewegt werden, werden evtl. Trafos einzelnd und getrennt durchgeführt !
		{
			zCTree<zCVob> *child = globalVobTreeNode->GetFirstChild(); 
			while (child) 
			{
				zCVob *vob = child->GetData			();
				vob->BeginMovement					();
				vob->SetMovementHintTrafoLocalConst	(TRUE);
				vob->SetTrafoObjToWorld				(this->trafoObjToWorld * vob->GetTrafoLocal());
				vob->EndMovement					(a_bHintTrafoChanged);
				child = child->GetNextChild			();
			};
		};

		// Groundpoly setzen
		// FIXME: kann/muss mit anderen TraceRay nach unten Routs gekoppelt werden !!
		// nur setzen wenn: 
		// - Vob neu in Welt eingefuegt 
		// - Vob wirklich bewegt wurde (translation)
		if (a_bHintTrafoChanged) CalcGroundPoly			();

		// eine Bewegung macht eine gecachte Beleuchtung ungueltig
		// FIXME: das ist bei models nicht nötig, wenn sie sich innerhalb der ani nicht rotiert oder bewegt haben
		SetLightColorDynDirty	();
		SetLightColorStatDirty	();

		//
		zCVob::CheckAutoUnlink	(this);

		// im Debug wird hier die Konsistenz der Matrizen uberprueft
		#ifdef _DEBUG
		//	zERR_ASSERT (trafo.IsUpper3x3Orthonormal());
		//	zERR_ASSERT (trafoObjToWorld.IsUpper3x3Orthonormal());
		#endif

		if (GetVisual() && a_bHintTrafoChanged) CalcWaterVob();  // FIXME: opti: alle 2 frames oder so reicht alle male
	};

	// re-enter guard loeschen
	SetInsideEndMovementMethod (FALSE);
};


// ==================================================================================================================
// ==================================================================================================================


void zCVob::SetCollisionObject (zCCollisionObject* collObject)		
{ 
	delete m_poCollisionObject;
	m_poCollisionObject	= collObject;	
};

void zCVob::SetCollisionClass (zCCollisionObjectDef* collClass)	
{ 
	// Wechsel zwischen CollClasses? 
	if ((m_poCollisionObjectClass!=collClass) && (m_poCollisionObject))
	{
		DestroyCollisionObject	(TRUE);
	};
	m_poCollisionObjectClass= collClass;
};

zCCollisionObject* zCVob::GetCollisionObject () const
{ 
	return m_poCollisionObject;			
};

void zCVob::CreateCollisionObject ()
{
	if (!m_poCollisionObject) 
	{
		zERR_ASSERT (!this->GetInMovement());		// => wuerde bedeuten, dass im Block kein CollObject vorhanden ist (waere ein Fehler!)
		m_poCollisionObject							= m_poCollisionObjectClass->CreateNewInstance();	
		GetCollisionObject()->SetClientData			(this);
	};
};

void zCVob::ResetCollisionObjectState ()
{
	this->GetCollisionObject()->SetTrafoOld		(this->trafoObjToWorld);
	this->GetCollisionObject()->SetTrafoNew		(this->trafoObjToWorld);
	this->GetCollisionObject()->ResetTrafoHints	();
};

void zCCFASTCALL zCVob::DestroyCollisionObject (const zBOOL destroyEvenIfVolatile)
{
	if ((m_poCollisionObjectClass) && 
		((destroyEvenIfVolatile) || (m_poCollisionObjectClass->IsVolatile()))
		)
	{
		delete m_poCollisionObject;	m_poCollisionObject=0;
	};
};

// ==================================================================================================================

void zCVob::CheckEmergencyPutToSleep ()
{
	if (GetPhysicsEnabled())
	{
		if (GetCollisionClass()!=zCCollObjectCharacter::S_GetCollObjClass())
		{
			// x mal hintereinander Collision, ohne sich jeweils n cm weg zu bewegen ??
			const zREAL travelLen2	= (GetCollisionObject()->GetTrafoNew().GetTranslation() - GetCollisionObject()->GetTrafoOld().GetTranslation()).Length2();
			if (travelLen2<(1.0*1.0)) 
			{
				collButNoMove++;
				if (collButNoMove>8) 
				{
					// emergency !
					SetPhysicsEnabled	(FALSE);		// trans/rot auf 0
					if (callback_ai) {
						SetSleepingMode		(zVOB_AWAKE_DOAI_ONLY);
					} else {
						SetSleeping			(TRUE);
					};
					collButNoMove		= 0;
					db_Print ("going to sleep .. emergencyStop");
				};
			};
		};
	};
};

// ==================================================================================================================

// Die fuer einen Kollisionscheck gueltige lokale Umgebung des Vobs, gegen den getested wird
struct zCVob::zTCollisionContext
{
	zCArray<zCCollisionObject*> otherCollObjectList;
	zCArray<zCVob*>				otherCollVobList;
};

void zCCFASTCALL zCVob::CollectCollisionContext_Vobs (const zTBBox3D& speedBox, zTCollisionContext &collisionContext)
{
	if (!this->GetCollDetDyn()) return;

	// Vobs aus dem BSP ziehen
	zCArray<zCVob*>	vobList;
	homeWorld->GetBspTree()->GetRoot()->CollectVobsInBBox3D (vobList, speedBox);

	// NoCollision Vobs herausfiltern
	for (int i=0; i<vobList.GetNum(); i++)
	{
		zCVob *vob	= vobList[i];

		// 'this' rausfiltern
		if (!vob->GetCollDetDyn())	{ vobList.RemoveIndex (i); i--; continue; } else
		if (vob==this)				{ vobList.RemoveIndex (i); i--; continue; } 
		else 
		{
			// CollisionDetector fragen, ob die CollKlassen ueberhaupt kollidieren koennen
			if (!S_GetCollisionDetector()->CanCollide (this->GetCollisionClass(), vob->GetCollisionClass()))
			{
				vobList.RemoveIndex (i); i--; continue;
			};

			// AIs und Vobs gegenseitig fragen, ob dieses Paar wirklich kollidieren darf (Troll/Gobbo, Schuetze/Pfeil)
			zBOOL valid=TRUE;
			valid	= this->CanThisCollideWith (vob)  &&
					  vob ->CanThisCollideWith (this);
			if ((valid) && (this->GetAI()))		valid = this->GetAI()->CanThisCollideWith (vob);
			if ((valid) && (vob ->GetAI()))		valid = vob ->GetAI()->CanThisCollideWith (this);
			if (!valid)							{ vobList.RemoveIndex (i); i--; continue; };
		};

		// Existenz des CollObjects sicherstellen
		vob->CreateCollisionObject	();

		// CollObject des anderen Vobs NUR initialisieren, falls es sich nicht bereits selber im eigenen MovementBlock befindet
		if (!vob->GetInMovement())
		{
			vob->ResetCollisionObjectState	();
		};

		collisionContext.otherCollObjectList.Insert	(vob->GetCollisionObject());
		collisionContext.otherCollVobList.Insert	(vob);

		zADDREF_NOACCT(vob);		// zur Sicherheit
	};
};

void zCCFASTCALL zCVob::CollectCollisionContext_Static (const zTBBox3D& speedBox, zCArray<zCCollisionObject*> &otherCollObjectList)
{
	if (!this->GetCollDetStat()) return;

	//
	// CollisionDetector fragen, ob die CollKlassen ueberhaupt kollidieren koennen
	if (!S_GetCollisionDetector()->CanCollide (this->GetCollisionClass(), zCCollObjectLevelPolys::S_GetCollObjClass()))
		return;

	//
	zCPolygon		**foundPolyList;
	int				foundPolyNum;

	// 0) temporaeres zCCollisionObject fuer die erhaltene PolySoup erstellen
	static zCCollObjectLevelPolys collObjectLevel;
	collObjectLevel.m_aoPolyList.EmptyList();

	// 1) Polys aus dem BSP-Tree ziehen, die die Speedbox ueberlagern
	homeWorld->GetBspTree()->GetRoot()->CollectPolysInBBox3D (speedBox, foundPolyList, foundPolyNum);
	if (foundPolyNum<=0) return;

	// 2) Falls die Zustandsaenderung nur eine Translation enthaelt koennen backfacing Polys eliminiert werden
	zVEC3 transDelta;
	zBOOL filterOutBackfaces	= FALSE;
	if (!this->GetCollisionObject()->GetTrafoHintRotation())
	{
		transDelta			= this->GetCollisionObject()->GetTrafoOld().GetTranslation() - this->GetCollisionObject()->GetTrafoNew().GetTranslation();
		filterOutBackfaces	= TRUE;
	};

	// 3) Polys ermitteln, die die BBox ueberlagern		(BBox/Poly-Check)		=> SET verkleinern.
	//    dabei: Wasser-Polys rausfiltern
	//	  FIXME: evtl. einen schnelleren, konservativeren Test fuer das CheckBBoxPolyIntersection()..
	for (int i=0; i<foundPolyNum; i++) 
	{
		if (
			( (filterOutBackfaces) && ((foundPolyList[i]->GetNormal() * transDelta)<=0)) ||	// backface testen?
			(!foundPolyList[i]->CheckBBoxPolyIntersection (speedBox)) ||					// bbox/poly intersection test: 
			( foundPolyList[i]->GetMaterial()->GetMatGroup()==zMAT_GROUP_WATER) ||
			( foundPolyList[i]->GetMaterial()->GetNoCollDet()) 
			)
		{
			foundPolyNum--;
			foundPolyList[i] = foundPolyList[foundPolyNum];
			i--;
		} else {
			collObjectLevel.m_aoPolyList.Insert	(foundPolyList[i]);
		};
	};
	if (!collObjectLevel.m_aoPolyList.IsEmpty())
		otherCollObjectList.Insert (&collObjectLevel);
};

void zCCFASTCALL zCVob::CollectCollisionContext (zTCollisionContext &collisionContext)
{
	// Speedbox bilden
	// FIXME: PERF!
	zTBBox3D speedBox;
	{
//		CalcDestinationBBox3DWorld		(speedBox);
//		speedBox.CalcGreaterBBox3D		(this->GetBBox3DWorld());

		zTBBox3D tmpBox;
		GetCollisionObject()->GetLargestBBox3DLocal(tmpBox);
		tmpBox.Transform				(GetCollisionObject()->GetTrafoOld(), speedBox);	// t0
		tmpBox.Transform				(GetCollisionObject()->GetTrafoNew(), tmpBox);		// t1
		speedBox.CalcGreaterBBox3D		(tmpBox);											// union

	};
	#ifdef DEBUG_HILDEBRANDT
	//	speedBox.Draw (GFX_GREEN);
	#endif

	// Liste leeren
	collisionContext.otherCollObjectList.EmptyList		();

	// Vobs aus dem BSP ziehen
	CollectCollisionContext_Vobs		(speedBox, collisionContext);

	// Polys aus dem BSP ziehen
	CollectCollisionContext_Static		(speedBox, collisionContext.otherCollObjectList);
};

void zCCFASTCALL zCVob::CleanupCollisionContext(const zTCollisionContext &collisionContext)
{
	for (int i=0; i<collisionContext.otherCollVobList.GetNum(); i++)
	{
		// CollObject des anderen Vobs NUR loeschen, falls es sich nicht bereits selber im eigenen MovementBlock befindet
		zCVob *otherVob = collisionContext.otherCollVobList[i];
		if (!otherVob->GetInMovement())
		{
			otherVob->DestroyCollisionObject ();
		};

		zRELEASE_NOACCT(otherVob);
	};
};


void zCCFASTCALL zCVob::NotifyCollisionPair (zCCollisionReport					*collReport, 
											 const zCArray<zCCollisionReport*>	&collReportList,
											 zBOOL								dontSendTouchMessages)
{
	zCVob *vob0	= static_cast<zCVob*>(collReport->m_poCollObject0->GetClientData());
	zCVob *vob1	= static_cast<zCVob*>(collReport->m_poCollObject1->GetClientData());

	// das erste Objekt im CollisionReport sollte immer das sich bewegende sein.
	zERR_ASSERT (vob0==this);

	// Kollision mit Level?
	if (collReport->m_poCollObject1->GetCollObjClass()==zCCollObjectLevelPolys::S_GetCollObjClass())
	{
		vob0->GetEM()->OnTouchLevel();
	};

	// Kollision Vob vs Vob
	if (vob0 && vob1)
	{
		// Response auf anderem CollObject ausloesen
		zBOOL simulateFurtherDummy;
		((vob0!=this) ? vob0 : vob1)->GetCollisionObject()->CollisionResponse (collReportList, simulateFurtherDummy);

		// Vobs benachrichtigen
		if (!dontSendTouchMessages)
		{
			vob0->GetEM()->OnTouch  (vob1);
			vob1->GetEM()->OnTouch  (vob0);
			vob1->GetEM()->OnUntouch(vob0);
			vob0->GetEM()->OnUntouch(vob1);
		};
	};

	// AIs benachrichtigen
	if (vob0->GetAI())				vob0->GetAI()->ReportCollisionToAI	(*collReport);
	if ((vob1) && (vob1->GetAI()))	vob1->GetAI()->ReportCollisionToAI	(*collReport);
};

void zCCFASTCALL zCVob::ExecuteCollisionResponse (const zCArray<zCCollisionReport*> &collReportList, zBOOL& simulateFurther)
{
	// CollisionResponse
	// => veraendert ggfs. Objekt Eigenschaften, insb. den gewuenschten Zustand fuer t=1
	zERR_ASSERT							(collReportList.GetNum()>0);
	simulateFurther						= FALSE;
	collReportList[0]->m_poCollObject0->CollisionResponse (collReportList, simulateFurther);
	db_Print							("response");

	// CollisionNotification
	// (weitere Objekte ueber Kollision informieren: AI, Vob)
	zBOOL simulateFurtherDummy			= FALSE;
	for (int i=0; i<collReportList.GetNum(); i++)
	{
		// Collision Response
		// Response auf anderem CollObject ausloesen
		{
			zCVob *vob0	= static_cast<zCVob*>(collReportList[i]->m_poCollObject0->GetClientData());
			zCVob *vob1	= static_cast<zCVob*>(collReportList[i]->m_poCollObject1->GetClientData());

			// Kollision Vob vs Vob
			if (vob0 && vob1)
			{
				((vob0!=this) ? vob0 : vob1)->GetCollisionObject()->CollisionResponse (collReportList, simulateFurtherDummy);
			};
		};

		// Notify
		NotifyCollisionPair (collReportList[i], collReportList);
	};

	// Hint resetten: Falls beim Updaten der Childs eines VobTrees Kollisionen auftraten, bleibt die trafoLocal 
	// (die relativ zum Parent ist) nicht konstant (da ja die ColLResp auf sie wirkt).
	this->SetMovementHintTrafoLocalConst	(FALSE);
};

void zCVob::CheckAndResolveCollisions()
{
	// Testet den Zielzustand des CollisionObjects dieses Vobs auf Gueltigkeit.
	// Ggfs. durch Responses in einen gueltigen Zustand bringen.
	// Initiert bei auftretenen Kollisionen Notifications und Responses.
	// Nach Verlassen ist zCCollisionObject::trafoNew der gueltige, kollisionsfreie, neue Zustand.

	if (!(GetCollDetStat() || GetCollDetDyn())) return;

	//
	zCCollisionObject*			movingCollObject	= GetCollisionObject();
	zCVob::zTCollisionContext	collisionContext;
	zCArray<zCCollisionReport*>	collReportList;
	zCArray<zCVob*>				newTouchVobList;				// Liste aller Vobs, die diesen beruehrt werden und per CollObj nur eine 'softe' Kollision haben (z.B. TriggerBoxen)
	zBOOL						simulateFurther		= FALSE;
	int							numIterations		= 0;

	db_Print ("**ENTER**: "+this->GetVobName());

	zBOOL blockEnd=TRUE;
	do
	{
		if (!blockEnd)
			db_PrintBlockEnd();
		blockEnd			= FALSE;
		db_PrintBlockBegin	();
		db_Print			("numIter: "+zSTRING(numIterations));

		if (numIterations>=3) 
		{
			// Nach mehreren Iterationen durch die CollDet/CollResp Loop konnte kein entgueltiger, die gesamte Bewegung
			// abdeckender Endzustand fuer t=1 gefunden werden. Hier koennte man theoretisch 2 verschiedene Faelle 
			// unterscheiden:
			// a) Kollisionen lagen bereits bei t=0 vor, die konnten natuerlich von CollResp nicht aufgeloest werden
			// b) mehrere CollDet/CollResp Loopdurchgaenge mit diversen Zwischenergebnissen, nach x Iterationen muesste
			//    eigentlich ein gueltiger Zustand erreicht werden.
			// Bei diesem Not-Exit wird der letzte garantiert gueltige Zustand (trafoOld) als neuer, gueltiger Zielzustand
			// festgelegt und in trafoNew kopiert.
			movingCollObject->SetTrafoNew (movingCollObject->GetTrafoOld());
			break;
		};

		collReportList.EmptyList();
		simulateFurther			= FALSE;

		// Einen lokalen 'Kollisionskontext' bilden
		// Objekte ermitteln und einsammeln, die mit diesem kollidieren koennten
		// (SpeedBox bilden, Vobs aus BSP holen, LevelPolys in ein CollObject verpacken)
		// (ggfs. kann bei einem retry die collisionContext.otherCollObjectList der letzten Iteration weiterbenutzt werden)
		if (numIterations==0)
			CollectCollisionContext (collisionContext);

		// Physikalische Simulation (von tx nach ty)
		// ..

		// Kollisionen ermitteln
		S_GetCollisionDetector()->DetectCollisions (movingCollObject, collisionContext.otherCollObjectList, collReportList);

		// Kollision stattgefunden?
		if (!collReportList.IsEmpty())
		{
			// 'soft-collisions' rausfiltern
			// (hmmm.. diese Sache macht den ganzen Mechanismus ein wenig 'undurchsichtiger'. Evtl. klarere Implemenation?)
			const zBOOL	collObject0SuppressCollResponse	= movingCollObject->SuppressCollisionResponse();
			zREAL		firstTimeOfCollision			= 0;

			for (int i=0; i<collReportList.GetNum(); i++)
			{
				zCCollisionObject *collObject1	= collReportList[i]->m_poCollObject1;
				if ((collObject1->SuppressCollisionResponse()) || (collObject0SuppressCollResponse))
				{
					//
					firstTimeOfCollision		= collReportList[i]->m_fTimeStamp;
					zCVob *vob1					= static_cast<zCVob*>(collObject1->GetClientData());
					newTouchVobList.Insert		(vob1);							// Vob fuer spaetere Notification merken (

					// Notify
					// (so wird allerdings bei einer laengeren softColl jeden Frame erneut z.B. die AI notified..)
					// (andere Moeglichkeit: die relevanten CollReports merken und spaeter zusammen mit OnTouch in UpdateTouchList die AIMeldungen verschicken)
					NotifyCollisionPair			(collReportList[i], collReportList, TRUE);	// TRUE= keine TouchMessages an die Vobs (wird am Ende fuer alle gemacht)

					// CollReport und Objekt aus Listen entfernen
					collisionContext.otherCollObjectList.Remove	(collObject1);	// keine Collision mehr gegen dieses Objekt testen
					collReportList.RemoveIndex	(i);
					--i;
				};
			};

			if (collReportList.IsEmpty())
			{
				// Keine CollReports mehr vorhanden? => alle aufgetretenen Kollisionen bei tc waren 'soft-collisions'
				if (collisionContext.otherCollObjectList.IsEmpty())
				{
					// es gibt (nach Eliminierung der SoftColl Objekte) keine potentiellen Kollisions-'Gegner' mehr => fertig!
					simulateFurther				= FALSE;
				} else 
				{
					// es gibt noch weitere Objekte zwischen tc unt t=1, mit denen bisher nich kollidiert wurde, aber 
					// gegen die noch weitergetestet werden muss.
					// trafoOld wird zu trafoTC, trafoNew bleibt als altes und neues Ziel bestehen
					simulateFurther				= TRUE;
					movingCollObject->CalcIntermediateTrafo	(firstTimeOfCollision, movingCollObject->GetTrafoOld());
				};
			} else 
			{
				// CollisionResponse
				// => veraendert ggfs. Objekt Eigenschaften, insb. den gewuenschten Zustand fuer t=1
				ExecuteCollisionResponse		(collReportList, simulateFurther);
			};
		};

		//
		++numIterations;

	} while (simulateFurther);

	//
//	zBOOL hadCollision		= (collReportList.GetNum()>0);		// wurde mit unaufgeloester Collision beendet?
//	CheckEmergencyPutToSleep();

	//
	UpdateTouchList			(newTouchVobList);

	//
	CleanupCollisionContext (collisionContext);

	// debug tracing
	if (!blockEnd)			db_PrintBlockEnd();
};

zBOOL zCVob::IsColliding ()
{
	// Testet den Zustand des CollisionObjects dieses Vobs auf Gueltigkeit.

	if (!(GetCollDetStat() || GetCollDetDyn())) return FALSE;

	//
	zCCollisionObject*			movingCollObject	= GetCollisionObject();
	zCVob::zTCollisionContext	collisionContext;
	zCArray<zCCollisionReport*>	collReportList;
	zBOOL						isColliding			= FALSE;

	{
		// Einen lokalen 'Kollisionskontext' bilden
		// Objekte ermitteln und einsammeln, die mit diesem kollidieren koennten
		// (SpeedBox bilden, Vobs aus BSP holen, LevelPolys in ein CollObject verpacken)
		CollectCollisionContext (collisionContext);

		// Kollisionen ermitteln
		S_GetCollisionDetector()->DetectCollisions (movingCollObject, collisionContext.otherCollObjectList, collReportList);

		// Kollision stattgefunden?
		if (!collReportList.IsEmpty())
		{
			// 'soft-collisions' rausfiltern
			for (int i=0; i<collReportList.GetNum(); i++)
			{
				zCCollisionObject *collObject1 = collReportList[i]->m_poCollObject1;
				if (collObject1->SuppressCollisionResponse())
				{
					#ifdef _DEBUG
					collisionContext.otherCollObjectList.Remove	(collObject1);	// keine Collision mehr gegen dieses Objekt testen
					#endif
					collReportList.RemoveIndex	(i);			// Report nicht mehr noetig, Kollision gilt als 'behandelt'
					--i;
				};
			};

			isColliding	= !collReportList.IsEmpty();

			#ifdef _DEBUG
				if (isColliding)
				{
					//zERR_ASSERT (collisionContext.otherCollObjectList.IsEmpty());
				};
			#endif
		};

		CleanupCollisionContext (collisionContext);
	};


	return isColliding;
};

/*
#ifdef DEBUG_HILDEBRANDT
			{
				// TEST_MUELL
				const zMAT4 newCopy = movingCollObject->GetTrafoNew();
				movingCollObject->SetTrafoNew(movingCollObject->GetTrafoOld());

				collReportList.EmptyList();
				S_GetCollisionDetector()->DetectCollisions (movingCollObject, otherCollObjectList, collReportList);
				if (collReportList.GetNum()>0)
					zerr.Message ("D: intersection at t=0, AFTER CollisionResponse");
				collReportList.EmptyList();

				movingCollObject->SetTrafoNew(newCopy);
			};
#endif
*/