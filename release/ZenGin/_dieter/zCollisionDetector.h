/******************************************************************************** 
 
     $Workfile:: zCollisionDetector.h $                $Date:: 10.01.01 17:11   $
     $Revision:: 8                    $             $Modtime:: 6.01.01 19:17    $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Sexy Collision Detector, detects collisions between zCCollisionObjects.
   created       : 8.12.2000

 * $Log: /current_work/zengin_work/_Dieter/zCollisionDetector.h $
 * 
 * 8     10.01.01 17:11 Hildebrandt
 * 
 * 7     21.12.00 21:24 Hildebrandt
 * 
 * 6     20.12.00 3:03 Hildebrandt
 * 
 * 5     15.12.00 3:55 Hildebrandt
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
/// @version $Revision: 8 $ ($Modtime: 6.01.01 19:17 $)

// ============================================================================================================

#ifndef __ZCOLLISIONDETECTOR_H__
#define __ZCOLLISIONDETECTOR_H__

// declarations
class zCCollisionObject;
class zCCollisionObjectDef;

// ============================================================================================================

// CollisionReport baseClass
// These reports are expected to be in memory pools. Intersection tests grab report objects from a pool, fill 
// and hand out them out, when a collision occurs. But these handed out objects are never 'deleted' from the
// calling routines, instead each collision detection 'frame' the memory pools should be resetted.

class zCCollisionReport {
public:
	zREAL					m_fTimeStamp;
	zPOINT3					m_oContactPoint;
	zVEC3					m_oCollNormal0;
	zVEC3					m_oCollNormal1;
	zCCollisionObject*		m_poCollObject0;
	zCCollisionObject*		m_poCollObject1;

			 zCCollisionReport()	{ m_poCollObject0 = m_poCollObject1 = 0; };
	virtual ~zCCollisionReport()	{ m_poCollObject0 = m_poCollObject1 = 0; };
};

// ============================================================================================================

// collision detector for 'one moving at a time'
// weiss nichts von zCVobs, zCWorlds, zCBSP, etc.

class zCCollisionDetector {
public:
			 zCCollisionDetector();
	virtual ~zCCollisionDetector();

	virtual void	zCCFASTCALL		DetectCollisions						(zCCollisionObject*					movingCollObject, 
																			 const zCArray<zCCollisionObject*>& otherCollObjectList,
																			 zCArray<zCCollisionReport*>&		collReportList);
																			
	typedef zBOOL					(zTStaticIntersectionTest)				(zREAL timeStamp, 
																			 zCCollisionObject*  collObject0, const zMAT4& trafoObj0,
																			 zCCollisionObject*  collObject1, const zMAT4& trafoObj1,
																			 zCCollisionReport** ppoCollReport);	// ptr to ptr of collReport, zero: TestFunc should not return a report
	typedef zBOOL					(zTDynamicIntersectionTest)				(zCCollisionObject*  collObject0,		// dynamic: trafoOld=>trafoNew
																			 zCCollisionObject*  collObject1,		// static
																			 zCCollisionReport** ppoCollReport);
	virtual void	zCCFASTCALL		RegisterStaticIntersectionTest			(zCCollisionObjectDef*	class0, zCCollisionObjectDef*	class1, zTStaticIntersectionTest  *testFunc);
	virtual void	zCCFASTCALL		RegisterDynamicIntersectionTest			(zCCollisionObjectDef*	class0, zCCollisionObjectDef*	class1, zTDynamicIntersectionTest *testFunc);
	virtual zBOOL	zCCFASTCALL		CanCollide								(zCCollisionObjectDef*	class0, zCCollisionObjectDef*	class1);
																			
	// reusable pool of generic collisionReports							
	static zCCollisionReport*		S_GetNextFreeCollReport					();
	static zDWORD					S_GetCollisionDetectionFrameCtr			() { return s_iCollisionDetectorFrameCtr; };// this ctr is incremented each time DetectCollisions() is called

private:
	zTStaticIntersectionTest**		m_apStaticTestFuncMatrix;
	zTDynamicIntersectionTest**		m_apDynamicTestFuncMatrix;
#ifdef COMPILING_SPACER
	enum							{ zNUM_COLL_REPORTS = 64 };
#else
	enum							{ zNUM_COLL_REPORTS = 16 };
#endif
	static zDWORD					s_iCollisionDetectorFrameCtr;
	static int						s_iCurrentCollReport;
	static zCCollisionReport		s_aoCollReportList[zNUM_COLL_REPORTS];
	static void						S_ResetFreeCollReportList				();

	int								zCCFASTCALL	GetTestFuncIndex			(zCCollisionObjectDef* collClass0, zCCollisionObjectDef* collClass1);
	zTStaticIntersectionTest*		zCCFASTCALL	GetStaticTestFunc			(zCCollisionObjectDef* collClass0, zCCollisionObjectDef* collClass1);
	zTDynamicIntersectionTest*		zCCFASTCALL	GetDynamicTestFunc			(zCCollisionObjectDef* collClass0, zCCollisionObjectDef* collClass1);
	void							zCCFASTCALL	DoDynamicIntersectionTests	(zCCollisionObject*				movingCollObject,		// IN
																			 zCArray<zCCollisionObject*>&	otherCollObjectList,	// IN/OUT, collObjs that need static tests remain in that list
																			 zCArray<zCCollisionReport*>&	collReportList);		// OUT
	void							zCCFASTCALL	DoStaticIntersectionTests	(zCCollisionObject*				movingCollObject,		// IN
																			 zCArray<zCCollisionObject*>&	otherCollObjectList,	// IN/OUT, collObjs that need static tests remain in that list
																			 zCArray<zCCollisionReport*>&	collReportList);		// OUT

};

// ============================================================================================================

#endif