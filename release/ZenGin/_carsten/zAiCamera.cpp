/******************************************************************************** 
 
     $Workfile:: zAICamera.cpp       $                 $Date:: 12.04.01 17:28      $
     $Revision:: 81               $						$Modtime:: 11.04.01 18:05   $
       $Author:: Edenfeld                                                       $
    Subproject:: ZenGin
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   Created:

 * $Log: /current_work/zengin/_Carsten/zAICamera.cpp $
 * 
 * 81    12.04.01 17:28 Edenfeld
 * Patch 2 (1.08): Falsches FOV nach anlabern Bugfix
 * 
 * 80    17.03.01 23:13 Edenfeld
 * Fix Dialogcamera und unsichtbarer SC wenn kurz vorher First Person
 * Kamera aktiv
 * 
 * 79    16.02.01 8:54 Edenfeld
 * 
 * 78    16.02.01 3:32 Edenfeld
 * DialogCamera Schwenk Fix
 * 
 * 77    16.02.01 2:20 Edenfeld
 * CamModRun -> CamModNormal smoother
 * 
 * 76    14.02.01 22:37 Edenfeld
 * LookBack Fix
 * 
 * 75    14.02.01 13:57 Moos
 * RingBuffer auf Relaxen umgestellt
 * 
 * 74    14.02.01 4:13 Edenfeld
 * LookBack Cam
 * 
 * 73    13.02.01 21:12 Edenfeld
 * Unterwasser Kamera Maus y Achse vertauscht
 * 
 * 72    13.02.01 1:01 Edenfeld
 * 
 * 71    11.02.01 18:23 Edenfeld
 * 
 * 70    7.02.01 12:53 Moos
 * 
 * 69    6.02.01 19:16 Edenfeld
 * 
 * 68    6.02.01 4:20 Speckels
 * 
 * 67    6.02.01 4:24 Edenfeld
 * 
 * 66    6.02.01 2:20 Edenfeld
 * 
 * 65    6.02.01 2:05 Edenfeld
 * 
 * 64    6.02.01 1:52 Edenfeld
 * 
 * 63    6.02.01 1:50 Edenfeld
 * 
 * 62    6.02.01 0:51 Edenfeld
 * 
 * 61    6.02.01 0:47 Edenfeld
 * 
 * 60    6.02.01 0:46 Edenfeld
 * 
 * 59    31.01.01 0:47 Speckels
 * 
 * 57    31.01.01 0:29 Speckels
 * 
 * 56    30.01.01 20:34 Edenfeld
 * 
 * 55    29.01.01 20:33 Edenfeld
 * 
 * 54    29.01.01 16:18 Edenfeld
 * 
 * 21    25.01.01 22:48 Admin
 * 
 * 53    25.01.01 20:42 Edenfeld
 * 
 * 52    25.01.01 15:48 Edenfeld
 * 
 * 51    23.01.01 22:13 Edenfeld
 * 
 * 50    23.01.01 22:12 Edenfeld
 * 
 * 49    22.01.01 22:41 Edenfeld
 * 
 * 47    17.01.01 23:35 Edenfeld
 * 
 * 46    16.01.01 17:27 Edenfeld
 * 
 * 45    16.01.01 17:01 Edenfeld
 * 
 * 44    16.01.01 16:05 Edenfeld
 * 
 * 43    12.01.01 21:00 Edenfeld
 * 
 * 42    12.01.01 18:20 Edenfeld
 * 
 * 41    12.01.01 16:53 Edenfeld
 * 
 * 7     12.10.00 16:17 Moos
 * 
 * 6     23.09.00 14:26 Simon
 * 
 * 5     22.09.00 20:10 Simon
 * 
 * 4     5.09.00 19:19 Simon
 * 
 * 3     29.08.00 14:45 Edenfeld
 * 
 * 1     29.08.0 13:05 Simon
 * ZenGin v0.92
 * 
 *********************************************************************************/

// DOC++
/// @author $Author: Edenfeld $
/// @version $Revision: 81 $ ($Modtime: 11.04.01 18:05 $)


#include "zcore.h"
#include "zParser.h"
#include "zDbgTools.h"
#include "zModel.h"
#include "zConsole.h"
#include "zCSCamera.h"
#include "zvob.h"
#include "zworld.h"
#include "zalgebra.h"
#include "zoption.h" 
#include "zAICamera.h"
#include "zAICamera_Movement.h"
#include "zAICamera_Core.h"
#include "zmenu.h"
#include "zinput.h"
 
#include "zAccount.h"

#define CS_VERSION ("v0.5")

zSTRING CamModNormal	("CAMMODNORMAL");
zSTRING CamModRun		("CAMMODRUN");
zSTRING CamModDialog	("CAMMODDIALOG");
zSTRING CamModInventory	("CAMMODINVENTORY");
zSTRING CamModMelee		("CAMMODMELEE");
zSTRING CamModMagic		("CAMMODMAGIC");
zSTRING CamModMeleeMult	("CAMMODMELEEMULT");
zSTRING CamModRanged	("CAMMODRANGED");
zSTRING CamModSwim		("CAMMODSWIM");
zSTRING CamModDive		("CAMMODDIVE");
zSTRING CamModJump		("CAMMODJUMP");
zSTRING CamModJumpUp	("CAMMODJUMPUP");
zSTRING CamModClimb		("CAMMODCLIMB");
zSTRING CamModDeath		("CAMMODDEATH");
zSTRING CamModLook		("CAMMODLOOK");
zSTRING CamModLookBack	("CAMMODLOOKBACK");
zSTRING CamModFocus		("CAMMODFOCUS");
zSTRING CamModRangedShrt("CAMMODRANGEDSHORT");
zSTRING CamModShoulder	("CAMMODSHOULDER");
zSTRING CamModFirstPerson("CAMMODFIRSTPERSON");
zSTRING CamModThrow		("CAMMODTHROW");
zSTRING CamModMobLadder ("CAMMODMOBLADDER");
zSTRING CamModFall		("CAMMODFALL");


// *********************************************************************************
// **							statische zCAICamera Klassen Definitionen
// *********************************************************************************

const float		HUMAN_NORMAL_MAX_EXTENT	= 100.0F;			// 15cm


zCAICamera*				zCAICamera	::	current				= NULL;
zBOOL					zCAICamera	::	bCreated			= FALSE;
zBOOL					zCAICamera	::	bCamChanges			= TRUE;
zCArray<zCCSCamera*>	zCAICamera	::	dialogCamList;
zREAL					zCAICamera	::	lookingCamLastAzi			= 0;
zBOOL					zCAICamera	::	lookingCamAziGoalReached	= FALSE;



