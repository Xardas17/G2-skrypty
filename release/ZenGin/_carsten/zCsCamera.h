/****************************************************************
*
* Camera - Cutscene Artificial Intelligence
* File          : zCSCamera.h 
* Projekt       : Phoenix
* Autor         : Carsten Edenfeld
* Version       : 0.00
* last modified : 15.07.98
* erstellt      : 15.07.98
* Compiler OK   :
*
*****************************************************************
- known bugs:
*****************************************************************
- possible optimizations:
*****************************************************************
- missing features:
	X- vertigo camera (brennweite + distanz ändern)
	X- rolloff
	2- anpassung an surroundings (TODO: an Line of Interest spiegeln)
	X- andere übergänge von/zur normalen Camera AI ausser switches
	X- diverse LerpModi, speziell zCAMTRJ_KEY_MOTION_SMOOTH könnte
	   sich auch auf umgebende Keys auswirken
	X- Ringbuffer für pos  (beide refVobs!) 
	X- AutoSetTime weiter füllen
	X- Interpol. Funcs fertigstellen
	3- v0 in Funcs integrieren
	3- Klasse für FX und Spacer brauchbar machen ...
	3- Performance beim Spline drawen scheint manchmal dramatisch in die Knie zu gehen
*****************************************************************
- comments:  
****************************************************************/
#ifndef __ZCSCAMERA_H__
#define __ZCSCAMERA_H__

#ifndef __ZVOB_H__
#include "zVob.h"
#endif

#ifndef __ZKBSPLINES_H__
#include "zKBSplines.h"
#endif

#ifndef __ZEVENTMAN_H__
#include "zEventMan.h"
#endif

#ifndef __ZAICAMERA_H__
#include "zAICamera.h"
#endif

#ifndef __ZAICAMERA_MOVEMENT_H__
#include "zAICamera_Movement.h"
#endif

typedef zREAL	(*LerpFunc)( const zREAL easeIn, const zREAL v0 = 0 );

enum zTCamTrj_KeyMotionType {
	zCAMTRJ_KEY_MOTION_UNDEF=0,
	zCAMTRJ_KEY_MOTION_SMOOTH,
	zCAMTRJ_KEY_MOTION_LINEAR,
	zCAMTRJ_KEY_MOTION_STEP,
	zCAMTRJ_KEY_MOTION_SLOW,
	zCAMTRJ_KEY_MOTION_FAST,
	zCAMTRJ_KEY_MOTION_CUSTOM
};

enum zTCamTrj_KFType		{	
	KF_UNDEF=0,
	KF_TARGET,
	KF_CAM	
};


const float zCS_KEYTIME_UNDEF			= -1;
const float zCSCAM_DEFAULT_DURATION		= 10;

class zCCSCamera;

class zCCamTrj_KeyFrame : public zCVob {
zCLASS_DECLARATION	(zCCamTrj_KeyFrame)
public:

	friend class zCCSCamera;
	zCCamTrj_KeyFrame();
protected:
	~zCCamTrj_KeyFrame();
public:

	void					SetTime			(const zREAL t)						{ time = t;			};
	zREAL					GetTime			() const							{ return time;		};
	zBOOL					GetTimeIsFixed  () const							{ return timeIsFixed; };
	zREAL					GetAngleRollDeg	() const							{ return angleRollDeg; };
	void					SetAngleRollDeg (const zREAL w)						{ angleRollDeg = w;	};
	zREAL					GetCamFOVScale	() const							{ return camFOVScale;};
	void					SetCamFOVScale	(const zREAL s)						{ camFOVScale = s;	};
	void					SetMotionType	(const zTCamTrj_KeyMotionType mt)	{ motionType = mt;	};
	zTCamTrj_KeyMotionType	GetMotionType	() const							{ return motionType;};
	void					SetMotionTypeFOV(const zTCamTrj_KeyMotionType mt)	{ motionTypeFOV = mt;	};
	zTCamTrj_KeyMotionType	GetMotionTypeFOV() const							{ return motionTypeFOV; };
	void					SetMotionTypeRoll(const zTCamTrj_KeyMotionType mt)	{ motionTypeRoll = mt;	};
	zTCamTrj_KeyMotionType	GetMotionTypeRoll() const							{ return motionTypeRoll;};
	void					SetMotionTypeTimeScale(const zTCamTrj_KeyMotionType mt)	{ motionTypeTimeScale = mt;	};
	zTCamTrj_KeyMotionType	GetMotionTypeTimeScale() const						{ return motionTypeTimeScale;};
	void					SetTimeScale	 (const zREAL timeScale)				{ this->timeScale = timeScale; };
	zREAL					GetTimeScale	 () const							{ return timeScale;		};
	zTCamTrj_KFType			GetType			 () const							{ return type;			};
	zREAL					GetBias			 () const							{ return bias;			};
	zREAL					GetTension		 () const							{ return tension;		};
	zREAL					GetContinuity	 () const							{ return continuity;	};
	zCCSCamera*				GetParentCam	 () const							{ return cscam;			};
	void					Changed			 ();

#ifdef COMPILING_SPACER
	virtual	void			EndMovement		 ();
#endif

