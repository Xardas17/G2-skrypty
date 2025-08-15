/******************************************************************************** 
 
     $Workfile:: zCollisionObjectMisc $                $Date:: 25.01.01 14:48   $
     $Revision:: 10                   $             $Modtime:: 25.01.01 14:18   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Collection of zCCollsionObject subclasses.
   created       : 8.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zCollisionObjectMisc.cpp $
 * 
 * 10    25.01.01 14:48 Moos
 * 
 * 9     15.01.01 19:12 Hildebrandt
 * 
 * 8     21.12.00 21:24 Hildebrandt
 * 
 * 7     20.12.00 3:03 Hildebrandt
 * 
 * 6     15.12.00 3:55 Hildebrandt
 * 
 * 5     14.12.00 20:56 Hildebrandt
 * 
 * 4     14.12.00 20:43 Hildebrandt
 * 
 * 3     13.12.00 3:24 Hildebrandt
 * 
 * 2     9.12.00 6:31 Hildebrandt
 * 
 * 1     8.12.00 21:29 Hildebrandt
 *********************************************************************************/

// DOC++
/// @author   Author: Hildebrandt 
/// @version $Revision: 10 $ ($Modtime: 25.01.01 14:18 $)

// ============================================================================================================

#include <zCore.h>
#include <zBVolume.h>
#include <zCollisionDetector.h>
#include <zCollisionObject.h>

#include <zCollisionObjectMisc.h>

#include <z3d.h>
#include <zVob.h>
#include <zPhysics.h>
#include <zWorld.h>
#include <zGrafix.h>
#include <zModel.h>

// ============================================================================================================

zCOLLISION_OBJECT_DEFINITION (zCCollObjectUndef			, TRUE)
zCOLLISION_OBJECT_DEFINITION (zCCollObjectLevelPolys	, TRUE)
zCOLLISION_OBJECT_DEFINITION (zCCollObjectCharacter		, FALSE)
zCOLLISION_OBJECT_DEFINITION (zCCollObjectPoint			, TRUE)
zCOLLISION_OBJECT_DEFINITION (zCCollObjectProjectile	, TRUE)
zCOLLISION_OBJECT_DEFINITION (zCCollObjectComplex		, TRUE)

zCOLLISION_OBJECT_DEFINITION (zCCollObjectBoxBlocker	, TRUE)
zCOLLISION_OBJECT_DEFINITION (zCCollObjectBoxPassThrough, TRUE)

// ============================================================================================================

extern zBOOL TestStatic_Char_Char	(zREAL timeStamp, 
									 zCCollisionObject*  collObject0, const zMAT4& trafoObj0,
									 zCCollisionObject*  collObject1, const zMAT4& trafoObj1,
									 zCCollisionReport** ppoCollReport);

// ============================================================================================================

/*
	NOTE: Was bei der Programmierung von zCCollObject::CollisionResponse() Methoden zu beachten ist:
	
	CollisionResponse:
	- Bei Eintritt enthaelt trafoOld den alten und trafoNew den neuen Zustand. Zwischen old und new trat mind. 1
	  Kollision auf. Die timeStamps der CollisionReports beziehen sich auf einen Zeitpunkt. Der timeStamp mit
	  dem kleinsten t ist ein Ort mit garantierter Kollisionsfreiheit.
	- Moegliche Reaktionsschemas sind z.B.

	  a) Zum t0 zuruecksetzen, Response fuer naechsten Frame einstellen, stop
		trafoNew		= trafoOld;
		// Zustandsaenderungen (z.B. auf RigidBody)
		simulateFurther	= FALSE;

	  b) Zum tc bewegen, Response fuer naechsten Frame einstellen, stop
		trafoNew		= trafoCollsion;
		// Zustandsaenderungen (z.B. auf RigidBody)
		simulateFurther	= FALSE;

	  c) Zum tc bewegen, Response berechnen, weitersimulieren
		trafoOld		= trafoCollision;
		trafoNew		= *neu berechnet, z.B. durch Sliding*	// der neue, fuer t=1 gewuenschte Zustand
		simulateFurther	= TRUE;

	- Beim Austritt:
		- simulateFurther	= FALSE
			- trafoOld		: Inhalt unwichtig
			- trafoNew		: neuer, garantiert kollisionsfreier Zustand
		- simulateFurther	= TRUE
			- trafoOld		: ein alter, kollisionsfreier Zustand (z.B. der des gemeldeten tc's)
			- trafoNew		: neuer Zustand, der im weiteren noch auf Kollision getestet werden muss
*/

