#include "zcore.h"
#include "zCSCamera.h"
#include "zMathTools.h"
#include "zDbgTools.h"
#include "zCCSCutscene.h"
#include "zVideo_Win32.h"
#include "zworld.h"

#ifdef COMPILING_GOTHIC
	#include "onpc.h"
#endif

#ifdef COMPILING_SPACER
	#include "windows.h"
#endif

#include "zAccount.h" 


const float timeToEaseToFirstKey = 1;
const float timeToEaseFromLastKey= 1;

static zMAT4		s_camTrafoObjToWorld	= Alg_Identity3D();
static zREAL		s_initialTimeScale		= 1;
static zREAL		s_initialCamFOV			= 90;				// PATCH 1.08! Default Wert auf 90 (vorher 1) gesetzt
static zBOOL		s_inGameCamStored		= FALSE;
static zCCSCamera*	s_actCSObject			= 0;

zBOOL	zCCSCamera :: playing				= FALSE;
zBOOL	zCCSCamera :: draw					= FALSE;
zBOOL 	zCCSCamera :: evaluateAvgFPS		= FALSE;


static zREAL LerpLinear(const zREAL easeIn, const zREAL v0) 
{
	return easeIn;
};

static zREAL LerpStep(const zREAL easeIn, const zREAL v0) 
{
	return 1;
};

static zREAL LerpSlowSlow(const zREAL easeIn, const zREAL v0) 
{
	return zSinusEase(easeIn);
};
static zREAL LerpFastFast(const zREAL easeIn, const zREAL v0) 
{
//	const zREAL _PI = 3.14159265358979323846F;
	return float( (asin(2*easeIn>1)+(M_PI/2)) /M_PI);
};

static zREAL LerpSlowFast(const zREAL easeIn, const zREAL v0)
{
	return (easeIn*easeIn);
};

static zREAL LerpFastSlow(const zREAL easeIn, const zREAL v0)
{
	return easeIn+(easeIn-(easeIn*easeIn));
};
static zREAL LerpSlowLinear(const zREAL easeIn, const zREAL v0) 
{
	return zSinusSlowStart(easeIn);
};

static zREAL LerpLinearSlow(const zREAL easeIn, const zREAL v0) 
{
	return zSinusSlowEnd(easeIn);
};

static zREAL LerpLinearFast(const zREAL easeIn, const zREAL v0) 
{
	if (easeIn <= 0.5F) return easeIn*0.5F;
	else return (0.5F*easeIn+(easeIn-0.5F));
};
static zREAL LerpFastLinear(const zREAL easeIn, const zREAL v0) 
{
	if (easeIn <= 0.5F) return 0.75F+((easeIn-0.5F)*0.5F)-(0.5F-easeIn);
	else return 0.75F+((easeIn-0.5F)*0.5F);
};

static LerpFunc GetLerpFunc(zTCamTrj_KeyMotionType motionIn, zTCamTrj_KeyMotionType motionOut)
{
	switch (motionIn) 
	{
		case zCAMTRJ_KEY_MOTION_SLOW:
			switch(motionOut) 
			{
				case zCAMTRJ_KEY_MOTION_SLOW:  return LerpSlowSlow;   break;
				case zCAMTRJ_KEY_MOTION_STEP:  return LerpStep;       break;
				case zCAMTRJ_KEY_MOTION_SMOOTH:return LerpSlowLinear; break;
				case zCAMTRJ_KEY_MOTION_LINEAR:return LerpSlowLinear; break;
				case zCAMTRJ_KEY_MOTION_FAST:  return LerpSlowFast;	  break;
				default:					   return LerpSlowSlow;   break;
			}
			break;
		case zCAMTRJ_KEY_MOTION_STEP:
			switch(motionOut) 
			{
				case zCAMTRJ_KEY_MOTION_SLOW:  return LerpSlowSlow;   break;
				case zCAMTRJ_KEY_MOTION_STEP:  return LerpStep;       break;
				case zCAMTRJ_KEY_MOTION_SMOOTH:return LerpSlowLinear; break;
				case zCAMTRJ_KEY_MOTION_LINEAR:return LerpSlowLinear; break;
				case zCAMTRJ_KEY_MOTION_FAST:  return LerpSlowFast;	  break;
				default:					   return LerpSlowSlow;   break;
			}
			break;
		case zCAMTRJ_KEY_MOTION_LINEAR:
			switch (motionOut) 
			{
				case zCAMTRJ_KEY_MOTION_SLOW:  return LerpLinearSlow; break;
				case zCAMTRJ_KEY_MOTION_STEP:  return LerpStep;       break;
				case zCAMTRJ_KEY_MOTION_SMOOTH:return LerpLinear;     break;
				case zCAMTRJ_KEY_MOTION_LINEAR:return LerpLinear;     break;
				case zCAMTRJ_KEY_MOTION_FAST:  return LerpLinearFast; break;
				default:					   return LerpLinear;     break;
			}
			break;
		case zCAMTRJ_KEY_MOTION_SMOOTH:
			switch (motionOut) 
			{
				case zCAMTRJ_KEY_MOTION_SLOW:  return LerpLinearSlow; break;
				case zCAMTRJ_KEY_MOTION_STEP:  return LerpStep;		  break;
				case zCAMTRJ_KEY_MOTION_SMOOTH:return LerpLinear;     break;
				case zCAMTRJ_KEY_MOTION_LINEAR:return LerpLinear;     break;
				case zCAMTRJ_KEY_MOTION_FAST:  return LerpLinearFast; break;
				default:					   return LerpLinear;     break;
			}
			break;
		case zCAMTRJ_KEY_MOTION_FAST:
			switch (motionOut) 
			{
				case zCAMTRJ_KEY_MOTION_SLOW:  return LerpFastSlow;	  break;
				case zCAMTRJ_KEY_MOTION_STEP:  return LerpStep;       break;
				case zCAMTRJ_KEY_MOTION_SMOOTH:return LerpFastLinear; break;
				case zCAMTRJ_KEY_MOTION_LINEAR:return LerpFastLinear; break;
				case zCAMTRJ_KEY_MOTION_FAST:  return LerpFastFast;	  break;
				default:					   return LerpLinear;     break;
			}
			break;
		case zCAMTRJ_KEY_MOTION_CUSTOM:
			switch (motionOut) 
			{
				case zCAMTRJ_KEY_MOTION_SLOW: return LerpLinearSlow;  break;
				case zCAMTRJ_KEY_MOTION_STEP: return LerpStep;        break;
				default:					  return LerpLinear;      break;
			}
			break;
		default: return LerpLinear;									  break;
	}

}


// ** zCCamTrj_KeyFrame *********************************************************************************

zCCamTrj_KeyFrame::zCCamTrj_KeyFrame()
{
	time				=	zCS_KEYTIME_UNDEF;
	timeIsFixed			=   FALSE;
	motionType			=	zCAMTRJ_KEY_MOTION_SMOOTH;
	motionTypeFOV		=	zCAMTRJ_KEY_MOTION_SMOOTH;
	motionTypeRoll		=	zCAMTRJ_KEY_MOTION_SMOOTH;
	motionTypeTimeScale = 	zCAMTRJ_KEY_MOTION_SMOOTH;
	adjusted			=   FALSE;
	cscam				=   NULL;
	type				=   KF_UNDEF;
	angleRollDeg		=	0;
	camFOVScale			=	1;
	tension				=	0;
	bias				=	0;
	continuity			=	0;	
	timeScale			=   1;

	originalPose.MakeIdentity();
	actPose     .MakeIdentity();
};
zCCamTrj_KeyFrame::~zCCamTrj_KeyFrame()
{
	// so, jetzt gibts keine Referenz mehr in der Camera auf diesen Keyframe,
	// also Releasen wir cscam
	zRELEASE(cscam);
};

void zCCamTrj_KeyFrame::ThisVobAddedToWorld		(zCWorld *homeWorld)
{	
	zCVob::ThisVobAddedToWorld(homeWorld);
}

void zCCamTrj_KeyFrame::ThisVobRemovedFromWorld	(zCWorld *homeWorld)
{
	zCVob::ThisVobRemovedFromWorld(homeWorld);

	if (cscam) 
	{
		zCCSCamera *currentCam = cscam;
		currentCam->AddRef();
		if (type == KF_CAM)		currentCam->RemoveCamKey	 (this); else
		if (type == KF_TARGET)	currentCam->RemoveTargetKey	 (this);
		currentCam->Refresh();
		zRELEASE(currentCam);
	}
}

void zCCamTrj_KeyFrame::Archive(zCArchiver &arc)
{
	zCVob :: Archive(arc);

	arc.WriteFloat("time"				,time);
	arc.WriteFloat("angleRollDeg"		,angleRollDeg);
	arc.WriteFloat("camFOVScale"		,camFOVScale);
	arc.WriteEnum ("motionType"			,"UNDEF;SMOOTH;LINEAR;STEP;SLOW;FAST;CUSTOM",motionType);
	arc.WriteEnum ("motionTypeFOV"		,"UNDEF;SMOOTH;LINEAR;STEP;SLOW;FAST;CUSTOM",motionTypeFOV);
	arc.WriteEnum ("motionTypeRoll"		,"UNDEF;SMOOTH;LINEAR;STEP;SLOW;FAST;CUSTOM",motionTypeRoll);
	arc.WriteEnum ("motionTypeTimeScale","UNDEF;SMOOTH;LINEAR;STEP;SLOW;FAST;CUSTOM",motionTypeTimeScale);

	arc.WriteGroupBegin	("Details");

	arc.WriteFloat		("tension"		,tension);
	arc.WriteFloat		("bias"			,bias);
	arc.WriteFloat		("continuity"	,continuity);
	arc.WriteFloat		("timeScale"	,timeScale);
	arc.WriteBool		("timeIsFixed"	,timeIsFixed);

	arc.WriteGroupEnd   ("Details");
	
	if (!arc.InProperties()) arc.WriteRaw("originalPose",(void*)&originalPose,sizeof(originalPose));

	if (arc.InSaveGame()) 
	{
	};
};

void zCCamTrj_KeyFrame::Unarchive(zCArchiver &arc)
{
	zCVob :: Unarchive(arc);

	arc.ReadFloat	("time"					,time);
	arc.ReadFloat	("angleRollDeg"			,angleRollDeg);
	arc.ReadFloat	("camFOVScale"			,camFOVScale);

	arc.ReadEnum	("motionType"			,(int&)motionType			);
	arc.ReadEnum	("motionTypeFOV"		,(int&)motionTypeFOV		);
	arc.ReadEnum	("motionTypeRoll"		,(int&)motionTypeRoll		);
	arc.ReadEnum	("motionTypeTimeScale"	,(int&)motionTypeTimeScale	);

	arc.ReadFloat	("tension"				,tension);
	arc.ReadFloat	("bias"					,bias);
	arc.ReadFloat	("continuity"			,continuity);
	arc.ReadFloat	("timeScale"			,timeScale);
	arc.ReadBool	("timeIsFixed"			,timeIsFixed);

	if (!arc.InProperties()) 
	{
		arc.ReadRaw("originalPose",(void*)&originalPose,sizeof(originalPose));
		actPose = originalPose;
	}

};

void zCCamTrj_KeyFrame::Changed()
{
	if (cscam) 
	{
		if (cscam->camKeysFOR == zCCSCamera::zCAMTRJ_KEY_FOR_OBJECT) 
		{
			actPose = cscam->camKeysRefVob->trafoObjToWorld.InverseLinTrafo() * trafoObjToWorld;
		}
		else actPose = trafoObjToWorld;
	}
	originalPose = actPose;
};


#ifdef COMPILING_SPACER
void zCCamTrj_KeyFrame::EndMovement()
{
	zCVob::EndMovement();
	if (cscam) cscam->Refresh();
}
#endif

// ** zCCSCamera *********************************************************************************
// ** statics *********************************************************************************

zCVob* zCCSCamera::GetPlayerVob()
{

#ifdef COMPILING_GOTHIC
	return oCNpc::player;
#endif
	return 0;
};


