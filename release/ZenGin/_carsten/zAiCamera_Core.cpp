
#include "zcore.h"
#include "zTypes3d.h"
#include "zKBSplines.h"
#include "zAICamera.h"
#include "zAICamera_Movement.h"
#include "zAICamera_Core.h"
#include "zDbgTools.h"
#include "zModel.h"
#include "zvob.h"
#include "zworld.h"
#include "zinput.h"
#include "zRayCache.h"
#include "zVobMisc.h"

#pragma warning( disable : 4244 )  
#ifdef DEBUG_EDENFELD
	//#define SHOW_SEARCHRESULTS
#endif

float numSCsSearched = 0;
float numSCsCached  = 0;

static zCRayCache rayCache1;
static zCRayCache rayCache2;
static zCRayCache rayCache3;
static zCRayCache rayCache4;

//TODO: 
// - ai ideen: 
//		-nach ausweichmöglichkeit mit min score suchen. falls nicht gefunden, den besten davon nehmen
//		 ab bestScore sofort benutzen
//		-ständig nach besserem Score suchen (über mehrere Frames verteilen? dabei die qualität der einzelnen sc searchs erhöhen?)
// - Zur Idealcone streben. Wenn derzeitige Cameraposition nicht sichtbar, erst zur letzten gültigen
// target position streben. ist das target von der letzen gültigen target position _nicht_ sichtbar, muss ein 
// safe mechanismus erfolgen 
// 3 umschau kamera v2
// 3 keyboard dist einstellbar. evtl. auch trägheit
// neue modi: cammodabyss
// kampf gegen mehrere gegner: alle targets von aussen reingeben und in der core ai mitgewichten
// - caching: die letzen n guten ausweichmöglickkeiten abspeichern und ggf. wiederverwenden
// lerpmode spline/arc implementieren ?
// future pos ?
// - GetPoseOfHEading mit offsetrotation in IsPointValid berücksichtigen
// zPLAYER_BEAMED muss die Wasserkamera reseten (es sei denn AIPlayer->waterlevel>0)
// ai für mover, (los cross problem) etc.
// - anpassung an bboxen noch nicht 100%ig
// - zPLAYER_BEAMED ! immer noch hakelig
// distanzbasierter easevelo. sieht ok aus. unit testing


// *********************************************************************************
// **							static global funcs
// *********************************************************************************

const	float MIN_EVASION_SCORE		= 0.000001F;
const	float SHOULDERCAM_SCORE		= 0.00001F;
float	CAMSPHERE_DIAMETER			= 40;		// 30 cm durchmesser

const float VOB_IGNORE_MAX_EXTEND		= 10;			// alle vobs mit grösster bboxedgelänge < 20 cm werden immer ignoriert
const float VOB_IGNORE_MIN_EXTEND		= 5;			// alle vobs mit kleinster bboxedgelänge< 20 cm werden immer ignoriert (nur wenn alpha)
const float VOB_IGNORE_MIN_EXTEND_RATIO = 20;
const float VOB_LOWEST_MINEXTEND		= 12;

zTPoseFailReason failReasonDummy;

static zBOOL CanIgnoreVob(const zCVob* testVob)
{
	if (!testVob) return FALSE;

	// so nun testen welche vobs ignoriert werden können
	// a) visual hat alpha und unter einem bestimmten wert
	// b) min extend unter extrem niedrigem wert + alpha testing an (zäune)
	// c) verhältnis min/max extend ab 1:10 + min extend unter der grenze (lampen)
	// d) max extend unter einer grenze (kleinere items/vobs)

	// a) 
	if (zDYNAMIC_CAST<zCTriggerBase>(testVob)) return FALSE;

	if (testVob->GetVisualAlphaEnabled() && testVob->GetVisualAlpha()<0.3f) 
	{
		return TRUE;
	}

	// b)
	zBOOL vobAlpha  = testVob->GetVisual() ? testVob->GetVisual()->GetAlphaTestingEnabled() : FALSE;
	zREAL minExtend = testVob->GetBBox3DWorld().GetMinExtent();
	if (minExtend<VOB_IGNORE_MIN_EXTEND && vobAlpha) 
	{
		return TRUE;
	}

	// c)
	zREAL maxExtend = testVob->GetBBox3DWorld().GetMaxExtent();
	if ( (8*minExtend<maxExtend) && minExtend<VOB_IGNORE_MIN_EXTEND_RATIO && minExtend>VOB_LOWEST_MINEXTEND) 
	{
		return TRUE;
	}


	// d)
	if ( maxExtend<VOB_IGNORE_MAX_EXTEND) 
	{
		return TRUE;
	}

	return FALSE;

};

static zBOOL AI_FindEvasionSphere(const zSEvasionSearchDesc &searchDesc)
{
	return zCPathSearch::GetSearch()->SphereSearch(searchDesc);
}
static zBOOL AI_FindEvasionSwitch(const zSEvasionSearchDesc &searchDesc)
{
	return zCPathSearch::GetSearch()->SwitchSearch(searchDesc);
}
static zBOOL AI_FindEvasionShoulderCam(const zSEvasionSearchDesc &searchDesc)
{
	return zCPathSearch::GetSearch()->ShoulderSearch(searchDesc);
}

static zBOOL AI_FindEvasionPanic(const zSEvasionSearchDesc &searchDesc)
{
	return zCPathSearch::GetSearch()->PanicSearch(searchDesc);
}

static int CompareRanges( const void *e1, const void *e2 )
{
	static int compResult;
	const float EPS_EQ_RANGE = 0.001F;
	compResult = (*(zCSphereCoordsCache::zSRangeSphereCoord **)e1)->range - (*(zCSphereCoordsCache::zSRangeSphereCoord **)e2)->range ;
	return (zAbs(compResult) <= EPS_EQ_RANGE) ? 0 : compResult ;
}

static int CompareAzis( const void *e1, const void *e2 )
{
	static int compResult;
	const float EPS_EQ_AZI = 0.001F;
	compResult=(*(zCSphereCoordsCache::zSAziSphereCoord **)e1)->azi - (*(zCSphereCoordsCache::zSAziSphereCoord **)e2)->azi;
	return (zAbs(compResult) <= EPS_EQ_AZI) ? 0 : compResult ;
}

static int CompareElevs( const void *e1, const void *e2 )
{
	static int compResult;
	const float EPS_EQ_ELEV = 0.001F;
	compResult = (*(zCSphereCoordsCache::zSElevSphereCoord **)e1)->elev - (*(zCSphereCoordsCache::zSElevSphereCoord **)e2)->elev;
	return (zAbs(compResult) <= EPS_EQ_ELEV) ? 0 : compResult ;
}

// *********************************************************************************
// **							zCPathSearch implementations
// *********************************************************************************
// constructor
zCPathSearch::zCPathSearch() 
/*:
	   moveTracker(zCMovementTracker::GetTracker())*/
{
	POISphere.center	  = zVEC3(0,0,0);
	POISphere.radius	  = 0;
	camVob				  = 0;
	target				  = 0;
	world				  = 0;
	collisionEnabled	  = TRUE;
	memset((void*)&lastSearchState,0,sizeof(lastSearchState));
	memset((void*)&bestSearchState,0,sizeof(lastSearchState));
	ignoreSearchFlags	  = 0;
	moveTracker			  = zCMovementTracker::GetTracker();
	searchOptions.SetDefaults();
	searchCache.aziCoords.SetCompare(CompareAzis);
};

void	zCPathSearch::CamVobChanged			()								
{ 
	camVob = camai->camVob;		
	if (!camVob) return;
	world  = camVob->GetHomeWorld();
	if (world == NULL) zERR_FAULT("C: zCPathSearch::CamVobChanged(). HomeWorld == 0");
};
void	zCPathSearch::TargetChanged			()								
{ 
	target = camai->target;		
};
void	zCPathSearch::SetAICamera			(zCAICamera* camera)			
{ 
	camai = camera;				
};


zBOOL zCSphereCoordsCache :: GetSphereCoordLazy(const float &azi, const float &elev, const float &range,zSPathSearchState_Internal*&cacheState)
{
	// FIXME: Höllen Speicher alloc Alarm!
	static zSAziSphereCoord		aziSearch;
	static zSElevSphereCoord	elevSearch;
	static zSRangeSphereCoord	rangeSearch;
	aziSearch.azi		= azi;
	elevSearch.elev		= elev;
	rangeSearch.range	= range;


	int aziIndex = aziCoords.Search(&aziSearch);
	if (aziIndex>=0)
	{
		int elevIndex = aziCoords[aziIndex]->elevCoords.Search(&elevSearch);
		if (elevIndex>=0)
		{
			int rangeIndex = aziCoords[aziIndex]->elevCoords[elevIndex]->rangeCoords.Search(&rangeSearch);
			if (rangeIndex>=0)
			{
				cacheState = &aziCoords[aziIndex]->elevCoords[elevIndex]->rangeCoords[rangeIndex]->searchState;			// gibts schon
				return TRUE;
			}

			zSRangeSphereCoord *rc = zNEW(zSRangeSphereCoord); 
			rc->range	= range;
			aziCoords[aziIndex]->elevCoords[elevIndex]->rangeCoords.InsertSort(rc);
			cacheState = &rc->searchState;
			cacheState->foundPos	= zCMovementTracker::GetTracker()->CalcAziElevRangeApprox(azi,elev,range);
			cacheState->maxRange	= aziCoords[aziIndex]->elevCoords[elevIndex]->maxRange;
		}
		else
		{
			zSElevSphereCoord  *ec = zNEW(zSElevSphereCoord);  
			ec->rangeCoords.SetCompare(CompareRanges);
			ec->elev	= elev; 
			zSRangeSphereCoord *rc = zNEW(zSRangeSphereCoord); 			
			rc->range	= range;
			ec->rangeCoords.InsertSort(rc);

			aziCoords[aziIndex]->elevCoords.InsertSort(ec);
			cacheState = &rc->searchState;

			cacheState->foundPos	= zCMovementTracker::GetTracker()->CalcAziElevRangeApprox(azi,elev,range);
			zVEC3 distTraceRay		= (cacheState->foundPos-zCMovementTracker::GetTracker()->GetPlayerPos());
			float testDist			= (zCAICamera::GetCurrent()->GetMaxRange()*100)+(CAMSPHERE_DIAMETER/2);
			zCWorld *homeWorld		= zCAICamera::GetCurrent()->GetVob()->GetHomeWorld();

			zCAICamera::GetCurrent()->raysCasted++;
			if (homeWorld->TraceRayNearestHit(zCMovementTracker::GetTracker()->GetPlayerPos(),distTraceRay.NormalizeApprox()*testDist,zCAICamera::GetCurrent()->GetTarget(),standardTraceFlags)	&& 	!CanIgnoreVob(homeWorld->traceRayReport.foundVob))	
				ec->maxRange = MAX(1,(homeWorld->traceRayReport.foundIntersection-zCMovementTracker::GetTracker()->GetPlayerPos()).Length2());
			else 
				ec->maxRange= testDist*testDist;

			cacheState->maxRange = ec->maxRange;
		};
	}
	else
	{
		zSAziSphereCoord*   ac	=	zNEW(zSAziSphereCoord);	
		zSRangeSphereCoord* rc	=	zNEW(zSRangeSphereCoord);	
		zSElevSphereCoord*  ec	=	zNEW(zSElevSphereCoord);	
		ac->azi					= azi;
		ec->elev				= elev;		
		rc->range				= range;
		ac->elevCoords .SetCompare(CompareElevs);
		ec->rangeCoords.SetCompare(CompareRanges);
		
		aziCoords.InsertSort(ac);
		ac->elevCoords.InsertSort (ec);
		ec->rangeCoords.InsertSort(rc);
		
		cacheState = &rc->searchState;

		cacheState->foundPos	= zCMovementTracker::GetTracker()->CalcAziElevRangeApprox(azi,elev,range);
		zVEC3 distTraceRay		= (cacheState->foundPos-zCMovementTracker::GetTracker()->GetPlayerPos());
		float testDist			= (zCAICamera::GetCurrent()->GetMaxRange()*100)+(CAMSPHERE_DIAMETER/2);
		zCWorld *homeWorld		= zCAICamera::GetCurrent()->GetVob()->GetHomeWorld();

		zCAICamera::GetCurrent()->raysCasted++;
		if (homeWorld->TraceRayNearestHit(zCMovementTracker::GetTracker()->GetPlayerPos(),distTraceRay.NormalizeApprox()*testDist,zCAICamera::GetCurrent()->GetTarget(),standardTraceFlags)	&& !CanIgnoreVob(homeWorld->traceRayReport.foundVob))	
			ec->maxRange = MAX(1,(homeWorld->traceRayReport.foundIntersection-zCMovementTracker::GetTracker()->GetPlayerPos()).Length2());
		else 
			ec->maxRange= testDist*testDist;

		cacheState->maxRange= ec->maxRange;
	};

	return FALSE;
};