	virtual	void			Archive			(zCArchiver &arc);
	virtual void			Unarchive		(zCArchiver &arc);
protected:

	virtual void			ThisVobAddedToWorld		(zCWorld *homeWorld);
	virtual void			ThisVobRemovedFromWorld	(zCWorld *homeWorld);

	zREAL					time;
	zREAL					angleRollDeg;
	zREAL					camFOVScale;
	zTCamTrj_KeyMotionType	motionType;
	zTCamTrj_KeyMotionType	motionTypeFOV;
	zTCamTrj_KeyMotionType	motionTypeRoll;
	zTCamTrj_KeyMotionType	motionTypeTimeScale;
	zBOOL					timeIsFixed;
	zREAL					tension;
	zREAL					bias;
	zREAL					continuity;
	zREAL					timeScale;
public:
	zMAT4					originalPose;
	zMAT4					actPose;		// actual pose (w/ possible parent FOR), might be adjusted
protected:
	zBOOL					adjusted;		// original pose (w/ possible parent FOR)

	// tension, bias, continuity
	zCCSCamera				*cscam;
	zTCamTrj_KFType			type;
};

class zCCSCamera_EventMsg : public zCEventMessage {
zCLASS_DECLARATION	(zCCSCamera_EventMsg)
public:
	enum zTCSCam_EvSubType {	
		EV_NOTHING = 0,
		EV_PLAY,				// initial event to send when shot/cut has to be played
		EV_PAUSE,				// Waits at key until EV_RESUME
		EV_RESUME,				// resumes shot paused by EV_PAUSE
		EV_STOP,				// Stops interpolation, new start with EV_PLAY possible
		EV_GOTO_KEY,			// walks to the specified key	   (time depends on total CS duration)
		EV_SET_DURATION,		// Sets total duration of the shot
		EV_SET_TO_TIME,			// sets cutscene to specified time (secs)
	};

	int	   key;
	zREAL  time;
	zBOOL  isDeleted;
	zTCamTrj_KFType kfType;

	zCCSCamera_EventMsg();
	zCCSCamera_EventMsg(zTCSCam_EvSubType subType);
protected:
	virtual ~zCCSCamera_EventMsg();
public:

	int						GetKey				()								{ return key; };
	zREAL					GetTime				()								{ return time;};
	zTCamTrj_KFType			GetKFType			()								{ return kfType; };

	virtual zBOOL			IsJob				()								{ if (subType == EV_PLAY || subType == EV_GOTO_KEY ) return TRUE; else return FALSE; };
	virtual	zBOOL			IsHighPriority		()								{ return TRUE; };
	virtual zBOOL			IsDeleted			()								{ return isDeleted; };
	virtual	void			Delete				()								{ isDeleted = TRUE; };

	// MetaData	- Subtypes
	virtual int				MD_GetNumOfSubTypes	();
	virtual zSTRING			MD_GetSubTypeString	(int n);

	virtual zTTimeBehavior	MD_GetTimeBehavior	()								{ if (subType == EV_PLAY || subType == EV_GOTO_KEY ) return TBFix; else return TBZero; };
	virtual zREAL			MD_GetMinTime		();

#ifdef COMPILING_SPACER // für den Cutscene sequenzer: ein string, der die Parameter enthält ( in gekürzter aussagekräftiger Form )
	virtual zSTRING			MD_GetInfo			();
	virtual void			MD_SetInfo			(const zSTRING & str);
#endif

protected:
	void					Archive				(zCArchiver &arc);
	void					Unarchive			(zCArchiver &arc);
};

class zCCSCamera_EventMsgActivate : public zCEventMessage {
zCLASS_DECLARATION      (zCCSCamera_EventMsgActivate)
public:
        enum zTCSCam_ActivateSubType {  
                EV_DEACTIVATE = 0,
                EV_SETCAMREFERENCE,
                EV_SETTARGETREFERENCE
        };

		zCCSCamera_EventMsgActivate() : referenceVob(0), referenceName(zSTRING()) { 
			subType = EV_DEACTIVATE;
			isDeleted = FALSE;
		};
        zCCSCamera_EventMsgActivate(zTCSCam_ActivateSubType t)
                : referenceVob(0), referenceName(zSTRING())						  { 
			isDeleted = FALSE;
			subType	  = t; 
		};

private:
        zSTRING                 referenceName;
		zBOOL					isDeleted;

protected:

        virtual ~zCCSCamera_EventMsgActivate()									  { };
        void                    Archive                 (zCArchiver &arc);
        void                    Unarchive               (zCArchiver &arc);

public:
        zCVob*                  referenceVob;

		virtual	zBOOL					IsDeleted			()					  { return isDeleted; };
		virtual	void					Delete				()					  { isDeleted = TRUE; };
        // MetaData     - Subtypes
        virtual int                     MD_GetNumOfSubTypes     ();
        virtual zSTRING                 MD_GetSubTypeString     (int n);

        //                      - Parameter
        virtual zSTRING                 MD_GetVobRefName        ();
        virtual void                    MD_SetVobRefName        (const zSTRING & name);
        virtual void                    MD_SetVobParam          (zCVob* vob);

#ifdef COMPILING_SPACER // für den Cutscene sequenzer: ein string, der die Parameter enthält ( in gekürzter aussagekräftiger Form )
        virtual zSTRING                 MD_GetInfo              ();
        virtual void                    MD_SetInfo              (const zSTRING & str);
#endif

};

class zCCSCamera : public zCVob {
zCLASS_DECLARATION	(zCCSCamera)
public:

	enum zTCamTrj_FOR {
		zCAMTRJ_KEY_FOR_WORLD,
		zCAMTRJ_KEY_FOR_OBJECT
	};

	enum zTCamTrj_LoopMode {
		zCAMTRJ_LOOPMODE_NONE = 0,
		zCAMTRJ_LOOPMODE_RESTART,
		zCAMTRJ_LOOPMODE_PINGPONG
	};

	// public spacer vars
	zTCamTrj_FOR				camKeysFOR;
	zTCamTrj_FOR				targetKeysFOR;
	zTCamTrj_LoopMode			loopMode;
	zTSplLerpMode				splLerpMode;
	zBOOL						ignoreFORVobRotCam; 
	zBOOL						ignoreFORVobRotTarget; 
	zBOOL						adaptToSurroundings;
	zBOOL						easeToFirstKey;
	zBOOL						easeFromLastKey;
	zREAL						totalTime;
	zSTRING						autoCamFocusVobName;
	zBOOL						autoCamPlayerMovable;
	zBOOL						autoCamUntriggerOnLastKey;
	zREAL						autoCamUntriggerOnLastKeyDelay;

	// public spacer vars end

	zCVob*						camKeysRefVob;					// can be any world vob, even this
	zCVob*						targetKeysRefVob;				// can be any world vob, even this

	zCCSCamera();
protected:
	~zCCSCamera();
public:

	static 	zBOOL	GetIsPlaying		()										{ return playing;	};
	static  void	SetDrawEnabled		(const zBOOL b );
	static  zBOOL	GetDrawEnabled		()										{ return draw;		};
	static void		SetEvaluateAvgFPS	(const zBOOL en)						{ evaluateAvgFPS = en; };
	static zBOOL	GetEvaluateAvgFPS	()										{ return evaluateAvgFPS; };
	static zCVob*	GetPlayerVob		();

	// keyframe related methods
	void			InsertCamKey		(zCCamTrj_KeyFrame*key);			
	void			InsertCamKeyAtPos	(zCCamTrj_KeyFrame*key, const int pos);
	void			RemoveCamKey		(zCCamTrj_KeyFrame*key);			
	void			InsertTargetKey		(zCCamTrj_KeyFrame*key);			
	void			InsertTargetKeyAtPos(zCCamTrj_KeyFrame*key,const int pos);
	void			RemoveTargetKey		(zCCamTrj_KeyFrame*key);			
	int				SearchCamKey		(zCCamTrj_KeyFrame*key)					{ return posKeys.Search(key); };					
	int				SearchTargetKey		(zCCamTrj_KeyFrame*key)					{ return targetKeys.Search(key); };					
	int				GetNumCamKeys		()										{ return posKeys.GetNumInList(); };
	int				GetNumTargetKeys	()										{ return targetKeys.GetNumInList();};

	zCCamTrj_KeyFrame*	GetCamKey	(const int num)								{ return (posKeys.GetNumInList()>num ? posKeys[num] : 0);};
	zCCamTrj_KeyFrame*	GetTargetKey(const int num)								{ return (targetKeys.GetNumInList()>num ? targetKeys[num] : 0);};

	void			SetIsAdaptive	(const zBOOL b)								{ adaptToSurroundings = b; };
	zBOOL			GetIsAdaptive	() const									{ return adaptToSurroundings;};
	zPOINT3			GetActFocusPos  () const									{ return actTargetFocus; };
	zREAL			GetProgressTime () const									{ return csTime;};
	zREAL			GetDuration		() const									{ return totalTime; };
	void			SetDuration		(const zREAL duration)						{ totalTime = duration; Refresh(); };

	void			Refresh			();							// call if keyframes moved, times changed, FOR changed etc...
	void			Reset			();							// tmp debug