zCCSCamera::zCCSCamera()
{
	camKeysFOR				=	zCAMTRJ_KEY_FOR_WORLD;
	targetKeysFOR			=   zCAMTRJ_KEY_FOR_WORLD;
	loopMode				=	zCAMTRJ_LOOPMODE_NONE;
	ignoreFORVobRotCam		=	FALSE;
	ignoreFORVobRotTarget	=	FALSE;
	totalTime				=   zCSCAM_DEFAULT_DURATION;
	csTime					=   0;
	started					=	FALSE;
	paused					=	FALSE;
	keysPreProcessed		=	FALSE;
	camKeysRefVob			=	0;
	targetKeysRefVob		=	0;
	LerpFuncCam				=   LerpLinear;
	LerpFuncTarget			=	LerpLinear;
	d_testCS				=   FALSE;
	initialized				=   FALSE;
	initialPoseCamRefVob	=	Alg_Identity3D();
	initialPoseTargetRefVob =	Alg_Identity3D();
	actTimeCam				=	0;
	adaptToSurroundings		=   TRUE;					
	angleRollDegSetBy		=	KF_UNDEF;
	globalTimeScaleSetBy	=	KF_UNDEF;
	camFOVSetBy				=	KF_UNDEF;
	lerpDirSign				=	1;
	gotoTimeMode			=	FALSE;
	timeToReach				=	0;
	timeToReachScale		=   1;
	actTargetFocus			=	zVEC3(0,0,0);
	easeToFirstKey			=	FALSE;
	easeFromLastKey			=	FALSE;
	splLerpMode				=	zTSPL_LERP_PATH;

	easeFromLastKeyNotPossible	= FALSE;
	easeToFirstKeyNotPossible	= FALSE;

	autoCamPlayerMovable		= TRUE;
	autoCamUntriggerOnLastKey	= TRUE;
	autoCamUntriggerOnLastKeyDelay= 0;
	unTriggerDelayTime			= 0;
	hasBeenTriggered			= FALSE;
	hasBeenUntriggered			= FALSE;
	autoAdjustTime				= TRUE;
	avgFPS						= 0;
	avgFPSNumFrames				= 0;
	triggerQueued				= FALSE;
	queuedVob					= 0;
	autoCamPlayerMovable_BAK	= TRUE;

	autoCamFocusVobName.Clear();

	camRefVobPose   .SetInertiaPos(0.2F);
	targetRefVobPose.SetInertiaPos(0.2F);

	//if (zCCamera::activeCam && zCCamera::activeCam->GetVob()) zCCamera::activeCam->GetVob()->AddRef();
};

zCCSCamera::~zCCSCamera()
{

	if (s_actCSObject == this) EV_Stop(0);

	PostKFProcessing();

	if (camKeysRefVob	 == this) camKeysRefVob		= 0;
	if (targetKeysRefVob == this) targetKeysRefVob	= 0;

	zRELEASE(camKeysRefVob);
	zRELEASE(targetKeysRefVob);

    for (int i=evMsgProcessList.GetNum()-1; i>=0; i--){
        zCEventMessage *msg = evMsgProcessList[i];
        zRELEASE(msg);  // [Moos] Leakfix
    }
    evMsgProcessList.DeleteList();

	// FIXME: wieso führt das Releasen hier zum Crash ? 

	/*if (zCCamera::activeCam && zCCamera::activeCam->GetVob()) 
	{
		zCCamera::activeCam->GetVob()->Release();
	}*/

};
 
void zCCSCamera::InsertCamKey		(zCCamTrj_KeyFrame*key)
{ 
	// das incoming Key befindet sich immer im Weltkoordinatensystem
	// die actPose Matrix dagegen bezieht sich immer auf das aktuelle Frame Of Reference Koordinatensystem
	if (camKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) {
		key->actPose = camKeysRefVob->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
	}
	else key->actPose = key->trafoObjToWorld;
	key->originalPose = key->actPose;

	posKeys.InsertEnd(key); 
	key->AddRef();

	key->cscam = this;
	key->cscam->AddRef();

	key->type  = KF_CAM;

	Changed(); 
};
void zCCSCamera::InsertCamKeyAtPos	(zCCamTrj_KeyFrame*key, const int pos)
{ 
	// das incoming Key befindet sich immer im Weltkoordinatensystem
	// die actPose Matrix dagegen bezieht sich immer auf das aktuelle Frame Of Reference Koordinatensystem
	if (camKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) {
		key->actPose = camKeysRefVob->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
	}
	else key->actPose = key->trafoObjToWorld;

	key->originalPose = key->actPose;

	posKeys.InsertAtPos(key,pos); 
	key->AddRef();

	key->cscam = this;
	key->cscam->AddRef();
	key->type  = KF_CAM;

	Changed(); 
};
void zCCSCamera::RemoveCamKey		(zCCamTrj_KeyFrame*key)
{ 
	if (posKeys.IsInList(key)) 
	{	
		posKeys.RemoveOrder(key); 
		zRELEASE(key);
		Changed();
	}
};
void zCCSCamera::InsertTargetKey		(zCCamTrj_KeyFrame*key)
{
	// das incoming Key befindet sich immer im Weltkoordinatensystem
	// die actPose Matrix dagegen bezieht sich immer auf das aktuelle Frame Of Reference Koordinatensystem
	if (targetKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) {
		key->actPose = targetKeysRefVob->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
	}
	else key->actPose = key->trafoObjToWorld;
	key->originalPose = key->actPose;

	targetKeys.InsertEnd(key); 
	key->AddRef();

	key->cscam = this;
	key->cscam->AddRef();
	key->type  = KF_TARGET;

	Changed();	
};
void zCCSCamera::InsertTargetKeyAtPos(zCCamTrj_KeyFrame*key,const int pos)
{
	// das incoming Key befindet sich immer im Weltkoordinatensystem
	// die actPose Matrix dagegen bezieht sich immer auf das aktuelle Frame Of Reference Koordinatensystem
	if (targetKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) {
		key->actPose = targetKeysRefVob->trafoObjToWorld.InverseLinTrafo() * key->trafoObjToWorld;
	}
	else key->actPose = key->trafoObjToWorld;
	key->originalPose = key->actPose;

	targetKeys.InsertAtPos(key,pos); 
	key->AddRef();

	key->cscam = this;
	key->cscam->AddRef();
	key->type  = KF_TARGET;

	Changed();	
};
void zCCSCamera::RemoveTargetKey		(zCCamTrj_KeyFrame*key)
{ 
	if (targetKeys.IsInList(key))
	{	
		targetKeys.RemoveOrder(key); 
		zRELEASE(key);
		Changed();			
	}

};

void zCCSCamera::Refresh()
{
	// das incoming Key befindet sich immer im Weltkoordinatensystem
	// die actPose Matrix dagegen bezieht sich immer auf das aktuelle Frame Of Reference Koordinatensystem
	for (int i=0; i<posKeys.GetNumInList(); i++) 
	{
		if (camKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) {
			if (camKeysRefVob) posKeys[i]->actPose = camKeysRefVob->trafoObjToWorld.InverseLinTrafo() * posKeys[i]->trafoObjToWorld;
		}
		else posKeys[i]->actPose = posKeys[i]->trafoObjToWorld;
	}

	for (i=0; i<targetKeys.GetNumInList(); i++) 
	{
		if (targetKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) {
			if (targetKeysRefVob) targetKeys[i]->actPose = targetKeysRefVob->trafoObjToWorld.InverseLinTrafo() * targetKeys[i]->trafoObjToWorld;
		}
		else targetKeys[i]->actPose = targetKeys[i]->trafoObjToWorld;
	}

	Initialize();
	Changed   ();
};

void zCCSCamera::Draw()
{	
	if (started) {
		if (posKeys.GetNumInList()>0 && posKeys[0]->GetShowVisual()) {
			for (int i=0; i<posKeys.GetNumInList(); i++) {
				posKeys[i]->SetShowVisual(FALSE);
			}
			for (    i=0; i<targetKeys.GetNumInList(); i++) {
				targetKeys[i]->SetShowVisual(FALSE);
			}
		}
		return;
	}
	else {
		if (posKeys.GetNumInList()>0 && !posKeys[0]->GetShowVisual()) {
			SetShowVisual(TRUE);
			for (int i=0; i<posKeys.GetNumInList(); i++) {
				posKeys[i]->SetShowVisual(TRUE);
			}
			for (    i=0; i<targetKeys.GetNumInList(); i++) {
				targetKeys[i]->SetShowVisual(TRUE);
			}
		}
	}

	// Test Part, um die Anpassungsalgos von einer externen Position zu beobachten
#ifdef CHASE_DEBUG
	if (posSpl.GetNumKeys() != 0) {
		if (camKeysFOR == zCAMTRJ_KEY_FOR_WORLD) {
			posSpl.Draw				 (GFX_WHITE);
			posSpl.DrawControlPolygon(GFX_YELLOW);
		} else if (camKeysRefVob && posKeys.GetNumInList() != 0) {
			zMAT4 camMat;
			if (ignoreFORVobRotCam) {
				  camMat = initialPoseCamRefVob;
				  camMat.SetTranslation(camKeysRefVob->GetPositionWorld());
			} else camMat = camKeysRefVob->trafoObjToWorld;
			if (posKeys.GetNumInList()>1) {
				// object FOR splines werden ins Welt Koordinaten System transformiert, und dann gezeichnet
				zCKBSpline spl;
				zCArray<zCPositionKey*>keys;
				for (int i=0; i<posSpl.GetNumKeys(); i++) {
					zCPositionKey *key = zNEW( zCPositionKey );
					key->SetPosition	( camMat * posSpl.GetKey(i)->GetPosition() );
					key->SetBias		( posSpl.GetKey(i)->GetBias() );
					key->SetContinuity	( posSpl.GetKey(i)->GetContinuity() );
					key->SetTension		( posSpl.GetKey(i)->GetTension()	);
					key->SetTime		( posSpl.GetKey(i)->GetTime() );
					// evtl. auch tension, bias, continuity kopieren?
					keys.Insert(key);
				}
				spl.Initialize		  (keys);
				spl.Draw			  (GFX_WHITE);
				spl.DrawControlPolygon(GFX_YELLOW);
			}
		}
	}

	if (targetSpl.GetNumKeys() != 0) {
		if (targetKeysFOR == zCAMTRJ_KEY_FOR_WORLD) {
			targetSpl.Draw				(GFX_GREEN);
			targetSpl.DrawControlPolygon(GFX_BLUE);

		} else if (targetKeysRefVob && targetKeys.GetNumInList() != 0) {
			// object FOR splines werden ins Welt Koordinaten System transformiert, und dann gezeichnet
			zMAT4 targetMat;
			if (ignoreFORVobRotTarget) {
				  targetMat = initialPoseTargetRefVob;
				  targetMat.SetTranslation(targetKeysRefVob->GetPositionWorld());
			} else targetMat = targetKeysRefVob->trafoObjToWorld;
			if (targetKeys.GetNumInList() >1) {
				zCKBSpline spl;
				zCArray<zCPositionKey*>keys;
				for (int i=0; i<targetSpl.GetNumKeys(); i++) {
					zCPositionKey *key = zNEW( zCPositionKey );
					key->SetPosition	( targetMat * targetSpl.GetKey(i)->GetPosition() );
					key->SetBias		( targetSpl.GetKey(i)->GetBias() );
					key->SetContinuity	( targetSpl.GetKey(i)->GetContinuity() );
					key->SetTension		( targetSpl.GetKey(i)->GetTension()	);
					key->SetTime		( targetSpl.GetKey(i)->GetTime() );
					keys.Insert(key);
				}
				spl.Initialize		  (keys);
				spl.Draw			  (GFX_GREEN);
				spl.DrawControlPolygon(GFX_BLUE);
			}
		}
	}
#else

	if (posKeys.GetNumInList()>=2) {
		zCKBSpline spl;
		// FIXME: zCKBSplines need double position keys at start and end
		zCArray <zCPositionKey*> camKeys;

		zCPositionKey *key = zNEW( zCPositionKey );
		key->SetMat			(posKeys[0]->trafoObjToWorld);
		key->SetBias		(posKeys[0]->GetBias()		);
		key->SetTension		(posKeys[0]->GetTension()	);
		key->SetContinuity	(posKeys[0]->GetContinuity());
		key->SetTime		(posKeys[0]->GetTime()		);
 
		camKeys.Insert(key);

		for (int i=0; i<posKeys.GetNumInList(); i++) {
			zCPositionKey *key = zNEW( zCPositionKey );
			key->SetMat			(posKeys[i]->trafoObjToWorld);
			key->SetBias		(posKeys[i]->GetBias()		);
			key->SetTension		(posKeys[i]->GetTension()	);
			key->SetContinuity	(posKeys[i]->GetContinuity());
			key->SetTime		(posKeys[i]->GetTime()		);
			camKeys.Insert(key);
		};

		key = zNEW( zCPositionKey );
		key->SetMat			(posKeys[i-1]->trafoObjToWorld);
		key->SetBias		(posKeys[i-1]->GetBias()	  );
		key->SetTension		(posKeys[i-1]->GetTension()	  );
		key->SetContinuity	(posKeys[i-1]->GetContinuity());
		key->SetTime		(posKeys[i-1]->GetTime()	  );

		camKeys.Insert(key);
		spl.Initialize(camKeys);
		spl.Draw(GFX_WHITE);
	}

	if (targetKeys.GetNumInList()>=2) {
		zCKBSpline spl;
		// FIXME: zCKBSplines need double position keys at start and end
		zCArray <zCPositionKey*> atKeys;

		zCPositionKey *key = zNEW( zCPositionKey );
		key->SetMat			(targetKeys[0]->trafoObjToWorld	);
		key->SetBias		(targetKeys[0]->GetBias()		);
		key->SetTension		(targetKeys[0]->GetTension()	);
		key->SetContinuity	(targetKeys[0]->GetContinuity()	);
		key->SetTime		(targetKeys[0]->GetTime()		);
		atKeys.Insert(key);

		for (int i=0; i<targetKeys.GetNumInList(); i++) {
			zCPositionKey *key = zNEW( zCPositionKey );
			key->SetMat			(targetKeys[i]->trafoObjToWorld	);
			key->SetBias		(targetKeys[i]->GetBias()		);
			key->SetTension		(targetKeys[i]->GetTension()	);
			key->SetContinuity	(targetKeys[i]->GetContinuity()	);
			key->SetTime		(targetKeys[i]->GetTime()		);
			atKeys.Insert(key);
		};

		key = zNEW( zCPositionKey );
		key->SetMat			(targetKeys[i-1]->trafoObjToWorld	);
		key->SetBias		(targetKeys[i-1]->GetBias()			);
		key->SetTension		(targetKeys[i-1]->GetTension()		);
		key->SetContinuity	(targetKeys[i-1]->GetContinuity()	);
		key->SetTime		(targetKeys[i-1]->GetTime()			);
		atKeys.Insert(key);
		spl.Initialize(atKeys);
		spl.Draw(GFX_GREEN);
	}

#endif

};