/*

	GetAdaptiveStepSize()
		vom kleinsten CollVolumen die Laenge der kleinsten Axen-Projektion

*/

// ============================================================================================================

void zCCFASTCALL zCCollObjectPoint::GetLargestBBox3DLocal(zTBBox3D &bbox3DLocalOut)
{
	bbox3DLocalOut.mins	= bbox3DLocalOut.maxs = GetCenterOffsetLocal();
};

void zCCFASTCALL zCCollObjectPoint::CollisionResponse	(const zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther)
{
	if (!this->HasMoved())	return;
	CalcIntermediateTrafo	(collReportList[0]->m_fTimeStamp, GetTrafoNew ());
	
	// physikalische Response nur ausfuehren, wenn sich Vob auch physikalisch bewegt
	if (GetVob()->GetPhysicsEnabled())
	{
		zBOOL adjustUpVector	= FALSE;
		zBOOL doSliding			= GetVob()->GetRigidBody()->ShouldSlide (collReportList[0]->m_oCollNormal0);
		if (doSliding) {
			// Sliding - Response
			// zerr.Message ("sliding.. "+collPlane.normal.GetString()); 
			if (!GetVob()->GetRigidBody()->SetSliding (collReportList[0]->m_oCollNormal0)) {
			};
			adjustUpVector	= TRUE;
		} else 
		{
			// Impulse - Response
			// zerr.Message ("impulse.. "+collPlane.normal.GetString());
			// Contact Point
			GetVob()->GetRigidBody()->SetMode						(zPHY_RBMODE_FLY);
			GetVob()->GetRigidBody()->CollisionImpulseCenterStatic	(collReportList[0]->m_oCollNormal0, 0.2F);
			if (collReportList[0]->m_oCollNormal0[VY]>0.5F)
				adjustUpVector	= TRUE;
		};

		if (adjustUpVector)
		{
			SetUpVectorNew (collReportList[0]->m_oCollNormal0);
		};

		// Kommt der Koerper zur Ruhe ?
		// FIXME: beim sliding am Hang gilt dies nicht.. (falls er gerade hochgeht & dann wendet..) => wird bereits in ::DoFrameActivity() gehandelt !!!
		{
			if (GetVob()->GetRigidBody()->GetVelocity().Length2()<(100*100)) 
			{
				// Legt sich nur schlafen, wenn keine AI mitmischt ?
				GetVob()->SetPhysicsEnabled		(FALSE);
				if (GetVob()->GetAI()) {
					GetVob()->SetSleepingMode	(zVOB_AWAKE_DOAI_ONLY);
				} else {
					GetVob()->SetSleeping		(TRUE);
				};
			};
		};
		};
};

zVEC3 zCCFASTCALL zCCollObjectPoint::GetCenterOffsetLocal() const
{
	// RayOrigin zum Mittelpunkt der Bodenflaeche der LocalBBox offseten
	zCVisual	*objPointVisual = GetVob()->GetVisual();
	if ((objPointVisual) && (objPointVisual->IsBBox3DLocal()))
	{
		return objPointVisual->GetBBox3D().GetCenterFloor();
	} else
		return zVEC3(0);
};

zVEC3 zCCFASTCALL zCCollObjectPoint::GetCenterOffsetNew() const
{
	// RayOrigin zum Mittelpunkt der Bodenflaeche der LocalBBox offseten
	const zVEC3& floorCenter = GetCenterOffsetLocal();
	return	floorCenter[VX] * GetTrafoNew().GetRightVector	() +
			floorCenter[VY] * GetTrafoNew().GetUpVector		() +
			floorCenter[VZ] * GetTrafoNew().GetAtVector		();
};

