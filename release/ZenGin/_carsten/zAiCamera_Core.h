/****************************************************************
*
* Camera Artificial Intelligence
* File          : zAICamera_Core.h (AI)
* Projekt       : Gothic
* Autor         : Carsten Edenfeld
*
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations:
*****************************************************************
- missing features:
*****************************************************************
- comments:  
****************************************************************/
#ifndef __zAICAM_CORE__
#define __zAICAM_CORE__

#include "zKBSplines.h"

// readability defines
const	int		AZI						= 0;
const	int		ELEV					= 1;
const	int		RANGE					= 2;

// forward declarations
struct zSEvasionSearchDesc;
struct zSPathSearchState_Internal;
class  zCMovementTracker;
class  zCAICamera;

// function pointer
typedef zBOOL (*zTPathSearchFunc)(const zSEvasionSearchDesc &searchDesc);

// zSEvasionSearchDesc. Core AI search priority descriptor
struct zSEvasionSearchDesc 
{
public:
	struct zSEvasionSearchOptions	
	{ 
		zVEC3				scSign;								// spherical coords sign
		zVEC3				scQuality;							// quality for each spherical coord
		zVEC3				scStart;
		zVEC3				scEnd;
		zSTRING				scSequence;							// AER,AER,ERA,EAR,ARE
		zSTRING				scName;
	};

	zTPathSearchFunc						searchFunc;
	zSTRING									searchName;
	zCArray		<zSEvasionSearchOptions>	sphereSearchList;
};


enum zTPoseFailReason 
{ 
	// basic interface
	zFAILREASON_NONE						= 0,
	zFAILREASON_PLAYER_INVISIBLE			= 1	<< 0, 
	zFAILREASON_CAM_INVISIBLE				= 1	<< 1, 
	zFAILREASON_PLAYER_TARGET_INVISIBLE		= 1	<< 2, 
	zFAILREASON_CAM_HIT_WALL				= 1	<< 3, 
	zFAILREASON_NO_EVASION_FOUND			= 1 << 4,
	// advanced interface
	zFAILREASON_BADSCENE_STAND				= 1	<< 5, 
	zFAILREASON_BADSCENE_MELEE				= 1	<< 6, 
	zFAILREASON_BADSCENE_RANGED				= 1	<< 7,
	zFAILREASON_BADSCENE_MAGIC				= 1	<< 8, 
	zFAILREASON_BADSCENE_CINEMA				= 1 << 9,
	zFAILREASON_VOB_CROSS_LINEOFSIGHT		= 1	<< 10, 
	zFAILREASON_NPC_CROSS_LINEOFSIGHT		= 1	<< 11, 
	zFAILREASON_VOB_HIT_CAM					= 1	<< 12, 
	zFAILREASON_NPC_HIT_CAM					= 1	<< 13, 
	zFAILREASON_AZIBOUND_LEFT				= 1	<< 14, 
	zFAILREASON_ELEVBOUND_LEFT				= 1	<< 15, 
	zFAILREASON_RANGEBOUND_LEFT				= 1	<< 16, 
	zFAILREASON_TARGET_NOT_IN_FRUSTUM		= 1	<< 17,
	zFAILREASON_PLAYER_BEAMED				= 1 << 18
};

// varius path interpolation modes in score order
enum zTPathLerpMode
{
	zPATH_LERP_NONE							= 0,			// no interpolation possible, target point is invalid
	zPATH_LERP_CUSTOM_JUMP					= 1 << 0,
	zPATH_LERP_JUMP							= 1	<< 1,		// switch possible
	zPATH_LERP_CUSTOM						= 1	<< 2,		// custom interpolation	(shoulder cam, 1st person cam, etc.)
	zPATH_LERP_SPLINE						= 1	<< 3,		// spline interpolation (e.g. special case: camera should rotate from -90 to 0 deg. through player, because no direct line to the ideal position is possible)
	zPATH_LERP_LINE							= 1	<< 4,		// direct path interpolation possible
	zPATH_LERP_ARC							= 1	<< 5,		// arc interpolation (e.g. quat slerp) possible. Best Mode
	zPATH_LERP_MAX							= 1 << 6
};

enum zTPathSearchFlags
{
	zPATHSEARCH_INCLUDE_NONE				= 0,
	zPATHSEARCH_INCLUDE_CAM_CHECK			= 1	<< 1,
	zPATHSEARCH_INCLUDE_PLAYER_CHECK		= 1	<< 2,
	zPATHSEARCH_INCLUDE_PLAYER_TARGET_CHECK = 1	<< 3,
	zPATHSEARCH_INCLUDE_NEARWALL_CHECK		= 1	<< 4,
	zPATHSEARCH_INCLUDE_VOB_CHECK			= 1	<< 5,
	zPATHSEARCH_INCLUDE_NPC_CHECK			= 1	<< 6,
	zPATHSEARCH_INCLUDE_INFRUSTUM_CHECK		= 1	<< 7,
	zPATHSEARCH_INCLUDE_BOUNDS_CHECK		= 1 << 8,
	zPATHSEARCH_USE_PLAYER_FUTURE_POS		= 1	<< 9,
	zPATHSEARCH_USE_PLAYER_MESH				= 1	<< 10,
	zPATHSEARCH_USE_DYNCOLLISION			= 1 << 11
};