void zCCSCamera::Archive			(zCArchiver &arc)
{
	zCVob :: Archive(arc);

	arc.WriteEnum	("camTrjFOR"		,"WORLD;OBJECT"			,camKeysFOR);
	arc.WriteEnum	("targetTrjFOR"		,"WORLD;OBJECT"			,targetKeysFOR);
	arc.WriteEnum	("loopMode"			,"NONE;RESTART;PINGPONG",loopMode);
	arc.WriteEnum	("splLerpMode"		,"UNDEF;PATH;PATH_IGNOREROLL;PATH_ROT_SAMPLES",splLerpMode);
	arc.WriteBool	("ignoreFORVobRotCam"			,ignoreFORVobRotCam);
	arc.WriteBool	("ignoreFORVobRotTarget"		,ignoreFORVobRotTarget);
	arc.WriteBool	("adaptToSurroundings"			,adaptToSurroundings);
	arc.WriteBool	("easeToFirstKey"				,easeToFirstKey);
	arc.WriteBool	("easeFromLastKey"				,easeFromLastKey);
	arc.WriteFloat	("totalTime"					,totalTime);
	arc.WriteString	("autoCamFocusVobName"			,autoCamFocusVobName);
	arc.WriteBool	("autoCamPlayerMovable"			,autoCamPlayerMovable);
	arc.WriteBool	("autoCamUntriggerOnLastKey"	,autoCamUntriggerOnLastKey);
	arc.WriteFloat	("autoCamUntriggerOnLastKeyDelay"	,autoCamUntriggerOnLastKeyDelay);

	if (!arc.InProperties()) 
	{
		arc.WriteInt("numPos"						,posKeys.   GetNumInList());
		arc.WriteInt("numTargets"					,targetKeys.GetNumInList());
		for (int i=0; i<posKeys.   GetNumInList(); i++) arc.WriteObject(posKeys[i]);
		for (	 i=0; i<targetKeys.GetNumInList(); i++) arc.WriteObject(targetKeys[i]);
	}

	if (arc.InSaveGame()) 
	{
		arc.WriteBool ("paused"						,paused);
		arc.WriteBool ("started"					,started);
		arc.WriteBool ("gotoTimeMode"				,gotoTimeMode);
		arc.WriteFloat("csTime"						,csTime);
	};
};

void zCCSCamera::Unarchive		(zCArchiver &arc)
{
	zCVob :: Unarchive(arc);
	 
	arc.ReadEnum	("camTrjFOR"						,(int&)camKeysFOR);
	arc.ReadEnum	("targetTrjFOR"						,(int&)targetKeysFOR);
	arc.ReadEnum	("loopMode"							,(int&)loopMode);
	arc.ReadEnum	("splLerpMode"						,(int&)splLerpMode);
	arc.ReadBool	("ignoreFORVobRotCam"				,ignoreFORVobRotCam);
	arc.ReadBool	("ignoreFORVobRotTarget"			,ignoreFORVobRotTarget);
	arc.ReadBool	("adaptToSurroundings"				,adaptToSurroundings);
	arc.ReadBool	("easeToFirstKey"					,easeToFirstKey);
	arc.ReadBool	("easeFromLastKey"					,easeFromLastKey);
	arc.ReadFloat	("totalTime"						,totalTime);
	arc.ReadString	("autoCamFocusVobName"				,autoCamFocusVobName);
	arc.ReadBool	("autoCamPlayerMovable"				,autoCamPlayerMovable);
	arc.ReadBool	("autoCamUntriggerOnLastKey"		,autoCamUntriggerOnLastKey);
	arc.ReadFloat   ("autoCamUntriggerOnLastKeyDelay"	,autoCamUntriggerOnLastKeyDelay);

#if 1
	// FIXME HACK, um ein Datenprob im Gothic Goldmaster zu umgehen
	easeFromLastKey = FALSE;
#endif

	if (!arc.InProperties()) 
	{
		int numPos		= arc.ReadInt("numPos");
		int numTargets	= arc.ReadInt("numTargets");

		for (int i=0; i<numPos; i++)     
		{
			zCCamTrj_KeyFrame* key	= (zCCamTrj_KeyFrame*)arc.ReadObject();

			// FIXME: folgendes Fragment ist nur nötig, da in zCVob::EndMovement() im Block
			// if (!GetHomeWorld()) die trafoObjToWorld falsch berechnet wird
			if (targetKeysFOR == zCAMTRJ_KEY_FOR_OBJECT)
				key->trafoObjToWorld = trafoObjToWorld * key->originalPose;
			else  
				key->trafoObjToWorld = key->originalPose;

			key->cscam				= this;
			key->cscam->AddRef();
			key->type				= KF_CAM;
			posKeys.Insert(key);
			//key->AddRef();
			//zRELEASE(key);
		}
		for (	 i=0; i<numTargets; i++) 
		{
			zCCamTrj_KeyFrame* key = (zCCamTrj_KeyFrame*)arc.ReadObject();

			// FIXME: folgendes Fragment ist nur nötig, da in zCVob::EndMovement() im Block
			// if (!GetHomeWorld()) die trafoObjToWorld falsch berechnet wird
			if (targetKeysFOR == zCAMTRJ_KEY_FOR_OBJECT)
				key->trafoObjToWorld = trafoObjToWorld * key->originalPose;
			else  
				key->trafoObjToWorld = key->originalPose;

			key->cscam = this;
			key->cscam->AddRef();
			key->type  = KF_TARGET;
			targetKeys.Insert(key);
			//key->AddRef();
			//zRELEASE(key);
		}
		
		#ifdef COMPILING_SPACER
		SetSleeping(FALSE);
		#endif
	}

	if (arc.InSaveGame()) 
	{
		arc.ReadBool ("paused"		,paused);
		arc.ReadBool ("started"		,started);
		arc.ReadBool ("gotoTimeMode",gotoTimeMode);
		arc.ReadFloat("csTime"		,csTime);
	};

};

void zCCSCamera::ThisVobAddedToWorld		(zCWorld *homeWorld)
{
	zCVob::ThisVobAddedToWorld(homeWorld);
};

void zCCSCamera::ThisVobRemovedFromWorld	(zCWorld *homeWorld)
{
	zCVob::ThisVobRemovedFromWorld(homeWorld);
	// keyframes releasen

	// safety, in den Keyframes wird ein zRELEASE(this) ausgeführt, vorsichtshalber
	// die Referenz bis zum Ende der Schleife erhöhen
	this->AddRef();

	for (int i=posKeys.GetNumInList()-1; i>=0;    i--) 
	{
		zCCamTrj_KeyFrame *key = posKeys[i];
		posKeys.Remove(key);
		zRELEASE(key);
	}
	for (	 i=targetKeys.GetNumInList()-1; i>=0 ; i--) 
	{
		zCCamTrj_KeyFrame *key  = targetKeys[i];
		targetKeys.Remove(key);
		zRELEASE(key);
	}

	posKeys.DeleteList();
	targetKeys.DeleteList();

	if (s_actCSObject == this) 	
	{
		playing = FALSE;
		zRELEASE(s_actCSObject);
	}

	// und den Safe AddRef wieder aufheben
	this->Release();
};


// event message handler
void zCCSCamera :: OnMessage	(zCEventMessage *eventMessage, zCVob* sourceVob)
{
	if (dynamic_cast<zCCSCamera_EventMsg*>(eventMessage)) 
	{
		zBOOL del = FALSE;
		zCCSCamera_EventMsg * msg = (zCCSCamera_EventMsg*)eventMessage;
		switch	(msg->GetSubType()) 
		{
			case zCCSCamera_EventMsg::EV_PLAY				:	del = EV_Play			(msg);		break;
			case zCCSCamera_EventMsg::EV_PAUSE				:	del = EV_Pause			(msg);		break;
			case zCCSCamera_EventMsg::EV_RESUME				:	del = EV_Resume			(msg);		break;
			case zCCSCamera_EventMsg::EV_STOP				:	del = EV_Stop			(msg);		break;
			case zCCSCamera_EventMsg::EV_GOTO_KEY			:	del = EV_GotoKey		(msg);		break;
			case zCCSCamera_EventMsg::EV_SET_DURATION		:	del = EV_SetDuration    (msg);		break;
			case zCCSCamera_EventMsg::EV_SET_TO_TIME		:	del = EV_SetTime		(msg);		break;
			default:																				break;
		};
		if (del) msg->Delete();
	}
	else if (dynamic_cast<zCCSCamera_EventMsgActivate*>(eventMessage)) 
	{
		zCCSCamera_EventMsgActivate *msg = (zCCSCamera_EventMsgActivate*)eventMessage;
		switch (msg->GetSubType()) 
		{
			case zCCSCamera_EventMsgActivate::EV_DEACTIVATE:				EV_Deactivate(msg);			break;
			case zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE:			EV_SetCamReference(msg);	break;
			case zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE:		EV_SetTargetReference(msg);	break;
			default:																					break;
		};
		msg->Delete();
	}
	else if (dynamic_cast<zCEvMsgCutscene*>(eventMessage)) 
	{
		zCEvMsgCutscene *msg = static_cast<zCEvMsgCutscene*>(eventMessage);
		switch (msg->GetSubType()) 
		{
			case zCEvMsgCutscene::EV_CS_STOP:			EV_Stop(0);		break;
			case zCEvMsgCutscene::EV_CS_INTERRUPT:		EV_Stop(0);		break;
		}
	}
};

// start cutscene or restart it (when stopped with EV_Stop)
int zCCSCamera :: EV_Play			(zCCSCamera_EventMsg *msg)
{

	zERR_MESSAGE(9,0,"C: zCCSCamera :: EV_Play()");

	if ( s_actCSObject && s_actCSObject != this ) 
	{
		// safety. Falls ein zweites anderes CSCam Objekt am laufen war, wird es gestoppt
		s_actCSObject->EV_Stop(0);
	}

	// Diese Message muss zwischengespeichert und gelöscht werden, wenn die CS beendet ist
	if (started) 
	{
		// Es kann sein, daß während einer Cutscene zweimal das gleich Preset
		// gespielt wird, aber mit verschiedenen RefVobs, das bedeutet,
		// es wird ein zweites Mal eine EV_Play Message gesendet. Das ist allerdings ein anderer 
		// pointer, darum schaun wir doch mal, ob dieser schon in der Liste ist.
		// Falls nicht, wird das Ding inserted. Dann müssen alte etwaige Messages gelöscht werden, 
		// und die Zeit reseted werden
		if (!evMsgProcessList.IsInList(msg)) 
		{

			DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_PLAY);
			evMsgProcessList.InsertEnd(msg);
			msg->AddRef();

			csTime		= 0;

			zRELEASE(s_actCSObject);
			s_actCSObject = this;
			s_actCSObject->AddRef();
		}
		return FALSE;
	}

	zRELEASE(s_actCSObject);
	s_actCSObject = this;
	s_actCSObject->AddRef();

	
	float prevTime = totalTime;
	csTime		   = 0;
	totalTime	   = msg->GetTime();

	if (totalTime == zCS_KEYTIME_UNDEF) totalTime = zCSCAM_DEFAULT_DURATION;
	if (gotoTimeMode) 
	{
		DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_GOTO_KEY);
		gotoTimeMode = FALSE;
	}

	started = TRUE;

	Initialize();

	// The time in the given message can differ from the already set up spline, so we have to update the spline
	// in PreKFProcessing(), but it is done only if PostKFProcessig has been called previously
	if (prevTime != totalTime) PostKFProcessing();

	PreKFProcessing();  // set times/lerp modes if not set

	// Remember the current game camera position, but only if no other cutscene cams have already been played
	if (!s_inGameCamStored && zCCamera::activeCam) 
	{
		s_camTrafoObjToWorld	= zCCamera::activeCam->GetVob()->trafoObjToWorld; // temp
		s_initialCamFOV			= zCCamera::activeCam->GetFOV();
		s_initialTimeScale		= ztimer.GetMotionFactor();
		s_inGameCamStored		= TRUE;
	}

	playing = TRUE;

	if (camKeysRefVob)		initialPoseCamRefVob	= camKeysRefVob->trafoObjToWorld;
	if (targetKeysRefVob)	initialPoseTargetRefVob	= targetKeysRefVob->trafoObjToWorld;

	evMsgProcessList.InsertEnd(msg);
	msg->AddRef();
	
	if (evaluateAvgFPS) 
	{
		avgFPS				= 0;
		avgFPSNumFrames		= 0;
	}

	if ( (camKeysFOR	== zCCSCamera::zCAMTRJ_KEY_FOR_OBJECT && camKeysRefVob	  == NULL) ||
		 (targetKeysFOR == zCCSCamera::zCAMTRJ_KEY_FOR_OBJECT && targetKeysRefVob == NULL) ) 

	{
		zERR_WARNING("C: (zCCSCamera :: EV_Play) : Tried to start object frame of reference camera with no reference Vob!");
		return FALSE;
	}