void zCCFASTCALL zCCollObjectPoint::SetUpVectorNew (const zVEC3& newUp)
{
	GetTrafoNew().Translate			( GetCenterOffsetNew());
	GetTrafoNew().SetUpVector		(newUp);
	GetTrafoNew().MakeOrthonormal	();
	GetTrafoNew().Translate			(-GetCenterOffsetNew());	// der Offset hat sich veraendert, also neu berechnen lassen
};

void zCCFASTCALL zCCollObjectPoint::DetectCollisionsSelf(const zCArray<zCCollisionObject*>& otherCollObjectList,
															   zCArray<zCCollisionReport*>&	collReportList) 
{
};

// ============================================================================================================

zREAL zCCFASTCALL zCCollObjectComplex::GetAdaptiveStepSize ()	
{
	return S_CalcAdaptiveCollStepFromVisualBBox (GetVob()->GetVisual());
};

void zCCFASTCALL zCCollObjectComplex::CollisionResponse (const zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther)
{
	if (!this->HasMoved()) return;
//	SetTrafoNew (GetTrafoOld());
	CalcIntermediateTrafo(collReportList[0]->m_fTimeStamp, GetTrafoNew ());
	
	zBOOL doSliding = GetVob()->GetRigidBody()->ShouldSlide (collReportList[0]->m_oCollNormal0);
	if (doSliding) 
	{
		// Sliding - Response
		// zerr.Message ("sliding.. "+collPlane.normal.GetString()); 
		if (!GetVob()->GetRigidBody()->SetSliding (collReportList[0]->m_oCollNormal0)) {
		};
	} else 
	{
		// Impulse - Response
		// zerr.Message ("impulse.. "+collPlane.normal.GetString());
		// Contact Point
		GetVob()->GetRigidBody()->SetMode						(zPHY_RBMODE_FLY);
		GetVob()->GetRigidBody()->CollisionImpulseCenterStatic	(collReportList[0]->m_oCollNormal0, 0.2F);
	};

	// Kommt der Koerper zur Ruhe ?
	// FIXME: beim sliding am Hang gilt dies nicht.. (falls er gerade hochgeht & dann wendet..) => wird bereits in ::DoFrameActivity() gehandelt !!!
	if (GetVob()->GetPhysicsEnabled())
	{
		if (GetVob()->GetRigidBody()->GetVelocity().Length2()<(100*100)) 
		{
			// Legt sich nur schlafen, wenn keine AI mitmischt ?
			GetVob()->SetPhysicsEnabled		(FALSE);
			if (GetVob()->GetAI()) 
			{
				GetVob()->SetSleepingMode	(zVOB_AWAKE_DOAI_ONLY);
			} else 
			{
				GetVob()->SetSleeping		(TRUE);
			};
		};
	};
};

// ============================================================================================================

// ===============================
//	Static Intersection Tests
// ===============================