// *********************************************************************************
// **							static global variables
// *********************************************************************************

static zCParser *	camParser		= 0;
static zCConsole*	camCon			= 0;
static zBOOL		firstTime		= TRUE;
static zBOOL		bMouseUsed		= FALSE;


int standardTraceFlags		= zTRACERAY_VOB_IGNORE_CHARACTER | zTRACERAY_POLY_IGNORE_TRANSP | zTRACERAY_VOB_IGNORE_NO_CD_DYN;

// *********************************************************************************
// **							static global funcs
// *********************************************************************************

static void  CamConsole_ParameterChanged(const zSTRING &s)
{
	zCAICamera::GetCurrent()->ParameterChanged();  // fixme: use direct aicam method
}

static zBOOL CamConsole_EvalFunc (const zSTRING &s, zSTRING &msg)
{
	return zCAICamera::GetCurrent()->Console_EvalFunc(s,msg);
}

static zBOOL ArraysEqual(zCArray<zCVob*>&a1, zCArray<zCVob*>&a2)
{
	if (a1.GetNumInList()!=a2.GetNumInList()) return FALSE;
	for (int i=0; i<a1.GetNumInList(); i++) if (a1[i]!=a2[i]) return FALSE;
	return TRUE;
}

// *********************************************************************************
// **							zCAICamera implementations
// *********************************************************************************

zCAICamera*	zCAICamera :: GetCurrent			()
{
	return current;
};

// Constructor
zCAICamera :: zCAICamera	()					  
	/*: 
	moveTracker	(zCMovementTracker::GetTracker()), 
	pathSearch	(zCPathSearch	  ::GetSearch ())*/
{
	memset(&bestRange,0,(int)&curcammode-(int)&bestRange);
	
	bestRange				= 2;
	oldCamSys				= CamModNormal;
							
	target					= 0;
	targetAlpha				= 1.0f;
	camVob					= 0; 
	numTargets				= 0;
							
	showPath				= FALSE;
	d_showDots				= FALSE;

	pathDetectCollision		= TRUE;

	focusVob				= 0;
	underWater				= FALSE;
	inCutsceneMode			= FALSE;
	sysChanged				= TRUE;
	raysCasted				= 0;
	rotate					= TRUE;
	translate				= TRUE;
	collision				= TRUE;	
	firstPerson				= FALSE;
	playerIsMovable			= TRUE;
	followIdealPos			= TRUE;
	npcVolumeRangeOffset	= 0;
	camDistOffset			= 0;
	camSysFirstPos			= zVEC3(0,0,0);
	bCamChanges				= TRUE;
	targetInPortalRoom		= FALSE;

	for (int i=0; i<MAX_CTRL_VOBS; i++)		 ctrlDot[i] = 0; 

	InitDialogCam();
	
	moveTracker			= zCMovementTracker::GetTracker();
	pathSearch			= zCPathSearch::GetSearch();
	evasionSearchReport = zCPathSearch::GetReport();

	pathSearch		->	SetAICamera		(this);
	moveTracker		->	SetAICamera		(this);
	moveTracker		->	TargetChanged	();
	pathSearch		->	TargetChanged	();
	moveTracker		->	CamVobChanged	();
	pathSearch		->	CamVobChanged	();

};

/* ----------------------------------------------------------------------
    
    ~zCAICamera()
	

	26.08.2000	[Moos]	
                CleanUp() hinzugefügt. Hoffentlich war das eine
                gute Idee... Immerhin fixt es ein paar leaks.

    06.09.2000  [Moos]
                In CleanUp() aufgeräumt, also gehört das wohl hierher.
                Zurücksetzen von current hinzugefügt.

   ---------------------------------------------------------------------- */

zCAICamera ::~zCAICamera()
{
    CleanUp			(); // [Moos]
	ClearTargetList	();

	zRELEASE_ACCT(camVob);			
	zRELEASE_ACCT(target);
	
	pathSearch		= 0;
	moveTracker     = 0;

	bCreated = FALSE;
    current  = NULL;  // [Moos] ungültigen Pointer löschen
};

zCAICamera* zCAICamera::Create()
{
	if (!bCreated)
	{
		current	 = zNEW(zCAICamera);
		bCreated = TRUE;		
	};

	return current;
};

void zCAICamera :: StartUp()
{	
	zerr.Message(zSTRING("C: *** camera system ") + zSTRING(CS_VERSION) + zSTRING("...") );
	
	if (!camParser) 
	{
		camParser = zNEW( zCParser );
		zoptions->ChangeDir(DIR_SCRIPTS);

		// [BENDLIN] AddonMOD
		zSTRING filename = "";
		if (zgameoptions)
			filename = zgameoptions->ReadString(zOPT_SEC_FILES, "Camera");
		if (filename.IsEmpty())
			filename = "System\\Camera";
		zERR_MESSAGE(4, 0, "N: CAM: Loading file " + filename + ".src or .dat");

		camParser->Parse			(filename + ".src");
		camParser->CreatePCode		();
		camParser->CheckClassSize	(zSTRING("CCAMSYS"),int(&endOfDScript)-int(&bestRange));

		StartupDialogCam();
	}
	else return;		// brauch nicht nochmal zu initialisiert zu werden

	zcon.Register( "EDIT CAMERA"	,		"Camerainstanz editieren " );
	zcon.Register( "TOGGLE NOCLIP"	,		"Toggles collision of camera with world ");
	zcon.Register( "TOGGLE CAMDEBUG",		"Toggles camera debug");
	zcon.Register( "TOGGLE INERTIATARGET",	"Toggles averaging of target position (for camera)");

	zcon.AddEvalFunc( CamConsole_EvalFunc );
	focusVob = zNEW( zCVob );
	focusVob->SetDontWriteIntoArchive(TRUE);
	firstTime = FALSE;
}


/* ----------------------------------------------------------------------
	
    zCAICamera::CleanUp()	

	26.08.2000	[Moos]	
                löscht jetzt auch die KeyFrames

    06.09.2000  [Moos]
                Alles, was globale Variablen betrifft, nach GlobalCleanUp() geschaufelt



   ---------------------------------------------------------------------- */

void zCAICamera :: CleanUp()
{
	zRELEASE_ACCT(focusVob);
};

/* ----------------------------------------------------------------------
	
    zCAICamera::GlobalStartUp()	

	6.09.2000	[Moos]	
                Leer erzeugt, um potentielle Leakfixes richtig zu machen.

   ---------------------------------------------------------------------- */

void zCAICamera::GlobalStartUp				()
{
}