void zCSphereCoordsCache :: GetBestScoredSearch(zREAL &azi,zREAL &elev,zREAL &range,zSPathSearchState_Internal*&cacheState)
{
	float bestAziIndex, bestElevIndex, bestRangeIndex;
	float maxScore = -1;

	for (int a=0; a<aziCoords.GetNum(); a++)
	{
		for (int e=0; e<aziCoords[a]->elevCoords.GetNum(); e++)
		{
			for (int r=0; r<aziCoords[a]->elevCoords[e]->rangeCoords.GetNum(); r++)
			{
				cacheState = &aziCoords[a]->elevCoords[e]->rangeCoords[r]->searchState;
				if (cacheState->totalScore>maxScore)
				{
					bestAziIndex  = a; 
					bestElevIndex = e; 
					bestRangeIndex= r;
					maxScore	  = cacheState->totalScore;
				}
			}
		}
	}

	zERR_ASSERT(maxScore>-1);
	azi			= aziCoords[bestAziIndex]->azi;
	elev		= aziCoords[bestAziIndex]->elevCoords[bestElevIndex]->elev;
	range		= aziCoords[bestAziIndex]->elevCoords[bestElevIndex]->rangeCoords[bestRangeIndex]->range;
	cacheState	= &aziCoords[bestAziIndex]->elevCoords[bestElevIndex]->rangeCoords[bestRangeIndex]->searchState;
};

zCSphereCoordsCache::zCSphereCoordsCache()
{
};

zCSphereCoordsCache::~zCSphereCoordsCache()
{
	DeleteList();
};


void zCSphereCoordsCache :: DeleteList		  ()
{
	numSCsCached	= 0;
	numSCsSearched  = 0;

	for (int a=aziCoords.GetNum()-1; a>=0; a--)
	{
		for (int e=aziCoords[a]->elevCoords.GetNum()-1; e>=0; e--)
		{
			for (int r=aziCoords[a]->elevCoords[e]->rangeCoords.GetNum()-1; r>=0; r--)
			{
				delete aziCoords[a]->elevCoords[e]->rangeCoords[r];
				aziCoords[a]->elevCoords[e]->rangeCoords.RemoveIndex(r);
			}
			delete aziCoords[a]->elevCoords[e];
			aziCoords[a]->elevCoords.RemoveIndex(e);
		}
		delete aziCoords[a];
		aziCoords.RemoveIndex(a);
	}
};


zSPathSearchResult*	zCPathSearch::GetReport	()
{ 
	static zSPathSearchResult theReport; 
	return &theReport;	
};

// interface aicam/pathsearch
zCPathSearch* zCPathSearch::GetSearch	()
{ 
	static zCPathSearch theSearch; 
	return &theSearch;	
};

// zCPathSearch::SphereSearch
// universal camera evasion search. 
// search boundaries are given in spherical coordinates
// azimuth, elevation and range sequence can also vary
// the deepness of each sphere segment search can be adjusted with the parameter quality 

zBOOL zCPathSearch::SphereSearch(const zSEvasionSearchDesc &searchDesc)
{	
	D_Print("AI Sphere");

	struct zSSphereCoordsSearch
	{
		zREAL	start;
		zREAL*	end;
		zREAL	sign;
		zREAL	step;
		int		iterator;
	};


	// reset the last search state
	bestSearchState.bestLerpMode = zPATH_LERP_NONE;
	int totalSearchIterations    = 0;


	// walk through all sphere segments

	for (int i=0; i<searchDesc.sphereSearchList.GetNumInList(); i++)
	{
		// get the search options of this sphere segment
		zSEvasionSearchDesc::zSEvasionSearchOptions opts = searchDesc.sphereSearchList[i];
		zSSphereCoordsSearch sc[3];				// (one index for azi,elev and range)

		const float distAzi				= zAbs(opts.scEnd[AZI]	-opts.scStart[AZI]	);				
		const float distElev			= zAbs(opts.scEnd[ELEV]	-opts.scStart[ELEV]	);					
		const float distRange			= zAbs(opts.scEnd[RANGE]-opts.scStart[RANGE]);					
		const float MAX_RANGE			= 400;
		const float MAX_AZI				= 180;
		const float MAX_ELEV			= 90 + 60;								// (min+max elev)
		const float MAX_RANGE_STEP		= (10 * (distRange	/	MAX_RANGE)) + 1;		// maximale schritte bei MAX_RANGE Distanzsuche
		const float MAX_AZI_STEP		= (8 * (distAzi	/	MAX_AZI	)) + 1;		// maximale schritte bei MAX_AZI   Seitenwinkelsuche
		const float MAX_ELEV_STEP		= (8 * (distElev	/	MAX_ELEV)) + 1;		// maximale schritte bei MAX_ELEV  Höhenwinkelsuche

		
		// aktuelle  suche initialisieren. hole sc grenzen aus den optionen für dieses segment
		bestSearchState.startAzi		= opts.scStart	[AZI];
		bestSearchState.startElev		= opts.scStart	[ELEV];
		bestSearchState.startRange		= opts.scStart	[RANGE];
		bestSearchState.endAzi			= opts.scEnd	[AZI];
		bestSearchState.endElev			= opts.scEnd	[ELEV];
		bestSearchState.endRange		= opts.scEnd	[RANGE];

		// setup the sc array, so that the sequence ptr. are set to the correct variables
		// in the lastSearch struct
		zERR_ASSERT(opts.scSequence.Length()==3);

		for (int c=0; c<3; c++)
		{
			if		(opts.scSequence[c] == 'A')
			{
				sc[c].start		= bestSearchState.startAzi;
				sc[c].end		= &bestSearchState.endAzi;
				sc[c].sign		= opts.scSign[AZI];
				float dist		= zAbs(*sc[c].end-sc[c].start);
				sc[c].iterator	= MAX(1,opts.scQuality[AZI]*MAX_AZI_STEP)+1;
				sc[c].step		= dist/sc[c].iterator;
			}
			else if (opts.scSequence[c] == 'E')
			{
				sc[c].start		= bestSearchState.startElev;
				sc[c].end		= &bestSearchState.endElev;
				sc[c].sign		= opts.scSign[ELEV];
				float dist		= zAbs(*sc[c].end-sc[c].start);
				sc[c].iterator	= MAX(1,opts.scQuality[ELEV]*MAX_ELEV_STEP)+1;
				sc[c].step		= dist/sc[c].iterator;
			}
			else if (opts.scSequence[c] == 'R')
			{
				sc[c].start		= bestSearchState.startRange;
				sc[c].end		= &bestSearchState.endRange;
				sc[c].sign		= opts.scSign[RANGE];
				float dist		= zAbs(*sc[c].end-sc[c].start);
				sc[c].iterator	= MAX(1,opts.scQuality[RANGE]*MAX_RANGE_STEP)+1;
				sc[c].step		= dist/sc[c].iterator;
			}
			else zERR_ASSERT(1!=1);		// scSequence must be one of "AER","ARE","ERA","EAR","RAE","REA"
		}

		// now try to find the best evasion in this sphere segment
		int it2 = sc[2].iterator;
		for (*sc[2].end = sc[2].start; it2-- >= 0; *sc[2].end += sc[2].sign*sc[2].step)
		{
			int it1 = sc[1].iterator;
			for (*sc[1].end = sc[1].start; it1-- >= 0; *sc[1].end += sc[1].sign*sc[1].step)
			{
				int it0 = sc[0].iterator;
				for (*sc[0].end = sc[0].start; it0-- >= 0; *sc[0].end += sc[0].sign*sc[0].step)
				{

					totalSearchIterations++;
					int skipCycle = 1;
						
					// score dieses gefundenen auswegs ermitteln
					// bei geringer distanz können die seiten und höhenwinkel checks wesentlich gröber ausfallen
					// bei hohem höhenwinkel können die seitenwinkel checks wesentlich gröber ausfallen
					if ( (it0 != -1) && (it1!=-1) && (it2!=-1) ) // end scs müssen auf jeden fall erreicht werden
					{
						skipCycle = Lerp( MIN(1,bestSearchState.endRange/MAX_RANGE), 3,1);
						skipCycle+= Lerp( MIN(1,zAbs(bestSearchState.endElev)/90.0F), 0,3);
						if (totalSearchIterations % skipCycle) continue;
					}

					// score dieses gefundenen auswegs ermitteln
					CalcStateScores(bestSearchState);

					if (bestSearchState.totalScore>=searchOptions.bestScore)
					{
						bestSearchState.lerpModes		   |= bestSearchState.bestLerpMode;
						bestSearchState.bestAzi				= bestSearchState.endAzi;
						bestSearchState.bestElev			= bestSearchState.endElev;
						bestSearchState.bestRange			= bestSearchState.endRange;
#ifdef DEBUG_EDENFELD
						bestSearchState.sphereSearchName	= searchDesc.searchName;
						bestSearchState.sphereSearchSegment = opts.scName + zSTRING("(SEQ: ") + opts.scSequence + zSTRING(")");
#endif
						return TRUE;
					}
				};
			}
		}
	}

	return FALSE;
}

zBOOL zCPathSearch::SwitchSearch(const zSEvasionSearchDesc &searchDesc)
{
	return TRUE;
}

zBOOL zCPathSearch::ShoulderSearch(const zSEvasionSearchDesc &searchDesc)
{
	D_Print("AI Shoulder");
	static zSPathSearchState_Internal *cachedState;

	bestSearchState.bestLerpMode		= zPATH_LERP_CUSTOM;
	bestSearchState.totalScore			= 0;
	bestSearchState.trafoCamToWorld		= moveTracker->GetShoulderCamMat();

	int tmpFlags = searchOptions.searchFlags;
	// während der ai suche auf das player mesh verzichten
	// drawbacks: die ai findet keine positionen, in denen das ganze mesh gesehen wird.
	// besser: sichtbarkeit des players in der core suche mitgewichten
	tmpFlags &= ~zPATHSEARCH_USE_PLAYER_MESH; 
	//tmpFlags &= ~zPATHSEARCH_INCLUDE_CAM_CHECK;				// FIXME: An Ecken gibts Probs. Besser: Waypoints benutzen
	tmpFlags &= ~zPATHSEARCH_INCLUDE_NEARWALL_CHECK; 
	
	zTPoseFailReason failReason;
	zPOINT3 shoulderPos = bestSearchState.trafoCamToWorld.GetTranslation();

	bestSearchState.bestAzi				= SHOULDERCAM_AZI;
	bestSearchState.bestElev			= SHOULDERCAM_ELEV;
	bestSearchState.bestRange			= SHOULDERCAM_RANGE+zCAICamera::GetCurrent()->GetNpcDistOffset();
	bestSearchState.totalScore			= SHOULDERCAM_SCORE;
	bestSearchState.sphereSearchName	= searchDesc.searchName;
	bestSearchState.sphereSearchSegment	= "Shoulder";

	
	if (!IsPointValid(shoulderPos,tmpFlags,failReason)) 
	{
		// schultercamera position kann prinzipiell erreicht werden, aber 
		// es besteht keine sichtverbindung dorthin
		if (failReason == zFAILREASON_PLAYER_INVISIBLE) return FALSE;
		if (failReason == zFAILREASON_CAM_INVISIBLE)
		{
			// schauen ob a): Der letzte Target Waypoint gesehen werden kann und b) das Target
			// vom letzten Waypoint gesehen werden kann. Wenn ja: Strebe zum letzten Target Waypoint.
			// wenn nein: Ein SWITCH zur Schultercamera (oder besser: mit AdjustCenterSphere das getroffene
			// poly ermitteln, und dorthin switchen
			zPOINT3 lastValidTargetPos =  moveTracker->GetLastValidWayPoint(zCMovementTracker::zWAYPOINT_HEAD);
			if ( LineOfSight(camVob->GetPositionWorld(),  lastValidTargetPos) &&
				 LineOfSight(moveTracker->GetPlayerPos(), lastValidTargetPos) )
			{
				bestSearchState.bestAzi				= moveTracker->GetAzimuth	(lastValidTargetPos);
				bestSearchState.bestElev			= moveTracker->GetElevation (lastValidTargetPos);
				bestSearchState.bestRange			= moveTracker->GetRange		(lastValidTargetPos);
				bestSearchState.totalScore			= SHOULDERCAM_SCORE-0.00000001F;
				bestSearchState.sphereSearchName	= searchDesc.searchName;
				bestSearchState.sphereSearchSegment	= "Shoulder/Ease To Last Valid Target Pos";
				bestSearchState.bestLerpMode		= zPATH_LERP_LINE;
			}
			else bestSearchState.bestLerpMode		= zPATH_LERP_CUSTOM_JUMP;
		}
	}
	else 
	{

	};
	
	searchCache.GetSphereCoordLazy(bestSearchState.bestAzi,bestSearchState.bestElev,bestSearchState.bestRange,cachedState);

	cachedState->totalScore				= bestSearchState.totalScore;
	cachedState->trafoCamToWorld		= bestSearchState.trafoCamToWorld;

	return TRUE;
}

