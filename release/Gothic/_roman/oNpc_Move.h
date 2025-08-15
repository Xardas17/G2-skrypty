/******************************************************************************** 
 
     $Workfile:: oNpc_Move.h          $                $Date:: 8.02.01 19:39    $
     $Revision:: 11                   $             $Modtime:: 8.02.01 18:06    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Roman/oNpc_Move.h $
 * 
 * 11    8.02.01 19:39 Edenfeld
 * 
 * 10    29.01.01 16:27 Keskenti
 * 
 * 9     18.12.00 20:57 Wohlers
 * 
 * 8     18.12.00 14:37 Wohlers
 * 
 * 7     14.12.00 20:46 Wohlers
 * 
 * 6     7.11.00 13:40 Moos
 * 
 * 5     6.11.00 18:18 Wohlers
 * 
 * 4     31.10.00 13:14 Wohlers
 * 
 * 3     27.10.00 17:01 Wohlers
 * 
 * 2     26.10.00 14:45 Wohlers
 * 
 * 1     12.10.00 16:20 Keskenti
 * 
 *********************************************************************************/

#ifndef __ONPC_MOVE_H__
#define __ONPC_MOVE_H__

#define RBT_POSITION_INDEX_MAX 5

//	
//class oCNpc : public oCVob 
//{

public:
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************

	//
	//	CAN
	//
	zBOOL			CanDive					( void									);
	zBOOL			CanSwim					( void									);					
	int				CanGo					( zREAL len, zVEC3 &cdNormal			);
	zBOOL			CanStrafe				( zBOOL dirLeft, zTModelAniID aniID = zMDL_ANI_ID_ILLEGAL );
	zBOOL			CanJumpBack				( zTModelAniID aniID = zMDL_ANI_ID_ILLEGAL );

	//
	//	GET
	//
	zREAL			GetAngle				( zCVob*  to							);							
	void			GetAngles				( zCVob*  to, zREAL& azi, zREAL& elev	);	
	void			GetAngles				( zVEC3& pos, zREAL& azi, zREAL& elev	);
	zREAL			GetClimbRange			( void									);
	zREAL			GetDistanceToPos2		( zVEC3& pos, zBOOL dim2 = FALSE);
	zREAL			GetFallDownHeight		( void									);
	zREAL			GetJumpRange			( void									);
	zCRoute*		GetRoute				( void									)		{ return this->route	; }
	zREAL			GetTurnSpeed			( void									);		
	zCVob*			GetRbtObstacleVob		( void									);
	zVEC3			GetVecNormalFromBBox	( zCVob* vob, zVEC3& pos				);
	zBOOL			GetWalkStopChasm		( );
		
	//
	//	SET
	//
	void			SetFallDownHeight		( zREAL fallHeight						);
	void			SetFallDownDamage		( int fallDamage						);
	void			SetRoute				( zCRoute* rt							);
	void			SetTurnSpeed			( int speed								)		{ this->speedTurn = speed ? speed : NPC_TURNVELOCITY; speedTurn *= 0.001f; }
	void			SetWalkStopChasm		( zBOOL stop							);
	virtual	void	ResetPos				( zVEC3 &pos							);
	virtual void	EmergencyResetPos		( zVEC3 &p								);

	//
	//	CREATE
	//
	void			CreateDynJump			( zVEC3 &p1, zVEC3 &p2					);
	void			CreateFallDamage		( zREAL dist							);

	//
	//	EXTERNALS
	//
	void			AI_Flee					( oCNpc *pEnemy							);
	void			AI_Follow				( oCNpc *pEnemy							);

	//
	//	EVENTS
	//
	zBOOL			EV_RobustTrace			( oCMsgMovement* csg					);
	zBOOL			EV_GotoPos				( oCMsgMovement* csg					);
	zBOOL			EV_GotoVob				( oCMsgMovement* csg					);
	zBOOL			EV_GoRoute				( oCMsgMovement* csg					);
	zBOOL			EV_Turn					( oCMsgMovement* csg					);
	zBOOL			EV_TurnToPos			( oCMsgMovement* csg					);
	zBOOL			EV_TurnToVob			( oCMsgMovement* csg					);
	zBOOL			EV_TurnAway				( oCMsgMovement* csg					);
	zBOOL			EV_Jump					( oCMsgMovement* csg					);
	zBOOL			EV_WhirlAround			( oCMsgMovement* csg					);
	zBOOL			EV_SetWalkMode			( oCMsgMovement* csg					);
	zBOOL			EV_StandUp				( oCMsgMovement* csg					);
	zBOOL			EV_CanSeeNpc			( oCMsgMovement* csg					);
	zBOOL			EV_Strafe				( oCMsgMovement* csg					);
	zBOOL			EV_GotoFP				( oCMsgMovement* csg					);
	zBOOL			EV_AlignToFP			( oCMsgMovement* csg					);
	zBOOL			EV_Dodge				( oCMsgMovement* csg					);
	
	//
	//	MISC
	//
	zBOOL			BeamTo					( const zSTRING& targetVob				);
	void			Fleeing					( void									);
	void			StandUp					( zBOOL walkingallowed = FALSE, zBOOL startAniTransition = TRUE);
	int				ThinkNextFleeAction		( void									);
	zREAL			Turn					( zVEC3 &dir							);
	zREAL			Turning					( zVEC3 &dir							);
											
	//
	//	ROBUST TRACE
	//
	zBOOL			RobustTrace				( void									);
																					
	zBOOL			RbtAvoidObstacles		( void									);
	zBOOL			RbtCheckLastDirection	( zREAL dist							);
	void			RbtInit					( zVEC3& tpos, zCVob* tvob				);
	zBOOL			RbtIsDirectionValid		( const zVEC3& direction				);
	zBOOL			RbtMoveToExactPosition	( void									);
	void			RbtReset				( void									);
	void			RbtUpdate				( zVEC3& tpos, zCVob* tvob				);
	int				RbtChooseChasmAction	( const zVEC3& pos, const zVEC3& dir	);

	zBOOL			RbtGetObstacle			( const zVEC3& pos, const zVEC3& dir, zCVob* &obstacle, zVEC3& cdNormal	);
	zBOOL			RbtIsObjectObstacle		( zCVob* obstacle, const zVEC3& pos, const zVEC3& dir, zVEC3& cdNormal	);
	zBOOL			RbtGetSmallObstacle		( const zVEC3& dir, zCVob* &obstacle, zVEC3& cdNormal );

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************