static zBOOL TestStatic_Complex_LevelPolys (zREAL timeStamp, 
										    zCCollisionObject*  collObject0, const zMAT4& trafoObj0,
										    zCCollisionObject*  collObject1, const zMAT4& trafoObj1,
										    zCCollisionReport** ppoCollReport)
{
	const zCCollObjectComplex*		objComplex	= static_cast<zCCollObjectComplex   *>(collObject0);
	const zCCollObjectLevelPolys*	objLevel	= static_cast<zCCollObjectLevelPolys*>(collObject1);

	// Complex aus dem Vob/Visual herausziehen
	zCVisual	*obj0Visual	= (objComplex->GetVob()) ? (objComplex->GetVob()->GetVisual()) : 0;
	if (!obj0Visual)	return FALSE;

	//
	zTBBox3D	objComplexAABB;
	zCOBBox3D	*obbTree	= obj0Visual->GetOBBox3D();
	if (!obbTree)
	{
		if (obj0Visual->IsBBox3DLocal())
		{
			obj0Visual->GetBBox3D().Transform (trafoObj0, objComplexAABB);
		} else
			return FALSE;
	};

	//
	const zMATRIX4	trafoWorldToObj = trafoObj0.InverseLinTrafo();
	for (int i=0; i<objLevel->m_aoPolyList.GetNum(); i++) 
	{ 
		zCPolygon	*poly	= objLevel->m_aoPolyList[i];
		zBOOL		hit;
		if (obbTree)	hit = obbTree->CheckOBBPolyIntersection (poly, trafoWorldToObj);
		else			hit = poly->CheckBBoxPolyIntersection (objComplexAABB);
		if (hit)
		{
			// VEREINFACHUNG:
			// hier wird bereits bei dem ersten Poly abgebrochen
			if (ppoCollReport)
			{
				// Report besorgen (den generischen)
				(*ppoCollReport)					= zCCollisionDetector::S_GetNextFreeCollReport();
				// Report ausfuellen
				(*ppoCollReport)->m_fTimeStamp		= timeStamp;
				(*ppoCollReport)->m_oContactPoint	= trafoObj0.GetTranslation();
				(*ppoCollReport)->m_oCollNormal0	= poly->GetNormal();
				(*ppoCollReport)->m_oCollNormal1	= -(*ppoCollReport)->m_oCollNormal0;
			};
			return TRUE;
		};
	};

	return FALSE;
};

// ============================================================================================================

static zBOOL TestStatic_Complex_Complex	   (zREAL timeStamp, 
										    zCCollisionObject*  collObject0, const zMAT4& trafoObj0,
										    zCCollisionObject*  collObject1, const zMAT4& trafoObj1,
										    zCCollisionReport** ppoCollReport)
{
	// Derzeit Test der Local AABB gegeneinander.
	// TODO: Test der OBBTrees gegeneinander, falls vorhanden.
	const zCCollObjectComplex*	objComplex0	= static_cast<zCCollObjectComplex   *>(collObject0);
	const zCCollObjectComplex*	objComplex1 = static_cast<zCCollObjectComplex*>(collObject1);

	// Complex aus dem Vob/Visual herausziehen
	zCVisual	*obj0Visual	= (objComplex0->GetVob()) ? (objComplex0->GetVob()->GetVisual()) : 0;
	zCVisual	*obj1Visual	= (objComplex1->GetVob()) ? (objComplex1->GetVob()->GetVisual()) : 0;
	if ((!obj0Visual) || (!obj1Visual))	return FALSE;

	//
	zBOOL foundIntersection = FALSE;

	// Haben beide OBBTrees verfuegbar ? 
	zCOBBox3D	*obj0OBB	= obj0Visual->GetOBBox3D();
	zCOBBox3D	*obj1OBB	= obj1Visual->GetOBBox3D();
	if (obj0OBB && obj1OBB)
	{
		// OBBTree vs. OBBTree
		// PERF: evtl. vorher einmal ein schneller bbox-Check vorweg ?

		const zMATRIX4&	trafoObj1ToObj0	= trafoObj0.InverseLinTrafo() * trafoObj1;
		foundIntersection				= obj0OBB->TestIntersectionTree (obj1OBB, trafoObj1ToObj0);
	} else 
	{
		// WorldSpace AABB vs. AABB
		zTBBox3D	objComplex0AABB;
		if (obj0Visual->IsBBox3DLocal())
		{
			obj0Visual->GetBBox3D().Transform (trafoObj0, objComplex0AABB);
		} else
			return FALSE;

		//
		zTBBox3D	objComplex1AABB;
		if (obj1Visual->IsBBox3DLocal())
		{
			obj1Visual->GetBBox3D().Transform (trafoObj1, objComplex1AABB);
		} else
			return FALSE;

		// 
		if (objComplex0AABB.IsIntersecting(objComplex1AABB))
		{
			foundIntersection = TRUE;
		};
	};

	//
	if (foundIntersection)
	{
		if (ppoCollReport)
		{
			// Report besorgen (den generischen)
			(*ppoCollReport)				= zCCollisionDetector::S_GetNextFreeCollReport();
			// Report ausfuellen
			(*ppoCollReport)->m_fTimeStamp	= timeStamp;
			zCCollObjectBase::S_CalcGeneric_CollNormal_ContactPoint (objComplex0->GetVob(), objComplex1->GetVob(), **ppoCollReport);
		};
		return TRUE;
	};

	return FALSE;
};