zBOOL zCPathSearch::PanicSearch(const zSEvasionSearchDesc &searchDesc)
{
	zSPathSearchState_Internal *cachedState;
	D_Print("AI Panic");

	// achtung: wenn der spieler hier nicht gesehen wird, ist die panic cam falsch!
	// dann sollte entweder ein streben zum nächsten validen target waypoint, oder - falls der spieler vom target waypoint
	// aus nicht zu sehen ist, mit einem switch zu einer gültigen ausweichposition mit Lerpmode SWITCH springen

	zBOOL foundPos		  = FALSE;
	zBOOL fistPersonEvade = searchDesc.searchName == "__FP__";

	// ist die range nicht allzu gross, und wenn der spieler gesehen werden kann, wird die rotation aus der spieler rotation übernommen

	if (!fistPersonEvade)
	if (moveTracker->GetRange()<camai->npcVolumeRangeOffset+1.5F)
	{
		// FIXME: dirty 
		zPOINT3 savePOI			= moveTracker->POI_Player;
		moveTracker->POI_Player = moveTracker->GetPlayerPos();
		if (IsPointValid(moveTracker->GetCamPos(),zPATHSEARCH_INCLUDE_PLAYER_TARGET_CHECK))
		{
			bestSearchState.bestLerpMode		= zPATH_LERP_CUSTOM;
			bestSearchState.trafoCamToWorld		= moveTracker->GetPanicCamMat();

			bestSearchState.bestAzi				= moveTracker->GetAzimuth();
			bestSearchState.bestElev			= moveTracker->GetElevation();
			bestSearchState.bestRange			= moveTracker->GetRange();
			bestSearchState.totalScore			= MIN_EVASION_SCORE+0.0000000000001F;;
			bestSearchState.sphereSearchName	= searchDesc.searchName;
			bestSearchState.sphereSearchSegment	= "Panic";			
			foundPos = TRUE;
		}
		moveTracker->POI_Player = savePOI;
	}
	if (!foundPos)
	{
		// nicht möglich.
		// Ziel: FirstPerson Camera mit AdjustCenterSphere zum Mittelpunkt. (Alpha Fade)
		bestSearchState.bestLerpMode		= zPATH_LERP_CUSTOM;
		bestSearchState.trafoCamToWorld		= moveTracker->GetFirstPersonCamMat();

		bestSearchState.bestAzi				= 0;
		bestSearchState.bestElev			= 0;
		bestSearchState.bestRange			= 0;
		bestSearchState.totalScore			= MIN_EVASION_SCORE;
		bestSearchState.sphereSearchName	= searchDesc.searchName;
		bestSearchState.sphereSearchSegment	= "First Person";			
		
		zTPoseFailReason failReason;
		if (!IsPointValid(bestSearchState.trafoCamToWorld.GetTranslation(),zPATHSEARCH_INCLUDE_CAM_CHECK,failReason)) 
		{
			// schauen ob a): Der letzte Target Waypoint gesehen werden kann und b) das Target
			// vom letzten Waypoint gesehen werden kann. Wenn ja: Strebe zum letzten Target Waypoint.
			// wenn nein: Ein SWITCH zur Schultercamera (oder besser: mit AdjustCenterSphere das getroffene
			// poly ermitteln, und dorthin switchen
			zPOINT3 lastValidTargetPos =  moveTracker->GetLastValidWayPoint(zCMovementTracker::zWAYPOINT_HEAD);
			if ( LineOfSight(camVob->GetPositionWorld(),  lastValidTargetPos) &&
				 LineOfSight(bestSearchState.trafoCamToWorld.GetTranslation(), lastValidTargetPos) )
			{
				bestSearchState.bestAzi				= moveTracker->GetAzimuth	(lastValidTargetPos);
				bestSearchState.bestElev			= moveTracker->GetElevation (lastValidTargetPos);
				bestSearchState.bestRange			= moveTracker->GetRange		(lastValidTargetPos);
				bestSearchState.totalScore			= MIN_EVASION_SCORE;
				bestSearchState.sphereSearchName	= searchDesc.searchName;
				bestSearchState.sphereSearchSegment	= "First Person/Ease To Last Valid Target Pos";
				bestSearchState.bestLerpMode		= zPATH_LERP_LINE;
			}
			else bestSearchState.bestLerpMode		= zPATH_LERP_CUSTOM_JUMP;

		}
	}

		// wenn der Spieler in der Nähe ist, und die Camera in gut gewählten Azi/Elev Grenzen ist, kann direkt zur Panic Cam gesprungen werden
	searchCache.GetSphereCoordLazy(bestSearchState.bestAzi,bestSearchState.bestElev,bestSearchState.bestRange,cachedState);

	cachedState->bestLerpMode			= bestSearchState.bestLerpMode;
	cachedState->totalScore				= bestSearchState.totalScore;
	cachedState->trafoCamToWorld		= bestSearchState.trafoCamToWorld;

	return TRUE;
}

void zCPathSearch::CalcStateScores(zSPathSearchState &state)
{
	zSPathSearchState_Internal *cachedState = 0;
	numSCsSearched++;
	
	if (searchCache.GetSphereCoordLazy(state.endAzi,state.endElev,state.endRange,cachedState))
	{
		// werte übernehmen
		numSCsCached++;

		state.totalScore	= cachedState->totalScore;
		state.bestLerpMode	= cachedState->bestLerpMode;
		return;
	}
	
	if (cachedState->maxRange>=state.endRange*state.endRange)
	{
		// je nach dem, wie gut die maximale Range Ermittlung beim Hinzufügen einer SC Ergebnisse bringt,
		// können hier noch mehr Flags hinzugefügt werden
		#ifdef SHOW_SEARCHRESULTS
		zERR_MESSAGE(10,0,"C: cached maxRange is greater than endRange. maxRange is: " + zSTRING(cachedState->maxRange) + "! Values A("+ zSTRING(state.endAzi) + ") + E(" + zSTRING(state.endElev) + ") + R(" + zSTRING(state.endRange) + ")");
		#endif
		numSCsCached++;
		SetIgnoreSearchFlags(zPATHSEARCH_INCLUDE_PLAYER_CHECK);
	}
	else 
	{
		cachedState->totalScore		= 0;
		cachedState->bestLerpMode	= zPATH_LERP_NONE;
		state.totalScore			= cachedState->totalScore;
		state.bestLerpMode			= cachedState->bestLerpMode;
		return;
	}

	cachedState->bestLerpMode = GetBestLerpMode(moveTracker->GetCamPos(),cachedState->foundPos);

	if (cachedState->bestLerpMode >= searchOptions.minLerpMode) 
	{
		// scores berechnen
		const float distScoreWeight			= 1.0F;
		const float lerpModeScoreWeight		= 0.2F;
		const float wrongSidePenalty		= 0.2F;

		zREAL distToIdealPos = (camai->GetCamSysFirstPos()-GetLastTriedPosition()).LengthApprox();
		cachedState->scoreDistToIdealPos	= 1.0F - distToIdealPos/((camai->GetMaxRange()+camai->GetBestRange())*100); 
		zClamp01(cachedState->scoreDistToIdealPos);
		
		int   lerpModeIndex  = 0;	int	 i	= (int)cachedState->bestLerpMode; 	while (i<<=1) lerpModeIndex++;
		cachedState->scoreLerpMode	= float(lerpModeIndex)/float(zPATH_LERP_MAX);

		cachedState->totalScore		= ((distScoreWeight	    * cachedState->scoreDistToIdealPos	) + 
									   (lerpModeScoreWeight * cachedState->scoreLerpMode		)
									   
									   )	/ 2;

		
		if ( moveTracker->GetPlayerAziSideSign()!=zSign(state.endAzi) )
		{
			cachedState->totalScore    -= wrongSidePenalty;
		};

		zClamp(cachedState->totalScore,SHOULDERCAM_SCORE+0.0001F,1.0F);

	}
	else cachedState->totalScore = 0;

	SetIgnoreSearchFlags(0);

	state.totalScore	= cachedState->totalScore;
	state.bestLerpMode	= cachedState->bestLerpMode;

};

zTPathLerpMode zCPathSearch::GetBestLerpMode(const zSPathSearchState &state)
{
	int tmpFlags = searchOptions.searchFlags;
	tmpFlags &= ~zPATHSEARCH_USE_PLAYER_MESH; 
//	tmpFlags &= ~zPATHSEARCH_INCLUDE_CAM_CHECK; 

	// FIXME: Teure unötige Rotationen
	zCQuat startRot		= moveTracker->GetLocalRot(state.startAzi,	state.startElev);
	zCQuat endRot		= moveTracker->GetLocalRot(state.endAzi,	state.endElev);

	zPOINT3	endDot		= DoSlerpRotQuat( startRot, endRot, 1, state.endRange);
	lastTriedPosition	= endDot;												// cache this position for SearchSphere()

	if (!IsPointValid(endDot,tmpFlags)) return zPATH_LERP_NONE;

	zPOINT3	firstDot	= DoSlerpRotQuat( startRot, endRot, 0, state.startRange );

	if ( LineOfSight( firstDot,endDot ) ) return zPATH_LERP_LINE; 
	else								  return zPATH_LERP_JUMP; 
	
	// alte (mit Intra Vis Check) GetWarpEaseMode Implementation
	//
	/*zTPathLerpMode mode;

	zPOINT3 aiCamPos	= moveTracker->GetRangePos(state.startRange);
	zPOINT3	firstDot	= moveTracker->DoSlerpRotQuat( startRot, endRot, 0 );

	aiCamPos			= moveTracker->GetRangePos(warp.endRange);
	zPOINT3	endDot		= moveTracker->DoSlerpRotQuat( startRot, endRot, 1);

	// Endposition besser checken
	zCPathSearch::zTPathSearchFlags tmpFlags = searchOptions.searchFlags & ~zPATHSEARCH_USE_PLAYER_MESH; 
	if (!IsPointValid(endDot,tmpFlags)) return mode;

	// @@@
	//if (allowRangeAdjust) { 
	//	warp.endRange = Distance(endDot, focus) ;
	//	aiCamPos    = tmp;
	//}

//	aiCamPos		= GetRangePos(warp.startRange);
//	@@@AI_SuggestCam(GetRangePos(warp.startRange));

	if (!tmpFlags & zPATHSEARCH_INCLUDE_CAM_CHECK) return zPATH_LERP_JUMP;

	zPOINT3 dot;

	float arcLength		= (endDot-firstDot).LengthApprox();
	float numCtrlDots	= MIN(5, 0.005F * (arcLength+200)) ;
	float nextTime		= 1/numCtrlDots;
	float t				= nextTime;
	zBOOL valid			= TRUE;
	zPOINT3	lastDot		= firstDot;

	// dots durchlaufen, check auf intravisibility
	do 
	{
		aiCamPos = Lerp( t, moveTracker->GetRangePos(state.startRange), moveTracker->GetRangePos(state.endRange) );
		dot      = moveTracker->DoSlerpRotQuat( startRot, endRot, t );

		if ( !LineOfSight(lastDot,dot) ) { valid = FALSE; break; }

		t += nextTime;
		lastDot = dot;
	}
	while ( t<=1 );

	if		( valid )						 mode = zPATH_LERP_ARC; 
	else if ( LineOfSight(firstDot,endDot) ) mode = zPATH_LERP_LINE;
	else									 mode = zPATH_LERP_JUMP;
	
	return mode;*/
}

zTPathLerpMode zCPathSearch::GetBestLerpMode(const zPOINT3 &startPos, const zPOINT3 &endPos)
{
	int tmpFlags = searchOptions.searchFlags;
	tmpFlags &= ~zPATHSEARCH_USE_PLAYER_MESH; 
//	tmpFlags &= ~zPATHSEARCH_INCLUDE_CAM_CHECK; 

	lastTriedPosition	= endPos;												// cache this position for SearchSphere()

	if (!IsPointValid(endPos,tmpFlags))		return zPATH_LERP_NONE;

	if ( LineOfSight( startPos,endPos ) )	return zPATH_LERP_LINE; 
	else									return zPATH_LERP_JUMP; 

};


zPOINT3 zCPathSearch :: DoSlerpRotQuat(const zCQuat &startRot, const zCQuat & endRot, const  float &rotTime, const float &range)
{
	if (rotTime<0 || rotTime>1) zERR_WARNING("C: zCMovementTracker::DoSlerpRotQuat():rotTime not in range [0..1]:"+zSTRING(rotTime));

	zCQuat newPose;
	zMAT4  newTrafo=Alg_Identity3D();

	newPose.Slerp( rotTime, startRot, endRot );

	newPose.QuatToMatrix4(newTrafo);

	newTrafo = moveTracker->GetPlayerTrafo() * newTrafo;

	// get new world-cam-pos
	return ( moveTracker->GetPlayerPos() - (newTrafo.GetAtVector() * range ) );
}