/* ----------------------------------------------------------------------
	
    zCAICamera::GlobalCleanUp()	

	6.09.2000	[Moos]	
                Erzeugt, um Leakfixes richtig zu machen. Code war 
                vorher im normalen CleanUp(), machte da aber Probleme.

   ---------------------------------------------------------------------- */

void zCAICamera::GlobalCleanUp				()
{
    if (current) zADDREF_ACCT(current);
    zRELEASE_ACCT(current);

	delete camParser;
	camParser = 0;

	GlobalDialogCamCleanUp();
}

zREAL zCAICamera::GetBestRange()
{
	static zREAL s_bestRange = 0;
	if (GetHintTargetInPortalRoom()) s_bestRange = bestRange + npcVolumeRangeOffset + MIN(1.5f,camDistOffset);
	else							 s_bestRange = bestRange + npcVolumeRangeOffset + camDistOffset;
	zClamp(s_bestRange,GetMinRange(),GetMaxRange());		// FIXME: innerloop. besser diesen wert cachen
	return s_bestRange;
};

zREAL zCAICamera::GetMinRange()
{
	return  minRange + npcVolumeRangeOffset; //(minRange + npcVolumeRangeOffset + camDistOffset);
};

zREAL zCAICamera::GetMaxRange()
{
	return  maxRange + npcVolumeRangeOffset;
};


void zCAICamera :: SetMode(zSTRING &m, const zCArray <zCVob *> targetList)
{
	if (m==CamModDialog && targetList.GetNum()==0)
	{
		zERR_WARNING("C: zCAICamera :: SetMode(): tried to change to the dialog cam without given targets!");
		return;
	}

	SetTargetList(targetList);

	if (m==GetMode())								return;

	zSTRING realCamMode = m;

	if (zCAICamera::GetModeChangeEnabled())
	{
		if (GetMode()!=realCamMode) 
		{
			SetByScript	 (realCamMode);
			zERR_MESSAGE(6,0,zSTRING("C: < Switched Cam -  ") + realCamMode + zSTRING(" >\n"));
		}
	}
}

zSTRING zCAICamera :: GetMode()
{
	return curcammode;
}

zBOOL zCAICamera :: IsModeActive(zSTRING &m)
{
	return (curcammode==m);
}

zBOOL zCAICamera ::	IsModeAvailable	(const zSTRING &mode)
{
    return (camParser->GetIndex(mode)>=0);
}

void zCAICamera::ReceiveMsg(const zTAICamMsg &msg)
{
	// im Moment noch zum Movement Tracker durchgeschliffen. Später ist gewünscht
	// keine externen Movement Messages senden zu müssen (zCMovementTracker soll zentraler Verwalter
	// für Bewegungen des Targets sein)
	
	// Durchgeschliffen werden derzeit:
	// a) zPLAYER_BEAMED (Hinweis, das Spieler neu eingefügt wurde, oder sich teleportiert hat)
	// b) zPLAYER_MOVED_BACKWARD: Steht der Spieler mit dem Rücken zur Wand, und drückt die CRSR-DOWN Tasten
	// so soll in jedem Fall die Backward AI genommen werden, unabhängig von der Bewegung

	if (msg == zPLAYER_BEAMED ||
		msg == zPLAYER_MOVED_BACKWARD)
	{
		moveTracker->ReceiveMsg(msg);
	}

}

void zCAICamera :: 	SetVob (zCVob *newCamera)
{
	zERR_ASSERT_STRICT(newCamera);

	zRELEASE_ACCT(camVob);
	camVob			  = newCamera;
	zADDREF_ACCT(camVob);

	zERR_MESSAGE(6,0,"C: zCAICamera :: SetVob(). VobName:" + newCamera->GetObjectName());

	pathSearch ->CamVobChanged();
	moveTracker->CamVobChanged();

	CalcFirstPosition();
}

void zCAICamera :: SetTarget(zCVob* t) 
{ 
	zERR_ASSERTT_STRICT(t,"C: zAICamera (zCAICamera :: SetTarget) : No target specified");

	if (t) zERR_MESSAGE(6,0,"C: zCAICamera :: SetTarget(). VobName:" + t->GetObjectName());

	// No last target -> no last focus
	zRELEASE_ACCT(target);
	target					= t; 	
	zADDREF_ACCT(target);
	targetAlpha				= 1.0f;

	npcVolumeRangeOffset	= 0;

	zCModel *targetModel = dynamic_cast<zCModel*>(target->GetVisual());

	if (targetModel)
	{
		const zTBBox3D	bbox					= targetModel->GetBBox3DLocalFixed();
		// passe die range an die maximalen extends des neuen npcs an
		const float		EPS_RESCALE_RANGES		= 10.0F;				// 10cm
		float maxExtend							= 0;
		for (int i=0; i<3; i++)	if (zAbs(bbox.maxs[i])>maxExtend) maxExtend = zAbs(bbox.maxs[i]);
		for (	 i=0; i<3; i++)	if (zAbs(bbox.mins[i])>maxExtend) maxExtend = zAbs(bbox.mins[i]);
		zERR_ASSERT(maxExtend>0);
		if (zAbs(maxExtend-HUMAN_NORMAL_MAX_EXTENT)>EPS_RESCALE_RANGES)	
		{
			npcVolumeRangeOffset	= (maxExtend-HUMAN_NORMAL_MAX_EXTENT)*0.01F *0.8F;
			zERR_MESSAGE(8,0,"C: zCAICamera :: SetTarget(): Max Extent differs from human Max extend, reset to: " + zSTRING(npcVolumeRangeOffset));
		}
	}

	moveTracker->TargetChanged();
	pathSearch ->TargetChanged();

	CalcFirstPosition();
};

void zCAICamera::SetTargetList	(zCArray <zCVob *> newList)
{
	if (GetMode() == CamModFocus ) return; 

	lastNumDialogCamTakes = numDialogCamTakes;

	zBOOL targetChanged = FALSE;
	
	if (!ArraysEqual(targetVobList,newList))
	{
		targetChanged = TRUE;
		numOUsSpoken  = 0;
	} 
	else numOUsSpoken ++;

	if ( GetMode() == CamModDialog && newList.GetNum()>=2 && ( targetChanged || (/*numDialogCamTakes >=2 &&*/ numOUsSpoken>1) ))
	{
		ClearTargetList();
		targetVobList = newList;
		for (int i=0; i<targetVobList.GetNum(); i++) zADDREF_ACCT(targetVobList[i]);
		numTargets = targetVobList.GetNumInList();
		StartDialogCam(FALSE);
		return;
	}

	ClearTargetList();
	targetVobList = newList;
	for (int i=0; i<targetVobList.GetNum(); i++) zADDREF_ACCT(targetVobList[i]);

	numTargets = targetVobList.GetNumInList();
}