// ============================================================================================================

// ===============================
//	Dynamic Intersection Tests
// ===============================

// first object is moving (trafoOld=>trafoNew), second is static

static zBOOL TestDynamic_Point_LevelPolys(zCCollisionObject*  collObject0,
										  zCCollisionObject*  collObject1,
										  zCCollisionReport** ppoCollReport)
{
	const zCCollObjectPoint*		objPoint	= static_cast<zCCollObjectPoint     *>(collObject0);
	const zCCollObjectLevelPolys*	objLevel	= static_cast<zCCollObjectLevelPolys*>(collObject1);

	// Ray von old nach new gegen alle Polys testen
	const zPOINT3&	rayOrigin	= objPoint->GetTrafoOld().GetTranslation() + objPoint->GetCenterOffsetNew();
	const zVEC3&	ray			= objPoint->GetTrafoNew().GetTranslation() - objPoint->GetTrafoOld().GetTranslation();
	// FIXME: was bei rayLen==0? (=> bei inPlace CollTests..)

	//
	zVEC3 inters;
	zREAL alpha;
	for (int i=0; i<objLevel->m_aoPolyList.GetNum(); i++)
	{
		zCPolygon *poly = objLevel->m_aoPolyList[i];
		if (poly->CheckRayPolyIntersection (rayOrigin, ray, inters, alpha))
		{
			if (ppoCollReport)
			{
				// Report besorgen (den generischen)
				(*ppoCollReport)					= zCCollisionDetector::S_GetNextFreeCollReport();
				// Report ausfuellen
				(*ppoCollReport)->m_fTimeStamp		= alpha * zREAL(0.95F);			// etwas vom Kollisionsort wegruecken
				(*ppoCollReport)->m_oContactPoint	= inters;
				(*ppoCollReport)->m_oCollNormal0	= poly->GetNormal();
				(*ppoCollReport)->m_oCollNormal1	= -(*ppoCollReport)->m_oCollNormal0;
			};
			return TRUE;
		};
	};

	return FALSE;
};

// ============================================================================================================

static zBOOL TestDynamic_Point_Complex	( zCCollisionObject*  collObject0,
										  zCCollisionObject*  collObject1,
										  zCCollisionReport** ppoCollReport)
{
	const zCCollObjectPoint*	objPoint	= static_cast<zCCollObjectPoint     *>(collObject0);
	const zCCollObjectComplex*	objComplex	= static_cast<zCCollObjectComplex	*>(collObject1);

	// Ray von old nach new in das Mesh tracen
	const zPOINT3&	rayOrigin	= objPoint->GetTrafoOld().GetTranslation() + objPoint->GetCenterOffsetNew();
	const zVEC3&	ray			= objPoint->GetTrafoNew().GetTranslation() - objPoint->GetTrafoOld().GetTranslation();
	// FIXME: was bei rayLen==0? (=> bei inPlace CollTests..)

	zTTraceRayReport	traceRayReport;
	int					traceFlags	= zTRACERAY_POLY_NORMAL | zTRACERAY_POLY_IGNORE_TRANSP;
	if (objComplex->GetVob()->TraceRay (rayOrigin, ray, traceFlags, traceRayReport))
	{
		if (ppoCollReport)
		{
			// Report besorgen (den generischen)
			(*ppoCollReport)					= zCCollisionDetector::S_GetNextFreeCollReport();
			// Report ausfuellen
			zREAL alpha							= (traceRayReport.foundIntersection - rayOrigin).Length() / ray.Length();
			zClamp01							(alpha);							// safety
			(*ppoCollReport)->m_fTimeStamp		= alpha * zREAL(0.95F);				// etwas vom Kollisionsort wegruecken
			(*ppoCollReport)->m_oContactPoint	= traceRayReport.foundIntersection;
			(*ppoCollReport)->m_oCollNormal0	= traceRayReport.foundPolyNormal;
			(*ppoCollReport)->m_oCollNormal1	=-traceRayReport.foundPolyNormal;
		};
		return TRUE;
	};

	return FALSE;
};