#ifndef COMPILING_SPACER
	SetShowVisual(0);
	for (int i=0; i<this->posKeys.GetNum();    i++) posKeys[i]	 ->SetShowVisual(0);
	for (	 i=0; i<this->targetKeys.GetNum(); i++) targetKeys[i]->SetShowVisual(0);
#endif

	OnTick();

	return FALSE;
};

// resume cutscene when paused
int	zCCSCamera ::EV_Resume		(zCCSCamera_EventMsg *msg)									
{
	if (!paused) return FALSE;
	paused = FALSE;
	return TRUE;
};

int zCCSCamera :: EV_Pause		(zCCSCamera_EventMsg *msg)						
{
	if (!started) zerr.Warning("C: zCCSCamera(zCCSCamera :: EV_Pause): called although not started!");
	paused = TRUE;
	return TRUE;
};

int	zCCSCamera :: EV_Stop			(zCCSCamera_EventMsg *msg)									
{
	zERR_MESSAGE(9,0,"C: zCCSCamera :: EV_Stop()");

	if (s_actCSObject == this) playing = FALSE;

	if (!d_testCS && started) 
	{
		if ( easeFromLastKey && !easeFromLastKeyNotPossible )
		{
			// hier: zusätzlicher dynamisch hinzugefügter letzter Key muss aus der Liste gelöscht werden
			zCCamTrj_KeyFrame *key = posKeys[posKeys.GetNumInList()-1];
			RemoveCamKey(key);

			// FIXME FIXME: komischerweise erhöht sich die Anzahl der posKF's wenn im Destruktor nocheinmal
			// der KF aus der posKey Liste entfernt wird. Auch ein delete key hat den gleichen Effekt
			// Darum HACK:
 
   			// key->cscam = 0; [Moos] Scheint nicht mehr nötig zu sein
			// zRELEASE(key); 

			totalTime -= timeToEaseFromLastKey; 
 
			// nun wieder die Zeiten an allen Keyframes um Faktor timeToEaseToFirstKey vermindern
			for (int kf=0; kf<posKeys.GetNumInList(); kf++) 
			{
				posKeys[kf]->SetTime(posKeys[kf]->GetTime()-timeToEaseToFirstKey);
			}
		}

		if ( easeToFirstKey && !easeToFirstKeyNotPossible ) 
		{
			// hier: zusätzlicher dynamisch hinzugefügter erster Key muss aus der Liste gelöscht werden
			zCCamTrj_KeyFrame *key = posKeys[0];
			RemoveCamKey(key);


			// FIXME FIXME: komischerweise erhöht sich die Anzahl der posKF's wenn im Destruktor nocheinmal
			// der KF aus der posKey Liste entfernt wird. Auch ein delete key hat den gleichen Effekt
			// Darum HACK:

    		// key->cscam = 0; [Moos] Scheint nicht mehr nötig zu sein
			// zRELEASE(key);  

			totalTime -= timeToEaseToFirstKey;
		}

		// Camera muss zur besten Position der in Game AI zurückswitchen wenn
		// Spieler beweglich & easeFromLastKey auf FALSE

		// Im Spacer soll beim Drücken auf den Stop Button auf jeden Fall
		// immer auf die letzte bekannte Position zurückgeswitcht werden
#ifdef COMPILING_SPACER
		zBOOL playerCanMove = FALSE;
#else
		zBOOL playerCanMove = autoCamPlayerMovable;
#endif

		if ( GetEM()->GetCutscene() && GetEM()->GetCutscene()->IsGlobalCutscene() )
		{
			playerCanMove = FALSE;
		}

		if (playerCanMove && !easeFromLastKey ) 
		{
			if (zCAICamera::GetCurrent())
			{
				zCAICamera::GetCurrent()->ReceiveMsg(zPLAYER_BEAMED);
			}
		} 
		else if (zCCamera::activeCam)
		{
			zCCamera::activeCam->GetVob()->SetTrafo(s_camTrafoObjToWorld); 
			zCCamera::activeCam->SetFOV(s_initialCamFOV);
			ztimer.SetMotionFactor(s_initialTimeScale);
		}

		s_inGameCamStored = FALSE;

		if (evaluateAvgFPS) 
		{ 
			avgFPS /= avgFPSNumFrames;
			zERR_WARNING("C: evaluated avg fps:" + zSTRING(avgFPS));
			evaluateAvgFPS = FALSE;
		}
	}

	DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_PLAY);
	DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_GOTO_KEY);

	if (zCAICamera::GetCurrent()) zCAICamera::GetCurrent()->SetPlayerIsMovable(autoCamPlayerMovable_BAK);

	started = FALSE;

	return TRUE;
};

int	zCCSCamera :: EV_GotoKey (zCCSCamera_EventMsg *msg)					
{
	// Diese Message muss zwischengespeichert und gelöscht werden, wenn der gewünschte KF erreicht wurde
	zREAL time;

	if (!started) 
	{
		started = TRUE;

		Initialize     ();
		PreKFProcessing();  // set times/lerp modes if not set

		if (!s_inGameCamStored && zCCamera::activeCam) 
		{
			s_camTrafoObjToWorld  = zCCamera::activeCam->GetVob()->trafoObjToWorld; // temp
			s_initialCamFOV		  = zCCamera::activeCam->GetFOV();
			s_initialTimeScale	  = ztimer.GetMotionFactor();
			s_inGameCamStored	  = TRUE;
		}
		if (!GetVisual()) playing = TRUE;

		if (camKeysRefVob)		initialPoseCamRefVob	= camKeysRefVob->trafoObjToWorld;
		if (targetKeysRefVob)	initialPoseTargetRefVob	= targetKeysRefVob->trafoObjToWorld;

		for (int i=0; i<posKeys.GetNumInList(); i++) posKeys[i]->actPose= posKeys[i]->originalPose;


		zRELEASE(s_actCSObject);
		s_actCSObject = this;
		if (s_actCSObject) s_actCSObject->AddRef();
	}

	if ( msg->GetKFType()==KF_UNDEF) 
	{
		zERR_WARNING("C: zCSCamera.cpp(zCCSCamera :: EV_GotoKey): Illegal key type for EV_GOTO_KEY Message");
		msg->kfType = KF_CAM;
	}

	if ( msg->GetKFType()==KF_CAM) 
	{
		if ( msg->GetKey() < 0 || msg->GetKey()>posKeys.GetNumInList()-1 ) 
		{
			zERR_WARNING("C: zCSCamera.cpp(zCCSCamera :: EV_GotoKey): Illegal key number for EV_GOTO_KEY Message");
			msg->key = 0;
		}
		time = posKeys[msg->GetKey()]->GetTime();
	}
	else if ( msg->GetKFType()==KF_TARGET ) 
	{
		if ( msg->GetKey() < 0 || targetKeys.GetNumInList() == 0 || msg->GetKey()>targetKeys.GetNumInList()-1 ) 
		{
			zERR_WARNING("C: zCSCamera.cpp(zCCSCamera :: EV_GotoKey): Illegal key number for EV_GOTO_KEY Message");
			msg->key = 0;
		}
		else time = targetKeys[msg->GetKey()]->GetTime();
	}

	if (gotoTimeMode && time == timeToReach) return FALSE;

	gotoTimeMode = TRUE;

	if (time == zCS_KEYTIME_UNDEF) 	timeToReach = 0;
	else							timeToReach = time;

	if (timeToReach < csTime) lerpDirSign = -1;
	else					  lerpDirSign = +1;

	// Finde die Skalierung, um die korrekte Zeitdauer bis zum Erreichen des gewünschten KF zu gewährleisten
	timeToReachScale = zAbs(timeToReach-csTime)/msg->GetTime();

	evMsgProcessList.InsertEnd(msg);
	msg->AddRef();

	return FALSE;
};	


int	zCCSCamera :: EV_SetDuration  (zCCSCamera_EventMsg *msg)
{
	totalTime =  msg->GetTime();
	Changed();
	return TRUE;
};

 
int	zCCSCamera :: EV_SetTime		(zCCSCamera_EventMsg *msg)
{
	csTime = msg->GetTime();
	return TRUE;
};

int	zCCSCamera :: EV_Deactivate		(zCCSCamera_EventMsgActivate *msg)
{
	initialized				=	FALSE;
	csTime					=   0;
	actTimeCam				=	0;
	started					=	FALSE;
	paused					=	FALSE;
	keysPreProcessed		=	FALSE;
	camKeysRefVob			=	0;
	targetKeysRefVob		=	0;
	initialPoseCamRefVob	=	Alg_Identity3D();
	initialPoseTargetRefVob =	Alg_Identity3D();

	return TRUE;
};

int	zCCSCamera :: EV_SetCamReference(zCCSCamera_EventMsgActivate *msg)
{ 
	zRELEASE(camKeysRefVob);
	camKeysRefVob = msg->referenceVob;
	
	if ( camKeysRefVob == NULL ) camKeysRefVob = this;
	zADDREF_ACCT(camKeysRefVob);
	
	camRefVobPose.SetPose(camKeysRefVob->trafoObjToWorld);

	return TRUE;
};
 
int	zCCSCamera :: EV_SetTargetReference	(zCCSCamera_EventMsgActivate *msg)
{
	zRELEASE(targetKeysRefVob);
	
	targetKeysRefVob = msg->referenceVob;

	if ( targetKeysRefVob == NULL ) targetKeysRefVob = this;
	zADDREF_ACCT(targetKeysRefVob);

	targetRefVobPose.SetPose(targetKeysRefVob->trafoObjToWorld);

	return TRUE;
};

void zCCSCamera :: DeleteEvMsgOfSubType(const int subType) 
{
	// check list of processing event messages for given subType msg and delete it
	for (int i=0; i<evMsgProcessList.GetNumInList(); i++) 
	{
		if (evMsgProcessList[i]->GetSubType()==subType) 
		{
			zCEventMessage *msg = evMsgProcessList[i];
			msg -> Delete();
			evMsgProcessList.Remove(msg);
			zRELEASE(msg);
			return;
		}
	}
};