void zCAICamera::ClearTargetList()
{
	if (numTargets == 0) return;
	for (int i=0; i<targetVobList.GetNum(); i++) zRELEASE_ACCT(targetVobList[i]);
	targetVobList.DeleteList();
	numTargets = 0;
}

void zCAICamera::AddTarget		(zCVob *newTarget)
{
	if ( newTarget == target ) return;
	
	if (!targetVobList.IsInList(newTarget)) 
	{
		targetVobList.Insert(newTarget);
		zADDREF_ACCT(newTarget);
		numTargets++;
	}

}

void zCAICamera::SubTarget		(zCVob *trgt)
{
	if (targetVobList.IsInList(trgt)) 
	{
		targetVobList.Remove(trgt);
		zRELEASE_ACCT_NONULL(trgt);
		--numTargets; 
	}
	zERR_ASSERT(numTargets >= 0);
}

zBOOL zCAICamera::Console_EvalFunc (const zSTRING &in, zSTRING &msg)
{
	zSTRING s = in;
	s.Upper();

	if ( s.PickWord(1, " ") == "EDIT" ) 
	{
		if ( s.PickWord(2, " ") == "CAMERA" ) 
		{
			zcon.Hide();
			
			if (camCon) delete camCon;
			camCon = zNEW( zCConsole() );
			camCon -> SetPos		(0,0);
			camCon -> SetParser		(camParser);
			camCon -> SetChangedFunc(CamConsole_ParameterChanged);  
			camCon -> EditInstance	(curcammode, &bestRange);
			camCon -> SetFocus		();

			return TRUE;
		} 
	}
	else if ( s.PickWord(1, " ") == "TOGGLE" ) 
	{
		if ( s.PickWord(2, " ") == "NOCLIP" ) 
		{
			pathSearch->SetCollisionEnabled(!pathSearch->GetCollisionEnabled());

			if (pathSearch->GetCollisionEnabled())	msg = "Camera collision enabled";
			else									msg = "Camera collision disabled";
			
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "CAMDEBUG" ) 
		{
			d_showDots=!d_showDots;
			showDebug =!showDebug;
			if (d_showDots) 
			{
				InitHelperVobs();
				if (target) 
				{
					target->SetVisualAlphaEnabled(TRUE);
					target->SetVisualAlpha(0.1F);
				}
				msg = "visualizing camera control dots enabled";
			}
			else 
			{
				D_ClrWin();
				DeleteHelperVobs();
				if (target) 
				{
					target->SetVisualAlphaEnabled(FALSE);
					target->SetVisualAlpha(1);
				}

				msg = "visualizing camera control dots disabled";
			}
			return TRUE;
		} 
		else if ( s.PickWord(2, " ") == "INERTIATARGET" ) 
		{
			if (moveTracker->numPreSamplesPlayerPos==1) 
			{
				moveTracker->numPreSamplesPlayerPos		= 10; 
///				moveTracker->ringPosPreSamplesPlayerPos	= 0;
				moveTracker->SetPlayerPos(moveTracker->GetPlayerPos());
				msg = "target trägheit an";
			}
			else 
			{
				moveTracker->numPreSamplesPlayerPos		= 1; 
//				moveTracker->ringPosPreSamplesPlayerPos	= 0;
				moveTracker->SetPlayerPos(moveTracker->GetPlayerPos());
				msg = "target trägheit aus";
			}

			return TRUE;
		} 
	}

	return FALSE;
}

void zCAICamera :: ParameterChanged()
{
	moveTracker->RecalcRingPositions();
	CalcFirstPosition();
	firstPerson = FALSE;
}

void zCAICamera::CalcFirstPosition()
{
	camSysFirstPos = moveTracker->GetPlayerPos() - (moveTracker->GetPlayerAtVector());
	camSysFirstPos = moveTracker->ApplyRangeToPoint( GetBestRange()*100, camSysFirstPos);
	camSysFirstPos = moveTracker->ApplyAziToPoint  ( bestRotY,  camSysFirstPos);
	camSysFirstPos = moveTracker->ApplyElevToPoint ( bestRotX,  camSysFirstPos);
};


zBOOL zCAICamera :: SetByScript(zSTRING & instance)
{
	if (firstTime) StartUp();
	
	instance.Upper();
	if (curcammode == CamModThrow)
	{
		if (zinput->KeyPressed(KEY_PAD_INS)) return TRUE;
	}

	if (!IsModeAvailable(instance)) 
	{
		zERR_WARNING("C: zAICamera : (zCAICamera :: SetByScript): Camera instance not found : " + instance);
		return FALSE;
	}

	// FIXME: folgendes Fragment sorgt für ein sauberen Switch zur in Game AI 
	// nach der Dialogcamera. Schön ist das aber nicht. Sollte besser auch
	// die Möglichkeit geben "easeToFirstKey" zu berücksichtigen... hihi
	if ( (GetMode()==CamModDialog) && (instance!=CamModDialog) )
	{
		moveTracker->ReceiveMsg(zPLAYER_BEAMED);
	}

	zBOOL noUpdateRotX = FALSE;
	zREAL oldBestRotX  = 0;
	if (bMouseUsed)
	{
		if		(GetMode() == CamModNormal && (instance==CamModRun)	  ) noUpdateRotX = TRUE;
		else if (GetMode() == CamModRun    && (instance==CamModNormal) ) noUpdateRotX = TRUE;
		else if (GetMode() == CamModNormal && (instance==CamModMelee)  ) noUpdateRotX = TRUE;
		else if (GetMode() == CamModRun    && (instance==CamModMelee)  ) noUpdateRotX = TRUE;
		else if (GetMode() == CamModMelee  && (instance==CamModRun)    ) noUpdateRotX = TRUE;
		else if (GetMode() == CamModMelee  && (instance==CamModNormal) ) noUpdateRotX = TRUE;
	}

	if (noUpdateRotX) oldBestRotX = bestRotX;

	camParser->CreateInstance(instance,&bestRange); 

	if (noUpdateRotX) bestRotX    =  oldBestRotX;

	oldCamSys  = curcammode;

	curcammode = instance;

	if (GetMode() == CamModLook) moveTracker->inertiaTrans = 0; else moveTracker->inertiaTrans = 0.1F;

	moveTracker->SetHintMouseUsed(FALSE);

//	inertiaHead			= 0.05F;
//	inertiaRotTargetFOR	= 0;
//	inertiaTargetTrans	= 0.2F;
//	inertiaTargetRot	= 0;

	// We need a target & cam sys values to obtain ideal rotation relative to target

	if (!noUpdateRotX) this->ParameterChanged();

	lookingCamLastAzi		=0;
	lookingCamAziGoalReached=FALSE;

	// evtl. alte dialog Camera aus der Welt entfernen, und neue
	// einsetzen

	ReleaseLastDialogCam();

	if (instance == CamModDialog) 
	{
		StartDialogCam();
		return TRUE;
	}

	numDialogCamTakes	= 0;
	firstSpeakerWasPC	= FALSE;
	sysChanged			= TRUE;

	return TRUE;
}