// ============================================================================================================

zBOOL TestDynamic_Projectile_Char( zCCollisionObject*  collObject0,
								   zCCollisionObject*  collObject1,
								   zCCollisionReport** ppoCollReport)
{
	const zCCollObjectProjectile*	objPoint= static_cast<zCCollObjectProjectile*>(collObject0);
	const zCCollObjectCharacter*	objChar	= static_cast<zCCollObjectCharacter	*>(collObject1);

	// Ray von old nach new in das Mesh tracen
	const zPOINT3&	rayOrigin	= objPoint->GetTrafoOld().GetTranslation() + objPoint->GetCenterOffsetNew();
	const zVEC3&	ray			= objPoint->GetTrafoNew().GetTranslation() - objPoint->GetTrafoOld().GetTranslation();
	// FIXME: was bei rayLen==0? (=> bei inPlace CollTests..)

	zPOINT3 inters;
	if (objChar->GetVob()->GetBBox3DWorld().TraceRay (rayOrigin, ray, inters))
	{
		if (ppoCollReport)
		{
			// Report besorgen (den generischen)
			(*ppoCollReport)				= zCCollisionDetector::S_GetNextFreeCollReport();
			// Report ausfuellen
			zREAL alpha						= (inters - rayOrigin).Length() / ray.Length();
			(*ppoCollReport)->m_fTimeStamp	= alpha * zREAL(0.95F);			// etwas vom Kollisionsort wegruecken
			zCCollObjectBase::S_CalcGeneric_CollNormal_ContactPoint (objPoint->GetVob(), objChar->GetVob(), **ppoCollReport);
		};
		return TRUE;
	};

	return FALSE;
};

// ============================================================================================================

zBOOL TestDynamic_XXX_BoxPassThrough	(zCCollisionObject*  collObject0,	// in Bewegung
										 zCCollisionObject*  collObject1,	// statisch
										 zCCollisionReport** ppoCollReport)
{
	const zCCollisionObject*			objXXX	= static_cast<zCCollisionObject			*>(collObject0);
	const zCCollObjectBoxPassThrough*	objBox	= static_cast<zCCollObjectBoxPassThrough*>(collObject1);

	//
	zCVob*	vobXXX	= static_cast<zCVob*>(objXXX->GetClientData());
	zCVob*	vobBox	= objBox->GetVob();

	//
	zERR_ASSERT (vobXXX);
	zERR_ASSERT (vobBox);

	// WorldSpace AABB, AABB Sweep Test
	zREAL timeStamp;
	if (vobXXX->GetBBox3DWorld ().IsIntersectingSweep (objXXX->GetTrafoNew().GetTranslation(), vobBox->GetBBox3DWorld(), timeStamp))
	{
		if (ppoCollReport)
		{
			// Report besorgen (den generischen)
			(*ppoCollReport)				= zCCollisionDetector::S_GetNextFreeCollReport();
			// Report ausfuellen
			(*ppoCollReport)->m_fTimeStamp	= timeStamp * zREAL(0.95F);			// etwas vom Kollisionsort wegruecken
			zCCollObjectBase::S_CalcGeneric_CollNormal_ContactPoint (vobXXX, vobBox, **ppoCollReport);
		};
		return TRUE;
	};

	return FALSE;
};

// ============================================================================================================
// ============================================================================================================

// generische Helper Funktionen fuer alle zCCollisionObject Klassen