zBOOL zCPathSearch  ::	FindBestEvasion(zSPathSearchOptions &options)
{
	zCArray <zSEvasionSearchDesc>	evasionSearchList;
	searchOptions				= options;
	searchOptions.startAzi		= moveTracker->GetAzimuth();
	searchOptions.startElev		= moveTracker->GetElevation();
	searchOptions.startRange	= moveTracker->GetRange();
	searchOptions.bestScore		= MIN_EVASION_SCORE;
	searchOptions.searchFlags   |= zPATHSEARCH_INCLUDE_CAM_CHECK;
	//searchOptions.searchFlags	|= zPATHSEARCH_USE_PLAYER_FUTURE_POS;

	memset ( &evasionSearchReport,0, sizeof(evasionSearchReport));
	
	searchCache.DeleteList();	

	if ( !FindEvasionSequence(evasionSearchList) ) return FALSE;


	zBOOL foundEvasion	= FALSE;
	int	  i				= 0;
	do 
	{  
		if ( evasionSearchList[i].searchFunc(evasionSearchList[i]) ) 
		{
			foundEvasion = TRUE;
			break;
		}
	} 
	while (i++ < evasionSearchList.GetNum());

	if (!foundEvasion)  	return FALSE;

	if (bestSearchState.totalScore<searchOptions.bestScore)
	{
		// nun den besten score aus allen gefundenen rauspicken
		zSPathSearchState_Internal *cachedState = 0;
		searchCache.GetBestScoredSearch(bestSearchState.bestAzi,bestSearchState.bestElev,bestSearchState.bestRange,cachedState);
		zERR_ASSERT(cachedState);
		bestSearchState.bestLerpMode	= cachedState->bestLerpMode;
		bestSearchState.trafoCamToWorld	= cachedState->trafoCamToWorld;
	};

	// gefundenen Ausweg in die evasionsearchreport Struktur in die zCAICamera Klasse eintragen
	zSPathSearchResult *evasionSearchReport = zCAICamera::GetCurrent()->evasionSearchReport;

	evasionSearchReport->foundEvasion	= foundEvasion;
	evasionSearchReport->p1				= moveTracker->GetCamPos();
	evasionSearchReport->p2				= (bestSearchState.bestLerpMode == zPATH_LERP_CUSTOM) ? bestSearchState.trafoCamToWorld.GetTranslation() : moveTracker->CalcAziElevRangeApprox(bestSearchState.bestAzi,bestSearchState.bestElev,bestSearchState.bestRange);
	evasionSearchReport->lerpModes		= bestSearchState.lerpModes;
	evasionSearchReport->bestLerpMode	= bestSearchState.bestLerpMode;
	evasionSearchReport->veloTrans		= camai->veloTrans;
	evasionSearchReport->veloRot		= camai->veloRot;
	evasionSearchReport->r1.Matrix4ToQuat(camVob->trafoObjToWorld);
	evasionSearchReport->r2.Matrix4ToQuat(bestSearchState.trafoCamToWorld);

	// wenn der gefundene Ausweg des letzten Frames besser bewertet wurde, und immer noch gültig ist,
	// wird dieser genommen
	const float BETTER_CHOICE_MIN_DELTA = 0.08F;
	zBOOL useLast = FALSE;

	if (lastSearchState.totalScore == SHOULDERCAM_SCORE && 
		bestSearchState.totalScore>lastSearchState.totalScore &&
		CanEvadeTo(lastSearchState) && 
		bestSearchState.endRange<250 &&
		bestSearchState.endElev>60
		) useLast = TRUE;

	if ( useLast																				||
		 ((lastSearchState.totalScore>bestSearchState.totalScore)								&& 
		 (lastSearchState.totalScore>MIN_EVASION_SCORE		   )								&& 
		 (zAbs(lastSearchState.totalScore-bestSearchState.totalScore)>BETTER_CHOICE_MIN_DELTA)	&&
		 CanEvadeTo(lastSearchState)) )
	{
#ifdef DEBUG_EDENFELD
		zERR_MESSAGE(10,0,"C: Last found evasion is better than actual found evasion");
#endif
		evasionSearchReport->p2				= moveTracker->CalcAziElevRangeApprox(lastSearchState.bestAzi,lastSearchState.bestElev,lastSearchState.bestRange);
		evasionSearchReport->lerpModes		= lastSearchState.lerpModes;
		evasionSearchReport->bestLerpMode	= lastSearchState.bestLerpMode;
		evasionSearchReport->r2.Matrix4ToQuat(lastSearchState.trafoCamToWorld);
	}
	else lastSearchState = bestSearchState;

#if 0
	if (!LineOfSight(moveTracker->GetPlayerPos(),evasionSearchReport->p2))
	{
		int brk = 0;
	};
#endif


#ifdef DEBUG_EDENFELD
#ifdef SHOW_SEARCHRESULTS
	zERR_MESSAGE(10,0,"C: zCPathSearch::FindBestEvasion(): SCs Searched: " + zSTRING(numSCsSearched) + " , SCs cached: " + zSTRING(numSCsCached));

	static zSPathSearchState oldSearchState;
	static zSTRING debugString;
	if ( (bestSearchState.bestAzi		!= oldSearchState.bestAzi)	||
		 (bestSearchState.bestElev		!= oldSearchState.bestElev)	||
		 (bestSearchState.bestRange		!= oldSearchState.bestRange)||
		 (bestSearchState.bestLerpMode	!= oldSearchState.bestLerpMode) )
	{
		oldSearchState = bestSearchState;

		debugString =	 zSTRING("A(")							  + zSTRING(int(oldSearchState.bestAzi))	+ 
									 zSTRING("), E(")			  + zSTRING(int(oldSearchState.bestElev))	+ 
									 zSTRING("), R(")			  + zSTRING(int(oldSearchState.bestRange))	+ 
									 zSTRING(") (Name: ")		  + oldSearchState.sphereSearchName			+
									 zSTRING(") (Seg:")			  + oldSearchState.sphereSearchSegment		+
									 zSTRING(")");
		if (zinput->KeyPressed(KEY_LSHIFT))	
		{
			zERR_WARNING("C: Evasion " + debugString);
		}
	}

	screen->Print( 1096,8000,debugString );

#endif
#endif

		
	return TRUE;

}

zBOOL zCPathSearch::CanEvadeTo(zSPathSearchState &searchState)
{
	zPOINT3 movePos = moveTracker->CalcAziElevRangeApprox(searchState.bestAzi,searchState.bestElev,searchState.bestRange);
	if (IsPointValid(movePos,searchOptions.searchFlags)) return TRUE;
	return FALSE;
};

// zCPathSearch::FindEvasionSequence
// Findet ein priorisierte Sequenz von zu untersuchenden Sphere Segmenten in Abhängigkeit
// von den Suchparametern in zCPathSearch::searchOptions

zBOOL zCPathSearch :: FindEvasionSequence(zCArray<zSEvasionSearchDesc> &evasion) 
{

	if (searchOptions.poseFailReason == zFAILREASON_BADSCENE_CINEMA)
	{
		FES_NoEvasionFound		 (evasion);
		return TRUE;
	}

	// als erstes einen punkt in der "ideal cone" suchen
	zBOOL backMove = moveTracker->GetPlayerMovement() & zPLAYER_MOVED_BACKWARD;
		
	if (!backMove) FES_IdealCone(evasion);

	// Was war verantwortlich für den "bad mode" ?
	switch (searchOptions.poseFailReason) 
	{
	case zFAILREASON_PLAYER_TARGET_INVISIBLE:	FES_PlayerTargetInvisible(evasion);				break;
	default:
	case zFAILREASON_PLAYER_INVISIBLE:			
		if (moveTracker->HasPlayerMoved())		FES_PlayerInvisible_Moved	(evasion); else
		if (moveTracker->HasPlayerRotated())	FES_PlayerInvisible_Rotated	(evasion); 
		else									FES_PlayerInvisible_Standing(evasion);					
		break;
	}

	if (backMove) FES_IdealCone(evasion);

	// TODO: Evasion Search mit allen noch nicht angegebenen Sphere Segmenten aufbauen
	// in diesen Segmenten gefundenen Ausweichmöglichkeiten sind dann geringer in der core ai zu bewerten


	// Schulter Camera und die Panic Camera sind die letzten Alternativen (vorerst)
	zSEvasionSearchDesc	shoulderDesc,panicDesc;
	shoulderDesc.searchFunc	=	AI_FindEvasionShoulderCam;
	shoulderDesc.searchName =   "Shoulder Cam";
	panicDesc	.searchFunc =   AI_FindEvasionPanic;
	panicDesc	.searchName =   "Panic Cam";
	evasion		.InsertEnd(shoulderDesc);
	evasion		.InsertEnd(panicDesc);


	if (evasion.GetNum() > 0) return TRUE;
	else					  return FALSE;
}