zSTRING zCAICamera :: SetByScriptLine(zSTRING & command)
{

	if (command.IsEmpty()) return zSTRING("");

	zSTRING arg = command.PickWord (3,"=","");
	command.Upper();

	if		(command.Search ("MINRANGE"		)!=-1)		minRange		= arg.ToFloat();
	else if (command.Search ("MAXRANGE"		)!=-1)		maxRange		= arg.ToFloat();
	else if (command.Search ("BESTRANGE"	)!=-1)		bestRange		= arg.ToFloat();
	else if (command.Search ("MINAZIMUTH"	)!=-1)		minRotY			= arg.ToFloat();
	else if (command.Search ("MAXAZIMUTH"	)!=-1)		maxRotY			= arg.ToFloat();
	else if (command.Search ("BESTAZIMUTH"	)!=-1)		bestRotY		= arg.ToFloat();
	else if (command.Search ("MINELEVATION"	)!=-1)		minRotX			= arg.ToFloat();
	else if (command.Search ("MAXELEVATION"	)!=-1)		maxRotX			= arg.ToFloat();
	else if (command.Search ("BESTELEVATION")!=-1)		bestRotX		= arg.ToFloat();
	else if (command.Search ("MINROTZ"		)!=-1)		minRotZ			= arg.ToFloat();
	else if (command.Search ("MAXROTZ"		)!=-1)		maxRotZ			= arg.ToFloat();
	else if (command.Search ("BESTROTZ"		)!=-1)		bestRotZ		= arg.ToFloat();
	else if (command.Search ("ROTOFFSETX"	)!=-1)		rotOffsetX		= arg.ToFloat();
	else if (command.Search ("ROTOFFSETY"	)!=-1)		rotOffsetY		= arg.ToFloat();
	else if (command.Search ("ROTOFFSETZ"	)!=-1)		rotOffsetZ		= arg.ToFloat();
	else if (command.Search ("VELOTRANS"	)!=-1)		veloTrans		= arg.ToFloat();
	else if (command.Search ("VELOROT"	)	 !=-1)		veloRot			= arg.ToFloat();
	else if (command.Search ("TRANSLATE"	)!=-1)		translate		= (zBOOL) arg.ToInt();
	else if (command.Search ("ROTATE"	)	!=-1 )		rotate			= (zBOOL) arg.ToInt();
	else if (command.Search ("COLLISION"	)!=-1)		collision		= (zBOOL) arg.ToInt();
	else if (command.Search ("INERTIAHEAD"	)!=-1)		moveTracker->inertiaHead		= arg.ToFloat();
	else if (command.Search ("INERTIATRANS"	)!=-1)		moveTracker->inertiaTrans	= arg.ToFloat();
	else if (command.Search ("INERTIATARGETROT"	)!=-1)	moveTracker->inertiaTargetRot= arg.ToFloat();
	else if (command.Search ("NOCLIP"	)!=-1) 
	{ 
		pathSearch->SetCollisionEnabled(!pathSearch->GetCollisionEnabled());
		return zSTRING("Collision: ")+zSTRING(pathSearch->GetCollisionEnabled()) ; 
	} // TEMP
	else return zSTRING("C: zCAICamera (zCAICamera::SetByScriptLine): Unkown command: "+command);

	this->ParameterChanged();

	return zSTRING("\nCommand executed!");

}


void zCAICamera :: CreateInstance(zSTRING &instance)
{
	camParser->CreateInstance(instance,&bestRange);
}


short int zCAICamera::s_iLookAroundSgn=+1;