zREAL zCCFASTCALL zCCollObjectBase::S_CalcAdaptiveCollStepFromVisualBBox (zCVisual *visual) 
{
	// evtl. kann/sollte man hier auch die Richtung der Bewegung miteinbeziehen
	if (visual)
	{
		if (visual->GetOBBox3D()) {
			return zMax (zREAL(0.1F), visual->GetOBBox3D()->GetMinExtent()*0.9F);	// mindestens 0.1 mm! (safe gegenuber Datenproblemen)
		} else {
			return zMax (zREAL(0.1F), visual->GetBBox3D (). GetMinExtent()*0.9F);
		};
	} else
		return 1;
};

void zCCFASTCALL zCCollObjectBase::S_CalcGeneric_CollNormal_ContactPoint (const zCVob* vob0, const zCVob* vob1, zCCollisionReport &collReport)
{
	const zPOINT3&	center0		= vob0->GetBBox3DWorld().GetCenter();
	const zPOINT3&	center1		= vob1->GetBBox3DWorld().GetCenter();
	collReport.m_oContactPoint	= (center1 + center0) * zREAL(0.5F);
	collReport.m_oCollNormal0	= (center1 - center0).NormalizeApprox();
	collReport.m_oCollNormal1	= -collReport.m_oCollNormal0;
};

void zCCFASTCALL zCCollObjectBase::GetLargestBBox3DLocal(zTBBox3D &bbox3DLocalOut)
{
	// Den Praezisionsverlust der BBox-Transformationen kann man wahrscheinlich gut in Kauf nehmen:
	// Das Ergebnis dieser Berechnung wird nur fuer die SpeedBox Berechnung eingesetzt.
	if (!GetVob()->GetVisual())
	{
		// transformiere WorldSpace VobBox in den LocalSpace
		GetVob()->GetBBox3DWorld().Transform (GetVob()->GetOldTrafoObjToWorld().InverseLinTrafo(), bbox3DLocalOut);
	} else 
	{
		bbox3DLocalOut = GetVob()->GetVisual()->GetBBox3D();
		if (!GetVob()->GetVisual()->IsBBox3DLocal())
		{
			// transformiere WorldSpace VisualBox in den LocalSpace
			bbox3DLocalOut.Transform (GetVob()->GetOldTrafoObjToWorld().InverseLinTrafo(), bbox3DLocalOut);
		};
	};
};

// ============================================================================================================

void zCCollObjectBase::S_RegisterCollisionTestFuncs (zCCollisionDetector* collisionDetector)
{
	zERR_ASSERT(collisionDetector);

	#define REG_STATIC_TEST(  classA, classB, testFunc) collisionDetector->RegisterStaticIntersectionTest  (classA::S_GetCollObjClass(), classB::S_GetCollObjClass(), testFunc)
	#define REG_DYNAMIC_TEST( classA, classB, testFunc) collisionDetector->RegisterDynamicIntersectionTest (classA::S_GetCollObjClass(), classB::S_GetCollObjClass(), testFunc)

	// static tests
	REG_STATIC_TEST (zCCollObjectComplex	, zCCollObjectLevelPolys	, TestStatic_Complex_LevelPolys);
	REG_STATIC_TEST (zCCollObjectComplex	, zCCollObjectComplex		, TestStatic_Complex_Complex);
	REG_STATIC_TEST (zCCollObjectCharacter	, zCCollObjectCharacter		, TestStatic_Char_Char);

	// dynamic tests
	REG_DYNAMIC_TEST(zCCollObjectPoint		, zCCollObjectLevelPolys	, TestDynamic_Point_LevelPolys);
	REG_DYNAMIC_TEST(zCCollObjectPoint		, zCCollObjectComplex		, TestDynamic_Point_Complex);
	REG_DYNAMIC_TEST(zCCollObjectCharacter	, zCCollObjectBoxPassThrough, TestDynamic_XXX_BoxPassThrough);
	REG_DYNAMIC_TEST(zCCollObjectPoint		, zCCollObjectBoxPassThrough, TestDynamic_XXX_BoxPassThrough);
	REG_DYNAMIC_TEST(zCCollObjectProjectile	, zCCollObjectBoxPassThrough, TestDynamic_XXX_BoxPassThrough);
	REG_DYNAMIC_TEST(zCCollObjectProjectile	, zCCollObjectComplex		, TestDynamic_Point_Complex);
	REG_DYNAMIC_TEST(zCCollObjectProjectile	, zCCollObjectLevelPolys	, TestDynamic_Point_LevelPolys);
	REG_DYNAMIC_TEST(zCCollObjectProjectile	, zCCollObjectCharacter		, TestDynamic_Projectile_Char);
		
	#undef REG_STATIC_TEST
	#undef REG_DYNAMIC_TEST
};