zBOOL zCPathSearch :: FES_PlayerInvisible_Moved(zCArray<zSEvasionSearchDesc> &evasion) 
{	
	D_Print("FES Player Invisible (moved)");

	zCMovementTracker::zTWayPoint wpType;
	// standard camera AI. Spieler wird nicht mehr gesehen. 
	zVEC3 movPlayerWorld= moveTracker->GetPlayerPos()-moveTracker->GetLastPlayerPos();
	int	  axis	=  VZ;

	zBOOL playerRotated = moveTracker->HasPlayerRotated();

	// Check with part of targets body movement is responsible for LOS fail
	zPOINT3 failPos = zPOINT3(0,0,0);

	if (world->TraceRayFirstHit(moveTracker->GetPlayerHipLeft(), (moveTracker->GetCamPos()-moveTracker->GetPlayerHipLeft()),target,standardTraceFlags)) 
	{
		D_Print("Left hip failed");
		failPos = moveTracker->GetPlayerHipLeft();
		wpType  = zCMovementTracker::zWAYPOINT_HIP_LEFT;
	}
	else if (world->TraceRayFirstHit(moveTracker->GetPlayerHipRight(), (moveTracker->GetCamPos()-moveTracker->GetPlayerHipRight()),target,standardTraceFlags)) 
	{
		D_Print("Right hip failed");
		failPos = moveTracker->GetPlayerHipRight();
		wpType  = zCMovementTracker::zWAYPOINT_HIP_RIGHT;
	}
	else if (world->TraceRayFirstHit(moveTracker->GetPlayerHead(), (moveTracker->GetCamPos()-moveTracker->GetPlayerHead()),target,standardTraceFlags)) 
	{
		D_Print("Head failed");
		failPos = moveTracker->GetPlayerHead();
		wpType  = zCMovementTracker::zWAYPOINT_HEAD;
	}
	else 
	{
		D_Print("player IS visible, trying rotation evasion");
		// etwas anderes muss passiert sein... TODO: behandeln
		// Rückwärtsbewegung: Auf hohem Seitenwinkel stehenbleiben
		// Vorwärtsbewegung : 
		if	    (moveTracker->GetPlayerMovement() & zPLAYER_MOVED_FORWARD) return FES_PlayerInvisible_Moved_FW(evasion);
		else if	(moveTracker->GetPlayerMovement() & zPLAYER_MOVED_BACKWARD)return FES_PlayerInvisible_Moved_BW(evasion);
		else if (moveTracker->HasPlayerRotated())						   return FES_PlayerInvisible_Rotated (evasion);

		return FES_PlayerInvisible_Moved_FW(evasion);
	}

	zPOINT3 oldWayPoint = moveTracker->GetLastValidWayPoint(wpType);

	zVEC3	movPlayerCam= (moveTracker->GetCamTrafoInv() * failPos) - (moveTracker->GetCamTrafoInv() * oldWayPoint);

	// Find which part of the movement vector caused LOS-Fail

	zVEC3 pXMove  = (moveTracker->GetCamTrafoInv() * oldWayPoint) + zVEC3(movPlayerCam[VX],0,0);
	zVEC3 pYMove  = (moveTracker->GetCamTrafoInv() * oldWayPoint) + zVEC3(0,movPlayerCam[VY],0);
	zVEC3 pXYMove = (moveTracker->GetCamTrafoInv() * oldWayPoint) + zVEC3(movPlayerCam[VX],movPlayerCam[VY]);

	if		( !LineOfSight ( moveTracker->GetCamPos(), moveTracker->GetCamTrafo() * pXMove)  ) 	axis = VX; 
	else if ( !LineOfSight ( moveTracker->GetCamPos(), moveTracker->GetCamTrafo() * pYMove)  )	axis = VY; 
	else if ( !LineOfSight ( moveTracker->GetCamPos(), moveTracker->GetCamTrafo() * pXYMove) )	axis = VZ;	// eigentlich nicht VZ, da eine nur Distanzänderung des Spieler zur Camera nicht zur nicht Sichtbarkeit des Spielers führen kann (ausser beim Durchdringen von NSCs)
	else	
	{
		D_Print("Player Fail Reason unknown");
		if (moveTracker->HasPlayerRotated()) return FES_PlayerInvisible_Rotated (evasion);
		else								 return FES_PlayerInvisible_Moved_FW(evasion);
	}

	zREAL	a	= camai->bestRotY,
			e	= camai->bestRotX,
			r	= camai->GetBestRange()*100;

	float aziEnd, elevEnd;
	float minRange = camai->GetMinRange()*100;
			//zClamp(r, camai->minRange*100, camai->maxRange*100);

	switch (axis) 
	{
	case VX :
		{
			if (movPlayerCam[VX]<0) D_Print("AI Left"); else D_Print("AI Right");

			zSEvasionSearchDesc::zSEvasionSearchOptions  opt1,opt2,opt3;

			// zuerst die seiten winkel versuchen 
			opt1.scSign			=	zVEC3(	movPlayerCam[VX]<0?1.0F:-1.0F, 	0, -1.0F);
			opt1.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
			opt1.scSequence		=	playerRotated ? "RAE" : "AER";
			opt1.scStart		=	zVEC3(a,e,r);
			aziEnd				=	a+(opt1.scSign[AZI]*100); 	zClamp(aziEnd,-100.0F,100.0F);
			opt1.scEnd			=	zVEC3( aziEnd ,e, minRange );
			opt1.scName			=	movPlayerCam[VX]<0 ? "PIML A(+)E(0)R(-)" : "PIMR A(-)E(0)R(-)";

			// als nächstes versuchen nach oben auszuweichen, wenn die elevation > 0 ist, sonst nach unten
			opt2.scSign			=	zVEC3(0,e>0?1.0F:-1.0F,0);
			opt2.scQuality		=	zVEC3(0.2F,0.2F,0.2F);
			opt2.scSequence		=	playerRotated ? "REA" : "EAR";
			opt2.scStart		=	zVEC3(a,e,r);
			elevEnd				=	e+(opt2.scSign[ELEV]*60);	zClamp(elevEnd,-89.0F,89.0F);
			opt2.scEnd			=	zVEC3(a,elevEnd,minRange);
			opt2.scName			=	e>0 ? "PIMLR A(0)E(+)R(0)" : "PIMLR A(0)E(-)R(0)";

			// nun die andere elevation versuchen
			opt3.scSign			=	zVEC3(0,-opt2.scSign[ELEV],0);
			opt3.scQuality		=	zVEC3(0.2F,0.2F,0.2F);
			opt3.scSequence		=	playerRotated ? "REA" : "ERA";
			opt3.scStart		=	zVEC3(a,e,r);
			elevEnd				=   e+(opt3.scSign[ELEV]*60); zClamp(elevEnd,-89.0F,89.0F);
			opt3.scEnd			=	zVEC3(a,elevEnd,minRange);
			opt3.scName			=	e>0 ? "PIMLR A(0)E(-)R(0)" : "PIMLR A(0)E(+)R(0)";

			zSEvasionSearchDesc		leftDesc;
			leftDesc.searchFunc		=	AI_FindEvasionSphere;
			leftDesc.searchName		=	"Player Invisible, moved left/right";
			leftDesc.sphereSearchList.InsertEnd(opt1);
			leftDesc.sphereSearchList.InsertEnd(opt2);
			leftDesc.sphereSearchList.InsertEnd(opt3);
			evasion .InsertEnd				   (leftDesc);
		}
		break;
	case VY :
		{
			if (movPlayerCam[VY]<0) D_Print("AI Down"); else D_Print("AI Up");

			zSEvasionSearchDesc::zSEvasionSearchOptions upOpt1,upOpt2,upOpt3;

			// zuerst die höhenwinkel versuchen 
			upOpt1.scSign			=	zVEC3(0,movPlayerCam[VY]<0?1.0F:0,-1.0F);
			upOpt1.scQuality		=	zVEC3(0,0.3F,0.2F);
			upOpt1.scSequence		=	"ERA";
			upOpt1.scStart			=	zVEC3(a,e,r);
			elevEnd					=   e+(upOpt1.scSign[ELEV]*89.9F); zClamp(elevEnd,-89.9F,89.9F);
			upOpt1.scEnd			=	zVEC3(a,elevEnd,minRange);
			upOpt1.scName			=	movPlayerCam[VY]<0 ? "PIMD A(0)E(+)R(-)" : "PIMU A(0)E(-)R(-)";

			// andere seite
			upOpt2.scSign			=	zVEC3(0,-upOpt1.scSign[ELEV],-1.0F);
			upOpt2.scQuality		=	zVEC3(0,0.3F,0.2F);
			upOpt2.scSequence		=	"ERA";
			upOpt2.scStart			=	zVEC3(a,e,r);
			elevEnd					=	e+(upOpt2.scSign[ELEV]*89.9F);		zClamp(elevEnd,-89.9F,89.9F);
			upOpt2.scEnd			=	zVEC3(a,elevEnd,minRange);
			upOpt2.scName			=	movPlayerCam[VY]<0 ? "PIMD A(0)E(-)R(-)" : "PIMU A(0)E(+)R(-)";

			// nun die seitenwinkel testen
			upOpt3.scSign			=	zVEC3(movPlayerCam[VX]<0?1:-1.0F, 0, -1.0F);
			upOpt3.scQuality		=	zVEC3(0.5F,0,0.5F);
			upOpt3.scSequence		=	"ARE";
			upOpt3.scStart			=	zVEC3(a,e,r);
			aziEnd					=	a+(upOpt3.scSign[AZI]*100); zClamp(aziEnd,-180.0F,180.0F);
			upOpt3.scEnd			=	zVEC3(aziEnd,e,minRange);
			upOpt3.scName			=	movPlayerCam[VY]<0 ? "PIMD A(+)E(0)R(-)" : "PIMU A(-)E(0)R(-)";

			zSEvasionSearchDesc		upDesc;
			upDesc.searchFunc		=	AI_FindEvasionSphere;
			upDesc.searchName		=	"Player Invisible, moved up/down";
			upDesc.sphereSearchList.InsertEnd(upOpt1);
			upDesc.sphereSearchList.InsertEnd(upOpt2);
			upDesc.sphereSearchList.InsertEnd(upOpt3);
			evasion .InsertEnd				   (upDesc);
		}
		break;
	case VZ:
		{
			if (movPlayerCam[VX]<0 && movPlayerCam[VY]<0) D_Print("AI LeftUp");   else
			if (movPlayerCam[VX]<0 && movPlayerCam[VY]>0) D_Print("AI LeftDown"); else
			if (movPlayerCam[VX]>0 && movPlayerCam[VY]>0) D_Print("AI RightDown");else
			if (movPlayerCam[VX]>0 && movPlayerCam[VY]<0) D_Print("AI RightUp");  
			else D_Print("AI Unknown");
			
			zSEvasionSearchDesc::zSEvasionSearchOptions miscOpt1,miscOpt2,miscOpt3,miscOpt4;
			// zuerst die höhenwinkel versuchen 
			miscOpt1.scSign			=	zVEC3(movPlayerCam[VX]<0?1.0F:0,movPlayerCam[VY]<0?1.0F:0,-1.0F);
			miscOpt1.scQuality		=	zVEC3(0.5F,0.2F,0.2F);
			miscOpt1.scSequence		=	zAbs(movPlayerCam[VX])>zAbs(movPlayerCam[VY]) ? "AER":"EAR";
			miscOpt1.scStart		=	zVEC3(a,e,r);
			aziEnd					=   a+(miscOpt1.scSign[AZI]*100); zClamp(aziEnd,-100.0F,100.0F);
			elevEnd					=	e+(miscOpt1.scSign[ELEV]*89.9F);zClamp(elevEnd,-89.9F,89.9F);
			miscOpt1.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
			miscOpt1.scName			=	"PIMLRUD1";


			// andere seite azi
			miscOpt2.scSign			=	zVEC3(-miscOpt1.scSign[AZI],miscOpt1.scSign[ELEV],-1.0F);
			miscOpt2.scQuality		=	zVEC3(0.5F,0.2F,0.2F);
			miscOpt2.scSequence		=	zAbs(movPlayerCam[VX])>zAbs(movPlayerCam[VY]) ? "AER":"EAR";
			miscOpt2.scStart		=	zVEC3(a,e,r);
			aziEnd					=	a+(miscOpt2.scSign[AZI]*100); zClamp(aziEnd,-100.0F,100.0F);
			elevEnd					=	e+(miscOpt1.scSign[ELEV]*89.9F); zClamp(elevEnd,-89.9F,89.9F);
			miscOpt2.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
			miscOpt2.scName			=	"PIMLRUD2";

			// andere seite elev
			miscOpt3.scSign			=	zVEC3(miscOpt1.scSign[AZI],-miscOpt1.scSign[ELEV],-1.0F);
			miscOpt3.scQuality		=	zVEC3(0.5F,0.2F,0.2F);
			miscOpt3.scSequence		=	zAbs(movPlayerCam[VX])>zAbs(movPlayerCam[VY]) ? "AER":"EAR";
			miscOpt3.scStart		=	zVEC3(a,e,r);
			aziEnd					=	a+(miscOpt3.scSign[AZI]*100);	zClamp(aziEnd,-100.0F,100.0F);
			elevEnd					=	e+(miscOpt3.scSign[ELEV]*89.9F);	zClamp(elevEnd,-89.9F,89.9F);
			miscOpt3.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
			miscOpt3.scName			=	"PIMLRUD3";

			// andere seite azi/elev
			miscOpt4.scSign			=	zVEC3(-miscOpt1.scSign[AZI],-miscOpt1.scSign[ELEV],-1.0F);
			miscOpt4.scQuality		=	zVEC3(0.5F,0.2F,0.2F);
			miscOpt4.scSequence		=	zAbs(movPlayerCam[VX])>zAbs(movPlayerCam[VY]) ? "AER":"EAR";
			miscOpt4.scStart		=	zVEC3(a,e,r);
			aziEnd					=	a+(miscOpt4.scSign[AZI]*100);	zClamp(aziEnd,-100.0F,100.0F);
			elevEnd					=	e+(miscOpt4.scSign[ELEV]*80);	zClamp(elevEnd,-89.9F,89.9F);
			miscOpt4.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
			miscOpt4.scName			=	"PIMLRUD4";

			zSEvasionSearchDesc		miscDesc;
			miscDesc.searchFunc		=	AI_FindEvasionSphere;
			miscDesc.searchName		=	"Player Invisible, moved diagonally";
			miscDesc.sphereSearchList.InsertEnd(miscOpt1);
			miscDesc.sphereSearchList.InsertEnd(miscOpt2);
			miscDesc.sphereSearchList.InsertEnd(miscOpt3);
			miscDesc.sphereSearchList.InsertEnd(miscOpt4);
			evasion .InsertEnd				   (miscDesc);
		}
		break;
	}

	return TRUE;

};

zBOOL zCPathSearch :: FES_PlayerInvisible_Moved_BW(zCArray<zSEvasionSearchDesc> &evasion)
{
	D_Print("FES Player Invisible (moved backward)");

	// determin on which side of the camera at vec the target lies
	zPOINT3 playerLocalCam = moveTracker->GetPlayerTrafoInv() * moveTracker->GetCamPos();

	zSEvasionSearchDesc::zSEvasionSearchOptions opt1,opt2,opt3,opt4;

	float minRange		=   camai->GetMinRange() * 100;
	
	zREAL	a	= camai->bestRotY,
			e	= camai->bestRotX,
			r	= camai->GetBestRange()*100;

	float aziEnd, elevEnd;

	//zERR_MESSAGE(4,0,"C: movePlayerCam: " + zSTRING(playerLocalCam[VX]));


	opt1.scSign			=	zVEC3(playerLocalCam[VX]>0 ? 1:-1, 1 ,-1);
	opt1.scQuality		=	zVEC3(0.5F,0.2F,0.5F);
	opt1.scSequence		=	"ARE";
	opt1.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt1.scSign[AZI]*100); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt1.scSign[ELEV]*30); zClamp(elevEnd,-60.0F,89.9F);
	opt1.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt1.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(+)E(+)R(-)" : "PIMBL A(-)E(+)R(-)";

	// andere elevation
	opt2.scSign			=	zVEC3(playerLocalCam[VX]>0 ? 1:-1, -1 ,-1);
	opt2.scQuality		=	zVEC3(0.5F,0.2F,0.5F);
	opt2.scSequence		=	"ARE";
	opt2.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt2.scSign[AZI]*100); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt2.scSign[ELEV]*30); zClamp(elevEnd,-60.0F,89.9F);
	opt2.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt2.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(+)E(-)R(-)" : "PIMBL A(-)E(-)R(-)";
	
	// andere seite azi
	opt3.scSign			=	zVEC3(playerLocalCam[VX]>0 ? -1:1, 1 ,-1);
	opt3.scQuality		=	zVEC3(0.5F,0.2F,0.5F);
	opt3.scSequence		=	"ARE";
	opt3.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt3.scSign[AZI]*100); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt3.scSign[ELEV]*30); zClamp(elevEnd,-60.0F,89.9F);
	opt3.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt3.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(-)E(+)R(-)" : "PIMBL A(+)E(+)R(-)";

	// andere seite elev
	opt4.scSign			=	zVEC3(playerLocalCam[VX]>0 ? -1:1, -1 ,-1);
	opt4.scQuality		=	zVEC3(0.5F,0.2F,0.5F);
	opt4.scSequence		=	"ARE";
	opt4.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt4.scSign[AZI]*100); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt4.scSign[ELEV]*30); zClamp(elevEnd,-60.0F,89.0F);
	opt4.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt4.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(-)E(+)R(-)" : "PIMBL A(+)E(+)R(-)";

	zSEvasionSearchDesc		rotDesc;
	rotDesc.searchFunc		=	AI_FindEvasionSphere;
	rotDesc.searchName		=	"Player moved backward";
	rotDesc.sphereSearchList.InsertEnd(opt1);
	rotDesc.sphereSearchList.InsertEnd(opt2);
	rotDesc.sphereSearchList.InsertEnd(opt3);
	rotDesc.sphereSearchList.InsertEnd(opt4);
	evasion .InsertEnd				   (rotDesc);

	return TRUE;


};
zBOOL zCPathSearch :: FES_PlayerInvisible_Moved_FW(zCArray<zSEvasionSearchDesc> &evasion)
{
	D_Print("FES Player Invisible (moved forward)");

	// determin on which side of the camera at vec the target lies
//	zPOINT3 playerLocalCam = moveTracker->GetCamTrafoInv() * moveTracker->GetPlayerPos();
	zPOINT3 playerLocalCam = moveTracker->GetPlayerTrafoInv() * moveTracker->GetCamPos();

	zSEvasionSearchDesc::zSEvasionSearchOptions opt1,opt2,opt3,opt4;
	
	zREAL	a	= moveTracker->GetAzimuth(),
			e	= moveTracker->GetElevation(),
			r	= camai->GetBestRange()*100;

	float minRange		=   camai->GetMinRange() * 100;
	float aziEnd, elevEnd;

	opt1.scSign			=	zVEC3(playerLocalCam[VX]>0 ? 1:-1, 1 ,-1);
	opt1.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt1.scSequence		=	"REA";
	opt1.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt1.scSign[AZI]*20); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt1.scSign[ELEV]*40); zClamp(elevEnd,-89.9F,89.9F);
	opt1.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt1.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(+)E(+)R(-)" : "PIMBL A(-)E(+)R(-)";

	// andere elevation
	opt2.scSign			=	zVEC3(playerLocalCam[VX]>0 ? 1:-1, -1 ,-1);
	opt2.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt2.scSequence		=	"REA";
	opt2.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt2.scSign[AZI]*20); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt2.scSign[ELEV]*40); zClamp(elevEnd,-89.9F,89.9F);
	opt2.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt2.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(+)E(+)R(-)" : "PIMBL A(-)E(+)R(-)";
	
	// andere seite azi
	opt3.scSign			=	zVEC3(playerLocalCam[VX]>0 ? -1:1, 1 ,-1);
	opt3.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt3.scSequence		=	"REA";
	opt3.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt3.scSign[AZI]*20); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt3.scSign[ELEV]*40); zClamp(elevEnd,-89.9F,89.9F);
	opt3.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt3.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(-)E(+)R(-)" : "PIMBL A(+)E(+)R(-)";

	// andere seite elev
	opt4.scSign			=	zVEC3(playerLocalCam[VX]>0 ? -1:1, -1 ,-1);
	opt4.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt4.scSequence		=	"REA";
	opt4.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt4.scSign[AZI]*20); zClamp(aziEnd,-100.0F,100.0F);
	elevEnd				=   e+(opt4.scSign[ELEV]*40); zClamp(elevEnd,-89.9F,89.9F);
	opt4.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt4.scName			=	playerLocalCam[VX]>0 ? "PIMBR A(-)E(+)R(-)" : "PIMBL A(+)E(+)R(-)";

	zSEvasionSearchDesc		rotDesc;
	rotDesc.searchFunc		=	AI_FindEvasionSphere;
	rotDesc.searchName		=	"Player moved forward";
	rotDesc.sphereSearchList.InsertEnd(opt1);
	rotDesc.sphereSearchList.InsertEnd(opt2);
	rotDesc.sphereSearchList.InsertEnd(opt3);
	rotDesc.sphereSearchList.InsertEnd(opt4);
	evasion .InsertEnd				   (rotDesc);

	return TRUE;
};