void zCAICamera::AI_LookingCam()
{	
	const float LOOKINGCAM_MIN_ELEV			= -80.0F;
	const float LOOKINGCAM_MAX_ELEV			= +89.0F;
	const float LOOKINGCAM_MIN_AZI			= -90.0F;
	const float LOOKINGCAM_MAX_AZI			= +90.0F;

	const float ELEV_VELO = 200;
	const float RANGE_VELO= 900;
	const float AZI_VELO  = 200;

	float frameTime = moveTracker->GetFrameTime();

	if		(zinput->GetState(GAME_DOWN)) 											bestRotX = bestRotX + s_iLookAroundSgn * (frameTime * ELEV_VELO); 
	else if	(zinput->GetState(GAME_UP)) 											bestRotX = bestRotX - s_iLookAroundSgn * (frameTime * ELEV_VELO); 	
	if		(zinput->GetState(GAME_LEFT) || zinput->GetState(GAME_STRAFELEFT))		bestRotY = bestRotY + (frameTime * AZI_VELO ); 
	else if (zinput->GetState(GAME_RIGHT)|| zinput->GetState(GAME_STRAFERIGHT))		bestRotY = bestRotY - (frameTime * AZI_VELO );
	
	zClamp( bestRotX, LOOKINGCAM_MIN_ELEV, LOOKINGCAM_MAX_ELEV );
	zClamp( bestRotY, LOOKINGCAM_MIN_AZI , LOOKINGCAM_MAX_AZI  );
	
	zMAT4	playerTrafo = moveTracker->GetPlayerTrafo();
	zPOINT3 aiTry		= moveTracker->GetPlayerHead ();

	if ( !firstPerson && !zinput->GetState(GAME_LOOK_FP) )
	{
		float focusAtScale= 1;

		const float MAX_AT_OFFSET=100;

		focusAtScale				   = (bestRotX/90)*MAX_AT_OFFSET;
		if (focusAtScale>=0)
		{
			if (focusOffsetZ < focusAtScale) focusOffsetZ = focusOffsetZ + (frameTime*RANGE_VELO);
			if (focusOffsetZ > focusAtScale) focusOffsetZ = focusAtScale;
		}
		else
		{
			if (focusOffsetZ > focusAtScale) focusOffsetZ = focusOffsetZ - (frameTime*RANGE_VELO);
			if (focusOffsetZ < focusAtScale) focusOffsetZ = focusAtScale;
		}

		// langsam zur idealen range zurückfallen
		float lookRange	 = Distance( camVob->GetPositionWorld(), moveTracker->GetPlayerPos() );
		
		if (lookRange < GetBestRange()*100) 
		{
			float rng			=	lookRange + (frameTime * RANGE_VELO * 10);
			
			int	  searchFlags   =	zPATHSEARCH_INCLUDE_PLAYER_CHECK		| 
									zPATHSEARCH_INCLUDE_NEARWALL_CHECK		|
									zPATHSEARCH_INCLUDE_CAM_CHECK;

			if (rng > GetBestRange()*100) rng = GetBestRange()*100;
			
			zPOINT3 test = CalcAziElevRange( bestRotY,bestRotX,rng, moveTracker->GetPlayerTrafo());
			if ( pathSearch->IsPointValid( test,searchFlags ) )  lookRange = rng;
			
		} 

		aiTry = CalcAziElevRange( bestRotY,bestRotX,lookRange, moveTracker->GetPlayerTrafo());

		pathSearch->AdjustCenterSphere( aiTry, moveTracker->GetPlayerPos(), 30.0f );
		
		if ( ((aiTry-moveTracker->GetPlayerHead()).Length()<40) || ((aiTry-moveTracker->GetPlayerPos()).Length()<65)) 
		{
			aiTry		= moveTracker->GetPlayerHead ();
			firstPerson = TRUE;
		}
	}
	else 
	{
		aiTry		= moveTracker->GetPlayerHead ();
		firstPerson = TRUE;
	}

	zSPathSearchResult evasion;

	evasion.bestLerpMode	= zPATH_LERP_LINE;
	evasion.p1				= camVob->GetPositionWorld();
	evasion.p2				= aiTry;
	evasion.veloTrans		= this->veloTrans;
	evasion.veloRot			= this->veloRot;
	evasion.r1.Matrix4ToQuat(camVob->trafoObjToWorld);
	
	if (firstPerson)	
	{
		if		(zinput->GetState(GAME_DOWN)) 											bestRotX = bestRotX + s_iLookAroundSgn * (0.3F*(frameTime * ELEV_VELO)); 
		else if	(zinput->GetState(GAME_UP)) 											bestRotX = bestRotX - s_iLookAroundSgn * (0.3F*(frameTime * ELEV_VELO)); 						
		if		(zinput->GetState(GAME_LEFT) || zinput->GetState(GAME_STRAFELEFT))		bestRotY = bestRotY - (4.5F*(frameTime * AZI_VELO )); 
		else if (zinput->GetState(GAME_RIGHT)|| zinput->GetState(GAME_STRAFERIGHT))		bestRotY = bestRotY + (4.5F*(frameTime * AZI_VELO ));

		zClamp( bestRotX, -89.999f, 89.999f	);
		zClamp( bestRotY, -95.0f,95.0f		);

		evasion.bestLerpMode	= zPATH_LERP_CUSTOM;
		playerTrafo.SetTranslation(aiTry);
		zMAT4 firstPersonTrafo	= moveTracker->GetPlayerTrafo();
		
		firstPersonTrafo.PostRotateY(bestRotY);
		firstPersonTrafo.PostRotateX(bestRotX);
		evasion.r2.Matrix4ToQuat(firstPersonTrafo);
	}

	moveTracker->InterpolateTo(evasion);
	zMAT4 newTrafo = camVob->GetNewTrafoObjToWorld();
	zPOINT3 newPos = newTrafo.GetTranslation();
	pathSearch->AdjustCenterSphere(newPos,moveTracker->GetPlayerPos());
	newTrafo.SetTranslation(newPos);
	camVob->SetTrafo(newTrafo);

};


// FIXME: gamecode
#include "oanictrl.h"
void zCAICamera :: AI_FirstPerson()
{
	zREAL x,y,z;
	zinput->GetMousePos(x,y,z);
	// [BENDLIN] 1.30 
	rotOffsetX += s_iLookAroundSgn * y * 0.6f;
	if (rotOffsetX>+89) rotOffsetX = +89;
	if (rotOffsetX<-89) rotOffsetX = -89;

	zCPathSearch::zSPathSearchOptions searchOpts;
	searchOpts.SetDefaults();
	searchOpts.quality		  = 1;
	searchOpts.poseFailReason = zFAILREASON_BADSCENE_CINEMA;
	pathSearch->FindBestEvasion(searchOpts);
	evasionSearchReport->p2 = moveTracker->GetPlayerHead();
	evasionSearchReport->p2[VY]+=10;


// hack, damit die firstperson camera richtig funzt (aber nicht wenn das model steht)

	if ( zinput->GetState(GAME_UP) && GetMode()!=CamModInventory ) 
	{
		zBOOL standing = FALSE;
		if (target)
		{
			if (zDYNAMIC_CAST<oCAniCtrl_Human>(target->GetAI()))
			{
				standing = static_cast<oCAniCtrl_Human*>(target->GetAI())->IsStanding();
			}
		}

		if (!standing) evasionSearchReport->p2 += 28 * target->GetAtVectorWorld();
	}

	pathSearch->AdjustCenterSphere( evasionSearchReport->p2, moveTracker->GetPlayerPos(), 30.0f );

	moveTracker->InterpolateTo(*evasionSearchReport);
}