// ============================================================================================================

/*
Phasen:
	a) Neue CollDet Infrastruktur komplett
	b) AIPlayer (Integration + Bugfixes)

TODO:
	x Abstandshalter ueber MDS justieren
	x Im KollTest: t=0 braucht i.A. nie getestet werden!!
	x TouchBox Funktionalitaet (CollDet, aber keine Resp)
	* CollObjectDef im zCVob-Archive (wie ablegen?)										=> fuer's erste NICHT im Archive,sondern per class-ctor
	* Char/Char Kollision (Capsules oder Ellipsoiden?)
	* CollDetector: statische Suche feintunen (Stepweiten, adaptiveCollStep, etc.),		=> was evtl. noch fehlt: binaere Feinsuche..
	* Speedbox sollte von dem CollObject gebildet werden (effizienter bei z.B. Point)	=> leider wird SpeedBox noch gegen Vob-WorldSpace Box getestet (bei char/char sieht's ineffizient aus..)
	* CollisionReports korrekt ausfuellen
	* alle Tests schreiben
	* zCVob::collisionObject Verwaltung
	* SubTree Abhaengigkeiten checken (EndMovement etc.) => CorrectTrafo()
	* CollisionReport Verwaltung
	* (Rest: SetHeading(),..)

	- Beim Kollisionstest den Fall Kollision bei t=0 evtl. gesondert nach oben melden
	  (in diesem Fall keine CollResp moeglich/noetig, keine weiteren Iterationen)
	- bei vergessenem EndMove() bei FrameEnde/Vob loeschen warnen?
	- MemPools? (collObjectComplex,..?)
	- Profile
	- Problemquelle: dynamische Tests sind nicht reflexiv! (=> TouchBox/Char, BBox-SweepTest hat time<0 geliefert)
	- Problem: zCModel Visuals
		- TraceRay bei Models mit SoftSkins????? (auch: animierte Model-Anteile..)
		- Complex vs. Complex Kollision derzeit nur auf WorldSpace AABB (=> Bett vs. Hocker...)

	- Magie-Kollision?
		- Problem bei zCCollObjectBoxPassThrough: keine Level und keine Complex Kollision
		- Problem bei zCCollObjectProjectile:
			- kein Volumen
			- es darf keine physikalische Response stattfinden (wie bei Pfeil etc., macht hier allein die AI)
			- (Gegner, die man haben will: Char, Complex, Level)

	- testen:
		* AutoLink testen
		- der statische Koll.Test beim Einfuegen in die Welt (=>Ulf)						=> TEST FEHLT NOCH
	  
	- zCAI Integration
	- AIPlayer Integration

	- zCCollisionObject::CollisionResponse(): evtl. sollte hier die Methode Gelegenheit habe, ein Vob. gegen den
	  kollidiert wird aus der otherListe zu loeschen.
	- CollectCollisionContext() pro Iteration

 Anpassungen:
	- geaenderte Namen ResetRotations(), SetHeading..()
	- anderes vob->SetCollDetType ()
	- ReportCollisionToAI				(const zCCollisionReport& collisionReport)
	- trafoObjToWorld ist nicht mehr der akkumulierte Zustand (nun auch wichtiger als trafo)
	- Test: mehrere moving Vobs zu Zeit erlaubt
	- zCVob::DetectCollision(mat)
	- Neue Files: zVobMove.cpp, zCollision*.*
	- (explicit zVEC3::zVEC3(const zREAL f))
*/