zBOOL zCPathSearch :: FES_IdealCone(zCArray<zSEvasionSearchDesc> &evasion) 
{
	D_Print("FES Ideal Cone");

	const float MIN_AZI_DEG_SWITCH_SIDE=20.0F;
	float bestRange			=	camai->GetBestRange() * 100;

	zSEvasionSearchDesc::zSEvasionSearchOptions  opt1,opt2,opt3,opt4,opt5,opt6,opt7,opt8;

	// bestrange - minRange, azi rechts, elevation hoch
	opt1.scSign				=	zVEC3( 1 , 	1, -1);
	opt1.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt1.scSequence			=	"RAE";
	opt1.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt1.scEnd				=	zVEC3( MIN(180, camai->bestRotY+10), MIN(+89,camai->bestRotX+30),MAX(0.01F, (bestRange-10)) );
	opt1.scName				=	"IC A(+)E(+)R(-)";

	// bestrange - minRange, azi in drehrichtung, elevation runter
	opt2.scSign				=	zVEC3( 1 , 	-1, -1);
	opt2.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt2.scSequence			=	"RAE";
	opt2.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt2.scEnd				=	zVEC3( MIN(180, camai->bestRotY+10), MAX(-89,camai->bestRotX-20),MAX(0.01F, (bestRange-10)));
	opt2.scName				=	"IC A(+)E(-)R(-)";

	// bestrange - minRange, azi gegen drehrichtung, elevation runter
	opt3.scSign				=	zVEC3( -1 , -1, -1);
	opt3.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt3.scSequence			=	"RAE";
	opt3.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt3.scEnd				=	zVEC3( MAX(-180, camai->bestRotY-10), MAX(-89,camai->bestRotX-20),MAX(0.01F, (bestRange-10)));
	opt3.scName				=	"IC A(-)E(-)R(-)";

	// bestrange - minRange, azi gegen drehrichtung, elevation hoch
	opt4.scSign				=	zVEC3( -1 , 1, -1);
	opt4.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt4.scSequence			=	"RAE";
	opt4.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt4.scEnd				=	zVEC3( MAX(-180, camai->bestRotY-10), MIN(+89,camai->bestRotX+30),MAX(0.01F, (bestRange-10)));
	opt4.scName				=	"IC A(-)E(+)R(-)";

	// bestrange - maxRange, azi gegen drehrichtung, elevation hoch
	opt5.scSign				=	zVEC3( -1 ,	1, 1);
	opt5.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt5.scSequence			=	"RAE";
	opt5.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt5.scEnd				=	zVEC3(MAX(-180, camai->bestRotY-10), MIN(+89,camai->bestRotX+30), (bestRange+10));
	opt5.scName				=	"IC A(-)E(+)R(+)";

	// bestrange - maxRange, azi gegen drehrichtung, elevation runter
	opt6.scSign				=	zVEC3( -1, -1, 1);
	opt6.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt6.scSequence			=	"RAE";
	opt6.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt6.scEnd				=	zVEC3(MAX(-180, camai->bestRotY-10), MAX(-89,camai->bestRotX-20), (bestRange+10));
	opt6.scName				=	"IC A(-)E(-)R(+)";

	// bestrange - maxRange, azi in drehrichtung, elevation runter
	opt7.scSign				=	zVEC3( 1,-1,+1);
	opt7.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt7.scSequence			=	"RAE";
	opt7.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt7.scEnd				=	zVEC3(MIN(+180, camai->bestRotY+10), MAX(-89,camai->bestRotX-20), (bestRange+10));
	opt7.scName				=	"IC A(+)E(-)R(+)";

	// bestrange - maxRange, azi in drehrichtung, elevation hoch
	opt8.scSign				=	zVEC3( 1,	1,	 +1);
	opt8.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
	opt8.scSequence			=	"RAE";
	opt8.scStart			=	zVEC3(camai->bestRotY,		camai->bestRotX,			bestRange);
	opt8.scEnd				=	zVEC3(MIN(+180, camai->bestRotY+10), MIN(+89,camai->bestRotX+30), (bestRange+10));
	opt8.scName				=	"IC A(+)E(+)R(+)";

	zSEvasionSearchDesc		idealDesc;
	idealDesc.searchFunc	=	AI_FindEvasionSphere;
	idealDesc.searchName	=	"Ideal Cone";
	idealDesc.sphereSearchList.InsertEnd(opt1);
	idealDesc.sphereSearchList.InsertEnd(opt2);
	idealDesc.sphereSearchList.InsertEnd(opt3);
	idealDesc.sphereSearchList.InsertEnd(opt4);
	idealDesc.sphereSearchList.InsertEnd(opt5);
	idealDesc.sphereSearchList.InsertEnd(opt6);
	idealDesc.sphereSearchList.InsertEnd(opt7);
	idealDesc.sphereSearchList.InsertEnd(opt8);
	evasion .InsertEnd			(idealDesc);

	if (zAbs(camai->bestRotY) >=MIN_AZI_DEG_SWITCH_SIDE)
	{
		// bestrange - minRange, azi rechts, elevation hoch
		opt1.scSign				=	zVEC3( 1 , 	1, -1);
		opt1.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt1.scSequence			=	"RAE";
		opt1.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt1.scEnd				=	zVEC3( MIN(180, -camai->bestRotY+10), MIN(+89,camai->bestRotX+20),MAX(0.01F, (bestRange-10)) );
		opt1.scName				=	"IC A(+)E(+)R(-)";

		// bestrange - minRange, azi in drehrichtung, elevation runter
		opt2.scSign				=	zVEC3( 1 , 	-1, -1);
		opt2.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt2.scSequence			=	"RAE";
		opt2.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt2.scEnd				=	zVEC3( MIN(180, -camai->bestRotY+10), MAX(-89,camai->bestRotX-20),MAX(0.01F, (bestRange-10)));
		opt2.scName				=	"IC A(+)E(-)R(-)";

		// bestrange - minRange, azi gegen drehrichtung, elevation runter
		opt3.scSign				=	zVEC3( -1 , -1, -1);
		opt3.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt3.scSequence			=	"RAE";
		opt3.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt3.scEnd				=	zVEC3( MAX(-180, -camai->bestRotY-10), MAX(-89,camai->bestRotX-20),MAX(0.01F, (bestRange-10)));
		opt3.scName				=	"IC A(-)E(-)R(-)";

		// bestrange - minRange, azi gegen drehrichtung, elevation hoch
		opt4.scSign				=	zVEC3( -1 , 1, -1);
		opt4.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt4.scSequence			=	"RAE";
		opt4.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt4.scEnd				=	zVEC3( MAX(-180, -camai->bestRotY-10), MIN(+89,camai->bestRotX+20),MAX(0.01F, (bestRange-10)));
		opt4.scName				=	"IC A(-)E(+)R(-)";

		// bestrange - maxRange, azi gegen drehrichtung, elevation hoch
		opt5.scSign				=	zVEC3( -1 ,	1, 1);
		opt5.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt5.scSequence			=	"RAE";
		opt5.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt5.scEnd				=	zVEC3(MAX(-180, -camai->bestRotY-10), MIN(+89,camai->bestRotX+20), (bestRange+10));
		opt5.scName				=	"IC A(-)E(+)R(+)";

		// bestrange - maxRange, azi gegen drehrichtung, elevation runter
		opt6.scSign				=	zVEC3( -1, -1, 1);
		opt6.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt6.scSequence			=	"RAE";
		opt6.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt6.scEnd				=	zVEC3(MAX(-180, -camai->bestRotY-10), MAX(-89,camai->bestRotX-20), (bestRange+10));
		opt6.scName				=	"IC A(-)E(-)R(+)";

		// bestrange - maxRange, azi in drehrichtung, elevation runter
		opt7.scSign				=	zVEC3( 1,-1,+1);
		opt7.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt7.scSequence			=	"RAE";
		opt7.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt7.scEnd				=	zVEC3(MIN(+180, -camai->bestRotY+10), MAX(-89,camai->bestRotX-20), (bestRange+10));
		opt7.scName				=	"IC A(+)E(-)R(+)";

		// bestrange - maxRange, azi in drehrichtung, elevation hoch
		opt8.scSign				=	zVEC3( 1,	1,	 +1);
		opt8.scQuality			=	zVEC3( 0.3F,0.3F,0.3F );
		opt8.scSequence			=	"RAE";
		opt8.scStart			=	zVEC3(-camai->bestRotY,		camai->bestRotX,			bestRange);
		opt8.scEnd				=	zVEC3(MIN(+180, -camai->bestRotY+10), MIN(+89,camai->bestRotX+20), (bestRange+10));
		opt8.scName				=	"IC A(+)E(+)R(+)";

		zSEvasionSearchDesc		idealDesc;
		idealDesc.searchFunc	=	AI_FindEvasionSphere;
		idealDesc.searchName	=	"Ideal Cone";
		idealDesc.sphereSearchList.InsertEnd(opt1);
		idealDesc.sphereSearchList.InsertEnd(opt2);
		idealDesc.sphereSearchList.InsertEnd(opt3);
		idealDesc.sphereSearchList.InsertEnd(opt4);
		idealDesc.sphereSearchList.InsertEnd(opt5);
		idealDesc.sphereSearchList.InsertEnd(opt6);
		idealDesc.sphereSearchList.InsertEnd(opt7);
		idealDesc.sphereSearchList.InsertEnd(opt8);
		evasion .InsertEnd			(idealDesc);
	}


	return TRUE;
}

zBOOL zCPathSearch :: FES_PlayerInvisible_Standing(zCArray<zSEvasionSearchDesc> &evasion) 
{
	D_Print("FES Player Invisible (standing)");
	searchOptions.searchFlags |= zPATHSEARCH_USE_PLAYER_MESH;	

	return FES_PlayerTargetInvisible(evasion);
};

