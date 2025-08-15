/******************************************************************************** 
 
     $Workfile:: zAIPlayer.h          $                $Date:: 24.04.01 17:33   $
     $Revision:: 27                   $             $Modtime:: 17.04.01 0:30    $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   C++ AI base-class for animation controled creatures
   Implements moves like walking, swimming, diving, jumping, climbing
   created       : ?.?.98

 * $Log: /current_work/ZenGin/_Dieter/zAIPlayer.h $
 * 
 * 27    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 26    26.01.01 19:40 Hildebrandt
 * 
 * 25    15.01.01 19:08 Hildebrandt
 * 
 * 24    15.01.01 18:04 Moos
 * 
 * 23    15.01.01 3:55 Hildebrandt
 * 
 * 22    14.01.01 16:36 Hildebrandt
 * 
 * 21    12.01.01 12:38 Moos
 * 
 * 20    11.01.01 20:15 Moos
 * 
 * 19    11.01.01 18:53 Hildebrandt
 * 
 * 18    11.01.01 18:46 Hildebrandt
 * 
 * 16    20.12.00 3:04 Hildebrandt
 * 
 * 15    6.12.00 1:16 Hildebrandt
 * 
 * 14    5.12.00 19:57 Hildebrandt
 * 
 * 13    5.12.00 19:04 Hildebrandt
 * 
 * 12    25.10.00 15:07 Hildebrandt
 * 
 * 11    22.09.00 17:14 Moos
 * 
 * 10    21.09.00 20:58 Moos
 * 
 * 9     14.09.00 19:43 Hildebrandt
 * 
 * 8     11.09.00 17:34 Hildebrandt
 * 
 * 7     15.08.00 23:54 Hildebrandt
 * zenGin 0.92h
 * 
 * 15    9.08.00 17:12 Admin
 * 
 * 6     6.07.00 13:33 Hildebrandt
 * 
 * 4     2.05.00 21:47 Hildebrandt
 * zenGin 089c
 * 
 * 11    15.03.00 16:42 Hildebrandt
 * zenGin 088
 * 
 * 10    22.02.00 2:01 Hildebrandt
 * zenGin 087d
 * 
 * 9     17.02.00 3:07 Hildebrandt
 * zenGin 087a
 * 
 * 7     10.01.00 15:13 Hildebrandt
 * zenGin 0.85a
 * 
 * 6     12.11.99 1:03 Hildebrandt
 * ZenGin v0.83d
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 27 $ ($Modtime: 17.04.01 0:30 $)

// =====================================================================================================================

#ifndef __ZAIPLAYER_H__
#define __ZAIPLAYER_H__


#ifndef __ZWORLD_H__
#include <zWorld.h>
#endif

#ifndef __Z3D_H__
#include <z3D.h>
#endif

#ifndef __ZAI_H__
#include <zAI.h>
#endif

#ifndef __ZSOUND_H__
#include <zSound.h>
#endif

#ifndef __ZRAYCACHE_H__
#include <zRayCache.h>
#endif

#ifndef __ZCOLLISIONDETECTOR_H__
#include <zCollisionDetector.h>
#endif

#ifndef __ZCOLLISIONOBJECT_H__
#include <zCollisionObject.h>
#endif

#ifndef __ZCOLLISIONOBJECTMISC_H__
#include <zCollisionObjectMisc.h>
#endif

// =====================================================================================================================

#ifdef ZENGINE_DEBUG
	#define ZENGINE_AIPLAYER
#endif

class zCModel;
class zCModelAni;
class zCModelNodeInst;
class zCQuadMark;

// =====================================================================================================================

// detect climb up ledge forward scan depth
#define zMV_DCUL_SCAN_DEPTH		zREAL(150)

//
#define zMV_LAND_HEIGHT			zREAL(10)

// specify a water depth greater than this to make the AI ignore water completely (zMV_WATER_DEPTH_KNEE and zMV_WATER_DEPTH_CHEST)
#define zMV_WATER_IGNORE_DEPTH	zREAL(999999)


//class zCAIPlayer : public zCAIBaseSound {
class zENGINE_API zCAIPlayer : public zCAIBase {
	zCLASS_DECLARATION	(zCAIPlayer)
public:

	zCAIPlayer ();

	// zCAIBase Interface
	virtual void		DoAI							(zCVob* inVob, zBOOL& vobDeleted);
	virtual void		HostVobRemovedFromWorld			(zCVob* hostVob, zCWorld* hostWorld);
//	virtual void		HostVobAddedToWorld				(zCVob* hostVob, zCWorld* hostWorld);

	// ===================================================================================================

	// Config
	struct zTConfig {
		zREAL			zMV_MIN_SPACE_MOVE_FORWARD;
		zREAL			zMV_DETECT_CHASM_SCAN_AT;
		zREAL			zMV_STEP_HEIGHT;				// => collObjChar
		zREAL			zMV_JUMP_UP_MIN_CEIL;
		zREAL			zMV_WATER_DEPTH_KNEE;
		zREAL			zMV_WATER_DEPTH_CHEST;
		zREAL			zMV_YMAX_SWIM_CLIMB_OUT;
		zREAL			zMV_FORCE_JUMP_UP;
		zREAL			zMV_YMAX_JUMPLOW;
		zREAL			zMV_YMAX_JUMPMID;
						
		//				
		zREAL			zMV_MAX_GROUND_ANGLE_WALK;		// => collObjChar
		zREAL			zMV_MAX_GROUND_ANGLE_SLIDE;
		zREAL			zMV_MAX_GROUND_ANGLE_SLIDE2;
						
		//				
		zREAL			zMV_DCUL_WALL_HEADING_ANGLE;
		zREAL			zMV_DCUL_WALL_HORIZ_ANGLE;
		zREAL			zMV_DCUL_GROUND_ANGLE;

		// intern, wird nicht im Game benutzt
		#ifdef ZENGINE_AIPLAYER
			zREAL		zMV_MIN_VELOCITY_RUN;
			zREAL		zMV_MIN_VELOCITY_WALK;
			zREAL		zMV_MIN_VELOCITY_RUN2;
			zREAL		zMV_MIN_VELOCITY_WALK2;
		#endif
	} config;
	enum zTSurfaceAlignMode {						
		zMV_SURFACE_ALIGN_NONE	= 0,				// off
		zMV_SURFACE_ALIGN_NORMAL= 1,				// e.g. ShadowBeast
		zMV_SURFACE_ALIGN_HIGH	= 2,				// e.g. SwampShark, Meatbug
	};												
	void				SetConfigDoDetectWalkStopChasm	(const zBOOL b)					{ zMV_DO_DETECT_WALK_STOP_CHASM = b;	};
	zBOOL				GetConfigDoDetectWalkStopChasm	() const						{ return zMV_DO_DETECT_WALK_STOP_CHASM;	};
	void				SetConfigDoWallSliding			(const zBOOL b)					{ zMV_DO_WALL_SLIDING = b;				};
	zBOOL				GetConfigDoWallSliding			() const						{ return zMV_DO_WALL_SLIDING;			};
	void				SetConfigDoHeightCorrection		(const zBOOL b)					{ zMV_DO_HEIGHT_CORRECTION = b;			};
	zBOOL				GetConfigDoHeightCorrection		() const						{ return zMV_DO_HEIGHT_CORRECTION;		};
	void				SetConfigDoSurfaceAlign			(const zTSurfaceAlignMode s)	{ zMV_DO_SURFACE_ALIGN = s;		};
	zTSurfaceAlignMode	GetConfigDoSurfaceAlign			() const						{ return zTSurfaceAlignMode(zMV_DO_SURFACE_ALIGN);	};


	// info about the last calculated jumpUp/grab ledge

   struct zTLedgeInfo{
        zVEC3 point;            // position to grab
        zVEC3 normal;           // normal to align to
        zVEC3 cont;             // vector parallel to upper polygon. normalized
        zREAL maxMoveForward;   // max distance to go into that direction

        zTLedgeInfo(const zCAIPlayer *):point(0,0,0), normal(0,0,0), cont(0,0,0), maxMoveForward(0){}
    };


    static zBOOL		S_GetShowWeaponTrails			()								{ return s_bShowWeaponTrails;	};
    static void			S_SetShowWeaponTrails			(const zBOOL b)					{ s_bShowWeaponTrails = b;		};

    // zTLedgeInfo *ledgeInfo;

    void                CreateLedgeInfo                 ()      ;
    zTLedgeInfo        *GetLedgeInfo                    () const;
	zBOOL           	GetFoundLedge			        () const;
    void				ClearFoundLedge           		()      ;
    const zVEC3&		GetLastLedgePoint				()	const						{ zERR_ASSERT(GetLedgeInfo()); return GetLedgeInfo()->point;              };
	const zVEC3&		GetLastLedgeNormal				()	const						{ zERR_ASSERT(GetLedgeInfo()); return GetLedgeInfo()->normal;             };
	const zVEC3&		GetLastLedgeCont				()	const						{ zERR_ASSERT(GetLedgeInfo()); return GetLedgeInfo()->cont ;              };
	const zREAL 		GetLastLedgeMaxMoveForward		()	const						{ zERR_ASSERT(GetLedgeInfo()); return GetLedgeInfo()->maxMoveForward ;    };

    zCVob*              GetVob                          () const { return vob;                                                              };
    zCModel*            GetModel                        () const { return model;                                                            };
    zCWorld*            GetWorld                        () const { return world;                                                            };
	zCCollObjectCharacter* GetCollObject				() const { return static_cast<zCCollObjectCharacter*>(vob->GetCollisionObject());	};
	zREAL				GetFloorY						() const { return GetCollObject()->GetSpatialState().m_fFloorY;						};
	zREAL				GetLastFloorY					() const { return GetCollObject()->GetSpatialState().m_fLastFloorY;					};
	zREAL				GetWaterY						() const { return GetCollObject()->GetSpatialState().m_fWaterY;						};
	zREAL				GetCeilingY						() const { return GetCollObject()->GetSpatialState().m_fCeilingY;					};
	zCPolygon*			GetFloorPoly					() const { return GetCollObject()->GetSpatialState().m_poFloorPoly;					};
	zCPolygon*			GetWaterPoly					() const { return GetCollObject()->GetSpatialState().m_poWaterPoly;					};

    int                 GetWaterLevel                   () const { return waterLevel;           };
	zREAL				GetFeetY						() const { return feetY;	            };
	zREAL				GetHeadY						() const { return headY;	            };
	zREAL				GetAboveFloor					() const { return aboveFloor;           };
	zREAL				GetFallDownDistanceY    		() const { return fallDownDistanceY;    };

	void				SetFallDownStartY    		    (zREAL y){ fallDownStartY = y;          };

    const zCCollObjectCharacter::zTInterferenceReport& GetInterferenceReport() const { return GetCollObject()->GetInterferenceReport(); };

	enum zTMovementState {							// keep in sync with bitfield!
		zMV_STATE_STAND			= 0,				
		zMV_STATE_FLY			= 1,				
		zMV_STATE_SWIM			= 2,				
		zMV_STATE_DIVE			= 3,				
	};					
	zTMovementState		GetState						()	const						{ return state;			};
	void				SetState						(const zTMovementState s)		{ state	= s;			};

	const zVEC3&		GetCenterPos					()	const						{ return centerPos;		};	
	const zVEC3&		GetVelocity						()	const						{ return velocity;		};


	// methods			
    void                SetModel                        (zCModel *m)       { model = m;                                                               };
    void                SetWorld                        (zCWorld *w)       { world = w;                                                               };
	void				SetVob							(zCVob *inVob);
	void				Begin							(zCVob* inVob);
	void				End								();

	// 
//	zBOOL				DetectWalkStopChasm				();
	zBOOL				DetectClimbUpLedge				(zPOINT3& resultLedgePoint, const zBOOL startYScanFromFeet=FALSE);
	void				AlignModelToLedge				(const zSTRING& hangAniName);
	void				AlignToFloor					(const zREAL floorHeight);
	zVEC3				GetHandPositionWorld			() const;
	zREAL				GetModelFloorWorld				();
	zBOOL				GetTreatsWaterAsSolid			() const	{ return (config.zMV_WATER_DEPTH_KNEE >= zMV_WATER_IGNORE_DEPTH); }; // Wasser komplett ignorieren?
	void				LandAndStartAni					(const zSTRING& aniName);
	void				LandAndStartAni					(zCModelAni		*modelAni);
	zBOOL				CheckForceModelHalt				(const zSTRING& aniName);
	zBOOL				CheckForceModelHalt				(zCModelAni		*modelAni);
	zBOOL				CheckEnoughSpaceMoveDir			(const zVEC3&	unitDir, const zBOOL dontDetectWalkStopChasm=FALSE);
	zBOOL				CheckEnoughSpaceMoveForward		(const zBOOL dontDetectWalkStopChasm=FALSE);
	zBOOL				CheckEnoughSpaceMoveBackward	(const zBOOL dontDetectWalkStopChasm=FALSE);
	zBOOL				CheckEnoughSpaceMoveLeft		(const zBOOL dontDetectWalkStopChasm=FALSE);
	zBOOL				CheckEnoughSpaceMoveRight		(const zBOOL dontDetectWalkStopChasm=FALSE);

	// Helper			
	zREAL				GetProtoYHeight					();
	zVEC3				GetInters						() const					{ return world->traceRayReport.foundIntersection; };
	zBOOL				GetCDStat						() const					{ return cdStat; };
	void				SetCDStat						(const zBOOL b);
	void				SetPhysicsEnabled				(zBOOL b);
	void				StartPhysicsWithVel				();
	zREAL				GetJumpUpHeight					(); // returns the the height from bbox-top that can be overcome by jumping up
	void				SetJumpUpForceByHeight			(const zREAL height);
						
	//					
	void				DiveRotateX						(const zREAL& angle);
	zBOOL				ShouldCorrectFloorHeight		();

	// Blood quadMark
	void				SetBleeding						(const zREAL bleedPerc)		{ bleedingPerc = bleedPerc;	};
	zREAL				GetBleeding						()							{ return bleedingPerc;		};
	void				SetBloodDefaultTexture			(const zSTRING& texName);
	void				AddBlood						(const zPOINT3& rayOrg, const zVEC3& ray, zREAL size, zBOOL scaleUp, zSTRING* texName=0);

	// Weapon Trail
	void				AddWeaponTrailSegment			(const zPOINT3& posUp, const zPOINT3& posDown);
												
	//													
	virtual void		StartStandAni					();
	virtual void		StartFallDownAni				();

	// autoRoll
	void				DoAutoRoll						();
	void				SetAutoRollMaxAngle				(const zREAL& maxAngle)	{ autoRollMaxAngle	= maxAngle;	};
	void				SetAutoRollSpeed				(const zREAL& speed)	{ autoRollSpeed		= speed;	};
	void				SetAutoRollPosDest				(const zREAL& rollDest)	{ autoRollPosDest	= rollDest;	};
	zREAL				GetAutoRollPosDest				() const            	{ return autoRollPosDest;   	};
	void				ResetAutoRoll					();
	zBOOL				GetAutoRollEnabled				() const				{ return autoRollEnabled;	};
	void				SetAutoRollEnabled				(const zBOOL& b)		{ autoRollEnabled=b;		};
	
	// persistance										
	virtual void		Archive							(zCArchiver &arc);
	virtual void		Unarchive						(zCArchiver &arc);

	zBOOL				IsSliding						();

	// ===================================================================================================

protected:
	virtual				~zCAIPlayer ();					// use Release() instead!
	// Debug
	void				Print							(const zSTRING& s) const;
	void				PrintScreen						(int xscr, int yscr, zSTRING s) const;
	void				Line3D							(const zVEC3& a, const zVEC3& b, int col) const;

	// ===================================================================================================

private:												

	// ===================================================================================================
	// ===================================================================================================
	static	zBOOL		s_bShowWeaponTrails;
	zCVob				*vob;							// MUSS erste Variable bleiben
	zCModel				*model;
	zCWorld				*world;
						
	zPOINT3				centerPos;						// current pos of vob
	zREAL				feetY   , headY;
	zREAL				aboveFloor;
	
	int					waterLevel;						// 0=bis Knie, 1=bis Brust, 2=ueber Brust (zu tief zum Stehen)

	// common state data
	zREAL				velocityLen2;
	zVEC3				velocity;
						
	zREAL				fallDownDistanceY;
	zREAL				fallDownStartY;
			
	zVEC3				slidePolyNormal;
	zREAL				checkWaterCollBodyLen;
	zCModelNodeInst*	modelHeadNode;

	//
	#pragma pack (push, 1)							// Alignment ausschalten
	struct {	// 27 Bit
		zUINT8			zMV_DO_SURFACE_ALIGN			: 2;	// zTSurfaceAlignMode
		zUINT8			zMV_DO_DETECT_WALK_STOP_CHASM	: 1;
		zUINT8			zMV_DO_WALL_SLIDING				: 1;	// => collObjChar
		zUINT8			zMV_DO_HEIGHT_CORRECTION		: 1;	// => collObjChar

		zUINT8			cdStatOriginal					: 1;
		zUINT8			cdStat							: 1;
		zUINT8			startFXModelLandDust			: 1;
//		zUINT8			foundLedge						: 1;    // [Moos] ledgeInfo übernimmt diesen Part
		zUINT8			forceModelHalt					: 1;
		zUINT8			autoRollEnabled					: 1;
		zUINT8			modelAnisInPlace				: 1;
		zTMovementState	oldState						: 3;	// zTMovementState
		zTMovementState	state							: 3;	// zTMovementState
		zUINT8			oldWaterLevel					: 2;	// 0,1 or 2
		zCCollObjectCharacter::zEConfigState m_eCollObjectState		: 4;
		zCCollObjectCharacter::zEConfigState m_eCollObjectStateOld	: 4;
	};
	#pragma pack (pop)								// Alignment einschalten

	// Blood effects
	struct zTBloodVobTrack {
		zCVob			*bloodVob;
		zREAL			alpha;
	};
	zCArray<zTBloodVobTrack>	bloodVobList;
	zREAL				bleedingPerc;
	zVEC3				bleedingLastPos;
	zREAL				bleedingNextDist;

	// Weapon Trail effects
	zCVob*				weaponTrailVob;

	// WaterRing effects
	zCVob				*waterRingVob;
	zREAL				waterRingTimer;

	// autoRolling
	zREAL				autoRollPos;
	zREAL				autoRollPosDest;
	zREAL				autoRollSpeed;
	zREAL				autoRollMaxAngle;

	//
	#ifdef ZENGINE_AIPLAYER
		// temps ?
		zREAL			xspeed,yspeed,zspeed,rotspeed;
		zREAL			force_x, force_y, force_z, force_rot;
		zBOOL			irgnoreKeyBoard;
		zVEC3			lastWeaponPos;
		zVEC3			jumpLowMidVel;
		int				jumpLowMidPass;							// 0,1 or 2  // FIXME [MOOS]: wird nicht mehr gebraucht


	#endif					

	zBYTE				dummyLastVar;							// MUSS letzte Variable bleiben

	// ===================================================================================================
	// ===================================================================================================

	zSTRING				bloodDefaultTexName;

	//
	zCQuadMark*			GetBloodQuadMark				();
	void				UpdateEffects					();
	void				RemoveEffects					();
	zPOINT3				GetSurfaceAlignScanOrigin		();
	static zREAL		CalcFloorSlopeRad				(zREAL normalY) { zClamp (normalY, zREAL(-1.0F), zREAL(+1.0F)); return zREAL(acosf(normalY)); };	// returns radiants

	//
	void				BeginStateSwitch				();
	void				CalcModelAnisInPlace			();

	//
	void				PropagateCollObjectStates		(const zTMovementState movementState);
	void				CalcForceModelHalt				();
	void				CalcStateVars					();
	void				DoProceduralMovement			();
	void				CheckPhysics					();
	zBOOL				CheckFloorSliding				();
	void				DoSurfaceAlignment				();
	#ifdef ZENGINE_AIPLAYER
		void			DoStateSwitch					();
		void			CheckWeaponCollisions			();
		void			SetIgnoreKeyboard				(zBOOL k)		{ irgnoreKeyBoard = k; };
		zBOOL			KeyPressed						(int key);
		void			PrintDebugInfos					();
	#endif
};

// =====================================================================================================================


#endif