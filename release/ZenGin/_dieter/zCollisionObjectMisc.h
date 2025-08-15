/******************************************************************************** 
 
     $Workfile:: zCollisionObjectMisc $                $Date:: 13.02.01 17:05   $
     $Revision:: 24                   $             $Modtime:: 13.02.01 16:39   $
        Author:: Hildebrandt
    Subproject:: ZenGin
     Copyright:: 1998-2001, Piranha Bytes GmbH
 
   Description:
   Collection of zCCollsionObject subclasses.
   created       : 8.12.2000

 * $Log: /current_work/ZenGin/_Dieter/zCollisionObjectMisc.h $
 * 
 * 24    13.02.01 17:05 Moos
 * Diego-Bewegt-Sich-Im-OC-keinen-Millimeter-wegen-Höhenangst-Fix
 * 
 * 23    12.02.01 18:40 Hildebrandt
 * 
 * 22    6.02.01 10:30 Moos
 * 
 * 21    6.02.01 9:51 Moos
 * 
 * 20    3.02.01 2:19 Hildebrandt
 * 
 * 19    22.01.01 20:01 Moos
 * 
 * 18    19.01.01 21:20 Moos
 * 
 * 17    17.01.01 1:46 Hildebrandt
 * 
 * 16    16.01.01 17:33 Moos
 * 
 * 15    16.01.01 11:30 Moos
 * 
 * 14    15.01.01 17:30 Hildebrandt
 * 
 * 13    15.01.01 16:53 Hildebrandt
 * 
 * 12    15.01.01 3:55 Hildebrandt
 * 
 * 11    14.01.01 16:36 Hildebrandt
 * 
 * 10    12.01.01 12:38 Moos
 * 
 * 9     12.01.01 3:23 Hildebrandt
 * 
 * 8     11.01.01 18:45 Hildebrandt
 * 
 * 7     21.12.00 16:07 Moos
 * 
 * 6     20.12.00 21:15 Moos
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
/// @version $Revision: 24 $ ($Modtime: 13.02.01 16:39 $)

// ============================================================================================================

#ifndef __ZCOLLISIONOBJECTMISC_H__
#define __ZCOLLISIONOBJECTMISC_H__

#ifndef __ZRAYCACHE_H__
#include <zRayCache.h>
#endif

// ============================================================================================================

class  zCVob;
class  zCVisual;
struct zTTraceRayReport;

// ============================================================================================================

class zCCollObjectBase : public zCCollisionObject {
public:
	static void		zCCFASTCALL	S_RegisterCollisionTestFuncs			(zCCollisionDetector* collisionDetector);
	static zREAL	zCCFASTCALL	S_CalcAdaptiveCollStepFromVisualBBox	(zCVisual *visual);
	static void		zCCFASTCALL	S_CalcGeneric_CollNormal_ContactPoint	(const zCVob* vob0, const zCVob* vob1, zCCollisionReport &collReport);

	// zCCollisionObject interface
	void			zCCFASTCALL GetLargestBBox3DLocal					(zTBBox3D &bbox3DLocalOut);
	
	//
	zCVob*						GetVob									() const	{ return static_cast<zCVob*>(this->GetClientData()); };
};

// ============================================================================================================
// ============================================================================================================

class zCCollObjectUndef : public zCCollObjectBase {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectUndef)
public:
};

// ============================================================================================================

class zCCollObjectPoint : public zCCollObjectBase {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectPoint)
public:
	zCCollObjectPoint() {};
	// zCCollisionObject interface
	void		zCCFASTCALL		DetectCollisionsSelf	(const zCArray<zCCollisionObject*>& otherCollObjectList,	// IN
														       zCArray<zCCollisionReport*>&	collReportList);		// OUT
	void		zCCFASTCALL		CollisionResponse		(const zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther);
	void		zCCFASTCALL		GetLargestBBox3DLocal	(zTBBox3D &bbox3DLocalOut);

	//
	zVEC3		zCCFASTCALL		GetCenterOffsetNew		() const;
private:												
	void		zCCFASTCALL		SetUpVectorNew			(const zVEC3& newUp);
	zVEC3		zCCFASTCALL		GetCenterOffsetLocal	() const;
};

// ============================================================================================================

class zCCollObjectProjectile : public zCCollObjectPoint {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectProjectile)
public:
};

// ============================================================================================================

class zCCollObjectComplex : public zCCollObjectBase {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectComplex)
public:
	// zCCollisionObject interface
	void		zCCFASTCALL		CollisionResponse		(const zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther);
	zREAL		zCCFASTCALL		GetAdaptiveStepSize		();
};

// ============================================================================================================

// polysoup, part of the static level
class zCCollObjectLevelPolys : public zCCollObjectBase {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectLevelPolys)
public:
	zCArray<zCPolygon*>		m_aoPolyList;				// polySoup
};

// ============================================================================================================

// zVOB_COLL_TYPE_NO_COLLRESP
class zCCollObjectBoxPassThrough : public zCCollObjectBase {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectBoxPassThrough)
public:
	// zCCollisionObject interface
	zBOOL		zCCFASTCALL		SuppressCollisionResponse	()			{ return TRUE; };
};

// ============================================================================================================

// static, invisible AABB movement blocker
class zCCollObjectBoxBlocker : public zCCollObjectBase {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectBoxBlocker)
public:
};

// ============================================================================================================

class zCConvexPrimitive;


class zCCollObjectCharacter : public zCCollObjectBase {
	zCOLLISION_OBJECT_DECLARATION (zCCollObjectCharacter)
public:

	// traceRay accelerating CacheObjects
    zCRayCache						m_oUpRayCache, m_oDownRayCache, m_oFrontRayCache, m_oBackRayCache, m_oLeftRayCache, m_oRightRayCache;

	// ctor/dtor
			 zCCollObjectCharacter();
	virtual ~zCCollObjectCharacter();

	// zCCollisionObject interface
	void		zCCFASTCALL			DetectCollisionsSelf		(const zCArray<zCCollisionObject*>& otherCollObjectList,	// IN
																       zCArray<zCCollisionReport*>&	collReportList);		// OUT
	void		zCCFASTCALL			CollisionResponse			(const zCArray<zCCollisionReport*>& collReportList, zBOOL& simulateFurther);
	zREAL		zCCFASTCALL			GetAdaptiveStepSize			();
	void		zCCFASTCALL			GetLargestBBox3DLocal		(zTBBox3D &bbox3DLocalOut);

	// zCCollObjectCharacter vs. zCCollObjectCharacter ('CC')
    virtual zCConvexPrimitive*		GetPrimitiveCC				() const;

	// configuration accesors
	enum zEConfigState
	{
		zCONFIG_STATE_STAND			= 0,
		zCONFIG_STATE_FLY			= 1,
		zCONFIG_STATE_SLIDE			= 2,
		zCONFIG_STATE_SWIM			= 3,
		zCONFIG_STATE_DIVE			= 4,
	};	
	struct zTConfig {
		zREAL						m_fMaxGroundAngleWalk;					// radiants	, max slope that a char can walk up on
		zREAL						m_fStepHeight;							// cm		, max heightY that a char can step up w/o climbing, step down w/o falling
									
		struct {
			zUINT8					m_bTreatWaterAsSolid			: 1;		//
			zUINT8					m_bDoWallSliding				: 1;		//
			zUINT8					m_bUseSpacingRays				: 1;		// use spacing rays to keep character off obstacles
			zUINT8					m_bLiftSpacingRayStart			: 1;		// lift startLocation of spacingRays, useful for characters that have a a very low centerPosition relative to the ground
			zUINT8					m_bFloorTooLowIsHardCollision	: 1;		// treats stepping on a floor that is lower than stepHeight as a hard collision
			zUINT8					m_eDoHeightCorrection			: 1;		// if true, char sticks firmly to ground, when not flying, diving (ATT: 2 bits are not enough!! Comp.Bug??)
			zUINT8					m_eDoHeightCorrectionSmooth		: 1;		// makes height correction smooth, when walking climbing edgie things like stairs (comes at small performance cost)
			zEConfigState			m_eState						: 4;		// 
		};
	} ;
	const zTConfig&					GetConfig					() const			{ return m_oConfig;	};
	zTConfig&						GetConfig					()					{ return m_oConfig;	};

	// SpatialState: gathered data about the environment
	struct zTSpatialState {
		zREAL						m_fFloorY  , m_fWaterY, m_fCeilingY;	// world space
		zREAL						m_fLastFloorY;							// world space
		zCPolygon*					m_poFloorPoly;
		zCPolygon*					m_poWaterPoly;
		zCPolygon*					m_poCeilingPoly;
		struct {
			zUINT8					m_bFloorIsStair		: 1;
			zUINT8					m_bFloorIsVob		: 1;
            zUINT8                  m_bIsUninited       : 1;
		};

        zTSpatialState()            { m_bIsUninited = true; }
	};								
	const zTSpatialState&			GetSpatialState				() const			{ return m_oSpatialState;				};
	zTSpatialState&					GetSpatialState				()					{ return m_oSpatialState;				};
	void        					MarkSpatialStateAsUninited	(zBOOL recalculateImmediately = FALSE);
    
									
	//								
	zREAL							GetFeetYLocal				() const			{ return m_fFeetYLocal;					};
	void							SetFeetYLocal				(const zREAL feetY) { m_fFeetYLocal	= feetY;				};
	zREAL							GetHeadYLocal				() const			{ return m_fHeadYLocal;					};
	void							SetHeadYLocal				(const zREAL headY) { m_fHeadYLocal	= headY;				};

	// tests whether a move is valid in terms of hard collision
	zBOOL		zCCFASTCALL			IsMoveInvalid				(const zVEC3&		transOld,			// IN
																 const zVEC3&		transNew,
																 zVEC3&				transOut,			// OUT
																 zTSpatialState&	spatialStateOut,
																 zVEC3&				collisionNormalOut)	{ return TestHardCollisions	(transOld, transNew, transOut, spatialStateOut, collisionNormalOut); };

	// Interference Report
	struct zTInterferenceReport 
	{
		zCPolygon					*spacingRayFrontPoly;
		zCVob						*spacingRayFrontVob;
		zCPolygon					*spacingRayBackPoly;
		zCVob						*spacingRayBackVob;
		zCPolygon					*spacingRayLeftPoly;
		zCVob						*spacingRayLeftVob;
		zCPolygon					*spacingRayRightPoly;
		zCVob						*spacingRayRightVob;
									
		struct {					
			zUINT8					spacingRayFront		: 1;				// after stateSwitch, set in End() / CollisionDetectionAndResponse()
			zUINT8					spacingRayBack		: 1;				
			zUINT8					spacingRayLeft		: 1;				
			zUINT8					spacingRayRight		: 1;				
			zUINT8					spacingRayWallSlide	: 1;				
		} correction;														
																			
		struct {															
			zUINT8					lowCeiling			: 1;				// character does not fit between floor and ceiling
			zUINT8					floorTooSteepUp		: 1;				// floor ahead is not accesible, too steep going upwards
			zUINT8					floorTooSteepDown	: 1;				// floor ahead is not accesible, too steep going downwards
			zUINT8					floorTooHigh		: 1;				// higher than stepHeight
			zUINT8					floorTooLow			: 1;				// lower than stepHeight
			zUINT8					centerRayCollided	: 1;				// center ray hit something
			zUINT8					blockingWallSlide	: 1;				// did wallSlide as a collision Response
		} blocking;															
		
        zVEC3 collisionNormal;                                              // normal of the wall that was hit (pointing AWAY from the wall)
        																
		void Clear() {												
			memset					(this, 0, sizeof(*this));				
		};
	};
	const zTInterferenceReport&		GetInterferenceReport		()                  const   { return m_oInterferenceReport; };

    virtual zBOOL IsDead                                        ()                  const   { return FALSE;                 };
    virtual zBOOL DontLetHimComeNearer                          (const zCVob *him)  const   { return FALSE;                 };

protected:	
    virtual zREAL TurnSpeed                                     ()                  const   { return 1;                     };
    virtual void  PushAround                                    (const zVEC3 &v)            {                               };

private:													
	// zCCollObjectCharacter vs. zCCollObjectCharacter ('CC')
    zCConvexPrimitive*				m_poPrimitiveCC;

	// gathered data about the environment
	zTSpatialState					m_oSpatialState;
									
	//								
	zREAL							m_fFeetYLocal;							// local space
	zREAL							m_fHeadYLocal;							// local space
									
	// wallSlide					
	zREAL							m_fWallSlideTimer;
	zREAL							m_fWallSlideRotDir;						// encodes direction(left/right) and magnitude
	zVEC3							m_oWallSlideRotAxis;
									
	// configuration				
	zTConfig						m_oConfig;
									
	// interference report
	// the interferenceReport is cleared at each frames this->Begin() and is completed after each frames this->End()
	zTInterferenceReport			m_oInterferenceReport;

	// methods
	static inline zREAL				S_GetSourceBBoxScaler	()					{ return zREAL(1.2F); };
	void		zCCFASTCALL			FindFloorWaterCeiling	(const zPOINT3& testLocation, zTSpatialState& spatialState);
	void		zCCFASTCALL			GetCollisionPoleYDims	(zREAL &miny, zREAL &maxy) const;
	zREAL							GetCollisionPoleYHeight () const							{ zREAL miny, maxy; GetCollisionPoleYDims(miny, maxy); return (maxy-miny); };
	zBOOL		zCCFASTCALL			TestHardCollisions		(const zVEC3&		transOld,			// IN
															 const zVEC3&		transNew,
															 zVEC3&				transOut,			// OUT
															 zTSpatialState&	spatialStateOut,
															 zVEC3&				collisionNormalOut);
	zBOOL		zCCFASTCALL			TestSoftCollisions		(const zPOINT3&		transOld,			// IN
															 const zPOINT3&		transNew,			//		this is the actual testLocation
															 zVEC3&				deltaTransOut,		// OUT
															 zVEC3&				collisionNormalOut);

	// methods: zCCollObjectCharacter vs. zCCollObjectCharacter ('CC')
	void		zCCFASTCALL			GetFallbackTrafoCC		(const zMAT4& trafoBeforeCollision,		// IN
															 const zMAT4& trafoNow, 
															 const zVEC3& evadeAt, 
															 const zBOOL  rotateFree,
															 zMAT4&		  ret) const;				// OUT
	static zVEC3 zCCFASTCALL		S_SlideCC				(const zVEC3& lastNormal, zREAL lastDistance, const zVEC3 &wishMove);
									
	// helper						
	void		zCCFASTCALL			PrintDebugInfos			();
	static inline zREAL				S_CalcFloorSlopeRad		(zREAL normalY)		{ zClamp (normalY, zREAL(-1.0F), zREAL(+1.0F)); return zREAL(acosf(normalY)); };	// returns radiants
	static zBOOL zCCFASTCALL		S_CalcAvgNormalVariance	(const zTTraceRayReport	(&rayHitReport)[4],
															 zVEC3					&collNormal, 
															 zREAL					&collNormalVariance);
	zBOOL		zCCFASTCALL			CalcSlideVector			(const zVEC3	&transDelta,		// IN
															 const zVEC3	&collNormal, 
															 zVEC3			&slideVectorOut,		// OUT
															 zVEC3			&slideRotAxis,
															 zREAL			&slideRotDirOut);
	void		zCCFASTCALL			DoWallSlidingLatentRotation (zMATRIX4 &trafoIn);
	zPOINT3		zCCFASTCALL			GetSurfaceAlignScanOrigin(const zPOINT3& testLocation);
};														

// ============================================================================================================

#endif