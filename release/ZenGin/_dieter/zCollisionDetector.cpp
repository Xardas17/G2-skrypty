/******************************************************************************** 
 
     $Workfile:: zCollisionDetector.c $                $Date:: 11.01.01 16:59   $
     $Revision:: 9                    $             $Modtime:: 11.01.01 16:59   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Collision Detector, detects collisions between zCCollisionObjects.
   created       : 8.12.2000

 * $Log: /current_work/zengin_work/_Dieter/zCollisionDetector.cpp $
 * 
 * 9     11.01.01 16:59 Hildebrandt
 * 
 * 8     11.01.01 15:38 Hildebrandt
 * 
 * 7     10.01.01 17:11 Hildebrandt
 * 
 * 6     21.12.00 21:24 Hildebrandt
 * 
 * 5     20.12.00 3:03 Hildebrandt
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
/// @version $Revision: 9 $ ($Modtime: 11.01.01 16:59 $)

// ============================================================================================================

#include <zCore.h>
#include <zTypes3D.h>

#include <zCollisionDetector.h>
#include <zCollisionObject.h>

// ============================================================================================================

zDWORD				zCCollisionDetector::s_iCollisionDetectorFrameCtr	= 0;
int					zCCollisionDetector::s_iCurrentCollReport			= 0;
zCCollisionReport	zCCollisionDetector::s_aoCollReportList				[zNUM_COLL_REPORTS];

// ctor, dtor

zCCollisionDetector::zCCollisionDetector()
{
	//
	int numCollClasses			= zCCollisionObjectDef::S_GetNum();

	// static testFunc table
	m_apStaticTestFuncMatrix	= zNEW(zTStaticIntersectionTest*) [numCollClasses*numCollClasses];
	memset						(m_apStaticTestFuncMatrix, 0, sizeof(zTStaticIntersectionTest*) * numCollClasses*numCollClasses);

	// dynamic testFunc table
	m_apDynamicTestFuncMatrix	= zNEW(zTDynamicIntersectionTest*) [numCollClasses*numCollClasses];
	memset						(m_apDynamicTestFuncMatrix, 0, sizeof(zTDynamicIntersectionTest*) * numCollClasses*numCollClasses);
};

zCCollisionDetector::~zCCollisionDetector()
{
	delete[] m_apStaticTestFuncMatrix ; m_apStaticTestFuncMatrix =0;
	delete[] m_apDynamicTestFuncMatrix; m_apDynamicTestFuncMatrix=0;
};

// Verwaltung

int zCCFASTCALL zCCollisionDetector::GetTestFuncIndex	(zCCollisionObjectDef* collClass0, 
														 zCCollisionObjectDef* collClass1)
{
	int numCollClasses	= zCCollisionObjectDef::S_GetNum();
	return collClass0->GetIndex()*numCollClasses + collClass1->GetIndex();
};

zCCollisionDetector::zTStaticIntersectionTest* zCCFASTCALL zCCollisionDetector::GetStaticTestFunc  (zCCollisionObjectDef* collClass0, 
																	 		   zCCollisionObjectDef* collClass1)
{
	return m_apStaticTestFuncMatrix [GetTestFuncIndex(collClass0, collClass1)];
};

zCCollisionDetector::zTDynamicIntersectionTest* zCCFASTCALL zCCollisionDetector::GetDynamicTestFunc  (zCCollisionObjectDef* collClass0, 
																				 zCCollisionObjectDef* collClass1)
{
	return m_apDynamicTestFuncMatrix [GetTestFuncIndex(collClass0, collClass1)];
};

void zCCFASTCALL zCCollisionDetector::RegisterStaticIntersectionTest (zCCollisionObjectDef* collClass0, 
																	  zCCollisionObjectDef* collClass1, 
																	  zTStaticIntersectionTest *testFunc)
{
	int testFuncIndex = GetTestFuncIndex(collClass0, collClass1);
	m_apStaticTestFuncMatrix[testFuncIndex] = testFunc;
};

void zCCFASTCALL zCCollisionDetector::RegisterDynamicIntersectionTest(zCCollisionObjectDef* collClass0, 
																	  zCCollisionObjectDef* collClass1, 
																	  zTDynamicIntersectionTest *testFunc)
{
	int testFuncIndex = GetTestFuncIndex(collClass0, collClass1);
	m_apDynamicTestFuncMatrix[testFuncIndex] = testFunc;
};

zBOOL zCCFASTCALL zCCollisionDetector::CanCollide (zCCollisionObjectDef*	class0, zCCollisionObjectDef* class1)
{
	return (GetDynamicTestFunc(class0, class1)!=0) || (GetStaticTestFunc(class0, class1)!=0);
};

void zCCollisionDetector::S_ResetFreeCollReportList()
{
	s_iCurrentCollReport = 0;
};

zCCollisionReport* zCCollisionDetector::S_GetNextFreeCollReport()
{
	if (s_iCurrentCollReport>=zNUM_COLL_REPORTS)
	{
		zERR_WARNING ("D: CD: generic zCCollisionReport pool too small!");
		s_iCurrentCollReport=0;
	};
	return &(s_aoCollReportList[s_iCurrentCollReport++]);
};

// ============================================================================================================

void zCCFASTCALL zCCollisionDetector::DoDynamicIntersectionTests (zCCollisionObject*			movingCollObject,
																  zCArray<zCCollisionObject*>&	otherCollObjectList,
																  zCArray<zCCollisionReport*>&	collReportList)
{
	// Sind dynamische CollisionTests anwendbar?
	// Liefert bei mehreren moeglich Kollisionen den EINEN, mit dem kleinsten timeStamp.
	// CollObjects, die getestet werden konnten, werden aus der 'otherCollObjectList' entfernt.

	zREAL timeNearest = zREAL(9999.0F);
	for (int i=0; i<otherCollObjectList.GetNum(); i++)
	{
		zCCollisionObject			*otherCollObject= otherCollObjectList[i]; 
		zTDynamicIntersectionTest	*dynamicTestFunc= GetDynamicTestFunc(movingCollObject->GetCollObjClass(), otherCollObject->GetCollObjClass());
		if (dynamicTestFunc)
		{
			zCCollisionReport *freeCollisionReport	= 0;
			if ((*dynamicTestFunc)(movingCollObject,
								   otherCollObject ,
								   &freeCollisionReport)
				)
			{
				// Ist diese Intersection naeher als die bisherigen?

				// [EDENFELD] 1.09 Nullptr Crash behoben. Laut [BENDLIN] kann ein Crash bei niedrigen Frameraten passieren
				if (freeCollisionReport)
				if (freeCollisionReport->m_fTimeStamp<timeNearest)
				{
					if (timeNearest<zREAL(9999.0F))
					{
						// ein bereits registrierten Report mit groesserem timeStamp wieder entfernen (den letzte also)
						collReportList.RemoveIndex			(collReportList.GetNum()-1);
					};
					// Rest des Reports ausfuellen & registrieren
					freeCollisionReport->m_poCollObject0	= movingCollObject;
					freeCollisionReport->m_poCollObject1	= otherCollObject;
					collReportList.Insert					(freeCollisionReport);

					//
					timeNearest	= freeCollisionReport->m_fTimeStamp;
				};
			};

			// ein dynamischer Test fuer dieses Objekt existiert und wurde benutzt => keine weitere Bearbeitung mehr noetig
			otherCollObjectList.RemoveIndex			(i);
			--i;
		};
	};
};

void zCCFASTCALL zCCollisionDetector::DoStaticIntersectionTests (zCCollisionObject*				movingCollObject,
																 zCArray<zCCollisionObject*>&	otherCollObjectList,
																 zCArray<zCCollisionReport*>&	collReportList)
{
	// timeNearest: der frueheste Zeitpunkt, an dem bereits eine Intersection erkannt wurde.
	// Es wird erwartet, dass die frueheste erkannte Intersection (falls vorhanden) im CollReportList Array an erster
	// Stelle hereingereicht wird.
	const zREAL	timeNearest		= (collReportList.GetNum()>0) ? collReportList[0]->m_fTimeStamp : zREAL(1.0F);

	//
	zVEC3		transStep;
	zREAL		transStepLen;
	zREAL		timeStep;
	zREAL		time			= 0.0F;

	// calculates: transStep, transStepLen, timeStep
	{
		zVEC3		trans		= movingCollObject->GetTrafoNew().GetTranslation() - movingCollObject->GetTrafoOld().GetTranslation();
		zREAL		transLen	= trans.Length();
		zREAL		maxStepSize	= movingCollObject->GetAdaptiveStepSize();	// FIXME
		if (maxStepSize<=0)			maxStepSize= 4.0F;		// kein else
		if (maxStepSize>transLen)	maxStepSize= transLen;

		if ((transLen<=0) || (transLen<=maxStepSize))	timeStep= 1; else
														timeStep= maxStepSize / transLen;				// Bruchteil von 1
		transStepLen			= transLen	* timeStep;
		transStep				= trans		* timeStep;
	};

	// Rot-Interpol. nur, wenn unbed. noetig 
	zCQuat		rotStart, rotEnd;
	if (movingCollObject->GetTrafoHintRotation())
	{
		rotStart.Matrix4ToQuat (movingCollObject->GetTrafoOld());
		rotEnd	.Matrix4ToQuat (movingCollObject->GetTrafoNew());
	};

	// FIXME: evtl. koennte man hier noch Matrix-Copys vermeiden: z.B. wenn der timeStep so klein ist, dass
	//        nur bei t=1 getestet werden soll. Dann kann statt der currentTrafo gleich die trafoNew benutzt werden

	//
	zBOOL		currentTrafoInited	= FALSE;								// die currentTrafo wird lazy mit der trafoOld initialisiert
	zMAT4		currentTrafo;
	zBOOL		searching			= TRUE;
	zREAL		timeLastSafe		= 0;									// letzter Zeitpunkt t, der garantiert ohne Kollision ist (= tc beim Beenden)

	do {
		// Bei einer gefundenen Collision bei diesem t das deltaT verkleinern und feiner suchen?
//		zBOOL searchFinerIfIntersection	= (transStepLen>=5.0F);
		zBOOL searchFinerIfIntersection	= FALSE;
		zBOOL intersectionFound			= FALSE;

		// Der Zeitpunkt t=0 gilt als im letzten Timeframe getestet, und braucht (aus effizienzgruenden) 
		// hier nicht nocheinmal bearbeitet werden.
		if (time>0)
		{
			zERR_ASSERT (currentTrafoInited);
			for (int i=0; i<otherCollObjectList.GetNum(); i++)
			{
				zCCollisionObject			*otherCollObject		= otherCollObjectList[i];
				zTStaticIntersectionTest	*staticTestFunc			= GetStaticTestFunc(movingCollObject->GetCollObjClass(), otherCollObject->GetCollObjClass());
				zCCollisionReport			*freeCollisionReport	= 0;			
				if ((staticTestFunc) &&
					(*staticTestFunc)(time,
									  movingCollObject, currentTrafo,
									  otherCollObject , otherCollObject->GetTrafoOld(),
									  (searchFinerIfIntersection) ? 0 : &freeCollisionReport)
					)
				{
					if (time==0)
					{
						zERR_MESSAGE(5,0,"D: intersection at t=0!");
					};
					// weitersuchen?
					if (!searchFinerIfIntersection && freeCollisionReport)
					{
						// Suche beenden, Genauigkeit ist ausreichend
						// Rest des Reports ausfuellen & registrieren
						freeCollisionReport->m_fTimeStamp		= timeLastSafe;
						freeCollisionReport->m_poCollObject0	= movingCollObject;
						freeCollisionReport->m_poCollObject1	= otherCollObject;
						collReportList.Insert					(freeCollisionReport);
						searching								= FALSE;
					};
					intersectionFound			= TRUE;
				};
			};
		};

		if (intersectionFound) 
		{
			if (!searchFinerIfIntersection)
			{
				// Suche mit Collision bei tc beenden, Genauigkeit ist ausreichend
				// tc = timeLastSafe (annaeherungsweise)
				searching				= FALSE;
				int warnAgrl;
//				zERR_ASSERT (collReportList.GetNum()>0);
				break;	// Abbruch mit Kollision!
			} else 
			{
				// einen halbierten Schritt zurueckgehen
				timeStep				*= zREAL(0.5F);
				transStep				*= zREAL(0.5F);
				transStepLen			*= zREAL(0.5F);

				time					-= timeStep;			
				currentTrafo.Translate	(-transStep);
				if (movingCollObject->GetTrafoHintRotation())
				{
					zCQuat quat;
					quat.Lerp			(time, rotStart, rotEnd);
					quat.QuatToMatrix4	(currentTrafo);
				};
			};
		} else
		{
			// udpate
			if (time>=timeNearest)
			{
				searching				= FALSE;
			} else 
			{
				timeLastSafe			= time;
				time					+= timeStep;
				// Aus Stabilitaetsgruenden, damit bei t=1 auch wirklich der korrekte Zustand getestet wird..
				if (time>=0.99F)
				{
					time				= 1.0F;
					if ((movingCollObject->GetTrafoHintRotation()) || (!currentTrafoInited))
					{
						currentTrafo		= movingCollObject->GetTrafoNew();
						currentTrafoInited	= TRUE;
					} else 
					{
						currentTrafo.SetTranslation (movingCollObject->GetTrafoNew().GetTranslation());
					};
				} else 
				{
					if (!currentTrafoInited)
					{
						// layz initialisierung der CurrentTrafo
						currentTrafo		= movingCollObject->GetTrafoOld();	
						currentTrafoInited	= TRUE;
					};
					currentTrafo.Translate	(transStep);
					if (movingCollObject->GetTrafoHintRotation())
					{
						zCQuat quat;
						quat.Lerp			(time, rotStart, rotEnd);
						quat.QuatToMatrix4	(currentTrafo);
					};
				};
			};
		};
	} while (searching);
};

void zCCFASTCALL zCCollisionDetector::DetectCollisions	(zCCollisionObject*					movingCollObject, 
														 const zCArray<zCCollisionObject*>& otherCollObjectListInput,
														 zCArray<zCCollisionReport*>&		collReportList)
{
	//
	++s_iCollisionDetectorFrameCtr;
	collReportList.EmptyList	();
	S_ResetFreeCollReportList	();

	// Das sich bewegende Objekt darf auch selbststaendig nach eigenen/speziellen Kollisionen suchen, 
	// auch, wenn keine otherCollObjectListInput hereingegeben worden sind.
	// (gleichzeitig ein per-moving-frame-Callback)
	movingCollObject->DetectCollisionsSelf (otherCollObjectListInput, collReportList);

	// Gibt es Objekte, gegen die getestet werden soll?
	if (!otherCollObjectListInput.IsEmpty())
	{
		// Kopie der other-Liste erzeugen (darauf wird gearbeitet)
		zCArray<zCCollisionObject*> otherCollObjectList	= otherCollObjectListInput;

		// Sind dynamische CollisionTests anwendbar?
		// (otherCollObjectList wird in diesem Fall ausgeduennt)
 		DoDynamicIntersectionTests (movingCollObject, otherCollObjectList, collReportList);

		// Noch weitere statische Tests noetig?
		if (otherCollObjectList.GetNum()>0)
		{
			int numReportsBefore		= collReportList.GetNum();
			DoStaticIntersectionTests	(movingCollObject, otherCollObjectList, collReportList);

			// Falls ein dyn. Test eine Intersection hinter dem ersten stat. Test liefert, wird
			// der entsprechende Report wieder entfernt
			if ((numReportsBefore>0) && (collReportList.GetNum()>numReportsBefore))
			{
				if (collReportList[0]->m_fTimeStamp>collReportList[numReportsBefore]->m_fTimeStamp)
					collReportList.RemoveIndex (0);
			};
		};
	};

	// Eine Kollision liegt beim Verlassen vor, wenn das 'collReportList' Array nicht leer ist.

	// TEST_MUELL
//#ifdef DEBUG_HILDEBRANDT
#if 0
	if (collReportList.GetNum()>0)
	{
		zerr.Message ("D: Collision, num:"+zSTRING(collReportList.GetNum())+", time: "+zSTRING(collReportList[0]->m_fTimeStamp));

		for (int i=0; i<collReportList.GetNum(); i++)
		{
			if (collReportList[0]->m_fTimeStamp!=collReportList[i]->m_fTimeStamp)
				zerr.Message ("D: ungleiche timeStamps in der Report-Liste!");
		};
	};
#endif
};

// ============================================================================================================