struct zSPathSearchResult
{
public:
	zBOOL				foundEvasion;
	zPOINT3				p1,p2;
	zCQuat				r1,r2;
	zTPathLerpMode		bestLerpMode;
	int					lerpModes;			// all result lerpModes
	zCArray<zCPositionKey*>resPath;			// resulting path for zPATH_LERP_SPLINE
	zREAL				avgScore;			// average score for all sphere segment searches
	zREAL				bestScore;			// best score found in a sphere segment
	zREAL				veloTrans;
	zREAL				veloRot;

	void		Initialize()												{	memset(this,0,sizeof(this)); };
};

struct zSPathSearchState
{
	float			startAzi,	startElev,	startRange;
	float			endAzi	,	endElev,	endRange;
	float			bestAzi,	bestElev,	bestRange;
	zMAT4			trafoCamToWorld;								// end orientation for zPATH_LERP_CUSTOM;
	zTPathLerpMode	bestLerpMode;
	int				lerpModes;
	zREAL			totalScore;
	zSTRING			sphereSearchName;
	zSTRING			sphereSearchSegment;
};



extern  zTPoseFailReason failReasonDummy;

struct zSPathSearchState_Internal
{
	zREAL			maxRange;
	zVEC3			foundPos;
	zMAT4			trafoCamToWorld;								// end orientation for zPATH_LERP_CUSTOM;
	zTPathLerpMode	bestLerpMode;
	zREAL			scoreLerpMode;				// Bewertung des durchschnittlichen gefundenen Lerpmodes
	zREAL			scoreDistToIdealPos;		// Wie weit ist die Sphere von der Idealpos. entfernt ?
	zREAL			scoreFoundNumNpcs;			// Anzahl der NPCs, die in diesem Segment  sichtbar sind. 1: viele sind sichtbar, 0: keine sind sichtbar
	zREAL			scoreFoundNumBBoxes;		// Anzahl der BBoxes, die sich in diesen Segment befinden (trivial in, oder nur bis zur bestimmten grösse)
	zREAL			scoreFoundNumTargets;		// Anzahl der Targets, die in diesem Segment  sichtbar sind. 1: alle sind sichtbar, 0: keine sind sichtbar
	zREAL			scorePlayerVisibility;		
	zREAL			scoreDistToLastEvasion;
	zREAL			totalScore;					// gesamt Score dieses sphere segments
};


class zCSphereCoordsCache
{
public:
	zCSphereCoordsCache();
	~zCSphereCoordsCache();

	zBOOL	GetSphereCoordLazy(const float &azi, const float &elev, const float &range,zSPathSearchState_Internal*&cacheState);
	void	GetBestScoredSearch(float &azi, float &elev, float &range, zSPathSearchState_Internal *&cachedState);
	void	EmptyList		  ()						{};
	void	DeleteList		  ();

	struct zSRangeSphereCoord
	{
		float range;
		zSPathSearchState_Internal searchState;
	};

	struct zSElevSphereCoord
	{
		float elev;
		float maxRange;
		zCArraySort<zSRangeSphereCoord*> rangeCoords;
	};

	struct zSAziSphereCoord
	{
		float azi;
		zCArraySort<zSElevSphereCoord*> elevCoords;
	};

	zCArraySort<zSAziSphereCoord*>	aziCoords;

};



// zCPathSearch Class. Responsible for finding evasions under giving circumstances (surroundings, playermovement)
class zCPathSearch
{
friend class zCAICamera;
friend class zCMovementTracker;
public:

	// struct zSPathSearchOptions. given as parameter into zCPathSearch
	struct zSPathSearchOptions
	{
		// which checks to include
		int					searchFlags;					// Typ: zTPathSearchFlags
		zTPoseFailReason	poseFailReason;
		zTPathLerpMode		minLerpMode;					// stops search immediately if this lerp mode found
		zREAL				bestScore;						// stops sphere segment search if this score reached
		zREAL				minScore;						// if bestScore could not be reached,accepts any evasions over this score

		// boundaries
		float				startAzi,	startElev,	startRange;
		float				endAzi	,	endElev,	endRange;
		// further options
		zREAL				quality;

		void				SetDefaults()
		{
			searchFlags			= zPATHSEARCH_INCLUDE_CAM_CHECK | zPATHSEARCH_INCLUDE_NEARWALL_CHECK | zPATHSEARCH_INCLUDE_PLAYER_CHECK;
			poseFailReason		= zFAILREASON_PLAYER_INVISIBLE;
			minLerpMode			= zPATH_LERP_LINE;			// break at first found line lerp 
			minScore			= 0;					
			bestScore			= 1;
			startAzi			= -180;
			startElev			= -89.99999F;
			startRange			= 1;
			endAzi				= +180;
			endElev				= +89.99999F;
			endRange			= 4;
			quality				= 1;
		};
	};


