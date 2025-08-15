#include "zAICamera.h"
#include "zAICamera_Core.h"

#ifndef __ZAICAMERA_MOVEMENT_H__
#define __ZAICAMERA_MOVEMENT_H__


const float PLAYER_FUTURE_POS_ADVANCE_TIME_SEC	= 0.5F;
const float SHOULDERCAM_AZI						= 0;
const float SHOULDERCAM_ELEV					= 85;
const float SHOULDERCAM_RANGE					= 1.5F * 100;
const float SHOULDERCAM_FOCUS_OFFSET_AT			= 200;
const float SHOULDERCAM_FOCUS_OFFSET_UP			= 10;

const int	MAX_POS_SAMPLES_PLAYER				= 100;  // Max Number of pos. for ring buffer
const int	MAX_POS_SAMPLES_CAM					= 100; 
const int   MAX_POS_SAMPLES_FOCUS				= 100;
const int   NUM_MOV_SAMPLES_FOCUS				= 10;
const int	NUM_WAYPOINTS						= 3;
const float zWAYPOINT_SAMPLE_TIME				= 0.3F;
const int	NUM_ROT_SAMPLES						= 20;

// Movement related
// these are relative to cam position

enum zTAICamMsg 
{ 
	zPLAYER_MOVED_FORWARD	= 1 << 1,
	zPLAYER_MOVED_BACKWARD	= 1 << 2, 
	zPLAYER_MOVED_LEFT		= 1 << 3,
	zPLAYER_MOVED_RIGHT		= 1 << 4,
	zPLAYER_MOVED_UP		= 1 << 5,	
	zPLAYER_MOVED_DOWN		= 1 << 6,
	zPLAYER_ROTATED_LEFT	= 1 << 7,
	zPLAYER_ROTATED_RIGHT	= 1 << 8,
	zPLAYER_ROTATED_UP		= 1 << 9,  
	zPLAYER_ROTATED_DOWN	= 1 << 10,
	zPLAYER_MOVED			= 1 << 11,
	zPLAYER_STAND			= 1 << 12,
	zPLAYER_ROTATED			= 1 << 13,
	zPLAYER_ROT_NONE		= 1 << 14,
	zPLAYER_BEAMED			= 1 << 15
};


class zCMovementTracker 
{
	friend class zCAICamera;
	friend class zCMovementTracker;
public:

	typedef zDWORD zTPlayerMovement;

	enum zTWayPoint		
	{ 
		zWAYPOINT_PLAYER, 
		zWAYPOINT_CAM, 
		zWAYPOINT_HEAD, 
		zWAYPOINT_HIP_LEFT, 
		zWAYPOINT_HIP_RIGHT 
	};

	static zCMovementTracker*	GetTracker	();

						~zCMovementTracker	();
	// AI-related
	void				CamVobChanged		();
	void				TargetChanged		();
	void				SetAICamera			(zCAICamera* camera)					{ camai	 = camera;				};

	void				InterpolateTo		(const zSPathSearchResult &lerpDesc);
	void				Update				();

	// timer
	float				GetFrameTime		()										{ return frameTime;	};

	// ai methods. set methods change internal camera position ( get it with GetCamPos()/GetCamPosRing())

	zPOINT3&			CalcAziElevRangeApprox(const float &aziDeg,const float &elevDeg,const float &rng);
	void				SetAzimuth			(const zREAL &angle);
	void				SetElevation		(const zREAL &angle);
	void				SetRange			(const zREAL &range);
	zREAL				GetAzimuth			();
	zREAL				GetElevation		();
	zREAL				GetRange			();
	zREAL				GetAzimuth			(const zPOINT3 &testPos);
	zREAL				GetElevation		(const zPOINT3 &testPos);
	zREAL				GetRange			(const zPOINT3 &testPos);
	zREAL				GetPlayerAziSideSign()										{ return playerAziSideSign;	};
	zREAL				GetPlayerElevSideSign()										{ return playerElevSideSign;};

	zPOINT3				ApplyElevToPoint	(const zREAL &elev,const zPOINT3 &p);
	zPOINT3				ApplyAziToPoint		(const zREAL &azi, const zPOINT3 &p);
	zPOINT3				ApplyRangeToPoint	(const zREAL &dist,const zPOINT3 &p);