	void			SetDebugEnabled	(const zBOOL b )							{ d_testCS = b; };

	// virtuals

	virtual void	ThisVobAddedToWorld		(zCWorld *homeWorld);
	virtual void	ThisVobRemovedFromWorld	(zCWorld *homeWorld);

	void			OnMessage		(zCEventMessage *eventMessage, zCVob* sourceVob);
	void			OnTick			();
	void			OnTrigger		(zCVob *otherVob,zCVob *vobInstigator);
	void			OnUntrigger		(zCVob *otherVob,zCVob *vobInstigator);

	void			Archive			(zCArchiver &arc);
	void			Unarchive		(zCArchiver &arc);

private:
	static			zBOOL			playing;
	static			zBOOL			draw;
	static			zBOOL			evaluateAvgFPS;

	zCArray	<zCEventMessage*>	evMsgProcessList;
	zCArray <zCCamTrj_KeyFrame*>posKeys;
	zCArray <zCCamTrj_KeyFrame*>targetKeys;

	zBOOL			paused;
	zBOOL			hasBeenTriggered;
	zBOOL			hasBeenUntriggered;
	zBOOL			triggerQueued;
	zCVob*			queuedVob;
	zBOOL			keysPreProcessed;
	zBOOL			started;
	zBOOL			gotoTimeMode;
	zBOOL			initialized;
	zBOOL			easeToFirstKeyNotPossible;
	zBOOL			easeFromLastKeyNotPossible;
	zBOOL			autoCamPlayerMovable_BAK;
	zBOOL			autoAdjustTime;
	float			avgFPS;
	int				avgFPSNumFrames;
	zREAL			actTimeCam;
	zREAL			csTime;
	zREAL			unTriggerDelayTime;
	zMAT4			trafoCStoWS;
	zREAL			lerpDirSign;
	zREAL			timeToReach;
	zREAL			timeToReachScale;

	zTCamTrj_KFType	camFOVSetBy;
	zTCamTrj_KFType	angleRollDegSetBy;
	zTCamTrj_KFType	globalTimeScaleSetBy;
	
	// debug flags
	zBOOL			d_testCS;

	zCPose			camRefVobPose;
	zCPose			targetRefVobPose;
	zCKBSpline		posSpl;
	zCKBSpline		targetSpl;

	LerpFunc		LerpFuncCam;
	LerpFunc		LerpFuncTarget;

	zMAT4			initialPoseCamRefVob;
	zMAT4			initialPoseTargetRefVob;
	
	zPOINT3			actTargetFocus;

	void			Initialize		();

	int				EV_Play						(zCCSCamera_EventMsg *msg);
	int				EV_Resume					(zCCSCamera_EventMsg *msg);
	int				EV_Pause					(zCCSCamera_EventMsg *msg);
	int				EV_Stop						(zCCSCamera_EventMsg *msg);
	int				EV_GotoKey					(zCCSCamera_EventMsg *msg);	
	int				EV_SetDuration				(zCCSCamera_EventMsg *msg);	
	int				EV_SetTime					(zCCSCamera_EventMsg *msg);	
	int				EV_Deactivate				(zCCSCamera_EventMsgActivate *msg);
	int				EV_SetCamReference			(zCCSCamera_EventMsgActivate *msg);
	int				EV_SetTargetReference		(zCCSCamera_EventMsgActivate *msg);

	void			RecalcTrajectories			();
	void			PreKFProcessing				();
	void			PostKFProcessing			();
	void			AutoSetKeyTimes				(zCArray<zCCamTrj_KeyFrame*>&keys);
	zBOOL			CheckAndCorrectKey			(const int frameNum);
	zBOOL			CheckAndCorrectPose			(zMAT4 &mat);
	zBOOL			CheckAndResetAdjustedKeys	();
	void			DeleteEvMsgOfSubType		(const int subtype);
	void			CalcPrevNextActKeyOfTime	(const zREAL &time,zCArray <zCCamTrj_KeyFrame*>&keys, int &prev, int &next, int &act);
	void			SetAutoSetKeyTimesEnabled	(const zBOOL enabled)								{ autoAdjustTime = enabled;	};
	zBOOL			GetAutoSetKeyTimesEnabled	()	const											{ return autoAdjustTime;		};

	void			Draw						();
	void			Changed						();							// call if any public spacer vars have changed

	// methods of zCAICamera (FIXME: share! )
	zPOINT3			GetPolyNearestPoint			(zCPolygon *poly,const zPOINT3 &checkPt) const;
	zBOOL			IsPointNearWall				(const zPOINT3 &p);
	zBOOL			AdjustCenterSphere			(zPOINT3 &center, const zPOINT3 &b, const float radius = CAMSPHERE_DIAMETER * 0.5F );

};


#endif