	// interface aicam/pathsearch
	static zCPathSearch*		GetSearch	();	
	static zSPathSearchResult*	GetReport	();	
	
	void			CamVobChanged			();
	void			TargetChanged			();
	void			SetAICamera				(zCAICamera* camera);
	void			SetOptions				(zSPathSearchOptions &options)	{ searchOptions = options;		};
	zBOOL			GetCollisionEnabled		()								{ return collisionEnabled;		};
	void			SetCollisionEnabled		(const zBOOL enabled)			{ collisionEnabled= enabled;	};

	zBOOL			FindBestEvasion			(zSPathSearchOptions &options); // 1.0 -> best possible
	zBOOL			EvasionPossible			();

	// public funcs for core ai
	zBOOL			SphereSearch			(const zSEvasionSearchDesc &searchDesc);
	zBOOL			SwitchSearch			(const zSEvasionSearchDesc &searchDesc);
	zBOOL			ShoulderSearch			(const zSEvasionSearchDesc &searchDesc);
	zBOOL			PanicSearch				(const zSEvasionSearchDesc &searchDesc);
	zBOOL			CorrectPosForNearClip(zPOINT3 &center);

protected:
	zCPathSearch(const zCPathSearch&)				{};
	zCPathSearch& operator = (const zCPathSearch&)  { return *this;};

	// main rotation / translation funcs during normal AI
	zBOOL			IsPointValid		(const zPOINT3 &testPos, const int flags,zTPoseFailReason &failReason = failReasonDummy);		
	zBOOL			IsPointNearWall		(const zPOINT3 &p);
	zBOOL			IsIdealOrientation	();
	zBOOL			IsIdealRange		();

	// utility functions 
	zBOOL			AdjustCenterSphere	(zPOINT3 &center, const zPOINT3 &maxRangePos, const float radius = CAMSPHERE_DIAMETER * 0.5F );
	zPOINT3&		GetPolyNearestPoint (zCPolygon *poly,const zPOINT3 &checkPt) const;
	zBOOL			LineOfSight			(const zPOINT3 &from,const zPOINT3 &to);

	// quaternion related
	zCQuat&			GetCamRotRelToTarget		(const float &azi,const float &elev);
	zPOINT3			DoSlerpRotQuat				(const zCQuat &startRot, const zCQuat &endRot, const float &rotTime,const float &range);

private:

	zCPathSearch	();

	zBOOL			FindEvasionSequence			(zCArray<zSEvasionSearchDesc> &evasionList); 
	
	zBOOL			FES_PlayerInvisible_Moved	(zCArray<zSEvasionSearchDesc> &evasionList);
	zBOOL			FES_PlayerInvisible_Moved_FW(zCArray<zSEvasionSearchDesc> &evasionList);
	zBOOL			FES_PlayerInvisible_Moved_BW(zCArray<zSEvasionSearchDesc> &evasionList);
	zBOOL			FES_PlayerInvisible_Rotated (zCArray<zSEvasionSearchDesc> &evasionList);
	zBOOL			FES_PlayerInvisible_Standing(zCArray<zSEvasionSearchDesc> &evasionList);
	zBOOL			FES_PlayerTargetInvisible	(zCArray<zSEvasionSearchDesc> &evasion);
	zBOOL			FES_CamHitWall				(zCArray<zSEvasionSearchDesc> &evasion);
	zBOOL			FES_NoEvasionFound			(zCArray<zSEvasionSearchDesc> &evasion);
	zBOOL			FES_IdealCone				(zCArray<zSEvasionSearchDesc> &evasion);
	zPOINT3&		GetLastTriedPosition		()										{ return lastTriedPosition;	};
	void			CalcStateScores				(zSPathSearchState &state);
	void			SetIgnoreSearchFlags		(const int flags)						{ ignoreSearchFlags = flags;};
	int				GetIgnoreSearchFlags		() const								{ return ignoreSearchFlags;	};



	zSPathSearchState	bestSearchState;
	zSPathSearchState	lastSearchState;
	int					ignoreSearchFlags;

	zTPathLerpMode	GetBestLerpMode			(const zSPathSearchState &state);
	zTPathLerpMode	GetBestLerpMode			(const zPOINT3 &startPos, const zPOINT3 &endPos);

	zBOOL			FindFirstEvasion		(zSPathSearchOptions &options);
	zBOOL			CanEvadeTo				(zSPathSearchState &searchState);


	zCAICamera*			camai;
	zCVob*				camVob;
	zCVob*				target;
	zCWorld*			world;
	zBOOL				collisionEnabled;
	zSPathSearchOptions searchOptions;
	zSPathSearchResult	evasionSearchReport;
	zCMovementTracker*	moveTracker;
	zCSphereCoordsCache searchCache;
	zPOINT3				lastTriedPosition;

	zTBSphere3D			POISphere;				// minimal sphere containing all POI's

	// array of search funcs
	zCArray<zTPathSearchFunc*>	searchFuncs;			
};





#endif