zBOOL zCPathSearch :: FES_PlayerInvisible_Rotated(zCArray<zSEvasionSearchDesc> &evasion) 
{
	D_Print("FES Player Invisible (rotated)");

	zSEvasionSearchDesc::zSEvasionSearchOptions opt1,opt2,opt3,opt4;
	
	zBOOL rotatedLeft = moveTracker->GetPlayerMovement() & zPLAYER_ROTATED_LEFT;

	zREAL	a	= camai->bestRotY,
			e	= camai->bestRotX,
			r	= camai->GetBestRange()*100;

	float minRange = camai->GetMinRange()*100;

	float aziEnd, elevEnd;

	// bei linksrotation rechte seitenwinkel, negative range und positive elevation testen
	opt1.scSign			=	zVEC3(rotatedLeft ? 1:-1, 1 ,-1);
	opt1.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt1.scSequence		=	"REA";
	opt1.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt1.scSign[AZI]*30); zClamp(aziEnd,-180.0F,180.0F);
	elevEnd				=   e+(opt1.scSign[ELEV]*40);zClamp(elevEnd,-89.9F,89.9F);
	opt1.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt1.scName			=	rotatedLeft ? "PIR A(+)E(+)R(-)" : "PIR A(-)E(+)R(-)";

	// andere elevation
	opt2.scSign			=	zVEC3(rotatedLeft ? 1:-1, -1 ,-1);
	opt2.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt2.scSequence		=	"REA";
	opt2.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt2.scSign[AZI]*30); zClamp(aziEnd,-180.0F,180.0F);
	elevEnd				=   e+(opt2.scSign[ELEV]*30);zClamp(elevEnd,-89.9F,89.9F);
	opt2.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt2.scName			=	rotatedLeft ? "PIR A(+)E(-)R(-)" : "PIR A(-)E(-)R(-)";

	// andere seite azi
	opt3.scSign			=	zVEC3(rotatedLeft ? -1:1, -1 ,-1);
	opt3.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt3.scSequence		=	"REA";
	opt3.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt2.scSign[AZI]*30); zClamp(aziEnd,-180.0F,180.0F);
	elevEnd				=   e+(opt2.scSign[ELEV]*30);zClamp(elevEnd,-89.9F,89.9F);
	opt3.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt3.scName			=	rotatedLeft ? "PIR A(-)E(-)R(-)" : "PIR A(+)E(-)R(-)";

	// andere seite azi/elev
	opt4.scSign			=	zVEC3(rotatedLeft ? -1:1, 1 ,-1);
	opt4.scQuality		=	zVEC3(0.5F,0.5F,0.5F);
	opt4.scSequence		=	"REA";
	opt4.scStart		=	zVEC3(a,e,r);
	aziEnd				=	a+(opt2.scSign[AZI]*30); zClamp(aziEnd,-180.0F,180.0F);
	elevEnd				=   e+(opt2.scSign[ELEV]*40);zClamp(elevEnd,-89.9F,89.9F);
	opt4.scEnd			=	zVEC3(aziEnd,elevEnd,minRange);
	opt4.scName			=	rotatedLeft ? "PIR A(-)E(+)R(-)" : "PIR A(+)E(+)R(-)";

	zSEvasionSearchDesc		rotDesc;
	rotDesc.searchFunc		=	AI_FindEvasionSphere;
	rotDesc.searchName		=	"Player invisible, rotated";
	rotDesc.sphereSearchList.InsertEnd(opt1);
	rotDesc.sphereSearchList.InsertEnd(opt2);
	rotDesc.sphereSearchList.InsertEnd(opt3);
	rotDesc.sphereSearchList.InsertEnd(opt4);
	evasion .InsertEnd				   (rotDesc);

	return TRUE;
};

zBOOL zCPathSearch :: FES_PlayerTargetInvisible(zCArray<zSEvasionSearchDesc> &evasion) 
{
	D_Print("FES Player Target Invisible");
	searchOptions.searchFlags |= zPATHSEARCH_INCLUDE_PLAYER_TARGET_CHECK;
	return FES_PlayerInvisible_Rotated(evasion);
};

zBOOL zCPathSearch :: FES_CamHitWall(zCArray<zSEvasionSearchDesc> &evasion) 
{
	return TRUE;
};

zBOOL zCPathSearch :: FES_NoEvasionFound(zCArray<zSEvasionSearchDesc> &evasion) 
{
	zSEvasionSearchDesc	panicDesc;
	panicDesc	.searchFunc =   AI_FindEvasionPanic;
	panicDesc	.searchName = "__FP__";
	evasion		.InsertEnd(panicDesc);
	return TRUE;
};

zBOOL zCPathSearch :: EvasionPossible() 
{
	return TRUE;
};


zBOOL zCPathSearch :: IsPointValid (const zPOINT3 &testPos, const int flags,zTPoseFailReason &failReason)
{	
	if (!GetCollisionEnabled()) return TRUE;			// noclip

	// besteht sichtlinie zum target ?
	zBOOL canSeeTarget = FALSE;
	zVEC3 playerOffset = zVEC3(0,0,0);
		//(flags & zPATHSEARCH_USE_PLAYER_FUTURE_POS) ? moveTracker->GetPlayerFuturePos()-moveTracker->GetPlayerPos() : zVEC3(0,0,0);

	if ( flags & zPATHSEARCH_INCLUDE_BOUNDS_CHECK )
	{
		if ( zNotInRange( (moveTracker->GetPlayerPos()-testPos).Length2(), camai->minRange*camai->minRange*100, camai->maxRange*camai->GetMaxRange()*100 ))	{ failReason = zFAILREASON_RANGEBOUND_LEFT; return FALSE;	}
		if ( zNotInRange( moveTracker->GetAzimuth	(testPos)			 , camai->minRotY, camai->maxRotY ))											{ failReason = zFAILREASON_AZIBOUND_LEFT;	return FALSE;	}
	    if ( zNotInRange( moveTracker->GetElevation(testPos)			 , camai->minRotX, camai->maxRotX ))											{ failReason = zFAILREASON_ELEVBOUND_LEFT;	return FALSE;	}
	};

	if ( !(GetIgnoreSearchFlags() & zPATHSEARCH_INCLUDE_PLAYER_CHECK) )
	if ( flags & zPATHSEARCH_INCLUDE_PLAYER_CHECK )
	{
		if ( flags & zPATHSEARCH_USE_PLAYER_MESH ) 
		{
			// mesh check
			camai->raysCasted++;
			zPOINT3 trgtHead = moveTracker->GetPlayerHead()+playerOffset;
			camai->DrawClipLine(trgtHead,testPos,GFX_RED);
			if (world->TraceRayFirstHitCache(trgtHead, (testPos-trgtHead),target,standardTraceFlags,&rayCache1))   		{ failReason = zFAILREASON_PLAYER_INVISIBLE; return FALSE;	}

			camai->raysCasted++;
			zPOINT3 trgtHipLeft = moveTracker->GetPlayerHipLeft()+playerOffset;
			camai->DrawClipLine(trgtHipLeft,testPos,GFX_RED);
			if (world->TraceRayFirstHitCache(trgtHipLeft, (testPos-trgtHipLeft),target,standardTraceFlags,&rayCache1))  { failReason = zFAILREASON_PLAYER_INVISIBLE; return FALSE;	}

			camai->raysCasted++;
			zPOINT3 trgtHipRight = moveTracker->GetPlayerHipRight()+playerOffset; 
			camai->DrawClipLine(trgtHipRight,testPos,GFX_RED);
			if (world->TraceRayFirstHitCache(trgtHipRight, (testPos-trgtHipRight),target,standardTraceFlags,&rayCache1)) { failReason = zFAILREASON_PLAYER_INVISIBLE; return FALSE;	}
			canSeeTarget = TRUE;
		}
		else
		{
			camai->raysCasted++;
			zPOINT3 testPlayerPos = moveTracker->GetPlayerPos() + playerOffset;
			camai->DrawClipLine(testPlayerPos,testPos,GFX_ORANGE);
			if (world->TraceRayFirstHitCache(testPlayerPos, (testPos-testPlayerPos),target,standardTraceFlags,&rayCache1))		{ failReason = zFAILREASON_PLAYER_INVISIBLE; return FALSE;	}
			canSeeTarget = TRUE;
		}
	} 
	else canSeeTarget = TRUE;

	if ( !(GetIgnoreSearchFlags() & zPATHSEARCH_INCLUDE_PLAYER_TARGET_CHECK) )
	if ( flags & zPATHSEARCH_INCLUDE_PLAYER_TARGET_CHECK ) 
	{

		// FIXME: evtl. muss auch die Rotation des Spielers vorrausberechnet werden, denn wenn oben das Flag
		// zPATHSEARCH_INCLUDE_PLAYER_FUTURE_POS gesetzt ist, ist hier aber der Spieler Focus der derzeitigen, und nicht
		// der zukünftigen Position berücksichtigt.
		zMAT4 camSaveTrafo = zCCamera::activeCam->GetVob()->trafoObjToWorld;
		zVALUE xscr,yscr;
		camai->raysCasted++;

		// besteht sichtlinie zum target ?
		if (!canSeeTarget) camai->DrawClipLine(moveTracker->GetPlayerPos(),testPos,GFX_ORANGE);
		if ( canSeeTarget || !world->TraceRayFirstHitCache(moveTracker->GetPlayerPos()+playerOffset, (testPos - moveTracker->GetPlayerPos()+playerOffset),zCAICamera::GetCurrent()->GetTarget(),standardTraceFlags,&rayCache1) )  
		{ 
			// ja, nun checken, ob der spieler sichtpunkt vom neu aufgebauten camera frustum in dessen viewport liegt
			// achtung: das ist nur ein ungenauer check, da das nur in modes funktionieren wird, in denen
			// die camera direkt auf den Spieler schaut. Evtl. genauere Matrix mit offsetorienteriung benutzen
			// FIXME: Perf.
			if ( (moveTracker->GetPlayerPos()+playerOffset) == testPos) goto leave_target_search;

			zMAT4 camTrafo = GetPoseOfHeading( testPos, (moveTracker->GetPlayerPos()+playerOffset-testPos).Normalize());
			zCCamera::activeCam->GetVob()->SetTrafoObjToWorld( camTrafo );
			{
				zCCamera::activeCam->Activate();

				zPOINT3 pcs = zCCamera::activeCam->camMatrix * moveTracker->GetPlayerTargetPos();
				// hinter near clipping plane ? dann kann man gleich raus hier
				if (pcs[VZ]<0) 
				{
					zCCamera::activeCam->GetVob()->SetTrafoObjToWorld( camSaveTrafo );
					// folgende Zeile muss eigentlich rein, da sonst die render camera nicht wieder vollständig hergestellt ist.
					// Da die Camera AI aber nach dem Render Vorgang aufgerufen wird, 
					// keine weiteren Transformationen bzw. Frustum Checks mehr stattfinden, und
					// die Internas im nächsten Frame wiederhergestellt werden, kann man sich den Extra Call sparen
					//zCCamera::activeCam->Activate();		 
					failReason = zFAILREASON_PLAYER_TARGET_INVISIBLE;
					return FALSE;
				}
				
				zCCamera::activeCam->Project(&(pcs), xscr, yscr); 

				if ( !zCCamera::activeCam->InViewport(zVEC2(xscr,yscr)) ) 
				{
					zCCamera::activeCam->GetVob()->SetTrafoObjToWorld( camSaveTrafo );
					failReason = zFAILREASON_PLAYER_TARGET_INVISIBLE;
					//zCCamera::activeCam->Activate();		 
					return FALSE;
				}
			}
			zCCamera::activeCam->GetVob()->SetTrafoObjToWorld( camSaveTrafo );
			//zCCamera::activeCam->Activate();		 
		} 
		else { failReason = zFAILREASON_PLAYER_INVISIBLE; return FALSE; };
	}

leave_target_search:

	if ( flags & zPATHSEARCH_INCLUDE_CAM_CHECK )
	{
		// kann die aktuelle camera position von der testposition gesehen werden ?
		camai->raysCasted++;
		camai->DrawClipLine(moveTracker->GetCamPos(),testPos,GFX_WHITE);
		if (world->TraceRayFirstHitCache(testPos, (moveTracker->GetCamPos()-testPos),(zCVob *)0,standardTraceFlags,&rayCache2)) { failReason = zFAILREASON_CAM_INVISIBLE; return FALSE;	}
	}

	
	if ( !(GetIgnoreSearchFlags() & zPATHSEARCH_INCLUDE_NEARWALL_CHECK ) )
	if ( flags & zPATHSEARCH_INCLUDE_NEARWALL_CHECK )
	{
		// ist die testposition in der nähe einer wand ? (nötig, um textur artefakte zu vermeiden)
		if ( IsPointNearWall(testPos) )			{ failReason = zFAILREASON_CAM_HIT_WALL; return FALSE;	}
	}
		
	failReason = zFAILREASON_NONE;
	return TRUE;

}