void zCAICamera :: AI_Normal()
{
	// 1. Alle Arten von best Positions werden versucht zu erreichen,
	// 2. Falls keine Position davon gültig ist werden Ausweichmöglichkeiten in der Sphäre gesucht,
	//    ist das Target nicht in Bewegung, wird die Suche weiter eingeschränkt, 
	//    d.h. es muss auch noch das gesehen werden, was der Spieler sieht.
	// Effektiv bedeutet das, dass die Kamera, bei sich bewegendem Target potentiell nicht
	// immer das sieht, was der Spieler sieht, sich dafür aber ruhiger verhält.

	//if (bMouseUsed)
	if (1)
	{
		evasionSearchReport->p1				= camVob->GetPositionWorld();
		evasionSearchReport->p2				= GetCamSysFirstPos();
		evasionSearchReport->bestLerpMode	= zPATH_LERP_LINE;
		evasionSearchReport->veloTrans		= this->veloTrans;
		evasionSearchReport->veloRot		= this->veloRot;
		evasionSearchReport->r1.Matrix4ToQuat(camVob->trafoObjToWorld);
		evasionSearchReport->r2.Matrix4ToQuat(camVob->trafoObjToWorld);
		
		pathSearch->AdjustCenterSphere(evasionSearchReport->p2,moveTracker->GetPlayerPos());

		// FIXME: folgendes assert tritt andauernd auf (newworld_city.zen)
//		zERR_ASSERT(pathSearch->LineOfSight(moveTracker->GetPlayerPos(),evasionSearchReport->p2));

		//zERR_WARNING("C: length" + zSTRING((evasionSearchReport->p2-moveTracker->GetPlayerPos()).Length()));
		
		if ( (evasionSearchReport->p2-moveTracker->GetPlayerPos()).Length()<80 )
		{
			evasionSearchReport->p2				= moveTracker->GetShoulderCamMat().GetTranslation();
			evasionSearchReport->r2.Matrix4ToQuat(moveTracker->GetShoulderCamMat());
			evasionSearchReport->bestLerpMode   = zPATH_LERP_CUSTOM;

			if (!pathSearch->IsPointValid(evasionSearchReport->p2,zPATHSEARCH_INCLUDE_PLAYER_CHECK))
			{
				evasionSearchReport->p2 = moveTracker->GetPlayerHead();
			}
		}

		moveTracker->InterpolateTo(*evasionSearchReport);
		return;
	}

	const  float MAX_AZI_DEG_SEARCH_PLAYER_FOCUS	= 45;

	int searchFlags;
	zBOOL checkPlayerTarget							= FALSE;

	// wenn der Spieler sich bewegt hat, den Player Focus nicht mit berücksichtigen
	if (moveTracker->PlayerStands())						checkPlayerTarget = TRUE;
	if (zAbs(bestRotY) >=MAX_AZI_DEG_SEARCH_PLAYER_FOCUS )	checkPlayerTarget = FALSE;


	zPOINT3 bestPos					= GetCamSysFirstPos();
//	int targetCheckFlag = checkPlayerTarget ? zPATHSEARCH_INCLUDE_PLAYER_TARGET_CHECK : 0;
	int targetCheckFlag = 0;//checkPlayerTarget ? zPATHSEARCH_INCLUDE_PLAYER_TARGET_CHECK : 0;
	// first check. Is the best Position valid ?
	searchFlags = zPATHSEARCH_INCLUDE_CAM_CHECK			|
				  zPATHSEARCH_INCLUDE_PLAYER_CHECK		| 
				  zPATHSEARCH_USE_PLAYER_MESH			| 
				  zPATHSEARCH_INCLUDE_NEARWALL_CHECK	| targetCheckFlag;

	evasionSearchReport->p1				= camVob->GetPositionWorld();
	evasionSearchReport->p2				= bestPos;
	evasionSearchReport->bestLerpMode	= zPATH_LERP_LINE;
	evasionSearchReport->veloTrans		= this->veloTrans;
	evasionSearchReport->veloRot		= this->veloRot;
	evasionSearchReport->r1.Matrix4ToQuat(camVob->trafoObjToWorld);
	evasionSearchReport->r2.Matrix4ToQuat(camVob->trafoObjToWorld);

	if ( !pathSearch->IsPointValid( bestPos, searchFlags ) )
	{
		zCPathSearch::zSPathSearchOptions searchOpts;
		searchOpts.SetDefaults();
		searchOpts.quality		  = 1;
		searchOpts.poseFailReason = failReasonDummy;

		pathSearch->FindBestEvasion(searchOpts);
	}

	moveTracker->InterpolateTo(*evasionSearchReport);
}


zPOINT3& zCAICamera::GetCamSysFirstPos()
{
	return camSysFirstPos;
}

void zCAICamera::SetHintTargetInPortalRoom(const zBOOL b)
{
	if (targetInPortalRoom != b)
	{
		if (!targetInPortalRoom)
		{
			if (camDistOffset>0.5f)	camDistOffset = 0.5f;
		}
		targetInPortalRoom = b;		
	}
};

void zCAICamera	:: CheckKeys()
{
	const float VEL_CAMRANGE = 3.0F;

	if		(zinput->KeyPressed(KEY_GREYMINUS))
	{
		camDistOffset -= VEL_CAMRANGE * moveTracker->GetFrameTime();
		zClamp(camDistOffset,minRange-(bestRange+npcVolumeRangeOffset),maxRange-(bestRange+npcVolumeRangeOffset));
	}	
	else if (zinput->KeyPressed(KEY_GREYPLUS))
	{
		camDistOffset += VEL_CAMRANGE * moveTracker->GetFrameTime();
		zClamp(camDistOffset,minRange-(bestRange+npcVolumeRangeOffset),maxRange-(bestRange+npcVolumeRangeOffset));
	}
	
	if (zinput->GetDeviceConnected(zINPUT_MOUSE) && zinput->GetDeviceEnabled(zINPUT_MOUSE))
	{
		bMouseUsed		= TRUE;
		
		zBOOL bLookingCam = (GetMode() == CamModLook);
		zBOOL bInvCam	  = (GetMode() == CamModInventory);
		zBOOL bClimbCam	  = (GetMode() == CamModClimb);
		zBOOL bDeathCam   = (GetMode() == CamModDeath);
		zBOOL bLadderCam  = (GetMode() == CamModMobLadder);
		zBOOL bDiveCam	  = (GetMode() == CamModDive);
		zBOOL bLookBackCam= (GetMode() == CamModLookBack);
		zBOOL bMobUseCam  = (GetMode().Search("CAMMODMOB")!=-1);

		zBOOL bMouseCam   = bClimbCam					||
							bLookingCam					|| 
							bDeathCam					||
							bLadderCam					||
							bInvCam						||
							bMobUseCam					||
							bLookBackCam				||
							GetMode() == CamModNormal	|| 
							GetMode() == CamModRun		||
							GetMode() == CamModMelee	||
							GetMode() == CamModMagic	||
							GetMode() == CamModRanged	||
							GetMode() == CamModSwim		||
							GetMode() == CamModDive;	

		if ( bMouseCam )
		{
			const  zREAL MIN_MOUSE_DX		= 0;
			const  zREAL MIN_MOUSE_DY		= 0;
			const  zREAL MIN_MOUSE_DZ		= 0;
			const  zREAL MAX_MOUSE_DX		= 100;
			const  zREAL MAX_MOUSE_DY		= 100;
			const  zREAL MAX_MOUSE_DZ		= 100;
			const  zREAL MOUSE_AZI_VELO		= 5;
			const  zREAL MOUSE_ELEV_VELO	= 5;
			const  zREAL MOUSE_RANGE_VELO	= 5;

			zREAL mx,my,mz;

			zinput->GetMousePos(mx,my,mz);

			zClamp(mx, -MAX_MOUSE_DX, MAX_MOUSE_DX);
			zClamp(my, -MAX_MOUSE_DY, MAX_MOUSE_DY);
			zClamp(mz, -MAX_MOUSE_DZ, MAX_MOUSE_DZ);

			if	(  zAbs(my)>MIN_MOUSE_DY ) 
			{
				zREAL xScale	= 1.5f;

				if		(firstPerson)					xScale = 2.0f;
				else if	(bLookingCam || bLookBackCam)	xScale = 1.5f;
				if		(bDiveCam   ) {
					//xScale = 3.0f;
					xScale = 0;
					//my     = -my;
				}
				
				//if (!bInvCam) bestRotX	= bestRotX + s_iLookAroundSgn * (moveTracker->GetFrameTime() * my * xScale * MOUSE_ELEV_VELO); 
				// [EDENFELD] 1.09 im Inventory Modus kann man jetzt auch hoch & runter schauen
				bestRotX	= bestRotX + s_iLookAroundSgn * (moveTracker->GetFrameTime() * my * xScale * MOUSE_ELEV_VELO); 
			}

			if (zAbs(mx)>MIN_MOUSE_DX)
			{
				if (bLookingCam || bInvCam || bClimbCam || bDeathCam || bLadderCam || bMobUseCam) 
				{
					zREAL yScale = 2.0f;
					if (firstPerson) 
					{
						mx		= -mx;
						yScale	= 4.0f;
					}
					else if (bLookingCam)
					{
						yScale  = 2.5f;
					}
					else if (bInvCam || bClimbCam || bDeathCam || bLadderCam)
					{
						yScale  = 2.5f;
					}
					bestRotY	= bestRotY - (moveTracker->GetFrameTime() * mx * yScale * MOUSE_AZI_VELO ); 
				}
			}

			if (!zCMenu::GetActive())		// Status screen, log screen, menu
			if ( !bInvCam && zAbs(mz) > MIN_MOUSE_DZ )
			{
				camDistOffset -= MOUSE_RANGE_VELO * moveTracker->GetFrameTime() * zSign(mz);
				zClamp(camDistOffset,minRange-(bestRange+npcVolumeRangeOffset),maxRange-(bestRange+npcVolumeRangeOffset));
			}

			zClamp( bestRotX, -60.0f, 84.999f );

			if (bInvCam || bDeathCam || bMobUseCam) zClamp( bestRotY, -180.0f, 180.0f   );
			else		 zClamp( bestRotY, -80.0f, 89.999f   );

		};
	}
	else bMouseUsed = FALSE;

	moveTracker->SetHintMouseUsed(bMouseUsed);
}