private:
	// *********************************************************************************
	// **							ENUMS & STRUCTURES
	// *********************************************************************************

	typedef struct oSDirectionInfo {
	
		zVEC3			checkDirection;
		zUINT8			checkForChasm			: 1 ;	// 0
		zUINT8			checkForSmallObject		: 1 ;	// 1
		zUINT8			checkIfClimbable		: 1 ;	// 2

	} oTDirectionInfo;

	struct oTRobustTrace {

		struct {
			zUINT8			stand					: 1	;	// 0x00	- 0
			zUINT8			dirChoosed				: 1	;	// 0x00	- 1
			zUINT8			exactPosition			: 1	;	// 0x00	- 2
			zUINT8			targetReached			: 1	;	// 0x00	- 3
			zUINT8			standIfTargetReached	: 1	;	// 0x00	- 4
			zUINT8			waiting					: 1	;	// 0x00	- 5
			zUINT8			isObstVobSmall			: 1 ;	// 0x00 - 6	
			zUINT8			targetVisible			: 1	;	// 0x00	- 7
			zUINT8			useChasmChecks			: 1 ;
		};													// 0x01		
		
		zVEC3							targetPos					;
		zCVob*							targetVob					;
		zCVob*							obstVob						;
		zREAL							targetDist					;
		zREAL							lastTargetDist				;
		zREAL							maxTargetDist				;
		zREAL							dirTurn						;
		zREAL							timer						;			
		zVEC3							dirFirst					;
		zREAL							dirLastAngle				;
		zCArray	< oTDirectionInfo* >	lastDirections				;
		int								frameCtr					;
		
		// Follow Kram
		zVEC3							targetPosArray				[5];
		int								targetPosCounter			;
		int								targetPosIndex				;
        zREAL							checkVisibilityTime			;
		zREAL							positionUpdateTime			;
		zREAL							failurePossibility			;

		oTRobustTrace(){};
	};

	// *********************************************************************************
	// **								 METHODS
	// *********************************************************************************
	
	oTDirectionInfo*		RbtInsertDirection		( zVEC3 direction										);
	zREAL					RbtCalcTurnDirection	( const zVEC3& cdNormal, zREAL dist, int lastObstacle	);
	zBOOL					RbtCheckIfTargetVisible	( void );
	zBOOL					RbtGotoFollowPosition	( void );
	zBOOL					RbtCheckForSolution		( zVEC3 curPos, zVEC3 targetPos );
	void					ForceRotation			( zREAL deg );

	// *********************************************************************************
	// **								ATTRIBUTES
	// *********************************************************************************
	zREAL					speedTurn		;

	zBOOL					foundFleePoint	;
	zBOOL					reachedFleePoint;
	zVEC3					vecFlee			;
	zVEC3					posFlee			;
	zCWaypoint*				waypointFlee	;

	oTRobustTrace			rbt				;


	//}
//

#endif // __ONPC_MOVE_H__