// called per frame
void zCCSCamera :: OnTick			()
{
	if (triggerQueued)
	{
		if ( zCCamera::activeCam && zCCamera::activeCam->GetVob() ) 
		{
			triggerQueued = FALSE;
			OnTrigger(queuedVob,queuedVob);
		}
		else return;
	}

	if (started) 
	{
		if (adaptToSurroundings) RecalcTrajectories();
		if (camKeysRefVob)		 camRefVobPose   .UpdatePose(camKeysRefVob->trafoObjToWorld);
		if (targetKeysRefVob)	 targetRefVobPose.UpdatePose(targetKeysRefVob->trafoObjToWorld);

		if (evaluateAvgFPS) 
		{ 
			avgFPS += (float)vidGetFPSRate();
			avgFPSNumFrames ++;
		}

		if (!paused) 
		{

			if (posKeys.GetNumInList() == 0) return;

			// interpolate through all given keys
			zREAL frameTime = ztimer.GetFrameTimeF()/ztimer.GetMotionFactor()/1000; 
			csTime += frameTime*lerpDirSign*timeToReachScale;

			if (gotoTimeMode) 
			if ( (lerpDirSign == 1 && csTime>=timeToReach) || (lerpDirSign == -1 && csTime<=timeToReach) ) 
			{
				csTime = timeToReach;
				DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_GOTO_KEY);
			}

			// folgender Block muss aufgerufen werden, um ein korrektes zurücklaufen der KF
			// auf die Startposition zu gewährleisten, falls easeFromLastKey gesetzt wurde
			if ( hasBeenTriggered && easeFromLastKey && !easeFromLastKeyNotPossible && !autoCamUntriggerOnLastKey)
			{ 
				float fixedTime = GetCamKey( GetNumCamKeys()-2)->GetTime();
				if ( csTime > fixedTime ) 
				{
					if (!hasBeenUntriggered) 
					{
						// wir müssen warten, bis ein Untrigger manuell von aussen erfolgte
						// bis dahin darf die Zeit nicht weiterlaufen
						csTime = fixedTime;
					}
				}

			}

			if (csTime > totalTime) 
			{

				if (hasBeenTriggered && autoCamUntriggerOnLastKey) 
				{
					unTriggerDelayTime += frameTime;
					if (unTriggerDelayTime >= autoCamUntriggerOnLastKeyDelay)
					{
						unTriggerDelayTime = 0;
						OnUntrigger(0,0);
						return;
					}
				}

				if (s_actCSObject != this) return;	// nur weitermachen, wenn innerhalb derselben Cutscene nicht ein anderes aktuelleres CS Objekt abgespielt wird

				if (loopMode == zCAMTRJ_LOOPMODE_NONE) 
				{
					if (playing && evaluateAvgFPS) 
					{
						avgFPS /= avgFPSNumFrames;
						zERR_WARNING("C: evaluated avg fps:" + zSTRING(avgFPS));
						evaluateAvgFPS = FALSE;
					}

					if (autoCamUntriggerOnLastKey) playing= FALSE;		// reicht der test auf autoCamUntriggerOnLastKey ?
					csTime = totalTime;
					DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_PLAY);
					DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_GOTO_KEY);
				}
				else if (loopMode == zCAMTRJ_LOOPMODE_RESTART) 
				{
					csTime = 0;
				}
				else if (loopMode == zCAMTRJ_LOOPMODE_PINGPONG) 
				{
					csTime		= totalTime;
					lerpDirSign = -1;
				}
			}
			else if (csTime < 0) 
			{
				csTime		= 0;
				lerpDirSign = 1;
			}

			// Unterwasser Effekt prüfen, FIXME: besser irgendwie statisch in zCAICamera packen und dort vom Game regelmässig aufrufen
			if (zCAICamera::GetCurrent()) zCAICamera::GetCurrent()->CheckUnderWaterFX();

			// ok, now find the keys through which we have to interpolate 

			zMAT4 finalPose				= posKeys[0]->actPose;
			zMAT4 targetPose			= Alg_Identity3D();
			zREAL camFOVScale			= 1;
			zREAL globalTimeScale		= 1;
			zREAL angleRollDeg			= 0;
			zBOOL poseSetByCamSpline	= FALSE;

			// Calc final position & orientation for the camera in three steps
			// 1. calc the actual position on the camera spline
			if (posKeys.GetNumInList() > 1) 
			{
				// position spline, first key
				int prev = 0, next = 0,act = 0;

				CalcPrevNextActKeyOfTime(csTime,posKeys,prev,next,act);

				// all right, now we should have start and end key -> interpolate					
				LerpFuncCam = GetLerpFunc(posKeys[prev]->GetMotionType(), posKeys[next]->GetMotionType());

				zREAL tmin				= posKeys[prev]->GetTime(), tmax = posKeys[next]->GetTime();
				zREAL easeIn			= (csTime - tmin)/(tmax - tmin);
				zREAL easeOut			= LerpFuncCam(easeIn);
				if (easeOut>1) easeOut  = 1;
				actTimeCam				= Lerp( easeOut , tmin, tmax  );
				zTSplLerpMode lerpMode	= splLerpMode;

				if (     easeToFirstKey   && !easeToFirstKeyNotPossible  && actTimeCam < posKeys[1]->GetTime() ) 
				{
					lerpMode		   = zTSPL_LERP_PATH_ROT_SAMPLES;
					poseSetByCamSpline = TRUE;
				}
				else if ( easeFromLastKey && !easeFromLastKeyNotPossible && actTimeCam > posKeys[posKeys.GetNumInList()-2]->GetTime() ) 
				{
					lerpMode		   = zTSPL_LERP_PATH_ROT_SAMPLES;
					poseSetByCamSpline = TRUE;
				}

				posSpl.Interpolate( actTimeCam, finalPose,lerpMode ); 

				tmin		= posKeys[act]->GetTime(), tmax = posKeys[act+1]->GetTime();
				easeIn		= (csTime - tmin)/(tmax - tmin);

				if (camFOVSetBy == KF_CAM) 
				{
					LerpFuncCam = GetLerpFunc(posKeys[act]->GetMotionTypeFOV(), posKeys[act+1]->GetMotionTypeFOV());
					easeOut		= LerpFuncCam(easeIn);
					if (easeOut>1) easeOut = 1;
					camFOVScale = Lerp(easeOut,posKeys[act]->GetCamFOVScale(),posKeys[act+1]->GetCamFOVScale());
				}

				if (angleRollDegSetBy == KF_CAM) 
				{
					LerpFuncCam = GetLerpFunc(posKeys[act]->GetMotionTypeRoll(), posKeys[act+1]->GetMotionTypeRoll());
					easeOut		= LerpFuncCam(easeIn);
					if (easeOut>1) easeOut = 1;
					angleRollDeg= Lerp(easeOut,posKeys[act]->GetAngleRollDeg(),posKeys[act+1]->GetAngleRollDeg());
				}
				
				if (globalTimeScaleSetBy == KF_CAM)
				{
					LerpFuncCam		= GetLerpFunc(posKeys[act]->GetMotionTypeRoll(), posKeys[act+1]->GetMotionTypeRoll());
					easeOut			= LerpFuncCam(easeIn);
					if (easeOut>1) easeOut = 1;
					globalTimeScale	= Lerp(easeOut,posKeys[act]->GetTimeScale(),posKeys[act+1]->GetTimeScale());
				};
			} 

			if (camKeysFOR == zCAMTRJ_KEY_FOR_OBJECT && camKeysRefVob != 0) 
			{
				if (ignoreFORVobRotCam) 
				{
					initialPoseCamRefVob.SetTranslation(camRefVobPose.GetPos());
					finalPose = initialPoseCamRefVob * finalPose;
				} else finalPose = camRefVobPose.GetPose() * finalPose;
			}

			int numTargets = targetKeys.GetNumInList();
			
			// 2. calc the position on the target spline on which the camera has to look
			if ( !poseSetByCamSpline ) 
			{
				if ( numTargets == 1 ) 
				{
					targetPose = targetKeys[0]->actPose;
				}
				else if ( numTargets > 1 ) 
				{
					// target spline, first key
					int prev = 0, next = 0,act=0;
					
					float timeOffset = 0;
					
					// folgender timeoffset ist notwendig, damit auf den korrekten Target Key geschaut wird,
					// wenn ein fliessender Übergang von der in Game Camera gewünscht ist (d.h. easeToFirstKey = TRUE)
					if (easeToFirstKey && !easeToFirstKeyNotPossible) timeOffset = timeToEaseToFirstKey;

					CalcPrevNextActKeyOfTime(csTime-timeOffset,targetKeys,prev,next,act);

					// all right, now we should have start and end key -> interpolate
					
					LerpFuncTarget  = GetLerpFunc(targetKeys[prev]->GetMotionType(), targetKeys[next]->GetMotionType());

					zREAL tmin		= targetKeys[prev]->GetTime(), tmax = targetKeys[next]->GetTime();
					zREAL easeIn	= ( (csTime-timeOffset) - tmin)/(tmax - tmin);
					zREAL easeOut   = LerpFuncTarget(easeIn);
					if (easeOut>1) easeOut = 1;

					targetSpl.Interpolate( Lerp(easeOut,tmin,tmax), targetPose ); 

					// FIXME: warum andere Keyframes für FOV/angleRoll/timeScale ?
					tmin		= targetKeys[act]->GetTime(), tmax = targetKeys[act+1]->GetTime();
					easeIn		= ( (csTime-timeOffset) - tmin)/(tmax - tmin);

					if (camFOVSetBy == KF_TARGET) 
					{
						LerpFuncTarget  = GetLerpFunc(targetKeys[act]->GetMotionTypeFOV(), targetKeys[act+1]->GetMotionTypeFOV());
						easeOut			= LerpFuncTarget(easeIn);
						if (easeOut>1) easeOut = 1;
						camFOVScale		= Lerp(easeOut,targetKeys[act]->GetCamFOVScale(),targetKeys[act+1]->GetCamFOVScale());
					}

					if (angleRollDegSetBy == KF_TARGET) 
					{
						LerpFuncTarget  = GetLerpFunc(targetKeys[act]->GetMotionTypeRoll(), targetKeys[act+1]->GetMotionTypeRoll());
						easeOut			= LerpFuncTarget(easeIn);
						if (easeOut>1)  easeOut = 1;
						angleRollDeg	= Lerp(easeOut,targetKeys[act]->GetAngleRollDeg(),targetKeys[act+1]->GetAngleRollDeg());
					}
					
					if (globalTimeScaleSetBy == KF_TARGET)
					{
						LerpFuncTarget	= GetLerpFunc(targetKeys[act]->GetMotionTypeTimeScale(), targetKeys[act+1]->GetMotionTypeTimeScale());
						easeOut			= LerpFuncTarget(easeIn);
						if (easeOut>1)  easeOut=1;
						globalTimeScale	= Lerp(easeOut,targetKeys[act]->GetTimeScale(),targetKeys[act+1]->GetTimeScale());
					};

				};

				// 3. merge step 1 and 2 into finalPose
				if (numTargets != 0) 
				{
					if (targetKeysFOR == zCAMTRJ_KEY_FOR_OBJECT && targetKeysRefVob != 0) 
					{
						if (ignoreFORVobRotCam) 
						{
							initialPoseTargetRefVob.SetTranslation(targetRefVobPose.GetPos());
							targetPose = initialPoseTargetRefVob * targetPose;
						} else targetPose = targetRefVobPose.GetPose() * targetPose;
					}

					actTargetFocus = targetPose.GetTranslation();
					finalPose = GetPoseOfHeading(finalPose.GetTranslation(), (actTargetFocus-finalPose.GetTranslation()).Normalize());
				}
			}

			zBOOL changed = FALSE;
			if (adaptToSurroundings) changed = !CheckAndCorrectPose(finalPose);
			
			// apply rolloff to the finalPose
			finalPose.PostRotateZ(angleRollDeg);		

			trafoCStoWS = finalPose;

			if (changed) Changed();

			if (!d_testCS) 
			{
				zCCamera::activeCam->SetFOV(camFOVScale*s_initialCamFOV);
				zCCamera::activeCam->SetUpFrustum();
				zCCamera::activeCam->GetVob()->SetTrafo(finalPose);
				ztimer.SetMotionFactor(globalTimeScale * s_initialTimeScale);
			}
		}

	}
	if (draw) Draw();
};

void zCCSCamera :: OnTrigger(zCVob *otherVob,zCVob *vobInstigator) 
{
	zERR_MESSAGE(8,0,"C: zCCSCamera :: OnTrigger()");

	// es kann sein, das eine in der Welt befindliche zCCSCamera Instanz getriggert wird, 
	// _bevor_ die RenderCamera aktiviert wurde (z.B. bei Level Change Camerafahrten)
	// in diesem Fall darf die Fahrt erst gestartet werden, wenn die RenderCamera exisitiert
	if ( !zCCamera::activeCam || !zCCamera::activeCam->GetVob() )
	{
		triggerQueued = TRUE;
		queuedVob     = vobInstigator;
		return;
	}

	zCVob *refVob = vobInstigator;
	if (hasBeenTriggered) return;

	// Die Kamera wird hier getriggert. Falls es einen triggerInstigator gibt, und der autoCamFocusVobName
	// leer ist, wird dieser genommen, ansonsten nur, wenn es den angebeben Vob Namen nicht gibt

	if (!autoCamFocusVobName.IsEmpty()) 
	{
		if (GetHomeWorld()) 
		{
			refVob = GetHomeWorld()->SearchVobByName(autoCamFocusVobName);
			if (autoCamFocusVobName == "_PLAYER") refVob = GetPlayerVob();
			if (!refVob) refVob = otherVob;
		}
	}
	
	if (zCAICamera::GetCurrent()) 
	{
		autoCamPlayerMovable_BAK = zCAICamera::GetCurrent()->GetPlayerIsMovable();
		zCAICamera::GetCurrent()->SetPlayerIsMovable(autoCamPlayerMovable);
	}

	// falls es noch keine Keys gibt, werden diese jetzt der einfachkeit halber hinzugefügt

	if (camKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) 
	{
		zCCSCamera_EventMsgActivate* msg_c = zNEW( zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETCAMREFERENCE) );
		msg_c->MD_SetVobParam(refVob);
		EV_SetCamReference(msg_c);
		zRELEASE(msg_c);
	} 
	else if (posKeys.GetNumInList() == 0) 
	{
		zCCamTrj_KeyFrame *newkey	= zNEW( zCCamTrj_KeyFrame );
		// [HILDEBRANDT] Zugriff auf zCVob::trafo unterbunden zwecks Kapselung.
		newkey->SetTrafoObjToWorld	(Alg_Identity3D());
		// newkey->trafo			= Alg_Identity3D();
		// newkey->trafoObjToWorld	= trafoObjToWorld;
		InsertCamKey				(newkey);
	}

	if (targetKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) 
	{
		zCCSCamera_EventMsgActivate* msg_t = zNEW( zCCSCamera_EventMsgActivate(zCCSCamera_EventMsgActivate::EV_SETTARGETREFERENCE) );
		msg_t->MD_SetVobParam(refVob);
		EV_SetTargetReference(msg_t);
		zRELEASE(msg_t);
	} 
	else if (targetKeys.GetNumInList()==0) 
	{
		zCCamTrj_KeyFrame *newkey	= zNEW( zCCamTrj_KeyFrame );
		// [HILDEBRANDT] Zugriff auf zCVob::trafo unterbunden zwecks Kapselung.
		newkey->SetTrafoObjToWorld	(refVob ? refVob->trafoObjToWorld : this->trafoObjToWorld);
//		newkey->trafo				= Alg_Identity3D();
//		newkey->trafoObjToWorld		= refVob ? refVob->trafoObjToWorld : this->trafoObjToWorld;
		InsertTargetKey				(newkey);
	}

	zCCSCamera_EventMsg* msg = zNEW( zCCSCamera_EventMsg(zCCSCamera_EventMsg::EV_PLAY) );
	msg->time				 = totalTime;

	EV_Play(msg);
	DeleteEvMsgOfSubType(zCCSCamera_EventMsg::EV_PLAY);
	zRELEASE(msg);

	SetSleeping(FALSE);

	if ( !autoCamPlayerMovable && !autoCamUntriggerOnLastKey ) 
	{
		zERR_WARNING("C: (zCCSCamera :: EV_Play): 	autoCamPlayerMovable and autoCamUntriggerOnLastKey are both FALSE => player can't untrigger camera");
	}

	hasBeenTriggered	= TRUE;
	hasBeenUntriggered	= FALSE;

	if (evaluateAvgFPS) 
	{
		avgFPS				= 0;
		avgFPSNumFrames		= 0;
	}

};

