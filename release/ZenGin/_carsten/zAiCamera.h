
/****************************************************************
*
* Camera Artificial Intelligence
* File          : zAICamera.h (AI)
* Projekt       : Phoenix
* Autor         : Carsten Edenfeld
* Version       : 0.21b
* last modified : 12.12.98
* erstellt      : 26.02.98
* Compiler OK   :
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


#ifndef __ZAICAMERA_H__
#define __ZAICAMERA_H__


#ifndef __ZAI_H__
#include "zAI.h"
#endif

#ifndef __ZGRAFIX_H__
#include "zGrafix.h"
#endif

#ifndef __ZBVOLUME_H__
#include "zBVolume.h"
#endif

extern	float	CAMSPHERE_DIAMETER;		

const   int		MAX_CTRL_VOBS		   = 80;

class			zCCSCamera;
class			zCMovementTracker;
class			zCPathSearch;
enum			zTAICamMsg;					// tmp
struct			zSPathSearchResult;

extern zSTRING	CamModNormal;
extern zSTRING	CamModRun;
extern zSTRING	CamModDialog;
extern zSTRING	CamModInventory;
extern zSTRING	CamModMelee;
extern zSTRING	CamModMagic;
extern zSTRING	CamModRanged;
extern zSTRING	CamModSwim;
extern zSTRING	CamModDive;
extern zSTRING	CamModJump;
extern zSTRING	CamModJumpUp;
extern zSTRING	CamModClimb;
extern zSTRING	CamModDeath;
extern zSTRING	CamModFirstPerson;
extern zSTRING	CamModThrow;
extern zSTRING	CamModLook;
extern zSTRING  CamModLookBack;
extern zSTRING  CamModFall;

extern int		standardTraceFlags;

class zCAICamera : public zCAIBase 
{
	zCLASS_DECLARATION(zCAICamera)
	friend class zCConsole;				// for editing (ParameterChanged/Console_EvalFunc)
	friend class zCPathSearch;		
	friend class zCMovementTracker;
	friend class zCCSCamera;

	static short int s_iLookAroundSgn;

public:

	// use zCAICamera::Create() to create a new zCAICamera instance. There can be only one instance, therefore 
	// the constructor is explicitly disabled. 
	static	zCAICamera*		Create				();
	static	zCAICamera*		GetCurrent			();

	// enable/disable camera mode changes
	static	void			SetModeChangeEnabled(zBOOL change)				{ bCamChanges = change;	};
	static	zBOOL			GetModeChangeEnabled()							{ return bCamChanges;	};

    // global Init and Cleanup [Moos] (create and destroy parser...)
	static	void			GlobalStartUp		();
    static  void			GlobalCleanUp		();

	static  void			SetLookaroundInverse(zBOOL inv) { s_iLookAroundSgn=(inv)?-1:+1; };
	static  zBOOL			IsLookaroundInverse() { return (s_iLookAroundSgn<0); };

	// main ai
	void			SetVob				(zCVob* vob);
	zCVob*			GetVob				() const							{ return camVob; };
	void			DoAI				(zCVob* vob, zBOOL &vobDeleted);

	// target related
	void			SetTarget			(zCVob* t) ;
	zCVob*			GetTarget			() const							{ return target;	};
	void			SetTargetAlpha		(zREAL alpha)						{ targetAlpha = alpha;	};
	zREAL			GetTargetAlpha		() const							{ return targetAlpha;	};
	void			AddTarget			(zCVob *newTarget);  // add more additional points of interest (POI) for camera
	void			SubTarget			(zCVob *target);
	void			SetTargetList		(zCArray <zCVob *>newTargetList);
	zCArray<zCVob*>&GetTargetList		()									{ return targetVobList;	 }
	void			ClearTargetList		(); 
	zBOOL			TargetInList		(zCVob *vob)						{ return targetVobList.IsInList(vob); };
	int				GetNumTargets		()									{ return numTargets; };
	

	// skripting/mode setting
	void			SetMode				(zSTRING &m, const zCArray <zCVob *>targetList = 0);
	zSTRING			GetMode				();
	zSTRING			GetPreviousMode		()									{ return oldCamSys; };
	zBOOL			IsModeActive		(zSTRING &m);
	zBOOL			IsModeAvailable		(const zSTRING &mode);
	zBOOL			GetHintTargetInPortalRoom() const						{ return targetInPortalRoom;	};
	void			SetHintTargetInPortalRoom(const zBOOL b);
	
	// dialogCam
	void			SetDialogCamDuration(const float duration);
	float			GetDialogCamDuration() const							{ return dialogCamDuration;	};
	
	void			SetRotateEnabled	(const zBOOL r);
	zBOOL			GetRotateEnabled	() const							{ return rotate;			};
	zBOOL			GetPlayerIsMovable  ()									{ return playerIsMovable;	};
	void			SetPlayerIsMovable	(const zBOOL m)						{ playerIsMovable = m;		};
	zBOOL			GetFollowIdealPos	() const							{ return followIdealPos;	};
	void			SetFollowIdealPos	(const zBOOL follow)				{ followIdealPos = follow;	};

	// additional msg/modes (will be eventually set automatically by the movement tracker)
	zREAL			GetMaxRange			();
	zREAL			GetMinRange			();
	zREAL			GetBestRange		();
	zREAL			GetNpcDistOffset	()									{ return npcVolumeRangeOffset;	};

	void			ReceiveMsg			(const zTAICamMsg &msg);

	// public funcs for CamConsole_EvalFunc - make private !
	zBOOL			d_showDots;	  // 
	zBOOL			pathDetectCollision;


protected:
	virtual			~zCAICamera			();			// use Release() instead

	void			StartUp				();
	void			CleanUp				();

	// main move funcs
	void			AI_Normal			();
	void			AI_LookingCam		();
	void			AI_FirstPerson		();

	// scripting
	void			SetName				(zSTRING name); 	
	void			CreateInstance		(zSTRING &instance);
	zBOOL			SetByScript			(zSTRING &instance);
	zSTRING			SetByScriptLine		(zSTRING &command);

	zPOINT3&		GetCamSysFirstPos	();

	// Parser Parametersatz Start

	// range boundaries
	float			bestRange;
	float			minRange;
	float			maxRange;

	// angle boundaries
	float			bestRotX;
	float			minRotX;
	float			maxRotX;
	float			bestRotY;
	float			minRotY;
	float			maxRotY;
	float			bestRotZ;
	float			minRotZ;
	float			maxRotZ;

	// offset angles
	float			rotOffsetX;
	float			rotOffsetY;
	float			rotOffsetZ;

	// focus offset position
	float			focusOffsetX;
	float			focusOffsetY;
	float			focusOffsetZ;

	// dynamic 
	float			veloTrans;			  // velocity while easing   to best position
	float			veloRot;			  // velocity while rotating to best orientation
	
	// feature flags
	zBOOL			translate;			    // translate to target, 1: on, 0: off
	zBOOL			rotate;					// rotate around target, 1: on, 0:off
	zBOOL			collision;			    // disable collision for this mode (ideal pos must be near player)

	// Parser Parametersatz Ende
	zBYTE			endOfDScript;

	zCArray<zCVob*>			targetVobList;			// targetVobs WO player
	zCVob*					camVob;
	zCVob*					target;
	zREAL					targetAlpha;			// target's default alpha (reset to 1.0f on SetTarget()!)
	int						numTargets;				// num point of interests minus player
	zSTRING					oldCamSys;
	zBOOL					sysChanged;
	zBOOL					playerIsMovable;
	zBOOL					followIdealPos;
																				
	#include "zAICamera_Dialog.h"
	#include "zAICamera_Util.h"

	zCPathSearch*			pathSearch;				// main core ai class. finds evasions and puts the result in the var evasionSearchReport
	zCMovementTracker*		moveTracker;			// movement tracker. tracks movement of the camera and all relevant targets
	zSPathSearchResult*		evasionSearchReport;	// evasionsearchreport. set by the zCPathSearch class after a necessary evasionsearch

private:
							zCAICamera			();					// constructor explicitly disabled. Use Create() instead
	void					CheckKeys			();
	void					CalcFirstPosition	();

	zSTRING					curcammode;
	zREAL					npcVolumeRangeOffset;
	zREAL					camDistOffset;
	zPOINT3					camSysFirstPos;
	zBOOL					firstPerson;
	zBOOL					targetInPortalRoom;
	static	zREAL			lookingCamLastAzi;
	static  zBOOL			lookingCamAziGoalReached;

	static	zCAICamera*		current;
	static	zBOOL			bCreated;
	static	zBOOL			bCamChanges;
};


#endif