zBOOL zCPathSearch::IsPointNearWall(const zPOINT3 &testPos)
{
	if (!GetCollisionEnabled()) return FALSE;

	if (world->IsCompiled() /*&& (world->GetMasterFrameCtr()&2)==0*/) 
	{
		zTBSphere3D  camSphere;
		camSphere.center = testPos;
		camSphere.radius = CAMSPHERE_DIAMETER*0.5F;
		zTBBox3D  camBox; 

		camBox.mins = testPos - (zVEC3(1,1,1) * camSphere.radius*1.3F);
		camBox.maxs = testPos + (zVEC3(1,1,1) * camSphere.radius*1.3F);	

		zCPolygon **polyList;
		int	numPolys=0;

		if (world->GetBspTree()->GetRoot()->CollectPolysInBBox3D(camBox,polyList,numPolys)) 
		{
			zCMaterial*		mat = 0;
			int				planeClass;
			for (int i=0; i<numPolys; i++) 
			{
				mat = polyList[i]->GetMaterial();
				if ( mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE ||
					(mat->GetTexture() && mat->GetTexture()->HasAlphaChannel())) 
					continue;
				 
				planeClass = polyList[i]->GetPlane().ClassifyPoint(testPos);

				if ( (planeClass == zPLANE_INFRONT || planeClass == zPLANE_ONPLANE) &&
					  polyList[i]->CheckBSpherePolyIntersection(camSphere) )  
				{
					return TRUE;
				}
			}
		}
	}
		
	return FALSE;
}

zBOOL zCPathSearch :: LineOfSight	(const zPOINT3 &from,const zPOINT3 &to)
{
	if (!GetCollisionEnabled()) return TRUE;

	camai->raysCasted++;
	if (world->TraceRayFirstHit(from, (to- from),target,standardTraceFlags)) 
	{
		if ( world->traceRayReport.foundVob	&& CanIgnoreVob(world->traceRayReport.foundVob))
			return TRUE;
		return FALSE; 
	}
	return TRUE;
}

zBOOL	zCPathSearch::CorrectPosForNearClip(zPOINT3 &center)
{
	// rays abschiessen links/rechts/oben/unten/vorne
	// dieser test ist nicht nötig, wenn der nearclip wert der camera 1 beträgt
	if (!zCCamera::activeCam)					return FALSE;
	if (!zCCamera::activeCam->GetVob())			return FALSE;

	// FIXME: dirty method to access the default near clip value
	zCCamera *cam		= zNEW(zCCamera);
	zREAL origMinZ		= cam->GetNearClipZ();
	delete cam;
	cam = 0;

	if (origMinZ==1.0f) return FALSE;


	zPOINT3 polyPoint; 
	zPOINT3 startCenter = center;
	zREAL	radius		= origMinZ+1;
	float	radius2		= radius * radius;

	{  // cam too near to walls (polys in camsphere)
		// find which poly lies nearest to target
		
		zTBSphere3D camSphere;
		camSphere.center = center;
		camSphere.radius = radius;
		zTBBox3D  camBox; 

		camBox.mins = center - (zVEC3(1,1,1) * radius*1.4F);
		camBox.maxs = center + (zVEC3(1,1,1) * radius*1.4F);	

		zCPolygon **polyList; 
		zPOINT3     nearestPt;
		zCPolygon  *nearestPoly	= 0;		
		
		float lastDistance		= FLT_MAX;
		int	  numPolys			= 0;
		int   numNearPolys		= 0;
		zVEC3 avgNormal			= zVEC3(0,0,0);

		world->GetBspTree()->GetRoot()->CollectPolysInBBox3D(camBox,polyList,numPolys);

		if (numPolys == 0) 		
		{
			zCCamera::activeCam->SetNearClipZ(origMinZ);
			return FALSE;
		}


		for (int i=0; i<numPolys; i++) 
		{
			int	planeClass;
			zCMaterial *mat = polyList[i]->GetMaterial();

			if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE ||
				(mat->GetTexture() && mat->GetTexture()->HasAlphaChannel()) || mat->GetNoCollDet()) 
				continue;

			planeClass = polyList[i]->GetPlane().ClassifyPoint(center);

			if ( (planeClass == zPLANE_INFRONT || planeClass == zPLANE_ONPLANE) &&
				 polyList[i]->CheckBSpherePolyIntersection(camSphere)  )
			{
				zPOINT3 cross = GetPolyNearestPoint(polyList[i], center);
				float dist = (cross-center).Length2();
				// FIXME: test auf dist <= radius2 sollte nicht nötig sein, da CheckBSpherePolyInters
				// ausreichen müsste
				if (  dist <= radius2 && dist < lastDistance ) 
				{
					lastDistance = dist; 
					nearestPoly = polyList[i];
					polyPoint   = cross;
					avgNormal  += polyList[i]->GetNormal();
					numNearPolys++;
				}
			}
		}

		if (nearestPoly == 0) 
		{
			zCCamera::activeCam->SetNearClipZ(origMinZ);
			return FALSE;
		}
		// so hier gibt es nun ein paar nearPolys.
		// per vereinfachung nehmen wir nun die durchschnittsnormale und bewegen 
		// uns soweit in die richtung des vectors bis der abstand gerade der radius ist
		//avgNormal /= numNearPolys;
		//avgNormal.NormalizeSafe();

		// besser, aber nicht immer befriedigend
		//center += avgNormal * ((radius - sqrt(lastDistance)));
		zREAL realLastDist = sqrt(lastDistance);
		if (realLastDist<1.0f) 
		{
			//center += avgNormal * (radius - realLastDist);
			realLastDist = 1.0f;
		};

		zCCamera::activeCam->SetNearClipZ(realLastDist);

		return TRUE;

		//D_Print(zSTRING("sphere"),D_SCREEN);
	} 
	return FALSE;
};

zBOOL zCPathSearch::AdjustCenterSphere(zPOINT3 &center, const zPOINT3 &b, const float radius)
{
	// Adjust a spheres range towards a given end position, end position must be valid
	// returns TRUE if a position has been found, false otherwise
	if (!GetCollisionEnabled()) return FALSE;

#if 1

	zPOINT3 newCenter;
	
	if ((center-b).Length()==0) return FALSE;
	zVEC3 bToCenter = (center-b).Normalize();
	
	newCenter = center + (radius * bToCenter);

	camai->raysCasted++;
	camai->DrawClipLine(center,b,GFX_PALEGREEN);

	if (world->TraceRayNearestHit(b, (newCenter-b),target,standardTraceFlags)) 
	{
		if ( world->traceRayReport.foundVob && CanIgnoreVob(world->traceRayReport.foundVob ) )
			return TRUE;

		if ((world->traceRayReport.foundIntersection - b).Length2()>=radius*radius)
		{
			center = world->traceRayReport.foundIntersection + (radius * (-bToCenter));
		}
		else
		{
			center = b;
		}
	}
	else return FALSE;

	return TRUE;

#else
	// FIXME: folgender Code ist buggy. Test: Umschau Camera mit grösserer Distanz in einer Umgebung mit vielen Polys
	// führt zum Emergency Abbruch des Algos bei (s<0.01) -> teuer und fehlerhaft
	// evtl. ist das FIXME ungültig, da ein falsches TraceRayFirstHit statt ein richtiges TraceRayNearestHit
	// benutzt wurde. Checken im Testlevel im Raum mit dem unebenen Boden und der Umschaukamera
	// check if false position
	// Update 1.26b: Code ist buggy! 
	zPOINT3 polyPoint; 
	zPOINT3 startCenter = center;
	float	radius2 = radius * radius;
	float   minDist = radius + 1;
	do 
	{
		camai->raysCasted++;
		camai->DrawClipLine(center,b,GFX_PALEGREEN);
		if (world->TraceRayNearestHitCache(b, (center-b),target,standardTraceFlags,&rayCache3)) 
		{
			// 1st case: LOS failed. Intersection with world easy to find
			//D_Print(zSTRING("failed los:") ,D_SPY);
			polyPoint = world->traceRayReport.foundIntersection;
			//D_Print(zSTRING("LOS"),D_SCREEN);
		}
		else 
		{  // 2nd case: cam too near to walls (polys in camsphere)
			// find which poly lies nearest to target
			
			zTBSphere3D camSphere;
			camSphere.center = center;
			camSphere.radius = radius;
			zTBBox3D  camBox; 

			camBox.mins = center - (zVEC3(1,1,1) * radius*1.4F);
			camBox.maxs = center + (zVEC3(1,1,1) * radius*1.4F);	

			zCPolygon **polyList; 
			zCPolygon *nearestPoly = 0;		
			zPOINT3   nearestPt;
			float lastDistance = FLT_MAX;
			int	  numPolys=0;

			world->GetBspTree()->GetRoot()->CollectPolysInBBox3D(camBox,polyList,numPolys);
			if (numPolys == 0) break;

			for (int i=0; i<numPolys; i++) 
			{
				int	planeClass;
				zCMaterial *mat = polyList[i]->GetMaterial();

				if (mat->GetAlphaBlendFunc()!=zRND_ALPHA_FUNC_NONE ||
					(mat->GetTexture() && mat->GetTexture()->HasAlphaChannel())) 
					continue;

				planeClass = polyList[i]->GetPlane().ClassifyPoint(center);

				if ( (planeClass == zPLANE_INFRONT || planeClass == zPLANE_ONPLANE) &&
				     polyList[i]->CheckBSpherePolyIntersection(camSphere)  )
				{
					zPOINT3 cross = GetPolyNearestPoint(polyList[i], center);
					float dist = (cross-center).Length2();
					// FIXME: test auf dist <= radius2 sollte nicht nötig sein, da CheckBSpherePolyInters
					// ausreichen müsste
					if (  dist <= radius2 && dist < lastDistance ) 
					{
						lastDistance = dist; 
						nearestPoly = polyList[i];
						polyPoint   = cross;
					}
				}
			}

			if (nearestPoly == 0) break;
			//D_Print(zSTRING("sphere"),D_SCREEN);
		} 

		zVEC3 CMinT  = center - b;
		zVEC3 IMinC  = polyPoint - center;
		float nenner = CMinT * CMinT;
		if (nenner == 0) return FALSE;		// emergency
		float pHalve = (CMinT*IMinC)/nenner;
		float q		 = ((IMinC * IMinC)-(minDist*minDist))/nenner;
		float root	 = (float) sqrt( (float)(pHalve*pHalve) - q );
		float s   	 = (- pHalve + root) > 0 ? (- pHalve + root) : (- pHalve - root);
		//D_Print(zSTRING("s:") +zSTRING(s),D_SCREEN);
		if (s < 0.01F || s > 0.96F) 
		{
			center = startCenter;
			return FALSE;
		}
		center = Lerp(s, center, b);
	}
	while (1);
	return TRUE;
#endif

}

zPOINT3& zCPathSearch :: GetPolyNearestPoint (zCPolygon *poly,const zPOINT3 &checkPt) const
{
	// findet den nächsten Punkt auf einem poly zu einem gegebenen Punkt
	static zPOINT3 res;
	float alpha; 
	float minDist	= FLT_MAX;
	float checkPtDistToWorldOrigin = (checkPt - zPOINT3(0,0,0)).Length();

	// wenn der Fusslotpunkt auf die PolyEbene durch den Checkpunkt läuft, sind wir fertig
	if ( !poly->CheckRayPolyIntersection(checkPt, checkPt - (2000000.0f * (poly->GetNormal())), res, alpha) ) 
	{
		// nein, also den Abstand zu allen Geraden und (falls nötig) Vertices messen
		zTPlane EOrthG;
		zVEC3   inters,ray,rayOrigin;

		// alle polykanten abgehen 
		for (int i=1; i<poly->polyNumVert; i++) 
		{
			rayOrigin		= poly->GetVertexPtr(i-1)->position;
			ray				= (poly->GetVertexPtr(i)->position - rayOrigin);
			// ebene die orthog. zur polykante ist, und durch den checkpt. geht, aufspannen
			EOrthG.normal	= ray.NormalizeSafe();
			EOrthG.distance = checkPtDistToWorldOrigin;
			// wenn die kante die ebene schneidet, checken wir ob der Schnittpunkt bisher der naheste
			// Punkt ist, falls nicht, checken wir ob die Distanz zum 1. Vertex der Kante bisher 
			// der naheste ist
			if ( !EOrthG.Intersection( rayOrigin, ray, inters ) ) 
			{
				float dist	= (rayOrigin-checkPt).Length2();
				if ( dist < minDist ) 
				{ 
					res		= rayOrigin;
					minDist = dist;
				}
			}
			else
			{
				float dist	= (inters-checkPt).Length2();
				if ( dist < minDist ) 
				{ 
					res		= inters;
					minDist = dist;
				}
			}
		}
		// Dasselbe mit der letzten Polykante
		rayOrigin		= poly->GetVertexPtr(poly->polyNumVert-1)->position;
		ray				= (poly->GetVertexPtr(0)->position - rayOrigin);
		EOrthG.normal	= ray.NormalizeSafe();
		EOrthG.distance = checkPtDistToWorldOrigin;
		if ( !EOrthG.Intersection( rayOrigin, ray, inters ) ) 
		{
			float dist	= (rayOrigin-checkPt).Length2();
			if ( dist < minDist ) 
			{ 
				res		= rayOrigin;
				minDist = dist;
			}
		}
		else
		{
			float dist	= (inters-checkPt).Length2();
			if ( dist < minDist ) 
			{ 
				res		= inters;
				minDist = dist;
			}
		}
	}
	return res;
};

#pragma warning( default : 4244 )  