	void				SetPlayerPos		(const zPOINT3 &newTarget);  // overrides ring-pos
	zPOINT3&			GetPlayerPos		()										{ return playerPos;			};
	zPOINT3&			GetPlayerHead		()										{ return playerHead;		};
	zPOINT3&			GetPlayerHipLeft	()										{ return playerHipLeft;		};
	zPOINT3&			GetPlayerHipRight	()										{ return playerHipRight;	};
	zPOINT3&			GetLastPlayerPos	()										{ return oldPlayerPos;		};
	void				UpdatePlayerPos		(const zPOINT3 &newPos); // dito
	zPOINT3&			GetPlayerFuturePos	(const float advanceTimeSec);
	zPOINT3&			GetPlayerFuturePos	()										{ return playerFuturePos;	};
	void				SetPlayerFuturePosDT(const float &deltaT)					{ playerFuturePosDT = deltaT;		};
	zREAL				GetPlayerFuturePosDT() const								{ return playerFuturePosDT;			};
	zVEC3				GetPlayerAtVector	()										{ return trafoTStoWS.GetAtVector();	};
	zPOINT3&			GetPlayerPosRing	()										{ return playerPosRing;				}
	void				SetPlayerTrafo		(const zMAT4 &newTrafo)					{ trafoTStoWS = newTrafo; playerPos = trafoTStoWS.GetTranslation(); trafoWStoTS = trafoTStoWS.InverseLinTrafo();};
	zMAT4&				GetPlayerTrafo		()										{ return trafoTStoWS;		};
	zMAT4&				GetPlayerTrafoInv	()										{ return trafoWStoTS;		};
	zVEC3&				GetPlayerMoveRing	()										{ return playerPosMovementRing; };
	zPOINT3&			GetPlayerTargetPos	()										{ return POI_Player;	};
	float				GetPlayerRangeVelo  ()										{ return playerVeloRange;	};

	// camera position

	zPOINT3&			GetCamPos			()										{ return camPos;	};
	void				SetCamPos			(const zPOINT3 &newPos);
	void				UpdateCamPos		(const zPOINT3 &newPos); // dito
	zPOINT3&			GetCamPosRing		()										{ return camPosRing; };
	zMAT4&				GetCamTrafo			()										{ return trafoCStoWS;	};
	zMAT4&				GetCamTrafoInv		()										{ return trafoWStoCS;	};
	zMAT4&				GetShoulderCamMat	();
	zMAT4&				GetPanicCamMat		();
	zMAT4&				GetFirstPersonCamMat();

	zPOINT3				GetIdealRangePos	();
	zPOINT3				GetRangePos			(const float &dist);
	zCQuat				GetLocalRot			(const float &azi, const float &elev);
	zMAT4				GetLocalRotEnd		();
	zTPlayerMovement	GetPlayerMovement	()										{ return movement;				};
	zBOOL				HasPlayerMoved		()										{ return (movement & zPLAYER_MOVED);	};
	zBOOL				HasPlayerRotated	()										{ return (movement & zPLAYER_ROTATED);	};
	zBOOL				PlayerStands		()										{ return (!HasPlayerMoved() && !HasPlayerRotated()); };

	// sample waypoints
	void				ResetWayPoints		(const zPOINT3 &fillPos, const zTWayPoint &type);
	void				UpdateWayPoint		(const zTWayPoint &type);
	zPOINT3&			GetLastValidWayPoint(const zTWayPoint &type);
	void				CalcPlayerSpline	();

	// Messages / Hints
	void				ReceiveMsg			(const zTAICamMsg &msg);
	void				SetHintMouseUsed	(const zBOOL used)						{ bMouseUsed = used;		};

	zTPlayerMovement	movement;

	zCArray<zCPositionKey*>targetKFList;

	float	frameTime;
	zPOINT3 sampledPlayerPos;				// position gained by target-pos-sampling each time period 
	zPOINT3 sampledPlayerPosRing;			
	zPOINT3	playerPos;						
	zPOINT3 playerPosRing;					// ring buffered player
	zPOINT3 POI_Player;
	zPOINT3 camPos;
	zPOINT3 camPosRing;
	zPOINT3 oldSampledPlayerPosRing;
	zPOINT3 oldSampledPlayerPos;
	zPOINT3 offsetPos;
	zPOINT3 playerFuturePos;
	float	playerFuturePosDT;
	
	int		numPreSamplesPlayerPos;
//	zPOINT3 posRingPreSamplesPlayerPos[MAX_POS_SAMPLES_PLAYER];
//	zWORD	ringPosPreSamplesPlayerPos;