/********************************************************************************
 FUNCTION: DoAI
 DESC    : Performs all cam-AI during each frame
 PARAM   : ptr. to (cam) vob doing AI with
*********************************************************************************/

void zCAICamera	:: DoAI(zCVob* camera, zBOOL &vobDeleted)
{	
	// da die camera nicht performance kritisch ist, und höchste präzision vonnöten ist, 
	// wird die fpu auf 64 bit precision gesetzt

	if (ztimer.GetFrameTimeF() == 0) return;

	// läuft eine cutscene camera oder ist die dialogcamera aktiv ? -> dann raus hier
	if ( zCCSCamera::GetIsPlaying() || GetMode() == CamModDialog ) 
	{
		if (target)
		{
			if (zDYNAMIC_CAST<zCModel>(target->GetVisual()))
			{
				static_cast<zCModel*>(target->GetVisual())->SetDrawHandVisualsOnly(FALSE);
			}
			target->SetVisualAlphaEnabled(0);
			target->SetVisualAlpha(1);
		}
		return;
	}
	else 
	{
		zBOOL autoChange;
		zCZoneMusic::GetAutochange(&autoChange);
		if (!autoChange) zCZoneMusic::SetAutochange(TRUE);
	}


	zfpuControler.SaveCurrentControlWord();
	zfpuControler.SetPrecision_64();

	CheckKeys		 ();
	CheckUnderWaterFX();


#if 0
	// Bugfix 1.08: Nach Beenden eines Dialoges wurde illegalerweise ein falscher FOV im Savegame gespeichert
	// Ursache war ein falscher Wert in zCCSCamera.cpp. Folgender Code ist nun obsolet
	if ( zCCamera::activeCam )
	{
		if (zCCamera::activeCam->GetFOV() != 90.0f)
		{
			zCCamera::activeCam->SetFOV(90.0F);
			zCCamera::activeCam->Activate();
		}
	}
#endif

	CalcFirstPosition  ();

	camera->BeginMovement();
	moveTracker->Update();

	{
		
		raysCasted = 0;
		D_Reset();

		CheckKeys();

		if	( GetMode() == CamModLook		 ) AI_LookingCam	();		else
		if  ( GetMode() == CamModFirstPerson ) AI_FirstPerson	();	
		else 								   AI_Normal		();
	}

	/// ALPHA FADE
	if (GetMode() != CamModFirstPerson)
	{
		if (target)
		{	
			if (zDYNAMIC_CAST<zCModel>(target->GetVisual()))
			{
				static_cast<zCModel*>(target->GetVisual())->SetDrawHandVisualsOnly(FALSE);
			}

			// [BENDLIN] Addon - Ghost Alpha
			zREAL alpha			= targetAlpha;
			zREAL distToHead	= (moveTracker->GetPlayerHead()-moveTracker->GetCamPos()).Length();
			zREAL maxExtend		= (npcVolumeRangeOffset+HUMAN_NORMAL_MAX_EXTENT)*0.8F;

			if (  ((distToHead < minRange*100) && (moveTracker->GetRange() < maxExtend) && (moveTracker->GetRange()<minRange*100)) )
			{
					  alpha		= zSinusEase(MIN(1,distToHead/maxExtend));
			}
			target->SetVisualAlphaEnabled(alpha<1);
			target->SetVisualAlpha(alpha);
		}
	}
	else
	{
		if (zDYNAMIC_CAST<zCModel>(target->GetVisual()))
		{
			static_cast<zCModel*>(target->GetVisual())->SetDrawHandVisualsOnly(TRUE);
		}
	}

	camera->EndMovement	();
	
	if (showDebug) ShowDebug();

#ifdef DEBUG_EDENFELD

	if (camVob != zCCamera::activeCam->GetVob()) 
	{
		zCCamera::activeCam->Activate();
		DrawClipLine(camVob->GetPositionWorld(),moveTracker->GetPlayerPos(),GFX_WHITE);
		DrawClipLine(camVob->GetPositionWorld(),camVob->GetPositionWorld() + 150*camVob->GetAtVectorWorld(),		GFX_GREEN);
	}

#endif

	moveTracker->SaveFrameStates();

	zfpuControler.RestoreSavedControlWord();
}

void zCAICamera ::SetRotateEnabled(const zBOOL r)
{
	moveTracker->SetRotateEnabled(r);
}

zCLASS_DEFINITION(zCAICamera,zCAIBase,0,0)

/*EOF********************************************************************************/
	