void zCCSCamera :: OnUntrigger(zCVob *otherVob,zCVob *vobInstigator) 
{
	zERR_MESSAGE(8,0,"C: zCCSCamera :: OnUntrigger()");

	hasBeenUntriggered = TRUE;

	if (evaluateAvgFPS) 
	{
		avgFPS /= avgFPSNumFrames;
		zERR_WARNING("C: evaluated avg fps:" + zSTRING(avgFPS));
		evaluateAvgFPS = FALSE;
	}

	EV_Stop(0);

	hasBeenTriggered = FALSE;

};

// need eventually to readjust to the surrounding scene, only if an object "frame of reference" is given
void zCCSCamera :: RecalcTrajectories()
{
	/*  Algo: 
		Letzte eingefügte Position entfernen
		Aktuelle Position als Keyframe einfügen. (nicht immer nötig!)
		justierte Keys ggfs. wieder zum Originalzustand
		Nachfolgende Keys checken und ggfs. justieren
		interpol. Falls nicht gültig justieren */

	/* Man könnte auch mehrere Tests durchführen:
	   - Intra Key visibility
	   - Sphere Test
	   - Von der aktuellen Position bis zum nächsten Keyframe alle paar cm rays casten (alle paar frames ?)
	*/
	const int NUM_KEYS_PRE_CHECK = 3;

	zBOOL changed = FALSE;

	if (!CheckAndResetAdjustedKeys()) changed = TRUE;

	if (camKeysFOR == zCAMTRJ_KEY_FOR_OBJECT) 
	{
		int numKeysPreChecked = 0;
		for (int i=0; i<posKeys.GetNumInList(); i++) 
		{
			zCCamTrj_KeyFrame *key = posKeys[i];
			if (key->GetTime() >= csTime) 
			{
				if (numKeysPreChecked ++ < NUM_KEYS_PRE_CHECK) 
				{
					if (!CheckAndCorrectKey(i)) changed = TRUE;
				} else break;
			}
		}
	}
	if (changed) Changed();
};


// returns FALSE if any keys reseted
zBOOL zCCSCamera :: CheckAndResetAdjustedKeys() 
{
	zBOOL anyReseted = FALSE;
	for (int i=0; i<posKeys.GetNumInList(); i++) 
	{
		if (posKeys[i]->adjusted) 
		{
			zMAT4 trafo	  = camKeysRefVob->trafoObjToWorld * posKeys[i]->originalPose;
			if (CheckAndCorrectPose(trafo)) 
			{
				posKeys[i]->adjusted	= FALSE;
				posKeys[i]->actPose		= posKeys[i]->originalPose;
				anyReseted				= TRUE;
			}
		}
	}
	return !anyReseted;
};

zBOOL zCCSCamera :: CheckAndCorrectKey(const int frameNum) 
{
	zCCamTrj_KeyFrame*	key		= posKeys[frameNum];
	zMAT4				trafo	= camKeysRefVob->trafoObjToWorld * key->actPose;

	if (!CheckAndCorrectPose(trafo)) 
	{
		key->adjusted	= TRUE;
		key->actPose	= camKeysRefVob->trafoObjToWorld.InverseLinTrafo() * trafo;
		return FALSE;
	}
	return TRUE;
};

zBOOL zCCSCamera :: CheckAndCorrectPose			(zMAT4 &mat)
{
	if (!camKeysRefVob) return TRUE;

	zVEC3 ray = mat.GetTranslation()-camKeysRefVob->GetPositionWorld();

	if (IsPointNearWall(mat.GetTranslation())) 
	{
		zPOINT3 pos = mat.GetTranslation();
		AdjustCenterSphere(pos,camKeysRefVob->GetPositionWorld());
		mat.SetTranslation(pos);
		return FALSE;
	}
	else if (GetHomeWorld()->TraceRayFirstHit(camKeysRefVob->GetPositionWorld(), ray, camKeysRefVob, zTRACERAY_VOB_IGNORE_NO_CD_DYN|zTRACERAY_STAT_POLY|zTRACERAY_POLY_IGNORE_TRANSP|zTRACERAY_VOB_IGNORE_CHARACTER)) 
	{
		mat.SetTranslation(GetHomeWorld()->traceRayReport.foundIntersection - (CAMSPHERE_DIAMETER * 0.51F* ray.NormalizeApprox())); 
		return FALSE;
	}

	return TRUE;
};


/* ----------------------------------------------------------------------
	
    zCCSCamera::PreKFProcessing()	

	8.09.2000	[Moos]	
                Leakfix
	13.09.2000  [Edenfeld]	Leakfix entfernt

   ---------------------------------------------------------------------- */

void zCCSCamera :: PreKFProcessing()
{
	// TODO: hier auch z.B. bei Dialogkameras checken, ob mit einer Spiegelung an der Line of interest
	// bessere/korrekte Ergebnisse erzielt werden
	
	if (keysPreProcessed) return;

	int i				= 0; 
	int numCamKeys		= posKeys.GetNumInList();
	int numTargetKeys	= targetKeys.GetNumInList();

	// here find out which keyframes are responsible for special fx like camera fov change or
	// camera roll of factor
	for (	i=0; i<posKeys.GetNumInList(); i++) 
	{
		if ( posKeys[i]->camFOVScale!=1 )		camFOVSetBy			 = KF_CAM;
		if ( posKeys[i]->angleRollDeg!=0) 		angleRollDegSetBy	 = KF_CAM;
		if ( posKeys[i]->timeScale	 !=1) 		globalTimeScaleSetBy = KF_CAM;
	}
	for (	i=0; i<targetKeys.GetNumInList(); i++) 
	{
		if ( targetKeys[i]->camFOVScale!=1 ) 	camFOVSetBy				= KF_TARGET;
		if ( targetKeys[i]->angleRollDeg!=0)	angleRollDegSetBy		= KF_TARGET;
		if ( targetKeys[i]->timeScale	!=1) 	globalTimeScaleSetBy	= KF_TARGET;
	}

	AutoSetKeyTimes(posKeys	  );
	AutoSetKeyTimes(targetKeys);

	// spline(s) aus allen Keyframes initialisieren
	zCArray <zCPositionKey*> camKeys;
	zCArray <zCPositionKey*> atKeys;

	// FIXME: zCKBSplines need double position keys at start and end
	if (numCamKeys > 1) 
	{
		zCPositionKey *key = zNEW( zCPositionKey );
		key->SetMat			(posKeys[0]->actPose		);
		key->SetBias		(posKeys[0]->GetBias()		);
		key->SetTension		(posKeys[0]->GetTension()	);
		key->SetContinuity	(posKeys[0]->GetContinuity());
		key->SetTime		(posKeys[0]->GetTime()		);
		camKeys.Insert(key);

		for (i=0; i<posKeys.GetNumInList(); i++) 
		{
			if ( csTime>0 && adaptToSurroundings )			
			if (i>0 && posKeys[i]->GetTime()>actTimeCam && posKeys[i-1]->GetTime()<actTimeCam ) 
			{
				// aktuelle position einfügen (nötig bei dynamischen key anpassungen, damit keine sprünge sichtbar werden)
				zMAT4 trafo;
				zCPositionKey *newkey = zNEW( zCPositionKey );
				if (camKeysFOR == zCAMTRJ_KEY_FOR_WORLD) trafo = trafoCStoWS; 
				else					 				 trafo = camKeysRefVob->trafoObjToWorld.InverseLinTrafo() * trafoCStoWS;
				newkey->SetMat	(trafo);
				newkey->SetTime (actTimeCam);
				camKeys.Insert(newkey);
			}

			zCPositionKey *key = zNEW( zCPositionKey );
			key->SetMat			(posKeys[i]->actPose		);
			key->SetBias		(posKeys[i]->GetBias()		);
			key->SetTension		(posKeys[i]->GetTension()	);
			key->SetContinuity	(posKeys[i]->GetContinuity());
			key->SetTime		(posKeys[i]->GetTime()		);
			camKeys.Insert(key);
		};

		key = zNEW( zCPositionKey );
		key->SetMat			(posKeys[i-1]->actPose			);
		key->SetBias		(posKeys[i-1]->GetBias()		);
		key->SetTension		(posKeys[i-1]->GetTension()		);
		key->SetContinuity	(posKeys[i-1]->GetContinuity()	);
		key->SetTime		(posKeys[i-1]->GetTime()		);
		camKeys.Insert(key);

		posSpl		.Initialize(camKeys);

		// sonder modi checken, und ggfs. darauf reagieren
	}

	if (numTargetKeys > 1) 
	{
		// zCKBSplines need double position keys at start and end, (encapsulation like this into zCKBSpline ?)
		zCPositionKey *key = zNEW( zCPositionKey );
		key->SetMat			(targetKeys[0]->actPose			);
		key->SetBias		(targetKeys[0]->GetBias()		);
		key->SetTension		(targetKeys[0]->GetTension()	);
		key->SetContinuity	(targetKeys[0]->GetContinuity()	);
		key->SetTime		(targetKeys[0]->GetTime		 ()	);
		atKeys.Insert(key);
		
		for (i=0; i<numTargetKeys; i++) {
			zCPositionKey *key = zNEW( zCPositionKey );
			key->SetMat			(targetKeys[i]->actPose			);
			key->SetBias		(targetKeys[i]->GetBias()		);
			key->SetTension		(targetKeys[i]->GetTension()	);
			key->SetContinuity	(targetKeys[i]->GetContinuity()	);
			key->SetTime		(targetKeys[i]->GetTime		 ()	);
			atKeys.Insert(key);
		};

		key = zNEW( zCPositionKey );
		key->SetMat			(targetKeys[i-1]->actPose			);
		key->SetBias		(targetKeys[i-1]->GetBias()			);
		key->SetTension		(targetKeys[i-1]->GetTension()		);
		key->SetContinuity	(targetKeys[i-1]->GetContinuity()	);
		key->SetTime		(targetKeys[i-1]->GetTime()			);
		atKeys.Insert(key);
		targetSpl	.Initialize(atKeys );
	}

	keysPreProcessed    = TRUE;

    camKeys.DeleteList();  
    atKeys.DeleteList();
};


void zCCSCamera :: PostKFProcessing()
{
	keysPreProcessed = FALSE;
	posSpl   .Terminate();
	targetSpl.Terminate();
};


/* ----------------------------------------------------------------------
	
    zCCSCamera::AutoSetKeyTimes	()

	8.09.2000	[Moos]	
                Leakfix 
	13.09.2000  [Edenfeld]	Leakfix entfernt


   ---------------------------------------------------------------------- */