	int		numSamplesCam;
//	zPOINT3 posRingCam[MAX_POS_SAMPLES_CAM];
//	zWORD	ringPosCam;

	int		numSamplesPlayer;
//	zPOINT3 posRingPlayerPos[MAX_POS_SAMPLES_FOCUS];
//	zWORD	ringPosPlayerPos;

//	zVEC3	movRingFocus[NUM_MOV_SAMPLES_FOCUS];
//	zWORD	ringPosPlayerPosMov;

	zCPose	rotPoseTargetFOR;
	zCPose	headPose;
	zCPose	sampledPlayerPose;

	// focus waypoint list for ai

	zPOINT3 wayPointHead    [NUM_WAYPOINTS];
	zPOINT3 wayPointHipLeft [NUM_WAYPOINTS];
	zPOINT3 wayPointHipRight[NUM_WAYPOINTS];
	zPOINT3 wayPointCam	    [NUM_WAYPOINTS];
	int     actWayPointHead;
	int     actWayPointHipLeft;
	int     actWayPointHipRight;
	int		actWayPointCam;
	float	wayTimeHead;
	float	wayTimeHipLeft;
	float	wayTimeHipRight;
	float	wayTimeCam;

	zPOINT3 playerHead;
	zPOINT3 playerHipLeft;
	zPOINT3 playerHipRight;
	zVEC3   playerPosMovement;
	zVEC3   playerPosMovementRing;
	zVEC3   playerPosMovementLocal;
	zVEC3   playerPosMovementLocalCam;
	zVEC3	oldPlayerPosMovement;
	zPOINT3	oldPlayerPos;
	zPOINT3	oldCamPos;
	float	oldDistToPlayer;

	// trägheit
	float	inertiaTrans;
	float	inertiaHead;
	float	inertiaRotTargetFOR;
	float	inertiaTargetTrans;
	float	inertiaTargetRot;

	float	actAzi;
	float	actElev;
	float	distToPlayer;
	float	playerVeloRange;
	float   oldAzi;
	float	oldElev;

	zMAT4	trafoWStoTS;					// trafo world system	-> target system
	zMAT4	trafoTStoWS;					// trafo target system	-> world system
	zMAT4	trafoWStoCS;					// trafo world system   -> camera system
	zMAT4	trafoCStoWS;					// trafo camera system  -> world system
	zMAT4	oldTrafoWStoTS;
	zMAT4	oldTrafoWStoCS;
	zMAT4   oldTrafoRotOffsetWStoCS;
	zMAT4	lastValidCamTrafo; 

	zCQuat	startRot;
	zCQuat	endRot;
	zCQuat	maxAziRot;
	zCQuat	minAziRot;
	zCQuat	idealRot;
	zCQuat	idealRotTrans;
	zCQuat	actRot;
	zCQuat	idealRotLocal;
	zMAT4	initialPoseRotFreeze;

	float	timeSamples;
	float	standTimer;

	zBOOL	standing ;

protected:
	void	ClearMessages						();
	void	RecalcRingPositions					();
	void	SetRotateEnabled					(zBOOL rotate);


private:
						zCMovementTracker		();

	// player position sampling methods
	zPOINT3&			GetSampledPlayerPos		()									{ return sampledPlayerPos;	};
	void				SetSampledPlayerPos		(const zPOINT3 &newTarget);				
	void				UpdateSampledPlayerPos	(const zPOINT3 &p);	
	zPOINT3&			GetSampledPlayerPosRing	()									{ return sampledPlayerPosRing; }

	zBOOL				CheckSpecialMoves		();
	void				CheckKeys				();	
	void				CalcPlayerMovements		();
	void				CalcPlayerPose			();

	void				UpdateMessages			();
	void				AutoSetMessages			();

	// @@@
	float				GetDistToIdealRange		();
	zBOOL				IsIdealOrientation		();
	zBOOL				IsIdealRange();

	void				SaveFrameStates		();

	zBOOL			rotate;
	zBOOL			bMouseUsed;
	zREAL			playerAziSideSign;				// -1: player is on left side of camera, 0: player azi is zero, 1: player is on right side of camera
	zREAL			playerElevSideSign;				// -1: player is on top of camera, 0: player elev is zero, 1: player is on bottom side of camera

	zCVob*			target;
	zCVob*			camVob;
	zCAICamera*		camai;
	zCPathSearch*	pathSearch;						// main core ai class. finds evasions and puts the result in the var evasionSearchReport
};


#endif