void zCCSCamera :: AutoSetKeyTimes(zCArray<zCCamTrj_KeyFrame*>&keys)
{
	// Abfangen:	- Zeit auf letztem Keyframe ungleich Gesamt Cutscene Zeit: komplett skalieren
	//				- Einer der Keys ungültige Zeit:  anpassen
	//				- Kein Key mit Zeit belegt: Lineare Geschw. durch Berücksichtigen der Abstände zwischen
	//				  den Keys.
	//				- auf ansteigende Zeit prüfen
	//				- zwei aufeinanderfolgende Keys dürfen nicht dieselbe Zeit besitzen, aber um exakte
	//				  easein/out Lerps zu simulieren, kann das passieren
	//				  ->für diesen fall um Interpol. Probs zu vermeiden zeit minimal anpassen ... -> Keine komplette neu Skalierung
	//				  nötig

	const float EPS_COR = 0.0001F;

	if (!GetAutoSetKeyTimesEnabled()) return;

	if (keys.GetNumInList() == 0) return;

	// Sonderbehandlung bei einem Key
	if (keys.GetNumInList() == 1) 
	{
		if (keys[0]->GetTime() != 0) keys[0]->SetTime(0);
		return;
	}
 
	zBOOL wrongUserInput = FALSE;

	for (int i=0; i<keys.GetNumInList(); i++) 
	{
		if (keys[i]->GetTime() == zCS_KEYTIME_UNDEF) 
		{
			wrongUserInput = TRUE;
			break;
		}
		else if (i>0 && keys[i-1]->GetTime()>keys[i]->GetTime()) 
		{
			zERR_WARNING("C: zCCSCamera :: AutoSetKeyTimes: Key Times are not ascending");
			#ifdef COMPILING_SPACER
				zSTRING s("Warning! Times on Keyframes are not ascending and will be corrected!");
				MessageBox(NULL,s.ToChar(), "Error-Message", MB_OK);
			#endif
			wrongUserInput = TRUE;
			break;
		}
	}


	// es sind alle Zeiten belegt. checken ob der letzte Key eine Zeit ungleich der Cutscene Dauer
	// besitzt, und auch schon mal initialisiert wurde, wenn ja, alle Keys entsprechend skalieren
	float lastKeyTime = keys[keys.GetNumInList()-1]->GetTime();

	if ( lastKeyTime != totalTime && !wrongUserInput ) 
	{ 
		float sc = totalTime/keys[keys.GetNumInList()-1]->GetTime();
		for (int i=0; i<keys.GetNumInList(); i++) {
			keys[i]->SetTime( keys[i]->GetTime()*sc );
		}
	}
	else if (lastKeyTime != totalTime && wrongUserInput ) 
	{
		// wird hier abgefangen, indem alle Zeiten an den Keys linear ansteigend gesetzt werden
		for (i=0; i<keys.GetNumInList(); i++) {
			keys[i]->SetTime( zREAL(i)/keys.GetNumInList()*totalTime );
		}
	}
	else 
	{
		// Nö, die Zeiten KF's sind also entweder schon mal berechnet worden, aber da ein KF bewegt worden
		// sein kann, muss für dieses evtl. die Zeit neu berechnet werden

		// temporäre spline für intra distanz ermittlung aufbauen
		zCArray<zCPositionKey*>splKeys; 
		zCKBSpline spl;
		zCPositionKey *key = zNEW( zCPositionKey );
		key->SetMat(keys[0]->actPose);
		key->SetTime((float)0);
		splKeys.Insert(key);

        int i;
		for (i=0; i<keys.GetNumInList(); i++) 
		{
			zCPositionKey *key = zNEW( zCPositionKey );
			key->SetMat(keys[i]->actPose);
			key->SetTime((float)i);
			splKeys.Insert(key);
		};

		key = zNEW( zCPositionKey );
		key->SetMat(keys[keys.GetNumInList()-1]->actPose);
		key->SetTime((float)i-1);
		splKeys.Insert(key);

		spl.Initialize(splKeys);

		if (spl.Length()==0) 
		{
			// sonderfall: alle keys sind auf einem Punkt (User Fehler)
			// wird hier abgefangen, indem alle Zeiten an den Keys linear ansteigend gesetzt werden
			for (i=0; i<keys.GetNumInList(); i++) {
				keys[i]->SetTime( zREAL(i)/keys.GetNumInList()*totalTime );
			}
		}
		else if (lastKeyTime != zCS_KEYTIME_UNDEF) 
		{
			// nun einen linearen zeitverlauf ermitteln
			for (i=0; i<keys.GetNumInList(); i++) {
				if (!keys[i]->GetTimeIsFixed())	{
					// Nur wenn der Keyframe keine Fixed-Zeit hat, wird diese neu berechnet
					keys[i]->SetTime( (spl.Length((zREAL)i)*totalTime)/spl.Length() );
				}
			}
		}
		else 
		{
			for (i=0; i<keys.GetNumInList(); i++) {
				keys[i]->SetTime( (spl.Length((zREAL)i)*totalTime)/spl.Length() );
			}
		}
	}

	// hier wird überprüft, ob zwei Keyframes die gleiche Zeit besitzen,
	// das kamm passieren, weil der User dies manuell wegen Simulation von getrennten EaseIn/Out Lerps
	// gewollt hat, oder weil zwei Keyframes an der gleichen Position sind. Durch minimale Korrektur
	// der Zeiten wird eine Division durch Null in der Spline Klasse vermieden
	for (i=1; i<keys.GetNumInList(); i++) {
		if (keys[i-1]->GetTime()==keys[i]->GetTime()) keys[i]->SetTime(keys[i]->GetTime()+EPS_COR);
	}

};

void zCCSCamera :: Changed()		
{
	PostKFProcessing();
	PreKFProcessing ();
};

/* ----------------------------------------------------------------------
	
    zCCSCamera::Initialize()	

	8.09.2000	[Moos]	
                Leakfix
	13.09.2000  [Edenfeld]	Leakfix entfernt


   ---------------------------------------------------------------------- */

void zCCSCamera :: Initialize()
{

	// Jetzt checken, ob die letzte bekannte Kamera Position mit in die Camerafahrt integriert werden soll.
	// (Kann nur klappen, wenn die Position zum ersten Camera KF auch sichtbar ist)

	if ( started && posKeys.GetNumInList()>0 && zCCamera::activeCam && zCCamera::activeCam->GetVob() ) 
	{
		if (easeToFirstKey) 
		{
			if (GetHomeWorld()) 
			{
				zPOINT3 firstKeyPos = posKeys[0]->GetPositionWorld();
				zMAT4   actCamTrafo = zCCamera::activeCam->GetVob()->trafoObjToWorld;
				zPOINT3 camPos		= zCCamera::activeCam->GetVob()->GetPositionWorld();

				// erst checken, ob der erste KF von der Cameraposition aus gesehen werden kann
				if (!GetHomeWorld()->TraceRayFirstHit(firstKeyPos, (camPos-firstKeyPos),camKeysRefVob,zTRACERAY_STAT_POLY|zTRACERAY_VOB_IGNORE_CHARACTER|zTRACERAY_POLY_IGNORE_TRANSP|zTRACERAY_VOB_IGNORE_NO_CD_DYN)) 
				{
					zCCamTrj_KeyFrame *key = zNEW( zCCamTrj_KeyFrame );
					key->trafoObjToWorld = actCamTrafo;
					key->SetTime		  (0);
					key->SetMotionType			(	zCAMTRJ_KEY_MOTION_SLOW	);
					key->SetMotionTypeFOV		(	zCAMTRJ_KEY_MOTION_SLOW );
					key->SetMotionTypeRoll		(	zCAMTRJ_KEY_MOTION_SLOW );
					key->SetMotionTypeTimeScale	(	zCAMTRJ_KEY_MOTION_SLOW );
					// falls splLerpMode != zTSPL_LERP_PATH_ROT_SAMPLES sollte man den ersten KF
					// mit der entsprechenden Matrix die auf die erste TargetSpline Pos zeigt initialisieren
					if (splLerpMode != zTSPL_LERP_PATH_ROT_SAMPLES) 
					{
						if (targetKeys.GetNumInList()>0) {
							posKeys[0]->trafoObjToWorld = GetPoseOfHeading(firstKeyPos,(targetKeys[0]->GetPositionWorld()-firstKeyPos).Normalize());
							posKeys[0]->Changed();
						} 
						else if (posKeys.GetNumInList()>1)  
						{
							// Spezialfall: Kein Targetkey vorhanden, die Orientierung des ersten Pos Keys
							// muss entlang der Steigung für t=0 ausgerichtet werden
							// Also: Spline aufbauen, und die Trafo für t=0 ermitteln
							

							zCArray<zCPositionKey*>splKeys; 
							zCKBSpline spl;
							zCPositionKey *key = zNEW( zCPositionKey );
							key->SetMat(posKeys[0]->trafoObjToWorld);
							key->SetTime((float)0);
							splKeys.Insert(key);

							for (int i=0; i<posKeys.GetNumInList(); i++) 
							{
								zCPositionKey *key = zNEW( zCPositionKey );
								key->SetMat(posKeys[i]->trafoObjToWorld);
								key->SetTime((float)i);
								splKeys.Insert(key);
							};

							key = zNEW( zCPositionKey );
							key->SetMat(posKeys[posKeys.GetNumInList()-1]->trafoObjToWorld);
							key->SetTime((float)i-1);
							splKeys.Insert(key);
							spl.Initialize(splKeys);

							spl.Interpolate( 0, posKeys[0]->trafoObjToWorld ); 

						}
					}
					// Wir gehen von einer durchschnittlichen Zeit von timeToEaseToFirstKey Sekunden aus, um den 
					// tatsächlichen ersten Keyframe zu erreichen, also erhöhen wir die Zeiten
					// an allen Keyframes um timeToEaseToFirstKey Sekunden
					for (int kf=0; kf<posKeys.GetNumInList(); kf++) 
					{
						posKeys[kf]->SetTime(posKeys[kf]->GetTime()+timeToEaseToFirstKey);
					}

					totalTime += timeToEaseToFirstKey;

					SetAutoSetKeyTimesEnabled(FALSE);
					InsertCamKeyAtPos(key,0);                                      
					SetAutoSetKeyTimesEnabled(TRUE);

					easeToFirstKeyNotPossible = FALSE;

                    zRELEASE(key);
				} 
				else easeToFirstKeyNotPossible = TRUE;
			}
		}
		if (easeFromLastKey) 
		{
			if (GetHomeWorld()) 
			{
				zPOINT3 lastKeyPos  = posKeys[posKeys.GetNumInList()-1]->GetPositionWorld();
				zMAT4   actCamTrafo = zCCamera::activeCam->GetVob()->trafoObjToWorld;
				zPOINT3 camPos		= zCCamera::activeCam->GetVob()->GetPositionWorld();
				if (!GetHomeWorld()->TraceRayFirstHit(lastKeyPos, (camPos-lastKeyPos),camKeysRefVob,zTRACERAY_STAT_POLY|zTRACERAY_VOB_IGNORE_CHARACTER|zTRACERAY_POLY_IGNORE_TRANSP|zTRACERAY_VOB_IGNORE_NO_CD_DYN)) 
				{
					int lastKey = posKeys.GetNumInList()-1;
					zCCamTrj_KeyFrame *key = zNEW( zCCamTrj_KeyFrame );
					key->trafoObjToWorld = actCamTrafo;
					key->SetMotionType			(	zCAMTRJ_KEY_MOTION_SLOW	);
					key->SetMotionTypeFOV		(	zCAMTRJ_KEY_MOTION_SLOW );
					key->SetMotionTypeRoll		(	zCAMTRJ_KEY_MOTION_SLOW );
					key->SetMotionTypeTimeScale	(	zCAMTRJ_KEY_MOTION_SLOW );
					// falls splLerpMode != zTSPL_LERP_PATH_ROT_SAMPLES sollte man den ersten KF
					// mit der entsprechenden Matrix die auf die erste TargetSpline Pos zeigt initialisieren
					if (splLerpMode != zTSPL_LERP_PATH_ROT_SAMPLES) 
					{
						if (targetKeys.GetNumInList()>0) {
							posKeys[lastKey]->trafoObjToWorld = GetPoseOfHeading(lastKeyPos,(targetKeys[targetKeys.GetNumInList()-1]->GetPositionWorld()-lastKeyPos).Normalize());
							posKeys[lastKey]->Changed();
						}
						else if (posKeys.GetNumInList()>1)  
						{
							// Spezialfall: Kein Targetkey vorhanden, die Orientierung des letzten Pos Keys
							// muss entlang der Steigung für t=totalTime ausgerichtet werden
							// Also: Spline aufbauen, und die Trafo für t=totalTime ermitteln

							zCArray<zCPositionKey*>splKeys; 
							zCKBSpline spl;
							zCPositionKey *key = zNEW( zCPositionKey );
							key->SetMat(posKeys[0]->trafoObjToWorld);
							key->SetTime((float)0);
							splKeys.Insert(key);

							for (int i=0; i<posKeys.GetNumInList(); i++) {
								zCPositionKey *key = zNEW( zCPositionKey );
								key->SetMat(posKeys[i]->trafoObjToWorld);
								key->SetTime((float)i);
								splKeys.Insert(key);
							};

							key = zNEW( zCPositionKey );
							key->SetMat(posKeys[posKeys.GetNumInList()-1]->trafoObjToWorld);
							key->SetTime((float)i-1);
							splKeys.Insert(key);
							spl.Initialize(splKeys);

							spl.Interpolate( float(i-1), posKeys[lastKey]->trafoObjToWorld ); 

						}
					}

					// Wir gehen von einer durchschnittlichen Zeit von 2 Sekunden aus, um den 
					// tatsächlichen letzten Keyframe zu erreichen
					key->SetTime(posKeys[posKeys.GetNumInList()-1]->GetTime()+2);
					totalTime += timeToEaseFromLastKey;

					SetAutoSetKeyTimesEnabled(FALSE);
					InsertCamKey(key);
					SetAutoSetKeyTimesEnabled(TRUE);

					easeFromLastKeyNotPossible = FALSE;
				} 
				else easeFromLastKeyNotPossible = TRUE;
			}
		}
	}
					
	for (int i=0; i<posKeys.GetNumInList(); i++) {
		posKeys[i]->originalPose = posKeys[i]->actPose;
	}

	for (	 i=0; i<targetKeys.GetNumInList(); i++) {
		targetKeys[i]->originalPose = targetKeys[i]->actPose;
	}

	initialized = TRUE;
};

void zCCSCamera :: Reset()
{
	for (int i=0; i<posKeys.GetNumInList(); i++) 
	{
		posKeys[i]->actPose = posKeys[i]->originalPose;
		posKeys[i]->SetMotionType(zCAMTRJ_KEY_MOTION_SMOOTH);
	}
	csTime = 0;
	Changed();
};

void  zCCSCamera :: CalcPrevNextActKeyOfTime(const zREAL &time,zCArray <zCCamTrj_KeyFrame*>&keys, int &prev, int &next,int &act)
{
	for (act=0; act<keys.GetNumInList(); act++) 
	{
		// ACHTUNG: compiler BUG, manchmal failed die if Bedingung, obwohl definitiv (keys[act]->GetTime() == totalTime)
		if ( keys[act]->GetTime() > time || keys[act]->GetTime() == totalTime ) {
			act--;
			break;
		} else if (keys[act]->GetTime() == time) break;
	}

	if (act == keys.GetNumInList()) act-=2; // FIXME: das ist nicht nötig (siehe Compiler Bug oben)
	
	// Es kann Situationen geben, in denen hier act < 0 ist, z.B. wenn an einem ersten Key einer Spline
	// ein Wert > 0 angegeben wurde.
	if (act<0) act = 0;

	// find backwards first key which has a lerpmode other than SMOOTH or UNDEF
	for (prev=act; prev>0; prev--) {
		if ( keys[prev]->GetMotionType() != zCAMTRJ_KEY_MOTION_UNDEF &&
			 keys[prev]->GetMotionType() != zCAMTRJ_KEY_MOTION_SMOOTH ) break;
	}

	// find forward last key which has a lerpmode other than SMOOTH or UNDEF
	for (next=act+1; next<keys.GetNumInList()-1; next++) {
		if ( keys[next]->GetMotionType() != zCAMTRJ_KEY_MOTION_UNDEF &&
			 keys[next]->GetMotionType() != zCAMTRJ_KEY_MOTION_SMOOTH ) break;
	}

	assert(prev != next);
};


zBOOL zCCSCamera :: IsPointNearWall(const zPOINT3 &testPos) 
{
	if (GetHomeWorld()->IsCompiled()) 
	{	
		zTBBox3D	camBox; 
		zTBSphere3D camSphere;
		camSphere.center = testPos;
		camSphere.radius = CAMSPHERE_DIAMETER*0.5F;

		camBox.mins = testPos - (zVEC3(1,1,1) * camSphere.radius*1.3F);
		camBox.maxs = testPos + (zVEC3(1,1,1) * camSphere.radius*1.3F);	

		zCPolygon **polyList;
		int	numPolys=0;

		if (GetHomeWorld()->GetBspTree()->GetRoot()->CollectPolysInBBox3D(camBox,polyList,numPolys)) 
		{
			for (int i=0; i<numPolys; i++) 
			{
				if ( polyList[i]->GetMaterial()->GetMatGroup()!=zMAT_GROUP_WATER && 
					 polyList[i]->CheckBSpherePolyIntersection(camSphere) ) {
					return TRUE;
				}
			}
		}
	}
	return FALSE;  
}

zPOINT3 zCCSCamera :: GetPolyNearestPoint (zCPolygon *poly,const zPOINT3 &checkPt) const
{
	// findet den nächsten Punkt auf einem poly zu einem gegebenen Punkt
	
	float alpha; zPOINT3 res;
	float minDist	= FLT_MAX;
	float checkPtDistToWorldOrigin = (checkPt - zPOINT3(0,0,0)).Length();

	// wenn der Fusslotpunkt auf die PolyEbene durch den Checkpunkt läuft, sind wir fertig
	if ( !poly->CheckRayPolyIntersection(checkPt, checkPt - (FLT_MAX * (poly->GetNormal())), res, alpha) ) 
	{

		// nein, also den Abstand zu allen Geraden und (falls nötig) Vertices messen
		zTPlane EOrthG;
		zVEC3   inters,ray,rayOrigin;

		// alle polykanten abgehen 
		for (int i=1; i<poly->polyNumVert; i++) 
		{
			rayOrigin		= poly->vertex[i-1]->position;
			ray				= (poly->vertex[i]->position - rayOrigin);
			// ebene die orthog. zur polykante ist, und durch den checkpt. geht, aufspannen
			EOrthG.normal	= ray.Normalize();
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
			else {
				float dist	= (inters-checkPt).Length2();
				if ( dist < minDist ) 
				{ 
					res		= inters;
					minDist = dist;
				}
			}
		}
		// Dasselbe mit der letzten Polykante
		rayOrigin		= poly->vertex[poly->polyNumVert-1]->position;
		ray				= (poly->vertex[0]->position - rayOrigin);
		EOrthG.normal	= ray.Normalize();
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

zBOOL zCCSCamera :: AdjustCenterSphere(zPOINT3 &center, const zPOINT3 &b, const float radius)
{
	zPOINT3 newCenter;
	
	if ((center-b).Length()==0) return FALSE;
	zVEC3 bToCenter = (center-b).Normalize();
	
	newCenter = center + (radius * bToCenter);

	if (GetHomeWorld()->TraceRayNearestHit(b, (newCenter-b),camKeysRefVob,standardTraceFlags)) 
	{
		if ((GetHomeWorld()->traceRayReport.foundIntersection - b).Length2()>=radius*radius)
		{
			center = GetHomeWorld()->traceRayReport.foundIntersection + (radius * (-bToCenter));
		}
		else
		{
			center = b;
		}
	}
	else return FALSE;

	return TRUE;
	
#if 0	
	// Adjust a spheres range towards a given end position, end position must be valid
	// returns TRUE if a position has been found, false otherwise

	// check if false position
	zPOINT3 polyPoint; 
	zPOINT3 startCenter = center;
	float	radius2		= radius * radius;
	float   minDist		= radius + 1;
	do 
	{
		if (GetHomeWorld()->TraceRayNearestHit(b, (center-b),camKeysRefVob,zTRACERAY_STAT_POLY|zTRACERAY_VOB_IGNORE_CHARACTER|zTRACERAY_POLY_IGNORE_TRANSP|zTRACERAY_VOB_IGNORE_NO_CD_DYN)) {
			polyPoint = GetHomeWorld()->traceRayReport.foundIntersection;
		}
		else 
		{   // 2nd case: cam too near to walls (polys in camsphere)
			// find which poly lies nearest to target
			
			zTBSphere3D camSphere;
			camSphere.center = center;
			camSphere.radius = radius;
			zTBBox3D  camBox; 

			camBox.mins = center - (zVEC3(1,1,1) * radius*1.4F);
			camBox.maxs = center + (zVEC3(1,1,1) * radius*1.4F);	

			zPOINT3   nearestPt;
			zCPolygon**	polyList; 
			zCPolygon *	nearestPoly		= 0;		
			float		lastDistance	= FLT_MAX;
			int			numPolys		= 0;

			GetHomeWorld()->GetBspTree()->GetRoot()->CollectPolysInBBox3D(camBox,polyList,numPolys);
			if (numPolys == 0) break;

			for (int i=0; i<numPolys; i++) 
			{
				if ( polyList[i]->GetMaterial()->GetMatGroup() != zMAT_GROUP_WATER && 
					 polyList[i]->CheckBSpherePolyIntersection(camSphere)          &&
					 polyList[i]->GetPlane().ClassifyPoint(center) == zPLANE_INFRONT ) 
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
		} 

		zVEC3 CMinT  = center - b;
		zVEC3 IMinC  = polyPoint - center;
		float nenner = CMinT * CMinT;
		float pHalve = (CMinT*IMinC)/nenner;
		float q		 = ((IMinC * IMinC)-(minDist*minDist))/nenner;
		float root	 = (float) sqrt( (float)(pHalve*pHalve) - q );
		float s   	 = (- pHalve + root) > 0 ? (- pHalve + root) : (- pHalve - root);
		
		// safety check
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
// ** zCCSCamera_EventMsg *********************************************************************************

// standard constructor
zCCSCamera_EventMsg::zCCSCamera_EventMsg()
{
	subType			= EV_NOTHING;
	time			= 0;
	key				= 0;
	isDeleted		= FALSE;
	kfType			= KF_CAM;
};

zCCSCamera_EventMsg::zCCSCamera_EventMsg(zTCSCam_EvSubType subType) 
{
	this->subType	= subType;
	time			= zCS_KEYTIME_UNDEF;
	key				= 0;
	isDeleted		= FALSE;
	kfType			= KF_CAM;
	if (subType==EV_PLAY || subType == EV_GOTO_KEY) time = zCSCAM_DEFAULT_DURATION;
};

zCCSCamera_EventMsg::~zCCSCamera_EventMsg()
{
};


void zCCSCamera_EventMsg :: Archive			(zCArchiver &arc)
{
	zCEventMessage::Archive(arc);
	switch(subType) 
	{
		case EV_PLAY:			arc.WriteFloat("time",time); break;
		case EV_GOTO_KEY:		
			arc.WriteFloat("time",time); 
			arc.WriteInt  ("key",key); 
			arc.WriteEnum ("kfType","UNDEF;TARGET;CAM",kfType);  
			break;
		case EV_SET_DURATION:	arc.WriteFloat("time",time); break;
		case EV_SET_TO_TIME:	arc.WriteFloat("time",time); break;
	}
};

void zCCSCamera_EventMsg ::	Unarchive		(zCArchiver &arc)
{
	zCEventMessage::Unarchive(arc);
	switch(subType) 
	{
		case EV_PLAY:			arc.ReadFloat("time",time);	break;
		case EV_GOTO_KEY:		
			arc.ReadFloat("time",time);	
			arc.ReadInt  ("key",key);
			kfType = (zTCamTrj_KFType) arc.ReadEnum("kfType");
			break;
		case EV_SET_DURATION:	arc.ReadFloat("time",time);	break;
		case EV_SET_TO_TIME:	arc.ReadFloat("time",time);	break;
	}
};

int	zCCSCamera_EventMsg ::	MD_GetNumOfSubTypes	()
{
	return 9;
}
zSTRING	zCCSCamera_EventMsg ::	MD_GetSubTypeString	(int n)
{
	switch (n) {
		case EV_NOTHING:		return zSTRING("EV_CAM_NOTHING");  
		case EV_PLAY:			return zSTRING("EV_CAM_PLAY");  
		case EV_PAUSE:			return zSTRING("EV_CAM_PAUSE");  
		case EV_RESUME:			return zSTRING("EV_CAM_RESUME");  
		case EV_STOP:			return zSTRING("EV_CAM_STOP");  
		case EV_GOTO_KEY:		return zSTRING("EV_CAM_GOTO_KEY");  
		case EV_SET_DURATION:	return zSTRING("EV_CAM_SET_DURATION");  
		case EV_SET_TO_TIME:	return zSTRING("EV_CAM_SET_TO_TIME");  
		default	:				return zSTRING();
	}
};

zREAL	zCCSCamera_EventMsg ::	MD_GetMinTime		()								
{ 
	if (subType == EV_PLAY)		 return time; else
	if (subType == EV_GOTO_KEY)  return time;				
	else return 0;		
};

// ** zCCSCamera_EventMsgActivate *********************************************************************************

void zCCSCamera_EventMsgActivate :: Archive			(zCArchiver &arc)
{
	zCEventMessage::Archive(arc);
	arc.WriteString("refVobName",referenceName);
};

void zCCSCamera_EventMsgActivate ::	Unarchive		(zCArchiver &arc)
{
	zCEventMessage::Unarchive(arc);
	referenceName = arc.ReadString("refVobName");
};

int	zCCSCamera_EventMsgActivate ::	MD_GetNumOfSubTypes	()
{
	return 3;
}

zSTRING	zCCSCamera_EventMsgActivate ::	MD_GetSubTypeString	(int n)
{
	switch (n) {
		case EV_DEACTIVATE:				return zSTRING("EV_CAM_DEACTIVATE"); 
		case EV_SETCAMREFERENCE:		return zSTRING("EV_CAM_SETPOSREFERENCE");
		case EV_SETTARGETREFERENCE:		return zSTRING("EV_CAM_SETTARGETREFERENCE");
		default	:						return zSTRING();
	}
}

zSTRING	zCCSCamera_EventMsgActivate :: MD_GetVobRefName	()
{
	return referenceName;
}

void	zCCSCamera_EventMsgActivate :: MD_SetVobRefName	(const zSTRING & name)
{
	referenceName = name;
}

void	zCCSCamera_EventMsgActivate :: MD_SetVobParam		(zCVob* vob)
{
	referenceVob = vob;
}

void  zCCSCamera::SetDrawEnabled	(const zBOOL b )
{
	draw = b;
};



zCLASS_DEFINITION(zCCSCamera_EventMsg,			zCEventMessage,0,	6)
zCLASS_DEFINITION(zCCSCamera_EventMsgActivate,	zCEventMessage,0,	6)
zCLASS_DEFINITION(zCCSCamera,					zCVob,		  ,0,   8)
zCLASS_DEFINITION(zCCamTrj_KeyFrame,			zCVob,		  ,0,	7)

